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

/*
*   FILE Name :
*                   osd_16BDC.c
*
*   DESCRIPTION
*   control OSD interface for 16bit direct color mode.
*
*         Rev	Date	        Author(s)      Status & Comments History :
*                 20041022        jslin           created file
*
*   Note : 
*         currently, OSD 16bit direct color mode is only used by SWD engine.
*         it will only ONE full screen OSd regine, 
*         visual size 720*480, resolution 360*240.
*         and this OSD regine uses the sdram space of JPEF PS buffer
*/


#include "memmap0.h"    // 2004/11/05 yltseng
#include "memcfg.h"


#define OSD_MAX_W   360         // OSD region max width
#define OSD_MAX_H    240        // OSD region max height

#ifndef DVDRELEASE
#define MONE_OSD_16BDC
#endif


void osd_16BDC_init_bitmap(UINT8 *hp, int w, int h);
void osd_16BDC_set_region(t_osd_region *p);
void osd_16BDC_create_region(t_osd_region *p, int X, int Y, t_osd_region *prev);//, int scanmd);
void osd_16BDC_init(void);
void osd_16BDC_draw_bitmap(UINT16 *ptr, int x, int y, int w, int h, UINT8 mask);
void osd_16BDC_setbuf(void);
void osd_16BDC_get_block(UINT8 *ptr, int x, int y, int w, int h);
void osd_16BDC_draw_string(int xStart, int yStart, const BYTE *str, UINT16 fontColor, UINT16 bkColor,UINT16 size);
extern const unsigned char LOWERCASE_FONT_BITMAP[];
#define	 lowercase_table	LOWERCASE_FONT_BITMAP

/**************************************************************************
 *  Function Name: 
 *                        osd_16BDC_setbuf                                        
 *  Purposes:                                                            
 *                  set OSD regine pointer 
 *  Descriptions:                                                         
 *    
 *  Arguments:                                                            
 *    
 *  Returns:                                                             
 *    
 *  See also:                                                             
 *    
 **************************************************************************/
void osd_16BDC_setbuf()
{
    if(OSD_buffer_16bit==1) 
    {
        REG_OSDYA                   = GP_REF1_LUMA + 64;
        REG_OSDYA2                  = GP_REF1_LUMA + 64;//osdya_n;
        BackUpOSDAddress(GP_REF1_LUMA + 64);
    } 
}


/**************************************************************************
 *  Function Name: 
 *                          osd_16BDC_init                                        
 *  Purposes:                                                            
 *                          initiate OSD region
 *  Descriptions:                                                         
 *                          set regine format, widthe, height, and then create region
 *  Arguments:                                                            
 *    
 *  Returns:                                                             
 *    
 *  See also:                                                             
 *    
 **************************************************************************/
void osd_16BDC_init(void)
{
    #ifdef MONE_OSD_16BDC
    osd_puts("\n\nosd init flash\n\n");
    #endif
    
    osd_16BDC_setbuf();

    #ifdef MONE_OSD_16BDC
        printf("\n\n>>>>>16bit OSD buffer ptr[%x]  [%d]\n", get_osdbuf_baseptr(), OSD_buffer_16bit);
    #endif
    
    osd_free = 0;
    region[0].osd_w		= 360;
    if(p_scan) {
	region[0].osd_h		= 480;
    } else {
    	region[0].osd_h		= 240;
    }		
    region[0].osd_format	= OSD_FORMAT_DIRECT16B;     //A-RGB 1-555

    osd_16BDC_create_region(&region[0], 0, 0, NULL);//, 0);

    osd_active_regions = 1;
    ENABLE_OSD();
}



/**************************************************************************
 *  Function Name: 
 *                          osd_16BDC_create_region                                       
 *  Purposes:                                                            
 *                          create OSD region
 *  Descriptions:                                                         
 *                          set OSD region header information
 *  Arguments:                                                            
 *    
 *  Returns:                                                             
 *    
 *  See also:                                                             
 *    
 **************************************************************************/
void osd_16BDC_create_region(t_osd_region *p, int X, int Y, t_osd_region *prev)
{
    int                       oW, oH;
    t_osdv2_header    hdr;
    UINT16                lnkprev;
    UINT8                 *hp;
    unsigned              clut_type;
    int				 color_format;
    int                       hdr_size;
    unsigned		clut_update;

    
    lnkprev = (prev!=NULL) ? prev->osd_header[0] : LINK_NULL;

    p->osd_header[0] = osd_free;
    p->osd_header[1] = osd_free;

    oW			= p->osd_w/2;
    oH			= p->osd_h;
    color_format	= p->osd_format;

    clut_type		= OSDV2_CLUT_32b;

    hdr_size  = 16;
    clut_update =0;// 1;

    hp = (UINT8 *)get_osdbuf_baseptr() + (osd_free<<5);

    osd_free  = osd_free + ((hdr_size+31)>>5);

    memset(&hdr,0,sizeof(hdr));

    hdr.config0   = ((clut_update & 0x01) << BIT_CU)
                | ((0x0) << BIT_FT)
                | ((0x1) << BIT_PR)
                | ((color_format & 0x07) << BIT_MD);

    hdr.config1   = ((0x00 & 0x0f) << BIT_SHD)
                | ((0x0f & 0x0f) << BIT_BLND);

    hdr.config2   = V2_CLUT_TYPE(clut_type)
  				| V2_RGB_MODE
				| V2_SWAP_BYTE_OFF
				| V2_SHADE_MODE_A;
  
    hdr.v_size    = SWAP16(oH);
    hdr.h_size    = SWAP16(oW);
    hdr.x         = SWAP16(X);
    hdr.y         = SWAP16(Y);
    hdr.link_data = SWAP16(osd_free);
    hdr.link_next = SWAP16(lnkprev);

    memcpy(hp,&hdr,sizeof(hdr));

    // initialize bitmap
    hp        = get_osdbuf_baseptr() + (osd_free<<5);
    osd_16BDC_init_bitmap(hp, oW, oH);
}


/**************************************************************************
 *  Function Name: 
 *                          osd_16BDC_init_bitmap                                                               
 *  Purposes:                                                            
 *                          initiate OSD region with transprant block
 *  Descriptions:                                                         
 *    
 *  Arguments:                                                            
 *    
 *  Returns:                                                             
 *    
 *  See also:                                                             
 *    
 **************************************************************************/
void osd_16BDC_init_bitmap(UINT8 *hp, int w, int h)
{
    int i, j;
  
    unsigned a, R, G, B;
    unsigned v;
    R	= 0x00;
    G	= 0x00;
    B	= 0x00;
    a   = 0x0;

    #ifdef MONE_OSD_16BDC
        printf("w[%d] h[%d] [%x] [%x]\n", w, h, REG_OSDYA, REG_OSDYA2);
    #endif
    
    v = ((a&0x1)<<15)|(((R>>3)&0x1f)<<10) | (((G>>3)&0x1f)<<5) | (((B>>3)&0x1f)<<0) ;		// 1555
	if(p_scan)
	{
		for (i=0;i<h;i++)
		{
			for (j=0;j<w;j++)
			{
				 *(UINT16 *)(&hp[0]) = SWAP16(v);
				 *(UINT16 *)(&hp[2]) = SWAP16(v);

				hp+=(w*4);
				 *(UINT16 *)(&hp[0]) = SWAP16(v);
				 *(UINT16 *)(&hp[2]) = SWAP16(v);
				hp-=(w*4);
	
				hp+=4;
			}
			hp+=(w*4);
			i++;
		}
	}
	else
	{
		  for (i=0;i<h;i++)
		  {
				for (j=0;j<w;j++)
			      {
					*(UINT16 *)(&hp[0]) = SWAP16(v);
					*(UINT16 *)(&hp[2]) = SWAP16(v);
					hp+=4;
				  }
		    }
	} 
}


/**************************************************************************
 *  Function Name: 
 *                          osd_16BDC_draw_bitmap                                                              
 *  Purposes:                                                            
 *                          display bitmap in OSD region
 *  Descriptions:                                                         
 *                          copy a bitmap block into OSD buffer
 *  Arguments:                                                            
 *                          *ptr     : bitmap pointer
 *                          (x, y)   : bitmap start address in OSD region
 *                          (w, h)  : bitmap width and height
 *                          mask   : transprant parameter
 *  Returns:                                                             
 *    
 *  See also:                                                             
 *    
 **************************************************************************/
void osd_16BDC_draw_bitmap(UINT16 *ptr, int x, int y, int w, int h, UINT8 mask)
{
	UINT8 *hp;
	UINT16 v, colorMask;
	int region_W, draw_X, draw_Y, draw_W, draw_H, draw_P;
	int i, j;//, Dcase;

    if(x<0)
    {
        draw_X = 0;
        draw_W = w+x;
    }
    else if((x+w) > OSD_MAX_W)
    {
        draw_X = x;
        draw_W = (OSD_MAX_W-x);
    }
    else
    {
        draw_X = x;
        draw_W = w;
    }

    if(y<0)
    {
        draw_Y = 0;
        draw_H = h+y;
        draw_P = (h-draw_H) * w;
    }
    else if((y+h)>OSD_MAX_H)
    {
            draw_Y = y;
            draw_H = (OSD_MAX_H-y);
            draw_P = 0;
    }
    else
    {
        draw_Y = y;
        draw_H = h;
        draw_P = 0;
    }



	if(mask){
		colorMask = 0x0;
	} else {
		colorMask = 0xffff;
	}
	
	hp = get_osdbuf_baseptr() + (osd_free<<5);
	region_W = (region[0].osd_w/2)*4;

	if(p_scan)
	{
		hp = hp +(2*draw_Y*region_W) + (draw_X*2);

		for (i=0; i<draw_H; i++)
		{
		       if(x<0)
		       {
                        draw_P -=x; 
                     }
			for(j=0; j<draw_W; j++)
			{
				v=(UINT16)ptr[draw_P];
				*(UINT16 *)(&hp[0]) = (v&colorMask);

				hp+=region_W;
				v=(UINT16)ptr[draw_P];
				*(UINT16 *)(&hp[0]) = (v&colorMask);
				hp-=region_W;

				hp+=2;
                            draw_P++;
			}
			hp+=region_W;
			hp+=(region_W-(draw_W*2));

                     if((x+w)>OSD_MAX_W)
                     {
                        draw_P+=(w-draw_W);
                     }
		}
	}
	else
	{
		hp = hp +(draw_Y*region_W) + (draw_X*2);

		for (i=0; i<draw_H; i++)
		{
		       if(x<0)
		       {
                        draw_P -= x; 
                     }

			for(j=0; j<draw_W; j++)
			{
				v=(UINT16)ptr[draw_P];
				*(UINT16 *)(&hp[0]) = (v&colorMask);
				hp+=2;
                            draw_P++;
			}
			hp+=(region_W-(draw_W*2));

                     if((x+w)>OSD_MAX_W)
                     {
                        draw_P+=(w-draw_W);
                     }
		}
	}
}


/**************************************************************************
 *  Function Name: 
 *                          osd_16BDC_get_block                                        
 *  Purposes:                                                            
 *                          copy an OSD block into tempoary memory space
 *  Descriptions:                                                         
 *    
 *  Arguments:                                                            
 *                          *ptr     : bitmap pointer
 *                          (x, y)   : bitmap start address in OSD region
 *                          (w, h)  : bitmap width and height   
 *  Returns:                                                             
 *    
 *  See also:                                                             
 *    
 **************************************************************************/
void osd_16BDC_get_block(UINT8 * ptr, int x, int y, int w, int h)
{
    UINT8 *hp;
    int region_W;
    int i, j, Bpos;

    hp = get_osdbuf_baseptr() + (osd_free<<5);
    region_W = (region[0].osd_w/2)*4;

    if(p_scan)
    {
        hp = hp +(2*y*region_W) + (x*2);

        for(i=0; i<h; i++)
        {
            for(j=0; j<w; j++)
            {
                Bpos = (i*w*2)+(j*2);
                ptr[Bpos] = hp[0];
                ptr[Bpos+1] = hp[1];
                hp+=2;
            }
            hp+=(region_W-(w*2));
            hp+=region_W;
        }
    }
    else
    {
        hp = hp + (y*region_W) + (x*2);

        for(i=0; i<h; i++)
        {
            for(j=0; j<w; j++)
            {
                Bpos = (i*w*2)+(j*2);
                ptr[Bpos] = hp[0];
                ptr[Bpos+1] = hp[1];
                hp+=2;
            }
            hp+=(region_W-(w*2));
        }
    }
}

/**************************************************************************
 *  Function Name: 
 *                          osd_16BDC_draw_string                                 
 *  Purposes:                                                            
 *                          draw 16bit color string
 *  Descriptions:                                                         
 *    
 *  Arguments:                                                            
 *                         *str    : string pointer end with "\0"
 *                          *start:          (x,y) start-coordinate of rectangle 
 *                          *dimension:      width and height of font
 *                          
 *  Returns:                                                             
 *    
 *  See also:                                                             
 *    
 **************************************************************************/
void osd_16BDC_draw_string(int xStart, int yStart, const BYTE *str, UINT16 fontColor, UINT16 bkColor,UINT16 size)
{
    BYTE c;
    BYTE *pFont;
    UINT32 iStrLoc;
    UINT16  region_W;
    unsigned int i,j,k,font_width,font_height,bitcount,shiftnum,index;
    UINT8 *hp;
    UINT32 disploc = 0,total_width=0,mask = 0x80;
	
    region_W = (region[0].osd_w/2)*4;

   iStrLoc = 0;
   
   while( (c = ((BYTE *)str)[iStrLoc])!= '\0' ) 
    {
               
        iStrLoc++;
        
        //printf("\n%x\n", c);
        if ((c >= 'a') && (c <= 'z'))
	{
		index = 48 * (c -97);
		if ( (c=((BYTE *)str)[iStrLoc -1])=='\0' ) break; 
		for (i = 0; i < 24; i++)
		{
			UINT8 cc1,cc2;
    		
    			cc1=lowercase_table[index+i*2];
    			cc2=lowercase_table[index+i*2+1];
				
			pFont [i*2] = cc1;
			pFont [i*2+1] = cc2;
		}
	}

	  else if (c == '\r')      //prefix characher:to use font_table2
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
        else 
        {   
            if (c=='\n')
            {
                c=' ';   
            }    

            //get current char entry
           if ((pFont = get_font_entry(0,c))==NULL) continue;
        }	

	 hp = get_osdbuf_baseptr() + (osd_free<<5);

	if ((c >= 'a') && (c <= 'z'))
	{
		font_width = 16;
		font_height = 24;
		disploc = 0;
	}else{	
		font_width = pFont[0];
		font_height = pFont[1];
		disploc = 3;
	}
	
	if (size==0)//small size
	{
		font_width =font_width;
		font_height = font_height /2;
		bitcount = 4;
	}else{			//big size
		font_width = font_width;
		font_height = font_height ;
		bitcount = 8;
	}	
	#if 0	
	printf("fontcolor =%d=======bkcolor========%d\n",fontColor,bkColor);
	printf("font_width=%d,font_height=%d\n",font_width,font_height);
	printf("========%x=========%x\n",xStart,yStart);
	#endif
	hp = hp + (yStart* region_W) + (xStart* 2);
	
	for ( i=0;i<font_height;i ++)
	{
		for (j=0;j<font_width/8;j++)
		{	
			for(k=0;k<bitcount;k ++)
			{
			if(size)
				shiftnum = k;
			else
				shiftnum = 2*k;
			if ((pFont[j + disploc] <<shiftnum) & mask)
			{
				//printf("pFont[((j + disploc) ]==========%d\n",pFont[j + disploc]);
				*(UINT16*)(&hp[0]) = SWAP16(fontColor);
			}	
			else
			{
				//printf("pFont[((j + disploc) ]====%d\n",pFont[j + disploc]);
				*(UINT16*)(&hp[0]) = SWAP16(bkColor);
			}	
			hp += 2;
			}
		}
		if(size)
		{
			hp+=(region_W - (font_width*2));
			disploc +=2;
		}
		else
		{
			hp+=(region_W - (font_width));
			disploc +=4;
		}
	}
         //========================================
        	 if(size)
		 	xStart+=font_width;
		else
        		xStart+=font_width/2;
        
        //Check that the length of string is longer than region width or not
        if(xStart> region_W)
           break;    
    }
    //printf("\n");
}

