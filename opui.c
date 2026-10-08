/********************************************
*  opui.c
*
*  include  in Appdraw.c   
*  when normal setup menu.
* 
*  UI function:
*     UP,DOWN,SELECT,show_op_menu. 
* 
* Creator: libing
* Date:  2005-1-27 14:43
*******************************************/

//#include "gb_def.h"
#include "ircmd.h"
#include "func.h"
#include "fsNAV.h"
#include "config.h"
#include "regmap.h"
#include "global.h"
#include "subtitle.h"
#include "memmap.h"
#include "func.h"
#include "stdlib.h"
#include "cfont.h"

#include "osd.h"
#include "osdsup.h"
#include "osdfont.h"
#include "osd_str.h"
#include "endian.h"
#include "user_if.h"
#include "jpeglib.h"
#include "cdg.h"
#include "e2prom_map.h"

#ifdef OPUI_STOP_JPEGSLIDE  //hongfeng 2006/3/28 15:15
#ifdef JPG_OLD_PARSER_FLOW
    #ifdef JPG_EFFECT
    #include "jpegeffect.h"
    #endif
#else
    #include "pic_effect.h"
#endif
#endif

#ifdef OP_PLAYMODE
void exit_tray_menu(void);
void exit_op_menu(void);
enum
{
    SET_MODE=0,
    SET_ITEM=0x1,
};
enum
{
    SET_NE=0,
    SET_BS=0x1,
    SET_FUNC=0x2,
    SET_CHART=0x3,
    SET_SCALE=0x4
};	
#define BKCOLOR   0
#define FTCOLOR   2
#define SCORE_GRAY_COLOR 12
#define HL_COLOR  5
#define HL_X      228
#ifdef SDRAM_16Mb_Mode
	#define HL_Y1     40
	#define HL_Y2     72
#elif defined(SCORE_IN_PLAYMODE_MENU)
	#define HL_Y1     40
	#define HL_Y2     76
	#define HL_Y3     112	
#else
	#define HL_Y1     56 //chenzhao20050928
	#define HL_Y2     100 //chenzhao20050928
#endif

#ifdef SDRAM_16Mb_Mode
#define HL_WIDTH  12*16
#else	
	#define HL_WIDTH  15*16
#endif

#define HL_HIGH   1*32 //chenzhao20050928
#define HL_LINEWIDTH   28
#ifdef SDRAM_16Mb_Mode
	#define OP_REGION 1 
#else
	#define OP_REGION 3
#endif
#ifdef SDRAM_16Mb_Mode
	#define X_START   16//72
#else	
	#define X_START   15//72
#endif
#ifdef SDRAM_16Mb_Mode
	#define Y_START1  10
	#define Y_START2  18
#elif defined(SCORE_IN_PLAYMODE_MENU)
	#define Y_START1  9
	#define Y_START2  18
	#define Y_START3  27	
#else
	#define Y_START1  14
	#define Y_START2  25
#endif

 
#define __palette4F(G,B,R,A) \
        ( ((UINT32)((G)&0xff)<<24)|((UINT32)((B)&0xff)<<16)|((UINT32)((R)&0xff)<<8)|(A&0xff) )   
#ifdef SUPPORT_MP4_SUBTITLE
extern void supClearSubtitle(void);
#ifdef SUPPORT_OSDSRT
extern void osd_init_OSDSRT(void);
#endif
#endif
extern void osd_draw_HL(BYTE r,UINT32 xStart, UINT32 yStart,UINT32 xLen,UINT32 yLen, int LineWidth,BYTE color);
//extern void osd_DrawRegionString(BYTE xStart, BYTE yStart, BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r);
extern void osd_DrawRegionLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth, BYTE r);
extern void osd_draw_region_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor, BYTE r);
extern void ShowProPage(void);
extern void osd_init_menu(void);
extern void osd_DrawRegionString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r);
extern UINT16 Is_MP3_STATE(void);
extern UINT16 Is_JPEG_STATE(void);
extern void osd_init_tray_password(void);
extern void disp_fade_in(void);
extern int is_cdg_disc(int show);
#ifdef OPUI_STOP_JPEGSLIDE //hongfeng 2006/3/28 15:22
extern UINT16 Is_JPEG_SlideMode(void);  
#endif

#ifdef SCORE_IN_PLAYMODE_MENU
int  score_flag = 0;
extern BYTE CDG_IsCDGNow();
#endif
void Exit_Op_Region_ui(void);

int program_func_flag = 0;

#ifdef CD_INTRO_IN_PLAYMODE //cd_intro in playmode hongfeng 2005-08-23
int cd_intro_flag = 0;
#endif

#ifdef OP_RECEIVER_PLAYMODE //hongfeng 2005-08-23
enum
{
    sel_off=1,
    sel_random=2,
    sel_prog,
    #ifdef CD_INTRO_IN_PLAYMODE
    sel_cd_intro,
    #endif
};

enum
{
    sel_repeat_off=1,
    sel_repeat_title=2,
    sel_repeat_chapter=3,
    sel_repeat_all,
    sel_repeat_1,
    sel_repeat_dir,
};
#endif


#ifdef SCORE_IN_PLAYMODE_MENU
	#define LEVEL   3
#else
	#define LEVEL   2
#endif	
#define ITEM    7

UINT8 mode_id1,mode_id2,mode_id3;
int   sel_1 = 0,sel_2 = 0,sel_3 = 0;
int   old_sel_1 = 0,old_sel_2 = 0,old_sel_3 = 0;
#if 0//def CD_INTRO_IN_PLAYMODE //hongfeng 2005-08-23
#define sel_max 4
#else
BYTE sel_max=sel_prog;
#endif
BYTE  op_level = 0;
UINT8 op_sel[LEVEL]={1,1};
const UINT8 op_item[LEVEL][ITEM]=
{
	#ifdef SCORE_IN_PLAYMODE_MENU
	    {SET_FUNC,STR_OS_OFF,STR_OS_RANDOM,STR_OS_PROG,0,0,0},
	    {SET_FUNC,STR_OS_OFF,STR_OS_TITLE,STR_OS_CHAPTER,STR_OS_REP_ALL,STR_OS_REP_1,STR_OS_REP_DIR},
		{SET_FUNC,STR_OS_ON,STR_OS_OFF,0,0,0,0}
       #elif defined(CD_INTRO_IN_PLAYMODE)
           {SET_FUNC,STR_OS_OFF,STR_OS_RANDOM,STR_OS_PROG,STR_OS_CD_INTRO,0,0},
    	    {SET_FUNC,STR_OS_OFF,STR_OS_TITLE,STR_OS_CHAPTER,STR_OS_REP_ALL,STR_OS_REP_1,STR_OS_REP_DIR}	
	#else	
		{SET_FUNC,STR_OS_OFF,STR_OS_RANDOM,STR_OS_PROG,0,0,0},
    	{SET_FUNC,STR_OS_OFF,STR_OS_TITLE,STR_OS_CHAPTER,STR_OS_REP_ALL,STR_OS_REP_1,STR_OS_REP_DIR}		
	#endif	
};    
#ifdef SDRAM_16Mb_Mode// chenzhao20051104
#ifdef SUPPORT_MP4_SUBTITLE
static int IsSubtitle = 0;
#endif
#endif
void show_op_menu(void)
{ 
	const char   *str;
	const char   *str2;
	const char   *str3 __attribute__((unused));
    #ifdef SDRAM_16Mb_Mode// chenzhao20051104
	#ifdef SUPPORT_MP4_SUBTITLE
	if(g_pfnPollingSubtitle)
	{
		IsSubtitle = 1;
		supClearSubtitle();
	}	
	#endif
    #endif
    osd_init_menu();
    
    #ifdef SDRAM_16Mb_Mode
    SetOsdCol(1,1,0,__palette4F(  38,181, 49, 0xbf));//(G,B,R,A)
    #else
    SetOsdCol(3,3,0,__palette4F(  38,181, 49, 0xbf));//(G,B,R,A)
    #endif
    full_scrn = OP_MENU;

    #ifdef OPUI_STOP_JPEGSLIDE //chenzhao20060209
    if((full_scrn&OP_MENU)&&Is_JPEG_SlideMode())
        jpg_slide_time = 0xffffffff;
    #endif

    SetFullscrnCmdFuncPtr(op_func_up, op_func_down,  op_func_left,
                         op_func_right, op_func_select);
		
	if(sel_1<=sel_off)
	{
		if(shuffle_flag==1)
		sel_1=sel_random;
		else if(program_func_flag==1)
		sel_1=sel_prog;
        #ifdef CD_INTRO_IN_PLAYMODE //hongfeng 2005-08-23
        else if(bIntro==1)    
           sel_1=sel_cd_intro;
        #endif
		else
		sel_1 = sel_off;
	}
	if(sel_2<=1)
		sel_2 = 1;
#ifdef SCORE_IN_PLAYMODE_MENU		
	if(sel_3<=1)
		sel_3 = 1;		
	if(score_flag)	
		sel_3 = 1;
	else
		sel_3 = 2;	
#endif		
	if(play_state==VCD_STATE_STOP)
	{
			if(sel_1==2)
			sel_1=2;
			if(sel_1==1)
			sel_1=1;
			if(sel_1==3)
			sel_1=3;
                    #ifdef CD_INTRO_IN_PLAYMODE //hongfeng 2005-08-23
			if(sel_1==4)
			sel_1=4;         
                    #endif
	}
	else
	{
	    #ifdef CD_INTRO_IN_PLAYMODE//hongfeng 2005-08-23
	       if(sel_1==4)
	        {
        	if(shuffle_flag==1)
        	    sel_1=2;
        	if(program_func_flag==0)//libing 2005-6-30 14:02
			sel_1=1;
		}
           #endif   //CD_INTRO_IN_PLAYMODE
		if(sel_1==3)
        {
        	if(shuffle_flag==1)
        	sel_1=2;
        	if(program_func_flag==0)//libing 2005-6-30 14:02
			sel_1=1;
		}
        else
        if(sel_1==2)
        {
	        if(shuffle_flag==0)
	       	sel_1=1;
	       	if(program_func_flag==1)
	       	sel_1=3;
        }       		
	} 
	if(shuffle_flag==1||program_func_flag==1)
		sel_2=1;
	else
	{
		if(rep_mode==REPEAT_IDLE)
		{
		sel_2=1;
		}
		else
		{	
			if(cd_type_loaded==CDDVD)
			{
				//if(sel_2==4)
					//sel_2=sel_repeat_off;
				if(sel_2==sel_repeat_1)
					sel_2=sel_repeat_off;
				else if(sel_2==sel_repeat_dir)
					sel_2=sel_repeat_off;
				if(rep_mode == REPEAT_TRACK)
					sel_2=sel_repeat_chapter;
				else if(rep_mode == REPEAT_DISC)
					sel_2=sel_repeat_title;	
                else if(rep_mode==REPEAT_DVDDISC)//hongfeng add 2005-11-01
                    sel_2=sel_repeat_all;
			}else if((cd_type_loaded==CDROM)|| ((cd_type_loaded==CDDA)&&(!CDG_IsCDGNow()))||(Is_MP3_STATE())||(GetCurrentFileType() == CDROM_WMA)||(Is_JPEG_STATE())||(setup_IsMICOff())
			#ifndef NO_MIC
			||(Micflag==0)
			#endif
			)
			{
				if(sel_2==sel_repeat_title)
					sel_2=sel_repeat_off;
				if(sel_2==sel_repeat_chapter)
					sel_2=sel_repeat_off;
				if(rep_mode == REPEAT_DISC)
					sel_2=4;
				else if(rep_mode == REPEAT_TRACK)
					sel_2=sel_repeat_1;
				else if(rep_mode == REPEAT_DIRECTORY)
					sel_2=sel_repeat_dir;	
                else if(rep_mode==REPEAT_DVDDISC)//hongfeng add 2005-11-01
                    sel_2=sel_repeat_all;
			}
		}	 				
	} 				
	if(pFsJpeg->gifsState == FS_STATE_JPEG||Is_JPEG_STATE())
	{
		if(sel_1==3)
		{
			if(shuffle_flag==1)
			{
				sel_1=2;
			}else{
				sel_1=1;
			}
		}
	}
	else if(pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)
	{	
		if(sel_1==2)
		{
			if(program_func_flag==1)
				sel_1 = 3;
			else
				sel_1 = 1;	
		}			
	} 				
	if(shuffle_flag==1)
        sel_1=sel_random;
	else if(program_func_flag==1)
        sel_1=sel_prog;
    #ifdef CD_INTRO_IN_PLAYMODE
    else if(bIntro==1)  //hongfeng 2005-08-23
        sel_1=sel_cd_intro;
    #endif
		
    mode_id1 = op_item[0][sel_1]; 
    mode_id2 = op_item[1][sel_2];       
    str  = _OsdMessegeFont1[osd_font_mode][mode_id1];
    str2 = _OsdMessegeFont1[osd_font_mode][mode_id2];  
    op_level=0; 
       
    const char *menu_item_0,*menu_item_1,*menu_item_2;  
    menu_item_0 = _OsdMessegeFont1[osd_font_mode][STR_OS_PLAYMODE];
    menu_item_1 = _OsdMessegeFont1[osd_font_mode][STR_OS_MODE];
    menu_item_2 = _OsdMessegeFont1[osd_font_mode][STR_OS_REPEAT]; 
    #ifdef SDRAM_16Mb_Mode
	    osd_DrawRegionString(2,2,menu_item_0,FTCOLOR,0,OP_REGION);	    
	    osd_DrawRegionString(2,Y_START1,menu_item_1,FTCOLOR,0,OP_REGION);
	    osd_DrawRegionString(2,Y_START2,menu_item_2,FTCOLOR,0,OP_REGION);
	    osd_draw_HL( OP_REGION, HL_X, HL_Y1, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);
	    osd_DrawRegionString(X_START,Y_START1,(BYTE *)str,FTCOLOR,5,OP_REGION);
	    osd_DrawRegionString(X_START,Y_START2,(BYTE *)str2,FTCOLOR,0,OP_REGION);
    #else
	    osd_DrawRegionString(2,1,menu_item_0,FTCOLOR,0,OP_REGION);
	    osd_DrawRegionString(2,Y_START1,menu_item_1,FTCOLOR,0,OP_REGION);//14
	    osd_DrawRegionString(2,Y_START2,menu_item_2,FTCOLOR,0,OP_REGION);//26	    
	    osd_draw_HL( OP_REGION, HL_X, HL_Y1, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);    
	    osd_DrawRegionString(X_START,Y_START1,(BYTE *)str,FTCOLOR,5,OP_REGION);
	    osd_DrawRegionString(X_START,Y_START2,(BYTE *)str2,FTCOLOR,0,OP_REGION);
		#ifdef SCORE_IN_PLAYMODE_MENU    
			const char *menu_item_3;    
		    mode_id3 = op_item[2][sel_3]; 
		    menu_item_3 =  _OsdMessegeFont1[osd_font_mode][STR_OS_SCORE];
	    	str3 = _OsdMessegeFont1[osd_font_mode][mode_id3]; 
		    if((cd_type_loaded==CDROM)||((cd_type_loaded==CDDA)&&(!CDG_IsCDGNow()))||(Is_MP3_STATE())||(GetCurrentFileType() == CDROM_WMA)||(Is_JPEG_STATE())||(setup_IsMICOff())
		    #ifndef NO_MIC
			||(Micflag==0)
			#endif
			)
		    {
		    	str3 = _OsdMessegeFont1[osd_font_mode][STR_OS_OFF];
		    	osd_DrawRegionString(2,Y_START3,menu_item_3,SCORE_GRAY_COLOR,0,OP_REGION);
			    osd_DrawRegionString(X_START,Y_START3,(BYTE *)str3,SCORE_GRAY_COLOR,0,OP_REGION);
			}
			else
			{    
			    osd_DrawRegionString(2,Y_START3,menu_item_3,FTCOLOR,0,OP_REGION);
			    osd_DrawRegionString(X_START,Y_START3,(BYTE *)str3,FTCOLOR,0,OP_REGION);
			}
		#endif
		#ifdef PLAYMODE_RUN_PAUSE
			run_pause(0);
		#endif	
    #endif
    old_sel_1 = sel_1;
    old_sel_2 = sel_2;
    #ifdef SCORE_IN_PLAYMODE_MENU
    	old_sel_3 = sel_3;
    #endif	
}   

int r __attribute__((unused));
int u __attribute__((unused));
void exit_op_menu(void)
{	
	osd_tog_region(0, OSD_OFF);
    safe_srn_forceOFF();
    safe_srn_off();
	#ifdef SDRAM_16Mb_Mode
        regs0->osd_base_addr=GetOSDBackUpAddress();
    #endif
    
    #ifdef OPUI_STOP_JPEGSLIDE  //hongfeng 2006/3/28 15:14
    if((jpg_slide_time==0xffffffff)&&(full_scrn&OP_MENU)&&(!vpp_zoom)&&(!rotate_mode))
        jpg_slide_time = JPEG_SLIDE_TIME;
    #endif
    
	full_scrn = 0;
    delay_srv_10ms(3);//libing 2005-4-14 23:34 to avoid the disturb bug at op menu fade out
    #ifdef SUPPORT_MP4_SUBTITLE  // chenzhao20051104
    if(cd_type_loaded == CDROM)  
        osd_init_OSDSRT();
    else
    #endif
	osd_init();
#ifdef PLAYMODE_RUN_PAUSE
	ircmd_play();
#endif
#ifdef SDRAM_16Mb_Mode
	show_angle_osd();
    restore_osd_msg();
    if(u)//libing for display&OP_MENU 
    	{
    		//DispFadeIn();
    		if(r==1)
    		t_disp=1;
    		if(r==2)
    		t_disp=2;
    		disp_fade_in();
    		u=0;
    	}
    #ifdef SUPPORT_OSDSRT	
	    if(IsSubtitle)
	    {
	      supOpenSubtitle();
	    }		
    #endif
#endif    
#ifdef SCORE_IN_PLAYMODE_MENU
	if(score_flag)
		ircmd_score();
#endif	
}

/*********************************************************
for score function when VCD&PBC_ON can select score item.
*********************************************************/
#ifdef SCORE_IN_PLAYMODE_MENU
void Show_Op_Menu_When_PBC_On()
{
	const char *c0,*c1 __attribute__((unused));
	const char *c2,*c3 __attribute__((unused));
    #ifdef SDRAM_16Mb_Mode// chenzhao20051104
	#ifdef SUPPORT_MP4_SUBTITLE
	if(g_pfnPollingSubtitle)
	{
		IsSubtitle = 1;
		supClearSubtitle();
	}	
	#endif
	#endif
    osd_init_menu();
    SetOsdCol(3,3,0,__palette4F(  38,181, 49, 0xbf));//(G,B,R,A)
    full_scrn = OP_MENU;
    SetFullscrnCmdFuncPtr(ircmd_null, ircmd_null,  op_func_left,
                         op_func_right, op_func_select);
	
	if(((cd_type_loaded==CDVCD10)||(cd_type_loaded==CDVCD20)||(cd_type_loaded==CDSVCD)||(Micflag))&&IsPBCOn())
	{
		const char *menu_item_0,*menu_item_1,*menu_item_2,*menu_item_3;  
	    menu_item_0 = _OsdMessegeFont1[osd_font_mode][STR_OS_PLAYMODE];
	    menu_item_1 = _OsdMessegeFont1[osd_font_mode][STR_OS_MODE];
	    menu_item_2 = _OsdMessegeFont1[osd_font_mode][STR_OS_REPEAT]; 
	    menu_item_3 = _OsdMessegeFont1[osd_font_mode][STR_OS_SCORE];
		c0 = _OsdMessegeFont1[osd_font_mode][STR_OS_OFF];
		//c1 = _OsdMessegeFont1[osd_font_mode][STR_OS_OFF];
		if(score_flag)
			sel_3 = 1;
		else
			sel_3 = 2;		
		mode_id3 = op_item[2][sel_3];
		c2 = _OsdMessegeFont1[osd_font_mode][mode_id3];
		printf("%%%%%%%%%%%%%% mode_id3 = %d\n",mode_id3);
		//printf_w( "%%%%%%%%%%%%%% %d %d %d %d %s\n", op_level, sel_3, osd_font_mode, mode_id3, c2 );
		osd_DrawRegionString(2,1,menu_item_0,FTCOLOR,0,OP_REGION);
	    osd_DrawRegionString(2,Y_START1,menu_item_1,SCORE_GRAY_COLOR,0,OP_REGION);//14
	    osd_DrawRegionString(2,Y_START2,menu_item_2,SCORE_GRAY_COLOR,0,OP_REGION);//26	    

	    osd_draw_HL( OP_REGION, HL_X, HL_Y3, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);    
	    osd_DrawRegionString(X_START,Y_START1,(BYTE *)c0,SCORE_GRAY_COLOR,0,OP_REGION);
	    osd_DrawRegionString(X_START,Y_START2,(BYTE *)c0,SCORE_GRAY_COLOR,0,OP_REGION);

	    if(Micflag==1)
	    {
		    osd_DrawRegionString(2,Y_START3,menu_item_3,FTCOLOR,0,OP_REGION);
	    osd_DrawRegionString(X_START,Y_START3,(BYTE *)c2,FTCOLOR,5,OP_REGION);
		}else{
			c2 = _OsdMessegeFont1[osd_font_mode][STR_OS_OFF];
		    osd_DrawRegionString(2,Y_START3,menu_item_3,SCORE_GRAY_COLOR,0,OP_REGION);
		    osd_DrawRegionString(X_START,Y_START3,(BYTE *)c2,SCORE_GRAY_COLOR,5,OP_REGION);
	    }
	    op_level = 2;
	}
}
#endif


void op_func_up(void)
{    
    const char  *str;
    const char  *str2;
    const char  *str3 __attribute__((unused));
    if(op_level==1)
    {
	    sel_2 = old_sel_2;
	    mode_id1 = op_item[op_level-1][sel_1];
	    mode_id2 = op_item[op_level][sel_2];		    
	    str  = _OsdMessegeFont1[osd_font_mode][mode_id1];
	    str2 = _OsdMessegeFont1[osd_font_mode][mode_id2];	  
	    
	    #ifdef SDRAM_16Mb_Mode
		    osd_draw_HL( OP_REGION, HL_X, HL_Y1, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);    
		    osd_draw_HL( OP_REGION, HL_X, HL_Y2, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,0);
		    osd_DrawRegionString(X_START,Y_START1,(BYTE *)str,FTCOLOR,5,OP_REGION);
		    osd_DrawRegionString(X_START,Y_START2,(BYTE *)str2,FTCOLOR,0,OP_REGION);
	    #else
		    osd_draw_HL( OP_REGION, HL_X, HL_Y1, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);    
		    osd_draw_HL( OP_REGION, HL_X, HL_Y2, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,0);
		    osd_DrawRegionString(X_START,Y_START1,(BYTE *)str,FTCOLOR,5,OP_REGION);
			osd_DrawRegionString(X_START,Y_START2,(BYTE *)str2,FTCOLOR,0,OP_REGION); 
			
			#if 0//def 	SCORE_IN_PLAYMODE_MENU
				mode_id3 = op_item[op_level+1][sel_3];
		    	str3 = _OsdMessegeFont1[osd_font_mode][mode_id3];
				osd_draw_HL( OP_REGION, HL_X, HL_Y3, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,0);
				osd_DrawRegionString(X_START,Y_START3,(BYTE *)str3,FTCOLOR,0,OP_REGION);
			#endif
			
		#endif
		op_level=0;
    }
#ifdef SCORE_IN_PLAYMODE_MENU    
    else if(op_level==2)
    { 
    	sel_3 = old_sel_3;
		mode_id1 = op_item[op_level-2][sel_1];
		mode_id2 = op_item[op_level-1][sel_2];	
		mode_id3 = op_item[op_level][sel_3];
		str  = _OsdMessegeFont1[osd_font_mode][mode_id1];
		str2 = _OsdMessegeFont1[osd_font_mode][mode_id2];
		str3 = _OsdMessegeFont1[osd_font_mode][mode_id3];
		#ifdef SDRAM_16Mb_Mode 
		    osd_draw_HL( OP_REGION, HL_X, HL_Y1, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,0);    
		    osd_draw_HL( OP_REGION, HL_X, HL_Y2, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);
		    osd_DrawRegionString(X_START,Y_START2,(BYTE *)str2,FTCOLOR,5,OP_REGION);
			osd_DrawRegionString(X_START,Y_START1,(BYTE *)str,FTCOLOR,0,OP_REGION);
		#else
			osd_draw_HL( OP_REGION, HL_X, HL_Y1, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,0);    
		    osd_draw_HL( OP_REGION, HL_X, HL_Y2, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5); 
			osd_draw_HL( OP_REGION, HL_X, HL_Y3, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,0);
			osd_DrawRegionString(X_START,Y_START1,(BYTE *)str,FTCOLOR,0,OP_REGION);
			osd_DrawRegionString(X_START,Y_START2,(BYTE *)str2,FTCOLOR,5,OP_REGION);
			osd_DrawRegionString(X_START,Y_START3,(BYTE *)str3,FTCOLOR,0,OP_REGION);	
		#endif
		op_level=1;
    }
#endif
}
void op_func_down(void)
{
    const char *str;
    const char *str2;
    const char *str3 __attribute__((unused));
    if(op_level==0)
    {    		
	    sel_1  = old_sel_1;
	    mode_id1 = op_item[op_level][sel_1];
	    mode_id2 = op_item[op_level+1][sel_2];  	
	    
	    str  = _OsdMessegeFont1[osd_font_mode][mode_id1]; 
	    str2 = _OsdMessegeFont1[osd_font_mode][mode_id2]; 
	    
	    #ifdef SDRAM_16Mb_Mode
		    osd_draw_HL( OP_REGION, HL_X, HL_Y1, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,0);
		    osd_draw_HL( OP_REGION, HL_X, HL_Y2, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);
		    osd_DrawRegionString(X_START,Y_START1,(BYTE *)str,FTCOLOR,0,OP_REGION);
		    osd_DrawRegionString(X_START,Y_START2,(BYTE *)str2,FTCOLOR,5,OP_REGION);
	    #else
		    osd_draw_HL( OP_REGION, HL_X, HL_Y1, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,0);        
		    osd_draw_HL( OP_REGION, HL_X, HL_Y2, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);
		    osd_DrawRegionString(X_START,Y_START1,(BYTE *)str,FTCOLOR,0,OP_REGION);
			osd_DrawRegionString(X_START,Y_START2,(BYTE *)str2,FTCOLOR,5,OP_REGION);	
			#if 0//def SCORE_IN_PLAYMODE_MENU
				mode_id3 = op_item[op_level+2][sel_3];
	    		str3 = _OsdMessegeFont1[osd_font_mode][mode_id3];
	    		if((cd_type_loaded==CDROM)||((cd_type_loaded==CDDA)&&(!CDG_IsCDGNow()))||(Is_MP3_STATE())||(GetCurrentFileType() == CDROM_WMA)||(Is_JPEG_STATE())||(setup_IsMICOff())
	    		#ifndef NO_MIC
				||(Micflag==0)
				#endif
				)
	    		{
	    			osd_draw_HL( OP_REGION, HL_X, HL_Y3, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,0);
					osd_DrawRegionString(X_START,Y_START3,(BYTE *)str3,SCORE_GRAY_COLOR,0,OP_REGION);	 
	    		}
	    		else
	    		{
					osd_draw_HL( OP_REGION, HL_X, HL_Y3, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,0);
					osd_DrawRegionString(X_START,Y_START3,(BYTE *)str3,FTCOLOR,0,OP_REGION);	 
				}
			#endif
		#endif	     
		op_level=1;    
    }
#ifdef 	SCORE_IN_PLAYMODE_MENU	    
    else if(op_level==1)
    {
    	if((cd_type_loaded==CDROM)||((cd_type_loaded==CDDA)&&(!CDG_IsCDGNow()))||(Is_MP3_STATE())||(GetCurrentFileType() == CDROM_WMA)||(Is_JPEG_STATE())||(setup_IsMICOff())
    	#ifndef NO_MIC
		||(Micflag==0)
		#endif
		)
    	return;
    	sel_2 = old_sel_2;
	    mode_id1 = op_item[op_level-1][sel_1]; 	
	    mode_id2 = op_item[op_level][sel_2]; 	
	    mode_id3 = op_item[op_level+1][sel_3];       	
	    str  = _OsdMessegeFont1[osd_font_mode][mode_id1]; 
	    str2 = _OsdMessegeFont1[osd_font_mode][mode_id2]; 
	    str3 = _OsdMessegeFont1[osd_font_mode][mode_id3];	    
	    	    
	    #ifdef SDRAM_16Mb_Mode
		    osd_draw_HL( OP_REGION, HL_X, HL_Y1, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);    
		    osd_draw_HL( OP_REGION, HL_X, HL_Y2, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,0);
		    osd_DrawRegionString(X_START,Y_START1,(BYTE *)str,FTCOLOR,5,OP_REGION);
		    osd_DrawRegionString(X_START,Y_START2,(BYTE *)str2,FTCOLOR,0,OP_REGION);
		#else
		    osd_draw_HL( OP_REGION, HL_X, HL_Y1, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,0);    
		    osd_draw_HL( OP_REGION, HL_X, HL_Y2, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,0);
		    osd_draw_HL( OP_REGION, HL_X, HL_Y3, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);
		    osd_DrawRegionString(X_START,Y_START1,(BYTE *)str,FTCOLOR,0,OP_REGION);
			osd_DrawRegionString(X_START,Y_START2,(BYTE *)str2,FTCOLOR,0,OP_REGION);
			osd_DrawRegionString(X_START,Y_START3,(BYTE *)str3,FTCOLOR,5,OP_REGION);				    			   					    
		#endif	
		op_level=2;
    }
#endif    
}    
void op_func_select(void)
{
	if(op_level==0)
	{
	       if((sel_1==sel_cd_intro)&&!( is_cdg_disc(1)))//kingslon add op cdg no intro 20051017
	        {
	            if(shuffle_flag==1)
	            {
                   exit_op_menu();
                   shuffle_flag=0;
                   ircmd_preview();
	            }
                    else
		{
                    exit_op_menu();
                    ircmd_preview();
                    }
	        }
		if(sel_1==sel_prog)
		{
	        if(bIntro == 1) //hongfeng add 2005-10-18
            bIntro = 0;
            rep_ab_mode = REPEAT_AB_IDLE;//chenzhao 20051108
			if(shuffle_flag==1)
			{		
	    	exit_op_menu();
	    	ircmd_prog();
	    	shuffle_flag=0;
			}
            else
			{		
		    exit_op_menu(); 
		    program_func_flag=1; //tsinhwa,add 2005-8-31 23:12
		    ircmd_prog(); 
			}   
		}
		else if(sel_1==sel_random)
		{
		    if(bIntro == 1) //hongfeng add 2005-09-02
                    bIntro = 0;
            
			if((cd_type_loaded==CDROM_MP4)||(cd_type_loaded==CDROM_AVI))
	    		{
	    			invalid_key();
	    			shuffle_flag=0;
	    		}
	    		else if(program_func_flag==1)
	    		{
	    			exit_op_menu();
	    			prog_func_off();
	    			program_func_flag=0;
	    			shuffle_flag=1;
	    			ircmd_shuffle();
	    			prog_cnt = 0;
	    			#ifdef SCORE_IN_PLAYMODE_MENU
	    			if(score_flag==0)
	    			#endif
	    			PrintOsdMsg(STR_OS_PROG_CNL,REGION2,1,0);
	    		}	
	    		else
	    		{
					exit_op_menu();
					shuffle_flag = 1;
					ircmd_shuffle();
				}		
		}	
		else if(sel_1==sel_off)
		{
			exit_op_menu();
            if(shuffle_flag==1)//hongfeng modify 2005-11-07
            {
			shuffle_flag = 0;
			ircmd_shuffle();		
            }
			if(program_func_flag==1)
			{
				prog_func_off();
				program_func_flag=0;
				prog_cnt = 0;
				PrintOsdMsg(STR_OS_PROG_CNL,REGION2,1,0);		
			}	
                    #ifdef CD_INTRO_IN_PLAYMODE //hongfeng 2005-08-23
                    else if(bIntro==1)
                    {
                    ircmd_preview();
                    }
                    #endif
		}	
	}
    else if(op_level==1)
	{
		int t=0;
		int m=0;
		int k=0;
		int md=4;	
		if(program_func_flag==1)
		{
			prog_func_off();
			prog_cnt = 0;
			program_func_flag = 0;
			exit_op_menu();
			delay_srv_10ms(20);
			k=1;		
		}	
		else if(rep_ab_mode != REPEAT_AB_IDLE)
		{
			rep_ab_mode = REPEAT_AB_IDLE;
			t=1;
		}	
		else if(shuffle_flag==1)
		{
			if(sel_2==1)
			m=0;
			else
			m=1;
		}	
		if(sel_2==6)
		{
			shuffle_flag = 0;
			//PrintOsdMsg(STR_OS_RANDOM|(STR_OS_ON<<OSDSTR_ID_TOTL_BIT),REGION2,1,md);
			exit_op_menu();
			rep_mode = REPEAT_DIRECTORY;
			ircmd_repeat_all();
			
		}	
		else if(sel_2==5)
		{
			shuffle_flag = 0;
			//PrintOsdMsg(STR_OS_RANDOM|(STR_OS_ON<<OSDSTR_ID_TOTL_BIT),REGION2,1,md);
			exit_op_menu();
			rep_mode = REPEAT_TRACK;
			ircmd_repeat_all();
			
		}	
		else if(sel_2==4)
		{
			shuffle_flag = 0;
			//PrintOsdMsg(STR_OS_RANDOM|(STR_OS_ON<<OSDSTR_ID_TOTL_BIT),REGION2,1,md);
			exit_op_menu();
			rep_mode = REPEAT_DVDDISC;
			ircmd_repeat_all();
				
		}
		else if(sel_2==3)
		{
			shuffle_flag = 0;
			//PrintOsdMsg(STR_OS_RANDOM|(STR_OS_ON<<OSDSTR_ID_TOTL_BIT),REGION2,1,md);
			exit_op_menu();
			rep_mode = REPEAT_TRACK;
			ircmd_repeat_all();
			
		}	
		else if(sel_2==2)
		{
			shuffle_flag = 0;
			//PrintOsdMsg(STR_OS_RANDOM|(STR_OS_ON<<OSDSTR_ID_TOTL_BIT),REGION2,1,md);
			exit_op_menu();
			rep_mode = REPEAT_DISC;
			ircmd_repeat_all();
					
		}   
		else if(sel_2==1)
		{
			exit_op_menu();
			rep_mode = REPEAT_IDLE;
			ircmd_repeat_all();
					
		}   
		//rep_ab_mode = REPEAT_AB_IDLE;
		if(t)
		{		
			#ifdef SCORE_IN_PLAYMODE_MENU
	    	if(score_flag==0)
	    	#endif
			PrintOsdMsg(STR_OS_REP_AB_CNL,REGION2,2,0);
			t=0;
		}
		if(m)
		{
			#ifdef SCORE_IN_PLAYMODE_MENU
	    	if(score_flag==0)
	    	#endif
			PrintOsdMsg(STR_OS_RANDOM|(STR_OS_OFF<<OSDSTR_ID_TOTL_BIT),REGION2,1,md);
			m=0;
		}
		if(k)
		{
			#ifdef SCORE_IN_PLAYMODE_MENU
	    	if(score_flag==0)
	    	#endif
			PrintOsdMsg(STR_OS_PROG_CNL,REGION2,1,0);
			k=0;
		}
	}
#ifdef SCORE_IN_PLAYMODE_MENU	
	else if(op_level==2)
	{
		if(sel_3 == 1)
		{
			exit_op_menu();
			if(cd_type_loaded!=CDROM)
			{
			ircmd_score();
			full_scrn = SCORE;
		}
		else
				invalid_key();
		}
		else
		{
		    exit_op_menu();
		    full_scrn = 0;
		    score_flag = 0;
		    PrintOsdMsg(STR_OS_SCORE|(STR_OS_OFF<<OSDSTR_ID_TOTL_BIT),REGION1,1,4);
		}
	}	    	
#endif		
}    
void op_func_left(void)
{
    const char  *str;
 
    if(pFsJpeg->gifsState == FS_STATE_LIST) //((cd_type_loaded==CDROM_JPEG)&&//&& (pFsJpeg->gifsbPreview) && (pFsJpeg->gbfsSlide == 0) )
    	resumeMSF=1;
    if(op_level==0)
    {    	
    	sel_1++;
        #ifdef CD_INTRO_IN_PLAYMODE //hongfeng 2005-08-25 //chenzhao20050928
        if((cd_type_loaded == CDDA)&&!( is_cdg_disc(1)))//kingslon add op cdg no intro 20051017
            sel_max=sel_cd_intro;
        else
            sel_max=sel_prog;
        #endif
        if(((cd_type_loaded == CDVCD10)||(cd_type_loaded == CDVCD20)||(cd_type_loaded == CDSVCD))&&(sel_1 == sel_random))
            sel_1++;    //VCD don't need random function hongfeng    
        
    	if(sel_1>sel_max)    
        sel_1=sel_off;	
	    if(pFsJpeg->gifsState == FS_STATE_JPEG||Is_JPEG_STATE())
	    {
	    	if(sel_1==sel_prog)//kingslon add op jpg off and random 20051017
	    		sel_1=sel_off;
	    }
	    else if(pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)
	    {
	    	if(sel_1==sel_random)//hongfeng modify op mp4 off and program 20051101
	    	sel_1=sel_prog;
	    }			
    mode_id1=op_item[op_level][sel_1];
    str=_OsdMessegeFont1[osd_font_mode][mode_id1];    
    #ifdef SDRAM_16Mb_Mode
    osd_draw_HL( OP_REGION, HL_X, HL_Y1, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);
    osd_DrawRegionString(X_START,Y_START1,(BYTE *)str,FTCOLOR,5,OP_REGION);
    #else
    osd_draw_HL( OP_REGION, HL_X, HL_Y1, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);
    osd_DrawRegionString(X_START,Y_START1,(BYTE *)str,FTCOLOR,5,OP_REGION); 
    #endif
    }
    else if(op_level==1)
    {
    	sel_2++;        
    #ifdef OP_RECEIVER_PLAYMODE //hongfeng 2005-09-02
        if(cd_type_loaded==CDDVD)
    	{
	    	if(sel_2>4)
	    	sel_2=1;
    	}
    #else
        if(cd_type_loaded==CDDVD)
    	{
	    	if(sel_2>3)
	    	sel_2=1;
    	}
    #endif  //OP_RECEIVER_PLAYMODE
	    else if(cd_type_loaded==CDROM)
	    {
	    	if(sel_2==sel_repeat_title)
	    	sel_2=sel_repeat_1;	
	    	if(sel_2==sel_repeat_chapter)
	    	sel_2=sel_repeat_1;
	    	if(sel_2>sel_repeat_dir)
	    	sel_2=sel_repeat_off;	
	    }
	    else
	    {
	    	if(sel_2==2)
	    	sel_2=4;	
	    	if(sel_2==3)
	    	sel_2=4;
	    	if(sel_2>5)
	    	sel_2=1;
	    }
	    mode_id1=op_item[op_level][sel_2];
	    str=_OsdMessegeFont1[osd_font_mode][mode_id1];    
	    #ifdef SDRAM_16Mb_Mode
	    osd_draw_HL( OP_REGION, HL_X, HL_Y2, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);
	    osd_DrawRegionString(X_START,Y_START2,(BYTE *)str,FTCOLOR,5,OP_REGION);
	    #else
	    osd_draw_HL( OP_REGION, HL_X, HL_Y2, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);
	    osd_DrawRegionString(X_START,Y_START2,(BYTE *)str,FTCOLOR,5,OP_REGION);
	    #endif
    }
#ifdef SCORE_IN_PLAYMODE_MENU 
    else if(op_level==2)
    {
    	sel_3++;
    	if(sel_3 >= 3)
    		sel_3 = 1;   
    	mode_id1 = op_item[op_level][sel_3];
	    str = _OsdMessegeFont1[osd_font_mode][mode_id1];	
		osd_draw_HL( OP_REGION, HL_X, HL_Y3, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);
		osd_DrawRegionString(X_START,Y_START3,(BYTE *)str,FTCOLOR,5,OP_REGION);
	}
#endif	
}     
void op_func_right(void)
{
    const char  *str;
    
    if(op_level==0)
    {
    	sel_1--;
        if(((cd_type_loaded == CDVCD10)||(cd_type_loaded == CDVCD20)||(cd_type_loaded == CDSVCD))&&(sel_1 == sel_random))
            sel_1--;    //VCD don't need random function hongfeng    
    	if(sel_1<1)    
         #ifdef CD_INTRO_IN_PLAYMODE    //hongfeng 2005-08-23
            {
            if((cd_type_loaded == CDDA)&&!( is_cdg_disc(1)))//kingslon add op cdg no intro 20051017
                sel_1=sel_cd_intro;
            else
                sel_1=sel_prog;	
            }
         #endif
	    if(pFsJpeg->gifsState == FS_STATE_JPEG||Is_JPEG_STATE())
	    {
	    	if(sel_1==sel_prog)//kingslon add op jpg off and random 20051017
	    	{
	    		sel_1=sel_random;
	    	}
	    }
	    else if(pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)
	    {
	    	if(sel_1==sel_random)//kingslon add op jpg off and random 20051017
	    	sel_1 = sel_off;
	    }   		
	    mode_id1=op_item[op_level][sel_1];
	    str=_OsdMessegeFont1[osd_font_mode][mode_id1];
	    
	    printf_w( "*** %d %d %d %d %s\n", op_level, sel_1, osd_font_mode, mode_id1, str );
	    #ifdef SDRAM_16Mb_Mode
	    osd_draw_HL( OP_REGION, HL_X, HL_Y1, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);
	    osd_DrawRegionString(X_START,Y_START1,(BYTE *)str,FTCOLOR,5,OP_REGION);
	    #else
	    osd_draw_HL( OP_REGION, HL_X, HL_Y1, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);
	    osd_DrawRegionString(X_START,Y_START1,(BYTE *)str,FTCOLOR,5,OP_REGION);
	    #endif   
    }
    else if(op_level==1)
    { 
	    sel_2--;
        #ifdef OP_RECEIVER_PLAYMODE //hongfeng 2005-09-02
	    if(cd_type_loaded==CDDVD)
	    {
	    	if(sel_2>4)
	    	sel_2=1;
	    	else if(sel_2<1)
	    	sel_2=4;
	    }
        #else
	    if(cd_type_loaded==CDDVD)
	    {
	    	if(sel_2>3)
	    	sel_2=1;
	    	else if(sel_2<1)
	    	sel_2=3;
	    }
        #endif  //OP_RECEIVER_PLAYMODE
	    else if(cd_type_loaded==CDROM)
	    {
	    	if(sel_2==sel_repeat_title)    //hongfeng modify 2005-11-01
	    	sel_2=sel_repeat_off;  
            if(sel_2==sel_repeat_chapter)
	    	sel_2=sel_repeat_off;  
            if(sel_2==sel_repeat_all)
	    	sel_2=sel_repeat_off;  
	    	if(sel_2<sel_repeat_off)
	    	sel_2=sel_repeat_dir;
	    }	
	    else
	    {
	    	if(sel_2==2)
	    	sel_2=1;
	    	if(sel_2==3)
	    	sel_2=1;    	    
	    	if(sel_2<1)
	    	sel_2=5;
	    }
	    mode_id1=op_item[op_level][sel_2];
	    str=_OsdMessegeFont1[osd_font_mode][mode_id1];
	    
	    #ifdef SDRAM_16Mb_Mode
	    osd_draw_HL( OP_REGION, HL_X, HL_Y2, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);
	    osd_DrawRegionString(X_START,Y_START2,(BYTE *)str,FTCOLOR,5,OP_REGION);
	    #else
	    osd_draw_HL( OP_REGION, HL_X, HL_Y2, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);
	    osd_DrawRegionString(X_START,Y_START2,(BYTE *)str,FTCOLOR,5,OP_REGION); 
	    #endif 
    } 
#ifdef SCORE_IN_PLAYMODE_MENU      
    else if(op_level==2)
    {
    	sel_3--;
    	if(sel_3 <= 0)
    	sel_3 = 2;
    	mode_id1 = op_item[op_level][sel_3];
    	str = _OsdMessegeFont1[osd_font_mode][mode_id1];
    	osd_draw_HL( OP_REGION, HL_X, HL_Y3, HL_WIDTH, HL_HIGH,HL_LINEWIDTH,5);
	    osd_DrawRegionString(X_START,Y_START3,(BYTE *)str,FTCOLOR,5,OP_REGION); 
    }
#endif    	
}
void play_mode_cancel(void)
{
	sel_1=1;
	sel_2=1;
	rep_mode = REPEAT_IDLE;//libing 2005-6-29 21:42
    rep_ab_mode = REPEAT_AB_IDLE;
    prog_func_off();
    program_func_flag = 0;
    shuffle_flag=0;
}            	
#endif//OP_PLAYMODE

/********************************************************
********************************************************/

#ifdef ORITRON_TRAY_PASSWORD
BYTE tray_level;

void show_pwd_ui(void)
{
	tray_psd_exit_flag=1;
	osd_init_tray_password();
	full_scrn = (SETUP|TRAY_PWD);
	printf("full_scrn:%d\n",full_scrn);
	SetOsdCol(0,0,0,__palette4F(  38,181, 49, 0xbf));
	osd_DrawRegionString(1,1,"LOCK THE TRAY?",2,0,0);
	osd_draw_region_rect(256,0,192,38,15,0);	
	tray_level=0;	
	SetFullscrnCmdFuncPtr( ircmd_null, ircmd_null, tray_pwd_left,
							tray_pwd_right,tray_pwd_select);
}

void exit_tray_menu(void)
{	
	osd_tog_region(0, OSD_OFF);
    safe_srn_forceOFF();
    safe_srn_off();
	#ifdef SDRAM_16Mb_Mode
        regs0->osd_base_addr=GetOSDBackUpAddress();
    #endif
	full_scrn = 0;
    delay_srv_10ms(1);//libing 2005-4-14 23:34 to avoid the disturb bug at op menu fade out
	osd_init();
	tray_psd_exit_flag=0;
	#ifdef ORITRON_TRAY_PASSWORD
		WriteToI2c(0xa0, ADDR_I2C_TRAY_PWD, &tray_flag, 1);
	#endif
}


void tray_pwd_left(void)
{
	if(tray_level==0)
	{
		tray_level++;
		osd_draw_region_rect(288,0,144,38,0,0);
		osd_DrawRegionString(21,1,"YES",2,0,0);
	}
	else if(tray_level==1)
	{
		tray_level++;
		osd_draw_region_rect(288,0,144,38,0,0);
		osd_DrawRegionString(21,1,"NO",2,0,0);
	}
}

void tray_pwd_right(void)
{
	if(tray_level==0)
	{
		osd_draw_region_rect(288,0,144,38,0,0);
		osd_DrawRegionString(21,1,"NO",2,0,0);
		tray_level=2;
	}
	else if(tray_level==2)
	{
		tray_level--;
		osd_draw_region_rect(288,0,144,38,0,0);
		osd_DrawRegionString(21,1,"YES",2,0,0);
	}
}

void tray_pwd_select(void)
{
	if(tray_level==0)
	{		
		return;
	}
	else if(tray_level==1)
		{
		tray_flag=0x33;			
		exit_tray_menu();
	}
	else if(tray_level==2)
	{
		tray_flag=0;		
		exit_tray_menu();
	}			
}	
#endif //ORITRON_TRAY_PASSWORD
/********************************************************
********************************************************/

#ifdef SUPPORT_OP_REGION_UI

int Oritron_Region_Level = 0,Old_Level = 0;
void Osd_Init_Op_Region();

const UINT8 Oritron_Region_UI_Item[1][7]=
{
	{STR_OS_REGION_0,STR_OS_REGION_1,STR_OS_REGION_2,STR_OS_REGION_3,STR_OS_REGION_4,STR_OS_REGION_5,STR_OS_REGION_6,}
};

BYTE Region_count = 0;
const char *Str;
int Region_Avoid_Ckpwd = 0;
void Show_Oritron_Region_UI(void)
{	
	Region_Avoid_Ckpwd = 1;
	Osd_Init_Op_Region();	
	full_scrn = (OP_REGION_UI | SETUP);
	//SetOsdCol(0,0,0,__palette4F(  21,102,200, 0xbf ));//(GBR)
	SetOsdCol(0,0,0,__palette4F(  227,84,237, 0xbf ));
	SetFullscrnCmdFuncPtr(ircmd_null,ircmd_null,Region_Func_Left,
							Region_Func_Right,Region_Func_Select);
	Oritron_Region_Level = UserSet.P_RCD;
	osd_draw_region_rect(250,0,60,38,15,0);
	osd_DrawRegionString(1,1,"REGION SETTING",2,0,0);
	Region_count = Oritron_Region_UI_Item[0][Oritron_Region_Level];
	Str = _OsdMessegeFont1[osd_font_mode][Region_count];
	osd_DrawRegionString(21,1,(BYTE *)Str,2,0,0);
}

void Region_Func_Left(void)
{

	if(Oritron_Region_Level<0&&Oritron_Region_Level>6)
		Oritron_Region_Level = 0;
	
	Oritron_Region_Level--;
	
	if(Oritron_Region_Level<0)
		Oritron_Region_Level = 6;

	Region_count = Oritron_Region_UI_Item[0][Oritron_Region_Level];	
	Str = _OsdMessegeFont1[osd_font_mode][Region_count];
	osd_DrawRegionString(21,1,(BYTE *)Str,2,0,0);	
	//Old_Level = Oritron_Region_Level;
}

void Region_Func_Right(void)
{
	if(Oritron_Region_Level<0&&Oritron_Region_Level>6)
		Oritron_Region_Level = 0;
	
	Oritron_Region_Level++;	
	
	if(Oritron_Region_Level>6)
		Oritron_Region_Level = 0;
		
	Region_count = Oritron_Region_UI_Item[0][Oritron_Region_Level];
	Str = _OsdMessegeFont1[osd_font_mode][Region_count];
	osd_DrawRegionString(21,1,(BYTE *)Str,2,0,0);	
	//Old_Level = Oritron_Region_Level;	
	
}
void Region_Func_Select(void)
{
	extern int Region_Construct_Flag;
	int Region_Construct_Flag = 0;
	
	Region_Construct_Flag = Oritron_Region_Level;
	UserSet.P_RCD = Region_Construct_Flag;
	Exit_Op_Region_ui();
	//Old_Level = Oritron_Region_Level;
	printf("!!!!!!!!! %d !!!!!!!!!!!\n",Region_Construct_Flag);
	//setup_VA[SETUP_VA_REGION_CODE] = UserSet.P_RCD+2;
	//run_set_variable();
}

void Exit_Op_Region_ui(void)
{	
	osd_tog_region(0, OSD_OFF);
    safe_srn_forceOFF();
    safe_srn_off();
	#ifdef SDRAM_16Mb_Mode
        regs0->osd_base_addr=GetOSDBackUpAddress();
    #endif
	full_scrn = 0;
    delay_srv_10ms(1);//libing 2005-4-14 23:34 to avoid the disturb bug at op menu fade out
	osd_init();
    Region_Avoid_Ckpwd = 0;
    #ifdef SUPPORT_OP_REGION_UI//libing 2005-8-25 10:58
   	    WriteToI2c(0xa0, ADDR_I2C_REGION_CODE_PWD,&UserSet.P_RCD,1);
   	#endif 
}

#endif//SUPPORT_OP_REGION_UI

#ifdef SUPPORT_OP_SW_VERSION_UI//libing 2005-11-3 14:43
void Show_Oritron_SW_Version_UI(void)
{	
	Osd_Init_SW_Version();	
	full_scrn = (OP_REGION_UI);
	SetOsdCol(0,0,0,__palette4F(  210,194,53, 0xbf ));
	SetFullscrnCmdFuncPtr(ircmd_null,ircmd_null,ircmd_null,
							ircmd_null,ircmd_null);
	osd_DrawRegionString(1,1,"SOFTWORE VERSION:",2,0,0);
}
#endif

