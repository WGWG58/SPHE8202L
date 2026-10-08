/********************************************
*  setup_tab_ui_op.c
*
*  include in setup_tab.c   
*  
* 
*  UI function:
*     LEFT,RIGHT, UP, DOWN,  SELECT, ShowSetupPage. 
* 
* Creator: zhaoyanhua 
* Date:  3-7-25 17:12
*******************************************/
#ifdef OP_UI
#include "menu_func.h"

//NULL functions
void ShowSetupPage(BYTE refresh) {}
void ShowCUSTMMsg(void) {}


void ExitSetupPage(BYTE save) //jhuang 2001/5/18 10:30PM
{
   ExitMainMenu(); 
}

void setup_func_left(void)
{
    mainmenu_func_left();    
}

void setup_func_right(void)
{
    mainmenu_func_right();    
}

void setup_func_up(void)
{
    mainmenu_func_up();    
}

void setup_func_down(void)
{
    mainmenu_func_down();    
}

void setup_func_select(void)
{
    mainmenu_func_select();    
}

#endif//ifdef OP_UI
