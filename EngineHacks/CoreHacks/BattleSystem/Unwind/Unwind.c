#include "common.h"
#include "battle.h"
#include "skill-system.h"
#include "item.h"

extern u8 WindSweepID, QuickRiposteID, VantageID, DesperationID;

static int CheckVantage(void);
static int CheckDesperation(void);
static int CanDouble(BattleUnit* A, BattleUnit* B);

enum{
	NOP_ATTACK = 0,
	ACT_ATTACK = 1,
	TAR_ATTACK = 2,
};

enum{
	UNWIND_VANTAGE = 1<<0,
	UNWIND_DESPERA = 1<<1,
	UNWIND_DOUBLE_ACT = 1<<2,
	UNWIND_DOUBLE_TAR = 1<<3,
};


static const u8 RoundArr[56] = {
	ACT_ATTACK, TAR_ATTACK, NOP_ATTACK, NOP_ATTACK,	// 0:default
	TAR_ATTACK, ACT_ATTACK, NOP_ATTACK, NOP_ATTACK,	// 1	= 1
	ACT_ATTACK, ACT_ATTACK, TAR_ATTACK, NOP_ATTACK, // 2	= 2	
	
	TAR_ATTACK, ACT_ATTACK, ACT_ATTACK, NOP_ATTACK, // 12	= 3
	ACT_ATTACK, TAR_ATTACK, ACT_ATTACK, NOP_ATTACK, // 3	= 4
	TAR_ATTACK, ACT_ATTACK, ACT_ATTACK, NOP_ATTACK, // 13	= 5
	ACT_ATTACK, TAR_ATTACK, NOP_ATTACK, NOP_ATTACK,	// 0:default
	ACT_ATTACK, TAR_ATTACK, NOP_ATTACK, NOP_ATTACK,	// 0:default
	ACT_ATTACK, TAR_ATTACK, TAR_ATTACK, NOP_ATTACK, // 4	= 8
	TAR_ATTACK, ACT_ATTACK, TAR_ATTACK, NOP_ATTACK, // 14	= 9
	ACT_ATTACK, ACT_ATTACK, TAR_ATTACK, TAR_ATTACK, // 24	= 10
	
	
	TAR_ATTACK, ACT_ATTACK, ACT_ATTACK, TAR_ATTACK, // 124	= 11
	ACT_ATTACK, TAR_ATTACK, ACT_ATTACK, TAR_ATTACK, // 34	= 12
	TAR_ATTACK, ACT_ATTACK, TAR_ATTACK, ACT_ATTACK  // 134	= 13
};




// 0x8024AB5
void BattleUnwind()
{
	u8 round[4];
	u8 roundInfo = 0;
	
	if( CheckVantage() )
		roundInfo |= UNWIND_VANTAGE;

	if( CanDouble(&gBattleUnitA, &gBattleUnitB) )
	{
		if( CheckDesperation() )
			roundInfo |= UNWIND_DESPERA;
		else
			roundInfo |= UNWIND_DOUBLE_ACT;
	}
	if( CanDouble(&gBattleUnitB, &gBattleUnitA) )
		roundInfo |= UNWIND_DOUBLE_TAR;

	for( int i=0; i<4; i++)
		round[i] = RoundArr[i+roundInfo*4];

	// Make Battle Real
	ClearBattleHits();
	gBattleHitIt->info |= BATTLE_HIT_INFO_BEGIN;

	// 1st
	for( int i=0; i<4; i++) {
		if((ACT_ATTACK == round[i])) {
			if(!BattleGenerateRoundHits(&gBattleUnitA, &gBattleUnitB))
				gBattleHitIt->attributes |= BATTLE_HIT_ATTR_RETALIATE;
			else
				break;
		}

		else if((TAR_ATTACK == round[i])) {
			if(!BattleGenerateRoundHits(&gBattleUnitB, &gBattleUnitA))
				gBattleHitIt->attributes |= BATTLE_HIT_ATTR_RETALIATE;
			else
				break;
		} else
			break;
	}

	gBattleHitIt->info |= BATTLE_HIT_INFO_END;
}





static int CheckVantage(void)
{
	Unit* unit = GetUnit(gBattleUnitB.unit.id);

	// if Hp < HpMax/2, Vantage
	if((*SkillTester)(unit,VantageID))
		if(unit->hp < GetUnitMaxHp(unit)/2)
			return TRUE;

	return FALSE;
}


static int CheckDesperation(void)
{
	Unit* unit = GetUnit(gBattleUnitA.unit.id);

	// if Hp < HpMax/2, Vantage
	if((*SkillTester)(unit,DesperationID))
		if(unit->hp < GetUnitMaxHp(unit)/2)
			return TRUE;

	return FALSE;
}



static int CanDouble(BattleUnit* A, BattleUnit* B)
{
	Unit* unitA = GetUnit(A->unit.id);

	// Judge Skills
	if((*SkillTester)(&A->unit,WindSweepID))
		return FALSE;

	if(&gBattleUnitB == A )
		if((*SkillTester)(&A->unit,QuickRiposteID))
			if(unitA->hp > GetUnitMaxHp(unitA)/2)
				return TRUE;

	// Normal Judge
	if(A->battle_speed > B->battle_speed)
		if((A->battle_speed - B->battle_speed) >= BATTLE_FOLLOWUP_SPEED_THRESHOLD)
			return TRUE;

	return FALSE;
}


bool BattleGetFollowUpOrder(struct BattleUnit** outAttacker, struct BattleUnit** outDefender)
{
	if (CanDouble(&gBattleUnitA, &gBattleUnitB)) 
	{
        *outAttacker = &gBattleUnitA;
        *outDefender = &gBattleUnitB;
    } else if(CanDouble( &gBattleUnitB, &gBattleUnitA)) {
        *outAttacker = &gBattleUnitB;
        *outDefender = &gBattleUnitA;
    } else
		return FALSE;

    if (GetItemWeaponEffect((*outAttacker)->weapon_before) == WEAPON_EFFECT_ECLIPSE)
		return FALSE;

    return TRUE;
}
