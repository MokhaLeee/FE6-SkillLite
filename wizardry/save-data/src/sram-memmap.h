#ifndef EMS_SRAM_MEMMAP
#define EMS_SRAM_MEMMAP

/**
 * Mokha's plan:
 * SAVE NAME       SAVE OFFSET     SAVE LENGTH     DEFAULT LENGTH  EXPANSION SIZE
 * meta            0x00            0x90            0x90            0x0
 * suspend0        0x90            0x27C0          0x1DAC          0xA14
 * suspend1        0x2850          0xC             0x1DAC          -----
 * save1           0x285C          0x1474          0xDF0           0x684
 * save2           0x3CD0          0x1474          0xDF0           0x684
 * save3           0x5144          0x1474          0xDF0           0x684
 * link_arena      0x65B8          0x93C (?)       0x93C (?)       ???
 * chunk6          0x7000          ???             ???             0x0
 */

#define EMS_SRAM_SIZE_HEADER 0x90
#define EMS_SRAM_SIZE_SUS0   0x27C0
#define EMS_SRAM_SIZE_SUS1   0xC
#define EMS_SRAM_SIZE_SAV    0x1474
#define EMS_SRAM_SIZE_BLOCK5 0x093C
#define EMS_SRAM_SIZE_BLOCK6 0x1000

#define EMS_SRAM_MEMAP_HEADER 0x0
#define EMS_SRAM_MEMMAP_SUS0  (EMS_SRAM_MEMAP_HEADER + EMS_SRAM_SIZE_HEADER)
#define EMS_SRAM_MEMMAP_SUS1  (EMS_SRAM_MEMMAP_SUS0 + EMS_SRAM_SIZE_SUS0)
#define EMS_SRAM_MEMMAP_SAV0  (EMS_SRAM_MEMMAP_SUS1 + EMS_SRAM_SIZE_SUS1)
#define EMS_SRAM_MEMMAP_SAV1  (EMS_SRAM_MEMMAP_SAV0 + EMS_SRAM_SIZE_SAV)
#define EMS_SRAM_MEMMAP_SAV2  (EMS_SRAM_MEMMAP_SAV1 + EMS_SRAM_SIZE_SAV)
#define EMS_SRAM_MEMMAP_5     (EMS_SRAM_MEMMAP_SAV2 + EMS_SRAM_SIZE_SAV)
#define EMS_SRAM_MEMMAP_6     0x7000

#endif /* EMS_SRAM_MEMMAP */
