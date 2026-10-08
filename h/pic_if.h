/**************************************************************************
 *                                                                        *
 *         Copyright (c) 2002 by Sunplus Technology Co., Ltd.             *
 *                                                                        *
 *  This software is copyrighted by and is the property of Sunplus        *
 *  Technology Co., Ltd. All rights are reserved by Sunplus Technology    *
 *  Co., Ltd. This software may only be used in accordance with the       *
 *  corresponding license agreement. Any unauthorized use, duplication,   *
 *  distribution, or disclosure of this software is expressly forbidden.  *
 *                                                                        *
 *  This Copyright notice MUST not be removed or modified without prior   *
 *  written consent of Sunplus Technology Co., Ltd.                       *
 *                                                                        *
 *  Sunplus Technology Co., Ltd. reserves the right to modify this        *
 *  software without notice.                                              *
 *                                                                        *
 *  Sunplus Technology Co., Ltd.                                          *
 *  19, Innovation First Road, Science-Based Industrial Park,             *
 *  Hsin-Chu, Taiwan, R.O.C.                                              *
 **************************************************************************/
#ifndef __PIC_IF_H
#define __PIC_IF_H
//=================================================================================
//jpeg part, should be moved to jpeg_if.c later
//=================================================================================


//---------------------------------------------------------------------------------
//JPEG display setup 
//---------------------------------------------------------------------------------
//MEMORY_GRAPH_PAL(736X576)
#define JPEG_FULLSCREEN_X           0
#define JPEG_FULLSCREEN_Y           0
#define JPEG_FULLSCREEN_W           720
#define JPEG_FULLSCREEN_H           576

//MEMORY_GRAPH_PAL(736X576)
#define JPEG_THUMBNAIL_X            72
#define JPEG_THUMBNAIL_Y            144
#define JPEG_THUMBNAIL_W            160
#define JPEG_THUMBNAIL_H            120

//MEMORY_GRAPH_HD_720P(1280X720)
#define JPEG_HD_FULLSCREEN_X_720P           0
#define JPEG_HD_FULLSCREEN_Y_720P           0
#define JPEG_HD_FULLSCREEN_W_720P           1280
#define JPEG_HD_FULLSCREEN_H_720P           720

//MEMORY_GRAPH_HD_1080I(1920X1080)
#ifdef SDRAM_32Mb_Mode
    //for 32m memory
    #define JPEG_HD_FULLSCREEN_X_1080I           0
    #define JPEG_HD_FULLSCREEN_Y_1080I           0
    #define JPEG_HD_FULLSCREEN_W_1080I           1280
    #define JPEG_HD_FULLSCREEN_H_1080I           720
#elif defined(SDRAM_64Mb_Mode)
    #define JPEG_HD_FULLSCREEN_X_1080I           0
    #define JPEG_HD_FULLSCREEN_Y_1080I           0
    #define JPEG_HD_FULLSCREEN_W_1080I           1440
    #define JPEG_HD_FULLSCREEN_H_1080I           1024
#endif

enum{
    NON_CENTER = 0, 
    CENTER = 1,
};


#ifdef SDRAM_NO_REORDER
    #define swap_luma(x)        (x)
    #define swap_chroma(x)      (x)
#else
    #define swap_luma(x)        (((x)&0xffe7) | (((x)&0x0008)<<1) | (((x)&0x0010)>>1))
    #define swap_chroma(x)      (((x)&0xffe6) | (((x)&0x0008)<<1) | (((x)&0x0010)>>1))
#endif


#define sdram_start()           (SDRAM_BASE_UNCACHED)
#define luma_start()            (sdram_start() + REF0_LUMA*1024)
#define chroma_start()          (sdram_start() + REF0_CHROMA*1024)

#define get_luma_addr(x,y)      (luma_start() + (y)*(LINE_OFFSET) + swap_luma(x))
#define get_chroma_addr(x,y)    (chroma_start() + (y)*(LINE_OFFSET) + swap_chroma(x))
//---------------------------------------------------------------------------------
//Extern basic functions of pic interface
//---------------------------------------------------------------------------------
extern ifunc  Pic_nav_mainloop;

extern INT32 Pic_nav_enter(void);
extern INT32 Pic_nav_init(void);
extern INT32 Pic_nav_exit(void);
extern INT32 Pic_nav_entrance(void);

extern INT32 Jpg_init_parameters(UINT32 navmode);
extern INT32 Jpg_display_setup(UINT32 navmode);
extern INT32 Jpg_buffer_setup(UINT32 navmode);
extern INT32 Jpg_decoder_setup(UINT32 navmode __attribute__((unused)));
extern INT32 Jpg_scaler_setup(UINT32 navmode __attribute__((unused)));
extern INT32 Jpg_memory_config(UINT32 navmode);

extern UINT32 Jpg_PreviewCallBackCheck(UINT32 func);
extern UINT32 Jpg_ThumbnailCallBackCheck(UINT32 func);
extern UINT32 Jpg_FullScreenCallBackCheck(UINT32 func);

//=================================================================================
//gif part, should be moved to gif_if.c later
//=================================================================================



//=================================================================================
//bmp part, should be moved to bmp_if.c later
//=================================================================================



//=================================================================================
//mjpeg part, should be moved to mjpeg_if.c later
//=================================================================================


#endif  //__PIC_IF_H
