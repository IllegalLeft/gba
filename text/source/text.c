#include <stdio.h>

#include <tonc.h>

int main(void) {

    // setup display
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

    //irqInit();
    //IRQ_INIT();
    //irqEnable(IRQ_VBLANK);
    //irq_add(II_VBLANK, NULL);
 
    tte_init_chr4c_default(0, BG_CBB(0) | BG_SBB(31));
    tte_write("#{P:72,64}");        // Goto (72, 64).
    tte_write("Hello World!");      // Print "Hello world!"
    
    while (1) {
        //VBlankIntrWait();
    }
}


