

#include "types.h"


#define TRANS_COLOR		0x0000
#define DRK_GREEN_COLOR	0xeeee
#define MID_GREEN_COLOR	0x8888
#define BR_GREEN_COLOR	0x9999

#define YELLOW_COLOR	0x7777
#define DRK_ORANGE		0x5555
#define BR_ORANGE		0x5555
#define DRK_RED_COLOR	0xdddd
#define BR_RED_COLOR	0xcccc
#define GRAY_COLOR		0x3333


BYTE	PatternMode;
BYTE 	bEqMaxKeepTm=0;
BYTE    header_id;



const	UINT16 	bColorTab[]=
{ DRK_GREEN_COLOR,MID_GREEN_COLOR,BR_GREEN_COLOR,
YELLOW_COLOR,DRK_ORANGE,DRK_RED_COLOR,BR_RED_COLOR 
};  
//0 -> 00(OSD background)
//1 -> 11(yellow-green)
//font boundary(only horizontal) -> 01(anti-background)
#ifdef DRAW_BLACK_FRAME
const BYTE PatternEdge[] = { //Detect Edge 
    0x00,                                                   //0000 0000 0000
    0x01,                                                   //0001 0000 0001
    0x04,                                                   //0010 0000 0100
    0x05,                                                   //0011 0000 0101
    0x10,                                                   //0100 0001 0000
    0x11,                                                   //0101 0001 0001
    0x14,                                                   //0110 0001 0100
    0x15,                                                   //0111 0001 0101
    0x40,                                                   //1000 0100 0000
    0x41,                                                   //1001 0100 0001
    0x44,                                                   //1010 0100 0100
    0x45,                                                   //1011 0100 0101
    0x50,                                                   //1100 0101 0000
    0x51,                                                   //1101 0101 0001
    0x54,                                                   //1110 0101 0100
    0x55                                                    //1111 0101 0101
};
const BYTE pattern_4[] = { //old:pattern_4
    0x00,                                                   //0000 0000 0000
    0x07,                                                   //0001 0000 0111
    0x1d,                                                   //0010 0001 1101
    0x1f,                                                   //0011 0001 1111
    0x74,                                                   //0100 0111 0100
    0x77,                                                   //0101 0111 0111
    0x7d,                                                   //0110 0111 1101
    0x7f,                                                   //0111 0111 1111
    0xd0,                                                   //1000 1101 0000
    0xd7,                                                   //1001 1101 0111
    0xdd,                                                   //1010 1101 1101
    0xdf,                                                   //1011 1101 1111
    0xf4,                                                   //1100 1111 0100
    0xf7,                                                   //1101 1111 0111
    0xfd,                                                   //1110 1111 1101
    0xff,                                                   //1111 1111 1111
};
#else
const BYTE pattern_4[]=
{//0=>00 1=>11
	0x00, 0x03,	0x0c, 0x0f,	0x30, 0x33,	0x3c, 0x3f,
	0xc0, 0xc3,	0xcc, 0xcf,	0xf0, 0xf3,	0xfc, 0xff
};
#endif
const BYTE pattern_a4[]=
{//0=>10 1=>11	
	0xaa, 0xab,	0xae, 0xaf,	0xba, 0xbb,	0xbe, 0xbf,
	0xea, 0xeb,	0xee, 0xef,	0xfa, 0xfb,	0xfe, 0xff		
};

const BYTE pattern_b4[]=
{//0=>01 1=>11
	0x55, 0x57,	0x5D, 0x5F,	0x75, 0x77,	0x7D, 0x7F,
	0xD5, 0xD7,	0xDD, 0xDF,	0xF5, 0xF7,	0xFD, 0xFF,
};

