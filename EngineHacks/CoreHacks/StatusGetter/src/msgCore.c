#include "unit.h"

typedef int (*MSG_Func)(Unit*);
extern MSG_Func HpGetters[];
extern MSG_Func PowGetters[];
extern MSG_Func SpdGetters[];
extern MSG_Func SklGetters[];
extern MSG_Func LckGetters[];
extern MSG_Func DefGetters[];
extern MSG_Func ResGetters[];




static int Get(MSG_Func* funcs, Unit* unit){
	int base = 0;
	MSG_Func* it = &funcs[0];
	while(*it)
		base += (*it++)(unit);
	
	return base;	
}


int GetUnitMaxHp(struct Unit* unit){
	int stat = unit->max_hp + Get(HpGetters,unit);
	return stat>0 ? stat:0;
}

int GetUnitCurrentHp(struct Unit* unit){
	
	if (unit->hp > GetUnitMaxHp(unit))
        unit->hp = GetUnitMaxHp(unit);
	
	return unit->hp;
}


int GetUnitPower(struct Unit* unit){
	int stat = unit->pow + Get(PowGetters,unit);
	return stat>0 ? stat:0;
}


int GetUnitSkill(struct Unit* unit){
	int stat;
	
	if (unit->state & US_RESCUING)
		stat = unit->skl/2 + Get(SklGetters,unit);
	else
		stat = unit->skl + Get(SklGetters,unit);
	
	if( stat < 0 )
		stat = 0;
	
	return stat;
}

int GetUnitSpeed(struct Unit* unit){
	int stat;
	
	if (unit->state & US_RESCUING)
		stat = unit->spd/2 + Get(SpdGetters,unit);
	else
		stat = unit->spd + Get(SpdGetters,unit);
	
	if( stat < 0 )
		stat = 0;
	
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

