#include <gba.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "characters.h"
#include "tiles.h"

OBJATTR obj_buffer[128] ;
OBJAFFINE *const  obj_aff_buffer = (OBJAFFINE*)obj_buffer;

void oam_copy(OBJATTR *dst, const OBJATTR *src, uint count) {

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

void init_oam(OBJATTR *obj, u32 count) {
    u32 nn = count;
    u32 *dst = (u32*)obj;

    // Hide each object
    while (nn--)
    {
        *dst++ = OBJ_DISABLE;
        *dst++ = 0;
    }

    oam_copy(OAM, obj, count);
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
	
	//// Load gfx
	// map
	// load in map palette
	memcpy(BG_PALETTE, tilesPal, tilesPalLen);
	// load in map tiles
	memcpy(MAP_BASE_ADR(0), tilesTiles, tilesTilesLen);
	// load in map
	memcpy(MAP_BASE_ADR(20), tilesMap, tilesMapLen);
	// sprites
	// load in sprites palette
	memcpy(SPRITE_PALETTE, charactersPal, charactersPalLen);
	// load in sprite tiles
	memcpy(SPRITE_GFX, charactersTiles, charactersTilesLen);
	
	// OAM
	init_oam(obj_buffer, 128);
	
	// set video up
	REG_DISPCNT = MODE_0 | BG0_ON | OBJ_ON | OBJ_1D_MAP;
	REG_BG0CNT = BG_256_COLOR | BG_SIZE_0 | CHAR_BASE(0) | SCREEN_BASE(20);
	
	// set background
	u16 map_x = 0;
	u16 map_y = 0;
	REG_BG0VOFS = map_y;
	REG_BG0HOFS = map_x;
	
	// set up sprites
	u32 character = 0;
	u32 direction = 0; // 0 - down, 1 - up, 2 - left, 3 - right
	obj_buffer[0].attr0 = OBJ_Y((SCREEN_HEIGHT/2)-8) | ATTR0_COLOR_256 | ATTR0_NORMAL | ATTR0_SQUARE | OBJ_TRANSLUCENT;
	obj_buffer[0].attr1 = OBJ_X((SCREEN_WIDTH/2)-8) | ATTR1_SIZE_16;
	obj_buffer[0].attr2 = OBJ_CHAR((8*character)+(16*direction));
	

	// update OAM
	oam_copy(OAM, obj_buffer, 128);

	setRepeat(1,1);

	while (1) {
		scanKeys();
		u16 keysdown = keysDown();
		u16 keysrepeat = keysDownRepeat(); 
		
		// KeysDown
		// L
		if (keysdown & KEY_L)
			character -= 8;
		// R
		else if (keysdown & KEY_R)
			character += 8;

		// LEFT
		if (keysrepeat & KEY_LEFT) {
			direction = 3;
			map_x -= 1;
		}
		// DOWN
		else if (keysrepeat & KEY_RIGHT) {
			direction = 2;
			map_x += 1;
		}
		// UP
		if (keysrepeat & KEY_UP) {
			direction = 1;
			map_y -= 1;
		}
		// DOWN
		else if (keysrepeat & KEY_DOWN)	{
			direction = 0;
			map_y += 1;
		}
	
		REG_BG0VOFS = map_y;
		REG_BG0HOFS = map_x;
	
		obj_buffer[0].attr2 = OBJ_CHAR((8*character)+(16*direction));
		oam_copy(OAM, obj_buffer, 1);
	
		VBlankIntrWait();
	}
}


