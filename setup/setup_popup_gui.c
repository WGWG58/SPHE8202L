#include "setup_popup_gui.h"

#ifdef SUPPOT_SETUP_POPUP_PASSWORD_GUI

#ifdef NEW_SOFT_PASSWORD_UI
#include "setup_password_gui_new.c"
#else
#include "setup_password_gui.c"
#endif
#endif

#ifdef SUPPORT_SETUP_POPUP_TESTSPK_GUI
#include "setup_testspk_gui.c"
#endif

#ifdef SUPPORT_SETUP_POPUP_MEDIA_GUI
#include "setup_media_gui.c"
#endif

#ifdef SETUP_POPUP_PSCAN_WARNING_GUI
#include "setup_pscan_warning_gui.c"
#endif


SETUPGUI_TYPE setup_gui_state=SETUPGUI_MENU;

void setup_GetPos_PopUp(UINT8 direction)
{
    switch(setup_gui_state)
    {
        #ifdef SOFT_MENU_REENG
        case SETUPGUI_PASSWORD:
            setup_GetPos_Password(direction);
            break;
        #endif
        #ifdef SUPPORT_SETUP_POPUP_TESTSPK_GUI
        case SETUPGUI_TESTSPK:
            setup_GetPos_Testspk(direction);
            break;
        #endif
        #ifdef SUPPORT_SETUP_POPUP_MEDIA_GUI
        case SETUPGUI_MEDIA:
            setup_GetPos_Media(direction);
            break;
        #endif
        #ifdef SETUP_POPUP_PSCAN_WARNING_GUI
        case SETUPGUI_PSCAN_WARNING:        	
        	setup_GetPos_PscanWarning(direction);
        	break;
        #endif
        default:
            setup_gui_state=SETUPGUI_MENU;
            break;
    }
    if(SETUP_ENTER ==direction)
    {
        setup_mLevel = SETUP_ML0;
        setup_pos[SETUP_ML0] = setup_mLevel;
        setup_pos[SETUP_ML1] = 0;
        setup_pos[SETUP_ML2] = 0;
        setup_pos[SETUP_ML3] = 0;
        setup_gui_state=SETUPGUI_MENU;
    }
}

