#include <string.h>

//#include <gba.h>
#include <tonc.h>

#include <base.h>
#include <map.h>
//#include <random.h>
#include <things.h>

u8 generatemap(u16 map[MAP_WIDTH][MAP_HEIGHT]) {
    u16 tilestodig = 340;
    u16 x = MAP_WIDTH/2;
    u16 y = MAP_HEIGHT/2;
    u16 direction;

    // Random direction mole map digger
    while (tilestodig > 0) {
        // pick a random direction
        direction = qran_range(0,3);
        if (direction == 0)
            x += 1;
        else if (direction == 1)
            x -= 1;
        else if (direction == 2)
            y += 1;
        else if (direction == 3)
            y -= 1;

        // bound x and y into the map
        if (x >= (MAP_WIDTH-2))
            x = 0;
        if (x < 1)
            x = 1;
        if (y > (MAP_HEIGHT-2))
            y = 0;
        if (y < 1)
            y = 1;

        // dig tile if need be
        if (map[x][y] == TILE_WALL) {
            map[x][y] = TILE_SPACE;
            tilestodig--;
        }
    }
    // up stairs
    map[MAP_HEIGHT/2][MAP_WIDTH/2] = TILE_STAIRSUP;

    return 1;
}

u8 loadmap(u16 map[MAP_WIDTH][MAP_HEIGHT]) {
    u8 tile;
    u8 final_map[MAP_WIDTH][MAP_HEIGHT];
    u16 map_buffer[4][MAP_BUFFER_WIDTH][MAP_BUFFER_HEIGHT];
    u8 sbb = 0; // screen base block
    u8 j, i;

    // TODO: map vision
    // load tiles into final map
    for (j = 0; j < MAP_HEIGHT; j++) {
        for (i = 0; i < MAP_HEIGHT; i++) {
            final_map[j][i] = map[j][i];
        }
    }
    // load items into final map
    for (i = 0; i < BUFLEN_ITEM; i++) {
        if (item[i].type > 0) {
            final_map[item[i].y][item[i].x] = item[i].type;
        }
    }
    // load enemies into final map
    for (i = 0; i < BUFLEN_CREATURE; i++) {
        if (creature[i].hp > 0) {
            final_map[creature[i].y][creature[i].x] = creature[i].type;
        }
    }
    // load player into final map
    final_map[player.y][player.x] = TILE_PLAYER;
    // load finalmap tiles into buffer
    for (j = 0; j < MAP_HEIGHT; j++) {
        for (i = 0; i < MAP_WIDTH; i++) {
            sbb = (j / 16)*2 + (i / 16);
            tile = final_map[j][i];
            map_buffer[sbb][((j%16)*2)+0][((i%16)*2)+0] = (tile * 4) + 1;
            map_buffer[sbb][((j%16)*2)+0][((i%16)*2)+1] = (tile * 4) + 2;
            map_buffer[sbb][((j%16)*2)+1][((i%16)*2)+0] = (tile * 4) + 3;
            map_buffer[sbb][((j%16)*2)+1][((i%16)*2)+1] = (tile * 4) + 4;
        }
    }

    // load into mapbase memory
    //memcpy(MAP_BASE_ADR(MAPBASE), map_buffer[0], sizeof(map_buffer[0]));
    //memcpy(MAP_BASE_ADR(MAPBASE)+sizeof(map_buffer[0]), map_buffer[1], sizeof(map_buffer[1]));
    //memcpy(MAP_BASE_ADR(MAPBASE)+sizeof(map_buffer[0])*2, map_buffer[2], sizeof(map_buffer[2]));
    //memcpy(MAP_BASE_ADR(MAPBASE)+sizeof(map_buffer[0])*3, map_buffer[3], sizeof(map_buffer[3]));
    memcpy(se_mem[MAPBASE], map_buffer[0], sizeof(map_buffer[0]));
    memcpy(se_mem[MAPBASE+1], map_buffer[1], sizeof(map_buffer[1]));
    memcpy(se_mem[MAPBASE+2], map_buffer[2], sizeof(map_buffer[2]));
    memcpy(se_mem[MAPBASE+3], map_buffer[3], sizeof(map_buffer[3]));

    return 0;
}
