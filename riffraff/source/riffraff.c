#include <string.h>

#include <gba.h>

#include "tools.h"
#include "notes.h"
#include "tracks.h"

// Images
#include "drumkit.h"
#include "bass.h"
#include "title.h"


#define SONG_BPM    130
#define SONG_LEN    32
#define STEPS       8 // 8 steps per beat
#define SONG_TIMER  (u16)(-(SONG_BPM*8/60*16384))


////////////////////////////////////////////////////////////////
// Global Variables

u16 keys = 0;

u8 songindex = 0;

bool Sqr1Play = 0;
bool Sqr2Play = 0;
bool NoisePlay = 0;

u16 *Sqr1Track;
u16 *Sqr2Track;
u16 *NoiseTrack;

OBJATTR obj_buffer[128];
OBJAFFINE *const obj_aff_buffer = (OBJAFFINE*)obj_buffer;

////////////////////////////////////////////////////////////////
// Functions
void nextnote() {
	// SQR1
    if ((Sqr1Play) && (Sqr1Track[songindex])) {
        SQR1FREQ = (1 << 0xF) | Sqr1Track[songindex];
    }
	// SQR2
	if ((Sqr2Play) && (Sqr2Track[songindex])) {
        SQR2FREQ = (3 << 0xF) | Sqr2Track[songindex];
    }
	// Noise
	if ((NoisePlay) && (NoiseTrack[songindex])) {
		switch (NoiseTrack[songindex]) {
			// Kick
			case 1:
				REG_SOUND4CNT_L = (10 << 12) | (0 << 11) | (1 << 8) | 3;
				REG_SOUND4CNT_H = (1 << 14) | (7 << 4) | (1 << 3);
				break;
			// Snare
			case 2:
				REG_SOUND4CNT_L = (10 << 12) | (0 << 11) | (2 << 8) | 3;
				REG_SOUND4CNT_H = (1 << 14) | (0 << 4) | (1 << 3);
				break;
			// Hihat close
			case 3:
				REG_SOUND4CNT_L = (10 << 12) | (0 << 11) | (1 << 8) | 3;
				REG_SOUND4CNT_H = (1 << 14) | (0 << 4) | (1 << 3);
			default:
				break;
		}

        REG_SOUND4CNT_H |= (1 << 15);
	}

    // increment song index
    songindex++;
    if (songindex == SONG_LEN )
        songindex = 0;
}

////////////////////////////////////////////////////////////////
// Game Loop
void gameLoop() {
	REG_DISPCNT = MODE_0 | BG2_ON | OBJ_ON | OBJ_1D_MAP;
	
    // load sprites for playing and show them
	memcpy(SPRITE_GFX, drumkitTiles, drumkitTilesLen);
	obj_buffer[0].attr0 = ATTR0_SQUARE | ATTR0_NORMAL | ATTR0_COLOR_16 | OBJ_Y(50);
	obj_buffer[0].attr1 = ATTR1_SIZE_64 | OBJ_X(50);
	obj_buffer[0].attr2 = ATTR2_PALETTE(0);
	
	memcpy(SPRITE_GFX+drumkitTilesLen, bassTiles, bassTilesLen);
	obj_buffer[1].attr0 = ATTR0_SQUARE | ATTR0_NORMAL | ATTR0_COLOR_16 | OBJ_Y(0);
	obj_buffer[1].attr1 = ATTR1_SIZE_64 | OBJ_X(0);
	obj_buffer[1].attr2 = ATTR2_PALETTE(0) | OBJ_CHAR(128);
	oam_copy(OAM, obj_buffer, 4);
	
	
	while (1) {
		VBlankIntrWait();

		scanKeys();
		keys = keysDownRepeat();

		Sqr1Play = 0;
		Sqr2Play = 0;
		NoisePlay = 0;
		
		MODE3_FB[0][0] = RGB5(0x00,0x00,0x0);
		if (keys & DPAD) {
			Sqr1Play = 1;
		}
		if (keys & KEY_A) {
			Sqr2Play = 1;
		}
		if (keys & KEY_R) {
			NoisePlay = 1;
		}
	}
}

////////////////////////////////////////////////////////////////
// Main
int main(void) {
	
	Sqr1Track = (u16*) &track_berniebass1c;
	Sqr2Track = (u16*) &track_pianolead2;
	NoiseTrack = (u16*) &track_4floorkick;

    // Interrupts
    irqInit();
    irqEnable(IRQ_VBLANK | IRQ_TIMER2);
    irqSet(IRQ_TIMER2, nextnote);

	//// VIDEO ////
    // Enable Video
    REG_DISPCNT = MODE_3 | BG2_ENABLE;
	// init OAM
	oam_init(obj_buffer, 128);
	// load object into OAM
	memcpy(SPRITE_PALETTE, drumkitPal, drumkitPalLen);
	
	// Load splash
	memcpy(MODE3_FB, titleBitmap, titleBitmapLen);
	

	//// SOUND ////
    // Enable Sound
    SNDSTAT = SNDSTAT_ENABLE;
    // Set Volume
    DSOUNDCTRL = DSOUNDCTRL_DMG100;
    DMGSNDCTRL = DMGSNDCTRL_LVOL(7) | DMGSNDCTRL_RVOL(7);
    // SQR 1
	DMGSNDCTRL |= DMGSNDCTRL_LSQR1;
    SQR1SWEEP = SQR1SWEEP_OFF;
    SQR1CTRL = SQR_VOL(0xF) | (1 << 8) | SQR_DUTY(2) | 1;
    SQR1FREQ = 0;
	// SQR 2
	DMGSNDCTRL |= DMGSNDCTRL_RSQR2;
	SQR2CTRL = SQR_VOL(0xF) | (3 << 8) | SQR_DUTY(0) | 1;
	SQR1FREQ = 0;
	// Noise
	DMGSNDCTRL |= DMGSNDCTRL_RNOISE | DMGSNDCTRL_LNOISE;
	REG_SOUND4CNT_L = (10 << 12) | (0 << 11) | (1 << 8) | 3;
	REG_SOUND4CNT_H = (1 << 14) | (7 << 4) | (1 << 3);
	

    // Timer 2
    REG_TM2CNT_L = -0x0800; //SONG_TIMER;
    REG_TM2CNT_H = TIMER_START | TIMER_IRQ | 3;

    // keys repeat
    setRepeat(1, 1);

	while (1) {
		VBlankIntrWait();

		scanKeys();
		keys = keysDownRepeat();
		
		if (keys & KEY_START) gameLoop();
    }
	return 0;
}
