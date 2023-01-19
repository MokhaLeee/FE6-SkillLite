#pragma once

#include "common-chax.h"

struct EmsChunk {
    /* 00 */ u16 offset;
    /* 02 */ u16 size;

    /* 04 */ void (*save)(void* target, unsigned size);
    /* 08 */ void (*load)(void* source, unsigned size);
};

extern const struct EmsChunk EmsChunkSa[], EmsChunkSu[];
