/*
*  Terry,2004/1/14 07:09PM
*  Terry,2004/4/1 05:36PM
*  Terry,2005/3/12 09:35¤U¤È
*/

//#define LINK_LIB_TEST

#ifdef LINK_LIB_TEST
#define TEST_LIB   -ltest
#define BIT_LIB    -lbits
#endif

#ifdef SUPORT_TFT_TCON//shenyj add 2006-9-12 04:44ÏÂÎç
#define TFT_TCON_LIB -ltft
#endif

#if defined(SPHE8202)&&defined(SDRAM_16Mb_Mode)
//8202......................................8202.................................
//---------------------------------8202 16M
#define PE_LIB     -lpe_16
#define OSD_LIB    -losd_16
#define SYS_LIB    -lsys_16
#define NAV_LIB    -lnav_16
#define FS_LIB     -lfs_16
#define FS_KRNL_LIB -lfs_krnl_16
#define FS_PMP_LIB  -lfs_pmp_16
#define FS_MIDI_LIB -lfs_midi_16
#define FS_MIDI_CUST_LIB -lfs_midi_cust     //ouyang add 2005.07.04
#define DRM_LIB     -ldrm_8202
#define JPEG_LIB   -ljpeg_16
#define MJPEG_LIB  -lmjpeg_8202
#define AUTH_LIB   -lauth_16
#define VCD_LIB    -lvcd_16
#define FS_MP4_LIB  -lfs_mp4_16

#ifdef TURBO_DECODE
    #if defined(IC_8202D)
		#define KERN_LIB   -lkern_tb
		#define MP4_LIB    -lmp4_tb
        #define DISP_LIB   -ldisp_tb
    #elif defined(IC_8202L)
		#define KERN_LIB   -lkern_8202L_tb
		#define MP4_LIB    -lmp4_8202L_tb    
        #define DISP_LIB   -ldisp_8202L_tb
    #else
		#error "Turbo decode is not supported on 8202A/S"
    #endif
#else
    #if defined(IC_8202L)
		#define KERN_LIB   -lkern_8202L
		#define MP4_LIB    -lmp4_8202L
        #define DISP_LIB   -ldisp_8202L
    #else
		#define KERN_LIB   -lkern_8202
		#define MP4_LIB    -lmp4_8202
        #define DISP_LIB   -ldisp_8202
    #endif
#endif

#define BOOT_LIB   -lboot_8202
#define GAME_LIB   -lgame_8202
#define GAME16_LIB -lgame16_8202
#define TASK_LIB   -ltask_8202
#define IR_LIB     -lir_8202
#define ATA_LIB    -latapi_8202
#define ENC_LIB    -lenc_8202
#define AUDDRV_LIB -lauddrv_16 //**** Audio Driver library  2004.12.28 oliver ****//
//---------------------------------8202 16M ending
#elif defined(SPHE8202)
#define PE_LIB     -lpe_8202
#define OSD_LIB    -losd_8202
#define SYS_LIB    -lsys_8202
#define NAV_LIB    -lnav_8202
#define FS_LIB     -lfs_8202
#define FS_KRNL_LIB     -lfs_krnl_8202
#define FS_PMP_LIB      -lfs_pmp_8202
#define FS_MIDI_LIB     -lfs_midi_8202
#define FS_MIDI_CUST_LIB -lfs_midi_cust   //ouyang add 2005.07.04
#define FS_MP4_LIB     -lfs_mp4_8202
#define FS_SMF_LIB     -lfs_SMF_8202
#define DRM_LIB     -ldrm_8202
#define JPEG_LIB   -ljpeg_8202
#define MJPEG_LIB  -lmjpeg_8202
#define AUTH_LIB   -lauth_8202
#define VCD_LIB    -lvcd_8202

    #if defined(IC_8202L)
        #define KERN_LIB   -lkern_8202L
        #define MP4_LIB    -lmp4_8202L
        #define DISP_LIB   -ldisp_8202L
    #else
        #define KERN_LIB   -lkern_8202
        #define MP4_LIB    -lmp4_8202
        #define DISP_LIB   -ldisp_8202
    #endif
    
#define BOOT_LIB   -lboot_8202
#define GAME_LIB   -lgame_8202
//#define GAME16_LIB   -lgame16_8202
#define TASK_LIB   -ltask_8202
#define IR_LIB     -lir_8202
#define ATA_LIB    -latapi_8202
#define ENC_LIB    -lenc_8202
#define AUDDRV_LIB -lauddrv //**** Audio Driver library  2004.12.28 oliver ****//
//8202......................................8202 ending.................................
#elif defined(SPHE1000)
//1000......................................1000.................................
#define PE_LIB     -lpe_1000
#define OSD_LIB    -losd_1000
#define SYS_LIB    -lsys_1000
#define NAV_LIB    -lnav_1000
#define FS_LIB     -lfs_1000
#define FS_KRNL_LIB     -lfs_krnl_1000
#define FS_MIDI_LIB     -lfs_midi_1000
#define FS_MP4_LIB     -lfs_mp4_1000
#define DRM_LIB    -ldrm_1000
#define JPEG_LIB   -ljpeg_1000
#define MJPEG_LIB  -lmjpeg_1000
#define AUTH_LIB   -lauth_1000
#define VCD_LIB    -lvcd_1000
#define KERN_LIB   -lkern_1000
#define BOOT_LIB   -lboot_1000
#define GAME_LIB   -lgame_1000
#define GAME16_LIB   -lgame16_1000
#define TASK_LIB   -ltask_1000
#define IR_LIB     -lir_1000
#define ATA_LIB    -latapi_1000
#define ENC_LIB    -lenc_1000
#define MP4_LIB    -lmp4_1000
#define AUDDRV_LIB -lauddrv //**** Audio Driver library  2004.12.28 oliver ****//
//1000......................................1000 ending.................................
#elif defined(SDRAM_16Mb_Mode)
//8200......................................8200.................................
//---------------------------------8200 16M
#define PE_LIB     -lpe_16
#define OSD_LIB    -losd_16
#define SYS_LIB    -lsys_16
#define NAV_LIB    -lnav_16
#define FS_LIB     -lfs_16
#define FS_KRNL_LIB     -lfs_krnl_16
#define FS_MIDI_LIB     -lfs_midi_16
#define FS_MIDI_CUST_LIB -lfs_midi_cust    //ouyang add 2005.07.04
#define FS_MP4_LIB     -lfs_mp4_16
#define JPEG_LIB   -ljpeg_16
#define AUTH_LIB   -lauth_16
#define VCD_LIB    -lvcd_16
#define KERN_LIB   -lkern
#define BOOT_LIB   -lboot
#define GAME_LIB   -lgame
#define TASK_LIB   -ltask
#define IR_LIB     -lir
#define ATA_LIB    -latapi
#define ENC_LIB    -lenc
#define MP4_LIB    -lkern
#define AUDDRV_LIB -lauddrv_16 //**** Audio Driver library  2004.12.28 oliver ****//
//---------------------------------8200 16M ending
#else
//---------------------------------8200 32M
#define PE_LIB     -lpe
#define OSD_LIB    -losd
#define SYS_LIB    -lsys
#define NAV_LIB    -lnav
#define FS_LIB     -lfs
#define FS_KRNL_LIB     -lfs_krnl
#define FS_MIDI_LIB     -lfs_midi
#define FS_MIDI_CUST_LIB -lfs_midi_cust    //ouyang add 2005.07.04
#define FS_MP4_LIB     -lfs_mp4
#define JPEG_LIB   -ljpeg
#define AUTH_LIB   -lauth
#define VCD_LIB    -lvcd
#define KERN_LIB   -lkern
#define BOOT_LIB   -lboot
#define GAME_LIB   -lgame
#define TASK_LIB   -ltask
#define IR_LIB     -lir
#define ATA_LIB    -latapi
#define ENC_LIB    -lenc
#define MP4_LIB    -lkern
#define AUDDRV_LIB -lauddrv //**** Audio Driver library  2004.12.28 oliver ****//
//---------------------------------8200 32M ending
//8200.....................................8200 ending...........................
#endif

// DSP code related library                 // 2004/12/21 yltseng
#define DSP_LIB         -ldsp3
#define DSPAAC_LIB      -ldsp3_aac
#define DSPPPCM_LIB     -ldsp3_ppcm
//#define DSPWMA_LIB      -ldsp3_wma//nono mark it.5-12-5 3:18
#define DSPDTS_LIB      -ldsp3_dts
// **************************************************************************************** //

#define CSS_LIB         -lcss

#ifdef TWO_SUBTITLE//terry,2004/8/4 02:37PM
#undef  KERN_LIB
#define KERN_LIB   -lkern_2st
#endif

#ifdef SUPPORT_DVB //barry,2005/7/19 05:08PM
#undef  KERN_LIB
#define KERN_LIB   -lkern_dvb

#undef  MP4_LIB
#define MP4_LIB   -lmp4_dvb

#undef  DISP_LIB
#define DISP_LIB  -ldisp_dvb
#endif

#ifdef SUPORT_TFT_TCON
INPUT(TFT_TCON_LIB)//shenyj add 
#endif
INPUT(IR_LIB)
INPUT(NAV_LIB)
INPUT(ATA_LIB)
INPUT(TASK_LIB)
INPUT(ENC_LIB)

#ifdef SUPPORT_HD_DVD
#ifdef Simplay_warning	//eric lin,2006-07-06,for Simplay format warning message
INPUT(-lscaler)
#endif	//#ifdef Simplay_warning
#endif

INPUT(OSD_LIB)
INPUT(SYS_LIB)
#ifdef DVD_SERVO
#ifdef USER_SUPER_SA_LOADER
  #include "srv_lib_std.h"
#else
  #ifdef SPHE8202
  	#ifdef IC_8202L
	#include "srv_lib_8202L.h"
	#else
    #include "srv_lib_8202.h"
	#endif
  #else
    #include "srv_lib.h"
  #endif
#endif
#endif

//INPUT(SYS_LIB)
#ifdef LINK_LIB_TEST
INPUT(TEST_LIB)
INPUT(BIT_LIB)
#endif

//INPUT(FS_LIB)             // 2005/02/24 yltseng

#ifdef SUPPORT_MP4
INPUT(FS_MP4_LIB)
#endif

INPUT(FS_KRNL_LIB)
#ifdef PMP_DVD
INPUT(FS_PMP_LIB)
#endif
INPUT(FS_LIB)//nono 4-9-4 0:26

#ifdef SUPPORT_PLAY_SWD
INPUT(-lmem)
#endif

#ifdef SUPPORT_MIDI
INPUT(FS_MIDI_LIB)
INPUT(FS_MIDI_CUST_LIB)     //ouyang add 2005.07.04
INPUT(OSD_LIB)
#endif

#ifdef DIVX_DRM
INPUT(DRM_LIB)
#endif

#ifdef SUPPORT_UNICODE_FONT//Joshua 2005/9/2
    INPUT(-lfont_uni)
#else
    #ifdef SUPPORT_FONT_UTIL
        INPUT(-lfont)
    #endif
#endif

INPUT(JPEG_LIB)
INPUT(SYS_LIB)//nono add. 4-7-15 0:57 for jpegeffect_help.c is moved to "system". 

INPUT(AUTH_LIB)

INPUT(CSS_LIB)

#if defined(SUPPORT_MP4) || defined(SUPPORT_WMA) || defined(SUPPORT_AUD_WMA)
INPUT(-lparser)
#endif

#ifdef SUPPORT_MP4
INPUT(MP4_LIB)
#endif

//GROUP( KERN_LIB PE_LIB )        // 2005/02/24 yltseng
GROUP( KERN_LIB PE_LIB DISP_LIB)  // 2006 0421 swpong

#ifdef BOOT_LOAD_CODE
INPUT(NAV_LIB)
#endif
#ifdef SUPPORT_MJPEG
INPUT(MJPEG_LIB)
#endif

INPUT(GAME_LIB)

#ifdef SUPPORT_SPG_GAME
//INPUT(GAME16_LIB)
INPUT(-lGraphDrv)
#endif

#ifdef SUPPORT_SMF
INPUT(FS_SMF_LIB)
#endif

INPUT(VCD_LIB)
INPUT(BOOT_LIB)

//INPUT(-lfonts)    // 2004/09/11 yltseng
INPUT(-lhigui)


#ifdef SUPPORT_DVD_NATIVE_GAME	//linrc for NATIVE_GAME 2005-10-18 14:51
INPUT(-ldvdgame)
#endif  

#ifdef SUPPORT_RECEIVER
INPUT(-lreceiver)
#endif

#ifdef SUPPORT_HD_DVD
#ifndef Simplay_warning	//eric lin,2006-07-06,for Simplay format warning message
INPUT(-lscaler)
#endif	//#ifdef Simplay_warning
#endif

INPUT(AUDDRV_LIB)           // 2004.12.28 oliver : the order is significant. It should be placed before DSP.

#if 0//defined(SUPPORT_WMA) || defined(SUPPORT_AUD_WMA)//nono mark 20051205
INPUT(DSPWMA_LIB)
#endif

#ifndef NO_DTS_OUTPUT
INPUT(DSPDTS_LIB)
#endif

#ifdef DVD_AUDIO            // 2004/10/13 yltseng
INPUT(DSPPPCM_LIB)
#endif

#ifdef SUPPORT_AAC          // 2004/10/13 yltseng
INPUT(DSPAAC_LIB)
#endif

INPUT(DSP_LIB)

#ifdef SUPPORT_TVG          // 2005/03/29 yltseng
INPUT(TVG/libtvg.a)
    #ifdef SUPPORT_TVG_ACTIVATION
INPUT(TVG/libiact.a)
    #endif
#endif

#ifdef DVB_DVD_8202 //wthsin ,2005/3/21 11:04
#ifdef SUPPORT_DVB_GUI_NEW //David 2005-7-15 19:20
INPUT(-ldvb_menu_std)
#ifdef SUPPORT_DVB_NATIVE_GAME
INPUT(-ldvbgame)
#endif //SUPPORT_DVB_NATIVE_GAME
#endif
INPUT(-ldvb_func)
#ifdef SUPPORT_TELETEXT	//tcf 2005-10-25 17:38
INPUT(-lttx)
#endif //end #ifdef SUPPORT_TELETEXT
#ifdef SUPPORT_NEWDB
INPUT(-ldvbdb)  
#endif   

#include "dvb_tuner_lib.h"//xiaopeng 2005/06/17

INPUT(-ldemux) 
INPUT(AUTH_LIB)
#endif //#ifdef DVB_DVD_8202

#ifdef MAKE_TFT_DRIVER_LIB
INPUT(-ltft_lcd)
#endif

/* basic libraries */
INPUT(-lstd)
INPUT(-lm)
#ifdef DVB_DVD_8202 //wthsin,2005/11/24 04:49pm
INPUT(-lc)
#endif
INPUT(-lgcc)


