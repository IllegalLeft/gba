// notes

#define NOTE_FREQ(_freq)	(u16)((131072-(2048*_freq))/-_freq)

#define C2		NOTE_FREQ(65.41)
#define CS2		NOTE_FREQ(69.30)
#define Db2		CS2
#define D2		NOTE_FREQ(73.42)
#define DS2		NOTE_FREQ(77.78)
#define Eb2		DS2
#define E2		NOTE_FREQ(82.41)
#define F2		NOTE_FREQ(87.31)
#define FS2		NOTE_FREQ(92.50)
#define Gb2		FS2
#define G2		NOTE_FREQ(98.00)
#define GS2		NOTE_FREQ(103.83)
#define Ab2		GS2
#define A2		NOTE_FREQ(110.00)
#define AS2		NOTE_FREQ(116.54)
#define Bb2		AS2
#define B2		NOTE_FREQ(123.47)
#define C3		NOTE_FREQ(130.81)
#define CS3		NOTE_FREQ(138.59)
#define Db3		CS3
#define D3		NOTE_FREQ(146.83)
#define DS3		NOTE_FREQ(155.56)
#define Eb3		DS3
#define E3		NOTE_FREQ(164.81)
#define F3		NOTE_FREQ(174.61)
#define FS3		NOTE_FREQ(185.00)
#define Gb3		FS3
#define G3		NOTE_FREQ(196.00)
#define GS3		NOTE_FREQ(207.65)
#define Ab3		GS3
#define A3		NOTE_FREQ(220.00)
#define AS3		NOTE_FREQ(233.08)
#define Bb3		AS3
#define B3		NOTE_FREQ(246.94)