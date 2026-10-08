//====================================================================================
// memmap0s_tb.h
// 8202 with turbo decoding 16Mb memory mapping
// Creator  : kevinmonkey
// Maintain :
// -----------------------------------------------------------------------------------
// Revision History   
//          2005.04.05   Created.
// 2005/12/28 yltseng
//====================================================================================

#include "set.h"
//====================================================================================
// Decode mode memory config
//====================================================================================
#define P_VIDEO_COMPRESS        (RF_COMPRESS_888 \
                                |RF_COMPRESS_DITHER_OFF \
                                |RF_COMPRESS_CHROMA_FULL)
#define	GN_VIDEO_COMPRESS       (P_VIDEO_COMPRESS)
#define	GP_VIDEO_COMPRESS       (P_VIDEO_COMPRESS)
#define	GS_VIDEO_COMPRESS       (P_VIDEO_COMPRESS)

#define INVALID_POINTER         (JPEG_YA)

//====================================================================================
// task stack Allocation 
//====================================================================================
#define A_MAIN_TASK_TOP         (1)     // 1.3
#ifdef SUPPORT_SDRAM16M_AC3_5_1CH_OUTPUT
#define MAIN_TASK_SIZE          (1)     // 1.7 , terry,2004/7/26 02:52PM
#define A_MAIN_TASK_BOM         (3)
#else   //!SUPPORT_SDRAM16M_AC3_5_1CH_OUTPUT
#define MAIN_TASK_SIZE          (2)     // 1.7 , terry,2004/7/26 02:52PM
#define A_MAIN_TASK_BOM         (4)
#endif  //#ifdef SUPPORT_SDRAM16M_AC3_5_1CH_OUTPUT
#define DBG_STACK_SIZE          (2)
#define A_DBG_TASK_BOM          (2048)  // put it at 2045~2047k range
#define A_DBG_TASK_TOP          (A_DBG_TASK_BOM - DBG_STACK_SIZE)

//====================================================================================
// Top Memory Allocation
//====================================================================================
//(Common for all configuration)
//DSP size
#ifdef  SUPPORT_SDRAM16M_AC3_5_1CH_OUTPUT
#define DSP_SIZE                (68)
#else	//two channel
#define DSP_SIZE                (66)
#endif	//#ifdef  SUPPORT_SDRAM16M_AC3_5_1CH_OUTPUT

#define MEM_START               (0)

#define A_IOPYA                 (MEM_START + 0)
#define IOP_SIZE                (2)
#define A_CDYA                  (A_IOPYA + IOP_SIZE + MAIN_TASK_SIZE)
#define CDSIZE                  (4)
#define SDRAM_CS_ST	            (A_CDYA + CDSIZE)

#ifdef  SUPPORT_SDRAM16M_AC3_5_1CH_OUTPUT
#define MEMORY_FROM_DSP_FOR_SDRAM_CS    (0)
#else
#define MEMORY_FROM_DSP_FOR_SDRAM_CS    (1)
#endif

#if defined(COMPRESS_ROM_CODE_040) && defined(DVDRELEASE)
    #ifdef SUPPORT_DVD_NATIVE_GAME		//linrc for NATIVE GAME 2005-10-19 17:12
        #define SDRAM_CS_SZ             (25+5+MEMORY_FROM_DSP_FOR_SDRAM_CS)
    #else
        #define SDRAM_CS_SZ             (25+2+MEMORY_FROM_DSP_FOR_SDRAM_CS) //ycwen 2005/11/16 add 2K for PCI_BUF
    #endif
#else
    #ifdef SUPPORT_DVD_NATIVE_GAME		//linrc for NATIVE GAME 2005-10-19 17:12
        #define SDRAM_CS_SZ             (25+1+5+MEMORY_FROM_DSP_FOR_SDRAM_CS)
    #else
        #define SDRAM_CS_SZ             (25+1+2+MEMORY_FROM_DSP_FOR_SDRAM_CS)  //kevinmonkey 050302 temporary add 1 cause SDRAM_CS_SZ is now full
    #endif                                        //ycwen 2005/11/16 add 2K for PCI_BUF
#endif

#define A_DSP24YA               (SDRAM_CS_ST + SDRAM_CS_SZ)

#define END_SEG1                (A_DSP24YA+DSP_SIZE)

//====================================================================================
// Bottom Memory Allocation
//====================================================================================
// (Common for all configuration)
#ifndef DVD_SRV_BUF_SMALL
//SERVOBUF_COPY_USERTABLE_WHEN_RECONFIG is to keep user table intact.
//when the start point of servo buffer is reconfigurated, copy necessary user table to new 
//position. this is better since servo may temporarily use ,say, 5k for user table while 
//beginning reading disc but use only 2k after the initial stage. At this scenario
//SERVOBUF_USERTABLE_ALIGNED_TO_BOTTOM have to keep 5k at the bottom but 3k of them is not
//always in use.          kevinmonkey050714
#define SERVOBUF_COPY_USERTABLE_WHEN_RECONFIG
#endif //#ifndef DVD_SRV_BUF_SMALL

//OSD size
#ifdef SUPPORT_OSDSRT
#define EXTRA_OSDSIZE           (4)
#else   //!SUPPORT_OSDSRT
#define EXTRA_OSDSIZE           (0)
#endif  //#ifdef SUPPORT_OSDSRT

#ifdef NEW_DISPLAY_GOTO_OSD
#define BASIC_OSDSIZE           (3)
#else   //!NEW_DISPLAY_GOTO_OSD
#define BASIC_OSDSIZE           (6)
#endif  //#ifdef NEW_DISPLAY_GOTO_OSD

#define OSDSIZE                 (BASIC_OSDSIZE + EXTRA_OSDSIZE)

//Servo size
#define SERVO_3ECC_SIZE         (127)
#define SERVO_4ECC_SIZE         (170)
#define SERVO_5ECC_SIZE         (211)
#define SERVO_6ECC_SIZE         (254)
#define SERVO_7ECC_SIZE         (297)

#define JPEG_SERVO_SIZE         (SERVO_3ECC_SIZE)
#ifdef  DVD_SRV_BUF_SMALL
#define DVDV_SERVO_SIZE         (SERVO_3ECC_SIZE)
#else   //!DVD_SRV_BUF_SMALL
#define DVDV_SERVO_SIZE         (SERVO_4ECC_SIZE)
#endif  //DVD_SRV_BUF_SMALL

//Memory allocation
//OSD
#ifdef DVDRELEASE
#define OSD_BOTTOM_YA           (A_DBG_TASK_BOM)  //Leaves no DBG memory
#else
#define OSD_BOTTOM_YA           (A_DBG_TASK_TOP)
#endif
#define MN_OSDYA                (OSD_BOTTOM_YA - OSDSIZE)
#define P_OSDYA                 (MN_OSDYA)

//Servo
#define SERVOBUF_BOTTOM_YA      (MN_OSDYA - AP_CODESIZE)
#define A_DVD_SERVO_YA          (SERVOBUF_BOTTOM_YA - DVDV_SERVO_SIZE)
#define A_JPEG_SERVO_YA         (SERVOBUF_BOTTOM_YA - JPEG_SERVO_SIZE)

//====================================================================================
// MPEG,AVI Video Frame Buffer Memory Allocation
//====================================================================================
//kevinmonkey 050309 align PAL and NTSC memory layout. NTSC has some(153k) blank 
//space before END_VIDEO_FRAMEBUF 

//Frame buffer size
#define LUMA_SIZE               (405)   // PAL D1 luma size      720x576
#define CHROMA_SIZE             (203)   // PAL D1 chroma size    720x576/2

#define P_LUMA_SIZE             (405)   // PAL D1 luma size      720x576
#define P_CHROMA_SIZE           (203)   // PAL D1 chroma size    720*576/2
#define N_LUMA_SIZE             (338)   // NTSC D1 luma size     720*480
#define N_CHROMA_SIZE           (169)   // NTSC D1 chroma size   720*480/2
#define M_LUMA_SIZE             (270)   // PAL 2/3D1 luma size   480x576
#define M_CHROMA_SIZE           (135)   // PAL 2/3D1 chroma size 480x576/2

#define P_BIDIR_LUMA_SIZE        (80)   // PAL D1 luma size 
#define P_BIDIR_CHROMA_SIZE      (40)   // PAL D1 chroma size 
#define N_BIDIR_LUMA_SIZE       (214)   // NTSC D1 luma size 
#define N_BIDIR_CHROMA_SIZE     (107)   // NTSC D1 chroma size 
#define M_BIDIR_LUMA_SIZE       (345)   // NTSC D1 luma size with 32 pixel aligned 736x480
#define M_BIDIR_CHROMA_SIZE     (173)   // NTSC D1 chroma size with 32 pixel aligned 736x480/2

#ifdef  REDUCE_SUP_SRT_FOR_FS9660  //kevinmonkey 0713 extra BIDIR frame buffer comes from FS9660 buffer
#define EXTRA_BIRDIR_LUMA_SIZE   (22)   //((25+9)*(2/3))  2/3 of fs 9660 total buffer
#define EXTRA_BIRDIR_CHROMA_SIZE (12)   //((25+9)*(1/3))  1/3 of fs 9660 total buffer
#elif   (EXTRA_FS9660BUF == 0)
#define EXTRA_BIRDIR_LUMA_SIZE   (0)
#define EXTRA_BIRDIR_CHROMA_SIZE (0)
#else   //unexpected extra buffer size
#error  "please take care of B frame extra buffer size."
#endif

//PAL
#define	P_REF0_LUMA             (END_SEG1)
#define	P_REF0_LUMA_END         (P_REF0_LUMA + LUMA_SIZE)
#define	P_REF0_CHROMA           (P_REF0_LUMA_END)
#define	P_REF0_CHROMA_END       (P_REF0_CHROMA + CHROMA_SIZE)
#define	P_REF1_LUMA             (P_REF0_CHROMA_END)
#define	P_REF1_LUMA_END         (P_REF1_LUMA + LUMA_SIZE)
#define P_REF1_CHROMA           (P_REF1_LUMA_END)
#define	P_REF1_CHROMA_END       (P_REF1_CHROMA + CHROMA_SIZE)
#define P_BIDIR_LUMA            (P_REF1_CHROMA_END)
#define P_BIDIR_LUMA_END        (P_BIDIR_LUMA + P_BIDIR_LUMA_SIZE)
#define P_BIDIR_CHROMA          (P_BIDIR_LUMA_END)
#define P_BIDIR_CHROMA_END      (P_BIDIR_CHROMA + P_BIDIR_CHROMA_SIZE)

//NTSC
#define	N_REF0_LUMA             (END_SEG1)
#define	N_REF0_LUMA_END         (N_REF0_LUMA + N_LUMA_SIZE)
#define	N_REF0_CHROMA           (N_REF0_LUMA_END)
#define	N_REF0_CHROMA_END       (N_REF0_CHROMA + N_CHROMA_SIZE)
#define	N_REF1_LUMA             (N_REF0_CHROMA_END)
#define	N_REF1_LUMA_END         (N_REF1_LUMA + N_LUMA_SIZE)
#define N_REF1_CHROMA           (N_REF1_LUMA_END)
#define	N_REF1_CHROMA_END       (N_REF1_CHROMA + N_CHROMA_SIZE)
#define N_BIDIR_LUMA            (N_REF1_CHROMA_END)
#define N_BIDIR_LUMA_END        (N_BIDIR_LUMA + N_BIDIR_LUMA_SIZE)
#define N_BIDIR_CHROMA          (N_BIDIR_LUMA_END)
#define N_BIDIR_CHROMA_END      (N_BIDIR_CHROMA + N_BIDIR_CHROMA_SIZE)

//VCD,SVCD Preview
#define	M_REF0_LUMA             (END_SEG1)
#define	M_REF0_LUMA_END         (M_REF0_LUMA + M_LUMA_SIZE)
#define	M_REF0_CHROMA           (M_REF0_LUMA_END)
#define	M_REF0_CHROMA_END       (M_REF0_CHROMA + M_CHROMA_SIZE)
#define	M_REF1_LUMA             (M_REF0_CHROMA_END)
#define	M_REF1_LUMA_END         (M_REF1_LUMA + M_LUMA_SIZE)
#define M_REF1_CHROMA           (M_REF1_LUMA_END)
#define	M_REF1_CHROMA_END       (M_REF1_CHROMA + M_CHROMA_SIZE)
#define M_BIDIR_LUMA            (M_REF1_CHROMA_END)
#define M_BIDIR_LUMA_END        (M_BIDIR_LUMA + M_BIDIR_LUMA_SIZE)
#define M_BIDIR_CHROMA          (M_BIDIR_LUMA_END)
#define M_BIDIR_CHROMA_END      (M_BIDIR_CHROMA + M_BIDIR_CHROMA_SIZE)

#define END_VIDEO_FRAMEBUF      (P_BIDIR_CHROMA_END + FS9660_SIZE)

//====================================================================================
// DVD Playback Memory Allocation
//====================================================================================
//Video bitstream buffer, same position for PAL,NTSC DVD and AVI now
//ycwen 2006/2/13 Add 6K for video bitstream, for performance issue.
//                These 6k bytes come from sub picture buffer below.
#ifdef SUPPORT_DVD_FULL_SUBTITLE
    #ifdef COMPRESS_ROM_CODE_040
        #define EVBSZ               (235 - USB_BUFEER_OCCUPIER)
    #else
        #define EVBSZ               (235 - USB_BUFEER_OCCUPIER + 6)
    #endif
#else
    #define EVBSZ                   (235 - USB_BUFEER_OCCUPIER)
#endif

#define P_EVBYA                 (END_VIDEO_FRAMEBUF)
#define P_EVBSZ                 (EVBSZ)

#define N_EVBYA                 (END_VIDEO_FRAMEBUF)
#define N_EVBSZ                 (EVBSZ)

#define M_EVBYA                 (END_VIDEO_FRAMEBUF)
#define M_EVBSZ                 (EVBSZ)

//Sub-picture memory
#ifdef SUPPORT_DVD_FULL_SUBTITLE
    #ifdef COMPRESS_ROM_CODE_040
        #define SUPSIZE                 (52)
    #else
        #define SUPSIZE                 (52)    
    #endif    
#else   
    #define SUPSIZE                 (16)
#endif 

#ifdef COMPRESS_ROM_CODE_040
#define P_SUPYA                 (DRV1_ST + DRV1_CODESIZE)
#define MN_SUPYA                (DRV1_ST + DRV1_CODESIZE)
#else
#define P_SUPYA                 (P_EVBYA + P_EVBSZ + USB_BUFEER_OCCUPIER)
#define MN_SUPYA                (N_EVBYA + N_EVBSZ + USB_BUFEER_OCCUPIER)
#endif

//====================================================================================
// AVI playback memory segment
//====================================================================================
//MP4 video buffer size
#define A_AVIEVBSZ              (235 - USB_BUFEER_OCCUPIER)

//AVI internal sub-picture
#ifdef AVI_INTERNAL_SUP
    #ifdef COMPRESS_ROM_CODE_040    //reserve 16k for internal sup
#define INTERN_SUPYA            (MN_SUPYA)
#define INTERN_SUPSIZE          (16)
    #else   //internal sup can use external subtitile memory
#define INTERN_SUPYA            (A_FILE_BUF_YA)    // 2005/10/03 yltseng
#define INTERN_SUPSIZE          (52)
    #endif  //#ifdef COMPRESS_ROM_CODE_040
#else   //!AVI_INTERNAL_SUP
#define INTERN_SUPYA            (INVALID_POINTER)
#define INTERN_SUPSIZE          (0)
#endif  //#ifdef AVI_INTERNAL_SUP

//AVI buffer for audio,index,ext.subtitile etc.
#ifdef COMPRESS_ROM_CODE_040
   #ifdef AVI_INTERNAL_SUP
       #define A_FILE_BUF_YA           (INTERN_SUPYA + INTERN_SUPSIZE)  //16k is reserved for internal subtitle
   #else
       #define A_FILE_BUF_YA           (MN_SUPYA)  //16k is reserved for internal subtitle
   #endif
   //cut back avi external subtitle for drv1 and internal sub picture
   #define A_FILE_BUF_SIZE         (180 - EXTRA_FS9660BUF - DRV1_CODESIZE - INTERN_SUPSIZE)
#else   //!COMPRESS_ROM_CODE_040
#define A_FILE_BUF_YA           (END_VIDEO_FRAMEBUF + A_AVIEVBSZ + USB_BUFEER_OCCUPIER)
#define A_FILE_BUF_SIZE         (180 - EXTRA_FS9660BUF)
#endif  //#ifdef COMPRESS_ROM_CODE_040

// MVC buffer
#define MVC_BUF_YA              (A_FILE_BUF_YA + A_FILE_BUF_SIZE)
#ifdef SUPPORT_SPECIAL_RATIO_MP4_VIDEO
#define MVC_BUF_SIZE            (33)
#else
#define MVC_BUF_SIZE            (30)
#endif

//====================================================================================
// Others.
//====================================================================================
//File system buffer
// FS buffer size
#ifdef  REDUCE_SUP_SRT_FOR_FS9660
#define EXTRA_FS9660BUF         (25)
#else   //!REDUCE_SUP_SRT_FOR_FS9660
#define EXTRA_FS9660BUF         (0)
#endif  //#ifdef  REDUCE_SUP_SRT_FOR_FS9660

#define FS9660_SIZE             (9 + EXTRA_FS9660BUF)

#define P_FS9660YA              (P_BIDIR_CHROMA_END)
#define N_FS9660YA              (P_BIDIR_CHROMA_END)

//Nav buffer
#if  defined(SUPPORT_DVD_FULL_SUBTITLE) && defined(COMPRESS_ROM_CODE_040)
#define N_NAVYA                 (INVALID_POINTER)
#define S_NAVYA                 (INVALID_POINTER)
#define MAX_BUF_SIZE            (0)
#else   //!defined(SUPPORT_DVD_FULL_SUBTITLE) || !defined(COMPRESS_ROM_CODE_040)
#define N_NAVYA                 (MN_SUPYA + SUPSIZE)
#define S_NAVYA                 (JPEG_YA)
#define MAX_BUF_SIZE            (36)
#endif  //#if  defined(SUPPORT_DVD_FULL_SUBTITLE) && defined(COMPRESS_ROM_CODE_040)

//====================================================================================
// Code Module 
//====================================================================================
//mpeg code
//loaded at (P_EVBYA + P_EVBSZ)
#ifdef COMPRESS_ROM_CODE_040
#define DRV1_CODESIZE           (36)
#define DRV1_ST                 (P_EVBYA + P_EVBSZ)
#else
#define DRV1_ST                 (INVALID_POINTER)
#define DRV1_CODESIZE           (0)
#endif

//JPEG code
//loaded at A_DSP24YA
#define DRV2_ST                 (A_DSP24YA)
#define DRV2_CODESIZE           (36)
#define JPEG_CODE_YA            (A_DSP24YA + DRV2_CODESIZE)
#define JPEG_CODE_SIZE          (8)

//AP1 code
//loaded at (MN_OSDYA - AP_CODESIZE)
#ifdef SUPPORT_MP4_SUBTITLE      
#define AP_CODESIZE             (16)
#define AP1_ST                  (MN_OSDYA - AP_CODESIZE)
#else   //use extra osd buffer prepared for MP4 ext. subtitle to load AP1 code
    #ifdef DVDRELEASE
#define AP_CODESIZE             (20 + DBG_STACK_SIZE - EXTRA_OSDSIZE)
    #else   //!DVDRELEASE
#define AP_CODESIZE             (20 - EXTRA_OSDSIZE)
    #endif  //#ifdef DVDRELEASE
#define AP1_ST                  (MN_OSDYA - AP_CODESIZE)
#endif

//AP2N3 not loaded
#define AP2N3_ST                      (0)
#define AP3_CODESIZE            (0)
#define AP2_CODESIZE            (0)

//CDROM code
//terry,2005/6/23 02:20¤U¤È
#if defined(COMPRESS_ROM_CODE_040) && defined(SUPPORT_DVD_FULL_SUBTITLE)
    #ifdef SUPPORT_MP4
#define CDROM_CODE_SIZE         (A_JPEG_SERVO_YA - CDROM_CODE_YA)
        #ifdef SHARE_CDROM_CODE_WITH_SUP
#define CDROM_CODE_YA           (MN_SUPYA)
        #else
#define CDROM_CODE_YA           (MN_SUPYA + SUPSIZE)
        #endif
    #else
#define CDROM_CODE_SIZE         (A_WMA_CODE_YA-CDROM_CODE_YA)
#define CDROM_CODE_YA           (GP_REF1_CHROMA+GP_CHROMA_SIZE)
    #endif
#else   //!defined(COMPRESS_ROM_CODE_040) || !defined(SUPPORT_DVD_FULL_SUBTITLE)
#define CDROM_CODE_SIZE         (A_JPEG_SERVO_YA - CDROM_CODE_YA)
#define CDROM_CODE_YA           (N_NAVYA + MAX_BUF_SIZE)
#endif  //#if defined(COMPRESS_ROM_CODE_040) && defined(SUPPORT_DVD_FULL_SUBTITLE)

//DVD code
#if defined(COMPRESS_ROM_CODE_040) &&!defined(SUPPORT_MP4)
#define DVD_NAV_CODE           (P_SUPYA+SUPSIZE)
#define DVD_CODE_SIZE           (A_DVD_SERVO_YA-DVD_NAV_CODE)
#else
#define DVD_NAV_CODE           (INVALID_POINTER)
#define DVD_CODE_SIZE           (0)
#endif

#define A_SERVO_YA              (A_JPEG_SERVO_YA)
#define SERVO_SIZE              (20)

#define WMA_CODE_SIZE           (10+10) //terry,2005/5/20 02:23¤U¤È, 10->20
#define A_WMA_CODE_YA           (GP_END-WMA_CODE_SIZE)

//MP4 code
#define A_MP4_CODE_YA           (INVALID_POINTER)
#define MP4_CODE_SIZE           (0)

//Free code
#define FREE_CODE_YA            (INVALID_POINTER)
#define FREE_CODESIZE           (0)

//Second sub-picture
#define SUPSIZE2                (0)
#define A_SUPYA2                (INVALID_POINTER)

//Interlace buffer
#define A_DEINTLACE_YA          (INVALID_POINTER)
#define DEINTLACE_BUF_SIZE      (627)

#define OSD_BASE_USE_ADDR       (JPEG_YA + MAX_BUF_SIZE) //kevinmonkey 050318 changed from P_BIDIR_LUMA, 
                                          //to avoid setup menu osd pollute wma code when field decoding is enabled

//====================================================================================
// JPEG memory segment
//====================================================================================
//second segment (JPEG)
//using pal: 736x576 ,block mode
#define GP_LUMA_SIZE            (414)
#define GP_CHROMA_SIZE          (207)
#define GP_REF0_LUMA            (VFBMA + 0)
#define GP_REF0_CHROMA	        (GP_REF0_LUMA + GP_LUMA_SIZE) 
#define GP_REF1_LUMA	        (GP_REF0_CHROMA + GP_CHROMA_SIZE)   
#define GP_REF1_CHROMA          (GP_REF1_LUMA + GP_LUMA_SIZE) 
#define GP_END                  (N_FS9660YA)//kevinmonkey 050414 can't interfere with FS buffer

#define GN_REF0_LUMA            (GP_REF0_LUMA)
#define GN_REF1_LUMA            (GP_REF1_LUMA)
#define GN_REF0_CHROMA          (GP_REF0_CHROMA)
#define GN_REF1_CHROMA          (GP_REF1_CHROMA)
#define GN_END                  (GP_END)

#define P_JPEG_PS               (GP_REF1_LUMA)
#if defined(COMPRESS_ROM_CODE_040) &&!defined(SUPPORT_MP4)
#define JPEG_PS_SIZE            (GP_LUMA_SIZE+GP_CHROMA_SIZE)
#else
#define JPEG_PS_SIZE            (GP_END - GP_REF1_LUMA)
#endif


#define JPEG_FULLSCREEN_WORKING_BUF_SIZE    (100)   //20060627, joshua, added for ps-jpeg decoding buffer
#define JPEG_PREVIEW_WORKING_BUF_SIZE       (100)

//kevinmonkey 051207 reduce FS_OVERLOAD_FILE_MEMORY_SIZE for overload file to support more music/jpeg file under 16m
#ifdef FS_OVERLOAD_FILE
#define JPEG_YA                 (N_FS9660YA + FS9660_SIZE + FS_OVERLOAD_FILE_MEMORY_SIZE)
#define JPEG_CDBUF_SIZE         (220 - FS_OVERLOAD_FILE_MEMORY_SIZE - JPEG_FULLSCREEN_WORKING_BUF_SIZE)
#else  //!FS_OVERLOAD_FILE
#define JPEG_YA                 (N_FS9660YA + FS9660_SIZE)
#define JPEG_CDBUF_SIZE         (220 - JPEG_FULLSCREEN_WORKING_BUF_SIZE)
#endif  //#ifdef FS_OVERLOAD_FILE

#define JPEG_FULLSCREEN_WORKING_BUF_YA      (JPEG_YA+JPEG_CDBUF_SIZE)
#define JPEG_PREVIEW_WORKING_BUF_YA         (GP_REF0_LUMA + 844)


#define SSAVER_YA               (JPEG_YA + JPEG_CDBUF_SIZE+JPEG_FULLSCREEN_WORKING_BUF_SIZE)
#define SSAVER_PIC_SIZE         (16)
#define TEMPYA                  (SSAVER_YA)

//====================================================================================
// File List GUI memory segment
//====================================================================================
#define GS_LUMA_SIZE            (99)
#define GS_CHROMA_SIZE          (50)
#define	GS_REF0_LUMA            (VFBMA + 0)
#define	GS_REF1_LUMA            (GS_REF0_LUMA)
#define	GS_REF0_CHROMA          (GS_REF0_LUMA + GS_LUMA_SIZE)
#define	GS_REF1_CHROMA          (GS_REF1_LUMA + GS_LUMA_SIZE)
#define	GS_END                  (GS_REF1_CHROMA + GS_CHROMA_SIZE)
#define A_UDF_WORK_BUF          (GS_END)
#define UDF_WORK_BUF_SIZE       (80)

#define MOVE_WMA_DSP_CODEC_ADDR // 2004/11/18 yltseng
#define DSP_WMA_SIZE            130
//wma decoder address
#define A_DSP24_WMA_YA          (A_UDF_WORK_BUF+UDF_WORK_BUF_SIZE)

#if defined(COMPRESS_ROM_CODE_040)&&defined(TURBO_DECODE)		//linrc add because memory overlay 2005-10-21 10:16
#define A_CDG_DATA_YA      		(A_DSP24_WMA_YA+DSP_WMA_SIZE)
#endif
//====================================================================================
// GAME Memory Allocation
//====================================================================================
//third segment (Game , RGB color index)
//small: 256*240 ,linear mode
#define VFBMA                   (END_SEG1) //(167)//(END_SEG1)    for NES engine, NES engine fixed its address at 307k
#define GG_REF0_FRAME           (167 + 0)
#define GG_REF1_FRAME           (167 + 70)
#define GG_REF1_FRAME_END       (GG_REF1_FRAME + 70)
#define GAME_OSD_FRAME_START    (GG_REF0_FRAME)
#define GAME_PARAMETER_START    (GG_REF1_FRAME_END)
#define GAME_PARAMETER_SIZE     (1)
#define MAX_GAME_BUF            (100)         //driver size
#define GAMEYA                  (GAME_PARAMETER_START + GAME_PARAMETER_SIZE + 100)	//100K for work space
#define GAME_STACK 	            (GAME_PARAMETER_START + GAME_PARAMETER_SIZE + 200)	//100K for driver
#define GAME_STACK_SIZE         (9)
#define GAME_FILE_START         (GAME_STACK + GAME_STACK_SIZE)     //NES game file buffer
#define MAX_GAME_FILE_SIZE      (1024)  //max NES game file content size(1M Bytes)
#define GAME_CALL_ENTRY         (SDRAM_BASE + GAMEYA * 1024)

//====================================================================================
// Other featuers
//====================================================================================
//CD TEXT
#ifdef SUPPORT_CD_TEXT
    #define CD_TEXT_YA          N_BIDIR_CHROMA
    #define CD_TEXT_SIZE        N_BIDIR_CHROMA_SIZE
#endif

//USB
#if defined(SUPPORT_USB)
    #ifdef HOST_UHCI
#define USB_BUFEER_OCCUPIER     (15)
#define USB_BUFFER_SIZE         (7)
#define CARD_BUFFER_SIZE        (3)
#define USB_YA_ALIGNTO4K        (((N_EVBYA + N_EVBSZ+3))>>2<<2)
#define USB_YA                  (USB_YA_ALIGNTO4K)
#define CARD_YA                 (USB_YA + USB_BUFFER_SIZE)
#define A_SUPYA                 (N_NAVYA)
    #elif defined(USB_HOST_DRV)
#define USB_BUFEER_OCCUPIER     (0)
#define USB_BUFFER_SIZE         (1)
#define CARD_BUFFER_SIZE        (3)
#define USB_YA_ALIGNTO4K        (INVALID_POINTER)
        #ifdef IDE_CF_SW
            #if (HD_FAT_TABLE_SIZE > CF_FAT_TABLE_SIZE)
#define USB_YA                  (NORMAL_FAT_CACHE_ADDR + HD_FAT_TABLE_SIZE)
            #else //(HD_FAT_TABLE_SIZE < CF_FAT_TABLE_SIZE)
#define USB_YA                  (NORMAL_FAT_CACHE_ADDR + CF_FAT_TABLE_SIZE)
            #endif  //#if (HD_FAT_TABLE_SIZE > CF_FAT_TABLE_SIZE)
        #else   //!IDE_CF_SW
//Normal USB, card support use this!!
#define USB_YA                  (NORMAL_FAT_CACHE_YA + MAX_BUF_SIZE)
        #endif  //#ifdef IDE_CF_SW
#define CARD_YA                 (USB_YA + USB_BUFFER_SIZE)
//FAT cache address (NORMAL_FAT_CACHE_ADDR) no longer at A_SUPYA
#define A_SUPYA                 (INVALID_POINTER)
    #else   //!HOST_UHCI and !USB_HOST_DRV
        #error "please define your USB controller interface!"
    #endif  //host controller
#else   //!SUPPORT_USB
#define USB_BUFEER_OCCUPIER      0
#define USB_BUFFER_SIZE          0
#define CARD_BUFFER_SIZE         0
#define USB_YA_ALIGNTO4K        (INVALID_POINTER)
#define USB_YA                  (INVALID_POINTER)
#define CARD_YA                 (INVALID_POINTER)
#define A_SUPYA                 (INVALID_POINTER)
#endif  //#if defined(SUPPORT_USB)

//--------------------------------------
// for mp3 encoder write FAT devices
//--------------------------------------
#ifdef INCLUDE_MP3_ENCODER
#define MP3ENC_PCM_BUF_YA       (REF1_LUMA)   
#define MP3ENC_PCM_BUF_SIZE     (96) 
#define MP3ENC_FAT_BUF_YA       (MP3ENC_PCM_BUF_YA + MP3ENC_PCM_BUF_SIZE)
#define MP3ENC_FAT_BUF_SIZE     (1024)
#define MP3ENC_UPDATE_REC_YA    (MP3ENC_FAT_BUF_YA + MP3ENC_FAT_BUF_SIZE)
#define MP3ENC_UPDATE_REC_SIZE  (4)         //kevinmonkey not sure how large it is.

#define	DATA_BUF_ADDR		    (SDRAM_BASE + ((MP3ENC_PCM_BUF_YA) * 1024))
#define	DATA_BUF_LEN		    (MP3ENC_PCM_BUF_SIZE)	// 32 * 3KB		//buffer for mp3 data produced by DSP
#endif  //#ifdef INCLUDE_MP3_ENCODER

#ifdef USE_48M_BUF_IN_64M_SDRAM_AS_ESP_BUF	//we use the 64M sdram's end of 32M memory as ESP USE...
#define A_DVD_SERVO_YA_4096		2048		//define it must use 64M sdram...linrc 2005-11-18 17:10
#define DVDV_SERVO_SIZE_4096   	6144
#endif
//====================================================================================
// Checking Section
//====================================================================================
//left to be done

#ifndef TURBO_DECODE
#error  "This memory map is for systems supporting TURBO_DECODE!"
#endif

#ifndef SUPPORT_FILE_SYSTEM_MODE
#error  "Situation not supporting SUPPORT_FILE_SYSTEM_MODE is not yet considerred."
#endif

#if (JPEG_SERVO_SIZE > DVDV_SERVO_SIZE)
#error  "(JPEG_SERVO_SIZE > DVDV_SERVO_SIZE), may bring about memory overlapping."
#endif

#if ((MVC_BUF_YA + MVC_BUF_SIZE) > (A_JPEG_SERVO_YA))
#error  "mvc buffer overlaps servo buffer, grow from top and grow from bottom conflicts each other."
#endif

#ifdef MEMCFG_PAL_LMEM
#error  "Why you want Lmem even when you have turbo-decode?"
//probably error:
//MOVE_SUP() in config_memory_size();
#endif
//support mp3 encoder
//--------------------------------------
// for fat file system write 
//--------------------------------------
#ifndef PMP_DVD//liweihua add 2004-12-10 
#define FAT_WRITE_TEMP_YA	    (P_BIDIR_LUMA)
#define FAT_WRITE_TEMP_SIZE     (1)
#define FAT_COPY_YA             (FAT_WRITE_TEMP_YA+FAT_WRITE_TEMP_SIZE) 
#define FAT_COPY_SIZE           (384)
#endif

//====================================================================================
// Some Development Notes
//====================================================================================
// (Common for all configuration)
#if 0
//about CDROM code, fsCDDA
left to be composed

//======================================================================================
//  something about SERVOBUF_ALIGNED_TO_BOTTOM definition
//======================================================================================
kevinmonkey 050318, move osd buffer to bottom since it is a all-time needed function   
servo buffer at bottom as well, since its sizes changes between DVD/AVI playback
kevinmonkey 050309 move servo to bottom: merit->for variable servo size in 16Mb,
demerit: memory overlap problem results in wrong bitstream 
  |                        |     |                        |
  |________________________|     |________________________|
  _________________________      _________________________
  |usable space, combine   |     |                        |
  |with the space above    |     |                        |
  |makes a continous space |     |  bigger servo buffer   |
  |________________________|     |  size when playing     |
  _________________________      |  DVD, and bottom       |
  |small servo buffer when |     |  position not changed  |
  |playing JPEG, AVI, MP3  |     |                        |
  |________________________|     |________________________|  <- aligned at both situation
  
#endif  //0, end of documentation
