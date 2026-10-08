/*
*  Terry,2004/2/10 03:34PM
*/
//#include "setup_page.h"//nono mark why add it??

#ifndef AC3_BASS_MANAGEMENT
 int downmix_off;
#endif 

#ifdef PULIANG_SETUP_MENU  //yaowh add 04-12-15
    int show_menu_setup_flag;
#endif

#ifdef SELECT_MEDIA_IN_SETUPMENU
BYTE media_changed_flag = 0;
#endif

void exe_setup_function(UINT8 tt_id, UINT8 sub_id, UINT8 exe);

#ifdef SETUP_CAN_DIRECT_SEL_MENU_LANG
extern void is_reload_dvd_menu(void);
#endif

#ifdef DVD_SETUP_REENG
extern void setup_VA2sel(void);
extern UINT32 setup_getSelPos(UINT16 selection);        // 2005/03/29 yltseng
extern UINT16 setup_getItemPos(UINT16 item);            // 2005/03/29 yltseng
#endif

#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:12
extern int IDTWO;
UINT8 language_id;
UINT16 LCD_2;  //Language CoDe of the second subtitle.
#endif

#ifdef SCALER_6500
#ifdef Simplay_warning	//eric lin,2006-07-06,for Simplay format warning message
UINT8 hdmi_sel;//eric lin  
#endif	//#ifdef Simplay_warning   
    #ifdef HDMI_FMT_RESTORE
           BYTE pre_tvsys, pre_hdfmt, default_set;
           extern BYTE FMT_CHANGE;
    #endif
    
extern void HDMI_AUTO_Mode(UINT8 sub_id);
extern void scaler_6500_main(void); //helm 050707
extern void SPHE6500_Select_Format(UINT8 sub_id);
#endif

#ifdef DVB_OSD_LANGUAGE_SYNC_DVD
extern BYTE g_cMenuLanguage;
#endif
        	
#ifdef SETUP_CAN_DIRECT_SEL_SUBTITLE//Jack clear warning msg 05/09/29
extern void dvd_sel_subtitle_right_now();		
#endif

#ifdef USE_SETUP_SELECT_FONT
extern UINT32 ftSetFont( UINT32 uiFontIdx );
#endif

#ifdef SETUP_CAN_DIRECT_SEL_AUDIO_LANG//Jack clear warning msg 05/09/29
extern void dvd_sel_language_right_now();		
#endif 
        	
#ifdef MIC_MUTE_PIN   // lxg 2006-7-14 03:56
int mic_mute_flag=0;
extern void Mic_mute_pin_output_low(void);
extern void Mic_mute_pin_output_high(void);
#endif 
        	
#ifdef SUPPORT_HD_DVD
extern void scaler_main(void);

static inline void  exe_setup_function_dvi(UINT8 tt_id, UINT8 sub_id, UINT8 exe __UNUSED)//chenzhao 20051207
{
    #ifdef ADD_DVI311_SETUP
	
    #if 0////Modifed by chenzhao on 2004-12-10 15:39  
    static unsigned char init_output=1;
	if(tt_id == STR_OS_DVI311_FORMAT)
	{
		dvi311_format = sub_id;
		if(dvi311_format==STR_OS_ANOLOG_OUTPUT)  ////analog kevin0710
			{
			if(init_output==0)  
			{
				}
			else
			{
				init_output=0;
				scaler_main(); 
				}
            close_pll(0x00);
            Power_off_311=1;
			}
		if(dvi311_format==STR_OS_DIGIT_OUTPUT)  //digital
			{
			if(Power_off_311==1)
				{
				    close_pll(0xff);
#if 0
   			 	GPIO_O_SET(40, 1);
 				delay_1ms(200);
				delay_1ms(200);
				GPIO_O_SET(40, 0);	//reset 311	
				delay_1ms(600);
				scaler_main();
#endif //0
				Power_off_311=0;
				}
			init_output=0;
			}
//		scaler_main(); //040512
		printf("set output--kevin");
    	psprintf(linebuf, "dvi311_format %x\n", dvi311_format); 
    	epp_write_wait(linebuf);	
	}
    #endif
    #ifdef HDCP_CUSTOM//Modifed by chenzhao on 2004-12-1 11:24   
	if(tt_id == STR_OS_HDCP)
	{
	    if(STR_OS_OFF==sub_id)
	        hdcp_mode=HDCP_OFF;
        else
	        hdcp_mode=HDCP_ON;
        ResetAuthentStates();
	}
    #endif
	if(tt_id ==STR_OS_TV_SYS)
	{
	    if(sub_id!=STR_OS_AUTO)
		dvi311_tv_mode = sub_id;
        #ifdef DVD_SETUP_REENG//Modifed by chenzhao on 2004-11-24 21:8   
            //dvi311_mode=setup_VA[SETUP_VA_SPV311MODE]-MIN_ITEM_SEL;
        #else
        dvi311_mode=SETUP_DVI_MODE-MIN_ITEM_SEL;//for load saved SETUP_DVI_MODE.added by ChenZhao on 2004-10-19 14:22  
        #endif
		//kevin tsest
//if(tv_out_id!=P_SCAN)//Modifed by chenzhao on 2004-11-25 16:46  //not HD output  kevin@2k0708
//{
	if(dvi311_tv_mode>0x84&&dvi311_mode==Mode_576P)// NTSC and 480P   @kevin 2k40708
                    dvi311_mode=Mode_480P;
	if(dvi311_tv_mode==0x84&&dvi311_mode==Mode_480P)// PAL and 576P   @kevin 2k40708
                    dvi311_mode=Mode_576P;                        
#if 0//Modifed by chenzhao on 2004-11-25 16:46   
//}
else if(tv_out_id==P_SCAN)                                   //not HD output  kevin@2k0708
{
	if(dvi311_tv_mode>0x84&&dvi311_mode==Mode_576P)// NTSC and 480P   @kevin 2k40708
		dvi311_mode=Mode_480P;
	if(dvi311_tv_mode==0x84&&dvi311_mode==Mode_480P)// PAL and 576P   @kevin 2k40708
		dvi311_mode=Mode_576P;
}	
#endif
        #ifdef DVD_SETUP_REENG//Modifed by chenzhao on 2004-11-24 21:8   
            //setup_VA[SETUP_VA_SPV311MODE]=dvi311_mode+MIN_ITEM_SEL;
        #else
        //SETUP_DVI_MODE=dvi311_mode+MIN_ITEM_SEL;
        #endif
        if(Power_off_311==1)//for standby powerup start 311.added by ChenZhao on 2004-10-19 16:51  
        {
            close_pll(0xff);
            Power_off_311=0;
        }
		scaler_main(); //040512
    	psprintf(linebuf, "dvi311_tv_mode %x,exe=%d\n", dvi311_tv_mode,exe); 
    	epp_write_wait(linebuf);		
	}
#elif defined(SCALER_6500) //helm for 6500 scaler 050707
    #ifdef HDCP_CUSTOM//Modifed by chenzhao on 2004-12-1 11:24   
	if(tt_id == STR_OS_HDCP)
	{
	    if(STR_OS_OFF==sub_id)
	        hdcp_mode=HDCP_OFF;
        else
	        hdcp_mode=HDCP_ON;
        ResetAuthentStates();
	}
    #endif

	if(tt_id ==STR_OS_TV_SYS)
	{
	    if(sub_id!=STR_OS_AUTO)
		dvi311_tv_mode = sub_id;
       
 	if(dvi311_tv_mode>0x84&&dvi311_mode==Mode_576P)// NTSC and 480P   @kevin 2k40708
                    dvi311_mode=Mode_480P;
	if(dvi311_tv_mode==0x84&&dvi311_mode==Mode_480P)// PAL and 576P   @kevin 2k40708
                    dvi311_mode=Mode_576P;   
        }
#endif

}

#endif


#include "str_os_downmix_setup.inc"
#include "str_os_aud_out.inc"

#include "str_os_16_9.inc"
#include "str_os_4_3lb.inc"
#include "str_os_4_3ps.inc"

#include "str_os_svideo.inc"
#include "str_os_ycbcr.inc"
#include "str_os_tv_rgb.inc"
#include "str_os_pc_vga.inc"
#include "str_os_pscan_yuv.inc"
#include "str_os_hd.inc"

#ifdef SUPPORT_PROLOGIC_II
#include "str_os_prologic2.inc"
#endif

#ifdef SUPPORT_SW_OSD_SCALING
#include "osd_WndAPI.h"
#endif

//added by JS	//for setup reengineering	//20040817
#ifdef DVD_SETUP_REENG

#ifdef SPHE8202_CARD_STORAGE 
   extern void Card_power_off();                         
#endif

#ifdef SLEEP_CONTROL_COUNTER   //liumzh 2004-12-10 23:53
extern	UINT32 counter_sleep_control ;
extern	UINT32 sleep_time ;//seconds
#endif


#ifdef SETUP_EXTENSION_TABLE        // 2005/03/29 yltseng
#include "TVGApp.h"

void exe_setup_function_ex(UINT8 tt_id, UINT8 sub_id, UINT8 exe __attribute__((unused)) )
{
    switch( tt_id )
    {
    #ifdef SUPPORT_TVG
    case STR_OS_TVG_MODE:
        switch( sub_id )
        {
        case STR_OS_OFF_EX:
            TVGSetMode( TVG_MODE_OFF );
            break;
        case STR_OS_TOLERANT:
            TVGSetMode( TVG_MODE_ONTOL );
            break;
        case STR_OS_MODERATE:
            TVGSetMode( TVG_MODE_ONMOD );
            break;
        case STR_OS_STRICT:
            TVGSetMode( TVG_MODE_ONSTR );
            break;
        }
        break;
    case STR_OS_HELL_DAMM:   			
        switch( sub_id )
        {
        case STR_OS_ON_EX:
            TVGSetWordSets( TVG_WORD_SET_DAMMHELL, TRUE );
            break;
        case STR_OS_OFF_EX:
            TVGSetWordSets( TVG_WORD_SET_DAMMHELL, FALSE );
            break;
        }
        break;
    case STR_OS_SEXUAL:   			
        switch( sub_id )
        {
        case STR_OS_ON_EX:
            TVGSetWordSets( TVG_WORD_SET_SEXUAL, TRUE );
            break;
        case STR_OS_OFF_EX:
            TVGSetWordSets( TVG_WORD_SET_SEXUAL, FALSE );
            break;
        }
        break;
    case STR_OS_RELIGIOUS:   			
        switch( sub_id )
        {
        case STR_OS_ON_EX:
            TVGSetWordSets( TVG_WORD_SET_RELIGIOUS, TRUE );
            break;
        case STR_OS_OFF_EX:
            TVGSetWordSets( TVG_WORD_SET_RELIGIOUS, FALSE );
            break;
        }
        break;
    case STR_OS_CC_MODE:   			
        switch( sub_id )
        {
        case STR_OS_CC_OFF:
            TVGSetCCOperation( TVG_CC_OFF );
            break;
        case STR_OS_ON_MUTE:
            TVGSetCCOperation( TVG_CC_ONCUSS );
            break;
        case STR_OS_CC_CONTINUOUS:
            TVGSetCCOperation( TVG_CC_ON );
            break;
        }
        break;
    case STR_OS_TVG_CHANNEL:   			
        switch( sub_id )
        {
        case STR_OS_CC1:
            TVGSetCCChannel( TVG_CC1 );
            break;
        case STR_OS_CC2:
            TVGSetCCChannel( TVG_CC2 );
            break;
        }
        break;
    #endif
    }
}
#endif

void exe_setup_function(UINT8 tt_id, UINT8 sub_id, UINT8 exe)
{
#ifdef HDMI_FMT_RESTORE
    pre_tvsys = dvi311_tv_mode; 
    pre_hdfmt = dvi311_mode;
#endif
    //language,osd,subtitle,audio
    //printf("tt:%d sub:%d exe:%x\n",tt_id,sub_id,exe);
    #ifdef STORE_VIDEO_PARAMETER
    BYTE res; 
    #endif     

printf("\n	exe_setup_function in  %d  %d  %d\n", tt_id, sub_id, exe);
	
    #if defined(ADD_DVI311_SETUP) || defined(SCALER_6500)
    exe_setup_function_dvi(tt_id,  sub_id,  exe);
    #endif
    
    switch(tt_id)
    {
    #if  0//def SELECT_MEDIA_IN_SETUPMENU     //denghg  marked  20050204
    case STR_OS_MEDIA_TYPE:
    		if(system_state == SYSTEM_OPEN)	//Maoyong 2004/8/11 can't switch in OPEN state
    			break;
    			
    		switch(sub_id)
    		{
    			case STR_OS_MEDIA_DISC:
    			    if(media_type == MEDIA_CARD)
                    {
                      #ifdef SPHE8202_CARD_STORAGE 
                        Card_power_off();   //wthsin,  2004/9/1 10:13am
                      #endif 
                        media_changed_flag = 1;
                        SwitchMedia(CARD2CD);
                        printf("========= Switch to Disk Media ==========\n");
                    }
    				break;
			    case STR_OS_MEDIA_USB:
			        if( (media_type == MEDIA_CD) || (storage_type != USB_DEVICE) )
    			    {
    			      #ifdef SPHE8202_CARD_STORAGE 
                        Card_power_off();   //wthsin,  2004/9/1 10:13am
                      #endif      			    	
    			        media_changed_flag = 1;
    			        storage_type = USB_DEVICE;
                        SwitchMedia(CD2CARD);
                        printf("========= Switch to USB Device ==========\n");
                    }
				    break;
			    case STR_OS_MEDIA_CARD:	//Maoyong 2004/8/11 for eastech TYPE 3 CARD Storage
                    if( (media_type == MEDIA_CD) || ( (storage_type != MS_CARD_DEVICE) && (storage_type != SD_CARD_DEVICE) && (storage_type != SMC_CARD_DEVICE) )  )
    			    {
    			        media_changed_flag = 1;
    			        if(detect_type & MS_CARD_DEVICE)
    			            storage_type = MS_CARD_DEVICE;
                        else if(detect_type & SD_CARD_DEVICE)
    			            storage_type = SD_CARD_DEVICE;
    			        else if(detect_type & SMC_CARD_DEVICE) 
    			        	storage_type = SMC_CARD_DEVICE;  
                        SwitchMedia(CD2CARD);
                        printf("========= Switch to MS/SD/SMC CARD Device ==========\n");
                    }
				    break;
    		}
    		break;
    #endif //#ifdef SELECT_MEDIA_IN_SETUPMENU
        	
    #ifdef TUNR_OFF_PARENTAL_LVL
    case STR_OS_RATING:
	bTurnOffParentalLVL=0;//terry,2002/9/20 11:40PM
	break;
    #endif
#ifdef ADD_P_SCAN_ONOFF
	case STR_OS_P_SCAN_YUV:  //add by Tom 20040714
		if(sub_id==STR_OS_ON)
 			str_os_pscan_yuv();        
		else
			str_os_ycbcr(); 
		break;
#endif
#ifdef SWITCH_SUB_DIRECTION//libing 2005-7-15 14:43
	    case STR_OS_OPEN:
		    if(sub_id==STR_OS_ON)
		    	subtitle_ratate_flag = 1;
		    if(sub_id==STR_OS_OFF)
		        subtitle_ratate_flag = 0;
		    break;		
#endif

#ifdef USE_SETUP_SELECT_FONT
	case STR_OS_DIVX_FONT_CODE:
		{
			extern BYTE font_setup_map[8];
			int i;
			for(i=0;i<8;i++)
				{
					if(font_setup_map[i] == sub_id) 
						break;
				}
			#ifdef ALCO_DIVX_UI
			switch(sub_id)
		    {
		        case 1:
		            #ifdef SWITCH_SUB_DIRECTION
		            subtitle_ratate_flag=0;
		            #endif
		            ftSetFont(2);
		        	break;
		        case 2:
		            #ifdef SWITCH_SUB_DIRECTION
		            subtitle_ratate_flag=0;
		            #endif
		            ftSetFont(0);
		        	break;
		        case 3:
		            #ifdef SWITCH_SUB_DIRECTION
		            subtitle_ratate_flag=0;
		            #endif
		            ftSetFont(1);
		        	break;
		        case 4:
		        case 5:
		        case 6:
		            #ifdef SWITCH_SUB_DIRECTION
		            subtitle_ratate_flag=0;  
		            #endif      
		            ftSetFont(sub_id-1);
		        	break;
		        case 7:
		            #ifdef SWITCH_SUB_DIRECTION
		            subtitle_ratate_flag=1;
		            #endif
		            ftSetFont(5);
		            break;
		        default:
		        	 ftSetFont(2);
		        	break;
		    }	
		    #else//#ifdef ALCO_DIVX_UI	  
			ftSetFont(i);
			#endif//#ifdef ALCO_DIVX_UI
		}
		break;
#endif
	case STR_OS_VIDEO:
        #ifdef SUPPORT_HD_RESOLUTION
                 if(setup_VA_EN[SETUP_VA_VIDEO] == 1)   {
                    SET_TV_RESOLUTION(SD_576);
                 }   
        #endif
               break;
	case STR_OS_OSD:
		{

			int         i;
			for  (i=MIN_ITEM_SEL; i<=MAX_ITEM_SEL; i++) {//nono 2-10-30 17:35
				if (sub_id==setup_item[setup_pos[1]][setup_pos[2]][i])
				{
					break;
				}
			}
			/*	//marked by JS	//20040817
			#ifdef SUPER_DEFAULT_OSD_LANG
			if(page==CUSTMPAGEINDEX)
			{
			    	UserSet.setup_default_osd_lang = i -2;
                		SETUP_OSD_LANG = UserSet.setup_default_osd_lang +2;
			}
			#endif
			*/
			//osd_font_mode = i-2;
			osd_font_mode = OSD_LANG_MAP[i-2]; //Jeff 20030217
#ifdef DVB_OSD_LANGUAGE_SYNC_DVD
            g_cMenuLanguage = osd_font_mode;
#endif		
		}
		break;


	case STR_OS_SUBTITLE_LANG_SETUP:
		UserSet.SPSTN = 0x40|0x3E;//setting sub-picture on
		if(sub_id==STR_OS_AUTO) {
			sub_id=LCD_EN;//'e' * 256 + 'n';
		} else if(sub_id==STR_OS_OFF) {
			//sub_id=LCD_EN;//'e' * 256 + 'n';
			sub_id=0; //Jeff 20020925
			UserSet.SPSTN =0xffbf;//setting sub-picture on
		}
		UserSet.SPST_LCD = lang_639code[sub_id];//trans_lang_id(sub_id);
			
//#define SETUP_CAN_DIRECT_SEL_SUBTITLE			
#ifdef	SETUP_CAN_DIRECT_SEL_SUBTITLE
		dvd_sel_subtitle_right_now();
#endif
		printf("UserSet.SPST_LCD:%d\n",UserSet.SPST_LCD);
		printf("SPTN:%x\n",UserSet.SPSTN);	
		break;
		
	case STR_OS_SSAVER_SETUP:
		break;

    //joshua, 20050711, modified for servo-debug function on OSD
    case STR_OS_SERVO_DEBUG:

        #ifdef DVD_SERVO    
    		if (sub_id==STR_OS_OFF) 
    			servo_debug_message=0;
    		else
    			servo_debug_message=1;
		#endif
			
		break;
    	
	#ifdef SAME_DISC_RESUME
	case STR_OS_RESUME:
		if (sub_id==STR_OS_OFF) 
			same_disc_onoff=0;
		else
			same_disc_onoff=1;
		break;
	#endif 			
        
#ifdef SUPPORT_ANGLE_MARK//liweihua add 2004-2-4
	case STR_OS_ANGLE_MARK:
		if (sub_id==STR_OS_OFF) 
		angleflag=1;
		else
		    angleflag=0;
		break;
#endif	

#ifdef SUPPORT_LAST_MEMERY
    case STR_OS_MEMORY:
		if (sub_id==STR_OS_ON) 
		{
		    memery_resumeflag = 1;
		}	
        else
        {
            memery_resumeflag = 0;
        }	
    break;
#endif//end=> #ifdef SUPPORT_LAST_MEMERY


#ifdef SUPPORT_PBC_ONOFF    //suxin add 2005-08-09 for wingsum_tvcombo DVD
    case STR_OS_PBC:
        if (sub_id==STR_OS_ON)
            pbcon_init();
        else
            pbcoff_init();
        break; 
#endif

#ifdef SUPPORT_CC_ONOFF//nono 2004-4-11 19:02
	case STR_OS_CLOSED_CAPTION:
		if (sub_id==STR_OS_OFF) 
		tv_l21_enable(0);
		else
		    tv_l21_enable(1);
		break;	
#endif//SUPPORT_CC_ONOFF

#ifdef DYNAMIC_SPECTRUM    //fengjl  for BBK  3-10-21 20:48
    case STR_OS_BAND:
        if (sub_id==STR_OS_OFF) 
		{	
			band_onoff=0;
			bEqDisplay=0;			
		}
		else 
		{	
			band_onoff=1;
	       // bEqDisplay=1;//zhaoyanhua mask for avoid the bug
	    }	
        break;
#endif
    
#if defined(ORITRON_HK_DVD)||defined (DYNAMICRANGEON_OFF)	//fcr 2005-10-12 15:24 exec here
case STR_OS_DYNAMICRANGE://libing 2005-6-10 17:01
    	if(sub_id==STR_OS_OFF) 
    {
    	ac3_dynarange=0;//setup_pos[3]-MIN_ITEM_SEL;
		set_AC3DynamicRange();	
	}else
	{
		ac3_dynarange=8;//setup_pos[3]-MIN_ITEM_SEL;
		set_AC3DynamicRange();
	}
	break;    
#endif
    
#ifdef USER_MPEG_LOGO
		case STR_OS_SELECT_LOGO:
		#ifdef JIEKE_DVD
		if (sub_id==STR_OS_JIEKE_SETUP)
		#elif defined(NINTAUS_DVD)//nono 2004-2-17 17:49
		if (sub_id==STR_OS_RESTORE_SETUP1)
		#else
		if (sub_id==STR_OS_RESTORE_SETUP) 
		#endif
		{
			mpeg_logo_onoff=0;
		}
		else
		{
			mpeg_logo_onoff=1;
		}	
		Change_User_Logo();
		need_show_logo=1;
		break;	
#endif 

	case STR_OS_AUDIO_LANG_SETUP:
		UserSet.AST_LCD = lang_639code[sub_id];
		printf("audio lang id:%d\n",UserSet.AST_LCD);
#ifdef SETUP_CAN_DIRECT_SEL_AUDIO_LANG  //axel 2004/9/21 
        dvd_sel_language_right_now();		
#endif        		
		break;
		
	case STR_OS_MENU_LANG_SETUP:
		UserSet.M_LCD = lang_639code[sub_id];;

#ifdef SETUP_CAN_DIRECT_SEL_MENU_LANG //terry,2004/9/20 09:58PM
                is_reload_dvd_menu();
#endif 		
		
		printf("menu language id:%d\n",UserSet.M_LCD);
		break;

#ifdef SOUND_EFFECT_MENU          //sunzhh add 2004-4-30 10:36 
    case STR_OS_EQ:
    {    
        if (sub_id==STR_OS_STANDARD)
           EQ_type=1;
        else if (sub_id==STR_OS_CLASSIC)
           EQ_type=2;
        else if (sub_id==STR_OS_ROCK)
           EQ_type=3;
        else if (sub_id==STR_OS_JAZZ)
           EQ_type=4;
        else if (sub_id==STR_OS_POP)
           EQ_type=5;
        else if (sub_id==STR_OS_ELECTRON)
           EQ_type=6;
        else if (sub_id==STR_OS_LIGHT_MUSIC)
           EQ_type=7;
    	
		SetEQ();        
        printf("I have finished EQ setting!Haha!\n");        
        break;   
    }

    case STR_OS_SURR:
    {     
        if (sub_id==STR_OS_CONCERT)
           surround_type = 2;
        else if (sub_id==STR_OS_CHURCH)
           surround_type = 3;
        else if (sub_id==STR_OS_PASSIVE)
           surround_type = 4;
        else if (sub_id==STR_OS_WIDE)
           surround_type = 5;
        else if (sub_id==STR_OS_LIVE)
           surround_type = 6;
        else if (sub_id==STR_OS_OFF)
           surround_type = 1;
    	    
		SetSurround();
	    printf("I have finished sound field setting!Haha!\n");        
        break;  
    }   
#endif      //#ifdef SOUND_EFFECT_MENU

#ifdef DIVIDE_AC3_DTS_SPDIF_OUTPUTS
	case STR_OS_AC3_DIGITAL:
        if(coding_mode_now&(AUDIF_CODING_MODE_AC3) && (cd_type_loaded==CDDVD))
            str_os_ac3_out(sub_id);
            break;
	case STR_OS_DTS_DIGITAL:	    
        if((coding_mode_now&(AUDIF_CODING_MODE_DTS )&& (cd_type_loaded==CDDVD) )|| ((cd_type_loaded==CDDA) && (cd_subtype==CD_DTS)) )
            str_os_dts_out(sub_id);
            break;
#endif//DIVIDE_AC3_DTS_SPDIF_OUTPUTS

	case STR_OS_AUD_OUT:
#ifdef DIVIDE_AC3_DTS_SPDIF_OUTPUTS
    if((coding_mode_now!=AUDIF_CODING_MODE_AC3)&& (coding_mode_now!=AUDIF_CODING_MODE_DTS)  && (cd_subtype!=CD_DTS))
#endif
            str_os_aud_out(sub_id);
            #ifdef TV_WANT_6500_AUDIO_MUTE//caoh 2006-7-11 02:59ÏÂÎç only for some tv don't mute RAW and DTS audio
              if((cd_type_loaded==CDDVD)||(pDSV->dAudio_coding_md == 6))
               scaler_6500_main();
            #endif
            //yanlb added 2004/07/07
            #ifdef  REMB_3DSOUND 
            {
                exe_3Dsound(sound_sel,user_osd_set); 
            }
            #endif
            
            break;

			//20041222 JSLIN	//case for STR_OS_FREQ_MASK should always exist
            case STR_OS_FREQ_MASK:
		    {
                //2004AUDDRV audif_set_frequency_mask(setup_sel[setup_pos[1]][setup_pos[2]] - MIN_ITEM_SEL);
                //AUDIF_Set_FrqMsk(setup_VA[SETUP_VA_FREQ_MASK] - MIN_ITEM_SEL);
			    setup_SetFreqMaskConfig();
			    break;
            }
            
            #ifndef NO_MIC
            case STR_OS_MIC_ONOFF:
                if (sub_id==STR_OS_AUTO) {
                    AUDIF_Set_MICStatus(STATUS_AUTO, 0);//2004AUDDRV AudioSetMIC(2, 0); //Set MIC auto detect
        		} else if (sub_id==STR_OS_ON) {
                    AUDIF_Set_MICStatus(STATUS_ON, 0);//2004AUDDRV AudioSetMIC(1, 0); //Set MIC on(the second parameter:unsed now)
				} else {
					AUDIF_Set_MICStatus(STATUS_OFF, 0);//2004AUDDRV AudioSetMIC(0, 0); //Set MIC off(the second parameter:unsed now)
				}
				break;
            #endif  
            
         #ifdef MIC_MUTE_PIN   // lxg 2006-7-1 09:31  Use a GPIO to control MIC mute
            case STR_OS_MIC_ONOFF:
                if (sub_id==STR_OS_ON) 
                	{ 
                		mic_mute_flag=0;    // When use analog MIC ,GPIO_MUTE() can't work ,or there will no mic sound output  
                		Mic_mute_pin_output_low();
        		      } 
        		    else if (sub_id==STR_OS_OFF) 
        			    {
        			    	mic_mute_flag=1;   // GPIO_MUTE() can  work now ,polling.c
                    Mic_mute_pin_output_high();
				          } 
				    break;
        #endif     
            
            case STR_OS_DOWNMIX_SETUP:
                str_os_downmix_setup(sub_id);
                break;

            case STR_OS_SUBWOOFER:
                if (sub_id==STR_OS_ON) {
                    #ifdef SPEAKER_CONFIG
                    speaker_subwoofer=STATUS_ON;
                    #endif
                    //sub-woof on command to DSP
                    AUDIF_Set_SubWoof(STATUS_ON);//2004AUDDRV AudioSetSubWoof(1);
                } else {
                    #ifdef SPEAKER_CONFIG
                    speaker_subwoofer=STATUS_OFF;
                    #endif
                    //sub-woof on command to DSP
                    AUDIF_Set_SubWoof(STATUS_OFF);//2004AUDDRV AudioSetSubWoof(0);
                }
                //#ifdef TEST_BASS_MANAGEMENT
                //  #ifdef TEST_BASS_COMMAND
                //    AudioSetBassMag(SetBassConfig());
                //  #else
                //    DSPReset();
                //  #endif                                            
                //#endif
                break;

            case STR_OS_DOLBY_OP_SETUP:
                printf("ac3: op mode\n");
                if(sub_id==STR_OS_DOLBY_LINE_SETUP) {
                    printf("ac3: line op mode\n");
                    AUDIF_Set_OutputMode(OUT_LineModeK2, 0);//2004AUDDRV AudioSetOutputMode(0x20, 0); //Set Output mode(0x20:AC3 line mode)
                } else
				if(sub_id==STR_OS_DOLBY_RF_SETUP) {
					printf("ac3: RF op mode\n");
					AUDIF_Set_OutputMode(OUT_RFModeK3, 0);//2004AUDDRV AudioSetOutputMode(0x10, 0); //Set Output mode(0x10:AC3 RF mode)
				}

                #ifndef NO_AC3_DYNAMIC_RANGE
                if (full_scrn & SETUP)
					setup_ShowAC3DynamicRange(); //Jeff 20020621
				set_AC3DynamicRange();
                #endif //#ifndef NO_AC3_DYNAMIC_RANGE

					break;
		
            case STR_OS_DUAL_MONO_SETUP:
                printf("ac3: dual mono mode\n");
                if(sub_id==STR_OS_STEREO) {
                    printf("ac3: stereo mode\n");
                    AUDIF_Set_OutputMode(OUT_NoVocal, 0);//2004AUDDRV AudioSetOutputMode(0x30, 0); //Set Output mode(0x30:AC3 no vocal)
        		} else if(sub_id==STR_OS_CHL) {
					printf("ac3: ch L mode\n");
					AUDIF_Set_OutputMode(OUT_LeftVocal, 0);//2004AUDDRV AudioSetOutputMode(0x40, 0); //Set Output mode(0x40:AC3 left vocal)
				} else if(sub_id==STR_OS_CHR) {
					printf("ac3: ch R mode\n");
					AUDIF_Set_OutputMode(OUT_RightVocal, 0);//2004AUDDRV AudioSetOutputMode(0x50, 0); //Set Output mode(0x50:AC3 right vocal)
				} else {
					//STR_OS_MIX_MONO_SETUP
					printf("ac3: down-mix mode\n");
					AUDIF_Set_OutputMode(OUT_BothVocal, 0);//2004AUDDRV AudioSetOutputMode(0x60, 0); //Set Output mode(0x60:AC3 both vocal)
				}
				break;

            #ifdef AC3_BASS_MANAGEMENT
			case STR_OS_BASS_MANAGEMENT: // Robert 021016

                #ifndef SPHE8202//def DESAY_DVD   //fengjl edit it to avoid noise when change bass mode between "ALL LG SPK" and "MIXED SPK" 2004-06-24 13:50
                if ( (GetCurrentFileType() != CDROM_WMA)&&(cd_subtype != CD_DTS) )
    			#endif 
				AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
				break;
            #endif //#ifdef AC3_BASS_MANAGEMENT

            case STR_OS_REGION_CODE:
            #if defined(DEFAULT_REGION_ONE)
            	UserSet.P_RCD = 1;
            #elif defined(DISPLAY_DISPLAY_FW_VERSION)||defined(USE_ANGLE_AND_DISPLAY_SHOW_FW_VERSION)
                if(setup_pos[SETUP_ML3] != 8)
                    UserSet.P_RCD = setup_pos[SETUP_ML3] - 1;
                else
                    UserSet.P_RCD = setup_pos[SETUP_ML3] - 8;
            #else	
                UserSet.P_RCD = setup_sel[setup_pos[1]][setup_pos[2]] - MIN_ITEM_SEL;
            #endif    
                if (UserSet.P_RCD>6) {
					setup_sel[setup_pos[1]][setup_pos[2]] = MIN_ITEM_SEL;
					UserSet.P_RCD = setup_sel[setup_pos[1]][setup_pos[2]] - MIN_ITEM_SEL;
                }
                
                #ifdef SAVE_REGION_AND_RATING_ITEM
                run_save_total_userSet();
                #endif
                
                break;
            /*
			case STR_OS_SHARPNESS:
				SetSharpness(setup_sel[setup_pos[1]][setup_pos[2]] - MIN_ITEM_SEL);
				break;
            */

			case STR_OS_BRIGHTNESS:
				SetBrightness(setup_sel[setup_pos[1]][setup_pos[2]] - MIN_ITEM_SEL);
				break;

			case STR_OS_CONTRAST:
				SetContrast(setup_sel[setup_pos[1]][setup_pos[2]] - MIN_ITEM_SEL);
				break;

			case STR_OS_HUE:
				SetHUE(setup_sel[setup_pos[1]][setup_pos[2]] - MIN_ITEM_SEL);
				break;

			case STR_OS_SATURATION:
				SetSaturation(setup_sel[setup_pos[1]][setup_pos[2]] - MIN_ITEM_SEL);
				break;

            #ifdef DIP_CFG_ENABLE
			case STR_OS_DEINTLC:
				SetDeInterlace(setup_sel[setup_pos[1]][setup_pos[2]] - MIN_ITEM_SEL);
				break;
            #endif//#ifdef DIP_CFG_ENABLE

#ifdef SUPPORT_PROLOGIC_II		// alan, 2003/7/11 03:14¤U¤È
			case STR_OS_PROLOGIC:
            	str_os_prologic2(sub_id);
				break;
            #ifdef SUPPORT_PROLOGIC_II_ADVANCE_SETTING // chenzhao 2005-5-12
            case STR_OS_PL_PANORAMA:
                str_os_prologic2_panorama(sub_id);
                break;
            #endif//SUPPORT_PROLOGIC_II_ADVANCE_SETTING
#endif

        #ifdef SPEAKER_CONFIG //ycwen 2005/5/17 Bass Management //chenzhao20060116
            case STR_OS_FSPK:            
                if(sub_id==STR_OS_BASS_MODE_1)speaker_front=SPEAKER_LARGE;
                else if(sub_id==STR_OS_BASS_MODE_2)speaker_front=SPEAKER_SMALL;
                else if(sub_id==STR_OS_OFF)speaker_front=SPEAKER_OFF;
                AUDIF_Set_BassConfig(FRNT_SPK, setup_VA[SETUP_VA_FSPK]-MIN_ITEM_SEL);
                break;
            case STR_OS_CSPK:	            
                if(sub_id==STR_OS_BASS_MODE_1)speaker_center=SPEAKER_LARGE;
                else if(sub_id==STR_OS_BASS_MODE_2)speaker_center=SPEAKER_SMALL;
                else if(sub_id==STR_OS_OFF)speaker_center=SPEAKER_OFF;
                AUDIF_Set_BassConfig(CNTR_SPK, setup_VA[SETUP_VA_CSPK]-MIN_ITEM_SEL);
                break;
		    case STR_OS_SSPK:					
                if(sub_id==STR_OS_BASS_MODE_1)speaker_surround=SPEAKER_LARGE;
                else if(sub_id==STR_OS_BASS_MODE_2)speaker_surround=SPEAKER_SMALL;
                else if(sub_id==STR_OS_OFF)speaker_surround=SPEAKER_OFF;
                AUDIF_Set_BassConfig(SRND_SPK, setup_VA[SETUP_VA_SSPK]-MIN_ITEM_SEL);			
               //2004AUDDRV #ifdef TEST_BASS_COMMAND
               //2004AUDDRV     AudioSetBassMag(SetBassConfig());
               //2004AUDDRV #else
               //2004AUDDRV     DSPReset();
               //2004AUDDRV #endif
			    break;
		#endif
		
#ifdef SCALER_6500 //helm for scaler 6500 050707
            case STR_SPHE6500_FMT:
                 /*
                 ** helm move the selection to /scaler/6500_scl.c
                 */ 
		 #ifdef Simplay_warning	//eric lin,2006-07-06,for Simplay format warning message
                 hdmi_sel=setup_sel[3][5];//eric lin,base on HDMI_OUTPUT location.
		 #endif	//#ifdef Simplay_warning 
		                  
                 SPHE6500_Select_Format(sub_id);
                 
 		 #ifdef Simplay_warning	//eric lin,2006-07-06,for Simplay format warning message
                 setup_sel[3][5]=hdmi_sel;                 
		 #endif	//#ifdef Simplay_warning                    
                break;
#endif

                
			default:
				break;
    }

    //special setting
    //printf("sub_id:%x tt_id:%x",sub_id,tt_id);
    switch(sub_id)
    {
	case STR_OS_NTSC:
	        #ifdef SCALER_6500  //helm 050628	
                dvi311_tv_mode = STR_OS_NTSC;
	        if (dvi311_mode == Mode_576I)
	            dvi311_mode=Mode_SXGA;	

                #endif	
		tv_format=MODE_NTSC;
		break;
		
#ifdef SUPPORT_PAL60
	case STR_OS_PAL60:
	        #ifdef SCALER_6500  //helm 050628	
                dvi311_tv_mode = STR_OS_NTSC;
                #endif	
		tv_format=MODE_PAL60;
		break;
#endif//SUPPORT_PAL60

#ifdef SUPPORT_PALM			//gerry,2004-1-8 13:49
	case STR_OS_PALM:
	        #ifdef SCALER_6500  //helm 050628	
                dvi311_tv_mode = STR_OS_NTSC;
                #endif	
		tv_format=MODE_PALM;
		break;
#endif//SUPPORT_PALM

	case STR_OS_PAL:
                #ifdef SCALER_6500  //helm 050628		
	             dvi311_tv_mode = STR_OS_PAL;
	             if (dvi311_mode == Mode_SXGA)
	                 dvi311_mode=Mode_576I;		             	
                #endif		
		tv_format=MODE_PAL;
		break;

#ifdef SUPPORT_PALN
	case STR_OS_PALN:
		tv_format=MODE_PALN;
		break;
#endif//SUPPORT_PAL60

#ifdef SUPPORT_PALNc
	case STR_OS_PALNc:
		tv_format=MODE_PALNC;
		break;
#endif//SUPPORT_PAL60

	case STR_OS_AUTO:
		if(tt_id==STR_OS_TV_SYS)
		{
			tv_format=MODE_AUTO;
		}
		break;

		// b10~b11 initial display aspect ratio,
		// b8~b9 Current display mode
		// VI4-171
		// 00b: 4:3 ,01b:Not specified ,11b: 16:9
		// 00b: Normal(4:3) or Wide(16:9)
		// 01b: PS 10b:LB
    case STR_OS_16_9:       str_os_16_9();          break;
    case STR_OS_4_3LB:      str_os_4_3lb();         break;
    case STR_OS_4_3PS:      str_os_4_3ps();         break;

    case STR_OS_P_SCAN_YUV: 
    #ifdef SUPPORT_HD_RESOLUTION
        if(setup_VA_EN[SETUP_VA_VIDEO] == 1)       
    #endif	
        {
             #ifdef SUPPORT_SPI
             
             tv_out_id = P_SCAN;
             search_ap_tv_out_id();
             
             #ifdef STORE_VIDEO_PARAMETER
             res = WriteToI2c(0xa0, TV_OUT_ID_ADDR,(BYTE *)&tv_out_id,1);
             if(res<0)
             {
               BYTE i=0;
               for(i=0;((i<15)&&(res<0));i++)
               {
                 res = WriteToI2c(0xa0, TV_OUT_ID_ADDR, (BYTE *)&tv_out_id, 1);
                 printf("tv_out_id store error,retry.......i%d res:%d\n",i,res);
               }
             }
             #endif
             
             if(pdvd_mode == AV_OUTPUT_MODE)
             {
               sp8200tv_setup_custom_output(TV_OUT_YBRRgb);
               //printf("exe in output mode and YPbPr ouput\n");
             }
             else
             {//just record
               //printf("exe in Pdvd mode and setup YPbPr ouput ,just record...\n");
             }
             #else
             str_os_pscan_yuv();     
             #endif    
        }   
    break;
	
    case STR_OS_YCbCr:
    #ifdef SUPPORT_HD_RESOLUTION
        if(setup_VA_EN[SETUP_VA_VIDEO] == 1)     
    #endif
        {
             #ifdef SUPPORT_SPI
             tv_out_id = INTERLACE;
             search_ap_tv_out_id();
             #ifdef STORE_VIDEO_PARAMETER
             res = WriteToI2c(0xa0, TV_OUT_ID_ADDR,(BYTE *)&tv_out_id,1);
             if(res<0)
             {
               BYTE i=0;
               for(i=0;((i<15)&&(res<0));i++)
               {
                 res = WriteToI2c(0xa0, TV_OUT_ID_ADDR, (BYTE *)&tv_out_id, 1);
                 printf("tv_out_id store error,retry.......i%d res:%d\n",i,res);
               }
             }
             #endif
                
               
             if(pdvd_mode == AV_OUTPUT_MODE)
             {
               sp8200tv_setup_custom_output(TV_OUT_YUVRGB);
               //printf("exe in output mode and YCbCr ouput\n");
             }
             else
             {//just record
               //printf("exe in Pdvd mode and setup YCbCr ouput,just record...\n");
             }
             #else
             str_os_ycbcr();         
             #endif
        }   
    break;
    case STR_OS_TV_RGB:     
    #ifdef SUPPORT_HD_RESOLUTION
        if(setup_VA_EN[SETUP_VA_VIDEO] == 1)      
    #endif        
        {
            str_os_tv_rgb();      
        }            
        break;
    case STR_OS_PC_VGA:
    #ifdef SUPPORT_HD_RESOLUTION
        if(setup_VA_EN[SETUP_VA_VIDEO] == 1)     
    #endif
        {
            str_os_pc_vga();        
        }
        break;
    case STR_OS_S_VIDEO:
        
    #ifdef SUPPORT_HD_RESOLUTION
        if(setup_VA_EN[SETUP_VA_VIDEO] == 1) 
    #endif
        {
             #ifdef SUPPORT_SPI
             tv_out_id = TV_SVIDEO;
             search_ap_tv_out_id();  
             
             #ifdef STORE_VIDEO_PARAMETER
             res = WriteToI2c(0xa0, TV_OUT_ID_ADDR,(BYTE *)&tv_out_id,1);
             if(res<0)
             {
               BYTE i=0;
               for(i=0;((i<15)&&(res<0));i++)
               {
                 res = WriteToI2c(0xa0, TV_OUT_ID_ADDR, (BYTE *)&tv_out_id, 1);
                 printf("tv_out_id store error,retry.......i%d res:%d\n",i,res);
               }
             }
             #endif
               
             if(pdvd_mode == AV_OUTPUT_MODE)
             {
               sp8200tv_setup_custom_output(TV_OUT_CScRGB);
               //printf("exe in output mode and SV/CVBS ouput\n");
             }
             else
             {//just record id!!!
               //printf("exe in Pdvd mode and setup SV/CVBS ouput,just record...\n");
             }
             #else
             str_os_svideo();
             #endif
        }            
    break;

#ifdef SUPPORT_HD_RESOLUTION
    case STR_OS_HD_OFF:
        setup_VA_EN[SETUP_VA_VIDEO] = 1;    // for enable the "VIDEO" item of setup menu    
        ap_tv_out_id=0;
        tv_out_id=INTERLACE;  
        //joshua, jpeg re-decoding between SD and HD
        if(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
        {
            jpg_redecode_byTvResolution();
        }    
        setup_tv_out(tv_out_id);  // When HD off, change the "VIDEO" selection to "INTERLACE-YUV".
        setup_SetPScan();           // Then save the result to the setup menu buffer. by robert.chang, 2006-10-02
    break;
        
    case STR_OS_HD_720P:
           setup_VA_EN[SETUP_VA_VIDEO] = 2;  // for disable the "VIDEO" item of setup menu
           str_os_hd_720p(); 
    break;
        
    case STR_OS_HD_1080I:
           setup_VA_EN[SETUP_VA_VIDEO] = 2; // for disable the "VIDEO" item of setup menu         
           str_os_hd_1080i(); 
    break;
    
#endif//#ifdef SUPPORT_HD_RESOLUTION

#ifdef SETUP_CVBS_OUTPUT
    case STR_OS_CVBS:
        setup_tv_out(CVBS);
		//ap_tv_out_id=TV_SVIDEO;//nono 2003-8-1 18:05
		search_ap_tv_out_id();//terry,2003/8/19 03:21PM

#ifdef SUPPORT_SCART_TV//SPHE8202//nono 4-3-27 21:35
        SET_SCART_GPIO_SFT_CFG_CTRL();
        SET_SCART_TO_CVBS();
#endif//#ifdef SUPPORT_SCART_TV//SPHE8202//nono 4-3-27 21:35

        #if defined(SCART_TV)||defined(KSD_SCART_TV)||defined(SCART_TV_2)||defined(SCART_TV_4)||defined(SCART_TV_5)//wangfeng 2003-12-2 23:03
		SET_SCART_RGB(0);
        #endif //#ifdef SCART_TV
        
        #if defined(SCART_TV_2)&&defined(THAKRAL_DVD)
		SET_SCART_RGB(1);
		#else
		//SET_SCART_RGB(0);
		SCART_TV_SET_TO_CVBS();
		#endif

		#if defined(SCART_TV_3)&&defined(DESAY_DVD)
        SET_SCART_RGB(1);
        #elif defined(SCART_TV_3)&&defined(SKYWORTH_DVD)
        SET_SCART_RGB(0);
        #endif
        break;
#endif//#ifdef SETUP_CVBS_OUTPUT

#ifdef RATING_8
	case STR_OS_RATING_1:
		UserSet.ParentalLvl=1;
		break;
	case STR_OS_RATING_2:
		UserSet.ParentalLvl=2;
		break;
	case STR_OS_RATING_3:
		UserSet.ParentalLvl=3;
		break;
	case STR_OS_RATING_4:
		UserSet.ParentalLvl=4;
		break;
	case STR_OS_RATING_5:
		UserSet.ParentalLvl=5;
		break;
	case STR_OS_RATING_6:
		UserSet.ParentalLvl=6;
		break;
	case STR_OS_RATING_7:
		UserSet.ParentalLvl=7;
		break;
	case STR_OS_RATING_8:
		UserSet.ParentalLvl=8;
		break;
#ifdef EASTECH_NO_PARENTAL_CONTROL  //liumzh , add for setup reengine 2005-6-2 23:38
    case STR_OS_NO_PARENTAL:
        UserSet.ParentalLvl=0xf;
        break;
#endif
#else
	case STR_OS_NO_ADULT:
		UserSet.ParentalLvl=6;//THEATRICAL level
		break;
	case STR_OS_KID_ONLY:
		UserSet.ParentalLvl=1;//KID level
		break;
	case STR_OS_VIEW_ALL:
		UserSet.ParentalLvl=8;//adult level
		break;
#endif
#ifdef ADJUST_JPEG_SLIDE_TIME  //lyc 2005-3-7 17:33
     BYTE  SlideTimeFlag;
     case STR_OS_15_SEC:                 
                 jpg_slide_time = 1500;
                 SlideTimeFlag=1;
                 UserSet.SETUP_JpegSlideTimeFlag = SlideTimeFlag;
                 //WriteToI2c(0xa0, ADDR_I2C_JPEG_SLIDE_TIME,&SlideTimeFlag,1);
		break;
     case STR_OS_30_SEC:                
                 jpg_slide_time = 3000;
                 SlideTimeFlag=2;
                 UserSet.SETUP_JpegSlideTimeFlag = SlideTimeFlag;
                 //WriteToI2c(0xa0, ADDR_I2C_JPEG_SLIDE_TIME,&SlideTimeFlag,1);  
                 break;
     case STR_OS_45_SEC:                
                 jpg_slide_time = 4500;
                 SlideTimeFlag=3;
                 UserSet.SETUP_JpegSlideTimeFlag = SlideTimeFlag;
                 //WriteToI2c(0xa0, ADDR_I2C_JPEG_SLIDE_TIME,&SlideTimeFlag,1);
                 break;      
#endif
	default:
		break;
    }

    if(exe)
    {
        if((tt_id==STR_OS_OSD)||(tt_id==STR_OS_DOLBY_OP_SETUP))
        {
            setupLevel = 1;
            if (full_scrn & SETUP)
            #ifdef PULIANG_SETUP_MENU  //yaowh add 04-12-15
            {
                show_menu_setup_flag=1;
                ShowSetupPage(2);
                show_menu_setup_flag=0;
            }
            #else
            ShowSetupPage(2);
            #endif
        }else if(tt_id==STR_OS_TV_SYS)
        {
            #ifdef SUPPORT_HD_RESOLUTION  //modify the N/P behavior for HD, by robert.chang, 2006-07-18
            if(GET_TV_RESOLUTION()  == HD_720){
                if(tv_format == MODE_NTSC) {
                    sp8200tv_set_hd_mode(HD_720P_F60, 1);
                }                
                else if(tv_format == MODE_PAL) {
                    sp8200tv_set_hd_mode(HD_720P_F50, 1);
                }                
                set_vpp_disp_window(0,0,1280,720);
            }
            else if(GET_TV_RESOLUTION()  == HD_1080){
                if(tv_format == MODE_NTSC) {
                    sp8200tv_set_hd_mode(HD_1080I_F60, 1);
                }                
                else if(tv_format == MODE_PAL) {
                    sp8200tv_set_hd_mode(HD_1080I_F50, 1);
                }    
                set_vpp_disp_window(0,0,1920,1080);
            }
            #endif//#ifdef SUPPORT_HD_RESOLUTION  //modify the N/P behavior for HD, by robert.chang, 2006-07-18
            
            setup_tv_format(tv_format);
            
            update_tv_format_sel();//terry,2004/2/5 12:11PM
            
            #ifndef OP_IR //caoh 05/08/02
            osd_move_subtitle_region(); // 2005/07/12 yltseng
            #endif

            #ifdef SUPPORT_SPI
            #ifdef STORE_VIDEO_PARAMETER
            res = WriteToI2c(0xa0, TV_FORMAT_ADDR,(BYTE *)&tv_format,1);
            if(res<0)
            {
              BYTE i=0;
              for(i=0;((i<15)&&(res<0));i++)
              {
                res = WriteToI2c(0xa0, TV_FORMAT_ADDR, (BYTE *)&tv_format, 1);
                printf("tv_format store error,retry.......i%d res:%d\n",i,res);
              }
            }
            //printf("exe record tv_format:%d.....\n",tv_format);
            #endif
            #endif
            //setVPP_TVformat(tv_format);
            
            #ifdef SCALER_6500 //helm 050725                
            extern BYTE Run_Default_Setting;              
            if (Run_Default_Setting){
                HDMI_AUTO_Mode(sub_id);    	
                scaler_6500_main();

#ifdef HDMI_FMT_RESTORE      //helm set this flag for restoring format, 060312
                if (!default_set)
                    FMT_CHANGE = 1;
#endif                

            }    
            #endif
                        
#ifdef SETUP_PAL_ADJUST_IN_INDIGO_UI   // zxb 2006-8-29 14:15
		if(full_scrn&SETUP)
		{          
         	osd_init_setup();        	 
    	 	setup_force_showPage();
    	}
#endif    
                        
        }else if(sub_id==STR_OS_RETURN_MAIN_SETUP)
        {
            setup_func_return_main();
        }else if(sub_id==STR_OS_EXIT_MENU)
        {
            ExitSetupPage(1);
        }
    }
    
}

#ifdef SELECT_MEDIA_IN_SETUPMENU  //denghg  add  for  change media type  2005-2-4 9:42
extern void SwitchMedia(BYTE direction);//chenzhao20060116
void change_media_type(void)  
{   
    
    printf("============  change_media_type ============\n");
    UINT16 P = 0;                 //denghg add  2004-12-17 22:04
    UINT16 I = 0;
    UINT16 S = 0;
    P = setup_getItemPos(STR_OS_MEDIA_TYPE);
    I = P & 0xff;
    P = P >> 8;
    S = setup_VA[SETUP_VA_MEDIA_TYPE];
    printf("setup_VA[SETUP_VA_MEDIA_TYPE]=%d\n",S);
   
    switch(setup_item[P][I][S])
    {
        case STR_OS_MEDIA_TYPE:
        	if (system_state == SYSTEM_OPEN)	//Maoyong 2004/8/11 can't switch in OPEN state
        	{
        	    break; 
        	}   			
        
        case STR_OS_MEDIA_DISC:
            if (media_type == MEDIA_CARD)
            {
                #ifdef SPHE8202_CARD_STORAGE 
                  Card_power_off();   //wthsin,  2004/9/1 10:13am
                #endif 
                  media_changed_flag = 1;
                if (detect_type != 0)  //qinhua ,add 2005-9-13 14:20//need detect CARD/USB.
                {
                  SwitchMedia(CARD2CD);
                }
                printf("========= Switch to Disk Media ==========\n");
            }
        	break;
        	
         case STR_OS_MEDIA_USB:
            if ((media_type == MEDIA_CD) || (storage_type != USB_DEVICE) )
            {
                #ifdef SPHE8202_CARD_STORAGE 
                Card_power_off();   //wthsin,  2004/9/1 10:13am
                #endif      			    	
                media_changed_flag = 1;
                storage_type = USB_DEVICE;
                
                if (detect_type != 0)  //qinhua ,add 2005-9-13 14:20//need detect CARD/USB.
                {
                    #ifdef USB_SEPARATE_DETECT_AND_ENUM//added by wangwei,2005-11-1 22:30
                    extern void EnumUsb(void);
                    void EnumUsb(void);
                    #endif//USB_SEPARATE_DETECT_AND_ENUM        
                    SwitchMedia(CD2CARD);
                }
                printf("========= Switch to USB Device ==========\n");
            }
    	    break;
    	    
    	case STR_OS_MEDIA_CARD:	//Maoyong 2004/8/11 for eastech TYPE 3 CARD Storage
            if ((media_type == MEDIA_CD) || ((storage_type != MS_CARD_DEVICE) && (storage_type != SD_CARD_DEVICE) && (storage_type != SMC_CARD_DEVICE)
            #ifdef SUPPORT_STOP_PLAY_READ_USB_CARD  //qinhua,add CF CARD,2005-11-2 20:53 for so as exit setup to read cf card 
             &&(storage_type != CF_CARD_DEVICE)
            #endif  
               )) 
            {
                  media_changed_flag = 1;
                  if (detect_type & MS_CARD_DEVICE)
                  {
                      storage_type = MS_CARD_DEVICE;
                  }
                  else if (detect_type & SD_CARD_DEVICE)
                  {
                      storage_type = SD_CARD_DEVICE;
                  }
                  else if (detect_type & SMC_CARD_DEVICE)
                  { 
                  	storage_type = SMC_CARD_DEVICE;  
                  }
                  #ifdef SUPPORT_STOP_PLAY_READ_USB_CARD  //qinhua ,add,2005-11-2 20:55
                  else if (detect_type & CF_CARD_DEVICE)  
                  { 
                    storage_type = CF_CARD_DEVICE;  
                  }
                  #endif  
                  
                  if (detect_type!=0)  //qinhua ,add 2005-9-13 14:20
                  {
                    SwitchMedia(CD2CARD);
                  }
                  printf("========= Switch to MS/SD/SMC CARD Device 2222222222222 ==========\n");
            }
    		 break;
    		 
      default:
    		break; 		
   
    }

}
#endif   //denghg  end SELECT_MEDIA_IN_SETUPMENU  2005-2-4 9:46
#else
//#ifdef SPHE8202_CARD_STORAGE 
//   extern void Card_power_off();                         
//#endif

#ifdef SLEEP_CONTROL_COUNTER   //liumzh 2004-12-10 23:53
extern	UINT32 counter_sleep_control ;
extern	UINT32 sleep_time ;//seconds
#endif
void exe_setup_function(UINT8 tt_id, UINT8 sub_id, UINT8 exe)
{
    //language,osd,subtitle,audio
    //printf("tt:%d sub:%d exe:%x\n",tt_id,sub_id,exe);
    #ifdef STORE_VIDEO_PARAMETER
    BYTE res; 
    #endif     
    
    #ifdef ADD_DVI311_SETUP
    exe_setup_function_dvi(tt_id,  sub_id,  exe);
	#endif
    switch(tt_id)
    {
    #ifdef SELECT_MEDIA_IN_SETUPMENU
    case STR_OS_MEDIA_TYPE:
    		if(system_state == SYSTEM_OPEN)	//Maoyong 2004/8/11 can't switch in OPEN state
    			break;
    			
    		switch(sub_id)
    		{
    			case STR_OS_MEDIA_DISC:
    			    if(media_type == MEDIA_CARD)
                    {
//                      #ifdef SPHE8202_CARD_STORAGE  //Something wrong in switch Disk/Card ,mark it by wthsin 2004/9/6 04:32pm
//                        Card_power_off();   //wthsin,  2004/9/1 10:13am
//                      #endif 
                        media_changed_flag = 1;
                        SwitchMedia(CARD2CD);
                        printf("========= Switch to Disk Media ==========\n");
                    }
    				break;
			    case STR_OS_MEDIA_USB:
			        if( (media_type == MEDIA_CD) || (storage_type != USB_DEVICE) )
    			    {
//    			      #ifdef SPHE8202_CARD_STORAGE 
//                        Card_power_off();   //wthsin,  2004/9/1 10:13am
//                    #endif  
    			        media_changed_flag = 1;
    			        storage_type = USB_DEVICE;
                        SwitchMedia(CD2CARD);
                        printf("========= Switch to USB Device ==========\n");
                    }
				    break;
			    case STR_OS_MEDIA_CARD:	//Maoyong 2004/8/11 for eastech TYPE 3 CARD Storage
                    if( (media_type == MEDIA_CD) || ( (storage_type != MS_CARD_DEVICE) && (storage_type != SD_CARD_DEVICE) && (storage_type != SMC_CARD_DEVICE) )  )
    			    {
    			        media_changed_flag = 1;
    			        if(detect_type & MS_CARD_DEVICE)
    			            storage_type = MS_CARD_DEVICE;
                        else if(detect_type & SD_CARD_DEVICE)
    			            storage_type = SD_CARD_DEVICE;
    			        else if(detect_type & SMC_CARD_DEVICE) 
    			        	storage_type = SMC_CARD_DEVICE;  
                        SwitchMedia(CD2CARD);
                        printf("========= Switch to MS/SD/SMC CARD Device ==========\n");
                    }
				    break;
    		}
    		break;
    #endif //#ifdef SELECT_MEDIA_IN_SETUPMENU

    #ifdef TUNR_OFF_PARENTAL_LVL
    case STR_OS_RATING:
	bTurnOffParentalLVL=0;//terry,2002/9/20 11:40PM
	break;
    #endif
#ifdef ADD_P_SCAN_ONOFF
	case STR_OS_P_SCAN_YUV:  //add by Tom 20040714
		if(sub_id==STR_OS_ON)
 			str_os_pscan_yuv();        
		else
			str_os_ycbcr(); 
		break;
#endif
#ifdef SLEEP_CONTROL_COUNTER
    case STR_OS_SLEEP_SETUP:
{
	if(sub_id==STR_OS_SLEEP_120MIN)
		{
		  sleep_time=120;
		  counter_sleep_control=1;
		}
	else if(sub_id==STR_OS_SLEEP_90MIN)
		{
		  sleep_time=90;	
		 counter_sleep_control=1;
		}
	else if(sub_id==STR_OS_SLEEP_60MIN)
		{
		  sleep_time=60;	
		counter_sleep_control=1;
		}
	else if(sub_id==STR_OS_SLEEP_45MIN)
		{
		  sleep_time=45;	 
		counter_sleep_control=1;
		}
	else if(sub_id==STR_OS_SLEEP_30MIN)
		{
		  sleep_time=30;
		 counter_sleep_control=1;
		}
	else if(sub_id==STR_OS_SLEEP_15MIN)
		{
		  sleep_time=15;		
		 counter_sleep_control=1;
	     }
	else if (sub_id==STR_OS_SLEEP_OFF)
		{
		  counter_sleep_control=0;		
		
		}
	
}
		break;
#endif
	case STR_OS_OSD:
		{
			int         i;
		for (i=MIN_ITEM_SEL; i<=MAX_ITEM_SEL; i++) {//nono 2-10-30 17:35
				if (sub_id==setup_item[LANGPAGE][LANGITEM][i])
				{
					break;
			}
			}
			#ifdef SUPER_DEFAULT_OSD_LANG
			if(page==CUSTMPAGEINDEX)
			{
			    UserSet.setup_default_osd_lang = i -2;
                SETUP_OSD_LANG = UserSet.setup_default_osd_lang +2;
			}
			#endif
			//osd_font_mode = i-2;
			osd_font_mode = OSD_LANG_MAP[i-2]; //Jeff 20030217
			#ifdef DVB_MENU_SETUP_STYLE //Maoyong 2004-12-23 14:28 Should set both DVB/DVD language
		    SETUP_OSD_LANG = i;
		    SETUP_DVB_LANG = i;
		               
            if(system_state == SYSTEM_TS)
                run_save_sel_cmd(LANGPAGE, LANGITEM);
            else
                run_save_sel_cmd(INSTALLPAGE, ITEM_LANGUAGE);                
            #endif
		}
		break;
#ifdef DVB_MENU_SETUP_STYLE
    extern int g_iCurrentGMT;
	case STR_OS_TIME_ZONE:
	{
  		switch(sub_id)
   		{
   			case STR_OS_TIME_ZONE1:
   			    printf("GMT\n");
			    g_iCurrentGMT= 0;
   			    break;
   			case STR_OS_TIME_ZONE2:
   			    printf("GMT + 1\n");
			    g_iCurrentGMT= 1;
   			    break;
   			case STR_OS_TIME_ZONE3:
   			    printf("GMT + 2\n");
			    g_iCurrentGMT= 2;
   			    break;
   			case STR_OS_TIME_ZONE4:
   			    printf("GMT + 7\n");
			    g_iCurrentGMT= 7;
   			    break;
   			case STR_OS_TIME_ZONE5:
   			    printf("GMT + 8\n");
			    g_iCurrentGMT= 8;
   			    break;
   		}
   		break;
   	}
#endif
	case STR_OS_SUBTITLE_LANG_SETUP:
		UserSet.SPSTN = 0x40|0x3E;//setting sub-picture on
		if(sub_id==STR_OS_AUTO) {
			sub_id=LCD_EN;//'e' * 256 + 'n';
		} else if(sub_id==STR_OS_OFF) {
			//sub_id=LCD_EN;//'e' * 256 + 'n';
			sub_id=0; //Jeff 20020925
			UserSet.SPSTN =0xffbf;//setting sub-picture on
		}
		UserSet.SPST_LCD = lang_639code[sub_id];//trans_lang_id(sub_id);
			
//#define SETUP_CAN_DIRECT_SEL_SUBTITLE			
#ifdef	SETUP_CAN_DIRECT_SEL_SUBTITLE
		dvd_sel_subtitle_right_now();
#endif
            
		printf("UserSet.SPST_LCD:%d\n",UserSet.SPST_LCD);
		printf("SPTN:%x\n",UserSet.SPSTN);
		break;
			
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:12
    case STR_OS_SUBTITLE_LANG_2ND_SETUP:
        printf("------SETUP MENU select the 2nd subtitle IN!------\n");
        LCD_2 = lang_639code[sub_id];//trans_lang_id(sub_id);
        printf("LCD_2:%x,%d\n",LCD_2,LCD_2);
        language_id=sub_id;
		break;
#endif
		
#if defined(ORITRON_HK_DVD)||defined (DYNAMICRANGEON_OFF)	//fcr 2005-10-12 15:24
case STR_OS_DYNAMICRANGE://libing 2005-6-10 17:01
    	if(sub_id==STR_OS_OFF) 
    {
    	ac3_dynarange=0;//setup_pos[3]-MIN_ITEM_SEL;
		set_AC3DynamicRange();	
	}else
	{
		ac3_dynarange=8;//setup_pos[3]-MIN_ITEM_SEL;
		set_AC3DynamicRange();
	}
	break;    
#endif		
		
	case STR_OS_SSAVER_SETUP:
		break;
    	
    	 #ifdef SUPPORT_TESTSPK  //jiangxl 
	case STR_OS_TESTSPK_MENU:
		if (sub_id==STR_OS_ON) 
       {
        testspk_state=1;
        {
        Start_Test_Speaker();
        }
        }
    else  
        testspk_state=0;
 
		break;
	#endif 	
	#ifdef SAME_DISC_RESUME
	case STR_OS_RESUME:
		if (sub_id==STR_OS_OFF) 
			same_disc_onoff=0;
		else
			same_disc_onoff=1;
		break;
	#endif 			
    #ifdef SWITCH_SUB_DIRECTION//libing 2005-7-15 14:43
	    case STR_OS_OPEN:
		    if(sub_id==STR_OS_ON)
		    	subtitle_ratate_flag = 1;
		    if(sub_id==STR_OS_OFF)
		        subtitle_ratate_flag = 0;
		    break;		
	#endif    
#ifdef SUPPORT_ANGLE_MARK//liweihua add 2004-2-4
	case STR_OS_ANGLE_MARK:
		if (sub_id==STR_OS_OFF) 
		angleflag=1;
		else
		    angleflag=0;
		break;
#endif	

#ifdef SUPPORT_CC_ONOFF//nono 2004-4-11 19:02
	case STR_OS_CLOSED_CAPTION:
		if (sub_id==STR_OS_OFF) 
		tv_l21_enable(0);
		else
		    tv_l21_enable(1);
		break;	
#endif//SUPPORT_CC_ONOFF

#ifdef DYNAMIC_SPECTRUM    //fengjl  for BBK  3-10-21 20:48
    case STR_OS_BAND:
        if (sub_id==STR_OS_OFF) 
		{	
			band_onoff=0;
			bEqDisplay=0;			
		}
		else 
		{	
			band_onoff=1;
	       // bEqDisplay=1;//zhaoyanhua mask for avoid the bug
	    }	
        break;
#endif
    
#ifdef USER_MPEG_LOGO
		case STR_OS_SELECT_LOGO:
		#ifdef JIEKE_DVD
		if (sub_id==STR_OS_JIEKE_SETUP)
		#elif defined(NINTAUS_DVD)//nono 2004-2-17 17:49
		if (sub_id==STR_OS_RESTORE_SETUP1)
		#else
		if (sub_id==STR_OS_RESTORE_SETUP) 
		#endif
		{
			mpeg_logo_onoff=0;
		}
		else
		{
			mpeg_logo_onoff=1;
		}	
		Change_User_Logo();
		need_show_logo=1;
		break;	
#endif 

	case STR_OS_AUDIO_LANG_SETUP:
		UserSet.AST_LCD = lang_639code[sub_id];
		printf("audio lang id:%d %d\n",UserSet.AST_LCD, sub_id);
#ifdef SETUP_CAN_DIRECT_SEL_AUDIO_LANG  //axel 2004/9/21 
        dvd_sel_language_right_now();		
#endif        
		break;
		
	case STR_OS_MENU_LANG_SETUP:
		UserSet.M_LCD = lang_639code[sub_id];;
		
#ifdef SETUP_CAN_DIRECT_SEL_MENU_LANG //terry,2004/9/20 09:58PM
                is_reload_dvd_menu();
#endif 		
		
		break;

#ifdef SOUND_EFFECT_MENU          //sunzhh add 2004-4-30 10:36 
    case STR_OS_EQ:
    {    
        if (sub_id==STR_OS_STANDARD)
           EQ_type=1;
        else if (sub_id==STR_OS_CLASSIC)
           EQ_type=2;
        else if (sub_id==STR_OS_ROCK)
           EQ_type=3;
        else if (sub_id==STR_OS_JAZZ)
           EQ_type=4;
        else if (sub_id==STR_OS_POP)
           EQ_type=5;
        else if (sub_id==STR_OS_ELECTRON)
           EQ_type=6;
        else if (sub_id==STR_OS_LIGHT_MUSIC)
           EQ_type=7;
    	
		SetEQ();        
        printf("I have finished EQ setting!Haha!\n");        
        break;   
    }

    case STR_OS_SURR:
    {     
        if (sub_id==STR_OS_CONCERT)
           surround_type = 2;
        else if (sub_id==STR_OS_CHURCH)
           surround_type = 3;
        else if (sub_id==STR_OS_PASSIVE)
           surround_type = 4;
        else if (sub_id==STR_OS_WIDE)
           surround_type = 5;
        else if (sub_id==STR_OS_LIVE)
           surround_type = 6;
        else if (sub_id==STR_OS_OFF)
           surround_type = 1;
    	    
		SetSurround();
	    printf("I have finished sound field setting!Haha!\n");        
        break;  
    }   
#endif      //#ifdef SOUND_EFFECT_MENU

#ifdef DIVIDE_AC3_DTS_SPDIF_OUTPUTS
	case STR_OS_AC3_DIGITAL:
        if(coding_mode_now&(AUDIF_CODING_MODE_AC3) && (cd_type_loaded==CDDVD))
            str_os_ac3_out(sub_id);
            break;
	case STR_OS_DTS_DIGITAL:	    
        if((coding_mode_now&(AUDIF_CODING_MODE_DTS )&& (cd_type_loaded==CDDVD) )|| ((cd_type_loaded==CDDA) && (cd_subtype==CD_DTS)) )
            str_os_dts_out(sub_id);
            break;
#endif//DIVIDE_AC3_DTS_SPDIF_OUTPUTS

	case STR_OS_AUD_OUT:
#ifdef DIVIDE_AC3_DTS_SPDIF_OUTPUTS
    if((coding_mode_now!=AUDIF_CODING_MODE_AC3)&& (coding_mode_now!=AUDIF_CODING_MODE_DTS)  && (cd_subtype!=CD_DTS))
#endif
            str_os_aud_out(sub_id);
            
            //yanlb added 2004/07/07
            #ifdef  REMB_3DSOUND 
            {
                exe_3Dsound(sound_sel,user_osd_set);
            }
            #endif
            
            break;

            #ifdef USE_FREQ_MASK
		    case STR_OS_FREQ_MASK:
		    {//terry,2004/2/4 02:27PM
			    printf("LPCM_ITEM:%x AUDPAGE:%x\n",LPCM_ITEM,AUDPAGE);
			    printf("SETUP_FREQ_MASK:%x\n",SETUP_FREQ_MASK);
		AUDIF_Set_FrqMsk(SETUP_FREQ_MASK-2);//2004AUDDRV audif_set_frequency_mask(SETUP_FREQ_MASK-2);
			    break;
            }
            #endif //#ifdef USE_FREQ_MASK
                #ifndef NO_MIC
            case STR_OS_MIC_ONOFF:
                if (sub_id==STR_OS_AUTO) {
            AUDIF_Set_MICStatus(STATUS_AUTO, 0);//2004AUDDRV AudioSetMIC(2, 0); //Set MIC auto detect(the second parameter:unsed now)
        		} else if (sub_id==STR_OS_ON) {
		    AUDIF_Set_MICStatus(STATUS_ON, 0);//2004AUDDRV AudioSetMIC(1, 0); //Set MIC always on
				} else {
			AUDIF_Set_MICStatus(STATUS_OFF, 0);//2004AUDDRV AudioSetMIC(0, 0); //Set MIC always off
				}
				break;
                #endif  
            case STR_OS_DOWNMIX_SETUP:
                str_os_downmix_setup(sub_id);
                break;

            case STR_OS_SUBWOOFER:
                if (sub_id==STR_OS_ON) {
                    #ifdef SPEAKER_CONFIG
                    speaker_subwoofer=STATUS_ON;
                    #endif
                    AUDIF_Set_SubWoof(STATUS_ON);//2004AUDDRV AudioSetSubWoof(1); //sub-woof on command to DSP(1:on)
                } else {
                    #ifdef SPEAKER_CONFIG
                    speaker_subwoofer=STATUS_OFF;
                    #endif
                    AUDIF_Set_SubWoof(STATUS_OFF);//2004AUDDRV AudioSetSubWoof(0); //sub-woof on command to DSP(0:off)
                }
//2004AUDDRV #ifdef TEST_BASS_MANAGEMENT
//2004AUDDRV #ifdef TEST_BASS_COMMAND
//2004AUDDRV AudioSetBassMag(SetBassConfig());                        
//2004AUDDRV #else
//2004AUDDRV DSPReset();
//2004AUDDRV #endif                                            
//2004AUDDRV #endif
                break;

            case STR_OS_DOLBY_OP_SETUP:
                printf("ac3: op mode\n");
                if(sub_id==STR_OS_DOLBY_LINE_SETUP) {
                    printf("ac3: line op mode\n");
                    AUDIF_Set_OutputMode(OUT_LineModeK2, 0);//2004AUDDRV AudioSetOutputMode(0x20, 0); //Set Output mode(0x20:AC3 line mode)
                } else
				if(sub_id==STR_OS_DOLBY_RF_SETUP) {
					printf("ac3: RF op mode\n");
					AUDIF_Set_OutputMode(OUT_RFModeK3, 0);//2004AUDDRV AudioSetOutputMode(0x10, 0); //Set Output mode(0x10:AC3 RF mode)
				}

                #ifndef NO_AC3_DYNAMIC_RANGE
                if (full_scrn & SETUP)
					setup_ShowAC3DynamicRange(); //Jeff 20020621
				set_AC3DynamicRange();
                #endif //#ifndef NO_AC3_DYNAMIC_RANGE

					break;
		
            case STR_OS_DUAL_MONO_SETUP:
                printf("ac3: dual mono mode\n");
                if(sub_id==STR_OS_STEREO) {
                    printf("ac3: stereo mode\n");
                    AUDIF_Set_OutputMode(OUT_NoVocal, 0);//2004AUDDRV AudioSetOutputMode(0x30, 0); //Set Output mode(0x30:AC3 no vocal)
        		} else if(sub_id==STR_OS_CHL) {
					printf("ac3: ch L mode\n");
					AUDIF_Set_OutputMode(OUT_LeftVocal, 0);//2004AUDDRV AudioSetOutputMode(0x40, 0); //Set Output mode(0x40:AC3 left vocal)
				} else if(sub_id==STR_OS_CHR) {
					printf("ac3: ch R mode\n");
					AUDIF_Set_OutputMode(OUT_RightVocal, 0);//2004AUDDRV AudioSetOutputMode(0x50, 0); //Set Output mode(0x50:AC3 right vocal)
				} else {
					//STR_OS_MIX_MONO_SETUP
					printf("ac3: down-mix mode\n");
					AUDIF_Set_OutputMode(OUT_BothVocal, 0);//2004AUDDRV AudioSetOutputMode(0x60, 0); //Set Output mode(0x60:AC3 both vocal)
				}
				break;

            #ifdef AC3_BASS_MANAGEMENT
			case STR_OS_BASS_MANAGEMENT: // Robert 021016

                #ifndef SPHE8202//def DESAY_DVD   //fengjl edit it to avoid noise when change bass mode between "ALL LG SPK" and "MIXED SPK" 2004-06-24 13:50
                if ( (GetCurrentFileType() != CDROM_WMA)&&(cd_subtype != CD_DTS) )
    			#endif 
				AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
				break;
            #endif //#ifdef AC3_BASS_MANAGEMENT

            case STR_OS_REGION_CODE:
                UserSet.P_RCD = SETUP_CUSTM_REGION - 2;
                if (UserSet.P_RCD>6) {
					SETUP_CUSTM_REGION = 2;
					UserSet.P_RCD = SETUP_CUSTM_REGION - 2;
                }
                break;
            /*
			case STR_OS_SHARPNESS:
				SetSharpness(SETUP_SHARPNESS - 2);
				break;
            */

			case STR_OS_BRIGHTNESS:
				SetBrightness(SETUP_BRIGHTNESS - 2);
				break;

			case STR_OS_CONTRAST:
				SetContrast(SETUP_CONTRAST - 2);
				break;

			case STR_OS_HUE:
				SetHUE(SETUP_HUE - 2);
				break;

			case STR_OS_SATURATION:
				SetSaturation(SETUP_SATURATION - 2);
				break;

            #ifdef DIP_CFG_ENABLE
			case STR_OS_DEINTLC:
				SetDeInterlace(SETUP_DE_INTERLACE - 2);
				break;
            #endif//#ifdef DIP_CFG_ENABLE

#ifdef SUPPORT_PROLOGIC_II		// alan, 2003/7/11 03:14¤U¤È
			case STR_OS_PROLOGIC:
            	str_os_prologic2(sub_id);
				break;
#endif
            
            #ifdef SPEAKER_CONFIG//chenzhao20060116Bass Management 
            case STR_OS_FSPK:
                if(sub_id==STR_OS_BASS_MODE_1)speaker_front=SPEAKER_LARGE;
                else if(sub_id==STR_OS_BASS_MODE_2)speaker_front=SPEAKER_SMALL;
                else if(sub_id==STR_OS_OFF)speaker_front=SPEAKER_OFF;
                AUDIF_Set_BassConfig(FRNT_SPK, SETUP_SPK_FRONT-2);
            case STR_OS_CSPK:	
                if(sub_id==STR_OS_BASS_MODE_1)speaker_center=SPEAKER_LARGE;
                else if(sub_id==STR_OS_BASS_MODE_2)speaker_center=SPEAKER_SMALL;
                else if(sub_id==STR_OS_OFF)speaker_center=SPEAKER_OFF;
                AUDIF_Set_BassConfig(CNTR_SPK, SETUP_SPK_CENTER-2);
		    case STR_OS_SSPK:		
                if(sub_id==STR_OS_BASS_MODE_1)speaker_surround=SPEAKER_LARGE;
                else if(sub_id==STR_OS_BASS_MODE_2)speaker_surround=SPEAKER_SMALL;
                else if(sub_id==STR_OS_OFF)speaker_surround=SPEAKER_OFF;
                AUDIF_Set_BassConfig(SRND_SPK, SETUP_SPK_SURROUND-2);
			    break;
		    #endif
		
			default:
				break;
    }

    //special setting
    //printf("sub_id:%x tt_id:%x",sub_id,tt_id);
    switch(sub_id)
    {
	case STR_OS_NTSC:
		tv_format=MODE_NTSC;
		break;
		
#ifdef SUPPORT_PAL60
	case STR_OS_PAL60:
		tv_format=MODE_PAL60;
		break;
#endif//SUPPORT_PAL60

#ifdef SUPPORT_PALM			//gerry,2004-1-8 13:49
	case STR_OS_PALM:
		tv_format=MODE_PALM;
		break;
#endif//SUPPORT_PALM

	case STR_OS_PAL:
		tv_format=MODE_PAL;
		break;

#ifdef SUPPORT_PALN
	case STR_OS_PALN:
		tv_format=MODE_PALN;
		break;
#endif//SUPPORT_PAL60

#ifdef SUPPORT_PALNc
	case STR_OS_PALNc:
		tv_format=MODE_PALNC;
		break;
#endif//SUPPORT_PAL60

	case STR_OS_AUTO:
		if(tt_id==STR_OS_TV_SYS)
		{
			tv_format=MODE_AUTO;
		}
		break;

		// b10~b11 initial display aspect ratio,
		// b8~b9 Current display mode
		// VI4-171
		// 00b: 4:3 ,01b:Not specified ,11b: 16:9
		// 00b: Normal(4:3) or Wide(16:9)
		// 01b: PS 10b:LB
    case STR_OS_16_9:       str_os_16_9();          break;
    case STR_OS_4_3LB:      str_os_4_3lb();         break;
    case STR_OS_4_3PS:      str_os_4_3ps();         break;

    case STR_OS_P_SCAN_YUV: 
         #ifdef EASTWIN  //Jack added 04/09/08   
         if(tt_id==STR_OS_VIDEO)
    	 {
    		tv_dacoff(0);
    	
    	 }
    	 #endif
         
         #ifdef SUPPORT_SPI
         
         tv_out_id = P_SCAN;
         search_ap_tv_out_id();
         
         #ifdef STORE_VIDEO_PARAMETER
         res = WriteToI2c(0xa0, TV_OUT_ID_ADDR,(BYTE *)&tv_out_id,1);
         if(res<0)
         {
           BYTE i=0;
           for(i=0;((i<15)&&(res<0));i++)
           {
             res = WriteToI2c(0xa0, TV_OUT_ID_ADDR, (BYTE *)&tv_out_id, 1);
             printf("tv_out_id store error,retry.......i%d res:%d\n",i,res);
           }
         }
         #endif
         
         if(pdvd_mode == AV_OUTPUT_MODE)
         {
           sp8200tv_setup_custom_output(TV_OUT_YBRRgb);
           //printf("exe in output mode and YPbPr ouput\n");
         }
         else
         {//just record
           //printf("exe in Pdvd mode and setup YPbPr ouput ,just record...\n");
         }
         #else
         	{
         str_os_pscan_yuv();     
		 #ifdef DEACTIVATE_PSCAN
                extern BYTE Pscan_on;
  	          Pscan_on=1;
                #endif
         	}
         #endif
    break;
    case STR_OS_YCbCr:
         #ifdef EASTWIN  //Jack added 04/09/08   
         if(tt_id==STR_OS_VIDEO)
    	 {
    		tv_dacoff(0);
    	
    	 }
    	 #endif
         
         #ifdef SUPPORT_SPI
         tv_out_id = INTERLACE;
         search_ap_tv_out_id();
         #ifdef STORE_VIDEO_PARAMETER
         res = WriteToI2c(0xa0, TV_OUT_ID_ADDR,(BYTE *)&tv_out_id,1);
         if(res<0)
         {
           BYTE i=0;
           for(i=0;((i<15)&&(res<0));i++)
           {
             res = WriteToI2c(0xa0, TV_OUT_ID_ADDR, (BYTE *)&tv_out_id, 1);
             printf("tv_out_id store error,retry.......i%d res:%d\n",i,res);
           }
         }
         #endif
            
           
         if(pdvd_mode == AV_OUTPUT_MODE)
         {
           sp8200tv_setup_custom_output(TV_OUT_YUVRGB);
           //printf("exe in output mode and YCbCr ouput\n");
         }
         else
         {//just record
           //printf("exe in Pdvd mode and setup YCbCr ouput,just record...\n");
         }
         #else
         str_os_ycbcr();         
         #endif
    break;
    case STR_OS_TV_RGB:     str_os_tv_rgb();        break;
    case STR_OS_PC_VGA:     str_os_pc_vga();        break;
    case STR_OS_S_VIDEO:
         #ifdef EASTWIN  //Jack added 04/09/08   
    	if(tt_id==STR_OS_VIDEO)
    	{
    		tv_dacoff(0);   	
    	}
    #endif
#ifdef EASTWIN    
    case STR_OS_OFF:
    	if(tt_id==STR_OS_VIDEO)
    	{
    		tv_dacoff(TV_DAC_D|TV_DAC_E|TV_DAC_F);//jhuang eastwin 2004/8/16
    		//return;
    	}
    break;
#endif
         #ifdef SUPPORT_SPI
         tv_out_id = TV_SVIDEO;
         search_ap_tv_out_id();  
         
         #ifdef STORE_VIDEO_PARAMETER
         res = WriteToI2c(0xa0, TV_OUT_ID_ADDR,(BYTE *)&tv_out_id,1);
         if(res<0)
         {
           BYTE i=0;
           for(i=0;((i<15)&&(res<0));i++)
           {
             res = WriteToI2c(0xa0, TV_OUT_ID_ADDR, (BYTE *)&tv_out_id, 1);
             printf("tv_out_id store error,retry.......i%d res:%d\n",i,res);
           }
         }
         #endif
           
         if(pdvd_mode == AV_OUTPUT_MODE)
         {
           sp8200tv_setup_custom_output(TV_OUT_CScRGB);
           //printf("exe in output mode and SV/CVBS ouput\n");
         }
         else
         {//just record id!!!
           //printf("exe in Pdvd mode and setup SV/CVBS ouput,just record...\n");
         }
         #else
         str_os_svideo();
         #endif         
    break;

#ifdef SETUP_CVBS_OUTPUT
    case STR_OS_CVBS:
        setup_tv_out(CVBS);
		//ap_tv_out_id=TV_SVIDEO;//nono 2003-8-1 18:05
		search_ap_tv_out_id();//terry,2003/8/19 03:21PM

#ifdef SUPPORT_SCART_TV//SPHE8202//nono 4-3-27 21:35
        SET_SCART_GPIO_SFT_CFG_CTRL();
        SET_SCART_TO_CVBS();
#endif//#ifdef SUPPORT_SCART_TV//SPHE8202//nono 4-3-27 21:35

        #if defined(SCART_TV)||defined(KSD_SCART_TV)||defined(SCART_TV_4)||defined(SCART_TV_5)//wangfeng 2003-12-2 23:03
		SET_SCART_RGB(0);
        #endif //#ifdef SCART_TV
		
		#if defined(SCART_TV_2)
		#if defined(THAKRAL_DVD)
		SET_SCART_RGB(1);
		#else
		SET_SCART_RGB(0);
		#endif
		#endif
		
		#if defined(SCART_TV_3)&&defined(DESAY_DVD)
        SET_SCART_RGB(1);
        #elif defined(SCART_TV_3)&&defined(SKYWORTH_DVD)
        SET_SCART_RGB(0);
        #endif
        
        break;
#endif//#ifdef SETUP_CVBS_OUTPUT

#ifdef RATING_8
	case STR_OS_RATING_1:
		UserSet.ParentalLvl=1;
		break;
	case STR_OS_RATING_2:
		UserSet.ParentalLvl=2;
		break;
	case STR_OS_RATING_3:
		UserSet.ParentalLvl=3;
		break;
	case STR_OS_RATING_4:
		UserSet.ParentalLvl=4;
		break;
	case STR_OS_RATING_5:
		UserSet.ParentalLvl=5;
		break;
	case STR_OS_RATING_6:
		UserSet.ParentalLvl=6;
		break;
	case STR_OS_RATING_7:
		UserSet.ParentalLvl=7;
		break;
	case STR_OS_RATING_8:
		UserSet.ParentalLvl=8;
		break;
#ifdef EASTECH_NO_PARENTAL_CONTROL
       case STR_OS_NO_PARENTAL:
              UserSet.ParentalLvl=0xf;
              break;
#endif

#else//#ifdef RATING_8
	case STR_OS_NO_ADULT:
		UserSet.ParentalLvl=6;//THEATRICAL level
		break;
	case STR_OS_KID_ONLY:
		UserSet.ParentalLvl=1;//KID level
		break;
	case STR_OS_VIEW_ALL:
		UserSet.ParentalLvl=8;//adult level
		break;
#endif//#ifdef RATING_8
#ifdef ADJUST_JPEG_SLIDE_TIME  //lyc 2005-3-7 17:33
     BYTE  SlideTimeFlag;
     case STR_OS_15_SEC:                 
                 jpg_slide_time = 1500;
                 SlideTimeFlag=1;
                 UserSet.SETUP_JpegSlideTimeFlag = SlideTimeFlag;
                 //WriteToI2c(0xa0, ADDR_I2C_JPEG_SLIDE_TIME,&SlideTimeFlag,1);
		break;
     case STR_OS_30_SEC:                
                 jpg_slide_time = 3000;
                 SlideTimeFlag=2;
                 UserSet.SETUP_JpegSlideTimeFlag = SlideTimeFlag;
                 //WriteToI2c(0xa0, ADDR_I2C_JPEG_SLIDE_TIME,&SlideTimeFlag,1);  
                 break;
     case STR_OS_45_SEC:                
                 jpg_slide_time = 4500;
                 SlideTimeFlag=3;
                 UserSet.SETUP_JpegSlideTimeFlag = SlideTimeFlag;
                 //WriteToI2c(0xa0, ADDR_I2C_JPEG_SLIDE_TIME,&SlideTimeFlag,1);
                 break;      
#endif
	default:
		break;
    }

    if(exe)
    {
        if((tt_id==STR_OS_OSD)||(tt_id==STR_OS_DOLBY_OP_SETUP))
        {
            setupLevel = 1;
            if (full_scrn & SETUP)
            ShowSetupPage(2);
        }else if(tt_id==STR_OS_TV_SYS)
        {
            setup_tv_format(tv_format);
            update_tv_format_sel();//terry,2004/2/5 12:11PM
            
             #ifndef OP_IR //caoh 05/08/02
             osd_move_subtitle_region(); // 2005/07/12 yltseng
             #endif
			#ifdef SOFT_MENU//Modifed by ChenZhao on 2004-9-25 9:31  
			if(full_scrn&SETUP)
				{
				osd_init_setup();
				ShowSetupPage(REFRESH_SETUP);
				}
			#endif//SOFT_MENU
            #ifdef SUPPORT_SPI
            #ifdef STORE_VIDEO_PARAMETER
            res = WriteToI2c(0xa0, TV_FORMAT_ADDR,(BYTE *)&tv_format,1);
            if(res<0)
            {
              BYTE i=0;
              for(i=0;((i<15)&&(res<0));i++)
              {
                res = WriteToI2c(0xa0, TV_FORMAT_ADDR, (BYTE *)&tv_format, 1);
                printf("tv_format store error,retry.......i%d res:%d\n",i,res);
              }
            }
            //printf("exe record tv_format:%d.....\n",tv_format);
            #endif
            #endif
            //setVPP_TVformat(tv_format);
        }else if(sub_id==STR_OS_RETURN_MAIN_SETUP)
        {
            setup_func_return_main();
        }else if(sub_id==STR_OS_EXIT_MENU)
        {
            ExitSetupPage(1);
        }
    }
}
#endif	//end of DVD_SETUP_REENG


//======================================ending===================================

