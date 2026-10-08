/*
*   Terry,2006/4/6 07:04下午 
*   Creat 8200/8202/8202S/8202D GPIO file.
*/
#ifdef SUPPORT_ETRON_EL8332_TCON
#include "kernel.h"
#include "setup_VA.h"
#endif

#ifdef EASTWIN
#include "iop.h"
#include "kernel.h"         // Kevin Sep 20,04 
extern void show_level(int id,INT8 level,BYTE total_level); 

#if 1
/* Default parameter table of AN2526H */
unsigned char color_drv_data[16] = { 0x84,0x8b,0xbf,0x73,/* 0,1,2,3 */
                                     0x47,0xca,0xad,0x7f,/* 4,5,6,7 */            
                                     0x5f,0x5f,0x85,0x7f,/* 8,9,10,11 */
                                     0xe4,0x6e,0x3c,0xcc /* 12,13,14,15 */
                                    }; 
#endif

#if 0
/* Default parameter table of AN2526H from Maple */
unsigned char color_drv_data[16] = { 0x13,0x11,0xe0,0xdd,/* 0,1,2,3 */
                                     0x8f,0xed,0xa5,0x80,/* 4,5,6,7 */            
                                     0x7f,0x73,0x80,0x80,/* 8,9,10,11 */
                                     0xff,0x82,0x80,0xac /* 12,13,14,15 */
                                    }; 
#endif
#endif



#ifdef SUPPORT_Auo_UPS053_Digital_panel
#if 0
BYTE auo_053_ntsc[25]={ /*00*/0xE3, /*01*/0xE0, /*02*/0x96, /*03*/0x06, 
                        /*04*/0x00,/*05*/0x0E, /*06*/0x52, /*07*/0x02,
                        /*08*/0x6A, /*09*/0x9C,/*0A*/0xB4, /*0B*/0x50,
                        /*0C*/0xF7, /*0D*/0x80, /*0E*/0x20, /*0F*/0xC1,
                        /*10*/0xCE, /*11*/0x07, /*12*/0x91, /*13*/0x01,
                        /*14*/0x80, /*15*/0x00, /*16*/0x00, /*17*/0x00,
                        /*18*/0x00
                    };
                    
                
                    
BYTE auo_053_ntsc[25]={ /*00*/0xE2, /*01*/0x28, /*02*/0x96, /*03*/0x06, 
                        /*04*/0x00,/*05*/0x10, /*06*/0x52, /*07*/0x02,
                        /*08*/0x6A, /*09*/0x9C,/*0A*/0xB4, /*0B*/0x50,
                        /*0C*/0xF7, /*0D*/0x80, /*0E*/0x20, /*0F*/0xC1,
                        /*10*/0xCE, /*11*/0x00, /*12*/0x91, /*13*/0x01,
                        /*14*/0x30, /*15*/0x00, /*16*/0x00, /*17*/0x00,
                        /*18*/0xc7
                    };                  
BYTE auo_053_ntsc[25]={
         /*00*/0xE1, /*1*/0x28, /*2*/0x96, /*3*/0x06, 
         /*04*/0x0B,/*5*/0x10, /*6*/0x15, /*7*/0x07,
         /*08*/0x44, /*9*/0x9C,/*A*/0xB4, /*B*/0x52,
         /*0C*/0xE4, /*D=4A-DVD;8A-decoder*/0x4A, /*E*/0x60, /*F*/0x40,
         /*10*/0x6C, /*1*/0x00, /*2*/0x91, /*3*/0x01,
         /*14*/0x30, /*5*/0xFF, /*6*/0x00, /*7*/0x00,
         /*18*/0x47
};                      
#endif    
BYTE auo_053_ntsc[25]={ /*00*/0xE2, /*01*/0x28, /*02*/0x96, /*03*/0x06, 
                        /*04*/0x00,/*05*/0x10, /*06*/0x52, /*07*/0x02,
                        /*08*/0x6A, /*09*/0x9C,/*0A*/0xB4, /*0B*/0x50,
                        /*0C*/0xF7, /*0D*/0x80, /*0E*/0x20, /*0F*/0xC1,
                        /*10*/0xCE, /*11*/0x00, /*12*/0x91, /*13*/0x01,
                        /*14*/0x30, /*15*/0x00, /*16*/0x00, /*17*/0x00,
                        /*18*/0xc7
                    
};    
                             
                    
#endif

#ifdef SUPPORT_Auo_UPS018_Digital_panel
#if 0   
BYTE auo_018_ntsc[5]={ /*00*/0x7a, /*1*/0x4e, /*2*/0x71, /*3*/0x80, 
         /*04*/0x91};//////for 480*234 pannel (1)
BYTE auo_018_ntsc[5]={ /*00*/0x7b, /*1*/0x4e, /*2*/0x71, /*3*/0x80, 
         /*04*/0x91};//////for 480*234 pannel (2)        
BYTE auo_018_ntsc[5]={ /*00*/0x67, /*1*/0x4e, /*2*/0x71, /*3*/0x80, 
         /*04*/0x91};/////for 7" pannel out for 4:3     
BYTE auo_018_ntsc[5]={ /*00*/0x7f, /*1*/0x4e, /*2*/0x71, /*3*/0x80, 
         /*04*/0x91};/////for 7" pannel out for 16:9             
#endif
BYTE auo_018_ntsc[5]={ /*00*/0x7a, /*1*/0x4e, /*2*/0x71, /*3*/0x80, 
         /*04*/0x91};//////for 480*234 pannel (1)
BYTE color_drv_data[16] = { 0x84,0x8b,0xbf,0x73,/* 0,1,2,3 */
                                     0x47,0xca,0xad,0x7f,/* 4,5,6,7 */            
                                     0x5f,0x5f,0x85,0x7f,/* 8,9,10,11 */
                                     0xe4,0x6e,0x3c,0xcc /* 12,13,14,15 */
                                    }; 
BYTE an2526_data_ntsc[16] =
    {
        0x84,       // 0 Vertical sync. signal output position
        0x8e,       // 1 Horizontal sync. signal output position
        0x80,       // 2 PWM duty
        0x98,       // 3 Common pulse amplitude
        0x80,       // 4 Y-gain
        0xcf,//0xbf,        // 5 Color gain
        0xbe,//0xbe,        // 6 Hue
        0x80,       // 7 Black-limiter level
        0x5f,//0x6c,        // 8 Bright
        0x80,       // 9 Y-aperture gain
        0x8b,       // 10 R-ch. sub bright
        0x87,       // 11 B-ch. sub bright
        0x80,       // 12 White peak limiter
        0x89,       // 13 Gamma-1 Knee level
        0x80,       // 14 Gamma-2 Knee level
        0x99//0x8a      // 15 RGB contrast
    };    
         
             

#endif



//
// FUNCTION
// reset_gpio
//
// restore GPIO initial state
//

#ifdef PORTABLE_DVD
#include "gpio_portable.c" //0725 splitted for portable
#endif
#ifdef SUPPORT_OP_FIVE_DISC  //chenzhao20060107 add
#include "fdisc_gpio.c"
#endif

#ifdef ALCO_PORTABLE
#include "gpio_alco_portable.c"
#endif

#if defined(PMP_DVD)
//extern void hwHddPowerOn(void);//kenny 2005/5/13
extern void Set_PMP_Key(void);

//kenny 2005/5/12 move the code from pmp_drv.c
///for PMP power control
void ioPowerOff(void)
{
    //CUT_USB_PWR  set it to be low 
    regs0->sft_cfg1=regs0->sft_cfg1&(~(1<<0x02));//pin77,GPIO 17
    GPIO_M_SET(17,1);
    GPIO_E_SET(17,1);
    GPIO_O_SET(17,0);
    
}   

inline void hwCfpowerOn(void)
{
    //pin78  set it to be high , let CF power on
    regs0->sft_cfg1=regs0->sft_cfg1&(~(1<<0x01));//pin78,GPIO 18
    GPIO_M_SET(18,1);
    GPIO_E_SET(18,1);
    GPIO_O_SET(18,1);
    
}   

inline void hw8202IdeBusOn(void)
{
    //pin61  set it to be high , let 8202 ide bus switch on
    regs0->sft_cfg4=regs0->sft_cfg4&(~(1<<0x04));//pin61,GPIO 4
    GPIO_M_SET(4,1);
    GPIO_E_SET(4,1);
    GPIO_O_SET(4,1);
    
}   

inline void hwHddPowerOn(void)
{
     //Power on HDD  HDD_PWR is set to high , pin152 GPIO 31
    
     
     GPIO_M_SET(30,1);
     GPIO_E_SET(30,1);
     GPIO_O_SET(30,1);
        
}   

void ioPowerOn(void)
{
    
    //CUT_USB_PWR  set it to be high, cut the connect between VCC5_USB and Vcc5_IO 
    regs0->sft_cfg1=regs0->sft_cfg1&(~(1<<0x02));//pin77,GPIO 17
    GPIO_M_SET(17,1);
    GPIO_E_SET(17,1);
    GPIO_O_SET(17,1);
    hw8202IdeBusOn();
    hwHddPowerOn();
    delay_1ms(10);
    hwCfpowerOn();
    
    
    
}



void PMP_gpio_init()
{
   regs0->sft_cfg1 &= ~(0x1 << 2);  //set GPIO 17 ca8202 pin77  yangli add 2005/4/20
    GPIO_M_SET(CUT_PANEL_POWER ,1);
    GPIO_E_SET(CUT_PANEL_POWER ,1); 
    GPIO_O_SET(CUT_PANEL_POWER ,0);
     
    regs0->sft_cfg4 &= ~(0x1 << 2);
    GPIO_M_SET(2 ,1);
    GPIO_E_SET(2 ,0); 
    
    regs0->sft_cfg0 &= ~(0x1 << 5);     //set GPIO 38 ca8202 pin161
    GPIO_E_SET(PC_USB_CONNECT_PIN, 0);  //pin161 is Pc Usb Vcc detect pin
    //pin61  set it to be high , let 8202 ide bus switch on
    regs0->sft_cfg4=regs0->sft_cfg4&(~(1<<0x04));  //pin61,GPIO 4
    GPIO_M_SET(IDE_BUS_SWITCH_CONTROL_PIN,1);
    GPIO_E_SET(IDE_BUS_SWITCH_CONTROL_PIN,1); 
    GPIO_O_SET(IDE_BUS_SWITCH_CONTROL_PIN,1);
    //pin64
    GPIO_M_SET(USB_DEVICE_CHIP_POWER_PIN,1);
    GPIO_E_SET(USB_DEVICE_CHIP_POWER_PIN,1); 
   #ifdef PMP_PCB_VER_B 
    GPIO_O_SET(USB_DEVICE_CHIP_POWER_PIN,0);
   #else  //PMP_PCB_VER_C
    GPIO_O_SET(USB_DEVICE_CHIP_POWER_PIN,1);
    hwHddPowerOn();
   #endif
    #ifdef PMP_KEYBOARD//xyy add 2005-1-13
    Set_PMP_Key();
    #endif
}


#endif //#if defined(PMP_DVD)


//kenny 2005/5/12 move the code from pmp_drv.c
#ifdef IDE_CF_SW


/**************************************************************************
 *                                                                        *
 *  Function Name: hwCfCardStandby                                              *
 *                                                                        *
 *  Purposes:                                                             *
 *      disable CF card interface                                         *
 *  Descriptions:                                                         *
 *                                                                        *
 *  Arguments:                                                            *
 *      on     : 1 -> CF enter to stanby                                  *
 *               0 -> CF out of stand by mode                             *
 *  Returns:                                                              *
 *      None                                                              *
 *  See also:                                                             *
 *                                                                        *
 **************************************************************************/
void hwCfCardStandby(UINT8 on)
{
    
    regs0->sft_cfg3=regs0->sft_cfg3&(~(1<<7));//pin194 GPIO51
    GPIO_M_SET(51,1);
    GPIO_E_SET(51,1);
    
    if(on)
    {
   // printf("CF is OFF #########################\n");    
    GPIO_O_SET(51,0);
    delay_1ms(2);
    
    }
    else
    {
   // printf("CF is ON #########################\n");
    GPIO_O_SET(51,1);
    delay_1ms(10);
    }
    
}   



#endif //#ifdef IDE_CF_SW 

#ifdef SUPPORT_8202D_EXT_ADC//chenzhao2000118//chyeh 2005/03/21
void init_8202D_EXT_ADC(void)
{
    #ifdef SUPPORT_RECEIVER            //chyeh 2005/0809  
    regs0->sft_cfg13 &= (~((0x1f)<<4));  //pin 62 as EXT_ADC pin, for 8202 receiver PCB
        #ifdef MP_BOARD_216_PIN_NON_SHARE
        regs0->sft_cfg13 |= (0x04<<4);
        #elif defined(MP_BOARD_256_PIN_NON_SHARE)
            #if defined(OP_EXT_DAC_IN_256_PIN)
            regs0->sft_cfg13 |= (0x1c<<4);
            #else
            regs0->sft_cfg13 |= (0x0e<<4);
            #endif
        #else
        #error need configuration of EXT_ADC data pin.
        #endif
    #else
        #ifdef MP_BOARD_216_PIN_NON_SHARE   
            regs0->sdc_data_cnt[6][0] |= (0x02);  //disable ROM_A20
            regs0->sft_cfg13 &= (~((0x1f)<<4));   //pin 75 as EXT_ADC pin, for 8202D release board 
            regs0->sft_cfg13 |= (0x16<<4);
            #ifdef SDRAM1X4X16_USE_GPIO_39   //chyeh 2005-08-20
                regs0->sft_cfg0 &= (~((0x1)<<4));//Enable GPIO39
            #endif
            #ifdef SDRAM2X4X16_USE_GPIO_5
                regs0->sft_cfg4 &= (~((0x1)<<5)); //Enable GPIO5
            #endif     
        #elif defined( MP_BOARD_256_PIN_NON_SHARE )     
            regs0->sft_cfg13 &= (~((0x1f)<<4));   //pin 189 as EXT_ADC pin, for 8202D release board
            
                #ifdef USE_PIN190_AS_ADC_DATA   //pin 190 as EXT_ADC pin
                    regs0->sft_cfg13 |= (0x1e<<4); 
                #elif defined( USE_PIN188_AS_ADC_DATA ) // FanGang added for 8202A-256+6500 solution release board,2005-12-12 16:34
                    regs0->sft_cfg13 |= (0x1c<<4); //pin 188 as EXT_ADC pin,for 8202A-256+6500 solution release board
                #else
                    regs0->sft_cfg13 |= (0x1d<<4); 
                #endif
        #endif
        #ifdef EXT_ADC_RESET
            GPIO_M_SET(EXT_ADC_RESET,1);
            GPIO_E_SET(EXT_ADC_RESET,1);
            GPIO_O_SET(EXT_ADC_RESET,1);
        #endif  
    #endif  // SUPPORT_RECEIVER
}   
void disable_8202D_EXT_ADC(void)
{
    regs0->sft_cfg13 &= (~((0x1f)<<4));  //clear EXT ADC data pin config.
}
#endif  // SUPPORT_8202D_EXT_ADC








void reset_gpio(void)
{	 
#ifdef GAME_GPIO_USE_PIN52_125_181_182	//yaowh add 2006-3-13 13:42
    regs0->sft_cfg4 &= ~(0x1 << 5);
	regs0->sft_cfg0 &= ~(0x1 << 6);
	regs0->sft_cfg2 &= ~(0x3 << 2);
	regs0->sft_cfg4 &= ~(0x7 << 13);

	GPIO_M_SET(5, 0);	//CLK
	GPIO_M_SET(29, 0);	//LATCH
	GPIO_M_SET(60, 0);	//D0
	GPIO_M_SET(61, 0);	//D1
	GPIO_E_SET(5, 1);	//outup
	GPIO_E_SET(29, 1);
	GPIO_E_SET(60, 0);	//input
	GPIO_E_SET(61, 0);
#endif

#ifdef SUPPORT_ANTENNA_POWER_CONTROL ////yangli add for antenna  power ,2006-1-5 17:50
        GPIO_M_SET(SENSOR_ANT_POWER_8202_PIN,1);
	    GPIO_E_SET(SENSOR_ANT_POWER_8202_PIN,0);
	#endif

#ifdef MTC_DVD_DVB_8202D_6600/////////ADD BY YANGLI,FOR mtc DVB STANDBY2005-12-20 20:45
    GPIO_M_SET(CONTROL_STANDBY_GPIO, 1);
    GPIO_E_SET(CONTROL_STANDBY_GPIO, 1);
    GPIO_O_SET(CONTROL_STANDBY_GPIO, 1);
#endif   
    #ifdef ROM_BUS_EXTENT_IO    //hongfeng 2005-08-08
    GPIO_M_SET(16, 1);
    GPIO_E_SET(16, 1);
    GPIO_O_SET(16, 1);
    regs0->sft_cfg1  &=  ~(1<<3);//aviod play DTS write CS4 hongfeng 2005-08-05

    /*huziqin move these 2 line from rom_bus_io.c*/
    regs0->rom3_base      = (0x400000>>16);// 64;
    regs0->oe_wait_cyc3_2 = 0x0400;
    #endif 

#if  0//use SUPPORT_UPD68A_READY_PIN instead.chenzhao20060107//defined(ORITRON_RECEIVER_6001)&&defined(SUPPORT_MCU_68A)  //for OP 68A hongfeng 2005-08-09
    GPIO_M_SET(9, 1);
    GPIO_E_SET(9, 1);
    GPIO_O_SET(9, 1);
    #endif
#ifdef SUPPORT_UPD68A_READY_PIN//chenzhao20060107
    SET_UPD68A_READY_GPIO();
    SET_UPD68A_READY_POWER_ON(); //to power on
#endif

#ifdef  ORITRON_RECEIVER_6001//for OP control tuner power hongfeng 2005-08-10
    regs0->sft_cfg3 &= ~(0x1 << 4);
    GPIO_M_SET(56, 1);
    GPIO_E_SET(56, 1);
#endif
    #ifdef STBY_CONTROLLER_IO_58PIN_10GPIO      //for OP hongfeng 2005-07-14

    GPIO_M_SET(10,1);   //pin 58 gpio 10 s-by
    GPIO_E_SET(10,1);   //pin 58 gpio 10 s-by
    GPIO_O_SET(10,1);    //pin 58 gpio 10 s-by

    #endif

    #ifdef  CONTROL_STANDBY_MCU
    #ifdef CONTROL_DVD4125_POWER_GPIO //PIN68 caoh 2005-6-20 13:13
      regs0->sft_cfg1 &= ~(0x1 << 1);
      GPIO_M_SET(CONTROL_POWER_GPIO,1);   
      GPIO_E_SET(CONTROL_POWER_GPIO,1);  
      GPIO_O_SET(CONTROL_POWER_GPIO,1); 
    #elif defined(CONTROL_DVD5115_POWER_GPIO) //57pin caoh 2005-6-20 13:13
      GPIO_M_SET(CONTROL_POWER_GPIO,1);   
      GPIO_E_SET(CONTROL_POWER_GPIO,1);
      GPIO_O_SET(CONTROL_POWER_GPIO,1);
      
    #elif defined(CONTROL_DVD5121_POWER_GPIO) //57pin caoh 2005-6-20 13:13
      GPIO_M_SET(CONTROL_POWER_GPIO,1);   
      GPIO_E_SET(CONTROL_POWER_GPIO,1);
      GPIO_O_SET(CONTROL_POWER_GPIO,1); 
   
    #elif defined(CONTROL_DVD6122_POWER_GPIO) //57pin caoh 2005-6-20 13:13
      regs0->sft_cfg13 &= ~(0xf << 0);
      GPIO_M_SET(CONTROL_POWER_GPIO,1);   
      GPIO_E_SET(CONTROL_POWER_GPIO,1);
      GPIO_O_SET(CONTROL_POWER_GPIO,1);          
    #endif    
    
        
 #endif
  
  #ifdef NO_CONTROL_POWER_MCU   
    #ifdef CONTROL_DVD3111_POWER_GPIO //57pin caoh 2005-6-20 13:13
      GPIO_M_SET(CONTROL_POWER_GPIO,1);   
      GPIO_E_SET(CONTROL_POWER_GPIO,1);
      GPIO_O_SET(CONTROL_POWER_GPIO,1);
    #elif defined(CONTROL_DVD4110_POWER_GPIO) //57pin caoh 2005-6-20 13:13
      GPIO_M_SET(CONTROL_POWER_GPIO,1);   
      GPIO_E_SET(CONTROL_POWER_GPIO,1);
      GPIO_O_SET(CONTROL_POWER_GPIO,1);
    #elif defined(CONTROL_DVD5112_POWER_GPIO) //57pin caoh 2005-6-20 13:13
     GPIO_M_SET(CONTROL_POWER_GPIO,1);   
     GPIO_E_SET(CONTROL_POWER_GPIO,1);
     GPIO_O_SET(CONTROL_POWER_GPIO,1);      
    #endif
  #endif        

    #ifdef MIDI_CHECK_PASSWORD_PASS_MCU //lijd 2005-2-25 14:25
        //Set gpio STB,CLK,DAT use for RISC    
        GPIO_M_SET(STB, 1);
        GPIO_M_SET(CLK, 1);
        GPIO_M_SET(DAT, 1);
        //Set gpio STB  as input port
        GPIO_E_SET(STB, 0);
        //Set gpio CLK,DAT as output port        
        GPIO_E_SET(CLK, 1);
        GPIO_E_SET(DAT, 1);
        //Set gpio CLK,DAT output high        
        GPIO_O_SET(CLK, 1);
        GPIO_O_SET(DAT, 1);
    #endif

//wanghaoying add 2005-3-28 9:51 for wuxi-oritron w5690 type: slot in loader dector pin
#ifdef W5690
    //---> set 8202/256 pin62 as gpio5
    regs0->sft_cfg2 &= ~(0x3 << 10);
    regs0->sft_cfg4 &= ~(0x1 << 5);
    regs0->sft_cfg8 &= ~(0x3 << 8);
    //---> set gpio5 control by RISC
    GPIO_M_SET(5,1);
    //---> set gpio5 as input pin
    GPIO_E_SET(5,0);

    //---> set 8202/256 pin65 as gpio8
    regs0->sft_cfg2 &= ~(0x3 << 10);
    regs0->sft_cfg4 &= ~(0x1 << 6);
    regs0->sft_cfg8 &= ~(0x1 << 9);
    //---> set gpio8 control by RISC
    GPIO_M_SET(8,1);
    //---> set gpio8 as input pin
    GPIO_E_SET(8,0);
    //---> set 8202/256 pin78 as gpio18
    regs0->sft_cfg1 &= ~(0x1 << 1);
    regs0->sft_cfg8 &= ~(0x1 << 9);
    //---> set gpio18 control by RISC
    GPIO_M_SET(18,1);
    //---> set gpio18 as input pin
    GPIO_E_SET(18,0);
#endif//#ifdef W5690
    
#ifdef SHINCO_DVD
    //wanghaoying 2005-9-15 16:12 add to light the led
    // when standby mode, pull high; or pull low.
    regs0->sft_cfg1 &= ~(0x1 << 3);//GPIO16
    GPIO_M_SET(16,1);
    GPIO_E_SET(16,1);
    GPIO_O_SET(16,1);
#endif 

    #if defined(MINTON_DVD)&&defined(TOP_DOOR_LOADER)  //liudan,for ngailik top_door sense pin,2005-1-12 11:31
    regs0->sft_cfg4 &= ~(0x1 << 6);
    
    GPIO_M_SET(8,1);
    GPIO_E_SET(8,0);
    #endif
    
    #ifdef IR_SWITCH_CD_USB_CF_OTHER  //dingzhy use vfd data test bus switch 4-10-22 10:41
         GPIO_E_SET(23,1);
    #endif
    
    #ifdef AKI_2CH_KEY_SCAN     //linrc add for AKI 2004-12-31 10:42
    GPIO_M_SET(22,1);
    GPIO_M_SET(23,1);
    GPIO_E_SET(22,1);
    GPIO_E_SET(23,1);
    GPIO_O_SET(22,1);
    GPIO_O_SET(23,1);
    #endif
    
    #ifdef NINTAUS_612_SCAN_KEY     //linrc 2004-6-9 17:52
    regs0->sft_cfg1 &= ~(0x1 << 3);//PIN29 use as CARD_RESET gpio3
    
    GPIO_M_SET(3,1);
    GPIO_M_SET(4,1);
    GPIO_M_SET(54,1);//set  used by RISC
    GPIO_M_SET(55,1);//set   
    GPIO_M_SET(56,1);//set   
    GPIO_E_SET(54,0);//set  CLK as input
    GPIO_E_SET(55,0);//set  STB as input
    GPIO_E_SET(56,1);//set  STB as output  
    GPIO_E_SET(3,1);   //linrc modify 2004-6-7 19:30 
    GPIO_E_SET(4,1);
    #endif      //end NINTAUS_612_SCAN_KEY
    
    #if defined(HANYANG_SCAN_KEY)||defined(HJ2439_SCAN_KEY)  //caoh  2004-4-19 12:00
    regs0->sft_cfg3 &= ~(0x1 << 5);//PIN163 use as SCART_RGB gpio57
    regs0->sft_cfg6 &= ~(0x1 << 5);//PIN151 use as SCART_SW gpio18
    GPIO_M_SET(54,1);
    GPIO_M_SET(55,1);
    GPIO_M_SET(56,1);
    GPIO_M_SET(57,1);
    GPIO_M_SET(18,1);
    
    GPIO_E_SET(57,1);
    GPIO_E_SET(18,1);
    GPIO_E_SET(55,1);
    #endif   
    
#ifdef DP3240_KEY_SCAN   // add xrh 
    #ifdef STBY_CONTROLLER_IO_61PIN_12GPIO
    GPIO_M_SET(12,1);   //pin 61 gpio 12 s-by
    GPIO_E_SET(12,1);   //pin 61 gpio 12 s-by
       GPIO_O_SET(12,1);    //pin 61 gpio 12 s-by
       #endif

    GPIO_M_SET(PLAY_LED_1,1);   //  gpio 13  pin 62  led 2
    GPIO_E_SET(PLAY_LED_1,1);   // gpio 13   pin 62  led 2
    GPIO_O_SET(PLAY_LED_1,1);
    
   
    
    GPIO_M_SET(POWER_LED_2,1);   // gpio 14 pin 63  led 3
    GPIO_E_SET(POWER_LED_2,1);   //gpio 14 pin 63  led 3
    GPIO_O_SET(POWER_LED_2,1);
#endif

// mimitsai merge from dp2070/dp3240
#ifdef DP2070_KEY_SCAN   
    GPIO_M_SET(PLAY_LED_1,1);   //  gpio 12  pin 61  led 1
    GPIO_E_SET(PLAY_LED_1,1);   // gpio 12   pin 61  led 1
    GPIO_O_SET(PLAY_LED_1,0);
   
    GPIO_M_SET(POWERON_LED_0,1);   // gpio 14 pin 63  led 0
    GPIO_E_SET(POWERON_LED_0,1);   //gpio 14 pin 63  led 0
    GPIO_O_SET(POWERON_LED_0,0);
#endif  //#ifdef DP2070_KEY_SCAN   

   #ifdef DP2030_SCAN_KEY  //caoh  2004-4-19 12:00

    GPIO_M_SET(PANEL_LED_PLAY,1);   //PANEL_LED1  pin82     
    GPIO_E_SET(PANEL_LED_PLAY,1);       //SETUP AS OUTPUT 
        GPIO_O_SET(PANEL_LED_PLAY,1);   //PLAY 
        
        GPIO_M_SET(PANEL_LED_POWER,1);      //PANEL_LED2    pin83
        GPIO_E_SET(PANEL_LED_POWER,1);
        GPIO_O_SET(PANEL_LED_POWER,1);  //POWER
    
    GPIO_M_SET(23,1);       //SCAN_KEY1 pin84    
    GPIO_M_SET(93,1);       //SCAN_KEY2 pin226    
    GPIO_M_SET(94,1);       //SCAN_KEY3 pin227
    GPIO_M_SET(97,1);   //SCAN_KEY4 pin230
    GPIO_M_SET(98,1);       //SCAN_KEY5 pin231
    GPIO_M_SET(100,1);      //SCAN_KEY6 pin233

    GPIO_M_SET(99,1);   //DOOR_SENSE_GPIO

    
    
    GPIO_E_SET(23,1);       //KEY1
    GPIO_E_SET(93,1);       //KEY2
    GPIO_E_SET(98,1);       //KEY5

    
    GPIO_E_SET(99,0);   //as input  DOOR_SENSE_GPIO
    GPIO_E_SET(94,0);       //KEY3
    GPIO_E_SET(97,0);       //KEY4
    GPIO_E_SET(100,0);      //KEY6

    //GPIO_O_SET(DOOR_SENSE_GPIO,1);
    #endif//#ifdef DP2030_SCAN_KEY 

#ifdef DP30H0_KEY_SCAN  //add  2004-5-14 xia        
//wthsin
    regs0->sdc_data_cnt[6][0] |= (0x0c);//Disable ROM_A21(Pin226),ROM_A22(Pin227) as GPIO93,94  
    GPIO_M_SET(21,1);   //PANEL_LED1  pin82
    GPIO_M_SET(22,1);   //PANEL_LED2  pin83
    GPIO_M_SET(23,1);      //bit   PIN 84
    regs0->sft_cfg1 &= ~(0x1 << 4); //gpio 94  intput
    regs0->sft_cfg1 &= ~(0x1 << 5); //gpio 97  output
    GPIO_M_SET(93,1);       //SCAN_KEY1 pin226
    GPIO_M_SET(94,1);       //SCAN_KEY2 pin227
    GPIO_M_SET(97,1);       //SCAN_KEY3 pin230
    GPIO_M_SET(98,1);   //SCAN_KEY4 pin231
    GPIO_M_SET(99,1);       //SCAN_KEY5 pin232  
    GPIO_M_SET(100,1);      //SCAN_KEY6 pin233
    GPIO_E_SET(21,1);       //SETUP AS OUTPUT 
    GPIO_E_SET(22,1);
    GPIO_E_SET(23,1);   
    GPIO_E_SET(97,1);       //KEY3
    GPIO_E_SET(98,1);       //KEY4
    GPIO_E_SET(99,1);       //KEY5
    GPIO_E_SET(100,1);      //KEY6
    GPIO_E_SET(93,0);   //key1
    GPIO_E_SET(94,0);   //key2
    GPIO_O_SET(PANEL_LED_POWER,1);  //POWER
    GPIO_O_SET(PANEL_LED_PLAY,1);   //PLAY  
    GPIO_O_SET(PANEL_LED_CLOCK,0);      //clock
    GPIO_O_SET(IR_LED,0);
#endif//#ifdef DP30H0_KEY_SCAN
//dingzhy  3-11-17 10:15    
#ifdef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313
    regs0->sft_cfg6 &= ~(0x1 << 4); // A11 as GPIO14
    regs0->sft_cfg6 &= ~(0x1 << 6); // BA1 as GPIO15
    GPIO_M_SET(14,1);//1 risc use
    GPIO_M_SET(15,1);
    GPIO_M_SET(56,1);
    GPIO_M_SET(55,1);
    GPIO_M_SET(54,1);
    GPIO_E_SET(14,0);// 0 input
    GPIO_E_SET(15,0);
    GPIO_E_SET(56,0);
    GPIO_E_SET(55,0);
    GPIO_E_SET(54,0);
    
    
    regs0->sft_cfg1 &= ~(0x1 << 3);//GPIO3  pin29 use as MP3 LIGHT
    regs0->sft_cfg3 &= ~(0x3 << 14);//GPIO62 63  pin175 176 use as DVD CD LIGHT
    regs0->sft_cfg2 &= ~(0x7 << 2);//GPIO62 63  pin175 176 use as DVD CD LIGHT
    GPIO_M_SET(3,1);//1 risc use
    GPIO_M_SET(62,1);
    GPIO_M_SET(63,1);
    GPIO_E_SET(3,1);// 1 output
    GPIO_E_SET(62,1);
    GPIO_E_SET(63,1);
       
    GPIO_O_SET(3,1);
    GPIO_O_SET(62,1);
    GPIO_O_SET(63,1);
#endif      
    
#ifndef ROM_ATA_SHARE_BUS   
    regs0->sft_cfg1 &= ~(0x3 << 1);
#else
    #ifdef SUPPORT_CARD_STORAGE
        regs0->sft_cfg1 |= (0x7 << 0);
        regs0->sft_cfg1 &= ~(0x1 << 3);
    #endif
#endif

#ifdef PORTABLE_DVD //Jack added for all PDVD customers
    portable_reset_gpio(); //0725 splitted for portable
#endif

/*
#ifdef SUPPORT_8202_EXT_ADC        //chyeh 2005/03/21
	regs0->sft_cfg3 &= 0xf3ff;       
	regs0->sft_cfg3 |= 0x0400;
#endif
*/

#ifdef SUPPORT_8202D_EXT_ADC        //chyeh 2005/03/21
    init_8202D_EXT_ADC();
#endif  // SUPPORT_8202D_EXT_ADC

#ifdef SUPPORT_RECEIVER     // benosn add extrenal AD interface PIN 130,131,133 
#ifdef SUPPORT_EXT_ADC  
    regs0->sft_cfg0 &= ~((0x0fffc)<<1);
    regs0->gpio_master[2]|= 0x01b0;    //GPIO 37~47
        //regs0->gpio_oe[2]|= 0xe980;        
        regs0->gpio_oe[2]&= ~(0x01b0);     
        //regs0->gpio_out[2]|= 0x0900;
        //regs0->gpio_out[2]&= ~(0xe080);       
        regs0->sft_cfg3 &= 0xfff8;
        regs0->sft_cfg3 |= 0x0004;
#endif  


#ifdef SUPPORT_8202_216_EXT_ADC    //  benson add 2004.08.18  pin 59,61,62 hongfeng modify 2005-05-18
	regs0->sft_cfg3 &= 0xf3ff;
	regs0->sft_cfg3 |= 0x0400;  
#endif

#ifdef SUPPORT_8202_EXT_ADC    //  benson add 2004.08.23  pin 169,171,172
	regs0->sft_cfg3 &= 0xf3ff;
	regs0->sft_cfg3 |= 0x0800;  
#endif

#endif

#ifdef ALCO_PORTABLE
    alco_portable_reset_gpio(); 
#endif

    #if defined(SUPPORT_USB)&&defined(HOST_SL811HS) //wthsin, 2004/1/12 01:36pm
        regs0->sft_cfg1 |= (0x7 << 0);
    #endif

/*a block is removed. huziqin 2004-2-26*/
    
#ifdef PCM1742 //Jeff 20030917
    regs0->sft_cfg1 |= (0x7 << 0);
    regs0->sft_cfg1 &= ~(0x1 << 3);
#endif

#if defined(PCM1742)&&defined(CHECK_DAC_ZERO_FLAG_TO_GPIO_MUTE)     //gerry,3-10-20 11:36
    regs0->sft_cfg6 &= ~(0x1 << 4); // SA11 as GPIO 14, pin 109
    GPIO_M_SET(14,1);//GPIO_M_SET(35,1);
    GPIO_E_SET(14,0);//GPIO_E_SET(35,0);    
#endif

#ifdef USE_CD_SENSE_PIN_AS_LED_GPIO     //gerry,2004-2-10 18:33
    GPIO_M_SET(4,1);
    GPIO_E_SET(4,1);
    GPIO_O_SET(4,0);
#endif//USE_CD_SENSE_PIN_AS_LED_GPIO

#ifdef USE_PIN31_CONTROL_POWER_LED      //gerry,normal led is high on,2004/2/11 05:31下午
    GPIO_M_SET(4,1);
    GPIO_E_SET(4,1);
    GPIO_O_SET(4,0);
#endif//USE_PIN31_CONTROL_POWER_LED

#ifdef GBM_USE_GPIO_CONTROL_LED         //use gpio44(pin138) control led on/off,2004/2/11 08:54下午
    GPIO_M_SET(44,1);
    GPIO_E_SET(44,1);
    GPIO_O_SET(44,1);
#endif//GBM_USE_GPIO44_CONTROL_LED

#if defined(SUPPORT_CARD_STORAGE) && defined(CARD_HOT_PLUG)
  //#ifndef GBM_CARD_READER
  #if (!defined(GBM_CARD_READER))&&(!defined(HJ023_CARD_READER))&&(!defined(QSI_PORTABLE_DVD))//wangfeng 2003-12-3 21:32
        #ifdef MIDI_4_FSLOADER_CARD
            regs0->sft_cfg3 &= ~(0x1 << 5); //PIN163 use as CD_CARD_DETECT_PIN(GPIO57)
        #else
            regs0->sft_cfg6 &= ~(0x1 << 4);//PIN109 use as SCART_SW1 gpio14 //wthsin
        #endif
  #endif//#ifndef GBM_CARD_READER
    regs0->gpio_master[CARD_RESET_PIN / 16] |= (0x1 << (CARD_RESET_PIN % 16));
    regs0->gpio_master[CF_CARD_DETECT_PIN / 16] |= (0x1 << (CF_CARD_DETECT_PIN % 16));
    regs0->gpio_master[CD_CARD_DETECT_PIN / 16] |= (0x1 << (CD_CARD_DETECT_PIN % 16));
#elif defined(CF_GPIO_CONTROL_COLOR)

   // #define VFD_BACK_COLOR_RED        3 //GPIO 17 ca720 pin29
    //#define VFD_BACK_COLOR_GREEN    2 //GPIO 18 ca720 pin28
   // #define VFD_BACK_COLOR_BLUE    4 //GPIO 19 ca720 pin163
    regs0->gpio_master[3 / 16] |= (0x1 << (3 % 16));
    regs0->gpio_master[2 / 16] |= (0x1 << (2 % 16));
    regs0->gpio_master[4 / 16] |= (0x1 << (4 % 16));

      GPIO_E_SET(3,1);
      GPIO_E_SET(2,1);
      GPIO_E_SET(4,1);

#endif

#ifdef CHECKPHONE               //////////////////////yangli2004-10-10
regs0->sft_cfg3 &= ~((0x01)<<8);  //////PIN164 use as PHONE_SW gpio58
    GPIO_M_SET(58,1);
    GPIO_E_SET(58,0);
#endif

#ifdef AUDIO_MUTE_2
    regs0->sft_cfg1 |= (0x7 << 0);
    regs0->sft_cfg1 &= ~(0x1 << 3);
    
    regs0->gpio_master[ 2/16 ] |= 0x1 << (2%16);
    regs0->gpio_master[ 3/16 ] |= 0x1 << (3%16);
    
    regs0->gpio_oe[ 2/16 ] |= 0x1 << (2%16);
    regs0->gpio_out[2/16 ] &= ~(0x1 << (2%16));
    regs0->gpio_oe[ 3/16 ] |= 0x1 << (3%16);
    regs0->gpio_out[3/16 ] &= ~(0x1 << (3%16));
    
    delay_1ms(1000);
    regs0->gpio_out[3/16 ] |= (0x1<<(3%16));
    delay_1ms(1000);
    regs0->gpio_out[2/16 ] |= (0x1<<(2%16));
#endif

#ifdef USE_PIN151CN_LED         //freyman 2004-3-16 11:19 for wuxi oritron  
    regs0->sft_cfg6 &= ~(0x1 << 5);
    GPIO_M_SET(18,1);
    GPIO_E_SET(18,1);
    GPIO_O_SET(18,0);
#endif

#if defined(SUPPORT_AUDIO_RESET)&&defined(HANYANG_4340_AUDRESET)
//#ifdef SUPPORT_AUDIO_RESET     //2004-4-27 01:03?迻M
    GpioResetAudio();
#endif    

#if defined(SCART_TV)&&defined(ORI_SCART_TV)
    // GPIO39 (ROM_ADDR22) = SCART_SIGNAL_MODE
    // GPIO38 (ROM_ADDR21) = SCART_DISPLAY_MODE
    // GPIO37 (ROM_ADDR20) = SCART_RELEASE_TV

    regs0->sft_cfg0 &= ~(0x3f << 1);
    regs0->gpio_oe[37 / 16] |= (0x7 << (37 % 16));

    regs0->gpio_out[37 / 16] &= ~(0x1 << (37 % 16));
    regs0->gpio_out[38 / 16] &= ~(0x1 << (38 % 16));
    regs0->gpio_out[39 / 16] &= ~(0x1 << (39 % 16));
#elif defined(KSD_SCART_TV)
    regs0->sft_cfg3 &= ~(0x1 << 5);//PIN163 use as SCART_RGB gpio57
    regs0->sft_cfg6 &= ~(0x1 << 5);//PIN151 use as SCART_SW gpio18
    GPIO_M_SET(57,1);
    GPIO_E_SET(57,1);
    GPIO_O_SET(57,0);
    
    GPIO_M_SET(18,1);
    GPIO_E_SET(18,1);
    GPIO_O_SET(18,0);

#elif defined(SCART_TV_2)       //wanghaoying 2003-8-13 15:11 added
    regs0->sft_cfg3 &= ~(0x1 << 5);//PIN163 use as SCART_RGB gpio57
    regs0->sft_cfg6 &= ~(0x1 << 5);//PIN151 use as SCART_SW gpio18
    GPIO_M_SET(57,1);
    GPIO_E_SET(57,1);
    GPIO_O_SET(57,0);
    
    GPIO_M_SET(18,1);
    GPIO_E_SET(18,1);
    GPIO_O_SET(18,0);

    #ifdef NIN_SCART_TV //fangang added 4-2-11 17:13
    GPIO_M_SET(2,1);    //pin28 use as scart_standby gpio2
    GPIO_E_SET(2,1);
    GPIO_O_SET(2,0);
    #endif

    #ifdef YILI_SCART_TV      //hq add for ngailik 1003, 4-2-17 10:03
    GPIO_M_SET(4,1);    //pin31 use as scart_standby gpio2
    GPIO_E_SET(4,1);
    GPIO_O_SET(4,0);    
    #endif
    
    #ifdef GBM_USE_A11_AS_SCART_TV_RELEASE
    regs0->sft_cfg6 &= ~(0x1 << 4);
    GPIO_M_SET(14, 1);
    GPIO_E_SET(14, 1);
    GPIO_O_SET(14, 0);
    #endif

    #ifdef SCART_TV_2_ADD_RELEASE  //David 2003-12-6 10:25
    regs0->sft_cfg1 &= ~(0x01 << 2);  // pin71 GPIO36
    GPIO_M_SET(36,1);
    GPIO_E_SET(36,1);
    GPIO_O_SET(36,0);
    #endif
    
#elif defined(SCART_TV_3)
    regs0->sft_cfg3 &= ~(0x1 << 5);//PIN163 use as SCART_RGB gpio57
    regs0->sft_cfg6 &= ~(0x1 << 5);//PIN151 use as SCART_SW gpio18
    regs0->sft_cfg6 &= ~(0x1 << 4);//PIN109 use as SCART_SW1 gpio14
   #if defined(SKYWORTH_DVD)
    GPIO_M_SET(57,1);
    GPIO_E_SET(57,1);
    GPIO_O_SET(57,0);
   #else    
        GPIO_M_SET(57,1);
    GPIO_E_SET(57,1);
    GPIO_O_SET(57,1);
   #endif   
    GPIO_M_SET(18,1);
    GPIO_E_SET(18,1);
    GPIO_O_SET(18,0);

    GPIO_M_SET(14,1);
    GPIO_E_SET(14,1);
    GPIO_O_SET(14,0);
#elif defined(SCART_TV_4)       //nono 2003-9-26 1:23 for himage HJ-018
    regs0->sft_cfg1 |= (0x7 << 0);//pin28   use as SCART_TV gpio2//SCART_SW1
    regs0->sft_cfg1 &= ~(0x1 << 3);//pin29  use as SCART_RGB gpio3

    GPIO_M_SET(2,1);
    GPIO_E_SET(2,1);
    GPIO_O_SET(2,0);
    
    GPIO_M_SET(3,1);
    GPIO_E_SET(3,1);
    GPIO_O_SET(3,0);
    
    GPIO_M_SET(4,1);//pin31 use as SCART_SW gpio4
    GPIO_E_SET(4,1);
    GPIO_O_SET(4,0);
#elif defined(SCART_TV_5)//wangfeng 2003-12-2 11:43 for himage HJ-023
    SetScartTV5();
    GPIO_O_SET(62,0);
    GPIO_O_SET(63,0);
    //GPIO_O_SET(2,0);  
#elif defined(XQ_SCART_TV)//xyy 2004-4-29
    regs0->sft_cfg6 &= ~(0x1 << 5);//used to set pin151(GPIO18),SCART_DISPLAY
    GPIO_M_SET(SCART_RELEASE,1);
    GPIO_E_SET(SCART_RELEASE,1);
    GPIO_M_SET(SCART_SIG,1);
    GPIO_E_SET(SCART_SIG,1);
    GPIO_M_SET(SCART_DISPLAY,1);
    GPIO_E_SET(SCART_DISPLAY,1);
    
#endif

#ifndef DVD_SERVO
    regs0->sft_cfg2 |=1;    // for 8200 real chip + ATAPI loader
#endif

#ifdef SUPPORT_VIDEO_BUFFER_STANDBY //kenny 2003/5/13    
    video_buff_power_on();
#endif

#ifdef SUPPORT_EXTERNAL_MIC
    extern_mic_detect_on();
#endif  

    SFT_CFG_GPIO();
#if defined(VIDEO_IN_CONTROL)
    #if defined(ALCO_PV1950)||defined(ALCO_PVS19251) 
    if(!(GPIO_I_GET(INT_EXT_VIDEO_GPIO1)+GPIO_I_GET(INT_EXT_VIDEO_GPIO2)))
    #elif defined(ALCO_PVS177W)||defined(ALCO_PVS1090_AVIN)//shenyj add for alco177w 
    if(GPIO_I_GET(INT_EXT_VIDEO_GPIO))
    #endif
#endif
    GPIO_MUTE();

#ifdef SUPPORT_SCART_TV//SPHE8202//nono 4-3-26 23:45
    SET_SCART_GPIO_SFT_CFG_CTRL();

    SCART_TV_SET_TO_CVBS();
    SCART_TV_SET_TO_DVDPLAYER();
    SCART_TV_SET_TO_DISPLAY_4B3();

#endif//SPHE8202

/*deleted by xyy 2004-8-12*/


#ifdef SUPPORT_COAXIAL_IN//xyy 2004-4-29 10:22 for XQ
    GPIO_M_SET(OPT_COAX_SEL,1);//GPIO48: OPTICAL/COAXIAL SEL
    GPIO_E_SET(OPT_COAX_SEL,1);
#endif

#ifndef SUPPORT_EXT_MCU
#ifdef SUPPORT_EXT_ADC//xyy 2004-4-29 
    GPIO_M_SET(EXT_ADC_RESET,1);
    GPIO_E_SET(EXT_ADC_RESET,1);
#endif
#endif

#ifdef PROVIEW_GPIO_KEY

    //#define DVD_LED_GPIO          56 // VFD_DATA
    //#define CD_LED_GPIO           54 // VFD_CLK
    //#define MP3_LED_GPIO          55 // VFD_STB

    //#define NEXT_KEY_GPIO         2 // CARD_RESET
    //#define PREV_KEY_GPIO         14
    //#define STOP_KEY_GPIO         3 // CF_SENSE
    //#define PAUSEPLAY_KEY_GPIO    15
    //#define EJECT_KEY_GPIO        32

    regs0->sft_cfg0 &= ~(0x1 << 0); // pin 66 as GPIO 32
    regs0->sft_cfg1 &= ~(0x1 << 3); // CS4 as GPIO3
    regs0->sft_cfg6 &= ~(0x1 << 4); // A11 as GPIO14
    regs0->sft_cfg6 &= ~(0x1 << 6); // BA1 as GPIO15
       #ifndef PROVIEW_GPIO_KEY_527
    regs0->gpio_master[NEXT_KEY_GPIO / 16] |= (0x1 << (NEXT_KEY_GPIO % 16));
    regs0->gpio_master[PREV_KEY_GPIO / 16] |= (0x1 << (PREV_KEY_GPIO % 16));
       #endif // PROVIEW_GPIO_KEY_527   
    regs0->gpio_master[STOP_KEY_GPIO / 16] |= (0x1 << (STOP_KEY_GPIO % 16));
    regs0->gpio_master[PAUSEPLAY_KEY_GPIO / 16] |= (0x1 << (PAUSEPLAY_KEY_GPIO % 16));
    regs0->gpio_master[EJECT_KEY_GPIO / 16] |= (0x1 << (EJECT_KEY_GPIO % 16));
       #ifndef PROVIEW_GPIO_KEY_527 
    regs0->gpio_master[DVD_LED_GPIO / 16] |= (0x1 << (DVD_LED_GPIO % 16));
    regs0->gpio_master[CD_LED_GPIO / 16] |= (0x1 << (CD_LED_GPIO % 16));
    regs0->gpio_master[MP3_LED_GPIO / 16] |= (0x1 << (MP3_LED_GPIO % 16));
       #else
        regs0->gpio_master[RED_LED_GPIO / 16] |= (0x1 << (RED_LED_GPIO % 16));
    regs0->gpio_master[GREEN_LED_GPIO / 16] |= (0x1 << (GREEN_LED_GPIO % 16));   
       #endif // PROVIEW_GPIO_KEY_527  
       
       #ifndef PROVIEW_GPIO_KEY_527
    regs0->gpio_oe[NEXT_KEY_GPIO / 16] &= ~(0x1 << (NEXT_KEY_GPIO % 16));
    regs0->gpio_oe[PREV_KEY_GPIO / 16] &= ~(0x1 << (PREV_KEY_GPIO % 16));
       #endif // PROVIEW_GPIO_KEY_527  
    regs0->gpio_oe[STOP_KEY_GPIO / 16] &= ~(0x1 << (STOP_KEY_GPIO % 16));
    regs0->gpio_oe[PAUSEPLAY_KEY_GPIO / 16] &= ~(0x1 << (PAUSEPLAY_KEY_GPIO % 16));
    regs0->gpio_oe[EJECT_KEY_GPIO / 16] &= ~(0x1 << (EJECT_KEY_GPIO % 16));
   #ifndef PROVIEW_GPIO_KEY_527 
    regs0->gpio_oe[DVD_LED_GPIO / 16] |= (0x1 << (DVD_LED_GPIO % 16));
    regs0->gpio_oe[CD_LED_GPIO / 16] |= (0x1 << (CD_LED_GPIO % 16));
    regs0->gpio_oe[MP3_LED_GPIO / 16] |= (0x1 << (MP3_LED_GPIO % 16));
   #else 
    regs0->gpio_oe[RED_LED_GPIO / 16] |= (0x1 << (RED_LED_GPIO % 16));
    regs0->gpio_oe[GREEN_LED_GPIO / 16] |= (0x1 << (GREEN_LED_GPIO % 16));   
   #endif // PROVIEW_GPIO_KEY_527  
 #ifndef PROVIEW_GPIO_KEY_527 
  #ifdef LED_HIGH_LIGHT
    GPIO_O_SET(DVD_LED_GPIO, 0); // DVD
    GPIO_O_SET(CD_LED_GPIO, 0); // CD
    GPIO_O_SET(MP3_LED_GPIO, 0); // MP3
  #else
    GPIO_O_SET(DVD_LED_GPIO, 1); // DVD
    GPIO_O_SET(CD_LED_GPIO, 1); // CD
    GPIO_O_SET(MP3_LED_GPIO, 1); // MP3
  #endif
 #else
  #ifdef LED_HIGH_LIGHT
    GPIO_O_SET(RED_LED_GPIO, 0);  
    GPIO_O_SET(GREEN_LED_GPIO, 0);       
  #else
    GPIO_O_SET(RED_LED_GPIO, 1);  
    GPIO_O_SET(GREEN_LED_GPIO, 1);  
  #endif
 #endif
#endif

#ifdef ROTARY_VOLUME
#ifdef HJ_8202_8408
     regs0->sft_cfg1 &= ~(0x1 << 3);//GPIO16
     regs0->sft_cfg1 &= ~(0x1 << 2);//GPIO17
     GPIO_M_SET(16,1);
     GPIO_M_SET(17,1);
     GPIO_E_SET(16,0);
     GPIO_E_SET(17,0);
#else    
    regs0->sft_cfg6 &= ~(0x1 << 6);
    regs0->sft_cfg6 &= ~(0x1 << 4);
    regs0->gpio_master[14/16] |= (0x3 << (14%16));
    regs0->gpio_oe[14/16] &= ~(0x3 << (14%16) );
    //regs0->gpio_out[14/16] &= ~(0x3 << (14%16) );
#endif 
#endif   

#ifdef GPIO14_STANDBY_LED  //for Ngailik LCD1003_6ch, hq, 2004-3-20 14:06
    regs0->sft_cfg6 &= ~(0x1 << 4); 
    GPIO_M_SET(14,1);
    GPIO_E_SET(14,1);
    GPIO_O_SET(14,0);
#endif     

#ifdef GPIO15_STANDBY_LED  //for Ngailik LCD1003, liudan, 2005-1-12 11:35	
	GPIO_M_SET(15,1);
        GPIO_E_SET(15,1);
        GPIO_O_SET(15,0);
#endif       

#if defined(QSI_PORTABLE_DVD) && defined(QSI_PLATFORM)  //qsi: merge by johnson 20040712
//#ifdef MA0QS1_SLM
    GPIO_M_SET(GPIO_IS_FOR_SLED_OP_SW,1);
    GPIO_E_SET(GPIO_IS_FOR_SLED_OP_SW,0);
    GPIO_M_SET(GPIO_IS_FOR_EJECT_BUTTON,1);
    GPIO_E_SET(GPIO_IS_FOR_EJECT_BUTTON,0);
    GPIO_M_SET(GPIO_IS_FOR_SYSTEM_LED,1);
    GPIO_E_SET(GPIO_IS_FOR_SYSTEM_LED,1);
    GPIO_O_SET(GPIO_IS_FOR_SYSTEM_LED,0);
//#endif
//qsi: add by sharon
#endif

#ifdef DVI_AUDIO_MUTE
#ifdef SPHE8202

#else /*SPHE8202*/
#define AUDIO_MUTE_GPIO 37
regs0->sft_cfg0 &= ~(0x3f << 1);
GPIO_M_SET(AUDIO_MUTE_GPIO, 1); //audio_mute is gpio 37,pin129
GPIO_E_SET(AUDIO_MUTE_GPIO, 1);
GPIO_O_SET(AUDIO_MUTE_GPIO, 1);
#endif /*SPHE8202*/
#endif

#ifdef RESET_TO_DVI311  //tjf 04-05-06
#ifdef SPHE8202

#else /*SPHE8202*/
#define RESET_DVI311_GPIO 40
regs0->sft_cfg0 &= ~(0xfff<<3);   //ra21~ra26 is gpio
GPIO_M_SET(RESET_DVI311_GPIO, 1); //dvi311_reset is gpio 37,pin129
GPIO_E_SET(RESET_DVI311_GPIO, 1);
GPIO_O_SET(RESET_DVI311_GPIO, 1);
#endif/*SPHE8202*/
#endif

#ifdef USE_GPIO52_AS_HEADPHONE_SENSE   //xyy add for Oritron 2004-8-13
    GPIO_M_SET(HEADPHONE_SENSE,1);
    GPIO_E_SET(HEADPHONE_SENSE,0);
#endif

#ifdef MINTON_8202_601           //heqiang added,2004-9-8 20:53
    SFT_CFG_GPIO56();
#endif

#ifdef PMP_DVD           //wthsin added,2004/11/9 02:47
    PMP_gpio_init();
#endif //#if defined(PMP_DVD)

#ifdef HANYANG_DP02CD_WF_8202S_16//added by wangwei,2005-2-3 11:41
//use VFD pin
GPIO_M_SET(21, 1);
GPIO_E_SET(21, 0);

GPIO_M_SET(22, 1);
GPIO_E_SET(22, 0);

GPIO_M_SET(23, 1);
GPIO_E_SET(23, 0);


GPIO_M_SET(15, 1);
GPIO_E_SET(15, 0);
/*
regs0->sft_cfg1 &= ~(0x1 << 3);
regs0->sft_cfg1 &= ~(0x1 << 7);
regs0->sft_cfg8 &= ~(0x1 << 9);*/
GPIO_M_SET(16, 1);
GPIO_E_SET(16, 0);
#endif//HANYANG_DP02CD_WF_8202S_16

#ifdef GBM_AP_DVD_16//added by wangwei,2005-2-25 13:06//for 8200
regs0->sft_cfg0 &= ~(0xfff << 3);//ra21~ra26//pin 130~131, pin 133~136

GPIO_M_SET(43,1);
GPIO_M_SET(42,1);
GPIO_M_SET(41,1);
GPIO_M_SET(40,1);

GPIO_E_SET(43,0);
GPIO_E_SET(42,0);
GPIO_E_SET(41,0);
GPIO_E_SET(40,0);
#endif

#ifdef HANYANG_DP02CD_WG_8202S_16//added by wangwei,2005-3-11 14:21
// Use VFD_CLK/VFD_STB/VFD_DATA/PIN65/PIN66 to scan key.
// VFD_DATA/PIN65/PIN66---PULL LOW,INPUT PIN.
// VFD_CLK/VFD_STB---PULL HIGH,OUPUT PIN.
//regs0->sft_cfg6 &= ~(0x1 << 6);// BA1 as GPIO15
regs0->sft_cfg1 &= ~(0x1 << 3);// GPIO16
GPIO_M_SET(23, 1);// VFD_DATA
GPIO_E_SET(23, 0);
//GPIO_O_SET(23, 1);
GPIO_M_SET(15, 1);// PIN65
GPIO_E_SET(15, 0);
//GPIO_O_SET(15, 0);
GPIO_M_SET(16, 1);// PIN66
GPIO_E_SET(16, 0);
//GPIO_O_SET(16, 1);

GPIO_M_SET(21, 1);// VFD_CLK
GPIO_E_SET(21, 1);
//GPIO_O_SET(21, 1);
GPIO_M_SET(22, 1);// VFD_STB
GPIO_E_SET(22, 1);
//GPIO_O_SET(22, 1);
#endif//HANYANG_DP02CD_WG_8202S_16

#ifdef IC_8202D
#if defined(EMU_BOARD_216_PIN) || defined(MP_BOARD_216_PIN) || defined(MP_BOARD_216_PIN_NON_SHARE)
int i;
regs0->sdc_data_cnt[6][0] |= (1<<3)|(1<<2); // group 41, reg #12, bit #2~3 = 1
for (i=92;i<=100;i++)
{
    GPIO_M_SET(i,1);
    GPIO_E_SET(i,1);
    GPIO_O_SET(i,0);
}    
#endif
#endif

#ifdef SUPPORT_OP_FIVE_DISC//chenzhao20060107
	reset_5disc_gpio();
#endif


#ifdef SUPPORT_8202_DVB//Jack added 06/01/19
    regs0->sdc_data_cnt[6][0] |= (0x0e);//Disable ROM_A20(Pin225),ROM_A21(Pin226),ROM_A22(Pin227) as GPIO92,93,94  
#endif

#ifdef HDMI_16_BIT_256PIN_BOARD
regs0->sft_cfg13 &= 0xfff0;      // 8202A256  194pin  GPIO 51
GPIO_M_SET(51,0);               //  lxg 2006-4-18 10:19  Card_sense 3     
#endif  

}

#if defined(GPIO_KEY_LIGHT)
void init_keylight_io(void)
{
#if defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ)
init_hj_keylight_io();
#elif defined(USE_VFDPORT_TO_KEYLIGHT_GBM)
init_gbm_keylight_io();
#elif defined(USE_VFDPORT_TO_KEYLIGHT_MINTON)       //wanghaoying 2003-8-19 20:00
init_minton_keylight_io();
    #elif defined(USE_VFDPORT_TO_KEYLIGHT_IDALL)
    init_idall_keylight_io();
#elif defined(USE_VFDPORT_TO_KEYLIGHT_THAKRAL)
    init_thakral_keylight_io();
#elif defined(USE_GPIO_TO_KEYLIGHT_WINGSUM)
	init_wingsum_keylight_io();
#elif defined(OP_4110_SCAN_KEY_USE_GPIO)//lijd 2005-6-13 18:45        
    init_op_hk_keylight_io();
#elif defined(OP_5112_SCAN_KEY_USE_GPIO)//lijd 2005-6-13 18:45        
    init_op_hk_keylight_io();	
#elif defined(OP_5116_SCAN_KEY_USE_GPIO)//caoh 2005-7-27 22:03       
    init_op_hk_keylight_io();    	
#elif defined(OP_5121_POWER_KEY)   
    init_op_hk_keylight_io_5121();      	
#endif//#if defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ)
}
#if defined(OP_4110_SCAN_KEY_USE_GPIO)||defined(OP_5112_SCAN_KEY_USE_GPIO)||defined(OP_5116_SCAN_KEY_USE_GPIO)//lijd 2005-6-13 18:42
void init_op_hk_keylight_io(void)
{
   GPIO_M_SET(STB, 1);
   GPIO_M_SET(CLK, 1);
   GPIO_M_SET(DAT, 1);        
   GPIO_E_SET(STB, 0);
   GPIO_E_SET(CLK, 0);
   GPIO_E_SET(DAT, 0);
}  
#endif

#if defined(USE_GPIO_TO_KEYLIGHT_WINGSUM)
void init_wingsum_keylight_io(void)
{
    #if defined(KEY_DIRECT_LOW_WORK)
	regs0->sft_cfg1 &= ~(0x1 <<1);//set gpio16 ---> pin66
	GPIO_M_SET(16,1);
	GPIO_E_SET(16,0);           //set gpio16 as input port

	GPIO_M_SET(14,1);           //set gpio14 ---> pin63
	GPIO_E_SET(14,0);           //set gpio14 as input port

	GPIO_M_SET(13,1);           //set gpio13 ---> pin62
	GPIO_E_SET(13,0);           //set gpio13 as input port
    #endif
    
    #if defined(KEY_SELECT_MAX_SIX)
	regs0->sft_cfg1 &= ~(0x1 <<1);//set gpio16 ---> pin66
	GPIO_M_SET(16,1);
	GPIO_E_SET(16,1);           //set gpio16 as output port

	GPIO_M_SET(14,1);           //set gpio14 ---> pin63
	GPIO_E_SET(14,0);           //set gpio14 as input port

	GPIO_M_SET(13,1);           //set gpio13 ---> pin62
	GPIO_E_SET(13,0);           //set gpio13 as input port

    GPIO_M_SET(12,1);           //set gpio12 ---> pin61
    GPIO_E_SET(12,0);           //set gpio12 as input port
    #endif
}
#endif

#if defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ)
void init_hj_keylight_io(void)
{
    regs0->sft_cfg6 &= ~(0x1 << 6);//gpio15
    regs0->sft_cfg6 &= ~(0x1 << 4);//gpio14
    regs0->gpio_master[54 / 16] |= (0x7 << (54 % 16));  // gpio[54~56]
    //regs0->gpio_master[4 / 16] |= (0x1 << (4 % 16));
    regs0->gpio_master[14 / 16] |= (0x3 << (14 % 16));
    
    
    regs0->gpio_oe[54 / 16] &= ~(0x7 << (54 % 16));
    regs0->gpio_oe[14 / 16] &= ~(0x3 << (14 % 16));
//  regs0->gpio_oe[4 / 16] &= ~(0x1 << (4 % 16));

    //printf("1.regs0->gpio_out[3]=%x\n", regs0->gpio_out[3]);
}
#elif defined(USE_VFDPORT_TO_KEYLIGHT_GBM)
void init_gbm_keylight_io(void)
{
    regs0->gpio_master[54 / 16] |= (0x7 << (54 % 16));  // gpio[54~56]
    //   vfd          gpio     IN/OUT(for 720)
    //   DATA        gpio56       IN/OUT
    //   STB         gpio55       IN/OUT
    //   CLK         gpio54       IN/OUT
    
    
    regs0->gpio_master[54 / 16] |= (0x7 << (54 % 16));//pin151
    regs0->gpio_oe[54 / 16] |= (0x7 << (54 % 16));
    regs0->gpio_out[54 / 16] &= ~(0x7 << (54 % 16));      

}   
#elif defined(USE_VFDPORT_TO_KEYLIGHT_GBM_2)
void init_gbm_keylight_io(void)
{
    //PIN141(GPIO45):GPIO1->LED1
    //PIN138(GPIO44):GPIO2->LED2
    //PIN136(GPIO43):GPIO3->PLAY/PAUSE
    //PIN135(GPIO42):GPIO4->STOP
    //PIN134(GPIO41):GPIO5->F.F.(NEXT)
    //PIN133(GPIO40):GPIO6->F.R.(PREV)
    //PIN131(GPIO39):GPIO7->reversed
    //PIN130(GPIO38):GPIO8->reversed
    regs0->sft_cfg0 &= ~(0xfff << 3);//ra21~ra26//pin 130~131, pin 133~136
    
    
    regs0->gpio_master[38 / 16] |= (0xff << (38 % 16)); // gpio[38~45]
    //   vfd          gpio     IN/OUT(for 720)
    //   DATA        gpio56       IN/OUT
    //   STB         gpio55       IN/OUT
    //   CLK         gpio54       IN/OUT

    regs0->gpio_oe[44 / 16] |= (0x3 << (44 % 16));
    regs0->gpio_oe[38 / 16] |= (0x3f << (38 % 16));

}   
#elif defined(USE_VFDPORT_TO_KEYLIGHT_MINTON)
void init_minton_keylight_io(void)
{
    //regs0->sft_cfg6 &= ~(0x1 << 6);
    regs0->sft_cfg6 &= ~(0x1 << 4);
    regs0->gpio_master[54 / 16] |= (0x7 << (54 % 16));  // gpio[54~56]
    regs0->gpio_master[14 / 16] |= (0x1 << (14 % 16));
    
    
    //regs0->gpio_oe[54 / 16] &= ~(0x7 << (54 % 16));
    regs0->gpio_oe[14 / 16] |= (0x1 << (14 % 16));

}
#elif defined(USE_VFDPORT_TO_KEYLIGHT_IDALL)
void init_idall_keylight_io(void)
{
    regs0->sft_cfg6 &= ~(0x1 << 4); // SA11 as GPIO 14, pin 109
    regs0->gpio_master[14/16] |= (0x1<<(14%16));
    regs0->gpio_oe[14/16] &= ~(0x1<<(14%16));

    regs0->sft_cfg1 &= ~(0x1 << 2); //ROM_CS3 as GPIO 36, pin 71
    regs0->gpio_master[36/16] |= (0x1<<(36%16));
    regs0->gpio_oe[36/16] &= ~(0x1<<(36%16));

    regs0->gpio_master[54/16] |= (0x7<<(54%16));//VFD_CLK as GPIO54, pin154
    regs0->gpio_oe[54/16] &= ~(0x1<<(54%16));
    regs0->gpio_oe[55/16] |= (0x1<<(55%16));
    regs0->gpio_oe[56/16] |= (0x1<<(56%16));
}
#elif defined(USE_VFDPORT_TO_KEYLIGHT_THAKRAL)
void init_thakral_keylight_io(void)
{
    regs0->gpio_master[54 / 16] |= (0x7 << (54 % 16));  // gpio[54~56]
    //   vfd          gpio     IN/OUT(for 720)
    //   DATA        gpio56       IN/OUT
    //   STB         gpio55       IN/OUT
    //   CLK         gpio54       IN/OUT
    regs0->gpio_master[54 / 16] |= (0x7 << (54 % 16));//pin151
    regs0->gpio_oe[54 / 16] &= ~(0x7 << (54 % 16));

    regs0->sft_cfg1 &= ~(0x1 << 2); 
    //ROM_CS3 as GPIO 36, pin 71
    //ROM_CS2 as GPIO 35, pin 70
    regs0->gpio_master[35/16] |= (0x3<<(36%16));
    regs0->gpio_oe[36/16] &= ~(0x1<<(36%16));
    regs0->gpio_oe[35/16] |=  (0x1<<(35%16));
    //regs0->gpio_out[35 /16] |=  (0x1 << (35 % 16));
/*
    regs0->gpio_oe[54 / 16] |=  (0x7 << (54 % 16));
    regs0->gpio_out[54 / 16] |= (0x7<<(54 % 16));
    regs0->gpio_oe[36 / 16] |=  (0x1 << (36 % 16));
    regs0->gpio_out[36 /16] |=  (0x1 << (36 % 16));
    regs0->gpio_oe[35 / 16] |=  (0x1 << (35 % 16));
    regs0->gpio_out[35 /16] |=  (0x1 << (35 % 16));
*/
}
#endif//#if defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ)

#endif//defined(GPIO_KEY_LIGHT)



#ifdef SUPPORT_AUDIO_RESET
void GpioResetAudio(void)
{
    // QISHENG_DVD use pin 151(GPIO 18) to reset audio DAC
#ifdef QISHENG_DVD  // alan, 2003/9/8 10:40上午
    regs0->sft_cfg6 &= 0xFFDF;  // SBA12 disable
    regs0->gpio_master[18 / 16] |= (0x01 << (18 % 16));
    regs0->gpio_oe[18 / 16] |= (0x01 << (18 % 16));
    delay_srv_10ms(30);
    regs0->gpio_out[18 / 16] |= (0x01 << (18 % 16));
#elif 0//defined(HANYANG_DVD)    //2004-4-27 01:02?迻M
     regs0->sft_cfg3 &= ~(0x1 << 4);
    regs0->gpio_master[60 / 16] |= (0x01 << (60 % 16));
    regs0->gpio_oe[60 / 16] |= (0x01 << (60 % 16));
    regs0->gpio_out[60 / 16] &= ~(0x01 << (60 % 16));
    //delay_srv_10ms(100);
    //regs0->gpio_out[60 / 16] |= (0x01 << (60 % 16));
#else
    regs0->sft_cfg6 &= 0xFFBF;  // SBA1 disable
    regs0->gpio_master[15 / 16] |= (0x01 << (15 % 16));
    regs0->gpio_oe[15 / 16] |= (0x01 << (15 % 16));
    delay_srv_10ms(30);
    regs0->gpio_out[15 / 16] |= (0x01 << (15 % 16));
#endif
}
#endif

#ifdef  TCL_VFD_GPIO//2004-3-22 12:52 lijd
    void  tcl_led(void)
{
    regs0->gpio_master[DVD_LED_GPIO / 16] |= (0x1 << (DVD_LED_GPIO % 16));
    regs0->gpio_master[CD_LED_GPIO / 16] |= (0x1 << (CD_LED_GPIO % 16));
    regs0->gpio_master[MP3_LED_GPIO / 16] |= (0x1 << (MP3_LED_GPIO % 16));

    switch(cd_type_loaded)
    {
        case CDDVD: 
        GPIO_O_SET(DVD_LED_GPIO, 0); // DVD
        GPIO_O_SET(CD_LED_GPIO, 1); // CD
        GPIO_O_SET(MP3_LED_GPIO, 1); // MP3
        break;

        case CDDA:
        GPIO_O_SET(DVD_LED_GPIO, 1); // DVD
        GPIO_O_SET(CD_LED_GPIO, 0); // CD
        GPIO_O_SET(MP3_LED_GPIO, 1); // MP3
        break;

        case CDSVCD:
        case CDVCD10:
        case CDVCD20:
        case CDROM:
        GPIO_O_SET(DVD_LED_GPIO, 1); // DVD
        GPIO_O_SET(CD_LED_GPIO, 1); // CD
        GPIO_O_SET(MP3_LED_GPIO, 0); // MP3
        break;

        default:
        GPIO_O_SET(DVD_LED_GPIO, 1); // DVD
        GPIO_O_SET(CD_LED_GPIO, 1); // CD
        GPIO_O_SET(MP3_LED_GPIO, 1); // MP3
        break;
    }
}
#endif


#ifdef SUPPORT_EXTERNAL_MIC
void extern_mic_detect_on(void)
{
    regs0->sft_cfg3 &=0xffdf ;
    regs0->gpio_oe[EXTERN_MIC_DECT / 16] &= ~(0x1 << (EXTERN_MIC_DECT % 16));
    regs0->sft_cfg6 &=0xffdf ;
    regs0->gpio_oe[EXTERN_MIC_MUTE / 16] |= (0x1 << (EXTERN_MIC_MUTE % 16));
    regs0->gpio_out[EXTERN_MIC_MUTE / 16] |= (0x1 << (EXTERN_MIC_MUTE % 16));

}

void extern_mic_unmute(void)
{
    regs0->gpio_out[EXTERN_MIC_MUTE / 16] &= ~(0x1 << (EXTERN_MIC_MUTE % 16));
}   

void extern_mic_mute(void)
{
    regs0->gpio_out[EXTERN_MIC_MUTE / 16] |= (0x1 << (EXTERN_MIC_MUTE % 16));
}   


int extern_mic_is_detected(void)
{
    if((regs0->gpio_in[EXTERN_MIC_DECT / 16]>>(EXTERN_MIC_DECT % 16))&0x1)
    return 1;
    else
    return 0;
    
}   

#endif

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

#ifdef YI_XIAN_TONG//zhaoyanhua add  03-11-3 22:04
#define AUDIOMODE_GPIO   14
void GpioStereoOutput(void)
{
    regs0->sft_cfg6 &= ~(0x1 << 4); // SA11 as GPIO 14, pin 109
    GPIO_M_SET(AUDIOMODE_GPIO ,1); //set master
    GPIO_E_SET(AUDIOMODE_GPIO ,1); //enable output
    GPIO_O_SET(AUDIOMODE_GPIO ,1); //set ouput high
}

void Gpio5ChOutput(void)
{
    regs0->sft_cfg6 &= ~(0x1 << 4); // SA11 as GPIO 14, pin 109
    GPIO_M_SET(AUDIOMODE_GPIO,1);//set master
    GPIO_E_SET(AUDIOMODE_GPIO,1);//enable output 
    GPIO_O_SET(AUDIOMODE_GPIO,0);//set output low
}
#endif


/*
#define I2C_SDA 59      // GPIOE[0]
#define I2C_SCL 60      // GPIOE[1]


#define I2C_SCL_SET(d)  GPIO_O_SET(I2C_SCL,d)
#define I2C_SDA_SET(d)  GPIO_O_SET(I2C_SDA,d)
#define I2C_SDA_GET()   GPIO_I_GET(I2C_SDA)

#define I2C_SCL_IN()    GPIO_E_SET(I2C_SCL,0)
#define I2C_SDA_IN()    GPIO_E_SET(I2C_SDA,0)
#define I2C_SCL_OUT()   GPIO_E_SET(I2C_SCL,1)
#define I2C_SDA_OUT()   GPIO_E_SET(I2C_SDA,1)

static void delay_gpio(int i)
{
    do
    {
        int j =1000;
        do
        {
            asm volatile ("nop");
        } while (--j >= 0);
    } while (--i >= 0);
}

#define delay_i2c(i)    delay_gpio(i)

void    write_i2c(int add, int aa, int data)
{
  int i;

  add = (add << 1) | 0; // write_BIT

  I2C_SCL_SET(1); delay_i2c(1);         // scl -- high
  I2C_SDA_SET(0); delay_i2c(1);         //      (start)
  
  for (i=7; i>=0; i--)
  {
    I2C_SCL_SET(0); delay_i2c(1);       // scl -> low
    I2C_SDA_SET((add>>i) & 0x01); delay_i2c(1);// scl -- low
    I2C_SCL_SET(1); delay_i2c(1);       // scl -> high
  }

  I2C_SCL_SET(0); delay_i2c(1);         // scl -> low
  I2C_SDA_IN();  delay_i2c(1);          // scl -- low
  I2C_SCL_SET(1); delay_i2c(1);         // scl -> high
  if (I2C_SDA_GET()) { 
      #ifdef GPIO_DBG
      epp_write("fail\n");
      #endif
  } //      (ack)

  // address
  for (i=7; i>=0; i--)
  {
    I2C_SCL_SET(0); delay_i2c(1);       // scl -> low
    I2C_SDA_SET((aa>>i) & 0x01); delay_i2c(1);// scl -- low
    I2C_SDA_OUT(); delay_i2c(1);        // scl -- low
    I2C_SCL_SET(1); delay_i2c(1);       // scl -> high
  }

  I2C_SCL_SET(0); delay_i2c(1);         // scl -> low
  I2C_SDA_IN();  delay_i2c(1);          // scl -- low
  I2C_SCL_SET(1); delay_i2c(1);         // scl -> high
  if (I2C_SDA_GET()) { 
      #ifdef GPIO_DBG
      epp_write("fail\n");
      #endif
  } //      (ack)

  // data
  for (i=7; i>=0; i--)
  {
    I2C_SCL_SET(0); delay_i2c(1);       // scl -> low
    I2C_SDA_SET((data>>i) & 0x01); delay_i2c(1);// scl -- low
    I2C_SDA_OUT(); delay_i2c(1);        // scl -- low
    I2C_SCL_SET(1); delay_i2c(1);       // scl -> high
  }

  I2C_SCL_SET(0); delay_i2c(1);         // scl -> low
  I2C_SDA_IN();  delay_i2c(1);          // scl -- low
  I2C_SCL_SET(1); delay_i2c(1);         // scl -> high
  if (I2C_SDA_GET()) { 
      #ifdef GPIO_DBG
      epp_write("fail\n");
      #endif
  } //      (ack)

  I2C_SCL_SET(0); delay_i2c(1);         // scl -> low
  I2C_SDA_SET(0); delay_i2c(1);         // scl -- low
  I2C_SDA_OUT(); delay_i2c(1);          // scl -- low

  I2C_SCL_SET(1); delay_i2c(1);         // scl -> high
  I2C_SDA_SET(1); delay_i2c(1);         //      (stop)
}
*/

#ifdef SCART_TV_5   //wangfeng 2003-12-2 11:43 for himage HJ-023
void SetScartTV5(void)//As Scart
{
    regs0->sft_cfg2 &= ~(0x7 << 2);//GPIO62 63  pin175 176 use as not uart
    regs0->sft_cfg3 &= ~(0x3 << 14);//GPIO62 63  pin175 176 use as gpio
    //regs0->sft_cfg1 |= (0x7 << 0);//pin28 use as SCART_TV gpio2//SCART_SW1
    //1 risc use
    GPIO_M_SET(62,1);
    GPIO_M_SET(63,1);
    //GPIO_M_SET(2,1);
    // 1 output
    GPIO_E_SET(62,1);
    GPIO_E_SET(63,1);
    //GPIO_E_SET(2,1);

//  GPIO_O_SET(62,0);
//  GPIO_O_SET(63,0);
//  GPIO_O_SET(2,0);
}

void ReSetScartTV5(void)//As V/H SYNC
{
    //regs0->sft_cfg2 &= ~(0x7 << 2);//GPIO62 63  pin175 176 use as not uart
    regs0->sft_cfg3 &= ~(0x1 << 15);//GPIO62 63  pin175 176 use as h/v sync
    regs0->sft_cfg3 |= (0x1 << 14);//GPIO62 63  pin175 176 use as h/v sync
}
#endif

#ifdef SUPPORT_I2C_LCD_Panel

void init_I2C_panel_4094(void)
{
    int i;
        const Data4094[8]={0,0,0,0,0,0,0,0};
                
        regs0->sft_cfg0 &= ~(0xfffc << 1);  //Disable ra20~ra26 pin 129~131, pin 133~136
    GPIO_M_SET(42,1);
    GPIO_E_SET(42,1);
    GPIO_O_SET(42,1);    //Set TFT_SB to H ,Enable TFT 9V. 
    GPIO_M_SET(41,1);
    GPIO_E_SET(41,1);
    GPIO_O_SET(41,0);    //Set STROBE to L
        GPIO_M_SET(0,1);     //Set I2C_CLK to RISC
        GPIO_E_SET(0,1);
        GPIO_O_SET(0,1);     //Set I2C_CLK to L 
        
        
        GPIO_M_SET(1,1);     //Set I2C_DATA to RISC
        GPIO_E_SET(1,1);
        GPIO_O_SET(1,1);     //Set I2C_DATA to H
        delay_1us(100);
        GPIO_O_SET(41,1);    //Set STROBE to H for 4094 transfer data
        delay_1us(10);
        GPIO_O_SET(0,0);     //Set I2C_CLK to L 
        delay_1us(7);
        
        for(i=0;i<8;i++)
        {
            GPIO_O_SET(1,Data4094[i]);
            delay_1us(7);
        GPIO_O_SET(0,1);
        delay_1us(7);
        GPIO_O_SET(0,0);
        delay_1us(7);
    }
    GPIO_O_SET(41,0);
    delay_1us(10);
}   

void init_I2C_command(void)
{
        GPIO_M_SET(0,0);    //Set I2C_CLK to IOP
    GPIO_M_SET(1,0);    //Set I2C_DATA to IOP
     
    WriteI2c(0x88,0x01,0xc0,1);
    WriteI2c(0x88,0x02,0x80,1);
    WriteI2c(0x88,0x03,0xb0,1);
    WriteI2c(0x88,0x04,0xc8,1);
    WriteI2c(0x88,0x05,0xd5,1);
    WriteI2c(0x88,0x06,0x4c,1);
    WriteI2c(0x88,0x07,0xc0,1);
    WriteI2c(0x88,0x08,0x98,1);
    WriteI2c(0x88,0x09,0x99,1);
    WriteI2c(0x88,0x0a,0xf0,1);
    WriteI2c(0x88,0x0b,0x80,1);
    WriteI2c(0x88,0x0c,0x50,1);
    WriteI2c(0x88,0x0d,0x9b,1);
    WriteI2c(0x88,0x0e,0x48,1);
    WriteI2c(0x88,0x0f,0x3c,1);
    WriteI2c(0x88,0x10,0x80,1);
    WriteI2c(0x88,0x11,0x05,1);
    WriteI2c(0x88,0x12,0x92,1);
    WriteI2c(0x88,0x13,0x8c,1);
    WriteI2c(0x88,0x14,0x47,1);
    WriteI2c(0x88,0x15,0x40,1);
    WriteI2c(0x88,0x16,0x5d,1);
    WriteI2c(0x88,0x17,0x8f,1);
    WriteI2c(0x88,0x18,0x2d,1);
}


void init_I2C_panel(void)
{
          //For EDOM Panasonic LCD Panel test
    init_I2C_panel_4094();
        
        init_I2C_command();
        
        GPIO_M_SET(0,0);    //Set I2C_CLK to IOP
    GPIO_M_SET(1,0);    //Set I2C_DATA to IOP
    WriteI2c(0x88,0x03,0xb0,1);
    WriteI2c(0x88,0x0d,0x9b,1);
    WriteI2c(0x88,0x06,0x4c,1);
    
    delay_1us(100); 
        init_I2C_panel_4094();
        init_I2C_panel_4094();
        init_I2C_panel_4094();
        
        GPIO_M_SET(0,0);    //Set I2C_CLK to IOP
    GPIO_M_SET(1,0);    //Set I2C_DATA to IOP
    WriteI2c(0x88,0x16,0x5d,1);
}   
#endif      

#ifdef EASTWIN
void init_an2526h(void)
{
    if(tv_format == MODE_NTSC)  //NTSC system
    {
        NTSC_SET();
        init_an2526h_ntsc();
    }
    else                        // PAL system
    {
        PAL_SET();
        init_an2526h_pal();
    }
}

void init_an2526h_ntsc(void)
{
    
    color_drv_data[1] = color_drv_data[1] | 0x80; /* NTSC system */
    color_drv_data[2] = color_drv_data[2] | 0x80; /* NTSC system */
    //color_drv_data[1] = color_drv_data[1] | 0x91; /* NTSC system *///MAPLE
    
    /* retrieve the color parameter setting from EEPROM */ 
    ReadFromI2c(I2C_ID_MEMORY, COLOR_ADDR,&color_value,1);
    an2526h_value_change(COLOR_ADJ, color_value);
    
    /* retrieve the brightness parameter setting from EEPROM */ 
    ReadFromI2c(I2C_ID_MEMORY, BRIGHTNESS_ADDR,&brightness_value,1);
    an2526h_value_change(BRIGHTNESS_ADJ, brightness_value);

    an2526h_send_data();
}

void init_an2526h_pal(void)
{
    color_drv_data[1] = color_drv_data[1] & 0x7F; /* PAL system */
    color_drv_data[2] = color_drv_data[2] | 0x80; /* PAL system */
    //color_drv_data[1] = color_drv_data[1] | 0x11; /* NTSC system *///MAPLE

    /* retrieve the color parameter setting from EEPROM */ 
    ReadFromI2c(I2C_ID_MEMORY, COLOR_ADDR,&color_value,1);
    an2526h_value_change(COLOR_ADJ, color_value);
    
    /* retrieve the brightness parameter setting from EEPROM */ 
    ReadFromI2c(I2C_ID_MEMORY, BRIGHTNESS_ADDR,&brightness_value,1);
    an2526h_value_change(BRIGHTNESS_ADJ, brightness_value);

    an2526h_send_data();
}

void an2526h_send_data(void)
{
    unsigned char index;    
    GPIO_M_SET(0,0);    //Set I2C_CLK to IOP
    GPIO_M_SET(1,0);    //Set I2C_DATA to IOP
    for(index=0;index<16;index++)
    {
        WriteI2c(AN2526H_ADDR,data_refresh_mode|index,color_drv_data[index],1); /* Data refresh mode */
    }
}

void an2526h_value_change(unsigned char para,unsigned char value)
{   
#ifdef AN2546H
    if(para == COLOR_ADJ)                           /* color adjustment */
    {
        if(value == 8)                              
            color_drv_data[2]=0x80;
        else if(value < 8)
            color_drv_data[2]=(0x80)-(8-value)*7;
        else if(value > 8)
            color_drv_data[2]=(0x80)+(value-8)*7;
    }
    else if(para == BRIGHTNESS_ADJ)                 /* brightness adjustment */
    {
        if(value == 8)
            color_drv_data[5]=0x38;
        else if(value < 8)
            color_drv_data[5]=(0x38)-(8-value)*7; 
        else if(value > 8)
            color_drv_data[5]=(0x38)+(value-8)*7;   
    }
#else   //AN2526H
    if(para == COLOR_ADJ)                           /* color adjustment */
    {
        if(value == 8)                              
            color_drv_data[5]=0xca;
        else if(value < 8)
            color_drv_data[5]=(0xca)-(8-value)*4;
        else if(value > 8)
            color_drv_data[5]=(0xca)+(value-8)*5;
    }
    else if(para == BRIGHTNESS_ADJ)                 /* brightness adjustment */
    {
        if(value == 8)
            color_drv_data[8]=0x5f;
        else if(value < 8)
            color_drv_data[8]=(0x5f)-(8-value)*8;
        else if(value > 8)
            color_drv_data[8]=(0x5f)+(value-8)*8;  
    }
#endif
}   

void load_customer_default(void)
{
    unsigned char default_view_mode,default_brightness_value,default_color_value;
    default_brightness_value = 8;   // default brightness value
    default_color_value = 8;        // default color value
    default_view_mode = FULL_MODE;  // default view mode value
    WriteToI2c(I2C_ID_MEMORY,BRIGHTNESS_ADDR,&default_brightness_value,1);
    WriteToI2c(I2C_ID_MEMORY,COLOR_ADDR,&default_color_value,1);
    WriteToI2c(I2C_ID_MEMORY,VIEWMODE_ADDR,&default_view_mode,1);
}

void check_customer_default(void)
{
    unsigned char eeprom_been_used;
    ReadFromI2c(I2C_ID_MEMORY, BEEN_USED_ADDR,&eeprom_been_used,1);
    if( eeprom_been_used != E2PROM_BEEN_USED)
    {
        eeprom_been_used = E2PROM_BEEN_USED;
        WriteToI2c(I2C_ID_MEMORY,BEEN_USED_ADDR,&eeprom_been_used,1);
        load_customer_default();                
    }
}

void init_lcd_display_mode(void)
{
    unsigned char view_mode;     
    ReadFromI2c(I2C_ID_MEMORY,VIEWMODE_ADDR,&view_mode,1);
        
    if( view_mode == NORMAL_MODE)   
    {
        //PrintOsdMsg(STR_OS_VIEW_MODE_NORMAL,REGION2,1,0);
        LCD_VIEW_MODE_NORMAL();
    }
    else
    {
        //PrintOsdMsg(STR_OS_VIEW_MODE_FULL,REGION2,1,0);
        LCD_VIEW_MODE_FULL();
    }
}
#endif

#ifdef SUPPORT_TOPPOLY_UPS051_Digital_panel
//define toppoly pannel GPIO pin
#define AUO_CSB     66 //pin57 GPIO 0
#define AUO_SCL     67 //pin58 GPIO 1
#define AUO_SDA     68 //pin59 GPIO 1
void init_toppoly_digital_interface(void)
{
   regs0->sft_cfg4&=~(1<<0);
   regs0->sft_cfg4&=~(1<<1); 
   regs0->sft_cfg4&=~(1<<2);
   GPIO_M_SET(AUO_SCL,1);     //Set AUO_SCL to RISC
   GPIO_M_SET(AUO_SDA,1);     //Set AUO_SDA to RISC
   GPIO_M_SET(AUO_CSB,1);     //Set AUO_CSB to RISC
   
   GPIO_E_SET(AUO_SCL,1);
   GPIO_E_SET(AUO_SDA,1);
   GPIO_E_SET(AUO_CSB,1); 
   
   GPIO_O_SET(AUO_SCL,0);
   GPIO_O_SET(AUO_SDA,0);
   GPIO_O_SET(AUO_CSB,1); 
}
BYTE read_topp0ly_panel(BYTE ADD)
{
    int  i;
    BYTE buf=0;
    ADD=ADD<<2;  
    ADD=ADD|0X2;
    GPIO_O_SET(AUO_CSB,0);     //Set AUO_CSB to L 
    delay_1us(1);
    for(i=7;i>=0;i--)
    {
        //GPIO_O_SET(AUO_SCL,0);
        if((ADD>>i)&0x01)
        {
            GPIO_O_SET(AUO_SDA,1);
  
        }
        else
        {
            GPIO_O_SET(AUO_SDA,0);
        }
   //   delay_1us(1);
        GPIO_O_SET(AUO_SCL,1);
        delay_1us(1);  
        GPIO_O_SET(AUO_SCL,0); 
        delay_1us(1);  
   }  
   GPIO_E_SET(AUO_SDA,0);
   for(i=7;i>=0;i--)
    {
        //GPIO_I_GET(AUO_SDA);
        buf=buf|(GPIO_I_GET(AUO_SDA)<<i);
   //   delay_1us(1);
        GPIO_O_SET(AUO_SCL,1);
        delay_1us(1);  
        GPIO_O_SET(AUO_SCL,0); 
        delay_1us(1);  
   }  
  GPIO_O_SET(AUO_CSB,1);     //Set AUO_CSB to H    
  GPIO_E_SET(AUO_SDA,1);   
    return(buf);
}
void send_toppoly_panel_cmd(UINT16 set_cmd)
{
    int i;
    GPIO_O_SET(AUO_CSB,0);     //Set AUO_CSB to L 
    delay_1us(1);
    for(i=15;i>=0;i--)
    {
        //GPIO_O_SET(AUO_SCL,0);
        if((set_cmd>>i)&0x01)
        {
            GPIO_O_SET(AUO_SDA,1);
  
        }
        else
        {
            GPIO_O_SET(AUO_SDA,0);
        }
   //   delay_1us(1);
        GPIO_O_SET(AUO_SCL,1);
        delay_1us(1);  
        GPIO_O_SET(AUO_SCL,0); 
        delay_1us(1);  
   }  
   GPIO_O_SET(AUO_SDA,0);  
   GPIO_O_SET(AUO_CSB,1);     //Set AUO_CSB to H    
}   
#include "vpp.h"
void init_toppoly_digital_panel(void)
{
    init_toppoly_digital_interface(); 
    //send_toppoly_panel_cmd((0x02<<10)+0x9); //ntsc
    //send_toppoly_panel_cmd((0x03<<10)+0x3c); 
    //send_toppoly_panel_cmd((0x02<<10)+0x0d); //pal 
    if(getVPP_TVsystem()==1)
        {
            send_toppoly_panel_cmd((0x02<<10)+0xd); 
        }
     else 
        { 
            send_toppoly_panel_cmd((0x02<<10)+0x9);          
        }
    send_toppoly_panel_cmd((0x03<<10)+0x2); 
    send_toppoly_panel_cmd((0x04<<10)+0x0f); 
    #ifdef TOPPOLY_36_PANEL
    send_toppoly_panel_cmd((0x05<<10)+0x17); 
    #else defined(TOPPOLY_25_PANEL)
    send_toppoly_panel_cmd((0x05<<10)+0x13); 
    #endif  
    send_toppoly_panel_cmd((0x06<<10)+0x18); 
    send_toppoly_panel_cmd((0x07<<10)+0xd); 
    send_toppoly_panel_cmd((0x08<<10)+0x00); 
    send_toppoly_panel_cmd((0x09<<10)+0x20); 
    send_toppoly_panel_cmd((0x0a<<10)+0x20); 
    send_toppoly_panel_cmd((0x0B<<10)+0x20); 
    send_toppoly_panel_cmd((0x0C<<10)+0x0);
    send_toppoly_panel_cmd((0x10<<10)+0x3A);
    send_toppoly_panel_cmd((0x11<<10)+0x3A);
    send_toppoly_panel_cmd((0x12<<10)+0x1D);
    send_toppoly_panel_cmd((0x13<<10)+0x17);
    send_toppoly_panel_cmd((0x14<<10)+0x98);
    send_toppoly_panel_cmd((0x15<<10)+0x9A);
    send_toppoly_panel_cmd((0x16<<10)+0xA9);
    send_toppoly_panel_cmd((0x17<<10)+0x99);
    send_toppoly_panel_cmd((0x18<<10)+0x08);
    
}   



#endif//#ifdef SUPPORT_TOPPOLY_UPS051_Digital_panel

#ifdef SUPPORT_Auo_2inch_Digital_panel //add for auo 2" ccir656 panel

//define Auo panel I2c GPIO pin
#define AUO_CSB     0 //pin57 GPIO 0
#define AUO_SCL     1 //pin58 GPIO 1
#define AUO_SDA     2 //pin59 GPIO 1

/********************************************************************/
/* Function:  init_auo_digital_interface()                          */  
/*                                                                  */
/*          Initual the I2C GPIO                                    */
/********************************************************************/
void init_auo_digital_interface(void)
{

   regs0->sysclk_div_sel|=(1<<5);   //set data output in ccir656 clock low 
   regs0->sft_cfg4&=~(1<<0);
   regs0->sft_cfg4&=~(1<<1); 
   regs0->sft_cfg4&=~(1<<2);
   GPIO_M_SET(AUO_SCL,1);     //Set AUO_SCL to RISC
   GPIO_M_SET(AUO_SDA,1);     //Set AUO_SDA to RISC
   GPIO_M_SET(AUO_CSB,1);     //Set AUO_CSB to RISC
   
   GPIO_E_SET(AUO_SCL,1);
   GPIO_E_SET(AUO_SDA,1);
   GPIO_E_SET(AUO_CSB,1);   
    
}   


void send_auo_panel_cmd(UINT16 set_comd)
{
   int i;   
   
      
   GPIO_O_SET(AUO_CSB,0);     //Set AUO_CSB to L 
   delay_1us(1);
   for(i=15;i>=0;i--)
   {
    GPIO_O_SET(AUO_SCL,0);
    if((set_comd>>i)&0x01)
    {
    GPIO_O_SET(AUO_SDA,1);
  
    }
    else
    {
    GPIO_O_SET(AUO_SDA,0);
    
    }
   //   delay_1us(1);
    GPIO_O_SET(AUO_SCL,1);
      delay_1us(1);
        
   }    
   GPIO_O_SET(AUO_CSB,1);     //Set AUO_CSB to H 
  
}   

void init_auo_digital_panel(void)
{
    init_auo_digital_interface(); 
    send_auo_panel_cmd(0x000f); 
    send_auo_panel_cmd(0x4003); 
    send_auo_panel_cmd(0x6007); 
    send_auo_panel_cmd(0xc006); 
    
}   


#endif


#ifdef SUPPORT_Auo_UPS053_Digital_panel //add for auo 3.5" ccir656 panel
//define Auo panel I2c GPIO pin
#define AUO_CSB     0 //pin57 GPIO 0
#define AUO_SCL     1 //pin58 GPIO 1
#define AUO_SDA     2 //pin59 GPIO 2




/********************************************************************/
/* Function:  init_auo_digital_interface()                          */  
/*                                                                  */
/*          Initual the I2C GPIO                                    */
/********************************************************************/
void init_auo_digital_interface(void)
{
   
   regs0->sysclk_div_sel|=(1<<5);   //set data output in ccir656 clock low 
   
#ifndef PMP_KEYBOARD//olive add 2005-1-24   
   regs0->sft_cfg4&=~(1<<0);
   regs0->sft_cfg4&=~(1<<1); 
   regs0->sft_cfg4&=~(1<<2);
   GPIO_M_SET(AUO_SCL,1);     //Set AUO_SCL to RISC
   GPIO_M_SET(AUO_SDA,1);     //Set AUO_SDA to RISC
   GPIO_M_SET(AUO_CSB,1);     //Set AUO_CSB to RISC
   
   GPIO_E_SET(AUO_SCL,1);
   GPIO_E_SET(AUO_SDA,1);
   GPIO_E_SET(AUO_CSB,1);   
    GPIO_O_SET(AUO_CSB,1);
     GPIO_O_SET(AUO_SDA,1);
     GPIO_O_SET(AUO_SCL,1);
#endif
   
   regs0->sft_cfg1 = regs0->sft_cfg1 & (~(1<<1));
     GPIO_M_SET(17,1);
     GPIO_E_SET(17,1);
     GPIO_O_SET(17,1); 
     
    
     
    
    
}   

void write_auo_i2c_page(int iDevAdd, int iSubAdd, BYTE *iSetData ,int len)
{
     int i,j;
     
    
     GPIO_O_SET(AUO_CSB,1);
     GPIO_O_SET(AUO_SDA,1);
     GPIO_O_SET(AUO_SCL,1);
    
     delay_1ms(2);
     GPIO_O_SET(AUO_SDA,0);
     delay_1us(7);
     GPIO_O_SET(AUO_SCL,0);
     delay_1us(7);
     
    
     
     for(i=7;i>=0;i--)
     {
         
     if((iDevAdd>>i)&0x01)
     GPIO_O_SET(AUO_SDA,1);
     else
     GPIO_O_SET(AUO_SDA,0);
     
     delay_1us(3);
     
     GPIO_O_SET(AUO_SCL,1);
     delay_1us(1);
     
     GPIO_O_SET(AUO_SCL,0);
     delay_1us(1);
     
     
     if((iDevAdd>>i)&0x01)
     GPIO_O_SET(AUO_SDA,0);
     
     if(i>0)
     delay_1us(11);
     else
     delay_1us(9);
    
     
    }
    
     
     //wait for ack
     GPIO_O_SET(AUO_SCL,1);
     delay_1us(6);
     
     GPIO_O_SET(AUO_SCL,0);
     GPIO_O_SET(AUO_SDA,1);
     delay_1us(1);
     
     GPIO_O_SET(AUO_SDA,0);
     delay_1us(12);
     
     
     
     //set sub address
     for(i=7;i>=0;i--)
     {
         
     if((iSubAdd>>i)&0x01)
     GPIO_O_SET(AUO_SDA,1);
     else
     GPIO_O_SET(AUO_SDA,0);
     
     delay_1us(3);
     
     GPIO_O_SET(AUO_SCL,1);
     delay_1us(1);
     
     GPIO_O_SET(AUO_SCL,0);
     delay_1us(1);
     
     if((iSubAdd>>i)&0x01)
     GPIO_O_SET(AUO_SDA,0);
     
     if(i>0)
     delay_1us(11);
     else
     delay_1us(9);
     
    
    }
     
     //wait for ack
     GPIO_O_SET(AUO_SCL,1);
     delay_1us(6);
     
     GPIO_O_SET(AUO_SCL,0);
     GPIO_O_SET(AUO_SDA,1);
     delay_1us(1);
     
     GPIO_O_SET(AUO_SDA,0);
     delay_1us(31);
         
     for(j=0;j<len;j++)
     {
     for(i=7;i>=0;i--)
     {
     
     if((*(iSetData+j)>>i)&0x01)
     GPIO_O_SET(AUO_SDA,1);
     else
     GPIO_O_SET(AUO_SDA,0);
     
     delay_1us(3);
    
     GPIO_O_SET(AUO_SCL,1);
     delay_1us(1);
    
     GPIO_O_SET(AUO_SCL,0);
     delay_1us(1);
     
     if((*(iSetData+j)>>i)&0x01)
     GPIO_O_SET(AUO_SDA,0);
     
     if(i>0)
     delay_1us(11);
     else
     delay_1us(9);
    }
     //wait for ack
     GPIO_O_SET(AUO_SCL,1);
     delay_1us(6);
     GPIO_O_SET(AUO_SCL,0);
     GPIO_O_SET(AUO_SDA,1);
     delay_1us(1);
     GPIO_O_SET(AUO_SDA,0);
     if(j<=24)
     delay_1us(34);
     else
     delay_1us(15);
    
     }
     
     GPIO_O_SET(AUO_SCL,1);
     delay_1us(66);
     GPIO_O_SET(AUO_SDA,1);
     
        
}   


void init_auo_ups053_digital_panel(void)
{
    int i;
     watchdog_onoff(0);
    init_auo_digital_interface(); 
    for(i=0;i<2;i++)
    {
        #ifdef PMP_KEYBOARD//olive mod 2005-1-24
        WriteToI2c(0x58,0x00,&auo_053_ntsc[0],25);
        #else
        write_auo_i2c_page(0x58,0x00,&auo_053_ntsc[0],25);
        #endif
    }
    watchdog_onoff(1);   
}   




#endif

#ifdef SUPPORT_Auo_UPS018_Digital_panel  
void init_auo_ups018_digital_panel(void)
{
     int iRts,kk;
    
    GPIO_O_SET(CUT_PANEL_POWER ,1);
     delay_1ms(100);
    kk=WriteToI2c(0x58,0x00,auo_018_ntsc,5);     //////////yangli add for write ups018 I2C,05/02/15
     if(kk == 1)   /////////////////////for debug 
        printf("write UPS018 ok!\n");
    else
        printf("write UPS018 error!\n");
    iRts=WriteToI2c(0x88,0,an2526_data_ntsc,16); /* Data refresh mode */
    if(iRts == 1)
        printf("write an2526 ok!\n");
    else
        printf("write an2526 error!\n");
}   
#endif

#ifdef SUPPORT_Auo_A070FW04_Digital_panel //add for auo 7" ccir656 panel

//define Auo panel I2c GPIO pin
#define AUO_CSB     51 //pin57 GPIO 0
#define AUO_SCL     54 //pin58 GPIO 1
#define AUO_SDA     55 //pin59 GPIO 1

/********************************************************************/
/* Function:  init_auo_digital_interface()                          */  
/*                                                                  */
/*          Initual the I2C GPIO                                    */
/********************************************************************/
void init_auo_A070FW04_digital_interface(void)
{

    regs0->sysclk_div_sel|=(1<<5);    //set data output in ccir656 clock low 
    regs0->sft_cfg13 &= ~(0x0f<<0);  //pin194  gpio51
    regs0->sft_cfg3 &= ~(0x01<<2);    //pin198  gpio54
    regs0->sft_cfg8 &= ~(0x01<<3);   //pin199 gpio55
    
    GPIO_M_SET(AUO_SCL,1);     //Set AUO_SCL to RISC
    GPIO_M_SET(AUO_SDA,1);     //Set AUO_SDA to RISC
    GPIO_M_SET(AUO_CSB,1);     //Set AUO_CSB to RISC
   
    GPIO_E_SET(AUO_SCL,1);
    GPIO_E_SET(AUO_SDA,1);
    GPIO_E_SET(AUO_CSB,1);   
   
    GPIO_O_SET(AUO_CSB,1);
    GPIO_O_SET(AUO_SDA,1);
    GPIO_O_SET(AUO_SCL,1);
  
    
}   


void send_auo_A070FW04_panel_cmd(UINT16 set_comd)
{
    int i;
    GPIO_O_SET(AUO_CSB,0);
    GPIO_O_SET(AUO_CSB,0);
    for(i=0;i<16;i++)
    {
        GPIO_O_SET(AUO_SCL,0);
    	if(set_comd & 0x8000){
            GPIO_O_SET(AUO_SDA,1);
            GPIO_O_SET(AUO_SDA,1);
            }
    	else{
            GPIO_O_SET(AUO_SDA,0);
            GPIO_O_SET(AUO_SDA,0);
            }
    GPIO_O_SET(AUO_SCL,1);
    GPIO_O_SET(AUO_SCL,1);
    GPIO_O_SET(AUO_SCL,1);
    set_comd <<= 1;
    }
    GPIO_O_SET(AUO_CSB,1);
    GPIO_O_SET(AUO_CSB,1);
    return;  
}   

void init_auo_A070FW04_digital_panel(void)
{
    init_auo_A070FW04_digital_interface(); 
    delay_1us(10);
    send_auo_A070FW04_panel_cmd(0x002F); //R0 reset	'0000 0000 0010 1111'
    send_auo_A070FW04_panel_cmd(0x0037); //R0 stanby'0000 0000 0011 0111'
    send_auo_A070FW04_panel_cmd(0x13AF); //R1 			'0001 0011 1010 1111'
    send_auo_A070FW04_panel_cmd(0x3010);//R3 			'0011 0000 0001 0000'
    send_auo_A070FW04_panel_cmd(0x8638); //r8 for vcom
    send_auo_A070FW04_panel_cmd(0xC000); //R12			'1100 0001 0000 0000'
    send_auo_A070FW04_panel_cmd(0x003F); //R0 release stanby
    return;
}   
#endif//#ifdef SUPPORT_Auo_A070FW04_Digital_panel //add for auo 7" ccir656 panel



#ifdef SUPPORT_VX1818_TOSHIBA_PANEL  
BYTE VX1818_ntsc_data[8]={0x5a,0x7d,0x94,0x11,0xd9,0xf8,0xd6,0x01};
BYTE VX1818_ntsc_Addr[8]={0x01,0xc0,0x3c,0x22,0x05,0xc1,0x3b,0x02};
void init_xv1818_toshiba_panel(void)
{
    int i=0;
    for(i=0,i<8,i++)
     WriteToI2c(0xd8,VX1818_ntsc_Addr[i],&VX181_ntsc_data[i],1);
    
}   
#endif

#ifdef  DVB_DVD_8202 //Jack added 05/10/21
#include "gpio_demux.c"
#endif

