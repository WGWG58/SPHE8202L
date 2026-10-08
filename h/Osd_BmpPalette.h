/**************************************************************
** FILE
** Osd_Palette.h
**
** DESCRIPTION
**   the pallettes of all the bmps of Osd
**
**
**   Creator: feeling,suqiaoli
**   Date:    2004-7-7 17:02
****************************************************************/

#ifdef OSD_BMP

#define __palette4F(G,B,R,A) \
        ( ((UINT32)((G)&0xff)<<24)|((UINT32)((B)&0xff)<<16)|((UINT32)((R)&0xff)<<8)|(A&0xff) ) 


#define	CLUTE_TRANS	0x80808000

#define _WHITE     __palette4F(0xeb,0x80,0x80,0xff)
#define _YELLOW    __palette4F(0xa2,0x8e,0x2c,0xff)
#define _CYAN      __palette4F(0x83,0x2c,0x9c,0xff)
#define _GREEN     __palette4F(0x70,0x,0x2c,0xff)


static const UINT32 g_aPalette_Display_Region0[16] =
{
__palette4F(0xff,0xff,0xff,0x0),
 //__palette4F(0x34,0xa8,0x6b,0xff),
 __palette4F(0x55,0x78,0x8e,0xff),
 __palette4F(0x4a,0x88,0x82,0xff),
 __palette4F(0x32,0x64,0x57,0xff),
 __palette4F(0x3f,0x98,0x76,0xff),
 __palette4F(0x8b,0xb6,0xa1,0xff),
 __palette4F(0x54,0xad,0x7f,0xff),
 __palette4F(0x34,0xa8,0x6b,0xff),  //index = 7, the purple color used as display shadow
 __palette4F(0xd8,0x19,0x0,0xff),
 __palette4F(0x0,0xa4,0x2,0xff),
 __palette4F(0xc2,0xc1,0xc2,0xff),
 __palette4F(0xbd,0x6,0xfb,0xff),
 __palette4F(0x8f,0x2f,0xc9,0xff),
 __palette4F(0x3e,0x27,0x58,0xff),
 __palette4F(0x6d,0x57,0xa6,0xff),
 __palette4F(0x0,0x0,0x0,0x1e),
//__palette4F(0xff,0xff,0xff,0x0), 

};

static const UINT32 g_aPalette_Display_Region1[4] = 
{
    __palette4F(  0x34, 0xA8, 0x6B, 0xff), //background(52, 168, 107)
    __palette4F(  0,    0xff, 0xff, 0),    //transparent
    __palette4F(  0,    0,    0,    0x1e), //blend
    __palette4F(  0xC2, 0xC1, 0xC2, 0xff), //fontcolor(194, 193, 194) 

};


static const UINT32	g_aPalette_Setup_Region1[16] = //palette 1
{
 };

static const UINT32	g_aPalette_Setup_Region2[16] = //palette 2
{
};

static const UINT32	g_aPalette_Setup_Region3[16] = //palette 3
{
};

static const UINT32	g_aPalette_Setup_Region4[16] = //palette 4
{
};

static const UINT32	g_aPalette_Setup_Region5[16] = //palette 5
{
};




/************************************************************\
 OSD Header Config
 config 0: color upate|force transparent|pixel resolution[1:0]|reserved|color mode[2:0](0:4 1:16 2:256 4:16bit#1 5:16bit#2)
 config 1: shade[3:0]|blend[3:0]
 config 2: CLUT entries type[1:0](0:16 bit,1:32 bit,2:27 bit)|rgb(0:YCbCr,1:RGB)|swp(0:Normal,1:BYTE swap)|shd(0:Sub,1:Ratio)|Reserved[1:0] 
\************************************************************/
const UINT8 osd_header_config[][3]=
{
      {//display region 0 16 colors
       //config 0
      	((1&0x01) << BIT_CU)|((0) << BIT_FT)|((0 & 0x03) << BIT_PR),      	
       //config 1
      	((0xc & 0x0f) << BIT_SHD)| ((0xf & 0x0f) << BIT_BLND),
       //config 2
         V2_CLUT_TYPE(OSDV2_CLUT_32b)| V2_RGB_MODE|V2_SWAP_BYTE_OFF| V2_SHADE_MODE_B
      },

      {//display region 1  4 color
       //config 0
        ((1&0x01) << BIT_CU)|((0) << BIT_FT)|((0 & 0x03) << BIT_PR),
       //config 1
        ((0x0 & 0x0f) << BIT_SHD)| ((0xf & 0x0f) << BIT_BLND),
       //config 2
         V2_CLUT_TYPE(OSDV2_CLUT_32b)| V2_RGB_MODE|V2_SWAP_BYTE_OFF| V2_SHADE_MODE_A
      },
};
const UINT32 *g_aOsdPalette[]=
{
	g_aPalette_Display_Region0, //index = 0
	g_aPalette_Display_Region1,//index = 1
	
	//g_aPalette_Setup_Region1, //index = 2
	//g_aPalette_Setup_Region2,//index = 3
	//g_aPalette_Setup_Region3,//index = 4
	//g_aPalette_Setup_Region4,//index = 5
	//g_aPalette_Setup_Region5,//index = 6
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
	ALIGN_32B(16),
	ALIGN_32B(16)
};

#endif//ifdef OSD_BMP



