#include "common-chax.h"
#include "battle.h"

#include "skill-system.h"

void BuCalcMain_BuStatus(struct BattleUnit *buA, struct BattleUnit *buB)
{
    struct Unit *unit = GetUnit(buA->unit.id);

    if (SkillTester(unit, SKILLID_CritUp))
        buA->battle_crit += 15;
}
