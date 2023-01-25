#pragma once
#include "common-chax.h"
#include "skill-defs.h"

#include "unit.h"

#define MAX_SKILL_NUM 255
#define SKILL_ICON(id) (id + (1 << 8))

struct SkillInfo {
    u16 name;
    u16 desc;
    const u8 *icon;
    u32 priv;
};
extern const struct SkillInfo * const SkillInfoTable[MAX_SKILL_NUM];

enum skill_data_sizes {
    SKILL_ROM_DEFAULT_LIST_SIZE = 3,
    SKILL_ROM_LEVEL_LIST_SIZE = 5,

    SKILL_RAM_LIST_SIZE = 5,
};

struct SkillRomTable {
    u8 default_skills[SKILL_ROM_DEFAULT_LIST_SIZE];
    u8 level_skills[SKILL_ROM_LEVEL_LIST_SIZE];
};
extern const struct SkillRomTable Skills_PData[], Skills_JData[];

typedef bool (*const skill_test_func_t)(struct Unit *unit, const u8 skill);

extern skill_test_func_t SkillTester;
extern skill_test_func_t SkillTester_Extern[];

#ifdef CONFIG_SKILL_RAM_LIST
u8 *GetSkillRamList(struct Unit *unit);
#else
static inline u8 *GetSkillRamList(struct Unit *unit)
{
    return NULL;
}
#endif /* CONFIG_SKILL_RAM_LIST */

const void* GetSkillIconGfx(unsigned id);
u16 GetSkillName(const u8 skill);
u16 GetSkillDesc(const u8 skill);
u32 GetSkillPriv(const u8 skill);
void DrawSkillPage();
