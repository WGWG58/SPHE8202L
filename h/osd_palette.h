/************************************************************\
define
\************************************************************/
#define LINK_NULL   (0xffff)

#define __palette(Y,Cb,Cr,BlendFactor) \
    (\
	(((UINT32)(Y)     & 0x3f)<<10)   \
	| (((UINT32)(Cb)    & 0x0f)<<6)    \
	| (((UINT32)(Cr)    & 0x0f)<<2)    \
	| (((UINT32)(BlendFactor) & 0x03)) \
)

#define __palette2(Y,Cb,Cr,Blend,Fill) \
    (\
	(((UINT32)(Y)     & 0x3f)<<10)   \
	| (((UINT32)(Cb)    & 0x0f)<<6)    \
	| (((UINT32)(Cr)    & 0x0f)<<2)    \
	| ((Blend) ? 0x02 : 0x01)      \
	| ((Fill)  ? 0x01 : 0x00)      \
)

#define __paletteF(Y,B,R,BlendFactor) \
__palette((Y)>>2, (B)>>4, (R)>>4, (BlendFactor))

#define __palette2F(Y,B,R,Blend,Fill) \
__palette2((Y)>>2, (B)>>4, (R)>>4, (Blend), (Fill))


#define SOUND_MAX_REGION        5


//#define HEADER_SIZE     0x10
/*
#define NORMAL_HEADER   0
#define EQ_HEADER       1
#define SETUP_HEADER    2
#define NES_HEADER      3

#ifdef  BBK_NEW_SETUP     //fengjl  add for BBK's NEW_SETUP  3-11-17 16:08
#define BBK_SETUP_HEADER      4
#endif

#ifdef VIRTUAL_KEYBOARD
#define KEYBOARD_HEADER 4   //liweihua add for 256 color keyboard 2003-11-10 19:28
#endif
*/

#define	ONE_BYTE_POINT	4		//4 color -> 1 byte has 4 point 
#define DASH_MARK				0x2d
#ifdef NEW_SETUP_OSD                     // majinping 2002-05-02 for new setup menu
#define SETUP_MAIN_YSTART       1
#endif
#ifndef	NULL
#define	NULL	((void *)0)
#endif

#define OSD_FONT_HEIGHT 24
//#define	REGIONS_ACTIVE	6
#ifdef INDIGO_STYLE_OSDUI
	#define SETUP_BTN_HEIGHT        (OSD_FONT_HEIGHT+4) // button height
#else
#define SETUP_BTN_HEIGHT        (OSD_FONT_HEIGHT+8)
#endif	

#define MAX_VOLUME		25


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


//define in osd_drv.h
//#define OSD_PAL_16b
//#define OSD_PAL_32b
//#define OSD_PAL_RGB_32b

#ifdef OSD_PAL_16b
#include "osd_pal_16b.h"
#endif

#ifdef OSD_PAL_32b
#include "osd_pal_32b.h"
#endif

#ifdef OSD_PAL_RGB_32b
#include "osd_pal_rgb_32b.h"
#endif

//#ifdef OSD_BMP
//#include "Osd_BmpPalette.h"
//#endif
#define	OSD_DATA_OFFSET(f)	    (osd_header_offset[(f)&OSD_FORMAT_MASK])
#define	OBV_BASE		        (SDRAM_BASE + regs0->osd_base_addr*1024)
#define	get_osdbuf_baseptr()	((void *)OBV_BASE)

#if !defined(OSD_PAL_16b) || defined(OSD_16b_BUG)
#define OSD_CLUT_SIZE   4
#else
#define OSD_CLUT_SIZE   2
#endif

#define	PALETTE_2_SIZE			(2*OSD_CLUT_SIZE)
#define PALETTE_4_SIZE			(4*OSD_CLUT_SIZE)
#define PALETTE_16_SIZE			(16*OSD_CLUT_SIZE)
#define PALETTE_256_SIZE		(256*OSD_CLUT_SIZE)

// extern from osd_palette.c
extern  BYTE	PatternMode;
extern  BYTE 	bEqMaxKeepTm;
extern  BYTE    header_id;
extern  UINT8 safe_on;

extern  const UINT16 	bColorTab[];
extern  const BYTE PatternEdge[];
extern  const BYTE pattern_4[];
extern  const BYTE pattern_a4[];
extern  const BYTE pattern_b4[];

