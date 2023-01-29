#pragma once

#include "unit.h"
#include "battle.h"

enum battle_can_counter_ret {
    NORMAL_COUNTER,
    NULL_COUNTER,
    FORCE_COUNTER
};

extern u16 *gBuWpnBackUp;
extern bool8 *gHasInventoryWpnBackUp; 

static inline void NullTargetCounterAtk()
{
    gBattleUnitB.weapon = 0;
    gBattleUnitB.has_inventory_weapon = FALSE;
}

static inline void ResetTargetCounterAtk()
{
    gBattleUnitB.weapon = *gBuWpnBackUp;
    gBattleUnitB.has_inventory_weapon = *gHasInventoryWpnBackUp;
}
