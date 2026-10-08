/********************************************
*  setup_newstyle_ui.h
*
*  include  in setup_tab.c   
*  when normal setup menu.
* 
*  UI function:
*     LEFT,RIGHT, UP, DOWN,  SELECT, ShowSetupPage. 
* 
* Creator: zhaoyanhua 
* Date:  3-7-25 17:12
*******************************************/
#ifdef SUPPORT_MIDI
#include "fsmidi.h"
#ifdef QISHENG_DEBUG_04_10_09
#include "fsmidiui.h"
#endif
#endif

#ifndef DVDRELEASE
//#define SETUP_UI_DBG
#endif

#ifndef SETUP_UI_DBG
#undef ui_printf
#undef ui_print_block
#define ui_printf(f, a...) do {} while (0)
#define ui_print_block(x,y) do {} while (0)
#else
#define ui_printf printf
#define ui_print_block print_block
#endif

#ifdef PULIANG_SETUP_MENU  //yaowh add 04-12-15
    extern int show_menu_setup_flag;
#endif

extern  unsigned int get_iop_b_status();

#if defined(DVB_MENU_SETUP_STYLE) || defined(DVB_MENU_TYPE1) //Maoyong 2004-12-21 20:41 for disable unrealized item of DVB Menu
extern const char *osd_str_dvb_install[N_OSD_LANGS][5];
extern const char *osd_str_dvb_channel[N_OSD_LANGS][6];

#define IsDvbSetupLanguage()    ( (page == INSTALLPAGE) && (setup_item[page][index_y][1] == STR_OS_OSD) )
#ifdef SUPPORT_DVB_TIMER //kehw 2005-04-20 modify
#define IsDvbSetupTimezone()  (0)
#else
#define IsDvbSetupTimezone()    ( (page == INSTALLPAGE) && (setup_item[page][index_y][1] == STR_OS_TIME_ZONE) )
#endif
#define IsDvbSubItem()          ( (system_state == SYSTEM_TS) && (IsDvbSetupLanguage() || IsDvbSetupTimezone()) )
#define IsDvbSubMenuPageItem()  ( IsDvbSubItem() || ( (page != CHANNELPAGE) && (page != INSTALLPAGE) ) )
#define IsDvbStateHasSubMenu()  ( (system_state == SYSTEM_TS) && IsDvbSubMenuPageItem() && setupLevel )   
#define IsDvbStateNoSubMenu()   ( (system_state == SYSTEM_TS) && !IsDvbSubMenuPageItem() && setupLevel  )    

/*UINT8 IsValidDvbMenuItem(UINT8 i)
{
    UINT8 uRes = 0;
    if(system_state == SYSTEM_TS ) {
        if(((dvbpage == INSTALLPAGE) && (i == ITEM_AUTO_SCAN || i == ITEM_MANUAL_SCAN ))
        || ( (dvbpage == CHANNELPAGE) && (i == ITEM_ADD_CHANNEL || i == ITEM_EDIT_CHANNEL)))
        uRes =  1;
    }      
    return uRes;
}

void GetUpValidDvbMenuItem(void)
{
    
    if(system_state == SYSTEM_TS)
    {
        if(dvbpage == INSTALLPAGE)
        {
            while(index_y == ITEM_AUTO_SCAN || index_y == ITEM_MANUAL_SCAN)
                index_y--;
        }
        else if(dvbpage == CHANNELPAGE)
        {
            while(index_y == ITEM_ADD_CHANNEL ||index_y == ITEM_EDIT_CHANNEL)
                index_y--;
        }
    }
}

void GetDownValidDvbMenuItem(void)
{

    if(system_state == SYSTEM_TS)
    {
        if(dvbpage == INSTALLPAGE)
        {
            while(index_y == ITEM_AUTO_SCAN || index_y == ITEM_MANUAL_SCAN)
            {
                index_y++;
                if(index_y > (MAX_ITEM_SEL - 1))
                    index_y = 0;
            }
        }
        else if(dvbpage == CHANNELPAGE)
        {
            while(index_y == ITEM_ADD_CHANNEL || index_y == ITEM_EDIT_CHANNEL)
            {
                index_y++;
                if(index_y > (MAX_ITEM_SEL - 1))
                    index_y = 0;
            }
        }
    }
}
*/
//When enter DVB turn off MIC and restore MIC state when in DVD state. Maoyong 2005-1-18 16:58
void ControlDvbDvdMic()
{
	if(system_state == SYSTEM_TS)
		exe_setup_function(STR_OS_MIC_ONOFF, STR_OS_OFF, 1);
	else
	{
		if(SETUP_MIC_ONF == 2)//AUTO
			exe_setup_function(STR_OS_MIC_ONOFF, STR_OS_AUTO, 1);
		else
			exe_setup_function(STR_OS_MIC_ONOFF, STR_OS_OFF, 1);
	}
}

const char *SetDvbItemString(UINT16 idString)
{
    const char* str;
    if(system_state == SYSTEM_TS)
    {
    	if(idString == STR_OS_EXIT_MENU || idString == STR_OS_OSD)
    		str = _OsdMessegeFont1[osd_font_mode][idString];
    	else if(page == INSTALLPAGE)
    	{
    		str = osd_str_dvb_install[osd_font_mode][idString-STR_OS_DVBT_CONFIG];
    	}
    	else if(page == CHANNELPAGE)
    	{
    		str = osd_str_dvb_channel[osd_font_mode][idString-STR_OS_TV_CHANNEL];
    	}
    	else
    		str = _OsdMessegeFont1[osd_font_mode][idString];
    }
    else
    	str = _OsdMessegeFont1[osd_font_mode][idString];
    return str;
}
#endif  //#ifdef DVB_MENU_SETUP_STYLE Maoyong 2004-12-22 13:49 for disable unrealized item of DVB Menu

#ifdef SHOW_SETUPMENU_SETUP     //linrc modify 2004-5-9 20:01
#ifndef DVD_SETUP_REENG
static inline void show_setupmenu(void)
{
     if (full_scrn&CUSTM)   //2004-7-28 11:15?宇P
     return;
     int    menuset;
     const char *setupmenu_str;
     char buf[3];
     int j;
     for (j=0; j<MAX_PAGE_ITEM; j++)
     {
        sel=setup_sel[page][j];
        id = setup_item[page][j][sel];
        if(page==VIDEOPAGE)                   //LINRC ADD 2004-5-6 0:56 for show the video setup
        {
           menuset = SETUP_BRIGHTNESS - 2;
           psprintf(buf,"%02d",menuset);
           osd_DrawString(SETUP_SUB_XSTART+1, 3,buf, S16WHITEFONT, 1);
           #ifdef PULIANG_SETUP_MENU       //yaowh add 04-12-15
               menuset = SETUP_HUE - 2;
               psprintf(buf,"%02d",menuset);
               osd_DrawString(SETUP_SUB_XSTART+1, 4,buf, S16WHITEFONT, 1);
               menuset = SETUP_CONTRAST - 2;
               psprintf(buf,"%02d",menuset);
               osd_DrawString(SETUP_SUB_XSTART+1, 5,buf, S16WHITEFONT, 1);
           #else
           menuset = SETUP_CONTRAST - 2;
           psprintf(buf,"%02d",menuset);
           osd_DrawString(SETUP_SUB_XSTART+1, 4,buf, S16WHITEFONT, 1);
           menuset = SETUP_HUE - 8;
           psprintf(buf,"%02d",menuset);
           osd_DrawString(SETUP_SUB_XSTART+1, 5,buf, S16WHITEFONT, 1);
           menuset = SETUP_SATURATION - 2;
           psprintf(buf,"%02d",menuset);
           osd_DrawString(SETUP_SUB_XSTART+1, 6,buf, S16WHITEFONT, 1);
            #endif
        }
        else
        {
           setupmenu_str = setup_SetItemString();
           osd_DrawString(SETUP_SUB_XSTART+1, j+3, setupmenu_str, S16WHITEFONT, 1);
           #ifdef HANYANG_SETUPMENU
           if(page==AUDPAGE)
           {
              menuset = SETUP_AC3DIGITAL_DYNA - 2;
              psprintf(buf,"%02d",menuset);
              osd_DrawString(SETUP_SUB_XSTART+1, 6,buf, S16WHITEFONT, 1);
           }
           #else
           if(page==AC3DIGITALPAGE)
           {
              menuset = SETUP_AC3DIGITAL_DYNA - 2;
              psprintf(buf,"%02d",menuset);
              osd_DrawString(SETUP_SUB_XSTART+1, 4,buf, S16WHITEFONT, 1);
           }
           #endif
         }
     }
}
#else//#ifndef DVD_SETUP_REENG  //denghg add  2004-9-28 20:29
static inline void show_setupmenu(void)
{
	   if (full_scrn&CUSTM)   //denghg  2004-9-27 21:05
     return;

    //added by wangwei,2005-3-30 16:32(For hanyang setup menu bug.To clear 3th level osd message before showing setup menu previous settings.)
    osd_draw_rect((SETUP_MAX_WIDTH*8)-8, 10+SETUP_BUTTON_HEIGHT*2+22, (SETUP_MAX_WIDTH*8)-10, (MAX_PAGE_ITEM*SETUP_BUTTON_HEIGHT)+10, setupBGcolorL3);

     int  j,VA,k,menuset;
     const char *setupmenu_str;
     char buf[3];
     for(j=1; j<=MAX_PAGE_ITEM; j++)
	   {
	   	  VA = setup_item[setup_pos[SETUP_ML1]][j][MAX_ITEM_SEL+1];
		    k=setup_item[setup_pos[SETUP_ML1]][j][setup_VA[VA]];
        //"(setup_item[setup_pos[SETUP_ML1]][j][0]==SET_NM)"marked by wangwei,2005-4-2 13:23(for showing "PASSWORD" item's setting.)
        if((setup_item[setup_pos[SETUP_ML1]][j][0]==SET_SH)||(setup_item[setup_pos[SETUP_ML1]][j][0]==SET_SPACE)/*||(setup_item[setup_pos[SETUP_ML1]][j][0]==SET_NM)*/||(setup_item[setup_pos[SETUP_ML1]][j][0]==SET_NE)) {}
	   	  else if(setup_item[setup_pos[SETUP_ML1]][j][0]==SET_FUNC)
	   	  {
            if(VA == SETUP_VA_DEFAULT)//{}//modifed by wangwei,2005-4-2 10:12(For hanyang SETUP MENU showing "DEFAULT" item's setting.)
            {
                setupmenu_str = _OsdMessegeFont1[osd_font_mode][k];
                osd_DrawString(SETUP_SUB_XSTART+1, j+2, setupmenu_str, setupFcolorIN, 0);
            }
		 	     else if((VA==SETUP_VA_OSD_LANG)||(VA==SETUP_VA_AUDIO_LANG)||(VA==SETUP_VA_SUBTITLE_LAN)||(VA==SETUP_VA_MENU_LANG))
		 	     {
		 	     	  if(k==STR_OS_OFF)
		 	     	     setupmenu_str = _OsdMessegeFont1[osd_font_mode][k];
              else
                 setupmenu_str = lang_names[osd_font_mode][k];
                 osd_DrawString(SETUP_SUB_XSTART+1, j+2, setupmenu_str, setupFcolorIN, 0);
           }
           else
		 	     {
		 	     	  setupmenu_str= _OsdMessegeFont1[osd_font_mode][k] ;
		 	        osd_DrawString(SETUP_SUB_XSTART+1, j+2, setupmenu_str, setupFcolorIN, 0);
		 	     }
		 	  }
        else if(setup_item[setup_pos[SETUP_ML1]][j][0]==SET_NM)//added by wangwei,2005-4-2 10:09(For hanyang SETUP MENU showing "PASSWORD" item's setting.)
        {
            setupmenu_str = _OsdMessegeFont1[osd_font_mode][k];
            osd_DrawString(SETUP_SUB_XSTART+1, j+2, setupmenu_str, setupFcolorIN, 0);
        }
		 	  else  //
		 	  {
		 	  	 	//if((VA==SETUP_VA_BRIGHTNESS)||(VA==SETUP_VA_CONTRAST)||(VA==SETUP_VA_SATURATION)||(VA==SETUP_VA_DYNAMCRANGE)||(VA==SETUP_VA_CSPK_DELAY)||(VA==SETUP_VA_MIC_VOL)||(VA==SETUP_VA_ECHO))
		 	  	  if((VA==SETUP_VA_HUE)||(VA==SETUP_VA_KEY))
		 	  	     menuset=setup_VA[VA]-8;
		 	  	  else  if(VA==SETUP_VA_SSPK_DELAY)
		 	  	     menuset=(setup_VA[VA]-2)*3;
		 	  	  else
		 	  	     menuset=setup_VA[VA]-2;
		 	  	     psprintf(buf,"%02d",menuset);
               osd_DrawString(SETUP_SUB_XSTART+1, j+2,buf, setupFcolorIN, 0);
		 	  }

		 }
}
#endif//#ifndef DVD_SETUP_REENG //denghg  end     show_setupmenu  in DVD_SETUP_REEN



#endif // end SHOW_SETUPMENU_SETUP

#include "setup_ui_ext_func.h"
#include "setup_ui_def.h"

//=============================================
//for setup re-engineering  //added by JS   20040728
#ifdef DVD_SETUP_REENG

#ifdef SUPPORT_SETUP_POPUP_GUI//added by chenzhao 20050524
#include "setup_popup_gui.c"
#endif//SUPPORT_SETUP_POPUP_GUI
#include "setup_ui_util.c"

#ifdef INDIGO_STYLE_OSDUI
	#include "setup_OSD_util_INDIGO_STYLE_OSDUI.c"
#else
#include "setup_OSD_util.c"
#endif

#ifdef SOFT_MENU_REENG //added by chenzhao 20050520
#include "setup_show_page_sfm.c"
#else//#ifdef SOFT_MENU_REENG
#include "setup_show_page.c"
#endif//#ifdef SOFT_MENU_REENG
#include "setup_get_pos.c"
#include "setup_ui_input.c"

#else

#include "setup_ui_down.c"
#include "setup_ui_up.c"
#include "setup_ui_left.c"
#include "setup_ui_right.c"
#include "setup_ui_sel.c"
#endif
//==============================================


//#define SHOW_SYSTEM_CLOCK

//=============================================
//for DVD_SETUP_REENG   //added by JS   //20040728
#ifdef DVD_SETUP_REENG
#ifdef SELECT_MEDIA_IN_SETUPMENU   //chenzhao20060116
extern void setupSettingMediaItem(void);
#endif  //dengh end
void ShowSetupPage(BYTE refresh)
{


    if(refresh){

    #ifdef INDIGO_STYLE_OSDUI
        if(refresh == 2) {     // for redrawing the setup menu icon, by robert.chang, 2006-07-05
   	     	extern BYTE reDrawSetupIconPage;
	     	reDrawSetupIconPage = 0;
        }
    #endif

        setup_refresh = 1;
        setup_ShowPageL1();
        setup_ShowPageL2();

        //int id = setup_item[setup_last_pos[1]][setup_last_pos[2]][1]; //helm 050622
        //if(id!=STR_OS_DEFAULT_SETUP)    //helm 050622
        setup_ShowPageL3();

        setup_refresh = 0;
    } else {
        osd_init_setup();
        #ifdef SELECT_MEDIA_IN_SETUPMENU   //denghg  add  2005-2-18 14:05
        setupSettingMediaItem();
        #endif  //dengh end
        setup_mDir = SETUP_ENTER;
        setup_GetPos(setup_mDir);
    }

}

#else //==============================================
void ShowSetupPage(BYTE refresh)
{
    int     i;
    BYTE    fontColor, bgColor;
    BYTE    upDown;
    const char   *str;
    #ifdef  SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28
    UINT16 line=SETUP_MAX_WIDTH*16;
    #else
    UINT16 line=SETUP_MAX_WIDTH*16-20;
    #endif

    #ifdef  SHOW_SETUPMENU_SETUP  //linrc add 2004-5-1 20:31
    osd_draw_rect(300, 75, 250, 350, 1);
    #endif
    reset_passwd_cnt();

    #ifdef SELECT_MEDIA_IN_SETUPMENU    //Maoyong 2004-8-10 17:23, just loas as act meida when setup
    setupSettingMediaItem();
    #endif

    #ifdef DVB_MENU_SETUP_STYLE         //Maoyong 2004-12-22 11:06
    SetOsdCol(0, 0, 8,  0xC8C8C8ff);
    #endif

    if (full_scrn&CUSTM)
    { //set to CUSTM mode
        osd_init_setup();
        setupLevel = 1;

        #ifdef SUPER_DEFAULT_OSD_LANG       //freyman add 2004-2-11 9:11
        if(id==STR_OS_OSD)
            index_y = CUSTMOSDITEM;
        else
        #endif

#ifdef CUSTM_MENU_REVISE //WSLEE for customer menu region item fix 20050526 PM2:00
	index_y = REGION_REMOVE -1;
#else
        index_y = 2;
#endif


        index_y_start = 0;
    }

    if (refresh)
    {
        //draw main rect
        #ifdef  SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28
        //to move the main rect down for 22 pixels
            osd_draw_rect(0, 0, line, 22, SSHEER);
            osd_draw_rect(0, 0+22, (SETUP_MAX_WIDTH*16), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT), SBGCOLOR);//wangfeng 3-8-27 21:44
        #elif defined(SETUP_COLOR_TYPE2)
            #ifdef EASTECH_NEW_SETUP_MENU
                osd_draw_rect(0, /*10+SETUP_BUTTON_HEIGHT*2+10*/0, (SETUP_MAX_WIDTH*16), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT), SBGCOLOR);  //modified by Tom
            #else
                osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+10, (SETUP_MAX_WIDTH*16), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-84), SBGCOLOR);
            #endif
        #else
            osd_draw_rect(0, 0, (SETUP_MAX_WIDTH*16), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT), SBGCOLOR);

            if (p_scan==1)
            {
                //draw top horizontal line
                #ifndef SPE_SETUP
                    osd_DrawLine(12, SETUP_BUTTON_HEIGHT+20, (SETUP_MAX_WIDTH*16-10), SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 2);
                    //draw bottom horizontal line
                    osd_DrawLine(10, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 2);
               #endif
            }
            else
            {
                 #ifndef SPE_SETUP
                    osd_DrawLine(12, SETUP_BUTTON_HEIGHT+20, (SETUP_MAX_WIDTH*16-10), SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 1);
                    osd_DrawLine(10, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 1);
                 #endif

            }
             #ifndef SPE_SETUP
                //draw left vertical line
                osd_DrawLine(10, SETUP_BUTTON_HEIGHT+20, 10, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SWHITECOLOR, 1);
                //draw right vertical line
                osd_DrawLine((SETUP_MAX_WIDTH*16-12), SETUP_BUTTON_HEIGHT+20, (SETUP_MAX_WIDTH*16-12), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 1);
                //osd_DrawLine((SETUP_MAX_WIDTH*16-10), SETUP_BUTTON_HEIGHT+12, (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SWHITECOLOR, 1);
            #endif          //end  #ifndef SPE_SETUP
        #endif

        if (refresh==2)
        {
            #if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)&& !defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-4 14:17//wangfeng 2003-08-29 17:28
                #ifdef SPE_SETUP  //2004-4-28 19:03  zhangyu-lorenc
                    osd_draw_rect(21, 10, line-18, SETUP_BUTTON_HEIGHT+10, SBARCOLOR);//张宇不会
                #else
                    osd_draw_rect(10, 10, line, SETUP_BUTTON_HEIGHT+10, SBARCOLOR);//张宇
                #endif
            #endif

            #ifdef  SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28
                //draw blue bar for main pages of the menu
                osd_draw_rect(0, 22, line, SETUP_BUTTON_HEIGHT+10, SBARCOLOR);//wangfeng 3-8-27 21:47
                //draw black bar for the output of main page
                osd_draw_rect(0, SETUP_BUTTON_HEIGHT+10+10+10+2, line, SETUP_BUTTON_HEIGHT-2, 0);//wangfeng 3-8-27 21:47
                //draw blue bar at the bottom of the menu
                osd_draw_rect(0, SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-SETUP_BUTTON_HEIGHT, line, SETUP_BUTTON_HEIGHT, SBARCOLOR);
            #elif defined(SETUP_COLOR_TYPE2)
                osd_draw_rect(10, 10, line, SETUP_BUTTON_HEIGHT+12,13);

                #ifndef SKYWORTH_DVD    //3-10-28 3:33张宇P
                osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+10+(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)-100, (SETUP_MAX_WIDTH*16), /*(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)*/16, 13);//SBGCOLOR);
                #endif
                osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT+20, line+20, SETUP_BUTTON_HEIGHT+1, 0);//3-8-25 2:26张宇P
            #else
                #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-2 18:56
                    #ifdef SPE_SETUP
                        osd_draw_rect(21, 10, line-18, SETUP_BUTTON_HEIGHT+10, 6); //2004-4-20 09:25张宇P bmmm
                    #else
                        osd_draw_rect(10, 10, line, SETUP_BUTTON_HEIGHT+10, 1); //2004-4-20 09:25张宇P bmmm
                    #endif   // end #ifndef SPE_SETUP
                #endif//#ifndef QSI_SETUP_MENU_DESIGN
            #endif

            //#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
            #if defined(NEXTPAGE_SYS)       //freyman 2004-3-26 0:10
                #if!defined(SETUP_COLOR_TYPE1)&&!defined(SETUP_COLOR_TYPE2)&& !defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-4 14:17 //wangfeng 2003-08-29 17:28
                    if(page==SysNextPage)
                        osd_draw_rect((line*0)/6+10, 10, line/6, SETUP_BUTTON_HEIGHT+10, SBGCOLOR);
                    else
                #endif
            #endif
//          #ifndef SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28

            #if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)&& !defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-4 14:17
                #ifdef SPE_SETUP
                    #ifdef HANYANG_SETUPMENU//caoh2004-6-18 11:17
                        osd_draw_rect((line*page)/4+21, 10, line/6+1+40, SETUP_BUTTON_HEIGHT+18, SBGCOLOR);//2004-4-20 08:51张宇P bmmm
                    #else
                        osd_draw_rect((line*page)/6+21, 10, line/6+1, SETUP_BUTTON_HEIGHT+18, SBGCOLOR);//2004-4-20 08:51张宇P bmmm
                    #endif
                #else
                    #ifndef DVB_MENU_SETUP_STYLE
                                osd_draw_rect((line*page)/6+10, 10, line/6, SETUP_BUTTON_HEIGHT+10, SBGCOLOR);
                    #else
                                osd_draw_rect((line*dvbpage)/6+10, 10, line/6, SETUP_BUTTON_HEIGHT+10, SBGCOLOR);
                    #endif
                #endif

                #ifndef SPE_SETUP     //fengjl edit 2004-04-30 16:59
                    for (i=0;i<6;i++)
                    {
                        if (p_scan==1)

                          {
                            //#ifndef SPE_SETUP
                            osd_DrawLine((line*i)/6+11, 10, (line*(i+1))/6+10, 10, SWHITECOLOR, 2); // top
                           //#endif

                           printf("----not draw setupline---\n");
                           }
                        else
                            osd_DrawLine((line*i)/6+11, 10, (line*(i+1))/6+10, 10, SWHITECOLOR, 1); // top
                        osd_DrawLine((line*i)/6+11, 10, (line*i)/6+11, SETUP_BUTTON_HEIGHT+21, SWHITECOLOR, 1); // left
                        osd_DrawLine((line*(i+1))/6+8, 10, (line*(i+1))/6+8, SETUP_BUTTON_HEIGHT+20, SBLACKCOLOR, 1); // right
                    }
                #endif     //end #ifndef SPE_SETUP

                //#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
                #if defined(NEXTPAGE_SYS)       //freyman 2004-3-26 0:10
                    if(page==SysNextPage)
                    osd_DrawLine((line*0)/6+12, SETUP_BUTTON_HEIGHT+20, (line*(0+1))/6+8, SETUP_BUTTON_HEIGHT+20, SBGCOLOR, 2);
                    else
                #endif

            #endif//#if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)

            #ifdef SETUP_COLOR_TYPE2
                osd_DrawLine((line*page)/6+12, SETUP_BUTTON_HEIGHT+20, line/6-25/*(line*(page+1))/6+8*/, 1, /*SBGCOLOR*/13, 13);
            #elif defined(SETUP_COLOR_TYPE1)
                printf("==========Delete this line!!");
            #else
                #ifndef DVB_MENU_SETUP_STYLE
                    osd_DrawLine((line*page)/6+12, SETUP_BUTTON_HEIGHT+20, (line*(page+1))/6+8, SETUP_BUTTON_HEIGHT+20, SBGCOLOR, 2);
                #else
                    osd_DrawLine((line*dvbpage)/6+12, SETUP_BUTTON_HEIGHT+20, (line*(dvbpage+1))/6+8, SETUP_BUTTON_HEIGHT+20, SBGCOLOR, 2);
                #endif
            #endif
        }
    } //if (refresh)
    else
    {
        #ifdef  SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28
            //refresh the 5 rects
            osd_draw_rect(0, 0+22+SETUP_BUTTON_HEIGHT+10+SETUP_BUTTON_HEIGHT-2, (SETUP_MAX_WIDTH*16), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)-(22+SETUP_BUTTON_HEIGHT+10+SETUP_BUTTON_HEIGHT-2)-(SETUP_BUTTON_HEIGHT), SBGCOLOR);
            // osd_draw_rect(0, 0, line, 22, SSHEER);
            //osd_draw_rect(0, 22, line, SETUP_BUTTON_HEIGHT+10, SBARCOLOR);
            osd_draw_rect(0, SETUP_BUTTON_HEIGHT+10+10+10+2, line, SETUP_BUTTON_HEIGHT-2, 0);//wangfeng 3-8-27 21:47

            //osd_draw_rect(0, SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-SETUP_BUTTON_HEIGHT, line, SETUP_BUTTON_HEIGHT, SBARCOLOR);
        #elif defined(SETUP_COLOR_TYPE2)
            osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT+20, line+20, SETUP_BUTTON_HEIGHT+1, 0);//3-8-25 2:26张宇P
            osd_draw_rect(20, SETUP_BUTTON_HEIGHT+24+40, (SETUP_MAX_WIDTH*15), 8*SETUP_BUTTON_HEIGHT, SBGCOLOR);

        #else

            osd_draw_rect(20, SETUP_BUTTON_HEIGHT+24, (SETUP_MAX_WIDTH*15), 10*SETUP_BUTTON_HEIGHT-12, SBGCOLOR);
        #endif
    }


    if (!(full_scrn&CUSTM)
        #if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE

            && (!one_key_pass_flag)//no draw ICON. zhaoyanhua add 03-11-7 10:17
        #endif

        #ifdef  KARAOKE_MENU
            &&(KARAOKE_MENU_FLAG==0)//WANGFENG 2003-10-29 18:06
        #endif
        )
    {
//            int icon_y = (p_scan) ? 13 : 7;
#ifdef SETUP_COLOR_TYPE1 //|| defined(SETUP_COLOR_TYPE2)    //wangfeng 2003-08-29 17:28
            osd_DrawIcon(4, 26,0,page);
//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)       //freyman 2004-3-26 0:11
        if (page==SysNextPage)  osd_DrawIcon(4,26,0,0);
#endif
            osd_DrawIcon(16,26,1,page);
            osd_DrawIcon(27,26,2,page);
            osd_DrawIcon(38,26,3,page);
            osd_DrawIcon(50,26,4,page);
            osd_DrawIcon(61,26,5,page);
#else//#ifdef SETUP_COLOR_TYPE1

    #ifdef SETUPMENU_16Mb_NO_ICON
       #ifdef SPE_SETUP
       #ifdef HANYANG_SETUPMENU//caoh2004-6-18 11:17
            osd_DrawSetupIconString(4, 15, "SYS", SBLACKCOLOR, SDEFAULTCOLOR1);
       #else
            osd_DrawSetupIconString(3, 15, "SYS", SBLACKCOLOR, SDEFAULTCOLOR1);
       #endif
       #else//#ifdef SPE_SETUP
            osd_DrawSetupIconString(2, 15, "SYS", S16WHITEFONT, SDEFAULTCOLOR);
        #endif//#ifdef SPE_SETUP
    #elif defined(BBK_SIMPLE_SETUP)                //sunzhh add for bbk_dv911s 2004-4-22 15:04
            osd_DrawIcon(8, 13,0,page);
    #elif defined(QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-2 17:03
            osd_DrawIcon(10, 13,0,page);
    #elif defined(DVB_MENU_TYPE1)             //sunzhh 20050430
       	if(system_state != SYSTEM_TS)
            osd_DrawIcon(4, 13,2,page);
       	else
            osd_DrawIcon(4, 13,0,page);
    #else
            osd_DrawIcon(4, 13,0,page);
    #endif//#ifdef SETUPMENU_16Mb_NO_ICON

    #ifdef SETUP_ON_OPEN_VALID          //dingzhy for yili 12/26/2003 9:34PM

        //#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
        #if defined(NEXTPAGE_SYS)       //freyman 2004-3-26 0:11
            if (page==SysNextPage)  osd_DrawIcon(10,13,0,0);
        #endif

        osd_DrawIcon(23,13,1,page);
        osd_DrawIcon(43,13,2,page);
        osd_DrawIcon(62,13,3,page);
    #else//#ifdef SETUP_ON_OPEN_VALID          //dingzhy for yili 12/26/2003 9:34PM

         //#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
        #if defined(NEXTPAGE_SYS)       //freyman 2004-3-26 0:12
            if (page==SysNextPage)  osd_DrawIcon(4,13,0,0);
        #endif

        #ifdef SETUPMENU_16Mb_NO_ICON
           #ifdef SPE_SETUP      //2004-4-28 19:10  zhangyu-lorenc
              #ifdef HANYANG_SETUPMENU//caoh2004-6-18 11:17
              osd_DrawSetupIconString(12, 15, "LANG", SBLACKCOLOR, SDEFAULTCOLOR1);
              osd_DrawSetupIconString(21, 15, "AUD", SBLACKCOLOR, SDEFAULTCOLOR1);
              #else
            osd_DrawSetupIconString(8, 15, "LANG", SBLACKCOLOR, SDEFAULTCOLOR1);
            osd_DrawSetupIconString(14, 15, "AUD", SBLACKCOLOR, SDEFAULTCOLOR1);
              #endif
           #else//#ifdef SPE_SETUP
            osd_DrawSetupIconString(7, 15, "LANG", S16WHITEFONT, SDEFAULTCOLOR);
            osd_DrawSetupIconString(13, 15, "AUD", S16WHITEFONT, SDEFAULTCOLOR);
           #endif//#ifdef SPE_SETUP
            #ifndef SETUP_DONGLI459
                #ifdef SPE_SETUP  //2004-4-28 19:12 zhangyu-lorenc
                #ifdef HANYANG_SETUPMENU//caoh2004-6-18 11:17
                osd_DrawSetupIconString(29, 15, "VID", SBLACKCOLOR, SDEFAULTCOLOR1);
                #else
                osd_DrawSetupIconString(19, 15, "VID", SBLACKCOLOR, SDEFAULTCOLOR1);
                #endif
                #else//#ifdef SPE_SETUP
                osd_DrawSetupIconString(19, 15, "VID", S16WHITEFONT, SDEFAULTCOLOR);
            	#endif//#ifdef SPE_SETUP
            #endif//#ifndef SETUP_DONGLI459
        //#ifdef SETUPMENU_16Mb_NO_ICON
        #elif defined(BBK_SIMPLE_SETUP)           //sunzhh add for bbk_dv911s 2004-4-22 15:04
                osd_DrawIcon(24,13,1,page);
                osd_DrawIcon(40,13,2,page);
            #ifndef SETUP_DONGLI459
                osd_DrawIcon(56,13,3,page);
            #endif
        #elif defined(QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-2 17:08
                osd_DrawIcon(25,13,1,page);
                osd_DrawIcon(40,13,2,page);
                osd_DrawIcon(55,13,3,page);
        #elif defined(EASTECH_NEW_SETUP_MENU)//liweihua 2004-7-2 17:08
                osd_DrawIcon(23,13,1,page);  // modify by Tom  20040714
                osd_DrawIcon(42,13,2,page);
                osd_DrawIcon(61,13,3,page);
        #elif defined(PULIANG_SETUP_MENU)      //yaowh add 04-12-15
            osd_DrawIcon(17,13,1,page);
            osd_DrawIcon(30,13,2,page);
            osd_DrawIcon(43,13,3,page);
        #elif defined(DVB_MENU_TYPE1)
            if(system_state != SYSTEM_TS)
            {
                osd_DrawIcon(16,13,3,page);
                osd_DrawIcon(27,13,4,page);
                osd_DrawIcon(38,13,5,page);
            }
            else
            {
                osd_DrawIcon(16,13,1,page);
                osd_DrawIcon(27,13,2,page);
                osd_DrawIcon(38,13,5,page);
            }
       #else//#ifdef SETUPMENU_16Mb_NO_ICON
            osd_DrawIcon(16,13,1,page);
            osd_DrawIcon(27,13,2,page);
            #ifndef SETUP_DONGLI459
            osd_DrawIcon(38,13,3,page);
            #endif
     #endif//#ifdef SETUPMENU_16Mb_NO_ICON
    #endif  //#ifdef SETUP_ON_OPEN_VALID end dingzhy

#ifndef NO_DIGIT_VIDEO_MENU
    #ifdef SETUP_DONGLI459
        osd_DrawIcon(38,13,3,page);//SPEAKER PAGE
        osd_DrawIcon(50,13,4,page);//DOBLY PAGE
    #else//#ifndef SETUP_DONGLI459

   #ifdef SETUPMENU_16Mb_NO_ICON
       #ifdef SPE_SETUP  //2004-4-28 19:15 zhangyu-lorenc
         #ifdef HANYANG_SETUPMENU//caoh2004-6-18 11:17
         osd_DrawSetupIconString(24, 15, "", SBLACKCOLOR, SDEFAULTCOLOR1);
         #else
        osd_DrawSetupIconString(24, 15, "SPKR", SBLACKCOLOR, SDEFAULTCOLOR1);
         #endif
       #else//#ifdef SPE_SETUP
        osd_DrawSetupIconString(24, 15, "SPKR", S16WHITEFONT, SDEFAULTCOLOR);
       #endif//#ifdef SPE_SETUP
   #elif !(defined(BBK_SIMPLE_SETUP)||defined(QSI_SETUP_MENU))  //liweihua mod for SQI 2004-6-15//sunzhh add for bbk_dv911s 2004-4-22 15:04
       #ifdef PULIANG_SETUP_MENU  //yaowh add 04-12-15
               osd_DrawIcon(56,13,4,page);
       #elif defined(DVB_MENU_SETUP_STYLE)
           if(system_state != SYSTEM_TS)
               osd_DrawIcon(50,13,4,page);
       #elif defined(DVB_MENU_TYPE1)//sunzhh modify 20050430
           if(system_state != SYSTEM_TS)
               osd_DrawIcon(50,13,6,page);
       #else//#ifdef PULIANG_SETUP_MENU
               osd_DrawIcon(50,13,4,page);
       #endif//#ifdef PULIANG_SETUP_MENU

  #endif//#ifdef SETUPMENU_16Mb_NO_ICON

#ifndef PULIANG_SETUP_MENU //yaowh add 04-12-15
    #ifndef NO_AUDIO_PAGE//liweihua add for syber 2003-12-30 20:40
        #ifdef SETUPMENU_16Mb_NO_ICON
          #ifdef SPE_SETUP       //2004-4-28 19:41zhangyu-lorenc
             #ifdef HANYANG_SETUPMENU//caoh2004-6-18 11:17
            	osd_DrawSetupIconString(30, 15, "", SBLACKCOLOR, SDEFAULTCOLOR1);
             #else
            	osd_DrawSetupIconString(30, 15, "DGT", SBLACKCOLOR, SDEFAULTCOLOR1);
            #endif
          #else//#ifdef SPE_SETUP
            osd_DrawSetupIconString(30, 15, "DGT", S16WHITEFONT, SDEFAULTCOLOR);
          #endif//#ifdef SPE_SETUP
        #elif !(defined(BBK_SIMPLE_SETUP)||defined(QSI_SETUP_MENU))  //liweihua mod for SQI 2004-6-15//sunzhh add for bbk_dv911s 2004-4-22 15:04
                //SETUPMENU_16Mb_NO_ICON
         #ifdef DVB_MENU_SETUP_STYLE
             if(system_state != SYSTEM_TS)
                osd_DrawIcon(61,13,5,page);
         #elif defined(DVB_MENU_TYPE1)//sunzhh modify 20050430
             if(system_state != SYSTEM_TS)
                osd_DrawIcon(61,13,7,page);
         #else//#ifdef DVB_MENU_SETUP_STYLE
            osd_DrawIcon(61,13,5,page);
         #endif//#ifdef DVB_MENU_SETUP_STYLE

        #endif//SETUPMENU_16Mb_NO_ICON
    #endif//#ifndef NO_AUDIO_PAGE/
#endif//#ifndef PULIANG_SETUP_MENU

    #endif//#ifndef SETUP_DONGLI459
#endif//NO_DIGIT_VIDEO_MENU
#endif//SETUP_COLOR_TYPE1
    }

    if (setupLevel == 0)
    {
        BYTE    iItemType;
        #ifndef SPE_SETUP
        show_main_title(setup_MainP[page][0]);
        #endif
        //draw item strings in sub menu
        for (i=index_y_start; i<setupItemNum[1]; i++)
        {
            if ( (i-index_y_start+1) > (SETUP_MAX_LINE-3) ) break;

            iItemType=setup_item[page][i][0];
            if (iItemType == SET_SPACE) continue;
            if (iItemType == SET_NE) break;

            id = setup_item[page][i][1];

            #ifdef BBK_NEW_SETUP    //fengjl edit 4-1-29 13:02
            #if defined(BBK_DSS_555_DVD)||defined(BBK_DV911S)
            if (id==STR_OS_RETURN_MAIN_SETUP)
                id=STR_OS_EXIT_MENU;
            #endif
            #else
            if (id==STR_OS_RETURN_MAIN_SETUP)    // no main page, so this item changes to exit_setup_menu
                id=STR_OS_EXIT_MENU;
            #endif
		#if !defined(DVB_MENU_SETUP_STYLE)&&!defined(DVB_MENU_TYPE1)
            str = _OsdMessegeFont1[osd_font_mode][id];
        #else
        	str = SetDvbItemString(id);

        #endif //DVB_MENU_SETUP_STYLE

            bgColor = SBGCOLOR;
            upDown = 0;

            /*#ifdef DVB_MENU_SETUP_STYLE //Maoyong 2004-12-22 11:13
            if(IsValidDvbMenuItem(i))
                fontColor = SGRAYCOLOR;
            else
            #endif*/
            fontColor = SFONTCOLOR;

            #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39
            osd_draw_setup_button(SETUP_MENU_XSTART, i-index_y_start+SETUP_MENU_YSTART+1, SETUP_SUB_XSTART-SETUP_MENU_XSTART-1, bgColor, upDown);
            #endif
            osd_DrawString(SETUP_MENU_XSTART+1, i-index_y_start+SETUP_MENU_YSTART+1, str, fontColor, bgColor);
            #ifdef SHOW_SETUPMENU_SETUP     // linrc add 2004-5-1 18:30
            sel=setup_sel[page][i];
            id = setup_item[page][i][sel];
            str = setup_SetItemString();
            osd_DrawString(SETUP_SUB_XSTART+1, i+3, str, S16WHITEFONT, 1);
            #endif //end SHOW_SETUPMENU_SETUP
        } //end of for each item
        // highlight : draw a frame to identify which tab is enable
    #if !defined(SETUP_COLOR_TYPE2) && !defined(SETUP_COLOR_TYPE1)&& !defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-2 17:38
        SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffff);
         #endif
    #if !defined(SETUP_COLOR_TYPE1)&&!defined(SETUP_COLOR_TYPE2)&& !defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-5 10:04//#ifndef   SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28
//#ifndef   SETUP_COLOR_TYPE1
#ifndef DVB_MENU_SETUP_STYLE
        setup_Showredframe(page);
#else
        setup_Showredframe(dvbpage);
#endif
        #endif
    } else
    { //second(or third)-level page menu
        BYTE    iItemType;

        //find max items in this page
        for (i=0; i<MAX_PAGE_ITEM; i++)
        {
            iItemType=setup_item[page][i][0];
            if (iItemType == SET_SPACE) continue;
            if (iItemType == SET_NE) break;
            #ifdef SHOW_SETUPMENU_SETUP     //linrc modify 2004-5-9 20:02
            if(index_y!=6)          //2004-6-2 01:56?宇P
            {
                #ifdef PULIANG_SETUP_MENU   //yaowh add 04-12-15
                if(show_menu_setup_flag!=1)
                #endif
            show_setupmenu();
            }
            #endif //end SHOW_SETUPMENU_SETUP
        }
        #ifdef SHOW_SETUPMENU_SETUP     //linrc add 2004-5-5 16:05
        for (i=0; i<MAX_PAGE_ITEM; i++)
        {
            iItemType=setup_item[page][i][0];
            if (iItemType == SET_SPACE) continue;
            if (iItemType == SET_NE) break;
            sel=setup_sel[page][i];
            id = setup_item[page][i][sel];
            if((id==STR_OS_P_SCAN_YUV||id==STR_OS_YCbCr||id==STR_OS_RESTORE_SETUP)&&(index_y==2||index_y==6))
              osd_draw_rect(300, 75, 250, 350, 1);
        }
        #endif //SHOW_SETUPMENU_SETUP
        setupItemNum[1] = i;

        //draw menu title
        if (full_scrn&CUSTM)
#ifdef BBK_NEW_CUSTM     //fengjl add 2004-03-27 10:58
{
    BYTE    buf[15];

    psprintf(buf, "%s", VERSION_STRING1);
    osd_DrawString(SETUP_MENU_XSTART+1, SETUP_MENU_YSTART, buf, SFONTCOLOR, SBGCOLOR);
}
//move to ShowCUSTMMsg //20040708//JSLIN
/*
#elif defined(SHOW_SYSTEM_CLOCK)//nono 4-4-6 0:30
{
    BYTE    buf[5];
    extern int get_sysclk;
    psprintf(buf, "SC:%d", (get_sysclk*675/100));
    osd_DrawString(SETUP_MENU_XSTART+1, SETUP_MENU_YSTART, buf, SFONTCOLOR, SBGCOLOR);
}
*/
#else
            //show_main_title(STR_OS_MENU);
{}
#endif
//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)       //freyman 2004-3-26 0:12
        else if (page==SysNextPage)
    #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP            //gerry for gbm,2004-3-12 13:12
        {
            if(IsOSDChinese())
            show_main_title(setup_item[0][6][1]);
            else
            show_main_title(STR_OS_PREV_PAGE);
        }
    #else//NEXT_PAGE_SHOW_ADVANCED_SETUP
            show_main_title(setup_MainP[0][0]);
    #endif//NEXT_PAGE_SHOW_ADVANCED_SETUP
#endif

#ifdef  KARAOKE_MENU
        else if((page==AUDPAGE)&&(KARAOKE_MENU_FLAG))
            show_main_title(STR_OS_KARAOKE_SETUP);
#endif
        else
        #ifdef SETUP_ON_OPEN_VALID      //dingzhy for yili 12/26/2003 9:37PM
            #ifdef NO_DIGIT_VIDEO_MENU
                 if(page==3)
            show_main_title(setup_MainP[4][0]);
            else
            show_main_title(setup_MainP[page][0]);
            #endif
        #else
            show_main_title(setup_MainP[page][0]);
        #endif


        //draw item strings in sub menu
        for (i=index_y_start; i<setupItemNum[1]; i++)
        {
            if ( (i-index_y_start+1) > (SETUP_MAX_LINE-3) ) break;

            iItemType=setup_item[page][i][0];
            if (iItemType == SET_SPACE) continue;
            if (iItemType == SET_NE) break;

            id = setup_item[page][i][1];
#ifdef ONLY_DOWNMIX_IN_SPEAKER_PAGE//liweihua add 2004-1-2 15:05
            if(page == MULTISPKPAGE)
            {
                if((i>0) && (id!=STR_OS_RETURN_MAIN_SETUP))
                    continue;
            }
#endif
            /*
    #ifndef  BBK_NEW_SETUP//zhaoyanhua add 2003-11-18 17:14
            if (id==STR_OS_RETURN_MAIN_SETUP)  // no main page, so this item changes to exit_setup_menu
                id=STR_OS_EXIT_MENU;
            #endif
            */

            #ifdef BBK_NEW_SETUP    //fengjl edit 4-1-29 13:02
            #if defined(BBK_DSS_555_DVD)||defined(BBK_DV911S)
            if (id==STR_OS_RETURN_MAIN_SETUP)
                id=STR_OS_EXIT_MENU;
            #endif
            #else
            if (id==STR_OS_RETURN_MAIN_SETUP)    // no main page, so this item changes to exit_setup_menu
                id=STR_OS_EXIT_MENU;
            #endif

		#if !defined(DVB_MENU_SETUP_STYLE)&&!defined(DVB_MENU_TYPE1)  //sunzhh 20050430
            str = _OsdMessegeFont1[osd_font_mode][id];
        #else
        	str = SetDvbItemString(id);

        #endif //DVB_MENU_SETUP_STYLE

            if ( (index_y+index_y_start) == i)
            {
                #ifdef SETUP_COLOR_TYPE1
                if (setupLevel)
                #else
                if (setupLevel==1)
                #endif
                {
                     fontColor = SANTIFONTCOLOR;
                } else
                {
                     fontColor = SFONTCOLOR;
                }
                bgColor = SANTIBGCOLOR;
                upDown = 1;
            }else
            {
                bgColor = SBGCOLOR;
                upDown = 0;

    #if !defined(SETUP_ALL_VALID)||defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE)||defined(SUPPORT_APOGEE_AMP)     //xulf 2004-01-07
                //special case////nonotest 2003-9-5 17:44
                if ( (page==MULTISPKPAGE) && (SETUP_SPK_DOWNMIX!=AC3DOWNMIXOFF) &&
                            ( (i>=SPKSTART) && (i<=SPKEND) ))
                {
                    fontColor = SGRAYCOLOR;
                } else
#endif//    #if !defined(SETUP_ALL_VALID)||defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE)

    #ifdef PROLOGICII_3D_MUTEX//nono 4-2-12 0:58

    if ((page==AUDPAGE) && is_EQ_SOUND_set()&&(i==PROLOGIC_II))
    //if (i==PROLOGIC_II)
    {
          fontColor = SGRAYCOLOR;
    }else

    #endif//PROLOGICII_3D_MUTEX

    #ifdef PROLOGIC_ON_51CH
                 if ((page==AUDPAGE)&&(KARAOKE_MENU_FLAG==0)
                    && !setup_IsSpkDownmixOff()&&(i==1))
                {
                    fontColor = SGRAYCOLOR;
                } else
    #endif

        #ifndef SETUP_ALL_VALID
                if ( (page==AUDPAGE) &&
                            (
                            ((SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF) &&
                            ( coding_mode_now&(AUDIF_CODING_MODE_AC3|
                            AUDIF_CODING_MODE_DTS|
                            AUDIF_CODING_MODE_DTSCD)
                            )
                            )
                            ||(coding_mode_now==AUDIF_CODING_MODE_LPCM)//terry,0512,currently ,we are not surport LPCM key shift
                            ) &&
                            (i==(KEYITEM) )
                            )
                {
                        #ifdef SETUP_COLOR_TYPE2
                                   fontColor = SGRAYCOLOR;
                        #elif defined(SETUP_COLOR_TYPE1)
                            fontColor = SGRAYCOLOR;
                           #else
                    //wanghaoying 2003-11-26 20:05 changed
                    //fontColor = SFONTCOLOR;
                    fontColor = SGRAYCOLOR;
                           #endif
                }
                else if ( (page==AUDPAGE) &&
                            (SETUP_SPDIF==SPDIFBITSTREAM) &&
                            ( ( coding_mode_now&(AUDIF_CODING_MODE_AC3|
                            AUDIF_CODING_MODE_DTS|
                            //AUDIF_CODING_MODE_PCM|   //DTSCD-BITSTREAM MODE, Jeff 20020719
                            AUDIF_CODING_MODE_DTSCD)
                            )||(cd_subtype==CD_DTS) )&&      //NONO 2-7-25 17:26
                            ( (i>=VOLCTRLSTART) && (i<=VOLCTRLEND) )
                            )
                {
                    //fontColor = SGRAYCOLOR;
#ifdef SETUP_COLOR_TYPE2
fontColor = SGRAYCOLOR;
#elif defined(SETUP_COLOR_TYPE1)
fontColor = SGRAYCOLOR;
#else
                    //wanghaoying 2003-11-26 20:05 changed
                    //fontColor = SFONTCOLOR;
                    fontColor = SGRAYCOLOR;
#endif
                #ifndef NO_AC3_DYNAMIC_RANGE
                } else if ( (page==AC3DIGITALPAGE) && //Jeff 20020621
                            (i==AC3DYNAMICITEM1) &&
                            ( (SETUP_AC3DIGITAL_OUTMODE!=AC3DYNAMICITEM2)
//                            ||(SETUP_SPK_DOWNMIX!=AC3DOWNMIXOFF)
                            )
                            )
                {
                    fontColor = SFONTCOLOR;
//                  fontColor = SGRAYCOLOR;
                #endif //NO_AC3_DYNAMIC_RANGE
                } else
            #endif //SETUP_ALL_VALID
                {
                    fontColor = SFONTCOLOR;
                }
                }
                if (!refresh)
                {
                    bgColor=SBGCOLOR;
                    upDown=0;
                    //marked by wangfeng 2003-09-01 19:42
                    if (i==index_y_start)
                    fontColor=SFONTCOLOR;
                }
            #ifdef KARAOKE_MENU //wangfeng 2003-10-30 10:19
            if((page==AUDPAGE)&&(KARAOKE_MENU_FLAG)&&((i<2)||(i>5)))//((i<1)||(i>4)))
            {
                fontColor = SBGCOLOR;

            }
            //wangfeng 2003-11-11 14:06
            else if((page==AUDPAGE)&&(KARAOKE_MENU_FLAG==0)&&((i>=2)&&(i<=5)))
            {
                fontColor = SBGCOLOR;
            }
            else
            #endif

            #ifdef DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF //zxb 2005-5-8 13:06
                if((id==STR_OS_ECHO || id==STR_OS_MIC_VOL) &&
                (setup_item[page][MIC_SETUP_ITEM_INDEX][(setup_sel[page][MIC_SETUP_ITEM_INDEX])] == STR_OS_OFF))
                {
                	fontColor = SGRAYCOLOR;
                }
                else
            #endif

            /*#ifdef DVB_MENU_SETUP_STYLE //Maoyong 2004-12-21 20:41
            if(IsValidDvbMenuItem(i))
            {
                fontColor = SGRAYCOLOR;
            }
            #endif*/

            #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39
#ifdef EASTECH_NEW_SETUP_MENU
            if(fontColor==1)  //add by TOM
                    bgColor=5;
#endif
                osd_draw_setup_button(SETUP_MENU_XSTART, i-index_y_start+SETUP_MENU_YSTART+1, SETUP_SUB_XSTART-SETUP_MENU_XSTART-1, bgColor, upDown);
            #endif
                osd_DrawString(SETUP_MENU_XSTART+1, i-index_y_start+SETUP_MENU_YSTART+1, str, fontColor, bgColor);
            #ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-7 19:26
                if((page == VIDEOPAGE) &&(setup_item[page][i][0] == SET_SCALE))//not draw "EXIT" item,
                {
                    setup_VideoItemValue(i,SFONTCOLOR,SBGCOLOR );//show value with HL color.
                }
            #endif//VIDEO_SETUP_NEW_GUI
            } //end of for each item

            //some special system information shown in selection area
            if (full_scrn&CUSTM)
            {
                #if 0
                BYTE    buf[40];
                BYTE    *pVersion;
                extern const UINT8 ServoVersion[];

                pVersion = (BYTE *)(ROM_BASE_UNCACHED);

                //show ROM code checksum
                buf[0]= '[';
                for (i=0x40; i<0x44; i++)
                {
                    BYTE    ch[3];
                    psprintf(ch,"%02x",*(pVersion+i));
                    buf[2*i-126]=ch[1];
                    buf[2*i-127]=ch[0];
                }

                buf[9]= ']';
                buf[10]= 0;
                osd_DrawString(SETUP_SUB_XSTART+6, SETUP_MENU_YSTART+2, buf, SFONTCOLOR, SBGCOLOR);

                //ServoVersion[16]=0; can't write to const data
                osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART, ServoVersion, SFONTCOLOR, SBGCOLOR);
                //show some "codes" strings
                for (i=0x50; i<0x58; i++) { //Extend version string length to 8 Bytes, Jeff 20020715
                    buf[i-0x50] = *(pVersion+i);
                }

                buf[8]= 0; //Extend version string length to 8 Bytes, Jeff 20020715
                osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+1, buf, SFONTCOLOR, SBGCOLOR);
                //add build version, Jeff 20021008
                psprintf(buf, "%s", VERSION_STRING);
                osd_DrawString(SETUP_SUB_XSTART+8, SETUP_MENU_YSTART+1, buf, SFONTCOLOR, SBGCOLOR);
                //psprintf(buf, "%c SUM:", regs0->stamp+'A');
                psprintf(buf, "%02x%03x", (regs0->stamp & 0xff),get_iop_b_status()); //2004/11/30 ycwen
                osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+2, buf, SFONTCOLOR, SBGCOLOR);
                #endif

                ShowCUSTMMsg();

            #ifdef SUPER_DEFAULT_OSD_LANG       //freyman add 2004-2-11 9:11
            id = setup_item[page][index_y][1];
            if(id==STR_OS_OSD)
                index_y = CUSTMOSDITEM;
            else
            #endif

#ifdef CUSTM_MENU_REVISE
	index_y = REGION_REMOVE -1;
#else
        index_y = 2;
#endif
            }

            if (refresh)
            {
                draw_3rd_menu();
            }
            return;

            //draw ">" between sub-mean and it's corresponding selection area
        //#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
        #if defined(NEXTPAGE_SYS)       //freyman 2004-3-26 0:13
            if((id!=STR_OS_NEXT_PAGE)&&(id!=STR_OS_PREV_PAGE))
            #endif

            #ifdef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 17:12
            osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART, Ch_arrorR, SANTIFONTCOLOR, SBGCOLOR);
            #else
            osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART, Ch_arrorR, SFONTCOLOR, SBGCOLOR);
            #endif// QSI_SETUP_MENU_DESIGN
            //show first selection menu of third-level menu
#ifdef  Ti3001_OSD_UI_2
            if(page!=5&&page!=6)
            {
                for (i=2; i<MAX_ITEM_SEL; i++)
                {
                    //get select item
                    sel = setup_sel[page][index_y+index_y_start];

                    id = setup_item[page][index_y+index_y_start][i];
                    if (id==0) break;

                    str = setup_SetItemString();
                    if (sel == i) {
                        fontColor = SFONTCOLOR;
                        bgColor = SANTIBGCOLOR;
                        upDown = 1;
                    } else {
                        fontColor = SFONTCOLOR;
                        bgColor = SBGCOLOR;
                        upDown = 0;
                    }
                    //special item(PASSWORD), page-0, item-4
                    if (setup_item[page][index_y+index_y_start][0]==SET_NM) {
                        if (UserSet.parental_ststus==C_LOCK) {
                            setup_sel[page][index_y+index_y_start] = MIN_ITEM_SEL;
                            str = _OsdMessegeFont1[osd_font_mode][STR_OS_LOCK];
                        } else {
                            setup_sel[page][index_y+index_y_start] = MIN_ITEM_SEL + 1;
                            str = _OsdMessegeFont1[osd_font_mode][STR_OS_UNLOCK];
                        }
                        #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39
                        osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart), SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 1);
                        #endif
                        osd_DrawString(SETUP_SUB_XSTART+1, (submenuStart), str, SANTIFONTCOLOR, SANTIBGCOLOR);
                    } else {
                        #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39
                        osd_draw_setup_button(SETUP_SUB_XSTART, (i-2+index_y)+SETUP_MENU_YSTART, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, bgColor, upDown);
                        #endif
                        osd_DrawString(SETUP_SUB_XSTART+1, (i-2+index_y)+SETUP_MENU_YSTART, str, fontColor, bgColor);
                    }
                }
                setupItemNum[2] = i-2;
            }
            else
            {
                for (i=1; i<MAX_ITEM_SEL; i++)
                {


                    //get select item
                    sel = setup_sel[page][index_y+index_y_start];

                    id = setup_item[page][index_y+index_y_start][i];
                    if (id==0) break;

                    str = setup_SetItemString();

                    if (sel == i)
                    {
                        fontColor = SFONTCOLOR;
                        bgColor = SANTIBGCOLOR;
                        //bgColor = SBGCOLOR;
                        upDown = 1;
                    } else
                    {
                        fontColor = SFONTCOLOR;
                        bgColor = SBGCOLOR;
                        upDown = 0;
                    }
                    if (setup_item[page][index_y+index_y_start][0]==SET_SCALE)
                    {
                        setup_PrepareScaleItem(id,upDown);
                    }
                }
                setupItemNum[2] = i-2;
            }
#else
            for (i=2; i<MAX_ITEM_SEL; i++)
            {
                //get select item
                       #if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE
                if(one_key_pass_flag)
                {
                    sel = GetOneKeyPageSel(index_y);
                    printf("+++++++++++++ 111111111sel = %d,index_y = %d--\n");
                }
                else
                sel = setup_sel[page][index_y+index_y_start];
            #else
                sel = setup_sel[page][index_y+index_y_start];
            #endif
                id = setup_item[page][index_y+index_y_start][i];
                if (id==0) break;

                str = setup_SetItemString();
                if (sel == i)
                {
                    fontColor = SFONTCOLOR;
                    bgColor = SANTIBGCOLOR;
                    upDown = 1;
                }
                else
                {
                    fontColor = SFONTCOLOR;
                    bgColor = SBGCOLOR;
                    upDown = 0;
                }
                //special item(PASSWORD), page-0, item-4
                if (setup_item[page][index_y+index_y_start][0]==SET_NM)
                {
                    if (UserSet.parental_ststus==C_LOCK)
                    {
                        setup_sel[page][index_y+index_y_start] = MIN_ITEM_SEL;
                        str = _OsdMessegeFont1[osd_font_mode][STR_OS_LOCK];
                    } else
                    {
                        setup_sel[page][index_y+index_y_start] = MIN_ITEM_SEL + 1;
                        str = _OsdMessegeFont1[osd_font_mode][STR_OS_UNLOCK];
                    }
                    #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39
                    osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart), SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 1);
                    #endif
                    osd_DrawString(SETUP_SUB_XSTART+1, (submenuStart), str, SANTIFONTCOLOR, SANTIBGCOLOR);
                }
                else
                {
                    #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39
                    osd_draw_setup_button(SETUP_SUB_XSTART, (i-2+index_y)+SETUP_MENU_YSTART, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, bgColor, upDown);
                    #endif
                    osd_DrawString(SETUP_SUB_XSTART+1, (i-2+index_y)+SETUP_MENU_YSTART, str, fontColor, bgColor);
                }
            }

            setupItemNum[2] = i-2;
#endif
    }
    #ifdef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-2 18:42
    osd_DrawLine(0, 86, 280*2, 86, 12, 1);
    #endif
}

#endif  // end of DVD_SETUP_REENG
//=============================================

#ifdef QSI_PLATFORM //qsi: added by johnson 20040712
extern BYTE is_show_full_qsi_version(void);
#endif



//=============================================
//for DVD_SETUP_REENG   //added by JS   //20040728
#ifndef DVD_SETUP_REENG
/*
** FUNC: to rewrite the infomation in CUSM when Rating_8.
**
**  zhaoyanhua
**  Date: 3-7-25 17:55
*/
void ShowCUSTMMsg(void)
{
    BYTE    buf[40];
    BYTE    *pVersion;
#ifdef DVD_SERVO
    extern const UINT8 ServoVersion[];
#endif
    extern const UINT8 KernelVersion[];     // moved to libkern.a, leochen 2004/4/19 09:43と
    int i=0;

    pVersion = (BYTE *)(ROM_BASE_UNCACHED);

    //show ROM code checksum
    buf[0]= '[';
    for (i=0x40; i<0x44; i++)
    {
        BYTE    ch[3];
        psprintf(ch,"%02x",*(pVersion+i));
        buf[2*i-126]=ch[1];
        buf[2*i-127]=ch[0];
    }

    buf[9]= ']';
    buf[10]= 0;

#ifdef  SETUP_COLOR_TYPE2
    #ifdef OP_CUST_UI//libig 2005-5-9 13:55
    printf("use showcustmmesg\n");
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+2, buf,/* SFONTCOLOR*/7, SBGCOLOR);
    #else//#ifdef OP_CUST_UI//libig 2005-5-9 13:55
    printf("use showcustmmesg\n");
    osd_DrawString(SETUP_SUB_XSTART+6, SETUP_MENU_YSTART+2, buf,/* SFONTCOLOR*/7, SBGCOLOR);
	#endif//#ifdef OP_CUST_UI//libig 2005-5-9 13:55
#else//#ifdef  SETUP_COLOR_TYPE2
    osd_DrawString(SETUP_SUB_XSTART+6, SETUP_MENU_YSTART+2, buf, SFONTCOLOR, SBGCOLOR);
#endif//#ifdef  SETUP_COLOR_TYPE2

#ifdef DVD_SERVO
    //ServoVersion[16]=0; can't write to const data
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART, ServoVersion, SFONTCOLOR, SBGCOLOR);
#endif
    //Maoyong 2004.04.16, marked
    //show some "codes" strings
    //for (i=0x50; i<0x58; i++) { //Extend version string length to 8 Bytes, Jeff 20020715
    //  buf[i-0x50] = *(pVersion+i);
    //}
#ifdef OP_CUST_UI
	buf[8]= 0;
    psprintf(buf, "%s", MPEG_UI_VERSION);
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+1, buf, SFONTCOLOR, SBGCOLOR);
    osd_DrawString(SETUP_SUB_XSTART+4, SETUP_MENU_YSTART+1, KernelVersion, SFONTCOLOR, SBGCOLOR);
    psprintf(buf, "%s", VERSION_STRING);
    osd_DrawString(SETUP_SUB_XSTART+8, SETUP_MENU_YSTART+1, buf, SFONTCOLOR, SBGCOLOR);
    psprintf(buf, "%s", UPDATE_DATE);
    osd_DrawString(SETUP_MENU_XSTART+1, SETUP_MENU_YSTART-2, buf, SFONTCOLOR, SBGCOLOR);
    psprintf(buf, "%s", UPDATE_WEEK);

    psprintf(buf, "%s", SDRAM_SIZE);
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART-2, buf, SFONTCOLOR, SBGCOLOR);
    psprintf(buf, "%s", SDRAM_BUS);
    osd_DrawString(SETUP_SUB_XSTART+8, SETUP_MENU_YSTART-2, buf, SFONTCOLOR, SBGCOLOR);

    extern int get_sysclk;
    psprintf(buf, "SC:%d", (get_sysclk*675/100));
    osd_DrawString(SETUP_MENU_XSTART+1, SETUP_MENU_YSTART, buf, SFONTCOLOR, SBGCOLOR);
    psprintf(buf, "DIVX ID");
    osd_DrawString(SETUP_MENU_XSTART+1, SETUP_MENU_YSTART+6, buf, SFONTCOLOR, SBGCOLOR);
    psprintf(buf, "05-02-22");
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+6, buf, SFONTCOLOR, SBGCOLOR);
#else//#ifdef OP_CUST_UI
    buf[8]= 0; //Extend version string length to 8 Bytes, Jeff 20020715
    //osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+1, buf, SFONTCOLOR, SBGCOLOR);
    psprintf(buf, "%s", MPEG_UI_VERSION);
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+1, buf, SFONTCOLOR, SBGCOLOR);
    //osd_DrawString(SETUP_SUB_XSTART+5, SETUP_MENU_YSTART+1, KernelVersion, SFONTCOLOR, SBGCOLOR);
    osd_DrawString(SETUP_SUB_XSTART+4, SETUP_MENU_YSTART+1, KernelVersion, SFONTCOLOR, SBGCOLOR);
    //add build version, Jeff 20021008
    psprintf(buf, "%s", VERSION_STRING);
    osd_DrawString(SETUP_SUB_XSTART+8, SETUP_MENU_YSTART+1, buf, SFONTCOLOR, SBGCOLOR);
    //psprintf(buf, "%c SUM:", (regs0->stamp&0x7f)+'A');//4-8-26 16:06
    psprintf(buf, "%02x%04x", (regs0->stamp & 0xff),get_iop_b_status()); //2004/11/30 ycwen
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+2, buf, SFONTCOLOR, SBGCOLOR);

#ifdef CUSTM_MENU_REVISE
    const char *str;
    id = setup_item[6][2][REGION_NUM + 2]; //WSLEE remove region for customer menu 20050526 PM2:00
    str = _OsdMessegeFont1[osd_font_mode][id];
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+3, str, SFONTCOLOR, SBGCOLOR);
#endif

// show SDRAM, System clock, and update information
//added by JSLin    //20040709
    //show update date and week
    psprintf(buf, "%s", UPDATE_DATE);
    osd_DrawString(SETUP_MENU_XSTART+1, SETUP_MENU_YSTART-2, buf, SFONTCOLOR, SBGCOLOR);
    psprintf(buf, "%s", UPDATE_WEEK);
    osd_DrawString(SETUP_MENU_XSTART+8+1+1, SETUP_MENU_YSTART-2, buf, SFONTCOLOR, SBGCOLOR);

    //show SDRAM information
    psprintf(buf, "%s", SDRAM_SIZE);
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART-2, buf, SFONTCOLOR, SBGCOLOR);
    psprintf(buf, "%s", SDRAM_BUS);
    osd_DrawString(SETUP_SUB_XSTART+8, SETUP_MENU_YSTART-2, buf, SFONTCOLOR, SBGCOLOR);
#endif//#ifdef OP_CUST_UI
#ifdef DVB1000_NON_OS
	psprintf(buf, "%s", DVB_TUNER_LABEL);
    osd_DrawString(SETUP_MENU_XSTART+1, SETUP_MENU_YSTART, buf, SFONTCOLOR, SBGCOLOR);
#else
    //show system clock
    extern int get_sysclk;
    psprintf(buf, "SC:%d", (get_sysclk*675/100));
    osd_DrawString(SETUP_MENU_XSTART+1, SETUP_MENU_YSTART, buf, SFONTCOLOR, SBGCOLOR);
#endif //#ifdef DVB1000_NON_OS

//==========================================================================

#ifdef QSI_PLATFORM //qsi: merge by johnson 20040712
    psprintf(buf,"QSI FIRMWARE VER: %s",QSI_MASTER_VER);
    if(is_show_full_qsi_version())
    {
        BYTE len;
        len=strlen(buf);
        //buf[(len-QSI_VER_MASK_LEN)]='\0';
        psprintf(&buf[len],"%s",QSI_SLAVE_VER);
    }
    osd_DrawString(3, SETUP_MENU_YSTART-1, buf, SFONTCOLOR, SBGCOLOR);
#endif


}
#endif  // end of DVD_SETUP_REENG
//=============================================


#ifdef SUPPORT_FUNCTION_MENU
void show_FW_MCU_servoV(void)
{
    BYTE    buf[20];

#ifdef DVD_SERVO
    extern const UINT8 ServoVersion[];
#endif
    extern const UINT8 KernelVersion[];     // moved to libkern.a, leochen 2004/4/19 09:43と

    osd_draw_setup_button(SETUP_SUB_XSTART,submenuStart,SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 0);
    osd_draw_setup_button(SETUP_SUB_XSTART,submenuStart+1,SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 0);
    osd_draw_setup_button(SETUP_SUB_XSTART,submenuStart+2,SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 0);

    //show F/W version
    buf[8]= 0; //Extend version string length to 8 Bytes, Jeff 20020715

    psprintf(buf, "%s", MPEG_UI_VERSION);
    osd_DrawString(SETUP_SUB_XSTART, submenuStart, buf, SFONTCOLOR, SBGCOLOR);

    osd_DrawString(SETUP_SUB_XSTART+4, submenuStart, KernelVersion, SFONTCOLOR, SBGCOLOR);
    //add build version, Jeff 20021008
    psprintf(buf, "%s", VERSION_STRING);
    osd_DrawString(SETUP_SUB_XSTART+8, submenuStart, buf, SFONTCOLOR, SBGCOLOR);
    #ifdef SUPPORT_SPI
    //show MCU version
    osd_DrawString(SETUP_SUB_XSTART, submenuStart+1, mcu_version, SFONTCOLOR, SBGCOLOR);
    #endif
    //show servo version
#ifdef DVD_SERVO
    osd_DrawString(SETUP_SUB_XSTART, submenuStart+2, ServoVersion, SFONTCOLOR, SBGCOLOR);
#endif

}
#endif //end #ifdef SUPPORT_FUNCTION_MENU

/*move ExitSetupPage() to the below file .2004-11-17 9:59*/
#include "setup_tab_ui1_exit.c"
#if 0//ndef SUPPORT_RECEIVER
#ifdef SUPPORT_TESTSPK //jiangxl 2005-5-24 10:01
#include ".//TestSpk.c"
#endif
#endif//#ifdef SUPPORT_RECEIVER


