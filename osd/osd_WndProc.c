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
|  File Name    :  osd_WindowProc.c
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
#ifdef SUPPORT_WINDOW_PROC

#include "global.h"
#include "ircode.h"
#include "osd_api.h"
#include "osd_AppAPI.h"
#include "kinf.h"
#include "timer.h"

// **************************************************************************************** //
#ifndef NEW_OSD_DRIVER
#error "Must define NEW_OSD_DRIVER\n"
#endif

#ifndef DVDRELEASE
    #define WND_PROC_DBG
#endif

#ifndef WND_PROC_DBG
    #undef printf
    #undef print_block
    #define printf(f, a...) do {} while (0)
    #define print_block(x,y) do {} while (0)
#endif

// **************************************************************************************** //

WND_PARAM g_mbParam;
static UINT32 (*s_pCallbackFunc)( UINT32 );
static UINT32 s_uiPrevTime;
static UINT8  s_uiReturnValue;
static UINT32 s_uiElapseTime                = 0xFFFFFFFF;

// **************************************************************************************** //
void ShowWindowText( const char* pText, UINT16 uiX, UINT16 uiY, UINT8 uiFontColor, UINT8 uiBackColor )
{
#ifndef DVDRELEASE
    if( !pText || strlen( pText ) == 0 )
        return;
#endif
    
    UINT8       uiTextHeight    = g_mbParam.uiHeight / ROW_HEI;
    UINT8       uiTextWidth     = g_mbParam.uiWidth >> 4;
    UINT8       aTextArray[ uiTextWidth ];
    coordinate  coStart;
    
    coStart.x   = g_mbParam.uiX + uiX;
    coStart.y   = g_mbParam.uiY + uiY;
    if( g_mbParam.uiStyle & WS_CAPTION )
        coStart.y += ROW_HEI;
    
    UINT8 uiLineCount   = 0;
    UINT8 uiChar        = *pText;
    
    while( uiChar != '\0' )
    {
        UINT8 uiCount = 0;
        while( uiChar != '\0' )
        {
            if( uiChar == '\n' || uiCount >= uiTextWidth - 1 )
                break;

            aTextArray[uiCount] = uiChar;
            pText++;
            uiCount++;
            uiChar = *pText;
        }
        aTextArray[uiCount] = '\0';

        osd_draw_string( &coStart, aTextArray, uiFontColor, uiBackColor, g_mbParam.uiRegion,0 );
        coStart.y   += ROW_HEI;

        uiLineCount++;
        if( uiLineCount >= uiTextHeight )
            break;
    };
}

// **************************************************************************************** //
void RegisterCallback( UINT32 (*pFunc)( UINT32 ) )
{
#ifndef DVDRELEASE
    if( !pFunc )
        printf( "Parameter of RegisterCallback can't be NULL!\n" );
#endif
    s_pCallbackFunc = pFunc;
}

// **************************************************************************************** //
void SetTimer( UINT32 uiElapse )
{
    set_rtc_val( 0 );
    s_uiPrevTime    = 0;
    s_uiElapseTime  = uiElapse;
}

// **************************************************************************************** //
void KillTimer()
{
    s_uiPrevTime    = 0;
    s_uiElapseTime  = 0xFFFFFFFF;
}

// **************************************************************************************** //
void ExitWindow( UINT8 uiParam )
{
    s_uiReturnValue = uiParam;
}

// **************************************************************************************** //
void CreateWindow( BYTE uiRegion, const char* pCaption, UINT8 uiStyle, UINT16 uiX, UINT16 uiY, UINT16 uiWidth, UINT16 uiHeight )
{
    g_mbParam.uiRegion  = uiRegion;
    g_mbParam.pCaption  = pCaption;
    g_mbParam.uiStyle   = uiStyle;
    g_mbParam.uiX       = uiX;
    g_mbParam.uiY       = uiY;
    g_mbParam.uiWidth   = uiWidth;
    g_mbParam.uiHeight  = uiHeight;
}

// **************************************************************************************** //
void ShowWindow()
{
    // Draw Window
    coordinate  coStart;
    dimension   diSize;
    UINT8       uiStyle  = g_mbParam.uiStyle;
    UINT8       uiRegion = g_mbParam.uiRegion;

    coStart.x           = g_mbParam.uiX;
    coStart.y           = g_mbParam.uiY;
    diSize.x_length     = g_mbParam.uiWidth;
    
    if( uiStyle & WS_CAPTION )
    {
        diSize.y_length     = ROW_HEI;
        osd_draw_rectangle( &coStart, &diSize, 5, uiRegion );
        
        if( uiStyle & WS_THICKFRAME )
            osd_draw_rectangle_border( &coStart, &diSize, 1, 2, uiRegion );
 
        coStart.y           += ROW_HEI;

    }

    diSize.y_length     = g_mbParam.uiHeight;
    osd_draw_rectangle       ( &coStart, &diSize, 6, uiRegion );
    if( uiStyle & WS_THICKFRAME )
        osd_draw_rectangle_border( &coStart, &diSize, 1, 2, uiRegion );

    if( ( uiStyle & WS_CAPTION ) && ( uiStyle & WS_SYSMENU ) )
    {
        // Draw Window Icon (Close at right-up corner)
        coStart.x           = g_mbParam.uiX + g_mbParam.uiWidth - 22;
        coStart.y           = g_mbParam.uiY + 3;
        osd_draw_string( &coStart, "X", 2, 5, uiRegion,0 );
        
        coStart.x           = g_mbParam.uiX + g_mbParam.uiWidth - 24;
        diSize.x_length     = 20;
        diSize.y_length     = 24;
        osd_draw_rectangle_border( &coStart, &diSize, 2, 2, uiRegion );

        // Draw Window Icon (Min at left-up corner)
        coStart.x           = g_mbParam.uiX + 6;
        coStart.y           = g_mbParam.uiY + 3;
        osd_draw_string( &coStart, "-", 2, 5, uiRegion ,0);
        coStart.x           = g_mbParam.uiX + 4;
        diSize.x_length     = 20;
        diSize.y_length     = 24;
        osd_draw_rectangle_border( &coStart, &diSize, 2, 2, uiRegion );
    }
    
    // Draw Caption
    if( ( uiStyle & WS_CAPTION ) && g_mbParam.pCaption )
    {
        UINT8   uiWidth     = g_mbParam.uiWidth >> 4;
        UINT8   uiStrLen    = strlen( g_mbParam.pCaption );
        UINT8   aTextArray[ uiWidth + 1 ];
    
        uiStrLen = ( uiStrLen > uiWidth ) ? uiWidth : uiStrLen;
        memcpy( aTextArray, g_mbParam.pCaption, uiStrLen );
        aTextArray[ uiStrLen ] = '\0';
    
        coStart.x           =  g_mbParam.uiX + 28;
        coStart.y           =  g_mbParam.uiY + 3;    
        osd_draw_string( &coStart, g_mbParam.pCaption, 2, 5, uiRegion, 0);
    }
}

// **************************************************************************************** //
//UINT8 WindowMain()		//linrc change for create other UI 2005-12-15 15:29
UINT8 WindowMain(UINT16 Tvg_CMD)
{
    watchdog_onoff(0);
    
    s_uiReturnValue = 0xFF;
    s_pCallbackFunc( Tvg_CMD );
    //s_pCallbackFunc( IRC_ACTIVATE );
    
    do
    {
        UINT32 uiCurTime = get_rtc_val();
        if( uiCurTime - s_uiPrevTime > s_uiElapseTime )
        {
            s_uiPrevTime = uiCurTime;
            s_pCallbackFunc( IRC_TIMER );
        }

        extern UINT16 GetIRCode();
        UINT32  rx = GetIRCode();

        if( rx != IR_CODE_MAX_NUM )
            s_pCallbackFunc( rx );
	#ifdef Simplay_warning	//eric lin,2006-07-06,for Simplay format warning message
        extern void HDCP_polling();
        HDCP_polling();//wait press yes or no,but still need to do Ri compare per 2 second by hdcp_polling().
        #endif	//#ifdef Simplay_warning       
#ifdef SUPPORT_SW_OSD_SCALING 
//    if((GET_TV_RESOLUTION() ==HD_720) || (GET_TV_RESOLUTION() ==HD_1080)) {
//        osd_scaling_region();
//    }        
#endif      
    } while( s_uiReturnValue == 0xFF );

    s_pCallbackFunc( IRC_DESTROY );
    watchdog_onoff(1);

    return s_uiReturnValue;
}
#endif
// **************************************************************************************** //
