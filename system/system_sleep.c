#if defined(SUPPORT_8202_DVB)&&defined(USE_DEMUX_GPIO_WHEN_STANDBY)
extern void Demux6600HwInit(void);
#endif

static inline void sleep_when_power_on(void)
{
#ifdef SLEEP_WHEN_POWER_ON
#ifdef HJ_8202_8408
   static BYTE   flag=0,fag=0,i=0;    
#endif//#ifdef HJ_8202_8408
    //volatile int *iMagic=(int *)(DATA_RAM_BASE|0x80);
    volatile int *iMagic=(int *)(DATA_RAM_BASE|0x90); //Jeff 20040312
 #ifdef HJ_8202_8408
    for(i=0;i<100;i++)
    {
        flag=(BYTE)((regs0->iop_data[5]&0xff00)>>8);
        if(flag&0x10) 
        {
            regs0->iop_data[5]&=~0x1000;
            fag=1;     
        }
    }
#endif
    //printf("iMagic=%08x\n", *iMagic);
    if ((*iMagic != 0x1234abcd)
    #ifdef HJ_8202_8408
    &&(fag==1)
    #endif
    )
    {
#ifdef HJ_8202_8408
        fag=0;
#endif//#ifdef HJ_8202_8408
        #ifdef TCL_STANDBY
            #ifdef YADAI_PT6554_PANNEL
        		        regs0->gpio_master[4 / 16] |= (0x1 << (4 % 16));
				regs0->gpio_oe[ 4/16 ] |= 0x1 << (4%16);//output
				regs0->gpio_out[4/16 ] |= (0x1 << (4%16));
	    #endif
            ircmd_power();//2004-3-22 13:38 lijd
          
        #else
            //#if defined(POWER_RESUME)&&defined(SLEEP_WHEN_POWER_ON)
            #ifdef SLEEP_WHEN_POWER_ON //Jeff 20040312
            //hq marked,because of no method to wake up the DVD system. 3-11-25 22:34
            //sleep_when_power_on();
            //#else
            #if defined(SUPPORT_8202_DVB)&&defined(USE_DEMUX_GPIO_WHEN_STANDBY)
            Demux6600HwInit();
            #endif
            ircmd_power();
            #endif  
        #endif
    }
#ifdef PULIANG_DVD  //yaowh add 04-12-17
    regs0->gpio_master[35 / 16] |= (0x1 << (35 % 16));	
	GPIO_E_SET(35,1);
    GPIO_O_SET(35,1);
#endif
    
    *iMagic = 0;

    //yanlb move here from sysmain.c; 04/05/12 PM 2:00
#ifdef POWER_ON_VIDEO_DAC_OFF//nono 2004-7-7 18:12
    delay_1ms(1000);
#endif//POWER_ON_VIDEO_DAC_OFF

    tv_dacoff(0);                   // dac f/e/d/c/b/a on    
    ShowTitle();
#endif        
}
    
    
