#include <gba.h>

int main(void) {

    irqInit();
    irqEnable(IRQ_VBLANK);

    // set screen up
    REG_DISPCNT = MODE_3 | BG2_ON;

    // set up timer
    REG_TM2CNT_L = -0x4000;
    REG_TM2CNT_H = 3;
    REG_TM3CNT_H = TIMER_COUNT | TIMER_START;
    REG_TM2CNT_H ^= TIMER_START;

    MODE3_FB[0][0] = RGB5(0xff,0xff,0xf);
    MODE3_FB[0][5] = RGB5(0xff,0x0,0x0);

    u32 timer;

    while (1) {
        timer = REG_TM3CNT_L;

        if ((timer % 2) > 0) {
            MODE3_FB[0][0] = RGB5(0xff,0xff,0xf);
            MODE3_FB[0][1] = RGB5(0xff,0xff,0xf);
            MODE3_FB[1][0] = RGB5(0xff,0xff,0xf);
            MODE3_FB[1][1] = RGB5(0xff,0xff,0xf);
        }
        else
        {
            MODE3_FB[0][0] = RGB5(0,0,0);
            MODE3_FB[0][1] = RGB5(0,0,0);
            MODE3_FB[1][0] = RGB5(0,0,0);
            MODE3_FB[1][1] = RGB5(0,0,0);
        }

        VBlankIntrWait();
    }
}
