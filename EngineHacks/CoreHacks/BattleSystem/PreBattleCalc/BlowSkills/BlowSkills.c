#include "unit.h"
#include "battle.h"
#include "skill-system.h"

extern int BlowDartingID, BlowDeathID, BlowArmoredID;
extern int BlowFiendishID, BlowWardingID, BlowDuelistID, BlowUncannyID;

static inline int CheckBlow(BattleUnit* attacker, int skillId){
    if( &gBattleUnitA == attacker )
        if( TRUE == (*SkillTester)(&attacker->unit,skillId) )
            return TRUE;
    return FALSE;
}

// Darting Blow: AS +6
short DartingBlow(BattleUnit* atk, BattleUnit* def)
{
    return CheckBlow(atk,BlowDartingID)?6:0;
}

// Death Blow: Str +6
short DeathBlow(BattleUnit* atk, BattleUnit* def)
{
    return CheckBlow(atk,BlowDeathID)?6:0;
}

// Armored Blow: Def +6
short ArmoredBlow(BattleUnit* atk, BattleUnit* def)
{
    return CheckBlow(atk,BlowArmoredID)?6:0;
}

// Fiendish Blow: Mag+6
short FiendishBlow(BattleUnit* atk, BattleUnit* def)
{
    return CheckBlow(atk,BlowFiendishID)?6:0;
}

// Warding Blow: Res +6
short WardingBlow(BattleUnit* atk, BattleUnit* def)
{
    return CheckBlow(atk,BlowWardingID)?6:0;
}

// Duelist's Blow: Avo +20
short DuelistsBlow(BattleUnit* atk, BattleUnit* def)
{
    return CheckBlow(atk,BlowDuelistID)?20:0;
}

// Uncanny Blow: Hit +30
short UncannyBlow(BattleUnit* atk, BattleUnit* def)
{
    return CheckBlow(atk,BlowUncannyID)?30:0;
}
