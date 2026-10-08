//====================================================================================
// File name  : memmap0_dvb.h
// Deacription: 8202A-256/8202D+6600 64M DVB memory mapping
// Creator    : wthsin
// Maintain   :  
// -----------------------------------------------------------------------------------
// Revision History   
//          2005.06.15 create this file
//          2006.01.16 maintain: move all DVB memory blocks to this file
//====================================================================================
#ifndef _MEMMAP0_DVB_
#define _MEMMAP0_DVB_

#include "user_init.h"
  
//DVB-T Demux segment
#define DEMUX_BUFFER_YA           (4096) 
//For High Bitrate performance issue
#define DEMUX_BUFFER_SIZE         (1024+300)
//#define DEMUX_BUFFER_SIZE         (770)

/* EPG/TTX/SUBTITLE FUNCTION COMMON BUFFER POINT */
#define DVB_FUNCTION_BUFFER_YA    (DEMUX_BUFFER_YA + DEMUX_BUFFER_SIZE)  
/* Maximum Buffer Size of EPG/TTX/SUBTITLE FUNCTION COMMON BUFFER */
 #define DVB_EPG_BUFFER_YA          DVB_FUNCTION_BUFFER_YA
 #define DVB_EPG_BUFFER_SIZE        443 
 #define DVB_TTX_BUFFER_YA          DVB_FUNCTION_BUFFER_YA
 #ifdef SUPPORT_SOFT_HW_TTX       //yangli mod for hwttx,2006-10-10 13:41
 #define DVB_TTX_BUFFER_SIZE        510//486
 #else
 #define DVB_TTX_BUFFER_SIZE        486
 #endif  //// #ifdef SUPPORT_SOFT_HW_TTX
 #define DVB_SUBTITLE_BUFFER_YA     DVB_FUNCTION_BUFFER_YA
 #define DVB_SUBTITLE_BUFFER_TSIZE  350

#ifdef CHECK_SCRAMBLED_BY_CA_DESC
/*PSI BUFFER POINT*/
#define DEMUX_PSI_POOL              DVB_FUNCTION_BUFFER_YA+DVB_TTX_BUFFER_SIZE
#define DEMUX_PSI_POOL_SZ	        (30)//(90)
#define DEMUX_PSI_LEN		        (3)
#define DVB_FUNCTION_BUFFER_SIZE    (DVB_TTX_BUFFER_SIZE+DEMUX_PSI_POOL_SZ)
#else
#define DVB_FUNCTION_BUFFER_SIZE    DVB_TTX_BUFFER_SIZE //TTX used maximum commom buffer
#endif

#ifdef SUPPORT_SUBTITLE

#define DVB_SUBTITLE_OSD_BUFFER_YA   (DVB_FUNCTION_BUFFER_YA+DVB_FUNCTION_BUFFER_SIZE)
#define DVB_SUBTITLE_OSD_BUFFER_SIZE 200//200K for subtitle osd buffer

#ifdef TTX_ENHANCED 	//tcf added 2006-3-29 02:18ÏÂÎç
    #define TTX_CACHE_YA 		    (DVB_SUBTITLE_OSD_BUFFER_YA+DVB_SUBTITLE_OSD_BUFFER_SIZE)
    #define TTX_CACHE_SIZE 			1024
    #define DVB_NOUSE_SDRAM_BUFFER_YA   (TTX_CACHE_YA+TTX_CACHE_SIZE)
    #define DVB_NOUSE_SDRAM_BUFFER_SIZE (4096-TTX_CACHE_SIZE-DVB_SUBTITLE_OSD_BUFFER_SIZE-DEMUX_BUFFER_SIZE-DVB_FUNCTION_BUFFER_SIZE-DVB_CODESIZE-DVB_CS_BUFFER_SIZE-DVB_PM_BUFFER_SIZE)
#else
#define DVB_NOUSE_SDRAM_BUFFER_YA   (DVB_SUBTITLE_OSD_BUFFER_YA+DVB_SUBTITLE_OSD_BUFFER_SIZE)
#define DVB_NOUSE_SDRAM_BUFFER_SIZE (4096-DVB_SUBTITLE_OSD_BUFFER_SIZE-DEMUX_BUFFER_SIZE-DVB_FUNCTION_BUFFER_SIZE-DVB_CODESIZE-DVB_CS_BUFFER_SIZE-DVB_PM_BUFFER_SIZE)
#endif

#else //not support subtitle

#ifdef TTX_ENHANCED 	//tcf added 2006-3-29 02:18ÏÂÎç
    #define TTX_CACHE_YA 		(DVB_FUNCTION_BUFFER_YA+DVB_FUNCTION_BUFFER_SIZE)
    #define TTX_CACHE_SIZE      1024
    #define DVB_NOUSE_SDRAM_BUFFER_YA   (TTX_CACHE_YA+TTX_CACHE_SIZE)
    #define DVB_NOUSE_SDRAM_BUFFER_SIZE (4096-TTX_CACHE_SIZE-DEMUX_BUFFER_SIZE-DVB_FUNCTION_BUFFER_SIZE-DVB_CODESIZE-DVB_CS_BUFFER_SIZE-DVB_PM_BUFFER_SIZE)
#else 
#define DVB_NOUSE_SDRAM_BUFFER_YA   (DVB_FUNCTION_BUFFER_YA+DVB_FUNCTION_BUFFER_SIZE)
#define DVB_NOUSE_SDRAM_BUFFER_SIZE (4096-DEMUX_BUFFER_SIZE-DVB_FUNCTION_BUFFER_SIZE-DVB_CODESIZE-DVB_CS_BUFFER_SIZE-DVB_PM_BUFFER_SIZE)   
#endif  //end #ifdef TTX_ENHANCED 	//tcf added 2006-3-29 02:18ÏÂÎç

#endif  //end #ifdef SUPPORT_SUBTITLE

#define DVB_CODE_YA                 (DVB_NOUSE_SDRAM_BUFFER_YA+DVB_NOUSE_SDRAM_BUFFER_SIZE)
#define DVB_CODESIZE                (932)  
//DVB-T CS Global Variable Buffer
#define DVB_CS_BUFFER_YA            (DVB_CODE_YA + DVB_CODESIZE)
#define DVB_CS_BUFFER_SIZE          60 
//DVB-T Program Mangment  segment 
#define DVB_PM_BUFFER_YA            (DVB_CS_BUFFER_YA + DVB_CS_BUFFER_SIZE)
#define DVB_PM_BUFFER_SIZE          32 

#ifdef ENLARGE_STATCK_SIZE    //sunzhh add for epg scroll 20060414
#define NEW_MAIN_STACK_SIZE               	5
#define NEW_A_MAIN_STACK_BOM                (DVB_CODE_YA)
#define NEW_A_MAIN_STACK_TOP                (NEW_A_MAIN_STACK_BOM - NEW_MAIN_STACK_SIZE-1)
#define NEW_RMAIN_STACK_SIZE              	(NEW_A_MAIN_STACK_BOM - NEW_A_MAIN_STACK_TOP)
//maybe need add "system halt proction"
#endif	

#define DVB_BUFFER_END_YA           (DVB_PM_BUFFER_YA+ DVB_PM_BUFFER_SIZE) //Must be 8192

//system halt protection
#if (DVB_BUFFER_END_YA > 8192)
    #error "DVB SDRAM config size overflow!!!"
#endif

#define DVB_CODE_INFO_SIZE          (DVB_BUFFER_END_YA-DVB_CODE_YA)
#ifdef DESKTOP_ESP                //////////yanlgli add for dektop esp,2006-7-14 13:36
#define DVB_CODEandChInfoSIZE (8192-DVB_CODE_YA) 
#if (DVB_CODEandChInfoSIZE > 2048)
    #error "SDRAM no size for esp!!!"
#endif
#endif 
    
#endif  /* #define _MEMMAP0_DVB  */

