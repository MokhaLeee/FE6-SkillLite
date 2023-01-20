#include "common-chax.h"
#include "save.h"
#include "bm.h"
#include "hardware.h"
#include "sram.h"

#include "debug.h"
#include "modular-save.h"
#include "null-bwl.h"

enum MSA_BasicMemMap {
    MSA_MEMMAP_START    = 0,
    MSA_MEMMAP_PLAYST   = MSA_MEMMAP_START,
    MSA_MEMMAP_SUPPLY   = MSA_MEMMAP_PLAYST   + SAV_SIZE_PLAYST,
    MSA_MEMMAP_PIDSTATS = MSA_MEMMAP_SUPPLY   + SAV_SIZE_SUPPLY,
    MSA_MEMMAP_CHWIN    = MSA_MEMMAP_PIDSTATS + 0x460 /* SAV_SIZE_PIDSTATS */,
    MSA_MEMMAP_PERMFLAG = MSA_MEMMAP_CHWIN    + SAV_SIZE_CHWIN,

    MSA_MEMMAP_BASE_RSV = MSA_MEMMAP_PERMFLAG + SAV_SIZE_PERMFLAG,
    MSA_MEMMAP_BASE_MAX = MSA_MEMMAP_BASE_RSV
};

enum MSA_UnitMemMap {
    MSA_MEMMAP_UNIT     = MSA_MEMMAP_START,

    MSA_MEMMAP_UNIT_RSV = MSA_MEMMAP_UNIT + UNIT_SAVE_AMOUNT_BLUE  * 0x28 /* sizeof(struct SavePackedUnit) */,
    MSA_MEMMAP_UNIT_MAX = MSA_MEMMAP_UNIT_RSV
};

void MSA_SaveBasic(u8 *dst, const u32 size)
{
    if (size < MSA_MEMMAP_BASE_MAX)
        goto error;

    gPlaySt.unk_00 = GetGameTime();
    WriteAndVerifySramFast(
        (u8 *)&gPlaySt,
        dst + MSA_MEMMAP_PLAYST,
        SAV_SIZE_PLAYST);

    SaveSupplyItems(dst + MSA_MEMMAP_SUPPLY);
    SavePidStats(dst + MSA_MEMMAP_PIDSTATS);
    SaveChWinData(dst + MSA_MEMMAP_CHWIN);
    SavePermanentFlagBits(dst + MSA_MEMMAP_PERMFLAG);
    return;

error:
    DebugPrintStr("MSA_SaveBasic:\n");
    DebugPrintStr("Block size is NOT enough\n");
    FailScreen();
}

void MSA_LoadBasic(u8 *src, const u32 size)
{
    if (size < MSA_MEMMAP_BASE_MAX)
        goto error;

    ReadSramFast(
        src + MSA_MEMMAP_PLAYST,
        (u8 *)&gPlaySt,
        SAV_SIZE_PLAYST);
    SetGameTime(gPlaySt.unk_00);

    LoadSupplyItems(src + MSA_MEMMAP_SUPPLY);
    LoadPidStats(src + MSA_MEMMAP_PIDSTATS);
    LoadChWinData(src + MSA_MEMMAP_CHWIN);
    LoadPermanentFlagBits(src + MSA_MEMMAP_PERMFLAG);
    return;

error:
    DebugPrintStr("MSA_LoadBasic:\n");
    DebugPrintStr("Block size is NOT enough\n");
    FailScreen();
}

void MSA_SaveUnit(u8 *dst, const u32 size)
{
    int i;

    if (size < MSA_MEMMAP_UNIT_MAX)
        goto error;

    for (i = 0; i < UNIT_SAVE_AMOUNT_BLUE; i++)
        SaveUnit(
            &gUnitArrayBlue[i],
            dst + i * 0x28 /* sizeof(struct SuspendPackedUnit) */);

    return;

error:
    DebugPrintStr("MSA_SaveUnit:\n");
    DebugPrintStr("Block size is NOT enough\n");
    FailScreen();
}

void MSA_LoadUnit(u8 *src, const u32 size)
{
    int i;

    if (size < MSA_MEMMAP_UNIT_MAX)
        goto error;

    InitUnits();

    for (i = 0; i < UNIT_SAVE_AMOUNT_BLUE; i++)
        LoadUnit(
            src + i * 0x28 /* sizeof(struct SuspendPackedUnit) */,
            &gUnitArrayBlue[i]);

    return;

error:
    DebugPrintStr("MSA_LoadUnit:\n");
    DebugPrintStr("Block size is NOT enough\n");
    FailScreen();
}
