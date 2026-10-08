//==================================================================================
// include header file
//==================================================================================
#include "config.h"
#include "regmap.h"
#include "global.h"
#include "macro.h"
#include "func.h"
#include "util.h"
#include "stdlib.h"    //huo 2000.12.14
#include "cdfunc.h"
#include "cfont.h"
#include "sio.h"
#include "vfdfunc.h"
#include "ringbuf.h"
#include "ircmd.h"
#include "ircode.h"
#include "cd.h"
#include "auctrl.h"
#include "user_init.h"  //terry,2001/1/9 03:29PM

#include "avd.h"
#include "dvdpe.h"

#include "fs96602.h"
#include "osd.h"
#include "framebuf.h"
#include "cderr.h"
//#include "dsa.h"
//#include "drammap.h"  /*jhuang 2001/3/26*/
#include "vpp.h"
#include "user_if.h"
#include "dsp3_if.h"
#include "atapi_if.h"
#include "dma.h" //Jeff 20010919
#include "auddrv.h" //2004AUDDRV oliver 20041004 for using audio driver purpose
//#include "audif.h"
#include "setup.h"
#include "fsGUI.h"
#include "tvif.h"
#include "drv.h"
//#include "auddac.h"
#include "fsNAV.h"
#include "iop.h"//2-7-9 9:40
#include "UartTxd.h"
#include "kernel.h"

#ifdef TUNER_T988
#include "radio_t988.h"  //jinping 2-6-20 14:04
#elif defined(TUNER_MV114)
#include "radio_mv114.h"  //jinping 2002-7-1 20:30
#endif

#if defined(PT2322)||defined(PT2320)
#include "audctrl.h"
#endif

#if defined(TAS3001_AMP)   //use TI 3001 amplifier  jason ych add 2-8-9 10:10
#include "ti3001.h"
#endif

#if defined(TAS5026_AMP)   //use TI 3001 amplifier  jason ych add 2-8-9 10:10
#include "ti5026.h"
#endif

#ifdef SUPPORT_CDG  //Jeff 20020824
#include "cdg.h"
#endif

//==================================================================================
// function decalre
//==================================================================================
extern void init_vfd_clear(void);
extern void system_sleep();

extern UINT8 DVD_show_time(void);   //Jeff 20010717
extern void DVD_get_time(int);
extern UINT8 DVD_check_state(void);
extern void setup_SetTV_format(UINT8);//terry,2004/2/5 12:05PM
extern UINT8 ExeHLBm(UINT8 mode,int val);
extern void ExitSetupPage(BYTE save);
#ifdef OSD_BMP_SOUND
extern void EQ_bmp_init(void);
#else
extern void EQ_init(void);
#endif

extern BYTE FSIsZoomOK(); //Jeff 20010822
extern UINT16 Is_JPEG_STATE(void);
extern UINT16 Is_MP3_STATE(void);
extern UINT16 Is_JPEG_SlideMode(void);
extern UINT16 mp3_file_count(void);

#ifdef SUPPORT_NESGAME
extern UINT16 Is_GAME_STATE(void);
#endif

//extern void get_zoom_center(UINT16 *x,UINT16 *y); //Jeff 20010830
//extern void    resync_audio(void);
//extern void osd_restore();
extern void osd_init_setup(void);

extern void DispFadeIn();
extern void DispFadeOut();
extern void DispCookOSD0(BYTE bChange);
extern void DispPolling(BYTE bReset);
extern void init_setup(void);
#ifdef DISP_REGION_BOTTOM
extern  UINT8 OSD_ShowBottomDisp(void);
#endif


extern void reset_sup(void);
extern void tv_sleep();
extern void tv_resume();
extern void setup_tv_format(int fmt);

extern int is_menu(void);

//in sysmain2.c
extern void ShowTitle();

extern int is_dvd_prohibit_key(void);

extern void vfd_set_showtime(void);
#ifdef SUPPORT_FILE_SYSTEM_MODE
#include "fsNAV.h"
extern UINT16 Is_OTHER_STATE(void);
extern UINT16 IsOtherStatePlayMode(void);
#endif

/*wanghaoying marked 2004-7-1 14:27, for not use any more
#ifdef IR17
UINT16 vfd_set_front(UINT16 index);
UINT16 vfd_set_center(UINT16 index);
UINT16 vfd_set_rear(UINT16 index);
UINT16 vfd_set_woofer(UINT16 index);
UINT16 vfd_set_treble(UINT16 index);
UINT16 vfd_set_middle(UINT16 index);
UINT16 vfd_set_base(UINT16 index);
UINT16 vfd_set_volume(UINT16 index);
#endif
*/

#ifdef TEST_VFD                             //shawn add at 910131
extern void update_vfd_mod_dec(void);
extern void update_vfd_mod_inc(void);
extern void update_vfd_dot_dec(void);
extern void update_vfd_dot_inc(void);
extern void update_vfd_dec(void);
extern void update_vfd_inc(void);
#endif
void ircmd_play_resume_pause(void);

//static BYTE echo_flag; //kenny 891107  /*jhuang 2000/11/27 reduce warning*/
void ir_num_select(int x);

void Mp3_ChkSkipData(void);
//void seek_continue(void);
//void DrawRmTime(void);
//void DrawTime(BYTE mm,BYTE ss);
//void DrawTrk(UINT16 trk,UINT16 tt);
void show_dvd_err(void);
void run_pause(int show);
void set_video_aspect(void);


#ifdef OURMIND_VFDPORT_TO_BUTTON
extern void check_ourmind_light_status(void);
#endif
extern void setVPP_DoItNow(void);
extern void cancel_rep(void);
extern void Score_Init();
extern void Score_Exit();
extern void setup_MIC(BYTE set);

#ifdef AUDIO_SHOW_SAVER
extern BYTE  bDisableGUI;
#endif

#ifdef POWER_RESUME
void RsmInfo2Flash(int clr);
#endif

extern UINT16 Is_JPEG_PLAY_STATE(void);

#ifdef SUPPORT_TUNER
void tuner_mute(BYTE mute);
#endif

void close_tray_init(void);

#ifdef SUPPORT_FUNCTION_MENU
void init_setup_plus(void);
#endif //end #ifdef SUPPORT_FUNCTION_MENU

//==================================================================================
// define decalre
//==================================================================================
#define FAST2NORM    0x01<<0
#define PAUSE2NORM   0x01<<1
#define SLOW2NORM    0x01<<2

#define DEMUTE       2
#define REALPLAY     1
#define TRANSFER     0

#define CD_TRK_CHANGED          1
#define CD_MM_CHANGED           2
#define CD_SS_CHANGED           3

#define C_SHOW  0x01
#define C_PLAY  0x02
#define C_ZOOM  0x04
#define ZOOM_MOVE   16

#define KEY_UP_MAX  6
#define KEY_DN_MAX  -6

#define MASK        0x57

//==================================================================================
// variable decalre
//==================================================================================
extern UINT32 dAMG_LSN;
extern BYTE book_flag;
extern BYTE avstatus;

extern UINT32 coding_mode_now;


extern UINT16 smp_rate_now;
extern UINT8   bReadSubChannel;
extern UINT16  iBlockLen;
extern UINT8 sound_sel[];
extern BYTE bSleepFlag; // keep standby mode flag

BYTE    audioNotContinuous=0; //>0:audio is not continuous, especially when we change audio language
UINT32  myTime=0; //Jeff 20020902
UINT32  oldmp3ReadLen=0; //Jeff 20020917
BYTE rem_osd_id;//show "PAUSE" & "STEP"...after "setup" 2-7-15 21:44
#ifdef MUSTEK_ESS_DVD //shawn 0227
int display_and_time=0;
#endif
#ifdef REMAIN_TIME//nono 2-7-13 11:27
BYTE polling_clock;//nono 20020713
#endif
//#ifdef MUSTEK_ESS_DVD //shawn 0227
#if defined(MUSTEK_FUSS_DVD)
int display_and_time=0;
#endif
//#ifdef SVA_SAMPLE//freyman add 2002-9-20 18:00 and marked 2004-3-23 16:03
//BYTE display_flag = 0;
//#endif

#ifdef VOCAL_CANCEL
   #ifdef ORITRON_HK_DVD
    const int id_ary[MAX_CH_NUM+1]={STR_OS_OLD_STEREO,STR_OS_LEFT,STR_OS_RIGHT,STR_OS_AUTO_L,STR_OS_AUTO_R};
   #else
    const int id_ary[MAX_CH_NUM+1]={STR_OS_STEREO,STR_OS_CHL,STR_OS_CHR,STR_OS_AUTO_L,STR_OS_AUTO_R};
   #endif
#else
   #ifdef ORITRON_HK_DVD
    const int id_ary[MAX_CH_NUM+1]={STR_OS_OLD_STEREO,STR_OS_LEFT,STR_OS_RIGHT};
   #else
#ifdef SUPPORT_MIX_MONO		// diya 2006/8/3 05:44¤U¤È
    const int id_ary[MAX_CH_NUM+1]={STR_OS_STEREO,STR_OS_CHL,STR_OS_CHR,STR_OS_MIX_MONO_SETUP};
#else
    const int id_ary[MAX_CH_NUM+1]={STR_OS_STEREO,STR_OS_CHL,STR_OS_CHR};    
#endif
   #endif
#endif
UINT32  SeedSeed = 0xbadface;

#ifdef MIC_FUNCTION_KEY
BYTE bFuncStep = 0;
#endif

