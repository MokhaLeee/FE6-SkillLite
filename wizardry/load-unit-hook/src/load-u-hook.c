#include "common-chax.h"
#include "unit.h"
#include "trap.h"
#include "faction.h"

typedef void (*lu_func)(struct Unit *unit);
extern lu_func OnLoadUnitFuncList[];

/* bwl-support */
void _SetUnitLeaderPid(struct Unit * unit, int pid);

struct Unit *CreateUnit(struct UnitInfo const *info)
{
    struct Unit *unit = NULL;
    lu_func *it;

    switch (info->faction_id) {
    case FACTION_ID_BLUE:
        unit = GetFreeUnit(FACTION_BLUE);
        break;

    case FACTION_ID_RED:
        unit = GetFreeUnit(FACTION_RED);
        break;

    case FACTION_ID_GREEN:
        unit = GetFreeUnit(FACTION_GREEN);
        break;
    }

    if (unit == NULL)
        return NULL;

    ClearUnit(unit);

    UnitInitFromInfo(unit, info);
    UnitInitStats(unit, unit->pinfo);

    UnitHideIfUnderRoof(unit);

    if (info->autolevel) {
        if (UNIT_FACTION(unit) == FACTION_BLUE) {
            UnitAutolevelPlayer(unit);
            UnitAutolevelWeaponExp(unit, info);
        } else {
            UnitAutolevel(unit);
            UnitAutolevelWeaponExp(unit, info);

            _SetUnitLeaderPid(unit, info->pid_lead);
        }
    }

    func_fe6_08017764(unit);
    UnitInitSupports(unit);

    UnitCheckStatOverflow(unit);

    unit->hp = GetUnitMaxHp(unit);

    for (it = OnLoadUnitFuncList; *it; it++)
        (*it)(unit);

    return unit;
}

void UnitInitStats(struct Unit *unit, struct PInfo const *pinfo)
{
    int i;

    unit->max_hp = pinfo->base_hp + unit->jinfo->base_hp;
    unit->pow = pinfo->base_pow + unit->jinfo->base_pow;
    unit->skl = pinfo->base_skl + unit->jinfo->base_skl;
    unit->spd = pinfo->base_spd + unit->jinfo->base_spd;
    unit->def = pinfo->base_def + unit->jinfo->base_def;
    unit->res = pinfo->base_res + unit->jinfo->base_res;
    unit->lck = pinfo->base_lck;

    unit->bonus_con = 0;

    for (i = 0; i < UNIT_WEAPON_EXP_COUNT; ++i) {
        unit->wexp[i] = unit->jinfo->wexp[i];

        if (unit->pinfo->wexp[i] != 0)
            unit->wexp[i] = unit->pinfo->wexp[i];
    }

    if (UNIT_FACTION(unit) == FACTION_BLUE && (unit->level != UNIT_LEVEL_MAX))
        unit->exp = 0;
    else
        unit->exp = 0xFF;
}
