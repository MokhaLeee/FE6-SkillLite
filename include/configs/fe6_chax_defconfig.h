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

/**
 * Free RAM Space in SRAM
 * Note that these data can only be accessed via function:
 * WriteAndVerifySramFast() & ReadSramFast()
 */
#define FreeSRAMSpace 0x0E008000
#define DebugTextSramSt_ptr 0x0E008000
#define DebugTextSramSt_End 0x0E00A028

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
 * Icon-rework getter
 */
#define ICON_SHEET_COUNT 4

#endif /* _CONFIG_H */
