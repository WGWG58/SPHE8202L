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
|  File Name   :  ircmd_subtitle.c
|
|  Description :  realize subtitle function in IR subtitle key.
|
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2004/4/6        Terry         Creating
|  0.2  2004/8/4        Terry         modified
|--------------------------------------------------------------------------------*/

#include "file_if.h" //lyc add 2006-4-26,for null idx1,can't resync av but continues only  
#include "avi_def.h"

extern void sup_select_subtitles(int n);
extern void sup_select_channel_2(int chn);
#ifdef SUPPORT_QUICKTIME
extern int QT_Set_SubP();
#endif //SUPPORT_QUICKTIME

#ifdef TWO_KEY_SWITCH_TWO_SUBTITLE  //added by wangwei,2004-9-29 17:25
extern int IDTWO;
extern int twoSubTTFlag;
#endif

#ifdef SUPPORT_MP4_SUBTITLE
extern BYTE  Is_Support_FormatS ; //lyc add for check if support subtitle format
#endif

#if defined( AVI_INTERNAL_SUP ) || defined( SUPPORT_MP4_SUBTITLE )  // 2004/09/17 yltseng
#include "avi_if.h"
UINT8   g_uiSubtitleKeyPressed = FALSE;

#ifdef SUPPORT_QUICKTIME
static inline UINT32 sub_picture_QT()
{
    if (IS_FILE_TYPE_ND())
    {
        UINT32 uResult;
        uResult = QT_Set_SubP();
        if ((uResult & 0xF0000000) == 0xF0000000)
        {
            psprintf(RegionValStr[REGION1], "DISABLE SUBPICTURE");
            PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        }
        else
        {
             //lyc add 2005-12-22
            extern char *get_cur_SUBP_Name();
	          char *c = get_cur_SUBP_Name(); 
            psprintf(RegionValStr[REGION1], "SUBPICTURE %d  %s", uResult,c);
            PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        }
        return TRUE;
    }
    return FALSE;
}
#endif //SUPPORT_QUICKTIME

static inline void PrepareToLoadMP4InternalSubtitle()
{
    if( action_click &&( (GetCurrentFileType() == CDROM_MP4)||(GetCurrentFileType() == CDROM_AVI)) )
    {
        g_uiSubtitleKeyPressed = TRUE;

    #ifdef AVI_INTERNAL_SUP
        extern int file_set_supic_stream(int sup_strm_num);
        
        if( file_set_supic_stream( NP_SPSTN & 0x3f ) )
            g_uiSubtitleKeyPressed = FALSE;
        #ifndef SUPPORT_MP4_SUBTITLE
        else    
            NP_SPSTN &= (~0x40);
        #endif
    #endif
    }
}
/**************************************************************************
 *  Function Name: PrepareToLoadMP4ExternalSubtitle                       *               
 *  Purposes:                                                             *
 *     load external subtitle.                                            *
 *  Descriptions:                                                         *                                                                       *
 *  Arguments:                                                            *
 *    NP_SPSTN: current subtitle number variable.                         *
 *              numerical value from 0x40.                                *         
 *                                                                        *
 *  Returns:     NONE                                                     *
 *  See also:    NONE                                                     *
 **************************************************************************/
void PrepareToLoadMP4ExternalSubtitle()
{
    #ifdef SUPPORT_MP4_SUBTITLE
    // 2004/01/31 yltseng, if DiscType is CDROM, then we need to wait until current packet is finished,
    // that is, we have to wait until !is_dvddsp_hw_busy() and ( do_cd == do_cd_sync )
    // for DVDROM, it's easier, we just wait until !is_dvddsp_hw_busy()
    
    extern int do_cd_sync(void);
    extern BYTE DiscType;
    if( DiscType == CDDVD || do_cd == do_cd_sync 
    #if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
        || (media_type == MEDIA_CARD)  //kevinmonkey 050707 for card to call this function
    #endif  //usb,card supported    
    )
    {
        if( g_uiSubtitleKeyPressed )
        {
            g_uiSubtitleKeyPressed = FALSE;         // 2004/09/19 yltseng, [note] don't change the code sequence
            UINT32 uiStream = ( NP_SPSTN & 0x40 ) ? ( NP_SPSTN & 0x3f ) : 0xffff;
            if( supSetSubtitleStream( uiStream ) )  // 2005/10/04 yltseng, resync av after change subtitle stream
            {
               if((GET_FILE_FLAG()&AVI_IDX1) > 0) //lyc add 2006-4-26,for null idx1,can't resync av but continues only  
            	{
                extern UINT8 avd_video_discont;
                avd_video_discont = 1;
            	}
            }
            else
            {
                NP_SPSTN &= (~0x40);
            }
#if 0//tw delete.20030223
			extern BYTE s_supParseAgain; //2006-02-14 mimitsai add for changing sub-title language bug.
			if(s_supParseAgain == 1)
				s_supParseAgain=0;            
#endif//#if 0//tw delete.20030223
        }
    }
    #endif//#ifdef SUPPORT_MP4_SUBTITLE
}
#else

static inline void PrepareToLoadMP4InternalSubtitle()   {}
inline void PrepareToLoadMP4ExternalSubtitle()          {}

#endif//#if defined( AVI_INTERNAL_SUP ) || defined( SUPPORT_MP4_SUBTITLE )  // 2004/09/17 yltseng

#ifdef SUPPORT_MP4
/**************************************************************************
 *  Function Name: set_sub_title_Ns                                       *
 *  Purposes:                                                             *
 *      get subtitle total number .                                       *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *      dAv_SPST_Ns: subtitle total number variable.                      *
 *                                                                        *
 *  Returns:     NONE                                                     *
 *  See also:    NONE                                                     *
 **************************************************************************/
void set_sub_title_Ns(UINT8 Ns)
{
    pDSV->dAv_SPST_Ns=Ns;
}
#endif

/**************************************************************************
 *  Function Name: sel_2nd_subtitle                                       *
 *  Purposes:                                                             *
 *       realize two subtitle switch.                                     * 
 *  Descriptions:                                                         *
 *       realize two subtitle switch,but there is a fixed connection      *
 *       between subtitle 1and subtitle 2,unskillfully.                   *                      
 *  Arguments:                                                            *
 *       id: get subtitle number.  for example,0x40:ch1.                  *
 *                                                                        *
 *  Returns:     NONE                                                     *
 *  See also:    NONE                                                     *
 **************************************************************************/

#ifdef TWO_SUBTITLE//terry,2004/8/4 09:39AM
#ifndef TWO_KEY_SWITCH_TWO_SUBTITLE  //modified by wangwei,2004-9-29 17:04
void sel_2nd_subtitle(int id2)
{
    int id1=NP_SPSTN&0x3f;
    
    id2=id2&0x3f;    
    if(id2>=pDSV->dAv_SPST_Ns) id2=0;    
    
    if(pDSV->dAv_SPST_Ns>1)
    {
      if(id1 != id2)
      {
        sup_select_subtitles(2);            
        sup_select_channel_2(0x20+id2);                
      }else
      {
        sup_select_subtitles(1);            
      }
    }    
}
#endif //TWO_KEY_SWITCH_TWO_SUBTITLE
#endif
/**************************************************************************
 *  Function Name: ircmd_sub_picture                                      *
 *  Purposes:                                                             *
 *     realize subtitle switch function in IR subtitle key.               *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *    id     : subtitle number id.                                        *
 *    timer  : fix time length that contents show on display.             *                                        *
 *    id_str : str id.                                                    *
 *                                                                        *
 *  Returns:     NONE                                                     *
 *  See also:    NONE                                                     *
 **************************************************************************/
#if defined(PMP_UI)&&defined(SUPPORT_OSDID3)
extern int osd_id3_flag;
extern void show_id3(void);
#endif
void ircmd_sub_picture(void)
{
   #if defined(PMP_UI)&&defined(SUPPORT_OSDID3)//////////////yangli mod control osdid3 2005-7-18
   if(pFsJpeg->gifsState == FS_STATE_MP3)
    {
        if(osd_id3_flag==0)
     {
        osd_id3_flag=1;
        show_id3();
        psprintf(RegionValStr[REGION1], "ID3 ON");
        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1); 
     }
     else
     {
        osd_id3_flag=0;
        osd_tog_region(REGION3,OSD_OFF);
        psprintf(RegionValStr[REGION1], "ID3 OFF");
        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
     }
     
     return;
    }
     #endif /////////////////SUPPORT_OSDID3
    
    int id=0,timer,id_str;

#ifdef DVB1000_NON_OS 	//Maoyong 2005-3-21 19:43
	#ifdef SUPPORT_TELETEXT
	if(system_state == SYSTEM_TS)
	{
		extern int g_Ttx_Mode;
		if(g_Ttx_Mode == 0)
			EnterTeletextMode();
		else
			ExitTeletextMode();	
		return;
	}
	#endif
#endif	//#ifdef DVB1000_NON_OS
    
#ifdef SUPPORT_MIDI_MENU_SEL  //xlluo for midi title 
        if (Is_MIDI_STATE())
        {
		invalid_key();
		return;
        }
#endif
#ifdef SUPPORT_MIDIDISK_TITLE
        if (bIsPlayMidiTitle)//xlluo for midi title
        {
		invalid_key();
		return;
        }
#endif
#ifdef	INVALID_SUBPICTURE_WHEN_SVCD	//wuxiaofeng 2004-03-23
	if(cd_type_loaded==CDSVCD)
	{
		invalid_key();
		return;
	}
#endif//#ifdef	INVALID_SUBPICTURE_WHEN_SVCD

    /*
	#if defined(ADJUSTING_ACTION_VALID_RIGHT_NOW)
	#ifdef NEWSTYLE_WINDOW
		if ( (full_scrn&MESSAGE) && (action_click==2) )	// alan, 2003/8/28 05:32PM
			action_click = 0;
		else
	#endif
    action_click = 1; //Jeff 20030506
    #endif
    */
#ifdef	JPEG_EFFECT_MODE_USE_SUBTITLE//zhaoyanhua add 2003-12-24 9:50
	if(cd_type_loaded == CDROM)
	{
		if (Is_JPEG_PLAY_STATE())
		{
#ifdef JPG_EFFECT
			jpeg_effect_toggle();
#endif
		}
		else
			invalid_key();
		
		return;
	}
#endif

    //kevinmonkey 060606 if IR command flows to this place, check stream number. currently
    //meant for mpeg2 and AVI with subpicture/subtitle or multi audio track
    //if(stream number == -1) invalid key, if(stream number == 1) print stream 1 message.
    if(pDSV->dAv_SPST_Ns == 255)
    {
        invalid_key();
        return;    
    }
    else if(pDSV->dAv_SPST_Ns == 0)
    {
        #ifdef VOB_SUBTITLE 
        if(GetCurrentFileType()!=CDROM_MPG)
        #endif
        {
            invalid_key();
            return;
        }
    }

#ifdef SUPPORT_QUICKTIME
    if ((GetCurrentFileType() ==CDROM_MP4) && (sub_picture_QT()))
        return;
#endif //SUPPORT_QUICKTIME    

    //Jeff change, 20031006, fix press IR(GOTO) sub-picture will be "automatic" toggled
    #if defined(ADJUSTING_ACTION_VALID_RIGHT_NOW)
    	#ifdef NEWSTYLE_WINDOW
        	if ( (full_scrn&MESSAGE) && (action_click==2) )	 
        		action_click = 0;
        	else
      	#endif
        action_click = 1; //Jeff 20030506
    #else
        #ifdef NEWSTYLE_WINDOW
		    if ( (full_scrn&MESSAGE) && (action_click==2) )	// alan, 2003/8/28 05:32PM
			    action_click = 0;
	    #endif
    #endif

#ifdef VOB_SUBTITLE
	if(GetCurrentFileType()==CDROM_MPG) {
		id=Subp_stream_Chg_VOB(action_click);
	}
	else	
#endif    
    if(bDiscType == CD_OKO) { //Jeff 20020610
        invalid_key();
        return;
    } else
		//chg & check subtitle stream id
		if( !(!DVD_check_state()&&(cd_type_loaded==CDDVD)) )
		{
            #ifdef NEW_SEARCH_OSD  //yw 021007
            if(key_up_down==0)
				//id=Subp_stream_Chg(action_click,-1); //Jeff 20021008
				id=Subp_stream_Chg(action_click,1); //nono 2-11-22 11:19
            else
            #endif
				id=Subp_stream_Chg(action_click,1); //Jeff 20021008

		   printf("chg sub-title\n");
		}

        printf("pDSV->dAv_SPST_Ns:%x\n",pDSV->dAv_SPST_Ns);
		//setting osd data
        //id : 0x40:Ch1, 0x41:Ch2, 0x42:Ch3, 0x43:Ch4, 0xbf:off
		#ifdef ALCO_DVD_UI
		if((id&0x40)&&((id&0x3f)<=pDSV->dAv_SPST_Ns)&&(pDSV->dAv_SPST_Ns>0))//shenyj modify for alco 11/22
		#else
		if( (id&0x40)&&( (id&0x3f)<pDSV->dAv_SPST_Ns ) ) 
		#endif
		{
            
            timer=((id&0x3f)<<8)|0x01;
#ifdef TWO_SUBTITLE//terry,2004/8/4 09:39AM
        #ifndef TWO_KEY_SWITCH_TWO_SUBTITLE  //modified by wangwei,2004-9-29 17:02
            sel_2nd_subtitle(id+1);
        #else          
        if(action_click)
        {
            if(IDTWO==(NP_SPSTN&0x3f))  //same one,close the 2nd subtitle.
            {
                sup_select_subtitles(1);
            twoSubTTFlag=1;
        }
            else if(IDTWO>=pDSV->dAv_SPST_Ns)  //off,close the 2nd subtitle.
        {
            sup_select_subtitles(1);
                twoSubTTFlag=0;
        }
            else if(IDTWO!=-1)
        {
                sup_select_subtitles(2);
                twoSubTTFlag=2;
            }
        }
        #endif//TWO_KEY_SWITCH_TWO_SUBTITLE
        
#endif            
            id_str=0x20;       
		}else
		{
            id_str=STR_OS_OFF;
            timer=1;
		}

        PrepareToLoadMP4InternalSubtitle();     // 2004/09/17 yltseng
	#if defined (SUPPORT_SMI_MultiLanguage)//parse external caption before show the caption id
        PrepareToLoadMP4ExternalSubtitle();
 	#endif
		//show osd str
		if(id)
        {
#ifdef SPHE1000_DVDSTATE_CALLBACK			//2004/10/21 wjzhang , sphe1000B(stb-dvd): osd display
            if(id==0xbf|id==0x7e)
				OSD1000ISP_STATUS(OSDISP_TITLE_OFF, OSDIR_SUB_TITLE);
			else
                OSD1000ISP_STATUS(((pDSV->dAv_SPST_Ns)<<4)|(id+1&0x0f), OSDIR_SUB_TITLE);
#endif
            //PrintOsdMsg(STR_OS_SUBTITLE|(id_str<<8),REGION1,timer,4);
        #ifdef SUPPORT_DIVX6
            extern UINT32 is_divx6_file;
            extern void	divx6_display_subpic_track(UINT8 sup_strm_num);
            //kevinmonkey 060821 switch to divx6 display function only for clips with internal subpicture.
            if (is_divx6_file == 1 && (file_sup_num != 0)) 
            {
               divx6_display_subpic_track(NP_SPSTN & 0x3f);
            }
            else
        #endif
       #ifdef SUPPORT_MP3_ENCODER  //qinhua,2005-11-9 9:26   
           if ((cd_type == CDDA)&&!(detect_type))
            {              
              psprintf(RegionValStr[REGION1], "NO DEVICE");
	      PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
            }
           else if((cd_type == CDDA)&&(detect_type))
           {
 	   return;
           }
           else
            PrintOsdMsg(STR_OS_SUBTITLE|(id_str<<OSDSTR_ID_TOTL_BIT),REGION1,timer,4);
       #else
            PrintOsdMsg(STR_OS_SUBTITLE|(id_str<<OSDSTR_ID_TOTL_BIT),REGION1,timer,4);
       #endif 
       
       #ifdef SUPPORT_MP4_SUBTITLE
         if(Is_Support_FormatS) //lyc add for check if support subtitle format
         {
         	 psprintf(RegionValStr[REGION1], "UnSupport Format Subtitle");
	         PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
	         Is_Support_FormatS = 0;
         }	
       #endif
        }
        else {
    #ifdef NEWSTYLE_WINDOW
		if(full_scrn&MESSAGE)//xyy 2003-7-29 15:08
			psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_NONE]);
		else
    #endif
            invalid_key();
        }
    #ifdef NEWSTYLE_WINDOW
		if(full_scrn&MESSAGE)//xyy 2003-7-29 15:08
            updateSubtitle();
    #endif
}

#ifdef DOUBLE_TITLE //susu 2003-8-22 18:44
void ircmd_double_picture(void)
{
	if(full_scrn&DOUBLETITLE) 
	{
		exit_double_title();
	}
	else
	{
		if( !(!DVD_check_state()&&(cd_type_loaded==CDDVD)) )
		{
			full_scrn=DOUBLETITLE;
			exe_double_title();
			
			//Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 9:13
            SetFullscrnCmdFuncPtr( double_title_func_up, double_title_func_down, double_title_func_left,
                                   double_title_func_right, double_title_func_select);
		}
		else
	        invalid_key();
	}
}
#endif



