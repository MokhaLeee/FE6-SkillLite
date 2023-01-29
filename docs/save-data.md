# Mokha's expand plan for SRAM
Total length: 32K, 0x8000 (0x0E000000 ~ 0x0E007FFF)

```
SAVE NAME       SAVE OFFSET     SAVE LENGTH     DEFAULT LENGTH  EXPANSION SIZE
meta            0x00            0x94            0x94            0x0
suspend0        0x94            0x2A40          0x1DAC          0xC94
save1           0x2AD4          0x13F8          0xDF0           0x608
save2           0x3ECC          0x13F8          0xDF0           0x608
save3           0x52C4          0x13F8          0xDF0           0x608
link_arena      0x66BC          0x93C           0x93C           0x0
_PAD_           0x6FF8          0x8             -----           -----
block_6         0x7000          0x1000          0x1000          0x0
```

BTW, a better way is to remove block-6 so that we can get another 0x1000 size block. But it is a W.I.P work, and at this time, the expand plan may get this:
```
SAVE NAME       SAVE OFFSET     SAVE LENGTH     DEFAULT LENGTH  EXPANSION SIZE
meta            0x00            0x94            0x94            0x0
suspend0        0x94            0x2F30          0x1DAC          0x1184
save1           0x2F54          0x17A8          0xDF0           0x9B8
save2           0x46CC          0x17A8          0xDF0           0x9B8
save3           0x5E44          0x17A8          0xDF0           0x9B8
link_arena      0x75BC          0x93C           0x93C           0x0
_PAD_           0x7EF8          0x8             -----           -----
block_6         -----           -----           0x1000           -----
```

# Add your own chunks to modular-expanded-save

Suppose we need to save a 8 Bytes from 0x03000000 space in save data:

1. Get into **wizardry/save-data/src/ms-memmap.h**, and define this size at the head of the file:
```C
// wizardry/save-data/src/ms-memmap.h
#define MSA_SIZE_EXAMPLE 8
```
2. Modify in `msa_memmap`:
```diff
-- MSA_MEMMAP_RSV      = MSA_MEMMAP_UNIT     + MSA_SIZE_UNIT,
++ MSA_MEMMAP_EXAMPLE  = MSA_MEMMAP_UNIT     + MSA_SIZE_UNIT,
++ MSA_MEMMAP_RSV      = MSA_MEMMAP_EXAMPLE  + MSA_SIZE_EXAMPLE,
```
3. Get into **wizardry/save-data/src/msa.c**, and define the `.load` and `.save` function:
```C
// wizardry/save-data/src/msa.c
void MSA_SaveExample(u8 *dst, const u32 size)
{
    if (size < MSA_SIZE_EXAMPLE)
        ModSaveErrLog("MSA_SaveExample: size\n");

    WriteAndVerifySramFast(
        (u8 *)0x03000000,
        dst + MSA_MEMMAP_EXAMPLE,
        MSA_SIZE_EXAMPLE);
}

void MSA_LoadExample(u8 *src, const u32 size)
{
    if (size < MSA_SIZE_EXAMPLE)
        ModSaveErrLog("MSA_LoadExample: size\n");

    ReadSramFast(
        src + MSA_MEMMAP_EXAMPLE,
        (u8 *)0x03000000,
        MSA_SIZE_EXAMPLE);
}
```
4. Add your save-chunk to `EmsChunkSa`:
```C
// wizardry/save-data/src/msa.c
    {
        .off  = MSA_MEMMAP_EXAMPLE,
        .size = MSA_SIZE_EXAMPLE,
        .save = MSA_SaveExample,
        .load = MSA_LoadExample,
    },
```
5. Rebuild the project and test your rom
Try to start a new game. If the size or offset is overflow, the debug system (need `CONFIG_USE_DEBUG_TEXT` defined) will show you the message.
