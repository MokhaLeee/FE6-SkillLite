#include "unit.h"
#include "battle.h"
#include "skill-system.h"

extern int CritUpID;

short CritUp(BattleUnit* atk, BattleUnit* def){
    if( (*SkillTester)(&atk->unit, CritUpID) )
        return 15;
    else
        return 0;
}