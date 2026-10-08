/*
** FILE
** sysmain_user.inc
**
** DESCRIPTION
** Separate user code from standard DVD sysmain() flow
**
** user_step0: just after booting
** user_step1: just after hardware resetting
** user_step3: just before ATAPI-reset
** user_step4: just before main-loop
**
*/

/*******************************
Standard sysmain flow

void sysmain()
{
    [user_step0]
    hardware-reset
    [user_step1]
    read-setup-menu
    initialize-audio
    [user_step2]
    setup-other-hw
    [user_step3]
    reset-atapi
    [user_step4]
    enter main-loop
}
********************************/
#include "cardfs.h"

static  inline  void    sysmain_user_init_usb();
static  inline  void    sysmain_user_init_card();


extern void ResetAuthentStates();       // HDMI
extern void uhci_reset(void);           // USB
extern void usb_host_init();            // USB


static inline void sysmain_user_step0(void)
{
	// setup shared-bus
#ifdef ROM_SDRAM_SHARE_BUS
	regs0->sdctrl_gclk_dis = 8 << 8;
	regs0->stamp = 0x01;
#endif

#if defined(PAL_VERSION)&&defined(UNLOCK_STATE_NOT_CHECK_PASSWD)
	disc_has_unlock = 0xf0;
#endif

#if defined(STOP_RESUME_DVD_VCD)&&defined(DISC_ID_IN_FLASH)
	need_record = POWER_ON_RECORD_FLAG;
#endif

#ifdef PORTABLE_POWER_ON_MUTE
	regs0->sft_cfg3 &=~((0x01<<6));         //CHENZZ FOR LRCK=0.for power on noise
#endif

#ifdef SUPPORT_MIDI //Jeff 20040420
	if (chipid_check_midi() == 0)
	{
		volatile int *buf;
		buf = (volatile int *)(0xBFFE8008);
		*buf = -1;
	}
#endif

#ifdef PULIANG_DVD  //yaowh add 04-12-17
	regs0->gpio_master[35 / 16] |= (0x1 << (35 % 16));	
	GPIO_E_SET(35,1);
	GPIO_O_SET(35,1);
#endif

#if defined(SUPPORT_AUDIO_RESET)&&defined(HANYANG_4340_AUDRESET)
	regs0->sft_cfg3 &= ~(0x1 << 4);
	regs0->gpio_master[60 / 16] |= (0x01 << (60 % 16));
	regs0->gpio_oe[60 / 16] |= (0x01 << (60 % 16));
	regs0->gpio_out[60 / 16] |= (0x01 << (60 % 16));
	delay_srv_10ms(30);
#endif    
    
#ifdef SUPPORT_SPI
	regs0->sft_cfg0 &= ~(0x3fff << 1); //pin 129~131, pin 133~136 is GPIO  
	regs0->gpio_master[SPI_DATAIN / 16] |= (0x1 << (SPI_DATAIN % 16));
	regs0->gpio_oe[SPI_DATAIN / 16] |= (0x1 << (SPI_DATAIN % 16));
	regs0->gpio_out[SPI_DATAIN / 16] |= (0x1 << (SPI_DATAIN % 16));  
#endif  

#ifdef STBY_CONTROLLER_IO_61PIN_12GPIO
	GPIO_M_SET(12,1);  	//pin 61 gpio 12 s-by
	GPIO_E_SET(12,1);  	//pin 61 gpio 12 s-by
	GPIO_O_SET(12,1);  	//pin 61 gpio 12 s-by
#endif

#if defined(SUPPORT_CARD_STORAGE)       //liweihua mod 20040324
	media_type = MEDIA_CARD;
#endif
} 



#ifdef ADD_DVI311_SETUP
#include "spv301.h"
#endif

static  inline  void    sysmain_user_step1()
{
#ifdef BOOT_LOAD_ROMA //terry,2005/3/6 08:07PM
    rom_checksum_per_kbyte1(ROMB_CHK_SUM_ST,ROMB_CHK_SUM_END);
#endif    
    
#ifdef VIDEO_IN_CONTROL
    #if defined(ALCO_PV1950)||defined(ALCO_PVS19251)
    //check_8200_portable_gpio();
    if(!(GPIO_I_GET(INT_EXT_VIDEO_GPIO1)||GPIO_I_GET(INT_EXT_VIDEO_GPIO2)))
    { 
      AVin_step = 0x0f;
      ircmd_power();
    }
    #elif defined(ALCO_PVS177W)//shenyj add for alco177w
    if(GPIO_I_GET(INT_EXT_VIDEO_GPIO))
    { 
      AVin_step = 0x0f;
      ircmd_power();
    }
    #endif
#endif
    
#ifdef DVI_I2C_SET
#ifdef SPHE8202
//  i2c_init_io_risc();
#else
    // select GPIO 0,1 for mips I2C tjf 04-04-29
    regs0->gpio_master[0]|=0x3; //gpio 0,1 for risc
    regs0->gpio_oe[0]|=0x03;
#endif
#endif

#ifdef RESET_TO_DVI311//tjf 04-05-06
#ifdef SPHE8202
    regs0->sft_cfg3 &= (~(0x01<<7));
    regs0->sft_cfg8 &= (~(0x03<<8));

    regs0->sft_cfg3 &= (~(0x01<<4));
    //regs0->sft_cfg8 &= (~(0x03<<8));
#else
#define RESET_DVI311_GPIO 40
//  regs0->gpio_master[2]|=(1<<8);
//  regs0->gpio_oe[2]|=(1<<8);
    //GPIO_M_SET(RESET_DVI311_GPIO, 1); //dvi311_reset is gpio 37,pin129
    //GPIO_E_SET(RESET_DVI311_GPIO, 1);
//  GPIO_O_SET(RESET_DVI311_GPIO, 1);
    GPIO_O_SET(RESET_DVI311_GPIO, 1);
    delay_1ms(200);
    delay_1ms(200);
    GPIO_O_SET(RESET_DVI311_GPIO, 0);
#endif
#endif


}


static  inline  void    sysmain_user_step2()
{
    #ifdef POWER_ON_ENTER_DVB//Jack moved to here 06/04/03
	extern UINT8 DVD2DVB_switch_flag ; 
	DVD2DVB_switch_flag = 1; 
	    #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
	    source_play_mode = DVB_T_MODE;
	    #endif//end=> #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
	#endif//end=>#ifdef POWER_ON_ENTER_DVB
	
#ifdef PCM1742 //zhongshan turn on dac after audio init 050718
    dac_turn_on();
#endif
	
#ifdef ADD_DVI311_SETUP//moved from setup menu to avoid redundant initialization
    init_scaler();
#endif

#ifdef HDMI     //moved from below to avoid affect loading disc
    ResetAuthentStates();
#endif

#ifdef SUPPORT_FUNCTION_MENU
    #ifdef SUPPORT_SPI
    pdvd_mode = PDVD_MODE;
    #endif
#endif
    
    // setup hardware (in additional to reset_all())
#ifdef EASTWIN
    check_customer_default();
    init_lcd_display_mode();
#endif

#ifdef SPHE1000 //MIKEY 2004.07.15
    LoadModual(MODUAL_LWIP);
    read_profile();
#endif
}



#ifdef SUPPORT_RECEIVER
#include "amp_gui.h"
#endif

static  inline  void    sysmain_user_step3()
{
    #ifdef SUPPORT_VIDEO_OUT_DELAY//Jack moved to here 06/04/03
	tv_dacoff(TV_DAC_F|TV_DAC_E|TV_DAC_D|TV_DAC_C|TV_DAC_B);
	#endif
	
    // first time display DVD player title
#ifndef SLEEP_WHEN_POWER_ON   
    #ifdef QSI_PORTABLE_DVD
        sp8200tv_setup_custom_output(TV_OUT_CScCSc);
        tv_dacoff(TV_DAC_A|TV_DAC_E|TV_DAC_F);
    #elif defined(GPS_DVD)
	sp8200tv_setup_custom_output(TV_OUT_CScCSc);
        tv_dacoff(TV_DAC_D|TV_DAC_E|TV_DAC_F);    
    #endif
    ShowTitle(); 
#endif//#ifndef SLEEP_WHEN_POWER_ON   

#ifdef PMP_Video_Onlycvbs    ///yangli 2004-11-29.add to pmp video out only cvbs
    sp8200tv_setup_custom_output(TV_OUT_CScCCC);
    tv_dacoff(TV_DAC_B|TV_DAC_C|TV_DAC_D|TV_DAC_E|TV_DAC_F);//only cvb is on
#endif  

#ifdef RUN_IN_SUNPLUS_8202D_PORTABE_BOARD    ///rbhung 2005-06-17 add for Sunplus 8202S/D 216pin Portable Demoboard
    sp8200tv_setup_custom_output(TV_OUT_CScCCC);
    tv_dacoff(TV_DAC_A|TV_DAC_C|TV_DAC_D|TV_DAC_E|TV_DAC_F);//only cvb is on
#endif

#if defined(SUPPORT_RECEIVER)&&(defined(SUPPORT_APOGEE_AMP)||defined(TAS_5026_PWM)||defined(TAS_5508_PWM)||defined(PT2258)||defined(TDA7448))
    init_amp();
#endif

#ifdef USE_TLV320_ADC	//fcr 2005-11-4 17:18
    TLV320_init();	
#endif

#ifdef SUPPORT_I2C_LCD_Panel
    init_I2C_panel();
#endif
   
#ifdef SPHE1000
    f_ExtendGPIOall();
    boot_linux();
#endif
}



static  inline  void    sysmain_user_step4()
{
    sysmain_user_init_usb();
    sysmain_user_init_card();

#ifdef AD_TCL//2004-3-31 14:24 lijd
    #ifdef SLEEP_WHEN_POWER_ON
    {
        volatile int *iMagic=(int *)(DATA_RAM_BASE|0x80);
        if (*iMagic != 0x1234abcd) 
        {
            #ifdef TCL_STANDBY
                         regs0->gpio_master[4 / 16] |= (0x1 << (4 % 16));
                         regs0->gpio_oe[ 4/16 ] |= (0x1 << (4%16));//output
                         regs0->gpio_out[4/16 ] |= (0x1 << (4%16));
                     ircmd_power();
            #else
            #if defined(POWER_RESUME)&&defined(SLEEP_WHEN_POWER_ON)
            ircmd_power();
            #endif
          
            #endif
        }
         else
         {
            #ifdef TCL_STANDBY
                         regs0->gpio_master[4 / 16] |= (0x1 << (4 % 16));
                         regs0->gpio_oe[ 4/16 ] |= (0x1 << (4%16));//output
                         regs0->gpio_out[ 4/16 ] &= ~(0x1 << (4%16));
            #endif
         }
        *iMagic = 0;
        //yanlb move it here;04/05/12 PM 10:15
        tv_dacoff(0);                   // dac f/e/d/c/b/a on    
        ShowTitle();
    }
    #endif
#else
    #ifndef AFTER_UPGRADE_TRAYOUT
    sleep_when_power_on();
    #else
        //tray out after updata,fist time don't sleep .move from sysmain2.c
        #if defined( RESET_AFTER_UPGRADE ) || defined( RISC_ALIVE_STANDBY )    // 2004/10/01 yltseng
        {
            volatile int *iMagic = (int *)(DATA_RAM_BASE|0x80);
            if (*iMagic == 0x1881)ircmd_trayout();
            else sleep_when_power_on();
            *iMagic = 0;
        }    
        #endif
    #endif
#endif
}
           

//
// user routines
//
static  inline  void    sysmain_user_init_usb()
{
    // initialize USB
    #ifdef SUPPORT_USB//liweihua 2003-9-25
      #ifdef HOST_UHCI  //wthsin, 2004/1/12 02:09pm
        regs0->reset2 &= 0xEFFF;  //wthsin, Enable UHCI register R/W access
        extern UINT16 uhci_usb_driver;
        #ifdef IC_8202E
         uhci_usb_driver=0x6f1f;
        #else
         uhci_usb_driver=0x3e3e;
        #endif
        uhci_reset();   
        card_plug_state = USER_DO_PLUG_OUT; 
      #elif defined(USB_HOST_DRV)
        regs0->reset2 &= ~(1<<12);      //For Usb Host, wthsin, 2005/2/23 05:04pm
	#ifdef IC_8202L
	//regs0->gclken1 &= 0xefff;  //turn off usb gated clk.
	#endif
        regs0->sft_cfg11 |= (1<<12);    //USB PHY Ena
        regs0->sft_cfg11 &= ~(1<<13);   //USB PHY suspend 
        extern UINT16 usb_phy_driver;;
        usb_phy_driver=0x3e3e;
        usb_host_init();
      #endif  
    #endif
}

static  inline  void    sysmain_user_init_card()
{
    // initialize CARD
    #ifdef SUPPORT_CARD_STORAGE
        #ifdef SUPPORT_HDD_ACCESS
            load_hdd_init();
        #endif
        CardReset();
    #endif
}
