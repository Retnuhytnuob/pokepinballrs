#include "global.h"
#include "main.h"


void RubyBoardProcess_0A_50848(void)
{
    s16 i;
    struct SpriteGroup *group;

    for (i = 0; i < 84; i++)
        gMain.spriteGroups[i].active = 0;

    gMain.spriteGroups[SG_64].active = 1;
    group = &gMain.spriteGroups[SG_48]; // fake match?
    gMain.spriteGroups[SG_70].active = 1;
    gMain.spriteGroups[SG_0].active = 1;
    gMain.spriteGroups[SG_1].active = 1;
    gMain.spriteGroups[SG_2].active = 1;
    gMain.spriteGroups[SG_28].active = 1;
    gMain.spriteGroups[SG_81].active = 1;
    gMain.spriteGroups[SG_65].active = 1;
    gMain.spriteGroups[SG_71].active = 1;
    gMain.spriteGroups[SG_66].active = 1;
    gMain.spriteGroups[SG_51].active = 1;
    gMain.spriteGroups[SG_61].active = 1;
    group->active = 1;
    gMain.spriteGroups[SG_52].active = 1;
    gMain.spriteGroups[SG_62].active = 1;
    LoadSpriteSets(
        gFieldSpriteSets[gMain.selectedField].spriteSets,
        gFieldSpriteSets[gMain.selectedField].numSpriteSets,
        gMain.spriteGroups);
}

void RubyBoardProcess_0B_50918(void)
{
    s16 i;

    gMain.spriteGroups[SG_10].active = 0;
    gMain.spriteGroups[SG_11].active = 0;
    gMain.spriteGroups[SG_48].active = 0;
    gMain.spriteGroups[SG_71].active = 0;
    for (i = 51; i < 67; i++)
        gMain.spriteGroups[i].active = 0;

    gCurrentPinballGame->randomSpriteVariantSeed = gMain.systemFrameCount % 25;
    if (gCurrentPinballGame->cameraYViewport < 110)
    {
        gMain.spriteGroups[SG_65].active = 1;
        gMain.spriteGroups[SG_71].active = 1;
        gMain.spriteGroups[SG_66].active = 1;
    }

    if (gCurrentPinballGame->cameraYViewport < 168)
    {
        gMain.spriteGroups[SG_48].active = 1;
        gMain.spriteGroups[SG_52].active = 1;
    }

    if (gCurrentPinballGame->cameraYViewport < 220)
    {
        gMain.spriteGroups[SG_51].active = 1;
        gMain.spriteGroups[SG_61].active = 1;
        gMain.spriteGroups[SG_64].active = 1;
        if (gCurrentPinballGame->shouldProcessWhiscash)
            gMain.spriteGroups[SG_63].active = 1;
        else
            gMain.spriteGroups[SG_62].active = 1;
    }

    if (gCurrentPinballGame->cameraYViewport > 63)
    {
        gMain.spriteGroups[SG_53].active = 1;
        gMain.spriteGroups[SG_57].active = 1;
    }

    if (gCurrentPinballGame->cameraYViewport > 115)
        gMain.spriteGroups[SG_58].active = 1;

    if (gCurrentPinballGame->cameraYViewport > 130)
    {
        gMain.spriteGroups[SG_59].active = 1;
        gMain.spriteGroups[SG_60].active = 1;
    }

    if (gCurrentPinballGame->cameraYViewport > 216)
    {
        gMain.spriteGroups[SG_56].active = 1;
        gMain.spriteGroups[SG_54].active = 1;
        gMain.spriteGroups[SG_55].active = 1;
        gMain.spriteGroups[SG_10].active = 1;
        gMain.spriteGroups[SG_11].active = 1;
    }

    LoadSpriteSets(
        gFieldSpriteSets[gMain.selectedField].spriteSets,
        gFieldSpriteSets[gMain.selectedField].numSpriteSets,
        gMain.spriteGroups);
}

void SapphireBoardProcess_0A_50AD4(void)
{
    s16 i;

    for (i = 0; i < 87; i++)
        gMain.spriteGroups[i].active = 0;

    gMain.spriteGroups[SG_72].active = 1;
    gMain.spriteGroups[SG_63].active = 1;
    gMain.spriteGroups[SG_60].active = 1;
    gMain.spriteGroups[SG_69].active = 1;
    gMain.spriteGroups[SG_52].active = 1;
    gMain.spriteGroups[SG_74].active = 1;
    gMain.spriteGroups[SG_0].active = 1;
    gMain.spriteGroups[SG_1].active = 1;
    gMain.spriteGroups[SG_2].active = 1;
    gMain.spriteGroups[SG_25].active = 1;
    gMain.spriteGroups[SG_85].active = 1;
    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void SapphireBoardProcess_0B_50B80(void)
{
    s16 i;

    for (i = 55; i < 71; i++)
        gMain.spriteGroups[i].active = 0;

    gMain.spriteGroups[SG_52].active = 0;
    gMain.spriteGroups[SG_72].active = 0;
    gMain.spriteGroups[SG_26].active = 0;
    gMain.spriteGroups[SG_51].active = 0;
    gMain.spriteGroups[SG_76].active = 0;
    gMain.spriteGroups[SG_75].active = 0;
    gMain.spriteGroups[SG_10].active = 0;
    gMain.spriteGroups[SG_11].active = 0;
    gCurrentPinballGame->randomSpriteVariantSeed = gMain.systemFrameCount % 25;
    if (gCurrentPinballGame->cameraYViewport < 90)
    {
        gMain.spriteGroups[SG_52].active = 1;
        gMain.spriteGroups[SG_51].active = 1;
    }
    if (gCurrentPinballGame->cameraYViewport < 220)
    {
        gMain.spriteGroups[SG_72].active = 1;
    }
    if (gCurrentPinballGame->cameraYViewport < 150)
    {
        gMain.spriteGroups[SG_60].active = 1;
        gMain.spriteGroups[SG_69].active = 1;
    }
    if (gCurrentPinballGame->cameraYViewport < 196)
    {
        gMain.spriteGroups[SG_63].active = 1;
        gMain.spriteGroups[SG_75].active = 1;
    }
    if (gCurrentPinballGame->cameraYViewport < 202)
    {
        gMain.spriteGroups[SG_61].active = 1;
        gMain.spriteGroups[SG_58].active = 1;
        gMain.spriteGroups[SG_62].active = 1;
        gMain.spriteGroups[SG_59].active = 1;
        gMain.spriteGroups[SG_76].active = 1;
    }
    if (gCurrentPinballGame->cameraYViewport > 118)
    {
        gMain.spriteGroups[SG_70].active = 1;
        gMain.spriteGroups[SG_26].active = 1;
        gMain.spriteGroups[SG_64].active = 1;
        gMain.spriteGroups[SG_68].active = 1;
        gMain.spriteGroups[SG_65].active = 1;
        gMain.spriteGroups[SG_66].active = 1;
        gMain.spriteGroups[SG_67].active = 1;
    }
    if (gCurrentPinballGame->cameraYViewport > 216)
    {
        gMain.spriteGroups[SG_57].active = 1;
        gMain.spriteGroups[SG_55].active = 1;
        gMain.spriteGroups[SG_56].active = 1;
        gMain.spriteGroups[SG_10].active = 1;
        gMain.spriteGroups[SG_11].active = 1;
    }

    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets, gFieldSpriteSets[gMain.selectedField].numSpriteSets, gMain.spriteGroups);
}

void DusclopsBoardProcess_0A_50D48(void)
{
    s16 i;

    for (i = 0; i < 15; i++)
    {
        if (i < 5)
            gMain.spriteGroups[i].active = 1;
        else
            gMain.spriteGroups[i].active = 0;
    }

    gMain.fieldSpriteGroups[0]->active = 1;

    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void DusclopsBoardProcess_0B_50DB8(void)
{
    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void KecleonBoardProcess_0A_50DE0(void)
{
    s16 i;

    for (i = 0; i < 33; i++)
    {
        if (i < 5)
            gMain.spriteGroups[i].active = 1;
        else
            gMain.spriteGroups[i].active = 0;
    }

    gMain.fieldSpriteGroups[0]->active = 1;
    gMain.spriteGroups[SG_23].active = 1;
    gMain.spriteGroups[SG_9].active = 1;
    gMain.spriteGroups[SG_24].active = 1;
    gMain.spriteGroups[SG_16].active = 1;
    gMain.spriteGroups[SG_17].active = 1;
    gMain.spriteGroups[SG_7].active = 1;
    gMain.spriteGroups[SG_10].active = 1;
    gMain.spriteGroups[SG_11].active = 1;
    gMain.spriteGroups[SG_12].active = 1;
    gMain.spriteGroups[SG_13].active = 1;
    gMain.spriteGroups[SG_14].active = 1;
    gMain.spriteGroups[SG_15].active = 1;
    gMain.spriteGroups[SG_18].active = 1;
    gMain.spriteGroups[SG_19].active = 1;
    gMain.spriteGroups[SG_20].active = 1;
    gMain.spriteGroups[SG_21].active = 1;
    gMain.spriteGroups[SG_25].active = 1;
    gMain.spriteGroups[SG_26].active = 1;
    gMain.spriteGroups[SG_27].active = 1;
    gMain.spriteGroups[SG_28].active = 1;
    gMain.spriteGroups[SG_31].active = 1;
    gMain.spriteGroups[SG_32].active = 1;
    gMain.spriteGroups[SG_29].active = 1;
    gMain.spriteGroups[SG_30].active = 1;

    LoadSpriteSets(
        gFieldSpriteSets[gMain.selectedField].spriteSets,
        gFieldSpriteSets[gMain.selectedField].numSpriteSets,
        gMain.spriteGroups
    );
}

void nullsub_20(void)
{}

void KyogreBoardProcess_0A_50F04()
{
    s16 i;

    for (i = 0; i < 27; i++)
    {
        if (i < 5)
            gMain.spriteGroups[i].active = 1;
        else
            gMain.spriteGroups[i].active = 0;
    }

    gMain.fieldSpriteGroups[0]->active = 1;
    gMain.spriteGroups[SG_11].active = 1;
    gMain.spriteGroups[SG_12].active = 1;
    gMain.spriteGroups[SG_13].active = 1;
    gMain.spriteGroups[SG_14].active = 1;
    gMain.spriteGroups[SG_21].active = 1;
    gMain.spriteGroups[SG_22].active = 1;
    gMain.spriteGroups[SG_23].active = 1;
    gMain.spriteGroups[SG_15].active = 1;

    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void KyogreBoardProcess_0B_50FAC(void)
{
    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void GroudonBoardProcess_0A_50FD4(void)
{
    s16 i;

    for (i = 0; i < 32; i++)
    {
        if (i < 5) {
            gMain.spriteGroups[i].active = 1;
        } else {
            gMain.spriteGroups[i].active = 0;
        }
    }

    gMain.fieldSpriteGroups[0]->active = 1;
    gMain.spriteGroups[SG_11].active = 1;
    gMain.spriteGroups[SG_12].active = 1;
    gMain.spriteGroups[SG_13].active = 1;
    gMain.spriteGroups[SG_14].active = 1;
    gMain.spriteGroups[SG_29].active = 1;

    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void GroudonBoardProcess_0B_51068(void)
{
    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void RayquazaBoardProcess_0A_51090(void)
{
    s16 i;

    for (i = 0; i < 46; i++)
    {
        if (i < 5)
            gMain.spriteGroups[i].active = 1;
        else
            gMain.spriteGroups[i].active = 0;
    }

    gMain.fieldSpriteGroups[0]->active = 1;
    gMain.spriteGroups[SG_42].active = 1;
    gMain.spriteGroups[SG_11].active = 1;
    gMain.spriteGroups[SG_12].active = 1;
    gMain.spriteGroups[SG_13].active = 1;
    gMain.spriteGroups[SG_21].active = 1;

    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void RayquazaBoardProcess_0B_51128(void)
{
    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void SphealBoardProcess_0A_51150(void)
{
    s16 i;

    for (i = 0; i < 23; i++)
    {
        if (i < 5)
            gMain.spriteGroups[i].active = 1;
        else
            gMain.spriteGroups[i].active = 0;
    }

    gMain.fieldSpriteGroups[0]->active = 1;
    gMain.spriteGroups[SG_18].active = 1;
    gMain.spriteGroups[SG_21].active = 1;
    gMain.spriteGroups[SG_22].active = 1;
    gMain.spriteGroups[SG_14].active = 1;
    gMain.spriteGroups[SG_15].active = 1;
    gMain.spriteGroups[SG_16].active = 1;
    gMain.spriteGroups[SG_17].active = 1;

    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void SphealBoardProcess_0B_511F8(void)
{
    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}
