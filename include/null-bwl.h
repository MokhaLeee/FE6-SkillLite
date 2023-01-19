#pragma once

#include "common-chax.h"
#include "unit.h"

#ifndef CONFIG_NULL_BWL

#define NewBwl PidStats
#define GetNewBwlEntry GetPidStats

#else /* CONFIG_NULL_BWL */

struct NewBwl {
#ifdef CONFIG_BWL_SUPPORT
    u8 supports[UNIT_SUPPORT_COUNT];
#endif /* CONFIG_BWL_SUPPORT */

    /* Max size 0x10 */
};

struct NewBwl *GetNewBwlEntry(u8 pid);

#endif /* CONFIG_NULL_BWL */
