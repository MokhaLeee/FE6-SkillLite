#include "common.h"
#include "skill-system.h"

const void* GetSkillIconGfx(unsigned id){
	return SkillInfoTable[id]->icon;
}