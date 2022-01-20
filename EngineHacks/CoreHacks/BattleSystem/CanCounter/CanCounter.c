#include "battle.h"
#include "unit.h"
#include "faction.h"
#include "item.h"
#include "skill-system.h"

extern u8 CounterAttackID, WindSweepID;


static void NullCounter(BattleUnit* bu){
	bu->weapon = 0;
	bu->has_inventory_weapon = FALSE;
}

void BattleInitTargetCanCounter(void)
{
    // Target cannot counter if either units are using "uncounterable" weapons

    if ((gBattleUnitA.weapon_attributes | gBattleUnitB.weapon_attributes) & ITEM_ATTR_7)
		NullCounter(&gBattleUnitB);

    // Target cannot counter if a berserked player unit is attacking another player unit

	if (gBattleUnitA.unit.status == UNIT_STATUS_BERSERK)
		if ((UNIT_FACTION(&gBattleUnitA.unit) == FACTION_BLUE) && (UNIT_FACTION(&gBattleUnitB.unit) == FACTION_BLUE))
			NullCounter(&gBattleUnitB);
	
	
	// add for Func: SetBattleUnitWeapon
	if (gBattleUnitB.weapon_inventory_slot == 0xFF)
		NullCounter(&gBattleUnitB);
	
	if (gBattleUnitB.unit.status == UNIT_STATUS_SLEEP)
		NullCounter(&gBattleUnitB);
	
	
	
	
	
	
	// More for Skills
	
	// Counterattack
	if( !CanItemReachDistance(gBattleUnitB.weapon, gBattleSt.range) )
		if( !(*SkillTester)(&gBattleUnitB.unit,CounterAttackID) )
			NullCounter(&gBattleUnitB);
	
	// WindSweep
	if( (*SkillTester)(&gBattleUnitA.unit,WindSweepID) )
		if( gBattleUnitA.battle_speed > gBattleUnitB.battle_speed )
			NullCounter(&gBattleUnitB);
	
}
