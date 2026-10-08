//
// fsGUI.h
//
//      fs9660-GUI module internal include
//
// notes:
//
// history:
//  2002/02/26  : create
//  2005/09/12 yltseng, Add new structure for font
//

#ifndef __FS_GUI_H
#define __FS_GUI_H

//common FS GUI parts

#include "fsGUI1.h"

extern BYTE JPEG_Preview_drawed;

//2006-06-02, mimitsai add for HD ui.move to fsGUIArea.c
extern const BTNAREA Rect[];
extern const BTNAREA fsArea[];

//UINT16  file_array[PER_PAGE];   	//store file index of iso9660_file[index], PER_PAGE defined in fsGUIx.h
//UINT16  dir_array[PER_PAGE];		//store file index of iso9660_dir[index]
void PollingJpgVfd();//wanghaoying 2003-8-12 15:12
void reset_zoom_state(void);
void return_menu(void);
void copy_ref1_frame_mpg2gp(void);
void init_pic_cd_first_play(void);
void init_hw_gp_md(void);
void set_dsp_codec_addr(int jpeg);
//FS GUI utilitiy function
//void    FSShowChar_Bfm(UINT16 x, UINT16 y, BYTE c, BYTE iY, UINT16 iCbCr);
void    FSGUI_ShowChar(BYTE vid, int x, int y, BYTE c, BYTE iY, UINT16 iCbCr); //Jeff 20020823
void    FSGUI_ShowChar_SR(int x, int y, BYTE c, BYTE iY, UINT16 iCbCr);
void    FSGUI_ShowString(int x, int y, const UINT8 *s, BYTE iY, UINT16 iCbCr);

#define EnlargeFontSizeToDouble( pDest, pSrc, uiWidth, uiHeight )   EnlargeFontSize( pDest, pSrc, uiWidth, uiHeight, 2, 2 )
extern void EnlargeFontSize( UINT8 *pDest, const UINT8 *pSrc, BYTE uiWidth, BYTE uiHeight, BYTE uiScaleX, BYTE uiScaleY );
extern void ResampleWidthFrom12PixelTo16Pixel( UINT8* pDest, const UINT8* pSrc, UINT32 uiHeight );

#ifdef FS_BMP_GUI
void FSGUI_ShowLittleString(int x, int y, const char *s, BYTE iY, UINT16 iCbCr);
void FSGUI_ShowLittleChar(BYTE vid, int x, int y, BYTE c, BYTE iY, UINT16 iCbCr); 
#endif
//void    FSGUI_ShowImage(BYTE* MapArray, int xStart, int yStart, int width, int height);
void    FSGUI_FillFrameBuf(int x,int y, int xSize,int ySize,UINT16 color_Y,UINT16 color_CrCb);
void    FSGUI_ReplaceFrameBuf(int x,int y, int xSize,int ySize,UINT16 replace_Y,UINT16 replace_CrCb,UINT16 color_Y,UINT16 color_CrCb);

void    FSGUI_RotateDiscIcon(int phase);
void    FSGUI_FlashFileIcon(int on);

//customize FS GUI parts
void    FSGUI_Init();                                   //initialize all FSGUI interal variables
void    FSGUI_Menu();                                   //draw main menu
void    FSGUI_UpdateInfoArea(BYTE* strInfo);            //show strInfo to information area(file name or others)
void    FSGUI_JpgUpdateOSD(void);                       //get JPEG current track to OSD display
void    FSGUI_Shuffle();                                //do SHUFFLE GUI
#ifdef SHUFFLE_ACCOMPLISH_BY_ARITHMETIC
void    FSGUI_Shuffle_New();
void    FSGUI_Shuffle_Next();
void    FSGUI_Shuffle_Prev();
#endif
void    FSGUI_ProgSelect(UINT16 index);                 //do PROGRAM GUI
void    FSGUI_Refresh(void);                            //refresh all GUI
void    FSGUI_Return2Menu(void);                        //return 2 main menu
void    FSGUI_CookFileItem(BYTE iItem);                 //do select file index GUI
void    FSGUI_FileSelect(int iSelect);                //do select file index job
int     FSGUI_Select(int iSelect);                      //do select file index job
int     FSGUI_GetDispTrack();                           //get current track info for OSD disp
void    FSGUI_2Last();                                  //locate to last dir and last file item
int     FSGUI_PreChangeDir(UINT16 *iDir,UINT16 iDirect);             //based on fsnav_dir_now to do directory chage(iDirect=0->next, 1->previous)
int     FSGUI_PreFindDir(UINT16 *iDir,UINT16 iDirect);      //find the next or prev directory,panxing for yuxing,2002-4-11(iDirect=0->next, 1->previous)
int     FSGUI_NormalNext();                             //normal to next item
int     FSGUI_NormalPrev();                             //normal to previous item
void    FSGUI_Stop();                                   //do GUI stop status
void    FSGUI_JpgPreview();                             //show JPEG in preview mode
//void    FSGUI_JPGPrevClr();                             //clear JPEG preview area
UINT32  FSGUI_CmdEnter();                               //got "ENTER"(SELECT) command from FSNAV
UINT32  FSGUI_CmdUp();                                  //got "UP" command from FSNAV
UINT32  FSGUI_CmdDown();                                //got "DOWN" command from FSNAV
UINT32  FSGUI_CmdLeft();                                //got "LEFT" command from FSNAV
UINT32  FSGUI_CmdRight();                               //got "RIGHT" command from FSNAV
UINT32  FSGUI_CmdPlay();                                //got "PLAY" button-command from FSNAV

UINT32  FSGUI_IsSelectable();                           //check whether it is selectable now
UINT16 antiAnchorDir(int iDir);
UINT16 AnchorDir(int iSeq);
UINT16 AnchorFile(int iSeq);	// return the index of iso9660_file by giving the index of a specified format
void Will2Playing(void);
void Playing2Will(void);
void Restore2PlayingFile(void);
void Restore2PlayingDir(void);
void ClearJpegPreviewBg(void);

void FSShowDirIcon(void);        
void ShowFileIcon(void);
void DirList();
void FileList(void);
void CalcDirNow(UINT16 *iDir);
int  PrepareForChangeFilePage(UINT16 iPage, UINT16 iSpecialTrk,UINT16 iDirect);

//extern function could be used
extern int    Jpg_Main(UINT32 msf, UINT32 len, UINT16 xStart, UINT16 yStart, UINT16 xWidth, UINT16 yHeight);
extern void   JPGBreak();
extern void   _JPGBreak();

#ifdef  FSGUI_FONTFRAME	//suxin add 2005-10-13
    extern void FrameBuf_DrawFontFrame( BYTE video_buf, const BYTE* bmp, coordinate *start, UINT32 FontColor, UINT32 FrameColor);
#endif

#if defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)
	//2006-06-02, mimitsai add for HD ui.
	void ClearRectArea(BTNAREA  Rect, UINT16 RectColorStep, UINT8 Y_1, UINT8 Y_2, UINT16 CbCr,int iIndex,int iItem);
	void DrawRectCorner(BTNAREA  Rect, int CornerRad,  BYTE updown, UINT8 step, BYTE Y_1, BYTE Y_2, UINT16 CbCr);
#elif defined (FS_BMP_GUI)
	void DrawRectCorner(BTNAREA  Rect, int CornerRad,  BYTE updown, UINT8 step, UINT16 RegionColor_C);
#endif

#ifdef INDIGO_STYLE_FSGUI
	void DrawVarientRect(BTNAREA Rect, YUV_COLOR stColor1, YUV_COLOR stColor2, int direction);
#endif

extern void ShowCurrentFilePlaying();

#endif

