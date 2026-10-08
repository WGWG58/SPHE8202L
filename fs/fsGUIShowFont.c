// 2005/09/12 yltseng, Add new structure for font
#ifndef _FSGUISHOWFONT_C_
#define _FSGUISHOWFONT_C_

#include "global.h"
#include "graph.h"
#include "fsGUI.h"
#include "LanguageUtil.h"

#ifdef FSGUI_FONTFRAME                //suxin add 2005-10-13
#include "osd_AppAPI.h"
extern void OSD_DrawFontFrame(UINT8 *pDest, UINT8 *pSrc, BYTE Width, BYTE Height,BYTE FrameWidth);
#endif

#ifdef SUPPORT_NATIVE_FSNAME // denghg add for  it call OSD function 2006-6-10 15:51
#include "osd_AppAPI.h"
#endif

// **************************************************************************************** //  
void EnlargeFontSize( UINT8 *pDest, const UINT8 *pSrc, BYTE uiWidth, BYTE uiHeight, BYTE uiScaleX, BYTE uiScaleY )
{
    UINT32 uiDestSize = ( uiWidth * uiHeight * uiScaleX * uiScaleY + 7 ) / 8;

    if( uiScaleX == 1 && uiScaleY == 1 )
    {
        memcpy( pDest, pSrc, uiDestSize );
        return;
    }
    
    memset( pDest, 0, uiDestSize );
    
    UINT32 x, y, i, j;
    UINT32 uiSrcOffset_Y;

    for( y = 0, uiSrcOffset_Y = 0; y < uiHeight;  y++, uiSrcOffset_Y += uiWidth )
    {
        for( j = 0; j < uiScaleY; j++ )
        {
            for( x = 0; x < uiWidth; x++ )
            {
                UINT8 uiBitVal = ( ( pSrc[ ( uiSrcOffset_Y + x ) / 8 ] >> ( 7 - ( uiSrcOffset_Y + x ) % 8 ) ) ) & 0x01;
                if( uiBitVal )
                {
                    for( i = 0; i < uiScaleX; i++ )
                    {
                        pDest[ ( ( y * uiScaleY + j )* uiWidth * uiScaleX + x * uiScaleX + i ) / 8 ] |= ( uiBitVal << ( 7 - ( ( ( y * uiScaleY + j )* uiWidth * uiScaleX + x * uiScaleX + i ) % 8 ) ) );
                    }
                }
            }
        }
    }
}

//*******************************************************************************//

typedef enum
{
    ENUM_DOWN_SAMPLING_RIGHT_UP_CORNER,
    ENUM_DOWN_SAMPLING_ALL,
} ENUM_SAMPLING_MODE;

void ReduceFontSize( UINT8 *pDest, const UINT8 *pSrc, BYTE uiWidth, BYTE uiHeight, BYTE uiScaleX, BYTE uiScaleY, ENUM_SAMPLING_MODE enSamplingMode )
{
    // Prepare value for width, height, size after resize
    UINT32 uiCntX           = uiWidth  / uiScaleX;
    UINT32 uiCntY           = uiHeight / uiScaleY;
    UINT32 uiDestSize       = ( uiCntX * uiCntY + 7 ) / 8;

    if( uiScaleX == 1 && uiScaleY == 1 )
    {
        memcpy( pDest, pSrc, uiDestSize );
        return;
    }
    memset( pDest, 0, uiDestSize );

    // Prepare value for sampling block
    UINT32 uiBlkStartX;
    UINT32 uiBlkStartY;
    UINT32 uiBlkSizeX;
    UINT32 uiBlkSizeY;
    //UINT32 uiBlkthreshold;

    if( enSamplingMode == ENUM_DOWN_SAMPLING_RIGHT_UP_CORNER )
    {
        uiBlkStartX     = uiScaleX - 1;
        uiBlkStartY     = 0;
        uiBlkSizeX      = uiScaleX;
        uiBlkSizeY      = 1;
        //uiBlkthreshold  = 1;
    }
    else// if( enSamplingMode == ENUM_DOWN_SAMPLING_ALL )
    {
        uiBlkStartX     = 0;
        uiBlkStartY     = 0;
        uiBlkSizeX      = uiScaleX;
        uiBlkSizeY      = uiScaleY;
        //uiBlkthreshold  = uiScaleX * uiScaleY / 2;
    }

    // Start sampling
    UINT32 i, j, m, n;
    UINT32 uiDestPixel  = 0;
    UINT32 uiSrcOffsetY = 0;
        
    for( j = 0; j < uiCntY; j++ )
    {
        UINT32 uiSrcOffsetX = 0;
        
        for( i = 0; i < uiCntX; i++ )
        {
            UINT32 uiPixelCnt = 0;

            for( n = uiBlkStartY; n < uiBlkSizeY; n++ )
            {            
                for( m = uiBlkStartX; m < uiBlkSizeX; m++ )
                {
                    UINT32  uiPos       = ( uiSrcOffsetY + n ) * uiWidth + uiSrcOffsetX + m;
                    UINT32  uiBitVal    = ( pSrc[ uiPos / 8 ] >> ( 7 - ( uiPos % 8 ) ) ) & 0x01;
                    if( uiBitVal )
                        uiPixelCnt++;
                }
            }
            
            if( uiPixelCnt )//>= uiBlkthreshold )
                pDest[ uiDestPixel / 8 ] |= ( 0x01 << ( 7 - ( uiDestPixel % 8 ) ) );
            
            uiDestPixel++;
            uiSrcOffsetX += uiScaleX;
        }

        uiSrcOffsetY += uiScaleY;
    }
}

// **************************************************************************************** //
void ResampleWidthFrom12PixelTo16Pixel( UINT8* pDest, const UINT8* pSrc, UINT32 uiHeight )
{
    UINT8 i = 0, uiToggle = 0;
    
    for( ; i < ( uiHeight << 1 ); i += 2 )
    {
        if( uiToggle )
        {
            pDest[ i     ] = ( ( pSrc[0] & 0x0f ) << 4 ) | ( ( pSrc[1] & 0xf0 ) >> 4 );
            pDest[ i + 1 ] = ( pSrc[1] & 0x0f ) << 4;
            pSrc += 2;
        }
        else
        {
            pDest[ i     ] = pSrc[0];
            pDest[ i + 1 ] = pSrc[1] & 0xf0;
            pSrc += 1;
        }

        uiToggle = !uiToggle;
    }
}

// **************************************************************************************** //

typedef struct {
    UINT8 ui_y;
    UINT16 ui_cbcr;
}YCbCrType;
typedef struct {
    YCbCrType font_color;
    YCbCrType frame_color;
}VppColor;    
/*
  * Function: FSGUI_DrawFontBmp()   
  * Purposes: Draw font bitmap to video frame buffer.                
  * Description: 
  *                 1. font bitmap format support  1, 2 bits for a pixel, but not odd bits
  *                 2. support to adjust the gap between fonts.
  *                 
  * Arguments: video_buf: indicate the video frame buffer . 
  *                   pbmp_size: the font bitmap size.
  *                   pbmp_offset: indicate the scope of bitmap for drawing.
  *                   pixel_size: indicate 1 pixel stand for how many bits.
  * Return: NO.
  * Create: robert.chang, 2006/05/16 
  * Modify: 
  */
void FSGUI_DrawFontBmp(BYTE video_buf, const coordinate *pstatr_loc, const BYTE *pbmp, const dimension *pbmp_size, 
                                    const DrawDimension *pbmp_offset, const VppColor *pcolor, UINT8 pixel_size)
{
    UINT32  i, j, bmp_loc;
    UINT16 bmp_width;
    UINT16 draw_height, draw_widht;
    UINT8 bmp_mask, max_pix_index_inbyte, bmp_pix2byte_shift, bmp_shift_uint_power;

    draw_widht = pbmp_offset->draw_dimension.x_length;
    draw_height = pbmp_offset->draw_dimension.y_length;
    bmp_width = pbmp_size->x_length;


    switch(pixel_size) {
        default:
        case 1:
            bmp_pix2byte_shift = 3;     // 2^3 = 8, so pixel num >> 3 = byte num;
            max_pix_index_inbyte = 0x07;
            bmp_mask =  0x01;
            bmp_shift_uint_power = 0;   // shift unit is 1 bit, the bmp_shift_uint_power =0. So 1<<0 = 1
            break;
        case 2:
            bmp_pix2byte_shift = 2;    // 2^2 = 4, and 1pixel = 2bits ,so pixel num >> 2 = byte num;
            max_pix_index_inbyte = 0x03;
            bmp_mask = 0x03;
            bmp_shift_uint_power = 1; // shift unit is 2 bit, the bmp_shift_uint_power =1. So 1<<1 = 2
            break;
    }    

    bmp_loc = (pbmp_offset->draw_start.y) * bmp_width + pbmp_offset->draw_start.x;
    
    for(j=0; j<draw_height; j++) {
        for(i=0; i<draw_widht; i++) {
            /*
                UINT8 uiBitVal = ( pFont[ uiPixelCnt / 8 ] >> ( 7 - ( uiPixelCnt % 8 ) ) ) & 0x01;
            */
            // shift_num = ( 7 - ( uiPixelCnt % 8 ) )
            UINT8 shift_num = ( (~(bmp_loc+i)) & max_pix_index_inbyte )<<bmp_shift_uint_power; 
            // uiBitVal = ( pFont[ uiPixelCnt / 8 ] >> shift_num ) & 0x01;
            UINT8 uiBitVal = ( pbmp[(bmp_loc+i)>>bmp_pix2byte_shift] >> shift_num ) & bmp_mask;
            if( uiBitVal )
            {
                UINT16 uiCoordX = pstatr_loc->x + i;
                UINT16 uiCoordY = pstatr_loc->y + j;
                UINT32 uiFrmLAddr = 0, uiFrmCAddr = 0;
                
                if( video_buf == 0 )
                {
                    uiFrmLAddr  = REF0_LUMA;
                    uiFrmCAddr  = REF0_CHROMA;
                }
                else if( video_buf == 1 )
                {
                    uiFrmLAddr  = REF1_LUMA;
                    uiFrmCAddr  = REF1_CHROMA;
                }
                else if( video_buf == 2 )
                {
                    uiFrmLAddr  = BIDIR_LUMA;
                    uiFrmCAddr  = BIDIR_CHROMA;
                }
                
                UINT8*  pFrmLAddr = (UINT8*) ( SDRAM_BASE + ( uiFrmLAddr << 10 ) + OFFSET_Y(uiCoordY) + SFF(uiCoordX) );
                UINT16* pFrmCAddr = (UINT16*)( SDRAM_BASE + ( uiFrmCAddr << 10 ) + OFFSET_C( (uiCoordY) >> 1 ) + 2 *( SFF(uiCoordX) >> 1 ) );

                if(pixel_size == 1) {
                    *pFrmLAddr  = pcolor->font_color.ui_y;
                        
                        //modified for font blotted problem on framebuf
                    if(uiCoordX%2==0)
                        *pFrmCAddr  = pcolor->font_color.ui_cbcr;
                }
                else {

                    *pFrmLAddr = (uiBitVal == 0x03) ? pcolor->font_color.ui_y : pcolor->frame_color.ui_y;
                    
                        //modified for font blotted problem on framebuf                    
                    if(uiCoordX%2==0)
                            *pFrmCAddr  = (uiBitVal == 0x03) ? pcolor->font_color.ui_cbcr : pcolor->frame_color.ui_cbcr;

                }                           
            }    
        }
        bmp_loc += bmp_width ;        
    }

}

// **************************************************************************************** //
void FSGUI_DrawMonoBitmap( BYTE video_buf, const BYTE* pFont, UINT16 x, UINT16 y, UINT16 uiWidth, UINT16 uiHeight, UINT8 uiY, UINT16 uiCbCr )
{
    UINT32  uiPixelCnt = 0;
    UINT32  i, j;

	for( j = 0; j < uiHeight; j++ )
	{
	    for( i = 0; i < uiWidth; i++ )
	    {
	        UINT8 uiBitVal = ( pFont[ uiPixelCnt / 8 ] >> ( 7 - ( uiPixelCnt % 8 ) ) ) & 0x01;
	        
	        if( uiBitVal )
	        {
	            UINT16 uiCoordX = x + i;
	            UINT16 uiCoordY = y + j;
                UINT32 uiFrmLAddr = 0, uiFrmCAddr = 0;
                
                if( video_buf == 0 )
                {
                    uiFrmLAddr  = REF0_LUMA;
                    uiFrmCAddr  = REF0_CHROMA;
                }
                else if( video_buf == 1 )
                {
                    uiFrmLAddr  = REF1_LUMA;
                    uiFrmCAddr  = REF1_CHROMA;
                }
                else if( video_buf == 2 )
                {
                    uiFrmLAddr  = BIDIR_LUMA;
                    uiFrmCAddr  = BIDIR_CHROMA;
                }
                
                UINT8*  pFrmLAddr = (UINT8*) ( SDRAM_BASE + ( uiFrmLAddr << 10 ) + OFFSET_Y(uiCoordY) + SFF(uiCoordX) );
                UINT16* pFrmCAddr = (UINT16*)( SDRAM_BASE + ( uiFrmCAddr << 10 ) + OFFSET_C( (uiCoordY) >> 1 ) + 2 *( SFF(uiCoordX) >> 1 ) );
                *pFrmLAddr  = uiY;
                
                //20060104, joshua modified for font blotted problem on framebuf
                if(uiCoordX%2==0)
                    *pFrmCAddr  = uiCbCr;
	        }

	        uiPixelCnt++;
	    }
    }
}

// **************************************************************************************** //
static UINT32 FSGUI_PreDrawBmp( BYTE video_buf, const BYTE* pFont, UINT16 x, UINT16 y, UINT16 uiWidth, UINT16 uiHeight, UINT8 uiY, UINT16 uiCbCr, UINT16 uiFitHeight, ENUM_SAMPLING_MODE enMode )
{
    #define FSJPEG_BUF_OFFSET  ( ( sizeof( FSJPEGDATA ) >> 2 ) << 2 )
    const UINT8*  pDestFont   = pFont;

    if( uiFitHeight )
    {
        if( uiHeight < uiFitHeight )
        {
            UINT32 uiScale = uiFitHeight / uiHeight;
            if( uiScale > 1 )
            {
                pDestFont = (const UINT8*) ( (UINT32)pFsJpeg + FSJPEG_BUF_OFFSET );
                EnlargeFontSize( (UINT8*) pDestFont, pFont, uiWidth, uiHeight, uiScale, uiScale );
                uiWidth     *= uiScale;
                uiHeight    *= uiScale;
            }
        }
        else
        {
            UINT32 uiScale = ( uiHeight + uiFitHeight - 1 ) / uiFitHeight;
            if( uiScale > 1 )
            {
                pDestFont = (const UINT8*) ( (UINT32)pFsJpeg + FSJPEG_BUF_OFFSET );
                ReduceFontSize( (UINT8*) pDestFont, pFont, uiWidth, uiHeight, uiScale, uiScale, enMode );
                uiWidth     /= uiScale;
                uiHeight    /= uiScale;
            }
        }       
    }

    coordinate start;
    dimension size;
    DrawDimension draw_offset;    
    VppColor color;
    start.x = x;
    start.y = y;

    #ifdef SUPPORT_NATIVE_FSNAME //denghg update for ADJ_FSGUI STRING whitespace , it will seen better 2006-6-13 14:15
    //#define FSGUI_CHAR_SPACEPIXEL 3 //new it is define in OSD_Appdraw PreFontDraw_Position function 2006-6-15 18:47
    UINT8 uiRealWidth = 0;
    UINT8  NoBGLeftwidth   = 0;
    FONTDATA fontP;    
    
    CntFontContent( pDestFont,uiWidth, uiHeight,&fontP);
    uiRealWidth = PreFontDraw_Position( (int*) &x, &fontP , uiWidth, &NoBGLeftwidth);
  
    #endif
    

#ifdef FSGUI_FONTFRAME
	const UINT8*  pFonttem;
	const UINT8*  pFonttmp1;
	pFonttem = (UINT8*) ( (UINT32)pFsJpeg + FSJPEG_BUF_OFFSET);

	UINT8 Amount;
	if(uiWidth%8 != 0)
	{
		#define FSJPEG_BUF_OFFSET  ( ( sizeof( FSJPEGDATA ) >> 2 ) << 2 )	
		OSD_AdjustFontWidth( (UINT8*) pFonttem, pDestFont, uiHeight, uiWidth);
   	    Amount = ((uiWidth+4)/8)*(uiHeight);
		uiWidth += 4;
	}                                             
    else
		Amount = (uiWidth/8)*(uiHeight); 

	pFonttmp1 = pFonttem;
	pFonttem = (UINT8*) ( (UINT32)pFsJpeg + FSJPEG_BUF_OFFSET+Amount);
	OSD_DrawFontFrame((UINT8*)pFonttem, (UINT8*)pFonttmp1, uiWidth, uiHeight, 1);  		

    size.x_length = pFonttem[0];
    size.y_length = pFonttem[1];
    draw_offset.draw_start.y = 0;
	draw_offset.draw_dimension.y_length = pFonttem[1];
    color.font_color.ui_y 		= 0xF1;
    color.font_color.ui_cbcr 	= 0x8A41;
    color.frame_color.ui_y 		= 0x67;
    color.frame_color.ui_cbcr 	= 0x807F;

	#define FONT_OUTLINE_WIDTH 1
    #ifdef FONT_WIDTH_ADJUSTMENT
	extern UINT8 RWid, LWid;
	CalcuteFontActualWidth((UINT8*)pFonttem, pFonttem[0], pFonttem[1], pFonttem[0], OSD_FORMAT_4COLOR);	

    draw_offset.draw_start.x = LWid;
    draw_offset.draw_dimension.x_length = (RWid-LWid+1);
    FSGUI_DrawFontBmp(video_buf, &start, (pFonttem+2), &size, &draw_offset, &color, 2);
	uiWidth = (RWid-LWid+1) - 3;
    #else
    draw_offset.draw_start.x = 0;
    draw_offset.draw_dimension.x_length = pFonttem[0];
    FSGUI_DrawFontBmp(video_buf, &start, (pFonttem+2), &size, &draw_offset, &color, 2);
	uiWidth = pFonttem[0] - 8 + 2*FONT_OUTLINE_WIDTH;
	#endif
#else

    size.x_length = uiWidth;
    size.y_length = uiHeight;
	draw_offset.draw_start.y = 0;
	draw_offset.draw_dimension.y_length = uiHeight;
    color.font_color.ui_y    = uiY;
    color.font_color.ui_cbcr = uiCbCr;
	#ifdef FONT_WIDTH_ADJUSTMENT       
	extern UINT8 RWid, LWid;
	CalcuteFontActualWidth((UINT8*)pDestFont, uiWidth, uiHeight, uiWidth, OSD_FORMAT_2COLOR);	
    draw_offset.draw_start.x = LWid;
    draw_offset.draw_dimension.x_length = (RWid-LWid+1);
    FSGUI_DrawFontBmp(video_buf, &start, pDestFont, &size, &draw_offset, &color, 1);
	uiWidth = (RWid-LWid+1);
	#else
    draw_offset.draw_start.x = 0;
    draw_offset.draw_dimension.x_length = uiWidth;
    FSGUI_DrawFontBmp(video_buf, &start, pDestFont, &size, &draw_offset, &color, 1);
	#endif

#endif
#ifndef SUPPORT_NATIVE_FSNAME
    return uiWidth;    
#else
    return uiRealWidth;
#endif
}

// **************************************************************************************** //
typedef struct
{
    UINT16 uiCharFitHeight;
    UINT16 uiMaxStringLength;
} FSGUI_FONT_DRAW_LIMITATION;

void FSGUI_ShowString_Ex( BYTE video_buf, UINT16 x, UINT16 y, const UINT8 *pStr, BYTE uiY, UINT16 uiCbCr, FSGUI_FONT_DRAW_LIMITATION* pLimit )
{
    #ifdef SUPPORT_DVB_PREVIEW_9FRAMES
    extern UINT8 dvb_preview_state;
	if( dvb_preview_state )
		video_buf = 2;
    #endif

    UINT16 uiCount              = 0;
    UINT16 uiCharFitHeight      = 0;
    UINT16 uiMaxStringLength    = 0xFFFF;
    if( pLimit )
    {
        uiCharFitHeight     = pLimit->uiCharFitHeight;
        uiMaxStringLength   = pLimit->uiMaxStringLength;
    }

    UINT8 uiWidth, uiHeight;    
    langGetFontSize( &uiWidth, &uiHeight );

 
   

	while( *pStr )
	{
        const UINT8* pBmp       = NULL;
        UINT32 uiRtnVal         = langGetCharacterBmp( pStr, &pBmp );
        ENUM_FONT_TYPE enType   = langGetFontType();
        
        
        if( ( uiRtnVal != FONT_NOT_IN_RANGE ) 
            #ifdef SUPPORT_NATIVE_FSNAME //denghg modify 2006-6-10 15:53
            && ( enType >= FONT_CP_1250 && enType <= FONT_CP_1258 )
            #else
            &&  enType <= FONT_CP_950_COMMON 
            #endif
          )
        
        {
            
            
            uiCount += FSGUI_PreDrawBmp( video_buf, pBmp, x + uiCount, y, uiWidth, uiHeight, uiY, uiCbCr, uiCharFitHeight, ENUM_DOWN_SAMPLING_ALL );

            if( uiRtnVal == FONT_ONE_BYTE )
                pStr++;
            else
                pStr += 2;            
        }
        else
        {
		    BYTE    c   = *pStr;
		#ifdef	GPS_MP3_UI	//suxin add, 2005-09-20
            if ( ((c > 10) && (c < 32)) || (c > 126) )
            {
                c = '_';
            }
			if((c >= 1) && (c <= 10))
			{
				if( ( pBmp = get_font_entry( 3, c ) ) )
					uiCount += FSGUI_PreDrawBmp( video_buf, pBmp + 3, x + uiCount, y, pBmp[0], pBmp[1], uiY, uiCbCr, uiCharFitHeight, ENUM_DOWN_SAMPLING_RIGHT_UP_CORNER );
			}
			else
			{
				if( ( pBmp = get_font_entry( 0, c ) ) )
                	uiCount += FSGUI_PreDrawBmp( video_buf, pBmp + 3, x + uiCount, y, pBmp[0], pBmp[1], uiY, uiCbCr, uiCharFitHeight, ENUM_DOWN_SAMPLING_RIGHT_UP_CORNER );
			}
		#else	//GPS_MP3_UI
            if ( (c < 32) || (c > 126) )
            {
                c = '_';
            }

            if( ( pBmp = get_font_entry( 0, c ) ) )
                uiCount += FSGUI_PreDrawBmp( video_buf, pBmp + 3, x + uiCount, y, pBmp[0], pBmp[1], uiY, uiCbCr, uiCharFitHeight, ENUM_DOWN_SAMPLING_RIGHT_UP_CORNER );

		#endif	//GPS_MP3_UI
            pStr++;
        }
		if( uiCount > uiMaxStringLength )
			break;
	}
}

// **************************************************************************************** //
#include "vpp.h"
#include "avd.h"
#include "fsNAV.h"

#define SMALL_GUI_ROW_HEIGHT    12
#define LARGE_GUI_ROW_HEIGHT    24

#define SMALL_GUI_LONG_ROW_WIDTH	350
#define SMALL_GUI_SHORT_ROW_WIDTH	105

#define LAEGE_GUI_ROW_WIDTH		540

static void FSGUI_Pre_ShowString_Ex( BYTE video_buf, int x, int y, const UINT8 *s, BYTE uiY, UINT16 uiCbCr )
{
	extern int is_show_path_info_string;
    FSGUI_FONT_DRAW_LIMITATION stLimit;
    if((getVPP_PictureWidth() <= 352) || IsAVDPreview() || (pFsJpeg->g_nJpegMode == JPEG_THUMBNAIL_MODE))
    {
		if(is_show_path_info_string || (pFsJpeg->g_nJpegMode == JPEG_THUMBNAIL_MODE))
		{
	    	stLimit.uiMaxStringLength = SMALL_GUI_LONG_ROW_WIDTH;
			is_show_path_info_string  = 0;
		}
		else
		{
	   	    stLimit.uiMaxStringLength = SMALL_GUI_SHORT_ROW_WIDTH;			
		}
		stLimit.uiCharFitHeight   = SMALL_GUI_ROW_HEIGHT;
    }
    else
    {
        stLimit.uiCharFitHeight     = LARGE_GUI_ROW_HEIGHT;
        stLimit.uiMaxStringLength   = LAEGE_GUI_ROW_WIDTH;        
    }

    FSGUI_ShowString_Ex( video_buf, x, y, s, uiY, uiCbCr, &stLimit );    
}

// **************************************************************************************** //
void FSGUI_ShowString( int x, int y, const UINT8 *s, BYTE uiY, UINT16 uiCbCr )
{
    FSGUI_Pre_ShowString_Ex( 0, x, y, s, uiY, uiCbCr );
}

// **************************************************************************************** //
void FSGUI_ShowChar( BYTE video_buf, int x, int y, BYTE c, BYTE uiY, UINT16 uiCbCr )
{
    char aBuf[2] = { c, 0 };
    FSGUI_Pre_ShowString_Ex( video_buf, x, y, aBuf, uiY, uiCbCr );
}

// **************************************************************************************** //
    #ifdef FS_BMP_GUI
/*
    Function:In order to show little string in Sunplus New GUI
    Creator:Feeling
*/
void FSGUI_ShowLittleString( int x, int y, const char *s, BYTE uiY, UINT16 uiCbCr )
{
    FSGUI_FONT_DRAW_LIMITATION stLimit;
    stLimit.uiCharFitHeight     = SMALL_GUI_ROW_HEIGHT;
    stLimit.uiMaxStringLength   = 540;   
    FSGUI_ShowString_Ex( 0, x, y, s, uiY, uiCbCr, &stLimit );
}
    #endif

// **************************************************************************************** //

#ifdef FSGUI_FONTFRAME
//suxin add 2005-10-09 for display frame_font.
extern void FrameBuf_DrawFontFrame( BYTE video_buf, const BYTE* bmp, coordinate *start, UINT32 FontColor, UINT32 FrameColor)
{
    UINT32  uiPixelCnt = 0;
    UINT32  i, j;
    UINT8	  uiHeight,uiWidth;
    uiHeight = bmp[1];
    uiWidth = bmp[0];
    bmp = bmp + 2;
	
	for( j = 0; j < uiHeight; j++ )
	{
	    for( i = 0; i < uiWidth; i++ )
	    {
	        UINT8 uiBitVal = ( bmp[ uiPixelCnt / 4 ] >> ( (3 - ( uiPixelCnt % 4 ))*2 ) ) & 0x03;
	        
	        if( uiBitVal )
	        {
	            UINT16 uiCoordX = start->x + i;
	            UINT16 uiCoordY = start->y+ j;
                   UINT32 uiFrmLAddr = 0, uiFrmCAddr = 0;
                
                if( video_buf == 0 )
                {
                    uiFrmLAddr  = REF0_LUMA;
                    uiFrmCAddr  = REF0_CHROMA;
                }
                else if( video_buf == 1 )
                {
                    uiFrmLAddr  = REF1_LUMA;
                    uiFrmCAddr  = REF1_CHROMA;
                }
                else if( video_buf == 2 )
                {
                    uiFrmLAddr  = BIDIR_LUMA;
                    uiFrmCAddr  = BIDIR_CHROMA;
                }
                
                UINT8*  pFrmLAddr = (UINT8*) ( SDRAM_BASE + ( uiFrmLAddr << 10 ) + OFFSET_Y(uiCoordY) + SFF(uiCoordX) );
                UINT16* pFrmCAddr = (UINT16*)( SDRAM_BASE + ( uiFrmCAddr << 10 ) + OFFSET_C( (uiCoordY) >> 1 ) + 2 *( SFF(uiCoordX) >> 1 ) );
			if(uiBitVal == 0x03)
                	{	UINT8 r,g,b;
				r=FontColor>>16;
				g=FontColor>>8;
				b=FontColor;
                		*pFrmLAddr  = (((71*(r) + 141*g + 27*b + 0x1000)&0xFF00)>>8);
                		*pFrmCAddr  = (((127*(r)-106*(g)-21*(b)+0x8000)&0xFF00)|((((-43)*(r)-85*(g)+127*(b)+0x8000)>>8)&0xFF));
			}
			else
			{
				UINT8 r,g,b;
				r=FrameColor>>16;
				g=FrameColor>>8;
				b=FrameColor;
				*pFrmLAddr  =(((71*(r) + 141*g + 27*b + 0x1000)&0xFF00)>>8);
                		*pFrmCAddr  = (((127*(r)-106*(g)-21*(b)+0x8000)&0xFF00)|((((-43)*(r)-85*(g)+127*(b)+0x8000)>>8)&0xFF));
			}
	        }

	        uiPixelCnt++;
	    }
    }
}
#endif
#endif

