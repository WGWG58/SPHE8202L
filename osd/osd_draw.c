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
|  File Name    :  osd_draw.c
|  Description  :  Provide functions of osd-hareware control and osd-drawsing
|  Version      :  1.0  
|  Compiler     : GCC for MIPS(R3000)
|  Platform     : Sunplus SPCA8202A DVD Player
|
|  Rev	Date	        Author(s)               Status & Comments
|---------------------------------------------------------------------------------
|  1.0	01/01/2005      joshua/stanleyc         Creating
|--------------------------------------------------------------------------------*/ 

//Note: Each new function should be externed by osd_api.h (update osd_draw.c and osd_api.h)

/************************************************************************************
OSD drawing-related API
************************************************************************************/

#include "config.h"
#include "regmap.h"
#include "global.h"

#include "osd_api.h"
#include "osd_palette.h"

#ifndef DVDRELEASE
#define OSD_DBG         1
UINT8 osdbuf[100];//terry,2003/9/26 03:37PM
#else
#define osdbuf linebuf
#endif

#define osd_puts(s)         do {} while (0)
#define osd_printf(s...)    do {} while (0)

#ifdef OSD_DBG
#undef  osd_puts
#undef  osd_printf
#include "emuio.h"
#include "sio.h"
UINT8   lbuf2[128];
#define osd_puts(s)         io_write_wait(s)
#define osd_printf(s...)    do {psprintf(lbuf2, ##s); osd_puts(lbuf2);} while (0)
#endif


#ifdef NEW_OSD_DRIVER
#if SUPPORT_OSD
/***********************************************************************************/
//New functions are as follows:

//////////////////////////////////////////////////////
// For drawing a rectangle
//	start:			upper left coordinate				(in pixel)
//	in_dimension:   width and height of rectangle       (in pixel)
//	color:			color index according to color format(2, 4, 16, 256, 16bit)
//	region_index:	region index to draw
//	Return:         [ 0 = drawing ok]
//      			[-1 = region is deleted, not in the list]
//					[-2 = rectangle length(width) > region length(width)]
//					[-3 = 256 color not supported]
//					[-4 = 2 color not supported]
//#define DEBUG_OSD_DRAW_RECTANGLE_BASIC
//#define DEBUG_OSD_DRAW_RECTANGLE
//#define DEBUG_OSD_DRAW_RECTANGLE_DIRECT_COLOR
int osd_draw_rectangle(coordinate *start,
					dimension *in_dimension, UINT16 color, UINT8 region_index)
{
    int idx;
    t_osd_region *region_pointer = &region[region_index];
#ifdef   SUPPORT_SW_OSD_SCALING    
    scaling_t_osd_region *scale_region_p = &scaling_region[region_index];
#endif
    UINT16 region_osd_format, region_width, region_height, start_x, start_y, length, width;
    UINT16 region_width_byte, region_length_byte, start_byte, end_byte;
    UINT16 head_color, tail_color, head_background_mask, tail_background_mask;
    UINT16 i, j;
    UINT8	x_remainder;
    UINT8 *p, *pTopLine, *pBtmLine;
    UINT16 *p16;
    t_osdv2_header  *T, *B;
    
    i = j=0;
//    length = width  = 0;
//    region_width = region_height = 0;

    p = NULL;
    p16 = NULL;
    
    for(idx=0; idx<2 ;idx++) {
        if(idx==0) {
//            region_pointer = &region[region_index];
            region_width = region_pointer->osd_w;

            region_osd_format = region_pointer->osd_format;
	     start_x = start->x;
	     start_y = start->y;
	     length = in_dimension->x_length;
	     width = in_dimension->y_length;

	     x_remainder = 0;
	#ifdef DEBUG_OSD_DRAW_RECTANGLE_BASIC
	osd_printf("\nregion[region_index].osd_format=%d\n",region[region_index].osd_format);
	osd_printf("=>start.x: %d\n", start_x);
	osd_printf("=>start.y: %d\n", start_y);
	osd_printf("=>x_length: %d\n", in_dimension->x_length);
	osd_printf("=>y_length: %d\n", in_dimension->y_length);
	osd_printf("=>color: %d\n", color);
	osd_printf("=>region_index: %d\n", region_index);
	osd_printf("=>region_width: %d\n", osd_byte_to_pixel(region_width, region[region_index].osd_format));
	osd_printf("=>region_height: %d\n", region[region_index].osd_h);
	delay_1ms(5);
	#endif

	    if (region_pointer->osd_used == 0)
		return -1;

	// if length > region length
	    if ((start_x + length) > osd_byte_to_pixel(region_width, region_osd_format))
		return -2;
	    if ((width+start_y) > region_pointer->osd_h)	// if height > region height
	    {
                #ifdef DEBUG_OSD_DRAW_RECTANGLE
	        osd_printf("Drawing rectangle failed, -2: height > region height\n");
		 osd_printf("Region height: %d\n", region_pointer->osd_h);
		 osd_printf("Start.y: %d\n", start_y);
		 osd_printf("Rect height: %d\n", width);
                #endif
		 return -2;
	    }

	//initialize buffer start
	    T = (t_osdv2_header *)(get_osdbuf_baseptr()+ region_pointer->osd_header[0]*32);
	    B = (t_osdv2_header *)(get_osdbuf_baseptr()+ region_pointer->osd_header[1]*32);
	
	    pTopLine = (UINT8 *)(get_osdbuf_baseptr() + (SWAP16(T->link_data) * 32));
	    pBtmLine = (UINT8 *)(get_osdbuf_baseptr() + (SWAP16(B->link_data) * 32));

        }   
#ifdef   SUPPORT_SW_OSD_SCALING      
        else if((idx==1) &&( (GET_TV_RESOLUTION()  == HD_720) || (GET_TV_RESOLUTION()  == HD_1080) ) && IS_OSD_SCALE_BUF_OK()) 
        {            
    
            region_width = scale_region_p->osd_w;
            region_height = scale_region_p->osd_h;

	     region_osd_format = region_pointer->osd_format;

            // trick!! for fill up the scaling region when scaling. 
 	     length = (in_dimension->x_length)*(scale_region_p->osd_w)/(region_pointer->osd_w)+1;
	     start_x = (start->x)*(scale_region_p->osd_w)/(region_pointer->osd_w);         
//	     width = (in_dimension->y_length)*(scale_region_p->osd_h)/(region_pointer->osd_h)+1;
//        start_y = (start->y)*(scale_region_p->osd_h)/(region_pointer->osd_h);

         
	     width = (in_dimension->y_length)*(scale_region_p->ratio.y_dividend)/(scale_region_p->ratio.y_divisor)+1;
            start_y = (start->y)*(scale_region_p->ratio.y_dividend)/(scale_region_p->ratio.y_divisor);
// 	     length = (in_dimension->x_length)*(scale_region_p->ratio.x_dividend)/(scale_region_p->ratio.x_divisor)+1;            
//	     start_x = (start->x)*(scale_region_p->ratio.x_dividend)/(scale_region_p->ratio.x_divisor);

	     x_remainder = 0;

	#ifdef DEBUG_OSD_DRAW_RECTANGLE_BASIC
	osd_printf("\nregion[region_index].osd_format=%d\n",region[region_index].osd_format);
	osd_printf("=>start.x: %d\n", start_x);
	osd_printf("=>start.y: %d\n", start_y);
	osd_printf("=>x_length: %d\n", in_dimension->x_length);
	osd_printf("=>y_length: %d\n", in_dimension->y_length);
	osd_printf("=>color: %d\n", color);
	osd_printf("=>region_index: %d\n", region_index);
	osd_printf("=>region_width: %d\n", osd_byte_to_pixel(region_width, region[region_index].osd_format));
       osd_printf("=>region_height: %d\n", region_height);
	delay_1ms(5);
	#endif

	     if (region_pointer->osd_used == 0)
                return -1;

	// if length > region length
	     if ((start_x + length) > osd_byte_to_pixel(region_width, region_osd_format)) {
                length = osd_byte_to_pixel(region_width, region_osd_format) - start_x;
            }
	     if ((width+start_y) > region_height)	// if height > region height
	     {
                width = region_height - start_y;
                #ifdef DEBUG_OSD_DRAW_RECTANGLE                
	         osd_printf("Drawing rectangle failed, -2: height > region height\n");
                osd_printf("Region height: %d\n", region_height);
                osd_printf("Start.y: %d\n", start_y);
	         osd_printf("Rect height: %d\n", width);
                #endif
	     }

	//initialize buffer start
	     T = (t_osdv2_header *)(get_osdbuf_baseptr()+ scale_region_p->osd_header[0]*32);
            B = (t_osdv2_header *)(get_osdbuf_baseptr()+ scale_region_p->osd_header[1]*32);
	     pTopLine = (UINT8 *)(get_osdbuf_baseptr() + (SWAP16(T->link_data) * 32));
	     pBtmLine = (UINT8 *)(get_osdbuf_baseptr() + (SWAP16(B->link_data) * 32));    
         
        }
 #endif       
        else {
            return 0;
        }    

	if (region_osd_format == 0)	// 4 color
	{
		x_remainder = start_x & 0x03;   //x_remainder = start_x % 4;
		x_remainder = ((x_remainder + length) <= 4);

		color = (color & 0x0003);		// take lower 2 bits
		color = (color | (color << 2));	//color = (color | (color << 2));	// build lower 4 bits
		color = (color | (color << 4));	//color = (color | (color << 4));	// build lower 8 bits

		// Build head mask
		{
			const   UINT8   head[4] = {0x00, 0xc0, 0xf0, 0xfc};
			head_background_mask = head[start_x % 4];
		}
		head_color = color & (~head_background_mask);

		#ifdef DEBUG_OSD_DRAW_RECTANGLE
		osd_printf("4 color\n");
		osd_printf("head_background_mask: %04x\n", head_background_mask);
		osd_printf("!head_background_mask: %04x\n", (~head_background_mask));
		osd_printf("head_color: %04x\n", head_color);
		delay_1ms(5);
		#endif

		// Build tail mask
		{
			const   UINT8   tail[4] = {0x00, 0x3f, 0x0f, 0x03};
			tail_background_mask = tail[(start_x + length) % 4];
		}
		tail_color = color & (~tail_background_mask);

		#ifdef DEBUG_OSD_DRAW_RECTANGLE
		osd_printf("4 color\n");
		osd_printf("tail_background_mask: %4x\n", tail_background_mask);
		osd_printf("!tail_background_mask: %4x\n", (~tail_background_mask));
		osd_printf("tail_color: %4x\n", tail_color);
		delay_1ms(5);
		#endif

		region_width_byte = region_width;	// 1 pixel = 1/4 byte

		start_byte = start_x >> 2;
		end_byte = (start_x + length + 3) >> 2;
		region_length_byte = end_byte - start_byte;
	}
	else if (region_osd_format == 1)	// 16 color
	{
		x_remainder = start_x & 0x01;  //x_remainder = start_x % 2;
		x_remainder = ((x_remainder + length) <= 2);

		color = (color & 0x000f);			// take lower 4 bits
		color = (color | (color << 4));	// build lower 8 bits
		
		// Build head mask
        head_background_mask = (start_x %2) ? 0xf0 : 0x00; 

		head_color = color & (~head_background_mask);

		// Build tail mask
		tail_background_mask = ((start_x + length) % 2)? 0x0f : 0x00;

		tail_color = color & (~tail_background_mask);

		region_width_byte = region_width;	// 1 pixel = 0.5 bytes;

		start_byte = start_x >> 1;
		end_byte = (start_x + length + 1) >> 1;
		region_length_byte = end_byte - start_byte;
		
		#ifdef DEBUG_OSD_DRAW_RECTANGLE
		osd_printf("16 color...\n");
		#endif
	}
	else if (region_osd_format == 2)	// 256 color
	{
#ifdef OSD_SUPPORT_256_COLOR
		x_remainder = 0;
		region_width_byte = region_width;	// 1 pixel = 1 byte
		region_length_byte = length;		// 1 pixel = 1 byte
		start_byte = start_x;
		head_background_mask = 0;
		tail_background_mask = 0;
		head_color = color;
		tail_color = color;
#else
		return -3;
#endif	// #ifdef OSD_SUPPORT_256_COLOR
	}
	else if (region_osd_format == 3)	// 2 color
	{
#ifdef OSD_SUPPORT_2_COLOR
		x_remainder = start_x & 0x07;  //x_remainder = start_x % 8;
		x_remainder = ((x_remainder + length) <= 8);

		color = (color & 0x0001);		// take lower 1 bits
		color = (color | (color << 1));	// build lower 2 bits
		color = (color | (color << 2));//color = (color | (color << 2));	// build lower 4 bits
		color = (color | (color << 4));//color = (color | (color << 4));	// build lower 8 bits
		
		// Build head mask
		{
        	const   UINT8   head[8] = {0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe};
			head_background_mask = head[start_x % 8];
        }

		head_color = color & (~head_background_mask);

		// Build tail mask
		{
			const   UINT8   tail[8] = {0x00, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01};
			tail_background_mask = tail[(start_x + length) %8];
		}

		tail_color = color & (~tail_background_mask);

		region_width_byte = region_width;	// 1 pixel = 1/8 bytes

		start_byte = start_x >> 3;
		end_byte = (start_x + length + 7) >> 3;
		region_length_byte = end_byte - start_byte;

		#ifdef DEBUG_OSD_DRAW_RECTANGLE
		osd_printf("length: %d\n", length);
		osd_printf("region_length_byte: %d\n", region_length_byte);
		delay_1ms(5);
		#endif
#else
		return -4;
#endif // #ifdef OSD_SUPPORT_2_COLOR
	}
	// else it's direct color which is 16 bits and does not need mask or shift etc.
	else
	{
		x_remainder = 0;
		region_width_byte = region_width;	// 1 pixel = 2 bytes
		region_length_byte = length << 1;
		start_byte = start_x << 1;
		head_background_mask = 0;
		tail_background_mask = 0;
		head_color = color;
		tail_color = color;
		#ifdef DEBUG_OSD_DRAW_RECTANGLE_DIRECT_COLOR
		osd_printf("color: %04x\n", color);
		delay_1ms(5);
		#endif
	}

	#ifdef DEBUG_OSD_DRAW_RECTANGLE
	osd_printf("start->x: %d\n", start_x);
	osd_printf("start->x in byte: %d\n", osd_pixel_to_byte(start_x, region_osd_format));
	osd_printf("head_color: %04x\n", head_color);
	osd_printf("tail_color: %04x\n", tail_color);
	osd_printf("width_byte: %d\n", region_width_byte);
	osd_printf("region_width: %d\n", region_width);
	osd_printf("region_length_byte: %d\n", region_length_byte);
	delay_1ms(5);
	#endif

	int color1;
	if (x_remainder == 1)
	{
		color1 = head_color = tail_color = head_color & tail_color;
	}

	if (p_scan == 0)
	{
		pTopLine = pTopLine + ((start_y>>1) * region_width_byte) + start_byte;
		pBtmLine = pBtmLine + ((start_y>>1) * region_width_byte) + start_byte;
	}
	else
	{
		pTopLine = pTopLine + (start_y * region_width_byte) + start_byte;
		pBtmLine = pBtmLine + (start_y * region_width_byte) + start_byte;
	}

       UINT32 color32;
       color32 = (UINT32)color;
       color32 = (color32<<24) | (color32<<16) | (color32<<8) | color32;

	for (i=0; i<width; i++)
	{
		// determine top line or bottom line
		if (region_osd_format < 4)		// for 2/4/256 color
		{
			if (p_scan == 0)
				p = ((start_y+i)&1) ? pBtmLine : pTopLine;
			else
				p = pTopLine;
		}
		else									// for direct color
		{
			if (p_scan == 0)
				p16 = ((start_y+i)&1) ? (UINT16*)pBtmLine : (UINT16*)pTopLine;
			else
				p16 = (UINT16*)pTopLine;
		}

		// draw
		if (region_length_byte == 1)		// length is within a byte boundary
		{
			if (region_osd_format < 4)
				p[0] = (color1 | ((p[0]) & head_background_mask) | ((p[0]) & tail_background_mask));			
			else
				p16[0] = SWAP16(color1);
		}
		else								// length is longer than a byte or crosses a byte boundary
		{
						
                    if (region_osd_format < 4){
                        // paint head
                        p[0] = (head_color | ((p[0]) & head_background_mask));

                        // paint middle section
                        if(region_length_byte<(2+3+4)) {
                            for (j=1; j< region_length_byte-1; j=j+1)  // middle section from p array index 1. modify by robert.chang
                                p[j] = color;
                        }    
                        else {
                            // for speeding up osd draw rectangle, we fill data to memory at 
                            // the rate of 4bytes or 1bytes per time. robert.chang,2006-09-11
                            UINT8 *pline_8;
                            UINT32 *pline_32;
                                                        
                            pline_8 = (p+1);
                            pline_32 = (UINT32*)((( (UINT32)pline_8 +3)>>2)<<2);
                            
                            UINT16 align4byte_offset = (UINT16)((UINT32)pline_32-(UINT32)pline_8);
                            UINT16 length_byte   = region_length_byte-2-align4byte_offset;
                            UINT16 length_4byte = length_byte >>2;
                            UINT16 length_1byte = length_byte - (length_4byte<<2);
                            
                            for(j=0; j<align4byte_offset; j++)
                                pline_8[j] = color;
                            
                            for(j=0; j<length_4byte; j++)
                                pline_32[j] = color32;

                            pline_8 = (p+1+align4byte_offset+(length_4byte<<2));
                            for(j=0; j<length_1byte; j++)
                                pline_8[j] = color;
                            
                        }

                        // paint tail
                        p[region_length_byte - 1] = (tail_color | ((p[region_length_byte - 1]) & tail_background_mask));

                    }    
                    else {        // for direct color
                        // paint head
                        p16[0] = SWAP16(color);
                        
                        // paint middle section        
                        for (j=1; j< region_length_byte-1; j=j+1)                         
                            p16[j] = SWAP16(color);
                        
                        // paint tail
                        p16[region_length_byte - 1] = SWAP16(color);
                    }
                     
 		}

		if (p_scan == 0)
		{
			if (i & 1)
				pBtmLine = pBtmLine + region_width_byte;
			else
				pTopLine = pTopLine + region_width_byte;
		}
		else
			pTopLine = pTopLine + region_width_byte;
	}
    }
    
	return 0;
	///osd_enable();
}


//////////////////////////////////////////////////////
// For drawing a rectangle border
//	start:				upper left coordinate				(in pixel)
//	in_dimension:       width and height of border          (in pixel)
//	line_width:			border thickness					(in pixel)
//	color:				color of the rectangle outline
//	region_index:		region index to draw
//#define DEBUG_OSD_DRAW_RECTANGLE_BORDER
void osd_draw_rectangle_border(coordinate *start, dimension *in_dimension,
							UINT16 line_width, UINT16 color, UINT8 region_index)
{
	t_osd_region *region_pointer = &region[region_index];
	UINT16	in_dimension_x_length = in_dimension->x_length;
	UINT16	in_dimension_y_length = in_dimension->y_length;
	coordinate out_start = *start;
	dimension out_dimension;

	if (region_pointer->osd_used == 0)
		return;

	// Draw top line
	out_dimension.x_length = in_dimension_x_length;
	out_dimension.y_length = line_width;

	osd_draw_rectangle(&out_start, &out_dimension, color, region_index);

	// Draw left line
	out_dimension.x_length = line_width;
	out_dimension.y_length = in_dimension_y_length;
	osd_draw_rectangle(&out_start, &out_dimension, color, region_index);

	// Draw bottom line
	coordinate temp = out_start;
	temp.y = temp.y + in_dimension_y_length - line_width;
	out_dimension.x_length = in_dimension_x_length;
	out_dimension.y_length = line_width;

	osd_draw_rectangle(&temp, &out_dimension, color, region_index);

	// Draw right line
	out_start.x = out_start.x + in_dimension_x_length - line_width;
	out_dimension.x_length = line_width;
	out_dimension.y_length = in_dimension_y_length;

	#ifdef DEBUG_OSD_DRAW_RECTANGLE_BORDER
	osd_printf("start->x: %d\n", start->x);
	osd_printf("start->y: %d\n", start->y);
	osd_printf("x_length: %d\n", out_dimension.x_length);
	osd_printf("y_length: %d\n", out_dimension.y_length);
	osd_printf("color: %d\n", color);
	osd_printf("region_index: %d\n\n", region_index);
	delay_1ms(100);
	#endif
	osd_draw_rectangle(&out_start, &out_dimension, color, region_index);
}

//////////////////////////////////////////////////////
// For drawing a region border
//	line_width:			border thickness					(units in pixel)
//	color:				color of the rectangle outline
//	region_index:		region index to draw
void osd_draw_region_border(UINT16 line_width, UINT16 color, UINT8 region_index)
{
	t_osd_region *region_pointer = &region[region_index];
	coordinate start = {0, 0};

	dimension out_dimension;

	if (region_pointer->osd_used == 0)
		return;

	//out_dimension.x_length = osd_byte_to_pixel(region[region_index].osd_visible_w, region[region_index].osd_format);
	out_dimension.x_length = region_pointer->osd_visible_w;
	out_dimension.y_length = region_pointer->osd_h;

	osd_draw_rectangle_border(&start,
							&out_dimension,
							line_width, color, region_index);
}

//////////////////////////////////////////////////////
// For drawing horizontal line
//  start_x:        start x-coordinate of line
//  end_x:          end x-coordinate of line
//  y:              start y-coordinate of line
//  color:          line color
//  width:          line width
//  region_index:   region index to draw
//	Return:         [ 0 = drawing ok]
//      			[-1 = region is deleted, not in the list]
//					[-2 = rectangle length(width) > region length(width)]
//#define DEBUG_OSD_DRAW_HORIZONTAL_LINE
int osd_draw_horizontal_line(UINT16 start_x, UINT16 end_x,
				UINT16 y, UINT16 color, UINT16 width, UINT8 region_index)
{
	t_osd_region *region_pointer = &region[region_index];
	coordinate start = {start_x, y};
	dimension in_dimension = {end_x - start.x, width};

	if (region_pointer->osd_used == 0)
		return -1;

    #ifdef DEBUG_OSD_DRAW_HORIZONTAL_LINE
    	osd_printf("---OSD_DRAW_HORIZONTAL_LINE---\n");
    	osd_printf("Region[%d]: \n",region_index);
    	osd_printf("[x, y] = [%d,%d]\n",start_x, y);
    	osd_printf("[length, width] = [%d,%d]\n",end_x - start.x, width);
    	osd_printf("color = %d \n",color);
    	delay_1ms(500);
    #endif

	return osd_draw_rectangle(&start, &in_dimension, color, region_index);
}

//////////////////////////////////////////////////////
// For drawing vertical line
//  start_x:        start x-coordinate of line
//  start_y:        start y-coordinate of line
//  end_y:          end y-coordinate of line
//  color:          line color
//  width:          line width
//  region_index:   region index to draw
//	Return:         [ 0 = drawing ok]
//      			[-1 = region is deleted, not in the list]
//					[-2 = rectangle length(width) > region length(width)]
//#define DEBUG_OSD_DRAW_VERTICAL_LINE
int osd_draw_vertical_line(UINT16 x, UINT16 start_y,
				UINT16 end_y, UINT16 color, UINT16 width, UINT8 region_index)
{
	t_osd_region *region_pointer = &region[region_index];
	coordinate start = {x, start_y};
	dimension in_dimension = {width, end_y - start.y};

	if (region_pointer->osd_used == 0)
		return -1;

    #ifdef DEBUG_OSD_DRAW_VERTICAL_LINE
    	osd_printf("---OSD_DRAW_VERTICAL_LINE---\n");
    	osd_printf("Region[%d]: \n",region_index);
    	osd_printf("[x, y] = [%d,%d]\n",x, start_y);
    	osd_printf("[width, length] = [%d,%d]\n", width, end_y - start.y);
    	osd_printf("color = %d \n",color);
    	delay_1ms(500);
    #endif

	return osd_draw_rectangle(&start, &in_dimension, color, region_index);
}

//////////////////////////////////////////////////////
// For drawing the border of a rectangular button
//	start:          (x,y) start-coordinate of rectangle 
//	end:            (x,y) end-coordinate of rectangle 
//	bDown:			[0=button not pressed]	[1=button pressed]
//	mask:           upper:1000, bottom:0100, lefe:0010, right:0001
//	region_index:	region index to draw
//#define DEBUG_OSD_DRAW_BUTTON_BORDER
void osd_draw_button_border(coordinate *start, coordinate *end,
						int bDown, unsigned mask, UINT8 region_index)
{
    int i;
    UINT16	start_x = start->x;
    UINT16	start_y = start->y;
    UINT16	end_x = end->x;
    UINT16	end_y = end->y;
    
    t_osd_region *region_pointer = &region[region_index];
    
	#ifdef DEBUG_OSD_DRAW_BUTTON_BORDER
	osd_printf("\n======> Begin: osd_draw_button_outline\n");
	#endif

	unsigned    uBorderC, xBorderC, dBorderC, temp_BorderC;

	if (region_pointer->osd_used == 0)
		return;

	if (bDown) {
		//button is pressed (down)
		uBorderC = C16_BLACK;       // upper border color
		xBorderC = C16_LIGHTGRAY;
		dBorderC = C16_WHITE;       // rear border color
	} else {
		//button is not-pressed (up)
		uBorderC = C16_WHITE;
		xBorderC = C16_LIGHTGRAY;
		dBorderC = C16_BLACK;
	}

	if (mask & (1<<3)) {//osd_draw_horizontal_line
		//draw upper border
		for(i=0;i<4;i++)
		{
		    if(i==1||i==2)
		        temp_BorderC = uBorderC;
		    else
		        temp_BorderC = xBorderC;     

            osd_draw_horizontal_line(start_x+i, end_x-i, start_y+i, temp_BorderC, 1, region_index);		    
		}
		//osd_draw_horizontal_line(start->x+0, end->x-0, start->y+0, xBorderC, 1, region_index);
		//osd_draw_horizontal_line(start->x+1, end->x-1, start->y+1, uBorderC, 1, region_index);
		//osd_draw_horizontal_line(start->x+2, end->x-2, start->y+2, uBorderC, 1, region_index);
		//osd_draw_horizontal_line(start->x+3, end->x-3, start->y+3, xBorderC, 1, region_index);
	}

	if (mask & (1<<2)) {
		//draw bottom border
		for(i=3;i>=0;i--)
		{
		    if(i==2||i==1)
		        temp_BorderC = dBorderC;
		    else
		        temp_BorderC = xBorderC;     

            osd_draw_horizontal_line(start_x+i, end_x-i, end_y-i, temp_BorderC, 1, region_index);		    
		}				
		//osd_draw_horizontal_line(start->x+3, end->x-3, end->y-3, xBorderC, 1, region_index);
		//osd_draw_horizontal_line(start->x+2, end->x-2, end->y-2, dBorderC, 1, region_index);
		//osd_draw_horizontal_line(start->x+1, end->x-1, end->y-1, dBorderC, 1, region_index);
		//osd_draw_horizontal_line(start->x+0, end->x-0, end->y-0, xBorderC, 1, region_index);
	}

	//draw left border
	if (mask & (1<<1)) {
	    
	    for(i=1;i<4;i++)
		{
		    if(i==2||i==1)
		        temp_BorderC = uBorderC;
		    else
		        temp_BorderC = xBorderC;     

            osd_draw_vertical_line(start_x+i, start_y+i, end_y-i, temp_BorderC, 1, region_index);		    
		}
	    
	    
		////osd_draw_vertical_line(start->x+0, start->y+0, end->y-0, xBorderC, 1, region_index);
		//osd_draw_vertical_line(start->x+1, start->y+1, end->y-1, uBorderC, 1, region_index);
		//osd_draw_vertical_line(start->x+2, start->y+2, end->y-2, uBorderC, 1, region_index);
		//osd_draw_vertical_line(start->x+3, start->y+3, end->y-3, xBorderC, 1, region_index);
	}

	//draw right border
	if (mask & (1<<0)) {
	    
	    for(i=1;i<4;i++)
		{
		    if(i==2||i==1)
		        temp_BorderC = dBorderC;
		    else
		        temp_BorderC = xBorderC;     

            osd_draw_vertical_line(end_x-i, start_y+i, end_y-i, temp_BorderC, 1, region_index);		    
		}
	    
		////osd_draw_vertical_line(end->x-0, start->y+0, end->y-0, xBorderC, 1, region_index);
		//osd_draw_vertical_line(end->x-1, start->y+1, end->y-1, dBorderC, 1, region_index);
		//osd_draw_vertical_line(end->x-2, start->y+2, end->y-2, dBorderC, 1, region_index);
		//osd_draw_vertical_line(end->x-3, start->y+3, end->y-3, xBorderC, 1, region_index);
	}
}

//////////////////////////////////////////////////////
// For filling a region with color
//#define DBG_OSD_FILL_REGION
int osd_fill_region(UINT8 region_index, UINT16 color)
{
	t_osd_region *region_pointer = &region[region_index];
	coordinate start = {0, 0};
	dimension in_dimension;

	if (region[region_index].osd_used == 0)
		return -1;

	in_dimension.x_length = region_pointer->osd_visible_w;
	in_dimension.y_length = region_pointer->osd_h;

	#ifdef DBG_OSD_FILL_REGION
	osd_printf("Fill region[%d]:\n", region_index);
	osd_printf("x_length: %d\n", in_dimension.x_length);
	osd_printf("y_length: %d\n", in_dimension.y_length);
	delay_1ms(100);
	#endif

	return osd_draw_rectangle(&start,
							&in_dimension,
							color,
							region_index);
}
#if 0

//////////////////////////////////////////////////////
// For drawing font bitmap
//	pFont:			    the pointer of the font bitmap data
//	start:              (x,y) start-coordinate of rectangle 
//  dimension:          width and height of font
//  palette:            font-color and background-color 
//	region_index:	    the OSD region number
//  only_font_color:    1:only draw font color, 0: draw font color and background color
//  2005/04/12 yltseng
//  2005/12/28 yltseng
void osd_draw_font_bitmap(const UINT8* pFont, coordinate *start, dimension *in_dimension,
					font_palette *palette, int region_index, int only_font_color)
{
	t_osd_region *region_pointer = &region[region_index];
	UINT8 font_color = palette->font_color;
	UINT8 bkg_color = palette->background_color;
    UINT8 temp_color, temp_color_2=0x0,ori_bkg_color=0x0;
#ifdef USE_NEW_SCHINESE_OSD
    UINT8 region_bk_color = 0;
#endif//end=> #ifdef USE_NEW_SCHINESE_OSD

	BYTE	bEscapePixelNum;
	UINT8*	pTopLine, * pBtmLine, * pLine;
	UINT32	iDispLoc, disploc = 0;
	UINT32  coordinate_x, coordinate_y;
	UINT32  pixels_in_first_byte, pixels_in_last_byte, pixels_in_byte, temp_pixels;
    UINT8	head_foreground_mask;

	int		iRegionWidth = region_pointer->osd_w;

	UINT8			osd_format = region_pointer->osd_format;
	unsigned int	font_width,font_height;
	unsigned int	i, j, Bperpixel,pixels_a_byte,shift_num,tempi;


    t_osdv2_header *T, *B;
    
	if (region_pointer->osd_used == 0)
		return;
	
	//printf("<1> [x,y]=[%d,%d] iRegionWidth=%d, region=%d\n",start->x, start->y,iRegionWidth, region_index );	
		
	T = (t_osdv2_header *)(get_osdbuf_baseptr()+ (region_pointer->osd_header[0]<<5));
	B = (t_osdv2_header *)(get_osdbuf_baseptr()+ (region_pointer->osd_header[1]<<5));
	
	pTopLine = (UINT8 *)(get_osdbuf_baseptr() + (SWAP16(T->link_data) <<5));
	pBtmLine = (UINT8 *)(get_osdbuf_baseptr() + (SWAP16(B->link_data) <<5));	
/*
	pTopLine = (BYTE *)(((BYTE *) get_osdbuf_baseptr()) +
		(osd_region_list[region_index].osd_link_data[0]) * 32);
	pBtmLine = (BYTE *)(((BYTE *) get_osdbuf_baseptr()) +
		(osd_region_list[region_index].osd_link_data[1]) * 32);
*/
    coordinate_x = start->x;
    coordinate_y = start->y;
	//coordinate_y = (p_scan) ? coordinate_y : coordinate_y>>1;
	
	//iDispLoc = (coordinate_y ) * iRegionWidth  + coordinate_x;
	//bEscapePixelNum = iDispLoc & 0x01;
	
	//iDispLoc = (((coordinate_y - ((coordinate_y) & 0x01)) * iRegionWidth ) + (coordinate_x))>>1;	//16 color only?

    //printf("<2> [x,y]=[%d,%d] iDispLoc=%d, bEscapePixelNum=%d\n",coordinate_x, coordinate_y, iDispLoc,bEscapePixelNum );
    
    tempi = 0;
    bEscapePixelNum = 0;    

	switch (osd_format)
	{
        case OSD_FORMAT_2COLOR:
		#ifdef OSD_SUPPORT_2_COLOR
            Bperpixel = 3;
            pixels_a_byte = 8;
            shift_num = 1;
            bEscapePixelNum = coordinate_x%8;
            
            // Build head mask
    		{
    			const   UINT8   head[8] = {0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01};
    			head_foreground_mask = head[bEscapePixelNum];
    		}
    		
            break;
		#else
			return;
		#endif // #ifdef OSD_SUPPORT_2_COLOR
         
		case OSD_FORMAT_4COLOR:
			Bperpixel = 2; // 4
			pixels_a_byte = 4;
			shift_num = 2;
			//iDispLoc = (((coordinate_y - ((coordinate_y) & 0x01)) * iRegionWidth ) + (coordinate_x))>>2;
			//iDispLoc = ((coordinate_y>>1) * iRegionWidth ) + (coordinate_x>>2);
			//Calculate the num of escape pixels when start->x isn't 4 multiple
			bEscapePixelNum = coordinate_x%4;			
			
			// Build head mask
    		{
    			const   UINT8   head[4] = {0xff, 0x3f, 0x0f, 0x03};
    			head_foreground_mask = head[bEscapePixelNum];
    		}
			break;
            
		case OSD_FORMAT_256COLOR:
		#ifdef OSD_SUPPORT_256_COLOR
			Bperpixel = 0; // 1
			pixels_a_byte = 1;
			shift_num = 8;
			//iDispLoc = (((coordinate_y - ((coordinate_y) & 0x01)) * iRegionWidth ) + (coordinate_x));
			//iDispLoc = ((coordinate_y>>1) * iRegionWidth ) + (coordinate_x);
			break;
		#else
			return;
		#endif // #ifdef OSD_SUPPORT_256_COLOR
            
		case OSD_FORMAT_16COLOR:
			Bperpixel = 1; // 2
			pixels_a_byte = 2;
			shift_num = 4;
			//iDispLoc = (((coordinate_y - ((coordinate_y) & 0x01)) * iRegionWidth ) + (coordinate_x))>>1;
			//iDispLoc = ((coordinate_y>>1) * iRegionWidth ) + (coordinate_x>>1);
			bEscapePixelNum = coordinate_x & 0x01;
			
			// Build head mask
    		{
    			const   UINT8   head[2] = {0xff, 0x0f};
    			head_foreground_mask = head[bEscapePixelNum];
    		}
			break;
            
		default:    // direct color
		    return;
	}
	
	iDispLoc = (coordinate_y>>1) * iRegionWidth + (coordinate_x>>Bperpixel);
    //printf("<3> (x,y)=(%d,%d),iRegionWidth=%d, iDispLoc=%d\n",coordinate_x, coordinate_y,iRegionWidth,iDispLoc );
	//printf("<3>font_color=%x, bkg_color=%x \n", font_color,bkg_color);

	//font_width = pFont[0];
	//font_height = pFont[1];
	font_width = in_dimension->x_length;
	font_height = in_dimension->y_length;

    //printf("<draw> (x,y)=(%d, %d) (width, height)=(%d, %d)\n", coordinate_x,coordinate_y,font_width,font_height);
	disploc = 0;
	
	pixels_in_byte = 8/shift_num;
	pixels_in_first_byte = pixels_in_byte-bEscapePixelNum;
    pixels_in_last_byte = (font_width-pixels_in_first_byte)%pixels_in_byte;
	
	//if only_font_color is true, we get ori_bkg_color first.
	if(only_font_color)
	{
	    if(coordinate_y&0x01)
		{
			pLine = pBtmLine;
		}
		else
		{
		    pLine = pTopLine;
		}
	    
	    switch (osd_format)
	    {
	        case OSD_FORMAT_2COLOR:
	            ori_bkg_color = pLine[iDispLoc]>>7;
	            break;         
	    
	        case OSD_FORMAT_4COLOR:
	            ori_bkg_color = pLine[iDispLoc]>>6;
	            break;
	        
	        case OSD_FORMAT_16COLOR:
	            ori_bkg_color = pLine[iDispLoc]>>4;
	            break;
	        
	        case OSD_FORMAT_256COLOR:
	            ori_bkg_color = pLine[iDispLoc];
	            break;           
	        
	        default:
	            return;     
	    }
	  
	    bkg_color = ori_bkg_color;
	    if(monflg==2)
	    printf_w("<mh>[%d %d][%d %d %d %d]\n", coordinate_x,coordinate_y, osd_format,ori_bkg_color,bEscapePixelNum,font_width);
	}
			
	for (i = 0; i < font_height; i++)
	{
		if (((i + coordinate_y) & 0x01) && (p_scan ==0))
		{
			pLine = pBtmLine;
			//printf("pBtmLine\n");
		}	
		else
		{
			pLine = pTopLine;
			//printf("pTopLine\n");
		}	

#ifdef USE_NEW_SCHINESE_OSD
        //if (only_font_color == 2), we get region_bk_color first.
        if (only_font_color == 2)
        {
            switch (osd_format)
            {
                case OSD_FORMAT_2COLOR:
                    region_bk_color = pLine[iDispLoc]>>7;
                    break;
                    
                case OSD_FORMAT_4COLOR:
                    region_bk_color = pLine[iDispLoc]>>6;
                    break;
                    
                case OSD_FORMAT_16COLOR:
                    region_bk_color = pLine[iDispLoc]>>4;
                    break;
                    
                case OSD_FORMAT_256COLOR:
                    region_bk_color = pLine[iDispLoc];
                    break;
                    
                default:
                    return;
            }
            bkg_color = region_bk_color;
        }
#endif //end =>  #ifdef USE_NEW_SCHINESE_OSD
		for (j = 0; j < font_width; j++)
		{
			tempi = (j+bEscapePixelNum) >> Bperpixel;
            //printf("<4>j=%d, bEscapePixelNum=%d, Bperpixel=%d, tempi=%d\n",j,bEscapePixelNum,Bperpixel,tempi );
			if (pFont[((j + disploc) >> 3) + 0/*3*/] & (0x80 >> ((j + disploc) & 0x07)))
			{
			    temp_color = font_color;
				//pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] << shift_num) | font_color;
				//printf("<true>iDispLoc=%d, tempi=%d, value=%x \n",iDispLoc,tempi,pLine[iDispLoc + tempi]);
			}	
			else
			{
			    //if only_font_color is true, we don't re-draw bkg_color
			    //temp_color = (only_font_color) ? ori_bkg_color : bkg_color;

#ifdef ADJUST_SPACE_BETWEEN_FONT  //denghg add 2006-1-6 06:11     
			     extern  BYTE LeftNoBGwidth;
			     if((region_index==3)&&(j<LeftNoBGwidth)) //not draw BGfontcolor denghg 2006-1-6 06:11     
			     	temp_color = pLine[iDispLoc + tempi] ;
			     else
			     	temp_color = (only_font_color) ? pLine[iDispLoc + tempi] : bkg_color;
#else//#ifdef ADJUST_SPACE_BETWEEN_FONT  //denghg add 2006-1-6 06:11     

			    if (only_font_color == 2)//Liyl modified 06/01/19
                    temp_color = pLine[iDispLoc + tempi];
                else
                    temp_color = bkg_color;
#endif
			    //pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] << shift_num) | bkg_color;
				//printf("<false>iDispLoc=%d, tempi=%d, value=%x \n",iDispLoc,tempi,pLine[iDispLoc + tempi]);				
			}	
			
			/*
			if((bEscapePixelNum!=0)&&(j==0)) // coordinate_x is odd, so clear and then shift first pixel
			    pLine[iDispLoc + tempi] = ((pLine[iDispLoc + tempi] >> shift_num) << shift_num) | temp_color;			
			else			
			    pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] << shift_num) | temp_color;
			*/
			
			//handling the first byte when bEscapePixelNum!=0;
			if((bEscapePixelNum!=0)&&(j<(pixels_a_byte - bEscapePixelNum)))    
			{
			    temp_color_2 = (temp_color_2<<shift_num)|temp_color;
                
                if(j==(pixels_a_byte - bEscapePixelNum -1))    			    
                {
                    temp_color_2 = temp_color_2 & head_foreground_mask;
//                    pLine[iDispLoc + tempi] = ((pLine[iDispLoc + tempi]>>(pixels_a_byte - bEscapePixelNum))<<(pixels_a_byte - bEscapePixelNum))| temp_color_2;   
                      pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] & (~head_foreground_mask)) | temp_color_2;   // intra-byte status, reserve original color and add new color(temp_color_2),robert.chang.  

                }    
			}    
			else
			{			
			    pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] << shift_num) | temp_color;
			}    
			
		}
		
		//Note: Following program can handle odd font_width of font
		//correct these pixels in last byte for displaying normally
		
		if(pixels_in_last_byte!=0)
		{
		    pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] << (8-pixels_in_last_byte*shift_num));		    
		    
		    //bkg-color pixels in last byte should be set bkg-color not 0
		    temp_pixels = pixels_in_byte-pixels_in_last_byte;
		    while(temp_pixels!=0)
		    {
		        pLine[iDispLoc + tempi]|= bkg_color << shift_num*(temp_pixels-1);
		        temp_pixels--;
		    }
		}
		
		disploc += font_width ;
		if (((i + coordinate_y) & 0x01)||(p_scan ==1))
			iDispLoc += iRegionWidth;
	}
}

//////////////////////////////////////////////////////
// For combining foreground and background colors in a byte
//	color_mode:		            color format of the region
//	current_bitmap_byte:		bitmap byte
//	current_background_byte:	background byte
//	Return:         [combined byte]
//      			[-1 = don't support this color format]
//					[-2 = 256 color not supported]
//					[-3 = 2 color not supported]
UINT8 osd_combine_fore_back_grounds(UINT8 color_mode, UINT8 current_bitmap_byte, UINT8 current_background_byte)
{
	UINT8 i = 0;
	UINT8 pixel_mask = 0;   //pixel_mask is used to find where are background color
	UINT8 final_mask = 0;   //final_mask is used to determine where are background color
	UINT8 shift_num = 0;    //depend on color_mode
	switch (color_mode)
	{
		case OSD_FORMAT_4COLOR:
			shift_num = 2;
			pixel_mask = 0x03;
			break;
		case OSD_FORMAT_16COLOR:
			shift_num = 4;
			pixel_mask = 0x0f;
			break;
		case OSD_FORMAT_256COLOR:
		#ifdef OSD_SUPPORT_256_COLOR
			shift_num = 8;
			pixel_mask = 0xff;
			break;
		#else
			return -2;
		#endif // #ifdef OSD_SUPPORT_256_COLOR
		case OSD_FORMAT_2COLOR:
		#ifdef OSD_SUPPORT_2_COLOR
			shift_num = 1;
			pixel_mask = 0x01;
			break;
		#else
			return -3;
		#endif // #ifdef OSD_SUPPORT_2_COLOR	
		default:
			return -1;
	}
	for (i=0; i < 8/shift_num; i++)
	{
		if ((current_bitmap_byte & pixel_mask) == 0)
			final_mask = final_mask | pixel_mask;
		pixel_mask = pixel_mask << shift_num;
	}
	return (current_bitmap_byte & (~final_mask)) | (current_background_byte & final_mask);
}

//////////////////////////////////////////////////////
// For drawing BMP on osd region r with given colors
// This function can support 2, 4, 16 and 256 color bmps
//	start:		upper left coordinate				(units in pixel)
//	bmp:		The bmp image data
//	region_index:	region index to draw
//	Return:         [ 0 = drawing ok]
//      			[-1 = region is deleted, not in the list]
//					[-2 = don't support this format]
//					[-3 = 256 color not supported]
//					[-4 = 2 color not supported]
//#define DBG_OSD_DRAW_BMP
int osd_draw_bmp(coordinate *start, const BYTE* bmp,  BYTE region_index)
{
	t_osd_region *region_pointer = &region[region_index];
	UINT16	region_width = region_pointer->osd_w;
	UINT16	bmp_x_length = bmp[0];
	UINT16	bmp_y_length = bmp[1];

	UINT16	start_x = start->x;
	UINT16	start_y = start->y;

	UINT8	*p;

	UINT16	i = 0;
	UINT16	j = 0;

	UINT8	*pTopLine;
	UINT8	*pBtmLine;

	UINT16	region_width_byte;
	UINT16	region_length_byte;
	UINT16	start_byte;
	UINT16	end_byte;

	UINT8	head_background_mask;
	UINT8	tail_background_mask;
	UINT8	current_bitmap_byte;

	UINT8	head_right_shift;
	UINT8	tail_left_shift;

	UINT8	head_left_shift;

	UINT8	x_remainder = 0;
	UINT16	bmp_index = 2;
	
	t_osdv2_header *T, *B;    

	if (region_pointer->osd_used == 0)
		return -1;

    #ifdef DBG_OSD_DRAW_BMP
    osd_printf("-------------------------\n");
	osd_printf("start.x: %d\n", start_x);
	osd_printf("bmp_x_length: %d\n", bmp_x_length);
	osd_printf("region width: %d\n", osd_byte_to_pixel(region_width,region_pointer->osd_format));
	osd_printf("start.y: %d\n", start_y);
	osd_printf("bmp_y_length: %d\n", bmp_y_length);
	osd_printf("region height: %d\n", region_pointer->osd_h);
    #endif

	//initialize buffer start
	
	T = (t_osdv2_header *)(get_osdbuf_baseptr()+ region_pointer->osd_header[0]*32);
	B = (t_osdv2_header *)(get_osdbuf_baseptr()+ region_pointer->osd_header[1]*32);
	
	pTopLine = (UINT8 *)(get_osdbuf_baseptr() + (SWAP16(T->link_data) * 32));
	pBtmLine = (UINT8 *)(get_osdbuf_baseptr() + (SWAP16(B->link_data) * 32));
	
	//pTopLine = (UINT8*)(get_osdbuf_baseptr() + (osd_region_list[region_index].osd_link_data[0] * 32));
	//pBtmLine = (UINT8*)(get_osdbuf_baseptr() + (osd_region_list[region_index].osd_link_data[1] * 32));

	if (region_pointer->osd_format == 0)	// 4 color
	{
		x_remainder = start_x % 4;
		x_remainder = ((x_remainder + bmp_x_length) < 4);

		// Build head mask
		switch (start_x % 4)
		{
			case 1:	head_background_mask	= 0xc0;
					head_right_shift		= 2;	break;
			case 2:	head_background_mask	= 0xf0;
					head_right_shift		= 4;	break;
			case 3:	head_background_mask	= 0xfc;
					head_right_shift		= 6;	break;
			default:
				head_background_mask = 0x00;
				head_right_shift = 0;
		}

		// Build tail mask
		switch ((start_x + bmp_x_length) % 4)
		{
			case 1:	tail_background_mask	= 0x3f;
					tail_left_shift			= 6;	break;
			case 2:	tail_background_mask	= 0x0f;
					tail_left_shift			= 4;	break;
			case 3:	tail_background_mask	= 0x03;
					tail_left_shift			= 2;	break;
			default:
				tail_background_mask = 0x00;
				tail_left_shift = 0;
		}

		region_width_byte = region_width;	// 1 pixel = 1/4 byte

		start_byte = start_x / 4;
		end_byte = (start_x + bmp_x_length - 1) / 4;
		region_length_byte = end_byte - start_byte + 1;
	}
	else if (region_pointer->osd_format == 1)	// 16 color
	{
		x_remainder = start_x % 2;
		x_remainder = ((x_remainder + bmp_x_length) < 2);

		// Build head mask
		switch (start_x % 2)
		{
			case 1:	head_background_mask	= 0xf0;
					head_right_shift		= 4;	break;
			default:
				head_background_mask = 0x00;
				head_right_shift = 0;
		}

		// Build tail mask
		switch ((start_x + bmp_x_length) % 2)
		{
			case 1:	tail_background_mask	= 0x0f;
					tail_left_shift			= 4;	break;
			default:
				tail_background_mask = 0x00;
				tail_left_shift = 0;
		}

		region_width_byte = region_width;	// 1 pixel = 0.5 bytes;

		start_byte = start_x / 2;
		end_byte = (start_x + bmp_x_length - 1) / 2;
		region_length_byte = end_byte - start_byte + 1;
	}
	else if (region_pointer->osd_format == 2)	// 256 color
	{
#ifdef OSD_SUPPORT_256_COLOR
		x_remainder = 0;
		region_width_byte = region_width;	// 1 pixel = 1 byte
		region_length_byte = bmp_x_length;	// 1 pixel = 1 byte
		start_byte = start_x;
		head_background_mask = 0;
		tail_background_mask = 0;
		head_right_shift = 0;
		tail_left_shift = 0;
#else
		return -3;
#endif // #ifdef OSD_SUPPORT_256_COLOR
	}
	else if (region_pointer->osd_format == 3)	// 2 color
	{
#ifdef OSD_SUPPORT_2_COLOR
		x_remainder = start_x % 8;
		x_remainder = ((x_remainder + bmp_x_length) < 8);

		// Build head mask
		switch (start_x % 8)
		{
			case 1:	head_background_mask	= 0x80;
					head_right_shift		= 1;	break;
			case 2:	head_background_mask	= 0xc0;
					head_right_shift		= 2;	break;
			case 3:	head_background_mask	= 0xe0;
					head_right_shift		= 3;	break;
			case 4:	head_background_mask	= 0xf0;
					head_right_shift		= 4;	break;
			case 5:	head_background_mask	= 0xf8;
					head_right_shift		= 5;	break;
			case 6:	head_background_mask	= 0xfc;
					head_right_shift		= 6;	break;
			case 7:	head_background_mask	= 0xfe;
					head_right_shift		= 7;	break;
			default:
				head_background_mask = 0x00;
				head_right_shift = 0;
		}

		// Build tail mask
		switch ((start_x + bmp_x_length) % 8)
		{
			case 1:	tail_background_mask	= 0x7f;
					tail_left_shift			= 7;	break;
			case 2: tail_background_mask 	= 0x3f;
					tail_left_shift			= 6;	break;
			case 3: tail_background_mask 	= 0x1f;
					tail_left_shift			= 5;	break;
			case 4: tail_background_mask 	= 0x0f;
					tail_left_shift			= 4;	break;
			case 5: tail_background_mask 	= 0x07;
					tail_left_shift			= 3;	break;
			case 6: tail_background_mask 	= 0x03;
					tail_left_shift			= 2;	break;
			case 7: tail_background_mask 	= 0x01;
					tail_left_shift			= 1;	break;
			default:
				tail_background_mask = 0x00;
				tail_left_shift = 0;
		}

		region_width_byte = region_width;	// 1 pixel = 1/8 bytes

		start_byte = start_x / 8;
		end_byte = (start_x + bmp_x_length + 7) / 8;
		region_length_byte = end_byte - start_byte;
#else
		return -4;
#endif // #ifdef OSD_SUPPORT_2_COLOR
	}
	// else it's direct color which is not supported (yet?) here
	else
	{
		return -2;
	}

    #ifdef DBG_OSD_DRAW_BMP
    osd_printf("head_background_mask: %x\n", head_background_mask);
    osd_printf("head_right_shift: %d\n", head_right_shift);
    osd_printf("tail_background_mask: %x\n", tail_background_mask);
    osd_printf("tail_left_shift: %d\n", tail_left_shift);
    osd_printf("start_byte: %d\n", start_byte);
    osd_printf("end_byte: %d\n", end_byte);
    osd_printf("region_length_byte: %d\n", region_length_byte);
    #endif

	head_left_shift = 8 - head_right_shift;

	if (p_scan == 0)
	{
		pTopLine = pTopLine + (start_y/2 * region_width_byte) + start_byte;
		pBtmLine = pBtmLine + (start_y/2 * region_width_byte) + start_byte;
	}
	else
	{
		pTopLine = pTopLine + (start_y * region_width_byte) + start_byte;
		pBtmLine = pBtmLine + (start_y * region_width_byte) + start_byte;
	}

	for (i=0; i<bmp_y_length; i++)
	{
	       if (p_scan == 0)
	       {
		    p = (i&1) ? pBtmLine : pTopLine;
		}
		else
		{
		    p = pTopLine;    
		}    

		for (j=0; j< region_length_byte; j=j+1)
		{
			if (j == 0)	// First byte -> Combine part of 1st byte with background
			{
				current_bitmap_byte = bmp[bmp_index] >> head_right_shift;				    
				
				//if start_x is odd number, this byte(bmp[2]) will be used in next time(when j==1)     
				//therefore bmp_index is subtracted 1 first
/*marked by tw Robert.chang 20060515
				if( (start_x%2!=0) || (region_pointer->osd_format == 0) )//libing modify it 2006/4/20.
				 //Note:bmp[2] should also be re-draw next time when color format is 4color.
*/

				if(start_x%2!=0)    
				    bmp_index -=1;
				    
				#ifdef DBG_OSD_DRAW_BMP
			    printf("<1>p[0]=%x\n",p[0]);
			    printf("<1>current_bitmap_byte=%x\n",current_bitmap_byte);
				#endif    
			}
			else if (j == (region_length_byte - 1)) // Last byte -> Combine last bmp byte with the background
			{
				current_bitmap_byte = bmp[bmp_index] << tail_left_shift;
				
				#ifdef DBG_OSD_DRAW_BMP
				printf("<last>current_bitmap_byte=%x\n",current_bitmap_byte);
				printf("---------------------------------\n");
				#endif
			}
			else		// Middle bytes -> Combine parts of 2 consecutive bytes
			{
				current_bitmap_byte = (bmp[bmp_index] << head_left_shift)
										| (bmp[bmp_index + 1] >> head_right_shift);
			}
			//p[j] byte is background color
			p[j] =  osd_combine_fore_back_grounds(region_pointer->osd_format,
														current_bitmap_byte,
														p[j]);

			bmp_index = bmp_index + 1;	// Increment bmp pointer
		}
		if (p_scan == 0)
		{
			if (i & 1)
				pBtmLine = pBtmLine + region_width_byte;
			else
				pTopLine = pTopLine + region_width_byte;
		}
		else
			pTopLine = pTopLine + region_width_byte;
	}
	return 0;  
}

#endif

 
void osd_draw_font_bitmap(const UINT8* pFont, coordinate *start, dimension *in_dimension,
					font_palette *palette, int region_index, int only_font_color)
{

    DrawAttribute draw_bmp_attribute;
    draw_bmp_attribute.start.x = start->x;
    draw_bmp_attribute.start.y = start->y;
    draw_bmp_attribute.bmp_dimension.x_length = in_dimension->x_length;
    draw_bmp_attribute.bmp_dimension.y_length = in_dimension->y_length;
    draw_bmp_attribute.bmp_offset.draw_start.x = 0;
    draw_bmp_attribute.bmp_offset.draw_start.y = 0;    
    draw_bmp_attribute.bmp_offset.draw_dimension.x_length = in_dimension->x_length;
    draw_bmp_attribute.bmp_offset.draw_dimension.y_length = in_dimension->y_length;
    draw_bmp_attribute.p_bmp = pFont;
    UINT16 color_palette[]={palette->background_color, palette->font_color};
    draw_bmp_attribute.p_palette = color_palette;
    draw_bmp_attribute.region_index = region_index;
    draw_bmp_attribute.draw_type.bits_a_pixel = 1;
    draw_bmp_attribute.draw_type.is_reference_palette = 1;
    draw_bmp_attribute.draw_type.only_fore_color = only_font_color;

    osd_draw_data(&draw_bmp_attribute);
}

int osd_draw_bmp(coordinate *start, const BYTE* bmp,  BYTE region_index)
{
    DrawAttribute draw_bmp_attribute;
    draw_bmp_attribute.start.x = start->x;
    draw_bmp_attribute.start.y = start->y;
    draw_bmp_attribute.bmp_dimension.x_length = bmp[0];
    draw_bmp_attribute.bmp_dimension.y_length = bmp[1];
    draw_bmp_attribute.bmp_offset.draw_start.x = 0;
    draw_bmp_attribute.bmp_offset.draw_start.y = 0;    
    draw_bmp_attribute.bmp_offset.draw_dimension.x_length = bmp[0];
    draw_bmp_attribute.bmp_offset.draw_dimension.y_length = bmp[1];
    draw_bmp_attribute.p_bmp = bmp+2;
    draw_bmp_attribute.p_palette = NULL;
    draw_bmp_attribute.region_index = region_index;
    t_osd_region *region_pointer = &region[region_index];
    switch(region_pointer->osd_format)
    {
        case OSD_FORMAT_2COLOR:
            draw_bmp_attribute.draw_type.bits_a_pixel = 1;
            break;
        case OSD_FORMAT_4COLOR:
            draw_bmp_attribute.draw_type.bits_a_pixel = 2;
            break;
        case OSD_FORMAT_16COLOR:    
            draw_bmp_attribute.draw_type.bits_a_pixel = 4;
            break;
    }
    draw_bmp_attribute.draw_type.is_reference_palette = 0;
    draw_bmp_attribute.draw_type.only_fore_color = 1;

    osd_draw_data(&draw_bmp_attribute);


    return 0;
}

void osd_draw_bitmap(UINT8 region_index, coordinate *start, const UINT8* pbmp, dimension *bmp_dimension, 
                      UINT8 pixel_size, UINT8 only_fore_color, font_palette *palette)
{
    UINT16  color_palette[4];
    DrawAttribute draw_bmp_attribute;
    draw_bmp_attribute.region_index = region_index;    
    draw_bmp_attribute.start.x = start->x;
    draw_bmp_attribute.start.y = start->y;
    draw_bmp_attribute.p_bmp = pbmp;    
    draw_bmp_attribute.bmp_dimension.x_length = bmp_dimension->x_length;
    draw_bmp_attribute.bmp_dimension.y_length = bmp_dimension->y_length;
    draw_bmp_attribute.bmp_offset.draw_start.x = 0;
    draw_bmp_attribute.bmp_offset.draw_start.y = 0;    
    draw_bmp_attribute.bmp_offset.draw_dimension.x_length = bmp_dimension->x_length;
    draw_bmp_attribute.bmp_offset.draw_dimension.y_length = bmp_dimension->y_length;
    if(palette == NULL) {
        draw_bmp_attribute.p_palette = NULL;    
        draw_bmp_attribute.draw_type.is_reference_palette = 0;            
    }    
    else {
        
        #ifndef DVDRELEASE
        if((pixel_size>2) || (pixel_size<=0) ) { // this function don't support over 2 bits-to-1 pixel bmp draw with palette
            osd_printf("Error, pixel size of bmp with reference palette over 2 bits or negative\n");
            return ;
        }    
        #endif 

        
        if(pixel_size == 1) {
            color_palette[0] = palette->background_color; 
            color_palette[1] = palette->font_color;
            color_palette[2] = 0;
            color_palette[3] = 0;
        }        
        else  {
            color_palette[0] = palette->background_color; 
            color_palette[1] = palette->outline1_color; 
            color_palette[2] = palette->outline2_color; 
            color_palette[3] = palette->font_color;
        }
        draw_bmp_attribute.p_palette = color_palette;        
        draw_bmp_attribute.draw_type.is_reference_palette = 1;
    }        
    draw_bmp_attribute.draw_type.bits_a_pixel = pixel_size;
    draw_bmp_attribute.draw_type.only_fore_color = only_fore_color;

    osd_draw_data(&draw_bmp_attribute); 

}
    

/*
  * Function: osd_draw_bitmap()   
  * Purposes: integrate osd_draw_font_bitmap() and osd_draw_bmp() to osd_draw_bitmap()                
  * Description: 
  *                 1. draw bitmap to region buffer.
  *                 2. bitmap format support  1, 2, 4, 8 bits for a pixel, but not odd bits
  *                 3. region support 2, 4, 16, 256, and true color, but osd_init_regions() 
  *                     and osd_create_region1 must support the format.
  * Arguments: data struct DrawAttribute include all attributes about draw bitmap to region buffer
  * Return: 1  :success
  *		  -1 :fail
  * Create: robert.chang, 2006/04/20 
  * Modify: 
  */
int osd_draw_data(DrawAttribute *_draw_attribute)
{
//printf_w(__FUNCTION__ "in\n"); 
    t_osd_region *region_pointer =&region[_draw_attribute->region_index];
    t_osdv2_header *ptop_region, *pbtm_region;
    UINT8 *ptop_line, *pbtm_line, *pline;
    UINT8 osd_format, is_ref_palette, only_fore_color, is_true_color=0;    
    const UINT16 *p_palette;
    UINT16 pixel_color = 0, regn_ori_color = 0, color_index, i, j;
 
    //bmp attribute
    UINT8 bmp_shift_uint, bmp_shift_uint_power, bmp_pix2byte_shift, bmp_pix_inbyte, bmp_mask;
    const UINT8 *pbmp;
    UINT16 bmp_width, bmp_height, draw_width, draw_height;  // pixel unit
    UINT32 bmp_loc;                                                              // pixel uint
    
    // region attribute
    UINT8 regn_shift_uint_power, regn_pix2byte_shift, regn_pix_inbyte, regn_pix_offset, regn_mask;
    UINT16 start_x, start_y;                         // pixel uint
    UINT16 region_width;                             // byte uint     
    UINT32 regn_loc, regn_row_offset;     // byte uint

#ifndef DVDRELEASE
    if(region_pointer->osd_used == FALSE)
    {
        osd_printf("Region %d not used, Error\n", _draw_attribute->region_index);
        return -1;
    } 
#endif
//printf_w(__FUNCTION__ " ENTER NEW OSD\n");
    osd_format  = region_pointer->osd_format;
    region_width = region_pointer->osd_w;

    ptop_region= (t_osdv2_header *)(get_osdbuf_baseptr()+ ((region_pointer->osd_header[0])<<5));
    pbtm_region = (t_osdv2_header *)(get_osdbuf_baseptr()+ ((region_pointer->osd_header[1])<<5));	
	
    ptop_line = (UINT8 *)(get_osdbuf_baseptr() + (SWAP16(ptop_region->link_data)<<5));
    pbtm_line = (UINT8 *)(get_osdbuf_baseptr() + (SWAP16(pbtm_region->link_data)<<5));

    start_x = _draw_attribute->start.x;
    start_y = _draw_attribute->start.y;

    bmp_width = _draw_attribute->bmp_dimension.x_length;
    bmp_height = _draw_attribute->bmp_dimension.y_length;

    draw_width = _draw_attribute->bmp_offset.draw_dimension.x_length;
    draw_height = _draw_attribute->bmp_offset.draw_dimension.y_length;

    is_ref_palette = _draw_attribute->draw_type.is_reference_palette;
    only_fore_color = _draw_attribute->draw_type.only_fore_color;
    pbmp = _draw_attribute->p_bmp;
    p_palette = _draw_attribute->p_palette;
#ifndef DVDRELEASE
/*
    printf_w("\n%x\n %x\n %x\n %x\n %x\n %x\n %x\n %x\n %x\n %x\n %x\n %x\n %x\n %x\n", 
    _draw_attribute->start.x, _draw_attribute->start.y, 
    _draw_attribute->bmp_dimension.x_length, _draw_attribute->bmp_dimension.y_length, 
    _draw_attribute->bmp_offset.draw_dimension.x_length, _draw_attribute->bmp_offset.draw_dimension.y_length, 
    _draw_attribute->bmp_offset.draw_start.x, _draw_attribute->bmp_offset.draw_start.y, 
    _draw_attribute->p_bmp, _draw_attribute->p_palette, 
    _draw_attribute->region_index, 
    _draw_attribute->draw_type.bits_a_pixel, _draw_attribute->draw_type.is_reference_palette, 
    _draw_attribute->draw_type.only_fore_color    
    );
    if(_draw_attribute->draw_type.is_reference_palette) {
        int i;
        printf_w("color: ");
        for(i=0; i<(0x01<<(_draw_attribute->draw_type.bits_a_pixel));  i++)
            printf_w("%x  ", *(p_palette+i));
        printf_w("\n");

    }    
*/
#endif

    // set relational attributes about putting pixel color to region buffer
    switch(osd_format)
    {
                case OSD_FORMAT_2COLOR:
                    regn_pix2byte_shift = 3;
                    regn_pix_inbyte = 8;
                    regn_shift_uint_power = 0;
                    regn_pix_offset = start_x%8;            
                    regn_mask = 0x80;    		        
            		break;

                case OSD_FORMAT_4COLOR:
                    regn_pix2byte_shift = 2; // 4
                    regn_pix_inbyte = 4;
                    regn_shift_uint_power = 1;
                    regn_pix_offset = start_x%4;						
                    regn_mask = 0xC0;             
			break;

                case OSD_FORMAT_16COLOR:
                    regn_pix2byte_shift = 1; // 2
                    regn_pix_inbyte = 2;
                    regn_shift_uint_power = 2;
                    regn_pix_offset = start_x & 0x01;			
                    regn_mask = 0xf0;             
                    break;

			
                case OSD_FORMAT_256COLOR:
                    regn_pix2byte_shift = 0; // 1
                    regn_pix_inbyte = 1;
                    regn_shift_uint_power = 3;
                    regn_pix_offset = 0;
                    regn_mask = 0xff;
			break;
            			
                default:    // direct color
                    is_true_color = TRUE;
                    is_ref_palette = FALSE;
                    only_fore_color = FALSE;
                    regn_pix2byte_shift = 0; // 1
                    regn_pix_inbyte = 0;
                    regn_shift_uint_power = 0;
                    regn_pix_offset = 0;
                    regn_mask = 0;
                    
                    break;    
    }
 
    // set relational attributes about getting pixel color from bmp buffer
    bmp_shift_uint = _draw_attribute->draw_type.bits_a_pixel;
    switch(bmp_shift_uint)
    {
        case 1:
            bmp_pix2byte_shift = 3;  
            bmp_pix_inbyte = 8;
            bmp_mask =  0x80;
            bmp_shift_uint_power = 0;
            break;
        case 2:
            bmp_pix2byte_shift = 2;
            bmp_pix_inbyte = 4;
            bmp_mask = 0xC0;
            bmp_shift_uint_power = 1;
            break;
        case 4:
            bmp_pix2byte_shift = 1;
            bmp_pix_inbyte = 2;
            bmp_mask = 0xF0;
            bmp_shift_uint_power = 2; 
            break;
        case 8:
            bmp_pix2byte_shift = 0;
            bmp_pix_inbyte = 1;
            bmp_mask = 0xFF;
            bmp_shift_uint_power =3;
            break;
        default:
            is_true_color = TRUE;
            is_ref_palette = FALSE;
            only_fore_color = FALSE;
            bmp_pix2byte_shift = 0;
            bmp_pix_inbyte = 0;
            bmp_mask = 0;
            bmp_shift_uint_power = 0; 

            break;
    }        

#ifdef OSD_DBG
    if(regn_pix_inbyte > bmp_pix_inbyte) { // bit/perpixel of region must larger than or equal to  bit/perpixel of bmp
        osd_printf("Error, bmp color num is more than region color num\n");// So regn_pix_inbyte <= bmp_pix_inbyte.
        return -1;                                
    }
    if(is_true_color) {
        if( (bmp_shift_uint!=16) || (osd_format<OSD_FORMAT_DIRECT16_1) ) {
            osd_printf("Error, BMP or Region is not True Color\n");
            return -1;
        }
    }    
#endif

    UINT8 bmp_max_pix_index = bmp_pix_inbyte - 1;
    UINT8 regn_max_pix_index = regn_pix_inbyte - 1; 
    UINT32 loc_tmp= (p_scan == 1) ? (start_y * region_width) : ((start_y>>1) * region_width);
    
    regn_loc = (is_true_color) ? ( loc_tmp+(start_x << 1) ) : ( loc_tmp+(start_x>>regn_pix2byte_shift) );
    
    bmp_loc = _draw_attribute->bmp_offset.draw_start.y * bmp_width + _draw_attribute->bmp_offset.draw_start.x;
	
    for (i = 0; i < draw_height; i++)
    {
        if (((i + start_y) & 0x01) && (p_scan ==0))
        {
            pline = pbtm_line;
			//printf("pBtmLine\n");
        }	
        else
        {
            pline = ptop_line;
			//printf("pTopLine\n");
        }	

        if(only_fore_color == 2) {
            BYTE region_byte_mask = regn_mask >> (regn_pix_offset <<regn_shift_uint_power) ;
            regn_ori_color = (pline[regn_loc] & region_byte_mask) >> (((~regn_pix_offset) & (regn_max_pix_index)) << regn_shift_uint_power);
#ifndef DVDRELEASE            
//        printf_w(__FUNCTION__ "  region_byte_mask:%x  shift:%x\n", region_byte_mask, (regn_pix_offset <<regn_shift_uint_power));
#endif
        }

        for (j = 0; j < draw_width; j++)
        {
            if(is_true_color == TRUE) {
                UINT8 high_pixel = pbmp[j+bmp_loc];
                UINT8 low_pixel = pbmp[j+bmp_loc+1];
                pline[j+regn_loc] = low_pixel;
                pline[j+regn_loc+1] = high_pixel;
                j++;
            }
            else {
                    // get pixel color from bmp buffer
                UINT8 shift_offset = (j + bmp_loc) & (bmp_max_pix_index); 
                BYTE bmp_byte_mask = bmp_mask >> (shift_offset << bmp_shift_uint_power); 
                    
                color_index = pbmp[(j+bmp_loc)>>bmp_pix2byte_shift]  & bmp_byte_mask;                        // if color_index = 00110000
                color_index = color_index >> (((~shift_offset)&(bmp_max_pix_index))  << bmp_shift_uint_power);//-> color_index = 00000011
                if(is_ref_palette) {
                    pixel_color = *(p_palette+color_index);
                }    
                else{
                    pixel_color = color_index;
                }     

                if((only_fore_color==2) && (color_index == 0)) {
                    pixel_color = regn_ori_color;
                }
                    // put pixel color to region memory
                if((only_fore_color != 1) || (color_index != 0)) {
                    regn_row_offset = (j+regn_pix_offset) >> regn_pix2byte_shift;
                    UINT32 loc = regn_loc + regn_row_offset;         
                        
                    shift_offset = (j+regn_pix_offset) & (regn_max_pix_index);
                    BYTE region_byte_mask = regn_mask >> (shift_offset << regn_shift_uint_power);
                    pixel_color = pixel_color<<(((~shift_offset) & (regn_max_pix_index)) << regn_shift_uint_power);
                    pline[loc] = (pline[loc] & (~region_byte_mask)) | pixel_color;

#ifndef DVDRELEASE
//printf_w(__FUNCTION__  " j:%x, start_x:%x, regn_pix_offset:%x, regn_row_offset:%x, loc:%x ", j, start_x, regn_pix_offset, regn_row_offset, loc);
#endif                    
                }
            }
        }


        bmp_loc += bmp_width ;
        if (((i + start_y) & 0x01)||(p_scan ==1))
            regn_loc += region_width;

    }

#ifdef SUPPORT_SW_OSD_SCALING

    if( ((GET_TV_RESOLUTION()  == HD_720) || (GET_TV_RESOLUTION()  == HD_1080)) && IS_OSD_SCALE_BUF_OK() ) {
        DrawDimension scale_section;
        scale_section.draw_start.x = start_x;
        scale_section.draw_start.y = start_y;        
        scale_section.draw_dimension.x_length = draw_width;
        scale_section.draw_dimension.y_length = draw_height;  
        
        osd_region_scaling(_draw_attribute->region_index, &scale_section);
    }
 
#endif

    return 1;

}



#endif //#if SUPPORT_OSD
#endif // #ifdef NEW_OSD_DRIVER

