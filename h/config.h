#ifndef __CONFIG_H
#define __CONFIG_H

#include "user_init.h"

#ifdef DVB1000_NON_OS  //Maoyong 2004-9-27 17:28
#include "dvbdef.h"
#endif

#define DVD728				// barry
#define FORSIMULATION		// barry
#define NO_WAIT_V_BLANK		// barry
//#define MONE_CKM		    // barry

/*
** configuration of mpeg2/mpeg1 core controller
*/
#define	CONFIG_VCD	0
#define	CONFIG_SVCD	1
#define	CONFIG_DVD	2

#define	CONFIG		CONFIG_DVD

#define	SUPPORT_CVD		1
#define	SUPPORT_SVCD		1
#define	SUPPORT_MPEG2		1
//#define SUPPORT_IR		1
//#define SUPPORT_VFD		1
//#define SUPPORT_OGT		1
//#define SUPPORT_MP3		1
#define SUPPORT_OSD		1

//#define SUPPORT_DEVICE_CDROM	1	
//#define SUPPORT_DEVICE_DVDROM	1

#ifdef DVDRELEASE
#undef  SUPPORT_EPP
#else
    #ifndef SUPPORT_EPP
        #define	SUPPORT_EPP		1
    #endif 
    /*
    	if soft UART is enable,
     	the gpio_sel[0:1] will be initialize to gpio mode on reset iop function
    */
    #ifdef TAS3001_AMP
    #define SOFT_UART_OUT		1
    #else
    //#define SOFT_UART_OUT		1
#endif

#endif

#ifdef SUPPORT_UART_UPGRADE // for doing upgrade via uart, we must turn on SUPPORT_EPP. Robert 020603
    #ifndef SUPPORT_EPP
        #define SUPPORT_EPP
    #endif
#endif 

//
// hardware control register 
#define GLOBAL_REGISTER				// use hardware reg

#if     (CONFIG==CONFIG_DVD)
#ifdef DVD728
#define RGST_OFFSET     0xbffe8000
#else
#define RGST_OFFSET     0xafff0000
#endif
#elif   (CONFIG==CONFIG_SVCD)
#define RGST_OFFSET     0x00510000
#elif   (CONFIG==CONFIG_VCD)
#define RGST_OFFSET     0x00510000
#endif

#define	RTC_TICKS	(100)			// 100-tick/s

#define	OLDAGDC		0

#define	POLLING_VIDEO_DECODE
#define	CHECK_PARSING_BARRIER
#define	PIC_INFO_SDRAM

#define	PARSE_GOP
//#define	PARSE_USER_DATA

#define	FRAME_DECODING
//#define FIELD_DECODING
#define	SYSTEM_LEN_MAX		2324

#define	CDDSP_CRC_RETRY		1
#define	CDDSP_RETRY_LOW		16
#define	CDDSP_RETRY		20
#define	CDDSP_RESTART_TIME	(2*RTC_TICKS)

/*
** GNU c specific definitions.
*/
#ifdef	__GNUC__
#define	ENABLE_INLINE
#if defined(ARM_EVM)
#define __value_in_regs
#define	ENABLE_INLINE
#endif
#endif

#ifdef	ENABLE_INLINE
#ifdef 	ARM_EVM
#define	INLINE	__inline
#else
#define	INLINE	inline
#endif
#else
#define	INLINE
#endif

/*
** parsing pause criteria
*/
#define	VBV_LIMIT		2	/* ROWs to stop parsing		*/
#define	ABV_LIMIT		4
#define	CBV_LIMIT		8

/*
** DMA batch, deprecated
*/
#define	DMA_BATCH		64

/*
** system input buffer (0-63)
*/
#define	SRV_IN_BUF		0
#define	SRV_IN_BATCH		DMA_BATCH

/*
** video output buffer (64-95)
*/
#define	VIDEO_OUT_BUF		(SRV_IN_BUF+SRV_IN_BATCH)
#define	VIDEO_OUT_BATCH		32	

/*
** audio output buffer (96-127)
*/
#define	AUDIO_OUT_BUF		(VIDEO_OUT_BUF+VIDEO_OUT_BATCH)
#define	AUDIO_OUT_BATCH		32	

/*
** OGT output buffer (128-160)
*/
#define	OGT_OUT_BUF		(AUDIO_OUT_BUF+AUDIO_OUT_BATCH)
#define	OGT_OUT_BATCH		32	

/*
**
*/
#define TEMP_DMA_RAM		(OGT_OUT_BUF+OGT_OUT_BATCH)

//#define SUPPORT_VFD		1//move to user_init.h nono 2-9-16 23:10
#define PLAY_SPEED		2

#endif/*__CONFIG_H*/

