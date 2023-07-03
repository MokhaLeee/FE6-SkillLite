#pragma once

#include "common.h"
#include "unit.h"
#include "bm.h"
#include "trap.h"
#include "supply.h"
#include "action.h"
#include "eventinfo.h"
#include "save_game.h"

enum SuspandDataSizes {
    SUS_SIZE_PLAYST     = sizeof(struct PlaySt),
    SUS_SIZE_ACTION     = sizeof(struct Action),
    SUS_SIZE_UNIT_B     = (UNIT_SAVE_AMOUNT_BLUE) * sizeof(struct SuspendSavePackedUnit),
    SUS_SIZE_UNIT_R     = (UNIT_SAVE_AMOUNT_RED) * sizeof(struct SuspendSavePackedUnit),
    SUS_SIZE_UNIT_G     = (UNIT_SAVE_AMOUNT_GREEN) * sizeof(struct SuspendSavePackedUnit),
    SUS_SIZE_TRAP       = TRAP_MAX_COUNT * sizeof(struct Trap),
    SUS_SIZE_SUPPLY     = SUPPLY_ITEM_COUNT * sizeof(u16),
    SUS_SIZE_PIDSTATS   = PID_STATS_COUNT * sizeof(struct PidStats),
    SUS_SIZE_CHWIN      = CHAPTER_STATS_COUNT * sizeof(struct ChapterStats),
    SUS_SIZE_PERMFLAG   = sizeof(gPermanentFlagBits),
    SUS_SIZE_TEMPFLAG   = sizeof(gChapterFlagBits) + 3 /* align 2 */,
};

enum SaveDataSizes {
    SAV_SIZE_PLAYST     = sizeof(struct PlaySt),
    SAV_SIZE_UNIT       = UNIT_SAVE_AMOUNT_BLUE * sizeof(struct GameSavePackedUnit),
    SAV_SIZE_SUPPLY     = SUPPLY_ITEM_COUNT * sizeof(u16),
    SAV_SIZE_PIDSTATS   = PID_STATS_COUNT * sizeof(struct PidStats),
    SAV_SIZE_CHWIN      = CHAPTER_STATS_COUNT * sizeof(struct ChapterStats),
    SAV_SIZE_PERMFLAG   = sizeof(gPermanentFlagBits) + 3 /* align 2 */,
};
