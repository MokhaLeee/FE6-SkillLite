#include "battle.h"
#include "item.h"

typedef int (*BC_Func)(BattleUnit*, BattleUnit*);
extern BC_Func BC_DefBonus[];
extern BC_Func BC_ResBonus[];
extern BC_Func BC_PowBonus[];
extern BC_Func BC_MagBonus[];
extern BC_Func BC_SpdBonus[];
extern BC_Func BC_HitBonus[];
extern BC_Func BC_AvoBonus[];
extern BC_Func BC_CritBonus[];
extern BC_Func BC_DodgBonus[];



static inline int Get(BC_Func* funcs, BattleUnit* A, BattleUnit* B){
	int base = 0;
	BC_Func* it = &funcs[0];
	while(*it)
		base += (*it++)(A,B);
	
	return base;	
}





void ComputeBattleUnitDefense(BattleUnit*, BattleUnit*);
void ComputeBattleUnitAttack(BattleUnit*, BattleUnit*);
void ComputeBattleUnitSpeed(BattleUnit*, BattleUnit*);
void ComputeBattleUnitHitRate(BattleUnit*, BattleUnit*);
void ComputeBattleUnitAvoidRate(BattleUnit*, BattleUnit*);
void ComputeBattleUnitCritRate(BattleUnit*, BattleUnit*);
void ComputeBattleUnitDodgeRate(BattleUnit*, BattleUnit*);

void ComputeBattleUnitStats(struct BattleUnit* attacker, struct BattleUnit* defender)
{
    /* 
	ComputeBattleUnitDefense(attacker, defender);
	ComputeBattleUnitAttack(attacker, defender);
    ComputeBattleUnitSpeed(attacker, defender);
    ComputeBattleUnitHitRate(attacker, defender);
    ComputeBattleUnitAvoidRate(attacker, defender);
    ComputeBattleUnitCritRate(attacker, defender);
    ComputeBattleUnitDodgeRate(attacker, defender);
	
    ComputeBattleUnitSupportBonuses(attacker, defender); 
	*/
	
	typedef void (*BC_Compute)(BattleUnit*, BattleUnit*);
	extern BC_Compute PreBattleCalcLoop[];
	
	BC_Compute *it = &PreBattleCalcLoop[0];
	while(*it)
		(*it++)(attacker, defender);
}


void InitBuStat(BattleUnit* attacker, BattleUnit* defender){
	attacker->battle_attack = 0;
	attacker->battle_defense = 0;
	attacker->battle_speed = 0;
	attacker->battle_hit = 0;
	attacker->battle_avoid = 0;
	attacker->battle_crit = 0;
	attacker->battle_dodge = 0;
}

void ComputeBattleUnitDefense(struct BattleUnit* attacker, struct BattleUnit* defender){
	short def =
		attacker->battle_defense +
		attacker->terrain_defense + 
		attacker->unit.def;
	
	if (GetItemAttributes(defender->weapon) & ITEM_ATTR_MAGIC)
		def += Get(BC_ResBonus, attacker, defender);
	else
		def += Get(BC_DefBonus, attacker, defender);
	
	// minus zero
	if( def < 0 )
		def = 0;
	
	attacker->battle_defense = def;
}


void ComputeBattleUnitAttack(struct BattleUnit* attacker, struct BattleUnit* defender)
{
    short atk =
		attacker->battle_attack +
		GetItemMight(attacker->weapon) + 
		attacker->advantage_bonus_damage;
	
	if (GetItemAttributes(attacker->weapon) & ITEM_ATTR_MAGIC)
		atk += Get(BC_MagBonus, attacker, defender);
	else
		atk += Get(BC_PowBonus, attacker, defender);
	
	// minus zero
	if( atk < 0 )
		atk = 0;
	
	if (IsItemEffectiveAgainst(attacker->weapon, &defender->unit) == TRUE)
		atk *= 3;

    attacker->battle_attack = atk + attacker->unit.pow;
}



void ComputeBattleUnitSpeed(struct BattleUnit* attacker, BattleUnit* defender)
{
	int weight = GetItemWeight(attacker->weapon_before);

	weight -= attacker->unit.bonus_con;

	if (weight < 0)
		weight = 0;

	short spd = 
		attacker->battle_speed +
		attacker->unit.spd - 
		weight +
		Get(BC_SpdBonus, attacker, defender);
	
	// minus zero
	if (spd < 0)
		spd = 0;
	
	attacker->battle_speed = spd;
}



void ComputeBattleUnitHitRate(struct BattleUnit* attacker, BattleUnit* defender)
{
	short hit =
		attacker->battle_hit +
		attacker->unit.skl*2 + 
		GetItemHit(attacker->weapon) + 
		attacker->unit.lck/2 + 
		attacker->advantage_bonus_hit +
		Get(BC_HitBonus, attacker, defender);
	
	// minus zero
	if (hit < 0)
		hit = 0;
	
	attacker->battle_hit = hit;
}




void ComputeBattleUnitAvoidRate(BattleUnit* attacker, BattleUnit* defender)
{
	short avo = 
		attacker->battle_speed*2 + 
		attacker->terrain_avoid + 
		attacker->unit.lck +
		Get(BC_AvoBonus, attacker, defender);
		
	// minus zero
	if (avo < 0)
		avo = 0;
	
	 attacker->battle_avoid += avo;
}



void ComputeBattleUnitCritRate(struct BattleUnit* attacker, BattleUnit* defender)
{
    short crit = 
		attacker->battle_crit +
		GetItemCrit(attacker->weapon) + 
		attacker->unit.skl/2 +
		Get(BC_CritBonus, attacker, defender);

	// if (UNIT_ATTRIBUTES(&attacker->unit) & UNIT_ATTR_CRITBONUS)
	//	crit += 30;
	
	// minus zero
	if( crit < 0 )
		crit = 0;
	
	attacker->battle_crit = crit;
}




void ComputeBattleUnitDodgeRate(struct BattleUnit* attacker, BattleUnit* defender)
{
	short dodge = 
		attacker->battle_dodge +
		attacker->unit.lck +
		Get(BC_DodgBonus, attacker, defender);
	
	// minus zero
	if( dodge < 0 )
		dodge = 0;
	
    attacker->battle_dodge = dodge;
}