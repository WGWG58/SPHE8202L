/**************************************************************************
 *                                                                        *
 *         Copyright (c) 2002 by Sunplus Technology Co., Ltd.             *
 *                                                                        *
 *  This software is copyrighted by and is the property of Sunplus        *
 *  Technology Co., Ltd. All rights are reserved by Sunplus Technology    *
 *  Co., Ltd. This software may only be used in accordance with the       *
 *  corresponding license agreement. Any unauthorized use, duplication,   *
 *  distribution, or disclosure of this software is expressly forbidden.  *
 *                                                                        *
 *  This Copyright notice MUST not be removed or modified without prior   *
 *  written consent of Sunplus Technology Co., Ltd.                       *
 *                                                                        *
 *  Sunplus Technology Co., Ltd. reserves the right to modify this        *
 *  software without notice.                                              *
 *                                                                        *
 *  Sunplus Technology Co., Ltd.                                          *
 *  19, Innovation First Road, Science-Based Industrial Park,             *
 *  Hsin-Chu, Taiwan, R.O.C.                                              *
 **************************************************************************/
/*--------------------------------------------------------------------------
|  File Name   : iop.c
|
|  Description : This file main contains three parts.
|                1. Include 8200 and 8202 iop normal play inc.
|                2. Include iop normal and standby reset function.
|                3. Include I2C(24C02) read and write function.
|
|  Version    :  0.1  
| 
| 
|  Rev  Date            Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|       2004/12/20        Lijd           Updating
|       2006/04/06        Terry          Creat
|--------------------------------------------------------------------------------*/
#define IOP_RESET() (regs0->iop_control = IOPHW_RESET)
#define IOP_GO()    (regs0->iop_control = 0)


#ifdef SOFT_UART_OUT 
    int PutSoftUartChar(BYTE *,int);
    int GetSoftUartChar(BYTE *,int);    
    BYTE bResetIop=0;       
#endif  

BYTE bSleepFlag = 0; // keep standby mode flag

extern const BYTE ir_mapcode[256];
extern const BYTE vfd_keycode[40];

extern void LoadModual(UINT16);

/**************************************************************************
 *  Function Name: void reset_iop(void)                                   *
 *  Purposes:                                                             *
 *              Reset iop for normal / standby mode.                      *
 *  Descriptions:                                                         *
 *              This function contains three parts                        *   
 *              1.   reset iop                                            *
 *              2.   Set I2C,VFD,IR,GAME GPIOS for iop use.               *
 *                   if system is coming into standby mode. then pass     *
 *                   the IR or VFD power key value and flag to reset code.*
 *              3.   LoadModual(MODUAL_IOP_RESET) /LoadModual(MODUAL_IOP) *
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              (None)                                                    *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/

void reset_iop(void)
{
    int     i;
    //int       len;
    //UINT32    *p, *q;

#ifdef 	NOT_SHOW_MIC_SETUP_detect_by_sensor//2005-4-27 10:01 zhoulin
    GPIO_M_SET(11, 1);
    GPIO_E_SET(11, 0);    
#endif


#ifdef PORTABLE_DVD
#if defined(QSI_PORTABLE_DVD)||defined(TEAC_PORTABLE_DVD)
	#ifdef MP_BOARD_216_PIN_NON_SHARE//TEAC
    //use ioprom_spi_teac_8202_216.inc
    GPIO_M_SET(9, 0);//TEAC 8202 216 pin
    GPIO_M_SET(10, 0);//TEAC 8202 216 pin
    GPIO_M_SET(15, 0);//TEAC 8202 216 pin
	#else
    //use ioprom_spi_teac_8202.inc and ioprom_spi_qsi_8202.inc
    GPIO_M_SET(21, 0);//TEAC/QSI 8202 256 pin
    GPIO_M_SET(22, 0);//TEAC/QSI 8202 256 pin
    GPIO_M_SET(23, 0);//TEAC/QSI 8202 256 pin
	#endif
#endif	
#endif//#ifdef PORTABLE_DVD
    
    // reset iop
    IOP_RESET();
    #ifdef PMP_MCU810
     // gpio 21, 22, 23 for VFD
        GPIO_M_SET(21, 0);
        GPIO_M_SET(22, 0);
        GPIO_M_SET(23, 0);
    #endif
    // setup IOP interface / GPIO
#ifdef OLD_I2C_DEFINE
    // select GPIO 35,36 for I2C
    regs0->gpio_master[35 / 16] &= ~(0x3 << (35 % 16));
#else
    #ifdef SPHE8202
        #if defined(MP_BOARD_256_PIN_NON_SHARE)||defined(MP_BOARD_256_PIN_SHARE)//NONO 4-3-23 22:19
            #if defined(SDRAM_BUS_32BITS)||defined(SDRAM_128Mx1)||defined(SCALER_6500)||(defined(PORTABLE_DVD)&&!defined(DVB_DVD_8202)) //mimitsai add 2004-12-07
                                // gpio 48(pin173), 49(pin174) for I2C
                               #if defined(ORITRON_HK_HDMI_CARD)||defined(HDMI_16_BIT_256PIN_BOARD)   // caoh 2006-01-12   // lxg add HDMI_16_BIT_256PIN_BOARD 2006-4-18
                                 regs0->sft_cfg0 &= ~(0x1 << 5); //GPIO38
                                 regs0->sft_cfg0 &= ~(0x1 << 4); //GPIO39 
                                 GPIO_M_SET(38, 0);
                                 GPIO_M_SET(39, 0);
                               #else
                                regs0->sft_cfg0 &= ~(0x1 << 7);//GPIO48
                                regs0->sft_cfg1 &= ~(0x1 << 5);//GPIO49 
                                GPIO_M_SET(48, 0);
                                GPIO_M_SET(49, 0);
                              #endif
            #elif defined(PMP_I2C_NEW)    //////////////YANGLI ADD FOR PMP 2002\12\29
                 regs0->sft_cfg4 &= ~(0x1 << 5);//I2C DATA PIN62   
                 GPIO_M_SET(5, 0);//I2C DATA PIN62
                 GPIO_M_SET(6, 0);//I2C CLK  PIN63                   
            #elif defined(Tuner_8202_I2C)||defined(Tuner_6600_I2C)&&!defined(CARD_6IN1_DVB_I2C)     //wthsin, 2005/3/7 05:58pm
                 // gpio 48(pin173), 49(pin174) for I2C
                 regs0->sft_cfg0 &= ~(0x1 << 7);//GPIO48
                 regs0->sft_cfg1 &= ~(0x1 << 5);//GPIO49 
                 GPIO_M_SET(48, 0);
                 GPIO_M_SET(49, 0);  
            #elif defined(CARD_6IN1_DVB_I2C)
                 GPIO_M_SET(99, 0);  /////SCL
                 GPIO_M_SET(100, 0); ///////SDA                                
            #else
                //gpio 95(pin228), 96(pin229) for I2C
                GPIO_M_SET(95, 0);
                GPIO_M_SET(96, 0);          
            #endif
            
        #elif defined(MP_BOARD_216_PIN_NON_SHARE)   //kenny 2004/7/14
                // gpio 17(pin67), 18(pin68) for I2C
                regs0->sft_cfg1 &= ~(0x1 << 2);//GPIO17
                regs0->sft_cfg1 &= ~(0x1 << 1);//GPIO18
                GPIO_M_SET(17, 0);
                GPIO_M_SET(18, 0);          
        #else//MP_BOARD_256_PIN_NON_SHARE
                        // gpio 17, 18 for I2C
                        GPIO_M_SET(17, 0);
                        GPIO_M_SET(18, 0);
        #endif//MP_BOARD_256_PIN_NON_SHARE
        #ifdef DVI_I2C_SET //chenzhao20050606
        i2c_init_io_risc();
        #endif//#ifdef DVI_I2C_SET
    #elif defined(SPHE1000)
    // select GPIO44,45 for I2C
    GPIO_M_SET(44,0);
    GPIO_M_SET(45,0);
    #else
    // select GPIO 0,1 for I2C
    regs0->gpio_master[0 / 16] &= ~(0x3 << (0 % 16));
    #endif
#endif

#ifdef SUPPORT_SPI
    regs0->gpio_master[SPI_DATAIN / 16] &= ~(0x1 << (SPI_DATAIN % 16)); //SPI IN
    regs0->gpio_master[SPI_CLK / 16] &= ~(0x1 << (SPI_CLK % 16)); // SPI CLK
    regs0->gpio_master[SPI_DATAOUT / 16] &= ~(0x1 << (SPI_DATAOUT % 16)); // SPI OUT

    //regs0->gpio_master[49 / 16] |= (0x1 << (49 % 16)); //50 SPI IN
    //regs0->gpio_master[51 / 16] |= (0x1 << (51 % 16)); //51 SPI CLK
    //regs0->gpio_master[52 / 16] |= (0x1 << (52 % 16)); //52 SPI OUT
//while(1)
//{
//  GPIO_E_SET(49, 1);
//  GPIO_O_SET(49, 0);
    //GPIO_O_SET(49, 1);
//  GPIO_E_SET(49, 0);
//  delay_1ms(100);
//}
    //GPIO_E_SET(51, 1);
    //GPIO_O_SET(51, 1);
    
    //GPIO_E_SET(52, 1);
    //GPIO_O_SET(52, 1);
#endif

//  set GPIO97(GAME_D1) for PS/2 mouse DATA and GPIO98(GAME_D0) for PS/2 mouse CLK
#if defined(SUPPORT_PS2) && !defined(SUPPORT_GAMEPAD_MOUSE) && !defined (SUPPORT_USB_HID)
    GPIO_M_SET(97, 0);
    GPIO_M_SET(98, 0);
#endif

    // select GPIO 40,41,42,43 for game pad
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME) || defined(SUPPORT_GAMEPAD_MOUSE)
#ifndef SUPPORT_IR_GAME
#ifdef SPHE8202
    #if defined(MP_BOARD_256_PIN_NON_SHARE)
        #if defined(SDRAM_BUS_32BITS)||defined(SDRAM_128Mx1) //mimitsai add 2004-12-07
        regs0->gpio_master[98 / 16] &= ~(0x1 << (98 % 16)); //D0  gpio 98 PIN 231
        regs0->gpio_master[97 / 16] &= ~(0x1 << (97 % 16)); //D1  gpio 97 PIN 230
        regs0->gpio_master[99 / 16] &= ~(0x1 << (99 % 16)); //CLK   gpio 99 PIN 232
        regs0->gpio_master[96 / 16] &= ~(0x1 << (96 % 16)); //LATCH gpio 96 PIN 229
        #else
        regs0->gpio_master[98 / 16] &= ~(0x1 << (98 % 16)); //D0  gpio 98 PIN 231
        regs0->gpio_master[97 / 16] &= ~(0x1 << (97 % 16)); //D1  gpio 97 PIN 230
        regs0->gpio_master[99 / 16] &= ~(0x1 << (99 % 16)); //CLK   gpio 99 PIN 232
        regs0->gpio_master[100 / 16] &= ~(0x1 << (100 % 16)); //LATCH gpio 100 PIN 233
        #endif  
    #elif defined(MP_BOARD_216_PIN_NON_SHARE)   //rbhung for 8202S/D 216pin 2005-01-13
        #ifdef IC_8202E_216_PIN_NON_SHARE_CD_DVD_MP_BOARD
        regs0->gpio_master[15 / 16] &= ~(0x1 << (15 % 16)); //D0  gpio 15 PIN 65
        regs0->gpio_master[16 / 16] &= ~(0x1 << (16 % 16)); //D1  gpio 16 PIN 66
        regs0->gpio_master[11 / 16] &= ~(0x1 << (11 % 16)); //CLK   gpio 11 PIN 59
        regs0->gpio_master[10 / 16] &= ~(0x1 << (10 % 16)); //LATCH gpio 10 PIN 58
        #else
        	#ifdef GAME_GPIO_USE_PIN52_125_181_182	//yaowh add 2006-3-13 13:46
        	regs0->gpio_master[60 / 16] &= ~(0x1 << (60 % 16)); //D0  gpio 60 PIN 181
        	regs0->gpio_master[61 / 16] &= ~(0x1 << (61 % 16)); //D1  gpio 61 PIN 182
        	regs0->gpio_master[ 5 / 16] &= ~(0x1 << ( 5 % 16)); //CLK   gpio 5 PIN 52
        	regs0->gpio_master[29 / 16] &= ~(0x1 << (29 % 16)); //LATCH gpio 29 PIN 125
        	#else
            regs0->gpio_master[13 / 16] &= ~(0x1 << (13 % 16)); //D0  gpio 13 PIN 62
            regs0->gpio_master[14 / 16] &= ~(0x1 << (14 % 16)); //D1  gpio 14 PIN 63
            regs0->gpio_master[11 / 16] &= ~(0x1 << (11 % 16)); //CLK   gpio 11 PIN 59
            regs0->gpio_master[12 / 16] &= ~(0x1 << (12 % 16)); //LATCH gpio 12 PIN 61
            #endif
        #endif
    #else
        regs0->gpio_master[87 / 16] &= ~(0x1 << (87 % 16)); //D0  gpio 87 PIN 181
        regs0->gpio_master[86 / 16] &= ~(0x1 << (86 % 16)); //D1  gpio 86 PIN 180
        regs0->gpio_master[88 / 16] &= ~(0x1 << (88 % 16)); //CLK   gpio 88 PIN 183
        regs0->gpio_master[89 / 16] &= ~(0x1 << (89 % 16)); //LATCH gpio 89 PIN 184
    #endif
#else

#ifdef GBM_PORTABLE_DVD
    regs0->gpio_master[45 / 16] &= ~(0x1 << (45 % 16)); //D0  gpio 45 PIN 140
    regs0->gpio_master[17 / 16] &= ~(0x1 << (17 % 16)); //D1  gpio 17 PIN 141
    regs0->gpio_master[54 / 16] &= ~(0x1 << (54 % 16)); // CLK   gpio 54 PIN 154
    regs0->gpio_master[55 / 16] &= ~(0x1 << (55 % 16)); // LATCH gpio 55 PIN 155
#else
    #ifndef SDRAM_16Mb_Mode
    regs0->sft_cfg1 &= ~(0x1 << 3); // CS4 as GPIO3
    regs0->gpio_master[2 / 16] &= ~(0x1 << (2 % 16)); //D0  gpio 2 PIN 28
    regs0->gpio_master[3 / 16] &= ~(0x1 << (3 % 16)); //D1 gpio 3 PIN 29
        
    regs0->gpio_master[4 / 16] &= ~(0x1 << (4 % 16)); // clk  gpio 4 PIN 31
    regs0->gpio_master[35 / 16] &= ~(0x1 << (35 % 16)); // latch  gpio 35PIN 70

    #else

    // select GPIO 40,41,42,43 for game pad
    regs0->sft_cfg0 &= ~(0xff << 7);
    regs0->gpio_master[40 / 16] &= ~(0xf << (40 % 16));

    #endif
#endif
#endif  //SPHE8202
#endif  //SUPPORT_IR_GAME
#endif  //SUPPORT_NESGAME

#ifdef SPHE8202
    // gpio 20 as IR
    GPIO_M_SET(20, 0);
#elif defined(SPHE1000)
    // gpio 26 as IR
    GPIO_M_SET(26, 0);
#else
    // GPIO 53 as IR, GPIO 54,55,56 as VFD
    regs0->gpio_master[53 / 16] &= ~(0x1 << (53 % 16));
#endif

#ifdef SUPPORT_VFD
    #ifdef SPHE8202
        // gpio 21, 22, 23 for VFD
        GPIO_M_SET(21, 0);
        GPIO_M_SET(22, 0);
        GPIO_M_SET(23, 0);
    #elif defined(SPHE1000)
    // GPIO 26 as IR, GPIO 27,28,29 as VFD
        GPIO_M_SET(27, 0);
    GPIO_M_SET(28, 0);
    GPIO_M_SET(29, 0);
    #else
        // GPIO 53 as IR, GPIO 54,55,56 as VFD
        regs0->gpio_master[54 / 16] &= ~(0x7 << (54 % 16));
    #endif
#endif

    #ifdef TTE_HOST_DVD      //for TTE PCA964  LIJD 2004-11-11 20:02       
        regs0->sft_cfg0 &= ~(0x1 << 7);//GPIO48   
        regs0->sft_cfg1 &= ~(0x1 << 5);//GPIO49    
        GPIO_M_SET(32, 0);
        GPIO_M_SET(33, 0);
        GPIO_M_SET(35, 0); 
        GPIO_M_SET(36, 0);
        GPIO_M_SET(37, 0);        
        GPIO_M_SET(40, 0);
        GPIO_M_SET(41, 0);
        GPIO_M_SET(42, 0);
        GPIO_M_SET(43, 0);
        GPIO_M_SET(44, 0);
        GPIO_M_SET(45, 0);
        GPIO_M_SET(46, 0);
        GPIO_M_SET(47, 0);   
        GPIO_M_SET(48, 0);         
        GPIO_M_SET(49, 0);
    #endif

    // reset IOP/RISC interface
    for (i = 0; i < 7; i++) regs0->iop_data[i] = 0;

// below registers' value are used only for first time gotten by IOP
// regs0->iop_data[1]: in standby mode or not (1:Y, 0:N)
// regs0->iop_data[2]: store IR power key value
// regs0->iop_data[3]: store VFD power key value
// regs0->iop_data[4]: IR power key exist or not
// regs0->iop_data[5]: VFD power key exist or not
//
    if (bSleepFlag)
    {
        BYTE nIndex, bVFD_MASK, nIndex2 = 0;

        regs0->iop_data[1] = 1;
#if defined(DP2030_SCAN_KEY)//eastech2030
    GPIO_M_SET(23,0);
    GPIO_M_SET(100,0);
#elif defined(DP30H0_KEY_SCAN)//eastech2030
regs0->sft_cfg1 &= ~(0x1 << 5); 
    GPIO_M_SET(94,0);
    GPIO_M_SET(97,0);
#endif
#ifdef USE_VFDPORT_TO_KEYLIGHT_GBM
        regs0->gpio_master[54 / 16] &= ~(0x7 << (54 % 16));//NONO 2003-8-3 15:34
#endif//USE_VFDPORT_TO_KEYLIGHT_GBM
#ifdef VTREK_MINI_DVD      //linrc add for vtreck mini dvd 2004-3-27 16:50
    regs0->gpio_master[54 / 16] &= ~(0x7 << (54 % 16));//linrc 2003-8-3 15:34
    GPIO_M_SET(55,0);
#endif //endif VTREK_MINI_DVD
#ifdef USE_PIN31_CONTROL_POWER_LED
        regs0->gpio_master[4 / 16] &= ~(0x1 << (4 % 16));//gerry,2004/2/11 05:32¤U¤È
#endif//USE_PIN31_CONTROL_POWER_LED
#if defined(HANYANG_SCAN_KEY)||defined(HJ2439_SCAN_KEY)     //caoh 2004-4-19 12:00
    regs0->sft_cfg3 &= ~(0x1 << 5);//PIN163 use as SCART_RGB gpio57
    regs0->sft_cfg6 &= ~(0x1 << 5);//PIN151 use as SCART_SW gpio18
    GPIO_M_SET(54,0);
    GPIO_M_SET(55,0);
    GPIO_M_SET(56,0);
    GPIO_M_SET(57,0);
    GPIO_M_SET(18,0);    
#endif   
        // get IR code
        for (nIndex = 0; nIndex <= 255; nIndex++)
        {
            if (ir_mapcode[nIndex] == IRC_POWER)
            {
                regs0->iop_data[4] = 1;
                nIndex2 = nIndex;
                break;
            }
        }

#if   defined(IR_NEC)||defined(IR_M50560)||defined(IR_AS1213)||defined(IR_ORITRON)||defined(IR_THOMSON_ANGUS)||defined(IR_MRC2222)
        nIndex = reverse_fun(nIndex);
#endif
        regs0->iop_data[2] = nIndex;
        printf("IR IRC_POWER = %d\n", nIndex); 

#ifdef PULIANG_EJECT_MODE  //yaowh add 04-12-17
    for (nIndex = 0; nIndex <= 255; nIndex++)
    {
        if (ir_mapcode[nIndex] == IRC_EJECT)
        {
            regs0->iop_data[5] = 1;
            break;
        }
    }
    #if defined (IR_NEC)||defined(IR_MRC2222)//frank.huang 050801
        nIndex = reverse_fun(nIndex);
    #endif
        regs0->iop_data[3] = nIndex;
#else//#ifdef PULIANG_EJECT_MODE

#if (VFD_DRIVER == HT1621)||defined(SUPPORT_EX_IR) // Robert 031024
        //if vfd driver is HT1621, we check another IR power key.
        for (nIndex = nIndex2 + 1; nIndex <= 255; nIndex++)
        {
            if (ir_mapcode[nIndex] == IRC_POWER)
            {
                regs0->iop_data[5] = 1;
                break;
            }
        }

#if defined (IR_NEC)||defined(IR_MRC2222)

        nIndex = reverse_fun(nIndex);
#endif
        regs0->iop_data[3] = nIndex;
        printf("IR IRC_POWER 2 = %d\n", nIndex); 

#else // (VFD_DRIVER == HT1621)
        // get VFD code

#ifdef SUPPORT_VFD//nono 2003-11-24 12:06
        for (nIndex = 0; nIndex < 40; nIndex++)
        {
#ifdef QISHENG_DVD
            if (vfd_keycode[nIndex] == IRC_STOP)
#elif defined(GBM_POWER_ON_USE_EJECT_KEY)       //gerry add it for eject,04-1-28 17:39
            if (vfd_keycode[nIndex] == IRC_EJECT)
#elif defined(GBM_POWER_ON_USE_PAUSEPLAY_KEY)       //gerry add it for pauseplay,04-1-28 17:39
            if (vfd_keycode[nIndex] == IRC_PAUSEPLAY)
#else
            if (vfd_keycode[nIndex] == IRC_POWER)
#endif          
            {
                regs0->iop_data[5] = 1;
                nIndex++;
                break;
            }
        }
#endif//SUPPORT_VFD

        #if (VFD_DRIVER == SPL10)
                regs0->iop_data[3]=nIndex;//2004-2-9 12:48 LIJD
                #else
    if(nIndex==40)
    {
        regs0->iop_data[3] =0x0f;
    }
    else if(nIndex==8)
    {
        regs0->iop_data[3] =0x80;
    }
    else if(nIndex==16)
    {
        regs0->iop_data[3] =0x180;
    }
    else if(nIndex==24)
    {
        regs0->iop_data[3] =0x280;
    }
    else if(nIndex==32)
    {
        regs0->iop_data[3] =0x380;
    }
    else
    {       
        bVFD_MASK = nIndex % 8;
        bVFD_MASK = 1 << (bVFD_MASK - 1);
        nIndex = nIndex / 8;
        regs0->iop_data[3] = nIndex;
        regs0->iop_data[3] <<= 8;
        regs0->iop_data[3] |= bVFD_MASK;
    }
#endif
        printf("VFD IRC_POWER = %x\n", regs0->iop_data[3]);
#endif // (VFD_DRIVER == HT1621)
#endif//PULIANG_EJECT_MODE
#ifdef TCL_STANDBY
        regs0->sft_cfg1 &= ~(0x1 << 3);//gpio 3 enable
        regs0->gpio_master[ 3/16 ] &= ~(0x1 << (3%16));//gpio 3 for iop
        regs0->gpio_master[ 2/16 ] &= ~(0x1 << (2%16));//gpio 2 for iop
#endif
       
#ifdef RISC_ALIVE_STANDBY       
    #ifdef VIDEO_IN_CONTROL
    if(AVin_step == 0x0f)
	{
	  AVin_step = 0;
	  go_into_prestandby = 1;
	}
	#endif    
#elif defined(ALONE_GPIO_KEY)//Jack 20040930
        GPIO_M_SET(STANDBY_KEY_GPIO,0);
        GPIO_M_SET(STANDBY_LED_GPIO,0);
        GPIO_M_SET(EJECT_KEY_GPIO,0);
        GPIO_M_SET(STOP_EJECT_KEY_GPIO,0);
        GPIO_M_SET(BACKWARD_KEY_GPIO,0);
        GPIO_M_SET(FORWARD_KEY_GPIO,0);
        GPIO_M_SET(44,0);
#endif //endif #ifdef RISC_ALIVE_STANDBY
        
        LoadModual(MODUAL_IOP_RESET);
        printf("iop modual: iop standby mode\n"); //terry,2005/4/4 03:18¤U¤È
    }
    else
    {
        LoadModual(MODUAL_IOP);
        printf("iop modual: iop normal mode\n");
    }


/*
    // download binary
    p = (UINT32 *) IOPcode;
    q = (UINT32 *) (SDRAM_BASE + MEM_IOPYA * 1024);
    len = (IOPcodelen+3) & ~0x03;
    for (i=0; i<len/4; i++) *q++ = *p++;
*/
    MIPS_flush_LBC_cache();
    
    // release iop
    IOP_GO();
    
    delay_1ms(10);
  
#ifdef SOFT_UART_OUT
    bResetIop=1;
#endif     
}
/**************************************************************************
 *  Function Name: static  inline  int __is_iop_ready(void)               *
 *  Purposes:                                                             *
 *              Judge iop is ready  or not .                              *
 *  Descriptions:                                                         *
 *              wait iop function ready for new command                   *
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              return 1: IOP is ready                                    * 
 *              return 0: IOP is not ready                                *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/
static  inline  int
__is_iop_ready(void)
{
    return !(regs0->iop_data[0]&FUN_MASK);
}

/**************************************************************************
 *  Function Name: int IsIopFunRdy(void)                                  *
 *  Purposes:                                                             *
 *               Judge iop function is ready  or not .                    *
 *  Descriptions:                                                         *
 *              (None)                                                    *
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              return 1: IOP is ready                                    * 
 *              return 0: IOP is not ready                                *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/
int
IsIopFunRdy(void)
{
    return __is_iop_ready();
}

/**************************************************************************
 *  Function Name:  int WaitIopFunRdy(int iWait)                          *
 *  Purposes:                                                             *
 *               Judge iop is ready or not in  "iWait" time .             *
 *  Descriptions:                                                         *
 *              (None)                                                    *
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              return >0: IOP is ready                                   * 
 *              return -1: IOP is not ready                               *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/
int
WaitIopFunRdy(int iWait)
{
    do {
        if (__is_iop_ready())
            return iWait;
    } while (--iWait>0);
  
#ifdef IOP_DEBUG_INFO
    printf("iopf timeout\n");
#endif
    return -1;
}

/**************************************************************************
 *  Function Name: int WriteI2c(                                          *
 *                   int iDeviceAddr,                                     *
 *                   int iAddr,                                           *
 *                   int iData,                                           *
 *                   int iLen)                                            *
 *  Purposes:                                                             *
 *              Write 1,2 byte data into 24c02.                           *
 *  Descriptions:                                                         *
 *              Input :                                                   *
 *                    iDeviceAddr = device address                        * 
 *                    iAddr   = destination address                       *
 *                    iData   = the input data                            *  
 *                    len     = 1,2                                       *                                    
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              return -1:  iop isn't ready.                              *
 *              return  0:  write I2C sucess                              *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/

#ifdef SETUP_IN_FLASH
extern void ReadFromI2cA0(UINT16 iAddr,BYTE *bBuffer,UINT16 len);
extern int ReadFromI2cA0_32(UINT16 iAddr,BYTE *bBuffer,UINT16 len);
extern void WriteToI2cA0(int iAddr,BYTE *bData,int len);
#endif

int
WriteI2c(int iDeviceAddr,int iAddr,int iData,int iLen)
{
    int iCmd;
    
    iCmd=(iDeviceAddr<<8)|((iAddr<<1)&0x0e00)|(iAddr&0xff);
    
    if (WaitIopFunRdy(IOP_RDY_WAIT)<0)
        return -1;
    
    //setting parameter
    regs0->iop_data[I2C_CTRL_ADDR]=iCmd;
    regs0->iop_data[I2C_DATA]=iData;
    
    //select function 
    if (iLen==1)
        regs0->iop_data[0]=FUN_I2C_WRITE|I2C_WRITE_BYTE|VFD_DAT_LEN0;   
    else
        regs0->iop_data[0]=FUN_I2C_WRITE|I2C_WRITE_BYTE|VFD_DAT_LEN1;   
    return 0;
}


#if defined(DVI_I2C_SET)&&defined(SPHE8202)//Modifed by ChenZhao on 2004-9-21 15:59  
/**************************************************************************
 *  Function Name: int WriteToI2c(                                        *
 *                   int iDeviceAddr,                                     *
 *                   int iAddr,                                           *
 *                   BYTE *bData,                                         *
 *                   int iLen)                                            *
 *  Purposes:                                                             *
 *              Write n byte data to I2C memory/device on BYTE mode       *
 *               and wait complete                                        *
 *  Descriptions:                                                         *
 *              Input :                                                   *
 *                    iDeviceAddr = device address                        * 
 *                    iAddr   = destination address                       *
 *                    *bData= the input data stream.                      *  
 *                    len   = the write data lenght                       *                                     
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              return -1:  write error                                   *
 *              return  1:  write success                                 *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/
int
WriteToI2c(int iDeviceAddr,int iAddr,BYTE *bData,int len)
{
    UINT16 loop;
    
#ifdef SCALER_6500 //helm re-open these parameter with 6500, 050729
    int ret=0;
    unsigned char data=0,checkfail;
#endif

#ifdef NO_EEPORM
    if(iDeviceAddr==0xa0)
        return -1;
#endif
#ifdef SETUP_IN_FLASH
    if (iDeviceAddr == 0xa0)
    {
        WriteToI2cA0(iAddr,bData, len);
        return 1;
    }
#endif  

    /*if use 24c04, we need to change Addr to 0xa2.huziqin*/
    if(iDeviceAddr == 0xa0)//chenzhao 20060113
    {
        iDeviceAddr |=((iAddr>>7)&0x0e);
    }
    
    printf("I2Cwrite DADDR 0X%x iAddr 0X%x LEN 0X%x\n",iDeviceAddr,iAddr,len);
    //i2c_init_io_risc();

    while (len)
    { 
        loop=0;
        if(iAddr>0xff)
        {
            iDeviceAddr &= 0xf0;
            iDeviceAddr |=((iAddr&0x700)>>7);
        }
#ifdef SCALER_6500 //HELM for scaler 6500 platform, 050729
        do
        {
            checkfail=0;
            if(0xa0==(iDeviceAddr & 0xf0))//Only write to 24c02 need read out check.//chenzhao 2004/10/9
            {
            for (;loop<K_loopMax;loop++)
        {
        ret=0;
        init_i2c();
        i2c_start_sig();
                    ret+=i2c_byte_w(iDeviceAddr&0xfe); //W add
            if(ret)  continue;
        ret+=i2c_byte_w(iAddr);
        if(ret)  continue;
                    //  i2c_stop_sig();     
                    // Read DATA
                    i2c_start_sig();
                    ret+=i2c_byte_w(iDeviceAddr|1); //R data
        if(ret)  continue;
                    data=i2c_byte_r(1);
        i2c_stop_sig();  
        break;
        }
                if (loop >= K_loopMax) 
            {
            printf("I2CWRITE ERR DADDR 0X%x LEN 0X%x\n",iDeviceAddr,len);
            //i2c_init_io_iop();
            return -1;
            }
                if(data!=*bData)
                {
                    checkfail=1;
                    loop++;
                }
                else
                    break;
            }
#endif //SCALER_6500
            for (;loop<K_loopMax;loop++)
                {
                i2c_start_sig();
                if(0==i2c_byte_w(iDeviceAddr&0xfe)) //W add data(addr<<1|0); //W add data
                    if(0==i2c_byte_w(iAddr))
                        if(0==i2c_byte_w(*bData))
                        {
                            i2c_stop_sig();  
                            break;
                        }
                init_i2c();
                }
            if (loop >= K_loopMax) 
               {
                printf("I2CWRITE ERR DADDR 0X%x LEN 0X%x\n",iDeviceAddr,len);
                //i2c_init_io_iop();
                return -1;
               }
#ifdef SCALER_6500               
        }while(checkfail);
#endif
        
        len--;
        bData++;
        iAddr++;
        //printf("loop=%d ",loop);
    }
    
    //i2c_init_io_iop();
    return 1;
}
#else//defined(DVI_I2C_SET)&&defined(SPHE8202)
/**************************************************************************
 *  Function Name: int WriteToI2c(                                        *
 *                   int iDeviceAddr,                                     *
 *                   int iAddr,                                           *
 *                   BYTE *bData,                                         *
 *                   int iLen)                                            *
 *  Purposes:                                                             *
 *              Write n byte data to I2C memory/device on BYTE mode       *
 *               and wait complete                                        *
 *  Descriptions:                                                         *
 *              Input :                                                   *
 *                    iDeviceAddr = device address                        * 
 *                    iAddr   = destination address                       *
 *                    *bData= the input data stream.                      *  
 *                    len   = the write data lenght                       *                                     
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              return -1:  write error                                   *
 *              return  1:  write success                                 *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/
int
WriteToI2c(int iDeviceAddr,int iAddr,BYTE *bData,int len)
{
    int iCmd;

#ifdef NO_EEPORM
    if(iDeviceAddr==0xa0)
        return -1;
#endif

#ifdef SETUP_IN_FLASH
    if (iDeviceAddr == 0xa0)
    {
        WriteToI2cA0(iAddr,bData, len);
        return 1;
    }
#endif
    
    if (WaitIopFunRdy(IOP_RDY_WAIT)<0)
    {
    #ifdef IOP_DEBUG_INFO
        printf("i2c-f fail %x %x %x\n", iDeviceAddr, iAddr, len);
    #endif
        return -1;
    }
    
    
    //pro-clear error flag
    regs0->iop_data[0]&=(~I2C_RW_ERR);
    
    while (len)
    { 
        iCmd=(iDeviceAddr<<8)|((iAddr<<1)&0x0e00)|(iAddr&0xff);
        
        
        if (WaitIopFunRdy(IOP_RDY_WAIT)<0)
        {
    #ifdef IOP_DEBUG_INFO
            printf("i2c-f fail %x %x %x\n", iDeviceAddr, iAddr, len);
    #endif
            return -1;
        }
        
        if (regs0->iop_data[0]&I2C_RW_ERR)
            return -1;
        
        
        //setting parameter
        regs0->iop_data[I2C_CTRL_ADDR]=iCmd;
        regs0->iop_data[I2C_DATA]=*bData;
        
        //select function and clear flag
        regs0->iop_data[0]=FUN_I2C_WRITE|I2C_WRITE_BYTE|VFD_DAT_LEN0;
        len--;
        bData++;
        iAddr++;
    }
    
    
    if (WaitIopFunRdy(IOP_RDY_WAIT)<0)
        return -1;
    
    if (regs0->iop_data[0]&I2C_RW_ERR)
        return -1;
        
    
    return 1;
}
#endif//defined(DVI_I2C_SET)&&defined(SPHE8202)

BYTE bI2cCurDatLoc,bI2cSendLen=0;
BYTE bI2cSendBuffer[15];
WORD bI2cWaitResponse;

#ifdef TAS3001_AMP
/**************************************************************************
 *  Function Name: inline void  PollingI2CPageWrite()                     *
 *  Purposes:                                                             *
 *               Write bI2cSendLen byte data to I2C memory/device         *
 *               on Page mode and wait complete .                         *
 *                                                                        *
 *  Descriptions:                                                         *
 *              (None)                                                    *
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              (None)                                                    *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/
inline void  PollingI2CPageWrite()
{
    if (bI2cSendLen)
    {
        if (regs0->iop_data[0]&I2C_WR_RDY)
        {   
            regs0->iop_data[I2C_DATA]=bI2cSendBuffer[bI2cCurDatLoc];
    
            bI2cSendLen--;
            bI2cCurDatLoc++;
            bI2cWaitResponse=0;
            
            if (bI2cSendLen)
                //write next byte
                regs0->iop_data[0]&=(~I2C_WR_RDY);
            else
                //last byte to write
                regs0->iop_data[0]&=((~I2C_WRITE_PAGE)&(~I2C_WR_RDY));
        }
        else
        {
            bI2cWaitResponse++;                 
            if (bI2cWaitResponse==0xffff)
                bI2cSendLen=0;
        }
    }
}
#endif
/**************************************************************************
 *  Function Name: void WriteToI2cPageMode(                                        *
 *                   int iDeviceAddr,                                     *
 *                   int iAddr,                                           *
 *                   BYTE *bData,                                         *
 *                   int iLen)                                            *
 *  Purposes:                                                             *
 *              Write n byte data to I2C memory/device on Page mode       *
 *               and wait complete                                        *
 *  Descriptions:                                                         *
 *              Input :                                                   *
 *                    iDeviceAddr = device address                        * 
 *                    iAddr   = destination address                       *
 *                    *bData= the input data stream.                      *  
 *                    len   = the write data lenght                       *                                     
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              (None)                                                    *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/
#ifdef Tuner_8202_I2C  //wthsin,2005/2/2 12:02pm
void WriteToI2cPageMode(int iDeviceAddr,int iAddr,BYTE *bData,int len)
{
  int iCmd;  
  int iWait;
  //printf("W_3_:iDeviceAddr=%x,iAddr=%d,len=%d \n",iDeviceAddr,iAddr,len);
  //check it's on stop state
 
  if (WaitIopFunRdy(IOP_RDY_WAIT)<0)
  {
    //#ifdef IOP_DEBUG_INFO
    printf("i2c-f fail %x %x %x\n", iDeviceAddr, *bData, len);
    //#endif
    return;
  }

  //pro-clear error flag
  regs0->iop_data[0]&=(~I2C_RW_ERR);

  iCmd=(iDeviceAddr<<8)|((iAddr<<1)&0x0e00)|(iAddr&0xff);

  //setting parameter
  regs0->iop_data[0]=FUN_I2C_WRITE|I2C_WRITE_PAGE|VFD_DAT_LEN0;   
  regs0->iop_data[I2C_CTRL_ADDR]=iCmd;
  regs0->iop_data[I2C_DATA]=*bData++;  
  len--;
  
    while(len)
    {
/*
        if(WaitIopWriteRdy(IOP_RDY_WAIT)<0)
            return; 
*/
        for (iWait=IOP_RDY_WAIT;iWait>=0 && !(regs0->iop_data[0]&I2C_WR_RDY);iWait--)
        {
            if (regs0->iop_data[0]&I2C_RW_ERR)
                return -1;
        }
        
        if (iWait<0)
            return -1;
        
        regs0->iop_data[I2C_DATA] = *bData++;
        len--;
        if(len)
            regs0->iop_data[0] &= (~I2C_WR_RDY);
        else
            regs0->iop_data[0] &= ((~I2C_WRITE_PAGE)&(~I2C_WR_RDY));
            
    }
                  
  return;    
}
#elif defined(DVI_I2C_SET)&&defined(SPHE8202)&&defined(I2C_PAGE_MODE)//chenzhao20050606
int WriteToI2cPageMode(int iDeviceAddr,int iAddr,BYTE *bData,int len)
{
        UINT16 loop;
        int ret=0;
    
    #ifdef NO_EEPORM
        if(iDeviceAddr==0xa0)
            return -1;
    #endif
    #ifdef SETUP_IN_FLASH
        if (iDeviceAddr == 0xa0)
        {
            WriteToI2cA0(iAddr,bData, len);
            return 1;
        }
    #endif  
        printf("I2CWRITE_P DADDR 0X%x iAddr 0X%x LEN 0X%x\n",iDeviceAddr,iAddr,len);
        //i2c_init_io_risc();
    
        for (loop=0;loop<K_loopMax;loop++)
        {
            ret=0;
            init_i2c();
            i2c_start_sig();
            ret+=i2c_byte_w(iDeviceAddr&0xfe); //W add data(addr<<1|0); //W add data
            if(ret)  continue;
            ret+=i2c_byte_w(iAddr & 0xff);
            if(ret)  continue;
            for(;len>0;len--)
            { 
                ret+=i2c_byte_w(*bData);
                if(ret)break;
                bData++;
                //printf("loop=%d ",loop);
            }
            i2c_stop_sig();  
            if(ret)
                continue;
            else
                break;
        }
        if (loop >= K_loopMax) 
        {
            printf("I2CWRITE_P ERR DADDR 0X%x LEN 0X%x\n",iDeviceAddr,len);
            //i2c_init_io_iop();
            return -1;
        }
        
        //i2c_init_io_iop();
        return 1;
}
int ReadFromI2cPageMode(int iDeviceAddr,int iAddr,BYTE *bData,int len)
{
        int ret=0;
        // Write ADDR
        unsigned char loop;
    
    
    #ifdef NO_EEPORM
        if(iDeviceAddr==0xa0)
            return -1;
    #endif
    
    #ifdef SETUP_IN_FLASH
        if (iDeviceAddr == 0xa0)
        {
            ReadFromI2cA0(iAddr,bBuffer,len);
            return 1;
        }
    #endif
     
        printf("I2CREAD_P DADDR 0X%x iAddr 0X%x LEN 0X%x\n",iDeviceAddr,iAddr,len);
        //i2c_init_io_risc();
        //wait function rdy
        for (loop=0;loop<K_loopMax;loop++)
        {
            ret=0;
            init_i2c();
            i2c_start_sig();
            ret+=i2c_byte_w(iDeviceAddr&0xfe); //W add
            if(ret)  continue;
            ret+=i2c_byte_w(iAddr);
            if(ret)  continue;
            i2c_start_sig();
            ret+=i2c_byte_w(iDeviceAddr|1); //R data
            if(ret)  continue;
            for(;len>0;len--)
            {
                
                // Read DATA
                *bData=i2c_byte_r((len==1)?1:0);//return ack except the last byte
                bData++;
                //printf("loop=%d ",loop);
            }
            i2c_stop_sig();  
            break;
        }
        if (loop >= K_loopMax) 
        {
            printf("I2CREAD_P ERR DADDR 0X%x LEN 0X%x\n",iDeviceAddr,len);
            //i2c_init_io_iop();
            return -1;
        }
        //i2c_init_io_iop();
        return 1;
}
#endif //Tuner_8202_I2C
/////////////////////////////////////////////////////
///////xyy add for I2C sequential read/write/////////
////////////////2003-11-30 14:18/////////////////////
/////////////////////////////////////////////////////
#ifdef SUPPORT_RDS_FUNCTION
/**************************************************************************
 *  Function Name: static inline int _is_iop_write_ready(void)            *
 *  Purposes:                                                             *
 *              Judge iop I2C write is ready or not .                     *
 *  Descriptions:                                                         *
 *              (None)                                                    *
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              return 1: I2C write is ready.                             *
 *              return 0: I2C write isn't ready.                          *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/
static inline int _is_iop_write_ready(void)
{
    return (regs0->iop_data[0] & I2C_WR_RDY);
}
/**************************************************************************
 *  Function Name: int WaitIopWriteRdy(int iWait)                         *
 *  Purposes:                                                             *
 *              Judge iop I2C write is ready or not .                     *
 *  Descriptions:                                                         *
 *              (None)                                                    *
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              return >0: I2C write is ready.                             *
 *              return -1: I2C write isn't ready.                          *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/
int WaitIopWriteRdy(int iWait)
{
    do{
        if(_is_iop_write_ready())
            return iWait;
    }while(--iWait>0);
    return -1;
}
/**************************************************************************
 *  Function Name: void WriteToI2cSequentialMode(                         *
 *                   int iDeviceAddr,                                     *
 *                   BYTE *bData,                                         *
 *                   int iLen)                                            *
 *  Purposes:                                                             *
 *              Sequential write n byte data to I2C memory/device         *
 *              on BYTE mode and wait complete.                           *
 *                                                                        *
 *  Descriptions:                                                         *
 *              Input :                                                   *
 *                    iDeviceAddr = device address                        * 
 *                    *bData= the input data stream.                      *  
 *                    len   = the write data lenght                       *                                    
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              (None)                                                    *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/
void WriteToI2cSequentialMode(int iDeviceAddr,BYTE *bData,int len)
{
  int iCmd;  
  
  //check it's on stop state
 
  if (WaitIopFunRdy(IOP_RDY_WAIT)<0)
  {
    //#ifdef IOP_DEBUG_INFO
    printf("i2c-f fail %x %x %x\n", iDeviceAddr, *bData, len);
    //#endif
    return;
  }

  //pro-clear error flag
  regs0->iop_data[0]&=(~I2C_RW_ERR);

  iCmd=iDeviceAddr<<8;   

  //setting parameter
  regs0->iop_data[0]=FUN_I2C_WRITE|I2C_WRITE_PAGE|VFD_DAT_LEN0|I2C_SEQUENTIAL_ORER;   
  regs0->iop_data[I2C_CTRL_ADDR]=iCmd;
  regs0->iop_data[I2C_DATA]=*bData++;  
  len--;
  
    while(len)
    {
        if(WaitIopWriteRdy(IOP_RDY_WAIT)<0)
            return; 
        
            regs0->iop_data[I2C_DATA] = *bData++;
            len--;
            if(len)
                regs0->iop_data[0] &= (~I2C_WR_RDY);
            else
                regs0->iop_data[0] &= ((~I2C_WRITE_PAGE)&(~I2C_WR_RDY)&(~I2C_SEQUENTIAL_ORER));
            
    }
                  
  return;    
}

/**************************************************************************
 *  Function Name: int ReadFromI2cSequentialMode(                         *
 *                   int iDeviceAddr,                                     *
 *                   int iAddr,                                           *
 *                   BYTE *bBuffer,                                       *
 *                   int iLen)                                            *
 *  Purposes:                                                             *
 *              Sequential read n byte data from I2C memory/device        *
 *              on BYTE mode and wait complete                            *
 *  Descriptions:                                                         *
 *              Input :                                                   *
 *                    iDeviceAddr = device address                        * 
 *                    iAddr   = destination address                       *
 *                    *bBuffer=  the input data stream.                   *  
 *                    len   = the input data lenght                       *                                    
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              return -1:  read error                                    *
 *              return  1:  read success                                  *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/
/*huziqin 2004-2-26*/
int
ReadFromI2cSequentialMode(int iDeviceAddr,int iAddr,BYTE *bBuffer,int len)
{
  int iWait,iCmd;

#ifdef NO_EEPORM
    if(iDeviceAddr==0xa0)
       return -1;
#endif    

#ifdef SETUP_IN_FLASH
    if (iDeviceAddr == 0xa0)
    {
        ReadFromI2cA0(iAddr,bBuffer,len);
        return 1;
    }
#endif
 
  iCmd=(iDeviceAddr<<8)|((iAddr<<1)&0x0e00)|(iAddr&0xff);

  if (WaitIopFunRdy(IOP_RDY_WAIT)<0) return -1;
    
  //pro-clear error flag
  regs0->iop_data[0]&=(~I2C_RW_ERR);
        
  //setting parameter
  regs0->iop_data[I2C_CTRL_ADDR]=iCmd;
    
  // select one-time or continuous function
  if (len==1)       
    regs0->iop_data[0]=FUN_I2C_READ|I2C_READ_ONE;
  else      
    regs0->iop_data[0]=FUN_I2C_READ|I2C_READ_CONT;  
    
      regs0->iop_data[0] |= I2C_SEQUENTIAL_ORER;
  //wait function rdy       
  while(len)
  { 
    for (iWait=IOP_RDY_WAIT;iWait>=0 && !(regs0->iop_data[0]&I2C_RD_RDY);iWait--)
    {
      if (regs0->iop_data[0]&I2C_RW_ERR) return -1;
    }
            
    if (iWait<0) return -1;
                
    *bBuffer++=(BYTE)(regs0->iop_data[I2C_DATA]&0xff);
        
    len--;
                
    if (len==1)
      //read the last data
      regs0->iop_data[0]&=((~I2C_READ_CONT)&(~I2C_RD_RDY));
    else
      //clear flag      
      regs0->iop_data[0]&=(~I2C_RD_RDY);
  }

      regs0->iop_data[0] &= (~I2C_SEQUENTIAL_ORER);
  return 1;
}
#endif

#if defined(DVI_I2C_SET)&&defined(SPHE8202)//Modifed by ChenZhao on 2004-9-21 15:59  
/**************************************************************************
 *  Function Name: int ReadFromI2c(                                       *
 *                   int iDeviceAddr,                                     *
 *                   int iAddr,                                           *
 *                   BYTE *bBuffer,                                       *
 *                   int iLen)                                            *
 *  Purposes:                                                             *
 *              Read data from I2C device                                 *
 *  Descriptions:                                                         *
 *              Input :                                                   *
 *                    iDeviceAddr = device address                        * 
 *                    iAddr   = destination address ( 0 ~ 0x7ff)          *
 *                    *bBuffer= the input data stream.                    *  
 *                    len   = the input data lenght                       *                                    
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              return -1:  read error                                    *
 *              return  1:  read success                                  *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/
int
ReadFromI2c(int iDeviceAddr,int iAddr,BYTE *bBuffer,int len)
{
    //int ret=0;
    unsigned char data=0;
    // Write ADDR
    unsigned char loop;


#ifdef NO_EEPORM
    if(iDeviceAddr==0xa0)
        return -1;
#endif

#ifdef SETUP_IN_FLASH
    if (iDeviceAddr == 0xa0)
    {
        ReadFromI2cA0(iAddr,bBuffer,len);
        return 1;
    }
#endif
 
    /*if use 24c04, we need to change Addr to 0xa2.huziqin*/
    if(iDeviceAddr == 0xa0)//chenzhao 20060113
    {
        iDeviceAddr |=((iAddr>>7)&0x0e);
    }
    
    printf("I2CREAD DADDR 0X%x iAddr 0X%x LEN 0X%x\n",iDeviceAddr,iAddr,len);
    //i2c_init_io_risc();
    //wait function rdy
    while(len)
    {
        if(iAddr>0xff)
        {
            iDeviceAddr &= 0xf0;
            iDeviceAddr |=((iAddr&0x700)>>7);
        }
        for (loop=0;loop<K_loopMax;loop++)
            {
            i2c_start_sig();
            if(0==i2c_byte_w(iDeviceAddr&0xfe)) //W add
                if(0==i2c_byte_w(iAddr))
                {
                    // Read DATA
                    i2c_start_sig();
                    if(0==i2c_byte_w(iDeviceAddr|1)) //R data
                    {
                        data=i2c_byte_r(1);
                        i2c_stop_sig();  
                        break;
                    }
                }
            init_i2c();
            }
        if (loop >= K_loopMax) 
           {
            printf("I2CREAD ERR DADDR 0X%x LEN 0X%x\n",iDeviceAddr,len);
            //i2c_init_io_iop();
            return -1;
           }
    
        
        iAddr++;
        *bBuffer++=data;
        len--;
        //printf("loop=%d ",loop);
        
    }
    //i2c_init_io_iop();
    return 1;
}
#else//defined(DVI_I2C_SET)&&defined(SPHE8202)
/**************************************************************************
 *  Function Name: int ReadFromI2c(                                       *
 *                   int iDeviceAddr,                                     *
 *                   int iAddr,                                           *
 *                   BYTE *bBuffer,                                       *
 *                   int iLen)                                            *
 *  Purposes:                                                             *
 *              Read data from I2C device                                 *
 *  Descriptions:                                                         *
 *              Input :                                                   *
 *                    iDeviceAddr = device address                        * 
 *                    iAddr   = destination address                       *
 *                    *bBuffer= the input data stream.                    *  
 *                    len   = the input data lenght                       *                                    
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              return -1:  read error                                    *
 *              return  1:  read success                                  *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/
int
ReadFromI2c(int iDeviceAddr,int iAddr,BYTE *bBuffer,int len)
{
    
    int iWait,iCmd;


#ifdef NO_EEPORM
    if(iDeviceAddr==0xa0)
        return -1;
#endif

#ifdef SETUP_IN_FLASH
    if (iDeviceAddr == 0xa0)
    {
        ReadFromI2cA0(iAddr,bBuffer,len);
        return 1;
    }
#endif
     
    iCmd=(iDeviceAddr<<8)|((iAddr<<1)&0x0e00)|(iAddr&0xff);
    
    if (WaitIopFunRdy(IOP_RDY_WAIT)<0)
        return -1;
    
    //pro-clear error flag
    regs0->iop_data[0]&=(~I2C_RW_ERR);
    
    //setting parameter
    regs0->iop_data[I2C_CTRL_ADDR]=iCmd;
    
    // select one-time or continuous function
    if (len==1)
        regs0->iop_data[0]=FUN_I2C_READ|I2C_READ_ONE;
    else
        regs0->iop_data[0]=FUN_I2C_READ|I2C_READ_CONT;  
    
    
    //wait function rdy
    while(len)
    {
        
        for (iWait=IOP_RDY_WAIT;iWait>=0 && !(regs0->iop_data[0]&I2C_RD_RDY);iWait--)
        {
            if (regs0->iop_data[0]&I2C_RW_ERR)
                return -1;
        }
        
        if (iWait<0)
            return -1;
        
        
        *bBuffer++=(BYTE)(regs0->iop_data[I2C_DATA]&0xff);
        len--;
        
        
        if (len==1)
            //read the last data
            regs0->iop_data[0]&=((~I2C_READ_CONT)&(~I2C_RD_RDY));
        else
            //clear flag
                
            regs0->iop_data[0]&=(~I2C_RD_RDY);
                
    }

    return 1;
}
#endif//defined(DVI_I2C_SET)&&defined(SPHE8202)


#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)  || defined(SUPPORT_GAMEPAD_MOUSE) || defined(SUPPORT_SMF)
/**************************************************************************
 *  Function Name:int ReadGamePad(void)                                   *
 *  Purposes:                                                             *
 *              Send read game pad data cmd and return ready flag.        *
 *  Descriptions:                                                         *
 *              (None)                                                    *                              
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              return -1:  read error                                    *
 *              return  1:  read success                                  *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/
int ReadGamePad(void)
{
    if (regs0->iop_data[0]&FUN_MASK)
        return -1;
    
    //read game pad
    regs0->iop_data[0]=(regs0->iop_data[0]&VFD_DATLEN_MASK)|FUN_GPAD_READ;
    
    //wait read end
    while(regs0->iop_data[0]&FUN_MASK);
    
    //if (regs0->iop_data[4] != 0xffff)
    //printf("game pad= %04x\n",regs0->iop_data[4]);
    return 1;
}

#endif

#ifdef SOFT_UART_OUT 
/**************************************************************************
 *  Function Name:int PutSoftUartChar(BYTE *buf,int len)                  *
 *  Purposes:                                                             *
 *              Send data to software UART port                           *
 *  Descriptions:                                                         *
 *              *buf        = the input data stream.                      *
 *              len         = how many byte to send.                      *                              
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              Return the value that is write byte number                 * 
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/

int PutSoftUartChar(BYTE *buf,int len)
{
    
#if 1   
    /*
        The block program is send data to  UART buffer by IOP function call 
        , that's good. 
    */

    int     j;
    
    if (!bResetIop)
        return 0;
    
    for (j=0;j<len;j++)
    {   
        
        if (WaitIopFunRdy(IOP_RDY_WAIT)<0)
            break;      
           
        regs0->iop_data[VFD_CMD]=*buf;          
        regs0->iop_data[0]=(regs0->iop_data[0]&VFD_DATLEN_MASK)|FUN_UART_SEND;          
        buf++;
    }
    
    return j;

#else
    /*
        The block program is direct access UART buffer on iop area, but 
        I find few time the char will send again, strange?
    */
    static BYTE i=0;    
    int     iWait,j;
    UINT32  unAddr;
    BYTE    *TxdTail;   //read
    BYTE    *TxdHead;   //write
    BYTE    *TxDBuffer; //buffer
    
    if (!bResetIop)
        return 0;
    
    unAddr=SDRAM_BASE_UNCACHED+MEM_IOPYA*1024;
    TxdTail=(BYTE*)(unAddr+0x590);
    TxdHead=(BYTE*)(unAddr+0x591);
    TxDBuffer=(BYTE*)(unAddr+0x592);
    
    //i=*TxdHead;
    
    for (j=0;j<len;j++)
    {       
        iWait=IOP_RDY_WAIT;         
        while ((iWait--) && (i+1)==*TxdTail);   
        if (iWait==0)
            break;      
                
        TxDBuffer[i++]=*buf;
        *TxdHead=i;     
        MIPS_flush_LBC_cache();
        buf++;
    }   
    return j;   
    
#endif
    
}
/**************************************************************************
 *  Function Name: int GetSoftUartChar(BYTE *buf,int len)                 *
 *  Purposes:                                                             *
 *              read data to software UART port                           *
 *  Descriptions:                                                         *
 *              Input :                                                   *
 *              *buf        = save data buffer                            *
 *              len         = Max read byte number.                       *
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              Return the value that is read byte number                 *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/
int GetSoftUartChar(BYTE *buf,int len)
{
    static BYTE i=0;        
    int     j;      
    UINT32  unAddr;
    BYTE    *RxdTail;   //read
    BYTE    *RxdHead;   //write
    BYTE    *RxDBuffer; 
    
    if (!bResetIop)
        return 0;
    
    unAddr=SDRAM_BASE_UNCACHED+MEM_IOPYA*1024;
    RxdTail=(BYTE*)(unAddr+0x692);
    RxdHead=(BYTE*)(unAddr+0x693);
    RxDBuffer=(BYTE*)(unAddr+0x694);
    
    //i=*RxdTail;   
    for (j=0;j<len;j++)
    {       
        if (i==*RxdHead)
            break;
            
        *buf=RxDBuffer[i];
        *RxdTail=i++;       
        buf++;
    }   
    return j;
}

#endif

#if 0
void HexDump(BYTE *cpBuffer,int len)
{
    int iAddr,iData;
    int iDelay;
    
    for (iAddr=0;iAddr<len;iAddr+=16)
    {
        psprintf(linebuf, "%08x - ",iAddr);
        printf(linebuf);
        
        for (iData=0;iData<16;iData+=1)
        {
            if( (iAddr+iData)<len )
            {
                psprintf(linebuf, "%02x,",cpBuffer[iAddr+iData]);
                printf(linebuf);
            }
            else
                break;
        }
        printf("\n");
        
        for(iDelay=0;iDelay<0xfffff;iDelay++);
    }
    
}

#endif

//for switching IOP code
//added by JSLin    //20041022
#if defined(SUPPORT_PS2) && !defined(SUPPORT_GAMEPAD_MOUSE) && !defined (SUPPORT_USB_HID)  //liulifeng  for usb mouse  20050920

extern UINT16 modual_loaded;

#define IOP_NORMAL  0x0
#define IOP_PS2         0x1
/**************************************************************************
 *  Function Name: void Switch_IOP(BYTE TYPE, UINT8 * ptr, int len)       *
 *  Purposes:                                                             *
 *              Swap high and low byte for a word data.                   *
 *  Descriptions:                                                         *
 *              Input :                                                   *
 *              TYPE        = IOP_NORMAL / IOP_PS2                        *
 *              * ptr       = the address point of iop binary code        *
 *              len         = the length of iop binary code               *
 *  Arguments:                                                            *
 *              (None)                                                    *
 *  Returns:                                                              *
 *              (None)                                                    *
 *  See also:                                                             *
 *              (None)                                                    *
 **************************************************************************/
void Switch_IOP(BYTE TYPE, UINT8 * ptr, int len)
{
    int i;
    UINT32 *p, *q;

    switch(TYPE)
    {
        case IOP_NORMAL:
            printf("\n\n\n              IOP_NORMAL\n\n");
            bSleepFlag = 0;
            modual_loaded &= (~(1<<MODUAL_IOP));
            reset_iop();
            break;
        case IOP_PS2:
            printf("\n\n            IOP_PS2 \n");
            
            IOP_RESET();

            // download binary
            p = (UINT32 *) ptr;
            q = (UINT32 *) (SDRAM_BASE + MEM_IOPYA * 1024);
            len = (len+3) & ~0x03;
            for (i=0; i<len/4; i++) *q++ = *p++;

            MIPS_flush_LBC_cache();

            delay_1ms(20);
            IOP_GO();
            break;

    }

}
#endif





