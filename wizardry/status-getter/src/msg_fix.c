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
