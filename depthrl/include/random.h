#ifndef RANDOM_H
#define RANDOM_H


extern int __qran_seed;     // Seed / rnd holder


static inline int qran() {
    __qran_seed= 1664525*__qran_seed+1013904223;
    return (__qran_seed>>16) & 0x7FFF;
}
static inline int qran_range(int min, int max) {
    return (qran()*(max-min)>>15)+min;
}


int sqran(int seed);

#endif
