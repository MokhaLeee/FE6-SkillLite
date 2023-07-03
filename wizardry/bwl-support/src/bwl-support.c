#include "common-chax.h"
#include "unit.h"
#include "faction.h"
#include "support.h"
#include "action.h"
#include "eventinfo.h"

#include "null-bwl.h"

enum {
    MAX_SIMULTANEOUS_SUPPORT_COUNT = 5,
    SUPPORT_BONUSES_MAX_DISTANCE = 3,
};

extern int CONST_DATA sMaxExpLut[];
bool DoSupportAction(ProcPtr proc);

#ifdef CONFIG_BWL_SUPPORT

u8 *GetUnitBwlSupport(struct Unit *unit)
{
    struct NewBwl *bwl = GetNewBwlEntry(UNIT_PID(unit));
    if (!bwl)
        return NULL;

    return bwl->supports;
}

LYN_REPLACE_CHECK(ClearUnit);
void ClearUnit(struct Unit *unit)
{
    int i;
    u8 *supports;
    u8 id = unit->id;

    CpuFill16(0, unit, sizeof(struct Unit));

    supports = GetUnitBwlSupport(unit);
    if (supports) {
        for (i = 0; i < UNIT_SUPPORT_COUNT; i++)
            supports[i] = 0;
    }

    unit->id = id;
}

LYN_REPLACE_CHECK(UnitInitSupports);
void UnitInitSupports(struct Unit *unit)
{
    int i, count = GetUnitSupportCount(unit);
    u8 *supports = GetUnitBwlSupport(unit);

    if (!supports)
        return;

    for (i = 0; i < count; ++i)
        supports[i] = GetUnitInitialSupportExp(unit, i);
}

LYN_REPLACE_CHECK(GetUnitLeaderPid);
int GetUnitLeaderPid(struct Unit *unit)
{
    u8 *supports = GetUnitBwlSupport(unit);
    if (!supports)
        return 0;

    if (UNIT_FACTION(unit) == FACTION_BLUE)
        return 0;

    return supports[UNIT_SUPPORT_COUNT - 1];
}

/* LYN_REPLACE_CHECK(SetUnitLeaderPid); */
/* hack in function: CreateUnit */
void _SetUnitLeaderPid(struct Unit * unit, int pid)
{
    u8 *supports = GetUnitBwlSupport(unit);
    if (!supports)
        return;

    supports[UNIT_SUPPORT_COUNT - 1] = pid;
}

LYN_REPLACE_CHECK(GetUnitSupportLevel);
int GetUnitSupportLevel(struct Unit * unit, int num)
{
    u8 *supports;
    supports = GetUnitBwlSupport(unit);
    if (!supports)
        return SUPPORT_LEVEL_NONE;

    int exp = supports[num];

    if (exp >= SUPPORT_EXP_A)
        return SUPPORT_LEVEL_A;

    if (exp >= SUPPORT_EXP_B)
        return SUPPORT_LEVEL_B;

    if (exp >= SUPPORT_EXP_C)
        return SUPPORT_LEVEL_C;

    return SUPPORT_LEVEL_NONE;
}

LYN_REPLACE_CHECK(UnitGainSupportExp);
void UnitGainSupportExp(struct Unit *unit, int num)
{
    u8 *supports;
    supports = GetUnitBwlSupport(unit);
    if (!supports)
        return;

    if (unit->pinfo->support_info) {
        int gain = unit->pinfo->support_info->exp_growth[num];
        int exp = supports[num];
        int maxExp = sMaxExpLut[GetUnitSupportLevel(unit, num)];

        if (exp + gain > maxExp)
            gain = maxExp - exp;

        supports[num] = exp + gain;
        gPlaySt.support_gain += gain;
    }
}

LYN_REPLACE_CHECK(UnitGainSupportLevel);
void UnitGainSupportLevel(struct Unit *unit, int num)
{
    u8 *supports;
    supports = GetUnitBwlSupport(unit);
    if (!supports)
        return;

    supports[num]++;
    gPlaySt.support_gain++;
}

LYN_REPLACE_CHECK(CanUnitSupportNow);
bool CanUnitSupportNow(struct Unit *unit, int num)
{
    int exp, maxExp;
    u8 *supports;

    if (gPlaySt.flags & PLAY_FLAG_COMPLETE)
        return FALSE;

    if (gPlaySt.flags & PLAY_FLAG_TUTORIAL)
        return FALSE;

    if (GetUnitTotalSupportLevel(unit) >= MAX_SIMULTANEOUS_SUPPORT_COUNT)
        return FALSE;

    if (GetUnitTotalSupportLevel(GetUnitSupportUnit(unit, num)) >= MAX_SIMULTANEOUS_SUPPORT_COUNT)
        return FALSE;
    
    supports = GetUnitBwlSupport(unit);
    if (!supports)
        return FALSE;

    exp    = supports[num];
    maxExp = sMaxExpLut[GetUnitSupportLevel(unit, num)];

    if (exp == SUPPORT_EXP_A)
        return FALSE;

    return (exp == maxExp) ? TRUE : FALSE;
}

LYN_REPLACE_CHECK(ClearUnitSupports);
void ClearUnitSupports(struct Unit *unit)
{
    int i;
    u8 *supports;

    for (i = 0; i < GetUnitSupportCount(unit); ++i) {
        struct Unit * other = GetUnitSupportUnit(unit, i);

        if (!other)
            continue;
        
        supports = GetUnitBwlSupport(other);
        if (supports)
            supports[GetUnitSupportNumByPid(other, unit->pinfo->id)] = 0;

        supports = GetUnitBwlSupport(unit);
        if (supports)
            supports[i] = 0;
    }
}

LYN_REPLACE_CHECK(DoSupportAction);
bool DoSupportAction(ProcPtr proc)
{
    int expA, expB;

    struct Unit * target = GetUnit(gAction.target);

    int numA = GetUnitSupportNumByPid(gActiveUnit, target->pinfo->id);
    int numB = GetUnitSupportNumByPid(target, gActiveUnit->pinfo->id);

    u8 * supportsAct = GetUnitBwlSupport(gActiveUnit);
    u8 * supportsTar = GetUnitBwlSupport(target);

    if (!CanUnitSupportNow(target, numB))
    {
    }

    UnitGainSupportLevel(gActiveUnit, numA);
    UnitGainSupportLevel(target, numB);

    StartAvailableSupportEvent(gActiveUnit->pinfo->id, target->pinfo->id, GetUnitSupportLevel(gActiveUnit, numA));

    expA = 0;
    if (supportsAct)
        expA = gActiveUnit->supports[numA];

    expB = 0;
    if (supportsTar)
        expB = target->supports[numB];

    if (expA != expB) {
        if (expA > expB)
            if (supportsTar)
                supportsTar[numB] = expA;

        if (expA < expB)
            if (supportsAct)
                supportsAct[numA] = expB;
    }

    return FALSE;
}

#endif /* CONFIG_BWL_SUPPORT */
