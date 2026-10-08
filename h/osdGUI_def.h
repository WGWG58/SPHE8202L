/**************************************************************
** FILE
** osdGUI_def.h
**
** DESCRIPTION
**  some MACRO definition
**
**
**   Creator:  zhaoyanhua
** 	 Date:     2004-5-20 11:16
****************************************************************/

#ifndef  _OSDGUI_DEF_H
#define _OSDGUI_DEF_H

#include "menu_def.h"


#define ONEPAGE				6  //6 button one page


#define SUB_FOLDER_BASE		ISO_FILE_MAX// a flag which denotes it is a subfolder
#define END_FILE			SUB_FOLDER_BASE+ISO_DIR_MAX//a flag which denotes no useful items again

#define TYPE_UNKOWN         0
#define DIR                 1
#define FILE                2

#define PAGE_UP 			0
#define PAGE_DOWN 			1
#define PAGE_LEFT           2
//LEFT page position
//folder bmp unit: 16 pixels one char
#define FS_FOLDER_XSTART       (MENU_XSTART+2)
#define FS_FOLDER_YSTART       MENU_YSTART
//string unit: 16 pixels
#define FS_STRING_XSTART       MENU_XSTART+4
#define FS_STRING_YSTART       MENU_YSTART




#endif//_OSDGUI_DEF_H
