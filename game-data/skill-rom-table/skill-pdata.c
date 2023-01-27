#include "skill-system.h"
#include "constants/pids.h"

const struct SkillRomTable Skills_PData[MAX_PIDS] = {

    [PID_ROY] = {
        .default_skills = {
            SKILLID_SklBonus,
            SKILLID_StrBonus,
        },
        .level_skills = {
            SKILLID_BlowDeath,
        },
    },
};
