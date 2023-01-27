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
