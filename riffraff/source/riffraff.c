#include <gba.h>

#include "notes.h"


#define SONG_BPM    130
#define SONG_LEN    32
#define STEPS       8 // 8 steps per beat
#define SONG_TIMER  (u16)(-(SONG_BPM*8/60*16384))


u16 trax[SONG_LEN] = {
    C3,0,0,0, 0,0,0,A2,
    0,A2,C3,0, 0,0,B2,0,
    A2,0,A3,0, 0,0,0,A2,
    0,A2,E2,G2, 0,0,GS2,0
};
u8 songindex = 0;
u8 aChan = 0;

void nextnote() {
    if (trax[songindex]) {//((aChan) && (trax[songindex])) {
        SQR1CTRL = SQR_VOL(0xF) | (0 << 8) | SQR_DUTY(2) | 1;
        SQR1FREQ = (1 << 0xF) | trax[songindex];
        MODE3_FB[1][songindex] = RGB5(0, 0xff, 0);
    }
    else {
        MODE3_FB[1][songindex] = RGB5(0xff, 0, 0);
        SQR1CTRL = SQR_VOL(0x0);
    }

    // increment song index
    songindex++;
    if (songindex == SONG_LEN )
        songindex = 0;
}

int main(void) {

    u16 keys = 0;

    // Interrupts
    irqInit();
    irqEnable(IRQ_VBLANK | IRQ_TIMER2);
    irqSet(IRQ_TIMER2, nextnote);

    // Enable Video
    REG_DISPCNT = MODE_3 | BG2_ON;

    // Enable Sound
    SNDSTAT = SNDSTAT_ENABLE;
    // Set Volume
    DSOUNDCTRL = DSOUNDCTRL_DMG25;
    DMGSNDCTRL = DMGSNDCTRL_LVOL(7) | DMGSNDCTRL_RVOL(7) | DMGSNDCTRL_LSQR1 | DMGSNDCTRL_RSQR1;
    // No sweep
    SQR1SWEEP = SQR1SWEEP_OFF;
    SQR1CTRL = SQR_VOL(0xF) | (0 << 8) | SQR_DUTY(2) | 1;
    SQR1FREQ = 0;

    // Timer 2
    REG_TM2CNT_L = -0x0800;//SONG_TIMER;
    REG_TM2CNT_H = TIMER_START | TIMER_IRQ | 3;

    // keys repeat
    setRepeat(1, 1);


    while (1) {
        VBlankIntrWait();

        scanKeys();
        keys = keysDownRepeat();

        if (keys & DPAD) {
            aChan = 1;
            MODE3_FB[0][0] = RGB5(0xff,0xff,0xf);
        }
        else {
            aChan = 0;
            MODE3_FB[0][0] = RGB5(0x00,0x00,0x0);
        }
    }

    return 0;
}
