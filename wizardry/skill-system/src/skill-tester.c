#include "common-chax.h"
#include "unit.h"
#include "constants/jids.h"
#include "constants/pids.h"
#include "skill-system.h"

#define BasicJudgeSkill(unit, skill)    \
do {                                    \
    if (MAX_SKILL_NUM == skill)         \
        return TRUE;                    \
                                        \
    if (0 == skill)                     \
        return FALSE;                   \
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

static bool JudgeSkillRom(struct Unit *unit, const u8 skill)
{
    int i;

    /* Judge default skills */
    for (i = 0; i < SKILL_ROM_DEFAULT_COUNT; i++) {
        if (skill == Skills_PData[unit->pinfo->id].default_skills[i])
            return TRUE;

        if (skill == Skills_JData[unit->jinfo->id].default_skills[i])
            return TRUE;
    }

    /* Judge level-based skills */
    for (i = 0; i < SKILL_ROM_LEVEL_COUNNT; i++) {
        if (unit->level < 5 * i)
            break;

        if (skill == Skills_PData[unit->pinfo->id].level_skills[i])
            return TRUE;

        if (skill == Skills_JData[unit->jinfo->id].level_skills[i])
            return TRUE;
    }

    return FALSE;
}

static bool _SkillTester(struct Unit *unit, const u8 skill)
{
    BasicJudgeSkill(unit, skill);

    if (TRUE == JudgeSkillRom(unit, skill))
        return TRUE;

    /* External modular */
    if (SkillTester_Extern)
        return SkillTester_Extern(unit, skill);

    return FALSE;
}

bool (*const SkillTester)(struct Unit *unit, const u8 skill) = _SkillTester;
