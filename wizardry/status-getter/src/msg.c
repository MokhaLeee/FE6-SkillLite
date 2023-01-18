#include "common-chax.h"
#include "unit.h"
#include "item.h"

LYN_REPLACE_CHECK(GetUnitMaxHp);
int GetUnitMaxHp(struct Unit *unit)
{
    int status;

    status = unit->max_hp;
    status += GetItemHpBonus(GetUnitEquippedWeapon(unit));

    return status > 0 ? status : 0;
}

LYN_REPLACE_CHECK(GetUnitPower);
int GetUnitPower(struct Unit *unit)
{
    int status;

    status = unit->pow;
    status += GetItemPowBonus(GetUnitEquippedWeapon(unit));

    return status > 0 ? status : 0;
}

LYN_REPLACE_CHECK(GetUnitSkill);
int GetUnitSkill(struct Unit *unit)
{
    int status;

    status = unit->flags & UNIT_FLAG_RESCUING ? unit->skl / 2 : unit->skl;
    status += GetItemSklBonus(GetUnitEquippedWeapon(unit));

    return status > 0 ? status : 0;
}

LYN_REPLACE_CHECK(GetUnitSpeed);
int GetUnitSpeed(struct Unit *unit)
{
    int status;

    status = unit->flags & UNIT_FLAG_RESCUING ? unit->spd / 2 : unit->spd;
    status += GetItemSpdBonus(GetUnitEquippedWeapon(unit));

    return status > 0 ? status : 0;
}

LYN_REPLACE_CHECK(GetUnitDefense);
int GetUnitDefense(struct Unit *unit)
{
    int status;

    status = unit->def;
    status += GetItemDefBonus(GetUnitEquippedWeapon(unit));

    return status > 0 ? status : 0;
}

LYN_REPLACE_CHECK(GetUnitResistance);
int GetUnitResistance(struct Unit *unit)
{
    int status;

    status = unit->res;
    status += GetItemResBonus(GetUnitEquippedWeapon(unit));
    status += unit->barrier;
    
    return status > 0 ? status : 0;
}

LYN_REPLACE_CHECK(GetUnitLuck);
int GetUnitLuck(struct Unit *unit)
{
    int status;

    status = unit->lck;
    status += GetItemLckBonus(GetUnitEquippedWeapon(unit));

    return status > 0 ? status : 0;
}
