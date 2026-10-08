#ifndef __FONT_UNICODE_H
#define __FONT_UNICODE_H


#include "config.h"
#include "regmap.h"
#include "global.h"

#include "FontInterface.h"
#include "memmap0.h"
///////////////////////////////////////////////////////////////////////////////

#define LANG_KOREAN_INCLUDE//LANG_CHINESE_TRAD_INCLUDE 
#define	NLS_INCLUDE			1

/*
LANG_KOREAN_INCLUDE			// Korean KSC 5601
LANG_KOREAN_EXT_INCLUDE		// Korean KSC 5601 and Extended Korean code
LANG_CHINESE_INCLUDE		// Chinese Simplified same as LANG_CHINESE_SIMP_INCLUDE
LANG_CHINESE_SIMP_INCLUDE	// Chinese Simplified
LANG_CHINESE_TRAD_INCLUDE	// Chinese Traditional
LANG_JAPANESE_INCLUDE		// Japanese JIS X208
LANG_ENGLISH_INCLUDE		// English
*/
///////////////////////////////////////////////////////////////////////////////

#define CP_437      437     // MS-DOS United States 
//#define CP_737      737     // Greek
//#define CP_775      775     // Baltic 
//#define CP_850      850     // MS-DOS Multilingual (Latin I) 
//#define CP_852      852     // MS-DOS Slavic (Latin II) 
//#define CP_855      855     // IBM Cyrillic (primarily Russian) 
//#define CP_857      857     // IBM Turkish 
//#define CP_860      860     // MS-DOS Portuguese 
//#define CP_861      861     // MS-DOS Icelandic 
//#define CP_862      862     // Hebrew 
//#define CP_863      863     // MS-DOS Canadian-French 
//#define CP_864      864     // Arabic 
//#define CP_865      865     // MS-DOS Nordic 
//#define CP_866      866     // MS-DOS Russian (former USSR) 
//#define CP_869      869     // IBM Modern Greek 
//#define CP_874      874     // Thai 
#define CP_932      3     // Japanese
#define CP_936      2     // Chinese (PRC, Singapore) 
#define CP_949      1     // Korean 
#define CP_950      0     // Chinese (Taiwan Region; Hong Kong SAR, PRC)  

// Locale code
#define CP_ENGLISH          CP_437
#define CP_JAPANESE         CP_932
#define CP_CHINESE          CP_936
#define CP_KOREAN           CP_949

// Chinese Simplified and Traditional
#define CP_CHINESE_SIMP     CP_936
#define CP_CHINESE_TRAD     CP_950

///////////////////////////////////////////////////////////////////////////////

#define UNKNOWN_ANSICODE    '?'
#define UNKNOWN_UNICODE     0xff1f			// full with '?'

///////////////////////////////////////////////////////////////////////////////

//typedef UINT16 UINT16;

extern int NLS_nCurCodePage;
typedef int (*Ansi2Uni)(unsigned char *ansi, UINT16 *uni);
#if defined(UNI2ANSI_INCLUDE)
typedef int (*Uni2Ansi)(UINT16 uni, unsigned char *ansi);
#endif


void    InitNLS			(void);
int     SetCodePage     (int nCodePage);
int     GetCodePage		(void);

UINT32  uni_subtitle_language;
Ansi2Uni    char2uni_translation;

//typedef	int	(*ifunc_t)(unsigned char *ansi, UINT16 *uni);
//ifunc_t char2uni_translation;

////////////////////
#define     UINCODE_FONT_WIDTH  (16)
#define     UINCODE_FONT_HEIGHT (16)
////////////////////
extern  UINT32  unicode_strlen(const UINT16 *pStr);
extern  UINT32  unicode_strlen_for_ascii(const UINT8 *pStr);
extern  UINT32  unicode_strcpy(UINT16 *des, const UINT16 *src);
extern  UINT32  unicode_strcat(UINT16 *des, const UINT16 *src);

extern  UINT32 unicode_LFN_strlen(UINT16 *filename, UINT8 LFN_uni_bytes);
extern  UINT32  native_2_unicode(const unsigned char *src, UINT16 *des);

extern  void    show_fsGUI_uni_string( UINT16 x, UINT16 y, const UINT16 *pStr, BYTE uiY, UINT16 uiCbCr, UINT8 uiMode );
extern  void    show_fsGUI_native_string( UINT16 x, UINT16 y, const UINT8 *pStr, BYTE uiY, UINT16 uiCbCr, UINT8 uiMode );
extern  void    show_osd_uni_string( int x, int y, const UINT16 *s, int strlen , BYTE fontcolor, BYTE region );
extern  void    show_OSD_native_string( UINT16 xstart, UINT16 ystart, const UINT8 *pStr, BYTE fontcolor, BYTE region );
extern  void    show_osd_uni_text(const char *p,  UINT16 size);

extern  int     char2uni_cp950(unsigned char *ansi, UINT16 *uni);
extern  int     char2uni_cp949(unsigned char *ansi, UINT16 *uni);
extern  int     char2uni_cp932(unsigned char *ansi, UINT16 *uni);
extern  int     char2uni_cp936(unsigned char *ansi, UINT16 *uni);
//UINT32      GetUnicodeBmp( const UINT16 *pCode, const UINT8 **pBmp );

#endif

