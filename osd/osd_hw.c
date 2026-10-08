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
|  1.1  05/18/2005	    WSLEE 			        Modified osd_init_regions
|  1.2  08/29/2005      yltseng                 Fix a bug in osd_init_regions, add get region size & position functions,
|                                               init two more variables in t_osd_region structure.
|  1.3  09/06/2005      yltseng                 Fix show mp4 string bug when switching to progressive scan
|  1.4  10/28/2005      yltseng                 Add a function to set original region position
|--------------------------------------------------------------------------------*/ 

//Note: Each new function should be externed by osd_api.h (update osd_hw.c and osd_api.h)

/************************************************************************************
OSD Hardware-related API
************************************************************************************/
#include "config.h"
#include "regmap.h"
#include "global.h"
#include "osd.h"
#include "osdhw.h"
#include "osd_palette.h"
#include "osd_api.h"
#ifdef SUPPORT_SW_OSD_SCALING
#include "kernel.h"
#endif

#if defined(PMP_UI)||defined(EASTECH_STD_SETUP_MENU)//jwk modify for 8202D setup switch abnormal
#include "kernel.h"
#endif

#if defined(SUPPORT_SMI_MultiColor)//2005-8-16 20:38 zhoulin 
UINT32 palette_16color_MP4_SUB[16];
extern int IS_EXT_SUP_ACTIVATED();
extern UINT8  SmiSupType;
#endif

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

#if 0//def TTX_MULTI_BG //tcf added 2006-4-18 11:05上午
extern UINT8 ttx_bg_format;//Jack marked and use one lonely key
#endif

#ifdef NEW_OSD_DRIVER
#if SUPPORT_OSD
/***********************************************************************************/
//New functions are as follows:


//////////////////////////////////////////////////////
// For calculating the size required for each color region
//	md_value:	        format of this OSD region
//  width_in_byte:      the osd_w of region[i]
//  height_in_pixel:    the osd_h of region[i]
//	Return:	            [region size (in 32-bytes)]
#ifdef OSD_DBG
//#define DEBUG_OSD_CALC_MODE_SIZE
UINT16 osd_calc_region_size(UINT8 md_value, UINT16 width_in_pixel, UINT16 height_in_pixel)
{
	UINT16 size = 0;
    //UINT8 md_value, *T;
    UINT16 width_in_byte;
        
        width_in_byte = osd_pixel_to_byte(width_in_pixel, md_value);

        if(width_in_byte%4!=0)        
            width_in_byte = width_in_byte + (4-(width_in_byte%4));
        
        //T = (UINT8 *)(get_osdbuf_baseptr()+(region[region_index].osd_header[0])*32);
        //md_value = *(T)&0x07;
            
		switch(md_value)
		{
			case 0:	size = ((HEADER_SIZE + PALETTE_4_SIZE + 31)>>5); break;		// 4 color
			case 1:	size = ((HEADER_SIZE + PALETTE_16_SIZE + 31)>>5); break;	// 16 color
#ifdef OSD_SUPPORT_256_COLOR
			case 2:	size = ((HEADER_SIZE + PALETTE_256_SIZE + 31)>>5); break;	// 256 color
#endif // #ifdef OSD_SUPPORT_256_COLOR
#ifdef OSD_SUPPORT_2_COLOR
			case 3:	size = ((HEADER_SIZE + PALETTE_2_SIZE + 31)>>5); break;		// 2 color
#endif // #ifdef OSD_SUPPORT_2_COLOR
			default:
				size = (HEADER_SIZE + 31)>>5; break;							// direct color
		}

	#ifdef DEBUG_OSD_CALC_MODE_SIZE
	osd_printf("osd_calc_region_size(%d, %d, %d)\n", md_value,width_in_byte,height_in_pixel);
	osd_printf("Header + Palette: %0d\n", size);
	delay_1ms(10);
	#endif

	if (p_scan)
		size = size + ((width_in_byte * height_in_pixel + 31)>>5);
	else
	{
		size = size + (((width_in_byte * height_in_pixel >>1) + 31)>>5);
	    size = size << 1;
	}

	#ifdef DEBUG_OSD_CALC_MODE_SIZE
	osd_printf("pscan: %0d\n", p_scan);
	osd_printf("Data blk: %04x\n", (width_in_byte * height_in_pixel + 31)>>5);
	osd_printf("Final Size: %04x\n", size);
	osd_printf("--------------\n");
	delay_1ms(10);
	#endif

	return size;
}
#endif

//////////////////////////////////////////////////////
// For deleting a region from the region list
//	region_index:	the region of the list to delete
//	Return:			[1 = OK]
//                  [-1 = region is deleted, not in the list]
//					[-2 = region index > total region]
//					[-3 = total region <= 0]
//#define DEBUG_OSD_DELETE_MODE
/*
int osd_delete_region(UINT8 region_index)
{    
    UINT16 *T, *B;
    UINT8 first_region, previous_region;
    int i;
        
    first_region = osd_display_list[0];
	//UINT8 region_index = osd_mode_list[mode_index].region_index;

	if (region[region_index].osd_used == 0)
		return -1;
	else if (region_index >= osd_active_regions)
		return -2;

    T = (UINT16 *)(get_osdbuf_baseptr()+ region[region_index].osd_header[0]*32);
    B = (UINT16 *)(get_osdbuf_baseptr()+ region[region_index].osd_header[1]*32);

	if (osd_active_regions == 1)
	{		
		osd_disable();
		osd_display_list[0]= 0xff;
	}
	else if (osd_active_regions > 1)
	{
		// update link address of region_index - 1
		if(regs0->osd_tlink_addr==region[region_index].osd_header[0])
		{
			#ifdef DEBUG_OSD_DELETE_MODE
			osd_printf("osd_delete_region: region_index = 0\n");
			#endif						
			
			regs0->osd_tlink_addr  = SWAP16(*(T+7));
	    	regs0->osd_blink_addr  = SWAP16(*(B+7));
	    	first_region = osd_display_list[1];
		}
		else
		{
			#ifdef DEBUG_OSD_DELETE_MODE
			osd_printf("osd_delete_mode: region_index = %d\n", region_index);
			#endif
			
			previous_region = osd_find_previous_region(region_index);
			
			osd_set_region_link_next_addr(previous_region,
										SWAP16(*(T+7)),
										SWAP16(*(B+7)));																				
		}
	}
	else
		return -3;

    osd_active_regions -=1;

    //set LINK_NULL to deleted header
    region[region_index].osd_header[0] = LINK_NULL;
    region[region_index].osd_header[1] = LINK_NULL;
    
    region[region_index].osd_used = 0;
    
    //update osd_display_list[];    
    osd_display_list[0]=first_region;
    for(i=1;i<osd_active_regions;i++)
    {
        osd_display_list[i]=osd_find_next_region(osd_display_list[i-1]);
    }

	return 1;
}
*/


//////////////////////////////////////////////////////
//  Find a previous region according links between regions
//	region_index:	the current region 
//	Return:			[-2 = current region is deleted]
//                  [-1 = current region is the first region]
//					[ i = previous region index ]
/*
int osd_find_previous_region(UINT8 region_index)
{
    int i;
    UINT16 *T;
 
    if(region[region_index].osd_used==0||region[region_index].osd_header[0]==LINK_NULL)
        return -2;
 
    if(regs0->osd_tlink_addr==region[region_index].osd_header[0])
        return -1;
        
    for(i=0;i<MAX_REGION;i++)
    {
        if(region[i].osd_used==1)
        {
            T = (UINT16 *)(get_osdbuf_baseptr()+ region[i].osd_header[0]*32);
            
            if(SWAP16(*(T+7))==region[region_index].osd_header[0])
                break;        
        }    
    }          
      
    return i;
}
*/

//////////////////////////////////////////////////////
//  Find a next region according links between regions
//	region_index:	the current region 
//	Return:			[-2 = current region is deleted]
//                  [-1 = current region is the last region]
//					[ i = next region index ]
/*
int osd_find_next_region(UINT8 region_index)
{
    int i;
    UINT16 *T, next_address;
    
    if(region[region_index].osd_used==0||region[region_index].osd_header[0]==LINK_NULL)
        return -2;        
    
    T = (UINT16 *)(get_osdbuf_baseptr()+ region[region_index].osd_header[0]*32);
 
    next_address = SWAP16(*(T+7));
    
    if(next_address==LINK_NULL)
        return -1;
        
    for(i=0;i<MAX_REGION;i++)
    {                
        if(region[i].osd_used==1)
        {
            if(next_address==region[i].osd_header[0])
                break;        
        }        
    }          
      
    return i;
}
*/

//////////////////////////////////////////////////////
// For setting a region's link_next header field
//	region_index:	index of the region's link_next header field to set
//	top_link_data:	the top_link_next address
//	btm_link_data:	the btm_link_next address
//#define DEBUG_OSD_SET_REGION_LINK_NEXT_ADDR
void osd_set_region_link_next_addr(UINT8 region_index, UINT16 top_link_next, UINT16 btm_link_next)
{
	t_osd_region *region_pointer = &region[region_index];
	UINT16	*top_pointer, *btm_pointer;

	top_pointer = get_osdbuf_baseptr()
					+ (region_pointer->osd_header[0] << 5);
	btm_pointer = get_osdbuf_baseptr()
					+ (region_pointer->osd_header[1] << 5);

	#ifdef DEBUG_OSD_SET_REGION_LINK_NEXT_ADDR
	mon_printf("Top: %08x\n", top_pointer);
	mon_printf("Btm: %08x\n", btm_pointer);
	mon_printf("Write Top: %08x\n", top_link_next);
	mon_printf("Write Btm: %08x\n", btm_link_next);
	mon_printf("Written Top: %08x\n", *(top_pointer+7));
	mon_printf("Written Btm: %08x\n", *(btm_pointer+7));
	#endif

	wbe16(top_pointer+7, top_link_next);
	wbe16(btm_pointer+7, btm_link_next);
}
/*
//////////////////////////////////////////////////////
// For sorting display order
//#define DEBUG_OSD_UPDATE_DISPLAY_LIST
void osd_update_display_list(void)
{
    UINT8   first_region=0;
    int i;
    
    for(i=0;i<MAX_REGION;i++)
    {        
        if(regs0->osd_tlink_addr==region[i].osd_header[0])
        {
            first_region = i;            
            break;
        }
    }    
    
    osd_display_list[0]=first_region;
    
    for(i=1;i<osd_active_regions;i++)
    {
        osd_display_list[i]=osd_find_next_region(osd_display_list[i-1]);
    }
    
    #ifdef  DEBUG_OSD_UPDATE_DISPLAY_LIST
    
    for(i=0;i<osd_active_regions;i++)
    {
        osd_printf("osd_display_list[%d]=%d\n",i,osd_display_list[i]);
    }    
    
    #endif
    
}
*/
//////////////////////////////////////////////////////
// Checking region overlapping for debugging(Debug function)
//	y_temp  :	    y coordinate of region
//  height_temp:    height of region
//  skipped_region: don't check overlap with skipped_region
//	Return:	    	[0 = No overlap]
//			    	[1 = Overlap]
#ifdef OSD_DBG
//#define DEBUG_OSD_CHECK_OVERLAP
UINT8 osd_check_overlap(UINT16 y_temp, UINT16 height_temp, UINT8 skipped_region)
{    
    // y1 and y2 of new region, y_1 and y_2 of existing region
    UINT16  y1, y2, y_1, y_2;
    UINT16  *p;
    t_osdv2_header  *hdr;
    int i;
    
    //y_temp = hdr_pointer->y;
    //height_temp = hdr_pointer->height;
    
    if(p_scan)
    {
        y_temp<<=1;
    }
    else
    {
        //if(bScanMode==OSD_INTERLACED)
        height_temp>>=1;
    }
        
    y1 = y_temp;
    y2 = y1 + height_temp;

    for(i=0;i<osd_active_regions;i++)
    {
        //don't check overlap with skipped_region
        if(osd_display_list[i]==skipped_region)
            continue;
        
        p = (UINT16 *)(get_osdbuf_baseptr()+ region[osd_display_list[i]].osd_header[0]*32);        
        hdr = (t_osdv2_header *)p;
        
        y_1 = SWAP16(hdr->y);  
        y_2 = y_1 + SWAP16(hdr->v_size);
        
        #ifdef DEBUG_OSD_CHECK_OVERLAP
            osd_printf("checking region:[%d,%d], other region:[%d,%d]\n",y1,y2,y_1,y_2);            
        #endif
        
        // check that y1=y_1 or y2=y_2
        if((y1==y_1)||(y2==y_2))
        {
            #ifdef DEBUG_OSD_CHECK_OVERLAP
            osd_printf("<case 1>new position is overlapped\n");
            #endif
            return 1;        
        }    
        // check that y1 or y2 is in region[osd_display_list[i]]
        if(((y_1 < y1)&&(y1 < y_2))||((y_1 < y2)&&(y2 < y_2)))    
        {
            #ifdef DEBUG_OSD_CHECK_OVERLAP
            osd_printf("<case 2>new position is overlapped\n");
            #endif
            return 1;
        }    
        // check that y_1 or y_2 of existing region is in new region    
        if(((y1 < y_1)&&(y_1 < y2))||((y1 < y_2)&&(y_2 < y2)))
        {
            #ifdef DEBUG_OSD_CHECK_OVERLAP
            osd_printf("<case 3>new position is overlapped\n");
            #endif
            return 1;                   
        }    
    }    
    
    return 0;
}
#endif

//////////////////////////////////////////////////////
// For calculating [x,y] in pixel unit 

/*
//UINT32 osd_calc_address_to_pixel(UINT32 addr, UINT32 region_index, UINT32 field)
coordinate *osd_calc_address_to_pixel(UINT32 addr, UINT32 region_index, UINT32 field)
{
    UINT32  region_addr,link_data_addr, temp_addr;
    //UINT32  value;
    UINT16  width, height;
    BYTE    color_format;
    coordinate  start,*p;
    
    width  = region[region_index].osd_w; //in byte
    height = region[region_index].osd_h;
    region_addr = OBV_BASE + region[region_index].osd_header[field];
    color_format = region[region_index].osd_format;
    
    link_data_addr =  region_addr + OSD_DATA_OFFSET(color_format)*32;
    
    printf("<1>region(%d)=[%x, %x]\n",region_index,region_addr,region_addr+width*height);
    
    
    if((addr>=link_data_addr)&&(addr<=(region_addr+width*height)))                        
    {
        temp_addr = addr - link_data_addr;
        printf("<2>addr=%x, link_data_addr=%x, temp_addr=%x\n", addr,link_data_addr,temp_addr);
        start.y = temp_addr / width;
        start.x = (temp_addr % width)*2;                             
    
        if(field==1)                            
            start.y += 1;    
    }
    else
    {
        start.y = 0xffff;
        start.x = 0xffff;
    }
    
    p = &start;
    //value = (start.x<<16)|start.y;
    return  p;
    //return  value;
}
*/

//////////////////////////////////////////////////////
// For inserting a region 
//	region_index:	the index of region[MAX_REGION]
//	Return:	    	[ 1 = insert ok]
//                  [-1 = is overlapped]
//			    	[-2 = region is already created]
//				    [-3 = not enough free memory]
//#define DEBUG_OSD_INSERT_REGIONS
// maybe creat another osd_insert_multi_regions(int n, _t_osd_hdr *hdrp);
/*
int osd_insert_regions(_t_osd_hdr *hdrp, UINT8 region_index)
{    
     
    UINT16 osd_visible_w_byte;
    //t_osdv2_header *p;  
    void *rgnp;  
    //int i, previous_region, next_region;;
    
    #ifdef DEBUG_OSD_INSERT_REGIONS
        osd_printf("======DEBUG_OSD_INSERT_REGIONS======\n");
    
        for(i=0;i<osd_active_regions;i++)
            osd_printf("Before inserting, osd_display_list[%d]=%d\n",i,osd_display_list[i]);
            
        osd_printf("Before inserting, osd_free=%d\n", osd_free);
    #endif
    
    //we assume that this insert-region will be the lastest region
    rgnp = (void *)NULL;
    //previous_region = osd_display_list[osd_active_regions-1];
    //next_region = -1;

#ifdef OSD_DBG      //for debugging
    UINT8 is_overlapped;
    UINT16 need_size;

    is_overlapped = osd_check_overlap(hdrp->y, hdrp->height, 10);
    
    if(is_overlapped)
        return -1;
    
    if(region[region_index].osd_header[0] != LINK_NULL)    
        return -2;
    
    need_size = osd_calc_region_size(hdrp->format,hdrp->width, hdrp->height);
    
    //maybe perform compact memory
    if(MAX_MEMORY-osd_free < need_size)
        return -3;
#endif        
   
    //delay_1ms(20);
    header_id       = hdrp->header_type;
    region[region_index].osd_visible_w  = hdrp->width;  //in pixel
    region[region_index].osd_h          = hdrp->height;
    region[region_index].osd_used       = 1;
    osd_visible_w_byte = osd_pixel_to_byte(hdrp->width, hdrp->format);
    
    if (osd_visible_w_byte % 4 == 0)
    {
        region[region_index].osd_w = osd_visible_w_byte;
    }
    else
    {
        // 2 color, 4 color, or direct color will be returned
        if (!((hdrp->format==OSD_FORMAT_16COLOR) || (hdrp->format==OSD_FORMAT_16COLOR)))	
			return -1;
        region[region_index].osd_w = osd_visible_w_byte + (4 - (osd_visible_w_byte % 4));
    }
        
    osd_create_region1(region_index,
                hdrp->x,  hdrp->y,
                rgnp,
                hdrp->format,
                hdrp->type 
        );        
    
    osd_active_regions +=1;
    region[region_index].osd_used = 1;
    
    osd_display_list[osd_active_regions-1] = region_index;
    //osd_update_display_list();
    osd_update_region_links();
    
    
    #ifdef DEBUG_OSD_INSERT_REGIONS
    
    UINT16 *T, *B;    
    
    osd_printf("need_size=%d, osd_free=%d\n",need_size,osd_free);
    
    osd_printf("<0>the previous region index =%d \n",previous_region);            
    osd_printf("<1>the next region index =%d \n",next_region);
    
    for(i=0;i<MAX_REGION;i++)
    {                
        osd_printf("<region[%d].osd_used=%d)> \n", i,region[i].osd_used);
    }
    
    for(i=0;i<MAX_REGION;i++)
    {                
        osd_printf("<region[%d]: pre(%d) next(%d)> \n", i,osd_find_previous_region(i),osd_find_next_region(i));
    }
    
    for(i=0;i<MAX_REGION;i++)
    {                                                       
        osd_printf("region[%d].osd_header[0]=%x\n", i, region[i].osd_header[0]);
        osd_printf("region[%d].osd_header[1]=%x\n", i, region[i].osd_header[1]);

        T = (UINT16 *)(get_osdbuf_baseptr()+ (region[i].osd_header[0]<< 5));
        B = (UINT16 *)(get_osdbuf_baseptr()+ (region[i].osd_header[1]<< 5));
        
        osd_printf("<T>region[%d].link_next=%x [%x]\n",i, *(T+7),SWAP16(*(T+7)));
        osd_printf("<B>region[%d].link_next=%x [%x]\n",i, *(B+7),SWAP16(*(B+7)));        
    }
    osd_printf("======DEBUG_OSD_INSERT_REGIONS======\n");
    #endif
    return 1;
}
*/

//////////////////////////////////////////////////////
// For setting a new position of a region 
//	region_index:	the index of region[MAX_REGION]
//  x, y:           new region position
//	Return:	    	[ 1 = insert ok]
//                  [-1 = region isn't existing]
//			    	[-2 = is overlapped]
//#define DEBUG_OSD_SET_REGION_POSITION
int osd_set_region_position(UINT8 region_index, UINT16 x, UINT16 y)
{
    if(region_index > (osd_active_regions-1))
        return -1;
        
	t_osd_region *region_pointer = &region[region_index];
    UINT16 nCol, nRow;
    
    if(p_scan)    
        y<<=1;
        
    if(region_pointer->osd_header[0] == LINK_NULL)
    {
        #ifdef DEBUG_OSD_SET_REGION_POSITION
            osd_printf("region isn't existing\n");
        #endif    
        return -1;
    }

    t_osdv2_header *pOSDHeader1 = (t_osdv2_header *)(get_osdbuf_baseptr()
    						+ (region_pointer->osd_header[0] << 5));
    t_osdv2_header *pOSDHeader2 = (t_osdv2_header *)(get_osdbuf_baseptr()
    						+ (region_pointer->osd_header[1] << 5));    

    nRow = y & 0x3ff;
    nCol = x & 0x3ff;

#ifdef OSD_DBG    
    if(osd_check_overlap(nRow,2*SWAP16(pOSDHeader1->v_size),region_index))
    {
        #ifdef DEBUG_OSD_SET_REGION_POSITION
        osd_printf("Overlapping.....\n");
        osd_printf("Region[%d] new position: (%d, %d), height=%d\n",
                    region_index,nCol,nRow, SWAP16(pOSDHeader1->v_size));        
        #endif
        return -2;
    }    
#endif
    pOSDHeader1->x = SWAP16(nCol);
    pOSDHeader2->x = SWAP16(nCol);
    pOSDHeader1->y = SWAP16(nRow);
    pOSDHeader2->y = SWAP16(nRow);

    #ifdef DEBUG_OSD_SET_REGION_POSITION
    osd_printf("Region[%d] new position [%d, %d, %d, %d]\n",region_index,SWAP16(pOSDHeader1->x)
            ,SWAP16(pOSDHeader2->x),SWAP16(pOSDHeader1->y),SWAP16(pOSDHeader2->y));    
    #endif            
            
    osd_update_region_links();               

#ifdef SUPPORT_SW_OSD_SCALING
    if( ((GET_TV_RESOLUTION()  == HD_720) || (GET_TV_RESOLUTION()  == HD_1080)) && IS_OSD_SCALE_BUF_OK() ) {
        scaling_t_osd_region* scaling_region_p = &scaling_region[region_index]; 
        t_osdv2_header *pScalOSDHd1 = (t_osdv2_header *)(get_osdbuf_baseptr()
    	    					+ (scaling_region_p->osd_header[0] << 5));
        t_osdv2_header *pScalOSDHd2 = (t_osdv2_header *)(get_osdbuf_baseptr()
    		    				+ (scaling_region_p->osd_header[1] << 5)); 
        UINT16 nScaleCol = x*(scaling_region_p->ratio.x_dividend)/(scaling_region_p->ratio.x_divisor);
        pScalOSDHd1->x = SWAP16(nScaleCol);
        pScalOSDHd2->x = SWAP16(nScaleCol);
        UINT16 nScaleRow;
        // Trick!! Under HD, we switch NTSC to PAL then the subtitle is too low.So we set the osd position.by robert.chang, 2006-09-20
        if((region_index == 3) && (tv_format == MODE_PAL) && (GET_TV_RESOLUTION()  == HD_720))
            nScaleRow = (y-96)*(scaling_region_p->ratio.y_dividend)/(scaling_region_p->ratio.y_divisor);
        else if((region_index == 3) && (tv_format == MODE_PAL) && (GET_TV_RESOLUTION()  == HD_1080))
            nScaleRow = (y-48)*(scaling_region_p->ratio.y_dividend)/(scaling_region_p->ratio.y_divisor);
        else
            nScaleRow = y*(scaling_region_p->ratio.y_dividend)/(scaling_region_p->ratio.y_divisor);
        pScalOSDHd1->y = SWAP16(nScaleRow);
        pScalOSDHd2->y = SWAP16(nScaleRow);
    #ifdef DEBUG_OSD_SET_REGION_POSITION
    osd_printf("scale_Region[%d] new position [%d, %d, %d, %d]\n",region_index,SWAP16(pScalOSDHd1->x)
            ,SWAP16(pScalOSDHd2->x),SWAP16(pScalOSDHd1->y),SWAP16(pScalOSDHd2->y));    
    #endif            
        
    } 
#endif

    return 1;
}

//////////////////////////////////////////////////////
// For updating osd_display_list[] and links of each region
//#define DEBUG_OSD_UPDATE_REGION_LINKS
void osd_update_region_links(void)
{
    t_osdv2_header *p, *q;
    int i, j, temp;
    
    for(i=0;i<osd_active_regions-1;i++)
    {               
        for(j=i+1;j<osd_active_regions;j++) 
        {   
            p = (t_osdv2_header *)(get_osdbuf_baseptr()+ (region[osd_display_list[i]].osd_header[0]<< 5));                 
            q = (t_osdv2_header *)(get_osdbuf_baseptr()+ (region[osd_display_list[j]].osd_header[0]<< 5));        

            if(SWAP16(q->y) < SWAP16(p->y))
            {
                temp = osd_display_list[i];
                osd_display_list[i] = osd_display_list[j];
                osd_display_list[j] = temp;                                                
            }    
        }    
    }    
    
    #ifdef DEBUG_OSD_UPDATE_REGION_LINKS
    for(i=0;i<osd_active_regions;i++)
        osd_printf("osd_display_list[%d]=%d\n",i,osd_display_list[i]);            
    #endif    
#ifdef SUPPORT_SW_OSD_SCALING  // jiangxl for id3 region in HD
if(Is_MP3_STATE()&&( (GET_TV_RESOLUTION() == HD_720) || (GET_TV_RESOLUTION() == HD_1080) ))
{//libing 2006-9-1 add.
    regs0->osd_tlink_addr  = scaling_region[osd_display_list[0]].osd_header[0];
    regs0->osd_blink_addr  = scaling_region[osd_display_list[0]].osd_header[1];  
}else
#endif
{
    regs0->osd_tlink_addr  = region[osd_display_list[0]].osd_header[0];
    regs0->osd_blink_addr  = region[osd_display_list[0]].osd_header[1];    
}   
 
    for(i=0;i<osd_active_regions-1;i++)
    {
        osd_set_region_link_next_addr(osd_display_list[i],
								    region[osd_display_list[i+1]].osd_header[0],
								    region[osd_display_list[i+1]].osd_header[1]);
        
    }
    
    //set LINK_NULL to link_next of the lastest region 
    osd_set_region_link_next_addr(osd_display_list[osd_active_regions-1],
								    LINK_NULL,LINK_NULL);
        
}

//////////////////////////////////////////////////////
// For setting a palette color of a region 
//	region_index:	the index of region[MAX_REGION]
//  palette_index:  the index of color
//  color:          new palette color
// change color palette
void osd_set_palette_color(UINT8 region_index, UINT8 palette_index, UINT32 color)
{
	t_osd_region *region_pointer = &region[region_index];	
	UINT8	*top_pointer, *btm_pointer;
	top_pointer = get_osdbuf_baseptr()
					+ (region_pointer->osd_header[0] << 5)
					+ HEADER_SIZE
					+ palette_index*OSD_CLUT_SIZE;
	btm_pointer = get_osdbuf_baseptr()
					+ (region_pointer->osd_header[1] << 5)
					+ HEADER_SIZE
					+ palette_index*OSD_CLUT_SIZE;

#ifdef OSD_PAL_16b
		wbe16(top_pointer, color);
		wbe16(btm_pointer, color);
#else
		wbe32(top_pointer, color);
		wbe32(btm_pointer, color);
#endif

#ifdef SUPPORT_SW_OSD_SCALING
    if( ((GET_TV_RESOLUTION()  == HD_720) || (GET_TV_RESOLUTION()  == HD_1080)) && IS_OSD_SCALE_BUF_OK() ) {

	scaling_t_osd_region *scal_region_p = &scaling_region[region_index];	
	UINT8	*scal_top_p, *scal_btm_p;
	scal_top_p = get_osdbuf_baseptr()
					+ (scal_region_p->osd_header[0] << 5)
					+ HEADER_SIZE
					+ palette_index*OSD_CLUT_SIZE;
	scal_btm_p = get_osdbuf_baseptr()
					+ (scal_region_p->osd_header[1] << 5)
					+ HEADER_SIZE
					+ palette_index*OSD_CLUT_SIZE;

        
#ifdef OSD_PAL_16b
	wbe16(scal_top_p, color);
	wbe16(scal_btm_p, color);
#else
	wbe32(scal_top_p, color);
	wbe32(scal_btm_p, color);
#endif

    }
 
#endif


}


//////////////////////////////////////////////////////
// For setting a palette color of multi-regions
//	region_start:	the start index of region[MAX_REGION]
//	region_end:	    the end index of region[MAX_REGION]
//  palette_index:  the index of color
//  color:          new palette color
void osd_set_palette_color_of_multi_regions(UINT8 region_start, UINT8 region_end,
								UINT8 palette_index, UINT32 color)
{
	UINT8	region_index;

	for (region_index = region_start; region_index <= region_end; region_index++)
	{
	    if(region[region_index].osd_used==1)
	    {
            osd_set_palette_color(region_index, palette_index, color);
            
            //osd_printf("Set region[%d] palette success...\n",region_index);
        }    
        //else
            //osd_printf("Set region[%d] palette failed...\n",region_index);    
	}
}

//////////////////////////////////////////////////////
// For converting from pixel unit to byte unit
//	pixel_width:	pixel unit of the mode width
//	format:			color format of the mode
//	Return:			region width in bytes
UINT16 osd_pixel_to_byte(UINT16 pixel_width, UINT8 format)
{
	switch (format)
	{
		case 0:	return ((pixel_width+3) >>2);	// 1 byte has 4 pixels		4 color
		case 1:	return ((pixel_width+1) >>1);	// 1 byte has 2 pixels		16 color
#ifdef OSD_SUPPORT_256_COLOR
		case 2:	return (pixel_width);		// 1 byte has 1 pixel		256 color
#endif	// #ifdef OSD_SUPPORT_256_COLOR
#ifdef OSD_SUPPORT_2_COLOR
		case 3:	return ((pixel_width+7) >>3);	// 1 byte has 8 pixels		2 color
#endif	// #ifdef OSD_SUPPORT_2_COLOR
		default:
				return (pixel_width << 1);	// 1 byte has 0.5 pixels	direct color
	}
}

//////////////////////////////////////////////////////
// For converting a region's length in byte-unit to pixel-unit
//	byte_width:	length of region in bytes
//	format:		color format of the region
//	Return:		length in pixels
UINT16 osd_byte_to_pixel(UINT16 byte_width, UINT8 format)
{
	switch (format)
	{
		case 0:	return (byte_width <<2);	// 1 byte has 4 pixels		4 color
		case 1:	return (byte_width <<1);	// 1 byte has 2 pixels		16 color
#ifdef OSD_SUPPORT_256_COLOR
		case 2:	return byte_width;			// 1 byte has 1 pixel		256 color
#endif	// #ifdef OSD_SUPPORT_256_COLOR
#ifdef OSD_SUPPORT_2_COLOR
		case 3:	return (byte_width <<3);	// 1 byte has 8 pixels		2 color
#endif	// #ifdef OSD_SUPPORT_2_COLOR
		default:
				return (byte_width >> 1);	// 1 byte has 0.5 pixels	direct color
	}
}

extern UINT32  osd_get_original_region_size( UINT32 uiRegion, dimension* pSize )
{
    if( uiRegion > osd_active_regions )
        return FALSE;
    
    pSize->x_length = region[ uiRegion ].osd_visible_w;
    pSize->y_length = region[ uiRegion ].osd_h;
    
    return TRUE;
}

extern UINT32  osd_get_original_region_position( UINT32 uiRegion, coordinate* pPos )
{
    if( uiRegion > osd_active_regions )
        return FALSE;
    
    pPos->x = region[ uiRegion ].osd_x;
    pPos->y = region[ uiRegion ].osd_y;
    
    return TRUE;
}

extern UINT32  osd_set_original_region_position( UINT32 uiRegion, coordinate* pPos )
{
    if( uiRegion > osd_active_regions )
        return FALSE;
    
    region[ uiRegion ].osd_x = pPos->x;
    region[ uiRegion ].osd_y = pPos->y;

    return TRUE;
}

extern UINT32  osd_get_current_region_size( UINT32 uiRegion, dimension* pSize )
{
    if( uiRegion > osd_active_regions )
        return FALSE;
    
    t_osdv2_header* pRegionHeader = (t_osdv2_header *)( get_osdbuf_baseptr()+ region[ uiRegion ].osd_header[0]*32 );
    pSize->x_length = SWAP16(pRegionHeader->h_size);
    pSize->y_length = SWAP16(pRegionHeader->v_size);
    
    UINT8 uiColorMode = pRegionHeader->config0 & ( 0x07 << BIT_MD );
    pSize->x_length = osd_byte_to_pixel( ( pSize->x_length << 2 ), uiColorMode );

    if( !p_scan )
        pSize->y_length <<= 1;

    return TRUE;
}

extern UINT32  osd_get_current_region_position( UINT32 uiRegion, coordinate* pPos )
{
    if( uiRegion > osd_active_regions )
        return FALSE;
    
    t_osdv2_header* pRegionHeader = (t_osdv2_header *)( get_osdbuf_baseptr()+ region[ uiRegion ].osd_header[0]*32 );    
    pPos->x = SWAP16(pRegionHeader->x);
    pPos->y = SWAP16(pRegionHeader->y);
    
    return TRUE;
}
            
/***********************************************************************************/
//Old functions are as follows:

//////////////////////////////////////////////////////
inline void osd_disable(void)
{
    regs0->osd_en    = 0;
}

inline void osd_enable(void)
{    
#if(!defined(DVB_SETUP)||defined(SUPPORT_DVD_OSD))

	#ifdef HW_SUPPORT_OSD_DEFLICKER //2006-04-12, mimitsai add for IC_8202xx relative
    if(p_scan)
        regs0->osd_deflicker_control = 0;
    else
        regs0->osd_deflicker_control = 0x8001;
    #endif
    
    regs0->osd_en    = 1;
#endif
}

void reset_osd()
{
    osd_disable();
    regs0->osd_tlink_addr = LINK_NULL;
    regs0->osd_blink_addr = LINK_NULL;
}


void ENABLE_OSD(void)
{
#if(!defined(DVB_SETUP)||defined(SUPPORT_DVD_OSD))

    #ifdef SUPPORT_SW_OSD_SCALING
        if( (GET_TV_RESOLUTION()  == HD_720) || (GET_TV_RESOLUTION()  == HD_1080) ) {
            regs0->osd_tlink_addr  = scaling_region[0].osd_header[0];
            regs0->osd_blink_addr  = scaling_region[0].osd_header[1];
        }else 
    #endif
    {
        regs0->osd_tlink_addr  = region[0].osd_header[0];
        regs0->osd_blink_addr  = region[0].osd_header[1];
    }    
    osd_enable();
    
#endif
}


void DISABLE_OSD(void)
{
    extern void wait_v_blank(void);
    osd_disable(); 
    wait_v_blank();    //20020613 to avoid  noise when 3D_MENU  toggle .
}


void __osd_init(void)
{
    int i;
    osd_free = addr_vxvy(0,0);
    header_id = NORMAL_HEADER;
    DISABLE_OSD();

    // reset OSD regions information
    for (i=0;i<MAX_REGION;i++) timeout_osd[i] = 0;
    osd_active_regions = 0;
}


void osd_init__(void)
{
    ClearOsdMsg(0);
    ENABLE_OSD();        
}

void InitSW_region(void)
{
    int i,j;
    
    //clear old message
    for(i=0;i<MAX_REGION;i++)
        for(j=0;j<MAX_SW_REGION;j++)  
            RegionStr[i][j][0]=0;
}

//////////////////////////////////////////////////////
//update color index
void SetOsdCol(UINT8 rb, UINT8 re, UINT8 id, UINT32 color)
{
    osd_set_palette_color_of_multi_regions(rb, re, id, color);
    
/*    
    int r;
    for(r=rb;r<=re;r++)
    {
        UINT8 *p, *q, *t;
        t = get_osdbuf_baseptr()+HEADER_SIZE+id*OSD_CLUT_SIZE;    
        p = t + (region[r].osd_header[0] << 5);
        q = t + (region[r].osd_header[1] << 5);
#ifdef OSD_PAL_16b    
        wbe16(p, color);      
        wbe16(q, color);      
#else
        // 2004/10/16 yltseng
        wbe32( p, osd_rescale_color(color) );      
        wbe32( q, osd_rescale_color(color) );      
#endif
    }
*/    
}


UINT32 GetOsdCol(UINT8 r, UINT8 id)
{
    UINT8 *p;
    p=get_osdbuf_baseptr()+region[r].osd_header[0]*32+HEADER_SIZE+id*OSD_CLUT_SIZE;
#ifdef  OSD_PAL_16b
    return getUINT16_bi(p);
#else
    return getUINT32_bi(p);
#endif
}    


//////////////////////////////////////////////////////
void osd_tog_region(BYTE r, int mode)
{
    int        t,j;
    t_osd_region *p;

    if (r>=osd_active_regions) return; //terry,2003/11/21 05:58PM

    //osd_printf("osd_tog_region(%d, %d)\n", r, mode);
    
    //if( (full_scrn==SOUND)&&(r>=SOUND_MAX_REGION) ) //terry,2003/11/21 05:59PM
    //    return;
    
    RegionOnOff[r][0]=mode;
    if(mode==OSD_OFF)
    {
        RegionOnOff[r][2]=STR_OS_SPACE;
        RegionOnOff[r][1]=0;
        for(j=0;j<MAX_SW_REGION;j++)            
            RegionStr[r][j][0]=0;                    
    }
    
    p=&region[r];
    
    for (t=0; t<2; t++)
    {
        BYTE    *obase;
        UINT16   h = p->osd_header[t];
        UINT8    x;
        
        /* check header-address */
        if (h==LINK_NULL) continue;
        obase = get_osdbuf_baseptr() + h*32;
        
        x = obase[0];
        switch(mode)
        {
        case OSD_ON:    x &= ~0x40; break;
        case OSD_OFF:   x |=  0x40; break;
        case OSD_TOG:   x ^=  0x40; break;
        }
        obase[0] = x;
    }

#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
	// use highlight to cover the osd show  region, robert.chang, 2006/03/16
	// turn highlight on or off by setting the bits of highlight header
	UINT8*  pRegion;
	UINT32 uiConfig;	
	if((r==REGION1 || r==REGION2) && (!(full_scrn & PROGRAM))) {
    		p=&region[r];
		pRegion = (UINT8*)(get_osdbuf_baseptr()+ (p->osd_header[0]<<5));
		uiConfig = pRegion[2];
		
		if(uiConfig&(0x01<<BIT_HIGHLIGHT)) {
			switch(mode)
			{
				case OSD_ON:
					osd_toggle_sub_highlight( r, 1 );
					break;
				case OSD_OFF: 	
					osd_toggle_sub_highlight( r, 0 );
					break;

			}
		}		
	}
#endif

#ifdef SUPPORT_SW_OSD_SCALING

    if( (GET_TV_RESOLUTION()  ==HD_720)  || (GET_TV_RESOLUTION()  ==HD_1080) ) {
        
        scaling_t_osd_region *scaling_p=&scaling_region[r];
  
        for (t=0; t<2; t++)
        {
            BYTE    *obase;
            UINT16   h = scaling_p->osd_header[t];
            UINT8    x;
            

            if (h==LINK_NULL) continue;
            obase = get_osdbuf_baseptr() + h*32;
            
            x = obase[0];
            switch(mode)
            {
            case OSD_ON:    x &= ~0x40; break;
            case OSD_OFF:   x |=  0x40; break;
            case OSD_TOG:   x ^=  0x40; break;
            }
            obase[0] = x;
        }
#if 0
            for(j=0; j<osd_active_regions; j++) {
		scaling_p=&scaling_region[j];
		for(t=0; t<2 ; t++){
       		BYTE    *obase;
        		UINT16  h = scaling_p->osd_header[t];
        		UINT8    x;
				
        		if (h==LINK_NULL) continue;
        		obase = get_osdbuf_baseptr() + h*32;
        		x = obase[0];
			x &= ~0x40;
        		obase[0] = x;
		}
           }
#endif
        regs0->osd_tlink_addr  = scaling_region[0].osd_header[0];
        regs0->osd_blink_addr  = scaling_region[0].osd_header[1];



        
//        if(mode == OSD_OFF) {
//            regs0->osd_tlink_addr  = region[0].osd_header[0];
//            regs0->osd_blink_addr  = region[0].osd_header[1];
//        }
    }  
    else {
#if 0
            for(j=0; j<osd_active_regions; j++) {
		p=&region[j];
		for(t=0; t<2 ; t++){
       		BYTE    *obase;
        		UINT16  h = p->osd_header[t];
        		UINT8    x;
				
        		if (h==LINK_NULL) continue;
        		obase = get_osdbuf_baseptr() + h*32;
        		x = obase[0];
			x &= ~0x40;
        		obase[0] = x;
		}
            }
#endif
            
            regs0->osd_tlink_addr  = region[0].osd_header[0];
            regs0->osd_blink_addr  = region[0].osd_header[1];
    }        

#endif
	
//#if    SUPPORT_OSD
    regs0->osd_en = 1;
//#else
    //regs0->osd_en = 0;
//#endif
}

//////////////////////////////////////////////////////
// initialize OSD regions using _t_osd_hdr table
//#define DEBUG_OSD_INIT_REGIONS
int osd_init_regions(int n, const _t_osd_hdr *hdrp)
{
    int i, j;
    void *rgnp;
    UINT16  osd_visible_w_byte;
    UINT8   region_index;

    SET_OSD_SCALE_BUF_FLAG(0);
    __osd_init();        

    for(i=0;i<MAX_REGION;i++)
    {                
    	t_osd_region *region_pointer = &region[i];	
        region_pointer->osd_used = 0;
        
        //set LINK_NULL to deleted header
        region_pointer->osd_header[0] = LINK_NULL;
        region_pointer->osd_header[1] = LINK_NULL;
    }

    rgnp = NULL;
    for (i=0, j=n-1; i<n; i++, j--)
    {
    	t_osd_region *region_pointer = &region[j];	
        region_index            =j;
        header_id               = hdrp[i].header_type;
        region_pointer->osd_visible_w = hdrp[i].width;        
        region_pointer->osd_h         = (hdrp[i].height)&~1;
        region_pointer->osd_used      = 1;
        osd_visible_w_byte		= osd_pixel_to_byte(hdrp[i].width, hdrp[i].format);

#ifndef OSD_SUPPORT_256_COLOR //WSLEE  20050518
			     //osd will be init fail, if we define "ifndef" with 256 color 
		if (hdrp[i].format==OSD_FORMAT_256COLOR)
			return -1;
#endif	// #ifndef OSD_SUPPORT_256_COLOR 

#ifndef OSD_SUPPORT_2_COLOR
		if (hdrp[i].format==OSD_FORMAT_2COLOR)
			return -1;
#endif	// #ifdef OSD_SUPPORT_2_COLOR

        if (osd_visible_w_byte % 4 == 0)
        {
            region_pointer->osd_w = osd_visible_w_byte;
        }
        else
        {
            // 2 color, 4 color, or direct color will be returned
            if (!((hdrp[i].format==OSD_FORMAT_16COLOR) || (hdrp[i].format==OSD_FORMAT_256COLOR)))	
				return -1;
            region_pointer->osd_w = osd_visible_w_byte + (4 - (osd_visible_w_byte % 4));
        }

        #ifdef DEBUG_OSD_INIT_REGIONS
        osd_printf("[%d]osd_w=%d, osd_visible_w=%d, osd_h=%d, osd_used=%d\n", j,
                region_pointer->osd_w,region_pointer->osd_visible_w, region_pointer->osd_h, region_pointer->osd_used);
        #endif
        
        osd_create_region1(region_index,       
                //&region[j],
                hdrp[i].x,  hdrp[i].y,
                rgnp,
                hdrp[i].format,
                hdrp[i].type
        );
        rgnp = &region[j];
        
        osd_display_list[j]=j;
    }
    
    osd_active_regions = n;
    osd_init__();

#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
    osd_init_highlights();
#endif

    return 1;
}    

#ifdef OSD_AUTO_RECOVER
UINT16	osd_get_header_chksum(UINT32 reg_idx, UINT32 field)
{
	t_osd_region	*region_pointer = &region[reg_idx];
	UINT16			current_check_sum = 0;
	BYTE*			header_address 
						= get_osdbuf_baseptr() + (region_pointer->osd_header[field]*32);
	
	current_check_sum = (header_address[0] & ~(0x40))
						^ header_address[1]
						^ header_address[2]
						^ ((UINT16*)header_address)[2]
						^ ((UINT16*)header_address)[3]
						^ ((UINT16*)header_address)[4]
						^ ((UINT16*)header_address)[5]
						^ ((UINT16*)header_address)[6]
						^ ((UINT16*)header_address)[7];
	return current_check_sum;
}

void osd_auto_recover()
{
	if (osd_active_regions == 0)
		return;
		
	t_osdv2_header	hdr;
	t_osd_region	*region_pointer;		
	UINT32			region_header_id;
	UINT32			region_count;
	BYTE*			header_address;
		
	for (region_count = 0; region_count < osd_active_regions; region_count ++)
	{
		UINT32	i = 0;
		UINT32	link_next[2];
		
		region_pointer	= &region[region_count];
		
		if (region_count < (UINT32)(osd_active_regions - 1))
		{
			link_next[0] = region[region_count+1].osd_header[0];
			link_next[1] = region[region_count+1].osd_header[1];
		}
		else
		{
			link_next[0] = LINK_NULL;
			link_next[1] = LINK_NULL;
		}

		for (i=0; i < 2; i++)
		{
			if (region_pointer->osd_header_chk_sum[i] != osd_get_header_chksum(region_count, i))
			{
				memset(&hdr,0,sizeof(hdr));
				
				region_header_id	= region_pointer->osd_header_id;
				header_address	= get_osdbuf_baseptr() + (region_pointer->osd_header[i]*32);
				
			    hdr.config0		= osd_header_config[region_header_id][0]
			    					| ((region_pointer->osd_format & 0x07) << BIT_MD)
			    					| (header_address[0] & 0x40);        
			    hdr.config1		= osd_header_config[region_header_id][1];
			    hdr.config2		= osd_header_config[region_header_id][2];
			    
			    if (p_scan)
				    hdr.v_size    = SWAP16(region_pointer->osd_h);
				else
					hdr.v_size    = SWAP16(region_pointer->osd_h>>1);
	
			    hdr.h_size    = SWAP16(region_pointer->osd_w/4);
			    hdr.x         = SWAP16(region_pointer->osd_x);
			    hdr.y         = SWAP16((p_scan ? (region_pointer->osd_y << 1) : region_pointer->osd_y));
			    hdr.link_data = SWAP16(region_pointer->osd_link_data[i]);
			    hdr.link_next = SWAP16(link_next[i]);
	
			    memcpyS(header_address,
			    		&hdr,
			    		sizeof(hdr));
			}
		}
	}
}
#endif // #ifdef OSD_AUTO_RECOVER

//////////////////////////////////////////////////////
//function: create region for interlace mode
//#define DEBUG_OSD_CREATE_REGION
//#define DEBUG_OSD_CREATE_REGION_BY_PIXEL
//Note: the osd create region is addition the color mode for create
//void osd_create_region1(t_osd_region *p, int X, int Y, t_osd_region *prev,BYTE bColorMode,BYTE bScanMode)
// 2005/04/12 yltseng
void osd_create_region1(UINT8 region_index, int X, int Y, t_osd_region *prev,BYTE bColorMode,BYTE bScanMode  __attribute__((unused)))
{
	t_osd_region *region_pointer = &region[region_index];
    BYTE    *ofrom    = get_osdbuf_baseptr();
    BYTE    *obase;    
    t_osdv2_header    hdr;
#ifdef OSD_PAL_16b    
    UINT16  *pa;      
#else    
    UINT32  *pa;      
#endif    
    UINT32    linkaddr;
    int         W,H,pn;    
    int        j,i,align;
    
    //W = p->osd_w/4;        //width must times of 4        
    //H = p->osd_h;        //Top + bottom    
    
    
    #ifdef PMP_UI   //for display normally in pal mode. 
    #include "fsNAV.h"
        if((getVPP_TVsystem() ==  1)&&(region_index==2)&&(pFsJpeg->gifsState == FS_STATE_MODE))//if(tv_format==TV_FORMAT_PAL)
        {
            if(!(full_scrn&SETUP))
            {
                Y = (Y*6)/5;
                //joshua, 20050929, region_pointer->osd_h must be "even".
                region_pointer->osd_h = ((region_pointer->osd_h*6)/5)&~1;
            }    
        }
    #endif
    
    //20050809 mimitsai add for avoid changing PAL to NTSC, the insturction will be cutted.
    #ifdef EASTECH_STD_SETUP_MENU 
    if(getVPP_TVsystem()==1)//if(tv_format==TV_FORMAT_PAL)
    {
        if(full_scrn & SETUP)
            Y = (Y*7)/5;
    } 
     #endif
    
    W = region_pointer->osd_w/4;        //width must times of 4        
    H = region_pointer->osd_h;        //Top + bottom 

    region_pointer->osd_x = X;
    region_pointer->osd_y = Y;

    if(p_scan)
    {
        Y<<=1;
    }
    else
    {
        //if(bScanMode==OSD_INTERLACED)
        H>>=1;
    }

    #ifdef OSD_AUTO_RECOVER
    region_pointer->osd_header_id = header_id;
    #endif	// #ifdef OSD_AUTO_RECOVER
         
    for (i=0;i<2;i++)
    {    
        obase=ofrom+(osd_free<<5);    
        
        //buffer must in 32 aligment
        //p->osd_header[i]=osd_free;
        region_pointer->osd_header[i]=osd_free;
        
        // get prev link address (for header generation)
        linkaddr = (prev==NULL) ? LINK_NULL : prev->osd_header[i];
        
        //Cal. data blk start addr.        
        osd_free  = osd_free + OSD_DATA_OFFSET(bColorMode);
        
        //p->osd_format=bColorMode;
        region_pointer->osd_format=bColorMode;
        
        //initial header        
        memset(&hdr,0,sizeof(hdr));
        hdr.config0   = osd_header_config[header_id][0]|((bColorMode & 0x07) << BIT_MD);        
        hdr.config1   = osd_header_config[header_id][1];        
        hdr.config2   = osd_header_config[header_id][2];        
        
        hdr.v_size    = SWAP16(H);
        hdr.h_size    = SWAP16(W);
        hdr.x         = SWAP16(X);
        hdr.y         = SWAP16(Y);
        hdr.link_data = SWAP16(osd_free);
        hdr.link_next = SWAP16(linkaddr);

        #ifdef OSD_AUTO_RECOVER
        region_pointer->osd_header_chk_sum[i] = (hdr.config0 & ~(0x40))
        										^ hdr.config1
        										^ hdr.config2
        										^ hdr.v_size
        										^ hdr.h_size
        										^ hdr.x
        										^ hdr.y
        										^ hdr.link_data
        										^ hdr.link_next;
	    region_pointer->osd_link_data[i] = osd_free;
	    #endif	// #ifdef OSD_AUTO_RECOVER

        #ifdef DEBUG_OSD_CREATE_REGION
        osd_printf("\nRegion[%d]:\n",region_index);
        osd_printf("hdr.config0=%x\n",hdr.config0);
        osd_printf("hdr.config0=%x\n",hdr.config1);
        osd_printf("hdr.config0=%x\n",hdr.config2);
        osd_printf("hdr.v_size=%d\n",SWAP16(hdr.v_size));
        osd_printf("osd_visible_w(pixel-unit) =%d\n",region_pointer->osd_visible_w);
        osd_printf("osd_w(byte-unit) =%d\n",region_pointer->osd_w);
        osd_printf("hdr.h_size(4bytes-unit) =%d\n",SWAP16(hdr.h_size));
        osd_printf("hdr.x=%d\n",SWAP16(hdr.x));
        osd_printf("hdr.y=%d\n",SWAP16(hdr.y));
        osd_printf("hdr.link_data=%d\n",SWAP16(hdr.link_data));
        osd_printf("hdr.link_next=%d\n",SWAP16(hdr.link_next));
        #endif
        
        memcpyS(obase,&hdr,sizeof(hdr));
        //osd_printf("obase:%x data:%x offset:%x\n",obase,osd_free<<5,OSD_DATA_OFFSET(bColorMode));
        
        obase+= HEADER_SIZE;    // skip header region
        
//#ifdef OSD_BMP
//	pa = (UINT32*)g_aOsdPalette[header_id];
//#elif defined(OSD_PAL_16b)
#ifdef OSD_PAL_16b
        pa = (UINT16*)osd__pal[header_id];
#else
        pa = (UINT32*)osd__pal[header_id];
#endif

#if defined(SUPPORT_SMI_MultiColor)
        if( IS_EXT_SUP_ACTIVATED() && ( region_index == 3 ) && SmiSupType )
            pa = (UINT32*) palette_16color_MP4_SUB;
#endif
        if( bColorMode == OSD_FORMAT_2COLOR )
        {
			#ifdef OSD_SUPPORT_2_COLOR
            pn = 2;
			#else
			return;
			#endif	// #ifdef OSD_SUPPORT_2_COLOR
		}
        else if( bColorMode == OSD_FORMAT_4COLOR )
            pn = 4;
        else if( bColorMode == OSD_FORMAT_16COLOR )
            pn = 16;                           
        else if( bColorMode == OSD_FORMAT_256COLOR )
        {
			#ifdef OSD_SUPPORT_256_COLOR
            pn = 256;
			#else
			return;
			#endif	// #ifdef OSD_SUPPORT_256_COLOR
		}
        else
            pn = 0;

        align = (OSD_DATA_OFFSET(bColorMode)<<5) - HEADER_SIZE - OSD_CLUT_SIZE*pn;        

        // put color   
        while( pn-- > 0 )
        {
#ifdef OSD_PAL_16b                
            wbe16(obase, *pa);
#else            
    #ifdef SUPPORT_FUNCTION_MENU
            if((full_scrn&SETUP_PLUS) && (pn==16))
            {//需要背景为透明
                wbe32(obase, 0);
            }
            else
    #endif //end #ifdef SUPPORT_FUNCTION_MENU
    #ifdef SUPPORT_TTX_MIXER_KEY //tcf added 2006-4-18 11:05上午
    		if((header_id==TTX_HEADER)&&(pn==15)&&(ttx_bg_mixer==1))//15 is bg color,but in palette_ttx_16color is 0,i don't konw the reason.
    			wbe32(obase, 0);
    		else
    #endif
                wbe32( obase, osd_rescale_color(*pa) ); // 2004/10/16 yltseng
#endif            
            obase += OSD_CLUT_SIZE;
            pa ++;
        }
        
        //Add for DVB Subtitle solution //The invisible pallete table index may not be 0.
        #ifdef SUPPORT_SUBTITLE
        extern int l_subtitle_show_flag;
        extern UINT16 Region_InvisibalPallete_Index[8];
        if (l_subtitle_show_flag)
        {
            UINT8 utemp = Region_InvisibalPallete_Index[region_index]; 
            utemp = ((utemp&0xF)<<4)|utemp;
            UINT32 uPalleteData;

            uPalleteData = utemp|(utemp<<8)|(utemp<<16)|(utemp<<24);

            memset(obase,uPalleteData,align);
            obase+=align;  
        
            for (pn=H;pn>0;pn--)
            {
                for(j=0;j<W;j++) ((UINT32 *)obase)[j]=uPalleteData;

                obase+=(W<<2);            
            }

            SetOsdCol (region_index, region_index, Region_InvisibalPallete_Index[region_index], __palette4F(0,0,0,0)); //HW def != DVB subtitle spec.
        }
        else
        {
            memset(obase,0,align);
            obase+=align;
        
            for (pn=H;pn>0;pn--)
            {
                for(j=0;j<W;j++) ((UINT32 *)obase)[j]=0;
                //next line    
               obase+=(W<<2);            
            }
        }
        
        #else //SUPPORT_SUBTITLE
        memset(obase,0,align);
        obase+=align;        
        
    // clear OSD bitmap content
        for (pn=H;pn>0;pn--)
        {
            for(j=0;j<W;j++) ((UINT32 *)obase)[j]=0;
            //next line    
        obase+=(W<<2);            
        }
        #endif //SUPPORT_SUBTITLE

        //osd_printf("--obase:%x\n",obase);        
        //aligment buffer on 32 byte start
        //osd_free += (H*W*4/32);
        osd_free    = ((obase - ofrom)+31)/32;
        
        //if on non-interface mode , display become top line= bottom line
        //if ( (bScanMode==OSD_NONINTERLACED)||p_scan )
        //we don't use OSD_NONINTERLACED varible
        if (p_scan )
        {
            region_pointer->osd_header[1] = region_pointer->osd_header[0];
            break;
        }        
    }
    
    // This part is for invisble region feature
	// If mode_width is not divisible by 4, only works for 16/256 color
	if (region_pointer->osd_visible_w != 
	    osd_byte_to_pixel(region_pointer->osd_w, region_pointer->osd_format))
	{
		coordinate start = {region_pointer->osd_visible_w, 0};
		UINT16	length = osd_byte_to_pixel(region_pointer->osd_w, region_pointer->osd_format) 
		                    - region_pointer->osd_visible_w;

		#ifdef DEBUG_OSD_CREATE_REGION_BY_PIXEL
		osd_printf("---Region[%d]: transparent rectangle is drawing---\n", region_index);
		osd_printf("osd_visible_w(in pixel): %d\n", region_pointer->osd_visible_w);
        osd_printf("pixel to byte(in byte): %d\n", 
            osd_pixel_to_byte(region_pointer->osd_visible_w, region_pointer->osd_format));
		osd_printf("osd_w(in byte): %d\n", region_pointer->osd_w);
		osd_printf("osd_format: %d\n", region_pointer->osd_format);
		osd_printf("--\n");
		osd_printf("start_x: %d\n", start.x);
		osd_printf("start_y: %d\n", start.y);
		osd_printf("length of rectangle: %d\n", length);
		osd_printf("height: %d\n", region_pointer->osd_h);
		osd_printf("------------------------------------------------\n");
		delay_1ms(5);
		#endif

		switch (region_pointer->osd_format)
		{
			dimension out_dimension;
			case 1:	
					out_dimension.x_length = length;
					out_dimension.y_length = region_pointer->osd_h;

					#ifdef SUPPORT_SUBTITLE
					extern int l_subtitle_show_flag;
					if (l_subtitle_show_flag)
					{
					    osd_draw_rectangle(&start, &out_dimension, 0, region_index);
					}
					else
					#endif //SUPPORT_SUBTITLE
					{
					    osd_draw_rectangle(&start, &out_dimension, 15, region_index);
					}
					break;
#ifdef OSD_SUPPORT_256_COLOR
			case 2:	out_dimension.x_length = length;
					out_dimension.y_length = region_pointer->osd_h;
					osd_draw_rectangle(&start, &out_dimension, 255, region_index);
					break;
#endif	// #ifdef OSD_SUPPORT_256_COLOR
			default:	// 2 color, 4 color, and direct color
				break; //osd_draw_rectangle(start, length, osd_mode_list[mode_index].mode_height,
		}
	}
                 
}

//////////////////////////////////////////////////////
#ifdef OSD_COLOR_ADJUST_BY_BRIGHTNESS_AND_CONTRAST      // 2004/11/12 yltseng

    #ifdef DVD_SETUP_REENG
#include "setup_VA.h"
    #else
#include "setup_page.h"
    #endif
    
int osd_get_brightness(UINT8 b_new_val)
{
    #define b_scale 4
    return b_scale * (b_new_val - 6);
}

UINT32 osd_get_contrast(UINT8 c_new_val)
{
    // 0.82 * 512, 0.85 * 512, 0.88 * 512, 0.91 * 512 .... 1.18 * 512 ( contrast scale step size = 0.03 )
    UINT32 c_scale[13] = {420, 435, 451, 466, 481, 497, 512, 527, 543, 558, 573, 589, 604};
    return c_scale[c_new_val];
}

UINT32 osd_rescale_color(UINT32 uiColor)
{  
    int g = (0xff000000 & uiColor) >> 24;
    int b = (0x00ff0000 & uiColor) >> 16;
    int r = (0x0000ff00 & uiColor) >> 8;
    UINT8 alpha = (0x000000ff & uiColor);  
        
    #ifdef DEBUG_OSD_RESCALE_COLOR
    printf("==> Begin osd_rescale_color\n");
    printf("old R: %d\n", r);
    printf("old G: %d\n", g);
    printf("old B: %d\n", b);
    #endif
    
    #ifdef DVD_SETUP_REENG      // 2004/11/12 yltseng
    UINT32  c_coef = osd_get_contrast  ( setup_VA[ SETUP_VA_CONTRAST   ] - 2 );
    int     b_coef = osd_get_brightness( setup_VA[ SETUP_VA_BRIGHTNESS ] - 2 );    
    #else
    UINT32  c_coef = osd_get_contrast  ( SETUP_CONTRAST - 2 );
    int     b_coef = osd_get_brightness( SETUP_BRIGHTNESS - 2 );
    #endif
    
    if (g > 20)
    {
        g = (UINT32)((int)( (g * c_coef) >> 9 ) + b_coef);
        g = g > 255 ? 255 : g < 0 ? 0 : g;
    }
    
    if (b > 20)
    {
        b = (UINT32)((int)( (b * c_coef) >> 9 ) + b_coef);
        b = b > 255 ? 255 : b < 0 ? 0 : b;     
    }        
    
    if (r > 20)
    {
        r = (UINT32)((int)( (r * c_coef) >> 9 ) + b_coef);
        r = r > 255 ? 255 : r < 0 ? 0 : r;         
    }
   
    #ifdef DEBUG_OSD_RESCALE_COLOR
    printf("new R: %d\n", r);
    printf("new G: %d\n", g);
    printf("new B: %d\n", b);
    printf("=old color: %08x\n", uiColor);
    printf("=new color: %08x\n\n\n", ((g << 24) | (b << 16) | (r << 8) | alpha));
    #endif
    
    return ((g << 24) | (b << 16) | (r << 8) | alpha);
}

void osd_update_setupmenu_palette()
{
    int r = 0;
    UINT32 *palette = osd__pal[SETUP_HEADER];
    
    #ifdef DEBUG_OSD_UPDATE_SETUPMENU_PALETTE
    printf("==> Begin: osd_update_setupmenu_palette\n");
    #endif
    
    
    for( ; r < 16; r++ )
    {
        UINT8 *p, *q, *t;
        t_osd_region *region_pointer = &region[0];
        t = get_osdbuf_baseptr()+HEADER_SIZE+r*OSD_CLUT_SIZE;
        p = t + (region_pointer->osd_header[0] << 5);
        q = t + (region_pointer->osd_header[1] << 5);
        
        wbe32( p, osd_rescale_color( palette[r] ) );
        wbe32( q, osd_rescale_color( palette[r] ) );
    }
}
#else

UINT32 osd_rescale_color(UINT32 uiColor) { return uiColor; }

#endif  //OSD_COLOR_ADJUST_BY_BRIGHTNESS_AND_CONTRAST


//////////////////////////////////////////////////////
UINT8 *get_osdbuf_region_ptr(int _region, int _field)
{
    UINT8 *p = get_osdbuf_baseptr();
    p = p + ((region[_region].osd_header[_field] + OSD_DATA_OFFSET(region[_region].osd_format))<<5);
    return  p;
}

//////////////////////////////////////////////////////
/*
#if defined(OSD_FONT_API)||defined (OSD_BMP)
//move out this function,because it must be used in OSD_BMP,suqiaoli modified,2004-12-22
//this function can be used when tv format change from NTSC to PAL
//move region r to a new location
//liweihua add 2004-1-13 16:00
void MoveRegion(BYTE r,UINT16 x,UINT16 y)
{
    osd_set_region_position(r, x, y);
    
    
    UINT16* pOSDHeader1 = (UINT16*)(get_osdbuf_baseptr() + region[r].osd_header[0] * 32);
    UINT16* pOSDHeader2 = (UINT16*)(get_osdbuf_baseptr() + region[r].osd_header[1] * 32);   
    UINT16 nCol, nRow;

    nRow = y & 0x3ff; 
    nCol = x & 0x3ff;

    wbe16(pOSDHeader1 + 4, nRow);
    wbe16(pOSDHeader2 + 4, nRow);
    wbe16(pOSDHeader1 + 5, nCol);
    wbe16(pOSDHeader2 + 5, nCol);

}
#endif
*/
//////////////////////////////////////////////////////

#endif //#if SUPPORT_OSD
#endif // #ifdef NEW_OSD_DRIVER

