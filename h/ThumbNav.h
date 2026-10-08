#ifndef __THUMBNAV_H
#define __THUMBNAV_H

#include "types.h"

// The breaking reason in JpgIsIRBreak() called by Jpg_Main().
int g_nBreakReason;

// set global variables in this files.
void SetGlobalVariables(void);

// show thumbnail's file name and size on menu's left-top corner.
void ShowThumbnailInfo(void);

// Display thumbnail selection menu.
void DisplayMenu(void);

// Draw a rectangle frame at a specific position with specific color.
void DrawFrame(int nXpos, int nYpos, int nWidth, int nHeight, UINT16 nLineWidth, UINT16 nColorY, UINT16 nColorCrCb);

// return the index of iso9660_file by giving the index of JPEG files
UINT16 GetIndexFrom9660Array(UINT16 nIndex);

// set related global variables according to current g_nThumbnailIndex 
void SetVariableFromThumbIndex(void);

// proceed UP button
UINT32 NavCmdUp(void);

// proceed DOWN button
UINT32 NavCmdDown(void);

// proceed LEFT button
UINT32 NavCmdLeft(void);

// proceed RIGHT button
UINT32 NavCmdRight(void);

// goto one one page which is nPageOffset away from current page.
// we often set nPageOffset = 1 to deal with CMD_FUNC_NEXT and PREV.
// nDirection = 0 means NEXT; 1 means PREVIOUS.
void GotoPage(UINT16 nPageOffset, int nDirection);

// Callback function for Thumbnail selection menu
UINT32 ThumbSelectCallback(UINT32 func);

#ifdef THUMBNAIL_BMP_GUI
void Thumbnail_Draw3DFrames(void);
void Thumbnail_Clear3DFrames(void);
#endif

#endif //__THUMBNAV_H

