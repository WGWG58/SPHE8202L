
#include "gpio.h"
//liweihua, 2004-12-24 15:54
#ifdef PMP_KEYBOARD  //xyy 2005-1-10
//PMP I/O DEFINE  //xyy 2005-1-13
#define PMP_IO1 16
#define PMP_IO2 55
#define PMP_IO3 54
#define PMP_IO4 4
#define PMP_POWER_OFF_SELECT 8
#define PMP_CUT_POWER        3
#define PMP_HDD_POWER_CONTROL 30
#define PMP_USB_IC_POWER     7
#define PMP_CUT_PANEL_POWER  17

#define PMP_KEY_PRESS_POLLING (regs0->gpio_in[PMP_IO4/16]&(1<<(PMP_IO4%16)))
#define IO1_STATUS (regs0->gpio_in[PMP_IO1/16]&(1<<(PMP_IO1%16)))
#define IO2_STATUS (regs0->gpio_in[PMP_IO2/16]&(1<<(PMP_IO2%16)))
#define IO3_STATUS (regs0->gpio_in[PMP_IO3/16]&(1<<(PMP_IO3%16)))
#define GET_PMP_POWER_OFF_SELECT (regs0->gpio_in[PMP_POWER_OFF_SELECT/16]&(1<<(PMP_POWER_OFF_SELECT%16)))

void polling_key_press(void)
{
	int i,temp=5;
	regs0->sft_cfg1 &= ~(0x1 << 3);
	regs0->sft_cfg1 &= ~(0x1 << 7);
	regs0->sft_cfg8 &= ~(0x1 << 9);
	GPIO_M_SET(PMP_IO1,1);                                                                                                                                                                            
	GPIO_E_SET(PMP_IO1,1);
	
	regs0->sft_cfg3 &= ~(0x1 << 3);
	regs0->sft_cfg8 &= ~(0x3 << 8);
	GPIO_M_SET(PMP_IO2,1);
	GPIO_E_SET(PMP_IO2,1);

	for(i=0;i<temp;i++)
	{
		GPIO_E_SET(PMP_IO1,1);
		GPIO_E_SET(PMP_IO2,0);
		GPIO_E_SET(PMP_IO3,0);
		GPIO_O_SET(PMP_IO1,1);
	}
	if(IO2_STATUS)
	{
	    #ifdef IRCMD_DBG
		psprintf(RegionValStr[REGION1],"SW6");
	 	PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
	 	#endif
	 	pmpkey_down();
	 }	
	else if(IO3_STATUS)
	{
	    #ifdef IRCMD_DBG
		psprintf(RegionValStr[REGION1],"SW10");
	 	PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
	 	#endif
	}

	for(i=0;i<temp;i++)
	{
		GPIO_E_SET(PMP_IO1,0);
		GPIO_E_SET(PMP_IO2,1);
		GPIO_E_SET(PMP_IO3,0);
		GPIO_O_SET(PMP_IO2,1);
	}

	if(IO1_STATUS)
	{
	    #ifdef IRCMD_DBG
		psprintf(RegionValStr[REGION1],"SW2");
	 	PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
	 	#endif
	 	pmpkey_up();
	 }	
	else if(IO3_STATUS)
	{
	    #ifdef IRCMD_DBG
		psprintf(RegionValStr[REGION1],"SW9");
	 	PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
	 	#endif
	 	pmpkey_select();
	}

	for(i=0;i<temp;i++)
	{
		GPIO_E_SET(PMP_IO1,0);
		GPIO_E_SET(PMP_IO2,0);
		GPIO_E_SET(PMP_IO3,1);
		GPIO_O_SET(PMP_IO3,1);
	}	
	if(IO1_STATUS)
	{
	    #ifdef IRCMD_DBG
		psprintf(RegionValStr[REGION1],"SW1");
	 	PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
	 	#endif
	 	pmpkey_left();
	 }	
	else if(IO2_STATUS)
	{
	    #ifdef IRCMD_DBG
		psprintf(RegionValStr[REGION1],"SW4");
	 	PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
	 	#endif
	 	pmpkey_right();
	}
}
void polling_pmpkey(void)
{
	//static int iTmCount;
	regs0->sft_cfg1 &= ~(0x1 << 3);
	regs0->sft_cfg1 &= ~(0x1 << 7);
	regs0->sft_cfg8 &= ~(0x1 << 9);
	GPIO_M_SET(PMP_IO1,1);                                                                                                                                                                            
	GPIO_E_SET(PMP_IO1,1);
//	GPIO_O_SET(PMP_IO1,1);
	
	regs0->sft_cfg3 &= ~(0x1 << 3);
	regs0->sft_cfg8 &= ~(0x3 << 8);
	GPIO_M_SET(PMP_IO2,1);
	GPIO_E_SET(PMP_IO2,1);
//	GPIO_O_SET(PMP_IO2,1);   
	if(!PMP_KEY_PRESS_POLLING)
		polling_key_press();
	if(GET_PMP_POWER_OFF_SELECT)
	{
		printf("-------------  hello ----------------\n");
		//iTmCount++;
		//if(iTmCount==1)
			pmpkey_return();
	}
	/*else
		iTmCount=0;
	if(iTmCount > 5)
	{
		printf("==========   hello hello hello ===========\n");
		GPIO_E_SET(PMP_POWER_OFF_SELECT,1);
		GPIO_O_SET(PMP_POWER_OFF_SELECT,0);
		delay_1ms(1000);
		GPIO_E_SET(PMP_POWER_OFF_SELECT,0);
	}*/
 
}
void Set_PMP_Key(void)
{
    regs0->sft_cfg2 &= ~(0x3<<10);
	regs0->sft_cfg4 &= ~(0x1<<1);
	regs0->sft_cfg8 &= ~(0x3<<8);
	GPIO_M_SET(PMP_IO4,1);
	GPIO_E_SET(PMP_IO4,0);
    
	regs0->sft_cfg3 &= ~(0x1 << 2);
	regs0->sft_cfg8 &= ~(0x3 << 8);
	GPIO_M_SET(PMP_IO3,1);
	GPIO_E_SET(PMP_IO3,1);
	GPIO_O_SET(PMP_IO3,1);

	regs0->sft_cfg1 &= ~(0x1 << 3);
	regs0->sft_cfg1 &= ~(0x1 << 7);
	regs0->sft_cfg8 &= ~(0x1 << 9);
	GPIO_M_SET(PMP_IO1,1);                                                                                                                                                                            
	GPIO_E_SET(PMP_IO1,1);
	GPIO_O_SET(PMP_IO1,1);
	
	regs0->sft_cfg3 &= ~(0x1 << 3);
	regs0->sft_cfg8 &= ~(0x3 << 8);
	GPIO_M_SET(PMP_IO2,1);
	GPIO_E_SET(PMP_IO2,1);
	GPIO_O_SET(PMP_IO2,1);   

	regs0->sft_cfg2 &= ~(0x1 << 10);
	regs0->sft_cfg4 &= ~(0x1 << 6);
	regs0->sft_cfg8 &= ~(0x1 << 9);
	GPIO_M_SET(PMP_POWER_OFF_SELECT,1);                                                                                                                                                                            
	GPIO_E_SET(PMP_POWER_OFF_SELECT,0);
	GPIO_O_SET(PMP_POWER_OFF_SELECT,0);

	regs0->sft_cfg2 &= ~(0x1 << 10);
	regs0->sft_cfg4 &= ~(0x1 << 3);
	regs0->sft_cfg8 &= ~(0x3 << 8);
	GPIO_M_SET(PMP_CUT_POWER,1);                                                                                                                                                                            
	GPIO_E_SET(PMP_CUT_POWER,1);
	GPIO_O_SET(PMP_CUT_POWER,0);

	regs0->sft_cfg2 &= ~(0x3 << 4);
	regs0->sft_cfg2 &= ~(0x1 << 10);
	regs0->sft_cfg1 &= ~(0x2 << 9);
	regs0->sft_cfg0 &= ~(0x1 << 12);
	regs0->sft_cfg8 &= ~(0x1f << 6);
	regs0->sft_cfg7 &= ~(0x0 << 1);

	regs0->sft_cfg2 &= ~(0xa << 2);
	regs0->sft_cfg7 &= ~(0x3 << 6);
	regs0->sft_cfg8 &= ~(0x1 << 2);
	regs0->sft_cfg8 &= ~(0x1 << 9);
	regs0->sft_cfg7 &= ~(0x3 << 14);
	regs0->sft_cfg9 &= ~(0x2 << 13);
	regs0->sft_cfg6 &= ~(0x1 << 4);
	GPIO_M_SET(PMP_USB_IC_POWER,1);                                                                                                                                                                            
	GPIO_E_SET(PMP_USB_IC_POWER,1);
	GPIO_O_SET(PMP_USB_IC_POWER,0);

	regs0->sft_cfg1 &= ~(0x1 << 2);
	regs0->sft_cfg8 &= ~(0x1 << 9);
	GPIO_M_SET(PMP_CUT_PANEL_POWER,1);                                                                                                                                                                            
	GPIO_E_SET(PMP_CUT_PANEL_POWER,1);
	GPIO_O_SET(PMP_CUT_PANEL_POWER,0);

	regs0->sft_cfg2 &= ~(0x3<<10);
	GPIO_M_SET(PMP_IO4,1);
	GPIO_E_SET(PMP_IO4,0);
    
	regs0->sft_cfg3 &= ~(0x1 << 2);
	GPIO_M_SET(PMP_IO3,1);
	GPIO_E_SET(PMP_IO3,1);
	GPIO_O_SET(PMP_IO3,1);

	regs0->sft_cfg2 &= ~(0x1 << 2);
	regs0->sft_cfg3 &= ~(0x01 << 12);
	regs0->sft_cfg4 &= ~(0x3 << 13);
	GPIO_M_SET(PMP_IO1,1);                                                                                                                                                                            
	GPIO_E_SET(PMP_IO1,1);
	GPIO_O_SET(PMP_IO1,1);
	
	GPIO_M_SET(PMP_IO2,1);
	GPIO_E_SET(PMP_IO2,1);
	GPIO_O_SET(PMP_IO2,1);    
}
#endif	

void pmpkey_up(void)
{
    if((pFsJpeg->gifsState == FS_STATE_MP3)||(pFsJpeg->gifsState == FS_STATE_OTHER))
        ircmd_volume_up();
    else
    HDDCard_up();
    return;
}
void pmpkey_down(void)
{
    if((pFsJpeg->gifsState == FS_STATE_MP3)||(pFsJpeg->gifsState == FS_STATE_OTHER))
        ircmd_volume_down();
    else
    HDDCard_down();
    return;
}
void pmpkey_left(void)
{
	if((pFsJpeg->gifsState == FS_STATE_MP3)||(pFsJpeg->gifsState == FS_STATE_OTHER))
        ircmd_prev();
    else
    HDDCard_left();
    return;
}
void pmpkey_right(void)
{
	if((pFsJpeg->gifsState == FS_STATE_MP3)||(pFsJpeg->gifsState == FS_STATE_OTHER))
        ircmd_next();
    else
    HDDCard_right();
    return;
}
void pmpkey_return(void)
{
    #ifdef PMP_KEYBOARD
    if(pFsJpeg->gifsState == FS_STATE_MODE)
    {
        GPIO_E_SET(PMP_POWER_OFF_SELECT,1);
		GPIO_O_SET(PMP_POWER_OFF_SELECT,0);
		delay_1ms(1000);
		GPIO_E_SET(PMP_POWER_OFF_SELECT,0);
    }
    else
    #endif
    HDDCard_return();
    return;
}
void pmpkey_select(void)
{
    HDDCard_select();
    return;
}

void pmpkey_lcd(void)
{
	static int i=0;
	i++;
	//printf("pmpkey_lcd=%d\n",i);
	if(i==1)
	{
		if(GPIO_I_GET(2))
		tv_dacoff(TV_DAC_A|TV_DAC_B|TV_DAC_C|TV_DAC_D|TV_DAC_F);
		else
		tv_dacoff(TV_DAC_A|TV_DAC_B|TV_DAC_C|TV_DAC_D|TV_DAC_E|TV_DAC_F);
		delay_1ms(100);
		GPIO_O_SET(CUT_PANEL_POWER ,0);
		regs0->sft_cfg4 &= ~(0x1 << 5);  //////////////set I2C scl sda to low
		GPIO_M_SET(5 ,1);
        GPIO_E_SET(5 ,1); 
        GPIO_O_SET(5 ,0);
        GPIO_M_SET(6 ,1);
        GPIO_E_SET(6 ,1); 
        GPIO_O_SET(6 ,0);
	}
	if(i==2)
	{
		GPIO_O_SET(CUT_PANEL_POWER ,1);
		GPIO_M_SET(5 ,0);
		GPIO_M_SET(6 ,0);
		delay_1ms(3);
		 #ifdef SUPPORT_Auo_UPS018_Digital_panel
        init_auo_ups018_digital_panel();
        #endif
        i=0;
        delay_1ms(100);
        if(GPIO_I_GET(2))
		tv_dacoff(TV_DAC_B|TV_DAC_C|TV_DAC_D|TV_DAC_F);
		else
        tv_dacoff(TV_DAC_B|TV_DAC_C|TV_DAC_D|TV_DAC_E|TV_DAC_F);
     }
}

