/*
**	COLOR	Y	Cr	Cb
**
**	WHITE	0xeb	0x80	0x80
**	YELLOW	0xa2	0x8e	0x2c
**	CYAN	0x83	0x2c	0x9c
**	GREEN	0x70	0x3a	0x48
**	MAGENTA	0x54	0xc6	0xb8
**	RED	0x41	0xd4	0x64
**	BLUE	0x23	0x72	0xd4
**	BLACK	0x10	0x80	0x80
**
*/
#define __palette4F(Y,B,R,A) \
        ( ((UINT32)((Y)&0xff)<<24)|((UINT32)((B)&0xff)<<16)|((UINT32)((R)&0xff)<<8)|(A&0xff) ) 
        
#define	CLUTE_TRANS	0x80808000

#define _WHITE     __palette4F(0xeb,0x80,0x80,0xff)
#define _YELLOW    __palette4F(0xa2,0x8e,0x2c,0xff)
#define _CYAN      __palette4F(0x83,0x2c,0x9c,0xff)
#define _GREEN     __palette4F(0x70,0x,0x2c,0xff)



/************************************************************\
 pal
\************************************************************/
//for 3d-sound menu
const	UINT32	palette_16color[] = 
{    
    __palette4F(  20, 128, 128,0xff),    //11 black //Jeff 20020404
    __palette4F(  75 , 85,  74,0xff),    //dark green    1
    __palette4F(  112, 64,  47,0xff),    //middle green  2
    __palette4F(  149, 43,  21,0xff),    //green         3
    __palette4F(  199, 15, 167,0xff),    //yellow        4
    __palette4F(  152, 41, 201,0xff),    //dark orange   5
    __palette4F(  164, 35, 192,0xff),    //bright orange 6
    __palette4F(  112, 64, 229,0xff),    //dark red      7
    __palette4F(   78, 84, 255,0xff),    //bright red    8
    __palette4F(  128,128, 128,0xff),    //gray white    9
    __palette4F(  0xa2, 0x2c, 0x8e,0xff),    //yellow-green  10
    CLUTE_TRANS,
    CLUTE_TRANS,
    CLUTE_TRANS,
    CLUTE_TRANS,
    CLUTE_TRANS,
};


//for setup menu and OSD0
//setup : 0, 1, 2, 3, 4, 5, 6, 7
//OSD0  : 0, 3, 8, 9, 10, 15
static	const	UINT32	palette_16color_setup[] = 
{
    __palette4F(  0x50, 0x70, 0x70,0x80),   // 0  transparent
    __palette4F(  72, 178, 120,0xff),	    // 1  gray-blue
    __palette4F(  196-30, 122, 130,0xff),   // 2  near white    //nono 2-3-11 14:05 for yuxing
    __palette4F(  132,144, 126,0xff),	    // 3  light gray
    __palette4F(  72, 178, 120,0xff),	    // 4  gray-blue
#ifndef KONKA_DVD//20020820
    __palette4F( 80, 170, 80,0xff),         // 5  gray-green
    __palette4F(  112, 160, 112,0xff),	    // 6  light-gray-blue
#else
    __palette4F(  80, 180, 80,0xff),        // 5  gray-green
    __palette4F(  110, 170, 112,0xff),	    // 6  light-gray-blue
#endif
    __palette4F(  0xa0, 0x28, 0x8c, 0xff),  // 7  yellow
    __palette4F(  180, 43,  21,0xff),       // 8  green
    __palette4F(  180, 0x2c, 0x8e,0xff),    // 9  yellow-green
    __palette4F(  180, 41, 201,0xff),       // 10 dark orange
    __palette4F(  40+10, 128, 128,0xff),    // 11 black         //nono 2-3-11 14:05for yuxing
    __palette4F(  100, 128, 128,0xff),      // 12 dark-gray
    CLUTE_TRANS,                            // 13
    CLUTE_TRANS,                            // 14	
#ifdef GREY_OSD_DISP                        // ych 2-7-8 17:39
    __palette4F( 100, 128, 128,0xff),       // 15 gray white  
#else
    CLUTE_TRANS,                            // 15 OSD shadow color(not modify)
#endif 
};


#define C16_WHITE       2
#define C16_LIGHTGRAY   3
#define C16_DARKGRAY    12
#define C16_BLACK       11


//4 color palette
const	UINT32	palette_4color[] = 
{   
    __palette4F(  0x50, 0x70, 0x70,0x80),    //00b:background		
	CLUTE_TRANS,                                     //01b:transparent		
	__palette4F(  0x50, 0x70, 0x70,0xff),    //10b:anti background
#ifdef GREY_OSD_DISP                        
	__palette4F(  166, 122, 130,0xff),       //11b:text,white  
#else
	__palette4F(  0xa2, 0x2c, 0x8e,0xff),    //11b:text,yellow-green
#endif
};





/************************************************************\
 OSD Header Config
 config 0: color upate|force transparent|pixel resolution[1:0]|reserved|color mode[2:0](0:4 1:16 2:256 4:16bit#1 5:16bit#2)
 config 1: shade[3:0]|blend[3:0]
 config 2: CLUT entries type[1:0](0:16 bit,1:32 bit,2:27 bit)|rgb(0:YCbCr,1:RGB)|swp(0:Normal,1:BYTE swap)|shd(0:Sub,1:Ratio)|Reserved[1:0] 
\************************************************************/
const UINT8 osd_header_config[][3]=
{
      {//normal 4 color
       //config 0
      	((1&0x01) << BIT_CU)|((0) << BIT_FT)|((0 & 0x03) << BIT_PR),
       //config 1
      	((0xf & 0x0f) << BIT_SHD)| ((0xf & 0x0f) << BIT_BLND),
       //config 2
         V2_CLUT_TYPE(OSDV2_CLUT_32b)| V2_SWAP_BYTE_OFF| V2_SHADE_MODE_A
      },
      {//eq 16 color
       //config 0
      	((1&0x01) << BIT_CU)|((0) << BIT_FT)|((1 & 0x03) << BIT_PR),      	
       //config 1
      	((0xc & 0x0f) << BIT_SHD)| ((0xf & 0x0f) << BIT_BLND),
       //config 2
         V2_CLUT_TYPE(OSDV2_CLUT_32b)| V2_SWAP_BYTE_OFF| V2_SHADE_MODE_A
      },
      {//setup,display
       //config 0
      	((1&0x01) << BIT_CU)|((0) << BIT_FT)|((0 & 0x03) << BIT_PR),      	
       //config 1
      	((0xf & 0x0f) << BIT_SHD)| ((0xf & 0x0f) << BIT_BLND),
       //config 2
         V2_CLUT_TYPE(OSDV2_CLUT_32b)| V2_SWAP_BYTE_OFF| V2_SHADE_MODE_A
      },
      {//nes game
       //config 0
      	((1&0x01) << BIT_CU)|((0) << BIT_FT)|((1 & 0x03) << BIT_PR),      	
       //config 1
      	((0xc & 0x0f) << BIT_SHD)| ((0xf & 0x0f) << BIT_BLND),
       //config 2
         V2_CLUT_TYPE(OSDV2_CLUT_32b)| V2_SWAP_BYTE_OFF| V2_SHADE_MODE_A
      }
};

UINT32 *osd__pal[]=
{
	  palette_4color,//normal
	  palette_16color,//eq
	  palette_16color_setup,//setup,display
	  NULL//nes game
};
/************************************************************\
 OSD Header Offset ,data block location
\************************************************************/
#define OSD_16b_BUG
#define ALIGN_32B(x) ((x+31)/32)

const	UINT8	osd_header_offset[8] = 
{
	ALIGN_32B(16 + 4*4), 
	ALIGN_32B(16 + 4*16), 
	ALIGN_32B(16 + 4*256), 
	ALIGN_32B(16),
	ALIGN_32B(16),
	ALIGN_32B(16),
	ALIGN_32B(HEADER_SIZE),
	ALIGN_32B(HEADER_SIZE)
};



