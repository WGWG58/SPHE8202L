/*--------------------------------------------------------------------------
|  File Name   : InfoBanner_func.h
|
|  Description : Function declaration of InfoBannner.c and InfoBanner_ui.c 
|  
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	20040315       feeling      creating
|
*/
#ifndef MENU_FUNC_H
#define MENU_FUNC_H

//extern void osd_draw_passwd_button(UINT32 xStart, UINT32 yStart, UINT32 xLen, BYTE flag );

//void InitMainMenu(void);
void show_info_banner_page(void);
void show_play_mode(void);
void osd_init_info_banner(void);
void info_banner_func_left(void);
void info_banner_func_right(void);
void info_banner_func_up(void);
void info_banner_func_down(void);
void info_banner_func_select(void);
void exit_info_banner(void);
void exe_infobanner_str_rect_display(void);
void exe_infobanner_function(UINT8 Type, UINT8 OpnLR, UINT8 OpnUD);
void init_tt_ch_info(void);
BYTE get_str_circle_num(void);
void info_input_chapter(int num);
void info_input_title(int num);
void info_input_time(int num);
void exit_info_banner_page(void);
#endif

