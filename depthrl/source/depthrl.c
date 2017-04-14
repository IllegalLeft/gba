#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gba.h>

#include "base.h"
#include "tools.h"
#include "map.h"
#include "random.h"
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
    memcpy(BG_PALETTE, tilesPal, tilesPalLen);
    // load tiles
    memcpy(TILE_BASE_ADR(TILEBASE), tilesTiles, tilesTilesLen);

    irqInit();
    irqEnable(IRQ_VBLANK);

    // set up map and buffer
    // setup map
    for (u8 j = 0; j < MAP_HEIGHT; j++) {
        for (u8 i = 0; i < MAP_WIDTH; i++) {
            map[i][j] = TILE_WALL;
        }
    }

    // set key repeat
    setRepeat(1,1);

    // set random seed somewhat randomly with a key press that will not be the
    // same everytime
    while (1) {
        sqran(qran());

        scanKeys();
        keys = keysDown();
        if (keys)
            break;
    }

    // set up video registers
    REG_DISPCNT = MODE_0 | BG0_ON;
    REG_BG0CNT = TILE_BASE(TILEBASE) | MAP_BASE(MAPBASE) | BG_16_COLOR | BG_SIZE(3);


    player.x = MAP_WIDTH / 2;
    player.y = MAP_HEIGHT / 2;
    // center screen on player's x/y
    vofs = player.y - (SCREEN_HEIGHT/2) + 8;
    hofs = player.x - (SCREEN_WIDTH/2) + 8;

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
            scanKeys();
            keys = keysDown();

            // movement
            if (keys & KEY_UP)
                dest.y--;
            if (keys &  KEY_DOWN)
                dest.y++;
            if (keys & KEY_LEFT)
                dest.x--;
            if (keys & KEY_RIGHT)
                dest.x++;
            if (keys & DPAD)
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


