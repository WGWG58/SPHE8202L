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
|  File Name   :  ircmd_audio.c
|
|  Description :  realize audio language function in IR audio language key.
|
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2004/1/14        Terry         Creating
|--------------------------------------------------------------------------------*/

#define is_dvd()    (cd_type_loaded == CDDVD)//move from ircmd_3dsound.c 2004-4-10 17:24

//wangap add for downmix off volume 2004/3/3
#ifndef AC3_BASS_MANAGEMENT
extern  BYTE    cspk_volume;
extern  BYTE    fspk_volume;
extern  BYTE    sspk_volume;
extern  int    downmix_off;
#endif

//Maoyong add 2004.02.14 must be same with the one in disp.c
#define		MAX_ENG_WORDS   3		
static inline void set_audio_pl2(void)
{
#ifdef  AUDIO_2CH_5_1CH//zhaoyanhua add 03-11-3 15:07
  #ifdef SUPPORT_PROLOGIC_II //axel 2004/1/28 10:39 
    if(pDSV->dNs_Audio_ch!=5)//when 2channle auido,must open PROLOGIC II
    {
        if(ChannelFlag == AUDIO_5_1CH)
           AudioSetPrologic_IIOutput();
    }
    else
  #endif //SUPPORT_PROLOGIC_II
    {
         //when 5.1channelaudio, current output mode is PROLOGIC II
         // must change to 5.1ch.
  #ifdef SUPPORT_PROLOGIC_II  //axel 2004/1/28 10:39
        if((ChannelFlag == AUDIO_5_1CH)&&(setup_GetPrologicII() != 4))
  #else
        if(ChannelFlag == AUDIO_5_1CH)
  #endif  //SUPPORT_PROLOGIC_II
           AudioSet5_1chOutput();	
    }
#endif    
}
/**************************************************************************
 *  Function Name: only_audio_mute                           
 *  Purposes:                                                             
 *       audio mute when enter one playing.                          
 *  Descriptions:                                                         
 *       mute audio when FF switch to play and play switch to FF.
 *  Arguments:                                                            
 *       audioNotContinuous:>0:audio is not continuous.                        
 *       for example, audioNotContinuous=5:mute 50ms.
 *       
 *  Returns:     NONE
 *  See also:    NONE                                                          
 *    
 **************************************************************************/

void only_audio_mute(void)
{
    if ( ( (cd_type_loaded==CDDA) || (cd_type_loaded==CDROM) ) && 
          (adv_search_time<=2) && (adv_search_time>=-2) )
    { //Jeff 20020918
        audioNotContinuous=5; //to do extra mute(50ms) when enter one playing, Jeff 20020910
    }
}
    
/*
* Terry,2004/1/13 11:58AM
* mute = 1 : mute
* mute = 2 : demute
* other    : abort
*/
#if 0 
void audio_codec_chg_mute(int mute)
{     	
    if(mute==1)	
    {
      if (!user_mute) 
      {
         audioNotContinuous=5;
         AudioSetVolume(0);
         #ifdef CHANGE_DSP_SPDIF_OFF
	   AudioSetSPDIF(0); //S-PDIF off mode command to DSP(0:off)
	   delay_srv_10ms(5);
         #endif//CHANGE_DSP_SPDIF_OFF
      }
    }else if(mute==2)
    { 

       //to unmute immediatelly when no audio-language could be selected.
       //Because valid selection is (determined and set) in deep (Audio_stream_Chg-Select_ASTN),
       //we undo former mute work here.       
       #ifdef CHANGE_DSP_SPDIF_OFF //nono 2003-12-23 20:14
        setup_SetSPDIFConfig();      
        AudioSetPause();
        AudioSetPlay();
       #endif//#ifdef CHANGE_DSP_SPDIF_OFF	
       audioNotContinuous=0;
       AudioDemute();
    }
}
#endif


#ifdef SUPPORT_MP4
void set_audio_language_Ns(UINT8 Ns)
{
    //pDSV->dAv_AST_Ns = Ns-1;
    pDSV->dAv_AST_Ns = Ns;//nono 4-8-25 15:49
}
#endif

//terry,2004/4/8 05:38PM
#define is_svcd() (cd_type_loaded==CDSVCD)
#ifdef SUPPORT_MP4
#define is_mp4()  (GetCurrentFileType()==CDROM_MP4)
#else
#define is_mp4()  (0)
#endif

#ifdef CHANNEL_SVCD_VALID//EASTECH
#define is_channel() ( (!is_dvd())&&(!is_mp4()) )   //(!is_svcd())&&  Modified by Tom
#else
#define is_channel() ( (!is_svcd())&&(!is_dvd())&&(!is_mp4()) )
#endif

#define is_language() ( is_svcd()||is_mp4() )

/*
*  Terry,2004/1/13 11:46AM
*/
/**************************************************************************
 *  Function Name: ircmd_audio_language                           
 *  Purposes:                                                             
 *      realize audio language function using IR language key,
 *      switch different audio track for dvd .                          
 *  Descriptions:                                                         
 *   
 *  Arguments:                                                            
 *     id: audio stream.
 *     Audio_stream_Chg: Ouput: 0~7:audio stream id  0xf:fail
 *                       The operation to set the stream number of
                         the audio and to change SPRM.
 *  Returns:     NONE
 *  See also:    NONE                                                          
 *    
 **************************************************************************/
 #ifdef SUPPORT_LINE_OUT_MUTE
    extern void use_rom_line_out_mute(void);
    extern void use_rom_line_out_demute(void);
#endif

void ircmd_audio_language(void)
{
#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
    UINT16 id = 0;

    //----------------------------------------------------------------
    // Conditions in which we wish to override the whole function
    //----------------------------------------------------------------
    #ifdef AUDIO_KEY_CONTROL_CHANNEL    //libing 2005-4-21 22:00
    if((cd_type_loaded == CDVCD10)||(cd_type_loaded == CDVCD20))//||(cd_type_loaded==CDSVCD))
    {
        ircmd_channel();
        return;
    }
    if( is_channel() )
    {
        #ifdef CHANNEL_CD_MP3_INVALID
        if(Is_MP3_STATE()==1 || Is_JPEG_STATE() )  //add by Tom 
        {
            invalid_key();
            return;
        }
        #endif  //#ifdef CHANNEL_CD_MP3_INVALID
        ircmd_channel();
        return;
    }
    #endif  //#ifdef AUDIO_KEY_CONTROL_CHANNEL

    #ifdef DVB1000_NON_OS //moved from dvb_gui_util.c for supporting multi-APID by liuchuanyi 05/04/18
    if(system_state==SYSTEM_TS)
    {
        dvbAPIDSwitch();
        return;
    }
    #endif  //#ifdef DVB1000_NON_OS

    //-------------------------------------------------------------------------
    // Conditions in which we want to show invalid key or just ignore the key
    //-------------------------------------------------------------------------

    //kevinmonkey 060606 if IR command flows to this place, check stream number. 
    //currently meant for mpeg2 and AVI with subpicture/subtitle or multi audio track
    //if(stream number == -1) invalid key, if(stream number == 1) print stream 1 message.
    if( (pDSV->dAv_AST_Ns == 255) || (pDSV->dAv_AST_Ns == 0))
    {
        invalid_key();
        return;    
    }
    else if(pDSV->dAv_AST_Ns == 1)
    {
        //if we want to show invalid key:
        invalid_key();
        //if we want to show stream 1 OSD message:
        //PrintOsdMsg(STR_OS_AUDIO|(0x20<<OSDSTR_ID_TOTL_BIT),REGION1,1,4);
        return;
    }

    #ifdef SUPPORT_QUICKTIME   //lyc add 2005-12-09,for nero digital only one audio trk
    extern UINT32  uSoundTrackNum;
    if((uSoundTrackNum<=1)&&((IS_FILE_TYPE_QT())||(IS_FILE_TYPE_ND())))
    {
        invalid_key();
        return;
    }
    #endif  //#ifdef SUPPORT_QUICKTIME

    if(bDiscType == CD_OKO) 
    {
        //invalid_key();
        //return;
        id=1;
    }
    else if( is_language() ) //terry,2004/4/8 05:31PM
    {//check SVCD status_ext, to see whether this SVCD disc supports $C1
     //svcd_status_ext : INFO.SVCD(00:04:00) 2037th Byte
     //if(pDSV->dAv_AST_Ns<2)
     //id = 1;      //nono 2-3-11 for yuxing     
        //kevinmonkey move this mute to the moment we really changing the audio channel 
        //since now we not necessary want to change audio even action_click is true.
        //(situation is divx6. Say now we want to change to track 8. Press language only 
        //changes track setting, after switch to 8th track and wait for a few seconds then we 
        //do the change. This behavior avoid reparsing 6 times while switch through track 2~7.
        //if(action_click)//nono 2004-6-2 21:59
        //{
        //    audioNotContinuous=10;//terry,2004/2/25 07:21PM
        //    AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
        //}
    }
    else if(!DVD_check_state())
    {
        id=1;
    }

    #ifdef VOB_SUBTITLE 
    if(GetCurrentFileType()==CDROM_MPG)
        id = 0;
    #endif  //#ifdef VOB_SUBTITLE 

    if(id)
    {
    #ifdef NEWSTYLE_WINDOW
        if(full_scrn&MESSAGE)//xyy 2003-7-30 8:53
            psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_NONE]);
        else
    #endif  //#ifdef NEWSTYLE_WINDOW
        {
            invalid_key();
            return;
        }
    }

    //--------------------------------------------------------------------------------------------
    // Adjusting action_click to determine parameter passing into audio chainging sub-routine. 
    // Basically check conditions enabling action_click first, then those disabling action_click.
    //--------------------------------------------------------------------------------------------
    #if defined(ADJUSTING_ACTION_VALID_RIGHT_NOW)
    action_click = 1; //Jeff 20030506
    #endif  //#if defined(ADJUSTING_ACTION_VALID_RIGHT_NOW)

    #ifdef SUPPORT_DIVX6
    extern UINT32 mp4_aud_channel_flg;
    extern UINT32 is_divx6_file;
    // do not reset action_click before audio track is actually changed
    if ((is_divx6_file == 1) && (mp4_aud_channel_flg == 1))
        action_click = 1;
    #endif  //#ifdef SUPPORT_DIVX6    

    #ifdef NEWSTYLE_WINDOW
    if ( (full_scrn&MESSAGE) && (action_click==2) )	 
        action_click = 0;
    #endif  //#ifdef NEWSTYLE_WINDOW
    #ifdef SUPPORT_LINE_OUT_MUTE    //hongfeng add   
    if(action_click)
        use_rom_line_out_mute();
	#endif 
    
    //-----------------------------------------------------------------------------------
    // Call respective audio stream changing functions (depends on media type currently).
    //-----------------------------------------------------------------------------------
    if(cd_type_loaded == CDDVD)
    {
        id = Audio_stream_Chg(action_click, 1);
    }
    else if(cd_type_loaded == CDSVCD)
    {
        id = Audio_stream_Chg_SVCD(action_click);
    }
    #ifndef SUPPORT_MPG_FILE_PARSER
    else if(GetCurrentFileType() == CDROM_MPG)
    {
        #ifdef VOB_SUBTITLE
        id = Audio_stream_Chg_VOB(action_click);
        #endif  //#ifdef VOB_SUBTITLE
    }
    #endif  //#ifndef SUPPORT_MPG_FILE_PARSER
    #ifdef SUPPORT_MP4  //support mpeg4 or "support file parser framework", such as Nero Digital.
    else if(GetCurrentFileType() == CDROM_MP4)
    {
        #if defined(SUPPORT_MPG_FILE_PARSER)&&defined(VOB_SUBTITLE)
        if(IS_FILE_TYPE_MPG12())
        {
            id = Audio_stream_Chg_VOB(action_click);
        }else
        #endif  //#ifdef SUPPORT_MPG_FILE_PARSER
        {
            id = Audio_stream_Chg_MediaContainerFile(action_click);  //media container file type
        }
    }
    #endif  //#ifdef SUPPORT_MP4

    set_audio_pl2();
    //wangap add for downmix off volume 2004/3/3
    #ifndef AC3_BASS_MANAGEMENT
    if(downmix_off==1)
    {
        AUDIF_Set_FSPKGain(fspk_volume/2);//2004AUDDRV AudioSetFSPKGain(fspk_volume/2);
        AUDIF_Set_CSPKGain(cspk_volume/2);//2004AUDDRV AudioSetCSPKGain(cspk_volume/2);
        AUDIF_Set_SSPKGain(sspk_volume/2);//2004AUDDRV AudioSetSSPKGain(sspk_volume/2);
    }
    #endif  //#ifndef AC3_BASS_MANAGEMENT

#ifdef SUPPORT_LINE_OUT_MUTE    //hongfeng add   
    if(action_click)
        use_rom_line_out_demute();
#endif 

    //------------------
    // Showing message
    //------------------
    if (id!=0xf) 
    {//terry,2003/12/15 02:27PM,for Real time Video Format PAL, Philips 3122-783-01941
        OSD1000ISP_STATUS(((pDSV->dAv_AST_Ns)<<4)|(NP_ASTN+1&0x000f), OSDIR_LANGUAGE);

    #ifdef SUPPORT_DIVX6
        extern UINT32 is_divx6_file;
        extern void divx6_display_audio_track(UINT8	aud_strm_num);
        if (is_divx6_file == 1)
            divx6_display_audio_track(NP_ASTN);
        else
    #endif  //#ifdef SUPPORT_DIVX6
        {
            PrintOsdMsg(STR_OS_AUDIO|(0x20<<OSDSTR_ID_TOTL_BIT),REGION1,1|(((id-min_astn_id)<<8)),4);
        }
        counter_down = 5;//terry,2004/1/13 02:44PM
    }else   //id==0xf
    {
    #ifdef NEWSTYLE_WINDOW
        if(full_scrn&MESSAGE)//xyy 2003-7-30 8:53
        { 
        //when only one audio language,show"1/1" while not NONE
            psprintf(linebuf,"1/1");//zhaoyanhua add 2003-12-8 20:25
        }
        else
    #endif  //#ifdef NEWSTYLE_WINDOW
        {
            invalid_key();
        }
    }

    #ifdef TV_WANT_6500_AUDIO_MUTE//caoh 2006-7-11 02:59ÏÂÎç only for some tv don't mute RAW and DTS audio
       if((cd_type_loaded==CDDVD)&&(pDSV->dAudio_coding_md == 6))
               scaler_6500_main();
    #endif

    #ifdef NEWSTYLE_WINDOW//zhaoyanhua add 2003-12-8 19:55			
    if(full_scrn&MESSAGE)			
    {
    //Maoyong add 2004.02.14 to avoid too long non-chinese language 
        if (!IsOSDChinese()||((linebuf[0]>='A')&&(linebuf[0]<='Z')))	
        {
            linebuf[MAX_ENG_WORDS]='\0';
            psprintf(linebuf+3, "%s", get_audio_mode());
        }
        updateAudioLanguage();
    }
    #endif  //#ifdef NEWSTYLE_WINDOW

    //------------------
    // Terminating
    //------------------
    return;

#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}

//==================== ending =================================================


