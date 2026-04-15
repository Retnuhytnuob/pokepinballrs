#include "global.h"
#include "main.h"


void RubyBoardProcess_0A_50848(void)
{
    s16 i;
    struct SpriteGroup *group;

    for (i = 0; i < 84; i++)
        gMain.spriteGroups[i].active = 0;

    gMain.spriteGroups[64].active = 1;
    group = &gMain.spriteGroups[48]; // fake match?
    gMain.spriteGroups[70].active = 1;
    gMain.spriteGroups[0].active = 1;
    gMain.spriteGroups[1].active = 1;
    gMain.spriteGroups[2].active = 1;
    gMain.spriteGroups[28].active = 1;
    gMain.spriteGroups[81].active = 1;
    gMain.spriteGroups[65].active = 1;
    gMain.spriteGroups[71].active = 1;
    gMain.spriteGroups[66].active = 1;
    gMain.spriteGroups[51].active = 1;
    gMain.spriteGroups[61].active = 1;
    group->active = 1;
    gMain.spriteGroups[52].active = 1;
    gMain.spriteGroups[62].active = 1;
    LoadSpriteSets(
        gFieldSpriteSets[gMain.selectedField].spriteSets,
        gFieldSpriteSets[gMain.selectedField].numSpriteSets,
        gMain.spriteGroups);
}

void RubyBoardProcess_0B_50918(void)
{
    s16 i;

    gMain.spriteGroups[10].active = 0;
    gMain.spriteGroups[11].active = 0;
    gMain.spriteGroups[48].active = 0;
    gMain.spriteGroups[71].active = 0;
    for (i = 51; i < 67; i++)
        gMain.spriteGroups[i].active = 0;

    gCurrentPinballGame->randomSpriteVariantSeed = gMain.systemFrameCount % 25;
    if (gCurrentPinballGame->cameraYViewport < 110)
    {
        gMain.spriteGroups[65].active = 1;
        gMain.spriteGroups[71].active = 1;
        gMain.spriteGroups[66].active = 1;
    }

    if (gCurrentPinballGame->cameraYViewport < 168)
    {
        gMain.spriteGroups[48].active = 1;
        gMain.spriteGroups[52].active = 1;
    }

    if (gCurrentPinballGame->cameraYViewport < 220)
    {
        gMain.spriteGroups[51].active = 1;
        gMain.spriteGroups[61].active = 1;
        gMain.spriteGroups[64].active = 1;
        if (gCurrentPinballGame->shouldProcessWhiscash)
            gMain.spriteGroups[63].active = 1;
        else
            gMain.spriteGroups[62].active = 1;
    }

    if (gCurrentPinballGame->cameraYViewport > 63)
    {
        gMain.spriteGroups[53].active = 1;
        gMain.spriteGroups[57].active = 1;
    }

    if (gCurrentPinballGame->cameraYViewport > 115)
        gMain.spriteGroups[58].active = 1;

    if (gCurrentPinballGame->cameraYViewport > 130)
    {
        gMain.spriteGroups[59].active = 1;
        gMain.spriteGroups[60].active = 1;
    }

    if (gCurrentPinballGame->cameraYViewport > 216)
    {
        gMain.spriteGroups[56].active = 1;
        gMain.spriteGroups[54].active = 1;
        gMain.spriteGroups[55].active = 1;
        gMain.spriteGroups[10].active = 1;
        gMain.spriteGroups[11].active = 1;
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

    gMain.spriteGroups[72].active = 1;
    gMain.spriteGroups[63].active = 1;
    gMain.spriteGroups[60].active = 1;
    gMain.spriteGroups[69].active = 1;
    gMain.spriteGroups[52].active = 1;
    gMain.spriteGroups[74].active = 1;
    gMain.spriteGroups[0].active = 1;
    gMain.spriteGroups[1].active = 1;
    gMain.spriteGroups[2].active = 1;
    gMain.spriteGroups[25].active = 1;
    gMain.spriteGroups[85].active = 1;
    LoadSpriteSets(gFieldSpriteSets[gMain.selectedField].spriteSets,
                   gFieldSpriteSets[gMain.selectedField].numSpriteSets,
                   gMain.spriteGroups);
}

void SapphireBoardProcess_0B_50B80(void)
{
    s16 i;

    for (i = 55; i < 71; i++)
        gMain.spriteGroups[i].active = 0;

    gMain.spriteGroups[52].active = 0;
    gMain.spriteGroups[72].active = 0;
    gMain.spriteGroups[26].active = 0;
    gMain.spriteGroups[51].active = 0;
    gMain.spriteGroups[76].active = 0;
    gMain.spriteGroups[75].active = 0;
    gMain.spriteGroups[10].active = 0;
    gMain.spriteGroups[11].active = 0;
    gCurrentPinballGame->randomSpriteVariantSeed = gMain.systemFrameCount % 25;
    if (gCurrentPinballGame->cameraYViewport < 90)
    {
        gMain.spriteGroups[52].active = 1;
        gMain.spriteGroups[51].active = 1;
    }
    if (gCurrentPinballGame->cameraYViewport < 220)
    {
        gMain.spriteGroups[72].active = 1;
    }
    if (gCurrentPinballGame->cameraYViewport < 150)
    {
        gMain.spriteGroups[60].active = 1;
        gMain.spriteGroups[69].active = 1;
    }
    if (gCurrentPinballGame->cameraYViewport < 196)
    {
        gMain.spriteGroups[63].active = 1;
        gMain.spriteGroups[75].active = 1;
    }
    if (gCurrentPinballGame->cameraYViewport < 202)
    {
        gMain.spriteGroups[61].active = 1;
        gMain.spriteGroups[58].active = 1;
        gMain.spriteGroups[62].active = 1;
        gMain.spriteGroups[59].active = 1;
        gMain.spriteGroups[76].active = 1;
    }
    if (gCurrentPinballGame->cameraYViewport > 118)
    {
        gMain.spriteGroups[70].active = 1;
        gMain.spriteGroups[26].active = 1;
        gMain.spriteGroups[64].active = 1;
        gMain.spriteGroups[68].active = 1;
        gMain.spriteGroups[65].active = 1;
        gMain.spriteGroups[66].active = 1;
        gMain.spriteGroups[67].active = 1;
    }
    if (gCurrentPinballGame->cameraYViewport > 216)
    {
        gMain.spriteGroups[57].active = 1;
        gMain.spriteGroups[55].active = 1;
        gMain.spriteGroups[56].active = 1;
        gMain.spriteGroups[10].active = 1;
        gMain.spriteGroups[11].active = 1;
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
    gMain.spriteGroups[23].active = 1;
    gMain.spriteGroups[9].active = 1;
    gMain.spriteGroups[24].active = 1;
    gMain.spriteGroups[16].active = 1;
    gMain.spriteGroups[17].active = 1;
    gMain.spriteGroups[7].active = 1;
    gMain.spriteGroups[10].active = 1;
    gMain.spriteGroups[11].active = 1;
    gMain.spriteGroups[12].active = 1;
    gMain.spriteGroups[13].active = 1;
    gMain.spriteGroups[14].active = 1;
    gMain.spriteGroups[15].active = 1;
    gMain.spriteGroups[18].active = 1;
    gMain.spriteGroups[19].active = 1;
    gMain.spriteGroups[20].active = 1;
    gMain.spriteGroups[21].active = 1;
    gMain.spriteGroups[25].active = 1;
    gMain.spriteGroups[26].active = 1;
    gMain.spriteGroups[27].active = 1;
    gMain.spriteGroups[28].active = 1;
    gMain.spriteGroups[31].active = 1;
    gMain.spriteGroups[32].active = 1;
    gMain.spriteGroups[29].active = 1;
    gMain.spriteGroups[30].active = 1;

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
    gMain.spriteGroups[11].active = 1;
    gMain.spriteGroups[12].active = 1;
    gMain.spriteGroups[13].active = 1;
    gMain.spriteGroups[14].active = 1;
    gMain.spriteGroups[21].active = 1;
    gMain.spriteGroups[22].active = 1;
    gMain.spriteGroups[23].active = 1;
    gMain.spriteGroups[15].active = 1;

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
    gMain.spriteGroups[11].active = 1;
    gMain.spriteGroups[12].active = 1;
    gMain.spriteGroups[13].active = 1;
    gMain.spriteGroups[14].active = 1;
    gMain.spriteGroups[29].active = 1;

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
    gMain.spriteGroups[42].active = 1;
    gMain.spriteGroups[11].active = 1;
    gMain.spriteGroups[12].active = 1;
    gMain.spriteGroups[13].active = 1;
    gMain.spriteGroups[21].active = 1;

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
    gMain.spriteGroups[18].active = 1;
    gMain.spriteGroups[21].active = 1;
    gMain.spriteGroups[22].active = 1;
    gMain.spriteGroups[14].active = 1;
    gMain.spriteGroups[15].active = 1;
    gMain.spriteGroups[16].active = 1;
    gMain.spriteGroups[17].active = 1;

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
