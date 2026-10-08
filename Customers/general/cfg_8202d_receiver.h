#define SUPPORT_RECEIVER

#ifdef SUPPORT_RECEIVER

//#undef  SDRAM_BUS_32BITS

//#undef MP_BOARD_216_PIN_NON_SHARE
//#define MP_BOARD_256_PIN_NON_SHARE     //mass-production board 256 pin NON SHARE MODE

#define ENLARGE_SDRAM_CS_AND_OSD_SIZE

//----------------------------------------------------------------------//
// SERVO def    hongfeng 2005/5/31
//----------------------------------------------------------------------//
#undef  SA2SA0_STD
#define SA0SA0_STD
//****END****END****END****END****END****END****END****END****END****//

//#undef NO_DTS_OUTPUT

//#undef TWO_CHANNEL_ONLY
#undef TEMP_TWO_CHANNEL          //define it to output two channel audio only, mark it for 5.1 channel, Jeff 20020819
#undef ONLY_DOWNMIX

//----------------------------------------------------------------------//
// receiver state def   hongfeng 2005/5/31
//----------------------------------------------------------------------//
#define NUM_MODES_MAX 6
 #define SUPPORT_DVD_PLAYER
 #define SUPPORT_AV_IN
 //#define SUPPORT_SPDIF_IN
 //#define SUPPORT_SECOND_AV_IN       // Support 2nd AV input
 #define SUPPORT_AVIN_FUNCTION//xyy 2003-12-6 13:04
 //#define SUPPORT_VIDEO_WITH_SPDIF   // Support video in + SPDIF in at the same time
 #define RECEIVER_USE_PSCAN_BUTTON  // Use P-Scan button to change modes
/*  Digital input processing */
 #ifdef SUPPORT_SPDIF_IN
  #define SUPPORT_SPDIF_96
  #define SUPPORT_SPDIF_AC3
  #ifndef NO_DTS_OUTPUT
  #define SUPPORT_SPDIF_DTS
  #endif//#ifndef NO_DTS_OUTPUT
  #define SUPPORT_SPDIF_PLII
  #define SUPPORT_SPDIF_SFX
 #endif
 #define SUPPORT_RECEIVER_MODE_MEMORY //chenzhao 20050622
 //****END****END****END****END****END****END****END****END****END****//

 
//----------------------------------------------------------------------//
// IR IR IR IR IR IR IR IR IR IR IR IR IR    hongfeng 2005/5/31
//----------------------------------------------------------------------//
//#undef  IR44
//#define IR120 
//#define IR202	//receiver new ir remote hongfeng 2005-03-08
//#define IR_OP_rcvr

//****END****END****END****END****END****END****END****END****END****//

//----------------------------------------------------------------------//
// AUDIO_MUTE & Headphone & MIC    hongfeng 2005/5/31
//----------------------------------------------------------------------//
#undef USE_AUD4_AS_GPIO_MUTE
#define USE_AUD3_AS_GPIO_MUTE

#define NO_MIC
//#define USE_AMP_MUTE
//#define UNMUTE_LINE_OUT
#define PORTABLE_POWER_ON_MUTE

//#define SUPPORT_HEADPHONE
#ifdef SUPPORT_HEADPHONE
    #define USE_GPIO32_AS_HEADPHONE_SENSE
    #ifdef USE_GPIO32_AS_HEADPHONE_SENSE
    #define HEADPHONE_SENSE 32
    #endif
#endif
//****END****END****END****END****END****END****END****END****END****//


//----------------------------------------------------------------------//
// SETUPMENU TYPE   SETUPMENU TYPE    hongfeng 2005/5/31
//----------------------------------------------------------------------//
#ifdef SETUP_COLOR_TYPE2
//#undef SETUP_COLOR_TYPE2
//#define SETUP_COLOR_TYPE1
#endif

//#define NO_MIC_ITEM_ENABLE_MIC

//#define NO_KARAOK_SETTING_IN_SETUP

//#define SUPPORT_TESTSPK

//#define SUPPORT_RECEIVER_TEST //2005/05/11 chenzhao

#ifdef SUPPORT_RECEIVER_TEST
    #if defined(AC3_BASS_MANAGEMENT) && defined(DVD_SETUP_REENG)
    #define SPEAKER_CONFIG
    #endif//AC3_BASS_MANAGEMENT

    #ifdef SPEAKER_CONFIG
    #define TEST_BASS_MANAGEMENT    //2004AUDDRV oliver testing
    #define TEST_BASS_COMMAND       //2004AUDDRV oliver testing
	//#define FIX_2_1_SPEAKER_CONFIG //chenzhao20050707
    #endif //SPEAKER_CONFIG
     
    #define SUPPORT_PROLOGIC_II
    #if defined( SUPPORT_PROLOGIC_II)&& defined(DVD_SETUP_REENG)
    #define SUPPORT_PROLOGIC_II_ADVANCE_SETTING
    #endif
    
    #ifdef DVD_SETUP_REENG
    #define USE_SETUP_ITEM_ENABLE_FLAG //added by by chenzhao on 2005-3-31 16:4  
    #define HIDE_DISNABLE_ITEM //added by by chenzhao on 2005-3-31 16:4  
    #endif
#endif//#ifdef SUPPORT_RECEIVER_TEST

//****END****END****END****END****END****END****END****END****END****//

#define DVI_I2C_SET

//----------------------------------------------------------------------//
// APOGEE POWER AMP    hongfeng 2005/5/31
//----------------------------------------------------------------------//  

#define SUPPORT_APOGEE_AMP     
#ifdef SUPPORT_APOGEE_AMP
//select chip type here huziqin
//#define SUPPORT_DDX8000  
//#define SUPPORT_DDX8228
#define SUPPORT_DDX8001 

//support bass and treble adjust xyy 2004-3-8 9:49 
//#define SUPPORT_BASS_TREBLE

//support 7 mode eq, which is realised on amplifier xyy 2004-3-8 9:52 
//#define AMP_SUPPORT_EQ

//support reverberation(for temporary using) xyy 2004-3-8 10:32
//#define SUPPORT_REVERBERATION

//#define SUPPORT_SAVE_AMPLIFIER_STATUS

//#define AMPVOL_VFD_DISP//xyy 2004-1-2 10:16
#endif     
//****END****END****END****END****END****END****END****END****END****//


//----------------------------------------------------------------------//
// TI POWER AMP    hongfeng 2005/5/31
//----------------------------------------------------------------------//  
//#define TAS_5026_PWM
//#define TAS_5508_PWM
#ifdef TAS_5508_PWM
#define DVI_I2C_SET
#define I2C_PAGE_MODE
//#define SUPPORT_BASS_TREBLE
//#define AMP_SUPPORT_EQ
#endif
//****END****END****END****END****END****END****END****END****END****//



//----------------------------------------------------------------------//
// PUBLIC POWER AMP SETTING    hongfeng 2005/5/31
//----------------------------------------------------------------------//  
#define NO_INTERNAL_VOLUME_CTRL
#define  DOLBY_AMP_VOLUME_CTRL
#if defined(DOLBY_AMP_VOLUME_CTRL)
#ifdef TAS_5508_PWM
/*set default volumb 0--15*/
    #define MAIN_VOL_MAX   40 //MAIN_VOL_MAX <->0dB
    #define MAIN_VOL    30  
    #define LINE_OUT_VOL 37  /*line out use channel 7,8*/
    
    #define CH_VOL_MAX  20 // -10 dB->+10dB
    #define CH1_VOL     10  //0dB
    #define CH2_VOL     10
    #define CH3_VOL     10
    #define CH4_VOL     10
    #define CH5_VOL     10
    #define CH6_VOL     10
    #ifdef SUPPORT_BASS_TREBLE
    #define CH_BASS_VOL     10
    #define CH_TREBEL_VOL   10
    #endif
#else//#ifdef TAS_5508_PWM
/*set default volumb 0--15*/
#define MAIN_VOL  15  // 0-> 80dB
#define CH1_VOL    10  // -10 dB->+10dB
#define CH2_VOL    10
#define CH3_VOL    10
#define CH4_VOL    10
#define CH5_VOL    10
#define CH6_VOL    10
#define MAIN_VOL_MAX   40
#define CH_VOL_MAX   20
#define LINE_OUT_VOL 37  /*line out use channel 7,8 huziqin*/
#endif//#ifdef TAS_5508_PWM
#endif //dolby
//#define  SAVE_AMP_VOLUME
//#define  SHOW_VOL_ON_VFD
//****END****END****END****END****END****END****END****END****END****//


//----------------------------------------------------------------------//
// TUNER & RDS    hongfeng 2005/5/31
//----------------------------------------------------------------------//  
#define SUPPORT_RDS_FUNCTION//xyy 2003-12-4 15:47
//#define SUPPORT_SAA6588
#define SUPPORT_BA1924

#define ENABLE_TIMER1_PROCESS_RDS   //hongfeng modify 2005-05-17
#define RADIO_2006

//RDS len, don't change them
#define programServiceBuf_len 9 //hongfeng 2005-02-23
#define programTypeNameBuf_len 9    //hongfeng 2005-02-23
#define programTypeBuf_len 17   //hongfeng 2005-02-23
#define clocktimeBuf_len 26 //hongfeng 2005-02-23

//#define VFD_DISPLAY_RDS     //hongfeng 2005-02-23
    #ifdef VFD_DISPLAY_RDS
        #define display_speed  4       //the larger the slower hongfeng 2005-02-23 
        #define VFDlen 9    //VFD len hongfeng 2005-03-02
    #endif
    
//#define SUPPORT_TUNER_MV114//if define it,the system can't work,wangfeng 2003-12-10 10:06
#define STOP_LOADER

//#define SUPPORT_Radio_NEW_UI
//****END****END****END****END****END****END****END****END****END****//


//----------------------------------------------------------------------//
// SUPPORT_8202_EXT_ADC    hongfeng 2005/5/31
//----------------------------------------------------------------------//  
//#define SUPPORT_8202D_EXT_ADC   // benson 2004/8/17 01:01¤U¤È
#ifdef  SUPPORT_8202D_EXT_ADC
#undef  ADC_CONFIG_MODE
#define ADC_CONFIG_MODE     8
//#define ADC_EXT_RESET //for cs5340 etc.
#endif
//****END****END****END****END****END****END****END****END****END****//



/*
define audio and video switch GPIO
*/
//xyy 2004-3-23
#define AUIN_SL0   18 //use GPIO 18 as audio select 0 
#define AUIN_SL1   52  //use GPIO 52 as audio select 1 
#define VIDEO_SL0  51  //use GPIO 51 as video select 0 
#define VIDEO_SL1  50  //use GPIO 50 as video select 1 



//----------------------------------------------------------------------//
// PROLOGIC_II    hongfeng 2005/5/31
//----------------------------------------------------------------------// 
#ifdef SUPPORT_PROLOGIC_II
#define  USE_PROLOGIC_II_KEY
#define USE_PROLOGIC_II_KEY_FOR_SURROUND
    #ifdef USE_PROLOGIC_II_KEY_FOR_SURROUND
    //#define USE_PL2_3DSURROUND_KEY
        #ifdef SPEAKER_CONFIG
        #define USE_PL2_KEY_SWITCH_SPEAKER
        #endif
    #endif
#define SUPPORT_PRO_LOGIC_IN_RECEIVRR_MODE
#endif
//****END****END****END****END****END****END****END****END****END****//


//----------------------------------------------------------------------//
// IO_EXTENT    hongfeng 2005/5/31
//----------------------------------------------------------------------//  
//#define HC4094 //shift register huziqin 2004-2-23 
//#define HC165  //shift input huziqin 2004-8-5
//#define PT2258  //volumb control ;huziqin 2004-2-23
//#define TDA7448  //volumb control ;huziqin 2004-4-8
#define ROM_BUS_EXTENT_IO
//****END****END****END****END****END****END****END****END****END****//


//----------------------------------------------------------------------//
// SPHE8202_CARD_STORAGE    hongfeng 2005/5/31
//----------------------------------------------------------------------//  
    //#define  SPHE8202_CARD_STORAGE  //wthsin,    2004/2/23 10:49am 
    #ifdef SPHE8202_CARD_STORAGE      //wthsin,    2004/3/1  11:08am 
        //#define CARD_SETUP_TYPE_1   //Three card Bus Demo 
        //#define CARD_SETUP_TYPE_2     //Share One card Bus(EASTECH)
        #define CARD_SETUP_TYPE_3   //256Pin 16bit Non_share mode All card.
        //#define CARD_SETUP_TYPE_4   //256Pin 32bit Non_share mode 3-in-1 card

    #endif  
    
    //#define SUPPORT_USB
//****END****END****END****END****END****END****END****END****END****//

    
    //#define DVD_AUDIO
    
    //#define SUPPORT_RECEIVER_EQ
    //#define SUPPORT_RECEIVER_3D
    //#define SUPPORT_MULTI_CHANNEL_5_BAND_EQ             //support 5.1 EQ ,chenzhao 20050802

    #define SUPPORT_BOOK

#endif //support receiver

