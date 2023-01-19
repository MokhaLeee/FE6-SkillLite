#include "common-chax.h"
#include "hardware.h"
#include "icon.h"
#include "text.h"
#include "statscreen.h"
#include "skill-system.h"
#include "constants/videoalloc_global.h"

void DrawSkillPage()
{
    int i, count;
    const int X = 1, Y = 14;
    u8 SkillList[6] = {0};

    for (i = 1, count = 0; i < MAX_SKILL_NUM; i++) {
        if (SkillTester(gStatScreenSt.unit, i)) {
            SkillList[count++] =  i;

            if (count > 5)
                break;
        }
    }

    if (count != 0) {
        PutDrawText(gStatScreenSt.text + STATSCREEN_TEXT_BWL,
            gUnk_Tm_02003238 + TM_OFFSET(X, Y),
            TEXT_COLOR_SYSTEM_GOLD, 0, 0,
            "Skills:");
    }

    for (i = 0; i < count; i++) {
        PutIcon(gUnk_Tm_02003238 + TM_OFFSET(X + 4 + i * 2, Y + 1),
            SKILL_ICON(SkillList[i]),
            TILEREF(0, BGPAL_ICONS));
    }
}
