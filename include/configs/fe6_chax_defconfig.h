#ifndef _CONFIG_H
#define _CONFIG_H

// define CONFIG_DEBUG

// FreeSpace
#define FreeSpaceBLRange 0xF635C
#define FreeSpaceTable 0x7FF0B0
#define FreeSpaceTableEnd (FreeSpaceTable + 0x2000)
#define FreeSpaceStr FreeSpaceTableEnd
#define FreeSpaceStrEnd (FreeSpaceStr + 0xF0000)
#define FreeSpaceComm FreeSpaceStrEnd

#ifndef CONFIG_DEBUG
    #define FreeRAMSpace 0x2025B8C // sDebugTextSt, size = 0x2028, end at 0x2027BB4
#endif

#define ICON_SHEET_COUNT 4

#endif
