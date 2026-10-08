/*
** Notes:
** 1.Split from cfg_xxx.h for general use on 06/02/06 by Jack.
** 2.Please put all general DVB define in this file,thanks for your kindly support.
** 3.This file is included in cust_def.h.
*/

//=========== Important Define Start =========== Important Define Start =========== Important Define Start ===========//
#ifdef  DVB_DVD_8202

    /************************** Tuner I2C Control Start **************************/
    //#define Tuner_8202_I2C
    #define Tuner_6600_I2C  
    /************************** Tuner I2C Control End **************************/
    
    /************************** Transport Steam Interface Start *********************/
    //#define DeMux_SDIF
    #define DeMux_TSIF  
    
    /**sunif setting*/
    #define SUNIF_TYPE_1     //PIN165~172
    //#define SUNIF_TYPE_2   //PIN225~231
    
    #ifdef CARD_SETUP_TYPE_3   ////////yanglli add for card 6in1
    #define CARD_SENSE3_USE_GPIO38
    #undef SUNIF_TYPE_1
    #define SUNIF_TYPE_2   ////PIN225~231
    #define CARD_6IN1_DVB_I2C
    #endif
    
    //#define INVERSE_TS_CLK
    //#define SUNIF_36M    //36M
    #define SUNIF_22M    //22.5M
    
    #define RESET_SUNIF_WHEN_ERROR
    /************************** Transport Steam Interface End *********************/
    
    /************************* Front End Info Start ***************************/
    /*TPS information show*/
    #if defined(TUNER_DNOS204ZH102A_NIM)||defined(TUNER_DNOS204ZH103A_NIM) \
      ||defined(TUNER_SAM0ZAR1_HALFNIM)||defined(TUNER_LG0ZAR1_HALFNIM)	   \
      ||defined(TUNER_DNOS404PH104A_NIM)||defined(TUNER_MDVBT_7K8_NIM)\
      ||defined(TUNER_PH1ZAR1_HALFNIM)
    #define TPS_DETAIL_INFORMATION//xiaopeng 2005/09/27
    #endif
    //#define BER_TEST_INFO//xiaopeng 2005/11/10
    /************************* Front End Info End ***************************/
    
    /************************* System Architecture Start ***************************/
    #define SUPPORT_8202_DVB
    #define SUPPORT_DVB
    
    #ifdef SUPPORT_8202_DVB
    #define DVB_T
    #endif
    /************************* System Architecture End ***************************/

    /************************ Test Start *************************/
    // ================================================
    //#define VPPISSUE_TEST
    // ================================================
    /************************ Test End *************************/
    
#endif //#define DVB_DVD_8202  
//=========== Important Define End =========== Important Define End =========== Important Define End ===========//

//=========== antenna control start=================//xiaopeng 2006/08/09
#define SUPPORT_ANTENNA_POWER_CONTROL
#ifdef SUPPORT_ANTENNA_POWER_CONTROL
	#define SENSOR_ANT_POWER_8202_PIN       40
#endif

//=========== antenna control end=================

//=========== DataBase Start =========== DataBase Start =========== DataBase Start ===========//
#define SUPPORT_NEWDB //Yvonne 05042005
#ifdef SUPPORT_NEWDB//Yvonne_051805
    //#define ONLY_FLASH_STORE_INFO
    #ifdef EEPROM_FLASH_STORE_INFO
    //#define STORE_INFO_IMMEDIATELY
    #endif
#endif //end #ifdef SUPPORT_NEWDB
//=========== DataBase End =========== DataBase End =========== DataBase End ===========//


//=========== EPG Start =========== EPG Start =========== EPG Start ===========//
#ifdef SUPPORT_EPG
    //#define CLOSE_EPG_FILTER  //wangcj 2005-11-4 9:32 for not use the filter for eit table
	#define EPG_WITHOUT_FILTER //sunzhh add 20060516
    #define RADIO_HAS_NO_EPG //Just as the name.Jack added 05/12/30
    #define VIDEO_AJUST_TV           //sunzhh add for EPG UI adjusting TV
    #define CHECK_SCRAMBLED_BY_CA_DESC	//JennyLee 09302005: check scrambled channel by PMT CA_descriptor//Jack 06/03/01 porting from 1000
    #define DEMUX_PASS_SCRAMBLED_PROG   //Jack added 06/03/01
	#define EPG_INFO_SCROLL
	#ifdef EPG_INFO_SCROLL
	#define ENLARGE_STATCK_SIZE
	#endif
#endif
//=========== EPG End =========== EPG End =========== EPG End ===========//


//=========== TTX Start =========== TTX Start =========== TTX Start ===========//
#ifdef SUPPORT_TELETEXT
	#define RADIO_HAS_NO_TTX 				//tcf added 2006-4-14 04:11下午
    #define TRANSPARENCY_LEVEL_TTX  0xf0 	//tcf added 2005-11-17 20:04
    #define TTX_STATE_MACHINE	 			//tcf added 2006-3-29 08:41下午
    #define TTX_ENHANCED				    //tcf added 2006-3-29 01:46下午
    
    #ifdef TTX_ENHANCED
    #define TTX_CACHE_NEW					//tcf added 2006-4-5 04:34下午 new cache method
    #define TTX_4CKEY						//tcf added 2006-4-14 02:05下午 4color key function
    #define TTX_LIMIT_FEATURE				//tcf added 2006-4-15 10:45上午 limit ttx function at some state
    #define TTX_UPDOWN_SEARCH_IN_CACHE		//tcf added 2006-9-12 10:36上午
    #endif
    
    #define TTX_TIME_NEW					//tcf added 2006-4-17 10:33上午
    #define TTX_MULTI_BG					//tcf added 2006-4-18 11:36上午 use ir(repeat) change the ttx bg
    #define TTX_TIMEOUT_FUNC				//tcf added 2006-5-15 01:20下午 add ttx timeout function(dvb_ttx.c)

    //#define SUPPORT_SOFT_HW_TTX   //yangli add HW_TTX 2006-10-10 13:40,
    #ifdef SUPPORT_SOFT_HW_TTX
    #define HWTTX_USE_BUFFER_POOL_WHEN_SOFTTTXON//when soft ttx on,hw ttx use buffer pool
    #endif
#endif
//=========== TTX End =========== TTX End =========== TTX End ===========//


//=========== Subtitle Start =========== Subtitle Start =========== Subtitle Start ===========//
#ifdef SUPPORT_SUBTITLE
    #define RADIO_HAS_NO_SUBTITLE
#endif
//=========== Subtitle End =========== Subtitle End =========== Subtitle End ===========//


//=========== DVB Game Start =========== DVB Game Start =========== DVB Game Start ===========//
#ifdef SUPPORT_DVB_NATIVE_GAME
    #define SUPPORT_GAME_BOXMAN
    #define SUPPORT_GAME_TETRIS   
    #define SUPPORT_GAME_HITRAT
    //#define SUPPORT_GAME_MOUSE
#endif
//=========== DVB Game End =========== DVB Game End =========== DVB Game End ===========//


//=========== 9Frame Start =========== 9Frame Start =========== 9Frame Start ===========//
#ifdef SUPPORT_DVB_PREVIEW_9FRAMES
    #define SUPPORT_PREVIEW_9FRAMES
    #define DVD_PREVIEW_FUNCTION
#endif
//=========== 9Frame End =========== 9Frame End =========== 9Frame End ===========//


//=========== DVB SETUP Start =========== DVB SETUP Start =========== DVB SETUP Start ===========//
#define CHANNEL_SCAN_MODE //wangcj added

#define SUPPORT_DVB_GUI_NEW
#ifdef SUPPORT_DVB_GUI_NEW
    //#define NEW_OSD_DRIVER
    #define IRCMD_TEST
    #define DVB_16Color_BMP //added by wangcj for supporting the 16 color bmp 2005-6-15 10:49
    #define DVB_16Color_FLAT_STYLE //taolin
    #define DVB_GUI_SUPPORT_MUSTEK //wangcj added for supporting the mustek's GUI
    #define FIRST_INSTALL_DIALOG //taolin
    //#define SCAN_RESULT_ERASE_DIALOG //taolin
    #define ENLARGE_SDRAM_CS_AND_OSD_SIZE
#endif //end #ifdef SUPPORT_DVB_GUI_NEW
    
#if defined(DVD_SETUP_REENG)&&defined(DVB_SETUP_MENU)
    #define DVB_SETUP_REENG
#endif

#define SUPPORT_DVB_TIMER
#ifdef SUPPORT_DVB_TIMER          //sunzhh add 20050929
    #define TIME_NO_SAVING
    #define READ_TS_TIME_ZONE  ///yang li,2006-4-13 11:00
    //#define SUPPORT_AUTO_ADJUST_SUMMER_TIMER_WHEN_NOTOT
#endif

#ifdef FOUR_CHAN_CLASS
    #define CHAN_CLASS_6COL  //wangcj added for chanclass only 6 cols.
#endif

//#define	SETUP_COLOR_TYPE2
#ifdef SETUP_COLOR_TYPE2
    #define DVB_OSD_MENU_VER3
#else
    #define DVB_OSD_MENU_VER1                            //First version button style menu
#endif

#define ENLARGING_DVB_MENU_ITEM_LENGTH //Jack added 05/09/26

#define DEL_LEVEL_AND_QUALITY_IN_SCAN_MENU //Jack added 05/09/27

//#define SHOW_LCN
//#define NO_RENAME_PROGRAM_FUNC           //sunzhh add 20051031
//#define NO_CANCEL_CHANNEL_SORT           //sunzhh add 20051031

#define TRANSPARENCY_LEVEL LEVEL_1      //sunzhh add 20050920
#define LEVEL_0 0xff//Note: The value is more big,the menu transparency is more less.
#define LEVEL_1 0xe0
#define LEVEL_2 0x90

//#define ALL_TIMEZONE_OPEN //Jack added 06/04/05

//=========== DVB SETUP End =========== DVB SETUP End =========== DVB SETUP End ===========//


//=========== DVB Other UI Start =========== DVB Other UI Start =========== DVB Other UI Start ===========//
#define SHOW_WARMMSG_WHEN_NO_SIGNAL_AFTER_SCAN

#define WHEN_NO_SIGNAL_SHOW_BLACK_BG

//#define WHEN_PROG_CHANGE_BLACK_BG   //Just as the name.Jack added for user select 05/11/08

//#define USE_OSD_DEBUG_DEMUX_I2C //Jack 06/01/11 temp added for customer debug

#define UNPOLLING_USB_WHEN_SYSTEM_STATE_IS_TS //Yangli added

#if defined(SUPPORT_DVB_BOOKING)&&!defined(RISC_ALIVE_STANDBY)
    #define RISC_ALIVE_STANDBY
#endif

//=========== DVB Other UI End =========== DVB Other UI End =========== DVB Other UI End ===========//


//=========== Servo Begin =========== Servo Begin =========== Servo Begin =========== Servo Begin ===========//
#define STOP_LOADER
//=========== Servo End =========== Servo End =========== Servo End =========== Servo End ===========//


//=========== OSD Begin =========== OSD Begin =========== OSD Begin =========== OSD Begin ===========//
#define DVB_OSD_TIMEOUT     2//2 mean the basic unit is 2 seconds
#define DVB_OSD_LANGUAGE_SYNC_DVD
//Jack 06/05/24 added for some conflict between new DVD OSD drvier and DVB OSD dirver.
//After changing DVB osd to DVD osd driver,we will mark it!!!
//Because in DVD OSD driver,we have added p-scan judge so UI can't judge p-scan again,otherwise will cause conflict!
#define USE_NNEW_OSD_DRIVER
//=========== OSD End =========== OSD End =========== OSD End =========== OSD End ===========//


//=========== IR Begin =========== IR Begin =========== IR Begin =========== IR Begin ===========//
//#define IR_SWITCH_DVD_USB_CARD_AVIN_DVB//Must Open <SUPPORT_USB><SPHE8202_CARD_STORAGE><DVB_DVD_8202> 
#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
//#define ONLY_CARD_NO_USB
//#define ONLY_USB_NO_CARD
//#define NO_USB_NO_CARD
#define SUPPORT_NOT_CHECK_OPENCLOSE_DVB
//#define AV_IN_THROUGH_EXT_ADC
    #define IR_SWITCH_CD_USB_CF_OTHER
//#define DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB//<debug debug debug debug debug debug><Release version must close it>
    #define NO_SWITCH_GPIO
//#define NOT_RECORD_DVB_DVD_STATE
    #define MODE_SWITCH_DELAY
    #ifdef MODE_SWITCH_DELAY
#define MODE_DELAY_CNT  4
    #endif
    #define USBCARD_PLUG_OUT_CLEAR_SETUP_PROG
    #define FIX_STATE_CHANE_NOT_READ_USB
#endif


#define DVB_IR_3D_ON
#define DVB_IR_FORMAT_ON
#define DVB_IR_PSCAN_ON

#define DVB_IR_SCAN_KEY
#ifdef DVB_IR_SCAN_KEY
    //#define SCAN_KEY_DIRECTLY_GOTO_FIRSTIME_INSTALLATION
    #define SCAN_KEY_DIRECTLY_GOTO_AUTO_SCAN_MENU
#endif

#define LEFT_RIGHT_KEY_CHANGE_CLASS //Just as the name.Jack added 05/12/30  
//=========== IR End =========== IR End =========== IR End =========== IR End ===========//


//=========== Audio Start =========== Audio Start =========== Audio Start =========== Audio Start ===========//
//#define _DynamicGet_AudioPID   //sunzhh add
#define RECODE_VOL_INFO
//#define SUPPORT_RESET_6600_BY_GPIO32
//#define SUPPORT_CONTROL_DEMUX_RESET 
#ifdef SUPPORT_CONTROL_DEMUX_RESET  //Jack 06/08/22 added  to replace SUPPORT_RESET_6600_BY_GPIO32
    #if defined(LG_DVBCOMBO_DVD)
    #define DEMUX_RESET_GPIO    51
    #else
    #define DEMUX_RESET_GPIO    32
    #endif
#endif


#define MOVE_IOP_CODE_START
//=========== Audio End =========== Audio End =========== Audio End =========== Audio End ===========//


//=========== Scan Start =========== Scan Start =========== Scan Start =========== Scan Start ===========//
//#define DEFAULT_SCAN_RESULT_REPLACE  //sunzhh add
//#define AUTO_SCAN_DEL_ALL_OLD_INFO    //Jack added 06/04/20
//=========== Scan End =========== Scan End =========== Scan End =========== Scan End ===========//
    
//=========== Flash Start =========== Flash Start =========== Flash Start =========== Flash Start ===========//
//#define USE_2M_FLASH  //Jack added for LG DVD+DVB-T use 2M flash
//=========== Flash End =========== Flash End =========== Flash End =========== Flash End ===========//
    
//======= Bottom ======= Bottom ======= Bottom ======= Bottom ======= Bottom ======= Bottom ======= Bottom ======= Bottom =======

