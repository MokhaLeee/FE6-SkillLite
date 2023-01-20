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

enum MSU_BasicMemMap {
    MSU_MEMMAP_START    = 0,
    MSU_MEMMAP_PLAYST   = MSU_MEMMAP_START,
    MSU_MEMMAP_ACTION   = MSU_MEMMAP_PLAYST   + SUS_SIZE_PLAYST,
    MSU_MEMMAP_TRAP     = MSU_MEMMAP_ACTION   + SUS_SIZE_ACTION,
    MSU_MEMMAP_SUPPLY   = MSU_MEMMAP_TRAP     + SUS_SIZE_TRAP,
    MSU_MEMMAP_PIDSTATS = MSU_MEMMAP_SUPPLY   + SUS_SIZE_SUPPLY,
    MSU_MEMMAP_CHWIN    = MSU_MEMMAP_PIDSTATS + 0x460 /* SUS_SIZE_PIDSTATS */,
    MSU_MEMMAP_PERMFLAG = MSU_MEMMAP_CHWIN    + SUS_SIZE_CHWIN,
    MSU_MEMMAP_TEMPFLAG = MSU_MEMMAP_PERMFLAG + SUS_SIZE_PERMFLAG,

    MSU_MEMMAP_BASE_RSV = MSU_MEMMAP_TEMPFLAG + SUS_SIZE_TEMPFLAG,
    MSU_MEMMAP_BASE_END = MSU_MEMMAP_BASE_RSV
};

enum MSU_UnitMemMap {
    MSU_MEMMAP_UNIT_B   = MSU_MEMMAP_START,
    MSU_MEMMAP_UNIT_R   = MSU_MEMMAP_UNIT_B + UNIT_SAVE_AMOUNT_BLUE  * 0x34 /* sizeof(struct SuspendPackedUnit) */,
    MSU_MEMMAP_UNIT_G   = MSU_MEMMAP_UNIT_R + UNIT_SAVE_AMOUNT_RED   * 0x34 /* sizeof(struct SuspendPackedUnit) */,

    MSU_MEMMAP_UNIT_RSV = MSU_MEMMAP_UNIT_G + UNIT_SAVE_AMOUNT_GREEN * 0x34 /* sizeof(struct SuspendPackedUnit) */,
    MSU_MEMMAP_UNIT_END = MSU_MEMMAP_UNIT_RSV
};

void MSU_SaveBasic(u8 *dst, const u32 size)
{
    if (size < MSU_MEMMAP_BASE_END)
        goto error;

    gPlaySt.unk_00 = GetGameTime();
    WriteAndVerifySramFast(
        (u8 *)&gPlaySt,
        dst + MSU_MEMMAP_PLAYST,
        SUS_SIZE_PLAYST);

    SaveActionRand();
    WriteAndVerifySramFast(
        (u8 *)&gAction,
        dst + MSU_MEMMAP_ACTION,
        SUS_SIZE_ACTION);

    SaveTraps(dst + MSU_MEMMAP_TRAP);
    SaveSupplyItems(dst + MSU_MEMMAP_SUPPLY);
    SavePidStats(dst + MSU_MEMMAP_PIDSTATS);
    SaveChWinData(dst + MSU_MEMMAP_CHWIN);
    SavePermanentFlagBits(dst + MSU_MEMMAP_PERMFLAG);
    SaveChapterFlagBits(dst + MSU_MEMMAP_TEMPFLAG);
    return;

error:
    DebugPrintStr("MSU_SaveBasic:\n");
    DebugPrintStr("Block size is NOT enough\n");
    FailScreen();
}

void MSU_LoadBasic(u8 *src, const u32 size)
{
    if (size < MSU_MEMMAP_BASE_END)
        goto error;

    ReadSramFast(
        src + MSU_MEMMAP_PLAYST,
        (u8 *)&gPlaySt,
        SUS_SIZE_PLAYST);
    SetGameTime(gPlaySt.unk_00);

    ReadSramFast(
        src + MSU_MEMMAP_ACTION,
        (u8 *)&gAction,
        SUS_SIZE_ACTION);
    RestoreActionRand();

    LoadTraps(src + MSU_MEMMAP_TRAP);
    LoadSupplyItems(src + MSU_MEMMAP_SUPPLY);
    LoadPidStats(src + MSU_MEMMAP_PIDSTATS);
    LoadChWinData(src + MSU_MEMMAP_CHWIN);
    LoadPermanentFlagBits(src + MSU_MEMMAP_PERMFLAG);
    LoadChapterFlagBits(src + MSU_MEMMAP_TEMPFLAG);
    return;

error:
    DebugPrintStr("MSU_LoadBasic:\n");
    DebugPrintStr("Block size is NOT enough\n");
    FailScreen();
}

void MSU_SaveUnit(u8 *dst, const u32 size)
{
    int i;

    if (size < MSU_MEMMAP_UNIT_END)
        goto error;

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
    return;

error:
    DebugPrintStr("MSU_SaveUnit:\n");
    DebugPrintStr("Block size is NOT enough\n");
    FailScreen();
}

void MSU_LoadUnit(u8 *src, const u32 size)
{
    int i;

    if (size < MSU_MEMMAP_UNIT_END)
        goto error;
    
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
    return;

error:
    DebugPrintStr("MSU_LoadUnit:\n");
    DebugPrintStr("Block size is NOT enough\n");
    FailScreen();
}
