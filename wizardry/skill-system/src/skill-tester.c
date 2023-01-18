#include "common-chax.h"
#include "unit.h"
#include "skill-system.h"

static bool _SkillTester(struct Unit *unit, u8 skillId)
{
    return FALSE;
}

bool (*const SkillTester)(struct Unit *unit, u8 skillId) = _SkillTester;
