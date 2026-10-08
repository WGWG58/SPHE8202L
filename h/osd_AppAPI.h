#ifndef _OSD_APPAPI_H_
#define _OSD_APPAPI_H_

// 2005/08/29 yltseng, to mark some define

#include "user_init.h"

#ifdef NEW_OSD_DRIVER

#include "types.h"
#include "osd_api.h"

#ifndef DVDRELEASE
#define OSD_APP_DEBUG
#endif


/************************************************************
OSD App Related Data Structure
************************************************************/
typedef struct 
{
    UINT8 xst;
    UINT8 yst;
    UINT8 *str;
}   t_osd_str;


#define OSD_OnOffRegion(m,r) osd_tog_region(r,m)
/*
// Following defines are for OSD_FONT_API & SUPPORT_OSDSRT
#define FONT_LEN_EXTERNAL_TWO_BYTE  14
#define FONT_LEN_INTERNAL_OSD       9

#if defined(EUROPE_FOREIGN_LANGUAGES) || defined(MIDDLE_EUROPE_LANGUAGES) || defined (SUPPORT_TURKISH_LANGUAGES) || defined ( USE_CYRILLIC_FONT )
    #define FONT_LEN_EXTERNAL_ONE_BYTE  6
#else
    #define FONT_LEN_EXTERNAL_ONE_BYTE  FONT_LEN_INTERNAL_OSD
#endif
*/

/************************************************************
OSD App Standard Region Init Functions
************************************************************/

extern void osd_init(void);
extern void osd_init_prog(void);
extern void osd_init_music(void);
extern void osd_init_setup(void);
extern void osd_init_screensaver(void);


/************************************************************
OSD App Define-Related Region Init Functions
************************************************************/

#if defined(FAT_Write_UI)||defined(FILE_MODE_WRITE)
extern void osd_init_MediaswitchGUI(void);
#else
#define     osd_init_MediaswitchGUI(...)
#endif

#ifdef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-5-13 11:34
extern void osd_init_media_switch_gui(void);
#else//DIRECT_ACCESS_MEDIA
#define osd_init_media_switch_gui(...)
#endif//DIRECT_ACCESS_MEDIA


#if defined(CF_CARD_WRITE)||defined(FAT_Write_UI)||defined(FILE_MODE_WRITE)
extern void osd_init_periphGUI(void);
#else
#define     osd_init_periphGUI(...)
#endif

#ifdef SUPPORT_OSDID3
extern void osd_init_OSDID3(void);
#else
#define     osd_init_OSDID3(...)
#endif

#ifdef SWITCH_CD_CARD_USB
extern void osd_init_switchGUI(void);
#else
#define     osd_init_switchGUI(...)
#endif

#ifdef RIPPING_MODE_SELECT //qinhua,add 2006-5-30 11:01ÏÂÎç
extern void osd_init_ripGUI(void);
extern void osd_init_ripStep(void);
#endif 

#ifdef SUPPORT_OSDSRT   // 2005/07/12 yltseng
extern void osd_init_OSDSRT(void);
extern void osd_move_subtitle_region();
#else
#define     osd_init_OSDSRT(...)
#define     osd_move_subtitle_region(...)
#endif

#ifdef  RECORD_KEY
extern void osd_init_record();
#else
#define     osd_init_record(...)
#endif

#ifdef DOUBLE_TITLE
extern void osd_init_double_title(void);
#else
#define     osd_init_double_title(...)
#endif

#ifndef NES_USE_GRAPH
extern void osd_init_NES(int x,int y,int w,int h, const UINT16 *pPalette);
#else
#define     osd_init_NES(...)
#endif

#ifdef CD_PLAYER
extern void osd_init_cdplayer(void);
#else
#define     osd_init_cdplayer(...)
#endif

#ifdef VIRTUAL_KEYBOARD
extern void osd_init_keyboard(void);
#else
#define     osd_init_keyboard(...)
#endif

#ifdef PMP_UI
extern void osd_init_pmp(void);
#else
#define     osd_init_pmp(...)
#endif

#ifdef NEW_PARENTAL_GUI
extern void osd_init_parental_gui(void);
#else
#define     osd_init_parental_gui(...)
#endif

#ifdef NEWSTYLE_WINDOW
extern void osd_init_newstyle_window(void);

    #ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
extern void osd_init_newstyle_window_NTSC(void);
extern void osd_init_newstyle_window_PAL(void);
    #else
#define     osd_init_newstyle_window_NTSC(...)
#define     osd_init_newstyle_window_PAL(...)
    #endif
#else
#define     osd_init_newstyle_window(...)
#define     osd_init_newstyle_window_NTSC(...)
#define     osd_init_newstyle_window_PAL(...)
#endif
 
#ifdef SUPPORT_REP_READ
extern void osd_init_rep_reading(void);
#else
#define     osd_init_rep_reading(...)
#endif

#ifdef NEW_STYLE_SETUP
extern void osd_init_hand_ICON_for_NTSC(void);
extern void osd_init_hand_ICON_for_PAL(void);
#else
#define     osd_init_hand_ICON_for_NTSC(...)
#define     osd_init_hand_ICON_for_PAL(...)
#endif

#ifdef SUPPORT_DVB_GUI_NEW
extern void osd_init_new_dvb_menu(void);
extern void osd_init_new_dvb_info(void);  ////sunzhh add for Program Info display 20051027
#else
#define 	osd_init_new_dvb_menu(...)
#define 	osd_init_new_dvb_info(...)
#endif

#ifdef DVB1000_OSD_MENU
extern void osd_init_dvb_ttx_menu(void);
#else
#ifdef SUPPORT_TELETEXT  //tcf 2005-11-1 17:21
extern void osd_init_dvb_ttx_menu(void);
#else
#define 	osd_init_dvb_ttx_menu(...)
#endif
#endif

/************************************************************
OSD App Standard Draw Functions
************************************************************/

// Draw String Functions
extern void osd_draw_string( const coordinate *start, const BYTE *str, UINT16 fontColor, UINT16 bkColor, BYTE r, BYTE only_font_color);
extern void osd_DrawString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor);
extern void osd_DrawStrings(const t_osd_str *p, BYTE fg, BYTE bg);

#if defined(SOFT_MENU)||defined(SOFT_MENU_REENG)//chenzhao20050523
extern void osd_DrawString_ori(UINT32 xStart, UINT32 yStart, const BYTE *str, BYTE fontColor, BYTE bkColor);
#else
extern void osd_DrawString_ori(BYTE xStart, UINT32 yStart, const BYTE *str, BYTE fontColor, BYTE bkColor);
#endif

extern void osd_DrawRegionString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r);
extern void osd_DrawIcon(int xStart, int yStart, unsigned index, unsigned page);

// Draw Line Functions
extern void osd_DrawRegionLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth, BYTE r);
extern void osd_DrawLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth);
extern void osd_draw_vline_region(int x, int yStart, int yEnd, unsigned color, int n, int r);
extern void osd_draw_hline_region(int xStart, int xEnd, int y, unsigned color, int n, int r);

// Draw Rectangle Functions
extern void osd_draw_region_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor, BYTE r);
extern void osd_replace_rect_color(BYTE bkColor, BYTE destColor);
extern void osd_draw_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor);

// Draw Specific Object Functions
extern void osd_draw_button_outline(int x1, int y1, int x2, int y2, int bDown, unsigned mask, int r);
extern void osd_draw_setup_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown __UNUSED);
extern void osd_draw_sound_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown);
extern void draw_osd_board(UINT8 r, UINT8 board_type);

// Other Misc Functions
extern void osd_print_eq_setting(UINT8 r,UINT8 unSele);
extern void osd_Move2OSD0(BYTE iLine);
extern void show_angle_osd(void);
extern void PrintOsdMsg(UINT32 id,UINT8 r,int t,BYTE mode);
extern void osdshow(UINT8 r,char *buf);
extern void ClearOsdMsg(int i);
extern void polling_osd(int diff);


/************************************************************
OSD App Define-Dependent Draw Functions
************************************************************/

#ifdef OSD_FONT_API
extern void OSD_ShowString( int x, int y, const char *s, BYTE fontcolor, BYTE r );    
    #if defined(SUPPORT_SMI_MultiColor)//2005-8-16 20:38 zhoulin  
extern void OSD_ShowColorString( int x, int y, const char *s, BYTE *fontcolor, BYTE r );
    #endif
#else
#define     OSD_ShowString(...)
#endif

#ifdef SETUPMENU_16Mb_NO_ICON
extern void osd_DrawSetupIconString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor);
#else
#define     osd_DrawSetupIconString(...)
#endif

#if defined( REALCOLOR_SCREENSAVER ) || defined( REALCOLOR_QSI )
extern void osd_draw_256color_bmp(int xStart, int yStart, const BYTE* bmp, BYTE r);
#else
#define     osd_draw_256color_bmp(...)
#endif

#ifdef NEWSTYLE_WINDOW
#include "osd_arc.h"
extern void osd_draw_region_arc(ARC_REGION_LOC *loc_var,BYTE updown);
#else
#define     osd_draw_region_arc(...)
#endif

#ifdef SUPPORT_REP_READ
extern void osd_print_read_eq(UINT8 r, const BYTE *p);
#else
#define     osd_print_read_eq(...)
#endif

#ifdef DISP_REGION_BOTTOM
extern UINT8 OSD_ShowBottomDisp();
extern UINT8 OSD_GetTrueDispRegion();
#else
#define      OSD_ShowBottomDisp(...)
#define      OSD_GetTrueDispRegion(...)
#endif

#ifdef SUPPORT_3DSOUND
extern void osd_print_eq(UINT8 r, const BYTE *p);
#else
#define     osd_print_eq(...)
#endif

#ifdef OSD_FONT_API
extern void osd_draw_gbfont(BYTE vid, const BYTE pFont[], int xStart, int yStart, unsigned int  fwidth, unsigned int  fhight, BYTE fontcolor,BYTE number);
extern void osd_ClearOneRegion(BYTE number, BYTE bkColor);
#else
#define     osd_draw_gbfont(...)
#define     osd_ClearOneRegion(...)
#endif

#ifdef NEW_HDMI_FLOW
extern void UpDateHDMI_StateDisplay(void);
#else
#define     UpDateHDMI_StateDisplay(...)
#endif

#ifdef DVB1000_OSD_MENU
extern void osd_draw_dvbmenu_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown);
extern void osd_draw_dvbmenu_border_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown);
#else
#define 	osd_draw_dvbmenu_button(...)
#define 	osd_draw_dvbmenu_border_button(...)
#endif

#endif  //#ifdef NEW_OSD_DRIVER

#ifdef SOFT_MENU_REENG//chenzhao20050523
    #ifdef SUPPORT_OSD_DIAGONAL
    void osd_DrawSlantCorner(INT32 xStart,INT32 yStart,INT32 xEnd,INT32 yEnd,BYTE direct,BYTE lineOnly,BYTE fontColor);
    #endif
    void osd_DrawIcon_Trans(int xStart, int yStart, unsigned index,BYTE mask,BYTE fontColor);
    void osd_draw_roundcorner(int x,int y,BYTE direct,unsigned fontColor,unsigned bkColor);
    UINT32 osd_StringDrawLength(const BYTE *str);
    void Draw_Border(UINT32  xStart,UINT32 yStart,UINT32 xLen,UINT32 yLen,BYTE fontColor,BYTE bkColor,BYTE fillColor);
    void Draw_RoundBox(UINT32  xStart,UINT32 yStart,UINT32 xLen,UINT32 yLen,BYTE fontColor,BYTE bkColor);
#endif

extern void osd_print_servo_msg(char *buf);

#ifdef SUPPORT_FONT_OUTLINE
extern void OSD_DrawFontFrame(UINT8 *pDest, UINT8 *pSrc, BYTE Width, BYTE Height,BYTE FrameWidth);
extern void	OSD_AdjustFontWidth( UINT8* pDest, const UINT8* pSrc, BYTE Height,BYTE Width); 	//suxin add 20051009
extern UINT8 OSD_EnlargeFontForFrame(UINT8 *pDest,UINT8 *pSrc,UINT8 Width, UINT8 Height,BYTE FrameWidth);
#endif

#if defined( ADJUST_SPACE_BETWEEN_FONT ) || defined (SUPPORT_NATIVE_FSNAME)  //DENGHG ADD  for ADJUST_SPACE_BETWEEN_FONT function 20060428   
//denghg updata for ADJUST_SPACE_BETWEEN_FONT , NOW it is clarity 2006-4-24 14:11
//denghg move from OSD_AppDraw.c, 2006-6-10 15:31
typedef struct
{
    UINT8      LeftSpaceWidth;
    UINT8      RightSpaceWidth;
}FONTDATA;

extern void   ftGetDrawFontSize(const BYTE* DrawChar, UINT8* pWidth, UINT8* pHeight );
extern UINT32  GetDrawFontBmp(const BYTE* DrawChar ,const BYTE** pBmp);
extern void CntFontContent(const BYTE* pBmp,int uiWidth, int uiHeight,FONTDATA *p);
extern int PreFontDraw_Position(int* x, const FONTDATA* p ,UINT8 uiWidth, UINT8* NoBGLeftwidth);
extern void	OSD_AdjustFontWidth( UINT8* pDest, const UINT8* pSrc, BYTE Height,BYTE Width); 
extern int Cnt_font_Realwidth(const BYTE* pBmp,int uiWidth, int uiHeight );
#endif

#ifdef SUPPORT_SW_OSD_SCALING
extern int osd_init_scaling(int n,  int mode);
extern void osd_region_scaling(int uiRegionIdx, DrawDimension * draw_section);
extern void osd_raw_copy(int uiRegionIdx, DrawDimension * draw_section, BYTE *pLine_scaling, const BYTE *pLine_origin);
#endif


#endif  // _OSD_APPAPI_H_


