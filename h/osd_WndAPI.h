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
|  File Name    :  osd_WndProc.h
|  Description  :  Provide functions of osd-hareware control and osd-drawsing
|  Version      :  1.0  
|  Compiler     : GCC for MIPS(R3000)
|  Platform     : Sunplus SPCA8202A DVD Player
|
|  Rev	Date	        Author(s)               Status & Comments
|---------------------------------------------------------------------------------
|  1.0	03/29/2005      yltseng                 Creating
|--------------------------------------------------------------------------------*/ 

#ifndef _OSD_WNDAPI_H_
#define _OSD_WNDAPI_H_

#include "user_init.h"
#include "types.h"

/************************************************************************************
OSD Window Creation
************************************************************************************/
#define ROW_HEI             32

#define IRC_DESTROY         0xFC
#define IRC_ACTIVATE        0xFD
#define IRC_TIMER           0xFE
#define IRC_TVGHELP         0xFB
#define IRC_TVGSHOW 		0xFA

// Window Style
#define WS_CAPTION          0x01
#define WS_THICKFRAME       0x02
#define WS_SYSMENU          0x04

typedef struct
{
    const char* pCaption;
    UINT16      uiX;
    UINT16      uiY;
    UINT16      uiWidth;
    UINT16      uiHeight;
    UINT8       uiRegion;
    UINT8       uiStyle;
} WND_PARAM;


#ifdef SUPPORT_WINDOW_PROC

static inline   WND_PARAM GetWindowInfo() { extern WND_PARAM g_mbParam; return g_mbParam; }
extern void     ExitWindow( UINT8 uiParam );
extern void     ShowWindowText( const char* pText, UINT16 uiX, UINT16 uiY, UINT8 uiFontColor, UINT8 uiBackColor );
extern void     RegisterCallback( UINT32 (*pFunc)( UINT32 ) );
extern void     SetTimer( UINT32 uiElapse );
extern void     KillTimer();
extern void     CreateWindow( BYTE uiRegion, const char* pCaption, UINT8 uiStyle, UINT16 uiX, UINT16 uiY, UINT16 uiWidth, UINT16 uiHeight );
extern void     ShowWindow();
//extern UINT8    WindowMain();
extern UINT8  WindowMain(UINT16 Tvg_CMD);

#else

#define         GetWindowInfo()
#define         ExitWindow()
#define         ShowWindowText()
#define         RegisterCallback()
#define         SetTimer()
#define         KillTimer()
#define         CreateWindow()
#define         ShowWindow()
#define         WindowMain()

#endif

/************************************************************************************
OSD Warning message box
************************************************************************************/

typedef enum
{
    MB_NORMAL,
    MB_OK,
    MB_YESNO,
} WARNBOX_TYPE;

typedef enum
{
    IDNONE,
    IDDEFAULT,
    IDNO,
    IDOK,
    IDYES,
} MESSAGEBOX_RETURN_TYPE;

typedef enum
{
    WARNBOX_SIZE_SMALL,
    WARNBOX_SIZE_MIDDLE,
    WARNBOX_SIZE_LARGE,
} WARNBOX_SIZE;

#if defined(SUPPORT_WARNING_BOX)||defined(Simplay_warning)	//eric lin,2006-07-06,for Simplay format warning message
MESSAGEBOX_RETURN_TYPE Warning_box(BYTE region, const char *cap, const char *txt, WARNBOX_TYPE type, WARNBOX_SIZE size, UINT32 uiCountDown );
#else
#define Warning_box( region, cap, txt, type, size, uiCountDown )
#endif

// **************************************************************************************** //
#endif
