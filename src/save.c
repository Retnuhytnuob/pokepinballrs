#include "global.h"
#include "m4a.h"
#include "agb_sram.h"
#include "main.h"
#include "constants/species_rs.h"

static bool16 LoadSaveDataFromSram(void);
static void LoadExtraPokedexFlagsFromSram(void);
static void SaveExtraPokedexFlagsToSram(void);

#define EXTRA_POKEDEX_FLAGS_COUNT (NUM_SPECIES - NUM_SAVE_SPECIES)
#define EXTRA_POKEDEX_SAVE_MAGIC 0x58444550
#define EXTRA_POKEDEX_SAVE_OFFSET 0x1A00
#define EXTRA_POKEDEX_SAVE_BACKUP_OFFSET 0x1B00

struct ExtraPokedexSaveData
{
    u32 magic;
    u16 count;
    u16 checksum;
    u8 flags[EXTRA_POKEDEX_FLAGS_COUNT];
};

void SaveFile_LoadGameData(void)
{
    SetSramFastFunc();
    gMain.sramError = FALSE;
    if (LoadSaveDataFromSram() == FALSE)
    {
        ResetSaveFile();
        SaveFile_WriteToSram();
        if (LoadSaveDataFromSram() == FALSE)
        {
            gMain.sramError = TRUE;
            ResetSaveFile();
        }
    }
    else
    {
        SetButtonConfigInputs(gMain_saveData.buttonConfigType);
        LoadExtraPokedexFlagsFromSram();
    }
}

extern u8 gSaveFileSignature[];

static bool16 LoadSaveDataFromSram(void)
{
    u16 isOk = FALSE;
    u16 fileNum;
    u16 i;
    u32 checksum;

    // Looks like there are two copies of the save data, one used as a backup?
    for (fileNum = 0; fileNum < 2; fileNum++)
    {
        u16 *saveData = (u16 *)&gMain_saveData;
        size_t size = sizeof(gMain_saveData);

        ReadSramFast((void *)(SRAM + 0x4 + fileNum * 672), (u8 *)saveData, size);

        // Verify signature
        for (i = 0; i < 10; i++)
        {
            if (gMain_saveData.signature[i] != gSaveFileSignature[i])
                break;
        }
        if (i != 10)
            continue;

        // Verify checksum
        checksum = 0;
        while (size > 1)
        {
            checksum += *saveData++;
            size -= 2;
        }
        if (size != 0)  // never happens (size is even)
            checksum += *saveData & 0xFF00;
        checksum = (checksum & 0xFFFF) + (checksum >> 16);
        if (checksum == 0xFFFF)
        {
            isOk = TRUE;
            break;
        }
    }
    return isOk;
}

static u16 CalcExtraPokedexChecksum(struct ExtraPokedexSaveData *saveData)
{
    u16 i;
    u16 checksum = 0;

    checksum += saveData->magic & 0xFFFF;
    checksum += saveData->magic >> 16;
    checksum += saveData->count;

    for (i = 0; i < EXTRA_POKEDEX_FLAGS_COUNT; i++)
        checksum += saveData->flags[i];

    return ~checksum;
}

static bool16 IsExtraPokedexSaveValid(struct ExtraPokedexSaveData *saveData)
{
    if (saveData->magic != EXTRA_POKEDEX_SAVE_MAGIC)
        return FALSE;

    if (saveData->count != EXTRA_POKEDEX_FLAGS_COUNT)
        return FALSE;

    if (saveData->checksum != CalcExtraPokedexChecksum(saveData))
        return FALSE;

    return TRUE;
}

static void LoadExtraPokedexFlagsFromSram(void)
{
    s16 i;
    struct ExtraPokedexSaveData saveData;

    ReadSramFast((void *)(SRAM + EXTRA_POKEDEX_SAVE_OFFSET), (u8 *)&saveData, sizeof(saveData));
    if (!IsExtraPokedexSaveValid(&saveData))
        ReadSramFast((void *)(SRAM + EXTRA_POKEDEX_SAVE_BACKUP_OFFSET), (u8 *)&saveData, sizeof(saveData));

    if (IsExtraPokedexSaveValid(&saveData))
    {
        for (i = 0; i < EXTRA_POKEDEX_FLAGS_COUNT; i++)
            gExtraPokedexFlags[i] = saveData.flags[i];
    }
    else
    {
        for (i = 0; i < EXTRA_POKEDEX_FLAGS_COUNT; i++)
            gExtraPokedexFlags[i] = SPECIES_UNSEEN;
    }
}

static void SaveExtraPokedexFlagsToSram(void)
{
    s16 i;
    struct ExtraPokedexSaveData saveData;

    saveData.magic = EXTRA_POKEDEX_SAVE_MAGIC;
    saveData.count = EXTRA_POKEDEX_FLAGS_COUNT;

    for (i = 0; i < EXTRA_POKEDEX_FLAGS_COUNT; i++)
        saveData.flags[i] = gExtraPokedexFlags[i];

    saveData.checksum = CalcExtraPokedexChecksum(&saveData);

    WriteAndVerifySramFast((u8 *)&saveData, (void *)(SRAM + EXTRA_POKEDEX_SAVE_OFFSET), sizeof(saveData));
    WriteAndVerifySramFast((u8 *)&saveData, (void *)(SRAM + EXTRA_POKEDEX_SAVE_BACKUP_OFFSET), sizeof(saveData));
}

void SaveFile_WriteToSram(void)
{
    u32 checksum;
    u16 *saveData = (u16 *)&gMain_saveData;
    size_t size = sizeof(gMain_saveData);

    gMain_saveData.saveChangeCounter++;
    gMain_saveData.checksum = 0;

    checksum = 0;
    while (size > 1)
    {
        checksum += *saveData++;
        size -= 2;
    }
    if (size != 0)  // never happens (size is even)
        checksum += *saveData & 0xFF00;
    checksum = (checksum & 0xFFFF) + (checksum >> 16);
    gMain_saveData.checksum = ~((checksum >> 16) + checksum);

    WriteAndVerifySramFast((u8 *)&gMain_saveData, (void *)(SRAM + 0x4),   sizeof(gMain_saveData));
    WriteAndVerifySramFast((u8 *)&gMain_saveData, (void *)(SRAM + 0x2A4), sizeof(gMain_saveData));
    SaveExtraPokedexFlagsToSram();
}

void SaveFile_SetPokedexFlags(s16 species, u8 flag)
{
    u16 *saveData = (u16 *)&gMain_saveData;
    size_t size = sizeof(gMain_saveData);
    u32 checksum;

    if (species >= NUM_SAVE_SPECIES && species < NUM_SPECIES)
    {
        if (gExtraPokedexFlags[species - NUM_SAVE_SPECIES] < flag)
        {
            gExtraPokedexFlags[species - NUM_SAVE_SPECIES] = flag;
            SaveExtraPokedexFlagsToSram();
        }
        return;
    }

    if (species < 0)
        return;

    if (gMain_saveData.pokedexFlags[species] < flag)
    {
        gMain_saveData.saveChangeCounter++;
        gMain_saveData.pokedexFlags[species] = flag;
        gMain_saveData.checksum = 0;

        checksum = 0;
        while (size > 1)
        {
            checksum += *saveData++;
            size -= 2;
        }
        if (size != 0)  // never happens (size is even)
            checksum += *saveData & 0xFF00;
        checksum = (checksum & 0xFFFF) + (checksum >> 16);
        gMain_saveData.checksum = ~((checksum >> 16) + checksum);

        WriteAndVerifySramFast((u8 *)&gMain_saveData, (void *)(SRAM + 0x4),   sizeof(gMain_saveData));
        WriteAndVerifySramFast((u8 *)&gMain_saveData, (void *)(SRAM + 0x2A4), sizeof(gMain_saveData));
    }
}

void SaveFile_ReadSavedGamePresent(void)
{
    ReadSramFast((void *)(SRAM + 0x544), (u8 *)&gMain.hasSavedGame, sizeof(gMain.hasSavedGame));
}

void ResetSaveFile(void)
{
    s16 i;

    for (i = 0; i < 10; i++)
        gMain_saveData.signature[i] = gSaveFileSignature[i];

    gMain_saveData.saveChangeCounter = 0;
    gMain_saveData.rumbleEnabled = FALSE;
    gMain_saveData.ballSpeed = 0;
    SetButtonConfigInputs(BUTTON_CONFIG_RESET);
    SetDefaultHighScores();
    ResetPokedex();
    gMain_saveData.buttonConfigType = BUTTON_CONFIG_TYPE_A;
}
