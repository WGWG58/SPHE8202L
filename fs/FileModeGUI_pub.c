/*-------------------------------------------------------------------------------
|  File Name   :  FileModeGUI_pub.c
|
|  Description :  Support USB/Card FAT File mode UI for copy and delete
|
|  Version    :   0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2004/12/31       sunzhonghui         Creating
|--------------------------------------------------------------------------------*/
#ifdef FILE_MODE_WRITE
#include "fsNAV.h"
#include "fsGUI1.h"
#include "global.h"

//ir related
#include "iop.h"
#include "ircode.h"
extern const BYTE ir_mapcode[256]; 

//to save the last access meida flag : MEDIA_CD or MEDIA_CARD
BYTE last_access_media = 0;
extern void SwitchMedia(BYTE direction);

//0:no CD,1:CD exists
unsigned int detect_CD = 0;

BYTE old_hl_index = 0;//whb add 05-08-16
//input table related
BYTE  Max_left_flag;
BYTE  Max_input_flag;
BYTE  Exit_Enter_flag;
char  *Str_temp;
char  *StrExit="EXIT";
char  *StrEnter="ENTER";
char  GetString[9] = {"        "};
int   input_xoffset;
int   Str_Index_x,Str_Index_y;
UINT8 Item_Num[5][8] = {{ 0, 1, 2, 3, 4, 5, 6, 7},
                        { 8, 9,10,11,12,13,14,15},
                        {16,17,18,19,20,21,22,23},
                        {24,25,26,27,28,29,30,31},
                        {32,33,34,35,36,37,38,39}};

char *Item_Str[] = {   
                       "A","B","C","D","E","F","G","H","I","J",
                       "K","L","M","N","O","P","Q","R","S","T",
                       "U","V","W","X","Y","Z","1","2","3","4",
                       "5","6","7","8","9","0","~","_","-","\\"};


//others
#include "fsgui.h"
//extern const BTNAREA Rect[];
//extern const BTNAREA fsArea[];
extern void  DrawFileIconX(int x, int y, int type, int mono);
#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI)
extern int  old_ControlArea; //record last ControlArea.
extern int  HL_show;//record HL .
#endif
BYTE   *mediaStr[]={};
BYTE   *functionStr[]={"COPY","DELETE","NEW","RENAME","FORMAT","CAPACITY INFO",};

BYTE   srceType_flag;
BYTE   file_mode_flag = 0;
extern void osd_init_periphGUI(void);
//extern void osd_DrawRegionString(UINT32 xStart, UINT32 yStart, const BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r);
extern void osd_draw_region_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor, BYTE r);
extern void osd_init_MediaswitchGUI(void);
extern int  ReadCDTitle(void);

//buffer areas
UINT32 iso9660buf_src = SDRAM_BASE + FS9660YA * 1024;
UINT32 iso9660buf_des = SDRAM_BASE + FS_STRUCTURE_YA * 1024;
FSJPEGDATA  *pFsJpeg_des_buf = (FSJPEGDATA  *)(SDRAM_BASE + FSJPEGDATA_DES_YA*1024);


//debug related
#ifndef DVDRELEASE
#define FILE_MODE_WRITE_DBG  1
#endif

#define	D	printf("INFO: __%d__(%s:%s)\n",__LINE__,__FILE__,__FUNCTION__);

#ifndef FILE_MODE_WRITE_DBG
    #undef printf
    #undef print_block
    #define printf(f, a...) do {} while (0)
    #define print_block(x,y) do {} while (0)
#endif

//main functions of FileMode Write
#include "FileMode_pub.h"
#include "FileMode_pub.c"
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : Draw_FileMode_Menu                                                   *
 *                                                                                       *
 *  Purposes      :                                                                      *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void Draw_FileMode_Menu(void)
{
    refresh_dir_page=1;
    refresh_file_page=1;
#if defined(MP3_LARGE_GUI) || defined(INDIGO_STYLE_LARGE_FSGUI) //2006-06-02, mimitsai add for HD ui.
    set_disbuf_now(0);
#endif

#ifdef NEW_MP3_GUI
    // background
    #ifdef MP3_LARGE_GUI
    FSGUI_FillFrameBuf(0,0, 720, 480, BK_GROUNDY,BK_CRCB);
    #else
    FSGUI_FillFrameBuf(0,0,352,288,BK_GROUNDY,BK_CRCB);
    #endif

    //draw left,right and bottom rec area
    #ifdef MONO_FSGUI //FS GUI, axel 2003-12-29 23:26
	//2006-06-02, mimitsai add for HD ui.
    DrawRectCorner(Rect[DIR_RECT],  CORNER_RAD, 1, 1, 0, 0, DIR_AREA_BKGROUND_CRCB);
    DrawRectCorner(Rect[FILE_RECT], CORNER_RAD, 1, 1, 0, 0, FILE_AREA_BKGROUND_CRCB);
    #else
    DrawRectCorner(Rect[DIR_RECT], CORNER_RAD,  1, DIR_STEP,  0, 0, DIR_AREA_BKGROUND_CRCB);
    DrawRectCorner(Rect[FILE_RECT], CORNER_RAD, 1, FILE_STEP, 0, 0, FILE_AREA_BKGROUND_CRCB);
    #endif
    DrawRectCorner(Rect[INFO_RECT], CORNER_RAD, 1, 40, 0, 0, DIR_AREA_BKGROUND_CRCB );

#elif defined FS_BMP_GUI

    // show background
    FSGUI_DrawBackGround(BG_XSTART, BG_YSTART + 0, BG_XREPEAT, BG_YREPEAT,LAY_BG_3_1);
    FSGUI_DrawBackGround(BG_XSTART, BG_YSTART + 0xaa, BG_XREPEAT, BG_YREPEAT,LAY_BG_3_2);
    FSGUI_DrawBackGround(BG_XSTART, BG_YSTART + 0x17d, BG_XREPEAT, BG_YREPEAT, LAY_BG_3_3);

    // dir background and file background
    FSGUI_ShowBmpCornerRect(DIR_AREA_XSTART, DIR_AREA_YSTART, DIR_AREA_XLEN, DIR_AREA_YLEN);
    FSGUI_ShowBmpCornerRect(FILE_AREA_XSTART, FILE_AREA_YSTART, FILE_AREA_XLEN, FILE_AREA_YLEN);

	//draw the left and right edge of the info area
	FSGUI_LayoutBmp(LAY_PLAYING_BAR_3_1);
	FSGUI_LayoutBmp(LAY_PLAYING_BAR_3_3);

    	//draw the info area background
	FSGUI_DrawBackGround(fsArea[FS_AREA_PATHBACKGROUND].xStart ,
		fsArea[FS_AREA_PATHBACKGROUND].yStart,
		fsArea[FS_AREA_PATHBACKGROUND].xSize,
		fsArea[FS_AREA_PATHBACKGROUND].ySize,
		LAY_PLAYING_BAR_3_2);

#else	//NEW_MP3_GUI
	// background
	FSGUI_FillFrameBuf(0,0,352,288,BK_GROUNDY,BK_GROUNDCRCB);

	// high line
	FSGUI_FillFrameBuf(0,Y1,352,LIGHT_WID,WHITE_Y,WHITE_CRCB);

	FSGUI_FillFrameBuf(0, Y1+LIGHT_WID,
		X1, SHADOW_WID,
		BLACK_Y, BLACK_CRCB);

	FSGUI_FillFrameBuf(X1+LIGHT_WID+SHADOW_WID, Y1+LIGHT_WID,
		352-X1-LIGHT_WID-SHADOW_WID, SHADOW_WID,
		BLACK_Y, BLACK_CRCB);

	FSGUI_FillFrameBuf(0, Y3,
		X1, LIGHT_WID,
		WHITE_Y,WHITE_CRCB);

	FSGUI_FillFrameBuf(X1+LIGHT_WID+SHADOW_WID, Y3,
		352-X1-LIGHT_WID-SHADOW_WID, LIGHT_WID,
		WHITE_Y,WHITE_CRCB);

	FSGUI_FillFrameBuf(0, Y3+LIGHT_WID,
		352, SHADOW_WID,
		BLACK_Y,BLACK_CRCB);

	FSGUI_FillFrameBuf(X1, Y1+LIGHT_WID,
		LIGHT_WID, Y3-Y1,
		WHITE_Y,WHITE_CRCB);

	FSGUI_FillFrameBuf(X1+LIGHT_WID, Y1+LIGHT_WID,
		SHADOW_WID, Y3-Y1-LIGHT_WID,
		BLACK_Y,BLACK_CRCB);
	DrawScroll();
#endif	//NEW_MP3_GUI

#ifdef FS_BMP_GUI
    FSGUI_ShowString( xStart + 46, 
		(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * iItem ), 
		buf, file_focus_y, file_focus_CrCb);
#else	
    FSGUI_ShowString( Rect[SRCE_TITILE_RECT].xStart,Rect[SRCE_TITILE_RECT].yStart, "SOURCE:", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
    FSGUI_ShowString( Rect[DEST_TITLE_RECT].xStart,Rect[DEST_TITLE_RECT].yStart, "DESTINATION:", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
#endif

    MediaItem_List(FS_DIRLIST_XSTART,SRCE);
    MediaItem_List(fsArea[FS_AREA_FILEITEM].xStart + 4,DEST);    
    ShowWarning("PLEASE SELECT TO ENTER");
    
    old_ControlArea = CNT_AREA_SRCE;
    pFsJpeg->ControlArea=CNT_AREA_SRCE;
    HL_show = pFsJpeg->media_current = pFsJpeg->media_will=1;
    FSGUI_FileMode_Init();

    ShowHL();
    Draw_File_Mode_Button();
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : Draw_File_Mode_Button                                                *
 *                                                                                       *
 *  Purposes      :                                                                      *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void Draw_File_Mode_Button(void)
{
    /*
    if((pFsJpeg->ControlArea==CNT_AREA_SRCE)||(pFsJpeg->gifsState == FS_STATE_MEDIA))  
    {
		FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart, fsArea[FS_AREA_BUTTON].yStart, 25, 25, BK_GROUNDY, BK_GROUNDCRCB);				        
    }
    else
    */
		DrawRect(fsArea[FS_AREA_BUTTON].xStart, fsArea[FS_AREA_BUTTON].yStart,
			25, 25,
			pFsJpeg->gifsFuncBtn == FS_FUNC_COPYING ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);

    	DrawFileIconX(fsArea[FS_AREA_BUTTON].xStart +6, fsArea[FS_AREA_BUTTON].yStart + 6, 2,0);

		DrawRect(fsArea[FS_AREA_BUTTON].xStart+30, fsArea[FS_AREA_BUTTON].yStart,
			25, 25,
			pFsJpeg->gifsFuncBtn == FS_FUNC_DELETE ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);

	    DrawFileIconX(fsArea[FS_AREA_BUTTON].xStart + 30 +6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2,0);

		DrawRect(fsArea[FS_AREA_BUTTON].xStart+60, fsArea[FS_AREA_BUTTON].yStart,
			25, 25,
			pFsJpeg->gifsFuncBtn == FS_FUNC_NEW ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);

	    DrawFileIconX(fsArea[FS_AREA_BUTTON].xStart + 60 +6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2,0);
			
		DrawRect(fsArea[FS_AREA_BUTTON].xStart+90, fsArea[FS_AREA_BUTTON].yStart,
			25, 25,
			pFsJpeg->gifsFuncBtn==FS_FUNC_RENAME ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);

	    DrawFileIconX(fsArea[FS_AREA_BUTTON].xStart + 90 +6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2,0);

		DrawRect(fsArea[FS_AREA_BUTTON].xStart+120, fsArea[FS_AREA_BUTTON].yStart,
			25, 25,
			pFsJpeg->gifsFuncBtn==FS_FUNC_FORMAT ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);

	    DrawFileIconX(fsArea[FS_AREA_BUTTON].xStart + 120 +6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2,0);
	
		DrawRect(fsArea[FS_AREA_BUTTON].xStart+150, fsArea[FS_AREA_BUTTON].yStart,
			25, 25,
			pFsJpeg->gifsFuncBtn==FS_FUNC_CAPACITY ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);	

	    DrawFileIconX(fsArea[FS_AREA_BUTTON].xStart + 150 +6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2,0);															    
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : FSShowFatIcon                                                        *                                                                               *
 *  Purposes      :                                                                      *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void FSShowFatIcon(UINT16 xStart,UINT16 yLoc)
{
    BYTE mode;
    
    if (pFsJpeg->dir_array[yLoc] != pFsJpeg->fsnav_dir_now)
        mode = 0;
    else
        mode = 1;
    DrawFolderIcon(xStart, (FS_DIRLIST_YSTART + FS_FILELIST_YSTEP * yLoc), mode);
    
	refresh_dir_icon = 0;
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : Media_detect                                                         *
 *                                                                                       *
 *  Purposes      :                                                                      *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
int Media_detect(void)
{
    BYTE MediaItem=0;
    
    #ifdef FILE_MODE_WRITE_DBG
    printf("detect_CD = %x\n",detect_CD);
    #endif
    
    if(detect_CD)
    {
        MediaItem++;
        mediaStr[MediaItem]= "CDROM";                        
    }

   if(detect_type & USB_DEVICE)
   {
       MediaItem++;
       mediaStr[MediaItem]= "U DISK";         
   }
#ifdef SPHE8202_CARD_STORAGE
   #ifdef CARD_SETUP_TYPE_3   //256Pin 16bit Non_share mode All card. 
   if(detect_type & CF_CARD_DEVICE) 
   {
       MediaItem++;
       mediaStr[MediaItem]= "CF CARD";                                
   }
   #endif
   if(detect_type & SD_CARD_DEVICE) 
   {
       MediaItem++;
       mediaStr[MediaItem]= "SD/MMC";                                        
   }
   if(detect_type & MS_CARD_DEVICE)
   {
       MediaItem++;
       mediaStr[MediaItem]= "MS/MSPRO";                                                
   }
   #ifdef CARD_SETUP_TYPE_3   //256Pin 16bit Non_share mode All card.       
   if(detect_type & SMC_CARD_DEVICE) 
   {
       MediaItem++;
       mediaStr[MediaItem]= "SMC CARD";                        
   }
   #endif  
#endif
   return MediaItem;
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : MediaItem_List                                                       *
 *                                                                                       *
 *  Purposes      :                                                                      *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void MediaItem_List(UINT16 xStart,BYTE media_flag)
{
    BYTE i,j;
    int iconArea;
    BYTE MediaItem = Media_detect();
    if(!media_flag)
    {
        iconArea=FS_AREA_DIRICON;    
        j=1;
    }    
    else
    {
        iconArea=FS_AREA_FILEICON;
        //if(mediaStr[1]== "CDROM")                
        if(!(strcmp(mediaStr[1],"CDROM")))
        {
            srceType_flag=1;               
            j=2; 
        }
        else
        {
            srceType_flag=0; 
            j=1;
        }

    }          
    for(i=j;i<=MediaItem;i++)
    {    
        FSGUI_ShowString( xStart,(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * (i-j) ), mediaStr[i], FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);        
        FSShowFatIcon(fsArea[iconArea].xStart,i-j);    
    }
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : ShowWarning                                                          *
 *                                                                                       *
 *  Purposes      :                                                                      *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void ShowWarning(const char *s)
{
	char    buf[30];

	#ifdef AUDIO_SHOW_SAVER
	if (bDisableGUI) return;
	#endif
	psprintf(buf, "%s", s);
	
#ifdef FS_BMP_GUI
    FSGUI_ShowString( fsArea[FS_AREA_WARNING].xStart + 46,
			fsArea[FS_AREA_WARNING].yStart,
			buf, file_focus_y, file_focus_CrCb);
#else	
    DrawRectCorner(Rect[INFO_RECT], CORNER_RAD,1, 40, 0x36, 0xc1, DIR_AREA_BKGROUND_CRCB );	
	FSGUI_ShowString( fsArea[FS_AREA_WARNING].xStart,
			fsArea[FS_AREA_WARNING].yStart,
			buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
#endif    	
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : FileModeGUI_select                                                   *
 *                                                                                       *
 *  Purposes      :                                                                      *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void FileModeGUI_select(void)
{
    printf("\n============FileModeGUI_select================\n");     
    int Res; 
    BYTE media_return = 0;    
    //input table select
    if(full_scrn & INPUT_TBL)
    {
        input_str_func_select();
        pFsJpeg->ControlArea = old_ControlArea;            
        ShowHL();
        return;
    }
    
    if(pFsJpeg->ControlArea == CNT_AREA_COPYBUTTON)
    {
        if(pFsJpeg->gifsState == FS_STATE_INIT)
        {
            pFsJpeg->gifsFuncBtn = FS_FUNC_COPYING;
            ButtonCopy();
        }
        else
        {
            ShowWarning("INVALID BUTTON NOW");
        } 
        ShowHL();
        return;                
    }
    
    if(pFsJpeg->ControlArea == CNT_AREA_DELETEBUTTON)
    {
        if(pFsJpeg->gifsState == FS_STATE_INIT)
        {        
            pFsJpeg->gifsFuncBtn = FS_FUNC_DELETE;
            ButtonDelete();
        }
        else
        {
            ShowWarning("INVALID BUTTON NOW");
        }
        ShowHL();
        return;                        
    }    

    if((pFsJpeg->ControlArea == CNT_AREA_NEWBUTTON) && !(full_scrn & INPUT_TBL))
    {
        if(pFsJpeg->gifsState == FS_STATE_INIT)
        {
            pFsJpeg->gifsFuncBtn = FS_FUNC_NEW;        
            ButtonNew();
        }
        else
		{
            ShowWarning("INVALID BUTTON NOW");
		}
        ShowHL();
        return;                        
    }
    
    if((pFsJpeg->ControlArea == CNT_AREA_RENAMEBUTTON) && !(full_scrn & INPUT_TBL))
    {
        if(pFsJpeg->gifsState == FS_STATE_INIT)
        {                        
            pFsJpeg->gifsFuncBtn = FS_FUNC_RENAME;
            ButtonRename();
        }
        else
		{
            ShowWarning("INVALID BUTTON NOW");
		}
        ShowHL();
        return;                        
    }
    
    if(pFsJpeg->ControlArea == CNT_AREA_FORMATBUTTON)
    {
        if(pFsJpeg->gifsState == FS_STATE_MEDIA)
        {                
            pFsJpeg->gifsFuncBtn = FS_FUNC_FORMAT;
            ButtonFormat();
        }
        else
		{
            ShowWarning("INVALID BUTTON NOW");
		}
        ShowHL();
        return;                        
    }
    
    if(pFsJpeg->ControlArea == CNT_AREA_CAPACITYBUTTON)
    {
        pFsJpeg->gifsFuncBtn = FS_FUNC_CAPACITY;
        ButtonCapacity();
        return;                        
    }              
    
    if(pFsJpeg->gifsState == FS_STATE_MEDIA)
    {
        pFsJpeg->gifsState = FS_STATE_INIT;
                
        FileModeJudgeSelMedia();
        if(media_type == MEDIA_CARD)
        {
            if(pFsJpeg->ControlArea == CNT_AREA_SRCE)
            {
                ShowWarning("IT IS INVALID NOW");
                pFsJpeg->gifsState = FS_STATE_MEDIA;
                return;   
            }
            else
            {     
            BYTE n;
            n = pFsJpeg->media_will;     //to avoid pFsJpeg->media_will being changed
            CardTestReady();             
            FileModeGetInfo();
            pFsJpeg->media_will = n;
        }
        }
        else if(media_type == MEDIA_CD)
        {
            media_type = MEDIA_CD;
            LoadModual(MODUAL_CDROM);
            sys_cmd=(CMD_FUNC|CMD_FUNC_CLOSE);
            ReadCDTitle();
            system_state=SYSTEM_SETUP_BROWSER;          
        }             
        ReadFile(&Res);
        pFsJpeg->file_index_in_dir = 0;	
        pFsJpeg->dir_current = 0;
        HL_show = pFsJpeg->file_current_in_page = 0;
        pFsJpeg->file_page_index = 0;        
    } 
    else if(pFsJpeg->gifsState == FS_STATE_INIT)
    {
        UINT16 index=0;
        if(pFsJpeg->ControlArea == CNT_AREA_SRCE)
            index = DirFileCount1[pFsJpeg->file_index_in_dir];
        else if(pFsJpeg->ControlArea == CNT_AREA_DEST)
            index = DirFileCount2[pFsJpeg->file_index_in_dir];

        if((index > ISO_FILE_MAX)&& JudgeDir(index-ISO_FILE_MAX))
        {   
            pFsJpeg->file_index_in_dir = 0;	
            HL_show = pFsJpeg->file_current_in_page = 0;
            pFsJpeg->file_page_index = 0;
            pFsJpeg->dir_current = index-ISO_FILE_MAX;
        }
        else if(index == ISO_FILE_MAX)
        {
            pFsJpeg->file_index_in_dir = 0;	
            HL_show = pFsJpeg->file_current_in_page = 0; 
            pFsJpeg->file_page_index = 0;
            pFsJpeg->dir_current = iso9660_dir[pFsJpeg->dir_current].parent_dir;
            if(pFsJpeg->dir_current == 0xffff)
                media_return = 1;
        }   
    }    
    watchdog_onoff(0);//disable watchdog 
    #ifdef FILE_MODE_WRITE_DBG
    show_fat_dir_file_info();
    #endif
    FileModeGUI_Refresh();

    if(media_return)
    {
        if(pFsJpeg->ControlArea == CNT_AREA_SRCE)
        {            
            MediaItem_List(FS_DIRLIST_XSTART,SRCE);
            old_ControlArea = CNT_AREA_SRCE;
            pFsJpeg->ControlArea = CNT_AREA_SRCE;
        }          
        else if(pFsJpeg->ControlArea == CNT_AREA_DEST)
        {            
            MediaItem_List(fsArea[FS_AREA_FILEITEM].xStart + 4,DEST); 
            old_ControlArea = CNT_AREA_DEST;
            pFsJpeg->ControlArea = CNT_AREA_DEST;            
        }    
        ShowWarning("PLEASE SELECT TO ENTER"); 
        HL_show = pFsJpeg->media_will;   
        FSGUI_FileMode_Init();
    }      
    else
    {
    	FileMode_DirList(pFsJpeg->dir_current);                                   
    }

    ShowHL();
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : FileModeGUI_up                                                       *
 *                                                                                       *
 *  Purposes      :                                                                      *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void FileModeGUI_up(void)
{
    //input table up
    if(full_scrn & INPUT_TBL)
    {
        input_str_func_up();
        return;
    }
    
    if((pFsJpeg->ControlArea == CNT_AREA_COPYBUTTON)||(pFsJpeg->ControlArea == CNT_AREA_DELETEBUTTON)
    ||(pFsJpeg->ControlArea == CNT_AREA_NEWBUTTON)||(pFsJpeg->ControlArea == CNT_AREA_RENAMEBUTTON)
    ||(pFsJpeg->ControlArea == CNT_AREA_FORMATBUTTON)||(pFsJpeg->ControlArea == CNT_AREA_CAPACITYBUTTON))
        return;                
    
    printf("\n============FileModeGUI_up================\n");
    if(pFsJpeg->gifsState == FS_STATE_MEDIA)
    {
        if(pFsJpeg->media_current<= pFsJpeg->count_media)
        {
            pFsJpeg->media_will--; 
            if(pFsJpeg->media_will < 1)
                pFsJpeg->media_will = pFsJpeg->count_media;                        
            pFsJpeg->media_current = pFsJpeg->media_will;                                             
        }
    }
    else if(pFsJpeg->gifsState == FS_STATE_INIT)
    {
        if(pFsJpeg->file_index_in_dir > 0)
        {
            printf("index=%d,count=%d\n",pFsJpeg->file_index_in_dir,pFsJpeg->file_count_in_dir);
            pFsJpeg->file_index_in_dir--;
            if(pFsJpeg->file_current_in_page > 0)
                pFsJpeg->file_current_in_page--;
            else
            {
                pFsJpeg->file_current_in_page = PER_PAGE-1;
                pFsJpeg->file_page_index--;
                FileModeGUI_Refresh();                                
                FileMode_DirList(pFsJpeg->dir_current);                                                
            }
        }       
    }    
    ShowHL();
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : FileModeGUI_down                                                     *
 *                                                                                       *
 *  Purposes      :                                                                      *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void FileModeGUI_down(void)
{
    //input table down
    if(full_scrn & INPUT_TBL)
    {
        input_str_func_down();
        return;
    }
    
    printf("\n============FileModeGUI_down================\n");
    
    if((pFsJpeg->ControlArea == CNT_AREA_COPYBUTTON)||(pFsJpeg->ControlArea == CNT_AREA_DELETEBUTTON)
    ||(pFsJpeg->ControlArea == CNT_AREA_NEWBUTTON)||(pFsJpeg->ControlArea == CNT_AREA_RENAMEBUTTON)
    ||(pFsJpeg->ControlArea == CNT_AREA_FORMATBUTTON)||(pFsJpeg->ControlArea == CNT_AREA_CAPACITYBUTTON))
        return;
            
    if(pFsJpeg->gifsState == FS_STATE_MEDIA)
    {
        if(pFsJpeg->media_current<= pFsJpeg->count_media)
        {
            pFsJpeg->media_will++; 
            if(pFsJpeg->media_will > pFsJpeg->count_media)
            {
                if((!srceType_flag)||(pFsJpeg->ControlArea == CNT_AREA_SRCE))
                    pFsJpeg->media_will = 1;                        
                else if(srceType_flag)
                    pFsJpeg->media_will = 2;                   
            }
            pFsJpeg->media_current = pFsJpeg->media_will;                           
        }
    }
    else if(pFsJpeg->gifsState == FS_STATE_INIT)
    {
        if(pFsJpeg->file_index_in_dir < (pFsJpeg->file_count_in_dir-1))
        {
            printf("index=%d,count=%d\n",pFsJpeg->file_index_in_dir,pFsJpeg->file_count_in_dir);
            pFsJpeg->file_index_in_dir++;
            if(pFsJpeg->file_current_in_page < (PER_PAGE-1))
                pFsJpeg->file_current_in_page++;
            else
            {
                pFsJpeg->file_current_in_page = 0;
                pFsJpeg->file_page_index++; 
                FileModeGUI_Refresh();
                FileMode_DirList(pFsJpeg->dir_current);                                
            }
        }          
    }
    ShowHL();       
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : FileModeGUI_left                                                     *
 *                                                                                       *
 *  Purposes      :                                                                      *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void FileModeGUI_left(void)
{
    printf("\n============FileModeGUI_left================\n");

    //input table up
    if(full_scrn & INPUT_TBL)
    {
        input_str_func_left();
        return;
    }

    if(pFsJpeg->ControlArea == CNT_AREA_DEST)
    {
        Switch2SrcDesBuf(SRCE);
        pFsJpeg->ControlArea = CNT_AREA_SRCE;                     
        ShowWarning("PLEASE SELECT TO ENTER");                            
    }
    else if(pFsJpeg->ControlArea == CNT_AREA_SRCE)   
    {              
        if(pFsJpeg->gifsState == FS_STATE_INIT)
        {
            Switch2SrcDesBuf(DEST);
                  
//            if(pFsJpeg->gifsState == FS_STATE_INIT)
                pFsJpeg->ControlArea=CNT_AREA_COPYBUTTON;
                ShowWarning(functionStr[0]);                
//            else 
//                pFsJpeg->ControlArea=CNT_AREA_FORMATBUTTON; 
           pFsJpeg->gifsFuncBtn = 0; 
        }           
    }
    else
    {
        int buttonNum = pFsJpeg->ControlArea;
        if(pFsJpeg->ControlArea >= CNT_AREA_COPYBUTTON)
        {
            buttonNum --;
            pFsJpeg->ControlArea = buttonNum;
            ShowWarning(functionStr[buttonNum - 7]);                            
        }
        if(pFsJpeg->ControlArea < CNT_AREA_COPYBUTTON)
        {
            Switch2SrcDesBuf(SRCE);
            ShowWarning("PLEASE SELECT TO ENTER");            
        }
    }     
    ShowHL();
}

void FSGUI_FileMode_Init(void)
{
    pFsJpeg->gifsState = FS_STATE_MEDIA;
    pFsJpeg->count_media = Media_detect();   
        
    pFsJpeg->file_index_in_dir = 0;	
    pFsJpeg->file_current_in_page = 0;
    pFsJpeg->file_page_index = 0;
    pFsJpeg->dir_current = 0;
    pFsJpeg->iso9660_dir_cnt = 0;
    pFsJpeg->iso9660_file_cnt = 0;
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : FileModeGUI_right                                                    *
 *                                                                                       *
 *  Purposes      :                                                                      *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void FileModeGUI_right(void)
{
    //input table right
    if(full_scrn & INPUT_TBL)
    {
        input_str_func_right();
        return;
    }
    
    printf("\n============FileModeGUI_right================\n");
    if(pFsJpeg->ControlArea == CNT_AREA_SRCE)
    {
        Switch2SrcDesBuf(DEST);

        if(pFsJpeg->gifsState == FS_STATE_MEDIA)
        {
            pFsJpeg->ControlArea=CNT_AREA_DEST;
            FSGUI_FileMode_Init();
        
            //if(mediaStr[1] == "CDROM")
            if(!(strcmp(mediaStr[1],"CDROM")))
                pFsJpeg->media_will = pFsJpeg->media_current = 2;
            else
                pFsJpeg->media_will = pFsJpeg->media_current = 1; 
        }
        ShowWarning("PLEASE SELECT TO ENTER");             
    }
    else if(pFsJpeg->ControlArea == CNT_AREA_DEST)
    {
        pFsJpeg->ControlArea=CNT_AREA_CAPACITYBUTTON;  
        ShowWarning(functionStr[5]); 
    }
    else if(pFsJpeg->ControlArea == CNT_AREA_CAPACITYBUTTON)
    {
        pFsJpeg->ControlArea = CNT_AREA_DEST; 
        pFsJpeg->gifsFuncBtn = 0;           
        Switch2SrcDesBuf(DEST);
        if(pFsJpeg->gifsState == FS_STATE_MEDIA)
        {
            pFsJpeg->ControlArea=CNT_AREA_DEST;
            FSGUI_FileMode_Init();
        
            //if(mediaStr[1] == "CDROM")
            if(!(strcmp(mediaStr[1],"CDROM")))
                pFsJpeg->media_will = pFsJpeg->media_current = 2;
            else
                pFsJpeg->media_will = pFsJpeg->media_current = 1;             
        }  
        else  
        HL_show = pFsJpeg->file_current_in_page;                            
        ShowWarning("PLEASE SELECT TO ENTER");                        
    }
    else
    {
        int buttonNum = pFsJpeg->ControlArea;
        if(pFsJpeg->ControlArea <= CNT_AREA_CAPACITYBUTTON)
        {
            buttonNum ++;
            pFsJpeg->ControlArea = buttonNum;
            ShowWarning(functionStr[buttonNum -7]);   //need according to the user's define                         
        }
        if(pFsJpeg->ControlArea > CNT_AREA_CAPACITYBUTTON)
        {
            Switch2SrcDesBuf(DEST);
            ShowWarning("PLEASE SELECT TO ENTER");
        }
    }                
    ShowHL();
}
//*******************************************************************************************//
//play
void FileModeGUI_play(void)
{
    printf("\n============FileModeGUI_play================\n");

    if(pFsJpeg->gifsState == FS_STATE_MEDIA)
    {
        if(pFsJpeg->ControlArea == CNT_AREA_SRCE)
        {
            //to clear old control area.
            old_ControlArea = 0;
            
            file_mode_flag = 0;
            FileModeJudgeSelMedia();
            FileModeSwitchMedia();
        }
    }
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : show_fat_dir_file_info                                               *
 *                                                                                       *
 *  Purposes      :  Show fat dir and file information in dubug.                         *
 *                                                                                       *
 *  Descriptions  :   Use for test.                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void show_fat_dir_file_info(void) 
{
#ifdef FILE_MODE_WRITE_DBG    
    printf("===========Show directory sturcture=========.\n");
    printf("===========all dir count:%d=========\n",pFsJpeg->iso9660_dir_cnt);
    int i,j,k;
    for (i = 0; i < pFsJpeg->iso9660_dir_cnt; i++)
    {
        printf("\nDir===%d:[%s],parent_dir===%d\n", i, iso9660_dir[i].name,iso9660_dir[i].parent_dir);
    }
    printf("Show the file name in the related directory .\n");
    for (i = 0; i < pFsJpeg->iso9660_dir_cnt; i++)
    {
        printf("\n===READ DIR:%d name:[%s],file amount:%d \n",i,iso9660_dir[i].name,iso9660_dir[i].dir);
        k=0;
        for (j = 0; j < pFsJpeg->iso9660_file_cnt; j++)
        {
            if(i==iso9660_file[j].parent_dir)            
            printf("  (%d)File:%s\n",++k,iso9660_file[j].name);            
              
        }    
    }
#endif 
} 

void ShowFileItem(UINT16 xStart,int hl_index)
{
    UINT16 index;
//whb modified    
//S:去除bug：file list 翻页且下一页文件数不足 PER_PAGE 个时，在list最后一行显示有误
    if( ((pFsJpeg->file_count_in_dir - PER_PAGE*(pFsJpeg->file_page_index) ) < PER_PAGE)
        && ( hl_index == (PER_PAGE-1) ) && ( hl_index == old_hl_index ) )
        hl_index = 0;
        
    old_hl_index = hl_index;
        
    index = hl_index+PER_PAGE*(pFsJpeg->file_page_index);
    if(pFsJpeg->ControlArea == CNT_AREA_SRCE)
        index = DirFileCount1[index];
    else if((pFsJpeg->ControlArea == CNT_AREA_DEST)||(pFsJpeg->ControlArea == CNT_AREA_CAPACITYBUTTON))
        index = DirFileCount2[index];

    if(index == ISO_FILE_MAX)
        ShowSrceItem(xStart, hl_index,"\\..");	        
    else if(index > ISO_FILE_MAX)
        ShowSrceItem(xStart, hl_index,iso9660_dir[(index-ISO_FILE_MAX)].name);            
    else
        ShowSrceItem(xStart, hl_index,iso9660_file[index].name);
}

/****************************************************************************************\
 *                                                                                       *
 *  Function Name : Src_FileMode_DirList                                                 *
 *                                                                                       *
 *  Purposes      : Show all dir or file item  in that we select dir .                   *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void FileMode_DirList(UINT16 iDirIndex)
{
    #ifdef FILE_MODE_WRITE_DBG   
    printf("\n===========Src_FileMode_DirList=========.\n");
    #endif
    int i = 0,j = 0;
    UINT16 xStart = 0; 
    int iconArea = 0;      
    
    if(pFsJpeg == &(share_data.JPEG)) 
    {
        pFsJpeg->ControlArea=CNT_AREA_SRCE;
        xStart = FS_DIRLIST_XSTART;
        iconArea = FS_AREA_DIRICON;
    } 
    else if(pFsJpeg == pFsJpeg_des_buf) 
    {
        pFsJpeg->ControlArea=CNT_AREA_DEST; 
        xStart = fsArea[FS_AREA_FILEITEM].xStart + 4;
        iconArea = FS_AREA_FILEICON;        
    }     

    pFsJpeg->file_count_in_dir = JudgeDir(iDirIndex);//total file count.
    printf("--------pFsJpeg->file_count_in_dir = %d\n",pFsJpeg->file_count_in_dir);
    if(pFsJpeg->file_count_in_dir >= PER_PAGE*(pFsJpeg->file_page_index+1))
        j = PER_PAGE;
    else
        j = (pFsJpeg->file_count_in_dir) % PER_PAGE;
	
	for(i=0;i<j;i++)
	{
	    int index = 0;
        if(pFsJpeg->ControlArea == CNT_AREA_SRCE)
	        index = DirFileCount1[i+PER_PAGE*(pFsJpeg->file_page_index)];
        else if(pFsJpeg->ControlArea == CNT_AREA_DEST)
	        index = DirFileCount2[i+PER_PAGE*(pFsJpeg->file_page_index)];  
 
	    if(index == ISO_FILE_MAX )
	    {
	        printf("\n===========\\..=========\n");
            ShowSrceItem(xStart, 0,"\\..");	        
	    }
	    else if(index > ISO_FILE_MAX)
	    {   
	        printf("\n===========FSShowMediaIcon=========\n");
            ShowSrceItem(xStart, i,iso9660_dir[(index-ISO_FILE_MAX)].name);            
	        FSShowFatIcon(fsArea[iconArea].xStart,i);	        
	    }
	    else
	    {
	        printf("\n===========FSShowFileIcon=========\n");	       
            ShowSrceItem(xStart, i,iso9660_file[index].name); 
	        FSShowFileIcon(index, iconArea,i);	       
	    }
	}
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : ShowSrceItem                                                         *
 *                                                                                       *
 *  Purposes      : Show Source dir or file item                                         *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void ShowSrceItem(UINT16 xStart,int iItem, const char *s)
{
  	char    buf[20];
    psprintf(buf,s);
#ifdef FS_BMP_GUI
    FSGUI_ShowString( xStart + 46, 
		(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * iItem ), 
		buf, file_focus_y, file_focus_CrCb);
#else	
	FSGUI_ShowString( xStart, 
		(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * iItem ), 
		buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
#endif    
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : FSShowFileIcon                                                       *
 *                                                                                       *
 *  Purposes      : Show file ICON                                                       *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void FSShowFileIcon(UINT16 index, BYTE area, int yLoc)
{
    int type = 0;
    
    switch(iso9660_file[index].file_type)
    {
        case CDROM:
        case CDROM_WMA:
            type = CNT_AREA_MP3BUTTON - 2;
            break;
        case CDROM_JPEG:
            type = CNT_AREA_JPEGBUTTON - 2;
            break;
        case CDROM_MPG:
        case CDROM_DAT:
        case CDROM_MP4:
            type = CNT_AREA_OTHERBUTTON - 2;
            break;
    } 
    DrawFileIconX(fsArea[area].xStart+2,(fsArea[area].yStart+FS_FILELIST_YSTEP*yLoc),type,0);       
}

/****************************************************************************************\
 *                                                                                       *
 *  Function Name : FileModeGUI_Refresh_Src                                              *
 *                                                                                       *
 *  Purposes      : Refresh source GUI                                                   *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void FileModeGUI_Refresh(void)
{
    int i;
    if(pFsJpeg == &(share_data.JPEG)) 
        pFsJpeg->ControlArea=CNT_AREA_SRCE;
    else if(pFsJpeg == pFsJpeg_des_buf) 
        pFsJpeg->ControlArea=CNT_AREA_DEST; 

    if(pFsJpeg->ControlArea == CNT_AREA_SRCE)
    {
        for(i =0;i<PER_PAGE;i++)
        {
			//2006-06-02, mimitsai add for HD ui.        
            ClearRectCorner(Rect[DIR_RECT],        DIR_STEP, 0, 0, DIR_AREA_BKGROUND_CRCB, FS_AREA_DIRICON,i);
            ClearRectArea(Rect[FS_AREA_DIRITEM], DIR_STEP, 0, 0, 0x36, 0xc1, DIR_AREA_BKGROUND_CRCB, FS_AREA_DIRITEM, i);
        }
    }
    else if(pFsJpeg->ControlArea == CNT_AREA_DEST)
    {
        for(i=0; i<PER_PAGE;i++)
        {
			//2006-06-02, mimitsai add for HD ui.        
            ClearRectArea(Rect[FILE_RECT], FILE_STEP, 0, 0, 0x36, 0xc1, DIR_AREA_BKGROUND_CRCB, FS_AREA_FILEICON, i);        
            ClearRectArea(Rect[FILE_RECT], FILE_STEP, 0, 0, 0x36, 0xc1, FILE_AREA_BKGROUND_CRCB,FS_AREA_FILEITEM, i);
        }
    }            

}

/****************************************************************************************\
 *                                                                                       *
 *  Function Name : FileModeMainLoop                                                     *
 *                                                                                       *
 *  Purposes      : Get key code & call related functions.                               *
 *                                                                                       *
 *  Descriptions  : Only up,down,right,left,select,return,play KEY valid.                *
 *                  Called by ircmd_mute().                                              *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      : Creator : wangwei,2005-1-8 14:36                                     *
 *                                                                                       *
\****************************************************************************************/
void FileModeMainLoop(void)
{
    file_mode_flag = 1;    
    FSGUI_FileMode_Init();        
    UINT32 rx;
    
    watchdog_onoff(0);//disable watchdog 
    
    for(;;)//main loop
    {
    	if(uhci_slaveDetect())//frank.huang 050816 add to support usb plug in filemode
    	{				
		    pFsJpeg = pFsJpeg_des_buf;
		    memset(pFsJpeg, 0, sizeof(FSJPEGDATA));
		    pFsJpeg->gifsState = FS_STATE_MEDIA;
		    pFsJpeg = &(share_data.JPEG);
		    memset(pFsJpeg, 0, sizeof(FSJPEGDATA));  
		    pFsJpeg->gifsState = FS_STATE_MEDIA;			
		    Draw_FileMode_Menu();
	    }
        //to get key code
        rx = regs0->iop_data[IR_PORT];
        if (rx & IR_RDY)
        {
            rx = reverse_fun(rx);
            rx = ir_mapcode[(BYTE) rx];
            regs0->iop_data[IR_PORT] &= (~IR_RDY);  
        }
        //--------------------------------------------------------------
        if(rx == IRC_UP)         //IRC_UP
        {
            FileModeGUI_up();
        }
        //--------------------------------------------------------------
        else if(rx == IRC_DOWN)  //IRC_DOWN
        {
            FileModeGUI_down();
        }
        //--------------------------------------------------------------
        else if(rx == IRC_RIGHT) //IRC_RIGHT
        {
            FileModeGUI_right();
        }
        //--------------------------------------------------------------
        else if(rx == IRC_LEFT)  //IRC_LEFT
        {
            FileModeGUI_left();
        }
        //--------------------------------------------------------------
        else if(rx == IRC_SELECT)//IRC_SELECT
        {
            FileModeGUI_select();
        }
        //--------------------------------------------------------------
        else if((rx == IRC_PLAY_RESUME)||(rx == IRC_PLAY))  //IRC_PLAY
        {
            if(pFsJpeg->gifsState == FS_STATE_MEDIA)//for only FS_STATE_MEDIA can "PLAY" Media.
            {
                FileModeGUI_play();
                break;
            }
        }
        //--------------------------------------------------------------
        else if(rx == IRC_EJECT)  //IRC_EJECT
        {
            file_mode_flag = 0;
            call_ir_func(IRC_EJECT);
            play_state = VCD_STATE_OPEN;
            system_state=SYSTEM_OPEN;    
            break;
        }
        //--------------------------------------------------------------
        else if(rx == IRC_POWER)  //IRC_POWER
        {
             call_ir_func(IRC_POWER);
             play_state = VCD_STATE_POWER;  
             system_state=SYSTEM_POWER;  
            break;
        }
        //--------------------------------------------------------------
        watchdog_onoff(0);//disable watchdog 
    }
    //to clear old control area.
    old_ControlArea = 0;      
    
    watchdog_renew(0xffff);//renew watchdog
    watchdog_onoff(1);//enable watchdog
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : FileModeJudgeSelMedia                                                *
 *                                                                                       *
 *  Purposes      : To judge whitch media we select                                      *
 *                                                                                       *
 *  Descriptions  : To judge whitch media we select & store it in                        *
 *                  variable current_access_storage                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      : Creator : wangwei,2005-1-8 14:36                                     *
 *                                                                                       *
\****************************************************************************************/
void FileModeJudgeSelMedia(void)
{
    //if(mediaStr[pFsJpeg->media_will] == "CDROM")
    if(!(strcmp(mediaStr[pFsJpeg->media_will],"CDROM")))
    {
        printf("========== CDROM =============\n");
        media_type = MEDIA_CD;    
    }
    else
    {
        media_type = MEDIA_CARD;
        //if(mediaStr[pFsJpeg->media_will] == "U DISK")
        if(!(strcmp(mediaStr[pFsJpeg->media_will],"U DISK")))
        {
            printf("========== U DISC =============\n");
            storage_type = USB_DEVICE;
        }
        //else if(mediaStr[pFsJpeg->media_will] == "CF CARD")
        else if(!(strcmp(mediaStr[pFsJpeg->media_will],"CF CARD")))
        {
            printf("========== CF CARD =============\n");
            storage_type = CF_CARD_DEVICE;
        }
        //else if(mediaStr[pFsJpeg->media_will] == "SD/MMC")
        else if(!(strcmp(mediaStr[pFsJpeg->media_will],"SD/MMC")))
        {
            printf("========== SD/MMC =============\n");
            storage_type = SD_CARD_DEVICE;
        }
        //else if(mediaStr[pFsJpeg->media_will] == "MS/MSPRO")
        else if(!(strcmp(mediaStr[pFsJpeg->media_will],"MS/MSPRO")))
        {
            printf("========== MS/MSPRO =============\n");
            storage_type = MS_CARD_DEVICE;
        }
        //else if(mediaStr[pFsJpeg->media_will] == "SMC CARD")
        else if(!(strcmp(mediaStr[pFsJpeg->media_will],"SMC CARD")))
        {
            printf("========== SMC CARD =============\n");
            storage_type = SMC_CARD_DEVICE;
        }
    }
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : FileModeSwitchMedia                                                  *
 *                                                                                       *
 *  Purposes      : Switch to selected device                                            *
 *                                                                                       *
 *  Descriptions  : Switch to selected device                                            *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      : Creator : wangwei,2005-1-8 14:36                                     *
 *                                                                                       *
\****************************************************************************************/
void FileModeSwitchMedia(void)
{
    if(last_access_media == MEDIA_CD)
    {
        if(media_type == MEDIA_CARD)
            SwitchMedia(CD2CARD);
        else
        {
            no_disk_cnt = DETECT_TIMES;
            media_type = MEDIA_CD;          
            adv_search_time = 0;
            play_state = VCD_STATE_CLOSE;   
            full_scrn = 0;     
            ClearOsdMsg(0);
            t_disp = 0; 
            osd_init();              
            system_state = SYSTEM_OPEN;
        }
    }
    else if(last_access_media == MEDIA_CARD)
    {
        if(media_type == MEDIA_CARD )
            SwitchMedia(CARD2CARD);
        else
            SwitchMedia(CARD2CD);
    }
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : ShowCapacityInfo                                                     *
 *                                                                                       *
 *  Purposes      : Show the capacity infomation if the "CapacityInfo" button is select  *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *  Creator       : sunzhh 2004-11-10                                                    *
 *                                                                                       *
\****************************************************************************************/
void ShowCapacityInfo(void)
{
    #ifdef SPHE8202_ALL_TYPE_CARD_WRITE
    card_browse_sign = 0;	//dingzhy add for not into CardSetBrowse
    #endif
    //InfoGui_flag=1;
    //to get capacity information
    StorageGetCapacityInfo();
    
    //init region
    osd_init_MediaswitchGUI();
    
    BYTE *title_str="CAPACITY INFO";
    osd_draw_region_rect(0, 0, 64*4, 40, COLOR_GREEN, 3);
    osd_DrawRegionString(2, 1, title_str, COLOR_YELLOW, COLOR_GREEN, FUNCTION_REGION);
    
    //draw background of the region
    SetOsdCol(FUNCTION_REGION, FUNCTION_REGION, 0,__palette4F(192,192, 192, 0xe0));		
    osd_DrawRegionString(2, 1, title_str, COLOR_YELLOW, COLOR_GREEN, FUNCTION_REGION);
    psprintf(linebuf, "TOTAL: %5dM", uiTotalCapacity);
    
    //draw string on button
    osd_DrawRegionString(1,8+5,linebuf, COLOR_WHITE, COLOR_GRAYWHITE,3);		       
    psprintf(linebuf, "USED: %6dM", uiUsedCapacity);
    
    //draw string on button
    osd_DrawRegionString(1,2*8+5,linebuf, COLOR_WHITE, COLOR_GRAYWHITE,3);		
    psprintf(linebuf, "REMAIN: %4dM", uiRemainCapacity);
    
    //draw string on button
    osd_DrawRegionString(1,3*8+5,linebuf, COLOR_WHITE, COLOR_GRAYWHITE,3);		
}
/****************************************************************************************\
 *                                                                                       *
 *                           New input table related functions                           *
 *                                                                                       *
\****************************************************************************************/
//Start,New input table related functions.
void input_str_clear_HL(void)
{
    int i;
    BYTE *str[] = {   " A  B  C  D  E  F  G  H ",
                      " I  J  K  L  M  N  O  P ",
                      " Q  R  S  T  U  V  W  X ",
                      " Y  Z  1  2  3  4  5  6 ",
                      " 7  8  9  0  ~  _  -  \\",
                      "                        ",                    
                      "    EXIT        ENTER   "};
    for(i=0;i<=6;i++)
        osd_DrawRegionString(4, (i+1)*8+5, str[i], COLOR_WHITE, COLOR_GRAYWHITE, FUNCTION_REGION);                     
}
/****************************************************************************************/
void input_HL_ItemStr(BYTE itemstr_index )
{
    BYTE itemstr_xstart = 0;
    BYTE itemstr_ystart = 0;
    BYTE x,y;   
    x = itemstr_index % 8;
    y = itemstr_index / 8;
    itemstr_xstart = 5  + x * 3;
    itemstr_ystart = 13 + y * 8;
    osd_DrawRegionString(itemstr_xstart, itemstr_ystart,Item_Str[itemstr_index], COLOR_WHITE, COLOR_DBLUE,FUNCTION_REGION);      
}
/****************************************************************************************/
void input_str_func_up(void)
{
    input_str_clear_HL();
    Str_Index_x--;
    if(Str_Index_x<-1)
    {
        Str_Index_x=-1;        
    }
    else if(Str_Index_x==-1)
    {
        
    }
    else if(Str_Index_x>-1)
    {
        input_HL_ItemStr(Item_Num[Str_Index_x][Str_Index_y]);
    }
}
/****************************************************************************************/
void input_str_func_down(void)
{   
    input_str_clear_HL();
    Str_Index_x++;
    if((Str_Index_x==5)&&(Str_Index_y<4))
    {
        Exit_Enter_flag=1;
        osd_DrawRegionString(8, 7*8+5, StrExit, COLOR_WHITE, COLOR_DBLUE, FUNCTION_REGION);	
    }
    else if((Str_Index_x==5)&&(Str_Index_y>=4))
    {
        Exit_Enter_flag=2;
        osd_DrawRegionString(20, 7*8+5, StrEnter, COLOR_WHITE, COLOR_DBLUE, FUNCTION_REGION);	
    }
    else if(Str_Index_x>5)
    {     
        Str_Index_x=5;
        if(Exit_Enter_flag==1) 
        {
            osd_DrawRegionString(8, 7*8+5, StrExit, COLOR_WHITE, COLOR_DBLUE, FUNCTION_REGION);	
        }
        else if(Exit_Enter_flag==2) 
        {
            osd_DrawRegionString(20, 7*8+5, StrEnter, COLOR_WHITE, COLOR_DBLUE, FUNCTION_REGION);	
        }
        
    }
    else if(Str_Index_x<5)
    {      
        input_HL_ItemStr(Item_Num[Str_Index_x][Str_Index_y]);
    }
}
/****************************************************************************************/
void input_str_func_left(void)
{        
    if(Str_Index_x==-1)
    {        
        Max_input_flag=0;
        input_xoffset--;
        printf("=============input_xoffset:%d=================\n",input_xoffset);
        if(input_xoffset<0)
        { 
            Max_left_flag=1;
            input_xoffset=0;
        }
        else if(Max_left_flag!=1)
        {           
            GetString[input_xoffset]=' ';
            printf("===GetString:%s========\n",GetString); 
            osd_DrawRegionString(14+input_xoffset, 1, " ", COLOR_DBLUE,COLOR_GREEN, FUNCTION_REGION); 
        }   
        return;
    }
    input_str_clear_HL();  
    if((Str_Index_x==5)&&(Exit_Enter_flag==2))
    {
        Exit_Enter_flag=1;
        osd_DrawRegionString(8, 7*8+5, StrExit, COLOR_WHITE, COLOR_DBLUE, FUNCTION_REGION);	
    }  
    else if((Str_Index_x==5)&&(Exit_Enter_flag==1))
    {       
        osd_DrawRegionString(8, 7*8+5, StrExit, COLOR_WHITE, COLOR_DBLUE, FUNCTION_REGION);	
    }  
    else if(Str_Index_x<5)
    {     
        Str_Index_y--;
        if(Str_Index_y<0) Str_Index_y=0;
        input_HL_ItemStr(Item_Num[Str_Index_x][Str_Index_y]);
    }
}
/****************************************************************************************/
void input_str_func_right(void)
{     
    if(Str_Index_x==-1)
    {   
        if(input_xoffset>7)
        {
            Max_input_flag=1;
            input_xoffset=7;
        }
        else if((input_xoffset<=7)&&(Max_input_flag!=1))
        {
            GetString[input_xoffset]=' ';
            printf("===GetString:%s========\n",GetString); 
            osd_DrawRegionString(14+input_xoffset, 1, " ", COLOR_DBLUE,COLOR_GREEN, FUNCTION_REGION); 
        }
        input_xoffset++;
        return;
    }    
    input_str_clear_HL();  
    if((Str_Index_x==5)&&(Exit_Enter_flag==1))
    {
        Exit_Enter_flag=2;
        osd_DrawRegionString(20, 7*8+5, StrEnter, COLOR_WHITE, COLOR_DBLUE, FUNCTION_REGION);	
    }     
    else  if((Str_Index_x==5)&&(Exit_Enter_flag==2))
    {      
        osd_DrawRegionString(20, 7*8+5, StrEnter, COLOR_WHITE, COLOR_DBLUE, FUNCTION_REGION);	
    }     
    else if(Str_Index_x<5)
    {     
        Str_Index_y++;
        if(Str_Index_y>7) Str_Index_y=7;
        input_HL_ItemStr(Item_Num[Str_Index_x][Str_Index_y]);
    }
}
/****************************************************************************************/
void input_str_func_select(void)
{
    BYTE Str_ID=0;     
    Max_left_flag=0;
    if((Str_Index_x==5)&&(Exit_Enter_flag==1))
    {
        input_str_func_exit();
        return;
    } 
    if((Str_Index_x==5)&&(Exit_Enter_flag==2))
    {
        input_str_func_enter();
        
        //added by wangwei,2005-1-13 16:33
        full_scrn &= (~INPUT_TBL);//for release the IR
        osd_init();
        
        //for debug
        int i = 0;
        for(;i<8;i++)
        {
            printf("++++++++++++++++++++++++++++++++ GetString[%x] = %x+++++++++++++\n",i,GetString[i]);
        }
        
        return;
    }   
    Str_ID=Item_Num[Str_Index_x][Str_Index_y];
    if(input_xoffset>7)
    {
        Max_input_flag=1;
        input_xoffset=7;
    }
    else if((input_xoffset<=7)&&(Max_input_flag!=1))
    {
        Str_temp=Item_Str[Str_ID];
        GetString[input_xoffset]=*Str_temp;
        osd_DrawRegionString(14+input_xoffset, 1, Item_Str[Str_ID], COLOR_DBLUE,COLOR_LBLUE, FUNCTION_REGION);
    }
    input_xoffset++;
}
/****************************************************************************************/
void input_str_func_exit(void)
{
     input_str_clear_variable();
     full_scrn &= (~INPUT_TBL);//for release the IR
	 osd_init();    
}
/****************************************************************************************/
void input_str_func_enter(void)
{
    char  NullStr[9] = {"        "};
    if(strcmp(GetString, NullStr)==0)//input nothing
        ShowWarning("PLEASE INPUT A NAME.");
    else
    {
        if((pFsJpeg->gifsState == FS_STATE_INIT) && (pFsJpeg->ControlArea == CNT_AREA_NEWBUTTON))
            CreateDir();
        else if((pFsJpeg->gifsState == FS_STATE_INIT) && (pFsJpeg->ControlArea == CNT_AREA_RENAMEBUTTON))
            RenameFileDir();
    }

    FileModeGUI_Refresh();
    FileMode_DirList(pFsJpeg->dir_current);
    pFsJpeg->gifsFuncBtn = 0;
}
/****************************************************************************************/
void input_str_clear_variable(void)
{
    int i;
    for(i=0;i<8;i++)
       GetString[i]=' ';
    Str_Index_x=0;
    Str_Index_y=0;
    Exit_Enter_flag=0;
    Max_input_flag=0;
    Max_left_flag=0;
    input_xoffset=0;    
}
//End,New input table related functions.
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : input_page                                                           *
 *                                                                                       *
 *  Purposes      : Draw the input page after select the rename button                   *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void input_page(void)
{
    //#ifdef NEW_INPUT_MENU   
    BYTE *title_str2="INPUT NAME:";
    
    osd_init_periphGUI();
    
    osd_draw_region_rect(0, 0,   64*8, 40, COLOR_GREEN, 3);
    osd_draw_region_rect(0, 278, 64*8, 10, COLOR_GREEN, 3);
    
    //for test,marked by wangwei,2005-1-13 10:28
    /*if(KeyID == BUTTON_COPY)
	    osd_DrawRegionString(2, 1, title_str1, COLOR_YELLOW, COLOR_GREEN, FUNCTION_REGION);		
    else if(KeyID == BUTTON_RENAME)
	    osd_DrawRegionString(2, 1, title_str2, COLOR_YELLOW, COLOR_GREEN, FUNCTION_REGION);*/
    
    //for test,added by wangwei,2005-1-13 10:29
    osd_DrawRegionString(2, 1, title_str2, COLOR_YELLOW, COLOR_GREEN, FUNCTION_REGION);		

    osd_DrawRegionString(14, 1, " ", COLOR_DBLUE,COLOR_LBLUE, FUNCTION_REGION);
	SetOsdCol(FUNCTION_REGION, FUNCTION_REGION, 0,__palette4F(192,192, 192, 0xe0));//draw background of the region
    
    //init variable
    input_str_clear_variable();
    input_str_clear_HL();
    
    //HL first itemstr
    input_HL_ItemStr(0);
    
    //for IR U/D/L/R/Sel input str func setting,for test,marked by wangwei,2005-1-13 10:58
    //SetFullscrnCmdFuncPtr(input_str_func_up, input_str_func_down, input_str_func_left, input_str_func_right, input_str_func_select);
}
/****************************************************************************************\
 *                                                                                       *
 *                                                                                       *
 *                                           Buttons                                     *
 *                                                                                       *
 *                                                                                       *
\****************************************************************************************/
void ButtonCopy(void)
{
    Draw_File_Mode_Button();            
    FATCopy();       
    pFsJpeg->ControlArea = old_ControlArea;                      
    pFsJpeg->gifsFuncBtn = 0;                                     
}
/****************************************************************************************/
void ButtonDelete(void)
{
    printf("\n============ButtonDelete================\n");     
    Draw_File_Mode_Button();                
    FATDelete();            
    pFsJpeg->ControlArea = old_ControlArea;                                         
    pFsJpeg->gifsFuncBtn = 0;                                                        
}    
/****************************************************************************************/
void ButtonNew(void)
{
    printf("\n============ButtonNew================\n");     
    Draw_File_Mode_Button();                    
    full_scrn |= INPUT_TBL;
    input_page();
    pFsJpeg->gifsFuncBtn = 0;                
}  
/****************************************************************************************/
void ButtonRename(void)
{
    printf("\n============ButtonRename================\n");     
    Draw_File_Mode_Button();                    
    full_scrn |= INPUT_TBL;
    input_page();
    pFsJpeg->gifsFuncBtn = 0;                
}
/****************************************************************************************/
void ButtonFormat(void)
{
    printf("\n============ButtonFormat================\n");     
    Draw_File_Mode_Button();                    
    ShowWarning("FORMATING...");                       
    FSFormat();                  
    ShowWarning("FORMAT IS OK.");                                            
    pFsJpeg->gifsFuncBtn = 0;                                                           
}
/****************************************************************************************/
void ButtonCapacity(void)
{
    printf("\n============ButtonCapacity================\n");  
    Draw_File_Mode_Button();                    
    if(full_scrn & STRG_INFO)
    {
        full_scrn &= (~STRG_INFO);//for release the IR
        osd_init();
        ShowHL();
        ShowWarning(functionStr[5]);                
    }
    else
    {
        full_scrn |= STRG_INFO;
        //show USB & CARD information
        ShowCapacityInfo();
        ShowWarning("PRESS SELECT TO CANCEL");        
    }
    pFsJpeg->gifsFuncBtn = 0;            
}
/****************************************************************************************\
*                                                                                        *
*  Function Name : DrawProgressBarInit                                                   *
*                                                                                        *
*  Purposes      : Initialize draw process bar.                                          *
*                                                                                        *
*  Descriptions  : Initialize draw process bar. to clear the backgroud of the            *
*                  the process bar & draw the back rut of the process bar.               *
*                                                                                        *
*  Arguments     : (none)                                                                *
*                                                                                        *
*  Returns       : (none)                                                                *
*                                                                                        *
*  See also      :                                                                       *
*                                                                                        *
\****************************************************************************************/
void DrawProgressBarInit(void)
{
    //cover bottom buttons.
    FSGUI_FillFrameBuf(FS_BOTTOM_AREA_X_START, FS_BOTTOM_AREA_Y_START, FS_BOTTOM_AREA_X_SIZE, FS_BOTTOM_AREA_Y_SIZE, BK_GROUNDY, BK_CRCB);
    //draw character.
    strcpy(linebuf, "PROGRESS");
    FSGUI_ShowString(FS_BOTTOM_AREA_X_START + 15, FS_BOTTOM_AREA_Y_START + 14, linebuf, FS_FONTCOLOR_FILE_Y1, FS_FONTCOLOR_FILE_CrCb1);
    //draw process back rut. 
    DrawRect(FS_BOTTOM_AREA_X_START + 90, FS_BOTTOM_AREA_Y_START + 13, FS_BOTTOM_AREA_X_SIZE - 101, FS_BOTTOM_AREA_Y_SIZE - 35, 1, BK_GROUNDY, BK_CRCB);
    //draw process back bar.
    int i;
    for(i=0;i<192;i+=4)
        FSGUI_FillFrameBuf(FS_BOTTOM_AREA_X_START + 94 + i, FS_BOTTOM_AREA_Y_START + 17, 3, FS_BOTTOM_AREA_Y_SIZE - 42, RGB2Y(0,0,0), RGB2CrCb(0,0,0));
}
/****************************************************************************************\
*                                                                                        *
*  Function Name : Refresh                                                               *
*                                                                                        *
*  Purposes      : Draw process bar.                                                     *
*                                                                                        *
*  Descriptions  : Draw process bar.                                                     *
*                                                                                        *
*  Arguments     :                                                                       *
*                  copy_process : The percentage of copying action that have been        *
*                                 already completed, ranges from 0 to 100.               *
*                                                                                        *
*  Returns       : (none)                                                                *
*                                                                                        *
*  See also      :                                                                       *
*                                                                                        *
\****************************************************************************************/
void Refresh(BYTE copy_process)
{
    int i;
    if(copy_process<=100)  
        {
            psprintf(linebuf, "COPYING FILE[%d%s]", copy_process,"%");   
            //FSGUI_UpdateInfoArea(linebuf);
            //draw process.
            for(i=0;i<copy_process*2-8;i+=4){
                FSGUI_FillFrameBuf(FS_BOTTOM_AREA_X_START + 94 + i, FS_BOTTOM_AREA_Y_START + 17, 3, FS_BOTTOM_AREA_Y_SIZE - 42, RGB2Y(45,84,229), RGB2CrCb(45,84,229));
                FSGUI_FillFrameBuf(FS_BOTTOM_AREA_X_START + 94 + i, FS_BOTTOM_AREA_Y_START + 21, 3, FS_BOTTOM_AREA_Y_SIZE - 46, RGB2Y(20,47,149), RGB2CrCb(20,47,149));
            }
        }
        if(copy_process >= 100)
        {
            psprintf(linebuf, "COPYING FILE[100%s]", "%");
            //lijd for updata copy file name 2004-11-16 20:26
            delay_srv_10ms(100);
            //FSGUI_UpdateInfoArea(linebuf);	 
            //FSGUI_UpdateInfoArea(linebuf);
            FSGUI_FillFrameBuf(FS_BOTTOM_AREA_X_START, FS_BOTTOM_AREA_Y_START,FS_BOTTOM_AREA_X_SIZE, FS_BOTTOM_AREA_Y_SIZE, BK_GROUNDY, BK_CRCB);   // lijd 2004-11-16 14:52
        }
}
/****************************************************************************************/
#endif//FILE_MODE_WRITE


