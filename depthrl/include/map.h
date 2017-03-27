#ifndef MAP_H
#define MAP_H

#define MAP_HEIGHT          32
#define MAP_WIDTH           MAP_HEIGHT
#define MAP_BUFFER_HEIGHT   32
#define MAP_BUFFER_WIDTH    MAP_BUFFER_HEIGHT

// TILES
#define TILE_A      16
#define TILE_B      TILE_A+1
#define TILE_C      TILE_B+1
#define TILE_D      TILE_C+1
#define TILE_E      TILE_D+1
#define TILE_F      TILE_E+1
#define TILE_G      TILE_F+1
#define TILE_H      TILE_G+1
#define TILE_I      TILE_H+1
#define TILE_J      TILE_I+1
#define TILE_K      TILE_J+1
#define TILE_L      TILE_K+1
#define TILE_M      TILE_L+1
#define TILE_N      TILE_M+1
#define TILE_O      TILE_N+1
// dungeon features
#define TILE_SPACE      15 // .
#define TILE_WALL       3  // #
// items
#define TILE_POTION     2  // !
#define TILE_MONEY      4  // $
#define TILE_FOOD       5  // %
#define TILE_TRAP       6  // ^
#define TILE_WAND       7  // /
#define TILE_GEM        8  // *
#define TILE_RING       13 // =
// creatures
#define TILE_PLAYER     2  // @


u8 generatemap(u16 map[MAP_WIDTH][MAP_HEIGHT]);

u8 loadmap(u16 map[MAP_WIDTH][MAP_HEIGHT]);

#endif
