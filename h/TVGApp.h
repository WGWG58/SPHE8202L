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
|  File Name   :  TVGApp.h
|
|  Description :  TV Guardian communication interface header
|
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2005/03/23      yltseng         Creating
|--------------------------------------------------------------------------------*/ 
#ifndef _TVG_APP_H_
#define _TVG_APP_H_

#include "user_init.h"

#ifdef SUPPORT_TVG

#include "TVG\TVGAPI.h"

extern void     TVGInitSystem( UINT8 );
extern void     TVGProcessData( UINT8 *ccdata, UINT8 field );
extern void     TVGRequestMute( int mute_flg );
extern UINT8    TVGControlMute();

extern void     TVGSetMode( UINT8 uiMode );
extern void     TVGSetWordSets( UINT8 uiMode, UINT8 uiFlag );
extern void     TVGSetCCOperation( UINT8 uiMode );
extern void     TVGSetCCChannel( UINT8 uiMode );

        #ifdef SUPPORT_TVG_ACTIVATION
extern UINT32   TVGActivationProcess();
extern void     TVGClearUnitID();
        #else
#define         TVGActivationProcess()
#define         TVGClearUnitID()
        #endif
UINT8 MessageBox_TVGHelp();
UINT8 MessageBox_TVGSTART();

#else//#ifdef SUPPORT_TVG

#define TVGInitSystem( ... )
#define TVGProcessData( ... )
#define TVGRequestMute( ... )
#define TVGClearUnitID( ... )
#define TVGControlMute()    FALSE

#define TVGSetMode( ... )
#define TVGSetWordSets( ... )
#define TVGSetCCOperation( ... )
#define TVGSetCCChannel( ... )

#define TVGActivationProcess()

#endif//#ifdef SUPPORT_TVG

#endif//#ifndef _TVG_APP_H_


