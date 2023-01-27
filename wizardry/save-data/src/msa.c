#include "common-chax.h"
#include "save.h"
#include "bm.h"
#include "hardware.h"
#include "sram.h"
#include "chapter.h"

#include "debug.h"
#include "modular-save.h"
#include "null-bwl.h"

void MSA_SavePlaySt(u8 *dst, const u32 size)
{
    if (size < SAV_SIZE_PLAYST)
        ModSaveErrLog("MSA_SavePlaySt: size\n");

    gPlaySt.unk_00 = GetGameTime();

    WriteAndVerifySramFast(
        (u8 *)&gPlaySt,
        dst + MSA_MEMMAP_PLAYST,
        SAV_SIZE_PLAYST);
}

void MSA_LoadPlaySt(u8 *src, const u32 size)
{
    if (size < SAV_SIZE_PLAYST)
        ModSaveErrLog("MSA_LoadPlaySt: size\n");

    ReadSramFast(
        src + MSA_MEMMAP_PLAYST,
        (u8 *)&gPlaySt,
        SAV_SIZE_PLAYST);

    SetGameTime(gPlaySt.unk_00);
}

void MSA_SaveSupply(u8 *dst, const u32 size)
{
    if (size < SAV_SIZE_SUPPLY)
        ModSaveErrLog("MSA_SaveSupply: size\n");

    SaveSupplyItems(dst + MSA_MEMMAP_SUPPLY);
}

void MSA_LoadSupply(u8 *src, const u32 size)
{
    if (size < SAV_SIZE_SUPPLY)
        ModSaveErrLog("MSA_LoadSupply: size\n");

    LoadSupplyItems(src + MSA_MEMMAP_SUPPLY);
}

void MSA_SaveBwl(u8 *dst, const u32 size)
{
    if (size < 0x460 /* SAV_SIZE_PIDSTATS */)
        ModSaveErrLog("MSA_SaveBwl: size\n");

    SavePidStats(dst + MSA_MEMMAP_PIDSTATS);
}

void MSA_LoadBwl(u8 *src, const u32 size)
{
    if (size < 0x460 /* SAV_SIZE_PIDSTATS */)
        ModSaveErrLog("MSA_LoadBwl: size\n");

    LoadPidStats(src + MSA_MEMMAP_PIDSTATS);
}

void MSA_SaveChWin(u8 *dst, const u32 size)
{
    if (size < SAV_SIZE_CHWIN)
        ModSaveErrLog("MSA_SaveChWin: size\n");

    SaveChWinData(dst + MSA_MEMMAP_CHWIN);
}

void MSA_LoadChWin(u8 *src, const u32 size)
{
    if (size < SAV_SIZE_CHWIN)
        ModSaveErrLog("MSA_LoadChWin: size\n");

    LoadChWinData(src + MSA_MEMMAP_CHWIN);
}

void MSA_SavePermFlag(u8 *dst, const u32 size)
{
    if (size < SAV_SIZE_PERMFLAG)
        ModSaveErrLog("MSA_SavePermFlag: size\n");

    SavePermanentFlagBits(dst + MSA_MEMMAP_PERMFLAG);
}

void MSA_LoadPermFlag(u8 *src, const u32 size)
{
    if (size < SAV_SIZE_PERMFLAG)
        ModSaveErrLog("MSA_LoadPermFlag: size\n");

    LoadPermanentFlagBits(src + MSA_MEMMAP_PERMFLAG);
}

void MSA_SaveUnit(u8 *dst, const u32 size)
{
    int i;

    if (size < MSA_SIZE_UNIT)
        ModSaveErrLog("MSA_SaveUnit: size\n");

    for (i = 0; i < UNIT_SAVE_AMOUNT_BLUE; i++)
        SaveUnit(
            &gUnitArrayBlue[i],
            dst + i * 0x28 /* sizeof(struct SavePackedUnit) */);
}

void MSA_LoadUnit(u8 *src, const u32 size)
{
    int i;

    if (size < MSA_SIZE_UNIT)
        ModSaveErrLog("MSA_LoadUnit: size\n");

    InitUnits();

    for (i = 0; i < UNIT_SAVE_AMOUNT_BLUE; i++)
        LoadUnit(
            src + i * 0x28 /* sizeof(struct SavePackedUnit) */,
            &gUnitArrayBlue[i]);
}

const int gMsaTotalSize = EMS_SRAM_SIZE_SAV;
const int gMsaUsedSize = MSA_MEMMAP_RSV;
const int gMsaRsvSize = EMS_SRAM_SIZE_SAV - MSA_MEMMAP_RSV;

const struct EmsChunk EmsChunkSa[] = {
    {
        .off  = MSA_MEMMAP_PLAYST,
        .size = SAV_SIZE_PLAYST,
        .save = MSA_SavePlaySt,
        .load = MSA_LoadPlaySt,
    },
    {
        .off  = MSA_MEMMAP_SUPPLY,
        .size = SAV_SIZE_SUPPLY,
        .save = MSA_SaveSupply,
        .load = MSA_LoadSupply,
    },
    {
        .off  = MSA_MEMMAP_PIDSTATS,
        .size = 0x460 /* SAV_SIZE_PIDSTATS */,
        .save = MSA_SaveBwl,
        .load = MSA_LoadBwl,
    },
    {
        .off  = MSA_MEMMAP_CHWIN,
        .size = SAV_SIZE_CHWIN,
        .save = MSA_SaveChWin,
        .load = MSA_LoadChWin,
    },
    {
        .off  = MSA_MEMMAP_PERMFLAG,
        .size = SAV_SIZE_PERMFLAG,
        .save = MSA_SavePermFlag,
        .load = MSA_LoadPermFlag,
    },
    {
        .off  = MSA_MEMMAP_UNIT,
        .size = MSA_SIZE_UNIT,
        .save = MSA_SaveUnit,
        .load = MSA_LoadUnit,
    },
    {EMS_CHUNK_INVALID_OFFSET, 0, NULL, NULL}
};
