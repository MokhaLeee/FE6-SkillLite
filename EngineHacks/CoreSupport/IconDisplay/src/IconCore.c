#include "hardware.h"
#include "move.h"
#include "constants/video-global.h"

// #include "icon.h"
#include "IconDisplay.h"

static inline u16 IconSlot2Chr(int num);
static unsigned GetIconUsedSlot(unsigned icon);
static unsigned GetIconNewSlot(unsigned icon);

enum { MAX_ICON_COUNT = 160 };
enum { MAX_ICON_DISPLAY_COUNT = 0x20 };

typedef struct IconSt IconSt;
struct IconSt {
    /* 00 */ u8 refCount;
    /* 01 */ u8 dispId;
};

extern u8 const Img_Icons[];
extern u16 const Pal_Icons[];

extern struct IconSt sIconStTable[MAX_ICON_COUNT];
extern u8 sIconDisplayList[MAX_ICON_DISPLAY_COUNT];


/* 
void PutIcon(u16* tm, int icon, int tileref)
{
    if (icon < 0)
    {
        tm[0x00] = 0;
        tm[0x01] = 0;
        tm[0x20] = 0;
        tm[0x21] = 0;
    }
    else
    {
        u16 tile = GetIconChr(icon) + tileref;

        tm[0x00] = tile++;
        tm[0x01] = tile++;
        tm[0x20] = tile++;
        tm[0x21] = tile;
    }
} 
*/


int GetIconChr(int icon)
{
	unsigned slot, tile;
	// Check if icon is already loaded
	slot = GetIconUsedSlot(icon);

	if ( slot )
		return IconSlot2Chr(slot);

	// Register new icon
	slot = GetIconNewSlot(icon);
	tile = IconSlot2Chr(slot);

	// Register icon graphics
    RegisterVramMove(
		GetIconGfx(icon),
        VRAM + CHR_SIZE * tile, 
		CHR_SIZE * 4);

    return tile;
}


void ClearIcons(void)
{
	CpuFill32(-1, &sIconStTable, MAX_SIMULTANEOUS_ICONS * sizeof(u16));
}


void ClearIcon(unsigned icon)
{
	u16* it;
	u16* head = (u16*)&sIconStTable;
	u16* end = head + MAX_SIMULTANEOUS_ICONS;

	for (it = head; it != end; ++it) {
		if (*it == icon) {
			*it = -1;
			break;
		}
	}
}


void PutIconObjImg(int icon, int tile)
{
	void* target = OBJ_VRAM0 + (tile * 0x20);

	if (icon >= 0) {
		const void* source = GetIconGfx(icon);

		RegisterDataMove(source,        target,         0x40);
		RegisterDataMove(source + 0x40, target + 0x400, 0x40);
	} else {
		// no icon, we clear the target graphics
		RegisterDataFill(0, target,         0x40);
		RegisterDataFill(0, target + 0x400, 0x40);
	}
}




static inline u16 IconSlot2Chr(int num)
{
    return BGCHR_ICON_END - num * 4;
}


/* 
int GetNewIconSlot(int icon)
{
    int i;

    for (i = 0; i < MAX_ICON_DISPLAY_COUNT; ++i)
    {
        if (sIconDisplayList[i] == 0)
        {
            sIconDisplayList[i] = icon + 1;
            return i;
        }
    }

    return -1;
} */

static unsigned GetIconUsedSlot(unsigned icon)
{
	u16* it;
	u16* head = (u16*)&sIconStTable;
	u16* end = head + MAX_SIMULTANEOUS_ICONS;
	

	for (it = head; it != end; ++it)
		if (*it == icon)
			return (it - head) + 1;

	return 0;
}

static unsigned GetIconNewSlot(unsigned icon)
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
