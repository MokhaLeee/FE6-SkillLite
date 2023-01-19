#include "common-chax.h"
#include "skill-system.h"

extern const u8 SI_WIP[];

const struct SkillInfo * const SkillInfoTable[MAX_SKILL_NUM] = {NULL};

const void* GetSkillIconGfx(unsigned id)
{
    if (SkillInfoTable[id] && SkillInfoTable[id]->icon)
        return SkillInfoTable[id]->icon;

    return SI_WIP;
}

u16 GetSkillName(const u8 id)
{
    if (SkillInfoTable[id])
        return SkillInfoTable[id]->name;

    return 0;
}

u16 GetSkillDesc(const u8 id)
{
    if (SkillInfoTable[id])
        return SkillInfoTable[id]->desc;

    return 0;
}

u32 GetSkillPriv(const u8 skill)
{
    if (SkillInfoTable[skill])
        return SkillInfoTable[skill]->priv;
    
    return 0;
}
