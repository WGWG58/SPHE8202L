/*
* terry,2003/8/18 04:19PM
* Maintain this file
* Terry,2004/3/25 06:29PM
* yltseng, 2006/05/18, fix mpeg show time bug
* yltseng, 2006/09/06, fix M2I truncation error when msf comes from DVD
*/

#include "config.h"
#include "regmap.h"
#include "global.h"
#include "macro.h"
#include "func.h"
#include "util.h"
#include "stdlib.h"    //huo 2000.12.14
#include "cdfunc.h"
#include "cfont.h"
#include "sio.h"
#include "vfdfunc.h"
#include "ringbuf.h"
#include "ircmd.h"
#include "ircode.h"
#include "cd.h"
#include "auctrl.h"
#include "user_init.h"  //terry,2001/1/9 03:29PM

#include "avd.h"
#include "dvdpe.h"

#include "fs96602.h"
#include "osd.h"
#include "framebuf.h"
#include "cderr.h"
#include "vpp.h"
#include "user_if.h"
#include "dsp3_if.h"
#include "atapi_if.h"
#include "dma.h" //Jeff 20010919
#include "auddrv.h" //2004AUDDRV oliver 20041004 for using audio driver purpose
//#include "audif.h"
#include "setup.h"
#include "fsGUI.h"
#include "drv.h"
#include "auddac.h"
#include "fsNAV.h"
#include "asf_if.h"

#include "iop.h"//2-7-9 9:40
#include "UartTxd.h"
#include "avsync.h"

//huziqin 2006-4-19 removed

#if defined(PT2322)||defined(PT2320)
#include "audctrl.h"
#endif 

#if defined(TAS3001_AMP)   //use TI 3001 amplifier  jason ych add 2-8-9 10:10
#include "ti3001.h"
#endif 

#if defined(TAS5026_AMP)   //use TI 3001 amplifier  jason ych add 2-8-9 10:10
#include "ti5026.h"
#endif 

#ifdef SUPPORT_CDG  //Jeff 20020824
#include "cdg.h"
#endif

#ifdef SUPPORT_MP4  // 2004/04/20 yltseng, to show remain time
#include "avi_if.h"
#endif

#include "kinf.h"   // 2004/08/11 yltseng
#include "bit_rate.h"

#if ( defined(SUPPORT_CARD_STORAGE) || defined(SUPPORT_USB) || defined(SPHE8202_CARD_STORAGE) )
#include "cardfs.h"
#endif

#ifdef IC_1002
#include "sinf.h"
#endif

// **************************************************************************************** //
extern UINT8    DVD_show_time(void);    //Jeff 20010717

extern UINT16   Is_MP3_STATE(void);
extern void     vfd_set_showtime(void);

extern void     DispPolling(BYTE bReset);
extern void     DispCookOSD0(BYTE bChange);

extern UINT32   mp3ReadLen;             //Jeff 20010919
extern UINT32   myTime;                 //Jeff 20020902
extern UINT32   oldmp3ReadLen;          //Jeff 20020917
extern BYTE     bASFHeaderFinish;


#ifdef SUPPORT_OSDID3                   //suqiaoli add 2004-3-26 
extern void     show_id3_song(void);
#endif

extern UINT8    avd_search_header(void);

extern UINT32   PlayBackLength;

#ifdef SUPPORT_SCORE        //gerry modified,2004-3-6 9:37
UINT32          score_disp_flag;
#endif
#ifdef EASTECH_VFD_DISP
extern BYTE clear_old_show_time ; //lyc 2005-4-15
#endif
#ifdef MP3_REPEAT_AB_SHOW_TIME_EXACTLY
UINT32  _mp3ReadLen,_myTime; 
#endif
// **************************************************************************************** //
#ifndef DVDRELEASE
    //#define DBG_TIME
#endif

#ifdef DBG_TIME
    #define printf_time printf
#else
    #undef printf
    #undef print_block
    #define printf(f, a...) do {} while (0)
    #define print_block(x,y) do {} while (0)
    #define printf_time(f, a...) do {} while (0)
#endif

// **************************************************************************************** //
/*
** showtime
*/
void show_time(void)
{
    switch(play_state)
    {
    case VCD_STATE_POWER:
        return;
        
    case VCD_STATE_OPEN:    // terry 891002
    case VCD_STATE_CLOSE:   // terry 891002
    case VCD_STATE_IDLE:    // terry 891002
    case VCD_STATE_READTOC: // terry 891002
        disp_trk_now=0;
    case VCD_STATE_MP3_FILELIST:    //kevinmonkey 050329 fixing in playlist display time errorneously ticking
        disp_time=0;        // terry 891002
        break;
        
    case VCD_STATE_STOP:    // terry 891002
        #ifdef OP_STOP_PANEL_DISPLAY//lijd 2005-6-30 11:32
          if(StopTimes==1)
          {
           disp_time==old_disp_time;
           
          }
          else if(StopTimes==2) 
          {
           if(cd_type_loaded==CDDA)
           {
           		 
                 disp_time=disc_time;                
           }
          
          }
        #else
        if(cd_type_loaded!=CDROM)
        {
            if(cd_type_loaded!=CDDVD)
                disp_trk_now = cd_total_trk();
            
            disp_time=disc_time;
            
            if(cd_type_loaded==CDSVCD)
                disp_time=disp_time/PLAY_SPEED;
        }
        else
        {
            disp_time=0;        // 2005/06/24 yltseng
        }
       #endif//OP_STOP_PANEL_DISPLAY  
            
        break;
    } //end case
    
    if( ((goto_active)||(sys_cmd))&&(play_state!=VCD_STATE_STOP) )//2-5-25 22:42 to avoid AB show "00" quickly.
    {
        printf_time("goto_active:%x sys_cmd:%x play_state:%x\n",goto_active,sys_cmd,play_state);
        return;
    }
    
    if( (disp_time < 0)||((disp_time > (100*3600))) )
    {
        printf_time("time<0\n");
        return;
    }
    if ( (cd_type_loaded!=CDROM) && (disp_trk_now > 99) ) 
    {
        printf_time("trk>99\n");
        return;
    }
    
#if !defined( SUPPORT_FILE_DISPLAY_TM ) && defined( SUPPORT_FILE_SYSTEM_MODE )
    if ((cd_type_loaded == CDROM) && (GetCurrentFileType() == CDROM_MPG)) // Robert 021125
        disp_time = 0;
#endif
#if defined(ALCO_DVD_UI)//maybe not need the definition.nono 20060218

    if(IsPBCOn() && is_menu())
    {
        if(disp_time==1)
          disp_time = 0;
    }
#endif
    
#ifdef  NOCHANGE_DISPLAY_WHEN_PRESTOP
    if((play_state!=VCD_STATE_STOP)||(resumeMSF==0))//wuxiaofeng added 2004-03-05
#endif  
    {
      #ifdef EASTECH_VFD_DISP
      //lyc 2005-4-15
    	if((card_plug_state == USER_DO_PLUG_IN)&&(clear_old_show_time))
    	{
    	    disp_time = 0;
    	    clear_old_show_time =0; 	
    	}
	 #endif
    show_time_hh = disp_time / 3600;
    show_time_mm = (disp_time % 3600) / 60;
    show_time_ss = (disp_time % 3600) % 60;
    }
    
    if(
        (play_state!=VCD_STATE_CLOSE)&&
        (play_state!=VCD_STATE_OPEN)&&
        (play_state!=VCD_STATE_READTOC)&&
        (play_state!=VCD_STATE_IDLE)
        )
    {
#ifdef FUSS_DVD//nono 2-6-22 15:41
    #if defined(FUSS_PANEL)||defined(FUSS2_PANEL)
        if( (cd_type_loaded==CDDA)&&(full_scrn&MARK) )
        {
            vfd_set_showmark();
        }
        else
    #endif
#endif

#ifdef NEW_UART_COMMAND   //lijinhai for fuss updata time normal
            if(timeout_vfd) return;
            else
                vfd_set_showtime();
#endif
            //=========================================================================================
            //  freyman, 2002-07-03,
#if defined(SUPPORT_VFD)&&defined(SUPPORT_VFD_PANEL)//nono 2003-11-24 12:09//lijd 2004-12-4 11:38
    #ifndef VFD_VOLUME_DISPLAY
        #ifndef TEST_VFD//nono 2-8-9 14:39
            #if defined(BBK_PANNEL)||defined(BBK_DSS_555_PANNEL)//fengjl 3-12-26 9:24  to avoid VFD refresh successive when play WMA/MP3/DVD
            if(play_state!=VCD_STATE_STOP) 
            #endif 
            vfd_set_showtime();//2-5-15 16:09 add it to avoid vcd/cd vfd showing time irregularly.
        #endif 
    #endif 
#endif//SUPPORT_VFD
            //==========================================================================================
    }
    
    if(t_disp)
    {       
        #ifdef SUPPORT_FUNCTION_MENU
        if((full_scrn==SETUP) || (full_scrn==SETUP_PLUS))        
#else
        if(full_scrn==SETUP)        
        #endif //end #ifdef SUPPORT_FUNCTION_MENU
            return;
        
        //printf_time("<%d>",disp_time);        
        if(t_disp>10)
        {
            #ifndef NEW_DISPLAY_METHOD 
            DispCookOSD0(1);
            #endif
        } else {
            DispCookOSD0(0);
        }
        
        #ifndef NEW_DISPLAY_METHOD
        DispPolling(0);  
        #endif

        // 2004/07/26 yltseng
        sample_bit_rate_per_sec();
    } //if(full_scrn&GOTO)

#ifdef NEWSTYLE_WINDOW
    if(full_scrn&MESSAGE)
    {
        UpdateTT_CHP_info();    
    }
#endif
}

// **************************************************************************************** //
//************Steven 2006/6/1 add for get MP3 and AAC Sampling rate and bitrate************//
UINT8 cnt_smprate = 0;
UINT8 Mp3_kbitrate_temp = 0;
UINT16 Mp3_kbitrate_avg[10] = {0,0,0,0,0,0,0,0,0,0};//Steven 2006/6/1 add for stabilize bitrate//
inline void MPx_AAC_ChkSmpRate()
{
UINT8  i = 0;


#ifdef SUPPORT_AAC//Steven 2006/6/1 add for get AAC Sampling rate and bitrate//
    if(GetCurrentFileType() == CDROM_AAC)
    {
    
    //*****Steven 2006/6/1 move from do_aac start*********//
        extern UINT32	AUDIF_frequency_clock_set;
	    if(AUDIF_frequency_clock_set == 0)	//wrwu 2005/02/17, add for setting sampling frequency rate
	    {
		delay_1ms(1);	// wait DSP parsing smapling rate
		AUDIF_AAC_Init_Freq(get_dsp3_pcm_value(DSP_RUNTIME_AAC_SMPRATE_GET));
	    }     
    //*****Steven 2006/6/1 move from do_aac end *********//
        //Steven 2006/10/04 modify , use get_dsp3_pcm_value() instead of directly access address //
        Mp3_kbitrate = (UINT16)get_dsp3_pcm_value(DSP_RUNTIME_AAC_BITRATE);       
        if((Mp3_kbitrate > 0) && (cnt_smprate <= 10))
        {        
            for(i=9;i>0;i--)
            {
            Mp3_kbitrate_avg[i] = Mp3_kbitrate_avg[i-1];
            }
            Mp3_kbitrate_avg[0] = Mp3_kbitrate;
            cnt_smprate++;
            if(cnt_smprate > 10)
            cnt_smprate = 10;           
        }    
        else if(Mp3_kbitrate == 0 )
            cnt_smprate = 0;

        if(cnt_smprate == 10)
        {                              
            for(i=1;i<10;i++)
            {
            Mp3_kbitrate += Mp3_kbitrate_avg[i];
            }
            Mp3_kbitrate /= 10;
            Mp3_kbitrate_temp = Mp3_kbitrate;
        }      
        else
        {        
            if(Mp3_kbitrate_temp != 0)
            {
           
            Mp3_kbitrate = Mp3_kbitrate_temp;
            }
            else if((Mp3_kbitrate <10) && (Mp3_kbitrate != 0))
            {               
            Mp3_kbitrate = 96;
            Mp3_kbitrate_temp = 0;
            }
        }
        return;
    }
#endif


#ifdef SUPPORT_MP4
        if ( (GetCurrentFileType() == CDROM_MP4) && !IS_FILE_TYPE_MPG12() )  //qinhua,add ,2005-9-9 23:37
    return;
#endif	// SUPPORT_MP4

    
// 2004/07/28 yltseng    
    #ifdef REMAIN_TIME
    if( remain == NO_REMAIN_TIME )
    #endif
        //if this MP3 file is variable bitrate, the timeing display will be incorrect
    //Steven 2006/10/04 modify , use get_dsp3_pcm_value() instead of directly access address //
    Mp3_kbitrate = (UINT16)get_dsp3_pcm_value(DSP_RUNTIME_MPEG_BITRATE);     //3*14
    
    BYTE smpIndex   = (BYTE)get_dsp3_pcm_value(DSP_RUNTIME_MPEG_SMPRATE); //3*15+2;
    //smpIndex= 0 ~ 8
    //0: 44.1K(MPEG-I)
    //3: 22.05K(MPEG-II)
    //6: 11.025K(MPEG-II.V)
    //1: 48K(MPEG-I)
    //4: 24K(MPEG-II)
    //7: 12K(MPEG-II.V)
    //2: 32K(MPEG-I)
    //5: 16K(MPEG-II)
    //8: 8K(MPEG-II.V)
    if(smpIndex<=8)
    {//Get Sampling Rate success
    
        const BYTE tab[3] = {2, 4, 1};
        
        smpIndex=tab[smpIndex%3];
        
        if (smpIndex != smp_rate_now)
        {
            //set new sampling rate
            printf("smpIndex: %d\n", smpIndex);
            AUDIF_Set_SampleRate(smpIndex);//2004AUDDRV audif_set_sample_rate(smpIndex);
        }
    }
    
}

// **************************************************************************************** //
#ifndef MP3_REPEAT_AB_SHOW_TIME_EXACTLY
UINT32  _mp3ReadLen,_myTime; 
#endif
UINT32  oldBitRate=0;
#if defined(PMP_UI)&&defined(SUPPORT_OSDID3)//yangli add for control osdid3 2005/8/3
extern int osd_id3_flag;
#endif
//terry,2002/4/29 07:16PM
//debug: remain time , display error
//cause: recursive setting disp_time.
//assign default MP3BitRate(128b/s) to caculate time, Jeff 20020531
#ifdef ALCO_DVD_UI
BYTE old_remain=0;
#endif

void Mp3_ChkSkipData(void)
{
    UINT32 tmpBitRate;
    int nDiff;

    if ( (play_state!=VCD_STATE_NORMAL) && (adv_search_time==0) )   return;
       
    tmpBitRate = Mp3_kbitrate;
    if (tmpBitRate) 
    {   
        int totaltime;
        
        if (adv_search_time >= 0) 
        {       
            p_msf=s_msf;          
            
            //printf("mp3ReadLen:%x oldmp3ReadLen:%x\n",mp3ReadLen,oldmp3ReadLen);
            if (mp3ReadLen < oldmp3ReadLen) {
                oldmp3ReadLen = 0;
                myTime = 0;             
                  
                //printf("myTime:%x\n",myTime);
            }
            //playback in normal sequence
            if ( (oldBitRate>0) && (tmpBitRate>0) &&
                (mp3ReadLen>0) && (oldmp3ReadLen>0) && (mp3ReadLen!=oldmp3ReadLen)
                )
            {        
                UINT32 len = mp3ReadLen - oldmp3ReadLen;        
                
                if (len > 0) 
                {       
                    myTime = myTime + (len<<9)/oldBitRate;
                    old_disp_time = myTime>>16;
                    //printf("myTime:%x\n",myTime);   
                }
            }
            
            oldBitRate = tmpBitRate;
        } else {       
            //if (msf>p_msf) {
            //when backward playback, we just show time displaying in descending sequence
            //so, we skip it during it's neighboorhood when time is in descending sequence
            if (  //( (s_msf>p_msf) && (s_msf < (p_msf+20) ) ) ||
                ( (oldmp3ReadLen<mp3ReadLen) && (oldmp3ReadLen>0) )
                )
            {                
                if (mp3ReadLen > (oldmp3ReadLen+20000) ) {
                    oldmp3ReadLen = mp3ReadLen;
                }
                return;
            }
            
            old_disp_time=(mp3ReadLen>>(11-4))/tmpBitRate; //time-now
            
            p_msf=s_msf;
            
            myTime = old_disp_time << 16;           
        }
        oldmp3ReadLen = mp3ReadLen;
        
        //old_disp_time=((M2I(e_msf)*75+msf_ff(e_msf))-(M2I(p_msf)*75+msf_ff(p_msf)))*16/tmpBitRate; //time-remain
        if (remain > NO_REMAIN_TIME) {
            #if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)//Jack copy from search1.c
            if(media_type == MEDIA_CARD)
            {
                extern CARD_INFO   cardP;
                totaltime = PlayBackLength * cardP.bytePerSec * 8 /1024 / tmpBitRate;
            }else
            #endif  //#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
            totaltime = PlayBackLength * 16 / tmpBitRate;
            nDiff = disp_time - (totaltime - old_disp_time);
            //printf("..%d, %d, %d\n", disp_time, totaltime - old_disp_time, nDiff);
            #ifdef ALCO_DVD_UI //added 05/05/30 by Jack
            if((old_remain!=remain) && (adv_search_time<0))
            {
                disp_time = totaltime - old_disp_time;
                old_remain = remain;
                nDiff = 0;
            }
            #endif

            if (adv_search_time)
            {
                if (adv_search_time>0)
                {
                    if ((nDiff<adv_search_time) && (nDiff > 0))
                        return;
                }
                else if (nDiff>adv_search_time)
                {
                    return;
                }
            }

            disp_time = totaltime - old_disp_time;
            //printf("totaltime:%d old_disp_time:%d disp_time:%d\n",totaltime,old_disp_time,disp_time);
        }else
        {
            nDiff = old_disp_time - disp_time;
            //printf("..%d, %d, %d\n", disp_time, old_disp_time, nDiff);
            
            if (adv_search_time)
            {
                if (adv_search_time>0)
                { 
#if defined(ALCO_DVD_UI)//maybe not need the definition.nono 20060218
                    if(nDiff < 0) //Jack added 04/12/02
                        disp_time = old_disp_time;
#endif                        
                    if (nDiff<adv_search_time)
                        return;
                }
                //Steven 2006/6/1 add ((nDiff > 0) && (disp_time != 0)) for time display bug when F.B//
                else if (((nDiff>adv_search_time) && (nDiff < 0)) || ((nDiff > 0) && (disp_time != 0)))
                {
                    return;
                }              
            }
           
            disp_time = old_disp_time;                        
        }
       
#ifdef DISP_TIME_NOT_CHANGE_WINDOW_PROGESS//zhaoyanhua add 2004-2-5 13:59       
        track_play_time = old_disp_time;
#endif //DISP_TIME_NOT_CHANGE_WINDOW_PROGESS        
        
#ifdef  SUPPORT_ID3                      
        show_id3_song();
#endif

#ifdef SUPPORT_OSDID3//liweihua add 2004-1-14 10:52
#ifdef PMP_UI
        if(osd_id3_flag==1)//////////////yangli mod 2005/8/3
#endif
        show_osd_id3_song();
#endif

#ifdef ALCO_DVD_UI
    old_remain = remain;
#endif

        return;
    }
    
    if( (rep_ab_mode != REPEAT_FIND_B)&&(goto_time==0) )
    {//terry,2003/6/24 10:57¤W¤È
       disp_time=0; //time-now
       old_disp_time=0; //time-remain
    }
}

// **************************************************************************************** //
UINT32 M2I(UINT32 msf)
{
    #define	msf_mm2(msf)	(((msf)>>16) & 0xffff)
    return ( (is_svo_dvd() ? msf_mm2(msf):msf_mm(msf))*60 + msf_ss(msf) );
}

// **************************************************************************************** //
#ifdef SUPPORT_FILE_DISPLAY_TM  
void init_file_trk_time(void)
{   
    dPg_tm=M2I(st_msf);
    #if defined(SUPPORT_USB)||defined(SUPPORT_CARD_STORAGE)//liweihua add 2004-3-12 15:09
    if((media_type == MEDIA_CARD) && (GetCurrentFileType() == CDROM_MPG))
        dNx_pg_tm=M2I(e_msf)*4;
    else
    #endif
    dNx_pg_tm=M2I(e_msf);   
            
    #ifdef IRCMD_DBG
    printf("end:%d disc:%d\n",dPg_tm,dNx_pg_tm);
    #endif
}
#endif

// **************************************************************************************** //    
void init_vcd_trk_time(void)
{
//#ifdef SUPPORT_MIX_MP3_CDDA   //linrc change "SUPPORT_MIX_MP3_CDDA" to "SUPPORT_MIX_DATA_CDDA_DISC"
#ifdef SUPPORT_MIX_DATA_CDDA_DISC //because we not only support this type mix mode disc 2004-12-15 15:53
    if(mp3_cd_end_trk==0)
    {
#endif

//Maoyong 2004.04.20 for CDROM MPG file can't show track num normally. 
//Bug exist when not define SUPPORT_FILE_DISPLAY_TM
#ifdef SUPPORT_FILE_SYSTEM_MODE
    if ( (GetCurrentFileType() != CDROM_MPG) )
#endif
        disp_trk_now=show_trk_num(cd_trk_now);
        
    if( psd_state==(PSD_SEL_LIST|PSD_PLAY_SEG) )  //selection list, play segement
    {
        disp_trk_now=cd_trk_lo;
        dPg_tm=M2I(st_msf);
    }
    else
        dPg_tm=M2I(gettrkmsf(cd_trk_now));
            
    if(bDiscType == CD_OKO)
        dNx_pg_tm=e_msf&0x00ffffff;
    else
        dNx_pg_tm=gettrkmsf(cd_trk_now+1);
    
    if( (cd_trk_now+1)<=cd_trk_hi )//nono add "=" 5-4-6 15:53
        dNx_pg_tm=M2I(dNx_pg_tm);
    else
        dNx_pg_tm=disc_time;//terry 891004
                
#ifdef IRCMD_DBG
    printf("end:%d disc:%d\n",dNx_pg_tm,disc_time);
#endif

//#ifdef SUPPORT_MIX_MP3_CDDA   //linrc change "SUPPORT_MIX_MP3_CDDA" to "SUPPORT_MIX_DATA_CDDA_DISC"
#ifdef SUPPORT_MIX_DATA_CDDA_DISC //because we not only support this type mix mode disc 2004-12-15 15:53
    }
    else
    {
        dPg_tm=M2I(st_msf);
        dNx_pg_tm=M2I(e_msf);
    }
#endif
    if(dNx_pg_tm>disc_time)//terry 891004
        dNx_pg_tm=disc_time;//terry 891004
}


#ifdef SUPPORT_PRECALCULATE_VIDEOBITRATE_FOR_FILE_MODE
// **************************************************************************************** //
static inline void AdjustCDDisplayTime( UINT32 uiBPS, UINT32 uiCurTime )
{   // 2004/11/25 yltseng
    if( ( cd_type_loaded == CDSVCD || cd_type_loaded == CDROM ) && !uiBPS )
        return;
    
    switch( remain )
    {
    case TRK_REMAIN_TIME:
        disp_time = dNx_pg_tm - uiCurTime;
        break;
    
    case DISC_REMAIN_TIME:
        disp_time = disc_time - uiCurTime;
        break;
    
    case DISC_TIME:
        disp_time = uiCurTime - disc_st_time;
        break;
    
    default:
        disp_time = uiCurTime - dPg_tm;
        break;
    }

    #ifndef EASTWIN_PORTABLE_DVD
        #ifdef SUPPORT_MPG_FILE_PARSER    
        if (( cd_type_loaded == CDSVCD || cd_type_loaded == CDROM )&&(!IS_FILE_TYPE_MPG12())) // 2004/11/25 yltseng
       #elif defined (ALCO_DVD_UI)
       if ((cd_type_loaded!=CDDA) && (cd_type_loaded!=CDVCD20) && (cd_type_loaded!=CDVCD10))
       #else
    if ( cd_type_loaded == CDSVCD || cd_type_loaded == CDROM ) // 2005/09/27 axel
        #endif
            disp_time = disp_time * 1378 / (uiBPS);    // 1378 = 75 * 2352 * 8 / 1024
    #endif
}

// **************************************************************************************** //
static inline void AdjustCardDisplayTime( UINT32 uiBPS __attribute__((unused)))
{
    #if defined(SUPPORT_CARD_STORAGE) || defined(SUPPORT_USB) || defined(SPHE8202_CARD_STORAGE)
    extern CARD_FILE cardFile;

    switch( remain )
    {
    case TRK_REMAIN_TIME:
        disp_time = cardFile.iLeaveSize / ( uiBPS << 7 );
        break;

    case NO_REMAIN_TIME:
        disp_time = ( cardFile.iFileSize - cardFile.iLeaveSize ) / ( uiBPS << 7 );
        break;
    
    default:
        disp_time = 0;
        break;   
    }
    #endif    
}

// **************************************************************************************** //
static inline UINT32 ModifyMSFTime()
{
    old_disp_time   = M2I( p_msf );     //old time
    UINT32  p       = M2I( s_msf );     //new time
    int     t       = p - old_disp_time;//diff time
    
    if( t_disp <= 10 )
    {
        if( adv_search_time )
        {
            if( adv_search_time > 0 )
            {
                if( t < adv_search_time )
                    return 0;
            }
            else if( t > adv_search_time )
                return 0;
        }
        else if( t == 0 )
            return 0;
            }
    
    p_msf = s_msf;

    if( (p<dPg_tm)||(p>dNx_pg_tm) )
        p = dPg_tm;

    return p;
}

// **************************************************************************************** //
static inline void ModifyParamForNewSytleWindow( UINT32 uiCurTime __attribute__((unused)))
{
    #ifdef NEWSTYLE_WINDOW
        #ifdef  JUST_SHOW_CD_TYPE                   //Maoyong 2004.02.26
    if( ( uiCurTime - dPg_tm ) == 0 ) 
        track_play_diff_time = 0;
    if( ( uiCurTime - dPg_tm - track_play_time ) > 0 )
        track_play_diff_time++;
        #endif

        #ifdef DISP_TIME_NOT_CHANGE_WINDOW_PROGESS  //zhaoyanhua add 2004-2-5 13:59       
    if( full_scrn & MESSAGE )
    {   
        track_play_time =  uiCurTime - dPg_tm;
        if( cd_type_loaded == CDSVCD )
            track_play_time = track_play_time / PLAY_SPEED;
    }
        #endif
    #endif    
}

// **************************************************************************************** //
static void Show_VCD_CDDA_Time( BYTE flag )
{   
    if(flag==CD_TRK_CHANGED)//moved from below to init_vcd_trk_time when play cd track in mix mp3cd disc.chenzhao20050525
    {
    #if defined( SUPPORT_FILE_DISPLAY_TM ) && defined( SUPPORT_FILE_SYSTEM_MODE )
        #ifdef SUPPORT_MPG_FILE_PARSER// 2005/09/27 axel
        if (GetCurrentFileType() == CDROM_MPG || IS_FILE_TYPE_MPG12() )
        #else
        if (GetCurrentFileType() == CDROM_MPG)
        #endif
            init_file_trk_time();
            else
    #endif
            init_vcd_trk_time();
        return;
    }
    
    if( play_state == VCD_STATE_MP3_FILELIST )
    {
        disp_time = 0;
        show_time();
        return;
    }

    UINT32 p = ModifyMSFTime();
    if( !p )
        return;

    #ifdef SUPPORT_SCORE        //gerry modified,2004-3-6 9:38
    score_disp_flag = p - dPg_tm;
    if( cd_type_loaded == CDSVCD )
        score_disp_flag = ( p - dPg_tm ) / PLAY_SPEED;
    #endif
    
    ModifyParamForNewSytleWindow( p );
     
    UINT32 uiBPS = Mp3_kbitrate_PreCalc;
    
    if( !uiBPS )
    {
        uiBPS = ( GetBPS() >> 10 );

        if( !uiBPS )
        {
            if( cd_type_loaded == CDSVCD )
                uiBPS = 2400 ;
            else
                uiBPS = 1340;
        }
        else
            Mp3_kbitrate_PreCalc = uiBPS;
    }

    #if defined(SUPPORT_CARD_STORAGE) || defined(SUPPORT_USB) || defined(SPHE8202_CARD_STORAGE)
    switch( media_type )
    {
    case MEDIA_CD:                              // 2004/11/25 yltseng
            AdjustCDDisplayTime( uiBPS, p );
        break;

    case MEDIA_CARD:
        #ifndef PMP_UI
        if( uiBPS )
            AdjustCardDisplayTime( uiBPS );
        #endif
        
        break;
        
    default:
        disp_time = 0;
        break;
    }
    #else
        AdjustCDDisplayTime( uiBPS, p );        // 2004/11/25 yltseng
    #endif
    
     #ifdef  NEXT_TRC_CACEL_REPAB//tianye 200607
     if((cd_type_loaded==CDDA)&&(rep_ab_mode == REPEAT_FIND_A)&&(disp_time == 0))
     {
           rep_ab_mode = REPEAT_AB_IDLE;
	   show_repeatAB(1);				  
     }
     #endif//end=>  #ifdef  NEXT_TRC_CACEL_REPAB

    show_time();    
}

#else//#ifdef SUPPORT_PRECALCULATE_VIDEOBITRATE_FOR_FILE_MODE

// **************************************************************************************** //
static void Show_VCD_CDDA_Time( BYTE flag )
{
    UINT32 p;
    int t;
   
    #ifdef SUPPORT_USB//liweihua add 2004-3-12
        #ifdef SUPPORT_MPG_FILE_PARSER// 2005/09/27 axel
    if ( (GetCurrentFileType() == CDROM_MPG || IS_FILE_TYPE_MPG12() )
        #else
    if( (GetCurrentFileType()   == CDROM_MPG)
        #endif
     && (media_type             == MEDIA_CARD) 
     && (play_state             == VCD_STATE_MP3_FILELIST))
    {
        disp_time = 0;
        show_time();
        return;
    }
    #endif      

    if(flag==CD_TRK_CHANGED)
    {
    #if defined( SUPPORT_FILE_DISPLAY_TM ) && defined( SUPPORT_FILE_SYSTEM_MODE )
        #ifdef SUPPORT_MPG_FILE_PARSER// 2005/09/27 axel
        if (GetCurrentFileType() == CDROM_MPG || IS_FILE_TYPE_MPG12() )
        #else
        if (GetCurrentFileType() == CDROM_MPG)
        #endif
            init_file_trk_time();
            else
    #endif
            init_vcd_trk_time();
        return;
    }
    else
    {
        p=M2I(s_msf);//new time
        old_disp_time=M2I(p_msf);//old time
        t=p-old_disp_time;//diff time
        
        if(t_disp<=10)
        {
            if(adv_search_time)
            {
                if(adv_search_time>0)
                {
                    if(t<adv_search_time)
                        return;
                }
                else if(t>adv_search_time)
                    return;
            }
            else if(t==0)
                return;
        }
        
        p_msf=s_msf;
        
        //terry,2002/6/26 06:18PM
        if( (p<dPg_tm)||(p>dNx_pg_tm) )
            p=dPg_tm;
    }

    switch(remain)
    {
    case TRK_REMAIN_TIME:
        disp_time=dNx_pg_tm-p;
        break;
    
    case DISC_REMAIN_TIME:
        disp_time= disc_time-p;
        break;
    
    case DISC_TIME://terry,2002/6/4 09:29PM add
        disp_time = p-disc_st_time;
        break;
    
    default:
        disp_time=p-dPg_tm;
        break;
    }
    
    #ifdef SUPPORT_SCORE        //gerry modified,2004-3-6 9:38
    score_disp_flag=p-dPg_tm;
    #endif

    if(cd_type_loaded==CDSVCD)
    {
        disp_time=disp_time/PLAY_SPEED; //terry, the play_speed means loader reading data
    #ifdef SUPPORT_SCORE        //gerry modified,2004-3-6 9:38
        score_disp_flag=(p-dPg_tm)/PLAY_SPEED;
    #endif
    }
    
    
    #ifdef NEWSTYLE_WINDOW
        #ifdef  JUST_SHOW_CD_TYPE       //Maoyong 2004.02.26
    if( (p -dPg_tm ) == 0 ) 
        track_play_diff_time = 0;
    if( (p -dPg_tm - track_play_time)>0 )
        track_play_diff_time++;
        #endif

        #ifdef DISP_TIME_NOT_CHANGE_WINDOW_PROGESS//zhaoyanhua add 2004-2-5 13:59       
    if(full_scrn & MESSAGE)
    {   
        track_play_time =  p-dPg_tm;
        if(cd_type_loaded == CDSVCD)
            track_play_time = track_play_time/PLAY_SPEED;
    }
        #endif
    #endif

    #ifdef SUPPORT_FILE_DISPLAY_TM//liweihua add 2004-3-12
        #if defined(SUPPORT_USB)||defined(SUPPORT_CARD_STORAGE)
             #ifdef SUPPORT_MPG_FILE_PARSER// 2005/09/27 axel
    if ((media_type == MEDIA_CARD) && (GetCurrentFileType() == CDROM_MPG || IS_FILE_TYPE_MPG12()) )
            #else
    if((media_type == MEDIA_CARD) && (GetCurrentFileType() == CDROM_MPG))
            #endif
        disp_time = (disp_time/4)-1;
        #endif
    #endif
    show_time();    
}

// lxg add  2006/07/20  To modify new code compile error   #if defined(SUPPORT_USB)&&(REMAIN_TIME)
static inline void AdjustCardDisplayTime( UINT32 uiBPS __attribute__((unused)))
{
}

#endif//#ifdef SUPPORT_PRECALCULATE_VIDEOBITRATE_FOR_FILE_MODE

// **************************************************************************************** //
static inline void ShowMPEGTime( BYTE flag __attribute__((unused)))
{
#ifndef SUPPORT_FILE_DISPLAY_TM
    show_time();
#else
    Show_VCD_CDDA_Time( flag );
#endif
}

// **************************************************************************************** //
#include "stc.h"
#ifdef SUPPORT_OGG
extern UINT32 GET_OGG_TIME();
#endif
static inline void ShowMP4Time()
{
#ifdef SUPPORT_MP4
	if(file_get_show_time())
		show_time();
#endif
}

// **************************************************************************************** //
static inline void ShowMP3Time()
{
   //#if	!(defined (PMP_UI)||defined(GPS_MP3_UI)||defined(ORITRON_HK_DVD))/////////////YANGLI 2005/9/20 MOD for play mp3 not show play time
												//frank.huang mod for play mp3 show play time in GPS_MP3_UI 051008	
    #if (defined(SUPPORT_CARD_STORAGE) || defined(SUPPORT_USB) || defined(SPHE8202_CARD_STORAGE))&& defined(REMAIN_TIME)  //zhongshan add 2005-9-16 14:53 
    if(media_type == MEDIA_CARD) 
    { 
        AdjustCardDisplayTime( Mp3_kbitrate_PreCalc ); 
    } 
    else 
    #endif
   // #endif ////end pmp_ui
    if( Is_MP3_STATE() )
        Mp3_ChkSkipData();
        
    #ifdef MP3_REPEAT_AB_SHOW_TIME_EXACTLY
    if((rep_ab_mode==REPEAT_FIND_B) && ((s_msf-repStart)<8) && ((repEnd-repStart)>8))
    {
       disp_time = (_myTime>>16); 
       //printf("ok????????? %d\n",disc_time); 
    }
    #endif
    
    show_time();
}
// **************************************************************************************** //
//zhuyanfeng add 2004/11/11 to resolve the bug that the symbol of repeat on display will not change switching repeat key when play jpg disc 
static inline void ShowJpegTime()
{         
    show_time();
}
// **************************************************************************************** //
static inline void ShowWMATime()
{
int nDiff;
#ifdef PMU_UI          ///////////////yangli mod for play wma reset,2005\11\4
    if (pFsJpeg->gifsState == FS_STATE_INIT)
        return;
#endif

#ifdef SUPPORT_WMA
    if (remain > NO_REMAIN_TIME)
    {
        if (bASFHeaderFinish)
        {
            int TempTime;
            old_disp_time = get_asf_pck_time();
            TempTime = (asf_file_duration - old_disp_time) / 1000;
            disp_time = TempTime;
        }
        else
        {
            disp_time = old_disp_time = 0;
        }
    }
    else
    {
        //Steven 2006/09/19 add to avoid time display error when asf payload header failed
        if (((play_state == VCD_STATE_NORMAL)||(play_state == VCD_STATE_FASTFORWARD)||(play_state == VCD_STATE_FASTBACKWARD))
           &&((bCheckPldProperty&0xF0) != (bPldProperty&0xF0)))
            return;

        old_disp_time = get_asf_pck_time() / 1000;
        nDiff = old_disp_time - disp_time;
        //Steven 2006/09/19 add to avoid glitter of time display when F.B
        if (adv_search_time)
            {               
                if (adv_search_time<0)
                if (((nDiff > 0) && (disp_time != 0)))
                {
                    return;
                }              
            }    
        
        disp_time = old_disp_time;
    }
#ifdef MP3_ONLY_STOP_TO_GUI                     //zhaoyanhua add 2004-1-7 13:45
    if ((play_state == VCD_STATE_MP3_FILELIST)) // Robert 2003/12/31
        disp_time = old_disp_time = 0;
#else
    if (play_state == VCD_STATE_STOP)           // Robert 2003/12/31
        disp_time = old_disp_time = 0;
#endif

    show_time();   
#endif//SUPPORT_WMA

}

// **************************************************************************************** //
static inline void ShowDVDTime()
{
    if(DVD_show_time())
        show_time();
}

// **************************************************************************************** //
/*------------------------------------------------------------------------
*  Function: cdkit_track_time
*
*  Description:
*     This function handle display/remaintime function
*
*  NOTE:
*------------------------------------------------------------------------*/
void get_cdkit_time(BYTE flag)
{    
    if( avd_search_header() || ( cd_type_loaded == 0 )
#ifdef FS_LOAD_DIR_SEPARATELY   // 2005/07/05 yltseng, because during directory change, file info will also change
                                // thus we might access to the wrong data. So in this condition, we will let it return.
         || ( play_state == VCD_STATE_READTOC )
#endif
    )
        return;
   
    switch( GetCurrentFileType() )
    {
    case CDROM_MPG:
        ShowMPEGTime( flag );
        break;
    
    case CDROM_MP4:
        #ifdef SUPPORT_MPG_FILE_PARSER// 2005/09/27 axel
        if(IS_FILE_TYPE_MPG12()) //qinhua ,modify for DAT file showtime,2005-11-28 17:57
            ShowMPEGTime( flag );
        else
        #endif
            ShowMP4Time();
        break;
        
    case CDROM:
    #ifdef SUPPORT_AAC    
    case CDROM_AAC://Steven 2006/6/1 add for AAC time display function //
    #endif    
        ShowMP3Time();
        break;
        
    case CDROM_WMA:
        ShowWMATime();
        break;
        
    case CDROM_JPEG:
        ShowJpegTime();//zhuyanfeng add 2004/11/11 to resolve the bug that the symbol of repeat on display will not change switching repeat key when play jpg disc 
        break;   
        
    default:
        if( cd_type_loaded == CDDVD )
            ShowDVDTime();
        else
            Show_VCD_CDDA_Time( flag );
        break;
    }
    //printf_w("filetyte:%d........................steven\n",GetCurrentFileType());
}

// **************************************************************************************** //
