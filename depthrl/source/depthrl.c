#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <gba.h>
#include <tonc.h>

#include "base.h"
//#include "tools.h"
#include "map.h"
//#include "random.h"
#include "things.h"
// images
#include "tiles.h"



int main(void) {
    // plain ol' map array for JUST the map
    u16 map[MAP_WIDTH][MAP_HEIGHT];

    // screen view offsets
    u16 hofs;
    u16 vofs;

    u16 keys;

    struct tempdest {
        s8 x;
        s8 y;
    } dest;


    // load palette
    memcpy(pal_bg_mem, tilesPal, tilesPalLen);
    // load tiles
    memcpy(se_mem[TILEBASE], tilesTiles, tilesTilesLen);

    irq_init(NULL);
    irq_add(II_VBLANK, NULL);

    // set up map and buffer
    // setup map
    for (u8 j = 0; j < MAP_HEIGHT; j++) {
        for (u8 i = 0; i < MAP_WIDTH; i++) {
            map[i][j] = TILE_WALL;
        }
    }

    // set key repeat
    key_repeat_limits(1,1);

    REG_DISPCNT = DCNT_MODE0 | DCNT_BG1;
    // text
    tte_init_se(1, BG_CBB(2) | BG_SBB(31), 0x0000, CLR_RED, 14, &fwf_default, NULL);
    // text box
    //se_rect(&se_mem[31], 0, 0, 30, 3, 2);
    //se_fill(&se_mem[31],2);
    //se_plot(&se_mem[31],0,0,3);
    //se_window(&se_mem[31], 0, 0, 30, 3, 3);

    // set random seed somewhat randomly with a key press that will not be the
    // same everytime
    tte_write("Press any key . . .");
    while (1) {
        sqran(qran());

        key_poll();
        keys = key_curr_state();
        if (keys)
            break;
    }
    tte_write("#{es}");

    // set up video registers
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1;// | DCNT_WIN0;
    REG_BG0CNT = BG_CBB(TILEBASE) | BG_SBB(MAPBASE) | BG_4BPP | BG_SIZE3 | BG_PRIO(1);
    //REG_BG1CNT = BG_PRIO(0);

    /*
    REG_WININ = WIN_BG0;
    REG_WIN0H = 0 << 8 | 240;
    REG_WIN0V = 16 << 8 | 160;
    */

    player.x = MAP_WIDTH / 2;
    player.y = MAP_HEIGHT / 2;
    // center screen on player's x/y
    //vofs = player.y - (SCREEN_HEIGHT/2) + 8;
    //hofs = player.x - (SCREEN_WIDTH/2) + 8;

    //test enemy
    creature[0].type = TILE_Z;
    creature[0].hp = 10;
    creature[0].x = 10;
    creature[0].y = 10;
    creature[0].attack = 100;
    creature[0].speed = 10;
    creature[0].turn = 0;

    generatemap(map);
    loadmap(map);

    // center screen on player's x/y
    vofs = player.y*16 - (SCREEN_HEIGHT/2) + 8;
    hofs = player.x*16 - (SCREEN_WIDTH/2) + 8;
    REG_BG0HOFS = hofs;
    REG_BG0VOFS = vofs;

    // game loop
    while (1) {
        // reset destination to where player is currently
        dest.x = player.x;
        dest.y = player.y;

        // take enemy turns
        //for (int i = 0; i < BUFLEN_CREATURE; i++) {
        //    if (creature[i].hp > 0) {
        //        // AI
        //    }
        //}
        // Waiting for player's turn loop
        while (1) {
            //scanKeys();
            key_poll();
            //keys = keysDown();
            keys = key_hit(KEY_FULL);

            // movement
            if (keys & KEY_UP)
                dest.y--;
            if (keys &  KEY_DOWN)
                dest.y++;
            if (keys & KEY_LEFT)
                dest.x--;
            if (keys & KEY_RIGHT)
                dest.x++;
            if (keys & KEY_DIR)
                break;
        }
        // restrict x/y
        if (dest.x < 0) dest.x = 0;
        else if (dest.x >= MAP_WIDTH) dest.x = MAP_WIDTH - 1;
        if (dest.y < 0) dest.y = 0;
        else if (dest.y >= MAP_HEIGHT) dest.y = MAP_HEIGHT - 1;
        // check if tile is passable
        if (map[dest.y][dest.x] != TILE_WALL) {
            // move
            player.x = dest.x;
            player.y = dest.y;
        }

        loadmap(map);

        // a few VBlanks so that it seems to lag behind a little
        VBlankIntrWait();
        VBlankIntrWait();
        VBlankIntrWait();
        VBlankIntrWait();
        VBlankIntrWait();
        VBlankIntrWait();

        // center screen on player's x/y
        vofs = player.y*16 - (SCREEN_HEIGHT/2) + 8;
        hofs = player.x*16 - (SCREEN_WIDTH/2) + 8;

        REG_BG0HOFS = hofs;
        REG_BG0VOFS = vofs;
    }
}


