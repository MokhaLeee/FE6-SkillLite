#include "common-chax.h"
#include "unit.h"
#include "item.h"
#include "battle.h"

typedef void (*const mbc_loopfunc)(struct BattleUnit *buA, struct BattleUnit *buB);
typedef void (*const pbc_loopfunc)(struct BattleUnit *buA, struct BattleUnit *buB);
typedef int (*const pbc_func)(struct BattleUnit *buA, struct BattleUnit *buB, int old_status);

extern mbc_loopfunc ModularMainBuCalcator[];
extern pbc_loopfunc ModularPreBuCalcator[];
extern pbc_func ModularBuAtkGetter[], ModularBuDefGetter[], ModularBuSpdGetter[], ModularBuHitGetter[], \
                ModularBuAvoGetter[], ModularBuCrtGetter[], ModularBuDgeGetter[];

LYN_REPLACE_CHECK(BattleGenerate);
void BattleGenerate(struct Unit *instigator, struct Unit *target)
{
    mbc_loopfunc *it;

    ComputeBattleUnitStats(&gBattleUnitA, &gBattleUnitB);
    ComputeBattleUnitStats(&gBattleUnitB, &gBattleUnitA);

    ComputeBattleUnitEffectiveStats(&gBattleUnitA, &gBattleUnitB);
    ComputeBattleUnitEffectiveStats(&gBattleUnitB, &gBattleUnitA);

    /* Internal modular */

    
    /* External modular */
    for (it = ModularMainBuCalcator; *it; it++)
        (*it)(&gBattleUnitA, &gBattleUnitB);

    if (target == NULL)
        ComputeBattleObstacleStats();

    BattleUnwind();
}

LYN_REPLACE_CHECK(ComputeBattleUnitStats);
void ComputeBattleUnitStats(struct BattleUnit *attacker, struct BattleUnit *defender)
{
    pbc_loopfunc *it;
    for (it = ModularPreBuCalcator; *it; it++)
        (*it)(attacker, defender);
}

void InitBattleUnitStatus(struct BattleUnit *bu, struct BattleUnit *other)
{
    bu->battle_attack  = GetItemMight(bu->weapon);
    bu->battle_defense = GetItemAttributes(other->weapon) & ITEM_ATTR_MAGIC
                       ? bu->unit.res
                       : bu->unit.def;
    bu->battle_speed   = bu->unit.spd;
    bu->battle_hit     = bu->unit.skl * 2 + GetItemHit(bu->weapon) + bu->unit.lck / 2;;
    bu->battle_avoid   = bu->battle_speed * 2 + bu->unit.lck;
    bu->battle_crit    = GetItemCrit(bu->weapon) + bu->unit.skl / 2;
    bu->battle_dodge   = bu->unit.lck;
}

void PreBuStatusMinusZero(struct BattleUnit *bu)
{
    LIMIT_AREA(bu->battle_attack,  0, BATTLE_MAX_STATUS);
    LIMIT_AREA(bu->battle_defense, 0, BATTLE_MAX_STATUS);
    LIMIT_AREA(bu->battle_speed,   0, BATTLE_MAX_STATUS);
    LIMIT_AREA(bu->battle_hit,     0, BATTLE_MAX_STATUS);
    LIMIT_AREA(bu->battle_avoid,   0, BATTLE_MAX_STATUS);
    LIMIT_AREA(bu->battle_crit,    0, BATTLE_MAX_STATUS);
    LIMIT_AREA(bu->battle_dodge,   0, BATTLE_MAX_STATUS);
}

LYN_REPLACE_CHECK(ComputeBattleUnitDefense);
void ComputeBattleUnitDefense(struct BattleUnit *attacker, struct BattleUnit *defender)
{
    int status;
    pbc_func *it;
    
    status = attacker->battle_defense;

    /* Internal modular */
    status += GetItemAttributes(defender->weapon) & ITEM_ATTR_MAGIC
            ? attacker->terrain_resistance
            : attacker->terrain_defense;
    
    /* External modular */
    for (it = ModularBuDefGetter; *it; it++)
        status = (*it)(attacker, defender, status);

    attacker->battle_defense = status;
}

LYN_REPLACE_CHECK(ComputeBattleUnitBaseDefense);
void ComputeBattleUnitBaseDefense(struct BattleUnit *bu)
{
    int status;
    pbc_func *it;

    status = bu->battle_defense;

    /* Internal modular */
    status = status + bu->terrain_defense;

    /* External modular */
    for (it = ModularBuDefGetter; *it; it++)
        status = (*it)(bu, NULL, status);

    bu->battle_defense = status;
}

LYN_REPLACE_CHECK(ComputeBattleUnitAttack);
void ComputeBattleUnitAttack(struct BattleUnit *attacker, struct BattleUnit *defender)
{
    int status;
    pbc_func *it;

    status = attacker->battle_attack;

    /* Internal modular */
    status = status + attacker->advantage_bonus_damage;

    /* External modular */
    for (it = ModularBuAtkGetter; *it; it++)
        status = (*it)(attacker, defender, status);

    if (IsItemEffectiveAgainst(attacker->weapon, &defender->unit) == TRUE)
        status *= 3;

    status += attacker->unit.pow;

    attacker->battle_attack = status;
}

LYN_REPLACE_CHECK(ComputeBattleUnitSpeed);
void ComputeBattleUnitSpeed(struct BattleUnit *attacker)
{
    int status, weight;
    pbc_func *it;

    status = attacker->battle_speed;

    /* Internal modular */
    weight = GetItemWeight(attacker->weapon_before) - attacker->unit.bonus_con;
    if (weight < 0)
        weight = 0;
    
    status = status - weight;

    /* External modular */
    for (it = ModularBuSpdGetter; *it; it++)
        status = (*it)(attacker, NULL, status);

    attacker->battle_speed = status;
}

LYN_REPLACE_CHECK(ComputeBattleUnitHitRate);
void ComputeBattleUnitHitRate(struct BattleUnit *attacker)
{
    int status;
    pbc_func *it;

    status = attacker->battle_hit;

    /* Internal modular */
    status = status + attacker->advantage_bonus_hit;

    /* External modular */
    for (it = ModularBuHitGetter; *it; it++)
        status = (*it)(attacker, NULL, status);

    attacker->battle_hit = status;
}

LYN_REPLACE_CHECK(ComputeBattleUnitAvoidRate);
void ComputeBattleUnitAvoidRate(struct BattleUnit * attacker)
{
    int status;
    pbc_func *it;

    status = attacker->battle_avoid;

    /* Internal modular */
    status = status + attacker->terrain_avoid;

    /* External modular */
    for (it = ModularBuAvoGetter; *it; it++)
        status = (*it)(attacker, NULL, status);

    attacker->battle_avoid = status;
}

LYN_REPLACE_CHECK(ComputeBattleUnitCritRate);
void ComputeBattleUnitCritRate(struct BattleUnit *attacker)
{
    int status;
    pbc_func *it;

    status = attacker->battle_crit;

    /* Internal modular */
    if (UNIT_ATTRIBUTES(&attacker->unit) & UNIT_ATTR_CRITBONUS)
        status += 30;
    
    /* External modular */
    for (it = ModularBuCrtGetter; *it; it++)
        status = (*it)(attacker, NULL, status);

    attacker->battle_crit = status;
}

/* No enough space for lyn-jump ... */
void _ComputeBattleUnitDodgeRate(struct BattleUnit *attacker)
{
    int status;
    pbc_func *it;

    status = attacker->battle_dodge;

    /* Internal modular */

    /* External modular */
    for (it = ModularBuDgeGetter; *it; it++)
        status = (*it)(attacker, NULL, status);

    attacker->battle_dodge = status;
}
