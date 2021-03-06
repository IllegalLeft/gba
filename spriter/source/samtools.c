/*
	Sam's Tools
*/

#include <stdio.h>
#include <stdlib.h>

#include <gba_sprites.h>


// oam_init
// used to initialize the OAM
void oam_init(OBJATTR *obj, uint count)
{
	u32 *dst = (u32*) obj;
    int i;
	
	// Hide each object
	for (i = 0; i < count; i++)
	{
		*dst++ = OBJ_DISABLE; //hidden by default
		*dst++ = 0;
	}
	
	oam_copy(OAM, obj, count);
}
// oam_copy
// used to copy attributes to the OAM
void oam_copy(OBJATTR *dst, const OBJATTR *src, uint count)
{

// NOTE: while struct-copying is the Right Thing to do here, 
//   there's a strange bug in DKP that sometimes makes it not work
//   If you see problems, just use the word-copy version.
#if 1
    while(count--)
        *dst++ = *src++;
#else
    u32 *dstw= (u32*)dst, *srcw= (u32*)src;
    while(count--)
    {
        *dstw++ = *srcw++;
        *dstw++ = *srcw++;
    }
#endif

}
