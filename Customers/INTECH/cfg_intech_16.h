#define VERSION_STRING      "C16-001"   //version: xxx-yyy, 20030422

//---------------------
//board parts settings
//---------------------
#define SDRAM_16Mb_Mode       // only use 16Mb*1 SDRAM
//#define SDRAM_32Mb_Mode         // with 4MB memory
//#define SDRAM_64Mb_Mode       // with 8MB memory


//SDRAM settings(bus width, default is 16-bits mode)
#ifndef SDRAM_16Mb_Mode
#define SDRAM_BUS_32BITS        // define it to use 32 bits SDRAM Bus width
#endif

/*
* Define Disc detect polling time
*/
#define DETECT_TIMES	0xff
#define NO_DISC_TIMES	30

/*
*  Video seting
*/
/*#define PC_VGA_OUT*/
/*#define TV_YUV_OUT*/
#define S_VIDEO_OUT


/*
* ROM setting
*/
/*#define ROM_SDRAM_SHARE_BUS*/
/*#define ROM_ATA_SHARE_BUS*/



//CD-G related
#define SUPPORT_CDG                 //define it to support CD-G

//#define TVOUT6_4DAC_ON
#ifdef TVOUT6_4DAC_ON
#define TV_USE_4_DAC
#endif

//#define TV_USE_4_DAC
//#define SCART_TV                  //define it if we support SCART TV, use GPIO-37-38-39 to control
//#define ORI_SCART_TV
//#define SCART_TV_2				//define pin151---SCART_DISPLAY; pin163---SCART_SIG  wanghaoying

//Upgrade setting
#define UPGRADE_FILE_NAME	{"DVDROM.BIN"}



#ifndef SDRAM_16Mb_Mode
//#define SUPPORT_NESGAME
//#define DVD_AUDIO
#endif


//audio DAC settings, chose one
//6 channel audio DAC
//#define WM8746                      //(format:RJ24)WM8766 is pin-2-pin compatible
#define WM8746I2S24               //(format:I2S24)
//#define WM8736                    //for AUDIO DAC WM8736 or DA1196 6 chanell
//#define AV2188
//#define CS4228
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
#define DACOUTLm        6//0
#define DACOUTRm        7//1
#define DACOUT0L        0//2
#define DACOUT0R        1//3
#define DACOUT1L        2//4
#define DACOUT1R        3//5
#define DACOUT2L        4//6
#define DACOUT2R        5//7

#define DAC_INVERT      1           //dac polarity 0 (untouch) or 1 (inverted)

//#define USE_A19_AS_GPIO_MUTE
#define TEMP_TWO_CHANNEL          //define it to output two channel audio only, mark it for 5.1 channel, Jeff 20020819
#define ONLY_DOWNMIX
#define HJ_APEX_NO_KEY
#define NO_MIC                    //if use it,about MIC item will be gray and can't be selected.
#define NO_DTS_OUTPUT             //define it when we don't support DTS audio output

#define MOVE_MP3_DSP_CODEC_ADDR    

//IR setting
#define IR15                        // for new SUNPLUS remote controller
#define IR_PLAY_RESUME
#define IR_PLAY_RESUME_PAUSE

//#define ADJUSTING_ACTION_VALID_RIGHT_NOW
//#define NEXT_FORWARD_IN_A_KEY
//#define IR5                         //"ircode_N700.h"
#undef SF_SR_IN_A_KEY
#undef IR_SHUFFLE_ON
#undef KARAOKE_USE_IR_CRT
#undef DOWNMIX_USE_IR_CRT
#undef SUPPORT_SCORE
#undef SETUP_DEFAULT_USE_IR_CRT


#define IR_10_PLUS
//#define IR_NO_REPEAT              //disable repeat, when we keep to press one button, Jeff 20020924
//#define USE_VFD_LED_POWER         //use VFD LED to indicate power mode

//VFD setting
#define GENERAL_PANNEL              //for most VFD pannel.2-7-4 13:41
//#define INTECH_PANEL             
//#define INTECH_PANEL_5600_KEY		//#else is INTECH_PANEL_5500_KEY



#ifdef SDRAM_16Mb_Mode	// alan, 2003/10/14 01:21§U§»
//OSD language related settings(don't change the sequence)
#define USE_ENGLISH_OSD             //LCD_EN
#define USE_GERMAN_OSD              //LCD_DE
#define USE_SPANISH_OSD             //LCD_ES

#define N_OSD_LANGS                 3

#define DEFAULT_OSD_LANG            0
#define OSD_LAGN_SETUP_STRING     LCD_EN,LCD_DE,LCD_ES,0,0,0,0,0
#define OSD_LANG_SETUP_MAP          {0,		 1,     2,   0, 0,0,0,0} //mapping table(OSD_LAGN_SETUP_STRING --> USE_XXX_OSD)

#else


///OSD language related settings(don't change the sequence)
#define USE_ENGLISH_OSD             //LCD_EN
#define USE_SCHINESE_OSD            //LCD_ZH
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


#define DEFAULT_OSD_LANG            0

#define N_OSD_LANGS                 6//8//3
#define OSD_LAGN_SETUP_STRING       LCD_EN,LCD_ZH,LCD_DE,LCD_ES,LCD_FR,LCD_PT,0,0
#define OSD_LANG_SETUP_MAP          {0,		1,     2,     3,     4,      5, 0, 0} //mapping table(OSD_LAGN_SETUP_STRING --> USE_XXX_OSD)
#endif//#ifdef SDRAM_16Mb_Mode	

#define OSD_TIMEOUT                 200
#define OSD_SCREEN_SAVER

#define REGION_NUM                  6       //set default region:0->all rigion;1~6->REGION 1~6.

#define SUPER_PASSWORD              {IRC_9,IRC_7,IRC_3,IRC_5}   //define super password when open tray
#define DEFAULT_PASSWORD            0000                        //Jeff 20020703
#define USER_SUPER_PASSWORD         0000                       //NONO 3-6-17 14:31


#define DEFAULT_AUDIO_LANG          2   //2:Chn, 3:Eng, 4:Jap, 5:Frn, 6:Spa, 7:Por, 8:Ger, 9:Lat
#define OSD_AUDIO_LAGN_SETUP_STRING     LCD_ZH,LCD_EN,LCD_JA,LCD_FR,LCD_ES,LCD_PT, LCD_LA, LCD_DE

#define DEFAULT_SUBT_LANG           2   //2:Chn, 3:Eng, 4:Jap, 5:Frn, 6:Spa, 7:Por, 8:Ger, 9:off
#define OSD_SUBT_LAGN_SETUP_STRING     LCD_ZH,LCD_EN,LCD_JA,LCD_FR,LCD_ES,LCD_PT, LCD_DE, STR_OS_OFF

#define DEFAULT_MENU_LANG       2      //2:Chn, 3:Eng, 4:Jap, 5:Frn, 6:Spa, 7:Por, 8:Ger, 9:Lat
#define OSD_MENU_LAGN_SETUP_STRING     LCD_ZH,LCD_EN,LCD_JA,LCD_FR,LCD_ES,LCD_PT, LCD_DE, LCD_LA

#define DEFAULT_TV_SYS              0       //0:NTSC, 1:PAL60, 2:PAL, 3:AUTO
#define TV_SYS_SETUP_STRING     	STR_OS_NTSC, STR_OS_PAL60, STR_OS_PAL, STR_OS_AUTO, 0, 0, 0,0

#ifdef TV_USE_4_DAC
#define MODE_MAX_PSCAN 0x05
#else
#define MODE_MAX_PSCAN 0x04
#endif

#ifdef PC_VGA_OUT
   #ifdef TV_USE_4_DAC
   #define VIDEO_SETUP_STRING     		STR_OS_PC_VGA,STR_OS_P_SCAN_YUV,STR_OS_YCbCr,STR_OS_TV_RGB, STR_OS_S_VIDEO, 0,0
   #define VIDEO_SET_MODE				PC_VGA,       P_SCAN,           INTERLACE,	 TV_RGB,	       TV_SVIDEO
   #else
   #define VIDEO_SETUP_STRING     		STR_OS_PC_VGA,STR_OS_P_SCAN_YUV,STR_OS_YCbCr,STR_OS_TV_RGB, 0, 0,0
   #define VIDEO_SET_MODE				PC_VGA,       P_SCAN,           INTERLACE,	 TV_RGB
   #endif
#elif defined(TV_YUV_OUT)
   #ifdef TV_USE_4_DAC
   #define VIDEO_SETUP_STRING     		STR_OS_P_SCAN_YUV,STR_OS_PC_VGA,STR_OS_YCbCr,STR_OS_TV_RGB, STR_OS_S_VIDEO, 0,0
   #define VIDEO_SET_MODE				P_SCAN,           PC_VGA,       INTERLACE,	 TV_RGB,	       TV_SVIDEO
   #else
   #define VIDEO_SETUP_STRING     		STR_OS_P_SCAN_YUV,STR_OS_PC_VGA,STR_OS_YCbCr,STR_OS_TV_RGB, 0, 0,0
   #define VIDEO_SET_MODE				P_SCAN,           PC_VGA,       INTERLACE,	 TV_RGB
   #endif
#elif defined(S_VIDEO_OUT)
   #ifdef TV_USE_4_DAC
   #define VIDEO_SETUP_STRING     		STR_OS_YCbCr,STR_OS_TV_RGB,STR_OS_P_SCAN_YUV,STR_OS_PC_VGA, STR_OS_S_VIDEO, 0,0
   #define VIDEO_SET_MODE				INTERLACE,	 TV_RGB,	   P_SCAN,           PC_VGA,        TV_SVIDEO
   #else
   #define VIDEO_SETUP_STRING     		STR_OS_YCbCr,STR_OS_TV_RGB,STR_OS_P_SCAN_YUV,STR_OS_PC_VGA, 0, 0,0
   #define VIDEO_SET_MODE				INTERLACE,	 TV_RGB,	   P_SCAN,           PC_VGA
   #endif
#endif

#define SETUP_ALL_VALID             //define it to let SETUP MENU is always valid, Jeff 20021023
//#define SETUP_DONT_PAUSE                // define it to continue play when SETUP, alan 3-8-5 17:48

//#define NEW_SEARCH_OSD              //new search OSD function, using up/down to switch selection

#define RATING_8                  //if we define it, there are 8 ratings, 1/2/3/../8, otherwise, 3 ratings, Jeff 20020723


//idle time to wake up screen saver
#define SAFE_WAIT_TIME              (3* 60 * 100)      //x second

#ifndef SDRAM_16Mb_Mode
#define SUPPORT_FILE_SYSTEM_MODE  //use MP3 menu to play all we support files(e.g. .dat .vob ...)
#define SUPPORT_PLAYBACK_ICON       // display osd playback icons
#endif
//#define MP3_DIRECT_SELECT         //select file item all disc, panxing,2002-4-8
//#define MP3_CD_FF1_BF1_MUTE       //FF*2 and BF*2 mute

#define JPEG_EXT2FULL             //extend JPEG to full screen
#define JPGExtMaxMultiple         2               //max. ext multiple=JPGExtMaxMultiple * JPGExtMaxMultiple
#define JPEG_SLIDE_TIME             (3*100)         //JPEG slide show hold time, x second
#ifndef SDRAM_16Mb_Mode
#define JPEG_THUMBNAIL_MENU         //enable JPEG thumbnail menu
//#define JPEG_PREFETCH               //pre-fetch JPEG file and decode when we select someone file
#endif

//#define POWER_RESUME
//#define SAME_DISC_RESUME
#ifdef SAME_DISC_RESUME
#define POWER_RESUME
#endif
//#define AUDIO_SHOW_SAVER                          //MP3 or CDDA play will show screen-saver when idle > 10 seconds, Jeff 20020815
//#define SLEEP_WHEN_POWER_ON                       //system enter sleep mode when power-on, Jeff 20020922

#ifndef SDRAM_16Mb_Mode //terry,de-mark,2003/8/2 11:49AM
#define SUPPORT_DVD_3D                              //SUPPORT_DVD_3D defined only to enable DOWNMIX SWITCH
#define DVD_3D_SHOW_SPECTRUM                        //SUPPORT_DVD_3D+DVD_3D_SHOW_SPECTRUM : to show spectrum(not include LPCM)
//#define SUPPORT_DVD_3D_EFFECT//for two channel, DVD can use 3Dsound.
#endif


//#define SUPPORT_WMA

#define SPDIF_REAL_OFF                              //close SPDIF clock when not in SPDIF mode, Jeff 20020920

#define AC3_BASS_MANAGEMENT                         //AC3 Bass Management

//#define SPDIF_PLUS_ANALOG                           //define it when we output SPDIF/PCM+Analog simultaneous, Jeff 20021029
//#define USE_FREQ_MASK

#define MIC_THRESHOLD               0x30            //default:0x30, (0x20 ~ 0xa0)
#define MIC_PRESENSITIVITY          0x1a            //MIC turn-on sense time(unit: 32/44100 sec, only for (S)VCD/MP3)
#define MIC_AFTERSENSITIVITY        0x0903          //MIC turn-off sense time(units:1/3 seconds, Hi-auto, Lo-MIC(unused))
#define ECHO_DECAY_INIT             0x05            //ECHO decay model(1~8), hi:intensity

#define RESET_AFTER_UPGRADE         //reset 8200 and tray out after smart upgrade
#define SUPPORT_VIDEO_BUFFER_STANDBY //kenny 2003/5/13
//#define SUPPORT_EXTERNAL_MIC //kenny 2003/5/14

#ifdef SUPPORT_VIDEO_BUFFER_STANDBY

#define STANDBY_GPIO 52
#endif

#ifdef SUPPORT_EXTERNAL_MIC

#define EXTERN_MIC_DECT     57
#define EXTERN_MIC_MUTE     18

#endif

//#define SUPPORT_UART_UPGRADE      //Upgrade flash via UART, Robert 020603
//#define SUPPORT_UART_COMMAND      //Support UART to communicate with external MCU //KENNY 2002/7/16


//#define RCD_GPIO_CONTROL          //alan 2002/11/14 05:06§U§», use GPIO to control RCD, must run nav.bat
//#define CUS_RCD 1                 //customer region code
//#define GPIO_N  6                 //use GPIO 6

//#define VFD_PIN_TO_DAC


//seek error skip
//#define CSWDP_0						//cServoWrongDataPass = 0;playing DVD.
//#define ERROR_CONCEALMENT

#ifdef ERROR_CONCEALMENT
#define ERROR_MB_LIMIT_NUM				4//n=0:0~15 macroblock; n=1:16~31 macroblock...default=4
#define ERROR_CONCEALMENT_MODE			0x03//n=0 disable error concealment
												//n=1 detect error and switch to good picture
												//n=3 detect error and switch to good picture, jump to next I
#endif

//#undef SEEK_SKIP_TIME
//#define SEEK_SKIP_TIME					1//NORMAL=1				



//Servo related
// Servo Denotation : PUH_MECHA_Customer
//#define SO0SO0_STD        // Sony_Sony_Standard
//#define SA0SA0_STD        // Sanyo_Sanyo_Standard
#define SO1SO1_STD        // Sony_Sony_Standard
//#define HI0FS0_STD        // Hitach-HOP1200_FUSS_Standard
//#define MI0CS0_STD        // 
//#define AA0AA0_STD

#define HW_DMA
#define SOFT_ATAPI
#define PREAMP_GPIO_ENABLE
#define TRAY_AVAILABLE	    // system with tray
#define DISC_TYPE_RETRY
#define POWER_ON_SERVO_STARTUP
//#define SERVO_RANDOM_SEEK
//#define SERVO_TEST
//#define SERVO_UART
//#define SERVO_DBG

//SERVO Eject  Speed
#define TRAY_SPEED	0	//  0:fastest	4:slowest :3 for ASA loader, 2 for ®Œ±mloader,3 for GBM ,0 for full time Eject

//#define VCD_BACKWARD_TIME	//show backward time on VFD when menu is off,wangfeng 2003-12-15 15:08
#define NEW_MP3_GUI
#define JPG_EFFECT   //David Add 3-6-26 17:12
#ifdef JPG_EFFECT
//#define JPG_EFFECT_ONLY_ROTATE	//wanghaoying 2003-09-03 13:54, if define this only up/down/right/left has effect no program key
#define USE_PREVIEW_KEY_TO_CALL_JPGEFFECT_HELP
#define CALL_JPGEFFECT_HELP
#endif
//#define	SETUP_COLOR_TYPE1   //wangfeng 2003-08-30 10:39
#define	SETUP_COLOR_TYPE2		//3-9-1 4:24’≈”ÓP

#define DVD_MEMU_RSM
//#define STOP_LOADER
//----------------------- bottom ---------------



