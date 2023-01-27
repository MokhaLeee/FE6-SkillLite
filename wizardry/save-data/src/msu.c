#include "common-chax.h"
#include "save.h"
#include "bm.h"
#include "action.h"
#include "hardware.h"
#include "sram.h"
#include "unit.h"
#include "supply.h"
#include "trap.h"

#include "debug.h"
#include "modular-save.h"
#include "null-bwl.h"

void MSU_SavePlaySt(u8 *dst, const u32 size)
{
    if (size < SUS_SIZE_PLAYST)
        ModSaveErrLog("MSU_SavePlaySt: size\n");

    gPlaySt.unk_00 = GetGameTime();

    WriteAndVerifySramFast(
        (u8 *)&gPlaySt,
        dst + MSU_MEMMAP_PLAYST,
        SUS_SIZE_PLAYST);
}

void MSU_LoadPlaySt(u8 *src, const u32 size)
{
    if (size < SUS_SIZE_PLAYST)
        ModSaveErrLog("MSU_LoadPlaySt: size\n");

    ReadSramFast(
        src + MSU_MEMMAP_PLAYST,
        (u8 *)&gPlaySt,
        SUS_SIZE_PLAYST);

    SetGameTime(gPlaySt.unk_00);
}

void MSU_SaveAction(u8 *dst, const u32 size)
{
    if (size < SUS_SIZE_ACTION)
        ModSaveErrLog("MSU_SaveAction: size\n");

    SaveActionRand();

    WriteAndVerifySramFast(
        (u8 *)&gAction,
        dst + MSU_MEMMAP_ACTION,
        SUS_SIZE_ACTION);
}

void MSU_LoadAction(u8 *src, const u32 size)
{
    if (size < SUS_SIZE_ACTION)
        ModSaveErrLog("MSU_LoadAction: size\n");

    ReadSramFast(
        src + MSU_MEMMAP_ACTION,
        (u8 *)&gAction,
        SUS_SIZE_ACTION);

    RestoreActionRand();
}

void MSU_SaveTrap(u8 *dst, const u32 size)
{
    if (size < SUS_SIZE_TRAP)
        ModSaveErrLog("MSU_SaveTrap: size\n");

    SaveTraps(dst + MSU_MEMMAP_TRAP);
}

void MSU_LoadTrap(u8 *src, const u32 size)
{
    if (size < SUS_SIZE_TRAP)
        ModSaveErrLog("MSU_LoadTrap: size\n");

    LoadTraps(src + MSU_MEMMAP_TRAP);
}

void MSU_SaveSupply(u8 *dst, const u32 size)
{
    if (size < SUS_SIZE_SUPPLY)
        ModSaveErrLog("MSU_SaveSupply: size\n");

    SaveSupplyItems(dst + MSU_MEMMAP_SUPPLY);
}

void MSU_LoadSupply(u8 *src, const u32 size)
{
    if (size < SUS_SIZE_SUPPLY)
        ModSaveErrLog("MSU_LoadSupply: size\n");

    LoadSupplyItems(src + MSU_MEMMAP_SUPPLY);
}

void MSU_SaveBwl(u8 *dst, const u32 size)
{
    if (size < 0x460 /* SUS_SIZE_PIDSTATS */)
        ModSaveErrLog("MSU_SaveBwl: size\n");

    SavePidStats(dst + MSU_MEMMAP_PIDSTATS);
}

void MSU_LoadBwl(u8 *src, const u32 size)
{
    if (size < 0x460 /* SUS_SIZE_PIDSTATS */)
        ModSaveErrLog("MSU_LoadBwl: size\n");

    LoadPidStats(src + MSU_MEMMAP_PIDSTATS);
}

void MSU_SaveChWin(u8 *dst, const u32 size)
{
    if (size < SUS_SIZE_CHWIN)
        ModSaveErrLog("MSU_SaveChWin: size\n");

    SaveChWinData(dst + MSU_MEMMAP_CHWIN);
}

void MSU_LoadChWin(u8 *src, const u32 size)
{
    if (size < SUS_SIZE_CHWIN)
        ModSaveErrLog("MSU_LoadChWin: size\n");

    LoadChWinData(src + MSU_MEMMAP_CHWIN);
}

void MSU_SavePermFlag(u8 *dst, const u32 size)
{
    if (size < SUS_SIZE_PERMFLAG)
        ModSaveErrLog("MSU_SavePermFlag: size\n");

    SavePermanentFlagBits(dst + MSU_MEMMAP_PERMFLAG);
}

void MSU_LoadPermFlag(u8 *src, const u32 size)
{
    if (size < SUS_SIZE_PERMFLAG)
        ModSaveErrLog("MSU_LoadPermFlag: size\n");

    LoadPermanentFlagBits(src + MSU_MEMMAP_PERMFLAG);
}

void MSU_SaveTempFlag(u8 *dst, const u32 size)
{
    if (size < SUS_SIZE_PERMFLAG)
        ModSaveErrLog("MSU_SaveTempFlag: size\n");

    SaveChapterFlagBits(dst + MSU_MEMMAP_TEMPFLAG);
}

void MSU_LoadTempFlag(u8 *src, const u32 size)
{
    if (size < SUS_SIZE_PERMFLAG)
        ModSaveErrLog("MSU_LoadTempFlag: size\n");

    LoadChapterFlagBits(src + MSU_MEMMAP_TEMPFLAG);
}

void MSU_SaveUnit(u8 *dst, const u32 size)
{
    int i;

    if (size < MSU_MEMMAP_UNIT_END)
        ModSaveErrLog("MSU_SaveUnit: size\n");

    for (i = 0; i < UNIT_SAVE_AMOUNT_BLUE; i++) {
        PackUnitForSuspend(
            &gUnitArrayBlue[i],
            gBuf + MSU_MEMMAP_UNIT_B + i * 0x34 /* sizeof(struct SuspendPackedUnit) */);
    }

    for (i = 0; i < UNIT_SAVE_AMOUNT_RED; i++) {
        PackUnitForSuspend(
            &gUnitArrayRed[i],
            gBuf + MSU_MEMMAP_UNIT_R + i * 0x34 /* sizeof(struct SuspendPackedUnit) */);
    }

    for (i = 0; i < UNIT_SAVE_AMOUNT_GREEN; i++) {
        PackUnitForSuspend(
            &gUnitArrayGreen[i],
            gBuf + MSU_MEMMAP_UNIT_G + i * 0x34 /* sizeof(struct SuspendPackedUnit) */);
    }
    
    WriteAndVerifySramFast(gBuf, dst, MSU_MEMMAP_UNIT_END);
}

void MSU_LoadUnit(u8 *src, const u32 size)
{
    int i;

    if (size < MSU_MEMMAP_UNIT_END)
        ModSaveErrLog("MSU_LoadUnit: size\n");
    
    InitUnits();
    
    for (i = 0; i < UNIT_SAVE_AMOUNT_BLUE; i++) {
        LoadUnitFormSuspend(
            src + MSU_MEMMAP_UNIT_B + i * 0x34 /* sizeof(struct SuspendPackedUnit) */,
            &gUnitArrayBlue[i]);
    }

    for (i = 0; i < UNIT_SAVE_AMOUNT_RED; i++) {
        LoadUnitFormSuspend(
            src + MSU_MEMMAP_UNIT_R + i * 0x34 /* sizeof(struct SuspendPackedUnit) */,
            &gUnitArrayRed[i]);
    }

    for (i = 0; i < UNIT_SAVE_AMOUNT_GREEN; i++) {
        LoadUnitFormSuspend(
            src + MSU_MEMMAP_UNIT_G + i * 0x34 /* sizeof(struct SuspendPackedUnit) */,
            &gUnitArrayGreen[i]);
    }
}

const int gMsuTotalSize = EMS_SRAM_SIZE_SUS;
const int gMsuUsedSize = MSU_MEMMAP_RSV;
const int gMsuRsvSize = EMS_SRAM_SIZE_SUS - MSU_MEMMAP_RSV;

const struct EmsChunk EmsChunkSu[] = {
    {
        .off  = MSU_MEMMAP_PLAYST,
        .size = SUS_SIZE_PLAYST,
        .save = MSU_SavePlaySt,
        .load = MSU_LoadPlaySt,
    },
    {
        .off  = MSU_MEMMAP_ACTION,
        .size = SUS_SIZE_ACTION,
        .save = MSU_SaveAction,
        .load = MSU_LoadAction,
    },
    {
        .off  = MSU_MEMMAP_TRAP,
        .size = SUS_SIZE_TRAP,
        .save = MSU_SaveTrap,
        .load = MSU_LoadTrap,
    },
    {
        .off  = MSU_MEMMAP_SUPPLY,
        .size = SUS_SIZE_SUPPLY,
        .save = MSU_SaveSupply,
        .load = MSU_LoadSupply,
    },
    {
        .off  = MSU_MEMMAP_PIDSTATS,
        .size = 0x460 /* SUS_SIZE_PIDSTATS */,
        .save = MSU_SaveBwl,
        .load = MSU_LoadBwl,
    },
    {
        .off  = MSU_MEMMAP_CHWIN,
        .size = SUS_SIZE_CHWIN,
        .save = MSU_SaveChWin,
        .load = MSU_LoadChWin,
    },
    {
        .off  = MSU_MEMMAP_PERMFLAG,
        .size = SUS_SIZE_PERMFLAG,
        .save = MSU_SavePermFlag,
        .load = MSU_LoadPermFlag,
    },
    {
        .off  = MSU_MEMMAP_TEMPFLAG,
        .size = SUS_SIZE_TEMPFLAG,
        .save = MSU_SaveTempFlag,
        .load = MSU_LoadTempFlag,
    },
    {
        .off  = MSU_MEMMAP_UNIT,
        .size = MSU_SIZE_UNIT,
        .save = MSU_SaveUnit,
        .load = MSU_LoadUnit,
    },
    {EMS_CHUNK_INVALID_OFFSET, 0, NULL, NULL}
};
