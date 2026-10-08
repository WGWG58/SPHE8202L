/**************************************************************
** FILE
** osdGUI_def.h
**
** DESCRIPTION
**  some function declaration
**
**
**   Creator:  zhaoyanhua
** 	 Date:     2004-5-25 13:59
****************************************************************/

#ifndef  _OSDGUI_FUNC_H
#define _OSDGUI_FUNC_H

void OSDGUI_Init();
void OSDGUI_ShowDirInitPara(void);
void OSDGUI_ShowOneDirContent(int iDir);
void OSDGUI_SetCurrentDir(UINT16 iDir);
void OSDGUI_RefreshButton(int btn_index, int button_state);
BYTE OSDGUI_GetSelButtonType(int btn_index);
INT16 OSDGUI_GetRootDir(void);
INT16  OSDGUI_GetParentDir(UINT16 iSelect, BYTE type);
void OSDGUI_GetOneDirContent(int iDir);
UINT16 OSDGUI_GetCurrentDir(void);
void OSDGUI_GetFileName(BYTE file_name[], UINT16 file_index);
void OSDGUI_GetDirName(BYTE dir_name[], UINT16 dir_index);
void OSDGUI_GetCurrentPage(BYTE page_type);
void OSDGUI_DrawOnePage(void);

UINT32 OSDGUI_CmdUp(void);
UINT32 OSDGUI_CmdRight(void);
UINT32 OSDGUI_CmdLeft(void);
UINT32 OSDGUI_CmdDown(void);

#endif//_OSDGUI_FUNC_H
