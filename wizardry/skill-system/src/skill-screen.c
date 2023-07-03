#include "common-chax.h"
#include "hardware.h"
#include "icon.h"
#include "text.h"
#include "statscreen.h"
#include "helpbox.h"
#include "constants/videoalloc_global.h"

#include "skill-system.h"

void DrawSkillPage()
{
    int i;
    const int X = 1, Y = 14;

    struct SkillFastList *list = GetUnitSkillFastList(gStatScreenSt.unit);

    if (list->count != 0) {
        PutDrawText(gStatScreenSt.text + STATSCREEN_TEXT_BWL,
            gUiTmScratchA + TM_OFFSET(X, Y),
            TEXT_COLOR_SYSTEM_GOLD, 0, 0,
            "Skills:");
    }

    for (i = 0; i < list->count; i++) {
        PutIcon(gUiTmScratchA + TM_OFFSET(X + 4 + i * 2, Y + 1),
            SKILL_ICON(list->skills[i]),
            TILEREF(0, BGPAL_ICONS));
        
        if (i >= MSS_MAX_SKILL_COUNT)
            break;
    }
}

void HelpBoxRedirectStatScreenSkills(struct HelpBoxProc *proc)
{
    if (proc->info->msg >= GetUsedSkillCounts(gStatScreenSt.unit)) {
        switch (proc->move_key_bit) {
        case KEY_DPAD_UP:
            HelpBoxTryRelocateUp(proc);
            break;
        
        case KEY_DPAD_DOWN:
            HelpBoxTryRelocateDown(proc);
            break;
        
        case KEY_DPAD_LEFT:
            HelpBoxTryRelocateLeft(proc);
            break;

        case KEY_DPAD_RIGHT:
            HelpBoxTryRelocateRight(proc);
            break;
        
        default:
            break;
        }
    }
}

void HelpBoxPopulateStatScreenSkill(struct HelpBoxProc *proc)
{
    struct SkillFastList *list = GetUnitSkillFastList(gStatScreenSt.unit);
    u8 skill = list->skills[proc->info->msg];

    proc->msg = GetSkillDesc(skill);
}
