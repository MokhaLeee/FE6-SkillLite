#include "common-chax.h"
#include "icon.h"
#include "move.h"
#include "constants/videoalloc_global.h"
#include "icon-rework.h"

enum { MAX_ICON_COUNT = 160 };
enum { MAX_ICON_DISPLAY_COUNT = 0x20 };

struct IconSt
{
    /* 00 */ u8 ref_count;
    /* 01 */ u8 disp_id;
};
extern struct IconSt sIconStTable[MAX_ICON_COUNT];
extern u8 const Img_Icons[];

int GetIconChr(int icon);

static int GetIconUsedSlot(u16 icon)
{
    u16* it;
    u16* head = (u16 *)&sIconStTable;
    u16* end = head + MAX_SIMULTANEOUS_ICONS;
    

    for (it = head; it != end; ++it)
        if (*it == icon)
            return (it - head) + 1;

    return 0;
}

static int GetIconNewSlot(u16 icon)
{
    u16* it;
    u16* head = (u16*)&sIconStTable;
    u16* end = head + MAX_SIMULTANEOUS_ICONS;
    
    for (it = head; it != end; ++it) {
        if (*it == (u16)(-1)) {
            *it = icon;
            return (it - head) + 1;
        }
    }
    return 0;
}

static int IconSlot2Chr(int num)
{
    return BGCHR_ICON_END - num * 4;
}

LYN_REPLACE_CHECK(ClearIcons);
void ClearIcons(void)
{
    CpuFill32(-1, &sIconStTable, MAX_SIMULTANEOUS_ICONS * sizeof(u16));
}

LYN_REPLACE_CHECK(ClearIcon);
void ClearIcon(int icon)
{
    u16* it;
    u16* head = (u16 *)&sIconStTable;
    u16* end = head + MAX_SIMULTANEOUS_ICONS;

    for (it = head; it != end; ++it) {
        if (*it == icon) {
            *it = -1;
            break;
        }
    }
}

LYN_REPLACE_CHECK(GetIconChr);
int GetIconChr(int icon)
{
    int slot, tile;
    const u8 *src;

    // Check if icon is already loaded
    slot = GetIconUsedSlot(icon);
    if (0 != slot)
        return IconSlot2Chr(slot);

    // Register new icon
    slot = GetIconNewSlot(icon);
    tile = IconSlot2Chr(slot);

    // Register icon graphics
    src = GetIconGfx(icon);
    if (src) {
        RegisterVramMove(
            src,
            VRAM + CHR_SIZE * tile,
            CHR_SIZE * 4);
    } else {
        RegisterVramFill(
            0,
            VRAM + CHR_SIZE * tile,
            CHR_SIZE * 4);
    }

    return tile;
}

LYN_REPLACE_CHECK(PutIconObjImg);
void PutIconObjImg(int icon, int chr)
{
    const u8 *src = GetIconGfx(icon);
    u8 *dst = OBJ_VRAM0 + CHR_SIZE * (chr & 0x3FF);

    if (!src) {
        // no icon, we clear the target graphics
        RegisterDataFill(0, dst,         CHR_SIZE * 2);
        RegisterDataFill(0, dst + 0x400, CHR_SIZE * 2);
    } else {
        RegisterDataMove(src,                dst,         CHR_SIZE * 2);
        RegisterDataMove(src + CHR_SIZE * 2, dst + 0x400, CHR_SIZE * 2);
    }
}
