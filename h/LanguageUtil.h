#ifndef _LANGUAGE_UTIL_H_
#define _LANGUAGE_UTIL_H_

// 2005/08/29 yltseng, modify header declaration to fit preprocessor define
// 2005/09/12 yltseng, Add new structure for font
#include "types.h"
#include "FontInterface.h"

    #ifdef SUPPORT_FONT_UTIL

extern void langInitSupportedFont();
extern void langGetScale( UINT8* pScaleX, UINT8* pScaleY );
#define langGetSupportedFontNum()           ftGetSupportedFontNum()
#define langSetFont( uiFontIdx )            ftSetFont( uiFontIdx )
#define langSetFontByType( enFontType )     ftSetFontByType( enFontType )
#define langNextFont()                      ftNextFont()
#define langIsInCharacterSet( pCode )       ftIsInCharacterSet( pCode )
#define langGetCharacterBmp( pCode, pBmp )  ftGetCharacterBmp( pCode, pBmp )
#define langGetFontType()                   ftGetFontType()
#define langGetFontSize( pWidth, pHeight )  ftGetFontSize( pWidth, pHeight )

    #else
    
#define langInitSupportedFont()
#define langGetScale(...)
#define langGetSupportedFontNum()           (0)
#define langSetFont(...)                    (FALSE)
#define langSetFontByType(...)              (FALSE)
#define langNextFont()                      (FALSE)
#define langIsInCharacterSet(...)           (FALSE)
#define langGetCharacterBmp(...)            (FONT_NOT_IN_RANGE)
#define langGetFontType()                   (FONT_NONE)
#define langGetFontSize(...)                (FALSE)

    #endif

// ******************************************************************* //
// *************************** Font Define *************************** //
// ******************************************************************* //
/*
    #define SUPPORT_FONT_UTIL
    #ifdef SUPPORT_FONT_UTIL
        //#define SUPPORT_MULTI_FONT_SWITCH

        //#define SUPPORT_FONT_COMPRESSED
        #ifdef SUPPORT_FONT_COMPRESSED

    // ***** Thai *****
    //#define SUPPORT_FONT_CP_874_COMPRESSED
    
    // ***** Shift JIS *****
    //#define SUPPORT_FONT_CP_932_COMPRESSED
    
    // ***** GB2312 *****
    //#define SUPPORT_FONT_CP_936_COMPRESSED
    
    // ***** GB2312 Common *****
    //#define SUPPORT_FONT_CP_936_COMMON_COMPRESSED
    
    // ***** Unified Hangul *****
    //#define SUPPORT_FONT_CP_949_COMPRESSED

    // ***** Unified Hangul Common *****
    //#define SUPPORT_FONT_CP_949_COMMON_COMPRESSED
        
    // ***** Big5 *****
    //#define SUPPORT_FONT_CP_950_COMPRESSED
    
    // ***** Big5 Common *****
    //#define SUPPORT_FONT_CP_950_COMMON_COMPRESSED
    
    // ***** Central Europe *****
    //#define SUPPORT_FONT_CP_1250_COMPRESSED
    
    // ***** Cyrillic *****
    //#define SUPPORT_FONT_CP_1251_COMPRESSED
    
    // ***** Latin I *****
    //#define SUPPORT_FONT_CP_1252_COMPRESSED
    
    // ***** Greek *****
    //#define SUPPORT_FONT_CP_1253_COMPRESSED
    
    // ***** Turkish *****
    //#define SUPPORT_FONT_CP_1254_COMPRESSED
    
    // ***** Hebrew *****
    //#define SUPPORT_FONT_CP_1255_COMPRESSED
    
    // ***** Arabic *****
    //#define SUPPORT_FONT_CP_1256_COMPRESSED
    
    // ***** Baltic *****
    //#define SUPPORT_FONT_CP_1257_COMPRESSED
    
    // ***** Vietnam *****
    //#define SUPPORT_FONT_CP_1258_COMPRESSED
    
    // ***** Latin I *****
    //#define SUPPORT_FONT_ISO_8859_1_COMPRESSED
    
    // ***** Latin II *****
    //#define SUPPORT_FONT_ISO_8859_2_COMPRESSED

    // ***** Cyrillic *****
    //#define SUPPORT_FONT_ISO_8859_5_COMPRESSED

    // ***** Arabic *****
    //#define SUPPORT_FONT_ISO_8859_6_COMPRESSED

    // ***** Greek *****
    //#define SUPPORT_FONT_ISO_8859_7_COMPRESSED

    // ***** Hebrew *****
    //#define SUPPORT_FONT_ISO_8859_8_COMPRESSED

    // ***** Turkish *****
    //#define SUPPORT_FONT_ISO_8859_9_COMPRESSED
    
        #endif  // SUPPORT_FONT_COMPRESSED
    
    // ***** Thai *****
    //#define SUPPORT_FONT_CP_874
    
    // ***** Shift JIS *****
    //#define SUPPORT_FONT_CP_932
    
    // ***** GB2312 *****
    //#define SUPPORT_FONT_CP_936
    
    // ***** GB2312 Common *****
    //#define SUPPORT_FONT_CP_936_COMMON
    
    // ***** Unified Hangul *****
    //#define SUPPORT_FONT_CP_949

    // ***** Unified Hangul Common *****
    //#define SUPPORT_FONT_CP_949_COMMON
        
    // ***** Big5 *****
    //#define SUPPORT_FONT_CP_950
    
    // ***** Big5 Common *****
    //#define SUPPORT_FONT_CP_950_COMMON
    
    // ***** Central Europe *****
    //#define SUPPORT_FONT_CP_1250
    
    // ***** Cyrillic *****
    //#define SUPPORT_FONT_CP_1251
    
    // ***** Latin I *****
    //#define SUPPORT_FONT_CP_1252
    
    // ***** Greek *****
    //#define SUPPORT_FONT_CP_1253
    
    // ***** Turkish *****
    //#define SUPPORT_FONT_CP_1254
    
    // ***** Hebrew *****
    //#define SUPPORT_FONT_CP_1255
    
    // ***** Arabic *****
    //#define SUPPORT_FONT_CP_1256
    
    // ***** Baltic *****
    //#define SUPPORT_FONT_CP_1257
    
    // ***** Vietnam *****
    //#define SUPPORT_FONT_CP_1258
    
    // ***** Latin I *****
    //#define SUPPORT_FONT_ISO_8859_1
    
    // ***** Latin II *****
    //#define SUPPORT_FONT_ISO_8859_2

    // ***** Cyrillic *****
    //#define SUPPORT_FONT_ISO_8859_5

    // ***** Arabic *****
    //#define SUPPORT_FONT_ISO_8859_6

    // ***** Greek *****
    //#define SUPPORT_FONT_ISO_8859_7

    // ***** Hebrew *****
    //#define SUPPORT_FONT_ISO_8859_8

    // ***** Turkish *****
    //#define SUPPORT_FONT_ISO_8859_9

    #endif // SUPPORT_FONT_UTIL
*/

#endif
