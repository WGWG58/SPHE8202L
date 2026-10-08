/**************************************************************
** FILE
** fsGUI_osd_func.h
**
** DESCRIPTION
**   funciton declaration
**  
**
**   Creator:  zhaoyanhua
** 	 Date:     2004-4-2 11:04
****************************************************************/

#ifndef  FSGUI_OSD_FUNC_H
#define FSGUI_OSD_FUNC_H
//osd related funcitons
extern void osd_draw_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor);;
extern void ClearString(UINT32 xstart,UINT32 ystart,UINT32 ilen,BYTE bkcolor);
extern void osd_draw_path_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE button_type,BYTE button_flag);
extern void osd_DrawRegionString(UINT32 xStart, UINT32 yStart, const BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r);
extern void osd_init_mainmenu(void);
extern void osd_draw_hline_region(int xStart, int xEnd, int y, unsigned color, int n, int r);
extern void osd_draw_bmp_old(int xStart, int yStart,const BYTE* bmp,  BYTE r);
extern void ShowOperationMsg(UINT16 osd_id, BYTE r);
extern void osd_DrawRegionLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth, BYTE r);

//mainmenu related funcitons
extern void show_mainmenu(void);
extern void StrCenterDisplay(BYTE x, BYTE y, const BYTE *str,BYTE fontColor, BYTE bgColor, BYTE ButtonFlag);
extern void ShowMenuPage(UINT8 page, UINT8 level, UINT8 HL_y);

//in sysmain2.c
extern void ShowTitle();

#ifdef SURRORT_MP3_PREPLAY
INT16 FSGUI_GetHLMp3File(void);
//for preplay funciton
extern void FS_ClearPreplayFlag(void);
#endif

UINT32 FSGUI_OsdCmdRight();
UINT32 FSGUI_OsdCmdLeft();
UINT32 FSGUI_OsdCmdDown();
UINT32 FSGUI_OsdCmdUp();
UINT32 FSGUI_OsdCmdSelect();
UINT32 FSGUI_OsdCmdPlay();
void FSGUI_OsdMenu();
void FSGUI_RefreshMenu(int mode);
void FSGUI_Return2Menu(void);
void FSGUI_Osdinit();

void FSGUI_ShowOneDirContent(int iDir,int type);
UINT16 FSGUI_GetRootDir(void);


void FSGUI_ShowCurrentSelection(UINT16 file_index);
void FSGUI_OsdExitGUI();
void FSGUI_OperationInit(void);

void FSGUI_GetOneDirContent(int iDir);
void FSGUI_ShowOperationMsg(void);
BYTE GetCDROMDiscType(void);
void CalcDirFirstPage(UINT16 iDir);
void FSGUI_GetPathName(BYTE pathname[], UINT16 iDir);
BYTE FSGUI_IsFolderEnd(UINT16 iDir, BYTE Direction);
#endif//#ifndef  FSGUI_OSD_FUNC_H

