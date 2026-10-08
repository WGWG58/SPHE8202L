/*
----->included by vfd_io_util.c
----->only for portable dvd use.
----->did it on 07/25
*/

#ifdef EASTWIN
extern UINT8  safe_on;
#endif

#ifdef MUSTEK_K100D_MODEL//by justin 2005/09/30
extern int IunTestPin84;
#endif

#ifdef SUPPORT_8202_DVB
#include "..\dvb_h\dvb_func.h"
extern UINT8 Dvb_ircmd_pre_parser(BYTE rx __attribute__((unused)));
#endif

#ifdef REM_JPEG_DECODE_STATE
extern BYTE jpeg_in_decode;
#endif

#ifdef EASTWIN
void check_portable_gpio(void)
{
    UINT16 temp=0;
    
    #ifdef TFT_VIDEO_INOUT
    static BYTE AVin_step = 0;
    
    INT_EXT_GPIO_INIT();
   
    switch (GPIO_I_GET(INT_EXT_VIDEO_GPIO))
    {
      case 0://8210 input video to TFT
        if((system_state == SYSTEM_OPEN) && (AVin_step == 1))
        {//just now system was interrupted in reading disc 
              if(CDOpened())
              {
                call_ir_func(IRC_EJECT);
                AVin_step = 0;
                //printf("i am going to read disc.......\n");
              }
        }
        else if((system_state == SYSTEM_STOP) && (AVin_step == 2))
        {//just now system was interrupted in normal playing state
                ircmd_play();
                AVin_step = 0;
                //printf("i am going to play disc.......\n");
        }
        
        if(hold_state == 2)
          hold_state = 0;
          
      break;
      case 1://External AV input to TFT
        if(system_state == SYSTEM_READ_TITLE)
        {//in reading disc and 
            if(!CDOpened())
            {
              AVin_step = 1;
              call_ir_func(IRC_EJECT);
              //printf("video in when reading disc,then i go into open state\n");
            } 
            
        }
        else if(system_state == SYSTEM_BROWSE)
        {
            if(play_state != VCD_STATE_STOP)
            {
                AVin_step = 2;
                ircmd_stop();
                #ifdef STOP_LOADER
                stop_loader();
                #endif
                //printf("video in when playing disc,then i go into stop state\n");
            }
        } 
        
        if(hold_state == 0)
          hold_state = 2;       
      
      break;
      
    }
    
    if(!AVin_step)
    {
    #endif //end #ifdef TFT_VIDEO_INOUT
    
    #ifdef SUNPLUS_8202P_DEMOBOARD
    regs0->sft_cfg4 &= ~((0x03)<<2);    //Enable GPIO2,3 For COVER & TFT SW
    #endif
    
    #ifdef TFT_VIDEO_INOUT
    }
    #endif //end #ifdef TFT_VIDEO_INOUT

    #ifdef TFT_VIDEO_INOUT 
    if(!AVin_step)
    {
    #endif //end #ifdef TFT_VIDEO_INOUT 
    #ifdef HOLD_KEY_DETECT    
    temp=regs0->gpio_in[HOLD_GPIO / 16] & (1 << (HOLD_GPIO % 16));  //get gpio37(HOLD)
    if(temp)
        hold_state=1;
    else
        hold_state=0;           
    #endif
    
    temp=regs0->gpio_in[TFT_SW_GPIO / 16] & (1 << (TFT_SW_GPIO % 16));  //get gpio44(TFT_SW)

    if(temp)						// lcd panel open
    {
    	if(!bINVERTER_POWER)
    	{
    		INVERTER_POWER_ON();			
    		bINVERTER_POWER = 1;
    		bPOWER_LED_FLASH = 0;
    	}		
    }
    else									// lcd panel close
    {
    	if(bINVERTER_POWER)
    	{
    		INVERTER_POWER_OFF();			
    		bINVERTER_POWER = 0;
    		bPOWER_LED_FLASH = 1;
    	}   	
    }
    
    if(bINVERTER_POWER)						// lcd panel open
    {
		if(!bAMP_IS_ON && bPOWER_ON_MUTE_EXE)
		{
    		ENABLE_AMP();
    		bAMP_IS_ON = 1;
    	}
    }
    else									// lcd panel close
    {
		if(EAR_DETECT())			// earphone no plug in 
    	{
    		if(bAMP_IS_ON)
			{
    			DISABLE_AMP();
    			bAMP_IS_ON = 0;
    		}
    	} 
    	else						// earphone plug in 
    	{	if(!bAMP_IS_ON && bPOWER_ON_MUTE_EXE)
			{
    			ENABLE_AMP();
    			bAMP_IS_ON = 1;
    		}							
    	} 
    }
    
    #ifdef POWER_ON_MUTE
    if(!bPOWER_ON_MUTE_EXE)
    {
    	if(power_on_mute_timer >100 )	// power on to mute off time around 4.5S 
    	{
    		AUDIO_MUTE_OFF();
    		bPOWER_ON_MUTE_EXE = 1;
    		power_on_mute_timer = 0;
    	}
    	power_on_mute_timer++;
    }
    #endif    
    
    #ifdef POWER_LED_FLASH
    if(bPOWER_LED_FLASH)
    {
    	if( power_led_flash_timer < 100 )
    	{
    		power_led_flash_timer ++;
    		POWER_LED_ON();	   	
    	}    	
    	else
    	{
    		if((power_led_flash_timer>=100) & (power_led_flash_timer<=200))
            {
    			power_led_flash_timer ++;    		
    			POWER_LED_OFF();
    		}
    		else
    		    power_led_flash_timer = 0;
    	}	
    }
    else
    {
    	power_led_flash_timer = 0;
    	POWER_LED_OFF();
    }  
    #endif // end of POWER_LED_FLASH
      
    
    #ifdef TFT_VIDEO_INOUT
    }
    #endif //end #ifdef TFT_VIDEO_INOUT
        
    // Eastwin change to GPIO 18
    temp = regs0->gpio_in[LOWBAT_DET_GPIO / 16] & (1 << (LOWBAT_DET_GPIO % 16));
    if(!temp)	  
    {   
        bIS_LOWBAT = 0;			// Kevin Sep 10,04 
        if(bLOWBAT_DISP)
        {
        	bLOWBAT_DISP = 0;
        	ClearOsdMsg(2);
        	lowbat_timer=0;
        } 
    }
    else
    {
        bIS_LOWBAT = 1;			// Kevin Sep 10,04 		
        if (safe_on==1)			// Kevin Sep 10,04 
        	safe_srn_off();
        if(lowbat_timer<100)
        {
            PrintOsdMsg(STR_OS_LOWBAT,REGION2,0,0);
            lowbat_timer++;
            bLOWBAT_DISP = 1;
        }   
        else
        {
            if((lowbat_timer>=100) & (lowbat_timer<150))
            {
                ClearOsdMsg(2);
                lowbat_timer++;
                bLOWBAT_DISP = 0;
            }   
            else
            {    
                lowbat_timer = 0;
                bLOWBAT_DISP = 1;
            }
        }   
    }   
}

#elif defined (MALATA_GPS_DVD)// liulifeng add for malata gps portable dvd  2005-09-21
 void check_portable_gpio(void)
{
	UINT16 temp=0;
	
	#ifdef CHECK_PORTABLE_OPCLSW
    regs0->sft_cfg4 &= ~((0x03)<<2);    //Enable GPIO2,3 For COVER & TFT SW
    temp=GPIO_I_GET(3);  //get gpio16(COVER_SW)

    if(temp)
    {
      if(!CDOpened())
      {
        call_ir_func(IRC_EJECT);
        PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);
      }   
    }
    else
    {
        if(CDOpened())
          call_ir_func(IRC_EJECT);
    }
	#endif    
 }

#else

void check_portable_gpio(void)
{
	UINT16 temp __UNUSED =0;
	
	#ifdef SUPPORT_SYS_POWER_ON_WAITING_MCUINFO //tianye 200607
       if(!flag_check_mcu_info)
       {
	   return;
       }
 	#endif//end=> #ifdef  SUPPORT_SYS_POWER_ON_WAITING_MCUINFO
	
	#ifdef REM_JPEG_DECODE_STATE
    if(jpeg_in_decode)
        return;
    #endif
  
    #ifdef TFT_VIDEO_INOUT
    static BYTE AVin_step = 0;
    
    INT_EXT_GPIO_INIT();
   
    switch (GPIO_I_GET(INT_EXT_VIDEO_GPIO))
    {
    case 0://8210 input video to TFT
        if((system_state == SYSTEM_OPEN) && (AVin_step == 1))
        {//just now system was interrupted in reading disc 
              if(CDOpened())
              {
                call_ir_func(IRC_EJECT);
                AVin_step = 0;
                //printf("i am going to read disc.......\n");
              }
        }
        else if((system_state == SYSTEM_STOP) && (AVin_step == 2))
        {//just now system was interrupted in normal playing state
                ircmd_play();
                AVin_step = 0;
                //printf("i am going to play disc.......\n");
        }
        
        if(hold_state == 2)
            hold_state = 0;
          
        break;
    case 1://External AV input to TFT
        if(system_state == SYSTEM_READ_TITLE)
        {//in reading disc and 
            if(!CDOpened())
            {
              AVin_step = 1;
              call_ir_func(IRC_EJECT);
              //printf("video in when reading disc,then i go into open state\n");
            } 
            
        }
        else if(system_state == SYSTEM_BROWSE)
        {
            if(play_state != VCD_STATE_STOP)
            {
                AVin_step = 2;
                ircmd_stop();
                #ifdef STOP_LOADER
                stop_loader();
                #endif
                //printf("video in when playing disc,then i go into stop state\n");
            }
        } 
        
        if(hold_state == 0)
            hold_state = 2;       
      
        break;
    }
    
    if(!AVin_step)
    {
    #endif //end #ifdef TFT_VIDEO_INOUT
    
        #ifdef FIX_GAME_RETURN_OSD_ERR//tianye 200607
		extern  UINT32 Is_Dvb_State();
        #endif//end=> #ifdef FIX_GAME_RETURN_OSD_ERR	
	  
        #ifdef  DVB_DVD_8202
	    if((system_state!=SYSTEM_TS)
	       #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
		   &&(source_play_mode==DVD_PLAY_MODE)
           #endif
	     #ifdef  FIX_GAME_RETURN_OSD_ERR//tianye 200607
                 &&(! Is_Dvb_State())
	      #endif//end=> #ifdef  FIX_GAME_RETURN_OSD_ERR
	   
	       ) 
	    {
        #endif

            #ifdef CHECK_PORTABLE_OPCLSW //Jack moved to here 06/04/11
            
            #if defined(SUNPLUS_8202P_DEMOBOARD)||defined(DVB_DVD_8202)
            regs0->sft_cfg4 &= ~((0x03)<<2);    //Enable GPIO2,3 For COVER & TFT SW
            #endif

            #if defined(MUSTEK_K100D_MODEL)
            GPIO_E_SET(DOOR_SENSE_GPIO,0);
            GPIO_E_SET(OPEN_TRAY_GPIO, 1);
            GPIO_E_SET(EJECT_KEY_GPIO, 0);
  
		    if(!(GPIO_I_GET(DOOR_SENSE_GPIO)))//关门状态
		    {	
			    #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
			    if(source_play_mode == DVD_PLAY_MODE)
			    #endif
			    {			
				    if(!(GPIO_I_GET(EJECT_KEY_GPIO)))//eject键按下停机	//if(!GPIO_I_GET(3))//eject键按下停机
				    {	
				        #ifndef ADD_AUDIO_PLAY_WHEN_OPEN
				        GPIO_MUTE();// by justin 2005/11/01
				        #endif
			            //safe_srn_forceOFF();
			            //safe_srn_off();//xiaminmin050811     
			            //by justin 2005/09/26  get it away about saverscreen  by justin
			            if((full_scrn&SETUP) || (full_scrn&CUSTM))
			            { 
			                ExitSetupPage(1); // if in setup page ,exit it and open the door
			            }//xiaminmin050909
						else
						    osd_tog_region(0,OSD_OFF);
                        
                        t_disp = old_t_disp = 0;
						
						call_ir_func(IRC_EJECT);
           				PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);
                        //bDoorStatus=1;
						if(system_state==SYSTEM_NODISC)//(system_state==SYSTEM_STOP))//||(pre_stop==0))//xiaminmin0580808
						{					
							delay_srv_10ms(50);//out 200ms plus
							GPIO_E_SET(OPEN_TRAY_GPIO, 1);  //GPIO_E_SET(7, 1); liutao 0126 for gpio modify
							GPIO_O_SET(OPEN_TRAY_GPIO, 0); //GPIO_O_SET(7, 0);
							GPIO_O_SET(OPEN_TRAY_GPIO, 1); //GPIO_O_SET(7, 1);//电磁阀动作
							delay_srv_10ms(20);//out 200ms plus
							GPIO_O_SET(OPEN_TRAY_GPIO, 0);  //GPIO_O_SET(7, 0);//电磁阀复位
						}
						else
						{
							extern void watchdog_renew(int n);
							watchdog_renew(WATCHDOG_RENEW_TIME);
							delay_srv_10ms(350);//xiaminmin050701
							GPIO_E_SET(OPEN_TRAY_GPIO, 1);  //GPIO_E_SET(7, 1); liutao 0126 for gpio modify
							GPIO_O_SET(OPEN_TRAY_GPIO, 0); //GPIO_O_SET(7, 0);
							GPIO_O_SET(OPEN_TRAY_GPIO, 1); //GPIO_O_SET(7, 1);//电磁阀动作
							delay_srv_10ms(20);//out 200ms plus
							GPIO_O_SET(OPEN_TRAY_GPIO, 0);  //GPIO_O_SET(7, 0);//电磁阀复位							
							watchdog_renew(WATCHDOG_RENEW_TIME);	
						}	
				        /*
						if(user_mute==1)
						{
						    ircmd_mute();
						}*/
						delay_srv_10ms(50);//out 200ms plus
					    GPIO_DEMUTE();   // by justin 2005/11/01
	                }	
		            else
		            {		
				        if(CDOpened())
             		        call_ir_func(IRC_EJECT);	
			        }
		        }
	        }	
		    else
		    {		
			    delay_srv_10ms(1);//防止开门时光头发光	
			    GPIO_MUTE();	 // by justin 2005/11/01
		    }
    
            #else//not K100D

            temp=GPIO_I_GET(PDVD_OPCLSW_GPIO);
    
            if(temp)
            {
                if(!CDOpened())
                {
		            #ifdef ARGUS_PDVD_MENU_PLUS
                    if(full_scrn & SETUP_PLUS)
                        ircmd_setup_plus();
                    #endif //end #ifdef ARGUS_PDVD_MENU_PLUS
                    call_ir_func(IRC_EJECT);
                    PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);
                }   
            }
            else
            {
                if(CDOpened())
                call_ir_func(IRC_EJECT);
            }
	    
            #endif //end #if defined(MUSTEK_K100D_MODEL)
            #endif //#ifdef CHECK_PORTABLE_OPCLSW
        
	    #ifdef  DVB_DVD_8202
        }
	    #endif   
        
    #ifdef TFT_VIDEO_INOUT
    }
    #endif //end #ifdef TFT_VIDEO_INOUT
        
        

#if defined(GBM_PORTABLE_DVD)||defined(SUNPLUS_8202P_DEMOBOARD)     //rbhung for GBM Portable DVD
    #ifdef TFT_VIDEO_INOUT 
    if(!AVin_step)
    #endif //end #ifdef TFT_VIDEO_INOUT 
    {
        #ifdef HOLD_KEY_DETECT    
        temp=regs0->gpio_in[HOLD_GPIO / 16] & (1 << (HOLD_GPIO % 16));  //get (HOLD)
        if(temp)
        	hold_state=1;
        else
        	hold_state=0;		 	
        #endif
        
        temp=regs0->gpio_in[TFT_SW_GPIO / 16] & (1 << (TFT_SW_GPIO % 16));  //get (TFT_SW)
        if(temp)
            regs0->gpio_out[CTR_TFT_GPIO /16]|= (1 << (CTR_TFT_GPIO % 16));
        else
            regs0->gpio_out[CTR_TFT_GPIO /16]&= ~(1 << (CTR_TFT_GPIO % 16));
    }
    	
    temp=regs0->gpio_in[MCU_POWER_DET_GPIO / 16] & (1 << (MCU_POWER_DET_GPIO % 16));  //get gpio41(MCU_POWER_DET)
    if(temp)
    {
    	powerdown_timer=0;
    }
    else
    {
    	powerdown_timer++;
    	if(powerdown_timer>100)
    	{
            regs0->gpio_out[CTR_GLED_GPIO/16]|= (1 << (CTR_GLED_GPIO % 16));      //CTR_GLED->H,GREEN LED OFF
            regs0->gpio_out[DSP_RLED_GPIO/16]&= ~(1 << (DSP_RLED_GPIO % 16));     //DSP_RLED->L,RED LED ON    
	    	call_ir_func(IRC_POWER);
		}
    }	
        	
    	
    temp=regs0->gpio_in[LOWBAT_DET_GPIO / 16] & (1 << (LOWBAT_DET_GPIO % 16));  //get gpio42(LOWBAT_DET)
    if(temp)
    {	
        if(lowbat_timer==0)
			ClearOsdMsg(2);
    	lowbat_timer=1;
        regs0->gpio_out[CTR_GLED_GPIO/16]&= ~(1 << (CTR_GLED_GPIO % 16));     //CTR_GLED->L,GREEN LED ON
        regs0->gpio_out[DSP_RLED_GPIO/16]|= (1 << (DSP_RLED_GPIO % 16));      //DSP_RLED->H,RED LED OFF
    }
    else
    {
    	if(lowbat_timer<100)
    	{
    		PrintOsdMsg(STR_OS_LOWBAT,REGION2,0,0);
    		lowbat_timer++;
            regs0->gpio_out[CTR_GLED_GPIO/16]|= (1 << (CTR_GLED_GPIO % 16));  //CTR_GLED->H,GREEN LED OFF
            regs0->gpio_out[DSP_RLED_GPIO/16]&= ~(1 << (DSP_RLED_GPIO % 16)); //DSP_RLED->L,RED LED GLITTER ON
    	}	
    	else
    	{
    		if((lowbat_timer>=100) & (lowbat_timer<150))
    		{
    			ClearOsdMsg(2);
    			lowbat_timer++;
                regs0->gpio_out[DSP_RLED_GPIO/16]|= (1 << (DSP_RLED_GPIO % 16));  //DSP_RLED->H,RED LED GLITTER OFF
    		}	
    		else	
    			lowbat_timer=0;
    	}	
    }	
#endif //end #ifdef GBM_PORTABLE_DVD
}
#endif
     
#ifdef PDVD_USE_IO_SCAN_KEY
    
#ifdef APEX_PORTABLE_DVD  //liulilifeng add for apex portable dvd eth1007

const BYTE gpio[5]={KEY_A,KEY_B,KEY_C,KEY_D,KEY_E};

void check_portable_key(void)
{
    BYTE i,j,keydata,press_key=0;
    static BYTE keyprev=0;
    #ifdef HOLD_KEY_DETECT
    if(hold_state)
        return;
    #endif

    //GPIO_E_SET (23 , 1 );
    //GPIO_O_SET (23 , 1 );

    for (i=5;i>0;i--)
    {

        for (j=0;j<5;j++)
        {
            if ( j<i )
                GPIO_E_SET( gpio[j] , 0); //set as input port
            else if (j>i)
            {
                GPIO_E_SET( gpio[j] , 1); //set as output port
                GPIO_O_SET( gpio[j] , 1);
            }
            else
            {
                GPIO_E_SET( gpio[j] , 1); //set as output port
                GPIO_O_SET (gpio[j] , 0);
            }

        }
       
        for (j=0;j<i;j++)
        {
            keydata = GPIO_I_GET( gpio[j] );
            if (keydata ==0 )
            {
                press_key =1;
                keydata = i*5 + j;
                if (keyprev != keydata)
                {
                    keyprev = keydata;
                    call_ir_func(vfd_keycode[keydata - 1]);
                    printf ("key %d x,y %d ,%d \n",keydata , i , j );
                }
                
            }
        }
        if (press_key ==1 )
            break ;
    }

    for (j=0;j<5;j++)
    {
        GPIO_E_SET (gpio[j] , 1);
        GPIO_O_SET (gpio[j] , 1);
    }
    
  	if(press_key==0) keyprev=0;
}

#elif defined(MUSTEK_K100D_MODEL)
/*
by justin 2005/09/08
from here to end this function is change to let keyboard used.
*/

#define LONG_PRESS_KEY_TIME  5   ///10  
const BYTE gpio[6]={31,33,39,40,30,32};
#ifdef IO_CHECK_DELAY
#define MAX_DELAY_CNT   30
#endif

void check_portable_key(void)
{
    BYTE i,j,k,keydata,unuseful,press_key=0;
    static BYTE keyprev=0;
    static BYTE olddata=0;
    static BYTE key_press_times=0;	
        	        
	GPIO_M_SET(31,1);
	GPIO_M_SET(33,1);
	GPIO_M_SET(39,1);
	GPIO_M_SET(40,1);
	GPIO_M_SET(30,1);
	GPIO_M_SET(32,1);

	GPIO_E_SET(31,1);
	GPIO_E_SET(33,1);
	GPIO_E_SET(39,1);
	
	GPIO_E_SET(40,0);
	GPIO_E_SET(30,0);
	GPIO_E_SET(32,0);
	
    #ifdef HOLD_KEY_DETECT
    if(hold_state)
        return;
    #endif
    
    //gpio confgi should move to reset_gpio_portable()!!!
    //regs0->sft_cfg0 &=~((0x01)<<4); //GPIO39(Pin162)Disable M_DQM2 and enable
    
    //1.100 maybe is too lagrge!!!
    //2.delay should be not in here!!!
    //for(unuseful=0;unuseful<100;unuseful++);
    //delay key scan 
    // for the program  run  too fast  
    //regs0->sft_cfg1 &= ~(0x7 << 9); //gpio 33(pin 155)
    //for(unuseful=0;unuseful<100;unuseful++);
    
    regs0->sft_cfg1 &= ~(0x7 << 9); //gpio33(pin 155)
    
	for(i=0;i<3;i++)
	{
	    for(j=0;j<3;j++)
		    GPIO_O_SET(gpio[j],1);
        
	    GPIO_O_SET(gpio[i],0);
	    
	    //delay....
	    #ifdef IO_CHECK_DELAY
	    for(unuseful=0;unuseful<MAX_DELAY_CNT;unuseful++);
	    #endif
	    
  	    for(k=3;k<6;k++)
  		{  		 
        	keydata=GPIO_I_GET(gpio[k]);
    		if(keydata==0)
    		{    	       	  
    			press_key=1;
    	
              	keydata=i*3+(k-3)+1;    	
//by justin 2005/10/21 press a key for a long time , system do it again
			    if(keydata==olddata)
    			{
    			    key_press_times++;
    			}
    			else
    			{
    			    key_press_times=0;
    				olddata=keydata;
    			}
              	
    			if((keyprev!=keydata)||(key_press_times>LONG_PRESS_KEY_TIME))
    			{    			  			
    			    BYTE temp;
    			    key_press_times=0;
    			    keyprev=keydata;
    			    temp=vfd_keycode[keydata - 1];
    			    //by justin 2005/11/01  the same key on panel have different name in different mode
			        if(source_play_mode==DVB_T_MODE)
					{	
						if(temp==IRC_FORWARD)temp=IRC_NEXT;
						if(temp==IRC_BACKWARD)temp=IRC_PREV;
					}
			        
			        #ifdef SUPPORT_8202_DVB
	                if(Is_Dvb_State())
	                    Dvb_ircmd_pre_parser(temp);
    		        else
                    #endif //SUPPORT_8202_DVB
			        call_ir_func(temp);

    		       // call_ir_func(vfd_keycode[keydata - 1]);
    	            //printf("key %d SW %d,%d.\n",keydata,i,k-4);
    	            //call_ir_func(IRC_VOLUME_UP);
                    //printf("key %d SW %d,%d.\n",keydata,i,k-3);
                      		

    	        }  
    			break;
    		}    		    		
  		}  		
  	}
  	if(press_key==0) 
  	{
  		keyprev=0;
  		key_press_times=0;
  		olddata=0;
  	}
  	
  	/*.......................................................................................................
    by justin 2005/09/012
    key_board_power  
    .........................................................................................................*/
    if(IunTestPin84>=2)
    {
        GPIO_E_SET(POWER_KEY_GPIO,0);
        //QiaoHuilin:2005-10-21
	    if(GPIO_I_GET(POWER_KEY_GPIO))while(1)
	    	call_ir_func(IRC_POWER);
	///////////////////////////////////////////////////////////////////////////
	}    
    
}

#else //#ifdef APEX_PORTABLE_DVD 
   
const BYTE gpio[8]={46,47,48,49,50,51,52,18};
#ifdef USE_COMBINED_KEY
#define LONG_PRESS_KEY_TIME 12  
#endif
    
//#define PORTABLE_IOKEY_DEBUG
        
void check_portable_key(void)
{
#ifdef USE_COMBINED_KEY
    BYTE i,j,keydata;
    static BYTE column_dot = 4;
    static BYTE row_dot = 0;
    static BYTE keyprev = 0;
    static BYTE key_press_times = 0 ;

    #ifdef HOLD_KEY_DETECT
    if(hold_state)
        return;
    #endif
	
    regs0->gpio_oe[3]&= 0xffcf;     //jhuang org 011f
    
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
          GPIO_O_SET(gpio[j],1);
          
        GPIO_O_SET(gpio[i],0);
    
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
                    #ifdef D02_9_10INCH
                    if((keydata == 8) || (keydata == 10))
                    #else 
                    if((keydata == 4) || (keydata == 6)
                        #ifdef D02_A_10INCH
                        ||(keydata == 10) || (keydata == 16)
                        #endif
                      )
                    #endif
                    {
                        key_press_times++;
                        #ifdef PORTABLE_IOKEY_DEBUG
                        printf("key press times:---->%d\n",key_press_times);
                        #endif
                    }
                }           
                break;
            }
            else if((j == column_dot) && (i == row_dot) && (keyprev != 0))
            {//key is released
                if(key_press_times >= LONG_PRESS_KEY_TIME)
                {//long press key 
                    #ifdef PORTABLE_IOKEY_DEBUG
                    printf("call long key:%d!press %d times\n",keyprev,key_press_times);
                    #endif  
                 
                    #ifdef D02_9_10INCH
                    if(keyprev == 8)
                    #else
                    if(keyprev == 4)
                    #endif
                    {
                        #ifdef D02_A_10INCH
                        call_ir_func(IRC_LEFT); 
                        #else
                        call_ir_func(IRC_PREV); 
                        #endif
                    }
                    else
                    {
                        #ifdef D02_A_10INCH
                        if(keyprev == 10)
                            call_ir_func(IRC_DOWN);
                        else if (keyprev == 16)
                            call_ir_func(IRC_UP); 
                        else
                            call_ir_func(IRC_RIGHT);
                        #else
                        call_ir_func(IRC_NEXT);
                        #endif
                    }
              }
              else
              {//short key press
                  call_ir_func(vfd_keycode[keyprev - 1]);
                  #ifdef PORTABLE_IOKEY_DEBUG
                  printf("call short key:%d\n",keyprev);
                  #endif
              }
              
              key_press_times = 0;
              keyprev = 0;
              column_dot = 4;
              row_dot = 0;
           } 
        }       
    }
#else
    BYTE i,j,k,keydata,press_key=0;
    static BYTE keyprev=0;
	
    #ifdef HOLD_KEY_DETECT
    if(hold_state)
        return;
    #endif
    
    regs0->gpio_oe[3]&= 0xffcf;     //jhuang org 011f
	
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
    			if(keyprev!=keydata)
    			{    			  			
    			    keyprev=keydata;
    			    call_ir_func(vfd_keycode[keydata - 1]);
    			    printf("key %d SW %d,%d.\n",keydata,i,k-4);
    			}  
    			break;
    		}    		    		
  		}  		
  	}
  	if(press_key==0) keyprev=0;
#endif //end #ifdef USE_COMBINED_KEY

}
#endif//#else //#ifdef APEX_PORTABLE_DVD 
#endif //#ifdef PDVD_USE_IO_SCAN_KEY


//Jack added 05/11/29 for PollingSpecifiedKeys() use when in MP4 file init state.
UINT16 GetPanelKeyCode(void)
{//panel keys check...... pls add,because different customers have different key-detect array!!!
    UINT16 iRet = IR_CODE_MAX_NUM;
    
    #if defined(MUSTEK_K100D_MODEL)
    {
        GPIO_M_SET(POWER_KEY_GPIO,1);
        GPIO_E_SET(POWER_KEY_GPIO,0);
        
        if(GPIO_I_GET(POWER_KEY_GPIO))
            iRet = IRC_POWER;
    }
    
    #endif
        
    return iRet;
}

UINT16 get_portable_panel_key(void)
{
    UINT16 iRet = IR_CODE_MAX_NUM;
        
    BYTE temp __UNUSED =0;
    
    //Cover SW check......
    #ifdef CHECK_PORTABLE_OPCLSW
    
    #if defined(MUSTEK_K100D_MODEL)
    {
        
    }
    #elif 0//defined()
    {
        
    }
    #else
    {
        #ifdef SUNPLUS_8202P_DEMOBOARD
        regs0->sft_cfg4 &= ~((0x03)<<2);    //Enable GPIO2,3 For COVER & TFT SW
        #endif
    
        GPIO_M_SET(PDVD_OPCLSW_GPIO,1);
        GPIO_O_SET(PDVD_OPCLSW_GPIO,0);
    
        temp=GPIO_I_GET(PDVD_OPCLSW_GPIO);
    
        if(temp)
        {
            if(!CDOpened())
                iRet = IRC_EJECT;
        
        }
    }
    #endif
    
    #endif
    
    //panel keys check......
    if(iRet != IRC_EJECT)
        iRet = GetPanelKeyCode();
    
    return iRet;
}

#if defined(CHECK_PORTABLE_OPCLSW)/*||defined(TOP_DOOR_LOADER)*/
BYTE  check_eject_sw(void);
BYTE  check_eject_sw(void)
{
      return  GPIO_I_GET(PDVD_OPCLSW_GPIO);
}
#endif

#ifdef  SUPPORT_DVD_POWER_ONOFF
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

