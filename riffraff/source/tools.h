/*
	Samtools
*/

//#ifndef TOOLS_H
//#define TOOLS_H

#include <gba_sprites.h>
#include <gba_types.h>

// OAM
void oam_init(OBJATTR *obj, unsigned int count);
void oam_copy(OBJATTR *dst, const OBJATTR *src, unsigned int count);

//#endif