#include "hardware.h"
#include "icon.h"
#include "text.h"

#include "skill-system.h"
#include "status-screen.h"

void DrawSkillPages(void)
{
	static int const X = 1;
	static int const Y = 14;
	struct Text* const text = gStatScreen.text + STATSCREEN_TEXT_BWL;
	
	Unit* unit = gStatScreen.unit;
	int count = 0;
	u8 SkillList[6];
	
	for(int i=1; i<MAX_SKILL_NUM; i++)
		if( (*SkillTester)(unit,i) )
		{
			SkillList[count++] = i;
			
			if( count > 5 )
				break;
		}
	
	
	
	ClearText(text);
	
	if(0 != count ){
		Text_SetColor(text, TEXT_COLOR_SYSTEM_GOLD);
		Text_DrawString(text, "Skills:");
		PutText(text, gBmFrameTmap0 + TM_OFFSET(X, Y));
	}
	
	for(int i=0; i<count; i++)
		PutIcon(
			gBmFrameTmap0 + TM_OFFSET(X +4+ 2*i, Y+1), 
			SKILL_ICON(SkillList[i]), 
			TILEREF(0, 4) );
    
}