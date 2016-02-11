#include <gba.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "blueslime.h"
#include "orangeslime.h"
#include "drakee.h"


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

OBJATTR obj_buffer[128];
OBJAFFINE *const obj_aff_buffer = (OBJAFFINE*)obj_buffer;


void init_oam(OBJATTR *obj, u32 count)
{
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

	// set mode 0, 1D mapping
	REG_DISPCNT = MODE_0 | OBJ_1D_MAP;

    init_oam(obj_buffer, 128);

	// copy sprites to appropriate memory spots
	u16 *palette_end = SPRITE_PALETTE;
	u16 *tiles_end =SPRITE_GFX;
	// blue slime
	memcpy(palette_end, blueslimePal, blueslimePalLen);
	memcpy(tiles_end, blueslimeTiles, blueslimeTilesLen);
	palette_end += blueslimePalLen/2;
	tiles_end += blueslimeTilesLen/2;
	// drakee
	memcpy(palette_end, drakeePal, drakeePalLen);
	memcpy(tiles_end, drakeeTiles, drakeeTilesLen);
	palette_end += drakeePalLen/2;
	tiles_end += drakeeTilesLen/2;
	// orange slime
	memcpy(palette_end, orangeslimePal, orangeslimePalLen);
	memcpy(tiles_end, orangeslimeTiles, orangeslimeTilesLen);
	palette_end += orangeslimePalLen/2;
	tiles_end += orangeslimeTilesLen/2;

	// enable sprites
	REG_DISPCNT |= OBJ_ON | OBJ_WIN_ENABLE;

	u16 x = 0;
	u16 y = 0;
	s8 sprite = 1;
	u16 status = ATTR0_NORMAL;
    u16 mosaic_v = 0;
    u16 mosaic_h = 0;


	obj_buffer[0].attr0 = (y & 0x00ff) | ATTR0_NORMAL | ATTR0_COLOR_16 | ATTR0_SQUARE;
	obj_buffer[0].attr1 = (x & 0x01ff) | ATTR1_SIZE_32;
    obj_buffer[0].attr2 = OBJ_CHAR(0);
	
	oam_copy(OAM, obj_buffer, 1);

	setRepeat(1,1);

	while (1){

		// check keypad
		scanKeys();
		u16 keystate = keysDownRepeat();
		u16 keydown = keysDown();
		// directional pad
		// move sprite
		if (keystate & KEY_LEFT)
			x -= 1;
		else if (keystate & KEY_RIGHT)
			x += 1;
		if (keystate & KEY_UP)
			y -= 1;
		else if (keystate & KEY_DOWN)
			y += 1;
		// A
		// enable/disable mosaic
        if (keydown & KEY_A) {
            if (status == ATTR0_MOSAIC)
                status = 0;
            else
                status = ATTR0_MOSAIC;
        }
		// L + R
		// change mosaic level for both V&H
        
        if (keydown & KEY_R) {
            mosaic_v += 1;
            mosaic_v &= 0x0f;
            mosaic_h += 1;
            mosaic_h &= 0x0f;
            REG_MOSAIC = (mosaic_v<<12) + (mosaic_h<<8);
		}
        else if (keydown & KEY_L) {
            mosaic_v -= 1;
            mosaic_v &= 0x0f;
            mosaic_h -= 1;
            mosaic_h &= 0x0f;
            REG_MOSAIC = (mosaic_v<<12) + (mosaic_h<<8);
		}

		// set current sprite attributes
        obj_buffer[0].attr0 = (y & 0x00ff) | status | ATTR0_COLOR_16 | ATTR0_SQUARE;
        obj_buffer[0].attr1 = (x & 0x01ff) | ATTR1_SIZE_32;
        obj_buffer[0].attr2 = OBJ_CHAR(sprite*16) | OBJ_PALETTE(sprite);

        oam_copy(OAM, obj_buffer, 1);

		VBlankIntrWait();
	}

	return 0;
}


