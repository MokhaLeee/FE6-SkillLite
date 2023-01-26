#include "common-chax.h"
#include "battle.h"
#include "unit.h"
#include "item.h"

#include "battle-system.h"

bool IsItemEffectiveAgainst(u16 item, struct Unit *unit)
{
    int jid = unit->jinfo->id;
    u8 const *list = GetItemEffectiveness(item);

    if (UNIT_PID(unit) == UNIT_PID(&gBattleUnitB.unit)) {
        /*
         * Here we may judge for attacker (gBattleUnitA)
         * which may  prepare for combat-art, etc.
         */
    }

    if (!list)
        return FALSE;

    while (*list != 0) {
        if (*list == jid)
            goto check_delphi_shield;

        list++;
    }

    return FALSE;

    check_delphi_shield: {
        int i, attributes;

        if (GetItemEffectiveness(item) != JList_BowEffectiveness)
            return TRUE;

        attributes = 0;

        for (i = 0; i < ITEMSLOT_INV_COUNT; ++i)
            attributes = attributes | GetItemAttributes(unit->items[i]);

        if (attributes & ITEM_ATTR_DELPHI_SHIELD)
            return FALSE;

        return TRUE;
    }
}
