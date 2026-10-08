/*****************************************************\
Creater: Terry
Date   : 2001/5/14 05:30PM
Description: Program menu using
\*****************************************************/

//#define MONE_PROG

#if defined( SUPPORT_OSDID3) || defined(SUPPORT_ID3)                 //suxin add 2005-9-20 ,fix bug,when open ID3 and not open osdID3,complie cannot pass.
        extern void osd_init_OSDID3(void);
        extern void show_id3(void);
        extern UINT16 Is_MP3_STATE(void);
#endif

#ifdef  OP_PLAYMODE//libing 2005-7-4 10:10
extern int  program_func_flag;
#endif
#ifdef SUPPORT_MP4_SUBTITLE  // David 2004-5-12
extern int IS_EXT_SUP_ACTIVATED(void);
extern void osd_init_OSDSRT(void);
extern BYTE GetCurrentFileType(void);
#endif

#ifdef OSD_BMP_PROG
//Note:some data about OSD_BMP_PROG,moved to prog_bmp.c
//suqiaoli 2004-11-23 
#include "prog_bmp.c"
extern void ShowBmpProgSel(UINT8 mode);
extern void ShowBmpProgPage(void);
#endif

#ifdef SETUP_PROGRAM_IN_PLACE_UNDER_16M

#ifdef NEW_STYLE_SETUP

static inline void ProgOffForNewStyleSetup()
{   // 2004/11/26 yltseng
    #ifdef SDRAM_16Mb_Mode
    
    #include "memmap0.h"
	#include "navdata.h"
	
	regs0->osd_base_addr=GetOSDBackUpAddress();
	osd_init();

	if( (prog_state == 2)||(prog_state == 6))
	{
		if ((cd_type_loaded == CDROM) && (pFsJpeg->gifsFuncBtn == 2))
		{		
			prog_state=255;
			ircmd_post_func(CMD_FUNC | CMD_FUNC_PLAY);          
		} 
		else 
		{
			if ((prog_state != 6)&& (prog_state != 3))
		        ircmd_resume();	
			prog_state=0;
		}    	    

        OSD1000ISP_STATUS(OSDISP_PROG_CNL, OSDIR_PROGRAM);

		psprintf(RegionValStr[REGION1], "");
		PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);                  
	}
	
    #else
    
	if( (old_play_state==VCD_STATE_NORMAL)&&(play_state==VCD_STATE_PAUSE) ) // add by shawn 20020218
		ircmd_play();
        #ifdef MP3_STOP_IN_GUI_START//zhaoyanhua add 03-10-14 11:39 keep inital state for MP3
	else if((Is_MP3_STATE()) && (old_play_state == VCD_STATE_MP3_FILELIST))
	{
		play_state = old_play_state;
	}
        #endif
        
    #endif
}

#else

static inline void ProgOffForNormal()
{   // 2004/11/26 yltseng
    #ifdef SDRAM_16Mb_Mode

    osd_disable();
    
    extern UINT8   g_uiOSDStatus;       // 2005/01/14 yltseng
    g_uiOSDStatus = OSD_FULL_SCREEN_STATUS_NONE;
    regs0->osd_base_addr=GetOSDBackUpAddress();

        #ifdef JPEG_PAUSE_WHEN_SETUP    // 2004/12/30 yltseng
    if( Is_JPEG_SlideMode() )
    {
        play_state = VCD_STATE_NORMAL;
        PrintOsdMsg( STR_OS_SEQUENCE, REGION1, 1, 0 );
    }
        #endif
    #endif
    
	if( (old_play_state==VCD_STATE_NORMAL)&&(play_state==VCD_STATE_PAUSE) ) // add by shawn 20020218
		ircmd_play();
    #ifdef MP3_STOP_IN_GUI_START//zhaoyanhua add 03-10-14 11:39 keep inital state for MP3
	else if((Is_MP3_STATE()) && (old_play_state == VCD_STATE_MP3_FILELIST))
	{
		play_state = old_play_state;
	}
    #endif
}

#endif

void prog_func_off()
{
    if(prog_cnt==0) //uncomplete program no
    {
        ircmd_cancel(1);//terry 1011
    }    

#ifdef CD_PLAYER        //liweihua add 2003-9-11
    if(cd_type_loaded == CDDA)
        osd_init_cdplayer();
    else
        osd_init();
#else		
    osd_init();
#endif

    full_scrn = 0; 
// 2004/11/26 yltseng
#ifdef NEW_STYLE_SETUP //zhaoyanhua add 2003-8-26 19:03
    ProgOffForNewStyleSetup();
#else
    ProgOffForNormal();
#endif

//initializing infomation displaying OSD
#ifdef SUPPORT_MP4_SUBTITLE
    if(IS_EXT_SUP_ACTIVATED())
        osd_init_OSDSRT();
    else
#endif
#ifdef SUPPORT_OSDID3
    if(Is_MP3_STATE())
    {
        osd_init_OSDID3();
        show_id3();
    }
#endif 
}

#else   // SETUP_PROGRAM_IN_PLACE_UNDER_16M

void prog_func_off()
{
#ifdef CD_PLAYER        //liweihua add 2003-9-11
    if(cd_type_loaded == CDDA)
        osd_init_cdplayer();
    else
        osd_init();
#else		
    osd_init();
#endif

    if(prog_cnt==0) //uncomplete program no
    {
      ircmd_cancel(1);//terry 1011
    }    
    
    full_scrn = 0;        
#ifdef SDRAM_16Mb_Mode  
	{
	    #include "memmap0.h"
		#include "navdata.h"
		
		regs0->osd_base_addr=GetOSDBackUpAddress();
		osd_init();
		
		#ifdef NEW_STYLE_SETUP //zhaoyanhua add 2003-8-26 19:03
		if( (prog_state == 2)||(prog_state == 6))
		#else
		if (prog_state==2)
		#endif//#ifdef NEW_STYLE_SETUP //zhaoyanhua add 2003-8-26 19:03
		{
			if ((cd_type_loaded == CDROM) && (pFsJpeg->gifsFuncBtn == 2))
			{		
				prog_state=255;
				ircmd_post_func(CMD_FUNC | CMD_FUNC_PLAY);          
			} 
			else 
			{
				#ifdef NEW_STYLE_SETUP//zhaoyanhua add 2003-8-26 19:02
				if ((prog_state != 6)&& (prog_state != 3))
			        ircmd_resume();	
				prog_state=0;
				#else
				prog_state=0;
				ircmd_resume();	
				#endif//end NEW_STYLE_SETUP
			}    	    

            OSD1000ISP_STATUS(OSDISP_PROG_CNL, OSDIR_PROGRAM);

			psprintf(RegionValStr[REGION1], "");
			PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);                  
		}
	}
#else
	{
		if( (old_play_state==VCD_STATE_NORMAL)&&(play_state==VCD_STATE_PAUSE) ) // add by shawn 20020218
			ircmd_play();
	#ifdef MP3_STOP_IN_GUI_START//zhaoyanhua add 03-10-14 11:39 keep inital state for MP3
		else if((Is_MP3_STATE()) && (old_play_state == VCD_STATE_MP3_FILELIST))
		{
			play_state = old_play_state;
		}
	#endif
	}
#endif

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

}

#endif  // SETUP_PROGRAM_IN_PLACE_UNDER_16M

void prog_func_clear(void)
{
	UINT8 i;
	for(i=0;i<=SHOW_PROG_NO;i++)
	{
		prog[i][0]=0;
		prog[i][1]=0;
	}
	index_y=2;
	index_x=0;
	
	prog_cnt = 0;
#ifdef  OP_PLAYMODE//libing 2005-7-4 10:10
	program_func_flag = 0;
#endif
#ifdef OSD_BMP_PROG
	flag_data = 0;
#endif
	
}



int is_clear_pos(void)//2002-4-19 1:53
{
	int ret=0;
	if(prog_item[page][index_y][0]==SET_FUNC)
	{
#ifndef PROG_12_ITEMS //Jeff 20020925
		if(prog_item[page][index_y][index_x/2+1]==STR_OS_CLEAR)
#else
		if(prog_item[page][index_y][index_x/2+2]==STR_OS_CLEAR)
#endif
		{
			ret=1;
		}
	}
	return ret;	
}	

void prog_func_select(void)
{
	if(prog_item[page][index_y][0] == SET_FUNC)
	{
#ifdef PROG_12_ITEMS
		if (prog_item[page][index_y][index_x / 2 + 2] == STR_OS_CLEAR)
		{
			prog_func_clear();
			ShowProgPage();
		}
		else if (prog_item[page][index_y][index_x / 2 + 2] == STR_OS_PLAY)
			ircmd_play();
#else
		if (prog_item[page][index_y][index_x / 2 + 1] == STR_OS_CLEAR)
		{
            OSD1000ISP_STATUS(OSDISP_PROG_CLEAR, OSDIR_PROGRAM);

			prog_func_clear();
			ShowProgPage();
		}
		else if (prog_item[page][index_y][index_x / 2 + 1] == STR_OS_PLAY)
			ircmd_play();
#endif
	}
}


void prog_func_play(void)
{
	UINT8 i;

#ifdef MONE_PROG
	printf("prog_func_play, in\n");
#endif
	
	prog_cnt=0;
	
	for(i=0;i<SHOW_PROG_NO;i++)
	{
		//if (offset == 3) { //Jeff 20010808
		if (cd_type_loaded == CDROM) { //Jeff 20010914
			BYTE    iPage = prog[i][0];
			BYTE    iItem = prog[i][1];
			
			if ( iPage && iItem && FSChkProg(iPage, iItem) )
			{
#ifdef MONE_PROG
				printf("i:%d Page:%d Item:%d sucess\n", i, prog[i][0], prog[i][1]);
#endif
				prog_cnt++;
				prog[prog_cnt][0]=prog[i][0];
				prog[prog_cnt][1]=prog[i][1];
			}
			else
			{
#ifdef MONE_PROG
				printf("i:%d Page:%d Item:%d fail\n", i, prog[i][0], prog[i][1]);
#endif
			}
			
			if (i > prog_cnt)
			{
				prog[i][0]=0;
				prog[i][1]=0;
			}
		}
		else //if (cd_type_loaded == CDROM)
		if(offset==2)
		{
			//printf("i:%x prog[i][0]:%x\n",i,prog[i][0]);

//			if( (prog[i][0]>=cd_trk_lo)&&(prog[i][0]<=show_trk_num(cd_trk_hi)) )
			if ((prog[i][0] >= 1) && (prog[i][0] <= show_trk_num(cd_trk_hi))) // robert 030512 for some case cd_trk_lo = 2
			{
				prog_cnt++;
				prog[prog_cnt][0]=prog[i][0];
				//printf("prog_cnt:%x\n",prog_cnt);
			}
			
			if(i>prog_cnt)
				prog[i][0]=0;
		}
		else //if(offset==2)
		{//dvd ,reference ChkPTTRange
			UINT8 tt=prog[i][0];
			UINT16 ptt=prog[i][1];
			
#ifdef DVD_AUDIO
			UINT8  (*ChkRange)(UINT8*, UINT16*);

			if (dAMG_LSN)				// alan, 2002/11/8 11:40上午
				ChkRange=ChkTrkRange;
			else
				ChkRange=ChkPTTRange;			
			if( tt && ptt && ChkRange(&tt,&ptt))
#else
			if( tt && ptt && ChkPTTRange(&tt,&ptt))
#endif					
			{
#ifdef MONE_PROG
				printf("i:%d tt:%d ptt:%d sucess\n",i,prog[i][0],prog[i][1]);
#endif
				
				prog_cnt++;
				prog[prog_cnt][0]=prog[i][0];
				prog[prog_cnt][1]=prog[i][1];
			} else
			{
#ifdef MONE_PROG
				printf("i:%d tt:%d ptt:%d fail\n",i,prog[i][0],prog[i][1]);
#endif
			}
			
			if(i>prog_cnt)
			{
				prog[i][0]=0;
				prog[i][1]=0;
			}
		}
	} //for(i=0;i<SHOW_PROG_NO;i++)
	
#ifdef SUPPORT_WMA        //nono 4-9-3 20:36    
    asf_resume_pck = 0;
#endif
	
	if (prog_cnt)
	{
        OSD1000ISP_STATUS(OSDISP_PROG_ON, OSDIR_PROGRAM);

		PrintOsdMsg(STR_OS_PROGPLAY,REGION1,1,0);//nono 2-7-9 22:05
	}
#ifdef MONE_PROG
	printf("prog_func_play, out\n");
#endif
	
//to avoid the bug when program play not show display.
//zhaoyanhua add 2003-11-13 16:34
#ifdef SDRAM_16Mb_Mode
    if (old_t_disp)
    {
        extern void DispPolling(BYTE bReset);
        t_disp=old_t_disp;
        DispPolling(3);
    }
#endif

#if 1//ndef SDRAM_16Mb_Mode//nono 2004-7-28 18:02 ->zhongshan 16Mb need too 2005-10-10 20:06
	resumeMSF = 0; //Jeff 20020715
#endif
	#ifdef  OP_PLAYMODE//libing 2005-7-4 10:10
		program_func_flag = 1;
	#endif	
}



void prog_func_input(UINT8 num)
{
	UINT8 x,y;
	int val;
	
	x=index_x%2;
#ifdef OSD_BMP_PROG
    y = (index_y - 2 ) + MAX_NM_Y * (index_x / 2) + 1;
#else	
	y=index_y+MAX_NM_Y*(index_x/2)-1;
#endif
	
	if(num!=11)
	{//clear
		val=prog[y][x];
		add_input_num(&val);
		prog[y][x]=val%100;

/* alan 0429 modified */
		/* if the prog doesn't locate in valid range, prog=0 to invalid it */
		switch (cd_type_loaded)
		{
		case CDDA:
		case CDVCD10:
		case CDVCD20:
		case CDSVCD:
			if (prog[y][x]>cd_total_trk()) prog[y][x]=0;
			break;
		case CDROM:
			if (!FSChkProg(prog[y][0],prog[y][1])) prog[y][x]=0;            	
			break;
		case CDDVD:
			{
				UINT8 tt=prog[y][0];
				UINT16 ptt=prog[y][1];
#ifdef DVD_AUDIO
				if (dAMG_LSN)	// alan, 2002/11/8 11:39上午
				{
					if (!ChkTrkRange(&tt,&ptt))
						prog[y][x]=0;
				} else
#endif   				
				{
					if(!ChkPTTRange(&tt,&ptt)) 
						prog[y][x]=0;
				}
			}
			break;
		}
	}
	else
		prog[y][x]=0;

	//psprintf(linebuf,"%d %d %d",x,y,prog[y][x]);
	//ShowOsdMsg(linebuf,2);

#ifdef OSD_BMP_PROG
    if (prog[y][x]!=0)
    {        
        flag_data = 1;
        Draw_Prog_Play_Reset_Button(0);
    }        	
#endif	

    OSD1000ISP_STATUS(OSDISP_PROG_NUM, OSDIR_PROGRAM);

	ShowProgSel(SW_REGION_ANTI);
}


void ShowProgSel(UINT8 mode)
{
#ifdef OSD_BMP_PROG//in order to use new Prog osd sel
	ShowBmpProgSel(mode);
	return;
#endif

  UINT8 sub_r, tt, ch, y, prog_r_max;
//  int str_id = 0;

#ifdef PROG_12_ITEMS
  if ((index_y >= 2) && (index_y <= 6))
    sub_r = index_x / 2 + 2; // skip first column
  else
    sub_r = index_x / 2 + 1;
#else // 16 items
  sub_r = index_x / 2 + 1;
#endif

  id = prog_item[page][index_y][sub_r];
  y = index_y + MAX_NM_Y * (index_x / 2) - 1;

  //start of show prog_dir_picture  by chichang 2001/5/18
  if(cd_type_loaded == CDDVD || CDROM == cd_type_loaded) // mp3 format is the same as DVD. Added by Robert 2002/05/03
#ifdef PROG_12_ITEMS
	prog_r_max = 5;
else
	prog_r_max = 4;
#else // 16 items
    prog_r_max = 7;
  else
	prog_r_max = 6;
#endif

  if(prog_item[page][index_y][0] == SET_NM)
  {//terry,2004/1/26 01:10PM
  	UINT8 str[10];
  	
	tt = prog[y][0];
	ch = prog[y][1];
	
	if (y==9)
		psprintf(RegionValStr[index_y + 1], " %d ", y);	// for column alignment
	else
		psprintf(RegionValStr[index_y + 1], "%d ", y);			
	
	str[0]=0;	
	mode = mode | 0x02;
	if (offset == 2)
	{
		//vcd
        	if (tt)
		{
			id = STR_OS_SPACE;
			psprintf(str, " %02d ", tt);
		}			
		//mode = mode | 0x02;
	}
	else
	{
		if (tt || ch)
		{
			//dvd
			id = STR_OS_SPACE;
			if (!tt)
				psprintf(str, "--:%02d",ch);
			else if (!ch)
				psprintf(str, "%02d:--",tt);
			else
				psprintf(str, "%02d:%02d",tt, ch);			
	       }
	      // mode = mode | 0x02;
		
	}
	strcat1(RegionValStr[index_y + 1],str);
  }

  if (id)
  {//terry,2004/1/26 01:10PM
	//str_id = id;
	if(prog_item[page][index_y][0] == SET_FUNC)
	{//terry,2003/9/26 04:05PM
		psprintf(RegionValStr[index_y + 1], "%s ", &_OsdMessegeFont1[osd_font_mode][id][0]);
		id = STR_OS_SPACE;
		mode = mode | 1;
	}
	else if(mode & 0xf0)
	{
		if(page < 1)
			mode = mode + (0x10 << (index_x % 2));
	}
	//board_type=BOARD_LR_LINE;
	if((index_y==1)&&(index_x==3))	//wangshf for tonic to set "TT" "CC"  2/6/2004 4:16PM
    {
#ifdef INDIGO_STYLE_OSDUI    	
		psprintf(RegionValStr[index_y + 1], "%s", "");	// the distance of two TC	
#else
		psprintf(RegionValStr[index_y + 1], "%s", "    ");		
#endif
		mode = mode | 1;
	}		
	PrintOsdMsg(id, (index_y + 1) | (sub_r << 4), 0, mode);
  }
  
  #ifndef INDIGO_STYLE_OSDUI
	draw_osd_board(index_y+1,BOARD_LR_LINE); 
  #endif

}

#ifdef INDIGO_STYLE_OSDUI

#define PROG_WID			(610+6)//(576)
#define PROG_HEI			(300)
#define ICON_BG_WID			(610)//(576)
#define ICON_BG_HEI			(36)
#define CONTENT_BG_WID		(PROG_WID-4*2)
#define CONTENT_BG_HEI		(210)
#define LINE_WID			(1)  //2

void ShowProgPage(void)
{
    UINT8 x,y;

    if (full_scrn&PROGRAM) 
	{

		// draw Prog. BG
		osd_tog_region(1, OSD_ON);

		//osd_draw_region_rect(   0,             0,         PROG_WID,                PROG_HEI, 8, 1);
		osd_draw_region_rect(          0,           0, PROG_WID,          ICON_BG_HEI, 8, 1);
		osd_draw_region_rect(          0, ICON_BG_HEI,        4, PROG_HEI-ICON_BG_HEI, 8, 1);		
		osd_draw_region_rect( PROG_WID-4, ICON_BG_HEI,        4, PROG_HEI-ICON_BG_HEI, 8, 1);				
		osd_draw_region_rect(          0,  PROG_HEI-4, PROG_WID,                    4, 8, 1);				
		
		//osd_draw_region_rect(   4,   ICON_BG_HEI,     PROG_WID-4*2,  PROG_HEI-ICON_BG_HEI-4, 1, 1);
		osd_draw_region_rect(            4,              ICON_BG_HEI, PROG_WID-4*2,                      9, 1, 1);
		osd_draw_region_rect(            4,              ICON_BG_HEI,            9, PROG_HEI-ICON_BG_HEI-4, 1, 1);
		osd_draw_region_rect( PROG_WID-4-9,              ICON_BG_HEI,            9, PROG_HEI-ICON_BG_HEI-4, 1, 1);
		osd_draw_region_rect(            4, PROG_HEI-ICON_BG_HEI-4-2, PROG_WID-4*2,          ICON_BG_HEI+2, 1, 1);

		osd_draw_region_rect( 4+9, ICON_BG_HEI+9, PROG_WID-(4+9)*2, 	     CONTENT_BG_HEI, 6, 1);

		osd_DrawRegionLine( 4+9    ,                ICON_BG_HEI+9,      			  4+9, ICON_BG_HEI+9+CONTENT_BG_HEI, 5, LINE_WID, 1); // line left
		osd_DrawRegionLine( PROG_WID-4-9-LINE_WID,  ICON_BG_HEI+9,  PROG_WID-4-9-LINE_WID, ICON_BG_HEI+9+CONTENT_BG_HEI, 5, LINE_WID, 1); // line right
		osd_DrawRegionLine( 4+9    ,                ICON_BG_HEI+9,     	   PROG_WID-(4+9),                ICON_BG_HEI+9, 5, LINE_WID, 1); // line top
		osd_DrawRegionLine( 4+9    , ICON_BG_HEI+9+CONTENT_BG_HEI,         PROG_WID-(4+9), ICON_BG_HEI+9+CONTENT_BG_HEI, 5, LINE_WID, 1); // line botton

        osd_draw_region_rect(295, 263,304, 30, 6, 1); // draw rect before play.

	    coordinate start;

		#ifdef PROG_USE_MUTILANG //zxb 2006-7-26 17:52
		start.x = 40;
		start.y = 10;		
		osd_draw_string(&start, _OsdMessegeFont1[osd_font_mode][34], 5, 8, 1, 0);
		#else
	    start.x = 10;
		start.y = 10;
		osd_draw_string(&start, "PROGRAM", 5, 8, 1, 0);
		#endif
        InitSW_region();
        x=index_x;
        y=index_y;
		
	    if((cd_type_loaded==CDDVD)||(cd_type_loaded==CDROM)) 
	    {
	       offset=1;
		   page=0;
	    }
		else 
	    {
	       offset=2;
		   page=1;
	    }
	    for(index_y=0;index_y<MAX_REGION;index_y++) 
	    {
	      if(prog_item[page][index_y][0]) 
	      {
	        for(index_x=1;index_x<MAX_PROG_SEL;index_x+=offset) 
	            ShowProgSel(0);
	      }
	    }
	    if(offset==2) 
	    {
	      psprintf(RegionValStr[1],"[%d-%d]",show_trk_num(cd_trk_lo_now),show_trk_num(cd_trk_hi));	    
	      PrintOsdMsg(STR_OS_SPACE, (0x04<<4)|1,0,1);
	    }
	    index_x=x;
	    index_y=y;

	    ShowProgSel(SW_REGION_ANTI);
    }// if(full_scrn&PROGRAM) 
}

#else//#ifdef INDIGO_STYLE_OSDUI
void ShowProgPage(void)
{
#ifdef OSD_BMP_PROG//in order to use new Prog osd page
	ShowBmpProgPage();
	return;
#endif    

    UINT8 x,y;

    if (full_scrn&PROGRAM) 
	{
		//test
		//board_type=BOARD_FULL_LINE;
		//SetOsdCol(1,1,0,0xb3ff8880);//region 1~1,color index:0, gbr	color : 
		#ifdef ALCO_MODIFY_PAL_OSD
		//SetOsdCol(7,7,0,0xc0ffc0e0);//region 7~7,color index:0, gbr	color :	amethyst//nono 3-6-9 16:43
		SetOsdCol(1,7,0,0x000000b0);
		//SetOsdCol(2,7,1,0x806+8080ff);//region 2~7,color index:0, gbr	color :	Gray
		//SetOsdCol(1,7,1,0x000000b0);//region 1~7,color index:1, gbr	color : black						
		SetOsdCol(3,7,2,0x8346cfff);//region 3~7,color index:2, gbr	color : 橘色								
		SetOsdCol(1,7,3,0xf3f3f3ff);//region 1~7,color index:3, gbr	color : blue
		#else
		SetOsdCol(7,7,0,0xc0ffc0e0);//region 7~7,color index:0, gbr	color :	amethyst//nono 3-6-9 16:43
		SetOsdCol(1,6,0,0xb3ff88e0);//region 2~7,color index:0, gbr	color :	light blue//nono 3-6-9 16:43
		//SetOsdCol(2,7,1,0x808080ff);//region 2~7,color index:0, gbr	color :	Gray
		SetOsdCol(1,7,1,0x000000ff);//region 1~7,color index:1, gbr	color : black						
		SetOsdCol(3,7,2,0x8346cfff);//region 3~7,color index:2, gbr	color : 橘色								
		SetOsdCol(1,7,3,0xf3f3f3ff);//region 1~7,color index:3, gbr	color : blue
		#endif
		
        InitSW_region();
        x=index_x;
        y=index_y;
		
	    if((cd_type_loaded==CDDVD)||(cd_type_loaded==CDROM)) 
	    {
	       offset=1;
	       page=0;
	    }else 
	    {
	       offset=2;
	       page=1;
	    }

	    for(index_y=0;index_y<MAX_REGION;index_y++) 
	    {
	      if(prog_item[page][index_y][0]) 
	      {
	        for(index_x=1;index_x<MAX_PROG_SEL;index_x+=offset) 
	        {
	            ShowProgSel(0);
	        }
	      }
	    }
		
	    if(offset==2) 
	    {
	      //psprintf(RegionValStr[0],"[%d-%d]",show_trk_num(cd_trk_lo_now),show_trk_num(cd_trk_hi));
	      //PrintOsdMsg(STR_OS_SPACE,0x04<<4,0,1);
	      //board_type=BOARD_FULL_LINE;
	      psprintf(RegionValStr[1],"[%d-%d]",show_trk_num(cd_trk_lo_now),show_trk_num(cd_trk_hi));	    
	      PrintOsdMsg(STR_OS_SPACE, (0x04<<4)|1,0,1);
	    }
		
	    index_x=x;
	    index_y=y;
	    ShowProgSel(SW_REGION_ANTI);
	    //board_type=0;
	    #ifndef ALCO_MODIFY_PAL_OSD
	    draw_osd_board(1,BOARD_FULL_LINE);
	    draw_osd_board(2,BOARD_UP_LINE);
	    #endif
	    
	} //if (full_scrn&PROGRAM)
}
#endif // INDIGO_STYLE_OSDUI

void prog_func_down(void)
{
UINT8 y=index_y;
ShowProgSel(0);
#ifdef OSD_BMP_PROG
UINT8 old_index_x=index_x;
#endif

for(index_y++;index_y<MAX_PROG_ITEM;index_y++) {
if(prog_item[page][index_y][0]!=SET_NE) {
    if(prog_item[page][index_y][0]!=SET_NM) {
#ifdef PROG_12_ITEMS
        if(prog_item[page][index_y][index_x/2+2]==0) {
#else
				if(prog_item[page][index_y][index_x/2+1]==0) {
#endif
					if(index_x<MIN_FUNC_X) {
						//index_x=MIN_FUNC_X;//kenny mark it
						
						if(offset==2)
							index_x+=offset;
						else
							index_x+=prog_item[page][index_y][0];
						
						//printf("1.**x=%d y=%d page:%d \n",index_x,index_y,page);
						
					} else //if(index_x<MIN_FUNC_X)
						if (index_x>MAX_FUNC_X) {
							index_x=MAX_FUNC_X;
						}
				} //if(prog_item[page][index_y][index_x/2+1]==0)
				
			} //if(prog_item[page][index_y][0]!=SET_NM)
			
			break;
		} //if(prog_item[page][index_y][0]!=SET_NE)
		
	} //for(index_y++;index_y<MAX_PROG_ITEM;index_y++)
	
#ifdef OSD_BMP_PROG
    if ((flag_data == 0)&&(index_y >= MAX_PROG_ITEM - 2))
    {  
        index_y = MAX_PROG_ITEM - 2;
        index_x = old_index_x;
    }
    else
#endif	
	if(index_y==MAX_PROG_ITEM) {
		index_y=y;
	}

    OSD1000ISP_STATUS(OSDISP_PROG_DIR, OSDIR_PROGRAM);

	ShowProgSel(SW_REGION_ANTI);
	
#ifdef 	MONE_PROG
	printf("prog_func_down:x=%d y=%d page:%d \n",index_x,index_y,page);
#endif
}


void prog_func_up(void)
{
	if(index_y>2) {
		ShowProgSel(0);
		
		for(index_y--;index_y>0;index_y--) {
			if(prog_item[page][index_y][0]!=SET_NE)
				break;
		}

        OSD1000ISP_STATUS(OSDISP_PROG_DIR, OSDIR_PROGRAM);

		ShowProgSel(SW_REGION_ANTI);
	}
	
	
#ifdef 	MONE_PROG
	printf("prog_func_up:x=%d y=%d page:%d \n",index_x,index_y,page);
#endif
}



void prog_func_left(void)
{
	
	ShowProgSel(0);
	if( ((index_x>0)&&(prog_item[page][index_y][0]==SET_NM))||
    ((index_x>MIN_FUNC_X)&&(prog_item[page][index_y][0]==SET_FUNC)) )
	{
		for(;index_x>0;) {
			if(offset==2) {
				index_x-=offset;
			} else {
				index_x-=prog_item[page][index_y][0];
			}
			
			if(prog_item[page][index_y][index_x/2+1]!=SET_NE)
				break;
		}
	}

    OSD1000ISP_STATUS(OSDISP_PROG_DIR, OSDIR_PROGRAM);

	ShowProgSel(SW_REGION_ANTI);
	
#ifdef 	MONE_PROG
	printf("prog_func_left:x=%d y=%d page:%d \n",index_x,index_y,page);
#endif
}



void prog_func_right(void)
{
#ifdef PROG_12_ITEMS
	UINT8 max = MAX_PROG_SEL - offset - 2;
#else
	UINT8 max = MAX_PROG_SEL - offset;
#endif
	
	if( ((index_x<max)&&(prog_item[page][index_y][0]==SET_NM))||
    ((index_x<MAX_FUNC_X)&&(prog_item[page][index_y][0]==SET_FUNC)) )
	{
		ShowProgSel(0);
		
		for(;index_x<MAX_PROG_SEL;) {
			if(offset==2) {
				index_x+=offset;
			} else {
				index_x+=prog_item[page][index_y][0];
			}
			
			if(prog_item[page][index_y][index_x/2+1]!=SET_NE)
				break;
		}

        OSD1000ISP_STATUS(OSDISP_PROG_DIR, OSDIR_PROGRAM);

		ShowProgSel(SW_REGION_ANTI);
	}
	
#ifdef 	MONE_PROG
	printf("prog_func_right:x=%d y=%d page:%d \n",index_x,index_y,page);
#endif
}


/* move to ircmd.c
void prog_next(void)
{
	if (prog_cnt) {
		prog_index = (prog_index>=prog_cnt) ?  1 :(prog_index+1);
	}
}


void prog_prev(void)
{
	if (prog_cnt) {
		prog_index = ((prog_index>1) ? prog_index-1:prog_cnt);
	}
}
*/

