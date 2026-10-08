/**************************************************************************
 * File Name:   ircmd_card.c
 * Created:     2004.05.19 13:36 Maoyong 
 * Description: contain some utilized functions for card switch or move/exist
                state check and so on
 *************************************************************************/
#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
#ifdef SUPPORT_USB
extern UINT32 UsbTestReady(void);
extern BYTE IsUSBCardReader(void);
extern UINT8 USBCheckNextReadyLun(void);
#ifdef ORITRON_HK_DVD  //qinhua add,
extern int program_func_flag;
#endif 
extern UINT8 CBWLUN;
#ifdef SWITCH_BETWEEN_USB_CARDS //for different cards swithch on USB card reader
#define MAX_USB_CARDS  4       //one port for SD/MS/SM/MMC, another for CF/Micro Driver(zhongshan modify for usb cardreader 4 port)
UINT8  card_switch_times = 0;   //record times switch between cards, if = 2, switch to CD
#endif  //#ifdef SWITCH_BETWEEN_USB_CARDS
#endif  //#ifdef SUPPORT_USB

extern BYTE ReadPercent;
extern CARD_FILE       cardFile;
extern void InitVar(void);
#ifdef IR_SWITCH_CARD_CD //lijd 2004-9-30 10:25
extern UINT8 atapi_p_start_stop_unit(UINT8 Immed,UINT8 start);
extern UINT8 USBCheckNextReadyLun(void);//zhongshan add 01/14
#endif

#ifdef SUPPORT_MP4_SUBTITLE	//yaowh add 2005-12-22 11:20
	//static int IsSubtitle = 0;	
	extern void supClearSubtitle(void);
#endif

#ifdef IR_SWITCH_CD_USB_CF_OTHER  //dingzhy 04-10-22
BYTE	now_valid_type = 0;
BYTE    detect_result_last = 0; 
extern void polling_storage(void);
#endif

#ifdef FILE_MODE_WRITE//added by wangwei,2005-1-25 9:29
extern BYTE file_mode_flag;
#endif
/**************************************************************************
 * Functioin:  SwitchMedia
 * Input:      direction: CARD2CD/CD2CARD/CARD2CARD
 * Purpose:    used for switch media between card and cd / card and card
 *************************************************************************/
#ifdef USE_STOP_SWITCH_DISC_CARD_USB
extern BYTE IsCardMediaExist(void);
extern void SwitchMedia(BYTE direction);
#endif
void SwitchMedia(BYTE direction)
{
	#ifdef USB_CARD_SWITCH
	ircmd_post_func(CMD_FUNC | CMD_FUNC_STOP);  
    delay_1ms(10); 
    #endif                           

    if( (direction == CD2CARD) || (direction == CARD2CARD) )
    {
        #if defined(SUPPORT_SETUP_POPUP_MEDIA_GUI)&&defined(SAME_DISC_RESUME)//chenzhao 20060116
        if(direction == CD2CARD)
            RsmInfo2Flash(0);
        #endif
        InitVar();      //maoyong 2004.05.25 just treat as change disc
        media_type = MEDIA_CARD; 
        cardFile.status = CARD_STATUS_NORMAL;   //for flow control, status will be set dynamically so no influence.
       #ifdef ORITRON_HK_DVD
        // if(prog_cnt)  //qinhua add ,2005-10-31 23:28
         {
          prog_cnt = 0;
          prog_func_clear();
          prog_func_off();  
          program_func_flag=0;
         }
       #endif   
        #ifndef SP1000_NO_DVD
        atapi_p_start_stop_unit(Immed_1,START_STOP_DO_STOP);
        #endif //#ifndef SP1000_NO_DVD
        
        #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
        old_system_state = system_state;
        old_play_state = play_state;
        #endif 
    }
    else if(direction == CARD2CD)
    {
    	#ifdef SPHE8202_CARD_STORAGE
    		GPIO_O_SET(CARD_POWER_RESET,1);//dingzhy for off the card light 4-10-23 14:18,dingzhy mod.
 		#endif    		
        no_disk_cnt = DETECT_TIMES;
        media_type = MEDIA_CD;          
        adv_search_time = 0;
#ifndef SPHE1000 //Jeff 20041217
        atapi_open_tray();  //Maoyong 2004-8-10 11:00
        atapi_close_tray(0);
#endif
     
      #ifdef ORITRON_HK_DVD
    
      // if(prog_cnt)  //qinhua add ,2005-10-31 23:28
         {
          prog_cnt = 0;
          prog_func_clear();
          prog_func_off();  
          program_func_flag=0;
         }
      #endif   
    
    }
    AVD_SetMediaTimeout();
    play_state = VCD_STATE_CLOSE;   
    full_scrn = 0;     
    ClearOsdMsg(0);     
    t_disp = 0; 
    osd_init();
     #ifdef USE_STOP_SWITCH_DISC_CARD_USB//shenyj add 
    if(system_state == SYSTEM_STOP)
    {
        //check whether card is plugged in
        if ( IsCardMediaExist() && (card_plug_state&USER_DO_PLUG_IN))
        {            
        #if defined(CF_CARD_WRITE)|| defined(SPHE8202_FAT_Write_Function)//||defined(WRITE_USB)
            if( read_card_sign && (media_type == MEDIA_CARD) && (MediaIsEmpty == MEDIA_NOT_EMPTY))  //modefied by wangwei,2004-11-19 17:31(for storage no files screen refresh problem)
            {
                CardTestReady();
            }
        #endif
        polling_storage();
        }
        else if(!IsCardMediaExist())
        {
            #if defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
            polling_storage();   //polling_U_Disk(); //wthsin,2004/4/12 02:16pm
            #else
            polling_card_plug();//kenny 2003/1/26
            #endif
            drv_do_set_features(); //card plug out, do set feature to loader            //if((card_plug_state&USER_DO_PLUG_OUT)&&(media_type == MEDIA_CARD))
            if(media_type == MEDIA_CARD)    //Maoyong 2004.05.18 for USB card reader consideration
            {
                SwitchMedia(CARD2CD);       //this will do more actions
             }
            media_type = MEDIA_CD;
        }
    }
    #endif//#ifdef USE_STOP_SWITCH_DISC_CARD_USB//shenyj add 
    ircmd_post_func(CMD_FUNC | CMD_FUNC_OPEN);                  
    system_state = SYSTEM_OPEN;    
   
}

/**************************************************************************
 * Functioin:  IsCardMediaExist
 * Purpose:    used for switch condition check, if return FALSE, can't switch
               to Card Media now.
 *************************************************************************/
BYTE IsCardMediaExist(void)
{
    if( CARDIsPlugIn() )
    {
        //Maoyong 2004.05.20 for other storage_type and USB Card reader consideration
        #ifdef SUPPORT_USB
        if(storage_type&USB_DEVICE)
        {
            if( !UsbTestReady() )
                return FALSE;
        }
        #endif
        
        //Maoyong 2004.05.21 for flow control when switch to CD, to avoid SwitchMedia 
        //called again and back to CARD again when IsCardMediaRemove called.        
        cardFile.status = CARD_STATUS_NORMAL;
        return TRUE;        
    }    

    return FALSE;
}

/**************************************************************************
 * Functioin:  IsCardMediaRemove
 * Purpose:    play card media program, check if card remove when no card
               data reading such as: Jpeg/MPEG/MP4 file list, pause state
 *************************************************************************/
BYTE IsCardMediaRemove(void)
{
    if (media_type == MEDIA_CARD) 
    {
//        if ( CardGetStatus() == CARD_STATUS_NG ) 
        if ( FSGetStatus() == CARD_STATUS_NG ) 
        {
            #if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)
              #if !defined(HOST_UHCI)&&!defined(USB_HOST_DRV)                                                                                                                                                                       
            CardReset();
            #endif 
            #endif
            //Mp3ReadFinish = 0;
            //ircmd_stop();            
            #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
            usb_card_state = USB_CARD_WAS_PLUG_OUT;
            #else
            #ifndef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-4-11 10:49
            SwitchMedia(CARD2CD); 
            #endif//DIRECT_ACCESS_MEDIA
            #endif
            return 1;
        }
    }
    return 0;    
}

/**************************************************************************
 * Functioin:  show_card_reading_osd
 * input:      SHOW_MEDIA/SHOW_READ_PERCENT/SHOW_OFF (gb_def.h)
 * Purpose:    display card media reading info: type/read file percent
 *************************************************************************/
void  show_card_reading_osd(BYTE type)
{
    #ifdef PMP_UI//liweihua 2004-12-22 13:56
    return;
    #endif
    if(ReadPercent > 100)
        ReadPercent = 100;
    #ifdef FILE_MODE_WRITE//develope use,for switching to play CDROM show "read usb" bug, modified by wangwei,2005-1-24 15:07
    if((type != SHOW_OFF)&&(!file_mode_flag))
    #else
    if(type != SHOW_OFF)
    #endif
    {
        #ifdef SWITCH_BETWEEN_USB_CARDS    //Maoyong 2004.05.25 here just for USB
        if(type == SHOW_MEDIA)
        {
        if(storage_type & USB_DEVICE)
        {
            //show card number 1, 2, 3...
            psprintf(RegionValStr[REGION1], "READ CARD %d", CBWLUN+1);
            PrintOsdMsg(STR_OS_SPACE, REGION1, 0, 1);
            }
        }
        else //SHOW_READ_PERCENT
        {
            psprintf(RegionValStr[REGION1], "READ CARD %d %02d%s  [%04d]", CBWLUN+1, ReadPercent, "%", pFsJpeg->iso9660_file_cnt);
            if(storage_type & USB_DEVICE)
            {
                //show reading percent here
                PrintOsdMsg(STR_OS_SPACE, REGION1, 0, 1);
            }
        }
        #else  //SWITCH_BETWEEN_USB_CARDS
        if(type == SHOW_MEDIA)
        {
            //if(storage_type & USB_DEVICE)
            if(storage_type)//liweihua mod 2004-6-9
            {
                //show card number 1, 2, 3...
               if(storage_type & USB_DEVICE) 
                psprintf(RegionValStr[REGION1], "READ USB");  //wthsin, 2004/7/19 03:02pm
               else  
                psprintf(RegionValStr[REGION1], "READ CARD");
               PrintOsdMsg(STR_OS_SPACE, REGION1, 0, 1);
            }
        }
        else
        {
           	if(storage_type & USB_DEVICE) 	//wthsin, 2004/7/19 03:02pm
            	psprintf(RegionValStr[REGION1], "READ USB %02d%s  [%04d]", ReadPercent, "%", pFsJpeg->iso9660_file_cnt);
           	else    
            	psprintf(RegionValStr[REGION1], "READ CARD %02d%s  [%04d]", ReadPercent, "%", pFsJpeg->iso9660_file_cnt);
            
			if(storage_type & USB_DEVICE)
            {
                //show reading percent
                PrintOsdMsg(STR_OS_SPACE, REGION1, 0, 1);
            }
        }
        #endif //SWITCH_BETWEEN_USB_CARDS
    }
    else    //turn off osd display
        ClearOsdMsg(1);
}

/* SWITCH_BETWEEN_USB_CARDS: CD--->USB CARD A ---> USB CARD B ---> CD in turn */
#if defined(IR_SWITCH_CARD_CD) || defined(SUPPORT_SPI_QSI) //Maoyong 2004.05.13
void  ircmd_switch_card_cd(void)
{
    if(media_type == MEDIA_CD)      //switch CD to Card
    {
        if( IsCardMediaExist() )
        {
            #ifdef SWITCH_BETWEEN_USB_CARDS
            card_switch_times = 1;
            #endif

            SwitchMedia(CD2CARD);  
        }
        else 
        {   
            psprintf(RegionValStr[REGION1], "CARD NOT FOUND");  
            PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);           
        }   
    }
    #ifdef IR_SWITCH_CARD_CD_ADD_USB		//dingzhy 2005-3-24 14:59
    else if((storage_type==USB_DEVICE)&&(detect_type&USB_DEVICE!=0))
    {
		if((detect_type & SMC_CARD_DEVICE)) 
            storage_type = SMC_CARD_DEVICE;
		else if((detect_type & MS_CARD_DEVICE)) 
            storage_type = MS_CARD_DEVICE;
		else if((detect_type & SD_CARD_DEVICE)) 
            storage_type = SD_CARD_DEVICE;
		else if((detect_type & CF_CARD_DEVICE)) 
            storage_type = CF_CARD_DEVICE;  
            
		SwitchMedia(CD2CARD);  
    }    
    #endif
    else    //switch from card  to cd, in fact should check if no disc here!
    {
        #ifdef SWITCH_BETWEEN_USB_CARDS
        if( storage_type&USB_DEVICE )
        {
            if( IsUSBCardReader() && USBCheckNextReadyLun()&& (card_switch_times < MAX_USB_CARDS) )
            {
                card_switch_times++;
                SwitchMedia(CARD2CARD);
            }
            else
            {
                SwitchMedia(CARD2CD);
                card_switch_times = 0;
            }
        }
        #else  //SWITCH_BETWEEN_USB_CARDS
        SwitchMedia(CARD2CD);
        #endif //SWITCH_BETWEEN_USB_CARDS
    }
}
#endif //#ifdef  IR_SWITCH_CARD_CD

#ifdef IR_SWITCH_CD_USB_CF_OTHER  //added by dingzhy  4-10-20 13:57
void ircmd_switch_cd_usb_cf_other(void)
{
	
	    if(media_type == MEDIA_CD)      //switch CD to Card
	    {
	    	if( IsCardMediaExist() )
	           {
	           	now_valid_type = detect_type;//for bug:read cf,insert usb,will read cf again.
	        	SwitchMedia(CD2CARD);
	        	}
	        else 
        	   {   
		        if(play_state != VCD_STATE_OPEN)
        	   	{
		        psprintf(RegionValStr[REGION1], "USB/CARD NOT FOUND");  
		        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);           
        		}
        	   }   
	    }  
	        
	    else if(detect_result_last==0x01)   //when play USB
	    {
	    	if(detect_type == 0x01)
	    	SwitchMedia(CARD2CD);
	    	else
	    	{
	        now_valid_type = (detect_type & 0x1e);
	        SwitchMedia(CD2CARD);
	        }
	     }   
	    else if(detect_result_last==0x02)   //when play CF
	    {
	    	if((detect_type == 0x03)||(detect_type == 0x02))
	    	{
	    	now_valid_type = 0;	
	    	SwitchMedia(CARD2CD);
	    	}
	    	else
	    	{
	        now_valid_type = (detect_type & 0x1c);
	        SwitchMedia(CD2CARD);
	        }
	        
	     }   
	    else	//play other card  dingzhy 4-10-22 13:52
	    {
	    SwitchMedia(CARD2CD);
	    now_valid_type = 0;
	    }
	
}		
#endif	//#ifdef IR_SWITCH_CD_USB_CF_OTHER

#ifdef SWITCH_CD_CARD_USB//liweihua add 2004-6-8 13:57, for swtich between cd/card/usb
//color define
#define COLOR_WHITE         2
#define COLOR_GRAY          3
#define COLOR_GRAYWHITE     14
#define COLOR_YELLOW        7
#define COLOR_YELLOWGREEN   9
#define COLOR_DBLUE         4
#define COLOR_LBLUE         6
#define COLOR_GREEN         13
#define COLOR_ORANGE        5
//button id define
#define CDBUTTON            0
#ifdef SUPPORT_USB
#define USBBUTTON           CDBUTTON+1
#else
#define USBBUTTON           CDBUTTON
#endif
#ifdef CARD_SETUP_TYPE_3    //dingzhy 2005-6-23 10:03
#define CFBUTTON            (USBBUTTON+1)
#define SDBUTTON            (USBBUTTON+2)
#define MSBUTTON            (USBBUTTON+3)
#define SMCBUTTON           (USBBUTTON+4)
#else  //dingzy add for 3in1 card,usb and cd change 2005-6-23 10:00
#define CARDBUTTON          (USBBUTTON+1)//2
#endif
//define osd parameter
#define RWIDTH      64*4
#define RHEIGHT     288
#define GUIREGION   3


BYTE *show_string[] = { "READ CD",
                        #ifdef SUPPORT_USB
                        "READ USB",
                        #endif
                        #ifdef CARD_SETUP_TYPE_3  //dingzhy 2005-6-23 10:00
                        "READ CF",
                        "READ SD/MMC",
                        "READ MS/MS PRO",
                        "READ SMC",
                        #else
                        "READ CARD",
                        #endif
                        };
BYTE select_media_type = 0;//define selected media type through switch gui
BYTE hilight_button_id;

void draw_switch_background(void)
{
    osd_draw_region_rect(0, 0, RWIDTH, RHEIGHT, COLOR_LBLUE, GUIREGION);
    osd_DrawRegionLine(0, 0, RWIDTH-1, 0, COLOR_WHITE, 1, GUIREGION);
    osd_DrawRegionLine(0, 0, 0, RHEIGHT-1, COLOR_WHITE, 1, GUIREGION);
    osd_DrawRegionLine(RWIDTH-1, 0, RWIDTH-1, RHEIGHT, COLOR_GRAY,1, GUIREGION);
    osd_DrawRegionLine(0, RHEIGHT-1, RWIDTH, RHEIGHT-1, COLOR_GRAY, 1, GUIREGION);    
}
void draw_switch_button(BYTE button_id,BYTE fontcolor,BYTE backcolor,BYTE region)
{
    osd_DrawRegionString(1, button_id*8+6, show_string[button_id],fontcolor,backcolor,region);    
}
#ifdef SWITCH_CD_CARD_USB //winking.J add for DISPLAY 2006 07 17
BYTE AngleSwichFlag;
#endif

void show_switch_gui(void)
{

#ifdef SWITCH_CD_CARD_USB //winking.J add for DISPLAY 2006 07 17
   AngleSwichFlag = 1;
#endif

    //osd_init_switchGUI();
    hilight_button_id = 0;
    if(detect_type == 0)
    {
        psprintf(RegionValStr[REGION1], "USB/CARD NOT FOUND");
        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);   
    }
    else
    {
	#ifdef SUPPORT_MP4_SUBTITLE	//yaowh add 2005-12-22 11:28
		if(g_pfnPollingSubtitle)
		{
			IsSubtitle = 1;
			supClearSubtitle();
		}	
	#endif
    	osd_init_switchGUI();	//yaowh move here 2005-12-22 11:28
        draw_switch_background();
        if(media_type == MEDIA_CARD)
            hilight_button_id = CDBUTTON;
        else if((detect_type & USB_DEVICE) ) 
            hilight_button_id = USBBUTTON;
        #ifdef CARD_SETUP_TYPE_3   //dingzhy 2005-6-23 10:00
        else if((detect_type & CF_CARD_DEVICE)) 
            hilight_button_id = CFBUTTON;
        else if((detect_type & SD_CARD_DEVICE)) 
            hilight_button_id = SDBUTTON;
        else if((detect_type & MS_CARD_DEVICE)) 
            hilight_button_id = MSBUTTON;
        else if((detect_type & SMC_CARD_DEVICE)) 
            hilight_button_id = SMCBUTTON;
        #else
        else if((detect_type & SD_CARD_DEVICE)||(detect_type & MS_CARD_DEVICE)) 
            hilight_button_id = CARDBUTTON;
        #endif
        
        hilight_button(hilight_button_id);
    }
    
}
//draw default button 
void set_switch_button(void)
{
    BYTE i;
    //DRAW all button with gray font
    #ifdef CARD_SETUP_TYPE_3  //dingzhy add  2005-6-23 10:01
    for(i=CDBUTTON;i<=SMCBUTTON;i++)
        draw_switch_button(i,COLOR_GRAY,COLOR_LBLUE,GUIREGION);
    #else
    for(i=CDBUTTON;i<=CARDBUTTON;i++)
        draw_switch_button(i,COLOR_GRAY,COLOR_LBLUE,GUIREGION);
    #endif    
    //draw all exist media button with white font
    //CD button    
    if(media_type == MEDIA_CARD)
        draw_switch_button(CDBUTTON,COLOR_WHITE,COLOR_LBLUE,GUIREGION);
    // USB button
    #ifdef SUPPORT_USB
    if(detect_type & USB_DEVICE)
        draw_switch_button(USBBUTTON,COLOR_WHITE,COLOR_LBLUE,GUIREGION);
    #endif
    // CF button
    #ifdef CARD_SETUP_TYPE_3  //dingzhy 2005-6-23 10:01
    if(detect_type & CF_CARD_DEVICE)
        draw_switch_button(CFBUTTON,COLOR_WHITE,COLOR_LBLUE,GUIREGION);
    // SD/MMC button
    if(detect_type & SD_CARD_DEVICE)
        draw_switch_button(SDBUTTON,COLOR_WHITE,COLOR_LBLUE,GUIREGION);
    // MS/MS pro button
    if(detect_type & MS_CARD_DEVICE)
        draw_switch_button(MSBUTTON,COLOR_WHITE,COLOR_LBLUE,GUIREGION);
    // SMC button
    if(detect_type & SMC_CARD_DEVICE)
        draw_switch_button(SMCBUTTON,COLOR_WHITE,COLOR_LBLUE,GUIREGION);
    #else
    if((detect_type & SD_CARD_DEVICE)||(detect_type & MS_CARD_DEVICE))
        draw_switch_button(CARDBUTTON,COLOR_WHITE,COLOR_LBLUE,GUIREGION);
    #endif

}

//draw default button and hilight the current select button
void hilight_button(BYTE button_id)
{
    set_switch_button();
    osd_DrawRegionString(1, button_id*8+6, show_string[button_id],COLOR_WHITE,COLOR_ORANGE,GUIREGION); 
}

void switch_gui_up(void)
{
    BYTE offset;
    BYTE current_type;
    offset = detect_type << (7-hilight_button_id);
    if((media_type == MEDIA_CARD)&&(hilight_button_id <= CDBUTTON))
        hilight_button_id = CDBUTTON;
    else if((media_type == MEDIA_CD) && (hilight_button_id <= (CDBUTTON+1)))
        hilight_button_id = CDBUTTON+1;
    else if(offset > 0)
    {
        hilight_button_id--;
        if(hilight_button_id > CDBUTTON)
        {
            #ifdef SUPPORT_USB
            current_type = 0x01<<(hilight_button_id-1);
            #else
            current_type = 0x01<<(hilight_button_id);
            #endif
            if((current_type & detect_type) == 0)
            {
                hilight_button_id--;
                if((media_type == MEDIA_CD) && (hilight_button_id == CDBUTTON))
                return;
            }
        }
        hilight_button(hilight_button_id);
    }
}
void switch_gui_down(void)
{
    BYTE offset;
    BYTE current_type;
    offset = detect_type>>hilight_button_id;
    #ifdef CARD_SETUP_TYPE_3  //dingzhy 2005-6-23 10:01
    if(hilight_button_id>=SMCBUTTON)
        hilight_button_id = SMCBUTTON;
    #else
    if(hilight_button_id>=CARDBUTTON)
        hilight_button_id = CARDBUTTON;
    #endif
    #ifdef SUPPORT_USB
     #ifndef CARD_SETUP_TYPE_3 //dingzhy add 2005-6-23 10:18
     else if(((detect_type>>hilight_button_id) > 0)&&(hilight_button_id < CARDBUTTON))
     #else
    else if((detect_type>>hilight_button_id) > 0)
     #endif
    #else
    else if((detect_type>>(hilight_button_id+1)) > 0)
    #endif
    {
        hilight_button_id++;
        #ifdef SUPPORT_USB
        current_type = 0x01<<(hilight_button_id-1);
        #else
        current_type = 0x01<<(hilight_button_id);
        #endif
        #ifdef CARD_SETUP_TYPE_3 //dingzhy  2005-6-23 10:02
        if((current_type & detect_type) == 0)
            hilight_button_id++;
        #endif
        hilight_button(hilight_button_id);
    }
}
void switch_gui_select(void)
{
    BYTE current_type;
    
    AVD_SetMediaInterrupt();
    
    switch(hilight_button_id)
    {
        case CDBUTTON:
            select_media_type = 0;
            SwitchMedia(CARD2CD);
            break;
        #ifdef SUPPORT_USB
        case USBBUTTON:
            select_media_type = USB_DEVICE;
            storage_type = USB_DEVICE;  //dingzhy  add for  3in1 car usb and disc change  050623 
            SwitchMedia(CD2CARD);
            break;
        #endif
				#ifdef CARD_SETUP_TYPE_3  //dingzhy  add  0623
        case CFBUTTON:
            select_media_type = CF_CARD_DEVICE;
            SwitchMedia(CD2CARD);
            break;
        case SDBUTTON:
            select_media_type = SD_CARD_DEVICE;
            SwitchMedia(CD2CARD);
            break;
        case MSBUTTON:
            select_media_type = MS_CARD_DEVICE;
            SwitchMedia(CD2CARD);
            break;
        case SMCBUTTON:
            select_media_type = SMC_CARD_DEVICE;
            break;
        #else//#ifdef CARD_SETUP_TYPE_3  //dingzhy  a
        case CARDBUTTON:
        		if(detect_type & SD_CARD_DEVICE)
        		{
            	select_media_type = SD_CARD_DEVICE;
            	storage_type = SD_CARD_DEVICE;
            }
            else if(detect_type & MS_CARD_DEVICE)
            {
            	select_media_type = MS_CARD_DEVICE;
            	storage_type = MS_CARD_DEVICE;
            }
            SwitchMedia(CD2CARD);
            break;
        #endif//#ifdef CARD_SETUP_TYPE_3  //dingzhy  a
        default:
            break;
    }
}
void ircmd_switch_cd_card_usb(void)
{
    if(play_state == VCD_STATE_OPEN)
        return;
    if (full_scrn & SWITCH_GUI)
    {
        full_scrn &= (~SWITCH_GUI);
        #ifdef CD_PLAYER 
        if(cd_type_loaded==CDDA)
        {
            osd_init_cdplayer();
        }else               
            osd_init();
        #else
        delay_srv_10ms(1);	//yaowh add 2005-12-22 11:27
        osd_init();
        full_scrn = 0;
        
        #ifdef SUPPORT_MP4_SUBTITLE	//yaowh add 2005-12-22 11:22
        if(IsSubtitle)
        {
			supOpenSubtitle();
		}
		#endif
        #endif
    }
    else
    {
        if((full_scrn & MARK)||(full_scrn & GOTO))
        {
            invalid_key();
            return;
        }
        full_scrn |= SWITCH_GUI;

        show_switch_gui();
        //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 9:59
        SetFullscrnCmdFuncPtr( switch_gui_up, switch_gui_down, ircmd_null,
                                   ircmd_null, switch_gui_select);
    }
}

#endif//#ifdef SWITCH_CD_CARD_USB
#if defined(FAT_FILE_MODE) && defined(SPHE8202_FAT_WRITE_API)//liweihua mod 2005-3-15 16:16
void ircmd_card_copy(void)
{
    if(fat_play_mode == 1)
    {
        if(pFsJpeg->ControlArea == CNT_AREA_CARD)
        {
            if(pFsJpeg->gifsState == FS_STATE_HDD)
                CardCopy();
            else
            {
                FATCopy();
             }

        }
        else
        {
            invalid_key();
            return;
        }
    }
}
void ircmd_card_delete(void)
{
    if(fat_play_mode == 1)
    {
        FATDelete();
        return;
    }
}
#endif


#endif  //#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)

