#include <gba.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mapped.h"
#include "tiles.h"

int main(void)
{
	s16 x = 0;
	s16 y = 0;

	// interrupt initialize and enable vblank
	irqInit();
	irqEnable(IRQ_VBLANK);
	
	// load palette
	memcpy(BG_PALETTE, tilesPal, tilesPalLen);
	// load tiles
	memcpy(CHAR_BASE_BLOCK(0), tilesTiles, tilesTilesLen);
	// load map
	memcpy(SCREEN_BASE_BLOCK(10), bgMap, bgMapLen);

	// set display mode
	REG_BG0CNT = CHAR_BASE(0) | SCREEN_BASE(10) | BG_256_COLOR | BG_SIZE_0;
	REG_DISPCNT = MODE_0 | BG0_ON;
	REG_BG0HOFS = x;
	REG_BG0VOFS = y;

	setRepeat(1,1);

	while(1)
	{
		scanKeys();
		u16 keystate = keysDownRepeat();
		// Up
		if (keystate & KEY_UP)
			y -= 1;
		// Down
		else if (keystate & KEY_DOWN)
			y += 1;
		// Left
		if (keystate & KEY_LEFT)
			x -= 1;
		// Right
		if (keystate & KEY_RIGHT)
			x += 1;
		
		REG_BG0HOFS = x;
		REG_BG0VOFS = y;
		
		VBlankIntrWait();
	}

	return 0;
}