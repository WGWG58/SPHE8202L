
#include "osd_api.h"
#include "user_init.h"
#include "cust_def.h"

//////////
#if defined(LARGE_SCORES_DISPLAY)
void draw_midi_bitmap_HZnew(const UINT8* pFont, int xStart, int yStart,
    BYTE fontcolor, BYTE bgcolor, BYTE  FigureColor, BYTE FontType,
    BYTE number);
void Osd_Clear_Rect(int xx, int yy, int xlen, int ylen, BYTE colour,
    BYTE regNum);
void osd_Clear_Region(BYTE reg, BYTE bkColor);
#endif
//////////
#ifdef TONIC_DVD
void draw_osd_board_pscan(UINT8 r, UINT8 board_type);
void OsdShowPscan(BYTE onoff);
void draw_osd_board_pscan(UINT8 r, UINT8 board_type);
#endif
//////////
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)
void osd_init_bbk_setup(void);
void osd_draw_icon_bbk(int xStart, int yStart,int index);
#endif
//////////
#ifdef ROLL_SHOW_SETUP
void MoveRect2buf(int xStart, int xEnd, int yStart, unsigned color, int yLen, int r);
void MoveString2Buf(BYTE xStart, BYTE yStart,BYTE * str, BYTE fontColor, BYTE bkColor);
void MoveBuf2OSD(UINT16 xStart, UINT16 xEnd);
#endif
//////////
#ifdef SUPPORT_REP_READ
void osd_draw_read_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown);
#endif
//////////



