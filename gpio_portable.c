/*
----->included&called by gpio.c
----->only for portable dvd use.
----->did it on 2004/07/25
*/
#ifdef  SUPPORT_dvd_power_onoff
extern void  dvd_power_onoff(BYTE  onoff);
#endif
#if defined(SUPPORT_TUNER_POWER_ONOFF)&&!defined(TUNER_POWER_SW_USE_DEMUX_GPIO)
#include "..\\dvb_h\\dmx_6600_gpio.h"
#endif

void portable_reset_gpio(void)
{
#ifndef SPHE8202    
    regs0->sft_cfg0 &= ~(0x3fff << 1);  //Disable ra20~ra26 pin 129~131, pin 133~136
    regs0->sft_cfg2 &= ~(0x08<<5);      //GPIO 46 pin143.
    //regs0->sft_cfg3 &= ~((0x07)<<3);  //Disable AUD1,2,3,4 (GPIO59,60,57)
    regs0->sft_cfg6 &= ~((0x03)<<7);    //Disable DQM2,3 for pin139,140
    regs0->sft_cfg6 &= ~(0x1 << 5);     //SA12 as GPIO 18, pin 151
    
    regs0->sft_cfg3 |= ((0x17)<<3);
    
    if(PDVD_OPCLSW_GPIO == 16)
      regs0->sft_cfg6 &= ~((0x02)<<7);
    
	#ifdef PNGPIO_CON_TFT
    PALNTSC_GPIO_INIT(); //P/N_KEY is output
    #endif
#else	//for 8202P Portable DVD
    regs0->sft_cfg1 &= ~((0x11)<<1);    //for Disable ROM_CS2(GPIO18),ROM_A22(GPIO94)
    regs0->sdc_data_cnt[6][0] |= (0x0e);//Disable ROM_A20(Pin225),ROM_A21(Pin226),ROM_A22(Pin227) as GPIO92,93,94  
    #ifndef TRAY_AVAILABLE//Jack added 06/04/11
    regs0->sft_cfg4 &= ~((0x03)<<2);    //Enable GPIO2,3
    #endif
    
    #ifdef TWO_CHANNEL_ONLY
    regs0->sft_cfg3 &= ~((0x27)<<2);    //Disable SPDIF_IN,AUD1,2,3(GPIO51,54,55,56)
    #else
    regs0->sft_cfg3 &= ~((0x20)<<2);    //Disable SPDIF_IN/OUT(GPIO51)
    #endif
    
#if defined(SUPPORT_DVD_POWER_ONOFF)
    GPIO_M_SET(DVD_POWER_SW_GPIO,1);  
    GPIO_E_SET(DVD_POWER_SW_GPIO,1);
    #ifndef SUPPORT_8202_DVB//at first need know the current system_state
    dvd_power_onoff(TURN_OFF);  //rbhung turn on VCC5 power
    #endif
#endif    
    
#ifdef EASTWIN 
   regs0->sft_cfg3 &= ~((0x01)<<1);    //Disable AUD0(GPIO53)
#endif
    
    #ifdef SUPPORT_SLOT_IN_LOADER    
    GPIO_M_SET(6,1);	//TRAY_IS_IN_GPIO	99
    GPIO_E_SET(6,0);
	GPIO_M_SET(18,1);	//TRAY_IS_OUT_GPIO	98
	GPIO_E_SET(18,0);
    GPIO_M_SET(55,1);	//DISC_IS_IN_GPIO	100
	GPIO_E_SET(55,0);
    #endif

    #ifdef TR0QS3_SLM
	GPIO_M_SET(97,1);	//TRAY_IS_IN_GPIO	6
	GPIO_E_SET(97,0);
    GPIO_M_SET(98,1);	//TRAY_IS_OUT_GPIO	71
    GPIO_E_SET(98,0);
    GPIO_M_SET(99,1);
	GPIO_E_SET(99,0);	//DISC_IS_IN_GPIO	70
	GPIO_M_SET(100,1); 
    GPIO_E_SET(100,0);
    GPIO_M_SET(93,1); 
    GPIO_E_SET(93,0); 
    #endif
#endif        
      
	#ifdef TEAC_PORTABLE_DVD
    	#ifdef SRV_GPIO_FOR_216
    		regs0->sft_cfg4 &= ~((0x1)<<6);//Enable GPIO8
    		regs0->sft_cfg0 &= ~((0x1)<<5);//Enable GPIO38	    	
    		
    		GPIO_M_SET(8,1);
    		GPIO_E_SET(8,0);
    		GPIO_M_SET(72,1);
    		GPIO_E_SET(72,0);
    		GPIO_M_SET(23,1);
    		GPIO_E_SET(23,0);
    		GPIO_M_SET(38,1);
    		GPIO_E_SET(38,0);
    		GPIO_M_SET(70,1);
    		GPIO_E_SET(70,0);    	
    	#endif	
	#endif


#ifdef GBM_PORTABLE_DVD		//rbhung for GBM Portable DVD
    //Jack moved gpio setting for all portable dvd customers.06/06/16
    regs0->sft_cfg3 &= ~((0x07)<<3);    //Disable AUD1,2,3,4 (GPIO59,60,57)
    
    regs0->gpio_master[1]|= 0x0027;    //GPIO 16,17,18,21
    regs0->gpio_oe[1]|= 0x0022;
    regs0->gpio_oe[1]&= ~(0x0005);
    regs0->gpio_out[1]&= ~(0x0022);
    regs0->gpio_master[2]|= 0xffe0;    //GPIO 37~47
    regs0->gpio_oe[2]|= 0xe980;        //jhuang org 29c0
    regs0->gpio_oe[2]&= ~(0x1660);     //jhuang org d620
    regs0->gpio_out[2]|= 0x0900;
    regs0->gpio_out[2]&= ~(0xe080);    
    regs0->gpio_master[3]|= 0x1f1f;    //GPIO 48~52,56~60
    regs0->gpio_oe[3]|= 0x1e03;        //jhuang org 1e00
    regs0->gpio_oe[3]&= ~(0x011c);     //jhuang org 011f
    regs0->gpio_out[3]|= 0x1600;
    regs0->gpio_out[3]&= ~(0x0803);
    
    #ifndef PDVD_10INCH_QSI //because 10 inch use kernel to fix.
    regs0->tv_mode[0]&=~(0x001e);//config video dac output mode(16)
    #endif
    #ifdef HOLD_KEY_DETECT
    hold_state=0;
    #endif
    powerdown_timer=0;
    lowbat_timer=0;
    
#endif

#ifdef SUNPLUS_8202P_DEMOBOARD		//rbhung for Sunplus 8202 Portable DVD Demoboard
    regs0->gpio_master[0]|= 0x000c;    //GPIO 2,3
    regs0->gpio_master[1]|= 0x00e4;    //GPIO 18,21,22,23
    regs0->gpio_master[3]|= 0x01c8;    //GPIO 51,54~56
    regs0->gpio_master[5]|= 0x7000;    //GPIO 92,93,94
    regs0->gpio_oe[0]&= ~(0x000c);
    regs0->gpio_oe[1]|= 0x0004;
    regs0->gpio_oe[1]&= ~(0x00e0);
    regs0->gpio_oe[3]|= 0x01c8;
    regs0->gpio_oe[5]|= 0x6000;
    regs0->gpio_oe[5]&= ~(0x1000);
    regs0->gpio_out[1]|= 0x0004;
    regs0->gpio_out[3]|= 0x0140;
    regs0->gpio_out[3]&= ~(0x00c0);
    regs0->gpio_out[5]|= 0x6000;
#ifdef EASTWIN    
    regs0->sft_cfg0 &= ~(0x0080);		//config to GPIO 48   
    GPIO_M_SET(18,1);		// Kevin Jul 20,04 set battery low detect pin for RISC
    GPIO_E_SET(18,0);		// Kevin Jul 20,04 set battery low detect pin is input
    GPIO_M_SET(48,1);		// Kevin Jul 20,04 set shutdown amp pin for RISC
    GPIO_E_SET(48,1);		// Kevin Jul 20,04 set shutdown amp pin is output
    GPIO_M_SET(49,1);		// Kevin Jul 20,04 set ear detect pin for RISC
    GPIO_E_SET(49,0);		// Kevin Jul 20,04 set ear detect pin is input    
    GPIO_M_SET(97,1);		// Kevin Jul 20,04 set view mode pin for RISC
    GPIO_E_SET(97,1);		// Kevin Jul 20,04 set view mode pin is output
    GPIO_M_SET(100,1);		// Kevin Jul 20,04 set lcd power pin for RISC
    GPIO_E_SET(100,1);		// Kevin Jul 20,04 set lcd power pin is output
    //GPIO_O_SET(56,0);		// Kevin Jul 20,04 disable audio mute // Kevin Sep 21,04 move to vfd.c
    POWER_LED_OFF();		// Kevin Jul 20,04 power led off
    LCD_POWER_ON();			// Kevin Jul 20,04 lcd panel power supply turn on
    
#endif
#endif

#ifdef MUSTEK_K100D_MODEL
    regs0->sft_cfg0 &=~((0x01)<<4); //GPIO39(Pin162)Disable M_DQM2 and enable
    regs0->sft_cfg1 &= ~(0x7 << 9); //gpio33(pin 155)
    regs0->sft_cfg4 &=~((0x01)<<5); //GPIO5(pin 62) for panel power key 
    
#endif

#ifdef  CHECK_PORTABLE_OPCLSW
	GPIO_M_SET(PDVD_OPCLSW_GPIO,1);
	GPIO_E_SET(PDVD_OPCLSW_GPIO,0);	
#endif

#if defined(SUPPORT_TUNER_POWER_ONOFF)&&!defined(TUNER_POWER_SW_USE_DEMUX_GPIO)
    GPIO_M_SET(TUNER_POWER_SW_GPIO,1);
	GPIO_E_SET(TUNER_POWER_SW_GPIO,1);
#endif

}

