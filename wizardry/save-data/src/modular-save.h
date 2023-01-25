#pragma once

#include "common-chax.h"

/**
 * Mokha's plan:
 * 
 * W-O Block-6:
 * SAVE NAME       SAVE OFFSET     SAVE LENGTH     DEFAULT LENGTH  EXPANSION SIZE
 * meta            0x00            0x94            0x94            0x0
 * suspend0        0x94            0x2F30          0x1DAC          0x1184
 * save1           0x2F54          0x17A8          0xDF0           0x9B8
 * save2           0x46CC          0x17A8          0xDF0           0x9B8
 * save3           0x5E44          0x17A8          0xDF0           0x9B8
 * link_arena      0x75BC          0x93C           0x93C           0x0
 * _PAD_           0x7EF8          0x8             -----           -----
 * 
 * W Block-6:
 * meta            0x00            0x94            0x94            0x0
 * suspend0        0x94            0x2830          0x1DAC          0xA84
 * save1           0x28C4          0x14A8          0xDF0           0x6B8
 * save2           0x3D6C          0x14A8          0xDF0           0x6B8
 * save3           0x5214          0x14A8          0xDF0           0x6B8
 * link_arena      0x66BC          0x93C           0x93C           0x0
 * block_6         0x6FF8          0x1000          0x1000          0x0
 * _PAD_           0x7FF8          0x8             -----           -----
 */

enum EMS_SRAM_block_sizes {
    EMS_SRAM_SIZE_HEADE = 0x94,
    EMS_SRAM_SIZE_SUS   = 0x2830,
    EMS_SRAM_SIZE_SAV   = 0x14A8,
    EMS_SRAM_SIZE_ARENA = 0x093C,
    EMS_SRAM_SIZE_PAD   = 0x8,
    EMS_SRAM_SIZE_6     = 0x1000,
};

enum EMS_SRAM_block_memmap {
    EMS_SRAM_MEMMAP_HEAD = 0x0000,
    EMS_SRAM_MEMMAP_SUS  = EMS_SRAM_MEMMAP_HEAD + EMS_SRAM_SIZE_HEADE,
    EMS_SRAM_MEMMAP_SAV0 = EMS_SRAM_MEMMAP_SUS  + EMS_SRAM_SIZE_SUS,
    EMS_SRAM_MEMMAP_SAV1 = EMS_SRAM_MEMMAP_SAV0 + EMS_SRAM_SIZE_SAV,
    EMS_SRAM_MEMMAP_SAV2 = EMS_SRAM_MEMMAP_SAV1 + EMS_SRAM_SIZE_SAV,
    EMS_SRAM_MEMMAP_5    = EMS_SRAM_MEMMAP_SAV2 + EMS_SRAM_SIZE_SAV,
    EMS_SRAM_MEMMAP_6    = 0x7000,
};

struct EmsChunk {
    /* 00 */ u16 offset;
    /* 02 */ u16 size;

    /* 04 */ void (*save)(void* dst, const u32 size);
    /* 08 */ void (*load)(void* src, const u32 size);
};

extern const struct EmsChunk EmsChunkSa[], EmsChunkSu[];
