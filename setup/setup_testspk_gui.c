#include "Setup_testspk_gui.h"
#include ".\\h\\TestSpk.h"


#define TESTSPK_GUI_X  18
#define TESTSPK_GUI_Y  3
#define TESTSPK_GUI_TEXT_X 2
#define TESTSPK_GUI_TEXT_XL 12
#define TESTSPK_GUI_TEXT_Y 4
#define TESTSPK_GUI_TEXT_YL 1
#define TESTSPK_GUI_VOL_X 2
#define TESTSPK_GUI_VOL_Y 5

const UINT16 Testspk_iconXY[6][2]= //(x,y) in pixel
{
#ifdef TESTSPK_3CHANNEL//kingslon marked for 6008 20050924
    {0,0},{0,40},{0,80},{20,80},{10,0},{0,80},
#else
    {0,0},{20,0},{0,80},{20,80},{10,0},{20,40},
#endif
};
BYTE testspk_ch=0,old_testspk_ch=0;
void ShowSetupTestspk_SpeakerIcon(BYTE ch,BYTE select)
{
    ch=spk_ch_map[ch];
    osd_DrawIcon(TESTSPK_GUI_X*2+Testspk_iconXY[ch][0],TESTSPK_GUI_Y*32+Testspk_iconXY[ch][1],4,select?4:0);
}
void ShowSetupTestspk_SpeakerStr(void)
{
	switch(spk_ch_map[testspk_ch])
#ifdef TESTSPK_3CHANNEL//kingslon marked for 6008 20050924
	{
		case 0: 
			psprintf(linebuf, "%s %s",_OsdMessegeFont1[osd_font_mode][STR_OS_FSPK],
                    "LEFT");
			osd_draw_rect((TESTSPK_GUI_X+TESTSPK_GUI_TEXT_X+2)*16,(TESTSPK_GUI_Y-4+TESTSPK_GUI_TEXT_Y)*32,TESTSPK_GUI_TEXT_XL*16,TESTSPK_GUI_TEXT_YL*32,0);
    			osd_DrawString(TESTSPK_GUI_X+TESTSPK_GUI_TEXT_X+2,TESTSPK_GUI_Y-4+TESTSPK_GUI_TEXT_Y,linebuf,7,0);

			break;
		case 1:
			psprintf(linebuf, "%s %s",_OsdMessegeFont1[osd_font_mode][STR_OS_FSPK],
                    "RIGHT");
			osd_draw_rect((TESTSPK_GUI_X+TESTSPK_GUI_TEXT_X+2)*16,(TESTSPK_GUI_Y-4+TESTSPK_GUI_TEXT_Y)*32,TESTSPK_GUI_TEXT_XL*16,TESTSPK_GUI_TEXT_YL*32,0);
    			osd_DrawString(TESTSPK_GUI_X+TESTSPK_GUI_TEXT_X+2,TESTSPK_GUI_Y-4+TESTSPK_GUI_TEXT_Y,linebuf,7,0);

			break;
		case 2:
			psprintf(linebuf, "%s %s",_OsdMessegeFont1[osd_font_mode][STR_OS_SSPK],
                    "LEFT");
			break;
		case 3:
			psprintf(linebuf, "%s %s",_OsdMessegeFont1[osd_font_mode][STR_OS_SSPK],
                    "RIGHT");
			break;
		case 4:
			psprintf(linebuf, "%s",_OsdMessegeFont1[osd_font_mode][STR_OS_CSPK]);
			break;
        case 5:
			psprintf(linebuf, "%s",_OsdMessegeFont1[osd_font_mode][STR_OS_SUBWOOFER]);
			osd_draw_rect((TESTSPK_GUI_X+TESTSPK_GUI_TEXT_X+2)*16,(TESTSPK_GUI_Y-4+TESTSPK_GUI_TEXT_Y)*32,TESTSPK_GUI_TEXT_XL*16,TESTSPK_GUI_TEXT_YL*32,0);
    			osd_DrawString(TESTSPK_GUI_X+TESTSPK_GUI_TEXT_X+2,TESTSPK_GUI_Y-4+TESTSPK_GUI_TEXT_Y,linebuf,7,0);

            break;
	}
#else
	{
		case 0: 
			psprintf(linebuf, "%s %s",_OsdMessegeFont1[osd_font_mode][STR_OS_FSPK],
                    "LEFT");
			break;
		case 1:
			psprintf(linebuf, "%s %s",_OsdMessegeFont1[osd_font_mode][STR_OS_FSPK],
                    "RIGHT");
			break;
		case 2:
			psprintf(linebuf, "%s %s",_OsdMessegeFont1[osd_font_mode][STR_OS_SSPK],
                    "LEFT");
			break;
		case 3:
			psprintf(linebuf, "%s %s",_OsdMessegeFont1[osd_font_mode][STR_OS_SSPK],
                    "RIGHT");
			break;
		case 4:
			psprintf(linebuf, "%s",_OsdMessegeFont1[osd_font_mode][STR_OS_CSPK]);
			break;
        case 5:
			psprintf(linebuf, "%s",_OsdMessegeFont1[osd_font_mode][STR_OS_SUBWOOFER]);
            break;
	}
    osd_draw_rect((TESTSPK_GUI_X+TESTSPK_GUI_TEXT_X)*16,(TESTSPK_GUI_Y+TESTSPK_GUI_TEXT_Y)*32,TESTSPK_GUI_TEXT_XL*16,TESTSPK_GUI_TEXT_YL*32,0);
    osd_DrawString(TESTSPK_GUI_X+TESTSPK_GUI_TEXT_X,TESTSPK_GUI_Y+TESTSPK_GUI_TEXT_Y,linebuf,7,0);
#endif
}
#ifdef TESTSPK_CONTROL_VOL
void ShowSetupTestspk_SpeakerVol(void)
{
    psprintf(linebuf, "%+3d dB",get_subvol_vol(spk_ch_map[testspk_ch]));
    #ifdef TESTSPK_3CHANNEL//kingslon marked for 6008 20050924
    osd_DrawString(TESTSPK_GUI_X+2+TESTSPK_GUI_VOL_X,TESTSPK_GUI_Y-4+TESTSPK_GUI_VOL_Y,linebuf,7,0);
    #else
    osd_DrawString(TESTSPK_GUI_X+TESTSPK_GUI_VOL_X,TESTSPK_GUI_Y+TESTSPK_GUI_VOL_Y,linebuf,7,0);
    #endif
}
#endif//#ifdef TESTSPK_CONTROL_VOL
void setup_GetPos_Testspk(UINT8 direction)
{
    polling_testspk_100ms(1);//1:reset timer; 0: normal
    switch(direction)
    {
		case SETUP_SELECTION:
            setup_gui_state=SETUPGUI_MENU;
            setup_mLevel = SETUP_ML2;
            setup_pos[SETUP_ML0] = setup_mLevel;
            setup_pos[SETUP_ML3] = 0;
		case SETUP_ENTER:
            Set_Testspk_Channel_GUI(SETUPGUI_TESTSPK_EXIT);
			break;
        #ifdef TESTSPK_CONTROL_VOL
		case SETUP_UP:
            Set_Testspk_Channel_GUI(SETUPGUI_TESTSPK_VOLUP);
			break;
        
		case SETUP_DOWN:
            Set_Testspk_Channel_GUI(SETUPGUI_TESTSPK_VOLDOWN);
			break;
        #endif//#ifdef TESTSPK_CONTROL_VOL
		case SETUP_LEFT:
            Set_Testspk_Channel_GUI(SETUPGUI_TESTSPK_PREV);
			break;
		case SETUP_RIGHT:
            Set_Testspk_Channel_GUI(SETUPGUI_TESTSPK_NEXT);
			break;
    }
}

void Set_Testspk_Channel_GUI(TESTSPK_TYPE operation)
{
    switch(operation)
    {
        case SETUPGUI_TESTSPK_INIT:
            testspk_ch=0;
            int i;
            ShowSetupTestspk_SpeakerIcon(0,1);
            ShowSetupTestspk_SpeakerStr();
            #ifdef TESTSPK_CONTROL_VOL
            ShowSetupTestspk_SpeakerVol();
            #endif//#ifdef TESTSPK_CONTROL_VOL
            for(i=1;i<MAX_TEST_CHANNEL;i++)
                ShowSetupTestspk_SpeakerIcon(i,0);
            TestSpeaker_Init();
            map_testspk_channel(testspk_ch);
			break;
        case SETUPGUI_TESTSPK_NEXT:
            ShowSetupTestspk_SpeakerIcon(testspk_ch,0);
            testspk_ch++;
            if(testspk_ch >= MAX_TEST_CHANNEL)
                testspk_ch = 0;
            map_testspk_channel(testspk_ch);
            ShowSetupTestspk_SpeakerStr();
            #ifdef TESTSPK_CONTROL_VOL
            ShowSetupTestspk_SpeakerVol();
            #endif//#ifdef TESTSPK_CONTROL_VOL
            ShowSetupTestspk_SpeakerIcon(testspk_ch,1);
			break;
        case SETUPGUI_TESTSPK_PREV:
            ShowSetupTestspk_SpeakerIcon(testspk_ch,0);
            if(testspk_ch == 0)
                testspk_ch = MAX_TEST_CHANNEL-1;
            else
                testspk_ch--;
            map_testspk_channel(testspk_ch);
            ShowSetupTestspk_SpeakerStr();
            #ifdef TESTSPK_CONTROL_VOL
            ShowSetupTestspk_SpeakerVol();
            #endif//#ifdef TESTSPK_CONTROL_VOL
            ShowSetupTestspk_SpeakerIcon(testspk_ch,1);
			break;
        #ifdef TESTSPK_CONTROL_VOL
        case SETUPGUI_TESTSPK_VOLUP:
            set_subvol_vol(spk_ch_map[testspk_ch],1);
            ShowSetupTestspk_SpeakerVol();
			break;
        case SETUPGUI_TESTSPK_VOLDOWN:
            set_subvol_vol(spk_ch_map[testspk_ch],-1);
            ShowSetupTestspk_SpeakerVol();
			break;
        #else
        case SETUPGUI_TESTSPK_VOLUP:
        case SETUPGUI_TESTSPK_VOLDOWN:
            break;
        #endif//#ifdef TESTSPK_CONTROL_VOL
        case SETUPGUI_TESTSPK_EXIT:
            restore_speaker();
			break;
    }
}


