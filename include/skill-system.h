#pragma once
#include "skill-defs.h"

#include "unit.h"

#define MAX_SKILL_NUM 255

struct SkillInfo {
    u16 name;
    u16 desc;
    const u8 *icon;
	u32 priv;
};
extern const struct SkillInfo * const SkillInfoTable[];

enum skill_rom_table_counts {
    SKILL_ROM_DEFAULT_COUNT = 3,
    SKILL_ROM_LEVEL_COUNNT = 5,
};

struct SkillRomTable {
    u8 default_skills[SKILL_ROM_DEFAULT_COUNT];
    u8 level_skills[SKILL_ROM_LEVEL_COUNNT];
};
extern const struct SkillRomTable Skills_PData[], Skills_JData[];

// Core
extern bool (*const SkillTester)(struct Unit *unit, u8 skillId);

// Icons
#define SKILL_ICON(id) (id + (1 << 8))
