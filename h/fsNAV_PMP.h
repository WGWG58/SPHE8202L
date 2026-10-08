#ifndef __fsNAV_PMP_H
#define __fsNAV_PMP_H

#include "types.h"
#include "udf_167.h"
#include "global.h"
#include "fs96602.h"
#include "fsGUI1.h"
#include "psd.h"

//------------------------------------------------
//for icon menu GUI
typedef struct
{
    BYTE    main_icon_index;
    BYTE    main_icon_will;
    BYTE    first_level_index;
    BYTE    setup_menu_index;
    BYTE    setup_menu_will;
    BYTE    setup_level_index;
}FSNAVUI;
//------------------------------------------------
//location of selected rec in main menu
#define X_STEP      198  
#define Y_STEP      156
#define X_LEN       190
#define Y_LEN       152      
#define X_START     (8)
#define Y_START     (14)
#define X_END       (X_START + X_LEN)
#define Y_END       (Y_START + Y_LEN)
//------------------------------------------------
//location of button in setup main menu
#define SETUP_X_START   40
#define SETUP_Y_START   90
#define SETUP_X_LEN     241
#define SETUP_Y_LEN     61
#define SETUP_X_STEP    241  
#define SETUP_Y_STEP    70
#define SETUP_X_END     (SETUP_X_START + SETUP_X_LEN)
#define SETUP_Y_END     (SETUP_Y_START + SETUP_Y_LEN)
//---------------------------------------------------
//info of selected rec
#define COLOR       3
#define LINEWIDTH   4
#define REGION      2
//------------------------------------------------
//defination of icon in first level menu
#define VIDEO_ICON  0
#define MUSIC_ICON  1
#define PHOTO_ICON  2
#define BROWSE_ICON 3
#ifdef SUPPORT_PMP_COPY
#define COPY_ICON   4
#define SETUP_ICON  5
#else
#define SETUP_ICON  4
#endif
//------------------------------------------------
//defination of button in setup main menu
#define AUDIO_BUTTON    0
#define VIDEO_BUTTON    1
#define CLOCK_BUTTON    2
#define SYSTEM_BUTTON   3
#define LANGUAGE_BUTTON 4
#define POWER_BUTTON    5
//------------------------------------------------
#define BLUE_DARK_Y         0x57
#define BLUE_DARK_CRCB      0x6194
#define GRAY_Y              0x80
#define GRAY_CRCB           0x7882
#define WHITE_GRAY_Y        0xb3
#define WHITE_GRAY_CRCB     0x7882
#define ORANGE_Y            0x9a
#define ORANGE_CRCB         0xbb2f
//------------------------------------------------
UINT16 HDDCardJudgeDir(INT16 iDirIndex);
void FSGUI_Refresh_PMP(void);
void PlayFile(DIR_REC *FileInfo);
void SelectCopyIcon(void);
void show_path_info(const char *s);
void update_path_info(void);
void osd_show_pmp_hl(BYTE index);
void osd_show_setup_hl(BYTE index);
void ShowItemHL(int hl_index);
void show_copy_page(void);
BYTE quick_browse_folder(BYTE flag);
void select_icon(void);
void FSGUI_DirList(UINT16 iDirIndex);
void show_copy_select_menu(BYTE index);
void ShowCopyingProcess(char *s);
void PMP_show_next_osd(void);              //////////yangli 2005/8/10
void PMP_show_prev_osd(void);
void pmp_enable_user_flag(UINT32 i);
int pmp_get_user_flag(void);
void pmp_disable_user_flag(UINT32 i);
void osd_init_show_setup_pmp(void);
#endif//#ifndef __fsNAV_PMP_H

