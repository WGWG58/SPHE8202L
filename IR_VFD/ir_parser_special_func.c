//nono split from ir_parser.c 5-5-9 15:07
/*
**  freyman 2002-7-30 13:24
**  Des: Rotary encoder utility.
**  
*/
#ifdef ROTARY_VOLUME

#define RV_IDLE         1
#define RV_CWBEGIN      2
#define RV_CWEND        3
#define RV_CCWBEGIN     4
#define RV_CCWEND       5
#define RV_HIGH         1
#define RV_LOW          0

#if 0//def  ROTARY_VOL_HUAJIA600    //wangfeng 2003-09-22 20:31

#define RV_WAIT_HIGH    0
#define RV_WAIT_LOW 6

void polling_rotary(void)
{
    BYTE pin_a=RV_LOW, pin_b=RV_LOW;
    static BYTE rotary_state = RV_WAIT_HIGH;
    static BYTE old_pin_a=RV_LOW,old_pin_b=RV_LOW;
    static BYTE _j;
    extern void set_volume(BYTE);
    extern void ampvol_rotary(BYTE direction);

    regs0->sft_cfg6 &= ~(0x1 << 6);
    regs0->sft_cfg6 &= ~(0x1 << 4);
    regs0->gpio_master[14/16] |= (0x3 << (14%16));
    regs0->gpio_oe[14/16] &= (~0x3 << (14%16) );
    pin_a = ((regs0->gpio_in[14/16] >> (14%16)) & 0x01);
    pin_b = ((regs0->gpio_in[15/16] >> (15%16)) & 0x01);

    if((old_pin_a!=pin_a)||(old_pin_b!=pin_b))
    {
        old_pin_a=pin_a;
        old_pin_b=pin_b;
        _j=0;
        return;
    }
    
    //if(_j++<1)    return;
    if( (pin_a==RV_HIGH)&&(pin_b==RV_HIGH) )        
    {
        rotary_state = RV_WAIT_HIGH;
        return;
        
    }
    else if( (pin_a==RV_LOW)&&(pin_b==RV_LOW) )
    {
        rotary_state = RV_WAIT_LOW;
        return;
        
    }
    else if((pin_a==RV_HIGH)&&(pin_b==RV_LOW))  
    {
        if(rotary_state==RV_WAIT_HIGH)
        {
            rotary_state = RV_CCWBEGIN;//RV_CCWEND;  
        }
        else if(rotary_state==RV_WAIT_LOW)
        {
            rotary_state = RV_CWBEGIN;//RV_CWEND;
        }
        
        else if(rotary_state==RV_CCWBEGIN)
        {
            rotary_state = RV_CCWEND;
        }
        else if(rotary_state==RV_CWBEGIN)
        {
            rotary_state = RV_CWEND;
        }
    }

    if(rotary_state==RV_CWEND)
    {
        ircmd_volume_up();
        //rotary_state==RV_WAIT_HIGH;
        
    }
    else if(rotary_state==RV_CCWEND)
    {
        ircmd_volume_down();
        //rotary_state==RV_WAIT_HIGH;
        
    }
}               

#elif 1//0//for hj-1250/hj-1251 rotary volume

#define RV_WAIT         0

void polling_rotary(void)
{
    BYTE pin_a=RV_LOW, pin_b=RV_LOW;
    static BYTE rotary_state = RV_WAIT;
    static BYTE old_pin_a=RV_LOW,old_pin_b=RV_LOW;
    static BYTE _j;
    extern void set_volume(BYTE);
    extern void ampvol_rotary(BYTE direction);
/*
    regs0->sft_cfg6 &= ~(0x1 << 6);
    regs0->sft_cfg6 &= ~(0x1 << 4);
    regs0->gpio_master[14/16] |= (0x3 << (14%16));
    regs0->gpio_oe[14/16] &= (~0x3 << (14%16) );
*/ 
#ifdef HJ_8202_8408
    pin_a = ((17/16] >> (17%16)) & 0x01);
    pin_b = ((regs0->gpio_in[16/16] >> (16%16)) & 0x01);
#else
    pin_a = ((regs0->gpio_in[15/16] >> (15%16)) & 0x01);
    pin_b = ((regs0->gpio_in[16/16] >> (16%16)) & 0x01);
#endif
    if((old_pin_a!=pin_a)||(old_pin_b!=pin_b))
    {
        old_pin_a=pin_a;
        old_pin_b=pin_b;
        _j=0;
        return;
    }

    if(_j++<6)  return;
    if( (pin_a==RV_HIGH)&&(pin_b==RV_HIGH) )        
    {
        rotary_state = RV_WAIT;
        return;
        
    }
    else if( (pin_a==RV_LOW)&&(pin_b==RV_LOW) )
    {
        if(rotary_state==RV_CWBEGIN)
        {
            rotary_state = RV_CWEND;
        }
        else if(rotary_state==RV_CCWBEGIN)
        {
            rotary_state = RV_CCWEND;
        }
        
    }
    else if((pin_a==RV_HIGH)&&(pin_b==RV_LOW))  
    {
        if(rotary_state==RV_WAIT)
        {
            rotary_state = RV_CCWBEGIN;//RV_CCWEND;  
        }
    }
    else if((pin_a==RV_LOW)&&(pin_b==RV_HIGH))  
    {
        if(rotary_state==RV_WAIT)
        {
            rotary_state = RV_CWBEGIN;//RV_CWEND;
        }
                
    }

    if(rotary_state==RV_CWEND)
    {
        RotaryStateChk();
        #ifdef ROTARY_SWITCH_1251
        //ircmd_volume_down();//1251    //fengjl mark it  2004-03-03 16:21 to cancel screen saver by rotate volume
        call_ir_func(IRC_VOLUME_DN);  
        #else
        //ircmd_volume_up();
        call_ir_func(IRC_VOLUME_UP);
        #endif
        rotary_state = RV_WAIT;
        
    }
    else if(rotary_state==RV_CCWEND)
    {
        RotaryStateChk();
        #ifdef ROTARY_SWITCH_1251
        //ircmd_volume_up();
        call_ir_func(IRC_VOLUME_UP);        
        #else
        //ircmd_volume_down();
        call_ir_func(IRC_VOLUME_DN);        
        #endif
        rotary_state = RV_WAIT;
    }
} 
//wangfeng add 2003-12-29
#elif 0//for hj-3000 rotary volume
#define RV_WAIT         0
#define R_WAIT          6
#define L_WAIT          7
#define RV_R            8
#define RV_L            9
void polling_rotary(void)
{
    BYTE pin_a=RV_LOW, pin_b=RV_LOW;
    static BYTE rotary_state = RV_WAIT;
    static BYTE old_pin_a=RV_LOW,old_pin_b=RV_LOW;
    //static BYTE old_pin_a=RV_HIGH,old_pin_b=RV_HIGH;
    static BYTE _j;
    extern void set_volume(BYTE);
    extern void ampvol_rotary(BYTE direction);
 
    pin_a = ((regs0->gpio_in[14/16] >> (14%16)) & 0x01);
    pin_b = ((regs0->gpio_in[15/16] >> (15%16)) & 0x01);


    if((old_pin_a!=pin_a)||(old_pin_b!=pin_b))
    {
        old_pin_a=pin_a;
        old_pin_b=pin_b;
        _j=0;
        return;
    }

    if(_j++<8)  return;

    if( (pin_a==RV_HIGH)&&(pin_b==RV_HIGH) )        
    {
        if(rotary_state==RV_CWEND)
            rotary_state=RV_R;
        else
                rotary_state = R_WAIT;

        //return;
        
    }
    else if((pin_a==RV_HIGH)&&(pin_b==RV_LOW))
    {
        if(rotary_state==RV_CCWEND)
            rotary_state=RV_L;
        else if(rotary_state==RV_CWEND)
            rotary_state=RV_R;
        else
                rotary_state = L_WAIT;

        //return;
        
    }
    else if( (pin_a==RV_LOW)&&(pin_b==RV_LOW) )
    {
        if(rotary_state==L_WAIT)
        {
            rotary_state = RV_CCWEND;
        }
        else if(rotary_state==RV_CWBEGIN)
        {
            rotary_state = RV_CWEND;
        }
        
    }
    else if((pin_a==RV_LOW)&&(pin_b==RV_HIGH))  
    {
        if(rotary_state==R_WAIT)
        {
            rotary_state = RV_CWBEGIN;//RV_CCWEND;  
        }
        else if(rotary_state==RV_CCWBEGIN)
        {
            rotary_state = RV_CCWEND;
        }
    }
    

    if(rotary_state==RV_R)
    {
        RotaryStateChk();
        #ifdef ROTARY_SWITCH_1251
        ircmd_volume_down();//1251
        #else
        ircmd_volume_up();
        #endif
        rotary_state = RV_WAIT;
        
    }
    else if(rotary_state==RV_L)
    {
        RotaryStateChk();
        #ifdef ROTARY_SWITCH_1251
        ircmd_volume_up();
        #else
        ircmd_volume_down();
        #endif
        rotary_state = RV_WAIT;
    }
} 
#else//ROTARY_VOL_HUAJIA600

#define RV_WAIT         0

void polling_rotary(void)
{
    BYTE pin_a=RV_LOW, pin_b=RV_LOW;
    static BYTE rotary_state = RV_WAIT;
    extern void set_volume(BYTE);
    extern void ampvol_rotary(BYTE direction);

    pin_a = ((regs0->gpio_in[4/16] >> (4%16)) & 0x01);
    pin_b = ((regs0->gpio_in[5/16] >> (5%16)) & 0x01);

    if( (pin_a==RV_HIGH)&&(pin_b==RV_HIGH) )        
    {
        rotary_state = RV_WAIT;
        return;
    }
    else if( (pin_a==RV_LOW)&&(pin_b==RV_LOW) )
    {
        rotary_state = RV_IDLE;
        return;
    }
    else if( (pin_a==RV_LOW)&&(pin_b==RV_HIGH) )
    {
        if(rotary_state==RV_WAIT)
        {
            rotary_state = RV_CWBEGIN;  
        }
        else if( (rotary_state==RV_IDLE)||(rotary_state==RV_CCWBEGIN) )
        {
            rotary_state = RV_CCWEND;
        }
        else
        {
            rotary_state = RV_WAIT;
        }
    }
    else if( (pin_a==RV_HIGH)&&(pin_b==RV_LOW) )
    {
        if(rotary_state==RV_WAIT)
        {
            rotary_state = RV_CCWBEGIN;
        }
        else if( (rotary_state==RV_IDLE)||(rotary_state==RV_CWBEGIN) )
        {
            rotary_state = RV_CWEND;
        }
        else
        {
            rotary_state = RV_WAIT;
        }
    }
    
    if(rotary_state==RV_CWEND)
    {
/* freyman marked 2004-3-23 15:39 for no use any more
        #ifdef SVA_SAMPLE
        if(full_scrn==AMPVOL)
            ampvol_func_right();
        else
        set_volume(1);
        #else
*/
        #if defined(SUPPORT_TUNER)
        ircmd_power_volume(IRC_VOLUME_UP);
        #else
        ircmd_volume_up();
        #endif//SUPPORT_TUNER AV_INPUT
//        #endif
    }
    else if(rotary_state==RV_CCWEND)
    {
/* freyman marked 2004-3-23 15:37 for no use any more
        #ifdef SVA_SAMPLE
        if(full_scrn==AMPVOL)
            ampvol_func_left();
        else
        set_volume(0);
        #else
*/
        #if defined(SUPPORT_TUNER)
        ircmd_power_volume(IRC_VOLUME_DN);
        #else
        ircmd_volume_down();
        #endif
//        #endif
    }
}                   

#endif//ROTARY_VOL_HUAJIA600

//shut off certain full_scrn when rotary vol is on, wangfeng 2004-2-4 17:02
void RotaryStateChk(void)
{
        if(full_scrn)
            {
                if (full_scrn & PROGRAM)  //add by shawn 20020218
                {
                    #ifdef SDRAM_16Mb_Mode                  
                        prog_state=3;   // 3 means that ircmd_stop pressed when full_scrn==PROGRAM
 
                    #endif//SDRAM_16Mb_Mode 

                    #ifdef JIEKE_DVD
                    prog_cnt = 0;
                    #endif
                    prog_func_off();

                }
                else if (full_scrn & SOUND)  //add by wangfeng 2004-2-4 17:00
                {
                    cancel_sound();
                }
                else if (full_scrn & SETUP)  //add by wangfeng 2004-2-5 14:41
                {
                    ExitSetupPage(1);
                }
#ifdef  CF_CARD_WRITE
        if(!(full_scrn & PERIPHERAL))       //wuxiaofeng if define card, use preview for IR input
#endif
                //wanghaoying changed 2003-12-9 14:21
                full_scrn = 0;            
                #ifdef SOUND_NO_KEYPAGE                
                bEqDisplay = 0;  
                #endif
                //display_again=1;
            } //if(full_scrn)
}
#endif//ROTARY_VOLUME

