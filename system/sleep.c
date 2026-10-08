//
// FILE
// sleep.c
//
// DESCRIPTION
// provide sleep functionality
//
// History
// terry,2004/9/21 10:16PM , add risc can work when standby mode
// terry,2005/4/4 11:37と, reduce sleep function code size
//       Revise:
//       1. vfd receive Key function.
//       2. HANYANG_DP02CD_WG_8202S_16
//       3. add in debug function
//       Relation Files: hwif.c,iop.c
//       

#include "config.h"
#include "global.h"
#include "regmap.h"
#include "flash.h"
#include "pu8560.h"

#include "cpu.h"
#include "func.h"

#include "gpio.h"
#include "hwif.h"
#include "tvif.h"
#ifdef PMP_MCU810
#include "vfd.h"
#endif
#ifdef RISC_ALIVE_STANDBY  // 2004/10/01 yltseng
#include "iop.h"
#include "uartsup.h"
#include "ircode.h"
#endif

#ifdef ORITRON_TRAY_PASSWORD
#include "e2prom_map.h"   //hongfeng 2005-08-31
#endif
#ifdef SUPPORT_RECEIVER		//OP fcr 2005-9-30 14:52
#include "amp_gui.h"
#endif

//#include "auddac.h"

//#include "ircode.h"    /* alan 02-05-21 added for IRC_POWER */

#ifndef	DVDRELEASE
#include "sio.h"
#include "emuio.h"
#endif

#if defined(MUSTEK_K100D_MODEL)&&defined(USE_DEMUX_GPIO_WHEN_STANDBY)
#include "dmx_6600_gpio.h"
#endif

#ifdef SUPPORT_DVD_POWER_ONOFF
#include "vfdfunc.h"
#endif

/*
*  Debug Option
*/
#ifndef   DVDRELEASE
#define SLEEP_DBG
#define SLEEP_RISC_ALIVE_DBG
//#define DRAM_TEST
#endif

#ifdef SLEEP_DBG
#define hwif_printf(s...) {psprintf(linebuf,##s);UART0_puts(linebuf);}
#else
#define hwif_printf(s...) do {} while (0)
#endif


/*
*  External Variable
*/

extern BYTE TP6317_Power ;
extern UINT8 bSleepFlag;

/*
*  External Function
*/

extern void servo_turn_off(void);
extern int atapi_standby_mode(void);
extern void run_close_tray(UINT8);
extern int atapi_p_mechanism_status(void);
extern void ircmd_trayin(void);
extern void reset_iop();
extern int standby_cnt;
extern const BYTE vfd_keycode[40];
extern void delay_time(UINT32 counter);
extern void __boot_entry();    
extern void hwif_reset_sleep2(int awake);
extern UINT16 GetIRCode();  // 2004/10/01 yltseng
extern int change_system_clock(int);


/*
*  Define 
*/

//#ifdef SAFE_AUTO_POWEROFF===>#if 1//nono modify on 20060428
//#define SAFE_AUTO_POWEROFF//nono set it. 4-7-22 23:46 Because servo need longer time to finish when trayout.

#define	ROM_ISA_ENABLE	(1<<15)
#define	HW_RESET_GLOBAL		(1<<0)		// 1-shot global reset
#define	HW_RESET_AGDC_MMU	(1<<1)		// will/may hang up system
#define	HW_RESET_STC		(1<<2)
#define	HW_RESET_IOP		(1<<3)
#define	HW_RESET_HOST		(1<<4)		// ATAPI/UDE/CSS/CDDSP
#define	HW_RESET_AUD		(1<<5)		// DSP/DSP3IF/DVDAUD
#define	HW_RESET_VDEC		(1<<6)		// VLD/INVQ/IDCT/MC/OGT(?)
#define	HW_RESET_DISPLAY	(1<<7)		// VPP/OSD
#define	HW_RESET_SIO0		(1<<8)
#define	HW_RESET_UART0		(1<<9)
#define	HW_RESET_UART1		(1<<10)


#ifdef SCART_TV
    // mimitsai merge from dp2070/dp3240

    #ifdef DP2070_KEY_SCAN
        #define SET_SCART_RGB(d)    GPIO_O_SET( SCART_RGB_GPIO_PIN,	d )
        #define SET_SCART_SW(d)     GPIO_O_SET( SCART_SW_GPIO_PIN,	d )
        #define SET_SCART_TV(d)     GPIO_O_SET( SCART_TV_GPIO_PIN,	d )
    #else
        #define SET_SCART_RGB(d)	((d) ? (regs0->gpio_out[39 / 16] |= (0x1 << (39 % 16))) : (regs0->gpio_out[39 / 16] &= ~(0x1 << (39 % 16))))
        #define SET_SCART_SW(d)		((d) ? (regs0->gpio_out[38 / 16] |= (0x1 << (38 % 16))) : (regs0->gpio_out[38 / 16] &= ~(0x1 << (38 % 16))))
        #define SET_SCART_TV(d)		((d) ? (regs0->gpio_out[37 / 16] |= (0x1 << (37 % 16))) : (regs0->gpio_out[37 / 16] &= ~(0x1 << (37 % 16))))
    #endif
#elif defined(KSD_SCART_TV)

    #define SET_SCART_RGB(d)	((d) ? (regs0->gpio_out[57 / 16] |= (0x1 << (57 % 16))) : (regs0->gpio_out[57 / 16] &= ~(0x1 << (57 % 16))))
    //#define SET_SCART_SW(d)		((d) ? (regs0->gpio_out[18 / 16] |= (0x1 << (18 % 16))) : (regs0->gpio_out[18 / 16] &= ~(0x1 << (18 % 16))))
#elif defined(SCART_TV_2)    //wanghaoying 2003-8-13 15:11 added 
    #define SET_SCART_RGB(d)	((d) ? (regs0->gpio_out[57 / 16] |= (0x1 << (57 % 16))) : (regs0->gpio_out[57 / 16] &= ~(0x1 << (57 % 16))))
    #define SET_SCART_SW(d)		((d) ? (regs0->gpio_out[18 / 16] |= (0x1 << (18 % 16))) : (regs0->gpio_out[18 / 16] &= ~(0x1 << (18 % 16))))
    #ifdef NIN_SCART_TV    //fangang added 4-2-11 17:02
           #define SET_SCART_TV(d)		((d) ? (regs0->gpio_out[2 / 16] |= (0x1 << (2 % 16))) : (regs0->gpio_out[2 / 16] &= ~(0x1 << (2 % 16))))
    #endif
    #ifdef YILI_SCART_TV  //hq add, use 31 pin control  TV-AV switch, 4-2-17 9:40 
           #define SET_SCART_TV(d)		((d) ? (regs0->gpio_out[4 / 16] |= (0x1 << (4 % 16))) : (regs0->gpio_out[4 / 16] &= ~(0x1 << (4 % 16))))
    #endif    
#elif defined(SCART_TV_3)   //wanghaoying 2003-9-12 11:28 added
    #define SET_SCART_RGB(d)    ((d) ? (regs0->gpio_out[57 / 16] |= (0x1 << (57 % 16))) : (regs0->gpio_out[57 / 16] &= ~(0x1 << (57 % 16))))
    #define SET_SCART_SW(d)		((d) ? (regs0->gpio_out[18 / 16] |= (0x1 << (18 % 16))) : (regs0->gpio_out[18 / 16] &= ~(0x1 << (18 % 16))))
    #define SET_SCART_SW1(d)	((d) ? (regs0->gpio_out[14 / 16] |= (0x1 << (14 % 16))) : (regs0->gpio_out[14 / 16] &= ~(0x1 << (14 % 16))))
#elif defined(SCART_TV_4)   //nono 2003-9-26 1:44 for himage HJ-018

    #define SET_SCART_RGB(d)    ((d) ? (regs0->gpio_out[3 / 16] |= (0x1 << (3 % 16))) : (regs0->gpio_out[3 / 16] &= ~(0x1 << (3 % 16))))

	    #ifdef HJ_021_SCART
	    #define SET_SCART_SW1(d)		((d) ? (regs0->gpio_out[4 / 16] |= (0x1 << (4 % 16))) : (regs0->gpio_out[4 / 16] &= ~(0x1 << (4 % 16))))
	    #define SET_SCART_SW(d)	((d) ? (regs0->gpio_out[2 / 16] |= (0x1 << (2 % 16))) : (regs0->gpio_out[2 / 16] &= ~(0x1 << (2 % 16))))
	    #else//#ifdef HJ_021_SCART
    #define SET_SCART_SW(d)		((d) ? (regs0->gpio_out[4 / 16] |= (0x1 << (4 % 16))) : (regs0->gpio_out[4 / 16] &= ~(0x1 << (4 % 16))))
    #define SET_SCART_SW1(d)	((d) ? (regs0->gpio_out[2 / 16] |= (0x1 << (2 % 16))) : (regs0->gpio_out[2 / 16] &= ~(0x1 << (2 % 16))))
	    #endif//#ifdef HJ_021_SCART

#elif defined(SCART_TV_5)//wangfeng 2003-12-2 11:43 for himage HJ-023
    #define SET_SCART_RGB(d)    ((d) ? (regs0->gpio_out[63 / 16] |= (0x1 << (63 % 16))) : (regs0->gpio_out[63 / 16] &= ~(0x1 << (63 % 16))))
    #define SET_SCART_SW(d)		((d) ? (regs0->gpio_out[62 / 16] |= (0x1 << (62 % 16))) : (regs0->gpio_out[62 / 16] &= ~(0x1 << (62 % 16))))	
    #define SET_SCART_SW1(d)	//((d) ? (regs0->gpio_out[2 / 16] |= (0x1 << (2 % 16))) : (regs0->gpio_out[2 / 16] &= ~(0x1 << (2 % 16))))
#endif



/*
*  Variable
*/
#ifdef POWER_OFF_ONLY_VIDEO_DAC_OFF
static UINT16 tv_mode5;
#endif



/*
*   static inline function
*/

static inline void system_sleep_flash_setup(void)
{    
   if(((system_flash_id&0xffff)==0x1c42)||((system_flash_id&0xffff)==0x7f12))
    {
        //joshua, modified for IR boot problem of Eon and Amic flash, 
        //change to initial mode(1-bit mode)           
        SPI_APP_upgrade_init();    
    }
    else
    {
        //restore spi flash to initial value
        regs0->RF_SPI_CTRL =0x2cfb;
    }            
}

static inline void system_tuner_sleep(void)
{
    tv_sleep();
#if 0
    regs0->rom_config	= (1 << 15)   // rom run slow
                        | (15 << 0)
                        | (15 << 4)
                        | (15 << 8);
#endif    
    delay_srv_10ms(10);

    cpu_intr_disable();	
    regs0->intr_mask = 0;
    regs0->intr_flag = -1;    
}

static inline void disable_tv(void)
{
    // disable tv-encoder
    tv_sleep();
#ifdef  YILI_SCART_TV  //hq added, use 31 pin control  TV-AV switch, 4-2-11 16:59
    SET_SCART_TV(1);
#endif   
#ifdef  NIN_SCART_TV  //fangang added 4-2-11 16:59
    SET_SCART_TV(1);
#endif

#ifdef SUPPORT_SCART_TV//SPHE8202//nono 4-3-27 21:35
    SET_SCART_GPIO_SFT_CFG_CTRL();
    SET_SCART_TO_TV();
#endif//SPHE8202
}

static inline void close_tray_func(void)
{
#ifdef GBM_DVD
    run_close_tray(0); // gerry for gbm use old servo code,if we update servo,maybe we need not this. 2004-2-7 15:42
#elif !defined(TOP_DOOR_FOR_NGAILIK)     //hq add for ngailik, in order to wake up the system after power off-on quickly switch. 2004-3-3 17:38
#if 1//def SAFE_AUTO_POWEROFF//nono 20040327
    //if (atapi_p_mechanism_status()==0/*ATAPI_DOOR_OPEN*/)
    //  ircmd_trayin();//nono 2004-3-27 16:27 for auto_poweroff.
    //else				//zhongshan marked here no need now 2006-2-7 18:15
      run_close_tray(1); // Robert 2003/12/16        
#else//SAFE_AUTO_POWEROFF
    run_close_tray(1); // Robert 2003/12/16
#endif//SAFE_AUTO_POWEROFF
#endif    
}

#ifdef HANYANG_DP02CD_WG_8202S_16//added by wangwei,2005-3-14 11:37
static inline UINT8 standby_scan_power_key_and_light(void)
{
    UINT8 key_value;
    // Power key wake up.
    GPIO_O_SET(21, 1);
    GPIO_O_SET(22, 0);
    delay_time(0xff);
    if((!GPIO_I_GET(15)) && (!GPIO_I_GET(16)) && GPIO_I_GET(23))
    { 
        key_value = 1;
    }
    else 
    { 
        key_value = 0;
    }
    GPIO_O_SET(21, 0);// closing Green LED
    GPIO_O_SET(22, 1);// lighting Red LED
    delay_1ms(1);
    
    return key_value;
}
#endif//HANYANG_DP02CD_WG_8202S_16

static inline void led_light(void)
{

#ifdef OP_256_USE_PIN65_POWER_LED 

GPIO_M_SET(8, 1);
GPIO_E_SET(8, 1);
GPIO_O_SET(8, 0);
  
#endif
 
#ifdef OP_216_USE_PIN57_POWER_LED 
 
GPIO_M_SET(9, 1);
GPIO_E_SET(9, 1);
GPIO_O_SET(9, 0);
  
#endif

#ifdef USE_VFD_LED_AS_IO //xyy add for Oritron
	write_vfd_led(0x01);
#endif
	
#ifdef KENLOON_PANEL3
    write_vfd_led(0xff);  //wangap add 2004/6/29
#endif
#ifdef USE_VFD_LED_POWER
#ifdef USE_VFD_LED_POWER_LOW
    write_vfd_led(0);
#else
    #ifdef  PROVIEW_DV_509	
        write_vfd_led(0x8);
    #elif defined(VTREK_DVD)
        write_vfd_led(0x7);
    #else    
        write_vfd_led(0xf);
    #endif 
#endif 
#endif

#ifdef KSD_SCART_TV
	GPIO_O_SET(18,1);
#endif

#ifdef USE_CD_SENSE_PIN_AS_LED_GPIO			//gerry,2004-2-10 18:33
	GPIO_O_SET(4,1);
#endif//USE_CD_SENSE_PIN_AS_LED_GPIO    

#ifdef NINTAUS_612      //linrc add for nintaus 2004-7-6 13:57 when standby,the LED must light
    GPIO_O_SET(4,1);
    GPIO_O_SET(3,0);
#endif

#if defined(USE_VFDPORT_TO_KEYLIGHT_GBM)
	regs0->gpio_master[56 / 16] |= (0x1 << (56 % 16));//pin156
    regs0->gpio_oe[56 / 16] |= (0x7 << (56 % 16));
    regs0->gpio_out[56 / 16] |= (0x7 << (56 % 16));      
#elif defined(GPIO14_STANDBY_LED)    //hq, 2004-3-20 15:52
    GPIO_O_SET(14,1);//turn on the Standby LED.
#elif defined(USE_VFDPORT_TO_KEYLIGHT_MINTON)
	GPIO_O_SET(14,0);//off

	regs0->gpio_oe[54 / 16] |= (0x7 << (54 % 16));//nono 2003-9-1 23:50
	GPIO_O_SET(54,1);//off
	GPIO_O_SET(55,1);//off
	GPIO_O_SET(56,1);//off         
#elif defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_2290)

	GPIO_O_SET(54,1);//off
	GPIO_O_SET(55,1);//off
	GPIO_O_SET(56,1);//off
#elif defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313)
	GPIO_O_SET(3,1);
	GPIO_O_SET(62,1);
	GPIO_O_SET(63,1);          
#endif

#ifdef GBM_SET_VFD_PIN_LOW_WHEN_STANDBY		//set vfd pin low when standby for GBM TOP_DOOR_LOADER,gerry,2004/2/11 08:48と
    GPIO_M_SET(54,1);
	GPIO_E_SET(54,1);
	GPIO_O_SET(54,0);
	
	GPIO_M_SET(55,1);
	GPIO_E_SET(55,1);
	GPIO_O_SET(55,0);
	
	GPIO_M_SET(56,1);
	GPIO_E_SET(56,1);
	GPIO_O_SET(56,0); 	
#endif//GBM_SET_VFD_PIN_LOW_WHEN_STANDBY

#ifdef GBM_USE_GPIO_CONTROL_LED			//use gpio44(pin138) control led on/off,2004/2/11 08:54と
    GPIO_M_SET(44,1);
	GPIO_E_SET(44,1);
	GPIO_O_SET(44,0);
#endif//GBM_USE_GPIO44_CONTROL_LED

}

static inline void disable_scart_tv(void)
{
    #if defined(SCART_TV_4)||defined(SCART_TV_5)//wangfeng 2003-12-2 23:03
    SET_SCART_SW1(1);
#elif defined(SCART_TV_2)&&defined(GBM_SCART_TV)//nono 2003-12-10 14:50
    SET_SCART_RGB(1);
    SET_SCART_SW(0);
#elif defined(SCART_TV_2)&&defined(GBM_USE_A11_AS_SCART_TV_RELEASE)     //gerry for scart_tv_release,2004-1-17 20:11
    GPIO_O_SET(14, 1);
    SET_SCART_SW(0);
#endif

// Add temporily by David
// for Syber Sanyo
#ifdef SCART_TV_2_ADD_RELEASE  //David 2003-12-6 10:25
	SET_SCART_SW(0);
    regs0->sft_cfg1 &= ~(0x01 << 2);  // pin71 GPIO36
    GPIO_M_SET(36,1);
	GPIO_E_SET(36,1);
	GPIO_O_SET(36,1);
#endif
}

static inline void servo_sleep(void)
{
#if 1//def SAFE_AUTO_POWEROFF
#if (!defined(TOP_DOOR_LOADER))&&(!defined(CHECK_PORTABLE_OPCLSW))//jack 5-1-24 18:21
    #ifdef SUPPORT_RECEIVER//for non DVD mode fake tray out state.chenzhao20051123
	if ((current_rcvr_mode==RECEIVER_MODE_DVD)&&atapi_p_mechanism_status()==0/*ATAPI_DOOR_OPEN*/)
    #else
	if (atapi_p_mechanism_status()==0/*ATAPI_DOOR_OPEN*/)
    #endif
	    delay_srv_10ms(300); //nono 2004-3-27 16:27 for auto_poweroff.
	else
#endif
	    delay_srv_10ms(20);
#else//SAFE_AUTO_POWEROFF
	delay_srv_10ms(20); // wait for led to be turned off
#endif//SAFE_AUTO_POWEROFF
}

static inline void 
vfd_sleep(void)
{
#ifdef QISHENG_DVD
	do
	{		
		delay_srv_10ms(1);
		polling_vfdr();
		printf("<%d>",standby_cnt);	
		
	}while(standby_cnt);
#endif 	
}

static inline 
void disable_intr(void)
{
    // disable interrupt
    cpu_intr_disable();
    regs0->intr_mask = 0;
    regs0->intr_flag = -1;
}

#ifdef RISC_ALIVE_STANDBY  // 2004/10/01 yltseng

#ifdef SUPPORT_VFD//nono 2004-10-10 22:30
static inline 
UINT32  GetVFDKeyData()
{
    UINT8  vfd_key_data1;
    UINT8  vfd_key_data2;
    UINT8  vfd_key_data3;
    UINT32  vfd_key_data=0;
    UINT32  temp;
    UINT8   i;
    
    if((regs0->iop_data[1]&0x0080)==0x0080)     // vfd key data has been received
    {
        regs0->iop_data[1]&=~(0x0080);
        vfd_key_data1=(BYTE)((regs0->iop_data[1]&0xff00)>>8);
        vfd_key_data2=(BYTE)((regs0->iop_data[2]&0xff00)>>8);
        vfd_key_data3=(BYTE)((regs0->iop_data[4]&0xff00)>>8);        
        vfd_key_data=( vfd_key_data1|(vfd_key_data2<<8)|(vfd_key_data3<<16) );
        
        if(vfd_key_data!=0x00ffffff)// lijd 2004-10-11 13:09,modify for press power key but don't power off.
        for(i = 0; i < 24; i++)
        {
            temp = 0x01 << i;
            if(vfd_key_data & temp)
            {
                if (vfd_key_data > temp) // Robert 030224 for preventing illegal key_data
                {
                    vfd_key_data = 0;
                    break;
                }
                else
                {
                    vfd_key_data = i + 1;
                    break;
                }
            }
        }
        //psprintf(linebuf,"vfd: %d\n",vfd_key_data); UART0_puts(linebuf);
    }
    
    return vfd_key_data;
}
#endif//#ifdef SUPPORT_VFD//nono 2004-10-10 22:30

static inline 
void sleep_EASTECH_3240_WAKE_UP(void)
{
#ifdef EASTECH_3240_WAKE_UP

   #ifdef STBY_CONTROLLER_IO_61PIN_12GPIO
	GPIO_M_SET(12,1);  	//pin 61 gpio 12 s-by
	GPIO_E_SET(12,1);  	//pin 61 gpio 12 s-by
    GPIO_O_SET(12,0);  	//pin 61 gpio 12 s-by
   #endif
	GPIO_M_SET(GPIO_WAKE_UP_INPUT,1);  	//VFD_CLK pin72		
	GPIO_E_SET(GPIO_WAKE_UP_INPUT,0);   	//AS input
	GPIO_M_SET(GPIO_WAKE_UP_OUTPUT,1);  	//VFD_DATA  pin74		
	GPIO_E_SET(GPIO_WAKE_UP_OUTPUT,1);   	//AS output

	GPIO_O_SET(GPIO_WAKE_UP_OUTPUT,0);	//
#endif//#ifdef EASTECH_3240_WAKE_UP	
}

#ifdef ORITRON_RECEIVER_5105
static inline
void sleep_GPIO10_LOW(void)
{
    #ifdef STBY_CONTROLLER_IO_58PIN_10GPIO      //for OP hongfeng 2005-07-14
        GPIO_M_SET(10,1);   //pin 58 gpio 10 s-by
        GPIO_E_SET(10,1);   //pin 58 gpio 10 s-by
        GPIO_O_SET(10,0);    //pin 58 gpio 10 s-by
    #endif  //STBY_CONTROLLER_IO_58PIN_10GPIO
}

static inline
void power_on_GPIO10_HIGH(void)
{
    #ifdef STBY_CONTROLLER_IO_58PIN_10GPIO      //for OP hongfeng 2005-07-14
        GPIO_M_SET(10,1);   //pin 58 gpio 10 s-by
        GPIO_E_SET(10,1);   //pin 58 gpio 10 s-by
        GPIO_O_SET(10,1);    //pin 58 gpio 10 s-by
    #endif  //STBY_CONTROLLER_IO_58PIN_10GPIO
}

#endif  //ORITRON_RECEIVER_5105

#ifdef HANYANG_DP02CD_WG_8202S_16//added by wangwei,2005-3-14 12:29        
static inline 
UINT16 sleep_HANYANG_DP02CD_WG_8202S_16(void)
{    
    UINT8 key_data_pre = 0xff;    
    
    while(GetIRCode() != IRC_POWER)
    {
        if(standby_scan_power_key_and_light() == 0)  key_data_pre = 0;        
        if((key_data_pre == 0) && (standby_scan_power_key_and_light() == 1))
        {
           while(standby_scan_power_key_and_light() == 1);
           break;
        }        
    }
    
    return IRC_POWER;               
}
#endif//HANYANG_DP02CD_WG_8202S_16


static inline 
UINT16 sleep_vfd(void)
{
#ifdef SUPPORT_VFD//nono 2004-10-10 22:30    
    UINT32  key_data;
    
    key_data=GetVFDKeyData();   //lijd 2004-9-28 17:09
    //hwif_printf("<key_data:%x>",key_data);
    
    if( (key_data<=40)&&(key_data>=1) )  return vfd_keycode[key_data - 1];             
    else
    {
        return IR_CODE_MAX_NUM;
    }
#else
    return IR_CODE_MAX_NUM;
#endif
}

static inline 
void sleep_STBY_CONTROLLER_IO_61PIN_12GPIO(void)
{
    #ifdef STBY_CONTROLLER_IO_61PIN_12GPIO
	GPIO_M_SET(12,1);  	//pin 61 gpio 12 s-by
	GPIO_E_SET(12,1);  	//pin 61 gpio 12 s-by
    GPIO_O_SET(12,1);  	//pin 61 gpio 12 s-by

	GPIO_M_SET(21,1);GPIO_E_SET(21,1);GPIO_O_SET(21,1);
	GPIO_M_SET(22,1);GPIO_E_SET(22,1);GPIO_O_SET(22,1);
	GPIO_M_SET(23,1);GPIO_E_SET(23,1);GPIO_O_SET(23,1);
	GPIO_M_SET(21,1);GPIO_E_SET(21,0);
	GPIO_M_SET(22,1);GPIO_E_SET(22,0);
	GPIO_M_SET(23,1);GPIO_E_SET(23,0);
	#endif
}

#ifdef SLEEP_RISC_ALIVE_DBG
static inline 
void sleep_risc_alive_chk_key_dbg(UINT16 rx)
{
    static int i=0;
          
    if( rx != IR_CODE_MAX_NUM )
    {
        hwif_printf("<%x,%x>",rx,IR_CODE_MAX_NUM);        
    }else
    {
        if(i>50000)
        {
            hwif_printf(".");
            i=0;
        }
    }
    
    i++;
} 
#endif        
#ifdef DP2070_KEY_SCAN      
// mimitsai merge from dp2070/dp3240
// V3.2 ylseng
UINT8 g_uiFirstTime2 = TRUE;
UINT8 g_uiPowerActive2 = TRUE;
#endif
      

#ifdef OP_4110_SCAN_KEY_USE_GPIO//lijd 2005-7-4 20:34
static inline 
BYTE Check_panel_open_play_key(void)
{
	UINT8  key_data,key_data1,key_data2,key_data3;
    static BYTE key_state = 0;
    static BYTE Flag = 0;
    BYTE   Rtn_key_value=0;
    key_data1 = (BYTE)(regs0->gpio_in[CLK / 16] & (0x1 << (CLK % 16)));
    key_data2 = (BYTE)(regs0->gpio_in[STB / 16] & (0x1 << (STB % 16)));
    key_data3 = (BYTE)(regs0->gpio_in[DAT / 16] & (0x1 << (DAT % 16)));   
    key_data =(key_data1|key_data2|key_data3);
    key_data= key_data >> 5;
    if(key_data==0x07) Flag=0;
    if(Flag!=1)
    {
        switch (key_data)
        {
	        case 0x01://SW1
	             Rtn_key_value=IRC_EJECT;
	             Flag=1;
	             break; 
	        case 0x03://SW3
	        	 Rtn_key_value=IRC_PLAY_RESUME;
	             Flag=1;
	             break; 
	    }
    }   
    return Rtn_key_value; 
}
#elif defined(OP_5112_SCAN_KEY_USE_GPIO)//lijd 2005-7-4 20:34
static inline 
BYTE Check_panel_open_key(void)
{
	UINT8  key_data,key_data1,key_data2,key_data3;
    static BYTE key_state = 0;
    static BYTE Flag = 0;
    BYTE   Rtn_key_value=0;
    key_data1 = (BYTE)(regs0->gpio_in[CLK / 16] & (0x1 << (CLK % 16)));
    key_data2 = (BYTE)(regs0->gpio_in[STB / 16] & (0x1 << (STB % 16)));
    key_data3 = (BYTE)(regs0->gpio_in[DAT / 16] & (0x1 << (DAT % 16)));   
    key_data =(key_data1|key_data2|key_data3);
    key_data= key_data >> 5;
    if(key_data==0x07) Flag=0;
    if(Flag!=1)
    {
        switch (key_data)
        {
	        case 0x06://SW1
	             Rtn_key_value=IRC_EJECT;
	             Flag=1;
	             break; 	       	                      
	    }
    }   
   return Rtn_key_value;
}
#elif defined(OP_5116_SCAN_KEY_USE_GPIO)//lijd 2005-7-4 20:34
static inline 
BYTE Check_panel_open_key(void)
{
	UINT8  key_data,key_data1,key_data2,key_data3;
    static BYTE key_state = 0;
    static BYTE Flag = 0;
    BYTE   Rtn_key_value=0;
    key_data1 = (BYTE)(regs0->gpio_in[CLK / 16] & (0x1 << (CLK % 16)));
    key_data2 = (BYTE)(regs0->gpio_in[STB / 16] & (0x1 << (STB % 16)));
    key_data3 = (BYTE)(regs0->gpio_in[DAT / 16] & (0x1 << (DAT % 16)));   
    key_data =(key_data1|key_data2|key_data3);
    key_data= key_data >> 5;
    if(key_data==0x07) Flag=0;
    if(Flag!=1)
    {
        switch (key_data)
        {
	        case 0x06://SW1
	             Rtn_key_value=IRC_EJECT;
	             Flag=1;
	             break; 	       	                      
	        case 0x03://SW3
	        	 Rtn_key_value=IRC_PAUSEPLAY;
	             Flag=1;
	             break;  	       	                      
	    }
    }   
   return Rtn_key_value;
}
#endif      
#ifdef SUPPORT_DVB_BOOKING
#include "timer.h"
#include "..\dvb_h\sp_dtv.h"
#include "..\dvb_menu\sunplus_std\Dvb_booking.h"
#include "fsNAV.h"
#endif
//use define RISC_ALIVE_STANDBY
static inline 
void system_stdy_sleep_risc_alive(void)
{ 
    hwif_printf("system_stdy_sleep_risc_alive,in\n");
    
    hwif_reset_sleep2(1);
    regs0->sft_cfg2 &= ~(1<<1);
    regs0->iop_data[6] = 0;
    regs0->iop_data[IR_PORT]=0xff;
    
// mimitsai merge from dp2070/dp3240
#ifdef EASTECH_2070_WAKE_UP
	GPIO_M_SET(GPIO_WAKE_UP_INPUT,1);  	//VFD_CLK pin72		
	GPIO_E_SET(GPIO_WAKE_UP_INPUT,0);   	//AS input
	GPIO_M_SET(GPIO_WAKE_UP_OUTPUT,1);  	//VFD_DATA  pin74		
	GPIO_E_SET(GPIO_WAKE_UP_OUTPUT,1);   	//AS output

	GPIO_O_SET(GPIO_WAKE_UP_OUTPUT,0);	//
#endif	
	
#ifdef DP2070_KEY_SCAN
    //#define PLAY_LED_1   12  //PIN 61           
    //#define  POWERON_LED_0  14
    //GPIO_O_SET(PLAY_LED_1, 0);
    //GPIO_O_SET(POWERON_LED_0, 1);
    #define KEY_GPIO_21 21  //pin 72
    #define KEY_GPIO_22 22  //pin 73
    #define KEY_GPIO_23 23  //pin 74
#endif

#ifdef DP2070_KEY_SCAN
    //GPIO_O_SET(PLAY_LED_1, 0);
    GPIO_E_SET(KEY_GPIO_21,0) ; 
    GPIO_E_SET(KEY_GPIO_23,0) ; 
  
    GPIO_E_SET(KEY_GPIO_22,1) ; 
    GPIO_O_SET(KEY_GPIO_22,0) ; 
#endif

#ifdef  DRAM_TEST
#include "tstsdram.c"//terry,2005/4/4 07:16と

    test_sdram();
#endif
    
    #ifdef ORITRON_RECEIVER_5105    //hongfeng 2005-07-14
    sleep_GPIO10_LOW();
    #endif
    sleep_EASTECH_3240_WAKE_UP();

#ifdef  AWAKE_SLOWDOWN        
    hwif_printf("Note:> baud rate be seeting to 9600...\n");
#endif
    
#ifdef SUPPORT_DVB_BOOKING
regs0->stc_divisor = ((6.75 * 1000000)/90000+0.5)-1;  /// <------- add this line 
//int i=0;
UINT32 booking_start_t;
unsigned diff,rtc;  
booking_start_t =  get_rtc_val();
//int iii=0;
#endif
    hwif_printf("check power key,in\n");
    while(1)
    {       
       UINT16 rx,vfd __UNUSED;
       
       rx = GetIRCode();
               
#if defined(MUSTEK_K100D_MODEL)
       
       #ifdef USE_DEMUX_GPIO_WHEN_STANDBY
       DMX_GPIO_E_SET(LED_CONTROL_GPIO,1);
       DMX_GPIO_O_SET(LED_CONTROL_GPIO,0);
       #endif
       
#if defined(PDVD_USE_IO_SCAN_KEY)
       /*.....................................................................................................
        by justin 2005/09/14
        for key_power 
        let it power on 
        ......................................................................................................*/
        GPIO_E_SET(POWER_KEY_GPIO,0);
	   
	    if(GPIO_I_GET(POWER_KEY_GPIO))
		  rx = IRC_POWER;     
#endif
#endif//end #if defined(MUSTEK_K100D_MODEL)

       //hwif_printf("<ir:%x>",rx);
#ifdef SUPPORT_VFD//nono 2004-10-10 22:30
       vfd= sleep_vfd();        
       //hwif_printf("<vfd:%x>",vfd);
       
       if(vfd!=IR_CODE_MAX_NUM) rx=vfd;
#endif//SUPPORT_VFD

// mimitsai merge from dp2070/dp3240
    #ifdef DP2070_KEY_SCAN
        if(GPIO_I_GET(KEY_GPIO_23)==0)
        {          
            if( g_uiPowerActive2 )
            {
                if( g_uiFirstTime2 )
                {
                    g_uiFirstTime2      = FALSE;
                    g_uiPowerActive2    = FALSE;
                    continue;
                }
                rx=IRC_POWER;
            }
        }
        else
        {
            g_uiFirstTime2   = FALSE;
            g_uiPowerActive2 = TRUE;
        }
    #endif  //#ifdef DP2070_KEY_SCAN

#ifdef SLEEP_LED_FLASH
	static UINT16 stby_led_cnt_i=0,stby_led_cnt_j=0;
	static BYTE sleep_led_flag=0;
	
	stby_led_cnt_j ++;
	if(stby_led_cnt_j>=512) 
    	{
    		stby_led_cnt_j=0;
    		stby_led_cnt_i++;
    		if(stby_led_cnt_i>=255) 
    		{
    			stby_led_cnt_i=0;
				if(sleep_led_flag)
				{
					sleep_led_flag=0;
					GPIO_O_SET(POWER_LED_2,1);	
				}
				else
				{
					sleep_led_flag=1;
					GPIO_O_SET(POWER_LED_2,0);	
				}
			}
		}   
#endif

#ifdef HANYANG_DP02CD_WG_8202S_16//added by wangwei,2005-3-14 12:29        
       rx=sleep_HANYANG_DP02CD_WG_8202S_16();
#endif       
        
#ifdef OP_4110_SCAN_KEY_USE_GPIO//lijd 2005-7-4 20:34
    BYTE ScanKeyValue=0;
	ScanKeyValue=Check_panel_open_play_key();
	if(ScanKeyValue!=0) rx=ScanKeyValue;
#elif defined(OP_5112_SCAN_KEY_USE_GPIO)//lijd 2005-7-4 20:34 
	BYTE ScanKeyValue=0;
	ScanKeyValue=Check_panel_open_key();
	if(ScanKeyValue!=0) rx=ScanKeyValue;
#elif defined(OP_5116_SCAN_KEY_USE_GPIO)//caoh 2005-7-27 22:14
	BYTE ScanKeyValue=0;
	ScanKeyValue=Check_panel_open_key();
	if(ScanKeyValue!=0) rx=ScanKeyValue;	
#endif   
        
#ifdef GBM_AP_DVD_16//8200 pin135,STOP KEY wake up,added by wangwei,2005-2-25 10:20
    if(!GPIO_I_GET(42))  rx=IRC_POWER;   
#endif//GBM_AP_DVD_16

#ifdef OP_5121_POWER_KEY  
  if(!GPIO_I_GET(38))  rx=IRC_POWER;   
#endif 

#ifdef EASTECH_3240_WAKE_UP
		if(!GPIO_I_GET(GPIO_WAKE_UP_INPUT))	 rx=IRC_POWER;      
#endif//#ifdef EASTECH_3240_WAKE_UP 

#ifdef SLEEP_RISC_ALIVE_DBG
        sleep_risc_alive_chk_key_dbg(rx);
#endif        

#ifdef SUPPORT_DVB_BOOKING
    rtc = get_rtc_val();
    diff=rtc-booking_start_t; 
    if(diff==100)
    {
        booking_start_t = get_rtc_val();
        count_current_time();
        int iRst=check_the_time();
        if(iRst>=0)
        {
            volatile int *iMagic=(int *)(DATA_RAM_BASE|0xa0);
            *iMagic = iRst;
            //WriteToI2c(0xa0, I2C_ADDR_BOOK_IDX_FLAG, &iRst, 1);		  
            rx = IRC_POWER;
        }    
    }
#endif      
        switch( rx )
        {
#ifndef EASTECH_OPEN_KEY_DNOT_POWER_ON
            case IRC_EJECT:
            {
                volatile int *iMagic=(int *)(DATA_RAM_BASE|0x80);
                *iMagic = 0x1881;
            }
#endif

#if defined(ORITRON_8202D_3111_DVD)||defined(ORITRON_8202D_4110_DVD)||defined(ORITRON_8202D_4119_DVD)||defined(ORITRON_8202D_5112_DVD)||defined(ORITRON_8202D_5116_DVD)||defined(ORITRON_8202D_5122_DVD)||defined(ORITRON_8202D_5121_DVD)||defined(ORITRON_8202D_6122_DVD) //LIJD 2005-7-4 16:51     
		    case IRC_PLAY_RESUME:
#endif
#if defined(ORITRON_8202D_5116_DVD)||defined(ORITRON_8202D_5117_DVD)      
          case IRC_PAUSEPLAY:
  #endif
            case IRC_POWER:                
                #ifdef SUPPORT_DVB_BOOKING 
                remember_current_time();    
                #endif         
	            sleep_STBY_CONTROLLER_IO_61PIN_12GPIO();		        
                    #ifdef ORITRON_RECEIVER_5105    //hongfeng 2005-07-14
                    power_on_GPIO10_HIGH();
                    #endif
	            //regs0 -> reset2 = (0x01<<15)|(0x01<<4);	            
                __boot_entry();            	
                break;            
        }
    }
}
#endif//#ifdef RISC_ALIVE_STANDBY








#ifdef HK_ORITRON_PANNEL//lijd 2005-5-26 14:01
extern void SendDataToSM1623LED(void);
BYTE	vfd_mem[14];
#endif

#ifdef MULTIDISC_LOADER//chenzhao20060112
    #include "multidisc_loader.h"
#endif

/*
*  system_stdy_sleep
*/
static inline void system_stdy_sleep(void)
{    
    sspll_reg_restore();        // 2006/09/22 yltseng

#ifdef POWER_OFF_ONLY_VIDEO_DAC_OFF
   tv_mode5 = regs0->tv_mode[5];
#endif
#ifdef SUPPORT_LINE_OUT_MUTE	//FCR 2005-10-25 13:51
	mute_line_out();
#endif	

#ifdef OP_SWITCH_MODE_MUTE_AMP	//fcr 2005-10-25 13:51
	sub_masterMute(1);   
#endif


#ifdef SPHE1000
   disable_tv();
   if (bDev & DVD_LOADER_EXIST) 
   {
     close_tray_func();
     atapi_standby_mode();
   }
#else//#ifdef SPHE1000
   disable_tv();
    #if defined(HK_ORITRON_PANNEL)&& !defined(OP_5116_SCAN_KEY_USE_GPIO)&& !defined(OP_5112_SCAN_KEY_USE_GPIO)&&!defined(OP_4110_SCAN_KEY_USE_GPIO)//lijd 2005-5-26 14:01
     int i;
     delay_srv_10ms(20);
	 for(i = 0; i < 14; i++)				
		vfd_mem[i] = 0x00;	
	    SendDataToSM1623LED();	
    #endif
    #ifdef DVD_5_DISC_RESUME//lijd 2005-6-9 14:56
    if((cd_type_loaded==CDDVD)&&(StopTimes==0))//lijd 2005-6-30 13:31  
    {  
		RSM_Flag =0;
    	if((pDSV->CurrDomain != VTSM_DOM)&&(pDSV->CurrDomain != VMGM_DOM)&&(pDSV->CurrDomain != FP_DOM))//lijd 2005-7-6 21:27
    	{
	ircmd_stop();
	LoadModual(MODUAL_CDROM); 	
		resumeMSF = 1;  
        RsmInfo2Flash(0);
    }
    }
    else if((cd_type_loaded==CDDVD)&&(StopTimes==1))
    {
    	if((pDSV->CurrDomain != VTSM_DOM)&&(pDSV->CurrDomain != VMGM_DOM)&&(pDSV->CurrDomain != FP_DOM))//lijd 2005-7-6 21:27
    	{
    	resumeMSF = 1; 
		LoadModual(MODUAL_CDROM); 		 
        RsmInfo2Flash(0); 
    }    
    } 
    else if((cd_type_loaded==CDDVD)&&(StopTimes==2))//lijd 2005-8-1 13:56
    {
    		ircmd_stop();
    	   	resumeMSF = 0; 
	 	 LoadModual(MODUAL_CDROM); 	 
	        RsmInfo2Flash(0); 
	 }	 
    #endif
   
   	#ifdef SUPPORT_OP_REGION_UI//libing 2005-8-25 10:58
   	    WriteToI2c(0xa0, ADDR_I2C_REGION_CODE_PWD,(BYTE* )(&UserSet.P_RCD),1);
   	#endif    
   
	#ifdef ORITRON_TRAY_PASSWORD
		WriteToI2c(0xa0, ADDR_I2C_TRAY_PWD, &tray_flag, 1);
	#endif

#if defined(TOP_DOOR_LOADER) || defined(CHECK_PORTABLE_OPCLSW) //Jack added 04/10/10
   #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB  
   if((source_play_mode==DVD_PLAY_MODE) || ((old_play_state!=VCD_STATE_OPEN) && (old_play_state!=VCD_STATE_IDLE) /*&& (!((old_play_state==VCD_STATE_STOP)&&(!resumeMSF)))*/))
   #else
   if((old_play_state!=VCD_STATE_OPEN) && (old_play_state!=VCD_STATE_IDLE) /*&& (!((old_play_state==VCD_STATE_STOP)&&(!resumeMSF)))*/)
   #endif
   atapi_standby_mode();
#elif defined(SUPPORT_OP_FIVE_DISC)//chenzhao20060107
   standby_to_close_fun(); 
   #ifdef SUPPORT_UPD68A_READY_PIN
   SET_UPD68A_READY_POWER_OFF(); //to standby 
   #endif
#else
   close_tray_func();   
   atapi_standby_mode();
#endif

//nono move it.(power off couldn't tray in when tray out.)4-12-29 22:28
//   servo_turn_off();//caohui 2004-11-26 16:54	For limit Power
#endif//#ifdef SPHE1000

#ifdef SUPPORT_DVB_BOOKING   //sunzhh add 2006-8-9 09:30下午
if(pFsJpeg->gifsFuncBtn==FS_FUNC_JPEG) 
{
	volatile int *iMagic=(int *)(DATA_RAM_BASE|0xa0);
	extern int iMagicdata;
	*iMagic=(int *)(DATA_RAM_BASE|0xa0);
	//printf_w("$$$$$$$$$$$$$$$$$$$$$ *iMagic = %d \n",*iMagic);
	*iMagic=iMagicdata;
	//printf_w("$$$$$$$$$$$$$$$$$$$$$ *iMagic = %d \n",*iMagic);
}
#endif

#ifndef POWER_OFF_ONLY_VIDEO_DAC_OFF
#ifdef TP6317_PANNEL		//yaowh add 04-10-25
	define_standbykey();
	TP6317_Power = 2 ;// flag
#endif
   led_light();   
   GPIO_MUTE();
   disable_scart_tv();
#ifdef DVD_SERVO
   servo_sleep();
#endif   
   vfd_sleep();	

#ifdef TP6317_PANNEL		//yaowh add 04-10-25
	Power_off_define_TP6317_standbykey();
	delay_srv_10ms(20);
#endif


#ifdef CONTROL_STANDBY_MCU//lijd 2005-5-26 17:58
	 // reset iop
     regs0->iop_control = 1<<0;
#ifdef CONTROL_DVD5121_POWER_GPIO
       regs0->sft_cfg0 &= ~(0x1 << 5);   // qinhua ,i don't know why ,if not define,don't put low.
      GPIO_M_SET(CONTROL_POWER_GPIO,1);   
      GPIO_E_SET(CONTROL_POWER_GPIO,1);
   	 GPIO_O_SET(CONTROL_POWER_GPIO,0);   	
#else       
    
   	 GPIO_O_SET(CONTROL_POWER_GPIO,0);   	
#endif    	
   	 while(1);
#endif   	 

#ifdef NO_CONTROL_POWER_MCU
	 GPIO_O_SET(CONTROL_POWER_GPIO,0);  
#endif 
	 
#ifdef PMP_MCU810   
      //send power cmd
      write_pmp_mcu810(CMD_PMP_POWER_OFF,0);
      while(1);

#else//#ifdef PMP_MCU810   

#ifdef SUPPORT_UPD68A_READY_PIN //solve when power on/off VFD has some strang flash hongfeng 2005-10-13
	SET_UPD68A_READY_LOW();
    #ifdef SUPPORT_MCU_68A	//fcr2005-10-26 14:34 
    while(1);
    #else
       reset_iop(); 
    #endif
#else
    reset_iop(); 
#endif

#ifdef PULIANG_DVD  //yaowh add for 320DVD 04-12-17
    regs0->gpio_master[35 / 16] |= (0x1 << (35 % 16));
	GPIO_E_SET(35,1);
	GPIO_O_SET(35,0);
	
    regs0->sft_cfg1 &= ~(0x1 << 2); //ROM_CS3 as GPIO 36, pin 71
    regs0->gpio_master[36/16] |= (0x1<<(36%16));
	GPIO_E_SET(36,1);
	GPIO_O_SET(36,1);
	
   regs0->sft_cfg3 &= ~(0x1 << 5); // AU4 as GPIO 57, pin163
    regs0->gpio_master[57/16] |= (0x1<<(57%16));
	GPIO_E_SET(57,1);
	GPIO_O_SET(57,0);
#endif

#if defined(USE_GAMEPORT_TO_DISCLIGHT)
    init_light_io_out();
#endif
    // wait until device turn-off
    delay_1ms(100);
    disable_intr();

#ifdef DVD_SERVO_REAL_TURN_OFF
//nono move it here.(power off couldn't tray in when tray out.)4-12-29 22:28
   servo_turn_off();//caohui 2004-11-26 16:54	For limit Power
#endif//DVD_SERVO_REAL_TURN_OFF

#ifdef SUPPORT_DVD_POWER_ONOFF
    dvd_power_onoff(TURN_OFF);
#endif

#ifdef RISC_ALIVE_STANDBY   // 2004/10/01 yltseng
    system_stdy_sleep_risc_alive();
#elif defined(STANDBY_GPIO_STILL_ON)    //2004-10-10 14:11 wanghaoying for thakral only
    system_standby_gpio_still_on();
#else
    hwif_reset_sleep();
#endif

#endif//#ifdef PMP_MCU810   
#else //POWER_OFF_ONLY_VIDEO_DAC_OFF
    // wait until device turn-off
    delay_1ms(100);
    cpu_intr_disable();
    hwif_reset_sleep3();
#endif //POWER_OFF_ONLY_VIDEO_DAC_OFF
}



#if defined(STANDBY_GPIO_STILL_ON)
static inline void system_standby_gpio_still_on(void)
{
    //wanghaoying add as nono told 2004-9-27 20:39
    // go sleep-await function. (cached region)
    {
        extern void hwif_reset_sleep2(int);
        void (*vf)(int);
        vf = hwif_reset_sleep2;  //、、、、、、、、、、
        //vf = (void *)(0xA0000000 | (UINT32)vf); 
        vf(1);
    }

    UINT16 rx,pin36;  
    //rx为IR键值，pin36为连接Power 键的GPIO口
    //in fact, we should call it gpio36 not pin36
    static UINT8 timer = 0x08;  //the value is random got, but need to balance the clock
    
    regs0->sft_cfg2 &= ~(1<<1);
    regs0->iop_data[6] = 0;
    regs0->iop_data[5]=0xff;
    
    printf("\n\n\ncall syttem_standby sleep\n\n\n");
           
//            do   //Power键 
//            {
//               pin36=GPIO_I_GET(36); 
//               //psprintf(linebuf,"pin56:%d\n",pin56); UART0_puts(linebuf);
//            }while(pin36==0);

    while(1)
    {
        GPIO_M_SET(36,1);  //设置GPIO36为RISC控制
        GPIO_E_SET(36,0);   //设置GPIO36为输入口
        
        GPIO_M_SET(35,1);   //set gpio35 controled by RISC
        GPIO_E_SET(35,1);   //set gpio35 output pin

        rx = regs0->iop_data[5];   //读取IOP所传送键值

        GPIO_O_SET(35,0);
        pin36=GPIO_I_GET(36);         //获取Power键状态
        
        timer--;
    
        //psprintf(linebuf,"%d pin56:%d\n",rx,pin36); UART0_puts(linebuf);
    
        //如果按下IR的Power键或者VFD面板的Power键就唤醒系统
        if((rx==242)||(pin36==0))  
        {
            //hwif_reset_all();  //从standby模式转入normal模式，唤醒系统
            __boot_entry();
            break;
        }
           
        if(timer==0)
        {
            timer = 0x10;
            while(1)
            {
                
                GPIO_M_SET(35,1);
                GPIO_E_SET(35,1);
                GPIO_O_SET(35,1);

                GPIO_M_SET(36,1);
                GPIO_E_SET(36,1);
                GPIO_O_SET(36,1);
                timer--;
                if(timer==0)
                {
                    timer = 0x08;
                    break;
                }
            }        
        }
    }
}
#endif  //#if defined(STANDBY_GPIO_STILL_ON)



//
// FUNCTION
// system_sleep
//
void system_sleep()
{    
    
#ifdef SUPPORT_SPI_FLASH
    system_sleep_flash_setup();
#endif
        
#ifdef SUPPORT_TUNER
   system_tuner_sleep();
#else  
   system_stdy_sleep();
#endif 
}

void system_wakeup()
{
#ifdef POWER_OFF_ONLY_VIDEO_DAC_OFF
	regs0->tv_mode[5]=tv_mode5;
	regs0->sft_cfg6  &= ~(1<<12);
	regs0->reset2 &= ~ (
	    (1<<14)
	    );
	cpu_intr_enable();
#endif
}
//-------------------------------------------  ending  ---------------------------------------

