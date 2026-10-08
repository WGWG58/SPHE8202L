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
/*--------------------------------------------------------------------------
|  File Name   :  FsNav_util.h
|
|  Description :  Header of file system utility
|
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2006/07/11      Joshua         Creating
|--------------------------------------------------------------------------------*/ 

#ifndef _FSNAV_UTIL_H_
#define _FSNAV_UTIL_H_

#include "types.h"

#ifdef SUPPORT_SPG_GAME
extern UINT16 Is_SPG_STATE(void);
#endif

extern UINT16 Is_JPEG_STATE(void);
extern UINT16 Is_MP3_STATE(void);
extern UINT16 Is_JPEG_SlideMode(void);
extern UINT16 Is_JPEG_PLAY_STATE(void);

#ifdef SUPPORT_MIDI
UINT16 Is_MIDI_STATE(void);
#endif

#ifdef SUPPORT_QUICKTIME
BYTE IsM4AFileType();
#endif

extern BYTE GetCurrentFileType();
extern void FSNav_Init();

#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 021007
UINT16 Is_OTHER_STATE(void);
UINT16 IsOtherStatePlayMode(void);
#endif

extern BYTE FSIsZoomOK();

#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
UINT16 Is_GAME_STATE(void);
#endif

#ifdef MP3_DIRECT_SELECT
void FSGUI_cal_dir_file(UINT16 *dir,UINT16 *file,UINT16 iSelect);
void FSGUI_cal_2_file(UINT16 *iSelect,UINT16 dir,UINT16 file);
#endif

#endif
