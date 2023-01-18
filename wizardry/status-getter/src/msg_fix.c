#include "common-chax.h"
#include "unit.h"
#include "faction.h"
#include "action.h"
#include "trap.h"

LYN_REPLACE_CHECK(SetUnitHp);
void SetUnitHp(struct Unit *unit, int hp)
{
    unit->hp = hp;

    if (unit->hp > GetUnitMaxHp(unit))
        unit->hp = GetUnitMaxHp(unit);
}

LYN_REPLACE_CHECK(AddUnitHp);
void AddUnitHp(struct Unit *unit, int amount)
{
    int hp = unit->hp;

    hp += amount;

    if (hp > GetUnitMaxHp(unit))
        hp = GetUnitMaxHp(unit);

    if (hp < 0)
        hp = 0;

    unit->hp = hp;
}

LYN_REPLACE_CHECK(CreateUnit);
struct Unit *CreateUnit(struct UnitInfo const *info)
{
    struct Unit *unit;

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
    
    default:
        return NULL;
    }

    if (!unit)
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

            SetUnitLeaderPid(unit, info->pid_lead);
        }
    }

    func_fe6_08017764(unit);
    UnitInitSupports(unit);

    UnitCheckStatOverflow(unit);

    unit->hp = GetUnitMaxHp(unit);

    return unit;
}

LYN_REPLACE_CHECK(UnitApplyBonusLevels);
void UnitApplyBonusLevels(struct Unit *unit, int levelCount)
{
    UnitAutolevelCore(unit, unit->jinfo->id, levelCount);
    UnitCheckStatOverflow(unit);

    unit->hp = GetUnitMaxHp(unit);
}

LYN_REPLACE_CHECK(GetUnitMagRange);
int GetUnitMagRange(struct Unit *unit)
{
    return 5 + GetUnitPower(unit) / 2;
}
