
//added by JS	//for setup reengineering	//20040810

#define C_UNLOCK    1
#define C_LOCK      0

//frank.huang 050801
#ifdef GPS_DVD
#define MAX_MENU_VA		9
#define MAX_SETUP_VA	64 + MAX_MENU_VA
#else

  #ifdef SUPPORT_HD_RESOLUTION
#define MAX_SETUP_VA	74
  #else
#define MAX_SETUP_VA	64
  #endif

#endif

UINT8 setup_VA[MAX_SETUP_VA];

#ifdef SUPPORT_HD_RESOLUTION    // HD items of setup menu must use setup_VA_EN[],so support HD also must 
                                                     // support setup_VA_EN[] .
#ifndef USE_SETUP_ITEM_ENABLE_FLAG
#error "If open #define SUPPORT_HD_RESOLUTION, must also open #define USE_SETUP_ITEM_ENABLE_FLAG."
#endif
#endif

#ifdef USE_SETUP_ITEM_ENABLE_FLAG//added by chenzhao on 2005-3-31 16:6  
UINT8 setup_VA_EN[MAX_SETUP_VA];
#endif

#define SETUP_VA_NONE				0xff

#define SETUP_VA_TV_SYS				0x00
#define SETUP_VA_SSAVER				0x01
//#define SETUP_VA_VIDEO				0x02
#define SETUP_VA_TV_RATIO			0x03
#define SETUP_VA_PASSWORD			0x04
#define SETUP_VA_RATING				0x05
#define SETUP_VA_DEFAULT			0x06

#define SETUP_VA_OSD_LANG			0x07
#define SETUP_VA_AUDIO_LANG			0x08
#define SETUP_VA_SUBTITLE_LAN		0x09
#define SETUP_VA_MENU_LANG			0x0a

#define SETUP_VA_AUD_OUT			0x0b
#define SETUP_VA_MIC_ONOFF			0x0c
#define SETUP_VA_ECHO				0x0d
#define SETUP_VA_MIC_VOL			0x0e
#define SETUP_VA_KEY				0x0f
#define SETUP_VA_FREQ_MASK			0x10

#define SETUP_VA_BRIGHTNESS			0x11
#define SETUP_VA_CONTRAST			0x12
#define SETUP_VA_HUE				0x13
#define SETUP_VA_SATURATION			0x14

#define SETUP_VA_DOWNMIX			0x15
#define SETUP_VA_SUBWOOFER			0x16
#define SETUP_VA_BASE_MODE			0x17
#define SETUP_VA_CSPK_DELAY			0x18
#define SETUP_VA_SSPK_DELAY			0x19

#define SETUP_VA_DOLBY_OP			0x1a
#define SETUP_VA_DYNAMCRANGE		0x1b
#define SETUP_VA_DUAL_MONO			0x1c

#define SETUP_VA_REGION_CODE		0x1d


//for MIC_2CHANNEL
#define SETUP_VA_MIC_VOL_1			0x1e	//corresponding to STR_OS_MIC_VOL_1
#define SETUP_VA_MIC_VOL_2			0x1f	//corresponding to STR_OS_MIC_VOL_2

//for DYNAMIC_SPECTRUM
#define SETUP_VA_BAND				0x20	//corresponding to STR_OS_BAND

//for USER_MPEG_LOGO
#define	SETUP_VA_SELECT_LOGO		0x21	//corresponding to STR_OS_SELECT_LOGO

// for SUPPORT_PROLOGIC_II
#define SETUP_VA_PROLOGIC			0x22	//corresponding to STR_OS_PROLOGIC

//for CORTROL_VCD_ONF
#define SETUP_VA_VCD				0x23	//corresponding to STR_OS_VCD

#define SETUP_VA_DTS_DIGITAL		0x24 	//corresponding to STR_OS_DTS_DIGITAL
#define SETUP_VA_AC3_DIGITAL		0x25	//corresponding to STR_OS_AC3_DIGITAL

//for SPEAKER_CONFIG
#define SETUP_VA_FSPK				0x26	//corresponding to STR_OS_FSPK	
#define SETUP_VA_CSPK				0x27	//corresponding to STR_OS_CSPK
#define SETUP_VA_SSPK				0x28	//corresponding to STR_OS_SSPK

//for SELECT_MEDIA_IN_SETUPMENU
#define SETUP_VA_MEDIA_TYPE		0x29	//corresponding to STR_OS_MEDIA_TYPE				

//for CLOSE CAPTION CONTROL
#define SETUP_VA_CC                 0x2a    //corresponding to STR_OS_CLOSED_CAPTION

//for Angle mark control
#define SETUP_VA_ANGLE              0x2b    //corresponding to STR_OS_ANGLE_MARK

//for address 0x02 make error value when reload
#define SETUP_VA_VIDEO				0x2c

//for hddvd 
#define SETUP_VA_SPV311MODE         0x2d
#define SETUP_VA_HDCP               0x2e

//for 8282D sharpness
#define SETUP_VA_SHARPNESS      0x2f

#ifdef MCU51_PANNEL//2005-5-12 10:14 zhoulin  sending message to MCU for reseting default settings
  #define SET_VA_DEFAULT         0x31
#elif defined(ADJUST_JPEG_SLIDE_TIME)  //lyc add 2005-8-12
   #define SET_VA_TIME    0x31
#endif

// for TVG      // 2005/03/29 yltseng
#ifdef SUPPORT_TVG
    #define SETUP_VA_TVG_MODE                   0x30
    #define SETUP_VA_TVG_WORD_SET_HELLDAMM      0x31
    #define SETUP_VA_TVG_WORD_SET_RELIGIOUS     0x32
    #define SETUP_VA_TVG_WORD_SET_SEXUAL        0x33
    #define SETUP_VA_TVG_CC_OPERATION           0x34
    #define SETUP_VA_TVG_CC_CHANNEL             0x35
#endif

#define SETUP_VA_RESUME		0x36	//zxb for SAME_DISC_RESUME

#ifdef SUPPORT_LAST_MEMERY
#define SETUP_VA_MEMORY             0x37 //corresponding to STR_OS_MEMORY
#else   //else => #ifdef SUPPORT_LAST_MEMERY
// for SUPPORT_PROLOGIC_II
#define SETUP_VA_PL_PANORAMA       0x37	//corresponding to STR_OS_PL_PANORAMA
#endif  //end => #ifdef SUPPORT_LAST_MEMERY
 
// for SUPPORT_PROLOGIC_II
#define SETUP_VA_PL_CENTER_WIDTH    0x38	//corresponding to STR_OS_PL_CENTER_WIDTH
 
// for SUPPORT_PROLOGIC_II
#define SETUP_VA_PL_DIMENSION       0x39	//corresponding to STR_OS_PL_DIMENSION

#define SETUP_VA_JPG       0x3a//LIBING 2005-6-9 10:41

#define SETUP_VA_SERVO_DBG      0x3b        //joshua, 20050711, modified for servo-debug function on OSD


#ifdef USE_SETUP_SELECT_FONT
#define SETUP_VA_DIVX_FONT_CODE 0x3c
#endif

#define SETUP_VA_DE_INTERLACE   0X3d//nono 20050924

#ifdef AUTO_LOAD_MODE_SETUP  //DENGHG ADD FOR PHILIPS 2005-11-15 05:01     
#define SETUP_VA_MODE_ID            0x3e 
#define updateromFlagAdr 98 //updateromFlagAdr£¬updateromFlagAdr+1 are 0x9a78£¡£¡update rom.bin flag2005-11-16 08:42        
#endif  

/*
#define SETUP_VA_TV_SIG            0x3a

#define SETUP_VA_AUTO_SEA       0x3b

#define SETUP_VA_FINE_TUN        0x3c

#define SETUP_VA_FAVOR              0x3d

#define SETUP_VA_CHANNEL          0x3e
*/

#ifdef GPS_DVD
#define MENU_VA_BUZZ				0x40
#define MENU_VA_BR_AUTO 			0x41
#define MENU_VA_FM_POWER 	 		0x42
#define MENU_VA_FM_FREQ_H			0x43
#define MENU_VA_FM_FREQ_L			0x44
#define MENU_VA_AUD_VOL				0x45
#define	MENU_VA_BRIGHTNESS			0x46
#define	MENU_VA_CONTRAST			0x47
#define	MENU_VA_TV_RATIO			0x48
#endif

#ifdef SUPPORT_HD_RESOLUTION
#define SETUP_VA_HD         0x49 
#endif


