#include "config.h"
#include "global.h"
#include "osd_palette.h"
#include "osd_api.h"

/***********************************************************************************/

#ifndef DVDRELEASE
    #define OSD_HL_DBG
#endif

#define osd_puts(s)         do {} while (0)
#define osd_printf(s...)    do {} while (0)

#ifdef OSD_HL_DBG
    #undef  osd_puts
    #undef  osd_printf
    
    #include "emuio.h"
    #include "sio.h"
    
    extern UINT8   lbuf2[128];
    #define osd_puts(s)         io_write_wait(s)
    #define osd_printf(s...)    do {psprintf(lbuf2, ##s); osd_puts(lbuf2);} while (0)
#endif

/***********************************************************************************/

#define osd_get_highlight_pointer( uiRegionIdx ) \
    (OSD_HIGHLIGHT_HEADER *)(get_osdbuf_baseptr()+ (region[osd_display_list[uiRegionIdx]].osd_highlight<< 5))
    
#define osd_get_region_pointer( uiRegionIdx, uiField ) \
    (t_osdv2_header*)(get_osdbuf_baseptr() + (region[osd_display_list[uiRegionIdx]].osd_header[uiField]<< 5))

#define osd_get_region_palette_pointer( uiRegionIdx, uiField ) \
    (UINT8*)(((UINT32)osd_get_region_pointer(uiRegionIdx, uiField)) + HEADER_SIZE)

#define osd_get_palette_entry_count( uiRegionIdx ) \
    (( region[uiRegionIdx].osd_format == OSD_FORMAT_2COLOR ) ? 2 : 4 )
    
#define osd_get_palette_entry_size( uiRegionIdx, uiField ) \
    ((((const UINT8*) osd_get_region_pointer( uiRegionIdx, uiField ))[2] & V2_CLUT_TYPE(0x11) ) ? 4 : 2 )
    
/***************************************************************************
* Function: All highlight function  
* Purposes: Show additional highlight region on 2/4 color osd region 
* Description: There are two highlight regions and we could use these region to add 
*                   the other color on 2/4 color regions.       
*Function feature:
*   H/W version: 8202L
*                      Because H/W limitation, so the highlight region width have to be 32 bit unit.
*                      We use "highlight 0" to cover the redundant area of "highlight 1" for highlight 1 fit 
*                      the length of osd strings.So, we have only a highlight region to use.
*  H/W version: 8203A
*                      The H/W allow we use the pixel for the width unit.So, there isn't a alignment problem of 
*                      8202L and we could use 2 highlight regions.
*
* Create: robert.chang
* Modify: robert.chang, 2006/09/22 
*                           
***************************************************************************/

static UINT8* osd_get_highlight_palette_N_pointer( UINT32 uiRegionIdx, UINT32 uiField, UINT32 uiSubHighlight, UINT32 uiNthPaletteIdx )
{
    UINT32  uiClutCount = osd_get_palette_entry_count( uiRegionIdx );

#ifdef OSD_HL_DBG
    if( uiNthPaletteIdx >= uiClutCount )
    {
        osd_printf( "osd_get_highlight_palette_N_pointer: Nth palette index overflow\n" );
        return NULL;
    }
#endif
    UINT32 uiClutSize = osd_get_palette_entry_size( uiRegionIdx, uiField );

    return (UINT8*) (osd_get_region_palette_pointer(uiRegionIdx, uiField) + (uiClutCount * (uiSubHighlight + 1) + uiNthPaletteIdx) * uiClutSize);
}

/***********************************************************************************/
UINT8* osd_get_highlight_palette_pointer( UINT32 uiRegionIdx, UINT32 uiField, UINT32 uiSubHighlight   __attribute__((unused)))
{
    #ifdef IC_8202L
    return osd_get_highlight_palette_N_pointer( uiRegionIdx, uiField, 1, 0 );
    #else
    return osd_get_highlight_palette_N_pointer( uiRegionIdx, uiField, uiSubHighlight, 0 );
    #endif
}

/***********************************************************************************/
void osd_set_highlight_palette_color( UINT32 uiRegion,  UINT32 uiSubHighlight  __attribute__((unused)), UINT32 uiPaletteIdx, UINT32 uiColor )
{
#ifdef OSD_HL_DBG
    const t_osd_region*   pRegionInfo = &region[osd_display_list[uiRegion]];
    if( !pRegionInfo->osd_highlight )
    {
        osd_printf( "osd_set_highlight_palette_color: not support highlight\n" );
        return;
    }
#endif

    UINT32  uiClutSize;
    UINT8*  pRegion     = (UINT8*) osd_get_region_pointer( uiRegion, 0 );
    if( pRegion[2] & V2_CLUT_TYPE(0x11) )
        uiClutSize  = 4;    // 32 bit(0x01) or 27 bit(0x10)
    else
        uiClutSize  = 2;    // 16 bit color(0x00)

    UINT32 i;
    for( i = 0; i < 2; i++ )
    {
     
#ifdef IC_8202L
        void* pData = osd_get_highlight_palette_N_pointer( uiRegion, i, 1, uiPaletteIdx );
#else
        void* pData = osd_get_highlight_palette_N_pointer( uiRegion, i, uiSubHighlight, uiPaletteIdx );
#endif

        if( uiClutSize == 2 )
            wbe16( pData, uiColor );
        else
            wbe32( pData, uiColor );
    }
}

/***********************************************************************************/
void osd_move_sub_highlight( UINT32 uiRegionIdx, UINT32 uiSubHighlight  __attribute__((unused)), coordinate coord )
{
    const t_osd_region*   pRegionInfo = &region[osd_display_list[uiRegionIdx]];

#ifdef OSD_HL_DBG
    if( !pRegionInfo->osd_highlight )
    {
        osd_printf( "osd_move_sub_highlight: Nth palette index overflow\n" );
        return;
    }
#endif

    // Input Y position is also in progressive mode, we also must divide it
    // by 2 in interlaced mode    
    if(!p_scan)
        coord.y     >>= 1;

    OSD_HIGHLIGHT_HEADER* pHighlight = osd_get_highlight_pointer( uiRegionIdx );
    
#ifdef IC_8202L   // when we move the highlight 1, the highlight 0 have to move depending on highlight 1  
    UINT16* pCoord0 = (UINT16*)&(pHighlight->uiHL1_VStart);
    UINT16* pCoord1 = (UINT16*)&(pHighlight->uiHL2_VStart);

    wbe16( pCoord1,      coord.y );
    wbe16( pCoord1+1,    coord.x );

    wbe16( pCoord0,      coord.y );
    wbe16( pCoord0+1,    coord.x+pRegionInfo->osd_highlight_w );
#else
    UINT16* pCoord = uiSubHighlight ? ((UINT16*)&(pHighlight->uiHL2_VStart)) : ((UINT16*)&(pHighlight->uiHL1_VStart));

    wbe16( pCoord,      coord.y );
    wbe16( pCoord+1,    coord.x );
#endif
}

/***********************************************************************************/
void osd_resize_sub_highlight( UINT32 uiRegionIdx, UINT32 uiSubHighlight __attribute__((unused)), dimension dim )
{
    t_osd_region*   pRegionInfo = &region[osd_display_list[uiRegionIdx]];
    
#ifdef OSD_HL_DBG
    if( !pRegionInfo->osd_highlight )
    {
        osd_printf( "osd_resize_sub_highlight: Nth palette index overflow\n" );
        return;
    }
#endif

#ifdef  IC_8202L 
    pRegionInfo->osd_highlight_w = dim.x_length;

    // Input width is in pixel based, but HW only accept 32bit input value
    // that is, for 2 color highlight, pixel can only be 32 pixel aligned ( 32 / 1 = 32 )
    // for 4 color highlight, pixel can only be 16 pixel aligned ( 32 / 2 = 16 )
    UINT32  uiPixelAlignment = ( pRegionInfo->osd_format == OSD_FORMAT_2COLOR ) ? 32 : 16;
    dim.x_length = ( dim.x_length + uiPixelAlignment - 1 ) / uiPixelAlignment;

    // Input height is in progressive scan mode, if current setting is interlaced,
    // we must divide it by 2
    if(!p_scan)
        dim.y_length /= 2;
    
    OSD_HIGHLIGHT_HEADER* pHighlight = osd_get_highlight_pointer( uiRegionIdx );    

    // set size of HL1    
    wbe16( &(pHighlight->uiHL2_VLength), dim.y_length );
    wbe16( &(pHighlight->uiHL2_HLength), dim.x_length );

    // set height of HL0
    UINT32 uiVal = SWAP16(pHighlight->uiHL12Switch_N_HL1_VLength);
    uiVal = (uiVal & 0xC000) | dim.y_length;
    wbe16( &(pHighlight->uiHL12Switch_N_HL1_VLength), uiVal );

    // set x pos of HL0
    wbe16( &(pHighlight->uiHL1_HStart), SWAP16(pHighlight->uiHL2_HStart) + pRegionInfo->osd_highlight_w );
#else

    // Input height is in progressive scan mode, if current setting is interlaced,
    // we must divide it by 2
    if(!p_scan)
        dim.y_length /= 2;
    
    OSD_HIGHLIGHT_HEADER* pHighlight = osd_get_highlight_pointer( uiRegionIdx );


    if( uiSubHighlight )
    {
        wbe16( &(pHighlight->uiHL2_VLength), dim.y_length );
        wbe16( &(pHighlight->uiHL2_HLength), dim.x_length );
    }
    else
    {
        UINT32 uiVal = SWAP16(pHighlight->uiHL12Switch_N_HL1_VLength);
        uiVal = (uiVal & 0xC000) | dim.y_length;

        wbe16( &(pHighlight->uiHL12Switch_N_HL1_VLength), uiVal );
        wbe16( &(pHighlight->uiHL1_HLength), dim.x_length );
    } 

#endif
}
       
/***********************************************************************************/
void osd_set_highlight_palette( UINT32 uiRegionIdx, UINT32 uiSubHighlight __attribute__((unused)), const UINT8* pPalette )
{
    const t_osd_region*   pRegionInfo = &region[osd_display_list[uiRegionIdx]];
    
#ifdef OSD_HL_DBG
    if( !pRegionInfo->osd_highlight )
    {
        osd_printf( "osd_set_highlight_palette: Nth palette index overflow\n" );
        return;
    }
#endif

    UINT32  uiClutCount = ( pRegionInfo->osd_format == OSD_FORMAT_2COLOR ) ? 2 : 4;    

    UINT32  uiClutSize;
    UINT8*  pRegion     = (UINT8*) osd_get_region_pointer( uiRegionIdx, 0 );
    if( pRegion[2] & V2_CLUT_TYPE(0x11) )
        uiClutSize  = 4;    // 32 bit(0x01) or 27 bit(0x10)
    else
        uiClutSize  = 2;    // 16 bit color(0x00)

    UINT32 i, j;
    for( i = 0; i < 2; i++ )
    {
        const UINT8* pSrcPalette    = pPalette;
     
#ifdef IC_8202L
        UINT8* pDstPalette          = osd_get_highlight_palette_N_pointer( uiRegionIdx, i, 1, 0 );
#else
        UINT8* pDstPalette          = osd_get_highlight_palette_pointer( uiRegionIdx, i, uiSubHighlight );
#endif
        
        for( j = 0; j < uiClutCount; j++ )
        {
            if( uiClutSize == 2 )
            {
                wbe16( pDstPalette, *((UINT16*) pSrcPalette) );
                pDstPalette += 2;
                pSrcPalette += 2;
            }
            else
            {
                wbe32( pDstPalette, *((UINT32*) pSrcPalette) );
                pDstPalette += 4;
                pSrcPalette += 4;
            }
        }
    }
}

/***********************************************************************************/
void osd_toggle_sub_highlight( UINT32 uiRegionIdx, UINT32 uiSubHighlight  __attribute__((unused)), UINT32 uiMode )
{
    #define HL1_SWITCH_BIT  15
    #define HL2_SWITCH_BIT  14
    
    OSD_HIGHLIGHT_HEADER*   pHighlight      = osd_get_highlight_pointer( uiRegionIdx );

#ifdef IC_8202L
    UINT32 uiMask   = 0x03 << HL2_SWITCH_BIT;
#else
    UINT32 uiMask   = uiSubHighlight ? (0x01 << HL2_SWITCH_BIT): (0x01 << HL1_SWITCH_BIT);
#endif

    UINT32 uiValue  = SWAP16(pHighlight->uiHL12Switch_N_HL1_VLength);
    
    switch( uiMode )
    {
    case OSD_OFF:
        uiValue &= ~uiMask;;
        break;
        
    case OSD_ON:
        uiValue |= uiMask;
        break;

    case OSD_TOG:
        uiValue ^= uiMask;
        break;
    }

    wbe16( &(pHighlight->uiHL12Switch_N_HL1_VLength), uiValue );
}

/***********************************************************************************/
static inline void osd_update_highlight_link( UINT32 uiRegionIdx, UINT32 uiEnable )
{
    const t_osd_region*     pRegionInfo     = &region[osd_display_list[uiRegionIdx]];
    t_osdv2_header*         pTopRegion      = osd_get_region_pointer( uiRegionIdx, 0 );
    t_osdv2_header*         pBottomRegion   = osd_get_region_pointer( uiRegionIdx, 1 );
    OSD_HIGHLIGHT_HEADER*   pHighlight      = osd_get_highlight_pointer( uiRegionIdx );

    if( uiEnable )
    {
        pHighlight->uiLinkNextTop   = pTopRegion->link_next;
        pHighlight->uiLinkNextBottom= pBottomRegion->link_next;
        wbe16( &(pTopRegion->link_next), pRegionInfo->osd_highlight );
        wbe16( &(pBottomRegion->link_next), pRegionInfo->osd_highlight );
    }
    else
    {
        pTopRegion->link_next       = pHighlight->uiLinkNextTop;
        pBottomRegion->link_next    = pHighlight->uiLinkNextBottom;
    }
}

/***********************************************************************************/
void osd_toggle_highlight( UINT32 uiRegionIdx, UINT32 uiMode )
{
#ifdef OSD_HL_DBG
    const t_osd_region* pRegionInfo = &region[osd_display_list[uiRegionIdx]];    
    if( !pRegionInfo->osd_highlight )
    {
        osd_printf( "osd_toggle_highlight: Nth palette index overflow\n" );
        return;
    }
#endif

    #define HIGHLIGHT_MASK  (0x01<<BIT_HIGHLIGHT)

    UINT32  i, uiConfig;
    for( i = 0; i < 2; i++ )
    {
        UINT8*  pRegion  = (UINT8*)osd_get_region_pointer( uiRegionIdx, i );
        uiConfig = pRegion[2];
        
        switch( uiMode )
        {
        case OSD_OFF:
            uiConfig &= ~HIGHLIGHT_MASK;
            break;
            
        case OSD_ON:
            uiConfig |= HIGHLIGHT_MASK;
            break;

        case OSD_TOG:
            uiConfig ^= HIGHLIGHT_MASK;
            break;
        }
        
        pRegion[2] = uiConfig;        
    }
    
    UINT32 uiEnable = ( uiConfig & (0x01 << BIT_HIGHLIGHT) ) ? TRUE : FALSE;
    osd_update_highlight_link( uiRegionIdx, uiEnable );
}

/***********************************************************************************/
void osd_set_highlight_header( UINT32  uiRegionIdx, OSD_HIGHLIGHT_HEADER stHighlightSrc )
{
    t_osd_region*   pRegionInfo = &region[osd_display_list[uiRegionIdx]];
    
#ifdef OSD_HL_DBG
    if( !pRegionInfo->osd_highlight )
    {
        osd_printf( "osd_set_highlight_header: Nth palette index overflow\n" );
        return;
    }
#endif

#ifdef  IC_8202L  
    pRegionInfo->osd_highlight_w = stHighlightSrc.uiHL2_HLength;
    
    // Input width is in pixel based, but HW only accept 32bit input value
    // that is, for 2 color highlight, pixel can only be 32 pixel aligned ( 32 / 1 = 32 )
    // for 4 color highlight, pixel can only be 16 pixel aligned ( 32 / 2 = 16 )
    UINT32  uiPixelAlignment = ( pRegionInfo->osd_format == OSD_FORMAT_2COLOR ) ? 32 : 16;
    stHighlightSrc.uiHL1_HLength = ( stHighlightSrc.uiHL1_HLength + uiPixelAlignment - 1 ) / uiPixelAlignment;
    stHighlightSrc.uiHL2_HLength = ( stHighlightSrc.uiHL2_HLength + uiPixelAlignment - 1 ) / uiPixelAlignment;
#endif

    if(!p_scan)
    {
        // Input height is in progressive scan mode, if current setting is interlaced,
        // we must divide it by 2
        UINT32 uiVal = stHighlightSrc.uiHL12Switch_N_HL1_VLength;
        stHighlightSrc.uiHL12Switch_N_HL1_VLength = (uiVal & 0xC000) | ((uiVal & 0x3FFF)>>1);
        stHighlightSrc.uiHL2_VLength    >>= 1;

        // Input Y position is also in progressive mode, we also must divide it
        // by 2 in interlaced mode
        stHighlightSrc.uiHL1_VStart     >>= 1;
        stHighlightSrc.uiHL2_VStart     >>= 1;
    }

    // Set input variable to OSD header region
    UINT16* pHeaderSrc = (UINT16*) &stHighlightSrc;
    UINT16* pHeaderDst = (UINT16*) osd_get_highlight_pointer( uiRegionIdx );
    UINT32 i;
    for( i = 0; i < 10; i++ )
        wbe16( &pHeaderDst[i], pHeaderSrc[i] );
}   
    
/***********************************************************************************/
void osd_init_highlights(void)
{   
    UINT32 i;
    for ( i = 0; i < osd_active_regions; i++)
    {
        t_osd_region*   pRegionInfo = &region[osd_display_list[i]];
        
        if( pRegionInfo->osd_format == OSD_FORMAT_2COLOR || 
            pRegionInfo->osd_format == OSD_FORMAT_4COLOR )
        {

#ifdef IC_8202L  // 8202L, copy color palette of osd region to color palette of "highlight 0"    
            // set highlight mask palette( use highlight 0 for mask )
            UINT32 j;
            for( j = 0; j < 2; j++ )
            {
                UINT8* pRegionPalette       = osd_get_region_palette_pointer(i, j);
                UINT8* pHighlightPalette    = osd_get_highlight_palette_N_pointer( i, j, 0, 0 );
                
                UINT32 uiClutCount  = osd_get_palette_entry_count(i);
                UINT32 uiClutSize   = osd_get_palette_entry_size(i, j);

                memcpy( pHighlightPalette, pRegionPalette, uiClutCount * uiClutSize );
            }			
#endif            
            // set highlight header address
            pRegionInfo->osd_highlight = osd_free;

#if 0//def SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
			
            OSD_HIGHLIGHT_HEADER osd_highlight;
            memset( &osd_highlight, 0, sizeof(OSD_HIGHLIGHT_HEADER) );
	     UINT32  uiPixelAlignment = ( pRegionInfo->osd_format == OSD_FORMAT_2COLOR ) ? 32 : 16;
					
            osd_highlight.uiHL12Switch_N_HL1_VLength    = osd_set_sub_highlight_config( 0 , 0, 24 );
            osd_highlight.uiHL1_HLength     = uiPixelAlignment;
            osd_highlight.uiHL1_VStart      = 0;
            osd_highlight.uiHL1_HStart      = 0;
            osd_highlight.uiHL2_VLength     = 24;
            osd_highlight.uiHL2_HLength     = uiPixelAlignment;
            osd_highlight.uiHL2_VStart      = 0;
            osd_highlight.uiHL2_HStart      = 0;
            osd_highlight.uiLinkNextTop     = 0;          
            osd_highlight.uiLinkNextBottom  = 0;        
					
	     osd_set_highlight_header( i, osd_highlight );
            osd_set_highlight_palette( i, (UINT8*)palette_4color_hl );
	     osd_toggle_highlight( i, 1);
#endif
			
            osd_free++;
        }
        else
        {
            pRegionInfo->osd_highlight = 0;
        }
        
        pRegionInfo->osd_highlight_w = 0;
    }
}

/***********************************************************************************/
