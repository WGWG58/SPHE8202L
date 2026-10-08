/**************************************************************
** FILE
** fsGUI_new.c
**
** DESCRIPTION
** On the base of fsGUI1.c, build a new GUI for MP3/JPEG/GAME.
**
**
**   Creator:   zhaoyanhua
**   Date:     3-7-10 13:24
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
//#include "user_if.h"
//zhaoyanhua add 3-7-25 15:08
#include "fsGUI1.h"
//#include "fsGUI_new.h"

#ifdef JPG_OLD_PARSER_FLOW
    #ifdef JPG_EFFECT
    #include "jpegeffect.h"
    #endif
#else
    #include "pic_effect.h"
#endif


#include "fsGUIX.h"

//extern const UINT8 pic_cd_str[17];//terry,2004/1/8 06:25PM
#ifdef FAT_FILE_MODE//liweihua 2004-10-25 20:15
extern FSJPEGDATA  *pFsJpegbuf;
extern UINT32 iso9660buf;
#endif
#ifdef IDE_CF_SW
extern UINT8 max_part;
#endif//#ifdef IDE_CF_SW

#ifdef CARD_SETUP_TYPE_5
  extern UINT8 PMP_CF_Card_Insert;
#endif

#ifdef FILE_MODE_WRITE
extern BYTE     *mediaStr[];
extern BYTE     srceType_flag;
extern FSJPEGDATA  *pFsJpeg_des_buf; 
extern UINT32 iso9660buf_src;
extern UINT32 iso9660buf_des;
void Draw_File_Mode_Button(void);
extern void ShowFileItem(UINT16, int);
#endif
/*
 * FUNC: draw slot.
 */
void DrawScroll(UINT8 area)
{
    int  x, y, xSize, ySize;
    x = fsArea[area].xStart;
    y = fsArea[area].yStart;
    xSize = fsArea[area].xSize;
    ySize = fsArea[area].ySize;

    #ifdef PHILIPS_FSGUI//chenzhao20050613
    FSGUI_FillFrameBuf(x+1, y+ARROW_SIZE, xSize-2, ySize-2*ARROW_SIZE, PREVIEW_BKGROUND_Y, FILE_AREA_BKGROUND_CRCB);//terry,2004/1/30 06:54PM
	#elif defined(INDIGO_STYLE_FSGUI)	
	FSGUI_FillFrameBuf(      x,       y, xSize, ySize, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB); // clear bg
    FSGUI_FillFrameBuf(      x,       y, xSize,     1, SCROLL_LINE_Y,SCROLL_LINE_CbCr); // top line
    FSGUI_FillFrameBuf(      x,       y,     1, ySize, SCROLL_LINE_Y,SCROLL_LINE_CbCr); // left line
    FSGUI_FillFrameBuf(x+xSize,       y,     1, ySize, SCROLL_LINE_Y,SCROLL_LINE_CbCr); // right line	
    FSGUI_FillFrameBuf(      x, y+ySize, xSize,     1, SCROLL_LINE_Y,SCROLL_LINE_CbCr); // bottom line
    #else
    FSGUI_FillFrameBuf(x, y+ARROW_SIZE, xSize, ySize-2*ARROW_SIZE, WHITE_Y-0x05, WHITE_CRCB);//terry,2004/1/30 06:54PM
    #endif
}

void MoveScroll(UINT16 locate, UINT8 area)
{
	int y, fileOrDirCount,scroll_length, scroll_step;
	if(area == FS_AREA_MOVEBAR)	
	{
		DrawScroll(FS_AREA_SLOT);   
		fileOrDirCount 	= pFsJpeg->file_specify_in_dir;
		scroll_step 	= pFsJpeg->scroll_step;
		scroll_length	= pFsJpeg->scroll_len;
	}
#ifdef DIR_SCROLL_BAR
	else
{
		int iDirCount=0, total_dir=0;
		for (iDirCount = 0; iDirCount < pFsJpeg->fsnav_dir_cnt; iDirCount++)
		{
			if (iso9660_dir[iDirCount].type & (0x01 << pFsJpeg->gifsFuncBtn))
	            total_dir++;
		}
	    pFsJpeg->dir_count_in_specity_Category = total_dir;
		DrawScroll(FS_DIR_AREA_SLOT); 

		fileOrDirCount 	= pFsJpeg->dir_count_in_specity_Category;
		scroll_step 	= pFsJpeg->dir1_scroll_step;
		scroll_length	= pFsJpeg->dir1_scroll_len;
	}
#endif	

	#ifndef INDIGO_STYLE_FSGUI
    DrawArrow(fsArea[area].xStart,fsArea[area].yStart-ARROW_SIZE,2);
    DrawArrow(fsArea[area].xStart,fsArea[area].yStart +fsArea[area].ySize,1);
	#endif

    if ((fsArea[area].ySize - scroll_length) >= (fileOrDirCount - 1))
        y = fsArea[area].yStart + locate * scroll_step;
    else
        y = fsArea[area].yStart + locate * scroll_step / 10;

	#ifdef INDIGO_STYLE_FSGUI
	FSGUI_FillFrameBuf(fsArea[area].xStart, y, fsArea[area].xSize, scroll_length, SCROLL_LINE_Y, SCROLL_LINE_CbCr);
	#else
    DrawRect(fsArea[area].xStart, y, fsArea[area].xSize, scroll_length, 0, YELLOW_Y, YELLOW_CRCB);
	#endif
}


#ifdef INDIGO_STYLE_FSGUI
//2006-06-02, mimitsai add for HD ui.
#ifdef INDIGO_STYLE_LARGE_FSGUI
#define lineWid	3
#else
#define lineWid	1
#endif
void DrawBottomOutLine(UINT16 x, UINT16 y, UINT16 wid, UINT16 hei, UINT8 color_y, UINT16 color_cbcr)
{
	FSGUI_FillFrameBuf( x    -lineWid,  y   -lineWid,         wid, lineWid, color_y, color_cbcr);
	FSGUI_FillFrameBuf( x    -lineWid,  y   -lineWid,     lineWid,     hei, color_y, color_cbcr);
	FSGUI_FillFrameBuf( x+wid-lineWid,  y   -lineWid,     lineWid,     hei, color_y, color_cbcr);
	FSGUI_FillFrameBuf( x    -lineWid, y+hei-lineWid, wid+lineWid, lineWid, color_y, color_cbcr);		
}
//2006-06-02, mimitsai add for HD ui.
void DrawSelectedBottomOutLine(UINT16 x, UINT16 y, UINT16 wid, UINT16 hei)
{
	FSGUI_FillFrameBuf( x    -lineWid,  y   -lineWid,         wid, lineWid, BK_GROUNDY, BK_GROUNDCRCB);
	FSGUI_FillFrameBuf( x    -lineWid,  y   -lineWid,     lineWid,     hei, BK_GROUNDY, BK_GROUNDCRCB);
	FSGUI_FillFrameBuf( x+wid-lineWid,  y   -lineWid,     lineWid,     hei, (RGB2Y (125, 128, 156)), (RGB2Cr(125, 128, 156)<<8)|(RGB2Cb(125, 128, 156)));
	FSGUI_FillFrameBuf( x    -lineWid, y+hei-lineWid, wid+lineWid, lineWid, (RGB2Y (125, 128, 156)), (RGB2Cr(125, 128, 156)<<8)|(RGB2Cb(125, 128, 156)));		
}
#endif


void SelectHL()
{
    int iFiles;

#ifdef MP3_DIRECT_SELECT
    iFiles = pFsJpeg->count_file[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3];
#else
    iFiles = pFsJpeg->file_specify_in_dir;
#endif

// 2004/04/20 yltseng, to make HL wider for Chinse Font and Joliet
#ifdef INDIGO_STYLE_FSGUI
    HL_Width = ITEM_MAX_WIDTH;
#else
#if defined (SUPPORT_FONT_UTIL) || defined (SUPPORT_JOLIET_FORMAT)  // 2005/02/16 yltseng
	#ifdef DIR_SCROLL_BAR
    	HL_Width = 110;;
    #else
    HL_Width = 116;
	#endif
#else
    if (iFiles>999)
        HL_Width = 116;
    else if (iFiles>99)
        HL_Width = 108;
    else
	#ifdef DIR_SCROLL_BAR
        HL_Width = 110;
    #else
        HL_Width = 116;
#endif
#endif
#endif


    //ShowHL();//move to the last of SelectHL() zhaoyanhua  2004-2-2 17:13
#ifdef MP3_TXT_DISPLAY //zhaoyanhua add 2003-9-2 9:40
    if ( ( (JPEG_Preview_drawed == DIR_LIST_IN_DIR_AREA)
         &&(pFsJpeg->gifsFuncBtn != FS_FUNC_MP3) )
      || ( (MP3_Lyrics_Drawed == DIR_LIST_IN_DIR_AREA)
         &&(pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)))//zhaoyanhua modify 2003-8-28 13:29
#else
    //to avoid the bug : when play JPEG, BUTTON->FILE  (RIGHT) or(UP) ,not draw DIR playing again.
    //zhaoyanhua modify 2003-12-27 11:10
    if ( ((JPEG_Preview_drawed == DIR_LIST_IN_DIR_AREA) //&&(!(pFsJpeg->gifsbPreview))
        &&(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG))//for JPEG 
      ||((JPEG_Preview_drawed == DIR_LIST_IN_DIR_AREA) && (pFsJpeg->gifsFuncBtn != FS_FUNC_JPEG))//for MP3/OTHER 
       )
#endif
        ShowCurrentDirPlaying();
    
    ShowCurrentFilePlaying();
    ShowHL();//zhaoyanhua move here 2004-2-2 17:13
}


#ifdef READ_FAT_LONGNAME //linrc 2005-3-17 10:58
BYTE dFlag;
#endif
void ShowHL(void)
{
    #ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
    #endif

    #if defined(FAT_FILE_MODE)||defined(FILE_MODE_WRITE)
    FSJPEGDATA  *addr1;
    UINT32 addr2;
    BYTE j;
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
            {//2006-06-02, mimitsai add for HD ui.
			   	ClearRectArea(Rect[FILE_RECT], FILE_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, FILE_AREA_BKGROUND_CRCB,FS_AREA_FILEITEM, HL_show);
                FSShowFileItem(HL_show, iso9660_file[pFsJpeg->file_array[HL_show]].name);//resume the last HL
            }
            break;
        case  CNT_AREA_DIR:
            //zhaoyanhua add 2004-2-2 16:54
            //make some changes for the GUI not blink .
            if(HL_show == fsnav_dir_HL)
                ShowCurrentDirPlaying();
            else
            {//2006-06-02, mimitsai add for HD ui.
				ClearRectArea(Rect[DIR_RECT], DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB, FS_AREA_DIRITEM, HL_show);
                ShowDirItem(HL_show,iso9660_dir[pFsJpeg->dir_array[HL_show]].name);//resume the last HL
            }
            break;

        case  CNT_AREA_MP3BUTTON:
            {
			#ifdef INDIGO_STYLE_FSGUI
				if(pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
					DrawSelectedBottomOutLine(fsArea[FS_AREA_MP3_BUTTON].xStart, fsArea[FS_AREA_MP3_BUTTON].yStart, fsArea[FS_AREA_MP3_BUTTON].xSize, fsArea[FS_AREA_MP3_BUTTON].ySize);	
				else
					DrawBottomOutLine(fsArea[FS_AREA_MP3_BUTTON].xStart,fsArea[FS_AREA_MP3_BUTTON].yStart, fsArea[FS_AREA_MP3_BUTTON].xSize  ,fsArea[FS_AREA_MP3_BUTTON].ySize, HIGHLIGHT_BG_COLOR_Y, HIGHLIGHT_BG_COLOR_CbCr);
			#else	
                DrawRect(fsArea[FS_AREA_BUTTON].xStart, fsArea[FS_AREA_BUTTON].yStart,
                		25, 25,
                    	pFsJpeg->gifsFuncBtn == FS_FUNC_MP3 ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
                DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2);
			#endif					
            }
            break;
        case  CNT_AREA_JPEGBUTTON:
            {
			#ifdef INDIGO_STYLE_FSGUI
				if(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
					DrawSelectedBottomOutLine(fsArea[FS_AREA_JPG_BUTTON].xStart, fsArea[FS_AREA_JPG_BUTTON].yStart, fsArea[FS_AREA_JPG_BUTTON].xSize, fsArea[FS_AREA_JPG_BUTTON].ySize);	
				else
					DrawBottomOutLine(fsArea[FS_AREA_JPG_BUTTON].xStart,fsArea[FS_AREA_JPG_BUTTON].yStart, fsArea[FS_AREA_JPG_BUTTON].xSize  ,fsArea[FS_AREA_JPG_BUTTON].ySize, HIGHLIGHT_BG_COLOR_Y, HIGHLIGHT_BG_COLOR_CbCr);
			#else	
                DrawRect(fsArea[FS_AREA_BUTTON].xStart+27, fsArea[FS_AREA_BUTTON].yStart,
                		25, 25,
                    	pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
                DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 33, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_JPEGBUTTON - 2);
			#endif
            }
            break;

#ifdef SUPPORT_NESGAME
        case  CNT_AREA_GAMEBUTTON:
            {
			#ifdef INDIGO_STYLE_FSGUI
				if(pFsJpeg->gifsFuncBtn == FS_FUNC_GAME)
					DrawSelectedBottomOutLine(fsArea[FS_AREA_GAME_BUTTON].xStart, fsArea[FS_AREA_GAME_BUTTON].yStart, fsArea[FS_AREA_GAME_BUTTON].xSize, fsArea[FS_AREA_GAME_BUTTON].ySize);	
				else
					DrawBottomOutLine(fsArea[FS_AREA_GAME_BUTTON].xStart,fsArea[FS_AREA_GAME_BUTTON].yStart, fsArea[FS_AREA_GAME_BUTTON].xSize  ,fsArea[FS_AREA_GAME_BUTTON].ySize, HIGHLIGHT_BG_COLOR_Y, HIGHLIGHT_BG_COLOR_CbCr);
			#else	
                DrawRect(fsArea[FS_AREA_BUTTON].xStart+54, fsArea[FS_AREA_BUTTON].yStart,
                		25, 25,
                    	pFsJpeg->gifsFuncBtn == FS_FUNC_GAME ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
                DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 60, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_GAMEBUTTON - 2);
			#endif
            }
            break;
#endif

#ifdef SUPPORT_FILE_SYSTEM_MODE
        case  CNT_AREA_OTHERBUTTON:
			{
			#ifdef INDIGO_STYLE_FSGUI
				if(pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)
					DrawSelectedBottomOutLine(fsArea[FS_AREA_OTHER_BUTTON].xStart, fsArea[FS_AREA_OTHER_BUTTON].yStart, fsArea[FS_AREA_OTHER_BUTTON].xSize, fsArea[FS_AREA_OTHER_BUTTON].ySize);	
				else
					DrawBottomOutLine(fsArea[FS_AREA_OTHER_BUTTON].xStart,fsArea[FS_AREA_OTHER_BUTTON].yStart, fsArea[FS_AREA_OTHER_BUTTON].xSize  ,fsArea[FS_AREA_OTHER_BUTTON].ySize, HIGHLIGHT_BG_COLOR_Y, HIGHLIGHT_BG_COLOR_CbCr);
			#else	
#ifdef SUPPORT_NESGAME
                DrawRect(fsArea[FS_AREA_BUTTON].xStart+81, fsArea[FS_AREA_BUTTON].yStart,
                		25, 25,
                    	pFsJpeg->gifsFuncBtn == FS_FUNC_GAME ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
                DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 87, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_OTHERBUTTON - 2);
#else
                DrawRect(fsArea[FS_AREA_BUTTON].xStart+54, fsArea[FS_AREA_BUTTON].yStart,
                		25, 25,
                    	pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
                DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 60, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_OTHERBUTTON - 2);
#endif
			#endif
			}
			break;
#endif

#ifdef SUPPORT_MIDI
        case  CNT_AREA_MIDIBUTTON:
            {
#ifdef SUPPORT_FILE_SYSTEM_MODE
#ifdef SUPPORT_NESGAME
            DrawRect(fsArea[FS_AREA_BUTTON].xStart+108, fsArea[FS_AREA_BUTTON].yStart,
                    25, 25,
                        pFsJpeg->gifsFuncBtn == FS_FUNC_MIDI ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
            //FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 3+108, fsArea[FS_AREA_BUTTON].yStart + 3, 19,19, BK_GROUNDY,BK_GROUNDCRCB);
            DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 114, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MIDIBUTTON - 2);
#else //SUPPORT_NESGAME
            DrawRect(fsArea[FS_AREA_BUTTON].xStart+81, fsArea[FS_AREA_BUTTON].yStart,
                    25, 25,
                        pFsJpeg->gifsFuncBtn == FS_FUNC_MIDI ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
            DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 87, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MIDIBUTTON - 2);
#endif //SUPPORT_NESGAME
#else //SUPPORT_FILE_SYSTEM_MODE
#ifdef SUPPORT_NESGAME
           DrawRect(fsArea[FS_AREA_BUTTON].xStart+81, fsArea[FS_AREA_BUTTON].yStart,
                    25, 25,
                        pFsJpeg->gifsFuncBtn == FS_FUNC_MIDI ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);

            DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 87, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MIDIBUTTON - 2);
#else //SUPPORT_NESGAME
            DrawRect(fsArea[FS_AREA_BUTTON].xStart+54, fsArea[FS_AREA_BUTTON].yStart,
                    25, 25,
                        pFsJpeg->gifsFuncBtn == FS_FUNC_MIDI ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
            DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 60, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MIDIBUTTON - 2);
#endif //SUPPORT_NESGAME
#endif //SUPPORT_FILE_SYSTEM_MODE
            }
            break;
#endif
#ifdef SUPPORT_PLAYLIST	//wanghaoying 2005-9-28 19:23
        case CNT_AREA_PLAYLISTBUTTON:
            DrawRect(fsArea[FS_AREA_BUTTON].xStart+81, fsArea[FS_AREA_BUTTON].yStart,
                    25, 25,
                        pFsJpeg->gifsFuncBtn == FS_FUNC_PLAYLIST ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
            DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 87, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_PLAYLISTBUTTON - 2);
            
            break;
#endif
#ifdef SUPPORT_MULTI_PARTITION
        case CNT_AREA_MULTI_PART:
            if(pFsJpeg->gifsState == FS_STATE_HDD)
            {
                if(HL_show == pFsJpeg->part_will)
                    ShowCurrentMultiPart();
                else
                {//2006-06-02, mimitsai add for HD ui.
                    ClearRectArea(Rect[6], DIR_STEP, 0x36, 0xc1, DIR_AREA_BKGROUND_CRCB, FS_AREA_DIRITEM, HL_show);
                    if((HL_show == max_part)&&PMP_CF_Card_IsPlugIn())//liweihua mod 2004-11-30
                       ShowHDDItem(fsArea[FS_AREA_DIRITEM].xStart,HL_show, "CF CARD",0);
                    else
                       ShowHDDItem(fsArea[FS_AREA_DIRITEM].xStart,HL_show, "LOCAL DISK",0);
                }        
            } 
            #ifdef PMP_UI //liweihua 2004-12-30 9:55      
            else if((pFsJpeg->gifsState == FS_STATE_INIT)||(pFsJpeg->gifsState == FS_STATE_MP3))//kenny 2005/6/27
            {
                #ifdef READ_FAT_LONGNAME   //linrc 2005-3-17 10:58
                dFlag = 1;
            	#endif
       			//2006-06-02, mimitsai add for HD ui.
                ClearRectArea(Rect[6], DIR_STEP, 0x36, 0xc1, DIR_AREA_BKGROUND_CRCB, FS_AREA_DIRITEM, HL_show);
                ShowItemHL(HL_show);
            }
            #endif//#ifdef PMP_UI //liweihua 2004-12-30 9:55      
            break;
    #ifdef FAT_FILE_MODE//liweihua 2004-10-10 22:10
        case CNT_AREA_DISK:
                {
                    addr1 = pFsJpeg;
                    addr2 = _fs9660_buf;
                    pFsJpeg = &(share_data.JPEG);
                    _fs9660_buf = SDRAM_BASE + HD_FS_STRUCTURE_YA * 1024;

                    //2006-06-02, mimitsai add for HD ui.
					ClearRectArea(Rect[FS_AREA_DIRITEM], DIR_STEP, 0x36, 0xc1, DIR_AREA_BKGROUND_CRCB, FS_AREA_DIRITEM, HL_show);
					
                    //draw the selected rec,liweihua add 2004-11-17
                    if(((HL_show == pFsJpeg->part_current-1)&&(pFsJpeg->gifsState == FS_STATE_HDD))
                        ||((HL_show == pFsJpeg->file_current_in_page)&&(pFsJpeg->gifsState != FS_STATE_HDD))
                        )
                        ShowPlayFrame(fsArea[FS_AREA_DIRITEM].xStart-2,fsArea[FS_AREA_DIRITEM].yStart + 16*HL_show,78,14);
                    if(pFsJpeg->gifsState == FS_STATE_HDD)
                        ShowHDDItem(fsArea[FS_AREA_DIRITEM].xStart,HL_show, "DISK",0);
                    else
                        ShowItem(HL_show);
                    pFsJpeg = addr1;
                    _fs9660_buf = addr2;
                }
             break;
        case CNT_AREA_CARD:
                {
                    BYTE width;
                    addr1 = pFsJpeg;
                    addr2 = _fs9660_buf;
                    pFsJpeg = pFsJpegbuf;
                    _fs9660_buf = iso9660buf;
                    if(pFsJpeg->gifsState == FS_STATE_HDD)//liweihua mod 2004-11-30
                        width = 94;
                    else
                        width = 78;
                    //2006-06-02, mimitsai add for HD ui.
                    ClearRectArea(Rect[FILE_RECT], FILE_STEP, 0x36, 0xc1, FILE_AREA_BKGROUND_CRCB,FS_AREA_FILEITEM, HL_show);
                    
                    //draw the selected rec,liweihua add 2004-11-17
                    if(((HL_show == pFsJpeg->part_current)&&(pFsJpeg->gifsState == FS_STATE_HDD))
                        ||((HL_show == pFsJpeg->file_current_in_page)&&(pFsJpeg->gifsState != FS_STATE_HDD))
                        )
                        ShowPlayFrame(fsArea[FS_AREA_FILEITEM].xStart-2,fsArea[FS_AREA_FILEITEM].yStart + 16*HL_show,width,14);
                    if(pFsJpeg->gifsState == FS_STATE_HDD)
                        ShowCardItem(HL_show,"CF CARD",0);
                    else
                        ShowItem(HL_show);
                    pFsJpeg = addr1;
                    _fs9660_buf = addr2;                    
                }
             break;
        case CNT_AREA_WARNING:
                {
                    //2006-06-02, mimitsai add for HD ui.
                    ClearRectArea(Rect[FS_AREA_DIRITEM], 0x36, 0xc1, DIR_STEP, DIR_AREA_BKGROUND_CRCB, FS_AREA_DIRITEM, HL_show);
                    ShowWarning("TESTTEST");
                }
             break;
    
    #endif//#ifdef FAT_FILE_MODE
#endif
#ifdef FILE_MODE_WRITE     //sunzhh 2005-01-06
        case CNT_AREA_SRCE:
                {
                    int j;
                    addr1 = pFsJpeg;
                    addr2 = _fs9660_buf;
                    pFsJpeg = &(share_data.JPEG);                    
                    _fs9660_buf = SDRAM_BASE + FS9660YA * 1024;
                    if(pFsJpeg->gifsState == FS_STATE_MEDIA)
                        j = 1;
                    else
                        j = 0;

                    //2006-06-02, mimitsai add for HD ui.
                    ClearRectArea(Rect[FS_AREA_DIRITEM], DIR_STEP, 0x36, 0xc1, DIR_AREA_BKGROUND_CRCB, FS_AREA_DIRITEM, HL_show-j);                            
                    
                    if(((HL_show == pFsJpeg->media_current)&&(pFsJpeg->gifsState == FS_STATE_MEDIA))
                    ||((HL_show == pFsJpeg->file_current_in_page)&&(pFsJpeg->gifsState != FS_STATE_MEDIA))
                    )
                        ShowPlayFrame(fsArea[FS_AREA_DIRITEM].xStart-2,fsArea[FS_AREA_DIRITEM].yStart + 16*(HL_show-j),94,14);                                                                         
                    if(pFsJpeg->gifsState == FS_STATE_MEDIA)
                            FSGUI_ShowString( FS_DIRLIST_XSTART,(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * (HL_show-1) ), mediaStr[HL_show], FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);        
                    else 
                        ShowFileItem(FS_DIRLIST_XSTART, HL_show);  
//                    FSShowFatIcon(fsArea[FS_AREA_DIRICON].xStart,HL_show-1); 
                }
                pFsJpeg = addr1;
                _fs9660_buf = addr2;                
             break;
        case CNT_AREA_DEST:
                {
                    addr1 = pFsJpeg;
                    addr2 = _fs9660_buf;
                    pFsJpeg = pFsJpeg_des_buf;
                    _fs9660_buf = iso9660buf_des;
                    if((!srceType_flag)&&(pFsJpeg->gifsState == FS_STATE_MEDIA))
                        j = 1;
                    else if((srceType_flag == 1)&&(pFsJpeg->gifsState == FS_STATE_MEDIA))
                        j = 2;                        
                    else
                        j = 0;          

                    //2006-06-02, mimitsai add for HD ui.
                    ClearRectArea(Rect[FILE_RECT], FILE_STEP, 0x36, 0xc1, FILE_AREA_BKGROUND_CRCB,FS_AREA_FILEITEM, HL_show-j);                    
                    
                    if(((HL_show == pFsJpeg->media_current)&&(pFsJpeg->gifsState == FS_STATE_MEDIA))
                    ||((HL_show == pFsJpeg->file_current_in_page)&&(pFsJpeg->gifsState != FS_STATE_MEDIA))
                    )
                        ShowPlayFrame(fsArea[FS_AREA_FILEITEM].xStart+2,fsArea[FS_AREA_FILEITEM].yStart + 16*(HL_show-j),94,14);                                                
                    if(pFsJpeg->gifsState == FS_STATE_MEDIA)
                        FSGUI_ShowString( fsArea[FS_AREA_FILEITEM].xStart+4,(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * (HL_show-j) ), mediaStr[HL_show], FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);        
//                        FSShowFatIcon(FS_AREA_FILEICON,HL_show-j); 
                    else 
                        ShowFileItem( fsArea[FS_AREA_FILEITEM].xStart+4, HL_show);  
                    pFsJpeg = addr1;
                    _fs9660_buf = addr2;                    
                }
             break;
        case  CNT_AREA_COPYBUTTON:
        case  CNT_AREA_DELETEBUTTON:
        case  CNT_AREA_NEWBUTTON:
        case  CNT_AREA_RENAMEBUTTON:
        case  CNT_AREA_FORMATBUTTON:                                                                     
        case  CNT_AREA_CAPACITYBUTTON:
            Draw_File_Mode_Button();
            break;
             
#endif
        default: break;
   }

    #ifdef PHILIPS_FSGUI//chenzhao20050613
    file_focus_y = FS_FONTCOLOR_FILE_HL_Y;
    file_focus_CrCb = FS_FONTCOLOR_FILE_HL_CrCb;
    #endif
    // draw current HL
    switch (pFsJpeg->ControlArea)
    {
        case  CNT_AREA_FILE:
                {
                    HL_show = pFsJpeg->file_will;
		 #ifdef FS_SLECTE_FONT_COLOR //qinhua,2006-3-14 03:09下午
                     char buf[20];
		    psprintf(buf, "%02d.%s", HL_show+1,iso9660_file[pFsJpeg->file_array[HL_show]].name);
		   #ifdef MP3_DIRECT_SELECT
		       if(pFsJpeg->count_file[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3] >= 1000)
		    psprintf(buf, "%04d.%s", HL_show+1, iso9660_file[pFsJpeg->file_array[HL_show]].name);
		        else if(pFsJpeg->count_file[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3] >= 100)
		   #else
			if(pFsJpeg->file_specify_in_dir >= 1000)
				psprintf(buf, "%04d.%s", HL_show+1, iso9660_file[pFsJpeg->file_array[HL_show]].name);
			if(pFsJpeg->file_specify_in_dir >= 100)
		    #endif
			 psprintf(buf, "%03d.%s", HL_show+1, iso9660_file[pFsJpeg->file_array[HL_show]].name);
			else
		       psprintf(buf, "%02d.%s", HL_show+1, iso9660_file[pFsJpeg->file_array[HL_show]].name);
                   #endif//#ifdef FS_SLECTE_FONT_COLOR //qinhua,2006-3-14 03:09下午
                    old_ControlArea = CNT_AREA_FILE;

                    FSGUI_FillFrameBuf(fsArea[FS_AREA_FILEITEM].xStart - 2, FS_DIRLIST_YSTART  + HL_show * FS_FILELIST_YSTEP, HL_Width, HL_Heighth, HL_Y, HL_CRCB);
                  #ifdef FS_SLECTE_FONT_COLOR //qinhua,2006-3-14 03:09下午
                   FSGUI_ShowString(fsArea[FS_AREA_FILEITEM].xStart,
			(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * HL_show),
			buf, FS_FONTCOLOR_FILE_Y_SL, FS_FONTCOLOR_FILE_CrCb_SL );
                  #else
                    FSShowFileItem(HL_show , iso9660_file[pFsJpeg->file_array[HL_show]].name);//resume the last HL
                  #endif  
                    /// NOTE:
                    // These code are put here ,for they will used by FSGUI_Refresh()/FSGUI_CmdLeft/FSGUI_CmdRight()
                    // if MP3_Lyrics_Drawed is 1,then show lyrics.
                    //zhaoyanhua add 2003-9-1 17:49
                    #ifdef MP3_TXT_DISPLAY
				    if(MP3TotalNo)		//linrc for bug 2005-11-3 17:11
				    {
                    ShowLyricsWhileHL();
                	}
                    #endif    
                }
                break;
        case  CNT_AREA_DIR:
                {
                    HL_show = pFsJpeg->dir_current;
                  #ifdef FS_SLECTE_FONT_COLOR  //qinhua,2006-3-14 03:09下午
                    char buf[20];
                  if ( strcmp(iso9660_dir[pFsJpeg->dir_array[HL_show]].name, "")==0 )
                    {
	            psprintf(buf, "%02d.\\", HL_show+1);
      	             }               
	            else
	             {
	        	psprintf(buf, "%02d.%s",HL_show+1, iso9660_dir[pFsJpeg->dir_array[HL_show]].name);
	              }
                   
                  #endif  
                    old_ControlArea = CNT_AREA_DIR;

                    FSGUI_FillFrameBuf(fsArea[FS_AREA_DIRITEM].xStart - 2, FS_DIRLIST_YSTART  + HL_show * FS_FILELIST_YSTEP, HL_Width, HL_Heighth, HL_Y, HL_CRCB);
               #ifdef FS_SLECTE_FONT_COLOR//qinhua,2006-3-14 03:09下午
                    FSGUI_ShowString(fsArea[FS_AREA_DIRITEM].xStart,
	        	(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * HL_show ),
			buf, FS_FONTCOLOR_FILE_Y_SL, FS_FONTCOLOR_FILE_CrCb_SL );
	        #else
                    ShowDirItem(HL_show,iso9660_dir[pFsJpeg->dir_array[HL_show]].name);//resume the last HL
                #endif 
                }
                break;

        case  CNT_AREA_MP3BUTTON:
                {
                    old_ControlArea = CNT_AREA_MP3BUTTON;
                    #ifdef PHILIPS_FSGUI//chenzhao20050613
                    FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart , fsArea[FS_AREA_BUTTON].yStart , 25,25,BUTTOM_HL_Y,BUTTOM_HL_CRCB);
                    #else
					#ifdef INDIGO_STYLE_FSGUI
						// clear other bottom
						DrawBottomOutLine(fsArea[FS_AREA_MP3_BUTTON].xStart  ,fsArea[FS_AREA_MP3_BUTTON].yStart  , fsArea[FS_AREA_MP3_BUTTON].xSize  ,fsArea[FS_AREA_MP3_BUTTON].ySize  , HIGHLIGHT_COLOR_Y   , HIGHLIGHT_COLOR_CbCr);
					#else					
                    FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart , fsArea[FS_AREA_BUTTON].yStart , 25,25,HL_Y,HL_CRCB);
                    #endif
                #endif

				#ifdef INDIGO_STYLE_FSGUI
					DrawFileIcon(fsArea[FS_AREA_MP3_BUTTON].xStart+BTN_XOFFSET_FROM_OUTLINE, fsArea[FS_AREA_MP3_BUTTON].yStart+BTN_YOFFSET_FROM_OUTLINE, CNT_TAB_MP3BUTTON - 2);
				#else					
                    DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2);
				#endif
                }
                break;
        case  CNT_AREA_JPEGBUTTON:
                {
                    old_ControlArea = CNT_AREA_JPEGBUTTON;
                    #ifdef PHILIPS_FSGUI//chenzhao20050613
                    FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart+27 , fsArea[FS_AREA_BUTTON].yStart , 25,25, BUTTOM_HL_Y,BUTTOM_HL_CRCB);
                    #else
					#ifdef INDIGO_STYLE_FSGUI
						// clear other bottom
						DrawBottomOutLine(fsArea[FS_AREA_JPG_BUTTON].xStart  ,fsArea[FS_AREA_JPG_BUTTON].yStart  , fsArea[FS_AREA_JPG_BUTTON].xSize  ,fsArea[FS_AREA_JPG_BUTTON].ySize  , HIGHLIGHT_COLOR_Y   , HIGHLIGHT_COLOR_CbCr);
					#else					
                    FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart+27 , fsArea[FS_AREA_BUTTON].yStart , 25,25, HL_Y,HL_CRCB);
                    #endif
                #endif

				#ifdef INDIGO_STYLE_FSGUI
					DrawFileIcon(fsArea[FS_AREA_JPG_BUTTON].xStart+BTN_XOFFSET_FROM_OUTLINE, fsArea[FS_AREA_JPG_BUTTON].yStart+BTN_YOFFSET_FROM_OUTLINE, CNT_TAB_JPEGBUTTON - 2);
				#else					
                    DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 33, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_JPEGBUTTON - 2);
				#endif
                }
                break;
#ifdef SUPPORT_NESGAME
        case  CNT_AREA_GAMEBUTTON:
                {
                    old_ControlArea = CNT_AREA_GAMEBUTTON;
					#ifdef INDIGO_STYLE_FSGUI
						// clear other bottom
						DrawBottomOutLine(fsArea[FS_AREA_GAME_BUTTON].xStart  ,fsArea[FS_AREA_GAME_BUTTON].yStart  , fsArea[FS_AREA_GAME_BUTTON].xSize  ,fsArea[FS_AREA_GAME_BUTTON].ySize  , HIGHLIGHT_COLOR_Y   , HIGHLIGHT_COLOR_CbCr);
					#else					
                    FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart +54, fsArea[FS_AREA_BUTTON].yStart , 25,25,HL_Y,HL_CRCB);
					#endif					
 				#ifdef INDIGO_STYLE_FSGUI
					DrawFileIcon(fsArea[FS_AREA_GAME_BUTTON].xStart+BTN_XOFFSET_FROM_OUTLINE, fsArea[FS_AREA_GAME_BUTTON].yStart+BTN_YOFFSET_FROM_OUTLINE, CNT_TAB_GAMEBUTTON - 2);
				#else					
                    DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 60, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_GAMEBUTTON - 2);
				#endif				
                }
                break;
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE
        case  CNT_AREA_OTHERBUTTON:
              {
                    old_ControlArea = CNT_AREA_OTHERBUTTON;
#ifdef SUPPORT_NESGAME

				#ifdef INDIGO_STYLE_FSGUI
					// clear other bottom
					DrawBottomOutLine(fsArea[FS_AREA_OTHER_BUTTON].xStart  ,fsArea[FS_AREA_OTHER_BUTTON].yStart  , fsArea[FS_AREA_OTHER_BUTTON].xSize  ,fsArea[FS_AREA_OTHER_BUTTON].ySize  , HIGHLIGHT_COLOR_Y   , HIGHLIGHT_COLOR_CbCr);
				#else
                    FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart +81, fsArea[FS_AREA_BUTTON].yStart , 25,25, HL_Y,HL_CRCB);
				#endif				

 				#ifdef INDIGO_STYLE_FSGUI
					DrawFileIcon(fsArea[FS_AREA_OTHER_BUTTON].xStart+BTN_XOFFSET_FROM_OUTLINE, fsArea[FS_AREA_OTHER_BUTTON].yStart+BTN_YOFFSET_FROM_OUTLINE, CNT_TAB_OTHERBUTTON - 2);
				#else					
                    DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 87, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_OTHERBUTTON - 2);
				#endif				

#else
                    #ifdef PHILIPS_FSGUI//chenzhao20050613
                    FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart +54, fsArea[FS_AREA_BUTTON].yStart , 25,25, BUTTOM_HL_Y,BUTTOM_HL_CRCB);
                    #else
					#ifdef INDIGO_STYLE_FSGUI
						DrawBottomOutLine(fsArea[FS_AREA_OTHER_BUTTON].xStart,fsArea[FS_AREA_OTHER_BUTTON].yStart, fsArea[FS_AREA_OTHER_BUTTON].xSize,fsArea[FS_AREA_OTHER_BUTTON].ySize, HIGHLIGHT_COLOR_Y, HIGHLIGHT_COLOR_CbCr);
					#else					
                    FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart +54, fsArea[FS_AREA_BUTTON].yStart , 25,25, HL_Y,HL_CRCB);
                    #endif
                #endif

				#ifdef INDIGO_STYLE_FSGUI
					DrawFileIcon(fsArea[FS_AREA_OTHER_BUTTON].xStart+BTN_XOFFSET_FROM_OUTLINE, fsArea[FS_AREA_OTHER_BUTTON].yStart+BTN_YOFFSET_FROM_OUTLINE, CNT_TAB_OTHERBUTTON - 2);
				#else					
                    DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 60, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_OTHERBUTTON - 2);
#endif
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
            FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart +108, fsArea[FS_AREA_BUTTON].yStart , 25,25, HL_Y,HL_CRCB);
            DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 114, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MIDIBUTTON - 2);
#else //SUPPORT_NESGAME
            FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart +81, fsArea[FS_AREA_BUTTON].yStart , 25,25, HL_Y,HL_CRCB);
            DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 87, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MIDIBUTTON - 2);
#endif //SUPPORT_NESGAME
#else //SUPPORT_FILE_SYSTEM_MODE
#ifdef SUPPORT_NESGAME
            FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart +81, fsArea[FS_AREA_BUTTON].yStart , 25,25, HL_Y,HL_CRCB);
            DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 87, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MIDIBUTTON - 2);
#else //SUPPORT_NESGAME
            FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart +54, fsArea[FS_AREA_BUTTON].yStart , 25,25, HL_Y,HL_CRCB);
            DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 60, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MIDIBUTTON - 2);
#endif //SUPPORT_NESGAME
#endif //SUPPORT_FILE_SYSTEM_MODE
            }
            break;
#endif
#ifdef SUPPORT_PLAYLIST	//wanghaoying 2005-9-28 19:23
        case CNT_AREA_PLAYLISTBUTTON:
            old_ControlArea = CNT_AREA_PLAYLISTBUTTON;
            FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart +81, fsArea[FS_AREA_BUTTON].yStart , 25,25, HL_Y,HL_CRCB);
            DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 87, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_PLAYLISTBUTTON - 2);

            break;
#endif
#ifdef SUPPORT_MULTI_PARTITION
        case CNT_AREA_MULTI_PART:
                if(pFsJpeg->gifsState == FS_STATE_HDD)
                {
                    HL_show = pFsJpeg->part_will;//liweihua mod 2004-11-30
                    old_ControlArea = CNT_AREA_MULTI_PART;
                    FSGUI_FillFrameBuf((fsArea[FS_AREA_DIRITEM].xStart - 2), (FS_DIRLIST_YSTART  + HL_show * FS_FILELIST_YSTEP), 118, 14, 0x9a, 0xbb2f);
                    if((HL_show == max_part)&&PMP_CF_Card_IsPlugIn())//liweihua mod 2004-11-30
                        ShowHDDItem(fsArea[FS_AREA_DIRITEM].xStart,HL_show, "CF CARD",0);
                    else
                        ShowHDDItem(fsArea[FS_AREA_DIRITEM].xStart,HL_show, "LOCAL DISK",0);
                }
                #ifdef PMP_UI//liweihua 2004-12-30 9:56
                else
                {
                    #ifdef READ_FAT_LONGNAME  //linrc 2005-3-17 10:59
                    dFlag = 0;
                    #endif
                    HL_show = pFsJpeg->file_current_in_page;
                    FSGUI_FillFrameBuf((fsArea[FS_AREA_DIRITEM].xStart - 2), (FS_DIRLIST_YSTART  + HL_show * FS_FILELIST_YSTEP), 98, 14, 0x9a,0xbb2f);//0xa1, 0xb266);
                    ShowItemHL(HL_show);
                }
                #endif
            break;
    #ifdef FAT_FILE_MODE
        case CNT_AREA_DISK:
                {
                    addr1 = pFsJpeg;
                    addr2 = _fs9660_buf;
                    pFsJpeg = &(share_data.JPEG);
                    _fs9660_buf = SDRAM_BASE + HD_FS_STRUCTURE_YA * 1024;
                    if(pFsJpeg->gifsState == FS_STATE_HDD)
                        HL_show = pFsJpeg->part_will;//liweihua mod 2004-11-30
                    else
                        HL_show = pFsJpeg->file_current_in_page;
                    old_ControlArea = CNT_AREA_DISK;
                    FSGUI_FillFrameBuf((fsArea[FS_AREA_DIRITEM].xStart - 2), (FS_DIRLIST_YSTART  + HL_show * FS_FILELIST_YSTEP), 78, 14, 0xa1, 0xb266);
                    if(pFsJpeg->gifsState == FS_STATE_HDD)
                        ShowHDDItem(fsArea[FS_AREA_DIRITEM].xStart,HL_show, "DISK",0);
                    else
                        ShowItem(HL_show);
                    pFsJpeg = addr1;
                    _fs9660_buf = addr2;
                }
             break;
        case CNT_AREA_CARD:
                {
                    BYTE width;//liweihua 2004-11-30
                    addr1 = pFsJpeg;
                    addr2 = _fs9660_buf;
                    pFsJpeg = pFsJpegbuf;
                    _fs9660_buf = iso9660buf;
                    if(pFsJpeg->gifsState == FS_STATE_HDD)
                    {
                    HL_show = pFsJpeg->part_current;
                        width = 94;
                    }
                    else
                    {
                        HL_show = pFsJpeg->file_current_in_page;
                        width = 78;
                    }
                    old_ControlArea = CNT_AREA_CARD;
                    FSGUI_FillFrameBuf((fsArea[FS_AREA_FILEITEM].xStart - 2), (FS_DIRLIST_YSTART  + HL_show * FS_FILELIST_YSTEP), width, 14, 0xa1, 0xb266);
                    if(pFsJpeg->gifsState == FS_STATE_HDD)
                        ShowCardItem(HL_show,"CF CARD",0);
                    else
                        ShowItem(HL_show);
                    pFsJpeg = addr1;
                    _fs9660_buf = addr2; 
                }
            break;
        case CNT_AREA_WARNING:
                {
                    HL_show = pFsJpeg->part_current;
                    old_ControlArea = CNT_AREA_MULTI_PART;

                    FSGUI_FillFrameBuf((fsArea[FS_AREA_DIRITEM].xStart - 2), (FS_DIRLIST_YSTART  + HL_show * FS_FILELIST_YSTEP), 118, 14, 0xa1, 0xb266);
                }
             break;
    
    #endif//#ifdef FAT_FILE_MODE
#endif//#ifdef SUPPORT_MULTI_PARTITION
#ifdef FILE_MODE_WRITE                          //sunzhh 2005-01-06
        case CNT_AREA_SRCE:
                {
                    int j;
                    addr1 = pFsJpeg;
                    addr2 = _fs9660_buf;
                    pFsJpeg = &(share_data.JPEG);                    
                    _fs9660_buf = SDRAM_BASE + FS9660YA * 1024;
                    if(pFsJpeg->gifsState == FS_STATE_MEDIA)
                    {
                        HL_show = pFsJpeg->media_will;
                        j = 1;
                    }
                    else
                    {
                        HL_show = pFsJpeg->file_current_in_page;
                        j = 0;
                    }
                    FSGUI_FillFrameBuf((fsArea[FS_AREA_DIRITEM].xStart - 2), (FS_DIRLIST_YSTART  + (HL_show-j) * FS_FILELIST_YSTEP), 94, 14, HL_Y,HL_CRCB);                        
                    if(pFsJpeg->gifsState == FS_STATE_MEDIA)
                        FSGUI_ShowString( FS_DIRLIST_XSTART,(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * (HL_show-1) ), mediaStr[HL_show], FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);        
                    else
                        ShowFileItem(FS_DIRLIST_XSTART, HL_show);
                    old_ControlArea = CNT_AREA_SRCE;                                                
                    pFsJpeg = addr1;
                    _fs9660_buf = addr2;                     
                    }
             break;
        case CNT_AREA_DEST:
                {
                    addr1 = pFsJpeg;
                    addr2 = _fs9660_buf;
                    pFsJpeg = pFsJpeg_des_buf;
                    _fs9660_buf = iso9660buf_des;
                    if((!srceType_flag)&&(pFsJpeg->gifsState == FS_STATE_MEDIA))
                        j = 1;
                    else if((srceType_flag == 1)&&(pFsJpeg->gifsState == FS_STATE_MEDIA))
                        j = 2;                       
                    else
                        j = 0;          
                    if(pFsJpeg->gifsState == FS_STATE_MEDIA)
                        HL_show = pFsJpeg->media_will;
                    else
                        HL_show = pFsJpeg->file_current_in_page;                        
                        old_ControlArea = CNT_AREA_DEST;
                        FSGUI_FillFrameBuf((fsArea[FS_AREA_FILEITEM].xStart + 2), (FS_DIRLIST_YSTART  + (HL_show-j) * FS_FILELIST_YSTEP), 94, 14, HL_Y,HL_CRCB);

                    if(pFsJpeg->gifsState == FS_STATE_MEDIA)
                    {
                        FSGUI_ShowString( fsArea[FS_AREA_FILEITEM].xStart + 4,(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * (HL_show-j) ), mediaStr[HL_show], FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);        
//                        FSShowFatIcon(fsArea[FS_AREA_FILEICON].xStart,HL_show-j); 
                    }
                    else
                        ShowFileItem(fsArea[FS_AREA_FILEITEM].xStart + 4, HL_show);                
                    pFsJpeg = addr1;
                    _fs9660_buf = addr2;                     
                }
             break;
        case  CNT_AREA_COPYBUTTON:
                {
                    old_ControlArea = CNT_AREA_COPYBUTTON;
                    FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart, fsArea[FS_AREA_BUTTON].yStart, 25,25,HL_Y,HL_CRCB);
                    DrawFileIconX(fsArea[FS_AREA_BUTTON].xStart+6, fsArea[FS_AREA_BUTTON].yStart + 6, 2,0);                                                             
                }
                break;
        case  CNT_AREA_DELETEBUTTON:
                {
                    old_ControlArea = CNT_AREA_DELETEBUTTON;
                    FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart+30, fsArea[FS_AREA_BUTTON].yStart, 25,25,HL_Y,HL_CRCB);
                    DrawFileIconX(fsArea[FS_AREA_BUTTON].xStart + 30 +6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2,0);                                                              
                }
                break;
        case  CNT_AREA_NEWBUTTON:
                {
                    old_ControlArea = CNT_AREA_NEWBUTTON;
                    FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart+60, fsArea[FS_AREA_BUTTON].yStart, 25,25,HL_Y,HL_CRCB);
                    DrawFileIconX(fsArea[FS_AREA_BUTTON].xStart + 60 +6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2,0);                                                              
                }
                break;
        case  CNT_AREA_RENAMEBUTTON:
                {
                    old_ControlArea = CNT_AREA_RENAMEBUTTON;
                    FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart+90, fsArea[FS_AREA_BUTTON].yStart, 25,25,HL_Y,HL_CRCB);
                    DrawFileIconX(fsArea[FS_AREA_BUTTON].xStart + 90 +6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2,0);                                                              
                }
                break;      
        case  CNT_AREA_FORMATBUTTON:
                {
                    old_ControlArea = CNT_AREA_FORMATBUTTON;
                    FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart+120, fsArea[FS_AREA_BUTTON].yStart, 25,25,HL_Y,HL_CRCB);
                    DrawFileIconX(fsArea[FS_AREA_BUTTON].xStart + 120 +6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2,0);                                                             
                }
                break;                                                                                   
        case  CNT_AREA_CAPACITYBUTTON:
                {
                    old_ControlArea = CNT_AREA_CAPACITYBUTTON;
                    FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart+150, fsArea[FS_AREA_BUTTON].yStart, 25,25,HL_Y,HL_CRCB);
                    DrawFileIconX(fsArea[FS_AREA_BUTTON].xStart + 150 +6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2,0);                                                             
                }
                break;
#endif//#ifdef FILE_MODE_WRITE 
    default: break;
    }
    #ifdef PHILIPS_FSGUI//chenzhao20050613
    file_focus_y = FS_FONTCOLOR_FILE_Y;
    file_focus_CrCb = FS_FONTCOLOR_FILE_CrCb;
    #endif

}
#ifdef MINUS_VR_AUTH_PLAYBACK
#ifdef SUPPORT_VR_MENU

#include "kernel.h"
#define VR_PER_PAGE		3

const BTNAREA VR_PG_Rect =
				{ 24,     65,
				  280,     170};

const BTNAREA VR_Item_Rect =
	// dir item area
	{	94,		FS_DIRLIST_YSTART, 
		260,		VR_PER_PAGE * FS_FILELIST_YSTEP	};



#define VR_MODE_ORI			0x00
#define VR_MODE_PLAYLIST	0x01


void VRClearRectArea(BTNAREA Rect, UINT16 RectColorStep, UINT16 RegionColor_C, int iItem);
void VRShowHL(void);

UINT8 VR_Mode;

void VR_Menu_Init()
{
	pFsJpeg->dir_page_now=0;
	pFsJpeg->dir_current=0;
	HL_Width=200;
	pFsJpeg->ControlArea=CNT_AREA_DIR;
	VR_Mode=VR_MODE_ORI;
	old_ControlArea=0;
	return;
}

void VR_Show_Item(UINT16 i,UINT16 j)
{
	BYTE ShowName[22];
	if(VR_Mode==VR_MODE_ORI)
	{
			psprintf(ShowName,"TITLE%2d ",i+1);
			strcat(ShowName,pDSV->ORI_PG_Names[i]);	
	}
	else if(VR_Mode==VR_MODE_PLAYLIST)
	{
			psprintf(ShowName,"PLAYLIST:%2d",i+1);
			strcat(ShowName,pDSV->PL_Names[i]);	
	}
	FSGUI_ShowString( fsArea[FS_AREA_DIRITEM].xStart+50,
			(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * (j*VR_PER_PAGE+1)),
			ShowName, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
}

void VR_PG_List()
{
	UINT16 i;
	UINT16 j;
	UINT16 Limit;
	/*BTNAREA VR_Rect =
				{ 24,     65,
				  260,     170};
*/

	if(VR_Mode==VR_MODE_ORI)
		Limit=pDSV->ORI_PG_Ns;
	else
		Limit=pDSV->PL_Ns;
	
	//if (!refresh_dir_page)
	//	return;

	VRClearRectArea(VR_Item_Rect, DIR_STEP, DIR_AREA_BKGROUND_CRCB, -1);//zhaoyanhua add
	// DrawRectCorner(VR_PG_Rect, CORNER_RAD, 1,DIR_STEP, DIR_AREA_BKGROUND_CRCB);
	 VRShowHL();
	
	//sJpeg->Dir_Count=Limit;
	i = pFsJpeg->dir_page_now * VR_PER_PAGE;
	j = 0;

	while (j < VR_PER_PAGE && i < Limit)
	{	
		VR_Show_Item(i, j);	
		j++;
		i++;
	}
}

//
// Draw VR main menu, fill framebuf by some difference color
//
void VR_FSGUI_Menu()
{

    // background
    //FSGUI_FillFrameBuf(0,0,352,288,BK_GROUNDY,BK_GROUNDCRCB);
    FSGUI_FillFrameBuf(0,0,352,288,BK_GROUNDY,BK_CRCB);
#ifdef MONO_FSGUI //FS GUI, axel 2003-12-29 23:26
  //  DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1,1, DIR_AREA_BKGROUND_CRCB);
  //  DrawRectCorner(Rect[FILE_RECT], CORNER_RAD,  1, 1, FILE_AREA_BKGROUND_CRCB);
#else
    DrawRectCorner(VR_PG_Rect, CORNER_RAD, 1,DIR_STEP, 0x36, 0xc1, DIR_AREA_BKGROUND_CRCB);
#endif
}

#define BUTTON_OFFSET	90

/*
void VR_Draw_Button(UINT8 PlaylistCount,UINT16 Mode)
{

    {
        DrawRect(fsArea[FS_AREA_BUTTON].xStart+BUTTON_OFFSET, fsArea[FS_AREA_BUTTON].yStart,
            25, 25,
            Mode == 0 ? 1 : 0, BUTTON_Y, BUTTON_CRCB);
    }
    DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart +BUTTON_OFFSET+ 6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2);

	//draw JPEG icon
	if (PlaylistCount)
	{
		DrawRect(fsArea[FS_AREA_BUTTON].xStart +BUTTON_OFFSET+ 27, fsArea[FS_AREA_BUTTON].yStart, 25, 25,
			Mode == 1 ? 1 : 0, BUTTON_Y, BUTTON_CRCB);
	}
	else
	{
		FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart+BUTTON_OFFSET + 27, fsArea[FS_AREA_BUTTON].yStart,
			25, 25,
			BUTTON_Y, BUTTON_CRCB);
	}
	DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart +BUTTON_OFFSET+ 33, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_JPEGBUTTON - 2);
}
*/
#define BUTTON_START_X 120
#define BUTTON_START_Y 245

void VR_Draw_Button(UINT8 PlaylistCount)
{
        DrawRect(BUTTON_START_X, BUTTON_START_Y,
            100, 25,
            VR_Mode == 0 ? 1 : 0, BUTTON_Y, BUTTON_CRCB);
  //  DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart ++ 6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2);

		FSGUI_ShowString(BUTTON_START_X+15,
			BUTTON_START_Y+5,
			"ORIGINAL", YELLOW_Y, YELLOW_CRCB);


	//draw JPEG icon
	if (PlaylistCount)
	{
		DrawRect(BUTTON_START_X +100+2, BUTTON_START_Y, 100, 25,
			VR_Mode == 1 ? 1 : 0, BUTTON_Y, BUTTON_CRCB);
	}
	else
	{
		FSGUI_FillFrameBuf(BUTTON_START_X+100+2, BUTTON_START_Y,
			100, 25,
			BUTTON_Y, BUTTON_CRCB);
	}
	//DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart +BUTTON_OFFSET+ 33, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_JPEGBUTTON - 2);
		FSGUI_ShowString(BUTTON_START_X+15+100+2,
			BUTTON_START_Y+5,
			"PLAYLIST", YELLOW_Y, YELLOW_CRCB);
}

void VR_Menu_Set_Scroll()
{
		pFsJpeg->File_Page_Count = (pFsJpeg->file_specify_in_dir + VR_PER_PAGE - 1) / VR_PER_PAGE;

	if (pFsJpeg->File_Page_Count != 1)
		pFsJpeg->scroll_len = fsArea[FS_AREA_MOVEBAR].ySize / pFsJpeg->File_Page_Count;
	else if (pFsJpeg->file_specify_in_dir != 1)
		pFsJpeg->scroll_len = fsArea[FS_AREA_MOVEBAR].ySize / 2;
	else
		pFsJpeg->scroll_len = fsArea[FS_AREA_MOVEBAR].ySize;

	if (pFsJpeg->scroll_len < 4)
		pFsJpeg->scroll_len = 4;

	if ((fsArea[FS_AREA_MOVEBAR].ySize - pFsJpeg->scroll_len) >= (pFsJpeg->file_specify_in_dir - 1))
	{
		pFsJpeg->scroll_step = (fsArea[FS_AREA_MOVEBAR].ySize - pFsJpeg->scroll_len) / (pFsJpeg->file_specify_in_dir - 1);
		pFsJpeg->scroll_len = fsArea[FS_AREA_MOVEBAR].ySize - pFsJpeg->scroll_step * (pFsJpeg->file_specify_in_dir - 1);
	}
	else
	{
		pFsJpeg->scroll_step = 10 * (fsArea[FS_AREA_MOVEBAR].ySize - pFsJpeg->scroll_len) / (pFsJpeg->file_specify_in_dir - 1);
		pFsJpeg->scroll_len = fsArea[FS_AREA_MOVEBAR].ySize - pFsJpeg->scroll_step * (pFsJpeg->file_specify_in_dir - 1) / 10;
	}

	pFsJpeg->file_page_will = 0;
	pFsJpeg->file_will = 0;

}




void VRShowHL(void)
{

		// clear last HL
	switch (old_ControlArea)
	{

		case  CNT_AREA_DIR:
				{
					VRClearRectArea(VR_Item_Rect, DIR_STEP, DIR_AREA_BKGROUND_CRCB, HL_show%VR_PER_PAGE);
					VR_Show_Item(HL_show,HL_show%VR_PER_PAGE);
				}
				break;

		case  CNT_AREA_MP3BUTTON:
		case  CNT_AREA_JPEGBUTTON:
#if 0			
				{
					DrawRect(fsArea[FS_AREA_BUTTON].xStart+BUTTON_OFFSET, fsArea[FS_AREA_BUTTON].yStart,
					25, 25,
						VR_Mode == VR_MODE_ORI? 1 : 0, BUTTON_Y, BUTTON_CRCB);

					DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 6+BUTTON_OFFSET, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2);
				}
		
		
				{
					//FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 3+ 27-1, fsArea[FS_AREA_BUTTON].yStart + 3, 24,24, BUTTON_Y,BUTTON_CRCB);
					DrawRect(fsArea[FS_AREA_BUTTON].xStart+27+BUTTON_OFFSET, fsArea[FS_AREA_BUTTON].yStart,
					25, 25,
						VR_Mode == VR_MODE_PLAYLIST? 1 : 0, BUTTON_Y, BUTTON_CRCB);
					DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 33+BUTTON_OFFSET, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_JPEGBUTTON - 2);
				}
#else
				VR_Draw_Button(pDSV->PL_Ns);
#endif
				break;
		default: break;
   }

	// draw current HL
	switch (pFsJpeg->ControlArea)
	{

		case  CNT_AREA_DIR:
				{
					HL_show = pFsJpeg->dir_current;
					old_ControlArea = CNT_AREA_DIR;

					FSGUI_FillFrameBuf(VR_Item_Rect.xStart , FS_DIRLIST_YSTART  + (HL_show%VR_PER_PAGE)*VR_PER_PAGE* FS_FILELIST_YSTEP, HL_Width, HL_Heighth*3+10, HL_Y, HL_CRCB);
					VR_Show_Item(HL_show,HL_show%VR_PER_PAGE);
				}
				break;

		case  CNT_AREA_MP3BUTTON:
				{
					old_ControlArea = CNT_AREA_MP3BUTTON;
#if 0					
					FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart+BUTTON_OFFSET , fsArea[FS_AREA_BUTTON].yStart , 25,25,HL_Y,HL_CRCB);
					DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart+BUTTON_OFFSET+ 6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2);
#else
					FSGUI_FillFrameBuf(BUTTON_START_X , BUTTON_START_Y, 100,25,HL_Y,HL_CRCB);
					FSGUI_ShowString(BUTTON_START_X+15,
					BUTTON_START_Y+5,
					"ORIGINAL", YELLOW_Y, YELLOW_CRCB);
#endif
				}
				break;
		case  CNT_AREA_JPEGBUTTON:
				{
					old_ControlArea = CNT_AREA_JPEGBUTTON;
#if 0
					FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart+27+BUTTON_OFFSET, fsArea[FS_AREA_BUTTON].yStart , 25,25, HL_Y,HL_CRCB);
					DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart+BUTTON_OFFSET + 33, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_JPEGBUTTON - 2);
#else
					FSGUI_FillFrameBuf(BUTTON_START_X +100+2 , BUTTON_START_Y, 100,25,HL_Y,HL_CRCB);

					FSGUI_ShowString(BUTTON_START_X+15+100+2,
					BUTTON_START_Y+5,
					"PLAYLIST", YELLOW_Y, YELLOW_CRCB);
#endif
		}
				break;
	default: break;
	}
}


void VR_Draw_Menu_Bkg()
{
	disable_video();           
	config_memory(MEMORY_GRAPH_SMALL);
	setup_tv_format(tv_format);						
	delay_srv_10ms(2);         
								
	VR_FSGUI_Menu();   

	delay_srv_10ms(2);
	enable_video();			
	DrawScroll();
	
	pFsJpeg->file_specify_in_dir=pDSV->ORI_PG_Ns;
	VR_Menu_Set_Scroll();
	
	MoveScroll(0);
	VR_PG_List();
	VR_Draw_Button(pDSV->PL_Ns);
}

void FSGUI_FillFrameBuf2(int x, int y, int xSize, int ySize, UINT16 color_Y, UINT16 color_CrCb)
{
    int i, j;
    
    for (j = y; j < y + ySize; j++)
    {
        for (i = x; i < x + xSize; i++)
        {
        	UINT16 NewY;
			if((color_Y-(i-150)/6-j/6)>10)
				NewY=(color_Y-(i-150)/6-j/6); 
			else
				NewY=10;
            *Y_XY(i, j) = NewY & 0xff;
            *C_XY(i, j) = color_CrCb;
        }
		
    }
}

void FSGUI_ShowBigString(int x, int y, const char *s, BYTE iY, UINT16 iCbCr)
{
	int	i = 0;
	BYTE* p = (BYTE *)s;
	int length = 0;
	//sometime may exceed 25 chinese
	//zhaoyanhua modify. 2003-8-26 14:36
	#ifdef MP3_TXT_DISPLAY
	unsigned char ss[100];
	#else
	unsigned char ss[50];
	#endif
	unsigned char* ss_ptr = ss;

	strcpy(ss_ptr, p);
	
	while(p[i])
	{
		length++;
		i++;
	}
	i = 0;
	
	while (*p)
	{
		BYTE    c;
		BYTE    c1;
		int     iRes = 0;
        
		//  which character
		c = *p;
		c1 = *(p + 1);

#ifdef USE_GB2312_FONT
		if (((c >= 0xA1) && (c <= 0xF8)) && ((c1 >= 0xA1) && (c1 < 0xFF)))             
		 {
			// GB code
			iRes = 3;
		 }
		 else  
#endif
#ifdef USE_BIG5_FONT
		if(((c >= 0xA1) && (c <= 0xF9)) && ((c1 >= 0x40 && c1 <= 0x7E) || (c1 >= 0xA1 && c1 <= 0xFE))) // yhwang for big5 20021001
		{
			// Big5 code
			iRes = 2;
		}
		else 
#endif
		if ((c >= 32) && (c <= 126)) // ASCII code
			iRes = 1;
		else
		{
			iRes = 0;
			c = '_';
		}
		
		if ((iRes == 0) || (iRes == 1))
		{
#ifdef SUPPORT_CHINESE_FONT // Clead
			if ((c == '!') || (c == '"') || (c == '#') || (c == '$') ||
				(c == '&') || (c == '\'') || (c == '(') || (c == ')') ||
				(c == ',') || (c == ';') || (c == '=') || (c == '^'))
#ifdef USE_GB2312_FONT
			{
				c1 = 0x03 + 0xa0;
				c = c + 0x80;
				FSGUI_GBShowChar(0, (x + i), y, c1, c, iY, iCbCr);
			}
			else
#elif defined(USE_BIG5_FONT)
			{
				if(c < 114)
				{
					c1 = 0xa2;
					c = c + 0x8e;
				}
				else
				{
					c1 = 0xa3;
					c = c - 113 + 0x40;
				}
				FSGUI_Big5ShowChar(0, (x + i), y, c1, c, iY, iCbCr);
			}
			else
#endif
				FSGUI_ShowChar(0, (x + i), y, c, iY, iCbCr);
#else
			FSGUI_ShowBigChar(0, (x + i), y, c, iY, iCbCr);
#endif
			i += 18;
			p++;
		}

#ifdef USE_BIG5_FONT
		else if(iRes == 2)  //BIG5 code
		{
			FSGUI_Big5ShowChar(0, (x + i), y, c, c1, iY, iCbCr);
			i += 14;
			p += 2;
		}
#endif
#ifdef USE_GB2312_FONT
		else if (iRes == 3) //GB code
		{
			FSGUI_GBShowChar(0, (x+i), y, c, c1, iY, iCbCr);
			i += 14;
			p += 2;
		} 
#endif
		else
		{
			c = '-';
			FSGUI_ShowChar(0, (x+i), y, c, iY, iCbCr); 
			i += 9;
			p++;
		}
		//if (i > 260)
		//	break;  // yhwang, for limiting the length of FSGUI_ShowString
	}
}


void VR_Draw_Menu_Bkg2()
{
	//disable_video();           
	config_memory(MEMORY_GRAPH_NTSC);
	setup_tv_format(tv_format);						
	delay_srv_10ms(2);         
								
	//VR_FSGUI_Menu();   
	FSGUI_FillFrameBuf2(0,0,720,480,0xB0,BK_CRCB);
	FSGUI_FillFrameBuf(100,80,620,6,0x90,(RGB2Cr(183,179,255)<<8)|(RGB2Cb(183,179,255)));

		FSGUI_ShowBigString( 100,
			64,
			"RECORDER SETUP", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);


		FSGUI_ShowBigString( 140,
			150,
			"RECORDING MODE", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);

		

		FSGUI_ShowBigString( 100,
			210,
			"CHAPTER INTERVAL", FS_FONTCOLOR_FILE_Y-80, FS_FONTCOLOR_FILE_CrCb);


		FSGUI_ShowBigString( 480,
			180,
			"HQ 1HOUR", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);

		

		FSGUI_ShowBigString( 440,
			230,
			"SP 2HOURS", YELLOW_Y, YELLOW_CRCB);

		FSGUI_ShowBigString( 400,
			280,
			"LP 3HOURS", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);

		

		FSGUI_ShowBigString( 360,
			330,
			"EP 4HOURS", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);

		FSGUI_ShowBigString( 300,
			380,
			"MORE OPTIONS", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);




		FSGUI_FillFrameBuf(150,175,290,4,RED_Y+0x20,RED_CRCB);
	
	
/*	 DrawRectCorner(VR_PG_Rect, CORNER_RAD, 1,DIR_STEP, DIR_AREA_BKGROUND_CRCB);

	DrawRect(BUTTON_START_X, BUTTON_START_Y,
            100, 25,
            0 , BUTTON_Y, BUTTON_CRCB);
    
     DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2);
*/
	delay_srv_10ms(2);
			
	//DrawScroll();
	 set_disbuf_now(0);
	enable_video();	

	// show_virtual_keyboard();
	//pFsJpeg->file_specify_in_dir=pDSV->ORI_PG_Ns;
//	VR_Menu_Set_Scroll();
	
//	MoveScroll(0);
//	VR_PG_List();
//	VR_Draw_Button(pDSV->PL_Ns);
}

UINT32  VR_FSGUI_CmdDown()
{
	UINT32 iRes=0;

	UINT16 Limit;



	if(VR_Mode==VR_MODE_ORI)
		Limit=pDSV->ORI_PG_Ns;
	else
		Limit=pDSV->PL_Ns;


	if (pFsJpeg->ControlArea == CNT_AREA_DIR) {

		if (pFsJpeg->dir_current < (Limit - 1))
		{
			pFsJpeg->dir_current++;
			VRShowHL();
			
			if(pFsJpeg->dir_current&&!(pFsJpeg->dir_current%VR_PER_PAGE))
			{
				pFsJpeg->dir_page_now++;
				VR_PG_List();
			}
			
			
			
			

			MoveScroll(pFsJpeg->dir_current);
			
			sys_cmd = CMD_SELECT|CMD_FUNC_GAME_DN;
			iRes = 0x20000|sys_cmd;
			sys_cmd = 0;	// avoid receive another command,panxing,2002-4-13
		}
	} else {
		iRes = 0;
		sys_cmd = 0;

	}
	
	return iRes;
}

UINT32  VR_FSGUI_CmdUp()
{
	UINT32 iRes=0;

	if (pFsJpeg->ControlArea == CNT_AREA_DIR) {

		if (pFsJpeg->dir_current > 0)
		{
			pFsJpeg->dir_current--;
			VRShowHL();
			
			if(pFsJpeg->dir_current&&(pFsJpeg->dir_current%VR_PER_PAGE)==2)
			{
				pFsJpeg->dir_page_now--;
				VR_PG_List();
			}
			
			MoveScroll(pFsJpeg->dir_current);
			
			sys_cmd = CMD_SELECT|CMD_FUNC_GAME_DN;
			iRes = 0x20000|sys_cmd;
			sys_cmd = 0;	// avoid receive another command,panxing,2002-4-13
		}
	} else {
		iRes = 0;
		sys_cmd = 0;

	}
	
	return iRes;
}

UINT32 VR_FSGUI_CmdRightLeft()
{
	UINT32 iRes;
	
	if (pFsJpeg->ControlArea == CNT_AREA_DIR)
	{
		if(!pDSV->PL_Ns)
		{
			iRes = 0;
			sys_cmd = 0;
			return iRes;
		}
		else if(VR_Mode==VR_MODE_ORI)
		{
			pFsJpeg->ControlArea = CNT_AREA_JPEGBUTTON;
		}
		else if(VR_Mode==VR_MODE_PLAYLIST)
		{
			pFsJpeg->ControlArea = CNT_AREA_MP3BUTTON;
		}
			
	}
	else
	{
		pFsJpeg->ControlArea = CNT_AREA_DIR;
	}

	VRShowHL();
	
	iRes = 0x20000 | sys_cmd;
    	sys_cmd = 0;
	return iRes;
}

void VRClearRectArea(BTNAREA Rect, UINT16 RectColorStep, UINT16 RegionColor_C, int iItem)
{
	//int i =0;
	int  x0=0,y0=0;
	//UINT8 RegionColor_Y[60];
	//int Region[60];
	
	UINT16  RegionStep = 0;
	UINT8   RegionColorStep_Y = 0;
	UINT8 StepCount =0;
	int  xAreaStart=0,yAreaStart = 0, xAreaSize=0,yAreaSize=0;

	    RegionStep = /*Rect.xSize*/VR_PG_Rect .xSize / RectColorStep;
	    RegionColorStep_Y = (0xc1-0x36) / RectColorStep;



	if (iItem >= 0) //for clear last FILE or DIR item when show Current playing.
	{
		xAreaStart = Rect .xStart;
		yAreaStart = FS_DIRLIST_YSTART  + iItem*VR_PER_PAGE* FS_FILELIST_YSTEP;
		xAreaSize =  HL_Width;
		yAreaSize = HL_Heighth*3+10;
	}
	else
	{
		xAreaStart = Rect .xStart;
		yAreaStart =  FS_DIRLIST_YSTART;
		xAreaSize = HL_Width;;
		yAreaSize = 3*(HL_Heighth*3+10);

	}


 	StepCount = 0;

 	while(xAreaStart >= (VR_PG_Rect .xStart + RegionStep * StepCount))
 	{
 		StepCount++;
 	}

	//StepCount = StepCount-1;



 	for (x0 = xAreaStart; x0 < (xAreaStart+ xAreaSize); x0++)
	{
		if((StepCount +1) < RectColorStep)
		{
			if ((x0 >= (VR_PG_Rect.xStart + RegionStep * StepCount)) && (x0 < (Rect.xStart + RegionStep * (StepCount+1))))
			//if ((x0 >= Region[StepCount]) && (x0 < Region[StepCount + 1]))
			{
				StepCount++;

			}
 		}
 		else
 			StepCount = RectColorStep -1;
		
		for (y0 = yAreaStart; y0 < (yAreaStart+yAreaSize); y0++)
		{
			*Y_XY((x0),(y0)) = 0x36+RegionColorStep_Y*StepCount;//RegionColor_Y[StepCount];
			*C_XY((x0),(y0)) = RegionColor_C;
		}
	}

}

extern Play_PL_N(UINT8 PL_PGCN);
	
UINT32 VR_FSGUI_CmdEnter()
{
    UINT32  iRes=0;

	if(pFsJpeg->ControlArea==CNT_AREA_DIR)
	{
		if(VR_Mode==VR_MODE_ORI)
		{
			pDSV->CurrPGC_LSN= pDSV->ORG_PGCI_SA;
			pDSV->CurrPGN=pFsJpeg->dir_current+1;
			
		}
		else
		{
			Play_PL_N(pFsJpeg->dir_current+1);
		}

		pDSV->CurrState=NAV_NEW_PGC;
		
		iRes = 0x20000 | sys_cmd;
	    	sys_cmd = 0;  
 		return iRes;
	}

	else if(pFsJpeg->ControlArea == CNT_AREA_MP3BUTTON)
	{
		VR_Mode=VR_MODE_ORI;
		pFsJpeg->file_specify_in_dir=pDSV->ORI_PG_Ns;
	}
	else
	{
		VR_Mode=VR_MODE_PLAYLIST;
		pFsJpeg->file_specify_in_dir=pDSV->PL_Ns;
	}
				
	VR_Menu_Set_Scroll();
	pFsJpeg->ControlArea = CNT_AREA_DIR;
	pFsJpeg->dir_current=0;
	pFsJpeg->dir_page_now=0;

	MoveScroll(0);
	VR_PG_List();

	iRes = 0x20000 | sys_cmd;
    	sys_cmd = 0;
  
    return iRes;
}

#endif//#ifdef SUPPORT_VR_MENU
#endif//#ifdef MINUS_VR_AUTH_PLAYBACK


