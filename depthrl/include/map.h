#ifndef MAP_H
#define MAP_H

#define MAP_HEIGHT          32
#define MAP_WIDTH           MAP_HEIGHT
#define MAP_BUFFER_HEIGHT   32
#define MAP_BUFFER_WIDTH    MAP_BUFFER_HEIGHT

// TILES
// dungeon features
#define TILE_SPACE      6  // .
#define TILE_WALL       3  // #
// creatures
#define TILE_PLAYER     2  // @
// items
#define TILE_MONEY      4  // $
#define TILE_FOOD       5  // %


u8 generatemap(u16 map[MAP_WIDTH][MAP_HEIGHT]);

u8 loadmap(u16 map[MAP_WIDTH][MAP_HEIGHT]);

#endif
