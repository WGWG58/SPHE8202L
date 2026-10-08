

#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
//Qiaohuilin:2005-9-22
#ifdef MUSTEK_LCD_DRIVE_BITEK
#include "LCD\OSD.h"
#include "LCD\YUV.H"
#endif
/**************************************************************************
 *  Function Name: ircmd_dvd_usb_card_avin_dvb                            *
 *  Purposes:                                                             *
 *    Switch Media play between DVD,USB,Card,AV_IN and DVB-T              *
 *  Descriptions:                                                         *
 *    1.If you use this function,system will not automatically detect USB *
 *    or Card.                                                            *
 *    2.You can freely switch system between the state below:DVD,USB,Card,*
 *    AV_IN and DVB-T in this function.                                   *
 *  Arguments:                                                            *
 *    NULL                                                                *
 *  Returns:                                                              *
 *    NULL                                                                *
 **************************************************************************/
 #ifdef FIX_STATE_CHANE_NOT_READ_USB  
 extern  void force_detached();
 #endif// end=>  #ifdef FIX_STATE_CHANE_NOT_READ_USB 
 #ifdef SUPPORT_DVB_DESKTOP_STOP_SERVO_WHEN_TUNEON  //yangli add for usb ,card stop servo,2006-2-16 16:30,
 extern int stop_servo_flag;
 #endif
#ifdef SUPPORT_DVB_BOOKING
extern UINT8 iCountTime;
#endif 
void ircmd_dvd_usb_card_avin_dvb(void)
{
    if(prog_cnt)  ///yangli ,2006-2-27 23:07
    {
        prog_cnt = 0; 
        prog_func_clear();  
    }
    printf_w("----------yang li 1 = %d --------\n",source_play_mode);
    #ifdef MODE_SWITCH_DELAY
   // if(usb_card_state == USB_CARD_WAS_PLUG_OUT)
     //   return;
        //counter_down = 2; 
    mode_key_delay_cnt = 3;//MODE_DELAY_CNT;
    #endif
    
    #ifdef SUPPORT_DVB_BOOKING
    if(iCountTime>0)
        return;
    #endif
    
    //by justin 2005/11/15   close the setup_menu if you want to change mode and setup menu is openning
	if(full_scrn&SETUP) 
	    ExitSetupPage(1);	
    
    //Jack highly notes:in reading CD/DVD TOC state ,we should not let this key can change system state!!
    //Otherwise will cause some inexplicable issues.
    #ifdef MUSTEK_K100D_MODEL
    if( (source_play_mode==DVD_PLAY_MODE) && ((system_state==SYSTEM_READ_TITLE)||((system_state==SYSTEM_OPEN)/*&&(play_state==VCD_STATE_CLOSE)*/)) )
    #else
     if( (source_play_mode==DVD_PLAY_MODE) && ((system_state==SYSTEM_READ_TITLE)||(CDOpened())/*||((system_state==SYSTEM_OPEN)&&(play_state==VCD_STATE_CLOSE))*/) )
    #endif
        return;
    
    GPIO_MUTE();
            
	if(source_play_mode == DVD_PLAY_MODE)
    {
        osd_clear_and_init();

   
       #ifdef SUPPORT_DVD_TO_USB_CARD_DVB_ENABLE_RESUME//tianye 200607
	  #ifdef SUPPORT_LAST_MEMERY
	   if(memery_resumeflag)
    	  #endif//end=> #ifdef SUPPORT_LAST_MEMERY
         {
            RsmInfo2Flash(0);
         }
	 #endif//end=> #ifdef SUPPORT_DVD_TO_USB_CARD_DVB_ENABLE_RESUME	 
	 //-------------------------------------------

		
        #ifdef STOP_LOADER
        //Jack marked "If" 06/02/20 
        //if( !((play_state==VCD_STATE_OPEN) || ((play_state==VCD_STATE_STOP)&&!resumeMSF) || (system_state==SYSTEM_NODISC)) )
	    {
	        delay_srv_10ms(5);
            #ifdef TRAY_AVAILABLE//It seems that this will cause some servo bug,so markd again 06/02/22
            stop_loader();
            #endif
            delay_srv_10ms(5);
            
        }
        #endif
        
        if(system_state != SYSTEM_OPEN)
        {
		    AVD_SetMediaTimeout();
		    ircmd_post_func(CMD_FUNC|CMD_FUNC_OPEN);
		}
		
		#ifdef TRAY_AVAILABLE
		if(CDOpened())
		{
		    close_tray(1);
		    delay_srv_10ms(300);
		    printf_w("here  2=\n");
		}
		#endif
		
		#ifdef SUPPORT_DVB_DESKTOP_STOP_SERVO_WHEN_TUNEON  ///YANGLI ADD FOR STOP SERVO,2005-12-28 15:00
        atapi_p_start_stop_unit(4);
        stop_servo_flag = 1;
        #endif 
		

		#ifdef FIX_CARD_USD_OSD_ERR  
		polling_storage();
        #endif// end=>  #ifdef FIX_CARD_USD_OSD_ERR 

        #ifdef NO_USB_NO_CARD
		ircmd_dvb_dvd();
		#else
		switch_usb_card();
		#endif
		#ifdef FIX_STATE_CHANE_NOT_READ_USB  
		force_detached();
        #endif// end=>  #ifdef FIX_STATE_CHANE_NOT_READ_USB 
        #ifdef ONLY_CARD_NO_USB
        source_play_mode = CARD_PLAY_MODE;
        #elif defined(NO_USB_NO_CARD)
		source_play_mode = DVB_T_MODE;  
        #else
		source_play_mode = USB_PLAY_MODE;  
		#endif 
    }
	else if(source_play_mode == USB_PLAY_MODE)
    {           	
       	
		osd_clear_and_init();
		#ifdef ONLY_USB_NO_CARD
		ircmd_dvb_dvd();
		source_play_mode = DVB_T_MODE;
		#else
		switch_usb_card();
		source_play_mode = CARD_PLAY_MODE;	
		#endif
		
	}
	else if(source_play_mode == CARD_PLAY_MODE)
    #ifdef AV_IN_THROUGH_EXT_ADC
    {              
		osd_clear_and_init();
		
		ircmd_post_func(CMD_FUNC|CMD_FUNC_OPEN);
  	    //play_state = VCD_STATE_NORMAL;
	    //psprintf(RegionValStr[REGION2], "AV IN STATE");
        //PrintOsdMsg(STR_OS_SPACE, REGION2, 3, 1);
        
        source_play_mode = AV_IN_MODE;
        if(!(detect_type&0x1e))
        {
            system_state = SYSTEM_AVIN;
            usb_card_state = USB_CARD_NO_CHANGE;
            mode_switch_reset_var();
        }
        else
            usb_card_state = FROM_CARD_TO_AV_IN;
        
        //QiaoHuilin:2005-9-22
        #ifdef MUSTEK_LCD_DRIVE_BITEK
	    YUV_SetSourceMode(YUV_ID_CVBS_11);
        //	POR_PowerOn();//Sunpluss  advice      	
	    OSD_ShowMsg(OSD_MESSAGE,0,0,"    AV IN");
	    OSD_EnableWindow(OSD_MESSAGE, TRUE);  
	    if(user_mute)
		    LCD_ShowMuteIcon();  
        #endif
    }
	else if(source_play_mode == AV_IN_MODE)
	#endif
	{
	    enable_video_DAC_out(1);
	    ircmd_dvb_dvd();
	    source_play_mode = DVB_T_MODE;
	    //QiaoHuilin:2005-9-22
        #ifdef MUSTEK_LCD_DRIVE_BITEK
	    YUV_SetSourceMode(YUV_ID_YCBCR);
	    OSD_ShowMsg(OSD_MESSAGE,0,0,"      DVB");
	    OSD_ShowMsg(OSD_MESSAGE,0,1,"         ");
	    OSD_EnableWindow(OSD_MESSAGE, TRUE);  
        #endif
	}
	else if(source_play_mode == DVB_T_MODE)
	{//switch to DVD play mode
	    printf_w("====source_play_mode == dvb_t_mode ====\n");
	    volatile int *iMagic=(int *)(DATA_RAM_BASE|0xa0); ///yangli ,2006-2-20 19:56
        *iMagic = 0xff;
		ircmd_dvb_dvd();
	    source_play_mode = DVD_PLAY_MODE;
	    #ifdef MODE_SWITCH_DELAY///YANGLI ,2006-2-22 23:18
           mode_key_delay_cnt = 10;
        #endif
	    no_disk_cnt = DETECT_TIMES;
        media_type = MEDIA_CD;
		if(play_state != VCD_STATE_OPEN)//20051230 tiany add
            PrintOsdMsg(STR_OS_READ,REGION1,0,0);
        //QiaoHuilin:2005-9-22
        #ifdef MUSTEK_LCD_DRIVE_BITEK
	    YUV_SetSourceMode(YUV_ID_YCBCR);
	    OSD_ShowMsg(OSD_MESSAGE,0,0,"         ");
	    OSD_EnableWindow(OSD_MESSAGE, FALSE);  
        #endif
	}
	
	#ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB	
	printf_w("now system play mode--->%d\n",source_play_mode);
	#endif
}

/**************************************************************************
 *  Function Name: switch_usb_card                                        *
 *  Purposes:                                                             *
 *    Switch Media play only between USB and Card                         *
 *  Descriptions:                                                         *
 *    Called by ircmd_dvd_usb_card_avin_dvb()                             *
 *  Arguments:                                                            *
 *    NULL                                                                *
 *  Returns:                                                              *
 *    NULL                                                                *
 **************************************************************************/

#ifdef ONLY_CARD_NO_USB
void switch_usb_card(void)
{
    	if(/*(detect_result_last == 0x01)||*/(source_play_mode==DVD_PLAY_MODE))//when play USB
	{
	   	if(!(detect_type&0x1e))
	    {
	       	if((detect_type&USB_DEVICE) && (system_state==SYSTEM_BROWSE))
	       	{
	       	    AVD_SetMediaTimeout();
	       	    ircmd_post_func(CMD_FUNC | CMD_FUNC_OPEN);
	       	}
	       	
	       	psprintf(RegionValStr[REGION1], "CARD NOT FOUND");
	        PrintOsdMsg(STR_OS_SPACE, REGION1, 2, 1);
	        usb_card_state = SWITCH_TO_CARD_BUT_HAS_NO_CARD;
	    }
	    else
	    {
	        #ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
	       	printf_w("has Card in............\n");
            #endif
            
            now_valid_type = (detect_type & 0x1e);
            storage_type = now_valid_type;
            detect_result_last = storage_type;
            
	        SwitchMedia(CARD2CARD);
	        usb_card_state = HAS_CARD_AND_SWITCH_TO_CARD;
	    }
	}   
}
#elif defined(ONLY_USB_NO_CARD)
void switch_usb_card(void)
{
    if(source_play_mode == DVD_PLAY_MODE)
	{
	   	if( !(/*IsCardMediaExist()&&*/(detect_type&USB_DEVICE)) )
	    {
	       	psprintf(RegionValStr[REGION1], "USB NOT FOUND");
	        PrintOsdMsg(STR_OS_SPACE, REGION1, 2, 1);
	        
	        usb_card_state = SWITCH_TO_USB_BUT_HAS_NO_USB;
	        media_type = MEDIA_CARD;
	        cd_type_loaded = CDUNKNOWN;
            play_state = VCD_STATE_IDLE;
            no_disk_cnt = DETECT_TIMES;
	    }
	    else 
        {   
	        #ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
	       	printf_w("has USB in............\n");
            #endif
            
	       	now_valid_type = USB_DEVICE;
	       	storage_type = USB_DEVICE;
            detect_result_last = storage_type;

	       	SwitchMedia(CD2CARD);
	       	usb_card_state = HAS_USB_AND_SWITCH_TO_USB;
        }   
	}     
}
#else//#ifdef ONLY_CARD_NO_USB//tianye 200607
#ifdef    SUPPORT_OTHER_LANGUAGE_STRING
extern    const char *const osd_other_str[N_OSD_LANGS][STRINE_NUM];
#endif //end=> #ifdef    SUPPORT_OTHER_LANGUAGE_STRING
void switch_usb_card(void)
{
    #ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
    printf_w("media_type:%d...detect_result_last:%d...now_valid_type:%d...\n",media_type,detect_result_last,now_valid_type);
    printf_w("detect_type:%d............storage_type:%x\n",detect_type,storage_type);
    #endif
    
    media_type = MEDIA_CARD;
    if(source_play_mode == DVD_PLAY_MODE)
	{
	   	if( !(/*IsCardMediaExist()&&*/(detect_type&USB_DEVICE)) )
	    {

		     #ifdef SUPPORT_OTHER_LANGUAGE_STRING//tianye 200607
			psprintf(RegionValStr[REGION1], osd_other_str[osd_font_mode][USB_NOT_FOUND]); 
		     #else //else => #ifdef    SUPPORT_OTHER_LANGUAGE_STRING	 
	       	psprintf(RegionValStr[REGION1], "USB NOT FOUND");
		     #endif//end=> #ifdef    SUPPORT_OTHER_LANGUAGE_STRING	
	        PrintOsdMsg(STR_OS_SPACE, REGION1, 2, 1);
	        
	        usb_card_state = SWITCH_TO_USB_BUT_HAS_NO_USB;
	        media_type = MEDIA_CARD;
	        cd_type_loaded = CDUNKNOWN;
            play_state = VCD_STATE_IDLE;
            no_disk_cnt = DETECT_TIMES;
	    }
	    else 
        {   
	        #ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
	       	printf_w("has USB in............\n");
            #endif
            
	       	now_valid_type = USB_DEVICE;
	       	storage_type = USB_DEVICE;
            detect_result_last = storage_type;

	       	SwitchMedia(CD2CARD);
	       	usb_card_state = HAS_USB_AND_SWITCH_TO_USB;
        }   
	}  
	else if(/*(detect_result_last == 0x01)||*/(source_play_mode==USB_PLAY_MODE))//when play USB
	{
	   	if(!(detect_type&0x1e))
	    {
	       	if((detect_type&USB_DEVICE) && (system_state==SYSTEM_BROWSE))
	       	{
	       	    AVD_SetMediaTimeout();
	       	    ircmd_post_func(CMD_FUNC | CMD_FUNC_OPEN);
	       	}
	       	

			#ifdef    SUPPORT_OTHER_LANGUAGE_STRING//tianye 200607
			 psprintf(RegionValStr[REGION1], osd_other_str[osd_font_mode][CARD_NOT_FOUND]); 
		    #else //else => #ifdef    SUPPORT_OTHER_LANGUAGE_STRING	 
	       	 psprintf(RegionValStr[REGION1], "CARD NOT FOUND");
		    #endif//end=> #ifdef    SUPPORT_OTHER_LANGUAGE_STRING	

	        PrintOsdMsg(STR_OS_SPACE, REGION1, 2, 1);
	        usb_card_state = SWITCH_TO_CARD_BUT_HAS_NO_CARD;
	    }
	    else
	    {
	        #ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
	       	printf_w("has Card in............\n");
            #endif
            
            now_valid_type = (detect_type & 0x1e);
            storage_type = now_valid_type;
            detect_result_last = storage_type;
            
	        SwitchMedia(CARD2CARD);
	        usb_card_state = HAS_CARD_AND_SWITCH_TO_CARD;
	    }
	}   
}
#endif//#ifdef ONLY_CARD_NO_USB


/**************************************************************************
 *  Function Name: osd_clear_and_init                                     *
 *  Purposes:                                                             *
 *    Just as the function name.                                          *
 *  Descriptions:                                                         *
 *                                                                        *
 *  Arguments:                                                            *
 *    NULL                                                                *
 *  Returns:                                                              *
 *    NULL                                                                *
 **************************************************************************/

void osd_clear_and_init(void)
{
    if(full_scrn&SETUP)
        ExitSetupPage(0);
    
    full_scrn = 0;  
	t_disp = 0;    
    ClearOsdMsg(0);
    osd_init();
    osd_tog_region(2,OSD_OFF);
}
    
/**************************************************************************
 *  Function Name: mode_switch_reset_var                                  *
 *  Purposes:                                                             *
 *    reset some system variables when switch mode.                       *
 *  Descriptions:                                                         *
 *    Copy from stop_init()                                               *
 *  Arguments:                                                            *
 *    NULL                                                                *
 *  Returns:                                                              *
 *    NULL                                                                *
 **************************************************************************/

void mode_switch_reset_var(void)
{
    
#ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
    printf_w("reset_mode_var\n");
#endif
    
#ifdef  SUPPORT_BOOK
    extern BYTE    bookIndex;
    bookIndex=0;
#endif

    index_y=0;
    
    adv_search_time = 0 ;
    video_slow=0;
    avd_slow_state(video_slow);
    avd_play_state();
    goto_active = 0;
    bIntro=0;  

    
    reset_status();  

    prog_func_clear(); 
    resumeMSF = 0;
    resumeTRK = 0;

    rep_track = 0;
}


#ifdef  SUPPORT_DVD_DVB_USB_CARD_FREE_CHANGE //tianye 200607

#define CARD_DEVICE   0x1e

void   DVB_TO_DVD_NO_READ(void);
void   DVD_TO_USB(void);
void   DVD_TO_CARD(void);
void   USB_CARD_TO_DVD(void);
void   DVD_TO_STOP(void);
void  SYSTEM_CHANGE_TO_DVD(void);
void  SYSTEM_CHANGE_TO_DVB(void);
void  SYSTEM_CHANGE_TO_USB(void);
void  SYSTEM_CHANGE_TO_CARD(void);
void  SYSTEM_SOURCE_CHANGE(UINT8  sys_source_tpye);

void   DVD_TO_STOP()
{
	osd_clear_and_init();
	#ifdef STOP_LOADER
	//Jack marked "If" 06/02/20 
	//if( !((play_state==VCD_STATE_OPEN) || ((play_state==VCD_STATE_STOP)&&!resumeMSF) || (system_state==SYSTEM_NODISC)) )
	{
		delay_srv_10ms(5);
		//printf_w("START_STOP_DO_LOAD_POWER_OFF............\n");
		//Jack modified to atapi_p_start_stop_unit(Immed_1,START_STOP_DO_LOAD_POWER_OFF) 06/02/20
		#if 0//def TRAY_AVAILABLE//It seems that this will cause some servo bug,so markd again 06/02/22
		atapi_p_start_stop_unit(START_STOP_DO_LOAD_POWER_OFF);
		#else
		stop_loader();
		#endif
		delay_srv_10ms(100);
	}
	#endif

	//if(system_state != SYSTEM_OPEN)
	{
		AVD_SetMediaTimeout();
		ircmd_post_func(CMD_FUNC|CMD_FUNC_OPEN);
	}

	#ifdef TRAY_AVAILABLE
	if(CDOpened())
	{
		close_tray(1);
		delay_srv_10ms(100);
	}
	#endif

	#ifdef SUPPORT_DVB_DESKTOP_STOP_SERVO_WHEN_TUNEON  ///YANGLI ADD FOR STOP SERVO,2005-12-28 15:00
		atapi_p_start_stop_unit(4);
		stop_servo_flag = 1;
	#endif 

}


void   DVB_TO_DVD_NO_READ()
{    
         flag_no_check_servo = 1;
	  system_state = SYSTEM_TS ;
         ircmd_dvb_dvd();
         flag_no_check_servo =  0;
}
void   DVD_TO_USB()
{
	DVD_TO_STOP();
	#ifdef FIX_CARD_USD_OSD_ERR  
	polling_storage();
	#endif// end=>  #ifdef FIX_CARD_USD_OSD_ERR 

	#ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
	printf_w("media_type:%d...detect_result_last:%d...now_valid_type:%d...\n",media_type,detect_result_last,now_valid_type);
	printf_w("detect_type:%d............storage_type:%x\n",detect_type,storage_type);
	#endif
    
	media_type = MEDIA_CARD;
	source_play_mode=USB_PLAY_MODE;
	
	if( !(/*IsCardMediaExist()&&*/(detect_type&USB_DEVICE)) )
	{
		if((detect_type&CARD_DEVICE) && (system_state==SYSTEM_BROWSE))
		{
			AVD_SetMediaTimeout();
			ircmd_post_func(CMD_FUNC | CMD_FUNC_OPEN);
		}
		
		#ifdef    SUPPORT_OTHER_LANGUAGE_STRING
		psprintf(RegionValStr[REGION1], osd_other_str[osd_font_mode][USB_NOT_FOUND]); 
		#else //else => #ifdef    SUPPORT_OTHER_LANGUAGE_STRING	 
		psprintf(RegionValStr[REGION1], "USB NOT FOUND");
		#endif//end=> #ifdef    SUPPORT_OTHER_LANGUAGE_STRING	
		PrintOsdMsg(STR_OS_SPACE, REGION1, 2, 1);

		usb_card_state = SWITCH_TO_USB_BUT_HAS_NO_USB;
		media_type = MEDIA_CARD;
		cd_type_loaded = CDUNKNOWN;
		play_state = VCD_STATE_IDLE;
		no_disk_cnt = DETECT_TIMES;
	}
	else 
	{   
		#ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
		printf_w("has USB in............\n");
		#endif
            
		now_valid_type = USB_DEVICE;
		storage_type = USB_DEVICE;
		detect_result_last = storage_type;

		SwitchMedia(CD2CARD);
		usb_card_state = HAS_USB_AND_SWITCH_TO_USB;
	}   
	#ifdef FIX_STATE_CHANE_NOT_READ_USB  
	force_detached();
	#endif// end=>  #ifdef FIX_STATE_CHANE_NOT_READ_USB 
	source_play_mode=USB_PLAY_MODE;   
}
void   DVD_TO_CARD()
{
	DVD_TO_STOP();
	#ifdef FIX_CARD_USD_OSD_ERR  
	polling_storage();
	#endif// end=>  #ifdef FIX_CARD_USD_OSD_ERR 

    	#ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
    	printf_w("media_type:%d...detect_result_last:%d...now_valid_type:%d...\n",media_type,detect_result_last,now_valid_type);
    	printf_w("detect_type:%d............storage_type:%x\n",detect_type,storage_type);
    	#endif
    
	media_type = MEDIA_CARD;
	
	if(!(detect_type&CARD_DEVICE))
	{
		if((detect_type&USB_DEVICE) && (system_state==SYSTEM_BROWSE))
		{
			AVD_SetMediaTimeout();
			ircmd_post_func(CMD_FUNC | CMD_FUNC_OPEN);
		}	       	

		#ifdef    SUPPORT_OTHER_LANGUAGE_STRING
		psprintf(RegionValStr[REGION1], osd_other_str[osd_font_mode][CARD_NOT_FOUND]); 
		#else //else => #ifdef    SUPPORT_OTHER_LANGUAGE_STRING	 
		psprintf(RegionValStr[REGION1], "CARD NOT FOUND");
		#endif//end=> #ifdef    SUPPORT_OTHER_LANGUAGE_STRING	

	        PrintOsdMsg(STR_OS_SPACE, REGION1, 2, 1);
	        usb_card_state = SWITCH_TO_CARD_BUT_HAS_NO_CARD;
	}
	else
	{
		#ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
		printf_w("has Card in............\n");
		#endif
            
		now_valid_type = (detect_type & CARD_DEVICE);
		storage_type = now_valid_type;
		detect_result_last = storage_type;

		SwitchMedia(CARD2CARD);
		usb_card_state = HAS_CARD_AND_SWITCH_TO_CARD;
	}
	
	#ifdef FIX_STATE_CHANE_NOT_READ_USB  
	force_detached();
	#endif// end=>  #ifdef FIX_STATE_CHANE_NOT_READ_USB 
	source_play_mode=CARD_PLAY_MODE;
	 
}

void   USB_CARD_TO_DVD()
{
	if(((detect_type&USB_DEVICE)||(detect_type&CARD_DEVICE)) && (system_state==SYSTEM_BROWSE))
	{
		AVD_SetMediaTimeout();
		//ircmd_post_func(CMD_FUNC | CMD_FUNC_OPEN);
		polling();
	}
       system_state = SYSTEM_OPEN;
	no_disk_cnt = DETECT_TIMES;
	media_type = MEDIA_CD;
	usb_card_state = USB_CARD_NO_CHANGE;
	mode_switch_reset_var();
	ShowTitle();
	#if defined(CHECK_PORTABLE_OPCLSW)||defined(TOP_DOOR_LOADER)
	regs0->sft_cfg4 &= ~((0x03)<<2);    //Enable GPIO For COVER SW

	if(check_eject_sw())
	{
		play_state = VCD_STATE_OPEN;
		ircmd_trayout();
	}
	else
	#endif//else close tray and read disc
	{
		atapi_open_tray();  //Maoyong 2004-8-10 11:00
		//atapi_close_tray(0);
		ircmd_trayin();
		play_state = VCD_STATE_CLOSE;   
	}		
	source_play_mode=DVD_PLAY_MODE;
}

void  SYSTEM_CHANGE_TO_DVD(void)
{
	switch(source_play_mode)
	{
		case CARD_PLAY_MODE:
		{
			USB_CARD_TO_DVD(); 			
			break; 
		}
		case DVB_T_MODE:
		{
			ircmd_dvd_usb_card_avin_dvb();
			break; 
		}
		case USB_PLAY_MODE:
		{
			USB_CARD_TO_DVD(); 
			break; 
		}		 
		default: 
			break; 
	}


}
void  SYSTEM_CHANGE_TO_DVB(void)
{	   
	switch(source_play_mode)
	{
		case DVD_PLAY_MODE:
		{
			GPIO_MUTE();
		       DVD_TO_STOP(); 
		       system_state = SYSTEM_OPEN; 	 
		      #ifdef AV_IN_THROUGH_EXT_ADC
			source_play_mode = AV_IN_MODE;
			#else//else=> #ifdef AV_IN_THROUGH_EXT_ADC
			source_play_mode = CARD_PLAY_MODE;
			#endif//end=> #ifdef AV_IN_THROUGH_EXT_ADC
		       ircmd_dvd_usb_card_avin_dvb();
			break; 
		}
		case CARD_PLAY_MODE:
		{
			system_state = SYSTEM_OPEN;  
		      #ifdef AV_IN_THROUGH_EXT_ADC
			source_play_mode = AV_IN_MODE;
			#else//else=> #ifdef AV_IN_THROUGH_EXT_ADC
			source_play_mode = CARD_PLAY_MODE;
			#endif//end=> #ifdef AV_IN_THROUGH_EXT_ADC
		       ircmd_dvd_usb_card_avin_dvb();
			break; 
		}
		case USB_PLAY_MODE:
		{
			system_state = SYSTEM_OPEN;  
		      #ifdef AV_IN_THROUGH_EXT_ADC
			source_play_mode = AV_IN_MODE;
			#else//else=> #ifdef AV_IN_THROUGH_EXT_ADC
			source_play_mode = CARD_PLAY_MODE;
			#endif//end=> #ifdef AV_IN_THROUGH_EXT_ADC
		       ircmd_dvd_usb_card_avin_dvb();
			break; 
		}		 
		default: 
			break; 
	} 		  

}
void  SYSTEM_CHANGE_TO_USB(void)
{
	switch(source_play_mode)
	{
		case DVD_PLAY_MODE:
		{
			DVD_TO_USB(); 			
			break; 
		}
		case DVB_T_MODE:
		{
			DVB_TO_DVD_NO_READ();
			DVD_TO_USB();
			break; 
		}
		case CARD_PLAY_MODE:
		{
			DVD_TO_USB(); 
			break; 
		}		 
		default: 
			break; 
	} 	 
}
void  SYSTEM_CHANGE_TO_CARD(void)
{
	switch(source_play_mode)
	{
		case DVD_PLAY_MODE:
		{
			DVD_TO_CARD(); 			
			break; 
		}
		case DVB_T_MODE:
		{
			DVB_TO_DVD_NO_READ();
			DVD_TO_CARD();
			break; 
		}
		case USB_PLAY_MODE:
		{
			DVD_TO_CARD(); 
			break; 
		}		 
		default: 
			break; 
	} 

}

void  SYSTEM_SOURCE_CHANGE(UINT8  sys_source_tpye)
{	 
       printf_w("  SYSTEM_SOURCE_CHANGE   sys_source_tpye:%d \n",sys_source_tpye);
	printf_w("  SYSTEM_SOURCE_CHANGE   system_state:%d \n",system_state);

	#ifdef MODE_SWITCH_DELAY
	if(usb_card_state == USB_CARD_WAS_PLUG_OUT)
	{
		return;
	}
	
	if(mode_key_delay_cnt)
	{
		//printf_w("mode_key_delay_cnt:%d,return............\n",mode_key_delay_cnt);
		invalid_key();
		return;
	}
	else
	{
		counter_down=5;   
		mode_key_delay_cnt = 2;
	}
	#endif//end=> 	#ifdef MODE_SWITCH_DELAY

    
   	 //by justin 2005/11/15   close the setup_menu if you want to change mode and setup menu is openning
	if(full_scrn&SETUP) 
	{
		ExitSetupPage(1);	
	}

	if( (source_play_mode==DVD_PLAY_MODE) && ((system_state==SYSTEM_READ_TITLE)/*||((system_state==SYSTEM_OPEN)&&(play_state==VCD_STATE_CLOSE))*/) )
    	{
        	return;
    	}
	
    	GPIO_MUTE();
		
           //  printf_w("  SYSTEM_SOURCE_CHANGE   start                \n");

	switch(sys_source_tpye)
	{
		case SYSTEM_TO_DVD:
		{
			if(source_play_mode!=DVD_PLAY_MODE)
			{
				SYSTEM_CHANGE_TO_DVD(); 			
			}
			break; 
		}
		case SYSTEM_TO_USB:
		{
			if(source_play_mode!=USB_PLAY_MODE)
			{
				SYSTEM_CHANGE_TO_USB();
			}
			break; 
		}
		case SYSTEM_TO_CARD:
		{
			if(source_play_mode!=CARD_PLAY_MODE)
			{
				SYSTEM_CHANGE_TO_CARD();
			}	
			break; 
		}
		case SYSTEM_TO_DVB:
		{
			if(source_play_mode!=DVB_T_MODE)
                     {
				SYSTEM_CHANGE_TO_DVB();
			}
			break; 
		}		 
		default: 
			break; 
	}   	

   printf_w("  SYSTEM_SOURCE_CHANGE      DVD2DVB_switch_flag:%d     source_play_mode:  %d    \n",DVD2DVB_switch_flag,source_play_mode);
   printf_w("  SYSTEM_SOURCE_CHANGE       system_state   :  %d     flag_check_mcu_info:%d  \n",system_state,flag_check_mcu_info);
}


#ifdef   SUPPORT_CHECK_MCU_INFO
#define CHECK_TIME 3
UINT8  a_info_old= 0;
UINT8  b_info_old= 0;
UINT8  check_con= 0;

void  check_mcu_info(void);
void  check_mcu_info()
{


	UINT8  a_info= 0;
	UINT8  b_info= 0;
	GPIO_M_SET(A_MCUINFO,1);
	GPIO_E_SET(A_MCUINFO, 0);  
	GPIO_M_SET(B_MCUINFO,1);
	GPIO_E_SET(B_MCUINFO, 0); 
	a_info = GPIO_I_GET(A_MCUINFO);
	b_info = GPIO_I_GET(B_MCUINFO);
#ifdef ONE_TWO_THREE_FOUR_CHANGE
	a_info =   xxx;
	b_info =  yyy;
#endif//end=> #ifdef ONE_TWO_THREE_FOUR_CHANGE

//	 printf_w("  11  waiting_mcu_info      a_info:%d     b_info:  %d     flag_check_mcu_info:%d  \n",a_info,b_info,flag_check_mcu_info);

       if((a_info == a_info_old)&&(b_info == b_info_old))  
       {
              if(check_con < 50)
              {
			check_con++;
              }	
	}
       else
       {
		a_info_old=a_info;
		b_info_old=b_info;
		check_con = 0;
	}
	   
       #ifdef SUPPORT_SYS_POWER_ON_WAITING_MCUINFO 
       if(!flag_check_mcu_info)
       {
	   return;
       }
 	#endif//end=> #ifdef  SUPPORT_SYS_POWER_ON_WAITING_MCUINFO

	if(check_con == CHECK_TIME)
	{
             printf_w(" 22   waiting_mcu_info      a_info:%d     b_info:  %d       \n",a_info,b_info);

		switch(a_info)
		{
	        	case 0:
			{
				if(b_info) //a_info: 0,b_info :1    => CARD  
				{
					SYSTEM_SOURCE_CHANGE(SYSTEM_TO_CARD); 	
				}
				else// //a_info: 0,b_info :0    =>  DVD
				{
					SYSTEM_SOURCE_CHANGE(SYSTEM_TO_DVD);                                    
				}
				break;
	        	}	
	              case 1:
			{
				if(b_info)//a_info: 1,b_info :1    =>  DVB
				{
					SYSTEM_SOURCE_CHANGE(SYSTEM_TO_DVB);				
				}
				else// //a_info: 1,b_info :0    =>  USB
				{
					SYSTEM_SOURCE_CHANGE(SYSTEM_TO_USB);
				}
				break;
	        	}	  	
			default:
				break;	

		}
	}
}
#endif//end=> #ifdef   SUPPORT_CHECK_MCU_INFO

#ifdef SUPPORT_SYS_POWER_ON_WAITING_MCUINFO 
void waiting_mcu_info(void);
void waiting_mcu_info2(void);
void waiting_mcu_info3(void);
void waiting_mcu_info()
{
       UINT8  a_info= 0;
	UINT8  b_info= 0;
       source_play_mode=DVD_PLAY_MODE;
	DVD_TO_STOP();
       while(check_con < CHECK_TIME)
      	{
            polling();
             
	}
       if(check_con == CHECK_TIME)
       {

	       
		GPIO_M_SET(A_MCUINFO,1);
		GPIO_E_SET(A_MCUINFO, 0);  
		GPIO_M_SET(B_MCUINFO,1);
		GPIO_E_SET(B_MCUINFO, 0); 
		a_info = GPIO_I_GET(A_MCUINFO);
		b_info = GPIO_I_GET(B_MCUINFO);
              printf_w("    waiting_mcu_info      a_info:%d     b_info:  %d       \n",a_info,b_info);
	    	//a_info  = 0;
		//b_info  = 0;		
		switch(a_info)
		{
	        	case 0:
			{
				if(b_info) //a_info: 0,b_info :1    =>  CARD 
				{
				       system_state = SYSTEM_DVD ;
					DVD2DVB_switch_flag = 0;
					source_play_mode=CARD_PLAY_MODE;
				}
				else// //a_info: 0,b_info :0    =>  DVD
				{
				       system_state = SYSTEM_DVD ;
					DVD2DVB_switch_flag = 0;
					source_play_mode=DVD_PLAY_MODE;
				}
				break;
	        	}	
	              case 1:
			{
				if(b_info)//a_info: 1,b_info :1    =>  DVB
				{
				       system_state = SYSTEM_TS ;
					DVD2DVB_switch_flag = 1;
					source_play_mode=DVB_T_MODE;
				}
				else// //a_info: 1,b_info :0    => USB
				{
				       system_state = SYSTEM_DVD ;
					DVD2DVB_switch_flag = 0;
					source_play_mode=USB_PLAY_MODE;
				}
				break;
	        	}	  	
			default:
				break;	

		}
				
	}

}
void waiting_mcu_info2()
{
	switch(source_play_mode)
	{
	       case DVD_PLAY_MODE:
		{
			ircmd_trayin();
			break;
        	}
        	case USB_PLAY_MODE:
		{
			DVD_TO_USB();
			break;
        	}	
              case CARD_PLAY_MODE:
		{
			DVD_TO_CARD();
			break;
        	}	  	
		default:
			break;	

	}
       flag_check_mcu_info =1; 
	ShowTitle();
	osd_enable();
}

void waiting_mcu_info3()
{
	flag_check_mcu_info = 0;    
       osd_disable();
}

  #endif//end=> #ifdef  SUPPORT_SYS_POWER_ON_WAITING_MCUINFO

#endif//end=> #ifdef  SUPPORT_DVD_DVB_USB_CARD_FREE_CHANGE //20060429 add





#endif//end #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB

//#ifdef AV_IN_THROUGH_EXT_ADC
/**************************************************************************
 *  Function Name: enable_video_DAC_out                                   *
 *  Purposes:                                                             *
 *    enable or disable 8200/8202 Video DAC output                        *
 *  Descriptions:                                                         *
 *                                                                        *
 *  Arguments:                                                            *
 *    enable_disable = 1------>Enable Video Out                           *
 *                   = 0------>Disable Video Out                          *
 *  Returns:                                                              *
 *    NULL                                                                *
 **************************************************************************/
void enable_video_DAC_out(BYTE enable_disable)
{
    if(enable_disable)
    {//enable 
        #ifdef SUPPORT_VIDEO_OUT_DELAY
		 tv_dacoff(TV_DAC_F|TV_DAC_E|TV_DAC_C);
        #else //else=>#ifdef SUPPORT_VIDEO_OUT_DELAY
        tv_dacoff(0);
	#endif

       
        //regs0->sft_cfg20 &=~(0x1<<0); //Marked by jack 05/09/19,Otherwise when switch to DVB state,system will has terrible "tsif_reg_wr() error!" error!
        //regs0->sft_cfg7 &=~(0x1<<4);
        //regs0->sft_cfg7 |=(0x1<<5);
    }
    else
    {//disable
        tv_dacoff(TV_DAC_F|TV_DAC_E|TV_DAC_D|TV_DAC_C|TV_DAC_B|TV_DAC_A);
        //regs0->sft_cfg20 |=(0x1<<0); 
        //regs0->sft_cfg7 |=(0x1<<4);
        //regs0->sft_cfg7 &=~(0x1<<5);
    }
}
//#endif

