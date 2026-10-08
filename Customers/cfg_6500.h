/*benosn 2005-07-08  merge HD DVD code*/
/* helm modified code, 051222*/

/*nono move to cfg_xxx.h
#undef MP_BOARD_216_PIN_NON_SHARE     
#define MP_BOARD_256_PIN_NON_SHARE      
//#undef  INTERNAL_AUDIO_DAC 
#define MUTE_PULL_HIGH
*/


#undef ROM_TACC_DEFAULT          //helm for performance issue, 051014
#define ROM_TACC_DEFAULT    70


#define DIP_CFG_ENABLE		      //wsf add 2005-11-7 14:01

#define SUPPORT_HD_DVD

#define SCALER_6500  //helm mark this and remove it to cfg_customer_8202d.h//nono open it.5-12-24 4:19
//#define DAC_6500D  //eric lin,2006-07-06,6500 verD support video DAC 
#ifdef SUPPORT_HD_DVD
//#undef DVD_SETUP_REENG
//#undef SDRAM_BUS_32BITS

//nono mark it.5-12-26 14:05 Need to refer the cfg_xxx.h
//#undef DEFAULT_OSD_LANG
//#define DEFAULT_OSD_LANG 1 /*chinese*/

#define DIGITAL_VIDEO_OUT //Must Mask #define SDRAM_BUS_32BITS to use 16 bits SDRAM width
#ifdef DIGITAL_VIDEO_OUT
	#ifdef MP_BOARD_256_PIN_NON_SHARE
		#define CCIR656_TYPE1		//helm for 6500B CCIR656 Out from Pin164~173 (8202D 256pin)  
	#else 
		#define CCIR656_TYPE2		//ronnie for 6500C CCIR656 Out from Pin144~153 (8202D 216pin)
	#endif
#endif

//=======select input audio format=============//

#define SUPPORT_6500_SPDIF_INPUT  //hongfeng 2006/4/6 9:31
//#define SUPPORT_6500_I2S_INPUT  //hongfeng 2006/4/6 9:31


//#define DVI_AUDIO_MUTE    //tjf audio mute i/o is gpio37 2004-4-26 
#define DVI_I2C_SET       //tjf I2C set for dvi311 2004-4-26 11:44
#define RESET_TO_DVI311   //tjf gpio 40 use to reset dvi311

//#define HDCP_CUSTOM //Don't open for release code.chenzhao 2005-3-8
#if 1//def HDCP_CUSTOM//chenzhao on 2005-3-7 17:47  
    #define HDCP_ON     0
    #define HDCP_OFF    1
#endif


/*==========================================================================*/
#define Mode_576I               9
#define Mode_1080P              8
#define Mode_VGA     		7
#define Mode_SVGA   		6
#define Mode_XGA     		5
#define Mode_SXGA		4
#define Mode_480P		3
#define Mode_576P		2
#define Mode_720P60		1
#define Mode_720P50		1
#define Mode_1080i		0
/*=========================================================================*/

//====================kevin add for HDMI with HDCP==============
#define   HDMI
//#define HDMI_SMC_CLE // benson add for SMC_CLE control in hdmi project
//#define NEW_HDDVD_GPIO//add for new hddvd gpio config.chenzhao on 2004-12-14 16:8  
//#define NEW_HDMI_FLOW //for use new HDMI Flow,added by chenzhao on 2005-2-25 15:40  
//#define NO_311_ANALOG_OUTPUT //chenzhao on 2005-3-3 13:32  

//=====================================================

#endif  //SUPPORT_HD_DVD

#if defined(NEW_MP3_GUI)&&!defined(INDIGO_STYLE_FSGUI)
#define MP3_LARGE_GUI
#endif

#ifdef MP3_LARGE_GUI
#undef DIR_SCROLL_BAR
#endif

//#define SCART_TV_6500_USE_PIN110_111_112  //caoh 2006-7-4 02:24下午 move from cfg
#ifdef SCART_TV_6500_USE_PIN110_111_112
    #define USE_6500_HI_CTRL_SCART_TO_RGB
    //#define LOW_CTRL_SCART_TO_RGB
    //#define HI_CTRL_TO_RELEASE_SCART
    #define USE_6500_HI_CTRL_TO_RELEASE_SCART
    //#define USE_6500_LOW_CTRL_TO_RELEASE_SCART
    #define USE_6500_HI_CTRL_SCART_TO_DISPLAY_16B9
    //#define LOW_CTRL_SCART_TO_DISPLAY_16B9
#endif

#ifndef SDRAM_BUS_32BITS  //caoh 2006-7-8 03:56下午  only for 16bit mode I2C
#define HDMI_16_BIT_256PIN_BOARD
#endif

//#define HDDAC_USE_HALF_SWING   //caoh 2006-7-11 02:03下午  HDDAC use which current 
//#define HDDAC_USE_FULL_SWING
//#define HDDAC_USE_QUART_SWING

//#define TV_WANT_6500_AUDIO_MUTE   //caoh 2006-7-11 02:59下午 only for some tv don't mute RAW and DTS audio


