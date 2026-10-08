#ifndef __IRCMD_H
#define __IRCMD_H
/*** zhfy move it here from ircmd.c 0-11-20 10:34 ***/
//nono mark. they have been defined in global.h.2-7-12 19:48 
//#define NO_REMAIN_TIME          0
//#define TRK_REMAIN_TIME         1
//#define DISC_REMAIN_TIME        3//2


/*
enum    {
    IRCMD_NULL  = 0,    
    IRCMD_PLAY  = 0x10,
    IRCMD_DEFAULT,
    IRCMD_STOP,
    IRCMD_FORWARD,
    IRCMD_BACKWARD,
    IRCMD_NEXT,
    IRCMD_PREV,
    IRCMD_RETURN,
    IRCMD_EJECT,
    IRCMD_CLOSE,
    IRCMD_SLOW,
    IRCMD_PAUSE,
    IRCMD_PLAYMODE,
    IRCMD_FREEZE,
    IRCMD_PREVIEW,
    IRCMD_POWER,
    IRCMD_REPEAT,
    IRCMD_AB,
    IRCMD_DISPLAY,
    IRCMD_SUBTITLE,
    IRCMD_MUTE,
    IRCMD_CHANNEL,
    IRCMD_VOLUME_UP,
    IRCMD_VOLUME_DN,
    IRCMD_EFFECT,
    IRCMD_LANGUAGE,
    IRCMD_0,
    IRCMD_1,
    IRCMD_2,
    IRCMD_3,
    IRCMD_4,
    IRCMD_5,
    IRCMD_6,
    IRCMD_7,
    IRCMD_8,
    IRCMD_9 ,
    IRCMD_10,
    IRCMD_P10,
    IRCMD_FORMAT,
    IRCMD_FOCUS,
    IRCMD_ZOOM,
    IRCMD_STEP,
    IRCMD_GAME,
    IRCMD_QUALIFY, //kenny add 891107
};
*/


/*
**
*/
//void  ircmd_reset(void);
void    ircmd_0(void);
void    ircmd_1(void);
void    ircmd_2(void);
void    ircmd_3(void);
void    ircmd_4(void);
void    ircmd_5(void);
void    ircmd_6(void);
void    ircmd_7(void);
void    ircmd_8(void);
void    ircmd_9(void);
void    ircmd_10(void);
void    ircmd_p10(void);
//void    ircmd_focus(void);
void    ircmd_preview(void);
void    ircmd_9frames(void);
void    ircmd_intro(void);
void    ircmd_playmode_toggle(void);
void    ircmd_trayout(void);
void    ircmd_trayin(void);
void    ircmd_eject_toggle(void);
void    ircmd_step(void);
void    ircmd_play(void);
void    ircmd_play_resume(void);//nono 2-3-25 17:20
//void    ircmd_play_n_default(void);
void    ircmd_default(void);
void    ircmd_stop(void);
void    ircmd_subtitle(void);
void    ircmd_display_format_toggle(void);
//void    ircmd_display_pause(void);
void    ircmd_play_pause(void);
void    ircmd_pause(void);
void    ircmd_next(void);
void    ircmd_prev(void);
void    ircmd_return(void);
void	ircmd_touch_menu(void);//frank.huang 050801
void    ircmd_forward(void);
void    ircmd_backward(void);
void    ircmd_repeat_toggle(void);
void    ircmd_repeat_all(void);
void    ircmd_repeat_ab(void);

#ifdef TWO_FUN_IN_ONE_VFD_KEY
void    ircmd_vfd_next(void);       //dingzhy  04-04-21 7:01PM
void    ircmd_vfd_prev(void);       //dingzhy  04-04-21 7:01PM
#endif

void    ircmd_disk1(void);
void    ircmd_disk2(void);
void    ircmd_disk3(void);

void    ircmd_mute(void);

#ifdef MUTE_DEMUTE_HAVE_TWE_VALUE_IN_ONE_KEY//2005-4-19 10:23 zhoulin
void ircmd_indiv_MUTE(void);
void ircmd_indiv_DEMUTE(void);
#endif

#ifdef CNTR_5SPK_VOLUME
void    ircmd_volume_switch(void);
#else
void    ircmd_effect(void);
#endif

void    ircmd_channel(void);
void    ircmd_channel_dn(void);//nono 02-03-25 for fuss
void    ircmd_key_up(void);
void    ircmd_key_down(void);
void    ircmd_key_reset(void);
void    ircmd_volume_up(void);
void    ircmd_volume_down(void);
void    ircmd_slowmotion(void);
void    ircmd_shuffle(void);
void    ircmd_mix_func(void);
void    ircmd_echo_up(void);
void    ircmd_echo_down(void);
void    ircmd_mic_up(void);
void    ircmd_mic_down(void);

void    ircmd_vppmode(void);
#ifdef USER_MPEG_LOGO
void    ircmd_mpeg_logo(void);
#else
void    ircmd_null(void);
#endif

#if defined(SOUND_NO_KEYPAGE)&&defined(VTREK_DVD)
void    ircmd_3d2(void);
#endif
//jjding
void    ircmd_game(void);
void    ircmd_prog(void);
void    ircmd_zoom(void);
void    ircmd_up(void);
void    ircmd_down(void);
void    ircmd_left(void);
void    ircmd_right(void);
void    invalid_key(void);
void    ircmd_cancel(BYTE show);
void    ircmd_display(void);
void    ircmd_goto(void);
void    ircmd_mark(void);
void    ircmd_power(void);
void    ircmd_remaintime(void);
void    ircmd_resume(void);
void    ircmd_title_return(void);//2002-4-18 23:08
//for osd display
//void    show_prog(BYTE,BYTE);  //huo 2000.12.14
//void    show_goto(BYTE);
void    show_level(int,INT8,BYTE); 
void    show_time(void);
// for 
void    get_cdkit_time(BYTE);
//int     play_one_trk(int);
void    playmode_sel(BYTE);
BYTE    get_random_number(int range);
void    stop_init(void);
void    reset_ir(void);
BYTE    polling_ir(void);
void  ircmd_qualify(void);//kenny 891107
#ifdef ONE_KEY_CONTRL_ECHO
void  ircmd_echo(void);//kenny 891107 kenny mark it 891108
#endif 
#ifdef ONE_KEY_CONTRL_MIC
void  ircmd_mic(void);//wanghaoying 2005-9-20 13:04
#endif 
#if defined(VFD_DIMMING_CONTROL)
void  ircmd_dimming(void);
#endif
void ircmd_echo_up(void);//kenny 891107
void ircmd_echo_down(void);//kenny 891107
void ircmd_dsp_reset(void); //kenny 891108
//void  Display_Mp3play_Time(UINT16);
void reset_status(void);        //zhyf 1-2-8 9:27
void ResetAB(void);
void show_random_osd_msg(int id);
void show_repeatAB(int t);
void ircmd_sub_picture(void);

#ifdef DOUBLE_TITLE //susu add 2003-8-26 10:39
void ircmd_double_picture(void);
#endif

void ircmd_angle(void);
void ircmd_audio_language(void);
void ircmd_select(void);
void ircmd_title_menu(void);
void ircmd_clear(void);
void ircmd_setup(void);
void ircmd_karaoke(void);
#ifdef OP_IR
void ircmd_exit(void);
#endif
#ifdef OP_PLAYMODE
void ircmd_mode(void);
#endif
void ircmd_3dsound(void);
void ircmd_bk_slow(void);
void ircmd_reading(void);
void ircmd_root_menu(void);//nono 2-3-25 10:14

void ircmd_play_select(void);//IRC_PLAY_SELECT
void ircmd_display_time(void);//IRC_DISPLAY_TIME
void ircmd_slow_bak_ford(void);//IRC_SLOW_BAK_FORD

void ircmd_book(void);//kenny 2001/5/17

void ircmd_exit_setup(void);//IRC_EXIT_SETUP

void ircmd_score(void);

void ircmd_p_scan(void);
void ircmd_yuv(void);
void ircmd_chg_dac(void);
#ifdef SUPPORT_EXT_HW_DSA //kenny 891128

void get_disc_type(BYTE );      
void ircmd_sys_state(void);
#endif  //kenny 891220

#ifdef CAR_VCD //kenny 891220

void ircmd_next_disk(void);
void ircmd_pre_disk(void);
void ircmd_reset_changer(void);//kenny 891220

#endif  //SUPPORT_EXT_HW_DSA

//freyman add 2002-9-3 10:42
#ifdef IR25
void ircmd_amp_volume(void);
void ircmd_downmix(void);
#endif


/* wanghaoying marked 2004-7-1 14:27, for not use any more
#ifdef IR17

void ircmd_center_up(void);
void ircmd_center_down(void);
void ircmd_rear_up(void);
void ircmd_rear_down(void);
void ircmd_woofer_up(void);
void ircmd_woofer_down(void);
void ircmd_middle_up(void);
void ircmd_middle_down(void);
void ircmd_base_up(void);
void ircmd_base_down(void);
void ircmd_treble_up(void);
void ircmd_treble_down(void);
void ircmd_amp_onoff(void);
void ircmd_front_down(void);
void ircmd_front_up(void);
#endif
*/

#ifdef SUPPORT_AMP
void ircmd_amp_onoff(void);
#endif 

#ifdef Ti3001_OSD_UI_1
void ircmd_amp_control(void);
#endif

#ifdef Ti5026_OSD_UI_1
void ircmd_amp_control(void);
#endif

#ifdef USE_PROLOGIC_II_KEY//clead 2003-8-7 
void ircmd_prologic(void);
#endif 

#ifdef IR_KEY_SET_VIDEO_MODE
void ircmd_set_video_mode(void);
#endif
void ircmd_key_lock(void);//unused

void ircmd_only_pause(void);
void ircmd_default_setup(void);
void ircmd_virtual_keyboard(void);  // alan, 2003/8/16 05:00AM

#if defined(TV_FORMAT_CHG2_VIDEO_MODE)||defined(ADD_TV_VIDEO_MODE)
void ircmd_tv_sys_mode(void);
#endif


//zhaoyanhua add 03-10-17 19:49
#ifdef ONLY_INTERLACE_KEY
void ircmd_interlace(void);
#endif
#ifdef ONLY_VGA_KEY
void ircmd_VGA(void);
#endif
#ifdef ONLY_P_SCAN_KEY
void ircmd_only_P_SCAN(void);
#endif

#ifdef SPECTRUM_KEY  //fengjl add 2004-04-22 10:26 for the only key to show spectrum
void ircmd_spectrum(void);
#endif

#if defined(ONLY_EQ_KEY)||defined(SUPPORT_RECEIVER_EQ)//chenzhao20060117
void ircmd_EQ(void);
#endif

#ifdef ONLY_SOUND_FIELD_KEY
void ircmd_sound_field(void);
#endif

#ifdef ONE_KEY_PASS
void ircmd_one_key_pass(void);
#endif //ONE_KEY_PASS

#ifdef AUDIO_2CH_5_1CH
void ircmd_2ch_5_1ch(void);
#endif
#ifdef RECORD_KEY
void ircmd_record(void);
#endif
#ifdef DIV_GOTO_DISPLAY
void ircmd_search(void);
void ExitGOTOPage(void);
#endif
#ifdef DISC_INFO_KEY
void ircmd_disc_info(void);
#endif
#if defined (MIC_FUNCTION_KEY)&& defined (BBK_DVD)
void ExitEchoMode(void);
#endif

#ifdef GBM_IRC_SHIELD_FUNCTION      //gerry for gbm video off function,2004-1-30 19:13
void ircmd_shield_func(void);
#endif

#ifdef IR_SWITCH_CD_USB_CF_OTHER  //added by dingzhy  4-10-20 13:57
void ircmd_switch_cd_usb_cf_other(void);		//IRC_CD_USB_CF_OTHER
#elif defined(FILE_MODE_WRITE)//added by wangwei,2005-1-10 13:10
void ircmd_file_mode_write(void);//IRC_FM_WRITE
#elif defined(DIRECT_ACCESS_MEDIA)//added by wangwei, 2006-4-12 14:43
void ircmd_source(void);
#endif

#if defined(DVB1000_NON_OS)||defined(SUPPORT_8202_DVB)  // David 2005-2-17 16:38
void ircmd_dvb_dvd(void);		//IRC_DVB_DVD
void ircmd_tv_radio(void);      //IRC_TV_RADIO
#endif

#ifdef HONEYWLD_DVD 
void ircmd_dma_dvd(void);		//IRC_DMA_DVD
void ircmd_dvd_invalid(void);	//IRC_DVD_INVALID
#endif


#ifdef REPEAT_AB_TOO_SHORT_DISABLE_3D//nono 20040206
int ircmd_repeat_ab_time_is_too_short(void);
#endif

void run_pause_setting(void);

#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
extern void DrawNewWindow(void);
#endif

void  cancel_sound(void);

#ifdef SUPPORT_RECEIVER  //huziqin 2004-2-26
 void ircmd_rcvr_select_mode(int);
 void ircmd_rcvr_function_mode(void);
 void ircmd_rcvr_next_mode(void);
 #ifdef SUPPORT_VIDEO_WITH_SPDIF
  void ircmd_rcvr_analog_digital(void);
 #endif
#endif

#if defined(BASS_ADJUST_KEY)//xyy 2004-8-14
void  ircmd_rcvr_bass(void);
#endif

#if defined(TREBLE_ADJUST_KEY)
void  ircmd_rcvr_treble(void);
#endif

#if defined(EQ_SWITCH_KEY)
void ircmd_rcvr_EQ(void);             //xulf 2004-3-7 
#endif
#if defined(BAND_SWITCH_KEY)
void  ircmd_rcvr_band(void);
#endif

#ifdef SUPPORT_POWER_OFF_CLOCK_FUNC  //xyy 2004-10-12
void ircmd_set_clock(void);
#endif

#ifdef TWO_FUNC_IN_LEFT_RIGHT_KEY //xyy add for Oritron 2004-11-10 10:05
void ircmd_vfd_left(void);
void ircmd_vfd_right(void); 
#endif

#ifdef  AUTO_ADJUST_TV_TYPE
void auto_adjust_tv_type(void);
#endif

#ifdef DOLBY_AMP_VOLUME_CTRL
void  ircmd_set_treble();
void  ircmd_set_bass();
#endif

#ifdef IR_SWITCH_CARD_CD    //Maoyong 2004.05.13
void  ircmd_switch_card_cd(void);
#endif


#ifdef DIRECT_ACCESS_MEDIA    //added by wangwei, 2005-11-21 18:28
#ifndef NO_DVD_SERVO
void  ircmd_key_disc(void);
#endif//NO_DVD_SERVO

#ifdef SUPPORT_USB
void  ircmd_key_usb(void);
#endif//SUPPORT_USB

#ifdef SPHE8202_CARD_STORAGE
void  ircmd_key_card(void);
#endif//SPHE8202_CARD_STORAGE
#endif//DIRECT_ACCESS_MEDIA


#ifdef IR_IRCMD_JUMP_30SEC  //wangwei 2004-7-20 22:30
void  ircmd_jump_30sec(void);
#endif

#ifdef TWO_KEY_SWITCH_TWO_SUBTITLE  //added by wangwei,2004-10-5 14:33
void ircmd_switch_2nd_subtitle(void);
#endif
#ifdef SANJING_MIDI_DVD     //ouyang 2004-10-29 10:12
void ircmd_main_melody(void);
#endif

#ifdef SUPPORT_FUNCTION_MENU
void ircmd_setup_plus(void);
void init_setup_plus(void); 
#endif //end #ifdef SUPPORT_FUNCTION_MENU
#ifdef SUPPORT_DISPLAY_MENU
void ircmd_display_menu(void);
#endif

#ifdef SWITCH_CD_CARD_USB
void ircmd_switch_cd_card_usb(void);
#endif

#if defined(FAT_Write_UI) || defined(FILE_MODE_WRITE)                     //sunzhh add 2004-10-18 17:41
void ircmd_media_control(void);      //IRC_MEDIA_CONTROL                                //0x5f
#endif

#ifdef SUPPORT_SPI_QSI
typedef void (*SPI_CMD_FUNC)();
void spi_cmd_play(void); 

#ifdef SUPPORT_CARD_STORAGE
void spi_cmd_switch_media(void);
#ifdef QSI_PLATFORM //qsi: added by johnson 20040811
void spi_cmd_switch_media_to_dvd(void); 
void spi_cmd_switch_media_to_card(void);
#endif
#endif //SUPPORT_CARD_STORAGE 

void spi_cmd_ssaver_on(void); 
void spi_cmd_ssaver_off(void);    
void spi_cmd_stop2eject(void);
void spi_cmd_play_pause(void);
void spi_cmd_only_pause(void);
void spi_cmd_pre_stop(void);
void spi_cmd_system(void);
void spi_cmd_region(void);
void spi_cmd_tvsys(void);
void spi_cmd_tvout(void);
void spi_cmd_wakeup(void);
void spi_cmd_version_display(void);
#ifdef SUPPORT_CARD_STORAGE
    void spi_cmd_switch_2_disc(void);
    void spi_cmd_switch_2_card(void);
#endif //SUPPORT_CARD_STORAGE



#endif  //SUPPORT_SPI_QSI

#ifdef BRIGHTNESS_COLOR_KEY
void ircmd_brightness_color(void);
#endif

#ifdef VIEW_MODE_KEY
void ircmd_view_mode(void);
#endif

#ifdef USE_FW_SF   //zhongshan  070518
void ircmd_fw_sf_slowmotion(void);
#endif

#ifdef USE_BW_SR
void ircmd_bw_sr_slowmotion(void);
#endif
//=========================================
//for PMP UI,liweihua 2004-12-26 15:42
#ifdef PMP_UI
void pmpkey_up(void);
void pmpkey_down(void);
void pmpkey_right(void);
void pmpkey_left(void);
void pmpkey_return(void);
void pmpkey_select(void);
#endif
//=========================================
//for QSI disc/card switch  //added by JS   //20040726
#ifdef SUPPORT_QSI_SOURCE_SWITCH

#ifndef QSI_PLATFORM
       void ircmd_source_switch(void);
#else
       void ircmd_source_switch(/*unsigned char src*/void);
#endif

#endif
//=========================================

#ifdef IR_SLEEP //hongfeng 2005-07-12
void ircmd_sleep(void);
#endif

#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
void ircmd_dvd_usb_card_avin_dvb(void);
void switch_usb_card(void);
void osd_clear_and_init(void);
void mode_switch_reset_var(void);
#endif

#ifdef CONTINUOUS_NUM_KEY_SELECT
void polling_ir_num(void);

#define IR_NUM_TIMER 20 //20*100ms = 2seconds
#define NUM_STATE0  0
#define NUM_STATE1  1
#define NUM_STATE2  2
#define NUM_STATE3  3
#define NUM_STATE4  4
#endif

#ifdef SUPPORT_OP_FIVE_DISC////chenzhao20050111 SUPPORT_FIVE_DISC  //chenzhao20050107//OP add
void ircmd_panel_disc_1(void);
void ircmd_panel_disc_2(void);
void ircmd_panel_disc_3(void);
void ircmd_panel_disc_4(void);
void ircmd_panel_disc_5(void);
void ircmd_panel_exchange(void);
void ircmd_panel_all_eject(void);
#endif

#ifdef SUPPORT_EX_BASS_FUNC//chenzhao20060117
void ircmd_ex_bass_func(void);
#endif

#ifdef SUPPORT_HD_RESOLUTION
void ircmd_hd(void);
#endif 

#endif/*__IRCMD_H*/

