/***************************************************************
*  setup_show_page_INDIGO_STYLE_OSDUI.c
*  include  in setup_show_page.c
* 
* Creator:  Mimitsai 
* Date:     2005/11/07
*
* Description : 
*           setup menu precentation engine, 
*           1. for INDIGO_STYLE_OSDUI setup menu   
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

#include "osd_palette.h"
#define SETUP_WID			(576)
#define SETUP_HEI			(360)
#define ICON_BG_WID			(576)
#define ICON_BG_HEI			(63-5-3)
#define ICON_PAGE_WID		(100)
#define ICON_STR_BG_WID		(568)
#define ICON_STR_BG_HEI		(36-6)
#define CONTENT_BG_WID		(568)
#define CONTENT_BG_HEI		(258+10)
#define ITEM_BG_WID			(546)
#define ITEM_BG_HEI			(236+10)
#define LINE_WID			(1)  //2

#ifdef SCALER_6500  //helm 050628
UINT8 HDVD_MOD;  //helm for scaler 050707
UINT8 setup_Check_PageL2_Ystart_Addr(UINT8 L2_POS) //helm for video output mode 050628
{
               UINT8 itemMode, itemType;
               itemType = setup_item[setup_pos[SETUP_ML1]][L2_POS][1];
               itemMode = setup_item[setup_pos[SETUP_ML1]][L2_POS][2];
                  if( (setup_item[setup_pos[SETUP_ML1]][0][1]==STR_OS_VIDEO_SETUP &&
                         itemType == STR_OS_EXIT_MENU) || itemMode == STR_OS_480P576P)                
                     return (SETUP_MENU_YSTART + L2_POS-1);  
                else
                     return (SETUP_MENU_YSTART + L2_POS);              
}
#endif

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
char *show_register_code = "REGISTER CODE"; //helm 050622
char *show_DIVX_Web="VISIT WEB SITE: WWW.DIVX.COM/VOD";
char Clean_DRM_Web=0;

void setup_Clean_DIVX_Web(void){  //helm for clean DIVX web site, 050825
osd_draw_rect(18, 270, (SETUP_MAX_WIDTH*16)-28, (2*SETUP_BUTTON_HEIGHT), setupBGcolorL2);
}


void setup_Show_DRM_CODE(BYTE xStart_Str, BYTE yStart_Str)
{
	UINT32  xStart, yStart;
	UINT8  yDelta=0;
	UINT8    xWidth;
	
	Gen_RegCode(); 
	
	//show "register code"
	osd_DrawString(xStart_Str+1, yStart_Str-1, show_register_code, setupFcolorT, setupBGcolorSS);
	//show drm code
	osd_DrawString(xStart_Str+3, yStart_Str, buf_save_drm_code, setupFcolorSS, setupBGcolorSS);
	//show DIVX Web:  helm for clean DIVX web site, 050825
	osd_DrawString(xStart_Str-16, yStart_Str+2 , show_DIVX_Web, setupFcolorSS, setupBGcolorSS);
	
	//draw scale form
	xStart = SETUP_SUB_XSTART * 16;
        xWidth = 15 *16;
        yStart = (3+SETUP_MENU_YSTART + 1)*SETUP_BUTTON_HEIGHT;
        yDelta = 2*SETUP_BUTTON_HEIGHT;
        
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

	int pageIndex;
	pageIndex = setup_item[setup_pos[SETUP_ML1]][0][2];
	if(setup_pos[2] == 0)
	    osd_draw_rect( 4+9+pageIndex*90+10  , ICON_BG_HEI                , ICON_PAGE_WID-20, 7, 7); // draw page highlight
	else
    	osd_draw_rect( 4+9+pageIndex*90+10  , ICON_BG_HEI                , ICON_PAGE_WID-20, ICON_STR_BG_HEI, setupBGcolorTTB); // clear page highlight

}//end of setup_show_menu
//====================================================================
BYTE reDrawSetupIconPage = 0;
void setup_ShowPageL1(void) // mimitsai add for new ui 2005.11.01
{
	osd_draw_rect( 0          ,  ICON_BG_HEI,               4, SETUP_HEI-ICON_BG_HEI, setupBGcolorH);//line
	osd_draw_rect( SETUP_WID-4,  ICON_BG_HEI,               4, SETUP_HEI-ICON_BG_HEI, setupBGcolorH);//line
	osd_draw_rect( 0          ,SETUP_HEI-4-1,       SETUP_WID,                     4, setupBGcolorH);//line

	osd_draw_rect( 4          , ICON_BG_HEI, ICON_STR_BG_WID, ICON_STR_BG_HEI, setupBGcolorT);//rect

    osd_draw_rect( 4            , ICON_BG_HEI+ICON_STR_BG_HEI,  CONTENT_BG_WID,               9, setupBGcolorBB);//line
	osd_draw_rect( 4            , SETUP_HEI-4-9-2            ,  CONTENT_BG_WID,               9, setupBGcolorBB);//line
	osd_draw_rect( 4            , ICON_BG_HEI+ICON_STR_BG_HEI,               9,  CONTENT_BG_HEI, setupBGcolorBB);//line
	osd_draw_rect( SETUP_WID-4-9, ICON_BG_HEI+ICON_STR_BG_HEI,               9,  CONTENT_BG_HEI, setupBGcolorBB);//line

	osd_draw_rect( 4+9+2, ICON_BG_HEI+ICON_STR_BG_HEI+9+2,     ITEM_BG_WID,     ITEM_BG_HEI, setupBGcolorB);//rect

	osd_DrawLine(4+9              , ICON_BG_HEI+ICON_STR_BG_HEI+9              , 4+9                , ICON_BG_HEI+ICON_STR_BG_HEI+9+2+ITEM_BG_HEI, setupBGcolorSL, 1); // line left
	osd_DrawLine(4+9+ITEM_BG_WID+2, ICON_BG_HEI+ICON_STR_BG_HEI+9              , 4+9+ITEM_BG_WID+2  , ICON_BG_HEI+ICON_STR_BG_HEI+9+2+ITEM_BG_HEI, setupBGcolorSL, 1); // line right
	osd_DrawLine(4+9              , ICON_BG_HEI+ICON_STR_BG_HEI+9              , 4+9+ITEM_BG_WID+2  , ICON_BG_HEI+ICON_STR_BG_HEI+9              , setupBGcolorSL, 1); // line top
	osd_DrawLine(4+9              , ICON_BG_HEI+ICON_STR_BG_HEI+9+2+ITEM_BG_HEI, 4+9+ITEM_BG_WID+2+2, ICON_BG_HEI+ICON_STR_BG_HEI+9+2+ITEM_BG_HEI, setupBGcolorSL, 1); // line botton

    // show page title
    const char *str;
	int i, pageIndex;

	pageIndex = setup_item[setup_pos[SETUP_ML1]][0][2];

    #ifdef SETUP_EXTENSION_TABLE        // 2005/03/29 yltseng
    UINT8 uiExTable = ( setup_item[setup_pos[1]][setup_pos[2]][0] & 0xf0 ) ? TRUE : FALSE;
    if( uiExTable )
        str = GetOSDString( osd_font_mode, setup_item[setup_pos[SETUP_ML1]][0][1] );
    else
    #endif
    str = _OsdMessegeFont1[osd_font_mode][setup_item[setup_pos[SETUP_ML1]][0][1]];

    //2006-06-29, mimitsai add for not redraw setup Icon page.
	if(reDrawSetupIconPage ==0)
	{
		osd_draw_rect( 0, 0, SETUP_WID, ICON_BG_HEI, setupBGcolorH);//rect
		reDrawSetupIconPage =1;
	}
	else 
	{
		if(pageIndex == setup_max_icon-1)
		{
			osd_draw_rect( 4+9+(pageIndex-1)*90, 0, ICON_PAGE_WID, ICON_BG_HEI, setupBGcolorH);                
			osd_draw_rect( 4+9+(pageIndex  )*90, 0, ICON_PAGE_WID, ICON_BG_HEI, setupBGcolorH);                
			osd_draw_rect( 4+9+(          0)*90, 0, ICON_PAGE_WID, ICON_BG_HEI, setupBGcolorH);		
		}
		else if(pageIndex == 0)
		{
			osd_draw_rect( 4+9+(setup_max_icon-1)*90, 0, ICON_PAGE_WID, ICON_BG_HEI, setupBGcolorH);                
			osd_draw_rect( 4+9+(pageIndex       )*90, 0, ICON_PAGE_WID, ICON_BG_HEI, setupBGcolorH);                
			osd_draw_rect( 4+9+(pageIndex+1     )*90, 0, ICON_PAGE_WID, ICON_BG_HEI, setupBGcolorH);		
		}
		else
		{
			osd_draw_rect( 4+9+(pageIndex-1)*90, 0, ICON_PAGE_WID, ICON_BG_HEI, setupBGcolorH);                
			osd_draw_rect( 4+9+(pageIndex  )*90, 0, ICON_PAGE_WID, ICON_BG_HEI, setupBGcolorH);                
			osd_draw_rect( 4+9+(pageIndex+1)*90, 0, ICON_PAGE_WID, ICON_BG_HEI, setupBGcolorH);		
		}
	}

	// draw icon string
	if(pageIndex == 0)
		osd_DrawString_ori(8, 2*SETUP_BTN_HEIGHT+2, str, setupFcolorT, setupBGcolorT);
	if(pageIndex == 1)
		osd_DrawString_ori(14, 2*SETUP_BTN_HEIGHT+2, str, setupFcolorT, setupBGcolorT);
	if(pageIndex == 2)
		osd_DrawString_ori(19, 2*SETUP_BTN_HEIGHT+2, str, setupFcolorT, setupBGcolorT);
	if(pageIndex == 3)
		osd_DrawString_ori(6, 2*SETUP_BTN_HEIGHT+2, str, setupFcolorT, setupBGcolorT);
	if(pageIndex == 4)
		osd_DrawString_ori(9, 2*SETUP_BTN_HEIGHT+2, str, setupFcolorT, setupBGcolorT);
	if(pageIndex == 5)
		osd_DrawString_ori(15, 2*SETUP_BTN_HEIGHT+2, str, setupFcolorT, setupBGcolorT);
	
	// draw icon botton backgroud
	osd_draw_rect( 4+9+pageIndex*90  , 0                          , ICON_PAGE_WID,     ICON_BG_HEI, setupBGcolorIG);                
    osd_draw_rect( 4+9+pageIndex*90  , ICON_BG_HEI                , ICON_PAGE_WID, ICON_STR_BG_HEI, setupBGcolorTTB); 
    osd_draw_rect( 4+9+pageIndex*90  , ICON_BG_HEI+ICON_STR_BG_HEI, ICON_PAGE_WID,             9+2, setupBGcolorBTB);  
	// draw icon botton backgroud outline
	osd_DrawLine(  4+9+pageIndex*90                , 0, 4+9+ICON_PAGE_WID+pageIndex*90  ,                               0, setupBGcolorSL, 1); // line top
	osd_DrawLine(  4+9+pageIndex*90                , 0, 4+9+pageIndex*90                , ICON_BG_HEI+ICON_STR_BG_HEI+9+2, setupBGcolorSL, 1); // line left
	osd_DrawLine(  4+9+ICON_PAGE_WID-2+pageIndex*90, 0, 4+9+ICON_PAGE_WID-2+pageIndex*90, ICON_BG_HEI+ICON_STR_BG_HEI+9+2, setupBGcolorSL, 1); // line right

	// draw icon bar or setupIcon
    for(i=0; i<setup_max_icon; i++)
		osd_DrawIcon( i*11 + 5, 9-3, setup_item[i][0][2], setup_item[setup_pos[SETUP_ML1]][0][2]); 
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
//#ifdef SCALER_6500     
 //   UINT8   Page_Shrink=0;       //caoh 20060430 mark
//#endif 
    yStart = 0;


    //for setup_level = 1, left/right walking on page(1st) level, just list all items of this page
    if(((setup_pos[SETUP_ML2] == 0) && (setup_pos[SETUP_ML0] == SETUP_ML1))
        #ifdef USE_SETUP_ITEM_ENABLE_FLAG// for setup_level from 3 to 2, change the color of disable item,added by chenzhao on 2005-3-31 16:5  
        ||((setup_pos[0] == SETUP_ML2) && (setup_last_pos[0] == SETUP_ML3))
        #endif
        ||setup_refresh) 
    {            
        //clear level 2 area
		osd_draw_rect(4+9+2+1, ICON_BG_HEI+ICON_STR_BG_HEI+9+2, CONTENT_BG_WID/2, ITEM_BG_HEI, setupBGcolorL2);

        //clear level 3 area
        #ifndef SHOW_SETUPMENU_SETUP//denghangao 20040929
 		osd_draw_rect(4+9+2+(ITEM_BG_WID/2) , ICON_BG_HEI+ICON_STR_BG_HEI+9+2, ITEM_BG_WID/2, ITEM_BG_HEI, setupBGcolorL3);
        #endif
		xStart 	= SETUP_MENU_XSTART;
        xLen 	= SETUP_SUB_XSTART-SETUP_MENU_XSTART-1;
        setup_itemType= SETUP_itemNormal;
        
        for(i=1; i<=MAX_PAGE_ITEM; i++)
        {
        	if((setup_item[setup_pos[1]][i][0]!=SET_NE)&&(setup_item[setup_pos[1]][i][0]!=SET_SPACE))
        	{
            	#ifdef SCALER_6500    //helm for scaler 050707
            	yStart = SETUP_MENU_YSTART + i /*- Page_Shrink*/;  //caoh mark 2006/04/30          
            	#else
            	yStart = SETUP_MENU_YSTART + i;
            	#endif
            	
            	id = setup_item[setup_pos[SETUP_ML1]][i][1];
                #ifdef USE_SETUP_ITEM_ENABLE_FLAG //added by chenzhao on 2005-3-31 16:4  
                if((SETUP_VA_NONE!=setup_item[setup_pos[SETUP_ML1]][i][MAX_ITEM_SEL+1])
                      &&(0==setup_VA_EN[setup_item[setup_pos[SETUP_ML1]][i][MAX_ITEM_SEL+1]]))
                    setup_itemType = SETUP_itemDisnable;

                #ifdef SUPPORT_HD_RESOLUTION
                else if((SETUP_VA_NONE!=setup_item[setup_pos[SETUP_ML1]][i][MAX_ITEM_SEL+1])
                      &&(2==setup_VA_EN[setup_item[setup_pos[SETUP_ML1]][i][MAX_ITEM_SEL+1]])) 
                    setup_itemType = SETUP_itemHided;
                #endif   
                
                else
                    setup_itemType= SETUP_itemNormal;
                #endif//USE_SETUP_ITEM_ENABLE_FLAG added by chenzhao on 2005-3-31 16:4  

               /* #ifdef SCALER_6500  //helm 050628
                    UINT8 itemMode, itemType;
                    itemType = setup_item[setup_pos[SETUP_ML1]][i][1];
                    itemMode = setup_item[setup_pos[SETUP_ML1]][i][2];
                    if ((itemType == STR_SPHE6500_FMT ||\
                         itemType == STR_OS_SCALER_576P)&& itemMode!=HDVD_MOD)//caoh 20060428
                        {Page_Shrink++; }
                    else
                #endif*/ 
                //caoh mark 2006/04/30                
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
 		osd_draw_rect(4+9+2+(ITEM_BG_WID/2) , ICON_BG_HEI+ICON_STR_BG_HEI+9+2, ITEM_BG_WID/2, ITEM_BG_HEI, setupBGcolorL3);

        xStart 	= SETUP_MENU_XSTART;
        xLen 	= SETUP_SUB_XSTART-SETUP_MENU_XSTART-1;
            
        //unmark last located item
        if(setup_last_pos[SETUP_ML2] != 0)
        {
            #ifdef SCALER_6500 //helm for 6500 scaler 050707
            yStart = setup_Check_PageL2_Ystart_Addr( setup_last_pos[SETUP_ML2]);
            #else
            yStart = SETUP_MENU_YSTART + setup_last_pos[SETUP_ML2];
            #endif
            
            id = setup_item[setup_last_pos[SETUP_ML1]][setup_last_pos[SETUP_ML2]][1];
            setup_itemType= SETUP_itemNormal;
            setup_draw_item(xStart, yStart, xLen, id, setup_itemType, setup_item[setup_last_pos[SETUP_ML1]][setup_last_pos[SETUP_ML2]][0]);     // 2005/03/29 yltseng
        }

        // mark current located item
        if(setup_pos[SETUP_ML2] != 0)
        {
            #ifdef SCALER_6500	 //helm for 6500 scaler 050707
            yStart = setup_Check_PageL2_Ystart_Addr( setup_pos[SETUP_ML2]);     
            #else
            yStart = SETUP_MENU_YSTART + setup_pos[SETUP_ML2];
            #endif  
                 
            id = setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1];
            setup_itemType= SETUP_itemMark;
            setup_draw_item(xStart, yStart, xLen, id, setup_itemType, setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][0]);       // 2005/03/29 yltseng
        }
/*
        //draw arrow
        if((setup_item[setup_pos[1]][setup_pos[2]][0]!=SET_SH)&&(setup_item[setup_pos[1]][setup_pos[2]][0]!=SET_LINK))
        {
            osd_DrawString(SETUP_SUB_XSTART-1, yStart, Ch_arrorR, setupFcolorAL2, setupBGcolorAL2);
        }
*/
    }

    // for setup_level from 2 to 3, change the color of selected item
    if((setup_pos[0] == SETUP_ML3) && (setup_last_pos[0] == SETUP_ML2))
    {
                xStart = SETUP_MENU_XSTART;
        xLen = SETUP_SUB_XSTART-SETUP_MENU_XSTART-1;
        
        #ifdef SCALER_6500  //helm for 6500 scaler 050707
        yStart = setup_Check_PageL2_Ystart_Addr( setup_pos[SETUP_ML2]);
        #else
        yStart = SETUP_MENU_YSTART + setup_pos[SETUP_ML2];
        #endif
        
        id = setup_item[setup_pos[1]][setup_pos[2]][1];
        setup_itemType = SETUP_itemSelected;
        setup_draw_item(xStart, yStart, xLen, id, setup_itemType, setup_item[setup_pos[1]][setup_pos[2]][0]);                           // 2005/03/29 yltseng

/*
        //draw arrow
        osd_DrawString(SETUP_SUB_XSTART-1, yStart, Ch_arrorR, setupFcolorAL3, setupBGcolorAL3);
*/        
    }
}

//====================================================================

UINT32 setup_GetFuncItemPosition()      // 2005/04/11 yltseng
{
    UINT32 i;
    for( i = 2; i < MAX_ITEM_SEL; i++ )
    {   
		if( !setup_item[setup_pos[1]][setup_pos[2]][i] )
            break;
    }
    if( setup_pos[2] + i > 11 )
        i = 11 - i;
    else
        i = setup_pos[2];
    return i;
}

void setup_ShowPageL3(void)
{
    int         i;
    BYTE    xStart, yStart, xLen;//, xOffset, fColor, bgColor, upDown;
    UINT8   itemType, itemSel, Get_id; //helm for get DRM id 050622
        
    itemType = setup_item[setup_pos[1]][setup_pos[2]][0];
    Get_id = setup_item[setup_pos[1]][setup_pos[2]][1]; //helm 050622

    xStart = SETUP_SUB_XSTART;
    xLen = SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2;
    
    //for setup_level = 2, up/down walking on item(2nd) level, just list all selection of this item 
    if(setup_pos[0] == SETUP_ML2)
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

                    #ifdef SUPPORT_HD_RESOLUTION  // This trick for HD. When HD, the STR_OS_PAL60 and STR_OS_AUTO are hidded.
                                                                       // by robert.chang, 2006-07-19
                    if((GET_TV_RESOLUTION()  == HD_720) || (GET_TV_RESOLUTION()  == HD_1080)) {
                        if((setup_item[setup_pos[1]][setup_pos[2]][1]==STR_OS_TV_SYS) && ((id==STR_OS_PAL60)||(id==STR_OS_AUTO)))
                            setup_itemType = SETUP_itemHided;
                    }    
                    #endif

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
    if((setup_pos[0] == SETUP_ML3) && (setup_last_pos[0] == SETUP_ML2))
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
            
                    #ifdef SUPPORT_HD_RESOLUTION  // This trick for HD. When HD, the STR_OS_PAL60 and STR_OS_AUTO are hidded.
                                                                       // by robert.chang, 2006-07-19                    
                    if((GET_TV_RESOLUTION()  == HD_720) || (GET_TV_RESOLUTION()  == HD_1080)) {
                        if((setup_item[setup_pos[1]][setup_pos[2]][1]==STR_OS_TV_SYS) && ((id==STR_OS_PAL60)||(id==STR_OS_AUTO)))
                            setup_itemType = SETUP_itemHided;
                    }    
                    #endif
            
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

                        #ifdef SUPPORT_HD_RESOLUTION   // This trick for HD. When HD, the STR_OS_PAL60 and STR_OS_AUTO are hidded.
                                                                            // by robert.chang, 2006-07-19
                        if((GET_TV_RESOLUTION()  == HD_720) || (GET_TV_RESOLUTION()  == HD_1080)) {
                            if((setup_item[setup_pos[1]][setup_pos[2]][1]==STR_OS_TV_SYS) && ((id==STR_OS_PAL60)||(id==STR_OS_AUTO)))
                                setup_itemType = SETUP_itemHided;
                        }    
                        #endif
                        
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

#define CUST_WID			(576)
#define CUST_HEI			(360)
#define TAB_BG_HEI			(40)

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
		osd_draw_rect( 0    , 0                              ,       CUST_WID,                     CUST_HEI, setupBGcolorH);
		osd_draw_rect( 4    ,     TAB_BG_HEI, CONTENT_BG_WID,       CUST_HEI-TAB_BG_HEI-4, setupBGcolorBB);
		osd_draw_rect( 4+9+2, TAB_BG_HEI+9+2,    ITEM_BG_WID, CUST_HEI-TAB_BG_HEI-(4+9)*2, setupBGcolorB);

		osd_DrawLine(4+9              ,  TAB_BG_HEI+9, 4+9              ,   CUST_HEI-9-4, setupBGcolorSL, 1); // line left
		osd_DrawLine(4+9+ITEM_BG_WID+2,  TAB_BG_HEI+9, 4+9+ITEM_BG_WID+2,   CUST_HEI-9-4, setupBGcolorSL, 1); // line right
		osd_DrawLine(4+9              ,  TAB_BG_HEI+9, 4+9+ITEM_BG_WID+2,  TAB_BG_HEI+9, setupBGcolorSL, 1); // line top
		osd_DrawLine(4+9              , CUST_HEI-9-4-2, 4+9+ITEM_BG_WID+2, CUST_HEI-9-4-2, setupBGcolorSL, 1); // line botton

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
/*
        //draw ">>" between located item and it's corresponding selection area
        if((setup_item[setup_pos[1]][setup_pos[2]][0]!=SET_SH)&&(setup_item[setup_pos[1]][setup_pos[2]][0]!=SET_LINK))
        {
            osd_DrawString(SETUP_SUB_XSTART-1, yStart, Ch_arrorR, setupFcolorAL2, setupBGcolorAL2);
        }
*/
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
/*
        osd_DrawString(SETUP_SUB_XSTART-1, yStart, Ch_arrorR, setupFcolorAL3, setupBGcolorAL2);
*/
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
    if(setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1]!=STR_OS_RATING)
      #ifdef AUTO_LOAD_MODE_SETUP //DENGHG ADD FOR PHILIPS 2005-11-15 05:51     
      &&(setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1]!=STR_OS_MODE)
#endif
    setup_ShowCUSTMMsg();
}
//====================================================================


void setup_ShowCUSTMMsg(void)
{
    BYTE    buf[40];
    BYTE    *pVersion;
#ifdef DVD_SERVO
    extern const UINT8 ServoVersion[];
#endif
    extern const UINT8 KernelVersion[];     // moved to libkern.a, leochen 2004/4/19 09:43¤U¤È
    int i=0;

    coordinate start;
    start.x = 20;
    start.y = 10;
    osd_draw_string(&start, "CUSTOM PAGE", 5, 8, 0, 0);

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
    osd_DrawString(SETUP_SUB_XSTART+6, SETUP_MENU_YSTART+2, buf,setupFcolorCS, setupBGcolorCS);

#ifdef DVD_SERVO
    //ServoVersion[16]=0; can't write to const data
    printf("ServoVersion %s\n", ServoVersion);
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART, ServoVersion, setupFcolorCN, setupBGcolorCN);
#endif

    buf[8]= 0;
    psprintf(buf, "%s", MPEG_UI_VERSION);   
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+1, buf, setupFcolorCN, setupBGcolorCN);
    osd_DrawString(SETUP_SUB_XSTART+4, SETUP_MENU_YSTART+1, KernelVersion, setupFcolorCN, setupBGcolorCN);
 
    //add build version
    psprintf(buf, "%s", VERSION_STRING);
    osd_DrawString(SETUP_SUB_XSTART+8, SETUP_MENU_YSTART+1, buf, setupFcolorCN, setupBGcolorCN);
   
    psprintf(buf, "%02x%03x", (regs0->stamp & 0xff),get_iop_b_status()); //2004/11/30 ycwen
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+2, buf, setupFcolorCN, setupBGcolorCN);

//----show SDRAM, System clock, and update information----------------------------------------------
    // show update date and week
    psprintf(buf, "%s", UPDATE_DATE);
    osd_DrawString(SETUP_MENU_XSTART+1, SETUP_MENU_YSTART-1, buf, setupFcolorCN, 1);

    psprintf(buf, "%s", UPDATE_WEEK);
		osd_DrawString(SETUP_MENU_XSTART+8+1+1, SETUP_MENU_YSTART-1, buf, setupFcolorCN, 1);

    //show SDRAM information
    psprintf(buf, "%s", SDRAM_SIZE);
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART-1, buf, setupFcolorCN, 1);
    psprintf(buf, "%s", SDRAM_BUS);
    osd_DrawString(SETUP_SUB_XSTART+8, SETUP_MENU_YSTART-1, buf, setupFcolorCN, 1);

    //show system clock
    extern int get_sysclk;
    psprintf(buf, "SC:%d", (get_sysclk*675/100));
    osd_DrawString(SETUP_MENU_XSTART+1, SETUP_MENU_YSTART, buf, setupFcolorCN, setupBGcolorCN);
//---------------------------------------------------------------------------------------------------

#ifdef CUSTM_MENU_REVISE
    const char *str;
    id = setup_item[6][3][REGION_NUM+2];
    str = _OsdMessegeFont1[osd_font_mode][id];
    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+3, str, setupFcolorCN, setupBGcolorCN);
#endif     
}
//====================================================================
#ifdef SETUP_PAL_ADJUST_IN_INDIGO_UI   // zxb 2006-8-29 14:15
//the function is used to redraw setup menu;
void setup_force_showPage()
{
  	reDrawSetupIconPage=0;    	    
    setup_ShowPageL1();
    setup_refresh = 1;
    setup_ShowPageL2();
    setup_refresh = 0;
    setup_ShowPageL3();
    return;
}
#endif

