#include "global.h"
#include "functions.h"
#include "m4a.h"
#include "main.h"
#include "constants/bg_music.h"
#include "constants/dusclops_states.h"

#define BONUS_DUSKULL_TIME 7200 //2 minutes, 60FPS
#define BONUS_DUSKULL_COMPLETE_POINTS 30000000

#define DUSKULL_NEEDED_TO_PHASE_TRANSFER 20
#define DUSKULL_CONCURRENT_MAX 3
#define DUSKULL_ALLOWED_TO_SPAWN DUSKULL_NEEDED_TO_PHASE_TRANSFER - DUSKULL_CONCURRENT_MAX + 1

extern struct SongHeader se_duskull_appear;
extern s16 DusclopsFramesetData[][3];



void DuskullBonus_Setup(void)
{
    s16 i;
    gCurrentPinballGame->unk18 = 0;
    gCurrentPinballGame->unk17 = 0;
    gCurrentPinballGame->unk13 = DUSCLOPS_BOARD_STATE_0_INTRO;
    gCurrentPinballGame->unk294 = 1;
    gCurrentPinballGame->eventTimer = gCurrentPinballGame->timerBonus + BONUS_DUSKULL_TIME;
    gCurrentPinballGame->timerBonus = 0;
    gCurrentPinballGame->unk383 = 0;
    gCurrentPinballGame->unk388 = 3;
    gCurrentPinballGame->ball->unk0 = 1;
    gCurrentPinballGame->unk385 = 0;
    gCurrentPinballGame->unk386 = 0;
    gCurrentPinballGame->boardEntityCollisionMode = DUSCLOPS_ENTITY_COLISION_MODE_NONE;
    gCurrentPinballGame->unk392 = 0;
    gCurrentPinballGame->unk394 = 0;
    gCurrentPinballGame->minionActiveCount = 0;

    for (i = 0; i < DUSKULL_CONCURRENT_MAX; i++)
    {
        gCurrentPinballGame->minionSpriteVariant[i] = 0;
        gCurrentPinballGame->minionNextSpriteVariant[i] = 0;
        gCurrentPinballGame->minionOamIx[i] = 0;
        gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_SPAWN;
        gCurrentPinballGame->minionFramesetIx[i] = 0;
        gCurrentPinballGame->unk3A6[i] = 0;
        gCurrentPinballGame->unk3A9[i] = 0;
        gCurrentPinballGame->unk3AC[i] = 0;
        gCurrentPinballGame->minionStateTimer[i] = 0;
        gCurrentPinballGame->minionTimeAlive[i] = 0;
        gCurrentPinballGame->minionEscapeAtTime[i] = 0;
        gCurrentPinballGame->minionLogicPosition[i].x = 0;
        gCurrentPinballGame->minionLogicPosition[i].y = 0;
        gCurrentPinballGame->minionColisionPosition[i].x = 0;
        gCurrentPinballGame->minionColisionPosition[i].y = 0;
    }

    gCurrentPinballGame->unk3DC = 0;
    gCurrentPinballGame->unk3DE = 0;
    gCurrentPinballGame->unk3DF = 0;
    gCurrentPinballGame->unk3E0 = 0;
    gCurrentPinballGame->unk3E2 = 0;
    gCurrentPinballGame->unk3E4 = 0;
    gCurrentPinballGame->unk3E6 = 0;
    gCurrentPinballGame->unk3E8 = 0;
    gCurrentPinballGame->unk3EA = 0;
    gCurrentPinballGame->unk3EC = 0;
    gCurrentPinballGame->unk3EE = 0;
    gCurrentPinballGame->unk3F0 = 0;
    gCurrentPinballGame->unk3F2 = 0;
    gCurrentPinballGame->unk1A = 0;

    DuskullPhase_ProcessEntityLogic();
    DuskullPhase_ProcessGraphics();

    m4aSongNumStart(MUS_BONUS_FIELD_DUSKULL);

    DmaCopy16(3, (void *)gUnknown_081B36A4, (void *)0x05000320, 32);
}

void DusclopsBoardProcess_3B_33130(void)
{
    s16 temp;
    switch (gCurrentPinballGame->unk13)
    {
        case DUSCLOPS_BOARD_STATE_0_INTRO:
            gCurrentPinballGame->unk5F7 = 1;
            if (gCurrentPinballGame->unk18 < 120)
            {
                temp = gCurrentPinballGame->unk18 / 24;
                DmaCopy16(3, gUnknown_082EE0E0 + temp * 40, 0x05000000, 160);

                gCurrentPinballGame->unkE6 = gCurrentPinballGame->unk18 / 5 + 0xFFE8;
                gCurrentPinballGame->unk18++;
            }
            else
            {
                gCurrentPinballGame->unkE6 = 0;
                gMain.spriteGroups[7].available = TRUE;
                gMain.spriteGroups[8].available = TRUE;
                gMain.spriteGroups[9].available = TRUE;
                gCurrentPinballGame->unk13 = DUSCLOPS_BOARD_STATE_1_DUSKULL_PHASE;
                gCurrentPinballGame->unk18 = 0;
            }

            break;
        case DUSCLOPS_BOARD_STATE_1_DUSKULL_PHASE:
            if (!gCurrentPinballGame->unk386)
            {
                gMain.blendControl = 0x1C10;
                gMain.blendAlpha = 0x30D;
            }
            gCurrentPinballGame->boardEntityCollisionMode = DUSCLOPS_ENTITY_COLISION_MODE_DUSKULL;
            DuskullPhase_ProcessEntityLogic();
            DuskullPhase_ProcessGraphics();
            break;
        case DUSCLOPS_BOARD_STATE_2_INIT_DUSCLOPS_PHASE:
            gCurrentPinballGame->unk13 = DUSCLOPS_BOARD_STATE_3;
            gMain.spriteGroups[13].available = TRUE;
            gMain.spriteGroups[14].available = TRUE;
            gMain.spriteGroups[12].available = TRUE;
            gCurrentPinballGame->boardEntityCollisionMode = DUSCLOPS_ENTITY_COLISION_MODE_NONE;
            gCurrentPinballGame->unk385 = 0;
            m4aSongNumStart(MUS_BONUS_FIELD_DUSCLOPS);
            break;
        case DUSCLOPS_BOARD_STATE_3:
            if (!gCurrentPinballGame->unk386)
            {
                gMain.blendControl = 0x1C10;
                gMain.blendAlpha = 0x1000;
            }
            sub_34450();
            break;
        case DUSCLOPS_BOARD_STATE_4:
            if (gCurrentPinballGame->unk18 < 120)
            {
                gCurrentPinballGame->unk18++;
            }
            else
            {
                gCurrentPinballGame->unk13 = DUSCLOPS_BOARD_STATE_5;
                gCurrentPinballGame->unk18 = 0;
                gMain.spriteGroups[6].available = TRUE;
                gMain.spriteGroups[5].available = TRUE;
                DmaCopy16(3, gDusclopsBonusClear_Gfx, OBJ_VRAM1+0x1800, 8192);
                gCurrentPinballGame->unk394 = 136;
            }
            break;
        case DUSCLOPS_BOARD_STATE_5:
            sub_351A8();
            if (gCurrentPinballGame->scoreCounterAnimationEnabled)
            {
                gCurrentPinballGame->unk18 = 181;
            }
            if (gCurrentPinballGame->unk18 == 180)
            {
                gCurrentPinballGame->scoreCounterAnimationEnabled = TRUE;
                gCurrentPinballGame->scoreAddStepSize = 400000;
                gCurrentPinballGame->scoreAddedInFrame = BONUS_DUSKULL_COMPLETE_POINTS;
            }
            if (gCurrentPinballGame->unk18 < 240)
            {
                if (gCurrentPinballGame->unk18 == 20)
                {
                    m4aMPlayAllStop();
                    m4aSongNumStart(MUS_SUCCESS3);
                }
                gCurrentPinballGame->unk18++;
            }
            else
            {
                gCurrentPinballGame->unk18 = 0;
                gCurrentPinballGame->unk13 = DUSCLOPS_BOARD_STATE_6;
                gCurrentPinballGame->numCompletedBonusStages++;
            }

            break;
        case 6:
            sub_351A8();
            gCurrentPinballGame->unk386 = 1;
            break;
    }

    if (gCurrentPinballGame->unk294)
    {
        if (gCurrentPinballGame->eventTimer < 2)
        {
            if (!gMain.unkF)
            {
                m4aMPlayAllStop();
                m4aSongNumStart(MUS_END_OF_BALL3);
                gMain.unkF = gMain.unkF | 0x40;
            }
        }
    }

    if (gCurrentPinballGame->unk386)
        sub_350F0();

    sub_472E4();
}

void swap_duskull_entity_index(s16 index1, s16 index2)
{
    u8 temp397, temp39A, temp39D, temp3A0, temp3A3, temp3A6, temp3A9, temp3AC;
    u16 temp3B0, temp3B6, temp3BC;
    struct Vector16 temp3C4, temp3D0;

    temp397 = gCurrentPinballGame->minionSpriteVariant[index1];
    temp39A = gCurrentPinballGame->minionNextSpriteVariant[index1];
    temp39D = gCurrentPinballGame->minionOamIx[index1];
    temp3A0 = gCurrentPinballGame->minionState[index1];
    temp3A3 = gCurrentPinballGame->minionFramesetIx[index1];
    temp3A6 = gCurrentPinballGame->unk3A6[index1];
    temp3A9 = gCurrentPinballGame->unk3A9[index1];
    temp3AC = gCurrentPinballGame->unk3AC[index1];
    temp3B0 = gCurrentPinballGame->minionStateTimer[index1];
    temp3B6 = gCurrentPinballGame->minionTimeAlive[index1];
    temp3BC = gCurrentPinballGame->minionEscapeAtTime[index1];
    temp3C4.x = gCurrentPinballGame->minionLogicPosition[index1].x;
    temp3C4.y = gCurrentPinballGame->minionLogicPosition[index1].y;
    temp3D0.x = gCurrentPinballGame->minionColisionPosition[index1].x;
    temp3D0.y = gCurrentPinballGame->minionColisionPosition[index1].y;

    gCurrentPinballGame->minionSpriteVariant[index1] = gCurrentPinballGame->minionSpriteVariant[index2];
    gCurrentPinballGame->minionNextSpriteVariant[index1] = gCurrentPinballGame->minionNextSpriteVariant[index2];
    gCurrentPinballGame->minionOamIx[index1] = gCurrentPinballGame->minionOamIx[index2];
    gCurrentPinballGame->minionState[index1] = gCurrentPinballGame->minionState[index2];
    gCurrentPinballGame->minionFramesetIx[index1] = gCurrentPinballGame->minionFramesetIx[index2];
    gCurrentPinballGame->unk3A6[index1] = gCurrentPinballGame->unk3A6[index2];
    gCurrentPinballGame->unk3A9[index1] = gCurrentPinballGame->unk3A9[index2];
    gCurrentPinballGame->unk3AC[index1] = gCurrentPinballGame->unk3AC[index2];
    gCurrentPinballGame->minionStateTimer[index1] = gCurrentPinballGame->minionStateTimer[index2];
    gCurrentPinballGame->minionTimeAlive[index1] = gCurrentPinballGame->minionTimeAlive[index2];
    gCurrentPinballGame->minionEscapeAtTime[index1] = gCurrentPinballGame->minionEscapeAtTime[index2];
    gCurrentPinballGame->minionLogicPosition[index1].x = gCurrentPinballGame->minionLogicPosition[index2].x;
    gCurrentPinballGame->minionLogicPosition[index1].y = gCurrentPinballGame->minionLogicPosition[index2].y;
    gCurrentPinballGame->minionColisionPosition[index1].x = gCurrentPinballGame->minionColisionPosition[index2].x;
    gCurrentPinballGame->minionColisionPosition[index1].y = gCurrentPinballGame->minionColisionPosition[index2].y;

    gCurrentPinballGame->minionSpriteVariant[index2] = temp397;
    gCurrentPinballGame->minionNextSpriteVariant[index2] = temp39A;
    gCurrentPinballGame->minionOamIx[index2] = temp39D;
    gCurrentPinballGame->minionState[index2] = temp3A0;
    gCurrentPinballGame->minionFramesetIx[index2] = temp3A3;
    gCurrentPinballGame->unk3A6[index2] = temp3A6;
    gCurrentPinballGame->unk3A9[index2] = temp3A9;
    gCurrentPinballGame->unk3AC[index2] = temp3AC;
    gCurrentPinballGame->minionStateTimer[index2] = temp3B0;
    gCurrentPinballGame->minionTimeAlive[index2] = temp3B6;
    gCurrentPinballGame->minionEscapeAtTime[index2] = temp3BC;
    gCurrentPinballGame->minionLogicPosition[index2].x = temp3C4.x;
    gCurrentPinballGame->minionLogicPosition[index2].y = temp3C4.y;
    gCurrentPinballGame->minionColisionPosition[index2].x = temp3D0.x;
    gCurrentPinballGame->minionColisionPosition[index2].y = temp3D0.y;
}

void DuskullPhase_ProcessEntityLogic(void) {
    s16 i, j;
    bool32 r4 = TRUE;
    u16 oamIx = 0;
    u16 tileOffset = 0;

    // If target number of Duskulls spawned, check to see if all are removed before moving to next state
    if (gCurrentPinballGame->unk385 > DUSKULL_ALLOWED_TO_SPAWN)
    {
        for (i = 0; i < DUSKULL_CONCURRENT_MAX; i++)
        {
            if (gCurrentPinballGame->unk3A6[i])
                r4 = FALSE;
        }
        if (r4)
        {
            gCurrentPinballGame->unk13 = DUSCLOPS_BOARD_STATE_2_INIT_DUSCLOPS_PHASE;
            gMain.spriteGroups[7].available = FALSE;
            gMain.spriteGroups[8].available = FALSE;
            gMain.spriteGroups[9].available = FALSE;
        }
    }

    for (i = 0; i < DUSKULL_CONCURRENT_MAX; i++)
    {
        switch(gCurrentPinballGame->minionState[i])
        {
        case DUSKULL_ENTITY_STATE_SPAWN:
            if (gCurrentPinballGame->unk385 <= DUSKULL_ALLOWED_TO_SPAWN && 
                gCurrentPinballGame->minionActiveCount < 2)
            {
                gCurrentPinballGame->minionActiveCount++;
                gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_APPEARS; 
                gCurrentPinballGame->minionFramesetIx[i] = 0;
                gCurrentPinballGame->minionStateTimer[i] = 0;
                gCurrentPinballGame->minionLogicPosition[i].x = (Random() % 1400) - 700;
                gCurrentPinballGame->minionLogicPosition[i].y = (Random() % 9) * 80;
                gCurrentPinballGame->minionEscapeAtTime[i] = (Random() % 1000) + 200;
                gCurrentPinballGame->unk3A6[i] = 0;
                gCurrentPinballGame->unk3A9[i] = 0;
                oamIx = 4;
                tileOffset = 4; // Facing forward picture
                gCurrentPinballGame->minionTimeAlive[i] = 0;
                MPlayStart(&gMPlayInfo_SE1, &se_duskull_appear);

                //Check/swap Y index ordering, for proper sprite draw layering
                for (j = DUSKULL_CONCURRENT_MAX - 1; j > 0; j--)
                {
                    if (gCurrentPinballGame->minionLogicPosition[j].y > gCurrentPinballGame->minionLogicPosition[j-1].y)
                    {
                        swap_duskull_entity_index(j, j - 1);
                        j = DUSKULL_CONCURRENT_MAX;
                    }
                }
            }
            else
            {
                gCurrentPinballGame->minionLogicPosition[i].x = 0;
                gCurrentPinballGame->minionLogicPosition[i].y = 120;
                gCurrentPinballGame->unk3A6[i] = 0;
                Random();
            }
            break;
        case DUSKULL_ENTITY_STATE_APPEARS: //Spawn in, Wait and initial movement decision
            if (gCurrentPinballGame->minionStateTimer[i] < 20)
            {
                gCurrentPinballGame->minionStateTimer[i]++;
                gCurrentPinballGame->unk3A6[i] = (gCurrentPinballGame->minionStateTimer[i] % 4) / 2;
                oamIx = 4;
                tileOffset = 4;
                break;
            }
            else
            {
                if (gMain.systemFrameCount % 2)
                {
                    gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_MOVE_LEFT;
                    gCurrentPinballGame->minionFramesetIx[i] = DUSCLOPS_FRAMESET_MOVE_LEFT_START;
                }
                else
                {
                    gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_MOVE_RIGHT;
                    gCurrentPinballGame->minionFramesetIx[i] = DUSCLOPS_FRAMESET_MOVE_RIGHT_START;
                }

                gCurrentPinballGame->minionStateTimer[i] = 0;
                gCurrentPinballGame->unk3A6[i] = 1;
                gCurrentPinballGame->unk3A9[i] = 1;
                oamIx = DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][0];
                tileOffset = DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][2];
            }
            break;
        case DUSKULL_ENTITY_STATE_MOVE_LEFT:
            gCurrentPinballGame->minionTimeAlive[i]++;
            if (gCurrentPinballGame->minionLogicPosition[i].x > -800)
            {
                gCurrentPinballGame->minionLogicPosition[i].x -= 3; //Move left
                if (DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][1] > gCurrentPinballGame->minionStateTimer[i])
                {
                    gCurrentPinballGame->minionStateTimer[i]++;
                }
                else
                {
                    gCurrentPinballGame->minionStateTimer[i] = 0;
                    gCurrentPinballGame->minionFramesetIx[i]++;

                    //Animation frame reset
                    if (gCurrentPinballGame->minionFramesetIx[i] > DUSCLOPS_FRAMESET_MOVE_LEFT_END)
                        gCurrentPinballGame->minionFramesetIx[i] = DUSCLOPS_FRAMESET_MOVE_LEFT_START;
                }
            }
            else
            {
                if (DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][1] > gCurrentPinballGame->minionStateTimer[i])
                {
                    gCurrentPinballGame->minionStateTimer[i]++;
                }
                else
                {
                    gCurrentPinballGame->minionStateTimer[i] = 0;
                    gCurrentPinballGame->minionFramesetIx[i]++;

                    if (gCurrentPinballGame->minionFramesetIx[i] > 6) //Animation frame at neutral forward, continue with move right
                    {
                        gCurrentPinballGame->minionFramesetIx[i] = 7;
                        gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_MOVE_RIGHT;
                    }
                }
            }
            oamIx = DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][0];
            tileOffset = DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][2];
            break;
        case DUSKULL_ENTITY_STATE_MOVE_RIGHT:
            gCurrentPinballGame->minionTimeAlive[i]++;
            if (gCurrentPinballGame->minionLogicPosition[i].x < 800) //Dusclops x pos
            {
                gCurrentPinballGame->minionLogicPosition[i].x += 3;
                gCurrentPinballGame->minionLogicPosition[i].y += 0; // ! Dead code needed for matching
                if (DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][1] > gCurrentPinballGame->minionStateTimer[i])
                {
                    gCurrentPinballGame->minionStateTimer[i]++;
                }
                else
                {
                    gCurrentPinballGame->minionStateTimer[i] = 0; //Time since last decision
                    gCurrentPinballGame->minionFramesetIx[i]++; //Animation frame advance
                    if (gCurrentPinballGame->minionFramesetIx[i] > 10)
                        gCurrentPinballGame->minionFramesetIx[i] = 7;
                }
            }
            else
            {
                if (DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][1] > gCurrentPinballGame->minionStateTimer[i])
                {
                    gCurrentPinballGame->minionStateTimer[i]++; //Time since last decision
                }
                else
                {
                    gCurrentPinballGame->minionStateTimer[i] = 0; //Time since last decision
                    gCurrentPinballGame->minionFramesetIx[i]++; //Animation frame advance
                    if (gCurrentPinballGame->minionFramesetIx[i] > 13)
                    {
                        gCurrentPinballGame->minionFramesetIx[i] = 0; //Animation frame set
                        gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_MOVE_LEFT;
                    }
                }
            }
            oamIx = DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][0];
            tileOffset = DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][2];
            break;
        case DUSKULL_ENTITY_STATE_HIT:
            oamIx = DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][0];
            tileOffset = DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][2];
            gCurrentPinballGame->minionFramesetIx[i] = 14; //Animation frame
            gCurrentPinballGame->minionStateTimer[i] = 0; //Time since last decision
            gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_DYING;
            gCurrentPinballGame->unk3AC[i] = 0;
            gCurrentPinballGame->unk3A9[i] = 0;
            if (gCurrentPinballGame->minionActiveCount > 0)
                gCurrentPinballGame->minionActiveCount--; //Number of active duskull
            gCurrentPinballGame->scoreAddedInFrame = 100000;
            gCurrentPinballGame->unk385++; // Number hit
            m4aSongNumStart(SE_DUSKULL_DEATH_CRY); //Duskull Death cry
            playRumbleType(7);
            break;
        case DUSKULL_ENTITY_STATE_DYING:
            if (DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][1] > gCurrentPinballGame->minionStateTimer[i])
            {
                gCurrentPinballGame->minionStateTimer[i]++; //Time since last decision
            }
            else
            {
                gCurrentPinballGame->minionStateTimer[i] = 0; //Time since last decision
                gCurrentPinballGame->minionFramesetIx[i]++; //Animation frame advance
                if (gCurrentPinballGame->minionFramesetIx[i] > 15) //Animation frame
                {
                    gCurrentPinballGame->minionFramesetIx[i] = 15; //Animation frame
                    gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_CLEANUP;
                    gCurrentPinballGame->unk3A6[i] = 0;
                }
            }
            if (gCurrentPinballGame->minionFramesetIx[i] == 15) //Animation frame
                gCurrentPinballGame->unk3AC[i]++;
            oamIx = DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][0];
            tileOffset = DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][2];
            break;
        case DUSKULL_ENTITY_STATE_ESCAPE_WHILE_WALKING_LEFT:
            if (gCurrentPinballGame->minionStateTimer[i] < 6) //Time since last decision
            {
                gCurrentPinballGame->minionStateTimer[i]++; //Time since last decision
                oamIx = 3;
                tileOffset = 3;
            }
            else
            {
                gCurrentPinballGame->minionStateTimer[i] = 0; //Time since last decision
                gCurrentPinballGame->minionFramesetIx[i] = 18; //Animation frame
                gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_ESCAPE;
                gCurrentPinballGame->unk3A9[i] = 0;
                if (gCurrentPinballGame->minionActiveCount > 0)
                    gCurrentPinballGame->minionActiveCount--; //Number of active duskull
                oamIx = 3;
                tileOffset = 3;
                m4aSongNumStart(SE_DUSCLOPS_DEPART_INCOMPLETE);
            }
            break;
        case DUSKULL_ENTITY_STATE_ESCAPE_WHILE_WALKING_RIGHT:
            if (gCurrentPinballGame->minionStateTimer[i] < 6)
            {
                gCurrentPinballGame->minionStateTimer[i]++; //Time since last decision
                oamIx = 9;
                tileOffset = 3;
            }
            else
            {
                gCurrentPinballGame->minionStateTimer[i] = 0; //Time since last decision
                gCurrentPinballGame->minionFramesetIx[i] = 18; //Animation frame
                gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_ESCAPE;
                gCurrentPinballGame->unk3A9[i] = 0;
                if (gCurrentPinballGame->minionActiveCount > 0)
                    gCurrentPinballGame->minionActiveCount--; //Number of active duskull
                m4aSongNumStart(SE_DUSCLOPS_DEPART_INCOMPLETE);
                oamIx = 9;
                tileOffset = 3;
            }
            break;
        case DUSKULL_ENTITY_STATE_ESCAPE:
            if (DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][1] > gCurrentPinballGame->minionStateTimer[i])
            {
                gCurrentPinballGame->minionStateTimer[i]++; //Time since last decision
            }
            else
            {
                gCurrentPinballGame->minionStateTimer[i] = 0; //Time since last decision
                gCurrentPinballGame->minionFramesetIx[i]++; //Animation frame Advance
                if (gCurrentPinballGame->minionFramesetIx[i] > 25) //Animation frame
                {
                    gCurrentPinballGame->minionFramesetIx[i] = 25; //Animation frame
                    gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_CLEANUP;
                }
            }
            oamIx = DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][0];
            tileOffset = DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][2];
            break;
        case DUSKULL_ENTITY_STATE_CLEANUP:
            gCurrentPinballGame->unk3A6[i] = 0;
            gCurrentPinballGame->unk3A9[i] = 0;
            gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_SPAWN;
            oamIx = DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][0];
            tileOffset = DusclopsFramesetData[gCurrentPinballGame->minionFramesetIx[i]][2];
            break;
        }

        // Time alive > time before escape, && number hit < 18
        if (gCurrentPinballGame->minionTimeAlive[i] > gCurrentPinballGame->minionEscapeAtTime[i] &&
            gCurrentPinballGame->unk385 <= DUSKULL_ALLOWED_TO_SPAWN)
        {
            gCurrentPinballGame->minionTimeAlive[i] = 0;
            if (gCurrentPinballGame->minionState[i] == DUSKULL_ENTITY_STATE_MOVE_LEFT)
                gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_ESCAPE_WHILE_WALKING_LEFT; //Escape after moving left
            else
                gCurrentPinballGame->minionState[i] = DUSKULL_ENTITY_STATE_ESCAPE_WHILE_WALKING_RIGHT; //Escape after moving right

            gCurrentPinballGame->minionStateTimer[i] = 0;
        }

        gCurrentPinballGame->minionSpriteVariant[i] = gCurrentPinballGame->minionNextSpriteVariant[i];
        gCurrentPinballGame->minionNextSpriteVariant[i] = tileOffset;
        gCurrentPinballGame->minionOamIx[i] = oamIx;
        gCurrentPinballGame->minionColisionPosition[i].x = (gCurrentPinballGame->minionLogicPosition[i].x / 10) * 2 + 208;
        gCurrentPinballGame->minionColisionPosition[i].y = (gCurrentPinballGame->minionLogicPosition[i].y / 10) * 2 + 66;
    }
}

extern const u8 gDusclopsBoardDuskull_Gfx[];
extern const u16 gDuskullSpritesheetOam[][2][3];
void DuskullPhase_ProcessGraphics() {
    s16 i, animPiece;
    s16 oamIx;
    struct SpriteGroup *spriteGroup;
    struct OamDataSimple * oamData;
    u16 * dst;
    const u16 * src;

    for (i = 0; i < DUSKULL_CONCURRENT_MAX; i++)
    {
        s16 spriteVariant = gCurrentPinballGame->minionSpriteVariant[i];
        DmaCopy16(3, gDusclopsBoardDuskull_Gfx + spriteVariant * 0x280, OBJ_VRAM0 + 0x920 + i * 0x280, 0x280);
        oamIx = gCurrentPinballGame->minionOamIx[i];
        spriteGroup = &gMain_spriteGroups[7 + i];

        if (gCurrentPinballGame->unk3A6[i]) {
            s32 x = 0; // Scrub C to get the compiler to add before subtracting
            spriteGroup->baseX = gCurrentPinballGame->minionLogicPosition[i].x / 10 + 108 + x - gCurrentPinballGame->unk58;
            spriteGroup->baseY = gCurrentPinballGame->minionLogicPosition[i].y / 10 + 28 + x - gCurrentPinballGame->unk5A;
        } else {
            spriteGroup->baseX = 240;
            spriteGroup->baseY = 180;
        }

        if (spriteVariant == 6)
        {
            u16 scaleX;
            u16 scaleY;
            if (gCurrentPinballGame->unk3AC[i] <= 6) {
                scaleX = (gCurrentPinballGame->unk3AC[i] * 0x80) / 6 + 0x100;
                scaleY = ((6-gCurrentPinballGame->unk3AC[i]) * 0x80) / 6 + 0x80;
            } else {
                scaleX = ((24-gCurrentPinballGame->unk3AC[i]) * 0x170) / 18 + 0x10;
                scaleY = ((gCurrentPinballGame->unk3AC[i]-6) * 0x1C0) / 18 + 0x80;
            }
            SetMatrixScale(scaleX, scaleY, i + 2);
            spriteGroup->baseX -= 16;
            spriteGroup->baseY -= 16;

            for (animPiece = 0; animPiece < 2; animPiece++)
            {
                oamData = &spriteGroup->oam[animPiece];

                dst = (u16*)&gOamBuffer[oamData->oamId];
                src = gDuskullSpritesheetOam[oamIx][animPiece];
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;

                gOamBuffer[oamData->oamId].x += spriteGroup->baseX;
                gOamBuffer[oamData->oamId].y += spriteGroup->baseY;
                gOamBuffer[oamData->oamId].tileNum += i * 20;
                gOamBuffer[oamData->oamId].affineMode = ST_OAM_AFFINE_DOUBLE;
                gOamBuffer[oamData->oamId].matrixNum = i + 2;
            }
        }
        else
        {
            for (animPiece = 0; animPiece < 2; animPiece++)
            {
                oamData = &spriteGroup->oam[animPiece];
                dst = (u16*)&gOamBuffer[oamData->oamId];
                src = gDuskullSpritesheetOam[oamIx][animPiece];
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;

                gOamBuffer[oamData->oamId].x += spriteGroup->baseX;
                gOamBuffer[oamData->oamId].y += spriteGroup->baseY;
                gOamBuffer[oamData->oamId].tileNum += i * 20;
            }
        }
    }
}

void sub_34450(void)
{
    s16 r9;
    u16 available;
    struct OamDataSimple *oamSimple;
    struct SpriteGroup *spriteGroup;

    r9 = 0;
    spriteGroup = &gMain.spriteGroups[14];
    switch(gCurrentPinballGame->unk3DC)
    {
    case 0:
    {
        gCurrentPinballGame->unk3E8 = 880;
        gCurrentPinballGame->unk3EA = 300;
        gCurrentPinballGame->unk3DC = 1;
        gCurrentPinballGame->unk3E6 = 184;
        gCurrentPinballGame->unk3E2 = 21;
        r9 = 0;
        gCurrentPinballGame->unk294 = 1;
        break;
    }

    case 1:
    {
        if (gUnknown_086AE68E[gCurrentPinballGame->unk3E2][1] > gCurrentPinballGame->unk3E4)
            gCurrentPinballGame->unk3E4++;
        else
        {
            gCurrentPinballGame->unk3E4 = 0;
            gCurrentPinballGame->unk3E2++;

            if (gCurrentPinballGame->unk3E2 > 28)
            {
                gCurrentPinballGame->unk3E2 = 21;

                if (gCurrentPinballGame->unk3E0 <= 0)
                    gCurrentPinballGame->unk3E0++;
                else
                {
                    gCurrentPinballGame->unk3E0 = 0;
                    gCurrentPinballGame->unk3DC = 2;
                }
            }

            if (gCurrentPinballGame->unk3E2 == 23)
            {
                gCurrentPinballGame->unk129 = 0;
                gCurrentPinballGame->unk128 = 1;
                m4aSongNumStart(SE_DUSCLOPS_MOVE); //Dusclops entry; footstops
                playRumbleType(8);
            }

            if (gCurrentPinballGame->unk3E2 == 27)
            {
                gCurrentPinballGame->unk129 = 1;
                gCurrentPinballGame->unk128 = 1;
                m4aSongNumStart(SE_DUSCLOPS_MOVE); //Dusclops entry; footstops
                playRumbleType(8);

            }
        }

        r9 = 0;
        break;
    }
    case 2:
    {
        if (gCurrentPinballGame->unk3E4 <= 255)
        {
            r9 = gUnknown_08137D40[(gCurrentPinballGame->unk3E4 % 0x40) / 16];
            gCurrentPinballGame->unk3E4++;

            if (gCurrentPinballGame->unk3E4 == 256)
            {
                gCurrentPinballGame->unk3DC = 3;
                gCurrentPinballGame->unk3E4 = 0;

                if (gCurrentPinballGame->unk3E0 > 3)
                    gCurrentPinballGame->unk3E0 = 0;
                if (gCurrentPinballGame->unk3E0 <= 1)
                    gCurrentPinballGame->unk3E2 = 0;
                else
                    gCurrentPinballGame->unk3E2 = 7;
            }
        }

        if (gCurrentPinballGame->unk3E6 > 0)
        {
            if (gCurrentPinballGame->unk3E6 > 64)
                gCurrentPinballGame->unk3E6--;
            else
                gCurrentPinballGame->unk3E6 -= 2;

            if (gCurrentPinballGame->unk3E6 == 154)
                m4aSongNumStart(SE_DUSCLOPS_APPEAR); //Dusclops Appears
        }
        else
        {
            gCurrentPinballGame->boardEntityCollisionMode = DUSCLOPS_ENTITY_COLISION_MODE_DUSCLOPS;
            gCurrentPinballGame->unk294 = 2;
        }

        break;
    }
    case 3:
    {
        if (gUnknown_086AE68E[gCurrentPinballGame->unk3E2][1] > gCurrentPinballGame->unk3E4)
        {
            gCurrentPinballGame->unk3E4++;
        }
        else
        {
            gCurrentPinballGame->unk3E4 = 0;

            if (gCurrentPinballGame->unk3E0 <= 1)
            {
                gCurrentPinballGame->unk3E2++;

                if (gCurrentPinballGame->unk3E2 > 7)
                {
                    gCurrentPinballGame->unk3E2 = 0;
                    gCurrentPinballGame->unk3E0++;

                    if ((gCurrentPinballGame->unk3E0 & 1) == 0)
                    {
                        gCurrentPinballGame->unk3DC = 2;
                        gCurrentPinballGame->unk3E4 = 0;
                    }
                }
            }
            else if (--gCurrentPinballGame->unk3E2 < 0)
            {
                gCurrentPinballGame->unk3E0++;

                if ((gCurrentPinballGame->unk3E0 & 1) == 0)
                {
                    gCurrentPinballGame->unk3DC = 2;
                    gCurrentPinballGame->unk3E4 = 0;
                    gCurrentPinballGame->unk3E2 = 0;
                }
                else
                    gCurrentPinballGame->unk3E2 = 7;
            }

            if (gCurrentPinballGame->unk3E2 == 2)
            {
                gCurrentPinballGame->unk129 = 0;
                gCurrentPinballGame->unk128 = 1;
                m4aSongNumStart(SE_DUSCLOPS_MOVE); //Dusclops entry; footstops
                playRumbleType(8);
            }

            if (gCurrentPinballGame->unk3E2 == 6)
            {
                gCurrentPinballGame->unk129 = 1;
                gCurrentPinballGame->unk128 = 1;
                m4aSongNumStart(SE_DUSCLOPS_MOVE); //Dusclops entry; footstops
                playRumbleType(8);
            }
        }

        r9 = gUnknown_086AE68E[gCurrentPinballGame->unk3E2][0];

        if((gCurrentPinballGame->unk3E2  == 0) || (gCurrentPinballGame->unk3E2 == 4))
        {
            break;
        }

        if (gCurrentPinballGame->unk3E0 <= 1)
        {
            if (gCurrentPinballGame->unk3EA <= 583)
            {
                gCurrentPinballGame->unk3EA++;
                break;
            }

            if ((gCurrentPinballGame->unk3E2 % 4) != 0)
                break;

            gCurrentPinballGame->unk3DC = 2;
            gCurrentPinballGame->unk3E4 = 0;
            gCurrentPinballGame->unk3E2 = 0;
            gCurrentPinballGame->unk3E0 = 2;
            break;
        }

        if (gCurrentPinballGame->unk3EA > 300)
        {
            gCurrentPinballGame->unk3EA--;
            break;
        }

        if ((gCurrentPinballGame->unk3E2 % 4) != 0)
            break;

        gCurrentPinballGame->unk3DC = 2;
        gCurrentPinballGame->unk3E4 = 0;
        gCurrentPinballGame->unk3E2 = 0;
        gCurrentPinballGame->unk3E0 = 4;

        break;
    }
    case 4:
    {
        gCurrentPinballGame->unk3E4 = 0;
        gCurrentPinballGame->unk3E2 = 0;
        gCurrentPinballGame->unk3DC = 5;
        r9 = 7;

        m4aSongNumStart(SE_DUSCLOPS_HIT); //Dusclops hit
        gCurrentPinballGame->boardEntityCollisionMode = DUSCLOPS_ENTITY_COLISION_MODE_NONE;
        playRumbleType(7);
        break;
    }
    case 5:
    {
        if (gCurrentPinballGame->unk3E4 <= 27)
        {
            r9 = 7;
            gCurrentPinballGame->unk3E4++;
            break;
        }

        if (gCurrentPinballGame->unk385 <= 3)
        {
            gCurrentPinballGame->unk3E4 = 128;
            gCurrentPinballGame->unk3E2 = 0;
            gCurrentPinballGame->unk3DC = 2;
            gCurrentPinballGame->boardEntityCollisionMode = DUSCLOPS_ENTITY_COLISION_MODE_NONE;
            r9 = 7;
        }
        else
        {
            gCurrentPinballGame->unk3DC = 8;
            r9 = 7;
        }

        gCurrentPinballGame->unk385++;
        gCurrentPinballGame->scoreAddedInFrame = 300000;
        
        break;
    }
    case 6:
    {
        struct Vector16 tempVector;

        gCurrentPinballGame->unk3E2 = 9;
        gCurrentPinballGame->unk3E4 = 0;
        gCurrentPinballGame->unk3DC = 7;
        gCurrentPinballGame->unk5A6 = 0;
        r9 = 8;

        m4aSongNumStart(SE_DUSCLOPS_BALL_ABSORB); //Dusclops absorbs ball
        gCurrentPinballGame->unk288 = (gCurrentPinballGame->unk3E8 / 10) + 32;
        gCurrentPinballGame->unk28A = (gCurrentPinballGame->unk3EA / 10) + 36;

        tempVector.x = (gCurrentPinballGame->unk288 << 8) - gCurrentPinballGame->ball->positionQ8.x;
        tempVector.y = (gCurrentPinballGame->unk28A << 8) - gCurrentPinballGame->ball->positionQ8.y;

        gCurrentPinballGame->unk5AC = (tempVector.x * tempVector.x) + (tempVector.y * tempVector.y);
        gCurrentPinballGame->unk5AC = Sqrt(gCurrentPinballGame->unk5AC * 4) / 2;
        gCurrentPinballGame->unk5B0 = ArcTan2(-tempVector.x, tempVector.y);

        playRumbleType(13);
        break;
    }
    case 7:
    {
        if (gUnknown_086AE68E[gCurrentPinballGame->unk3E2][1] > gCurrentPinballGame->unk3E4)
            gCurrentPinballGame->unk3E4++;
        else
        {
            gCurrentPinballGame->unk3E4 = 0;
            gCurrentPinballGame->unk3E2++;

            if (gCurrentPinballGame->unk3E2 == 15)
            {
                gCurrentPinballGame->ball->velocity.x = (gMain.systemFrameCount % 2 * 300) + 65386;
                gCurrentPinballGame->ball->velocity.y = 300;
                gCurrentPinballGame->ball->unk0 = 0;
                m4aSongNumStart(SE_DUSCLOPS_BALL_LAUNCH); //Dusclops launch ball
                playRumbleType(8);
            }

            if (gCurrentPinballGame->unk3E2 == 16)
                gCurrentPinballGame->unk1F = 0;

            if (gCurrentPinballGame->unk3E2 > 16)
            {
                gCurrentPinballGame->unk3E4 = 128;
                gCurrentPinballGame->unk3E2 = 0;
                gCurrentPinballGame->unk3DC = 2;
            }
        }

        if (gCurrentPinballGame->ballSpeed != 0)
        {
            if ((gCurrentPinballGame->unk3E2 == 16) && (gCurrentPinballGame->unk3E4 > 4))
                gCurrentPinballGame->boardEntityCollisionMode = DUSCLOPS_ENTITY_COLISION_MODE_DUSCLOPS;
        }
        else
        {
            if ((gCurrentPinballGame->unk3E2 == 16) && (gCurrentPinballGame->unk3E4 != 0))
                gCurrentPinballGame->boardEntityCollisionMode = DUSCLOPS_ENTITY_COLISION_MODE_DUSCLOPS;
        }

        if (gCurrentPinballGame->unk5A6 <= 29)
        {
            s16 tr4 = 29 - gCurrentPinballGame->unk5A6;
            s32 sl;

            gCurrentPinballGame->unk5B0 -= ((tr4 * 8192) / 30) - 8192;
            gCurrentPinballGame->ball->unkA = gCurrentPinballGame->ball->unkA - 8192;

            sl = (gCurrentPinballGame->unk5AC * tr4) / 30;

            gCurrentPinballGame->ball->positionQ8.x = (gCurrentPinballGame->unk288 * 256) + ((Cos(gCurrentPinballGame->unk5B0) * sl) / 20000);

            gCurrentPinballGame->ball->positionQ8.y = (gCurrentPinballGame->unk28A * 256) - ((Sin(gCurrentPinballGame->unk5B0) * sl) / 20000);

            gCurrentPinballGame->ball->velocity.x = (gCurrentPinballGame->ball->velocity.x * 4) / 5;
            gCurrentPinballGame->ball->velocity.y = (gCurrentPinballGame->ball->velocity.y * 4) / 5;
        }

        if (gCurrentPinballGame->unk5A6 == 40)
        {
            gCurrentPinballGame->ball->unk0 = 1;
            gCurrentPinballGame->ball->velocity.x = 0;
            gCurrentPinballGame->ball->velocity.y = 0;
        }

        gCurrentPinballGame->unk5A6++;
        r9 = gUnknown_086AE68E[gCurrentPinballGame->unk3E2][0];

        break;
    }
    case 8:
    {
        gCurrentPinballGame->unk294 = 3;
        gMain.unkF = 128;

        if (gCurrentPinballGame->unk3E6 == 0)
        {
            gCurrentPinballGame->unk388 = 2;
            gCurrentPinballGame->unk392 = 0;
        }

        r9 = 15;

        if (gCurrentPinballGame->unk3E6 <= 183)
        {
            if (gCurrentPinballGame->unk3E6 <= 63)
                gCurrentPinballGame->unk3E6++;
            else
                gCurrentPinballGame->unk3E6 += 2;

            if (gCurrentPinballGame->unk3E6 == 30)
            {
                MPlayStart(&gMPlayInfo_SE1, &se_dusclops_appear);
            }
            break;
        }

        gMain.spriteGroups[13].available = FALSE;
        gMain.spriteGroups[14].available = FALSE;
        gMain.spriteGroups[12].available = FALSE;
        gCurrentPinballGame->unk13 = DUSCLOPS_BOARD_STATE_4;
        gCurrentPinballGame->unk18 = 0;
        break;
    }
    default:
        break;
    } //End switch

    DmaCopy16(3 , gDusclopsBoardDusclops_Gfx + r9 * 1024, (void *)OBJ_VRAM0+0x10a0, BG_SCREEN_SIZE);

    gCurrentPinballGame->unk3F0 = ((gCurrentPinballGame->unk3E8 / 10) * 2) + 16;
    gCurrentPinballGame->unk3F2 = ((gCurrentPinballGame->unk3EA / 10) * 2) + 16;

    if(spriteGroup->available != 0)
    {
        struct OamDataSimple *new_var;
        spriteGroup->baseX = (-gCurrentPinballGame->unk58) + (gCurrentPinballGame->unk3E8 / 10);
        spriteGroup->baseY = (-gCurrentPinballGame->unk5A) + (gCurrentPinballGame->unk3EA / 10);

        oamSimple = spriteGroup->oam;
        if (r9 == 7)
        {
            if (gCurrentPinballGame->unk3E4 <= 5)
                gOamBuffer[oamSimple->oamId].paletteNum = 4;
            else
                gOamBuffer[oamSimple->oamId].paletteNum = 3;
        }
        else
            gOamBuffer[oamSimple->oamId].paletteNum = 3;

        gOamBuffer[oamSimple->oamId].x = oamSimple->xOffset + spriteGroup->baseX;
        gOamBuffer[oamSimple->oamId].y = oamSimple->yOffset + spriteGroup->baseY;
    }

    spriteGroup = &gMain.spriteGroups[12];
    if (spriteGroup->available != 0)
    {
        if (gCurrentPinballGame->unk386 == 0)
        {
            u32 offY = 92;

            spriteGroup->baseX = -gCurrentPinballGame->unk58 + (gCurrentPinballGame->unk3E8 / 10);
            spriteGroup->baseY = -gCurrentPinballGame->unk5A + (gCurrentPinballGame->unk3EA / 10)
                + ((gCurrentPinballGame->unk3E6 / 2) - offY);
        }
        else
        {
            spriteGroup->baseX = 240;
            spriteGroup->baseY = 160;
        }

        {
            s16 i;
            u8 r1;
            r1 = gMain.systemFrameCount % 4;
            DmaCopy16(3 , gDusclopsBoardDusclopsAppearFx_Gfx + r1 / 2 * 0x600, (void *)OBJ_VRAM0 + 0x1aa0, 0xc00);

            for (i = 0; i < 2; i++)
            {
                oamSimple = &spriteGroup->oam[i];
                gOamBuffer[oamSimple->oamId].x = oamSimple->xOffset + spriteGroup->baseX;
                gOamBuffer[oamSimple->oamId].y = oamSimple->yOffset + spriteGroup->baseY;
            }
        }
    }

    spriteGroup = &gMain.spriteGroups[13];

    if (spriteGroup->available != 0)
    {
        s32 offX = 16;
        s32 offY = 20;
        spriteGroup->baseX = gCurrentPinballGame->unk3E8 / 10 + offX - gCurrentPinballGame->unk58;
        if (gCurrentPinballGame->unk3E2 >= 10 && gCurrentPinballGame->unk3E2 <= 12)
        {
            s16 r0;
            spriteGroup->baseY = ((gCurrentPinballGame->unk3EA / 10) + offY) - gCurrentPinballGame->unk5A;
            r0 = gCurrentPinballGame->unk5A6 % 24;
            if(r0 <= 10)
                r9 = 0;
            else if (r0 <= 17)
                r9 = 1;
            else
                r9 = 2;

            DmaCopy16(3 , gDusclopsBoardDusclopsBallGrabSwirl_Gfx + r9 * 0x200,(void *)OBJ_VRAM0+0x18a0, 0x200);
        }
        else
        {
            spriteGroup->baseY = 180;
        }

        oamSimple = spriteGroup->oam;
        gOamBuffer[oamSimple->oamId].x = oamSimple->xOffset + spriteGroup->baseX;
        gOamBuffer[oamSimple->oamId].y = oamSimple->yOffset + spriteGroup->baseY;
    }
}
