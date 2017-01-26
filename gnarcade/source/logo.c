//======================================================================
//
//	logo, 64x64@4, 
//	+ palette 8 entries, not compressed
//	+ 64 tiles not compressed
//	Total size: 16 + 2048 = 2064
//
//	Time-stamp: 2016-02-12, 15:18:21
//	Exported by Cearn's Usenti v1.7.3
//	(comments, kudos, flames to "daytshen@hotmail.com")
//
//======================================================================

const unsigned short logoPal[8]=
{
	0x01CC,0x44C6,0x5149,0x59CD,0x5E30,0x6AD5,0x777A,0x7FFF,
};

const unsigned short logoTiles[1024]=
{
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x1100,0x1111,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x1110,0x1111,0x1111,0x6421,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x1111,0x1111,0x5111,0x1677,0x7711,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x1100,0x1111,0x1111,0x3211,0x7777,0x7777,0x7777,0x7777,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x1110,0x1111,
	0x1111,0x5421,0x7111,0x7777,0x7167,0x7777,0x7177,0x7777,
	0x0000,0x0000,0x0000,0x0000,0x1110,0x1111,0x1111,0x1132,
	0x7777,0x5777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0011,0x0000,
	0x0011,0x0000,0x0111,0x0000,0x0111,0x0000,0x0111,0x0000,

	0x0000,0x1111,0x1100,0x7652,0x7110,0x7777,0x7711,0x7777,
	0x7711,0x7777,0x7741,0x7777,0x7741,0x1777,0x7741,0x1777,
	0x1111,0x1111,0x7777,0x1177,0x7777,0x5177,0x7777,0x6177,
	0x7777,0x7177,0x1245,0x7111,0x1111,0x7111,0x7765,0x7177,
	0x7731,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,
	0x7777,0x7116,0x7777,0x7116,0x7777,0x7116,0x7777,0x7116,
	0x7777,0x7711,0x7777,0x7754,0x7777,0x7754,0x7777,0x7754,
	0x7777,0x7754,0x7777,0x7754,0x7777,0x7754,0x7777,0x7754,

	0x7777,0x7777,0x7777,0x7777,0x1377,0x7771,0x1277,0x7771,
	0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,
	0x7177,0x7777,0x7177,0x7777,0x7177,0x7777,0x7177,0x7777,
	0x7177,0x7777,0x7177,0x7777,0x7177,0x7777,0x7177,0x7777,
	0x7567,0x7777,0x7114,0x7777,0x7777,0x7777,0x7777,0x1777,
	0x7777,0x2777,0x7777,0x7777,0x7457,0x7777,0x7114,0x7777,
	0x0111,0x0000,0x0111,0x0000,0x0111,0x0000,0x0111,0x0000,
	0x0011,0x0000,0x0111,0x0000,0x0111,0x0000,0x0111,0x0000,

	0x7741,0x1777,0x7741,0x1777,0x7741,0x1777,0x7741,0x1777,
	0x7731,0x1777,0x7731,0x3777,0x7731,0x7777,0x7731,0x7777,
	0x7777,0x7277,0x7777,0x7277,0x7777,0x7277,0x7777,0x7277,
	0x7751,0x7277,0x7775,0x7277,0x7777,0x7277,0x7777,0x7177,
	0x7777,0x7116,0x7777,0x7116,0x7777,0x7116,0x7777,0x7116,
	0x7777,0x7116,0x7777,0x7116,0x7777,0x7116,0x7777,0x7116,
	0x7777,0x7754,0x7777,0x7754,0x7777,0x7754,0x7777,0x7754,
	0x7777,0x7754,0x7777,0x7754,0x7777,0x7754,0x6777,0x1123,

	0x6777,0x7774,0x1277,0x7771,0x1277,0x7771,0x1277,0x7771,
	0x1277,0x7771,0x1277,0x7771,0x1277,0x1111,0x1111,0x7753,
	0x7177,0x7777,0x7177,0x7777,0x7177,0x7777,0x7177,0x7777,
	0x7177,0x7777,0x2157,0x1111,0x3111,0x1113,0x7777,0x1577,
	0x7114,0x7777,0x7114,0x7777,0x7114,0x7777,0x7114,0x7777,
	0x1114,0x1111,0x5421,0x7776,0x7771,0x7777,0x7771,0x7777,
	0x0111,0x0000,0x0111,0x0000,0x0111,0x1100,0x1111,0x1111,
	0x7642,0x1117,0x7777,0x1117,0x7777,0x1117,0x7777,0x1117,

	0x7711,0x7777,0x7611,0x7777,0x2111,0x1244,0x1110,0x1111,
	0x1000,0x1111,0x0000,0x0000,0x0000,0x0000,0x0000,0x1000,
	0x7777,0x7167,0x4777,0x1111,0x1111,0x7654,0x7511,0x7777,
	0x7771,0x7777,0x7771,0x7777,0x7771,0x6777,0x7771,0x1177,
	0x2467,0x1111,0x4111,0x7112,0x7777,0x7712,0x7777,0x7742,
	0x7777,0x7771,0x7777,0x7771,0x1135,0x7771,0x1111,0x7771,
	0x6421,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,
	0x7777,0x7777,0x1177,0x7771,0x1177,0x7772,0x7777,0x7777,

	0x7127,0x7777,0x7177,0x7777,0x7177,0x7777,0x7177,0x7777,
	0x7177,0x7777,0x7177,0x7777,0x7177,0x7777,0x7177,0x7777,
	0x7777,0x6777,0x7777,0x7777,0x7777,0x7777,0x7536,0x7777,
	0x7111,0x7777,0x7111,0x7777,0x7111,0x7777,0x7111,0x7777,
	0x7771,0x7777,0x7771,0x3577,0x7771,0x1177,0x7771,0x6577,
	0x7771,0x7777,0x7771,0x7777,0x7771,0x7777,0x7771,0x2477,
	0x7777,0x1116,0x1111,0x1111,0x1111,0x1111,0x1777,0x1111,
	0x1777,0x0011,0x1777,0x0011,0x1777,0x0011,0x1111,0x1111,

	0x0000,0x1000,0x0000,0x1000,0x0000,0x1000,0x0000,0x1000,
	0x0000,0x1000,0x0000,0x1000,0x0000,0x1000,0x0000,0x1000,
	0x7771,0x1177,0x7771,0x1177,0x7771,0x1177,0x7771,0x1177,
	0x7771,0x1177,0x7771,0x1177,0x7771,0x5277,0x7771,0x7777,
	0x1111,0x7771,0x1111,0x7771,0x1111,0x7771,0x1111,0x7771,
	0x1111,0x7771,0x1111,0x7771,0x7776,0x7772,0x7777,0x7772,
	0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x1177,0x7771,
	0x1177,0x7771,0x1177,0x7771,0x1177,0x7771,0x1177,0x7771,

	0x7177,0x7777,0x7177,0x7777,0x7177,0x7777,0x7177,0x7777,
	0x7177,0x7777,0x7177,0x7777,0x7177,0x7777,0x7177,0x6777,
	0x7111,0x7777,0x7111,0x7777,0x7311,0x7777,0x7777,0x7777,
	0x7777,0x3777,0x7777,0x1677,0x7777,0x1157,0x1124,0x1111,
	0x7771,0x1177,0x7771,0x7677,0x7771,0x7777,0x7771,0x7777,
	0x7771,0x7777,0x7771,0x7777,0x4561,0x1112,0x1111,0x1111,
	0x2111,0x1115,0x7777,0x1117,0x7777,0x1117,0x7777,0x1117,
	0x7777,0x1117,0x1246,0x1111,0x1111,0x1111,0x1111,0x0111,

	0x0000,0x1000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x7771,0x7777,0x7771,0x7777,0x7711,0x5777,0x1111,0x1111,
	0x1111,0x1111,0x1100,0x1111,0x0000,0x0000,0x0000,0x0000,
	0x7777,0x7772,0x7777,0x7772,0x1114,0x1111,0x1111,0x1111,
	0x1111,0x1111,0x0011,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x1177,0x7771,0x1167,0x1111,0x1111,0x1111,0x1111,0x1111,
	0x0001,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x1146,0x1111,0x1111,0x1111,0x1111,0x0111,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x1111,0x1111,0x1111,0x1111,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x1111,0x1111,0x0001,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,

	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
};
