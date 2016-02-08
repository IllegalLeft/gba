
#include <gba_console.h>
#include <gba_video.h>
#include <gba_sprites.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "samtools.h"
#include "mouse.h"


// Object 'shadow' buffer
OBJATTR obj_buffer[128];
OBJAFFINE *const obj_aff_buffer = (OBJAFFINE*)obj_buffer;

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

	// set display mode 0, 1D mapping
	REG_DISPCNT = MODE_0 | OBJ_1D_MAP;
	
	// copy sprites to appropriate memory spots
	memcpy(SPRITE_PALETTE, mousePal, mousePalLen);
	memcpy(SPRITE_GFX, mouseTiles, mouseTilesLen);
	
	// init sprite attribute data
	oam_init(obj_buffer, 128);
	
	// enable sprites
	REG_DISPCNT |= OBJ_ON | OBJ_WIN_ENABLE;
	
	int x = (SCREEN_WIDTH - 32) / 2;
	int y = (SCREEN_HEIGHT - 32) / 2;
	
	// set up OAM for sprites
	// mouse
	obj_buffer[0].attr0 = (y & 0x00ff) | ATTR0_COLOR_256 | ATTR0_SQUARE;
	obj_buffer[0].attr1 = (x & 0x00ff) | ATTR1_SIZE_32;
	obj_buffer[0].attr2 = 0;
	oam_copy(OAM, obj_buffer, 1);

	while (1)
	{
		// read x & y
		y = obj_buffer[0].attr0 & 0x00FF;
		x = obj_buffer[0].attr1 & 0x01FF;

		// check keypad
		int keystate = ~REG_KEYINPUT;
		// movement
		if (keystate & KEY_LEFT)
			x -= 1;
		else if (keystate & KEY_RIGHT)
			x += 1;
		if (keystate & KEY_UP)
			y -= 1;
		else if (keystate & KEY_DOWN)
			y += 1;
		// flips
		if (keystate & KEY_A)
			obj_buffer[0].attr1 ^= OBJ_HFLIP;
		if (keystate & KEY_B)
			obj_buffer[0].attr1 ^= OBJ_VFLIP;

		
		// write x & y
		obj_buffer[0].attr0 = (obj_buffer[0].attr0 &~ 0x00FF) | (y & 0x00FF);
		obj_buffer[0].attr1 = (obj_buffer[0].attr1 &~ 0x01FF) | (x & 0x01FF);

		oam_copy(OAM, obj_buffer, 1);

		VBlankIntrWait();
	}
	
	return 0;
}


