// ============================================================================
// Control flow
// ============================================================================
#ifdef SUPPORT_8202_DVB
#include "..\dvb_h\dvb_func.h"
#endif

#ifdef    SUPPORT_OTHER_LANGUAGE_STRING//tianye 200607
extern    const char *const osd_other_str[N_OSD_LANGS][STRINE_NUM];
#endif //end=> #ifdef    SUPPORT_OTHER_LANGUAGE_STRING


void invalid_key(void)
{
    int id;
    int test_ready_ret;
    //we don't show any invalid_key when PROGRAM  is active
    if (full_scrn & PROGRAM) return;
            
	if(play_state==VCD_STATE_IDLE)//zhongshan 20050121
	{
      	test_ready_ret=atapi_p_test_unit_ready();
             if(test_ready_ret != ATAPI_NO_MEDIA)
             {
                	OSD1000ISP_STATUS(OSDISP_ERR_DISC, OSDIR_GLOBAL);

                 	id=STR_OS_ERR_DISC;//nono 2-4-22 13:26 for fuss
             }else{
        OSD1000ISP_STATUS(OSDISP_NODISC, OSDIR_GLOBAL);

        id = STR_OS_NODISC;
             }
        #ifdef SHOW_SPECIAL_DISC_TYPE
        if(read_disc_state == 0x0f)
          id = STR_OS_ERR_DISC;
        #endif
            
	}
	else
	{
        OSD1000ISP_STATUS(OSDISP_INVAL, OSDIR_GLOBAL);

		id = STR_OS_NO;
	}
#if defined( SDRAM_16Mb_Mode ) && !defined( SETUP_PROGRAM_IN_PLACE_UNDER_16M )  // 2004/12/27 yltseng
    if (prog_state==3)
    {
        prog_state=0;

        OSD1000ISP_STATUS(OSDISP_STOP, OSDIR_STOP);

        id = STR_OS_STOP;
    }
#endif

    #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
    if((source_play_mode==USB_PLAY_MODE) || (source_play_mode==CARD_PLAY_MODE))
    { 
        if((id == STR_OS_NODISC) || (id==STR_OS_ERR_DISC))//(usb_card_state==SWITCH_TO_USB_BUT_HAS_NO_USB) || (usb_card_state==SWITCH_TO_CARD_BUT_HAS_NO_CARD))
        {
            if(source_play_mode == USB_PLAY_MODE)
            {
		     #ifdef    SUPPORT_OTHER_LANGUAGE_STRING
				psprintf(RegionValStr[REGION1], osd_other_str[osd_font_mode][USB_NOT_FOUND]); 
		     #else //else => #ifdef    SUPPORT_OTHER_LANGUAGE_STRING	 
                psprintf(RegionValStr[REGION1], "USB NOT FOUND");
		     #endif//end=> #ifdef    SUPPORT_OTHER_LANGUAGE_STRING	

            }			
            else
            {
			#ifdef    SUPPORT_OTHER_LANGUAGE_STRING
			 psprintf(RegionValStr[REGION1], osd_other_str[osd_font_mode][CARD_NOT_FOUND]); 
		    #else //else => #ifdef    SUPPORT_OTHER_LANGUAGE_STRING	 
                psprintf(RegionValStr[REGION1], "CARD NOT FOUND");
		    #endif//end=> #ifdef    SUPPORT_OTHER_LANGUAGE_STRING	
	    
            }
	        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        }
        else
            PrintOsdMsg(id,REGION1,1,0);
    }    
    else
    #endif 
#ifdef SHOW_SPECIAL_DISC_TYPE
    if(read_disc_state == 0x0f)
        PrintOsdMsg(id,REGION1,0,0);
    else
#endif
	PrintOsdMsg(id,REGION1,1,0);
}


void chg2normal_play(UINT8 md,UINT8 realplay)
{	
	if (md&FAST2NORM)
    {
		if(adv_search_time)
		{
            if (adv_search_time<0) {
				//replace temp, Jeff 20020715
				//AudioSetStop();
				if (coding_mode_now==AUDIF_CODING_MODE_PCM) {
					AUDIF_Flush_Buffer();//2004AUDDRV AudioFlushBuffer();
				} else {
					AUDIF_Set_Stop();//2004AUDDRV AudioSetStop();
				}
			} else {
				AUDIF_Flush_Buffer();//2004AUDDRV AudioFlushBuffer();
			}
			
			adv_search_time =0;
			if (cd_type_loaded==CDROM) {
                AUDIF_Set_Continue();//2004AUDDRV AudioSetContinue();
            }
		}
	}
	
    if (md&PAUSE2NORM)
    {
    	if(!Is_JPEG_STATE())           
        if(play_state==VCD_STATE_PAUSE)
        {
            Continue();
        }
    }
	
    if (md&SLOW2NORM) {
		video_slow=0;
		avd_slow_state(video_slow);
    }
	
	if (realplay)
	{
		if(!Is_JPEG_STATE())           
		{//terry,2002/7/18 08:36PM,avoid avd play cmd run many times
			avd_play_state();       
		}
		AUDIF_Set_Continue();//2004AUDDRV AudioSetContinue();
		if(!user_mute)
		{
			AUDIF_Demute();//2004AUDDRV AudioDemute();
            if ( (cd_type_loaded!=CDROM) && mpeg_audio)
			{
				if( (play_state==VCD_STATE_FASTFORWARD)||(play_state==VCD_STATE_FASTBACKWARD) )
				{
					AUDIF_Set_VCDFF2PLAY();//2004AUDDRV AudioSetVCD_FF2PLAY();
				}
				
			}
		}
		#ifdef MUSTEK_MULTI_FUNCTION_DIRECTION_KEY
        if((realplay==REALPLAY) && !((play_state==VCD_STATE_PAUSE) && (pFsJpeg->ControlArea>CNT_AREA_DIR)))
        #else
		if(realplay==REALPLAY)
		#endif
		{
		    extern void SetIDETimeOut(UINT16);      //wanghaoying 2003-8-12 16:44 added

            OSD1000ISP_STATUS(OSDISP_PLAY, OSDIR_GLOBAL);

			PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);
			play_state = VCD_STATE_NORMAL;
			#ifdef SUPPORT_8202_DVB//Jack added 05/11/21
            if(!Is_Dvb_State())
            #endif
				SetIDETimeOut(PLAY_TMOUT);//printf("set srv timeout tm = %d\n",PLAY_TMOUT);//terry,2003/7/17 11:17PM
		}
    }
	
    #ifdef IRCMD_DBG
    printf("play_st:%x search:%x slow:%x\n", play_state, adv_search_time,video_slow);
    #endif
}


/*
** FUNCTION
** pre_slowmotion()
**
*/

UINT8 pre_slowmotion(void)
{
	//printf("================= slow motion ==============\n");
	
	if(audio_only||PE_DSI_novideo())
	{
		invalid_key();
		return 1;
	}
	
	chg2normal_play(FAST2NORM|PAUSE2NORM,TRANSFER);
	
	AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
	AUDIF_Set_Pause();//2004AUDDRV AudioSetPause();
	play_state = VCD_STATE_SLOW;
	return 0;
}

//terry,move to ircmd_video,2003/8/20 09:04PM
//setup_tv_out
//search_ap_tv_out_id
// ============================================================================
// Audio  Audio  Audio  Audio  Audio
// ============================================================================




