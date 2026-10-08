
#ifdef ALCO_PVS177W
//#include "tvif.h"
#endif

#if defined(TFT_ONOFF_CONTROL)
#if defined(ALCO_PV1950)||defined(ALCO_PVS19251)
#define IS_VIDEO_INPUT()  (GPIO_I_GET(INT_EXT_VIDEO_GPIO1)+GPIO_I_GET(INT_EXT_VIDEO_GPIO2))
#elif defined(ALCO_PVS177W)||defined(ALCO_PVS1090_AVIN)//shenyj add for alco177w
#define IS_VIDEO_INPUT()  (GPIO_I_GET(INT_EXT_VIDEO_GPIO))
#endif
#endif

#ifdef DISPLAY_REMAIN_TIME
extern int display_and_time;
extern BYTE display_flag;
#endif
#ifdef ALCO_PORTABLE
extern void ForceClearOsdMsg();
#endif
#define DELAY_COUNT     25
#define TRAYIN_START1   50  //added 04/12/31
#define TRAYIN_START2   75

#ifdef BAT_DETECT    //shenyj add 050222
#ifdef FW_DELAY_LONG

#define FULL_BAT_LOW_DELAY_CNT      90000//90000*10ms==900s/60=15min
#define FULL_BAT_LOW_DELAY_LIMIT    120000  
#define LOW_BAT_LOW_DELAY_CNT       24000
#define LOW_BAT_LOW_DELAY_LIMIT     42000  
#define POWER_ON_BAT_LOW_LIMIT      6000
#define POWER_ON_DETECT_TIMER       8000

void check_alco_bat_detect_gpio(void)
{
    static int power_on_detect_timer=POWER_ON_DETECT_TIMER;
    static int power_on_bat_low_times=0;
    static int delay_cnt;
    static int delay_limit;
    
    if(power_on_detect_timer)
        power_on_detect_timer--;
    
    #ifdef HIGH_BAT_LOW
    if(!GPIO_I_GET(BAT_LOW_GPIO))
    #else
    if(GPIO_I_GET(BAT_LOW_GPIO))
    #endif
    {	   
        if(lowbat_timer)
		ClearOsdMsg(1);
		    
    	lowbat_timer = 0;
    	
    	#ifdef BAT_LOW_LED_CONTROL 
    	    #ifdef ALCO_PVS1090
    	    regs0->sdc_data_cnt[6][0] |= (0x0e);//enable gpio 72
	        GPIO_M_SET(BAT_LOW_LED_GPIO,1); 
	        GPIO_E_SET(BAT_LOW_LED_GPIO,1);  //output
	    #endif
	    GPIO_O_SET(BAT_LOW_LED_GPIO,0);
	    #endif
	    
	    power_on_bat_low_times = 0;
    }
    else
    {      
    	if(power_on_detect_timer)
    	    power_on_bat_low_times++;
    	
    	if(power_on_detect_timer==1)    
    	{
    	    if(power_on_bat_low_times >= POWER_ON_BAT_LOW_LIMIT)
    	    {
    	        delay_cnt = LOW_BAT_LOW_DELAY_CNT;
    	        delay_limit = LOW_BAT_LOW_DELAY_LIMIT;
        }	
    	else
    	{   		
    	        delay_cnt = FULL_BAT_LOW_DELAY_CNT;
    	        delay_limit = FULL_BAT_LOW_DELAY_LIMIT;
    	    }
        }
    
    	if(!power_on_detect_timer)
    	{
    	    #ifdef WHEN_BAT_LOW_POWER_OFF
    	    if(lowbat_timer<delay_limit)
    	    #endif
    	    {
    	        if(lowbat_timer>delay_cnt)
    	{
    	    int flag;
    	    flag=lowbat_timer/70;
    		if(flag%3!=1)
    		{
    		    PrintOsdMsg(STR_OS_LOWBAT,REGION1,0,0);
    		#ifdef BAT_LOW_LED_CONTROL 
    		#ifdef ALCO_PVS1090
    		regs0->sdc_data_cnt[6][0] |= (0x0e);//enable gpio 72
	        GPIO_M_SET(BAT_LOW_LED_GPIO,1); 
	        GPIO_E_SET(BAT_LOW_LED_GPIO,1);  //output
	        #endif
	        GPIO_O_SET(BAT_LOW_LED_GPIO,1);
	        #endif
        }	
    	else
    	{   		
    	        ClearOsdMsg(1); 
    	        #ifdef BAT_LOW_LED_CONTROL 
    	        #ifdef ALCO_PVS1090
    	        regs0->sdc_data_cnt[6][0] |= (0x0e);//enable gpio 72
	            GPIO_M_SET(BAT_LOW_LED_GPIO,1); 
	            GPIO_E_SET(BAT_LOW_LED_GPIO,1);  //output
	            #endif
	            GPIO_O_SET(BAT_LOW_LED_GPIO,0);
	            #endif
    	    }
    	        }   
    		lowbat_timer++;
        }	
    	    #ifdef WHEN_BAT_LOW_POWER_OFF
    	else
    	{   		
           ircmd_power();	
    	}	
#endif
        }
    }
}

#elif defined(ALCO_PVS1090)||defined(ALCO_PVS1090_AVIN)    //shenyj add 
void check_alco_bat_detect_gpio(void)
{
    if(GPIO_I_GET(BAT_LOW_GPIO))
    {	   
        if(lowbat_timer)
		ClearOsdMsg(1);
    	lowbat_timer = 0;
    	#ifdef BAT_LOW_LED_CONTROL 
    	    #ifdef ALCO_PVS1090
    	    regs0->sdc_data_cnt[6][0] |= (0x0e);//enable gpio 72
	        GPIO_M_SET(BAT_LOW_LED_GPIO,1); 
	        GPIO_E_SET(BAT_LOW_LED_GPIO,1);  //output
	        #endif
	        GPIO_O_SET(BAT_LOW_LED_GPIO,0);
	    #endif
    }
    else
    {      
        #ifdef BAT_LOW_LED_CONTROL 
    	    #ifdef ALCO_PVS1090
    	    regs0->sdc_data_cnt[6][0] |= (0x0e);//enable gpio 72
	        GPIO_M_SET(BAT_LOW_LED_GPIO,1); 
	        GPIO_E_SET(BAT_LOW_LED_GPIO,1);  //output
	        #endif
	        GPIO_O_SET(BAT_LOW_LED_GPIO,1);
	    #endif
    	if(lowbat_timer<6000)
    	{
    	    int flag;
    	    flag=lowbat_timer/70;
    		if(flag%3!=1)
    		{
    		    PrintOsdMsg(STR_OS_LOWBAT,REGION1,0,0);
    	    }
    	    else
    	    {
    	        ClearOsdMsg(1); 
    	    }
    		lowbat_timer++;
        }	
    	else
    	{   	
	        #ifdef WHEN_BAT_LOW_POWER_OFF 
           ircmd_power();	
            #endif
    	}	
    }
}

#else //#ifdef FW_DELAY_LONG

#define GPIO_LOW_DELAY_CNT          1000
#ifdef WHEN_BAT_LOW_POWER_OFF
#define POWER_OFF_LIMIT             18000
#endif
#define DETECT_PERIOD               300               

void check_alco_bat_detect_gpio(void)
{
    static UINT16 detect_times=DETECT_PERIOD;
    static BYTE power_on_delay_timer = 0;
    
    if(detect_times>1)
        detect_times--;
        
    #ifdef HIGH_BAT_LOW
    if(!GPIO_I_GET(BAT_LOW_GPIO))
    #else
    if(GPIO_I_GET(BAT_LOW_GPIO))
    #endif
    	highbat_timer++;
    else
        lowbat_timer++;
    
    if(detect_times==1)
    {
    	if((lowbat_timer>highbat_timer) && (power_on_delay_timer>=5))
    	    PrintOsdMsg(STR_OS_LOWBAT,REGION1,1,0);
        
        lowbat_timer = 0;
        highbat_timer = 0;  
        
        if(power_on_delay_timer<5)
            power_on_delay_timer++;
          
        detect_times = DETECT_PERIOD;
    }    
}
#endif  //end #ifdef FW_DELAY_LONG
#endif  //end #ifdef BAT_DETECT

//end shenyj add 050222
void check_alco_portable_gpio(void)
{
	UINT16 temp=0;
	static BYTE i=0;
	
	#ifdef IO_CHECK_GET_DELAY
	UINT16 delay_cnt;//shenyj add for alco177w
	#endif
	
	#ifdef PLAY_IN_SUNPLUS_PLATFORM
	return;
	#endif
	
	#ifdef TFT_ONOFF_CONTROL
	#if defined(ALCO_PV1950)||defined(ALCO_PVS19251)
	GPIO_O_SET(TFT_CONTROL_GPIO1,1);
	GPIO_O_SET(TFT_CONTROL_GPIO2,1);
    #elif defined(ALCO_PVS177W)//shenyj add for alco177w
	regs0->sft_cfg3 &= ~((0x1)<<3); //enable gpio55 for TFT_CHECK
    regs0->sft_cfg0&= ~((0x1)<<6); //enable gpio29 for TFT_CTL	
	
	GPIO_M_SET(TFT_CHECK_GPIO,1); 
	GPIO_E_SET(TFT_CHECK_GPIO,0);  //input	
	GPIO_M_SET(TFT_CONTROL_GPIO,1); 
	GPIO_E_SET(TFT_CONTROL_GPIO,1);  //output
	
	#ifdef IO_CHECK_GET_DELAY
	for(delay_cnt=0;delay_cnt<20;delay_cnt++)
	    ;
	#endif
	
	//printf_w("shenyj test here tft_flay=%d\n",tft_flag);
	if(GPIO_I_GET(TFT_CHECK_GPIO))
	{
	    GPIO_O_SET(TFT_CONTROL_GPIO,1);	
    }
    else
    {
        GPIO_O_SET(TFT_CONTROL_GPIO,0);	
    }
    #elif defined(ALCO_PVS127X)||defined(ALCO_PVS1262)||defined(ALCO_PVS8712)||defined(ALCO_PVS1090)
	    #if !defined(ALCO_PVS1090)&&!defined(ALCO_CARD_USB_MODEL)
	regs0->sft_cfg1&= ~((0x1)<<3); //enable gpio16 for TFT_STB_CTL
	    #endif
	    #if !defined(ALCO_PVS1262)&&!defined(ALCO_PVS8712)&&!defined(ALCO_PVS1090)&&!defined(ALCO_PVS1090_AVIN)
	regs0->sft_cfg3 &= ~((0x1)<<3); //enable gpio55 for TFT_CHECK
	#endif
	#ifdef ALCO_PVS1090
	regs0->sft_cfg3&= ~((0x1)<<1); //enable gpio53 for TFT_CHECK
	regs0->sft_cfg3 &= ~((0x1)<<0); //enable gpio58 for TFT_ON_OFF
	regs0->sft_cfg3 &= ~((0x1)<<9); //enable gpio59 for TFT_POWER_STB
	#endif
	#ifdef ALCO_CARD_USB_MODEL
	    regs0->sft_cfg3&= ~((0x1)<<1); //enable gpio53 for TFT_CHECK
	    regs0->sft_cfg3 &= ~((0x1)<<0); //enable gpio58 for TFT_ON_OFF
	    #ifdef ALCO_PVS1090_AVIN
	    #if !defined(ARCHT16_USE_64M_ESP)//shenyj add for alco 2006/02/28
	    regs0->sft_cfg1 &= ~((0x1)<<4); //enable gpio25 pin111 for TFT_POWER_STB
	    #endif
	    #else
	    regs0->sft_cfg3 &= ~((0x1)<<9); //enable for TFT_POWER_STB
	#endif
	    #endif
	GPIO_M_SET(TFT_CHECK_GPIO,1); 
	GPIO_E_SET(TFT_CHECK_GPIO,0);  //input	
	GPIO_M_SET(TFT_CONTROL_GPIO,1); 
	GPIO_E_SET(TFT_CONTROL_GPIO,1);  //output		
	GPIO_M_SET(TFT_STB_CONTROL_GPIO,1); 
	GPIO_E_SET(TFT_STB_CONTROL_GPIO,1);  //output
	
	#ifdef IO_CHECK_GET_DELAY
	for(delay_cnt=0;delay_cnt<20;delay_cnt++)
	    ;
	#endif
	if(GPIO_I_GET(TFT_CHECK_GPIO))
	{
	    #ifdef POWER_ON_LCD_BACKGROUND_VOlTAGE_DELAY
	    if(i > BACKGROUND_VOlTAGE_DELAY_VALUE)//added 07/05/26
	    #endif
	    GPIO_O_SET(TFT_CONTROL_GPIO,1);	
	    #if defined(ALCO_PVS1262)||defined(ALCO_PVS8712)||defined(ALCO_PVS1090)||defined(ALCO_PVS1090_AVIN)
	    GPIO_O_SET(TFT_STB_CONTROL_GPIO,1);
	    #else
	    GPIO_O_SET(TFT_STB_CONTROL_GPIO,0);
	    #endif
    }
    else
    {
        GPIO_O_SET(TFT_CONTROL_GPIO,0);	
        #if defined(ALCO_PVS1262)||defined(ALCO_PVS8712)||defined(ALCO_PVS1090)||defined(ALCO_PVS1090_AVIN)		
	    GPIO_O_SET(TFT_STB_CONTROL_GPIO,0);
	    #else
        GPIO_O_SET(TFT_STB_CONTROL_GPIO,1);
        #endif
    }
	#endif//end shenyj add for alco177w
	#endif
	
    #ifdef VIDEO_IN_CONTROL   
    #if defined(ALCO_PV1950)||defined(ALCO_PVS19251)  
    INT_EXT_GPIO_INIT1();
    INT_EXT_GPIO_INIT2();
   
    #ifdef IO_CHECK_GET_DELAY//Jack modified delay_cnt from 50 to 100 on 05/04/01
	for(delay_cnt=0;delay_cnt<100;delay_cnt++)
	    ;
	#endif  
	
    switch (IS_VIDEO_INPUT())
    {
    case 2: //two video-in sw are not in video in state 
        //printf_w("do nothing............\n");

        //do nothing!
        break;        
    case 1://8210 input video to TFT
        //one video-in sw is in video in state
        if(system_state!=SYSTEM_BROWSE)
           GPIO_DEMUTE();

        //printf_w("one AV in............\n");

        break;
    case 0://External AV input to TFT
        if(i > (DELAY_COUNT-1))
        {
            //printf_w("towo an in............\n");

        AVin_step = 0x0f;
        call_ir_func(IRC_POWER);
        }
        break;
    }
    #elif defined(ALCO_PVS177W)||defined(ALCO_PVS1090_AVIN)//shenyj add for alco177w       
    INT_EXT_GPIO_INIT();
    #ifdef IO_CHECK_GET_DELAY//Jack modified delay_cnt from 50 to 100 on 05/04/01
	for(delay_cnt=0;delay_cnt<100;delay_cnt++)
	    ;
	#endif     
    
    switch (IS_VIDEO_INPUT())
    {
        
    case 1://8202s input video to TFT        
        //if(system_state!=SYSTEM_BROWSE)
        //   GPIO_DEMUTE();
        break;
    case 0://External AV input to TFT       
        if(i > (DELAY_COUNT-1))
        {
        //tv_dacoff((1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0));
        AVin_step = 0x0f;        
        call_ir_func(IRC_POWER);
        }
        break;
    default:
        break;
    }
    #endif 

    if(!AVin_step)
    {
    #endif //end #ifdef VIDEO_IN_CONTROL
        #ifdef CHECK_PORTABLE_OPCLSW
         #ifdef PORTABLE_8202D
         regs0->sft_cfg4&= ~((0x1)<<6);//added 05/08/23     
         #endif
         GPIO_M_SET(PDVD_OPCLSW_GPIO,1);
	     GPIO_E_SET(PDVD_OPCLSW_GPIO,0); //input
	    //Cover SW(GPIO8)
        
        #ifdef IO_CHECK_GET_DELAY
	    for(delay_cnt=0;delay_cnt<20;delay_cnt++)
	        ;
	    #endif
	     
	    #if defined(PORTABLE_8202S)||defined(PORTABLE_8202D)
        temp=GPIO_I_GET(PDVD_OPCLSW_GPIO);
        #else
        regs0->gpio_in[PDVD_OPCLSW_GPIO / 16] & (1 << (PDVD_OPCLSW_GPIO % 16));  //get gpio16(COVER_SW)
        #endif
        
        //printf("open/close:%d...\n",temp);
        if(i<DELAY_COUNT)
          i++;
        
        if(temp)
        {
          if((i>=TRAYIN_START1) && (i<=TRAYIN_START2)) //added 04/12/31
          {
                i++;
                return;
          }
                
          #if 0//def REM_DECODE_JPEG
          if((!jpeg_decoding) && (!CDOpened())) 
          #else
          if(!CDOpened())
          #endif
          {
            #ifdef UNLOCK_STATE_NOT_CHECK_PASSWD
            disc_has_unlock = 0;
            #endif
            
            if(full_scrn)
            {    
                osd_init();
                ForceClearOsdMsg(0);
            }
            else
            osd_tog_region(0,OSD_OFF); //don't change the sequence between these two sentences and the "call_ir_func(IRC_EJECT);" sentence!!!
            t_disp = old_t_disp = 0;
            
            call_ir_func(IRC_EJECT);
            
            #ifdef DISPLAY_REMAIN_TIME
            display_and_time = 0;
            display_flag = 0; 
            #endif
            
            PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);
          }   
        }
        else
        {
            
            if((i>=TRAYIN_START1) && (i<=TRAYIN_START2))//added 04/12/31
                i++;
                
            if(CDOpened())
            {
              i = TRAYIN_START1;
              call_ir_func(IRC_EJECT);
            }
            
            if(i==1)
              ircmd_trayout();
            
        }
        #endif //end #ifdef CHECK_PORTABLE_OPCLSW
    #ifdef VIDEO_IN_CONTROL
}
#endif
    #ifdef BAT_DETECT
    check_alco_bat_detect_gpio();
    #endif   
}
     
#ifdef PDVD_USE_IO_SCAN_KEY

#ifdef ALCO_PV1950    
const BYTE gpio[8]={56,55,54,18,49,50,51,52};
#endif
#if defined(ALCO_PVS177W)||defined(ALCO_PVS127X)
const BYTE gpio[8]={23,22,21,16,12,13,14,15};
#endif

#ifdef ALCO_PVS19251
const BYTE gpio[4]={21,22,23,16};
#define MAX_DELAY   100
#define MAX_KEY     10
#endif

#ifdef ALCO_PVS1262
const BYTE gpio[4]={21,22,23,72};
#define MAX_DELAY   120
#define MAX_KEY     10
#endif

#ifdef ALCO_PVS8712
//const BYTE gpio[7]={14,13,12,21,22,23,72};
const BYTE gpio[5]={16,72,21,22,23};
#define MAX_DELAY   120
#define MAX_KEY     10
#endif

#ifdef ALCO_PVS1090
const BYTE gpio[8]={16,21,22,23,12,13,14,15};
#define MAX_DELAY   120
#define MAX_KEY     16
#endif

#ifdef ALCO_PVS1090_AVIN
const BYTE gpio[8]={59,21,22,23,55,56,57,29};
#define MAX_DELAY   120
#define MAX_KEY     16
#endif

#ifdef USE_COMBINED_KEY
#define LONG_PRESS_KEY_TIME 8  
#ifdef CONTINUOUS_PRESS_ACTION
#define OPEN_STATE_LONG_PRESS_KEY_TIME 4  
#endif
#endif
    
//#define PORTABLE_IOKEY_DEBUG
UINT16 get_portable_panel_key(void)
{
    UINT16 iRet=0;
    BYTE temp=0;
    #ifdef IO_CHECK_GET_DELAY
    BYTE delay_cnt=0;
    #endif
    
    
    #ifdef CHECK_PORTABLE_OPCLSW
    
    #ifdef PORTABLE_8202D
    regs0->sft_cfg4&= ~((0x1)<<6);//added 05/08/23     
    #endif
    GPIO_M_SET(PDVD_OPCLSW_GPIO,1);
	GPIO_E_SET(PDVD_OPCLSW_GPIO,0); //input
	    
    #ifdef IO_CHECK_GET_DELAY
	for(delay_cnt=0;delay_cnt<20;delay_cnt++)
	    ;
	#endif
	     
	temp=GPIO_I_GET(PDVD_OPCLSW_GPIO);
        
    if(temp)
        iRet=IRC_EJECT;
        
    #endif //end #ifdef CHECK_PORTABLE_OPCLSW
        
    return iRet;
}
        
void check_portable_key(void)
{
    #ifdef IO_CHECK_GET_DELAY
	UINT16 delay_cnt;
	#endif
	
    #ifdef VIDEO_IN_CONTROL
    if(AVin_step)
      return;
    #endif
    
    
#ifdef USE_COMBINED_KEY
#ifdef ALCO_PVS19251
    BYTE i,j,keydata,press_flag;
    static BYTE keyprev = 0;
    static BYTE key_press_times = 0 ;
    static BYTE long_press_flag = 0;
    
    #ifdef HOLD_KEY_DETECT
    if(hold_state)
        return;
    #endif

    regs0->gpio_master[1]|= 0x00e1;    //GPIO 16,21,22,23
    
    for(i=0;i<3;i++)
    {
        press_flag = 0; 
        
        if(i == 0)
        {    
            for(j=0;j<4;j++)
                GPIO_E_SET(gpio[j],0);
            
            #ifdef IO_CHECK_GET_DELAY
                for(delay_cnt=0;delay_cnt<MAX_DELAY;delay_cnt++)
                    ;
	        #endif
	    
            for(j=0;j<4;j++)
            {
                 keydata=GPIO_I_GET(gpio[j]);
                 
                 if(!keydata)
                 {
                    press_flag = 1;
                    goto KeyProcess;
                 }
            }
            
        }
        else if(i == 1)
        {    
            //two in
            for(j=0;j<2;j++)
                GPIO_E_SET(gpio[j],0);
            
            //two out
            for(;j<4;j++)
                GPIO_E_SET(gpio[j],1);
            
            GPIO_O_SET(gpio[j-2],0);    
            GPIO_O_SET(gpio[j-1],1);
            
            
            #ifdef IO_CHECK_GET_DELAY
                for(delay_cnt=0;delay_cnt<MAX_DELAY;delay_cnt++)
                    ;
	        #endif
	    
            for(j=0;j<2;j++)
            {
                 keydata=GPIO_I_GET(gpio[j]);
                 
                 if(!keydata)
                 {
                    press_flag = 1;
                    goto KeyProcess;
                 }
            }
            
        }
        else if(i == 2)
        {    
            //ont in
            GPIO_E_SET(gpio[0],0);
            
            //three out
            for(j=1;j<4;j++)
                GPIO_E_SET(gpio[j],1);
            
            GPIO_O_SET(gpio[j-3],0);
            GPIO_O_SET(gpio[j-2],1);    
            GPIO_O_SET(gpio[j-1],1);
            
            
            #ifdef IO_CHECK_GET_DELAY
                for(delay_cnt=0;delay_cnt<MAX_DELAY;delay_cnt++)
                    ;
	        #endif
	        
	        j = 0;
	        
	        keydata=GPIO_I_GET(gpio[j]);
                 
            if(!keydata)
            {
                press_flag = 1;
                goto KeyProcess;
            }
            
        }
    }

KeyProcess:
    if(press_flag)
    {
        keydata = 4*i+j+1;
                   
        if(keyprev != keydata)
        {//first press key!                         
            keyprev = keydata;
            #ifdef PORTABLE_IOKEY_DEBUG
            printf("%d key press at the first time\n",keydata);
            #endif
        }
        else 
        {//count the key press times
            #ifdef CONTINUOUS_PRESS_ACTION 
            key_press_times++;
                        
            if((key_press_times>=LONG_PRESS_KEY_TIME)
                ||((play_state==VCD_STATE_OPEN)&&(key_press_times>=OPEN_STATE_LONG_PRESS_KEY_TIME))
              )
            {        
                if((vfd_keycode[keyprev - 1]!=IRC_NULL) && (keyprev<=MAX_KEY))              
            call_ir_func(vfd_keycode[keyprev - 1]);
            
                key_press_times = 0;
                long_press_flag = 1;  
            }
                       
            #ifdef PORTABLE_IOKEY_DEBUG
            printf("key press times:---->%d\n",key_press_times);
            #endif
            
            #endif //end #ifdef CONTINUOUS_PRESS_ACTION
        }
    }  
    else
    {           
        if(keyprev && !long_press_flag)
        {
            if((vfd_keycode[keyprev - 1]!=IRC_NULL) && (keyprev<=MAX_KEY))
                {
                    //shenyj add for alco repeat_ab issue 1104
                if ((rep_ab_mode==REPEAT_FIND_B) && 
			        (sys_cmd==(CMD_FUNC|CMD_FUNC_REPAB)) && 
			        (cd_type_loaded != CDROM)) // Robert 2004/02/06
                {
			        //printf_w("!!!!waiting for navigator\n");
			        goto reset_key_para;
                }
                call_ir_func(vfd_keycode[keyprev - 1]);
            }
            
        }

        //printf_w("reset key para............\n");
reset_key_para:
        keyprev = 0;
        press_flag = 0;
        long_press_flag = 0;
        key_press_times = 0;
    } 
    
#elif defined(ALCO_PVS1262)
    BYTE i,j,keydata,press_flag;
    static BYTE keyprev = 0;
    static BYTE key_press_times = 0 ;
    static BYTE long_press_flag = 0;
    #ifdef PORTABLE_8202D
    regs0->sdc_data_cnt[6][0] |= (0x0e);
    #endif
    
    regs0->gpio_master[1]|= 0x00e0;    //GPIO 21,22,23
    GPIO_M_SET(72,1);//GPIO 72 
    
    for(i=0;i<4;i++)
    {
        press_flag = 0; 
        
        //current detected GPIO is set input
        GPIO_E_SET(gpio[i],0);
        keydata = 1;
        
        //others GPIOs output 1
        
        for(j=0;j<4;j++)
        {
            if(j!=i)
            {
                GPIO_E_SET(gpio[j],1);
                GPIO_O_SET(gpio[j],1);
            }   
        }
        
        if(i == 0)
        {                   
            GPIO_O_SET(gpio[j-1],0);
            
            #ifdef IO_CHECK_GET_DELAY
            for(delay_cnt=0;delay_cnt<MAX_DELAY;delay_cnt++)
                ;
	        #endif
            
            keydata=GPIO_I_GET(gpio[i]);
                 
            if(!keydata)
            {
                press_flag = 1;
                keydata = 1;
                goto KeyProcess;
            }
        }
        else if(i == 1)
        {    
            for(j=i;j<4;j++)
            {
                 if(j>i)
                GPIO_O_SET(gpio[j],0);
            
            #ifdef IO_CHECK_GET_DELAY
            for(delay_cnt=0;delay_cnt<MAX_DELAY;delay_cnt++)
                ;
	        #endif
	        
                 keydata=GPIO_I_GET(gpio[i]);
                 
                 if(!keydata)
                 {
                    press_flag = 1;
                    keydata = i+(j-1)+1;
                    goto KeyProcess;
                 }
            }
            
        }
        else if(i == 2)
        {                
	        for(j=i;j<4;j++)
            {
                 if(j>i)
                GPIO_O_SET(gpio[j],0);
            
            #ifdef IO_CHECK_GET_DELAY
            for(delay_cnt=0;delay_cnt<MAX_DELAY;delay_cnt++)
                ;
	        #endif
	        
                 keydata=GPIO_I_GET(gpio[i]);
                 
                 if(!keydata)
                 {
                    press_flag = 1;
                    keydata = i+j+1;
                    goto KeyProcess;
                 }
            }
        }
        else
        {                
            #ifdef IO_CHECK_GET_DELAY
            for(delay_cnt=0;delay_cnt<MAX_DELAY;delay_cnt++)
                ;
	        #endif
	        
	        keydata=1;
	             
            keydata=GPIO_I_GET(gpio[i]);
                 
            if(!keydata)
            {
                press_flag = 1;
                keydata = 7;
                goto KeyProcess;
            }
        }
    }

KeyProcess:
    if(press_flag)
    {                   
        if(keyprev != keydata)
        {//first press key!                         
            keyprev = keydata;
            #ifdef PORTABLE_IOKEY_DEBUG
            printf("%d key press at the first time\n",keydata);
            #endif
        }
        else 
        {//count the key press times
            #ifdef CONTINUOUS_PRESS_ACTION 
            key_press_times++;
                        
            if((key_press_times>=LONG_PRESS_KEY_TIME)
                ||((play_state==VCD_STATE_OPEN)&&(key_press_times>=OPEN_STATE_LONG_PRESS_KEY_TIME))
              )
            {        
                #ifdef PANEL_NEXT_FOWARD_IN_ONE_KEY
                if(keyprev == 2)
                {
                    call_ir_func(IRC_FORWARD);
                }
                else if(keyprev == 7)
                {
                    //printf_w(".............\n");
                    call_ir_func(IRC_BACKWARD);
                }
                else 
                #endif
                if((vfd_keycode[keyprev - 1]!=IRC_NULL) && (keyprev<=MAX_KEY))              
                    call_ir_func(vfd_keycode[keyprev - 1]);
                key_press_times = 0;
                long_press_flag = 1;  
            }
                       
            #ifdef PORTABLE_IOKEY_DEBUG
            printf("key press times:---->%d\n",key_press_times);
            #endif
            
            #endif //end #ifdef CONTINUOUS_PRESS_ACTION
        }
    }  
    else
    {           
        if(keyprev && !long_press_flag)
        {
            if((vfd_keycode[keyprev - 1]!=IRC_NULL) && (keyprev<=MAX_KEY))
            {
                //shenyj add for alco repeat_ab issue 1104
                if ((rep_ab_mode==REPEAT_FIND_B) && 
			        (sys_cmd==(CMD_FUNC|CMD_FUNC_REPAB)) && 
			        (cd_type_loaded != CDROM)) // Robert 2004/02/06
                {
			        //printf_w("!!!!waiting for navigator\n");
			        goto reset_key_para;
                }
                call_ir_func(vfd_keycode[keyprev - 1]);
            }    
            
        }

        //printf_w("reset key para............\n");
reset_key_para:
        keyprev = 0;
        press_flag = 0;
        long_press_flag = 0;
        key_press_times = 0;
    } 
     
#elif defined(ALCO_PVS8712)
    BYTE i,j,k,keydata,press_key=0;
    static BYTE keyprev=0;  
    regs0->gpio_master[1]|= 0x00e0;    //GPIO 21,22,23
    regs0->sdc_data_cnt[6][0] |= (0x0e);
    GPIO_M_SET(72,1);//GPIO 72 
    regs0->sft_cfg1&= ~((0x1)<<3); //GPIO 16 PIN66    
    GPIO_M_SET(16,1);//GPIO 16 PIN66
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
                GPIO_O_SET(gpio[j],1);
	   
	    GPIO_O_SET(gpio[i],0);
	    #if 0//def IO_CHECK_GET_DELAY
	    for(delay_cnt=0;delay_cnt<200;delay_cnt++)
                ;
	        #endif
  		for(k=2;k<5;k++)
  		{  		 
        	keydata=GPIO_I_GET(gpio[k]);
    		
    		if(keydata==0)
    		{    	       	  
    			press_key=1;
    			if(i==0)//shenyj modify for alco 8712 0928
    			keydata=k-1;
    			if(i==1)    	
    			keydata=k+2;	
    			//printf_w("key:%d i:%d k:%d.........\n",keydata,i,k);
    			if(keyprev!=keydata)
    			{    			  			
    			    keyprev=keydata;
    			    if ((rep_ab_mode==REPEAT_FIND_B) && 
			        (sys_cmd==(CMD_FUNC|CMD_FUNC_REPAB)) && 
			        (cd_type_loaded != CDROM)) // Robert 2004/02/06
                {
			        //printf_w("!!!!waiting for navigator\n");
			        goto reset_key_para;			        
                }
    			    call_ir_func(vfd_keycode[keydata - 1]);
    			    //printf("key %d SW %d,%d.\n",keydata,i,k-4);
    			}  
    			break;
    		}  		    		
  		}  		
reset_key_para:
    press_key=0;
    keyprev=0;	
  	}
  	if(press_key==0) keyprev=0;
  	
#elif defined(ALCO_PVS1090)||defined(ALCO_PVS1090_AVIN)
    BYTE i,j,keydata,press_key=0;
    static BYTE keyprev=0;  
    regs0->gpio_master[1]|= 0x00e0;    //GPIO 21,22,23
    #ifdef ALCO_PVS1090_AVIN
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
    #else
    regs0->sft_cfg1&= ~((0x1)<<3); //GPIO 16 PIN66    
    GPIO_M_SET(16,1);//GPIO 16 PIN66
    #endif
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
                GPIO_O_SET(gpio[j],1);
	   
	    GPIO_O_SET(gpio[i],0);
	    #ifdef IO_CHECK_GET_DELAY
	    for(delay_cnt=0;delay_cnt<200;delay_cnt++)
                ;
	    #endif
  		for(j=4;j<8;j++)
  		{  		 
        	keydata=GPIO_I_GET(gpio[j]);    		
    		if(keydata==0)
    		{    	       	  
    			keydata=i*4+(j-4)+1;	
    			printf_w("key:%d i:%d j:%d.........\n",keydata,i,j);
    			if(keyprev!=keydata)
    			{    			  			
    			    keyprev=keydata;
    			    if ((rep_ab_mode==REPEAT_FIND_B) && 
			        (sys_cmd==(CMD_FUNC|CMD_FUNC_REPAB)) && 
			        (cd_type_loaded != CDROM)) // Robert 2004/02/06
                {
			        //printf_w("!!!!waiting for navigator\n");
			        goto reset_key_para;			        
                }
    			    call_ir_func(vfd_keycode[keydata - 1]);
    			    //printf("key %d SW %d,%d.\n",keydata,i,k-4);
    			}  
    			break;
    		}  		    		
  		}  
reset_key_para:
			        press_key = 0;
			        keyprev=0; 
                }
  	if(press_key==0) keyprev=0; 	
#else    
    BYTE i,j,keydata;
    static BYTE column_dot = 4;
    static BYTE row_dot = 0;
    static BYTE keyprev = 0;
    static BYTE key_press_times = 0 ;
    static BYTE long_press_flag = 0;
    
    #ifdef HOLD_KEY_DETECT
    if(hold_state)
        return;
    #endif
	
    //regs0->gpio_oe[3]&= 0xffcf;     //jhuang org 011f
    #ifdef ALCO_PV1950
    regs0->gpio_master[1]|= 0x0004;    //GPIO 18
    regs0->gpio_master[3]|= 0x01de;    //GPIO 49,50,51,52,54,55,56    
	regs0->gpio_oe[1]|= 0x0004;        //GPIO 18 output
    regs0->gpio_oe[3]|= 0x01c0;		   //GPIO 54,55,56 output	
    regs0->gpio_oe[3]&= ~(0x001e);     //GPIO 49,50,51,52 input
    #endif
    
    #ifdef ALCO_PVS177W
    regs0->gpio_master[0]|= 0xf000;    //GPIO 12,13,14,15
    regs0->gpio_master[1]|= 0x00e1;    //GPIO 16,21,22,23
    regs0->gpio_oe[0]&= ~(0xf000);     //GPIO 12,13,14,15 input
    regs0->gpio_oe[1]|= 0x00e1;        //GPIO 16,21,22,23 output
    #endif
    
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
          GPIO_O_SET(gpio[j],1);
          
        GPIO_O_SET(gpio[i],0);
    
        #ifdef IO_CHECK_GET_DELAY
	    for(delay_cnt=0;delay_cnt<50;delay_cnt++)
	        ;
	    #endif
	        
        for(j=4;j<8;j++)
        {
           
	
            keydata=GPIO_I_GET(gpio[j]);
            
            if(keydata == 0)
            {//have key pressing                  
                keydata=i*4+(j-4)+1;
                column_dot = j;
                row_dot = i;
                
                if(keyprev != keydata)
                {//first press key!                         
                    keyprev = keydata;
                    #ifdef PORTABLE_IOKEY_DEBUG
                    printf("%d key press at the first time\n",keydata);
                    #endif
                }
                else 
                {//count the key press times
                    #ifndef CONTINUOUS_PRESS_ACTION 
                    if((keydata == 2) || (keydata == 6))
                    #endif
                    {
                        key_press_times++;
                        
                        if((key_press_times>=LONG_PRESS_KEY_TIME)
                            #ifdef CONTINUOUS_PRESS_ACTION
                            ||((play_state==VCD_STATE_OPEN)&&(key_press_times>=OPEN_STATE_LONG_PRESS_KEY_TIME))
                            #endif
                           )
                        
                        {
                          if(keyprev == 2)
                          {
                            if(Is_JPEG_STATE() && (pFsJpeg->gbfsSlide))
                                call_ir_func(IRC_PREV); 
                          else
                                call_ir_func(IRC_BACKWARD); 
                          }
                          else if(keyprev == 6)
                          {
                            if((cd_type_loaded==CDROM) && Is_JPEG_STATE() && (pFsJpeg->gbfsSlide))
                                call_ir_func(IRC_NEXT); 
                            else
                                call_ir_func(IRC_FORWARD);
                          }
                          #ifdef CONTINUOUS_PRESS_ACTION
                          else
                          {
                              #ifdef NEED_DIFF_IR_PANEL_KEY
                              if(!panel_key_flag)
                                panel_key_flag |= (0x01<<0);
                              #endif
                              
                              call_ir_func(vfd_keycode[keyprev - 1]);  
                              
                              #ifdef NEED_DIFF_IR_PANEL_KEY
                              /* //04/12/21 do not need pause/setup key
                              #ifdef USE_REVERSE_IO_KEY 
                              if((keyprev!=15) && (play_state!=VCD_STATE_STOP) && (play_state!=VCD_STATE_OPEN) && (play_state!=VCD_STATE_IDLE))
                              #else
                              if((keyprev!=9) && (play_state!=VCD_STATE_STOP) && (play_state!=VCD_STATE_OPEN) && (play_state!=VCD_STATE_IDLE))
                              #endif
                              */
                              panel_key_flag = 0;
                              
                              #endif
                          }
                          #endif
                            
                          key_press_times = 0;
                          long_press_flag = 1;  
                        }
                        
                        #ifdef PORTABLE_IOKEY_DEBUG
                        printf("key press times:---->%d\n",key_press_times);
                        #endif
                    }
                }           
                break;
            }
            else if((j == column_dot) && (i == row_dot) && (keyprev != 0))
            {//key is released
                /*
                if(key_press_times >= LONG_PRESS_KEY_TIME)
                {//long press key 
                    #ifdef PORTABLE_IOKEY_DEBUG
                    printf("call long key:%d!press %d times\n",keyprev,key_press_times);
                    #endif  
                                  
                    if(keyprev == 2)
                        call_ir_func(IRC_BACKWARD); 
                    else
                        call_ir_func(IRC_FORWARD);
              }
              else
              */
              if(!long_press_flag)
              {//short key press
                  #ifdef NEED_DIFF_IR_PANEL_KEY
                  if(!panel_key_flag)
                     panel_key_flag |= (0x01<<0);
                  #endif
                  
                  call_ir_func(vfd_keycode[keyprev - 1]);
                  
                  #ifdef NEED_DIFF_IR_PANEL_KEY
                  
                  #ifdef USE_REVERSE_IO_KEY 
                  if((keyprev!=15) && (play_state!=VCD_STATE_STOP) && (play_state!=VCD_STATE_OPEN) && (play_state!=VCD_STATE_IDLE))
                  #else
                  if((keyprev!=9) && (play_state!=VCD_STATE_STOP) && (play_state!=VCD_STATE_OPEN) && (play_state!=VCD_STATE_IDLE))
                  #endif
                  panel_key_flag = 0;
                  #endif
                  
                  #ifdef PORTABLE_IOKEY_DEBUG
                  printf("call short key:%d\n",keyprev);
                  #endif
              }
              
              key_press_times = 0;
              keyprev = 0;
              column_dot = 4;
              row_dot = 0;
              long_press_flag = 0;
           } 
        }       
    }
#endif
#else
    BYTE i,j,k,keydata,press_key=0;
    static BYTE keyprev=0;
	
	regs0->gpio_master[1]|= 0x0004;    //GPIO 18
    regs0->gpio_master[3]|= 0x01de;    //GPIO 49,50,51,52,54,55,56    
	#ifdef USE_REVERSE_IO_KEY 
	regs0->gpio_oe[1]&= ~(0x00040;        //GPIO 18 input
    regs0->gpio_oe[3]&= ~(0x01c0);		   //GPIO 54,55,56 input	
    regs0->gpio_oe[3]|= (0x001e);     //GPIO 49,50,51,52 output
    #else
	regs0->gpio_oe[1]|= 0x0004;        //GPIO 18 output
    regs0->gpio_oe[3]|= 0x01c0;		   //GPIO 54,55,56 output	
    regs0->gpio_oe[3]&= ~(0x001e);     //GPIO 49,50,51,52 inout
    #endif
    
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		  GPIO_O_SET(gpio[j],1);
	   
	    GPIO_O_SET(gpio[i],0);
	
  		for(k=4;k<8;k++)
  		{  		 
        	keydata=GPIO_I_GET(gpio[k]);
    		
    		if(keydata==0)
    		{    	       	  
    			press_key=1;
    			keydata=i*4+(k-4)+1;    			
    			//printf("key:%d i:%d k:%d.........\n",keydata,i,k);
    			if(keyprev!=keydata)
    			{    			  			
    			    keyprev=keydata;
    			    call_ir_func(vfd_keycode[keydata - 1]);
    			    //printf("key %d SW %d,%d.\n",keydata,i,k-4);
    			}  
    			break;
    		}    		    		
  		}  		
  	}
  	if(press_key==0) keyprev=0;
#endif //end #ifdef USE_COMBINED_KEY
}
#endif //#ifdef PDVD_USE_IO_SCAN_KEY
///////////////////////////shenyj add for alco 8712
#ifdef ALCO_PVS8712
const BYTE gpio2[4]={12,13,14,15};

void check_portable_key2(void)
{

    #ifdef IO_CHECK_GET_DELAY
	UINT16 delay_cnt;
	#endif
	
    BYTE i,j,keydata,press_flag;
    static BYTE keyprev = 0;
    static BYTE key_press_times = 0 ;
    static BYTE long_press_flag = 0;    
    regs0->gpio_master[0]|= 0x0f00;    //GPIO 12,13,14,15 
    for(i=0;i<4;i++)
    {
        press_flag = 0;         
        //current detected GPIO is set input
        GPIO_E_SET(gpio2[i],0);
        keydata = 1;        
        //others GPIOs output 1        
        for(j=0;j<4;j++)
        {
            if(j!=i)
            {
                GPIO_E_SET(gpio2[j],1);
                GPIO_O_SET(gpio2[j],1);
            }   
        }      
        if(i == 0)
        {  
            for(j=i;j<4;j++)
            {
                 if(j>i)
                GPIO_O_SET(gpio2[j],0);            
            #ifdef IO_CHECK_GET_DELAY
            for(delay_cnt=0;delay_cnt<MAX_DELAY;delay_cnt++)
                ;
	        #endif	        
                 keydata=GPIO_I_GET(gpio2[i]);                 
                 if(!keydata)
                 {
                    press_flag = 1;
                    keydata = i+j+1;
                    goto KeyProcess;
                 }
            }           
        }
        else if(i == 1)
        {    
            for(j=i;j<4;j++)
            {
                 if(j>i)
                GPIO_O_SET(gpio2[j],0);            
            #ifdef IO_CHECK_GET_DELAY
            for(delay_cnt=0;delay_cnt<MAX_DELAY;delay_cnt++)
                ;
	        #endif
	        
                 keydata=GPIO_I_GET(gpio2[i]);
                 
                 if(!keydata)
                 {
                    press_flag = 1;
                    keydata = 6+j;
                    goto KeyProcess;
                 }
            }
            
        }
        else if(i == 2)
        {                
	        for(j=i;j<4;j++)
            {
                 if(j>i)
                GPIO_O_SET(gpio2[j],0);
            
            #ifdef IO_CHECK_GET_DELAY
            for(delay_cnt=0;delay_cnt<MAX_DELAY;delay_cnt++)
                ;
	        #endif	        
                 keydata=GPIO_I_GET(gpio2[i]);
                 
                 if(!keydata)
                 {
                    press_flag = 1;
                    keydata = i+j+1;
                    goto KeyProcess;
                 }
            }
        }
        else
        {                
            #ifdef IO_CHECK_GET_DELAY
            for(delay_cnt=0;delay_cnt<MAX_DELAY;delay_cnt++)
                ;
	        #endif	        
	        keydata=1;	             
            keydata=GPIO_I_GET(gpio2[i]);                 
            if(!keydata)
            {
                press_flag = 1;
                keydata =10;
                goto KeyProcess;
            }
        }
    }

KeyProcess:
    if(press_flag)
    {                   
        if(keyprev != keydata)
        {//first press key!                         
            keyprev = keydata;
            #ifdef PORTABLE_IOKEY_DEBUG
            printf_w("%d key press at the first time\n",keydata);
            #endif
        }
        else 
        {//count the key press times
            #ifdef CONTINUOUS_PRESS_ACTION 
            key_press_times++;
                        
            if((key_press_times>=LONG_PRESS_KEY_TIME)
                ||((play_state==VCD_STATE_OPEN)&&(key_press_times>=OPEN_STATE_LONG_PRESS_KEY_TIME))
              )
            {        
                #ifdef PANEL_NEXT_FOWARD_IN_ONE_KEY
                if(keyprev == 2)
                {
                    call_ir_func(IRC_FORWARD);
                }
                else if(keyprev == 7)
                {
                   // printf_w(".............\n");
                    call_ir_func(IRC_BACKWARD);
                }
                else 
                #endif
                if((vfd_keycode2[keyprev - 1]!=IRC_NULL) && (keyprev<=MAX_KEY))              
                    call_ir_func(vfd_keycode2[keyprev - 1]);
            
                key_press_times = 0;
                long_press_flag = 1;  
            }
                       
            #ifdef PORTABLE_IOKEY_DEBUG
            printf("key press times:---->%d\n",key_press_times);
            #endif
            
            #endif //end #ifdef CONTINUOUS_PRESS_ACTION
        }
    }  
    else
    {           
        if(keyprev && !long_press_flag)
        {
            if((vfd_keycode2[keyprev - 1]!=IRC_NULL) && (keyprev<=MAX_KEY))
                {
                     //shenyj add for alco repeat_ab issue 1104
                if ((rep_ab_mode==REPEAT_FIND_B) && 
			        (sys_cmd==(CMD_FUNC|CMD_FUNC_REPAB)) && 
			        (cd_type_loaded != CDROM)) // Robert 2004/02/06
                {
			        //printf_w("!!!!waiting for navigator\n");
			        goto reset_key_para;
                }
                call_ir_func(vfd_keycode2[keyprev - 1]);
            }
            
        }
reset_key_para:
        keyprev = 0;
        press_flag = 0;
        long_press_flag = 0;
        key_press_times = 0;
    }   
}
#endif
/////shenyj move here for alco 2006/03/23//////////////////
#if defined(SUPPORT_DVD_POWER_ONOFF)&&defined(ALCO_PORTABLE_DVD_8202D_DVB)
void  dvd_power_onoff(BYTE  onoff)
{
    GPIO_M_SET(DVD_POWER_SW_GPIO,1);  
    GPIO_E_SET(DVD_POWER_SW_GPIO,1);

	if(onoff == TURN_ON) 
	{              
        GPIO_O_SET(DVD_POWER_SW_GPIO,1);  //tiany: turn on MOTOR power 
        // printf_w("turn off  MOTOR power   111111       turn on  MOTOR power   \n");//20051207 tiang add 
    }
	else
	{
        GPIO_O_SET(DVD_POWER_SW_GPIO,0);  //tiany: turn off  MOTOR power 
	    //  printf_w("turn off  MOTOR power     22222222     turn off  MOTOR power   \n");//20051207 tiang add 
	}
}            
#endif //endif=>#ifdef  SUPPORT_DVD_POWER_ONOFF
#if defined(CHECK_PORTABLE_OPCLSW)/*||defined(TOP_DOOR_LOADER)*/
BYTE  check_eject_sw(void);
BYTE  check_eject_sw(void)
{
      return  GPIO_I_GET(PDVD_OPCLSW_GPIO);
}
#endif
/////shenyj move here for alco 2006/03/23//////////////////

