//
// FILE
// sysmain2.c
//
// DESCRIPTION
// Main entry of DVD system firmware
//
// 20030307 Maintain by terry
// 20050928 Reorganized by potatooo
//

#include "sysmain2_h.h"
#include "gpio.h"
#include "user_init.h"
#include "kinf.h"
#include "sinf.h"
#include "user_if.h"
#include "timer.h"
#include "fs.h"
#include "Navdata.h"
#ifdef POWER_ON_MUTE_MIC   //axel 2004/2/26 04:10pm mute mic during initialization
#include "dsp3_if.h"
#endif

#ifdef SUPPORT_HD_RESOLUTION
    #include "setup\setup_VA.h"
#endif

#ifdef NODISC_SHOW_IN_DIFF_REGION
extern void nodisc_osd_init(void);
#endif

#ifdef STOP_LOADER
extern void stop_loader(void);
#endif 
#ifdef TP6317_PANNEL   //yaowh add 04-10-25
   extern BYTE TP6317_Power ;   //flag
#endif

#if 0//def JPEG_MP4_FRIST_STOP_TO_GUI
 extern int  mp4_to_logo; 
#endif 

#if 1//def TEST_SERVO//nono 2004-3-30 19:13
#include "ircode.h"
#endif
#include "srv_test.c"

#ifdef SUPPORT_RECEIVER     //benson  2004/03/01
#include "dsp3_if.h"
#endif

#ifdef MULTIDISC_LOADER  //chenzhao 20060111
#include "multidisc_loader.h"
#endif

#ifdef WAIT_SERVO_FLAG//chenzhao 2006-3-23 21:32 .
#include "dvddsp.h"
#endif

#ifdef SUPPORT_APOGEE_AMP
#include "ddx8000.h"
#endif

#include "auddrv.h" //2004AUDDRV oliver 20041004 for using audio driver purpose
#ifdef SUPPORT_SPDIF_IN
#include "audif.h"
#endif

#ifdef SUPPORT_WMA
#include "asf_if.h"
#endif

#ifdef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-4-11 16:28
#include "ircmd_switch_media.h"
#endif//DIRECT_ACCESS_MEDIA

//jslin //for QSI PIPO  //20040901
#ifdef QSI_SHOW_ERR_RATE
#include "uart.h"
#endif

#ifdef SUPPORT_8202_DVB
#include "kernel.h"
#include "..\dvb_h\TunerDrv.h"
#include "..\dvb_h\sp_dtv.h"
#include "..\dvb_h\dvb_func.h"
extern void dvb_check_media_switch();
extern void Demux6600HwInit(void);
extern int dvb_navigation(void);
extern void stop_loader(void);
extern void show_DvdDvbSwitch_status(BYTE flag);     //sunzhh add 20050927
extern void Dvb_PlayGame(void);
extern void dmx_6600_init(void);//Jack clear warning msg 05/09/29
extern void dvb_state_servo_stop(void);
#ifdef SUPPORT_TUNER_POWER_ONOFF
extern void tuner_power_control(BYTE control_flag);
#endif
#ifdef SUPPORT_ANTENNA_POWER_CONTROL//xiaopeng 2006-9-4 13:06
extern BYTE setting_ant_power_control(BYTE control_flag);
extern BYTE gAntSelPower;
#endif
#endif
extern void setup_error_counter_limit(int n);//terry,2005/10/13 01:59¤U¤È

#ifdef PMP_UI//liweihua 2005-3-16
#include "fsNAV_PMP.h"
#endif

#ifdef SUPPORT_UNICODE_FONT //joshua 2005/9/2
#include "font_unicode.h"
#endif

#ifdef MUSTEK_K100D_USE_SOME_6600_GPIO
#include "..\dvb_h\dmx_6600_gpio.h"
#endif

#ifdef AV_IN_THROUGH_EXT_ADC
static inline void apmain_state_avin();
#endif                
                
//=========================

#if defined(SUPPORT_MP4) || defined(SUPPORT_WMA) || defined(SUPPORT_AUD_WMA)
extern UINT32 nGotoPck;
#endif

//Maoyong 2004.03.05, move some resume relative declare/def to "rsm_util.h"
#ifdef  CHECK_RECORD_DISK_PARENT_LVL    //Maoyong 2004.03.04
extern BYTE CheckDiscParentLvl(void);
#endif
extern BYTE CheckLoadRsmInfo(void);
extern void RecordRsmPlay(void);

#if defined(AUDIO_2CH_5_1CH)&&defined(SUPPORT_PROLOGIC_II)//axel modified 2004/3/16 10:53am zhaoyanhua add 2003-12-17 9:47
extern int setup_IsSpkDownmixOff(void);//setup_tab.c
extern void AudioSet2chOutput(void);//setup_tab.c
#endif

#ifdef  DYNAMIC_SPECTRUM //zhaoyanhua add 03-11-6 15:26
extern void Show3dspectrum(void);
#endif
#ifdef SLEEP_CONTROL_COUNTER    //jwk 2005-11-5 13:51
extern UINT32 counter_sleep_control;
#endif

#ifdef CORTROL_VCD_ONF
extern int setup_IsVCD_OFF();
#endif

#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
extern BYTE IsCardMediaExist(void);
extern void SwitchMedia(BYTE direction);
#endif

#ifdef  SUPPORT_REP_READ
#include "read.h"
#endif

#ifdef PROVIEW_GPIO_KEY
void set_proview_gpio_key(void);
#endif

#ifndef DIRECT_ACCESS_MEDIA//added by wangwei, for no auto switch media.
void system_check_media_switch(void);
void system_check_source_switch(void);// for QSI disc\card switch   //added by JS   //20040727
#endif//DIRECT_ACCESS_MEDIA

#ifdef PMP_DVD //wthsin, 2004/11/9 07:19
 UINT8 PMP_ENABLE=0;
 extern void pc_usb_access_mode();
#endif //#ifdef PMP_DVD

#ifdef SUPPORT_Auo_2inch_Digital_panel
extern void init_auo_digital_panel(void);
#endif

#ifdef SUPPORT_Auo_UPS053_Digital_panel

extern void init_auo_ups053_digital_panel(void);

#endif

#ifdef FILE_MODE_WRITE//added by wangwei,2005-1-9 21:40
extern unsigned int detect_CD;
#endif

#if defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)  //modefied by wangwei,2004-11-19 17:31(for storage no files screen refresh problem)
extern UINT8 MediaIsEmpty;
//#define MEDIA_EMPTY 1         //dingzhy moved to gb_def.h
//#define MEDIA_NOT_EMPTY 0
#endif

//=====================================================
//* debug option
//=====================================================
#ifndef DVDRELEASE
//#define SYSMAIN2_DBG        1
//#define MONE_LOGO
//#define PLAY_VIDEO_DISC_AS_FILEMODE
#endif

#undef FORCE_SKIP_VCD_MOSAIC//nono 4-6-9 0:35

#ifndef SYSMAIN2_DBG
#undef printf
#undef print_block
#define printf(f, a...) do {} while (0)
#define print_block(x,y) do {} while (0)
#endif

//=====================================================
//* var. and extern function decalare
//=====================================================
#include "sysmain2.h"

extern UINT8 Subp_stream_Chg(UINT8,int);
extern UINT16 Audio_stream_Chg_SVCD(UINT8);
//2004AUDDRV extern void init_mp3(void);
extern void do_mp3(void);
extern int AUDIF_Set_Play();//2004AUDDRV AudioSetPlay();  //huziqin 2004-2-26
extern int AUDIF_Set_Stop();//2004AUDDRV AudioSetStop();  //change type to int
extern void RsmInfo2Flash(int);
extern void LoadRsmInfo(void);
extern void LoadModual(UINT16);
extern void RS42Init();
extern void RS2420Init();
extern void DisplayScreenSaver();
#ifdef DVD_SERVO
extern UINT8 cServoWrongDataPass;
#endif
void SetDeInterlace(BYTE nVal);
extern void setup_SetSPDIFConfig();//nono 3-8-18 15:45
#ifdef CD_PLAYER    //liweihua 2003-9-3
extern void show_cdplayer(void);
#endif
#if defined(CF_CARD_WRITE) || defined(SPHE8202_FAT_Write_Function)//|| defined(WRITE_USB)
extern BYTE read_card_sign,flag_cf2cd,flag_cd2cf;          //xulf
#endif
#ifdef VIRTUAL_KEYBOARD//liweihua 2003-9-18
extern BYTE KeyID;
void hl_keyboard_button(BYTE SelectID);
void osd_draw_virtual_keyboard(int xStart, int yStart,BYTE r);
#endif

#ifdef LOGO_PLAY_MP3
 int playindex;
#endif

BYTE logo_play_mp3_flag;
extern UINT8 power_on_mute;//terry 20030805
extern void set_video_default_offset(void);//wanghaoying 2003-8-12 20:21
extern void save_cmp_disc_info(UINT32 info1);//wanghaoying 2003-8-12 20:22

#ifdef SUPPORT_HDD_ACCESS
    UINT8 f_force_browser=0;
    UINT8 f_browser_mode=0;
#endif

#ifdef USE_PIN31_CONTROL_POWER_LED      //gerry,2004-3-9 19:41
int gbm_gpio_led_flag;
#endif//USE_PIN31_CONTROL_POWER_LED

#ifdef PLUS_VR_AUTH_PLAYBACK
extern INT8    bDVDplusVR;      //moved here by gary...
#endif
#ifdef PUSH_TRAY_IN_DISPLAY
extern void update_vfd_data(void);//chenzhao20051101
#endif

#ifdef PLAY_VIDEO_DISC_AS_FILEMODE  // for debug usage, usually when debugging DVD css
#define disc_init()
#define check_cdtype()  (cd_type_loaded = CDROM)
#endif
//
// state machines
//
static inline void apmain_state_open();
static inline void apmain_state_nodisc();
static inline void apmain_state_read_title();
static inline void apmain_state_setup_browser();
static inline void apmain_state_browse();
static inline void apmain_state_finish();
static inline void apmain_state_stop();


#ifdef PUSH_TRAY_IN_DISPLAY   //chenzhao20051110
void push_tray_in_detect(void)
{
    static BYTE tray_in_flag=0;
    if(GPIO_I_GET(TRAY_IS_OUT_NUM)==0)
       tray_in_flag=1;
    if((tray_in_flag)&&(GPIO_I_GET(TRAY_IS_OUT_NUM)))
      {
        tray_in_flag=0;
        if(current_rcvr_mode ==RECEIVER_MODE_DVD)
        {
            play_state = VCD_STATE_CLOSE;
            update_vfd_data();
            PrintOsdMsg(STR_OS_CLOSE,REGION1,0,0);
        }
     }
}
#endif     


//
// FUNCTION
// show_osd_disc_type()
// 
// terry,2003/12/29 08:25PM
//
static void show_osd_disc_type(void)
{
    #ifdef NO_FILES_OR_UNSUPPORT_NOT_SHOW_FSGUI_AND_SHOW_NODISC
    if((cd_type_loaded==CDROM) && (!pFsJpeg->iso9660_file_cnt)
    #ifdef NOT_SUPPORT_MP3
    ||(pFsJpeg->iso9660_file_cnt>pFsJpeg->gifsMP3Count)
    #endif
    )
        return;
    #endif
    
    #if defined(JUST_SHOW_CD_TYPE)||defined(NOSHOW_CDROM_WHEN_DISP)||defined(BEAUTIFUL_STYLE)       //Not show CD Icon for NINTAUS Maoyong 2004.02.12
    #if defined(NOSHOW_CDROM_WHEN_DISP)||defined(BEAUTIFUL_STYLE)//nono 2004-6-15 0:02    //dingzhy for beautiful
    if(cd_type_loaded == CDROM)
    #else
    if(cd_type_loaded == CDDA)
    #endif
    {
        osd_tog_region(REGION1, OSD_OFF);
        return;
    }
    #endif

#ifdef GBM_DVD
    PrintOsdMsg(osd_cd_id[cd_type_loaded],REGION1,2,0);
#elif defined(DVD_AUDIO)    // alan, 2003/8/15 04:23PM, to distinguish DVD-VIDEO or DVD-AUDIO
    // DVD_AUDIO
    #ifdef SHOW_DVD_ROM//NONO 4-2-10 19:08
    if( (is_svo_dvd())&&(cd_type_loaded==CDROM) )
        {
            OSD1000ISP_STATUS(OSDISP_TYPE_DVDROM, OSDIR_CDTYPE);
            psprintf(RegionValStr[REGION1], "DVDROM");
            PrintOsdMsg(STR_OS_SPACE,REGION1, 1, 1);
        }
    else
    #endif  //SHOW_DVD_ROM
    if (cd_type_loaded==CDDVD)
    {
        if (dAMG_LSN==0)
            psprintf(RegionValStr[REGION1], "DVD-VIDEO");
        else
            psprintf(RegionValStr[REGION1], "DVD-AUDIO");
        OSD1000ISP_STATUS(OSDISP_TYPE_DVD, OSDIR_CDTYPE);
        PrintOsdMsg(STR_OS_SPACE,REGION1, 1, 1);
    }
    else
    {
#ifdef DVD_SERVO
        if ((cd_type_loaded == CDVCD10) && (is_svo_dvd()))
#else
        if (cd_type_loaded == CDVCD10)
#endif
        {
            OSD1000ISP_STATUS(OSDISP_TYPE_DVD, OSDIR_CDTYPE);
            PrintOsdMsg(osd_cd_id[CDDVD],REGION1,1,0);
        }
        else
        {
            OSD1000ISP_STATUS(cd_type_loaded, OSDIR_CDTYPE);
            PrintOsdMsg(osd_cd_id[cd_type_loaded],REGION1,1,0);
        }
    }
#elif defined (FENGKAI_DVD)
    // FENGKAI : clead 2003-8-27 17:31
    printf("**--- cd_type_loaded:%d  bDiscType:%d ---**\n",cd_type_loaded,bDiscType);

    if((cd_type_loaded==CDSVCD)&&(bDiscType == CD_CVD))
    {
        OSD1000ISP_STATUS(OSDISP_TYPE_CVD, OSDIR_CDTYPE);
        psprintf(RegionValStr[REGION1], "CVD");
        PrintOsdMsg(STR_OS_SPACE,REGION1, 1, 1);
    }else
    {
        OSD1000ISP_STATUS(cd_type_loaded, OSDIR_CDTYPE);
        PrintOsdMsg(osd_cd_id[cd_type_loaded],REGION1,1,0);
    }
#elif defined(SKYWORTH_DVD)
    // SKYWORTH
    if(cd_type_loaded!=CDROM)
    {
        OSD1000ISP_STATUS(cd_type_loaded, OSDIR_CDTYPE);
        PrintOsdMsg(osd_cd_id[cd_type_loaded],REGION1,1,0);
    }
    else
    {
        PrintOsdMsg(STR_OS_SPACE,REGION1,1,0);
    }
#else
    // DEFAULT
    #ifdef DVD_SERVO
    if ((cd_type_loaded == CDVCD10) && (is_svo_dvd()))
    #else
    if (cd_type_loaded == CDVCD10)
    #endif
    {
        OSD1000ISP_STATUS(OSDISP_TYPE_DVD, OSDIR_CDTYPE);
        PrintOsdMsg(osd_cd_id[CDDVD],REGION1,1,0);
    }
    else
    {
        OSD1000ISP_STATUS(cd_type_loaded, OSDIR_CDTYPE);
        PrintOsdMsg(osd_cd_id[cd_type_loaded],REGION1,1,0);
    }
#endif
}



//*******init ce2746 dac ******** wangap 2004/4/21
#if defined(CE2746)||defined(CE2766)
#define Chip_addr 0x6a
#define Register_addr 0x00
void init_ce2746()
{
   #if defined(CE2746)
   int I2c_data1=0x01,I2c_data2=0x80;
   #elif defined(CE2766) //zxb 2005-9-14 0:35
   int I2c_data1=0x21,I2c_data2=0x80;
   #endif
   WriteI2c(Chip_addr,Register_addr,I2c_data1,1);
   delay_1ms(10);
   WriteI2c(Chip_addr,Register_addr+1,I2c_data2,1);
}
#endif

//*******init ce2826 dac ******** felix 2005-9-2 16:23
#ifdef CE2826
#define Chip_addr 0x6a
#define Register_addr 0x01
void init_ce2826()
{
   int I2c_data1=0x88;
   WriteI2c(Chip_addr,Register_addr,I2c_data1,1);
   delay_1ms(10);
}
#endif//

//*******init AV2808 dac ******** felix 2006-4-18 15:43

#ifdef AV2808
#define Chip_addr 0x66       //0x33[ca0:6]+RW
#define Register_addr1 0x0f  //Register_addr1 control reset.
#define Register_addr3 0x06  //Register_addr2 power control.
void init_av2808()
{  //Register_addr1 control reset.
     //sofeware reset, system reset;
   WriteI2c(Chip_addr,Register_addr1,0x01,1);
   delay_1ms(10);
   WriteI2c(Chip_addr,Register_addr1,0x11,1);
   delay_1ms(10);
   ///Register_addr2 power control.
   WriteI2c(Chip_addr,Register_addr3,0x80,1);
   delay_1ms(600);
   WriteI2c(Chip_addr,Register_addr3,0x00,1);
}
#endif
// 
// system state
//
static inline void set_system_state(int nst)
{
    system_state = nst;
}

static inline int get_system_state()
{
    return system_state;
}


//=====================================================
//* function decalare
//=====================================================
void InitVar(void)
{
    #if defined(DVD_DEFAULT_SHOW_TITLE_TIME)&&defined(SUPPORT_USB)
        remain = 0; //when swtich DVD to usb play mp3 display time error hongfeng 2005-07-18
    #endif
    
 	#ifdef FS_FILE_POWER_RESUME//qinhua,2006-6-16 07:01ÏÂÎç
     resume_clear=1;
  	#endif 
    
  #ifdef JPEG_MP4_FRIST_STOP_TO_GUI
   mp4_to_logo=0; 
  #endif 
   #ifdef SUPPORT_STOP_PLAY_READ_USB_CARD  //qinhua ,2005-10-24 13:00
      media_change_flag_mark = 1;
     // media_change_flag =1 ;
   #endif 
    #ifdef OP_CD_CDG_CHANGE //caoh 2005-9-19 10:37
    op_cd_cdg_flag = 0;//caoh 2005-9-19 10:37 only for OP
    #endif
    
    #ifdef OP_STOP_PANEL_DISPLAY//lijd 2005-6-30 11:32
    StopTimes=0;
    #endif 
    //init pe engine
    pe_run = 0;
//    dVts_iso9600_addr = 0;//terry,2003/8/6 04:01PM
#ifdef TP6317_PANNEL   //yaowh add  04-10-25
    TP6317_Power = 0 ;
#endif
    PE_ClearNav();
    mpeg_audio=0;
    #ifdef SUPPORT_AAC
    aac_audio = 0;//Steven 2006/6/1 add for aac audio flag initialization//
    #endif
    dspWatchDog=DSP_WD_INIT;

#ifdef BAD_DISC_AUTO_STOP //terry,2003/8/31 12:00AM
    bad_disc_auto_stop=0;
#endif

    //init navigation
    cd_subtype = CDROM_UNSUPPORT;
    bDiscType=CDUNKNOWN;
    still_timer=0;

    //#ifdef SUPPORT_MIX_MP3_CDDA   //linrc change "SUPPORT_MIX_MP3_CDDA" to "SUPPORT_MIX_DATA_CDDA_DISC"
    #ifdef SUPPORT_MIX_DATA_CDDA_DISC //because we not only support this type mix mode disc 2004-12-15 15:53
    mp3_cd_end_trk = 0;
    #endif
    play_dir = 0;

    Mp3ReadFinish=0;//mp3 ........
    logo_play_mp3_flag=1;
    fore_disp_time=-1;
#ifndef ADJUST_JPEG_SLIDE_TIME//lijd 2005-4-21 16:49
    jpg_slide_time = JPEG_SLIDE_TIME;//jpeg .......... wanghaoying 2003-8-26 20:21
#endif
#ifdef NO_BLACK_for_PIC_CD
    pic_cd_first_play = 0;
#endif

    bPbcOff=0; //vcd ..........
    cd_trk_now=0;
    cd_trk_hi=0xff;
    cd_trk_lo_now=0;
    cd_trk_lo=0;

    dVMG_LSN = 0; //dvd.......
    HL_exist=0;
    read_sector=0;
    dvd_error=0;
    min_astn_id=0;//terry,2003/12/15 02:33PM
    dvd_karaoke_mode = 0; //terry,2004/2/16 11:11AM

    #ifdef DVD_AUDIO
    dAMG_LSN = 0;
    #endif

    #ifdef TUNR_OFF_PARENTAL_LVL
    bTurnOffParentalLVL=0; //terry,2002/9/20 11:40PM
    #endif

    #ifdef JUST_SHOW_CD_TYPE    //Maoyong 2004.02.26
    track_play_diff_time = 0;
    #endif

#ifdef DVD_SEQ_PLAY
#ifdef AUTO_PLAY
    extern BYTE auto_play_on();
    if (auto_play_on())
        dvd_menu_play = 0;
    else
        dvd_menu_play = 1;
#else
    dvd_menu_play = 0;
#endif
#endif

    // 2004/07/16 yltseng
    wb_tag_init();

    //init UI
    init_ir_num();
    goto_active=0;
    mp3_user_select=0;
    pFsJpeg->iso9660_file_cnt = 0;
    disp_trk_now = 0;
    Mp3_kbitrate=0;
    bIntro=0;
    //keep_cmd_code=0;
    keep_cmd_code=IR_CODE_MAX_NUM;//2004-3-30 19:14
    disc_st_time=0;

    #if defined(IR_PLAY_RESUME) && defined(POWER_RESUME)  //yw 021003
    power_resumeflag = 0;
    #endif

    #ifdef SUPPORT_REP_READ    //Maoyong 2004.06.03
    InitRead();
    #endif

    #ifdef  SUPPORT_BOOK
    init_book();
    #endif

    goto_time = 0;//4-4-13 16:22
    pe_timesearch_clear();//nono 5-4-4 22:00 clear time search flag.
    
//#ifdef OP_UI//zhaoyanhua 2004-5-24 17:35
//    prog_cnt = 0;
//#endif
    //nono move from ap_mian(): SYSTEM_READ_TITTLE.2004-2-27 12:00
    coding_mode_now=AUDIF_CODING_MODE_NONE;//wangfeng 2003-12-19 17:44

#ifdef USE_PIN31_CONTROL_POWER_LED      //gerry,2004-3-9 19:42
    gbm_gpio_led_flag=0;
#endif//USE_PIN31_CONTROL_POWER_LED

    nOldFst = 0;          //Maoyong 2004.05.25 move from labif.c

#ifdef SUPPORT_WMA        //Maoyong 2004.05.31 for WMA
    asf_resume_pck = 0;
#endif

#if defined(SUPPORT_MP4) || defined(SUPPORT_WMA) || defined(SUPPORT_AUD_WMA)
    nGotoPck = 0;
#endif

    //FS SWD
    #ifdef SUPPORT_PLAY_SWD
        START_POLLING_SWD = 0;
    #endif

    //OSD 16bit direct color
    #ifdef SUPPORT_PS2
        OSD_buffer_16bit = 0;
    #endif

    #ifdef DIVX_DRM_MODEL_ID //linrc change for change this ID needn't update fs_mp4.a 2005-8-11 17:15
    Divx_drm_modelID = DIVX_DRM_MODEL_ID;
    #endif

    //initiate PS2 mouse
    #ifdef SUPPORT_PS2
        START_POLLING_PS2 = 0;  //hold polling
        mouse_pos_x = 180;
        mouse_pos_y = 120;
        mouse_btn_status = 0x0;
        PS2_INIT_DONE = 0x0;
    #endif

#ifdef CDDA_USE_MP3_GUI
	is_cdda_var = 0;
#endif
//==============================================
//for QSI source switch     //added by JS   //20040726
#if defined(QSI_PORTABLE_DVD) && defined(SUPPORT_CARD_STORAGE)
    #ifdef SUPPORT_QSI_SOURCE_SWITCH
        source_type_now = source_disc;
        source_type_old = source_disc;
    #endif
#endif
//==============================================
	#ifdef SUPPORT_MP3_ENCODER
		mp3_encoder_state = test_stop;
		dataInPtr = DATA_BUF_ADDR;
		dataOutPtr = DATA_BUF_ADDR;
		dataBarrierPtr = DATA_BUF_ADDR - 512;
		polling_MP3_encoder = 0;
		deviceWriteFlag = 1;
   ripping_flag=0; //qinhua,2005-11-10 20:31
   pre_ripping_flag=0;
	#endif

#ifdef RIPPING_MODE_SELECT //qinhua,add,2006-5-30 02:50ÏÂÎç
    ripping_all_flag=0;
#endif  

#ifdef MODE_SWITCH_DELAY///YANGLI ,2006-2-22 23:18
    //mode_key_delay_cnt =3;
#endif

   #ifdef  SUPPORT_DVD_DVB_USB_CARD_FREE_CHANGE
   flag_no_check_servo = 0;
   #endif//end=> #ifdef  SUPPORT_DVD_DVB_USB_CARD_FREE_CHANGE

    CSSEnable = 0; // init. CSSEnable for CSS DISC. robert.chang, 2006-09-01
   
}


#include "sysmain2_showtitle.inc"
#include "sysmain2_logomp3.inc"

/****************************************************/
/* initial subroutine                               */
/****************************************************/
void volume_init(void)
{
    #if !defined(Ti3001_OSD_UI_1)
        #if defined(VOLUME_RECODE)||defined(VOLUME_RECODE_NEW)
        {
            //audio_volume  = VOL_VALUE;   //set to maximum volume
            int read_volume=0;
            int i=0;
        #ifdef CNTR_5SPK_VOLUME
        for (i=0; i<7; i++) {
        #endif
            read_volume=ReadFromI2c(0xa0,ADDR_I2C_VOLUME+i,(BYTE *)&audio_volume,sizeof(audio_volume));
            if(read_volume!=1)
            {
            //#if 1//def    ROTARY_VOL_HUAJIA1251
                    #ifdef CNTR_5SPK_VOLUME// defined(HIMAGE1251) || defined(HIMAGE1250_03_185W)//wangfeng 2003-10-31 21:11
                    #ifdef SW_VOL_63
                    if(i==6){
                        audio_volume  = SUB_DEFAULT;

                    }
                    else
                    #endif
                audio_volume  = DEFAULT_VOL;
                #else
                audio_volume  = DEFAULT_VOL;
                    #endif
            //#else
            //    audio_volume  = VOL_VALUE;
            //#endif
            }
//by zongrifei 2005/10/28  

#ifdef MUSTEK_K100D_MODEL
            if(audio_volume > VOL_VALUE)
                audio_volume = DEFAULT_VOL;
#else
            audio_volume = (audio_volume<=DEFAULT_VOL)?audio_volume:DEFAULT_VOL;
#endif
        #ifdef CNTR_5SPK_VOLUME

                volume_5SPK[i]      = audio_volume;//VOL_VALUE; //set to maximum volume
                if(i==0)//wangfeng 2003-11-03 15:33
                idVolume_5SPK[i]    = Volume_Font_ID;
                else
                idVolume_5SPK[i]    = VOL_FL_ID+i-1;
            } //for
            audio_volume  = volume_5SPK[0] ;
            volume_Switch = 0;     //set to main volume
        #endif
        }
        #elif 0//defined(RECODE_VOL_INFO)
        int iRst=ReadFromI2c(0xa0,I2C_ADDR_VOL_INFO,(BYTE *)&audio_volume,1);
        if(iRst!=1)
            audio_volume=DEFAULT_VOL;
        #else //VOLUME_RECODE
            #if 1//def  ROTARY_VOL_HUAJIA1251
            audio_volume  = DEFAULT_VOL;//VOL_VALUE;   //set to maximum volume
            #else
            audio_volume  = VOL_VALUE;
        #endif
        #endif //VOLUME_RECODE
    #else
        //ti_set_volume(SET_TOTAL_VOLUME,TI_VOL_VALUE);
        ti_set_volume(SET_ALL_VALUE);//2002 0918
    #endif

    #if 0 //def TAS3001_AMP  // jason mark 2-10-5 16:29
        //  tas3001_vol   = TI_VOL_VALUE;//2002 0918
        iBalance=10;
        ti_set_volume(SET_TOTAL_VOLUME,TI_VOL_VALUE);//2002 0918
    #endif

    #ifdef TAS5026_AMP
    tas5026_vol   = TI_VOL_VALUE;
    iBalance=10;
    #endif
}


/* The main initial function  */
static inline void VCD_init()
{
    psd_state = PSD_PLAY_TRACK;          //for cdda vcd1.0 &1.1
    psd_st.psd_list_id = 0xffff;
    #ifdef SUPPORT_ALL_CDDA_DISCS_REPEAT//chenzhao20060206
    if(rep_mode == REPEAT_ALL_DISCS)
    {
        playmode_sel(CLEAR_ALL);
        rep_mode = REPEAT_ALL_DISCS;
    }
    else
    #endif
    playmode_sel(CLEAR_ALL);
}

#ifdef PLUS_VR_AUTH_PLAYBACK
#define RSAT_BUFF_SA        (SDRAM_BASE_UNCACHED+10337*1024)         /* 32K 1 ECC Block         */
const BYTE *p_RSAT=(BYTE*)(RSAT_BUFF_SA);
//#include "InterCPU.h"
#include "RecorderMessageIf.h"
#include "atapi_s.h"

#endif


//
// FUNCTION
// ReadCDTitle
//
// DESCRIPTION
// reading DISC information.
//
#define RES_OK          0
#define RES_OPEN        -1
#define RES_NODISC      -2
#define RES_POWEROFF    -3

int ReadCDTitle(void)
{
    extern  UINT8   DiscType;
    int Res;

#ifdef PLUS_VR_AUTH_PLAYBACK
    UINT32 rsat_start_address; 
    bDVDplusVR=0;
#endif

    cd_type_loaded=CDUNKNOWN;

    // check status
    if (CDOpened()) return RES_OPEN;
    if(system_state==SYSTEM_POWER) return RES_POWEROFF;

    // setup interrupt-mask
    SetIntrMask(INTR_MASK_READTOC);

    // READTOC
    pbcoff();
    play_state = VCD_STATE_READTOC;

    #ifdef DVD_SERVO
    Res=read_toc();
    #endif

    #ifdef PLUS_VR_AUTH_PLAYBACK
    //if (AtapiGetMediaType_S() == -1)
        AtapiUnInit_S();        //Should Be in Ircmd_Eject?
    
    if (AtapiInit_S() == -1)
        return -1;
    
    if (DiscIsIncomplete&&ATAPI_DISC_IS_R_SERIES()&&ATAPI_DISC_IS_DVD_SERIES()/*&& FileSystemIsUDF*/)
    {
        #if 0
        if(PlusVRLoadRSAT()<0)
        {
            printf("%s, PlusVRLoadRSAT() fail!\n", __FUNCTION__);
            return -2;
        }
        #else
        rsat_start_address = AtapiGetNextWritableSector_S()-3*16;
        printf(" rsat_start_address:%d %d\n", rsat_start_address,DiscIsIncomplete);
        AtapiReadBlock_S(rsat_start_address,3,p_RSAT);
        #endif
    }
    
    disc_init();
    
    if(ATAPI_DISC_IS_DVD_SERIES())
        cd_type_loaded = CDDVD;

#else

    disc_init();
#endif

    if (!is_user_opened())
    {
        //if (cd_type_loaded != CDDVD)
        if ( (cd_type_loaded != CDDVD) || ( (cd_type_loaded==CDDVD) && (dVMG_LSN==0) ) ) //add more DVD-video checking, Jeff 20031124
        {
            get_disc_info();

            VCD_init();

            #ifndef DVD_SERVO
            Res=read_toc();
            #endif

            #ifdef DVD_SERVO
            if( (Res>=0)||(DiscType == CDDVD) )
            #else
            if(Res>=0)
            #endif
            {
                Res=check_cdtype();
#ifdef SYSMAIN2_DBG
                if (cd_type_loaded != CDDVD) {
                    printf("check_cdtype:after disc_init, DVD xxx, dVMG_LSN=%x\n", dVMG_LSN);
                } else {
                    printf("check_cdtype:after disc_init, DVD ooo, dVMG_LSN=%x\n", dVMG_LSN);
                }

                printf("check_cdtype:Res=%d, cd_type_loaded=%x\n", Res, cd_type_loaded);
#endif//SYSMAIN2_DBG
                disc_time=M2I(gettrkmsf_leadout()); //terry 891004
                if(cd_type_loaded!=CDDVD)//terry,2003/8/7 03:57PM
                save_cmp_disc_info(disc_time);
            }
        }else
        {
            Res=RES_OK;
        }
    }

    if (is_user_opened())
        Res =  RES_OPEN;
#ifdef SUPPORT_CD_TEXT
    else
        read_cd_text();
#endif

#ifdef IC_8202L//nono add.2006-9-9 1:04 compile error.
extern UINT8 buffer_switching_enable;
#endif

#ifdef DIP_CFG_ENABLE
    SetDeInterlace(dip_sel);
    dip_enable = 1;
#else
    dip_enable = 0;
#endif

    if( (cd_type_loaded==CDVCD10)&&( (cd_trk_hi<1)||(cd_trk_hi>100) ) )
    {//terrry,2003/12/30 11:00AM
        printf("toc err\n");
        cd_trk_hi = 1;
        cd_type_loaded=CDROM;
    }

    return Res;
}



UINT8 is_test_unit(void)//2001/10/23
{
    //if(no_disk_cnt!=DETECT_TIMES&&no_disk_cnt!=0)
    //if((no_disk_cnt!=DETECT_TIMES&&no_disk_cnt!=0 )||(atapi_p_mechanism_status()==2))      //he qiang,4-2-11 1:07,avoid displaying "CLOSE" when should show "LOAD" on VFD when a poor disc is put in.
    //if((no_disk_cnt!=DETECT_TIMES&&no_disk_cnt!=0 )||(atapi_p_mechanism_status()==2)||(atapi_p_mechanism_status()==1))      //he qiang,4-2-11 10:23,avoid displaying "CLOSE" when should show "LOAD" on VFD when a poor disc is put in.
    if(((no_disk_cnt!=DETECT_TIMES&&no_disk_cnt!=0 )||(atapi_p_mechanism_status()==ATAPI_DOOR_CLOSE)||(atapi_p_mechanism_status()==ATAPI_ERROR))
        #ifdef SUPPORT_OP_FIVE_DISC //chenzhao 2006-4-20 10:59 .
            && multidisc_loader_close_end()
        #endif    
        )      //he qiang,4-2-11 10:25,avoid displaying "CLOSE" when should show "LOAD" on VFD when a poor disc is put in.
        return TRUE;
    else
        return FALSE;
}



void close_tray_init(void)
{

#ifdef SCALER_6500	
#ifdef SUPPORT_LOADER_OPEN_TV_SYSTEM
/* 
** while loader is open, then we reset load_is_open
** for SPHE6500, this parameter will automatically change format
*/
extern BYTE load_is_open;
            load_is_open = 0;
#endif
#endif
	
    #if 1//def WHEN_READTOC_AUTO_EXIT_SETUPPAGE//nono open it.5-4-29 0:44
        if((full_scrn&SETUP) || (full_scrn&CUSTM))
        {
            ExitSetupPage(1);   //dingzhy for tonic auto close setup menu 2004-2-5 2:40
        }
    #endif

    OSD1000ISP_STATUS(OSDISP_READ, OSDIR_GLOBAL);

    regs0->reset2|=  (0x01<<8);//axelchen 2005/3/24 resolve TEAC DVD+RW disc
    regs0->reset2&= ~(0x01<<8);

#ifdef SHOW_DVDDVB_STATUS        //sunzhh add 20050927
    osd_init();
#endif

    PrintOsdMsg(STR_OS_READ,REGION1,0,0);
    sys_cmd=(CMD_FUNC|CMD_FUNC_CLOSE);
    CDSetStop();
    play_state=VCD_STATE_CLOSE;
    no_disk_cnt=DETECT_TIMES;

#if defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)//liweihua add 20031223
    if(!(card_plug_state&USER_DO_PLUG_OUT)){
        printf("ENTER COLSE TRAY INIT!\n");
        card_plug_state |= USER_DO_PLUG_IN;
    }
#endif
}

#ifdef POWER_ON_SERVO_STOP//hongfeng 2006/2/24
static BYTE need_power_on_servo = 1;
#endif

void test_atapi_drv_rdy(void)
{
    int test_ready_ret;
    #ifdef STOP_LOADER_WHEN_NO_DVD_MODE
    static int stop_load_flag = 1;
    #endif  //#ifdef STOP_LOADER_WHEN_NO_DVD_MODE
    UINT8 door;

    test_ready_ret=atapi_p_test_unit_ready();//start up loader
    
    #ifdef POWER_ON_SERVO_STOP//need delay more time hongfeng add 2006/2/24
    if(need_power_on_servo)//hongfeng add 2006/2/20
        delay_srv_10ms(80); //
    else
        delay_srv_10ms(15); //hongfeng 2006/2/20 open/close don't need delay so long time
    #else
    delay_srv_10ms(15); //
    #endif

    door = atapi_p_mechanism_status();
    if( door==ATAPI_DOOR_CLOSE )
    {
        //tray close
        #ifdef SYSMAIN2_DBG
        printf("cnt: %x\n",no_disk_cnt);
        #endif

        #ifdef POWER_ON_SERVO_STOP//hongfeng add 2006/2/24
        #ifdef SUPPORT_RECEIVER
        if((current_rcvr_mode == RECEIVER_MODE_DVD)&&(need_power_on_servo == 1))//hongfeng modify 2006/2/16
        #else
        if(need_power_on_servo == 1)
        #endif
        {
            printf("...do load servo...\n");
            atapi_p_start_stop_unit(Immed_1,START_STOP_DO_LOAD);//hongfeng add 2006/2/8
            need_power_on_servo = 0;
            #if defined(WAIT_SERVO_FLAG)&&defined(MULTIDISC_LOADER)//chenzhao 2006-3-23 21:41 .
            {
                BYTE i=0;
                do
                {
                    delay_srv_10ms(1);
                    i++;
                    //printf_w("_0x%x_P %d ",cIDEStatus,i);
                }
                while(cIDEStatus==BIT_BSY && i<120);
            }
            #endif
        }
        #endif//#ifdef POWER_ON_SERVO_STOP

        #ifdef STOP_LOADER_WHEN_NO_DVD_MODE  //yangli,2006-2-23 11:31
        if(stop_load_flag)
        {
            delay_srv_10ms(100); //
            atapi_p_start_stop_unit(Immed_1,START_STOP_DO_LOAD);//
            stop_load_flag = 0;
            #ifdef MODE_SWITCH_DELAY///YANGLI ,2006-2-22 23:18
               mode_key_delay_cnt = 13;
            #endif
        }            
        #if !defined(AFTER_UPGRADE_TRAYOUT) && defined(TRAY_AVAILABLE)
            #ifdef RESET_AFTER_UPGRADE
            {
                volatile int *iMagic = (int *)(DATA_RAM_BASE|0x80);
               if (*iMagic == 0x1881) ircmd_trayout();
                *iMagic = 0;
            }
            #endif//#ifdef RESET_AFTER_UPGRADE
        #endif//#if !defined(AFTER_UPGRADE_TRAYOUT) && defined(TRAY_AVAILABLE)
        #endif//#ifdef STOP_LOADER_WHEN_NO_DVD_MODE  //yangli,2006-2-23 11:31

        if(no_disk_cnt==0)
        {
            close_tray_init();
        }
        else if(no_disk_cnt==1)
        {
            #ifdef HOBO_DVD //Jefftest 20020930
            if (test_ready_ret != 2)
                play_state=VCD_STATE_CLOSE;
            else
            #endif
                play_state=VCD_STATE_IDLE;

            #ifdef NODISC_SHOW_IN_DIFF_REGION
            nodisc_osd_init();
            #endif
          set_system_state(SYSTEM_NODISC);

            #ifdef DEBUG_WHEN_QUICKLY_PRESS_SETUP_OSD_FLOWER//////////yangli ,2006-2-28 22:37
                counter_down = 10; 
            #endif 
            #ifdef FILE_MODE_WRITE//added by wangwei,2005-1-9 16:13
            detect_CD = 0;
            #endif//FILE_MODE_WRITE


        }else
        {//test
            no_disk_cnt--;
            if(test_ready_ret==0)//unit is ready or not
            {
                // set feature
                #ifdef SYSMAIN2_DBG
                printf("system read title\n");
                #endif

                #ifdef TONIC_DVD
                if((full_scrn&SETUP) || (full_scrn&CUSTM))
                {
                ExitSetupPage(1);   //dingzhy for tonic auto close setup menu 2004-2-5 2:40
                }
                #endif

                #ifdef SHOW_DVDDVB_STATUS           //sunzhh add 20050927
                osd_init();
                #endif
                
                OSD1000ISP_STATUS(OSDISP_READ, OSDIR_GLOBAL);

                PrintOsdMsg(STR_OS_READ,REGION1,0,0);

                drv_do_set_features();

                if(!is_user_opened())
                {
                    #ifdef FILE_MODE_WRITE//added by wangwei,2005-1-9 16:21
                    printf("detect_CD = %x\n",detect_CD);
                    detect_CD = 1;
                    #endif//FILE_MODE_WRITE

                    set_system_state(SYSTEM_READ_TITLE);
                    no_disk_cnt=0;

                    extern UINT8 old_cd_type;   //2004/10/01 yltseng, set this value in order to let hostx_servo_buf_init() really reconfig/clear data
                    old_cd_type=0xff;
                }

            }
            //else if((test_ready_ret==ATAPI_NO_MEDIA)&&(no_disk_cnt>1)&&!CDOpened())//NO disc
            else if(((test_ready_ret==ATAPI_NO_MEDIA)||(test_ready_ret==ATAPI_MEDIA_UPSIDE_DOWN)||(test_ready_ret==ATAPI_UNKNOWN_MEDIA)\
                                ||(test_ready_ret==ATAPI_ILLEGAL_MODE))&&(no_disk_cnt>1)&&!CDOpened())//zhongshan modified 05/01/17 if media err ,will not show "play" for a long time.
            {
                if(no_disk_cnt>NO_DISC_TIMES)
                {
                    no_disk_cnt-=NO_DISC_TIMES;
                }else {
                    no_disk_cnt=1;
                }
            }
         }
    }else if( door==ATAPI_DOOR_CLOSE_ERR )//terry 2003-7-31 0:55
    {
//         printf("~~~~~~~~~~~open~~~~~~~~~~:%x\n",door);
//         gbCloseTrayFail=0;//terry 2003-7-31 0:55
	#ifdef TOP_DOOR_LOADER
         ircmd_trayout();
	#else
		//#ifdef EASTECH_DVD	//wsf add for eastech can't auto close or open door,When meet bar
			//winking.J marked for other customer could used
			#ifdef TRAYIN_TRAYOUT_ABNORMITY_STATE_ADJUST //winking.J  add 2006-3-2 11:48
			if(play_state==VCD_STATE_CLOSE)
			{
			ircmd_trayout();	
		}
		else if(play_state==VCD_STATE_OPEN)  //winking.J we forget the OPEN state. 2006-3-2 11:05
        {
            ircmd_trayin();
            }
		#else
         ircmd_trayout();
		#endif
	#endif
	
	
    }else
    {

        no_disk_cnt=0;
        #if defined( NO_DVD_SERVO)&&!defined(DVD_SERVO) //ycwen 2004/08/10
            set_system_state(SYSTEM_NODISC);
        #else

        #ifdef FILE_MODE_WRITE//added by wangwei,2005-1-9 16:21
        printf("detect_CD = %x\n",detect_CD);
        detect_CD = 1;
        #endif//FILE_MODE_WRITE

            no_disk_cnt=0;
        #endif
    } //if(atapi_p_mechanism_status()==2)
}


//terry,2003/8/14 12:22AM
void power_on_gpio_demute(int demute)
{
    if( power_on_mute&&((system_state==SYSTEM_NODISC)||(demute)) )
    {//terry,2003/8/14 12:10AM
      if(system_state==SYSTEM_NODISC) AUDIF_Init_CDDA();//2004AUDDRV init_cdda();//terry,for bbk

      power_on_mute=0;

      #ifdef POWER_ON_MUTE_MIC   //axel 2004/2/26 04:10pm mute mic during initialization
      AUDIF_Set_MICVol(mic_volume);//2004AUDDRV AudioSetMICVol(mic_volume);
      #endif

     #ifdef ALCO_PDVD_NO_DTS//Jack added 05/05/31 for DTS CDDA "pop" noise!          
     if((coding_mode_now!=AUDIF_CODING_MODE_DTSCD) && (cd_subtype!=CD_DTS))
     #endif
      GPIO_DEMUTE();
     setup_SetSPDIFConfig();//2003-8-15 20:56 for avoid SPDIF noise when power on.
    }
}


/*
CheckRecordKey
CheckDiscParentLvl
Maoyong 2004.03.05 move to IR_VFD\rsm_util.h
 */


//
// interface setup
//
#if defined(SPHE8202_CARD_STORAGE)
//#define  SPHE8202_216PIN  //wthsin,    2004/2/23 10:49am
//#define  SPHE8202_256PIN  //wthsin,    2004/2/23 10:49am
extern void Card_gpio_init();
void setup_8202_card_storage_interface()
{
   #if defined(CARD_SETUP_TYPE_1)||defined(CARD_SETUP_TYPE_2)
    regs0->sft_cfg7 = regs0->sft_cfg7 | 0x2;    // Set FM 256-PIN package
    regs0->fm_gpio_mode = 8;                    // Set FM GPIO TABLE to ALL IN ONE case
    regs0->fm_gpio_len  = 12                    // Set FMGPIO_B[41:0] turn on
                        |  (0xf << 4);          // Set FMGPIO_B[41:0] enable
   #elif defined(CARD_SETUP_TYPE_3) ||defined(CARD_SETUP_TYPE_5)
    regs0->sft_cfg7 = regs0->sft_cfg7 & (~0x2);    // Set FM 256-PIN package
        #ifdef HDMI_SMC_CLE//for HDDVD Non CF config.chenzhao on 2004-12-1 21:27
        regs0->fm_gpio_len  = 10
                            |  (0xf << 4);          // Set FMGPIO_B[26:0] enable
        #else
    regs0->fm_gpio_len  = 11                    // Set FMGPIO_B[26:0] turn on
                        |  (0xf << 4);          // Set FMGPIO_B[26:0] enable
        #endif//HDMI_SMC_CLE
   #elif defined(CARD_SETUP_TYPE_4)
    regs0->sft_cfg7 = regs0->sft_cfg7 & (~0x2);    // Set FM 256-PIN package
    regs0->fm_gpio_len  = 3                    // Set FMGPIO_B[5:0] turn on
                        |  (0x1 << 4);          // Set FMGPIO_B[5:0] enable
    //regs0->gpio_mode_B=0;
   #endif
    Card_gpio_init();    //wthsin,  2004/3/24 04:55pm
}
#endif

#if defined(SUPPORT_CARD_STORAGE)
void setup_card_storage_interface()
{
    if(regs0->stamp==1)               //Version-B ,wthsin 10/18
        regs0->pcmcia_iorw_wait = 0x2222;   // Must be 0x2222 in 8200B, setup and hold time for both ior, iow is 0xf,
     else
        regs0->pcmcia_iorw_wait = 0xffff;
    regs0->wait_cyc1_0 = regs0->wait_cyc1_0 | 0x3f00; // maximum cs timing for R_CS2_B
    regs0->wait_cyc3_2 = regs0->wait_cyc3_2 | 0x003f; // maximum cs timing for R_CS3_B
}
#endif


#if defined(SUPPORT_USB)&&defined(HOST_SL811HS) //wthsin, 2004/1/12 01:36pm
void setup_usbhost_sl811hs_interface()
{
    regs0->oe_wait_cyc1_0=regs0->oe_wait_cyc1_0|0x3200;
    regs0->we_wait_cyc1_0=regs0->we_wait_cyc1_0|0x3200;
    regs0->wait_cyc1_0 = regs0->wait_cyc1_0 | 0x1f00; // maximum cs timing for R_CS2_B
    regs0->rom1_base = 0x100;       // rom2 n*64k-base ,pcmcia
    regs0->rom2_base = 0x160;       // rom2 n*64k-base ,pcmcia
    regs0->rom3_base = 0x200;       // rom3 n*64k-base ,pcmcia
    regs0->rom_config = 0x7000;   // pcmcia,rom2,3
}
#endif


//
// setup supporting for extra interfaces
//
void
init_extra_interface() //terry,2004/2/18 10:12AM
{
#if defined(SPHE8202_CARD_STORAGE)
    setup_8202_card_storage_interface();
#elif defined(SUPPORT_CARD_STORAGE)
    setup_card_storage_interface();
#elif  defined(SUPPORT_USB)&&defined(HOST_SL811HS) //wthsin, 2004/1/12 01:36pm
    setup_usbhost_sl811hs_interface();
#endif
}


#ifdef SUPPORT_8202_DVB //Maoyong 2005-5-25 13:22
void dvb8202_startup(void)
{
    //#ifdef SUPPORT_ANTENNA_POWER_CONTROL////xiaopeng 2006-7-31 19:23
	//BYTE sel = 0;
	//#endif
    #ifdef EEPROM_FLASH_STORE_INFO//shenyj add 2006/05/12
        eeprom_flash_store_info_flag=1;
    #else
        eeprom_flash_store_info_flag=0;
    #endif
    
    Demux6600HwInit();  //must place befor turner_init
    #ifndef SUPPORT_TUNER_POWER_ONOFF
    tuner_init();
    #endif
    #ifdef SUPPORT_NEWDB//Yvonne_051005
    PM_DBInit();        
    #endif  
    
    FtaInit();
    dmx_6600_init();
    OpenTDT(5);
    // Houyiwu 4/18/2005 to adjust error concealment for London562.ts           
    #ifdef ERROR_CONCEALMENT
    setup_error_counter_limit(ERROR_MB_LIMIT_NUM);
    setup_error_concealment(ERROR_CONCEALMENT_MODE);
    #endif//ended by houyiwu 4/18/2005

    #if !defined(NOT_RECORD_DVB_DVD_STATE)
    BYTE dvd_dvb_staus=0;
    ReadFromI2c(0xa0,I2C_ADDR_DVD2DVB_FLAG,&dvd_dvb_staus,1); 
    if(dvd_dvb_staus!=0)
    {
        DVD2DVB_switch_flag = 1; 
        #ifdef SHOW_DVDDVB_STATUS           //sunzhh add 20050927
        show_DvdDvbSwitch_status(DVD2DVB_switch_flag);
        #endif 
        printf("####dvb_check_media_switch####\n");
       	//set_system_state(SYSTEM_TS);//not necessary!Jack mark 05/12/01
        dvb_state_servo_stop();
        #if defined(IR_SWITCH_DVD_USB_CARD_AVIN_DVB)&& !defined(NOT_RECORD_DVB_DVD_STATE)
        source_play_mode = DVB_T_MODE;
        #endif
    }
    //else
    #endif
    
    #ifdef SUPPORT_DVB_BOOKING
    volatile int *iMagic=(int *)(DATA_RAM_BASE|0xa0);
        if((*iMagic<MAX_BOOKINFO_ITEM)&&(*iMagic >= 0))
    {
        DVD2DVB_switch_flag = 1; 
        #ifdef SHOW_DVDDVB_STATUS           //sunzhh add 20050927
        show_DvdDvbSwitch_status(DVD2DVB_switch_flag);
        #endif 
        printf_w("####*iMagic = %d ####\n",*iMagic);
       	set_system_state(SYSTEM_TS);
        dvb_state_servo_stop();
        #if defined(IR_SWITCH_DVD_USB_CARD_AVIN_DVB)&& !defined(NOT_RECORD_DVB_DVD_STATE)
        	source_play_mode = DVB_T_MODE;
    	#endif    
    }
    #endif    
    
        #ifdef SUPPORT_TUNER_POWER_ONOFF
        tuner_power_control(0);
        #endif

    demux_gpio_reset();
    #ifdef SUPPORT_ANTENNA_POWER_CONTROL//xiaopeng 2006-9-4 13:06
    ReadFromI2c(0xa0, I2C_ADDR_ANT_POWER_CTRL, &gAntSelPower, 1);    
    setting_ant_power_control(gAntSelPower);
    #endif
}
#endif

#ifdef MINUS_VR_AUTH_PLAYBACK
extern INT8 bDVDminusVR;		//Gary
#endif

#ifdef  SUPPORT_DVB_DESKTOP_STOP_SERVO_WHEN_TUNEON  ///YANGLI ADD FOR STOP SERVO,2005-12-28 15:00
int stop_servo_flag=0;
#endif 

void dvd_startup(void)//20040316
{

#ifdef SUPPORT_DVB_BOOKING
extern void load_current_time(void);
    load_current_time();
    printf_w("=========================123==================================\n");
#endif 

#if (defined(SUPPORT_8202_DVB)&&!defined(NOT_RECORD_DVB_DVD_STATE))||defined(POWER_ON_ENTER_DVB)//Jack added 05/12/01 because in DVB state we have better not to post command to servo DSP
    if(DVD2DVB_switch_flag)
    {
        disc_time = 0xefff;
        #ifdef SHOW_DVDDVB_STATUS
        show_DvdDvbSwitch_status(DVD2DVB_switch_flag);
        #endif
        AVD_ResetMediaStatus();
        ClearCommand();
        set_system_state(SYSTEM_OPEN);
        power_on=2;
        #ifdef SUPPORT_DVB_DESKTOP_STOP_SERVO_WHEN_TUNEON  ///YANGLI ADD FOR STOP SERVO,2005-12-28 15:00
        atapi_p_start_stop_unit(Immed_1,START_STOP_DO_STANDBY);
        stop_servo_flag = 1;
        #endif 
        
        #if defined(POWER_ON_ENTER_DVB)
        atapi_p_start_stop_unit(Immed_1,START_STOP_DO_STOP);
        #endif
        
        #ifdef SUPPORT_DVD_POWER_ONOFF
        dvd_power_onoff(TURN_OFF);
        #endif
    }
    else
#endif
//if(DVD2DVB_switch_flag) else
{

#ifdef PULIANG_EJECT_MODE    //yaowh add for puliang 04-12-17
    BYTE    I2c_Data;
    BYTE    I2C_Clear=0;
#endif
    
    #ifdef SUPPORT_DVD_POWER_ONOFF
    dvd_power_onoff(TURN_ON);
    #endif
        
    disc_time = 0xefff;//terry 891004

    #if defined(PAL_VERSION)&&defined(UNLOCK_STATE_NOT_CHECK_PASSWD)
    disc_has_unlock = 0;
    #endif
    
   

    #ifdef TOP_DOOR_LOADER
        #ifdef SUNPLUS_8202P_DEMOBOARD
        regs0->sft_cfg4 &= ~((0x03)<<2);    //Enable GPIO2,3 For COVER & TFT SW
        #endif
        bDoorStatus = GPIO_GET_DOOR_STATUS();
        if (bDoorStatus==DOOR_OPEN) {
            OSD1000ISP_STATUS(OSDISP_OC_OPEN, OSDIR_OPEN);

            PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);
            //SERVO_LDOff();//maybe use it.
            //SERVO_STSledHome();//maybe use it.
            ircmd_trayout();
            play_state=VCD_STATE_OPEN;
        } else {
            #ifdef PAL_VERSION
            PrintOsdMsg(STR_OS_READ,REGION1,0,0);
            #endif

            ircmd_trayin();
            play_state=VCD_STATE_CLOSE;
        }
    #else
        #ifdef PULIANG_EJECT_MODE  //yaowh add 04-12-17
        ReadFromI2c(0xa0,0xfc,&I2c_Data,1);
        if((I2c_Data==0x80))
        {
            call_ir_func(IRC_EJECT);
            WriteToI2c(0xa0,0xfc,&I2C_Clear,1);
        }else
        #endif
        {
        #if !(defined(SUPPORT_8202_DVB)||defined(PMP_UI))
        #ifndef DIRECT_ACCESS_MEDIA//added by wangwei,2005-11-21 13:27, for power on no show "READ"
        PrintOsdMsg(STR_OS_READ,REGION1,0,0);
        #endif//DIRECT_ACCESS_MEDIA
        #elif defined(SHOW_DVDDVB_STATUS)        //sunzhh add 20050927
        show_DvdDvbSwitch_status(DVD2DVB_switch_flag);
        #endif
        play_state=VCD_STATE_CLOSE;
        }
    #endif //#ifdef TOP_DOOR_LOADER

    #ifdef  REPEAT_RESET_IOP //zhaoyanhua add 2004-2-13 13:59  //fengjl edit 2004-02-27 15:49
    //only for DSS 555(VFD Driver: NEC 16312)
    //This vfd is very strange! When power switch between on and off
    //more than 20 times, it will not show VFD informaiton again!
    //we found it that the data which IOP send to 16312 is abnormal,
    //so reset IOP here.
    reset_iop();
    reset_ir();
    reset_vfd();
    #endif //ifdef REPEAT_RESET_IOP

    #if defined(CE2746)||defined(CE2766)
    init_ce2746();
    #endif
    
    #ifdef CE2826
    init_ce2826();
    #endif
    
    #ifdef AV2808
    init_av2808();
    #endif
    
    //
    // CONTROL FLOW
    //
    AVD_ResetMediaStatus();
    ClearCommand();

    no_disk_cnt=DETECT_TIMES;

    set_system_state(SYSTEM_OPEN);

    sys_cmd=CMD_FUNC|CMD_FUNC_CLOSE;
    power_on=2;
    #ifdef SUPPORT_SYS_POWER_ON_WAITING_MCUINFO 
    if((source_play_mode==USB_PLAY_MODE)||(source_play_mode==CARD_PLAY_MODE))
    {
	  atapi_p_start_stop_unit(START_STOP_DO_STOP);
    }
    #endif//end=> #ifdef  SUPPORT_SYS_POWER_ON_WAITING_MCUINFO

	
}//if(DVD2DVB_switch_flag) else
    #ifdef MULTIDISC_LOADER//chenzhao20060107
    reset_multidisc_state();
    #endif
}



#ifdef SUPPORT_RECEIVER
#include "sysmain_receiver.c"  //huziqin 2004-3-12
#include ".\\receiver\\receiver.c"  /*2006-4-19 huziqin*/
#endif

#ifdef SUPPORT_TESTSPK //jiangxl 2005-5-24 10:01
#include "TestSpk.c"
#endif


#ifdef SUPPORT_POWER_OFF_CLOCK_FUNC  //xyy 2004-10-11 17:18
#include "clock_func.c"
#endif

#ifdef MULTIDISC_LOADER  //chenzhao 20060111
#include "multidisc_loader.c"
#endif

//
// FUNCTION
// ap_main()
//
// DESCRIPTION
// Application main function
//

static inline void apmain_dbg_in()
{
#ifdef SYSMAIN2_DBG
    if(old_state!=system_state)
    {
        old_state=system_state;
#ifndef IR_TOOL
        printf("[%s,in][play_state:%x][sys_cmd:%x][cd_type:%x]\n",
            system_state_str[system_state],play_state,sys_cmd,cd_type_loaded);
#endif
    }
#endif
}

static inline void apmain_dbg_out()
{
#ifdef SYSMAIN2_DBG
    if(old_state!=system_state)
    {
        old_state=system_state;
#ifndef IR_TOOL
        printf("[%s,out][play_state:%x][sys_cmd:%x][cd_type:%x]\n",
            system_state_str[system_state],play_state,sys_cmd,cd_type_loaded);
#endif
    }
#endif
}


#ifdef DVB_SETUP
UINT8 eBuffer[128];
void SP_SetVolume(UINT8 volume);

static inline void apmain_dvb_setup()
{
    int i;
    for(i=0;i<128;i++)  eBuffer[i]=0xff;
    watchdog_onoff(0);//disable watchdog
    for(i=0;i<128;i++)
        ReadFromI2c(0xa0, i, &eBuffer[i] ,1);

    watchdog_renew(0xffff);//reset watchdog
    watchdog_onoff(1);//enable watchdog
}
#endif

#ifdef  AUTO_ADJUST_TV_TYPE  //lijd 2004-9-15 13:27
extern BYTE  Adjust_TV_type ;
#endif


#ifdef SUPPORT_MIDI           //xlluo 2004-12-28
#include "fsmidi.h"
#ifdef SUPPORT_MIDI_MENU_SEL
#include "fsmidiui.h"
#endif
#endif


// QSI
#ifdef QSI_SHOW_ERR_RATE
#include "sysmain2_QSI.c"
#endif

#ifdef QSI_SUPPORT_SLOT_TEST
#include "sysmain2_qsislot.inc"
#endif

//
// AUDIO
static inline void apmain_audio_init()
{
    delay_srv_10ms(30);
    // set default audio coding-mode
    AUDIF_Set_CodingMode(AUDIF_CODING_MODE_DEFAULT);
#ifdef POWER_ON_MUTE_MIC  
    AUDIF_Set_MICVol(0);//2004AUDDRV AudioSetMICVol(0);
#endif

#ifdef  MIC_2CHANNEL        //gerry add it for setting mic vol,2004-7-6 9:34
    #include "dsp3_if.h"
    AUDIF_Set_MICVol2(setup_GetMICVol2()-2);//2004AUDDRV AudioSetMICVol_2(setup_GetMICVol2()-2);
    AUDIF_Set_MICVol(setup_GetMICVol()-2);//2004AUDDRV AudioSetMICVol(setup_GetMICVol()-2);
#endif


// add by Steven 2006/4/10 avoid SPDIF silent when MIC ON/OFF switch continuously//
#ifdef NO_MIC
	AUDIF_Set_MICSupport(MIC_NOT_SUPPORT);
#else
	AUDIF_Set_MICSupport(MIC_SUPPORT);
#endif





}


//
// OSD
static inline void apmain_osd_init()
{
#if SUPPORT_OSD
    #ifdef  DYNAMIC_SPECTRUM    //zhaoyanhua add 2003-12-4 9:26
    if(bEqDisplay) {
        Show3dspectrum();
        return;
    }
    #endif
    osd_init();
#endif
}


//
// SCREEN SAVER
//
static inline void apmain_test_screen_saver()
{
    int do_safe_srn_off = 0;

#ifdef SLOT_IN_LOADER
    if ((system_state>=SYSTEM_READ_TITLE)) do_safe_srn_off=1;
#elif defined(SETUP_CAN_ENTER_SAFECREEN) 
    if ((system_state >= SYSTEM_READ_TITLE) || (play_state == VCD_STATE_CLOSE)/*||(full_scrn & SETUP)||(full_scrn & CUSTM)*/)
    do_safe_srn_off=1;
#else
    #if defined(SDRAM_16Mb_Mode)&&!defined(SETUP_CAN_ENTER_SAFECREEN)
    #define FSCRN_MASK  (SETUP|CUSTM|PROGRAM)
    #elif   defined(GPS_DVD)
    #define FSCRN_MASK  (SETUP|CUSTM|TOUCH_MENU|TOUCH_KEYBOARD)
    #elif   defined(SUPPORT_FUNCTION_MENU)
    #define FSCRN_MASK  (SETUP|CUSTM|SETUP_PLUS)
    #else
    #define FSCRN_MASK  (SETUP|CUSTM)
    #endif
        if ((system_state>=SYSTEM_READ_TITLE)
          || (play_state==VCD_STATE_CLOSE)
          || (full_scrn & FSCRN_MASK))
            do_safe_srn_off=1;
#endif

    if (do_safe_srn_off)
    {
        safe_srn_off();
    }
    else
    {
        #ifdef SDRAM_16Mb_Mode      
        if (cd_type_loaded==CDDVD)
        {
                psprintf(RegionValStr[REGION1], "");
                PrintOsdMsg(STR_OS_SPACE,REGION1,1,0);
        }
        #endif
        safe_srn_on();
    }
}


//
// USER code step #0
static inline void apmain_user_step0()
{
}


//
// USER code step #1
static inline void apmain_user_step1()
{
#if defined(SUPPORT_8202D_EXT_ADC)&&defined(EXT_ADC_RESET)
    GPIO_O_SET(EXT_ADC_RESET,0);  //chyeh 2005-08-20
#endif

#ifdef SUPPORT_UNICODE_FONT //joshua 2005/9/2
    char2uni_translation = char2uni_cp950;
    uni_subtitle_language = 0;
#endif
    #ifndef STOP_LOADER_WHEN_NO_DVD_MODE///yangli,2006-3-31 14:42
    #if !defined(AFTER_UPGRADE_TRAYOUT) && defined(TRAY_AVAILABLE)
        #ifdef RESET_AFTER_UPGRADE
        {
            volatile int *iMagic = (int *)(DATA_RAM_BASE|0x80);
            #ifdef MULTIDISC_LOADER
            if (*iMagic == 0x1881) multidisc_loader_power_on_eject();
            #elif defined(AFTER_UPGRADE_POWER_OFF)//add by hongfeng 2006/3/8
            if (*iMagic == 0x1881) ircmd_power();
            #else
            if (*iMagic == 0x1881) ircmd_trayout();
            #endif
            *iMagic = 0;
        }
        #endif//#ifdef RESET_AFTER_UPGRADE
    #endif//#if !defined(AFTER_UPGRADE_TRAYOUT) && defined(TRAY_AVAILABLE)
    #endif//#ifndef STOP_LOADER_WHEN_NO_DVD_MODE///yangli,2006-3-31 14:42


#ifdef GBM_DEFAULT_NTSC_CAPTION_OFF         //gerry,2004-2-13 14:18
    tv_l21_enable(0);
#endif//GBM_DEFAULT_NTSC_CAPTION_OFF

    #ifdef SUPPORT_UART_COMMAND
    Inform_MCUOK();
    #endif

    #ifdef TONIC_DVD
    ReadFromI2c(0xa0,ADDR_I2C_TRAY_PWD,&KeyLockStatus,1);//nono 20050812 add macro
    if(KeyLockStatus!=0&&KeyLockStatus!=1)
    {
        KeyLockStatus=0;
        WriteToI2c(0xa0,ADDR_I2C_TRAY_PWD,&KeyLockStatus,1);//nono 20050812 add macro
    }

    {
        regs0->sft_cfg1  &=  ~(0x1<<2);  //  CS3  as GPIO3|
        GPIO_M_SET(36,1);
        GPIO_E_SET(36,0);
    }
    #ifdef SUPPORT_VFD_SHOW_P_SCAN
    vfd_show_p_scan();
    #endif
    #endif//#ifdef TONIC_DVD

#ifdef JPEG_EXP_RATIO               //terry,2004/2/6 04:24PM
    vpp_set_expansion_ratio(14*8);
#endif

#ifndef SUPPORT_EXT_MCU //xyy add 2004-11-17
#ifdef SUPPORT_EXT_ADC//xyy 2004-4-12
    GPIO_O_SET(EXT_ADC_RESET,1);
#endif
#endif

#if defined(SHINCO_DVD)
    GPIO_O_SET(16,0);
#endif

#ifdef DVB_SETUP
    apmain_dvb_setup();
#endif

#ifdef PMP_DVD  //wthsin add for PMP  2004/11/8
    PMP_ENABLE=1;
#endif //#ifdef PMP_DVD
    #ifdef SUPPORT_TOPPOLY_UPS051_Digital_panel
    init_toppoly_digital_panel();
    #endif
    #ifdef SUPPORT_Auo_2inch_Digital_panel
    init_auo_digital_panel();
    #endif
    #ifdef SUPPORT_Auo_UPS053_Digital_panel
    init_auo_ups053_digital_panel();
    #endif
    #ifdef SUPPORT_Auo_UPS018_Digital_panel
    init_auo_ups018_digital_panel();
    #endif
    #ifdef TCON_DRIVER_EL8332
    reset_tft();
    #endif
    #ifdef SUPPORT_Auo_A070FW04_Digital_panel 
    init_auo_A070FW04_digital_panel();
    #endif

	#ifdef SUPPORT_VIDEO_OUT_DELAY
	tv_dacoff(TV_DAC_F|TV_DAC_E|TV_DAC_C);
	#endif
}


static inline void apmain_user_loop()
{
#ifdef QSI_SUPPORT_SLOT_TEST
    qsi_slot_test();
#endif

#ifdef EASTWIN
    regs0->sft_cfg3 |= ((0x01)<<1);    //Enable AUD0(GPIO53) fix the audio noise bug
#endif

#ifdef SUPPORT_RECEIVER //huziqin 2004-3-12;move to sysmain_receiver.c
    receiver_check_system_state();
#endif

#ifdef SUPPORT_POWER_OFF_CLOCK_FUNC  //xyy 2004-10-11
    check_system_clock_func();
#endif

#ifdef MULTIDISC_LOADER//chenzhao20060111
    check_multidisc_loader_state();
#endif 
}



//
// FUNCTION
// ap_main()
//
int     test_ready_timer;
#if (defined(SUPPORT_JKDISKSTATUS)&defined(MIDI_EJECT_PASSWORD))  //xlluo add for 05/01/05
BYTE    isMidiDisk;
#define Read_isMidiDisk
#endif

#ifdef LOGO_PLAY_MP3
BYTE    old_system_state=0;  //for mp3
BYTE    play_mp3_flag=0;
UINT16  mp3_count=0;
#endif


void ap_main(void)  // benson update 2004/3/1 04:25¤U¤È
{

    // **STEP0**
    apmain_user_step0();
    // **STEP0**

    test_ready_timer=DEV_RDY_TM;

#if defined( NO_DVD_SERVO)&&!defined(DVD_SERVO)
    servo_turn_off();
#endif

#ifdef  Read_isMidiDisk
    isMidiDisk=0; ReadFromI2c(I2C_ID_MEMORY,DISK_STATUS,&isMidiDisk,1);
#endif

    #ifdef RECORD_PER_SECOND
    resume_time_ourmind=0;
    #endif

//Disable ATAPI interface and enable CCIR656 output. Add by Kaspar, 2005/04/12    
    #ifdef CCIR656_OUTPUT
        regs0->sft_cfg3 &= ~(0x1<<5);
        regs0->sft_cfg2 |= (0x1<<7);
        printf("Disable ATAPI and enable CCIR656 Output\n");    
    #endif

#ifdef SUPPORT_POWER_OFF_CLOCK_FUNC         //xyy 2004-10-12
    Pcf8563Init();
#endif

#ifdef SUPPORT_8202_DVB 
    dvb8202_startup();   
#endif

#ifdef SUPPORT_SYS_POWER_ON_WAITING_MCUINFO 
waiting_mcu_info();
#endif//end=> #ifdef  SUPPORT_SYS_POWER_ON_WAITING_MCUINFO


    // APMAIN level AUDIO setup
    apmain_audio_init();

    // Initialize other interfaces
    init_extra_interface();

    // initialize servo
    init_srv_test_mode();//terry,2003/9/10 12:17AM

    play_state=VCD_STATE_POWER;
    
    // initialize audio volume
    volume_init();

    //include tuner/amp/mic
    #include "sysmain2_inc.h"

    // APMAIN level OSD setup
    apmain_osd_init();
    
// Simon:  Receiver-related code here
// Receiver does not have to start in DVD mode
#ifdef SUPPORT_RECEIVER
    receiver_startup();
#else
    dvd_startup();
#endif

    // **STEP1**
    apmain_user_step1();
    // **STEP1**

#ifdef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-5-16 14:36
    #if !defined( NO_DVD_SERVO)||defined(DVD_SERVO)
    media_status = STATUS_DISC;
    #else	// !defined( NO_DVD_SERVO)
    media_status = STATUS_CARD;
    #endif	!defined( NO_DVD_SERVO)
#endif//DIRECT_ACCESS_MEDIA
    
#ifdef SUPPORT_SYS_POWER_ON_WAITING_MCUINFO 
	waiting_mcu_info2();
#endif//end=> #ifdef  SUPPORT_SYS_POWER_ON_WAITING_MCUINFO


#ifdef SUPPORT_TVG		//linrc add...because TVG need us display TVG information 5 time 2005-12-15 15:43
extern void ShowTVG_INFO_UI(void);
	ShowTVG_INFO_UI();
#endif
    
    // AP main loop
    while (1)
    {
        // polling 
        polling();

        // **USER LOOP**
        apmain_user_loop();
        // **USER LOOP**

#ifdef ALWAYS_DEFAULT_DIR_REPEAT
        rep_mode=REPEAT_DIRECTORY;//wangap 2005-4-5 15:24
#endif
        
        test_mode_chk_close_tray();                 // Tray
        apmain_test_screen_saver();                 // Screen saver
        apmain_dbg_in();                            // Debug Message

#ifdef LOGO_PLAY_MP3
        logo_play_mp3();
#endif

        // AP state machine
        switch(system_state)
        {
#ifdef PMP_DVD                          //wthsin add for PMP  2004/11/8
            case SYSTEM_PC_USB_MODE:
                pc_usb_access_mode(); break;
#endif
            case SYSTEM_NODISC:                 // No disk
                apmain_state_nodisc(); break;

            case SYSTEM_OPEN:                   // Opened
                apmain_state_open(); break;

            case SYSTEM_STOP:                   // Stopped
                apmain_state_stop(); break;

            case SYSTEM_READ_TITLE:             // Reading disc title
                apmain_state_read_title(); break;

            case SYSTEM_SETUP_BROWSER:          // Setup used browser.
                apmain_state_setup_browser(); break;

            case SYSTEM_BROWSE:                 // Start to browse.
                apmain_state_browse(); break;

            case SYSTEM_FINISH:                 // System playback finished.
                apmain_state_finish(); break;

            #ifdef SUPPORT_DVD_NATIVE_GAME      //linrc for NATIVE_GAME 2005-10-18 13:55
            case SYSTEM_DVDGAME:  
                Dvb_PlayGame(); break;	
            #endif

#if defined(SUPPORT_8202_DVB) && !defined(TEST_DVD)
            case SYSTEM_TS:                     // TS
                dvb_navigation(); break;

            #ifdef SUPPORT_DVB_NATIVE_GAME      //added by tbdong in 20050622
            case SYSTEM_DVBGAME:  
                Dvb_PlayGame(); break;	
            #endif	
#endif

#ifdef QSI_SHOW_ERR_RATE
            case SYSTEM_QSI_PIPO_TEST:
                psprintf(linebuf,"SYSTEM_QSI_PIPO_TEST> play_stste=%x\n", play_state);
                UART0_puts(linebuf);
                if(QSI_PIPO_FLAG) {
                    QSI_PIPO_routine();
                }
                break;
#endif

#ifdef AV_IN_THROUGH_EXT_ADC
            case SYSTEM_AVIN:
                apmain_state_avin();
                break;
#endif
        } //switch(system_state)

        apmain_dbg_out();

    } //while (1)
}


#ifdef AV_IN_THROUGH_EXT_ADC
// AVIN
static inline void apmain_state_avin()
{
    play_state = VCD_STATE_NORMAL;
    set_system_state(SYSTEM_AVIN_DOING);
        
    AUDIF_Reset_DSP();
    AUDIF_Init_DSPCodingMode();            
    AUDIF_Set_SampleRate(FS_44K);
    AUDIF_Set_CodingMode(AUDIF_CODING_MODE_TUNER);
    AUDIF_Set_Echo(0,0);
        
    GPIO_DEMUTE();
    
    //swith audio to AV IN 
#if defined(MUSTEK_K100D_USE_SOME_6600_GPIO)&&!defined(PLAY_IN_SUNPLUS_PORTABLE_6600_DEMO_BOARD)
    //control 74HC4052(6600 GPIO12 and GPIO13 output 0)
    DMX_GPIO_E_SET(AV_IN_4052_CTL_GPIO1,1);
    DMX_GPIO_O_SET(AV_IN_4052_CTL_GPIO1,0);
    DMX_GPIO_E_SET(AV_IN_4052_CTL_GPIO2,1);
    DMX_GPIO_O_SET(AV_IN_4052_CTL_GPIO2,0);
#endif
        
    //swith video to AV IN
    enable_video_DAC_out(0);
                
    while(system_state == SYSTEM_AVIN_DOING)
    {
        polling();
#ifdef SUPPORT_8202_DVB
        dvb_check_media_switch();
        if (Is_Dvb_State()) break;
#endif
        system_check_media_switch();
    }
    
    avd_idle_state();//Added it 05/11/10,otherwise when enter DVB state,then enter game...... 
}
#endif

        

//terry,2004/2/6 04:23PM
//move do syc job function to other file


//benons move  ap_main_receiver() 2004/3/1 03:22¤U¤È

//wanghaoying move to higui\backup.c 2005-1-18 20:09

//Maoyong 2004.05.14 moved here
#ifdef PROVIEW_GPIO_KEY
void set_proview_gpio_key(void)
{

    #ifdef PROVIEW_GPIO_KEY_527
    GPIO_E_SET(EJECT_KEY_GPIO, 0);      //IN GPIO[5] OPEN
    //GPIO_E_SET(PREV_KEY_GPIO, 0);     //IN GPIO[4] PREV
    GPIO_E_SET(PAUSEPLAY_KEY_GPIO, 0);      //IN GPIO[18] PLAY
    GPIO_E_SET(STOP_KEY_GPIO, 0);       //IN GPIO[17] STOP
    //GPIO_E_SET(NEXT_KEY_GPIO, 0);     //IN GPIO[16] NEXT
    #else
    GPIO_E_SET(EJECT_KEY_GPIO, 0);      //IN GPIO[5] OPEN
    GPIO_E_SET(PREV_KEY_GPIO, 0);       //IN GPIO[4] PREV
    GPIO_E_SET(PAUSEPLAY_KEY_GPIO, 0);      //IN GPIO[18] PLAY
    GPIO_E_SET(STOP_KEY_GPIO, 0);       //IN GPIO[17] STOP
    GPIO_E_SET(NEXT_KEY_GPIO, 0);       //IN GPIO[16] NEXT
    #endif
}
#endif


/*********************************************************************
 * call this function for card/cd switch process in special system state
 * Maoyong 2004.05.18 changes for consideration of USB card reader.
 *********************************************************************/
#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
#ifndef DIRECT_ACCESS_MEDIA//added by wangwei,2005-11-15 14:15
void system_check_media_switch(void)
{

    #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
    if( !(((usb_card_state==HAS_USB_AND_SWITCH_TO_USB)&&(detect_type&USB_DEVICE))||(usb_card_state==HAS_CARD_AND_SWITCH_TO_CARD)) )
        return;
    #endif

    if(system_state == SYSTEM_STOP)
    {
        //check whether card is plugged in
        if ( IsCardMediaExist() && (card_plug_state&USER_DO_PLUG_IN)//liweihua mod 2004-3-10
        //#if defined(CF_CARD_WRITE)|| defined(SPHE8202_FAT_Write_Function)//||defined(WRITE_USB)
        // && read_card_sign       //xulf
        //#endif
           )
        {
            #ifdef SUPPORT_STOP_PLAY_READ_USB_CARD //qinhua ,2005-10-24 12:59
        	  if(!media_change_flag_mark)
        	  {
        	    CardTestReady();
        	   media_change_flag_mark = 1;
              }
             
          #endif  	  
            //#ifndef SUPPORT_USB//Maoyong 2004.05.18 for USB carder consideration
            //CardTestReady();
            //#endif  //#ifdef SUPPORT_USB
            //Maoyong 2004.05.25. now use OPEN cmd and switch meida in SYSTEM_OPEN,just for wirte
        #if defined(CF_CARD_WRITE)|| defined(SPHE8202_FAT_Write_Function)//||defined(WRITE_USB)
            if( read_card_sign && (media_type == MEDIA_CARD) && (MediaIsEmpty == MEDIA_NOT_EMPTY))  //modefied by wangwei,2004-11-19 17:31(for storage no files screen refresh problem)
            {
                CardTestReady();
            }
        #endif
        
            #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB 
            if((usb_card_state==HAS_USB_AND_SWITCH_TO_USB) || (usb_card_state==HAS_CARD_AND_SWITCH_TO_CARD))
                CardTestReady();
            #endif
        
        }
        else if(!IsCardMediaExist())
        {
            #if defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
            polling_storage();   //polling_U_Disk(); //wthsin,2004/4/12 02:16pm
            #else
            polling_card_plug();//kenny 2003/1/26
            #endif
            drv_do_set_features(); //card plug out, do set feature to loader

           #ifdef SUPPORT_STOP_PLAY_READ_USB_CARD  //qinhua ,2005-10-24 12:59
           if ((media_change_flag)&&(!uhci_PlugInOutDetect()))
           #endif   
          {
            //if((card_plug_state&USER_DO_PLUG_OUT)&&(media_type == MEDIA_CARD))
            if(media_type == MEDIA_CARD)    //Maoyong 2004.05.18 for USB card reader consideration
            {
                SwitchMedia(CARD2CD);       //this will do more actions
             }
            media_type = MEDIA_CD;
        }
    }
    }
    else if(system_state == SYSTEM_OPEN)
    {
        if ((card_plug_state&USER_DO_PLUG_IN)&&CARDIsPlugIn()//liweihua mod 2004-3-10
        #if defined(CF_CARD_WRITE)|| defined(SPHE8202_FAT_Write_Function)//||defined(WRITE_USB)
           && read_card_sign       //xulf
        #endif
        )
        {
            //if(play_state == VCD_STATE_CLOSE)//liweihua add 2004-2-1
            {
                //8200 card power on run and 8202 cd to card switch will come here by CMD_FUNC_OPEN cmd
                if(media_type == MEDIA_CARD)
                {
                    //Maoyong 2004.05.25
                    #ifdef CARD_PLAY_STOP_LOADER
                        run_close_tray(1);
                    #endif
                    #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
                    CardTestReady();
                    #else
                    if(MediaIsEmpty == MEDIA_NOT_EMPTY)  //modefied by wangwei,2004-11-19 17:31(for storage no files screen refreshing problem)
                    CardTestReady();
                    else
                        media_type = MEDIA_CD;
                    #endif    
                }
            }
        }
        else
            media_type = MEDIA_CD; //Jeff 20020726


        #ifdef SP1000_NO_DVD
        set_system_state(SYSTEM_NODISC);
        #endif //#ifdef SP1000_NO_DVD

        #ifdef SUPPORT_SLOT_IN_LOADER
        if( IsCardMediaExist() )//Maoyong 2004.05.18 for USB card reader consideration
        {
            CardTestReady();
        }
        #endif
        
        #ifdef SUPPORT_OPEN_READ_USB_CARD //caoh 2005-8-31 9:54
            #if defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)    
                if(!media_change_flag)
                 if((detect_type)&&(media_type==MEDIA_CD))
                 {
                   SwitchMedia(CD2CARD);
                 }
            #endif
        #endif 
    }
    else if(system_state == SYSTEM_NODISC)  //no disc switch to card when card exist s
    {
        //if( (safe_on==0) && CARDIsPlugIn())
        if( IsCardMediaExist() )//Maoyong 2004.05.18 for USB card reader consideration
        {
            if(MediaIsEmpty == MEDIA_NOT_EMPTY)  //modefied by wangwei,2004-11-19 17:31(for storage no files screen refreshing problem)
            {
                #if 0 //def HOST_UHCI wthsin,05/03/23
                uhci_reset(); // for Hot Plug-In/Out. but this function have been implementd above.
                #endif
                CardTestReady();
            }
        }
    }
}
#endif//DIRECT_ACCESS_MEDIA
#else
void system_check_media_switch(void)    {}
#endif  //#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)


//==============================================
// for QSI disc\card switch \\added by JS   \\20040727
#ifdef SUPPORT_QSI_SOURCE_SWITCH
void system_check_source_switch(void)
{
    if(source_switch_flag) //  source switched
    {
        #if defined(QSI_PORTABLE_DVD) && defined(QSI_PLATFORM) //qsi: modify by johnson 20040812
            if(source_type_now == source_card)
            {
                SwitchMedia(CD2CARD);
            }
            else if(source_type_now == source_disc)
            {
                SwitchMedia(CARD2CD);
            }
        #else
            if(source_type_now == source_card)
            {
                CardReset();
                sys_cmd = (CMD_FUNC|CMD_FUNC_CLOSE);
            }
            else if(source_type_now == source_disc)
            {
                sys_cmd = (CMD_FUNC|CMD_FUNC_OPEN);
            }
        #endif

        set_system_state(SYSTEM_NODISC);
        play_state = VCD_STATE_IDLE;
        cd_type_loaded = CDUNKNOWN;

        source_switch_flag = 0;
    }
    else  // source has not switched
    {
        if((source_type_now == source_card) && (!CARDIsPlugIn()))
        {
            sys_cmd = (CMD_FUNC|CMD_FUNC_CLOSE);
            set_system_state(SYSTEM_NODISC);
            play_state = VCD_STATE_IDLE;
            cd_type_loaded = CDUNKNOWN;
        }
    }

}
#else
void system_check_source_switch(void)   {}
#endif


// BROWSE
static inline void apmain_state_browse()
{
    int continue_run_nav,mode,cmd;

#if defined(IR_SWITCH_DVD_USB_CARD_AVIN_DVB)
    GPIO_DEMUTE();
#endif
    
#ifdef USE_AMP_MUTE
if(!user_amp_mute)
    sub_masterMute(AMP_DEMUTE);
#endif

// recover tv resolution from CSS tv resolution. by robert.chang, 2006-09-01
#ifdef SUPPORT_HD_RESOLUTION
    #ifdef USE_SETUP_ITEM_ENABLE_FLAG
    extern UINT8 setup_VA_EN[MAX_SETUP_VA];
    #endif
    extern void setup_SetHD(void);
    extern void setup_SetPScan(void);
    extern void str_os_hd_720p(void);
    extern void str_os_hd_1080i(void);
    extern int tv_resolution_switch;
    extern int prior_tv_resolution;
    
    if( (tv_resolution_switch) && (!CSSEnable)){
        tv_resolution_switch = 0;
        
        if(prior_tv_resolution != GET_TV_RESOLUTION()) {
            if(prior_tv_resolution == HD_720){
                setup_VA_EN[SETUP_VA_VIDEO] = 2;
                str_os_hd_720p();                
            }
            else if(prior_tv_resolution == HD_1080){
                setup_VA_EN[SETUP_VA_VIDEO] = 2;                
                str_os_hd_1080i();                  
            }    
            setup_SetHD();              
            setup_SetPScan();        
        }
    }
#endif

#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
    if ((usb_card_state==HAS_USB_AND_SWITCH_TO_USB)
      ||(usb_card_state==HAS_CARD_AND_SWITCH_TO_CARD))
        usb_card_state = USB_CARD_NO_CHANGE;
#endif
#ifdef NODISC_SHOW_IN_DIFF_REGION//shenyj 0914 for usb&card osd show
            #if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
            if(media_type != MEDIA_CD)
            {
                osd_init();
            }
            #endif
#endif
#ifdef PORTABLE_POWER_ON_MUTE
    regs0->sft_cfg3 |=((0x01<<6));//CHENZZ FOR LRCK=1.for power on noise.
#endif
#ifdef ROM_EXT_POWER_ON_MUTE
rom_bus_set_io(ROM_BUS_OUT_AMP_MUTE,0);
#endif

#ifdef SUPPORT_LINE_OUT_MUTE	
			set_line_out_demute_flag(2);
#endif

#ifdef SHOW_TRK1_AFTER_READED_DISC
            disp_trk_now = 1;
#endif

#ifdef QSI_SHOW_ERR_RATE
    if(QSI_PIPO_TEST==0x1){
        if(QSI_PIPO_FLAG) {
            QSI_PIPO_routine();
        }
        return;
    }
#endif

#ifdef LOGO_PLAY_MP3
    play_mp3_flag=0;
#endif

#if defined(SUPPORT_CARD_STORAGE)
                    if ( (media_type==MEDIA_CARD) && CARDIsPlugIn() ) {
                        if(play_state == VCD_STATE_CLOSE)//liweihua 2004-2-1
                        CardTestReady();

                        memset(pFsJpeg, 0, sizeof(FSJPEGDATA));//liweihua mark 2004-1-31
                        //axel clear mark for HJ card reader 2004/4/30 08:52pm
                    }
#endif

		  #ifdef SDRAM_16Mb_Mode //zhongshan for mp3 stop return refresh 2006.07.24
		  if(
		     (cd_type_loaded == CDROM)
#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
		     &&(media_type != MEDIA_CARD)
#endif
		    )
		  {
		  	do
		  	{
		  	}while( ran_read(pwb, l2msf(0), 1024)!=ATAPI_OK);
		  }
		  #endif

                if(browser == read_iso9660) {
                    LoadModual(MODUAL_CDROM);
                }

                #ifdef TEST_SERVO//terry,2003/9/10 12:42AM
                if((iTestServoMode==1)||(iTestServoMode==3))
                   srv_test_mode_play();
                else
                #endif
                browser();

                #ifdef SUPPORT_INSIDE_GAME
                play_inside_game=0;
                #endif

                #ifdef SYSMAIN2_DBG
                printf("brower out,sys_cmd:%x play_state:%x\n",sys_cmd,play_state);
                printf("system_state=%x\n", system_state);
                #endif

                continue_run_nav=0;
                mode=GET_CMD_MODE();
                cmd=GET_CMD_SELECT();

                if(bPbcOff && ((cd_type_loaded==CDVCD20)||(cd_type_loaded==CDSVCD)) )
                {
                    cd_trk_lo_now   = cd_trk_lo + 1;
                    if(cd_trk_now>cd_trk_hi || cd_trk_now<cd_trk_lo_now)
                    {   /*prevent change mode(pbc on->pbc off)&FF/FB from startup timeout*/
                        bPbcOff = 0;
                    }else
                        continue_run_nav=2;

                }else if(mode==CMD_SELECT)
                {
                    continue_run_nav=2;
                }
                else if (mode==CMD_FUNC)
                {
                    if( (cmd==CMD_FUNC_GOTO)||(cmd==CMD_FUNC_PRG)||(cmd==CMD_FUNC_RESUME))//2-4-26 14:41
                        continue_run_nav=2;
                    else if(cmd==CMD_FUNC_PBC)
                        continue_run_nav=1;
                }

                if(continue_run_nav)
                {
                    cd_trk_lo_now   = cd_trk_lo + 1;
                    if(!IsPBCOn())
                    {
                        browser = v11_navigation;

                        if(continue_run_nav==1)
                            ClearCommand();
                    }
                    else
                    {
                        browser = psd_navigation;
                    }
                }
               else
                {
#if defined(CF_CARD_WRITE)|| defined(SPHE8202_FAT_Write_Function)//||defined(WRITE_USB)
            if(!flag_cf2cd&&!flag_cd2cf)           //xulf
#endif
                    set_system_state(SYSTEM_FINISH);
#if defined(CF_CARD_WRITE)|| defined(SPHE8202_FAT_Write_Function)//||defined(WRITE_USB)
            else                                                 //xulf
            {
            }
#endif
    }
}


// FINISH
static inline void apmain_state_finish()
{
#ifdef SUPPORT_OSDID3//liweihua 2004-1-9 11:18
    if(Is_MP3_STATE()) osd_init();
#endif
#ifdef ALCO_DVD_UI
    if(!((browser==read_iso9660) && !pFsJpeg->iso9660_file_cnt))
#endif
    if(cd_trk_lo!=0xff)  //jhuang 2000/11/16
        stop_init();

    if(GET_CMD_SELECT() == CMD_FUNC_POWER)
        state_stop_navigation();      //jhuang add it 891010
    else
    {
        #ifdef NO_FILES_OR_UNSUPPORT_NOT_SHOW_FSGUI_AND_SHOW_NODISC
                    if((cd_type_loaded==CDROM) && Mp3ReadFinish && (!pFsJpeg->iso9660_file_cnt)
                    #ifdef NOT_SUPPORT_MP3
                    ||(pFsJpeg->iso9660_file_cnt>pFsJpeg->gifsMP3Count)
                    #endif
                    )
                    {
                        system_state = SYSTEM_NODISC;
                        play_state = VCD_STATE_IDLE;
                        cd_type_loaded = CDUNKNOWN;
                        //PrintOsdMsg(STR_OS_NODISC,REGION1, 1, 0);
                    }    
                    else
        #endif
        set_system_state(SYSTEM_STOP);
#ifdef NEWSTYLE_WINDOW   //xyy  3-7-23 13:32
        if(full_scrn==MESSAGE)
        {
#if defined(BBK_DVD)&&defined(DISC_INFO_KEY)  //fengjl edit 2004-04-22 15:00
            ircmd_disc_info();
#else
            ircmd_goto();//exit goto mode
#endif
        }
#endif
        ShowTitle();
    }

    if(GET_CMD_SELECT() != CMD_FUNC_OPEN && GET_CMD_SELECT() != CMD_FUNC_CLOSE) /*jhuang add CMD_FUNC_CLOSE 891018*/
    {
        ClearCommand();//terry,2003/9/6 07:06PM
#ifdef STOP_LOADER  //terry,2003/9/1 05:34PM
        stop_loader();
#endif
    }
    else
    {
        flush_atapi();//terry,0515,let data tranfer finish
    }

    #ifdef SUPPORT_8202_DVB
    dvb_check_media_switch();
    #endif
#ifdef ALCO_DVD_UI
                if((browser==read_iso9660) && !pFsJpeg->iso9660_file_cnt)
                {
                    #ifdef SHOW_SPECIAL_DISC_TYPE
                    read_disc_state = 0xf0;
                    no_disk_cnt = 1; 
                    play_state = VCD_STATE_IDLE;
                    cd_type_loaded = CDUNKNOWN;
                    #ifdef NODISC_SHOW_IN_DIFF_REGION
                    nodisc_osd_init();
                    #endif
                    #endif
                    system_state = SYSTEM_NODISC;
                }
#endif

#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
    #ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
        printf_w("!!!--->usb_card_state:%d........source_play_mode:%d\n",usb_card_state,source_play_mode);
    #endif
                
    #ifdef AV_IN_THROUGH_EXT_ADC
        if(usb_card_state == FROM_CARD_TO_AV_IN)
        {              
            #ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
            printf_w("card play state sw to AVIN............\n");
            #endif
            set_system_state (SYSTEM_AVIN);
            usb_card_state = USB_CARD_NO_CHANGE;
        }
        else 
    #endif
        if(usb_card_state == USB_CARD_WAS_PLUG_OUT)
        {
            #ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
            printf_w("USB/CARD is plug out when in play state............\n");
            #endif
            usb_card_state = USB_CARD_NO_CHANGE;
            cd_type_loaded = CDUNKNOWN;
            play_state = VCD_STATE_IDLE;
            full_scrn = 0;     
            ClearOsdMsg(0);     
            t_disp = 0;
            osd_init();
            media_type = MEDIA_CARD;
        }
#endif//end #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB            
}

#ifdef    SUPPORT_OTHER_LANGUAGE_STRING
extern    const char *const osd_other_str[N_OSD_LANGS][STRINE_NUM];
#endif //end=> #ifdef    SUPPORT_OTHER_LANGUAGE_STRING

// STOP
static inline void apmain_state_stop()
{
    state_stop_navigation();
    
    #ifndef DIRECT_ACCESS_MEDIA//added by wangwei, for no auto switch media.
    system_check_media_switch();    //Maoyong 2004.05.14
    #endif//DIRECT_ACCESS_MEDIA

#ifdef SUPPORT_POWER_OFF_CLOCK_FUNC  //xyy 2004-10-11
    if(switch_to_clockmode == 1)
    {
        set_system_state(SYSTEM_MODE_CLOCK_FUNC);
    }
#endif

// Simon 12-16-2003
// If this code isn't in SYSTEM_STOP, sometimes user will have to hit the button twice
// before mode switch actually occurs (switching from DVD mode).
// This occurs because there are cases when system doesn't properly go to
// the OPEN state after ejecting (eg: ejecting right before VCD menu appears).
                #ifdef SUPPORT_RECEIVER
                  if (switch_modes_now == 1)
                  {
                    // Fix startup problem
                    // Make sure loader is stopped before switching
                    //while (play_state == VCD_STATE_POWER)
                    //{
                    //  printf("PS %d\n", play_state);
                    //  play_state = VCD_STATE_OPEN;
                    //}
                    set_system_state(SYSTEM_MODE_CHANGE);
                  }
                #endif

                system_check_source_switch();//for QSI disc/card switch //added by JS   //20040726

                #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
                if(usb_card_state == SWITCH_TO_USB_BUT_HAS_NO_USB)
	            {
	       	  		#ifdef    SUPPORT_OTHER_LANGUAGE_STRING
					psprintf(RegionValStr[REGION1], osd_other_str[osd_font_mode][USB_NOT_FOUND]); 
		     		#else //else => #ifdef    SUPPORT_OTHER_LANGUAGE_STRING	 
	       	        psprintf(RegionValStr[REGION1], "USB NOT FOUND");
		     		#endif//end=> #ifdef    SUPPORT_OTHER_LANGUAGE_STRING	

	                PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
	                play_state = VCD_STATE_IDLE;
	                system_state = SYSTEM_OPEN;
	            }
	            else if((usb_card_state==USB_CARD_WAS_PLUG_OUT)/* && (MediaIsEmpty==MEDIA_EMPTY)*/)
                {
                    #ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
                    printf_w("USB/CARD is plug out when USB/CARD has no files or in stop state\n");
                    #endif
                    usb_card_state = USB_CARD_NO_CHANGE;

                    if(pFsJpeg->iso9660_file_cnt)//Jack added 06/02/16
                    {
                        cd_type_loaded = CDUNKNOWN;
                        play_state = VCD_STATE_IDLE;
                        full_scrn = 0;     
                        ClearOsdMsg(0);     
                        t_disp = 0;
                        osd_init();
                    } 
                }
                #endif
}


// SETUP BROWSER
static inline void apmain_state_setup_browser()
{

#if 0//def SUPPORT_LINE_OUT_MUTE	//chenzhao marked.20060419
                    mute_line_out();
                    sub_masterMute(AMP_MUTE);           
#endif            

#ifdef LOGO_PLAY_MP3
    play_mp3_flag=0;
#endif

#if defined(USE_GAMEPORT_TO_DISCLIGHT)
    check_light_status();
#endif

#ifdef SHOW_DOUBLE_LOGO  //zxb 2005-7-29 0:02                          
    ShowTitle();                            	             
#endif

#ifdef DVD_SERVO
#ifdef CSWDP_0
    cServoWrongDataPass = 0;
#else
    cServoWrongDataPass = 1;
#endif
#endif

#ifdef FORCE_SKIP_VCD_MOSAIC//nono 4-5-5 12:38 for hyoptics VCD mosaic issue.
    setup_error_concealment(0);//(ERROR_CONCEALMENT_MODE);  // detect error and skip
#endif//#ifdef FORCE_SKIP_VCD_MOSAIC


    // enable watchdog (default)
    watchdog_renew(0xffff); // reset watchdog
    watchdog_onoff(1);      // enable watchdog

    if(cd_type_loaded==CDDVD)
    {
        // DVD (DVD-VIDEO/DVD-AUDIO)
#ifdef BAD_DISC_SEQ_PLAY
        bad_disc_seq_play = 1;//terry,2003/8/29 02:16AM
#endif
#ifdef MINUS_VR_AUTH_PLAYBACK
	//Added By Gary for DVD -VR Navigation
	if(bDVDminusVR)
		browser =DVD_Minus_VR_Navigation;
	else
#endif
        browser = dvd_navigation;
    #ifdef DISPLAY_PLAY_WHEN_GO_INTO_PLAY
                    if((!prog_cnt) && (!resumeMSF))
                        PrintOsdMsg(STR_OS_PLAY,REGION1,2,0);
                    #endif
                    #ifdef UNLOCK_STATE_NOT_CHECK_PASSWD
                    if(UserSet.parental_ststus == 1)
                        disc_has_unlock = 2;
      #endif
    }
    else if(cd_type_loaded==CDROM)
    {
        // CDROM (FS9660/UDF)
                
                    #ifdef ROMCODE_SKIP_CDROM //yarco   
                    {
                        pDVB->cd_type_loaded = CDROM;
                        //psprintf(RegionValStr[1], "ISO-9660");
                        //PrintOsdMsg(72, 1, 0, 1);
                        set_system_state(SYSTEM_FILESTREAM);
                        play_state=VCD_STATE_STOP;
                    
                        //Linux need to stop DVD mode, then romcode can disable romcode OSD and loader
                        return;
                    }   
                    #endif  
                    #ifdef SUPPORT_OSDID3
                    osd_init_OSDID3();
                    #endif
                    #if defined(AUDIO_2CH_5_1CH)&&defined(SUPPORT_PROLOGIC_II)//axel modified 2004/3/16 10:53am zhaoyanhua add 2003-12-17 9:47
                    //if MP3/WMA/MPG, must turn off PROLOGIC II.
                    if(setup_IsSpkDownmixOff())
                        AudioSet2chOutput();
                    #endif
                    // disable watchdog (default)
                    watchdog_onoff(0);

                    bInitPlayTrk=0;/*jhuang 891005 add,MP3 ignore bInitPalyTrk while tray open*/
                    browser = read_iso9660;
                    cd_trk_now = 1;// 2-6-13 23:40
                }else if(cd_type_loaded==CDDA)
                {
#if (defined(SUPPORT_JKDISKSTATUS)&defined(MIDI_EJECT_PASSWORD))  //xlluo add for 05/01/05
                    {
                        printf("WriteI2c(I2C_ID_MEMORY,DISK_STATUS,0x00,1)\n");
                        WriteI2c(I2C_ID_MEMORY,DISK_STATUS,0x00,1);
                    }
#endif

                    #ifdef CD_PLAYER    //liweihua 2003-9-3
                    ShowTitle();
                    ClearOsdMsg(3);
                    show_cdplayer();
                    #ifdef VIRTUAL_KEYBOARD//liweihua 2003-9-18
                    ClearOsdMsg(4);
                    osd_draw_virtual_keyboard(0,0,4);
                    hl_keyboard_button(KeyID);
                    full_scrn |= KEYBOARD;
                    #endif
                    #endif

                    // disable watchdog (default)
                    watchdog_onoff(0);

                    AUDIF_Init_CDDA();//2004AUDDRV init_cdda();

                    #if defined(SUPPORT_CDG)||defined(SUPPORT_CD_TEXT)
                    #ifdef SUPPORT_ECC
                    RS42Init();
                    RS2420Init();
                    #else
                    extern int Generate_Gf();
                    Generate_Gf();
                    #endif
                    #endif

                    cd_trk_lo_now   = cd_trk_lo;
                    browser = v11_navigation;
                     #ifdef DISPLAY_PLAY_WHEN_GO_INTO_PLAY
                    if((!prog_cnt) && (!resumeMSF))
                        PrintOsdMsg(STR_OS_PLAY,REGION1,2,0);
                    #endif
                }else
                {
                    //terry,2004/3/2 12:07PM
                    //Maoyong, 2004/03/04 changed for VCD10 resume play of all resume definition
                    #if defined(POWER_RESUME)|| defined(SAME_DISC_RESUME)||defined (RECORD_KEY)
                    if(resumeMSF)
                    {
                        goto_active=1;//terry,2004/3/2 11:59AM
                        #ifdef VCD_PBCON_RESUME
                        if(play_state!=VCD_STATE_STOP)
                    	#endif
                        psd_st.psd_list_id = 0xffff;
                    }
                    #endif

                    #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU    //linrc add 2004-11-4 20:19
                    extern BYTE VcdControlFlag();              //when "MNP" what define in setupmenu is on
                    if(VcdControlFlag())                      //VCD & CDG play one TRK in one time....
                    psd_st.psd_list_id = 0xffff;
                    #endif

                    if (cd_type_loaded==CDVCD10)
                        psd_st.psd_list_id = 0xffff;

                    AUDIF_Init_MP3();//2004AUDDRV init_mp3();

                    if(psd_st.psd_list_id == 0xffff)
                        browser = v11_navigation;
                    else
                    {
						#ifdef VCD_PBCON_RESUME
						if((play_state!=VCD_STATE_STOP)&&(!resumeMSF))
						#endif
                        psd_st.psd_list_id = 0;  //PVD start entr
                        browser   = psd_navigation;

#ifdef FORCE_SKIP_VCD_MOSAIC//nono 4-5-5 12:38 for hyoptics VCD mosaic issue.
//#if 1//def  ERROR_CONCEALMENT
                        setup_error_mb_limit(2);//(ERROR_MB_LIMIT_NUM);        // ERROR_MB_LIMIT_NUM*16 MB default=4
                        setup_error_concealment(0x03);//(ERROR_CONCEALMENT_MODE);  // detect error and skip
//#endif////#if 1//def  ERROR_CONCEALMENT
#endif//#ifdef FORCE_SKIP_VCD_MOSAIC

                    }

                    //terry,2002/9/6 12:01PM
                    //Às¬ì,ªìÅÊ
                    cd_trk_lo_now   = cd_trk_lo;

#ifdef SUPPORT_HDD_ACCESS
                    f_browser_mode=0;
                    if (f_force_browser) {
                        printf("MIKEY_BUG: force setup browser = read_iso9660\n");
#ifdef HDD_MODIFY_INDEX_TEST
                      watchdog_onoff(0);
                      ReadFontFile();
                      watchdog_onoff(1);
#endif
                        browser = read_iso9660;
                        f_force_browser=0;
                        f_browser_mode=1;
                        f_browser_mode=cd_type_loaded;
                        cd_type_loaded = CDROM;
                        watchdog_onoff(0);
                    }
#endif //SUPPORT_HDD_ACCESS

        if (cd_type_loaded!=CDVCD10)
            cd_trk_lo_now++;
         #ifdef DISPLAY_PLAY_WHEN_GO_INTO_PLAY
            if((!prog_cnt) && (!resumeMSF))
              PrintOsdMsg(STR_OS_PLAY,REGION1,2,0);
         #endif 
    }

    set_system_state(SYSTEM_BROWSE);

    if (cd_type_loaded!=CDROM)
        play_state =VCD_STATE_NORMAL;

}


// OPEN
static inline void apmain_state_open()
{
#ifdef SCALER_6500
#ifdef DAC_6500D   
if(run_scaler)
{
scaler_6500_main();//2006-06-05,eric lin.After state_open,6500's TVDAC should be updated and h/w reset.
run_scaler=0;
}
#endif
#endif	
#ifdef SUPPORT_8202_DVB
                    dvb_check_media_switch();
                    if(Is_Dvb_State()) return;
#endif            

                #ifdef DIRECT_ACCESS_MEDIA//added by wangwei,2005-11-15 15:21
                #ifdef SUPPORT_USB
                if(media_status == STATUS_USB)
                {
                    if( (detect_type == USB_DEVICE)
                    #ifndef NO_DVD_SERVO
                    && (atapi_p_mechanism_status() != ATAPI_DOOR_OPEN)
                    #endif
                    )
                    {
                        storage_type = detect_type;
                        usb_test_ready();
                    }
                }
                #endif//SUPPORT_USB

                #ifdef SPHE8202_CARD_STORAGE
                if( (media_status == STATUS_CARD)
                #ifndef NO_DVD_SERVO
                && (atapi_p_mechanism_status() != ATAPI_DOOR_OPEN)
                #endif//NO_DVD_SERVO
                )
                {
                    #ifdef CARD_SETUP_TYPE_3
                    extern int polling_card_conflict(void);
                    if(polling_card_conflict())
                        detect_type = 0;
                    #endif//CARD_SETUP_TYPE_3
                
                    if(detect_type & MS_CARD_DEVICE)
                    {
                        storage_type = MS_CARD_DEVICE;
                    }
                    else if(detect_type & SD_CARD_DEVICE)
                    {
                        storage_type = SD_CARD_DEVICE;
                    }
                    #ifdef CARD_SETUP_TYPE_3// All in 1
                    else if(detect_type & CF_CARD_DEVICE)
                    {
                        storage_type = CF_CARD_DEVICE;
                    }
                    else if(detect_type & SMC_CARD_DEVICE)
                {
                        storage_type = SMC_CARD_DEVICE;
                    }
                    #endif//CARD_SETUP_TYPE_3

                    card_test_ready();
                }
                #endif//SPHE8202_CARD_STORAGE
                #else//!DIRECT_ACCESS_MEDIA
                system_check_media_switch();   //Maoyong 2004.05.14
                #endif//DIRECT_ACCESS_MEDIA

#ifdef PROVIEW_GPIO_KEY
                set_proview_gpio_key();
#endif

#if defined(IR_SWITCH_DVD_USB_CARD_AVIN_DVB)&&defined(AV_IN_THROUGH_EXT_ADC)
                if(usb_card_state == FROM_CARD_TO_AV_IN)
                {              
                    #ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
                    printf_w("system open state sw to AVIN............\n");
                    #endif
                    
                    set_system_state(SYSTEM_AVIN);
                    usb_card_state = USB_CARD_NO_CHANGE;
                }
#endif

                //system test drv ready
#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
                #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
                if(source_play_mode == DVD_PLAY_MODE)
                #elif defined(DIRECT_ACCESS_MEDIA)//added by wangwei, 2006-5-13 9:46
                #ifndef NO_DVD_SERVO
                if(media_status == STATUS_DISC)
                #endif//NO_DVD_SERVO
                #else
                if(media_type == MEDIA_CD)
                #endif
#endif
                {
                    if(safe_on)
                    test_ready_timer=test_ready_timer%DEV_RDY_TM_IN_SCRNER;

                    if(--test_ready_timer<0)
                    {
                        test_ready_timer=DEV_RDY_TM;
                        test_drv_rdy();
                        power_on=0;
                        power_on_gpio_demute(0);
#ifdef PUSH_TRAY_IN_DISPLAY   //chenzhao20051110
                        push_tray_in_detect();
#endif     
                    }
                    srv_test_mode1_open();
                }

#ifdef SUPPORT_POWER_OFF_CLOCK_FUNC  //xyy 2004-10-11
    if(switch_to_clockmode == 1)
    {
        set_system_state(SYSTEM_MODE_CLOCK_FUNC);
    }
#endif

// Simon 12-16-2003
// This code is in both SYSTEM_STOP and SYSTEM_OPEN
#ifdef SUPPORT_RECEIVER
    if (switch_modes_now == 1)
    {
        set_system_state(SYSTEM_MODE_CHANGE);
    }
#endif

#ifdef QSI_SHOW_ERR_RATE
    if(system_state != SYSTEM_OPEN) {
        QSI_PIPO_pre_check(SYSTEM_OPEN);
    }
#endif
}

#ifdef SCALER_6500
#include "setup_VA.h"
#include "setup_def.h"
extern const UINT8 setup_item[MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE][MAX_PAGE_ITEM+1][MAX_ITEM_SEL+1+1+1];
extern BYTE X,Y;
extern BYTE TV_SYS, TV_MODE;
extern BYTE is_tv_auto;
extern void scaler_6500_main(void);
extern void run_save_sel_cmd(BYTE value , BYTE index);
extern void exe_setup_function(UINT8 tt_id, UINT8 sub_id, UINT8 exe);
#ifdef DAC_6500D
int run_scaler;//eric lin,2006-06-05
#endif
#endif


// NODISC
static inline void apmain_state_nodisc()
{
#ifdef SUPPORT_8202_DVB
    dvb_check_media_switch();
    if(Is_Dvb_State()) return;
#endif

#if (defined(SUPPORT_JKDISKSTATUS)&defined(MIDI_EJECT_PASSWORD))  //xlluo add for 05/01/05
            if (isMidiDisk)
            {
                printf("SYSTEM_NODISC WriteI2c(I2C_ID_MEMORY,DISK_STATUS,0x00,1)\n");
                WriteI2c(I2C_ID_MEMORY,DISK_STATUS,0x00,1);
                isMidiDisk = 0;
                gIsMidiSelMenu = 0;
                midi_open_pwd_start = 0;
                midi_open_pwd_finished = 0;
            }
#endif

                // remain=0;   //wsf  2004-7-27 13:12
                //#ifdef OP_UI//zhaoyanhua add 2004-2-26 10:57
                //system_state = SYSTEM_SETTING;

                #if defined(GBM_SLOT_IN_LOADER_TEST)          //gerry,2004-2-27 19:43
                if(no_disk_cnt==1)
                {
                    no_disk_cnt=0;

                    #ifdef POWER_RESUME //Jeff 20021022
                    RsmInfo2Flash(1);//clear memory
                    #endif
                    ircmd_eject_toggle();
                }

                #else//GBM_SLOT_IN_LOADER_TEST
                if(no_disk_cnt==1)
                {
                    int id;

                    int test_ready_ret;
                    if(play_state==VCD_STATE_IDLE)
                    {
                           test_ready_ret=atapi_p_test_unit_ready();
                           if(test_ready_ret != ATAPI_NO_MEDIA)
                           {
                            OSD1000ISP_STATUS(OSDISP_ERR_DISC, OSDIR_GLOBAL);

                            id=STR_OS_ERR_DISC;//nono 2-4-22 13:26 for fuss
                           }else{
                        OSD1000ISP_STATUS(OSDISP_NODISC, OSDIR_GLOBAL);

                        id=STR_OS_NODISC;
                        
#ifdef SCALER_6500                        
                        if (setup_item[X][Y][setup_VA[SETUP_VA_TV_SYS]] == STR_OS_AUTO){  
                            setup_VA[SETUP_VA_TV_SYS] = TV_SYS; // 1214
                            run_save_sel_cmd(setup_VA[SETUP_VA_TV_SYS], SETUP_VA_TV_SYS);
                            dvi311_tv_mode = TV_MODE;
                            exe_setup_function(STR_OS_TV_SYS, TV_MODE, 1); 
                        } 
#endif                         
                    }
                    }                   //zhongshan add 05/01/17 if media err ,show "err disc"
                    else
                    {
                    #if defined(FUSS_DVD) || defined(HOBO_DVD)
                        OSD1000ISP_STATUS(OSDISP_ERR_DISC, OSDIR_GLOBAL);
                        id=STR_OS_ERR_DISC;//nono 2-4-22 13:26 for fuss
                    #elif defined(CORTROL_VCD_ONF) //wangap add 2004/5/27
                      if( (
                                (bDiscType == CD_OKO)
                                ||(cd_type_loaded==CDVCD20)
                                ||(cd_type_loaded==CDVCD10)
                                ||(cd_type_loaded==CDSVCD)
                                )
                                &&(setup_IsVCD_OFF()) )
                            {
                                OSD1000ISP_STATUS(OSDISP_ERR_DISC, OSDIR_GLOBAL);
                               #ifdef VCD_DISC_ACCORDING_REGION
                               #ifdef STOP_LOADER
                               stop_loader();
                               cd_type_loaded = CDUNKNOWN;   //Jack added 04/11/25............     
                               #endif
                               #endif
                                id=STR_OS_ERR_DISC;
                                play_state=VCD_STATE_IDLE;
                            }
                    #else

                        OSD1000ISP_STATUS(OSDISP_STOP, OSDIR_STOP);
                        id=STR_OS_STOP;
                    #endif
                    }

                     #ifdef SLOT_IN_LOADER//terry,2004/4/7 06:20PM
                     OSD1000ISP_STATUS(OSDISP_STOP, OSDIR_STOP);
                     id=STR_OS_NODISC;
                     ircmd_eject_toggle();
                     #endif

                     #ifdef SHOW_SPECIAL_DISC_TYPE
                     if(read_disc_state == 0xf0)
                     {
                       read_disc_state = 0x0f;
                       id = STR_OS_ERR_DISC;
                     }
                     #endif

                     #if defined(QSI_PORTABLE_DVD) && defined(QSI_PLATFORM) //qsi: merge by johnson 20040712
                     id=STR_OS_NODISC;
                     ircmd_eject_toggle();
                     //qsi: modify by sharon
                     #endif

                #ifdef ALWAYS_DISPLAY_NODISK     //wthsin 03/08/15; for bbk,hq,3-11-22 14:13
                      PrintOsdMsg(id,REGION1,0,0);
                #elif !defined(KENLOON_DVD) //yaowh add 04-07-30
                    #ifdef SHOW_DVDDVB_STATUS       //sunzhh add 20050927
                    osd_init();
                    #endif
                    PrintOsdMsg(id,REGION1,1,0);
                #endif

                    no_disk_cnt=0;

                    #ifdef POWER_RESUME //Jeff 20021022
                    RsmInfo2Flash(1);//clear memory
                    #endif

                    srv_test_mode1_no_disc();//terry,2003/9/10 12:52AM
                }
                #endif//#if defined(GBM_SLOT_IN_LOADER_TEST)          //gerry,2004-2-27 19:43

                #ifndef DIRECT_ACCESS_MEDIA//added by wangwei, for no auto switch media.
                system_check_media_switch();    //Maoyong 2004.05.14
                #endif//DIRECT_ACCESS_MEDIA

                // probe if there is disc in loader
                if (sys_cmd==(CMD_FUNC|CMD_FUNC_OPEN))
                {
                    set_system_state(SYSTEM_OPEN);
                    #ifdef NODISC_SHOW_IN_DIFF_REGION 
                    osd_tog_region(REGION1, OSD_OFF);//PrintOsdMsg(STR_OS_SPACE,REGION1,0,0);
                    #ifdef ALCO_PVS177W
                    delay_srv_10ms(100); // jack added 05/03/11
                    #else
                    delay_srv_10ms(30); //added 04/11/22
                    #endif
                    osd_init();
                    PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);
                    #endif
                }
}

#ifdef  CHECK_RECORD_DISK_PARENT_LVL
#ifdef SUPPORT_LAST_MEMERY
#include "setup_def.h"//xujf-modify-for-parentlvl-check_passworld_in_resume-on
//extern UINT8 setup_sel[MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE][MAX_PAGE_ITEM+1];
#endif
#endif

// READ_TITLE
static inline void apmain_state_read_title()
{
    int Res;

#ifdef SETUP_IN_READ_STATE//terry,2003/9/15 06:22PM
    if(full_scrn&SETUP) return;
#endif

#ifdef LOGO_PLAY_MP3
    play_mp3_flag=0;
#endif

    InitVar();

    EnableBuffer( TRUE );

    // clear global variables, Robert 03/04/30
    memset(pFsJpeg, 0, sizeof(FSJPEGDATA));
    LoadModual(MODUAL_CDROM);

    sys_cmd=(CMD_FUNC|CMD_FUNC_CLOSE); // robert 020917

    Res=ReadCDTitle();

#ifdef DVD_SERVO
    hostx_servo_buf_init();//correct servo buffer location
#endif

#if defined(CORTROL_VCD_ONF)      //wangap add for no support vcd 2004/5/27
    if( (
      (bDiscType == CD_OKO)
      ||(cd_type_loaded==CDVCD20)
      ||(cd_type_loaded==CDVCD10)
      ||(cd_type_loaded==CDSVCD)
      )
      &&(setup_IsVCD_OFF()) )
    {
                    Res=RES_NODISC;
    }
#endif

    switch(Res)
    {
        default:    // RES_OK
#if defined(DVD_DEFAULT_SHOW_TITLE_TIME)//hongfeng 2005-07-01
            if(cd_type_loaded==CDDVD)
                remain= DISC_TIME;
            else
                remain= 0;
#else
            remain= 0;
#endif  //DVD_DEFAULT_SHOW_TITLE_TIME

            t_disp = 0;
            if(!(bInitPlayTrk&0x01))
            {
                #ifndef ALCO_DIVX_UI      
                show_osd_disc_type();//terry,2003/12/29 08:25PM
                 #endif        
                          #ifdef SHOW_DOUBLE_LOGO  //liych  added 2005-3-23
                           if((cd_type_loaded !=CDUNKNOWN)&&(play_state!=VCD_STATE_OPEN))
                          {
                                ShowTitle();
                                 delay_srv_10ms(200);
                           }                  
                          #endif
                         
                            set_system_state(SYSTEM_SETUP_BROWSER);
                        //#endif//ifdef OP_UI
                            //Jeff 20010816
                            NP_SPSTN = 0xbf;
                            Subp_stream_Chg(1,1);
                            NP_ASTN = 0xf;
                            Audio_stream_Chg_SVCD(1);

                            //terry,2002/6/25 09:17PM
                            
                            if(cd_type_loaded==CDDVD)
                            {
                                memset(pDSV, 0,sizeof(DataSaved));
                                 #ifdef  AUTO_ADJUST_TV_TYPE
                                         Adjust_TV_type=1;
                                 #endif
                            }
							
				read_cgms();	// get cgms form CD or CDDVD, robert.chang 2006/04/04
				
                            //Maoyong 2004.03.04 23:12, move and make into functions for record resume
                            if(!CheckLoadRsmInfo())
                                break;
                            LoadRsmInfo();
                            #ifdef  CHECK_RECORD_DISK_PARENT_LVL
                                #ifdef SUPPORT_LAST_MEMERY
				if(memery_resumeflag)
				{
                                	if(!CheckDiscParentLvl())
                                	{
                                    	break;
                                	}	
				}//xujf-060629-modify-for-parentlvl-check_passworld_in_resume-on
				#else
                                  if(!CheckDiscParentLvl())
				{
                                    break;
				 }
                                #endif
                            #endif//#ifdef  CHECK_RECORD_DISK_PARENT_LVL

                            
                            
                            #ifdef SUPPORT_LAST_MEMERY		    
                            if(memery_resumeflag)
                            #endif
                                RecordRsmPlay();    //Maoyong 2004.03.04, do record resume play now

                            #if defined(POWER_RESUME)&&!defined(STOP_RESUME_DVD_VCD)    //Jack 06/10/02 added here for simply release 
				            if(cd_type_loaded != CDROM)
				                RsmInfo2Flash(0xf0);//clear memory        //zhuyf 2004/9/8 add to resolve bug:When shut down power supply, the next same type disc will do resume play
                            #endif
                     

            }else //if(!(bInitPlayTrk&0x01))
            {
                            set_system_state(SYSTEM_FINISH);
                            play_state=VCD_STATE_STOP;
                            bInitPlayTrk=0;
                            sys_cmd=0;
            } //if(!(bInitPlayTrk&0x01))
            
            break;

        case RES_OPEN:          // OPEN
        case RES_POWEROFF:      // POWER-OFF
            set_system_state(SYSTEM_FINISH);
            break;

        case RES_NODISC:        // NO-DISC
            no_disk_cnt=1;
            set_system_state(SYSTEM_NODISC);
            play_state=VCD_STATE_STOP;
                        
            #ifdef SHOW_SPECIAL_DISC_TYPE
            read_disc_state = 0xf0;
            #endif
            #ifdef NODISC_SHOW_IN_DIFF_REGION
            nodisc_osd_init();
            #endif

            break;
    } //switch(Res)

//JSlin //for QSI PIPO  //20040901
#ifdef QSI_SHOW_ERR_RATE
    QSI_PIPO_pre_check(SYSTEM_READ_TITLE);
    //psprintf(linebuf, "next SYSTEM STATE: [%d]\n", system_state); UART0_puts(linebuf);
    //psprintf(linebuf, "SYSTEM_READ_TITLE [out]\n"); UART0_puts(linebuf);
#endif
//=========================
}

#ifdef SHOW_DVDDVB_STATUS        //sunzhh add 20051018
void Dvb_DrawString(coordinate* start, const BYTE* str, UINT16 fontColor, BYTE bRegionIndex);
void Dvb_DrawPopBackgroud(UINT16 xStart, UINT16 yStart,UINT16 xLen,UINT16 yLen);
void show_DvdDvbSwitch_status(BYTE flag)
{
    printf("******** show_DvdDvbSwitch_status ********\n");
    UINT16 Strlen;
    coordinate stStart;
    dimension in_dimension;
    UINT16 fontColor;//bkColor;
    UINT8 *Str;

    if(flag == 1)
    {
        Str="DVB";
        Strlen = strlen(Str);

        osd_init_new_dvb_menu();
        osd_tog_region(0, OSD_ON);
        in_dimension.x_length = 80;
        in_dimension.y_length = 30;
        printf_w("\n&&&&&&& now in the show status flag == 1 \n");
        stStart.x = 52;
        stStart.y = 42;
        //bkColor = 3;
        Dvb_DrawPopBackgroud(stStart.x, stStart.y, in_dimension.x_length, in_dimension.y_length);
        //osd_draw_rectangle(&stStart, &in_dimension, bkColor, 0); 
        stStart.x = stStart.x + (in_dimension.x_length-Strlen*12)/2;
        stStart.y = stStart.y + 6;
        fontColor = 9;
        Dvb_DrawString(&stStart, Str, fontColor, 0);
    /*        
        stStart.x = stStart.x + 12;
        stStart.y = stStart.y+2;
        fontColor = 4;
        Strlen = strlen(Str);
        Dvb_DrawString(&stStart, Str, fontColor, 0);
    */
    }
    else if(flag == 0)
    {
        printf_w("\n&&&&&&& now in the show status flag == 0 \n");
        osd_tog_region(1, OSD_ON);
        
        if(play_state == VCD_STATE_OPEN)//Jack added 05/12/12
            PrintOsdMsg(STR_OS_OPEN, REGION1, 0, 0);
        else
        {
            #ifndef NOT_SHOW_DVD_WORDS_AT_DVD_USB_CARD
            Str="DVD";
            psprintf(RegionValStr[REGION1], Str);
            PrintOsdMsg(STR_OS_SPACE, REGION1, 0, 1);
	    #endif //end=> #ifndef NOT_SHOW_DVD_WORDS_AT_DVD_USB_CARD		
        }
    }
}
#endif//#ifdef SHOW_DVDDVB_STATUS        //sunzhh add 20051018


void DVD_servo_check(void)//Jack moved to here 06/04/19 for no DVB model use.
{
    #if defined(CHECK_PORTABLE_OPCLSW)||defined(TOP_DOOR_LOADER)
    regs0->sft_cfg4 &= ~((0x03)<<2);    //Enable GPIO For COVER SW
    
    if(check_eject_sw())
    {
        play_state = VCD_STATE_OPEN;
        //CDSetPlay();//Jack added for "in open state then sw to DVD state then no show open" 
    }
    else
    #endif//else close tray and read disc
    {
        atapi_open_tray();  //Maoyong 2004-8-10 11:00
        atapi_close_tray(0);

        play_state = VCD_STATE_CLOSE;   
        
        #ifdef USE_LGDVD_UI //Jack moved to here06/03/21
        {//init lg status... if add in startup func, please mark here
            //g_ucOsdRegionType = 0;
            //osd_init();        
            //PrintOsdMsg(STR_OS_READ,REGION1,2,0);
            LGDVD_Osd_Init();
            LGDVD_Osd_Show(STR_OS_READ);            
        }
        #endif /*USE_LGDVD_UI*/ 
    }
}
 

