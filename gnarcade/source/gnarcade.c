#include <gba.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "logo.h"
#include "background.h"
#include "sinlut.h"

OBJATTR obj_buffer[128];
OBJAFFINE *const obj_aff_buffer = (OBJAFFINE*)obj_buffer;


// Sine/cosine lookups. 
// NOTE: theta's range is [0, 0xFFFF] for [0,2π⟩, just like the 
// BIOS functions
//! Look-up a sine value
static inline s32 lu_sin(u32 theta)
{   return sin_lut[(theta>>7)&0x1FF];   }

//! Look-up a cosine value
static inline s32 lu_cos(u32 theta)
{   return sin_lut[((theta>>7)+128)&0x1FF]; }

int main(void) {

	// init OAM
	oam_init(obj_buffer, 128);

	// load palettes
	memcpy(SPRITE_PALETTE, logoPal, logoPalLen);
	memcpy(BG_PALETTE, backgroundPal, backgroundPalLen);
	
	// load tiles
	memcpy(SPRITE_GFX, logoTiles, logoTilesLen);
	memcpy(TILE_BASE_ADR(0), backgroundTiles, backgroundTilesLen);

    // load map
    memcpy(MAP_BASE_ADR(4), backgroundMap, backgroundMapLen);
	
	u16 logo_x = (SCREEN_WIDTH/2) - 64;
	u16 logo_y = (SCREEN_HEIGHT/2) - 64;
	
	obj_buffer[0].attr0 = OBJ_Y(logo_y) | ATTR0_NORMAL | ATTR0_COLOR_16 | OBJ_ROT_SCALE_ON | OBJ_DOUBLE;
	obj_buffer[0].attr1 = OBJ_X(logo_x) | ATTR1_SIZE_64;
	obj_buffer[0].attr2 = OBJ_SQUARE;
	u16 aa, ab, ac, ad;
	aa = 0x07ff;
	ab = 0;
	ac = 0;
	ad = 0x07ff;
	obj_aff_buffer[0].pa = aa;
	obj_aff_buffer[0].pb = ab;
	obj_aff_buffer[0].pc = ac;
	obj_aff_buffer[0].pd = ad;

	oam_copy(OAM, obj_buffer, 4);

	irqInit();
	irqEnable(IRQ_VBLANK);
	
	// set up screen
	REG_DISPCNT = MODE_0 | OBJ_ON | OBJ_1D_MAP | BG2_ON;

    // set up bg2
    REG_BG2CNT = BG_TILE_BASE(0) | BG_MAP_BASE(4) | BG_SIZE(0) | BG_WRAP;
    s32 bg2_x, bg2_y, bgangle;
    bg2_x = 0;
    bg2_y = 0;
    bgangle = 0;
    REG_BG2VOFS = bg2_x;
    REG_BG2HOFS = bg2_y;
    REG_BG2PA = 1;
    REG_BG2PB = 0;
    REG_BG2PC = 0;
    REG_BG2PD = 1;
	
	// sweep in
	for (int i = 0x07ff; i > 0x07f; i -= 15) {
		aa = i;
		ab = 0;
		ac = 0;
		ad = i;
		
		obj_aff_buffer[0].pa = aa;
		obj_aff_buffer[0].pb = ab;
		obj_aff_buffer[0].pc = ac;
		obj_aff_buffer[0].pd = ad;

        // rotate bg in circle pattern
        bg2_x = lu_sin(bgangle)/15;
        bg2_y = lu_cos(bgangle)/15;
        REG_BG2HOFS = bg2_x;
        REG_BG2VOFS = bg2_y;
        bgangle += 100;
		
		oam_copy(OAM, obj_buffer, 4);

		VBlankIntrWait();
	}


	// bounce around
	u16 rot = 10; // 0 - 40
	aa = 0x007f;
	ab = 0;
	ac = 0;
	ad = 0x007f;
	while (1) {
        // rotate bg in circle pattern
        bg2_x = lu_sin(bgangle)/15;
        bg2_y = lu_cos(bgangle)/15;
        REG_BG2HOFS = bg2_x;
        REG_BG2VOFS = bg2_y;
        bgangle += 100;

		//logo rotation
		if (rot >= 20) {
			aa -= 0;
			ab += 1;
			ac -= 1;
			ad -= 0;
		}
		else {
			aa += 0;
			ab -= 1;
			ac += 1;
			ad += 0;
		}
		rot++;
		if (rot == 40)
			rot = 0;
			
		obj_buffer[0].attr0 |= OBJ_Y(logo_y) & 0x00ff;
		obj_buffer[0].attr1 |= OBJ_X(logo_x) & 0x01ff;
		obj_aff_buffer[0].pa = aa;
		obj_aff_buffer[0].pb = ab;
		obj_aff_buffer[0].pc = ac;
		obj_aff_buffer[0].pd = ad;
		
		oam_copy(OAM, obj_buffer, 4);
        
		VBlankIntrWait();
	}
}


