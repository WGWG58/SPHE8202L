void setup_GetPosL3(UINT8 direction);
void setup_ShowPageL3(void);
void setup_GetPos_Media(UINT8 direction)
{
    switch(direction)
    {
		case SETUP_SELECTION:
		case SETUP_UP:
		case SETUP_DOWN:
            setup_GetPosL3(direction);
            setup_ShowPageL3();
			break;
        default:
            break;
    }
}

void show_setup_popup_media_gui(void)
{
    UINT16 P=setup_getItemPos(STR_OS_MEDIA_TYPE);
    if(P!=0xffff)
    {
        UINT16 I=0;
        UINT16 S=0;
        I=P&0xff;
        P=P>>8;
        S= MIN_ITEM_SEL;//setup_VA[SETUP_VA_MEDIA_TYPE];
        
        setup_gui_state=SETUPGUI_MEDIA;

        ircmd_setup();
        
        osd_draw_rect(0,0,region[0].osd_w*2,region[0].osd_h,15);
        setup_gui_state=SETUPGUI_MEDIA;
        setup_mLevel = SETUP_ML3;
        setup_pos[SETUP_ML0] = setup_mLevel; 
        setup_pos[SETUP_ML1] = P;
        setup_pos[SETUP_ML2] = I;//MAX_PAGE_ITEM;
        setup_pos[SETUP_ML3] = S;
        setup_refresh = 1;
        setup_ShowPageL3();
        setup_refresh = 0;
    }
}


