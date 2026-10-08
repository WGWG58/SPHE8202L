/***********************************************************************
** Osd_BmpUI.h
**
**      structure define for Osd_BmpUI.c
**
**
** 	Creator :suqiaoli,feeling
**	Date:    2004-7-8 10:36
************************************************************************/

#ifndef _OSD_BMP_UI_H
#define  _OSD_BMP_UI_H

//pos variable and pos fixed bmps
//display osd
#define ANGLE_BMP	0
#define CD_BMP	1
#define CDROM_BMP	2
#define CLOCK_ICON_BMP	3
#define DOLBY_BMP	4
#define DTS_BMP	5
#define DVD_BMP	6
#define LANGUAGE_BMP	7
#define MUTE_ICON_BMP	8
#define REPEAT_1_BMP	9
#define REPEAT_ALL_BMP	10
#define REPEAT_CLOSE_BMP	11
#define SUB_TITLE_BMP	12
#define SVCD_BMP	13
#define VCD_BMP	14
#define VOLUME_ICON_BMP	15

//general osd bmp
#define OSD_BG_BMP_A                0
#define OSD_DOWN_BG_BMP_A           1
#define OSD_4_1_BMP_D	            2
#define OSD_4_2_BMP_D	            3
#define OSD_4_3_BMP_D	            4
#define OSD_5_1_BMP_E               5
#define OSD_5_3_BMP_E               6
#define OSD_6_1_BMP_F               7
#define OSD_6_2_BMP_F               8
#define OSD_6_3_BMP_F	            9

//sound data position,include bmp,line,rect,str
#ifdef OSD_BMP_SOUND
//sound bmp
#define OSD_CURSOR_1_BMP_B                  10
#define OSD_CURSOR_2_BMP_D                  11
#define SOUND_SLIDE_ARROW_SELECTED_BMP_E3	12
#define SOUND_SLIDE_ARROW_CURSOR_BMP_E3	    13

//sound line
#define SOUND_LINE1_A	0
#define SOUND_LINE2_A	1
#define SOUND_LINE1_B	2
#define SOUND_LINE2_B	3
#define SOUND_BG_LINE_B	4
#define SOUND_LINE1_D	5
#define SOUND_LINE2_D	6
#define SOUND_CURSOR_UP_LINE_E4	7
#define SOUND_CURSOR_DOWN_LINE_E4 8
#define SOUND_SEL_UP_LINE_E4 9
#define SOUND_SEL_DOWN_LINE_E4 10
#define SOUND_SCALE_N6_LINE_E3	11
#define SOUND_SCALE_N6_N4_LINE_E3	12
#define SOUND_SCALE_N4_LINE_E3	13
#define SOUND_SCALE_LINE_E3 14

//sound rect
#define SOUND_SHADOW_A	0
#define SOUND_RECT_BG_B	1
#define SOUND_DOWN_B		2
#define SOUND_SHADOW_B	3
#define SOUND_SHADOW_D	4
#define SOUND_DOWN_D	5
#define SOUND_CURSOR_RECT_E4	6
#define SOUND_SEL_RECT_E4	7
#define SOUND_UNSEL_RECT_E4	8
#define SOUND_BG_RECT_E4	9
#define SOUND_EQ_BG_RECT_E1	10
#define SOUND_BAND_BG_RECT_E1 11
#define SOUND_KEY_BG_RECT_E3 12
#define SOUND_EQ_POPUP_BG_RECT_E4	13
#define SOUND_EQ_CURSOR_BG_RECT_E4  14
#define SOUND_EQ_UNSEL_BG_RECT_E4	15

//sound str
#define SOUND_UNSEL_STR_B	0
#define SOUND_SEL_STR_B	1
#define SOUND_UNHL_ITEM_STR_E4	2
#define SOUND_HL_ITEM_STR_E4	3
#define SOUND_EQ_STR_E4	4
#define SOUND_SCALE_KEY_STR_E3 5
#define SOUND_SCALE_N_NUM_STR_E3 6
#define SOUND_SCALE_P_NUM_STR_E3 7
#endif

//Program data position,include bmp,line,rect,str
#ifdef OSD_BMP_PROG
//prog bmp
#define PROG_CDROM_FOLDER_BMP_D     10
#define PROG_CDROM_FILE_BMP_D     	11

//prog line
#define PROG_LINE1_A		        0
#define PROG_LINE2_A		        1
#define PROG_LINE1_B		        2
#define PROG_LINE2_B		        3
#define PROG_BG_LINE_B		        4
#define PROG_LINE1_D		        5
#define PROG_LINE2_D		        6
//prog rect
#define PROG_SHADOW_A	            0
#define PROG_SHADOW_B	            1
#define PROG_DOWN_B                 2
#define PROG_SHADOW_D	            3
#define PROG_DOWN_D                 4
#define PROG_BG2_E                  5
#define PROG_BG3_E                  6
#define PROG_PLAY_NORMAL_E          7
#define PROG_RESET_NORMAL_E         8
//prog str
#define PROG_STR_B                  0
#define PROG_STR_COLON              1
#define PROG_DVD_TT                 2
#define PROG_DVD_CH                 3

#endif

typedef struct
{
    UINT16  uiXStart; //x start position
    UINT16  uiYStart; //y start position
    UINT16  uiXWidth;//total x Width
    UINT16  uiYHeight;//total y Height
    UINT16  uiXOffset;// xoffset
    UINT8  uiYOffset;
    UINT8   uiIndex; // index in bmp array
    BYTE    bRegion; //region
} OSD_BITMAP_LAYOUT_S;

typedef struct
{
	UINT16  uiXStart;//x start position
	UINT16  uiYStart; // y start position
	UINT16  uiXLen; // x len
	UINT16  uiYLen; //y len
	UINT16   uiXOffset; //x offset for x variable line, if fixed then 0
	UINT16   uiYOffset; //y offset for y variable line, if fixed then 0
	UINT8   uiColor;	//color index in palette array
	BYTE    bRegion; // region 
}OSD_LINE_LAYOUT_S;

typedef struct
{
	UINT16  uiXStart; //x Start position
	UINT16  uiYStart; //y Start position
	UINT16  uiXWidth; // x Length
	UINT16  uiYHeight; // y Length
   	 UINT16   uiXOffset; //x offset for x variable line, if fixed then 0
	UINT16   uiYOffset; //y offset for y variable line, if fixed then 0
	UINT8   uiBgColor; //bg color in pallette array
	BYTE    bRegion; //region
}OSD_RECT_LAYOUT_S;

typedef struct
{
	UINT16  uiXStart;//x start position
	UINT16  uiYStart;//y start position
	UINT16   uiXOffset; //x offset for x variable line, if fixed then 0
	UINT16   uiYOffset; //y offset for y variable line, if fixed then 0
    UINT8   uiFontColor;//font color index in pallette array
    UINT8   uiBgColor;//bg color index in pallette array
    BYTE    bRegion;//region
}OSD_STR_LAYOUT_S;
    

typedef struct
{
	UINT16   uiBg;//bg bmp index
	UINT16   uiLineLeft; //line1 index
	UINT16   uiDownBg;//down bg bmp index
	UINT16   uiLineRight; //line2 index
    	UINT16   uiShadow;//shadow rect index
}OSD_REGIONA_LAYOUT_S;

typedef struct
{
	UINT16   uiBg;//bg bmp or rect index
	UINT16   uiBgLine;//bg line index
	UINT16   uiLineLeft; //line1 index
	UINT16   uiDownBg;//down rect
	UINT16   uiCursor; // cursor bmp index
	UINT16   uiSelStr; // selected string index
	UINT16   uiUnselStr; //unslected string index
	UINT16   uiLineRight; //line2 index
    	UINT16   uiShadow;//shadow rect index
}OSD_REGIONB_LAYOUT_S;

typedef struct
{
	UINT16   uiLeftBg;//Left bg bmp index
	UINT16   uiMiddleBg;//middle bg bmp index
	UINT16   uiLineLeft;//line1  index
	UINT16   uiDownBg; //down bg rect or bmp
	UINT16   uiCursor; // cursor bmp index
	UINT16   uiLineRight; //line2 index
    	UINT16   uiShadow;//shadow rect index
	UINT16   uiRightBg; //right bg bmp index 
}OSD_REGIOND_LAYOUT_S;

typedef struct
{
	UINT16   uiLeftBg;//Left bg bmp index
	UINT16   uiMiddleBg;//Middle bg rect
	UINT16   uiRightBg; //right bg bmp index 
}OSD_REGIONE_LAYOUT_S;

typedef struct
{
	UINT16   uiLeftBg;//Left bg bmp index
	UINT16   uiMiddleBg;//middle bg bmp index
	UINT16   uiRightBg; //right bg bmp index 
}OSD_REGIONF_LAYOUT_S;


void osd_draw_bmp_old(int xStart, int yStart,const BYTE* bmp,  BYTE r);
void osd_draw_repeat_bmp(UINT16 uiXStart,UINT16 uiYStart,UINT16 uiXWidth,UINT16 uiHeight,const BYTE* bmp,BYTE r);
void OSD_LayoutBmp(UINT8 uiLayoutBmpIndex,UINT8 uiOffsetIndex);


extern void osd_draw_hline_region(int xStart, int xEnd, int y, unsigned color, int n, int r);
void OSD_LayoutLine(UINT16 uiLayoutLineIndex, UINT8 uiOffsetIndex);

extern void osd_draw_region_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor, BYTE r);
void OSD_LayoutRect(UINT16 uiLayoutRectIndex, UINT8 uiOffsetIndex);

extern void osd_DrawRegionString(UINT32 xStart, UINT32 yStart, const BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r);
void osd_Draw_Bmp_RegionString(UINT32 xStart, UINT32 yStart, const BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r);
void OSD_LayoutStr(const BYTE *str, UINT16 uiLayoutStrIndex, UINT8 uiOffsetIndex);
void osd_Draw_Bmp_Little_RegionString(UINT32 xStart, UINT32 yStart, const BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r);
void OSD_LayoutLittleStr(const BYTE *str, UINT16 uiLayStrIndex, UINT8 uiOffsetIndex);

void OSD_DrawReverseBmp(UINT16 xStart, UINT16 yStart,  UINT8 uiLayoutIndex, BYTE bMode);
void OSD_Draw3DRect(UINT16 xStart, UINT16 yStart, UINT16 xEnd, UINT8 uiLayoutIndexEdge, UINT8 uiLayoutIndexLine);


#ifdef OSD_BMP_DISPLAY//feeling
void osd_draw_bmp_display(int xStart, int yStart,const BYTE* bmp,  BYTE r);
void OSD_LayoutBmpDisplay(UINT8 uiLayoutIndex);
#endif

#endif //ifndef  _OSD_BMP_UI_H


