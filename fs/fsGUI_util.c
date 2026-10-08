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
#include "iop.h"
#include "memcfg.h"
#include "ircmd.h"
#include "dsp3_if.h"

#include "user_init.h"
#include "nesinit.h"
#include "fs96602.h"
#include "fsNAV.h"
#include "fsGUI.h"
#include "user_if.h"

extern UINT16  Hl_x;
extern UINT16  Hl_y;
extern UINT16  Hl_len;
extern UINT16  Hl_high;
extern UINT16  Hl_x_btn;
extern UINT16  Hl_y_btn;
extern UINT16  Hl_len_btn;
extern UINT16  old_file_page;	        // index of current page
extern UINT16  old_dir_page;
extern UINT16  refresh_file_page;
extern UINT16  refresh_dir_page;

#ifdef HANYANG_LR_CHANGE_PAGE  //Maoyong for hanyang 2004.07.01
extern void FSGUI_Dir2FileArea(void);
#endif

void FSGUI_Init()
{
	pFsJpeg->scroll_len			= 0;
	pFsJpeg->scroll_step		= 0;
// 2006-03-16, mimitsai add
#ifdef DIR_SCROLL_BAR
	pFsJpeg->dir1_scroll_len		= 0;
	pFsJpeg->dir1_scroll_step		= 0;
	pFsJpeg->Dir_Page_Count		= 0;
#endif
	
	pFsJpeg->Dir_Count			= 0;
	pFsJpeg->File_Count			= 0;            // number of file in current page
	
	pFsJpeg->File_Page_Count	= 0;            // number of file page in current directory
	
	pFsJpeg->dir_page_now		= 0;
	pFsJpeg->file_page_now		= 0;            // index of current page
	
	old_dir_page		= 0xffff;
	old_file_page		= 0xffff;
	
	Hl_x				= 0;
	Hl_y				= 0;
	Hl_len				= 0;
	Hl_high				= 0;
	
	Hl_x_btn			= 0;
	Hl_y_btn			= 0;
	Hl_len_btn			= 0;
	
	pFsJpeg->ControlArea	= CNT_AREA_FILE;
	
	refresh_file_page	= 1;
	refresh_dir_page	= 1;
}

//Maoyong 2004.07.01. here is a common function for IR key to change fs file page
//maybe used Left/Right or other pairs IR keys to do.
//Should define the way for scroll page with SUPPORT_CHANGE_FILE_PAGE at the same time
#ifdef SUPPORT_CHANGE_FILE_DIR_PAGE
/*============================================================================
Note: (1)file page up down in current directory range, just do up down highlight
      (2)dir page up down in the button's all directory 
=============================================================================*/
extern void FSGUI_FileAreaUpdownRefresh(void);
extern BYTE jpg_break_up_down;
extern void FSGUI_File2DirArea(void);
/*****************************************************************************
Function:       int IsValidAreaChangePage(int direction)
Description:    check if in FILE/DIR in file List state
Input:          none
Output:         1: valid GUI area to change page; 0: not
******************************************************************************/
int IsValidAreaChangePage(void)
{
    if( ( cd_type_loaded == CDROM) && 
        ( (pFsJpeg->gifsState == FS_STATE_LIST) || (pFsJpeg->gifsState == FS_STATE_MP3) ) &&
        (JPEG_THUMBNAIL_MODE != pFsJpeg->g_nJpegMode )&&
        ( (pFsJpeg->ControlArea == CNT_AREA_FILE) || (pFsJpeg->ControlArea == CNT_AREA_DIR) ) )
        return 1;
    else
        return 0;
}
/*****************************************************************************
Function: int IsValidRangeChangePage(int direction)
Description:  check if in a valid range to change page
Input:        direction: 1 = next page, 0 = prev page
Output:       1: valid range to change page; 0: not
*****************************************************************************/
int IsValidRangeChangePage(int direction)
{
    int btn_dirs = 0;   
    int dir_total_trk = 0;
    int i = 0, j = 0;

    if( ( (pFsJpeg->gifsState == FS_STATE_LIST) || (pFsJpeg->gifsState == FS_STATE_MP3) ) &&
        (JPEG_THUMBNAIL_MODE != pFsJpeg->g_nJpegMode ) ){
        if( pFsJpeg->ControlArea == CNT_AREA_FILE ) {  //for file page change
            dir_total_trk = pFsJpeg->file_specify_in_dir;         
            //check current track if overflow or underflow
            if( ( (direction == 1) && (pFsJpeg->fsnav_trk_will + PER_PAGE > dir_total_trk ) ) || // in last dir
             ( (direction == 0) && (pFsJpeg->fsnav_trk_will < PER_PAGE) ) )
                return 0;
            else
                return 1;
        }else if( pFsJpeg->ControlArea == CNT_AREA_DIR ) { //for dir page change
            btn_dirs = pFsJpeg->count_dir[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3]; 
            if(btn_dirs <= PER_PAGE)
                return 0;
            
            //check how much dirs left by direction    
            if(direction) {    
                for( i = pFsJpeg->fsnav_dir_will; i< pFsJpeg->fsnav_dir_cnt - 1; i++) {
                    if( iso9660_dir[i].type & (0x01 << pFsJpeg->gifsFuncBtn) )
                        j++;
                }
            } else {       
                for( i = 0; i< pFsJpeg->fsnav_dir_will; i++) {
                    if( iso9660_dir[i].type & (0x01 << pFsJpeg->gifsFuncBtn) )
                        j++;
                }
            }
            
            if(j >= PER_PAGE )
                return 1;
        }
    }
    return  0;
}

/*****************************************************************************
Function: void FSGUI_UpdownDirPage(int direction)
Input:    direction: 1 = next page, 0 = prev page
Output:   0: not do page change, 1: has do page change
*****************************************************************************/
void FSGUI_UpdownDirPage(int iUpdown)
{
    int diff, pre_find_dir, i ;
    if(iUpdown){
        diff =1;
        pre_find_dir = 0;
    } else {
        diff = -1;
        pre_find_dir = 1;
    }
    
    for( i = 0; i< PER_PAGE; i++){
        pFsJpeg->fsnav_dir_will += diff;
        FSGUI_PreFindDir(&(pFsJpeg->fsnav_dir_will), pre_find_dir); //panxing for yuxing,2002-4-11
        CalcDirNow(&(pFsJpeg->fsnav_dir_will));
        FSShowDirIcon();
        DirList();
    }
    FSGUI_File2DirArea();
}

/*****************************************************************************
Function: void FSGUI_UpdownFilePage(int direction)
Input:    direction: 1 = next page, 0 = prev page
Output:   0: not do page change, 1: has do page change
*****************************************************************************/
void FSGUI_UpdownFilePage(int iUpdown)
{
    int i;
    
    if(iUpdown)
    {
    	#ifdef ANGLE_PAGE_DOWN //zhongshan add for Tonic 
    	if(pFsJpeg->file_page_will == (pFsJpeg->File_Page_Count -1))
	 	{
	 		for(i = 0; i<pFsJpeg->File_Count; i++)
			{
            	if (pFsJpeg->file_will < (pFsJpeg->File_Count - 1)) 
	     		{
                	(pFsJpeg->file_will)++;
                	pFsJpeg->fsnav_trk_will = pFsJpeg->file_array[pFsJpeg->file_will] - pFsJpeg->first_mp3_entry;
            	}
	     		else  
	    		{
                	pFsJpeg->file_page_will = 0;
                    PrepareForChangeFilePage(pFsJpeg->file_page_will, 0, 0);
					break;
           		}
        	} //for loop i
	 	}
	 	else
	 	#endif
	 	{
        	for(i = 0; i<PER_PAGE; i++)
        	{
            	if (pFsJpeg->file_will < (pFsJpeg->File_Count - 1)) 
            	{
                	(pFsJpeg->file_will)++;
                	pFsJpeg->fsnav_trk_will = pFsJpeg->file_array[pFsJpeg->file_will] - pFsJpeg->first_mp3_entry;
            	} 
            	else  
            	{
                	if (pFsJpeg->file_page_will < (pFsJpeg->File_Page_Count - 1))
					{
                    	pFsJpeg->file_page_will++;
                    	PrepareForChangeFilePage(pFsJpeg->file_page_will, 0, 0);
                	}
           		}
        	} //for loop i
    	}
    } 
    else 
    { // if(iUpDown)
        for(i = 0; i<PER_PAGE; i++) 
        {    
            if (pFsJpeg->file_will > 0) 
            {
                (pFsJpeg->file_will)--;
                pFsJpeg->fsnav_trk_will = pFsJpeg->file_array[pFsJpeg->file_will] - pFsJpeg->first_mp3_entry;
            } 
            else 
            {
                if (pFsJpeg->file_page_will) 
                {
                    pFsJpeg->file_page_will--;
                    PrepareForChangeFilePage(pFsJpeg->file_page_will, 0, 1);
                }
            }
        }//for loop i
    }// if(iUpDown)            
    ShowFileIcon();
    FileList(); 
    FSGUI_FileAreaUpdownRefresh();
    FSGUI_Dir2FileArea();       //for un highlight the current playing file  
}
/************************************************************
Function: int FSGUI_ChangFileDirPage(int direction)
Input:    direction: 1 = next page, 0 = prev page
Output:   0: not do page change, 1: has do page change
*************************************************************/
int FSGUI_ChangFileDirPage(int direction)
{
    if( !IsValidRangeChangePage(direction) ){
            invalid_key();
            return 0;       //no need to do page up down
    }else if (pFsJpeg->ControlArea == CNT_AREA_FILE) {
        FSGUI_UpdownFilePage(direction);
        return 1;
    }else if(pFsJpeg->ControlArea == CNT_AREA_DIR ){
        FSGUI_UpdownDirPage(direction);
        return 1;
    }
    return 0;
}
#endif //#ifdef SUPPORT_CHANGE_FILE_DIR_PAGE
#ifdef MINUS_VR_AUTH_PLAYBACK
#ifdef SUPPORT_VR_MENU
void FSGUI_ShowBigChar(BYTE vid, int x, int y, BYTE c, BYTE iY, UINT16 iCbCr) //Jeff 20020823
{
	int     i, j, i4x, j2x;
	BYTE    *pFont;
	UINT32  my16Bits;
	
	
	pFont = get_font_entry(0,c);
	
	//draw a character
	for (i = 0; i < 24; i++)
	{
		BYTE c1, c2;
		
		i4x = i << 1;
		c1 = pFont[3 + i4x];
		c2 = pFont[4 + i4x];
		
		my16Bits = (c1 << 8) | c2;
		
		for (j = 0; j < 16; j++)
		{
			j2x = j;

			if ((1 << j2x) & my16Bits)
			{
				if (vid == 2)  //Jeff 20020823
				{
					*Y_XYB( (x+16-j)-(i>>2), (y+i) ) = iY;
					*C_XYB( (x+16-j)-(i>>2), (y+i) ) = iCbCr;
				}
				else
				{
					*Y_XY( (x+16-j)-(i>>2), (y+i) ) = iY;
					*C_XY( (x+16-j)-(i>>2), (y+i) ) = iCbCr;
				}
			}
        }
	}
}
#endif
#endif

#if 0//yltseng merged to fsgui.c
extern BYTE* get_font_entry(int, int);

void FSGUI_ShowChar_SR(int x, int y, BYTE c, BYTE iY, UINT16 iCbCr) //Jeff 20020823
{
	int     i, j, i4x, j2x;
	BYTE    *pFont;
	UINT32  my16Bits;
	
	
#ifdef OSD_FONT_COMPRESS
	pFont = (BYTE *)(SDRAM_BASE + COMP_OSD_FONT * 1024 + font_table[c]);
#else        
	pFont = (BYTE *)font_table[c];
#endif        
	
	//draw a character
	for (i = 0; i < 12; i++)
	{
		BYTE c1, c2;
		
		i4x = i << 2;
		c1 = pFont[3 + i4x];
		c2 = pFont[4 + i4x];
		
		my16Bits = (c1 << 8) | c2;
		
		for (j = 0; j < 8; j++)
		{
			j2x = j << 1;

			if ((1 << j2x) & my16Bits)
			{
				*Y_XYB_SR( (x+8-j), (y+i) ) = iY;
				*C_XYB_SR( (x+8-j), (y+i) ) = iCbCr;				
			}
        }
	}
}

#if defined (USE_SMALL_FONT) && (defined (MP3_LARGE_GUI) || defined(FS_BMP_GUI))
//libing 2005-1-5 21:23
void FSGUI_ShowChar (BYTE vid, int x, int y, BYTE c, BYTE iY, UINT16 iCbCr) //Jeff 20020823
{//libing modified it 2004-12-01 17:48 
    // Modified by yltseng 20040329 to reduce some computation
	int     p, i, j;
	unsigned  uiData;
	unsigned  data, data1; 
	BYTE    *pFont = NULL;

	pFont = get_font_entry(0,c);
	
    if( !pFont )
        return;

    //pFont += 3;
         p = 2;   
	//draw a character
	for (i = 0; i < 16; i++)
	{
		if(i%2==0)
		{
			data = pFont[++p];
			data1 = pFont[++p] & 0xf0;
			uiData = data<<4 | data1>>4;
		}else{
		        data = pFont[p] & 0x0f;
		        data1 = pFont[++p];
		        uiData = data<<8 | data1; 	
                }
		for (j = 0; j < 12; j++)
		{
			if ((1 << j) & uiData) 
			{
				if (vid == 2)
			{	
					*Y_XYB( (x+12-j), (y+i) ) = iY;
					*C_XYB( (x+12-j), (y+i) ) = iCbCr;
			}
			else
			{
				*Y_XY( (x + 12 - j), (y+i) ) = iY;
				*C_XY( (x + 12 - j), (y+i) ) = iCbCr;				
			}
			}
		}		
	}
}

#elif defined (MP3_LARGE_GUI) || defined (FS_BMP_GUI)	//Maoyong 2003/12/19 add  for 720*480 MP3 GUI
void FSGUI_ShowChar (BYTE vid, int x, int y, BYTE c, BYTE iY, UINT16 iCbCr) //Jeff 20020823
{
    // Modified by yltseng 20040329 to reduce some computation
	int     i, j;
	UINT16  uiData;
	BYTE    *pFont = NULL;

	pFont = get_font_entry(0,c);
	
    if( !pFont )
        return;

    pFont += 3;

	//draw a character
	for (i = 0; i < 24; i++)
	{
		uiData = ( pFont[0] << 8 ) | pFont[1];

		for (j = 0; j < 16; j++)
		{
			if ((1 << j) & uiData) 
			{
				*Y_XY( (x + 16 - j), (y+i) ) = iY;
				*C_XY( (x + 16 - j), (y+i) ) = iCbCr;				
			}
		}		

        pFont += 2;
	}
}

#elif defined (USE_SMALL_FONT) && (!defined (MP3_LARGE_GUI) && !defined(FS_BMP_GUI))
//libing 2005-1-6 9:18
void FSGUI_ShowChar(BYTE vid, int x, int y, BYTE c, BYTE iY, UINT16 iCbCr) //Jeff 20020823
{//libing modified it 2004-12-01 17:48
    // Modified by yltseng 20040329 to reduce some computation
	int     p, i, j;
	unsigned  uiData;
	unsigned  data, data1; 
	BYTE    *pFont = NULL;

	pFont = get_font_entry(0,c);
	
    if( !pFont )
        return;

    //pFont += 3;
         p = 1;   
	//draw a character
	for (i = 0; i < 8; i++)
	{
			p +=2;
			data = pFont[p];
			data1 = pFont[++p] & 0xf0;			
			uiData = data<<4 | data1>>4;
			unsigned uiOffsetBit = 0x01;			
		for (j = 0; j < 12; j++)
		{
			if (uiOffsetBit & uiData) 
			{
				if (vid == 2)
			{	
					*Y_XYB( (x+12-j), (y+i) ) = iY;
					*C_XYB( (x+12-j), (y+i) ) = iCbCr;
			}
			else
			{
				*Y_XY( (x + 12 - j), (y+i+1) ) = iY;
				*C_XY( (x + 12 - j), (y+i+1) ) = iCbCr;				
			}
		}
		uiOffsetBit <<= 2;
		}		
	}
}

#else//#if defined (MP3_LARGE_GUI) || defined (FS_BMP_GUI)		//Maoyong 2003/12/19 add  for 720*480 MP3 GUI
void FSGUI_ShowChar(BYTE vid, int x, int y, BYTE c, BYTE iY, UINT16 iCbCr) //Jeff 20020823
{
    // Modified by yltseng 20040329. Reduce computation and local variables
	int     i, j;
    UINT16  uiData;
	BYTE    *pFont;
		
	pFont = get_font_entry(0,c);

    if( !pFont )
        return;
        
    pFont += 3;

	//draw a character
	#ifdef PULIANG_6PIC_GUI	//yaowh add 05-02-04
	if (JPEG_THUMBNAIL_MODE == pFsJpeg->g_nJpegMode)
		for (i = 0; i < 24; i++)
		{
			uiData = ( pFont[0] << 8 ) | pFont[1];
	
			for (j = 0; j < 16; j++)
			{
				if ((1 << j) & uiData) 
				{
					*Y_XY( (x + 16 - j), (y+i) ) = iY;
					*C_XY( (x + 16 - j), (y+i) ) = iCbCr;				
				}
			}		
	
	        pFont += 2;
		}
	else
	#endif
	for (i = 0; i < 12; i++)
	{
        uiData = (pFont[0] << 8) | pFont[1];

        UINT32 uiOffsetBit = 0x01;

		for (j = 0; j < 8; j++)
		{
			if ( uiOffsetBit & uiData )
			{
				if (vid == 2)  //Jeff 20020823
				{
					*Y_XYB( (x+8-j), (y+i) ) = iY;
					*C_XYB( (x+8-j), (y+i) ) = iCbCr;
				}
				else
				{
					*Y_XY( (x+8-j), (y+i) ) = iY;
					*C_XY( (x+8-j), (y+i) ) = iCbCr;
				}
			}

            uiOffsetBit <<= 2;
        }

        pFont += 4;
	}
}
#endif//if defined (MP3_LARGE_GUI) || defined (FS_BMP_GUI)

#ifdef FS_BMP_GUI	
/*
    Function:in NTSC mode, show 1/4 size char for jpeg file information
    Creator:Feeling
*/
void FSGUI_ShowLittleChar(BYTE vid, int x, int y, BYTE c, BYTE iY, UINT16 iCbCr) 
{
    // Modified by yltseng 20040329. Reduce computation and local variables
	int     i, j;
    	UINT16  uiData;
	BYTE    *pFont;
		
	pFont = get_font_entry(0,c);

    if( !pFont )
        return;

    pFont += 3;

	//draw a character
	for (i = 0; i < 12; i++)
	{
        uiData = (pFont[0] << 8) | pFont[1];

        UINT32 uiOffsetBit = 0x01;

		for (j = 0; j < 8; j++)
		{
			if ( uiOffsetBit & uiData )
			{
				if (vid == 2)  //Jeff 20020823
				{
					*Y_XYB( (x+8-j), (y+i) ) = iY;
					*C_XYB( (x+8-j), (y+i) ) = iCbCr;
				}
				else
				{
					*Y_XY( (x+8-j), (y+i) ) = iY;
					*C_XY( (x+8-j), (y+i) ) = iCbCr;
				}
			}

            uiOffsetBit <<= 2;
        }

        pFont += 4;
	}
}
#endif//#ifdef FS_BMP_GUI

#endif//#if 0//yltseng merged to fsgui.c


