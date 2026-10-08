/*
*   Terry,2006/4/6 07:04¤U¤È 
*   Creat 8202L GPIO file.
*/

/*
*  initial gpio function.
*/
void reset_gpio(void)
{

//============================ sft_cfg ==============================

    regs0->sft_cfg13 &= ~(0x1<<6);          //Disable SERVO_STEP_OUT for Pin1 as GPIO4
    regs0->sft_cfg4 &= ~(0x1<<5);           //Disable FGIN for Pin3 as GPIO6.
    regs0->sft_cfg8 &= ~(0x1);              //For Pin9 as GPIO9 (IR)
    //regs0->gpio_first[1]|= (0x1<<3);        //Pin20 default is SPDIF_OUT,open as GPIO19
    
#ifdef SDRAM_16Mb_Mode  
    regs0->gpio_first[1]|= (0x1<<4);   //For Pin21 as GPIO20 (M_DQM2)
    regs0->gpio_first[1]|= (0x1<<5);   //For Pin22 as GPIO21 (M_DQM3)
    regs0->gpio_first[1]|= (0x1<<7);   //For Pin45 as GPIO23 (M_A11)
    regs0->gpio_first[1]|= (0x1<<9);   //For Pin58 as GPIO25 (M_BA1)
#elif defined (SDRAM_32Mb_Mode)
    #ifdef SDRAM_32Mb_One_Chip
    regs0->gpio_first[1]|= (0x1<<4);   //For Pin21 as GPIO20 (M_DQM2)
    regs0->gpio_first[1]|= (0x1<<5);   //For Pin22 as GPIO21 (M_DQM3)
    #elif defined(SDRAM_32Mb_Two_Chip) //!SDRAM_32Mb_One_Chip, SDRAM_32Mb_Two_Chip defined
    regs0->gpio_first[1]|= (0x1<<7);   //For Pin45 as GPIO23 (M_A11)
    regs0->gpio_first[1]|= (0x1<<9);   //For Pin58 as GPIO25 (M_BA1)
    #else  //neither SDRAM_32Mb_One_Chip nor SDRAM_32Mb_Two_Chip..
    #error "Please check GPIO 8202L setting."
    #endif  //one or two chip setting
#elif defined (SDRAM_64Mb_Mode)         
    regs0->gpio_first[1]|= (0x1<<4);   //For Pin21 as GPIO20 (M_DQM2)
    regs0->gpio_first[1]|= (0x1<<5);   //For Pin22 as GPIO21 (M_DQM3)
#endif 

    regs0->pad_drv0 = 0x55ff;
    regs0->pad_drv1 = 0x0f55;
    regs0->pad_drv2 = 0x0000;        

#ifdef USE_32M_BUF_IN_64M_SDRAM_AS_ESP_BUF
	regs0->gpio_first[1]&= ~(0x1<<7);      //Disable GPIO23 (M_A11)
	regs0->gpio_first[1]&= ~(0x1<<9);      //Disable GPIO25 (M_BA1)
#endif

//================== init gpio default setting (OUTPUT "L") ==================== 

    regs0->gpio_master[0] |= ((0x1<<4)|(0x1<<6)|(0x1<<9));
    regs0->gpio_oe[0] |=  ((0x1<<4)|(0x1<<6)|(0x1<<9));
    regs0->gpio_out[0] &= ~((0x1<<4)|(0x1<<6)|(0x1<<9));
    
#ifdef SDRAM_16Mb_Mode  
    regs0->gpio_master[1] |= ((0x1<<3)|(0x1<<4)|(0x1<<5)|(0x1<<7)|(0x1<<9));
    regs0->gpio_oe[1] |=  ((0x1<<3)|(0x1<<4)|(0x1<<5)|(0x1<<7)|(0x1<<9));
    regs0->gpio_out[1] &= ~((0x1<<3)|(0x1<<4)|(0x1<<5)|(0x1<<7)|(0x1<<9));
#elif defined (SDRAM_32Mb_Mode)
    #ifdef SDRAM_32Mb_One_Chip
    regs0->gpio_master[1] |= ((0x1<<3)|(0x1<<4)|(0x1<<5));
    regs0->gpio_oe[1] |=  ((0x1<<3)|(0x1<<4)|(0x1<<5));
    regs0->gpio_out[1] &= ~((0x1<<3)|(0x1<<4)|(0x1<<5));
    #elif defined(SDRAM_32Mb_Two_Chip) //!SDRAM_32Mb_One_Chip, SDRAM_32Mb_Two_Chip defined
    regs0->gpio_master[1] |= ((0x1<<3)|(0x1<<7)|(0x1<<9));
    regs0->gpio_oe[1] |=  ((0x1<<3)|(0x1<<7)|(0x1<<9));
    regs0->gpio_out[1] &= ~((0x1<<3)|(0x1<<7)|(0x1<<9));
    #else  //neither SDRAM_32Mb_One_Chip nor SDRAM_32Mb_Two_Chip..
    #error "Please check GPIO 8202L setting."
    #endif  //one or two chip setting
#elif defined (SDRAM_64Mb_Mode)         
    regs0->gpio_master[1] |= ((0x1<<3)|(0x1<<4)|(0x1<<5));
    regs0->gpio_oe[1] |=  ((0x1<<3)|(0x1<<4)|(0x1<<5));
    regs0->gpio_out[1] &= ~((0x1<<3)|(0x1<<4)|(0x1<<5));
#endif       

//================== UART setting for debug mode ====================

#if !defined(DVDRELEASE) || defined(ENABLE_UART0_IN_RELEASE_MODE)
    regs0->sft_cfg2 &= ~(0xfe);
    #if defined(SDRAM_16Mb_Mode)&&defined(SERVO_DBG_ON_DQM_8202L)   //Move UART to Pin45 & Pin58 for Servo debug pin on 8202L Pin21 & Pin22
    regs0->sft_cfg0 &= ~(0x1<<6);               //Disable M_A11
    regs0->sft_cfg1 &= ~(0x1<<4);               //Disable M_BA1
    regs0->gpio_first[1]&= ~(0x1<<7);      //Disable GPIO23
    regs0->gpio_first[1]&= ~(0x1<<9);      //Disable GPIO25
    regs0->sft_cfg2 = (0x04<<5)|(0x04<<2);      //RX on Pin45 (M_A11) & TX on Pin58 (M_BA1)   
    #else 
        #if defined(SDRAM_16Mb_Mode) || defined(SDRAM_64Mb_Mode)
    regs0->gpio_first[1]&= ~(0x1<<4);      //Disable GPIO20 (M_DQM2)
    regs0->gpio_first[1]&= ~(0x1<<5);      //Disable GPIO21 (M_DQM3)
    regs0->sft_cfg2 = (0x01<<5)|(0x01<<2);      //RX on Pin21 (M_DQM2) & TX on Pin22 (M_DQM3)
        #elif defined (SDRAM_32Mb_Mode)
            #ifdef SDRAM_32Mb_One_Chip
    regs0->gpio_first[1]&= ~(0x1<<4);      //Disable GPIO20 (M_DQM2)
    regs0->gpio_first[1]&= ~(0x1<<5);      //Disable GPIO21 (M_DQM3)
    regs0->sft_cfg2 = (0x01<<5)|(0x01<<2);      //RX on Pin21 (M_DQM2) & TX on Pin22 (M_DQM3)
            #elif defined(SDRAM_32Mb_Two_Chip) //!SDRAM_32Mb_One_Chip, SDRAM_32Mb_Two_Chip defined
    regs0->sft_cfg0 &= ~(0x1<<6);               //Disable M_A11
    regs0->sft_cfg1 &= ~(0x1<<4);               //Disable M_BA1
    regs0->gpio_first[1]&= ~(0x1<<7);      //Disable GPIO23
    regs0->gpio_first[1]&= ~(0x1<<9);      //Disable GPIO25
    regs0->sft_cfg2 = (0x04<<5)|(0x04<<2);      //RX on Pin45 (M_A11) & TX on Pin58 (M_BA1)
            #else  //neither SDRAM_32Mb_One_Chip nor SDRAM_32Mb_Two_Chip..
    #error "Please check GPIO 8202L setting."
            #endif  //one or two chip setting
        #endif  
    #endif  //#ifdef SERVO_DBG_ON_DQM_8202L
#endif  //#ifndef DVDRELEASE          

//==================== AUDIO GPIO MUTE setting =====================    
    
    SFT_CFG_GPIO();
    GPIO_MUTE();

//======================= SCART TV setting =========================

#ifdef SUPPORT_SCART_TV
    SET_SCART_GPIO_SFT_CFG_CTRL();

    SCART_TV_SET_TO_CVBS();
    SCART_TV_SET_TO_DVDPLAYER();
    SCART_TV_SET_TO_DISPLAY_4B3();
#endif
    
//======================= VGA setting =========================
#ifdef ADD_PC_VGA_OUT    // lxg 2006-9-21 10:25   Use GPIO20(Pin21) as H_SYNC   GPIO21(Pin22)  as V_SYNC
    regs0->gpio_first[1]&= ~(0x1<<4);      //Disable GPIO20
    regs0->gpio_first[1]&= ~(0x1<<5);      //Disable GPIO21
#endif
       
    //special gpio control...standby,key...   
    
}

#ifdef SUPPORT_VIDEO_BUFFER_STANDBY //kenny 2003/5/13
void video_buff_power_off(void)
{
    regs0->gpio_oe[STANDBY_GPIO / 16] |= (0x1 << (STANDBY_GPIO % 16));  
    regs0->gpio_out[STANDBY_GPIO / 16] &= ~(0x1 << (STANDBY_GPIO % 16));    
    
}   

void video_buff_power_on(void)
{
    regs0->gpio_oe[STANDBY_GPIO / 16] |= (0x1 << (STANDBY_GPIO % 16));

    regs0->gpio_out[STANDBY_GPIO / 16] |= (0x1 << (STANDBY_GPIO % 16));
    
}   

#endif

#ifdef MIC_MUTE_PIN   // lxg  2006-8-8 11:36
#define MIC_MUTE_GPIO  4
void Mic_mute_pin_output_low(void)
{
	GPIO_M_SET(MIC_MUTE_GPIO,1);
  GPIO_E_SET(MIC_MUTE_GPIO,1);
  GPIO_O_SET(MIC_MUTE_GPIO,0);  // MIC_MUTE_GPIO output 0
} 

void Mic_mute_pin_output_high(void)
{
	GPIO_M_SET(MIC_MUTE_GPIO,1);
  GPIO_E_SET(MIC_MUTE_GPIO,1);
  GPIO_O_SET(MIC_MUTE_GPIO,1);  // MIC_MUTE_GPIO output 1
} 
#endif 

//================== end of file ============================================

