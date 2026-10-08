#define VERSION_STRING      "GD16-000"   //version: xxx-yyy, 2005/3/12 04:16下午

// ================== IC  ================== IC  ================== IC  ================== IC  ================== IC  ================== IC  ================== IC 
/*
* Define IC type
*/
#define IC_8202D

/*
* IC capability or special function definition
*/
#define HW_SUPPORT_GMC
#define HW_SUPPORT_QPEL

//================== Board Begin ==================== Board Begin  ================ Board Begin  =================== Board Begin  =========== Board Begin  =====
//---------------------
//board parts settings
//---------------------
//SDRAM settings(bus width, default is 16-bits mode)
//#define SUNPLUS_8202P_DEMOBOARD
//#define SDRAM_BUS_32BITS    //define it to use 32 bits SDRAM Bus width
#define SDRAM_16Mb_Mode       //only use 16Mb*1 SDRAM

//Board define, please select what board you used ,kenny 2004/3/4
/*emulation board*/
//#define EMU_BOARD_216_PIN              //emulation Board 216 pin 
//#define EMU_BOARD_256_SHARE          //emulation Board 256 pin sdram/rom share mode 
//#define EMU_BOARD_256_NON_SHARE      //emulation Board 256 pin sdram/rom non-share mode 
/*mass production board*/
//#define MP_BOARD_216_PIN               //mass-production board 216 pin
//#define MP_BOARD_256_PIN_SHARE         //mass-production board 256 pin SHARE MODE
//#define MP_BOARD_256_PIN_NON_SHARE     //mass-production board 256 pin NON SHARE MODE
#define MP_BOARD_216_PIN_NON_SHARE      //mass-production board 216 pin non share


/*
*  Modual test
*/
//#define SunplusMoudleTest    


/*
* ROM setting
*/
/*#define ROM_SDRAM_SHARE_BUS*/
/*#define ROM_ATA_SHARE_BUS*/
#define ROM_TACC_DEFAULT    75  //terry,2005/3/21 10:22下午




/*
* USB setting
*/
//#define SUPPORT_USB  //wthsin, 2005/2/24 08:24pm

/*
* Card setting
*/
//C/F Card setting
//#define SUPPORT_CARD_STORAGE      //Jeff 20020725
//#define CARD_MASTER                 //if you don't connect DVD-ROM, define SUPPORT_CARD_STORAGE+CARD_ONLY
//#define CARD_HOT_PLUG             //2002/11/8 kenny define for new reset(GPIO-17) scheme for card detect(GPIO-18)
//#define  SPHE8202_CARD_STORAGE  //wthsin,    2004/2/23 10:49am
#ifdef IC_8202D
    #if defined(CCIR656_TYPE3)|| defined(S_RGB_TYPE1)//kenny 2005/1/16
    #undef SPHE8202_CARD_STORAGE
    #endif
#endif 
    
#ifdef SPHE8202_CARD_STORAGE      //wthsin,    2004/3/1  11:08am
   //#define CARD_SETUP_TYPE_1   //Three card Bus Demo
   //#define CARD_SETUP_TYPE_2     //Share One card Bus(EASTECH)
   // #define CARD_SETUP_TYPE_3   //256Pin 16bit Non_share mode All card.
   #define CARD_SETUP_TYPE_4   //256Pin 32bit Non_share mode 3-in-1 card
   #define USE_SERVO_DFCT_GPIO //Because pin55 DFCT is used by card reader, so if you need to debug servo
                               //mark this definition   
#endif

/*
*  Mute pin Mute pin Mute pin Mute pin Mute pin Mute pin Mute pin
*/
//define GPIO MUTE pin //kenny 2004/7/14
#ifdef MP_BOARD_256_PIN_NON_SHARE
#define USE_AUD4_AS_GPIO_MUTE
#endif
#ifdef MP_BOARD_216_PIN_NON_SHARE //kenny define for 216 pin non-share board
#define USE_AUD3_AS_GPIO_MUTE
#endif

//#define USE_A19_AS_GPIO_MUTE
//#define USE_SBA1_AS_GPIO_MUTE//for 8200-32-sy-0-c GPIO MUTE nono 2004-10-15 18:25
#ifdef USE_SBA1_AS_GPIO_MUTE
#define LOW_MUTE
#endif     

#ifdef USE_AUD3_AS_GPIO_MUTE
#define LOW_MUTE
#define MUTE_PULL_HIGH              // 216 pin demo board use another mute circuit, ronnie 2004/09/09
#endif     

#ifdef USE_AUD4_AS_GPIO_MUTE
#define LOW_MUTE
#endif     


/*
*  SCART TV Pin  SCART TV Pin  SCART TV Pin  SCART TV Pin  SCART TV Pin
*/
//#define SCART_TV_216_USE_PIN55_65_66  // FanGang added for 8202s-16-SY-216-0-D scart control 2005/01/17
#ifdef SCART_TV_216_USE_PIN55_65_66
#define HI_CTRL_SCART_TO_RGB
//#define LOW_CTRL_SCART_TO_RGB
//#define HI_CTRL_TO_RELEASE_SCART
#define LOW_CTRL_TO_RELEASE_SCART
#define HI_CTRL_SCART_TO_DISPLAY_16B9
//#define LOW_CTRL_SCART_TO_DISPLAY_16B9
#endif

/*
* UART UART UART UART UART UART UART UART UART UART UART UART UART UART UART UART
*/
//#define SUPPORT_UART_COMMAND      //Support UART to communicate with external MCU //KENNY 2002/7/16

//================== Board ending ================== Board ending  ================ Board ending =================== Board ending  =========== Board Begin  =====




//================== Video Begin ==================== Video Begin  ================ Video Begin  =================== Video Begin  =========== Video Begin  =====
/*
*  TURBO_DECODE for 8202D
*/
#define TURBO_DECODE

/*
*  Subpicture
*/
#ifdef TURBO_DECODE
#define SUPPORT_DVD_FULL_SUBTITLE
#endif
/*
*  Video seting
*/
/*#define TV_YUV_OUT*/
#define S_VIDEO_OUT

#define TV_USE_4_DAC            //8202S need open always. 4 video DAC.
//#define SCART_TV                  //define it if we support SCART TV, use GPIO-37-38-39 to control
//#define ORI_SCART_TV
//#define SCART_TV_2                //define pin151---SCART_DISPLAY; pin163---SCART_SIG  wanghaoying
//#define AUTO_ADJUST_TV_TYPE         //auto adjust tv type (16:9 ,4:3LB,4:3PS) from disc  //lijd 2004-9-15 13:25

//#define DIGITAL_VIDEO_OUT //Must Mask #define SDRAM_BUS_32BITS to use 16 bits SDRAM width
#ifdef DIGITAL_VIDEO_OUT
    #ifdef IC_8202D //kenny 2005/2/16
    //#define CCIR656_TYPE3 //for 216 pin from pin 55~ pin66
    #else

    #define CCIR656_TYPE1       //CCIR656 Out from Pin225~233(8202A 256pin),Pin55~66(216pin)  
    //#define CCIR656_TYPE2     //CCIR656 Out from Pin164~172,193(8202A 256pin) 
    #endif //#ifdef IC_8202D
#endif 

#ifdef IC_8202D //only 8202D has serial RGB    
    //#define SERIAL_RGB //support Serial RGB
    #ifdef SERIAL_RGB
       #define S_RGB_TYPE1 //for serial R,G,B from pin 55~ pin66
    #endif 
    #ifdef S_RGB_TYPE1
       #undef CCIR656_TYPE3
    #endif
#endif //IC_8202D

#define SUPPORT_VIDEO_BUFFER_STANDBY //kenny 2003/5/13
#ifdef SUPPORT_VIDEO_BUFFER_STANDBY
#define STANDBY_GPIO 52
#endif


/*
* VPP Pixel Aspect Ratio (PAR)
*/
//#define PAR_MP_FORCE_SQUARE                   // force to use square source PAR for MPEG-1/2
//#define PAR_MP4_FORCE_SQUARE              // force to use square source PAR for MPEG-4
#define PAR_MP4_GUESS_43TV                  // guess to use source PAR of 4:3 TV for MPEG-4, according to video size
//#define PAR_MP4_REVERSE_169TV             // reverse operation of tranforming 4:3 TV to 16:9 TV, for MPEG-4
//#define PAR_MP4_PARTIAL_169TV

//#define VCD_BACKWARD_TIME //show backward time on VFD when menu is off,wangfeng 2003-12-15 15:08

//#define START_NO_VPP_DELAY

// Determination of MPEG-2 Progressive 
//#define FRCTL_MP2_ALWAYS_INTERLACED   // always treat MPEG-2 as interlaced in frame rate control
                                        // even if the progresiive flags are set.
//================== Video Ending ==================== Video Ending  ================ Video Ending  =================== Video Ending  =========== Video Ending  =====




//================== Audio Begin ==================== Audio Begin  ================ Audio Begin  =================== Audio Begin  =========== Audio Begin  =====
/*
* Audio Setting
*/
//#define SUPPORT_SDRAM16M_AC3_5_1CH_OUTPUT  //terry,2005/3/30 11:49上午
//#define TWO_CHANNEL_ONLY          //define it to output two channel audio only, mark it for 5.1 channel, Jeff 20020819
#define RAW_HAVE_ANALOG_OUTPUT

//#define SUPPORT_8202D_EXT_ADC   //chyeh 2005/03/21

#ifndef SUPPORT_8202D_EXT_ADC
#define NO_MIC                    //if use it,about MIC item will be gray and can't be selected.
#endif

#define HJ_APEX_NO_KEY

#ifndef SUPPORT_SDRAM16M_AC3_5_1CH_OUTPUT
#define TEMP_TWO_CHANNEL          //define it to output two channel audio only, mark it for 5.1 channel, Jeff 20020819
#define ONLY_DOWNMIX
#endif

/*
* Audio DAC Audio DAC Audio DAC Audio DAC Audio DAC Audio DAC Audio DAC
*/
//#define VFD_PIN_TO_DAC
//audio DAC settings, chose one
//6 channel audio DAC
#define WM8746I2S24         //(format:I2S24)
//#define WM8746            //(format:RJ24)WM8766 is pin-2-pin compatible
#ifdef IC_8202D
#define INTERNAL_AUDIO_DAC  // 8202D//short R187/R189 open R188/R190 reference 8202D-16-SY-216-0-B 
#endif

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


#define SPDIF_REAL_OFF                              //close SPDIF clock when not in SPDIF mode, Jeff 20020920
#define AC3_BASS_MANAGEMENT                         //AC3 Bass Management
//#define SPDIF_PLUS_ANALOG                         //define it when we output SPDIF/PCM+Analog simultaneous, Jeff 20021029
//#define USE_FREQ_MASK

#define MIC_THRESHOLD               0x30            //default:0x30, (0x20 ~ 0xa0)
#define MIC_PRESENSITIVITY          0x1a            //MIC turn-on sense time(unit: 32/44100 sec, only for (S)VCD/MP3)
#define MIC_AFTERSENSITIVITY        0x0903          //MIC turn-off sense time(units:1/3 seconds, Hi-auto, Lo-MIC(unused))
#define ECHO_DECAY_INIT             0x05            //ECHO decay model(1~8), hi:intensity

//#define SUPPORT_EXTERNAL_MIC //kenny 2003/5/14
#ifdef SUPPORT_EXTERNAL_MIC
#define EXTERN_MIC_DECT     57
#define EXTERN_MIC_MUTE     18
#endif

//SDRAM_16Mb_Mode
//#define SUPPORT_EQ_SDRAM_16Mb

#ifndef SDRAM_16Mb_Mode //terry,de-mark,2003/8/2 11:49AM
#define SUPPORT_DVD_3D                              //SUPPORT_DVD_3D defined only to enable DOWNMIX SWITCH
#define DVD_3D_SHOW_SPECTRUM                        //SUPPORT_DVD_3D+DVD_3D_SHOW_SPECTRUM : to show spectrum(not include LPCM)
//#define SUPPORT_DVD_3D_EFFECT//for two channel, DVD can use 3Dsound.
//to remember 3D sound,;yanlb add,2004/07/06
//#define REMB_3DSOUND    //Make sure:SUPPORT_3DSOUND defined       
#endif

//================== Audio Ending ==================== Audio Ending  ================ Audio  Ending  =================== Audio  Ending  =========== Audio  Ending  =====




//================== Servo ==================== Servo ================ Servo =================== Servo =========== Servo ====
//Servo related
// Servo Denotation : PUH_MECHA_Customer
#ifdef SPHE8202
      //#define HI0FS0_STD          // Hitach-HOP1200_FUSS_Standard
      //#define SA0SA0_STD        // SanyoHD60_Sanyo_Standard
      #define SA2SA0_STD        // SanyoHD62_Sanyo_Standard
      //#define SM0SM0_STD        // SAMSUNG_SAMSUNG_Standard
      //#define SO1SO1_STD        // Sony310_Sony_Standard
      //#define PH1YX0_STD        // Philips_Yuxing_Standard
      //#define SA2TO1_SLT        // Sanyo-HD62_TOHEI_Slot-in-Loader
      //#define AA0AA0_STD        // AATEK_AATEK_Standard
      //#define AR0AT0_STD        // Arima_Actima_Standard
      //#define HI0CO0_STD        // Hitach-HOP1200_Conser_Standard
      //#define HI0FS0_STD        // Hitach-HOP1200_FUSS_Standard
      //#define HI0GB0_STD        // Hitach-HOP1200_GBM_Standard
      //#define HI1KZ0_STD        // Hitach-HOP1200W_KZG_Standard
      //#define SA0SA0_BBK0       // SanyoHD60_Sanyo_BBK solution
      //#define SA2HY0_STD        // SanyoHD62_Hanyan_Standard
      //#define SK0SW0_STD        // SANKYO_SHINWA_Standard
      //#define SM0SM0_STD        // SAMSUNG_SAMSUNG_Standard
      //#define SO0SO0_STD        // Sony280_Sony_Standard
      //#define SO1SO1_STD        // Sony310_Sony_Standard
      //#define PI0GI0_STD        // Pioneer_Gigastorage_Standard
      //#define PH1YX0_STD        // Philips_Yuxing_Standard
#endif

//#define DVD_SRV_BUF_SMALL   // terry,2005/4/4 10:11下午
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
#define TRAY_SPEED  0   //  0:fastest   4:slowest :3 for ASA loader, 2 for 佳彩loader,3 for GBM ,0 for full time Eject

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

//================== Servo Ending==================== Servo Ending ================ Servo Ending =================== Servo Ending =========== Servo Ending ====





//================== Setup Begin ==================== Setup Begin ================  Setup Begin ===================  Setup Begin ===========  Setup Begin  ====
//=================================================================
//for DVD setup menu reengineering  //added by JS   //20040728
#define DVD_SETUP_REENG
#define SETUP_COLOR_TYPE2
//=================================================================
///OSD language related settings(don't change the sequence)
//#define USE_ENGLISH_OSD             //LCD_EN
//#define USE_SCHINESE_OSD            //LCD_ZH
//#define USE_TCHINESE_OSD            //LCD_ZH
//#define USE_GERMAN_OSD              //LCD_DE
//#define USE_SPANISH_OSD             //LCD_ES
//#define USE_FRENCH_OSD              //LCD_FR
//#define USE_PORTUGUESE_OSD          //LCD_PT
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

#define DEFAULT_OSD_LANG            0
#ifdef SDRAM_16Mb_Mode
#define N_OSD_LANGS                 2
#define USE_ENGLISH_OSD             //LCD_EN
//#define USE_SCHINESE_OSD            //LCD_ZH
#define USE_SPANISH_OSD             //LCD_ES
#define OSD_LAGN_SETUP_STRING       LCD_EN,LCD_ES,0,0,0,0,0,0
#define OSD_LANG_SETUP_MAP          {0,     1,     0,     0,     0,      0, 0, 0} //mapping table(OSD_LAGN_SETUP_STRING --> USE_XXX_OSD)
#else
#define N_OSD_LANGS                 6//8//3
#define USE_ENGLISH_OSD             //LCD_EN
#define USE_SCHINESE_OSD            //LCD_ZH
#define USE_GERMAN_OSD              //LCD_DE
#define USE_SPANISH_OSD             //LCD_ES
#define USE_FRENCH_OSD              //LCD_FR
#define USE_PORTUGUESE_OSD          //LCD_PT

#define OSD_LAGN_SETUP_STRING       LCD_EN,LCD_ZH,LCD_DE,LCD_ES,LCD_FR,LCD_PT,0,0
#define OSD_LANG_SETUP_MAP          {0,     1,     2,     3,     4,      5, 0, 0} //mapping table(OSD_LAGN_SETUP_STRING --> USE_XXX_OSD)
#endif

/*
*  Region  Region  Region  Region  Region  Region  Region  Region
*/
#define REGION_NUM                  6       //set default region:0->all rigion;1~6->REGION 1~6.
//#define RCD_GPIO_CONTROL          //alan 2002/11/14 05:06下午, use GPIO to control RCD, must run nav.bat
//#define CUS_RCD 1                 //customer region code
//#define GPIO_N  6                 //use GPIO 6

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

#define RATING_8                  //if we define it, there are 8 ratings, 1/2/3/../8, otherwise, 3 ratings, Jeff 20020723

#define SETUP_ALL_VALID             //define it to let SETUP MENU is always valid, Jeff 20021023
//#define SETUP_DONT_PAUSE                // define it to continue play when SETUP, alan 3-8-5 17:48
//idle time to wake up screen saver
#define SAFE_WAIT_TIME              (3* 60 * 100)      //x second
 
//#define	VIRTUAL_KEYBOARD //WSLEE for virtual keyboard 20050518 AM10:30
#ifdef VIRTUAL_KEYBOARD
	#define VIRTUAL_KEYBOARD_16_COLOR
	
#endif
//Maoyong 2004.04.21, in SETUP Menu, Speaker delay display in distance. 1ms<->30cm
//#define SHOW_SPK_DELAY_BY_DISTANCE                 


//================== Setup Ending ==================== Setup Ending ================  Setup Ending ===================  Setup Ending ===========  Setup Ending  ====



//================== GUI Begin ==================== GUI Begin ================  GUI Begin ===================  GUI Begin ===========  GUI Begin  ====
/*
* System System System System System System System
*/
#define DETECT_TIMES    0xff  //Define Disc detect polling time
#define NO_DISC_TIMES   30

//======================================================================
#define RISC_ALIVE_STANDBY        //power on by RISC on standby lijd  2004-9-28 17:33, 2004/10/01 yltseng
//#define SLEEP_WHEN_POWER_ON                       //system enter sleep mode when power-on, Jeff 20020922
//======================================================================

//Upgrade setting
#define SUPPORT_SPI_FLASH
#define UPGRADE_FILE_NAME   {"DVDROM.BIN"}
//#define SUPPORT_UART_UPGRADE      //Upgrade flash via UART, Robert 020603
#define RESET_AFTER_UPGRADE         //reset 8200 and tray out after smart upgrade
//#define UPGRADE_TRAYOUT               //joshua 2004/07/13 tray out when dvdrom.bin have been moved to sdram

/*
*  OSD OSD OSD OSD OSD OSD OSD OSD OSD OSD OSD OSD OSD
*/

//#define NEW_SEARCH_OSD              //new search OSD function, using up/down to switch selection
#define OSD_TIMEOUT                 200
#define OSD_SCREEN_SAVER
#define OSD_SUPPORT_2_COLOR
//#define SUPPORT_FILE_DISPLAY_TM

/*
* IR IR IR IR IR IR IR IR IR IR IR IR IR IR IR IR
*/
//IR setting
#define IR44                        // for new SUNPLUS remote controller
//#define IR200
#define IR_PLAY_RESUME
#define IR_PLAY_RESUME_PAUSE

//#define ADJUSTING_ACTION_VALID_RIGHT_NOW
//#define NEXT_FORWARD_IN_A_KEY
//#define IR5                         //"ircode_N700.h"
#define IR_10_PLUS
//#define IR_NO_REPEAT              //disable repeat, when we keep to press one button, Jeff 20020924

#undef IR_SHUFFLE_ON
#undef KARAOKE_USE_IR_CRT
#undef DOWNMIX_USE_IR_CRT
#undef SUPPORT_SCORE
#undef SETUP_DEFAULT_USE_IR_CRT
/*
*  MP4  MP4  MP4  MP4  MP4  MP4  MP4  MP4  MP4  MP4  MP4  MP4
*/
#ifdef TURBO_DECODE

#define SUPPORT_MP4  
#ifdef SUPPORT_MP4
    
    #define SUPPORT_MP4_SUBTITLE
    #ifdef SUPPORT_MP4_SUBTITLE
        //#define SUBTITLE_SUPPORT_COMMON_FORMAT
        #define SUBTITLE_SUPPORT_ALL_FORMAT

        #define SUPPORT_FONT_UTIL
        #ifdef SUPPORT_FONT_UTIL
            //#define SUPPORT_MULTI_FONT_SWITCH   
            #define SUPPORT_FONT_CP_950_COMMON    // reference to h/LanguageUtil.h for more languages
        #endif // SUPPORT_FONT_UTIL
    #endif
    
    #define DIVX_DRM  // DivX DRM 2.0 (not compatible with DRM 1.0)
    #ifdef  DIVX_DRM
        //#define DIVX_DRM_AES_ONLY
        #define SHOW_DRM_REGISTRATION_CODE_IN_SETUP


#ifdef SHOW_DRM_REGISTRATION_CODE_IN_SETUP
       #define DRM_CODE			//WSLEE for generate drm code 050615
#endif



        // 12-bits Model ID for DivX DRM (mask 0xF0FF)
        // This model number is assigned to each product by DivXNetworks.
        #define DIVX_DRM_MODEL_ID (0x3031 & 0xF0FF)	// Value 0x3031 is a TEST value only.
    #endif    
#endif  

#endif//#ifdef TURBO_DECODE

#define SUPPORT_FILE_DISPLAY_TM
#define SUPPORT_MPG_FILE_PARSER

/*
*  VFD  VFD  VFD  VFD  VFD  VFD  VFD  VFD  VFD  VFD  VFD  VFD  VFD  VFD
*/
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


/*
*  DVD  DVD  DVD  DVD  DVD  DVD  DVD  DVD  DVD  DVD  DVD  DVD  DVD  DVD
*/
//#define MODIFY_PARENTAL_GUI
//#define SET_PARENTAL_STS_AUTO_LOCK
//#define DVD_DIRECT_SELECT_CHAPTER
#define DVD_MENU_RSM
//#define DVD_PREVIEW_FUNCTION
//#define DVD_AUDIO
#define NO_DTS_OUTPUT             //define it when we don't support DTS audio output
#ifdef NO_DTS_OUTPUT                
//#define FORCE_NO_DTS_OUTPUT         //define it when we don't support DTS audio output, but load DTS dsp_code.
#endif
//#define SUPPORT_SDRAM16M_DTS_5_1CH_OUTPUT   //dts output(6).
    #ifdef SUPPORT_SDRAM16M_DTS_5_1CH_OUTPUT
    #undef  NO_DTS_OUTPUT
    //#define MOVE_PAL_AUDYA
    #endif
/*
*  Game Game Game Game Game Game Game Game Game Game Game
*/
//#define SUPPORT_NESGAME
#ifdef  SUPPORT_NESGAME   //for VFD pannel key valid in PLAY game state  2004-7-2 15:16 lijd
//#define SUPPORT_IR_GAME
#define VFDKEYBUFADDR      0x588 
#endif

/*
*  WMA  WMA  WMA  WMA  WMA  WMA  WMA  WMA  WMA  WMA  WMA  WMA  WMA  WMA
*/
#define SUPPORT_WMA           //nono mark 2004-10-16 16:20

/*
*  File system  File system  File system  File system  File system  File system
*/
//#define SUPPORT_JOLIET_FORMAT
//#define SUPPORT_FS_LONGNAME
#define FS_LOAD_DIR_SEPARATELY
#ifdef TURBO_DECODE 
    #define REDUCE_SUP_SRT_FOR_FS9660
#endif

/*
*  MP3  MP3  MP3  MP3  MP3  MP3  MP3  MP3  MP3  MP3  MP3  MP3  MP3  MP3
*/
//#define MP3_DIRECT_SELECT         //select file item all disc, panxing,2002-4-8

//#define MP3_CD_FF1_BF1_MUTE       //FF*2 and BF*2 mute

//li mao add 2004-5-12 10:02
//#define NO_DISPLAY_CDROM_ICON  
//#define MP3_BK_GROUND_BLACK;     
//#define MP3_BK_GROUND_GREEN;     
//#define MP3_BK_GROUND_AQUA; 

#ifdef TURBO_DECODE
#define SUPPORT_FILE_SYSTEM_MODE        
#endif

//Maoyong 2004.04.13 for program play of others file type except jpg/mp3/wma in CDROM disc

#ifdef  SUPPORT_FILE_SYSTEM_MODE
#define SUPPORT_FS_OTHER_PROG                   //Maoyong 2004.04.14
//#define SUPPORT_PLAYBACK_ICON       // display osd playback icons
#endif


/*
*  GUI  GUI  GUI  GUI  GUI  GUI  GUI  GUI  GUI  GUI  GUI  GUI  GUI  GUI
*/
#define ICON_REPEAT_FOLDER       // zhuyf add for mp3  2004-8-10     
#define DIR_SCROLL_BAR // 2006-03-21, mimitsai add for dir scroll bar

//#define INDIGO_STYLE_OSDUI // 2006-02-24, mimitsai add for new osd ui

// 2006-04-20, we can only choose one style GUI of the following three define.
#define NEW_MP3_GUI
//#define INDIGO_STYLE_FSGUI // 2006-02-24, mimitsai add for fsgui new ui
//#define FS_BMP_GUI  //zhaoyanhua. draw a new mp3 GUI with bmp

#ifdef NEW_MP3_GUI
    #undef INDIGO_STYLE_FSGUI
    #undef FS_BMP_GUI
    //#define MP3_LARGE_GUI // must dependant on NEW_MP3_GUI
#elif defined(INDIGO_STYLE_FSGUI)
    #undef NEW_MP3_GUI
    #undef FS_BMP_GUI
#else
    #undef NEW_MP3_GUI
    #undef INDIGO_STYLE_FSGUI
    #define FRAMEBUF_BMP_API
    #define THUMBNAIL_BMP_GUI //feeling 2004-07-15
    #define HELP_BMP_GUI      
    #if defined (JPG_EFFECT) && defined (HELP_BMP_GUI)
        #define USE_PREVIEW_KEY_TO_CALL_JPGEFFECT_HELP
        #define CALL_JPGEFFECT_HELP    
    #endif
#endif//ifdef FS_BMP_GUI 

//#define SUPPORT_FONT_OUTLINE //2006-04-27, mimitsai add for font outline of subtitle, setup menu, and FSGUI 
#ifdef SUPPORT_FONT_OUTLINE
	//#define SUPPORT_FONT_OUTLINE_IN_SETUP_MENU
#endif		

//#define FONT_WIDTH_ADJUSTMENT //2006-04-27, mimitsai add for adjusting font width of subtitle, setup menu, and FSGUI 
#ifdef FONT_WIDTH_ADJUSTMENT
	//#define FONT_WIDTH_ADJUSTMENT_IN_SETUP_MENU
#endif

/*
* JPEG JPEG JPEG JPEG JPEG JPEG JPEG
*/
#define PLAY_JPE_JPEG_FILE      //liweihua 2004-5-12 ,for "*.jpeg" file    
#define JPEG_EXT2FULL             //extend JPEG to full screen
#define JPGExtMaxMultiple         2               //max. ext multiple=JPGExtMaxMultiple * JPGExtMaxMultiple
#define JPG_EFFECT   //David Add 3-6-26 17:12
#define JPEG_SLIDE_TIME             (3*100)         //JPEG slide show hold time, x second
#define JPEG_THUMBNAIL_MENU         //enable JPEG thumbnail menu
//#define JPEG_PREFETCH               //pre-fetch JPEG file and decode when we select someone file

#ifdef JPG_EFFECT
//#define JPG_EFFECT_ONLY_ROTATE	//wanghaoying 2003-09-03 13:54, if define this only up/down/right/left has effect no program key
//#define USE_PREVIEW_KEY_TO_CALL_JPGEFFECT_HELP
//#define CALL_JPGEFFECT_HELP
//#define SUPPORT_PART1_JPGEFFECT//use odd Jpg_effect_mode, code size reduce 1k or so.
//#define SUPPORT_PART2_JPGEFFECT//use even Jpg_effect_mode,code size reduce 1k or so.
#endif


/*
* CDDA CDDA CDDA CDDA CDDA CDDA CDDA CDDA CDDA CDDA CDDA CDDA
*/
//CD-G related
#define SUPPORT_CDG                 //define it to support CD-G

/* ----------------------------------------------------------
CD-TEXT
Simon Lai 2006.6.29
---------------------------------------------------------- */   
//#define SUPPORT_CD_TEXT
#ifdef SUPPORT_CD_TEXT
    #define DISPLAY_CD_TEXT
    #define OSD_FONT_API
#endif

//================== GUI Ending ==================== GUI Ending ================  GUI Ending ===================  GUI Ending ===========  GUI Ending  ====    

/*  Config: (pls add define to itself position
*   1. IC
    2. Board: sdram,pin,gpio mute,modual test,rom,usb,card,scart,uart
    3. Video: turbo decode,output setting,vpp
    4. Audio: DAC,channel
    5. Servo
    6. Setup Memu
    7. GUI:   system,upgrade,osd,ir,mp4,vfd,dvd,game,wma,file system,mp3,jpeg,cdda,
*
*/    
//======= Bottom ======= Bottom ======= Bottom ======= Bottom ======= Bottom ======= Bottom ======= Bottom ======= Bottom ======= Bottom

