/***********************************************************************
** fsGUI_new.h
**
**      structure define for FrameBuf_BmpUI.c
**
**
** 	Creator :zhaoyanhua
**	Date:    2004-6-3 9:40
************************************************************************/

#ifndef _FRAMEBUF_BMP_UI_H
#define  _FRAMEBUF_BMP_UI_H


typedef struct
{
    UINT16  uiXPos; //x start position
    UINT16  uiYPos; //y start position
    UINT16   uiXRepeat;//x axis repeat 
    UINT16   uiYRepeat;//y axis repeat
    UINT8   uiIndex; // index in bmp array
    UINT8   uiPalette;//palette index
} BITMAP_LAYOUT;


//color value is defined by RGB not YCbCr in palette. 
/*typedef struct
{
    UINT8   uiGreen;
    UINT8   uiBlue;
    UINT8   uiRed;
} RGB_COLOR;
*/

typedef struct
{
    UINT8   uiY;
    UINT16  uiCrCb;
} YCrCb_COLOR;

void FrameBuf_DrawRGBPixel(UINT16 xStart, UINT16 yStart, UINT8 Red, UINT8 Green, UINT8 Blue);
void FrameBuf_DrawBmp(UINT16 xStart, UINT16 yStart, const BYTE *bmp, const YCrCb_COLOR* Palette);
void FrameBuf_DrawBackGround(UINT16 xStart, UINT16 yStart, UINT16 iWidth, UINT16 iHeigth, const BYTE*bmp, const YCrCb_COLOR * Palette);
void FrameBuf_DrawLine(UINT16 xStart, UINT16 yStart, UINT16 xLen, UINT16 yLen, UINT16 ColorY, UINT16 ColorCrCb);
void FrameBuf_DrawRect(UINT16 xStart, UINT16 yStart, UINT16 xLen, UINT16 yLen, UINT16 ColorY, UINT16 ColorCrCb);


#endif //ifndef  _FRAMEBUF_BMP_UI_H


