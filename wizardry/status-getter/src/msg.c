#include "common-chax.h"
#include "unit.h"
#include "item.h"
#include "skill-system.h"

typedef int (*const msg_func)(struct Unit *unit, int old_status);
extern msg_func ModularHpGetter[],  ModularPowGetter[], ModularMagGetter[], ModularSklGetter[], ModularSpdGetter[], \
                ModularLckGetter[], ModularDefGetter[], ModularResGetter[], ModularMovGetter[];

int msg_test_func(struct Unit *unit, int old_status)
{
    return old_status + 1;
}

LYN_REPLACE_CHECK(GetUnitMaxHp);
int GetUnitMaxHp(struct Unit *unit)
{
    int status;
    msg_func *it;

    /* Internal modular */
    status = unit->max_hp;
    status += GetItemHpBonus(GetUnitEquippedWeapon(unit));
    status += SkillTester(unit, SKILLID_HpBonus) ? 5 : 0;

    /* External modular */
    for (it = ModularHpGetter; *it; it++)
        status = (*it)(unit, status);

    LIMIT_AREA(status, 0, UNIT_MAX_STATUS);
    return status;
}

LYN_REPLACE_CHECK(GetUnitPower);
int GetUnitPower(struct Unit *unit)
{
    int status;
    msg_func *it;

    /* Internal modular */
    status = unit->pow;
    status += GetItemPowBonus(GetUnitEquippedWeapon(unit));
    status += SkillTester(unit, SKILLID_StrBonus) ? 2 : 0;

    /* External modular */
    for (it = ModularPowGetter; *it; it++)
        status = (*it)(unit, status);

    LIMIT_AREA(status, 0, UNIT_MAX_STATUS);
    return status;
}

LYN_REPLACE_CHECK(GetUnitSkill);
int GetUnitSkill(struct Unit *unit)
{
    int status;
    msg_func *it;

    /* Internal modular */
    status = unit->flags & UNIT_FLAG_RESCUING ? unit->skl / 2 : unit->skl;
    status += GetItemSklBonus(GetUnitEquippedWeapon(unit));
    status += SkillTester(unit, SKILLID_SklBonus) ? 2 : 0;

    /* External modular */
    for (it = ModularSklGetter; *it; it++)
        status = (*it)(unit, status);

    LIMIT_AREA(status, 0, UNIT_MAX_STATUS);
    return status;
}

LYN_REPLACE_CHECK(GetUnitSpeed);
int GetUnitSpeed(struct Unit *unit)
{
    int status;
    msg_func *it;

    /* Internal modular */
    status = unit->flags & UNIT_FLAG_RESCUING ? unit->spd / 2 : unit->spd;
    status += GetItemSpdBonus(GetUnitEquippedWeapon(unit));
    status += SkillTester(unit, SKILLID_SpdBonus) ? 2 : 0;

    /* External modular */
    for (it = ModularSpdGetter; *it; it++)
        status = (*it)(unit, status);

    LIMIT_AREA(status, 0, UNIT_MAX_STATUS);
    return status;
}

LYN_REPLACE_CHECK(GetUnitDefense);
int GetUnitDefense(struct Unit *unit)
{
    int status;
    msg_func *it;

    /* Internal modular */
    status = unit->def;
    status += GetItemDefBonus(GetUnitEquippedWeapon(unit));
    status += SkillTester(unit, SKILLID_DefBonus) ? 2 : 0;

    /* External modular */
    for (it = ModularDefGetter; *it; it++)
        status = (*it)(unit, status);

    LIMIT_AREA(status, 0, UNIT_MAX_STATUS);
    return status;
}

LYN_REPLACE_CHECK(GetUnitResistance);
int GetUnitResistance(struct Unit *unit)
{
    int status;
    msg_func *it;

    /* Internal modular */
    status = unit->res;
    status += GetItemResBonus(GetUnitEquippedWeapon(unit));
    status += SkillTester(unit, SKILLID_ResBonus) ? 2 : 0;
    status += unit->barrier;

    /* External modular */
    for (it = ModularResGetter; *it; it++)
        status = (*it)(unit, status);

    LIMIT_AREA(status, 0, UNIT_MAX_STATUS);
    return status;
}

LYN_REPLACE_CHECK(GetUnitLuck);
int GetUnitLuck(struct Unit *unit)
{
    int status;
    msg_func *it;

    /* Internal modular */
    status = unit->lck;
    status += GetItemLckBonus(GetUnitEquippedWeapon(unit));
    status += SkillTester(unit, SKILLID_LckBonus) ? 2 : 0;

    /* External modular */
    for (it = ModularLckGetter; *it; it++)
        status = (*it)(unit, status);

    LIMIT_AREA(status, 0, UNIT_MAX_STATUS);
    return status;
}

int GetUnitMove(struct Unit *unit)
{
    int status;
    msg_func *it;

    /* Internal modular */
    status = UNIT_CON_BASE(unit);
    status += unit->bonus_mov;
    status += SkillTester(unit, SKILLID_MovBonus) ? 2 : 0;

    /* External modular */
    for (it = ModularMovGetter; *it; it++)
        status = (*it)(unit, status);

    LIMIT_AREA(status, 0, UNIT_MAX_STATUS);
    return status;
}
