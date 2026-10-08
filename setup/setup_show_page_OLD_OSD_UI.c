/***************************************************************
*  setup_show_page.c
*  include  in setup_tab_ui1.c   when defined DVD_SETUP_REENG
* 
* Creator:  JSLin 
* Date:         2004/07/28
*
* Description : 
*           setup menu precentation engine, 
*           1. transform content into GUI   
*
****************************************************************/


void setup_ShowPage(void);
void setup_ShowPageL1(void);
void setup_ShowPageL2(void);
void setup_ShowPageL3(void);
void setup_ExitPage(void);
void setup_ShowPageCUSTM(void);
void setup_ShowCUSTMMsg(void);

extern  unsigned int get_iop_b_status();


void setup_Clear_CUSTM_L3(void){  //helm for REGION CODE display 050627
	
#ifdef CUSTM_MENU_REVISE
        osd_draw_rect((SETUP_SUB_XSTART-1)*16,
                        (SETUP_MENU_YSTART+3)*SETUP_BUTTON_HEIGHT+31,
                        (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
                        (SETUP_MAX_LINE-SETUP_MENU_YSTART-4)*SETUP_BUTTON_HEIGHT,
                        setupBGcolorCUSTM);
#else
        osd_draw_rect((SETUP_SUB_XSTART-1)*16,
                        (SETUP_MENU_YSTART+2)*SETUP_BUTTON_HEIGHT+31,
                        (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
                        (SETUP_MAX_LINE-SETUP_MENU_YSTART-3)*SETUP_BUTTON_HEIGHT,
                        setupBGcolorCUSTM);
#endif
}

#ifdef DRM_CODE //helm for showing DRM CODE 050622
extern char buf_save_drm_code[20]; //helm 050622
extern void Gen_RegCode(void);
#ifndef SHOW_DIVX_WEB_INIT_STR //qinhua ,2005-10-10 14:18
char *show_register_code_line1 = "REGISTRATION"; //helm 050622
char *show_register_code_line2 = "    CODE"; //kevinmonkey 051024 change string to "REGISTRATION \n CODE"
char *show_DIVX_Web="VISIT WEB SITE: WWW.DIVX.COM/VOD";
#endif 
char Clean_DRM_Web=0;

void setup_Clean_DIVX_Web(void){  //helm for clean DIVX web site, 050825
//osd_draw_rect(10, 300, (SETUP_MAX_WIDTH*16)-28, (2*SETUP_BUTTON_HEIGHT)+10, setupBGcolorL2); 
//liumzh modify, 2005-12-19
osd_draw_rect(10, (SETUP_MENU_YSTART+8)*SETUP_BUTTON_HEIGHT, 
		(SETUP_MAX_WIDTH*16)-28, (SETUP_BUTTON_HEIGHT), setupBGcolorL2);
}

#ifdef    SUPPORT_OTHER_LANGUAGE_STRING
extern    const char *const osd_other_str[N_OSD_LANGS][STRINE_NUM];
#endif //end=> #ifdef    SUPPORT_OTHER_LANGUAGE_STRING


void setup_Show_DRM_CODE(BYTE xStart_Str, BYTE yStart_Str)
{
	UINT32  xStart, yStart;
	UINT8  yDelta=0;
	UINT8    xWidth;
	
	Gen_RegCode(); 
	
#ifdef SHOW_DIVX_WEB_INIT_STR //qinhua ,2005-10-10 14:18
	//show "registration \n code"
	const char *str1;
	str1 = _OsdMessegeFont1[osd_font_mode][76];
	osd_DrawString(xStart_Str+1, yStart_Str-1, str1, setupFcolorT, setupBGcolorSS);
	//show drm code
	osd_DrawString(xStart_Str+3, yStart_Str, buf_save_drm_code, setupFcolorSS, setupBGcolorSS);
	//show DIVX Web:  helm for clean DIVX web site, 050825
	  const char *str2;
	  str2 = _OsdMessegeFont1[osd_font_mode][75];
      osd_DrawString(xStart_Str-17, yStart_Str+3 , str2, setupFcolorSS, setupBGcolorSS);
	//draw scale form
	xStart = SETUP_SUB_XSTART * 16;
        xWidth = 15 *16;
        yStart = (3+SETUP_MENU_YSTART + 1)*SETUP_BUTTON_HEIGHT;
        yDelta = 2*SETUP_BUTTON_HEIGHT;
#else  //!SHOW_DIVX_WEB_INIT_STR
	//show "registration \n code"
     #ifdef    SUPPORT_OTHER_LANGUAGE_STRING	 
       osd_DrawString(xStart_Str+1, yStart_Str-1, osd_other_str[osd_font_mode][SHOW_REGISTER_CODE_LINE1], setupFcolorT, setupBGcolorSS);	   
	osd_DrawString(xStart_Str+1, yStart_Str, osd_other_str[osd_font_mode][SHOW_REGISTER_CODE_LINE2], setupFcolorT, setupBGcolorSS);
     #else//else=>	#ifdef    SUPPORT_OTHER_LANGUAGE_STRING	
	osd_DrawString(xStart_Str+1, yStart_Str-1, show_register_code_line1, setupFcolorT, setupBGcolorSS);
	osd_DrawString(xStart_Str+1, yStart_Str, show_register_code_line2, setupFcolorT, setupBGcolorSS);
     #endif //end=> #ifdef    SUPPORT_OTHER_LANGUAGE_STRING

	//show drm code
	osd_DrawString(xStart_Str+3, yStart_Str+1, buf_save_drm_code, setupFcolorSS, setupBGcolorSS);
	//show DIVX Web:  helm for clean DIVX web site, 050825
	//osd_DrawString(xStart_Str-17, yStart_Str+3, show_DIVX_Web, setupFcolorSS, setupBGcolorSS);

     #ifdef    SUPPORT_OTHER_LANGUAGE_STRING
		osd_DrawString(xStart_Str-17, SETUP_MENU_YSTART+8 , osd_other_str[osd_font_mode][SHOW_DIVX_WEB], setupFcolorSS, setupBGcolorSS); //liumzh modify
     #else//else=>	#ifdef    SUPPORT_OTHER_LANGUAGE_STRING	
	osd_DrawString(xStart_Str-17, SETUP_MENU_YSTART+8 , show_DIVX_Web, setupFcolorSS, setupBGcolorSS); //liumzh modify, 2005-12-19
     #endif //end=> #ifdef    SUPPORT_OTHER_LANGUAGE_STRING

	
	//osd_DrawString(xStart_Str-17, SETUP_MENU_YSTART+8 , show_DIVX_Web, setupFcolorSS, setupBGcolorSS); //liumzh modify, 2005-12-19
	//draw scale form
	xStart = SETUP_SUB_XSTART * 16;
        xWidth = 15 *16;
        //yStart = (3+SETUP_MENU_YSTART + 1)*SETUP_BUTTON_HEIGHT;
        yStart = (yStart_Str - 1)*SETUP_BUTTON_HEIGHT; //liumzh modify, 2005-12-19
        yDelta = 3*SETUP_BUTTON_HEIGHT;
#endif //#ifdef SHOW_DIVX_WEB_INIT_STR
        
        if (p_scan==1)
             osd_DrawLine(xStart, yStart, xStart+xWidth, yStart, setupEcolorSPTLU, 2); //top line
        else
             osd_DrawLine(xStart, yStart, xStart+xWidth, yStart, setupEcolorSPTLU, 1); //top
             
        osd_DrawLine(xStart, yStart, xStart, yStart+yDelta, setupEcolorSPTLU, 1); //left line
        
        if (p_scan==1)
             osd_DrawLine(xStart, yStart+yDelta, xStart+xWidth, yStart+yDelta, setupEcolorSPBRU, 2); //bottom line
        else
             osd_DrawLine(xStart, yStart+yDelta, xStart+xWidth, yStart+yDelta, setupEcolorSPBRU, 1);//bottom
             
        osd_DrawLine(xStart+xWidth, yStart, xStart+xWidth, yStart+yDelta, setupEcolorSPBRU, 1); //right line
}
#endif //DRM_CODE

void setup_ShowPage(void)
{
    //printf("\n\nsetup_show_page\n");

#if defined(ALCO_DVD_UI)
    if(!full_scrn)//added 05/08/06
        return;
#endif 
    
    // setup position has no changed, no need to re-draw
    if((setup_pos[0] == setup_last_pos[0]) && (setup_pos[1] == setup_last_pos[1])
        &&(setup_pos[2] == setup_last_pos[2]) && (setup_pos[3] == setup_last_pos[3]))
    {
        return;
    }

    if(full_scrn&CUSTM)
    {
        setup_ShowPageCUSTM();
        return;
    }

    // level 1, show page title and icon bar
    if(((setup_pos[SETUP_ML0] == 1) && (setup_last_pos[SETUP_ML0] <= 1 ))||(setup_pos[1]!=setup_last_pos[1]))
    {
        setup_ShowPageL1();
        #ifdef SHOW_SETUPMENU_SETUP //denghangao 20040929
           show_setupmenu();
        #endif
        
    }

    // level 2, show page items
    if(!((setup_pos[SETUP_ML0] == SETUP_ML3) && (setup_last_pos[SETUP_ML0] == SETUP_ML3)))
    {
        setup_ShowPageL2();
    }
    
    // level 3, show item selections
    if(setup_pos[SETUP_ML0] > SETUP_ML1)
    {
        setup_ShowPageL3();
    }

}//end of setup_show_menu
//====================================================================


void setup_ShowPageL1(void)
{
    int     i;
#ifdef  SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28
    UINT16 line=SETUP_MAX_WIDTH*16;
#else
    UINT16 line=SETUP_MAX_WIDTH*16-20;
#endif

#ifndef  SETUPMENU_16Mb_NO_ICON
    //printf("\n\nsetup_show_page_L1\n");

    //draw rectangulars
    #ifndef NGAILIK_MENU    //liudan add for 1006 setup menu.
    osd_draw_rect(0, 0, (SETUP_MAX_WIDTH*16), 10+SETUP_BUTTON_HEIGHT+12, setupBGcolorH);                
    osd_draw_rect(10, 10, line, SETUP_BUTTON_HEIGHT+12,setupBGcolorI); 
    osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT+12, line+20, SETUP_BUTTON_HEIGHT+8, setupBGcolorT);
    #else
    osd_draw_rect(80, 10+12, line+20-80, SETUP_BUTTON_HEIGHT+8, setupBGcolorT);
    #endif
    #ifdef PHILIPS_SETUP//chenzhao 20050613
    osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+20, (SETUP_MAX_WIDTH*16),region[SETUP_REGION].osd_h-(10+SETUP_BUTTON_HEIGHT*2+20), setupBGcolorB);                
    osd_DrawIcon(setuplogo_x, setuplogo_y, setuplogo_index,0);       
    osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT+20, (SETUP_MAX_WIDTH*16), 2, setupBGcolorSL);                
    osd_draw_rect(0, region[SETUP_REGION].osd_h-18, (SETUP_MAX_WIDTH*16), 18, setupBGcolorF);
    #elif defined(NGAILIK_MENU)    //liudan add for 1006 setup menu.
    //osd_draw_rect(0, 0, 10+SETUP_BUTTON_HEIGHT+12, region[0].osd_h, setupBGcolorH);                
    osd_draw_rect(4, 4, SETUP_BUTTON_HEIGHT+12+4,region[0].osd_h-20 ,setupBGcolorI); 
    //osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT+12, line+20, SETUP_BUTTON_HEIGHT+8, setupBGcolorT); 
    
    //osd_draw_rect(10+SETUP_BUTTON_HEIGHT*2, 0, (SETUP_MAX_WIDTH*16), region[0].osd_h, setupBGcolorB);                
    osd_draw_rect(4+SETUP_BUTTON_HEIGHT+12+8, 0, 2, region[0].osd_h, setupBGcolorSL);                
    //osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+10+(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)-100, (SETUP_MAX_WIDTH*16), 18, setupBGcolorF);   
    #else //PHILIPS_SETUP
    osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+20, (SETUP_MAX_WIDTH*16), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT), setupBGcolorB);                
    osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+20, (SETUP_MAX_WIDTH*16), 2, setupBGcolorSL);                
    osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+10+(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)-100, (SETUP_MAX_WIDTH*16), 18, setupBGcolorF);
    #endif//PHILIPS_SETUP
    
    // show page title
    const char *str;

    #ifdef SETUP_EXTENSION_TABLE        // 2005/03/29 yltseng
    UINT8 uiExTable = ( setup_item[setup_pos[1]][setup_pos[2]][0] & 0xf0 ) ? TRUE : FALSE;
    if( uiExTable )
        str = GetOSDString( osd_font_mode, setup_item[setup_pos[SETUP_ML1]][0][1] );
    else
    #endif
        str = _OsdMessegeFont1[osd_font_mode][setup_item[setup_pos[SETUP_ML1]][0][1]];
    #ifdef NGAILIK_MENU    //liudan add for 1006 setup menu.
    osd_DrawString(setup_item[setup_pos[1]][0][3]+3, 1, str, setupFcolorT, setupBGcolorT);
    #else
    osd_DrawString(setup_item[setup_pos[1]][0][3], 2, str, setupFcolorT, setupBGcolorT);
    #endif

#else//denghg   draw rectangulars  2004-9-28 13:50
    osd_draw_rect(0, 0, (SETUP_MAX_WIDTH*16), 10+SETUP_BUTTON_HEIGHT+12, setupBGcolorH);                
    osd_draw_rect(10, 10, line, SETUP_BUTTON_HEIGHT+12,setupBGcolorI); 
    osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT+12, line+20, SETUP_BUTTON_HEIGHT+8, setupBGcolorT);
    osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+20, (SETUP_MAX_WIDTH*16), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT),setupBGcolorB);
    // osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+20, (SETUP_MAX_WIDTH*16), 2, setupBGcolorSL);                
    osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+10+(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)-100, (SETUP_MAX_WIDTH*16), 18, setupBGcolorF);
 
    //DENGHG  SHOW  CURSOR 2004-9-28 16:13 
    osd_draw_rect((setup_pos[SETUP_ML1])*line/setup_max_icon, 10, line/setup_max_icon+10,SETUP_BUTTON_HEIGHT+12, setupCURSOR);
    
#endif//

    // draw icon bar or  setupIconString  //denghg  2004-9-28 20:18
    for(i=0; i<setup_max_icon; i++)
    {       
#ifdef SETUPMENU_16Mb_NO_ICON
           const char *setupIconString[MAX_SETUP_PAGE]={"SYS","LAN","AUD","VID","SPE","DIG"};
           osd_DrawSetupIconString(setup_item[i][0][4], 13,setupIconString[setup_item[i][0][2]],IconStringTCOLOR,IconStringBGCOLOR);            	            
#elif defined(NGAILIK_MENU)    //liudan add for 1006 setup menu.
           osd_DrawIcon(1,region[0].osd_h*(2*i+1)/(2*setup_max_icon)-16 , setup_item[i][0][2], setup_item[setup_pos[SETUP_ML1]][0][2]); 	           
#else
           osd_DrawIcon(setup_item[i][0][4], 13, setup_item[i][0][2], setup_item[setup_pos[SETUP_ML1]][0][2]);       
           //printf("setup_pos[SETUP_ML1]=%4d\n",setup_pos[SETUP_ML1]);  
#endif          	  
    }
}



//====================================================================

void setup_ShowPageL2(void)
{
#ifdef SUPPORT_TVG_ACTIVATION       // 2005/11/08 yltseng
    #include "TVGApp.h"
    if( ( setup_pos[SETUP_ML0] == SETUP_ML1 ) && ( setup_item[setup_pos[SETUP_ML1]][0][1] == STR_OS_TV_GUARDIAN ) )
        if( !TVGActivationProcess() )
            return;
#endif

    int     i;
    BYTE    xStart, yStart, xLen;//, xOffset, fColor, bgColor, upDown;
    //const char   *str;    

    //printf("\n\nsetup_show_page_L2\n");
    yStart = 0;
    //for setup_level = 1, left/right walking on page(1st) level, just list all items of this page
    if(((setup_pos[SETUP_ML2] == 0) && (setup_pos[SETUP_ML0] == SETUP_ML1))
        #ifdef USE_SETUP_ITEM_ENABLE_FLAG// for setup_level from 3 to 2, change the color of disable item,added by chenzhao on 2005-3-31 16:5  
        ||((setup_pos[0] == SETUP_ML2) && (setup_last_pos[0] == SETUP_ML3))
        #endif
        ||setup_refresh) 
    {            
        //clear level 2 area
        #ifdef NGAILIK_MENU    //liudan add for 1006 setup menu.
        osd_draw_rect(4+SETUP_BUTTON_HEIGHT+12+12, 10+SETUP_BUTTON_HEIGHT*2+22, (SETUP_MAX_WIDTH*8)-16, (MAX_PAGE_ITEM*SETUP_BUTTON_HEIGHT)+10, setupBGcolorL2);
		#else        
        osd_draw_rect(10, 10+SETUP_BUTTON_HEIGHT*2+22, (SETUP_MAX_WIDTH*8)-16, (MAX_PAGE_ITEM*SETUP_BUTTON_HEIGHT)+10, setupBGcolorL2);
        #endif
        //clear level 3 area
        #ifndef SHOW_SETUPMENU_SETUP//denghangao 20040929
            #ifdef NGAILIK_MENU    //liudan add for 1006 setup menu.
            osd_draw_rect((SETUP_MAX_WIDTH*8)-8+32, 10+SETUP_BUTTON_HEIGHT*2+22, (SETUP_MAX_WIDTH*8)-10, (MAX_PAGE_ITEM*SETUP_BUTTON_HEIGHT)+10, setupBGcolorL3);
		    #else        
            osd_draw_rect((SETUP_MAX_WIDTH*8)-8, 10+SETUP_BUTTON_HEIGHT*2+22, (SETUP_MAX_WIDTH*8)-10, (MAX_PAGE_ITEM*SETUP_BUTTON_HEIGHT)+10, setupBGcolorL3);
            #endif
        #endif
        #ifdef PHILIPS_SETUP//chenzhao20050613
        osd_draw_rect((SETUP_MAX_WIDTH*8)-8,10+SETUP_BUTTON_HEIGHT*2+20,2, (MAX_PAGE_ITEM*SETUP_BUTTON_HEIGHT)+16,setupBGcolorSLV);
        #endif
		xStart = SETUP_MENU_XSTART;
        xLen = SETUP_SUB_XSTART-SETUP_MENU_XSTART-1;
        setup_itemType= SETUP_itemNormal;
        
        for(i=1; i<=MAX_PAGE_ITEM; i++)
        {
        	if((setup_item[setup_pos[1]][i][0]!=SET_NE)&&(setup_item[setup_pos[1]][i][0]!=SET_SPACE))
        	{
            	yStart = SETUP_MENU_YSTART + i;
            	
            	id = setup_item[setup_pos[SETUP_ML1]][i][1];
                #ifdef USE_SETUP_ITEM_ENABLE_FLAG //added by chenzhao on 2005-3-31 16:4  
                if((SETUP_VA_NONE!=setup_item[setup_pos[SETUP_ML1]][i][MAX_ITEM_SEL+1])
                      &&(0==setup_VA_EN[setup_item[setup_pos[SETUP_ML1]][i][MAX_ITEM_SEL+1]]))
                    setup_itemType = SETUP_itemDisnable;
                else
                    setup_itemType= SETUP_itemNormal;
                #endif//USE_SETUP_ITEM_ENABLE_FLAG added by chenzhao on 2005-3-31 16:4  

                                
            	setup_draw_item(xStart, yStart, xLen, id, setup_itemType, setup_item[setup_pos[1]][i][0] );     // 2005/03/29 yltseng
            }
        }
    }

    #ifdef SHOW_SETUPMENU_SETUP//added by wangwei,2005-3-31 15:55(For hanyang,when highlight level 1st,show setup menu settings.)
    if((setup_pos[SETUP_ML0] == SETUP_ML1)) //&& (setup_last_pos[SETUP_ML0] == SETUP_ML1))
        show_setupmenu();
    #endif//SHOW_SETUPMENU_SETUP

    //for setup_level =2, up/down walking on item(2nd) level, highlight the corresponding item
    if(setup_pos[SETUP_ML0] == SETUP_ML2)
    {
        //clear level 3 area
        #ifdef USE_SETUP_SELECT_FONT
        osd_draw_rect((SETUP_MAX_WIDTH*8)-40,10+SETUP_BUTTON_HEIGHT*2+22, (SETUP_MAX_WIDTH*8)-10+40, (MAX_PAGE_ITEM*SETUP_BUTTON_HEIGHT)+10, setupBGcolorL3);
        #elif defined(NGAILIK_MENU)    //liudan add for 1006 setup menu.
        osd_draw_rect((SETUP_MAX_WIDTH*8)-8+32, 10+SETUP_BUTTON_HEIGHT*2+22, (SETUP_MAX_WIDTH*8)-10, (MAX_PAGE_ITEM*SETUP_BUTTON_HEIGHT)+10, setupBGcolorL3);
        #else
        osd_draw_rect((SETUP_MAX_WIDTH*8)-8,10+SETUP_BUTTON_HEIGHT*2+22, (SETUP_MAX_WIDTH*8)-10, (MAX_PAGE_ITEM*SETUP_BUTTON_HEIGHT)+10, setupBGcolorL3);
        #endif
        
        #ifdef PHILIPS_SETUP//chenzha020050613  
        osd_draw_rect((SETUP_MAX_WIDTH*8)-8,10+SETUP_BUTTON_HEIGHT*2+20,2, (MAX_PAGE_ITEM*SETUP_BUTTON_HEIGHT)+16,setupBGcolorSLV);
        #endif

        xStart = SETUP_MENU_XSTART;
        xLen = SETUP_SUB_XSTART-SETUP_MENU_XSTART-1;
            
        //unmark last located item
        if(setup_last_pos[SETUP_ML2] != 0)
        {
            yStart = SETUP_MENU_YSTART + setup_last_pos[SETUP_ML2];
            
            id = setup_item[setup_last_pos[SETUP_ML1]][setup_last_pos[SETUP_ML2]][1];
            setup_itemType= SETUP_itemNormal;
            setup_draw_item(xStart, yStart, xLen, id, setup_itemType, setup_item[setup_last_pos[SETUP_ML1]][setup_last_pos[SETUP_ML2]][0]);     // 2005/03/29 yltseng
        }

        // mark current located item
        if(setup_pos[SETUP_ML2] != 0)
        {
            yStart = SETUP_MENU_YSTART + setup_pos[SETUP_ML2];
                 
            id = setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1];
            setup_itemType= SETUP_itemMark;
            setup_draw_item(xStart, yStart, xLen, id, setup_itemType, setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][0]);       // 2005/03/29 yltseng
        }

        //draw arrow
        if((setup_item[setup_pos[1]][setup_pos[2]][0]!=SET_SH)&&(setup_item[setup_pos[1]][setup_pos[2]][0]!=SET_LINK))
        {
            osd_DrawString(SETUP_SUB_XSTART-1, yStart, Ch_arrorR, setupFcolorAL2, setupBGcolorAL2);
        }
    }

    // for setup_level from 2 to 3, change the color of selected item
    if((setup_pos[0] == SETUP_ML3) && (setup_last_pos[0] == SETUP_ML2))
    {
                xStart = SETUP_MENU_XSTART;
        xLen = SETUP_SUB_XSTART-SETUP_MENU_XSTART-1;
        
        yStart = SETUP_MENU_YSTART + setup_pos[SETUP_ML2];
        
        id = setup_item[setup_pos[1]][setup_pos[2]][1];
        setup_itemType = SETUP_itemSelected;
        setup_draw_item(xStart, yStart, xLen, id, setup_itemType, setup_item[setup_pos[1]][setup_pos[2]][0]);                           // 2005/03/29 yltseng

        //draw arrow
        osd_DrawString(SETUP_SUB_XSTART-1, yStart, Ch_arrorR, setupFcolorAL3, setupBGcolorAL3);
    }
    
    #ifdef SHOW_SOFTWARE_VERSION_IN_SETUP_MENU//for hanyang SETUP MENU show software version,added by wangwei,2005-2-24 11:29
    if(setup_pos[SETUP_ML1] == (VERSION_IN_WHICH_PAGE - 1))
    {
        BYTE    buf[20];
        psprintf(buf, "%s", SETUP_VERSION);
        osd_DrawString(SETUP_MENU_XSTART+1,10, buf, 6, 0);
    }
    #endif//#if SHOW_SOFTWARE_VERSION_IN_SETUP_MENU
}
//====================================================================

UINT32 setup_GetFuncItemPosition()      // 2005/04/11 yltseng
{
    UINT32 i;
    for( i = 2; i < MAX_ITEM_SEL; i++ )
        if( !setup_item[setup_pos[1]][setup_pos[2]][i] )
            break;
    
    if( setup_pos[2] + i > 11 )
        i = 10 - i;
    else
        i = setup_pos[2] - 1;

    return i;
}

void setup_ShowPageL3(void)
{
    int         i;
    BYTE    xStart, yStart, xLen;//, xOffset, fColor, bgColor, upDown;
    UINT8   itemType, itemSel, Get_id; //helm for get DRM id 050622
        
    //printf("\n\nsetup_show_page_L3\n");

    itemType = setup_item[setup_pos[1]][setup_pos[2]][0];
    Get_id = setup_item[setup_pos[1]][setup_pos[2]][1]; //helm 050622

    xStart = SETUP_SUB_XSTART;
    #ifdef NGAILIK_MENU    //liudan add for 1006 setup menu.
    xLen = SETUP_MAX_WIDTH-SETUP_SUB_XSTART;
    #else
    xLen = SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2;
    #endif
    
    //for setup_level = 2, up/down walking on item(2nd) level, just list all selection of this item 
    if((setup_pos[0] == SETUP_ML2)||setup_refresh)//chenzhao 20060116
    {
        switch(itemType)
        {
            case SET_FUNC:
#ifdef SETUP_EXTENSION_TABLE        // 2005/03/29 yltseng
            case SET_FUNC_EX:
#endif
                itemSel = setup_sel[setup_pos[1]][setup_pos[2]];
                yStart = setup_GetFuncItemPosition() + 3;       // 2005/04/11 yltseng
                
                for(i=2; i<MAX_ITEM_SEL; i++, yStart++ )
                {
                    id = setup_item[setup_pos[1]][setup_pos[2]][i];
                    if (id == 0) break;
                    
                    #ifdef DOWNMIXOFF_DISP_51CHANNEL
                    if((setup_item[setup_pos[1]][setup_pos[2]][1]==STR_OS_DOWNMIX_SETUP)&&(id==STR_OS_OFF))
                         id=STR_OS_5_1_CHANNEL;
                    #endif
                    
                    if(itemSel==i)
                        setup_itemType= SETUP_itemSelected;
                    else
                        setup_itemType= SETUP_itemNormal;

#ifdef DRM_CODE                
                    if (Get_id == STR_OS_DRM_REGISTRATION_CODE){ //helm for showing drm code 050622
                        setup_Show_DRM_CODE(xStart, yStart);
                        Clean_DRM_Web = 1;
                    }    
                    else   
#endif
                    setup_draw_item(xStart, yStart, xLen, id, setup_itemType, itemType);    // 2005/03/29 yltseng
                }
                break;
            case SET_SCALE:
                id = setup_item[setup_pos[1]][setup_pos[2]][1];
                setup_DrawScaleForm( id, 0);
                setup_DrawScaleCursor(id, 0);
                break;
            case SET_NM:
                setup_pos[3] = setup_sel[setup_pos[1]][setup_pos[2]];
                id = setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]];
                yStart = setup_pos[2]+SETUP_MENU_YSTART;
                setup_itemType = SETUP_itemSelected;
                setup_draw_item(xStart, yStart, xLen, id, setup_itemType, itemType);        // 2005/03/29 yltseng
                break;
                
            case SET_SH:
            #ifdef SETUP_EXTENSION_TABLE
            case SET_SHOW_EX2:
            #endif
            case SET_NE:
            case SET_SPACE:
                break;
        }
    }

    //for setup_level from 2 to 3
    if(((setup_pos[0] == SETUP_ML3) && (setup_last_pos[0] == SETUP_ML2))||setup_refresh)//chenzhao 20060116
    {

        switch(itemType)
        {
            case SET_FUNC:
#ifdef SETUP_EXTENSION_TABLE        // 2005/03/29 yltseng
            case SET_FUNC_EX:
#endif
                
                id = setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]];
                yStart = setup_GetFuncItemPosition() + setup_pos[3] + 1;                    // 2005/04/11 yltseng
            #ifdef DOWNMIXOFF_DISP_51CHANNEL
                if((setup_item[setup_pos[1]][setup_pos[2]][1]==STR_OS_DOWNMIX_SETUP)&&(id==STR_OS_OFF))
                     id=STR_OS_5_1_CHANNEL;
            #endif 
                setup_itemType= SETUP_itemMark;
                setup_draw_item(xStart, yStart, xLen, id, setup_itemType, itemType);        // 2005/03/29 yltseng
                break;
            case SET_SCALE:
                id = setup_item[setup_pos[1]][setup_pos[2]][1];
                setup_DrawScaleForm( id, 1);
                setup_DrawScaleCursor(id, 1);
                break;
            case SET_NM:
                id = setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]];
                yStart = setup_pos[2]+SETUP_MENU_YSTART;

                setup_itemType= SETUP_itemMark;
                setup_draw_item(xStart, yStart, xLen, id, setup_itemType, itemType);        // 2005/03/29 yltseng
                break;
        }
    }

    //for setup_level =3, up/down walking on selection(3rd) level, highlight the corresponding selection
    if((setup_pos[0] == SETUP_ML3) && (setup_last_pos[0] == SETUP_ML3))
    {
        switch(itemType)
        {
            case SET_FUNC:
#ifdef SETUP_EXTENSION_TABLE        // 2005/03/29 yltseng
            case SET_FUNC_EX:
#endif
                    //unmark last selection
                    {
                        itemSel = setup_sel[setup_pos[1]][setup_pos[2]];
                        if(itemSel == setup_last_pos[3]) 
                            setup_itemType = SETUP_itemSelected;
                        else 
                            setup_itemType = SETUP_itemNormal;
                        
                        id = setup_item[setup_last_pos[1]][setup_last_pos[2]][setup_last_pos[3]];
                        yStart = setup_GetFuncItemPosition() + setup_last_pos[3] + 1;               // 2005/04/11 yltseng
                     #ifdef DOWNMIXOFF_DISP_51CHANNEL
                        if((setup_item[setup_pos[1]][setup_pos[2]][1]==STR_OS_DOWNMIX_SETUP)&&(id==STR_OS_OFF))
                          id=STR_OS_5_1_CHANNEL;
                     #endif    
                        
                        setup_draw_item(xStart, yStart, xLen, id, setup_itemType, itemType);        // 2005/03/29 yltseng
                    }

                    //mark current selection
                    {
                        id = setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]];
                        yStart = setup_GetFuncItemPosition() + setup_pos[3] + 1;                    // 2005/04/11 yltseng

                        setup_itemType = SETUP_itemMark;
                      #ifdef DOWNMIXOFF_DISP_51CHANNEL
                        if((setup_item[setup_pos[1]][setup_pos[2]][1]==STR_OS_DOWNMIX_SETUP)&&(id==STR_OS_OFF))
                          id=STR_OS_5_1_CHANNEL;
                     #endif 
                        
                        setup_draw_item(xStart, yStart, xLen, id, setup_itemType, itemType);        // 2005/03/29 yltseng
                    }
                break;
            case SET_SCALE:
                id = setup_item[setup_last_pos[1]][setup_last_pos[2]][setup_last_pos[3]];
                setup_DrawScaleCursor(id, 1);
                break;
        }
    }
    
    #ifdef SHOW_SOFTWARE_VERSION_IN_SETUP_MENU//for hanyang SETUP MENU show software version,added by wangwei,2005-2-24 11:29
    if(setup_pos[SETUP_ML1] == (VERSION_IN_WHICH_PAGE - 1))
    {
        BYTE    buf[20];
        psprintf(buf, "%s", SETUP_VERSION);
        osd_DrawString(SETUP_MENU_XSTART+1,10, buf, 6, 0);
    }
    #endif//#if SHOW_SOFTWARE_VERSION_IN_SETUP_MENU
    
}


void setup_ExitPage(void)
{
    ExitSetupPage(1);
    run_save_total_sel();
    #ifdef NEED_DIFF_IR_PANEL_KEY
    panel_key_flag = 0;
    #endif
    
    //printf("run_save_total_sel()\n");
}
//====================================================================


void setup_ShowPageCUSTM(void)
{
    int     i;//, j;
    BYTE    xStart, yStart, xLen;//, xOffset, fColor, bgColor, upDown;
    UINT8   itemType, itemSel;
    char buf[8];

    yStart=0;
    itemType = setup_item[setup_pos[1]][setup_pos[2]][0];

    //draw CUSTM page level_1 and level_2
    if(setup_last_pos[0]==0)
    {
        osd_draw_rect(0, 0, (SETUP_MAX_WIDTH*16), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT), setupBGcolorCUSTM);                
                
        //level_2
        xStart = SETUP_MENU_XSTART;
        xLen = SETUP_SUB_XSTART-SETUP_MENU_XSTART-1;
        setup_itemType= SETUP_itemNormal;
        
        for(i=1; i<=MAX_PAGE_ITEM; i++)
        {
            yStart = SETUP_MENU_YSTART + i;
            id = setup_item[setup_pos[SETUP_ML1]][i][1];
            /*    //jslin removed//20050304
            if(id == 0)//Jack added 04/12/01
                break;
            */  
            setup_draw_item(xStart, yStart, xLen, id, setup_itemType, itemType);        // 2005/03/29 yltseng
        }
        setup_ShowCUSTMMsg();
    }
//====================================================================


    //for setup_level =2, up/down walking on item(2nd) level, highlight the corresponding item
    if(setup_pos[SETUP_ML0] == SETUP_ML2)
    {
        //clear level 3 area
        #ifdef RATING_8 
        #ifdef OP_CUST_UI	 
        if (setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1]==STR_OS_REGION_CODE)
        osd_draw_rect((SETUP_SUB_XSTART-1)*16,
                        (SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT+31,
                        (SETUP_MAX_WIDTH-SETUP_SUB_XSTART)*16,
                        (SETUP_MAX_LINE-SETUP_MENU_YSTART-1)*SETUP_BUTTON_HEIGHT,
                        setupBGcolorCUSTM);                
        else 
        #endif//#ifdef OP_CUST_UI	      
        osd_draw_rect((SETUP_SUB_XSTART-1)*16,
                        (SETUP_MENU_YSTART+1)*SETUP_BUTTON_HEIGHT+31,
                        (SETUP_MAX_WIDTH-SETUP_SUB_XSTART)*16,
                        (SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT,
                        setupBGcolorCUSTM);
        #else//#ifdef RATING_8
         
        setup_Clear_CUSTM_L3();
        
        #endif//#ifdef RATING_8 

        xStart = SETUP_MENU_XSTART;
        xLen = SETUP_SUB_XSTART-SETUP_MENU_XSTART-1;
            
        //unmark last located item
        if(setup_last_pos[SETUP_ML1] == setup_page_CUS)
        {
            yStart = SETUP_MENU_YSTART + setup_last_pos[SETUP_ML2];
            id = setup_item[setup_last_pos[SETUP_ML1]][setup_last_pos[SETUP_ML2]][1];
            setup_itemType = SETUP_itemNormal;
            setup_draw_item(xStart, yStart, xLen, id, setup_itemType, itemType);        // 2005/03/29 yltseng
        }

        // mark current located item
        if(setup_pos[SETUP_ML2] != MAX_PAGE_ITEM)
        {
            yStart = SETUP_MENU_YSTART + setup_pos[SETUP_ML2];      
            id = setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1];
            setup_itemType = SETUP_itemMark;
            setup_draw_item(xStart, yStart, xLen, id, setup_itemType, itemType);        // 2005/03/29 yltseng
        }

        //draw ">>" between located item and it's corresponding selection area
        if((setup_item[setup_pos[1]][setup_pos[2]][0]!=SET_SH)&&(setup_item[setup_pos[1]][setup_pos[2]][0]!=SET_LINK))
        {
            osd_DrawString(SETUP_SUB_XSTART-1, yStart, Ch_arrorR, setupFcolorAL2, setupBGcolorAL2);
        }

        //level_3

        xStart = SETUP_SUB_XSTART;
        #ifdef RATING_8 
        xLen = SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1;
        #else
        xLen = SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2;
        #endif
        
        switch(itemType)
        {
            case SET_FUNC:
                itemSel = setup_sel[setup_pos[1]][setup_pos[2]];
                
                for(i=2; i<MAX_ITEM_SEL; i++)
                {
                    id = setup_item[setup_pos[1]][setup_pos[2]][i];
                    if (id == 0) break;

                    yStart = setup_item[setup_pos[1]][setup_pos[2]][MAX_ITEM_SEL]+i+1;
                    if(itemSel==i)
                        setup_itemType= SETUP_itemSelected;
                    else
                        setup_itemType= SETUP_itemNormal;

                    setup_draw_item(xStart, yStart, xLen, id, setup_itemType, itemType);        // 2005/03/29 yltseng
                }
                break;
            case SET_NM:
                setup_pos[3] = setup_sel[setup_pos[1]][setup_pos[2]];
                yStart = setup_pos[2]+SETUP_MENU_YSTART;
                
                #ifdef ALCO_DVD_UI
                osd_draw_setup_button(xStart,yStart,xLen, setupBGcolorCUSTM, SETUP_itemNormal);
                #endif

                #ifdef SETUP_6_DIGIT_PASSWORD
                    psprintf(buf, "%06d", UserSet.parent_passwd);
                #else
                    psprintf(buf, "%04d", UserSet.parent_passwd);
                #endif
                osd_DrawString(xStart+1, yStart, buf, setupFcolorSS, setupBGcolorCUSTM);
                break;
            case SET_SH:
            case SET_NE:
            case SET_SPACE:
                break;
        }       
    }
//==========================================================================

    
    // for setup_level from 2 to 3, change the color of selected item
    if((setup_pos[0] == SETUP_ML3) && (setup_last_pos[0] == SETUP_ML2))
    {
        xStart = SETUP_MENU_XSTART;
        xLen = SETUP_SUB_XSTART-SETUP_MENU_XSTART-1;
        yStart = SETUP_MENU_YSTART + setup_pos[SETUP_ML2];
        id = setup_item[setup_pos[1]][setup_pos[2]][1];

        setup_itemType = SETUP_itemSelected;
        setup_draw_item(xStart, yStart, xLen, id, setup_itemType, itemType);                // 2005/03/29 yltseng
        osd_DrawString(SETUP_SUB_XSTART-1, yStart, Ch_arrorR, setupFcolorAL3, setupBGcolorAL2);

        //level_3
        xStart = SETUP_SUB_XSTART;
        #ifdef RATING_8 
        xLen = SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1;
        #else
        xLen = SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2;
        #endif
    
        switch(itemType)
        {
            case SET_FUNC:
                id = setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]];
                yStart = setup_item[setup_pos[1]][setup_pos[2]][MAX_ITEM_SEL]+setup_pos[3]+1;

                setup_itemType = SETUP_itemMark;
                setup_draw_item(xStart, yStart, xLen, id, setup_itemType, itemType);        // 2005/03/29 yltseng
                break;
            case SET_NM:
                setup_pos[3] = setup_sel[setup_pos[1]][setup_pos[2]];
                id = setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]];
                yStart = setup_pos[2]+SETUP_MENU_YSTART;

                #ifdef SETUP_6_DIGIT_PASSWORD
                    psprintf(buf, "%06d", UserSet.parent_passwd);
                #else
                    psprintf(buf, "%04d", UserSet.parent_passwd);
                #endif
                osd_draw_setup_button(xStart,yStart,xLen, setupBGcolorSM, 1);
                osd_DrawString(xStart+1, yStart, buf, setupFcolorSM, setupBGcolorSM);
                break;
        }
    }   
//================================================================================


    //for setup_level =3, up/down walking on selection(3rd) level, highlight the corresponding selection
    if((setup_pos[0] == SETUP_ML3) && (setup_last_pos[0] == SETUP_ML3))
    {
        xStart = SETUP_SUB_XSTART;
        #ifdef RATING_8 
        xLen = SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1;
        #else
        xLen = SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2;
        #endif
        //xOffset = 1;
        
        switch(itemType)
        {
            case SET_FUNC:
                //unmark last selection
                if(setup_last_pos[SETUP_ML1] == setup_page_CUS)
                {
                    itemSel = setup_sel[setup_pos[1]][setup_pos[2]];
                    if(itemSel == setup_last_pos[3]) 
                        setup_itemType= SETUP_itemSelected;
                    else
                        setup_itemType = SETUP_itemNormal;
                    
                    id = setup_item[setup_last_pos[1]][setup_last_pos[2]][setup_last_pos[3]];
                    yStart = setup_item[setup_pos[1]][setup_pos[2]][MAX_ITEM_SEL]+setup_last_pos[3]+1;
                    setup_draw_item(xStart, yStart, xLen, id, setup_itemType, itemType);        // 2005/03/29 yltseng
                }

                //mark current selection
                {
                    id = setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]];
                    yStart = setup_item[setup_pos[1]][setup_pos[2]][MAX_ITEM_SEL]+setup_pos[3]+1;
                    setup_itemType= SETUP_itemMark;
                    setup_draw_item(xStart, yStart, xLen, id, setup_itemType, itemType);        // 2005/03/29 yltseng
                }
                break;
        }
    }
#ifdef OP_CUST_UI//libing 2005-5-11 11:39
    if((setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1]!=STR_OS_RATING)&&(setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1]!=STR_OS_REGION_CODE)) 
#else
//#ifndef CUSTM_MENU_REVISE // 2005/06/18 terry
    if((setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1]!=STR_OS_RATING)
      #ifdef AUTO_LOAD_MODE_SETUP //DENGHG ADD FOR PHILIPS 2005-11-15 05:51     
      &&(setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1]!=STR_OS_MODE)
      #endif
      )
//#endif
#endif
    setup_ShowCUSTMMsg();
}
//====================================================================


void setup_ShowCUSTMMsg(void)
{
#ifdef 	OP_CUST_UI//libing 2005-5-13 16:01
	//#include ".\\Customers\\HK_Oritron\\op_ver.h"
#endif	
    BYTE    buf[40];
    BYTE    *pVersion;
#ifdef DVD_SERVO
    extern const UINT8 ServoVersion[];
#endif
    extern const UINT8 KernelVersion[];     // moved to libkern.a, leochen 2004/4/19 09:43¤U¤È
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
#if 0//def OP_CUST_UI
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+2, buf,setupFcolorCS, setupBGcolorCS);
#else
    osd_DrawString(SETUP_SUB_XSTART+6, SETUP_MENU_YSTART+2, buf,setupFcolorCS, setupBGcolorCS);
#endif

#ifdef DVD_SERVO
    //ServoVersion[16]=0; can't write to const data
    printf("ServoVersion %s\n", ServoVersion);
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART, ServoVersion, setupFcolorCN, setupBGcolorCN);
#endif


    buf[8]= 0; //Extend version string length to 8 Bytes, Jeff 20020715
    //osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+1, buf, SFONTCOLOR, SBGCOLOR); 
    psprintf(buf, "%s", MPEG_UI_VERSION);   
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+1, buf, setupFcolorCN, setupBGcolorCN);
    //osd_DrawString(SETUP_SUB_XSTART+5, SETUP_MENU_YSTART+1, KernelVersion, SFONTCOLOR, SBGCOLOR);

    osd_DrawString(SETUP_SUB_XSTART+4, SETUP_MENU_YSTART+1, KernelVersion, setupFcolorCN, setupBGcolorCN);
 
    //add build version, Jeff 20021008
    psprintf(buf, "%s", VERSION_STRING);

    osd_DrawString(SETUP_SUB_XSTART+8, SETUP_MENU_YSTART+1, buf, setupFcolorCN, setupBGcolorCN);
   
#if 1//ndef OP_CUST_UI//libing 2005-5-11 11:39    
    //psprintf(buf, "%c SUM:", regs0->stamp+'A');
    psprintf(buf, "%02x%03x", (regs0->stamp & 0xff),get_iop_b_status()); //2004/11/30 ycwen
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+2, buf, setupFcolorCN, setupBGcolorCN);
#endif
// show SDRAM, System clock, and update information     
//added by JSLin    //20040709
    //show update date and week
    psprintf(buf, "%s", UPDATE_DATE);
    osd_DrawString(SETUP_MENU_XSTART+1, SETUP_MENU_YSTART-2, buf, setupFcolorCN, setupBGcolorCN);
#ifndef OP_CUST_UI//libing 2005-5-11 11:39
    //psprintf(buf, "%s", UPDATE_WEEK);
    //osd_DrawString(SETUP_MENU_XSTART+8+1+1, SETUP_MENU_YSTART-2, buf, setupFcolorCN, setupBGcolorCN);
#endif
    //show SDRAM information
    psprintf(buf, "%s", SDRAM_SIZE);
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART-2, buf, setupFcolorCN, setupBGcolorCN);
    psprintf(buf, "%s", SDRAM_BUS);
    osd_DrawString(SETUP_SUB_XSTART+8, SETUP_MENU_YSTART-2, buf, setupFcolorCN, setupBGcolorCN);
	#if defined( OP_CUST_UI )//libing 2005-5-11 11:39
	#ifdef DIVX_DRM//libing 2005-7-5 14:22
	psprintf(buf, "%s", DRM_CTL_ID);
	#else
	psprintf(buf, "%s", "024");
	#endif
	osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+3, buf, 10, 14);
      psprintf(buf, "%s", "MACROVISION");//libing 2005-8-2 11:28
	osd_DrawString(SETUP_MENU_XSTART+1, SETUP_MENU_YSTART+3, buf, 10, 14);
	#endif
    //show system clock
    extern int get_sysclk;
    psprintf(buf, "SC:%d", (get_sysclk*675/100));
    osd_DrawString(SETUP_MENU_XSTART+1, SETUP_MENU_YSTART, buf, setupFcolorCN, setupBGcolorCN);

#ifdef CUSTM_MENU_REVISE
    const char *str;
    #ifdef ALCO_DVD_UI
    #ifdef TEST_VERSION_ALL_OPEN
    id = setup_item[MAX_SETUP_PAGE][3][7+1];
    #else
    id = setup_item[MAX_SETUP_PAGE][3][REGION_NUM+1];
    #endif
    #else
    id = setup_item[6][3][REGION_NUM+2];
    #endif
    str = _OsdMessegeFont1[osd_font_mode][id];
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+3, str, setupFcolorCN, setupBGcolorCN);
#endif     
#ifdef ORITRON_HK_DVD
    psprintf(buf, "%s", "DATE CODE");//libing 2005-8-2 11:28
    osd_DrawString(SETUP_MENU_XSTART+1, SETUP_MENU_YSTART-1, buf, setupFcolorCN, setupBGcolorCN);
    psprintf(buf, "%s",OP_NEW_DATE);//libing 2005-8-2 11:28
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART-1, buf, setupFcolorCN, setupBGcolorCN);
    #ifdef SUPPORT_OP_REGION_UI
       if(UserSet.P_RCD)psprintf(buf, "%s %d",REGION_NUMBER,UserSet.P_RCD);//fcr 2005-10-27 11:36
    	else psprintf(buf, "%s","REGION ALL");//fcr 2005-10-27 11:36
		psprintf(buf, "%s",REGION_NUMBER);//LIBING 2005-7-19 11:05
    	osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+4, buf, setupFcolorCN, setupBGcolorCN); 
	#endif 
#endif 
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
    osd_DrawString(3, SETUP_MENU_YSTART-1, buf, setupFcolorCN, setupBGcolorCN); 
    #endif   

}
//====================================================================


