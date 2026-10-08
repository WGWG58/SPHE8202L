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
|  File Name    :  osd_api.h
|  Description  :  Provide functions of osd-hareware control and osd-drawsing
|  Version      :  1.0  
|  Compiler     : GCC for MIPS(R3000)
|  Platform     : Sunplus SPCA8202A DVD Player
|
|  Rev	Date	        Author(s)               Status & Comments
|---------------------------------------------------------------------------------
|  1.0	01/01/2005      joshua/stanleyc         Creating
|  1.1  03/29/2005      yltseng                 Modify some header
|  1.2  08/29/2005      yltseng                 Add function to get region size & position
|  1.3  10/28/2005      yltseng                 Add a function to set original region position
|--------------------------------------------------------------------------------*/ 
#ifndef __OSD_API_H
#define __OSD_API_H

#include "types.h"
#include "osd_drv.h"

/************************************************************************************
OSD Hardware-related API
************************************************************************************/

/***********************************************************************************/
//New functions are as follows:

UINT16 osd_calc_region_size(UINT8 md_value, UINT16 width_in_pixel, UINT16 height_in_pixel);
int osd_delete_region(UINT8 region_index);
int osd_find_previous_region(UINT8 region_index);
int osd_find_next_region(UINT8 region_index);
void osd_set_region_link_next_addr(UINT8 region_index, UINT16 top_link_next, UINT16 btm_link_next);
//void osd_update_display_list(void);
UINT8 osd_check_overlap(UINT16 y_temp, UINT16 height_temp, UINT8 skipped_region);
int osd_insert_regions(_t_osd_hdr *hdrp, UINT8 region_index);
int osd_set_region_position(UINT8 region_index, UINT16 x, UINT16 y);
void osd_update_region_links(void);
void osd_set_palette_color(UINT8 region_index, UINT8 palette_index, UINT32 color);
void osd_set_palette_color_of_multi_regions(UINT8 region_start, UINT8 region_end,
								UINT8 palette_index, UINT32 color);
UINT16 osd_pixel_to_byte(UINT16 pixel_width, UINT8 format);
UINT16 osd_byte_to_pixel(UINT16 byte_width, UINT8 format);
#ifdef OSD_AUTO_RECOVER
UINT16	osd_get_header_chksum(UINT32 reg_idx, UINT32 field);
void osd_auto_recover();
#endif
//coordinate *osd_calc_address_to_pixel(UINT32 addr, UINT32 region_index, UINT32 field);

extern UINT32  osd_get_current_region_size( UINT32 uiRegion, dimension* pSize );
extern UINT32  osd_get_current_region_position( UINT32 uiRegion, coordinate* pPos );

extern UINT32  osd_get_original_region_size( UINT32 uiRegion, dimension* pSize );
extern UINT32  osd_get_original_region_position( UINT32 uiRegion, coordinate* pPos );
extern UINT32  osd_set_original_region_position( UINT32 uiRegion, coordinate* pPos );
/***********************************************************************************/
//Old functions are as follows:

void osd_disable(void);
void osd_enable(void);
void reset_osd();
void ENABLE_OSD(void);
void DISABLE_OSD(void);
void __osd_init(void);
void osd_init__(void);
void InitSW_region(void);
void SetOsdCol(UINT8 rb, UINT8 re, UINT8 id, UINT32 color);
UINT32 GetOsdCol(UINT8 r, UINT8 id);
void osd_tog_region(BYTE r, int mode);
int osd_init_regions(int n, const _t_osd_hdr *hdrp);
void osd_create_region1(UINT8 region_index, int X, int Y, t_osd_region *prev,BYTE bColorMode,BYTE bScanMode);
UINT32 osd_rescale_color(UINT32 uiColor);
UINT8 *get_osdbuf_region_ptr(int _region, int _field);
//void MoveRegion(BYTE r,UINT16 x,UINT16 y);

/************************************************************************************
OSD Drawing-related API
************************************************************************************/

/***********************************************************************************/
//New functions are as follows:

int osd_draw_rectangle(coordinate *start,
					dimension *in_dimension, UINT16 color, UINT8 region_index);
					
void osd_draw_rectangle_outline(coordinate *start, dimension *in_dimension,
							UINT16 line_width, UINT16 color, UINT8 region_index);
							
void osd_draw_region_outline(UINT16 line_width, UINT16 color, UINT8 region_index);

int osd_draw_horizontal_line(UINT16 start_x, UINT16 end_x,
				UINT16 y, UINT16 color, UINT16 width, UINT8 region_index);

int osd_draw_vertical_line(UINT16 x, UINT16 start_y,
				UINT16 end_y, UINT16 color, UINT16 width, UINT8 region_index);

void osd_draw_button_border(coordinate *start, coordinate *end,
						int bDown, unsigned mask, UINT8 region_index);

int osd_fill_region(UINT8 region_index, UINT16 color);

void osd_draw_font_bitmap(const UINT8* pFont, coordinate *start, dimension *in_dimension,
					font_palette *palette, int region_index, int only_font_color);

int osd_draw_bmp(coordinate *start, const BYTE* bmp,  BYTE region_index);			

void osd_draw_bitmap(UINT8 region_index, coordinate *start, const UINT8* pbmp, dimension *in_dimension, 
                      UINT8 pixel_size, UINT8 only_fore_color, font_palette *palette);

int osd_draw_data(DrawAttribute *_draw_attribute);
/***********************************************************************************/

#include "osd_hw_highlight.h"

#endif  //#ifdef __OSD_API_H
