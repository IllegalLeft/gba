#include <gba.h>

void blink() {
    MODE3_FB[0][0] = ~MODE3_FB[0][0];
    MODE3_FB[0][1] = ~MODE3_FB[0][1];
    MODE3_FB[1][0] = ~MODE3_FB[1][0];
    MODE3_FB[1][1] = ~MODE3_FB[1][1];
}

int main(void) {

    irqInit();
    irqSet(IRQ_TIMER2, blink);
    irqEnable(IRQ_VBLANK | IRQ_TIMER2);

    // set screen up
    REG_DISPCNT = MODE_3 | BG2_ON;

    // set up timer
    // ~1 sec for timer 2
    REG_TM2CNT_L = -0x4000;
    REG_TM2CNT_H = TIMER_IRQ | 3;
    REG_TM2CNT_H ^= TIMER_START;

    MODE3_FB[0][5] = RGB5(0xff,0x0,0x0);


    while (1) {
        VBlankIntrWait();
    }
}
