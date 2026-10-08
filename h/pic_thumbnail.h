#ifndef __JPEG_THUMBNAIL_H
#define __JPEG_THUMBNAIL_H

#include "global.h"

enum
{
    CLEAR_FRAME =0, 
    DRAW_FRAME =1,
};

#define LINE_HEIGHT         4
#define LINE_GAP            64


// screen size
#define THUMBNAIL_SCREEN_WIDTH        720
#define	THUMBNAIL_SCREEN_HEIGHT       576

// thumbnail size
//#define THUMBNAIL_WIDTH     144     //the width should be 8X, Jeff 20030502
//#define THUMBNAIL_HEIGHT    100

//most thumbnail size in Exif is 160*120, Jeff 20030820
#define THUMBNAIL_WIDTH     160
#define THUMBNAIL_HEIGHT    120

// thumbnail amount in a page
#define THUMBNAIL_IN_ROW       3
#define THUMBNAIL_IN_COLUMN    2
#define THUMBNAIL_IN_PAGE      ((THUMBNAIL_IN_ROW) * (THUMBNAIL_IN_COLUMN))

#define THUMBNAIL_H_GAP     48
#define THUMBNAIL_V_GAP     48

#define THUMBNAIL_X_START   (((THUMBNAIL_SCREEN_WIDTH) - (THUMBNAIL_WIDTH) * (THUMBNAIL_IN_ROW) - (THUMBNAIL_H_GAP) * ((THUMBNAIL_IN_ROW) - 1)) / 2)
#define THUMBNAIL_Y_START   (((THUMBNAIL_SCREEN_HEIGHT) - (THUMBNAIL_HEIGHT) * (THUMBNAIL_IN_COLUMN) - (THUMBNAIL_V_GAP) * ((THUMBNAIL_IN_COLUMN) - 1)) / 2)

// screen size
#define SCREEN_WIDTH        THUMBNAIL_SCREEN_WIDTH
#define	SCREEN_HEIGHT       THUMBNAIL_SCREEN_HEIGHT

// thumbnail amount in a page
#define AMOUNT_IN_ROW       3
#define AMOUNT_IN_COLUMN    2
#define AMOUNT_IN_PAGE      ((AMOUNT_IN_ROW) * (AMOUNT_IN_COLUMN))

// the position of the first thumbnail's left-top corner
#define X_START             (((SCREEN_WIDTH) - (THUMBNAIL_WIDTH) * (AMOUNT_IN_ROW) - (THUMBNAIL_H_GAP) * ((AMOUNT_IN_ROW) - 1)) / 2)
#define Y_START             (((SCREEN_HEIGHT) - (THUMBNAIL_HEIGHT) * (AMOUNT_IN_COLUMN) - (THUMBNAIL_V_GAP) * ((AMOUNT_IN_COLUMN) - 1)) / 2)


#ifdef INDIGO_STYLE_FSGUI
#define THUMBNAIL_BG_WID				720	
#define THUMBNAIL_BG_HEI				576	
#define THUMBNAIL_BG_UP_RECT_HEI		65
#define THUMBNAIL_BG_DOWN_RECT_HEI		70
#define THUMBNAIL_BG_MIDDLE_RECT_HEI	(THUMBNAIL_BG_HEI-THUMBNAIL_BG_UP_RECT_HEI-THUMBNAIL_BG_DOWN_RECT_HEI)
#endif

#ifdef INDIGO_STYLE_FSGUI
	#define THUMBNAIL_OUT_FRAM_WIDTH    4
#else
	#define THUMBNAIL_OUT_FRAM_WIDTH    2
#endif
//=================================================================================
//thumbnail related functions
//=================================================================================

// proceed UP button
extern UINT32 Thumbnail_NavCmdUp(void);

// proceed DOWN button
extern UINT32 Thumbnail_NavCmdDown(void);

// proceed LEFT button
extern UINT32 Thumbnail_NavCmdLeft(void);

// proceed RIGHT button
extern UINT32 Thumbnail_NavCmdRight(void);

// goto one one page which is nPageOffset away from current page
extern UINT32 Thumbnail_GotoPage(UINT16 nPageOffset, UINT8 direction);

// Draw a rectangle frame at a specific position with specific color
//extern void Thumbnail_DrawFrame(int nXpos, int nYpos, int nWidth, int nHeight, UINT16 nLineWidth, UINT16 nColorY, UINT16 nColorCrCb);
extern void Thumbnail_DrawFrame(UINT32 Is_drawing, UINT8 nIndex);

// set related global variables according to current g_nThumbnailIndex 
extern void Thumbnail_setFsVariables(void);

// reset thumbnail variables
extern void Thumbnail_ResetVariables(void);

// return the index of iso9660_file by giving the index of JPEG files
extern UINT16 GetIndexFrom9660Array(UINT16 nIndex);

extern UINT32 Thumbnail_IsTheLastPage(void);

extern UINT32 Thumbnail_IsTheFirstPage(void);

extern UINT32 Thumbnail_IsTheLastFile(UINT32 thumbIndex);

extern UINT32 Thumbnail_IsTheFirstFile(UINT32 thumbIndex);

extern UINT32 Thumbnail_IsIndexValid(UINT32 thumbIndex);

#ifdef INDIGO_STYLE_FSGUI
extern void Thumbnail_DrawINDIGOBg(void);	
#else
extern void Thumbnail_DrawBg(void);
#endif

extern void Thumbnail_DrawPicInfo(UINT32 nIndex);

extern UINT16 Thumbnail_GetIndexFrom9660Array(UINT16 nIndex);
//=================================================================================
//other related functions
//=================================================================================

extern void FSGUI_JpgUpdateOSD(void);
extern void FSGUI_FillFrameBuf(int x, int y, int xSize, int ySize, UINT16 color_Y, UINT16 color_CrCb);
extern void FSGUI_FileSelect(int iSelect);

#endif //__THUMBNAV_H

