
#include <gba_console.h>
#include <gba_video.h>
#include <gba_sprites.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mouse.h"

#define INLINE static inline
INLINE OBJATTR *obj_set_attr(OBJATTR *obj, u16 a0, u16 a1, u16 a2);

void oam_copy(OBJATTR *dst, const OBJATTR *src, uint count)
{

// NOTE: while struct-copying is the Right Thing to do here, 
//   there's a strange bug in DKP that sometimes makes it not work
//   If you see problems, just use the word-copy version.
#if 1
    while(count--)
        *dst++ = *src++;
#else
    u32 *dstw= (u32*)dst, *srcw= (u32*)src;
    while(count--)
    {
        *dstw++ = *srcw++;
        *dstw++ = *srcw++;
    }
#endif

}


//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------


	// the vblank interrupt must be enabled for VBlankIntrWait() to work
	// since the default dispatcher handles the bios flags no vblank handler
	// is required
	irqInit();
	irqEnable(IRQ_VBLANK);

	// set mode 0, 1D mapping
	REG_DISPCNT = MODE_0 | OBJ_1D_MAP;
	
	// copy sprites to appropriate memory spots
	memcpy(SPRITE_PALETTE, mousePal, mousePalLen);
	memcpy(SPRITE_GFX, mouseTiles, mouseTilesLen);
	
	// enable sprites
	REG_DISPCNT |= OBJ_ON | OBJ_WIN_ENABLE;
	
	int x = 0;
	int y = 0;
	
	// set up OAM appropriately
	OBJATTR mouse_attr =
	{
		((y & 0x00ff) | ATTR0_NORMAL | ATTR0_COLOR_256 | ATTR0_SQUARE),
		((x & 0x01ff) | ATTR1_SIZE_32),
		0
	};
	
	while (1)
	{
		mouse_attr.attr0 = ((y & 0x00ff) | ATTR0_NORMAL | ATTR0_COLOR_256 | ATTR0_SQUARE);
		mouse_attr.attr1 = ((x & 0x01ff) | ATTR1_SIZE_32);
		oam_copy(OAM, &mouse_attr, 1);
		
		// check keypad
		int keystate = REG_KEYINPUT;
		if (!(keystate & KEY_LEFT))
			x -= 1;
		else if (!(keystate & KEY_RIGHT))
			x += 1;
		if (!(keystate & KEY_UP))
			y -= 1;
		else if (!(keystate & KEY_DOWN))
			y += 1;
	
		VBlankIntrWait();
	}
	
	return 0;
}


