
#ifdef SUPPORT_FUNCTION_MENU
#include "setup_def.h"
#endif 

#if (defined(SOFT_MENU)&&defined(VIDEOSETUPGUI))//Modifed by ChenZhao on 2004-9-22 11:33  
void InitVideoSetupGUI(void);
int IsVideoSetupExit_NextVideoSetup();
int IsPlayVideo(void)
{
	return (old_play_state!=play_state)&&(!Is_MP3_STATE()\
			&&((CDVCD10==cd_type_loaded)\
			||(CDVCD20==cd_type_loaded)\
			||(CDSVCD==cd_type_loaded)\
			||(CDDVD==cd_type_loaded)\
			||(CDJPEG==cd_type_loaded)\
			||is_mp4()\
			||Is_JPEG_STATE()\
			));
}
#endif//(defined(SOFT_MENU)&&defined(VIDEOSETUPGUI))
/*
* Wangfeng,2004-2-17 11:24
*/
static inline void show_normal_after_setup(void)
{
    if(old_play_state==VCD_STATE_NORMAL)
        RegionOnOff[REGION1][2]=STR_OS_PLAY;
    rem_osd_id = RegionOnOff[REGION1][2];
}

/*
* Terry,2004/1/30 04:28PM
*/
#if 0//def SUPPORT_USB
BYTE usb_card_setup_flag;//lijd 2004-9-29 11:23  //sunzhh modify 2005-3-11 because it results in many bugs and it no use now.
#endif
void run_pause_setting(void)
{
    #if 0//def SUPPORT_USB
         usb_card_setup_flag=1;  //sunzhh modify 2005-3-11 because it results in many bugs and it no use now.
    #endif
    if(still_timer)
    {
        old_play_state=VCD_STATE_PAUSE;
    }else if( (play_state==VCD_STATE_PAUSE)||(!cd_type_loaded)||(play_state==VCD_STATE_STOP) )
    {
        old_play_state=play_state;
    }else
    {
    #ifdef MP3_STOP_IN_GUI_START//zhaoyanhua add 03-10-14 11:39 keep inital state for MP3
        if ((Is_MP3_STATE()) && (play_state == VCD_STATE_MP3_FILELIST))
            old_play_state = VCD_STATE_MP3_FILELIST;
        else
    #elif defined(MP4_GUI_FF_INVALID)
        if ((Is_OTHER_STATE()) && (play_state == VCD_STATE_MP3_FILELIST))  //wsf  2004-9-15 20:18
            old_play_state = VCD_STATE_MP3_FILELIST;
        else
    #elif defined(DIVX_DRM) && !defined(DIVX_DRM_AES_ONLY)
    //kevinmonkey 051103 fix drm vod message don't show after setup menu
        if ((Is_OTHER_STATE()) && (play_state == VCD_STATE_MP3_FILELIST))  
            old_play_state = VCD_STATE_MP3_FILELIST;
        else    
    #endif

        // mimitsai modify, when in VCD_STATE_MP3_FILELIST state and enter setup, 
        // when exit setup, the state will be VCD_STATE_MP3_FILELIST but not VCD_STATE_NORMAL
        old_play_state= (play_state == VCD_STATE_MP3_FILELIST? VCD_STATE_MP3_FILELIST:VCD_STATE_NORMAL);
        //old_play_state=VCD_STATE_NORMAL;

        if((cd_type_loaded!=CDROM)||Is_MP3_STATE())
            run_pause(0);
#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 021014
        // when we save the old play state, we want to enable this define to avoid 
        //    entering pause state after exiting from setup page
      #if defined(MP4_GUI_FF_INVALID) || (defined(DIVX_DRM) && !defined(DIVX_DRM_AES_ONLY))
        if(play_state == VCD_STATE_NORMAL
		|| play_state == VCD_STATE_FASTFORWARD
		|| play_state == VCD_STATE_FASTBACKWARD
		|| play_state == VCD_STATE_SLOW)
      #endif
           {
        if (Is_OTHER_STATE())
            run_pause(0);
            }
#endif
    }
    if( (RegionOnOff[REGION1][2]==STR_OS_PAUSE)||(RegionOnOff[REGION1][2]==STR_OS_STEP) )//nono 2-7-17 17:22
        rem_osd_id = RegionOnOff[REGION1][2];//show "PAUSE" & "STEP"...after "setup" 2-7-15 21:44

}

#ifdef  AUTO_ADJUST_TV_TYPE
extern BYTE  Adjust_TV_type ;
#endif

#ifdef SETUP_PROGRAM_IN_PLACE_UNDER_16M

void OSDSetPause()      // 2005/01/14 yltseng
{
    #if !defined(SETUP_PLAY_CTRL)&&!defined(SETUP_DONT_PAUSE)       //wangfeng,2003-08-30 10:28        
//huziqin 2006-4-19 removed
        #ifdef  JPEG_PAUSE_WHEN_SETUP       // fengjl add 3-11-30 15:47
    if((Is_JPEG_SlideMode())&&(play_state == VCD_STATE_NORMAL))
    {  
        run_pause(0); 
       // if(Is_JPEG_SlideMode())
            old_play_state = VCD_STATE_NORMAL; 
    }
    else
        #endif //end JPEG_PAUSE_WHEN_SETUP 
    run_pause_setting();
    #endif        
}

#ifdef NEW_STYLE_SETUP
static inline UINT32 SetupSettingForNewStyleSetup()
{   // 2004/11/26 yltseng
//NOTE:
//In NEW_STYLE_SETUP && SDRAM_16Mb_Mode
//      prog_state = 0 : original state
//                   4 : to excute STOP
//                   2 : excute setup
//                   5 : At level 1,use "SELECT" to enter level 2 /3 
//                   6 : when SETUP interrupt PROGRAM or PROGRAM interrupt SETUP use this flag
//                       not excute ircmd_resume().
// zhaoyanhua note 2003-8-7 9:50               
    #ifdef SDRAM_16Mb_Mode  //zhaoyanhua add 2003-8-7 9:48                

    if (play_state!=VCD_STATE_STOP)
    {
        if (prog_state==0)
        {
            old_t_disp=t_disp;
            old_play_state=play_state;
            if( (play_state==VCD_STATE_STOP)||
                (system_state==SYSTEM_NODISC)
                ||Is_JPEG_STATE()
        #ifdef SUPPORT_FILE_SYSTEM_MODE // nono 2003-8-7 13:55
                ||Is_OTHER_STATE()
        #endif
                ||(system_state==SYSTEM_OPEN) )
            {
                prog_state = 5;
                ShowTitle();
            }else if( (pe_run==1)||(still_timer) )//terry 20030805
            {//terry,2003/8/4 10:27PM                   
            prog_state=4;
                printf("setup menu,run stop cmd\n");
            old_t_disp=t_disp;
            ircmd_stop();
            return FALSE;
            }else
            {//terry,2003/8/4 10:27PM
                invalid_key();
                return FALSE;
            }
        }
    
    }
    else
    {
        if (prog_state == 0)
        {   
            prog_state = 5; //already STOP ,only show setup_logo.zhaoyanhua 2003-8-7 13:51
            ShowTitle();
            old_t_disp=t_disp;
            old_play_state = VCD_STATE_STOP;
        }
        t_disp=0;
        DispFadeOut();
        //I masked it , but don't know if it will cause error.
        //zhaoyanhua note 2003-8-26 20:05
        regs0->osd_base_addr=OSD_BASE_USE_ADDR;//P_BIDIR_LUMA;
    }
    #else //Not SDRAM_16Mb_Mode     
    if (setup_state==0)
    {  
            old_t_disp=t_disp;
            old_play_state=play_state;
    
            if( (play_state==VCD_STATE_STOP)||
                (system_state==SYSTEM_NODISC)
                ||Is_JPEG_STATE()
        #ifdef SUPPORT_FILE_SYSTEM_MODE // nono 2003-8-7 13:55
                ||Is_OTHER_STATE()
        #endif
                ||(system_state==SYSTEM_OPEN) )
            {
                setup_state=3;
                ShowTitle();
    }
    else if( (pe_run==1)||(still_timer) )//terry 20030805
            {//terry,2003/8/4 10:27PM                   
                setup_state=1;
                printf("setup menu,run stop cmd\n");
                old_t_disp=t_disp;
                ircmd_stop();
                return FALSE;
            }else
            {//terry,2003/8/4 10:27PM
                invalid_key();
                return FALSE;
            }
      }
    #endif //SDRAM_16Mb_Mode
    
    return TRUE;
}
#else

UINT8   g_uiOSDStatus = OSD_FULL_SCREEN_STATUS_NONE;

static inline UINT32 SetupSettingForNormal()
{   // 2005/01/14 yltseng
    #ifdef SDRAM_16Mb_Mode
    if( g_uiOSDStatus == OSD_FULL_SCREEN_STATUS_NONE )
    {
        if( AVD_state != STATE_IDLE )
        {
            g_uiOSDStatus = OSD_FULL_SCREEN_STATUS_SETUP | OSD_FULL_SCREEN_STATUS_WAIT_ATAPI_CMD_FINISH;
            return FALSE;
        }
        else if( pFsJpeg->gifsState == FS_STATE_JPEG )
        {
            OSDSetPause();
        }
    }
    
    g_uiOSDStatus   = OSD_FULL_SCREEN_STATUS_SETUP | OSD_FULL_SCREEN_STATUS_ACTIVE;
    full_scrn       = SETUP;
    osd_disable();
        
    extern void SrvStopReceiveData(void);
    SrvStopReceiveData();
    regs0->osd_base_addr = A_SERVO_YA;
    
    #else
    OSDSetPause();
    #endif//SDRAM_16Mb_Mode 

    return TRUE;   
}
#endif

void ircmd_setup(void)
{
	
     #ifdef  AUTO_ADJUST_TV_TYPE    
        Adjust_TV_type=0;      
     #endif
     
#ifdef CONTINUOUS_NUM_KEY_SELECT
    if(ir_num_timer)
      return;
#endif
    
    #ifdef SUPPORT_MIDI_MENU_SEL
#if 1//ndef QISHENG_DEBUG_04_10_09 //axelchen modified for cancel ircmd_setup in playback MIDI 2004/10/22 
        if(gIsMidiSelMenu)  return;
#else
         if (gIsMidiSelMenu)
        {
//            if (((bMidiPlayerBoolean)&&(midiState == MIDI_STATE_PAYLOAD)))
//                Midi_pause_flag =1;
            run_pause(0);
        }    
#endif
    #endif

#ifdef IRCMD_DBG
    printf("=================ircmd_setup==================\n");
#endif

#ifdef NEW_STYLE_SETUP
    if ( Is_JPEG_SlideMode()
    #ifdef SUPPORT_FILE_SYSTEM_MODE
    ||(IsOtherStatePlayMode()) 
    #endif
    ) 
    {
        invalid_key();
        return;
    }
#endif    

#if !defined(SPHE1000)
    if ( (cd_type_loaded==CDROM) && (Mp3ReadFinish==0) ) { //Jeff 20020614
#else
	if((cd_type_loaded==CDROM)&&(Mp3ReadFinish==0) && (system_state!=SYSTEM_FILESTREAM)&&(system_state!=SYSTEM_TS)) { //MIKEY 2004.06.25 for setup
#endif
        invalid_key();
        return;
    }
    #ifdef KARAOKE_MENU
    //modefied by wangfeng 2003-10-31 11:30
    if((full_scrn&SETUP)&&(KARAOKE_MENU_FLAG==0) || (full_scrn&CUSTM)) //////////////////////////jhuang
    #else
    if((full_scrn&SETUP) || (full_scrn&CUSTM)) //////////////////////////jhuang
    #endif 
	{//aa begin
	#if (defined(SOFT_MENU)&&defined(VIDEOSETUPGUI))//Modifed by ChenZhao on 2004-9-22 11:33  
	if(IsVideoSetupExit_NextVideoSetup())
	#endif
    {
        ExitSetupPage(1);
         #if 0//def SUPPORT_USB//lijd 20041008  //sunzhh modify 2005-3-11 because it results in many bugs and it no use now.
         usb_card_setup_flag=0;
         #endif
//huziqin 2006-4-19 removed
        
#if defined(SDRAM_16Mb_Mode)||defined(NEW_STYLE_SETUP)
        if ( 0)//( cd_type_loaded == CDDA ) && (old_t_disp) )
        {
            t_disp=old_t_disp;
            DispPolling(3);
        }
#endif
        
#ifdef DOUBLE_LOGO
        if(play_state==VCD_STATE_STOP||system_state==SYSTEM_NODISC||system_state==SYSTEM_OPEN)
            ShowTitle();
#endif
    }
	}//aa end
    #ifdef KARAOKE_MENU
    //wangfeng 2003-10-31 11:30 
    else if((full_scrn&SETUP)&&(KARAOKE_MENU_FLAG==1))
        return;
    #endif
    else
    {//enter setup menu
#ifdef AUDIO_SHOW_SAVER //kono  1007 2001
        if( bDisableGUI) return;
#endif

    #ifdef SUPPORT_FUNCTION_MENU
    if(full_scrn&SETUP_PLUS)
      ExitSetupPage(0);
    #endif
 
// 2004/11/26 yltseng
#ifdef NEW_STYLE_SETUP
        if( !SetupSettingForNewStyleSetup() )
            return;
#else//Not NEW_STYLE_SETUP
        if( !SetupSettingForNormal() )
            return;
#endif //end NEW_STYLE_SETUP

		#if (defined(SOFT_MENU)&&defined(VIDEOSETUPGUI))//Modifed by ChenZhao on 2004-9-22 11:33  
		if(IsPlayVideo())
			InitVideoSetupGUI();
		else
			init_setup();
		#else//(defined(SOFT_MENU)&&defined(VIDEOSETUPGUI))
        init_setup();
		#endif//(defined(SOFT_MENU)&&defined(VIDEOSETUPGUI))

        //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 9:13
        SetFullscrnCmdFuncPtr( setup_func_up, setup_func_down,  setup_func_left,
                               setup_func_right, setup_func_select);
		
#ifdef NEW_UART_COMMAND
        timeout_vfd=0;
        nCurrentVolMode=VOL_MODE_MAIN;
#endif
    }
    show_normal_after_setup();//wangfeng 2004-2-17 11:27
}

#else   // SETUP_PROGRAM_IN_PLACE_UNDER_16M

#ifdef DEACTIVATE_PSCAN
extern BYTE video_out_type;
extern BYTE Pscan_on;
#endif

void ircmd_setup(void)
{

#ifdef IRCMD_DBG
    printf("=================ircmd_setup==================\n");
#endif
#ifdef MP4_INIT_STATE_INVALID_KEY//shenyj add for alco 2006/01/04
    if(MP4_init_state==1)
    return;
#endif

#ifdef ALCO_DIVX_UI//shenyj add for alco 12/12
    if(system_state==SYSTEM_SETUP_BROWSER)
    {
        invalid_key();
	    return; 
    }
#endif  

#ifdef MODIFY_FOR_DISPLAY_DBG//shenyj add for alco 1108
    if(play_state==VCD_STATE_STOP)
    {   
        disp_mode=0;
        polling_clock=0;
        remain = 0; 
        t_disp = 0; 
        display_flag = 0;
        display_and_time=0;
    }
#endif

#ifdef DEACTIVATE_PSCAN
  if(video_out_type==4)
  	{
  	    Pscan_on=1;
  	}
#endif

#ifdef OP_PLAYMODE 
    if(full_scrn==PROGRAM)
    {
 	    //invalid_key();
	    return;
    }
#endif

    //joshua, 20060822, setup-key is invalid during decoding or in jpeg slideshow mode.
/*    if(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)  ////lyc mark it,2006-9-14
    {
        if(jpg_is_decoding_process()||Is_JPEG_SlideMode())
    	{
    	    invalid_key();
    	    return;
        }
	}    
*/	
#ifdef  AUTO_ADJUST_TV_TYPE    
    Adjust_TV_type=0;      
#endif
     
#ifdef CONTINUOUS_NUM_KEY_SELECT
    if(ir_num_timer)
        return;
#endif

#ifdef ALCO_8200P_MULTIKEY
    #ifdef NEED_DIFF_IR_PANEL_KEY
    if((play_state==VCD_STATE_NORMAL) || (adv_search_time)
       ||((play_state==VCD_STATE_MP3_FILELIST)&&Is_MP3_STATE()) || (play_state==VCD_STATE_PAUSE))
    #else
    if((play_state==VCD_STATE_NORMAL) || (play_state==VCD_STATE_PAUSE))
    #endif
    {
        ircmd_repeat_all();
        return;
    }
#endif

    
#ifdef SUPPORT_MIDI_MENU_SEL
    #if 1//ndef QISHENG_DEBUG_04_10_09 //axelchen modified for cancel ircmd_setup in playback MIDI 2004/10/22 
        if(gIsMidiSelMenu)  return;
    #else
        if (gIsMidiSelMenu)
        {
//            if (((bMidiPlayerBoolean)&&(midiState == MIDI_STATE_PAYLOAD)))
//                Midi_pause_flag =1;
            run_pause(0);
        }    
    #endif
#endif


#ifdef NEW_STYLE_SETUP
    if ( Is_JPEG_SlideMode()
    #ifdef SUPPORT_FILE_SYSTEM_MODE
    ||(IsOtherStatePlayMode()) 
    #endif
    ) 
    {
        invalid_key();
        return;
    }
#endif    

#if !defined(SPHE1000)
    if ( (cd_type_loaded==CDROM) && (Mp3ReadFinish==0) ) { //Jeff 20020614
#else
	if((cd_type_loaded==CDROM)&&(Mp3ReadFinish==0) && (system_state!=SYSTEM_FILESTREAM)&&(system_state!=SYSTEM_TS)) { //MIKEY 2004.06.25 for setup
#endif
       #ifndef SUPPORT_PMP_SETUP_IN_LOGO
        invalid_key();
        return;
       #endif
    }
    
#ifdef DVB_MENU_SETUP_STYLE //Maoyong 2004-12-21 21:14
    pfnDvbGoto = ircmd_null;
#endif

    #ifdef KARAOKE_MENU
    //modefied by wangfeng 2003-10-31 11:30
    if((full_scrn&SETUP)&&(KARAOKE_MENU_FLAG==0) || (full_scrn&CUSTM)) //////////////////////////jhuang
    #else
    if((full_scrn&SETUP) || (full_scrn&CUSTM) 
    #ifdef DVB_MENU_SETUP_STYLE    //Maoyong 2004-12-21 9:36
    || (full_scrn & DVB_MENU)
    #endif
    ) //////////////////////////jhuang
    #endif 
	{//aa begin
	#if (defined(SOFT_MENU)&&defined(VIDEOSETUPGUI))//Modifed by ChenZhao on 2004-9-22 11:33  
	if(IsVideoSetupExit_NextVideoSetup())
	#endif
    {
		#ifdef GPS_DVD//frank.huang 050801
		extern UINT32 save_srn_start_t;
	    save_srn_start_t = get_rtc_val();
		#endif
		
        #ifdef NEED_DIFF_IR_PANEL_KEY
        panel_key_flag = 0;
        #endif
		
        ExitSetupPage(1);
        #ifdef DVB_MENU_SETUP_STYLE    //Maoyong for Setup key make DVB MENU disappear and normal return from sub menu
        set_dvb_vpp(SCREEN_TYPE_FULL);
        #endif
        
        #if 0//def SUPPORT_USB//lijd 20041008  //sunzhh modify 2005-3-11 because it results in many bugs and it no use now.
        usb_card_setup_flag=0;
        #endif
        
//huziqin 2006-4-19 removed

#if defined(SDRAM_16Mb_Mode)||defined(NEW_STYLE_SETUP)
        if ( old_t_disp)//( cd_type_loaded == CDDA ) && (old_t_disp) )
        {
            t_disp=old_t_disp;
            DispPolling(3);
        }
#endif        

        
//sunzhh moved to setup_tab_ui1_exit.c for exit setup with a display bar 20050707
        
#ifdef DOUBLE_LOGO
        if(play_state==VCD_STATE_STOP||system_state==SYSTEM_NODISC||system_state==SYSTEM_OPEN)
            ShowTitle();
#endif
    }
	}//aa end
    #ifdef KARAOKE_MENU
    //wangfeng 2003-10-31 11:30 
    else if((full_scrn&SETUP)&&(KARAOKE_MENU_FLAG==1))
        return;
    #endif
    else
    {//enter setup menu
        
        
        
        osd_tog_region(0,OSD_OFF);    
            
        t_disp=0;                          // when turning on setup menu, display must be hidden. by robert.chang, 2006-08-11
        extern BYTE    osd0_state;
        osd0_state = 1;
                
#ifdef AUDIO_SHOW_SAVER //kono  1007 2001
        if( bDisableGUI) return;
#endif

        #ifdef SUPPORT_FUNCTION_MENU
        if(full_scrn&SETUP_PLUS)
            ExitSetupPage(0);
        #endif
 
//NOTE:
//In NEW_STYLE_SETUP && SDRAM_16Mb_Mode
//      prog_state = 0 : original state
//                   4 : to excute STOP
//                   2 : excute setup
//                   5 : At level 1,use "SELECT" to enter level 2 /3 
//                   6 : when SETUP interrupt PROGRAM or PROGRAM interrupt SETUP use this flag
//                       not excute ircmd_resume().
// zhaoyanhua note 2003-8-7 9:50               
#ifdef NEW_STYLE_SETUP
    #ifdef SDRAM_16Mb_Mode  //zhaoyanhua add 2003-8-7 9:48                
    
        if (play_state!=VCD_STATE_STOP)
        {
            if (prog_state==0)
            {
                old_t_disp=t_disp;
                old_play_state=play_state;
                if( (play_state==VCD_STATE_STOP)||
                    (system_state==SYSTEM_NODISC)
                    ||Is_JPEG_STATE()
                    #ifdef SUPPORT_FILE_SYSTEM_MODE // nono 2003-8-7 13:55
                    ||Is_OTHER_STATE()
                    #endif
                    ||(system_state==SYSTEM_OPEN) )
                {
                    prog_state = 5;
                    ShowTitle();
                }else if( (pe_run==1)||(still_timer) )//terry 20030805
                {//terry,2003/8/4 10:27PM                   
                    prog_state=4;
                    printf("setup menu,run stop cmd\n");
                    old_t_disp=t_disp;
                    ircmd_stop();
                    return;
                }else
                {//terry,2003/8/4 10:27PM
                    invalid_key();
                    return;
                }
            }
        
        }
        else
        {
            if (prog_state == 0)
            {   
                prog_state = 5; //already STOP ,only show setup_logo.zhaoyanhua 2003-8-7 13:51
                ShowTitle();
                old_t_disp=t_disp;
                old_play_state = VCD_STATE_STOP;
            }
            t_disp=0;
            DispFadeOut();
            //I masked it , but don't know if it will cause error.
            //zhaoyanhua note 2003-8-26 20:05
            regs0->osd_base_addr=OSD_BASE_USE_ADDR;//P_BIDIR_LUMA;
    
        }
   
    
    #else //Not SDRAM_16Mb_Mode     
        if (setup_state==0)
        {  
            old_t_disp=t_disp;
            old_play_state=play_state;
        
            if( (play_state==VCD_STATE_STOP)||
                (system_state==SYSTEM_NODISC)
                ||Is_JPEG_STATE()
                #ifdef SUPPORT_FILE_SYSTEM_MODE // nono 2003-8-7 13:55
                ||Is_OTHER_STATE()
                #endif
                ||(system_state==SYSTEM_OPEN) )
                {
                    setup_state=3;
                    ShowTitle();
                }
                else if( (pe_run==1)||(still_timer) )//terry 20030805
                {//terry,2003/8/4 10:27PM                   
                    setup_state=1;
                    printf("setup menu,run stop cmd\n");
                    old_t_disp=t_disp;
                    ircmd_stop();
                    return;
                }else
                {//terry,2003/8/4 10:27PM
                    invalid_key();
                    return;
                }
          }
    #endif //SDRAM_16Mb_Mode
#else//Not NEW_STYLE_SETUP
        
    #ifdef SDRAM_16Mb_Mode
        #ifndef ALCO_DVD_UI
        if( ( cd_type_loaded == CDDVD ) || ( system_state != SYSTEM_STOP ) )   // 2004/09/30 yltseng, play jpeg, toggle setup fastly
        {
            if ( play_state!=VCD_STATE_STOP && play_state!=VCD_STATE_IDLE && play_state!=VCD_STATE_OPEN )
            {
                if (prog_state==0)
                {
                    prog_state=4;
                    old_t_disp=t_disp;
                        ircmd_stop();
                }
                else
                    invalid_key();
                    
                return;
            }
        }
        #endif //#ifndef ALCO_DVD_UI
/*        
        if ( play_state!=VCD_STATE_STOP && play_state!=VCD_STATE_IDLE && play_state!=VCD_STATE_OPEN )
        {
            if (prog_state==0)
            {
                prog_state=4;
                old_t_disp=t_disp;

                ircmd_stop();
                return;
            }
        }else if( (cd_type_loaded!=CDDVD)&&(system_state==SYSTEM_BROWSE) )        
        {//terry,play jpeg, toggle setup fastly 2004/2/9 03:51PM
           invalid_key();
           return;
        }
*/        
#ifdef ALCO_DVD_UI
        old_t_disp=t_disp;
        t_disp=0;
        DispFadeOut();
#endif

#ifdef PASSWORD       
        osd_tog_region(REGION1, OSD_OFF);
        RegionOnOff[REGION1][1] = 0;
        RegionOnOff[REGION1][2] = STR_OS_SPACE;
        RegionValStr[REGION1][0] = 0;   //kevinmonkey 050720 clear message so it won't appear again permanently after exit setup
#endif      
        regs0->osd_base_addr=OSD_BASE_USE_ADDR;//P_BIDIR_LUMA;
#else    //#ifdef SDRAM_16Mb_Mode
        #if !defined(SETUP_PLAY_CTRL)&&!defined(SETUP_DONT_PAUSE)       //wangfeng,2003-08-30 10:28        
//huziqin 2006-4-19 removed
            #ifdef  JPEG_PAUSE_WHEN_SETUP       // fengjl add 3-11-30 15:47
            if((Is_JPEG_SlideMode())&&(play_state == VCD_STATE_NORMAL))
            {  
                run_pause(0); 
                // if(Is_JPEG_SlideMode())
                old_play_state = VCD_STATE_NORMAL; 
            }
            else
            #endif //end JPEG_PAUSE_WHEN_SETUP 
            #ifndef DVB_MENU_SETUP_STYLE   // 2004/12/27 yltseng modify layout
            //Jack enhanced 05/11/10,otherwise when playing other disc except CDROM,system can't go into pause state forever.
            if(!((cd_type_loaded == CDROM)&&(play_state==VCD_STATE_MP3_FILELIST))) //zhongshan modified to fix cannot play play jpeg or mpeg file after use "setup" in GUI 2005-10-10 20:18
            	run_pause_setting();
            #else
            {
                if(system_state != SYSTEM_TS)
                    run_pause_setting();
            }
		    #endif	//#ifndef DVB_MENU_SETUP_STYLE
		#endif 	//#if !defined(SETUP_PLAY_CTRL)&&!defined(SETUP_DONT_PAUSE)
    #endif//SDRAM_16Mb_Mode
#endif //end NEW_STYLE_SETUP
        // force loading setup module
        //LoadModual(MODUAL_AP2);

		#if (defined(SOFT_MENU)&&defined(VIDEOSETUPGUI))//Modifed by ChenZhao on 2004-9-22 11:33  
		if(IsPlayVideo())
			InitVideoSetupGUI();
		else
			init_setup();
		#else//(defined(SOFT_MENU)&&defined(VIDEOSETUPGUI))
        init_setup();
		#endif//(defined(SOFT_MENU)&&defined(VIDEOSETUPGUI))

        //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 9:13
        SetFullscrnCmdFuncPtr( setup_func_up, setup_func_down,  setup_func_left,
                               setup_func_right, setup_func_select);

#if defined(ALCO_DVD_UI)&&defined(DVD_SETUP_REENG)
        setup_func_down();
#elif defined(ALCO_PORTABLE_SETUP_MENU)
        setup_func_right();
#endif
		
#ifdef NEW_UART_COMMAND
        timeout_vfd=0;
        nCurrentVolMode=VOL_MODE_MAIN;
#endif
    }
    show_normal_after_setup();//wangfeng 2004-2-17 11:27
}

#endif  // SETUP_PROGRAM_IN_PLACE_UNDER_16M

#ifdef SUPPORT_FUNCTION_MENU
void ircmd_setup_plus(void)
{
  if(full_scrn&SETUP_PLUS)
  {
    #ifdef DEBUG_FUNCTION_MENU
    printf("exit setup plus\n");
    #endif
    setup_menu_plus_timer = 0;
    
    ExitSetupPage(0);
  }
  else
  {
    #ifdef DEBUG_FUNCTION_MENU
    printf("enter setup plus\n");
    #endif
    setup_menu_plus_timer = MENU_PLUS_SHOW_TIME;

    init_setup_plus();
        
         //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 11:38
        SetFullscrnCmdFuncPtr( setup_func_up, setup_func_down,  setup_func_left,
                               setup_func_right, setup_func_select);
  }
}
#endif //end #ifdef SUPPORT_FUNCTION_MENU

