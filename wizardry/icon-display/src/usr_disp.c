#include "common-chax.h"
#include "icon.h"
#include "constants/videoalloc_global.h"

#include "icon-rework.h"

typedef const void* (*IconGetter) (int id);
extern IconGetter const IconGetters[];

extern u8 const Img_Icons[];

const void* GetIconGfx(unsigned icon)
{
    if (icon >= 0 && ICON_SHEET(icon) < ICON_SHEET_COUNT)
        return IconGetters[ICON_SHEET(icon)](ICON_INDEX(icon));
    
    return NULL;
}

const void* GetVanillaIconGfx(unsigned id)
{
    return Img_Icons + (id * CHR_SIZE * 4);
}
