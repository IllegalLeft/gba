#include <gba.h>

#define SONG_BPM    130
#define SONG_LEN    32
#define STEPS       8 // 8 steps per beat
#define SONG_TIMER  -(((SONG_BPM/STEPS)/60)/0.00006104)

#define PAUSE       0
#define NOTE_C      8013
#define NOTE_Cs     7566
#define NOTE_Db     NOTE_Cs
#define NOTE_D      7144
#define NOTE_Ds     6742
#define NOTE_Eb     NOTE_Ds
#define NOTE_E      6362
#define NOTE_F      6005
#define NOTE_Fs     5666
#define NOTE_Gb     NOTE_Fs
#define NOTE_G      5346
#define NOTE_Gs     5048
#define NOTE_Ab     NOTE_Gs
#define NOTE_A      4766
#define NOTE_As     4499
#define NOTE_Bb     NOTE_As
#define NOTE_B      4246


u16 trax[SONG_LEN] = {
    (NOTE_C>>(4+0)),0,0,0, 0,0,0,(NOTE_A>>4),
    0,NOTE_A,NOTE_C,0, 0,0,NOTE_B,0,
    NOTE_A,0,NOTE_A,0, 0,0,0,NOTE_A,
    0,NOTE_A,NOTE_E,NOTE_G, 0,0,NOTE_Gs,0
};
u8 songindex = 0;
u8 aChan = 0;

void nextnote() {
    if ((aChan) && (trax[songindex])) {
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
    REG_TM2CNT_L = -0x1155;//SONG_TIMER;
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
