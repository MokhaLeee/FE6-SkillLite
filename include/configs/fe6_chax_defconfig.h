#ifndef _CONFIG_H
#define _CONFIG_H

/**
 * FreeSpace
 */
#define FreeSpaceBLRange 0xF635C
#define FreeSpace 0x7FF0B0

#define FreeSpaceTable (FreeSpace)
#define FreeSpaceTableEnd (FreeSpaceTable + 0x2000)
#define FreeSpaceStr FreeSpaceTableEnd
#define FreeSpaceStrEnd (FreeSpaceStr + 0xF0000)
#define FreeSpaceComm FreeSpaceStrEnd


/**
 * Enbale Free-RAM-Sapce.
 * This will occupy debug text space (sDebugTextSt),
 */
#define FreeRAMSpace 0x2025B8C /* sDebugTextSt, size = 0x2028, end at 0x2027BB4 */

#define gBuWpnBackUp_ptr 0x2025B8C
#define gHasInventoryWpnBackUp_ptr 0x2025B8E
#define gSkillFastListNext_ptr 0x2025B8F
#define gRandStC_ptr 0x2025B90
#define gSkillFastLists_ptr 0x2025B98

#define FreeRAMSpace_cur 0x2025BD8

/**
 * Enable debug log with function FailScreen() etc.
 * BTW, sDebugTextSt has been moved to SRAM Free Space.
 * See: wizardry/debug/src/debug-text-sram.c
 */
#define CONFIG_USE_DEBUG_TEXT

/**
 * Disable vanilla BWL entry so that we may get (0x46 *0x10) auto savable Free-RAM-Space
 */
#define CONFIG_NULL_BWL

/**
 * Let unit support data saved in BWL table, need CONFIG_NULL_BWL defined
 */
#ifdef CONFIG_NULL_BWL
    #define CONFIG_BWL_SUPPORT
#endif

/**
 * Enable unit skill judgement via ram list.
 */
#define CONFIG_SKILL_RAM_LIST

/**
 * 
 * Since the physical memory is unit->supports[],
 * so we need ensure BWL_SUPPORT config is open.
 */
#ifdef CONFIG_SKILL_RAM_LIST
    #ifdef CONFIG_BWL_SUPPORT
        #define CONFIG_SKILL_RAM_LIST_SUPPORT
    #endif
#endif

/**
 * Enable chapter-based random number system.
 * This means you will get RNG that can only be changed if restart chapter
 */
#define CONFIG_RNG_EXT


/**
 * Icon-rework getter
 */
#define ICON_SHEET_COUNT 4

/**
 * Max status for unit status-getter
 */
#define UNIT_MAX_STATUS 128

/**
 * Max status for battle-system pre-battle-calc
 */
#define BATTLE_MAX_STATUS 0x7FFF

/**
 * Skip game intro movie
 */
#define CONFIG_SKIP_INTRO

/**
 * Enable all chapters get accress to prep-screen
 */
#define CONFIG_ALL_CHAPTER_PREP

#endif /* _CONFIG_H */
