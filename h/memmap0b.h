//====================================================================================
// memmap0b.h
// 8200 (before) 32M memory mapping
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
//          2005.09.12   yltseng, change define name for SUPPORT_FONT_COMPRESSED
//====================================================================================

#include "user_init.h"

#ifdef SPHE1000
#include "memmap_1000.h"
#else

#ifdef SUPPORT_MIDI     // 2005/01/04 yltseng
#include "memmap_dsp3.h"
#endif
/*====================================================================================
** Decode mode memory config
**====================================================================================*/
#define P_VIDEO_COMPRESS        (RF_COMPRESS_888 \
                                |RF_COMPRESS_DITHER_OFF \
                                |RF_COMPRESS_CHROMA_FULL)
#define	GN_VIDEO_COMPRESS       (P_VIDEO_COMPRESS)
#define	GP_VIDEO_COMPRESS       (P_VIDEO_COMPRESS)
#define	GS_VIDEO_COMPRESS       (P_VIDEO_COMPRESS)

/*====================================================================================
** task stack Allocation 
**====================================================================================*/
#ifdef SUPPORT_8202_DVB //Will be test later...
#ifdef ENLARGE_STATCK_SIZE    //sunzhh add
#define MAIN_TASK_SIZE 						NEW_MAIN_STACK_SIZE
#define A_MAIN_TASK_BOM						NEW_A_MAIN_STACK_BOM
#define A_MAIN_TASK_TOP						NEW_A_MAIN_STACK_TOP
#else
#define MAIN_TASK_SIZE          2           // about 1.7k,terry,2004/7/26 02:52PM
#define A_MAIN_TASK_TOP         1           // from 1.3k
#define A_MAIN_TASK_BOM         4           // to end of 2k
#endif
#elif defined(SUPPORT_DVD_NATIVE_GAME)
#define MAIN_TASK_SIZE          2           // about 1.7k,terry,2004/7/26 02:52PM
#define A_MAIN_TASK_TOP         1           // from 1.3k
#define A_MAIN_TASK_BOM         4           // to end of 2k
#else
#define MAIN_TASK_SIZE          1           // about 1.7k,terry,2004/7/26 02:52PM
#define A_MAIN_TASK_TOP         1           // from 1.3k
#define A_MAIN_TASK_BOM         3           // to end of 2k
#endif
#define DBG_STACK_SIZE          2

#if defined(SDRAM_64Mb_Mode) || defined(SUPPORT_MIDI2)  // 2004/12/22 yltseng
#define A_DBG_TASK_BOM          8192            // end of 8192k (8M)
#else
#define A_DBG_TASK_BOM          4096            // end of 4096k (4M)
#endif
#define A_DBG_TASK_TOP          (A_DBG_TASK_BOM-DBG_STACK_SIZE)

/*====================================================================================
** Memory Allocation Start
**====================================================================================*/
#define MEM_START		0

#ifdef SUPPORT_MIDI
#define MIDI_ST         4096
#endif

#ifdef SUPPORT_PLAY_SWD 
#define SWD_YA          4096
#define SWD_SIZE        4094
#endif

//----------------------
//first segment
//----------------------
// 2004/12/16 yltseng
#ifdef ENLARGE_SDRAM_CS_AND_OSD_SIZE
    #ifdef SUPPORT_8202_DVB
    #define SDRAM_CS_SZ         (DVB_CS_BUFFER_SIZE)
    #define OSDSIZE         (131+20)
    #else
    #define SDRAM_CS_SZ         (29+10)
    #define OSDSIZE         (131+10)
    #endif
#else
//kevinmonkey 0420 SDRAM CS is enlarged by cutting back OSD size (130->110)
/*
    #ifdef MINUS_VR_AUTH_PLAYBACK	//linrc add 2006-3-29 14:32
        #define VR_NEED_CS_SIZE		3
    #else
        #define VR_NEED_CS_SIZE		0
    #endif
    #ifdef SUPPORT_DVD_NATIVE_GAME		//linrc for DVD_NATIVE_GAME 2005-10-18 11:29
        #define SDRAM_CS_SZ         29+4
    #else
        #define SDRAM_CS_SZ         (29+1+VR_NEED_CS_SIZE) //ycwen 2005/11/16, add 1k for PCI_BUF
    #endif
*/
#define SDRAM_CS_SZ     (50)
#define OSDSIZE         (110) //ycwen 2005/11/16, add 1k to sdram_cs, for PCI_BUF
#endif

#define CDSIZE                  4
#define SSAVER_PIC_SIZE         31

#if defined(USE_C_IOP)//terry,2003/12/30 03:03PM
    #define IOP_SIZE            64
    #define A_IOPYA             (MEM_START + 1024*4)
    #define A_CDYA              (MEM_START + 3)   // 3
#elif defined(DECREASE_ESP_BUFFER_AS_IOP_BUFFER)//must use 4M*16 SDRAM!Jack added 06/03/13
    #define IOP_SIZE            2
    #define A_IOPYA             (8192-IOP_SIZE)
    #define A_CDYA              (MEM_START + 3)   // 3
#else
#ifdef ENLARGE_STATCK_SIZE   //Jack added 06/04/07
    #define IOP_SIZE            2
    #define A_IOPYA             (MEM_START + 0)
    #define A_CDYA              (A_IOPYA + IOP_SIZE + 2)   // 3
#else
    #define IOP_SIZE            2
    #define A_IOPYA             (MEM_START + 0)
    #define A_CDYA              (A_IOPYA + IOP_SIZE + MAIN_TASK_SIZE)   // 3
#endif
#endif

#ifdef SUPPORT_8202_DVB//Jack added 05/09/28
#define SDRAM_CS_ST		        (DVB_CS_BUFFER_YA)
#define A_OSDYA                 (47-31) //Jack moved A_OSDYA backward 06/06/02,because the old sdram_cs block is free in DVD+DVB system.
#else                                   //In DVD+DVB system we enlarge OSD_SIZE,so SEG1_END is larger than 167.If we let SEG1_END over 167,then open nes_game in DVD+DVB system,system will halt when entering game.
#define SDRAM_CS_ST		        (A_CDYA+CDSIZE)
#define A_OSDYA                 (SDRAM_CS_ST + SDRAM_CS_SZ)
#endif
#define SSAVER_YA               (A_OSDYA + OSDSIZE - SSAVER_PIC_SIZE - 1)
#define TEMPYA                  (SSAVER_YA)

#ifdef OSD_BMP_DISPLAY
    #define OSD0_TEMP_YA        (A_OSDYA + OSDSIZE - 12)
#else
    #define OSD0_TEMP_YA        (A_OSDYA + OSDSIZE - 9)
#endif

#define SEG1_END                (A_OSDYA + OSDSIZE)                     // A_OSDYA+OSDSIZE
#define VFBMA			        SEG1_END

//--------------------------
//second segment (DVD/VCD/CD)
//--------------------------
#define N_LUMA_SIZE             338             // NTSC D1 luma size 
#define N_CHROMA_SIZE           169             // NTSC D1 chroma size 
#define B_LUMA_SIZE             248             // PAL D1 B666 luma size 22MB 
#define B_CHROMA_SIZE           203             // PAL D1 B666 chroma size full-map 
#define M_LUMA_SIZE             270             // PAL 2/3D1 luma size 
#define M_CHROMA_SIZE           135             // PAL 2/3D1 chroma size 
#define D_LUMA_SIZE             99              // MIDI (352x288) luma size
#define D_CHROMA_SIZE           50              // MIDI (352x288) chroma size

#define LUMA_SIZE               405             // PAL D1 luma size 
#define CHROMA_SIZE             203             // PAL D1 chroma size 

// PAL D1 (576l)
#define	P_REF0_LUMA             (VFBMA + 0)					
#define	P_REF0_LUMA_END         (P_REF0_LUMA + LUMA_SIZE - 1)

#define	P_REF0_CHROMA           (P_REF0_LUMA_END + 1)
#define	P_REF0_CHROMA_END       (P_REF0_CHROMA + CHROMA_SIZE - 1)
#define	P_REF1_LUMA             (P_REF0_CHROMA_END + 1)
#define	P_REF1_LUMA_END         (P_REF1_LUMA + LUMA_SIZE - 1)
#define P_REF1_CHROMA           (P_REF1_LUMA_END + 1)
#define	P_REF1_CHROMA_END       (P_REF1_CHROMA + CHROMA_SIZE - 1)

#define P_BIDIR_LUMA            (P_REF1_CHROMA_END + 1)
#define P_BIDIR_LUMA_END        (P_BIDIR_LUMA + LUMA_SIZE - 1)
#define P_BIDIR_CHROMA          (P_BIDIR_LUMA_END + 1)
#define P_BIDIR_CHROMA_END      (P_BIDIR_CHROMA + CHROMA_SIZE - 1)
#define P_EVBYA                 (P_BIDIR_CHROMA_END + 1)
#ifdef NF200_TT27_AUDIO_ISSUE //ZXB 060809 FOR PHILIPS
//warning!! but need cut 15k from osd.
#define P_EVBSZ                 (235+6+15)
#else
#define P_EVBSZ                 (235+6)//NONO 4-4-5 22:48 ADD 6K
#endif

#define SEG2_END	        (P_EVBYA + P_EVBSZ)

#define ASVU_BUF1               (P_REF1_LUMA)
#define ASVU_BUF1_SIZE          (1216)
#define ASVU_BUF1_END           (ASVU_BUF1 + ASVU_BUF1_SIZE - 1)


// MIDI (352x288)
#define	D_REF0_LUMA             (VFBMA + 0)					
#define	D_REF0_LUMA_END         (D_REF0_LUMA + D_LUMA_SIZE - 1)

#define	D_REF0_CHROMA           (D_REF0_LUMA_END + 1)
#define	D_REF0_CHROMA_END       (D_REF0_CHROMA + D_CHROMA_SIZE - 1)
#define	D_REF1_LUMA             (D_REF0_CHROMA_END + 1)
#define	D_REF1_LUMA_END         (D_REF1_LUMA + D_LUMA_SIZE - 1)
#define D_REF1_CHROMA           (D_REF1_LUMA_END + 1)
#define	D_REF1_CHROMA_END       (D_REF1_CHROMA + D_CHROMA_SIZE - 1)

#define D_BIDIR_LUMA            (D_REF1_CHROMA_END + 1)
#define D_BIDIR_LUMA_END        (D_BIDIR_LUMA + D_LUMA_SIZE - 1)
#define D_BIDIR_CHROMA          (D_BIDIR_LUMA_END + 1)
#define D_BIDIR_CHROMA_END      (D_BIDIR_CHROMA + D_CHROMA_SIZE - 1)
#define D_EVBYA                 (D_BIDIR_CHROMA_END + 1)
#define D_EVBSZ                 (235 + 300*3 +6)//NONO 4-4-5 22:48 ADD 6K


// NTSC D1 (no preview mode)
#define	N_REF0_LUMA             (VFBMA + 0)					
#define	N_REF0_LUMA_END         (N_REF0_LUMA + N_LUMA_SIZE - 1)
#define	N_REF0_CHROMA           (N_REF0_LUMA_END + 1)
#define	N_REF0_CHROMA_END       (N_REF0_CHROMA + N_CHROMA_SIZE - 1)
#define	N_REF1_LUMA             (N_REF0_CHROMA_END + 1)
#define	N_REF1_LUMA_END         (N_REF1_LUMA + N_LUMA_SIZE - 1)
#define N_REF1_CHROMA           (N_REF1_LUMA_END + 1)
#define	N_REF1_CHROMA_END       (N_REF1_CHROMA + N_CHROMA_SIZE - 1)
#define N_BIDIR_LUMA            (N_REF1_CHROMA_END + 1)
#define N_BIDIR_LUMA_END        (N_BIDIR_LUMA + N_LUMA_SIZE - 1)
#define N_BIDIR_CHROMA          (N_BIDIR_LUMA_END + 1)
#define N_BIDIR_CHROMA_END      (N_BIDIR_CHROMA + N_CHROMA_SIZE - 1)

#define N_EVBYA                 (N_BIDIR_CHROMA_END + 1)
#define N_EVBSZ                 (235 + 6)///NONO 4-4-5 22:48 ADD 6K



// PAL 2/3 D1 (with preview mode)
#define	M_REF0_LUMA             (VFBMA + 0)					
#define	M_REF0_LUMA_END         (M_REF0_LUMA + M_LUMA_SIZE - 1)
#define	M_REF0_CHROMA           (M_REF0_LUMA_END + 1)
#define	M_REF0_CHROMA_END       (M_REF0_CHROMA + M_CHROMA_SIZE - 1)
#define	M_REF1_LUMA             (M_REF0_CHROMA_END + 1)
#define	M_REF1_LUMA_END         (M_REF1_LUMA + M_LUMA_SIZE - 1)
#define M_REF1_CHROMA           (M_REF1_LUMA_END + 1)
#define	M_REF1_CHROMA_END       (M_REF1_CHROMA + M_CHROMA_SIZE - 1)
#define M_BIDIR_LUMA            (M_REF1_CHROMA_END + 1)
#define M_BIDIR_LUMA_END        (M_BIDIR_LUMA + LUMA_SIZE - 1)
#define M_BIDIR_CHROMA          (M_BIDIR_LUMA_END + 1)
#define M_BIDIR_CHROMA_END      (M_BIDIR_CHROMA + CHROMA_SIZE - 1)

#define M_EVBYA                 (M_BIDIR_CHROMA_END + 1)
#define M_EVBSZ                 (235 + 6)//NONO 4-4-5 22:48 ADD 6K


//second segment (JPEG)
//using pal: 720x576 ,block mode
#define GP_LUMA_SIZE            414
#define GP_CHROMA_SIZE          207

#define	GP_REF0_LUMA            (VFBMA + 0)
#define	GP_REF0_CHROMA          (GP_REF0_LUMA + GP_LUMA_SIZE) 

//#define	GP_REF1_LUMA	        (GP_REF0_CHROMA + GP_CHROMA_SIZE)   
//#define	GP_REF1_CHROMA          (GP_REF1_LUMA + GP_LUMA_SIZE) 
//#define	GP_END		        (GP_REF1_CHROMA + GP_CHROMA_SIZE)


#define	GN_REF0_LUMA            GP_REF0_LUMA
//#define	GN_REF1_LUMA	        GP_REF1_LUMA
#define	GN_REF0_CHROMA	        GP_REF0_CHROMA
//#define	GN_REF1_CHROMA          GP_REF1_CHROMA
//#define	GN_END		        GP_END


// 3rd segment (MP3 GUI)
//small: 352x288,block mode
#define GS_LUMA_SIZE            99
#define GS_CHROMA_SIZE          50
#define	GS_REF0_LUMA            (VFBMA + 0)
#define	GS_REF1_LUMA            (GS_REF0_LUMA)
#define	GS_REF0_CHROMA	        (GS_REF0_LUMA + GS_LUMA_SIZE)
#define	GS_REF1_CHROMA          (GS_REF1_LUMA + GS_LUMA_SIZE)
#define	GS_END		        (GS_REF1_CHROMA + GS_CHROMA_SIZE)
//#define A_UDF_WORK_BUF          (GS_END)
#ifdef MEM_GRAPH_LARGE //2006-06-02, mimitsai add for HD ui.	
#define A_UDF_WORK_BUF          (GP_END)
#else
#define A_UDF_WORK_BUF          (GS_END)
#endif
#define UDF_WORK_BUF_SIZE       (40)

//linrc change because after call setup menu,LRC display error 2005-11-3 17:20
#ifdef MP3_TXT_DISPLAY
#define A_MP3LRC_MEM_YA			(A_UDF_WORK_BUF+UDF_WORK_BUF_SIZE)
#define MP3LRC_MEM_SIZE			(2)
#define A_MP3LRC_INFO_YA		(A_MP3LRC_MEM_YA+MP3LRC_MEM_SIZE)
#endif


// 3rd segment (Game , RGB color index)
//small: 256*240 ,linear mode
#define GG_REF0_FRAME           (VFBMA + 0)
#define GG_REF1_FRAME           (VFBMA + 70)
#define GG_REF1_FRAME_END       (GG_REF1_FRAME + 70)
#define GAME_OSD_FRAME_START    (GG_REF0_FRAME)
#define GAME_PARAMETER_START    (GG_REF1_FRAME_END)

//#define GG_REF0_FRAME         (1600)
//#define GG_REF1_FRAME         (1600+70)
//#define GG_REF1_FRAME_END     (1600+70*2)
//#define GAME_OSD_FRAME_START  GG_REF0_FRAME
//#define GAME_PARAMETER_START  (VFBMA+70*2)

#define GAME_PARAMETER_SIZE     (1)

#define MAX_GAME_BUF            (100)         //driver size
#define GAMEYA                  (GAME_PARAMETER_START + GAME_PARAMETER_SIZE + 100)	//100K for work space
#define GAME_STACK              (GAME_PARAMETER_START + GAME_PARAMETER_SIZE + 200)	//100K for driver
#define GAME_STACK_SIZE         (9)

#define GAME_FILE_START         (GAME_STACK + GAME_STACK_SIZE)     //NES game file buffer
#define MAX_GAME_FILE_SIZE      (1024)  //max NES game file content size(1M Bytes)

#define GAME_CALL_ENTRY         (SDRAM_BASE + GAMEYA * 1024)

//ycwen 2005/1/21
#if defined(MP3_JPEG_COWORK)&& defined(SDRAM_32Mb_Mode)
#define MP3_BUFFER_START                    (P_BIDIR_LUMA+100)   
#define MP3_BUFFER_SIZE                     730
#define POINTER_OFFSET                      200
#endif

//-------------------------------------
//4th segment
//-------------------------------------
// 2004/11/18 yltseng

#define DSP_START               SEG2_END                            // 2226+6=2232//NONO 4-4-5 22:48 ADD 6K
#define A_DSP24YA               (DSP_START + 0)                     // 2226+6=2232//NONO 4-4-5 22:48 ADD 6K
#define P_JPEG_PS               (GP_REF0_CHROMA + GP_CHROMA_SIZE) 

//  2005/04/07 kevinmonkey allow to separate drv1 and drv2
#define DRV1_ST                 (DRV1N2_ST)
#define DRV2_ST                 (DRV1N2_ST)
#define DRV1_CODESIZE           (DRV1_2_CODESIZE)
#define DRV2_CODESIZE           (DRV1_2_CODESIZE)

#ifdef SUPPORT_MIDI                                                 // 2005/01/04 yltseng

#define DSP_SIZE                (48-16)
#define PCMSIZE                 DSP3_MIDI_DM                        //4429KBs = 141KBs(47K words) + 4288KBs wavetable
#define AUDSIZE                 DSP3_MIDI_PM
#define PCMOFFSET               (50)
#define PCM_ST                  (A_DSP24YA+DSP_SIZE)                // 2274+6=2280//NONO 4-4-5 22:48 ADD 6K
#define A_PCMYA                 (MIDI_ST + 0)
#define A_AUDYA                 (PCM_ST + 0)
#define JPEG_PS_SIZE            (A_AUDYA + AUDSIZE - P_JPEG_PS)
#define DRV1N2_ST               (PCM_ST + PCMOFFSET + AUDSIZE)

#elif defined(SUPPORT_REP_READ)                                     //terry,2004/2/16 09:29AM

#define DSP_SIZE                48                                  // dsp code-size
#define PCMOFFSET               (200-16)
#define PCMSIZE                 4096
#define AUDSIZE                 50
#define A_PCMYA                 (4096)
#define PCM_ST                  (A_DSP24YA+DSP_SIZE)                // 2274+6=2280//NONO 4-4-5 22:48 ADD 6K
#define A_AUDYA                 (PCM_ST + PCMOFFSET)
#define JPEG_PS_SIZE            (A_AUDYA + AUDSIZE - P_JPEG_PS)     //(414+207+814+250+42)
#define DRV1N2_ST               (PCM_ST+PCMOFFSET+AUDSIZE)

#else

#define DSP_SIZE                282                                 // In fact, DSP_SIZE now only needs 281K bytes                                 // dsp code-size
    #ifdef MP3_JPEG_COWORK                                          //ycwen 2005/1/21
        #ifdef SDRAM_32Mb_Mode 
            #define JPEG_PS_SIZE            (MP3_BUFFER_START - P_JPEG_PS )    
        #elif defined SDRAM_64Mb_Mode
            #define JPEG_PS_SIZE            (A_DSP24YA - P_JPEG_PS)
        #endif
    #else                                                           //(not define MP3_JPEG_COWORK)
#define JPEG_PS_SIZE            (A_DSP24YA + DSP_SIZE - P_JPEG_PS)  //(414+207+814+250+42)//parson 
    #endif                                                          //(MP3_JPEG_COWORK)

#define DRV1N2_ST               (A_DSP24YA+DSP_SIZE)                //2530//NONO 2004-4-10 23:19

#endif

#define DRV1_2_CODESIZE         36


#define AP2_CODESIZE            32
#define AP3_CODESIZE            32

#ifdef ENLARGE_SDRAM_CS_AND_OSD_SIZE                                // 2004/01/28 yltseng
	#ifdef SUPPORT_8202_DVB
    #define AP_CODESIZE         (152 + 18 + 16 - 30)
    #else
    #define AP_CODESIZE         (152 + 18 + 16 - 20)
    #endif
#else
    #define AP_CODESIZE         (152 + 18 + 16)
#endif

#define AP2N3_ST                (DRV1N2_ST+DRV1_2_CODESIZE)         //2566//NONO 2004-4-10 23:22
#define AP1_ST                  (AP2N3_ST+AP2_CODESIZE)             //2598//NONO 2004-4-10 23:22
#define SEG4_END                (AP1_ST + AP_CODESIZE)

#ifdef FILE_MODE_WRITE                                              //sunzhh add for file mode usb&card write 2004-12-23 16:53
#define FS_STRUCTURE_YA      AP1_ST
#define FS_STRUCTURE_SIZE    (114) 
#define FAT_TABLE_YA         (FS_STRUCTURE_YA+114) 
#define FAT_TABLE_SIZE       (50)

#define FSJPEGDATA_DES_YA    (FAT_TABLE_YA+FAT_TABLE_SIZE)
#define FSJPEGDATA_DES_BUFFER_SIZE  (3)

#define INDEX_BUF_SRC_YA     (FSJPEGDATA_DES_YA+3)
#define INDEX_BUF_SRC_SIZE   (1)
#define INDEX_BUF_DES_YA     (INDEX_BUF_SRC_YA+1)
#define INDEX_BUF_DES_SIZE   (1)

#endif


//-------------------------------------
//5th segment for servo buffer
//-------------------------------------
/*
#define JPEG_YA                 (OSD0_TEMP_YA+DISP_WORK_BUF_SIZE)
#define JPEG_CDBUF_SIZE         (358)
#define DVD_NAV_CODE            (JPEG_YA) //dvd/vcd nav. code
#define DVD_CODE_SIZE           (70)
#define N_NAVYA                 (DVD_NAV_CODE+DVD_CODE_SIZE) //nav. buffer
#define MAX_BUF_SIZE            (70)     // size for NAV buffer
#define A_DVD_SERVO_YA          (N_NAVYA+MAX_BUF_SIZE)     //DVDV-A/VCD/CD servo work buffer start address
#define A_JPEG_SERVO_YA         (JPEG_YA+JPEG_CDBUF_SIZE)  //MP3/JPEG servo work buffer start address
#define DVDA_SERVO_SIZE         (218)
#define DVDV_SERVO_SIZE         (1076)
#define JPEG_SERVO_SIZE         (858)
#define ASVU_BUF2               (JPEG_YA+JPEG_CDBUF_SIZE)
#define ASVU_BUF2_SIZE          (858)
#define FS9660YA                (A_DVD_SERVO_YA+DVDV_SERVO_SIZE)
#define FS9660_SIZE             (114)
#define COMP_OSD_FONT           (FS9660YA+FS9660_SIZE)
#define OSD_FONT_SIZE           (42)
*/

//-------------------------------------
//5th segment for De-Interlace buffer
//-------------------------------------
#define SUPSIZE	                52
#ifdef  TWO_SUBTITLE
#define SUPSIZE2                SUPSIZE
#else
#define SUPSIZE2                0
#endif

#define SERVO_SIZE              (20)

#if defined(HOST_UHCI)||defined(SPHE8202_CARD_STORAGE)||defined(USB_HOST_DRV) 
  #define USB_BUFFER_SIZE          7 //10 
  #define CARD_BUFFER_SIZE         3
  #ifdef  SUPPORT_MIDI2
   #define USB_YA                  SEG6_END        //DVDV-A/VCD/CD servo work buffer start address
   #define CARD_YA                (USB_YA + USB_BUFFER_SIZE)
  #else
   #define USB_YA                  SEG4_END        //DVDV-A/VCD/CD servo work buffer start address
   #define CARD_YA                (USB_YA + USB_BUFFER_SIZE)
  #endif
  #define A_SERVO_YA               (USB_YA+USB_BUFFER_SIZE+CARD_BUFFER_SIZE)
#else
  #ifdef  SUPPORT_MIDI2
   #define A_SERVO_YA              SEG6_END        //DVDV-A/VCD/CD servo work buffer start address
  #else
   #define A_SERVO_YA              SEG4_END        //DVDV-A/VCD/CD servo work buffer start address
  #endif
#endif


// SERVO-SUP2-DEINT-NAVC-NAVD-SUP
/*
*NONO 4-4-5 22:48 USE 25K TO add AP_CODESIZE(152->152+19)[AP code and Part of Servo Code] 
*                               & M_EVBSZ(235->235+6)[video bit-stream]
*/

#if defined(HOST_UHCI)||defined(SPHE8202_CARD_STORAGE)||defined(USB_HOST_DRV)  
#define DVDV_SERVO_SIZE         (389 - SUPSIZE2-24)                        // DVDV=399-10-25=365 or 399-52k -10-25K//2769
#define DVDA_SERVO_SIZE         (158 - 24 )                                     // DVDA=168k-10-25=133
#define JPEG_SERVO_SIZE         (197 - 24) //678                                     // JPEG=678k//197-25=172K
#else

#ifdef DVD_ESP_2S
#define DVDV_SERVO_SIZE         (399 - SUPSIZE2+627/*DEINTLACE_BUF_SIZE*/-24)                        // DVDV=399 or 399-52k
#else//#ifdef DVD_ESP_2S
#define DVDV_SERVO_SIZE         (399 - SUPSIZE2-24)                        // DVDV=399 or 399-52k
#endif//#ifdef DVD_ESP_2S

#define DVDA_SERVO_SIZE         (168-24)                                     // DVDA=168k
#define JPEG_SERVO_SIZE         (207-24) //678                                     // JPEG=678k
#endif
// DVDV mode
#ifdef DVD_ESP_2S
#define DEINTLACE_BUF_SIZE      0//627                                 // size for de-interlacing buffer
#else
#define DEINTLACE_BUF_SIZE      (627)                                  // size for de-interlacing buffer
#endif

#define DVD_CODE_SIZE           70                                      // size for DVD NAV code
#define MAX_BUF_SIZE            50//60//70                                      // size for DVD NAV buffer

#define A_DVD_SERVO_YA          A_SERVO_YA
#define A_SUPYA2                (A_DVD_SERVO_YA + DVDV_SERVO_SIZE)
#define A_DEINTLACE_YA          (A_SUPYA2 + SUPSIZE2)
//#define DVD_NAV_CODE            (A_DEINTLACE_YA + DEINTLACE_BUF_SIZE)   //dvd/vcd nav. code
//#define N_NAVYA                 (DVD_NAV_CODE + DVD_CODE_SIZE)          //nav. buffer
//#define A_SUPYA	                (N_NAVYA + MAX_BUF_SIZE)
//2004.7.22 joshua modified for conflict of JPEG and LOAD_NAV, only change the location of N_NAVYA DVD_NAV_CODE
#define N_NAVYA                 (A_DEINTLACE_YA + DEINTLACE_BUF_SIZE)   //nav. buffer
#define DVD_NAV_CODE            (N_NAVYA + MAX_BUF_SIZE)          //dvd/vcd nav. code
#define A_SUPYA	                (DVD_NAV_CODE + DVD_CODE_SIZE)

#ifdef USE_32M_BUF_IN_64M_SDRAM_AS_ESP_BUF	//we use the 64M sdram's end of 32M memory as ESP USE...
#define A_DVD_SERVO_YA_4096		4096		//define it must use 64M sdram...linrc 2005-11-18 17:10
#define DVDV_SERVO_SIZE_4096    4096
#endif

#define SEG5_END                (A_SUPYA+SUPSIZE)


// DVDA mode
#define ASVU_BUF2_SIZE          858                                     //
#define ASVU_BUF2               (A_DVD_SERVO_YA + DVDA_SERVO_SIZE)
#define ASVB_BUF_OFFSET         (ASVU_BUF2 - ASVU_BUF1_END - 1)

//DVB demux memory map //yuliang 05/05/02
//#ifdef SUPPORT_8202_DVB        
//DVB Feature function buffer       
//tcf move here 2005-11-15 13:30
//#define DVB_FEATURE_BUFFER (6*1024+100)
//#define DVB_EPG_BUFFER_START DVB_FEATURE_BUFFER
//#define DVB_EPG_BUFFER_SZ (443) //33+410
//#define DVB_CHANNEL_INFO_START DVB_EPG_BUFFER_START
//#define DVB_CHANNEL_INFO_SZ (33)//K
//#define DVB_EPG_NEW_EVENT_BUFFER_START (DVB_CHANNEL_INFO_START+DVB_CHANNEL_INFO_SZ)
//#define DVB_EPG_NEW_EVENT_BUFFER_SZ (410)//K
//#define g_ch_info ((ST_CHANNEL_INFO *)(SDRAM_BASE+DVB_CHANNEL_INFO_START*1024))
//#define new_event_buffer_pool_start	((ST_PROGRAM_EVENT *)(SDRAM_BASE+DVB_EPG_NEW_EVENT_BUFFER_START*1024))
//#define DVB_EPG_BUFFER_End (DVB_EPG_BUFFER_START+DVB_EPG_BUFFER_SZ)
//#endif

//#define DVB_TTX_BUFFER_START  			DVB_FEATURE_BUFFER
//#define DVB_TTX_BUFFER_SZ 				(466)//230+70+44+16+20+46+20+20
//#define DVB_TTX_VBI_DECODER_START 		DVB_TTX_BUFFER_START
//#define DVB_TTX_VBI_DECODER_SZ 			(230)
//#define DVB_TTX_VBI_DEMUX_START 		(DVB_TTX_VBI_DECODER_START+DVB_TTX_VBI_DECODER_SZ)
//#define DVB_TTX_VBI_DEMUX_SZ 			(70)
//#define DVB_TTX_VBI_SLICED_START  		(DVB_TTX_VBI_DEMUX_START+DVB_TTX_VBI_DEMUX_SZ)
//#define DVB_TTX_VBI_SLICED_SZ 			(44) //tcf 2005-11-3
//#define DVB_TTX_VBI_SLICED_SZ 		(64)
//#define DVB_TTX_VT_PAGE_START 			(DVB_TTX_VBI_SLICED_START+DVB_TTX_VBI_SLICED_SZ)
//#define DVB_TTX_VT_PAGE_SZ 				(16)
//#define DVB_TTX_TTXBUFFER_START 		(DVB_TTX_VT_PAGE_START+DVB_TTX_VT_PAGE_SZ)
//#define DVB_TTX_TTXBUFFER_SZ 			(20)
//#define DVB_TTX_TEMP_TTXFONT_START 		(DVB_TTX_TTXBUFFER_START+DVB_TTX_TTXBUFFER_SZ)
//#define DVB_TTX_TEMP_TTXFONT_SZ 		(23)
//#define DVB_TTX_TTXFONT_START 			(DVB_TTX_TEMP_TTXFONT_START+DVB_TTX_TEMP_TTXFONT_SZ)
//#define DVB_TTX_TTXFONT_SZ 				(23)
//#define DVB_TTX_VBI_PAGE_START 			(DVB_TTX_TTXFONT_START+DVB_TTX_TTXFONT_SZ)
//#define DVB_TTX_VBI_PAGE_SZ 			(20)
//#define DVB_TTX_VBI_PAGE_DRAW_START 	(DVB_TTX_VBI_PAGE_START+DVB_TTX_VBI_PAGE_SZ) //tcf added 2005-12-13 13:43
//#define DVB_TTX_VBI_PAGE_DRAW_SZ 		(20)

//#define DMUX_BUFFER_POOL	4*1024//	ASVU_BUF2
//#define DEMUX_VIDEO_START	(DMUX_BUFFER_POOL)
//#define DEMUX_VIDEO_SZ		(256)
//#define DEMUX_AUDIO_START	(DEMUX_VIDEO_START+DEMUX_VIDEO_SZ)
//#define DEMUX_AUDIO_SZ		(32)
//#define DEMUX_PSI_POOL		(DEMUX_AUDIO_START+DEMUX_AUDIO_SZ)
//#define DEMUX_PSI_POOL_SZ	(30)//(90)
//#define DEMUX_PSI_LEN		(3)
//#if defined( SUPPORT_EPG)||defined(SUPPORT_TELETEXT)||defined(SUPPORT_SUBTITLE)
//    #define DEMUX_EPG_START		(DEMUX_PSI_POOL+DEMUX_PSI_POOL_SZ)
//    #define DEMUX_EPG_SZ		(20)//(50)
//    #define DEMUX_TTX_START		(DEMUX_PSI_POOL+DEMUX_PSI_POOL_SZ)
//    #define DEMUX_TTX_SZ		(20)
    //#define DEMUX_SUBTITLE_START		(DEMUX_PSI_POOL+DEMUX_PSI_POOL_SZ)
    //#define DEMUX_SUBTITLE_SZ		(20)
//    #define DMUX_BUFFER_POOL_SIZE	338//318+20
//#else     
//    #define DMUX_BUFFER_POOL_SIZE	318//256+32+30
//#endif
//DVB Old DB memory map//yuliang 05/05/02
//#define DVB_DATABASE_START (DMUX_BUFFER_POOL+DMUX_BUFFER_POOL_SIZE)
//#define DVB_DATABASE_SZ    (166) //166K for 256 transponders and 1000 programs support
//#endif //SUPPORT_8202_DVB

// JPEG/CDROM mode
#define JPEG_CODE_SIZE          8
#define CDROM_CODE_SIZE         ( 60 + 20 )             // 2004/02/17 yltseng

#ifdef SUPPORT_FONT_COMPRESSED                                  // 2004/09/19 yltseng, 2004/02/17 yltseng
    #define FS9660_SIZE         ( 104 - 20 )
#else
    #define FS9660_SIZE         ( 114 - 20 )
#endif

#ifdef SUPPORT_JPEG_MIC          //terry,2003/12/30 11:21AM
 #define JPEG_CDBUF_SIZE         (80-52)//190//200  //358,terry,2003/7/26 05:28PM
 #define A_MIC_DSP24YA           (4094-250)
 #define A_MIC_PCM_YA            (A_MIC_DSP24YA+DSP_SIZE)                  
#else
#define JPEG_CDBUF_SIZE         (16+50)//(180-52)//190//200  //358,terry,2003/7/26 05:28PM //joshua,04/7/22
#endif                                     //208=>200,jpeg decoder bug.

#define JPEG_FULLSCREEN_WORKING_BUF_YA  (GP_REF0_CHROMA+GP_CHROMA_SIZE)
#define JPEG_PREVIEW_WORKING_BUF_YA     (GP_REF0_LUMA + 844)

#define JPEG_FULLSCREEN_WORKING_BUF_SIZE    (400)
#define JPEG_PREVIEW_WORKING_BUF_SIZE       (400)

/*#define A_JPEG_SERVO_YA         A_SERVO_YA                              // MP3/JPEG servo work buffer start address
#define JPEG_CODE_YA            (A_JPEG_SERVO_YA+JPEG_SERVO_SIZE)       // 3422
#define CDROM_CODE_YA           (JPEG_CODE_YA+JPEG_CODE_SIZE)           // 3430
#define FS9660YA                (CDROM_CODE_YA+CDROM_CODE_SIZE)         // 3490
#define JPEG_YA                 (FS9660YA + FS9660_SIZE) */

#define A_JPEG_SERVO_YA         A_SERVO_YA                              // MP3/JPEG servo work buffer start address
#define	GP_REF1_LUMA	        (A_JPEG_SERVO_YA+JPEG_SERVO_SIZE)   
#define	GP_REF1_CHROMA          (GP_REF1_LUMA + GP_LUMA_SIZE) 
#define JPEG_CODE_YA            (GP_REF1_CHROMA+GP_CHROMA_SIZE)       // 3422
#define CDROM_CODE_YA           (JPEG_CODE_YA+JPEG_CODE_SIZE)           // 3430
#define FS9660YA                (CDROM_CODE_YA+CDROM_CODE_SIZE)         // 3490

#ifdef SUPPORT_FONT_COMPRESSED              // 2004/11/21 yltseng
    #define FONT_DECOMPRESS_SIZE    (10)
#else
    #define FONT_DECOMPRESS_SIZE    (0)
#endif
#define FONT_DECOMPRESS_YA      (FS9660YA + FS9660_SIZE)
#define JPEG_YA                 (FONT_DECOMPRESS_YA + FONT_DECOMPRESS_SIZE)

#define	GP_END		        (GP_REF1_CHROMA + GP_CHROMA_SIZE)
#define	GN_REF1_LUMA	        GP_REF1_LUMA
#define	GN_REF1_CHROMA          GP_REF1_CHROMA
#define	GN_END		        GP_END 

#define A_WMA_CODE_YA       (GP_REF1_LUMA)
#define WMA_CODE_SIZE       (10+40)          //terry,2005/5/20 01:49¤U¤È

#define A_MP4_CODE_YA       (A_WMA_CODE_YA + WMA_CODE_SIZE)
#define MP4_CODE_SIZE       (0)              //terry,2005/5/20 01:51¤U¤È

//----
// 6th
//----
#ifdef  SUPPORT_MIDI2
#define COMP_OSD_FONT           SEG4_END
#else
#define COMP_OSD_FONT           SEG5_END
#endif
#define OSD_FONT_SIZE           60
#define SEG6_END                (COMP_OSD_FONT+OSD_FONT_SIZE)

//free code size
//#ifdef LOAD_MANY_CODE_TO_64M_SDRAM    //kevinmonkey 051125 moved to 32M~64M section at the end of this file
//#define FREE_CODE_YA			4096
//#define FREE_CODESIZE			512
//#else
#define FREE_CODE_YA			SEG6_END
#define FREE_CODESIZE			92//82//72
//#endif	

//ycwen 2005/1/27 : MP3_JPEG_COWORK in 64MB //kevinmonkey 051125 moved to 32M~64M section at the end of this file
//#if defined(MP3_JPEG_COWORK)&&defined(SDRAM_64Mb_Mode)
//#define MP3_BUFFER_START                    (FREE_CODE_YA+FREE_CODESIZE)
//#define MP3_BUFFER_SIZE                     (3000)//0x2E9000  //3000-40
//#define POINTER_OFFSET                      500//500             //500
//#endif


#endif	// !SPHE1000

#ifdef SUPPORT_CD_TEXT
    #define CD_TEXT_YA          P_BIDIR_CHROMA
    #define CD_TEXT_SIZE        CHROMA_SIZE
#endif

//-------------------------------------
//avi segment
//-------------------------------------
// 2004/08/26 yltseng

// MP4 video buffer size
#define A_AVIEVBSZ              (235)

// MVC buffer
#define MVC_BUF_YA              (A_MP4_CODE_YA+MP4_CODE_SIZE)
#ifdef SUPPORT_HIGH_DEFINITION_VIDEO
#define MVC_BUF_SIZE            (37)
#else   //!SUPPORT_HIGH_DEFINITION_VIDEO
#define MVC_BUF_SIZE            (30)
#endif  //#ifdef SUPPORT_HIGH_DEFINITION_VIDEO

#define A_FILE_BUF_YA            (MVC_BUF_YA+MVC_BUF_SIZE)
#define A_FILE_BUF_SIZE          (GP_END-A_FILE_BUF_YA)

//--------------------------------------
// for fat file system write 
//--------------------------------------
#ifndef PMP_DVD//liweihua add 2004-12-10 
#define FAT_WRITE_TEMP_YA	    (P_BIDIR_LUMA)
#define FAT_WRITE_TEMP_SIZE     (1)
#define FAT_COPY_YA             (FAT_WRITE_TEMP_YA+FAT_WRITE_TEMP_SIZE) 
#define FAT_COPY_SIZE           (384)
#endif

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


//conditions of enlarge free code size
#if defined(LOAD_MANY_CODE_TO_64M_SDRAM)
#define ENLARGE_FREECODE_64Mb
#endif

    #ifdef ENLARGE_FREECODE_64Mb
#undef  FREE_CODE_YA
#undef  FREE_CODESIZE
#define FREE_CODE_YA			(4096)
#define FREE_CODESIZE           (512)
    #endif  //#ifdef ENLARGE_FREECODE_64Mb
#define FREE_CODE_END           (FREE_CODE_YA + FREE_CODESIZE)

//-----------------------------------------------------
// upper 32Mb~64Mb memory map starts from FREE_CODE_END
//-----------------------------------------------------
#if defined(MP3_JPEG_COWORK)&&defined(SDRAM_64Mb_Mode)
#define MP3_BUFFER_START                    (FREE_CODE_END)
#define MP3_BUFFER_SIZE                     (3000)//0x2E9000  //3000-40
#define POINTER_OFFSET                      500//500             //500
#endif  //(MP3_JPEG_COWORK)&&(SDRAM_64Mb_Mode)

#ifdef MINUS_VR_AUTH_PLAYBACK			//linrc 2006-3-29 11:33
#define TM_ENT_SA 			(SDRAM_BASE_UNCACHED+FREE_CODE_END*1024)//(SDRAM_BASE_CACHED+4002*1024)	//(15K 6 HOURs)
#define TM_ENT_BUF_SIZE			(15*1024)
#define VOBU_ENT_SA 		(TM_ENT_SA+TM_ENT_BUF_SIZE)//(SDRAM_BASE_CACHED+4017*1024)	//(127K 6 HOURs)
#define VOBU_ENT_BUF_SIZE		(127*1024)
#define M_C_EPI_SA 			(VOBU_ENT_SA+VOBU_ENT_BUF_SIZE)//(SDRAM_BASE_CACHED+4144*1024) //5994Bytes
#define M_C_EPI_BUF_SIZE	    (6*1024)
#define VR_ALLOC_DESC_SA    (M_C_EPI_SA+M_C_EPI_BUF_SIZE)
#define VR_ALLOC_DESC_BUF_SIZE  (1*1024)
#define VR_SDRAM_BUF_SIZE	((TM_ENT_BUF_SIZE+VOBU_ENT_BUF_SIZE+M_C_EPI_BUF_SIZE+VR_ALLOC_DESC_BUF_SIZE)/1024)
#endif


#if defined(SUPPORT_NERODIGITAL_64MB)||defined(SUPPORT_DIVX6_64Mb) 
#ifdef LOAD_MANY_CODE_TO_64M_SDRAM
#define MEDIA_FORMAT_BUF        (FREE_CODE_END)
#else 
#define MEDIA_FORMAT_BUF        (4096)
#endif

    #ifdef SUPPORT_DIVX6_64Mb
#define DIVX6_MEMORY_64Mb       (MEDIA_FORMAT_BUF)
//308"+52" is because divx6 now put DIVX6_SUP_BUFFER_SIZE which is 52k to JPEG_YA
//if we can move divx6 to 64Mb, this can be regroup back to divx6 buffer
#define DIVX6_MEMORY_SIZE_64Mb  (308 + 52) 
#define DIVX6_MEMORY_64Mb_END   (DIVX6_MEMORY_64Mb + DIVX6_MEMORY_SIZE_64Mb)
    #else   //!SUPPORT_DIVX6_64Mb
#define DIVX6_MEMORY_64Mb       (INVALID_POINTER)
#define DIVX6_MEMORY_SIZE_64Mb (0)
#define DIVX6_MEMORY_64Mb_END   (INVALID_POINTER)
    #endif  //#ifdef SUPPORT_DIVX6_64Mb

    #ifdef SUPPORT_NERODIGITAL_64MB
#define NERO_DIGITAL_MEMORY_YA             (MEDIA_FORMAT_BUF)
#define NERO_DIGITAL_MEMORY_SIZE           (3*1024)
#define NERO_DIGITAL_MEMORY_END            (NERO_DIGITAL_MEMORY_YA + NERO_DIGITAL_MEMORY_SIZE)
    #else   //!SUPPORT_NERODIGITAL_64MB
#define NERO_DIGITAL_MEMORY_YA     (MVC_BUF_YA + MVC_BUF_SIZE)
#define NERO_DIGITAL_MEMORY_SIZE   (A_FILE_BUF_SIZE)
#define NERO_DIGITAL_MEMORY_END    (NERO_DIGITAL_MEMORY_YA + NERO_DIGITAL_MEMORY_SIZE)
    #endif  //#ifdef SUPPORT_NERODIGITAL_64MB

    #if (DIVX6_MEMORY_SIZE_64Mb > NERO_DIGITAL_MEMORY_SIZE_64Mb)
#define MEDIA_FORMAT_BUF_SIZE   (DIVX6_MEMORY_SIZE_64Mb)
    #else //(DIVX6_MEMORY_SIZE_64Mb <= NERO_DIGITAL_MEMORY_SIZE_64Mb)
#define MEDIA_FORMAT_BUF_SIZE   (NERO_DIGITAL_MEMORY_SIZE_64Mb)
    #endif  //#if (DIVX6_MEMORY_SIZE_64Mb > NERO_DIGITAL_MEMORY_SIZE_64Mb)
#define MEDIA_FORMAT_BUF_END    (MEDIA_FORMAT_BUF + MEDIA_FORMAT_BUF_SIZE)
#endif //#if defined(SUPPORT_NERODIGITAL_64MB)||defined(SUPPORT_DIVX6_64Mb) 

