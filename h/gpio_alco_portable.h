#if defined(PORTABLE_8200)
//For Alco 8200 Portable use
#define PDVD_OPCLSW_GPIO    3//
#define DOOR_SENSE_GPIO     3 
#define POWER_LED_GPIO      36//14
#define TFT_CONTROL_GPIO1    57
#define TFT_CONTROL_GPIO2    59
//#define ICETDI_GPIO         38

#ifdef VIDEO_IN_CONTROL//need a gpio to detect AV in 
	#define INT_EXT_VIDEO_GPIO1	37
	#define INT_EXT_GPIO_INIT1()							\
					do {								\
						GPIO_M_SET(INT_EXT_VIDEO_GPIO1, 1);\
						GPIO_E_SET(INT_EXT_VIDEO_GPIO1, 0);\
					} while (0)
    
    #define INT_EXT_VIDEO_GPIO2	48
	#define INT_EXT_GPIO_INIT2()							\
					do {								\
						GPIO_M_SET(INT_EXT_VIDEO_GPIO2, 1);\
						GPIO_E_SET(INT_EXT_VIDEO_GPIO2, 0);\
					} while (0)					 
#endif //end #ifdef TFT_VIDEO_INOUT

#elif defined(PORTABLE_8202S)
#ifdef ALCO_PVS177W//shenyj add for alco177w
//For Alco 8202s Portable use
#define PDVD_OPCLSW_GPIO    8
#define DOOR_SENSE_GPIO     8 
#define BAT_LOW_LED_GPIO    11
#define TFT_CHECK_GPIO      55
#define TFT_CONTROL_GPIO    70
#ifdef BAT_DETECT
#define BAT_LOW_GPIO        10        
#endif

#ifdef VIDEO_IN_CONTROL
	#define INT_EXT_VIDEO_GPIO	29
	#define INT_EXT_GPIO_INIT()							\
					do {								\
						GPIO_M_SET(INT_EXT_VIDEO_GPIO, 1);\
						GPIO_E_SET(INT_EXT_VIDEO_GPIO, 0);\
					} while (0)
#endif 

#elif defined(ALCO_PVS127X)    

#define PDVD_OPCLSW_GPIO        8
#define DOOR_SENSE_GPIO         8 
#define POWER_LED_STB1_GPIO     2
#define POWER_LED_STB2_GPIO     5
#define TFT_CHECK_GPIO          55
#define TFT_CONTROL_GPIO        70
#define TFT_STB_CONTROL_GPIO    16
#ifdef BAT_DETECT
#define BAT_LOW_GPIO            10        
#endif

#endif

#endif

#ifdef ALCO_PVS19251

#define PDVD_OPCLSW_GPIO        8
#define DOOR_SENSE_GPIO         8 
#define POWER_LED_STB1_GPIO     2
#define POWER_LED_STB2_GPIO     5
#define TFT_CONTROL_GPIO1       9
#define TFT_CONTROL_GPIO2       10

#ifdef VIDEO_IN_CONTROL//need a gpio to detect AV in 
	#define INT_EXT_VIDEO_GPIO1	12
	#define INT_EXT_GPIO_INIT1()							\
					do {								\
						GPIO_M_SET(INT_EXT_VIDEO_GPIO1, 1);\
						GPIO_E_SET(INT_EXT_VIDEO_GPIO1, 0);\
					} while (0)
    
    #define INT_EXT_VIDEO_GPIO2	13
	#define INT_EXT_GPIO_INIT2()							\
					do {								\
						GPIO_M_SET(INT_EXT_VIDEO_GPIO2, 1);\
						GPIO_E_SET(INT_EXT_VIDEO_GPIO2, 0);\
					} while (0)					 
#endif //end #ifdef TFT_VIDEO_INOUT

#endif

#if defined(ALCO_PVS1262)||defined(ALCO_PVS8712)
#ifdef ALCO_CARD_USB_MODEL
#define PDVD_OPCLSW_GPIO        5
#define DOOR_SENSE_GPIO         5 
#define TFT_CHECK_GPIO          59
#define TFT_CONTROL_GPIO        58
#define TFT_STB_CONTROL_GPIO    57
#define BAT_LOW_GPIO            3    
#else
#define PDVD_OPCLSW_GPIO        8
#define DOOR_SENSE_GPIO         8 
#define TFT_CHECK_GPIO          9
#define TFT_CONTROL_GPIO        11
#define TFT_STB_CONTROL_GPIO    16
#define BAT_LOW_GPIO            10        
#endif  
#elif defined(ALCO_PVS1090)
#define PDVD_OPCLSW_GPIO        8
#define DOOR_SENSE_GPIO         8 
#define TFT_CHECK_GPIO          53
#define TFT_CONTROL_GPIO        58
#define TFT_STB_CONTROL_GPIO    59
#define BAT_LOW_GPIO            10   
//#define POWER_LED_GPIO          72
#define BAT_LOW_LED_GPIO        72
#define POWER_ON_OFF_CONTROL_GPIO    9
#elif defined(ALCO_PVS1090_AVIN)  //yth add for
    #ifdef ALCO_PVS6988_AVIN  //yth add for 2006-1-11 20:21
        #define PDVD_OPCLSW_GPIO      71// 5
        #define DOOR_SENSE_GPIO       71// 5 
        #define TFT_CHECK_GPIO          53
        #ifdef ALCO_PVS6988_AVIN
        	#define TFT_CONTROL_GPIO        59 //pin 180
        #else
        	#define TFT_CONTROL_GPIO        58
        #endif
        #define TFT_STB_CONTROL_GPIO    25
        #define BAT_LOW_GPIO            5// 3   
        //#define POWER_LED_GPIO          72
        #define BAT_LOW_LED_GPIO        72
        #define POWER_ON_OFF_CONTROL_GPIO    9
	#else//#ifdef ALCO_PVS6988_AVIN  /
        #define PDVD_OPCLSW_GPIO      5// 71// 5
        #define DOOR_SENSE_GPIO       5//71// 5 
        #define TFT_CHECK_GPIO          53
        #define TFT_CONTROL_GPIO        58
        #define TFT_STB_CONTROL_GPIO    25
        #define BAT_LOW_GPIO            10// 3   
        //#define POWER_LED_GPIO          72
        #define BAT_LOW_LED_GPIO        72
        #define POWER_ON_OFF_CONTROL_GPIO    9
	#endif//#ifdef ALCO_PVS6988_AVIN  /
#endif
/*
#elif defined(ALCO_PVS1090_AVIN)
#define PDVD_OPCLSW_GPIO        5
#define DOOR_SENSE_GPIO         5 
#define TFT_CHECK_GPIO          53
#define TFT_CONTROL_GPIO        58
#define TFT_STB_CONTROL_GPIO    25
#define BAT_LOW_GPIO            3   
//#define POWER_LED_GPIO          72
#define BAT_LOW_LED_GPIO        72
#define POWER_ON_OFF_CONTROL_GPIO    9
#endif
*/

#ifdef VIDEO_IN_CONTROL     //yth add for alco  2006-3-28 10:01
#ifdef ALCO_PVS1090_AVIN
	#define INT_EXT_VIDEO_GPIO	39//142pin
	#define INT_EXT_GPIO_INIT()							\
					do {								\
					    regs0->sft_cfg0&= ~((0x1)<<4);  \
						GPIO_M_SET(INT_EXT_VIDEO_GPIO, 1);\
						GPIO_E_SET(INT_EXT_VIDEO_GPIO, 0);\
					} while (0)
#endif 
#endif

#ifdef RUN_IN_SUNPLUS_8202D_PORTABE_DVB_DEMOBOARD
	#define PDVD_OPCLSW_GPIO	69
	#define MCU_POWER_DET_GPIO	22
	#define LOWBAT_DET_GPIO		21
	#define CTR_GLED_GPIO		55
	#define DSP_RLED_GPIO		54
	#define HOLD_GPIO			23
	#define TFT_SW_GPIO			68
	#define CTR_TFT_GPIO		93
	#ifdef SUPPORT_DVD_POWER_ONOFF
	#define DVD_POWER_SW_GPIO   101
	#endif
	//#if defined(SUPPORT_TUNER_POWER_ONOFF)&&!defined(TUNER_POWER_SW_USE_DEMUX_GPIO)
    //#define TUNER_POWER_SW_GPIO 37
    //#endif
#endif

#ifdef SUPPORT_DVD_POWER_ONOFF //shenyj move for compile 2006/03/23
	#define DVD_POWER_SW_GPIO   101
#endif

