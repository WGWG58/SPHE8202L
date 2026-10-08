/*****************************************************\
Creater: suqiaoli
Date   : 2004-11-15
Description: Program new menu using
\*****************************************************/

#ifdef OSD_BMP_PROG

#include "osd_BmpUI.h"

#define PROG_DVD_UNSELECT_RECT_WIDTH   40
#define PROG_DVD_UNSELECT_RECT_HEIGHT  28
#define PROG_DVD_SELECT_RECT_WIDTH     38
#define PROG_DVD_SELECT_RECT_HEIGHT    26

#define PROG_CD_RECT_WIDTH             70
#define PROG_CD_RECT_HEIGHT            26

#define PROG_SELECT_FONT_COLOR    		15
#define PROG_UNSELECT_FONT_COLOR  		3
#define PROG_SELECT_BG_COLOR      		12
#define PROG_UNSELECT_BG_COLOR    		0

#define PROG_PLAY_SELECT_FONT_COLOR     15
#define PROG_PLAY_SELECT_BG_COLOR       12
#define PROG_PLAY_UNSELECT_FONT_COLOR   14
#define PROG_PLAY_UNSELECT_BG_COLOR     1

//prog play,reset button info:rect and string
#define PROG_PLAY_RECT_XSTART       	222 
#define PROG_PLAY_STRING_XSTART     	222+47//302 
#define PROG_RESET_RECT_XSTART      	402
#define PROG_RESET_STRING_XSTART    	402+39//482
#define PROG_PLAY_RESET_RECT_YSTART 	232
#define PROG_PLAY_RESET_BUTTON_WIDTH	158
#define PROG_PLAY_RESET_BUTTON_HEIGHT	26
#define PROG_BUTTON_BG_SELECT_COLOR		12
#define PROG_BUTTON_FONT_SELECT_COLOR	15
#define PROG_BUTTON_BG_UNSELECT_COLR	1
#define PROG_BUTTON_FONT_UNSELECT_COLOR 14
#define PROG_BUTTON_BG_GRAY_COLOR        1
#define PROG_BUTTON_FONT_GRAY_COLOR     5

UINT8 flag_data;

/*
*
*Note:Following functions describe different region(A~F)info,
*     use region data structures,which include indexes(bmp,line,rect,str) 
*/

const OSD_REGIONA_LAYOUT_S g_stProgramRegionA = 
{
    OSD_BG_BMP_A,
    PROG_LINE1_A,
    OSD_DOWN_BG_BMP_A,
    PROG_LINE2_A,
    PROG_SHADOW_A,
};
const OSD_REGIONB_LAYOUT_S g_stProgramRegionB = 
{
    0,
    PROG_BG_LINE_B,
    PROG_LINE1_B,
    PROG_DOWN_B,
    0,
    PROG_STR_B,
    0,
    PROG_LINE2_B,
    PROG_SHADOW_B,
};
const OSD_REGIOND_LAYOUT_S g_stProgramRegionD = 
{
    OSD_4_1_BMP_D,
    OSD_4_2_BMP_D,
    PROG_LINE1_D,
    PROG_DOWN_D,
    0,
    PROG_LINE2_D,
    PROG_SHADOW_D,
    OSD_4_3_BMP_D,    
};
const OSD_REGIONE_LAYOUT_S g_stProgramRegionE = 
{
    OSD_5_1_BMP_E,
    0,
    OSD_5_3_BMP_E,
};
const OSD_REGIONF_LAYOUT_S g_stProgramRegionF = 
{
    OSD_6_1_BMP_F,
    OSD_6_2_BMP_F,
    OSD_6_3_BMP_F,
};

//Prog region A :region 1
void Layout_Prog_Region_A(void)
{
	const OSD_REGIONA_LAYOUT_S* pLayoutRegion_A =  &g_stProgramRegionA;
	
	OSD_LayoutBmp(pLayoutRegion_A -> uiBg,0) ;
	OSD_LayoutLine(pLayoutRegion_A ->uiLineLeft,0);
	OSD_LayoutBmp(pLayoutRegion_A -> uiDownBg,0) ;
	OSD_LayoutLine(pLayoutRegion_A ->uiLineRight,0);	
	OSD_LayoutRect(pLayoutRegion_A ->uiShadow,0);
}

//Prog region B :region 2
void Layout_Prog_Region_B(void)
{
	const OSD_REGIONB_LAYOUT_S* pLayoutRegion_B =  &g_stProgramRegionB;
	
	OSD_LayoutLine(pLayoutRegion_B ->uiBgLine,0);
	OSD_LayoutLine(pLayoutRegion_B ->uiLineLeft,0);	
	OSD_LayoutRect(pLayoutRegion_B ->uiDownBg,0);
	
	char str[10];
	psprintf(str, "%s ", &_OsdMessegeFont1[osd_font_mode][STR_OS_PROG][0]);
    OSD_LayoutStr(str, pLayoutRegion_B ->uiSelStr,0);
      
	OSD_LayoutLine(pLayoutRegion_B ->uiLineRight,0);	
	OSD_LayoutRect(pLayoutRegion_B ->uiShadow,0);
}

//Prog region D :region 3
void Layout_Prog_Region_D(void)
{
	const OSD_REGIOND_LAYOUT_S* pLayoutRegion_D =  &g_stProgramRegionD;

	OSD_LayoutBmp(pLayoutRegion_D -> uiLeftBg,0);
	OSD_LayoutBmp(pLayoutRegion_D -> uiMiddleBg,0);
    OSD_LayoutLine(pLayoutRegion_D ->uiLineLeft,0);
    OSD_LayoutRect(pLayoutRegion_D ->uiDownBg,0);
    OSD_LayoutLine(pLayoutRegion_D ->uiLineRight,0);
	OSD_LayoutBmp(pLayoutRegion_D -> uiRightBg,0);
	OSD_LayoutRect(pLayoutRegion_D ->uiShadow,0);
}

//Prog region E :region 4
void Layout_Prog_Region_E(void)
{
	const OSD_REGIONE_LAYOUT_S* pLayoutRegion_E = &g_stProgramRegionE;
	
	OSD_LayoutBmp(pLayoutRegion_E -> uiLeftBg,0);
	OSD_LayoutBmp(pLayoutRegion_E -> uiRightBg,0);
}	

//Prog region F :region 5
void Layout_Prog_Region_F(void)
{
	const OSD_REGIONF_LAYOUT_S* pLayoutRegion_F =  &g_stProgramRegionF;
	
	OSD_LayoutBmp(pLayoutRegion_F -> uiLeftBg,0);
	OSD_LayoutBmp(pLayoutRegion_F -> uiMiddleBg,0);
	OSD_LayoutBmp(pLayoutRegion_F -> uiRightBg,0);

}

/*
 * Funciton Description:  
 * 	 Draw prog region on osd,use new region
 * 
 *   
 * Creator:suqiaoli 
 * Date :2004-11-5
 */
void DrawProgRegion(void)
{
    Layout_Prog_Region_A();
    Layout_Prog_Region_B();
    Layout_Prog_Region_D();
    Layout_Prog_Region_E();
    Layout_Prog_Region_F();    
}

/*
 * Funciton Description:  
 * 	 Draw prog string on osd.
 * 
 * INPUT:
 *   xStart,yStart     --> the start of string,
 *   str               --> string 
 *   mode        	   --> 0:unselect state
 *                         other:select state
 * Note:only used by number state
 *   
 * Creator:suqiaoli 
 * Date :2004-11-5
 */
void Draw_Prog_String(UINT32 xStart, UINT32 yStart, const BYTE *str,BYTE mode)
{
    BYTE fontColor, bkColor;
    
    if (mode == 0)
    {
		int m;
		m = (index_y - 2 ) + MAX_NM_Y * (index_x / 2) + 1; 

		if (((offset==1)&&(strcmp(str,"--")== 0))||((offset==2)&&(strcmp(str,"----")== 0)))
			fontColor = PROG_UNSELECT_FONT_COLOR ;
		else        
	        fontColor = 14 ;
	        bkColor = PROG_UNSELECT_BG_COLOR ;
    }
    else
    {
        fontColor = PROG_SELECT_FONT_COLOR ;
        bkColor = PROG_SELECT_BG_COLOR ;
    }
    
    yStart = yStart * 40 + 32;        
    
    if (offset == 2)
        xStart = (xStart )*70+60;
    else
    {
        if (xStart%2==0)
            xStart = (xStart )*70+60;        
        else
            xStart = (xStart -1 )*70+60+54;
    }

    osd_Draw_Bmp_RegionString(xStart, yStart,str,fontColor,bkColor,4);	
}

/*
 * Funciton Description:  
 * 	 Draw prog rect on osd.
 *  
 * 
 * INPUT:
 *   xStart,yStart     --> the start of rect
 *   mode        	   --> 0:unselect state
 *                         other:select state
 * Note:only used by number state
 *  
 * Creator:suqiaoli 
 * Date :2004-11-5
 */
void Draw_Prog_Rect(UINT32 xStart, UINT32 yStart, BYTE mode)
{
    BYTE bkColor;
    UINT32 xLen, yLen;
    
    if (mode == 0)
    {
        bkColor = 0 ;
        yLen = PROG_DVD_UNSELECT_RECT_HEIGHT ; 
    }     
    else
    {    
        bkColor = 12 ;
        yLen = PROG_DVD_SELECT_RECT_HEIGHT ;
    }     
        
    yStart = yStart*40 + 32 ;

    if (offset == 2)
    {
        xLen = PROG_CD_RECT_WIDTH;
        xStart = (xStart )*70+60-2;
    }
    else
    {
        xLen = PROG_DVD_SELECT_RECT_WIDTH;
        
        if (xStart%2==0)
            xStart = (xStart )*70 + 60-2;
        else    
            xStart = (xStart -1 )*70 + 60 + 54-2;
    }
    
    osd_draw_region_rect(xStart, yStart, xLen, yLen, bkColor, 4);
    
    if ( mode != 0)
    {
        osd_draw_hline_region(xStart, xStart+xLen,yStart, 11, 1, 4);
        osd_draw_hline_region(xStart, xStart+xLen,yStart+yLen, 11, 1, 4);
    }       
}

/*
 * Funciton Description:  
 * 	 Draw prog rect on osd.
 *  
 * 
 * INPUT:
 *   mode        	   --> 0:unselect state
 *                         other:select state
 * Note:only used by func state
    
 * Creator:suqiaoli 
 * Date :2004-11-5
 */
void Draw_Prog_Play_Reset_Button(BYTE mode)
{
	char play_str[10],reset_str[10];
	UINT8 play_button_bg_color,play_str_font_color;
	UINT8 reset_button_bg_color,reset_str_font_color;
	
    psprintf(play_str, "%s ", &_OsdMessegeFont1[osd_font_mode][STR_OS_PLAY][0]);
    psprintf(reset_str, "%s ", &_OsdMessegeFont1[osd_font_mode][STR_OS_CLEAR][0]);
	
	int m;
	m = (index_y - 2 ) + MAX_NM_Y * (index_x / 2) + 1; 
	
	if (flag_data==0)
	{		
	    play_button_bg_color = PROG_BUTTON_BG_GRAY_COLOR;
		play_str_font_color = PROG_BUTTON_FONT_GRAY_COLOR;
		
		reset_button_bg_color = PROG_BUTTON_BG_GRAY_COLOR;
		reset_str_font_color = PROG_BUTTON_FONT_GRAY_COLOR;
	}	
	else
	{	
	//clear button and str 
	play_button_bg_color = PROG_BUTTON_BG_UNSELECT_COLR;
	play_str_font_color = PROG_BUTTON_FONT_UNSELECT_COLOR;
	
	reset_button_bg_color = PROG_BUTTON_BG_UNSELECT_COLR;
	reset_str_font_color = PROG_BUTTON_FONT_UNSELECT_COLOR;	

	//select button and str
	if ((index_x/2 == 1)&&(mode != 0))//play button
	{
		play_button_bg_color = PROG_BUTTON_BG_SELECT_COLOR;
		play_str_font_color = PROG_BUTTON_FONT_SELECT_COLOR;
	}	
	else if ((index_x/2 == 2)&&(mode != 0))//reset button
	{
		reset_button_bg_color = PROG_BUTTON_BG_SELECT_COLOR;
		reset_str_font_color = PROG_BUTTON_FONT_SELECT_COLOR;					
	}	
	}	
	
	//play button info
	osd_draw_region_rect(PROG_PLAY_RECT_XSTART, PROG_PLAY_RESET_RECT_YSTART, PROG_PLAY_RESET_BUTTON_WIDTH, PROG_PLAY_RESET_BUTTON_HEIGHT, play_button_bg_color, 4);
	osd_Draw_Bmp_RegionString(PROG_PLAY_STRING_XSTART, PROG_PLAY_RESET_RECT_YSTART,play_str,play_str_font_color,play_button_bg_color,4);
	
	//reset button info
	osd_draw_region_rect(PROG_RESET_RECT_XSTART, PROG_PLAY_RESET_RECT_YSTART, PROG_PLAY_RESET_BUTTON_WIDTH, PROG_PLAY_RESET_BUTTON_HEIGHT, reset_button_bg_color, 4);
	osd_Draw_Bmp_RegionString(PROG_RESET_STRING_XSTART, PROG_PLAY_RESET_RECT_YSTART,reset_str,reset_str_font_color,reset_button_bg_color,4);  	
	
}	  

/*
 * Funciton Description:  
 * 	 Draw prog sel
 *  
 * 
 * INPUT:
 *   mode        	   --> 0:unselect state
 *                         other:select state
 *
 * Note:this is same as ShowProgSel in prog_mp3undir.c
    
 * Creator:suqiaoli 
 * Date :2004-11-5
 */
void ShowBmpProgSel(UINT8 mode)
{
    UINT8 sub_r, tt, ch, y;
    UINT16 uXStart,uYStart;
        
#ifdef PROG_12_ITEMS
    if ((index_y >= 2) && (index_y <= 6))
        sub_r = index_x / 2 + 2; // skip first column
    else
        sub_r = index_x / 2 + 1;
#else // 16 items
    sub_r = index_x / 2 + 1;
#endif

    id = prog_item[page][index_y][sub_r];
    y = (index_y - 2 ) + MAX_NM_Y * (index_x / 2) + 1;
  
    //put data
    if(prog_item[page][index_y][0] == SET_NM)
    {//terry,2004/1/26 01:10PM
        UINT8 str[10];
  	
        tt = prog[y][0];
        ch = prog[y][1];

        if (tt||ch)
        {    
            flag_data = 1;
            Draw_Prog_Play_Reset_Button(0);
        }      

        str[0]=0;	
        if (offset == 2)
        {
            if (y >= 10)
        	    psprintf(RegionValStr[index_y ], " %d     ", y);	// for column alignment
            else if (y <= 5)
                psprintf(RegionValStr[index_y ], "%d     ", y);
            else
        	    psprintf(RegionValStr[index_y ], "  %d     ", y);
            
            if(tt) psprintf(str, " %02d ", tt);
            else psprintf(str, "----", tt);
	    }
	    else
	    {
            if (y >= 10)
        	    psprintf(RegionValStr[index_y ], " %d   :   ", y);	// for column alignment
            else if (y <= 5)
                psprintf(RegionValStr[index_y ], "%d   :   ", y);
            else
        	    psprintf(RegionValStr[index_y ], "  %d   :   ", y);
	        
			if((tt)&&(index_x%2==0))
			    psprintf(str, "%02d",tt);
			else if ((ch)&&(index_x%2==1))
			    psprintf(str, "%02d",ch);
			else psprintf(str, "--");
	    }
	    
        if (y >= 6)
            uXStart = (sub_r-1)*140;
        else
            uXStart = 32;
        
        uYStart = ( index_y - 2)*40 + 32;

        osd_Draw_Bmp_RegionString(uXStart, uYStart,RegionValStr[index_y ],3,0,4);				
		
		Draw_Prog_Rect(index_x , (index_y - 2),mode);
		Draw_Prog_String(index_x , (index_y - 2),str,mode);    	    
	    
    }
    if(prog_item[page][index_y][0] == SET_FUNC)
        Draw_Prog_Play_Reset_Button(mode);

}

/*
 * Funciton Description:  
 * 	 Draw prog page
 *  
 * 
 *
 * Note:this is same as ShowProgPage in prog_mp3undir.c
    
 * Creator:suqiaoli 
 * Date :2004-11-5
 */

void ShowBmpProgPage(void)
{
    UINT8 x,y,k;
    char colon_str[2],tt_str[2],ch_str[2];
    
    DrawProgRegion();
   
    OSD_LayoutRect(PROG_BG2_E,0);
    OSD_LayoutRect(PROG_BG3_E,0);
    
    strcpy(colon_str,":");
    strcpy(tt_str,"TT");
    strcpy(ch_str,"CH");
	
	if (cd_type_loaded == CDROM)
    {	
        for(k=0;k<4;k++)
    	{    
    	    OSD_LayoutBmp(PROG_CDROM_FOLDER_BMP_D, k);
    	    OSD_LayoutBmp(PROG_CDROM_FILE_BMP_D, k);
            OSD_LayoutStr(colon_str, PROG_STR_COLON,k);
    	}
    }
    else if (cd_type_loaded == CDDVD)	
    {	
        for(k=0;k<4;k++)
    	{    
            OSD_LayoutLittleStr(tt_str, PROG_DVD_TT,k);
            OSD_LayoutStr(colon_str, PROG_STR_COLON,k);
            OSD_LayoutLittleStr(ch_str, PROG_DVD_CH,k);
    	}
    }    
    
    x=index_x;
    y=index_y;
	
    if((cd_type_loaded==CDDVD)||(cd_type_loaded==CDROM)) 
    {
        offset=1;
        page=0;
    }
    else 
    {
        offset=2;
        page=1;
    }
	
    for(index_y=0;index_y<MAX_REGION;index_y++) 
    {
      if(prog_item[page][index_y][0]) 
      {
        for(index_x=0;index_x<MAX_PROG_SEL;index_x+=offset) 
        {
            ShowProgSel(0);
        }
      }
    }
    
    index_x=x;
    index_y=y;
    ShowProgSel(SW_REGION_ANTI);
    

}
 
#endif
