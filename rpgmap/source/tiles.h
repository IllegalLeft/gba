//======================================================================
//
//	tiles, 160x224@8, 
//	+ palette 256 entries, not compressed
//	+ 560 tiles 2x2 metatiles not compressed
//	Total size: 512 + 35840 = 36352
//
//	Time-stamp: 2016-02-01, 19:57:45
//	Exported by Cearn's Usenti v1.7.3
//	(comments, kudos, flames to "daytshen@hotmail.com")
//
//======================================================================

#ifndef __TILES__
#define __TILES__

#define tilesPalLen 512
extern const unsigned short tilesPal[256];

#define tilesTilesLen 35840
extern const unsigned short tilesTiles[17920];

#define tilesMapLen 2048
extern const unsigned short tilesMap[1024];

#endif // __TILES__

