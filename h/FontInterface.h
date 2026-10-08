/**************************************************************************
 *                                                                        *
 *         Copyright (c) 2002 by Sunplus Technology Co., Ltd.             *
 *                                                                        *
 *  This software is copyrighted by and is the property of Sunplus        *
 *  Technology Co., Ltd. All rights are reserved by Sunplus Technology    *
 *  Co., Ltd. This software may only be used in accordance with the       *
 *  corresponding license agreement. Any unauthorized use, duplication,   *
 *  distribution, or disclosure of this software is expressly forbidden.  *
 *                                                                        *
 *  This Copyright notice MUST not be removed or modified without prior   *
 *  written consent of Sunplus Technology Co., Ltd.                       *
 *                                                                        *
 *  Sunplus Technology Co., Ltd. reserves the right to modify this        *
 *  software without notice.                                              *
 *                                                                        *
 *  Sunplus Technology Co., Ltd.                                          *
 *  19, Innovation First Road, Science-Based Industrial Park,             *
 *  Hsin-Chu, Taiwan, R.O.C.                                              *
 **************************************************************************/
/*--------------------------------------------------------------------------
|  File Name   :  FontInterface.h
|
|  Description :  Font Interface Header File
|
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2004/11/22      yltseng         Creating
|  0.2  2005/03/03      yltseng         Add Windows CodePage 1250
|  0.3  2005/03/10      yltseng         Modify function name
|  0.4  2005/08/29      yltseng         Fix bug & add function to get font size
|  0.5  2005/09/12      yltseng         Add new structure for font
|--------------------------------------------------------------------------------*/ 

#ifndef _FONT_INTERFACE_H_
#define _FONT_INTERFACE_H_

#include "types.h"

// **************************************************************************************** //
typedef enum
{
    FONT_NONE       = 0,

    FONT_CP_874,            // Thai
    FONT_CP_932,            // Shift JIS
    FONT_CP_936,            // GB 2312
    FONT_CP_936_COMMON,     // GB 2312 Common
    FONT_CP_949,            // Unified Hangul
    FONT_CP_949_COMMON,     // Unified Hangul Common( KSC 5601-1987 )
    FONT_CP_950,            // Big5
    FONT_CP_950_COMMON,     // Big5 Common
    FONT_CP_1250,           // Central Europe
    FONT_CP_1251,           // Cyrillic
    FONT_CP_1252,           // Latin I
    FONT_CP_1253,           // Greek
    FONT_CP_1254,           // Turkish
    FONT_CP_1255,           // Hebrew
    FONT_CP_1256,           // Arabic
    FONT_CP_1257,           // Baltic
    FONT_CP_1258,           // Vietnam
    
    FONT_ISO_8859_1,        // Latin I
    FONT_ISO_8859_2,        // Latin II
    FONT_ISO_8859_5,        // Cyrillic
    FONT_ISO_8859_6,        // Arabic
    FONT_ISO_8859_7,        // Greek
    FONT_ISO_8859_8,        // Hebrew
    FONT_ISO_8859_9,        // Turkish

} ENUM_FONT_TYPE;

typedef enum
{
    // only for Big5 / GB / Hanguel / Shift JIS
    FONT_SIZE_12x12,
    FONT_SIZE_16x16,
    FONT_SIZE_20x24,
    
    // only for Other fonts
    FONT_SIZE_12x24,
    FONT_SIZE_16x24,
    FONT_SIZE_24x24,

} ENUM_FONT_BMP_SIZE;

typedef enum
{
    FONT_NOT_IN_RANGE   = 0,
    FONT_ONE_BYTE,
    FONT_TWO_BYTE,
} ENUM_FONT_SIZE;

typedef enum
{
    FONT_NOT_COMPRESSED,
    FONT_COMPRESSED,
} ENUM_FONT_FORMAT;

// 2005/02/16 yltseng
typedef struct
{
	UINT16  uiUniCode               __attribute__ ((packed));
	UINT16  uiNative                __attribute__ ((packed));
} UNICODE_TO_NATIVE_ENTRY;

typedef struct
{
    // For single byte character, put range in aRange[1], and set aRange[0] to NULL
    const UINT8*                    aRange[2]                       __attribute__ ((packed));
    const UINT8*                    pTranslateTbl                   __attribute__ ((packed));
    const UNICODE_TO_NATIVE_ENTRY*  pUniToNtvTbl                    __attribute__ ((packed));
    UINT32                          uiUniToNtvTblNum                __attribute__ ((packed));
    UINT8                           aRangeNum[2]                    __attribute__ ((packed));
    ENUM_FONT_TYPE                  enType                          __attribute__ ((packed));
    UINT8                           uiTranslateTblNum               __attribute__ ((packed));
}   FontInfo;

// **************************************************************************************** //
#define         ftAddFont( type, size, compressed )   ftAddFontEx2( &FontInfo_##type, FontBmp_##type##_##size##_##compressed, compressed )
#define         ftAddFontEx( type, bmp, compressed )  ftAddFontEx2( &FontInfo_##type, bmp, compressed )
extern UINT32   ftAddFontEx2( const FontInfo* pFontInfo, const BYTE* pFontBmp, ENUM_FONT_FORMAT uiCompressed );

// **************************************************************************************** //
/**************************************************************************
 *  Function Name: ftSetFont                                              *
 *  Purposes:                                                             *
 *    Set current font's information and data buffer address.             *
 *  Descriptions:                                                         *
 *    Font info structure is defined in FontInterface.h. And it can be    *
 *    seperated from font's raw data. That is I can use same font info on *
 *    two different raw data. For example, I can use english's font info  *
 *    on 12x12 english raw data or on 24x24 english raw data.             *
 *  Arguments:                                                            *
 *    pFont    : Pointer to font's information, it describes this font's  *
 *    code range, font size ... etc.                                      *
 *    pFontData: Pointer to font's data buffer, and this buffer should    *
 *    contain bmp raw data of this font.                                  *
 *  Returns:                                                              *
 *    TRUE if success, FALSE otherwise.                                   *
 *  See also:                                                             *
 *    ftIsInCharacterSet, ftGetCharacterBmp, ftGetFontType                *
 **************************************************************************/
extern UINT32           ftSetFont( UINT32 uiFontIdx );


// **************************************************************************************** //
extern UINT32           ftSetFontByType( ENUM_FONT_TYPE enFontType );


// **************************************************************************************** //
extern UINT32           ftNextFont();


// **************************************************************************************** //
typedef const BYTE*     (*PFN_FONT_CALLBACK)( const BYTE* );
extern void             ftSetDecompressCallbackFunc( PFN_FONT_CALLBACK pFunc );


// **************************************************************************************** //
extern UINT32           ftGetSupportedFontNum();


// **************************************************************************************** //
/**************************************************************************
 *  Function Name: ftIsInCharacterSet                                     *
 *  Purposes:                                                             *
 *    Find out if this character is in current character set or not.      *
 *  Descriptions:                                                         *
 *    None                                                                *
 *  Arguments:                                                            *
 *    pCode: Pointer to character. Depending on different language, it may*
 *    point to 2 byte char(eg:Chinese) or 1 byte character(eg:English)    *
 *  Returns:                                                              *
 *    FONT_NOT_IN_RANGE: Not in current character set                     *
 *    FONT_ONE_BYTE    : In current character set, and is 1 byte character*
 *    FONT_TWO_BYTE    : In current character set, and is 2 byte character*
 *  See also:                                                             *
 *    ftSetFont, ftGetCharacterBmp, ftGetFontType                  *
 **************************************************************************/
extern UINT32           ftIsInCharacterSet( const UINT8* pCode );


/**************************************************************************
 *  Function Name: ftGetCharacterBmp                                      *
 *  Purposes:                                                             *
 *    Get input character's bmp raw data.                                 *
 *  Descriptions:                                                         *
 *    None                                                                *
 *  Arguments:                                                            *
 *    pCode: Pointer to character. Depending on different language, it may*
 *    point to 2 byte char(eg:Chinese) or 1 byte character(eg:English)    *
 *    pBmp : Pointer to pointer to bmp raw data, if pCode is in current   *
 *    character set, we will write UINT8* into pBmp, thus pBmp contains   *
 *    pointer to this character's bmp.                                    *
 *  Returns:                                                              *
 *    FONT_NOT_IN_RANGE: Not in current character set                     *
 *    FONT_ONE_BYTE    : In current character set, and is 1 byte character*
 *    FONT_TWO_BYTE    : In current character set, and is 2 byte character*
 *  See also:                                                             *
 *    ftSetFont, ftIsInCharacterSet, ftGetFontType                 *
 **************************************************************************/
extern UINT32           ftGetCharacterBmp( const UINT8* pCode, const UINT8** pBmp );


/**************************************************************************
 *  Function Name: ftGetFontType                                          *
 *  Purposes:                                                             *
 *    Get what current character set is.                                  *
 *  Descriptions:                                                         *
 *    None                                                                *
 *  Arguments:                                                            *
 *    None                                                                *
 *  Returns:                                                              *
 *    ENUM_FONT_TYPE, see FontInterface.h. It represents what current     *
 *    character set is.                                                   *
 *  See also:                                                             *
 *    ftSetFont, ftIsInCharacterSet, ftGetCharacterBmp             *
 **************************************************************************/
extern ENUM_FONT_TYPE   ftGetFontType();


/**************************************************************************
 *  Function Name: ftGetFontSize                                          *
 *  Purposes:                                                             *
 *    Get what current font's size( in pixel ).                           *
 *  Descriptions:                                                         *
 *    None                                                                *
 *  Arguments:                                                            *
 *    None                                                                *
 *  Returns:                                                              *
 *    TRUE if current font is set, FALSE otherwise.                       *
 *  See also:                                                             *
 *    ftSetFont, ftIsInCharacterSet, ftGetCharacterBmp                    *
 **************************************************************************/
extern UINT32   ftGetFontSize( UINT8* pWidth, UINT8* pHeight );


// 2005/02/16 yltseng
extern void ftUni2Native( unsigned char* pStr, int *pLen );

// **************************************************************************************** //
#include "FontInterface_Macro.inc"

// **************************************************************************************** //
#endif

