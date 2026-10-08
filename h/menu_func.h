/*--------------------------------------------------------------------------
|  File Name   : higui_func.h
|
|  Description : Function declaration of mainmenu.c and mainmenu_ui.c 
|  
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	20040302        zhaoyanhua      creating
|
*/
#ifndef HIGUI_FUNC_H
#define HIGUI_FUNC_H

//osd related function
extern void osd_draw_passwd_button(UINT32 xStart, UINT32 yStart, UINT32 xLen, BYTE flag );
extern void osd_draw_bmp_old(int xStart, int yStart,const BYTE* bmp,  BYTE r);
extern void osd_init_mainmenu(void);
extern void osd_DrawLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth);
extern void osd_draw_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor);
extern void osd_draw_root_button(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen,BYTE color,BYTE flag);
extern void osd_draw_path_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE button_type,BYTE button_flag);
extern void osd_draw_radio_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE yLen, BYTE color,BYTE flag);
extern void  osd_draw_checkbox(BYTE xStart, BYTE yStart, BYTE xLen, BYTE yLen, BYTE color,BYTE flag);
extern void ClearString(UINT32 xstart,UINT32 ystart,UINT32 ilen,BYTE bkcolor);

//tv related funciton
extern void search_ap_tv_out_id(void);
extern void update_tv_format_sel(void);

//program related function
extern void prog_init(void);
extern void ShowProgPage(void);

//cdrom type related
extern BYTE GetCDROMDiscType(void);

void InitMainMenu(void);


void show_mainmenu(void);
void ShowMenuPage(UINT8 page, UINT8 level, UINT8 HL_y);
void mainmenu_func_left(void);
void mainmenu_func_right(void);
void mainmenu_func_up(void);
void mainmenu_func_down(void);
void mainmenu_func_select(void);
void ShowPlayState(UINT32 id);



void ExitMainMenu(void);
void higui_SetDefaultValue(void);
const char * higui_SetItemString(int id);
int higui_GetSelItem(int page,int HL_y);
void higui_DrawSelItem(int page,int parentmenu_level);
void StrCenterDisplay(BYTE x, BYTE y, const BYTE *str,BYTE fontColor, BYTE bgColor, BYTE ButtonFlag);
void higui_DrawSubMenu(int page, int parentmenu_level, int parentmenu_y, int submenu_y);
void higui_RefreshButton(int page, int level, int button_state);
void higui_DrawTransButton(int page, int index_y,int button_state);
void exe_higui_func(UINT8 tt_id, UINT8 sub_id, int value);

//for password
void ShowLockGUI();
void higui_DrawLockImg(int page);
BYTE ShowPasswdGUI(int index_y);
void RefreshPasswordGUI(int GUI_state, BYTE change_flag);
void higui_InputPasswd(int ir_select_number);
void RefreshPasswdButton(int index_x,BYTE button_state, BYTE number_flag);
void higui_ShowPasswd(int input_number);
void ClearWholeRegion(void);
void ResetPasswdCnt(void);
void ExitPasswdGUI(int index_y);
//for rating GUI
void ShowGradeGUI();
void RefreshGradeGUI(int dir);

//for Speaker setup
void higui_DrawSpkeakerImg(int speaker_id, int HL_flag);
void higui_ShowSpeakersPage(int parentmenu_y);
void higui_ShowVolumeImg(int refresh_flag);
void higui_DrawSpkDistanceImg(int parentmenu_y);
void higui_DrawRatioImg(int sub_y);
void higui_SetupValue(int page,int parentmenu_y);

//for pscan setup
void higui_ShowPscanPage(void);
void higui_ExitPscanPage(void);


void run_save_higui_para(int page, int index_y);
//get flag related
BYTE higui_IsStereoOn(void);
BYTE higui_IsPscanEnable(void);
BYTE higui_IsPLMusicOn(void);
BYTE higui_IsButtonSelectable(int page, int index_y);
BYTE higui_IsSubmenuOn(int page, int index_y,int level);
BYTE higui_IsPlaymodeValid(void);

void higui_ShowTVRatio(void);
void higui_ShowOperationMsg(int page, int level);

void SetDefaultSetting(void);

#endif/*ifndef higui_FUNC_H*/

