// 2005/08/29 yltseng, eliminate some functions
// 2005/09/12 yltseng, Add new structure for font
#include "user_init.h"

#ifdef SUPPORT_FONT_UTIL

#include "global.h"
#include "LanguageUtil.h"
#include "memmap.h"
#include "memmap0.h"
#include "func.h"

#ifndef DVDRELEASE
#define FONT_UTIL_DBG     1
#endif

#ifndef FONT_UTIL_DBG
#undef  printf
#undef  print_block
#define printf(f, a...)     do {} while (0)
#define print_block(x,y)    do {} while (0)
#endif

// **************************************************************************************** //
#ifndef FONT_DECOMPRESS_YA
    #define FONT_DECOMPRESS_YA      ( 0 )
    #define FONT_DECOMPRESS_SIZE    ( 0 )
    #warning "If you wanna use compressed font, you MUST define correct FONT_DECOMPRESS_YA & FONT_DECOMPRESS_SIZE"
#endif

const BYTE* DecompressFontCallback( const BYTE* pCompressedBmp )
{
#ifndef DVDRELEASE
    if( !pCompressedBmp )
        return NULL;
#endif

    BYTE*   pFontData       = (BYTE*)( SDRAM_BASE + ( FONT_DECOMPRESS_YA << 10 ) );
    int     iRes __UNUSED   = dsp3_decompress( pCompressedBmp, pFontData );



#ifndef DVDRELEASE
    #ifdef SUPPORT_FONT_COMPRESSED//Jack added 05/11/21.Only in SUPPORT_FONT_COMPRESSED need do it,otherwise system will set font error. 
    if( iRes <= 0 || iRes > ( FONT_DECOMPRESS_SIZE << 10 ) )
    #else
    if( iRes <= 0 /*|| iRes > ( FONT_DECOMPRESS_SIZE << 10 ) */)
    #endif
    {
        printf( "dsp3_decompress fail or font size too large\n" );
        return NULL;
    }
#endif

    return (const BYTE*) pFontData;
}

// **************************************************************************************** //
extern void langInitSupportedFont()
{
// ******************************************************************* //
// ********************* Windows CodePage Series ********************* //
// ******************************************************************* //
    
// ***** Thai *****
#ifdef SUPPORT_FONT_CP_874
    ftAddFont( FONT_CP_874, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_874_COMPRESSED
    ftAddFont( FONT_CP_874, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ***** Shift JIS *****
#ifdef SUPPORT_FONT_CP_932
    ftAddFont( FONT_CP_932, FONT_SIZE_16x16, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_932_COMPRESSED
    ftAddFont( FONT_CP_932, FONT_SIZE_16x16, FONT_COMPRESSED );
#endif

// ***** GB2312 *****
#ifdef SUPPORT_FONT_CP_936
    ftAddFont( FONT_CP_936, FONT_SIZE_12x12, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_936_COMPRESSED
    ftAddFont( FONT_CP_936, FONT_SIZE_12x12, FONT_COMPRESSED );
#endif

// ***** GB2312 Common *****
#ifdef SUPPORT_FONT_CP_936_COMMON
    ftAddFont( FONT_CP_936_COMMON, FONT_SIZE_12x12, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_936_COMMON_COMPRESSED
    ftAddFont( FONT_CP_936_COMMON, FONT_SIZE_12x12, FONT_COMPRESSED );
#endif

// ***** Unified Hangul *****
#ifdef SUPPORT_FONT_CP_949
    ftAddFont( FONT_CP_949, FONT_SIZE_16x16, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_949_COMPRESSED
    ftAddFont( FONT_CP_949, FONT_SIZE_16x16, FONT_COMPRESSED );
#endif

// ***** Unified Hangul Common *****
#ifdef SUPPORT_FONT_CP_949_COMMON
    ftAddFont( FONT_CP_949_COMMON, FONT_SIZE_16x16, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_949_COMMON_COMPRESSED
    ftAddFont( FONT_CP_949_COMMON, FONT_SIZE_16x16, FONT_COMPRESSED );
#endif

// ***** Big5 *****
#ifdef SUPPORT_FONT_CP_950
    ftAddFont( FONT_CP_950, FONT_SIZE_12x12, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_950_COMPRESSED
    ftAddFont( FONT_CP_950, FONT_SIZE_12x12, FONT_COMPRESSED );
#endif

// ***** Big5 Common *****
#ifdef SUPPORT_FONT_CP_950_COMMON
    ftAddFont( FONT_CP_950_COMMON, FONT_SIZE_12x12, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_950_COMMON_COMPRESSED
    ftAddFont( FONT_CP_950_COMMON, FONT_SIZE_12x12, FONT_COMPRESSED );
#endif

// ***** Central Europe *****
#ifdef SUPPORT_FONT_CP_1250
    ftAddFont( FONT_CP_1250, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_1250_COMPRESSED
    ftAddFont( FONT_CP_1250, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ***** Cyrillic *****
#ifdef SUPPORT_FONT_CP_1251
    ftAddFont( FONT_CP_1251, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_1251_COMPRESSED
    ftAddFont( FONT_CP_1251, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ***** Latin I *****
#ifdef SUPPORT_FONT_CP_1252
    ftAddFont( FONT_CP_1252, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_1252_COMPRESSED
    ftAddFont( FONT_CP_1252, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ***** Greek *****
#ifdef SUPPORT_FONT_CP_1253
    ftAddFont( FONT_CP_1253, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_1253_COMPRESSED
    ftAddFont( FONT_CP_1253, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ***** Turkish *****
#ifdef SUPPORT_FONT_CP_1254
    ftAddFont( FONT_CP_1254, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_1254_COMPRESSED
    ftAddFont( FONT_CP_1254, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ***** Hebrew *****
#ifdef SUPPORT_FONT_CP_1255
    ftAddFont( FONT_CP_1255, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_1255_COMPRESSED
    ftAddFont( FONT_CP_1255, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ***** Arabic *****
#ifdef SUPPORT_FONT_CP_1256
    ftAddFont( FONT_CP_1256, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_1256_COMPRESSED
    ftAddFont( FONT_CP_1256, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ***** Baltic *****
#ifdef SUPPORT_FONT_CP_1257
    ftAddFont( FONT_CP_1257, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_1257_COMPRESSED
    ftAddFont( FONT_CP_1257, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ***** Vietnam *****
#ifdef SUPPORT_FONT_CP_1258
    ftAddFont( FONT_CP_1258, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_CP_1258_COMPRESSED
    ftAddFont( FONT_CP_1258, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ******************************************************************* //
// ************************* ISO 8859 Series ************************* //
// ******************************************************************* //
    
// ***** Latin I *****
#ifdef SUPPORT_FONT_ISO_8859_1
    ftAddFont( FONT_ISO_8859_1, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_ISO_8859_1_COMPRESSED
    ftAddFont( FONT_ISO_8859_1, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ***** Latin II *****
#ifdef SUPPORT_FONT_ISO_8859_2
    ftAddFont( FONT_ISO_8859_2, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_ISO_8859_2_COMPRESSED
    ftAddFont( FONT_ISO_8859_2, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ***** Cyrillic *****
#ifdef SUPPORT_FONT_ISO_8859_5
    ftAddFont( FONT_ISO_8859_5, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_ISO_8859_5_COMPRESSED
    ftAddFont( FONT_ISO_8859_5, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ***** Arabic *****
#ifdef SUPPORT_FONT_ISO_8859_6
    ftAddFont( FONT_ISO_8859_6, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_ISO_8859_6_COMPRESSED
    ftAddFont( FONT_ISO_8859_6, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ***** Greek *****
#ifdef SUPPORT_FONT_ISO_8859_7
    ftAddFont( FONT_ISO_8859_7, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_ISO_8859_7_COMPRESSED
    ftAddFont( FONT_ISO_8859_7, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ***** Hebrew *****
#ifdef SUPPORT_FONT_ISO_8859_8
    ftAddFont( FONT_ISO_8859_8, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_ISO_8859_8_COMPRESSED
    ftAddFont( FONT_ISO_8859_8, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ***** Turkish *****
#ifdef SUPPORT_FONT_ISO_8859_9
    ftAddFont( FONT_ISO_8859_9, FONT_SIZE_12x24, FONT_NOT_COMPRESSED );
#endif

#ifdef SUPPORT_FONT_ISO_8859_9_COMPRESSED
    ftAddFont( FONT_ISO_8859_9, FONT_SIZE_12x24, FONT_COMPRESSED );
#endif

// ******************************************************************* //
// *********************** Font Initialization *********************** //
// ******************************************************************* //

    ftSetDecompressCallbackFunc( DecompressFontCallback );
    if( ftGetSupportedFontNum() )
        ftSetFont(0);
}

// **************************************************************************************** //

extern void langGetScale( UINT8* pScaleX, UINT8* pScaleY )
{
    (*pScaleX) = (*pScaleY) = 1;

    if( ftGetSupportedFontNum() )
    {
        UINT8 uiWidth, uiHeight;
        langGetFontSize( &uiWidth, &uiHeight );
        
        ENUM_FONT_TYPE  enType  = ftGetFontType();
        
        if( ( uiWidth == 12 ) && ( uiHeight == 12 ) &&
            ( enType >= FONT_CP_932 ) && (enType <= FONT_CP_950_COMMON ) )
        {
            (*pScaleX) = (*pScaleY) = 2;
        }
    }
}

// **************************************************************************************** //
#endif


