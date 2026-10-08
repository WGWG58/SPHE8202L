//nono split form user_int.h 5-5-9 17:51

/*WMA/HDCD:
* "This product is protected by certain intellectual property rights of
* Microsoft and cannot be used or further
* distributed without a license from Microsoft.
*/

//#define REMAIN_TIME               //must excute "nav.bat"2-7-12 19:31 
//#define NEW_SETUP_OSD 
//#define GREY_OSD_DISP             // grey display in region0 and 
                                    // white fontcolor in other region except setup menu . ych 2-7-8 17:27
                                    //
//
// SUPPORTED TV-FORMATS
// (should define/undefine in other setting files)
//
#define SUPPORT_NTSC
#define SUPPORT_PAL
//#define SUPPORT_NTSC
#define SUPPORT_PAL60
//#define SUPPORT_PALM
//#define SUPPORT_PALN
//#define SUPPORT_PALNc

#define TV_FORMAT_525_DEFAULT   TV_FORMAT_NTSC
#define TV_FORMAT_625_DEFAULT   TV_FORMAT_PAL
#define TV_FORMAT_AUTO_DEFAULT  TV_FORMAT_625_DEFAULT

/*
* JPEG JPEG JPEG JPEG JPEG JPEG JPEG
*/

//#define JPG_OLD_PARSER_FLOW

#ifndef JPG_OLD_PARSER_FLOW

    //New jpeg flow
    #define JPG_FULL_EXPANSION
    #define JPG_PIC_POST_PROCESSING
    
    #ifdef  JPG_PIC_POST_PROCESSING
        #define JPG_SPECIAL_EFFECT
        #define JPG_ROTATION_EFFECT
    #endif
    
    #if defined(JPG_SPECIAL_EFFECT)&& !defined(JPG_FULL_EXPANSION)
        #error if you want jpeg effect, you must define JPG_FULL_EXPANSION
    #endif
    
#else

    //old jpeg flow
    #define JPG_READ_SPEED_UP    
    #define JPG_SUPPORT_PROGRESSIVE
    #define JPG_BETTER_QUALITY              //2004.12.24 joshua, for better quality
    #define JPEG_THUMBNAIL_MENU             //enable JPEG thumbnail menu
    #define JPG_EFFECT   
    #define JPEG_EXT2FULL                   //extend JPEG to full screen
    #define JPGExtMaxMultiple         2     //max. ext multiple=JPGExtMaxMultiple * JPGExtMaxMultiple
    //#define ZOOMOUT_JPEG_ROTATE_NOT_SHOW_ZOOM //joshua marked it    
    //#define INCREASE_CONTRAST_SATURATION_IN_JPEG//joshua add.20050721                
    //#define JPEG_PREFETCH               //pre-fetch JPEG file and decode when we select someone file        
    
    #ifdef JPG_EFFECT
    //#define JPG_EFFECT_ONLY_ROTATE	//wanghaoying 2003-09-03 13:54, if define this only up/down/right/left has effect no program key
    //#define USE_PREVIEW_KEY_TO_CALL_JPGEFFECT_HELP
    //#define CALL_JPGEFFECT_HELP
    //#define SUPPORT_PART1_JPGEFFECT//use odd Jpg_effect_mode, code size reduce 1k or so.
    //#define SUPPORT_PART2_JPGEFFECT//use even Jpg_effect_mode,code size reduce 1k or so.
    #endif
    
#endif

#define JPEG_SLIDE_TIME             (3*100)         //JPEG slide show hold time, x second



#if !defined(PORTABLE_DVD)&& !defined(ALCO_PORTABLE) //shenyj add for alco 2006/03/23
    #define SUPPORT_VFD                             //move from config.h nono 2-9-16 23:10
    #define SUPPORT_VFD_PANEL //lijd 2004-12-4 11:12                            
#endif
    
//==============================
//Smart upgrade related function (ERASE_CHIP is defaulted)  joshua 04-7-20
//==============================
//#define SUPPORT_SPI_FLASH     //only for 8202L

#define SUPPORT_PARALLEL_FLASH
//#define UTI_SERIES_FLASH
//#define SUPPORT_28X_FLASH	//NOTE: Flash pin13 & 14 must connect to 3.3V ;yaowh add. 2006-1-20 15:01
//====================================================================
// IR related parameter area BEGINNING
//====================================================================

//Define for optional IR function 
#define IR_GOTO_ON
#define IR_PROG_ON
#define IR_REPEAT_ALL_ON
#define IR_SHUFFLE_ON
#define LINEAR_PLAY_9FRAME  
#define SUPPORT_PREVIEW_9FRAMES
#define KARAOKE_USE_IR_CRT
#define DOWNMIX_USE_IR_CRT
#define SUPPORT_SCORE
#define SETUP_DEFAULT_USE_IR_CRT
#define TVFORMAT_USE_IR_CRT

#ifndef SDRAM_16Mb_Mode
#define SUPPORT_SLOWBACKWARD
#endif

//=================================================================
//New OSD driver
//=================================================================
#define NEW_OSD_DRIVER
//#define SERVO_DEBUG_MSG_ON_OSD
//====================================================================
// IR related parameter area ENDING
//====================================================================

#define VOB_SUBTITLE        //joshua, 20050811, added for changing audio and sub-picture streams of VOB files

#define MAX_OSD_STR_ID  256       
//#define TUNR_OFF_PARENTAL_LVL
//#define MAX_OSD_LANG_STR_ID  25
#define MAX_OSD_LANG_STR_ID  39//32       

#define PASSWORD_TOTAL_DIGITAL      4

#define SEEK_SKIP_TIME                  1//NORMAL=1             

//#define SP_ALWAYS_BY_USER_CTL       //we use sub-picture selection in SETUP-MENU as our defult, Jeff 20020925
#define NEW_SEL_SUBTITLE_WAY        //fixed some bugs, base on SP_ALWAYS_BY_USER_CTL.nono 5-8-17 16:52


// ADC config ( default: 0)
// 0: Select Line_in L/R capability,but only mix right channel      //pin159
// 1: Select Mic_Amp capability (only left channel capability)      //pin157
#define ADC_CONFIG_MODE             0//2

#ifdef  SUPPORT_8202_EXT_ADC   //chyeh  2005/03/21
#undef  ADC_CONFIG_MODE
#define ADC_CONFIG_MODE     8
#endif


///define volume inital value
#define VOL_VALUE   15
#define DEFAULT_VOL     VOL_VALUE


//#define SUPPORT_PRECALCULATE_VIDEOBITRATE_FOR_FILE_MODE   // 2006/05/18 yltseng

#ifdef IC_8202L
#define TV_USE_QUART_SWING    //rbhung for DAC B,C,D quart-swing
#else
#define TV_USE_HALF_SWING//nono move from set.h
#endif

#ifndef PMP_DVD
#define TELL_FROM_MP4_EXT_NAME// nono open it.5-5-25 21:08
#endif
// 2004/12/16 yltseng, with this define enabled, osd color palettes are affected by brightness and
// contrast in setup menu
//#define OSD_COLOR_ADJUST_BY_BRIGHTNESS_AND_CONTRAST

#define ONLY_SHOW_PIC_DIR//joshua add 20050613

#ifdef  PORTABLE_DVD//Jack 06/05/20 added for Portable
#define SUPPORT_GOTO_IN_JPEG_STATE 
#endif


