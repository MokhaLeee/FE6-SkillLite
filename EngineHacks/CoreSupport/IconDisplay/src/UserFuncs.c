#include "hardware.h"
#include "move.h"
#include "constants/video-global.h"

// #include "icon.h"
#include "IconDisplay.h"


#define ICON_SHEET(icon) (((icon) >> 8) & 0xFF)
#define ICON_INDEX(icon) ((icon) & 0xFF)



const void* GetIconGfx(unsigned icon)
{
	typedef const void* (*GetIconFunc) (int id);
	extern GetIconFunc const IconGetters[];
	
	return IconGetters[ICON_SHEET(icon)](ICON_INDEX(icon));
}

const void* GetVanillaIconGfx(unsigned id)
{
	extern u8 const Img_Icons[];
	
	return Img_Icons + (id * CHR_SIZE * 4);
}