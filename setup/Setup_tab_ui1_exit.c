#include "fsNAV.h"/////////////yangli add for pmp setup,2005-10-11 16:17
extern void wait_v_blank(void); // in vpp+dvd.c
extern BYTE rem_osd_id;//nono 2-7-15 21:34
#ifdef DVB_MENU_SETUP_STYLE            //sunzhh add 2005-3-7
extern UINT8 rem_format_id;
BYTE noShowPlay_flag; 
#endif
extern void set_video_default_offset(void);
extern void startup_vpp_now(void);
extern BYTE GetCurrentFileType(void);

#ifdef SUPPORT_ID3
#include "fs_show.h"
    #ifdef SUPPORT_OSDID3//suqiaoli add 2004-3-26 
    extern void osd_init_OSDID3(void);
    extern void show_id3(void);
    #endif  
    extern UINT16 Is_MP3_STATE(void);

#endif

#ifdef SETUP_CAN_DIRECT_SEL_MENU_LANG
extern void rep_load_the_menu(void);
#endif

#ifdef SUPPORT_MP4_SUBTITLE
extern void osd_init_OSDSRT(void);
extern int IS_EXT_SUP_ACTIVATED();
#include "fsNav.h"
#endif

#if defined(SDRAM_16Mb_Mode)||defined(NEW_STYLE_SETUP)      //nono add 5-8-24 18:35 For avoid warning MSG.
extern void DispPolling(BYTE bReset);
#endif

#ifdef SPHE1000	
#include "driver/message.h"
extern share_info_t *pDVB;
#endif

#ifdef SUPPORT_FILE_SYSTEM_MODE
extern UINT16	Is_OTHER_STATE(void);
#endif

#ifdef JPEG_PAUSE_WHEN_SETUP
extern UINT16 Is_JPEG_SlideMode(void);
#endif

#include "setup_VA.h"

void ExitSetupPage(BYTE save) //jhuang 2001/5/18 10:30PM
{
#ifdef	GSPS_DVD//frank.huang 050801
	extern UINT32 get_rtc_val(void);
	save_srn_start_t = get_rtc_val();
#endif
#ifdef EASTECH_SETUPMENU
extern BYTE check_show_pscan_wait_time_mode;
	check_show_pscan_wait_time_mode=0;
#endif 
   int play=0;
    //save==1 save and exit setup menu
    //save==-1 NOT save and exit setup menu

//=============================================
//for DVD_SETUP_REENG   //added by JS   //20040728
#ifdef DVD_SETUP_REENG
    printf("setup_tab_ui1   ExitSetupPage\n");
    setup_mDir = SETUP_ENTER;
    setup_GetPos(setup_mDir);
 #ifdef SELECT_MEDIA_IN_SETUPMENU   ///denghg  add  2005-2-4 15:05
    if(system_state != SYSTEM_OPEN)
    change_media_type();
#endif
#endif//#ifdef DVD_SETUP_REENG

//sunzhh moved here
#ifdef DVB_MENU_SETUP_STYLE //sunzhh add 2005-3-31
    if(system_state == SYSTEM_TS)
    {
        DvbPlayCurrProg();
        if(g_iIsDelChannel)
        {
            osd_DrawRegionString(448, 3, "SAVING...", YELLOW_CLR, TRANS_CLR, DVBMENU_REGION);
            old_play_state = VCD_STATE_NORMAL;
            run_pause(0);
            DvbSaveProgInfo();
            g_iIsDelChannel = 0;
            if((CurrService ==DIGITAL_TV_SERVICE)&&(g_iTVCount==0))//added by fox 05/04/28
            {
                osd_init();
                set_dvb_vpp(SCREEN_TYPE_FULL);
                ShowTitle();
            }

            noShowPlay_flag = 1;  
        }
    }
#endif

//=============================================

    //In CUSTM page, we set UserSet.parental_ststus=C_UNLOCK, so we resync UserSet.parental_ststus here
    //if (setup_sel[0][1] == (MIN_ITEM_SEL+1) ) {
    
    //joshua, 2005.0613, lock is always locked when exiting setup menu.
    #if defined(DVD_SETUP_REENG)&&!defined(DEFAULT_UNLOCK)
#ifndef PARENT_PWD_DEFAULT_NULL //libing 2005-7-1 17:51
    UserSet.parental_ststus = C_LOCK ;
    setup_VA[SETUP_VA_PASSWORD] = MIN_ITEM_SEL;
    run_save_sel_cmd(setup_VA[SETUP_VA_PASSWORD], SETUP_VA_PASSWORD); // 2005/06/18 terry
#else
    UINT16 P, I;
    P=setup_getItemPos(STR_OS_PASSWORD);
    I=P&0xff;
    P=P>>8;
    if (setup_VA[SETUP_VA_PASSWORD] == (MIN_ITEM_SEL+1) ) {
        UserSet.parental_ststus=C_UNLOCK;
    } else {
        UserSet.parental_ststus=C_LOCK;
        setup_VA[SETUP_VA_PASSWORD]=MIN_ITEM_SEL;
    }
#endif  //end of PARENT_PWD_DEFAULT_NULL
/*    if (SETUP_PASSWORD == (MIN_ITEM_SEL+1) ) {
        UserSet.parental_ststus=C_UNLOCK;
    } else {
        UserSet.parental_ststus=C_LOCK;
        SETUP_PASSWORD=MIN_ITEM_SEL;
    }
*/
#endif  //end of DVD_SETUP_REENG

#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-16 9:58
        //if in PASSWORD GUI state,must set it to NO_GUI_STATE
        passwdGUI_state = NO_GUI_STATE;
#endif  
    safe_srn_forceOFF();
    safe_srn_off();
    osd_disable();

//#ifndef QISHENG_DVD // alan marked, 3-8-9 0:10
    if( (old_play_state==VCD_STATE_NORMAL)&&(play_state==VCD_STATE_PAUSE) )
    {
        play|=0x01;
    }
//#endif

#if 1//def FIX_VIDEO_RATIO_ISSUE//nono 20040518
#ifndef SUPPORT_ALL_VIDEO_CHANGE_ASPECT_RATIO	//linrc 2005-10-10 14:43 for can video call change Aspect ratio (4:3->16:9)
    if( (NP_P_CFG_for_Video&0x0300) != (UserSet.P_V_CFG&0x0300) )
#endif
#else
    if(NP_P_CFG_for_Video != UserSet.P_V_CFG)
#endif
    {
#ifndef SPHE1000
#ifndef SUPPORT_ALL_VIDEO_CHANGE_ASPECT_RATIO	//linrc 2005-10-10 14:43 for all video can change Aspect ratio (4:3->16:9)
        if(cd_type_loaded==CDDVD)
#endif
#endif
        {
            set_video_default_offset();//nono 4-9-3 16:07 for ZOOM4 16:9->4:3LB, picture x size error.
            startup_vpp_now();//nono add 2004-7-31 15:59 for ZOOM4 16:9->4:3LB, picture x size error.
            set_video_aspect();
            play|=is_aspect_menu();
        }
    }

    if(save==1) {
        setup_save_exit();//run_save_cmd();
        #ifdef AFTER_RECORD_DELAY
        if(cd_type_loaded == CDDVD)
            need_record = AFTER_RECORD_DELAY_CNT;
        #endif
    }

    #ifdef SDRAM_16Mb_Mode
        if (prog_state==2)
        {
            #include "memmap0.h"

            regs0->osd_base_addr=GetOSDBackUpAddress();
            osd_init();

//nono 20031202
            full_scrn=0;

            ClearOsdMsg(0);
            psprintf(RegionValStr[REGION1], "");
            PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
    
            if ((cd_type_loaded == CDROM) && (pFsJpeg->gifsFuncBtn == 2))
            {
                prog_state=255;
                ircmd_post_func(CMD_FUNC | CMD_FUNC_PLAY);
            } else {
                prog_state=0;
                ircmd_resume();
            }

//            full_scrn=0;

//            ClearOsdMsg(0);
//            psprintf(RegionValStr[REGION1], "");
//            PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
            return;
        }
    #endif

    //Terry,2002/4/29 01:16AM
    //Note: Don't revise the seq. .
    full_scrn=0;
    //terry,2002/5/10 02:52¤U¤È
    //move to osd1.c
    //ClearOsdMsg(0);
    //wait_v_blank();

#ifdef CD_PLAYER        //liweihua add 2003-9-11  //   //sunzhh moved  for exit setup with a display bar 20050707
    if(cd_type_loaded == CDDA)
        osd_init_cdplayer();
    else
        osd_init();
#else       
    #ifdef DYNAMIC_SPECTRUM    //fengjl  3-10-21 21:33
    if (band_onoff)         
    {   
    #ifdef LPCM_NO_SHOW_BAND  //fengjl edit 2004-03-19 18:51  
        if(coding_mode_now!=AUDIF_CODING_MODE_LPCM)  
    #endif
        bEqDisplay=1;
        Show3dspectrum();
    }
    else
    #endif 
    osd_init();
#endif

#ifdef SETUP_PROGRAM_IN_PLACE_UNDER_16M
    #ifdef SDRAM_16Mb_Mode
        // 2005/01/14 yltseng
        extern UINT8   g_uiOSDStatus;
        g_uiOSDStatus = OSD_FULL_SCREEN_STATUS_NONE;
        regs0->osd_base_addr=GetOSDBackUpAddress();
    #endif
#else   // SETUP_PROGRAM_IN_PLACE_UNDER_16M

    #if defined(SDRAM_16Mb_Mode)||defined(NEW_STYLE_SETUP)||defined(MUSTEK_PORTABLE_DVD)      //sunzhh moved from ircmd_setup.c for exit setup with a display bar 20050707
        if ( old_t_disp)//( cd_type_loaded == CDDA ) && (old_t_disp) )
        {
            t_disp=old_t_disp;
            #ifdef MUSTEK_PORTABLE_DVD
            DispPolling(2);
            #else
            DispPolling(3);
    #endif
        }
    #endif

    #ifdef SDRAM_16Mb_Mode
        regs0->osd_base_addr=GetOSDBackUpAddress();
        osd_init();      //sunzhh add for no display after set pscan 20050802        
    #endif
#endif  // SETUP_PROGRAM_IN_PLACE_UNDER_16M

#ifdef EASTECH_DVD_DP2070_D
    if(ShowingWarningMessage)//huhu, 20050720 kevinmonkey
    {
        printf_w("\n\n\nyouyouyou\n\n\n");
        regs0->osd_base_addr=GetOSDBackUpAddress();
        osd_init();
    }
#endif    

    #ifdef SUPPORT_DISPLAY_MENU
    Clear_Display_Menu_Flag();
    if(In_Goto_Menu())
      exit_goto_edit_state();
    #endif//end #ifdef SUPPORT_DISPLAY_MENU 
    
/*    //sunzhh move up 20050707
#ifdef CD_PLAYER        //liweihua add 2003-9-11
    if(cd_type_loaded == CDDA)
        osd_init_cdplayer();
    else
        osd_init();
#else       
    #ifdef DYNAMIC_SPECTRUM    //fengjl  3-10-21 21:33
    if (band_onoff)         
    {   
    #ifdef LPCM_NO_SHOW_BAND  //fengjl edit 2004-03-19 18:51  
        if(coding_mode_now!=AUDIF_CODING_MODE_LPCM)  
    #endif
        bEqDisplay=1;
        Show3dspectrum();
    }
    else
    #endif 
    osd_init();
#endif
*/
#ifdef SHOW_STANDBY_TIMER
        reset_standby_timer_pos();//suqiaoli  add 2003-8-5
#endif

    if(play&0x01)
    {   
#ifdef JPEG_PAUSE_WHEN_SETUP//zhaoyanhua add 2003-12-2 16:30
        if(Is_JPEG_SlideMode())
        {
            play_state = VCD_STATE_NORMAL;      

            OSD1000ISP_STATUS(OSDISP_PLAY, OSDIR_GLOBAL);

            // 2004/12/27 yltseng
            PrintOsdMsg(STR_OS_SEQUENCE,REGION1,1,0);   //Maoyong 2004.06.30 avoid always show "PAUSE"
        }
        else
#endif
        {
#ifdef EASTWIN_PORTABLE_DVD
        	if((play_state==VCD_STATE_MP3_FILELIST)&&( GetCurrentFileType() == CDROM_MP4))
	            ;//tulijuan040923 when divx pre_stop,setup exit,press play/pause can play.
	        else if(!Is_JPEG_PLAY_STATE())
#endif

#ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU    //linrc add 2004-11-4 15:39
                resumeMSF = 0;      //if resumeMSF!=0 ,when setup->play would resume again.
#endif        
#ifdef DVB_MENU_SETUP_STYLE //sunzhh add 2005-3-31
            if(system_state == SYSTEM_TS)
            {        
                //int i;
                //for(i=0;i<2;i++)
               	//	memset( (BYTE *) (SDRAM_BASE + DEMUX_VIDEO_START * 1024), 0, (DEMUX_VIDEO_SZ + DEMUX_AUDIO_SZ) * 1024);
               	AVD_SetMediaTimeout();
   		    //    flush_cdif();
            //    restart_video_engine();
            //   	restart_audio_engine();    
            }
#endif            
 
            ircmd_play();

#ifdef DVB_MENU_SETUP_STYLE //sunzhh add 2005-3-31
            if(system_state == SYSTEM_TS)
            {        
                ClearOsdMsg(0);
//                old_play_state = VCD_STATE_PAUSE;
            }
#endif  

        }
    }
    #ifdef SUPPORT_FUNCTION_MENU
    else if(!setup_menu_plus_timer)
    #else
    else
    #endif
    {
    
    #ifdef MP3_STOP_IN_GUI_START//zhaoyanhua add 03-10-14 11:39 keep inital state for MP3
        if((Is_MP3_STATE()) && (old_play_state == VCD_STATE_MP3_FILELIST))
        {
            play_state = old_play_state;
            return ;
        }
        else
    #elif defined(MP4_GUI_FF_INVALID)  //wsf 2004-9-15 20:22
        if((Is_OTHER_STATE()) && (old_play_state == VCD_STATE_MP3_FILELIST))
        {
            play_state = old_play_state;
            return ;
        }
        else
    #elif defined(DIVX_DRM) && !defined(DIVX_DRM_AES_ONLY)
    //kevinmonkey 051103 fix drm vod message don't show after setup menu
        if((Is_OTHER_STATE()) && (old_play_state == VCD_STATE_MP3_FILELIST))
        {
            play_state = old_play_state;
            return ;
        }
        else    
    #endif
        if ((play_state!=VCD_STATE_STOP)&&(play_state!=VCD_STATE_IDLE))
        #ifdef EASTWIN_PORTABLE_DVD
        {
			if((play_state==VCD_STATE_MP3_FILELIST)&&( GetCurrentFileType() == CDROM_MP4))
	 		 ;//tulijuan040923 when dvix pre_stop,setup exit,press play/pause can play.
	 		 else  if(!Is_JPEG_STATE())
	 	#endif
#ifdef DVB_MENU_SETUP_STYLE            //sunzhh add 2005-3-7
	 	if(rem_osd_id == STR_OS_ZOOM)
	 	    show_zoom(1);
	 	else if(rem_osd_id == STR_OS_TV_SYS)	 	    
            PrintOsdMsg(STR_OS_TV_SYS|(rem_format_id<<OSDSTR_ID_TOTL_BIT),REGION1,1,4);	 	    
	 	else if(rem_osd_id == STR_OS_VOL) 
        #ifdef  VOL_80
            //#ifdef CNTR_5SPK_VOLUME//wangfeng 2003-10-31 21:44
            #ifdef MAIN_VOL_20
            if(volume_Switch==0)
            show_level(Volume_Font_ID, (audio_volume/4), 81);
            else
            #endif
        show_level(Volume_Font_ID, audio_volume, 81);
            //#endif
        #elif defined(VOL_20)  //fengjl add 2004-03-08 21:38
        show_level(Volume_Font_ID,audio_volume,21);
		#elif defined(OSD_BMP_REGION1)
		show_level(Volume_Font_ID,audio_volume,13);
        #else
        show_level(Volume_Font_ID,audio_volume,16);
        #endif	 	
//            show_level(Volume_Font_ID,audio_volume,16);	 	    
	 else if(!noShowPlay_flag)	
#endif         		 
            PrintOsdMsg(rem_osd_id,REGION1,1,0);//show "PAUSE" & "STEP"...after "setup" 2-7-15 21:44

		#ifdef EASTWIN_PORTABLE_DVD
		}
		#endif	
//I think it will not excute correctly.
            //zhaoyanhua add 2003-12-10 12:17
            //PrintOsdMsg(rem_osd_id,REGION1,0,0);//PrintOsdMsg(rem_osd_id,REGION1,1,0);//show "PAUSE" & "STEP"...after "setup" 2-7-15 21:44
           //if(old_play_state == VCD_STATE_PAUSE)//zhaoyanhua add 2003-12-10 13:26
           //     PrintOsdMsg(STR_OS_PAUSE,REGION1,0,0); 

    }

//initializing infomation displaying OSD
#ifdef SUPPORT_MP4_SUBTITLE
    if(IS_EXT_SUP_ACTIVATED())
        osd_init_OSDSRT();
    else
#endif
{
#ifdef SUPPORT_OSDID3
    if(Is_MP3_STATE())
    {
        osd_init_OSDID3();
        show_id3();
    }
#endif 
}

    #ifdef SUPPORT_CD_TEXT//LIZHX ADD 2004,8,19
        if(cd_type_loaded == CDDA)
        {
            osd_init_CDText();
            show_CDText( v11_trk_now );
        }
    #endif
    if(play&0x02) {
        rep_run_the_menu();
    }

#ifdef QISHENG_DEBUG_04_10_09
    if (gIsMidiSelMenu)
    {
        osd_midi_init();
        ircmd_stop();
    }
#endif

#ifdef SETUP_CAN_DIRECT_SEL_MENU_LANG    //terry,2004/9/20 09:59PM
    rep_load_the_menu();
#endif
    
    #ifdef USER_MPEG_LOGO
    if (
           (need_show_logo==1) &&
           (
               (play_state==VCD_STATE_STOP) || (play_state==VCD_STATE_OPEN) || (system_state==SYSTEM_NODISC)
           )
       )    // alan, 2003/9/8 06:02¤U¤È
    {
        ShowTitle();
        need_show_logo=0;
    }
    #endif//#ifdef USER_MPEG_LOGO
    
    #ifdef ALWAYS_DISPLAY_OPEN                   //fengjl  add 3-12-1 20:20
    
    
    #ifdef SETUP_ON_OPEN_VALID          //dingzhy 12/26/2003 9:05PM
    extern BYTE OpenFlag;
    if ((system_state==SYSTEM_OPEN)&&(OpenFlag == 1))
    {
        OSD1000ISP_STATUS(OSDISP_OC_OPEN, OSDIR_OPEN);

        PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);//1
    }
/// 
    else
    if((play_state !=VCD_STATE_NORMAL)&&(!Is_JPEG_STATE())&&(dvd_error==0)
    &&(play_state != VCD_STATE_FASTFORWARD)&&(play_state !=  VCD_STATE_FASTBACKWARD)&&(play_state != VCD_STATE_STOP))
    {
        OSD1000ISP_STATUS(OSDISP_READ, OSDIR_GLOBAL);

        PrintOsdMsg(STR_OS_READ,REGION1,0,0);//1
    }
///
    #else
    if (system_state==SYSTEM_OPEN)
    {
        OSD1000ISP_STATUS(OSDISP_OC_OPEN, OSDIR_OPEN);

        PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);
    }
    #endif
    
#endif
    
    #ifdef NODISC_SHOW_IN_DIFF_REGION//shenyj add for alco 177w
    extern void nodisc_osd_init(void);//for warning
    if(system_state == SYSTEM_NODISC)
      nodisc_osd_init();   
    #endif 
    
    #ifdef ALWAYS_DISPLAY_NODISK
    if (system_state==SYSTEM_NODISC)
    {
        OSD1000ISP_STATUS(OSDISP_NODISC, OSDIR_GLOBAL);
        #ifdef ALCO_DVD_UI//shenyj add for alco177w 0509
        if(read_disc_state == 0x0f)
            PrintOsdMsg(STR_OS_ERR_DISC,REGION1,0,0);          
        else 
        #endif
        PrintOsdMsg(STR_OS_NODISC,REGION1,0,0);
    }
    #endif
        
#ifdef SETUP_DONGLI459
UserSet.parental_ststus=C_LOCK;
#endif
#ifdef SDRAM_16Mb_Mode
prog_state=0;    //sunzhh add for pressing "setup" not show setupmenu but show "stop" 2004/10/21
#endif
/*2005-03-31 sunzhh move up
#ifdef DVB_MENU_SETUP_STYLE //Maoyong rewrite it, 2004-12-24 14:11 ??? when playing program, will cause stop problem
    if(system_state == SYSTEM_TS)
      {
        DvbPlayCurrProg();
        if(g_iIsDelChannel)
            {
                DvbSaveProgInfo();
                g_iIsDelChannel = 0;
            }
      }
#endif
*/
#ifdef OSD_DYNAMIC_ONOFF 
{
	//printf("*****Out Setup Menu!!!\n");
	pDVB->tv_format = tv_format;
	pDVB->tv_out_id = tv_out_id;
	pDVB->osd_font_mode = osd_font_mode;
	pDVB->menu_on = 0;
	//printf("*****osd_font_mode = %d\n", osd_font_mode);
	//printf("*****tv_format = %d\n", tv_format);
	//printf("*****tv_out_id = %d\n", tv_out_id);
}	
#endif
#ifdef ORITRON_TRAY_PASSWORD//libing 2005-5-13 16:01 for op bug
setup_pos[SETUP_ML0]=0;
#endif

#ifdef SUPPORT_PMP_SETUP_IN_LOGO	/////////////YANGLI mod for logo goto setup  2005/9/14	 
osd_init_show_setup_pmp();
if((pFsJpeg->gifsState == FS_STATE_JPEG)||////////////////yangli mod for setup bug ,2005-10-11 16:17
   (pFsJpeg->gifsState == FS_STATE_MP3)||
   (pFsJpeg->gifsState == FS_STATE_OTHER))
{
PrintOsdMsg(rem_osd_id,REGION1,1,0);
}
else 
{   
    psprintf(RegionValStr[REGION1], "");
    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
}
#endif///////////////end pmp_ui


}

