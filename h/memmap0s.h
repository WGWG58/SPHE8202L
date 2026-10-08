//====================================================================================
// memmap0s.h
// 8200 16Mb memory mapping
// Creator  : Potatooo
// Maintain : Jeff (720) / Terry (8200)
// -----------------------------------------------------------------------------------
// Revision History   
//          2003.02.12   re-order all memory addr. for 
//                       a.easy to chk in stack overflow
//                       b.let a little difference between 16MBits and 32MBits 
//          2003.02.17   correct nes game/cd+g/servo buffer
//          2003.03.05   a.add de-interlace and slow backward
//                       b.move memory map to memmap0b.txt
//====================================================================================
#include "set.h"


#if defined(SPHE1000)&&defined(SINGLE_CPU)
#include "memmap_nonos_s.h"
#else
//====================================================================================
// Decode mode memory config
//====================================================================================
#define P_VIDEO_COMPRESS        (RF_COMPRESS_888 \
                                |RF_COMPRESS_DITHER_OFF \
                                |RF_COMPRESS_CHROMA_FULL)
#define	GN_VIDEO_COMPRESS       (P_VIDEO_COMPRESS)
#define	GP_VIDEO_COMPRESS       (P_VIDEO_COMPRESS)
#define	GS_VIDEO_COMPRESS       (P_VIDEO_COMPRESS)

//====================================================================================
// task stack Allocation 
//====================================================================================
#define A_MAIN_TASK_TOP         (1)  // 1.3
#define MAIN_TASK_SIZE          (1)  // 1.7 , terry,2004/7/26 02:52PM
#define A_MAIN_TASK_BOM         3
#define DBG_STACK_SIZE          2
#define A_DBG_TASK_BOM          2048            // put it at 2046~2047k range
#define A_DBG_TASK_TOP          (A_DBG_TASK_BOM-DBG_STACK_SIZE)

//====================================================================================
// Memory Allocation Start
//====================================================================================
#define MEM_START		0
#define SDRAM_CS_ST		7	// (A_CDYA + CDSIZE)


//----------------------
//first segment
//----------------------
#define A_IOPYA                 (MEM_START + 0)                         // 0
#define IOP_SIZE                2
#define A_CDYA                  (A_IOPYA + IOP_SIZE + MAIN_TASK_SIZE)   // 3
#define CDSIZE                  4
#ifdef SUPPORT_DVD_NATIVE_GAME		//linrc for NATIVE GAME 2005-10-19 17:12
#define SDRAM_CS_SZ             25+1+5
#else
#define SDRAM_CS_SZ             25+1  //kevinmonkey 050302 temporary add 1 cause SDRAM_CS_SZ is now full
#endif

/* sizes */
#ifdef SUPPORT_OSDSRT
    #ifdef NEW_DISPLAY_GOTO_OSD
#define OSDSIZE                 (3+20)
    #else   //SUPPORT_OSDSRT && !NEW_DISPLAY_GOTO_OSD
#define OSDSIZE                 (6+20)
    #endif
#else   //!SUPPORT_OSDSRT
    #ifdef NEW_DISPLAY_GOTO_OSD
#define OSDSIZE                 3
    #else   //!SUPPORT_OSDSRT && !NEW_DISPLAY_GOTO_OSD
#define OSDSIZE                 6
    #endif
#endif  //SUPPORT_OSDSRT

// 2004/07/16 yltseng
#ifdef TURBO_DECODE
#define SUPSIZE	                22
#else
    #ifdef USE_NAV_BUF_16M_DECREASE_SUBPICTURE
#define SUPSIZE	                30
    #else   //!USE_NAV_BUF_16M_DECREASE_SUBPICTURE
#define SUPSIZE	                52
    #endif  //#ifdef USE_NAV_BUF_16M_DECREASE_SUBPICTURE
#endif  //#ifdef TURBO_DECODE

#define SERVO_7ECC_SIZE         297
#define SERVO_5ECC_SIZE         211
#define SERVO_3ECC_SIZE         127
#define SERVO_4ECC_SIZE         (SERVO_7ECC_SIZE-SERVO_3ECC_SIZE)

#define SERVO_SIZE              20
#ifdef  TURBO_DECODE
   #define JPEG_SERVO_SIZE      SERVO_3ECC_SIZE
   #ifdef DVD_SRV_BUF_SMALL
      #define DVDV_SERVO_SIZE   SERVO_3ECC_SIZE
   #else//!DVD_SRV_BUF_SMALL
      #define DVDV_SERVO_SIZE   SERVO_7ECC_SIZE     
   #endif//DVD_SRV_BUF_SMALL

#else   //!TURBO_DECODE
#define JPEG_SERVO_SIZE         127
#define DVDV_SERVO_SIZE         127
#endif  //TURBO_DECODE
#define DSP_SIZE                65      // 2004/11/18 yltseng


#ifdef TURBO_DECODE
//kevinmonkey 050318, move osd buffer to bottom since it's a all-time needed function   
//servo buffer at bottom as well, since its sizes changes between DVD/AVI playback
#define MN_OSDYA                (A_DBG_TASK_TOP - OSDSIZE)
#define P_OSDYA                 (MN_OSDYA)
#define A_SERVO_YA              (MN_OSDYA - JPEG_SERVO_SIZE)
#define A_DVD_SERVO_YA          (MN_OSDYA - DVDV_SERVO_SIZE)
#define A_JPEG_SERVO_YA         (MN_OSDYA - JPEG_SERVO_SIZE)
#endif

//remark kevinmonkey:   
// TURBO_DECODE && MEMCFG_MOVE_OSDSUP && !MOVE_PAL_AUDYA && !22MB
#ifndef MEMCFG_MOVE_OSDSUP

/* TYPE0: OSD/SUP at top */
#define A_OSDYA                 (SDRAM_CS_ST + SDRAM_CS_SZ)
#define A_DSP24YA               (A_OSDYA+OSDSIZE)
#define A_SUPYA	                (A_DSP24YA+DSP_SIZE)
    #ifdef TURBO_DECODE//!TURBO_DECODE && !MEMCFG_MOVE_OSDSUP 
#define END_SEG1                (A_SUPYA+SUPSIZE)   //kevinmonkey 050309 servo buffer moved to the bottom
    #else   //!MEMCFG_MOVE_OSDSUP && TURBO_DECODE
#define A_SERVO_YA              (A_SUPYA+SUPSIZE)                      
#define A_DVD_SERVO_YA          (A_SERVO_YA)                             
#define A_JPEG_SERVO_YA         (A_DVD_SERVO_YA)
#define END_SEG1                (A_DVD_SERVO_YA+DVDV_SERVO_SIZE)
    #endif  //TURBO_DECODE

#else   //MEMCFG_MOVE_OSDSUP

/* TYPE1: OSD/SUP dynamically */
    #ifdef MOVE_PAL_AUDYA   //MEMCFG_MOVE_OSDSUP && MOVE_PAL_AUDYA
#define A_SERVO_YA              (SDRAM_CS_ST + SDRAM_CS_SZ)
#define A_DSP24YA               (A_SERVO_YA + DVDV_SERVO_SIZE)             // 32
#define A_DVD_SERVO_YA          (A_SERVO_YA)
#define A_JPEG_SERVO_YA         (A_DVD_SERVO_YA)
#define END_SEG1                (A_DSP24YA+DSP_SIZE)
    #else   //MEMCFG_MOVE_OSDSUP && !MOVE_PAL_AUDYA
        #ifdef TURBO_DECODE  //TURBO_DECODE and MOVE_PAL_AUDYA shouldn't be defined at the same time(no L-men)
#define A_DSP24YA               (SDRAM_CS_ST + SDRAM_CS_SZ)
//kevinmonkey 050309 move servo to bottom: merit->for variable servo size in 16Mb,demerit: memory overlap problem results in wrong bitstream 
#define END_SEG1                (A_DSP24YA+DSP_SIZE)
        #else   //MEMCFG_MOVE_OSDSUP && !MOVE_PAL_AUDYA && !TURBO_DECODE
#define A_DSP24YA               (SDRAM_CS_ST + SDRAM_CS_SZ)             // 32
#define A_SERVO_YA              (A_DSP24YA+DSP_SIZE)                    // 105
#define A_DVD_SERVO_YA          (A_SERVO_YA)
#define A_JPEG_SERVO_YA         (A_DVD_SERVO_YA)        
#define END_SEG1                (A_DVD_SERVO_YA+DVDV_SERVO_SIZE)     
        #endif  //TURBO_DECODE
    #endif  //MOVE_PAL_AUDYA

#endif  //MEMCFG_MOVE_OSDSUP


#define VFBMA                   END_SEG1                                // 232 or 281

//--------------------------
// second segment (DVD/VCD/CD)
//--------------------------

//PAL D1 (576-line)
#define LUMA_SIZE               405             // PAL D1 luma size 
#define CHROMA_SIZE             203             // PAL D1 chroma size 
#define EVBSZ                   235

#define P_LUMA_SIZE             LUMA_SIZE       // PAL D1 luma size 
#define P_CHROMA_SIZE           CHROMA_SIZE     // PAL D1 chroma size 
#define N_LUMA_SIZE             338             // NTSC D1 luma size 
#define N_CHROMA_SIZE           169             // NTSC D1 chroma size 
#define B_LUMA_SIZE             248             // PAL D1 B666 luma size 22MB 
#define B_CHROMA_SIZE           203             // PAL D1 B666 chroma size full-map 
#define M_LUMA_SIZE             270             // PAL 2/3D1 luma size 
#define M_CHROMA_SIZE           135             // PAL 2/3D1 chroma size 

#ifdef  TURBO_DECODE   //kevinmonkey 050225 field decoding
#define P_BIDIR_LUMA_SIZE        80             // PAL D1 luma size 
#define P_BIDIR_CHROMA_SIZE      40             // PAL D1 chroma size 
#define N_BIDIR_LUMA_SIZE       214             // NTSC D1 luma size 
#define N_BIDIR_CHROMA_SIZE     107             // NTSC D1 chroma size 
#else   //!TURBO_DECODE
#define P_BIDIR_LUMA_SIZE       405             // PAL D1 luma size 
#define P_BIDIR_CHROMA_SIZE     203             // PAL D1 chroma size 
#define N_BIDIR_LUMA_SIZE       338             // NTSC D1 luma size 
#define N_BIDIR_CHROMA_SIZE     169             // NTSC D1 chroma size 
#endif  //TURBO_DECODE
#define M_BIDIR_LUMA_SIZE       338             // NTSC D1 luma size 
#define M_BIDIR_CHROMA_SIZE     169             // NTSC D1 chroma size 
#define B_BIDIR_LUMA_SIZE       248             // PAL D1 B666 luma size 22MB 
#define B_BIDIR_CHROMA_SIZE     203             // PAL D1 B666 chroma size full-map 

#ifdef  TURBO_DECODE   //kevinmonkey 050225 PS2.5 AVI B frame field decoding
#define	P_REF0_LUMA             END_SEG1
#else   //!TURBO_DECODE
#define	P_REF0_LUMA             (A_DVD_SERVO_YA+DVDV_SERVO_SIZE) // 281      232  
#endif  //TURBO_DECODE

#define	P_REF0_LUMA_END         (P_REF0_LUMA + LUMA_SIZE - 1)
#define	P_REF0_CHROMA           (P_REF0_LUMA_END + 1)
#define	P_REF0_CHROMA_END       (P_REF0_CHROMA + CHROMA_SIZE - 1)
#define	P_REF1_LUMA             (P_REF0_CHROMA_END + 1)
#define	P_REF1_LUMA_END         (P_REF1_LUMA + LUMA_SIZE - 1)
#define P_REF1_CHROMA           (P_REF1_LUMA_END + 1)
#define	P_REF1_CHROMA_END       (P_REF1_CHROMA + CHROMA_SIZE - 1)
#define P_BIDIR_LUMA            (P_REF1_CHROMA_END + 1)

#ifdef  MB22
#define P_BIDIR_LUMA_END        (P_BIDIR_LUMA + B_LUMA_SIZE - 1)        // MB22 
#else   //!MB22
#define P_BIDIR_LUMA_END        (P_BIDIR_LUMA + P_BIDIR_LUMA_SIZE - 1)          // full-map
#endif  //MB22

#define P_BIDIR_CHROMA          (P_BIDIR_LUMA_END + 1)
#define P_BIDIR_CHROMA_END      (P_BIDIR_CHROMA + P_BIDIR_CHROMA_SIZE - 1)

#ifdef TURBO_DECODE
//kevinmonkey 050309 align PAL and NTSC memory layout. NTSC has some(153k) blank space before END_DVD_FRAMEBUF 
#define END_DVD_FRAMEBUF        (P_BIDIR_CHROMA_END + 1) 
#endif  //TURBO_DECODE

#ifdef MOVE_PAL_AUDYA   
#define P_EVBYA                 (A_DBG_TASK_BOM)    //L-memory
#else   // !MOVE_PAL_AUDYA
    #ifdef TURBO_DECODE //TURBO_DECODE && !MOVE_PAL_AUDYA
#define P_EVBYA                 END_DVD_FRAMEBUF
    #else   //!TURBO_DECODE && !MOVE_PAL_AUDYA
#define P_EVBYA                 (P_BIDIR_CHROMA + CHROMA_SIZE + 1)      // 2057 (+1 for debug task )  
    #endif
#endif  //MOVE_PAL_AUDYA
    
//#endif
#define P_EVBSZ                 EVBSZ
#define P_SUPYA                 (P_EVBYA+P_EVBSZ)
#ifndef TURBO_DECODE
#define P_OSDYA                 (P_SUPYA+SUPSIZE)
#endif

#ifdef MOVE_PAL_AUDYA           // 2004/11/18 yltseng
#define P_DSP24YA               (P_OSDYA+OSDSIZE)
#endif

// N: NTSC D1 (no preview mode)
#define	N_REF0_LUMA             VFBMA					// 281      232
#define	N_REF0_LUMA_END         (N_REF0_LUMA + N_LUMA_SIZE - 1)
#define	N_REF0_CHROMA           (N_REF0_LUMA_END + 1)
#define	N_REF0_CHROMA_END       (N_REF0_CHROMA + N_CHROMA_SIZE - 1)
#define	N_REF1_LUMA             (N_REF0_CHROMA_END + 1)
#define	N_REF1_LUMA_END         (N_REF1_LUMA + N_LUMA_SIZE - 1)
#define N_REF1_CHROMA           (N_REF1_LUMA_END + 1)
#define	N_REF1_CHROMA_END       (N_REF1_CHROMA + N_CHROMA_SIZE - 1)
#define N_BIDIR_LUMA            (N_REF1_CHROMA_END + 1)
#define N_BIDIR_LUMA_END        (N_BIDIR_LUMA + N_BIDIR_LUMA_SIZE - 1)
#define N_BIDIR_CHROMA          (N_BIDIR_LUMA_END + 1)
#define N_BIDIR_CHROMA_END      (N_BIDIR_CHROMA + N_BIDIR_CHROMA_SIZE - 1)

#ifdef TURBO_DECODE
#define N_EVBYA                 END_DVD_FRAMEBUF
#else   //!TURBO_DECODE
#define N_EVBYA                 (N_BIDIR_CHROMA_END + 1)
#endif

#define N_EVBSZ                 EVBSZ
#define N_END_SEG2              (N_EVBYA + N_EVBSZ)                     // 1802     1753

//kevinmonkey not taken care of for TURBO_DECODE
// M: PAL 2/3 D1 (with preview mode)
#define	M_REF0_LUMA             (VFBMA + 0)				// 281      232	
#define	M_REF0_LUMA_END         (M_REF0_LUMA + M_LUMA_SIZE - 1)
#define	M_REF0_CHROMA           (M_REF0_LUMA_END + 1)
#define	M_REF0_CHROMA_END       (M_REF0_CHROMA + M_CHROMA_SIZE - 1)
#define	M_REF1_LUMA             (M_REF0_CHROMA_END + 1)
#define	M_REF1_LUMA_END         (M_REF1_LUMA + M_LUMA_SIZE - 1)
#define M_REF1_CHROMA           (M_REF1_LUMA_END + 1)
#define	M_REF1_CHROMA_END       (M_REF1_CHROMA + M_CHROMA_SIZE - 1)
#define M_BIDIR_LUMA            (M_REF1_CHROMA_END + 1)
#define M_BIDIR_LUMA_END        (M_BIDIR_LUMA + M_BIDIR_LUMA_SIZE - 1)
#define M_BIDIR_CHROMA          (M_BIDIR_LUMA_END + 1)
#define M_BIDIR_CHROMA_END      (M_BIDIR_CHROMA + M_BIDIR_CHROMA_SIZE - 1)

#ifdef TURBO_DECODE
#define M_EVBYA                 END_DVD_FRAMEBUF
#else
#define M_EVBYA                 (M_BIDIR_CHROMA_END + 1)
#endif
#define M_EVBSZ                 EVBSZ
#define M_END_SEG2              (M_EVBYA + M_EVBSZ)

#define MN_SUPYA                (N_EVBYA+EVBSZ)

#if defined(TURBO_DECODE) && defined(SUPPORT_PREVIEW_9FRAMES)
#define M_SUPYA                 (M_EVBYA + M_EVBSZ)
#endif

//second segment (JPEG)
//using pal: 720x576 ,block mode
#define GP_LUMA_SIZE            414
#define GP_CHROMA_SIZE          207
#define	GP_REF0_LUMA            (VFBMA + 0)
#define	GP_REF0_CHROMA	        (GP_REF0_LUMA + GP_LUMA_SIZE) 
#define	GP_REF1_LUMA	        (GP_REF0_CHROMA + GP_CHROMA_SIZE)   
#define	GP_REF1_CHROMA          (GP_REF1_LUMA + GP_LUMA_SIZE) 
#define	GP_END                  (GP_REF1_CHROMA + GP_CHROMA_SIZE + 80) //add 80k from JPEG_CDBUF_SIZE for supporting progressive jpeg

#define	GN_REF0_LUMA            (GP_REF0_LUMA)
#define	GN_REF1_LUMA            (GP_REF1_LUMA)
#define	GN_REF0_CHROMA          (GP_REF0_CHROMA)
#define	GN_REF1_CHROMA          (GP_REF1_CHROMA)
#define	GN_END                  (GP_END)

//#define P_JPEG_PS             (GP_END)
//#define JPEG_PS_SIZE          (814+200+42)
#define P_JPEG_PS               (GP_REF1_LUMA)
#define JPEG_PS_SIZE            (700)//(A_AUDYA + AUDSIZE - GP_REF1_LUMA) //(414+207+814+200+42)

//third segment (MP3 GUI)
//small: 352x288,block mode
#define GS_LUMA_SIZE            99
#define GS_CHROMA_SIZE          50
#define	GS_REF0_LUMA            (VFBMA + 0)
#define	GS_REF1_LUMA	        (GS_REF0_LUMA)
#define	GS_REF0_CHROMA	        (GS_REF0_LUMA + GS_LUMA_SIZE)
#define	GS_REF1_CHROMA          (GS_REF1_LUMA + GS_LUMA_SIZE)
#define	GS_END		        (GS_REF1_CHROMA + GS_CHROMA_SIZE)
#define A_UDF_WORK_BUF          (GS_END)
#define UDF_WORK_BUF_SIZE       (80)

#define MOVE_WMA_DSP_CODEC_ADDR // 2004/11/18 yltseng
//wma decoder,address
#define DSP_WMA_SIZE            130
#define A_DSP24_WMA_YA          (A_UDF_WORK_BUF+UDF_WORK_BUF_SIZE)      

#ifdef MEMCFG_MOVE_OSDSUP
#define A_MP3ID3YA              (A_DSP24_WMA_YA+DSP_WMA_SIZE)
#endif
//-------------------------------------
//4th segment
//-------------------------------------
#define DRV1N2_ST               (A_DSP24YA)//(A_PCMYA)  // 2004/11/18 yltseng
#define DRV1_2_CODESIZE         (36)

//  2005/04/07 kevinmonkey allow to separate drv1 and drv2
#define DRV1_ST                 (DRV1N2_ST)
#define DRV2_ST                 (DRV1N2_ST)
#define DRV1_CODESIZE           (DRV1_2_CODESIZE)
#define DRV2_CODESIZE           (DRV1_2_CODESIZE)

#define AP2N3_ST                (0)             //NONO 2004-4-10 23:22
#define AP3_CODESIZE            (0)
#define AP2_CODESIZE            (0)

#define AP1_ST                  (0)                 //2598//NONO 2004-4-10 23:22
#define AP_CODESIZE             (0)

#define DVD_NAV_CODE            (2048)
#define DVD_CODE_SIZE           (0)

#define JPEG_CODE_SIZE          (8)

#ifndef MEMCFG_MOVE_OSDSUP                              // 2004/11/18 yltseng
    #define JPEG_CODE_YA        (A_SUPYA)
#else
    #define JPEG_CODE_YA        (DRV1N2_ST+DRV1_2_CODESIZE)
#endif

//-------------------------------------
//5th segment for De-Interlace buffer
//-------------------------------------
// MP4 video buffer size
#ifdef TURBO_DECODE
#define A_AVIEVBSZ              (235)
#else
    #ifdef SUPPORT_MP4_SUBTITLE
#define A_AVIEVBSZ              (140)    
    #else   //!TURBO_DECODE && SUPPORT_MP4_SUBTITLE
#define A_AVIEVBSZ              (200)    
    #endif  //!TURBO_DECODE && !SUPPORT_MP4_SUBTITLE
#endif //TURBO_DECODE

// MP4 code
#ifdef TURBO_DECODE
#define A_MP4_CODE_YA           (END_DVD_FRAMEBUF+A_AVIEVBSZ)   //kevinmonkey 050309
#else
#define A_MP4_CODE_YA           (N_EVBYA+A_AVIEVBSZ)
#endif
#define MP4_CODE_SIZE           (0)



// MVC buffer
#define MVC_BUF_YA              (A_MP4_CODE_YA+MP4_CODE_SIZE)
#define MVC_BUF_SIZE            (30)

#ifdef REDUCE_SUP_SRT_FOR_FS9660
#define EXTRA_FS9660BUF         (25)
#else
#define EXTRA_FS9660BUF         (0)
#endif

#define A_FILE_BUF_YA           (MVC_BUF_YA+MVC_BUF_SIZE)
#ifdef TURBO_DECODE
//kevinmonkey 050309 only 180 for avi buffer. 
#define A_FILE_BUF_SIZE         (180 - EXTRA_FS9660BUF)  
#else   //!TURBO_DECODE

    #ifdef REDUCE_SUP_SRT_FOR_FS9660
        #error  "Have no sub title buffer to enlarge fs buffer!"
    #endif

    #ifdef SUPPORT_MP4_SUBTITLE
#define A_FILE_BUF_SIZE         (97)
    #else   //!SUPPORT_MP4_SUBTITLE
#define A_FILE_BUF_SIZE         (57)
    #endif  //#ifdef SUPPORT_MP4_SUBTITLE
#endif  //#ifdef TURBO_DECODE

// FS buffer
#ifdef SUPPORT_FILE_SYSTEM_MODE
#define FS9660_SIZE             (9 + EXTRA_FS9660BUF)
#define P_FS9660YA              (P_SUPYA+SUPSIZE-FS9660_SIZE)
    #ifdef SUPPORT_MP4 //SUPPORT_FILE_SYSTEM_MODE && SUPPORT_MP4
#define N_FS9660YA              (A_FILE_BUF_YA+A_FILE_BUF_SIZE)
    #else   //SUPPORT_FILE_SYSTEM_MODE && !SUPPORT_MP4
#define N_FS9660YA              (MN_SUPYA+SUPSIZE-FS9660_SIZE)
    #endif
#else   //!SUPPORT_FILE_SYSTEM_MODE
#define FS9660YA                (GP_END+1)
#define FS9660_SIZE             (114)
#endif

// OSD
#ifndef TURBO_DECODE
    #if defined( SUPPORT_FILE_SYSTEM_MODE ) && defined( SUPPORT_MP4 )
#define MN_OSDYA                ( N_FS9660YA + FS9660_SIZE )
    #else   //!TURBO_DECODE && !(defined( SUPPORT_FILE_SYSTEM_MODE ) && defined( SUPPORT_MP4 ))
#define MN_OSDYA                ( MN_SUPYA + SUPSIZE )
    #endif
#endif  //TURBO_DECODE

#ifdef TURBO_DECODE
#ifdef SUPPORT_FILE_SYSTEM_MODE
#define SSAVER_YA               (GP_END)
    #else   //TURBO_DECODE && !SUPPORT_FILE_SYSTEM_MODE
#define SSAVER_YA 		        (FS9660YA+FS9660_SIZE)
    #endif  //SUPPORT_FILE_SYSTEM_MODE
#define SSAVER_PIC_SIZE         (31)
#define TEMPYA                  (SSAVER_YA)

#define JPEG_YA                 (SSAVER_YA+SSAVER_PIC_SIZE)
#define JPEG_CDBUF_SIZE         (300-80) //reduce 80k for progressive jpeg

#define CDROM_CODE_YA           (JPEG_YA + JPEG_CDBUF_SIZE)
    #ifdef DVD_SRV_BUF_SMALL
        #define CDROM_CODE_SIZE (60+SERVO_4ECC_SIZE)
    #else//!DVD_SRV_BUF_SMALL
        #define CDROM_CODE_SIZE (60)
    #endif//DVD_SRV_BUF_SMALL    
#else	//#ifdef TURBO_DECODE
    #ifdef SUPPORT_FILE_SYSTEM_MODE
#define CDROM_CODE_YA           (GP_END)
    #else   //!TURBO_DECODE && !SUPPORT_FILE_SYSTEM_MODE
#define CDROM_CODE_YA           (FS9660YA+FS9660_SIZE)
    #endif  //SUPPORT_FILE_SYSTEM_MODE
#define CDROM_CODE_SIZE         (60)

#define SSAVER_YA               (CDROM_CODE_YA+CDROM_CODE_SIZE)
#define SSAVER_PIC_SIZE         (31)
#define TEMPYA                  (SSAVER_YA)

#define JPEG_YA                 (SSAVER_YA+SSAVER_PIC_SIZE)
#define JPEG_CDBUF_SIZE         (300-80) //reduce 80k for progressive jpeg
#endif	//#ifdef TURBO_DECODE

// 2004/07/16 yltseng
#ifdef TURBO_DECODE
#define N_NAVYA                 (MN_SUPYA+SUPSIZE)
#define S_NAVYA                 (JPEG_YA)
#define MAX_BUF_SIZE            (52-SUPSIZE)//(A_DVD_SERVO_YA-N_NAVYA)
    #if (MAX_BUF_SIZE < 2)
    #error "Check Nav buffer, size less than 2K"
    #endif
#else//#ifdef TURBO_DECODE
    #ifdef USE_NAV_BUF_16M_DECREASE_SUBPICTURE
#define N_NAVYA                 (MN_OSDYA+OSDSIZE)
#define P_NAVYA                 (P_OSDYA+OSDSIZE)
        #ifdef DVDRELEASE
#define MAX_BUF_SIZE            (2048-N_NAVYA)
        #else   //!DVDRELEASE
#define MAX_BUF_SIZE            (2047-N_NAVYA)
        #endif  //DVDRELEASE
    #else   //!USE_NAV_BUF_16M_DECREASE_SUBPICTURE
        #ifdef SUPPORT_FILE_SYSTEM_MODE
#define N_NAVYA                 (MN_SUPYA)
#define P_NAVYA                 (P_SUPYA)
#define MAX_BUF_SIZE            (30)
        #else   //!USE_NAV_BUF_16M_DECREASE_SUBPICTURE && !SUPPORT_FILE_SYSTEM_MODE
#define N_NAVYA                 (JPEG_YA+JPEG_CDBUF_SIZE+10)
#define P_NAVYA                 (P_SUPYA)
#define MAX_BUF_SIZE            (40)
        #endif  //SUPPORT_FILE_SYSTEM_MODE
    #endif  //USE_NAV_BUF_16M_DECREASE_SUBPICTURE
#endif//#ifdef TURBO_DECODE
//free code size
#define FREE_CODE_YA            (N_NAVYA+MAX_BUF_SIZE)
#define FREE_CODESIZE           (0)

#define WMA_CODE_SIZE           (20)  //terry,2005/5/20 01:55¤U¤È,10->20
#define A_WMA_CODE_YA           (GP_END-WMA_CODE_SIZE)

#define SUPSIZE2                (0)

#define A_SUPYA2                (A_DVD_SERVO_YA + DVDV_SERVO_SIZE)
#define A_DEINTLACE_YA          (A_SUPYA2 + SUPSIZE2)
#define DEINTLACE_BUF_SIZE      (627)
/*#define ASVU_BUF1             (P_REF1_LUMA)
#define ASVU_BUF1_SIZE          (1216)
#define ASVU_BUF2               (A_DVD_SERVO_YA + DVDA_SERVO_SIZE)
#define ASVU_BUF2_SIZE          (858)
#define COMP_OSD_FONT           1000000000000000000000
#define OSD_FONT_SIZE           (42)
#define OSD0_TEMP_YA             1000000000000*/


//third segment (Game , RGB color index)
//small: 256*240 ,linear mode
#define GG_REF0_FRAME           (VFBMA + 0)
#define GG_REF1_FRAME           (VFBMA + 70)
#define GG_REF1_FRAME_END       (GG_REF1_FRAME + 70)
#define GAME_OSD_FRAME_START    (GG_REF0_FRAME)
#define GAME_PARAMETER_START    (GG_REF1_FRAME_END)
#define GAME_PARAMETER_SIZE     (1)
#define MAX_GAME_BUF            (100)         //driver size
#define GAMEYA                  (GAME_PARAMETER_START + GAME_PARAMETER_SIZE + 100)	//100K for work space
#define GAME_STACK 		(GAME_PARAMETER_START + GAME_PARAMETER_SIZE + 200)	//100K for driver
#define GAME_STACK_SIZE		(9)
#define GAME_FILE_START         (GAME_STACK + GAME_STACK_SIZE)     //NES game file buffer
#define MAX_GAME_FILE_SIZE      (1024)  //max NES game file content size(1M Bytes)
#define GAME_CALL_ENTRY         (SDRAM_BASE + GAMEYA * 1024)


#define OSD_BASE_USE_ADDR       JPEG_YA //kevinmonkey 050318 changed from P_BIDIR_LUMA, 
                                            //to avoid setup menu osd pollute wma code when field decoding is enabled

#ifdef SUPPORT_CD_TEXT
    #define CD_TEXT_YA          N_BIDIR_CHROMA
    #define CD_TEXT_SIZE        N_CHROMA_SIZE
#endif
#endif // SPHE1000 && SINGLE_CPU

#if 0
/*
//maybe we'll use independent memory config for file play in the future. 
// media container like avi
#ifdef TURBO_DECODE
#define MC_LUMA_SIZE                405
#define MC_CHROMA_SIZE              203
#define MC_BIDIR_LUMA_SIZE           80
#define MC_BIDIR_CHROMA_SIZE         40
#define MC_LOWRES_LUMA_SIZE         338
#define MC_LOWRES_CHROMA_SIZE       169
#define MC_LOWRES_BIDIR_LUMA_SIZE   169
#define MC_LOWRES_BIDIR_CHROMA_SIZE  85
#define MC_FRAME_BUF            END_SEG1
#else   //!TURBO_DECODE  //useless now
#define MC_LUMA_SIZE                338
#define MC_CHROMA_SIZE              169
#define MC_BIDIR_LUMA_SIZE          338
#define MC_BIDIR_CHROMA_SIZE        169
#define MC_LOWRES_LUMA_SIZE         338
#define MC_LOWRES_CHROMA_SIZE       169
#define MC_LOWRES_BIDIR_LUMA_SIZE   338
#define MC_LOWRES_BIDIR_CHROMA_SIZE 169
#define	MC_FRAME_BUF             END_SEG1
#endif  //TURBO_DECODE

#define	MC_REF0_LUMA                MC_FRAME_BUF
#define	MC_REF0_LUMA_END            (MC_REF0_LUMA + MC_LUMA_SIZE - 1)
#define	MC_REF0_CHROMA              (MC_REF0_LUMA_END + 1)
#define	MC_REF0_CHROMA_END          (MC_REF0_CHROMA + MC_CHROMA_SIZE - 1)
#define	MC_REF1_LUMA                (MC_REF0_CHROMA_END + 1)
#define	MC_REF1_LUMA_END            (MC_REF1_LUMA + MC_LUMA_SIZE - 1)
#define MC_REF1_CHROMA              (MC_REF1_LUMA_END + 1)
#define	MC_REF1_CHROMA_END          (MC_REF1_CHROMA + MC_CHROMA_SIZE - 1)
#define MC_BIDIR_LUMA               (MC_REF1_CHROMA_END + 1)
#define MC_BIDIR_LUMA_END           (MC_BIDIR_LUMA + MC_BIDIR_LUMA_SIZE - 1)
#define MC_BIDIR_CHROMA             (MC_BIDIR_LUMA_END + 1)
#define MC_BIDIR_CHROMA_END         (MC_BIDIR_CHROMA + MC_BIDIR_CHROMA_SIZE - 1)

#define	MC_LOWRES_REF0_LUMA         MC_FRAME_BUF
#define	MC_LOWRES_REF0_LUMA_END     (MC_LOWRES_REF0_LUMA + MC_LOWRES_LUMA_SIZE - 1)
#define	MC_LOWRES_REF0_CHROMA       (MC_LOWRES_REF0_LUMA_END + 1)
#define	MC_LOWRES_REF0_CHROMA_END   (MC_LOWRES_REF0_CHROMA + MC_LOWRES_CHROMA_SIZE - 1)
#define	MC_LOWRES_REF1_LUMA         (MC_LOWRES_REF0_CHROMA_END + 1)
#define	MC_LOWRES_REF1_LUMA_END     (MC_LOWRES_REF1_LUMA + MC_LOWRES_LUMA_SIZE - 1)
#define MC_LOWRES_REF1_CHROMA       (MC_LOWRES_REF1_LUMA_END + 1)
#define	MC_LOWRES_REF1_CHROMA_END   (MC_LOWRES_REF1_CHROMA + MC_LOWRES_CHROMA_SIZE - 1)
#define MC_LOWRES_BIDIR_LUMA        (MC_LOWRES_REF1_CHROMA_END + 1)
#define MC_LOWRES_BIDIR_LUMA_END    (MC_LOWRES_BIDIR_LUMA + MC_LOWRES_BIDIR_LUMA_SIZE - 1)
#define MC_LOWRES_BIDIR_CHROMA      (MC_LOWRES_BIDIR_LUMA_END + 1)
#define MC_LOWRES_BIDIR_CHROMA_END  (MC_LOWRES_BIDIR_CHROMA + MC_LOWRES_BIDIR_CHROMA_SIZE - 1)

#define MC_FRAMEBUF_END             (MC_BIDIR_CHROMA_END + 1)
#define MC_LOWRES_FRAMEBUF_END      (MC_LOWRES_BIDIR_CHROMA_END + 1)
*/
#endif  //if 0
