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
|  File Name   :  browse_func.c
|
|  Description :  NEW STYLE WINDOW function in it.it can exe some function.
                  for example goto and display some information  etc.
|
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2003/6/28        xiongyuyue         Creating
|--------------------------------------------------------------------------------*/
/*****************************************************\
Creater: xiongyuyue
Date   : 2003/6/28 
Description: browse function using 
\*****************************************************/
#include "global.h"
#include "osd.h"
#include "func.h"
#include "cfont.h"
#include "util.h"
#include "ircmd.h"
#include "user_if.h" 
#include "Icon.h"
#include "kernel.h"
#include "vpp.h"
#include "browse_gui.h"
#include "osd_arc.h"
#include "stdlib.h"
#include "vpp_if.h"

#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW//zhaoyanhua add 2003-12-8 9:29
#include "modify_browse_func.c"

#else

#ifndef DVDRELEASE
//#define BROWSE_DBG
#endif


#ifdef DYNAMIC_SPECTRUM     //fengjl  3-10-30 12:34
extern BYTE band_onoff;
extern void Show3dspectrum(void); //axel 2003/12/2 11:31pm
#endif

#define browse_puts()           ((void)0)
#define browse_show_function()  ((void)0)

#ifdef  BROWSE_DBG
#include "sio.h"
#include "emuio.h"
#undef  browse_puts
#undef  browse_show_function
#define browse_puts             puts_w
#define browse_show_function()  do {browse_puts(__FUNCTION__); browse_puts("\n");} while (0)
#endif

/////////////////////////////////////////////////////////////////////////
//wanghaoying 2003-8-12 19:50 added
extern void set_video_aspect(void);
extern void startup_vpp_now(void);
//extern void set_vpp_disp_window(UINT32,UINT32,UINT32,UINT32);
/////////////////////////////////////////////////////////////////////////
extern UINT16 mp3_file_count(void);   //axel 2003/12/2 11:30pm

#ifdef NEWSTYLE_WINDOW          //xiongyuyue 
BYTE bInputState = NON_INPUT_STATE;
int bInputIndex = 0;   //for title/chapter search function,
BYTE bTimeInput = 0;
BYTE update_definition = 40;
extern UINT32 PlayBackLength;
/**************************************************************************
 *                                                                        *
 *  Function Name: br_Draw8space                                          *
 *                                                                        *
 *  Purposes:                                                             *
 *    display 8 space                                                     *
 *  Descriptions:                                                         *
 *    display 8 space between left string and right string                *
 *  Arguments:    fontColor: display the font's color                     *
 *                bkColor  : display the background's color               *
 *                index    : the string index 0 1 2 3 4                   *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void br_Draw8space(BYTE fontColor,BYTE bkColor,BYTE index)
{//erase displayed word and disp new word when press updown key(for draw left item)
    strcpy(linebuf,"            ");  //fengjl changed space from 8 to 12   3-11-24 18:52
    osd_DrawRegionString(brArea[BR_ITEM_AREA].xStart,brArea[BR_ITEM_AREA].yStart+ITEM_HEIGHT*index,
                        linebuf,fontColor,bkColor,arc_region_loc.region);
}
/**************************************************************************
 *                                                                        *
 *  Function Name: br_Draw18space                                         *
 *                                                                        *
 *  Purposes:                                                             *
 *    display 18 space                                                    *
 *  Descriptions:                                                         *
 *    display 18 space between left string and right string               *
 *  Arguments:    fontColor: display the font's color                     *
 *                bkColor  : display the background's color               *
 *                index    : the string index 0 1 2 3 4                   *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void br_Draw18space(BYTE fontColor,BYTE bkColor,BYTE index)
{//erase displayed word and disp new word when press updown key(for draw right item)
    strcpy(linebuf,"                  ");
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*index,
                        linebuf,fontColor,bkColor,arc_region_loc.region);
}	
/**************************************************************************
 *                                                                        *
 *  Function Name: br_DrawLeftItemStr                                     *
 *                                                                        *
 *  Purposes:                                                             *
 *    draw the left item string in the gui                                *
 *  Descriptions:                                                         *
 *    draw the left item string in the gui                                *
 *  Arguments:        hl_index:the left item string HL index 0-4          *
 *                    str_index:the left item string  index               * 
 *                    fontColor:display the font's color                  *
 *                    bkColor: display the background's color             *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void br_DrawLeftItemStr(BYTE hl_index,BYTE str_index,BYTE fontColor,BYTE bkColor)
{
    br_Draw8space(fontColor,bkColor,hl_index);//xyy 2003-7-29 17:12
	if(cd_type_loaded==CDDVD)
        psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][string_index_dvd[str_index]]);
	else if(cd_type_loaded==CDROM || cd_type_loaded==CDDA)
		psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][string_index_cd[str_index]]);
    else
        psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][string_index_vcd[str_index]]);
    osd_DrawRegionString(brArea[BR_ITEM_AREA].xStart,brArea[BR_ITEM_AREA].yStart+ITEM_HEIGHT*(hl_index),
                        linebuf,fontColor,bkColor,arc_region_loc.region);
}
/**************************************************************************
 *                                                                        *
 *  Function Name: browse_HL_leftItem                                     *
 *                                                                        *
 *  Purposes:                                                             *
 *    browse HL left item                                                 *
 *  Descriptions:                                                         *
 *    browse HL left item  according  to the index                        *
 *  Arguments:    index:  left item index 0-4                             *
 *                fontColor:display the font's color                      *
 *                pre_bkColor:HL's color                                  *
 *                bkColor:display the background's color                  *
 *                UPDN:0 no HL ;1 HL                                      *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void browse_HL_leftItem(BYTE index,BYTE fontColor,BYTE pre_bkColor,BYTE bkColor,BYTE UPDN)
{
    if(UPDN == 0)//when press down key
    {
    	if(index>1)
		    br_DrawLeftItemStr(index-2,info_index-1,fontColor,pre_bkColor);//xyy 2003-7-29 20:05
	    br_DrawLeftItemStr(index-1,info_index,fontColor,bkColor);//xyy 2003-7-29 20:05
    }
    else if(UPDN == 1)//when press up key
    {
    	if(index < ITEM_PER_PAGE)
		    br_DrawLeftItemStr(index,info_index+1,fontColor,pre_bkColor);//xyy 2003-7-29 20:05
	    br_DrawLeftItemStr(index-1,info_index,fontColor,bkColor);//xyy 2003-7-29 20:05
    }
}
/**************************************************************************
 *                                                                        *
 *  Function Name: br_Draw_TT_info                                        *
 *                                                                        *
 *  Purposes:                                                             *
 *    display the title information                                       *
 *  Descriptions:                                                         *
 *    currently play title/all title                                      *
 *  Arguments:    mmcMode=1:MMC mmcMode=0:SD                              *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/       
void br_Draw_TT_info(void)
{
    BYTE dvd_title_Ns;
    
    if(cd_type_loaded==CDDVD)
    {
		dvd_title=get_tt_info(DISP_TT); 
		dvd_title_Ns = get_tt_info(DISP_TT_Ns); 
	}
	else
	{
/*
		dvd_title=disp_trk_now;
		dvd_title_Ns = cd_total_trk();
*/		 
		dvd_title=disp_trk_now;
		if(cd_type_loaded==CDROM)//xyy 2003-9-11 17:12
			dvd_title_Ns = mp3_file_count();
		else 
			dvd_title_Ns = cd_total_trk(); 
	}
    psprintf(linebuf, "%02d/%02d",dvd_title,dvd_title_Ns);
    if(bBrowseLevel==1 && info_index==0)
	    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart,
	    					linebuf,INFO_FONTCOL,INFO_BKCOL,arc_region_loc.region);	        
	else
	    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart,
	    					linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);	        
}
/**************************************************************************
 *                                                                        *
 *  Function Name: br_Draw_CHP_info                                       *
 *                                                                        *
 *  Purposes:                                                             *
 *    display the chapter information                                     *
 *  Descriptions:                                                         *
 *     currently play chapter/all chapter                                 *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void br_Draw_CHP_info(void)
{
    BYTE dvd_chp_Ns;
	dvd_chapter=get_tt_info(DISP_CH);  
	dvd_chp_Ns = get_tt_info(DISP_CH_Ns);
    psprintf(linebuf, "%02d/%02d",dvd_chapter,dvd_chp_Ns);
	if(bBrowseLevel==1 && info_index==1)
	    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*1,
	    					linebuf,INFO_FONTCOL,INFO_BKCOL,arc_region_loc.region);	        
    else
	    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*1,
	    					linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);	        
}
/**************************************************************************
 *                                                                        *
 *  Function Name: browse_func_up                                         *
 *                                                                        *
 *  Purposes:                                                             *
 *    use ir up_key to control browse function                            *
 *  Descriptions:                                                         *
 *    use ir up_key to control browse function                            *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void browse_func_up(void)
{
    BYTE i,j;
    if(bBrowseLevel==1 || info_index==0)
        return;
    else
        info_index--;
        
    if(info_index<ITEM_PER_PAGE)
    	bInputState = NON_INPUT_STATE;
    HL_index--;
    if((info_index+1)%ITEM_PER_PAGE==0)
    {
        for(i=info_index-(ITEM_PER_PAGE-1),j=0;j<ITEM_PER_PAGE;i++,j++)
            br_DrawLeftItem(i,j,INFO_FONTCOL,INFO_PRE_BKCOL);

        br_DrawRightItem();
        browse_HL_leftItem(ITEM_PER_PAGE,INFO_FONTCOL,INFO_PRE_BKCOL,INFO_BKCOL,1);
    }
    if(HL_index>0)
        browse_HL_leftItem(HL_index,INFO_FONTCOL,INFO_PRE_BKCOL,INFO_BKCOL,1);
    else
        HL_index = ITEM_PER_PAGE;
}
/**************************************************************************
 *                                                                        *
 *  Function Name: browse_func_down                                       *
 *                                                                        *
 *  Purposes:                                                             *
 *    use ir down_key to control browse function                          *
 *  Descriptions:                                                         *
 *    use ir down_key to control browse function                          *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void browse_func_down(void)
{
    BYTE i,j;
    if(bBrowseLevel==1)
        return;
    if((cd_type_loaded==CDROM || cd_type_loaded==CDDA) && info_index==2)//xyy 2003-9-12 14:22
    	return;
    if(cd_type_loaded==CDDVD)
    {
	    if(info_index>=DVD_MAXITEM-1)
	        return;
	    else
	        info_index++;
	}
	else
	{
	    if(info_index>=VCD_MAXITEM-1)
	        return;
	    else
	        info_index++;
	}
    if(info_index>=ITEM_PER_PAGE)
    	bInputState = INPUT_STATE;
    HL_index++;
    if((info_index%ITEM_PER_PAGE==0) && (info_index<DVD_MAXITEM))
    {
        for(i=info_index,j=0;j<ITEM_PER_PAGE;i++,j++)
            br_DrawLeftItem(i,j,INFO_FONTCOL,INFO_PRE_BKCOL);

        br_DrawRightItem();
        browse_HL_leftItem(1,INFO_FONTCOL,INFO_PRE_BKCOL,INFO_BKCOL,0);
    }
    if(HL_index<=ITEM_PER_PAGE)
        browse_HL_leftItem(HL_index,INFO_FONTCOL,INFO_PRE_BKCOL,INFO_BKCOL,0);
    else
        HL_index = 1;
    }
/**************************************************************************
 *                                                                        *
 *  Function Name: init_time_search                                       *
 *                                                                        *
 *  Purposes:                                                             *
 *    init time search and display                                        *
 *  Descriptions:                                                         *
 *    init time search and display                                        *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void init_time_search(void)
{
	bTimeInput = 1;
	goto_time = 0;
	psprintf(linebuf,"%02d:%02d:%02d",0,0,0);
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*(HL_index-1),
                            linebuf,INFO_FONTCOL,INFO_BKCOL,arc_region_loc.region); 
    br_Draw_tmhl(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*(HL_index-1),"_",INFO_FONTCOL,INFO_BKCOL);    
}
/**************************************************************************
 *                                                                        *
 *  Function Name: br_Draw_FBicon                                         *
 *                                                                        *
 *  Purposes:                                                             *
 *    draw the FB icon,likes  <<                                          *
 *  Descriptions:                                                         *
 *    draw the FB icon,likes  <<                                          *
 *  Arguments:  VIOD                                                      *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
#ifdef  SUPPORT_PLAYBACK_ICON
void br_Draw_FBicon(void)
{
	memset(linebuf,0,sizeof(linebuf));
	strcat1(linebuf, OSD_ICON_FB);
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*(HL_index-1),
                            linebuf,INFO_FONTCOL,INFO_BKCOL,arc_region_loc.region);//xyy 2003-8-11 16:25
}
/**************************************************************************
 *                                                                        *
 *  Function Name: br_Draw_FFicon                                         *
 *                                                                        *
 *  Purposes:                                                             *
 *    draw the FF icon,likes  >>                                          *
 *  Descriptions:                                                         *
 *    draw the FF icon,likes  >>                                          *
 *  Arguments:  VIOD                                                      *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void br_Draw_FFicon(void)
{
    strcat1(linebuf, OSD_ICON_FF);
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart+ITEM_WIDTH,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*(HL_index-1),
                            linebuf,INFO_FONTCOL,INFO_BKCOL,arc_region_loc.region); //xyy 2003-8-11 16:25 
}
#else
void br_Draw_FBicon(void){}
void br_Draw_FFicon(void){}
#endif
/**************************************************************************
 *                                                                        *
 *  Function Name: br_Draw_underline                                      *
 *                                                                        *
 *  Purposes:                                                             *
 *    Draw underline                                                      *
 *  Descriptions:                                                         *
 *    Draw underline                                                      *
 *  Arguments:   xStart; yStart;lineColor; bkColor;                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void br_Draw_underline(BYTE xStart, BYTE yStart, BYTE lineColor,BYTE bkColor)
{
    BYTE *s="__";
    bInputState = INPUT_STATE;
    if(bInputIndex==0)
	    osd_DrawRegionString(xStart,yStart,s,lineColor,bkColor,arc_region_loc.region);	 
}
/**************************************************************************
 *                                                                        *
 *  Function Name: exe_time_goto                                          *
 *                                                                        *
 *  Purposes:                                                             *
 *    exe time goto function in browse                                    *
 *  Descriptions:                                                         *
 *    exe time goto function in browse                                    *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
extern void preDealGoto_time(void);
extern void time_trans2hms(void);
extern void exe_timesearch_func(UINT32 goto_ff,UINT32 fail);
void exe_time_goto(void)
{
    index_x=0;
	time_trans2hms();  //xyy  2003-7-29 13:17           

	preDealGoto_time();//xyy 2003-7-29 13:18
	
	exe_timesearch_func(0,0);//xyy 2003-7-29 13:25
	bInputState = NON_INPUT_STATE;
	bTimeInput=0;
}
/**************************************************************************
 *                                                                        *
 *  Function Name: br_Draw_rtSpecialItem                                  *
 *                                                                        *
 *  Purposes:                                                             *
 *   select and exe some function according to different cases            *
 *  Descriptions:                                                         *
 *   select and exe some function according to different cases            *
 *  Arguments:    mmcMode=1:MMC mmcMode=0:SD                              *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void br_Draw_rtSpecialItem(void)//include audio language,sub-picture,repeat_all,multi-angle
{
    br_Draw18space(INFO_FONTCOL,INFO_PRE_BKCOL,HL_index-1);//xyy 2003-7-29 17:32
	br_Draw_FBicon();//xyy 2003-7-29 15:52
    switch(info_index)
    {
    //info_index:the index of string_index_dvd array or string_index_vcd array
    case 2://DVD:STR_OS_TIME ; VCD:STR_OS_TITLETIME ;CD:STR_OS_REP
    	if(cd_type_loaded==CDROM || cd_type_loaded==CDDA)
    		ircmd_repeat_all();
    	break;
	case 3://DVD:STR_OS_SUBTITLE_LANG_SETUP;
		ircmd_sub_picture();
		break;
	case 4://DVD:STR_OS_AUDIO_LANG_SETUP; VCD:STR_OS_REP
		if(cd_type_loaded==CDDVD)
			ircmd_audio_language();
		else
	    	ircmd_repeat_all();
		break;
	case 5://DVD:STR_OS_ANGLE
        ircmd_angle();
		break;
	case 8://DVD:STR_OS_REP
    	ircmd_repeat_all();
		break;
	}    	
	br_Draw_FFicon();//xyy 2003-7-29 16:51
}
/**************************************************************************
 *                                                                        *
 *  Function Name: browse_func_select                                     *          *
 *                                                                        *
 *  Purposes:                                                             *
 *    use enter key to select some function that according to             *  
 *    different cases  ,for example  select CH and TT for DVD.            *
 *    when the key was used ,the HL will be changed                       *
 *  Descriptions:                                                         *
 *    use enter key to select some function that according to             *  
 *    different cases  ,for example  select CH and TT for DVD.            *
 *    when the key was used ,the HL will be changed                       *                         *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void browse_func_select(void)
{
//info_index:the index of string_index_dvd array or string_index_vcd array
//which is defined in file browse_gui.h
    if(info_index==6||info_index==7)//the value of title time and chapter time is not changeable
    	return;
    if(cd_type_loaded==CDDVD)
    {	
	    if(info_index<=1 && bInputIndex<2 && bBrowseLevel==1)
	    	return;
    }
    else
    {	
	    if(info_index==0 && bInputIndex<2 && bBrowseLevel==1)
	    	return;
    }
    if(bBrowseLevel==0)
    {
#if defined(ADJUSTING_ACTION_VALID_RIGHT_NOW)//xyy 2003-9-9 16:10
			action_click = 2;	// alan, 2003/8/28 05:45PM
#else
			action_click = 0;
#endif
//    	action_click = 2;	// alan, 2003/8/28 05:45PM
        switch(info_index)
        {
            case 0://title(DVD) or track(VCD/CD/MP3) information
		        bBrowseLevel = 1;     //xyy 2003-8-11 17:14   
		        br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_PRE_BKCOL);
            	br_Draw_TT_info();
                br_Draw_underline(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*(HL_index-1),UNDERLINECOL,INFO_BKCOL);    
            	break;
            case 1://chaprter(DVD) or playtime(VCD/CD/MP3) information
		        br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_PRE_BKCOL);
	            if(cd_type_loaded==CDDVD)
	            {
			        bBrowseLevel = 1;      //xyy 2003-8-11 17:14  
	            	br_Draw_CHP_info();
	            	br_Draw_underline(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*(HL_index-1),UNDERLINECOL,INFO_BKCOL); //xyy 2003-8-11 16:16   
	 	        }
				else
					init_time_search();
					
               break;
            case 2://playtime(DVD) or title time(VCD) or repeat setup(CD/MP3)information
	            if(cd_type_loaded==CDDVD)
	            {
			        br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_PRE_BKCOL);
            		init_time_search();
            	}
				else if(cd_type_loaded==CDROM || cd_type_loaded==CDDA)//xyy 2003-9-12 13:38
				{
			        bBrowseLevel = 1;//zhaoyanhua add 2003-12-8 9:39
			        br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_PRE_BKCOL);
				    br_Draw_rtSpecialItem();					
				}
           	   	else
           	   		return;
           	   break;
            case 3://sub-title language setup(DVD) or chapter time(VCD) information
	            if(cd_type_loaded==CDDVD)
	            {
	                if(pDSV->dAv_SPST_Ns<2)
	                    return;
			        bBrowseLevel = 1;//zhaoyanhua add 2003-12-8 9:39
			        br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_PRE_BKCOL);
				    br_Draw_rtSpecialItem();
	            }
	            else
	            	return;                          
                
                break;    
            case 4://audio language setup(DVD) or repeat setup(VCD) information
            if(cd_type_loaded==CDDVD)
            {
            	if(pDSV->dAv_AST_Ns<=1)
            		return;
		    }
		    else
		    {
		    	if( IsPBCOn() )
		    		return;
				}            	
		        bBrowseLevel = 1;//zhaoyanhua add 2003-12-8 9:39
		        br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_PRE_BKCOL);
				br_Draw_rtSpecialItem();
                break;
            case 5://multi-angle(only DVD)information
            	if(get_angle_Ns()<1)
            		return;
                bBrowseLevel = 1;//zhaoyanhua add 2003-12-8 9:39
		        br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_PRE_BKCOL);
			    br_Draw_rtSpecialItem();
                break;
            case 8://repeat setup(DVD)information
		        bBrowseLevel = 1;//zhaoyanhua add 2003-12-8 9:39
		        br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_PRE_BKCOL);
			    br_Draw_rtSpecialItem();
                break;
                
        }
        bBrowseLevel = 1;        
    }
    else if(bBrowseLevel == 1)
    {
        br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_BKCOL);//xyy 2003-8-11 16:08
        switch(info_index)
        {
            case 0://title(DVD) or track(VCD/CD/MP3) information
                if(bInputIndex==1)
                    return;
                if(bInputIndex > 1)
                {
                    bInputIndex = 0;
                    if(cd_type_loaded==CDDVD)
                    {
	                    if(info_index==0)
	                    	dvd_chapter = 1;
	                    
	                    if(UOP_check(UOP_PTT_PS)&&(dvd_chapter==1))
				             dvd_chapter = 0;//TT play,terry,3-8-23 19:35
				             
		                ircmd_post_func(CMD_FUNC|CMD_PTT_PLAY);
	                }
                    else
	                    ircmd_post_func(CMD_SELECT | dvd_title);
                    bInputState = NON_INPUT_STATE;    
                }
                break;
            case 1://chaprter(DVD) or playtime(VCD/CD/MP3) information
            	if(cd_type_loaded==CDDVD)
            	{
                if(bInputIndex==1)
                    return;
                if(bInputIndex > 1)
                {
                    bInputIndex = 0;
                    
                    if(UOP_check(UOP_PTT_PS)&&(dvd_chapter==1))
				      dvd_chapter = 0;//TT play,terry,3-8-23 19:35
				      
	                ircmd_post_func(CMD_FUNC|CMD_PTT_PLAY);
	                    bInputState = NON_INPUT_STATE;    
                }
                }
                else
                	exe_time_goto();
                break;
            case 2://playtime(DVD) or title time(VCD) or repeat setup(CD/MP3)information
	            if(cd_type_loaded==CDDVD)
	            	exe_time_goto();
	            else
                	br_DrawRightItem();
                break;
            case 3://sub-title language setup(DVD) or chapter time(VCD) information
            case 4://audio language setup(DVD) or repeat setup(VCD) information
            case 5://multi-angle(only DVD)information
            case 8://repeat setup(DVD)information
                br_DrawRightItem();
                break;
        }
        bBrowseLevel = 0;
    }
}
/**************************************************************************
 *                                                                        *
 *  Function Name: browse_func_clear                                      *
 *                                                                        *
 *  Purposes:                                                             *
 *    clear the unuseful informaton which had been selected               *
 *  Descriptions:                                                         *
 *    clear the unuseful informaton which had been selected               *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
#ifdef	CLEAR_KEY_IN_WINDOW	//Maoyong 2004.02.18
void	browse_func_clear(void)
{
	//DVD not in CHP, TT, CHP and TT time item, no use
	if(cd_type_loaded == CDDVD)
	{
		if((info_index != 5)&&(info_index != 6)&&(info_index != 0)&&(info_index != 1))
			return;
	}
	else		//CDROM, CDVCD..., not DVD
	{
		if( (info_index != 0) && (info_index != 1) && (info_index != 2) ) 	
			return;	
	}	
	index_x=0;
	bBrowseLevel = 0;
	bInputState = NON_INPUT_STATE;
    bInputIndex = 0;
	browse_func_select();	
}	
#endif
UINT32 ten_power(BYTE exponent)
{
	UINT32 temp=1,i;
	for(i=0;i<exponent;i++)
		temp = temp*10;
	return temp;
}
/**************************************************************************
 *                                                                        *
 *  Function Name: browse_func_left                                       *
 *                                                                        *
 *  Purposes:                                                             *
 *    use ir left_key to control browse function                          *
 *  Descriptions:                                                         *
 *    use ir left_key to control browse function                          *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void browse_func_left(void)
{
    if(bBrowseLevel==0)
        return;
    if((cd_type_loaded==CDDVD && info_index <= 1) || (cd_type_loaded!=CDDVD && info_index==0))
    {
        bInputState = NON_INPUT_STATE;
        bInputIndex = 0;
        bBrowseLevel = 0;
        UpdateTT_CHP_info();
        br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_BKCOL);//xyy 2003-8-11 17:06
    }
    else if((cd_type_loaded==CDDVD && info_index == 2) || (cd_type_loaded!=CDDVD && info_index==1))
    {
        br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_BKCOL);//xyy 2003-8-11 17:06
    	br_DrawRightItem();
        bBrowseLevel = 0;
        bTimeInput = 0;
        index_x = 0; // alan, 2003/9/5 02:16¤U¤È
    }
    if(((cd_type_loaded==CDROM || cd_type_loaded==CDDA)&& info_index==2) || (cd_type_loaded!=CDROM && info_index>2))//xyy 2003-9-12 14:05
    {	
    	action_click=1;
    	br_Draw_rtSpecialItem();
	    	action_click=0;
	}
}
/**************************************************************************
 *                                                                        *
 *  Function Name: browse_func_right                                      *
 *                                                                        *
 *  Purposes:                                                             *
 *    use ir right_key to control browse function                         *
 *  Descriptions:                                                         *
 *    use ir right_key to control browse function                         *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void browse_func_right(void)
{
    if(bBrowseLevel==0)
        return;
    if(index_x==5)
    	return;
/*
    if((cd_type_loaded==CDROM || cd_type_loaded==CDDA) && info_index==2)//xyy 2003-9-12 13:43
    {
	    	action_click=1;
	    br_Draw_rtSpecialItem();
	    	action_click=0;   	
    }
*/
    if(info_index>=2)
    {	
	    	action_click=1;
	    br_Draw_rtSpecialItem();
	    	action_click=0;
	}
}
/**************************************************************************
 *                                                                        *
 *  Function Name: time_input                                             *
 *                                                                        *
 *  Purposes:                                                             *
 *    input the search time                                               *
 *  Descriptions:                                                         *
 *    input the search time                                               *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
extern void search_add_num(int *v,int pos);
void time_input(void)
{
	UINT8 hour,minute,second;
	tm2hms(disc_time,&hour,&minute,&second);
	
    search_add_num(&goto_time, 5 - index_x);
    psprintf(linebuf, "%01d",ir_select_number);
    
    BYTE xStart;
    xStart = brArea[BR_CONTENT_AREA].xStart + ITEM_WIDTH * (index_x+index_x/2)/2;
    osd_DrawRegionString(xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*(HL_index-1),linebuf,
    					INFO_FONTCOL,INFO_BKCOL,arc_region_loc.region);
    if(index_x<5)					
    br_Draw_tmhl(brArea[BR_CONTENT_AREA].xStart+ITEM_WIDTH * HL_loc[index_x+1]/2,
    			brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*(HL_index-1),"_",INFO_FONTCOL,INFO_BKCOL);    
	index_x++;	
}
/**************************************************************************
 *                                                                        *
 *  Function Name: browse_func_input                                      *
 *                                                                        *
 *  Purposes:                                                             *
 *   input  some information,TT and CH                                    *
 *  Descriptions:                                                         *
 *   input  some information,TT and CH                                    *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void browse_func_input(void)
{
	if(bBrowseLevel == 0)//xyy 2003-9-15 15:51
		return;
		
    if(info_index>2 || bInputIndex>1 || index_x>5)
        return;
    if(ir_select_number == 10)
        ir_select_number = 0;
	
    if(info_index==0)
    {
        int iTitle,tt;
    	if(cd_type_loaded==CDDVD)
	        iTitle = get_tt_info(DISP_TT_Ns);
	    else if(cd_type_loaded==CDROM)//xyy 2003-9-11 17:07
			iTitle = mp3_file_count();
	    else
	    	iTitle = cd_total_trk();
        
        tt = dvd_title;
        search_add_num(&tt, 1 - bInputIndex);
        dvd_title=tt;
        dvd_chapter = 1;//TT play,terry,3-8-23 19:35
        if((bInputIndex == 0) && (ir_select_number > iTitle/10))
            return;
        if(( bInputIndex == 1) && (dvd_title/10 == iTitle/10) && (ir_select_number > iTitle%10))
            return;
        psprintf(linebuf, "%01d",ir_select_number);
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart + ITEM_WIDTH * bInputIndex/2,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*(HL_index-1),
        					linebuf,INFO_FONTCOL,INFO_BKCOL,arc_region_loc.region);
	    if(bInputIndex<2)
	        bInputIndex++;
    }
    else if(info_index==1)
    {
    	if(cd_type_loaded==CDDVD)
    {
	        int iChapter,ch=dvd_chapter;
	        iChapter = get_tt_info(DISP_CH_Ns);
			
		    search_add_num(&ch, 1 - bInputIndex);
	        dvd_chapter = ch;
	        
	        if((bInputIndex == 0) && (ir_select_number > iChapter/10))
	            return;
	        if(( bInputIndex == 1) && (dvd_chapter/10 == iChapter/10) && (ir_select_number > iChapter%10))
	            return;
	        psprintf(linebuf, "%01d",ir_select_number);
	        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart + ITEM_WIDTH * bInputIndex/2,
	                          brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*(HL_index-1),linebuf,INFO_FONTCOL,INFO_BKCOL,arc_region_loc.region);
				    if(bInputIndex<2)
				        bInputIndex++;
	    }
	    else
	    	time_input();   
    }
    else if(info_index==2)
    {
    	if(bBrowseLevel==0)
    		return;
        if(cd_type_loaded==CDDVD)
    		time_input();
    }
}

void br_Draw_tmhl(BYTE xStart, BYTE yStart, char *s,BYTE fontCol,BYTE bkColor)
{
    osd_DrawRegionString(xStart,yStart,s,fontCol,bkColor,arc_region_loc.region);	 
}
/**************************************************************************
 *                                                                        *
 *  Function Name: exe_browse_func                                        *
 *                                                                        *
 *  Purposes:                                                             *
 *    exe browse function which has been selected                         *
 *  Descriptions:                                                         *
 *    exe browse function which has been selected                         *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void exe_browse_func(void)
{
    int j;

    browse_show_function();
    //restore default aspect
    set_video_aspect();
    startup_vpp_now();
    // 70,90 ~ 429,332
#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW //zhaoyanhua add 2003-11-30 15:29
    if(getVPP_TVsystem())
        set_vpp_disp_window(70,143,360,237);
        //set_vpp_disp_window(64,124,360,220);		 		  //70,143,360,237zhaoyanhua add 2003-11-30 15:06
    else
    set_vpp_disp_window(70,76,360,237);		 //axel 2003/11/21 07:19pm 70,92,360,238 alan, 2003/8/26 10:43PM
#else
    set_vpp_disp_window(70,92,360,238);		 //axel 2003/11/21 07:19pm 70,92,360,238 alan, 2003/8/26 10:43PM
#endif

//    vpp_set_bg_color(0x30,0xb070);
    sup_disable();
    brArea[BR_ITEM_AREA].yStart=brArea[BR_CONTENT_AREA].yStart=58;
    info_index = 0;//info_index:the index of string_index_dvd array or string_index_vcd array
    HL_index = 1;//HL_index(0~4): the location index of highlight
    index_x=0;//only time search function use this varialbe
    
    for(j=0;j<ITEM_PER_PAGE;j++)
    {
        br_DrawLeftItem(j,j,INFO_FONTCOL,INFO_PRE_BKCOL);
    }
    browse_HL_leftItem(HL_index,INFO_FONTCOL,INFO_PRE_BKCOL,INFO_BKCOL,0);
    
	br_DrawRightItem();
	
	//Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 9:13
    SetFullscrnCmdFuncPtr( browse_func_up, browse_func_down, browse_func_left,
                           browse_func_right, browse_func_select);
}

/**************************************************************************
 *                                                                        *
 *  Function Name: exit_browse_func                                       *
 *                                                                        *
 *  Purposes:                                                             *
 *    exit browse                                                         *
 *  Descriptions:                                                         *
 *    exit browse                                                         *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void
exit_browse_func(void)
{
    browse_show_function();

    bBrowseLevel    = 0;
    full_scrn       = 0;
    vpp_zoom        = 0;
//    total_play_time = 0;//xyy 2003-9-12 15:48
#ifdef CD_PLAYER
    if(cd_type_loaded==CDDA)
        osd_init_cdplayer();
    else
    	osd_init();
#else
	#ifdef DYNAMIC_SPECTRUM    //fengjl  3-10-30 12:53
  	if (band_onoff)  		
  		Show3dspectrum();
  	else		
#endif
    osd_init();
#endif
//    vpp_set_bg_color(0x10,0x8080);
    set_vpp_disp_window(0,0,0,0);

    //restore default aspect
    set_video_aspect();
    startup_vpp();

    setVPP_DoItNow();

    sup_enable();
}

/**************************************************************************
 *                                                                        *
 *  Function Name: br_Draw_AGL_info                                       *
 *                                                                        *
 *  Purposes:                                                             *
 *   draw angle information for dvd                                       *
 *  Descriptions:                                                         *
 *   draw angle information for dvd                                       *
 *  Arguments:  VOID                                                      *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void br_Draw_AGL_info(void)
{
    action_click = 2; //Jeff add 20031006, to avoid "GOTO" automatic toggled when high-light focus on "GOTO"
    ircmd_angle();//xyy 2003-7-29 15:14
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart,
                            linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
}
/**************************************************************************
 *                                                                        *
 *  Function Name: br_Draw_TT_time                                        *
 *                                                                        *
 *  Purposes:                                                             *
 *    display  title's time  that currently play                          *
 *  Descriptions:                                                         *
 *    display TT time                                                     *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void br_Draw_TT_time(void)
{
	UINT8 hour,minute,second,offset;
	if(cd_type_loaded==CDDVD)
		offset = ITEM_HEIGHT*1;
	else
		offset = ITEM_HEIGHT*2;
	tm2hms(disc_time,&hour,&minute,&second);
	psprintf(linebuf,"%02d:%02d:%02d",hour,minute,second);
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+offset,
                            linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
}
/**************************************************************************
 *                                                                        *
 *  Function Name: br_Draw_CHP_time                                       *                                                                        *
 *  Purposes:                                                             *
 *    display  chapter's time  that currently play                        *
 *  Descriptions:                                                         *
 *    display  chapter's time  that currently play                        *
 *  Arguments:    VOID                                                    *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void br_Draw_CHP_time(void)
{
	UINT8 hour,minute,second,offset;
	if(cd_type_loaded==CDDVD)
		offset = ITEM_HEIGHT*2;
	else
		offset = ITEM_HEIGHT*3;
	if(cd_type_loaded == CDSVCD)
		tm2hms((dNx_pg_tm-dPg_tm)/PLAY_SPEED,&hour,&minute,&second);
	else	
		tm2hms(dNx_pg_tm-dPg_tm,&hour,&minute,&second);	
	psprintf(linebuf,"%02d:%02d:%02d",hour,minute,second);
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+offset,
                            linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
}
/**************************************************************************
 *                                                                        *
 *  Function Name: br_Draw_TT_playtm                                      *
 *                                                                        *
 *  Purposes:                                                             *
 *    display current time                                                *
 *  Descriptions:                                                         *
 *    display current time                                                *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void br_Draw_TT_playtm(void)
{
	UINT8 hour,minute,second,offset;
	if(cd_type_loaded==CDDVD)
		offset = ITEM_HEIGHT*2;
	else
		offset = ITEM_HEIGHT*1;
	tm2hms(disp_time,&hour,&minute,&second);
	psprintf(linebuf,"%02d:%02d:%02d",hour,minute,second);
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+offset,
                            linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
}
/**************************************************************************
 *                                                                        *
 *  Function Name: br_DrawRightItem                                       *
 *                                                                        *
 *  Purposes:                                                             *
 *    init the right item string in the gui                               *
 *  Descriptions:                                                         *
 *    init the right item string in the gui                               *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void br_DrawRightItem(void)
{
	osd_draw_rect(brArea[BR_CONTENT_AREA].xStart*8, brArea[BR_CONTENT_AREA].yStart*4, 
					brArea[BR_CONTENT_AREA].xSize*8, brArea[BR_CONTENT_AREA].ySize*4, INFO_PRE_BKCOL); 

#if defined(ADJUSTING_ACTION_VALID_RIGHT_NOW)//xyy 2003-9-9 16:10
			action_click = 2;	// alan, 2003/8/28 05:45PM
#else
			action_click = 0;
#endif
    if(info_index<ITEM_PER_PAGE)
    {
    	br_Draw_TT_info();
    	br_Draw_TT_playtm();
    	
	if(cd_type_loaded==CDDVD)
    	{
	    	br_Draw_CHP_info();
	
			action_click=2;	//alan, 2003/8/28 05:45PM
			ircmd_sub_picture();
		    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*3,
		    					linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);	
			
			action_click=2;	//alan, 2003/8/28 05:45PM
			ircmd_audio_language();
	        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*4,
	                                linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
		}
		else if(cd_type_loaded==CDROM || cd_type_loaded==CDDA)//xyy 2003-9-12 13:34
		{
			memset(linebuf,0,100);
			ircmd_repeat_all();
	        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*2,
	                                linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
				
		}
	else
		{
			br_Draw_TT_time();
			br_Draw_CHP_time();
			
			action_click = 2;	// alan, 2003/8/28 05:45PM
			memset(linebuf,0,sizeof(linebuf));
			ircmd_repeat_all();
	        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*4,
	                                linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
		}
	}
	if(cd_type_loaded==CDDVD)
		if((info_index>=ITEM_PER_PAGE)&&(info_index<ITEM_PER_PAGE*2))
		{
			br_Draw_AGL_info();
			
			br_Draw_TT_time();
			br_Draw_CHP_time();

			action_click = 2;	// alan, 2003/8/28 05:45PM
			memset(linebuf,0,sizeof(linebuf));
			ircmd_repeat_all();
	        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*3,
	                                linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
		} 
}	
/**************************************************************************
 *                                                                        *
 *  Function Name: br_Draw_TT_progress                                    *
 *                                                                        *
 *  Purposes:                                                             *
 *    show the TT   progress                                              *
 *  Descriptions:                                                         *
 *    show the TT   progress                                              *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void br_Draw_TT_progress(void)
{
	UINT16 num,time_step,bar_step,xLen;
//	printf("br_Draw_TT_progress()\n");
	
	if(cd_type_loaded==CDROM)//xyy 2003-9-12 15:09
	{
		if((dNx_pg_tm-dPg_tm)<update_definition)
			update_definition = (dNx_pg_tm-dPg_tm)/2;
	
		if((PlayBackLength * 16/ Mp3_kbitrate)<update_definition)
			update_definition = (PlayBackLength * 16/ Mp3_kbitrate)/2;
		time_step = (PlayBackLength * 16/ Mp3_kbitrate)/update_definition;
		osd_draw_rect(BAR_XSTART+BAR_EDGE,TT_BAR_YSTART+BAR_EDGE,PROGRESS_BAR_LEN-2*BAR_EDGE,PROGRESS_BAR_YLEN,6);
		
		num = (disp_time)/time_step;
		bar_step = num*((PROGRESS_BAR_LEN-2*BAR_EDGE)/update_definition);
		xLen = PROGRESS_BAR_LEN-2*BAR_EDGE;
		
		if(bar_step>xLen)
			osd_draw_rect(BAR_XSTART+BAR_EDGE,TT_BAR_YSTART+BAR_EDGE,xLen,PROGRESS_BAR_YLEN,BAR_COL);
		else
			osd_draw_rect(BAR_XSTART+BAR_EDGE,TT_BAR_YSTART+BAR_EDGE,bar_step,PROGRESS_BAR_YLEN,BAR_COL);
	}else{
	time_step = disc_time/update_definition;
	if(cd_type_loaded==CDSVCD)
		time_step = time_step/PLAY_SPEED;
		osd_draw_rect(BAR_XSTART+BAR_EDGE,TT_BAR_YSTART+BAR_EDGE,PROGRESS_BAR_LEN-2*BAR_EDGE,PROGRESS_BAR_YLEN,6);
	
	if(cd_type_loaded==CDDVD)
		num = disp_time/time_step;
	else if(cd_type_loaded==CDSVCD)
		num = (dPg_tm/PLAY_SPEED+disp_time)/time_step;
		else if(cd_type_loaded==CDROM)//xyy 2003-9-12 16:03
	//		num = (total_play_time+disp_time)/time_step;
			num = (disp_trk_now * (PlayBackLength * 16/ Mp3_kbitrate)+disp_time)/time_step;
	else
		num = (dPg_tm+disp_time)/time_step;
		
		bar_step = num*((PROGRESS_BAR_LEN-2*BAR_EDGE)/update_definition);
		xLen = PROGRESS_BAR_LEN-2*BAR_EDGE;
	
	if(bar_step>xLen)
			osd_draw_rect(BAR_XSTART+BAR_EDGE,TT_BAR_YSTART+BAR_EDGE,xLen,PROGRESS_BAR_YLEN,BAR_COL);
	else
			osd_draw_rect(BAR_XSTART+BAR_EDGE,TT_BAR_YSTART+BAR_EDGE,bar_step,PROGRESS_BAR_YLEN,BAR_COL);
	}
}
/**************************************************************************
 *                                                                        *
 *  Function Name: br_Draw_TT_progress                                    *
 *                                                                        *
 *  Purposes:                                                             *
 *    show the CH   progress                                              *
 *  Descriptions:                                                         *
 *    show the CH   progress                                              *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void br_Draw_CHP_progress(void)
{
	UINT16 num,time_step,bar_step,xLen;
	
	if((dNx_pg_tm-dPg_tm)<update_definition)
		update_definition = (dNx_pg_tm-dPg_tm)/2;

	if(cd_type_loaded==CDROM)//xyy 2003-9-12 15:09
	{
		if((PlayBackLength * 16/ Mp3_kbitrate)<update_definition)
			update_definition = (PlayBackLength * 16/ Mp3_kbitrate)/2;
		time_step = (PlayBackLength * 16/ Mp3_kbitrate)/update_definition;
	}
	else
	{
		if((dNx_pg_tm-dPg_tm)<update_definition)
			update_definition = (dNx_pg_tm-dPg_tm)/2;
		time_step = (dNx_pg_tm-dPg_tm)/update_definition;
	}

	if(cd_type_loaded==CDSVCD)
		time_step = time_step/PLAY_SPEED;

	osd_draw_rect(BAR_XSTART+BAR_EDGE,CHP_BAR_YSTART+BAR_EDGE,PROGRESS_BAR_LEN-2*BAR_EDGE,PROGRESS_BAR_YLEN,6);
	
	if(cd_type_loaded==CDDVD)
		num = (disp_time-dPg_tm)/time_step;
	else
		num = (disp_time)/time_step;
	bar_step = num*((PROGRESS_BAR_LEN-2*BAR_EDGE)/update_definition);
	xLen = PROGRESS_BAR_LEN-2*BAR_EDGE;
	
	if(bar_step>xLen)
		osd_draw_rect(BAR_XSTART+BAR_EDGE,CHP_BAR_YSTART+BAR_EDGE,xLen,PROGRESS_BAR_YLEN,BAR_COL);
	else
		osd_draw_rect(BAR_XSTART+BAR_EDGE,CHP_BAR_YSTART+BAR_EDGE,bar_step,PROGRESS_BAR_YLEN,BAR_COL);
}

/**************************************************************************
 *                                                                        *
 *  Function Name: updateRepeatMode                                       *
 *                                                                        *
 *  Purposes:                                                             *
 *    update repeat mode in NEW_STYLE_WINDOW when USERS enter REPEAT      *
 *  Descriptions:                                                         *
 *    update repeat mode in NEW_STYLE_WINDOW when USERS enter REPEAT      *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/

/*
 * update repeat mode in NEW_STYLE_WINDOW when USERS enter REPEAT
 *
 * zhaoyanhua  add 2003-12-7 18:45
 */
void updateRepeatMode(void)
{
    //when it is in right item.not draw REPREAT MODE infomation
    if(((cd_type_loaded==CDROM) || (cd_type_loaded==CDDA)) &&(!((info_index == 2)&&(bBrowseLevel))))
    {    	             
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*2,
	                                "        ",INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*2,
	                                linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
        
    }
    else if((cd_type_loaded == CDDVD)&&(!((info_index == 8)&&(bBrowseLevel))))
    {
        if(info_index > ITEM_PER_PAGE) 
        {    
            osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*3,
	                                "        ",INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);     
         
            osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*3,
	                                linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
         }
         
    }
    else if(((cd_type_loaded == CDVCD10)||(cd_type_loaded ==CDSVCD)||(cd_type_loaded == CDVCD20)) &&(!((info_index == 3)&&(bBrowseLevel))) )
    {
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*4,
	                                "        ",INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);     
         
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*4,
	                                linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);        
    }
}
/**************************************************************************
 *                                                                        *
 *  Function Name: updateAudioLanguage                                    *
 *                                                                        *
 *  Purposes:                                                             *
 *    update auido mode in NEW_STYLE_WINDOW when USERS enter "AUDIO"      *
 *  Descriptions:                                                         *
 *    update auido mode in NEW_STYLE_WINDOW when USERS enter "AUDIO"      *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
/*
 * update auido mode in NEW_STYLE_WINDOW when USERS enter "AUDIO"
 *
 * zhaoyanhua  add 2003-12-7 18:45
 */
void updateAudioLanguage(void)
{
    //clear display words //8 SPACE
    
    if(!((info_index == 4)&&(bBrowseLevel)))
    {          
        
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*4,
	                    "       ",INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
   
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*4,
	                    linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
 }   
}
/**************************************************************************
 *                                                                        *
 *  Function Name: updateSubtitle                                         *
 *                                                                        *
 *  Purposes:                                                             *
 *    update subtitle in NEW_STYLE_WINDOW when USERS enter SUBTITLE       *
 *  Descriptions:                                                         *
 *    update subtitle in NEW_STYLE_WINDOW when USERS enter SUBTITLE       *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
/*
 * update subtitle in NEW_STYLE_WINDOW when USERS enter SUBTITLE
 *
 * zhaoyanhua  add 2003-12-7 18:45
 */
void updateSubtitle(void)
{
    //clear the current display words.8 SPACE 
    if(!((info_index == 3)&&(bBrowseLevel)))
    {        
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*3,
		    		     "          ",INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);
    
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*3,
		    		     linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);	
    }  
}

/**************************************************************************
 *                                                                        *
 *  Function Name: UpdateTT_CHP_info                                      *
 *                                                                        *
 *  Purposes:                                                             *
 *       update the title and chapter information                         *
 *  Descriptions:                                                         *
 *      exe this function,the TT and CH bar will be changed with time     *
 *  Arguments:    VOID                                                    *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void UpdateTT_CHP_info(void)
{
//	printf("run into UpdateTT_chp_info\n");
//	if(cd_type_loaded==CDROM)//xyy 2003-9-12 15:48
//		total_play_time = total_play_time + (PlayBackLength * 16/ Mp3_kbitrate);
    if(bInputState == NON_INPUT_STATE)
    {
        br_Draw_TT_info();
        if(cd_type_loaded==CDDVD)
	        br_Draw_CHP_info();
    }
    
    if(cd_type_loaded==CDDVD)
    {
    	if((info_index>=ITEM_PER_PAGE))
	    {
	    	br_Draw_TT_time();
	    	br_Draw_CHP_time();
	    }
	}
	else if(cd_type_loaded > CDROM && cd_type_loaded <= CDSVCD)
	{
	    	br_Draw_TT_time();
	    	br_Draw_CHP_time();
	}
    if((info_index==ITEM_PER_PAGE)&&(bBrowseLevel==0))
    	br_Draw_AGL_info();

	if(bTimeInput == 0 && info_index<ITEM_PER_PAGE)
	    br_Draw_TT_playtm();
	
	br_Draw_TT_progress();
	br_Draw_CHP_progress();
}
/**************************************************************************
 *                                                                        *
 *  Function Name: br_DrawleftItem                                       *
 *                                                                        *
 *  Purposes:                                                             *
 *    init the left item string in the gui                                *
 *  Descriptions:                                                         *
 *    init the left item string in the gui                                *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void br_DrawLeftItem(BYTE item_index,BYTE loc_index,BYTE fontColor,BYTE bkColor)
{
    br_Draw8space(fontColor,bkColor,loc_index);//xyy 2003-7-29 17:12
    if(item_index>=DVD_MAXITEM)
    	return;
    if((cd_type_loaded==CDROM || cd_type_loaded==CDDA) && item_index>=CD_MAXITEM)
    	return;           //xyy 2003-9-12 13:16
//        strcpy(linebuf,"        ");
    else
    {
    	if(cd_type_loaded==CDDVD)
	        psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][string_index_dvd[item_index]]);
		else if(cd_type_loaded==CDROM || cd_type_loaded==CDDA)
			psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][string_index_cd[item_index]]);
	    else
	        psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][string_index_vcd[item_index]]);
	}
    osd_DrawRegionString(brArea[BR_ITEM_AREA].xStart,brArea[BR_ITEM_AREA].yStart+ITEM_HEIGHT*loc_index,
                        linebuf,fontColor,bkColor,arc_region_loc.region);
}
/**************************************************************************
 *                                                                        *
 *  Function Name: exe_show_time                                          *
 *                                                                        *
 *  Purposes:                                                             *
 *    draw the TT and CH   progress bar                                   *
 *  Descriptions:                                                         *
 *    draw the TT and CH   progress bar                                   *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void exe_show_time(void)
{
    psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_TT]);
	
    osd_DrawRegionString(50,ITEM_HEIGHT*2+ITEM_HEIGHT/2,linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);
    psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_CHP]);
    osd_DrawRegionString(50,ITEM_HEIGHT*5/*+ITEM_HEIGHT/2*/,linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);

	osd_draw_rect(BAR_XSTART,TT_BAR_YSTART,PROGRESS_BAR_LEN,BAR_YLEN,BAR_BKCOL);
	osd_draw_rect(BAR_XSTART,CHP_BAR_YSTART,PROGRESS_BAR_LEN,BAR_YLEN,BAR_BKCOL);
	
	br_Draw_TT_progress();
	br_Draw_CHP_progress();
	
}
/**************************************************************************
 *                                                                        *
 *  Function Name: UpdateAngleInfo                                        *
 *                                                                        *
 *  Purposes:                                                             *
 *    update angle when USERS enter ANGLE                                 *
 *  Descriptions:                                                         *
 *   update angle when USERS enter ANGLE                                  *
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
/*
 * update angle when USERS enter ANGLE
 * 
 * fengjl  add 2003-12-10 11:50
 */
void UpdateAngleInfo(void)
{
    
    if(!((info_index == 4)&&(bBrowseLevel)))
    {
        
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*0,
                            "          ",INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); //xyy 2004-3-4
        
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*0,
                            linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);   //xyy 2004-3-4
        
    }
}


#endif//NEW_STYLE_WINDOW

#endif// MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
