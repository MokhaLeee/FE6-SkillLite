#include "common-chax.h"
#include "unit.h"
#include "battle.h"
#include "item.h"

#include "battle-system.h"

struct WeaponTriangleRule {
    i8 attackerKind;
    i8 defenderKind;
    i8 hitBonus;
    i8 damageBonus;
};

extern struct WeaponTriangleRule CONST_DATA sWeaponTriangleRules[];

LYN_REPLACE_CHECK(BattleApplyWeaponTriangleEffect);
void BattleApplyWeaponTriangleEffect(struct BattleUnit *attacker, struct BattleUnit *defender)
{
    /*
     * Idea:
     * Since vanilla WTA bonus can only get hit & dmg bonus.
     * So here we null the vanilla WTA bonus
     * But just calculate in Pre-Battle calc
     * now WTA-bonus in BattleUnit struct is just for BKSEL UI.
     */
    return;
}


/* I prefer to put WTA-bonus calc to pre-battle-calc */
void PreBuCalc_WTA_Bonus(struct BattleUnit *attacker, struct BattleUnit *defender)
{
    struct WeaponTriangleRule const *it;

    for (it = sWeaponTriangleRules; it->attackerKind >= 0; ++it) {
        if ((attacker->weapon_kind == it->attackerKind) && (defender->weapon_kind == it->defenderKind)) {
            attacker->advantage_bonus_hit = it->hitBonus;
            attacker->advantage_bonus_damage = it->damageBonus;

            defender->advantage_bonus_hit = -it->hitBonus;
            defender->advantage_bonus_damage = -it->damageBonus;

            break;
        }
    }

    if (attacker->weapon_attributes & ITEM_ATTR_REVERTS_TRIANGLE)
        BattleApplyReaverEffect(attacker, defender);

    if (defender->weapon_attributes & ITEM_ATTR_REVERTS_TRIANGLE)
        BattleApplyReaverEffect(attacker, defender);
}
