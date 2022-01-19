#pragma once

#define MAX_SIMULTANEOUS_ICONS 0x20

// Vanilla Rework
int GetIconChr(int icon);
void PutIconObjImg(int icon, int tile);
void ClearIcons(void);
void ClearIcon(unsigned icon);

// User function
const void* GetIconGfx(unsigned icon);
