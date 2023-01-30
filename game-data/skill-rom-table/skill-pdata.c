#include "skill-system.h"
#include "constants/pids.h"

const struct SkillRomTable Skills_PData[MAX_PIDS] = {

    [PID_ROY] = {
        .default_skills = {
            SID_SklBonus,
            SID_StrBonus,
        },
        .level_skills = {
            SID_BlowDeath,
        },
    },
};
