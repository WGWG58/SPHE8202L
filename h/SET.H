#ifndef _SET_H_
#define _SET_H_

#include "ver.h"
#include "..\\user_init.h"
#include "board.h"

/*
* Define DVD Release or Debug Version
*/
#define DVDRELEASE

#ifndef DVDRELEASE
//must re-make pe/task
//#define TASK_GBG    //must run pe.bat and task.bat
//#define ENABLE_SDRAM_OV_RANGE_INTR  //terry,2004/4/12 04:32PM
#else
//#define ENABLE_UART0_IN_RELEASE_MODE
#endif

#ifdef PORTABLE_DVD
	#define SUPPORT_SDRAM_64M_ESP_16Mbits
	#define ESP_RESEEK  //Jack added 06/06/06
	#undef SUPPORT_VFD
#endif

#ifdef DESKTOP_ESP  //wthsin, 2005/3/2 11:31am
    #define SUPPORT_SDRAM_64M_ESP_16Mbits
#endif //#ifdef DESKTOP_ESP 
#define AUDDRV

/*
* Define DVD Servo option
*/
#if defined(PMP_DVD)
  #define NO_DVD_SERVO //ycwen 2004/08/18 for power saving.
#elif defined (IC_1002)
#else  //default
  #define DVD_SERVO
#endif

#define DVD_SERVO_REAL_TURN_OFF//nono add. 4-12-30 11:23 only for use servo_turn_off().

/*
* Emulation mode setting
*/
/*#define EMU_MODE*/
#ifdef EMU_MODE
    #define NO_EEPORM
    #define NO_AUDIO_DSP
    #define UOP_DISABLE
#endif


/*
*  Video seting
*/
#define NES_USE_GRAPH
#define NEW_JPEG
#define ZOOMOUT_USE_DECIMATION
/*#define USE_711*/
//#ifndef PMP_DVD
//#define TV_USE_HALF_SWING//nono 5-5-17 0:21 move to cust_pre_def.h
//#endif

//#define TEST_SERVO      //define it to do some servo testing mode, Jeff 20030904
#ifdef TEST_SERVO
	#define TEST_SERVO_RUN_TIME			500
#endif//TEST_SERVO

//terry,2003/12/21 09:13PM
//#define LINK_LIB_TEST
//#define LINK_LIB_CH
#include "sunplus_user.h"        //terry,2003/12/30 10:42AM


//for displaying SDRAM information and version-date in CUSTM page
#ifdef PORTABLE_DVD
	#ifdef SUPPORT_SDRAM_64M_ESP_16Mbits
		#define SDRAM_SIZE "64M"	//64Mb*1
		#define SDRAM_BUS "16BIT"
	#elif defined(SUPPORT_SDRAM_16MX2_ESP_32Mbits) 
		#define SDRAM_SIZE "32M"	//16Mb*2
		#define SDRAM_BUS "32BIT"	
	#else	//#define SUPPORT_SDRAM_64MX2_ESP_32Mbits
		#define SDRAM_SIZE "128M"	//64Mb*2
		#define SDRAM_BUS "32BIT"		
	#endif		
#else
	#ifdef SDRAM_16Mb_Mode
		#define SDRAM_SIZE "16M"	//16Mb*1
	#else
		#define SDRAM_SIZE "32M"	//16M*2
	#endif
	#ifdef SDRAM_BUS_32BITS
		#define SDRAM_BUS "32BIT"
	#else
		#define SDRAM_BUS "16BIT"
	#endif
#endif

#endif //#ifndef _SET_H_

