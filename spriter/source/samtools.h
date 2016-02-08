/*
	Samtools
*/

#ifndef SAMTOOLS_H
#define SAMTOOLS_H

#include <gba_sprites.h>


// OAM
void oam_init(OBJATTR *obj, uint count);
void oam_copy(OBJATTR *dst, const OBJATTR *src, uint count);

#endif