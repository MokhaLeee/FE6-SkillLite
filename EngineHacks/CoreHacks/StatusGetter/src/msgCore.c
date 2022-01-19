#include "unit.h"

typedef int (*MSG_Func)(Unit*);
extern MSG_Func PowGetters[];
extern MSG_Func SpdGetters[];
extern MSG_Func SklGetters[];
extern MSG_Func LckGetters[];
extern MSG_Func DefGetters[];
extern MSG_Func ResGetters[];
extern MSG_Func HpMaxGetters[];
extern MSG_Func MovGetters[];



static int Get(MSG_Func* funcs, Unit* unit){
	int base = 0;
	MSG_Func* it = &funcs[0];
	while(*it)
		base += (*it++)(unit);
	
	return base;	
}

int GetUnitCurrentHp(struct Unit* unit){
	
	int bonus = Get(HpMaxGetters,unit);
	int stat = unit->hp + bonus;
	int HpMax = unit->max_hp + bonus;
	
	if( stat > HpMax)
		stat = HpMax;
	
	if( stat < 0 )
		stat = 0;
	
	unit->hp = stat;
	
	return stat;
}

int GetUnitMaxHp(struct Unit* unit){
	int stat = unit->max_hp + Get(HpMaxGetters,unit);
	return stat>0 ? stat:0;
}
int GetUnitPower(struct Unit* unit){
	int stat = unit->pow + Get(PowGetters,unit);
	return stat>0 ? stat:0;
}

int GetUnitSkill(struct Unit* unit){
	int stat = unit->skl + Get(SklGetters,unit);
	
	if( stat < 0 )
		stat = 0;
	
	if( US_RESCUING & unit->state )
		stat = stat/2;
	
	return stat;
}

int GetUnitSpeed(struct Unit* unit){
	int stat = unit->spd + Get(SpdGetters,unit);
	if( stat < 0 )
		stat = 0;
	
	if( US_RESCUING & unit->state )
		stat = stat/2;
	
	return stat;
}

int GetUnitDefense(struct Unit* unit){
	int stat = unit->def + Get(DefGetters,unit);
	return stat>0 ? stat:0;
}

int GetUnitResistance(struct Unit* unit){
	int stat = unit->res + Get(ResGetters,unit);
	return stat>0 ? stat:0;
}

int GetUnitLuck(struct Unit* unit){
	int stat = unit->lck + Get(LckGetters,unit);
	return stat>0 ? stat:0;
}

