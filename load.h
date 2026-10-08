#include ".\\h\\set.h"
#include "user_init.h"

/*
** This file is for linker-script and others, don't put
** cpp style comment here.
** History 
** Terry,2005/4/5 05:18下午
** Terry,2005/6/22 10:56下午
*/
#ifndef __LOAD_H
#define __LOAD_H

#ifndef SUPPORT_HDD_ACCESS
#ifndef SUPPORT_MIDI
//------------------------------------------------------start------------------------
//-------------------------------for all rom code
//#define LOAD_OTHER
//#define UNLOAD_ROMCODE
#ifdef LOAD_MANY_CODE_TO_64M_SDRAM
#define UNLOAD_ROMCODE
#endif


//-------------------------------default load rom code
#define LOAD_WMA
#define LOAD_JPEG
#define LOAD_MPEG
#define LOAD_CDROM
#define LOAD_NAV
#define LOAD_SERVO
#define LOAD_AP

#define LOAD_MP4
#define LOAD_AP_OTHER
#define LOAD_DVB

#if defined(SUPPORT_SERVO_CODE_NOT_RUN_IN_SDRAM)
	#undef LOAD_SERVO
#endif

#if defined(PORTABLE_DVD)||defined(ALCO_PORTABLE_DVD_8202D_DVB)
	#undef LOAD_AP
	#undef LOAD_MP4
	#undef LOAD_AP_OTHER
	#undef LOAD_NAV
#endif

/* 
//kevinmonkey 060919, we do not official support 32m DivX6 although possible. Try not use it or use new 8202L memory mapping
//which possible to allocate continuous memory space
#ifdef SUPPORT_DIVX6 
    #ifndef SUPPORT_DIVX6_64Mb
        #undef LOAD_CDROM  //kevinmonkey 051122 in order to get a continuous space after avi buffer when playing divx6, cdrom code is unloaded.
    #endif  //#ifndef SUPPORT_DIVX6_64Mb
#endif  //#ifdef SUPPORT_DIVX6
*/

#if (defined(IC_8202L) || defined(IC_8203A)) && defined(SDRAM_32Mb_Mode) && defined(DIP_CFG_ENABLE)
#undef LOAD_WMA
#undef LOAD_MP4
#endif

//------------------------------undefine start
#ifndef SUPPORT_8202_DVB     //terry,2005/10/12 07:51下午
#undef LOAD_DVB
#else
#undef LOAD_AP_OTHER
#undef LOAD_NAV //Jack added for desktop+dvb-t
#endif

#ifdef FILE_MODE_WRITE     //sunzhh add 20041223
#undef LOAD_AP
#endif

#ifdef SDRAM_16Mb_Mode   
#undef LOAD_AP
#undef LOAD_AP_OTHER
#undef LOAD_MP4
    
    #if !defined(TURBO_DECODE)|| (defined(SUPPORT_MP4_SUBTITLE)&&defined(SUPPORT_MP4 ))
    #undef LOAD_SERVO    
    #endif
    
    #if !defined(TURBO_DECODE)||!defined(COMPRESS_ROM_CODE_040)// || (defined(SUPPORT_DVD_FULL_SUBTITLE)&&defined(SUPPORT_MP4 )) //terry,mark it,2005/6/27 10:09下午
    #undef LOAD_MPEG
    #endif
    
    #if !defined(TURBO_DECODE)||(defined(DVD_SRV_BUF_SMALL)&&defined(SUPPORT_MP4 ))||!defined(COMPRESS_ROM_CODE_040)
    #undef LOAD_NAV//terry,2005/6/23 02:12下午
    #endif
    
    #ifdef SETUP_PROGRAM_IN_PLACE_UNDER_16M     // 2004/12/27 yltseng
    // Because in 16M jpeg, if user changes audio parameters in setup menu, dsp codec will
    // write some info in PCM area, but currently this area puts jpeg codes.
    // So in this situation, we need to undef JPEG codes, in order not to be overwrite by dsp codec
    #undef LOAD_JPEG
    #endif
    
#endif

#ifndef DVDRELEASE
#ifndef BOOT_LOAD_ROMA //terry,2005/3/6 10:16PM
#undef LOAD_AP
#undef LOAD_NAV
#endif
#endif

#ifdef SUPPORT_USB
#undef LOAD_AP_OTHER//nono 4-4-14 13:55
//#undef LOAD_CDROM
#endif

#ifdef SUPPORT_ID3
#undef LOAD_AP_OTHER//nono 4-4-14 13:55
#endif

#if defined(GBM_DVD)&&defined(NEW_STYLE_SETUP)//4-2-5 17:14
#undef LOAD_CDROM
#undef LOAD_JPEG
#endif

#ifdef TONIC_DVD
#undef LOAD_WMA
#undef LOAD_JPEG
#endif

#if defined(NINTAUS_DVD)&&!defined(NIN_612_4M)//4-2-20 3:34
#undef LOAD_CDROM
#undef LOAD_JPEG
#undef LOAD_NAV
#undef LOAD_WMA
#endif

#if defined(BBK_DSS_555_DVD)||defined(BBK_DV911S) //fengjl  add 2004-03-13 11:56
#undef LOAD_JPEG
#undef LOAD_MPEG
#undef LOAD_NAV
#undef LOAD_WMA
#endif

#ifdef SUPPORT_RECEIVER//define dvd release can not run.huziqin 2004-4-29
#undef LOAD_MPEG
#undef LOAD_NAV
#undef LOAD_AP
#endif

#ifdef SUPPORT_HD_DVD /*huziqin fix sdram full*/
#undef LOAD_AP
#endif


#if defined(THAKRAL_DVD)&&defined(SDRAM_16Mb_Mode)&&defined(NEC16312SW)
#undef LOAD_JPEG
#endif 

#ifdef ALCO_PORTABLE_16M //added 05/08/11
#undef LOAD_CDROM
#undef LOAD_NAV
#endif

//----------------------------undefine ending
#endif //#ifndef SUPPORT_MIDI
#endif //#ifndef SUPPORT_HDD_ACCESS
#endif/*__LOAD_H*/
//-----------------------------------------ending-----------------------------
