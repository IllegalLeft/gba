/*
 * Things.h
 *
 * Just a lotta things... ya know?
 */

#ifndef THINGS_H
#define THINGS_H

#define BUFLEN_CREATURE     32
#define BUFLEN_ITEM         32

struct character {
    u8 x;
    u8 y;
    u8 hp;
    u8 speed;
    u8 turn;
    u8 level;
    u8 floor;
    u16 money;
} player;

// creatures list (other than player)
struct being {
    u8 type;
    s8 x;
    s8 y;
    u8 hp;
    u8 attack;
    u8 speed;
    u8 turn;
} creature[BUFLEN_CREATURE];

// objects
struct object {
    u8 type;
    s8 x;
    s8 y;
} item[BUFLEN_ITEM];

#endif
