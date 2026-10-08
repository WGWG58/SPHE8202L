// 2005/09/12 yltseng, Add new structure for font

#ifndef _CUST_DEF_H_
#define _CUST_DEF_H_

#include ".\\h\\set.h"
#include ".\\h\\ic_configuration.h"

#ifdef SUPPORT_6500
#include ".\\Customers\\cfg_6500.h"
#endif

#ifdef  DVB_DVD_8202 //Jack added 06/02/06
#include ".\\Customers\\cfg_dvb.h"
#endif

#ifdef FOLLOW_8202D_IC_SETTINGS    //kevinmonkey 050520, use 8202D as basic config
    #define IC_8202D
#endif  //#ifdef FOLLOW_8202D_SETTING

#ifdef SDRAM_16Mb_Mode
    //#define SETUP_PROGRAM_IN_PLACE_UNDER_16M
    #ifdef SETUP_PROGRAM_IN_PLACE_UNDER_16M     // 2004/12/29 yltseng
    // Because we use track buffer to store Setup/Program OSD, so this buffer can't
    // be overwritten when Setup/Program OSD is shown
    #undef  SETUP_DONT_PAUSE
    #undef  PROG_DONT_PAUSE
    #define JPEG_PAUSE_WHEN_SETUP
    #endif
    
    #undef HD_DISPLAY_CONTROLLER    //joshua, 20060920, no HD output of 16m solution
    
#endif

//#define SEARCH_ISO9660_DIRECTORY_BY_DIRECTORY_TRAVERSE      // 2005/06/08 yltseng
//#define SEL_AUDIO_LANG_BY_USER
//#define SEL_AUDIO_LANG_BY_SETUPMENU

//#define FIX_VIDEO_RATIO_ISSUE//nono 20040518

#define SUPPORT_MIX_MONO	//for QSI by diya 2006/8/3 02:59下午


//#define SP_CTRL_BY_SETUP_MENU//nono 4-9-7 23:39 for SETUP MENU is set "OFF", but SUBP is still ON. Tkx for Terry's help.

//#define DVD_REP_ALL_TITLE                //terry,2003/10/18 06:30PM
#define SHARE_NAV_VAR                         //terry, share 
#ifndef MAKE_ONLY_UPDATE_CODE
//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
  #ifndef	IC_8202E    // terry,2005/4/5 10:46上午
    #define SUPPORT_ECC // define to use software ECC+De in ap level
                        // undefine to use software ECC+De in servo level, will retry, and more strong recovery, but larger code size
  #endif                    
#endif
//#define SUPPORT_STREAM_BUFFER
#if     defined(DVB_DVD_8202)
#if     !defined(SUPPORT_STREAM_BUFFER)
#define SUPPORT_STREAM_BUFFER
#endif  /* !defined(SUPPORT_STREAM_BUFFER) */
#endif  /* defined(DVB_DVD_8202) */

//#define SUPPORT_MIX_MP3_CDDA
#ifdef SUPPORT_MIX_MP3_CDDA     //linrc change "SUPPORT_MIX_MP3_CDDA" to "SUPPORT_MIX_DATA_CDDA_DISC"
#define SUPPORT_MIX_DATA_CDDA_DISC //because we support this type mix mode disc 2004-12-15 15:53
#endif

#define CUSTM_MENU_REVISE //WSLEE add this for static region item customer menu 20050525 PM3:00
#ifdef CUSTM_MENU_REVISE
	#define REGION_REMOVE 4
#endif



//#define UOP_PROHIBIT_ANGLE_SHOW_OFF		//nono 3-12-18 15:10 for YILI.

//#define JPG_EFFECT   //David Add 3-6-26 17:12
//#define JPG_ONCE_SHOW_ALL_PER_PIECE
//#define USER_LOGO
//#define JPG_LOGO		//use JPG save to logo.
//#define USER_MPEG_LOGO  //David 3-7-15 17:55

//#define SF_SR_IN_A_KEY    //freyman 2003-8-3 16:52 moved here from ircmd.c
//#define DVD_SEQ_PLAY
#define NEW_GOTO
//#define BIG_AC3_VOICE                         //terry, adjust ac3 default voice volume,0508 ,avoid audio noise
//#define SUPPORT_ID3
//#define OLD_VFD_DRV                           //old/new vfd driver ( different iop code )
//#define SLOT_IN_LOADER                        //robert 020919


//====================================================================
// System misc. function related
//====================================================================

#define DSPWATCHDOG     (5*100/50)         //RISC do DSP watchdog(x second)


#if defined(TONIC_DVD)||defined(INTRO_10S)			//dingzhy for tonic   2/3/2004 10:41AM
#define INTRO_LEN       10*75 + 5
#elif defined(MINTON_DVD)||defined(INTRO_7S)						//heqiang, cut down CD preview time to 7 seconds. 2004-3-5 11:03 
#define INTRO_LEN       7*75 + 5
#else
#define INTRO_LEN       15*75 + 5//dingzhy "+5" for some cd only play 14s    4-11-11 15:22
#endif//end of TONIC_DVD

#ifdef DESAY_DVD        //freyman 2003-8-6 11:05 added to cut the preview CD time to 8 sec
    #ifdef INTRO_LEN
    #undef INTRO_LEN
    #define INTRO_LEN 8*75
    #endif
#endif


//define password to show vcd F/W code version
#define PASSWORD

//define multiple screen saver selection
//#define MULTISCRNSAVER


//====================================================================
// JPEG related parameter area
//====================================================================

#ifndef JPG_OLD_PARSER_FLOW
    #undef JPEG_THUMBNAIL_MENU
    #undef MP3_JPEG_COWORK
    #undef JPG_EFFECT
    #undef CALL_JPGEFFECT_HELP
#endif

//====================================================================
// audio related parameter area
//====================================================================

//Jeff modify, 20031222
//Define audio DAC format(DSP --> DAC)
//legacy define
#if defined(WM8746I2S24)
    #define USE_DAC_I2S24
#elif defined(WM8746)
    #define USE_DAC_RJ24        //recommend to use this
//#elif defined(PCM1606)
    //#define USE_DAC_RJ16        //wuxiaofeng add for Eton
#endif


#ifdef USE_DAC_RJ24
    #define DACFORMAT       0x5e    //Right-justify format, High:L, Low:R
#elif defined(USE_DAC_I2S24)
    
        #define DACFORMAT       0x4d    //I2S  format, Low: L, High:R // benson update 2004.08.18
    
        
    
#elif defined(USE_DAC_RJ16)
    #define DACFORMAT       0x52    //Right-justify format, High:L, Low:R
#elif defined(USE_DAC_I2S16)
    #define DACFORMAT       0x41    //I2S  format, Low: L, High:R
#elif defined(USE_DAC_LJ24)
    #define DACFORMAT       0x5c    //LJ24  format, Low: L, High:R
#elif defined(USE_DAC_LJ16)
    #define DACFORMAT       0x50    //LJ16  format, Low: L, High:R
#else
    #define DACFORMAT       0x5e    //Right-justify format, High:L, Low:R
#endif

//Define AUD_XCK is output or input pin
#define SUPPORT_AUD_XCK_OUT


//Define Extern MIC OK
//#define SUPPORT_EXT_MIC

#ifndef NO_MIC
#define VOCAL_CANCEL
#endif


#ifdef SUPPORT_EXT_AD_SHOW_MIC_AUTO_SING    //ouyang add for extern AD achieve AUTO sing 2004-12-10 19:15
    #define VOCAL_CANCEL
#endif
    
#ifdef VOCAL_CANCEL
    #define MAX_CH_NUM  4
    #define CH_AUTO_L   3
    #define CH_AUTO_R   4
    //#define SET_AUTO_SW_CH_TM 100 //1 sec    //200 //2 sec
    //#define SET_AUTO_MUTE_TM 300 //3 sec /*jhuang 2001/4/20 05:37PM*/
#else
	#ifdef SUPPORT_MIX_MONO		// diya 2006/8/3 05:44下午
    #define MAX_CH_NUM 3
  #else
    #define MAX_CH_NUM 2
  #endif
#endif

#if defined(SUPPORT_8202_EXT_ADC)||defined(SUPPORT_8202D_EXT_ADC)   //chyeh  2005/03/23
#undef  ADC_CONFIG_MODE
#define ADC_CONFIG_MODE     8
#endif

//====================================================================
// VFD related parameter area
//====================================================================

//#define TEST_VFD  1
//#define VFD2OSD_DBG_TXD

//Define VFD driver type
#define NEC16311         0x01       // Made by NEC
#define NEC16312         0x02       // Made by NEC
#define MN12510          0x03       // Made by Panasonic
#define BU2872AK         0x04       // Made by Rohm
#define HEF4021B         0x05       // Made by Philips
#define NJU3421A         0x06       // Made by JRC
#define VFD_NO_SCAN      0x20
#define HT1621           0x21       // Made by Holtek
#define SPL10            0x22       //SPL10 VFD 
#define VFD_NONE_DRIVER  0xff
#define VFD_MCU51        0x23       //2005-4-14 9:22 zhoulin

//Define VFD module type   
#define ZEC_VFD28_0901  0x01      // Made by Zec
#define ZEC_VFD28_0903  0x02      // Made by ZEC
#define FUT_6_BT_265GK  0x03      // Made by Futaba
#define FUT_6_BT_269GK  0x04      // Made by Futaba
#define FUT_6_BT_253GK  0x05      // Made by Futaba
#define FUT_6_BT_267GK  0x06      // Made by Futaba
#ifdef YADAI_PT6554_PANNEL
#define  pt6554         0x07
#else
#define ZEC_0601        0x07      // Made by Futaba
#endif
#define LCD_PANEL       0x08      // Made by Futaba
#define FUT_6_BT_269GK1 0x09
//#define HT1621_LCD      0x0a
//#define HT1621_LCDX     0x0d    // 蛌詠珘儒そ
#define HT1611_LCD      0x0e       // chichang 2001 6/6 NINTAUS DVD-N701
#define HO16512_VFD     0x0c      // zyf 2000/11/16
#define VFD_NONE        0xff      // No Vfd Module

#ifdef N701_PANNEL 
    #define VFD_DRIVER      NEC16312 
    #define VFD_MODULE      HT1611_LCD 
    
#elif defined(YUXING_PANNEL)    
    #define VFD_DRIVER      NEC16312 
    #define VFD_MODULE      Y_DVD_801D

#elif defined(SAMSUNG1_PANNEL)      //add by shawn 910131
    #define VFD_DRIVER      NEC16312
    //#define VFD_MODULE        S_DVD1

#elif defined(HT1621_PANNEL)||defined(SKYWORTH_HT1621_PANNEL)
    #define VFD_DRIVER      HT1621

#elif defined(SPL10_PANNEL)
#define VFD_DRIVER      SPL10

#elif defined(HC164_PANNEL)
#define VFD_DRIVER      HC164

#elif defined(MCU810_PANNEL)
#define VFD_DRIVER      MCU810

#elif defined(YADAI_PT6554_PANNEL)
#define VFD_DRIVER      PT6554

#elif defined(AD7312_PANNEL)
#define VFD_DRIVER      AD7312

#elif defined(GT1128_PANNEL)
#define VFD_DRIVER      GT1128

#elif defined(MCU51_PANNEL)  //2005-4-14 9:31 zhoulin
#define VFD_DRIVER      VFD_MCU51

#else
    #define VFD_DRIVER      NEC16312 
    #define VFD_MODULE      FUT_6_BT_269GK1

#endif 


//====================================================================
// IR related parameter area move to user_init.h 4-1-13 13:41
//====================================================================

//Define for optional IR function 
//#define IR_GOTO_ON
//#define IR_PROG_ON
//#define IR_REPEAT_ALL_ON
//#define IR_SHUFFLE_ON
//#define LINEAR_PLAY_9FRAME

#ifdef IR_KEY_SET_VIDEO_MODE//nono 20031215
#define VIDEO_MODE_I2C_ADDRESS 127
#endif//IR_KEY_SET_VIDEO_MODE

//#define NEC16312SW   //lijinhai for rotary switch key


//
// SDRAM related config
//
#ifdef SPHE8202
    #define USE_108MHZ
#endif

#ifdef SDRAM_BUS_32BITS
    //#define F94_5
    #if defined(USE_108MHZ)&&!defined(SCALER_6500)//nono add "&&!defined(SCALER_6500)"20051023
    #define F108                // 4.00x
    //#define F114_75             // 4.25x
    #else
    #define F121_5              // 4.50x
    #endif
    
    //#if !defined(SDRAM_16Mb_Mode)
	//    #define DIP_CFG_ENABLE
	//#endif
#else
	//#if !defined(SDRAM_16Mb_Mode)
	    //#define DIP_CFG_ENABLE
    //#endif
    
    #if (defined(DIP_CFG_ENABLE) && defined(IC_8202D))
        #define F141_75
    #else
        //#define F108                // 4.00x (only for test, may not work)
        //#define F114_75             // 4.25x
        #if defined(TURBO_DECODE) && defined(IC_8202D)
           #define F135               // 5.00x
        #else        
            #ifdef  SUPPORT_HD_RESOLUTION  //8202L for HD output
                #define F135               // 5.00x
            #else
            	#ifdef IC_1002
            		#define F108
            	#else
                	#define F121_5             // 4.50x
                #endif
            #endif            
        #endif
    #endif
#endif

#ifdef F108 
    #define DISABLE_3D_DUE_TO_PERFORMANCE //Steven add 2006/07/03 for invalid 3D function when use 108MHZ//
#endif
#define SDRAM_NO_REORDER

#ifdef IC_8202L	//zhongshan	for 8202L default open 2006-9-19 
/*
* Spread Spectrum Clock Setting
*/
#define ENABLE_SSPLL		//rbhung 2006.7.28 for Spread Spectrum function

#ifdef ENABLE_SSPLL
//#define SSPLL_TYPE1
#define SSPLL_TYPE2			//TYPE2 > TYPE1
#define SSPLL_STEP_VALUE	7	//0~7
#endif

#ifdef F121_5
#define SSPLL_F121_5
#elif defined(F135)
#define SSPLL_F135
#endif

#endif //IC_8202L

//#define MB22		            // potatooo: don't use now
#define USE_LPCM_REPLACE_PCM //terry,2004/3/4 08:40PM

#ifdef SDRAM_16Mb_Mode
    #define MEMCFG_COMPACT_MODE			// potatooo
    #define MEMCFG_MOVE_OSDSUP			// potatooo
    #ifndef TURBO_DECODE				// kevinmonkey 050309 chosing TURBO_DECODE or L-memory
        #define MEMCFG_PAL_LMEM			// potatooo
        #define DTH_CFG_ENABLE			// potatooo
    #endif
    //#define NO_AUDIO_DSP
    #define SDRAM_1PCS	
    #ifndef SUPPORT_SDRAM16M_DTS_5_1CH_OUTPUT //linrc  2004-11-24 17:55
    #define NO_DTS_OUTPUT  
    #endif
    #undef SUPPORT_SLOWBACKWARD
    //#undef JPG_SUPPORT_PROGRESSIVE
    #undef JPG_READ_SPEED_UP
    /*#define ONLY_B_PIC*/
#else
    /*#define DIP_CFG_ENABLE*/
    /*#define JPEG_VFX_ENABLE*/
    //#define SUPPORT_BOOK  //this config should be moved to cfg_customer.h
    #ifndef MAKE_ONLY_UPDATE_CODE
    #define SUPPORT_3DSOUND
    //#define TWO_SUBTITLE
    #define COMPRESS_CODE
    #define PLAY_OKO_DISC
    #endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
#endif

#ifdef SUPPORT_3DSOUND
#define RESTORE_EQ_AFTER_DSPRESET//Steven 2006/07/14 for restore EQ after dsp reset//
#endif

#if !defined(SDRAM_16Mb_Mode)&&!defined(NEW_STYLE_SETUP)//nono for GBM
#if !defined(SUPPORT_JPEG_MIC)/*&&!defined(USE_NEW_SCHINESE_OSD)*/
#define OSD_FONT_COMPRESS     /* alan 020424 : flag to decide if you want to compress osd font */
#endif
#endif

#define SETUP_TAB			// alan, 2003/3/4 04:56下午, for TAB setup menu

#define	FREQ_MASK_DEFAULT		0xf

#define WATCHDOG_RENEW_TIME		0xbfff

//#define NEWSTYLE_WINDOW         //XYY,20030701
//#define BAD_DISC_SEQ_PLAY    //terry,2003/8/29 02:18AM,for all custumer
#ifndef MAKE_ONLY_UPDATE_CODE//??
//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
#define DVD_ALWAYS_AUTO_PLAY    //terry 4-6-14 12:22
#endif
//#define CHANGE_DSP_SPDIF_OFF	//nono 2003-10-21 21:07 spdif output, when change dsp code, run spdif off.

/*
* setup rating level    
* wanghaoying 2003-11-22 17:27
* If you want change the default setting of rate for some customer,
* Please define RATE_DEFAULT in the customer's cfg_xxxx.h.
* Notice: Please note me if you want to modify something here
*/
#define RATE_LOW    2

#ifdef RATING_8
    #ifdef EASTECH_NO_PARENTAL_CONTROL
        #define RATE_HIGH   10
    #else
#define RATE_HIGH   9
    #endif
#else
#define RATE_HIGH   4
#endif 

#ifndef RATE_DEFAULT
#define RATE_DEFAULT    RATE_HIGH
#endif 



// For DISC_ID_IN_FLASH to work, SAME_DISC_RESUME must also turn on
// Use 64KB of flash to store DISC RESUME information and SETUP Information
//#define SAME_DISC_RESUME   // in cfg_customer.h
//#define DISC_ID_IN_FLASH

//#define EON_SPI_FLASH   
//#define AMIC_SPI_FLASH

#ifdef DISC_ID_IN_FLASH
    #define SETUP_IN_FLASH  //Do you what to get rid of EEPROM and use the flash to store setup
    #define RW_NVMEM
    #define FLASH_HISTORY
    
    #if defined(EON_SPI_FLASH)||defined(AMIC_SPI_FLASH)
        //for Eon and Amic spi flash, no byte programming, write four byte once
        #undef FLASH_HISTORY
    #endif
    
    //#define SPEED_UP_FLASH_WRITE//Jack added 05/11/30 for speed up flash write...
    
    #ifdef SPEED_UP_FLASH_WRITE
    #define UNKNOWN_FLASH_ID    0xfe
    #endif
#endif

/*
#if defined(DISC_ID_IN_FLASH) && defined(SAME_DISC_RESUME)
//VERY IMPORTANT. 
// if ROM.BIN>=458752bytes, you have to use a 8Mbit flash to support disc resume features

//for 4Mbit Flash, uses addr 0x70000-0x7ffff for disc id
//#define FLASH_START_ADDR  0x70000
//#define FLASH_ERASE_SECTOR 7

// for 8Mbit Flash, uses addr 0xf0000-0xfffff for disc id
    #ifdef SUPPORT_SPI_FLASH
        #define RESUME_USE_SPI_BOOT_SECTOR
        
        #ifdef  RESUME_USE_SPI_BOOT_SECTOR        
            #define FLASH_START_ADDR            0x0
            #define FLASH_ERASE_SECTOR_TYPE     1           //for spi boot sector
            #define FLASH_SECTOR_SIZE           (8<<10)    //8KB
            #define FREE_SECTION_ARRAY_INDEX    10          //1024bytes
            #define FREE_SECTION_SPACE          10          //10:1024bytes, 11:2048bytes, 12:4096bytes, 13:8192
            #define ERASING_KEYWORD             0xFF
        #else               
            //use 18th sector, 64KB            
            #define FLASH_START_ADDR            0xf0000
            #define FLASH_ERASE_SECTOR_TYPE     0           //for spi normal sector
            #define FLASH_SECTOR_SIZE           (64<<10)    //64KB
            #define FREE_SECTION_ARRAY_INDEX    10          //1024bytes
            #define FREE_SECTION_SPACE          10          //10:1024bytes, 11:2048bytes, 12:4096bytes, 13:8192
            #define ERASING_KEYWORD             0x5A
        #endif
    #else
        //use 16th sector, 64KB            
        #define FLASH_START_ADDR            0xf0000
        #define FLASH_ERASE_SECTOR_TYPE     0           //meaningless for parallel flash
        #define FLASH_SECTOR_SIZE           (64<<10)    //64KB
        #define FREE_SECTION_ARRAY_INDEX    10          //1024bytes
        #define FREE_SECTION_SPACE          10          //10:1024bytes, 11:2048bytes, 12:4096bytes, 13:8192
        #define ERASING_KEYWORD             0x5A    
    #endif        
#endif
*/




/*
*  ==== Audio === ==== Audio === ==== Audio === ==== Audio === ==== Audio === ==== Audio === ==== Audio === ==== Audio === 
*/
/*
*  Mic Mic Mic Mic Mic Mic Mic Mic Mic Mic Mic
*/
#define USE_MIC_ECHO_PARAM     //terry,2004/1/8 05:37PM

/*
*  WMA WMA WMA WMA WMA WMA WMA WMA WMA WMA WMA
*/
//nono add.5-5-16 14:26 because SUPPORT_AUD_WMA & SUPPORT_WMA can't be defined at the same time.
#if (defined(SUPPORT_AUD_WMA)||defined(SUPPORT_ASF))&&defined(SUPPORT_WMA)
#error "SUPPORT_AUD_WMA & SUPPORT_WMA can't be defined at the same time."
#endif

#if defined(SUPPORT_AUD_WMA)||defined(SUPPORT_ASF)
#undef SUPPORT_WMA
#endif

#ifdef SUPPORT_WMA
#undef SUPPORT_AUD_WMA
#undef SUPPORT_ASF
#endif

/*
*  DVD-Audio DVD-Audio DVD-Audio DVD-Audio 
*/

#ifdef DVD_AUDIO
#define ENLARGE_SDRAM_CS_AND_OSD_SIZE
#endif

/*
*  ==== Audio ending   ==== Audio ending   ==== Audio ending   ==== Audio ending   ==== Audio ending   ==== Audio ending   ==== Audio ending 
*/



/*
* ==== System ==== System ==== System ==== System ==== System ==== System ==== System ==== System ==== System ==== System ==== System
*/
#include "krnl_chk.inl"

#ifdef SDRAM_16Mb_Mode

    #ifdef  TURBO_DECODE
        #if (defined(SUPPORT_DVD_FULL_SUBTITLE) && defined(COMPRESS_ROM_CODE_040))
            #undef  USE_NAV_BUF //no nav buffer
        #else
            #define USE_NAV_BUF
            #define MOVE_NAV_BUF
        #endif  //#if !(defined(SUPPORT_DVD_FULL_SUBTITLE) && defined(COMPRESS_ROM_CODE_040))
    #else   //!TURBO_DECODE
        #define USE_NAV_BUF
        #define MOVE_NAV_BUF
        //#define USE_NAV_BUF_16M_DECREASE_SUBPICTURE
        #if !defined(USE_NAV_BUF_16M_DECREASE_SUBPICTURE)
            #define USE_NAV_BUF_16M
        #endif  //#if !defined(USE_NAV_BUF_16M_DECREASE_SUBPICTURE)
    #endif  //#ifdef  TURBO_DECODE

    #ifndef TURBO_DECODE     //kevinmonkey 050309 when TURBO DECODE,no L-memory, 2005/04/01 yltseng
        #define MOVE_PAL_AUDYA
    #endif
        
    #ifdef SUPPORT_SDRAM16M_AC3_5_1CH_OUTPUT//nono move here.4-9-9 15:35
        #undef ONLY_DOWNMIX   //terry,2005/3/30 11:50上午
        #undef TEMP_TWO_CHANNEL
        #undef TWO_CHANNEL_ONLY
        #if defined(IC_8202D)||defined(IC_8202L)
          #undef INTERNAL_AUDIO_DAC  // 8202D
        #endif
    #endif

    #undef AC3_BASS_MANAGEMENT//nono add.2006-5-24 1:05 Because SDRAM_16Mb_Mode we can't support it

#else
    #define USE_NAV_BUF
#endif


//moved to here for both 8200 and 8202
#define SHOW_SYSTEM_CLOCK	//20040708//JSLin

/*
*  Terry,2004/2/17 04:21PM
*  8202 define 
*/
#ifdef SPHE8202//terry,2004/1/28 02:18PM

    //#define USE_108MHZ//nono mark it 2006-5-3 19:08

    #ifdef SUPPORT_USB
      #if defined(IC_8202D)||defined(IC_8202L)
        #define USB_HOST_DRV     //USB Simply Host, 2005/1/17 08:05pm, wthsin
      #else // for 8202A/8202S
        #define HOST_UHCI        //wthsin add  2003/12/25 10:03
      #endif 
    #endif//SUPPORT_USB

    #ifdef  SUPPORT_MP4
        #ifndef SHARE_CDROM_CODE_WITH_SUP
            #define AVI_INTERNAL_SUP // To support internal subtitle of AVI (subpicture format)
        #endif
    #endif

    //move from cfg_xxx.h 2006-5-3 19:10
	#ifdef SUPPORT_QUICKTIME
	       #define SUPPORT_AAC
              #define SUPPORT_NERODIGITAL
              
              #ifdef SUPPORT_NERODIGITAL
              #define SUPPORT_FILE_CHAPTER
              #undef PAR_MP4_GUESS_43TV
              #define SUPPORT_NERODIGITAL_64MB
              #endif //SUPPORT_NERODIGITAL
	#endif // #ifdef SUPPORT_QUICKTIME

    #ifdef SUPPORT_DIVX6
        #define DIVX_DRM//nono add.2006-5-3 19:10
        #ifndef SUPPORT_FILE_CHAPTER
            #define SUPPORT_FILE_CHAPTER
        #endif  //#ifndef SUPPORT_FILE_CHAPTER
        #ifndef USE_IR_FILTER
            #define USE_IR_FILTER
        #endif  //#ifndef USE_IR_FILTER
    	#define FRAME_PRECISION_DECODE
    	#define DIVX6_SUP_ALIGNMENT
    	#define DIVX6_SW_SUBPIC_SCALING
        #if !defined(MP4_SHOW_PARSING_PROGRESS)&&!defined(ALCO_DVD_UI)//shenyj add 2006-9-7 08:52狟敁
            #define MP4_SHOW_PARSING_PROGRESS
        #endif  //#ifndef MP4_SHOW_PARSING_PROGRESS
        #define SUPPORT_DIVX6_64Mb
        //DIVX6_REDUCE_STACK_USAGE is added due to the fact that if USB is enabled and play divx6 on USB device,
        //stack may overflow while doing IR.if usb is off or stack overflow not happens, mark this is OK.
        #define DIVX6_REDUCE_STACK_USAGE	// this should be turned on all the time (stanley 2005/11/30)
        //#define DIVX6_USE_JPEGCD_BUF_AS_SUPIC_SCALING_BUFFER    //kevinmonkey when we do net have continuous memory space, 
                                                                //we had to steal space here and there
    #endif

    #if defined(SUPPORT_NERODIGITAL_64MB)&&defined(SUPPORT_DIVX6_64Mb)
    //if we got 64MB and bot nero digital and divx6 are enabled, we want to reduce code size by loading code to sdram.
        #define LOAD_MANY_CODE_TO_64M_SDRAM
    #endif  //defined(SUPPORT_QUICKTIME)&&defined(SUPPORT_DIVX6)
    
    #ifdef  DIVX_DRM
    
    #define SHOW_DRM_REGISTRATION_CODE_IN_SETUP//liumzh
    
    #if defined(SHOW_DRM_REGISTRATION_CODE_IN_SETUP) &&defined(SUPPORT_MP4)//terry,2005/6/20 10:07下午,avoid linking error
           #define DRM_CODE			//WSLEE for generate drm code 050615
    #else 
           #undef DRM_CODE			//terry,2005/6/20 10:20下午
    #endif
    
    #else 
           #undef DRM_CODE			//terry,2005/6/20 10:20下午
    #endif

    #ifdef SDRAM_16Mb_Mode  // 2004/09/06 yltseng
        #ifndef TURBO_DECODE    //terry,2005/4/5 04:34下午
            #undef AVI_INTERNAL_SUP   
        #endif
        #ifndef SUPPORT_MP4    
            #undef SUPPORT_MP4_SUBTITLE
        #endif
    #endif

    #ifdef SUPPORT_MP4_SUBTITLE  
        #define SUPPORT_OSDSRT      //suqiaoli add 2004-3-17,show srt title on OSD
        #define OSD_FONT_API
        // 2005/02/16 yltseng
    #endif

    #if defined(CARD_SETUP_TYPE_1)||defined(CARD_SETUP_TYPE_2)||defined(CARD_SETUP_TYPE_3)  
        #ifdef HDMI_SMC_CLE//for HDDVD Non CF config.chenzhao on 2004-12-1 21:27  
            #undef COMPACT_FLASH       //CF Card
        #else
            #define COMPACT_FLASH       //CF Card
        #endif//HDMI_SMC_CLE
        #define SD_MMC_CARD         //SD、MMC Card
        #define MEMORY_STICK        //MS、MS Pro Card
        #define SMART_MEDIA         //SMC、xD Card    
        //#define MOVE_NAND_DRIVER_TO_FS_KRNL //wthsin ,2004/9/15 10:56am 
    #elif defined(CARD_SETUP_TYPE_4)    /*256Pin 32bit Non_share mode 3-in-1 card*/
        #define SD_MMC_CARD         //SD、MMC Card
        #define MEMORY_STICK        //MS、MS Pro Card
    #elif defined(CARD_SETUP_TYPE_5)    /*256Pin 16bit  PMP project,Support HD and CF */
        #define COMPACT_FLASH       //CF Card interface    
    #endif   

    //move out for both 8200and 8202//20040708//JSLIN
    //#define SHOW_SYSTEM_CLOCK//4-4-8 1:39

    //#define IC_8202_B//move from cfg_customers.h 4-6-18 23:41//nono mark it.no use5-3-14 16:27

    #ifndef DTS_CD_OUT_RAW_A
        #define DTS_CD_OUT_RAW_A
    #endif
  
    #if defined(NO_DTS_OUTPUT)&&!defined(FORCE_NO_DTS_OUTPUT)//nono 4-5-5 14:46
        #undef DTS_CD_OUT_RAW_A
    #endif//NO_DTS_OUTPUT
  
    #undef PREAMP_GPIO_ENABLE//terry,2004/2/3 12:00PM

    #ifndef USE_8_CH_DAC            
        #undef DACOUTLm
        #undef DACOUTRm
        #undef DACOUT0L
        #undef DACOUT0R
        #undef DACOUT1L
        #undef DACOUT1R
        #undef DACOUT2L
        #undef DACOUT2R
    
        #define DACOUTLm        6
        #define DACOUTRm        7
        #define DACOUT0L        0
        #define DACOUT0R        1
        #define DACOUT1L        2
        #define DACOUT1R        3
        #define DACOUT2L        4
        #define DACOUT2R        5
        #define LmRm_CFG        0 //0 means Lm/Rm output downmix, 1 means Lm/Rm output the same with L/R
        #define DTS_94_24_CFG   0
    #endif        
  
#else //#ifdef SPHE8202
  #define LmRm_CFG        1  
#endif

#endif//#ifndef _CUST_DEF_H_

// mimitsai merge from dp2070/dp3240
#ifdef EASTECH_DVD_DP2070_D
    #define SUPPORT_NTSC
    #define SUPPORT_PAL
    //#define SUPPORT_NTSC
    //#define SUPPORT_PAL60
    //#define SUPPORT_PALM
    //#define SUPPORT_PALN
    //#define SUPPORT_PALNc
#elif 0//nono mark it!!!!!!!!!20060318
    #define SUPPORT_NTSC
    #define SUPPORT_PAL
    //#define SUPPORT_NTSC
    #define SUPPORT_PAL60
    //#define SUPPORT_PALM
    //#define SUPPORT_PALN
    //#define SUPPORT_PALNc
#endif    

//==============================
//Smart upgrade related function (ERASE_CHIP is defaulted)  joshua 04-7-20
//==============================

#if defined(IC_8202L) //terry,2006/4/7 06:29下午    
    #define SUPPORT_SPI_FLASH
    #undef  SUPPORT_PARALLEL_FLASH
#endif

#if !defined(IC_8202L)&&!defined(IC_8202D) //nono add.2006-9-19 18:28 
    #define SUPPORT_PARALLEL_FLASH
    #undef SUPPORT_SPI_FLASH
#endif

/*
*  --  standby mode --  --  standby mode --  --  standby mode --
*/
#define AWAKE_SLOWDOWN


/*
*  --  Font library( for backward compatibility ) --  --  Font library( for backward compatibility ) --
*/
#if ( defined( SUPPORT_CHINESE_FONT ) || defined( USE_RUSSIAN_LANGUAGE ) || \
      defined( EUROPE_FOREIGN_LANGUAGES ) || defined( MIDDLE_EUROPE_LANGUAGES ) || \
      defined( USE_CYRILLIC_FONT ) || defined( SUPPORT_TURKISH_LANGUAGES ) || \
      defined( USE_JAPANESE_FONT ) || defined( USE_KOREAN_FONT ) || defined( USE_WINDOWS_CODEPAGE_1250 ) )

    #define SUPPORT_FONT_UTIL

    #ifdef SUPPORT_CHINESE_FONT
        #define SUPPORT_FONT_CP_950_COMMON       
        //#define SUPPORT_FONT_CP_936_COMMON
    #endif

    #ifdef EUROPE_FOREIGN_LANGUAGES
        #define SUPPORT_FONT_ISO_8859_1
    #endif

    #ifdef MIDDLE_EUROPE_LANGUAGES
        #define SUPPORT_FONT_ISO_8859_2
    #endif

    #if defined( USE_CYRILLIC_FONT ) || defined( USE_RUSSIAN_LANGUAGE )
        #define SUPPORT_FONT_ISO_8859_5
    #endif

    #ifdef SUPPORT_TURKISH_LANGUAGES
        #define SUPPORT_FONT_ISO_8859_9
    #endif

    #ifdef USE_JAPANESE_FONT
        #define SUPPORT_FONT_CP_932
    #endif

    #ifdef USE_KOREAN_FONT
        #define SUPPORT_FONT_CP_949_COMMON
    #endif

    #ifdef USE_WINDOWS_CODEPAGE_1250
        #define SUPPORT_FONT_CP_1250
    #endif
#endif


//-------------------------------------- ending --------------------------------------



