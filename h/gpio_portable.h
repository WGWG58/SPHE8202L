/*
----->included by gpio.h
----->only for portable dvd use.
----->did it on 07/25
*/	
	

//some general IO use define
#if defined(SUNPLUS_8202P_DEMOBOARD)
	#define PDVD_OPCLSW_GPIO	3
	
	#define MCU_POWER_DET_GPIO	22
#ifdef EASTWIN
	#define LOWBAT_DET_GPIO		18
#else
	#define LOWBAT_DET_GPIO		21
#endif
	#define CTR_GLED_GPIO		55
	#define DSP_RLED_GPIO		54
	#define HOLD_GPIO			23
	#define TFT_SW_GPIO			2
	#define CTR_TFT_GPIO		93
#elif defined(RUN_IN_SUNPLUS_8202D_PORTABE_DVB_DEMOBOARD)
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
#elif defined(MALATA_PORTABLE_DVBT)//tianye add 200607
	#define PDVD_OPCLSW_GPIO	69
	#define MCU_POWER_DET_GPIO	22
	#define LOWBAT_DET_GPIO		21
	#define CTR_GLED_GPIO		55
	#define DSP_RLED_GPIO		54
	#define HOLD_GPIO			23
	#define TFT_SW_GPIO			68
	#define CTR_TFT_GPIO		93
#else
	#define PDVD_OPCLSW_GPIO	16
	#define MCU_POWER_DET_GPIO	41
	#define LOWBAT_DET_GPIO		42
	#define CTR_GLED_GPIO		39
	#define DSP_RLED_GPIO		40
	#define HOLD_GPIO			37
	#define TFT_SW_GPIO			44
	#define CTR_TFT_GPIO		43
#endif
	
//spi related IO define 
#ifdef SUPPORT_SPI
		#ifdef SPI_IO_NEW
		#define SPI_DATAIN	52
		#define SPI_DATAOUT	50
		#define SPI_CLK		51
	    #else
	    #define SPI_DATAIN	39
	    #define SPI_DATAOUT	37
	    #define SPI_CLK		38
	    #endif
#endif
    
//need a gpio to control PAL/NTSC in TFT 
#ifdef PNGPIO_CON_TFT 
#ifdef EASTWIN
	#define PALNTSC_CON_GPIO	94	// EASTWIN change to gpio94
#else
	#define PALNTSC_CON_GPIO	59
#endif
	#define PALNTSC_GPIO_INIT()							\
					do {								\
						regs0->sft_cfg3 &= ~((0x01)<<3);\
						GPIO_M_SET(PALNTSC_CON_GPIO, 1);\
						GPIO_E_SET(PALNTSC_CON_GPIO, 1);\
					} while (0)
	#define NTSC_SET()	GPIO_O_SET(PALNTSC_CON_GPIO,1)
	#define PAL_SET()	GPIO_O_SET(PALNTSC_CON_GPIO,0)
#endif //end #ifdef PNGPIO_CON_TFT
    
//need a gpio to detect AV in
#ifdef TFT_VIDEO_INOUT 
	#define INT_EXT_VIDEO_GPIO	56
	#define INT_EXT_GPIO_INIT()							\
					do {								\
						GPIO_M_SET(INT_EXT_VIDEO_GPIO, 1);\
						GPIO_E_SET(INT_EXT_VIDEO_GPIO, 0);\
					} while (0)
#endif //end #ifdef TFT_VIDEO_INOUT
	
#ifdef EASTWIN
	#define ENABLE_AMP()			GPIO_O_SET(48,0)	
	#define DISABLE_AMP()			GPIO_O_SET(48,1)	
	#define EAR_DETECT()			GPIO_I_GET(49)
	#define INVERTER_POWER_ON()		GPIO_O_SET(51,0)
	#define INVERTER_POWER_OFF()	GPIO_O_SET(51,1)
	#define POWER_LED_ON()			GPIO_O_SET(54,0)
	#define POWER_LED_OFF()			GPIO_O_SET(54,1)
	#define LCD_VIEW_MODE_NORMAL()	GPIO_O_SET(97,0)	
	#define LCD_VIEW_MODE_FULL()	GPIO_O_SET(97,1)
	#define LCD_POWER_ON()			GPIO_O_SET(100,1)
	#define LCD_POWER_OFF()			GPIO_O_SET(100,0)
	#define AUDIO_MUTE_ON()			GPIO_O_SET(56,1)	// Kevin Sep 22,04 
	#define AUDIO_MUTE_OFF()		GPIO_O_SET(56,0)	// Kevin Sep 22,04 
	
	#define AN2526H_ADDR		0x88 
    #define AN2546H_ADDR		0x88 
    #define VX1818_ADDR			0xD8 
    #define data_refresh_mode   0x80 
    #define auto_increment_mode	0x00 
    
	/* an2526H operation mode */
	#define NORMAL_MODE         0                                       
    #define FULL_MODE	     	1                                         
                               
    #define E2PROM_BEEN_USED	0x55
    #define	BEEN_USED_ADDR		182		// I2C address
    #define	VIEWMODE_ADDR		183		// I2C address
		                                                                       
    void init_an2526h_ntsc(void);  
    void init_an2526h_pal(void);
    //void vx1818_init(void);                                           
    void an2526h_send_data(void);                                     
    void an2526h_value_change(unsigned char para,unsigned char value);
    void init_lcd_display_mode(void);
    void check_customer_default(void);
    void load_customer_default(void); 
    void init_an2526h(void);			// Kevin Sep 20,04 
                                   
#endif   
	
#ifdef MUSTEK_K100D_MODEL

    #define POWER_KEY_GPIO  5
    #define EJECT_KEY_GPIO  34
    #define OPEN_TRAY_GPIO  7
    #define DOOR_SENSE_GPIO 54    
    #undef PDVD_OPCLSW_GPIO
    #define PDVD_OPCLSW_GPIO    DOOR_SENSE_GPIO
    #define LED_CONTROL_GPIO    5//6600
    #define AV_IN_4052_CTL_GPIO1    12//6600
    #define AV_IN_4052_CTL_GPIO2    13//6600
    #ifdef ADD_OP_MUTE
    #define OP_MUTE_GPIO            7//6600
    #endif
    
#endif //end #ifdef MUSTEK_K100D_MODEL
	
#ifdef  SUPPORT_MALATA_GPIO
   #undef PDVD_OPCLSW_GPIO
   #define PDVD_OPCLSW_GPIO            GPIO_CHECK_OPEN_CLOSE
#endif//end=> #ifdef  SUPPORT_MALATA_GPIO
	
#if defined(TOP_DOOR_LOADER)
#undef PDVD_OPCLSW_GPIO
#define PDVD_OPCLSW_GPIO DOOR_SENSE_GPIO
#endif
