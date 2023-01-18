#pragma once
#include "configs/fe6_chax_defconfig.h"

#include "common.h"

#define LYN_REPLACE_CHECK(name) \
    static void const * const __attribute__((unused)) lyn_exists_check_ ## name = &name
