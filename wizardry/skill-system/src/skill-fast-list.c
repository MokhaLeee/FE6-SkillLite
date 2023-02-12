#include "common-chax.h"
#include "unit.h"
#include "battle.h"
#include "hardware.h"

#include "skill-system.h"

struct SkillFastList *GetUnitSkillFastList(struct Unit *unit)
{
    int i;
    struct SkillFastList *list = NULL;

    if (UNIT_PID(unit) == gSkillFastLists[0]->pid)
        list = gSkillFastLists[0];
    else if (UNIT_PID(unit) == gSkillFastLists[1]->pid)
        list = gSkillFastLists[1];

    if (!list) {
        /* List advance */
        list = gSkillFastLists[~*gSkillFastListNext];

        /* Fasten for battle-units judgement */
        if (UNIT_PID(unit) == UNIT_PID(&gBattleUnitA.unit))
            list = gSkillFastLists[0];
        if (UNIT_PID(unit) == UNIT_PID(&gBattleUnitB.unit))
            list = gSkillFastLists[1];

        list->pid = UNIT_PID(unit);
        list->count = 0;

        for (i = 1; i < MAX_SKILL_NUM; i++) {
            if (SkillTester_comm(unit, i)) {
                list->skills[list->count] = i;
                
                list->count++;
                if (list->count >= UNIT_MAX_SKILL_COUNT)
                    break;
            }
        }
    }

    return list;
}

int GetUsedSkillCounts(struct Unit *unit)
{
    return GetUnitSkillFastList(unit)->count;
}

void ResetSkillFastLists()
{
    CpuFastFill16(0, gSkillFastLists[0], 2 * sizeof(struct SkillFastList));
}

void DisableUnitSkills(struct Unit *unit)
{
    GetUnitSkillFastList(unit)->count = 0;
}
