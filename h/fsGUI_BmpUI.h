/***********************************************************************
** fsGUI_BmpUI.h
**
**      MACRO define for fsGUI_BmpUI.c
**
**
** 	Creator :zhaoyanhua
**	Date:    2004-6-9 11:07
************************************************************************/

#ifndef _FSGUI_BMP_UI_H
#define  _FSGUI_BMP_UI_H

#define BMP_LINE_WIDTH      1

//BUTTON or FILE STATE
#define UP_STATE      0
#define DOWN_STATE     1
#define HL_STATE        2


//index define in g_aBmpLayout[]
//fixed bmp
#define	LAY_BG_3_1	            0
#define	LAY_BG_3_2	            1
#define LAY_BG_3_3              2
#define	LAY_TAB_BAR2_1	        3
#define	LAY_MP3_ICON_L	        4
#define	LAY_JPG_ICON_L	        5
#define	LAY_VIDEO_ICON_L	    6
#define	LAY_GAME_ICON_L	        7
#define	LAY_PLAYING_BAR_3_1	    8
#define	LAY_PLAYING_BAR_3_3	    9
#define	LAY_ANIMATION1	        10
#define	LAY_ANIMATION2	        11

//moved bmp
#define	LAY_TAB_BAR2_2	        12
#define	LAY_TAB_BAR_SHINE	    13
#define	LAY_TAB_BAR_DOWN	    14
#define	LAY_PLAYING_BAR_3_2	    15
#define	LAY_FILE_BG_CORNER_LT	16
#define	LAY_FILE_BG_CORNER_RT	17
#define	LAY_FILE_BG_CORNER_LB	18
#define	LAY_FILE_BG_CORNER_RB	19
#define LAY_MP3_ICON_S          20
#define LAY_JPEG_ICON_S         21
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
#define LAY_GAME_ICON_S         22
#define LAY_VIDEO_ICON_S        23
#else
#define LAY_VIDEO_ICON_S        22
#define LAY_GAME_ICON_S         23
#endif
#define LAY_FILE_BG_10_0        24
#define LAY_FILE_BG_10_1        25
#define LAY_FILE_BG_10_2        26
#define LAY_FILE_BG_10_3        27
#define LAY_FILE_BG_10_4        28
#define LAY_FILE_BG_10_5        29
#define LAY_FILE_BG_10_6        30
#define LAY_FILE_BG_10_7        31
#define LAY_FILE_BG_10_8        32
#define LAY_FILE_BG_10_9        33
#define LAY_FOLDER_ICON         34
#ifdef GPS_MP3_UI//frank.huang 050915
    #define LAY_FOLDER_OPEN_ICON         35
	#define PATH_INFO_BAR_L         36
	#define PATH_INFO_BAR_R         37
	#define	MP3_PAGE_ICON			38
	#define	JPEG_PAGE_ICON			39
	#define	VIDEO_PAGE_ICON			40
	#define	SLIDER_BODY				41
	#define	ARROW_U					42
	#define	ARROW_D					43
	#define	SLIDER_BLOCK			44
	#define	SLIDER_BLOCK_U			45
	#define	SLIDER_BLOCK_D			46
#endif

#define MP3_BTN_BG_XPOS		216
#define BTN_BG_XOFFSET	105
#define BTN_BG_UP_YPOS		27
#define BTN_BG_HL_YPOS  32
#define BTN_BG_DOWN_YPOS  32

void FSGUI_LayoutBmp(UINT8 LayoutIndex);
void FSGUI_LayPosVariableBmp(UINT16 xStart, UINT16 yStart,UINT8 LayoutIndex);
void FSGUI_DrawOneButton(BYTE type, BYTE state);
void FSGUI_DrawBackGround(UINT16 xStart, UINT16 yStart, UINT16 xRepeat, UINT16 yRepeat,UINT8 LayoutIndex);
void DIR_DrawScroll(void);
void DIR_MoveScroll(UINT16 locate);
void FSGUI_ClearArea(UINT16 iIndex,UINT16 iItem);
void FSGUI_DrawBackGround(UINT16 xStart, UINT16 yStart, UINT16 xRepeat, UINT16 yRepeat,UINT8 LayoutIndex);
void FSGUI_ShowBmpCornerRect(UINT16 xStart, UINT16 yStart,UINT16 iWidth, UINT16 iHeight);
BYTE  DrawTriangle(UINT16 xStart, UINT16 yStart, UINT16 iBottom, UINT16 iHight, BYTE iDir, UINT16 iColorY, UINT16 iColorCrCb);
void FSGUI_ShowBtnTitle(void);
void fontFocus(void);
void fontunFocus(void);
void DrawSelectedRectWithSide(UINT16 xStart, UINT16 yStart, UINT16 xLen, UINT16 yLen, UINT16 RectY, UINT16 RectCrCb,UINT16 SideY ,UINT16 SideCrCb);

#endif //ifndef  _FSGUI_BMP_UI_H


