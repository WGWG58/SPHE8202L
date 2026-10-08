//nono split from ir_parser.c 5-5-9 15:07
#ifdef PMP_UI//liweihua 2005-1-5
const IRFUNC irc_func_table[IR_CODE_MAX_NUM]=
{
//00-0F
ircmd_0,                        //IRC_0,                                        //0x00
ircmd_1,                        //IRC_1,                                        //0x01
ircmd_2,                        //IRC_2,                                        //0x02
ircmd_3,                        //IRC_3,                                        //0x03
ircmd_4,                        //IRC_4,                                        //0x04
ircmd_5,                        //IRC_5,                                        //0x05
ircmd_6,                        //IRC_6,                                        //0x06
ircmd_7,                        //IRC_7,                                        //0x07
ircmd_8,                        //IRC_8,                                        //0x08
ircmd_9,                        //IRC_9,                                        //0x09
ircmd_10,                       //IRC_10,                                       //0x0a
ircmd_p10,                      //IRC_P10,                                      //0x0b
ircmd_null,//ircmd_eject_toggle,             //IRC_EJECT,                                    //0x0c
ircmd_mute,                     //IRC_MUTE,                                     //0x0d
ircmd_null,//ircmd_key_up,                   //IRC_KEY_UP,                                   //0x0e
ircmd_null,//ircmd_key_reset,                //IRC_KEY_RESET,                                //0x0f
//10-1F
ircmd_null,//ircmd_key_down,                 //IRC_KEY_DN,                                   //0x10
ircmd_volume_up,                //IRC_VOLUME_UP,                                //0x11
ircmd_volume_down,              //IRC_VOLUME_DN,                                //0x12
ircmd_slowmotion,               //IRC_SLOW,                                     //0x13
ircmd_null,//ircmd_step,                     //IRC_STEP,                                     //0x14
ircmd_pause,                    //IRC_PAUSE,                                    //0x15
ircmd_play,                     //IRC_PLAY,                                     //0x16
ircmd_play_resume,              //IRC_PLAY_RESUME,                              //0x17
//pmpkey_return,                  //IRC_RETURN,                                   //0x18
ircmd_return,                  //IRC_RETURN,                                   //0x18
ircmd_null,//ircmd_stop,                     //IRC_STOP,                                     //0x19
ircmd_null,                     //IRC_LANGUAGE,                                 //0x1a,(not use)
ircmd_backward,                 //IRC_BACKWARD,                                 //0x1b
ircmd_forward,                  //IRC_FORWARD,                                  //0x1c
ircmd_prev,                     //IRC_PREV,                                     //0x1d
ircmd_next,                     //IRC_NEXT,                                     //0x1e
ircmd_display,                  //IRC_DISPLAY,                                  //0x1f
//20-2F
#ifdef SUPPORT_REPEAT_PMP
ircmd_repeat_ab,                //IRC_AB,                                       //0x20
ircmd_repeat_all,               //IRC_REPEAT, 
#else
ircmd_null,                                 //0x20
ircmd_null,                                    ///0x21
#endif                             
ircmd_null,//ircmd_playmode_toggle,          //IRC_PBC,                                      //0x22
ircmd_goto,                     //IRC_GOTO,                                     //0x23
ircmd_null,//ircmd_shuffle,                  //IRC_RANDOM,                                   //0x24
ircmd_resume,                   //IRC_RESUME,                                   //0x25
ircmd_null,//ircmd_remaintime,               //IRC_TIME,                                     //0x26
ircmd_power,                    //IRC_POWER,                                    //0x27
ircmd_zoom,                     //IRC_ZOOM,                                     //0x28
//pmpkey_up,                       //IRC_UP,                                       //0x29
//pmpkey_down,                     //IRC_DOWN,                                     //0x2a
//pmpkey_left,                     //IRC_LEFT,                                     //0x2b
//pmpkey_right,                    //IRC_RIGHT,                                    //0x2c
ircmd_up,                       //IRC_UP,                                       //0x29
ircmd_down,                     //IRC_DOWN,                                     //0x2a
ircmd_left,                     //IRC_LEFT,                                     //0x2b
ircmd_right,                    //IRC_RIGHT,                                    //0x2c
ircmd_null,//reset_ir,                       //IRC_PLAY_IS_DEFAULT,                          //0x2d,(not use)
ircmd_null,                   	//IRC_FREEZE,                                   //0x2e,no use
ircmd_null,//ircmd_channel,                  //IRC_CHANNEL                                   //0x2f
//30-3F
ircmd_null,//ircmd_channel_dn,               //IRC_CHANNEL_DN,                               //0x30
ircmd_null,                     //IRC_EFFECT,                                   //0x31,(not use) ,terry,2004/2/10 05:00PM
ircmd_null,//ircmd_preview,                  //IRC_PREVIEW,                                  //0x32
ircmd_null,//ircmd_9frames,                  //IRC_9FRAMES,
#ifdef SUPPORT_MOVE_SUBTITLE_BY_PRO_KEY   ///YANGLI ADD FOR MOVE SUBTITLE FOR 16:9,2005-11-28 11:24                                  //0x33
ircmd_prog,                     //IRC_PROGRAM,                                  //0x34
#else 
ircmd_null,
#endif
ircmd_display_format_toggle,    //IRC_FORMAT,                                   //0x35
ircmd_null,//ircmd_intro,                    //IRC_INTRO,                                    //0x36
ircmd_null,                     //IRC_GAME_L,                                   //0x37
ircmd_null,                     //IRC_GAME_R,                                   //0x38
ircmd_null,                     //IRC_GAME_UP,                                  //0x39
ircmd_null,                     //IRC_GAME_DN,                                  //0x3a
ircmd_null,                     //IRC_GAME_TN,                                  //0x3b
ircmd_null,                     //IRC_GAME_UL,                                  //0x3c
ircmd_null,                     //IRC_GAME,                                     //0x3d,(not use)
ircmd_null,                     //IRC_FOCUS,                                    //0x3e,(not use)
ircmd_null,                    //IRC_DISK1,                                    //0x3f
//40-4F
ircmd_null,                    //IRC_DISK2,                                    //0x40
ircmd_null,                    //IRC_DISK3,                                    //0x41
ircmd_play_pause,               //IRC_PAUSEPLAY,                                //0x42
ircmd_null,                     //IRC_QUALIFY                                   //0x43,(not use)
ircmd_null,                //IRC_RESET_DSP                                 //0x44
ircmd_sub_picture,              //IRC_SUBP                                      //0x45                    
ircmd_angle,                    //IRC_ANGLE                                     //0x46
ircmd_audio_language,           //IRC_AUD_LANGUAGE                              //0x47
ircmd_select,                  //IRC_SELECT                                    //0x48
//pmpkey_select,                  //IRC_SELECT                                    //0x48
ircmd_null,//ircmd_title_menu,               //IRC_TITLEMENU                                 //0x49
ircmd_null,//ircmd_clear,                    //IRC_CLEAR                                     //0x4a
ircmd_setup,//ircmd_setup,                    //IRC_SETUP                                     //0x4b
//ircmd_null,//ircmd_setup,                    //IRC_SETUP                                     //0x4b
ircmd_null,//ircmd_karaoke,                  //IRC_KARAOKE                                   //0x4c
ircmd_null,//ircmd_3dsound,                  //IRC_3D                                        //0x4d
ircmd_null,//ircmd_bk_slow,                  //IRC_BK_SLOW                                   //0x4e
ircmd_null,//ircmd_reading,                  //IRC_READING                                   //0x4f
//50-5F
};
#else//#ifdef PMP_UI//liweihua 2005-1-5
const IRFUNC irc_func_table[IR_CODE_MAX_NUM]=
{
//00-0F
ircmd_0,                        //IRC_0,                                        //0x00
ircmd_1,                        //IRC_1,                                        //0x01
ircmd_2,                        //IRC_2,                                        //0x02
ircmd_3,                        //IRC_3,                                        //0x03
ircmd_4,                        //IRC_4,                                        //0x04
ircmd_5,                        //IRC_5,                                        //0x05
ircmd_6,                        //IRC_6,                                        //0x06
ircmd_7,                        //IRC_7,                                        //0x07
ircmd_8,                        //IRC_8,                                        //0x08
ircmd_9,                        //IRC_9,                                        //0x09
ircmd_10,                       //IRC_10,                                       //0x0a
ircmd_p10,                      //IRC_P10,                                      //0x0b
ircmd_eject_toggle,             //IRC_EJECT,                                    //0x0c
ircmd_mute,                     //IRC_MUTE,                                     //0x0d
ircmd_key_up,                   //IRC_KEY_UP,                                   //0x0e
ircmd_key_reset,                //IRC_KEY_RESET,                                //0x0f
//10-1F
ircmd_key_down,                 //IRC_KEY_DN,                                   //0x10
ircmd_volume_up,                //IRC_VOLUME_UP,                                //0x11
ircmd_volume_down,              //IRC_VOLUME_DN,                                //0x12
ircmd_slowmotion,               //IRC_SLOW,                                     //0x13
ircmd_step,                     //IRC_STEP,                                     //0x14
ircmd_pause,                    //IRC_PAUSE,                                    //0x15
ircmd_play,                     //IRC_PLAY,                                     //0x16
ircmd_play_resume,              //IRC_PLAY_RESUME,                              //0x17
ircmd_return,                   //IRC_RETURN,                                   //0x18
ircmd_stop,                     //IRC_STOP,                                     //0x19
ircmd_null,                     //IRC_LANGUAGE,                                 //0x1a,(not use)
ircmd_backward,                 //IRC_BACKWARD,                                 //0x1b
ircmd_forward,                  //IRC_FORWARD,                                  //0x1c
ircmd_prev,                     //IRC_PREV,                                     //0x1d
ircmd_next,                     //IRC_NEXT,                                     //0x1e
ircmd_display,                  //IRC_DISPLAY,                                  //0x1f
//20-2F
ircmd_repeat_ab,                //IRC_AB,                                       //0x20
ircmd_repeat_all,               //IRC_REPEAT,                                   //0x21
ircmd_playmode_toggle,          //IRC_PBC,                                      //0x22
ircmd_goto,                     //IRC_GOTO,                                     //0x23
ircmd_shuffle,                  //IRC_RANDOM,                                   //0x24
ircmd_resume,                   //IRC_RESUME,                                   //0x25
ircmd_remaintime,               //IRC_TIME,                                     //0x26
ircmd_power,                    //IRC_POWER,                                    //0x27
ircmd_zoom,                     //IRC_ZOOM,                                     //0x28
ircmd_up,                       //IRC_UP,                                       //0x29
ircmd_down,                     //IRC_DOWN,                                     //0x2a
ircmd_left,                     //IRC_LEFT,                                     //0x2b
ircmd_right,                    //IRC_RIGHT,                                    //0x2c

#ifdef GBM_IRC_SHIELD_FUNCTION                   //gerry,2004-1-30 19:20
ircmd_shield_func,              //IRC_SHIELD_FUNC       //0x2d
#elif TOUCH_MENU//gerry,2004-1-30 19:20//frank.huang 050801
ircmd_touch_menu,              //IRC_TOUCH_MENU       //0x2d
#else
reset_ir,                       //IRC_PLAY_IS_DEFAULT,                          //0x2d,(not use)
#endif

#ifdef USER_MPEG_LOGO
ircmd_mpeg_logo,                //IRC_mpeg_logo,                                //0x2e,no use
#elif defined(ADD_TV_VIDEO_MODE)
ircmd_tv_sys_mode,                      //IRC_TV_MODE,                                      //0X2e
#else
ircmd_null,                     //IRC_FREEZE,                                   //0x2e,no use
#endif 

ircmd_channel,                  //IRC_CHANNEL                                   //0x2f
//30-3F
ircmd_channel_dn,               //IRC_CHANNEL_DN,                               //0x30


#ifdef CNTR_5SPK_VOLUME
ircmd_volume_switch,            //IRC_VOLUME_SWITCH,                            //0x31
#else
ircmd_null,                     //IRC_EFFECT,                                   //0x31,(not use) ,terry,2004/2/10 05:00PM
#endif

ircmd_preview,                  //IRC_PREVIEW,                                  //0x32
ircmd_9frames,                  //IRC_9FRAMES,                                  //0x33
ircmd_prog,                     //IRC_PROGRAM,                                  //0x34
ircmd_display_format_toggle,    //IRC_FORMAT,                                   //0x35
ircmd_intro,                    //IRC_INTRO,                                    //0x36

#ifdef CAR_VCD//kenny 891220 modify
ircmd_next_disk,                                                                //0x37
ircmd_pre_disk,                                                                 //0x38
ircmd_reset_changer,                                                            //0x39
#elif defined(BRIGHTNESS_COLOR_KEY)////////////tw_kevin.lo040901
ircmd_brightness_color,			//IRC_BRICOL_ADJUST
ircmd_null,                                                        //0x38
ircmd_null,                      
   
#elif defined(DIRECT_ACCESS_MEDIA)//added by wangwei
#ifndef NO_DVD_SERVO
ircmd_key_disc,                    //0x37
#else//NO_DVD_SERVO
ircmd_null,
#endif//NO_DVD_SERVO

#ifdef SUPPORT_USB
ircmd_key_usb,                     //0x38
#else//SUPPORT_USB
ircmd_null,
#endif//SUPPORT_USB

#ifdef SPHE8202_CARD_STORAGE
ircmd_key_card,                    //0x39
#else//SPHE8202_CARD_STORAGE
ircmd_null,
#endif//SPHE8202_CARD_STORAGE

#elif defined(SUPPORT_OP_FIVE_DISC)//chenzhao20060107
ircmd_panel_disc_1,             //IRC_DISC_1                                    //0x37
ircmd_panel_disc_2,             //IRC_DISC_2                                    //0x38
ircmd_panel_disc_3,             //IRC_DISC_3                                    //0x39
#else
ircmd_null,                     //IRC_GAME_L,                                   //0x37
ircmd_null,                     //IRC_GAME_R,                                   //0x38
ircmd_null,                     //IRC_GAME_UP,                                  //0x39
#endif

#ifdef TWO_FUN_IN_ONE_VFD_KEY    //dingzhy for GBM
ircmd_vfd_next,                     //IRC_VFD_NEXT,                                  //0x3a
ircmd_vfd_prev,                     //IRC_VFD_PREV,                                  //0x3b
#else
ircmd_null,                     //IRC_GAME_DN,                                  //0x3a
ircmd_null,                     //IRC_GAME_TN,                                  //0x3b
#endif

#if defined(SUPPORT_OP_FIVE_DISC) && !defined(SUPPORT_5DISC_EXCHANGE)  //chenzhao 2006-4-20 11:4 .
ircmd_panel_all_eject,          //IRC_ALL_EJECT                                 //0x3c
#else
ircmd_null,                     //IRC_GAME_UL,                                  //0x3c
#endif

ircmd_null,                     //IRC_GAME,                                     //0x3d,(not use)
#ifdef VIRTUAL_KEYBOARD // alan, 2003/8/18 01:15PM
ircmd_virtual_keyboard,         //IRC_VIRTUAL_KEYBOARD,                         //0x3e
#else
ircmd_null,                     //IRC_FOCUS,                                    //0x3e,(not use)
#endif

#ifdef SUPPORT_OP_FIVE_DISC  //OP add
ircmd_panel_disc_4,             //IRC_DISC_4,                                   //0x3f
ircmd_panel_disc_5,             //IRC_DISC_5,                                   //0x40
ircmd_panel_exchange,           //IRC_EXCHANGE,                                 //0x41
#else //SUPPORT_OP_FIVE_DISC
ircmd_null,                    //IRC_DISK1,                                    //0x3f
//40-4F
#ifdef MUTE_DEMUTE_HAVE_TWE_VALUE_IN_ONE_KEY//2005-4-21 13:26 zhoulin
ircmd_indiv_MUTE,
ircmd_indiv_DEMUTE,
#else
ircmd_null,                    //IRC_DISK2,                                    //0x40
ircmd_null,                    //IRC_DISK3,                                    //0x41
#endif
#endif//#ifdef SUPPORT_FIVE_DISC
ircmd_play_pause,               //IRC_PAUSEPLAY,                                //0x42
ircmd_null,                     //IRC_QUALIFY                                   //0x43,(not use)
ircmd_null,                //IRC_RESET_DSP                                 //0x44
#ifdef DOUBLE_TITLE //susu add 2003-8-26 10:30
ircmd_double_picture,
#else
ircmd_sub_picture,              //IRC_SUBP                                      //0x45
#endif                                    
ircmd_angle,                    //IRC_ANGLE                                     //0x46
ircmd_audio_language,           //IRC_AUD_LANGUAGE                              //0x47
ircmd_select,                   //IRC_SELECT                                    //0x48
ircmd_title_menu,               //IRC_TITLEMENU                                 //0x49
ircmd_clear,                    //IRC_CLEAR                                     //0x4a
#ifdef OP_PLAYMODE                                                       
ircmd_mode,
#else
ircmd_setup,                    //IRC_SETUP 
#endif
#ifdef OP_IR                                                       
ircmd_exit,
#else                                    //0x4b
ircmd_karaoke,                  //IRC_KARAOKE                                   //0x4c
#endif                                  
ircmd_3dsound,                  //IRC_3D                                        //0x4d
ircmd_bk_slow,                  //IRC_BK_SLOW                                   //0x4e

#if defined(Ti3001_OSD_UI_1)||defined(Ti5026_OSD_UI_1)
ircmd_amp_control,      //IRC_AMP_CONTROL
#elif defined(IR_KEY_SET_VIDEO_MODE)
ircmd_set_video_mode,
#else
ircmd_reading,                  //IRC_READING                                   //0x4f
#endif

//50-5F
ircmd_root_menu,                //IRC_ROOT_MENU,                                //0x50
ircmd_play_select,              //IRC_PLAY_SELECT                               //0x51
ircmd_mix_func,                 //IRC_MIX_FUNC                              //0x52
#ifdef SUPPORT_FUNCTION_MENU
ircmd_setup_plus,               //IRC_SETUP_PLUS                            //0x53
#else
ircmd_null,                     //IRC_SLOW_BAK_FORD                             //0x53,(not use)
#endif

ircmd_book,                     //IRC_BOOK                                      //0x54

#ifdef USE_PROLOGIC_II_KEY//clead 2003-8-7 
ircmd_prologic,                 //IRC_BOOK                                      //0x55
#else
ircmd_score,                    //IRC_SCORE,                                    //0x55
#endif 

ircmd_title_return,             //IRC_TITLE_RETURN                              //0x56

#ifdef IR_SLEEP //hongfeng 2005-07-12
ircmd_sleep,                        //IRC_SLEEP                                     //0x57
#else
ircmd_echo_up,                  //IRC_ECHO_UP                                   //0x57
#endif

ircmd_echo_down,                //IRC_ECHO_DOWN                                 //0x58
ircmd_mic_up,                   //IRC_MIC_UP                                    //0x59
#ifdef VIEW_MODE_KEY
ircmd_view_mode,                //IRC_VIEW_MODE                                 //0x5a
#else
ircmd_mic_down,                 //IRC_MIC_DOWN                                  //0x5a
#endif
//reserve ir hard code to new ir cmd
ircmd_p_scan,                   //IRC_VIDEO_OUT,                                //0x5b
#ifdef EMU_MODE
ircmd_chg_dac,                  //IRC_NULL,                                     //0x5c
#else
reset_ir,                       //IRC_NULL,                                     //0x5c
#endif

#ifdef SWITCH_CD_CARD_USB
ircmd_switch_cd_card_usb,       //IRC_SWITCH_GUI                                //0x5d
ircmd_default_setup,            //IRC_NULL,                                     //0x5e
#elif defined(SUPPORT_8202_DVB) 
ircmd_dvb_dvd,		//IRC_DVB_DVD                                               //0x5d
ircmd_tv_radio,       //IRC_TV_RADIO                                            //0x5e
#elif defined(SUPPORT_EX_BASS_FUNC)//chenzhao20060117
ircmd_ex_bass_func,             //IRC_EX_BASS,                                  //0x5d
reset_ir,                       //IRC_NULL,                                     //0x5e
#else
reset_ir,                       //IRC_NULL,                                     //0x5d
ircmd_default_setup,            //IRC_NULL,                                     //0x5e
#endif


#if defined(FAT_Write_UI) || defined(FILE_MODE_WRITE)   //sunzhh 20041231
ircmd_media_control,            //IRC_MEDIA_CONTROL                                //0x5f
#else
reset_ir,                       //IRC_NULL,                                     //0x5f
#endif

//60-max

#ifdef SUPPORT_HD_RESOLUTION
ircmd_hd,                      //IRC_HD                                        //0x60 // add for HD, by robert.chang, 2006-07-12 
#endif 

#ifdef ONLY_INTERLACE_KEY
ircmd_interlace,               //IRC_INTERLACE                                 //0x60
#endif
#ifdef ONLY_VGA_KEY
ircmd_VGA,                     //IRC_VGA 
#endif                                         
#ifdef ONLY_P_SCAN_KEY
ircmd_only_P_SCAN,              //IRC_ONLY_P_SCAN                               //0x62
#endif
#if defined(ONLY_EQ_KEY)||defined(SUPPORT_RECEIVER_EQ)//chenzhao20060117
ircmd_EQ,                      //IRC_EQ 
#endif                                      
#ifdef ONLY_SOUND_FIELD_KEY
ircmd_sound_field,                 //IRC_SOUND_FEILD                               //0x64
#endif
#ifdef ONE_KEY_PASS             
ircmd_one_key_pass,            //IRC_ONE_KEY_PASS                              //0x65
#endif //ONE_KEY_PASS
#ifdef AUDIO_2CH_5_1CH
ircmd_2ch_5_1ch,               //IRC_2CH_5_1_CH                                //0x66
#endif
#ifdef RECORD_KEY
ircmd_record,                  //IRC_RECORD
#endif                                
#ifdef DIV_GOTO_DISPLAY
ircmd_search,                  //IRC_SEARCH                                    //0x68
#endif
#ifdef DISC_INFO_KEY
ircmd_disc_info,               //IRC_DISC_INFO                                 //0x69                   
#endif
#ifdef SPECTRUM_KEY   
ircmd_spectrum,               //IRC_SPECTRUM                                   //0x6a 
#endif

#ifdef IR_SWITCH_CARD_CD    //Maoyong,2004.05.13 swith between Card/CD
ircmd_switch_card_cd,
#endif

#ifdef IR_IRCMD_JUMP_30SEC  //wangwei 2004-7-20 22:30
ircmd_jump_30sec,
#endif

#ifdef SANJING_MIDI_DVD    
ircmd_main_melody,     //IRC_MAIN_MELODY
#endif

#ifdef TWO_KEY_SWITCH_TWO_SUBTITLE  //added by wangwei,2004-10-5 14:33
ircmd_switch_2nd_subtitle,
#elif defined(DVB1000_NON_OS) && defined(SUPPORT_SUBTITLE) //kehw 2005-04-27
ircmd_null,
#endif


#ifdef IR_SWITCH_CD_USB_CF_OTHER  //added by dingzhy  4-10-20 13:57
ircmd_switch_cd_usb_cf_other,		//IRC_CD_USB_CF_OTHER
#elif defined(FILE_MODE_WRITE)//added by wangwei,2005-1-10 13:07
ircmd_file_mode_write,
#elif defined(DIRECT_ACCESS_MEDIA)//added by wangwei, 2006-4-12 14:44
ircmd_source,
#endif

#if defined(DVB1000_NON_OS)
ircmd_dvb_dvd,		//IRC_DVB_DVD
//ircmd_tv_radio,       //IRC_TV_RADIO
#endif

#ifdef HONEYWLD_DVD
ircmd_dma_dvd,		//IRC_DMA_DVD
ircmd_dvd_invalid,	//IRC_DVD_INVALID
#endif

//Note:
//adjustment ir key code to 0x60 

//wanghaoying 2003-10-28 10:46
#if defined(SOUND_NO_KEYPAGE)&&defined(VTREK_DVD)
ircmd_3dsound,                      //IRC_3D2,                                      
#endif

#ifdef ONE_KEY_CONTRL_ECHO
ircmd_echo,                     //IRC_ECHO
#endif

#ifdef ONE_KEY_CONTRL_MIC
ircmd_mic,                     //IRC_MIC
#endif

#if defined(VFD_DIMMING_CONTROL)
ircmd_dimming,              //IRC_DIMMING
#endif

ircmd_only_pause,               //IRC_ONLY_PAUSE ,          //0x5b
ircmd_exit_setup,               //IRC_EXIT_SETUP,           //0x5c

#ifdef NEW_UART_COMMAND      //lijinhai define for fuss new requesst
        ircmd_av1_mode,           //0x5d
        ircmd_av2_mode,           //0x5e
        ircmd_tuner_mode,         //0x5f
        ircmd_dvd_mode,           //0x60
        ircmd_qsound,             //0x61 
        ircmd_vol_default,        //0x62
        ircmd_alarm,              //0x63
        ircmd_front_vol,          //0x64
        ircmd_center_vol,         //0x65
        ircmd_rear_vol,           //0x66
        ircmd_subwoofer_vol,      //0x67
        ircmd_treble_vol,         //0x68
        ircmd_bass_vol,           //0x69
        ircmd_balancefront_vol,   //0x6a
        ircmd_balancerear_vol,    //0x6b
#endif 

reset_ir,                       //IRC_NULL,                                     

#ifdef SUPPORT_RECEIVER  //huziqin 2004-2-26
  ircmd_rcvr_next_mode,     //0x6d
  ircmd_rcvr_function_mode,  //IRC_RCVR_FUNCTION_KEY chenzhao20060109
  #ifdef SUPPORT_VIDEO_WITH_SPDIF
    ircmd_rcvr_analog_digital,  //0x6e
  #endif
#endif

#if defined(BASS_ADJUST_KEY)
  ircmd_rcvr_bass,
#endif
#if defined(TREBLE_ADJUST_KEY)
  ircmd_rcvr_treble,
#endif
#if defined(EQ_SWITCH_KEY)
  ircmd_rcvr_EQ,        //xulf 2003-3-25
#endif
#if defined(BAND_SWITCH_KEY)
  ircmd_rcvr_band,
#endif
  
  
#ifdef SUPPORT_POWER_OFF_CLOCK_FUNC  //xyy 2004-10-12
  ircmd_set_clock,
#endif
  
#ifdef TWO_FUNC_LEFT_RIGHT_KEY
  ircmd_vfd_left,
  ircmd_vfd_right,
#endif

#ifdef SUPPORT_RECEIVER  //huziqin 2004-2-26
  ircmd_rcvr_select_mode,
#endif //SUPPORT_RECEIVER

#ifdef DOLBY_AMP_VOLUME_CTRL
    ircmd_set_treble,
    ircmd_set_bass,
#endif

#ifdef QSI_PLATFORM
    ircmd_card_cd_select,
#endif

#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
    ircmd_dvd_usb_card_avin_dvb,
#endif

#ifdef DVB_IR_SCAN_KEY
    ircmd_null,
#endif

#ifdef DVB_IR_MEMORY_FAVOR_KEY
    ircmd_null,
#endif

#ifdef DVB_IR_CHCLASS_SWITCH_KEY
    ircmd_null,
#endif

#ifdef DVB_IR_FAVOR_CLASS_KEY
    ircmd_null,
#endif

#ifdef SUPPORT_TELETEXT
    ircmd_null,
#endif

#ifdef TELETEXT_INDEX_KEY //Jack added 06/04/06
    ircmd_null,//"IRC_DVB_TTXINDEX",
#endif

#ifdef SUPPORT_TTX_MIXER_KEY //Jack added 06/04/17
    ircmd_null,//"IRC_DVB_TTXMIXER",
#endif
//IR_CODE_MAX_NUM,  // Just remark the maxium IR COMAMND Numbers. No func mapped to it!!

};
#endif//#ifdef PMP_UI

#ifdef IR_DBG
const UINT8 * const irc_func_str[IR_CODE_MAX_NUM]=
{
//00-0F
"ircmd_0",                              //IRC_0,                //0x00
"ircmd_1",                              //IRC_1,                //0x01
"ircmd_2",                              //IRC_2,                //0x02
"ircmd_3",                              //IRC_3,                //0x03
"ircmd_4",                              //IRC_4,                //0x04
"ircmd_5",                              //IRC_5,                //0x05
"ircmd_6",                              //IRC_6,                //0x06
"ircmd_7",                              //IRC_7,                //0x07
"ircmd_8",                              //IRC_8,                //0x08
"ircmd_9",                              //IRC_9,                //0x09
"ircmd_10",                             //IRC_10,               //0x0a
"ircmd_p10",                            //IRC_P10,              //0x0b
"ircmd_eject_toggle",                   //IRC_EJECT,            //0x0c
"ircmd_mute",                           //IRC_MUTE,             //0x0d
"ircmd_key_up",                         //IRC_KEY_UP,           //0x0e
"ircmd_key_reset",                      //IRC_KEY_RESET,        //0x0f
//10-1F
"ircmd_key_down",                       //IRC_KEY_DN,           //0x10
"ircmd_volume_up",                      //IRC_VOLUME_UP,        //0x11
"ircmd_volume_down",                    //IRC_VOLUME_DN,        //0x12
"ircmd_slowmotion",                     //IRC_SLOW,             //0x13
"ircmd_step",                           //IRC_STEP,             //0x14
"ircmd_pause",                          //IRC_PAUSE,            //0x15
"ircmd_play",                           //IRC_PLAY,             //0x16
"ircmd_play_resume",                    //IRC_PLAY_RESUME       //0x17
"ircmd_return",                         //IRC_RETURN,           //0x18
"ircmd_stop",                           //IRC_STOP,             //0x19
"ircmd_null",                           //IRC_LANGUAGE,         //0x1a,(not use)
"ircmd_backward",                       //IRC_BACKWARD,         //0x1b
"ircmd_forward",                        //IRC_FORWARD,          //0x1c
"ircmd_prev",                           //IRC_PREV,             //0x1d
"ircmd_next",                           //IRC_NEXT,             //0x1e
"ircmd_display",                        //IRC_DISPLAY,          //0x1f
//20-2F
"ircmd_repeat_ab",                      //IRC_AB,               //0x20
"ircmd_repeat_all",                     //IRC_REPEAT,           //0x21
"ircmd_playmode_toggle",                //IRC_PBC,              //0x22
"ircmd_goto",                           //IRC_GOTO,             //0x23
"ircmd_shuffle",                        //IRC_RANDOM,           //0x24
"ircmd_resume",                         //IRC_RESUME,           //0x25
"ircmd_remaintime",                     //IRC_TIME,             //0x26
"ircmd_power",                          //IRC_POWER,            //0x27
"ircmd_zoom",                           //IRC_ZOOM,             //0x28
"ircmd_up",                             //IRC_UP,               //0x29
"ircmd_down",                           //IRC_DOWN,             //0x2a
"ircmd_left",                           //IRC_LEFT,             //0x2b
"ircmd_right",                          //IRC_RIGHT,            //0x2c

#ifdef GBM_IRC_SHIELD_FUNCTION                   //gerry,2004-1-30 19:22
"ircmd_shield_func",                    //IRC_SHIELD_FUNC       //0x2d
#else
"reset_ir",                             //IRC_PLAY_IS_DEFAULT,  //0x2d,(not use)
#endif

#ifdef USER_MPEG_LOGO
"ircmd_mpeg_logo",                        //IRC_FREEZE,                           //0x2e,no use
#elif defined(ADD_TV_VIDEO_MODE)
"ircmd_tv_sys_mode",                      //IRC_TV_MODE,                                      //0X2e
#else
"ircmd_null",                         //IRC_FREEZE,                           //0x2e,no use
#endif 

"ircmd_channel",                        //IRC_CHANNEL,          //0x2f
//30-3F
"ircmd_channel_dn",                     //IRC_CHANNEL_DN        //0x30
"ircmd_null",                           //IRC_EFFECT,           //0x31,(not use)
"ircmd_preview",                        //IRC_PREVIEW,          //0x32
"ircmd_9frames",                        //IRC_9FRAMES,          //0x33
"ircmd_prog",                           //IRC_PROGRAM,          //0x34
"ircmd_display_format_toggle",          //IRC_FORMAT,           //0x35
"ircmd_intro",                          //IRC_INTRO,            //0x36

#ifdef CAR_VCD//kenny 891220 modify
"ircmd_next_disk",                      //IRC_NEXT_DISK         //0x37
"ircmd_pre_disk",                       //IRC_PRE_DISK          //0x38
"ircmd_reset_changer",                  //IRC_RES_CHG           //0x39
#elif defined(DIRECT_ACCESS_MEDIA)//added by wangwei
#ifndef NO_DVD_SERVO
"ircmd_key_disc",                    //0x37
#else//NO_DVD_SERVO
"ircmd_null",
#endif//NO_DVD_SERVO

#ifdef SUPPORT_USB
"ircmd_key_usb",                     //0x38
#else//SUPPORT_USB
"ircmd_null",
#endif//SUPPORT_USB

#ifdef SPHE8202_CARD_STORAGE
"ircmd_key_card",                    //0x39
#else//SPHE8202_CARD_STORAGE
"ircmd_null",
#endif//SPHE8202_CARD_STORAGE

#elif defined(SUPPORT_OP_FIVE_DISC)//chenzhao20060107
"ircmd_panel_disc_1",             //IRC_DISC_1                  //0x37
"ircmd_panel_disc_2",             //IRC_DISC_2                  //0x38
"ircmd_panel_disc_3",             //IRC_DISC_3                  //0x39
#else
"ircmd_null",                           //IRC_GAME_L,           //0x37
"ircmd_null",                           //IRC_GAME_R,           //0x38
"ircmd_null",                           //IRC_GAME_UP,          //0x39
#endif

#ifdef TWO_FUN_IN_ONE_VFD_KEY    //dingzhy for GBM
"ircmd_vfd_next",                           //IRC_VFD_NEXT,          //0x3a
"ircmd_vfd_prev",                           //IRC_VFD_PREV,          //0x3b
#else
"ircmd_null",                           //IRC_GAME_DN,          //0x3a
"ircmd_null",                           //IRC_GAME_TN,          //0x3b
#endif

#if defined(SUPPORT_OP_FIVE_DISC) && !defined(SUPPORT_5DISC_EXCHANGE)  //chenzhao 2006-4-20 11:5 .
"ircmd_panel_all_eject",          //IRC_ALL_EJECT               //0x3c
#else
"ircmd_null",                           //IRC_GAME_UL,          //0x3c
#endif
"ircmd_null",                           //IRC_GAME,             //0x3d,(not use)
"ircmd_null",                           //IRC_FOCUS,            //0x3e,(not use)
    
#ifdef SUPPORT_OP_FIVE_DISC  //OP add
"ircmd_panel_disc_4",             //IRC_DISC_4,                 //0x3f
"ircmd_panel_disc_5",             //IRC_DISC_5,                 //0x40
"ircmd_panel_exchange",           //IRC_EXCHANGE,               //0x41
#else //SUPPORT_OP_FIVE_DISC
"ircmd_disk1",                          //IRC_DISK1,            //0x3f
//40-4F
#ifdef MUTE_DEMUTE_HAVE_TWE_VALUE_IN_ONE_KEY  //2005-4-21 13:29 zhoulin
"ircmd_indiv_MUTE",
"ircmd_indiv_DEMUTE",
#else
"ircmd_disk2",                          //IRC_DISK2,            //0x40
"ircmd_disk3",                          //IRC_DISK3,            //0x41
#endif
#endif//#ifdef SUPPORT_FIVE_DISC

"ircmd_play_pause",                     //IRC_PAUSEPLAY,        //0x42
"ircmd_null",                           //IRC_QUALIFY           //0x43,(not use)
"ircmd_null",                      //IRC_RESET_DSP         //0x44
#ifdef DOUBLE_TITLE //susu add 2003-8-26 10:30
"ircmd_double_picture",
#else
"ircmd_sub_picture",                    //IRC_SUBP              //0x45                                     //0x45
#endif
"ircmd_angle",                          //IRC_ANGLE             //0x46
"ircmd_audio_language",                 //IRC_AUD_LANGUAGE      //0x47
"ircmd_select",                         //IRC_SELECT            //0x48
"ircmd_title_menu",                     //IRC_TITLEMENU         //0x49
"ircmd_clear",                          //IRC_CLEAR             //0x4a
#ifdef OP_PLAYMODE
"irvmd_mode",
#else
"ircmd_setup",                          //IRC_SETUP             //0x4b
#endif
#ifdef OP_IR
"ircmd_eixt",
#else
"ircmd_karaoke",                        //IRC_KARAOKE           //0x4c
#endif
"ircmd_3dsound",                        //IRC_3D                //0x4d
"ircmd_bk_slow",                        //IRC_BK_SLOW           //0x4e

#if defined(Ti3001_OSD_UI_1)||defined(Ti5026_OSD_UI_1)
"ircmd_amp_control",                    //IRC_AMP_CONTROL       //0x4f
#elif defined(IR_KEY_SET_VIDEO_MODE)
"ircmd_set_video_mode",
#else
"ircmd_reading",                        //IRC_READING           //0x4f
#endif

//50-max.
"ircmd_root_menu",                      //IRC_ROOT_MENU         //0x50
"ircmd_play_select",                    //IRC_PLAY_SELECT       //0x51
"ircmd_mix_func",                       //IRC_DISPLAY_TIME      //0x52
"ircmd_null",                           //IRC_SLOW_BAK_FORD     //0x53,(not use)

#ifdef USE_PROLOGIC_II_KEY//clead 2003-8-7 
"ircmd_prologic",                           //IRC_BOOK              //0x54
#else
"ircmd_book",                           //IRC_BOOK              //0x54
#endif

"ircmd_score",                          //IRC_SCORE,            //0x55
"ircmd_title_return",                   //IRC_TITLE_RETURN      //0x56
"ircmd_echo_up",                        //IRC_ECHO_UP           //0x57
"ircmd_echo_down",                      //IRC_ECHO_DOWN         //0x58
"ircmd_mic_up",                         //IRC_MIC_UP            //0x59
"ircmd_mic_down",                       //IRC_MIC_DOWN          //0x5a

//reserve ir hard code to new ir cmd
"ircmd_p_scan",                         //IRC_VIDEO_OUT,        //0x5b

#ifdef EMU_MODE
"ircmd_chg_dac",                        //IRC_NULL,             //0x5c
#else
"reset_ir",                             //IRC_NULL,             //0x5c
#endif

#if defined(SUPPORT_8202_DVB)    //sunzhh add 20050430
"ircmd_dvb_dvd",		//IRC_DVB_DVD
"ircmd_tv_radio",       //IRC_TV_RADIO
#elif defined(SUPPORT_EX_BASS_FUNC)//chenzhao20060117
"ircmd_ex_bass_func",                   //IRC_EX_BASS,          //0x5d
"reset_ir",                             //IRC_NULL,             //0x5e
#else
"reset_ir",                             //IRC_NULL,             //0x5d
"ir_default_setup",                     //IRC_NULL,             //0x5e
#endif                            

#if defined(FAT_Write_UI) || defined(FILE_MODE_WRITE)   //sunzhh 20041231
"ircmd_media_control",            //IRC_MEDIA_CONTROL                                //0x5f
#else
"reset_ir",                             //IRC_NULL,             //0x5f
#endif

// 60-IR_CODE_MAX_NUM

#ifdef SUPPORT_HD_RESOLUTION              
"ircmd_hd",                             //IRC_HD                 //0x60    // add for HD, by robert.chang, 2006-07-12       
#endif 

#ifdef ONLY_INTERLACE_KEY
"ircmd_interlace",                      //IRC_INTERLACE          //0x60
#endif
#ifdef ONLY_VGA_KEY
"ircmd_VGA",                            //IRC_VGA                //0x61
#endif
#ifdef ONLY_P_SCAN_KEY
"ircmd_only_P_SCAN",                     //IRC_ONLY_P_SCAN        //0x62
#endif
#if defined(ONLY_EQ_KEY)||defined(SUPPORT_RECEIVER_EQ)//chenzhao20060117
"ircmd_EQ",                            //IRC_EQ                 //0x63
#endif
#ifdef ONLY_SOUND_FIELD_KEY
"ircmd_sound_field",                       //IRC_SOUND_FIELD        //0x64
#endif
#ifdef ONE_KEY_PASS             
"ircmd_one_key_pass",                  //IRC_ONE_KEY_PASS       //0x65
#endif //ONE_KEY_PASS
#ifdef AUDIO_2CH_5_1CH
"ircmd_2ch_5_1ch",                     //IRC_2CH_5_1_CH         //0x66
#endif
#ifdef RECORD_KEY
"ircmd_record",                        //IRC_RECORD             //0x67
#endif
#ifdef DIV_GOTO_DISPLAY
"ircmd_search",                        //IRC_SEARCH             //0x68
#endif
#ifdef DISC_INFO_KEY
"ircmd_disc_info",                     //IRC_DISC_INFO          //0x69
#endif
#ifdef SPECTRUM_KEY                    //IRC_SPECTRUM           //0x6a
"ircmd_spectrum",
#endif

#ifdef IR_SWITCH_CARD_CD              //IRC_SWITCH_CARD_CD
"ircmd_switch_card_cd",
#endif

#ifdef IR_IRCMD_JUMP_30SEC  //wangwei 2004-7-20 22:30
"ircmd_jump_30sec",                   //IRC_JUMP_30SEC
#endif

#ifdef SANJING_MIDI_DVD    
"ircmd_main_melody",     //IRC_MAIN_MELODY
#endif

#ifdef TWO_KEY_SWITCH_TWO_SUBTITLE  //added by wangwei,2004-10-5 14:33
"ircmd_switch_2nd_subtitle",
#elif defined(DVB1000_NON_OS) && defined(SUPPORT_SUBTITLE) //kehw 2005-04-27
"ircmd_null",
#endif

#ifdef IR_SWITCH_CD_USB_CF_OTHER  //added by dingzhy  4-10-20 13:57
"ircmd_switch_cd_usb_cf_other",		//IRC_CD_USB_CF_OTHER
#elif defined(FILE_MODE_WRITE)//added by wangwei,2005-1-10 13:09
"ircmd_file_mode_write",
#elif defined(DIRECT_ACCESS_MEDIA)//added by wangwei, 2006-4-12 14:46
"ircmd_source",
#endif

#if defined(DVB1000_NON_OS)
"ircmd_dvb_dvd",		//IRC_DVB_DVD
//"ircmd_tv_radio",       //IRC_TV_RADIO//?? sunzhh add 20050430
#endif

//wanghaoying 2003-10-28 10:46
#if defined(SOUND_NO_KEYPAGE)&&defined(VTREK_DVD)
"ircmd_3dsound",                      //IRC_3D2,                                      
#endif

#ifdef ONE_KEY_CONTRL_ECHO
"ircmd_echo",                     //IRC_ECHO
#endif

#ifdef ONE_KEY_CONTRL_MIC
"ircmd_mic",                     //IRC_MIC
#endif

#if defined(VFD_DIMMING_CONTROL)
"ircmd_dimming",                //IRC_DIMMING
#endif

"ircmd_only_pause",                     //IRC_ONLY_PAUSE ,      //0x5b
"ircmd_exit_setup",                     //IRC_EXIT_SETUP,       //0x5c

#ifdef NEW_UART_COMMAND      //lijinhai define for fuss new requesst
        "ircmd_av1_mode",           //0x5d
        "ircmd_av2_mode",           //0x5e
        "ircmd_tuner_mode",         //0x5f
        "ircmd_dvd_mode",           //0x60
        "ircmd_qsound",             //0x61 
        "ircmd_vol_default",        //0x62
        "ircmd_alarm",              //0x63
        "ircmd_front_vol",          //0x64
        "ircmd_center_vol",         //0x65
        "ircmd_rear_vol",           //0x66
        "ircmd_subwoofer_vol",      //0x67
        "ircmd_treble_vol",         //0x68
        "ircmd_bass_vol",           //0x69
        "ircmd_balancefront_vol",   //0x6a
        "ircmd_balancerear_vol",    //0x6b
#endif 

"reset_ir",             //IRC_NULL,             //0x5D
#ifdef SUPPORT_RECEIVER  //huziqin 2004-2-26
"ircmd_rcvr_next_mode",		//0x6d
"ircmd_rcvr_function_mode",  //IRC_RCVR_FUNCTION_KEY chenzhao20060109
#ifdef SUPPORT_VIDEO_WITH_SPDIF
"ircmd_rcvr_analog_digital",	//0x6e
#endif
#endif

#if defined(BASS_ADJUST_KEY)
  "ircmd_rcvr_bass",
#endif
#if defined(TREBLE_ADJUST_KEY)
  "ircmd_rcvr_treble",
#endif
#if defined(EQ_SWITCH_KEY)
  "ircmd_rcvr_EQ",        //xulf 2003-3-25
#endif

#if defined(BAND_SWITCH_KEY)
  "ircmd_rcvr_band",
#endif
  
  
#ifdef SUPPORT_POWER_OFF_CLOCK_FUNC  //xyy 2004-10-12
  "ircmd_set_clock",
#endif
  

#ifdef SUPPORT_RECEIVER  //huziqin 2004-2-26
"ircmd_rcvr_select_mode",
#endif //SUPPORT_RECEIVER

#ifdef DOLBY_AMP_VOLUME_CTRL
	"ircmd_set_treble",
	"ircmd_set_bass",
#endif

#ifdef QSI_PLATFORM
    "ircmd_card_cd_select",
#endif

#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
    "ircmd_dvd_usb_card_avin_dvb",
#endif

#ifdef DVB_IR_SCAN_KEY
    "reset_ir",
#endif

#ifdef DVB_IR_MEMORY_FAVOR_KEY
    "reset_ir",
#endif

#ifdef DVB_IR_CHCLASS_SWITCH_KEY
    "reset_ir",
#endif
#ifdef DVB_IR_FAVOR_CLASS_KEY
    "reset_ir",
#endif

#ifdef SUPPORT_TELETEXT
    "reset_ir",
#endif
#ifdef TELETEXT_INDEX_KEY //Jack added 06/04/06
    "DVBGui_TTXIndexFunc",//"IRC_DVB_TTXINDEX",
#endif

#ifdef SUPPORT_TTX_MIXER_KEY //Jack added 06/04/17
    "DVBGui_TTXMixerFunc",//"IRC_DVB_TTXMIXER",
#endif
//IR_CODE_MAX_NUM,  // Just remark the maxium IR 
//IR_CODE_MAX_NUM,  // Just remark the maxium IR COMAMND Numbers. No func mapped to it!!

};
#endif//#ifdef IR_DBG


