//======================================================================
//
//	tiles, 128x128@8, 
//	+ palette 256 entries, not compressed
//	+ 256 tiles not compressed
//	Total size: 512 + 16384 = 16896
//
//	Time-stamp: 2016-01-30, 15:54:03
//	Exported by Cearn's Usenti v1.7.3
//	(comments, kudos, flames to "daytshen@hotmail.com")
//
//======================================================================

#ifndef __TILES__
#define __TILES__

#define tilesPalLen 512
extern const unsigned short tilesPal[256];

#define tilesTilesLen 16384
extern const unsigned short tilesTiles[8192];

#endif // __TILES__

