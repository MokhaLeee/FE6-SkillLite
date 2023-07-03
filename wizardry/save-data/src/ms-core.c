#include "common-chax.h"
#include "save.h"
#include "save_core.h"
#include "save_game.h"
#include "hardware.h"
#include "chapter.h"
#include "armfunc.h"

#include "debug.h"
#include "modular-save.h"

noreturn void ModSaveErrLog(char *str)
{
    DebugPrintStr(str);
    FailScreen();
}

LYN_REPLACE_CHECK(WriteSaveBlockInfo);
void WriteSaveBlockInfo(struct SaveBlockInfo *chunk, int index)
{
    chunk->magic16 = SAVE_MAGIC16;
    chunk->offset  = (uintptr_t)GetSaveWriteAddr(index);

    if (!(index < SAVE_COUNT))
        return;

    switch (chunk->kind) {
    case SAVE_KIND_GAME:
        chunk->size = EMS_SRAM_SIZE_SAV;
        break;

    case SAVE_KIND_SUSPEND:
        chunk->size = EMS_SRAM_SIZE_SUS;
        break;

    case SAVE_KIND_MULTIARENA:
        chunk->size = EMS_SRAM_SIZE_ARENA;
        break;

    case SAVE_KIND_XMAP:
        chunk->size = EMS_SRAM_SIZE_6;
        break;

    case (u8)SAVE_KIND_INVALID:
        chunk->size = 0;
        chunk->offset = 0;
        chunk->magic16 = 0;
        break;

    default:
        return;
    }; /* switch */

    PopulateSaveBlockChecksum(chunk);
    WriteAndVerifySramFast(chunk, &gSramMain->block_info[index], sizeof(struct SaveBlockInfo));
}

LYN_REPLACE_CHECK(GetSaveWriteAddr);
void *GetSaveWriteAddr(int index)
{
    switch (index) {
    case SAVE_GAME0:
        return gSramMain + EMS_SRAM_MEMMAP_SAV0;

    case SAVE_GAME1:
        return gSramMain + EMS_SRAM_MEMMAP_SAV1;

    case SAVE_GAME2:
        return gSramMain + EMS_SRAM_MEMMAP_SAV2;

    case SAVE_SUSPEND:
    case SAVE_SUSPEND_ALT:
        return gSramMain + EMS_SRAM_MEMMAP_SUS;

    case SAVE_MULTIARENA:
        return gSramMain + EMS_SRAM_MEMMAP_5;

    case SAVE_XMAP:
        return gSramMain + EMS_SRAM_MEMMAP_6;

    default:
        return NULL;
    } /* switch */
}

LYN_REPLACE_CHECK(SramChecksum32);
int SramChecksum32(void const * sram_src, int size)
{
    if (size > sizeof(gBuf))
        size = sizeof(gBuf);

    ReadSramFast(sram_src, gBuf, size);
    return Checksum32(gBuf, size);
}


LYN_REPLACE_CHECK(CopyGameSave);
void CopyGameSave(int index_src, int index_dst)
{
    struct SaveBlockInfo chunk;
    u8 *src = GetSaveReadAddr(index_src);
    u8 *dst = GetSaveWriteAddr(index_dst);

    ReadSramFast(src, gBuf, EMS_SRAM_SIZE_SAV);
    WriteAndVerifySramFast(gBuf, dst, EMS_SRAM_SIZE_SAV);

    chunk.magic32 = SAVE_MAGIC32;
    chunk.kind = SAVE_KIND_GAME;
    WriteSaveBlockInfo(&chunk, index_dst);
}

LYN_REPLACE_CHECK(WriteNewGameSave);
void WriteNewGameSave(int slot, int isHard)
{
    InitPlayConfig(isHard);
    InitUnits();
    ClearSupplyItems();
    ResetPermanentFlags();
    InvalidateSuspendSave(SAVE_SUSPEND);

    gPlaySt.playthrough_id = GetNewPlaythroughId();

    /* Directly save-game */
    WriteGameSave(slot);
}

LYN_REPLACE_CHECK(WriteGameSave);
void WriteGameSave(int slot)
{
    const struct EmsChunk *cur;
    struct SaveBlockInfo chunk;
    u8 *dst = GetSaveWriteAddr(slot);

    if (gMsaRsvSize < 0)
        ModSaveErrLog("SaveGame: gMsaRsvSize\n");

    InvalidateSuspendSave(SAVE_SUSPEND);

    gPlaySt.save_id = slot;

    for (cur = EmsChunkSa; cur->off != EMS_CHUNK_INVALID_OFFSET; cur++)
        cur->save(dst + cur->off, cur->size);

    chunk.magic32 = SAVE_MAGIC32;
    chunk.kind = SAVE_KIND_GAME;
    WriteSaveBlockInfo(&chunk, slot);
    WriteLastGameSaveId(slot);
}

LYN_REPLACE_CHECK(ReadGameSave);
void ReadGameSave(int slot)
{
    const struct EmsChunk *cur;
    u8 *src = GetSaveReadAddr(slot);

    if (gMsaRsvSize < 0)
        ModSaveErrLog("LoadGame: gMsaRsvSize\n");

    if (!(BM_FLAG_LINKARENA & gBmSt.flags))
        InvalidateSuspendSave(SAVE_SUSPEND);

    for (cur = EmsChunkSa; cur->off != EMS_CHUNK_INVALID_OFFSET; cur++)
        cur->load(src + cur->off, cur->size);

    gPlaySt.save_id = slot;
    WriteLastGameSaveId(slot);
}

LYN_REPLACE_CHECK(WriteSuspendSave);
void WriteSuspendSave(int slot)
{
    const struct EmsChunk *cur;
    u8 *dst;
    struct SaveBlockInfo chunk;

    if (PLAY_FLAG_TUTORIAL & gPlaySt.flags)
        return;

    if (!IsSramWorking())
        return;
    
    if (gMsuRsvSize < 0)
        ModSaveErrLog("SaveSuspendedGame: gMsuRsvSize\n");

    dst = GetSaveWriteAddr(SAVE_SUSPEND);

    for (cur = EmsChunkSu; cur->off != EMS_CHUNK_INVALID_OFFSET; cur++)
        cur->save(dst + cur->off, cur->size);

    chunk.magic32 = SAVE_MAGIC32;
    chunk.kind = SAVE_KIND_SUSPEND;
    WriteSaveBlockInfo(&chunk, SAVE_SUSPEND);

    gBmSt.just_resumed = FALSE;
    WriteSwappedSuspendSaveId();
}

LYN_REPLACE_CHECK(ReadSuspendSave);
void ReadSuspendSave(int slot)
{
    const struct EmsChunk *cur;
    u8 *src = GetSaveReadAddr(SAVE_SUSPEND);

    if (gMsuRsvSize < 0)
        ModSaveErrLog("LoadSuspendedGame: gMsuRsvSize\n");

    for (cur = EmsChunkSu; cur->off != EMS_CHUNK_INVALID_OFFSET; cur++)
        cur->load(src + cur->off, cur->size);
}
