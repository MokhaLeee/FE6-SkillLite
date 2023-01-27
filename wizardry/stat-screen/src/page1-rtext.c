#include "common-chax.h"
#include "statscreen.h"
#include "helpbox.h"

#include "skill-system.h"

extern struct HelpBoxInfo HelpInfo_086778B0;    /* res */
extern struct HelpBoxInfo HelpInfo_08677958;    /* cond */

const struct HelpBoxInfo HelpInfo_StatScreenSkill1, HelpInfo_StatScreenSkill2, HelpInfo_StatScreenSkill3, \
        HelpInfo_StatScreenSkill4, HelpInfo_StatScreenSkill5;

const struct HelpBoxInfo HelpInfo_StatScreenSkill1 =
{
    .adjacent_up = &HelpInfo_086778B0,
    .adjacent_right = &HelpInfo_StatScreenSkill2,
    .x = 0x8C,
    .y = 0x88,
    .msg = 0,
    .redirect = HelpBoxRedirectStatScreenSkills,
    .populate = HelpBoxPopulateStatScreenSkill,
};

const struct HelpBoxInfo HelpInfo_StatScreenSkill2 =
{
    .adjacent_left = &HelpInfo_StatScreenSkill1,
    .adjacent_right = &HelpInfo_StatScreenSkill3,
    .x = 0x9C,
    .y = 0x88,
    .msg = 1,
    .redirect = HelpBoxRedirectStatScreenSkills,
    .populate = HelpBoxPopulateStatScreenSkill,
};

const struct HelpBoxInfo HelpInfo_StatScreenSkill3 =
{
    .adjacent_left = &HelpInfo_StatScreenSkill2,
    .adjacent_right = &HelpInfo_StatScreenSkill4,
    .x = 0xAC,
    .y = 0x88,
    .msg = 2,
    .redirect = HelpBoxRedirectStatScreenSkills,
    .populate = HelpBoxPopulateStatScreenSkill,
};

const struct HelpBoxInfo HelpInfo_StatScreenSkill4 =
{
    .adjacent_left = &HelpInfo_StatScreenSkill3,
    .adjacent_right = &HelpInfo_StatScreenSkill5,
    .x = 0xBC,
    .y = 0x88,
    .msg = 3,
    .redirect = HelpBoxRedirectStatScreenSkills,
    .populate = HelpBoxPopulateStatScreenSkill,
};

const struct HelpBoxInfo HelpInfo_StatScreenSkill5 =
{
    .adjacent_left = &HelpInfo_StatScreenSkill4,
    .adjacent_right = &HelpInfo_StatScreenSkill1,
    .x = 0xCC,
    .y = 0x88,
    .msg = 4,
    .redirect = HelpBoxRedirectStatScreenSkills,
    .populate = HelpBoxPopulateStatScreenSkill,
};
