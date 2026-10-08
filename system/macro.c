//
// FILE
// macro.c
//
// DESCRIPTION
//
//

#include "config.h"
#include "global.h"
#include "memmap.h"
#include "cd.h"
#include "macro.h"
#include "osd.h"
#include "func.h"
#include "supfunc.h"
#include "dma.h"
#include "vpp.h"
#include "atapi_if.h"
#include "stc.h"
#include "lbaif.h"
#include "util.h"
#include "svcd.h"   //Jeff 20010717
#include "dsp3_if.h" //Jeff 20010827
#include "auddrv.h" //2004AUDDRV oliver 20041011 for using audio driver API purpose
#include "dvdpe.h"
#include "viddec.h"
#include "cdxa.h"
#include "mpegsys.h"
#include "cdfunc.h"
#include "dvdpe.h"
#include "setup.h"
#include "pu8560.h" //alan,2002/5/28 10:07PM
#include "fs96602.h"//#ifdef SUPPORT_FILE_SYSTEM_MODE
#include "fsGUI.h"
#include "fsNAV.h"
#include "srv2.h" //cyue: add streamming play

#include "kinf.h"
#include "sinf.h"
#include "kernel.h"

#include "asf_if.h"
#include "avi_if.h"

#include "audcodec.h"
#include "bit_rate.h"   // 2004/07/26 yltseng
#include "cardfs.h"     //wthsin, 2004/8/5 01:24am

#ifdef  SUPPORT_MP4_SUBTITLE
#include "Subtitle.h"
#endif

#ifndef DVDRELEASE
//#define MACRO_DBG       1
#endif

#ifdef MACRO_DBG
#define MONE_FUNCTION
#define macro_puts(s)       io_write_wait(s)
#endif

#ifdef  MONE_FUNCTION
#define macro_function(s)   do {macro_puts(s); macro_puts("\n");} while (0)
#endif

#ifndef macro_puts
#define macro_puts(s)       ((void)0)
#endif

#ifndef macro_function
#define macro_function(s)   ((void)0)
#endif


//
// standalone debugging
// enable macro_puts() with UART0_puts()
//
#if 0
#include "uartsup.h"
#undef  macro_puts
#define macro_puts(s)       UART0_puts(s)
#endif


#ifdef SUPPORT_MIDI_MENU_SEL
extern UINT8 gIsMidiSelMenu;
#endif


//2004AUDDRV extern  void    DSPReset();
extern  int     DTSAC3_check(void);        //Jeff 20010717
extern  void    resync_audio(void);
extern  int     get_size_map(int track);
extern  int     get_segment_length(int s);
//2004AUDDRV init_cdda(void);//kenny
//2004AUDDRV extern  void    init_dtscd(void);
//2004AUDDRV extern  void    init_mp3(void);
extern  int     do_mp3(void);
extern	int		do_aac(void);
extern  int     do_audio_cdda(void);

extern void ShowTitle();//axelchen 2005/3/31 
int bShowedTitle = 1;//add VCD->CDDA showed up LOGO

extern  void    set_video_aspect(void);
void    InitializeCDPlayback(UINT32 lba,UINT32 len,UINT8 id);

#include "ninf.h"
#include "pinf.h"

extern UINT32 save_srn_start_t;

UINT32  mp3ReadLen; //To count data(units in Word) that move to Aud Buf(for MP3 timeing display) Jeff 20010919
BYTE    audio_only;
#ifdef SUPPORT_ASF //add by Roger 06-04-18 for support asf video only file	
BYTE    video_only;
#endif

t_seq_info last_header;


static  inline  void
restart_sup(void)
{
	reset_sup();
}


void MacroSaveHeader()
{
    if( (!show_logo)&&((psd_state&PSD_SEL_LIST)==0) )
    {
        //Terry,2004/6/7 06:39PM
        //for HanYing, Video Masaic.
        save_sequence_info(&last_header);
    }
}


void MacroRestoreHeader()
{
    setup_sequence_info(&last_header);
}


/*
** Abort()
**
** HIGH PRIORITY.  IMMEDIATE
*/
void    MacroAbort()
{
	macro_puts("abort\n");
	avd_idle_state();
	SetIntrMask(0);
  //SetIntrFlag(0);
}

/*
** Sync()
**
** HIGH PRIORITY.  IMMEDIATE
*/
void    MacroSync()
{
	while (IsRPicStart || !IsVPicEnd)
		;
}

/*
** Pause()
**
** Cause the player to PAUSE and stop.
**
*/
void    MacroPause()
{
	AUDIF_Set_Pause();//2004AUDDRV AudioSetPause(); //Pause command to DSP Jeff 20010919
	avd_pause_on();
}

//
// Continue()
//
// Release from PAUSE status and continue playback.
// STC and other timers should be reset and resynced according to incoming
// bitstream.
//
void    MacroContinue()
{
	avd_pause_off();
	avd_play_state();
	AUDIF_Set_Continue();//2004AUDDRV AudioSetContinue(); //Continue-play command to DSP Jeff 20010919
}

/*
** DisplayBackground()
**
** Display the background for preview.
** Also set display picture id to 2
**
*/
//void    MacroDisplayBackground()
//{
//  set_disbuf(1);
//}

/*
** Freeze()
**
** Cause the player to play audio only.  Video output is freezed.
**
*/
//void    MacroFreeze()
//{
//}

/*
** OSD_OnOff()
**
**
*/
/*
void    MacroOSD_OnOff()
{
  if (MacroParam.OSD_OnOff.on_off)
  {
        // reset link address
    regs0->tlink_addr  = LINK_NULL;
    regs0->blink_addr  = LINK_NULL;
  }
  else
  {
        // setup link address
    regs0->tlink_addr  = region[0].osd_header[0];
    regs0->blink_addr  = region[0].osd_header[1];
  }
}

*/


/*
** PlayMP3
**
** interestingly, I am still not sure how to design this.
**
*/
void    MacroPlayMP3(void)
{
    macro_function(__FUNCTION__);

    /*
    ** play video elementary bitstream only.
    */
    CDSetPlayCRC();

    s_msf             = MacroParam.PlayMP3.address_msf;
    s_len             = MacroParam.PlayMP3.length;

    e_msf  = addmsf(s_msf, s_len);

    if(adv_search_time<0)
    {
    //Steven 2006/6/1 add (GetCurrentFileType() == CDROM_AAC) for aac audio data jump when F.B to last file//
        if ((GetCurrentFileType() == CDROM) || (GetCurrentFileType() == CDROM_AAC))
        {
            mp3ReadLen = (PlayBackLength-10)<<11;
            s_msf = addmsf(e_msf,-10);
        }
    }

    InitializeCDPlayback(msf2l(s_msf),(UINT32)s_len,0);
    VOBU_DIS = 0; //Jeff 20011024
}


/*
void PlayMP3FromEnd(UINT32 msf, UINT32 len)
{

}
*/


/*
void PlayMP3FromX(UINT32 msf, UINT32 len, UINT32 Xmsf)
{
  MacroParam.PlayMP3.address_msf=(msf);
  MacroParam.PlayMP3.length=(len);

  CDSetPlayCRC();

  s_msf             = MacroParam.PlayMP3.address_msf;
  s_len             = MacroParam.PlayMP3.length;

  e_msf  = addmsf(s_msf, s_len); //Jeff 20010827
  st_msf = s_msf;

//  mp3ReadLen = 0;

  //InitializeCDPlayback(msf2l(s_msf),(UINT32)s_len,0);
  InitializeCDPlayback(msf2l(Xmsf), (UINT32)s_len, 0);

  VOBU_DIS = 0;
}
*/


UINT8 avd_search_header(void)
{
    if (AVD_state == STATE_FINDFIRSTSEQ) return TRUE;
    return FALSE;
}


extern void init_svcd_as(void); // in \nav\user_if.c


extern BYTE audioNotContinuous; //Jeff 20021125


//
// FUNCTION
// InitializeCDPlayback()
//
void
InitializeCDPlayback(UINT32 lba,UINT32 len,UINT8 id)
{
    macro_function(__FUNCTION__);
    
    #ifdef MP4_INIT_STATE_INVALID_KEY
    MP4_init_state = 0;
    #endif
 
    #ifdef ZOOM_FFBF_NOT_ACROSS_TRACK//Jack 20040930
    if(vpp_zoom || adv_search_time)
    {
        vpp_zoom = 0;
        adv_search_time = 0;
        osd_tog_region(REGION1,OSD_OFF);
        //PrintOsdMsg(STR_OS_PLAY,REGION1, 1,0);
    }
    #endif


    if(counter_down==-1)
        counter_down = 5;
    flush_atapi();

	// initialize new playback
    audio_only    = 0;
    set_video_stream_id(0xe0);

	// initialize cd track
    cd_update_trk_now();

	// initialize service program
    setup_decode_service(SERVICE_CD);
    cd_type = GetCurrentFileType();

#ifdef SUPPORT_MP4
	if (cd_type != CDROM_MP4)
    	do_system_init = do_system = do_system_layer;
#else
   	do_system_init = do_system = do_system_layer;
#endif

	do_video = do_video_init = do_video_parsing;

#ifndef	SUPPORT_8202_DVB
	do_system_init_bak = do_system;
#endif

    restart_video_engine();
    restart_audio_engine();

    if ((cd_type != CDDVD) && (cd_type_loaded != CDROM)) // Robert 2004/02/05, cdrom disc should not enter.
    {
        //terry,2002/5/1 12:12AM
        //audio/subtitle must be initial,avoid being reset on trk chg
        init_svcd_as();

        // initialize cd msf
        //printf("psd_state:%x\n",psd_state);
        if (cd_type_loaded != CDROM)
        {
            if (((psd_state&PSD_PLAY_SEG) != PSD_PLAY_SEG) || (bDiscType == CD_OKO))
            {
                st_msf = gettrkmsf(cd_trk_now) & 0x00ffffff;
                if ((psd_state & PSD_PLAY_LIST) && pFsJpeg->List.p.play_time)
                {
                    e_msf = addmsf(s_msf, getUINT16_bi(&pFsJpeg->List.p.play_time) * 5);
                }
                else if ((bDiscType == CD_OKO) && ((!IsPBCOn()) || (psd_state & PSD_PLAY_LIST)))
                {
                    UINT8 a_o_id = (pFsJpeg->cdrom.oko_trk_end[cd_trk_now] >> 24);
                    e_msf = pFsJpeg->cdrom.oko_trk_end[cd_trk_now] & 0x00ffffff;
                    set_audio_stream_id(0xc0 | (a_o_id >> 4));
                    sup_set_channel(a_o_id & 0xf);
                }
                else
                {
                    e_msf = get_next_trk_msf(cd_trk_now);
                }

	        if (bDiscType == CD_CVD)
                {
                    //printf("oko id:%d\n",oko_menu_id);
		    set_audio_stream_id(0xc0 |oko_menu_id);
                    sup_set_channel(oko_menu_id);
                }

		if ((gettrkcna(cd_trk_now) & CNA_DATA) == 0)
                    cd_type = CDDA;
            } //if( ( (psd_state&PSD_PLAY_SEG)!=PSD_PLAY_SEG )||(bDiscType == CD_OKO) )
        } //if(cd_type_loaded!=CDROM)

        if (len == 0) len = msf2l(e_msf) - msf2l(s_msf);

        // setup VCD specific information
        if (cd_type != CDDA)
        {
            unsigned v_id;

            // initialize video stream
            v_id = 0xe0 | (id & 0x03);    // VCD: depends on PSD
            if(v_id >= 0xe3) v_id = 0xe0;
            if(v_id != 0xe0) audio_only = 2;
            set_video_stream_id(v_id);

            //printf("st_msf:%x s_msf:%x\n",st_msf,s_msf);
            //printf("2.goto_active:%x\n",goto_active);
	    if (goto_active == 1)
            {
                // * search video-sequence header
                //we must avoid user keyin when searching video seq. header
                //macro_puts("macro: search seq.hdr\n");
                reset_sequence_state();
                AVD_ResetMediaStatus();
                AVD_state = STATE_FINDFIRSTSEQ;
                start_atapi_intr(msf2l(st_msf),5*75, 16);
                MediaMainLoop();
                flush_atapi();

			    restart_video_engine();
			    restart_audio_engine();
                //if (!sequence_start)
                //  macro_puts("macro: seq.hdr NOT found\n");
                //else
                //  macro_puts("macro: seq.hdr FOUND\n");
	        if (sequence_start)
	            goto_active = 0;
            } else if (((psd_state==(PSD_PLAY_LIST|PSD_PLAY_ENTRY)) || adv_search_time<0) && (cd_type_loaded!=CDROM)) {
                // list, entry or backward playback: force auto-setting
                goto_active = 1;
            } else if ((last_header.horizontal_size_value)&&(last_header.vertical_size_value)) {
                // has last-header: use saved-header info.
                Restore_header();
	    } else {
                // otherwise
                goto_active = 1;
            }

            //printf("3.goto_active:%x\n",goto_active);
            //printf("psd_state:%x goto_active:%x\n",psd_state,goto_active);
            if (goto_active)
            {
                if( (get_size_map(cd_trk_now)==1) || (cd_type_loaded==CDVCD10))
                    setup_vcd_motion_pal();
                else
                    setup_vcd_motion_ntsc();
                goto_active=0;
            }
        } //if(cd_type != CDDA)
        //printf("stream_video:%x audio_only:%x psd_state:%x\n",stream_video,audio_only,psd_state);
    } //if ((cd_type!=CDDVD)&&(cd_type!=CDROM))

    if( (cd_type_loaded == CDSVCD || cd_type_loaded == CDVCD10 || cd_type_loaded == CDVCD20)&&(cd_type == CDDA) )
    {
        if (bShowedTitle) ShowTitle();
        
        bShowedTitle=0;
        //if (t_disp==0)    ircmd_display();
    }//axelchen 2005/3/31 add VCD->CDDA showed up LOGO
    else bShowedTitle=1;
    
    AVD_ResetMediaStatus();
    source_end = 0;
    program_end = 0;//Steven add 2006/07/07 to initialize audio-related control flag to fix CDDA halt down problem//
    if ((play_state != VCD_STATE_PREVIEW) && (play_state != VCD_STATE_9FRAMES))
    {
        avd_play_state();
    }
    else
    {
        avd_preview_state();
    }

    SetIntrMask(INTR_MASK_NORMAL);
    restart_sup();

    timeout_playback    = 0;
    regs0->rtc_31_16    = 0;
    timestamp_key       = 0;    // alan 0425
    #ifdef PMP_UI  //zxb 2005-9-23 11:37 for the bug that 
    //after the select button is pressed to play a mp3 
    //,the screen save is shown right now.
    save_srn_start_t = get_rtc_val();
    #endif
    set_stc(0);
    
    set_stc_init();
    P_frame	        = 0;    // clear pause

    // navigator-state
    PE_ClearNav();

    sys_cmd = 0;

    if (vpp_zoom<2)
    {
        set_video_aspect();
    }

#ifndef IR_TOOL
	printf("cd_type:%x\n",cd_type);
#endif
       
    switch(cd_type)
    {
	case CD_DA:
	case CDDA:
	{
		//Jeff 20020527
		BYTE bDTS=0;
		BYTE preCDsubtype;
		int     iRetry=0;

    #if defined(SUPPORT_MIX_MP3_CDDA)&&defined(REMAIN_TIME)    // lxg add   2006-4-7 11:37ÉÏÎç
		  if( (GetCurrentFileType() == CD_DA)  )  // Solve bug: when change mp3 to cdda file in mixed disc ,display time will error (when use remain time)
		 {
		   Mp3_kbitrate=Mp3_kbitrate_PreCalc=0;
		 }
    #endif

		preCDsubtype = cd_subtype; //Jeff 20021206
		audio_only = 1;   // terry,2002/4/30 05:32PM ff>=4 mute audio
		//init_cdda();        // for mix mode
		cd_subtype = CD_DA;       //Jeff 20020415
		setup_decode_service(SERVICE_CDDA);
		//4-7-23 0:28
		AUDIF_Set_Volume(0);//AudioSetVolume(0); //Jeff 20021125
        //#ifdef CDDA_DEEMPHASIS //Steven 2006/08/21 move it to AUDIF_LPCM_Init_Parm() to avoid missing command from dsp
        //set_dsp3_pcm_value(71, pFsJpeg->cdrom.pre_emphasis[cd_trk_now]); //axel 2005/10/20 for pre-emphasis disc
        //#else
        //set_dsp3_pcm_value(71, 0);
        //#endif
        // 2004/01/17 yltseng, because when we do some action during DTSAC3_check(), this action may be invalid because
        // goto_active is set to 1. So we prevent user input during DTSAC3_check by setting counter_down longer
        counter_down = 10;  

		do { //Jeff 20020518
			int iCheckType;
			audioNotContinuous=5; //Jeff 20021125
			goto_active = 1; //avoid display time show error time
			start_atapi_intr(msf2l(st_msf),150, 16);//terry,0515,search track start up
			iRetry++;

			iCheckType = DTSAC3_check();
#ifdef SUPPORT_AC3_CD_DISC //terry,2004/2/17 06:35PM
			if (iCheckType==0xac3)
			{ //Jeff 20040102
				//Dolby-CD
				cd_subtype = CD_AC3;
				AUDIF_Init_AC3CD();//2004AUDDRV init_ac3cd();
				setup_SetAC3Config();
				if ( setup_IsSet2SPDIF_Bitstream() ) {
					AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
				}
				iRetry = 3;
				bDTS=0xf;
			} else
#endif
			if (iCheckType > 0)
			{
				cd_subtype = CD_DTS;       //move to here 2003-8-13 0:38
				//printf("DTS bitstream\n");
#if !defined(NO_DTS_OUTPUT)||defined(FORCE_NO_DTS_OUTPUT)//nono 4-5-5 13:31
	#ifndef DTS_CD_OUT_RAW_A
				if ( !setup_IsSet2SPDIF_Bitstream() )//nono 2-7-5 21:38
	#endif
				{
					AUDIF_Init_DTSCD();//2004AUDDRV init_dtscd();
				}
#endif//#ifndef NO_DTS_OUTPUT

				// cd_subtype = CD_DTS;       //Jeff 20020415
				setup_SetDTSCDConfig();

#ifndef DTS_CD_OUT_RAW_A
				if ( setup_IsSet2SPDIF_Bitstream() ) { //Jeff 20031230
                    //ycwen 2004/08/31 : if not download PCM again, it would be wrong when "AC3->DTS"
                    AUDIF_Set_CodingMode(AUDIF_CODING_MODE_PCM);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_PCM);
					AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
				}
#endif
				iRetry = 3;
				bDTS=1;
			}
			//printf("2.cd_subtype=%x\n",cd_subtype);
		} while(iRetry < 3);

		printf("program:%x source_end:%x AVD_media_status:%x goto_active:%x sys_cmd:%x\n",program_end,source_end,AVD_media_status,goto_active,sys_cmd);

        #ifdef INCLUDE_MP3_ENCODER
			WAV_BARRIER_PTR = 3072;
		#endif
		
		if(program_end)
		{
			//terry,2003/8/24 04:38PM
			program_end = 0;
			source_end = 0;
			goto_active = 0;
			sys_cmd = 0;
			AVD_ResetMediaStatus();
		}

		if (bDTS==0) AUDIF_Init_CDDA();//2004AUDDRV init_cdda();

		flush_atapi();
		goto_active=0;

		if (preCDsubtype != cd_subtype) 
        {
		#ifdef ALCO_PDVD_NO_DTS //added 05/06/10 by Jack for alco!
            if(preCDsubtype == CD_DTS)
            {//enable AU_D0
                regs0->sft_cfg3 |=(0x01<<1);
            }
        #endif
		AUDIF_Reset_DSP();//2004AUDDRV DSPReset(); //Jeff 20021206
        }
		

#ifndef CD_INIT_DNOT_MUTE//4-8-20 12:16
		audioNotContinuous=10; //Jeff 20021125
		AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0); //Jeff 20021125
#else   //ycwen : 2004/9/6 : To prevent bf/ff from de-mute
    #ifdef MP3_CD_FF1_BF1_MUTE
        if (adv_search_time != 0)
    #else
        if ((adv_search_time > 2)||(adv_search_time < -2))
    #endif
            AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
#endif
	}
	break;

#ifdef SUPPORT_MP4
	case CDROM_MP4:
		if (!FILE_UNSUPPORT_AUDIO() && FILE_UNSUPPORT_VIDEO())
			audio_only = 1;

		do_video = do_video_init = do_mp4_parsing;

              #ifdef SUPPORT_NERODIGITAL
              extern UINT32 uVideoCodecType;
              
              if (uVideoCodecType == 0x61) //MP4 File Format, Mpeg-2 video source
              {
                  do_video = do_video_init = do_video_parsing;
              }
              #endif //SUPPORT_NERODIGITAL

		if (IS_FILE_TYPE_MPG12())  // 2005/09/28 yltseng
		{
		    do_system_init = do_system = do_system_layer;
			do_video = do_video_init = do_video_parsing;
		}

#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
		if (media_type == MEDIA_CARD)
			setup_decode_service(SERVICE_CARDFILE);
#endif

		break;
#endif

#ifdef SUPPORT_WMA
	case CDROM_WMA:
         //liych 2005-7-29 for play mp3 then prev to wma display time show number but 0;
         asf_pck_time = 0;
		do_system = doASFHeader;
		audio_only = 1;

	#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
		if (media_type == MEDIA_CARD)
			setup_decode_service(SERVICE_CARDFILE);
	#endif

		AUDIF_Init_WMA();//2004AUDDRV InitWma();
		//ycwen 2004/10/26 To prevent wma FF/BF from de-mute when changing track
    #ifdef MP3_CD_FF1_BF1_MUTE
        if (adv_search_time != 0)
    #else
        if ((adv_search_time > 2)||(adv_search_time < -2))
    #endif
            AUDIF_Set_Volume(0);
		break;
#endif

#ifdef SUPPORT_WAV
    case CDROM_WAV:
        printf("SUPPORT_WAV in macro.c\n");
        do_system = do_audio_cdda;
        audio_only = 1; 
	#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
            if (media_type == MEDIA_CARD)
			setup_decode_service(SERVICE_CARDFILE);
	#endif
		AUDIF_Init_CDDA();
        #ifdef MP3_CD_FF1_BF1_MUTE
            if (adv_search_time != 0)
        #else
            if ((adv_search_time > 2)||(adv_search_time < -2))
        #endif
                AUDIF_Set_Volume(0);
	    break;
#endif

#ifdef SUPPORT_AAC
	case CDROM_AAC:
		do_system = do_aac;
		audio_only = 1;

	#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
		if (media_type==MEDIA_CARD)
			setup_decode_service(SERVICE_CARDFILE);
	#endif

		AUDIF_Init_AAC(NULL);
		break;
#endif



	case CDROM:
		do_system = do_mp3;
		audio_only = 1; //Jeff 20011116

//kevinmonkey 060313 move to fs_nav_mp3.c FS_MP3MainLoop() since playmp3 may pass file_end - 10(msf) 
//into InitialzePlayback() [-> if(adv_search_time<0) s_msf = e_msf -10 in MacroPlayMP3()] and for some 
//files we may not be able to find bitrate information withing the last 10 msf.
/* 
#ifdef REMAIN_TIME  // 2004/08/10 yltseng
		Mp3_kbitrate = Mp3_kbitrate_PreCalc = PreParseMP3BitRate( VBR_MP3_CENTER_N_LBA, 20, lba, len );
#endif
*/
	#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
		if (media_type==MEDIA_CARD)
			setup_decode_service(SERVICE_CARDFILE);
	#endif

	    // 2004/08/11 yltseng
        AUDIF_Init_MP3();//2004AUDDRV init_mp3();
        break;

    default:

#ifdef SUPPORT_PRECALCULATE_VIDEOBITRATE_FOR_FILE_MODE
	    // 2004/08/11 yltseng, initialization for pre-calculate video bitrate
        Mp3_kbitrate_PreCalc = 0;
#endif

#ifdef SUPPORT_FILE_SYSTEM_MODE
	#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
		if ((cd_type_loaded == CDROM) || (cd_type == CDROM_MPG)) // Robert 021127
		{
			if (media_type == MEDIA_CARD)
				setup_decode_service(SERVICE_CARDFILE);
		}
		#endif
#endif

#ifdef SUPPORT_MIDI
	#ifdef SUPPORT_MIDI_MENU_SEL
		if ( gIsMidiSelMenu||Is_MIDI_STATE() )
		{
		} else
	#else
		if ( Is_MIDI_STATE() )
		{
		} else
	#endif
#endif
    #ifdef DVD_SERVO
		if ((cd_type_loaded == CDVCD10) && (is_svo_dvd()))
	#else
		if (cd_type_loaded == CDVCD10)
	#endif
		{
			AUDIF_Set_CodingMode(AUDIF_CODING_MODE_AC3);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_AC3); // robert 2004/02/19
		}
		else
		AUDIF_Init_MP3();//2004AUDDRV init_mp3();//for mix-mode
        break;

	case CDDVD:
		break;
    } //switch(cd_type)

	do_system_init = do_system;
#ifndef	SUPPORT_8202_DVB
	do_system_init_bak = do_system;
#endif


    if(IsPBCOn() && (rep_ab_mode == REPEAT_FIND_B))
    {
        s_msf=repStart;
        lba=msf2l(s_msf);
    }

    {//terry, reduce code ,0528
        int bat;

        #if DISC_SYSTEM!=DISC_SYSTEM_ATAPI
            ss_msf = s_msf;
            printf("goto msf %06x\n", s_msf);

            //if(cd_type_loaded==CDDVD)
            //bat=128;
            //else
            bat=32;
        #else
            if ((cd_type == CDDVD) || (cd_type == CDDA) || (cd_type == CD_DA))
            {
            #ifdef DVD_AUDIO
                bat=32;    //terry,2004/2/26 08:08PM
            #else
                bat=16;    //terry,2004/2/26 08:08PM
            #endif
            }
            //Steven 2006/6/1 add (GetCurrentFileType() == CDROM_AAC) for aac audio data fetch unit//
            else if ((GetCurrentFileType() == CDROM) || GetCurrentFileType() == CDROM_AAC)	// yltseng 0316 MP3 BW
                bat=1;      
            else
                bat=4;
        #endif

	    #if defined(SUPPORT_MP4) || defined(SUPPORT_WMA) || defined(SUPPORT_AUD_WMA)
            if (GetCurrentFileType() == CDROM_WMA)
                bat = 1;
		    else if (GetCurrentFileType() == CDROM_MP4)
			    bat = 32;
	    #endif
	
	    #ifdef SUPPORT_QUICKTIME  //ycwen 2006/9/27 move from lbaif.c
        if ((audio_only && IsM4AFileType()) ||  //M4A Audilo Only Source
            (IS_FILE_TYPE_ND() && FILE_UNSUPPORT_AUDIO()))    //Special case. MP4 Not coded Source
        {
           bat = 4;
        }
        #endif //SUPPORT_QUICKTIME
        
        #if defined(SUPPORT_OGG)
        if (IS_FILE_TYPE_OGG())
            bat = 1;
		#endif


        #ifndef IR_TOOL
        printf("initplayback,lba:%x s_msf:%x e_msf:%x len:%d\n",lba,s_msf,e_msf,len);
        #endif
        
        #ifdef SUPPORT_MP4_SUBTITLE	//yaowh add 2005-12-5 9:57
	    if( (GetCurrentFileType() == CDROM_MP4) )//&&(resumeMSF!=0) )//yaowh modify 2006-1-21 15:20
		{
			if(g_pfnPollingSubtitle){
				supOpenSubtitle();
			}
		}
		#endif
        
        #if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
         if (media_type==MEDIA_CARD)  //wthsin, 2004/7/7 02:34pm
         {
           if(adv_search_time!=0) 	adv_search_time=0;
         }
        #endif
        #if 0//def CDDA_FORWD_BACKWD_PLAY   //zxb 2005-5-12 0:14
        //nono move to v11.c please check. 2006-3-17 3:30

        if(cd_type_loaded==CDDA)
            adv_search_time=0;
        #endif//CDDA_FORWD_BACKWD_PLAY
        start_atapi_intr(lba,len, bat);

        if(cd_type_loaded!=CDDVD)
        {
            get_cdkit_time(CD_TRK_CHANGED);
            if(adv_search_time>=0) p_msf=0;//terry,2004/1/19 03:22PM,for bw ,cross track ,time error
            else p_msf=e_msf;
        }
    }
#ifdef DISPLAY_MENU_BUG_FIX    
    if(t_disp)
    {
        //printf("display base menu refresh............\n");
        //disp_fade_in(); 
        DispPolling(1);
    }
#endif                    
}


/*
** Play()
**
**
*/
void    MacroPlay()
{
  timeout_playback              = 0;
}


void    MacroFindFirstNav()
{
    flush_atapi();

    start_atapi_intr(MacroParam.FindFirstNav.lba, MacroParam.FindFirstNav.len, 16);

    setup_decode_service(SERVICE_CD);
    restart_video_engine();
    set_video_stream_id(0xe0);
    set_audio_stream_id(0xc0);

    SetIntrMask(INTR_MASK_NORMAL);
    //SetIntrFlag(0);
    restart_video_engine();

    restart_sup();

    timeout_playback    = 0;
    regs0->rtc_31_16    = 0;
    AVD_state           = STATE_FINDFIRSTNAV;
    AVD_ResetMediaStatus();
}



//
// FUNCTION
// MacroPlayLBA
//
// DESCRIPTION
// playback from a specific LBA location.
//
// PARAMETER
// MacroParam.PlayLBA.lba : LBA start address
//
void
MacroPlayLBA()
{
    UINT8 id=0;
    macro_function(__FUNCTION__);

    if( (bDiscType == CD_OKO)&&(psd_state==(PSD_SEL_LIST|PSD_PLAY_SEG)) )
    {
        id=2;
        cd_trk_now=1;
    }
    InitializeCDPlayback(MacroParam.PlayLBA.lba,MacroParam.PlayLBA.len,id);

#ifdef MACRO_DBG
    printf("playlba, msf:%x len:%d lba:%d stream_video:%x\n",
          s_msf,(msf2l(e_msf)-msf2l(s_msf)+5),msf2l(s_msf),stream_video);
#endif
}


// Cyue: for VOD
#ifdef SUPPORT_STREAM_BUFFER
//======================================================
//void  MacroPlayStream()
//      Initializing system to play stream
//INPUT  ARGUMENTS: NONE
//OUTPUT ARGUMENTS: NONE;
//RETURN: NONE
//
// cyue: 2002-08-08 08:35AM Add to Standard code
//======================================================
void    MacroPlayStream()
{
    if(counter_down==-1)//Jack added 06/02/23
        counter_down = 5;
        
  stream_init(); //init streambuffer
  // initialize new playback
  audio_only    = 0;
  set_video_stream_id(0xe0);
  set_audio_stream_id(0xc0);

  // initialize service program
  setup_decode_service(SERVICE_STREAMING);
  cd_type       = 0;

  // initialize video stream
  set_video_stream_id(0xe0);
  AVD_ResetMediaStatus();
  avd_play_state();

  restart_video_engine();
  restart_audio_engine();
  SetIntrMask(INTR_MASK_NORMAL);
  restart_sup();

  timeout_playback              = 0;
  regs0->rtc_31_16              = 0;
  timestamp_key                 = 0;    // alan 0425
  set_stc(0);
  set_stc_init();
  P_frame           = 0;    // clear pause

  // navigator-state
  PE_ClearNav();

  sys_cmd=0;
}


#endif //#ifdef SUPPORT_STREAM_BUFFER

/*
** PlayTrack()
*/
void    MacroPlayTrack()
{
  int item;
  macro_function(__FUNCTION__);

  item      = MacroParam.PlayTrack.track;
  #ifdef VCD_PBCON_RESUME
  //s_msf     = gettrkmsf(item)&0x00ffffff;
  if(resumeMSF)  	
  {
    s_msf     =  resumeMSF;
    resumeMSF = 0;
    resumeTRK = 0;
  }
  else
  s_msf     = gettrkmsf(item)&0x00ffffff;
  #else
  s_msf     = gettrkmsf(item)&0x00ffffff;
  #endif

//  goto_active = 0x0f;
  /*if ((gettrkcna(item)&CNA_DATA)==0)
    cd_type=CDDA;
  else
    cd_type=cd_type_loaded;*/

  InitializeCDPlayback(msf2l(s_msf),0,0);

  #ifdef MACRO_DBG
  printf("playtrk, msf:%x emsf:%d leadout:%x lba:%d stream_video:%x\n",s_msf,e_msf,gettrkmsf_leadout(),msf2l(s_msf),stream_video);
  #endif
}


/*
** PlayEntry()
*/
void    MacroPlayEntry()
{
  int item;

  item  = MacroParam.PlayEntry.entry;
  s_msf = get_entry(item);
  //printf("item:%x msf:%06x lba:%06x\n",item,s_msf,msf2l(s_msf));
  s_msf             = MSF(bcd2bin(msf_mm(s_msf)), bcd2bin(msf_ss(s_msf)), bcd2bin(msf_ff(s_msf)));
  //cd_type=cd_type_loaded;
  InitializeCDPlayback(msf2l(s_msf),0,0);

  #ifdef MACRO_DBG
  printf("playentry, msf:%x len:%d lba:%d \n",s_msf,msf2l(e_msf)-msf2l(s_msf),msf2l(s_msf));
  #endif
}


/*
** PlaySegment()
*/
void    MacroPlaySegment(void)
{
  int   item;
  BYTE  seg_code;

  item              = MacroParam.PlaySegment.segment;
  seg_code          = get_segment(item);

  #ifdef MACRO_DBG
  printf("SEG CODE=%x\n",seg_code);
  #endif

  #ifdef MACRO_DBG
  printf("SEG CODE[4:2]=%x\n",(seg_code>>2) & 0x07);
  #endif

  s_msf  = get_segment_msf(item)&0x00ffffff;
  SegLen = get_segment_length(item);
  e_msf  = addmsf_ss(s_msf,SegLen*2);
  st_msf = s_msf;

  //cd_type=cd_type_loaded;
  InitializeCDPlayback(msf2l(s_msf), 0,(seg_code>>2) & 0x07);

#if 0
  /*
  ** SEG_CODE [1:0]
  **
  ** 00 : no-audio
  ** 01 : mono audio
  ** 10 : stereo audio
  ** 11 : 2-channel audio
  */
  if( (seg_code&0x03)==0 )
      vcd_state       = 0;
  else
      vcd_state       = VCD_AUDIO;


  /*
  ** SEG_CODE [4:2]
  **
  ** 000 : no video
  ** 001 : NSTC normal res. still
  ** 010 : NTSC high res. still
  ** 011 : NTSC normal res. motion
  ** 100 : reserved
  ** 101 : PAL normal res. still
  ** 110 : PAL high res. still
  ** 111 : PAL normal res. motion
  */

  id=(seg_code>>2) & 0x07;
  switch (id)
  {
  case 1:   /* NTSC normal-res still        */
  case 5:   /*  PAL normal-res still        */
  case 2:       /* NTSC high-res still          */
  case 6:       /*  PAL high-res still          */
    vcd_state                 |= VCD_VIDEO;
    stream_video              = 0xe0| (id&0x03) ;
    break;

  case 3:   /* NTSC normal-res motion       */
  case 7:       /*  PAL normal-res motion       */
    vcd_state                 |= VCD_VIDEO;
    stream_video              = 0xe0;
    break;
  }
  #ifdef MACRO_DBG
   printf("playseg, msf:%x len:%d lba:%d stream_video:%x\n",s_msf,(msf2l(e_msf)-msf2l(s_msf)+5),msf2l(s_msf),stream_video);
  #endif
#endif
}

/*
** PlayOneSlide
**
** Playback exactly one slide and pause.
*/
//void    MacroPlayOneSlide()
//{
//}


/*
** PlayRomSlide()
**
** Playback video-elementary bitstream embedded in ROM (address space).
**
*/
void    MacroPlayRomSlide()
{
    macro_puts("play_rom_slide\n");

    // reset navigator-state
    PE_ClearNav();

    //
    // setup video source and server.
    romimage_ptr                  = MacroParam.PlayRomSlide.rom_addr;
    setup_decode_service(SERVICE_ROMV);

    SetIntrMask(INTR_MASK_NORMAL_ROM);
    restart_video_engine();
    restart_sup();

    timeout_playback    = 0;
    regs0->rtc_31_16    = 0;
    set_stc(0);
    set_stc_init();
    save_srn_start_t=0;

    macro_puts("prs_status\n");

    // avd-state
    avd_playoneromslide_state();
    AVD_ResetMediaStatus();

    // parser-state
    P_frame           = 0;

    //
    macro_puts("prs_aspect\n");
    set_video_aspect();

    //
    macro_puts("prs_stopcd\n");
    if (!CDOpened()) CDSetStop();

    macro_puts("prs_exit\n");
}



//void    MacroPlaySector()
//{
//}


//void    MacroPlaySlides()
//{
//}


//void    MacroPreview()
//{
//}


//void    MacroPreviewSector()
//{
//}


/*
** ReadCD
**
*/
//void    MacroReadCD()
//{
//}

//void    MacroReadSeqheader()
//{
//}

/*
** SelectStream()
**
** Select next incoming stream
**
** Typical values:
**
**  0xe0    Video motion picture
**  0xe1    Video low-res still picture
**  0xe2    Video hi-res still picture
**  0xc0    Audio (main)
**  0xc1    Audio (alternate)
**
**  0xff    Auto select next incoming stream.
**
*/
#if 0
void    MacroSelectStream()
{
  set_video_stream_id(MacroParam.SelectStream.video);
  set_audio_stream_id(MacroParam.SelectStream.audio);
}
#endif

