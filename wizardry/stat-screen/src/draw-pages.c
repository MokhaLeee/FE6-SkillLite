#include "common-chax.h"
#include "hardware.h"
#include "statscreen.h"
#include "icon.h"
#include "armfunc.h"
#include "unit.h"
#include "util.h"
#include "support.h"
#include "constants/videoalloc_global.h"

#include "skill-system.h"

extern struct StatScreenTextInfo const gStatScreenPersonalInfoLabelsInfo[];

void PutStatScreenPersonalInfoPage()
{
    Decompress(gUnk_08307D58, gBuf);
    TmApplyTsa(gUiTmScratchB, gBuf, TILEREF(BGCHR_WINDOWFRAME, BGPAL_WINDOWFRAME));

    PutStatScreenText(gStatScreenPersonalInfoLabelsInfo);

    /* display strength/magic labels */
    if (UnitKnowsMagic(gStatScreenSt.unit)) {
        /* magic */
        PutDrawText(gStatScreenSt.text + STATSCREEN_TEXT_POW,
            gUiTmScratchB + TM_OFFSET(1, 1),
            TEXT_COLOR_SYSTEM_GOLD, 0, 0,
            TEXT("魔力", "Mag"));
    } else {
        /* strength */
        PutDrawText(gStatScreenSt.text + STATSCREEN_TEXT_POW,
            gUiTmScratchA + TM_OFFSET(1, 1),
            TEXT_COLOR_SYSTEM_GOLD, 4, 0,
            TEXT("力", "Str"));
    }

    /* display strength/magic stat value */
    PutStatScreenStatWithBar(0, 5, 1,
        gStatScreenSt.unit->pow,
        GetUnitPower(gStatScreenSt.unit),
        UNIT_POW_CAP(gStatScreenSt.unit));

    /* display skill stat value */
    PutStatScreenStatWithBar(1, 5, 3,
        gStatScreenSt.unit->flags & UNIT_FLAG_RESCUING
            ? gStatScreenSt.unit->skl / 2 : gStatScreenSt.unit->skl,
        GetUnitSkill(gStatScreenSt.unit),
        gStatScreenSt.unit->flags & UNIT_FLAG_RESCUING
            ? UNIT_SKL_CAP(gStatScreenSt.unit) / 2 : UNIT_SKL_CAP(gStatScreenSt.unit));

    /* display speed stat value */
    PutStatScreenStatWithBar(2, 5, 5,
        gStatScreenSt.unit->flags & UNIT_FLAG_RESCUING
            ? gStatScreenSt.unit->spd/2 : gStatScreenSt.unit->spd,
        GetUnitSpeed(gStatScreenSt.unit),
        gStatScreenSt.unit->flags & UNIT_FLAG_RESCUING
            ? UNIT_SPD_CAP(gStatScreenSt.unit) / 2 : UNIT_SPD_CAP(gStatScreenSt.unit));

    /* display luck stat value */
    PutStatScreenStatWithBar(3, 5, 7,
        gStatScreenSt.unit->lck,
        GetUnitLuck(gStatScreenSt.unit),
        UNIT_LCK_CAP(gStatScreenSt.unit));

    /* display defense stat value */
    PutStatScreenStatWithBar(4, 5, 9,
        gStatScreenSt.unit->def,
        GetUnitDefense(gStatScreenSt.unit),
        UNIT_DEF_CAP(gStatScreenSt.unit));

    /* display resistance stat value */
    PutStatScreenStatWithBar(5, 5, 11,
        gStatScreenSt.unit->res,
        GetUnitResistance(gStatScreenSt.unit),
        UNIT_RES_CAP(gStatScreenSt.unit));

    /* display movement stat value */
    PutStatScreenStatWithBar(6, 13, 1,
        UNIT_MOV_BASE(gStatScreenSt.unit),
        UNIT_MOV(gStatScreenSt.unit),
        UNIT_MOV_CAP(gStatScreenSt.unit));

    /* display constitution stat value */
    PutStatScreenStatWithBar(7, 13, 3,
        UNIT_CON_BASE(gStatScreenSt.unit),
        UNIT_CON(gStatScreenSt.unit),
        UNIT_CON_CAP(gStatScreenSt.unit));

    /* display unit aid */
    PutNumber(gUiTmScratchA + TM_OFFSET(13, 5), TEXT_COLOR_SYSTEM_BLUE,
        GetUnitAid(gStatScreenSt.unit));

    /* display unit aid icon */
    PutIcon(gUiTmScratchA + TM_OFFSET(14, 5),
        GetAidIconFromAttributes(UNIT_ATTRIBUTES(gStatScreenSt.unit)),
        TILEREF(0, BGPAL_ICONS + 1));

    /* display unit rescue name */
    Text_InsertDrawString(gStatScreenSt.text + STATSCREEN_TEXT_RESCUE,
        24, TEXT_COLOR_SYSTEM_BLUE,
        GetUnitRescueName(gStatScreenSt.unit));

    /* display status name */
    Text_InsertDrawString(gStatScreenSt.text + STATSCREEN_TEXT_STATUS,
        24, TEXT_COLOR_SYSTEM_BLUE,
        GetUnitStatusName(gStatScreenSt.unit));

    /* display status turns */
    if (gStatScreenSt.unit->status != UNIT_STATUS_NONE)
        PutNumberSmall(gUiTmScratchA + TM_OFFSET(16, 11),
            TEXT_COLOR_SYSTEM_WHITE,
            gStatScreenSt.unit->status_duration);

    /* display affininity icon and name */
    PutIcon(gUiTmScratchA + TM_OFFSET(12, 9),
        GetUnitAffinityIcon(gStatScreenSt.unit),
        TILEREF(0, BGPAL_ICONS + 1));

    Text_InsertDrawString(gStatScreenSt.text + STATSCREEN_TEXT_AFFINITY,
        40, TEXT_COLOR_SYSTEM_BLUE, GetAffinityName(gStatScreenSt.unit->pinfo->affinity));
    
    DrawSkillPage();
}
