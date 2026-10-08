#ifndef __IRCONFIG_H
#define __IRCONFIG_H


void call_ir_func(BYTE rx);

#define IRC_MASK        0x00ff

typedef void (*IRCMDFUNC) ();

typedef void (*IRFUNC) ();

enum
{
// 00-0F
IRC_0,                          //0x00
IRC_1,                          //0x01
IRC_2,                          //0x02
IRC_3,                          //0x03
IRC_4,                          //0x04
IRC_5,                          //0x05
IRC_6,                          //0x06
IRC_7,                          //0x07
IRC_8,                          //0x08
IRC_9,                          //0x09
IRC_10,                         //0x0a
IRC_P10,                        //0x0b
IRC_EJECT,                      //0x0c
IRC_MUTE,                       //0x0d  T:(靜音)
IRC_KEY_UP,                     //0x0e
IRC_KEY_RESET,                  //0x0f
//10-1F
IRC_KEY_DN,                     //0x10  T:key-
IRC_VOLUME_UP,                  //0x11  T:(音量+)
IRC_VOLUME_DN,                  //0x12  T:(音量-)
IRC_SLOW,                       //0x13
IRC_STEP,                       //0x14
IRC_PAUSE,                      //0x15
IRC_PLAY,                       //0x16
IRC_PLAY_RESUME,                //0x17
IRC_RETURN,                     //0x18
IRC_STOP,                       //0x19
IRC_LANGUAGE,                   //0x1a
IRC_BACKWARD,                   //0x1b  Picture- T:(畫面-)
IRC_FORWARD,                    //0x1c  Picture+ T:(畫面+)
IRC_PREV,                       //0x1d 
IRC_NEXT,                       //0x1e
IRC_DISPLAY,                    //0x1f  Display T:(顯示)
//20-2F
IRC_AB,                         //0x20  B
IRC_REPEAT,                     //0x21  A
IRC_PBC,                        //0x22  Manu T:(選單)
IRC_GOTO,                       //0x23  SetTime T:(選時)
IRC_RANDOM,                     //0x24
IRC_RESUME,                     //0x25
IRC_TIME,                       //0x26
IRC_POWER,                      //0x27  Power T:(電源)
IRC_ZOOM,                       //0x28
IRC_UP,                         //0x29
IRC_DOWN,                       //0x2a
IRC_LEFT,                       //0x2b
IRC_RIGHT,                      //0x2c

#ifdef GBM_IRC_SHIELD_FUNCTION              //gerry,2004-1-30 19:24           
IRC_SHIELD,                     //0x2d                     
#elif TOUCH_MENU//frank.huang 050801          
IRC_TOUCH_MENU, 				//0x2d                     
#else 
IRC_PLAY_IS_DEFAULT,            //0x2d
#endif

#ifdef USER_MPEG_LOGO
IRC_MPEG_LOGO,                     //0x2e
#elif defined(ADD_TV_VIDEO_MODE)
IRC_TV_MODE,
#else
IRC_FREEZE,                     //0x2e
#endif 

IRC_CHANNEL,                    //0x2f
//30-3F
IRC_CHANNEL_DN,                 //0x30

#ifdef CNTR_5SPK_VOLUME
IRC_VOLUME_SWITCH,              //0x31
#else
IRC_EFFECT,                     //0x31 sound mode
#endif

IRC_PREVIEW,                    //0x32
IRC_9FRAMES,                    //0x33
IRC_PROGRAM,                    //0x34
IRC_FORMAT,                     //0x35
IRC_INTRO,                      //0x36

#ifdef CAR_VCD  
IRC_NEXT_DISK,                  //0x37
IRC_PRE_DISK,                   //0x38
IRC_RES_CHG,                    //0x39
////////////tw_kevin.lo040901  
#elif defined(BRIGHTNESS_COLOR_KEY)
IRC_BRICOL_ADJUST,		//0x37 tulijuan040901
IRC_GAME_R,                     //0x38
IRC_GAME_UP,                    //0x39
#elif defined(DIRECT_ACCESS_MEDIA)//added by wangwei, 2006-6-8 11:30
#ifndef NO_DVD_SERVO
IRC_KEY_DISC,                    //0x37
#else//NO_DVD_SERVO
IRC_GAME_L,
#endif//NO_DVD_SERVO

#ifdef SUPPORT_USB
IRC_KEY_USB,                     //0x38
#else//SUPPORT_USB
IRC_GAME_R,
#endif//SUPPORT_USB

#ifdef SPHE8202_CARD_STORAGE
IRC_KEY_CARD,                    //0x39
#else//SPHE8202_CARD_STORAGE
IRC_GAME_UP,
#endif//SPHE8202_CARD_STORAGE
#elif defined (SUPPORT_OP_FIVE_DISC)//chenzhao20060107
IRC_DISC_1,					//0x37
IRC_DISC_2,					//0x38
IRC_DISC_3,					//0x39
#else
IRC_GAME_L,                     //0x37
IRC_GAME_R,                     //0x38
IRC_GAME_UP,                    //0x39
#endif

#ifdef TWO_FUN_IN_ONE_VFD_KEY   //dingzhy for GBM 
IRC_VFD_NEXT,                    //0x3a
IRC_VFD_PREV,                    //0x3b
#else
IRC_GAME_DN,                    //0x3a
IRC_GAME_TN,                    //0x3b
#endif

#if defined(SUPPORT_OP_FIVE_DISC) && !defined(SUPPORT_5DISC_EXCHANGE)  //chenzhao 2006-4-20 11:2 .
IRC_ALL_EJECT,			//0x3c
#else
IRC_GAME_UL,                    //0x3c
#endif
IRC_GAME,                       //0x3d
IRC_VIRTUAL_KEYBOARD,           //0x3e, // alan, 2003/8/16 05:02AM
#ifdef SUPPORT_OP_FIVE_DISC  //chenzhao20060107
IRC_DISC_4,               //0x3f
IRC_DISC_5,               //0x40
IRC_EXCHANGE,              //0x41
#else
IRC_DISK1,                      //0x3f
//40-4F
#ifdef MUTE_DEMUTE_HAVE_TWE_VALUE_IN_ONE_KEY//2005-4-19 10:23 zhoulin
IRC_indiv_MUTE,                 //0x40
IRC_indiv_DEMUTE,               //0x41
#else
IRC_DISK2,                      //0x40
IRC_DISK3,                      //0x41
#endif
#endif//#ifdef SUPPORT_FIVE_DISC
IRC_PAUSEPLAY,                  //0x42
IRC_QUALIFY,                    //0x43
IRC_RESET_DSP,                  //0x44
IRC_SUBP,                       //0x45
IRC_ANGLE,                      //0x46
IRC_AUD_LANGUAGE,               //0x47
IRC_SELECT,                     //0x48
IRC_TITLEMENU,                  //0x49
IRC_CLEAR,                      //0x4a
#ifdef OP_PLAYMODE //lijd 2005-4-12 13:28
IRC_MODE,                       //0x4b
#else
IRC_SETUP,                      //0x4b
#endif                      
#ifdef OP_IR 
IRC_EXIT,                       //0x4c
#else
IRC_KARAOKE,                    //0x4c
#endif//#ifdef OP_IR //lijd 2005-4-12 13:28
IRC_3D,                         //0x4d
IRC_BK_SLOW,                    //0x4e



#if defined(Ti3001_OSD_UI_1)||defined(Ti5026_OSD_UI_1)
IRC_AMP_CONTROL,        //0x4f
#elif defined(IR_KEY_SET_VIDEO_MODE)
IRC_VIDEO_MODE,                 //0x4f
#else
IRC_READING,                    //0x4f
#endif

//50-5F
IRC_ROOT_MENU,                  //0x50
IRC_PLAY_SELECT,                //0x51
IRC_MIX_FUNC,                   //0x52
#ifdef SUPPORT_FUNCTION_MENU
IRC_SETUP_PLUS,                 //0x53
#else
IRC_SLOW_BAK_FORD,              //0x53
#endif

IRC_BOOK,                       //0x54

#ifdef USE_PROLOGIC_II_KEY                                      //clead 2003-8-7 
IRC_PROLOGIC,                       //0x55
#else
IRC_SCORE,                      //0x55
#endif 

IRC_TITLE_RETURN,               //0x56

#ifdef IR_SLEEP //hongfeng 2005-07-12
IRC_SLEEP,                          //0x57
#else
IRC_ECHO_UP,                    //0x57
#endif

IRC_ECHO_DOWN,                  //0x58
IRC_MIC_UP,                     //0x59
#ifdef VIEW_MODE_KEY
IRC_VIEW_MODE,                  //0x5a
#else
IRC_MIC_DOWN,                   //0x5a
#endif
IRC_P_SCAN,                     //0x5b
IRC_CHG_DAC,                    //0x5c

#ifdef SWITCH_CD_CARD_USB
IRC_SWITCH_GUI,                 //0x5d
IRC_DEFAULT_SETUP,              //0x5e
#elif defined(SUPPORT_8202_DVB) //sunzhh 20050430
IRC_DVB_DVD,                    //0x5d
IRC_TV_RADIO,                   //0x5e
#elif defined(SUPPORT_EX_BASS_FUNC)//chenzhao20060117
IRC_EX_BASS,                    //0c5d
IRC_NULL5e,                     //0x5e
#else
IRC_NULL5d,                     //0x5d
IRC_DEFAULT_SETUP,              //0x5e
#endif

#if defined(FAT_Write_UI) || defined(FILE_MODE_WRITE)        //sunzhh add 2004-10-18 17:41
IRC_MEDIA_CONTROL,               //0x5f
#else
IRC_NULL5f,                     //0x5f
#endif

//-----------------------------------------------------------------------------------------------------------
// Below this line everybody can create a new key defination. 
// Notice: You MUST insert the new key defination here and in irc_function_name_tbl.c as the same sequence.
//         If you don't know the detail very much, call nono or me.
//         wanghaoying 2005-9-20 15:24
//60-max

#ifdef SUPPORT_HD_RESOLUTION  // add for HD, by robert.chang, 2006-07-12 
IRC_HD,
#endif 

#ifdef ONLY_INTERLACE_KEY
IRC_INTERLACE,                   //0x60
#endif
#ifdef ONLY_VGA_KEY
IRC_VGA,                         //0x61
#endif
#ifdef ONLY_P_SCAN_KEY
IRC_ONLY_P_SCAN,                  //0x62
#endif
#if defined(ONLY_EQ_KEY)||defined(SUPPORT_RECEIVER_EQ)//chenzhao20060117
IRC_EQ,                          //0x63
#endif
#ifdef ONLY_SOUND_FIELD_KEY
IRC_SOUND_FIELD,                 //0x64
#endif
#ifdef ONE_KEY_PASS
IRC_ONE_KEY_PASS,                //0x65
#endif
#ifdef AUDIO_2CH_5_1CH
IRC_2CH_5_1_CH,                  //0x66
#endif
#ifdef RECORD_KEY
IRC_RECORD,                      //0x67
#endif
#ifdef DIV_GOTO_DISPLAY
IRC_SEARCH,                      //0x68
#endif
#ifdef DISC_INFO_KEY
IRC_DISC_INFO,                   //0x69
#endif
#ifdef SPECTRUM_KEY             // 0x6a
IRC_SPECTRUM,
#endif

#ifdef IR_SWITCH_CARD_CD        //0x6b,Maoyong,2004.05.13 swith between Card/CD
IRC_SWITCH_CARD_CD,
#endif

#ifdef IR_IRCMD_JUMP_30SEC      //0x6c,wangwei 2004-7-20 22:30
IRC_JUMP_30SEC,
#endif

#ifdef SANJING_MIDI_DVD    
IRC_MAIN_MELODY,          //ouyang 2004-10-29 9:54
#endif

#if defined(TWO_KEY_SWITCH_TWO_SUBTITLE) //|| defined(SUPPORT_SUBTITLE)//Jack mark 06/02/16
//#if defined(TWO_KEY_SWITCH_TWO_SUBTITLE) || (defined(DVB1000_NON_OS) && defined(SUPPORT_SUBTITLE))
IRC_2ND_SUBTITLE,
#endif

#ifdef IR_SWITCH_CD_USB_CF_OTHER  //0x6e  added by dingzhy  4-10-20 13:57
IRC_CD_USB_CF_OTHER,
#elif defined(FILE_MODE_WRITE)//added by wangwei,2005-1-10 13:12
IRC_FM_WRITE,
#elif defined(DIRECT_ACCESS_MEDIA)//added by wangwei, 2006-4-12 14:40
IRC_SW_MEDIA,
#endif

#if defined(DVB1000_NON_OS)
IRC_DVB_DVD,
//IRC_TV_RADIO,
#endif

#ifdef DMA_DVD_SWITCH	//xsyan
IRC_SWITCH_DMA_DVD,     //0x60
#endif

#ifdef HONEYWLD_DVD
IRC_DMA_DVD,
IRC_DVD_INVALID,
#endif

//Note:
//adjustment ir key code to 0x60 

//freyman add 2002-9-3 10:30
#ifdef IR25
IRC_AMP_VOLUME,                 //0x5b+0x05
#endif
//wanghaoying 2003-10-28 10:46
#if defined(SOUND_NO_KEYPAGE)&&defined(VTREK_DVD)
IRC_3D2,
#endif

#if defined(ONE_KEY_CONTRL_ECHO)
IRC_ECHO,
#endif

#if defined(ONE_KEY_CONTRL_MIC)
IRC_MIC,
#endif

#if defined(VFD_DIMMING_CONTROL)
IRC_DIMMING,
#endif

IRC_ONLY_PAUSE,     //0x5b+0x5
IRC_EXIT_SETUP,     //0x5c+0x5

#ifdef NEW_UART_COMMAND  //lijinhai define for fuss new request
IRC_AV1_MODE,       //0x5d+0x5
IRC_AV2_MODE,       //0x5e+0x5
IRC_TUNER_MODE,     //0x5f+0x5
IRC_DVD_MODE,       //0x60+0x5
IRC_QSOUND,         //0x61+0x5
IRC_VOL_DEFAULT,    //0x62+0x5
IRC_ALARM,          //0x63+0x5
IRC_FRONT_VOL,      //0x64+0x5
IRC_CENTER_VOL,     //0x65+0x5
IRC_REAR_VOL,       //0x66+0x5
IRC_SUBWOOFER_VOL,  //0x67+0x5
IRC_TREBLE_VOL,     //0x68+0x5
IRC_BASS_VOL,       //0x69+0x5
IRC_BALANCEFRONT_VOL,   //0x6a+0x5
IRC_BALANCEREAR_VOL,    //0x6b+0x5
#endif 

#ifdef TONIC_DVD
IRC_KEYLOCK,
#endif

IRC_NULL,

#ifdef SUPPORT_RECEIVER //huziqin 2004-2-26
// There are currently no buttons on the remote control
// that are intended for switching modes.
// In the future, fill in ir_mapcode[] in ircode_sunplus_8200.h (<-- example) when needed.
// For now, IRC_P_SCAN and IRC_DISPLAY are used for modes (special case in call_ir_func() in ir_parser.c)

 IRC_RCVR_NEXT_MODE,        //0x6d
 IRC_RCVR_FUNCTION_KEY,          //chenzhao 20060109
 #ifdef SUPPORT_VIDEO_WITH_SPDIF
    IRC_RCVR_ANALOG_DIGITAL,    //0x6e
 #endif
#endif
 
#if defined(BASS_ADJUST_KEY)
//xulf added temporarily 2004-3-7
IRC_RCVR_LEVEL,
#endif

#if defined(TREBLE_ADJUST_KEY)
IRC_RCVR_TONE,
#endif

#if defined(EQ_SWITCH_KEY)
IRC_RCVR_EQ,
#endif

#if defined(BAND_SWITCH_KEY)
IRC_RCVR_BAND,
#endif

#ifdef SUPPORT_POWER_OFF_CLOCK_FUNC  //xyy 2004-10-12
IRC_SET_CLOCK,
#endif

#ifdef TWO_FUNC_IN_LEFT_RIGHT_KEY//xyy add 2004-11-10 9:25
IRC_VFD_LEFT,
IRC_VFD_RIGHT,
#endif


#ifdef SUPPORT_RECEIVER //huziqin 2004-2-26
// Commands for each mode selection button
// This HAS TO BE in the same order as the enum in gb_def.h
// Otherwise, each button will be mixed up
 IRC_RCVR_SELECT_DVD,       //0x6f
 IRC_RCVR_SELECT_AV1,       //0x70
 IRC_RCVR_SELECT_AV2,       //0x71
 IRC_RCVR_SELECT_SPDIF,     //0x72
 IRC_RCVR_SELECT_TUNER,     //0x73
 IRC_RCVR_SELECT_DUMMY,     //0x74  development only
 #ifdef DOLBY_AMP_VOLUME_CTRL
 IRC_SET_TRE,
 IRC_SET_BASS,
 #endif
#endif

 #ifdef QSI_PLATFORM //qsi: added by johnson 20040812, for card/cd switch
 IRC_SRC_SEL,               //0x75
 #endif

#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
    IRC_DVD_USB_CARD_AVIN_DVB,
#endif

#ifdef DVB_IR_SCAN_KEY
 IRC_SCAN,
#endif
    
#ifdef DVB_IR_MEMORY_FAVOR_KEY                ////sunzhh add 20051025
 IRC_FAVOR,
#endif
    
#ifdef DVB_IR_CHCLASS_SWITCH_KEY
 IRC_PRLIST,
#endif
    
#ifdef DVB_IR_FAVOR_CLASS_KEY
 IRC_FAVOR_CLASS,
#endif
        
#ifdef SUPPORT_TELETEXT
 IRC_TTX,
#endif



IR_CODE_MAX_NUM,       //Just remark the maxium IR COMAMND Numbers. No func mapped to it!!
};


//extern const UINT8 StateChkKey[];

#if defined(IR_NEC)||defined(IR_MRC2222)//frank.huang 050801
    //
    // NEC type IR
    //
    #define IR_MISC             0x001f
    #define IR_WAVEFORM_AIS     0x0d1a
    #define IR_PRE_CD_NEC       0x366c
    #define IR_RPT_EF_NEC       0x1e6c
    #define IR_PRE_RPT_NEC      0x1806
    #define IR_PRE_PHILIPS      0x0020
    #define IR_PRE_PATT_PHILIPS 0
    #define IR_GUARD            0x0000
    #define IR_ADDR_DATA_CONFIG 0x057f
#elif defined(IR_THOMSON)||defined(IR_AS1213)||defined(IR_M3004)||defined(IR_KONKA)||defined(IR_TDP101)||defined(IR_ORITRON)//LIJD 2005-2-4 13:21
    //
    // THOMSON type IR
    //
    #define IR_MISC             0x001f
    #define IR_WAVEFORM_AIS     0x0d1a
    #define IR_PRE_CD_NEC       0x366c
    #define IR_RPT_EF_NEC       0x1e6c
    #define IR_PRE_RPT_NEC      0x1806
    #define IR_PRE_PHILIPS      0x0020
    #define IR_PRE_PATT_PHILIPS 0
    #define IR_GUARD            0x0000
    #define IR_ADDR_DATA_CONFIG 0x057f    
    
#elif defined(IR_PHILIPS)
    //
    // PHILIPS type IR
    //
    //#define   IR_MISC         0x001d
    #define IR_MISC             0x0019 //kenny 2001/1/15
    #define IR_WAVEFORM_AIS     0x0d1c  // 0x0d15 orig.
    #define IR_PRE_CD_NEC       0
    #define IR_RPT_EF_NEC       0
    #define IR_PRE_RPT_NEC      0
    #define IR_PRE_PHILIPS      0x0002
    //#define   IR_PRE_PATT_PHILIPS 0x0007
    #define IR_PRE_PATT_PHILIPS 0x0000 //kenny 2001/1/15
    #define IR_GUARD            0x0000
    #define IR_ADDR_DATA_CONFIG 0x0054

 #elif defined(IR_PHILIPS_EASTECH)
	//
	//PHILIPS RC_6 TYPE IR
	//#define IR_MISC  0x001d
	#define IR_MISC				0X0019
	#define IR_PRE_CD_NEC		0
	#define IR_RPT_EF_NEC   	0
	#define IR_RPE_RPT_NEC  	0
	#define IR_PRE_PHILIPS  	0X0002
	#define IR_PRE_PATT_PHILIPS	0X0000
	#define IR_GUARD     		0X0000
	#define IR_ADDR_DATA_CONFIG	0x0054                  
#elif defined(IR_HT220MCU)    //2005-4-14 14:56 zhoulin

    
#else
    //
    // ???? type IR
    //
#
#error  -1 - you must define your IR type
#
    #define IR_MISC             0
    #define IR_WAVEFORM_AIS     0
    #define IR_PRE_CD_NEC       0
    #define IR_RPT_EF_NEC       0
    #define IR_PRE_RPT_NEC      0
    #define IR_PRE_PHILIPS      0
    #define IR_PRE_PATT_PHILIPS 0
    #define IR_GUARD            0
    #define IR_ADDR_DATA_CONFIG 0
#endif

#ifndef IR_ADDR_PATT
#error -1 IR_ADDR_PATT not defined.
#endif

#endif/*__IRCONFIG_H*/

