/***************************************************************
*  setup_ui_input.c
*  include  in setup_tab_ui1.c   when defined DVD_SETUP_REENG
* 
* Creator: 	JSLin 
* Date:  		2004/07/28
*
* Description :	
*			adapter,
*			receiver user inputs from IR_cmd and pass to Navigator(setup_get_pos.c)
*
****************************************************************/
#ifdef SUPPORT_MALATA_SETUPMENU
void malata_setup_up_refresh(void)
{
	if((setup_pos[SETUP_ML0]==SETUP_ML2 )
		&&(setup_item[setup_pos[1]][setup_pos[2]+1][1]== STR_OS_DRM_REGISTRATION_CODE)
		)
	{
	   UINT32 old_setup_refresh = setup_refresh;
	    setup_refresh = 1;
		setup_ShowPageL2();
		setup_ShowPageL3();
		setup_refresh = old_setup_refresh;
	}
}

void malata_setup_down_refresh(void)
{
	if((setup_pos[SETUP_ML0]==SETUP_ML2 )
		&&(setup_item[setup_pos[1]][setup_pos[2]-1][1]== STR_OS_DRM_REGISTRATION_CODE)
		)
	{
	   UINT32 old_setup_refresh = setup_refresh;
	    setup_refresh = 1;
		setup_ShowPageL2();
		setup_ShowPageL3();
		setup_refresh = old_setup_refresh;
	}
}
#endif//end=> SUPPORT_MALATA_SETUPMENU

void setup_func_up(void)
{
 	printf("setup_ui_up.c	setup_func_up\n");
	printf("setupLevel:%x	page:%d\n", setupLevel, page);
	setup_mDir = SETUP_UP;
	setup_GetPos(setup_mDir);
	#ifdef SUPPORT_MALATA_SETUPMENU
    malata_setup_up_refresh();
    #endif
    
	return;
}



void setup_func_down(void)
{ 
	printf("setup_ui_down.c	setup_func_down\n");
	printf("setupLevel:%x	page:%d\n", setupLevel, page);
	setup_mDir = SETUP_DOWN;
	setup_GetPos(setup_mDir);
	#ifdef SUPPORT_MALATA_SETUPMENU
	malata_setup_down_refresh();
	#endif
	return;
}

void setup_func_left(void)
{
	printf("setup_ui_right.c	setup_func_right\n");
	printf("setupLevel:%x	page:%d\n", setupLevel, page);
	setup_mDir = SETUP_LEFT;
	setup_GetPos(setup_mDir);
	return;
}

void setup_func_right(void)
{
    #ifdef INPUT_2FOUR_NUM_STOP
    digit_cnt = 0;
    #endif

	printf("setup_ui_right.c	setup_func_right\n");
	printf("setupLevel:%x	page:%d\n", setupLevel, page);
	setup_mDir = SETUP_RIGHT;
	setup_GetPos(setup_mDir);
	return;
}

void setup_func_select(void)
{

#ifdef NEW_PARENTAL_GUI//Jack added 04/12/02
    if(new_parental_gui)
    {
        check_parent_password();
        new_parental_gui = 0;
        return;    
    }
#endif

	printf("setup_ui_sel.c	setup_func_select\n");
	printf("setupLevel:%x	page:%d\n", setupLevel, page);
	setup_mDir = SETUP_SELECTION;
	setup_GetPos(setup_mDir);
	return;
}

