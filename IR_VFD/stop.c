extern void VMG_Load_PTL_MAIT(void);

#if defined(JPEG_STOP_KEY_SHOW_STOP)   //yaowh modi 041123
int is_stop_key;
#endif

#ifdef SUPPORT_WMA
    extern int fnWMAgotoPacket(UINT32 nPck);
#endif

#ifdef SUPPORT_MP3_ENCODER //qinhua,2005-11-10 20:34
extern void stop_current_ripping(void);
extern UINT32 recNew;
#endif 

#ifdef  MP3_ONLY_STOP_TO_GUI//zhaoyanhua add 2004-1-5 16:52
//for bbk,when MP3 ,stop has no PRE_STOP and stop at GUI.
/*
 * Description:
 *   clear some parameters to not excute ResumePlay.
 *
 */
static inline void ClrMP3ResumePara(void)		
{		
#if !defined(MP3_STOP_IN_GUI_AND_NEED_RESUME_MSF)&&!defined(ALCO_DVD_UI)
	if ( Is_MP3_STATE() ) 
	{
	    resumeMSF = 0;
		disp_time = 0;
        #ifndef MP3_STOP_IN_GUI_AND_NEED_RESUME_TRACK
        FSNav_MP3Init(); //axel for cannot resume 1st mp3 2004/8/5 
        #endif
    #ifdef SUPPORT_WMA//zhaoyanhua add 2004-1-7 14:27
		if (GetCurrentFileType() == CDROM_WMA)
		{	
			asf_resume_pck = asf_pck_current = 0;
			asf_resume_len = lba_st.len = 0;

		}
    #endif//SUPPORT_WMA	
	}
#endif//end #ifndef MP3_STOP_IN_GUI_AND_NEED_RESUME_MSF
}
#endif//MP3_ONLY_STOP_TO_GUI

#if (defined(STOP_LOADER)||defined(SUPPORT_RECEIVER))  //huziqin 2004-2-26
UINT8 pre_stop;

void stop_loader(void)
{
    if(pre_stop)
    {
        pre_stop=0;
        flush_atapi();//terry,0515,let data tranfer finish
    }else
    {
        abort_play();
    }
}
#endif

/*
** ircmd stop
*/
//#define PLAY_JPEG_STOP_USE_AS_RETURN
#ifdef FALSE_POWER//zhuyanfeng 20041008
extern BYTE j;
#endif
#ifdef  USER_VERSION_INFORMATION//eastech	
extern	BYTE	custm_count;
extern	BYTE	enter_display_flag;
#endif

#ifdef MP3_STOP_IN_GUI_AND_LOGO //linrc add 2004-8-2 10:40 for SHAPE DVD 
UINT8 Stop_StateForTwice = 0;   //when play mp3,first enter stop,it stop to GUI, the twice enter stop to logo
#endif                          //this parameter is the enter counter
#ifdef STOP_15M_AUTO_POWEROFF
 UINT8 STOP_15M_STATE;
 extern unsigned short int sleep_counter;
 #endif 
#ifdef TEST_VFD_PANNEL_AND_KEY//lijd 2005-5-8 14:00
 BYTE     Test_Stop_flag=0;
#endif
#ifdef MP3_ONLY_STOP_TO_GUI// wsf 2005-7-5 16:57
	extern void FSShowDirIcon(void);
	extern UINT16 refresh_dir_page;
#endif
#ifdef MP3_JPEG_COWORK
BYTE cowork_dsp_stop;  //hongfeng 2006/4/24 17:32
#endif

void    ircmd_stop(void)
{
    #ifdef ALCO_DIVX_UI//shenyj add for alco 12/12
if((GetCurrentFileType() == CDROM_AVI)||(GetCurrentFileType() == CDROM_MP4))
{
    if((system_state==SYSTEM_SETUP_BROWSER)||(play_state==VCD_STATE_READTOC))
    {
        invalid_key();
	    return; 
    }
}


    if((GetCurrentFileType() == CDROM_AVI)||(GetCurrentFileType() == CDROM_MP4))
    osd_init();
#endif
    
	 #ifdef OP_DVD5121_PANEL //qinhua ,add 2005-9-5 22:34
  if (regs0->iop_data[6]==IR_ADDR_PATT)
 {
      if( (pressed_flag!=1) ) 
    {
       pressed_flag = 1;
       return;
    }
    else
    {
       pressed_flag = 0;
    }
}
#endif 
     
 #ifdef SUPPORT_MP3_ENCODER //qinhua,2005-11-10 20:34
 if(cd_type_loaded == CDDA)  
  {
  if((pre_ripping_flag)||((mp3_encoder_state == test_write_data)&&(recNew<1)))
	{
    invalid_key();
      return;
   }
         ripping_flag=0;   
   stop_current_ripping();
        }                                
#endif
	
	int id;
	#ifdef  OP_PLAYMODE//libing 2005-7-4 10:10
	extern int program_func_flag;
	program_func_flag = 0;
	#endif
	#ifdef SCORE_IN_PLAYMODE_MENU//libing 2005-8-3 19:41
		score_flag = 0;
	#endif	
	#ifdef DVD_5_DISC_RESUME//lijd 2005-6-30 21:56                    
    if(cd_type_loaded == CDDVD)
    {                           
        RSM_save(0xff,DVD_PRESTOP_RSM_ITEM); //chenzhao 2006-9-13 11:39 .
    }
	#endif

    #if defined(MP3_JPEG_COWORK)&&defined(STOP_MP3_JPG_ALL)//hongfeng modify 2005-12-06
    if((pFsJpeg->gifsFuncBtn==FS_FUNC_JPEG)&&(back_sign==0))
    {
        cowork_dsp_stop = AUDIF_Set_Stop();      
    }
    #endif
#ifdef JPEG_STOP_TO_RETURN  //hongfeng 2005-11-1
    if(Is_JPEG_STATE())
        {
        ircmd_post_func(CMD_FUNC|CMD_FUNC_RETURN);
        return;
        }
#endif

    #ifdef KODAKBOOK_only_ONE_STOP  //hongfeng 2005-04-27
     if(pFsJpeg->g_nJpegMode == JPEG_THUMBNAIL_MODE )
	{
	    invalid_key();
	    return;
	}
 #endif
    #ifdef MP3_ONLY_STOP_TO_GUI //hongfeng add 2005-11-07
    if(play_state==VCD_STATE_MP3_FILELIST)
        {
        invalid_key();
        return;
        }
    #endif
    #ifdef OP_PLAYMODE//libing 2005-7-14 22:01
    if(shuffle_flag)  
    shuffle_flag = 0;  
    #endif            
	#ifdef MP3_ONLY_STOP_TO_GUI//wsf 2005-7-5 16:57
	if((cd_type_loaded == CDROM)&&((cd_subtype == CDROM_MP3)||(cd_subtype ==CDROM_WMA)))
	{
		refresh_dir_page=1;
		FSShowDirIcon();
	}
	#endif

	#ifdef OP_STOP_PANEL_DISPLAY//lijd 2005-6-30 11:33	     
		 StopTimes++;
		 if(StopTimes>2) StopTimes=2;		 
	#endif 
	
    #ifdef CrYCb16_GRAPHIC_MODE //axel 2005/5/20 
        regs0->display_mode = 0x0;
    #endif    

	#ifdef TEST_VFD_PANNEL_AND_KEY//lijd 2005-5-8 14:00
	if( (play_state==VCD_STATE_IDLE)||(play_state==VCD_STATE_OPEN) ) 
	{
	    if(Test_Front_Panel_flag==1)
	    {
	    	Test_Stop_flag++;
	    	if(Test_Stop_flag>2) Test_Stop_flag=0;
	    	return;
	    }
	     else   return;    
    }   
	#endif	
#ifdef DVB1000_NON_OS	
#if defined(SUPPORT_EPG) && defined(STOP_KEY_ENTER_EPG) //in Argus IR, EPG/STOP are combo key
	if( (system_state == SYSTEM_TS) && (full_scrn == 0) && !is_zoom())
	{
		ShowEPGWindow();
		return;
	}
#endif
#endif  //#ifdef DVB1000_NON_OS
	
	  
#ifdef STOP_CHG_TO_RETURN
	UINT8 do_return_in_stop = 0;//liumzh 0416
if(Is_OTHER_STATE() || Is_JPEG_STATE())//liumzh 0416
	{
        ircmd_post_func(CMD_FUNC | CMD_FUNC_RETURN);
		do_return_in_stop = 1;
   	}
    #endif
	
	#ifdef OP_PLAYMODE //libing 2005-4-13 16:58
		DispFadeOut();
	#endif
	
#ifdef STOP_15M_AUTO_POWEROFF
		  sleep_counter=15;
                STOP_15M_STATE=1;
#endif

    //Maoyong 2004-10-25 15:51 for DVB Scan stop
    #ifdef DVB1000_OSD_MENU
    if(system_state == SYSTEM_TS)
    {
	    if(ScanCompleted == 0)
	        UserAbortScan = 1;
	    return;
	}
    #endif
    #ifdef NEED_DIFF_IR_PANEL_KEY
    if(panel_key_flag & (0x01<<0))
       panel_key_flag = 0;
    #endif
    
	#if defined(ALCO_DVD_UI)
    if((!resumeMSF) && ((play_state==VCD_STATE_STOP)||
    #ifdef JPEG_THUMBNAIL_MENU
                        ((cd_type_loaded==CDROM)&&(Is_JPEG_STATE())&&(!pFsJpeg->gbfsSlide)&&(JPEG_THUMBNAIL_MODE!=pFsJpeg->g_nJpegMode))) 
    #else
                        ((cd_type_loaded==CDROM)&&(Is_JPEG_STATE())&&(!pFsJpeg->gbfsSlide)))
    #endif
                        )
    {
      if(((Is_JPEG_STATE())&&(!pFsJpeg->gbfsSlide))&&(pFsJpeg->ControlArea!=CNT_AREA_DIR))
      {
        ircmd_left();
        #ifndef JPEG_NOT_STOP_LOADER
        #ifdef STOP_LOADER
        stop_loader();
        #endif
        #endif
      }
      else
      
      invalid_key();
      return;
    }	
    #endif//#if defined(ALCO_DVD_UI)
    
#ifdef ALCO_DVD_UI
    if(/*(prog_cnt) &&*/ (play_state==VCD_STATE_STOP))
    {
		prog_func_off();
		prog_func_clear();
	}
#endif

#ifdef CONTINUOUS_NUM_KEY_SELECT
    if(ir_num_timer)
      ir_continuous_num_clr();
#endif

#ifdef SUPPORT_MIDIDISK_TITLE
        if (bIsPlayMidiTitle)//xlluo for midi title
        {
		invalid_key();
		return;
        }
#endif
#ifdef  SUPPORT_SANJING_STOP    //xlluo add 04-11-6 for sanjing request
        if (MenuState >= MENU_MULTI_INDEX_SEL)
        {
		invalid_key();
		return;
        }
#endif
   
    #if defined(JPEG_MENU_DONT_PAUSE)&&defined(PORTABLE_DVD)//Jack 20041008 nono modify 20041009
    #ifdef JPEG_THUMBNAIL_MENU
    if((JPEG_THUMBNAIL_MODE == pFsJpeg->g_nJpegMode && pFsJpeg->gbfsSlide)/* && (pFsJpeg->gbfsSlide == 0)*/)
      pFsJpeg->g_nJpegMode = JPEG_NORMAL_MODE;
    #endif
    #endif
 
	if ( (Is_MP3_STATE()) && (adv_search_time!=0) )	//liumzh 2004-9-10 17:24
		adv_search_time = 0;

    //Maoyong 2004-8-13 0:45 stop should not do action in thumbnail menu for usage: stop key not return from 6 pic mode to GUI
	#if defined(JPEG_THUMBNAIL_MENU) && defined(MODIFY_KODAKBOOK_NO_GUI)
    if(JPEG_THUMBNAIL_MODE == pFsJpeg->g_nJpegMode)
	{
	    invalid_key();
	    return;
	}
    #endif //#ifdef JPEG_THUMBNAIL_MENU

#ifdef MP3_STOP_IN_GUI_AND_LOGO     //linrc add 2004-8-2 10:43
    if(play_state == VCD_STATE_NORMAL && play_state != VCD_STATE_MP3_FILELIST)
    {
        Stop_StateForTwice = 0;
    }     
    if(cd_type_loaded==CDROM && Is_MP3_STATE())
    {
        Stop_StateForTwice++;    
    }
#endif	
 
#if defined(MP3_ONLY_STOP_TO_GUI)&&defined(MODIFY_MP3_ONLY_STOP_TO_GUI)//nono add 4-8-10 11:00
    if ( (Is_MP3_STATE()) 
      && (play_state == VCD_STATE_MP3_FILELIST) //only in FsMP3mainloop,can use "REPAB"
        )
    {
        invalid_key();
        return; 
    }
#endif
 
#ifdef  USER_VERSION_INFORMATION	//eastech
	printf("enter ircmd_stop \n");
	if( (play_state==VCD_STATE_OPEN)) //||(play_state==VCD_STATE_OPEN) ) 
	{
	       custm_count=0;        	
        	enter_display_flag=1;
        	ClearOsdMsg(2);        	
        	return;
	}
#endif	


    #ifdef MOVE_HIGH_LIGHT_IN_PROG_MODE
	if(cd_type_loaded == CDROM){     //wsf  2004-7-20 14:55  changed for cancel program when stop  
            prog_cnt=0;
            prog_func_off();
            prog_func_clear();        
        }
    #endif

#ifdef AD_TCL
	DispFadeOut();
#endif	

#if ((defined(SDRAM_16Mb_Mode)||defined(PLAY_JPEG_STOP_USE_AS_RETURN))&&!defined(JPG_EFFECT))
#ifndef ALCO_DVD_UI
	if( Is_JPEG_STATE()&&(prog_state!=4)&&(pFsJpeg->g_nJpegMode != JPEG_PREVIEW_MODE))//nonotestjpg //lyc 2006-9-14,add for 16m ircmd_setup
    {
        #ifdef PLAY_JPEG_STOP_USE_AS_RETURN_SHOW_STOP//yaowh add 04-12-22
        is_stop_key = 1 ;
        #endif
        
		ircmd_return();
		return;
    }
	else
#endif	
#endif//#ifdef SDRAM_16Mb_Mode
    {	
#ifdef NEW_STYLE_SETUP//terry,2003/8/20 10:01PM
		if(setup_state!=1)
#endif    
#ifdef SDRAM_16Mb_Mode
			if( (prog_state!=1)&&(prog_state!=4) )
#endif
			{
				if (play_state!=VCD_STATE_STOP) { //PRE-STOP shouldn't show invalid-key, Jeff 20020522
					if(UOP_check(UOP_STOP))
					{
						invalid_key();
						return;
					}
				}
			}
			
		#if !defined(SPHE1000)
			if((cd_type_loaded==CDROM)&&(Mp3ReadFinish==0)) //huo 2000/10/31
		#else
			if((cd_type_loaded==CDROM)&&(Mp3ReadFinish==0) && (system_state!=SYSTEM_FILESTREAM)) //MIKEY 2004.06.25 for stop
		#endif
			{
				invalid_key();
				return;
			}
			
			ircmd_cancel(C_ZOOM);

#ifdef SUPPORT_WMA
			if (GetCurrentFileType() == CDROM_WMA) // Robert 2003/12/29
				AVD_SetMediaTimeout(); 
#endif            
			
			if(system_state!=SYSTEM_READ_TITLE)
			{
				//terry,clear vobu still
				Vobu_still=0;
				P_vobu=0;

#if defined(IR_PLAY_RESUME) ||defined(IR_PLAY_RESUME_PAUSE)//nono 2-3-26 11:34 for fuss

	#ifdef SUPPORT_FILE_SYSTEM_MODE		//to avoid bug when stop,gerry  3-1-26 17:39
        #if defined(SUPPORT_MP4)&&!defined(MODIFY_MP4_STOP_NOT_NEED_RESUME)//nono 4-8-10 22:47 for eastech
				if((( GetCurrentFileType() == CDROM_MP4 ) // Robert 2003/12/29
				//kevinmonkey sz 050614 fixing avi extension file name won't resume
            #ifdef TELL_FROM_MP4_EXT_NAME
                ||( GetCurrentFileType() == CDROM_AVI ) 
				||( GetCurrentFileType() == CDROM_DIV )) 
            #endif  //#ifdef TELL_FROM_MP4_EXT_NAME
                #ifdef ALCO_DVD_UI
                &&(play_state==VCD_STATE_NORMAL)//shenyj modify for alco 11/29
                #endif
				)
				{
                    if( IS_FILE_TYPE_MPG12() ) // 2005/09/29 yltseng
                    {
                        resumeMSF = resumeTRK = 0;
                    }
                    else
                    {
            #if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)//liweihua 2004-4-28 15:09
                        if(media_type == MEDIA_CARD)
                            resumeMSF = 0;
                        else
            #endif
//mark by roger 2006-06-08
//using GET_MP4_TIME() replace GET_ASF_TIME() 
//#if	defined(SUPPORT_ASF) && defined(SUPPORT_ASF_PTS) 
						//asf file not use GET_MP4_TIME() to get display time for av asf file
						//add by roger 2006-05-30 
//						if (IS_FILE_TYPE_ASF())
//							resumeMSF = GET_ASF_TIME();		
//						else							
//#endif				
                            resumeMSF = GET_MP4_TIME();
                        #ifdef ALCO_DVD_UI    
                        counter_down = 10;
                        #endif
                        resumeTRK = pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry;  // 2004/05/19 yltseng
                    }
				}
                else
        #endif
                #if defined(CDG_RESUME_PLAY_TO_TRACK)||defined(CDG_TRACK_RESUME)
				if((cd_type_loaded==CDROM)&&(!Is_MP3_STATE()))//chenzhao20051111 add CDG prestop
                #else
				if(((cd_type_loaded==CDROM)&&(!Is_MP3_STATE()))||(is_cdg_disc(1)))//wanghaoying 2003-9-12 17:11 to avoid CDG prestop
                #endif
				{
                   	resumeMSF=0;    	
				}
				else
	#endif
				{
					if (cd_type_loaded != CDDVD)
					{
	    #ifdef SDRAM_16Mb_Mode   //sunzhh add for SEQ PLAY when press "setup" continuously 2004-10-21 23:50
					    if((prog_state==4)||(prog_state == 1))			   
					    resumeMSF = 0;						 
		#endif
	#ifdef RECORD_PER_SECOND
						if(play_state != VCD_STATE_STOP)
							resumeMSF=0	;		//for display PRE_STOP  gerry  2-12-3 12:13
	#endif
						#ifdef SUPPORT_PROG_RESUME
						#ifdef MP3_ONLY_STOP_TO_GUI
						if (/*(resumeMSF == 0) &&*/ ((play_state!=VCD_STATE_STOP)&&(play_state!=VCD_STATE_MP3_FILELIST)) && (Is_JPEG_STATE() == 0) &&
						#else
						if (/*(resumeMSF == 0) &&*/ (play_state != VCD_STATE_STOP) && (Is_JPEG_STATE() == 0) &&
						#endif
						#else
						if ((resumeMSF == 0) && (play_state != VCD_STATE_STOP) && (Is_JPEG_STATE() == 0) &&
						#endif
	#ifdef SUPPORT_NESGAME
							(Is_GAME_STATE() ==0 ) &&
	#endif
	#ifdef SUPPORT_FILE_SYSTEM_MODE
							(Is_OTHER_STATE() ==0 ) &&
	#endif
							(!is_menu()) && ((cd_trk_now >= cd_trk_lo_now) && (cd_trk_now <= cd_trk_hi)))//nono 2-6-7 11:36
						{
	#if  defined(QISHENG_DVD)||defined(VTREK_DVD)||defined(DESAY_DVD)
							if (IsPBCOn())
							{
								ircmd_return();
								return;
							}
	#endif
                            resumeMSF = ( is_svo_dvd() ) ? s_msf&0xffffffff : s_msf&0x00ffffff; //2004/01/13 yltseng for DVD disk containing data
							resumeTRK = cd_trk_now; //2002/3/12
                            #ifdef CDG_RESUME_PLAY_TO_TRACK
                            if(is_cdg_disc(0))
                            resumeMSF = gettrkmsf(cd_trk_now)&0x00FFFFFF; //chenzhao20051111 add CDG prestop
                            #endif
//Maoyong 2004.06.22 moved out

	#if defined(IR_PLAY_RESUME) && defined(POWER_RESUME)  //yw 021003
						     #ifdef SUPPORT_LAST_MEMERY
					         if(memery_resumeflag)
					         #endif//end=> #ifdef SUPPORT_LAST_MEMERY
							power_resumeflag = 1;
	#endif
						}
						else
						{
							resumeMSF = 0;//nono test
							resumeTRK = 0; //2002/3/12
	#ifdef SUPPORT_WMA
							if (GetCurrentFileType() == CDROM_WMA) // Robert 2003/12/29
								asf_resume_pck = asf_resume_len = 0;
	#endif
						}
					}else {
						resumeMSF = 0;
					}

				}
#else   //defined(IR_PLAY_RESUME) ||defined(IR_PLAY_RESUME_PAUSE)
				if (cd_type_loaded == CDROM)
				{
					if ( Is_MP3_STATE() ) { //Jeff 20020518
						resumeMSF = s_msf;
					} else {
						resumeMSF = 0;
					}
				}
				else if(cd_type_loaded!=CDDVD)
				{
					resumeMSF=s_msf&0x00ffffff;
				}
				
				resumeTRK = cd_trk_now;

#endif  //defined(IR_PLAY_RESUME) ||defined(IR_PLAY_RESUME_PAUSE)

//Maoyong 2004.06.22 move the part under IRC_RESUME & IRC_PLAY_RESUME definiton here
#ifdef SUPPORT_WMA
			if (GetCurrentFileType() == CDROM_WMA) // Robert 2003/12/29
			{
			    if(play_state == VCD_STATE_STOP){
			        // clear resume packet and len and pck time
					asf_resume_pck = asf_resume_len = 0;
					resumeMSF = 0;
			    }else{
				asf_resume_pck = asf_pck_current;
                #if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)//liweihua 2004-4-13
                if(media_type == MEDIA_CARD)
                    {
                    asf_resume_len = cardFile.iFileSize-(fnWMAgotoPacket(asf_resume_pck)-cardFile.stLBA);
	                 #ifdef IC_8202L //qinhua,add for 8202L usb wma not pre stop,2006-7-20 05:39ÏÂÎç
				       delay_srv_10ms(5);	
				     #endif	
                	}
                else
                #endif
			    asf_resume_len = lba_st.len;
			
			}
			}
#endif

#ifdef SUPPORT_CDG                      //linrc add 2004-11-4 16:36
#ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU    //when "MNP" what define in setupmenu is on
extern BYTE VcdControlFlag();	            //VCD & CDG play one TRK in one time....
if((VcdControlFlag())&&(is_cdg_disc(0)))
{
    resumeMSF = 0;
    resumeTRK = 0;
}
#endif
#endif

#ifdef  MP3_ONLY_STOP_TO_GUI//zhaoyanhua add 2004-1-5 16:52
		//for bbk,when MP3 ,stop has no PRE_STOP and stop at GUI.
#if !defined(ALCO_DVD_UI)&& !defined(MP3_WMA_HAS_RESUME) //chenzhao 2006-4-17 10:7 .
		ClrMP3ResumePara();	//zhaoyanhua changed  2004-4-13 15:13
#endif
#endif//MP3_ONLY_STOP_TO_GUI
		 
        
				if(play_state != VCD_STATE_STOP)
				  {
					#ifdef DVD_5_DISC_RESUME//lijd 2005-6-30 21:56                    
                        if(cd_type_loaded == CDDVD)
                        {                           
                            RSM_save(0xff,DVD_PRESTOP_RSM_ITEM); //chenzhao 2006-9-13 11:39 .
                        }
                    #endif
                    
                    #ifdef STOP_RESUME_DVD_VCD
                    if(IS_DVD_VCD_DISC())
                    {
                        resumeMSF = 1;
                          
                        #ifdef DISC_ID_IN_FLASH
                        if(cd_type_loaded == CDDVD)
                        {                           
                            if(!need_record)
                            {                           
                                RSM_save(0xff,DVD_PRESTOP_RSM_ITEM); //chenzhao 2006-9-13 11:39 .
                            }
                            need_record = PRE_STOP_FLAG;
                        }
                        else if(cd_type_loaded != CDSVCD)
                        #endif
                        {
                            RsmInfo2Flash(0);
                            need_record = 5;//added 05/07/27 for VCD Playing--->STOP--->Quickly SETUP--->Then OSD is disordered.
                        }    
				    }
				    else
                    {
                        need_record = 5;//added 05/08/03 for All Disc Playing--->STOP--->Quickly SETUP--->Then OSD is disordered.
                    }    
				    #endif//#ifdef STOP_RESUME_DVD_VCD
				    
				    #if defined(SUPPORT_FILE_SYSTEM_MODE)&&defined(STOP_TO_GUI_WHEN_JPEG_OTHER )   //sunzhh add 
				    if((Is_OTHER_STATE() || Is_JPEG_STATE())&& (prog_state != 1))
				    {
				        ircmd_post_func(CMD_FUNC | CMD_FUNC_RETURN); 
				        resumeMSF = 0; 
				    }
				    else
				    #endif

					ircmd_post_func(CMD_FUNC | CMD_FUNC_STOP);
				}	
#if defined(NEW_PARENTAL_GUI)||defined(MODIFY_PARENTAL_GUI)	
		//when enter"STOP",clear this flag.
		//to show parental GUI when enter"PLAY" next time.
		//zhaoyanhua add 2003-11-29 9:26
	#ifdef TUNR_OFF_PARENTAL_LVL
	#ifndef NOT_SHOW_GUI_WHEN_PLAY_IN_STOP
	//when play parental disc,stop ->play not show parental GUI. 
	//zhaoyanhua 2004-2-9 17:26
				bTurnOffParentalLVL = 0;
	#endif
	#endif
				//to avoid the bug :
				// first enter"ONE_KEY_PASS",then enter STOP,the following
				//PLAY will excute "ONE_KEY_PASS" 
#ifdef ONE_KEY_PASS
				one_key_pass_play = 0;
#endif
				dvd_title = 0;
#endif//#if defined(NEW_PARENTAL_GUI)||defined(MODIFY_PARENTAL_GUI)	

				// alan 02-05-21 modified to fix '­ã°±¤î' when stop pressed
#if defined(IR_PLAY_RESUME) ||defined(IR_PLAY_RESUME_PAUSE)
			if(resumeMSF)
			{
                OSD1000ISP_STATUS(OSDISP_PRE_STOP, OSDIR_STOP);

				id = STR_OS_PRE_STOP;
				#ifdef MODIFY_CDG_STOP_SHOW	//dingzhy add
				if(CDG_IsCDGNow()==1)
				id = STR_OS_STOP;
				#endif

	            #ifdef STOP_LOADER//terry,2003/9/15 04:01PM
	   			#ifndef FALSE_POWER			
					pre_stop = 1;
				#else
		          	abort_play();
				#endif		
	            #endif
                
#if 0//nono 20050715 pls use special difinition
					if((GetCurrentFileType() == CDROM_MP4)||Is_JPEG_PLAY_STATE())   //mp4 stop to current file wuzhj 2005-04-28
                    {
                        ircmd_post_func(CMD_FUNC | CMD_FUNC_RETURN);
                        //return;
                    }
#endif//#if 0//nono 20050715 pls use special difinition

#if defined(STOP_RESUME_DVD_VCD)&&defined(DISC_ID_IN_FLASH)
                if(cd_type_loaded == CDSVCD)
                {
                    //Jack modify 05/07/27
                    //It seems that in SVCD we must write Flash later,so i do it in polling after need_record timeout.
                    //LoadModual(MODUAL_CDROM);
                    //RsmInfo2Flash(0); 
                    need_record = REAL_RECORD_VALUE;
                }    
#endif
                    			

			}else
#endif
				{
//#define STOP_LOADER            
#ifdef STOP_LOADER//terry,2003/8/23 08:58PM		
#ifdef JPEG_NOT_STOP_LOADER
					if(!Is_JPEG_STATE())
#endif
					abort_play();
#endif

                    OSD1000ISP_STATUS(OSDISP_STOP, OSDIR_STOP);

					id = STR_OS_STOP;
#ifdef TONIC_DVD
					shuffle_flag=0;
#endif
                    #ifdef DISPLAY_REMAIN_TIME
                    osd_tog_region(0,OSD_OFF); 
                    t_disp = old_t_disp = 0;
                    display_and_time = 0;
                    display_flag = 0; 
                    #endif
                                                    

#if 0//nono 20050715 pls use special difinition.
                   if((GetCurrentFileType() == CDROM_MP4)||Is_JPEG_PLAY_STATE())   //mp4 stop to current file wuzhj 2005-04-28
                    {
                        ircmd_post_func(CMD_FUNC | CMD_FUNC_RETURN);
                        //return;
                    }
#endif//#if 0//nono 20050715 pls use special difinition
//move "disp_time = 0" to Line 159
//zhaoyanhua mask them 2004-1-7 14:29					
//#ifdef  MP3_ONLY_STOP_TO_GUI//zhaoyanhua add 2004-1-5 13:53
//			disp_time = 0;	
//#endif // MP3_ONLY_STOP_TO_GUI 

#ifdef STOP_RESUME_DVD_VCD
                    if(IS_DVD_VCD_DISC())
                    {
                        #ifdef MODIFY_FOR_DISPLAY_DBG//shenyj add for alco 1108
                        remain = 0; t_disp = 0; display_flag = 0;display_and_time=0;
                        #endif 
                        resumeMSF = 0;
                    
                        #ifdef AFTER_RECORD_DELAY
                        if(cd_type_loaded == CDDVD)
                            need_record = AFTER_RECORD_DELAY_CNT;
                        #endif				
                        RsmInfo2Flash(0);
                    }    
#endif//#ifdef STOP_RESUME_DVD_VCD			

				}
#if defined( SDRAM_16Mb_Mode ) && !defined( SETUP_PROGRAM_IN_PLACE_UNDER_16M ) // 2004/12/27 yltseng
				if (prog_state==0)
#endif

#ifdef GBM_DVD
					PrintOsdMsg(id,REGION1,0,0);
#elif defined(AD_TCL)//2004-3-22 13:16 lijd
	{

	  if (menu_id)
	  {
	        PrintOsdMsg(30,REGION1,1,0);  //display "menu"
	        menu_id=0;
	  }	
	  else
	  	{
	        PrintOsdMsg(id,REGION1,1,0);   //display "stop"
	  	}	
	}					
#else 
        #if defined(FS_BMP_GUI)//when help mode,show help page end,no show "stop"
            if (help_stop_flag == 1)
                help_stop_flag = 0;
            else
                PrintOsdMsg(id,REGION1,1,0);
        #else
            
            #ifdef ALCO_DVD_UI
            osd_tog_region(REGION1,OSD_OFF);
		    #endif

            #ifdef FAT_Write_UI                     //sunzhh add 2004-11-25
                if (!((full_scrn & PERIPHERAL)&&(pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)))
            #endif     //#ifdef FAT_Write_UI
			PrintOsdMsg(id,REGION1,1,0);
		#endif

#endif
				play_state = VCD_STATE_STOP;
	}
	else
		bInitPlayTrk = 1;

#ifdef SDRAM_16Mb_Mode
	if (prog_state == 0)
#endif

#ifdef CANCEL_PROG_DOUBLE_STOP			//dingzhy  2/2/2004 1:30PM
if(!resumeMSF)
		{
		prog_cnt = 0;           // alan 0429 : clear prog_mode when stop pressed
			prog_func_clear();
			//PrintOsdMsg(STR_OS_STOP,REGION1,2,0);//dingzhy for test
		}
#elif defined(NEW_STYLE_SETUP)		//gerry for gbm setup menu,2004-3-27 16:30
		if(!setup_state)
		prog_cnt = 0;		
#else
		prog_cnt = 0;
#endif		//endif  CANCEL_PROG_DOUBLE_STOP


//wanghaoying mode 2003-11-24 17:44     
//Modified for resume error when CDDA, maybe still some bug here
#if defined(VIRTUAL_KEYBOARD)&&defined(CD_PLAYER)   //liweihua 2003-9-18
    if(cd_type_loaded==CDDA)
        full_scrn |= KEYBOARD;
#endif

    }//if(Is_JPEG_STATE())//nonotestjpg//#if defined(SDRAM_16Mb_Mode)||defined(PLAY_JPEG_STOP_USE_AS_RETURN)

    #ifdef SUPPORT_QUICKTIME
    file_set_subp_status(0);
    #endif //SUPPORT_QUICKTIME

#ifdef  NOCHANGE_DISPLAY_WHEN_PRESTOP//chenzhao20051110
    if(resumeMSF==0)
        show_time();
#endif  


    #ifdef MODIFY_FOR_DISPLAY_DBG///shenyj add for alco 11/24
    if((play_state==VCD_STATE_STOP)  //shenyj modify 2006-8-24 03:40ÏÂÎç
    #ifdef STOP_LOADER
    &&(pre_stop==0)
    #endif
    )
    {
        polling_clock=0;
        remain = 0; 
        t_disp = 0; 
        display_flag = 0;
        display_and_time=0;
    }
    #endif
    
    #ifdef USE_STOP_SWITCH_DISC_CARD_USB
    if((play_state==VCD_STATE_STOP)&&(pre_stop==0))
    {
        ircmd_switch_cd_usb_cf_other();
    }
    #endif  

    #ifdef ALCO_DVD_UI
    counter_down = 15;
    #endif

}


void system_stop(void)
{
    stop_init();

    
#ifdef STOP_LOADER //terry,2003/9/28 08:08PM
    stop_loader();    
#else
    flush_atapi();//terry,0515,let data tranfer finish
#endif

#ifdef ALCO_MODIFY_PAL_OSD
    if(t_disp)
        osd_tog_region(0,OSD_OFF);
#endif
    
    ShowTitle();//NONO maybe isn't needed.

#ifdef ALCO_MODIFY_PAL_OSD
    if(t_disp)
        osd_tog_region(0,OSD_ON);
#endif

#if defined(NEW_PARENTAL_GUI)||defined(MODIFY_PARENTAL_GUI)	//zhaoyanhua add 2003-11-28 14:47
    play_state=VCD_STATE_STOP;
    show_dvd_err();
#else
    show_dvd_err();
    play_state=VCD_STATE_STOP;
#endif
    #ifdef SDRAM_16Mb_Mode
    if (prog_state==1)
    {
        prog_state=2;
        ircmd_prog();
    } else if (prog_state==4)
    {
        prog_state=2;
        ircmd_setup();
    }
    #endif
    
    #ifdef NEW_STYLE_SETUP//only dvd excute this .zhaoyanhua note 2003-07-18 23:20
    #ifndef SDRAM_16Mb_Mode
    if(setup_state==1)
    {
    	setup_state = 2;
    	ircmd_setup();
    }
    #endif//SDRAM_16Mb_Mode
    #endif
    
#if defined(STOP_RESUME_DVD_VCD)&&defined(DISC_ID_IN_FLASH)
    LoadModual(MODUAL_CDROM);//moved to here for the bug of "wehn DVD auto stop,if write/read flash system will halt."
    if(resumeMSF && (need_record==PRE_STOP_FLAG))
    {
        need_record = REAL_RECORD_VALUE;
        //modual_loaded &= (~(1<<MODUAL_MPEG));
        //modual_loaded &= (~(1<<MODUAL_DVD));
        resumeMSF = 1;
        RsmInfo2Flash(0);
        #ifdef AFTER_RECORD_DELAY
        need_record = AFTER_RECORD_DELAY_CNT2;
        #else
        need_record = 0;
        #endif    
    }
#endif    
              
}



void system_play(void)
{
    if(play_state==VCD_STATE_STOP)
        play_state = VCD_STATE_NORMAL;
}

#if defined(NEW_PARENTAL_GUI)||defined(MODIFY_PARENTAL_GUI)	//zhaoyanhua add 2003-11-28 14:48
#define C_LOCK  0
#define C_UNLOCK 1
extern UINT32 setup_CheckPasswd();
extern UINT8   polling_avoid_reentry;
#endif

void show_dvd_err(void)
{
    UINT32  isPasswdRight __attribute__((unused));
    
    extern const char *const osd_err_str[N_OSD_LANGS][3];//[25];

    if(dvd_error)
    {
#if defined(NEW_PARENTAL_GUI)||defined(MODIFY_PARENTAL_GUI)	//zhaoyanhua add 2003-11-28 14:48
    
        if(dvd_error == PARENTAL_ERR)
        {
            
            if(polling_avoid_reentry==0)
            {
                #ifdef UNLOCK_STATE_NOT_CHECK_PASSWD
			    if(UserSet.parental_ststus)
			        disc_has_unlock = 3;
			    else 
			        disc_has_unlock = 4;
			    
			    if(disc_has_unlock != 3)
			    #endif
                isPasswdRight = setup_CheckPasswd();
                
                //if(UserSet.parental_ststus)
                if(isPasswdRight)
                {
                    NP_PTL_LVL = 8;
                    dvd_error = 0;
                #ifdef TUNR_OFF_PARENTAL_LVL		
                    bTurnOffParentalLVL=1;//terry,2002/9/20 11:40PM
                #endif
                    VMG_Load_PTL_MAIT();//load VMG+VTS PTL_ID_FLD	
                    
#ifdef ONE_KEY_PASS                    
                    if(one_key_pass_play) 
                    {
                        memset(RegionValStr[REGION1],0,14);
			            PrintOsdMsg(STR_OS_ONEKEY, REGION1, 1, 1);
			            ircmd_post_func(CMD_FUNC|CMD_FUNC_PLAY);	
                    }
                    else
#endif //ONE_KEY_PASS    axel 4-1-10 15:31                     
                        #ifdef PARENTAL_DVD_NEDD_RESUME  //hongfeng 2006/3/22 19:15
                        ircmd_play_resume();
                        #else
                        ircmd_play();
                        #endif
                   
                    #ifdef UNLOCK_STATE_NOT_CHECK_PASSWD
			        if(disc_has_unlock == 4)
			        #endif
                    UserSet.parental_ststus = C_LOCK;//set LOCK.
                }
                else
                {
#ifdef ONE_KEY_PASS
                //when one_key_pass ,only show GUI one time.
                // so must clear dvd_error to not enter this fucntion again.
                    if(one_key_pass_play)
                    {
                        dvd_error=0;
                        one_key_pass_play=0;
                    }
#endif //#ifdef ONE_KEY_PASS axel 4-1-10 15:32                    
                }

            }
         
        }
        else
        {
#endif
        //strcpy(RegionValStr[REGION1],osd_err_str[dvd_error-1][osd_font_mode]);
        strcpy(RegionValStr[REGION1],osd_err_str[osd_font_mode][dvd_error-1]);
#ifdef ALWAYS_SHOW_ERR
        PrintOsdMsg(STR_OS_SPACE,REGION1,0,1);//kenny modify it by customer
#else
        PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);//kenny modify it by customer
#endif
#if defined(NEW_PARENTAL_GUI)||defined(MODIFY_PARENTAL_GUI)	
        }
#endif    
    }
}



