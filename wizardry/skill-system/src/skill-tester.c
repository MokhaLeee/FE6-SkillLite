#include "common-chax.h"
#include "unit.h"
#include "constants/jids.h"
#include "constants/pids.h"

#include "skill-system.h"

#define BasicJudgeSkill(unit, skill)    \
do {                                    \
    if (MAX_SKILL_NUM == skill)         \
        return FALSE;                   \
                                        \
    if (0 == skill)                     \
        return TRUE;                    \
                                        \
    if (!UNIT_IS_VALID(unit))           \
        return FALSE;                   \
                                        \
    if (unit->jinfo->id > MAX_JIDS)     \
        return FALSE;                   \
                                        \
    if (unit->pinfo->id > MAX_PIDS)     \
        return FALSE;                   \
} while (0)

#ifdef CONFIG_SKILL_RAM_LIST
u8 *GetSkillRamList(struct Unit *unit)
{
    if (NULL != unit) {
#ifdef CONFIG_SKILL_RAM_LIST_SUPPORT
        return &unit->supports[0];
#endif
    }

    return NULL;
}
#endif /* CONFIG_SKILL_RAM_LIST */

static bool JudgeSkillRom(struct Unit *unit, const u8 skill)
{
    int i;

    /* Judge default skills */
    for (i = 0; i < SKILL_ROM_DEFAULT_LIST_SIZE; i++) {
        if (skill == Skills_PData[unit->pinfo->id].default_skills[i])
            return TRUE;

        if (skill == Skills_JData[unit->jinfo->id].default_skills[i])
            return TRUE;
    }

    /* Judge level-based skills */
    for (i = 0; i < SKILL_ROM_LEVEL_LIST_SIZE; i++) {
        if (unit->level < 5 * i)
            break;

        if (skill == Skills_PData[unit->pinfo->id].level_skills[i])
            return TRUE;

        if (skill == Skills_JData[unit->jinfo->id].level_skills[i])
            return TRUE;
    }

    return FALSE;
}

#ifdef CONFIG_SKILL_RAM_LIST
static bool JudgeSkillRam(struct Unit *unit, const u8 skill)
{
    int i;

    u8 *list = GetSkillRamList(unit);

    if (list) {
        for (i = 0; i < SKILL_RAM_LIST_SIZE; i++) {
            if (skill == list[i])
                return TRUE;
        }
    }

    return FALSE;
}
#endif /* CONFIG_SKILL_RAM_LIST */

bool SkillTester_comm(struct Unit *unit, const u8 skill)
{
    skill_test_func_t *it;

    BasicJudgeSkill(unit, skill);

    if (TRUE == JudgeSkillRom(unit, skill))
        return TRUE;

#ifdef CONFIG_SKILL_RAM_LIST
    if (TRUE == JudgeSkillRam(unit, skill))
        return TRUE;
#endif /* CONFIG_SKILL_RAM_LIST */

    /* External modular */
    for (it = SkillTester_Extern; *it; it++) {
        if (TRUE == (*it)(unit, skill))
            return TRUE;
    }

    return FALSE;
}

bool SkillTester_fast(struct Unit *unit, const u8 skill)
{
    int i;
    struct SkillFastList *list;

    BasicJudgeSkill(unit, skill);

    list = GetUnitSkillFastList(unit);
    if (list) {
        for (i = 0; i < list->count; i++) {
            if (list->skills[i] == skill)
                return TRUE;
        }
    }

    return FALSE;
}

bool (*const SkillTester)(struct Unit *unit, const u8 skill) = SkillTester_fast;
