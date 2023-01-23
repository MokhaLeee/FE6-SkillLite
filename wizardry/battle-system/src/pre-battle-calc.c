#include "common-chax.h"
#include "unit.h"
#include "item.h"
#include "battle.h"

void _ComputeBattleUnitDodgeRate(struct BattleUnit *bu);
void InitBattleUnitStatus(struct BattleUnit *bu);

LYN_REPLACE_CHECK(ComputeBattleUnitStats);
void ComputeBattleUnitStats(struct BattleUnit *attacker, struct BattleUnit *defender)
{
    InitBattleUnitStatus(attacker);
    ComputeBattleUnitDefense(attacker, defender);
    ComputeBattleUnitAttack(attacker, defender);
    ComputeBattleUnitSpeed(attacker);
    ComputeBattleUnitHitRate(attacker);
    ComputeBattleUnitAvoidRate(attacker);
    ComputeBattleUnitCritRate(attacker);
    _ComputeBattleUnitDodgeRate(attacker);
    ComputeBattleUnitSupportBonuses(attacker, defender);
}

void InitBattleUnitStatus(struct BattleUnit *bu)
{
    bu->battle_attack = 0;
    bu->battle_defense = 0;
    bu->battle_speed = 0;
    bu->battle_hit = 0;
    bu->battle_avoid = 0;
    bu->battle_crit = 0;
    bu->battle_dodge = 0;
}

LYN_REPLACE_CHECK(ComputeBattleUnitDefense);
void ComputeBattleUnitDefense(struct BattleUnit *attacker, struct BattleUnit *defender)
{
    int status;
    
    status = GetItemAttributes(defender->weapon) & ITEM_ATTR_MAGIC
           ? attacker->unit.res
           : attacker->unit.def;

    status += GetItemAttributes(defender->weapon) & ITEM_ATTR_MAGIC
            ? attacker->terrain_resistance
            : attacker->terrain_defense;

    LIMIT_AREA(status, 0, BATTLE_MAX_STATUS);
    attacker->battle_defense = status;
}

LYN_REPLACE_CHECK(ComputeBattleUnitBaseDefense);
void ComputeBattleUnitBaseDefense(struct BattleUnit *bu)
{
    int status;

    status = bu->unit.def;
    status = status + bu->terrain_defense;

    LIMIT_AREA(status, 0, BATTLE_MAX_STATUS);
    bu->battle_defense = status;
}

LYN_REPLACE_CHECK(ComputeBattleUnitAttack);
void ComputeBattleUnitAttack(struct BattleUnit *attacker, struct BattleUnit *defender)
{
    int status;

    status = GetItemMight(attacker->weapon) + attacker->advantage_bonus_damage;

    if (IsItemEffectiveAgainst(attacker->weapon, &defender->unit) == TRUE)
        status *= 3;

    status += attacker->unit.pow;

    LIMIT_AREA(status, 0, BATTLE_MAX_STATUS);
    attacker->battle_attack = status;
}

LYN_REPLACE_CHECK(ComputeBattleUnitSpeed);
void ComputeBattleUnitSpeed(struct BattleUnit *attacker)
{
    int status, weight = GetItemWeight(attacker->weapon_before);

    weight -= attacker->unit.bonus_con;

    if (weight < 0)
        weight = 0;

    status = attacker->unit.spd - weight;

    LIMIT_AREA(status, 0, BATTLE_MAX_STATUS);
    attacker->battle_speed = status;
}

LYN_REPLACE_CHECK(ComputeBattleUnitHitRate);
void ComputeBattleUnitHitRate(struct BattleUnit *attacker)
{
    int status;

    status = attacker->unit.skl * 2;
    status = status + GetItemHit(attacker->weapon);
    status = status + attacker->unit.lck / 2;
    status = status + attacker->advantage_bonus_hit;

    LIMIT_AREA(status, 0, BATTLE_MAX_STATUS);
    attacker->battle_hit = status;
}

LYN_REPLACE_CHECK(ComputeBattleUnitAvoidRate);
void ComputeBattleUnitAvoidRate(struct BattleUnit * attacker)
{
    int status;

    status = attacker->battle_speed * 2;
    status = status + attacker->terrain_avoid;
    status = status + attacker->unit.lck;

    LIMIT_AREA(status, 0, BATTLE_MAX_STATUS);
    attacker->battle_avoid = status;
}

LYN_REPLACE_CHECK(ComputeBattleUnitCritRate);
void ComputeBattleUnitCritRate(struct BattleUnit *attacker)
{
    int status;

    status = GetItemCrit(attacker->weapon);
    status = status + attacker->unit.skl / 2;

    if (UNIT_ATTRIBUTES(&attacker->unit) & UNIT_ATTR_CRITBONUS)
        status += 30;

    LIMIT_AREA(status, 0, BATTLE_MAX_STATUS);
    attacker->battle_crit = status;
}

/* No enough space for lyn-jump ... */
void _ComputeBattleUnitDodgeRate(struct BattleUnit *attacker)
{
    int status;

    status = attacker->unit.lck;

    LIMIT_AREA(status, 0, BATTLE_MAX_STATUS);
    attacker->battle_dodge = status;
}
