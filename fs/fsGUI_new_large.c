/**************************************************************
** FILE
** fsGUI_new_large.c
**
** DESCRIPTION
** On the base of fsGUI_new.c, build a larger Memory Mode GUI for MP3/JPEG/GAME.
**
**
**   Creator:   MaoYong
** 	 Date:     3-12-19 14:49
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
//#include "fsGUI1.h"
//#include "user_if.h"

//Maoyong 2004.04.15 add MP3_LARGE_GUI in fsGUI_new.h for different define.
#include "fsGUI_new.h"	

#ifdef JPG_OLD_PARSER_FLOW
    #ifdef JPG_EFFECT
    #include "jpegeffect.h"
    #endif
#else
    #include "pic_effect.h"
#endif

#ifdef MP3_TXT_DISPLAY//zhaoyanhua add 2003-9-1 17:49
//for MP3_Lyrics_Drawed
#define  MP3_LYRICS_IN_DIR_AREA    1
#define  DIR_LIST_IN_DIR_AREA      0

extern UINT16 MP3TotalNo;
extern BYTE MP3_Lyrics_Drawed;
extern void ShowLyricsWhileHL(void);
#endif

extern void	set_disbuf_now(int);
extern BYTE jpg_break_up_down;	//Maoyong 2004.04.19
//#define NEW_MP3_GUI_DEBUG
#if 0
#ifndef NEW_MP3_GUI_DEBUG
#undef printf
#endif
#endif

//define main menu look-and-feel style
//Notes : to avoid blinking (when white/black line displaying in n/n+1 line, with interlace mode)
//        SHADOW_WID , LIGHT_WID should >=2
//        X1, Y1, Y3 should be 2*n
#define SHADOW_WID                      2
#define LIGHT_WID                       2




#define LT  1//CornerLT
#define LB  2//CornerRT
#define RT  3//CornerLB
#define RB  4//CornerRB


///////////////////////////////////////////////////////////////////////
void   DrawArrow(int xStart, int yStart, BYTE updown);
//2006-06-02, mimitsai add for HD ui.
void   DrawRectCorner(BTNAREA  Rect, int CornerRad,  BYTE updown, UINT8 step, BYTE Y_1, BYTE Y_2, UINT16 RegionColor_C);
void   ClearRectArea(BTNAREA  Rect, UINT16 RectColorStep, BYTE Y_1, BYTE Y_2, UINT16 CbCr,int iIndex,int iItem);
void   ShowPlayFrame(int x, int y,int len,int high);
void   ShowCurrentDirPlaying();
void   ShowCurrentFilePlaying();
///////////////////////////////////////////////////////////////////////

//module global functions for internal reference
void    DirList();
void    FileList(void);

void    DrawFolderIcon(int x, int y, BYTE type);
void    ShowDirItem(int iItem, const char *s);
void    FSShowDirIcon(void);
void    ShowFileIcon(void);
void    DrawFileIconX(int x, int y, int type, int mono);
#define DrawFileIcon(x,y,t) DrawFileIconX(x,y,t,0)

void    DrawScroll(void);
void    ClearArea(UINT16 iIndex);
void    SelectHL();
void    ShowButtonHL(int x, int y,int len);
//void    ShowHL(int x, int y,int len,int high);
void    ShowHL();
void    FSGUI_FlashFileIcon(int iFlash);
UINT16  CountSpecifyFile(int iDir);
int     PrepareForChangeFilePage(UINT16 iPage, UINT16 iSpecialTrk,UINT16 iDirect);
void    CalcDirNow(UINT16 *iDir);

//module global variables for internal reference
UINT16  Hl_x;
UINT16  Hl_y;
UINT16  Hl_len;
UINT16  Hl_high;
UINT16  Hl_x_btn;
UINT16  Hl_y_btn;
UINT16  Hl_len_btn;
UINT16  old_file_page;	        // index of current page
UINT16  old_dir_page;
UINT16  refresh_file_page;
UINT16  refresh_dir_page;
UINT16  refresh_dir_icon;

#ifdef AUDIO_SHOW_SAVER
BYTE    bDisableGUI = 0;
#endif
// define a struct .


//for draw RECT. zhaoyanhua add 3-7-25 15:01

#include "fsGUIX.h"

//extern const UINT8 pic_cd_str[17];//terry,2004/1/8 06:25PM




void DrawButton(void)
{
#ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
#endif

    //draw MP3 icon
    if (pFsJpeg->gifsMP3Count)
    {
        DrawRect(fsArea[FS_AREA_BUTTON].xStart, fsArea[FS_AREA_BUTTON].yStart,
            48, 48,
            pFsJpeg->gifsFuncBtn == FS_FUNC_MP3 ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
    }
    else
    {
        FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart, fsArea[FS_AREA_BUTTON].yStart,
			48, 48,
            BK_GROUNDY, BK_GROUNDCRCB);
    }
    DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 12, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_MP3BUTTON - 2);

	//draw JPEG icon
	if (pFsJpeg->gifsJPEGCount)
	{
		DrawRect(fsArea[FS_AREA_BUTTON].xStart + 50, fsArea[FS_AREA_BUTTON].yStart, 48, 48,
            pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
	}
	else
	{
		FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 50, fsArea[FS_AREA_BUTTON].yStart,
			48, 48,
            BK_GROUNDY, BK_GROUNDCRCB);
	}
	DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 62, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_JPEGBUTTON - 2);

#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
 //Jeff 20020521
	//draw GAME icon
	if (pFsJpeg->gifsGAMECount)
	{
		DrawRect(fsArea[FS_AREA_BUTTON].xStart + 100, fsArea[FS_AREA_BUTTON].yStart, 48, 48,
            pFsJpeg->gifsFuncBtn == FS_FUNC_GAME? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
	}
	else
	{
		FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 100,  fsArea[FS_AREA_BUTTON].yStart,
			48, 48,
            BK_GROUNDY, BK_GROUNDCRCB);
	}
	DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 112, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_GAMEBUTTON - 2);
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 020930
#ifdef SUPPORT_NESGAME
	if (pFsJpeg->gifsOtherCount)
	{
		DrawRect(fsArea[FS_AREA_BUTTON].xStart + 150, fsArea[FS_AREA_BUTTON].yStart, 48, 48,
            pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
	}
	else
	{
		FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 150, fsArea[FS_AREA_BUTTON].yStart,
			48, 48,
            BK_GROUNDY, BK_GROUNDCRCB);
	}
	DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 162,  fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_OTHERBUTTON - 2);
#else
	if (pFsJpeg->gifsOtherCount)
	{
		DrawRect(fsArea[FS_AREA_BUTTON].xStart + 100,  fsArea[FS_AREA_BUTTON].yStart, 48, 48,
            pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
	}
	else
	{
		FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 100, fsArea[FS_AREA_BUTTON].yStart,
			48, 48,
            BK_GROUNDY, BK_GROUNDCRCB);
	}
	DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 112, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_OTHERBUTTON - 2);
#endif
#endif

#ifdef SUPPORT_MIDI
    #ifdef SUPPORT_NESGAME
	if (pFsJpeg->gifsMidiCount)
	{
		DrawRect(fsArea[FS_AREA_BUTTON].xStart + 200, fsArea[FS_AREA_BUTTON].yStart,
			48, 48,
            pFsJpeg->gifsFuncBtn == FS_FUNC_MIDI? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
	}
	else
	{
		FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 200, fsArea[FS_AREA_BUTTON].yStart,
			48, 48,
            BK_GROUNDY, BK_GROUNDCRCB);
	}
	DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 212, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_MIDIBUTTON - 2);
    #else
	    if (pFsJpeg->gifsMidiCount)
	    {
            DrawRect(fsArea[FS_AREA_BUTTON].xStart + 150, fsArea[FS_AREA_BUTTON].yStart,
			    48, 48,
                pFsJpeg->gifsFuncBtn == FS_FUNC_MIDI? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
	    }
	    else
	    {
		    FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 162, fsArea[FS_AREA_BUTTON].yStart,
			    48, 48,
                BK_GROUNDY, BK_GROUNDCRCB);
	    }
	    DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 87, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_MIDIBUTTON - 2);
    #endif
#endif

	return;
}


/*
 * FUNC: draw slot.
 */
void DrawScroll(void)
{
    int  x, y, xSize, ySize;

    x = fsArea[FS_AREA_SLOT].xStart;
    y = fsArea[FS_AREA_SLOT].yStart;
    xSize = fsArea[FS_AREA_SLOT].xSize;
    ySize = fsArea[FS_AREA_SLOT].ySize;

    FSGUI_FillFrameBuf(x, y+ARROW_SIZE, xSize, ySize-2*ARROW_SIZE, WHITE_Y-0x05, WHITE_CRCB);//terry,2004/1/30 06:54PM
    /*
    FSGUI_FillFrameBuf(x, y, xSize, 1, BLACK_Y, BLACK_CRCB);//top
    FSGUI_FillFrameBuf(x, y, 1, ySize, WHITE_Y, WHITE_CRCB);//left
    FSGUI_FillFrameBuf(x + xSize - 1, y + 1, 1, ySize - 1, WHITE_Y, WHITE_CRCB);//right
    FSGUI_FillFrameBuf(x + 1, y + ySize - 1, xSize - 1, 1 ,WHITE_Y, WHITE_CRCB);//bottom
    */
}


void MoveScroll(UINT16 locate)
{
	int y;

	DrawScroll();
	//draw up and down arrow.
	DrawArrow(fsArea[FS_AREA_MOVEBAR].xStart,fsArea[FS_AREA_MOVEBAR].yStart-ARROW_SIZE,2);
	DrawArrow(fsArea[FS_AREA_MOVEBAR].xStart,fsArea[FS_AREA_MOVEBAR].yStart +fsArea[FS_AREA_MOVEBAR].ySize,1);

	if ((fsArea[FS_AREA_MOVEBAR].ySize - pFsJpeg->scroll_len) >= (pFsJpeg->file_specify_in_dir - 1))
		y = fsArea[FS_AREA_MOVEBAR].yStart + locate * pFsJpeg->scroll_step;
	else
		y = fsArea[FS_AREA_MOVEBAR].yStart + locate * pFsJpeg->scroll_step / 10;


	DrawRect(fsArea[FS_AREA_MOVEBAR].xStart, y, fsArea[FS_AREA_MOVEBAR].xSize, pFsJpeg->scroll_len, 0,
		YELLOW_Y, YELLOW_CRCB);

	//return;//tw 20040201
}





void SelectHL()
{
    int iFiles;

#ifdef MP3_DIRECT_SELECT
    iFiles = pFsJpeg->count_file[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3];
#else
    iFiles = pFsJpeg->file_specify_in_dir;
#endif

   // if (iFiles>999)
        HL_Width =216;
   // else if (iFiles>99)
   //     HL_Width = 108;
  //  else
  //    HL_Width = 100;

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
		ShowCurrentDirPlaying();
	
	ShowCurrentFilePlaying();
	ShowHL();//zhaoyanhua move here 2004-2-2 17:13
}




#ifdef MP3_TXT_DISPLAY
#define LYRECT_XSIZE      145
#define LYRECT_XSTART     25
void ClearLycArea(BTNAREA  Rect, UINT16 RectColorStep,UINT16 RegionColor_C,int ItemStart, int ItemNumber)
{
	int i =0;
	int  x0=0,y0=0;
	UINT8 RegionColor_Y[60];
	int Region[60];
	UINT8 StepCount =0;
	int  xAreaStart=0,yAreaStart = 0, xAreaSize=0,yAreaSize=0;



	// calulate the Y and Region width according to the given step.
		for ( i = 0; i < RectColorStep; i++ )
		{
			Region[i] = Rect.xStart + i*(Rect.xSize / RectColorStep);
			RegionColor_Y[i] = 0x36 + i*((0xc1 - 0x36)/RectColorStep);
			
		}
    
    xAreaStart = LYRECT_XSTART;
	yAreaStart = FS_DIRLIST_YSTART + ItemStart *FS_FILELIST_YSTEP;
	xAreaSize =  LYRECT_XSIZE ;
	yAreaSize =  ItemNumber*FS_FILELIST_YSTEP;

 	StepCount = 0;

	//printf("Region[ 1 ] = %d\n",Region[1]);

 	while(xAreaStart >= Region[StepCount])
 	{
 		StepCount++;
 	}
 	StepCount = StepCount-1;
 	//printf("xAreaStart=%d,Region[%d]=%d\n",xAreaStart,StepCount,Region[StepCount]);

 	for (x0 = xAreaStart; x0 < (xAreaStart+ xAreaSize); x0++)
	{
		if((StepCount +1) < RectColorStep)
		{
			if ((x0 >= Region[StepCount]) && (x0 < Region[StepCount + 1]))
			{
				StepCount++;

			}
 		}
 		else
 			StepCount = RectColorStep -1;

		for (y0 = yAreaStart; y0 < (yAreaStart+yAreaSize); y0++)
		{
			*Y_XY((x0),(y0)) = RegionColor_Y[StepCount];
			*C_XY((x0),(y0)) = RegionColor_C;
		}
	}

}

#endif




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
					//2006-06-02, mimitsai add for HD ui.
					ClearRectArea(Rect[FILE_RECT], FILE_STEP, 0x36, 0xc1, FILE_AREA_BKGROUND_CRCB,FS_AREA_FILEITEM, HL_show);
					
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
					//2006-06-02, mimitsai add for HD ui.				
					ClearRectArea(Rect[DIR_RECT], DIR_STEP, 0x36, 0xc1, DIR_AREA_BKGROUND_CRCB, FS_AREA_DIRITEM, HL_show);
					ShowDirItem(HL_show,iso9660_dir[pFsJpeg->dir_array[HL_show]].name);//resume the last HL
				}
				break;

		case  CNT_AREA_MP3BUTTON:
				{
					DrawRect(fsArea[FS_AREA_BUTTON].xStart, fsArea[FS_AREA_BUTTON].yStart,
					48, 48,
                        pFsJpeg->gifsFuncBtn == FS_FUNC_MP3 ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);

					DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 12, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_MP3BUTTON - 2);
				}
				break;
		case  CNT_AREA_JPEGBUTTON:
				{
                    //FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 3+ 27-1, fsArea[FS_AREA_BUTTON].yStart + 3, 24,24, BK_GROUNDY,BK_GROUNDCRCB);
					DrawRect(fsArea[FS_AREA_BUTTON].xStart+50, fsArea[FS_AREA_BUTTON].yStart,
					48, 48,
                        pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
					DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 62, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_JPEGBUTTON - 2);
				}
				break;
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
		case  CNT_AREA_GAMEBUTTON:
				{
					DrawRect(fsArea[FS_AREA_BUTTON].xStart+100, fsArea[FS_AREA_BUTTON].yStart,
					48, 48,
                        pFsJpeg->gifsFuncBtn == FS_FUNC_GAME ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
					DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 112, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_GAMEBUTTON - 2);
				}
				break;
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE
		case  CNT_AREA_OTHERBUTTON:
			  {
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
                    //FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 3+81, fsArea[FS_AREA_BUTTON].yStart + 3, 19,19, BK_GROUNDY,BK_GROUNDCRCB);
					DrawRect(fsArea[FS_AREA_BUTTON].xStart+150, fsArea[FS_AREA_BUTTON].yStart,
					48, 48,
                        pFsJpeg->gifsFuncBtn == FS_FUNC_GAME ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
					DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 162, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_OTHERBUTTON - 2);
#else
					DrawRect(fsArea[FS_AREA_BUTTON].xStart+100, fsArea[FS_AREA_BUTTON].yStart,
					48, 48,
                        pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);

					DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 112, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_OTHERBUTTON - 2);
#endif
			 }
			break;


#endif

#ifdef SUPPORT_MIDI
		case  CNT_AREA_MIDIBUTTON:
			{
#ifdef SUPPORT_FILE_SYSTEM_MODE
#ifdef SUPPORT_NESGAME
            DrawRect(fsArea[FS_AREA_BUTTON].xStart+200, fsArea[FS_AREA_BUTTON].yStart,
					48, 48,
                        pFsJpeg->gifsFuncBtn == FS_FUNC_MIDI ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
            //FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 3+108, fsArea[FS_AREA_BUTTON].yStart + 3, 19,19, BK_GROUNDY,BK_GROUNDCRCB);
			DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 212, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_MIDIBUTTON - 2);
#else //SUPPORT_NESGAME
            DrawRect(fsArea[FS_AREA_BUTTON].xStart+150, fsArea[FS_AREA_BUTTON].yStart,
					48, 48,
                        pFsJpeg->gifsFuncBtn == FS_FUNC_MIDI ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
			DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 162, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_MIDIBUTTON - 2);
#endif //SUPPORT_NESGAME
#else //SUPPORT_FILE_SYSTEM_MODE
#ifdef SUPPORT_NESGAME
           DrawRect(fsArea[FS_AREA_BUTTON].xStart+150, fsArea[FS_AREA_BUTTON].yStart,
					48, 48,
                        pFsJpeg->gifsFuncBtn == FS_FUNC_MIDI ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);

			DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 162, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_MIDIBUTTON - 2);
#else //SUPPORT_NESGAME
            DrawRect(fsArea[FS_AREA_BUTTON].xStart+100, fsArea[FS_AREA_BUTTON].yStart,
					48, 48,
                        pFsJpeg->gifsFuncBtn == FS_FUNC_MIDI ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
			DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 112, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_MIDIBUTTON - 2);
#endif //SUPPORT_NESGAME
#endif //SUPPORT_FILE_SYSTEM_MODE
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

					FSGUI_FillFrameBuf(fsArea[FS_AREA_FILEITEM].xStart - 2, FS_DIRLIST_YSTART  + HL_show * FS_FILELIST_YSTEP, HL_Width, HL_Heighth, HL_Y, HL_CRCB);
					FSShowFileItem(HL_show , iso9660_file[pFsJpeg->file_array[HL_show]].name);//resume the last HL
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

					FSGUI_FillFrameBuf(fsArea[FS_AREA_DIRITEM].xStart - 2, FS_DIRLIST_YSTART  + HL_show * FS_FILELIST_YSTEP, HL_Width, HL_Heighth, HL_Y, HL_CRCB);
					ShowDirItem(HL_show,iso9660_dir[pFsJpeg->dir_array[HL_show]].name);//resume the last HL
				}
				break;

		case  CNT_AREA_MP3BUTTON:
				{
					old_ControlArea = CNT_AREA_MP3BUTTON;
					FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart , fsArea[FS_AREA_BUTTON].yStart , 48, 48, HL_Y,HL_CRCB);
					DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 12, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_MP3BUTTON - 2);
				}
				break;
		case  CNT_AREA_JPEGBUTTON:
				{
					old_ControlArea = CNT_AREA_JPEGBUTTON;
					FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart+50 , fsArea[FS_AREA_BUTTON].yStart , 48,48, HL_Y,HL_CRCB);
					DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 62, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_JPEGBUTTON - 2);
				}
				break;
#ifdef SUPPORT_NESGAME
		case  CNT_AREA_GAMEBUTTON:
				{
					old_ControlArea = CNT_AREA_GAMEBUTTON;
					FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart +100, fsArea[FS_AREA_BUTTON].yStart , 48,48,HL_Y,HL_CRCB);
					DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 112, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_GAMEBUTTON - 2);
				}
				break;
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE
		case  CNT_AREA_OTHERBUTTON:
			  {
					old_ControlArea = CNT_AREA_OTHERBUTTON;
#ifdef SUPPORT_NESGAME

					FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart +150, fsArea[FS_AREA_BUTTON].yStart , 48,48, HL_Y,HL_CRCB);
					DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 162, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_OTHERBUTTON - 2);
#else
					FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart +100, fsArea[FS_AREA_BUTTON].yStart , 48,48, HL_Y,HL_CRCB);
					DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 112, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_OTHERBUTTON - 2);
#endif
			 }
			break;

#endif
#ifdef SUPPORT_MIDI
		case  CNT_AREA_MIDIBUTTON:
			{
				old_ControlArea = CNT_AREA_MIDIBUTTON;
#ifdef SUPPORT_FILE_SYSTEM_MODE
#ifdef SUPPORT_NESGAME
            FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart +200, fsArea[FS_AREA_BUTTON].yStart , 48,48, HL_Y,HL_CRCB);
			DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 212, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_MIDIBUTTON - 2);
#else //SUPPORT_NESGAME
            FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart +150, fsArea[FS_AREA_BUTTON].yStart , 48,48, HL_Y,HL_CRCB);
			DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 162, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_MIDIBUTTON - 2);
#endif //SUPPORT_NESGAME
#else //SUPPORT_FILE_SYSTEM_MODE
#ifdef SUPPORT_NESGAME
            FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart +150, fsArea[FS_AREA_BUTTON].yStart , 48,48, HL_Y,HL_CRCB);
			DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 162, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_MIDIBUTTON - 2);
#else //SUPPORT_NESGAME
            FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart +100, fsArea[FS_AREA_BUTTON].yStart , 48,48, HL_Y,HL_CRCB);
			DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 112, fsArea[FS_AREA_BUTTON].yStart + 12, CNT_AREA_MIDIBUTTON - 2);
#endif //SUPPORT_NESGAME
#endif //SUPPORT_FILE_SYSTEM_MODE
			}
			break;
#endif

	default: break;
	}

}


