#ifndef __OSD_HW_HIGHLIGHT_H
#define __OSD_HW_HIGHLIGHT_H

#define	BIT_HIGHLIGHT   1       // [1]

typedef struct
{
    UINT16  uiHL12Switch_N_HL1_VLength; // uiHL1_Switch:1, uiHL2_Switch:1, uiHL1_VLength:14
    UINT16  uiHL1_HLength;      // 32-bit unit
    UINT16  uiHL1_VStart;
    UINT16  uiHL1_HStart;
    UINT16  uiHL2_VLength;
    UINT16  uiHL2_HLength;      // 32-bit unit
    UINT16  uiHL2_VStart;
    UINT16  uiHL2_HStart;
    UINT16  uiLinkNextTop;
    UINT16  uiLinkNextBottom;
} OSD_HIGHLIGHT_HEADER;

#define osd_set_sub_highlight_config( uiHL1_Switch, uiHL2_Switch, uiHL1_VLength ) \
    ((UINT16)((uiHL1_Switch << 15) | (uiHL2_Switch << 14) | (uiHL1_VLength & 0x3FFF)))

extern void     osd_init_highlights(void);
extern void     osd_set_highlight_header( UINT32  uiRegionIdx, OSD_HIGHLIGHT_HEADER stHighlightSrc );

extern void     osd_set_highlight_palette( UINT32 uiRegionIdx, UINT32 uiSubHighlight, const UINT8* pPalette );
extern void     osd_set_highlight_palette_color( UINT32 uiRegion,  UINT32 uiSubHighlight, UINT32 uiPaletteIdx, UINT32 uiColor );
extern UINT8*   osd_get_highlight_palette_pointer( UINT32 uiRegionIdx, UINT32 uiField, UINT32 uiSubHighlight );

extern void     osd_toggle_highlight( UINT32 uiRegionIdx, UINT32 uiMode );

extern void     osd_toggle_sub_highlight( UINT32 uiRegionIdx, UINT32 uiSubHighlight, UINT32 uiMode );

extern void     osd_move_sub_highlight( UINT32 uiRegionIdx, UINT32 uiSubHighlight, coordinate coord );
extern void     osd_resize_sub_highlight( UINT32 uiRegionIdx, UINT32 uiSubHighlight, dimension dim );

#endif  //#ifdef __OSD_HW_HIGHLIGHT_H
