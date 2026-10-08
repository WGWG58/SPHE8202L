#ifndef __BROWSE_GUI_H
#define __BROWSE_GUI_H
/*****************************************************\
Creater: xiongyuyue
Date   : 2003/6/28 
Description: browse function using 
\*****************************************************/

#ifdef NEWSTYLE_WINDOW

void br_DrawRightItem(void);
void br_DrawLeftItem(BYTE item_index,BYTE loc_index,BYTE fontColor,BYTE bkColor);

void br_Draw_tmhl(BYTE xStart, BYTE yStart, char *s,BYTE fontCol,BYTE bkColor);
extern UINT8 DVD_check_state(void);
extern void setVPP_OffsetX(int X);
extern void setVPP_OffsetY(int Y);
extern void osd_draw_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor);
extern void tm2hms(UINT32 time,UINT8 *h,UINT8 *m,UINT8 *s);
//extern void osd_DrawRegionString(BYTE xStart, BYTE yStart, BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r);
extern void sup_disable(void);
extern void sup_enable(void);

#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW//zhaoyanhua add 2003-12-18 15:33
void DrawNewWindow(void);
#endif



//zhaoyanhua add 2003-12-7 19:01
void updateAudioLanguage(void);
void updateSubtitle(void);
void updateRepeatMode(void);
void UpdateAngleInfo(void);

#ifndef NEW_OSD_DRIVER	//linrc modify for new osd drive 2005-10-22 13:57
#define ITEM_HEIGHT 7  // 4 pixel/unit,the height of an eng charactor is 24=4*6
#define ITEM_WIDTH 4  //4 pixel/unit,the width of an eng charactor is 16=4*4
#else
#define ITEM_HEIGHT 7  // 4 pixel/unit,the height of an eng charactor is 24=4*6
#define ITEM_WIDTH 2  //4 pixel/unit,the width of an eng charactor is 16=4*4
#endif

#define ITEM_PER_PAGE 5

#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW//zhaoyanhua add 2003-12-6 14:17
#define VCD_MAXITEM  4
#define DVD_MAXITEM  8
#else
#define VCD_MAXITEM 5
#define DVD_MAXITEM  9
#endif
#define CD_MAXITEM  3//xyy 2003-9-12 13:10

#define INFO_FONTCOL 2
#define INFO_PRE_BKCOL 4
#define INFO_BKCOL 5
#define UNDERLINECOL 11
#define HL_BKCOL 0

#define TIMEINFO_BKCOL 4
#define TIMEINFO_COL 7

#define INPUT_STATE 1
#define NON_INPUT_STATE 0

//#define ENG_STR_LEN 4
//#define ARROW_RADIUS 10


#define BAR_EDGE 4
//#define update_definition 40
#define PROGRESS_BAR_LEN  200+2*BAR_EDGE

#define BAR_XSTART  25*16-BAR_EDGE
#define TT_BAR_YSTART 24*4
#define CHP_BAR_YSTART 24*7
#define BAR_BKCOL 7
#define BAR_COL   3 

#define BAR_YLEN 32
#define PROGRESS_BAR_YLEN 24


/*
extern BYTE bBrowseLevel = 0;
extern int st_rtval=0;
extern int lang_rtval=0;
extern int agl_rtval=0;
*/
enum
{
    BR_ITEM_AREA    = 0,
    BR_CONTENT_AREA = 1,
};

typedef struct
{
	UINT16  xStart;
	UINT16  yStart;
	UINT16  xSize;
	UINT16  ySize;
}BROWSE_AREA;

#ifndef NEW_OSD_DRIVER   
BROWSE_AREA brArea[2]=
{
    {ITEM_WIDTH*4/*4 word width*/,63,ITEM_WIDTH*6/*6 word width*/,ITEM_HEIGHT*5},
    {ITEM_WIDTH*10/*10 word width*/,63,ITEM_WIDTH*8/*8 word width*/,ITEM_HEIGHT*5}
};
#else
BROWSE_AREA brArea[2]=
{
    {ITEM_WIDTH*2/*4 word width*/,63,ITEM_WIDTH*12/*6 word width*/,ITEM_HEIGHT*5},
    {ITEM_WIDTH*9/*10 word width*/,63,ITEM_WIDTH*16/*8 word width*/,ITEM_HEIGHT*5}
};
#endif

BYTE HL_loc[]={0,1,3,4,6,7};//for time search function,the val is location index

BYTE string_index_dvd[DVD_MAXITEM]=
{
    STR_OS_TT,
    STR_OS_CHP,
#ifndef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW//zhaoyanhua add 2003-12-6 14:00    
    STR_OS_TIME,
#endif    
    STR_OS_SUBTITLE_LANG_SETUP,
    STR_OS_AUDIO_LANG_SETUP,
    STR_OS_ANGLE,
    STR_OS_TITLETIME, 
    STR_OS_CHPTIME, 
    STR_OS_REP,
};

BYTE string_index_vcd[VCD_MAXITEM]=
{
	STR_OS_TRACK,
#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW//zhaoyanhua add 2003-12-6 14:00
    STR_OS_DISCTIME,
    STR_OS_TRACKTIME,
#else	
	STR_OS_PLAYTIME,
	STR_OS_TITLETIME,
	STR_OS_CHPTIME,
#endif	
	STR_OS_REP,
};

BYTE string_index_cd[CD_MAXITEM]=
{
	STR_OS_TRACK,
	STR_OS_PLAYTIME,
	STR_OS_REP,
};
/*
const char *time_string[4]=
{
	"TTREMAINTIME",
	"TT PLAY TIME",
	"CHREMAINTIME",
	"CH PLAY TIME"
};
*/
#endif

#endif
