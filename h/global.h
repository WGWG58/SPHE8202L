//=============================================================================
// FILE
// global.h
// Creat by potatooo
// Maintain by terry , 2002
// History
// 2003.3.20  terry spilt global.h to
//                  a.define struct
//                  b.global define
//                  c.kernel global var.
//                  d.navigation global var.
//                  e.io var.
//                  f.Aviq system designer
//
//==============================================================================
#ifndef __GLOBAL_H
#define __GLOBAL_H

#include "bufloc.h"
#include "config.h"
#include "user_init.h"
#include "types.h"
#include "regmap.h"
#include "func.h"

#include "gb_def.h"
#include "gb_struct.h"
#include "gb_knl.h"
#include "gb_nav.h"
#include "gb_io.h"
#include "gb_aviq.h"

/*
*  System global var.
*/
//=============================================================== system state
#ifdef IR_TOOL
int watch_ir_value;
int watch_ir_id_value;
UINT16 IRAddr;
#endif

#ifdef OP_STOP_PANEL_DISPLAY//lijd 2005-6-30 11:32
EXTERN  BYTE  StopTimes;
#endif 

#if defined( SUPPORT_STOP_PLAY_READ_USB_CARD)||defined(SUPPORT_OPEN_READ_USB_CARD) //caoh 2005-8-31 9:54 
EXTERN  BYTE  media_change_flag;
EXTERN  BYTE  media_change_flag_mark;
#endif
#ifdef OP_CD_CDG_CHANGE //caoh 2005-9-19 10:37
EXTERN BYTE op_cd_cdg_flag;//caoh 2005-9-19 10:32
#endif

#ifdef JPEG_MP4_FRIST_STOP_TO_GUI//caoh 2005-6-16 15:29   
EXTERN  BYTE  mp4_to_logo; 
#endif
#ifdef VFD_SHOW_MP3_TRACK  //qinhua add ,2005-9-21 22:54 //move from fs_nav_mp3.c
EXTERN  BYTE mp3_read_time; 
#endif 


#ifdef OP_GPIO54_CHECK_MIC_ON_OFF 
EXTERN  BYTE  Micflag;
#endif
#ifdef TEST_VFD_PANNEL_AND_KEY//lijd 2005-5-8 14:06
EXTERN  BYTE    Test_Front_Panel_flag;
#endif
#ifdef ORITRON_TRAY_PASSWORD//libing 2005-4-25 14:19
EXTERN  BYTE    tray_flag;
EXTERN  BYTE    tray_psd_exit_flag;
#endif
#ifdef ORITRON_PARENTAL_PASSWORD//libing 2005-4-25 14:19
EXTERN  BYTE    op_parent_pwd_flag;
#endif
#ifdef SWITCH_SUB_DIRECTION//libing 2005-7-15 14:43
EXTERN  int   subtitle_ratate_flag;
#endif
EXTERN  BYTE    pe_run;
EXTERN  BYTE    system_state;
EXTERN  ifunc   browser;
EXTERN  BYTE    play_state;
EXTERN  BYTE    old_play_state;
EXTERN  UINT16  sys_cmd;
EXTERN  BYTE    source_end;
EXTERN  BYTE    program_end;
EXTERN  BYTE    show_logo;
EXTERN  BYTE    bInitPlayTrk;
EXTERN  UINT8   no_disk_cnt;
EXTERN  int     monflg;
//================================================================ function pointer
//
// srv_kernel   : top level server
// do_cd    : cd-format parser
// do_system    : system-level parser
// do_video : video elementary parser
// do_audio : audio parser
// do_sup   : ogt/sup parser
//
EXTERN  ifunc   srv_kernel;
EXTERN  ifunc   do_cd;
EXTERN  ifunc   do_system;
EXTERN  ifunc   do_system_init;
EXTERN  ifunc	do_system_init_bak;
EXTERN  ifunc   do_video;
EXTERN  ifunc   do_video_init;
EXTERN  ifunc   do_audio;
#ifdef PARENT_PWD_DEFAULT_NULL
EXTERN  int   yu;//libing 
#endif

#ifdef  AVI_INTERNAL_SUP
EXTERN  ifunc   do_avi_sup;
#endif

EXTERN INT64	audio_fPTS;
EXTERN INT64	video_fPTS;
//Flash related global variables
EXTERN  BYTE    is_spi_flash;

/*
*  Application global var.
*/
//================================================================ SDRAM 16Mb
#ifdef SDRAM_16Mb_Mode
EXTERN  BYTE    prog_state;
#endif
#ifdef NEW_STYLE_SETUP
EXTERN  BYTE    setup_state;
#endif
//================================================================ IDE
#ifdef USE_HDD
EXTERN  char    hd_play;
#endif
EXTERN  BYTE    read_error_flag;
EXTERN  BYTE    dev_status_flag;
#ifdef BAD_DISC_AUTO_STOP //terry,2003/8/31 12:00AM
EXTERN  BYTE    bad_disc_auto_stop;
#endif
//#ifdef SUPPORT_SPG_GAME//nono add 20041228 //axel mark 20041230
EXTERN  int     spg_game_pad;
//#endif
//================================================================ USB Reader
//================================================================ Graph
EXTERN  UINT16  line_offset;

#ifdef SPHE1000
EXTERN  BYTE    media_type;
#endif
//================================================================ Card Reader
#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
#ifndef SPHE1000
EXTERN  BYTE    media_type;
#endif
EXTERN  BYTE    card_plug_state;
EXTERN  BYTE    storage_type; //1:exist 0:Not exist
                              //Bit0:USB Bit1:CF Bit2:SD_MMC Bit3:MS Bit4:SMC
EXTERN  BYTE    detect_type;  //liweihua 2004-6-7 16:52
                              //use to set flag for all pluged media types

#ifdef DIRECT_ACCESS_MEDIA//added by wangwei,2005-11-16 9:46
EXTERN  BYTE    media_status;
EXTERN  int     hl_item;
EXTERN  int     last_hl_item;
#endif//DIRECT_ACCESS_MEDIA
#endif
//================================================================ flash
EXTERN  UINT32  system_flash_id;
//================================================================ resume
//#ifdef POWER_RESUME   //maoyong marked 2004.02.20 22:12
EXTERN  UINT16  resume_fsnav_trk; // for receiving resume data
EXTERN  UINT16  resume_fsnav_dir;
EXTERN  UINT16  same_disc_flag;
EXTERN  UINT32  same_disc_vob11_pos;    //store "VTS_01_1.VOB" positon
//#endif
#if defined(IR_PLAY_RESUME) && defined(POWER_RESUME)
EXTERN  BYTE    power_resumeflag;
#endif
//kevinmonkey sz 050614, since fs_nav_trk_now may exceeds 256, UINT32 is required.
//fs_nav_trk_now depends on the number of files in a folder.
EXTERN  UINT32  resumeTRK;
EXTERN  UINT32  resumeMSF;

#ifdef FS_FILE_POWER_RESUME //qinhua,2006-6-16 01:49ÏÂÎç
EXTERN  BYTE		 resume_clear  ;// 0-> have cleared ,1-> have saveed 
EXTERN 	UINT32   Resume_Track_msf;
EXTERN 	BYTE 	 Resume_func_btn;
#endif

//================================================================ UI
EXTERN  INT8    counter_down;
EXTERN  BYTE    shuffle_track;
EXTERN  BYTE    shuffle_flag;
EXTERN  INT8    video_slow;
EXTERN  INT16   adv_search_time, play_dir;
EXTERN  BYTE    rep_run_this_menu;
EXTERN  int     nOldFst;    //Maoyong 2004.05.25 move from lbaif.c
EXTERN  int     nOldFst_orig;//Steven 2006/09/19 add to save the F.B/F.F condition
#if ALL==BIT16MODE
EXTERN  UINT16    full_scrn;
#else
EXTERN  BYTE    full_scrn;
#endif

EXTERN  BYTE    bIntro;

#ifdef NEXT_FORWARD_IN_A_KEY
EXTERN  BYTE    bIrSkipState;
EXTERN  BYTE    bIrSkipCnt;
#endif
#ifdef ANGLE_GOTO_IN_A_KEY  // add by Tom eastech
EXTERN  BYTE    bIrSkipState1;
EXTERN  BYTE    bIrSkipCnt1;
#endif

#ifdef SLOW_ZOOM_IN_A_KEY
EXTERN  BYTE    bIrSkipState2;
EXTERN  BYTE    bIrSkipCnt2;
#endif

//================================================================ Repeat
EXTERN  BYTE    rep_mode;
EXTERN  BYTE    rep_ab_mode;
EXTERN  BYTE    rep_track;
EXTERN  UINT32  repStart;
EXTERN  UINT32  repEnd;
#ifdef MINUS_VR_AUTH_PLAYBACK
EXTERN  UINT32  repStartVOBU;
#endif
//================================================================ Display
EXTERN  BYTE    remain;
EXTERN  INT16   t_disp;
EXTERN  INT16   old_t_disp;
EXTERN  INT16   disp_mode;
EXTERN  INT16   index_x;
EXTERN  BYTE    index_y;
EXTERN  BYTE    show_time_hh;
EXTERN  BYTE    show_time_mm;
EXTERN  BYTE    show_time_ss;
EXTERN  UINT32  disc_time;
EXTERN  UINT32  disc_st_time;
EXTERN  int     disp_time;
EXTERN  int     old_disp_time;
EXTERN  int     fore_disp_time;
EXTERN  UINT32  dNx_pg_tm;
EXTERN  UINT32  dPg_tm;
EXTERN  INT16   dvd_chapter;
EXTERN  INT16   dvd_title;
#ifdef  JUST_SHOW_CD_TYPE       //Maoyong 2004.02.25
EXTERN  int     track_play_diff_time;
#endif
//================================================================  time search
EXTERN  BYTE    goto_active;
EXTERN  UINT32  goto_time;
EXTERN  BYTE    goto_hour;
EXTERN  BYTE    goto_min;
EXTERN  BYTE    goto_sec;
//================================================================  book
#ifdef  SUPPORT_BOOK
EXTERN  BYTE    book[BOOK_MAX_ITEM][BOOK_MAX_RECORD];//vcd: track //dvd: title,chapter
EXTERN  UINT32  book_tm[BOOK_MAX_ITEM];
#endif
//================================================================  setup
t_USER_SET UserSet;
//================================================================  program
EXTERN  BYTE    digit_cnt;
EXTERN  BYTE    prog_cnt;
EXTERN  BYTE    mark_cnt;
EXTERN  BYTE    prog_index;
EXTERN  UINT16  prog[SHOW_PROG_NO+1][2];

#ifdef NEWSTYLE_WINDOW
//================================================================  new stytle window func
EXTERN  BYTE    info_index;
EXTERN  BYTE    HL_index;
//EXTERN  BYTE    bBrowse_state;
#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW//zhaoyanhua add 2003-12-18 16:51
EXTERN  BYTE    show_window_info;
#endif
//maoyong add OR condition for NINTAUS HDCD/CD division VFD display 2004.02.23
#if defined (DISP_TIME_NOT_CHANGE_WINDOW_PROGESS) || defined(JUST_SHOW_CD_TYPE)//zhaoyanhua add 2004-2-5 13:58
EXTERN  int     track_play_time;//time track has played.
#endif//DISP_TIME_NOT_CHANGE_WINDOW_PROGESS
//================================================================ Zoom in/out
#endif

//================================================================ Zoom in/out
EXTERN  UINT8   vpp_zoom;
EXTERN  UINT8   vpp_zoom_max;
EXTERN  UINT8   vpp_zoom_offset_mode;
EXTERN  INT16   vpp_zoom_x;
EXTERN  INT16   vpp_zoom_y;
//================================================================ 3d sound
#ifdef SUPPORT_3DSOUND
EXTERN  BYTE    bEqEnergyMax[13];    //jackie
EXTERN  UINT32  unEqMaxRef;          //jackie
#endif
EXTERN  BYTE    bEqDisplay;          //jackie
//================================================================ IR
EXTERN  UINT8   old_key;
EXTERN  UINT8   action_click;
EXTERN  int     ir_select_number;
EXTERN  int     mp3_user_select;
EXTERN  INT8    now_num_ns;
EXTERN  UINT8   keep_cmd_code;
EXTERN  INT16   ir_10p;
EXTERN  UINT32  (*ircmd_callback_check)(UINT32);
//================================================================ Audio
EXTERN  UINT8   audio_chan_num;
EXTERN  BYTE    user_mute;
EXTERN  BYTE    audio_only;
#ifdef SUPPORT_ASF //add by Roger 06-04-18 for support asf video only file				
EXTERN  BYTE    video_only;
#endif
EXTERN  BYTE    audio_volume;

#ifdef CNTR_5SPK_VOLUME
//EXTERN  BYTE    volume_5SPK[6];
//EXTERN  BYTE    idVolume_5SPK[6];
EXTERN  BYTE    volume_5SPK[7];
EXTERN  BYTE    idVolume_5SPK[7];
EXTERN  BYTE    volume_Switch;
#endif

EXTERN  BYTE    audio_effect;
EXTERN  BYTE    audio_channel;
EXTERN  INT8    audio_key;
EXTERN  INT8    echo_level;
EXTERN  INT8    echo_decay;
EXTERN  INT8    mic_volume;
EXTERN  INT8    ac3_dynarange;
EXTERN  INT8    mic_on;
EXTERN UINT32 coding_mode_now;


EXTERN  UINT16  smp_rate_now;
EXTERN  UINT16  smp_rate_down;
EXTERN  UINT16  frequency_mask;
EXTERN  UINT8   frequency_multiple;
EXTERN  BYTE    isSPDIFBitstream;
EXTERN  UINT16  buf_barrier_size;
EXTERN  UINT16  mpeg_audio;
#ifdef SUPPORT_AAC
EXTERN  UINT16  aac_audio;//Steven 2006/6/1 add for aac audio flag//
#endif
EXTERN  UINT16  Mp3_kbitrate;

#if defined( REMAIN_TIME ) || defined( SUPPORT_PRECALCULATE_VIDEOBITRATE_FOR_FILE_MODE )    // 2004/08/11 yltseng
EXTERN  UINT16  Mp3_kbitrate_PreCalc;
#endif

EXTERN  int     dspWatchDog;
EXTERN  BYTE    *bpcm_ya_ptr;
EXTERN  BYTE    auto_download_audio_chn;
//================================================================ CD
EXTERN  BYTE    bDiscType;
EXTERN  BYTE    cd_state;
EXTERN  BYTE    cd_subtype;
EXTERN  BYTE    cd_type;
EXTERN  BYTE    cd_type_loaded;
EXTERN  BYTE    mp3_cd_end_trk;
EXTERN  BYTE    cd_trk_now;
EXTERN  int     disp_trk_now;
EXTERN  BYTE    cd_trk_lo;
EXTERN  BYTE    cd_trk_lo_now;
EXTERN  BYTE    cd_trk_hi;
#ifdef CDDA_DEEMPHASIS
EXTERN  BYTE    cdda_pre_emphasis_flag; //axel 2005/10/20 for pre-emphasis disc
#endif
#ifdef BAD_DISC_SEQ_PLAY //axel 20050105
EXTERN  BYTE    bad_disc_seq_play;//terry,2003/8/29 02:32AM//4-6-14 12:22
#endif
#ifdef MICO_DVD
EXTERN  BYTE    power_off_state; //chen0627
EXTERN  BYTE    bCharTemp01[12]; //chen0627
#endif
//=============================================================== cd layer parser
EXTERN  INT16   cd_len;         /* cd-payload length        */
//================================================================ Video output
EXTERN  UINT8   p_scan;
EXTERN  UINT8   tv_out_id;
EXTERN  UINT8   tv_format;
EXTERN  UINT8   output_aspect;  // defined in aspect.h
EXTERN  UINT8   mode_aspect;
#ifdef IR_KEY_SET_VIDEO_MODE
EXTERN  BYTE    video_mode_val;
#endif

//================================================================ HD & HD OSD
EXTERN UINT8 tv_resolution;
EXTERN UINT8 osd_scale_buf_flag;  //check osd scaling buffer is ready or not. by robert.chang
//================================================================ Timer
EXTERN  UINT16  timeout_playback;
EXTERN  UINT16  rtc_10ms;
EXTERN  UINT16  rtc_100ms;
EXTERN  UINT16  rtc_500ms;

#if defined(SUPPORT_8202_DVB)||defined(SUPPORT_DVD_NATIVE_GAME)
EXTERN  UINT16  rtc_1s;	//eric add 2004-12-27 10:43
#endif
#ifdef OSD_AUTO_RECOVER
EXTERN  UINT16  rtc_1s;		//wjzhang 2004/09/25 for osd display&vfd display
#endif
#ifdef TURN_OFF_POWER_RESUME //wangap 2004/4/21
EXTERN  UINT16  rtc_60s;
#endif
EXTERN  UINT32  stc_polling; //terry,2005/3/30 03:07¤U¤È
EXTERN  UINT16  timestamp_key;
EXTERN  UINT16  timestamp_cderr;
//================================================================ CD FIFO control
EXTERN  UINT32  p_msf;
EXTERN  UINT32  s_msf;
EXTERN  UINT32  e_msf;
EXTERN  INT32   s_len;
EXTERN  UINT32  st_msf;
EXTERN  UINT16  dvddsp_vx;
//================================================================ rom ptr
EXTERN  BYTE    *romimage_ptr;
//================================================================ OSD
#include "osd_drv.h"
EXTERN  BYTE    osd_font_mode;
EXTERN  BYTE    PatternMode;
EXTERN  BYTE    ir_osd_post_show;
EXTERN  BYTE    sw_region_len;
EXTERN  BYTE    RegionValStr[MAX_REGION][14];
EXTERN  BYTE    RegionStr[MAX_REGION][MAX_SW_REGION][MAX_SW_R_LEN+1];
EXTERN  BYTE    RegionOnOff[MAX_REGION][4];

//================================================================ global line buffer var
EXTERN_MEM BYTE linebuf[100];

#ifndef	SUPPORT_DVB
//================================================================ system buf
EXTERN INT16   system_buf_cnt;
EXTERN BYTE    system_buf[32];
#else
extern  INT16   system_buf_cnt;
extern  BYTE    system_buf[32];
#endif	// SUPPORT_DVB

#ifdef OSD_BMP_DISPLAY
EXTERN_MEM BYTE linebuf_oriCh[100];
EXTERN  UINT8 disp_region;
EXTERN  UINT8 temp_region;
UINT32  *temp_region_top_buf;
UINT32  *temp_region_bottom_buf; 
#endif

#ifdef DOUBLE_TITLE//susu 2003-8-26 13:54
EXTERN_MEM BYTE linebuf_0[100];
EXTERN_MEM BYTE linebuf_1[100];
#endif

#ifdef SUPPORT_ANGLE_MARK	//liweihua add 20031118
EXTERN BYTE  angleflag;
#endif
//================================================================ JPEG
EXTERN UINT32 jpg_slide_time;
#ifdef NO_BLACK_for_PIC_CD
UINT8 pic_cd_first_play;
#endif

//================================================================ karaoke
#ifdef KARAOKE_MENU
EXTERN BYTE KARAOKE_MENU_FLAG;
#endif

#if defined(GBM_PORTABLE_DVD)||defined(SUNPLUS_8202P_DEMOBOARD)   //rbhung for GBM Portable DVD
#ifdef HOLD_KEY_DETECT
EXTERN BYTE hold_state;
#endif
EXTERN UINT32   lowbat_timer;
EXTERN UINT32   powerdown_timer;
#endif

#ifdef EASTWIN
EXTERN UINT32   lowbat_timer;
EXTERN UINT32   powerdown_timer;
EXTERN UINT32   blink_timer;
EXTERN BYTE     POWER_FLAG;
EXTERN UINT32   power_led_flash_timer;
EXTERN UINT32   power_on_mute_timer;
#endif

#ifdef SAFE_AUTO_POWEROFF
EXTERN BYTE   powerdown_time_counter;//nono add.2006-4-28 21:54
#endif

#ifdef VGA_CTRL_FORMAT//wangfeng 2003-12-18 16:12
EXTERN BYTE temp_format;
#endif

#ifdef TONIC_DVD
EXTERN BYTE KeyLockStatus;
#endif

//=================================================================standby timer
#ifdef SHOW_STANDBY_TIMER//suqiaoli add
EXTERN  UINT32  standby_time;
EXTERN  UINT32  counter_10ms;

EXTERN  BYTE  standby_hour;
EXTERN  BYTE  standby_min;
EXTERN  BYTE  standby_sec;
EXTERN  BYTE  show_standby_hour;
EXTERN  BYTE  show_standby_min;
EXTERN  BYTE  show_standby_sec;
EXTERN  BYTE  flag_standby_timer;
#endif
#ifdef AD_TCL
EXTERN BYTE jpg_ps;
EXTERN BYTE spk_dm_on;
EXTERN BYTE spk_sb_on;
EXTERN BYTE menu_id;
#endif

//==================Han Yang PDVD setup menu plus use
#ifdef SUPPORT_FUNCTION_MENU
EXTERN  BYTE  setup_menu_plus_timer;
#endif //end #ifdef SUPPORT_FUNCTION_MENU
#ifdef SUPPORT_DISPLAY_MENU
EXTERN  BYTE  in_display_function;
EXTERN  BYTE  goto_edit_state;
#endif
#ifdef ARGUS_PORTABLE_DVD
#ifdef SUPPORT_SPI
EXTERN  BYTE  pdvd_mode; //Portable DVD MODE,define in spi.h
EXTERN  BYTE  scommand;  //the special commands send to MCU
EXTERN  BYTE  check_sum;
EXTERN  BYTE  pdvd_timer;
#endif
#endif
#ifdef ADD_DVI311_SETUP
EXTERN BYTE dvi311_mode;
EXTERN BYTE dvi311_format;
EXTERN BYTE dvi311_tv_mode;
EXTERN BYTE Power_off_311;
 #endif

#ifdef SCALER_6500      //helm for scaler 050707
EXTERN BYTE dvi311_mode;
EXTERN BYTE dvi311_format;
EXTERN BYTE dvi311_tv_mode;
EXTERN BYTE Power_off_311;
#ifdef DAC_6500D   //2006-06-05 eric lin,6500 verD DAC
extern int run_scaler;
#endif
#endif

#ifdef BRIGHTNESS_COLOR_KEY
EXTERN BYTE BriCol_timer;
EXTERN BYTE BriCol_state;
EXTERN BYTE brightness_value;
EXTERN BYTE color_value;
#endif

//==============================================
//for QSI source switch     //added by JS   //20040726
#ifdef SUPPORT_QSI_SOURCE_SWITCH
EXTERN UINT8 source_type_now;
EXTERN UINT8 source_type_old;
EXTERN UINT8 source_switch_flag;
#endif
//==============================================

// for periher device
#define DVD_LOADER_EXIST    (1<<0)
EXTERN BYTE bDev;


//===============================================
#ifdef QSI_SHOW_ERR_RATE
EXTERN UINT8 QSI_PIPO_TEST;
EXTERN UINT8 QSI_PIPO_FLAG;
EXTERN UINT32 QSI_PIPO_MSF;
#endif

#ifdef SUPPORT_INSIDE_GAME
EXTERN UINT8 play_inside_game;
#endif

//===============================================
#ifdef SUPPORT_CD_TEXT        //lizhx add  2004/09/06
EXTERN  int flicker_flag;
#endif

#ifdef  SUPPORT_USB//lijd 20041008
EXTERN BYTE usb_card_setup_flag;
EXTERN BYTE usb_card_pause_flag;
EXTERN BYTE usb_plug_out_flag;
#endif

//================================================
// for support SWD related

#ifdef SUPPORT_PLAY_SWD
EXTERN BYTE START_POLLING_SWD;
#endif

#ifdef CHECK_PASSWORD_PLAY_MP3    //set password for reading MP3 cdrom   zhujg   2005-8-29
   EXTERN BYTE check_password_play_mp3;
 #endif

#ifdef SUPPORT_PS2
EXTERN int   mouse_pos_x;
EXTERN int   mouse_pos_y;
EXTERN BYTE      mouse_btn_status;
EXTERN BYTE      START_POLLING_PS2;
EXTERN BYTE      PS2_INIT_DONE;
#endif

#ifdef SUPPORT_16BIT_OSD
EXTERN BYTE OSD_buffer_16bit;
#endif

//================================================
EXTERN UINT32	file_media_flag;			// file media flag, byte 0 for contained file media, byte 1 for media supportability, byte 2 for media special type

#ifdef CONTINUOUS_NUM_KEY_SELECT
EXTERN BYTE ir_num1;
EXTERN BYTE ir_num2;
EXTERN BYTE ir_num3;
EXTERN BYTE ir_num4;
EXTERN BYTE ir_num_timer;
EXTERN BYTE ir_num_state;
#endif

#ifdef SOLVE_VBR_SVCD_FOR_STARLITE
EXTERN BYTE  SVCD_Bad_Disc;
#endif

#ifdef SHOW_SPECIAL_DISC_TYPE
EXTERN BYTE read_disc_state;
#endif

#if defined(HDMI)||defined(USE_2MS_RTC)//Modifed by chenzhao on 2006-01-10
EXTERN UINT16	NewRTC;
#endif
#ifdef HDCP_CUSTOM//Modifed by chenzhao on 2004-12-1 11:36   
EXTERN BYTE hdcp_mode;
#endif

EXTERN  BYTE    user_mute; //WSLEE for switching audio channel and mute mode 2005-01-14

#ifdef SUPPORT_TESTSPK /*2005-6-6 huziqin*/
EXTERN  BYTE    testspk_state; //chenzhao for add testspk ui 2005-01-14
#endif

#ifdef SUPPORT_HEADPHONE
BYTE bHpPlug;  // 1: headphone plug in   0:headphone not plug in
#endif

#ifdef SUPPORT_PROLOGIC_II
//enum move to gb_def.h chenzhao20060120
EXTERN BYTE surround_mode; /*1 for 2ch  0 for 5.1ch*/
EXTERN BYTE    prologic_val ;//clead 2003-8-7
EXTERN BYTE    prologic_flag;  //wuzhj add for prologic_II 2004/04/04
#endif //SUPPORT_PROLOGIC_II

EXTERN int GamePadVal;

EXTERN UINT32 FH_iRes;
EXTERN int IsDoingBitBLT;
EXTERN int ELAIsEnable;  
EXTERN int FlashIsEnable;  
#ifdef PARENT_PWD_DEFAULT_NULL
EXTERN int RSM_Flag;
EXTERN int PassWord_OK;
#endif
#ifdef SUPPORT_SPG_GAME //axel 2005/8/29 10:24¤W¤È
EXTERN     UINT32 SPG_iRes;
#endif
//=================================================================DIVX
#ifdef DIVX_DRM_MODEL_ID //linrc change for change this ID needn't update fs_mp4.a 2005-8-11 17:15
EXTERN UINT32 Divx_drm_modelID;
#endif

#if     defined(SUPPORT_DVB)
#include "..\dvb_h\dvb.h"
#endif      /* defined(SUPPORT_DVB) */

#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
EXTERN BYTE source_play_mode;
EXTERN BYTE old_system_state;
EXTERN BYTE usb_card_state;
#ifdef MODE_SWITCH_DELAY
EXTERN BYTE mode_key_delay_cnt;
#endif
#endif

#ifdef	SUPPORT_FONT_OUTLINE
EXTERN BYTE	Mp4Subtitle_flag;
#endif
#ifdef SUPPORT_MP3_ENCODER 
EXTERN	int		mp3_encoder_state;
EXTERN	int 	deviceWriteFlag;
EXTERN	BYTE	polling_MP3_encoder;
EXTERN	UINT32	dataInPtr;
EXTERN	UINT32	dataOutPtr;
EXTERN	UINT32	dataBarrierPtr;

EXTERN	UINT32	ripping_flag; //qinhua ,add 2005-11-10 16:30
EXTERN	UINT32	change_speed_flag; //qinhua ,add 2005-11-10 16:30     
EXTERN	UINT32	pre_ripping_flag;
UINT32 e_ptr; 
#endif

#ifdef LINE_IN_ENCODE
EXTERN	int     encoder_type;
EXTERN	int     line_in_flag;
EXTERN int  linein_state;
#endif

#ifdef RIPPING_MODE_SELECT//qinhua,add,2006-5-30 02:49ÏÂÎç
EXTERN	BYTE	ripping_all_flag; // 0:rip 1 , 1:rip all
#endif 

#ifdef  SLOW_SOME_KEY_IN_MALATA_IR
EXTERN  BYTE  clear_key;
EXTERN  BYTE  clear_count;
#endif
#ifdef SUPPORT_IR10P_LIMIT//tianye 200607
UINT8  flag_input ;
#endif//#ifdef  SUPPORT_IR10P_LIMIT		

#ifdef SUPPORT_LAST_MEMERY		    
EXTERN  BYTE  memery_resumeflag;
#endif//end=> #ifdef SUPPORT_LAST_MEMERY

#ifdef SUPPORT_OP_FIVE_DISC //chenzhao20060107
EXTERN BYTE play_5disc_state;	
#endif

#ifdef STOP_SERVO_IN_OTHER_MODE
EXTERN BYTE stop_loder_cnt;
#endif

#if     defined(USE_AMP_MUTE)//chenzhao20060114
EXTERN BYTE user_amp_mute;// 1:mute ,0:demute
#endif      /* defined(USE_AMP_MUTE) */

#ifdef SUPPORT_SETUP_POPUP_MEDIA_GUI//chenzhao20060116
EXTERN BYTE need_popup_menu;
#endif

#ifdef SPEAKER_CONFIG//chenzhao20060116
EXTERN BYTE speaker_front;
EXTERN BYTE speaker_center;
EXTERN BYTE speaker_surround;
EXTERN BYTE speaker_subwoofer;
#endif

#ifdef I2C_MASS_DATA_POLLING_WRITE 
EXTERN const BYTE *p_i2c_mass_data;// 1:mute ,0:demute
#endif//#ifdef I2C_MASS_DATA_POLLING_WRITE 

#if (defined SUPPORT_SPDIF_IN	||defined SUPPORT_COAXIAL_IN) //chenzhao20060118
EXTERN BYTE spdif_in_channel;
EXTERN BYTE spdifin_type;
    #ifdef MERGE_TEMP
    EXTERN BYTE spdif_in_sample_rate;
    #endif
#endif

#ifdef SUPPORT_RECEIVER//moved from gb_def.h chenzhao 20060120
EXTERN BYTE current_rcvr_mode;
EXTERN BYTE next_rcvr_mode;
EXTERN BYTE last_non_dvd_rcvr_mode;
EXTERN BYTE switch_modes_now;
EXTERN BYTE servo_inited;
EXTERN BYTE rcvr_support_bits;
#endif

//=============add for alco==================================================
#ifdef VIDEO_IN_CONTROL
EXTERN BYTE AVin_step;
#endif

#ifdef NEED_DIFF_IR_PANEL_KEY
EXTERN BYTE panel_key_flag;
#endif

#ifdef STOP_2LIST_MENU_2MENU
EXTERN BYTE menu_key_timer;
#endif

#ifdef REM_DECODE_JPEG
EXTERN BYTE jpeg_decoding; 
#endif 

#ifdef UNLOCK_STATE_NOT_CHECK_PASSWD
EXTERN BYTE disc_has_unlock;
#endif
		
#if defined(RISC_ALIVE_STANDBY)&&defined(ALCO_DVD_UI)
EXTERN BYTE go_into_prestandby;
#endif

#ifdef DIVX_STOP_TO_PLAY_DELAY//shenyj add for alco divx 12/09
//EXTERN BYTE record_file_extern_name_flag;
EXTERN BYTE divx_stop_to_play_delay_timer;
#endif

#if 0//def ALCO_MODIFY_PAL_OSD //05/01/03 mark!
EXTERN BYTE old_vppsetup_tv_system;
#endif
		    
#ifdef VCD_DISC_ACCORDING_REGION
EXTERN BYTE region_code_reset;
#endif
		    
#ifdef BAT_DETECT
EXTERN UINT32   lowbat_timer;
EXTERN UINT32   highbat_timer;
#endif
		   
#ifdef AUDIO_AND_SUBTITLE_SAME2_OSD
EXTERN BYTE osd_has_chaned;
#endif
		   
#ifdef STOP_RESUME_DVD_VCD
EXTERN BYTE need_record;
#endif

EXTERN int IsFieldEnd;//shenyj

#ifdef JPG_ROTATE_DELAY
EXTERN BYTE angle_key_timer;
#endif
          
#ifdef MP4_INIT_STATE_INVALID_KEY
BYTE MP4_init_state;
#endif
//===============================================================
#ifdef SUPPORT_CARDREADER_TEST//added by ouyang, 2006-4-18 16:41
EXTERN int iMidi_storage_type;
#endif//SUPPORT_CARDREADER_TEST

#ifdef SUPPORT_TTX_MIXER_KEY //Jack modified 06/04/17
EXTERN BYTE  ttx_bg_mixer;
#endif

#ifdef SUPPORT_NEWDB //shenyj add 2006/05/12
EXTERN int  eeprom_flash_store_info_flag;
#endif
#ifdef  SUPPORT_DVD_DVB_USB_CARD_FREE_CHANGE//tianye add.200607
UINT8   flag_no_check_servo ;
#endif//end=> #ifdef  SUPPORT_DVD_DVB_USB_CARD_FREE_CHANGE

#ifdef SUPPORT_SYS_POWER_ON_WAITING_MCUINFO //tianye add.200607
UINT8  flag_check_mcu_info;
#ifdef ONE_TWO_THREE_FOUR_CHANGE
UINT8  xxx;
UINT8  yyy;
#endif//end=> #ifdef ONE_TWO_THREE_FOUR_CHANGE
#endif//end=> #ifdef  SUPPORT_SYS_POWER_ON_WAITING_MCUINFO

#ifdef  SHOW_FREQ_MT2060//tianye add.200607
EXTERN   UINT32  fre_mt2060;
#endif//end=>#ifdef  SHOW_FREQ_MT2060

#ifdef ENABLE_SSPLL             // 2006/09/22 yltseng
#define sspll_reg_backup()      {sft_cfg24_bak = regs0->sft_cfg24; sysckl_sel_bak = regs0->sysclk_sel;}
#define sspll_reg_restore()     {regs0->sft_cfg24 = sft_cfg24_bak; regs0->sysclk_sel = sysckl_sel_bak;}

EXTERN  UINT16  sft_cfg24_bak;
EXTERN  UINT16  sysckl_sel_bak;
#else
#define sspll_reg_backup()
#define sspll_reg_restore()
#endif

#endif/*__GLOBAL_H*/

