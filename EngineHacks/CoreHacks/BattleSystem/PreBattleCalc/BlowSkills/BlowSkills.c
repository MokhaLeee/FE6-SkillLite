#include "unit.h"
#include "battle.h"
#include "skill-system.h"

extern int BlowDartingID, BlowDeathID, BlowArmoredID;
extern int BlowFiendishID, BlowWardingID, BlowDuelistID, BlowUncannyID;


static int CheckBlow(BattleUnit* attacker, BattleUnit* defender, int skillId){
	if( &gBattleUnitA == attacker )
		if( TRUE == (*SkillTester)(&attacker->unit,skillId) )
			return TRUE;
	return FALSE;
}


// Darting Blow: AS +6
short DartingBlow(BattleUnit* atk, BattleUnit* def)
{	return CheckBlow(atk,def,BlowDartingID)?6:0; }

// Death Blow: Str +6
short DeathBlow(BattleUnit* atk, BattleUnit* def)
{	return CheckBlow(atk,def,BlowDeathID)?6:0; }

// Armored Blow: Def +6
short ArmoredBlow(BattleUnit* atk, BattleUnit* def)
{	return CheckBlow(atk,def,BlowArmoredID)?6:0; }

// Fiendish Blow: Mag+6
short FiendishBlow(BattleUnit* atk, BattleUnit* def)
{	return CheckBlow(atk,def,BlowFiendishID)?6:0; }

// Warding Blow: Res +6
short WardingBlow(BattleUnit* atk, BattleUnit* def)
{	return CheckBlow(atk,def,BlowWardingID)?6:0; }

// Duelist's Blow: Avo +20	
short DuelistsBlow(BattleUnit* atk, BattleUnit* def)
{	return CheckBlow(atk,def,BlowDuelistID)?20:0; }

// Uncanny Blow: Hit +30
short UncannyBlow(BattleUnit* atk, BattleUnit* def)
{	return CheckBlow(atk,def,BlowUncannyID)?30:0; }

