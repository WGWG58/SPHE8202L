#define VERSION_STRING      "G32-000"   //version: xxx-yyy, 20030422

#ifdef SUPPORT_SPG_GAME
    #define SUPPORT_NESGAME
#endif   

#ifdef SUPPORT_ELA
    #define SUPPORT_WAV
    #define SUPPORT_MP4
#endif  

//#define IC_8202D  // 2004/12/27 yltseng
// Currently, when using this define, it won't download mp3 tables for this IC

//---------------------
//board parts settings
//---------------------
//SDRAM settings(bus width, default is 16-bits mode)
#define SDRAM_BUS_32BITS        //define it to use 32 bits SDRAM Bus width
//#define SDRAM_16Mb_Mode       //only use 16Mb*1 SDRAM

/*
* Define Disc detect polling time
*/
#define DETECT_TIMES    0xff
#define NO_DISC_TIMES   30

/*
*  Video seting
*/
/*#define TV_YUV_OUT*/
#define S_VIDEO_OUT

//CD-G related
#define SUPPORT_CDG                 //define it to support CD-G


//#define TVOUT6_4DAC_ON
//#define SUNPLUS_8202P_DEMOBOARD


#ifdef TVOUT6_4DAC_ON
#define TV_USE_4_DAC
#endif

//#define TV_USE_4_DAC
//#define AUTO_ADJUST_TV_TYPE         //auto adjust tv type (16:9 ,4:3LB,4:3PS) from disc  //lijd 2004-9-15 13:25

//Upgrade setting
#define UPGRADE_FILE_NAME   {"DVDROM.BIN"}
//#define SUPPORT_UART_UPGRADE      //Upgrade flash via UART, Robert 020603
#define RESET_AFTER_UPGRADE         //reset 8200 and tray out after smart upgrade
//#define UPGRADE_TRAYOUT               //joshua 2004/07/13 tray out when dvdrom.bin have been moved to sdram

#ifndef SDRAM_16Mb_Mode
//#define SUPPORT_NESGAME
//#define DVD_AUDIO
#endif

#ifdef  SUPPORT_NESGAME   //for VFD pannel key valid in PLAY game state  2004-7-2 15:16 lijd
//#define SUPPORT_IR_GAME
#define VFDKEYBUFADDR      0x588
#endif

//audio DAC settings, chose one
//6 channel audio DAC
#ifdef SPHE8202
#define WM8746I2S24               //(format:I2S24)
#else
#define WM8746                      //(format:RJ24)WM8766 is pin-2-pin compatible
#endif
//#define WM8736                    //for AUDIO DAC WM8736 or DA1196 6 chanell
//#define AV2188
//#define CS4228
//#define CE2746                    //for AUDIO DAC CE2746  6 chanell                 
//2 channel audio DAC
//#define WM8726RJ16
//#define WM8746I2S24
//#define WM8720                    //use GPIO-17 as AUDIO_RST
//#define CS4334DAC
//#define PCM1742
//#define PCM1606
//#define PCM1720
//#define PCM1723

//Audio channel connector(RCA connector)setting, Jeff 20020520
//We assign connectors to the following index, Lm(0), Rm(1), L(2), R(3), Ls(4), Rs(5), C(6), SFE(7)
//2-3-4-5-6-7 map to DAC OUT0L-OUT0R-OUT1L-OUT1R-OUT2L-OUT2R
#define DACOUTLm        0
#define DACOUTRm        1
#define DACOUT0L        2
#define DACOUT0R        3
#define DACOUT1L        4
#define DACOUT1R        5
#define DACOUT2L        6
#define DACOUT2R        7

#define DAC_INVERT      1           //dac polarity 0 (untouch) or 1 (inverted)


//#define SUPPORT_DSPMUTE        // benson add for dsp mute function 2004/07/12
#define CD_INIT_DNOT_MUTE

//#define USE_SBA1_AS_GPIO_MUTE//for 8200-32-sy-0-c GPIO MUTE nono 2004-10-15 18:25
#ifdef USE_SBA1_AS_GPIO_MUTE
#define LOW_MUTE
#endif


//IR setting
//#define IR200                        // for new SUNPLUS remote controller   2004-10-22 15:38, felix
#define IR44                        // for new SUNPLUS remote controller
#define IR_PLAY_RESUME
#define IR_PLAY_RESUME_PAUSE

//#define ADJUSTING_ACTION_VALID_RIGHT_NOW
//#define NEXT_FORWARD_IN_A_KEY
//#define IR5                         //"ircode_N700.h"
//======================================================================
//#define RISC_ALIVE_STANDBY        //power on by RISC on standby lijd  2004-9-28 17:33, 2004/10/01 yltseng
//======================================================================
#define IR_10_PLUS
//#define IR_NO_REPEAT              //disable repeat, when we keep to press one button, Jeff 20020924
//#define USE_VFD_LED_POWER         //use VFD LED to indicate power mode

//VFD setting
#define GENERAL_PANNEL              //for most 16312 VFD pannel.2-7-4 13:41
//#define GENERAL_HT1621_PANNEL              //for most HT1621 VFD pannel.2004-5-9 18:44 lijd
#ifdef GENERAL_HT1621_PANNEL
#define HT1621_PANNEL
#endif//GENERAL_HT1621_PANNEL
//#define AD7312_PANNEL              //2004-5-18 16:19 lijd
//#define CONSER_DVD288_PANNEL
//#define N701_PANNEL               //NINTAUS DVD-N701 PANNEL
//#define SM1623_DRIVER_VFD     //for SM1623 driver vfd      add 2003/10/11
//#define HC164_PANNEL
//#define GT1128_PANNEL         //for GT1128 driver 2004-7-21 11:13 lijd
//#define TP6317_PANNEL		//yaowh add for complete standby 04-10-25
//#define GET_5BYTES_KEY_DATA          //If vfd driver(SM1628) has 5 bytes keydata, define it.//lijd 2005-5-30 13:51 



///OSD language related settings(don't change the sequence)
#define USE_ENGLISH_OSD             //LCD_EN
//#define USE_SCHINESE_OSD            //LCD_ZH
//#define USE_TCHINESE_OSD            //LCD_ZH
#define USE_GERMAN_OSD              //LCD_DE
#define USE_SPANISH_OSD             //LCD_ES
#define USE_FRENCH_OSD              //LCD_FR
#define USE_PORTUGUESE_OSD          //LCD_PT
//#define USE_LATIN_OSD               //LCD_LA
//#define USE_ITALIAN_OSD             //LCD_IT
//#define USE_JAPANESE_OSD            //LCD_JA
//#define USE_RUSSIAN_OSD             //LCD_RU
//#define USE_ROMANIAN_OSD             //LCD_RO
//#define USE_TURKISH_OSD             //LCD_TR
//#define USE_DUTCH_OSD               //LCD_NL
//#define USE_SWEDISH_OSD             //LCD_SV
//#define USE_CZECH_OSD               //LCD_CS
//#define USE_THAI_OSD               //LCD_TH
//#define USE_HUNGARIAN_OSD           //LCD_HU
//#define USE_ARABIC_OSD           //LCD_AR
//#define USE_GREECE_OSD           //LCD_EL

#define DEFAULT_OSD_LANG            0
#define N_OSD_LANGS                 5//8//3
#define OSD_LAGN_SETUP_STRING       LCD_EN,LCD_DE,LCD_ES,LCD_FR,LCD_PT,0,0,0
#define OSD_LANG_SETUP_MAP          {0,     1,     2,     3,     4,      0, 0, 0} //mapping table(OSD_LAGN_SETUP_STRING --> USE_XXX_OSD)

#define OSD_TIMEOUT                 200
#define OSD_SCREEN_SAVER

#define REGION_NUM                  6       //set default region:0->all rigion;1~6->REGION 1~6.

#define SUPER_PASSWORD              {IRC_5,IRC_1,IRC_6,IRC_8}   //define super password when open tray
#define DEFAULT_PASSWORD            0000                        //Jeff 20020703
#define USER_SUPER_PASSWORD         0000                       //NONO 3-6-17 14:31


#define DEFAULT_AUDIO_LANG          2   //2:Chn, 3:Eng, 4:Jap, 5:Frn, 6:Spa, 7:Por, 8:Ger, 9:Lat
#define OSD_AUDIO_LAGN_SETUP_STRING     LCD_ZH,LCD_EN,LCD_JA,LCD_FR,LCD_ES,LCD_PT, LCD_LA, LCD_DE

#define DEFAULT_SUBT_LANG           2   //2:Chn, 3:Eng, 4:Jap, 5:Frn, 6:Spa, 7:Por, 8:Ger, 9:off
#define OSD_SUBT_LAGN_SETUP_STRING     LCD_ZH,LCD_EN,LCD_JA,LCD_FR,LCD_ES,LCD_PT, LCD_DE, STR_OS_OFF

#define DEFAULT_MENU_LANG       2      //2:Chn, 3:Eng, 4:Jap, 5:Frn, 6:Spa, 7:Por, 8:Ger, 9:Lat
#define OSD_MENU_LAGN_SETUP_STRING     LCD_ZH,LCD_EN,LCD_JA,LCD_FR,LCD_ES,LCD_PT, LCD_DE, LCD_LA

#define DEFAULT_TV_SYS              0       //0:NTSC, 1:PAL60, 2:PAL, 3:AUTO
//#define TV_SYS_SETUP_STRING       STR_OS_NTSC, STR_OS_PAL60, STR_OS_PAL, STR_OS_PALM, STR_OS_PALN, STR_OS_PALNc, STR_OS_AUTO, 0
#define TV_SYS_SETUP_STRING         STR_OS_NTSC, STR_OS_PAL60, STR_OS_PAL, STR_OS_AUTO, 0, 0, 0

#ifdef TV_USE_4_DAC
#define MODE_MAX_PSCAN 0x04
#else
#define MODE_MAX_PSCAN 0x03
#endif

#if defined(TV_YUV_OUT)
   #ifdef TV_USE_4_DAC
   #define VIDEO_SETUP_STRING           STR_OS_P_SCAN_YUV,STR_OS_YCbCr,STR_OS_TV_RGB, STR_OS_S_VIDEO, 0,0,0
   #define VIDEO_SET_MODE               P_SCAN,           INTERLACE,   TV_RGB,           TV_SVIDEO
   #else
   #define VIDEO_SETUP_STRING           STR_OS_P_SCAN_YUV,STR_OS_YCbCr,STR_OS_TV_RGB, 0, 0,0,0
   #define VIDEO_SET_MODE               P_SCAN,           INTERLACE,   TV_RGB
   #endif
#elif defined(S_VIDEO_OUT)
   #ifdef TV_USE_4_DAC
   #define VIDEO_SETUP_STRING           STR_OS_YCbCr,STR_OS_TV_RGB,STR_OS_P_SCAN_YUV,STR_OS_S_VIDEO, 0,0,0
   #define VIDEO_SET_MODE               INTERLACE,   TV_RGB,       P_SCAN,           TV_SVIDEO
   #else
   #define VIDEO_SETUP_STRING           STR_OS_YCbCr,STR_OS_TV_RGB,STR_OS_P_SCAN_YUV,0, 0,0,0
   #define VIDEO_SET_MODE               INTERLACE,   TV_RGB,       P_SCAN,
   #endif
#endif

#define SETUP_ALL_VALID             //define it to let SETUP MENU is always valid, Jeff 20021023
//#define SETUP_DONT_PAUSE                // define it to continue play when SETUP, alan 3-8-5 17:48

//#define NEW_SEARCH_OSD              //new search OSD function, using up/down to switch selection

//#define RATING_8                  //if we define it, there are 8 ratings, 1/2/3/../8, otherwise, 3 ratings, Jeff 20020723


//#define TWO_CHANNEL_ONLY          //define it to output two channel audio only, mark it for 5.1 channel, Jeff 20020819


//#define NO_MIC                    //if use it,about MIC item will be gray and can't be selected.

//#define SUPPORT_EXT_AD_SHOW_MIC_AUTO_SING      // #define it to let extern AD achieve AUTO sing
#ifdef  SUPPORT_EXT_AD_SHOW_MIC_AUTO_SING
#define NO_MIC                    //if use it,about MIC item will be gray and can't be selected.
#define NO_MIC_ITEM_ENABLE_MIC
#define NOT_SHOW_MIC_SETUP_DAFAULT_AUTO
#endif

#define NO_DTS_OUTPUT             //define it when we don't support DTS audio output
#ifdef NO_DTS_OUTPUT
//#define FORCE_NO_DTS_OUTPUT         //define it when we don't support DTS audio output, but load DTS dsp_code.
#endif

//idle time to wake up screen saver
#define SAFE_WAIT_TIME              (3* 60 * 100)      //x second

#ifndef SDRAM_16Mb_Mode
#define SUPPORT_FILE_SYSTEM_MODE  //use MP3 menu to play all we support files(e.g. .dat .vob ...)
#define SUPPORT_PLAYBACK_ICON       // display osd playback icons
#endif

#ifdef SDRAM_16Mb_Mode
    #ifdef SUPPORT_FILE_SYSTEM_MODE
        #undef TWO_CHANNEL_ONLY
    #endif
#endif

//#define MP3_DIRECT_SELECT         //select file item all disc, panxing,2002-4-8
//#define MP3_CD_FF1_BF1_MUTE       //FF*2 and BF*2 mute

//li mao add 2004-5-12 10:02
//#define NO_DISPLAY_CDROM_ICON
//#define MP3_BK_GROUND_BLACK;
//#define MP3_BK_GROUND_GREEN;
//#define MP3_BK_GROUND_AQUA;

#define JPEG_EXT2FULL             //extend JPEG to full screen
#define JPGExtMaxMultiple         2               //max. ext multiple=JPGExtMaxMultiple * JPGExtMaxMultiple
#define JPG_EFFECT   //David Add 3-6-26 17:12
#define JPEG_SLIDE_TIME             (3*100)         //JPEG slide show hold time, x second
//#define ADJUST_JPEG_SLIDE_TIME  //lyc 2005/2/17 for adjust jpeg slide time in setup menu
#ifdef ADJUST_JPEG_SLIDE_TIME
#undef JPEG_SLIDE_TIME                  
#endif

#ifndef SDRAM_16Mb_Mode
#define JPEG_THUMBNAIL_MENU         //enable JPEG thumbnail menu
//#define JPEG_PREFETCH               //pre-fetch JPEG file and decode when we select someone file
#endif

//#define AUDIO_SHOW_SAVER                          //MP3 or CDDA play will show screen-saver when idle > 10 seconds, Jeff 20020815
//#define SLEEP_WHEN_POWER_ON                       //system enter sleep mode when power-on, Jeff 20020922

#ifdef SDRAM_16Mb_Mode
//#define SUPPORT_EQ_SDRAM_16Mb
#endif

#ifndef SDRAM_16Mb_Mode //terry,de-mark,2003/8/2 11:49AM
#define SUPPORT_DVD_3D                              //SUPPORT_DVD_3D defined only to enable DOWNMIX SWITCH
#define DVD_3D_SHOW_SPECTRUM                        //SUPPORT_DVD_3D+DVD_3D_SHOW_SPECTRUM : to show spectrum(not include LPCM)
//#define SUPPORT_DVD_3D_EFFECT//for two channel, DVD can use 3Dsound.
//to remember 3D sound,;yanlb add,2004/07/06
//#define REMB_3DSOUND    //Make sure:SUPPORT_3DSOUND defined
#endif


#define SUPPORT_WMA           //nono mark 2004-10-16 16:20

//#define SUPPORT_JOLIET_FORMAT
//#define SUPPORT_FS_LONGNAME

#define SPDIF_REAL_OFF                              //close SPDIF clock when not in SPDIF mode, Jeff 20020920

#define AC3_BASS_MANAGEMENT                         //AC3 Bass Management

//#define SPDIF_PLUS_ANALOG                           //define it when we output SPDIF/PCM+Analog simultaneous, Jeff 20021029
//#define USE_FREQ_MASK								//20041222 nono mark it, because most customers don't neet it.

#define MIC_THRESHOLD               0x30            //default:0x30, (0x20 ~ 0xa0)
#define MIC_PRESENSITIVITY          0x1a            //MIC turn-on sense time(unit: 32/44100 sec, only for (S)VCD/MP3)
#define MIC_AFTERSENSITIVITY        0x0903          //MIC turn-off sense time(units:1/3 seconds, Hi-auto, Lo-MIC(unused))
#define ECHO_DECAY_INIT             0x05            //ECHO decay model(1~8), hi:intensity

#define SUPPORT_VIDEO_BUFFER_STANDBY //kenny 2003/5/13

#ifdef SUPPORT_VIDEO_BUFFER_STANDBY

#define STANDBY_GPIO 52
#endif

//#define SUPPORT_UART_COMMAND      //Support UART to communicate with external MCU //KENNY 2002/7/16

//#define VFD_PIN_TO_DAC

//seek error skip
//#define CSWDP_0                       //cServoWrongDataPass = 0;playing DVD.
//#define ERROR_CONCEALMENT

#ifdef ERROR_CONCEALMENT
#define ERROR_MB_LIMIT_NUM          4//n=0:0~15 macroblock; n=1:16~31 macroblock...default=4
#define ERROR_CONCEALMENT_MODE          0x03//n=0 disable error concealment
                            //n=1 detect error and switch to good picture
                            //n=3 detect error and switch to good picture, jump to next I
#endif

//#undef SEEK_SKIP_TIME
//#define SEEK_SKIP_TIME                    1//NORMAL=1

//Maoyong 2004.04.21, in SETUP Menu, Speaker delay display in distance. 1ms<->30cm
//#define SHOW_SPK_DELAY_BY_DISTANCE

//Servo related
// Servo Denotation : PUH_MECHA_Customer

    #ifdef SPHE8202
        //#define HI0FS0_STD          // Hitach-HOP1200_FUSS_Standard
        #define SA0SA0_STD        // SanyoHD60_Sanyo_Standard
        //#define SA2SA0_STD        // SanyoHD62_Sanyo_Standard
        //#define SA3SA0_STD        // SanyoHD62(V)_Sanyo_Standard
        //#define SM0SM0_STD        // SAMSUNG_SAMSUNG_Standard
        //#define SO1SO1_STD        // Sony310_Sony_Standard
        //#define PH1YX0_STD		// Philips_Yuxing_Standard
    #else
        //#define AA0AA0_STD        // AATEK_AATEK_Standard
        //#define AR0AT0_STD        // Arima_Actima_Standard
        //#define HI0CO0_STD        // Hitach-HOP1200_Conser_Standard
        //#define HI0FS0_STD        // Hitach-HOP1200_FUSS_Standard
        //#define HI0GB0_STD        // Hitach-HOP1200_GBM_Standard
		//#define HI1KZ0_STD        // Hitach-HOP1200W_KZG_Standard
        #define SA0SA0_STD        // SanyoHD60_Sanyo_Standard
        //#define SA0SA0_BBK0       // SanyoHD60_Sanyo_BBK solution
        //#define SA2SA0_STD       	// SanyoHD62_Sanyo_Standard
        //#define SA2HY0_STD       	// SanyoHD62_Hanyan_Standard
       	//#define SK0SW0_STD		// SANKYO_SHINWA_Standard
        //#define SM0SM0_STD        // SAMSUNG_SAMSUNG_Standard
        //#define SO0SO0_STD        // Sony280_Sony_Standard
		//#define SO1SO1_STD        // Sony310_Sony_Standard
		//#define PI0GI0_STD        // Pioneer_Gigastorage_Standard
		//#define PH1YX0_STD		// Philips_Yuxing_Standard
		//#define PH1CH1_STD		// Philips_ChunHai_Standard
		//#define KE0KE0_STD        // Kenwood_Kenwood_Standard
		#define PREAMP_GPIO_ENABLE
    #endif

#define HW_DMA
#define SOFT_ATAPI
#define TRAY_AVAILABLE      // system with tray
#define DISC_TYPE_RETRY
#define POWER_ON_SERVO_STARTUP
//#define POWER_ON_TOPDOOR_PRESTOP
//#define SERVO_RANDOM_SEEK
//#define SERVO_TEST
//#define SERVO_UART
//#define SERVO_DBG
//SERVO Eject  Speed
#define TRAY_SPEED  0   //  0:fastest   4:slowest :3 for ASA loader, 2 for ¨Î±mloader,3 for GBM ,0 for full time Eject

// The below define just for SANYO OPU //*** modify by CANER ***//
#if (defined(SA0GB2_STD))

    //SERVO Eject  Speed for SA0GB2
    #define TRAY_SPEED1         10  //0~12,define it to change speed (in 480ms)
    #define TRAY_SPEED2         5   //0~12,definr it to change speed (480ms~  )

#elif (defined(SA0GB5_SLT))

    //SERVO Eject  Speed for SA0GB5
    #define TRAY_IN_SPEED1      0   //0~12,define it to change speed (in 480ms)
    #define TRAY_IN_SPEED2      0   //0~12,definr it to change speed (480ms~  )
    #define TRAY_OUT_SPEED1     0   //0~12,define it to change speed (in 480ms)
    #define TRAY_OUT_SPEED2     0   //0~12,definr it to change speed (480ms~  )

#elif (defined(SA0AT0_STD) || defined(SA0SA0_STD) || defined(SA0SA0_SLM) || defined(SA0SA0_SLM) || defined(SA0SA0_KXD0)|| defined(SA0SA0_GBM0) )

    //SERVO Eject  Speed for SANYO OPU for other mechas
    #define TRAY_IN_SPEED1      0   //0~5
    #define TRAY_OUT_SPEED1     0   //0~5

#endif

//#define TOP_DOOR_LOADER                   //define it to use TOP door loader
//#define DOOR_SENSE_GPIO           3       //define door sense gpio, 0:close/1:open

/*
* VPP Pixel Aspect Ratio (PAR)
*/
//#define PAR_MP_FORCE_SQUARE					// force to use square source PAR for MPEG-1/2
//#define PAR_MP4_FORCE_SQUARE				// force to use square source PAR for MPEG-4
#define PAR_MP4_GUESS_43TV					// guess to use source PAR of 4:3 TV for MPEG-4, according to video size
//#define PAR_MP4_REVERSE_169TV				// reverse operation of tranforming 4:3 TV to 16:9 TV, for MPEG-4

// Determination of MPEG-2 Progressive 
//#define FRCTL_MP2_ALWAYS_INTERLACED  	// always treat MPEG-2 as interlaced in frame rate control
                                        // even if the progresiive flags are set.

//#define VCD_BACKWARD_TIME //show backward time on VFD when menu is off,wangfeng 2003-12-15 15:08
#ifdef SPHE8202

//=================================================================
//for DVD setup menu reengineering	//added by JS	//20040728
#define DVD_SETUP_REENG
//=================================================================

    //---------------------------------------------------------------------
    // Bass Management  ycwen 2005/5/17
    //----------------------------------------------------------------------    
    #ifdef AC3_BASS_MANAGEMENT
        #ifdef DVD_SETUP_REENG
            //#define SPEAKER_CONFIG   //ycwen 2005/5/17 define for full set Bass Management            
            #ifdef SPEAKER_CONFIG
                #define USE_SETUP_ITEM_ENABLE_FLAG //added by by chenzhao on 2005-3-31 16:4  
                #define HIDE_DISNABLE_ITEM //added by by chenzhao on 2005-3-31 16:4  
            #endif    
        #endif    
    #endif     
    
    //---------------------------------------------------------------------
    // PROLOGIC_II    ycwen 2005/5/17
    //----------------------------------------------------------------------                    
    //#define SUPPORT_PROLOGIC_II
    #ifdef SUPPORT_PROLOGIC_II
        #ifdef DVD_SETUP_REENG
            //#define SUPPORT_PROLOGIC_II_ADVANCE_SETTING
            #ifdef SUPPORT_PROLOGIC_II_ADVANCE_SETTING
                #define USE_SETUP_ITEM_ENABLE_FLAG 
                #define HIDE_DISNABLE_ITEM
            #endif
        #endif       
    #endif    
    
    #ifndef SDRAM_16Mb_Mode
    //#define SUPPORT_USB
    #endif

    #ifndef SDRAM_16Mb_Mode
    #define SUPPORT_MP4
    #endif

    #ifdef  SUPPORT_MP4

    	//#define MP4_SPEED_UP_SRV    //for big bitrate mp4 in CD-ROM,need new servo

        #define SUPPORT_MP4_SUBTITLE

        #ifdef SUPPORT_MP4_SUBTITLE
            //#define SUBTITLE_SUPPORT_ALL_FORMAT
            #define SUBTITLE_SUPPORT_COMMON_FORMAT

            #define SUPPORT_FONT_UTIL
            #ifdef SUPPORT_FONT_UTIL
                //#define SUPPORT_MULTI_FONT_SWITCH   
                #define SUPPORT_FONT_ISO_8859_1    // reference to h/LanguageUtil.h for more languages
            #endif // SUPPORT_FONT_UTIL
        #endif

/*nono move to cust_def.h
		#define AVI_INTERNAL_SUP	// To support internal subtitle of AVI (subpicture format)
*/

        //#define SUPPORT_MJPEG     // Motion JPEG limitation: 320x240, 15fps, 2Mbps(2048k-bits per second)
        #define DIVX_DRM  // DivX DRM 2.0 (not compatible with DRM 1.0)
        #ifdef  DIVX_DRM
            //#define DIVX_DRM_AES_ONLY
            #define SHOW_DRM_REGISTRATION_CODE_IN_SETUP
            // 12-bits Model ID for DivX DRM (mask 0xF0FF)
            // This model number is assigned to each product by DivXNetworks.
            #define DIVX_DRM_MODEL_ID (0x3031 & 0xF0FF)	// Value 0x3031 is a TEST value only.
            											// 0x30 is the top/high byte, and 0x31 is the bottom/low byte.
        #endif
    #endif

    #define SETUP_COLOR_TYPE2
    #define NEW_MP3_GUI
    #undef IR_SHUFFLE_ON
    #undef KARAOKE_USE_IR_CRT
    #undef DOWNMIX_USE_IR_CRT
    #undef SUPPORT_SCORE
    #undef SETUP_DEFAULT_USE_IR_CRT
    //#define DVD_PREVIEW_FUNCTION

/*nono move to cust_def.h
    #define USE_108MHZ
*/

    //#define  SPHE8202_CARD_STORAGE  //wthsin,    2004/2/23 10:49am
    #ifdef SPHE8202_CARD_STORAGE      //wthsin,    2004/3/1  11:08am
        //#define CARD_SETUP_TYPE_1   //Three card Bus Demo
        //#define CARD_SETUP_TYPE_2     //Share One card Bus(EASTECH)
        #define CARD_SETUP_TYPE_3   //256Pin 16bit Non_share mode All card.
        //#define CARD_SETUP_TYPE_4   //256Pin 32bit Non_share mode 3-in-1 card

	#ifdef CARD_SETUP_TYPE_3
		//#define IR_SWITCH_CD_USB_CF_OTHER    //dingzhy for bus switch
		//#define SWITCH_GPIO 23	//use gpio cortrol switch
		//#define HIGH_CORTROL_CF	//mark it will use low cortrol cf
		//#undef SUPPORT_VFD	//only for test
	#endif

    #endif
    
    #if defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
    #ifndef DVD_SETUP_REENG//because some bugs need to be fixed.nono 20050204
    #define SELECT_MEDIA_IN_SETUPMENU   //dingzhy for default 
    #endif
    /***************************** Switch media block *****************************/
    //dingzhy for default, switch media in SETUP MENU.
    //#define SELECT_MEDIA_IN_SETUPMENU  
    
    //This definition for switching media with hardware support(bus switch).
    //#define IR_SWITCH_CD_USB_CF_OTHER  
    
    //This definition for switching between CARD and DISC.
    //#define IR_SWITCH_CARD_CD          
    
    //This definition for switching among CARD ,USB and DISC.
    //#define IR_SWITCH_CARD_CD_ADD_USB  
    #ifdef IR_SWITCH_CARD_CD_ADD_USB
    #define IR_SWITCH_CARD_CD
    #endif
    
    //This definition for switching between USB cardreader and DISC.
    //#define SWITCH_BETWEEN_USB_CARDS   
    #ifdef SWITCH_BETWEEN_USB_CARDS
    #define IR_SWITCH_CARD_CD
    #endif
    /***************************** Switch media block *****************************/
    #endif
    
    //#define SUPPORT_FILE_DISPLAY_TM //liweihua move to here  2004-3-23 15:57
                                    //for MPG file time display

    //Maoyong 2004.04.13 for program play of others file type except jpg/mp3/wma in CDROM disc
    #ifdef  SUPPORT_FILE_SYSTEM_MODE
    #define SUPPORT_FS_OTHER_PROG                   //Maoyong 2004.04.14
    #endif

    #ifdef SUPPORT_MP4
    #define MP4_DISC_DIRECT_PLAY             //Maoyong 2004.04.14
    //#define DISPLAY_MP4_AV_INFO            //Maoyong 2004.06.30
    //#define MP4_DISC_NOT_AUTO_PLAY
    #ifdef MP4_DISC_NOT_AUTO_PLAY	//yaowh add 04-10-25
    //#define MP4_START_DIRECT_PLAY_TO_GUI  //linrc 2005-8-2 11:20 for start Direct first play goto GUI
    #define FS_OTHER_DIRECT_PLAY
    #define MP4_DISC_DIRECT_PLAY
    #endif
    #endif

    #define PLAY_JPE_JPEG_FILE      //liweihua 2004-5-12 ,for "*.jpeg" file

   //Board define, please select what board you used ,kenny 2004/3/4
    #define MP_BOARD_256_PIN_NON_SHARE     //mass-production board 256 pin NON SHARE MODE
    

//define GPIO MUTE pin //kenny 2004/7/14
//#define USE_A19_AS_GPIO_MUTE
#ifdef MP_BOARD_256_PIN_NON_SHARE
#define USE_AUD4_AS_GPIO_MUTE
#ifdef USE_AUD4_AS_GPIO_MUTE
#define LOW_MUTE
#endif
#endif

#ifdef MP_BOARD_216_PIN_NON_SHARE //kenny define for 216 pin non-share board
#undef SDRAM_BUS_32BITS
#define NO_MIC                    //216 pin non-share doesn't support MIC function, Ronnie 2004/7/22
#define USE_AUD3_AS_GPIO_MUTE
#ifdef USE_AUD3_AS_GPIO_MUTE
#define LOW_MUTE
#define MUTE_PULL_HIGH				// 216 pin demo board use another mute circuit, ronnie 2004/09/09
#endif

#ifdef SPHE8202_CARD_STORAGE
#define USE_SERVO_DFCT_GPIO //Because pin55 DFCT is used by card reader, so if you need to debug servo
                           //mark this definition
#endif

#endif
#endif
#define ICON_REPEAT_FOLDER       // zhuyf add for mp3  2004-8-10


//#define START_NO_VPP_DELAY


//=================================================================
//for DVD setup menu reengineering	//added by JS	//20040728
//#define DVD_SETUP_REENG
//=================================================================

//#define SUPPORT_MIX_MP3_CDDA  //linrc add 2004-12-15 16:17
#ifdef SUPPORT_MIX_MP3_CDDA     //in new code I change "SUPPORT_MIX_MP3_CDDA" to "SUPPORT_MIX_DATA_CDDA_DISC"
#define SUPPORT_MIX_DATA_CDDA_DISC  //so in new code(after 12/15),you needn't define SUPPORT_MIX_MP3_CDDA
#endif

//#define MP3_JPEG_COWORK 
#ifdef SDRAM_16Mb_Mode //We can't support in 16MB
    #undef MP3_JPEG_COWORK
#endif    
#ifdef MP3_JPEG_COWORK  //must define SDRAM SIZE for mp3 buffer allocation

        #define SDRAM_32Mb_Mode

#endif   
// For DISC_ID_IN_FLASH to work, SAME_DISC_RESUME must also turn on
// Use 64KB of flash to store DISC RESUME information and SETUP Information
//#define SAME_DISC_RESUME
//#define DISC_ID_IN_FLASH
//----------------------- bottom ---------------

