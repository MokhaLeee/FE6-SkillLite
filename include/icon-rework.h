#pragma once

#define MAX_SIMULTANEOUS_ICONS 0x20

#define ICON_SHEET(icon) (((icon) >> 8) & 0xFF)
#define ICON_INDEX(icon) ((icon) & 0xFF)

typedef const void* (*GetIconFunc) (int index);
extern GetIconFunc const IconGetters[];

const void* GetIconGfx(unsigned icon);
