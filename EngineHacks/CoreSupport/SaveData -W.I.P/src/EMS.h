#pragma once
#include "common.h"

struct SaveBlockDecl {
	/* 00 */ u16 offset;
	/* 02 */ u16 type;
};

struct SaveChunkDecl {
	/* 00 */ u16 offset;
	/* 02 */ u16 size;

	/* 04 */ void (*save)(void* target, unsigned size);
	/* 08 */ void (*load)(void* source, unsigned size);

	/* 0C */ u16 identifier;
};


extern const struct SaveChunkDecl gGameSaveChunks[];
extern const struct SaveChunkDecl gSuspendSaveChunks[];