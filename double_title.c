/*****************************************************\
Creater: susu
Date   : 2003-8-20 14:40
Description: show double title function 
\*****************************************************/

#include "global.h"
#include "osd.h"
#include "func.h"
#include "cfont.h"
#include "util.h"
#include "ircmd.h"
#include "user_if.h" 
#include "stdlib.h"

#include "emuio.h"
#include "sio.h"

#ifdef DOUBLE_TITLE

extern void osd_init_double_title(void);
extern void osd_draw_region_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor, BYTE r);
extern void osd_DrawRegionString(BYTE xStart, BYTE yStart, BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r);
extern void ircmd_sub_picture(void);

void exe_double_title(void);
void exit_double_title(void);
void double_title_func_select(void);
void double_title_func_up(void);
void double_title_func_down(void);
void double_title_func_left(void);
void double_title_func_right(void);
void draw_doubletitle_string(void);
void draw_doubletitle_12space(int i);

#define FIRST_TITLE_ITEM      0//first title choise
#define SECOND_TITLE_ITEM     1//second title choise

#define FONT_COLOR            2//White
#define HL_FONT_COLOR         12//Red
#define ICON_COLOR            9//yellow_green
#define BK_COLOR              0//Transparent

#define X_START_0             5//first title position
#define X_START_1             23//second title position

#define X_START               0
#define Y_START               0

#define X_LINE                36*4*2//display rect length
#define Y_LINE                24+5//display rect hight

int i_title_item=FIRST_TITLE_ITEM; //title item:first title item and second title item

void exit_double_title(void)
{
	full_scrn=0;
    osd_init();
}

void exe_double_title(void)
{
	osd_init_double_title();
	action_click=0;
	
	//Initialize double tile
	osd_draw_region_rect(X_START,X_START,X_LINE*2,Y_LINE-2,BK_COLOR,REGION1);
	draw_doubletitle_string();
	
	i_title_item=FIRST_TITLE_ITEM;
}

void double_title_func_up(void)//press up button
{
	if(i_title_item==FIRST_TITLE_ITEM)
	{
		draw_doubletitle_12space(0);
		memset(linebuf,0,sizeof(linebuf));
		
		ircmd_sub_picture();
		osd_DrawRegionString(X_START_0,Y_START,linebuf,HL_FONT_COLOR,BK_COLOR,REGION1);
		
		strcpy(linebuf_0,linebuf);
	}
	else
	{
		draw_doubletitle_12space(1);
		memset(linebuf,0,sizeof(linebuf));
		
		ircmd_sub_picture();
		osd_DrawRegionString(X_START_1,Y_START,linebuf,HL_FONT_COLOR,BK_COLOR,REGION1);
		
		strcpy(linebuf_1,linebuf);
	}
}

void double_title_func_down(void)//press down button
{
    printf("double_title_func_down\n");
	if(i_title_item==FIRST_TITLE_ITEM)
	{	
		draw_doubletitle_12space(0);
		memset(linebuf,0,sizeof(linebuf));
		
		ircmd_sub_picture();
		osd_DrawRegionString(X_START_0,Y_START,linebuf,HL_FONT_COLOR,BK_COLOR,REGION1);
		
		strcpy(linebuf_0,linebuf);
	
	}
	else
	{
		draw_doubletitle_12space(1);
		memset(linebuf,0,sizeof(linebuf));
		ircmd_sub_picture();
		osd_DrawRegionString(X_START_1,Y_START,linebuf,HL_FONT_COLOR,BK_COLOR,REGION1);
		
		strcpy(linebuf_1,linebuf);
	}
}

void double_title_func_right(void)//press right button
{
	action_click=0;
	i_title_item=SECOND_TITLE_ITEM;
	draw_doubletitle_12space(1);
	memset(linebuf,0,sizeof(linebuf));
	
	if(strlen(linebuf_1)==0)
	{
		ircmd_sub_picture();
		osd_DrawRegionString(X_START_0,Y_START,linebuf,FONT_COLOR,0,REGION1);
	}
	
	if(strlen(linebuf_1)==0)
	{
		psprintf(linebuf,"    [ %s ]",_OsdMessegeFont1[osd_font_mode][STR_OS_OFF]);
		osd_DrawRegionString(X_START_1, Y_START, linebuf, HL_FONT_COLOR, BK_COLOR,REGION1);
	}		
	
	osd_DrawRegionString(X_START_0, Y_START, linebuf_0, FONT_COLOR, BK_COLOR,REGION1);	
	osd_DrawRegionString(X_START_1, Y_START, linebuf_1, HL_FONT_COLOR, BK_COLOR,REGION1);

}

void double_title_func_left(void)//press left button
{	
	action_click=0;
	i_title_item=FIRST_TITLE_ITEM;
	draw_doubletitle_12space(0);
	memset(linebuf,0,sizeof(linebuf));
	
	if(strlen(linebuf_0)==0)
	{
		ircmd_sub_picture();
		osd_DrawRegionString(X_START_0,Y_START,linebuf,HL_FONT_COLOR,0,REGION1);
	}	
	
	if(strlen(linebuf_1)==0)
	{
		psprintf(linebuf,"    [ %s ]",_OsdMessegeFont1[osd_font_mode][STR_OS_OFF]);
		osd_DrawRegionString(X_START_1, Y_START, linebuf, FONT_COLOR, BK_COLOR,REGION1);
	}	
	
	osd_DrawRegionString(X_START_0,Y_START,linebuf_0,HL_FONT_COLOR,BK_COLOR,REGION1);
	osd_DrawRegionString(X_START_1,Y_START, linebuf_1,FONT_COLOR, BK_COLOR,REGION1);
	
}

void double_title_func_select(void)
{
	//exit_double_title();
}

void draw_doubletitle_string(void)
{//write subtitle string

	psprintf(linebuf,"%s:",_OsdMessegeFont1[osd_font_mode][STR_OS_SUBTITLE]);
	osd_DrawRegionString(X_START, Y_START, linebuf, ICON_COLOR, BK_COLOR,REGION1);
	
	if(strlen(linebuf_0)==0)
	{
	 	ircmd_sub_picture();
		osd_DrawRegionString(X_START_0,Y_START,linebuf,HL_FONT_COLOR,0,REGION1);
	
		psprintf(linebuf,"    [ %s ]",_OsdMessegeFont1[osd_font_mode][STR_OS_OFF]);
		osd_DrawRegionString(X_START_1, Y_START, linebuf, FONT_COLOR, BK_COLOR,REGION1);
	}
	
	if(strlen(linebuf_1)==0)
	{
		psprintf(linebuf,"    [ %s ]",_OsdMessegeFont1[osd_font_mode][STR_OS_OFF]);
		osd_DrawRegionString(X_START_1, Y_START, linebuf, FONT_COLOR, BK_COLOR,REGION1);
	}	

	osd_DrawRegionString(X_START_0,Y_START,linebuf_0,HL_FONT_COLOR,0,REGION1);
	osd_DrawRegionString(X_START_1, Y_START, linebuf_1, FONT_COLOR, BK_COLOR,REGION1);	
}	

void draw_doubletitle_12space(int i)//12 blank
{//erase displayed word and disp new word when press updown key(for draw right item)
		strcpy(linebuf, "            ");
		osd_DrawRegionString(18*i+5,Y_START, linebuf,FONT_COLOR,BK_COLOR,REGION1);	
}

#endif
