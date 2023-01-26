#pragma once

#include "common-chax.h"

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
