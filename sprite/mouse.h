//======================================================================
//
//	mouse, 64x64@8, 
//	+ palette 256 entries, not compressed
//	+ 64 tiles 8x8 metatiles not compressed
//	Total size: 512 + 4096 = 4608
//
//	Time-stamp: 2016-01-25, 17:29:28
//	Exported by Cearn's Usenti v1.7.3
//	(comments, kudos, flames to "daytshen@hotmail.com")
//
//======================================================================

#ifndef __MOUSE__
#define __MOUSE__

#define mousePalLen 512
extern const unsigned short mousePal[256];

#define mouseTilesLen 4096
extern const unsigned short mouseTiles[2048];

#endif // __MOUSE__

