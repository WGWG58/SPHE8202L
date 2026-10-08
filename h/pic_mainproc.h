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

#include "types.h"
#include "fsNAV.h"
//=================================================================================
//jpeg part
//=================================================================================


// Different jpeg decoding mode
#define		JPEG_ONLY				0
#define		JPEG_MJPEG				1
#define		JPEG_THUMBNAIL			2
#define		JPEG_PREVIEW			3
#define		JPEG_COWORK				4

extern UINT32  pic_decoding_break;
extern UINT32  PicAudCowork_AudioNextTrack;
//---------------------------------------------------------------------------------
//Extern PIC main procedure related functions 
//---------------------------------------------------------------------------------

extern INT32  jpg_main_preview();																																
extern INT32  jpg_main_thumbnail();	
extern INT32  jpg_main_fullscreen();																																								
extern INT32  jpg_main_mjpeg();																		
extern INT32  jpg_main_cowork();

extern INT32 jpg_exit_file(void);
extern INT32 jpg_get_fileinfo(UINT32 *msf, UINT32 *len, UINT32 thumb_index);
extern void jpg_ir_handler(void);
extern void jpg_fullscreen_rotate_frame(void);
extern void jpg_fullscreen_run_effect(void);
extern void jpg_fullscreen_draw_ui(void);
extern void jpg_ps_init();
extern void jpg_ps_display_setup();
extern void jpg_ps_enable_ms();
extern void jpg_preview_draw_ui(void);
extern void jpg_thumbnail_draw_ui(void);
extern void jpg_thumbnail_set_display(UINT32 thumb_index);
extern void jpg_thumbnail_process_index(UINT32 *thumbIndex);
extern void jpg_redecode_byTvResolution(void);
extern void jpg_load_pixel_aspect_ratio(UINT8 *par, UINT8 *bak_PAR_Height, UINT8 *bak_PAR_Width, UINT8 *bak_vpp_expansion);
extern void jpg_set_pixel_aspect_ratio(void);
extern void jpg_restore_pixel_aspect_ratio(UINT8 par, UINT8 bak_PAR_Width, UINT8 bak_PAR_Height, UINT8 bak_vpp_expansion);
extern void jpg_fullscreen_effect_postprocessing(void);

//=================================================================================
//gif part, should be moved to gif_parser.h later
//=================================================================================


//=================================================================================
//bmp part, should be moved to bmp_parser.h later
//=================================================================================

