#pragma once
#include "configs/fe6_chax_defconfig.h"

#include "common.h"

#define LYN_REPLACE_CHECK(name) \
    static void const * const __attribute__((unused)) lyn_exists_check_ ## name = &name

#ifndef LIMIT_AREA
#define LIMIT_AREA(num, min, max)   \
    if (num > max)                  \
        num = max;                  \
    if (num < min)                  \
        num = min;
#endif /* LIMIT_AREA */

#ifndef UNIT_IS_VALID
#define UNIT_IS_VALID(aUnit) ((aUnit) && (aUnit)->pinfo)
#endif /* UNIT_IS_VALID */
