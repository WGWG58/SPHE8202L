#include "user_init.h"
#define SERVOBUF_COPY_USERTABLE_WHEN_RECONFIG

//Default Memory Layout
#define MEM_START		    (0)

#ifndef MEM_END
    #ifdef SDRAM_16Mb_Mode
#define MEM_END             (2048)
    #elif  defined(SDRAM_64Mb_Mode)
#define MEM_END             (8192)
    #else
#define MEM_END             (4096)
    #endif  //#ifdef SDRAM_16Mb_Mode
#endif  //#ifndef MEM_END

#define INVALID_MEMORY_ADDRESS  (MEM_END)

// Resident Memory From Memory Start Growing Downwardly
//IOP code address
#define A_IOPYA             (MEM_START)
//IOP code size
#define IOP_SIZE            (2) //1.3k

//stack top
#define A_MAIN_TASK_TOP     (1) // from 1.3k
//stack size
#ifdef SUPPORT_SW_OSD_SCALING
#define MAIN_TASK_SIZE      (3) // about 1.7k
#else
#define MAIN_TASK_SIZE      (2) // about 1.7k
#endif
//stack end address
#define A_MAIN_TASK_BOM     (A_MAIN_TASK_TOP + MAIN_TASK_SIZE)// to end of 3k

//SDRAM_CS address
#define SDRAM_CS_ST	        (A_MAIN_TASK_BOM)     //7
//SDRAM_CS size
//kevinmonkey 0410 reduce OSD buffer to increase cs size
#define SDRAM_CS_SZ         (35)

//SDRAM_CS end address
#define SDRAM_CS_END        (SDRAM_CS_ST + SDRAM_CS_SZ)

//OSD buffer address
#define A_OSDYA             (SDRAM_CS_END)
//kevinmonkey 0410 reduce OSD buffer to increase cs size
//OSD buffer size
#ifdef SUPPORT_SW_OSD_SCALING
#define OSDSIZE             (710) // for software osd scaling method,
#else                             // enlarge the osd buffer size, by robert.chang,2006/06/27
#define OSDSIZE             (110)
#endif

//OSD memory address
#define A_OSDYA_END         (A_OSDYA + OSDSIZE)

//screen saver pic size
#define SSAVER_PIC_SIZE     (31)
//screen saver pic address
#define SSAVER_YA           (A_OSDYA + OSDSIZE - SSAVER_PIC_SIZE - 1)
//screen saver pic end address
#define SSAVER_YA_END       (A_OSDYA_END)

//OSD decompress buffer address
#define COMP_OSD_FONT       (A_OSDYA_END)
//OSD decompress buffer size
#define OSD_FONT_SIZE       (60)
//OSD decompress buffer end address
#define COMP_OSD_FONT_END   (COMP_OSD_FONT + OSD_FONT_SIZE)

#define SEG1_END            (COMP_OSD_FONT_END)

//Resident Memory From Bottom Growing Upwardly
//debug stack size
#define DBG_STACK_SIZE      (2)
//debug stack bottom position
#define A_DBG_TASK_BOM      (MEM_END)
//debug stack top position
#define A_DBG_TASK_TOP      (A_DBG_TASK_BOM - DBG_STACK_SIZE)

//free code bottom address
#define FREE_CODE_BOTTOM    (A_DBG_TASK_TOP)
//free code memory section size
    #ifdef LOAD_MANY_CODE_TO_64M_SDRAM
#define FREE_CODESIZE       (512)
    #else   //!LOAD_MANY_CODE_TO_64M_SDRAM
#define FREE_CODESIZE       (92)
    #endif  //#ifdef LOAD_MANY_CODE_TO_64M_SDRAM
//free code memory address
#define FREE_CODE_YA        (FREE_CODE_BOTTOM - FREE_CODESIZE)

//DVD NAV code bottom address
#define DVD_NAV_CODE_BOTTOM (FREE_CODE_YA)
//dvd nav code size
    #ifdef LOAD_MANY_CODE_TO_64M_SDRAM
#define DVD_CODE_SIZE       (0)
    #else   //LOAD_MANY_CODE_TO_64M_SDRAM
#define DVD_CODE_SIZE       (70)
    #endif  //#ifdef LOAD_MANY_CODE_TO_64M_SDRAM
//dvd nav code size
#define DVD_NAV_CODE        (DVD_NAV_CODE_BOTTOM - DVD_CODE_SIZE)

//CDROM code section
#define CDROM_CODE_BOTTOM   (DVD_NAV_CODE)
//size of CDROM memory section
    #ifdef LOAD_MANY_CODE_TO_64M_SDRAM
#define CDROM_CODE_SIZE     (0)
    #elif defined(SUPPORT_DIVX6) && !defined(SUPPORT_DIVX6_64Mb)
#define CDROM_CODE_SIZE     (0)
    #else   //LOAD_MANY_CODE_TO_64M_SDRAM
#define CDROM_CODE_SIZE     (80)
    #endif  //#ifdef LOAD_MANY_CODE_TO_64M_SDRAM
#define CDROM_CODE_YA       (CDROM_CODE_BOTTOM - CDROM_CODE_SIZE)

//jepg code, for backward compatible
#define JPEG_CODE_BOTTOM    (CDROM_CODE_YA)
#ifdef JPG_OLD_PARSER_FLOW
#define JPEG_CODE_SIZE      (8)
#else
#define JPEG_CODE_SIZE      (0)
#endif
#define JPEG_CODE_YA        (JPEG_CODE_BOTTOM - JPEG_CODE_SIZE)

#define A_WMA_CODE_BOTTOM   (JPEG_CODE_YA)//WMA and MPEG4 code
    #ifdef LOAD_MANY_CODE_TO_64M_SDRAM
#define WMA_CODE_SIZE       (0)
    #elif defined(SDRAM_32Mb_Mode) && defined(DIP_CFG_ENABLE)
#define WMA_CODE_SIZE       (0)
    #else   //LOAD_MANY_CODE_TO_64M_SDRAM
#define WMA_CODE_SIZE       (10+40)
    #endif  //#ifdef LOAD_MANY_CODE_TO_64M_SDRAM
#define A_WMA_CODE_YA       (A_WMA_CODE_BOTTOM - WMA_CODE_SIZE)

#define MP4_CODE_BOTTOM     (A_WMA_CODE_YA)
#define MP4_CODE_SIZE       (0)              //terry,2005/5/20 01:51¤U¤È
#define A_MP4_CODE_YA       (MP4_CODE_BOTTOM - MP4_CODE_SIZE)

//AP1 code bottom address
#define AP1_ST_BOTTOM       (A_MP4_CODE_YA)
//AP1 code size
    #ifdef LOAD_MANY_CODE_TO_64M_SDRAM
#define AP_CODESIZE         (0)
    #else   //LOAD_MANY_CODE_TO_64M_SDRAM
#define AP_CODESIZE         (186)
    #endif  //#ifdef LOAD_MANY_CODE_TO_64M_SDRAM
//AP1 address
#define AP1_ST              (AP1_ST_BOTTOM - AP_CODESIZE)

//AP2&AP3 bottom address
#define AP2N3_BOTTOM        (AP1_ST)
//AP2 code size
    #ifdef LOAD_MANY_CODE_TO_64M_SDRAM
#define AP2_CODESIZE        (0)
    #else   //LOAD_MANY_CODE_TO_64M_SDRAM
#define AP2_CODESIZE        (32)
    #endif  //#ifdef LOAD_MANY_CODE_TO_64M_SDRAM
//AP3 code size
    #ifdef LOAD_MANY_CODE_TO_64M_SDRAM
#define AP3_CODESIZE        (0)
    #else   //LOAD_MANY_CODE_TO_64M_SDRAM
#define AP3_CODESIZE        (32)
    #endif  //#ifdef LOAD_MANY_CODE_TO_64M_SDRAM
//AP2&AP3 address
#define AP2N3_ST            (AP2N3_BOTTOM - AP2_CODESIZE)

//code drive 1 and 2 bottom address
#define DRV1N2_BOTTOM       (AP2N3_ST)
//code drive 1 and 2 code size
    #ifdef LOAD_MANY_CODE_TO_64M_SDRAM
#define DRV1_2_CODESIZE     (0)
    #else   //LOAD_MANY_CODE_TO_64M_SDRAM
#define DRV1_2_CODESIZE     (36)
    #endif  //#ifdef LOAD_MANY_CODE_TO_64M_SDRAM
//code drive 1 and 2 start address
#define DRV1N2_ST           (DRV1N2_BOTTOM - DRV1_2_CODESIZE)
//code drive 1 address
#define DRV1_ST             (DRV1N2_ST)
//code drive 2 start address
#define DRV2_ST             (DRV1N2_ST)
//code drive 1 size
#define DRV1_CODESIZE       (DRV1_2_CODESIZE)
//code drive 2 size
#define DRV2_CODESIZE       (DRV1_2_CODESIZE)

//card buffer bottom address
#define CARD_BUFFER_BOTTOM  (DRV1_ST)
//card buffer size
#define CARD_BUFFER_SIZE    (3)
//card buffer address
#define CARD_YA             (CARD_BUFFER_BOTTOM - CARD_BUFFER_SIZE)
//USB UHCI host buffer bottom address
#define USB_YA_BOTTOM       (CARD_YA)
//USB UHCI host buffer size
#define USB_BUFFER_SIZE     (0)
//USB UHCI host buffer address
#define USB_YA              (USB_YA_BOTTOM - USB_BUFFER_SIZE)

#define APPLICATION_MEMORY_START    (SEG1_END)
#define APPLICATION_MEMORY_END      (USB_YA)

//servo buffer bottom address
#define SERVOBUF_BOTTOM     (USB_YA)
//servo track buffer size when DVD video and CDDA
#define DVDV_SERVO_SIZE     (313)   //around 7 ECC block
//servo buffer size when playing DVD video
#define A_DVD_SERVO_YA      (SERVOBUF_BOTTOM - DVDV_SERVO_SIZE)

//servo track buffer size when DVD audio
#define DVDA_SERVO_SIZE     (134)   //around 3 ECC block

//servo track buffer size when file play
#define JPEG_SERVO_SIZE     (173)   //around 4 ECC block
//servo buffer when playing files
#define A_JPEG_SERVO_YA     (SERVOBUF_BOTTOM - JPEG_SERVO_SIZE)

//DSP memory address
#define A_DSP24YA           (APPLICATION_MEMORY_START)
//DSP size
#define DSP_SIZE            (282)
//DSP memory end address
#define A_DSP24YA_END       (A_DSP24YA + DSP_SIZE)

//stream buffer address
#define A_CDYA              (A_DSP24YA_END)
//stream buffer size
#define CDSIZE              (4)
//stream buffer end address
#define A_CD_BUF_END        (A_CDYA + CDSIZE)


//Continuous Content Specific Memory
//for DVD/VCD/SVCD disc

//frame buffer PAL D1
#define P_LUMA_SIZE         (405)   // PAL D1 luma size      720x576
#define P_CHROMA_SIZE       (203)   // PAL D1 chroma size    720x576/2

//PAL first frame luma buffer address
#define P_REF0_LUMA         (A_CD_BUF_END)
//PAL first frame luma buffer size
#define P_REF0_LUMA_SIZE    (P_LUMA_SIZE)
//PAL first frame luma buffer end address
#define P_REF0_LUMA_END     (P_REF0_LUMA + P_REF0_LUMA_SIZE)
//PAL first frame chroma buffer address
#define P_REF0_CHROMA       (P_REF0_LUMA_END)
//PAL first frame chroma buffer size
#define P_REF0_CHROMA_SIZE  (P_CHROMA_SIZE)
//PAL first frame chroma buffer end address
#define P_REF0_CHROMA_END   (P_REF0_CHROMA + P_REF0_CHROMA_SIZE)

//PAL second frame luma buffer address
#define P_REF1_LUMA         (P_REF0_CHROMA_END)
//PAL second frame luma buffer size
#define P_REF1_LUMA_SIZE    (P_LUMA_SIZE)
//PAL second frame luma buffer end address
#define P_REF1_LUMA_END     (P_REF1_LUMA + P_REF1_LUMA_SIZE)
//PAL second frame chroma buffer address
#define P_REF1_CHROMA       (P_REF1_LUMA_END)
//PAL second frame chroma buffer size
#define P_REF1_CHROMA_SIZE  (P_CHROMA_SIZE)
//PAL second frame chroma buffer end address
#define P_REF1_CHROMA_END   (P_REF1_CHROMA + P_REF1_CHROMA_SIZE)

//PAL B frame luma buffer address
#define P_BIDIR_LUMA        (P_REF1_CHROMA_END)
//PAL B frame luma buffer size
#define P_BIDIR_LUMA_SIZE   (P_LUMA_SIZE)
//PAL B frame luma buffer end address
#define P_BIDIR_LUMA_END    (P_BIDIR_LUMA + P_BIDIR_LUMA_SIZE)
//PAL B frame chroma buffer address
#define P_BIDIR_CHROMA      (P_BIDIR_LUMA_END)
//PAL B frame chroma buffer size
#define P_BIDIR_CHROMA_SIZE (P_CHROMA_SIZE)
//PAL B frame chroma buffer end address
#define P_BIDIR_CHROMA_END  (P_BIDIR_CHROMA + P_BIDIR_CHROMA_SIZE)

//first sub-picture buffer
//subpicture buffer
#define A_SUPYA             (P_BIDIR_CHROMA_END)
//subpicture buffer size
#define SUPSIZE             (52)
//subpicture buffer end address
#define A_SUPYA_BOTTOM      (A_SUPYA + SUPSIZE)

//video bitstream buffer
#define P_EVBYA             (A_SUPYA_BOTTOM)
#define P_EVBSZ             (241)
#define P_EVBYA_END         (P_EVBYA + P_EVBSZ)

//disc&drive cache buffer address
#define N_NAVYA             (P_EVBYA_END)
//disc and cache buffer size
#define MAX_BUF_SIZE        (50)
//disc&drive cache buffer end address
#define N_NAVYA_END         (N_NAVYA + MAX_BUF_SIZE)

/* only used in compact mode
// NTSC D1 (no preview mode)
#define N_LUMA_SIZE         (338)
#define N_CHROMA_SIZE       (169)

//NTSC first frame luma buffer address
#define N_REF0_LUMA         (A_SUPYA_BOTTOM)
//NTSC first frame luma buffer size
#define N_REF0_LUMA_SIZE    (N_LUMA_SIZE)
//NTSC first frame luma buffer end address
#define N_REF0_LUMA_END     (N_REF0_LUMA + N_REF0_LUMA_SIZE)
//NTSC first frame chroma buffer address
#define N_REF0_CHROMA       (N_REF0_LUMA_END)
//NTSC first frame chroma buffer size
#define N_REF0_CHROMA_SIZE  (N_CHROMA_SIZE)
//NTSC first frame chroma buffer end address
#define N_REF0_CHROMA_END   (N_REF0_CHROMA + N_REF0_CHROMA_SIZE)

//NTSC second frame luma buffer address
#define N_REF1_LUMA         (N_REF0_CHROMA_END)
//NTSC second frame luma buffer size
#define N_REF1_LUMA_SIZE    (N_LUMA_SIZE)
//NTSC second frame luma buffer end address
#define N_REF1_LUMA_END     (N_REF1_LUMA + N_REF1_LUMA_SIZE)
//NTSC second frame chroma buffer address
#define N_REF1_CHROMA       (N_REF1_LUMA_END)
//NTSC second frame chroma buffer size
#define N_REF1_CHROMA_SIZE  (N_CHROMA_SIZE)
//NTSC second frame chroma buffer end address
#define N_REF1_CHROMA_END   (N_REF1_CHROMA + N_REF1_CHROMA_SIZE)

//NTSC B frame luma buffer address
#define N_BIDIR_LUMA        (N_REF1_CHROMA_END)
//NTSC B frame luma buffer size
#define N_BIDIR_LUMA_SIZE   (N_LUMA_SIZE)
//NTSC B frame luma buffer end address
#define N_BIDIR_LUMA_END    (N_BIDIR_LUMA + N_BIDIR_LUMA_SIZE)
//NTSC B frame chroma buffer address
#define N_BIDIR_CHROMA      (N_BIDIR_LUMA_END)
//NTSC B frame chroma buffer size
#define N_BIDIR_CHROMA_SIZE (N_CHROMA_SIZE)
//NTSC B frame chroma buffer end address
#define N_BIDIR_CHROMA_END  (N_BIDIR_CHROMA + N_BIDIR_CHROMA_SIZE)

// PAL 2/3 D1 (with preview mode) graphic mode, under graphic mode width has to be multiple of 32
#define M_LUMA_SIZE         (270)       // PAL 2/3D1(480x576) luma size
#define M_CHROMA_SIZE       (135)       // PAL 2/3D1(480x576) chroma size

//preview first frame luma buffer address
#define M_REF0_LUMA         (A_SUPYA_BOTTOM)
//preview first frame luma buffer size
#define M_REF0_LUMA_SIZE    (M_LUMA_SIZE)
#define M_REF0_LUMA_END     (M_REF0_LUMA + M_REF0_LUMA_SIZE)
#define M_REF0_CHROMA       (M_REF0_LUMA_END)
#define M_REF0_CHROMA_SIZE  (M_CHROMA_SIZE)
#define M_REF0_CHROMA_END   (M_REF0_CHROMA + M_REF0_CHROMA_SIZE)

#define M_REF1_LUMA         (M_REF0_CHROMA_END)
#define M_REF1_LUMA_SIZE    (M_LUMA_SIZE)
#define M_REF1_LUMA_END     (M_REF1_LUMA + M_REF1_LUMA_SIZE)
#define M_REF1_CHROMA       (M_REF1_LUMA_END)
#define M_REF1_CHROMA_SIZE  (M_CHROMA_SIZE)
#define M_REF1_CHROMA_END   (M_REF1_CHROMA + M_REF1_CHROMA_SIZE)

#define M_BIDIR_LUMA        (M_REF1_CHROMA_END)
#define M_BIDIR_LUMA_SIZE   (M_LUMA_SIZE)
#define M_BIDIR_LUMA_END    (M_BIDIR_LUMA + M_BIDIR_LUMA_SIZE)
#define M_BIDIR_CHROMA      (M_BIDIR_LUMA_END)
#define M_BIDIR_CHROMA_SIZE (M_CHROMA_SIZE)
#define M_BIDIR_CHROMA_END  (M_BIDIR_CHROMA + M_BIDIR_CHROMA_SIZE)

#define N_EVBYA             (N_BIDIR_CHROMA_END)
#define N_EVBSZ             (241)
#define N_EVBYA_END         (N_EVBYA + N_EVBSZ)

#define M_EVBYA             (M_BIDIR_CHROMA_END)
#define M_EVBSZ             (241)
#define M_EVBYA_END         (P_EVBYA + P_EVBSZ)

//disc&drive cache buffer address
#define N_NAVYA             (P_EVBYA_END)
//disc and cache buffer size
#define MAX_BUF_SIZE        (50)
//disc&drive cache buffer end address
#define N_NAVYA_END         (N_NAVYA + MAX_BUF_SIZE)
*/

//second subpicture
#define A_SUPYA2            (N_NAVYA_END)
//second subpicture size
#define SUPSIZE2            (52)
#define A_SUPYA2_BOTTOM     (A_SUPYA2 + SUPSIZE2)

//first dvd audio buffer
#define ASVU_BUF1           (P_REF1_LUMA)
#define ASVU_BUF1_SIZE      (1216)  //(P_BIDIR_CHROMA_END - ASVU_BUF1)??
#define ASVU_BUF1_END       (ASVU_BUF1 + ASVU_BUF1_SIZE)

//second dvd audio buffer
#define ASVU_BUF2           (N_NAVYA_END)
#define ASVU_BUF2_SIZE      (858)
#define ASVU_BUF2_BOTTOM    (ASVU_BUF2 + ASVU_BUF2_SIZE)

#define ASVB_BUF_OFFSET     (ASVU_BUF2 - ASVU_BUF1_END)

//for files playback
//file system buffer
#define FS9660YA_BOTTOM     (A_JPEG_SERVO_YA)
//directory and file record buffer address
#define FS9660_SIZE         (94)
#define FS9660YA            (FS9660YA_BOTTOM - FS9660_SIZE)

//mp3 and GUI
//frame buffer  small: 352x288,block mode
#define GS_LUMA_SIZE        (99)
#define GS_CHROMA_SIZE      (50)

#define GS_REF0_LUMA        (A_CD_BUF_END)
#define GS_REF0_LUMA_SIZE   (GS_LUMA_SIZE)
#define GS_REF0_LUMA_END    (GS_REF0_LUMA + GS_REF0_LUMA_SIZE)
#define GS_REF0_CHROMA      (GS_REF0_LUMA_END)
#define GS_REF0_CHROMA_SIZE (GS_CHROMA_SIZE)
#define GS_REF0_CHROMA_END  (GS_REF0_CHROMA + GS_REF0_CHROMA_SIZE)

#define GS_REF1_LUMA        (GS_REF0_LUMA)
#define GS_REF1_LUMA_SIZE   (GS_LUMA_SIZE)
#define GS_REF1_LUMA_END    (GS_REF1_LUMA + GS_REF1_LUMA_SIZE)
#define GS_REF1_CHROMA      (GS_REF1_LUMA_END)
#define GS_REF1_CHROMA_SIZE (GS_CHROMA_SIZE)
#define GS_REF1_CHROMA_END  (GS_REF1_CHROMA + GS_REF1_CHROMA_SIZE)
#define	GS_END              (GS_REF1_CHROMA + GS_CHROMA_SIZE)

//udf worling buffer
#ifdef MEM_GRAPH_LARGE //2006-06-02, mimitsai add for HD ui.
#define A_UDF_WORK_BUF          (GP_END)
#else
#define A_UDF_WORK_BUF      (GS_END)
#endif
#define UDF_WORK_BUF_SIZE   (40)
#define UDF_WORK_BUF_END    (A_UDF_WORK_BUF + UDF_WORK_BUF_SIZE)


//jpeg
//using pal: 736x576 ,graphic mode, under graphic mode width has to be multiple of 32
#define GP_LUMA_SIZE        (414)
#define GP_CHROMA_SIZE      (207)

//jpeg display buffer
#define	GP_REF0_LUMA        (A_CD_BUF_END)
#define GP_REF0_LUMA_SIZE   (GP_LUMA_SIZE)
#define GP_REF0_LUMA_END    (GP_REF0_LUMA + GP_REF0_LUMA_SIZE)
#define GP_REF0_CHROMA      (GP_REF0_LUMA_END)
#define GP_REF0_CHROMA_SIZE (GP_CHROMA_SIZE)
#define GP_REF0_CHROMA_END  (GP_REF0_CHROMA + GP_REF0_CHROMA_SIZE)

//jpeg display buffer
#define	GP_REF1_LUMA        (GP_REF0_CHROMA_END)
#define GP_REF1_LUMA_SIZE   (GP_LUMA_SIZE)
#define GP_REF1_LUMA_END    (GP_REF1_LUMA + GP_REF1_LUMA_SIZE)
#define GP_REF1_CHROMA      (GP_REF1_LUMA_END)
#define GP_REF1_CHROMA_SIZE (GP_CHROMA_SIZE)
#define GP_REF1_CHROMA_END  (GP_REF1_CHROMA + GP_REF1_CHROMA_SIZE)
#define GP_END              (GP_REF1_CHROMA+GP_CHROMA_SIZE)

#define JPEG_FULLSCREEN_WORKING_BUF_YA  (GP_END)
#define JPEG_PREVIEW_WORKING_BUF_YA     (GP_REF0_LUMA + 844)

#define JPEG_FULLSCREEN_WORKING_BUF_SIZE    (400)
#define JPEG_PREVIEW_WORKING_BUF_SIZE       (400)

#define P_JPEG_PS           (GP_REF1_CHROMA_END)
//pregressive jpeg decoding frame buffer
#define JPEG_PS_SIZE        (JPEG_YA - P_JPEG_PS)
#define P_JPEG_PS_END       (P_JPEG_PS+ JPEG_PS_SIZE)

#define JPEG_CDBUF_BOTTOM   (FS9660YA)
//JPEG CD buffer size
#define JPEG_CDBUF_SIZE     (66)
#define JPEG_YA             (JPEG_CDBUF_BOTTOM - JPEG_CDBUF_SIZE)

//AVI
//file buffer of avi
#define A_FILE_BUF_END      (FS9660YA)
#define A_FILE_BUF_SIZE     (320)    //to be precise, 304k on 20060303
#define A_FILE_BUF_YA       (A_FILE_BUF_END - A_FILE_BUF_SIZE)

//#define A_SUPYA           xxx     //subpicture (internal subtitle), same as DVD
//#define P_REF0_LUMA       xxx     //frame buffer, same as DVD
#define A_EVBYA             (A_SUPYA_BOTTOM)
#define A_AVIEVBSZ          (241)
#define A_EVBYA_END         (A_EVBYA + A_AVIEVBSZ)

// MVC buffer
//co-located motion vector buffer address
#define MVC_BUF_YA          (A_EVBYA_END)
//co-located motion vector buffer size
#define MVC_BUF_SIZE        (30)
#define MVC_BUF_END         (MVC_BUF_YA + MVC_BUF_SIZE)

//nero digital
    #ifdef SUPPORT_NERODIGITAL_64MB
#define NERO_DIGITAL_MEMORY_END     (FS9660YA)
#define NERO_DIGITAL_MEMORY_SIZE    (3072)
#define NERO_DIGITAL_MEMORY_YA      (NERO_DIGITAL_MEMORY_END - NERO_DIGITAL_MEMORY_SIZE)
    #else
#define NERO_DIGITAL_MEMORY_END     (FS9660YA)
#define NERO_DIGITAL_MEMORY_SIZE    (A_FILE_BUF_SIZE)
#define NERO_DIGITAL_BUFFER_YA      (NERO_DIGITAL_MEMORY_END - NERO_DIGITAL_MEMORY_SIZE)
    #endif

//divx6
    #ifdef SUPPORT_DIVX6
#define DIVX6_MEMORY_END            (A_FILE_BUF_YA)
#define DIVX6_MEMORY_SIZE           (415)
#define DIVX6_MEMORY_YA             (DIVX6_MEMORY_END - DIVX6_MEMORY_SIZE)
    #endif

//deinterlace buffer
//deinterlace buffer
#if defined(SDRAM_32Mb_Mode) && defined(DIP_CFG_ENABLE)
//kevinmonkey 060919 32M deinterlace needs more space, occupy 2nd supic
#define A_DEINTLACE_YA      (A_SUPYA2)
#else
#define A_DEINTLACE_YA      (A_SUPYA2_BOTTOM)
#endif

#if defined(ALLOCATE_SINGLE_DEINTERLACE_FRAME_BUFFER) || defined(ALLOCATE_DOUBLE_DEINTERLACE_FRAME_BUFFER) //first deinterlace buffer
#define P_DEINT0_LUMA           (A_DEINTLACE_YA)
#define P_DEINT0_LUMA_SIZE      (P_LUMA_SIZE)
#define P_DEINT0_LUMA_END       (P_DEINT0_LUMA + P_DEINT0_LUMA_SIZE)
#define P_DEINT0_CHROMA         (P_DEINT0_LUMA_END)
#define P_DEINT0_CHROMA_SIZE    (P_CHROMA_SIZE)
#define P_DEINT0_CHROMA_END     (P_DEINT0_CHROMA + P_DEINT0_CHROMA_SIZE)

#define HD_DEINT0_LUMA          (HD_MVC_BUF_END)
#define HD_DEINT0_LUMA_SIZE     (HD_LUMA_SIZE)
#define HD_DEINT0_LUMA_END      (HD_DEINT0_LUMA + HD_DEINT0_LUMA_SIZE)
#define HD_DEINT0_CHROMA        (HD_DEINT0_LUMA_END)
#define HD_DEINT0_CHROMA_SIZE   (HD_CHROMA_SIZE)
#define HD_DEINT0_CHROMA_END    (HD_DEINT0_CHROMA + HD_DEINT0_CHROMA_SIZE)
#else  //!ALLOCATE_DEINTERLACE_FRAME_BUFFER
#define P_DEINT0_LUMA           (INVALID_MEMORY_ADDRESS)
#define P_DEINT0_LUMA_SIZE      (0)
#define P_DEINT0_LUMA_END       (P_DEINT0_LUMA + P_DEINT0_LUMA_SIZE)
#define P_DEINT0_CHROMA         (INVALID_MEMORY_ADDRESS)
#define P_DEINT0_CHROMA_SIZE    (0)
#define P_DEINT0_CHROMA_END     (P_DEINT0_CHROMA + P_DEINT0_CHROMA_SIZE)
#define HD_DEINT0_LUMA          (INVALID_MEMORY_ADDRESS)
#define HD_DEINT0_LUMA_SIZE     (0)
#define HD_DEINT0_LUMA_END      (HD_DEINT0_LUMA + HD_DEINT0_LUMA_SIZE)
#define HD_DEINT0_CHROMA        (INVALID_MEMORY_ADDRESS)
#define HD_DEINT0_CHROMA_SIZE   (0)
#define HD_DEINT0_CHROMA_END    (HD_DEINT0_CHROMA + HD_DEINT0_CHROMA_SIZE)
#endif //#if defined(ALLOCATE_SINGLE_DEINTERLACE_FRAME_BUFFER)...

#if defined(ALLOCATE_DOUBLE_DEINTERLACE_FRAME_BUFFER)   //second deinterlace buffer
#define P_DEINT1_LUMA           (P_DEINT0_CHROMA_END)
#define P_DEINT1_LUMA_SIZE      (P_LUMA_SIZE)
#define P_DEINT1_LUMA_END       (P_DEINT1_LUMA + P_DEINT1_LUMA_SIZE)
#define P_DEINT1_CHROMA         (P_DEINT1_LUMA_END)
#define P_DEINT1_CHROMA_SIZE    (P_CHROMA_SIZE)
#define P_DEINT1_CHROMA_END     (P_DEINT1_CHROMA + P_DEINT1_CHROMA_SIZE)

#define HD_DEINT1_LUMA          (HD_DEINT0_CHROMA_END)
#define HD_DEINT1_LUMA_SIZE     (HD_LUMA_SIZE)
#define HD_DEINT1_LUMA_END      (HD_DEINT1_LUMA + HD_DEINT1_LUMA_SIZE)
#define HD_DEINT1_CHROMA        (HD_DEINT1_LUMA_END)
#define HD_DEINT1_CHROMA_SIZE   (HD_CHROMA_SIZE)
#define HD_DEINT1_CHROMA_END    (HD_DEINT1_CHROMA + HD_DEINT1_CHROMA_SIZE)
#else  //!ALLOCATE_DOUBLE_DEINTERLACE_FRAME_BUFFER, assign 2nd buffer to collocate the 1st buffer
#define P_DEINT1_LUMA           (P_DEINT0_LUMA)
#define P_DEINT1_LUMA_SIZE      (P_DEINT0_LUMA_SIZE)
#define P_DEINT1_LUMA_END       (P_DEINT1_LUMA + P_DEINT1_LUMA_SIZE)
#define P_DEINT1_CHROMA         (P_DEINT0_CHROMA)
#define P_DEINT1_CHROMA_SIZE    (P_DEINT0_CHROMA_SIZE)
#define P_DEINT1_CHROMA_END     (P_DEINT1_CHROMA + P_DEINT1_CHROMA_SIZE)
#define HD_DEINT1_LUMA          (HD_DEINT0_LUMA)
#define HD_DEINT1_LUMA_SIZE     (HD_DEINT0_LUMA_SIZE)
#define HD_DEINT1_LUMA_END      (HD_DEINT1_LUMA + HD_DEINT1_LUMA_SIZE)
#define HD_DEINT1_CHROMA        (HD_DEINT0_CHROMA)
#define HD_DEINT1_CHROMA_SIZE   (HD_DEINT0_CHROMA_SIZE)
#define HD_DEINT1_CHROMA_END    (HD_DEINT1_CHROMA + HD_DEINT1_CHROMA_SIZE)
#endif  //#if defined(ALLOCATE_DOUBLE_DEINTERLACE_FRAME_BUFFER)

//HD MPEG4
#ifndef MAX_VIDEO_HORIZONTAL_RESOLUTION
#define MAX_VIDEO_HORIZONTAL_RESOLUTION (1024)
#endif
#ifndef MAX_VIDEO_VERTICAL_RESOLUTION
#define MAX_VIDEO_VERTICAL_RESOLUTION   (1024)
#endif

#define	HD_LUMA_SIZE            ((MAX_VIDEO_HORIZONTAL_RESOLUTION*MAX_VIDEO_VERTICAL_RESOLUTION)>>10)
#define	HD_CHROMA_SIZE          ((HD_LUMA_SIZE+1)/2)

#define HD_FRAME_BUFFER_START   (A_CD_BUF_END)
#define HD_REF0_LUMA            (HD_FRAME_BUFFER_START)
#define HD_REF0_LUMA_SIZE       (HD_LUMA_SIZE)
#define HD_REF0_LUMA_END        (HD_REF0_LUMA + HD_REF0_LUMA_SIZE)
#define HD_REF0_CHROMA          (HD_REF0_LUMA_END)
#define HD_REF0_CHROMA_SIZE     (HD_CHROMA_SIZE)
#define HD_REF0_CHROMA_END      (HD_REF0_CHROMA + HD_REF0_CHROMA_SIZE)

#define HD_REF1_LUMA            (HD_REF0_CHROMA_END)
#define HD_REF1_LUMA_SIZE       (HD_LUMA_SIZE)
#define HD_REF1_LUMA_END        (HD_REF1_LUMA + HD_REF1_LUMA_SIZE)
#define HD_REF1_CHROMA          (HD_REF1_LUMA_END)
#define HD_REF1_CHROMA_SIZE     (HD_CHROMA_SIZE)
#define HD_REF1_CHROMA_END      (HD_REF1_CHROMA + HD_REF1_CHROMA_SIZE)

#define HD_BIDIR_LUMA           (HD_REF1_CHROMA_END)
#define HD_BIDIR_LUMA_SIZE      (HD_LUMA_SIZE)
#define HD_BIDIR_LUMA_END       (HD_BIDIR_LUMA+ HD_BIDIR_LUMA_SIZE)
#define HD_BIDIR_CHROMA         (HD_BIDIR_LUMA_END)
#define HD_BIDIR_CHROMA_SIZE    (HD_CHROMA_SIZE)
#define HD_BIDIR_CHROMA_END     (HD_BIDIR_CHROMA + HD_BIDIR_CHROMA_SIZE)

#define HD_SUPYA                (HD_BIDIR_CHROMA_END)
#define HD_SUPSIZE              (52)
#define HD_SUPYA_BOTTOM         (HD_SUPYA + HD_SUPSIZE)

#define HD_EVBYA                (HD_SUPYA_BOTTOM)
#define HD_EVBYA_SIZE           (241)
#define HD_EVBYA_END            (HD_EVBYA + HD_EVBYA_SIZE)

#define HD_MVC_BUF_YA           (HD_EVBYA_END)
#define HD_MVC_BUF_SIZE         ((((MAX_VIDEO_HORIZONTAL_RESOLUTION/16)*64 + (((MAX_VIDEO_HORIZONTAL_RESOLUTION/16)*(MAX_VIDEO_VERTICAL_RESOLUTION/16)+1)/2)*32) + 1023)/1024)
#define HD_MVC_BUF_END          (HD_MVC_BUF_YA + HD_MVC_BUF_SIZE)

//HD JPEG
//#define HD_GP_LUMA_SIZE         (2025)
//#define HD_GP_CHROMA_SIZE       (1013)
#ifdef SDRAM_32Mb_Mode
    #define HD_GP_LUMA_SIZE         (900)
    #define HD_GP_CHROMA_SIZE       (450)
#elif defined(SDRAM_64Mb_Mode)
    #define HD_GP_LUMA_SIZE         (1520)
    #define HD_GP_CHROMA_SIZE       (760)
#endif

#define	HD_GP_REF0_LUMA         (A_CD_BUF_END)
#define HD_GP_REF0_LUMA_SIZE    (HD_GP_LUMA_SIZE)
#define HD_GP_REF0_LUMA_END     (HD_GP_REF0_LUMA + HD_GP_REF0_LUMA_SIZE)
#define HD_GP_REF0_CHROMA       (HD_GP_REF0_LUMA_END)
#define HD_GP_REF0_CHROMA_SIZE  (HD_GP_CHROMA_SIZE)
#define HD_GP_REF0_CHROMA_END   (HD_GP_REF0_CHROMA + HD_GP_REF0_CHROMA_SIZE)

#define	HD_GP_REF1_LUMA         (HD_GP_REF0_CHROMA_END)   //jpeg can overlap navigation buffer and dsp code if it invalidate cache and no mp3 cowork
#define HD_GP_REF1_LUMA_SIZE    (HD_GP_LUMA_SIZE)
#define HD_GP_REF1_LUMA_END     (HD_GP_REF1_LUMA + HD_GP_REF1_LUMA_SIZE)
#define HD_GP_REF1_CHROMA       (HD_GP_REF1_LUMA_END)
#define HD_GP_REF1_CHROMA_SIZE  (HD_GP_CHROMA_SIZE)
#define HD_GP_REF1_CHROMA_END   (HD_GP_REF1_CHROMA + HD_GP_REF1_CHROMA_SIZE)

#ifdef SDRAM_32Mb_Mode
    #define HD_JPEG_FULLSCREEN_WORKING_BUF_YA   (HD_GP_REF0_CHROMA+HD_GP_CHROMA_SIZE)
#else
    #define HD_JPEG_FULLSCREEN_WORKING_BUF_YA   (HD_GP_REF1_CHROMA+HD_GP_CHROMA_SIZE)
#endif
//#define HD_JPEG_FULLSCREEN_WORKING_BUF_SIZE       (100)
#define HD_JPEG_FULLSCREEN_WORKING_BUF_SIZE       (700)
//some special feature
//mp3 txt
//linrc change because after call setup menu,LRC display error 2005-11-3 17:20
#ifdef MP3_TXT_DISPLAY
#define A_MP3LRC_MEM_YA     (UDF_WORK_BUF_END)
#define MP3LRC_MEM_SIZE	    (2)
#define A_MP3LRC_INFO_YA    (A_MP3LRC_MEM_YA+MP3LRC_MEM_SIZE)
#endif

//MP3 encoder buffer
#ifdef INCLUDE_MP3_ENCODER
#define MP3ENC_PCM_BUF_YA       (A_DVD_SERVO_YA - 128)//(REF1_LUMA)
#define MP3ENC_PCM_BUF_SIZE     (96)
#define MP3ENC_FAT_BUF_YA       (MP3ENC_PCM_BUF_YA + MP3ENC_PCM_BUF_SIZE)
#define MP3ENC_FAT_BUF_SIZE     (1024)
#define MP3ENC_UPDATE_REC_YA    (MP3ENC_FAT_BUF_YA + MP3ENC_FAT_BUF_SIZE)
#define MP3ENC_UPDATE_REC_SIZE  (4)         //kevinmonkey not sure how large it is.

#define	DATA_BUF_ADDR           (SDRAM_BASE + ((MP3ENC_PCM_BUF_YA) * 1024))
#define	DATA_BUF_LEN            (MP3ENC_PCM_BUF_SIZE)	// 32 * 3KB		//buffer for mp3 data produced by DSP
#endif  //#ifdef SUPPORT_MP3_ENCODER

//CD_TEXT
#ifdef SUPPORT_CD_TEXT
    #define CD_TEXT_YA          (P_BIDIR_CHROMA)
    #define CD_TEXT_SIZE        (CHROMA_SIZE)
#endif

#define FSJPEGDATA_DES_YA           (FAT_TABLE_YA+FAT_TABLE_SIZE)
#define FSJPEGDATA_DES_BUFFER_SIZE  (3)

#define INDEX_BUF_SRC_YA     (FSJPEGDATA_DES_YA+3)
#define INDEX_BUF_SRC_SIZE   (1)
#define INDEX_BUF_DES_YA     (INDEX_BUF_SRC_YA+1)
#define INDEX_BUF_DES_SIZE   (1)

// Heritage From Previous Version
/*====================================================================================
** Decode mode memory config
**====================================================================================*/
#define P_VIDEO_COMPRESS    (RF_COMPRESS_888 \
                            |RF_COMPRESS_DITHER_OFF \
                            |RF_COMPRESS_CHROMA_FULL)
#define	GN_VIDEO_COMPRESS   (P_VIDEO_COMPRESS)
#define	GP_VIDEO_COMPRESS   (P_VIDEO_COMPRESS)
#define	GS_VIDEO_COMPRESS   (P_VIDEO_COMPRESS)

    #ifdef OSD_BMP_DISPLAY
#define OSD0_TEMP_YA        (A_OSDYA + OSDSIZE - 12)
    #else
#define OSD0_TEMP_YA        (A_OSDYA + OSDSIZE - 9)
    #endif

#define SERVO_SIZE          (20)
#define A_SERVO_YA          (A_JPEG_SERVO_YA)

#define LUMA_SIZE           (405)   // PAL D1 luma size      720x576
#define CHROMA_SIZE         (203)   // PAL D1 chroma size    720x576/2

#define	GN_REF0_LUMA        (GP_REF0_LUMA)
#define	GN_REF0_CHROMA	    (GP_REF0_CHROMA)
#define	GN_REF1_LUMA	    (GP_REF1_LUMA)
#define	GN_REF1_CHROMA      (GP_REF1_CHROMA)
#define	GN_END		        (GP_END)

//Game
// 3rd segment (Game , RGB color index)
//small: 256*240 ,linear mode
//kevinmonkey 060915 since NES driver fixed its address, I direct place it at
//307K to avoid the need of another NES driver build.
#define GAME_PARAMETER_START    (307)

#define GAME_PARAMETER_SIZE     (1)

#define MAX_GAME_BUF            (100)         //driver size
#define GAMEYA                  (GAME_PARAMETER_START + GAME_PARAMETER_SIZE + 100)	//100K for work space
#define GAME_STACK              (GAME_PARAMETER_START + GAME_PARAMETER_SIZE + 200)	//100K for driver
#define GAME_STACK_SIZE         (9)

#define GAME_FILE_START         (GAME_STACK + GAME_STACK_SIZE)     //NES game file buffer
#define MAX_GAME_FILE_SIZE      (1024)  //max NES game file content size(1M Bytes)

#define GAME_CALL_ENTRY         (SDRAM_BASE + GAMEYA * 1024)

#define GG_REF0_FRAME           (GAME_FILE_START + MAX_GAME_FILE_SIZE)
#define GG_REF1_FRAME           (GG_REF0_FRAME + 70)
#define GG_REF1_FRAME_END       (GG_REF1_FRAME + 70)
#define GAME_OSD_FRAME_START    (GG_REF0_FRAME)

#ifdef MEMMAP_ADJUST_TEMPYA
#define TEMPYA              (MEMMAP_CUSTOM_TEMPYA)
#else   //!ADJUST_TEMPYA
#define TEMPYA              (SSAVER_YA)
#endif  //temp memory block with size as big as screen saver size

//--------------------------------------
// for fat file system write
//--------------------------------------
#ifndef PMP_DVD//liweihua add 2004-12-10
#define FAT_WRITE_TEMP_YA	(P_BIDIR_LUMA)
#define FAT_WRITE_TEMP_SIZE (1)
#define FAT_COPY_YA         (FAT_WRITE_TEMP_YA+FAT_WRITE_TEMP_SIZE)
#define FAT_COPY_SIZE       (384)
#endif

//--------------------------------------
// for mp3 encoder write FAT devices
//--------------------------------------
#ifdef SUPPORT_MP3_ENCODER
#define MP3ENC_PCM_BUF_YA       (REF1_LUMA)
#define MP3ENC_PCM_BUF_SIZE     (96)
#define MP3ENC_FAT_BUF_YA       (MP3ENC_PCM_BUF_YA + MP3ENC_PCM_BUF_SIZE)
#define MP3ENC_FAT_BUF_SIZE     (1024)
#define MP3ENC_UPDATE_REC_YA    (MP3ENC_FAT_BUF_YA + MP3ENC_FAT_BUF_SIZE)
#define MP3ENC_UPDATE_REC_SIZE  (4)         //kevinmonkey not sure how large it is.

#define	DATA_BUF_ADDR		    (SDRAM_BASE + ((MP3ENC_PCM_BUF_YA) * 1024))
#define	DATA_BUF_LEN		    (MP3ENC_PCM_BUF_SIZE)	// 32 * 3KB		//buffer for mp3 data produced by DSP
#endif  //#ifdef SUPPORT_MP3_ENCODER
