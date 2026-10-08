/*****************************************************\
HISTORY:

Creater: xiongyuyue
Date   : 2003/6/28 
Description: browse function using 

modifier : zhaoyanhua
date: 2003-12-6 16:18
 changed the some function of NEW_STYLE_WINDOw:
 VCD: DELETE ITEM : playtime  
      ADD ITEM:   : disctime¡¢track time
 DVD: DELETE ITEM : time
 modifier : linrc 
 data: 2005-10-22 14:10
 changed for NEW_OSD_DRIVE & warring message....
 
\*****************************************************/

#ifndef DVDRELEASE
//#define BROWSE_DBG
#endif

#include    "vpp_if.h"

#ifdef DYNAMIC_SPECTRUM     //fengjl  3-10-30 12:34
extern BYTE band_onoff;
extern void Show3dspectrum(void); //axel 2003/12/2 11:31pm
#endif

#define browse_puts()           ((void)0)
#define browse_show_function()  ((void)0)

#if 1
#ifdef  BROWSE_DBG
#include "sio.h"
#include "emuio.h"
#undef  browse_puts
#undef  browse_show_function
#define browse_puts             puts_w
#define browse_show_function()  do {browse_puts(__FUNCTION__); browse_puts("\n");} while (0)
#endif
#endif
/////////////////////////////////////////////////////////////////////////
//wanghaoying 2003-8-12 19:50 added
extern void set_video_aspect(void);
extern void startup_vpp_now(void);
//extern void set_vpp_disp_window(UINT32,UINT32,UINT32,UINT32);
/////////////////////////////////////////////////////////////////////////
extern UINT16 mp3_file_count(void);   //axel 2003/12/2 11:30pm
///////////////////////////////////////////////////////////////////
//zhaoyanhua add 2003-12-18 15:39
extern BYTE	memory_config_saved;//reset.h
extern BYTE GetConfigMode(int config);//memcfg.c
extern void   osd_init_newstyle_window_PAL(void);//osd1.c
extern void   osd_init_newstyle_window_NTSC(void);//osd1.c
///////////////////////////////////////////////////////////////////
#ifdef NEWSTYLE_WINDOW          //xiongyuyue 
BYTE bInputState = NON_INPUT_STATE;
int bInputIndex = 0;   //for title/chapter search function,
BYTE bTimeInput = 0;
BYTE update_definition = 40;
extern UINT32 PlayBackLength;

void br_Draw8space(BYTE fontColor,BYTE bkColor,BYTE index)
{//erase displayed word and disp new word when press updown key(for draw left item)
    strcpy(linebuf,"            ");  //fengjl changed space from 8 to 12   3-11-24 18:52
    osd_DrawRegionString(brArea[BR_ITEM_AREA].xStart,brArea[BR_ITEM_AREA].yStart+ITEM_HEIGHT*index,
                        linebuf,fontColor,bkColor,arc_region_loc.region);
}

void br_Draw18space(BYTE fontColor,BYTE bkColor,BYTE index)
{//erase displayed word and disp new word when press updown key(for draw right item)
    strcpy(linebuf,"                  ");
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*index,
                        linebuf,fontColor,bkColor,arc_region_loc.region);
}	

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

void browse_func_up(void)
{
    BYTE i,j;
    if(bBrowseLevel==1 || info_index==0)
        return;
    else
        info_index--;
        
    if((info_index<ITEM_PER_PAGE)||(info_index == 5)|| (info_index == 6))
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
    {
    	if((info_index == 5)|| (info_index == 6))
    	    bInputState = NON_INPUT_STATE;//zhaoyanhua modify2003-12-7 14:54 
        else
            bInputState = INPUT_STATE;
    }
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

void init_time_search(void)
{
	bTimeInput = 1;
	goto_time = 0;
	psprintf(linebuf,"%02d:%02d:%02d",0,0,0);
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*(HL_index-1),
                            linebuf,INFO_FONTCOL,INFO_BKCOL,arc_region_loc.region); 
    br_Draw_tmhl(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*(HL_index-1),"_",INFO_FONTCOL,INFO_BKCOL);    
}

#ifdef  SUPPORT_PLAYBACK_ICON
void br_Draw_FBicon(void)
{
	memset(linebuf,0,sizeof(linebuf));
	strcat1(linebuf, OSD_ICON_FB);
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*(HL_index-1),
                            linebuf,INFO_FONTCOL,INFO_BKCOL,arc_region_loc.region);//xyy 2003-8-11 16:25
}

void br_Draw_FFicon(void)
{
    strcat1(linebuf, OSD_ICON_FF);
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart+ITEM_WIDTH,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*(HL_index-1),
                            linebuf,INFO_FONTCOL,INFO_BKCOL,arc_region_loc.region); //xyy 2003-8-11 16:25 
}
#endif

void br_Draw_underline(BYTE xStart, BYTE yStart, BYTE lineColor,BYTE bkColor)
{
    BYTE *s="__";
    bInputState = INPUT_STATE;
    if(bInputIndex==0)
	    osd_DrawRegionString(xStart,yStart,s,lineColor,bkColor,arc_region_loc.region);	 
}

extern void preDealGoto_time(void);
extern void time_trans2hms(void);
extern void exe_timesearch_func(UINT32 goto_ff,UINT32 fail);
void exe_time_goto(void)
{
    #define DISCTIME_SEARCH     1
    #define TRACKTIME_SEARCH    2
    
    BYTE  search_mode = 0;
    
    index_x=0;
	time_trans2hms();  //xyy  2003-7-29 13:17           

	preDealGoto_time();//xyy 2003-7-29 13:18
	
	if(cd_type_loaded != CDDVD)
	{
	    switch(info_index)
	    {
	        case 1: 
	            search_mode = DISCTIME_SEARCH;
	            break;
	        case 2:
	            search_mode = TRACKTIME_SEARCH;
	            break;
	    }
	    if(goto_time)
	    {   
	        printf("browse function : goto_time :%d---\n",goto_time);
	    exe_timesearch_func(0,search_mode);//xyy 2003-7-29 13:25
	}
	}
	else//for DVD
	{
            printf("****exe_time_goto****goto_hour = %2d  goto_min = %2d goto_sec = %2d \n",goto_hour,goto_min,goto_sec);
	    
	    if(goto_time) ircmd_post_func(CMD_FUNC|CMD_FUNC_GOTO); //axel 2004/1/27 10:00pm return while min>60 or sec>60
	}
	
	bInputState = NON_INPUT_STATE;
	bTimeInput=0;
}

void br_Draw_rtSpecialItem(void)//include audio language,sub-picture,repeat_all,multi-angle
{
    br_Draw18space(INFO_FONTCOL,INFO_PRE_BKCOL,HL_index-1);//xyy 2003-7-29 17:32
	br_Draw_FBicon();//xyy 2003-7-29 15:52
    
    switch(info_index)
    {
    //info_index:the index of string_index_dvd array or string_index_vcd array
   
    case 2://DVD:STR_OS_subtitle ;;CD:STR_OS_REP
    	if(cd_type_loaded==CDROM || cd_type_loaded==CDDA)
    		ircmd_repeat_all();
    	
   
		if(cd_type_loaded == CDDVD)
		    ircmd_sub_picture();
		break;
	
	case 3://DVD:STR_OS_AUDIO_LANG_SETUP; VCD:STR_OS_REP
		if(cd_type_loaded==CDDVD)
			ircmd_audio_language();
		
		else
	    	ircmd_repeat_all();
	    
		break;
	case 4://DVD:STR_OS_ANGLE
        ircmd_angle();
		break;
	case 7://DVD:STR_OS_REP
    	ircmd_repeat_all();
		break;
	} 
	  	
	br_Draw_FFicon();//xyy 2003-7-29 16:51
}
void browse_func_select(void)
{
//info_index:the index of string_index_dvd array or string_index_vcd array
//which is defined in file browse_gui.h
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
            case 1://chaprter(DVD) or disc time (VCD)playtime(CD/MP3) information
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
            case 2://sub_title(DVD) or track time(VCD) or repeat setup(CD/MP3)information
	            
				 if(cd_type_loaded==CDROM || cd_type_loaded==CDDA)//xyy 2003-9-12 13:38
				{
			        bBrowseLevel = 1;  
			        br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_PRE_BKCOL);
				    br_Draw_rtSpecialItem();					
				}
				//zhaoyanhua add 2003-12-7 13:30
				else if(cd_type_loaded==CDDVD)
	            {
//	                if(pDSV->dAv_SPST_Ns<2)
//	                    return;
			        bBrowseLevel = 1;  
			        br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_PRE_BKCOL);
				    br_Draw_rtSpecialItem();
	            }
				else //disc time VCD
	            {
			        br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_PRE_BKCOL);
            		init_time_search();
            	}
           	   	
           	   		
           	   break;
            case 3://audio language (DVD), repeat (VCD) information
	            
	            if(cd_type_loaded==CDDVD)
	            {
	                if(pDSV->dAv_AST_Ns<=1)
            		return;
	            }
	            else//VCD
	            {
	                #if !defined(PULIANG_DVD)
	                if( IsPBCOn() )
		    		    return;
		    		#endif
				}
				bBrowseLevel = 1;  
				br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_PRE_BKCOL);
		        br_Draw_rtSpecialItem();
				//br_Draw_rtSpecialItem();
	            break;    
            case 4://multi-angle(only DVD)information
            	if(get_angle_Ns()<1)
            		return;
		        bBrowseLevel = 1;  
		        br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_PRE_BKCOL);
			    br_Draw_rtSpecialItem();
                break;
            //zhaoyanhua add 2003-12-7 13:55
            case 5:
            case 6:    
			    br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_PRE_BKCOL);
                init_time_search();
            	break;
            case 7://repeat setup(DVD)information
		        bBrowseLevel = 1;  
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
            case 1://chaprter(DVD) or disc time(VCD)or playtime(CD/MP3) information
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
                {
                	exe_time_goto();
                	bInputState = NON_INPUT_STATE; 
                    br_DrawRightItem();//zhaoyanhua add 2003-12-6 15:56
                }
                break;
            case 2://sub_title(DVD)   track time(VCD) or repeat setup(CD/MP3)information
	            if(cd_type_loaded == CDDVD)
	            {
	                br_DrawRightItem();
	            }
	            else if((cd_type_loaded == CDVCD10)||(cd_type_loaded ==CDVCD20)||(cd_type_loaded == CDSVCD))
	            {   
	                exe_time_goto();
	                bInputState = NON_INPUT_STATE; 
	                br_DrawRightItem();//zhaoyanhua add 2003-12-6 15:56
	            }
	            else if((cd_type_loaded == CDROM)||(cd_type_loaded == CDDA))	//linrc 2005-10-22 14:05
	            {
	            	br_DrawRightItem();
	            }
	           
                break;
            case 5:
            case 6:
                exe_time_goto();
                br_DrawRightItem();//zhaoyanhua add 2003-12-6 15:56  
                break;             
            case 3:////audio language setup(DVD) or repeat setup(VCD) information
            case 4://multi-angle(only DVD)information    
            case 7://repeat setup(DVD)information
                br_DrawRightItem();
                break;
        }
        bBrowseLevel = 0;
    }
}

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
    else if((cd_type_loaded==CDDVD && info_index == 5) ||((cd_type_loaded==CDDVD) && (info_index == 6)) 
      || (cd_type_loaded!=CDDVD && info_index==1)|| 
      (cd_type_loaded!=CDDVD &&cd_type_loaded!=CDROM && cd_type_loaded!=CDDA && info_index==2))	//linrc 2005-10-22 14:06
    {//for VCD £ºinfo_index 1/2 //zhaoyanhua add 2003-12-6 16:55
        #ifdef BROWSE_DBG
        printf("==========DRaw left Item =========\n");
        #endif
        br_DrawLeftItem(info_index,info_index%ITEM_PER_PAGE,INFO_FONTCOL,INFO_BKCOL);//xyy 2003-8-11 17:06
    	br_DrawRightItem();
        bBrowseLevel = 0;
        bTimeInput = 0;
        index_x = 0; // alan, 2003/9/5 02:16¤U¤È
    }
    if(((cd_type_loaded==CDROM || cd_type_loaded==CDDA)&& info_index==2) 
    || ((cd_type_loaded!=CDDVD) && info_index>2)
        || ((cd_type_loaded == CDDVD) &&((info_index == 2) || (info_index == 3)||(info_index == 7) ||(info_index == 4))))
        //zhaoyanhua add (info_index == 4), for DVD when multi_angle, LEFT/RIGHT can select angle. 2004-2-3 16:56
    {	
    	action_click=1;
    	br_Draw_rtSpecialItem();
	    	action_click=0;
	}
	
}

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
    if(((info_index>=3) && (cd_type_loaded != CDDVD))// 1/2VCD(disc time/track time)
     ||((cd_type_loaded == CDDVD)&&((info_index == 7)||(info_index== 2)||(info_index == 3)||(info_index == 4)))  
       )//zhaoyanhua add (info_index == 4), for DVD when multi_angle, LEFT/RIGHT can select angle. 2004-2-3 16:56
    {	
	    	action_click=1;
	    	#ifdef BROWSE_DBG
	    	printf("=====RIGHT=================== \n");
	        #endif
	    br_Draw_rtSpecialItem();
	    	action_click=0;
	}
	
}

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

void browse_func_input(void)
{
	if(bBrowseLevel == 0)//xyy 2003-9-15 15:51
		return;
	//info_index:0,1,2(track select,disc time,track time)can use input	
    if(((info_index>2)&&(cd_type_loaded !=CDDVD)) || (bInputIndex>1) || (index_x>5)) //linrc 2005-10-22 14:06
        return;
    //for DVD only info_index = 0,1,5,6 (title select,chapter select ,title time select,chapter time select)can valid
    //zhaoyanhua add 2003-12-7 14:33
    if(cd_type_loaded == CDDVD)
    {
        if(((info_index != 0)&&(info_index != 1)&&(info_index != 5) &&(info_index != 6))||(bInputIndex>1) || (index_x>5))
            return;
    }
    
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
    else if(info_index==1)//VCD(disc time )
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
    else if(info_index==2)//VCD(track time)
    {
    	if(bBrowseLevel==0)
    		return;
        #if 0//zhaoyanhua mask 2003-12-7 14:25
        if(cd_type_loaded==CDDVD)
    		time_input();
    	#endif
        else if((cd_type_loaded == CDVCD10)||(cd_type_loaded ==CDVCD20)||(cd_type_loaded == CDSVCD))//zhaoyanhua add 2003-12-6 14:43
            time_input();
    }
    //zhaoyanhua add 2003-12-7 14:26
    else if((info_index ==5)||(info_index == 6))//DVD( disc time),(chapter time)
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

/*
 * draw new style window GUI according to the cofig memory mode.
 *
 * NOTE :
 *   relocated the position of OSD and VPP window.
 *
 *  zhaoyanhua add 2003-12-18 15:32
 */

void
exit_browse_func(void)
{
    browse_show_function();

    bBrowseLevel    = 0;
    full_scrn       = 0;
    vpp_zoom        = 0;
    
	show_window_info = 0;
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


void br_Draw_AGL_info(void)
{
    UINT8 offset;
    
    action_click = 2; //Jeff add 20031006, to avoid "GOTO" automatic toggled when high-light focus on "GOTO"
    ircmd_angle();//xyy 2003-7-29 15:14
    offset = ITEM_HEIGHT*4;
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+offset,
                            linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
}

void br_Draw_TT_time(void)
{
	UINT8 hour,minute,second,offset;
	if(cd_type_loaded==CDDVD)
		offset = ITEM_HEIGHT*0;
	else
		offset = ITEM_HEIGHT*1;
	tm2hms(disc_time,&hour,&minute,&second);
	psprintf(linebuf,"%02d:%02d:%02d",hour,minute,second);
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+offset,
                            linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
}

void br_Draw_CHP_time(void)
{
	UINT8 hour,minute,second,offset;
	UINT32 chpTime;
	if(cd_type_loaded==CDDVD)
		offset = ITEM_HEIGHT*1;
	else
		offset = ITEM_HEIGHT*2;
		
	chpTime = dNx_pg_tm-dPg_tm;
	if(cd_type_loaded == CDSVCD)
		tm2hms(chpTime/PLAY_SPEED,&hour,&minute,&second);
	else	
		tm2hms(chpTime,&hour,&minute,&second);
	psprintf(linebuf,"%02d:%02d:%02d",hour,minute,second);
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+offset,
                            linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
}

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


void br_DrawRightItem(void)
{

#ifdef NEW_OSD_DRIVER
    osd_draw_rect(brArea[BR_CONTENT_AREA].xStart*10+105, brArea[BR_CONTENT_AREA].yStart*4, //2004-2-20 09:15ÕÅÓîP
					brArea[BR_CONTENT_AREA].xSize*10-60, brArea[BR_CONTENT_AREA].ySize*4, INFO_PRE_BKCOL); 
#else
    osd_draw_rect(brArea[BR_CONTENT_AREA].xStart*8, brArea[BR_CONTENT_AREA].yStart*4, //2004-2-20 09:15ÕÅÓîP
					brArea[BR_CONTENT_AREA].xSize*10, brArea[BR_CONTENT_AREA].ySize*4, INFO_PRE_BKCOL); 
#endif

#if defined(ADJUSTING_ACTION_VALID_RIGHT_NOW)//xyy 2003-9-9 16:10
			action_click = 2;	// alan, 2003/8/28 05:45PM
#else
			action_click = 0;
#endif
     if(info_index<ITEM_PER_PAGE)
    {
    	br_Draw_TT_info();
    	#if 0//not show play time//zhaoyanhua 2003-12-6 16:47
    	br_Draw_TT_playtm();
    	#endif
	if(cd_type_loaded==CDDVD)
    	{
	    	br_Draw_CHP_info();
	
			action_click=2;	//alan, 2003/8/28 05:45PM
			ircmd_sub_picture();
		    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*2,
		    					linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);	
			
			action_click=2;	//alan, 2003/8/28 05:45PM
			ircmd_audio_language();
	        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*3,
	                                linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
		    br_Draw_AGL_info();
		    	
		}
		else if(cd_type_loaded==CDROM || cd_type_loaded==CDDA)//xyy 2003-9-12 13:34
		{
			memset(linebuf,0,100);
			br_Draw_TT_time();//yaowh add 2005-11-22 15:56
			action_click=2;//20040213
			ircmd_repeat_all();
	        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*2,
	                                linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
				
		}
	    else//VCD
		{
		    br_Draw_TT_time();
	        br_Draw_CHP_time();
        			
			action_click = 2;	// alan, 2003/8/28 05:45PM
			memset(linebuf,0,sizeof(linebuf));
			ircmd_repeat_all();
			#ifdef BROWSE_DBG
			printf("#################### ------DRAWRightItem---\n");
	        #endif
	        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*3,
	                                linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
		
		}
	}
	if(cd_type_loaded==CDDVD)
		if((info_index>=ITEM_PER_PAGE)&&(info_index<ITEM_PER_PAGE*2))
		{
			
	        br_Draw_TT_time();
	        br_Draw_CHP_time();
			action_click = 2;	// alan, 2003/8/28 05:45PM
			memset(linebuf,0,sizeof(linebuf));
			ircmd_repeat_all();
	        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*2,
	                                linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
		} 
}	

void br_Draw_TT_progress(void)
{
	UINT16 num,time_step,bar_step,xLen;
	int playing_time_now = 0;
//	printf("br_Draw_TT_progress()\n");
#ifdef DISP_TIME_NOT_CHANGE_WINDOW_PROGESS//zhaoyanhua add 2004-2-5 14:17
	playing_time_now = track_play_time;
#else
	playing_time_now = disp_time;	
#endif//DISP_TIME_NOT_CHANGE_WINDOW_PROGESS	
//	printf("### ----playing_time_now: %d, track_play_time: %d===\n",playing_time_now,track_play_time);
	if(cd_type_loaded==CDROM)//xyy 2003-9-12 15:09
	{
		if((dNx_pg_tm-dPg_tm)<update_definition)
			update_definition = (dNx_pg_tm-dPg_tm)/2;
	
		if((PlayBackLength * 16/ Mp3_kbitrate)<update_definition)
			update_definition = (PlayBackLength * 16/ Mp3_kbitrate)/2;
		time_step = (PlayBackLength * 16/ Mp3_kbitrate)/update_definition;
		osd_draw_rect(BAR_XSTART+BAR_EDGE,TT_BAR_YSTART+BAR_EDGE,PROGRESS_BAR_LEN-2*BAR_EDGE,PROGRESS_BAR_YLEN,6);
		
		num = (playing_time_now)/time_step;

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
		num = playing_time_now/time_step;	//yaowh 2005-11-22 15:57
		//num = (playing_time_now+dPg_tm)/time_step;//zhaoyanhua changed 2004-2-6 9:03
	else if(cd_type_loaded==CDSVCD)
		num = (dPg_tm/PLAY_SPEED+playing_time_now)/time_step;
		else if(cd_type_loaded==CDROM)//xyy 2003-9-12 16:03
	//		num = (total_play_time+disp_time)/time_step;
			num = (disp_trk_now * (PlayBackLength * 16/ Mp3_kbitrate)+playing_time_now)/time_step;
	else
		num = (dPg_tm+playing_time_now)/time_step;
		
		bar_step = num*((PROGRESS_BAR_LEN-2*BAR_EDGE)/update_definition);
		xLen = PROGRESS_BAR_LEN-2*BAR_EDGE;
	
	if(bar_step>xLen)
			osd_draw_rect(BAR_XSTART+BAR_EDGE,TT_BAR_YSTART+BAR_EDGE,xLen,PROGRESS_BAR_YLEN,BAR_COL);
	else
			osd_draw_rect(BAR_XSTART+BAR_EDGE,TT_BAR_YSTART+BAR_EDGE,bar_step,PROGRESS_BAR_YLEN,BAR_COL);
	}
}

void br_Draw_CHP_progress(void)
{
	UINT16 num,time_step,bar_step,xLen;
	int playing_time_now = 0;
//	printf("br_Draw_TT_progress()\n");
#ifdef DISP_TIME_NOT_CHANGE_WINDOW_PROGESS//zhaoyanhua add 2004-2-5 14:17
	playing_time_now = track_play_time;
#else
	playing_time_now = disp_time;	
#endif//DISP_TIME_NOT_CHANGE_WINDOW_PROGESS	
	
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
		num = (playing_time_now -dPg_tm)/time_step;//fix the bug:progress not move.yaowh 2005-11-22 15:57
		//num = (playing_time_now)/time_step;//zhaoyanhua changed 2004-2-5 17:51
	else
		num = (playing_time_now)/time_step;
	bar_step = num*((PROGRESS_BAR_LEN-2*BAR_EDGE)/update_definition);
	xLen = PROGRESS_BAR_LEN-2*BAR_EDGE;
	
	if(bar_step>xLen)
		osd_draw_rect(BAR_XSTART+BAR_EDGE,CHP_BAR_YSTART+BAR_EDGE,xLen,PROGRESS_BAR_YLEN,BAR_COL);
	else
		osd_draw_rect(BAR_XSTART+BAR_EDGE,CHP_BAR_YSTART+BAR_EDGE,bar_step,PROGRESS_BAR_YLEN,BAR_COL);
}

void exe_show_time(void)  // fengjl edit 4-1-8 16:44 to display DISCTIME and TRACKTIME when play VCD
{
    if((cd_type_loaded==CDVCD10)||(cd_type_loaded==CDVCD20)||(cd_type_loaded==CDSVCD))
    {
        psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_DISCTIME]);
    }
    else    
	{
    	psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_TT]);
    }
    osd_DrawRegionString(25/*50*/,ITEM_HEIGHT*2+ITEM_HEIGHT/2-1,linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);
	
    if((cd_type_loaded==CDVCD10)||(cd_type_loaded==CDVCD20)||(cd_type_loaded==CDSVCD))
    {
        psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_TRACKTIME]);
    }
    else
    {
    	psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_CHP]);
    }
    osd_DrawRegionString(25/*50*/,ITEM_HEIGHT*5-1/*+ITEM_HEIGHT/2*/,linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);

	osd_draw_rect(BAR_XSTART,TT_BAR_YSTART,PROGRESS_BAR_LEN,BAR_YLEN,BAR_BKCOL);
	osd_draw_rect(BAR_XSTART,CHP_BAR_YSTART,PROGRESS_BAR_LEN,BAR_YLEN,BAR_BKCOL);
	
	br_Draw_TT_progress();
	br_Draw_CHP_progress();
	
}


/*
 * update repeat mode when USERS enter REPEAT
 *
 * zhaoyanhua  add 2003-12-7 18:45
 */
void updateRepeatMode(void)
{
    //when it is in right item.not draw REPREAT MODE infomation
    if(((cd_type_loaded==CDROM) || (cd_type_loaded==CDDA)) &&(!((info_index == 2)&&(bBrowseLevel))))
    {    	    
       
        {            
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*2,
	                                "        ",INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
       // br_Draw_FBicon();
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*2,
	                                linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
        }
        // br_Draw_FFicon();
    }
    else if((cd_type_loaded == CDDVD)&&(!((info_index == 7)&&(bBrowseLevel))))
    {
        if(info_index > ITEM_PER_PAGE) 
        {    
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*2,
	                                "        ",INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);     
         //br_Draw_FBicon();
         osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*2,
	                                linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
         }
         //br_Draw_FFicon();
    }
    else if(((cd_type_loaded == CDVCD10)||(cd_type_loaded ==CDSVCD)||(cd_type_loaded == CDVCD20)) &&(!((info_index == 3)&&(bBrowseLevel))) )
    {
       
        {    
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*3,
	                                "        ",INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);     
         //br_Draw_FBicon();
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*3,
	                                linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);     
        }
        //br_Draw_FFicon();
    }
}

/*
 * update auido mode when USERS enter "AUDIO"
 *
 * zhaoyanhua  add 2003-12-7 18:45
 */
void updateAudioLanguage(void)
{
    //clear display words //8 SPACE
    
    if( (!((info_index == 3)&&(bBrowseLevel)))&&(info_index<=4) )//terry, fixing GOTO browser bug 2004/1/27 11:42 
    {          
        
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*3,
	                    "              ",INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
   
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*3,
	                    linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
 }   
}

/*
 * update subtitle when USERS enter SUBTITLE
 *
 * zhaoyanhua  add 2003-12-7 18:45
 */
void updateSubtitle(void)
{
    //clear the current display words.8 SPACE 
  if(!((info_index == 2)&&(bBrowseLevel))&&(info_index<=4) )//terry, fixing GOTO browser bug 2004/1/27 11:42
{        
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*2,
		    		     "          ",INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);
    
    osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*2,
		    		     linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);	
 }  
}

/*
 * update angle when USERS enter ANGLE
 * 
 * fengjl  add 2003-12-10 11:50
 */
void UpdateAngleInfo(void)
{
    
    if(!((info_index == 4)&&(bBrowseLevel))&&(info_index<=4) )//terry, fixing GOTO browser bug 2004/1/27 11:42
    {
        
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*4,
                            "          ",INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region); 
        
        osd_DrawRegionString(brArea[BR_CONTENT_AREA].xStart,brArea[BR_CONTENT_AREA].yStart+ITEM_HEIGHT*4,
                            linebuf,INFO_FONTCOL,INFO_PRE_BKCOL,arc_region_loc.region);   
        
    }
}

void UpdateTT_CHP_info(void)
{
//	printf("run into UpdateTT_chp_info\n");
//	if(cd_type_loaded==CDROM)//xyy 2003-9-12 15:48
//		total_play_time = total_play_time + (PlayBackLength * 16/ Mp3_kbitrate);
    if(bInputState == NON_INPUT_STATE)
    {
        if(info_index == 0)//zhaoyanhua 2003-12-7 14:41
            br_Draw_TT_info();
        if(cd_type_loaded==CDDVD)
	    {    
	        if(info_index == 1)
	            br_Draw_CHP_info();
	    
	    }
    }
    
    if(cd_type_loaded==CDDVD)
    {
    	
    	if((info_index>=ITEM_PER_PAGE))
	    {
	    	#if 0
	    	br_Draw_TT_time();
	    	br_Draw_CHP_time();
	        #endif
	    }
	    
	}
	else if(cd_type_loaded > CDROM && cd_type_loaded <= CDSVCD)
	{
	    	#if 0//zhaoyanhua mask 2003-12-6 16:05
	    	br_Draw_TT_time();
	    	br_Draw_CHP_time();
	        #endif
	}
//    if((info_index==ITEM_PER_PAGE)&&(bBrowseLevel==0))
//    	br_Draw_AGL_info();

	#if 0
	if(bTimeInput == 0 && info_index<ITEM_PER_PAGE)
	    br_Draw_TT_playtm();
	#endif
	br_Draw_TT_progress();
	br_Draw_CHP_progress();
	
	//when play next charpter or title, update window info.
	//zhaoyanhua add 2003-12-18 17:29
	if(show_window_info> 10)
	{
		//if(cd_type_loaded == CDDVD)//fengjl mark it 3-12-23 12:43 just because VCD also need change
		//to avoid the BUG:
        //when HL in bBrowseLevel= 1,enter"NEXT""PREVIEW" will update the right information,
        // the HL will disappeared.
        //SOLUTION: SET bBrowseLevel = 0.
        //zhaoyanhua add 2004-2-10 9:18
		if(bBrowseLevel==1)	
		{    
		    br_DrawLeftItemStr(HL_index-1,info_index,INFO_FONTCOL,INFO_BKCOL);
            bBrowseLevel = 0;
		}
			br_DrawRightItem();
				
		show_window_info = 1; 				
	}
	//br_Draw_rtSpecialItem();//zhaoyanhua temp add 2003-12-6 17:05
   // br_DrawRightItem(1);
	
}

void br_DrawLeftItem(BYTE item_index,BYTE loc_index,BYTE fontColor,BYTE bkColor)
{
    br_Draw8space(fontColor,bkColor,loc_index);//xyy 2003-7-29 17:12
    if(item_index>=DVD_MAXITEM)
    	return;
    //zhaoyanhua add 2003-12-7 13:13
    if((item_index >= VCD_MAXITEM ) &&(cd_type_loaded!=CDDVD))//for VCD
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
void exe_browse_func(void)
{
    int j;

    browse_show_function();
    
    //printf("Item_yStar=%d  Content_yStar=%d \n",brArea[BR_ITEM_AREA].yStart,brArea[BR_CONTENT_AREA].yStart);
    //printf("Item_xStar=%d  Content_xStar=%d \n",brArea[BR_ITEM_AREA].xStart,brArea[BR_CONTENT_AREA].xStart);
    
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
	SetFullscrnCmdFuncPtr( browse_func_up, browse_func_down, browse_func_left,
                           browse_func_right, browse_func_select);
}

void DrawNewWindow(void)
{
	//BYTE config_mode = 0;  //yangli mark ,2005-12-5 11:35
	
	show_window_info = 1;
	
	//config_mode = GetConfigMode(memory_config_saved); //yangli mark ,2005-12-5 11:35
	if(getVPP_TVsystem() == MODE_PAL)//if(config_mode == MODE_PAL) //yangli mod ,2005-12-5 11:36
		osd_init_newstyle_window_PAL();
	else
		osd_init_newstyle_window_NTSC();
		
	arc_region_loc.region  = 2;
	osd_draw_rect(0,0,38*16,374,4);

    arc_region_loc.xStart  = 2*16-15;//2*16-15;
    arc_region_loc.yStart  = 6;//6;
    arc_region_loc.xLen    = 21*16+32;
    arc_region_loc.yLen    = 24*10-20;
    arc_region_loc.bkColor = 9;
    arc_region_loc.radius  = 10;
    osd_draw_region_arc(&arc_region_loc,2);


    arc_region_loc.xStart  = 2*16-15+10;
    arc_region_loc.yStart  = 16;
    arc_region_loc.xLen    = 21*16+32-20;
    arc_region_loc.yLen    = 24*10-40;
    arc_region_loc.bkColor = 0;
    osd_draw_region_arc(&arc_region_loc,2);
     
   	//restore default aspect
    set_video_aspect();
    startup_vpp_now();
    // 70,90 ~ 429,332    
    if(getVPP_TVsystem() == MODE_PAL)//if(config_mode == MODE_PAL) //yangli mod ,2005-12-5 11:36
        //set_vpp_disp_window(70,143,360,230);
        set_vpp_disp_window(70,108,360,210);//yaowh 2005-11-22 16:10
        //set_vpp_disp_window(64,124,360,220);		 		  //70,143,360,237zhaoyanhua add 2003-11-30 15:06
    else
    	//set_vpp_disp_window(70,76,360,237);		 //axel 2003/11/21 07:19pm 70,92,360,238 alan, 2003/8/26 10:43PM
		set_vpp_disp_window(70,70,360,220);	//yaowh 2005-11-22 16:10
//    vpp_set_bg_color(0x30,0xb070);
    sup_disable();  
         
    exe_browse_func();	
    exe_show_time();
}

#endif


