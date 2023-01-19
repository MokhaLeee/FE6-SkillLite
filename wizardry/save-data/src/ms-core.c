#include "common-chax.h"
#include "save.h"
#include "sram.h"
#include "hardware.h"
#include "chapter.h"

#include "modular-save.h"
#include "sram-memmap.h"

LYN_REPLACE_CHECK(WriteSaveBlockInfo);
void WriteSaveBlockInfo(struct SaveBlockInfo *chunk, int index)
{
    chunk->magic_b = SAVE_MAGICB_COMM;
    chunk->offset  = (uintptr_t)GetSaveTargetAddress(index);

    if (!(index < SAVE_ID_MAX))
        return;

    switch (chunk->kind) {
    case BLOCK_INFO_KIND_SAV:
        chunk->size = EMS_SRAM_SIZE_SAV;
        break;

    case BLOCK_INFO_KIND_SUS:
        chunk->size = (index == SAVE_ID_SUSPEND0)
                    ? EMS_SRAM_SIZE_SUS0
                    : EMS_SRAM_SIZE_SUS1;
        break;

    case BLOCK_INFO_KIND_2:
        chunk->size = EMS_SRAM_SIZE_BLOCK5;
        break;

    case BLOCK_INFO_KIND_3:
        chunk->size = EMS_SRAM_SIZE_BLOCK6;
        break;

    case (u8)BLOCK_INFO_KIND_INVALID:
        chunk->size = 0;
        chunk->offset = 0;
        chunk->magic_b = 0;
        break;

    default:
        return;
    }; /* switch */

    GenerateSaveBlockInfoCkSum32(chunk);
    WriteAndVerifySramFast((u8 *)chunk, (u8 *)&((struct SramHeader *)gpSramEntry)->chunks[index], sizeof(struct SaveBlockInfo));
}

LYN_REPLACE_CHECK(GetSaveTargetAddress);
u8 *GetSaveTargetAddress(int index)
{
    switch (index) {
    case SAVE_ID_GAME0:
        return gpSramEntry + EMS_SRAM_MEMMAP_SAV0;

    case SAVE_ID_GAME1:
        return gpSramEntry + EMS_SRAM_MEMMAP_SAV1;

    case SAVE_ID_GAME2:
        return gpSramEntry + EMS_SRAM_MEMMAP_SAV2;

    case SAVE_ID_SUSPEND0:
        return gpSramEntry + EMS_SRAM_MEMMAP_SUS0;

    case SAVE_ID_SUSPEND1:
        return gpSramEntry + EMS_SRAM_MEMMAP_SUS1;

    case SAVE_ID_5:
        return gpSramEntry + EMS_SRAM_MEMMAP_5;

    case SAVE_ID_6:
        return gpSramEntry + EMS_SRAM_MEMMAP_6;

    default:
        return NULL;
    } /* switch */
}

LYN_REPLACE_CHECK(CopyGameSave);
void CopyGameSave(int index_src, int index_dst)
{
    struct SaveBlockInfo chunk;
    u8 *src = GetSaveSourceAddress(index_src);
    u8 *dst = GetSaveTargetAddress(index_dst);

    ReadSramFast(src, gBuf, EMS_SRAM_SIZE_SAV);
    WriteAndVerifySramFast(gBuf, dst, EMS_SRAM_SIZE_SAV);

    chunk.magic_a = SAVE_MAGICA_COMM;
    chunk.kind = BLOCK_INFO_KIND_SAV;
    WriteSaveBlockInfo(&chunk, index_dst);
}

LYN_REPLACE_CHECK(SaveNewGame);
void SaveNewGame(int slot, int isHard)
{
    InitPlayConfig(isHard);
    InitUnits();
    ClearSupplyItems();
    ResetPermanentFlags();
    ResetSaveBlockInfo(SAVE_ID_SUSPEND0);

    gPlaySt.playthrough_id = GetNewPlaythroughId();

    /* Directly save-game */
    SaveGame(slot);
}

LYN_REPLACE_CHECK(SaveGame);
void SaveGame(int slot)
{
    const struct EmsChunk *cur;
    struct SaveBlockInfo chunk;
    u8 *dst = GetSaveTargetAddress(slot);

    ResetSaveBlockInfo(SAVE_ID_SUSPEND0);

    gPlaySt.save_slot = slot;
    gPlaySt.unk_00 = GetGameTime();
    
    for (cur = EmsChunkSa; cur->offset != 0xFFFF; cur++)
        cur->save(dst + cur->offset, cur->size);

    chunk.magic_a = SAVE_MAGICA_COMM;
    chunk.kind = BLOCK_INFO_KIND_SAV;
    WriteSaveBlockInfo(&chunk, slot);
    UpdateLastUsedGameSaveSlot(slot);
}

LYN_REPLACE_CHECK(LoadGame);
void LoadGame(int slot)
{
    const struct EmsChunk *cur;
    u8 *src = GetSaveSourceAddress(slot);

    if (!(BM_FLAG_LINKARENA & gBmSt.flags))
        ResetSaveBlockInfo(SAVE_ID_SUSPEND0);

    for (cur = EmsChunkSa; cur->offset != 0xFFFF; cur++)
        cur->load(src + cur->offset, cur->size);

    SetGameTime(gPlaySt.unk_00);
    gPlaySt.save_slot = slot;
    UpdateLastUsedGameSaveSlot(slot);
}

LYN_REPLACE_CHECK(SaveSuspendedGame);
void SaveSuspendedGame(int slot)
{
    const struct EmsChunk *cur;
    u8 *dst;
    struct SaveBlockInfo chunk;

    if (PLAY_FLAG_3 & gPlaySt.flags)
        return;

    if (!IsSramWorking())
        return;

    dst = GetSaveTargetAddress(SAVE_ID_SUSPEND0);

    gPlaySt.unk_00 = GetGameTime();
    SaveActionRand();
    
    for (cur = EmsChunkSu; cur->offset != 0xFFFF; cur++)
        cur->save(dst + cur->offset, cur->size);

    chunk.magic_a = SAVE_MAGICA_COMM;
    chunk.kind = BLOCK_INFO_KIND_SUS;
    WriteSaveBlockInfo(&chunk, SAVE_ID_SUSPEND0);

    gBmSt.unk_3C = 0;
    ChangeSuspendSaveId();
}

LYN_REPLACE_CHECK(LoadSuspendedGame);
void LoadSuspendedGame(int slot)
{
    const struct EmsChunk *cur;
    u8 *src = GetSaveSourceAddress(SAVE_ID_SUSPEND0);

    InitUnits();

    for (cur = EmsChunkSu; cur->offset != 0xFFFF; cur++)
        cur->load(src + cur->offset, cur->size);

    SetGameTime(gPlaySt.unk_00);
    RestoreActionRand();
}

LYN_REPLACE_CHECK(GetLastSuspendSaveId);
int GetLastSuspendSaveId()
{
    return 0;
}

LYN_REPLACE_CHECK(GetNextSuspendSaveId);
int GetNextSuspendSaveId()
{
    return 0;
}

LYN_REPLACE_CHECK(ChangeSuspendSaveId);
void ChangeSuspendSaveId() {}
