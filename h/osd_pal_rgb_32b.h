//--------------------------------------
//Modefied by wangfeng, 2003-08-29 15:32
//For new setup menu 
//--------------------------------------

/*
**  COLOR   Y   Cr  Cb
**
**  WHITE   0xeb    0x80    0x80
**  YELLOW  0xa2    0x8e    0x2c
**  CYAN    0x83    0x2c    0x9c
**  GREEN   0x70    0x3a    0x48
**  MAGENTA 0x54    0xc6    0xb8
**  RED     0x41    0xd4    0x64
**  BLUE    0x23    0x72    0xd4
**  BLACK   0x10    0x80    0x80
**
*/
#define __palette4F(G,B,R,A) \
        ( ((UINT32)((G)&0xff)<<24)|((UINT32)((B)&0xff)<<16)|((UINT32)((R)&0xff)<<8)|(A&0xff) ) 
        
#define CLUTE_TRANS 0x80808000

#define _WHITE     __palette4F(0xeb,0x80,0x80,0xff)
#define _YELLOW    __palette4F(0xa2,0x8e,0x2c,0xff)
#define _CYAN      __palette4F(0x83,0x2c,0x9c,0xff)
#define _GREEN     __palette4F(0x70,0x,0x2c,0xff)

#if defined(SUPPORT_TELETEXT) || defined(SUPPORT_SUBTITLE)  //David
#define OSD_ALPHA		180
#define RGBDEF(R,G,B) \
        ( ((UINT32)((R)&0xff)<<8)|((UINT32)((G)&0xff)<<24)|((UINT32)((B)&0xff)<<16)|(OSD_ALPHA&0xff) ) 
#endif
#define C16_WHITE   2
#define C16_LIGHTGRAY   3
#define C16_DARKGRAY    3
#define C16_BLACK   11

// extern from osd_pal_rgb_32b.c

extern const    UINT32   palette_16color[];
extern const    UINT32   palette_16color_qsi[];
extern const    UINT32   palette_16color_setup[];
extern const    UINT32   palette_16color_bmp_display[];
extern const    UINT32   palette_4color_bmp_region1[];
extern const    UINT32   palette_16color_region_A[];
extern const	UINT32	 palette_16color_region_B[];
extern const	UINT32   palette_16color_region_C[];
extern const	UINT32	 palette_16color_region_D[];
extern const	UINT32	 palette_16color_region_E[];
extern const	UINT32   palette_16color_region_F[];
extern const    UINT32   palette_16color_midi[];
extern const    UINT32   palette_4color[];
#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
extern const   UINT32   palette_4color_hl[];
#endif

#ifdef REALCOLOR_QSI
extern const    UINT32   palette_256color_sreensaver[5][256];
#else
extern const    UINT32   palette_256color_sreensaver[256];
#endif

extern const    UINT8    osd_header_config[][3];
extern const    UINT32   *osd__pal[];
extern const    UINT8    osd_header_offset[8];


