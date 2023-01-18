#include "common-chax.h"
#include "save.h"

LYN_REPLACE_CHECK(GetPidStats);
struct PidStats *GetPidStats(u8 pid)
{
    return NULL;
}

LYN_REPLACE_CHECK(PidStatsAddBattleAmt);
void PidStatsAddBattleAmt(struct Unit *unit) {}

LYN_REPLACE_CHECK(PidStatsAddWinAmt);
void PidStatsAddWinAmt(u8 pid) {}

LYN_REPLACE_CHECK(PidStatsRecordLoseData);
void PidStatsRecordLoseData(u8 pid) {}

LYN_REPLACE_CHECK(PidStatsRecordDeathData);
void PidStatsRecordDeathData(u8 pid, u8 killerPid, int deathCause) {}

LYN_REPLACE_CHECK(PidStatsAddActAmt);
void PidStatsAddActAmt(u8 pid) {}

LYN_REPLACE_CHECK(PidStatsAddStatViewAmt);
void PidStatsAddStatViewAmt(u8 pid) {}

LYN_REPLACE_CHECK(PidStatsAddDeployAmt);
void PidStatsAddDeployAmt(u8 pid) {}

LYN_REPLACE_CHECK(PidStatsAddSquaresMoved);
void PidStatsAddSquaresMoved(u8 pid, int amount) {}

LYN_REPLACE_CHECK(PidStatsAddExpGained);
void PidStatsAddExpGained(u8 pid, int amount) {}

LYN_REPLACE_CHECK(PidStatsGetTotalBattleAmt);
int PidStatsGetTotalBattleAmt()
{
    return 0;
}

LYN_REPLACE_CHECK(PidStatsGetTotalWinAmt);
int PidStatsGetTotalWinAmt()
{
    return 0;
}

LYN_REPLACE_CHECK(PidStatsGetTotalLossAmt);
int PidStatsGetTotalLossAmt()
{
    return 0;
}

LYN_REPLACE_CHECK(PidStatsGetTotalLevel);
int PidStatsGetTotalLevel()
{
    return 0;
}

LYN_REPLACE_CHECK(PidStatsRecordBattleRes);
void PidStatsRecordBattleRes(void) {}
