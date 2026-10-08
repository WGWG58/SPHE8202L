void alco_portable_reset_gpio(void)
{
    regs0->sdc_data_cnt[6][0] |= (0x0e);//Disable ROM_A20(Pin225),ROM_A21(Pin226),ROM_A22(Pin227) as GPIO92,93,94  

#if defined(PORTABLE_8200)&&defined(ALCO_PV1950)
    regs0->sft_cfg0 &= ~(0x3fff << 1);  //Disable ra20~ra26 pin 129~131, pin 133~136
    regs0->sft_cfg2 &= ~(0x08<<5);      //GPIO 46 pin143.
    regs0->sft_cfg3 &= ~((0x07)<<3);  //Disable AUD1,2,3,4 (GPIO59,60,57)
    //regs0->sft_cfg6 &= ~((0x03)<<7);    //Disable DQM2,3 for pin139,140
    regs0->sft_cfg6 &= ~(0x1 << 5);     //SA12 as GPIO 18, pin 151
    
    regs0->sft_cfg1 &= ~(0x1 << 3); //pin29 as GPIO3
    regs0->sft_cfg6 &= ~(0x1 << 4); //SA11 as GPIO 14, pin 109
    
    regs0->sft_cfg1 &= ~(0x3 << 1); //CS2,CS3--->GPIO35,GPIO36
    
    //for panel key 
    regs0->gpio_master[1]|= 0x0004;    //GPIO 18
    regs0->gpio_master[3]|= 0x01de;    //GPIO 49,50,51,52,54,55,56
    regs0->gpio_oe[1]|= 0x0004;        //GPIO 18 output
    regs0->gpio_oe[3]|= 0x01c0;		   //GPIO 54,55,56 output	
    regs0->gpio_oe[3]&= ~(0x001e);     //GPIO 49,50,51,52 inout
        
    //Cover SW    
    GPIO_M_SET(PDVD_OPCLSW_GPIO,1);
	GPIO_E_SET(PDVD_OPCLSW_GPIO,0); //input
	
	//Power LED 
	#ifdef POWER_LED_CONTROL 
	GPIO_M_SET(POWER_LED_GPIO,1); 
	GPIO_E_SET(POWER_LED_GPIO,1);  //output
	GPIO_O_SET(POWER_LED_GPIO,1);
	#endif
	
	//TFT control 
	#ifdef TFT_ONOFF_CONTROL //mark 04/11/23,do it in check_alco_portable_gpio() for tft display delay!
	GPIO_M_SET(TFT_CONTROL_GPIO1,1); 
	GPIO_E_SET(TFT_CONTROL_GPIO1,1);  //output
	GPIO_M_SET(TFT_CONTROL_GPIO2,1); 
	GPIO_E_SET(TFT_CONTROL_GPIO2,1);  //output
	#endif
	
	//Video in detect
	#ifdef VIDEO_IN_CONTROL
	GPIO_M_SET(INT_EXT_VIDEO_GPIO1,1);
	GPIO_E_SET(INT_EXT_VIDEO_GPIO1,0); //input
	GPIO_M_SET(INT_EXT_VIDEO_GPIO2,1);
	GPIO_E_SET(INT_EXT_VIDEO_GPIO2,0); //input
		#endif
	
	//ICETDI Control
	//GPIO_M_SET(ICETDI_GPIO,1);
	//GPIO_E_SET(ICETDI_GPIO,1); //output	
#endif

#if defined(PORTABLE_8202S)
#if defined(ALCO_PVS177W)//shenyj add for alco177w    
    //regs0->sft_cfg3&= ~((0x1)<<2); //enable gpio54 for avin
    regs0->sft_cfg3&= ~((0x1)<<4); //enable gpio56 AUDIO_MUTE    
    regs0->sft_cfg1&= ~((0x1)<<3); //enable gpio16(pin66)
    regs0->sft_cfg0&= ~((0x1)<<6); //enable gpio29(pin125)
    
    //for panel key use!!!
    regs0->gpio_master[0]|= 0xf000;    //GPIO 12,13,14,15
    regs0->gpio_master[1]|= 0x00e1;    //GPIO 16,21,22,23
    //regs0->gpio_oe[0]&= ~(0xf000);     //GPIO 12,13,14,15 input
    //regs0->gpio_oe[1]|= 0x00e1;        //GPIO 16,21,22,23 output
    
    //Cover SW
    regs0->sft_cfg4&= ~((0x1)<<6);    
    GPIO_M_SET(PDVD_OPCLSW_GPIO,1);
	GPIO_E_SET(PDVD_OPCLSW_GPIO,0); //input
	
	//Power LED 
	#ifdef BAT_LOW_LED_CONTROL 
	GPIO_M_SET(BAT_LOW_LED_GPIO,1); 
	GPIO_E_SET(BAT_LOW_LED_GPIO,1);  //output
	//GPIO_O_SET(POWER_LED_GPIO,1);
	#endif
	
	//TFT control 
	#ifdef TFT_ONOFF_CONTROL //shenyj add for alco177w
	regs0->sft_cfg3 &= ~((0x1)<<3); //enable gpio55 for TFT_CHECK
    regs0->sft_cfg0&= ~((0x1)<<6); //enable gpio29 for TFT_CTL
	
	GPIO_M_SET(TFT_CHECK_GPIO,1); 
	GPIO_E_SET(TFT_CHECK_GPIO,0);  //input	
	GPIO_M_SET(TFT_CONTROL_GPIO,1); 
	GPIO_E_SET(TFT_CONTROL_GPIO,1);  //output		
	#endif
	
	//Video in detect
	#ifdef VIDEO_IN_CONTROL
	GPIO_M_SET(INT_EXT_VIDEO_GPIO,1);
	GPIO_E_SET(INT_EXT_VIDEO_GPIO,0); //input
	#endif
	
	//Battery detect
	#ifdef BAT_DETECT
    GPIO_M_SET(BAT_LOW_GPIO,1);
    GPIO_E_SET(BAT_LOW_GPIO,0); //input
    #endif
#elif defined(ALCO_PVS127X) //shenyj add for alco127G    
    regs0->sft_cfg3&= ~((0x1)<<4); //enable gpio56 AUDIO_MUTE      
    //for panel key use!!!
    regs0->gpio_master[1]|= 0x00e0;    //GPIO 16,21,22,23
    GPIO_M_SET(72,1);//pin75 gpio72
    GPIO_E_SET(72,0); 
    //Cover SW
    regs0->sft_cfg4&= ~((0x1)<<6);    
    GPIO_M_SET(PDVD_OPCLSW_GPIO,1);
	GPIO_E_SET(PDVD_OPCLSW_GPIO,0); //input
	
	//Power LED 
	#ifdef POWER_LED_CONTROL 
	regs0->sft_cfg4&= ~((0x1)<<2);//enable gpio2(pin49)
	regs0->sft_cfg4&= ~((0x1)<<5);//enable gpio5(pin52)
	GPIO_M_SET(POWER_LED_STB1_GPIO,1); 
	GPIO_E_SET(POWER_LED_STB1_GPIO,1);  //output
	GPIO_M_SET(POWER_LED_STB2_GPIO,1); 
	GPIO_E_SET(POWER_LED_STB2_GPIO,1);  //output
	GPIO_O_SET(POWER_LED_STB1_GPIO,0);
    GPIO_O_SET(POWER_LED_STB2_GPIO,1);
	#endif
	
	//TFT control 
	#ifdef TFT_ONOFF_CONTROL 
	regs0->sft_cfg1&= ~((0x1)<<3); //enable gpio16 for TFT_STB_CTL
	regs0->sft_cfg3 &= ~((0x1)<<3); //enable gpio55 for TFT_CHECK
	
	GPIO_M_SET(TFT_CHECK_GPIO,1); 
	GPIO_E_SET(TFT_CHECK_GPIO,0);  //input	
	GPIO_M_SET(TFT_CONTROL_GPIO,1); 
	GPIO_E_SET(TFT_CONTROL_GPIO,1);  //output		
	GPIO_M_SET(TFT_STB_CONTROL_GPIO,1); 
	GPIO_E_SET(TFT_STB_CONTROL_GPIO,1);  //output
	#endif
	//Battery detect
	#ifdef BAT_DETECT
    GPIO_M_SET(BAT_LOW_GPIO,1);
    GPIO_E_SET(BAT_LOW_GPIO,0); //input
    #endif
    
#elif defined(ALCO_PVS19251) 
    #ifdef USE_SPDIF_OUT_AS_GPIO_MUTE
    regs0->sft_cfg3&=~((0x01)<<8); //enable gpio52 AUDIO_MUTE      
    #endif
    
    #ifdef ALCO_USE_PCM1753
    regs0->sft_cfg3&=~((0x07)<<2); //enable gpio54,55,56      
    regs0->gpio_master[3]|= 0x1c00;    
    #endif
    
    
    //for panel key use!!!
    regs0->gpio_master[1]|= 0x00e1;    //GPIO 16,21,22,23

    
    //Cover SW
    regs0->sft_cfg4&= ~((0x1)<<6);    
    GPIO_M_SET(PDVD_OPCLSW_GPIO,1);
	GPIO_E_SET(PDVD_OPCLSW_GPIO,0); //input
	
	//Power LED 
	#ifdef POWER_LED_CONTROL 
	regs0->sft_cfg4&= ~((0x9)<<2);//enable gpio2(pin49),gpio5(pin52)
	GPIO_M_SET(POWER_LED_STB1_GPIO,1); 
	GPIO_E_SET(POWER_LED_STB1_GPIO,1);  //output
	GPIO_M_SET(POWER_LED_STB2_GPIO,1); 
	GPIO_E_SET(POWER_LED_STB2_GPIO,1);  //output
	GPIO_O_SET(POWER_LED_STB1_GPIO,0);
    GPIO_O_SET(POWER_LED_STB2_GPIO,1);
	#endif
	
	//TFT control 
	#ifdef TFT_ONOFF_CONTROL 
	GPIO_M_SET(TFT_CONTROL_GPIO1,1); 
	GPIO_E_SET(TFT_CONTROL_GPIO1,1);  //output
	GPIO_M_SET(TFT_CONTROL_GPIO2,1); 
	GPIO_E_SET(TFT_CONTROL_GPIO2,1);  //output
	#endif
	
	#ifdef VIDEO_IN_CONTROL
	GPIO_M_SET(INT_EXT_VIDEO_GPIO1,1);
	GPIO_E_SET(INT_EXT_VIDEO_GPIO1,0); //input
	GPIO_M_SET(INT_EXT_VIDEO_GPIO2,1);
	GPIO_E_SET(INT_EXT_VIDEO_GPIO2,0); //input
	#endif

#elif defined(ALCO_PVS1262)||defined(ALCO_PVS8712)
    regs0->sft_cfg3&= ~((0x7)<<2); //enable gpio 54,55 and 56(AU_D1,AU_D2,AU_D3)       
    
    #ifdef ALCO_USE_PCM1753
    regs0->gpio_master[3]|= 0x1c00;    
    #endif
    
    //Panel key(GPIO 21,22,23,72)
    regs0->gpio_master[1]|= 0x00e0;    //GPIO 21,22,23
    GPIO_M_SET(72,1);//GPIO 72 
    
    //Cover SW(GPIO8)
    regs0->sft_cfg4&= ~((0x1)<<6);     
    GPIO_M_SET(PDVD_OPCLSW_GPIO,1);
	GPIO_E_SET(PDVD_OPCLSW_GPIO,0); //input
	
	//TFT control(check--->GPIO9;control--->GPIO70;STB--->GPIO16S) 
	#ifdef TFT_ONOFF_CONTROL 
	regs0->sft_cfg1&= ~((0x1)<<3); //enable gpio16 for TFT_STB_CTL
	//regs0->sft_cfg3 &= ~((0x1)<<3); //enable gpio55 for TFT_CHECK
	
	GPIO_M_SET(TFT_CHECK_GPIO,1); 
	GPIO_E_SET(TFT_CHECK_GPIO,0);  //input	
	GPIO_M_SET(TFT_CONTROL_GPIO,1); 
	GPIO_E_SET(TFT_CONTROL_GPIO,1);  //output		
	GPIO_M_SET(TFT_STB_CONTROL_GPIO,1); 
	GPIO_E_SET(TFT_STB_CONTROL_GPIO,1);  //output
	#endif
	
	//Battery detect(GPIO10)
	#ifdef BAT_DETECT
    GPIO_M_SET(BAT_LOW_GPIO,1);
    GPIO_E_SET(BAT_LOW_GPIO,0); //input
    #endif

#endif //end #if defined(ALCO_PVS177W)

#endif //end #if defined(PORTABLE_8202S)

#ifdef PORTABLE_8202D

#if defined(ALCO_PVS19251)
    #ifdef USE_SPDIF_OUT_AS_GPIO_MUTE
    regs0->sft_cfg3&=~((0x01)<<8); //enable gpio52 AUDIO_MUTE      
    #endif
    
    #ifdef ALCO_USE_PCM1753
    regs0->sft_cfg3&=~((0x07)<<2); //enable gpio54,55,56      
    regs0->gpio_master[3]|= 0x1c00;    
    #endif
    
    
    //for panel key use!!!
    regs0->gpio_master[1]|= 0x00e1;    //GPIO 16,21,22,23

    
    //Cover SW
    regs0->sft_cfg4&= ~((0x1)<<6);    
    GPIO_M_SET(PDVD_OPCLSW_GPIO,1);
	GPIO_E_SET(PDVD_OPCLSW_GPIO,0); //input
	
	//Power LED 
	#ifdef POWER_LED_CONTROL 
	regs0->sft_cfg4&= ~((0x9)<<2);//enable gpio2(pin49),gpio5(pin52)
	GPIO_M_SET(POWER_LED_STB1_GPIO,1); 
	GPIO_E_SET(POWER_LED_STB1_GPIO,1);  //output
	GPIO_M_SET(POWER_LED_STB2_GPIO,1); 
	GPIO_E_SET(POWER_LED_STB2_GPIO,1);  //output
	GPIO_O_SET(POWER_LED_STB1_GPIO,0);
    GPIO_O_SET(POWER_LED_STB2_GPIO,1);
	#endif
	
	//TFT control 
	#ifdef TFT_ONOFF_CONTROL 
	GPIO_M_SET(TFT_CONTROL_GPIO1,1); 
	GPIO_E_SET(TFT_CONTROL_GPIO1,1);  //output
	GPIO_M_SET(TFT_CONTROL_GPIO2,1); 
	GPIO_E_SET(TFT_CONTROL_GPIO2,1);  //output
	#endif
	
	#ifdef VIDEO_IN_CONTROL
	GPIO_M_SET(INT_EXT_VIDEO_GPIO1,1);
	GPIO_E_SET(INT_EXT_VIDEO_GPIO1,0); //input
	GPIO_M_SET(INT_EXT_VIDEO_GPIO2,1);
	GPIO_E_SET(INT_EXT_VIDEO_GPIO2,0); //input
	#endif 
	
#elif defined(ALCO_PVS1262)||defined(ALCO_PVS8712)
    regs0->sft_cfg3&= ~((0x7)<<2); //enable gpio 54,55 and 56(AU_D1,AU_D2,AU_D3)       
    regs0->sdc_data_cnt[6][0] |= (0x0e);//Disable ROM_A20(Pin225),ROM_A21(Pin226),ROM_A22(Pin227) as GPIO92,93,94  
    
    #ifdef ALCO_USE_PCM1753
    regs0->gpio_master[3]|= 0x1c00;    
    #endif
    
    //Panel key(GPIO 21,22,23,72)
    #ifdef ALCO_PVS8712 //added GPIO 12,13,14
///for main board key
    regs0->sft_cfg1&= ~((0x1)<<3); //GPIO 16 PIN66    
    GPIO_M_SET(16,1);//GPIO 16 PIN66
    ////for key board
    regs0->gpio_master[0]|= 0x0700;    //GPIO 12,13,14
GPIO_M_SET(15,1);//GPIO 15 PIN65
#endif
    ///for main board key
    regs0->gpio_master[1]|= 0x00e0;    //GPIO 21,22,23
    GPIO_M_SET(72,1);//GPIO 72 
#ifdef  ALCO_PVS8712    
    GPIO_E_SET(72,1);//GPIO 72 
    GPIO_O_SET(72,1);//GPIO 72 
#endif
    //Cover SW(GPIO8)
    #ifdef ALCO_CARD_USB_MODEL
    regs0->sft_cfg3&= ~((0x1)<<8);     
    GPIO_M_SET(PDVD_OPCLSW_GPIO,1);
	GPIO_E_SET(PDVD_OPCLSW_GPIO,0); //input
    #else
    regs0->sft_cfg4&= ~((0x1)<<6);     
    GPIO_M_SET(PDVD_OPCLSW_GPIO,1);
	GPIO_E_SET(PDVD_OPCLSW_GPIO,0); //input	
	#endif
	//TFT control(check--->GPIO9;control--->GPIO70;STB--->GPIO16S) 
	#ifdef TFT_ONOFF_CONTROL 
	#ifdef ALCO_CARD_USB_MODEL
	regs0->sft_cfg3 &= ~((0x1)<<6); 
	regs0->sft_cfg3 &= ~((0x1)<<0); 
	regs0->sft_cfg3 &= ~((0x1)<<9); 
	GPIO_M_SET(TFT_CHECK_GPIO,1); 
	GPIO_E_SET(TFT_CHECK_GPIO,0);  //input	
	GPIO_M_SET(TFT_CONTROL_GPIO,1); 
	GPIO_E_SET(TFT_CONTROL_GPIO,1);  //output		
	GPIO_M_SET(TFT_STB_CONTROL_GPIO,1); 
	GPIO_E_SET(TFT_STB_CONTROL_GPIO,1);  //output
	#else
	regs0->sft_cfg1&= ~((0x1)<<3); //enable gpio16 for TFT_STB_CTL
	//regs0->sft_cfg3 &= ~((0x1)<<3); //enable gpio55 for TFT_CHECK	
	GPIO_M_SET(TFT_CHECK_GPIO,1); 
	GPIO_E_SET(TFT_CHECK_GPIO,0);  //input	
	GPIO_M_SET(TFT_CONTROL_GPIO,1); 
	GPIO_E_SET(TFT_CONTROL_GPIO,1);  //output		
	GPIO_M_SET(TFT_STB_CONTROL_GPIO,1); 
	GPIO_E_SET(TFT_STB_CONTROL_GPIO,1);  //output
	#endif	
	#endif
	//Battery detect(GPIO10)
	#ifdef BAT_DETECT
    #ifdef ALCO_CARD_USB_MODEL
    regs0->sft_cfg4&= ~((0x1)<<3);
    #endif
    GPIO_M_SET(BAT_LOW_GPIO,1);
    GPIO_E_SET(BAT_LOW_GPIO,0); //input
    #endif
#elif defined(ALCO_PVS1090)
    //Cover SW(GPIO8)
    regs0->sft_cfg4&= ~((0x1)<<6);     
    GPIO_M_SET(PDVD_OPCLSW_GPIO,1);
	GPIO_E_SET(PDVD_OPCLSW_GPIO,0); //input	
	//TFT control(check--->GPIO9;control--->GPIO70;STB--->GPIO16S) 
	#ifdef TFT_ONOFF_CONTROL 
	regs0->sft_cfg3&= ~((0x1)<<1); 
	regs0->sft_cfg3 &= ~((0x1)<<0); 
	regs0->sft_cfg3 &= ~((0x1)<<9); 
	GPIO_M_SET(TFT_CHECK_GPIO,1); 
	GPIO_E_SET(TFT_CHECK_GPIO,0);  //input	
	GPIO_M_SET(TFT_CONTROL_GPIO,1); 
	GPIO_E_SET(TFT_CONTROL_GPIO,1);  //output		
	GPIO_M_SET(TFT_STB_CONTROL_GPIO,1); 
	GPIO_E_SET(TFT_STB_CONTROL_GPIO,1);  //output
	#endif	
	//Battery detect(GPIO10)
	#ifdef BAT_DETECT
    GPIO_M_SET(BAT_LOW_GPIO,1);
    GPIO_E_SET(BAT_LOW_GPIO,0); //input
    #endif
    #ifdef BAT_LOW_LED_CONTROL
    regs0->sdc_data_cnt[6][0] |= (0x0e);   //enable gpio72 pin75 of 8202d
    GPIO_M_SET(BAT_LOW_LED_GPIO,1);
    GPIO_E_SET(BAT_LOW_LED_GPIO,1); //output
    GPIO_O_SET(BAT_LOW_LED_GPIO,0); //output
    #endif
    #ifdef PDVD_USE_IO_SCAN_KEY
    regs0->sft_cfg1 &= ~((0x1)<<3); //enable gpio16 for key
    //////////for input
    GPIO_M_SET(12,1); 
	GPIO_E_SET(12,0);  //input	
	GPIO_M_SET(13,1); 
	GPIO_E_SET(13,0);  //input		
	GPIO_M_SET(14,1); 
	GPIO_E_SET(14,0);  //input
	GPIO_M_SET(15,1); 
	GPIO_E_SET(15,0);  //input
	/////////for output
    GPIO_M_SET(16,1); 
	GPIO_E_SET(16,1);  //output	
	GPIO_M_SET(21,1); 
	GPIO_E_SET(21,1);  //output		
	GPIO_M_SET(22,1); 
	GPIO_E_SET(22,1);  //output
	GPIO_M_SET(23,1); 
	GPIO_E_SET(23,1);  //output
    #endif
    #ifdef USE_PIN174_AS_GPIO_MUTE
    regs0->sft_cfg3 &= ~((0x1)<<2);
    GPIO_M_SET(54,1); 
	GPIO_E_SET(54,1);  //output
    #endif
    #ifdef POWER_ON_OFF_CONTROL
    GPIO_M_SET(POWER_ON_OFF_CONTROL_GPIO,1); 
	GPIO_E_SET(POWER_ON_OFF_CONTROL_GPIO,1);  //output
    #endif
#elif defined(ALCO_PVS1090_AVIN)//shenyj add for alco 12/04
    //Cover SW(GPIO5)
    regs0->sft_cfg4&= ~((0x1)<<5);     
    GPIO_M_SET(PDVD_OPCLSW_GPIO,1);
	GPIO_E_SET(PDVD_OPCLSW_GPIO,0); //input	
	//TFT control(check--->GPIO9;control--->GPIO70;STB--->GPIO16S) 
	#ifdef TFT_ONOFF_CONTROL 
	regs0->sft_cfg3&= ~((0x1)<<1); //enable gpio53 for TFT_CHECK
	regs0->sft_cfg3 &= ~((0x1)<<0); //enable gpio58 for TFT_ON_OFF 
	#if !defined(ARCHT16_USE_64M_ESP)//shenyj add for alco 2006/02/28
	regs0->sft_cfg1 &= ~((0x1)<<4); //enable gpio25 pin111 for TFT_POWER_STB 
	#endif
	GPIO_M_SET(TFT_CHECK_GPIO,1); 
	GPIO_E_SET(TFT_CHECK_GPIO,0);  //input	
	GPIO_M_SET(TFT_CONTROL_GPIO,1); 
	GPIO_E_SET(TFT_CONTROL_GPIO,1);  //output		
	GPIO_M_SET(TFT_STB_CONTROL_GPIO,1); 
	GPIO_E_SET(TFT_STB_CONTROL_GPIO,1);  //output
	#endif	
	//Battery detect(GPIO3)
	#ifdef BAT_DETECT
	regs0->sft_cfg4&= ~((0x1)<<3); 
    GPIO_M_SET(BAT_LOW_GPIO,1);
    GPIO_E_SET(BAT_LOW_GPIO,0); //input
    #endif
    #ifdef BAT_LOW_LED_CONTROL
    regs0->sdc_data_cnt[6][0] |= (0x0e);   //enable gpio72 pin75 of 8202d
    GPIO_M_SET(BAT_LOW_LED_GPIO,1);
    GPIO_E_SET(BAT_LOW_LED_GPIO,1); //output
    GPIO_O_SET(BAT_LOW_LED_GPIO,0); //output
    #endif
    #ifdef PDVD_USE_IO_SCAN_KEY
    #if !defined(ARCHT16_USE_64M_ESP)//shenyj add for alco 2006/02/28
    regs0->sft_cfg0&= ~((0x1)<<6); //enalbe gpio29 pin125
    #endif
    regs0->sft_cfg3&= ~((0x4b)<<3);//enable gpio55,56,57,59 pin175,176,177,180
    //////////for input
    GPIO_M_SET(55,1); 
	GPIO_E_SET(55,0);  //input	
	GPIO_M_SET(56,1); 
	GPIO_E_SET(56,0);  //input		
	GPIO_M_SET(57,1); 
	GPIO_E_SET(57,0);  //input
	GPIO_M_SET(29,1); 
	GPIO_E_SET(29,0);  //input
	/////////for output
    GPIO_M_SET(59,1); 
	GPIO_E_SET(59,1);  //output	
	GPIO_M_SET(21,1); 
	GPIO_E_SET(21,1);  //output		
	GPIO_M_SET(22,1); 
	GPIO_E_SET(22,1);  //output
	GPIO_M_SET(23,1); 
	GPIO_E_SET(23,1);  //output
    #endif
    #ifdef USE_PIN174_AS_GPIO_MUTE
    regs0->sft_cfg3 &= ~((0x1)<<2);
    GPIO_M_SET(54,1); 
	GPIO_E_SET(54,1);  //output
    #endif
    //Video in detect
	#ifdef VIDEO_IN_CONTROL
	regs0->sft_cfg0&= ~((0x1)<<4);//gpio39 pin142
	GPIO_M_SET(INT_EXT_VIDEO_GPIO,1);
	GPIO_E_SET(INT_EXT_VIDEO_GPIO,0); //input
	#endif
    #ifdef POWER_ON_OFF_CONTROL
    GPIO_M_SET(POWER_ON_OFF_CONTROL_GPIO,1); 
	GPIO_E_SET(POWER_ON_OFF_CONTROL_GPIO,1);  //output
    #endif
#endif //end #if defined(ALCO_PVS19251)
#endif //end #ifdef PORTABLE_8202D
}
