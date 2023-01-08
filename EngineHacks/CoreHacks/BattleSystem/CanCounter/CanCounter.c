#include "battle.h"
#include "unit.h"
#include "faction.h"
#include "item.h"
#include "skill-system.h"

extern u8 CounterAttackID, WindSweepID;



void BattleInitTargetCanCounter(void)
{
    BattleUnit* bu = &gBattleUnitB;
    
    // Target cannot counter if either units are using "uncounterable" weapons

    if ((gBattleUnitA.weapon_attributes | gBattleUnitB.weapon_attributes) & ITEM_ATTR_7) {
        bu->weapon = 0;
        bu->has_inventory_weapon = FALSE;
        return;
    }

    // Target cannot counter if a berserked player unit is attacking another player unit

    if (gBattleUnitA.unit.status == UNIT_STATUS_BERSERK)
        if ((UNIT_FACTION(&gBattleUnitA.unit) == FACTION_BLUE) && (UNIT_FACTION(&gBattleUnitB.unit) == FACTION_BLUE)) {
            bu->weapon = 0;
            bu->has_inventory_weapon = FALSE;
            return;
        }
    
    
    // add for Func: SetBattleUnitWeapon
    if (gBattleUnitB.weapon_inventory_slot == 0xFF) {
        bu->weapon = 0;
        bu->has_inventory_weapon = FALSE;
        return;
    }

    
    if (gBattleUnitB.unit.status == UNIT_STATUS_SLEEP) {
        bu->weapon = 0;
        bu->has_inventory_weapon = FALSE;
        return;
    }

    // More for Skills
    // Counterattack
    if(!CanItemReachDistance(gBattleUnitB.weapon, gBattleSt.range))
        if( !(*SkillTester)(&gBattleUnitB.unit,CounterAttackID)) {
            bu->weapon = 0;
            bu->has_inventory_weapon = FALSE;
            return;
        }

    // WindSweep
    if((*SkillTester)(&gBattleUnitA.unit,WindSweepID))
        if(gBattleUnitA.battle_speed > gBattleUnitB.battle_speed) {
            bu->weapon = 0;
            bu->has_inventory_weapon = FALSE;
            return;
        }
}
