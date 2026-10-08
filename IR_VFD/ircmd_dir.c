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
|  File Name   :  ircmd_dir.c
|
|  Description :  realize up,down,left,right function in remoter.
|
|  Version    :  0.1  
| 
| 
|  Rev  Date            Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1  2004/1/30        Terry         Creating
|--------------------------------------------------------------------------------*/

/*
*  Terry,2004/1/30 04:12PM
   Maoyong 2004/09/24 AM, ircmd_full_scrn_up replace call_full_scrn_fun((IRCMDFUNC *)func);
*/
#define is_zoom() ((vpp_zoom > 1) && (vpp_zoom <= ZOOMIN_MAX))

/**************************************************************************
 *  Function Name: ircmd_up                           
 *  Purposes:                                                             
 *      realize up function using up key of IR.
 *  Descriptions:                                                            
 *      ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_UL)
 *      CMD_SELECT:  number or up/down/left/right.
 *      CMD_FUNC_GAME_UL: up key.
 *  Arguments:   NONE                                                         
 *      
 *  Returns:     NONE
 *  See also:    NONE                                                          
 *    
 **************************************************************************/
 //#define DEBUG_OSD_LANGUAGE_OR_OSD_STR
 //#define TEST_OSD_LANGUAGE
 
 #ifdef DEBUG_OSD_LANGUAGE_OR_OSD_STR //wsf only for debug 2006-1-8 19:27
 	static UINT16 offset=0;
 	#ifdef TEST_OSD_LANGUAGE
 		#define TESTLANGUAGE lang_names
 		#define MAX_OFFSET MAX_OSD_LANG_STR_ID
 	#else
 		#define TESTLANGUAGE _OsdMessegeFont1
 		#define MAX_OFFSET MAX_OSD_STR_ID
 	#endif
 #endif  //DEBUG_OSD_LANGUAGE_OR_OSD_STR
 
 
void ircmd_up(void)
{
	#ifdef DEBUG_OSD_LANGUAGE_OR_OSD_STR //wsf only for debug 2006-1-8 19:27
	if(!full_scrn){
		if(offset<MAX_OFFSET)offset++;
		else offset=0;
	
		psprintf(RegionValStr[REGION0], "%d [%s]",offset,_OsdMessegeFont1[osd_font_mode][offset]);
	    PrintOsdMsg(STR_OS_SPACE, REGION0, 0, 1);
		//return;
	}
	#endif

#ifdef IRCMD_DBG
    printf("======================= up =====================\n");
#endif
#ifdef UP_SF_IN_A_KEY
if((play_state == VCD_STATE_SLOW)||((play_state == VCD_STATE_NORMAL)&&(!((cd_type_loaded==CDROM) && (cd_subtype ==CDROM_MP3)))))
    {
          ircmd_slowmotion();
		  return;
       }
#endif
#if defined(MUSTEK_MULTI_FUNCTION_DIRECTION_KEY)&&defined(MP3_ONLY_STOP_TO_GUI)    
    if(full_scrn)
    {
    }
    else if(cd_type_loaded==CDROM)
    {	   
	    /*if((play_state==VCD_STATE_PAUSE)&&Is_JPEG_PLAY_STATE()&&(full_scrn==0))
	    {
		    invalid_key();
		    return;
  	    }*/
 
  	    if((pFsJpeg->ControlArea<=CNT_AREA_DIR) || Is_JPEG_PLAY_STATE())
 		{
			if((Is_MP3_STATE()&&(play_state==VCD_STATE_NORMAL)) || Is_JPEG_PLAY_STATE() || IsOtherStatePlayMode())//Jack added Is_JPEG_PLAY_STATE() 05/04/04
			{
				/*
				if(((play_state==VCD_STATE_MP3_FILELIST)||(play_state==VCD_STATE_PAUSE)) && (pFsJpeg->ControlArea>CNT_AREA_DIR))
				{
				    #ifdef DEBUG_MULTI_FUNCTION_DIRECTION_KEY
				    printf_w("up--->up in pause or stop state\n",);
                    #endif
                    
				    OSD1000ISP_STATUS(OSDISP_DIR_ROTATE, OSDIR_UP);
                    ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_UL);
				}
				else
				{
				*/    
			        #ifdef DEBUG_MULTI_FUNCTION_DIRECTION_KEY
			        printf_w("up--->pause............\n");
                    #endif
                    
			        ircmd_pause();
			        return;
			    //}
		    }
		    /*
		    else if((play_state == VCD_STATE_MP3_FILELIST) || (play_state==VCD_STATE_PAUSE))
		    {
		      	#ifdef DEBUG_MULTI_FUNCTION_DIRECTION_KEY
			    printf_w("up--->pause............\n");
                #endif
                
		      	OSD1000ISP_STATUS(OSDISP_DIR_ROTATE, OSDIR_UP);
                ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_UL);
		    }
			*/
	    }
		else
		{
      		if(Is_JPEG_STATE() && (play_state==VCD_STATE_PAUSE))
      		{
      		    invalid_key();
			    return;
		    }
		    
      		OSD1000ISP_STATUS(OSDISP_DIR_ROTATE, OSDIR_UP);
            ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_UL);
			return;
		}
	}
    else if((!full_scrn) && (!(is_menu()&&(cd_type_loaded==CDDVD))) && cd_type_loaded)
	{
	    if((play_state!=VCD_STATE_OPEN) && (play_state!=VCD_STATE_IDLE) && (play_state!=VCD_STATE_STOP))
	{
	    ircmd_pause();
		return;
	}
	}
#endif //#if defined(MUSTEK_MULTI_FUNCTION_DIRECTION_KEY)&&defnied(MP3_ONLY_STOP_TO_GUI)
	
#ifdef SUPPORT_MIDIDISK_TITLE
        if (bIsPlayMidiTitle)//xlluo for midi title
        {
        invalid_key();
        return;
        }
#endif
#ifdef TEST_VFD
    update_vfd_mod_inc();           //shawn modify at 910131
    return ;
#endif

   

    
    if(full_scrn
	#ifdef GPS_DVD//frank.huang 050801
	&&(full_scrn!=TOUCH_MENU)&&(full_scrn!=TOUCH_KEYBOARD)
	#endif
	)
    {
        //printf("kk\n");
        //call_full_scrn_fun((IRCMDFUNC *)ircmd_up_table);
        ircmd_full_scrn_up();
        return;
    }
    else if( is_zoom() )
#ifdef MOVE_INVERSE_WHEN_ZOOM     
    {   //heqiang, down, 2004-3-2 17:51
        #ifdef JPEG_ZOOM_ROTATE_RESET_PLAY_TIME
		if((cd_type_loaded==CDROM) && Is_JPEG_SlideMode())
          set_rtc_val(0);
		#endif
		
        if(vpp_zoom_y < getVPP_YOffsetMax())
    {
            PrintOsdMsg(STR_OS_PIC_UP, REGION1, 1, 0);
            vpp_zoom_y += ZOOM_MOVE;
            startup_vpp();
            return;
        }
    #if defined(UPDN_AND_KEYUPDN_IN_A_KEY) || defined(LRUPDW_AND_BACKWARD_FORWARD_PREV_NEXT_IN_A_KEY)||defined(UPDN_AND_ECHO_IN_A_KEY) ||defined(UPDN_AND_MICVOL_IN_A_KEY)    //nono 20020706   wu 20020920
        else
        {
            invalid_key();
            return;
        }
    #endif
    }
#else//MOVE_INVERSE_WHEN_ZOOM    
    {         
        #ifdef JPEG_ZOOM_ROTATE_RESET_PLAY_TIME
		if((cd_type_loaded==CDROM) && Is_JPEG_SlideMode())
          set_rtc_val(0);
		#endif
		
        if (vpp_zoom_y > -getVPP_YOffsetMax())
        {
            OSD1000ISP_STATUS(OSDISP_DIR_ZOOM, OSDIR_UP);

            PrintOsdMsg(STR_OS_PIC_UP, REGION1, 1, 0);
            vpp_zoom_y -= ZOOM_MOVE;
            startup_vpp();
            #ifdef ZOOM_ROTATE_RESET_SLIDE_TIME//lijd 2005-6-6 10:02
            if(Is_JPEG_SlideMode())
                set_rtc_val(0);      
            #endif 
            return;
        }
        #if defined(UPDN_AND_KEYUPDN_IN_A_KEY) || defined(LRUPDW_AND_BACKWARD_FORWARD_PREV_NEXT_IN_A_KEY)||defined(UPDN_AND_ECHO_IN_A_KEY) ||defined(UPDN_AND_MICVOL_IN_A_KEY)    //nono 20020706   wu 20020920
        else
        {
            invalid_key();
            return;
        }
#endif
    }
#endif//MOVE_INVERSE_WHEN_ZOOM
    else if (HL_exist)
    {
        ExeHLBm(HL_DIR, HL_BM_U);
        return;
    }
#ifdef MIC_FUNCTION_KEY    
    #ifdef BBK_DVD//zhaoyanhua add 03-10-19 14:02
    else if (bFuncStep)
    {
        switch (bFuncStep)
        {
            case 1:
                ircmd_mic_up();
                break;
            case 2:
                ircmd_echo_up();
                break;  
            case 3:
                ircmd_key_up();     
                break;;
        }
        return;
    }
    #endif//end BBK_DVd
#endif//end MIC_FUNCTION_KEY
 #ifdef SUPPORT_MULTI_PARTITION//liweihua mod 2004-11-2
   else if((pFsJpeg->gifsState == FS_STATE_HDD)
    #ifdef FAT_FILE_MODE
        ||(pFsJpeg->gifsState == FS_STATE_MODE)
        ||(fat_play_mode == 1)
        #endif
        )
    {
        //printf("haha\n");
        if(pFsJpeg->gifsState == FS_STATE_JPEG)     /////YANGLI MOD FOR JPEG ROTATE 2005-7-15
        {
			ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_UL);
        	return;
        }
         if(pFsJpeg->gifsState == FS_STATE_OTHER) ////////yangli mod for up fuction 2005/9/14
       {
       	 invalid_key();
            return;       	
       }
        #if defined(PMP_DVD)&& defined(PMP_DVD_ONE_DIR_SELECT) //kenny add 2005/6/16
         pmp_disable_user_flag(PMP_USER_PRESS_NEXT_PREV_KEY);
         pmp_enable_user_flag(PMP_USER_PRESS_UP_DOWN__KEY);
        #endif
        HDDCard_up();
        return;
    }
    #endif//#ifdef SUPPORT_MULTI_PARTITION//liweihua mod 2004-11-2
    else if (cd_type_loaded == CDROM)
    {
        #ifdef JPEG_ZOOM_ROTATE_RESET_PLAY_TIME
        if(Is_JPEG_SlideMode())
        {
          #ifdef ONLY_USE_ANGLE_TO_ROTATE 
          invalid_key();
          return;
          #else  
          set_rtc_val(0);
          #endif
        }  
        #endif
          
        if ((play_state == VCD_STATE_MP3_FILELIST) || (play_state == VCD_STATE_NORMAL) || adv_search_time)
        {
            if ( (shuffle_flag == 0||Is_JPEG_SlideMode()==1)
            && ((prog_cnt == 0)||Is_JPEG_SlideMode()==1)
            )//NONO 3-12-22 23:22
            {
#if defined(ZOOM_DIRECT_STOP_SLIDE)||defined(ROTATE_DIRECT_STOP_SLIDE)  //wanghaoying 2003-08-25 20:35
                if( Is_JPEG_SlideMode() )              //wangap add 2005-5-8 10:23
                    jpg_slide_time = 0xffffffff;
#endif                

#ifdef ZOOMOUT_NOT_ROTATE //zhaoyanhua add for DESAY 03-10-11 14:54 when zoom ratio less than 1,not rotate.    
                if ((vpp_zoom >= ZOOMOUT_BASE) && (vpp_zoom <= ZOOMOUT_MAX))
                    invalid_key();
                else
#endif
                {
                #ifdef OP_IR //libing 2005-5-27 21:14
                if(Is_JPEG_PLAY_STATE())
                {
                    invalid_key();
                    return;
                }
                #endif  
                    OSD1000ISP_STATUS(OSDISP_DIR_ROTATE, OSDIR_UP);

                    ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_UL);
                    return;
                }
            }
        }
        
		#if defined(ROTATE_WHEN_PAUSE)&&!defined(JPEG_USE_ANGLE_KEY)       //zhaoyanhua add 03-10-13 10:09
        else if ((play_state == VCD_STATE_PAUSE) && (Is_JPEG_SlideMode()))
        {
            ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_UL);
            return;
        }
        #endif 

        #if defined(UPDN_AND_KEYUPDN_IN_A_KEY) || defined(LRUPDW_AND_BACKWARD_FORWARD_PREV_NEXT_IN_A_KEY)||defined(UPDN_AND_ECHO_IN_A_KEY)||defined(UPDN_AND_MICVOL_IN_A_KEY)     //nono 20020706   wu 20020920
        else
        {
            invalid_key();
            return;
        }
#endif
    }
	#ifdef USE_FSGUI_TO_PLAY_CD//frank.huang 051014
	if(cd_type_loaded == CDDA)
	{
    	OSD1000ISP_STATUS(OSDISP_DIR_ROTATE, OSDIR_UP);
    	ircmd_callback_check=FSGUI_CmdUp;
		ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_UL);
		return;
	}
    #endif

#ifdef MINUS_VR_AUTH_PLAYBACK
	if(bDVDminusVR&& (play_state == VCD_STATE_MP3_FILELIST))
	{
		ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_UL);
	   	return;
	}
#endif

#ifdef UPDN_AND_KEYUPDN_IN_A_KEY  //nono 20020706
    ircmd_key_up();
#elif defined(LRUPDW_AND_BACKWARD_FORWARD_PREV_NEXT_IN_A_KEY)   //wu 20020920
    ircmd_prev();
#elif defined(FUSS_FEIYANG_2120_PANEL)   //wu 20020923
    ircmd_forward();
#elif defined(UPDN_AND_MICVOL_IN_A_KEY)
    ircmd_mic_up();
#elif defined(UPDN_AND_ECHO_IN_A_KEY)  //nono 20020706
    ircmd_echo_up();
#elif defined(CF_GPIO_CONTROL_COLOR)
    chang_vfd_back_color_down();
#else
    invalid_key();
#endif
}
/**************************************************************************
 *  Function Name: ircmd_down                           
 *  Purposes:                                                             
 *      realize down function using down key of IR.
 *  Descriptions:                                                            
 *      ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_DN)
 *      CMD_SELECT:  number or up/down/left/right.
 *      CMD_FUNC_GAME_DN: down key.
 *  Arguments:   NONE                                                          
 *      
 *  Returns:     NONE
 *  See also:    NONE                                                          
 *    
 **************************************************************************/

void ircmd_down(void)
{
	#ifdef DEBUG_OSD_LANGUAGE_OR_OSD_STR //wsf only for debug 2006-1-8 19:27
	if(!full_scrn){
		if(offset)offset--;
		else offset=MAX_OSD_LANG_STR_ID;
	
		psprintf(RegionValStr[REGION0], "%d [%s]",offset,TESTLANGUAGE[osd_font_mode][offset]);
    	PrintOsdMsg(STR_OS_SPACE, REGION0, 0, 1);
		//return;
	}
	#endif
	
#ifdef IRCMD_DBG
    printf("======================= ircmd_down ================\n");
#endif

#if defined(MUSTEK_MULTI_FUNCTION_DIRECTION_KEY)&&defined(MP3_ONLY_STOP_TO_GUI)
    if(full_scrn)
	{
	}
    else if(cd_type_loaded==CDROM)
	{		
		/*if((play_state==VCD_STATE_PAUSE)&&Is_JPEG_PLAY_STATE()&&(full_scrn==0))
		{
			invalid_key();
			return;
        }*/
  	    if((pFsJpeg->ControlArea<=CNT_AREA_DIR) || Is_JPEG_PLAY_STATE())
		{
			if (Is_MP3_STATE()) 
			{
	 			#ifdef MP3_STOP_IN_GUI_AND_NEED_RESUME_MSF
	 			if((play_state!=VCD_STATE_MP3_FILELIST) || (resumeMSF))
	 			#else
	 			if(play_state!=VCD_STATE_MP3_FILELIST)
	 			#endif
				{
	 			    //resumeMSF = 0;
				    //disp_time = 0;
				    ircmd_stop();
				    return;
				}    
				
			}
			else if(play_state==VCD_STATE_MP3_FILELIST)
			{
				OSD1000ISP_STATUS(OSDISP_DIR_ROTATE, OSDIR_DOWN);
				ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_DN);
			    return;
			}
			#ifdef JPEG_THUMBNAIL_MENU
			else if((pFsJpeg->g_nJpegMode==JPEG_THUMBNAIL_MODE)&&!Is_JPEG_SlideMode())
			{
			}
			#endif
	        else
            {
                ircmd_stop();
				return;
			}
	    }
		else
		{
			if(Is_JPEG_STATE() && (play_state==VCD_STATE_PAUSE))
      		{
      		    invalid_key();
                return;
            }
            
            OSD1000ISP_STATUS(OSDISP_DIR_ROTATE, OSDIR_DOWN);
			ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_DN);
			return;				
		}
	}
	else if((!full_scrn) && (!(is_menu()&&(cd_type_loaded==CDDVD))) && cd_type_loaded)
	{
	    if((play_state!=VCD_STATE_OPEN) && (play_state!=VCD_STATE_IDLE))
	{
	        if(!((play_state==VCD_STATE_STOP)&&!resumeMSF))
	        {
	    ircmd_stop();
		return;
	}
	}
	}
#endif //#if defined(MUSTEK_MULTI_FUNCTION_DIRECTION_KEY)&&defnied(MP3_ONLY_STOP_TO_GUI)
	
#ifdef SUPPORT_MIDIDISK_TITLE
        if (bIsPlayMidiTitle)//xlluo for midi title
        {
        invalid_key();
        return;
        }
#endif
#ifdef TEST_VFD
    update_vfd_mod_dec();           //shawn modify at 910131
    return;
#endif

   
    
    
    if (full_scrn
	#ifdef GPS_DVD//frank.huang 050801
	&&(full_scrn!=TOUCH_MENU)&&(full_scrn!=TOUCH_KEYBOARD)
	#endif
	)
    {
        //call_full_scrn_fun((IRCMDFUNC *)ircmd_down_table);
        ircmd_full_scrn_down();
        return;
    }
    else if( is_zoom() )
#ifdef MOVE_INVERSE_WHEN_ZOOM  
   {    //heqiang, up, 2004-3-2 17:51
        #ifdef JPEG_ZOOM_ROTATE_RESET_PLAY_TIME
		if((cd_type_loaded==CDROM) && Is_JPEG_SlideMode())
          set_rtc_val(0);
		#endif
		
        if (vpp_zoom_y > -getVPP_YOffsetMax())
        {
            PrintOsdMsg(STR_OS_PIC_DN, REGION1, 1, 0);
            vpp_zoom_y -= ZOOM_MOVE;
            startup_vpp();
            return;
        }
    #if defined(UPDN_AND_KEYUPDN_IN_A_KEY) || defined(LRUPDW_AND_BACKWARD_FORWARD_PREV_NEXT_IN_A_KEY)||defined(UPDN_AND_ECHO_IN_A_KEY) ||defined(UPDN_AND_MICVOL_IN_A_KEY)    //nono 20020706   wu 20020920
        else
        {
            invalid_key();
            return;
        }
    #endif
    }
#else//MOVE_INVERSE_WHEN_ZOOM       
    {
        #ifdef JPEG_ZOOM_ROTATE_RESET_PLAY_TIME
		if((cd_type_loaded==CDROM) && Is_JPEG_SlideMode())
          set_rtc_val(0);
		#endif
        if(vpp_zoom_y < getVPP_YOffsetMax())
        {
            OSD1000ISP_STATUS(OSDISP_DIR_ZOOM, OSDIR_DOWN);

            PrintOsdMsg(STR_OS_PIC_DN, REGION1, 1, 0);
            vpp_zoom_y += ZOOM_MOVE;
            startup_vpp();
            #ifdef ZOOM_ROTATE_RESET_SLIDE_TIME//lijd 2005-6-6 10:02
            if(Is_JPEG_SlideMode())
                set_rtc_val(0);           
            #endif 
            return;
        }
        #if defined(UPDN_AND_KEYUPDN_IN_A_KEY) || defined(LRUPDW_AND_BACKWARD_FORWARD_PREV_NEXT_IN_A_KEY)||defined(UPDN_AND_ECHO_IN_A_KEY)||defined(UPDN_AND_MICVOL_IN_A_KEY)     //nono 20020706   wu 20020920
        else
        {
            invalid_key();
            return;
        }
#endif
    }
#endif//MOVE_INVERSE_WHEN_ZOOM    
    else if(HL_exist)
    {
        ExeHLBm(HL_DIR, HL_BM_D);
        return;
    }
#ifdef MIC_FUNCTION_KEY
    #ifdef BBK_DVD//zhaoyanhua add 03-10-19 14:02
    else if (bFuncStep)
    {
        switch (bFuncStep)
        {
            case 1:
                ircmd_mic_down();
                break;
            case 2:
                ircmd_echo_down();
                break;  
            case 3:
                ircmd_key_down();
                break;      
        }
        return;
    }
    
    #endif//end ifdef BBK_DVD
#endif//MIC_FUNCTION_KEY
#ifdef SUPPORT_MULTI_PARTITION//liweihua mod 2004-11-2
   else if((pFsJpeg->gifsState == FS_STATE_HDD)
    #ifdef FAT_FILE_MODE
        ||(pFsJpeg->gifsState == FS_STATE_MODE)
        ||(fat_play_mode == 1)
        #endif
        )
    {
        if(pFsJpeg->gifsState == FS_STATE_JPEG)               /////YANGLI MOD FOR JPEG ROTATE 2005-7-15
       {
         ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_DN);
        return;
       }
        if(pFsJpeg->gifsState == FS_STATE_OTHER)  ////////yangli mod for down fuction 2005/9/14
       {
       	 invalid_key();
            return;       	
       }
        #if defined(PMP_DVD)&& defined(PMP_DVD_ONE_DIR_SELECT) ////kenny add 2005/6/16
         pmp_disable_user_flag(PMP_USER_PRESS_NEXT_PREV_KEY);
         pmp_enable_user_flag(PMP_USER_PRESS_UP_DOWN__KEY);
        #endif
        HDDCard_down();
        return;
    }
    #endif//#ifdef SUPPORT_MULTI_PARTITION//liweihua mod 2004-11-2
    else if(cd_type_loaded == CDROM)
    {
        #ifdef JPEG_ZOOM_ROTATE_RESET_PLAY_TIME
        if(Is_JPEG_SlideMode())
        {
          #ifdef ONLY_USE_ANGLE_TO_ROTATE 
          invalid_key();
          return;
          #else
          set_rtc_val(0);  
          #endif
        }  
        #endif
        
        if ( (play_state == VCD_STATE_MP3_FILELIST) || (play_state == VCD_STATE_NORMAL) ||adv_search_time)
        {
            if ((shuffle_flag && Is_JPEG_SlideMode()!=1) //nono 2004-7-28 1:51
            || (prog_cnt&&Is_JPEG_SlideMode()!=1)
            )//nono 3-12-22 23:22
            {
                invalid_key();
            }
            else
            {
#if defined(ZOOM_DIRECT_STOP_SLIDE)||defined(ROTATE_DIRECT_STOP_SLIDE)  //wanghaoying 2003-08-25 20:35
                if( Is_JPEG_SlideMode() )                //wangap add 2005-5-8 10:23
                    jpg_slide_time = 0xffffffff;
#endif                


                #ifdef ZOOMOUT_NOT_ROTATE //zhaoyanhua add for DESAY 03-10-11 14:54 when zoom ratio less than 1,not rotate.    
                if ((vpp_zoom >= ZOOMOUT_BASE) && (vpp_zoom <= ZOOMOUT_MAX))
                    invalid_key();
                else
                #endif

                {
                #ifdef OP_IR//libing     
                if(Is_JPEG_PLAY_STATE())
                {
                    invalid_key();
                    return;
                }
                #endif  
                OSD1000ISP_STATUS(OSDISP_DIR_ROTATE, OSDIR_DOWN);

                ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_DN);
                }
            }
            return;
        }

        #if defined(ROTATE_WHEN_PAUSE)&&!defined(JPEG_USE_ANGLE_KEY)       //zhaoyanhua add 03-10-13 10:09
        else if ((play_state == VCD_STATE_PAUSE) && (Is_JPEG_SlideMode()))
        {
            ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_DN);
            return;
        }
        #endif 

        #if defined(UPDN_AND_KEYUPDN_IN_A_KEY) || defined(LRUPDW_AND_BACKWARD_FORWARD_PREV_NEXT_IN_A_KEY)||defined(UPDN_AND_ECHO_IN_A_KEY) ||defined(UPDN_AND_MICVOL_IN_A_KEY)   //nono 20020706   wu 20020920
        else
        {
            invalid_key();
            return;
        }
#endif
    }
#ifdef MINUS_VR_AUTH_PLAYBACK
	if(bDVDminusVR&& (play_state == VCD_STATE_MP3_FILELIST))
	{
		ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_DN);
	   	return;
	}
#endif

#ifdef UPDN_AND_KEYUPDN_IN_A_KEY  //nono 20020706
    ircmd_key_down();
#elif defined(LRUPDW_AND_BACKWARD_FORWARD_PREV_NEXT_IN_A_KEY)   //wu 20020920
    ircmd_next();
#elif defined(FUSS_FEIYANG_2120_PANEL)   //wu 20020923
    ircmd_backward();
    #elif defined(UPDN_AND_MICVOL_IN_A_KEY)
   ircmd_mic_down();
#elif defined(UPDN_AND_ECHO_IN_A_KEY)  //nono 20020706
    ircmd_echo_down();
#elif defined(CF_GPIO_CONTROL_COLOR)
   chang_vfd_back_color_up();
    
#else
#ifdef USE_FSGUI_TO_PLAY_CD//frank.huang add 051014
	if(cd_type_loaded == CDDA)
	{
    	OSD1000ISP_STATUS(OSDISP_DIR_ROTATE, OSDIR_DOWN);
    	ircmd_callback_check=FSGUI_CmdDown;
		ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_DN);
    	return;
	}
#endif
    invalid_key();
    return;
//#else
//  LoadModual(MODUAL_CDROM);
//  Change_User_Logo();
//#endif
#endif

}
/**************************************************************************
 *  Function Name: ircmd_left                           
 *  Purposes:                                                             
 *      realize left function using left key of IR.
 *  Descriptions:                                                            
 *      ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_L)
 *      CMD_SELECT:  number or up/down/left/right.
 *      CMD_FUNC_GAME_L: left key.
 *  Arguments:   NONE                                                          
 *      
 *  Returns:     NONE
 *  See also:    NONE                                                          
 *    
 **************************************************************************/
void ircmd_left(void)
{
	#ifdef DEBUG_OSD_LANGUAGE_OR_OSD_STR //wsf only for debug 2006-1-8 19:27
	if(!full_scrn){
		if(offset>10)offset-=10;
		else offset=MAX_OSD_LANG_STR_ID;
	
		psprintf(RegionValStr[REGION0], "%d [%s]",offset,TESTLANGUAGE[osd_font_mode][offset]);
    	PrintOsdMsg(STR_OS_SPACE, REGION0, 0, 1);
       	//return;
    }
    #endif
	
#ifdef IRCMD_DBG
    printf("====================== ircmd_left ==================\n");
#endif

#ifdef MUSTEK_MULTI_FUNCTION_DIRECTION_KEY
    if(full_scrn)
	{
	   
	}
	else if((is_menu()==0) && (/*GetCurrentFileType()>=CDROM_WMA*/cd_type_loaded) && (play_state!=VCD_STATE_MP3_FILELIST) && (!Is_JPEG_STATE()))
	{
		if((play_state!=VCD_STATE_PAUSE) && (play_state!=VCD_STATE_STOP))
		{
		    ircmd_backward();
		    return;
		}
		else if(Is_MP3_STATE())
		{
		    ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_L);
		    return;
		}
	}
#endif
	
   
#ifdef SUPPORT_MIDIDISK_TITLE
        if (bIsPlayMidiTitle)//xlluo for midi title
        {
        invalid_key();
        return;
        }
#endif
#ifdef TEST_VFD         //shawn add at 910131
    update_vfd_dot_dec();
    return ;
#endif

    #ifdef BRIGHTNESS_COLOR_KEY // Kevin Sep 21,04 
    if(BriCol_timer)
    {   
        BriCol_value_down();
        return;
    } 
    #endif
    
    if(full_scrn
	#ifdef GPS_DVD//frank.huang 050801
	&&(full_scrn!=TOUCH_MENU)&&(full_scrn!=TOUCH_KEYBOARD)
	#endif
	)
    {
        //call_full_scrn_fun((IRCMDFUNC *)ircmd_left_table);
        ircmd_full_scrn_left();
        return;
    }
    else if( is_zoom() )
#ifdef MOVE_INVERSE_WHEN_ZOOM  
    {   //heqiang, right, 2004-3-2 17:51
        #ifdef JPEG_ZOOM_ROTATE_RESET_PLAY_TIME
		if((cd_type_loaded==CDROM) && Is_JPEG_SlideMode())
          set_rtc_val(0);
		#endif
        if(vpp_zoom_x < getVPP_XOffsetMax())
        {
            OSD1000ISP_STATUS(OSDISP_DIR_ZOOM, OSDIR_LEFT);

            PrintOsdMsg(STR_OS_PIC_L, REGION1, 1, 0);
            vpp_zoom_x += ZOOM_MOVE;
            startup_vpp();
            return;
        }
    #if defined(LR_AND_ECHOUPDN_IN_A_KEY)|| defined(LRUPDW_AND_BACKWARD_FORWARD_PREV_NEXT_IN_A_KEY) ||defined(LR_AND_KEYUPDN_IN_A_KEY)  //nono 20020706   wu 20020920
        else
    {
            invalid_key();
            return;
        }
    #endif
    }
#else//MOVE_INVERSE_WHEN_ZOOM 
    {   //heqiang, left, 2004-3-2 17:51
        #ifdef JPEG_ZOOM_ROTATE_RESET_PLAY_TIME
		if((cd_type_loaded==CDROM) && Is_JPEG_SlideMode())
          set_rtc_val(0);
		#endif
        if((vpp_zoom_x > -getVPP_XOffsetMax())&&(getVPP_XOffsetMax() >=16 ))
        {
            OSD1000ISP_STATUS(OSDISP_DIR_ZOOM, OSDIR_LEFT);

            PrintOsdMsg(STR_OS_PIC_L, REGION1, 1, 0);
            vpp_zoom_x -= ZOOM_MOVE;
            startup_vpp();
            #ifdef ZOOM_ROTATE_RESET_SLIDE_TIME//lijd 2005-6-6 10:02
            if(Is_JPEG_SlideMode())
                set_rtc_val(0);           
            #endif 
            return;
        }
#if defined(LR_AND_ECHOUPDN_IN_A_KEY) || defined(LRUPDW_AND_BACKWARD_FORWARD_PREV_NEXT_IN_A_KEY) ||defined(LR_AND_KEYUPDN_IN_A_KEY)  //nono 20020706   wu 20020920
        else
        {
            invalid_key();
            return;
        }
#endif
    }
#endif//MOVE_INVERSE_WHEN_ZOOM    
    else if(HL_exist)
    {
        ExeHLBm(HL_DIR, HL_BM_L);
        return;
    }
#ifdef FAT_FILE_MODE//liweihua 2004-11-2 21:47
    else if(fat_play_mode == 1)
        {
        if(pFsJpeg->gifsState == FS_STATE_JPEG)            /////YANGLI MOD FOR JPEG ROTATE 2005-7-15
        ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_L);
        else
        HDDCard_left();
            return;
        }
#endif//#ifdef FAT_FILE_MODE//liweihua 2004-11-2 21:47
    else if(cd_type_loaded == CDROM)
    {
        
        #ifdef JPEG_ZOOM_ROTATE_RESET_PLAY_TIME
        if(Is_JPEG_SlideMode())
        {
          #ifdef ONLY_USE_ANGLE_TO_ROTATE 
          invalid_key();
          return;
          #else
          set_rtc_val(0);
          #endif
        }
        #endif//#ifdef JPEG_ZOOM_ROTATE_RESET_PLAY_TIME
        
        if ((play_state == VCD_STATE_MP3_FILELIST) || (play_state == VCD_STATE_NORMAL) || adv_search_time)
        {
            if ((shuffle_flag && Is_JPEG_SlideMode()!=1)//nono 2004-7-28 1:51
            || (prog_cnt&&Is_JPEG_SlideMode()!=1 ) 
            )//nono 3-12-22 23:23
            {
                invalid_key();
            }
            else
            {
#if defined(ZOOM_DIRECT_STOP_SLIDE)||defined(ROTATE_DIRECT_STOP_SLIDE)  //wanghaoying 2003-08-25 20:35
                if( Is_JPEG_SlideMode() ) 
                    jpg_slide_time = 0xffffffff;
#endif                
                //when zoom ratio less than 1,not rotate. zhaoyanhua add  03-10-11 14:54    
                #ifdef ZOOMOUT_NOT_ROTATE 
                if ((vpp_zoom >= ZOOMOUT_BASE) && (vpp_zoom <= ZOOMOUT_MAX))
                    invalid_key();
                else
                #endif
#ifdef HANYANG_LR_CHANGE_PAGE  //Maoyong 2004.07.02
                if( IsValidAreaChangePage(0) )
                    FSGUI_ChangFileDirPage(0);
                else
                #endif

                {
                #ifdef OP_IR//libing 
                if(Is_JPEG_PLAY_STATE())
                {
                    invalid_key();
                    return;
                }
                #endif  
                OSD1000ISP_STATUS(OSDISP_DIR_ROTATE, OSDIR_LEFT);

                ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_L);
                }
            }
            return;
        }

        #if defined(ROTATE_WHEN_PAUSE)&&!defined(JPEG_USE_ANGLE_KEY)       //zhaoyanhua add 03-10-13 10:09
        else if ((play_state == VCD_STATE_PAUSE) && (Is_JPEG_SlideMode()))
        {
            ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_L);
            return;
        }
        #endif           

#if defined(LR_AND_ECHOUPDN_IN_A_KEY) || defined(LRUPDW_AND_BACKWARD_FORWARD_PREV_NEXT_IN_A_KEY) ||defined(LR_AND_KEYUPDN_IN_A_KEY)  //nono 20020706   wu 20020920
        else
        {
            invalid_key();
            return;
        }
#endif
    }
#ifdef MINUS_VR_AUTH_PLAYBACK
	if(bDVDminusVR&& (play_state == VCD_STATE_MP3_FILELIST))
	{
		ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_L);
	   	return;
	}
#endif

#ifdef LR_AND_ECHOUPDN_IN_A_KEY  //nono 20020706
    ircmd_echo_down();
#elif defined(LRUPDW_AND_BACKWARD_FORWARD_PREV_NEXT_IN_A_KEY)    //wu 20020920
    ircmd_backward();
#elif defined(FUSS_FEIYANG_2120_PANEL)   //wu 20020923
    ircmd_prev();
#elif defined(LR_AND_KEYUPDN_IN_A_KEY)  //nono 20020706
    ircmd_key_down();
#elif defined(CF_GPIO_CONTROL_COLOR)
  chang_vfd_back_color_down();
//#elif defined(BRIGHTNESS_COLOR_KEY)   // Kevin Sep 21,04 
   //BriCol_value_down();               // Kevin Sep 21,04 
#else
    invalid_key();
#endif
}
/**************************************************************************
 *  Function Name: ircmd_right                           
 *  Purposes:                                                             
 *      realize up function using right key of IR.
 *  Descriptions:                                                            
 *      ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_R)
 *      CMD_SELECT:  number or up/down/left/right.
 *      CMD_FUNC_GAME_R: right key.
 *  Arguments:   NONE                                                         
 *     
 *  Returns:     NONE
 *  See also:    NONE                                                          
 *    
 **************************************************************************/
void ircmd_right(void)
{
	#ifdef DEBUG_OSD_LANGUAGE_OR_OSD_STR //wsf only for debug 2006-1-8 19:27
	if(!full_scrn){
		if(offset<(MAX_OFFSET-10))offset+=10;
		else offset=0;
	
		psprintf(RegionValStr[REGION0], "%d [%s]",offset,TESTLANGUAGE[osd_font_mode][offset]);
    	PrintOsdMsg(STR_OS_SPACE, REGION0, 0, 1);
		//return;
	}
	#endif
	
#ifdef IRCMD_DBG
    printf("====================== ircmd_right ====================\n");
#endif

#ifdef MUSTEK_MULTI_FUNCTION_DIRECTION_KEY
    if(full_scrn)
	{
	   
	}
	else if((is_menu()==0) && (/*GetCurrentFileType()>=CDROM_WMA*/cd_type_loaded) && (play_state!=VCD_STATE_MP3_FILELIST) && (!Is_JPEG_STATE()))
	{
		if((play_state!=VCD_STATE_PAUSE) && (play_state!=VCD_STATE_STOP))
		{
		    ircmd_forward();
		    return;
		}
		else if(Is_MP3_STATE())
		{
		    ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_R);
		    return;
		}    
	}
#endif
    

#ifdef SUPPORT_MIDIDISK_TITLE
        if (bIsPlayMidiTitle)//xlluo for midi title
        {
        invalid_key();
        return;
        }
#endif
#ifdef TEST_VFD         //shawn add at 910131
    update_vfd_dot_inc();
    return;
#endif

    //printf("ircmd_right:full_scrn=%x\n", full_scrn);

    #ifdef BRIGHTNESS_COLOR_KEY // Kevin Sep 21,04 
    if(BriCol_timer)
    {   
        BriCol_value_up();
        return;
    } 
    #endif
    
    if(full_scrn

	#ifdef GPS_DVD//frank.huang 050801
	&&(full_scrn!=TOUCH_MENU)&&(full_scrn!=TOUCH_KEYBOARD)
	#endif

	)
    {
        //call_full_scrn_fun((IRCMDFUNC *)ircmd_right_table);
        ircmd_full_scrn_right();
        return;
    }
    else if( is_zoom() )
#ifdef MOVE_INVERSE_WHEN_ZOOM     
    {   //heqiang, left, 2004-3-2 17:51
        #ifdef JPEG_ZOOM_ROTATE_RESET_PLAY_TIME
		if((cd_type_loaded==CDROM) && Is_JPEG_SlideMode())
          set_rtc_val(0);
		#endif
        if (vpp_zoom_x > -getVPP_XOffsetMax())
        {
            OSD1000ISP_STATUS(OSDISP_DIR_ZOOM, OSDIR_RIGHT);

            PrintOsdMsg(STR_OS_PIC_R, REGION1, 1, 0);
            vpp_zoom_x -= ZOOM_MOVE;
            startup_vpp();
            return;
        }
    #if defined(LR_AND_ECHOUPDN_IN_A_KEY) || defined(LRUPDW_AND_BACKWARD_FORWARD_PREV_NEXT_IN_A_KEY) ||defined(LR_AND_KEYUPDN_IN_A_KEY)  //nono 20020706   wu 20020920
        else
        {
            invalid_key();
            return;
        }
    #endif
    } 
#else//MOVE_INVERSE_WHEN_ZOOM     
    {
        #ifdef JPEG_ZOOM_ROTATE_RESET_PLAY_TIME
		if((cd_type_loaded==CDROM) && Is_JPEG_SlideMode())
            set_rtc_val(0);
		#endif

        if((vpp_zoom_x < getVPP_XOffsetMax())&&(getVPP_XOffsetMax() >=16 ))
        {
            OSD1000ISP_STATUS(OSDISP_DIR_ZOOM, OSDIR_RIGHT);

            PrintOsdMsg(STR_OS_PIC_R, REGION1, 1, 0);
            vpp_zoom_x += ZOOM_MOVE;
            startup_vpp();
            #ifdef ZOOM_ROTATE_RESET_SLIDE_TIME//lijd 2005-6-6 10:02
            if(Is_JPEG_SlideMode())
                set_rtc_val(0);          
            #endif 
            return;
        }
#if defined(LR_AND_ECHOUPDN_IN_A_KEY)|| defined(LRUPDW_AND_BACKWARD_FORWARD_PREV_NEXT_IN_A_KEY) ||defined(LR_AND_KEYUPDN_IN_A_KEY)  //nono 20020706   wu 20020920
        else
        {
            invalid_key();
            return;
        }
#endif
    }
#endif//MOVE_INVERSE_WHEN_ZOOM        
    else if(HL_exist)
    {
        ExeHLBm(HL_DIR, HL_BM_R);
        return;
    }
#ifdef FAT_FILE_MODE//liweihua mod 2004-11-2 21:47
    else if(fat_play_mode == 1)
    {
       if(pFsJpeg->gifsState == FS_STATE_JPEG)        /////YANGLI MOD FOR JPEG ROTATE 2005-7-15
       ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_R);
       else
        HDDCard_right();
            return;
        }
#endif//#ifdef FAT_FILE_MODE//liweihua 2004-11-2 21:47
    else if(cd_type_loaded == CDROM)
    {
        #ifdef JPEG_ZOOM_ROTATE_RESET_PLAY_TIME
        if(Is_JPEG_SlideMode())
        {
          #ifdef ONLY_USE_ANGLE_TO_ROTATE 
          invalid_key();
          return;
          #else
          set_rtc_val(0);
          #endif
        }
        #endif
        
        if ((play_state == VCD_STATE_MP3_FILELIST) || (play_state == VCD_STATE_NORMAL) || adv_search_time)
        {
            if ( (shuffle_flag &&(Is_JPEG_SlideMode()!=1) )//NONO 2004-7-28 1:51
            || (prog_cnt&&Is_JPEG_SlideMode()!=1 ) 
            )//nono 3-12-22 23:23
            {
                invalid_key();
            }
            else
            {
#if defined(ZOOM_DIRECT_STOP_SLIDE)||defined(ROTATE_DIRECT_STOP_SLIDE)  //wanghaoying 2003-08-25 20:35
                if( Is_JPEG_SlideMode() ) 
                    jpg_slide_time = 0xffffffff;
#endif                

                //when zoom ratio less than 1,not rotate. zhaoyanhua add  03-10-11 14:54  
                #ifdef ZOOMOUT_NOT_ROTATE 
                if ((vpp_zoom >= ZOOMOUT_BASE) && (vpp_zoom <= ZOOMOUT_MAX))
                    invalid_key();
                else
                #endif
                #ifdef HANYANG_LR_CHANGE_PAGE  //Maoyong 2004.07.02
                if( IsValidAreaChangePage(1) )
                    FSGUI_ChangFileDirPage(1);
                else
                #endif

                {
                #ifdef OP_IR//libing 
                if(Is_JPEG_PLAY_STATE())
                {
                    invalid_key();
                    return;
                }
                #endif  
                OSD1000ISP_STATUS(OSDISP_DIR_ROTATE, OSDIR_RIGHT);

                ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_R);
                }
            }
            return;
        }

        #if defined(ROTATE_WHEN_PAUSE)&&!defined(JPEG_USE_ANGLE_KEY)       //zhaoyanhua add 03-10-13 10:09
        else if ((play_state == VCD_STATE_PAUSE) && (Is_JPEG_SlideMode()))
        {
            ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_R);
            return;
        }
        #endif    

#if defined(LR_AND_ECHOUPDN_IN_A_KEY) || defined(LRUPDW_AND_BACKWARD_FORWARD_PREV_NEXT_IN_A_KEY) ||defined(LR_AND_KEYUPDN_IN_A_KEY)  //nono 20020706   wu 20020920
        else
        {
            invalid_key();
            return;
        }
#endif
    }
#ifdef MINUS_VR_AUTH_PLAYBACK
	if(bDVDminusVR&& (play_state == VCD_STATE_MP3_FILELIST))
	{
		ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_R);
	   	return;
	}
#endif

#ifdef LR_AND_ECHOUPDN_IN_A_KEY //nono 20020706
    ircmd_echo_up();
#elif defined(LRUPDW_AND_BACKWARD_FORWARD_PREV_NEXT_IN_A_KEY)   //wu 20020920
    ircmd_forward();
#elif defined(FUSS_FEIYANG_2120_PANEL)   //wu 20020923
    ircmd_next();
#elif defined(LR_AND_KEYUPDN_IN_A_KEY)  //nono 20020706
    ircmd_key_up();
#elif defined(CF_GPIO_CONTROL_COLOR)

   chang_vfd_back_color_up();
//#elif defined(BRIGHTNESS_COLOR_KEY)   // Kevin Sep 21,04 
//   BriCol_value_up();                 // Kevin Sep 21,04 
#else
    invalid_key();
#endif
}


//----------------------------------ending-------------------------------------------------------

