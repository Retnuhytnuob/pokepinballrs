#include "global.h"
#include "main.h"
#include "m4a.h"
#include "constants/bg_music.h"
#include "constants/generations.h"

enum GenerationSelectState
{
    GENERATION_SELECT_STATE_LOAD,
    GENERATION_SELECT_STATE_INPUT,
    GENERATION_SELECT_STATE_EXIT,
};

EWRAM_DATA u8 gSelectedGeneration = DEFAULT_GENERATION;
static EWRAM_DATA u8 sGenerationCursor = DEFAULT_GENERATION;
static EWRAM_DATA u8 sGenerationNextMainState = STATE_FIELD_SELECT;

extern const u16 gOptionsBackground_Pals[];
extern const u8 gOptionsText_Gfx[];
extern const u8 gOptionsBackground_Gfx[];
extern const u8 gOptionsBackground_Tilemap[];

static void LoadGenerationSelectGraphics(void);
static void HandleGenerationSelectInput(void);
static void ExitGenerationSelect(void);
static void RenderGenerationSelectScreen(void);
static void DrawGenerationSelectText(void);
static void DrawGenerationCell(s16 generation, s16 selected);

void GenerationSelectMain(void)
{
    switch (gMain.subState)
    {
    case GENERATION_SELECT_STATE_LOAD:
        LoadGenerationSelectGraphics();
        break;
    case GENERATION_SELECT_STATE_INPUT:
        HandleGenerationSelectInput();
        break;
    default:
        ExitGenerationSelect();
        break;
    }
}

static void LoadGenerationSelectGraphics(void)
{
    ResetDisplayState();

    REG_DISPCNT = DISPCNT_MODE_0 | DISPCNT_FORCED_BLANK;
    REG_BG0CNT = BGCNT_CHARBASE(1) | BGCNT_SCREENBASE(0) | BGCNT_PRIORITY(0) | BGCNT_TXT256x256;
    REG_BG1CNT = BGCNT_CHARBASE(2) | BGCNT_SCREENBASE(1) | BGCNT_PRIORITY(1) | BGCNT_TXT256x256;
    REG_DISPCNT |= DISPCNT_BG0_ON | DISPCNT_BG1_ON;
    gMain.dispcntBackup = REG_DISPCNT;

    DmaCopy16(3, gOptionsBackground_Pals, (void *)PLTT, 0x200);
    DmaCopy16(3, gOptionsText_Gfx, (void *)(VRAM + 0x4000), 0x1800);
    DmaCopy16(3, gOptionsBackground_Gfx, (void *)(VRAM + 0x8000), 0xC00);
    DmaCopy16(3, gOptionsBackground_Tilemap, (void *)(VRAM + 0x800), 0x800);

    sGenerationCursor = gSelectedGeneration;
    sGenerationNextMainState = STATE_FIELD_SELECT;
    DrawGenerationSelectText();
    RenderGenerationSelectScreen();
    EnableVBlankInterrupts();
    FadeInScreen();
    m4aSongNumStart(MUS_TABLE_SELECT);
    gMain.subState = GENERATION_SELECT_STATE_INPUT;
}

static void HandleGenerationSelectInput(void)
{
    if (JOY_NEW(DPAD_LEFT) && sGenerationCursor > 0)
    {
        sGenerationCursor--;
        m4aSongNumStart(SE_DEX_INFO_FIELD_SELECT_MOVE);
        DrawGenerationSelectText();
        RenderGenerationSelectScreen();
    }
    else if (JOY_NEW(DPAD_RIGHT) && sGenerationCursor < GENERATION_COUNT - 1)
    {
        sGenerationCursor++;
        m4aSongNumStart(SE_DEX_INFO_FIELD_SELECT_MOVE);
        DrawGenerationSelectText();
        RenderGenerationSelectScreen();
    }
    else if (JOY_NEW(DPAD_UP) && sGenerationCursor >= 5)
    {
        sGenerationCursor -= 5;
        m4aSongNumStart(SE_DEX_INFO_FIELD_SELECT_MOVE);
        DrawGenerationSelectText();
        RenderGenerationSelectScreen();
    }
    else if (JOY_NEW(DPAD_DOWN) && sGenerationCursor < 5)
    {
        sGenerationCursor += 5;
        m4aSongNumStart(SE_DEX_INFO_FIELD_SELECT_MOVE);
        DrawGenerationSelectText();
        RenderGenerationSelectScreen();
    }

    if (JOY_NEW(A_BUTTON | START_BUTTON))
    {
        gSelectedGeneration = sGenerationCursor;
        sGenerationNextMainState = STATE_FIELD_SELECT;
        m4aSongNumStart(SE_MENU_SELECT);
        gMain.subState = GENERATION_SELECT_STATE_EXIT;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        sGenerationNextMainState = STATE_TITLE;
        m4aSongNumStart(SE_MENU_CANCEL);
        gMain.subState = GENERATION_SELECT_STATE_EXIT;
    }
}

static void ExitGenerationSelect(void)
{
    FadeOutScreen();
    m4aMPlayAllStop();
    DisableVBlankInterrupts();
    SetMainGameState(sGenerationNextMainState);
}

static void RenderGenerationSelectScreen(void)
{
    DmaCopy16(3, gBG0TilemapBuffer, (void *)VRAM, 0x800);
}

static void DrawGenerationSelectText(void)
{
    s16 i;

    DmaFill16(3, 0x1FF, gBG0TilemapBuffer, 0x800);
    DrawTextToTilemap((u8 *)"SELECT GENERATION", 3, 7);
    DrawTextToTilemap((u8 *)"A OK   B BACK", 17, 8);

    for (i = 0; i < GENERATION_COUNT; i++)
        DrawGenerationCell(i, i == sGenerationCursor);
}

static void DrawGenerationCell(s16 generation, s16 selected)
{
    s16 row = generation / 5;
    s16 col = generation % 5;
    s16 y = 7 + row * 4;
    s16 x = 4 + col * 5;
    u8 text[5];

    text[0] = selected ? '>' : ' ';
    text[1] = 'G';
    if (generation == GENERATION_EXTRA)
        text[2] = 'X';
    else
        text[2] = '1' + generation;
    text[3] = selected ? '<' : ' ';
    text[4] = '\0';
    DrawTextToTilemap(text, y, x);
}
