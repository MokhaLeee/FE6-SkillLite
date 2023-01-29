#include "common-chax.h"
#include "unit.h"
#include "item.h"
#include "battle.h"
#include "arena.h"
#include "faction.h"
#include "trap.h"

#include "battle-system.h"

typedef int (*const mcc_func)();
extern mcc_func BattleCheckNullCounterCalculator[];

extern u16 *gBuWpnBackUp;
extern bool8 *gHasInventoryWpnBackUp; 

LYN_REPLACE_CHECK(SetBattleUnitWeapon);
void SetBattleUnitWeapon(struct BattleUnit *bu, int item_slot)
{
    if (item_slot == -1)
        item_slot = GetUnitEquippedWeaponSlot(&bu->unit);

    bu->has_inventory_weapon = TRUE;

    switch (item_slot) {
    case ITEMSLOT_INV0 ... ITEMSLOT_INV_COUNT - 1:
        bu->weapon_inventory_slot = item_slot;
        bu->weapon = bu->unit.items[bu->weapon_inventory_slot];
        break;

    case ITEMSLOT_OVERFLOW:
        bu->weapon_inventory_slot = -1;
        bu->weapon = gBmSt.inventory_item_overflow;
        break;

    case ITEMSLOT_ARENA_PLAYER:
        bu->weapon_inventory_slot = 0;
        bu->weapon = gArenaSt.player_weapon;
        bu->has_inventory_weapon = FALSE;
        break;

    case ITEMSLOT_ARENA_OPPONENT:
        bu->weapon_inventory_slot = 0;
        bu->weapon = gArenaSt.opponent_weapon;
        bu->has_inventory_weapon = FALSE;
        break;

    case ITEMSLOT_BALLISTA:
        bu->weapon_inventory_slot = -1;
        bu->weapon = GetBallistaItemAt(bu->unit.x, bu->unit.y);
        bu->has_inventory_weapon = FALSE;
        break;

    default:
        bu->weapon_inventory_slot = -1;
        bu->weapon = 0;
        bu->has_inventory_weapon = FALSE;
        break;
    }

    bu->weapon_before = bu->weapon;
    bu->weapon_attributes = GetItemAttributes(bu->weapon);
    bu->weapon_kind = GetItemKind(bu->weapon);

    if (!(gBattleSt.flags & BATTLE_FLAG_BIT2)) {
        if (bu->weapon_attributes & ITEM_ATTR_LIGHTBRAND)
            bu->weapon_kind = ITEM_KIND_LIGHT;
    }
}

LYN_REPLACE_CHECK(BattleInitTargetCanCounter);
void BattleInitTargetCanCounter(void)
{
    mcc_func *it;

    *gBuWpnBackUp = gBattleUnitB.weapon;
    *gHasInventoryWpnBackUp = gBattleUnitB.has_inventory_weapon;

    /* External modular */
    for (it = BattleCheckNullCounterCalculator; *it; it++) {
        switch ((*it)()) {
        case NULL_COUNTER:
        case FORCE_COUNTER:
            return;
        }
    }
}

/**
 * Modular check-can-counter usr functions
 */

int mcc_range()
{
    if (!CanItemReachDistance(gBattleUnitA.weapon, gBattleSt.range) || gBattleUnitA.weapon_inventory_slot == 0xFF) {
        gBattleUnitA.weapon = 0;
        gBattleUnitA.has_inventory_weapon = FALSE;
    }

    if (!CanItemReachDistance(gBattleUnitB.weapon, gBattleSt.range) || gBattleUnitB.weapon_inventory_slot == 0xFF)
        NullTargetCounterAtk();

    return NORMAL_COUNTER;
}

int mcc_debuf_sleep()
{
    if (gBattleUnitA.unit.status == UNIT_STATUS_SLEEP) {
        gBattleUnitA.weapon = 0;
        gBattleUnitA.has_inventory_weapon = FALSE;
    }

    if (gBattleUnitB.unit.status == UNIT_STATUS_SLEEP)
        NullTargetCounterAtk();

    return NORMAL_COUNTER;
}

int mcc_wpn_uncounter()
{
    if ((gBattleUnitA.weapon_attributes | gBattleUnitB.weapon_attributes) & ITEM_ATTR_UNCOUNTERABLE)
        NullTargetCounterAtk();

    return NORMAL_COUNTER;
}

int mcc_debuf_berserk()
{
    if (gBattleUnitA.unit.status == UNIT_STATUS_BERSERK) {
        if ((UNIT_FACTION(&gBattleUnitA.unit) == FACTION_BLUE) && (UNIT_FACTION(&gBattleUnitB.unit) == FACTION_BLUE))
            NullTargetCounterAtk();
    }

    return NORMAL_COUNTER;
}
