#pragma once

#include "common-chax.h"

/**
 * Mokha's plan:
 * 
 * SAVE NAME       SAVE OFFSET     SAVE LENGTH     DEFAULT LENGTH  EXPANSION SIZE
 * meta            0x00            0x94            0x94            0x0
 * suspend0        0x94            0x27C0          0x1DAC          0xA14
 * suspend1        ------          ------          0x1DAC          -----
 * save1           0x2854          0x1474          0xDF0           0x684
 * save2           0x3CC8          0x1474          0xDF0           0x684
 * save3           0x513C          0x1474          0xDF0           0x684
 * _PAD_           0x65B0          0x8             -----           -----
 * link_arena      0x65B8          0x93C           0x93C           0x0
 * _PAD_           0x6EF4          0xC             -----           -----
 * chunk6          0x7000          0x1000          0x1000          0x0
 */

enum EMS_SRAM_block_sizes {
    EMS_SRAM_SIZE_HEADER = 0x94,
    EMS_SRAM_SIZE_SUS0   = 0x27C0,
    EMS_SRAM_SIZE_SUS1   = 0x0,      /* Invalid now */
    EMS_SRAM_SIZE_SAV    = 0x1474,
    EMS_SRAM_SIZE_RSV0   = 0x8,
    EMS_SRAM_SIZE_BLOCK5 = 0x093C,
    EMS_SRAM_SIZE_RSV1   = 0xC,
    EMS_SRAM_SIZE_BLOCK6 = 0x1000,
};

enum EMS_SRAM_block_memmap {
    EMS_SRAM_MEMAP_HEADER = 0x0000,
    EMS_SRAM_MEMMAP_SUS0  = EMS_SRAM_MEMAP_HEADER + EMS_SRAM_SIZE_HEADER,
    EMS_SRAM_MEMMAP_SUS1  = EMS_SRAM_MEMMAP_SUS0,    /* Invalid now */
    EMS_SRAM_MEMMAP_SAV0  = EMS_SRAM_MEMMAP_SUS0  + EMS_SRAM_SIZE_SUS0,
    EMS_SRAM_MEMMAP_SAV1  = EMS_SRAM_MEMMAP_SAV0  + EMS_SRAM_SIZE_SAV,
    EMS_SRAM_MEMMAP_SAV2  = EMS_SRAM_MEMMAP_SAV1  + EMS_SRAM_SIZE_SAV,
    EMS_SRAM_MEMMAP_RSV0  = EMS_SRAM_MEMMAP_SAV2  + EMS_SRAM_SIZE_SAV,
    EMS_SRAM_MEMMAP_5     = EMS_SRAM_MEMMAP_RSV0  + EMS_SRAM_SIZE_RSV0,
    EMS_SRAM_MEMMAP_6     = EMS_SRAM_MEMMAP_5     + EMS_SRAM_SIZE_RSV1
};

struct EmsChunk {
    /* 00 */ u16 offset;
    /* 02 */ u16 size;

    /* 04 */ void (*save)(void* dst, const u32 size);
    /* 08 */ void (*load)(void* src, const u32 size);
};

extern const struct EmsChunk EmsChunkSa[], EmsChunkSu[];
