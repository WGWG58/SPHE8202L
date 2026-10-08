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
|  File Name    :  show_msg_box.c
|  Description  :  Show warning message box
|  Version      :  1.0  
|  Compiler     :  GCC for MIPS(R3000)
|  Platform     :  Sunplus SPCA8202A DVD Player
|
|  Rev	Date	        Author(s)               Status & Comments
|---------------------------------------------------------------------------------
|  1.0	03/29/2005      yltseng                 Creating
|--------------------------------------------------------------------------------*/ 

#include "osd_WndAPI.h"

// **************************************************************************************** //
#ifdef SUPPORT_WARNING_BOX
#include "global.h"
#include "ircode.h"

#ifndef SUPPORT_WINDOW_PROC
#error "Must define SUPPORT_WINDOW_PROC && NEW_OSD_DRIVER\n"
#endif

// **************************************************************************************** //
#ifndef DVDRELEASE
    #define WARN_MSG_DBG    1
#endif

#ifndef WARN_MSG_DBG
    #undef printf
    #undef print_block
    #define printf(f, a...) do {} while (0)
    #define print_block(x,y) do {} while (0)
#endif

// **************************************************************************************** //

#define SMALL_START_X    120
#define SMALL_START_Y    150
#define SMALL_TXT_WID    300
#define SMALL_TXT_HEI    100

#define MIDDLE_START_X   100
#define MIDDLE_START_Y   120
//#define MIDDLE_TXT_WID   350

#ifdef Simplay_warning	//eric lin,2006-07-06,for Simplay format warning message
#define MIDDLE_TXT_WID   368
#define MIDDLE_TXT_HEI   200
#else
#define MIDDLE_TXT_WID   368  //16*24
#define MIDDLE_TXT_HEI   180
#endif	//#ifdef Simplay_warning

#define LARGE_START_X    60
#define LARGE_START_Y    60
#define LARGE_TXT_WID    450
#define LARGE_TXT_HEI    250

const UINT16 msg_box_size[3][4] =
{
    {
        SMALL_START_X,
        SMALL_START_Y,
        SMALL_TXT_WID,
        SMALL_TXT_HEI,
    },
    {
        MIDDLE_START_X,
        MIDDLE_START_Y,
        MIDDLE_TXT_WID,
        MIDDLE_TXT_HEI,
    },
    {
        LARGE_START_X,
        LARGE_START_Y,
        LARGE_TXT_WID,
        LARGE_TXT_HEI,
    },
};

static UINT8 s_uiMsgBoxStyle;

static inline void SetMsgBoxStyle( UINT8 uiStyle )
{
    s_uiMsgBoxStyle = uiStyle;
}

static inline UINT8 GetMsgBoxStyle()
{
    return s_uiMsgBoxStyle;
}

UINT32 MessageBoxCallbackFunc( UINT32 uiMsg )
{
    static UINT8    s_uiCurBtn;
    WND_PARAM       mbParam = GetWindowInfo();
    UINT32          uiY = mbParam.uiHeight - ROW_HEI;
    
    switch( uiMsg )
    {
    case IRC_ACTIVATE:
      
        switch( GetMsgBoxStyle() )
        {
        case MB_OK:
            s_uiCurBtn  = IDOK;
            ShowWindowText( "OK", ( mbParam.uiWidth >> 1 ) - 25, uiY, 2, 4 );
            break;
            
        case MB_YESNO:
//            s_uiCurBtn  = IDYES;
            s_uiCurBtn  = IDNO; 
            goto DRAW_MSGBOX_BTN;
            break;
            
        case MB_NORMAL:
        default:
            s_uiCurBtn = IDDEFAULT;
            break;
        }
        break;
       
    case IRC_SELECT:
    case IRC_PLAY_SELECT:
        if( ( GetMsgBoxStyle() == MB_OK ) || ( GetMsgBoxStyle() == MB_YESNO ) )
            ExitWindow( s_uiCurBtn );
        break;
            
    case IRC_LEFT:
        if( GetMsgBoxStyle() == MB_YESNO )
        {
            s_uiCurBtn  = IDYES;
            goto DRAW_MSGBOX_BTN;
        }
        break;
        
    case IRC_RIGHT:
        if( GetMsgBoxStyle() == MB_YESNO )
        {
            s_uiCurBtn  = IDNO;
            goto DRAW_MSGBOX_BTN;
        }
        break;
    }
    
    return s_uiCurBtn;

DRAW_MSGBOX_BTN:
    {
    UINT32 uiBtnPos = mbParam.uiWidth / 3;
    ShowWindowText( "YES", uiBtnPos - 25, uiY, 2, ( s_uiCurBtn == IDYES ) ? 4 : 6 );
    ShowWindowText( "NO", ( uiBtnPos << 1 ) - 25, uiY, 2, ( s_uiCurBtn == IDNO ) ? 4 : 6 );
    }
    return s_uiCurBtn;
}

// **************************************************************************************** //

static UINT32 s_uiCountDownInitVal;

static inline void SetCountDown( UINT32 uiCountDown )
{
    s_uiCountDownInitVal = uiCountDown;
}

UINT32 CountDownCallbackProc( UINT32 uiMsg )
{
    MessageBoxCallbackFunc( uiMsg );

    static UINT32 s_uiCountDown;
    
    switch( uiMsg )
    {
    case IRC_ACTIVATE:
    case IRC_LEFT:
    case IRC_RIGHT:
        goto RENEW_COUNTDOWN; 
        break;
        
    case IRC_DESTROY:
        KillTimer();
        break;

    case IRC_TIMER:
    {
        if( s_uiCountDown == 0 )
        {
            if( GetMsgBoxStyle() == MB_OK )
                ExitWindow( IDOK );
            else if( GetMsgBoxStyle() == MB_YESNO )
                ExitWindow( IDNO );
            else
                ExitWindow( IDDEFAULT );
        }
        else
        {
            s_uiCountDown--;
            goto SHOW_COUNTDOWN_MSG;
        }

        break;
    }
    }

    return s_uiCountDown;
    
RENEW_COUNTDOWN:
    s_uiCountDown = s_uiCountDownInitVal;
    SetTimer( 100 );       

SHOW_COUNTDOWN_MSG:
    psprintf( linebuf, "YOU HAVE %d SECS LEFT.", s_uiCountDown );
//    ShowWindowText( linebuf, 2, 140, 2, 6 );
    ShowWindowText( linebuf, 2, 96, 2, 3 );

    return s_uiCountDown;
}

// **************************************************************************************** //
// region : pre-created osd region
// x,y    : which coordinate will be draw in the pre-created region
// cap    : the caption of warning message box
// txt    : the text of warning message box
// type   : warning message box type, can be MB_OK(0), MB_YESNO(1)
// size   : warning message box size, can be SMALL, MEDLE, LARGE
// uiCount: count down time
MESSAGEBOX_RETURN_TYPE Warning_box( BYTE region, const char *cap, const char *txt, WARNBOX_TYPE type, WARNBOX_SIZE size, UINT32 uiCountDown )
{
    SetMsgBoxStyle( type );
    
    if( uiCountDown )
    {
        SetCountDown( uiCountDown );
        RegisterCallback( CountDownCallbackProc );
    }
    else
    {
        RegisterCallback( MessageBoxCallbackFunc );
    }
    
    CreateWindow( region, cap, (WS_CAPTION|WS_THICKFRAME|WS_SYSMENU), msg_box_size[size][0], msg_box_size[size][1], msg_box_size[size][2], msg_box_size[size][3] );
    ShowWindow();
//    ShowWindowText( txt, 2, 2, 2, 6 );
    ShowWindowText( txt, 2, 2, 2, 3 ); 
#if defined(SUPPORT_SW_OSD_SCALING)||defined(Simplay_warning)	//eric lin,2006-07-06,for Simplay format warning message 
    return WindowMain(IRC_ACTIVATE);
#else
    return WindowMain();
#endif    
}

#endif
// **************************************************************************************** //
