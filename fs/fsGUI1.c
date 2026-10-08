#include "user_init.h"
#include "global.h"
#include "func.h" 
#include "memmap.h"
#include "util.h" 
#include "graph.h"
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

#ifdef JPG_OLD_PARSER_FLOW
    #ifdef JPG_EFFECT
    #include "jpegeffect.h"
    #endif
#else
    #include "pic_effect.h"
#endif

#ifdef FSGUI_NO_BLINK_SCROLL
//*******************************************************
//function: DrawRectShadow()	
//description: Draw rectangle edge line,up or down effect.
//creator: xulf
//date:2003-12-09
//*******************************************************
void DrawRectShadow(int x,int y,int xSize,int ySize,BYTE updown_sign)		
{
#ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
#endif
	if(updown_sign ==1)
	{
	    FSGUI_FillFrameBuf(x, y, xSize, 1, BLACK_Y, BLACK_CRCB);
	    FSGUI_FillFrameBuf(x, y, 1, ySize, BLACK_Y, BLACK_CRCB);
	    FSGUI_FillFrameBuf(x + xSize - 1, y + 1, 1, ySize - 1, WHITE_Y, WHITE_CRCB);
	    FSGUI_FillFrameBuf(x + 1, y + ySize - 1, xSize - 1, 1 ,WHITE_Y, WHITE_CRCB);
	}
	else
	{
	    FSGUI_FillFrameBuf(x, y, xSize, 1, WHITE_Y, WHITE_CRCB);
	    FSGUI_FillFrameBuf(x, y, 1, ySize, WHITE_Y, WHITE_CRCB);
	    FSGUI_FillFrameBuf(x + xSize - 1, y, 1, ySize, BLACK_Y, BLACK_CRCB);
	    FSGUI_FillFrameBuf(x, y + ySize - 1, xSize ,1 ,BLACK_Y, BLACK_CRCB);
	}
}
//*******************************************************
//function: MoveScroll()	
//description: redraw changed section of scollbar when 
//                press up_down buttons or refresh fsGUI.
//creator: xulf
//date:2003-12-09
//*******************************************************
void MoveScroll(UINT16 locate,INT8 move_sign)
{
	int y;

	if ((fsArea[FS_AREA_MOVEBAR].ySize - pFsJpeg->scroll_len) >= (pFsJpeg->file_specify_in_dir - 1))
		y = fsArea[FS_AREA_MOVEBAR].yStart + locate * pFsJpeg->scroll_step;
	else
		y = fsArea[FS_AREA_MOVEBAR].yStart + locate * pFsJpeg->scroll_step / 10;

	if(move_sign == SCROLLBAR_DOWN)
	{
	    FSGUI_FillFrameBuf(fsArea[FS_AREA_MOVEBAR].xStart, y-pFsJpeg->scroll_step, 
	        fsArea[FS_AREA_MOVEBAR].xSize, pFsJpeg->scroll_step+1, BK_GROUNDY-0x20, BK_GROUNDCRCB);
		FSGUI_FillFrameBuf(fsArea[FS_AREA_MOVEBAR].xStart, y-pFsJpeg->scroll_step+pFsJpeg->scroll_len-2, 
		    fsArea[FS_AREA_MOVEBAR].xSize, pFsJpeg->scroll_step+2, BK_GROUNDY, BK_GROUNDCRCB);
		DrawRectShadow(fsArea[FS_AREA_MOVEBAR].xStart,y,fsArea[FS_AREA_MOVEBAR].xSize, pFsJpeg->scroll_len, 0);
	}
	else if(move_sign == SCROLLBAR_UP)
	{
	    FSGUI_FillFrameBuf(fsArea[FS_AREA_MOVEBAR].xStart, y, fsArea[FS_AREA_MOVEBAR].xSize,
	        pFsJpeg->scroll_step+1, BK_GROUNDY, BK_GROUNDCRCB);
		FSGUI_FillFrameBuf(fsArea[FS_AREA_MOVEBAR].xStart, y+pFsJpeg->scroll_len, 
		    fsArea[FS_AREA_MOVEBAR].xSize, pFsJpeg->scroll_step, BK_GROUNDY-0x20, BK_GROUNDCRCB);
		DrawRectShadow(fsArea[FS_AREA_MOVEBAR].xStart,y,fsArea[FS_AREA_MOVEBAR].xSize, pFsJpeg->scroll_len, 0);
	}
	else
	{
		DrawScroll();
		DrawRect(fsArea[FS_AREA_MOVEBAR].xStart, y, fsArea[FS_AREA_MOVEBAR].xSize, pFsJpeg->scroll_len, 
		0, BK_GROUNDY, BK_GROUNDCRCB);
	}
	return;
}
#else
void MoveScroll(UINT16 locate)
{
	int y;
	
	DrawScroll();

	if ((fsArea[FS_AREA_MOVEBAR].ySize - pFsJpeg->scroll_len) >= (pFsJpeg->file_specify_in_dir - 1))
		y = fsArea[FS_AREA_MOVEBAR].yStart + locate * pFsJpeg->scroll_step;
	else
		y = fsArea[FS_AREA_MOVEBAR].yStart + locate * pFsJpeg->scroll_step / 10;
	
	DrawRect(fsArea[FS_AREA_MOVEBAR].xStart, y, fsArea[FS_AREA_MOVEBAR].xSize, pFsJpeg->scroll_len, 0,
		BK_GROUNDY, BK_GROUNDCRCB);
	
	return;
}
#endif

void DrawScroll(void)
{
	DrawRect(fsArea[FS_AREA_SLOT].xStart, fsArea[FS_AREA_SLOT].yStart,
		fsArea[FS_AREA_SLOT].xSize, fsArea[FS_AREA_SLOT].ySize,
		1, BK_GROUNDY-0x20, BK_GROUNDCRCB);
	
	return;
}

void SelectHL()
{
	if ((pFsJpeg->ControlArea == CNT_AREA_FILE) || (pFsJpeg->ControlArea == CNT_AREA_DIR))
	{
		ShowButtonHL(0, 0, 0);
		
		if (pFsJpeg->ControlArea == CNT_AREA_FILE)
		{
			//Jeff 20020521
			int iFiles, iWidth;
			
#ifdef MP3_DIRECT_SELECT
			iFiles = pFsJpeg->count_file[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3];
#else
			iFiles = pFsJpeg->file_specify_in_dir;
#endif
			
			if (iFiles>999)
				iWidth = 46;
			else if (iFiles>99)
				iWidth = 38;
			else iWidth = 28;
			ShowHL(fsArea[FS_AREA_FILEITEM].xStart - 2, FS_DIRLIST_YSTART - 1 + pFsJpeg->file_will * FS_FILELIST_YSTEP, iWidth, 14);
		}
		else if (pFsJpeg->ControlArea == CNT_AREA_DIR)
			ShowHL(fsArea[FS_AREA_DIRITEM].xStart - 2, FS_DIRLIST_YSTART - 1 + pFsJpeg->dir_current * FS_FILELIST_YSTEP, 28, 14);
	}
	else
	{
		ShowHL(0,0,0,0);
		
		if (pFsJpeg->ControlArea == CNT_AREA_MP3BUTTON)
		{
		  #ifdef NO_LIRIC_ID3 //caohui 2004-4-23 06:36
			ShowButtonHL(fsArea[FS_AREA_BUTTON].xStart + 3+40, fsArea[FS_AREA_BUTTON].yStart -203, 19);
		  #else
			ShowButtonHL(fsArea[FS_AREA_BUTTON].xStart + 3, fsArea[FS_AREA_BUTTON].yStart + 3, 19);
		  #endif
		}
		else if (pFsJpeg->ControlArea == CNT_AREA_JPEGBUTTON)
		{	
			 #ifdef NO_LIRIC_ID3 //caohui 2004-4-23 06:36
			ShowButtonHL(fsArea[FS_AREA_BUTTON].xStart + 3 + 92,fsArea[FS_AREA_BUTTON].yStart-203, 15);
             #else
			ShowButtonHL(fsArea[FS_AREA_BUTTON].xStart + 3 + 27,fsArea[FS_AREA_BUTTON].yStart + 3, 19);
            #endif
        }
#ifdef SUPPORT_NESGAME //Jeff 20020521
		else if (pFsJpeg->ControlArea == CNT_AREA_GAMEBUTTON)
			ShowButtonHL(fsArea[FS_AREA_BUTTON].xStart + 3 + 54, fsArea[FS_AREA_BUTTON].yStart + 3, 19);
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 020930
		else if (pFsJpeg->ControlArea == CNT_AREA_OTHERBUTTON)
#ifdef SUPPORT_NESGAME
			ShowButtonHL(fsArea[FS_AREA_BUTTON].xStart + 3 + 81, fsArea[FS_AREA_BUTTON].yStart + 3, 19);
#else
			ShowButtonHL(fsArea[FS_AREA_BUTTON].xStart + 3 + 54, fsArea[FS_AREA_BUTTON].yStart + 3, 19);
#endif
#endif

#ifdef SUPPORT_MIDI
        else if(pFsJpeg->ControlArea == CNT_AREA_MIDIBUTTON) {
#ifdef SUPPORT_FILE_SYSTEM_MODE
#ifdef SUPPORT_NESGAME
            ShowButtonHL(fsArea[FS_AREA_BUTTON].xStart + 3 + 108, fsArea[FS_AREA_BUTTON].yStart + 3, 19);
#else //SUPPORT_NESGAME
            ShowButtonHL(fsArea[FS_AREA_BUTTON].xStart + 3 + 81, fsArea[FS_AREA_BUTTON].yStart + 3, 19);
#endif //SUPPORT_NESGAME
#else //SUPPORT_FILE_SYSTEM_MODE
#ifdef SUPPORT_NESGAME
            ShowButtonHL(fsArea[FS_AREA_BUTTON].xStart + 3 + 81, fsArea[FS_AREA_BUTTON].yStart + 3, 19);
#else //SUPPORT_NESGAME
            ShowButtonHL(fsArea[FS_AREA_BUTTON].xStart + 3 + 54, fsArea[FS_AREA_BUTTON].yStart + 3, 19);
#endif //SUPPORT_NESGAME
#endif //SUPPORT_FILE_SYSTEM_MODE
        }
#endif //SUPPORT_MIDI

	}
}


void ShowButtonHL(int x, int y,int len)
{
	
	
	// resume preview HL
	
	if(Hl_len_btn!=0)
	
#ifdef NO_LIRIC_ID3
		DrawRectEdge(Hl_x_btn,Hl_y_btn,44,12,BK_GROUNDY,BK_GROUNDCRCB);
#else
		DrawRectEdge(Hl_x_btn,Hl_y_btn,Hl_len_btn,Hl_len_btn,BK_GROUNDY,BK_GROUNDCRCB);
#endif
	
	// draw current HL
	if (len!=0)
	{
	     #ifdef NO_LIRIC_ID3 
	    DrawRectEdge(x,y,44,12,WHITE_Y,WHITE_CRCB);
          #else
          printf("=======here is 4=======\n");
		DrawRectEdge(x,y,len,len,BLACK_Y,BLACK_CRCB);
    
	    #endif
	 } 
	Hl_x_btn = x;
	Hl_y_btn = y;
	Hl_len_btn = len;
}


void ShowHL(int x, int y,int len,int high)
{
#ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
#endif
	
	//if ( (x>351) || (y>287) )  return;
	//if ( (x<0) || (y<0) ) return;
	
	// resume preview HL
	if((Hl_len!=0)&&(Hl_high!=0))
		FSGUI_ReplaceFrameBuf(Hl_x,Hl_y,Hl_len,Hl_high,HL_Y,HL_CRCB,BK_GROUNDY,BK_GROUNDCRCB);
	
	// draw current HL
	if ( (len!=0) && (high!=0) ) {
		FSGUI_ReplaceFrameBuf(x,y,len,high,BK_GROUNDY,BK_GROUNDCRCB,HL_Y,HL_CRCB);
	}
	//resume shadow
	if((Hl_len!=0)&&(Hl_high!=0)) {    
		FSGUI_FillFrameBuf(Hl_x,Hl_y,Hl_len,1,BK_GROUNDY,BK_GROUNDCRCB);
		FSGUI_FillFrameBuf(Hl_x,Hl_y,1,Hl_high,BK_GROUNDY,BK_GROUNDCRCB);
	}
	//draw shadow
	if((len!=0)&&(high!=0)) {
		FSGUI_FillFrameBuf(x,y,len,1,BLACK_Y,BLACK_CRCB);
		FSGUI_FillFrameBuf(x,y,1, high,BLACK_Y,BLACK_CRCB);
	}
	
	// resume light line
	if((Hl_len!=0)&&(Hl_high!=0)) {
		FSGUI_FillFrameBuf(Hl_x+1,		Hl_y+Hl_high-1,Hl_len-1,	1,	BK_GROUNDY,BK_GROUNDCRCB);
		FSGUI_FillFrameBuf(Hl_x+Hl_len-1,	Hl_y+1,	1,Hl_high-1,		BK_GROUNDY,BK_GROUNDCRCB);
       	
	}
	//draw light line
	if((len!=0)&&(high!=0)) {
		FSGUI_FillFrameBuf(x+1,		y+high-1,len-1,1,WHITE_Y,WHITE_CRCB);
		FSGUI_FillFrameBuf(x+len-1,	y+1,	1,	high-1,WHITE_Y,WHITE_CRCB);
	}
    
	Hl_x = x;
	Hl_y = y;
	Hl_len = len;
	Hl_high = high;
}


