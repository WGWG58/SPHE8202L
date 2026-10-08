/*--------------------------------------------------------------------------
|  File Name   :  card_main.h
|
|  Description :  8202 card reader function -- SMC¡BCF¡BSD¡BMMC¡BMS¡BMS-Pro
|
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2004/2/9        wthsin         Creating
|--------------------------------------------------------------------------------*/
#ifndef _CARD_DMA_H_
#define _CARD_DMA_H_

#define DMA_SUCCESS					0
#define DMA_FAIL 					1

#define DMA_DRAM      1
#define DMA_FLASH     2
/*
#define CF_CARD_DEVICE   0x02
#define SD_CARD_DEVICE   0x04
#define MS_CARD_DEVICE   0x08
#define SMC_CARD_DEVICE  0x10
*/
enum {
    MEDIA_NONE     =0,
    MEDIA_SMC      =1,
    MEDIA_RESERVED1=2,
    MEDIA_CF       =3,
    MEDIA_SPI      =4,
    MEDIA_RESERVED2=5,
    MEDIA_SD       =6,
    MEDIA_MS       =7,
};

#ifdef CARD_SETUP_TYPE_1            /*Three card Bus Demo Set*/
 #define CARD_SENSE1_PIN        50 //GPIO 50 ca8202 pin193	
 #define CARD_SENSE2_PIN        84 //GPIO 84 ca8202 pin178	 
 #define CARD_SENSE3_PIN        83 //GPIO 83 ca8202 pin176	 
 #define CARD_POWER_RESET       17 //GPIO 17 ca8202 pin77	
 //#define CARD_LED_PIN           29 //GPIO 29 ca8202 pin145
#elif defined(CARD_SETUP_TYPE_2)    /*Share One card Bus(EASTECH)*/
 #define CARD_SENSE1_PIN        16 //GPIO 16 ca8202 pin76	 
 #define CARD_SENSE2_PIN        84 //GPIO 84 ca8202 pin178	 
 #define CARD_SENSE3_PIN        83 //GPIO 83 ca8202 pin176	 
 #define CARD_POWER_RESET       17 //GPIO 17 ca8202 pin77	
 //#define CARD_LED_PIN           29 //GPIO 29 ca8202 pin145
#elif defined(CARD_SETUP_TYPE_3)    /*256Pin 16bit Non_share mode All card*/
 #define CARD_SENSE1_PIN        16 //GPIO 16 ca8202 pin76	
 #define CARD_SENSE2_PIN        30 //GPIO 30 ca8202 pin152	 
#ifdef PORTABLE_DVD
 #define CARD_SENSE3_PIN        38 //GPIO 38 ca8202 pin161
	#elif defined(IDE_CF_SW)
	#define CARD_SENSE3_PIN        38 //GPIO 38 ca8202 pin161
          #elif defined(COSMIC_CARD_READER) //FanGang added 2005-1-10 17:37
          #define CARD_SENSE3_PIN        39//GPIO  39 ca8202 pin162
#elif defined (CARD_SENSE3_USE_GPIO39) /* 2005-6-6 huziqin*/
 #define CARD_SENSE3_PIN        39 // GPIO 39 ca8202 pin 162	 
#elif defined (IC_8202D)&&!defined(CARD_SENSE3_USE_GPIO38)	
     #ifdef HDMI_16_BIT_256PIN_BOARD
          	#define CARD_SENSE3_PIN 	51    // 194Pin  add for HDMI_16_BIT_256PIN_BOARD   lxg 2006-4-18 09:14
	 #else
			#define CARD_SENSE3_PIN 	102//GPIO 102 pin188 zhongshan add 2005-8-22 15:28
     #endif
#elif defined (CARD_SENSE3_USE_GPIO38)   
  #define CARD_SENSE3_PIN        38 // GPIO 38 ca8202 pin 161	
#else  	 
 #define CARD_SENSE3_PIN        29 //GPIO 29 ca8202 pin145	 
#endif 
 #define CARD_POWER_RESET       17 //GPIO 17 ca8202 pin77	  
 #ifdef HDMI_SMC_CLE
 #define CARD_SMC_CLE_PIN       36 // GPIO 36 ca8202 pin 159
 #endif
#elif defined(CARD_SETUP_TYPE_4)    /*256Pin 32bit Non_share mode 3-in-1 card*/
	#if defined(MP_BOARD_256_PIN_NON_SHARE) //kenny 2004/7/14
	#define CARD_SENSE1_PIN        16 //GPIO 16 ca8202 pin76	 
	#define CARD_SENSE2_PIN        15 //GPIO 15 ca8202 pin75
	#define CARD_POWER_RESET       17 //GPIO 17 ca8202 pin77	   
	#elif defined(MP_BOARD_216_PIN_NON_SHARE)
	#define CARD_SENSE1_PIN        15 //GPIO 15 ca8202 ns-216 pin66	 
	#ifdef SUPPORT_6500
		#define CARD_SENSE2_PIN        30 //for 8202D 216pin + 6500, pin132, ronnie
	#else
		#define CARD_SENSE2_PIN        16 //GPIO 16 ca8202 ns-216 pin65
	#endif
	#define CARD_POWER_RESET       8  //GPIO  8 ca8202 ns-216 pin55
	#else 
	#define CARD_SENSE1_PIN        16 //GPIO 16 ca8202 pin76	 
	#define CARD_SENSE2_PIN        15 //GPIO 15 ca8202 pin75
	#define CARD_POWER_RESET       17 //GPIO 17 ca8202 pin77	   
	#endif
#elif defined(CARD_SETUP_TYPE_5)    /*256Pin 16bit  PMP project,Support HD and CF */   
  #ifdef PMP_PCB_VER_B 
	#define CF_INS_SENSE           16 //GPIO 16 ca8202 pin76
  #else	//PMP_PCB_VER_C
	 #define CF_INS_SENSE           39 //GPIO 39 ca8202 pin162
  #endif	
	#define CARD_POWER_RESET       18 //GPIO 18 ca8202 pin78		
#endif

extern void SetMediaTypeMode(UINT8  , UINT16  ); 
extern void HW_DMA_DRAM_ADDR_SET(UINT32);
extern UINT32 hwDmaStart(UINT32, UINT32, UINT32);
extern int  CardStorageIsPlugIn(); 
extern BYTE Detect_Card_Storage();
 #ifdef CARD_SETUP_TYPE_5
  extern int PMP_CF_Card_IsPlugIn();
 #endif //CARD_SETUP_TYPE_5
#endif //_CARD_DMA_H_



