//======================================================================
//
//	background, 128x128@4, 
//	+ palette 16 entries, not compressed
//	+ 89 tiles (t|f|p reduced) not compressed
//	+ affine map, not compressed, 16x16 
//	Total size: 32 + 2848 + 256 = 3136
//
//	Time-stamp: 2016-09-22, 19:23:01
//	Exported by Cearn's Usenti v1.7.3
//	(comments, kudos, flames to "daytshen@hotmail.com")
//
//======================================================================

#ifndef __BACKGROUND__
#define __BACKGROUND__

#define backgroundPalLen 32
extern const unsigned short backgroundPal[16];

#define backgroundTilesLen 2848
extern const unsigned short backgroundTiles[1424];

#define backgroundMapLen 256
extern const unsigned short backgroundMap[128];

#endif // __BACKGROUND__

