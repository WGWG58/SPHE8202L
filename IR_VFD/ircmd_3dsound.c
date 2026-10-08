/*
*  Terry,2004/1/29 06:17PM
*/
//--------------------------------------------------------------------------------------
//#define is_dvd()    (cd_type_loaded == CDDVD)//move to ircmd_audio.c 2004-4-10 17:24
#define is_dvd_downmixoff()   ((cd_type_loaded == CDDVD) &&(setup_IsSpkDownmixOff())) //zxb 2005/09/26
#define is_cdda()   (cd_type_loaded == CDDA)
#define is_dts_cd() (cd_subtype == CD_DTS)
#define is_ppcm()   (coding_mode_now == AUDIF_CODING_MODE_PPCM)
#ifdef SUPPORT_WMA//zhaoyanhua add 03-10-11 17:58 when WMA ,not dot MP3.
#define is_wma()    (GetCurrentFileType()== CDROM_WMA)
#else
#define is_wma()    (0)
#endif
#ifdef SUPPORT_NESGAME
#define is_game()   (Is_GAME_STATE())
#else
#define is_game()   (0)
#endif

#ifdef INVALID_3D_WHEN_DTS			//dingzhy for tonic  2004-2-8 15:54
#define  is_DTS()    ( ( coding_mode_now&(AUDIF_CODING_MODE_DTS|AUDIF_CODING_MODE_DTSCD) )||(cd_subtype==CD_DTS) )
#else
#define  is_DTS()     (0)
#endif

#ifdef INVALID_3D_WHEN_AB	//wangfeng 2004-2-18 22:48
//#define is_repeat() (rep_mode==REPEAT_TRACK||rep_ab_mode==REPEAT_FIND_A||rep_ab_mode==REPEAT_FIND_B)
#define is_repeat() (rep_ab_mode==REPEAT_FIND_B)
#else
#define is_repeat() (0)
#endif
//--------------------------------------------------------------------------------------


#ifdef DISABLE_3D_DUE_TO_PERFORMANCE //Steven add 2006/07/03 for invalid 3D function when use 108MHZ//
	#if defined(REPEAT_AB_TOO_SHORT_DISABLE_3D)
		#define is_disable_3D() (is_dts_cd()||is_wma()||( is_cdda()&&ircmd_repeat_ab_time_is_too_short()))//wangfeng 2004-2-18 15:42)
	#else//REPEAT_AB_TOO_SHORT_DISABLE_3D
		#define is_disable_3D() (is_dts_cd()||is_wma()||is_repeat())
	#endif//REPEAT_AB_TOO_SHORT_DISABLE_3D

#else//#ifdef DISABLE_3D_DUE_TO_PERFORMANCE
#define is_disable_3D() (0)
#endif//#ifdef DISABLE_3D_DUE_TO_PERFORMANCE

#ifdef SUPPORT_REP_READ   //Maoyong add 0812  
#define is_read()  (full_scrn & READ)
#else
#define is_read()   (0)
#endif

#ifdef SUPPORT_PROLOGIC_II
#define is_pl2_on() (setup_GetPrologicII()<=3)
#else
#define is_pl2_on() (0)
#endif

//--------------------------------------------------------------------------------
//terry,2004/2/4 07:04PM
#ifdef SHOW_3D_WHEN_SPDIF //show 3d when spdif by wangfeng,2003-10-21 10:20
#define is_spdif_on() (0)
#else
#define is_spdif_on() ( setup_IsSet2SPDIF_Bitstream()||setup_IsSet2SPDIF_PCM() )
#endif

#define is_5ch_out() (setup_GetDownmixMode()>5)

//Steven add 2006/07/03 for invalid 3D function when use 108MHZ//
#define is_disable_3D_due_to_multi_chn() (((is_dts_cd()||is_dvd())&&(is_5ch_out()||is_spdif_on()))||is_DTS()||(setup_IsSpkDownmixOff()&&(cd_type_loaded==CDDVD))||is_ppcm())

//--------------------------------------------------------------------------------
#ifdef SUPPORT_MULTI_CHANNEL_5_BAND_EQ//Steven add 2006/07/03 for invalid 3D function when use 108MHZ//
    #define is_invalid() \
          (is_disable_3D()||is_game()||is_read()||is_ppcm())
#else
    #define is_invalid() \
          (is_disable_3D()||is_game()||is_read()||is_pl2_on()||is_disable_3D_due_to_multi_chn())
#endif

#ifdef SUPPORT_OGG  //ycwen 2006/9/5 OGG dsp code doesn't implement 3D/EQ at all.
    #define  ogg_disable_3d() (IS_FILE_TYPE_OGG())
#else
    #define  ogg_disable_3d() (0)        
#endif                    

       
//        (is_108mhz()||is_game()||is_read()||is_pl2_on()&&(!is_dsp_performance_ok())||is_ppcm() )//20040203


//-------------------------------------------------------------------------------------

#ifdef SUPPORT_OSDID3//suqiaoli add 2004-3-26 
extern void osd_init_OSDID3(void);
extern void show_id3(void);
#endif

#ifdef SUPPORT_MP4_SUBTITLE  // David 2004-5-12
extern void osd_init_OSDSRT(void);
#endif

#if defined(SUPPORT_DVB_GUI_NEW)&&defined(DVB_IR_3D_ON)
#ifdef SUPPORT_SUBTITLE     //sunzhh 20060326
extern BYTE gSubttDispOn;
extern BYTE gSubttKeyOn;
extern void Subtitle_On(void);
extern int SubtitleON;
extern int gSubttPreStatus;
extern UINT16 uCurSubTNum;
extern UINT16 uPreSubTNum;
extern UINT32 g_CurProgIdx;
void Dvb_StateMachine_Set( DVBGuiState_E NextState );
#endif
#endif
//---------------------------------------------------------------------------------------

//freyman add for sva 2002-10-25 15:34
void  cancel_sound(void)
{
#ifdef SUPPORT_3DSOUND	
    full_scrn=0;
    //bEqDisplay=0;
    setup_eq_display(0);//terry,2003/9/26 04:43PM

    sound_set_EQ_again();//NONO 20040722

#ifdef CD_PLAYER        //liweihua add 2003-9-11
    if(cd_type_loaded == CDDA)
        osd_init_cdplayer();
    else
    //osd_init();
#elif defined(SUPPORT_OSDID3)//liweihua add 2004-1-9 10:26
    if(Is_MP3_STATE())
    {
        osd_init_OSDID3();
        show_id3();
    }
    else
#endif	
#if defined(SUPPORT_DVB_GUI_NEW)&&defined(DVB_IR_3D_ON)
    if(Is_Dvb_State())
    {
        //DVBMenu_Init();//Return2HideMenu();
        osd_init_new_dvb_menu();  //sunzhh mofify  20051118
        osd_tog_region(DVB_MENU_OSD_REGION, OSD_ON);
        #ifdef SUPPORT_SUBTITLE
		if(gSubttPreStatus)  //sunzhh add 20060326
	    {
			uCurSubTNum = uPreSubTNum - 1;
	        //Subtitle_Off();
	        Subtitle_On();
	        uCurSubTNum ++;
	        Dvb_StateMachine_Set(DVB_UISTATE_SUBT);
	    }
		#endif
        printf_w("========osd init_newdvb menu ========\n");
    }
    else      
#endif  
    osd_init();

#ifdef SUPPORT_CD_TEXT//LIZHX ADD 2004,8,19
        if(cd_type_loaded == CDDA)
        {
            osd_init_CDText();
            show_CDText(v11_trk_now);
        }
#endif

#ifdef SUPPORT_MP4_SUBTITLE  // David 2004-5-12
    if(IS_EXT_SUP_ACTIVATED())
        osd_init_OSDSRT();
#endif

#endif//#ifdef SUPPORT_3DSOUND	

}

/*huziqin 2004-2-26 I removed a block here*/

#if defined(SDRAM_16Mb_Mode)|| !defined(SUPPORT_3DSOUND)
#ifdef PANDA_16Mb_Mode_3D_KEY_VALID		//gerry,2004-3-16 0:40
int surround_off=0;
#endif//PANDA_16Mb_Mode_3D_KEY_VALID
void ircmd_3dsound(void)
{
#ifdef PANDA_16Mb_Mode_3D_KEY_VALID		//gerry,2004-3-16 0:36 
	if(surround_off==1) 
		surround_off = 0; 
	else 
		surround_off = 1; 
	if(surround_off==1) 
	{ 
        OSD1000ISP_STATUS(OSDISP_3DON, OSDIR_3D);

		PrintOsdMsg(STR_OS_SURR|(STR_OS_ON<<OSDSTR_ID_TOTL_BIT),REGION1,1,4);
	}
	else
	{
        OSD1000ISP_STATUS(OSDISP_3DOFF, OSDIR_3D);

    	PrintOsdMsg(STR_OS_SURR|(STR_OS_OFF<<OSDSTR_ID_TOTL_BIT),REGION1,1,4);		
	}
#else//PANDA_16Mb_Mode_3D_KEY_VALID
   invalid_key();
#endif//PANDA_16Mb_Mode_3D_KEY_VALID
}
#else

static inline void start_up_3dsound(void)
{
   setup_eq_display(0);//terry,2003/9/26 04:43PM

    sound_set_EQ_again();//nono 20040722
    
   full_scrn = SOUND;
   osd_init_music();
#if defined(SOUND_NO_KEYPAGE)&&defined(VTREK_DVD)
   sound_init_2();
#else   
   sound_init();
#endif   
   ShowSoundPage();
   
   //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 2004-9-24 9:07            
   SetFullscrnCmdFuncPtr(sound_func_up, sound_func_down,  sound_func_left,
                         sound_func_right, sound_func_select);
}

void ircmd_3dsound(void)
{
  printf("================= ircmd_3dsound =================\n");

#if defined(FAT_FILE_MODE) && defined(SPHE8202_FAT_WRITE_API)//liweihua mod 2005-3-15 16:16
    if((fat_play_mode == 1)&&(media_type == MEDIA_CARD))
    {
        ircmd_card_delete();
        return;        
    }
    else if((fat_play_mode != 1)&&(play_state == VCD_STATE_CLOSE))
    {
        invalid_key();
        return;        
    }
#endif

  #ifdef SUPPORT_MIDI_MENU_SEL
  if(gIsMidiSelMenu)  return;
  #endif

#ifndef GBM_3D_KEY_ALL_VALID		//gerry,2004-2-7 15:48
  // invalid function ...............
  if(is_invalid()||ogg_disable_3d())
  {
    invalid_key();
    return;
  }
#endif//GBM_3D_KEY_ALL_VALID
#ifdef DVD_5CHOUT_3D_INVALID //zxb 2005-9-1 14:45
  if( is_dvd_downmixoff() )    
    {
        invalid_key();
        return;
    }
#endif    
  //old dvd 3d function
#ifndef GBM_DVD			//gerry,2004-2-7 15:55
  #ifndef DVD_3D_SHOW_SPECTRUM
  if ( is_dvd()||is_dts_cd() )
  {	
      #ifdef ADJUSTING_ACTION_VALID_RIGHT_NOW
         setup_DVD3DSound(1);
      #else
         setup_DVD3DSound(action_click);
      #endif
      return;
  }
  #endif
#endif//GBM_DVD

    counter_down = 3;  // slow down the speed of switch between 3D sound on and off  
                                 // by delaying the IR key. by robert.chang,2006-09-11
 
  //3d sound function
  if(full_scrn & SOUND)
  {
      cancel_sound();
#if 0//def OSD_BMP_DISPLAY //when display, press 3D to show sound menu in the region4 for cdrom,libing 20041120
      osd_init();//libing2004-11-16 11:30 
#endif
      #ifdef CD_PLAYER        //liweihua 2003-9-3
      if(is_cdda())  osd_init_cdplayer();
      #endif	
//huziqin 2006-4-19 removed

      OSD1000ISP_STATUS(OSDISP_3DOFF, OSDIR_3D);
  }
  else
  {
      start_up_3dsound();
  }
#if 0//def OSD_BMP_DISPLAY //when display, press 3D to show sound menu in the region4 for cdrom,feeling 20041009
	if((cd_type_loaded == CDROM) & t_disp)//libing 2004-11-14 12:43
    {
		DispFadeIn();
	}
#endif			

}
#endif
//--------------------------------------------------------------------------------------------

