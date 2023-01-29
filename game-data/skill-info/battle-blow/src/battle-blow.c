#include "common-chax.h"
#include "battle.h"
#include "item.h"

#include "skill-system.h"

void BuCalcMain_BattleBlowSkills(struct BattleUnit *buA, struct BattleUnit *buB)
{
    struct Unit *unit = GetUnit(buA->unit.id);

    /* W.I.P. */
    if (GetItemAttributes(buA->weapon) & ITEM_ATTR_MAGIC) {
        if (SkillTester(unit, SKILLID_BlowFiendish))
            buA->battle_attack += 6;
    } else {
        if (SkillTester(unit, SKILLID_BlowDeath))
            buA->battle_attack += 6;
    }

    if (GetItemAttributes(buB->weapon) & ITEM_ATTR_MAGIC) {
        if (SkillTester(unit, SKILLID_BlowWarding))
            buA->battle_defense += 6;
    } else {
        if (SkillTester(unit, SKILLID_BlowArmored))
            buA->battle_defense += 6;
    }

    if (SkillTester(unit, SKILLID_BlowDarting))
        buA->battle_speed += 6;
    
    if (SkillTester(unit, SKILLID_BlowDuelist))
        buA->battle_avoid += 20;
    
    if (SkillTester(unit, SKILLID_BlowUncanny))
        buA->battle_hit += 20;
}
