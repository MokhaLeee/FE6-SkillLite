#include "common-chax.h"
#include "icon.h"
#include "constants/videoalloc_global.h"

#include "icon-rework.h"

typedef const void* (*IconGetter) (int id);
extern IconGetter const IconGetters[];

extern u8 const Img_Icons[];

const void* GetIconGfx(unsigned icon)
{
    return IconGetters[ICON_SHEET(icon)](ICON_INDEX(icon));
}

const void* GetVanillaIconGfx(unsigned id)
{
    return Img_Icons + (id * CHR_SIZE * 4);
}