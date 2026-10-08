// 2005/08/29 yltseng, modify OSD_ShowChar to reduce memory usage
// 2005/09/12 yltseng, Add new structure for font
#include "user_init.h"

#ifndef NEW_OSD_DRIVER

#include "OSDShowFont.h"

#include "font_lowercase.c" //display lower letter ,suqiaoli add 2004-4-28

#define	 lowercase_table	LOWERCASE_FONT_BITMAP


#ifdef OSD_FONT_API     // 2005/02/16 yltseng

UINT32 OSD_ShowChar(int x, int y, BYTE c, BYTE fontcolor,BYTE r) 
{
	const BYTE  *pFont;
    BYTE        width, height;
    
    if( (c >= 'a') && (c <= 'z') )//litter case 
    { 
        int index   = 48 * (c - 97);
        width       = 16;
        height      = 24;
        pFont       = (const BYTE*) (&lowercase_table[index]);
    }
    
    else
    {
    	pFont   = get_font_entry(0,c);
        width   = pFont[0];
        height  = pFont[1];
        pFont  += 3;
    }

    osd_draw_gbfont( 0, (UINT8 *)pFont, x, y, width, height, fontcolor, r );
    
    return FONT_LEN_INTERNAL_OSD;
}

UINT32 OSD_FontShowChar(int x, int y, const BYTE* pBmp, BYTE fontcolor,BYTE r )
{   // 2004/09/23 yltseng
    UINT8   aFont1[ 24 ];
    UINT8   aFont2[ 96 ];    // 24 * 2 * 2

    ENUM_FONT_TYPE enType = langGetFontType();
    
    UINT8 uiWidth, uiHeight;
    if( !langGetFontSize( &uiWidth, &uiHeight ) )
        return 0;

    if( enType >= FONT_CP_932 && enType <= FONT_CP_950_COMMON )
    {
        if( uiWidth != 12 && uiHeight != 12 )
            return 0;

        ResampleWidthFrom12PixelTo16Pixel( aFont1, pBmp, 12 );
        EnlargeFontSizeToDouble( (UINT8 *)aFont2, (UINT8 *)aFont1, 16, 12 );
        osd_draw_gbfont( 0, (UINT8 *)aFont2, x, y, 32, 24, fontcolor, r );
        return FONT_LEN_EXTERNAL_TWO_BYTE;
    }
    else
    {
        if( ( uiWidth == 12 ) && ( uiHeight == 24 ) )
    {
        ResampleWidthFrom12PixelTo16Pixel( aFont2, pBmp, 24 );
        osd_draw_gbfont( 0, (UINT8 *)aFont2, x, y, 16, 24, fontcolor, r );
    }
        else if( ( uiWidth == 16 ) && ( uiHeight == 24 ) )
    {
        osd_draw_gbfont( 0, pBmp, x, y, 16, 24, fontcolor, r );//liweihua mod 2005-3-14
        }
        else
            return 0;
        
        return FONT_LEN_EXTERNAL_ONE_BYTE;
    }

    return 0;
    //wanghaoying add from 'else' sequence 2005-1-5 15:33
    //for this function did nothing while enType = FONT_NONE
    //such satuation will happen if undef SUPPORT_FONT_UTIL
    //NOTICE: I don't know wheather should return 0
}

void OSD_ShowString( int x, int y, const char *s, BYTE fontcolor, BYTE r )
{
    const BYTE* p   = s;

	while( *p )
	{
        const UINT8* pBmp   = NULL;
        UINT32 uiRtnVal     = langGetCharacterBmp( p, &pBmp );
        
        if( uiRtnVal != FONT_NOT_IN_RANGE )
        {
#ifdef SWITCH_SUB_DIRECTION//libing 2005-7-15 14:43
        	if(subtitle_ratate_flag)//libing
                x -= OSD_FontShowChar( x, y, pBmp, fontcolor, r );  // 2004/09/23 yltseng
	        else
#endif
            x += OSD_FontShowChar( x, y, pBmp, fontcolor, r );  // 2004/09/23 yltseng

            if( uiRtnVal == FONT_ONE_BYTE )
                p++;
            else 
                p += 2;
        }
        else
        {
		    BYTE    c   = *p;
            if ( (c < 32) || (c > 126) )
                c = '_';
#ifdef SWITCH_SUB_DIRECTION//libing 2005-7-15 14:43
			if(subtitle_ratate_flag){
				x -= OSD_ShowChar( x, y, c, fontcolor, r);
            }else	
#endif
            x += OSD_ShowChar( x, y, c, fontcolor, r);
            p++;
        }
#ifdef SWITCH_SUB_DIRECTION//libing 2005-7-15 14:43
		if(subtitle_ratate_flag)
		{
			if( x < 0) 
				break;
		}
		else
#endif
		{
    		if( x > region[r].osd_w ) 
    			break;
	    }
    }
}
   
#endif //#ifdef OSD_FONT_API

#endif  // #ifndef NEW_OSD_DRIVER

