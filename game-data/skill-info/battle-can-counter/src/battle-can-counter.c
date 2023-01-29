#include "common-chax.h"
#include "unit.h"
#include "battle.h"

#include "skill-system.h"
#include "battle-system.h"

int CheckCanCounterSkills()
{
    struct Unit *unitA = GetUnit(gBattleUnitA.unit.id);
    struct Unit *unitB = GetUnit(gBattleUnitB.unit.id);

    if (SkillTester(unitA, SKILLID_WindSweep)) {
        NullTargetCounterAtk();
        return NULL_COUNTER;
    }

    if (SkillTester(unitB, SKILLID_CounterAttack)) {
        ResetTargetCounterAtk();
        return FORCE_COUNTER;
    }

    if (1 == gBattleSt.range) {
        if (SkillTester(unitB, SKILLID_CloseCounter)) {
            ResetTargetCounterAtk();
            return FORCE_COUNTER;
        }
    }

    return NORMAL_COUNTER;
}
