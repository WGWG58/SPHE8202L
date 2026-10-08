/*
** FILE
** osdv2.c
**
** DESCRIPTION
** Ccontrol 728 OSD hardware interface.
*/

#include "config.h"

#ifdef OSD_VERSION_2

#include "global.h"
#include "memmap.h"
#include "func.h"
#include "cfont.h"
#include "osd.h"
#include "osdhw.h"

//DVD
#include "regmap.h"
#include "endian.h"
#include "stdlib.h"


#ifndef	NULL
#define	NULL    	((void *)0)
#endif

#ifndef	LINK_NULL
#define	LINK_NULL   0xffff
#endif

//
// buffer
//
#define OBV_BASE_PTR            (regs0->osd_base_addr)
#define	OBV_BASE_ADDR           (SDRAM_BASE + OBV_BASE_PTR*1024)

#define	get_osdbuf_baseptr()	((void *)OBV_BASE_ADDR)


//
// clut_entries_table[]
// size of color entry table.
static	const	UINT16	clut_entries_table[8] = 
{
#ifdef OSD_SUPPORT_256_COLOR
	4, 16, 256, 0, 0, 0, 0, 0
#else
	4, 16, 0, 0, 0, 0, 0, 0
#endif	// #ifdef OSD_SUPPORT_256_COLOR
};

//
// ppw_table[]
// pixel-per-word
static	const	UINT8	ppw_table[8] = 
{
  32/2, 32/4, 32/8, 32/8, 32/16, 32/16, 32/16, 32/16
};


void    osd_set_region(t_osd_region *p);
void    osdv2_create_region(t_osd_region *p, int X, int Y, t_osd_region *prev, int scanmd);

void
osd_initf(void)
{
  osd_free = 0;
#if 0
  region[1].osd_w		= (560)/4;
  region[1].osd_h		= 240;
  region[1].osd_format	= OSD_FORMAT_256COLOR;
#else
  region[1].osd_w		= (100)/2;
  region[1].osd_h		= 240;
  region[1].osd_format	= OSD_FORMAT_DIRECT16A;
#endif
  osdv2_create_region(&region[1], 20, 40, NULL, 0);

#ifdef OSD_SUPPORT_256_COLOR
  region[0].osd_w		= 100/4;
  region[0].osd_h		= 16;
  region[0].osd_format	= OSD_FORMAT_256COLOR;
  osdv2_create_region(&region[0], 40, 10, &region[1], 0);
#endif	// #ifdef OSD_SUPPORT_256_COLOR

  osd_set_region(&region[0]);
  osd_enable();
}


//
// FUNCTION
// osd_set_region
//
void
osd_set_region(t_osd_region *p)
{
	if (p!=NULL)
	{
		regs0->osd_tlink_addr = p->osd_header[0];
		regs0->osd_blink_addr = p->osd_header[1];
	}
	else
	{
		regs0->osd_tlink_addr = LINK_NULL;
		regs0->osd_blink_addr = LINK_NULL;
	}
}


//
//
//
void
osdv2_init_clut(UINT8 *hp, int ctype)
{
#ifdef OSD_SUPPORT_256_COLOR
  int i;
  for (i=0; i<256; i++)
  {
    unsigned y, cb, cr, bl;
    unsigned clutc;

    y  = 0xa0; //i * 4;
//    cb = 0x80; cr = 0x80;
    cb = i; cr = 255-i;
    bl = i;
	if (i==255) {y=0xff;cr=0x80;cb=0x80;bl=0xff;}

    switch (ctype)
    {
      case OSDV2_CLUT_32b:		// Y[7:0], Cb[7:0], Cr[7:0], BL[7:0]
        clutc = (bl) | (cr<<8) | (cb<<16) | (y<<24);
        ((UINT32 *)hp)[0] = SWAP32(clutc);
        hp+=4;
        break;
      case OSDV2_CLUT_16b:		// Y[7:2], Cb[7:4], Cr[7:4], BL[7:6]
      default:
        clutc = ((bl>>6)&0x03) | (((cr>>4)&0x0f)<<2) | (((cb>>4)&0x0f)<<6) | (((y>>2)&0x3f)<<10);
        ((UINT16 *)hp)[0] = SWAP16(clutc);
        hp+=2;
        break;
    }
  }
#endif	// #ifdef OSD_SUPPORT_256_COLOR
}


void
osdv2_init_bitmap(UINT8 *hp, int color_format, int w, int h)
{
  int i, j;

  if (color_format==OSD_FORMAT_DIRECT16A || color_format==OSD_FORMAT_DIRECT16B)
  {
    for (i=0;i<h;i++)
	{
	  unsigned y, cr, cb;
	  static	unsigned	f;
	  f = 0xc0;
	  y		= i&0x7f;
	  cb	= 0x80;
	  cr	= 0x80;
//	  cb	= 0x80+y;
//	  cr	= 0x80-y;
      for (j=0;j<w;j++)
	  {
		unsigned v;
#if 1
		y	= (f++);
		v = (((cr>>3)&0x1f)<<11) | (((y>>2)&0x3f)<<5) | (((cb>>3)&0x1f)<<0) ;		// 565
		*(UINT16 *)(&hp[0]) = SWAP16(v);
		y	= (f++);
		v = (((cr>>3)&0x1f)<<11) | (((y>>2)&0x3f)<<5) | (((cb>>3)&0x1f)<<0) ;		// 565
		*(UINT16 *)(&hp[2]) = SWAP16(v);
		hp+=4;
#endif
	  }
	}
  }
  else
  {
    for (i=0;i<h;i++)
    {
      for (j=0;j<w;j++)
      {
        hp[0] = 2*j+0;
        hp[1] = 2*j+0;
        hp[2] = 2*j+1;
        hp[3] = 2*j+1;
        hp+=4;
      }
    }
  }
}



extern	const UINT8	* const	fn_8x16gbfs[];
#define	fnt_table	fn_8x16gbfs
#define COLOR_FG	255
#define COLOR_BG	1

void
osdv2_outtext(t_osd_region *p, char *str)
{
	int i, idx, wrap;
	int h, w;
	int x, y, ly;
	int keep;
	UINT8 *hp;
	const UINT8 *c_p;

    hp      = (UINT8 *)get_osdbuf_baseptr() + p->osd_header[0]*32;		// header address
	hp		= (UINT8 *)get_osdbuf_baseptr() + lbe16(hp+12)*32;			// bitmap address

	w		= p->osd_w * ppw_table[p->osd_format];
	h		= p->osd_h;
	for (ly=y=0; y<h;)
	{
	  int c;
	  idx = 0;
	  wrap = 0;
	  x = 0;
	  keep = 0;
	  for (idx=0;(c=str[idx])!=0;idx++)
	  {
		int c_l;
		int cw, ch;
		unsigned c_pattern;

		if (c=='\n') break;
		c_p = fnt_table[c];
		if (c_p==NULL) c_p = fnt_table[' '];
		if (c_p==NULL) break;
		cw = c_p[0];
		ch = c_p[1];
		c_p += 3 + c_p[2]*ly;
		c_l = 0;
		c_pattern = 0;
		for (i=cw;i>0;i--)
		{
		  if (c_l==0 && ch>=ly) {c_pattern=*c_p++;c_l+=8;keep=1;}
		  *hp++ = (((c_pattern<<1)>>c_l) & 0x01) ? COLOR_FG : COLOR_BG;
		  x++;
		  c_l--;
		  if (x>=w) goto line_end;
		}
	  }
line_end:
	  // fill leftovers
	  while (x<w) {*hp++ = COLOR_BG; x++;}
	  y++;
	  ly++;
	  if (!keep)
	  {
		while (1)
		{
		  c = str[0];
		  if (c=='\0') break;
		  str++;
		  if (c=='\n') break;
		}
		ly=0;
	  }
	}
}


//
// FUNCTION
// osdv2_create_region
//
void
osdv2_create_region(t_osd_region *p, int X, int Y, t_osd_region *prev, int bScanMode)
{
  int               oW, oH;
  t_osdv2_header    hdr;
  UINT16            lnkprev;
  UINT8             *hp;
  unsigned          clut_type;
  int				color_format;
  int               hdr_size;
  int               clut_entries;
  int               clut_size;
  unsigned			clut_update;

    if(bScanMode){}//wanghaoying 2003-8-12 16:59 added, maybe the parameter will use lately.
    
  lnkprev = (prev!=NULL) ? prev->osd_header[0] : LINK_NULL;

  p->osd_header[0] = osd_free;
  p->osd_header[1] = osd_free;
  
  oW			= p->osd_w;
  oH			= p->osd_h;
  color_format	= p->osd_format;

  clut_type		= OSDV2_CLUT_32b;

  hdr_size  = 16;

  clut_entries	= clut_entries_table[color_format];
  if (clut_type==OSDV2_CLUT_16b) clut_size = clut_entries*2;
  else clut_size = clut_entries*4;

  clut_update = (color_format==OSD_FORMAT_DIRECT16A || color_format==OSD_FORMAT_DIRECT16B) ? 0 : 1;
  clut_update = 1;

  hp        = (UINT8 *)get_osdbuf_baseptr() + (osd_free<<5);

  osd_free  = osd_free + ((hdr_size+clut_size+31)>>5);

  memset(&hdr,0,sizeof(hdr));

  hdr.config0   = ((clut_update & 0x01) << BIT_CU)
                | ((0) << BIT_FT)
                | ((3 & 0x03) << BIT_PR)
                | ((color_format & 0x07) << BIT_MD);
#if 0
  hdr.config0   = ((0x01 & 0x01) << BIT_CU)
                | ((0) << BIT_FT)
                | ((0 & 0x03) << BIT_PR)
                | ((color_format & 0x07) << BIT_MD);
#endif
  hdr.config1   = ((0x00 & 0x0f) << BIT_SHD)
                | ((0x0f & 0x0f) << BIT_BLND);
  hdr.config2   = V2_CLUT_TYPE(clut_type)
				| V2_SWAP_BYTE_OFF
				| V2_SHADE_MODE_A;
  hdr.v_size    = SWAP16(oH);
  hdr.h_size    = SWAP16(oW);
  hdr.x         = SWAP16(X);
  hdr.y         = SWAP16(Y);
  hdr.link_data = SWAP16(osd_free);
  hdr.link_next = SWAP16(lnkprev);

  memcpy(hp,&hdr,sizeof(hdr));

  // initialize clut
  hp		+= hdr_size;
  osdv2_init_clut(hp, clut_type);

  // initialize bitmap
  hp        = get_osdbuf_baseptr() + (osd_free<<5);
  osdv2_init_bitmap(hp, color_format, oW, oH);

  osd_free += oH*oW*4/32;
}

#endif
