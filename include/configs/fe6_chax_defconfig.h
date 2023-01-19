#ifndef _CONFIG_H
#define _CONFIG_H

/**
 * Enable debug log with function FailScreen() etc.
 * But since FreeRAMSpace uses debug text space (sDebugTextSt) so it will disable FreeRAMSpace.
 */
// define CONFIG_DEBUG

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
 * Free-RAM-Space
 */
#ifndef CONFIG_DEBUG
    #define FreeRAMSpace 0x2025B8C /* sDebugTextSt, size = 0x2028, end at 0x2027BB4 */
#endif /* CONFIG_DEBUG */

/**
 * Icon-rework getter
 */
#define ICON_SHEET_COUNT 4

#endif /* _CONFIG_H */
