#ifndef _FONTINTERFACE_MACRO_H_
#define _FONTINTERFACE_MACRO_H_

#define FONT_DECLARATION( type, size )                                          \
extern const unsigned char FontBmp_##type##_##size##_FONT_NOT_COMPRESSED[];     \
extern const unsigned char FontBmp_##type##_##size##_FONT_COMPRESSED[];

#define FONT_CJK_DECLARATION( type )        \
extern const FontInfo FontInfo_##type;      \
FONT_DECLARATION( type, FONT_SIZE_12x12 )   \
FONT_DECLARATION( type, FONT_SIZE_16x16 )   \
FONT_DECLARATION( type, FONT_SIZE_20x24 )

#define FONT_OTHER_DECLARATION( type )      \
extern const FontInfo FontInfo_##type;      \
FONT_DECLARATION( type, FONT_SIZE_12x24 )   \
FONT_DECLARATION( type, FONT_SIZE_16x24 )   \
FONT_DECLARATION( type, FONT_SIZE_24x24 )

// ******************************************************************* //
// ********************* Windows CodePage Series ********************* //
// ******************************************************************* //

// ***** Thai *****
FONT_OTHER_DECLARATION( FONT_CP_874 )

// ***** Shift JIS *****
FONT_CJK_DECLARATION( FONT_CP_932 )

// ***** GB2312 *****
FONT_CJK_DECLARATION( FONT_CP_936 )

// ***** GB2312 Common *****
FONT_CJK_DECLARATION( FONT_CP_936_COMMON )

// ***** Unified Hangul *****
FONT_CJK_DECLARATION( FONT_CP_949 )

// ***** Unified Hangul Common *****
FONT_CJK_DECLARATION( FONT_CP_949_COMMON )

// ***** Big5 *****
FONT_CJK_DECLARATION( FONT_CP_950 )

// ***** Big5 Common *****
FONT_CJK_DECLARATION( FONT_CP_950_COMMON )

// ***** Central Europe *****
FONT_OTHER_DECLARATION( FONT_CP_1250 )

// ***** Cyrillic *****
FONT_OTHER_DECLARATION( FONT_CP_1251 )

// ***** Latin I *****
FONT_OTHER_DECLARATION( FONT_CP_1252 )

// ***** Greek *****
FONT_OTHER_DECLARATION( FONT_CP_1253 )

// ***** Turkish *****
FONT_OTHER_DECLARATION( FONT_CP_1254 )

// ***** Hebrew *****
FONT_OTHER_DECLARATION( FONT_CP_1255 )

// ***** Arabic *****
FONT_OTHER_DECLARATION( FONT_CP_1256 )

// ***** Baltic *****
FONT_OTHER_DECLARATION( FONT_CP_1257 )

// ***** Vietnam *****
FONT_OTHER_DECLARATION( FONT_CP_1258 )

// ******************************************************************* //
// ************************* ISO 8859 Series ************************* //
// ******************************************************************* //

// ***** Latin I *****
FONT_OTHER_DECLARATION( FONT_ISO_8859_1 )

// ***** Latin II *****
FONT_OTHER_DECLARATION( FONT_ISO_8859_2 )

// ***** Cyrillic *****
FONT_OTHER_DECLARATION( FONT_ISO_8859_5 )

// ***** Arabic *****
FONT_OTHER_DECLARATION( FONT_ISO_8859_6 )

// ***** Greek *****
FONT_OTHER_DECLARATION( FONT_ISO_8859_7 )

// ***** Hebrew *****
FONT_OTHER_DECLARATION( FONT_ISO_8859_8 )

// ***** Turkish *****
FONT_OTHER_DECLARATION( FONT_ISO_8859_9 )

#endif
