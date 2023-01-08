#pragma once
#include "common.h"
#include "unit.h"

#define MAX_SKILL_NUM 255

typedef struct SkillInfo SkillInfo;
struct SkillInfo{
    u16 msgName;      //* name text id
    u16 msgDesc;      //* description text id
    const void* icon; //* icon gfx address
	u8 unk[4];
};

extern const SkillInfo* const SkillInfoTable[];

// Core
extern int (*SkillTester)(Unit* unit, u8 skillId);


// Icons
#define SKILL_ICON(id) ( id + (1<<8) )
