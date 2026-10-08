/***************************************************************
*  setup_show_page.c
*  include  in setup_tab_ui1.c   when defined DVD_SETUP_REENG
* 
* Creator:  JSLin 
* Date:         2004/07/28
*
* Modify:	Mimisai
* Date:		2005/11/07
* Reason:	Move to Setup_show_page_xxx.c for different style ui
*
* Description : 
*           setup menu precentation engine, 
*           1. transform content into GUI   
*
****************************************************************/
#ifdef INDIGO_STYLE_OSDUI 
	#include "Setup_show_page_INDIGO_STYLE_OSDUI.c"
#else
	#include "Setup_show_page_OLD_OSD_UI.c"
#endif

