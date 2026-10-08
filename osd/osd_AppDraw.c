// 2005/08/29 yltseng, modify subtitle string drawing function to change from byte base to pixel base
#include "osd_AppAPI.h"

#ifdef NEW_OSD_DRIVER
#include "global.h"
#include "osd_api.h"

#include "cfont.h"
#include "osd.h"
#include "osdfont.h"
#if defined(MUSTEK_PORTABLE_DVD)
#include "osd_str_mustek_pdvd.h"
#elif defined(ALCO_PORTABLE)
#include "osd_str_alco_portable.h"
#else
#include "osd_str.h"
#endif
#include "osd_palette.h"

#include "setup.h"

#ifdef NEW_HDMI_FLOW
#include "hdmi_api.h"
#endif

#ifdef  ALWAYS_DISPLAY_OPEN//Jack 20041008
#include "cd.h"
#endif

#ifdef DVB_DVD_8202
#include "..\dvb_h\dvb_func.h"
#endif
#if defined (SUPPORT_SMI_MultiLanguage)
extern BYTE lang_num;
extern BYTE nowSupLang;
extern UINT8  SmiSupType;
extern int IS_EXT_SUP_ACTIVATED();
#endif

#ifndef OSD_APP_DEBUG
    #define osdbuf              linebuf
    #define osd_putc(c)         ((void) 0)
    #define osd_puts(s)         ((void) 0)
    #define osd_printf(s...)    ((void) 0)

    #undef  printf
    #undef  print_block
    #define printf(f, a...)     ((void) 0)
    #define print_block(x,y)    ((void) 0)

#else
    UINT8 osdbuf[100];
    #define osd_putc            putc_w
    #define osd_puts            puts_w
    #define osd_printf          printf_w

#endif

#ifdef  NEW_STYLE_SETUP
    #define SETUP_REGION    1
#else
    #define SETUP_REGION    0
#endif


#ifdef FONT_WIDTH_ADJUSTMENT
void CalcuteFontActualWidth(UINT8 *pSrc, UINT8 Width, UINT8 Height, UINT8 uStride,UINT8 color_format);
#endif

#if (defined(NEWSTYLE_WINDOW)|defined(SUPPORT_MIDI_MENU_SEL))
//xlluo modify for midiplayer draw menurect 04-6-11
const BYTE arc_tableLT[10][10]=
{
    {0,0,0,0,0,0,0,1,1,1},
    {0,0,0,0,0,1,1,2,2,2},
    {0,0,0,1,1,2,2,2,2,2},
    {0,0,1,2,2,2,2,2,2,2},
    {0,0,1,2,2,2,2,2,2,2},
    {0,1,2,2,2,2,2,2,2,2},
    {0,1,2,2,2,2,2,2,2,2},
    {1,2,2,2,2,2,2,2,2,2},    
    {1,2,2,2,2,2,2,2,2,2},    
    {1,2,2,2,2,2,2,2,2,2},
};

const BYTE arc_tableRT[10][10]=
{
    {1,1,1,0,0,0,0,0,0,0},
    {2,2,2,1,1,0,0,0,0,0},
    {2,2,2,2,2,1,1,0,0,0},
    {2,2,2,2,2,2,2,1,0,0},
    {2,2,2,2,2,2,2,1,0,0},
    {2,2,2,2,2,2,2,2,1,0},
    {2,2,2,2,2,2,2,2,1,0},
    {2,2,2,2,2,2,2,2,2,1},    
    {2,2,2,2,2,2,2,2,2,1},    
    {2,2,2,2,2,2,2,2,2,1},
};
    
const BYTE arc_tableLB[10][10]=
{
    {1,2,2,2,2,2,2,2,2,2},    
    {1,2,2,2,2,2,2,2,2,2},
    {1,2,2,2,2,2,2,2,2,2},    
    {0,1,2,2,2,2,2,2,2,2},
    {0,1,2,2,2,2,2,2,2,2},
    {0,0,1,2,2,2,2,2,2,2},
    {0,0,1,2,2,2,2,2,2,2},
    {0,0,0,1,1,2,2,2,2,2},
    {0,0,0,0,0,1,1,2,2,2},
    {0,0,0,0,0,0,0,1,1,1},
};
const BYTE arc_tableRB[10][10]=
{
    {2,2,2,2,2,2,2,2,2,1},
    {2,2,2,2,2,2,2,2,2,1},    
    {2,2,2,2,2,2,2,2,2,1},    
    {2,2,2,2,2,2,2,2,1,0},
    {2,2,2,2,2,2,2,2,1,0},
    {2,2,2,2,2,2,2,1,0,0},
    {2,2,2,2,2,2,2,1,0,0},
    {2,2,2,2,2,1,1,0,0,0},
    {2,2,2,1,1,0,0,0,0,0},
    {1,1,1,0,0,0,0,0,0,0},
};
#endif

const UINT8* get_font_entry(int tbl, int entry)
{
    extern  UINT8   decomp_fnTable[] __UNUSED;

    unsigned    u = 0;

    if (tbl == 0)
        u = (unsigned) font_table[entry];
    else if (tbl == 1)
        u = (unsigned) font_table2[entry];
#ifndef SETUPMENU_16Mb_NO_ICON 
    else if (tbl == 2)
        u = (unsigned) setup_icon[entry];
#endif
#ifdef USE_NEW_SCHINESE_OSD //liyl add 20060116
    else if (tbl == 4)
        u = (unsigned) font_table3[entry];
#endif
#if defined(SUPPORT_PLAYBACK_ICON)||defined(SUPPORT_8202_DVB)
    else
        u = (unsigned) play_icon[entry];
#endif

#ifdef OSD_FONT_COMPRESS            
    return (BYTE *)(decomp_fnTable + u);
#else
    return (BYTE *)u;
#endif
}

#ifdef OP_IR//libing
void osd_draw_HL(BYTE r,UINT32 xStart, UINT32 yStart,UINT32 xLen,UINT32 yLen, int LineWidth,BYTE color)
{//libing 2005-1-27 10:04
	osd_draw_hline_region(xStart, xStart+xLen, yStart, color,LineWidth, r);
	osd_draw_hline_region(xStart, xStart+xLen, yStart+yLen-LineWidth, color,LineWidth, r);
	osd_draw_vline_region(xStart, yStart, yStart+yLen, color,LineWidth, r);
	osd_draw_vline_region(xStart+xLen-LineWidth, yStart, yStart+yLen, color,LineWidth, r);
}
#endif
/*
#define OSD_SRT_REGION_NTSC_Y   182
#define OSD_SRT_REGION_PAL_Y    218
extern void osd_move_subtitle_region()     // 2005/07/12 yltseng
{
    if( IS_EXT_SUP_INITIALIZED() )
    {
    	if( getVPP_TVsystem() )
    		MoveRegion( 3, 26, OSD_SRT_REGION_PAL_Y );
    	else
    		MoveRegion( 3, 26, OSD_SRT_REGION_NTSC_Y );
	}
}
*/
/**************************************************************************
 *  Function Name: osd_draw_string                                        *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_draw_string( const coordinate *start, const BYTE *str, UINT16 fontColor, UINT16 bkColor, BYTE r, BYTE only_font_color)
{
    BYTE c;
    const BYTE *pFont;
    UINT32 iStrLoc;
    
    font_palette temp_palette;
    dimension out_dimension;
    coordinate  temp_coordinate;
    UINT16 strleng;
    
    temp_coordinate.x = start->x;
    temp_coordinate.y = start->y;

//    marked by robert.chang 2006/04/25
/*
    if(p_scan==1)
        temp_coordinate.y = temp_coordinate.y <<1;
*/    

	temp_palette.font_color = fontColor;
	temp_palette.background_color = bkColor;
	
    iStrLoc = 0;
    strleng = 0;	
    
    while( (c = ((BYTE *)str)[iStrLoc]) != '\0' ) 
    {       
        iStrLoc++;
        
        if (c == '\r')      //prefix characher:to use font_table2
        { 
            if ( (c = ((BYTE *)str)[iStrLoc])=='\0' )
                break;
            
            iStrLoc++;
            
            if ((pFont = get_font_entry(1,c))==NULL) continue;
  
        }
        else if (c == '\a') 
        { 
            if ( (c=((BYTE *)str)[iStrLoc])=='\0' ) break; 
             
            iStrLoc++; 
 
            if ((pFont = get_font_entry(3,c))==NULL) continue; 
 
        } 
#ifdef USE_NEW_SCHINESE_OSD //liyl add 20060116
        else if (c == '\f')
        {
            if ((c = ((BYTE *)str)[iStrLoc]) == '\0')
                break;
            iStrLoc++;
            if ((pFont = get_font_entry(4, c)) == NULL)
                continue;
        }
#endif
#if 0//def DVB1000_OSD_MENU //Maoyong 2004-10-26 16:08 //sunzhh modify 2005-4-15
        else if(c>='a' && c<='z')
        {
            if(IsOSDChinese())
                pFont = get_font_entry(0, c);
            else                
            pFont=get_font_entry(0,c-'a'+0xc0);
        }
#endif     
        else 
        {   
            if (c=='\n')
            {
                c=' ';   
            }    
  
            //get current char entry
            if ((pFont = get_font_entry(0,c))==NULL) continue;
        }
    
        if ((iStrLoc>antic_begin)&& (iStrLoc<antic_end))
        {
		#ifdef INDIGO_STYLE_OSDUI
           	temp_palette.background_color = 7; // change the HL color when prog item choosen.
			temp_palette.font_color = 1;	   // change the font color when prog item choosen.	  
	  	#else
            temp_palette.background_color = 2;
	  	#endif
        }
        else
        {
            temp_palette.background_color = bkColor;
		#ifdef INDIGO_STYLE_OSDUI
			temp_palette.font_color = fontColor;	
		#endif
		}
    
        out_dimension.x_length = pFont[0];
	 out_dimension.y_length = pFont[1];
	 strleng += out_dimension.x_length;
	 
        //Check that the length of string is longer than region width or not
        //liyl move to here 20060123
        if((temp_coordinate.x + out_dimension.x_length) > region[r].osd_visible_w)
            break;
        
        pFont +=3;
        
		DrawAttribute draw_bmp_attribute;
		draw_bmp_attribute.start.x = temp_coordinate.x;
		draw_bmp_attribute.start.y = temp_coordinate.y;
		draw_bmp_attribute.bmp_dimension.x_length = out_dimension.x_length;
		draw_bmp_attribute.bmp_dimension.y_length = out_dimension.x_length;
		draw_bmp_attribute.region_index = r;
		draw_bmp_attribute.p_bmp = pFont;
		draw_bmp_attribute.draw_type.is_reference_palette = 1;
		draw_bmp_attribute.draw_type.bits_a_pixel = 1;
		draw_bmp_attribute.draw_type.only_fore_color = only_font_color;
		draw_bmp_attribute.bmp_offset.draw_start.x = 0;
		draw_bmp_attribute.bmp_offset.draw_start.y = 0;
		draw_bmp_attribute.bmp_offset.draw_dimension.x_length = out_dimension.x_length;
		draw_bmp_attribute.bmp_offset.draw_dimension.y_length = out_dimension.y_length;
		UINT16 color_palette[]={temp_palette.background_color, temp_palette.font_color, 0, 0};
		draw_bmp_attribute.p_palette = color_palette;

		if(full_scrn & SETUP)
		{
			//first stage=============================================
			#if defined(SUPPORT_FONT_OUTLINE) && defined(SUPPORT_FONT_OUTLINE_IN_SETUP_MENU)
			const BYTE* 	pFont1;
			const BYTE*  	pFonttem;

			pFont1 = draw_bmp_attribute.p_bmp;

		    #define FSJPEG_BUF_OFFSET  ( ( sizeof( FSJPEGDATA ) >> 2 ) << 2 )    
			#define FONT_OUTLINE_WIDTH_IN_SETUP	1
		    pFonttem = (UINT8*) ( (UINT32)pFsJpeg + FSJPEG_BUF_OFFSET );
			OSD_DrawFontFrame((UINT8*)pFonttem,(UINT8*)pFont1, out_dimension.x_length, out_dimension.y_length, FONT_OUTLINE_WIDTH_IN_SETUP);	

			out_dimension.x_length  = pFonttem[0];
			out_dimension.y_length = pFonttem[1];

			pFonttem = pFonttem + 2;

			color_palette[0] = temp_palette.background_color;
			color_palette[1] = 1;
			color_palette[2] = 1;
			color_palette[3] = temp_palette.font_color;
			draw_bmp_attribute.draw_type.bits_a_pixel = 2;
			draw_bmp_attribute.p_bmp =  pFonttem;
			draw_bmp_attribute.bmp_dimension.x_length = out_dimension.x_length;
			draw_bmp_attribute.bmp_dimension.y_length = out_dimension.y_length;
			draw_bmp_attribute.bmp_offset.draw_dimension.x_length = out_dimension.x_length;
			draw_bmp_attribute.bmp_offset.draw_dimension.y_length = out_dimension.y_length;

			out_dimension.x_length = (out_dimension.x_length - 8 + 2*FONT_OUTLINE_WIDTH_IN_SETUP) + 1; 
			#endif

			//second stage=============================================
			#if defined(FONT_WIDTH_ADJUSTMENT) && defined(FONT_WIDTH_ADJUSTMENT_IN_SETUP_MENU)
			const BYTE* 	pFont1;
			#define FONTGAP 3
			extern UINT8 RWid, LWid;
			pFont1 = draw_bmp_attribute.p_bmp;

			if(draw_bmp_attribute.draw_type.bits_a_pixel == 1)
				CalcuteFontActualWidth((UINT8*)pFont1, out_dimension.x_length, out_dimension.y_length, out_dimension.x_length, OSD_FORMAT_2COLOR);

			else if(draw_bmp_attribute.draw_type.bits_a_pixel == 2)
				CalcuteFontActualWidth((UINT8*)(pFont1 - 2), out_dimension.x_length, out_dimension.y_length, out_dimension.x_length, OSD_FORMAT_4COLOR);

		    draw_bmp_attribute.bmp_offset.draw_start.x = LWid;
		    draw_bmp_attribute.bmp_offset.draw_dimension.x_length = (RWid-LWid+1);

			out_dimension.x_length = ((RWid-LWid+1) - 2* FONTGAP) + 3;
			#endif
		}
		osd_draw_data(&draw_bmp_attribute);        
        
        temp_coordinate.x +=out_dimension.x_length;
        
        //Check that the length of string is longer than region width or not
        //if(temp_coordinate.x > region[r].osd_visible_w)
            //break;    
    }

#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
//  move the HighLight to correct position, and resize to correct size for region, robert.chang, 2006/03/16
    	dimension hl_dimension;
    	coordinate hl_coordinate;
	if((r==REGION1 || r==REGION2) && (!(full_scrn & PROGRAM))) {
		if(region[osd_display_list[r]].osd_highlight != LINK_NULL) {
			hl_dimension.x_length = strleng;
			hl_dimension.y_length = region[r].osd_h;
			hl_coordinate.x = start->x;
			hl_coordinate.y = start->y;				
			osd_resize_sub_highlight( r, hl_dimension );
			osd_move_sub_highlight( r, hl_coordinate );
		}	
	}
#endif

	
}


/**************************************************************************
 *  Function Name: osd_DrawString                                         *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_DrawString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor)
{
#ifdef SOFT_MENU//Modifed by ChenZhao on 2004-9-6 10:43 WP
    osd_DrawString_ori(xStart*8, (yStart*SETUP_BTN_HEIGHT), str, fontColor, bkColor);
#elif defined(SOFT_MENU_REENG)//chenzhao20050523
    osd_DrawString_ori(xStart*16, (yStart*SETUP_BTN_HEIGHT), str, fontColor, bkColor);
#else
    osd_DrawString_ori(xStart, (yStart*SETUP_BTN_HEIGHT), str, fontColor, bkColor);
#endif
}


/**************************************************************************
 *  Function Name: osd_DrawString_ori                                     *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_DrawStrings(const t_osd_str *p, BYTE fg, BYTE bg)
{
    int i;
    for (i=0; p[i].str!=NULL; i++)
    {
        osd_DrawString(p[i].xst, p[i].yst, p[i].str, fg, bg);
    }
}


/**************************************************************************
 *  Function Name: osd_DrawString_ori                                     *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
#ifdef SOFT_MENU//Modifed by ChenZhao on 2004-9-6 10:43 WP

    #include "kernel.h"
    #include "setup_def.h"
	#include "osd_SFM.c"

#elif defined(SOFT_MENU_REENG)//chenzhao20050520
    #include "osd_sfm_reeng.c"
#elif defined(USE_SMALL_FONT)
//  libing for small font 2005-1-5 20:52
//  libing modify it for zhe smaller font 2004-11-3 13:53
extern void osd_DrawString_ori(BYTE xStart, UINT32 yStart, const BYTE *str, BYTE fontColor, BYTE bkColor)
{
    BYTE    c;
    BYTE    *pFont;
    UINT16  *pTopLine, *pBtmLine;
    int     cc;
    UINT32  iStrLoc;
    int     iRegionWidth;
    iRegionWidth = region[SETUP_REGION].osd_w;
    pTopLine = (UINT16 *)get_osdbuf_region_ptr(SETUP_REGION, 0);
    pBtmLine = (UINT16 *)get_osdbuf_region_ptr(SETUP_REGION, 1);
    cc = xStart*16; 
    iStrLoc = 0;
    while ((c = ((BYTE *)str)[iStrLoc]) != '\0')
    {
        int     i, j, k;
        int     iFontWidth, iFontHigh;
        UINT32  pos;
        UINT8   fourbit;
        iStrLoc++;
        
        if (c == '\r') {                   
            if ( (c = ((BYTE *)str)[iStrLoc])=='\0' ) break;
            iStrLoc++;
            if ((pFont = get_font_entry(1,c))==NULL) continue;
        } else {
            pFont = get_font_entry(0,c);
        }
        pos = 2;
        iFontWidth = (int)pFont[0];
        iFontHigh  = (int)pFont[1];
        fourbit=1;

        for (j=0; j<iFontHigh; j++) {
            UINT16 *pp;
            int     yy;
            int     iDispLoc;
            yy  = 4 + yStart + j;
            pp  = (yy&1) ? pBtmLine : pTopLine;
            if (p_scan==0) yy>>=1;     
            iDispLoc = yy*(iRegionWidth/2) + (cc/4);
            {            	
            for (i=0; i<iFontWidth/4; i++)
              {
                unsigned pat;
                unsigned curByte;
                UINT16 pixel4;
                if(fourbit)
                {                    
                    pat = (pFont[++pos])&0xf0;
                    fourbit=0;
                }
                else
                {                    
                    pat = (pFont[pos])<<4;
                    fourbit=1;
                }
                curByte = ((pat&0xc0)>>6) | ((pat&0x30)>>2);
                pixel4 = 0;
                for (k=0; k<4; k++) {       
                    if ((1<<k) & curByte)
                    {          
                        pixel4 = pixel4 | (fontColor<<(k*4));
                    } else {
                        pixel4 = pixel4 | (bkColor<<(k*4));
                    }
                }
                pp[iDispLoc+i] = pixel4;
             }
         }
    }   cc+=iFontWidth; 
    }
    timeout_osd[SETUP_REGION] = 0;
    osd_tog_region(SETUP_REGION, OSD_ON);  
}	
	
#else

extern void osd_DrawString_ori(BYTE xStart, UINT32 yStart, const BYTE *str, BYTE fontColor, BYTE bkColor)
{    
    coordinate start;
    start.x = xStart*16;
#ifdef INDIGO_STYLE_OSDUI
    start.y = yStart;   //This is a legacy-formula for back-compatible
#else
    start.y = yStart+4;   //This is a legacy-formula for back-compatible
#endif    
    
    osd_draw_string(&start, str, fontColor, bkColor, SETUP_REGION, 0);
}
#endif /* SOFT_MENU */


/**************************************************************************
 *  Function Name: osd_DrawRegionString                                   *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
#if defined(USE_SMALL_FONT)||defined(OP_PLAYMODE)
//libing for small font 2005-1-5 20:52
extern void osd_DrawRegionString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r)
{
    BYTE    *pFont, c;
    UINT16  *pTopLine, *pBtmLine;
    UINT32   iStrLoc;
    UINT16   iDispLoc;
    int     cc;
    int     i, j, k;
    int     iFontWidth, iFontHigh;
    int     iRegionWidth = region[r].osd_w,iRegionHigh = region[r].osd_h;    
    osd_tog_region(r, OSD_ON);  
    pTopLine = (UINT16 *)get_osdbuf_region_ptr(r,0);
    pBtmLine = (UINT16 *)get_osdbuf_region_ptr(r,1); 
    cc = xStart*16;   
    iStrLoc = 0;
    
    while ( (c = ((BYTE *)str)[iStrLoc]) != '\0' ) 
    {
        BYTE curByte;
        UINT32 pos;  
        int fourbit=1;      
        iStrLoc++;        
        if (c == '\r') 
        { 
            if ( (c = ((BYTE *)str)[iStrLoc])=='\0' )
                break;            
            iStrLoc++;
            if ((pFont = get_font_entry(1,c))==NULL) continue;
        }
        else 
        {
            pFont = get_font_entry(0,c);
        }
        
        pos = 2;
        iFontWidth = (int)pFont[0];
        iFontHigh = (int)pFont[1];
        
        for (j=0; j<iFontHigh; j++) {
            UINT16 *pp;
            int     yy;                   	
            if (iFontWidth==12)
            yy  = 4 + (yStart*4) + j +4;
            else
            yy  = 4 + (yStart*4) + j;
            pp  = (yy&1) ? pBtmLine : pTopLine;
            if (p_scan==0) yy>>=1;    
            iDispLoc = yy*(iRegionWidth/2) + (cc/4); 	
            for (i=0; i<iFontWidth/4; i++) {
                unsigned pat;
                unsigned curByte;
                UINT16 pixel4;
                if(fourbit)
                {                    
                    pat = (pFont[++pos])&0xf0;
                    fourbit=0;
                }
                else
                {                    
                    pat = (pFont[pos])<<4;
                    fourbit=1;
                }
                curByte = ((pat&0xc0)>>6) | ((pat&0x30)>>2);
                pixel4 = 0;//pTopLine[iDispLoc+i];
                for (k=0; k<4; k++) {       
                    if ((1<<k) & curByte)
                    {          
                        pixel4 = pixel4 | (fontColor<<(k*4));
                    } else {
                        pixel4 = pixel4 | (bkColor<<(k*4));
                    }

                    }                
                pp[iDispLoc+i] = pixel4; 
             }
        }    
                cc+=iFontWidth;               
        }    
    timeout_osd[r] = 0;
}

#else
extern void osd_DrawRegionString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r)
{
    coordinate start;
    start.x = xStart*16;
    start.y = yStart*4+4;   //This is a legacy-formula for back-compatible
    
    osd_draw_string(&start, str, fontColor, bkColor, r, 0);
}
#endif //#if defined(USE_SMALL_FONT)


/**************************************************************************
 *  Function Name: osd_DrawIcon                                           *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
#ifdef NEW_STYLE_SETUP //zhaoyanhua add 2003-07-22 22:21
extern void osd_DrawIcon(int xStart, int yStart, unsigned index, unsigned page)
{
    BYTE    *pIcon;
    UINT32  *pTopLine, *pBtmLine;
    UINT32  iDispLoc, iIconLoc;
    int     need_gray=0;

    int     i, j, k;
    int     iFontWidth, iFontHigh;
    int     iRegionWidth = region[1].osd_w;


    osd_tog_region(1, OSD_ON);
    iRegionWidth = region[1].osd_w;
    //initialize buffer start
    pTopLine = (UINT32 *)get_osdbuf_region_ptr(1,0);   // region 0 top
    pBtmLine = (UINT32 *)get_osdbuf_region_ptr(1,1);   // region 0 bot
    need_gray = 0;

    iIconLoc = 0;

    //skip n blank line on top(in pixel)
    //for interlace mode, we will skip n/2 blank lines, for example 4/2=2
    yStart+=2;

    {
        UINT32 pixel8;
        UINT32 pos;

        iIconLoc++;

        pIcon = get_font_entry(2, index);

        //start to process
        pos = 2;

        //get icon information
        iFontWidth  = (int)pIcon[0];
        iFontHigh   = (int)pIcon[1];

        for (j=0; j<iFontHigh; j++)
        {
            int yy;
            UINT32 *pp;
            yy = (p_scan) ? yStart : yStart>>1;
            pp = (yStart&1) ? pBtmLine : pTopLine;

            iDispLoc = (yy*iRegionWidth*2/8) + (xStart);
            for (i=0; i<(iFontWidth/4/2); i++) // every 4-bytes a time, every 2-pixels a byte
            {
                pixel8=0;
                // 0x12345678  ==>  0x78563412
                for (k=0;k<4;k++)
                {
                    unsigned curByte = pIcon[++pos];
                    if (page!=index)
                    {
                        if ((curByte&0x0f)==0x04) curByte=(0x00|(curByte&0xf0));
                        if ((curByte&0xf0)==0x40) curByte=(0x00|(curByte&0x0f));
                        if ((curByte&0x0f)==0x0b) curByte=(0x0c|(curByte&0xf0));
                        if ((curByte&0xf0)==0xb0) curByte=(0xc0|(curByte&0x0f));
                    }
                    if (need_gray==1)
                    {
                        if ((curByte&0x0f)!=0x01) curByte=(0x0b|(curByte&0xf0));
                        if ((curByte&0xf0)!=0x10) curByte=(0xb0|(curByte&0x0f));
                    }
                    pixel8 = pixel8 | (curByte<<8*k);
                }
                pp[iDispLoc+i] =  pixel8;
            }
            yStart++;
        }//for icon heigh
    }

    timeout_osd[1] = 0;

}

#elif defined(SOFT_MENU_REENG)//chenzhao20050524
#else //NORMAL setup MENU

#include "audcodec.h"
#include "setup_page.h"
#include "setup_def.h"
extern UINT8 setup_sel[MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE][MAX_PAGE_ITEM];
    
extern void osd_DrawIcon(int xStart, int yStart, unsigned index, unsigned page)
{
    const BYTE    *pIcon;
    UINT32  *pTopLine, *pBtmLine;
    UINT32  iDispLoc, iIconLoc;
    int     need_gray=0;

    int     i, j, k;
    int     iFontWidth, iFontHigh;
    int     iRegionWidth = region[0].osd_w;
#ifdef SUPPORT_SW_OSD_SCALING
        DrawDimension scale_section;
#endif
    
#ifdef NO_AUDIO_PAGE//liweihua add for syber 2003-12-30 22:01
    if((index>=2)&&(index<=4))index=index+1;
#endif

#ifdef DVB_MENU_SETUP_STYLE

	if(system_state == SYSTEM_TS)
	{
		if(index==3)
			index=index+2;
	}
	else
	{
		if((index>=0)&&(index<=5))
			index+=2;
	}
#endif

#ifdef EASTWIN_PORTABLE_DVD
    #ifdef NO_SPEAK_ICON//tulijuan040910
    if((index>=4)&&(index<=5))index=index+1;
    #endif
#endif

#ifndef SETUP_ALL_VALID        // alan, 2003/7/18 10:49と
    {
        if ( (index==MULTISPKPAGE)&&(cd_subtype!=CD_DTS) &&  (cd_type_loaded!=CDDVD) && ( coding_mode_now&(~(AUDIF_CODING_MODE_AC3|AUDIF_CODING_MODE_DTS|AUDIF_CODING_MODE_DTSCD)) ) )
        {
            need_gray=1;
        } else if ( (index==MULTISPKPAGE) && (SETUP_SPDIF!=SPDIFSIMULATE) )
        {
            need_gray=1;
        }
            
        if ( (index==AC3DIGITALPAGE) && ( (SETUP_SPDIF==SPDIFBITSTREAM) || (coding_mode_now!=AUDIF_CODING_MODE_AC3))) 
        {
            need_gray=1;
        } 
    }
#endif
    
#ifdef NO_DIGIT_MENU    
        if (index==AC3DIGITALPAGE)
        {
            need_gray=1;
        } 
#elif defined(NO_DIGIT_VIDEO_MENU)

        if( (index==AC3DIGITALPAGE)||(index==VIDEOPAGE) )
        {
            return;
        } 

    #ifdef EASTWIN_PORTABLE_DVD 
    #elif defined(NO_SPEAK_ICON)//tulijuan
        if( index==6)//MULTISPKPAGE )tulijuan040910
        {
            return;
        }
    #endif

#endif//NO_DIGIT_MENU
    
    osd_tog_region(0, OSD_ON);  
    
    //initialize buffer start
    pTopLine = (UINT32 *)get_osdbuf_region_ptr(0,0);   // region 0 top
    pBtmLine = (UINT32 *)get_osdbuf_region_ptr(0,1);   // region 0 bot

    iIconLoc = 0;
    
    //skip n blank line on top(in pixel)
    //for interlace mode, we will skip n/2 blank lines, for example 4/2=2
    yStart+=2;
     
    {
        UINT32 pixel8;
        UINT32 pos;
        
        iIconLoc++;        
        
#ifdef NO_DIGIT_VIDEO_MENU
        if(index == 3)

    #ifdef EASTECH_NEW_SETUP_MENU
        pIcon = get_font_entry(2, index-1);
    #else
        pIcon = get_font_entry(2, index+1);
    #endif//EASTECH_NEW_SETUP_MENU
        else
#endif//#ifdef NO_DIGIT_VIDEO_MENU

#ifdef SETUP_DONGLI459
        if(index==3||index==4)
        pIcon=get_font_entry(2, index+1);
        else
#endif

#ifdef EASTECH_NEW_SETUP_MENU
	if(index==2)   // modify by Tom  20040716
	        pIcon = get_font_entry(2, index+2);
	else
#elif defined(PHILIPS_SETUP) 
    if (page==index) // chenzhao20050613
        pIcon = get_font_entry(2, index+6);
    else
#endif//EASTECH_NEW_SETUP_MENU
        pIcon = get_font_entry(2, index);

        //start to process
        pos = 2;
        
        //get icon information
        iFontWidth  = (int)pIcon[0];
        iFontHigh   = (int)pIcon[1];
#ifdef SUPPORT_SW_OSD_SCALING

    if( (GET_TV_RESOLUTION()  == HD_720) || (GET_TV_RESOLUTION()  == HD_1080) ) {

        scale_section.draw_start.x = xStart*8;
        scale_section.draw_start.y = yStart;        
        scale_section.draw_dimension.x_length = iFontWidth;
        scale_section.draw_dimension.y_length = iFontHigh;     
    }
    
#endif
        
        for (j=0; j<iFontHigh; j++) 
        {
            int yy;
            UINT32 *pp;
            yy = (p_scan) ? yStart : yStart>>1;
            pp = (yStart&1) ? pBtmLine : pTopLine;
            
            iDispLoc = (yy*iRegionWidth*2/8) + (xStart);
            for (i=0; i<(iFontWidth/4/2); i++) // every 4-bytes a time, every 2-pixels a byte
            {
                pixel8=0;
                // 0x12345678  ==>  0x78563412
                for (k=0;k<4;k++)
                {                    
                    unsigned curByte = pIcon[++pos];
                    #ifndef PHILIPS_SETUP //chenzhao20050613
                    if (page!=index)
                    {                    
#ifdef SETUP_COLOR_TYPE2       //zhangyu 3-9-2 11:48张宇A
                        #ifdef ALCO_MODIFY_PAL_OSD
                        if ((curByte&0x0f)==0x06) curByte=(0x02|(curByte&0xf0));
                        if ((curByte&0xf0)==0x60) curByte=(0x20|(curByte&0x0f));
                        #else
                        if ((curByte&0x0f)==0x06) curByte=(0x0d|(curByte&0xf0));
                        if ((curByte&0xf0)==0x60) curByte=(0xd0|(curByte&0x0f));
                        #endif           
#elif defined( QSI_SETUP_MENU_DESIGN)           
                        if ((curByte&0x0f)==0x0c) curByte=(0x08|(curByte&0xf0));
                        if ((curByte&0xf0)==0xc0) curByte=(0x80|(curByte&0x0f));                
#elif defined(ALCO_DVD_UI)&&defined(DVD_SETUP_REENG)
                        ;
#else
                        if ((curByte&0x0f)==0x06) curByte=(0x01|(curByte&0xf0));
                        if ((curByte&0xf0)==0x60) curByte=(0x10|(curByte&0x0f));
                    
#endif
                    }
                    else
                    {
#ifdef SETUP_COLOR_TYPE2
                        #ifdef  ALCO_MODIFY_PAL_OSD
                        if ((curByte&0x0f)==0x06) curByte=(0x05|(curByte&0xf0));
                        if ((curByte&0xf0)==0x60) curByte=(0x50|(curByte&0x0f));
                        #elif defined(INDIGO_STYLE_OSDUI) // change the icon color when the page be pressed.
			    		curByte = (((curByte&0x0f)+4) | ((((curByte&0xf0)>>4)+4)<<4));
                         #else
                        if ((curByte&0x0f)==0x06) curByte=(0x07|(curByte&0xf0));
                        if ((curByte&0xf0)==0x60) curByte=(0x70|(curByte&0x0f));
						#endif
#elif defined(ALCO_DVD_UI)&&defined(DVD_SETUP_REENG)
                        if ((curByte&0x0f)==0x06) curByte=(0x05|(curByte&0xf0));
                        if ((curByte&0xf0)==0x60) curByte=(0x50|(curByte&0x0f));                        
#endif//#ifdef SETUP_COLOR_TYPE2
                        
                    }   

                    if (need_gray==1)
                    {
                        if ((curByte&0x0f)!=0x01) curByte=(0x0b|(curByte&0xf0));
                        if ((curByte&0xf0)!=0x10) curByte=(0xb0|(curByte&0x0f));                        
                    }

                    #endif //PHILIPS_SETUP
                    pixel8 = pixel8 | (curByte<<8*k);    
                }
                pp[iDispLoc+i] =  pixel8;
            }
            yStart++;
        }//for icon heigh  
    }
#ifdef SUPPORT_SW_OSD_SCALING

    if( ((GET_TV_RESOLUTION()  == HD_720) || (GET_TV_RESOLUTION()  == HD_1080)) && IS_OSD_SCALE_BUF_OK() ) {
        osd_region_scaling(0, &scale_section);
    } 
#endif

    timeout_osd[0] = 0;
}

#endif//NEW_STYLE_SETUP


/**************************************************************************
 *  Function Name: osd_DrawRegionLine                                     *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_DrawRegionLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth, BYTE r)
{    
    osd_tog_region(r, OSD_ON);
    
    lineWidth+=1;
       
    if (yStart==yEnd)
    {
        //draw horizontal line
        osd_draw_horizontal_line(xStart, xEnd, yStart, color, lineWidth, r);                
    }
    else
    {
        //draw vertical line
        osd_draw_vertical_line(xStart, yStart, yEnd, color, lineWidth, r);        
    }
    
    timeout_osd[r] = 0;
}


/**************************************************************************
 *  Function Name: osd_DrawLine                                           *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *    draw a horizontal line or vertical line                             *
 *  Arguments:                                                            *
 *    xStart      -> line start x(units in pixel)                         *
 *    yStart      -> line start y                                         *
 *    xEnd        ->                                                      *
 *    yEnd                                                                *
 *    color       -> line color                                           *
 *    lineWidth   -> line width                                           *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_DrawLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth)
{
    osd_DrawRegionLine(xStart,yStart,xEnd,yEnd,color,lineWidth,SETUP_REGION);
}


/**************************************************************************
 *  Function Name: osd_draw_vline_region                                  *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_draw_vline_region(int x, int yStart, int yEnd, unsigned color, int n, int r)
{
    osd_draw_vertical_line(x, yStart, yEnd, color, n, r);
}


/**************************************************************************
 *  Function Name: osd_draw_hline_region                                  *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_draw_hline_region(int xStart, int xEnd, int y, unsigned color, int n, int r)
{
    osd_draw_horizontal_line(xStart, xEnd, y, color, n, r);
}


/**************************************************************************
 *  Function Name: osd_draw_region_rect                                   *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *    fill a rectangular region using bk-Color                            *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_draw_region_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor, BYTE r)
{
    osd_draw_hline_region(xStart, xStart+xLen, yStart, bkColor, yLen, r);
}


/**************************************************************************
 *  Function Name: osd_replace_rect_color                                 *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *    replace bkColor with destColor                                      *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_replace_rect_color(BYTE bkColor, BYTE destColor)
{
    SetOsdCol(0,0,bkColor,palette_16color_setup[destColor]);
}


/**************************************************************************
 *  Function Name: osd_draw_rect                                          *
 *  Purposes:                                                             *
 *    draw a rectangle shape with blanking content                        *
 *  Descriptions:                                                         *
 *    Units in pixel                                                      *
 *  Arguments:                                                            *
 *    xStart      -> x start position to draw                             *
 *    yStart      -> y start position to draw                             *
 *    xLen        -> rectangle width(width of blank area)                 *
 *    yLen        -> rectangle lines(height of blank area)                *
 *    bkColor     -> color index of background color                      *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_draw_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor)
{
#ifdef NEWSTYLE_WINDOW
    if(full_scrn&MESSAGE)
        osd_draw_region_rect(xStart, yStart, xLen, yLen, bkColor, arc_region_loc.region);
    else
#endif
        osd_draw_region_rect(xStart, yStart, xLen, yLen, bkColor, SETUP_REGION);
}


/**************************************************************************
 *  Function Name: osd_draw_button_outline                                *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_draw_button_outline(int x1, int y1, int x2, int y2, int bDown, unsigned mask, int r)
{
    coordinate  start, end;
    
    start.x = x1;
    start.y = y1;
    
    end.x = x2;
    end.y = y2;
        
    osd_draw_button_border(&start, &end, bDown, mask, r);
}


/**************************************************************************
 *  Function Name: osd_draw_setup_button                                  *
 *  Purposes:                                                             *
 *    draw a setup-item button                                            *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *    xStart      -> x start position to draw                             *
 *    yStart      -> y start position to draw                             *
 *    xLen        -> record length                                        *
 *    color       -> button color                                         *
 *    bDown       -> UP(0) or DOWN(1)                                     *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_draw_setup_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown __UNUSED)
{
    unsigned    buttonC;
    UINT32      xNew, yNew;
    
    buttonC = color;
    
#ifdef NEW_SETUP_OSD             // majinping 2002-05-02 for new setup menu
    if (full_scrn&CUSTM) 
    { //set to CUSTM mode    
        if (bDown) {
            //button is pressed(down)
            uBorderC = 11;  //upper border color
        dBorderC = 2;   //rear border color
        } else {
            //button is up
        uBorderC = 2;
        dBorderC = 11;
    }
        
        xNew = xStart * 16;
        yNew = yStart * SETUP_BTN_HEIGHT;
        
        osd_draw_rect(xNew, yNew, xLen*16, SETUP_BTN_HEIGHT, buttonC);
        
        //draw upper border
        osd_DrawLine(xNew, yNew, (xNew+xLen*16), yNew, uBorderC, 1);
        //draw rear border
        osd_DrawLine(xNew, (yNew+SETUP_BTN_HEIGHT-2), (xNew+xLen*16), (yNew+SETUP_BTN_HEIGHT-2), dBorderC, 1);
        //draw left border
        xNew = xStart * 16;
        yNew = yStart * SETUP_BTN_HEIGHT;
        osd_DrawLine(xNew, yNew, xNew, yNew+SETUP_BTN_HEIGHT, uBorderC, 1);
        //draw right border
        xNew = (xStart+xLen) * 16 - 1;
        yNew = yStart * SETUP_BTN_HEIGHT;
        osd_DrawLine(xNew, yNew, xNew, yNew+SETUP_BTN_HEIGHT, dBorderC, 1);
    }    
    if( yStart == SETUP_MAIN_YSTART )
    {
        xNew = xStart * 16;
        yNew = yStart * SETUP_BTN_HEIGHT + 13;
        osd_draw_rect(xNew, yNew, xLen*16, SETUP_BTN_HEIGHT+5, buttonC);
    }
    else
    {
        xNew = xStart * 16;
        yNew = yStart * SETUP_BTN_HEIGHT;
        osd_draw_rect(xNew, yNew, xLen*16, SETUP_BTN_HEIGHT, buttonC);       
    }
#else
    
    xNew = xStart * 16;
#ifdef INDIGO_STYLE_OSDUI
    yNew = yStart * SETUP_BTN_HEIGHT-2; // ?? sub 2 mimitsai
#else
    yNew = yStart * SETUP_BTN_HEIGHT;   
#endif    
    osd_draw_rect(xNew, yNew, xLen*16, SETUP_BTN_HEIGHT, buttonC);
    
    #if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)&& !defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-5 12:32
        #ifndef SETUP_NOBUTTON       //2004-4-17 10:22张宇M
    osd_draw_button_outline(xNew, yNew, xNew+xLen*16-1, yNew+SETUP_BTN_HEIGHT-1, bDown, 0x0f, SETUP_REGION);
        #endif
    #endif
#endif
}


/**************************************************************************
 *  Function Name: osd_draw_sound_button                                  *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_draw_sound_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown)
{
    BYTE        buttonC;
    UINT32      xNew, yNew;    
    coordinate start, end;
    
    buttonC = color;    
    xNew = xStart * 16;
    yNew = yStart * SETUP_BTN_HEIGHT+12;    
    osd_draw_region_rect(xNew, yNew, (UINT32)(xLen*16), (UINT32)(SETUP_BTN_HEIGHT), buttonC,3);    
    
    start.x = xNew;
	start.y = yNew;
	end.x = (UINT16)(xNew+xLen*16);
	end.y = (UINT16)(yNew+SETUP_BTN_HEIGHT-2);
	osd_draw_button_border(&start, &end, bDown,0x0f,3);
}


/**************************************************************************
 *  Function Name: draw_osd_board                                         *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void draw_osd_board(UINT8 r, UINT8 board_type)
{
    int     i;
    int     w=region[r].osd_w;
    int     h=region[r].osd_h;
    BYTE    *pTopLine,*pBtmLine;
    
    pTopLine = get_osdbuf_region_ptr(r,0);
    pBtmLine = get_osdbuf_region_ptr(r,1);
    
    if(p_scan==0) h>>=1;    
    if(board_type&BOARD_UP_LINE)
    {           
        BYTE x_start;
#ifdef USE_NEW_SCHINESE_OSD
        if (r==1) x_start=0; else x_start=15;
#else
        if (r==1) x_start=0; else x_start=19;
#endif
        for (i=x_start;i<w;i++) 
        {
            pTopLine[i] =  0x55;
            pBtmLine[i] =  0x55;
        }
    }
    
    if(board_type&BOARD_DOWN_LINE)
    {   
        if (r!=1)
        {
            for (i=(h-1)*w;i<(h*w);i++) 
            {
                pTopLine[i] =  0x55;
                pBtmLine[i] =  0x55;
            }
        }
    }
    
    if(board_type&BOARD_LEFT_LINE)
    {   
        for(i=0;i<(h*w);i+=w) 
        {
            pTopLine[i] |=  0x40;
            pBtmLine[i] |=  0x40;                   
        }
    }
    
    if(board_type&BOARD_RIGHT_LINE)
    {   
        for(i=w-1;i<(h*w);i+=w) 
        {
            pTopLine[i] =  0x55;
            pBtmLine[i] =  0x55;                   
        }
    }
}    


/**************************************************************************
 *  Function Name: osd_print_eq_setting                                   *
 *  Purposes:                                                             *
 *    Draw EQ setting status on screen by OSD                             *
 *  Descriptions:                                                         *
 *    The each freq energy 0 ~ 24                                         *
 *  Arguments:                                                            *
 *    r: region for draw                                                  *
 *    unSele: which frequency is choice now                               *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
#include "Sound_def.h"
extern void    osd_print_eq_setting(UINT8 r,UINT8 unSele)
{
    BYTE    *p;
    UINT16    i,j,iBlock;
    UINT16    unColor;    
    BYTE    bChannelVal[MAX_BAND*2];
    coordinate  start;
    dimension   out_dimension;
    
    start.y = EQ_YSTART;
    out_dimension.x_length = RECT_WIDTH_PIXEL;
    out_dimension.y_length = RECT_HEIGHT;

    //calcuate the interpolate data
    //The data is mapping to 0 ~ 24
    p=&RegionValStr[r][0];
        
    for (i=0;i<MAX_BAND*2;i=i+2)
    {
        bChannelVal[i]=MAX_VOLUME-*p;
        bChannelVal[i+1]=MAX_VOLUME-((*(p)+*(p+1))/2);
        p++;
    }
           
    //Totally has 25 block for each freq (0 ~ 24 )    
    for (j=0;j<25;j++)
    {      
        start.x = EQ_XSTART_PIXEL;
        
		for (iBlock=0;iBlock<MAX_BAND*2-1;iBlock++) 
        {    
            //make sure color
			if (j==bChannelVal[iBlock])//center
        	{
                if (unSele==iBlock)
            		unColor=EQ_CURSOR_CENTER_RECT;//DRK_GREEN_COLOR
                else                
            		unColor=EQ_SELECTED_CENTER_RECT;//YELLOW_COLOR
        	}
			else //others
			{
	            if (unSele==iBlock)
            		unColor=EQ_CURSOR_OTHER_RECT;//GRAY_COLOR
                else
            		unColor=EQ_SELECTED_OTHER_RECT;//GRAY_COLOR

			}
			start.x += RECT_XOFFSET_PIXEL;
			
			osd_draw_rectangle(&start, &out_dimension, unColor, r);    			
        }
                        
        start.y += RECT_YOFFSET;
    }
}


/**************************************************************************
 *  Function Name: osd_Move2OSD0                                          *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *    Bytes/Line = 37*16*4/8 = 296                                        *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_Move2OSD0(BYTE iLine)
{
#ifndef SDRAM_16Mb_Mode
    UINT32  *buf;
#endif
    UINT32  *pTopLine, *pBtmLine;
    BYTE    i,end,max_remain,step;
    int  j, k;    
    
    
#ifdef DISP_REGION_BOTTOM
    UINT8 uiRegion = OSD_GetTrueDispRegion();
#else
    UINT8 uiRegion = 0;
#endif
    
    int	iRegionWidth = region[uiRegion].osd_w;
    int	iRegionHeight = region[uiRegion].osd_h;
    if (full_scrn&SETUP) return;
        
    if (iLine > iRegionHeight) return;
#ifdef MP3_NO_DISPLAY    //2004-4-22 04:40张宇P
    if(!Is_MP3_STATE())
#endif
        osd_tog_region(uiRegion, OSD_ON);  

#ifndef SDRAM_16Mb_Mode
    #ifdef OSD_VARIABLE_TEMP_DISPLAY_BUF
        //move the display bar data of temp region  to disp region
        temp_region_top_buf = (UINT32 *)get_osdbuf_region_ptr(temp_region,0);
        temp_region_bottom_buf = (UINT32 *)get_osdbuf_region_ptr(temp_region,1); 
    #else
        extern  UINT8   osd_temp_buf[];
    	buf = (UINT32 *) osd_temp_buf;
	#endif
#endif
    
    //initialize buffer start    
    pTopLine = (UINT32 *)get_osdbuf_region_ptr(uiRegion,0);
    pBtmLine = (UINT32 *)get_osdbuf_region_ptr(uiRegion,1);

    end=iLine;
    max_remain=iRegionHeight;
    step=1;
    if(p_scan==0)
    {
       end>>=1;
       max_remain=iRegionHeight>>1;
#ifdef  OSD_VARIABLE_TEMP_DISPLAY_BUF
        step=1;
#else
       	step=2;
#endif    
    }

#ifndef SDRAM_16Mb_Mode
    for (i=0; i<end; i++) {
		k = iRegionHeight-iLine+step*i;
        
        for (j=0; j<iRegionWidth/4; j++) {
    #ifdef  OSD_VARIABLE_TEMP_DISPLAY_BUF
            pTopLine[iRegionWidth/4*i+j] = temp_region_top_buf[iRegionWidth/4*i+j];
            pBtmLine[iRegionWidth/4*i+j] = temp_region_bottom_buf [iRegionWidth/4*i+j];
    #else  
            //top area
            pTopLine[iRegionWidth/4*i+j] = buf[iRegionWidth/4*k + j];
            //bottom area
            pBtmLine[iRegionWidth/4*i+j] = buf[iRegionWidth/4*(k+1) + j];
    #endif     
        }
    }

    //draw transparent from line-(iLine) to 24-th line
    for (i=end; i<max_remain; i++) {
    	k = iRegionHeight-iLine+step*i;
        for (j=0; j<iRegionWidth/4; j++) {
    #ifdef OSD_BMP_DISPLAY
	        //top area
            pTopLine[iRegionWidth/4*i+j] = 0; //f is the color index(palette_16color_setup) of transparent color
            //bottom area
            pBtmLine[iRegionWidth/4*i+j] = 0; //0 is the transparent color
	#else
            //top area
            pTopLine[iRegionWidth/4*i+j] = 0xffffffff; //f is the color index(palette_16color_setup) of transparent color
            //bottom area
            pBtmLine[iRegionWidth/4*i+j] = 0xffffffff; //0 is the transparent color
	#endif
        }
    }
#else //SDRAM_16Mb_Mode
    {
        //draw transparent from line-(iLine) to 24-th line
        for (i=end; i<max_remain; i++) {
        	k = iRegionHeight-iLine+step*i;
            
            for (j=0; j<iRegionWidth/8; j++) {
                //top area
                pTopLine[iRegionWidth/8*i+j] = 0; //f is the color index(palette_16color_setup) of transparent color
                //bottom area
                pBtmLine[iRegionWidth/8*i+j] = 0; //0 is the transparent color
            }
        }
    }
#endif    //SDRAM_16Mb_Mode

    timeout_osd[uiRegion] = 0;

#ifdef DISP_REGION_BOTTOM
	if(OSD_ShowBottomDisp() == 1)
	{	    
		if(getVPP_TVsystem()&&p_scan)
            osd_set_region_position(disp_region,10,520);
		else if(getVPP_TVsystem())
			osd_set_region_position(disp_region, 10, 260);
		else if (p_scan)
            osd_set_region_position(disp_region,10,432);
		else
			osd_set_region_position(disp_region,10,216);
	}		
#endif//DISP_REGION_BOTTOM
}


/**************************************************************************
 *  Function Name: restore_osd_msg                                        *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
#ifdef  ZOOMOUT_JPEG_ROTATE_NOT_SHOW_ZOOM
    #ifdef JPG_OLD_PARSER_FLOW
        #ifdef JPG_EFFECT
        #include "jpegeffect.h"
        #endif
    #else
        #include "pic_effect.h"
    #endif
#include "ircmd_h.h"
#endif

static void restore_osd_msg(void)
{
    //joshua, 2005.2.2, advoid "display" flashing of switching between "program key" and "mute key"
    if(full_scrn&PROGRAM)
        return;
    
#ifdef NEW_HDMI_FLOW
    UpDateHDMI_StateDisplay();
#endif//NEW_HDMI_FLOW

#ifdef DISPLAY_FBWARD_OSD //zhaoyanhua add 2003-4-4 11:19
    int val=0,id=0;    
        
    if (adv_search_time!=0)
    {
        if( adv_search_time< 0 )
        {  
            val=-adv_search_time;
            id=STR_OS_FB;    
        }
        else if( adv_search_time> 0 )
        {    
            val=adv_search_time;
            id=STR_OS_FF;
        }
            
        PrintOsdMsg(id|(val<<OSDSTR_ID_TOTL_BIT),REGION1,0,6);
                    
    }
    //gerry mark it,2004-3-3 23:49, 2004/12/27 yltseng modify layout
    #ifndef GBM_DVD
    else if(video_slow!=0)
    {
        if(video_slow>0)
        {
            id = STR_OS_SF;
            val = video_slow;
        }
        else
        {
            id = STR_OS_SB;
            val = (-1)*video_slow;
        }        

        PrintOsdMsg(id|(val<<OSDSTR_ID_TOTL_BIT),REGION1,0,7);
    }
    #endif
    else
#endif

#ifdef ALWAYS_SHOW_NO_DISC
    if (system_state==SYSTEM_NODISC)
    {
        PrintOsdMsg(STR_OS_NODISC,REGION1,0,0); // alan, 2003/8/26 04:32PM
    }
    else
#endif

#ifdef ALWAYS_SHOW_STOP  //2004-7-2 03:06?宇P
    if( play_state==VCD_STATE_STOP)
    {
        if(resumeMSF!=0)
        PrintOsdMsg(STR_OS_PRE_STOP,REGION1,0,0); // alan, 2003/8/26 04:32PM
        else
        PrintOsdMsg(STR_OS_STOP,REGION1,0,0);     
    }
    else
#endif
        
#ifdef ALWAYS_SHOW_PROG
    if (prog_cnt)
    {
        PrintOsdMsg(STR_OS_PROGPLAY,REGION1,0,0);   // alan, 2003/8/26 04:32PM
    }
    else
#endif
        
    if( (play_state!=VCD_STATE_OPEN)&&(play_state!=VCD_STATE_STOP)&&(play_state!=VCD_STATE_CLOSE) ) 
    {//disable restore_osd work under screen-saver on mode, Jeff 20020513
        //terry, 0516, addition disable range 
        
        //vpp_zoom:   2~4: zoom in
        show_repeatAB(0);                  

        /*Maoyong 2004.05.21: when rotate a zoom out picture, not show zoom state, because
        the picture is in normal state now*/
#ifdef  ZOOMOUT_JPEG_ROTATE_NOT_SHOW_ZOOM
        static BYTE old_rotate_mode = 0;
        if(vpp_zoom>=ZOOMIN_BASE)
        {
            if( Is_JPEG_STATE() )           
            {
                if( (rotate_mode == 0))         //normal, not rotate
                {
                    #ifndef JPEG_ROTATE_TO_NORMAL_DNOT_SHOW_ZOOM	//liumzh 2004-8-26 0:15
                    if(old_rotate_mode == 0)
                        show_zoom(0);
                    else
                    #endif
                        old_rotate_mode = rotate_mode;
                }
                else                            //in rotate mode!!!
                {
                    if(vpp_zoom <ZOOMOUT_BASE)  //Zoom in
                        show_zoom(0);
                    else                        //Zoom out
                        old_rotate_mode = rotate_mode;
                }
            }
            else                                //other disc, no jpeg
            {
                show_zoom(0);
            }
        }
#else       //else  #ifdef  ZOOMOUT_JPEG_ROTATE_NOT_SHOW_ZOOM             
        if(vpp_zoom>=ZOOMIN_BASE)//terry            
            show_zoom(0);//nono 2-4-24 21:54
#endif      //end   #ifdef  ZOOMOUT_JPEG_ROTATE_NOT_SHOW_ZOOM
        
        #ifdef USE_AMP_MUTE  //chenzhao20060114
        if (user_amp_mute)     
		#else//#ifdef USE_AMP_MUTE
        if (user_mute)     
		#endif//#ifdef USE_AMP_MUTE
            PrintOsdMsg(STR_OS_MUTE,REGION1, 0, 0);         
   
        
        if( ( play_state == VCD_STATE_PAUSE ) && !( full_scrn & PROGRAM ) )//terry,2004/2/4 06:36PM, 2004/12/27 yltseng
            PrintOsdMsg(STR_OS_PAUSE,REGION1, 0, 0);
    }
    
    #ifdef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-5-16 17:42
    #if defined(SPHE8202_CARD_STORAGE) && defined(CARD_SETUP_TYPE_3)
    extern int iIsCardConflict;
    if(iIsCardConflict)
    {
        psprintf(RegionValStr[REGION1], "PLEASE INSERT ONE CARD ONLY");
        PrintOsdMsg(STR_OS_SPACE, REGION1, 0, 1);
    }
    #endif//defined(SPHE8202_CARD_STORAGE) && defined(CARD_SETUP_TYPE_3)
    #endif//DIRECT_ACCESS_MEDIA
}


/**************************************************************************
 *  Function Name: show_angle_osd                                         *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
#include "user_if.h"
#ifdef SWITCH_CD_CARD_USB //winking.J add for DISPLAY 2006 07 17
extern BYTE AngleSwichFlag;
#endif
extern void show_angle_osd(void)
{
#ifdef NO_SHOW_ANGLE_OSD        //kono 021007
    return ;
#endif

    if(cd_type_loaded==CDDVD)
    {
#ifdef SUPPORT_FUNCTION_MENU
        if(full_scrn&PROGRAM) return;//terry,2003/7/31 03:06PM
#else
        if(full_scrn&(PROGRAM|MESSAGE)) return;//terry,2003/7/31 03:06PM
#endif //end #ifdef SUPPORT_FUNCTION_MENU

#ifdef SUPPORT_ANGLE_MARK	//liweihua add for syber 20031118
        if(angleflag == 0){

            if( (get_angle_Ns())&&(!UOP_check(UOP_AG_CHG)) ) {    
                PrintOsdMsg(STR_OS_ANGLE,REGION2,0,0);
            } else if (RegionOnOff[REGION2][2]==STR_OS_ANGLE)
            {
                osd_tog_region(2,OSD_OFF);
            }
        }
        else{
            if( (get_angle_Ns())&&(!UOP_check(UOP_AG_CHG)) ) {
                } else if (RegionOnOff[REGION2][2]==STR_OS_ANGLE)
                {
                     osd_tog_region(2,OSD_OFF);
                }
        }
#else
        if( (get_angle_Ns())&&(!UOP_check(UOP_AG_CHG)) 
			#ifdef SWITCH_CD_CARD_USB//winking.J add for DISPLAY 2006 07 17
			&&(AngleSwichFlag == 0)
			#endif
			) 
            {          
            #ifdef SHOW_ANGLE_MARK_THEN_CLOSE
            #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
            if(source_play_mode == DVD_PLAY_MODE)
            #endif
            PrintOsdMsg(STR_OS_ANGLE,REGION2,2,0);
            #else
            PrintOsdMsg(STR_OS_ANGLE,REGION2,0,0);
            #endif
  
        } else if ((RegionOnOff[REGION2][2]==STR_OS_ANGLE)
        #ifdef SWITCH_CD_CARD_USB //winking.J add for DISPLAY 2006 07 17
		||(AngleSwichFlag == 1)
		#endif
		)
        {
        #ifdef SWITCH_CD_CARD_USB //winking.J add for DISPLAY 2006 07 17
		AngleSwichFlag = 0;
		#endif
            osd_tog_region(2,OSD_OFF);
        }
#endif
    }
}


/**************************************************************************
 *  Function Name: chg_anti_pos                                           *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *    terry,2004/1/26 01:05PM                                             *
 *               vcd   dvd1   dvd2                                        *
 *    mode        2     2      2                                          *
 *    mode2       2     3      4                                          *
 *    s_len(0-8)  6     7      7                                          *
 *    s_len(9-16) 7     8      8                                          *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
static inline void chg_anti_pos(UINT8 mode2,UINT8 s_len)
{//edit prog id
  
  printf("1.antic_begin:%d antic_end:%d mode2:%d s_len:%d\n",antic_begin,antic_end,mode2,s_len);                    
  antic_begin+=2;
  
  switch(mode2)
  {
    case 2://vcd prog
       antic_end++;
#ifdef MP3_DIRECT_SELECT//7,8
       if(s_len>=7)  antic_begin+=(s_len-7+1);
#else       
       if(s_len==7)  antic_begin++;
#endif       
       break;
    case 3://dvd prog left side
       antic_end=antic_begin+s_len/2;
       if(s_len==8)  antic_begin++;
       break;
    case 4://dvd prog right side
       antic_end++;
       antic_begin=antic_begin+s_len/2;
       break;
  }   
  printf("2.antic_begin:%d antic_end:%d\n",antic_begin,antic_end);
}


/**************************************************************************
 *  Function Name: PrintOsdMsg                                            *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *    mode2    0:sw region on 1:sw region off 2:sw region anti            *
 *    id       1st~3th bytes: numeric use                                 *
 *             4th byte: osd string id                                    *
 *    r        MSB 4bits:software region                                  *
 *             LSB 4bits:hardware region                                  *
 *    t        time unit (second)                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
#ifdef VIRTUAL_KEYBOARD // alan, 2003/8/18 08:47PM
    #define VK  KEYBOARD
#else
    #define VK  0
#endif

#ifdef DOUBLE_TITLE // SUSU ADD
    #define DT  DOUBLETITLE
#else
    #define DT  0
#endif

#ifdef NEWSTYLE_WINDOW
    #define MG  MESSAGE
#else
    #define MG  0
#endif

#define NOT_SHOW_OSD (VK|DT|MG|MARK|GOTO|SCORE)

#include "Icon.h"

/**************************************************************************
 *  Function Name: osdshowProgStr                                         *
 *  Purposes:  show INDIGO_STYLE_OSDUI program                                    *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also: osdshow                                                     *
 **************************************************************************/
#ifdef INDIGO_STYLE_OSDUI
extern void osdshowProgStr(UINT8 r,char *buf)//2-8-1 20:15
{   
    BYTE y_start,x_start, temp=0;
    coordinate  start; 
    start.x = 0;
    start.y = 0;
    temp = strlen(buf);

    x_start = 0;
    y_start = 0;

    if(buf[0])
    {
        if (full_scrn&PROGRAM)
        {    
            y_start=3;
            x_start=8;                                                                
        }
        start.x = x_start*4;
		start.y = y_start*12*(r-1)+30;
		if(r == 7) // play/clear region
		{
			start.x = 340;	
			start.y = 265;	
		}
		//printf_w(" start.x:%d, start.y:%d\n\n", start.x, start.y);
		osd_draw_string(&start, buf, 5, 6, 1, 0);  //3->font color, 0->bkg color

/*          //disable for HD bug issue by robert.chang, 2006-08-09
		if(0)//(r == 7)
		{
			// 2006-03-06, mimitsai add for arranging the play/reset layout.			
			osd_draw_region_rect(start.x+95, start.y,  5, 24, 1, 1); // draw rect between play/clear
			osd_draw_region_rect(start.x-45, start.y, 45, 24, 6, 1); // draw rect before play.
		}
*/		
		
        antic_begin=antic_end=0;
        osd_tog_region(r,OSD_ON); 
    }
}
#endif // INDIGO_STYLE_OSDUI
extern void PrintOsdMsg(UINT32 id,UINT8 r,int t,BYTE mode)
{  
#ifdef SUPPORT_16BIT_OSD
    if(OSD_buffer_16bit) {return;}
#endif	

#if defined(SUPPORT_DVB_GUI_NEW) //Jack added 05/07/27
    if(Is_Dvb_State())
        return;
#endif

#ifdef FIX_DVB_SHOW_OPEN//tianye 200607
extern   UINT8 DVD2DVB_switch_flag;
  if((id == STR_OS_OPEN)&&(DVD2DVB_switch_flag == 1))
  {
	return;
  }
#endif//end=>#ifdef FIX_DVB_SHOW_OPEN
    BYTE sub_r,i,mode2,s_len=0,j,osd_id;
    UINT16 val;

#ifdef ALCO_DVD_UI
    if(safe_on)
        return;
#endif

#if defined(PAL_VERSION)&&defined(UNLOCK_STATE_NOT_CHECK_PASSWD)
    if(disc_has_unlock == 0xf0)
        return;
#endif
    
    osd_printf("PrintOsdMsg(%d,%d,%d,%d)\n", id, r, t, mode);
    
    // mode2    0:sw region on 1:sw region off 2:sw region anti
    // id       1st~3th bytes: numeric use  
    //          4th byte: osd string id
    // r        MSB 4bits:software region
    //          LSB 4bits:hardware region
    // t        time unit (second)
      
#ifdef SDRAM_16Mb_Mode   //2004-5-5 10:44?宇P
    if( (id==STR_OS_STOP)&&(system_state==SYSTEM_NODISC) )
        return;
#endif

#ifdef NEW_STYLE_SETUP
    if( (id==STR_OS_STOP)&&(setup_state==1) )
        return;
#endif//NEW_STYLE_SETUP 

/*
    Maoyong Marked: 
    for Bug: When PBC ON, "STOP" then PLAY, will show "PBC", not
            "MENUPLAY", because you have change in ircmd.c, don't need
             to change MENUPLAY to PBC again
*/
#if defined(VCD_SHOW_PBC_NOT_MENUPLAY)&&defined(TONIC_DVD)//20040206 FOR TONIC
    if(cd_type_loaded==CDVCD20||cd_type_loaded==CDSVCD)
    {
        if((id&0xff)==STR_OS_MENUPLAY)
        {
            id&=0xffffff00;
            id|=STR_OS_PBC;
        }
    }
#endif
    
#ifdef SUPPORT_FUNCTION_MENU
    if ((full_scrn&SETUP) || (full_scrn&SETUP_PLUS))
#else
    if (full_scrn&SETUP)
#endif //end #ifdef SUPPORT_FUNCTION_MENU
    {
        return;
    }
    
    sub_r=r>>4;    
    r=r&0x0f;
    mode2=mode>>4;
    mode=mode&0x0f;
    osd_id=id&0xff;
    val=id>>OSDSTR_ID_TOTL_BIT;//nono 20020708

#ifdef NEWSTYLE_WINDOW //terry,2003/8/4 03:24PM   
    if(full_scrn&MESSAGE)
        memset(osdbuf,0,sizeof(osdbuf));
#endif

#ifdef DOUBLE_TITLE //susu 2003-8-26 19:41
    if(full_scrn&DOUBLETITLE)
        memset(osdbuf,0,sizeof(osdbuf));
#endif
     
    if(full_scrn
		#ifdef GPS_DVD//frank.huang 050907
		&&(full_scrn!=TOUCH_KEYBOARD)
		#endif
	)
    {//terry,2004/1/29 01:09PM
        if( !( full_scrn&NOT_SHOW_OSD ) ) //terry,2004/1/20 05:59PM
        {
            if( (osd_id==STR_OS_STOP)||(osd_id==STR_OS_PLAY) )
                return;
        }
    }
    
    if(mode2!=1)
    {
        switch(mode)
        {
        #ifdef OP_JPEG_ZOOM_LEVEL //libing 2005-6-9 13:57
        case 9:	
            strcpy(osdbuf,_OsdMessegeFont1[osd_font_mode][osd_id]);                          
            strcat1(osdbuf,RegionValStr[r]);
            break;
        #endif	
        /************************************************************
        case 8  cat ?
        ************************************************************/
        case 8:
            strcpy(osdbuf,_OsdMessegeFont1[osd_font_mode][osd_id]);
            if( val>1) {
#ifndef TWELVE_ZOOMFACTORS   //fengjl add 2004-05-05 23:41
                psprintf(RegionValStr[r]," %d",val-1);            
#endif
            } else {
                psprintf(RegionValStr[r],": %s",_OsdMessegeFont1[osd_font_mode][STR_OS_OFF]);
            }
            strcat1(osdbuf,RegionValStr[r]);
            break;

        /************************************************************
        case 7  cat "1/?"
        ************************************************************/
        case 7:
            strcpy(osdbuf,_OsdMessegeFont1[osd_font_mode][osd_id]);
            psprintf(RegionValStr[r]," 1/%d",val);                
            strcat1(osdbuf,RegionValStr[r]);
            break;                            

        /************************************************************
        case 6  cat "X ?"
        ************************************************************/
        case 6:
            #ifdef NOT_SHOW_FBSTR
            strcpy(osdbuf,_OsdMessegeFont1[osd_font_mode][STR_OS_SPACE]);
            psprintf(RegionValStr[r],"X %d",val);
            #else
            strcpy(osdbuf,_OsdMessegeFont1[osd_font_mode][osd_id]);

            psprintf(RegionValStr[r]," X %d",val);                
            #endif
            strcat1(osdbuf,RegionValStr[r]);
            break;            

        /************************************************************
        case 4  cat status on ,double click
        ************************************************************/
        case 4:
#ifdef NEWSTYLE_WINDOW//terry,2003/8/4 03:24PM
            if( (full_scrn&MESSAGE)==0 )
#endif          
    
#ifdef DOUBLE_TITLE //susu 2003-8-26 19:19
            if( (full_scrn&DOUBLETITLE)==0 )
#endif              
            {   
                psprintf(osdbuf,"%s"," ");
                         
                strcpy(osdbuf,_OsdMessegeFont1[osd_font_mode][osd_id]);
                strcat1(osdbuf,":");
                s_len=strlen(osdbuf);                                
                j=0;
                for(i=0;i<s_len;i++)
                {                                
                    UINT8           c = osdbuf[i];
                    const UINT8*    p = get_font_entry(0,c);
                    RegionStr[r][sub_r][i]=c;                            
                    if(p!=NULL)
                    {
                        if(p[0]==0x20)                        
                            j++;
                    }                
                }
    
#if !defined(SDRAM_16Mb_Mode)&&!defined(ALCO_PORTABLE)       //shenyj modify for alco 2006/03/27         
                    for(j=j+s_len;j<13;j++)
                        strcat1(osdbuf,"\n");
#endif
            }
                
            switch(val)
            {
            case 0x20://space
            {
                UINT8 *p=0,id1=id&0xff;
                
                p=get_lang_name(id1);                            
#ifdef NEWSTYLE_WINDOW
                if(full_scrn&MESSAGE) //xyy 2003-7-29 14:21                           
                    psprintf(RegionValStr[r],"%s",p);
                else
#endif
                
#ifdef DOUBLE_TITLE //susu 2003-8-26 19:20
                if(full_scrn&DOUBLETITLE)                           
                    {
                    psprintf(RegionValStr[r],"    [%s",p);
                    }
                else
#endif                   
                
                // 16Mb , cut Sub title language/AUD Language(only show 3 words)  
                // zhaoyanhua 2003-11-13 15:42
#if defined(SDRAM_16Mb_Mode)||defined(ALCO_PORTABLE)//shenyj modify for alco 2006/03/27
                #ifdef ALCO_DVD_UI
                #define MAX_ENG_WORDS 3
                #elif defined(AD_HL_USE) 
                     #define MAX_ENG_WORDS 4   // lxg 2006-7-22 02:46
                #else
                #define MAX_ENG_WORDS 2//nono 20031210
                #endif
                
                #if defined(ALCO_DVD_UI)
                if(id1 == STR_OS_AUDIO)
                    psprintf(RegionValStr[r],"%d/%d",(t>>8)+1,pDSV->dAv_AST_Ns);
                else
                {    
                    if((NP_SPSTN&0x3f)==pDSV->dAv_SPST_Ns)
		                psprintf(RegionValStr[r],"%d/%d ",pDSV->dAv_SPST_Ns,pDSV->dAv_SPST_Ns);
		            else
                    psprintf(RegionValStr[r],"%d/%d ",(t>>8)+1,pDSV->dAv_SPST_Ns);
                }
                #else
                psprintf(RegionValStr[r],"[%d",(t>>8)+1);
                #endif//#if defined(ALCO_DVD_UI)
                
            //kevinmonkey 060616 trying to write pointer p is not reasonable, 
            //since it may point to a constant string or read-only memory
                //*(p+MAX_ENG_WORDS) = '\0';
                i = strlen(RegionValStr[r]);
                strncpy(RegionValStr[r]+i, p, MAX_ENG_WORDS);
                *(RegionValStr[r]+i+MAX_ENG_WORDS) = '\0';
                #ifdef ALCO_DVD_UI//shenyj add for alco177w
                //*(p+MAX_ENG_WORDS) = '\0';
                #else
                if (!IsOSDChinese()||((linebuf[0]>='A')&&(linebuf[0]<='Z'))) 
                {
                    ;//*(p+MAX_ENG_WORDS) = '\0';
                }
                else
                {
                    if(strlen(p)>4)
                    {
    #if defined(USE_TCHINESE_OSD)//2-10-9 17:51
                        //psprintf(p+2,"%s",TCh_yu);
                        psprintf((RegionValStr[r]+strlen(RegionValStr[r])),"%s",TCh_yu);
    #else
        #ifdef USE_KOREAN_OSD       //clead korean 2003-10-23 
                        //psprintf(p+2,"%s",KCh_09);
                        psprintf((RegionValStr[r]+strlen(RegionValStr[r])),"%s",KCh_09);
        #else
                        //psprintf(p+2,"%s",Ch_yu2);
                        psprintf((RegionValStr[r]+strlen(RegionValStr[r])),"%s",Ch_yu2);
        #endif
    #endif
                    }
                }
                #endif//end #ifdef ALCO_DVD_UI
                
#else
    #if defined (SUPPORT_SMI_MultiLanguage)
                if(IS_EXT_SUP_ACTIVATED()&&lang_num>1&&SmiSupType)    
                    psprintf(RegionValStr[r],"[ %d - %d %s",(t>>8)+1,nowSupLang+1,p);
           	    else
    #endif
                psprintf(RegionValStr[r],"[ %d %s",(t>>8)+1,p);
                    
#endif//end SDRAM_16Mb_Mode
                    
                if( (id1)==STR_OS_AUDIO )
                {
                    strcat1(RegionValStr[r],get_audio_mode());
                }
                
#ifdef NEWSTYLE_WINDOW
                if(!(full_scrn&MESSAGE)) //xyy 2003-7-29 14:21   
#endif                        
                    #ifndef ALCO_DVD_UI
                    strcat1(RegionValStr[r],"]");
                    #endif
            }
            break;
            
            case 0x0a:
            {
                UINT8 Ns=t>>12;
                UINT8 N=((t>>8)&0xf)+1;
                
                if(N>Ns)
                {
#ifdef NEWSTYLE_WINDOW
                    if(full_scrn&MESSAGE)//xyy 2003-7-29 14:21
                        psprintf(RegionValStr[r],"%s",STR_OS_NONE);//nono 2-11-23 10:49
                    else                        
#endif
                        psprintf(RegionValStr[r],"[ %s ]",STR_OS_NONE);//nono 2-11-23 10:49
                }else
                {
#ifdef NEWSTYLE_WINDOW
                    if(full_scrn&MESSAGE)//xyy 2003-7-29 14:21
                        psprintf(RegionValStr[r],"%d/%d",N,Ns);
                    else                        
#endif
                        psprintf(RegionValStr[r],"[ %d/%d ]",N,Ns);
                }
            }
            break;

            default:

#if defined(SDRAM_16Mb_Mode)||defined(ALCO_PORTABLE) //shenyj modify for alco 2006/03/27               
                #if defined(ALCO_DVD_UI)
                psprintf(RegionValStr[r],"%s",_OsdMessegeFont1[osd_font_mode][val]);
                #else
                psprintf(RegionValStr[r],"[%s]",_OsdMessegeFont1[osd_font_mode][val]);
                #endif
#else 
    #ifdef NEWSTYLE_WINDOW
                if(full_scrn&MESSAGE)//xyy 2003-7-29 14:23
                    psprintf(RegionValStr[r],"%s",_OsdMessegeFont1[osd_font_mode][val]);
                else
    #endif
    
    #ifdef DOUBLE_TITLE
                if(full_scrn&DOUBLETITLE)//susu 2003-8-26 19:51
                    psprintf(RegionValStr[r],"    [ %s ]",_OsdMessegeFont1[osd_font_mode][val]);
                else
    #endif       
                    psprintf(RegionValStr[r],"[ %s ]",_OsdMessegeFont1[osd_font_mode][val]);
#endif
                break;
            }
            
            t=t&0xff;    
            strcat1(osdbuf,RegionValStr[r]);
            break;

        /************************************************************
        case 2  string cat id's string
        ************************************************************/
        case 2:
            strcpy(osdbuf,_OsdMessegeFont1[osd_font_mode][id]);
            strcat1(RegionValStr[r],osdbuf);
            strcpy(osdbuf,RegionValStr[r]);
            break;

        /************************************************************
        case 1  cat string
        ************************************************************/
        case 1:
#if !defined(SDRAM_16Mb_Mode)&& defined(SUPPORT_PLAYBACK_ICON)
            if(osd_id==STR_OS_SCORE) //xyy 2003-11-18 11:06
            { 
                memset(osdbuf,0,sizeof(osdbuf));
                strcat1(osdbuf, OSD_ICON_MIC);
                strcat1(osdbuf,_OsdMessegeFont1[osd_font_mode][id]);
                strcat1(osdbuf,RegionValStr[r]);  
            }
            else
#endif//SDRAM_16Mb_Mode
            {
            strcpy(osdbuf,_OsdMessegeFont1[osd_font_mode][id]);
            strcat1(osdbuf,RegionValStr[r]);
            }
            break;                

        /************************************************************
        case 0  transfer id to string
        ************************************************************/
        case 0:
            strcpy(osdbuf,_OsdMessegeFont1[osd_font_mode][id]);
            break;

#ifndef  DVDRELEASE
        /************************************************************
        default
        ************************************************************/
        default:
            printf("osd err\n");
            while(1);
            break;
#endif                    
        }
    }

#ifdef SUPPORT_PLAYBACK_ICON
    switch (osd_id)
    {
    case STR_OS_PREV:
        #ifndef STR_CONNECT_WITH_ICON
        strcat1(osdbuf, " ");
        #endif
        strcat1(osdbuf, OSD_ICON_PREV);
        break;

    case STR_OS_NEXT:
        #ifndef STR_CONNECT_WITH_ICON
        strcat1(osdbuf, " ");
        #endif
        strcat1(osdbuf, OSD_ICON_NEXT);
        break;
    
    case STR_OS_PLAY:
        #ifndef STR_CONNECT_WITH_ICON
        strcat1(osdbuf, " ");
        #endif
        strcat1(osdbuf, OSD_ICON_PLAY);
        break;

    case STR_OS_PAUSE:
        #ifndef STR_CONNECT_WITH_ICON
        strcat1(osdbuf, " ");
        #endif
        strcat1(osdbuf, OSD_ICON_PAUSE);
        break;

    case STR_OS_STEP:
        strcat1(osdbuf, " ");
        strcat1(osdbuf, OSD_ICON_STEP);
        break;

    case STR_OS_STOP:
        #ifndef STR_CONNECT_WITH_ICON
        strcat1(osdbuf, " ");
        #endif
        strcat1(osdbuf, OSD_ICON_STOP);
        break;

    case STR_OS_PRE_STOP:
        #ifndef STR_CONNECT_WITH_ICON
        strcat1(osdbuf, " ");
        #endif
        strcat1(osdbuf, OSD_ICON_PRE_STOP);
        break;

    case STR_OS_FB:
        #ifndef STR_CONNECT_WITH_ICON
        strcat1(osdbuf, " ");
        #endif
        strcat1(osdbuf, OSD_ICON_FB);
        break;

    case STR_OS_FF:
        #ifndef STR_CONNECT_WITH_ICON
        strcat1(osdbuf, " ");
        #endif
        strcat1(osdbuf, OSD_ICON_FF);
        break;

    case STR_OS_SB:
        #ifndef STR_CONNECT_WITH_ICON
        strcat1(osdbuf, " ");
        #endif
        strcat1(osdbuf, OSD_ICON_SB);
        break;
    #if defined(TONIC_DVD)||defined(FF_DISPLAY_PLAY_ICON)
    case STR_OS_SF:
        strcat1(osdbuf, " ");
        strcat1(osdbuf, OSD_ICON_PLAY);
        break;  
    #endif          
    }
#endif

    if(sub_r)
    {            
        if(full_scrn&PROGRAM)
		  #ifdef INDIGO_STYLE_OSDUI	
            sw_region_len=8;
		  #else
            sw_region_len=9;        
		  #endif
        else
            sw_region_len=12;
        
        sub_r--;
        
        for(i=0;i<MAX_SW_REGION;i++)
        {                
            if((i!=sub_r)&&(RegionStr[r][i][0]==0))
            {
                for(j=0;j<sw_region_len;j++)
                {
				#ifdef INDIGO_STYLE_OSDUI	
					if(r != 7) // 2006-03-06, mimitsai add for arranging the play/reset layout.
				#endif	
                    RegionStr[r][i][j]=0x20;//'\n';//space char
                }
                RegionStr[r][i][j]=0;                    
            }        
        }
        
        if(mode2!=1)
        {//0:on                    
            s_len=strlen(osdbuf);                                
            j=0;
            for(i=0;i<s_len;i++)
            {    
                UINT8           c = osdbuf[i];
                const UINT8*    p = get_font_entry(0,c);
                RegionStr[r][sub_r][i]=c;            
                if(p!=NULL)
                {
                    if(p[0]==0x20)
                        j++;
                }                
            }
			i=0; // 2005-12-27 kevinhow helps mimi to find this bug.
            if( (sw_region_len-s_len-j)>0 )
			{
                for(;i<(sw_region_len-s_len-j);i++)
                {                
                    RegionStr[r][sub_r][i+s_len]=0x20;//'\n';                                            
                }            
			}	
            RegionStr[r][sub_r][i+s_len]=0;                                            
        }   
            
        osdbuf[0]=0;
            
        for(i=0;i<MAX_SW_REGION;i++)
        {
            if( (mode2>=2)&&(i==sub_r) )
            {//terry,2004/1/26 01:06PM
                antic_begin=strlen(osdbuf);
                antic_end=antic_begin+s_len;
                printf("mode:%d\n",mode);
                if(mode==2) chg_anti_pos(mode2,s_len);
            }                
            strcat1(osdbuf,RegionStr[r][i]);                                
        }
    }else
    {
        for(i=0;i<MAX_SW_REGION;i++)
        {                
            RegionStr[r][i][0]=0;                                
        }
    }
    
#ifdef NEWSTYLE_WINDOW  //xyy 2003-7-29 14:04
    if(full_scrn&MESSAGE)
    {
        if(osd_id == STR_OS_ANGLE || osd_id == STR_OS_AUDIO || osd_id == STR_OS_SUBTITLE)
            return;
    }
#endif    

#ifdef DIV_GOTO_DISPLAY//zhaoyanhua add 03-11-2 14:29
/*Maoyong 2004.02.14
  Bug:
  When DVD program, Title and Chapter Prompt will be show in 16 color Mode,
  So it will be enlonged.
*/
    if((r == REGION2) && ((full_scrn & PROGRAM) == 0))
    {
        extern void ClearRegion2(void);

        ClearRegion2();
        osd_DrawRegionString(0,0,osdbuf,7,10,2);
        timeout_osd[REGION2]= t*OSD_TIMEOUT; 
        
        RegionOnOff[r][1]=mode;
        RegionOnOff[r][2]=osd_id;   
        RegionOnOff[r][3]=val;
        
        return;
    }
#endif   
    
#ifdef DOUBLE_TITLE //susu 2003-8-26 20:38
    if(full_scrn&DOUBLETITLE)
            return;
#endif    

    if( (ir_osd_post_show==0)||(r!=1)||(full_scrn&PROGRAM) ) 
    {           
	#ifdef INDIGO_STYLE_OSDUI
	if(full_scrn&PROGRAM) {  // New OSD style for 8202L, the prog region and region 0&1&2 go different osdshow. by robert.chang
		if((r!=1)) // don't draw prog string
			osdshowProgStr(r,osdbuf);
	}
	else 
		osdshow(r,osdbuf);
	#else
        osdshow(r,osdbuf);//2-8-1 20:15
	#endif	
        
    } else {
        //terry,0512,move to ir.c  
        ir_osd_post_show=2;
        strcpy(osd_buf,osdbuf);//too bad...
    }
    
    timeout_osd[r]=t*OSD_TIMEOUT;   
    RegionOnOff[r][1]=mode;
    RegionOnOff[r][2]=osd_id;   
    RegionOnOff[r][3]=val;
}


/**************************************************************************
 *  Function Name: osdshow                                                *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osdshow(UINT8 r,char *buf)//2-8-1 20:15
{    
    BYTE y_start,x_start, temp=0;
    coordinate  start;
    dimension  in_dimension;
#ifndef USE_NEW_SCHINESE_OSD
    int     i=0,trim_num=0;
#endif
    
    start.x = 0;
    start.y = 0;
    temp = strlen(buf);

#ifdef OSD_BMP_REGION1
    x_start = 13;
    y_start = 2;
#else
    x_start = 0;
    y_start = 0;
#endif

    if(buf[0])
    {
        if (full_scrn&PROGRAM)
        {    
            if (r==7) 
                y_start=1; 
            else 
                y_start=3;
                
            x_start=2;                                                                
        }
        else
        {
#ifdef USE_NEW_SCHINESE_OSD
            start.x = 0;  
            start.y = 0;
            in_dimension.x_length=region[r].osd_visible_w;
            in_dimension.y_length=region[r].osd_h;
            osd_draw_rectangle(&start,&in_dimension, 1, r);
#else//#ifdef USE_NEW_SCHINESE_OSD
            //joshua, 2005.8.8, modified for russain/HEBRAIC("\r\x86""\r\x90") to trim '\r' characters
            while( buf[i]!='\0' )
            {
                if(buf[i]=='\r')
                {
                    trim_num++;
                }        
                i++;    
            }
            
            temp = temp - trim_num;
                        
            //printf_w("temp=%d, osd_visible_w=%d\n",temp,region[r].osd_visible_w);
            if(temp*16<region[r].osd_visible_w) //general osd font is 16X24 (pixel)
            {
                start.x = temp*16;
                start.y = 0;                
            }
            else
            {
                //joshua, 2005,6,15, modified for drawing volume string on 16m platform
                start.x = 256;  
                start.y = 0;
                temp = 16;              
            }
            
            in_dimension.x_length=region[r].osd_visible_w - temp*16;
            in_dimension.y_length=region[r].osd_h;
            //printf_w("(%d,%d) [%d,%d]",start.x,start.y,in_dimension.x_length,in_dimension.y_length);
#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR  
	// if OSD support 2 color, use transparent to cover all region domain, robert.chang, 2006/03/16
            osd_draw_rectangle(&start,&in_dimension, 0, r);
#else            
            osd_draw_rectangle(&start,&in_dimension, 1, r);
#endif
            
            //osd_fill_region(r,1);   //color 1 is transparent
#endif//#ifdef USE_NEW_SCHINESE_OSD
        }
  
        start.x = x_start*4;//x_start;
        start.y = y_start;//y_start;
  
	if(full_scrn & PROGRAM) {
		osd_draw_string(&start, buf, 3, 0, r, 0);
	}	
	else {
	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR  
        	osd_draw_string(&start, buf, 1, 0, r, 0);  //1->font color, 0->bkg color  modify by robert.chang, 2006/03/16       
	#else    
        	osd_draw_string(&start, buf, 3, 0, r, 0);  //3->font color, 0->bkg color
	#endif
	}        
	
        antic_begin=antic_end=0;
        
        osd_tog_region(r,OSD_ON); 
    }
}


/**************************************************************************
 *  Function Name: ClearOsdMsg                                            *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
#ifdef ALCO_DVD_UI
void ForceClearOsdMsg(int i)
{ 
    for(; i < osd_active_regions; i++) //kenny add it 2001/5/8
    {
        osd_tog_region(i, OSD_OFF);
        RegionOnOff[i][1] = 0;
        RegionOnOff[i][2] = STR_OS_SPACE;
        RegionValStr[i][0] = 0;
    }
}
#endif

extern void ClearOsdMsg(int i)
{        
#ifdef SUPPORT_FUNCTION_MENU
    if ((full_scrn&SETUP) || (full_scrn&SETUP_PLUS))
#else
    if (full_scrn&SETUP)
#endif //end #ifdef SUPPORT_FUNCTION_MENU 
        return;

    #ifdef ALCO_DVD_UI
    ForceClearOsdMsg(i);
    #else
    for(; i < osd_active_regions; i++) //kenny add it 2001/5/8
    {
        osd_tog_region(i, OSD_OFF);
        RegionOnOff[i][1] = 0;
        RegionOnOff[i][2] = STR_OS_SPACE;
        RegionValStr[i][0] = 0;
    }
    #endif
#if defined(OP_PLAYMODE) && defined(SDRAM_16Mb_Mode)      
	return;
#endif

    show_angle_osd();
    restore_osd_msg();//terry,2002/5/8 05:02と,reduce code
}


/**************************************************************************
 *  Function Name: polling_osd                                            *
 *  Purposes:                                                             *
 *    checking OSD timeout, every time 'diff' RTC ticks is subtracted     *
 *    from OSD timeout.                                                   *
 *  Descriptions:                                                         *
 *    if timeout value is 0 then this check is ignored.                   *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void polling_osd(int diff)
{
    int    i;
    
    if(diff<0) 
        return;
    else if(diff>100)
        diff=100;
    
    for (i=0;i<osd_active_regions;i++)
    {
        int TimeToLive;
        
        if ( (TimeToLive=timeout_osd[i]) != 0 )
        {       
            if ((TimeToLive -= diff)<=0)
            {
                TimeToLive=0;
                PatternMode=0;                
                
#ifdef SUPPORT_FUNCTION_MENU
                setup_menu_plus_timer = 0;
#endif //end #ifdef SUPPORT_FUNCTION_MENU
                
#ifdef BRIGHTNESS_COLOR_KEY
    			if(BriCol_timer && (i==REGION1))
      			{
                    BriCol_timer = 1 ;
    			}
#endif
                if(i==REGION1)
                {   
                    if(now_num_ns)                    
                    {
                        ir_num_select(ir_select_number);
                        TimeToLive=timeout_osd[i];
                    }
                    init_ir_num();                    
#ifdef NEW_UART_COMMAND
                    nCurrentVolMode=VOL_MODE_MAIN;
#endif 
                }
                
                if(!TimeToLive)
                {//terry,2002/5/9 09:20と,avoid new osd msg being off or restore
                    osd_tog_region(i, OSD_OFF);
                    
                    if(i==REGION1)
                    {//terry,2002/4/30 12:08AM
                        restore_osd_msg();//terry,2002/5/8 05:04と,reduce code
//zhaoyanhua add the following sentences. 2003-12-2 17:46
// to avoid when invalid key(),not show OPEN or NO DISC again
#ifdef  ALWAYS_DISPLAY_NODISK
                        if(system_state == SYSTEM_NODISC)    
                        {
                            if((!full_scrn)|| ( !safe_on))
    #ifdef SHOW_SPECIAL_DISC_TYPE //Jack added 04/11/16
                            {
                                if(read_disc_state == 0x0f)
                                    PrintOsdMsg(STR_OS_ERR_DISC,REGION1,2,0);
                                else
                                    PrintOsdMsg(STR_OS_NODISC,REGION1,2,0);//zhaoyanhua add 2003-12-2 17:29
                            }
    #else
                            PrintOsdMsg(STR_OS_NODISC,REGION1,2,0);//zhaoyanhua add 2003-12-2 17:29
    #endif
                        }
#endif//ALWAYS_DISPLAY_NODISK    

#ifdef  ALWAYS_DISPLAY_OPEN     
    #ifdef SETUP_ON_OPEN_VALID          //dingzhy    12/26/2003 9:08PM
                        else if( system_state == SYSTEM_OPEN )
                        {   
                            extern BYTE OpenFlag;
                            if( OpenFlag == 1 )
                            {
                                if((!full_scrn)|| ( !safe_on))
                                    PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);//zhaoyanhua add 2003-12-2 17:29
                            }
                        }
                        else 
                        if(system_state==SYSTEM_READ_TITLE)                   //Alex, Linkconcept, 2004-2-26 10:38
                        {   
                            if((!full_scrn)|| ( !safe_on))
                            PrintOsdMsg(STR_OS_READ,REGION1,0,0);
                        }
    #else
        #ifndef READ_NOSHOW_OPEN//zhangyu 20040611
                        //else if(system_state == SYSTEM_OPEN) 
                        if((system_state==SYSTEM_OPEN) && (CDOpened()))//Jack 20041008
                        {   
                            if((!full_scrn)|| ( !safe_on))
            #ifdef EASTWIN
                            PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);//zhaoyanhua add 2003-12-2 17:29
            #else
                            PrintOsdMsg(STR_OS_OPEN,REGION1,2,0);//zhaoyanhua add 2003-12-2 17:29
            #endif
                        }
        #endif
    #endif                           
#endif                           
    
#ifdef MIC_FUNCTION_KEY 
    #if defined(BBK_DVD)||defined(GBM_DVD)//zhaoyanhua add 2003-11-30 12:25 
                    //when OSD time end, clear the flag.
                    extern BYTE bFuncStep;
                    
                    if(bFuncStep)
                        bFuncStep = 0;
    #endif
#endif

#if defined(Ti3001_OSD_UI_1)||defined(Ti5026_OSD_UI_1)//clead 2-9-20 17:31
                        if(full_scrn==SET_AMP)    full_scrn=0;
#endif            
                    #ifdef WRONG_REGION_DISC_AUTO_TRAYOUT
                    void    ircmd_trayout(void);
                    if(dvd_error == REGION_ERR)
                        ircmd_trayout();
                    #endif
                    }
                    if(i==REGION2)
                    {
#ifdef DIV_GOTO_DISPLAY//zhaoyanhua add 03-10-22 9:17
                    extern BYTE SearchPage ;
                        if(full_scrn&GOTO)
                        {
                        full_scrn = 0;
                            SearchPage = 0;
                            if((get_angle_Ns()) &&(cd_type_loaded == CDDVD)) 
                            {
                                show_angle_osd();
                            }
                            else
                        osd_tog_region(i, OSD_OFF);
                        }
                        else
                            show_angle_osd();
                    //nono,2-6-2 15:44    
#else   
                        #ifndef SHOW_ANGLE_MARK_TEMP //hongfeng add 2005-11-04
                        show_angle_osd();
                        #endif
                     
#endif//end DIV_GOTO_DISPLAY
                    }
                }
                
            } //end of if ((TimeToLive -= diff)<=0)
            
            timeout_osd[i] = TimeToLive;
        }
    } // end of for (i=0;i<REGIONS_ACTIVE;i++)
}



//#ifdef OSD_FONT_API
#if (defined(OSD_FONT_API) || defined(USE_COMMON_OSD_DRIVER))

#include "LanguageUtil.h"
#include "fsGUI.h"
#include "font_lowercase.c"
#define	 lowercase_table	LOWERCASE_FONT_BITMAP

// 2006-03-29, mimitsai add for adjustive font width
#ifdef FONT_WIDTH_ADJUSTMENT
/**************************************************************************
 *  Function Name: polling_osd                                            *
 *  Purposes:                                                             *
 *  	Checking Font actual Width, calculate two gap of left and right   *
 *		of the font.													  *	
 *  Descriptions:                                                         *
 *      The font width is varient, so if we show it dependant on		  *
 *      it's actual font width, the word and string looks fine.			  * 
 *  Arguments:                                                            *
 *		pSrc:		Font source raw data.								  *	
 *		Width:		Font original width.								  *	
 *		Height: 	Font original height.								  *	
 *		uStride:	Font line stride. 									  *	 
 *		color_format: color_format, means 1-bits or 2-bits raw data		  *	 
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
UINT8 LWid =0, RWid; 	// LWid: x coord. of first left sample which have not bg.(0~wid-1)
						// RWid: x coord. of most right sample which have not bg.(0~wid-1)
#define FONTGAP	3
#define LeftTip  LWid
#define RightTip RWid
void CalcuteFontActualWidth(UINT8 *pSrc, UINT8 Width, UINT8 Height, UINT8 uStride,UINT8 color_format)
{
    UINT8 i,j,uBitPosition;
	UINT8* pData;
	pData = pSrc;//set to the first point of the font
	LeftTip = Width - 1;
	RightTip = 0;

	switch(color_format)
	{
		case OSD_FORMAT_4COLOR:
			uBitPosition = 0xc0;
			pData = pData + 2;
			//for(j=0; j < Height; j++)
			for(j=0; j < Height; j+=2)
			{
				//at this time, pData and bitposition point to a single bit represent the first pixel of the line
				for(i=0; i< Width; i++)
				{
					if(((*pData) & uBitPosition)!= 0)
					{
						if(i < LeftTip)	LeftTip  = i;
						if(i > RightTip)RightTip = i;
					}
					uBitPosition = uBitPosition >> 2;
					if(uBitPosition == 0)
					{
						pData 	    += 1;
						uBitPosition = 0xc0;
					}
				}
				pData = pData + ((uStride - Width)/8);
				for(i = 0; i < (uStride - Width)%8; i++)
				{
					uBitPosition = uBitPosition >> 2;
					if(uBitPosition == 0)
					{
						pData        = pData + 1;
						uBitPosition = 0xc0;
					}
				}
				//at this moment, pData and BitPosition points to the first pixel of next line
			}
			break;	
			
		case OSD_FORMAT_2COLOR:
			uBitPosition = 0x80;
			//for(j=0; j < Height; j++)
			for(j=0; j < Height; j+=2)
			{
				//at this time, pData and bitposition point to a single bit represent the first pixel of the line
				for(i=0; i< Width; i++)
				{
					if(((*pData) & uBitPosition)!= 0)
					{
						if(i < LeftTip)	LeftTip  = i;
						if(i > RightTip)RightTip = i;
					}
					uBitPosition = uBitPosition >> 1;
					if(uBitPosition == 0)
					{
						pData 	    += 1;
						uBitPosition = 0x80;
					}
				}
				pData = pData + ((uStride - Width)/8);
				for(i = 0; i < (uStride - Width)%8; i++)
				{
					uBitPosition = uBitPosition >> 1;
					if(uBitPosition == 0)
					{
						pData        = pData + 1;
						uBitPosition = 0x80;
					}
				}
				//at this moment, pData and BitPosition points to the first pixel of next line
			}
			break;
			
		default:
			break;
	}
	//printf_w("original :(%d,%d), \n",LeftTip, RightTip);	
	if(LeftTip > RightTip)
	{
		LeftTip  = 0;
		RightTip = Width - 1;
	}
	else
	{
		if(LeftTip < FONTGAP)
			LeftTip   = 0;
		else 
			LeftTip  -= FONTGAP;

		RightTip += FONTGAP;

		if(RightTip > (Width - 1))
			RightTip  = Width - 1;
	}
}
#undef LeftTip
#undef RightTip
#endif //#ifdef FONT_WIDTH_ADJUSTMENT


UINT8 preProcess_and_draw_font(coordinate start, dimension dimen,UINT8* pBmp, BYTE fontcolor __UNUSED, BYTE r, UINT8 font_byte)
{
	const BYTE  *pFont;
	const UINT8*  pFonttem;
    UINT8 uiWidth, uiHeight,WidthTmp;
	
	if(font_byte == 1)
	{
    	if( !langGetFontSize( &uiWidth, &uiHeight ) )
        	return 0;
	}
	else
	{
		uiWidth = dimen.x_length;
		uiHeight= dimen.y_length;
	}

	DrawAttribute draw_bmp_attribute;
	draw_bmp_attribute.start.x = start.x;
	draw_bmp_attribute.start.y = start.y;
	draw_bmp_attribute.bmp_dimension.x_length = uiWidth;
	draw_bmp_attribute.bmp_dimension.y_length = uiHeight;
	draw_bmp_attribute.region_index = r;
	draw_bmp_attribute.p_bmp =  pBmp;
	draw_bmp_attribute.draw_type.is_reference_palette = 1;
	draw_bmp_attribute.draw_type.bits_a_pixel = 1;
	draw_bmp_attribute.draw_type.only_fore_color = 1;
	draw_bmp_attribute.bmp_offset.draw_start.x = 0;
	draw_bmp_attribute.bmp_offset.draw_start.y = 0;
	draw_bmp_attribute.bmp_offset.draw_dimension.x_length = uiWidth;
	draw_bmp_attribute.bmp_offset.draw_dimension.y_length = uiHeight;
	#ifdef ALCO_DVD_UI//shenyj add 2006-9-7 08:45下午
	UINT16 color_palette[]={0, 2, 0, 0};
	#else
	UINT16 color_palette[]={0, 3, 0, 0};
	#endif
	draw_bmp_attribute.p_palette = color_palette;

	WidthTmp = uiWidth;

	//first stage=============================================
	if(font_byte == 1)
	{
	    UINT8 uiScaleX, uiScaleY;
	    langGetScale( &uiScaleX, &uiScaleY );
	    
	    if( uiScaleX != 1 || uiScaleY != 1 )
	    {
	        #define FSJPEG_BUF_OFFSET  ( ( sizeof( FSJPEGDATA ) >> 2 ) << 2 )    
	        pFont    = draw_bmp_attribute.p_bmp;
			pFonttem = (const UINT8*) ( (UINT32)pFsJpeg + FSJPEG_BUF_OFFSET );
			EnlargeFontSize( (UINT8*) pFonttem, pFont, uiWidth, uiHeight, uiScaleX, uiScaleY );
	        uiWidth     *= uiScaleX;
	        uiHeight    *= uiScaleY;

			draw_bmp_attribute.p_bmp = pFonttem;
			draw_bmp_attribute.bmp_dimension.x_length = uiWidth;
			draw_bmp_attribute.bmp_dimension.y_length = uiHeight;
			draw_bmp_attribute.bmp_offset.draw_dimension.x_length = uiWidth;
			draw_bmp_attribute.bmp_offset.draw_dimension.y_length = uiHeight;

			WidthTmp = uiWidth;
	    }
	}

	//second stage=============================================
	#ifdef SUPPORT_FONT_OUTLINE
	UINT8 Amount;
	pFont = draw_bmp_attribute.p_bmp;

	if(font_byte == 1)
	{
		if(uiWidth%8 != 0)
		{
			#define FSJPEG_BUF_OFFSET  ( ( sizeof( FSJPEGDATA ) >> 2 ) << 2 )	
			OSD_AdjustFontWidth( (UINT8*) pFonttem, pFont, uiHeight, uiWidth);
	   	    Amount = ((uiWidth+4)/8)*(uiHeight);
			uiWidth += 4;
		}                                             
	    else
			Amount = (uiWidth/8)*(uiHeight); 
	}
	else
		Amount = 0;
     
    #define FSJPEG_BUF_OFFSET  ( ( sizeof( FSJPEGDATA ) >> 2 ) << 2 )    
	#define FONT_OUTLINE_WIDTH	2
    pFonttem = (UINT8*) ( (UINT32)pFsJpeg + FSJPEG_BUF_OFFSET + Amount);
	OSD_DrawFontFrame((UINT8*)pFonttem,(UINT8*)pFont, uiWidth, uiHeight, FONT_OUTLINE_WIDTH);	

	uiWidth  = pFonttem[0];
	uiHeight = pFonttem[1];

	pFonttem = pFonttem + 2;

	color_palette[0] = 0;
	color_palette[1] = 1;
	color_palette[2] = 1;
	color_palette[3] = 3;
	draw_bmp_attribute.draw_type.bits_a_pixel = 2;
	draw_bmp_attribute.p_bmp =  pFonttem;
	draw_bmp_attribute.bmp_dimension.x_length = uiWidth;
	draw_bmp_attribute.bmp_dimension.y_length = uiHeight;
	draw_bmp_attribute.bmp_offset.draw_dimension.x_length = uiWidth;
	draw_bmp_attribute.bmp_offset.draw_dimension.y_length = uiHeight;

	WidthTmp = uiWidth - 8 + 2*FONT_OUTLINE_WIDTH; 
	#endif

	//second stage=============================================
	#ifdef FONT_WIDTH_ADJUSTMENT
	#include "FontInterface.h"

    ENUM_FONT_TYPE enType = langGetFontType();

    if(!( enType <= FONT_CP_932 && enType <= FONT_CP_950_COMMON ))
    {
	pFont = draw_bmp_attribute.p_bmp;

	if(draw_bmp_attribute.draw_type.bits_a_pixel == 1)
		CalcuteFontActualWidth((UINT8*)pFont, uiWidth, uiHeight, uiWidth, OSD_FORMAT_2COLOR);

	else if(draw_bmp_attribute.draw_type.bits_a_pixel == 2)
		CalcuteFontActualWidth((UINT8*)(pFont - 2), uiWidth, uiHeight, uiWidth, OSD_FORMAT_4COLOR);

    draw_bmp_attribute.bmp_offset.draw_start.x = LWid;
    draw_bmp_attribute.bmp_offset.draw_dimension.x_length = (RWid-LWid+1);

	WidthTmp = (RWid-LWid+1) - 2* FONTGAP;
    }
	#endif

	osd_draw_data(&draw_bmp_attribute);

	return WidthTmp;
}

/**************************************************************************
 *  Function Name: OSD_ShowChar                                           *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
static UINT32 OSD_ShowChar(int x, int y, BYTE c, BYTE fontcolor __UNUSED,BYTE r)  
{
	const BYTE  *pBmp;
    UINT8 uiWidth, uiHeight;
    
    if( ( c >= 'a' ) && ( c <= 'z' ) )
    { 
        int index   = 48 * (c - 97);
        uiWidth     = 16;
        uiHeight    = 24;
        pBmp       = (const BYTE*) (&lowercase_table[index]);
    }
    else
    {
    	pBmp        = get_font_entry(0,c);
        uiWidth     = pBmp[0];
        uiHeight    = pBmp[1];
        pBmp       += 3;
    }

	coordinate start;
	dimension  dimen;

	start.x = x;
	start.y = y;
	dimen.x_length = uiWidth;
	dimen.y_length = uiHeight;

	// the argument of last one means,... 0:table font, 1: font library font.
	return preProcess_and_draw_font(start, dimen, (UINT8 *)pBmp, fontcolor, r, 0);
}



#if defined( ADJUST_SPACE_BETWEEN_FONT ) || defined (SUPPORT_NATIVE_FSNAME) //DENGHG ADD 2005-12-7 02:35   
//#define ADJUST_SPACE_BETWEEN_FONT_DBG
#define FONTSPACEWIDTH  2 //2 pixel. space between font and font  denhg 2006-1-6 06:12     
BYTE LeftNoBGwidth; // if customer need font BGcolor ,it will be used !denghg 2006-6-15 18:55
/*
Now only for FONT_ONE_BYTE  uiWidth = 4 * x  2006-1-6 06:06   
denghg update it  Now it seen more  simpleness and quick 2006-6-15 19:26
*/

//denghg creat 2006-4-24 14:15
//denghg update 2006-9-28 10:11
/**************************************************************************
 *  Function Name: ftGetDrawFontSize                                      *
 *  Purposes:   .                                                         *
 *  Descriptions:  Because if we use 936 or 950,our subtitle font use     *
 *  osd tbl font and library font. ,Theirs size are  different.           *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void   ftGetDrawFontSize(const BYTE* DrawChar, UINT8* pWidth, UINT8* pHeight )
{
    const  BYTE*  pBmp  = NULL;
    BYTE   uiCurChar    = *DrawChar;
    UINT8  uiScaleX     = 0;
    UINT8  uiScaleY     = 0;
    UINT32 uiRtnVal     = langIsInCharacterSet(DrawChar);
	
    if (uiRtnVal != FONT_NOT_IN_RANGE)
    {
        langGetFontSize( pWidth, pHeight ) ;
        langGetScale( &uiScaleX, &uiScaleY );
        *pWidth     *= uiScaleX;
        *pHeight    *= uiScaleY;
    }
    else
    {
        if ((uiCurChar < 32) || (uiCurChar > 126))
{
            uiCurChar = '?';  
            langGetCharacterBmp(&uiCurChar, &pBmp);
	
            if (uiRtnVal == FONT_NOT_IN_RANGE) // use table font
            {
                pBmp        = get_font_entry(0, uiCurChar);
                *pWidth     = pBmp[0];
                *pHeight    = pBmp[1];
            }
            else // font library font
            {
	langGetFontSize( pWidth, pHeight ) ;
    langGetScale( &uiScaleX, &uiScaleY );
    *pWidth     *= uiScaleX;
    *pHeight    *= uiScaleY;
}
        }
        else // use table font
        {    
            if ((uiCurChar >= 'a') && (uiCurChar <= 'z'))
            {              
                 *pWidth     = 16;
                 *pHeight    = 24;             
            }
            else
            {
            	 pBmp        = get_font_entry(0, uiCurChar);
                 *pWidth     = pBmp[0];
                 *pHeight    = pBmp[1];
            } 
        }
    }
    
    #ifdef ADJUST_SPACE_BETWEEN_FONT_DBG
    printf("current font Width %d  uiHeight %d \n ",*pWidth, *pHeight);  
    #endif 
}  
   
/**************************************************************************
 *  Function Name: GetDrawFontBmp                                         *
 *  Purposes:                                                             *
 *  Descriptions:     it can get current Drawing font bmp                 *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
   
extern UINT32  GetDrawFontBmp(const BYTE* DrawChar ,const BYTE** pBmp)
{  
    UINT32 uiRtnVal         = langIsInCharacterSet(DrawChar);
    BYTE   uiCurChar        = *DrawChar;
    const UINT8*  DrawBmp   = NULL;
    const UINT8*  pFont     = DrawBmp;     
    
    #ifdef ADJUST_SPACE_BETWEEN_FONT_DBG
    printf("DrawChar = %c \n",*DrawChar);
    #endif      
    
    if (uiRtnVal != FONT_NOT_IN_RANGE) // it use library font bmp 2006-9-28 10:15
    {
        UINT8 OripWidth       = 0;			    
        UINT8 OripHeight      = 0; 
        UINT8 uiScaleX        = 0;
        UINT8 uiScaleY        = 0;
        
        langGetCharacterBmp(DrawChar, &DrawBmp);
        langGetFontSize(&OripWidth, &OripHeight) ;             
        langGetScale( &uiScaleX, &uiScaleY ); 
        
        if (uiScaleX != 1 || uiScaleY != 1) //font EnlargeFontSize denghg ADD 2006-9-22 9:02
        {
            #define FSJPEG_BUF_OFFSET  ( ( sizeof( FSJPEGDATA ) >> 2 ) << 2 )    
            pFont = (const UINT8*) ( (UINT32)pFsJpeg + FSJPEG_BUF_OFFSET );
            EnlargeFontSize( (UINT8*) pFont, DrawBmp, OripWidth, OripHeight, uiScaleX, uiScaleY );
            DrawBmp = pFont;
        }  
    }
    else
    {
            if ((uiCurChar < 32) || (uiCurChar > 126))
            {                
                uiCurChar = '?';               
                uiRtnVal  = langGetCharacterBmp(&uiCurChar, &DrawBmp);
                                
                if (uiRtnVal == FONT_NOT_IN_RANGE) //it will use OSD TBL font 2006-9-28 10:16
                {
                    DrawBmp        = get_font_entry(0, uiCurChar);
                    DrawBmp       += 3;
                }
    	    }           
            else // it will use OSD TBL font 2006-9-28 10:16
            {
                if ((uiCurChar >= 'a') && (uiCurChar <= 'z'))
                { 
                    int  index   = 48 * (uiCurChar - 97);
                    DrawBmp      = (&lowercase_table[index]);
                }
                else
                {
                	DrawBmp        = get_font_entry(0,uiCurChar);
                    DrawBmp       += 3;
                }
            }
    }
    
    #ifdef ADJUST_SPACE_BETWEEN_FONT_DBG
    printf("DrawBmp = %x \n",DrawBmp);
    #endif   
     
    *pBmp   =  DrawBmp;
    
    return uiRtnVal;
}



/**************************************************************************
 *  Function Name: CntFontContent                                       *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void CntFontContent(const BYTE* pBmp,int uiWidth, int uiHeight,FONTDATA *p)
{    
    
    if (pBmp == NULL)
    {
        p->LeftSpaceWidth  = 0;
        p->RightSpaceWidth = 0;
        
        #ifdef ADJUST_SPACE_BETWEEN_FONT_DBG
        printf(" pBmp = NULL R space :%d, L space: %d \n",p->RightSpaceWidth,p->LeftSpaceWidth);
        #endif 
        
        return;
    }
  
    #define SPACEWIDTH      6      // ' 'width denghg 2006-6-15 18:25
    const UINT8*  pFont   = pBmp;
    UINT8 uiTempWidth     = uiWidth;//bytes

    
    if (uiWidth%8 != 0)
    {
       #define FSJPEG_BUF_OFFSET  ( ( sizeof( FSJPEGDATA ) >> 2 ) << 2 )    
       pFont = (const UINT8*) ( (UINT32)pFsJpeg + FSJPEG_BUF_OFFSET );
       OSD_AdjustFontWidth( (UINT8*) pFont, pBmp, uiHeight, uiWidth);       
	   uiTempWidth = uiWidth + 4;
    }         
    
    
    UINT8 i         = 0;
    UINT8 j			= 0;
    UINT8 n         = uiTempWidth>>3;//bytes  
    UINT8 CntLend   = 0;
    UINT8 CntRend   = 0;
    UINT8 Cntfont[uiTempWidth >> 3]; 
    
    //denghg change it will be quick !!! 2006-6-9 10:24
    for (i = 0; i < n ; i++)  
    {  
        Cntfont[i] = 0;
            
        for (j = 0; j < uiHeight ;j++)
        { 
            Cntfont[i] |= pFont[i + j * n];
        }   
    }
    

    for (i = 0; i < uiTempWidth ; i++ )
    {  
        // left space 
       if ((CntLend != 1) && ((Cntfont[i >> 3] & (0x80 >> (i & 0x07))) == (0x80 >> (i & 0x07)) ) ) //left      
       {
           CntLend           = 1;
           p->LeftSpaceWidth = i;//cntleft space end
       } 
        //right space 
       if ((CntRend != 1) && (((Cntfont[n - 1 - (i >> 3)]) & (0x01 << (i & 0x07))) == ( 0x01 << (i & 0x07))))   
       {   
           CntRend            = 1;
           p->RightSpaceWidth = i - (uiTempWidth - uiWidth);// cntRight Space end;
       }	

       // cnt end
       if (( CntLend ==1) && (CntRend == 1)) 
       {
       	    break ; 
       }
    }  
   
   if (( CntLend == 0) && (CntRend == 0 )) // it is space  ' ' font!!
   {
        p->LeftSpaceWidth  = 0;
        p->RightSpaceWidth = uiWidth - SPACEWIDTH;
   }
   
   #ifdef ADJUST_SPACE_BETWEEN_FONT_DBG
   printf("R space :%d, L space: %d \n",p->RightSpaceWidth,p->LeftSpaceWidth);
   #endif 
}

/***************************************************************************
*  Function Name: PreFontDraw_Position                                     *
 *  Purposes:                                                             *
*  Descriptions:  if we sknow current font LeftSpaceWidth&RightSpaceWidth, *
*  we can adjust font draw position,sknow really drawing width not drawing * 
*  left BGcolor width .  so this Function  is usefulness                   *                     
*    denghg 2006-6-15 18:49                                                *
*  Arguments: uiRealWidth   it is incluse   FONTSPACEWIDTH 2006-6-15 18:52 *                                                      *
 *  Returns:                                                              *
 *  See also:                                                             *
 ***************************************************************************/

extern int PreFontDraw_Position( int* x, const FONTDATA* p ,UINT8 uiWidth, UINT8* NoBGLeftwidth)
{
    #ifdef ADJUST_SPACE_BETWEEN_FONT_DBG
    printf("NOWDrawPOS Ori  %d  uiWidth %d   total spacewidth %d \n",*x, uiWidth , (p->LeftSpaceWidth + p->RightSpaceWidth));
    #endif 
       
	if (p->LeftSpaceWidth >= FONTSPACEWIDTH)
	{
        *NoBGLeftwidth = p->LeftSpaceWidth - FONTSPACEWIDTH;
        *x -= (p->LeftSpaceWidth - FONTSPACEWIDTH);         
    }         
	else
    {
        *NoBGLeftwidth = 0;
        *x += (FONTSPACEWIDTH - p->LeftSpaceWidth);        
    }

    UINT8 uiRealWidth = FONTSPACEWIDTH + uiWidth - p->LeftSpaceWidth - p->RightSpaceWidth ;
       
    #ifdef ADJUST_SPACE_BETWEEN_FONT_DBG
    printf("uiRealWidth :%d , NoBGLeftwidth : %d  NOWDrawPOS %d \n",uiRealWidth,*NoBGLeftwidth,*x );
    #endif 
   
	return uiRealWidth;
    
}

/**************************************************************************
 *  Function Name: Cnt_Subfont_Realwidth                                       *
 *  Purposes:   .                                                         *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/

extern int Cnt_font_Realwidth(const BYTE* pBmp,int uiWidth, int uiHeight	)
{
	if (pBmp == NULL)
	{
    	#ifdef ADJUST_SPACE_BETWEEN_FONT_DBG
        printf("pBmp = NULL RealWidth %d \n",uiWidth);
        #endif
        
	    return uiWidth;	
	}
	
	FONTDATA p;
		
    CntFontContent( pBmp,uiWidth, uiHeight,&p ); 
        
    #ifdef ADJUST_SPACE_BETWEEN_FONT_DBG
    printf("RealWidth %d \n",uiWidth - p.RightSpaceWidth - p.LeftSpaceWidth + FONTSPACEWIDTH);
    #endif
    
    return uiWidth - p.RightSpaceWidth - p.LeftSpaceWidth + FONTSPACEWIDTH;//pixel denghg 2005-12-17 10:37     
}

#endif//#ifdef  ADJUST_SPACE_BETWEEN_FONT //DENGHG ADD 2005-12-7 02:35   


/**************************************************************************
 *  Function Name: OSD_FontShowChar                                       *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
static UINT32 OSD_FontShowChar( int x, int y, const BYTE* pBmp, BYTE fontcolor,BYTE r )
{
	coordinate start;
	dimension  dimen;
	start.x = x;
	start.y = y;

	// the argument of last one means,... 0:table font, 1: font library font.
	return preProcess_and_draw_font(start, dimen, (UINT8 *)pBmp, fontcolor, r, 1);
}


/**************************************************************************
 *  Function Name: OSD_ShowString                                         *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void OSD_ShowString( int x, int y, const char *s, BYTE fontcolor, BYTE r )
{
    const BYTE* p   = s;

    /*if( p_scan ) //libing marked.Note:Because New Style Driver has counted it.
        y = y << 1;*/
        
#ifdef	SUPPORT_FONT_OUTLINE                   //suxin add 2005-09-18
	if(Mp4Subtitle_flag==1)
	{
	    SetOsdCol(3,3,1,__palette4F(0x00,0x00,0x00,0xff));	   //01b:black,frame
	    SetOsdCol(3,3,2,__palette4F(0x00,0x00,0x00,0xff));	   //10b:black,frame
    	    SetOsdCol(3,3,3,__palette4F(0xff,0xff,0xff,0xff));     //11b:white
	    //SetOsdCol(3,3,1,__palette4F(0xff,0x84,0xff,0xff));	   //01b:white,frame
	    //SetOsdCol(3,3,2,__palette4F(0xff,0x84,0xff,0xff));	   //10b:white,frame
    	    //SetOsdCol(3,3,3,__palette4F(0x00,0xff,0x00,0xff));     //11b:blue
	}
#endif       


	while( *p )
	{
       
        const UINT8* pBmp   = NULL;
        
        #ifndef ADJUST_SPACE_BETWEEN_FONT 
        UINT32 uiRtnVal     = langGetCharacterBmp( p, &pBmp );
        #else        
        UINT8   uiWidth         = 0;
        UINT8   uiHeight        = 0;
        int     DrawPos         = x;
        FONTDATA fontP;
        
        ftGetDrawFontSize(p, &uiWidth, &uiHeight );          
        UINT32 uiRtnVal     = GetDrawFontBmp( p, &pBmp );
        CntFontContent(pBmp,uiWidth, uiHeight, &fontP);
        UINT8  RealDrwWidth = PreFontDraw_Position(&DrawPos, &fontP , uiWidth, &LeftNoBGwidth);      
        #endif 
        
        if( uiRtnVal != FONT_NOT_IN_RANGE )
        {
#ifdef SWITCH_SUB_DIRECTION //libing 2005-7-15 14:43
        	if( subtitle_ratate_flag )
                x -= OSD_FontShowChar( x, y, pBmp, fontcolor, r );  // 2004/09/23 yltseng
	        else
#endif
            {
   	            #ifdef ADJUST_SPACE_BETWEEN_FONT //get LeftNoBGwidth,when draw font,no draw BGfontcolor denghg 2006-1-6 05:33         
                langGetCharacterBmp(p, &pBmp );
                OSD_FontShowChar( DrawPos, y, pBmp, fontcolor, r );  
                x += RealDrwWidth;       
                #else
	            x += OSD_FontShowChar( x, y, pBmp, fontcolor, r );
                #endif 

            }   // 2004/09/23 yltseng    
            if( uiRtnVal == FONT_ONE_BYTE )
            {   
                p++;
            }
            else 
                p += 2;
        }
        else
        {
		    BYTE    c   = *p;
            if ( (c < 32) || (c > 126) )
            {
                c = '?';
            }

#ifdef SWITCH_SUB_DIRECTION//libing 2005-7-15 14:43
			if(subtitle_ratate_flag)
			{
				x -= OSD_ShowChar( x, y, c, fontcolor, r );
	        }
            else
#endif
            {
                #ifdef  ADJUST_SPACE_BETWEEN_FONT //denghg modify for TBL font 2006-9-29 9:17
                OSD_ShowChar( DrawPos, y, c, fontcolor, r );
                x += RealDrwWidth;                
                #else
                x += OSD_ShowChar( x, y, c, fontcolor, r );
                #endif
                
            }
            p++;
        }
#ifdef SWITCH_SUB_DIRECTION//libing 2005-7-15 14:43
		if( subtitle_ratate_flag )
		{
			if( x < 0) 
				break;
		}
		else
#endif
		{
    		if( x > region[r].osd_visible_w ) 
    			break;
		}
	}
	
	osd_tog_region( r, OSD_ON );
}

    #if defined(SUPPORT_SMI_MultiColor)//2005-8-16 20:38 zhoulin  
extern void OSD_ShowColorString( int x, int y, const char *s, BYTE *fontcolor, BYTE r )
{
    const BYTE* p   = s;

    if(p_scan)
        y = y<<1;
        
	while( *p )
	{
        const UINT8* pBmp   = NULL;
        UINT32 uiRtnVal     = langGetCharacterBmp( p, &pBmp );
        
        if( uiRtnVal != FONT_NOT_IN_RANGE )
        {
            x += OSD_FontShowChar( x, y, pBmp, *fontcolor, r );  // 2004/09/23 yltseng

            if( uiRtnVal == FONT_ONE_BYTE )
            {
                p++;
                fontcolor++;
            }
            else 
            {
                p += 2;
                fontcolor+=2;
            }
        }
        else
        {
		    BYTE    c   = *p;
            if ( (c < 32) || (c > 126) )
                c = '_';

            x += OSD_ShowChar( x, y, c, *fontcolor, r);
            p++;
            fontcolor++;
        }

		if( x > region[r].osd_visible_w ) 
			break;
	}
	
	osd_tog_region( r, OSD_ON );
}     
    #endif   

#endif //#ifdef OSD_FONT_API


#ifdef SETUPMENU_16Mb_NO_ICON
/**************************************************************************
 *  Function Name: osd_DrawSetupIconString                                *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_DrawSetupIconString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor)
{
    osd_DrawString_ori(xStart, yStart, str, fontColor, bkColor);
}
#endif//SETUPMENU_16Mb_NO_ICON


#if defined( REALCOLOR_SCREENSAVER ) || defined( REALCOLOR_QSI )
/**************************************************************************
 *  Function Name: osd_draw_256color_bmp                                  *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_draw_256color_bmp(int xStart, int yStart, const BYTE* bmp, BYTE r)
{
#ifndef OSD_SUPPORT_256_COLOR
	return;
#else	// #ifndef OSD_SUPPORT_256_COLOR
    UINT32  *pTopLine, *pBtmLine;
    UINT32  iDispLoc;
    
    int     i, j, k;
    int     iFontWidth, iFontHigh;
    int     iRegionWidth = region[r].osd_w;

    osd_tog_region(r, OSD_ON);
    iRegionWidth = region[r].osd_w;
    //initialize buffer start
    pTopLine = (UINT32 *)get_osdbuf_region_ptr(r,0);   // region r top
    pBtmLine = (UINT32 *)get_osdbuf_region_ptr(r,1);   // region r bot
   
    //skip n blank line on top(in pixel)
    //for interlace mode, we will skip n/2 blank lines, for example 4/2=2
    yStart+=2;

    UINT32 pixel4;
    UINT32 pos;

    //get Keyboard bmp information
    iFontWidth  = bmp[0];
    iFontHigh   = bmp[1];

    //start to process
    pos = 2;    
        
    for (j=0; j<iFontHigh; j++)
    {
        int yy;
        UINT32 *pp;
        yy = (p_scan) ? yStart : yStart>>1;
        pp = (yStart&1) ? pBtmLine : pTopLine;

        iDispLoc = (yy*iRegionWidth*2/8) + (xStart);
        for (i=0; i<(iFontWidth/4); i++) // every 4-bytes a time, every 1-pixel a byte
        {
            pixel4=0;
            // 0x12345678  ==>  0x78563412
            for (k=0;k<4;k++)
            {
                unsigned curByte = bmp[pos++];
                pixel4 = pixel4 | (curByte<<8*k);
            }
            pp[iDispLoc+i] =  pixel4;
        }
        yStart++;
    }//for key heigh
    timeout_osd[r] = 0;
#endif	// #ifndef OSD_SUPPORT_256_COLOR
}
#endif


#ifdef NEWSTYLE_WINDOW  //xiongyuyue add 20030630
/**************************************************************************
 *  Function Name: osd_draw_region_arc                                    *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 *    updown == 0,display 凹                                              *
 *    updown == 1,display 凸                                              *
 *    updown > 1 ,normal display                                          *
 **************************************************************************/
extern void osd_draw_region_arc(ARC_REGION_LOC *loc_var,BYTE updown)
{
    BYTE        *pTopLine, *pBtmLine,radius;
    UINT32      iDispLoc, iOffSet;
    UINT32      i, j;
    int         Region;
    int         iRegionWidth = region[loc_var->region].osd_w;
    BYTE        c1;

    if(updown) {}       //wanghaoying 2003-8-12 19:43 added for warning message
    
    //initialize buffer start
    Region = loc_var->region;
    pTopLine = get_osdbuf_region_ptr(Region, 0);
    pBtmLine = get_osdbuf_region_ptr(Region, 1);
    
    radius = loc_var->radius;
    if(p_scan==0)
    {
        loc_var->yLen>>=1;
        loc_var->yStart>>=1;
    }
    
    iDispLoc = (loc_var->yStart * iRegionWidth) + (loc_var->xStart/2);
    
    c1=loc_var->bkColor | (loc_var->bkColor<<4);

    for (j=0; j<loc_var->yLen; j++) 
    {
        //array index(in Byte)
        iOffSet = iDispLoc + j*iRegionWidth;
        for (i=0; i<loc_var->xLen/2; i++) 
        {
            if((i<loc_var->radius)&&(j<radius))//draw left-top corner
            {
                if((arc_tableLT[j][i]==0))
                    continue;
            }
            else if((i >= loc_var->xLen/2-loc_var->radius)&&(j<radius))//draw right-top corner
            {
                if((arc_tableRT[j][i-loc_var->xLen/2+loc_var->radius]==0))
                    continue;
            } 
            else if((i<loc_var->radius)&&(j>=loc_var->yLen-radius))//draw left-bottom corner
            {
                if((arc_tableLB[j-loc_var->yLen+loc_var->radius][i]==0))
                    continue;                    
            }
            else if((j >= loc_var->yLen-radius)&&(i >= loc_var->xLen/2-loc_var->radius))//draw right-bottom corner
            {
                if(arc_tableRB[j-loc_var->yLen+loc_var->radius][i-loc_var->xLen/2+loc_var->radius]==0)
                    continue;
            }
            pTopLine[iOffSet+i] = c1;
            pBtmLine[iOffSet+i] = c1;
        }
    }
    timeout_osd[loc_var->region] = 0;
    osd_tog_region(loc_var->region, OSD_ON);
}
#endif


#ifdef SUPPORT_REP_READ
/**************************************************************************
 *  Function Name: osd_print_read_eq                                      *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
#include "read.h"
extern void osd_print_read_eq(UINT8 r, const BYTE *p)
{
    UINT16  iWidth;
    UINT16  i,j,iBlock,step,k;
    UINT16  *pTopLine,*pBtmLine;
    UINT16  unColor;    
    BYTE    bChannelVal[14];    //byte 13 is garbage

    iWidth = region[r].osd_w/2;
   
    //calcuate the interpolate data
    //The data is mapping to 0 ~ 24    
    for (i=0;i<14;i=i+2)
    {
        bChannelVal[i]=*p;
        bChannelVal[i+1]=(*(p)+*(p+1))/2;
        p++;
    }
    
    //check the last max value
    for (i=0;i<13;i++)
    {
        if (bEqEnergyMax[i]<=bChannelVal[i])
            bEqEnergyMax[i]=bChannelVal[i];
        else
        {                
            if ( (bEqEnergyMax[i]!=0) && (bEqMaxKeepTm==0) )
                bEqEnergyMax[i]=bEqEnergyMax[i]-1;    //reduce 1             
        }
    }
    
    if (bEqMaxKeepTm)
        bEqMaxKeepTm--;
    else
        bEqMaxKeepTm=1;

    //plot the background block
    {
        if (p_scan==0) 
        {
            pTopLine = (UINT16 *) (get_osdbuf_region_ptr(r,0)+40+iWidth*60/2);
            pBtmLine = (UINT16 *) (get_osdbuf_region_ptr(r,1)+40+iWidth*60/2);
        } 
        else 
        {
            pTopLine = (UINT16 *) (get_osdbuf_region_ptr(r,0)+40+iWidth*60);
            pBtmLine=pTopLine;
        }
    }    

    //Totally has 25 block for each freq (0 ~ 24 )
    if(p_scan==0)  step=1;
    else step=2;
    
    for (j=25;j>0;j--)
    {      
        for(k=0;k<step;k++)
        {
            for (i=1,iBlock=0;iBlock<13;i=i+3,iBlock++)
            {    
                //make sure color
                if (j==bEqEnergyMax[iBlock])
                    unColor=BR_RED_COLOR;
                else {
                    if (j<bChannelVal[iBlock])
                        unColor=bColorTab[j/4];
                    else
                        unColor = 0x6666;//GRAY_COLOR;   
                }            
                                  
                pTopLine[i]   =  unColor;
                pTopLine[i+1] =  unColor;
                if (p_scan==0)
                {
                    pBtmLine[i]   =  unColor;
                    pBtmLine[i+1] =  unColor;
                }
            }
        }
        
       //step 2 line
        pTopLine+=(iWidth*step);    
        if (p_scan==0) pBtmLine+=(iWidth*step);
    }  
}
#endif


#ifdef DISP_REGION_BOTTOM
/**************************************************************************
 *  Function Name: OSD_ShowBottomDisp                                     *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *    1: show disp in bottom position                                     *
 *    0: show disp in top position                                        *
 *  See also:                                                             *
 **************************************************************************/
#include "fsNAV.h"

extern UINT8 OSD_ShowBottomDisp()
{
    extern UINT8 Jpg_Show_Usage_Flag;

	UINT8 uiShow;
	if((cd_type_loaded == CDROM) 
    
    #ifdef SUPPORT_FILE_SYSTEM_MODE	// 2004/10/16 nono add definition.
	    && (!IsOtherStatePlayMode())
    #endif
    
    #ifdef JPEG_THUMBNAIL_MENU
	    && ( pFsJpeg->g_nJpegMode != JPEG_THUMBNAIL_MODE )
    #endif

    #ifdef HELP_BMP_GUI
        &&(Jpg_Show_Usage_Flag == 0)
    #endif
    
        && (!Is_JPEG_PLAY_STATE()) 
	)
		uiShow = 1;
	else
		uiShow = 0;
		 
    //press stop button after playing mp3,display bar should show top position.suqiaoli add,2005-1-19.
    if ((cd_type_loaded == CDROM)&&(Is_MP3_STATE())&&(play_state == VCD_STATE_STOP)) 	
	    uiShow = 0;
		 
	return  uiShow;    
}


/**************************************************************************
 *  Function Name: OSD_GetTrueDispRegion                                  *
 *  Purposes:                                                             *
 *     Get to know true disp region                                       *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern UINT8 OSD_GetTrueDispRegion()
{
	if(OSD_ShowBottomDisp() == 1)
	{
		if (full_scrn & PROGRAM)
			disp_region = (sizeof(osd_hdr_prog)/sizeof(osd_hdr_prog[0])) - 1;
		else if (full_scrn & SOUND)
			disp_region = (sizeof(osd_hdr_music)/sizeof(osd_hdr_music[0])) - 1;
		else
			disp_region = (sizeof(osd_hdr_0)/sizeof(osd_hdr_0[0])) - 1;
		
		temp_region = 0;	
	}
	else
    {
		if (full_scrn & PROGRAM)
			temp_region = (sizeof(osd_hdr_prog)/sizeof(osd_hdr_prog[0])) - 1;
		else if (full_scrn & SOUND)
			temp_region = (sizeof(osd_hdr_music)/sizeof(osd_hdr_music[0])) - 1;
		else
			temp_region = (sizeof(osd_hdr_0)/sizeof(osd_hdr_0[0])) - 1;
		
		disp_region = 0;	        
   }     
    	
    return  disp_region;
      
}
#endif//#ifdef DISP_REGION_BOTTOM


#ifdef SUPPORT_3DSOUND
/**************************************************************************
 *  Function Name: osd_print_eq                                           *
 *  Purposes:                                                             *
 *    Draw EQ setting status on screen by OSD                             *
 *  Descriptions:                                                         *
 *    The each band energy range is 0 ~ 24                                *
 *    The each freq energy 0 ~ 25    0= nothing, 1 ~ 25 engry             *
 *  Arguments:                                                            *
 *    r: region for draw                                                  *
 *    p:  input 7 band EQ value                                           *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_print_eq(UINT8 r, const BYTE *p)
{
    UINT16  i,j,iBlock;
    UINT16  unColor;    
    BYTE    bChannelVal[MAX_BAND*2];    //byte 13 is garbage

    coordinate  start;
    dimension   out_dimension;
    
    start.y = BAND_YSTART;
    out_dimension.x_length = RECT_WIDTH_PIXEL;
    out_dimension.y_length = RECT_HEIGHT;
    
    //calcuate the interpolate data
    //The data is mapping to 0 ~ 24    
    for (i=0;i<MAX_BAND*2;i=i+2)
    {
        bChannelVal[i]=*p;
        bChannelVal[i+1]=(*(p)+*(p+1))/2;
        p++;
    }
    
    //check the last max value
    for (i=0;i<MAX_BAND*2-1;i++)
    {
        if (bEqEnergyMax[i]<=bChannelVal[i])
            bEqEnergyMax[i]=bChannelVal[i];
        else
        {                
            if ( (bEqEnergyMax[i]!=0) && (bEqMaxKeepTm==0) )
                bEqEnergyMax[i]=bEqEnergyMax[i]-1;    //reduce 1             
        }
    }
    
    if (bEqMaxKeepTm)
        bEqMaxKeepTm--;
    else
        bEqMaxKeepTm=1;
    
    //Totally has 25 block for each freq (0 ~ 24 )       
    for (j=25;j>0;j--)
    {      
        start.x = BAND_XSTART_PIXEL;            
            
        for (iBlock=0;iBlock<MAX_BAND*2-1;iBlock++)
        {    
            //make sure color
            if (j==bEqEnergyMax[iBlock])
                unColor= BAND_TOP_SEL_RECT;
            else {
                if (j<bChannelVal[iBlock])
                    unColor=BAND_SELECTED_RECT;
                else
                    unColor=BAND_OTHER_RECT;
            }            
            
            start.x += RECT_XOFFSET_PIXEL;
                              
            osd_draw_rectangle(&start, &out_dimension, unColor, r);   
        }

        start.y += RECT_YOFFSET;
    }
}
//#else
//void osd_print_eq(UINT8 r __UNUSED, const BYTE *p __UNUSED) {} 
#endif


//#ifdef OSD_FONT_API//liweihua mod 2004-3-12 18:48
#if (defined(OSD_FONT_API) || defined(USE_COMMON_OSD_DRIVER))
/**************************************************************************
 *  Function Name: osd_draw_gbfont                                        *
 *  Purposes:                                                             *
 *    to show chinse/Englisch word/number in OSD                          *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *    vid    -----> 0:  draw chinese                                      *
 *           -----> 1:  draw English word/number                          *
 *           -----> 2:  clear font (size: fwidth * fhight)                *
 *    pFont  -----> font lattice informaiton of a word                    *
 *    xStart -----> word x axis start positon                             *
 *    yStart -----> word y axis start positon                             *
 *    fwidth -----> font width                                            *
 *    fhight -----> font hight                                            *
 *    number -----> region number                                         *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_draw_gbfont(BYTE vid __UNUSED, const BYTE pFont[], int xStart, int yStart, unsigned int  fwidth, unsigned int  fhight, BYTE fontcolor,BYTE number)
{    
    coordinate start;
    font_palette temp_palette;
    dimension out_dimension;

	temp_palette.font_color         = fontcolor;
	
	#ifdef SUBTITLE_BLACK_BACKGROUND	//yaowh add 2005-11-14 17:03
		temp_palette.background_color   = 1;
	#else
		temp_palette.background_color   = 0;
	#endif
	
    start.x = xStart;
    start.y = yStart;
    
    out_dimension.x_length = fwidth;
    out_dimension.y_length = fhight;
   

	 osd_draw_font_bitmap( pFont, &start,&out_dimension, &temp_palette, number, 0);   
	
}


/**************************************************************************
 *  Function Name: osd_ClearOneRegion                                     *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void osd_ClearOneRegion(BYTE number, BYTE bkColor)
{
    osd_fill_region(number, bkColor);
}
#endif


#ifdef NEW_HDMI_FLOW
/**************************************************************************
 *  Function Name: UpDateHDMI_StateDisplay                                *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 **************************************************************************/
extern void UpDateHDMI_StateDisplay(void)
{
    static UINT8 UpDateHDMI_StateDisplayi;
    switch(HDMI_State())
    {
        case HDMI_STATE_HDCP_FAIL:
            //io_write_wait("HDMI_STATE_HDCP_FAIL\n");
            if(UpDateHDMI_StateDisplayi==0)
            {
                UpDateHDMI_StateDisplayi++;
                //ShowTitle();
                PrintOsdMsg(STR_OS_HDCP_FAIL,REGION1,0,0);
            }
            break;

        case HDMI_STATE_HDCP_AUTH:
            //io_write_wait("HDMI_STATE_HDCP_AUTH\n");
        case HDMI_STATE_NO_RX:
            //io_write_wait("HDMI_STATE_NO_RX\n");
            //psprintf(linebuf,"RegionOnOff[REGION1][2]=%d\n",RegionOnOff[REGION1][2]);
            //io_write_wait(linebuf);
            if(RegionOnOff[REGION1][2]==STR_OS_HDCP_FAIL)
            {
                //io_write_wait("Clear Fail Tip\n");
                osd_tog_region(REGION1, OSD_OFF);
                RegionOnOff[REGION1][1] = 0;
                RegionOnOff[REGION1][2] = STR_OS_SPACE;
                RegionValStr[REGION1][0] = 0;
            }
            break;
        default:
            break;
    }
    UpDateHDMI_StateDisplayi=0;
}
#endif


/************************************************************
Not used in current project
************************************************************/

#if 0//def OSD_STR_LINE_WRAP  
/**************************************************************************
 *  Function Name: FindNextLetter                                         *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *    Get next space position                                             *
 *  Arguments:                                                            *
 *    str: string                                                         *
 *    iStrLoc: initial position to search                                 *
 *  Returns:                                                              *
 *    if Find next given letter, return its postion                       *
 *    else if not find it, it means that the string will be end.          *
 *    so return its total strlen.                                         *
 *  See also:                                                             *
 *    zhaoyanhua 2004-4-22 9:49                                           *
 **************************************************************************/
int FindNextLetter(const BYTE *str, int iStrLoc, BYTE c)
{
    int i = 0;
    int lenth = strlen(str);
    
    for (i = iStrLoc; i < lenth; i++)
    {
        if (str[i] == c) 
            return i;    
    }
    return lenth;
}
#endif//#ifdef OSD_STR_LINE_WRAP  

#ifdef DVB1000_OSD_MENU
#include "dvbmenu.h"
void osd_draw_dvbmenu_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown)
{
    BYTE        buttonC;
    UINT32      xNew, yNew;    
    
    buttonC = color;    
    xNew = xStart * 16;
    yNew = yStart * SETUP_BTN_HEIGHT + 8;    
    #ifdef DVB_OSD_MENU_VER1
    osd_draw_region_rect(xNew, yNew, (UINT32)(xLen*16), (UINT32)(SETUP_BTN_HEIGHT), buttonC, DVBMENU_REGION);    
    osd_draw_button_outline(xNew,yNew,(UINT32)(xNew+xLen*16),(UINT32)(yNew+SETUP_BTN_HEIGHT-2),bDown,0x0f,DVBMENU_REGION);
    #else
    osd_draw_region_rect(xNew + 4, yNew + 4, (UINT32)(xLen*16 - 8), (UINT32)(SETUP_BTN_HEIGHT - 8), buttonC, DVBMENU_REGION);    
    #endif
}
//Draw button with light border
void osd_draw_dvbmenu_border_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown)
{
    BYTE        buttonC;
    UINT32      xNew, yNew;    
    buttonC = color;    
    xNew = xStart * 16;
    yNew = yStart * SETUP_BTN_HEIGHT + 8;    
    osd_draw_region_rect(xNew + 2, yNew + 2, (UINT32)(xLen*16 - 4), (UINT32)(SETUP_BTN_HEIGHT - 4), buttonC, DVBMENU_REGION);    
    osd_draw_button_outline(xNew + 2,yNew + 2,(UINT32)(xNew+xLen*16 - 4),(UINT32)(yNew+SETUP_BTN_HEIGHT - 4),bDown, 0x0F, DVBMENU_REGION);
}
#endif //DVB1000_MENU

//joshua, 20050711, modified for servo-debug function on OSD
void osd_print_servo_msg(char *buf __UNUSED)
{
    #ifdef DVD_SERVO
        #ifdef SERVO_DEBUG_MSG_ON_OSD
            if(servo_debug_message)
            {
                coordinate  start; 
                
                start.x = 0;
                start.y = 0;
                
                osd_draw_string(&start, buf, 3, 0, 1, 0);
                timeout_osd[1]= OSD_TIMEOUT;
                osd_tog_region(1, OSD_ON);
            }
        #endif
    #endif
}
#ifdef OP_PLAYMODE
	#include "opui.c"
#endif 
#endif // NEW_OSD_DRIVER

#ifdef	SUPPORT_FONT_OUTLINE
/********************************************************************************
*  Function Name:  OSD_DrawFontFrame                                     		*
 *  Purposes:		The function is the purpose to draw font outline.	  		*	
 *  Descriptions: 	The function add the width of 1byte and height according 	* 															*
 * 					the FrameWidth.												*
 *																				*	
 *  Arguments:    	pDest: The font outline added and stored in pDest by  		*
 * 						   the function.								  		*
 * 					pSrc:  The font raw data which want to be add outline 		*
 *					Width: The original font width.							 	*
 *					Height:The original font height.							*
 *					FrameWidth:	The font outline width.							*
 *																				*	
 *  Returns:		None                                                    	*
 *  See also:                                                  		           	*
 *      			suxin add 2005-09-18										*	
 *	   				suxin fixed 2005-10-09	                               		*
 *					mimitsai modify, 2006-04-25							  		*		
 *******************************************************************************/
extern void OSD_DrawFontFrame(UINT8 *pDest, UINT8 *pSrc, BYTE Width, BYTE Height, BYTE FrameWidth)
{
    int i,j,k, frmWidCnt;
	UINT8 DoubleNum;

	DoubleNum = OSD_EnlargeFontForFrame(pDest,pSrc,Width,Height,FrameWidth);

	UINT8 jdugeflag = 0x01;
	for(frmWidCnt =0; frmWidCnt < FrameWidth; frmWidCnt++)
	{
		UINT16 valueForPos0, valueForPos1, valueForPos2, valueForPos3;
		if(jdugeflag == 0x01)
		{
			valueForPos0 = 0x80; //xx00 0000
			valueForPos1 = 0x20; //00xx 0000
			valueForPos2 = 0x08; //0000 xx00
			valueForPos3 = 0x02; //0000 00xx
		}
		else
		{
			valueForPos0 = 0x40;
			valueForPos1 = 0x10;
			valueForPos2 = 0x04;
			valueForPos3 = 0x01;
		}

 		for(i=0; i < (Height + 2*FrameWidth);i++)
 		{
 			for(j=0; j<DoubleNum; j++)						// width : total 6 bytes
 	   		{
 				int aIndex = (DoubleNum * i) + j + 2;

 	      		for(k=0;k<4;k++)							// see one point(two pixel) one time
 	      		{
					if( (((pDest[aIndex]&(0xc0>>(2*k)))>>(6-(2*k)))==0x03) || (((pDest[aIndex]&(0xc0>>(2*k)))>>(6-(2*k)))==jdugeflag) ) 
 	        		{
 					    if(i != (Height + 2*FrameWidth)-1)  // don't check down point when last line  
 					  	{
 							if((pDest[aIndex + DoubleNum]&(0xc0>>(2*k)))==0)//down(1100 0000)
 	             	 			pDest[aIndex + DoubleNum] |=(valueForPos0>>(2*k));	// 1000 0000 for k=0, 00(10)0000 for k=1
 						}
 					  	if(i != 0)							// don't check up point when first line
 					  	{
							if((pDest[aIndex - DoubleNum]&(0xc0>>(2*k)))==0)// 1100 0000 up
	             	 			pDest[aIndex - DoubleNum] |=(valueForPos0>>(2*k));	// 1000 0000
						}
	             		switch (k)
	             		{
							case 0:
                    			if((pDest[aIndex - 1]&0x03)==0) 			//left (0000 0011)(xx00 0000)
                    				pDest[aIndex - 1] |= valueForPos3;		//     (0000 0010)(xx00 0000)
			                    if((pDest[aIndex]&0x30)==0) 				//right(xx11 0000)
			                    	pDest[aIndex] |= valueForPos1;			//	   (xx10 0000)
	    		                break;
	              			case 1:
	                    		if((pDest[aIndex] & 0xc0)==0)   			//left (11xx 0000)
			                    	pDest[aIndex] |= valueForPos0;			//	   (10xx 0000)
			                    if((pDest[aIndex] & 0x0c)==0) 				//right(00xx 1100)
			                    	pDest[aIndex] |= valueForPos2;			//	   (00xx 1000)
			                    break;
	    		           	case 2:
			                    if((pDest[aIndex]  &0x30)==0)   			//left (0011 xx00)
			                    	pDest[aIndex] |= valueForPos1;			//	   (0010 xx00)
			                    if((pDest[aIndex]  &0x03)==0) 				//right(0000 xx11)
			                    	pDest[aIndex] |= valueForPos3;	        //     (0000 xx10)
			                    break;	            
						   	case 3:
			                    if((pDest[aIndex]  &0x0c)==0)   			//left (0000 11xx)
			                    	pDest[aIndex] |= valueForPos2;			//	   (0000 10xx)
								if((pDest[aIndex + 1]&0xc0)==0) 			//right(0000 00xx)(1100 0000)
		                    		pDest[aIndex + 1] |= valueForPos0;	    //     (0000 00xx)(1000 0000)
			                    break;
			             }

		            }
	      		}//for(k=0;k<4;k++)	
			}//for(j=0;j<=( DoubleNum - 1 );j++)  
		}//for(i=0; i < (Height + 2*FrameWidth);i++)
		
		if(jdugeflag == 0x01)
			jdugeflag = 0x02;
		else
			jdugeflag= 0x01;
	}//for(frmWidCnt =0; frmWidCnt < FrameWidth; frmWidCnt++)
}

/**************************************************************************
 *  Function Name:  OSD_EnlargeFontForFrame                               *
 *  Purposes:        													  *	
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 *		   suxin added 2005-10-10	                                      *
 **************************************************************************/
extern UINT8 OSD_EnlargeFontForFrame(UINT8 *pDest,UINT8 *pSrc,BYTE Width, BYTE Height, BYTE FrameWidth)
{
	UINT16 my16bits;
    UINT8 i,j,k;
	UINT8 W_ByteNum;	//S:每行有几个字节 
	UINT8 DoubleNum;
	my16bits=0;
	
	//S:字符宽度是8个pixel的倍数
	if(Width%8 == 0)				
	{
		W_ByteNum = Width/8;	                                    // font total bytes(wid)
		DoubleNum = 2*(W_ByteNum+1);                                // double font enlarged bytes(wid)
	    UINT8 pDesttem[(W_ByteNum + 1)*(Height + FrameWidth*2)];	// total points of enlarged font 

		//S:对字符的最上面一行和最下面一行补零
		for(i=0;i<(W_ByteNum+1) * FrameWidth ;i++)	                // fill zero to temp for enlarged height(top and bottom)
		{
			pDesttem[i]=0x00;
			pDesttem[(W_ByteNum + 1)*(Height + FrameWidth*2)-1-i]=0x00;
		}

		//S:对字符补零，每行的最左边加四个零，最右边加四个零。例如: 0x25,0x68---->0x02,0x56,0x80
		for(i=FrameWidth;i<(Height + FrameWidth);i++)               // real font portion, copy font data to temp
		{	
			for(j=0;j<(W_ByteNum+1);j++)	                        // for width, see byte a time
			{
				if(j==0)	                                        // first byte
				{
					pDesttem[((W_ByteNum+1)*i) + j] = pSrc[(W_ByteNum*(i-FrameWidth))]>>4;
				}
				else if(j==W_ByteNum)                               // last byte
				{
					pDesttem[((W_ByteNum+1)*i) + j] = pSrc[(W_ByteNum*(i-FrameWidth))+W_ByteNum-1]<<4;
				}
				else                                                // second byte
				{
					my16bits = (pSrc[(W_ByteNum*(i-FrameWidth))+j-1]<<8)|pSrc[(W_ByteNum*(i-FrameWidth))+j];
					pDesttem[((W_ByteNum+1)*i) + j] = (my16bits>>4)&0x00ff;
					my16bits = 0;
				}		
			}
		}
		
		pDest[0] = Width + 8;                                       // 4bits for left and right.
		pDest[1] = Height + (FrameWidth<<1);                        // hei + 2* frameWidth(top, bottom).

		//S:把字符进行横向的放大一倍，0-->00   1-->11
		for(i=0;i<pDest[1];i++)                                     // copy tmp to dest.
		{
			for(j=0;j<(W_ByteNum+1);j++)
			{
				for(k=0;k<8;k++)
				{
					if((pDesttem[((W_ByteNum+1)*i)+j]&(0x80>>k)))   // if tmp have value, copy to my16bits.
	             	{
	               		my16bits |= 0xc000>>(2*k);
	             	}
				}
			 pDest[(DoubleNum * i) + (2 * j) + 2]=(my16bits>>8);
	         	 pDest[(DoubleNum * i) + (2 * j) + 1 + 2]=my16bits&0x00ff;
			 my16bits = 0;
			}
		 }
	}
	//S:字符宽度是4个pixel的整数倍,但不是8个pixel的整数倍
	else							//if(Width%8 == 0)
	{
		W_ByteNum = (Width+4)/8;
		DoubleNum = 2*(W_ByteNum);
		UINT8 pDesttem[W_ByteNum*(Height + FrameWidth*2)];
	
		//S:对字符的最上面一行和最下面一行补零
		for(i=0;i<(W_ByteNum+1)*FrameWidth;i++)
		{
			pDesttem[i]=0x00;
			pDesttem[W_ByteNum *(Height + FrameWidth*2)-1-i]=0x00;
		}

		//S:对于宽度不为字节整数倍的字符，经过处理，宽度变为字节的整数倍后，每行的最后四个pixel都为0,
		//把2个零移到最前面去.
		for(i = FrameWidth;i<(Height + FrameWidth);i++)
		{	
			for(j=0;j<W_ByteNum;j++)
			{
					if(j==0)
					{
						pDesttem[(W_ByteNum*i) + j] = pSrc[(W_ByteNum*(i-FrameWidth))]>>2;
					}
					else
					{
						my16bits = (pSrc[(W_ByteNum*(i-FrameWidth))+j-1]<<8)|pSrc[(W_ByteNum*(i-FrameWidth))+j];
						pDesttem[(W_ByteNum*i) + j] = (my16bits>>2)&0x00ff;
						my16bits = 0;
					}	
			}
		}
		
		pDest[0] = Width + 4;
		pDest[1] = Height + (FrameWidth<<1);
		
		//S:把字符进行横向的放大一倍，0-->00   1-->11
		for(i=0;i < pDest[1];i++)
		{
			for(j=0;j<W_ByteNum;j++)
			{
				for(k=0;k<8;k++)
				{
					if((pDesttem[((W_ByteNum)*i)+j]&(0x80>>k)))
	             	{
	               		my16bits |= 0xc000>>(2*k);
	             	}
				}
			 pDest[(DoubleNum * i) + (2 * j) + 2]=(my16bits>>8);
	         pDest[(DoubleNum * i) + (2 * j) + 1 + 2]=my16bits&0x00ff;
			 my16bits = 0;
			}
		 }
	}
	return DoubleNum;
}
#endif         //#ifdef  SUPPORT_FONT_OUTLINE
/**************************************************************************
 *  Function Name:  OSD_AdjustFontWidth                                       *
 *  Purposes: S: 如果字符宽度是4pixel的倍数，调整为8pixel的倍数 		  *	
 *  Descriptions:                                                         *
 *  Arguments:                                                            *
 *  Returns:                                                              *
 *  See also:                                                             *
 *		   suxin add 2005-10-09	                                      *
 **************************************************************************/
extern void OSD_AdjustFontWidth( UINT8* pDest, const UINT8* pSrc, UINT8 Height,UINT8 Width)	//suxin add 20051009
{
	UINT8 i = 0, uiToggle = 0;
	UINT8 j;
	UINT8 WidthByte;
	WidthByte = ( Width + 4 ) >> 3;
	for( ; i < Height ; i++)
	{
		if( uiToggle == 0 )
		{
			for( j = 0; j < (WidthByte - 1); j++ )
			{
				pDest[(i*WidthByte) + j] = pSrc[j];
			}
			pDest[(i*WidthByte) + j] = pSrc[j]& 0xf0;
			pSrc= pSrc + (WidthByte- 1);
		}
		else
		{
			for( j = 0; j < (WidthByte - 1); j++ )
			{
				pDest[(i*WidthByte)+j]= ((pSrc[j]&0x0f )<<4)|(( pSrc[j+1] & 0xf0 ) >> 4);
        	}
			pDest[(i*WidthByte) + j] = ( pSrc[j] & 0x0f ) << 4;
			pSrc = pSrc + WidthByte;
		}
		uiToggle = !uiToggle;
	}
}

#ifdef SUPPORT_SW_OSD_SCALING
//#define DEBUG_OSD_REG_SCALING
//#define DEBUG_OSD_REG_COPY
#define osd_get_region_pointer( uiRegionIdx, uiField ) \
    (t_osdv2_header*)(get_osdbuf_baseptr() + (region[uiRegionIdx].osd_header[uiField]<< 5))
#define osd_get_scaling_region_p( uiRegionIdx, uiField )\
    (t_osdv2_header*)(get_osdbuf_baseptr() + (scaling_region[uiRegionIdx].osd_header[uiField]<< 5))		


#if 1//new OSD mode
void osd_region_scaling(int uiRegionIdx, DrawDimension * draw_section)
{

    scaling_t_osd_region* scaling_region_p;
    t_osd_region *region_pointer;
	
    t_osdv2_header *pTop_origin, *pBot_origin;
    t_osdv2_header *pTop_scaling, *pBot_scaling;

    BYTE *osdfrom    = get_osdbuf_baseptr(); 
    BYTE *pLine_origin, *pLine_scaling;	

    UINT16 v_index, v_step, v_cnt;;
    UINT32 v_cnt_total;	
    UINT16 i;
    UINT16 origin_osd_h, origin_osd_w, scaling_osd_h, scaling_osd_w;
    UINT32 osd_loc, scaling_loc;
       

    scaling_region_p = &scaling_region[uiRegionIdx];
    region_pointer = &region[uiRegionIdx];

    origin_osd_h = region_pointer->osd_h;
    origin_osd_w = region_pointer->osd_w;

    scaling_osd_h = scaling_region_p->osd_h;
    scaling_osd_w = scaling_region_p->osd_w;
		
    pTop_origin = osd_get_region_pointer(uiRegionIdx, 0);
    pBot_origin = osd_get_region_pointer(uiRegionIdx, 1);

    pTop_scaling = osd_get_scaling_region_p(uiRegionIdx, 0);
    pBot_scaling = osd_get_scaling_region_p(uiRegionIdx, 1);

    int v_start, v_end, current_v=0;    //  the region of v_start to v_end will be copy and scale to scaling buffer. 
    v_start = draw_section->draw_start.y;
    if(v_start<0) v_start = 0;
    v_end = v_start + draw_section->draw_dimension.y_length-1;
    if(v_end>= origin_osd_h) v_end=origin_osd_h-1;
        
    v_cnt_total=0;
//    v_step = 256*(scaling_region_p->ratio.y_divisor)/(scaling_region_p->ratio.y_dividend);
    v_step = ((scaling_region_p->ratio.y_divisor)<<8)/(scaling_region_p->ratio.y_dividend);

    #ifdef DEBUG_OSD_REG_SCALING
    printf_w(__FUNCTION__  "  origin_osd_h:%d, origin_osd_w:%d, scaling_osd_h:%d,  scaling_osd_w:%d \n", origin_osd_h, origin_osd_w, scaling_osd_h, scaling_osd_w);
    printf_w(__FUNCTION__  "  v_start:%d, v_end:%d, v_step:%d \n", v_start, v_end, v_step);
    #endif
    
    for(i=0; i<scaling_osd_h; i++) {
        v_cnt = v_cnt_total & 0xff;      //v_cnt = v_cnt_total % 256;
        v_index = v_cnt_total >> 8;    //v_index = v_cnt_total / 256;    
                 
//	 if(v_index>=(origin_osd_h-1)  && v_cnt>128) return;  

        if ((i & 0x01) && (p_scan ==FALSE))
        {
            pLine_scaling = (BYTE *)(osdfrom + (SWAP16(pBot_scaling->link_data) <<5));
				//printf("pBtmLine\n");
        }	
        else
        {
            pLine_scaling = (BYTE *)(osdfrom + (SWAP16(pTop_scaling->link_data) <<5));
				//printf("pTopLine\n");
        }			

        if(p_scan == TRUE) {
            pLine_origin = (BYTE *)(osdfrom + (SWAP16(pTop_origin->link_data) <<5));				
            scaling_loc = i*scaling_osd_w;
            if(v_cnt<=128)
                current_v = v_index;
            else 
                current_v = v_index + 1;                
            osd_loc = current_v*origin_osd_w;
        }	
        else {
            scaling_loc = (i>>1)*scaling_osd_w;  //scaling_loc = (i/2)*scaling_osd_w;
				
            if(v_index & 0x01) {
                if(v_cnt<=128) {
                    pLine_origin = (BYTE *)(osdfrom + (SWAP16(pBot_origin->link_data) <<5));
                    current_v = v_index;
                }
                else {
                    pLine_origin = (BYTE *)(osdfrom + (SWAP16(pTop_origin->link_data) <<5));
                    current_v = v_index+1;
                }	
                osd_loc = (current_v>>1)*origin_osd_w;   //osd_loc = (current_v/2)*origin_osd_w;                   
            }
            else {
                if(v_cnt<=128) {
                    pLine_origin = (BYTE *)(osdfrom + (SWAP16(pTop_origin->link_data) <<5));
		      current_v = v_index;
                }
                else {
                    pLine_origin = (BYTE *)(osdfrom + (SWAP16(pBot_origin->link_data) <<5));
                    current_v = v_index;
                }
                osd_loc = (current_v>>1)*origin_osd_w;  //osd_loc = (current_v/2)*origin_osd_w;
            }		

        }	
       
        if( (current_v>=v_start) && (current_v<=v_end)){   
            osd_raw_copy( uiRegionIdx, draw_section, &pLine_scaling[scaling_loc], &pLine_origin[osd_loc]  );
        }else if(current_v>origin_osd_h) {
            if(p_scan == TRUE)
                osd_loc = (origin_osd_h-1)*origin_osd_w;
            else
                osd_loc = (origin_osd_h/2-1)*origin_osd_w;
            osd_raw_copy( uiRegionIdx, draw_section, &pLine_scaling[scaling_loc], &pLine_origin[osd_loc]  );
        }else if((current_v>v_end)  &&  (v_end<(origin_osd_h-1))) {
            return;
        }

        v_cnt_total += v_step;	
			
    }
     
}

#if 1
// rewrite the function for speeding up the osd scaling and copy. yltseng, 2006-09
void osd_raw_copy(int uiRegionIdx, DrawDimension * draw_section, BYTE *pLine_scaling, const BYTE *pLine_origin)
{
    #define HORIZONTAL_RESOLUTION           (512)
    #define HALF_HORIZONTAL_RESOLUTION      (512/2)

    scaling_t_osd_region*   scaling_region_p    = &scaling_region[uiRegionIdx];
    t_osd_region*           region_pointer      = &region[uiRegionIdx];
    
    UINT32  osd_format = region_pointer->osd_format;	
    UINT32  uiPixelPerByte, uiBitPerPixel, uiBitMask, uiPixel2Byte;
    
    switch (osd_format)
    {
        case OSD_FORMAT_2COLOR:
            uiPixelPerByte  = 8;
            uiBitPerPixel   = 1;
            uiBitMask       = 0x80;
            uiPixel2Byte    = 3;
            break;

        case OSD_FORMAT_4COLOR:
            uiPixelPerByte  = 4;
            uiBitPerPixel   = 2;
            uiBitMask       = 0xC0;
            uiPixel2Byte    = 2;
            break;
            
        case OSD_FORMAT_16COLOR:
            uiPixelPerByte  = 2;
            uiBitPerPixel   = 4;
            uiBitMask       = 0xF0;
            uiPixel2Byte    = 1;
            break;

        default:
            return;
    }

    UINT32  origin_osd_w            = region_pointer->osd_w;
    UINT32  origin_osd_visible_w    = region_pointer->osd_visible_w;
    UINT32  scaling_osd_w           = scaling_region_p->osd_w;

    UINT32  h_step = ((scaling_region_p->ratio.x_divisor)<<9) / (scaling_region_p->ratio.x_dividend);

    UINT32  h_start = draw_section->draw_start.x;

    UINT32  h_end = h_start + draw_section->draw_dimension.x_length-1;
    if(h_end>=origin_osd_visible_w) h_end = origin_osd_visible_w-1;

#ifdef DEBUG_OSD_REG_COPY
    printf(__FUNCTION__ " h_step:%d, h_start:%d, h_end:%d\n", h_step, h_start, h_end);
#endif

    // scale_h_start_BIdx is the start  Byte index of the scaling region 
    UINT32 scale_h_start_BIdx = (((h_start<<9)/h_step)>>uiPixel2Byte);
    if(scale_h_start_BIdx>0)  scale_h_start_BIdx--;

    // scale_h_end_BIdx is the end  Byte index of the scaling region 
    UINT32 scale_h_end_BIdx =  (((h_end<<9)/h_step)>>uiPixel2Byte)+(scaling_region_p->ratio.x_dividend/scaling_region_p->ratio.x_divisor);
    if(scale_h_end_BIdx>=scaling_osd_w) scale_h_end_BIdx = scaling_osd_w - 1;

    UINT32  i, j;
    UINT32  uiSrcColor = 0, uiDstColor = 0;

    UINT32 h_offset_cnt = (scale_h_start_BIdx<<uiPixel2Byte)*h_step ;
    UINT32 uiSrcStartpixel = h_offset_cnt>> 9;
    
    UINT32 uiSrcStartIdx  = uiSrcStartpixel >> uiPixel2Byte;    
    UINT32 h_index        = (uiSrcStartpixel&(uiPixelPerByte-1));
    int        h_cnt           = h_offset_cnt - (uiSrcStartpixel<<9);
    const UINT8*    pSrcRawData = &pLine_origin[uiSrcStartIdx];
    
    uiSrcColor = *pSrcRawData;
    pSrcRawData++;
    // deal with the first byte of scale buffer
    for(i=0; i<=h_index; i++) 
    {
        uiDstColor = ((uiSrcColor & uiBitMask) >> (8 - uiBitPerPixel));
        uiSrcColor = uiSrcColor << uiBitPerPixel;
    }        
    
    const UINT8*    pSrcEnd     = &pLine_origin[origin_osd_w-1];
    UINT8*          pDstRawData = &pLine_scaling[scale_h_start_BIdx];

    for(i = scale_h_start_BIdx; i <= scale_h_end_BIdx; i++) {

        UINT32 uiDstData = 0;

        for (j = 0; j < uiPixelPerByte; j++)
        {
            if (h_cnt > HALF_HORIZONTAL_RESOLUTION) // h_cnt > 256, get the next pixel color of osd buffer for scale buffer
            {                                                                  
                h_cnt -= HORIZONTAL_RESOLUTION;
                h_index++;
                
                if (h_index >= uiPixelPerByte)
                {
                    h_index = 0;
                    uiSrcColor = *pSrcRawData;
                    
                    if(pSrcRawData < pSrcEnd)
                        pSrcRawData++;
                }

                uiDstColor = ((uiSrcColor & uiBitMask) >> (8 - uiBitPerPixel));
                uiSrcColor = uiSrcColor << uiBitPerPixel;
            }

            uiDstData = (uiDstData << uiBitPerPixel) | uiDstColor;
            h_cnt += h_step;
        }

        *pDstRawData++ = uiDstData;
    }

}

#else 

// original osd_raw_copy. robert.chang
void osd_raw_copy(int uiRegionIdx, DrawDimension * draw_section, BYTE *pLine_scaling, const BYTE *pLine_origin)
{
    scaling_t_osd_region* scaling_region_p;
    t_osd_region *region_pointer;
	
    scaling_region_p = &scaling_region[uiRegionIdx];
    region_pointer = &region[uiRegionIdx];

    UINT16 origin_osd_w, origin_osd_visible_w, scaling_osd_w;    
    origin_osd_w = region_pointer->osd_w;
    origin_osd_visible_w = region_pointer->osd_visible_w;
    scaling_osd_w = scaling_region_p->osd_w;

    UINT8 osd_format = region_pointer->osd_format;	

    UINT8 pix2byte_shift;
    UINT32  h_index, h_cnt, h_step;
    UINT32 h_cnt_total;
    UINT32 originBIdx, originPIdx;

    h_cnt_total = 0;
//    h_step = 512*(scaling_region_p->ratio.x_divisor)/(scaling_region_p->ratio.x_dividend);
    h_step = ((scaling_region_p->ratio.x_divisor)<<9)/(scaling_region_p->ratio.x_dividend);

    int h_start, h_end;
    int scalingBIdx, scale_h_start_BIdx=0, scale_h_end_BIdx=0;
    h_start = draw_section->draw_start.x;
    if(h_start<0) h_start = 0;
    h_end = h_start + draw_section->draw_dimension.x_length-1;
    if(h_end>=origin_osd_visible_w) h_end = origin_osd_visible_w-1;

#ifdef DEBUG_OSD_REG_COPY
    printf_w(__FUNCTION__ " h_step:%d, h_start:%d, h_end:%d\n", h_step, h_start, h_end);
#endif

    pix2byte_shift = 0;
    if(osd_format == OSD_FORMAT_2COLOR) {
        pix2byte_shift = 3;
    }    
    else if(osd_format == OSD_FORMAT_4COLOR) {
        pix2byte_shift = 2;
    }    
    else if(osd_format == OSD_FORMAT_16COLOR) {
        pix2byte_shift = 1;
    }       

    // scale_h_start_BIdx is the start  Byte index of the scaling region 
    scale_h_start_BIdx = (((h_start<<9)/h_step)>>pix2byte_shift);   // scale_h_start_BIdx = (((h_start*512)/h_step)>>3)
    if(scale_h_start_BIdx>0)  scale_h_start_BIdx-- ;                        

    // scale_h_end_BIdx is the end  Byte index of the scaling region 
    scale_h_end_BIdx =  (((h_end<<9)/h_step)>>pix2byte_shift)+(scaling_region_p->ratio.x_dividend/scaling_region_p->ratio.x_divisor);
    if(scale_h_end_BIdx>=scaling_osd_w) scale_h_end_BIdx = scaling_osd_w-1;
        
    h_cnt_total = (scale_h_start_BIdx<<pix2byte_shift)*h_step;    // if the start position of copy isn't (0,0) of original osd region,
                                                                                               // we have to calculate the offset from the (0,0) .
#ifdef DEBUG_OSD_REG_COPY
    printf_w(__FUNCTION__ " h_cnt_total:%d, scale_h_start_BIdx:%d, scale_h_end_BIdx:%d\n", h_cnt_total, scale_h_start_BIdx, scale_h_end_BIdx);
#endif

    for(scalingBIdx=scale_h_start_BIdx; scalingBIdx<=scale_h_end_BIdx; scalingBIdx++) {
        BYTE originB=0, scalingB=0;
        BYTE temp_pixel = 0;
        int i;

        switch (osd_format)
        {
            case OSD_FORMAT_2COLOR:
                for(i=0; i<8; i++) { 
                    h_index = h_cnt_total>>9 ;         // h_index = h_cnt_total /512;
                    h_cnt = (h_cnt_total & 0x01FF);    // h_cnt = h_cnt_total % 512;
                    originBIdx = h_index>>3;           // originBIdx = h_index / 8;
                    originPIdx = (h_index & 0x07);     // originPIdx = h_index % 8;
                    if((originPIdx==3) && (h_cnt>256)) {
                        originBIdx++;
                        originPIdx = 0;
                        h_cnt = 0;
                    }	
                                        
                    originB = pLine_origin[originBIdx];
                    // sample byte for scaling over the origin osd byte width
                    if(originBIdx>=origin_osd_w) {
                        originB = pLine_origin[origin_osd_w-1];
                    }
                                    
                    if(originPIdx ==0 && h_cnt<=256) {
                        temp_pixel = (originB & 0x80)>>7;
                    }
                    else if((originPIdx ==0 && h_cnt>256) || (originPIdx == 1 && h_cnt<=256 )) {
                        temp_pixel = (originB & 0x40)>>6;
                    }
                    else if((originPIdx ==1 && h_cnt>256) || (originPIdx == 2 && h_cnt<=256 )) {
                        temp_pixel = (originB & 0x20)>>5;
                    }	
                    else if((originPIdx ==2 && h_cnt>256) || (originPIdx == 3 && h_cnt<=256 )) {
                        temp_pixel = (originB & 0x10)>>4;
                    }
                    else if((originPIdx ==3 && h_cnt>256) || (originPIdx == 4 && h_cnt<=256 )) {
                        temp_pixel = (originB & 0x08)>>3;
                    }
                    else if((originPIdx ==4 && h_cnt>256) || (originPIdx == 5 && h_cnt<=256 )) {
                        temp_pixel = (originB & 0x04)>>2;
                    }
                    else if((originPIdx ==5 && h_cnt>256) || (originPIdx == 6 && h_cnt<=256 )) {
                        temp_pixel = (originB & 0x02)>>1;
                    }
                    else if((originPIdx ==6 && h_cnt>256) || (originPIdx == 7 && h_cnt<=256 )) {
                        temp_pixel = (originB & 0x01);
                    }
                        
                    scalingB = (scalingB<<1) | temp_pixel;
                                       
                    h_cnt_total += h_step;				
                }
                pLine_scaling[scalingBIdx] = scalingB;

                break;
        
            case OSD_FORMAT_4COLOR:
                for(i=0; i<4; i++) { 
                    h_index = h_cnt_total>>9 ;
                    h_cnt = (h_cnt_total & 0x01FF);
                    originBIdx = h_index>>2;
                    originPIdx = (h_index & 0x03);
                    if((originPIdx==3) && (h_cnt>256)) {
                        originBIdx++;
                        originPIdx = 0;
                        h_cnt = 0;
                    }	
                                    
                    originB = pLine_origin[originBIdx];
                    // sample byte for scaling over the origin osd byte width
                    if(originBIdx>=origin_osd_w) {
                        originB = pLine_origin[origin_osd_w-1];
                    }
                                
                    if(originPIdx ==0 && h_cnt<=256) {
                        temp_pixel = (originB & 0xC0)>>6;
                    }
                    else if((originPIdx ==0 && h_cnt>256) || (originPIdx == 1 && h_cnt<=256 )) {
                        temp_pixel = (originB & 0x30)>>4;
                    }
                    else if((originPIdx ==1 && h_cnt>256) || (originPIdx == 2 && h_cnt<=256 )) {
                        temp_pixel = (originB & 0x0C)>>2;
                    }	
                    else if((originPIdx ==2 && h_cnt>256) || (originPIdx == 3 && h_cnt<=256 )) {
                        temp_pixel = (originB & 0x03);
                    }

                    scalingB = (scalingB<<2) | temp_pixel;
                                   
                    h_cnt_total += h_step;				
                }
                pLine_scaling[scalingBIdx] = scalingB;

                break;
 
            case OSD_FORMAT_16COLOR:
                for(i=0; i<2; i++) {	
                    h_index = h_cnt_total>>9;
                    h_cnt = (h_cnt_total & 0x01FF);
                    originBIdx = h_index >> 1;
                    originPIdx = (h_index & 0x01);                    
                    if((originPIdx==1) && (h_cnt>256)) {
                        originBIdx++;
                        originPIdx = 0;
                        h_cnt = 0;
                    }

                    originB = pLine_origin[originBIdx];
                    // sample byte for scaling over the origin osd byte width
                    if(originBIdx>=origin_osd_w){
                        originB = pLine_origin[origin_osd_w-1];
                    }
					
                    if(originPIdx == 0 && h_cnt<=256) {
                        temp_pixel = (originB & 0xF0) >> 4;
                    }
                    else if((originPIdx == 0 && h_cnt>256) || (originPIdx == 1 && h_cnt<=256)) {
                        temp_pixel = (originB & 0x0F);
                    }		

                    scalingB = (scalingB<<4) | temp_pixel;
                    h_cnt_total += h_step;
                    
                }
                pLine_scaling[scalingBIdx] = scalingB;

                break;
            }	
        
	}

}

#endif    
    
#else////old OSD mode//denghg add it.20061013//#if 1

void osd_scaling_region()
{

	scaling_t_osd_region* scaling_region_p;
	t_osd_region *region_pointer;
	
	t_osdv2_header *pTop_origin, *pBot_origin;
	t_osdv2_header *pTop_scaling, *pBot_scaling;

	BYTE *osdfrom    = get_osdbuf_baseptr(); 
	BYTE *pLine_origin, *pLine_scaling;	
//	BYTE    *origin_osd, *scaling_osd;
	int  uiRegionIdx;

	UINT16 v_index, v_step, v_cnt;;
	UINT32 v_cnt_total;	
	UINT16 i;
	UINT16 origin_osd_h, origin_osd_w, scaling_osd_h, scaling_osd_w;
	UINT32 osd_loc, scaling_loc;
//printf_w(__FUNCTION__  " osd_active_regions:%d \n", osd_active_regions);
       for (uiRegionIdx = 0; uiRegionIdx < osd_active_regions; uiRegionIdx++) {
		scaling_region_p = &scaling_region[uiRegionIdx];
		region_pointer = &region[uiRegionIdx];

		origin_osd_h = region_pointer->osd_h;
		origin_osd_w = region_pointer->osd_w;

		scaling_osd_h = scaling_region_p->osd_h;
		scaling_osd_w = scaling_region_p->osd_w;
		
		pTop_origin = osd_get_region_pointer(uiRegionIdx, 0);
		pBot_origin = osd_get_region_pointer(uiRegionIdx, 1);

		pTop_scaling = osd_get_scaling_region_p(uiRegionIdx, 0);
		pBot_scaling = osd_get_scaling_region_p(uiRegionIdx, 1);
		
		v_cnt_total=0;
		v_step = 256*(scaling_region_p->ratio.y_divisor)/(scaling_region_p->ratio.y_dividend);
//printf_w("origin_osd_h:%x, scaling_osd_h:%x, v_step:%x, ..............................Robert\n", origin_osd_h, scaling_osd_h, v_step);

		for(i=0; i<scaling_osd_h; i++) {
			v_cnt = v_cnt_total % 256;
			v_index = v_cnt_total / 256; 
//printf_w("v_cnt:%x, v_index:%x\n", v_cnt, v_index);
			if(v_index>=origin_osd_h  && v_cnt>128) return;  

			if ((i & 0x01) && (p_scan ==0))
			{
				pLine_scaling = (UINT8 *)(osdfrom + (SWAP16(pBot_scaling->link_data) <<5));
				//printf("pBtmLine\n");
			}	
			else
			{
				pLine_scaling = (UINT8 *)(osdfrom + (SWAP16(pTop_scaling->link_data) <<5));
				//printf("pTopLine\n");
			}			

			if(p_scan == 1) {
				pLine_origin = (UINT8 *)(get_osdbuf_baseptr() + (SWAP16(pTop_origin->link_data) <<5));				
				scaling_loc = i*scaling_osd_w;
				if(v_cnt<=128)
					osd_loc = v_index*origin_osd_w;
				else
					osd_loc = (v_index+1)*origin_osd_w;
			}	
			else {
				scaling_loc = (i/2)*scaling_osd_w;
				
				if(v_index & 0x01) {
					if(v_cnt<=128) {
						pLine_origin = (UINT8 *)(osdfrom + (SWAP16(pBot_origin->link_data) <<5));
						osd_loc = (v_index/2)*origin_osd_w;
					}
					else {
						pLine_origin = (UINT8 *)(osdfrom + (SWAP16(pTop_origin->link_data) <<5));
						osd_loc = ((v_index+1)/2)*origin_osd_w;
					}		
				}
				else {
					if(v_cnt<=128) {
						pLine_origin = (UINT8 *)(osdfrom + (SWAP16(pTop_origin->link_data) <<5));
						osd_loc = (v_index/2)*origin_osd_w;
					}
					else {
						pLine_origin = (UINT8 *)(osdfrom + (SWAP16(pBot_origin->link_data) <<5));
						osd_loc = (v_index/2)*origin_osd_w;
					}
				}		

			}	
			osd_scaling_copy( uiRegionIdx, &pLine_scaling[scaling_loc], &pLine_origin[osd_loc] );

			v_cnt_total += v_step;	
			
		}
       }
       
}

void osd_scaling_copy(int uiRegionIdx, BYTE *pLine_scaling, const BYTE *pLine_origin)
{
	scaling_t_osd_region* scaling_region_p;
	t_osd_region *region_pointer;
	UINT16 origin_osd_w, scaling_osd_w;
	
	scaling_region_p = &scaling_region[uiRegionIdx];
	region_pointer = &region[uiRegionIdx];
	
	origin_osd_w = region_pointer->osd_w;
	scaling_osd_w = scaling_region_p->osd_w;

	UINT8 osd_format = region_pointer->osd_format;	
	
//	UINT8 h_cnt, h_step;
	UINT16  h_index, h_cnt, h_step, h_step1;
	UINT32 h_cnt_total;
	UINT16 originBIdx, scalingBIdx, originPIdx;

	h_cnt_total = 0;
	h_step1 = 512*(scaling_region_p->ratio.x_divisor)/(scaling_region_p->ratio.x_dividend);
	h_step = 512*origin_osd_w/scaling_osd_w;
//printf_w(__FUNCTION__ " h_step1:%d, h_step:%d\n", h_step1, h_step);
///printf_w(__FUNCTION__ " origin_osd_w:%d  scaling_osd_w:%d \n", origin_osd_w, scaling_osd_w);
	for(scalingBIdx=0; scalingBIdx<scaling_osd_w; scalingBIdx++) {

		BYTE originB=0, scalingB=0;
		BYTE temp_pixel = 0;
		int i;

		switch (osd_format)
		{
			case OSD_FORMAT_4COLOR:
				for(i=0; i<4; i++) { 
					h_index = h_cnt_total /512;
					h_cnt = h_cnt_total % 512;
					originBIdx = h_index / 4;
					originPIdx = h_index % 4;
					if((originPIdx==3) && (h_cnt>256)) {
						originBIdx++;
						originPIdx = 0;
						h_cnt = 0;
					}	


					originB = pLine_origin[originBIdx];
/// printf_w(__FUNCTION__  "4 colors h_index:%d, h_cnt:%d, originBIdx%d, originPIdx:%d\n", h_index, h_cnt, originBIdx, originPIdx);                   
 ///printf_w(__FUNCTION__ " 4 colors h_cnt_total:%d scalingBIdx:%d, pLine_origin:%d, originBIdx:%d,  originB:%d \n", h_cnt_total, scalingBIdx, pLine_origin, originBIdx, originB);	                   
					// sample byte for scaling over the origin osd byte width
					if(originBIdx>=origin_osd_w) {
                                       originB = pLine_origin[origin_osd_w-1];
                                    }
                                
					if(originPIdx ==0 && h_cnt<=256) {
						temp_pixel = (originB & 0xC0)>>6;
					}
					else if((originPIdx ==0 && h_cnt>256) || (originPIdx == 1 && h_cnt<=256 )) {
						temp_pixel = (originB & 0x30)>>4;
					}
					else if((originPIdx ==1 && h_cnt>256) || (originPIdx == 2 && h_cnt<=256 )) {
						temp_pixel = (originB & 0x0C)>>2;
					}	
					else if((originPIdx ==2 && h_cnt>256) || (originPIdx == 3 && h_cnt<=256 )) {
						temp_pixel = (originB & 0x03);
					}

					scalingB = (scalingB<<2) | temp_pixel;

					h_cnt_total += h_step;				
				}
				pLine_scaling[scalingBIdx] = scalingB;
//                    printf_w(__FUNCTION__ " 4 colors pLine_scaling:%d, scalingBIdx:%d,  scalingB:%d \n", pLine_scaling, scalingBIdx, scalingB);					
				break;
			case OSD_FORMAT_16COLOR:
				for(i=0; i<2; i++) {	
					h_index = h_cnt_total /512;
					h_cnt = h_cnt_total % 512;
					originBIdx = h_index / 2;
					originPIdx = h_index % 2;
					if((originPIdx==1) && (h_cnt>256)) {
						originBIdx++;
						originPIdx = 0;
						h_cnt = 0;
					}
					
					// sample byte for scaling over the origin osd byte width
					if(originBIdx>=origin_osd_w){
                                        originB = pLine_origin[origin_osd_w-1];
                                    }
					originB = pLine_origin[originBIdx];
					
					if(originPIdx == 0 && h_cnt<=256) {
						temp_pixel = (originB & 0xF0) >> 4;
					}
					else if((originPIdx == 0 && h_cnt>256) || (originPIdx == 1 && h_cnt<=256)) {
						temp_pixel = (originB & 0x0F);
					}		

					scalingB = (scalingB<<4) | temp_pixel;
					
					h_cnt_total += h_step;
				}
				pLine_scaling[scalingBIdx] = scalingB;
//                    printf_w(__FUNCTION__ " 16 colors originBIdx:%d,  scalingBIdx:%d \n", originBIdx, scalingBIdx);				
				break;
		}	

	}
}
#endif//#if 1
#endif//#ifdef SUPPORT_SW_OSD_SCALING

