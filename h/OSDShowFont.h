// 2005/09/12 yltseng, Add new structure for font
#include "user_init.h"

#ifndef NEW_OSD_DRIVER

#include "global.h"
#include "func.h"

#ifdef OSD_FONT_API

#include "LanguageUtil.h"

#define EnlargeFontSizeToDouble( pDest, pSrc, uiWidth, uiHeight )   EnlargeFontSize( pDest, pSrc, uiWidth, uiHeight, 2, 2 )
extern void EnlargeFontSize( UINT8 *pDest, const UINT8 *pSrc, BYTE uiWidth, BYTE uiHeight, BYTE uiXRepeat, BYTE uiYRepeat );
extern void ResampleWidthFrom12PixelTo16Pixel( UINT8* pDest, const UINT8* pSrc, UINT32 uiHeight );
extern void osd_draw_gbfont(BYTE vid, const BYTE pFont[], int xStart, int yStart, unsigned int  fwidth, unsigned int  fhight, BYTE fontcolor,BYTE number);
extern const unsigned char LOWERCASE_FONT_BITMAP[];
extern void OSD_ShowString( int x, int y, const char *s, BYTE fontcolor, BYTE r );

#define FONT_LEN_EXTERNAL_TWO_BYTE  14
#define FONT_LEN_INTERNAL_OSD       9

#if defined(EUROPE_FOREIGN_LANGUAGES) || defined(MIDDLE_EUROPE_LANGUAGES) || defined (SUPPORT_TURKISH_LANGUAGES) || defined ( USE_CYRILLIC_FONT )
    #define FONT_LEN_EXTERNAL_ONE_BYTE  6
#else
    #define FONT_LEN_EXTERNAL_ONE_BYTE  FONT_LEN_INTERNAL_OSD
#endif

#endif //#ifdef OSD_FONT_API

#endif  // #ifndef NEW_OSD_DRIVER


