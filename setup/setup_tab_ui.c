/*
*   Terry,2004/3/28 04:51PM
*   hold old setup_tab_ui.c to setup_tab_ui_o.c
*/

#define __MODIFY_SETUP_UI

#ifdef __MODIFY_SETUP_UI
#include "setup_tab_ui1.c"
#else
#include "setup_tab_ui_o.c"
#endif
