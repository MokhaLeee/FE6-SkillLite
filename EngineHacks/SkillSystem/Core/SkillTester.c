#include "common.h"
#include "Unit.h"
#include "skill-system.h"

#ifndef s8
#define s8 int8_t
#endif


enum {
	SKILL_COUNT_DEFAULT	= 3,
	SKILL_COUNT_LEVEL	= 5
};

typedef struct SkillRomTable SkillRomTable;
struct SkillRomTable {
	u8 skills0[SKILL_COUNT_DEFAULT];
	u8 skillLv[SKILL_COUNT_LEVEL];
};

extern const SkillRomTable SkillTable_Char[];
extern const SkillRomTable SkillTable_Class[];

static int JudgeSkillROM(Unit* unit, u8 skillId);

// SkillTesters
int JudgeSkill(Unit* unit, u8 skillId)
{
	return JudgeSkillROM(unit,skillId);
}

// Judge ROM Funcs
static int CheckRomSkill_Char(Unit* unit, u8 skillId)
{
	int i;
	int level = unit->level;
	int CharID = unit->pinfo->id;
	
	// For Level 0
	for(i=0; i<SKILL_COUNT_DEFAULT; i++)
		if(skillId == SkillTable_Char[CharID].skills0[i])
			return TRUE;
	
	// Lv 5/10/15/20/25
	for(i = 0; i < SKILL_COUNT_LEVEL; i++) {
		level -= 5;
		if(level < 0)
			break;
		else if(skillId == SkillTable_Char[CharID].skillLv[i])
			return TRUE;
	}
	return FALSE;
}

static int CheckRomSkill_Class(Unit* unit, u8 skillId)
{
	int i;
	int level = unit->level;
	int ClassID = unit->jinfo->id;
	
	// Lv 0
	for(i = 0; i < 3; i++)
		if(skillId == SkillTable_Class[ClassID].skills0[i])
			return 1;
	
	// Lv 5/10/15/20/25
	for(i = 0; i < SKILL_COUNT_LEVEL; i++) {
		level -= 5;
		if(level < 0)
			break;
		else if(skillId == SkillTable_Class[ClassID].skillLv[i])
			return TRUE;
	}
	return FALSE;
}

static int JudgeSkillROM(Unit* unit, u8 skillId)
{
	return CheckRomSkill_Char(unit,skillId) || CheckRomSkill_Class(unit,skillId);
}
