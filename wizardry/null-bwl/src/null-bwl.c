#include "common-chax.h"
#include "save.h"
#include "save_stats.h"
#include "null-bwl.h"

#ifdef CONFIG_NULL_BWL

LYN_REPLACE_CHECK(GetPidStats);
struct PidStats *GetPidStats(u8 pid)
{
    return NULL;
}

LYN_REPLACE_CHECK(PidStatsAddBattle);
void PidStatsAddBattle(struct Unit *unit) {}

LYN_REPLACE_CHECK(PidStatsAddWin);
void PidStatsAddWin(u8 pid) {}

LYN_REPLACE_CHECK(PidStatsAddLoss);
void PidStatsAddLoss(u8 pid) {}

LYN_REPLACE_CHECK(PidStatsSetDefeatInfo);
void PidStatsSetDefeatInfo(u8 pid, u8 killerPid, int deathCause) {}

LYN_REPLACE_CHECK(PidStatsAddAct);
void PidStatsAddAct(u8 pid) {}

LYN_REPLACE_CHECK(PidStatsAddStatView);
void PidStatsAddStatView(u8 pid) {}

LYN_REPLACE_CHECK(PidStatsAddDeploy);
void PidStatsAddDeploy(u8 pid) {}

LYN_REPLACE_CHECK(PidStatsAddMove);
void PidStatsAddMove(u8 pid, int amount) {}

LYN_REPLACE_CHECK(PidStatsAddExpGained);
void PidStatsAddExpGained(u8 pid, int amount) {}

LYN_REPLACE_CHECK(PidStatsCountTotalBattles);
int PidStatsCountTotalBattles()
{
    return 0;
}

LYN_REPLACE_CHECK(PidStatsCountTotalWins);
int PidStatsCountTotalWins()
{
    return 0;
}

LYN_REPLACE_CHECK(PidStatsCountTotalLosses);
int PidStatsCountTotalLosses()
{
    return 0;
}

LYN_REPLACE_CHECK(PidStatsCountTotalLevelsGained);
int PidStatsCountTotalLevelsGained()
{
    return 0;
}

LYN_REPLACE_CHECK(PidStatsUpdateFromBattleOutcome);
void PidStatsUpdateFromBattleOutcome(void) {}

struct NewBwl *GetNewBwlEntry(u8 pid)
{
    if (pid >= PID_STATS_COUNT)
        return NULL;
    else if (0 == GetPInfo(pid)->affinity)
        return NULL;

    return (struct NewBwl *)(gPidStats + (pid - 1));
}

#endif /* CONFIG_NULL_BWL */
