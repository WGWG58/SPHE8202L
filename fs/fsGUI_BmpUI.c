/**************************************************************
** FILE
** fsGUI_BmpUI.c
**
** DESCRIPTION
** On the base of fsGUI_new.c, build a new GUI with bmp for MP3/JPEG/GAME.
**
**
**   Creator: zhaoyanhua
**   Date:    2004-6-3 10:17
****************************************************************/



#include "global.h"
#include "func.h"
#include "memmap.h"
#include "util.h"
#include "graph.h"
#include "memcfg.h"
#include "framebuf.h"
#include "macro.h"
#include "stc.h"
#include "cfont.h"
#include "vfdfunc.h"
#include "osd.h"
#include "image.h"
#include "nesinit.h"
#include "fs96602.h"
#include "fsNAV.h"
#include "fsGUI.h"
#include "fsGUI1.h"

#include "fsGUI1.h"
//#include "fsGUI_new.h"

#ifdef JPG_OLD_PARSER_FLOW
    #ifdef JPG_EFFECT
    #include "jpegeffect.h"
    #endif
#else
    #include "pic_effect.h"
#endif

#ifdef FS_BMP_GUI
#include "FrameBuf_BmpUI.h"
#include "fsGUI_Palette.h"
#include "fsGUI_Bmp.h"
#include "fsGUI_BmpUI.h"

const BITMAP_LAYOUT g_aBitmapLayout[] =
{
    //absolute postion
    {0,   0,   720,     0,   0,   1}, //bg.bmp top line                 //0
    {0,   171,   720,     0,   1,   1}, //bg.bmp middle line                 //0
    {0,   382,   720,     0,   2,   1}, //bg.bmp bottom line              //1
    {54,  27,    0,     0,   3,   1}, //tab_bar2-1.bmp                  //2
    {244, 35,    0,     0,   7,   0},//MP3_icon_L.bmp                   //3
    {348, 35,    0,     0,   8,   0},//JPG_icon_L.bmp                   //4
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
    {555, 34,    0,     0,   9,   0},//VIDEO_icon_L.bmp                 //5
    {454, 33,    0,     0,   10,   0},//GAME_icon_L.bmp                  //6
#else 
    {449, 36,    0,     0,   9,   0},//VIDEO_icon_L.bmp                 //5
    {560, 35,    0,     0,   10,   0},//GAME_icon_L.bmp                  //6
#endif    
    {78,  76,    0,     0,   11,  1},//playing_bar_3_1.bmp              //7
    {635, 76,    0,     0,   12,  1},//playing_bar_3_3                  //8
    
#ifdef	GPS_MP3_UI//frank.huang 050923
    {99,  99,    0,     0,   14,  0},//animation1.bmp                   //9
    {99,  99,    0,     0,   15,  0},//animation2.bmp                   //10
#else
    {99,  84,    0,     0,   14,  0},//animation1.bmp                   //9
    {99,  84,    0,     0,   15,  0},//animation2.bmp                   //10
#endif

    //opsite postion. when use these bmp, must add its start position
    {0,    0,    105,     1,    4,  1},//tab_bar2-2.bmp                   //11
    {0,    0,    105,     1,    5,  0},//tab_bar_shine.bmp                //12
    {0,    0,    105,     1,    6,  1},//tab_bar_down.bmp                 //13
    {0,    0,    0,     0,   13,  1},//playing_bar_3_2.bmp              //14
    {0,    0,    0,     0,   16,  1},//FILE bg Cornre LT                //15
    {0,    0,    0,     0,   17,  1},//FILE bg Cornre RT                //16
    {0,    0,    0,     0,   18,  1},//FILE bg Cornre LB                //17
    {0,    0,    0,     0,   19,  1},//FILE bg Cornre RB                //18
    {0,    0,    0,     0,   20,  0},//MP3_icon_S.bmp                   //19
    {0,    0,    0,     0,   21,  0},//JPEG_icon_S.bmp                  //20
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
    {0,    0,    0,     0,   22,  1},//Game_icon_S.bmp                 //22
    {0,    0,    0,     0,   23,  0},//Video_icon_S.bmp                  //23
#else
    {0,    0,    0,     0,   22,  0},//Video_icon_S.bmp                 //22
    {0,    0,    0,     0,   23,  1},//Game_icon_S.bmp                  //23
#endif    
    {0,    0,    0,     0,   24,  1},//FileBg10_0.bmp                   //23
    {0,    0,    0,     0,   25,  1},//FileBg10_1.bmp                   //24
    {0,    0,    0,     0,   26,  1},//FileBg10_2.bmp                   //25
    {0,    0,    0,     0,   27,  1},//FileBg10_3.bmp                   //26
    {0,    0,    0,     0,   28,  1},//FileBg10_4.bmp                   //27
    {0,    0,    0,     0,   29,  1},//FileBg10_5.bmp                   //28
    {0,    0,    0,     0,   30,  1},//FileBg10_6.bmp                   //29
    {0,    0,    0,     0,   31,  1},//FileBg10_7.bmp                   //30
    {0,    0,    0,     0,   32,  1},//FileBg10_8.bmp                   //31
    {0,    0,    0,     0,   33,  1},//FileBg10_9.bmp                   //32
    {0,    0,    0,     0,   34,  1},//folder_icon                      //33
#ifdef GPS_MP3_UI//frank.huang 050915
    {0,    0,    0,     0,   35,  1},//folder_icon                      //34
    {0,    0,    0,     0,   36,  1},//PATH_INFO_BACKGROUND_L 			//35
    {0,    0,    0,     0,   37,  1},//PATH_INFO_BACKGROUND_R           //36
    {89,   65,    0,     0,   38,  1},//MP3_PAGE_ICON           			//37
    {89,   65,    0,     0,   39,  1},//JPG_PAGE_ICON           			//38
    {89,   65,    0,     0,   40,  1},//VIDEO_PAGE_ICON           		//39
    {0,   0,   32*PER_PAGE,     1,   41,  1},//VIDEO_PAGE_ICON           		//40
    {0,   0,   0,     0,   42,  1},//ARROW_U           		//41
    {0,   0,   0,     0,   43,  1},//ARROW_D           		//42
    {0,   0,   0,     0,   44,  1},//SLIDER_BLOCK           		//43
    {0,   0,   0,     0,   45,  1},//SLIDER_BLOCK_U           		//44
    {0,   0,   0,     0,   46,  1},//SLIDER_BLOCK_D           		//45
#endif
};


/* 
 * Description:
 *      Draw all the buttons,including background and icon
 * NOTE:
 *      This function has be defined in fsGUI_pub.c
 *     
 *      we only modify the codes of DrawButton. 
 *
 *Creater:
 *	feeling
 *Date:
 *	2004-06-08
 */
void DrawButton(void)
{
	BYTE iBtnState = 0;

#ifdef AUDIO_SHOW_SAVER
    	if (bDisableGUI) return;
#endif

    //draw the left and right edge of button array 
    FSGUI_LayoutBmp(LAY_TAB_BAR2_1);

    //draw the backgroud
    FSGUI_DrawBackGround(fsArea[FS_AREA_BUTTONBACKGROUND].xStart,
		fsArea[FS_AREA_BUTTONBACKGROUND].yStart,
		fsArea[FS_AREA_BUTTONBACKGROUND].xSize,
		fsArea[FS_AREA_BUTTONBACKGROUND].ySize,
		LAY_TAB_BAR2_2);

    //draw the buttons
	
	//draw MP3 button
	#ifdef USE_FSGUI_TO_PLAY_CD//frank.huang add 051014 in order not to show button in CD-FSUI
	if(cd_type_loaded==CDDA)
		return;
	#endif
	
	if (pFsJpeg->gifsMP3Count) 
	{
		if (pFsJpeg->ControlArea == CNT_AREA_MP3BUTTON)
			iBtnState = HL_STATE;
		else if (pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
			iBtnState = DOWN_STATE;
		else
			iBtnState = UP_STATE;
		
		FSGUI_DrawOneButton(FS_FUNC_MP3,iBtnState);		    
	}
	else
	{
		FSGUI_DrawOneButton(FS_FUNC_MP3, UP_STATE);	
	}
	

	//draw JPEG button
	if (pFsJpeg->gifsJPEGCount)
	{
		if (pFsJpeg->ControlArea == CNT_AREA_JPEGBUTTON)
			iBtnState = HL_STATE;
		else if (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
			iBtnState = DOWN_STATE;
		else
			iBtnState = UP_STATE;
		
		FSGUI_DrawOneButton(FS_FUNC_JPEG, iBtnState);		    
	}
	else
	{
		FSGUI_DrawOneButton(FS_FUNC_JPEG, UP_STATE);	
	}


#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
	//draw GAME button
	if (pFsJpeg->gifsGAMECount)
	{
		if (pFsJpeg->ControlArea == CNT_AREA_GAMEBUTTON)
			iBtnState = HL_STATE;
		else if (pFsJpeg->gifsFuncBtn == FS_FUNC_GAME)
			iBtnState = DOWN_STATE;
		else
			iBtnState = UP_STATE;
		
		FSGUI_DrawOneButton(FS_FUNC_GAME, iBtnState);		    
	}
	else
	{
		FSGUI_DrawOneButton(FS_FUNC_GAME, UP_STATE);	
	}

#endif//#ifdef SUPPORT_NESGAME

#ifdef SUPPORT_FILE_SYSTEM_MODE
	//draw video button
	if (pFsJpeg->gifsOtherCount)
	{
		if (pFsJpeg->ControlArea == CNT_AREA_OTHERBUTTON)
			iBtnState = HL_STATE;
		else if (pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)
			iBtnState = DOWN_STATE;
		else
			iBtnState = UP_STATE;
		
		FSGUI_DrawOneButton(FS_FUNC_OTHER,iBtnState);		    
	}
	else
	{
		FSGUI_DrawOneButton(FS_FUNC_OTHER, UP_STATE);	
	}
#endif
	FSGUI_ShowBtnTitle();
	
#ifdef DISP_REGION_BOTTOM
	//if define OSD_BMP_DISPLAY, Jpeg Thumnail state display should show in top,
	//and quit Thumbnail state,display should show in bottom,so note jpeg mode here.
	if (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
	    pFsJpeg->g_nJpegMode = JPEG_NORMAL_MODE;
#endif
}//end DrawButton


/* 
 * Description:
 *      draw the bmp defined in g_aBitLayout[] according to the index.
 *
 * INPUT:
 *      LayoutIndex --> index of g_aBitMapLayout[]
 *
 */
void FSGUI_LayoutBmp(UINT8 LayoutIndex)
{
    const BITMAP_LAYOUT* pLayout  =  &g_aBitmapLayout[LayoutIndex];
   
    //only draw bmp no need repeat
    if ((pLayout->uiXRepeat != 0) 
       ||(pLayout->uiYRepeat != 0))
        return;
    
    FrameBuf_DrawBmp(pLayout->uiXPos, pLayout->uiYPos, 
                     g_aBitmap[pLayout->uiIndex],
                     g_aPalette[pLayout->uiPalette]);
    
}

/* 
 * Description:
 *      draw the bmp defined in g_aBitmapLayout[] according to the index.
 *
 * NOTE:
 *      the postion of the bmp is not fixed ,it can be variable.
 *    
 * INPUT:
 *      xStart      --> the bmp x position
 *      yStart      ---> the bmp y position
 *      LayoutIndex --> index of g_aBitmapLayout[]
 *
 */
void FSGUI_LayPosVariableBmp(UINT16 xStart, UINT16 yStart,UINT8 LayoutIndex)
{
    const BITMAP_LAYOUT* pLayout  =  &g_aBitmapLayout[LayoutIndex];
   
    //only draw bmp no need repeat
    if ((pLayout->uiXRepeat != 0) 
       ||(pLayout->uiYRepeat != 0))
        return;
    
    //the position of the bmp is fixed ,can not draw with this function.
    if ((pLayout->uiXPos != 0) || (pLayout->uiYPos != 0))
        return;
    
    FrameBuf_DrawBmp(xStart, yStart, 
                     g_aBitmap[pLayout->uiIndex],
                     g_aPalette[pLayout->uiPalette]);
  
}


/*
 *  Description:
 *      Draw a background by repeating the same bmp in Framebuf
 *  NOTE:
 *      the bmp is a bmp of Line generally,this only for a line,which width is 1 piexl
 *
 *  INPUT:   
 *      xStart  -->  the background x start position
 *      yStart  -->  the background y start position
 *      xRepeat  --> bmp repeat times in x axis
 *      yRepeat -->  bmp repreat times in y axis
 *      LayoutIndex --> index of g_aBitMapLayout[]
 * Creator: zhaoyanhua
 * Date: 2004-6-3 10:07
 * Update:  suqiaoli 2004-6-8 
 * Update:  yltseng  2004-6-23 
 */
void FSGUI_DrawBackGround(UINT16 xStart, UINT16 yStart, UINT16 xRepeat, UINT16 yRepeat,UINT8 LayoutIndex)
{
    const BITMAP_LAYOUT* pLayout   = &g_aBitmapLayout[LayoutIndex];
    const UINT8 *bmp               = g_aBitmap[pLayout->uiIndex];
    const YCrCb_COLOR *Palette     = g_aPalette[pLayout->uiPalette];
    
    int i               = 0;
    int j               = 0;
    int k               = 0;
    const BYTE *pBmp    = bmp + 3;
    int iBmpWidth       = bmp[0];
    int iBmpHeigth      = bmp[1];

    UINT32  uiYBase     = SDRAM_BASE + 1024 * REF0_LUMA + xStart;
    UINT32  uiCBase     = SDRAM_BASE + 1024 * REF0_CHROMA + 2 * ( xStart >> 1 );

//wanghaoying 2005-9-28 19:08 moved here.
#ifdef GPS_MP3_UI
	if(xRepeat<=1)//frank.huang 050922 add for when(xREPEAT==1) show  BackGround
	{
        const YCrCb_COLOR *pPalette     = g_aPalette[pLayout->uiPalette];
	    UINT16 uiCurX;
        UINT16 uiCurY;
        printf("uiWidth=%d\n",iBmpWidth);
	    printf("xRepeat=%d\n",xRepeat);
        for (j = 0, uiCurY = yStart; j < yRepeat; j++, uiCurY += iBmpHeigth )
        {
            for (i = 0, uiCurX = xStart; i < xRepeat; i++, uiCurX += iBmpWidth )
            {
                FrameBuf_DrawBmp( uiCurX, uiCurY, bmp,pPalette);
            }
        }
    }
	else
#endif
	{
        for (j = 0; j < iBmpHeigth; j++)
        {
            BYTE*   pY  = (BYTE*)   ( uiYBase + OFFSET_Y( yStart + j ) );
            UINT16* pC  = (UINT16*) ( uiCBase + OFFSET_C( (yStart + j) >> 1 ) );
            
            //draw pixel start from x axis
            for (i = 0; i < iBmpWidth; i++)
            {         
                int ColorIndex = *pBmp++;            
                if (ColorIndex == 0)    //index 0 is transparent
                    continue;
                
                YCrCb_COLOR PixelValue  = *(Palette+ColorIndex); 
                pY[i]                   =   PixelValue.uiY;
                pC[i>>1]                =   PixelValue.uiCrCb;
            }
            
            //one bmp in x axis has been drawn. 
            //Its data has been saved in pY[], and pC[]
            //so we can draw the other same bmp(repeat) with the same pY,pCrcb
           BYTE* pNextY  = pY;        
            for( k = 1; k < xRepeat; k++ )
            {
                pNextY += iBmpWidth;
                UINT16* pNextC = pC + ( ( iBmpWidth * k ) >> 1 );
                            
                for( i = 0; i < iBmpWidth; i++ )
                {
                    pNextY[i]       = pY[i];
                    pNextC[i>>1]    = pC[i>>1];
                }
            }
        }
    }  
/*    
    int i = 0;
    int j = 0;
    
    const BITMAP_LAYOUT* pLayout = &g_aBitmapLayout[LayoutIndex];
    const UINT8 *pBmp = g_aBitmap[pLayout->uiIndex];
    const YCrCb_COLOR *pPalette     = g_aPalette[pLayout->uiPalette];
    
    UINT8 uiWidth   = pBmp[0];
    UINT8 uiHeight  = pBmp[1];
    UINT16 uiCurX;
    UINT16 uiCurY;
    
    for (j = 0, uiCurY = yStart; j < yRepeat; j++, uiCurY += uiHeight )
    {
        for (i = 0, uiCurX = xStart; i < xRepeat; i++, uiCurX += uiWidth )
        {
            FrameBuf_DrawBmp( uiCurX, uiCurY, pBmp,pPalette); 
        }
    }
*/    
}


/*
 * Description:
 *      draw one button according its type.
 * 
 * INPUT:
 *      type ---> FS_FUNC_MP3    NOTE: different type has different button icon.
 *                FS_FUNC_JPEG  
 *                FS_FUNC_GAME
 *                FS_FUNC_OTHERS
 
 *      state --> HL_STATE       //HL in this button
 *                DOWN_STATE    //now playing the type file
 *                UP_STATE     //has no HL and no playing file
 *
 *Creater:feeling
 *
 *Date:2004-06-08
 */
void FSGUI_DrawOneButton(BYTE type, BYTE state)
{
	#ifdef 	GPS_MP3_UI//frank.huang 050927 
		return;//don't show button in gps_mp3 ui
	#endif

    const BITMAP_LAYOUT* pBgLayout;
    UINT8  uiBgIndex = 0, uiIcnIndex = 0, uiBgYPos = 0;
    UINT16 uiBgXPos = 0;
//    return;

    //decide the backgroud line of the button,
    //according to which state it is, highlighted,pressed or normal
    switch(state)
    {
        case HL_STATE:
            uiBgIndex = LAY_TAB_BAR_SHINE;
            uiBgYPos = BTN_BG_HL_YPOS;
            break;
        case DOWN_STATE:
            uiBgIndex = LAY_TAB_BAR_DOWN;
            uiBgYPos = BTN_BG_DOWN_YPOS;
            break;
        case UP_STATE:
            uiBgIndex = LAY_TAB_BAR2_2;
            uiBgYPos = BTN_BG_UP_YPOS;
            break;
    }      
    pBgLayout = &g_aBitmapLayout[uiBgIndex];
    
    //decide the backgroud x y pos and icon on the button, 
    //according to which type it represents, mp3,jpg,vide,or game.
    switch(type)
    {
        case FS_FUNC_MP3:
            uiIcnIndex = LAY_MP3_ICON_L;
            uiBgXPos = MP3_BTN_BG_XPOS;
            break;
        case FS_FUNC_JPEG:
            uiIcnIndex = LAY_JPG_ICON_L;
            uiBgXPos = MP3_BTN_BG_XPOS + (FS_FUNC_JPEG - FS_FUNC_MP3) * BTN_BG_XOFFSET;
            break;
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
        case FS_FUNC_GAME:
            uiIcnIndex = LAY_GAME_ICON_L;
            uiBgXPos = MP3_BTN_BG_XPOS + (FS_FUNC_GAME - FS_FUNC_MP3) * BTN_BG_XOFFSET;
            break;
#endif //#ifdef SUPPORT_NESGAME
            
#ifdef SUPPORT_FILE_SYSTEM_MODE
        case FS_FUNC_OTHER:
            uiIcnIndex = LAY_VIDEO_ICON_L;
            uiBgXPos = MP3_BTN_BG_XPOS + (FS_FUNC_OTHER - FS_FUNC_MP3) * BTN_BG_XOFFSET;
            break;
#endif //#ifdef SUPPORT_FILE_SYSTEM_MODE
#ifdef SUPPORT_MIDI
	    case FS_FUNC_MIDI:
	        break;
#endif	    
    }//end switch(type)

    //draw the backgroud line and layout the icon
    FSGUI_DrawBackGround(uiBgXPos, uiBgYPos, 
    		   pBgLayout->uiXRepeat, pBgLayout->uiYRepeat,
                 uiBgIndex); //draw the backgroud
          

    FSGUI_LayoutBmp(uiIcnIndex);//layout the icon
    
}//end FSGUI_DrawOneButton

/*
 * Description:
 *      Draw a rect with four corner,including dir scroll and fiel scroll background
 * Note:
 *      use 10 section pic to draw file and dir background
 * 
 * INPUT:
 *      xStart  -->  the background x start position
 *      yStart  -->  the background y start position
 *      iWidth  -->  width of background
 *      iHeight -->  height of background
 *
 * Creator:  suqiaoli
 *
 * Data:2004-6-10 
 *
 */
void FSGUI_ShowBmpCornerRect(UINT16 xStart, UINT16 yStart,UINT16 iWidth, UINT16 iHeight)
{
    int i = 0;
    int xRepeat = 0;
    int yRepeat = 0;
    
    #define HLINE_WIDTH         22
    #define HLINE_HEIGHT        2
    #define VLINE_WIDTH         2
    #define VLINE_HEIGHT        259
    
    xRepeat = iWidth/RECT_BG_BMP_WIDTH;
    yRepeat = iHeight/RECT_BG_BMP_HEIGHT;
   
    //----Draw left line and right line
    
    //draw background with file_bg.bmp//frank.huang 050915 edit
    FSGUI_DrawBackGround(xStart,yStart,xRepeat,yRepeat,LAY_FILE_BG_10_0);//first section
    for (i = 0; i < PER_PAGE; i ++)//8 sections
    {
        FSGUI_DrawBackGround(xStart,yStart + 12 + FS_FILELIST_YSTEP * i ,xRepeat,yRepeat,LAY_FILE_BG_10_1 + i );
    }

    
    //-----DrawScroll
    //Draw 4 horizonal lines
    #ifdef	GPS_MP3_UI//frank.huang 050923
	FrameBuf_DrawLine(xStart - 2 , yStart + 10 , 2, iHeight+8, RECTLINE_Y,RECTLINE_CRCB );
    FrameBuf_DrawLine(xStart + DIR_AREA_XLEN , yStart + 10, 2, iHeight+8, RECTLINE_Y,RECTLINE_CRCB );
	FSGUI_DrawBackGround(xStart+2 ,yStart + 12 + iHeight ,xRepeat,yRepeat,LAY_FILE_BG_10_9);//last section
	FSGUI_LayPosVariableBmp(xStart - 2, yStart,LAY_FILE_BG_CORNER_LT);//LT
    FSGUI_LayPosVariableBmp(xStart + iWidth - 27 , yStart,LAY_FILE_BG_CORNER_RT);//RT
	FSGUI_LayPosVariableBmp(xStart - 2, yStart + iHeight+ 12,LAY_FILE_BG_CORNER_LB);//LB
    FSGUI_LayPosVariableBmp(xStart + iWidth - 27 , yStart + iHeight+ 9 ,LAY_FILE_BG_CORNER_RB);//RB
    FSGUI_DrawBackGround(xStart + iWidth - 27, yStart + 13, 1,32*PER_PAGE,SLIDER_BODY);

	FSGUI_LayPosVariableBmp(xStart + iWidth - 21 , yStart + 9 ,ARROW_U);//RB
	FSGUI_LayPosVariableBmp(xStart + iWidth - 21 , yStart + iHeight-5 ,ARROW_D);//RB
	
	#else//#ifdef	GPS_MP3_UI
	FrameBuf_DrawLine(xStart - 2 , yStart + 10 , 2, FILE_AREA_XLEN + 2, RECTLINE_Y,RECTLINE_CRCB );
    FrameBuf_DrawLine(xStart + DIR_AREA_XLEN , yStart + 10, 2, FILE_AREA_XLEN + 2, RECTLINE_Y,RECTLINE_CRCB );
    
    FSGUI_DrawBackGround(xStart ,yStart + 12 + FS_FILELIST_YSTEP * PER_PAGE ,xRepeat,yRepeat,LAY_FILE_BG_10_9);//last section
    //Draw four corner
    FSGUI_LayPosVariableBmp(xStart - 2, yStart,LAY_FILE_BG_CORNER_LT);//LT
    FSGUI_LayPosVariableBmp(xStart + iWidth - 8 , yStart,LAY_FILE_BG_CORNER_RT);//RT
    FSGUI_LayPosVariableBmp(xStart - 2, yStart + iWidth + 8,LAY_FILE_BG_CORNER_LB);//LB
    FSGUI_LayPosVariableBmp(xStart + iWidth - 8 , yStart + iWidth + 8 ,LAY_FILE_BG_CORNER_RB);//RB
    //-----DrawScroll
    //Draw 4 horizonal lines
    FrameBuf_DrawLine(xStart + DIR_AREA_XLEN + 2 , yStart + 10 ,  HLINE_WIDTH, HLINE_HEIGHT, RECTSCROLL_LINE_Y,RECTSCROLL_LINE_CRCB );
    FrameBuf_DrawLine(xStart + DIR_AREA_XLEN + 2, yStart + 32 ,  HLINE_WIDTH, HLINE_HEIGHT, RECTSCROLL_LINE_Y,RECTSCROLL_LINE_CRCB );
    FrameBuf_DrawLine(xStart + DIR_AREA_XLEN + 2, yStart + DIR_AREA_YLEN - 34 , HLINE_WIDTH, HLINE_HEIGHT, RECTSCROLL_LINE_Y,RECTSCROLL_LINE_CRCB );
    FrameBuf_DrawLine(xStart + DIR_AREA_XLEN + 2, yStart + DIR_AREA_YLEN - 12 , HLINE_WIDTH, HLINE_HEIGHT, RECTSCROLL_LINE_Y,RECTSCROLL_LINE_CRCB );
    
    //draw 1 vertical line
    FrameBuf_DrawLine(xStart + DIR_AREA_XLEN + 24 , yStart + 10 , VLINE_WIDTH, VLINE_HEIGHT, RECTSCROLL_LINE_Y,RECTSCROLL_LINE_CRCB );
    
    //draw 2 arrows
    DrawTriangle(xStart + DIR_AREA_XLEN + 8 , yStart + 23, 12, 6, 1, UPARROW_Y, UPARROW_CRCB); 
    DrawTriangle(xStart + DIR_AREA_XLEN + 8 , yStart + DIR_AREA_YLEN - 23 , 12, 6, 0, DOWNARROW_Y, DOWNARROW_CRCB); 
    #endif//#ifdef	GPS_MP3_UI
    
}

/*
 * FUNC : Clear the item in Rectangle with four corner.
 *        Main for:file icon,dir icon,file item,dir item.
 * 
 * INPUT:
 *        iIndex :   Area index.
 *        iItem  :   if iItem >= PER_PAGE, it means clear all items or dir icons ;
 *                   if iItem <  PER_PAGE, it means clear current item
 * Creator: Suqiaoli
 * Date: 2004-6-10
 */

void FSGUI_ClearArea(UINT16 iIndex,UINT16 iItem)
{
    int i;
    
    if ((pFsJpeg->gifsState == FS_STATE_JPEG) && (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG))
		return;
	
	//clear current file icon;
	if ((iIndex == FS_AREA_FILEICON) && (refresh_file_page==0))
	{
		FSGUI_DrawBackGround(fsArea[iIndex].xStart ,fsArea[iIndex].yStart + FS_FILELIST_YSTEP * pFsJpeg->file_current,fsArea[iIndex].xSize,1,LAY_FILE_BG_10_1 + pFsJpeg->file_current );
    }
	else if ((iIndex == FS_AREA_FILEICON) && (refresh_file_page == 1))
	{// clear all file icon
		for (i = 0;i < PER_PAGE;i ++)
        {
            FSGUI_DrawBackGround(fsArea[iIndex].xStart ,fsArea[iIndex].yStart + FS_FILELIST_YSTEP*i,fsArea[iIndex].xSize,1,LAY_FILE_BG_10_1 + i );
        }
	} 
	else if (iItem > PER_PAGE)
	{//clear all items or dir icons
		for (i = 0;i < PER_PAGE;i ++)
        {
            FSGUI_DrawBackGround(fsArea[iIndex].xStart  ,fsArea[iIndex].yStart + FS_FILELIST_YSTEP*i,fsArea[iIndex].xSize,1,LAY_FILE_BG_10_1 + i );
        } 
	}
	else //iItem <= PER_PAGE
	{//clear current item
		FSGUI_DrawBackGround(fsArea[iIndex].xStart , fsArea[iIndex].yStart + iItem * 32, fsArea[iIndex].xSize, 1,LAY_FILE_BG_10_1+iItem);
	}
}

#if 0
/*
 * Description:
 *      only for DIR and FILE RECT 
 *      according the file state, draw its item.
 *      1)when HL chaned from one file to another file, 
 *        must redraw last HL file, HL current file.
 *      2)when curent playing file changed ,must redraw 
 *         last playing file, make the current file be playing sate. 
 *
 * INPUT:   
 *      CurrentPos --->  this file position in DIR(FILE)RECT. It's value is 0~7 (if onepage has 8 fileitem).
 *      iState     --->  the file current state
 *                       HL_STATE       //HL in this button
 *                       PRESS_STATE    //now playing the type file
 *                       NONE_STATE     //has no HL and no playing file
 *      iType      --->  the file in DIR RECT 
 *                             or in FILE RECT
 *
 */
void FSGUI_UpdateItem(UINT16 CurrentPos, BYTE iState, BYTE iType)
{
   #if 0
    //according its iState select its backgroud bmp.
    //background start position according its iType and CurrentPos.
    if (iState == NONE_STATE)
        FrameBuf_DrawBackGround();
    else//HL_STATE / Press_STATE
        FrameBuf_DrawRect();
        
    //Show file item String
    FSGUI_ShowString();
    #endif
}

#endif

/*
 * Description:
 *      Draw file area scroll
 *
 * Creator:suqioali
 * Data:2004-6-15 
 *
 */
#ifdef GPS_MP3_UI//frank.huang 050923 add for GPS_MP3 SCOLL_BAR
void DrawScroll(void)
{
    int  x, y, xRepeat, yRepeat;
		
    x = fsArea[FS_AREA_SLOT].xStart;
    y = fsArea[FS_AREA_SLOT].yStart;
    xRepeat = 1;//fsArea[FS_AREA_SLOT].xSize;
    yRepeat = FS_DIRSCROLLLEN_YSIZE;//fsArea[FS_AREA_SLOT].ySize/FS_DIRSCROLLLEN_YSIZE;
    
    FSGUI_DrawBackGround(x,y,xRepeat,yRepeat,SLIDER_BODY);
	//FSGUI_DrawBackGround(x,y,xRepeat,yRepeat,LAY_BG_3_2);

}
/*
 * Description:
 *      Draw dir area scroll
 *
 * Creator:suqioali
 * Data:2004-6-15 
 *
 */
void DIR_DrawScroll(void)
{
    int  x, y, xRepeat, yRepeat;

    x = fsArea[FS_AREA_DIR_SLOT].xStart;
    y = fsArea[FS_AREA_DIR_SLOT].yStart;
   	xRepeat = 1;//fsArea[FS_AREA_SLOT].xSize;
    yRepeat = FS_DIRSCROLLLEN_YSIZE;//fsArea[FS_AREA_SLOT].ySize/FS_DIRSCROLLLEN_YSIZE;
    
    //FrameBuf_DrawRect(x, y, xSize, ySize,BLUE_Y, BLUE_CRCB);
    FSGUI_DrawBackGround(x,y,xRepeat,yRepeat,SLIDER_BODY);
}

#else//ifdef GPS_MP3_UI//frank.huang 050923

void DrawScroll(void)
{
    int  x, y, xRepeat, yRepeat;

    x = fsArea[FS_AREA_SLOT].xStart;
    y = fsArea[FS_AREA_SLOT].yStart;
    xRepeat = fsArea[FS_AREA_SLOT].xSize;
    yRepeat = fsArea[FS_AREA_SLOT].ySize/FS_DIRSCROLLLEN_YSIZE;
    
    //FrameBuf_DrawRect(x, y, xSize, ySize,BLUE_Y, BLUE_CRCB);//Draw rect
    FSGUI_DrawBackGround(x,y,xRepeat,yRepeat,LAY_BG_3_2);
}

/*
 * Description:
 *      Draw dir area scroll
 *
 * Creator:suqioali
 * Data:2004-6-15 
 *
 */
void DIR_DrawScroll(void)
{
    int  x, y, xRepeat, yRepeat;

    x = fsArea[FS_AREA_DIR_SLOT].xStart;
    y = fsArea[FS_AREA_DIR_SLOT].yStart;
    xRepeat = fsArea[FS_AREA_DIR_SLOT].xSize;
    yRepeat = fsArea[FS_AREA_DIR_SLOT].ySize/FS_DIRSCROLLLEN_YSIZE;
    
    //FrameBuf_DrawRect(x, y, xSize, ySize,BLUE_Y, BLUE_CRCB);
    FSGUI_DrawBackGround(x,y,xRepeat,yRepeat,LAY_BG_3_2);
}

#endif


/*
 * Description:
 *      Draw file area move scroll
 *
 * Creator:suqioali
 * Data:2004-6-15 
 *
 */
void MoveScroll(UINT16 locate)
{
    
    int y;

    DrawScroll();
    
    if (( locate == pFsJpeg->File_Page_Count - 1)&& (pFsJpeg->File_Page_Count != 1))
        y = ( fsArea[FS_AREA_MOVEBAR].yStart + fsArea[FS_AREA_MOVEBAR].ySize ) - pFsJpeg->scroll_step;//-(8-PER_PAGE)*32;//0x179
    else
        y = fsArea[FS_AREA_MOVEBAR].yStart + locate * pFsJpeg->scroll_step;
    #ifdef	GPS_MP3_UI//frank.huang  050923
	FSGUI_DrawBackGround(fsArea[FS_AREA_MOVEBAR].xStart,y, 1, pFsJpeg->scroll_len,SLIDER_BLOCK);
	if(pFsJpeg->scroll_len)
	{
		FSGUI_LayPosVariableBmp(fsArea[FS_AREA_MOVEBAR].xStart, y-3, SLIDER_BLOCK_U);
		FSGUI_LayPosVariableBmp(fsArea[FS_AREA_MOVEBAR].xStart, y+pFsJpeg->scroll_len, SLIDER_BLOCK_D);
	}
	#else
    FrameBuf_DrawRect(fsArea[FS_AREA_MOVEBAR].xStart, y, fsArea[FS_AREA_MOVEBAR].xSize, pFsJpeg->scroll_len,
        SCROLL_Y, SCROLL_CRCB);
	#endif


}



/*
 * Description:
 *      Draw dir area move scroll
 *
 * Creator:suqioali
 * Data:2004-6-15 
 *
 */
void DIR_MoveScroll(UINT16 locate)
{
    int y;
    
    DIR_DrawScroll();
    
    if (( locate == dir_count_page - 1)&& (dir_count_page != 1))
        y = ( fsArea[FS_AREA_DIR_MOVEBAR].yStart + fsArea[FS_AREA_DIR_MOVEBAR].ySize ) - dir_scroll_step;
    else
        y = fsArea[FS_AREA_DIR_MOVEBAR].yStart + locate * dir_scroll_step;
    #ifdef	GPS_MP3_UI//frank.huang 050923
	FSGUI_DrawBackGround(fsArea[FS_AREA_DIR_MOVEBAR].xStart,y, 1, dir_scroll_len,SLIDER_BLOCK);
	if(dir_scroll_len)
	{
		FSGUI_LayPosVariableBmp(fsArea[FS_AREA_DIR_MOVEBAR].xStart, y-3, SLIDER_BLOCK_U);
		FSGUI_LayPosVariableBmp(fsArea[FS_AREA_DIR_MOVEBAR].xStart, y+dir_scroll_len, SLIDER_BLOCK_D);
	}
	#else
    FrameBuf_DrawRect(fsArea[FS_AREA_DIR_MOVEBAR].xStart, y, fsArea[FS_AREA_DIR_MOVEBAR].xSize, dir_scroll_len,
        SCROLL_Y, SCROLL_CRCB);
	#endif
}

void SelectHL()
{
    int iFiles;

#ifdef MP3_DIRECT_SELECT
    iFiles = pFsJpeg->count_file[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3];
#else
    iFiles = pFsJpeg->file_specify_in_dir;
#endif

    HL_Width = 252;
//in order to display playing dir
#if 0
    //ShowHL();//move to the last of SelectHL() zhaoyanhua  2004-2-2 17:13
#ifdef MP3_TXT_DISPLAY //zhaoyanhua add 2003-9-2 9:40
    if ( ( (JPEG_Preview_drawed == DIR_LIST_IN_DIR_AREA)
         &&(pFsJpeg->gifsFuncBtn != FS_FUNC_MP3) )
      || ( (MP3_Lyrics_Drawed == DIR_LIST_IN_DIR_AREA)
         &&(pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)))//zhaoyanhua modify 2003-8-28 13:29
#else
    //to avoid the bug : when play JPEG, BUTTON->FILE  (RIGHT) or(UP) ,not draw DIR playing again.
    //zhaoyanhua modify 2003-12-27 11:10
    if ( ((JPEG_Preview_drawed == DIR_LIST_IN_DIR_AREA) &&(!(pFsJpeg->gifsbPreview))
        &&(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG))//for JPEG 
      ||((JPEG_Preview_drawed == DIR_LIST_IN_DIR_AREA) && (pFsJpeg->gifsFuncBtn != FS_FUNC_JPEG))//for MP3/OTHER 
       )
#endif

#endif

        ShowCurrentDirPlaying();
    	ShowCurrentFilePlaying();
    
	if ((old_ControlArea != pFsJpeg->ControlArea) 
	    || (pFsJpeg->ControlArea < CNT_AREA_MP3BUTTON))//only for right and left command or in dir and file area //feeling
        ShowHL();
}



void ShowHL(void)
{
    #ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
    #endif


    // clear last HL
    switch (old_ControlArea)
    {
        case  CNT_AREA_FILE:
                //zhaoyanhua add 2004-2-2 16:54
                //make some changes for the GUI not blink .
                if(HL_show == fsnav_file_HL)
                    ShowCurrentFilePlaying();
                else
                {
                    FSGUI_ClearArea(FS_AREA_FILEITEM,HL_show);
                    ShowFileIcon();
                    FSShowFileItem(HL_show, iso9660_file[pFsJpeg->file_array[HL_show]].name);//resume the last HL
                }
                break;
        case  CNT_AREA_DIR:
                //zhaoyanhua add 2004-2-2 16:54
                //make some changes for the GUI not blink .
                if(HL_show == fsnav_dir_HL)
                    ShowCurrentDirPlaying();
                else
                {
                    FSGUI_ClearArea(FS_AREA_DIRITEM,HL_show);
                    FSShowDirIcon();
                    ShowDirItem(HL_show,iso9660_dir[pFsJpeg->dir_array[HL_show]].name);//resume the last HL
                }
                break;

        case  CNT_AREA_MP3BUTTON:
                {
                    if (pFsJpeg->gifsFuncBtn== FS_FUNC_MP3)
                        FSGUI_DrawOneButton(FS_FUNC_MP3, DOWN_STATE);
                    else
                        FSGUI_DrawOneButton(FS_FUNC_MP3, UP_STATE);
                }
                break;
        case  CNT_AREA_JPEGBUTTON:
                {
            		if (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
                        FSGUI_DrawOneButton(FS_FUNC_JPEG, DOWN_STATE);
            		else
                        FSGUI_DrawOneButton(FS_FUNC_JPEG, UP_STATE);
                }
                break;
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
        case  CNT_AREA_GAMEBUTTON:
                {
        			if (pFsJpeg->gifsFuncBtn == FS_FUNC_GAME)
                        FSGUI_DrawOneButton(FS_FUNC_GAME, DOWN_STATE);
        			else
                        FSGUI_DrawOneButton(FS_FUNC_GAME, UP_STATE);
                }
                break;
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE
        case  CNT_AREA_OTHERBUTTON:
                {
    			    if (pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)
                        FSGUI_DrawOneButton(FS_FUNC_OTHER, DOWN_STATE);
    			    else
                        FSGUI_DrawOneButton(FS_FUNC_OTHER, UP_STATE);
                }
                break;


#endif

#ifdef SUPPORT_MIDI
        case  CNT_AREA_MIDIBUTTON:
            {
    			if (pFsJpeg->gifsState == FS_FUNC_MIDI)
                    FSGUI_DrawOneButton(FS_FUNC_MIDI, DOWN_STATE);
    			else
                    FSGUI_DrawOneButton(FS_FUNC_MIDI, UP_STATE);
            }
            break;
#endif
        default: break;
   }

    // draw current HL
    switch (pFsJpeg->ControlArea)
    {
        case  CNT_AREA_FILE:
                {
                    HL_show = pFsJpeg->file_will;
                    old_ControlArea = CNT_AREA_FILE;
                    DrawSelectedRectWithSide (fsArea[FS_AREA_FILEITEM].xStart, FS_DIRLIST_YSTART  + HL_show * FS_FILELIST_YSTEP , HL_Width, HL_Heighth, HL_Y, HL_CRCB, HL_SIDE_Y, HL_SIDE_CRCB );   
                    ShowFileIcon();
                    fontFocus();
                    FSShowFileItem(HL_show , iso9660_file[pFsJpeg->file_array[HL_show]].name);//resume the last HL
                    fontunFocus();
                    /// NOTE:
                    // These code are put here ,for they will used by FSGUI_Refresh()/FSGUI_CmdLeft/FSGUI_CmdRight()
                    // if MP3_Lyrics_Drawed is 1,then show lyrics.
                    //zhaoyanhua add 2003-9-1 17:49
                    #ifdef MP3_TXT_DISPLAY
                    ShowLyricsWhileHL();
                    #endif    
                }
                break;
        case  CNT_AREA_DIR:
                {
                    HL_show = pFsJpeg->dir_current;
                    old_ControlArea = CNT_AREA_DIR;
                    DrawSelectedRectWithSide(fsArea[FS_AREA_DIRITEM].xStart, FS_DIRLIST_YSTART  + HL_show * FS_FILELIST_YSTEP, HL_Width, HL_Heighth, HL_Y, HL_CRCB,HL_SIDE_Y ,HL_SIDE_CRCB);
                    FSShowDirIcon();
                    fontFocus();
                    ShowDirItem(HL_show,iso9660_dir[pFsJpeg->dir_array[HL_show]].name);//resume the last HL
                    fontunFocus();
                }
                break;

        case  CNT_AREA_MP3BUTTON:
                {
                    old_ControlArea = CNT_AREA_MP3BUTTON;
			        FSGUI_DrawOneButton(FS_FUNC_MP3, HL_STATE);
        	    }
                break;
        case  CNT_AREA_JPEGBUTTON:
                {
                    old_ControlArea = CNT_AREA_JPEGBUTTON;
                    FSGUI_DrawOneButton(FS_FUNC_JPEG, HL_STATE);
                }
                break;
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
        case  CNT_AREA_GAMEBUTTON:
                {
                    old_ControlArea = CNT_AREA_GAMEBUTTON;
			        FSGUI_DrawOneButton(FS_FUNC_GAME, HL_STATE);
                }
                break;
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE
        case  CNT_AREA_OTHERBUTTON:
                {
                    old_ControlArea = CNT_AREA_OTHERBUTTON;
                    FSGUI_DrawOneButton(FS_FUNC_OTHER, HL_STATE);
                }
                break;
#endif
#ifdef SUPPORT_MIDI
        case  CNT_AREA_MIDIBUTTON:
                {
                    old_ControlArea = CNT_AREA_MIDIBUTTON;
		            FSGUI_DrawOneButton(FS_FUNC_MIDI, HL_STATE);
                }
                break;
#endif

    default: break;
    }

}

void ShowCurrentFilePlaying()
{
    //avoid when HL and the current page in the same item,not show HL. zhaoyanhua 3-7-15 21:12
    if (pFsJpeg->ControlArea == CNT_AREA_FILE)
    {
    #if 0
        if (HL_show == fsnav_file_HL)
        return;
    #endif
    }

    FSGUI_ClearArea(FS_AREA_FILEITEM,fsnav_file_HL);
    //not to disappear symbol of mp3,suqiaoli add,2004-10-9
    ShowFileIcon();
    FSShowFileItem(fsnav_file_HL, iso9660_file[pFsJpeg->file_array[fsnav_file_HL]].name);//resume the last HL


    #ifdef NEW_MP3_GUI_DEBUG
    printf("***ShowCurrentFile ,file_page_now = %d,file_page_will = %d,file_current =%d\n",pFsJpeg->file_page_now,pFsJpeg->file_page_will,pFsJpeg-> file_current);
    #endif

    //In the same page ,show the HL.
    if ((pFsJpeg->file_page_will) == (pFsJpeg->file_page_now) )
    {
        fsnav_file_HL = (pFsJpeg->file_current);
        FileList();//feeling 2004-07-28
        DrawSelectedRectWithSide (fsArea[FS_AREA_FILEITEM].xStart, FS_DIRLIST_YSTART  + fsnav_file_HL * FS_FILELIST_YSTEP , HL_Width, HL_Heighth, PLAYING_Y, PLAYING_CRCB, PLAYING_SIDE_Y, PLAYING_SIDE_CRCB );   
        ShowFileIcon();
        fontFocus();
        FSShowFileItem(fsnav_file_HL, iso9660_file[pFsJpeg->file_array[fsnav_file_HL]].name);//                     
        fontunFocus();
    }

}

/*
 * FUNC: to show current dir which is playing.
 *
 * Creator: zhaoyanhua
 * date: 3-7-2 12:56
 */

void ShowCurrentDirPlaying()
{
    UINT16  dir_now = 0,dir_will = 0;

    if (pFsJpeg->ControlArea == CNT_AREA_DIR)
    {
#if 0//zhoayanhua mask 2004-2-2 17:16
        if (HL_show == fsnav_dir_HL)
            return;
#endif          
    }
    //clear the last HL DirItem.
    
    FSGUI_ClearArea(FS_AREA_DIRITEM,fsnav_dir_HL);
    ShowDirItem(fsnav_dir_HL, iso9660_dir[pFsJpeg->dir_array[fsnav_dir_HL]].name);//resume the last HL
    FSShowDirIcon();

    //locate the positon of fsnav_dir_will and fsnav_dir_now  in the current type(MP3/JPEG/GAME).
    dir_will = antiAnchorDir(pFsJpeg->fsnav_dir_will);
    dir_now  =  antiAnchorDir(pFsJpeg->fsnav_dir_now);

    //In the same page ,show the HL.
    if ((dir_will / PER_PAGE) == (dir_now / PER_PAGE) )
    {
        fsnav_dir_HL = dir_now % PER_PAGE;
        DrawSelectedRectWithSide(fsArea[FS_AREA_DIRITEM].xStart, FS_DIRLIST_YSTART  + fsnav_dir_HL * FS_FILELIST_YSTEP, HL_Width, HL_Heighth, PLAYING_Y, PLAYING_CRCB, PLAYING_SIDE_Y, PLAYING_SIDE_CRCB );   
        FSShowDirIcon();
        fontFocus();
        ShowDirItem(fsnav_dir_HL, iso9660_dir[pFsJpeg->dir_array[fsnav_dir_HL]].name);
        fontunFocus();
    }

}

/* Description:
 *    Draw a Triange in given postion
 * NOTE:
 *    I divide a isoceles triangle into two right-angled triangles.
 *    Their Hypotenuse has contrarily  slope.
 *
 * INPUT:
 *    xStart --->  x postion
 *    yStart --->  y postion
 *    iBottom ---> the bottom of the Triange
 *    iHight ----> the height of the Triange
 *    iDir   ----> UP    
 *                 DOWN  
 * RETURN:
 *    if can not draw the Triangle in the given point (xStart, yStart) return FALSE    
 *    else return TRUE
 *
 * Creator: zhaoyanhua 
 * Date: 2004-6-11 17:08  
 *
 */
BYTE  DrawTriangle(UINT16 xStart, UINT16 yStart, UINT16 iBottom, UINT16 iHight, BYTE iDir, UINT16 iColorY, UINT16 iColorCrCb) 
{
    UINT16  a = iBottom/2;
    UINT16  b = iHight;   
    UINT16  iSlope = b/a;
    int  i = 0, j = 0, k = 0;
    INT8  iSign = 0;
    INT16 iMaxHight = 0;  
    
    if (iDir == 1)
    {    
        //error  check
        if ((yStart - b) < 0)//
            return FALSE;
        
        iSign = 1;
        iMaxHight = b;
    }
    else 
    {
        //error check
        if ((yStart + b) > 480)//exceed the screen max line
            return FALSE;
            
        iSign = -1;
        iMaxHight = -b;
    }
     
    //printf("#### Draw Triangle -Slope:%d-iSign:%d-\n",iSlope,iSign);
    //draw left part: right-angled triangle(which right angle in its right) 
    for (i = 0; i < a; i++)
    {
        //for dir = 1 y = b/a*x; start point(0,0)
        //for dir = 0, y = -b/a*x start point(0,0)
        j = (iSign)*iSlope * i;
        
        for (k = 0; k <= (iSign*j); k++)
        {
            //printf("11111111Draw Trigle : i:%d, iSign * iMaxHight: %d,j = :%d k:%d--\n",i,iSign * iMaxHight,j,k);
            //for dir = 1, when draw left part, yStart increase in negative direction
            //for dir = 0, when draw left part, ystart inscreese in positive direction 
            *Y_XY((xStart + i), (yStart+ k*((-1)*iSign))) = iColorY;
            *C_XY((xStart + i), (yStart+ k*((-1)*iSign))) = iColorCrCb;
        }
        if (j >= (iSign * iMaxHight))
            break;
    }    
    
    //draw right part:right-angled triangle(which right angle in its left) 
    for (i = a; i < iBottom; i++)
    {
        //for dir = 1,line : y = (a+b)-b/a*x; start point(a,-b)
        //for dir = 0,line : y = -(a+b)+b/a*x; start point(a,b)
        j = (iSign)*(a + b - (iSlope*i));
        
        for (k = 0; k <= (iSign*j); k++)
        {
            //printf("2222222Draw Trigle : i:%d, j = :%d,k:%d--\n",i, j,k);
            //for dir = 1, when draw left part, yStart increase in negative direction
            //for dir = 0, when draw left part, ystart inscreese in positive direction 
            *Y_XY((xStart + i), (yStart + k*((-1)*iSign))) = iColorY;
            *C_XY((xStart + i), (yStart + k*((-1)*iSign))) = iColorCrCb;    
        } 
           
        if ((j*iSign) <= 0)
            break;
    }
    
    return TRUE;
}

/*
 * Description:
 *     draw a reverse bmp with iLayoutIndex bmp.
 * INPUT:
 *    xStart  ---> x start postion
 *    yStart  ---> y Start postion
 *    iLayoutIndex ---> the index in g_aBitmapLayout
 *    iMode ----->  reverse mode(veer)
 *                 
 *
 */          
void FSGUI_DrawReverseBmp(UINT16 xStart, UINT16 yStart, BYTE iLayoutIndex, BYTE iMode __attribute__((unused)))
{
 	extern void ReverseImg(const BYTE ImgOriData [ ], BYTE ImgTransData [ ], BYTE iMode);
    const BITMAP_LAYOUT* pLayout  =  &g_aBitmapLayout[iLayoutIndex];

    BYTE iWidth = *(g_aBitmap[pLayout->uiIndex]+0);
    BYTE iHeight = *(g_aBitmap[pLayout->uiIndex]+1);
    
    if (iHeight % 4)
        iHeight = (iHeight/4+1)*4;
    BYTE  ReverseBmp[iWidth*iHeight+3];
    
    //only draw bmp no need repeat
    if ((pLayout->uiXRepeat != 0) 
       ||(pLayout->uiYRepeat != 0))
        return;
    
    ReverseImg(g_aBitmap[pLayout->uiIndex],ReverseBmp, 1);
    
    FrameBuf_DrawBmp(xStart, yStart, 
                     ReverseBmp,
                     //g_aBitmap[pLayout->uiIndex],
                     g_aPalette[pLayout->uiPalette]);
            
    
}

/*
 * FUNC: to show title string on left of the top buttons.
 *
 * Creator: feeling 
 * date: 2004-06-21
 */

void FSGUI_ShowBtnTitle(void)
{
	#ifdef 	GPS_MP3_UI//frank.huang 050927 
		return;//don't show button title in gps_mp3 ui
	#endif

//show buttton title string
	switch(pFsJpeg->gifsFuncBtn)
	{
		case FS_FUNC_IDLE:
            psprintf(linebuf,"%s","WAITING");
            break;
		case FS_FUNC_MP3:
            psprintf(linebuf,"%s","MUSIC");
			break;
		case FS_FUNC_JPEG:
            psprintf(linebuf,"%s","PHOTO");
            break;
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
		case FS_FUNC_GAME:
            psprintf(linebuf,"%s","GAME");
            break;
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE
		case FS_FUNC_OTHER:
            psprintf(linebuf,"%s","VIDEO");
            break;
#endif	        	
	}
	 FSGUI_DrawBackGround(fsArea[FS_AREA_BUTTONTITLE_BACKGROUND].xStart,
		fsArea[FS_AREA_BUTTONTITLE_BACKGROUND].yStart,
		fsArea[FS_AREA_BUTTONTITLE_BACKGROUND].xSize,
		fsArea[FS_AREA_BUTTONTITLE_BACKGROUND].ySize,
		LAY_TAB_BAR2_2); //clear the background
	FSGUI_ShowString(fsArea[FS_AREA_BUTTONTITLE].xStart,
		fsArea[FS_AREA_BUTTONTITLE].yStart,
		linebuf,
		FS_FONTCOLOR_TITLE_Y,
		FS_FONTCOLOR_TITLE_CrCb);
}

/*
 * FUNC: to show font color when Focus on font.
 *
 * Creator: suqiaoli
 * date: 2004-6-28 
 */
void fontFocus(void)
{
    file_focus_y = BLACK_Y;
    file_focus_CrCb = BLACK_CRCB;
}

/*
 * FUNC: to show font color when not Focus on font
 *
 * Creator: suqiaoli
 * date: 2004-6-28 
 */
void fontunFocus(void)
{
    file_focus_y = FS_FONTCOLOR_FILE_Y;
    file_focus_CrCb = FS_FONTCOLOR_FILE_CrCb;   
}    

/*
 * FUNC: to show selected item ,two sides and a rect
 *       side width = rect with
 *       side height = 1 piexl 
 *
 * Creator: suqiaoli
 * date: 2004-7-9 
 */

void DrawSelectedRectWithSide(UINT16 xStart, UINT16 yStart, UINT16 xLen, UINT16 yLen, UINT16 RectY, UINT16 RectCrCb,UINT16 SideY ,UINT16 SideCrCb)
{
    FrameBuf_DrawLine( xStart, yStart -1, xLen, 1, SideY, SideCrCb );
    FrameBuf_DrawRect( xStart, yStart, xLen, yLen, RectY, RectCrCb );
    FrameBuf_DrawLine( xStart, yStart + yLen , xLen, 1, SideY, SideCrCb );

}    

#endif//#ifdef FS_BMP_GUI
