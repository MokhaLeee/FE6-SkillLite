#include "common.h"
#include "unit.h"
#include "status-screen.h"
#include "skill-system.h"
#include "help-box.h"

void HbRedirect_Skill(struct HelpBoxProc* proc){
	int count = 0;
	const int InfoNum = proc->info->msg;
	Unit* unit = gStatScreen.unit;
	
	// W.I.P
	for(int i=1; i<MAX_SKILL_NUM; i++)
		if( (*SkillTester)(unit,i) )
			if( count++ == InfoNum )
				return;
	
	TryRelocateHbUp(proc);
}


void HbPopuplate_Skill(struct HelpBoxProc* proc){
    int count = 0;
	const int InfoNum = proc->info->msg;
	Unit* unit = gStatScreen.unit;
	
	// W.I.P
	for(int i=1; i<MAX_SKILL_NUM; i++)
		if( (*SkillTester)(unit,i) )
			if( count++ == InfoNum )
			{
				proc->msg = SkillInfoTable[i]->msgDesc;
				return;
			}

}


