#include "config.h"
#include "global.h"
#include "memmap.h"
#include "func.h"
#include "stdlib.h"
#include "cfont.h"
#include "osd.h"
#include "osdhw.h"
#include "osdfont.h"
#include "osd_str.h"
#include "user_init.h"
//DVD
#include "regmap.h"
#include "endian.h"
#include "memmap0.h"

void reset_osd(void) {}
void osd_disable(void) {regs0->osd_en = 0;}
void osd_enable(void) {regs0->osd_en = 1;}
void osd_create_regionNes(t_osd_region *p, int X, int Y,UINT16 *pallette) {}
void osd_init_music(void) {}
void osd_init_ampvol(void) {}
void osd_create_region_setup(t_osd_region *p, int X, int Y, t_osd_region *prev,BYTE bColorMode,BYTE bScanMode) {}
void osd_init_setup(void) {}
void osd_DrawString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor) {}
void osd_DrawLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth) {}
void osd_draw_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor) {}
void osd_draw_setup_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown) {}
void osd_clear_setup() {}
void osd_init(void) {}
void osd_Move2OSD0(BYTE iLine) {}
void osd_ClearOSD0(BYTE iSLine, BYTE iELine) {}
void osd_restore() {}
void restore_osd_msg(void) {}
inline void polling_osd(int diff) {}
void osd_tog_region(BYTE r, int mode) {}
void PrintOsdMsg(UINT32 id,UINT8 r,int t,BYTE mode) {}
void osdshow(UINT8 r,char *buf) {}
void PrintOsdMsg2(BYTE r, int t)  {}
void ClearOsdMsg(int i) {}
void InitSW_region(void) {}
void osd_create_region1(t_osd_region *p, int X, int Y, t_osd_region *prev,BYTE bColorMode,BYTE bScanMode) {}
void osd_print_region1(t_osd_region *p, const char *s0) {}
void osd_print_regionEQ(t_osd_region *p, const char *s0) {}
//void osd_print_eq_setting(UINT8 r,UINT8 unSele) {}
void osd_print_eq(UINT8 r, const BYTE *p) {}
void draw_osd_board(UINT8 r,UINT8 board_type) {}
#ifdef OSD_PAL_RGB_16b		        
void osd_init_NES(int x,int y,int w,int h, const UINT16 *pPalette) {}
#else
void osd_init_NES(int x,int y,int w,int h, const UINT16 *pPalette) {}
#endif
#ifdef OSD_PAL_16b
//update color index
void SetOsdCol(UINT8 rb,UINT8 re,UINT8 id,UINT16 color) {}
#else
//update color index
void SetOsdCol(UINT8 rb,UINT8 re,UINT8 id,UINT32 color) {}
#endif
void osd_DrawIcon(int xStart, int yStart, unsigned index, unsigned page) {}
void osd_replace_rect_color(BYTE bkColor, BYTE destColor) {}
const BYTE *get_font_entry(int tbl, int entry) {}

