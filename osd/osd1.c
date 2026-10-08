/*
** FILE
** osd1.c
**
** DESCRIPTION
** control OSD interface.
**
** Maintain by all
** History :
**      2003.03.10  terry  , check all function on disable osd mode
**      2003/9/26 03:38PM, terry,define osdbuf replacement linebuf when debug mode
**      2003-08-29 15:18, wangfeng For new setup menu
**      2005-1-18 8:48, wanghaoying moved some code about OP_UI to a file in the folder "higui"
** Note : all functions must make the same function name to osd2.c
**
*/

#include "config.h"
#include "regmap.h"
#include "global.h"

#include "memmap.h"
#include "func.h"
#include "stdlib.h"
#include "cfont.h"

#include "osd.h"
#include "osdsup.h"
#include "osdfont.h"
#include "osd_str.h"
#include "user_init.h"
#include "endian.h"
#include "user_if.h"


//#ifdef SPHE1000_DVDSTATE_CALLBACK
//#include "osd_1000isp.c"
//#else

#include "vpp.h"//opened by liudan 2004-11-17 16:45

#ifdef SOFT_MENU//Modifed by ChenZhao on 2004-9-6 21:47 WP
#include "kernel.h"
#include "setup_def.h"
#endif//SOFT_MENU

#ifdef NEWSTYLE_WINDOW      //xiongyuyue
#include "kernel.h"
#include "osd_arc.h"
#include "vpp.h"
#elif defined(SETUP_ADJUST_LOCATION_WHEN_PAL)
#include "kernel.h"
#endif

#ifdef ROLL_SHOW_SETUP  //zhaoyanhua add 2003-8-18 11:42
#include"memmap0.h"
#endif

#ifdef SUPPORT_REP_READ 
#include "read.h"
#endif

#ifdef  SUPPORT_MP4
#include "drm.h"
#endif

#ifdef SUPPORT_DISPLAY_MENU
#include "setup_def.h"
#endif

#ifdef  ALWAYS_DISPLAY_OPEN//Jack 20041008
#include "cd.h"
#endif

#if defined(DVB1000_OSD_MENU)||defined(DVB_MENU_TYPE1)  //sunzhh  20050430
#include "dvbmenu.h"
#endif

#ifdef HDMI
#include "hdmi_api.h"
#endif//NEW_HDMI_FLOW

#ifndef DVDRELEASE
//#define OSD_DBG         1
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

#ifdef DIV_GOTO_DISPLAY
extern BYTE  SearchPage;
#endif

#ifdef  NEW_STYLE_SETUP
#define SETUP_REGION    1
#else
#define SETUP_REGION    0
#endif

#if !defined(OSD_PAL_16b) || defined(OSD_16b_BUG)
#define OSD_CLUT_SIZE   4
#else
#define OSD_CLUT_SIZE   2
#endif

#ifdef SETUP_ON_OPEN_VALID      //dingzhy   12/26/2003 9:07PM
extern BYTE OpenFlag;
#endif

#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)    //axel 2004/1/27 04:48
#include "icon_bbk.h"
#endif

#ifdef  ZOOMOUT_JPEG_ROTATE_NOT_SHOW_ZOOM       //Maoyong 2004.02.25 for JPEG zoomout not show zoom 
#include "jpegeffect.h"

/*Maoyong 2004.02.25, when rotate to normal, we also can't show zoom state for a zoomout pic.
  So use old_rotate_mode to compare 'rotate_mode'
*/
BYTE old_rotate_mode = 0;

extern UINT16 Is_JPEG_STATE(void);
#endif

#ifdef OSD_DYNAMIC_ONOFF
/*xsyan 2004.04.18, SUNPLUS_DMA_DVD need switch OSD  between Linux and RomCode */
UINT8 OSD_Dynamic_onoff = 1;  //xsyan
#endif

//#ifdef NEWSTYLE_WINDOW             //xiongyuyue 
//xlluo modify for midiplayer draw menurect 04-6-11
#if (defined(NEWSTYLE_WINDOW)|defined(SUPPORT_MIDI_MENU_SEL))
/*
const BYTE arc_tableLT[16][16]={
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,1,1,1,2,2,2,2},
    {0,0,0,0,0,0,0,1,1,2,2,2,2,2,2,2},
    {0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2},
    {0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2},
    {0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2},
    {0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2},
    {0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};    
const BYTE arc_tableRT[16][16]=
{
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {2,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0},
    {2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0},
    {2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0},
    {2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0},
    {2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0},
    {2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},    
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},    
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},    
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1}    
};
const BYTE arc_tableLB[16][16]=
{
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2},
    {0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2},
    {0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2},
    {0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2},
    {0,0,0,0,0,0,0,1,1,2,2,2,2,2,2,2},
    {0,0,0,0,0,0,0,0,0,1,1,1,2,2,2,2},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1}
};
const BYTE arc_tableRB[16][16]=
{
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0},
    {2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0},
    {2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0},
    {2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0},
    {2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0},
    {2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0},
    {2,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0}
};
*/

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

/*        
const BYTE  arc_tableLT[6][6] = {
                        {0,0,0,0,1,1},
                                 {0,0,1,1,2,2},
                              {0,1,1,2,2,2},
                              {0,1,2,2,2,2},
                              {1,2,2,2,2,2},
                              {1,2,2,2,2,2},
                            };
const BYTE arc_tableRT[6][6] = {
                              {1,1,0,0,0,0},
                              {2,2,1,1,0,0},
                              {2,2,2,1,1,0},
                              {2,2,2,2,1,0},
                              {2,2,2,2,2,1},
                              {2,2,2,2,2,1},
                            };
const BYTE arc_tableLB[6][6] = {
                              {1,2,2,2,2,2},
                              {1,2,2,2,2,2},
                              {0,1,2,2,2,2},
                              {0,1,1,2,2,2},
                              {0,0,1,1,2,2},
                              {0,0,0,0,1,1},
                             };
const BYTE arc_tableRB[6][6] = {
                              {2,2,2,2,2,1},
                              {2,2,2,2,2,1},
                              {2,2,2,2,1,0},
                              {2,2,2,1,1,0},
                              {2,2,1,1,0,0},
                              {1,1,0,0,0,0},
                             };     */

/*
const BYTE Arrow_UP[6][6]=
{
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0}
};
const BYTE Arrow_DOWN[6][6]=
{
    {0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1},
    {0, 0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0}
};

const BYTE Arrow_Right[10][10]=
{
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
const BYTE Arrow_Left[10][10]=
{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
};

*/
#endif

/************************************************************\
Data
\************************************************************/
#include "osd_palette.h"


void    osd_DrawLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth);
void    osd_DrawRegionLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth, BYTE r);
void    osd_print_region2(t_osd_region *p, const char *s0, BYTE y_start,BYTE x_start);
void    osd_draw_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor);
void    osd_draw_region_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor, BYTE r);


extern  UINT8   decomp_fnTable[];
extern  UINT8   osd_temp_buf[];


#ifdef OP_IR//libing

void osd_draw_HL(BYTE r,UINT32 xStart, UINT32 yStart,UINT32 xLen,UINT32 yLen, int LineWidth,BYTE color)
{//libing 2005-1-27 10:04
	osd_draw_hline_region(xStart, xStart+xLen, yStart, color,LineWidth, r);
	osd_draw_hline_region(xStart, xStart+xLen, yStart+yLen-LineWidth, color,LineWidth, r);
	osd_draw_vline_region(xStart, yStart, yStart+yLen, color,LineWidth, r);
	osd_draw_vline_region(xStart+xLen-LineWidth, yStart, yStart+yLen, color,LineWidth, r);
}

#endif

//
// get_font_entry
//
const UINT8 *
get_font_entry(int tbl, int entry)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return 0;
#endif

    unsigned    u = 0;
    // Modified by yltseng. If no initial value 0, when this entry doesn't exist in all tables,
    // we will return what u contains( it may be any value ).
    // When we call this function, we need to check if the return value is NULL or not.

    if (tbl == 0)
        u = (unsigned) font_table[entry];
    else if (tbl == 1)
        u = (unsigned) font_table2[entry];
    else if (tbl == 2)
        u = (unsigned) setup_icon[entry];
#ifdef SUPPORT_PLAYBACK_ICON
    else
        u = (unsigned) play_icon[entry];
#endif

#ifdef OSD_FONT_COMPRESS            
    return (BYTE *)(decomp_fnTable + u);
#else
    return (BYTE *)u;
#endif
}


UINT8 *
get_osdbuf_region_ptr(int _region, int _field)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return 0;
#endif

    UINT8 *p = get_osdbuf_baseptr();
    p = p + (region[_region].osd_header[_field] + OSD_DATA_OFFSET(region[_region].osd_format))*32;
    return  p;
}


#if SUPPORT_OSD
//
// FUNCTION
// reset_osd
//
inline void osd_disable(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    regs0->osd_en    = 0;
}

inline void osd_enable(void)
{  
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif
  
#if(!defined(DVB_SETUP)||defined(SUPPORT_DVD_OSD))
    regs0->osd_en    = 1;
#endif
}


void
reset_osd()
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_disable();
    regs0->osd_tlink_addr = LINK_NULL;
    regs0->osd_blink_addr = LINK_NULL;
}


void
ENABLE_OSD(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

#if(!defined(DVB_SETUP)||defined(SUPPORT_DVD_OSD))
    regs0->osd_tlink_addr  = region[0].osd_header[0];
    regs0->osd_blink_addr  = region[0].osd_header[1];
    osd_enable();
#endif
}


void
DISABLE_OSD(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_disable(); 
    wait_v_blank();    //20020613 to avoid  noise when 3D_MENU  toggle .
    delay_1ms(10);  //caoh 05/08/02 aviod subtitle disable worng 
}


void   
__osd_init(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    int i;
    osd_free = addr_vxvy(0,0);
    header_id = NORMAL_HEADER;
    DISABLE_OSD();

    // reset OSD regions information
    for (i=0;i<MAX_REGION;i++) timeout_osd[i] = 0;
    osd_active_regions = 0;
}


void
osd_init__(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    ClearOsdMsg(0);
    ENABLE_OSD();        
}

//
// FUNCTION
// osd_init_regions
// initialize OSD regions using _t_osd_hdr table
//
void 
osd_init_regions(int n, const _t_osd_hdr *hdrp)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    int i, j;
    void *rgnp;

    __osd_init();        

    rgnp = NULL;
    for (i=0, j=n-1; i<n; i++, j--)
    {
        header_id       = hdrp[i].header_type;
        region[j].osd_w = hdrp[i].width;
        region[j].osd_h = hdrp[i].height;
        osd_create_region1(&region[j],
                hdrp[i].x,  hdrp[i].y,
                rgnp,
                hdrp[i].format,
                hdrp[i].type
        );
        rgnp = &region[j];
    }

    osd_active_regions = n;
    osd_init__();       
}



/***************************************************************
**Function: osd_init_cardswitch()
**Description: initialize the Switch interface.
**Create: wuxiaofeng, 2003-9-01 
***************************************************************/
/*const _t_osd_hdr  osd_cardswitch[] = {
    {64*3, (OSD_FONT_HEIGHT+8)*8, 80, 72, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},       // 3
    {64*3, (OSD_FONT_HEIGHT)*2, 80, 48, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},         // 2
    {36*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},             // 1
    {38*8, OSD_FONT_HEIGHT,   26, 16+4,      SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 0
};

void osd_init_cardswitch(void)
{
    osd_puts("osd_cardswitch()\n");
    osd_init_regions( sizeof(osd_cardswitch)/sizeof(osd_cardswitch[0]), (_t_osd_hdr *)&osd_cardswitch);
}
void osd_draw_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown, BYTE r)
{
        BYTE       buttonC;
        UINT32    xNew, yNew;
    BYTE    region;
    
        buttonC = color;
    region = r;
        xNew = xStart * 16;
        yNew = yStart * SETUP_BTN_HEIGHT+12;    
        osd_draw_region_rect(xNew, yNew, (UINT32)(xLen*16), (UINT32)(SETUP_BTN_HEIGHT), buttonC, region);    
        osd_draw_region_boarder(xNew, yNew, (UINT32)(xNew+xLen*16), (UINT32)(yNew+SETUP_BTN_HEIGHT-2), bDown, region);
}

#endif*/

#ifdef DVB_MENU_TYPE1    //sunzhh 20050430
const   _t_osd_hdr osd_hdr_dvb_menu[] = {
//    {38*8, OSD_FONT_HEIGHT*15, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    {38*8 + 20 , OSD_FONT_HEIGHT * 16, 10, 28, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 2
    //{36*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
    //{38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0

};

void osd_init_dvb_menu(void)
{

    osd_init_regions(sizeof(osd_hdr_dvb_menu)/sizeof(osd_hdr_dvb_menu[0]), (_t_osd_hdr *)&osd_hdr_dvb_menu);

    SetOsdCol(0, 0, 14, 0x0080fff0);
    SetOsdCol(0, 0, 8,  0xC8C8C8ff);
    SetOsdCol(0, 0, 0, 0x1e1e1e00);
}
#endif

#if defined(FAT_Write_UI)||defined(FILE_MODE_WRITE)//sunzhh 20041120
const   _t_osd_hdr osd_MediaswitchGUI[] = {
#ifdef DISP_REGION_BOTTOM
    {360, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
#endif
    #ifdef CARD_SETUP_TYPE_3 
    {64*2, (OSD_FONT_HEIGHT+8)*9, 50+65, 40, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 3      
    #else
    {64*2, (OSD_FONT_HEIGHT+8)*9, 50+65, 25, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 3
    #endif
    {64*3, (OSD_FONT_HEIGHT)*2,   80,    48, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 2
    {36*4, OSD_FONT_HEIGHT,       32,    34, NORMAL_HEADER,OSD_FORMAT_4COLOR,   OSD_INTERLACED},     // 1
#ifndef OSD_BMP_DISPLAY
    {38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#else
    {360, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#endif//OSD_BMP
};
void osd_init_MediaswitchGUI(void)
{
#ifdef SPHE1000_DVDSTATE_CALLBACK                     //2004/10/21 wjzhang , sphe1000B(stb-dvd): turn off the osd display in romcode
	return ;
#endif
    osd_puts("osd_init_key\n");
    osd_init_regions( sizeof(osd_MediaswitchGUI)/sizeof(osd_MediaswitchGUI[0]), (_t_osd_hdr *)&osd_MediaswitchGUI);
}
#endif//#if defined(FAT_Write_UI)//sunzhh 20041120

#if defined(CF_CARD_WRITE)||defined(FAT_Write_UI)||defined(FILE_MODE_WRITE)//liweihua add 2003-10-30 9:15
const   _t_osd_hdr osd_periphGUI[] = {
#ifdef DISP_REGION_BOTTOM
    {360, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
#endif
    {64*4, (OSD_FONT_HEIGHT+8)*9, 50, 72, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},       // 3
    {64*3, (OSD_FONT_HEIGHT)*2, 80, 48, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},         // 2
    {36*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},             // 1
#ifndef OSD_BMP_DISPLAY
    {38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#else
    {360, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#endif//OSD_BMP
};
void osd_init_periphGUI(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_puts("osd_init_key\n");
    osd_init_regions( sizeof(osd_periphGUI)/sizeof(osd_periphGUI[0]), (_t_osd_hdr *)&osd_periphGUI);
}
#endif
#ifdef SUPPORT_OSDID3//liweihua 2003-12-28
const   _t_osd_hdr osd_OSDID3[] = {
#ifdef DISP_REGION_BOTTOM
    {360, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
#endif
    {38*8, OSD_FONT_HEIGHT*5, 26, 134, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},  // 3//liweihua mod 2004-1-14 10:26
    {36*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2
    {36*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
#ifndef OSD_BMP_DISPLAY
    {38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#else
    {360, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#endif//OSD_BMP
};
void osd_init_OSDID3(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_puts("osd_init_key\n");
    osd_init_regions( sizeof(osd_OSDID3)/sizeof(osd_OSDID3[0]), (_t_osd_hdr *)&osd_OSDID3);
    SetOsdCol(3,3,0,__palette4F(85,125, 0, 0x80));
    SetOsdCol(3,3,2,__palette4F(255, 132, 255, 0xff));

}
#endif
#ifdef SWITCH_CD_CARD_USB //liweihua mod 2004-6-8 14:45
const   _t_osd_hdr osd_switchGUI[] = {
#ifdef DISP_REGION_BOTTOM
    {360, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
#endif
    {64*2, (OSD_FONT_HEIGHT+8)*9, 50+65, 72, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},    // 3
    {64*3, (OSD_FONT_HEIGHT)*2, 80, 48, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},         // 2
    {36*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},             // 1
#ifndef OSD_BMP_DISPLAY
    {38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#else
    {360, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#endif//OSD_BMP_DISPLAY
};
void osd_init_switchGUI(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_puts("osd_init_key\n");
    osd_init_regions( sizeof(osd_switchGUI)/sizeof(osd_switchGUI[0]), (_t_osd_hdr *)&osd_switchGUI);
}
#endif
//suqiaoli add 2004-3-17
// 2004/09/03 yltseng
#ifdef SUPPORT_OSDSRT
    #ifndef SDRAM_16Mb_Mode
        const   _t_osd_hdr osd_OSDSRT[] = {
#ifdef DISP_REGION_BOTTOM
    {360, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // last region for cdrom display region
#endif
            {38*8, (OSD_FONT_HEIGHT+10)*7, 26, 102, SETUP_HEADER, OSD_FORMAT_16COLOR,   OSD_INTERLACED},    // 3
#ifdef OSD_BMP_REGION1
    {36*4, OSD_FONT_HEIGHT, 32, 56, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},              // 2
    {40*4, OSD_FONT_HEIGHT + 8 , 0, 37, BMP_REGION1_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
#else
    {36*4, OSD_FONT_HEIGHT, 32, 56, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},              // 2
            {36*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},             // 1
#endif
#ifndef OSD_BMP_DISPLAY
            {38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}              // 0
#else
    {360, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#endif
        };
    #else
        const   _t_osd_hdr osd_OSDSRT[] = {

            {38*8, OSD_FONT_HEIGHT*2, 26, 182, SETUP_HEADER,  OSD_FORMAT_16COLOR,   OSD_INTERLACED},       // 3
            {36*4, OSD_FONT_HEIGHT,   32, 46,  SETUP_HEADER,  OSD_FORMAT_16COLOR,  OSD_INTERLACED},             // 2
            {18*4, OSD_FONT_HEIGHT,   32, 34,  NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},             // 1
        #ifdef  NEW_DISPLAY_GOTO_OSD
            {16*4, OSD_FONT_HEIGHT,   26, 20,  SETUP_HEADER,  OSD_FORMAT_4COLOR,  OSD_NONINTERLACED}           // 0
            // 0 Temporarily set the last para as non-interlace. wuxiaofeng 2004-06-02
        #else
            {38*4, OSD_FONT_HEIGHT,   26, 20,  SETUP_HEADER,  OSD_FORMAT_4COLOR,  OSD_INTERLACED}              // 0
        #endif
        };
    #endif
#ifdef OP_IR	//caoh 05/08/02
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
#endif   
void osd_init_OSDSRT(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    if( (full_scrn==0)||(full_scrn&GOTO)||(full_scrn&MARK)||(full_scrn&SCORE)////nono 4-7-26 10:37;
        ||(full_scrn&PROGRAM) ||(full_scrn&SOUND))//feeling 05-01-06
#if defined(DISP_REGION_BOTTOM) && defined(SUPPORT_FILE_SYSTEM_MODE)
	if(IsOtherStatePlayMode())
#endif
    {
    osd_puts("osd_init_key\n");
    osd_init_regions( sizeof(osd_OSDSRT)/sizeof(osd_OSDSRT[0]), (_t_osd_hdr *)&osd_OSDSRT);
	
//joshua, 20050720, modified for setup-menu flicking problem
/*
#ifdef MOVE_DOWN_SUBTITLE_WHEN_PAL//Move subtitle region down, because it is too high when PAL. yaowh add 2005-7-4 17:34
	if(getVPP_TVsystem())     
		MoveRegion(3,26,150);
	else
		MoveRegion(3,26,102);
#endif
*/
     #ifdef OP_IR	//caoh 05/08/02
     osd_move_subtitle_region();     // 2005/07/12 yltseng	
     #endif
SetOsdCol(3,3,0,__palette4F(30,30, 30, 0));//background color is transparent

#ifdef WHITE_MP4_SUBTITLE     //Liumzh  05/04/21
	SetOsdCol(3,3,2,__palette4F(255, 255, 255, 0xff));//white
#else
    SetOsdCol(3,3,2,__palette4F(255, 132, 255, 0xff));//font color is near to white
#endif
    }
}
#endif
//
// FUNCTION
// osd_init()
//
#ifndef SDRAM_16Mb_Mode
const   _t_osd_hdr osd_hdr_0[] = {
#if defined(LARGE_SCORES_DISPLAY)//&& defined(GBM_DVD)
    {24*4, (OSD_FONT_HEIGHT)*6, 120, 80, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 3
#endif

#ifdef DIV_GOTO_DISPLAY    
    {36*5+16, OSD_FONT_HEIGHT+6, 32, 46, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 2//{36*4, OSD_FONT_HEIGHT*2, 32, 46+6, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2
#else
#ifdef SUPPORT_GPIO_P_SCAN
     {36*3, OSD_FONT_HEIGHT, 80, 46+OSD_FONT_HEIGHT+12+64+24+12, SETUP_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 7
    {36*3, OSD_FONT_HEIGHT, 80, 46+OSD_FONT_HEIGHT+12+64+24, SETUP_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 6
    {36*3, OSD_FONT_HEIGHT, 80, 46+OSD_FONT_HEIGHT+64+24, SETUP_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 5
    {36*3, OSD_FONT_HEIGHT, 80, 46+OSD_FONT_HEIGHT+12+64, SETUP_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 4
    {36*3, OSD_FONT_HEIGHT, 80, 46+OSD_FONT_HEIGHT+64, SETUP_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 3
#endif //#ifdef SUPPORT_GPIO_P_SCAN
    //{36*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2     //mark by liudan,2004-11-16 14:38
#endif//DIV_GOTO_DISPLAY   
#ifdef DISP_REGION_BOTTOM
    {360, OSD_FONT_HEIGHT + 8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},      // 3 for cdrom display
#ifdef SUPPORT_MP4
    {38*8, OSD_FONT_HEIGHT * 6, 26, 134,    SETUP_HEADER,   OSD_FORMAT_16COLOR, OSD_NONINTERLACED},    // 3 for mp4 subtitle
#endif
    {36*4, OSD_FONT_HEIGHT + 8, 0, 56, BMP_REGION1_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2     //liudan add it,2004-11-17 11:07

#else    
    {36*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2     //liudan add it,2004-11-17 11:07
#endif

#ifdef OSD_BMP_REGION1//libing modify 36*4=>>40*4  2004-11-26 21:19
    {40*4, OSD_FONT_HEIGHT + 8 , 0, 37, BMP_REGION1_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
#else
    {36*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
#endif

#ifndef OSD_BMP_DISPLAY
    {38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#else
    {360, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#endif//OSD_BMP
};
#else
// 16Mb small-memory mode
const   _t_osd_hdr osd_hdr_0[] = {
    // 2004/11/26 yltseng add region2, in order to show ANGLE
#ifdef ORITRON_HK_DVD//libing 2005-5-26 11:39 for oritron_dvd becuase 8202D has enough osd buf    
	{18*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},      // 2
	{24*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
#else	
    {4*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},      // 2
    {18*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
#endif
#ifdef  NEW_DISPLAY_GOTO_OSD
    {16*4, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_4COLOR,  OSD_NONINTERLACED}      // 
    // 0 Temporarily set the last para as non-interlace. wuxiaofeng 2004-06-02
#else
    {38*4, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_4COLOR,  OSD_INTERLACED}      // 0
#endif
};
#endif


void    osd_init(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_puts("osd_init()\n");
    osd_init_regions( sizeof(osd_hdr_0)/sizeof(osd_hdr_0[0]), (_t_osd_hdr *)&osd_hdr_0);

#ifdef DIV_GOTO_DISPLAY//zhaoyanhua add 03-10-22 13:17
    SetOsdCol(2,2,0,0x1e1e1e00);//region 2 transent.
    SetOsdCol(2,2,10,0x32323290);//REGION2 10 is black. Be same with REIGON1 black color.
    #ifdef NINTAUS_OSD_STR    //2004-2-17 01:31张宇M
    SetOsdCol(2,2,7,0xffffffff);
    #else
    SetOsdCol(2,2,7, 0xa22c8eff);//REGION2 7 is yellow. Be same with REGION1 yellow color. zhaoyanhua add 2003-12-24 11:07
    #endif//SetOsdCol(2,2,7,0x1e1e1ea0);
#endif//end DIV_GOTO_DISPLAY
}


#ifdef  RECORD_KEY//zhaoyanhua add 
const   _t_osd_hdr osd_hdr_record[] = {
#ifdef DISP_REGION_BOTTOM
    {360, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
#endif

#ifndef OSD_BMP_DISPLAY
    {38*8, OSD_FONT_HEIGHT*4, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR,  OSD_INTERLACED}      // 0
#else
    {360, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#endif//OSD_BMP
};


/*
 * Function Description:
 *    when the disc which has been recorded is distinguished,
 *    before resume play ,show message.
 */
void osd_init_record()
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_puts("osd_init_record()\n");
    osd_init_regions( sizeof(osd_hdr_record)/sizeof(osd_hdr_record[0]), (_t_osd_hdr *)&osd_hdr_record);
    //osd_draw_region_rect(0, 0, 20, 14, 6, 1);
       SetOsdCol(0,0,0,0x1e1e1ef0);//3-11-21 9:25张宇P
}   
#endif




//
// FUNCTION
// osd_init_prog()
//
const   _t_osd_hdr osd_hdr_prog[] = {

#ifdef DISP_REGION_BOTTOM
    {360, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // last region, for cdrom display region
	#endif

#ifdef OSD_BMP_PROG

    {37*8, 20,  31, 37+7+17+6+131,  BMP_REGION_F_HEADER,  OSD_FORMAT_16COLOR,	OSD_INTERLACED},  	// 5
    {37*8, 262, 31, 37+7+17+6,      BMP_REGION_E_HEADER,  OSD_FORMAT_16COLOR,	OSD_INTERLACED},  	// 4
    {37*8, 12,  31, 37+7+17,        BMP_REGION_D_HEADER,  OSD_FORMAT_16COLOR,	OSD_INTERLACED},  	// 3
    {37*8, 34,  31, 37+7,           BMP_REGION_B_HEADER,  OSD_FORMAT_16COLOR,  	OSD_INTERLACED},    // 2
    {37*8, 14,  31, 37,             BMP_REGION_A_HEADER,  OSD_FORMAT_16COLOR,  	OSD_INTERLACED},    // 1
#else    
    {36*4, OSD_FONT_HEIGHT+8, 32, 150+4+4+4, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 7
    {36*4, OSD_FONT_HEIGHT*2, 32, 126+4+4+4, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 6
    {36*4, OSD_FONT_HEIGHT*2, 32, 102+4+4+4, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 5
    {36*4, OSD_FONT_HEIGHT*2, 32, 78+4+4+4,  NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 4
    {36*4, OSD_FONT_HEIGHT*2, 32, 54+4+4+4,  NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 3
    {36*4, OSD_FONT_HEIGHT+8, 32, 42+4+4,    NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 2
    {5*4,  OSD_FONT_HEIGHT+8, 32, 30+4,      NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 1
#endif

#ifdef SDRAM_16Mb_Mode//terry,2003/12/10 03:34PM
    {38*4, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_4COLOR,  OSD_INTERLACED}      // 0
#elif defined(OSD_BMP_DISPLAY)
	    {360, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#else
	    {38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#endif//#ifdef SDRAM_16Mb_Mode
};

void osd_init_prog(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_puts("osd_init_prog()\n");
    osd_init_regions( sizeof(osd_hdr_prog)/sizeof(osd_hdr_prog[0]), (_t_osd_hdr *)&osd_hdr_prog);

#ifdef CD_PLAYER        //liweihua add 2003-9-11
if(cd_type_loaded == CDDA)
    {
        SetOsdCol(0,0,0,0x1e1e1e00);
        SetOsdCol(0,0,5,__palette4F(128,64,255,0xff));
        SetOsdCol(0,0,8,__palette4F(128,255,0,0xff));
        SetOsdCol(0,0,9,__palette4F(128,255,0,0xff));
    }
#endif
}

#ifdef ORITRON_TRAY_PASSWORD//libing 2005-4-25 10:06
/*
const   _t_osd_hdr osd_hdr_op_psd[] = {
	
	{32*8, OSD_FONT_HEIGHT+14, 20, 49, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},      // 3
	//{36*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2
    //{36*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
    //{38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
};*/
void osd_init_tray_password(void)
{
	//osd_init_regions( sizeof(osd_hdr_op_psd)/sizeof(osd_hdr_op_psd[0]), (_t_osd_hdr *)&osd_hdr_op_psd);
	__osd_init();
	
	header_id = SETUP_HEADER;
	region[0].osd_w = 28*8;
	region[0].osd_h = OSD_FONT_HEIGHT+14;
	osd_create_region1(&region[0], 36, 40, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
	
	osd_active_regions=1;
	//osd_init__();
	ENABLE_OSD();
		
}
#endif

//
// FUNCTION
// osd_init_music
// 
// DESCRIPTION
// initialize (3dsound)osd-printing function
//
const   _t_osd_hdr osd_hdr_music[] = {

#ifdef DISP_REGION_BOTTOM
    {360, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},      // 6 for cdrom display
#endif

#ifdef OSD_BMP_SOUND
	{288, 20,  35, 58+7+17 +6+107, BMP_REGION_F_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 5, used as bmp sound region E
	{288, 214, 35, 58+7+17 +6,     BMP_REGION_E_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 4 ,used as bmp sound region D
	{288, 12,  35, 58+7+17,        BMP_REGION_D_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 3 ,used as bmp sound region C
	{288, 34,  35, 58+7,           BMP_REGION_B_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 2 ,used as bmp sound region B
	{288, 14,  35, 58,             BMP_REGION_A_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 1 ,used as bmp sound region A
#else//OSD_BMP_SOUND   
#ifdef  DYNAMIC_SPECTRUM  //fengjl   add 3-11-30 17:34
    {29*8,(OSD_FONT_HEIGHT+8)*7,64,  110,SETUP_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 3
#else
    {29*8,(OSD_FONT_HEIGHT+8)*7,64,  64+4,SETUP_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 3
#endif
#if  (defined DIV_GOTO_DISPLAY) && (defined BBK_DVD) //zhaoyanhua add 2003-11-10 11:52  
    {36*5+16, OSD_FONT_HEIGHT+6, 32, 46, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},        // 2
#else
    {29*8,OSD_FONT_HEIGHT+12,   64,  46+4,SETUP_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 2
#endif
#ifdef OSD_BMP_REGION1//libing modify 36*4=>>40*4 2004-11-26 21:19
    {40*4, OSD_FONT_HEIGHT + 8 , 0, 37, BMP_REGION1_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
#else
    {36*4,OSD_FONT_HEIGHT,      32,  34,  NORMAL_HEADER,OSD_FORMAT_4COLOR,OSD_INTERLACED},  // 1
#endif
#endif//OSD_BMP_SOUND
#ifndef OSD_BMP_DISPLAY
    {38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#else
    {360, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#endif//OSD_BMP
};

void
osd_init_music(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_puts("osd_init_music\n");
    osd_init_regions( sizeof(osd_hdr_music)/sizeof(osd_hdr_music[0]), (_t_osd_hdr *)&osd_hdr_music);

#ifdef DIV_GOTO_DISPLAY//zhaoyanhua add 03-10-22 13:17
    SetOsdCol(2,2,0,0x1e1e1e00);//region 2 transent.
    SetOsdCol(2,2,10,0x1e1e1ee0);
    //SetOsdCol(0,0,0,0x1e1e1ea0);
#endif//end DIV_GOTO_DISPLAY

    #ifdef CD_PLAYER    //liweihua add 2003-9-11
    if(cd_type_loaded == CDDA)
        {
            SetOsdCol(0,1,0,0x1e1e1e00);
            SetOsdCol(1,1,3,__palette4F(128,255,0,0xff));
            SetOsdCol(0,0,5,__palette4F(128,64,255,0xff));
            SetOsdCol(0,0,8,__palette4F(128,255,0,0xff));
            SetOsdCol(0,0,9,__palette4F(128,255,0,0xff));
        }
    #endif
}

#ifdef OP_PLAYMODE//libing
#ifndef SDRAM_16Mb_Mode
const   _t_osd_hdr osd_hdr_menu[] = {
	//{30*8, 6*OSD_FONT_HEIGHT, 62, 40, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},  // 3
	{30*8, 4*OSD_FONT_HEIGHT+60, 50, 60, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},		// 3
	{36*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2
	{36*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},  // 1
	{38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
};
#else
const   _t_osd_hdr osd_hdr_menu[] = {
	
	{28*8, 5*OSD_FONT_HEIGHT-8, 78, 40, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_NONINTERLACED},  // 1	
	{38*4, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_4COLOR,  OSD_INTERLACED}      // 0
};	
#endif

void 
osd_init_menu(void)//libing
{
	//osd_puts("osd_init_menu\n");
	osd_init_regions( sizeof(osd_hdr_menu)/sizeof(osd_hdr_menu[0]), (_t_osd_hdr *)&osd_hdr_menu);
}

#endif//OP_PLAYMODE
/*******************************************************
for op region UI,switch region code.
*******************************************************/
#ifdef SUPPORT_OP_REGION_UI//libing 2005-8-23 17:45
const   _t_osd_hdr osd_hdr_region_code[] = {
	{30*8,OSD_FONT_HEIGHT+14, 36, 40, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED} //0
};		

void 
Osd_Init_Op_Region()
{
	osd_init_regions( sizeof(osd_hdr_region_code)/sizeof(osd_hdr_region_code[0]),(_t_osd_hdr *)&osd_hdr_region_code );
}
#endif

#ifdef DOUBLE_TITLE //susu add 2003-8-20 14:43

const   _t_osd_hdr osd_hdr_double_title[] = {
#ifdef DISP_REGION_BOTTOM
    {360, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
#endif

    {36*4*2,OSD_FONT_HEIGHT+5,32,34,  SETUP_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 1

#ifndef OSD_BMP_DISPLAY
    {38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#else
    {360, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#endif//OSD_BMP


};

void osd_init_double_title(void)
{
    osd_puts("osd_init_double_title\n");
    osd_init_regions( sizeof(osd_hdr_double_title)/sizeof(osd_hdr_double_title[0]), (_t_osd_hdr *)&osd_hdr_double_title);
    
}
#endif

#ifndef NES_USE_GRAPH
#ifdef OSD_PAL_RGB_16b                
void osd_init_NES(int x,int y,int w,int h, const UINT16 *pPalette)
#else
void osd_init_NES(int x,int y,int w,int h, const UINT32 *pPalette)
#endif
{    
    osd_puts("osd_init_nes\n");
    __osd_init();

    header_id = NES_HEADER;
    osd__pal[header_id] = pPalette;
    
    //setup region 1    
    region[1].osd_w = w;        
    region[1].osd_h = h;    
    osd_create_region1(&region[1], x, y, NULL, OSD_FORMAT_256COLOR, OSD_NONINTERLACED);
    
    //setup region 0    
    region[0].osd_w = w;        
    region[0].osd_h = h;    
    osd_create_region1(&region[0], x, y, &region[1], OSD_FORMAT_256COLOR, OSD_NONINTERLACED);
        
    osd_active_regions = 2;
    ENABLE_OSD();    
}
#endif

#ifdef CD_PLAYER//liweihua 2003-9-3
void osd_init_cdplayer(void)
{
    __osd_init();

    #ifdef VIRTUAL_KEYBOARD
    header_id = KEYBOARD_HEADER;
    region[4].osd_w = 64*3;
    region[4].osd_h = (OSD_FONT_HEIGHT+8)*6;
    osd_create_region1(&region[4], 256, 168, NULL,OSD_FORMAT_256COLOR,OSD_INTERLACED);
    #endif
    
    //setup region 2(for cd player setting)
    header_id = EQ_HEADER;
    region[3].osd_w = 38*4-44;
    region[3].osd_h = (OSD_FONT_HEIGHT+8)*6;
    osd_create_region1(&region[3], 32+60+37,  72, &region[4],OSD_FORMAT_16COLOR,OSD_INTERLACED);

    //region2   
    header_id = NORMAL_HEADER;
    region[2].osd_w = 36*4;
    region[2].osd_h = OSD_FONT_HEIGHT;
    osd_create_region1(&region[2], 32,  42+4, &region[3],OSD_FORMAT_4COLOR,OSD_INTERLACED);

   // setup region 1
    header_id = NORMAL_HEADER;
    region[1].osd_w = 36*4;
    region[1].osd_h = OSD_FONT_HEIGHT;
    osd_create_region1(&region[1], 32,  34, &region[2],OSD_FORMAT_4COLOR,OSD_INTERLACED);
    SetOsdCol(1,1,3,__palette4F(128,255,0,0xff));
        
    // setup region 0
    header_id = SETUP_HEADER;
    region[0].osd_w = 38*8;
    region[0].osd_h = OSD_FONT_HEIGHT;
    osd_create_region1(&region[0], 24+2,  20, &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);
    SetOsdCol(0,4,0,0x1e1e1e00);
    SetOsdCol(0,0,5,__palette4F(128,64,255,0xff));
    SetOsdCol(0,0,8,__palette4F(128,255,0,0xff));
    SetOsdCol(0,0,9,__palette4F(128,255,0,0xff));
    
    osd_init__();  
}
#endif

#ifdef VIRTUAL_KEYBOARD //liweihua add 03-8-15
const   _t_osd_hdr osd_keyboard[] = {
#ifdef DISP_REGION_BOTTOM
    {360, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
#endif

    //{64*3, (OSD_FONT_HEIGHT+8)*6,256,168, KEYBOARD_HEADER, OSD_FORMAT_256COLOR,OSD_INTERLACED},  // 4
    #ifdef  NINTAUS_DVD //Maoyong 2004.03.11
    {160, 140,256,154, KEYBOARD_HEADER, OSD_FORMAT_256COLOR,OSD_INTERLACED},  // 4//20040225
    #else
    {160, 140,256,168, KEYBOARD_HEADER, OSD_FORMAT_256COLOR,OSD_INTERLACED},  // 4//20040225
    #endif
    #ifdef CD_PLAYER
    {38*4-44,(OSD_FONT_HEIGHT+8)*6,32+60+37,72, EQ_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED},  // 3
    #endif
    {36*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2
    {36*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
#ifndef OSD_BMP_DISPLAY
    {38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#else
    {360, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#endif//OSD_BMP
};
void osd_init_keyboard(void)
{
    osd_puts("osd_init_key\n");
    osd_init_regions( sizeof(osd_keyboard)/sizeof(osd_keyboard[0]), (_t_osd_hdr *)&osd_keyboard);
    #ifdef CD_PLAYER
    SetOsdCol(4,4,0,0x1e1e1e00);
    #else
    SetOsdCol(3,3,0,0x1e1e1e00);
    #endif
}
#endif

#ifdef PMP_UI//liweihua 204-12-28
const   _t_osd_hdr osd_pmp[] = {

	{38*8,(OSD_FONT_HEIGHT+8)*11,32,46, EQ_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED},  // 3//liweihua mod 2005-3-16
    // 2
    {36*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
#ifndef OSD_BMP
    {38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#else
    {360, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#endif//OSD_BMP    
};

void osd_init_pmp(void)
{
	osd_puts("osd_init_pmp\n");
    osd_init_regions( sizeof(osd_pmp)/sizeof(osd_pmp[0]), (_t_osd_hdr *)&osd_pmp); 
    SetOsdCol(2,2,0,0x1e1e1e00);   
}
#endif

#ifdef REALCOLOR_SCREENSAVER
const   _t_osd_hdr osd_screensaver[] = {
    {60*3, (OSD_FONT_HEIGHT+9)*6,2,2, SCREENSAVER_HEADER, OSD_FORMAT_256COLOR,OSD_INTERLACED},  // 1
};
void osd_init_screensaver(void)
{
    osd_puts("osd_init_key\n");
    osd_init_regions( sizeof(osd_screensaver)/sizeof(osd_screensaver[0]), (_t_osd_hdr *)&osd_screensaver);
    SetOsdCol(0,0,0,0x000ff);
}
#endif

/*
* Draw BMP on osd region r with 256 colors.
* The bmp image data and platte was made by image processing software.
*/
void osd_draw_256color_bmp(int xStart, int yStart, const BYTE* bmp, BYTE r)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    //BYTE    *pIcon;
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
}


#ifdef NEW_PARENTAL_GUI//zhaoyanhua add for BBK DVD 2003-11-28 10:49

const   _t_osd_hdr osd_hdr_parental[] = {
 //  {38*8, OSD_FONT_HEIGHT*4, 32,46 , SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED} ,     // 2
   //{36*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
   {38*6, OSD_FONT_HEIGHT*6, 80, 67, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
};

void osd_init_parental_gui(void)
{
    osd_init_regions( sizeof(osd_hdr_parental)/sizeof(osd_hdr_parental[0]), (_t_osd_hdr *)&osd_hdr_parental);
   
}
#endif

/*  freyman marked 2004-3-23 15:11 for no use
#ifdef SVA_SAMPLE
//
// FUNCTION
// osd_init_ampvol
// 
// DESCRIPTION
// initialize (3dsound)osd-printing function
//
void osd_init_ampvol(void)
{
    osd_puts("osd_init_ampvol\n");
    __osd_init();    

    // setup region 7
    region[7].osd_w = 36*4;
    region[7].osd_h = OSD_FONT_HEIGHT+5;
    osd_create_region1(&region[7], 65,  114+4+40, NULL,OSD_FORMAT_4COLOR,OSD_INTERLACED);
    
    // setup region 6
    region[6].osd_w = 36*4;
    region[6].osd_h = OSD_FONT_HEIGHT+5;
    osd_create_region1(&region[6], 65,  100+4+40, &region[7],OSD_FORMAT_4COLOR,OSD_INTERLACED);
    
    // setup region 5
    region[5].osd_w = 36*4;
    region[5].osd_h = OSD_FONT_HEIGHT+5;
    osd_create_region1(&region[5], 65,  86+4+40, &region[6],OSD_FORMAT_4COLOR,OSD_INTERLACED);
    
    // setup region 4
    region[4].osd_w = 36*4;
    region[4].osd_h = OSD_FONT_HEIGHT+5;
    osd_create_region1(&region[4], 65,  72+4+40, &region[5],OSD_FORMAT_4COLOR,OSD_INTERLACED);
    
    // setup region 3
    region[3].osd_w = 36*4;
    region[3].osd_h = OSD_FONT_HEIGHT+5;
    osd_create_region1(&region[3], 65,  58+4+40, &region[4],OSD_FORMAT_4COLOR,OSD_INTERLACED);
    
    // setup region 2
    region[2].osd_w = 36*4;
    region[2].osd_h = OSD_FONT_HEIGHT+5;
    osd_create_region1(&region[2], 65,  44+4+40, &region[3],OSD_FORMAT_4COLOR,OSD_INTERLACED);
    
    // setup region 1
    region[1].osd_w = 36*4;
    region[1].osd_h = OSD_FONT_HEIGHT+5;
    osd_create_region1(&region[1], 65,  30+4+40, &region[2],OSD_FORMAT_4COLOR,OSD_INTERLACED);
    
    // setup region 0
    header_id = SETUP_HEADER
    region[0].osd_w = 38*8;
    region[0].osd_h = 1*(OSD_FONT_HEIGHT+2);
    osd_create_region1(&region[0], 26,  16+4, &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);//nono 2-3-11 14:03 for yuxing
    
    osd_active_regions = 8;
    osd_init__();
}
#endif//SVA_SAMPLE
*/


//zhaoyanhua add this function to set NEW osd region for NEW_STYLE SETUP. 3-7-14 17:35
#ifdef NEW_STYLE_SETUP
void    osd_init_hand_ICON_for_NTSC(void)//NTSC
{
    osd_puts("osd_init_hand_ICON\n");
    __osd_init();

   #if 0
    //region 2
    header_id = SETUP_HEADER;
    region[2].osd_w = 160;//64;//40-8;                  //35 English Characters
    region[2].osd_h = 80;//40+14;//12 lines
    osd_create_region1(&region[2], 30, 210,  NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
    //SetOsdCol(2,2,0,0x1e1e1e00);//Initial color index is 0,but not transparent. zhaoyanhua 3-7-11 13:41
   // osd_tog_region(2,OSD_OFF);
    #endif
    //setup menu
    header_id = SETUP_HEADER;
    region[1].osd_w = 38*8;//22*8;                  //35 English Characters
    region[1].osd_h = 11*SETUP_BTN_HEIGHT;//9*SETUP_BTN_HEIGHT+24 ;//9*SETUP_BTN_HEIGHT;//7*SETUP_BTN_HEIGHT;//6*SETUP_BTN_HEIGHT+8;   //12 lines
    osd_create_region1(&region[1], 26/*110,115*/, 62/*50*/, NULL,OSD_FORMAT_16COLOR, OSD_INTERLACED);//60//54
    SetOsdCol(1,1,0,0x1e1e1e00);//Initial color index is 0,but not transparent. zhaoyanhua 3-7-11 13:41
    //osd_tog_region(1,OSD_OFF);

    //region 0
    header_id = SETUP_HEADER;
    region[0].osd_w = 160;//64;//40-8;                  //35 English Characters
    region[0].osd_h = 76;//40+14;//12 lines
    osd_create_region1(&region[0], 130,  24, &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);
    SetOsdCol(0,0,0,0x1e1e1e00);//Initial color index is 0,but not transparent. zhaoyanhua 3-7-11 13:41
    osd_tog_region(0,OSD_OFF);

    osd_active_regions = 2;
    osd_init__();
//  ENABLE_OSD();
}

void    osd_init_hand_ICON_for_PAL(void)//for PAL
{
    __osd_init();

   
    //setup menu
    header_id = SETUP_HEADER;
    region[1].osd_w = 38*8;//22*8;                  //35 English Characters
//gerry for DVD disc,maybe need test,2003-12-31 18:06
//    region[1].osd_h = 13*SETUP_BTN_HEIGHT+10;//9*SETUP_BTN_HEIGHT+24 ;//9*SETUP_BTN_HEIGHT;//7*SETUP_BTN_HEIGHT;//6*SETUP_BTN_HEIGHT+8;   //12 lines
    region[1].osd_h = 11*SETUP_BTN_HEIGHT;

    osd_create_region1(&region[1], 26/*110,115*/, 78-2-2/*50*/, NULL,OSD_FORMAT_16COLOR, OSD_INTERLACED);//60//54//nono 20030804
    SetOsdCol(1,1,0,0x1e1e1e00);//Initial color index is 0,but not transparent. zhaoyanhua 3-7-11 13:41
    //osd_tog_region(1,OSD_OFF);

    //region 0
    header_id = SETUP_HEADER;
    region[0].osd_w = 160;//64;//40-8;                  //35 English Characters
    region[0].osd_h = 76;//40+14;//12 lines
    osd_create_region1(&region[0], 130,  35-5, &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);//nono 20030804
    SetOsdCol(0,0,0,0x1e1e1e00);//Initial color index is 0,but not transparent. zhaoyanhua 3-7-11 13:41
    osd_tog_region(0,OSD_OFF);

    osd_active_regions = 2;
    osd_init__();
//  ENABLE_OSD();
}


void
osd_init_setup(void)
{
    osd_puts("osd_init_setup\n");
    __osd_init();
    
    header_id = SETUP_HEADER;
    
    region[1].osd_w = 35*8;                  //35 English Characters
    region[1].osd_h = 12*SETUP_BTN_HEIGHT;   //12 lines
    #ifdef SETUP_ADJUST_LOCATION_WHEN_PAL
    if(tv_format==MODE_PAL)                  //lizhx       2004/05/21
            osd_create_region1(&region[1], 45,  (23+22), NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
    else
    #endif
    osd_create_region1(&region[1], 45,  23, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
    SetOsdCol(1,1,0,0x1e1e1e00);//Initial color index is 0,but not transparent. zhaoyanhua 3-7-11 13:41
    
    region[0].osd_w = 8;                  //35 English Characters
    region[0].osd_h = 8+4;   //12 lines
     #ifdef SETUP_ADJUST_LOCATION_WHEN_PAL
    if(tv_format==MODE_PAL)                  //lizhx       2004/05/21
            osd_create_region1(&region[0], 38,  (2+22), &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);
    else
    #endif
            osd_create_region1(&region[0], 38,  2,&region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);
    osd_tog_region(0,OSD_OFF);
    
    osd_active_regions = 2;
    ENABLE_OSD();
}


#elif defined(SOFT_MENU)//Modifed by ChenZhao on 2004-9-2 14:23 WP
void
osd_init_setup(void)
{
	UINT16 screen_h,screen_w;
    osd_puts("osd_init_setup\n");
    __osd_init();

    header_id = SETUP_HEADER;
    region[SETUP_REGION].osd_w = SETUP_REGION_WIDTH;    //35 English Characters
    region[SETUP_REGION].osd_h = SETUP_REGION_HEIGHT;   //12 lines
    if(getVPP_TVsystem())//(TV_FORMAT_PAL==tv_format)//Modifed by chenzhao on 2004-11-16 24:50   
    	{
    	screen_h=288;
		screen_w=352;
    	}
	else
		{
		screen_h=240;
		screen_w=360;//Modifed by chenzhao on 2004-11-16 24:55   
		}
    osd_create_region1(&region[SETUP_REGION],(screen_w-SETUP_REGION_WIDTH)/2,(screen_h-SETUP_REGION_HEIGHT/2)/2, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
    //osd_create_region1(&region[SETUP_REGION], SETUP_REGION_X,  SETUP_REGION_Y, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
	osd_draw_rect(0,0,SETUP_REGION_WIDTH<<1,SETUP_REGION_HEIGHT,SETUP_BGCOLOR);
		osd_active_regions = 1;
		ENABLE_OSD();
	}
#else

// for supporting 16_bit OSD
#ifdef SUPPORT_16BIT_OSD
#include "OSD_16BDC.c"
#endif


void
osd_init_setup(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_puts("osd_init_setup\n");
    __osd_init();

#ifdef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-5 9:46
    header_id = QSI_SETUP_HEADER;
#else
    header_id = SETUP_HEADER;
#endif
#ifdef NEW_SETUP_OSD         // majinping 2002-05-02 for new setup menu
    region[0].osd_w = 37*8;                  //35 English Characters    
    region[0].osd_h = 13*SETUP_BTN_HEIGHT;   //13 lines
    #ifdef SETUP_ADJUST_LOCATION_WHEN_PAL
    if(tv_format==MODE_PAL) 
       osd_create_region1(&region[0], 30, (15+22), NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);    
    else
    #endif
    osd_create_region1(&region[0], 30, 15, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);    
#else    
    #ifdef SUPPORT_FUNCTION_MENU
    #ifdef SUPPORT_DISPLAY_MENU
    if(In_Display_Menu())
    {
      region[0].osd_w = 20*8;                 //15 English Characters
      region[0].osd_h = 10*SETUP_BTN_HEIGHT;   //9 lines
      osd_create_region1(&region[0], 38,  32, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
    }
    else
    #endif
    if(full_scrn&SETUP_PLUS)
    {
      region[0].osd_w = 32*8;                 //32 English Characters
      region[0].osd_h = 6*SETUP_BTN_HEIGHT;   //5 lines
      osd_create_region1(&region[0], 38,  32, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
    }
    else
    {
    #endif
    region[0].osd_w = 35*8;                  //35 English Characters
    region[0].osd_h = 12*SETUP_BTN_HEIGHT;   //12 lines
    #ifdef SETUP_ADJUST_LOCATION_WHEN_PAL
    if(tv_format==MODE_PAL)                  //lizhx       2004/05/21
       osd_create_region1(&region[0], 38,  (24+22), NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
    else
    #endif
    osd_create_region1(&region[0], 38,  24, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
    #ifdef SUPPORT_FUNCTION_MENU
    }
    #endif //end #ifdef SUPPORT_FUNCTION_MENU
#endif 

    osd_active_regions = 1;
    ENABLE_OSD();
}

#endif //end NEW_STYLE_SETUP

//fengjl add for bbk's new setup 3-11-10 16:57
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)       
void osd_init_bbk_setup(void)  
{   
    #define SETUP_HL_COLOR      5
    
    osd_puts("osd_init_setup\n");
    __osd_init();    
   
    header_id =SETUP_HEADER;
    region[1].osd_w = 32*8;                  //33 English Characters
    region[1].osd_h = 6*SETUP_BTN_HEIGHT;   //6 lines

    osd_create_region1(&region[1], 53, 4*SETUP_BTN_HEIGHT-9, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
    //SetOsdCol(1,1,0,0x1e1e1ef0);//black zhaoyanhua add 2003-12-2 14:21 
     SetOsdCol(1,1,0,0x757575f0);
    SetOsdCol(1,1,SETUP_HL_COLOR,0xa346ffff);
    //SetOsdCol(1,1,0,0x1e1e1ecd);//Initial color index is 0,but not transparent. zhaoyanhua 3-7-11 13:41
    
    header_id =BBK_SETUP_256HEADER;
    region[0].osd_w = 32*16;                  //33 English Characters
    region[0].osd_h = 5*SETUP_BTN_HEIGHT;   //6 lines
    osd_create_region1(&region[0], 53, 1*SETUP_BTN_HEIGHT+10, &region[1], OSD_FORMAT_256COLOR, OSD_INTERLACED);
    //SetOsdCol(0,0,0,0x1e1e1ecd);
    SetOsdCol(0,0,0,0x757575f0);// black zhaoyanhua add 2003-12-2 14:20
     
    osd_active_regions = 2;
    ENABLE_OSD(); 
    osd_init__();    
    
    osd_draw_icon_bbk(4,20,0);
    osd_draw_icon_bbk(68,23,1);         
}
void osd_draw_icon_bbk(int xStart, int yStart,int index)
{
    BYTE    *icon_bbk;
    UINT32  *pTopLine, *pBtmLine;
    UINT32  iDispLoc, iIconLoc;
    int     need_gray=0;

    int     i, j, k;
    int     iFontWidth, iFontHigh;
    int     iRegionWidth = region[0].osd_w;

    osd_tog_region(0, OSD_ON);  
    
    //initialize buffer start
    pTopLine = (UINT32 *)get_osdbuf_region_ptr(0,0);   // region 0 top
    pBtmLine = (UINT32 *)get_osdbuf_region_ptr(0,1);   // region 0 bot

    iIconLoc = 0;
    
    //skip n blank line on top(in pixel)
    //for interlace mode, we will skip n/2 blank lines, for example 4/2=2
    yStart+=2;
     
    {
        UINT32 pixel4;
        UINT32 pos;
        
        iIconLoc++;        
        icon_bbk = Pic_table[index];
       // icon_bbk = get_font_entry(2, index);

        //start to process
        pos = 2;
        
        //get icon information
                
        iFontWidth  =(int) icon_bbk[0];
        iFontHigh   = (int)icon_bbk[1];
               
        for (j=0; j<iFontHigh; j++) 
        {
            int yy;
            UINT32 *pp;
            yy = (p_scan) ? yStart : yStart>>1;
            pp = (yStart&1) ? pBtmLine : pTopLine;
            
            iDispLoc = (yy*iRegionWidth*2/8) + (xStart);
            for (i=0; i<(iFontWidth/4); i++) // every 4-bytes a time, every 1-pixels a byte
            {
                pixel4=0; 
               
                for (k=0;k<4;k++)
                {                    
                    unsigned curByte = icon_bbk[++pos];
                 
                    pixel4 = pixel4 | (curByte<<8*k);    
                }
                pp[iDispLoc+i] =  pixel4;
            }
            yStart++;
        }//for icon heigh  
    }

    timeout_osd[0] = 0;
}
#endif  // end bbk's new setup

#ifdef ROLL_SHOW_SETUP

/****************************************
FUNC:  similar to osd_draw_hline_region();
       difference: write button data to BUFFER not 
                    to SCREEN
        
Creator :zhaoyanhua 
Date:    2003-8-15 15:49
****************************************/
void MoveRect2buf(int xStart, int xEnd, int yStart, unsigned color, int yLen, int r)
{
    UINT8   *buf;
    int  i, j;
    //UINT8   *pTopLine, *pBtmLine;
    int     iRegionWidth  = region[r].osd_w;
    int     iRegionHeight = region[r].osd_h;
    UINT32   iDispLoc = 0;  
    
    
     buf = (UINT8 *)(SDRAM_BASE + P_BIDIR_LUMA*1024 + yStart*iRegionWidth );
    // setup color pixel (only support 16-color here)
    color &= 0x0f;
    //ButtonC = (color | (color<<4) | (color<<8) |color<<12)| (color<<16)|(color<<20) |(color<<24) | (color<<28));
    color =(color | (color<<4));
    
    for (j = 0; j < yLen; j++ )
    { 
        iDispLoc = j * iRegionWidth  ;
        for (i = xStart/2; i< (xEnd/2); i++) //draw one line
            buf[iDispLoc + i]= color;
    }
     
}

/***************************************
FUNC: 
      write string data to BUFFER not to SCREEN

Creator: zhaoyanhua 
Date: 2003-8-18 11:46
****************************************/
void MoveString2Buf(BYTE xStart, BYTE yStart,BYTE * str, BYTE fontColor, BYTE bkColor)
{
    BYTE    c;
    BYTE    *pFont;
    UINT32  *pTopLine, *pBtmLine;
    int     cc;
    UINT32  iStrLoc;
    int     iRegionWidth;
    UINT32  *buf;

    cc = xStart*16;//pixels.
    iRegionWidth = region[SETUP_REGION].osd_w;

    // initialize buffer start
    //pTopLine = (UINT32 *)get_osdbuf_region_ptr(SETUP_REGION, 0);
    //pBtmLine = (UINT32 *)get_osdbuf_region_ptr(SETUP_REGION, 1);
     buf= (UINT32 *)(SDRAM_BASE + P_BIDIR_LUMA*1024 + (yStart*SETUP_BTN_HEIGHT+4)*iRegionWidth+ xStart);     

    //process each charactor until string ending('\0')
    iStrLoc = 0;
    while ((c = ((BYTE *)str)[iStrLoc]) != '\0')
    {
        int     i, j, k;
        int     iFontWidth, iFontHigh;
        UINT32  pos;
        
        
        iStrLoc++;
        
        if (c == '\r') {                    //prefix characher: to use font_table2
            if ( (c = ((BYTE *)str)[iStrLoc])=='\0' ) break;
            iStrLoc++;
            if ((pFont = get_font_entry(1,c))==NULL) continue;
        } else {
            //get current char entry
            pFont = get_font_entry(0,c);
        }
        
        //start to process
        pos = 2;
        
        //get font information
        iFontWidth = (int)pFont[0];
        iFontHigh  = (int)pFont[1];
        
        //start this character
        for (j=0; j<iFontHigh; j++) {
            UINT32 *pp;
            int     yy;
            int     iDispLoc;

            yy  = j;
            iDispLoc = yy*(iRegionWidth/4) + (cc/8);
            
            //draw top line
            for (i=0; i<iFontWidth/8; i++) {
                unsigned pat;
                unsigned curByte;
                UINT32 pixel8;
                
                pat = pFont[++pos];
                curByte = ((pat&0xc0)>>6) | ((pat&0x30)>>2) | ((pat&0x0c)<<2) | ((pat&0x03)<<6);
                pixel8 = 0;
                for (k=0; k<8; k++) {       // for every-bit of pattern
                    if ( (1<<k) & curByte ) {          
                        pixel8 = pixel8 | (fontColor<<(k*4));
                    } else {
                        pixel8 = pixel8 | (bkColor<<(k*4));
                    }
                }
              //pp[iDispLoc+i] = pixel8;
               buf[iDispLoc+i] = pixel8;
            }
        }
        cc+=iFontWidth; 
    }
    
    timeout_osd[SETUP_REGION] = 0;
    osd_tog_region(SETUP_REGION, OSD_ON);   
}


extern BYTE setupItemNum[3];
//
// Bytes/Line = 37*16*4/8 = 296
//
/****************************************
FUNC:  
        draw the data to the SCREEN from 
        BUFFER
        
        BUF: P_BIDIR_LUMA

        EFFECT MODE: h_window .
    INPUT: 
        xStart:
        xEnd  :  unit is char.
        
Creator :zhaoyanhua 
Date:    2003-8-18 11:51        
*****************************************/
void MoveBuf2OSD(UINT16 xStart, UINT16 xEnd)
{
    UINT32  *buf;
    UINT32  *pTopLine, *pBtmLine;
    BYTE    i,step;
    UINT32  j, k;   
    UINT16  ButtonHight;//one BUTTON HIGHT.
    
    osd_tog_region(SETUP_REGION, OSD_ON);  


    buf = (UINT32 *)(SDRAM_BASE + P_BIDIR_LUMA*1024 );    
    //buf = (UINT32 *)(osd_temp_buf);
    
    //initialize buffer start    
    pTopLine = (UINT32 *)get_osdbuf_region_ptr(SETUP_REGION,0);
    pBtmLine = (UINT32 *)get_osdbuf_region_ptr(SETUP_REGION,1);

    //end=iLine;
    ButtonHight = 32;
    step=1;
    if(p_scan==0)
    {
       
       ButtonHight = 16;
       step=2;
    }
    else
    {
        ButtonHight = 32;
        step=1;
        
    }
    #if 0 //2 BUTTON cocurrently display.
    int m;
    printf("setupItemNum=%d\n",setupItemNum[1]);
    for (i = 0; i<ButtonHight; i++)//for (i = 0; i<32/2; i++)
    {
        delay_1ms(10);
        for (m =0; m < (setupItemNum[1]-1); m+=2)  
        {
           //NOTE:  
           //      xStart*16        : pixels
           //      xStart*16*4      : bits, one pixel 4 bits.
           //      (xStart*16*4)/8  : bytes.
           //      ((xStart*16*4)/8)/4  : bytes. unit is 4 BYTES.   
            for(j = ((xStart*16*4)/8)/4; j < ((xEnd*16*4)/8)/4; j++)//for(j = ((12)*16*4)/(8*4) ; j < ((12)*16*4)/(8*4)+((15)*16*4)/(8*4) ;j++)
            {// for (j=0; j<76; j++) {
       
               k = step * (m*ButtonHight +i);
               //top area
               pTopLine[76*(m*ButtonHight +i)+j] = buf[76*k + j];
               //bottom area
               pBtmLine[76*(m*ButtonHight +i)+j] = buf[76*(k+1) + j];            
            
            }            
        }
    }
    #endif
    
    #if 1 //1 BUTTON
    int m;
       //printf("setupItemNum=%d\n",setupItemNum[1]);
    
    for (i = 0; i<ButtonHight; i++)//for (i = 0; i<32/2; i++)
    {
        delay_1ms(15);
        for (m =0; m < (setupItemNum[1]-1); m++)  
        {
            //NOTE:  
           //      xStart*16        : pixels
           //      xStart*16*4      : bits, one pixel 4 bits.
           //      (xStart*16*4)/8  : bytes.
           //      ((xStart*16*4)/8)/4  : bytes. unit is 4 BYTES.   
            for(j = ((xStart*16*4)/8)/4; j < ((xEnd*16*4)/8)/4; j++)//for(j = ((12)*16*4)/(8*4) ; j < ((12)*16*4)/(8*4)+((15)*16*4)/(8*4) ;j++)
            {// for (j=0; j<76; j++) 
                k = step * (m*ButtonHight +i);
               //top area
                pTopLine[76*(m*ButtonHight +i)+j] = buf[76*k + j];
                //bottom area
                pBtmLine[76*(m*ButtonHight +i)+j] = buf[76*(k+1) + j];            
            
            }            
        }
    }
    #endif

    
    #if 0//Roll display
    for (i=iStartLine; i<iEndLine; i++) 
    {
       // k = 24-iLine+step*i;
        k = step*i;
        //NOTE:  
           //      xStart*16        : pixels
           //      xStart*16*4      : bits, one pixel 4 bits.
           //      (xStart*16*4)/8  : bytes.
           //      ((xStart*16*4)/8)/4  : bytes. unit is 4 BYTES.   
        for(j = ((xStart*16*4)/8)/4; j < ((xEnd*16*4)/8)/4; j++)
        {// for (j=0; j<76; j++) {
            //top area
            pTopLine[76*i+j] = buf[76*k + j];
            //bottom area
            pBtmLine[76*i+j] = buf[76*(k+1) + j];
            
        }
    }
   #endif
    
    
}
#endif

//
// osd_DrawString
//

#ifdef SOFT_MENU//Modifed by ChenZhao on 2004-9-6 10:43 WP
void osd_DrawString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor)
{
    osd_DrawString_ori(xStart*8, (yStart*SETUP_BUTTON_HEIGHT), str, fontColor, bkColor);
}
#else
void osd_DrawString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_DrawString_ori(xStart, (yStart*SETUP_BTN_HEIGHT), str, fontColor, bkColor);
}
#endif//SOFT_MENU

#ifdef SETUPMENU_16Mb_NO_ICON
void osd_DrawSetupIconString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor)
{
    osd_DrawString_ori(xStart, yStart, str, fontColor, bkColor);
}
#endif//SETUPMENU_16Mb_NO_ICON

#ifdef SOFT_MENU//Modifed by ChenZhao on 2004-9-6 10:43 WP
	#include"osd_SFM.c"
	
#elif defined(USE_SMALL_FONT)
//libing for small font 2005-1-5 20:52
void
osd_DrawString_ori(BYTE xStart, UINT32 yStart, const BYTE *str, BYTE fontColor, BYTE bkColor)
{
//libing modify it for zhe smaller font 2004-11-3 13:53
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
        //if(p_scan==0)    iFontHigh>>=1;
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
    }   cc+=iFontWidth; 
    }
    timeout_osd[SETUP_REGION] = 0;
    osd_tog_region(SETUP_REGION, OSD_ON);  
}	
	
#else

void
osd_DrawString_ori(BYTE xStart, UINT32 yStart, const BYTE *str, BYTE fontColor, BYTE bkColor)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    BYTE    c;
    const BYTE    *pFont;
    UINT32  *pTopLine, *pBtmLine;
    int     cc;
    UINT32  iStrLoc;
    int     iRegionWidth;

    iRegionWidth = region[SETUP_REGION].osd_w;

    // initialize buffer start
    pTopLine = (UINT32 *)get_osdbuf_region_ptr(SETUP_REGION, 0);
    pBtmLine = (UINT32 *)get_osdbuf_region_ptr(SETUP_REGION, 1);
    
    // initialize start position
    cc = xStart*16; //pixels

    //process each charactor until string ending('\0')
    iStrLoc = 0;
    while ((c = ((BYTE *)str)[iStrLoc]) != '\0')
    {
        int     i, j, k;
        int     iFontWidth, iFontHigh;
        UINT32  pos;
        
        iStrLoc++;
        
        if (c == '\r') {                    //prefix characher: to use font_table2
            if ( (c = ((BYTE *)str)[iStrLoc])=='\0' ) break;
            iStrLoc++;
            if ((pFont = get_font_entry(1,c))==NULL) continue;
        } 
        #if 0//def DVB1000_OSD_MENU //Maoyong 2005-4-6 9:49    //sunzhh modify2005-4-15
        else if(c>='a' && c<='z')
        {
            if(IsOSDChinese())
                pFont = get_font_entry(0, c);
            else                
            pFont=get_font_entry(0,c-'a'+0x100);  //2005-04-10 haoy midify from 0xc0 to 0x100 
        }
		#endif     
		else {
            //get current char entry
            pFont = get_font_entry(0,c);
        }
        
        //start to process
        pos = 2;
        
        //get font information
        iFontWidth = (int)pFont[0];
        iFontHigh  = (int)pFont[1];
        
        //start this character
        for (j=0; j<iFontHigh; j++) {
            UINT32 *pp;
            int     yy;
            int     iDispLoc;
//			#ifdef OP_UI//liwh add 2004-3-19 16:01
//			#include "menu_def.h"
//			yy  = 10 + yStart*(BUTTON_Y_DIFF) + j;
//			#else
            //yy  = 4 + yStart*SETUP_BTN_HEIGHT + j;
            yy  = 4 + yStart + j;
//            #endif
            //For every string line = 1 blank line(in pixel) + OSD_FONT_HEIGHT-line strings + 1 blank line
            pp  = (yy&1) ? pBtmLine : pTopLine;
            if (p_scan==0) yy>>=1;      // p-scan
            //in fact,iDispLoc = (yy*iRegionWidth + cc/2)/4;
            //yy*iRegionWidth + cc/2 calculate the positon as the byte.
            //iDispLoc is 32bit.so must "/4".
            //zhaoyanhua note 2003-8-14 15:35
            iDispLoc = yy*(iRegionWidth/4) + (cc/8);
            
            //draw top line
            for (i=0; i<iFontWidth/8; i++) {
                unsigned pat;
                unsigned curByte;
                UINT32 pixel8;
                
                pat = pFont[++pos];
                curByte = ((pat&0xc0)>>6) | ((pat&0x30)>>2) | ((pat&0x0c)<<2) | ((pat&0x03)<<6);
                pixel8 = 0;
                for (k=0; k<8; k++) {       // for every-bit of pattern
                    if ( (1<<k) & curByte ) {          
                        pixel8 = pixel8 | (fontColor<<(k*4));
                    } else {
                        pixel8 = pixel8 | (bkColor<<(k*4));
                    }
                }
                pp[iDispLoc+i] = pixel8;
            }
        }
        cc+=iFontWidth; 
    }
    timeout_osd[SETUP_REGION] = 0;
    osd_tog_region(SETUP_REGION, OSD_ON);  
}
#endif /* SOFT_MENU */


void
osd_DrawStrings(const t_osd_str *p, BYTE fg, BYTE bg)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    int i;
    for (i=0; p[i].str!=NULL; i++)
    {
        osd_DrawString(p[i].xst, p[i].yst, p[i].str, fg, bg);
    }
}

#ifdef OSD_STR_LINE_WRAP  
/*
 * Description:
 *   Get next space position
 *
 * INPUT:
 *    str:  ---> string
 *    iStrLoc ---> initial position to search
 *
 *
 * RETURN:
 *    if Find next given letter, return its postion
 *    else if not find it, it means that the string will be end.
 *                         so return its total strlen.
 * zhaoyanhua 2004-4-22 9:49
 */
int FindNextLetter(const BYTE *str, int iStrLoc, BYTE c)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

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

       
   
#if defined(USE_SMALL_FONT)||defined(OP_PLAYMODE)
//libing for small font 2005-1-5 20:52
void
osd_DrawRegionString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r)
{
    BYTE    *pFont, c;//,div=4;
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
void
osd_DrawRegionString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    const BYTE* pFont;
    BYTE    c,div=4;
    UINT32  *pTopLine, *pBtmLine;
    UINT32  iDispLoc, iStrLoc;
    int     i, j, k;
    int     iFontWidth, iFontHigh;
    int     iRegionWidth = region[r].osd_w;
    
    osd_tog_region(r, OSD_ON);  
    
    #ifdef SUPPORT_EPG
    extern int g_EPG_Mode;
    int old_font_mode = osd_font_mode;
    if(g_EPG_Mode)
    	osd_font_mode = 0;
    #endif
    //initialize buffer start
    pTopLine = (UINT32 *)get_osdbuf_region_ptr(r,0);
    pBtmLine = (UINT32 *)get_osdbuf_region_ptr(r,1);
    
    iStrLoc = 0;
    if(p_scan==0)
       div=8;
       
    if (p_scan==1)
    {
#ifdef NEWSTYLE_WINDOW   //xiongyuyue
        if(full_scrn&MESSAGE)
            iDispLoc = (yStart*iRegionWidth/*div*SETUP_BTN_HEIGHT*/) + (xStart);
        else
#endif
    
        iDispLoc = (yStart*iRegionWidth/*div*SETUP_BTN_HEIGHT*/) + (xStart*16/8)+(iRegionWidth/2);
    }
    else
    {
#ifdef NEWSTYLE_WINDOW   //xiongyuyue
    if(full_scrn&MESSAGE)
        iDispLoc = (yStart*iRegionWidth/2/*div*SETUP_BTN_HEIGHT*/) + (xStart);
    else
#endif
        iDispLoc = (yStart*iRegionWidth/2/*div*SETUP_BTN_HEIGHT*/) + (xStart*16/8);
    }
    //skip n blank line on top(in pixel)
    //for interlace mode, we will skip n/2 blank lines, for example 4/2=2
    iDispLoc += (iRegionWidth/4 * 2);
    
    //process each charactor until string ending('\0')
    while ( (c = ((BYTE *)str)[iStrLoc]) != '\0' ) {
        BYTE curByte;
        UINT32 pixel8;
        UINT32 pos;
        
        iStrLoc++;
        
        if (c == '\r') { //prefix characher:to use font_table2
            if ( (c = ((BYTE *)str)[iStrLoc])=='\0' )
                break;
            
            iStrLoc++;
            if ((pFont = get_font_entry(1,c))==NULL) continue;
        }
#if defined(NEWSTYLE_WINDOW)||defined(NEW_STYLE_SETUP)  || defined(SUPPORT_REP_READ) || defined(DVB1000_OSD_MENU)|| defined(DVB_MENU_TYPE1)//maoyong add 0915
        else if(c == '\a')
        {
            if ( (c=((BYTE *)str)[iStrLoc])=='\0' ) break;
            
            iStrLoc++;

            if ((pFont = get_font_entry(3,c))==NULL) continue;

        }
#endif 
#if 0//def DVB1000_OSD_MENU //Maoyong 2004-10-26 16:08 //sunzhh modify 2005-4-15
        else if(c>='a' && c<='z')
        {
            if(IsOSDChinese())
                pFont = get_font_entry(0, c);
            else                
                pFont=get_font_entry(0,c-'a'+0x100);  //2005-04-10 haoy midify from 0xc0 to 0x100 
            //printf("c=%c,c=%x\n",c,c);
        }
#endif     
        else {
            //get current char entry
            pFont = get_font_entry(0,c);
        }
        
        //start to process
        pos = 2;
        
        //get font information
        iFontWidth = (int)pFont[0];
        iFontHigh = (int)pFont[1];
        
        if(p_scan==0)
          iFontHigh>>=1;
          
        //start to draw        
        for (j=0; j<iFontHigh; j++) {
            //For every string line = 1 blank line(in pixel) + OSD_FONT_HEIGHT-line strings + 1 blank line
            
            //draw top line
            for (i=0; i<iFontWidth/8; i++) {
                BYTE c;
                
                c = pFont[++pos];
                curByte = ((c&0xc0)>>6) | ((c&0x30)>>2) | ((c&0x0c)<<2) | ((c&0x03)<<6);
                //NOTE:
                //The previous mothod has a problem when show our radio button.
                //When  write a char(smaller circle) in another char (bigger circle).
                //smaller circle looks like not a circle but a rect!!!
                //I modify the method to fill the fontcolor and bkcolor.  
                //Please don't care about the changes will effect the funciton's original funcitons.
                //zhaoyanhua add 2004-3-19 16:19
                
                //pixel8 = 0;//zhaoyanhua mask 2004-2-27 14:41
                pixel8 = pTopLine[iDispLoc+i];//zhao add 2004-2-27 14:41
                
                for (k=0; k<8; k++) {          
                    if ( (1<<k) & curByte ) {          
                        
                        //pixel8 = pixel8 | (fontColor<<(k*4));//zhaoyanhua mask 2004-2-27 14:41
                        pixel8 = (pixel8 & (~( 0x0f<<k*4))) |(fontColor<<(k*4));//zhao add 2004-2-27 14:41
                    } else {
                        //pixel8 = pixel8 | (bkColor<<(k*4));//zhaoyanhua mask 2004-2-27 14:41
                        if(bkColor != 0)//if color index is 0, no need to change the vlaue fo pixel8
                            pixel8 = (pixel8 & (~( 0x0f<<k*4))) | (bkColor<<(k*4));//zhao add 2004-2-27 14:41
                        
                    }
                }
                
                pTopLine[iDispLoc+i] = pixel8;
            }
            
            if(p_scan==0)
            {
               //draw bottom line
               for (i=0; i<iFontWidth/8; i++) {
                  BYTE c;
                
                  c = pFont[++pos];
                  curByte = ((c&0xc0)>>6) | ((c&0x30)>>2) | ((c&0x0c)<<2) | ((c&0x03)<<6);
                   //pixel8 = 0;//zhaoyanhua mask 2004-2-27 14:41
                    pixel8 = pBtmLine[iDispLoc+i];//zhao add 2004-2-27 14:41
                
                  for (k=0; k<8; k++) {          
                    if ( (1<<k) & curByte ) {
                       //pixel8 = pixel8 | (fontColor<<(k*4));//zhaoyanhua mask 2004-2-27 14:41
                        pixel8 = (pixel8 & (~( 0x0f<<k*4))) |(fontColor<<(k*4));//zhao add 2004-2-27 14:41
                    } else {
                        //pixel8 = pixel8 | (bkColor<<(k*4));//zhaoyanhua mask 2004-2-27 14:41
                        if(bkColor != 0)//if color index is 0, no need to change the vlaue fo pixel8
                            pixel8 = (pixel8 & (~( 0x0f<<k*4))) | (bkColor<<(k*4));//zhao add 2004-2-27 14:41
                        
                    }
                  }
                
                  pBtmLine[iDispLoc+i] = pixel8;
               }
            }
            iDispLoc += (iRegionWidth/4);
            
        }//for charactor heigh  
        
        //move to next character and move up to first line of this string
        iDispLoc = iDispLoc + (iFontWidth/8) - (iRegionWidth/4*iFontHigh);
        
    } // end of while ( (c=((BYTE *)str)[unFontLoc])!='\0' )
    
    timeout_osd[r] = 0;
    
    #ifdef SUPPORT_EPG	//Maoyong 2005-1-16 14:20
    if(g_EPG_Mode)
    	osd_font_mode = old_font_mode;
    #endif
    
}
#endif //#if defined(USE_SMALL_FONT)

#include "audcodec.h"
#include "..\setup\setup_def.h"
//#define MAX_SETUP_PAGE          6 
//#define MAX_CUSTM_SETUP_PAGE    1 
//#define MAX_PAGE_ITEM            8 


#ifdef SOFT_MENU//Modifed by ChenZhao on 2004-9-1 10:18 WP
#define AUDPAGE         2
#else
#define AUDPAGE         2
#endif

#ifdef NO_DIGIT_VIDEO_MENU
#define VIDEOPAGE       4
#define MULTISPKPAGE    3      //valid when AC3 or DTS
#else
#define VIDEOPAGE       3
#define MULTISPKPAGE    4      //valid when AC3 or DTS
#endif

#define SPDIFSIMULATE   2
#define AC3DIGITALPAGE  5 
#define SPDIFBITSTREAM  3

extern UINT8 setup_sel[MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE][MAX_PAGE_ITEM];

#define SETUP_SPDIF                 setup_sel[AUDPAGE][0]


#ifdef NEW_STYLE_SETUP //zhaoyanhua add 2003-07-22 22:21
void
osd_DrawIcon(int xStart, int yStart, unsigned index, unsigned page)
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

#else //NORMAL setup MENU

void
osd_DrawIcon(int xStart, int yStart, unsigned index, unsigned page)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    const BYTE    *pIcon;
    UINT32  *pTopLine, *pBtmLine;
    UINT32  iDispLoc, iIconLoc;
    int     need_gray=0;

    int     i, j, k;
    int     iFontWidth, iFontHigh;
    int     iRegionWidth = region[0].osd_w;
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
#endif//EASTECH_NEW_SETUP_MENU
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
                        #ifdef SETUP_COLOR_TYPE2       //zhangyu 3-9-2 11:48张宇A
                        if ((curByte&0x0f)==0x06) curByte=(0x0d|(curByte&0xf0));
                        if ((curByte&0xf0)==0x60) curByte=(0xd0|(curByte&0x0f));
                                   
                        #elif defined( QSI_SETUP_MENU_DESIGN)           
                        if ((curByte&0x0f)==0x0c) curByte=(0x08|(curByte&0xf0));
                        if ((curByte&0xf0)==0xc0) curByte=(0x80|(curByte&0x0f));                
                        #else
                        if ((curByte&0x0f)==0x06) curByte=(0x01|(curByte&0xf0));
                        if ((curByte&0xf0)==0x60) curByte=(0x10|(curByte&0x0f));
                    
                       #endif
                    }
                    else
                    {
                        #ifdef SETUP_COLOR_TYPE2
                        if ((curByte&0x0f)==0x06) curByte=(0x07|(curByte&0xf0));
                        if ((curByte&0xf0)==0x60) curByte=(0x70|(curByte&0x0f));
            #endif
                    }   
//#ifndef SETUP_COLOR_TYPE2
                    if (need_gray==1)
                    {
                        if ((curByte&0x0f)!=0x01) curByte=(0x0b|(curByte&0xf0));
                        if ((curByte&0xf0)!=0x10) curByte=(0xb0|(curByte&0x0f));                        
                    }
//#endif
                    pixel8 = pixel8 | (curByte<<8*k);    
                }
                pp[iDispLoc+i] =  pixel8;
            }
            yStart++;
        }//for icon heigh  
    }

    timeout_osd[0] = 0;
}

#endif//NEW_STYLE_SETUP
//
// osd_DrawLine     : draw a horizontal line or vertical line
//
// input    :   xStart      -> line start x(units in pixel)
//              yStart      -> line start y
//              xEnd        ->
//              yEnd
//              color       -> line color
//              lineWidth   -> line width
//
void
osd_DrawLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_DrawRegionLine(xStart,yStart,xEnd,yEnd,color,lineWidth,SETUP_REGION);
}


void
osd_draw_vline_region(int x, int yStart, int yEnd, unsigned color, int n, int r)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    int     i;
    UINT8   *pTopLine, *pBtmLine;
    int     iRegionWidth = region[r].osd_w;
        
    //initialize buffer start
    pTopLine = get_osdbuf_region_ptr(r,0);
    pBtmLine = get_osdbuf_region_ptr(r,1);

    // setup color pixel (only support 16-color here)
    color &= 0x0f;

    while (n-->0)
    {
        int idx = x>>1;
        for (i=yStart;i<yEnd;i++)
        {
            UINT8 *p = (i&1) ? pBtmLine : pTopLine;
            int yy;
            yy = (p_scan) ? i : i>>1;
            p  = p + yy * iRegionWidth;
            if (x&1)
                p[idx] = (p[idx]&~0x0f) | (color<<0);
            else
                p[idx] = (p[idx]&~0xf0) | (color<<4);
        }
        x++;
    }
}



void
osd_draw_hline_region(int xStart, int xEnd, int y, unsigned color, int n, int r)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    int  i;
    UINT8   *pTopLine, *pBtmLine;
    int     iRegionWidth  = region[r].osd_w;
    int     iRegionHeight = region[r].osd_h;
        
    //initialize buffer start
    pTopLine = get_osdbuf_region_ptr(r,0);
    pBtmLine = get_osdbuf_region_ptr(r,1);

    // setup color pixel (only support 16-color here)
    color &= 0x0f;
    color = color | (color<<4);

    xStart>>=1;     // 2-pixel at a time
    xEnd>>=1;       // 2-pixel at a time

    while (n-->0)
    {
        UINT8 *p = (y&1) ? pBtmLine : pTopLine;
        int yy;
        yy = (p_scan) ? y : y>>1;
        if (y>=iRegionHeight)
        {
            osd_printf("draw too large %d to region %d\n", y, r);
            return;
        }
        p = p + yy * iRegionWidth;
        for (i=xStart; i<xEnd; i++) p[i] = color;
        y++;
    }
}
    

void
osd_DrawRegionLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth, BYTE r)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    BYTE        *pTopLine, *pBtmLine;
    UINT32      iDispLoc, iOffSet;
    UINT32      i, j;
    int         iRegionWidth = region[r].osd_w;
    BYTE        c;
        
    if ( (xStart!=xEnd) && (yStart!=yEnd) ) return;     // we only support horizontal or vertical line
    if ( (xStart>xEnd) || (yStart>yEnd) ) return;       // check limit
    
    osd_tog_region(r, OSD_ON);
    
    //initialize buffer start
    pTopLine = get_osdbuf_region_ptr(r,0);
    pBtmLine = get_osdbuf_region_ptr(r,1);
    
    if (p_scan==0) 
    {
        yStart>>=1;
        yEnd>>=1;
    }    
    
    iDispLoc = (yStart * iRegionWidth) + (xStart/2);
    
    c = color | (color<<4);
    
    if (yStart==yEnd)
    {
        //draw horizontal line
        for (j=0; j<lineWidth; j++) {
            //array index(in Byte)
            iOffSet = iDispLoc + j*iRegionWidth;
            
            for (i=0; i<(xEnd-xStart)/2; i++)
            {
                pTopLine[iOffSet+i] = c;
                pBtmLine[iOffSet+i] = c;
            }
        }
    }
    else
    {
        //draw vertical line
        yEnd=yEnd-yStart;
        for (j=0; j<yEnd; j++) {
            //array index(in Byte)
            iOffSet = iDispLoc + j*iRegionWidth;
            
            for (i=0; i<lineWidth; i++)
            {
                pTopLine[iOffSet+i] = c;
                pBtmLine[iOffSet+i] = c;
            }
        }
    }
    
    timeout_osd[r] = 0;
}


//
// osd_draw_rect : draw a rectangle shape with blanking content
//
//  input   :   xStart      -> x start position to draw
//              yStart      -> y start position to draw
//              xLen        -> rectangle width(width of blank area)
//              yLen        -> rectangle lines(height of blank area)
//              bkColor     -> color index of background color
//
//  notes   :   Units in pixel
//
void
osd_draw_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

#ifdef NEWSTYLE_WINDOW
    if(full_scrn&MESSAGE)
        osd_draw_region_rect(xStart, yStart, xLen, yLen, bkColor, arc_region_loc.region);
    else
#endif
        osd_draw_region_rect(xStart, yStart, xLen, yLen, bkColor, SETUP_REGION);
}


#ifdef NEWSTYLE_WINDOW  //xiongyuyue add 20030630
//***************************//
//updown == 0,display 凹//
//updown == 1,display 凸//
//updown > 1 ,normal display//
//**************************//
void
osd_draw_region_arc(ARC_REGION_LOC *loc_var,BYTE updown)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

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
//    c2=loc_var->blackColor | (loc_var->blackColor<<4);
//    c3=loc_var->whiteColor | (loc_var->whiteColor<<4);

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
/*                else if((arc_tableLT[j][i]==1)&&(updown==0))
                {
                    pTopLine[iOffSet+i] = c2;
                    pBtmLine[iOffSet+i] = c2; 
                    continue;       
                }
                else if((arc_tableLT[j][i]==1)&&(updown==1))
                {
                    pTopLine[iOffSet+i] = c3;
                    pBtmLine[iOffSet+i] = c3; 
                    continue;       
                }*/
            }
            else if((i >= loc_var->xLen/2-loc_var->radius)&&(j<radius))//draw right-top corner
            {
                if((arc_tableRT[j][i-loc_var->xLen/2+loc_var->radius]==0))
                    continue;
/*                else if((arc_tableRT[j][i-loc_var->xLen/2+16]==1)&&(updown==0))
                {
                    pTopLine[iOffSet+i] = c2;
                    pBtmLine[iOffSet+i] = c2;  
                    continue;       
                }
                else if((arc_tableRT[j][i-loc_var->xLen/2+16]==1)&&(updown==1))
                {
                    pTopLine[iOffSet+i] = c3;
                    pBtmLine[iOffSet+i] = c3;  
                    continue;       
                }*/
            } 
            else if((i<loc_var->radius)&&(j>=loc_var->yLen-radius))//draw left-bottom corner
            {
                if((arc_tableLB[j-loc_var->yLen+loc_var->radius][i]==0))
                    continue;                    
/*                else if((arc_tableLB[j-loc_var->yLen+loc_var->radius][i]==1)&&(updown==0))
                {
                    pTopLine[iOffSet+i] = c2;
                    pBtmLine[iOffSet+i] = c2; 
                    continue;        
                }
                else if((arc_tableLB[j-loc_var->yLen+loc_var->radius][i]==1)&&(updown==1))
                {
                    pTopLine[iOffSet+i] = c3;
                    pBtmLine[iOffSet+i] = c3; 
                    continue;        
                }*/
            }
            else if((j >= loc_var->yLen-radius)&&(i >= loc_var->xLen/2-loc_var->radius))//draw right-bottom corner
            {
                if(arc_tableRB[j-loc_var->yLen+loc_var->radius][i-loc_var->xLen/2+loc_var->radius]==0)
                    continue;
/*                else if((arc_tableRB[j-loc_var->yLen+loc_var->radius][i-loc_var->xLen/2+loc_var->radius]==1)&&(updown==0))
                {
                    pTopLine[iOffSet+i] = c3;
                    pBtmLine[iOffSet+i] = c3;   
                    continue;      
                }
                else if((arc_tableRB[j-loc_var->yLen+loc_var->radius][i-loc_var->xLen/2+loc_var->radius]==1)&&(updown==1))
                {
                    pTopLine[iOffSet+i] = c2;
                    pBtmLine[iOffSet+i] = c2;   
                    continue;      
                }*/
            }
            pTopLine[iOffSet+i] = c1;
            pBtmLine[iOffSet+i] = c1;
        }
    }
    
/*    c2 = c3 = 0;
    
    if(updown==0)
    {
        c2 = loc_var->blackColor;
        c3 = loc_var->whiteColor;   
    }
    else if(updown==1)
    {
        c2 = loc_var->whiteColor;
        c3 = loc_var->blackColor;
    }
    else
        c2 = c3 = loc_var->bkColor;
    //draw top horizontal 
    osd_DrawRegionLine(loc_var->xStart+loc_var->radius*2,(loc_var->yStart)*2,
    loc_var->xStart + loc_var->xLen - loc_var->radius*2,(loc_var->yStart)*2,c2,1,loc_var->region);
    
    //draw bottom horizontal
    osd_DrawRegionLine(loc_var->xStart+loc_var->radius*2,(loc_var->yStart+loc_var->yLen)*2,
    loc_var->xStart + loc_var->xLen - loc_var->radius*2,(loc_var->yStart+loc_var->yLen)*2,c3,1,loc_var->region);

    //draw left vertical
    osd_DrawRegionLine(loc_var->xStart,(loc_var->yStart + loc_var->radius)*2,
    loc_var->xStart,(loc_var->yStart+loc_var->yLen-loc_var->radius)*2,c2,1,loc_var->region);
    
    //draw right vertical
    osd_DrawRegionLine((loc_var->xStart+loc_var->xLen),(loc_var->yStart + loc_var->radius)*2,
    (loc_var->xStart+loc_var->xLen),(loc_var->yStart+loc_var->yLen-loc_var->radius)*2,c3,1,loc_var->region);
*/
    timeout_osd[loc_var->region] = 0;
    osd_tog_region(loc_var->region, OSD_ON);
}

/*
void osd_DrawArrow(ARC_REGION_LOC *loc_var,BYTE UPDOWN)
{
    BYTE        *pTopLine, *pBtmLine;
    UINT32      iDispLoc, iOffSet;
    UINT32      i, j;
    int         iRegionWidth = region[loc_var->region].osd_w;
    BYTE        c;

    //initialize buffer start
    pTopLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (region[loc_var->region].osd_header[0]+OSD_DATA_OFFSET(region[loc_var->region].osd_format))*32 );
    pBtmLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (region[loc_var->region].osd_header[1]+OSD_DATA_OFFSET(region[loc_var->region].osd_format))*32 );
    
    if(p_scan==0)
    {
       loc_var->yStart>>=1;
    }
    
//    iDispLoc = (loc_var->yStart * iRegionWidth) + (loc_var->xStart/2);
    
    iDispLoc = (loc_var->yStart*4*iRegionWidth) + (loc_var->xStart*4);
    
    iDispLoc += 3*iRegionWidth;
    c=loc_var->bkColor | (loc_var->bkColor<<4);
    
    if(UPDOWN==1)
    {
        
        for (j=0; j<loc_var->radius; j++) 
        {
            iOffSet = iDispLoc + j*iRegionWidth;
            for (i=0; i<loc_var->radius; i++) 
            {
                if((Arrow_Left[j][i]==0))
                    continue;
                pTopLine[iOffSet+i] = c;
                pBtmLine[iOffSet+i] = c;
            }
        }
    } 
    else if(UPDOWN==2)
    {                              
        for (j=0; j<loc_var->radius; j++) 
        {
            iOffSet = iDispLoc + j*iRegionWidth;
            for (i=0; i<loc_var->radius; i++) 
            {
                if((Arrow_Right[j][i]==0))
                    continue;
                pTopLine[iOffSet+i] = c;
                pBtmLine[iOffSet+i] = c;
            }
        }
    } 
    timeout_osd[loc_var->region] = 0;
    osd_tog_region(loc_var->region, OSD_ON);
       
}
*/

/*
//the meaning of type par
//LT: left-top corner;
//RT: right-top corner;
//LB: left-bottom corner;
//RB: right-bottom corner;
void osd_Draw_Arc_Line( ARC_REGION_LOC *loc_var,BYTE type,BYTE lineWidth)
{
    BYTE        *pTopLine, *pBtmLine;
    UINT32      iDispLoc, iOffSet;
    UINT32      i, j, k;
    int         Region;
    int         iRegionWidth = region[loc_var->region].osd_w;
    BYTE        c;

    Region = loc_var->region;
    osd_tog_region(Region, OSD_ON);
    //initialize buffer start
    pTopLine = get_osdbuf_region_ptr(Region, 0);
    pBtmLine = get_osdbuf_region_ptr(Region, 1);
  
    if(p_scan==0)
    {
       loc_var->yLen>>=1;
       loc_var->yStart>>=1;
    }
    
    iDispLoc = (loc_var->yStart * iRegionWidth) + (loc_var->xStart/2);
    c = loc_var->bkColor | (loc_var->bkColor<<4);
    for (k=0;k<lineWidth;k++)
    {
        
        switch (type)
        {
            case 1:
                for (j=0; j<loc_var->radius; j++) 
                {
                    //array index(in Byte)
                    iOffSet = iDispLoc + j*iRegionWidth;
                    for (i=0; i<loc_var->radius; i++) 
                    {
                        if((arc_tableLT[j][i]==0)||(arc_tableLT[j][i]>1))
                            continue;
                        pTopLine[iOffSet+i] = c;
                        pBtmLine[iOffSet+i] = c;
                    }
                }
                break;
            case 2:
                for (j=0; j<loc_var->radius; j++) 
                {
                    //array index(in Byte)
                    iOffSet = iDispLoc + j*iRegionWidth;
                    for (i=0; i<loc_var->radius; i++) 
                    {
                        if((arc_tableRT[j][i]==0)||(arc_tableRT[j][i]>1))
                            continue;
                        pTopLine[iOffSet+i] = c;
                        pBtmLine[iOffSet+i] = c;
                    }
                }
                break;
            case 3:
                for (j=0; j<loc_var->radius; j++) 
                {
                    //array index(in Byte)
                    iOffSet = iDispLoc + j*iRegionWidth;
                    for (i=0; i<loc_var->radius; i++) 
                    {
                        if((arc_tableLB[j][i]==0)||(arc_tableLB[j][i]>1))
                            continue;
                        pTopLine[iOffSet+i] = c;
                        pBtmLine[iOffSet+i] = c;
                    }
                }
                break;
            case 4:
                for (j=0; j<loc_var->radius; j++) 
                {
                    //array index(in Byte)
                    iOffSet = iDispLoc + j*iRegionWidth;
                    for (i=0; i<loc_var->radius; i++) 
                    {
                        if((arc_tableRB[j][i]==0)||(arc_tableRB[j][i]>1))
                            continue;
                        pTopLine[iOffSet+i] = c;
                        pBtmLine[iOffSet+i] = c;
                    }
                }
                break;
                
        }
        
    }
    
    timeout_osd[loc_var->region] = 0;
}
*/
#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW//zhaoyanhua add for BBK_DVD
/*
 * when draw NEW_STYLE_WINDOW, for NTSC
 */
void   osd_init_newstyle_window_NTSC(void)
{
       osd_puts("osd_init_newstyle_window\n");
    __osd_init();
    
    header_id = SETUP_HEADER;

    region[2].osd_w = 38*8;
    region[2].osd_h = OSD_FONT_HEIGHT*16-10;//374
    osd_create_region1(&region[2], 24,  42-4, NULL,OSD_FORMAT_16COLOR,OSD_INTERLACED);//axel 2003/11/21 07:19pm

    SetOsdCol(2,2,0,0x1e1e1e00);
    header_id = NORMAL_HEADER;
    region[1].osd_w = 36*4;
    region[1].osd_h = OSD_FONT_HEIGHT;

    osd_create_region1(&region[1], 32,  30-4, &region[2],OSD_FORMAT_4COLOR,OSD_INTERLACED);//axel 2003/11/21 07:19pm    


    header_id = SETUP_HEADER;
    region[0].osd_w = 38*8;
    region[0].osd_h = OSD_FONT_HEIGHT;
    osd_create_region1(&region[0], 26,  16-4, &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);//axel 2003/11/21 07:19pm

    osd_active_regions = 3;
    osd_init__();

    
}
/*
 *  for PAL
 */
void   osd_init_newstyle_window_PAL(void)
{
       osd_puts("osd_init_newstyle_window\n");
    __osd_init();
    
    header_id = SETUP_HEADER;

    region[2].osd_w = 38*8;
    region[2].osd_h = OSD_FONT_HEIGHT*16-9;//OSD_FONT_HEIGHT*16-8;//374   //fengjl edit 3-12-24 13:04 
    osd_create_region1(&region[2], 24, 42+26 /*42+30*/, NULL,OSD_FORMAT_16COLOR,OSD_INTERLACED);//axel 2003/11/21 07:19pm

    SetOsdCol(2,2,0,0x1e1e1e00);
    header_id = NORMAL_HEADER;
    region[1].osd_w = 36*4;
    region[1].osd_h = OSD_FONT_HEIGHT;

    osd_create_region1(&region[1], 32,  30+20, &region[2],OSD_FORMAT_4COLOR,OSD_INTERLACED);//axel 2003/11/21 07:19pm    


    header_id = SETUP_HEADER;
    region[0].osd_w = 38*8;
    region[0].osd_h = OSD_FONT_HEIGHT;
    osd_create_region1(&region[0], 26,  16+10, &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);//axel 2003/11/21 07:19pm

    osd_active_regions = 3;
    osd_init__();   
}

#endif//MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
void    osd_init_newstyle_window(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_puts("osd_init_newstyle_window\n");
    __osd_init();
    
    header_id = SETUP_HEADER;
/*
    region[4].osd_w = 37*8;  //35 English Characters
    region[4].osd_h = 5*29;  //6 lines
    osd_create_region1(&region[4], 30,  128+4+4+16+7, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);

    region[3].osd_w = 12*8;  //12 English Characters
    region[3].osd_h = (OSD_FONT_HEIGHT+4)*5;  //6 lines
    osd_create_region1(&region[3], 230,  58+4, &region[4], OSD_FORMAT_16COLOR, OSD_INTERLACED);

    header_id = NORMAL_HEADER;
    region[2].osd_w = 36*4;
    region[2].osd_h = OSD_FONT_HEIGHT;
    osd_create_region1(&region[2], 32,  42+4, &region[3],OSD_FORMAT_4COLOR,OSD_INTERLACED);
*/
/*
    if(tv_format==MODE_PAL)
    {
        region[2].osd_w = 38*8;
//        region[2].osd_h = OSD_FONT_HEIGHT*19-30;//426
//        region[2].osd_h = 417;//426
        region[2].osd_h = OSD_FONT_HEIGHT*16-10;//374
        osd_create_region1(&region[2], 24,  42+4, NULL,OSD_FORMAT_16COLOR,OSD_INTERLACED);

    }
    else*/
    {
        region[2].osd_w = 38*8;
        region[2].osd_h = OSD_FONT_HEIGHT*16-10;//374
#ifdef BBK_DVD
        osd_create_region1(&region[2], 24,  42-4, NULL,OSD_FORMAT_16COLOR,OSD_INTERLACED);//axel 2003/11/21 07:19pm
#else
        osd_create_region1(&region[2], 24,  42+4, NULL,OSD_FORMAT_16COLOR,OSD_INTERLACED);//axel 2003/11/21 07:19pm
#endif    
    }
    SetOsdCol(2,2,0,0x1e1e1e00);

    header_id = NORMAL_HEADER;
    region[1].osd_w = 36*4;
    region[1].osd_h = OSD_FONT_HEIGHT;
#ifdef BBK_DVD
    osd_create_region1(&region[1], 32,  30-4, &region[2],OSD_FORMAT_4COLOR,OSD_INTERLACED);//axel 2003/11/21 07:19pm    
#else
    osd_create_region1(&region[1], 32,  30+4, &region[2],OSD_FORMAT_4COLOR,OSD_INTERLACED);//axel 2003/11/21 07:19pm    
#endif

    header_id = SETUP_HEADER;
    region[0].osd_w = 38*8;
    region[0].osd_h = OSD_FONT_HEIGHT;
#ifdef BBK_DVD
    osd_create_region1(&region[0], 26,  16-4, &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);//axel 2003/11/21 07:19pm
#else
    osd_create_region1(&region[0], 26,  16+4, &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);//axel 2003/11/21 07:19pm
#endif

    osd_active_regions = 3;
    osd_init__();
}
#endif

#if 0//def SUPPORT_APOGEE_AMP  //xyy 2003-8-30 11:59
/*
    {29*8,(OSD_FONT_HEIGHT+8)*7,64,  64+4,SETUP_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 3
    {29*8,OSD_FONT_HEIGHT+12,   64,  46+4,SETUP_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 2
    {36*4,OSD_FONT_HEIGHT,      32,  34,  NORMAL_HEADER,OSD_FORMAT_4COLOR,OSD_INTERLACED},  // 1
    {38*8,OSD_FONT_HEIGHT,      24+2,20,  SETUP_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 0
*/
void osd_init_apogeeAmpVol(void)
{
    osd_puts("osd_init_ampvol\n");
    __osd_init();    

    header_id = SETUP_HEADER;

    // setup region 2

    region[3].osd_w = 56*4;
//    region[3].osd_h = (OSD_FONT_HEIGHT+5)*9+2;  //huziqin 2004-2-26
    region[3].osd_h = (OSD_FONT_HEIGHT+5)*7+2;  //xyy 2004-3-8 15:19
    osd_create_region1(&region[3], 65,  44+4+40, NULL,OSD_FORMAT_16COLOR,OSD_INTERLACED);

//    SetOsdCol(3,3,0,0x1e1e1e00);

    header_id = NORMAL_HEADER;
    region[2].osd_w = 36*4;
    region[2].osd_h = OSD_FONT_HEIGHT;
    osd_create_region1(&region[2], 32,  42+4, &region[3],OSD_FORMAT_4COLOR,OSD_INTERLACED);

//    header_id = NORMAL_HEADER;
    region[1].osd_w = 36*4;
    region[1].osd_h = OSD_FONT_HEIGHT;
    osd_create_region1(&region[1], 32,  30+4, &region[2],OSD_FORMAT_4COLOR,OSD_INTERLACED);    

    header_id = SETUP_HEADER;
    region[0].osd_w = 38*8;
    region[0].osd_h = OSD_FONT_HEIGHT;
    osd_create_region1(&region[0], 26,  16+4, &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);

    osd_active_regions = 3;
    osd_init__();

}
#endif


#ifdef DVB1000_NON_OS

#ifdef DVB_SIMPLE_UI
const   _t_osd_hdr osd_hdr_dvb_menu[] = {
//    {38*8, OSD_FONT_HEIGHT*15, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#ifdef DISP_REGION_BOTTOM
    {360, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
#endif
    {33*8, 300, 50, 50, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 2
    {36*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
#ifndef OSD_BMP_DISPLAY
    {38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#else
    {360, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#endif//OSD_BMP_DISPLAY

};
#elif defined(DVB1000_OSD_MENU)
const   _t_osd_hdr osd_hdr_dvb_menu[] = {
//    {38*8, OSD_FONT_HEIGHT*15, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    {38*8 + 20 , OSD_FONT_HEIGHT * 16, 10, 28, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 2
    //{36*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
    //{38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0

};
#ifdef SUPPORT_TELETEXT
const   _t_osd_hdr osd_hdr_dvb_ttx_menu[] = {
    {TTX_REGION_W , TTX_REGION_H, TTX_REGION_X, TTX_REGION_X, TTX_HEADER, OSD_FORMAT_256COLOR,  OSD_INTERLACED},     // 0
};
#endif
#ifdef SUPPORT_SUBTITLE
const   _t_osd_hdr osd_hdr_dvb_subtitle_menu[] = {
    {SUBTITLE_REGION_W , SUBTITLE_REGION_H, SUBTITLE_REGION_X, SUBTITLE_REGION_Y, SUBTITLE_HEADER, OSD_FORMAT_256COLOR,  OSD_INTERLACED},     // 0
};
#endif
#endif

void osd_init_dvb_menu(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_init_regions(sizeof(osd_hdr_dvb_menu)/sizeof(osd_hdr_dvb_menu[0]), (_t_osd_hdr *)&osd_hdr_dvb_menu);
    #ifdef DVB_OSD_MENU_VER1
    SetOsdCol(0, 0, 14, 0x0080fff0);
    SetOsdCol(0, 0, 8,  0xC8C8C8ff);
    SetOsdCol(0, 0, 0, 0x1e1e1e00);
    #else
    SetOsdCol(0, 0, 0, 0x1e1e1e00); //TRANS_CLR
    SetOsdCol(0, 0, 6, 0x98d28de0); //LIGHT BLUE
    SetOsdCol(0, 0, 8, 0xc0c0c0e0);//Gray CLR
    //SetOsdCol(0, 0, 8, 0xc8f589e0);//Gray CLR for Bg
    SetOsdCol(0, 0, 9, 0x808080ff);
    SetOsdCol(0, 0, 10, 0xC8C8C8ff); //List Bg
    #endif
} 
#ifdef SUPPORT_TELETEXT
void osd_init_dvb_ttx_menu(void)
{
	printf("init DVB teletext osd \n");
    osd_init_regions(sizeof(osd_hdr_dvb_ttx_menu)/sizeof(osd_hdr_dvb_ttx_menu[0]), (_t_osd_hdr *)&osd_hdr_dvb_ttx_menu);
} 
#endif //SUPPORT_TELETEXT

#ifdef SUPPORT_SUBTITLE
void osd_init_dvb_subtitle_menu(void)
{
    int i,j;
    int yy;
    UINT8 *pp;
    UINT8  *pTopLine, *pBtmLine;

    osd_init_regions(sizeof(osd_hdr_dvb_subtitle_menu)/sizeof(osd_hdr_dvb_subtitle_menu[0]), (_t_osd_hdr *)&osd_hdr_dvb_subtitle_menu);

     pTopLine = (UINT8 *)get_osdbuf_region_ptr(0,0); 
    pBtmLine = (UINT8 *)get_osdbuf_region_ptr(0,1);

    for(i=SUBTITLE_REGION_Y;i<SUBTITLE_REGION_H;i++)
        {
            yy = (p_scan) ? i: i>>1;
            pp = (i&1) ? pBtmLine : pTopLine;

            if(p_scan)
                memset(pp+i*SUBTITLE_REGION_W,255,SUBTITLE_REGION_W);
            else
                memset(pp+(i/2)*SUBTITLE_REGION_W,255,SUBTITLE_REGION_W);
        }    

        osd_tog_region(0, OSD_ON);
        SetOsdCol(0, 0, 255, 0xaaaaaa00);

} 
#endif//SUPPORT_SUBTITLE
#endif //DVB_T


#ifdef SUPPORT_REP_READ
const   _t_osd_hdr osd_hdr_rep_read[] = {
#ifdef DISP_REGION_BOTTOM
    {360, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
#endif
    {READ_REG_W*8, READ_REG_H, 80, 48, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 2
    {36*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
#ifndef OSD_BMP_DISPLAY
    {38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#else
    {360, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#endif//OSD_BMP
};

void osd_init_rep_reading(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_init_regions(sizeof(osd_hdr_rep_read)/sizeof(osd_hdr_rep_read[0]), (_t_osd_hdr *)&osd_hdr_rep_read);
} 
void osd_print_read_eq(UINT8 r, const BYTE *p)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

   UINT16  iWidth;
    UINT16  i,j,iBlock,step,k;
    UINT16  *pTopLine,*pBtmLine;
    UINT16  unColor;    
    BYTE    bChannelVal[14];    //byte 13 is garbage

    iWidth = region[r].osd_w/2;

    //osd_puts("print eq\n");
    
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
                //pTopLine[i+2] =  unColor;
                if (p_scan==0)
                {
                    pBtmLine[i]   =  unColor;
                    pBtmLine[i+1] =  unColor;
                    //pBtmLine[i+2] =  unColor;
                }
            }
            //pTopLine+=iWidth;    
            //if (p_scan==0) pBtmLine+=iWidth;
        }
        
       //step 2 line
        pTopLine+=(iWidth*step);    
        if (p_scan==0) pBtmLine+=(iWidth*step);
    }  
}

#endif
//
// fill a rectangular region using bk-Color
//
void
osd_draw_region_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor, BYTE r)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_draw_hline_region(xStart, xStart+xLen, yStart, bkColor, yLen, r);

#if 0
    BYTE        *pTopLine, *pBtmLine;
    UINT32      iDispLoc, iOffSet;
    UINT32      i, j;
    int         iRegionWidth = region[r].osd_w;
    BYTE        c;
        
    osd_tog_region(r, OSD_ON);
    
    //initialize buffer start
    pTopLine = get_osdbuf_region_ptr(r,0);
    pBtmLine = get_osdbuf_region_ptr(r,1);
    
    if(p_scan==0)
    {
       yLen>>=1;
       yStart>>=1;
    }
    
    iDispLoc = (yStart * iRegionWidth) + (xStart/2);
    
    c = bkColor | (bkColor<<4);
    
    //draw horizontal line   
       
    for (j=0; j<yLen; j++) {
        //array index(in Byte)
        iOffSet = iDispLoc + j*iRegionWidth;
        
        for (i=0; i<xLen/2; i++) {
            pTopLine[iOffSet+i] = c;
            pBtmLine[iOffSet+i] = c;
        }
    }
    
    timeout_osd[r] = 0;
#endif
}


// replace bkColor with destColor
void
osd_replace_rect_color(BYTE bkColor, BYTE destColor)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    SetOsdCol(0,0,bkColor,palette_16color_setup[destColor]);
}

#ifdef ROLL_SHOW_SETUP
extern int GBM_run_setupmenu_flag;
#endif

void
osd_draw_button_outline(int x1, int y1, int x2, int y2, int bDown, unsigned mask, int r)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    unsigned    uBorderC, xBorderC, dBorderC;

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
    
    #ifdef ROLL_SHOW_SETUP//zhaoyanhua add 2003-8-18 11:24
    if ((!GBM_run_setupmenu_flag) && !(full_scrn&CUSTM) && !(full_scrn&SOUND))      //gerry modified 3D_SOUND,2004-4-12 13:35
    {
        if (mask & (1<<3)) 
        {
            //draw upper border
            MoveRect2buf(x1+0,x2-0,y1+0,xBorderC,1,r);
            MoveRect2buf(x1+1,x2-1,y1+1,uBorderC,1,r);
            MoveRect2buf(x1+2,x2-2,y1+2,uBorderC,1,r);
            MoveRect2buf(x1+3,x2-3,y1+3,xBorderC,1,r);
        }
    
        if (mask & (1<<2)) 
        {
            //draw rear border
            MoveRect2buf(x1+3,x2-3,y2-3,xBorderC,1,r);
            MoveRect2buf(x1+2,x2-2,y2-2,dBorderC,1,r);
            MoveRect2buf(x1+1,x2-1,y2-1,dBorderC,1,r);
            MoveRect2buf(x1+0,x2-0,y2-0,xBorderC,1,r);
        }
    
        //draw left border
        if (mask & (1<<1)) {
            MoveRect2buf(x1+0, y1+0, y2-0, xBorderC, 1, r);
            MoveRect2buf(x1+1, y1+1, y2-1, uBorderC, 1, r);
            MoveRect2buf(x1+2, y1+2, y2-2, uBorderC, 1, r);
            MoveRect2buf(x1+3, y1+3, y2-3, xBorderC, 1, r);
        }

        //draw right border
        if (mask & (1<<0)) {
            MoveRect2buf(x2-0, y1+0, y2-0, xBorderC, 1, r);
            MoveRect2buf(x2-1, y1+1, y2-1, dBorderC, 1, r);
            MoveRect2buf(x2-2, y1+2, y2-2, dBorderC, 1, r);
            MoveRect2buf(x2-3, y1+3, y2-3, xBorderC, 1, r);
        }
    }
    else
    {
        if (mask & (1<<3)) 
        {
        //draw upper border
        osd_draw_hline_region(x1+0,x2-0,y1+0,xBorderC,1,r);
        osd_draw_hline_region(x1+1,x2-1,y1+1,uBorderC,1,r);
        osd_draw_hline_region(x1+2,x2-2,y1+2,uBorderC,1,r);
        osd_draw_hline_region(x1+3,x2-3,y1+3,xBorderC,1,r);
    }
    
        if (mask & (1<<2)) 
        {
            //draw rear border
            osd_draw_hline_region(x1+3,x2-3,y2-3,xBorderC,1,r);
            osd_draw_hline_region(x1+2,x2-2,y2-2,dBorderC,1,r);
            osd_draw_hline_region(x1+1,x2-1,y2-1,dBorderC,1,r);
            osd_draw_hline_region(x1+0,x2-0,y2-0,xBorderC,1,r);
        }
    
        //draw left border
        if (mask & (1<<1)) {
            osd_draw_vline_region(x1+0, y1+0, y2-0, xBorderC, 1, r);
            osd_draw_vline_region(x1+1, y1+1, y2-1, uBorderC, 1, r);
            osd_draw_vline_region(x1+2, y1+2, y2-2, uBorderC, 1, r);
            osd_draw_vline_region(x1+3, y1+3, y2-3, xBorderC, 1, r);
        }

        //draw right border
        if (mask & (1<<0)) {
            osd_draw_vline_region(x2-0, y1+0, y2-0, xBorderC, 1, r);
            osd_draw_vline_region(x2-1, y1+1, y2-1, dBorderC, 1, r);
            osd_draw_vline_region(x2-2, y1+2, y2-2, dBorderC, 1, r);
            osd_draw_vline_region(x2-3, y1+3, y2-3, xBorderC, 1, r);
        }
    }
    #else
    
    if (mask & (1<<3)) {
        //draw upper border
        osd_draw_hline_region(x1+0,x2-0,y1+0,xBorderC,1,r);
        osd_draw_hline_region(x1+1,x2-1,y1+1,uBorderC,1,r);
        osd_draw_hline_region(x1+2,x2-2,y1+2,uBorderC,1,r);
        osd_draw_hline_region(x1+3,x2-3,y1+3,xBorderC,1,r);
    }
    
    if (mask & (1<<2)) {
        //draw rear border
        osd_draw_hline_region(x1+3,x2-3,y2-3,xBorderC,1,r);
        osd_draw_hline_region(x1+2,x2-2,y2-2,dBorderC,1,r);
        osd_draw_hline_region(x1+1,x2-1,y2-1,dBorderC,1,r);
        osd_draw_hline_region(x1+0,x2-0,y2-0,xBorderC,1,r);
    }
    
    //draw left border
    if (mask & (1<<1)) {
        osd_draw_vline_region(x1+0, y1+0, y2-0, xBorderC, 1, r);
        osd_draw_vline_region(x1+1, y1+1, y2-1, uBorderC, 1, r);
        osd_draw_vline_region(x1+2, y1+2, y2-2, uBorderC, 1, r);
        osd_draw_vline_region(x1+3, y1+3, y2-3, xBorderC, 1, r);
    }

    //draw right border
    if (mask & (1<<0)) {
        osd_draw_vline_region(x2-0, y1+0, y2-0, xBorderC, 1, r);
        osd_draw_vline_region(x2-1, y1+1, y2-1, dBorderC, 1, r);
        osd_draw_vline_region(x2-2, y1+2, y2-2, dBorderC, 1, r);
        osd_draw_vline_region(x2-3, y1+3, y2-3, xBorderC, 1, r);
    }
    #endif//ROLL_SHOW_SETUP
}


//
// osd_draw_setup_button    : draw a setup-item button
//
//  input   :   xStart      -> x start position to draw
//              yStart      -> y start position to draw
//              xLen        -> record length
//              color       -> button color
//              bDown       -> UP(0) or DOWN(1)
//
//  notes   :
//
void osd_draw_setup_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

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
    yNew = yStart * SETUP_BTN_HEIGHT;
    
    #ifdef ROLL_SHOW_SETUP//zhaoyanhua add 2003-8-18 11:44
    if ((!GBM_run_setupmenu_flag) && !(full_scrn&CUSTM) && !(full_scrn&SOUND))          //gerry modified 3D_SOUND,2004-4-12 13:35
        MoveRect2buf(xNew, xNew+xLen*16, yNew, color, SETUP_BTN_HEIGHT, SETUP_REGION );
    else
    osd_draw_rect(xNew, yNew, xLen*16, SETUP_BTN_HEIGHT, buttonC);
    
    #else
    
    osd_draw_rect(xNew, yNew, xLen*16, SETUP_BTN_HEIGHT, buttonC);
    #endif
//    #ifndef   SETUP_COLOR_TYPE1       //wangfeng 2003-08-29 17:06
#if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)&& !defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-5 12:32
    #ifndef SETUP_NOBUTTON       //2004-4-17 10:22张宇M
    osd_draw_button_outline(xNew, yNew, xNew+xLen*16-1, yNew+SETUP_BTN_HEIGHT-1, bDown, 0x0f, SETUP_REGION);
    #endif
#endif
#endif
}


void
osd_draw_region_boarder(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, UINT8 up_down, BYTE r)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    osd_draw_button_outline(xStart,yStart,xEnd,yEnd,up_down,0x0f,r);
}


void osd_draw_sound_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    BYTE        buttonC;
    UINT32      xNew, yNew;    
    
    buttonC = color;    
    xNew = xStart * 16;
    yNew = yStart * SETUP_BTN_HEIGHT+12;    
    osd_draw_region_rect(xNew, yNew, (UINT32)(xLen*16), (UINT32)(SETUP_BTN_HEIGHT), buttonC,3);    
    osd_draw_region_boarder(xNew,yNew,(UINT32)(xNew+xLen*16),(UINT32)(yNew+SETUP_BTN_HEIGHT-2),bDown,3);
}

#ifdef SUPPORT_REP_READ //Maoyong 2004.06.03
void osd_draw_read_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown)
{
    BYTE        buttonC;
    UINT32      xNew, yNew;    
    
    buttonC = color;    
    xNew = xStart * 16;
    yNew = yStart * SETUP_BTN_HEIGHT + 8;    
    osd_draw_region_rect(xNew, yNew, (UINT32)(xLen*16), (UINT32)(SETUP_BTN_HEIGHT), buttonC,READ_REGION);    
    osd_draw_region_boarder(xNew,yNew,(UINT32)(xNew+xLen*16),(UINT32)(yNew+SETUP_BTN_HEIGHT-2),bDown,READ_REGION);
}
#endif

#if defined(DVB1000_OSD_MENU)||defined(DVB_MENU_TYPE1) //Maoyong 2004-10-18 15:15
//Draw flat button, no border
void osd_draw_dvbmenu_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown)
{
    BYTE        buttonC;
    UINT32      xNew, yNew;    
    
    buttonC = color;    
    xNew = xStart * 16;
    yNew = yStart * SETUP_BTN_HEIGHT + 8;    
    #if defined(DVB_OSD_MENU_VER1)||defined(DVB_MENU_TYPE1)
    osd_draw_region_rect(xNew, yNew, (UINT32)(xLen*16), (UINT32)(SETUP_BTN_HEIGHT), buttonC, DVBMENU_REGION);    
    osd_draw_region_boarder(xNew,yNew,(UINT32)(xNew+xLen*16),(UINT32)(yNew+SETUP_BTN_HEIGHT-2),bDown, DVBMENU_REGION);
    #else
    osd_draw_region_rect(xNew + 4, yNew + 4, (UINT32)(xLen*16 - 8), (UINT32)(SETUP_BTN_HEIGHT - 8), buttonC, DVBMENU_REGION);    
    #endif
}
//Draw button with light border
void osd_draw_dvbmenu_border_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    BYTE        buttonC;
    UINT32      xNew, yNew;    
    buttonC = color;    
    xNew = xStart * 16;
    yNew = yStart * SETUP_BTN_HEIGHT + 8;    
    osd_draw_region_rect(xNew + 2, yNew + 2, (UINT32)(xLen*16 - 4), (UINT32)(SETUP_BTN_HEIGHT - 4), buttonC, DVBMENU_REGION);    
    osd_draw_button_outline(xNew + 2,yNew + 2,(UINT32)(xNew+xLen*16 - 4),(UINT32)(yNew+SETUP_BTN_HEIGHT - 4),bDown, 0x0F, DVBMENU_REGION);
}
#endif


//
// Bytes/Line = 37*16*4/8 = 296
//
void osd_Move2OSD0(BYTE iLine)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

#ifndef SDRAM_16Mb_Mode
    UINT32  *buf;
#endif
    UINT32  *pTopLine, *pBtmLine;
    BYTE    i,end,max_remain,step;
    UINT32  j, k;    
    
    
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
    //}
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
            MoveRegion(disp_region,10,520);
		else if(getVPP_TVsystem())
			MoveRegion(disp_region, 10, 260);
		else if (p_scan)
            MoveRegion(disp_region,10,432);
		else
			MoveRegion(disp_region,10,216);
	}		
#endif//DISP_REGION_BOTTOM
}

/*
void osd_ClearOSD0(BYTE iSLine, BYTE iELine)
{
    UINT32  *pTopLine, *pBtmLine;
    BYTE    i;
    UINT32  j;
    
    //initialize buffer start
    pTopLine = (UINT32 *)(((BYTE *)get_osdbuf_baseptr()) + (region[0].osd_header[0]+OSD_DATA_OFFSET(region[0].osd_format))*32);
    pBtmLine = (UINT32 *)(((BYTE *)get_osdbuf_baseptr()) + (region[0].osd_header[1]+OSD_DATA_OFFSET(region[0].osd_format))*32);
    
    for (i=(iSLine/2); i<(iELine/2); i++) {
        for (j=0; j<74; j++) {
            //top area
            pTopLine[74*i+j] = 0xffffffff;
            //bottom area
            pBtmLine[74*i+j] = 0xffffffff;                        
        }        
    }        
}*/    
void restore_osd_msg(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

	#ifdef DVB1000_OSD_MENU	//Maoyong added 2005-3-7 16:36g 
	if(system_state == SYSTEM_TS)
	{
		if(full_scrn)	//just when no menu, can do restore osd
			return;
	}
	#endif

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
        
       
#ifdef USE_AMP_MUTE //chenzhao20050926
        if (user_amp_mute)     
#else//#ifdef USE_AMP_MUTE
        if (user_mute)
#endif//#ifdef USE_AMP_MUTE       
            PrintOsdMsg(STR_OS_MUTE,REGION1, 0, 0);
        
        if( ( play_state == VCD_STATE_PAUSE ) && !( full_scrn & PROGRAM ) )//terry,2004/2/4 06:36PM, 2004/12/27 yltseng
            PrintOsdMsg(STR_OS_PAUSE,REGION1, 0, 0);
    }
}


//
// FUNCTION :   polling_osd(diff)
//
// DESCRIPTION
// checking OSD timeout, every time 'diff' RTC ticks is subtracted
// from OSD timeout.
//
// NOTES: if timeout value is 0 then this check is ignored.
//
void
polling_osd(int diff)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    int    i;
    
    if(diff<0) return;
    else if(diff>100)
    diff=100;
    
    for (i=0;i<REGIONS_ACTIVE;i++)
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
      			  // polling_BCtimer();
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
//#if 0//def SDRAM_16Mb_Mode
//for avoid stop->play "SEQ PLAY" can't fade away.nono 2004-5-6 2:42
//                    if (play_state!=VCD_STATE_STOP)
//#endif
//                    {
//                    #ifdef OP_UI
//                        PrintOsdMsg(RegionOnOff[i][2],i,0,0x0f);//clear corresponding bmp.
//                    #else    
                        osd_tog_region(i, OSD_OFF);
//                    #endif
//                    }
                    
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
                        else if((system_state == SYSTEM_OPEN)&&(OpenFlag==1))
                        {   
                            if((!full_scrn)|| ( !safe_on))
                            PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);//zhaoyanhua add 2003-12-2 17:29
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
                        #ifndef SHOW_ANGLE_MARK_TEMP    //hongfeng add 2005-09-20
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


void    osd_tog_region(BYTE r, int mode)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

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
    
#if    SUPPORT_OSD
    regs0->osd_en = 1;
#else
    regs0->osd_en = 0;
#endif
}


void show_angle_osd(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

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
            //if((rep_mode==REPEAT_TRACK)||(rep_mode==REPEAT_DISC))           
            //    delay_srv_10ms(100);//nono marked 2003-9-6 10:17              
      
            PrintOsdMsg(STR_OS_ANGLE,REGION2,0,0);
        } else if (RegionOnOff[REGION2][2]==STR_OS_ANGLE)
        {
            osd_tog_region(2,OSD_OFF);
        }
    }
        else{
            if( (get_angle_Ns())&&(!UOP_check(UOP_AG_CHG)) ) {
                    //if((rep_mode==REPEAT_TRACK)||(rep_mode==REPEAT_DISC))           
                    //    delay_srv_10ms(100);//nono marked 2003-9-6 10:17              
      
                } else if (RegionOnOff[REGION2][2]==STR_OS_ANGLE)
                {
                     osd_tog_region(2,OSD_OFF);
                }
        }
    #else
            if( (get_angle_Ns())&&(!UOP_check(UOP_AG_CHG)) ) {
                //if((rep_mode==REPEAT_TRACK)||(rep_mode==REPEAT_DISC))           
                //    delay_srv_10ms(100);//nono marked 2003-9-6 10:17              
           
                #if defined(SHOW_ANGLE_MARK_TEMP)
                PrintOsdMsg(STR_OS_ANGLE,REGION2,5,0);
                #else//SHOW_ANGLE_MARK_TEMP
                PrintOsdMsg(STR_OS_ANGLE,REGION2,0,0);
                #endif//SHOW_ANGLE_MARK_TEMP
      
            } else if (RegionOnOff[REGION2][2]==STR_OS_ANGLE)
            {
                osd_tog_region(2,OSD_OFF);
            }
        #endif
    }
}


#ifdef SUPPORT_PLAYBACK_ICON
#include "Icon.h"
#endif
#ifdef DIV_GOTO_DISPLAY//zhaoyanhua add 03-11-2 14:18
extern void ClearRegion2(void);
#endif

/*//terry,2004/1/26 01:05PM
*            vcd   dvd1   dvd2
* mode        2     2      2  
* mode2       2     3      4
* s_len(0-8)  6     7      7
* s_len(9-16) 7     8      8
*      
*/

static inline void chg_anti_pos(UINT8 mode2,UINT8 s_len)
{//edit prog id
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

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
       //if(s_len==8)  antic_begin++;
       break;
  }   
  printf("2.antic_begin:%d antic_end:%d\n",antic_begin,antic_end);
}

/*
#ifdef SUPPORT_REP_READ                
        case 10://id cat id
            //strcpy(osdbuf,_OsdMessegeFont1[osd_id][osd_font_mode]);
            strcpy(osdbuf,_OsdMessegeFont1[osd_font_mode][osd_id]);
            //strcpy(RegionValStr[r],_OsdMessegeFont1[val][osd_font_mode]);
            strcpy(RegionValStr[r],_OsdMessegeFont1[osd_font_mode][val]);
            strcat1(osdbuf," ");                 
            strcat1(osdbuf,RegionValStr[r]);    
            if(t)
            {             
                psprintf(RegionValStr[r],"[%d]",t);
                strcat1(osdbuf,RegionValStr[r]);
                t=0;                 
            }
            break;
            
        case 9://[?]
            psprintf(osdbuf,"[%d]",val);    
            mode=1;//anti...            
            break;
#endif                
*/

/*        case 12://display chapter, title use , id cat ":\n\n %d "
            //psprintf(osdbuf,"%s: %2d ",_OsdMessegeFont1[osd_id][osd_font_mode],val); 
            psprintf(osdbuf,"%s: %2d ",_OsdMessegeFont1[osd_font_mode][osd_id],val); 
            break;
        case 11://id cat [?]                
            //psprintf(osdbuf,"%s  [%d]",_OsdMessegeFont1[osd_id][osd_font_mode],val+1);    
            psprintf(osdbuf,"%s  [%d]",_OsdMessegeFont1[osd_font_mode][osd_id],val+1);
            break;*/

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

#if 0//def SUPPORT_APOGEE_AMP
#define NOT_SHOW_OSD (VK|DT|MG|MARK|GOTO|SCORE|APOGEEAMPVOL)//xyy 2004-3-4 15:35
#else
#define NOT_SHOW_OSD (VK|DT|MG|MARK|GOTO|SCORE)
#endif


void PrintOsdMsg(UINT32 id,UINT8 r,int t,BYTE mode)
{ 
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

#ifdef SUPPORT_16BIT_OSD
    if(OSD_buffer_16bit) {return;}
#endif	
    BYTE sub_r,i,mode2,s_len=0,j,osd_id;
    UINT16 val;

    osd_printf("PrintOsdMsg(%d,%d,%d,%d)\n", id, r, t, mode);
    
    // mode2    0:sw region on 1:sw region off 2:sw region anti
    // id       1st~3th bytes: numeric use  
    //          4th byte: osd string id
    // r        MSB 4bits:software region
    //          LSB 4bits:hardware region
    // t        time unit (second)
   
   
#ifdef SDRAM_16Mb_Mode   //2004-5-5 10:44?宇P
    if( (id==STR_OS_STOP)&&(system_state==SYSTEM_NODISC) )
    {
      return;
    }
#endif

#ifdef NEW_STYLE_SETUP
    if( (id==STR_OS_STOP)&&(setup_state==1) )
    {
        return;
    }
#endif//NEW_STYLE_SETUP 

/*
    Maoyong Marked: 
    for Bug: When PBC ON, "STOP" then PLAY, will show "PBC", not
            "MENUPLAY", because you have change in ircmd.c, don't need
             to change MENUPLAY to PBC again
*/
#if defined(VCD_SHOW_PBC_NOT_MENUPLAY)&&defined(TONIC_DVD)//20040206 FOR TONIC
    if(cd_type_loaded==CDVCD20||cd_type_loaded==CDSVCD)
    if((id&0xff)==STR_OS_MENUPLAY)
    {
        id&=0xffffff00;
        id|=STR_OS_PBC;
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
    //val=id>>8;
#ifdef NEWSTYLE_WINDOW //terry,2003/8/4 03:24PM   
    if(full_scrn&MESSAGE)
        memset(osdbuf,0,100);
#endif
        
#ifdef DOUBLE_TITLE //susu 2003-8-26 19:41
    if(full_scrn&DOUBLETITLE)
        memset(osdbuf,0,sizeof(osdbuf));
#endif
     
    if(full_scrn)
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
        case 8://cat ?
            //strcpy(osdbuf,_OsdMessegeFont1[osd_id][osd_font_mode]);
            strcpy(osdbuf,_OsdMessegeFont1[osd_font_mode][osd_id]);
            if( val>1) {
            #if !defined( TWELVE_ZOOMFACTORS )||!defined(OP_JPEG_ZOOM_LEVEL)  //libing 2005-6-9 13:57//fengjl add 2004-05-05 23:41
                psprintf(RegionValStr[r]," %d",val-1);            
            #endif
            } else {
                //psprintf(RegionValStr[r],": %s",_OsdMessegeFont1[STR_OS_OFF][osd_font_mode]);
                psprintf(RegionValStr[r],": %s",_OsdMessegeFont1[osd_font_mode][STR_OS_OFF]);
            }
            strcat1(osdbuf,RegionValStr[r]);
            break;
        case 7://cat "1/?"
            //strcpy(osdbuf,_OsdMessegeFont1[osd_id][osd_font_mode]);
            strcpy(osdbuf,_OsdMessegeFont1[osd_font_mode][osd_id]);
            psprintf(RegionValStr[r]," 1/%d",val);                
            strcat1(osdbuf,RegionValStr[r]);
            break;                            
        case 6://cat "X ?"
            //strcpy(osdbuf,_OsdMessegeFont1[osd_id][osd_font_mode]);
            strcpy(osdbuf,_OsdMessegeFont1[osd_font_mode][osd_id]);

            psprintf(RegionValStr[r]," X %d",val);                
            //                psprintf(RegionValStr[r]," X %d",val);                
            strcat1(osdbuf,RegionValStr[r]);
            break;            
        case 4://cat status on ,double click
            //id LSB String  cat ":"  cat "[id MSB string]"
            //strcpy(osdbuf,_OsdMessegeFont1[osd_id][osd_font_mode]);            
            
#ifdef NEWSTYLE_WINDOW//terry,2003/8/4 03:24PM
        if( (full_scrn&MESSAGE)==0 )
#endif          

#ifdef DOUBLE_TITLE //susu 2003-8-26 19:19
        if( (full_scrn&DOUBLETITLE)==0 )
            #endif              
        {            
            strcpy(osdbuf,_OsdMessegeFont1[osd_font_mode][osd_id]);
            strcat1(osdbuf,":");
            s_len=strlen(osdbuf);                                
            j=0;
            for(i=0;i<s_len;i++)
            {                                
                UINT8 c;
                const UINT8* p;
                
                c = osdbuf[i];
                p = get_font_entry(0,c);
                RegionStr[r][sub_r][i]=c;                            
                if(p!=NULL)
                {
                    if(p[0]==0x20)                        
                        j++;
                }                
            }

#ifndef SDRAM_16Mb_Mode                
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
                    #ifdef SDRAM_16Mb_Mode
                    #define MAX_ENG_WORDS 2//nono 20031210
                    
                    psprintf(RegionValStr[r],"[%d",(t>>8)+1);
                    if (!IsOSDChinese()||((linebuf[0]>='A')&&(linebuf[0]<='Z'))) 
                    {
                        *(p+MAX_ENG_WORDS) = '\0';
                    }
                    else
                    {
                        if(strlen(p)>4)
                        {
                        #if defined(USE_TCHINESE_OSD)//2-10-9 17:51
                            psprintf(p+2,"%s",TCh_yu);
                        #else
                            #ifdef USE_KOREAN_OSD       //clead korean 2003-10-23 
                            psprintf(p+2,"%s",KCh_09);
                            #else
                            psprintf(p+2,"%s",Ch_yu2);
                            #endif
                        #endif
                        
                        }
                       
                    }
                    
                    strcat1(RegionValStr[r], p);    
                    
                    #else
                        psprintf(RegionValStr[r],"[ %d %s",(t>>8)+1,p);
                        
                    #endif//end SDRAM_16Mb_Mode
                        
                        if( (id1)==STR_OS_AUDIO )
                        {
                            strcat1(RegionValStr[r],get_audio_mode());
                        }                            
                    #ifdef NEWSTYLE_WINDOW
                        if(!(full_scrn&MESSAGE)) //xyy 2003-7-29 14:21   
                    #endif                        
                        strcat1(RegionValStr[r],"]");
                    }
                    break;
                case 0x0a://
                    {
                        UINT8 Ns=t>>12;
                        UINT8 N=((t>>8)&0xf)+1;
                        
                        if(N>Ns)
                        {
                            //psprintf(RegionValStr[r],"[ %s ]",Ch_vff);
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
                    //psprintf(RegionValStr[r],"[ %s ]",_OsdMessegeFont1[val][osd_font_mode]);
#ifdef SDRAM_16Mb_Mode                  
                    psprintf(RegionValStr[r],"[%s]",_OsdMessegeFont1[osd_font_mode][val]);
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
                //if(t_disp) //terry,2001/8/8 08:01PM
                //t_disp+=10;
                break;
                case 2://string cat id's string
                    //strcpy(osdbuf,_OsdMessegeFont1[id][osd_font_mode]);
                    strcpy(osdbuf,_OsdMessegeFont1[osd_font_mode][id]);
                    strcat1(RegionValStr[r],osdbuf);
                    strcpy(osdbuf,RegionValStr[r]);
                    break;
                case 1://cat string            
                    //strcpy(osdbuf,_OsdMessegeFont1[id][osd_font_mode]);
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
                case 0://transfer id to string
                    //strcpy(osdbuf,_OsdMessegeFont1[id][osd_font_mode]);
                    strcpy(osdbuf,_OsdMessegeFont1[osd_font_mode][id]);
                    break;
#ifndef  DVDRELEASE
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
        strcat1(osdbuf, " ");
        strcat1(osdbuf, OSD_ICON_PREV);
        break;

    case STR_OS_NEXT:
        strcat1(osdbuf, " ");
        strcat1(osdbuf, OSD_ICON_NEXT);
        break;
    
    case STR_OS_PLAY:
        strcat1(osdbuf, " ");
        strcat1(osdbuf, OSD_ICON_PLAY);
        break;

    case STR_OS_PAUSE:
        strcat1(osdbuf, " ");
        strcat1(osdbuf, OSD_ICON_PAUSE);
        break;

    case STR_OS_STEP:
        strcat1(osdbuf, " ");
        strcat1(osdbuf, OSD_ICON_STEP);
        break;

    case STR_OS_STOP:
        strcat1(osdbuf, " ");
        strcat1(osdbuf, OSD_ICON_STOP);
        break;

    case STR_OS_PRE_STOP:
        strcat1(osdbuf, " ");
        strcat1(osdbuf, OSD_ICON_PRE_STOP);
        break;

    case STR_OS_FB:
        strcat1(osdbuf, " ");
        strcat1(osdbuf, OSD_ICON_FB);
        break;

    case STR_OS_FF:
        strcat1(osdbuf, " ");
        strcat1(osdbuf, OSD_ICON_FF);
        break;

#ifndef OP_BKSLOW_NO_ICON
    case STR_OS_SB:
        strcat1(osdbuf, " ");
        strcat1(osdbuf, OSD_ICON_SB);
        break;
#endif

    #ifdef TONIC_DVD
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
            sw_region_len=9;        
        else
            sw_region_len=12;
        
        sub_r--;
        
        for(i=0;i<MAX_SW_REGION;i++)
        {                
            if((i!=sub_r)&&(RegionStr[r][i][0]==0))
            {
                for(j=0;j<sw_region_len;j++)
                    RegionStr[r][i][j]=0x20;//'\n';//space char
                
                RegionStr[r][i][j]=0;                    
            }        
        }
        
        if(mode2!=1)
        {//0:on                    
            s_len=strlen(osdbuf);                                
            j=0;
            for(i=0;i<s_len;i++)
            {    
                UINT8 c;
                const UINT8* p;
                c=osdbuf[i];
                p=get_font_entry(0,c);
                RegionStr[r][sub_r][i]=c;            
                if(p!=NULL)
                {
                    if(p[0]==0x20)
                        j++;
                }                
            }
                
            if( (sw_region_len-s_len-j)>0 )
                for(i=0;i<(sw_region_len-s_len-j);i++)
                {                
                    RegionStr[r][sub_r][i+s_len]=0x20;//'\n';                                            
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
        ClearRegion2();
        osd_DrawRegionString(0,0,osdbuf,7,10,2);
        //osd_DrawRegionString(0,0,osdbuf,7,0,2);
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

    //osd_printf("mode2:%x %x %x\n",antic_begin,antic_end,mode2);   
   {
        if( (ir_osd_post_show==0)||(r!=1)||(full_scrn&PROGRAM) ) 
    {           
        osdshow(r,osdbuf);//2-8-1 20:15
    } else {
        //terry,0512,move to ir.c  
        ir_osd_post_show=2;
        strcpy(osd_buf,osdbuf);//too bad...
    }   
  }
    //#ifndef DVDRELEASE//2-7-29 16:00
    //osd_print_region1(&region[r],osdbuf);    
    //#endif
    
    timeout_osd[r]=t*OSD_TIMEOUT;   
    RegionOnOff[r][1]=mode;
    RegionOnOff[r][2]=osd_id;   
    RegionOnOff[r][3]=val;
    //osd_printf("printosdmsg:%x %s\n",r,osd_buf);
}


void osdshow(UINT8 r,char *buf)//2-8-1 20:15
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    BYTE y_start,x_start;
    //osd_printf("osdshow(%d,%x)\n", r, buf);

    #ifdef OSD_BMP_REGION1
    //region1 info x start pixel:x_start*4;y strat pixel:y_start
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

        osd_print_region2(&region[r],buf,y_start,x_start);    
        osd_tog_region(r,OSD_ON); 
    }
}


//void PrintOsdMsg2(BYTE r, int t) //Jeff 20010830
//{  
//    osd_tog_region(r, OSD_ON);
//    osd_print_regionEQ(&region[r], osdbuf);
//    timeout_osd[r] = t*OSD_TIMEOUT;
//}


//
// ClearOsdMsg
//
void ClearOsdMsg(int i)
{    
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    #ifdef SUPPORT_FUNCTION_MENU
    if ((full_scrn&SETUP) || (full_scrn&SETUP_PLUS))
    #else
    if (full_scrn&SETUP)
    #endif //end #ifdef SUPPORT_FUNCTION_MENU 
    return;

    for(; i < osd_active_regions; i++) //kenny add it 2001/5/8
    {
        osd_tog_region(i, OSD_OFF);
        RegionOnOff[i][1] = 0;
        RegionOnOff[i][2] = STR_OS_SPACE;
        RegionValStr[i][0] = 0;
    }
#if defined(OP_PLAYMODE) && defined(SDRAM_16Mb_Mode)      
return;
#endif  
    
//wanghaoying 2005-1-17 21:48 delete for no used from OrientPower strange request
//#if !defined(OP_UI)
    show_angle_osd();
    restore_osd_msg();//terry,2002/5/8 05:02と,reduce code
//#endif
}

#ifdef OSD_COLOR_ADJUST_BY_BRIGHTNESS_AND_CONTRAST      // 2004/11/12 yltseng

    #ifdef DVD_SETUP_REENG
#include "setup_VA.h"
    #else
#include "setup_page.h"
    #endif
    
int osd_get_brightness(UINT8 b_new_val)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    #define b_scale 4
    return b_scale * (b_new_val - 6);
}

UINT32 osd_get_contrast(UINT8 c_new_val)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    // 0.82 * 512, 0.85 * 512, 0.88 * 512, 0.91 * 512 .... 1.18 * 512 ( contrast scale step size = 0.03 )
    UINT32 c_scale[13] = {420, 435, 451, 466, 481, 497, 512, 527, 543, 558, 573, 589, 604};
    return c_scale[c_new_val];
}

UINT32 osd_rescale_color(UINT32 uiColor)
{  
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

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
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    int r = 0;
    UINT32 *palette = osd__pal[SETUP_HEADER];
    
    #ifdef DEBUG_OSD_UPDATE_SETUPMENU_PALETTE
    printf("==> Begin: osd_update_setupmenu_palette\n");
    #endif
    
    
    for( ; r < 16; r++ )
    {
        UINT8 *p, *q, *t;
        t = get_osdbuf_baseptr()+HEADER_SIZE+r*OSD_CLUT_SIZE;
        p = t + (region[0].osd_header[0] << 5);
        q = t + (region[0].osd_header[1] << 5);
        
        wbe32( p, osd_rescale_color( palette[r] ) );
        wbe32( q, osd_rescale_color( palette[r] ) );
    }
}
#else

#define osd_rescale_color( uiColor ) (uiColor)

#endif

//update color index
void SetOsdCol(UINT8 rb, UINT8 re, UINT8 id, UINT32 color)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

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
}


UINT32 GetOsdCol(UINT8 r, UINT8 id)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    UINT8 *p;
    p=get_osdbuf_baseptr()+region[r].osd_header[0]*32+HEADER_SIZE+id*OSD_CLUT_SIZE;
#ifdef  OSD_PAL_16b
    return getUINT16_bi(p);
#else
    return getUINT32_bi(p);
#endif
}


void
InitSW_region(void)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    int i,j;
    
    //clear old message
    for(i=0;i<MAX_REGION;i++)
        for(j=0;j<MAX_SW_REGION;j++)  
            RegionStr[i][j][0]=0;
}


//
//function: create region for interlace mode
//
//Note: the osd create region is addition the color mode for create
void osd_create_region1(t_osd_region *p, int X, int Y, t_osd_region *prev,BYTE bColorMode,BYTE bScanMode)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

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
    
    W = p->osd_w/4;        //width must times of 4        
    H = p->osd_h;        //Top + bottom    
    if(p_scan)
    {
        Y<<=1;
    }
    else
    {
        //if(bScanMode==OSD_INTERLACED)
        H>>=1;
    }
         
    for (i=0;i<2;i++)
    {    
        obase=ofrom+(osd_free<<5);    
        
        //buffer must in 32 aligment
        p->osd_header[i]=osd_free;
        
        // get prev link address (for header generation)
        linkaddr = (prev==NULL) ? LINK_NULL : prev->osd_header[i];
        
        //Cal. data blk start addr.        
        osd_free  = osd_free + OSD_DATA_OFFSET(bColorMode);
        
        p->osd_format=bColorMode;
        
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

        if(bColorMode==OSD_FORMAT_4COLOR)
            pn = 4;
    else if(bColorMode==OSD_FORMAT_16COLOR)
            pn = 16;                           
    else
            pn = 256;        

        align = (OSD_DATA_OFFSET(bColorMode)<<5) - HEADER_SIZE - OSD_CLUT_SIZE*pn;        
         
        // put color        
        do {
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
            wbe32( obase, osd_rescale_color(*pa) ); // 2004/10/16 yltseng
#endif            
            obase += OSD_CLUT_SIZE;
            pa ++;
        } while (--pn>0);                                
        
        memset(obase,0,align);
        obase+=align;        
        
    // clear OSD bitmap content
        for (pn=H;pn>0;pn--)
        {
            for(j=0;j<W;j++) ((UINT32 *)obase)[j]=0;
            //next line    
        obase+=(W<<2);            
        }

        //osd_printf("--obase:%x\n",obase);        
        //aligment buffer on 32 byte start
        //osd_free += (H*W*4/32);
        osd_free    = ((obase - ofrom)+31)/32;
        
        //if on non-interface mode , display become top line= bottom line
        if ( (bScanMode==OSD_NONINTERLACED)||p_scan )
        {
            p->osd_header[1]=p->osd_header[0];
            break;
        }        
    }                
}


void
draw_osd_board(UINT8 r, UINT8 board_type)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

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
        if (r==1) x_start=0; else x_start=19;
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
    
    //board_type=0;
}    

UINT32 StringLength(const BYTE *s)//libing 2005-1-13 10:38
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

	UINT32 len;
    const BYTE   *pFont;
	len=0;
    while (*s != '\0')
    	{
        if (*s == '\r') {                    //prefix characher: to use font_table2
            if (*(s++)=='\0' ) break;
            if ((pFont = get_font_entry(1,*s))==NULL) continue;
        	} 
		else {
            //get current char entry
            pFont = get_font_entry(0,*s);
        	}
        len+= (int)pFont[0];
		s++;
    	}
	len>>=4;
	return len;
}

//
//Function : draw a string on OSD region
//Action   : now the font width has two size, on is 16 point for english
//           and one is 32 point for chinese
//
//Notice   : 1. The font width must is time of 8
//           2. if the font high is more then region area, program will be fail
//           3. the font high must be even
//
//terry,2004/1/14 06:17PM,
#if 0
void osd_print_region2(t_osd_region *p, const char *s0, BYTE y_start,BYTE x_start)
{    
    int         iHeight, iWidth;
    int         W;
    BYTE        *pTopLine;
    BYTE        *pBtmLine;
    BYTE        *pFont;     
    BYTE        *pPattern;
    UINT16      space;     
    UINT16      unFontLoc;
    UINT16      unDispLoc;          
    int         i, j, k,tab_id;
    int         iFontHigh,iFontWidth;
    BYTE        c,c1;
#ifdef DRAW_BLACK_FRAME
    int        nibble_changed = 0;
    int        unFontMemLoc = 0;
#endif         

    iWidth = p->osd_w;
    iHeight = p->osd_h;

    //osd_printf("osd_print_region2 %x %x %d %d (%d %d)\n", p, s0, y_start, x_start, iWidth, iHeight);

    W = iWidth;

    pPattern = (BYTE *)pattern_4;

    unFontLoc = 0;    
    //c=1;
    unDispLoc = 0;    
    
    //process each charactor
    while(1)    
    {
        //get char.
        c=((BYTE *)s0)[unFontLoc];        
        c1=((BYTE *)s0)[unFontLoc+1];                        
        pPattern=(BYTE *)pattern_4;
        
        //parsing special char.
        switch(c)
        {
          case '\r': 
                     tab_id=1;
                     c=c1;
                     unFontLoc+=2;
                     break;
#ifdef SUPPORT_PLAYBACK_ICON          
          case '\a': 
                     tab_id=3;
                     unFontLoc+=2;
                     c=c1;                     
                     break;
#endif
          default:
                     tab_id=0;
                     unFontLoc++;
                     break;
                     
        }        
        
        if(c=='\0') break;//ending
        else if(c=='\n')  
        {
           c =' ';
        }
        else
        {//get anti-char 
           if ((unFontLoc>antic_begin)&& (unFontLoc<antic_end))
            pPattern=(BYTE *)pattern_a4;
        }
        
        //get current char entry
        if ((pFont = get_font_entry(tab_id,c))==NULL) continue;
        
        //get font information
        iFontWidth=(int)pFont[0];        
        iFontHigh=(int)(pFont[1]);       
        
        if(unDispLoc==0)
        {
          if( (y_start+iFontHigh) <= (p->osd_h) )
             unDispLoc = y_start*iWidth + x_start;
        }
        
        if(p_scan==0) iFontHigh>>=1;
        
        //how many byte need for is word         
        j=iFontWidth/ONE_BYTE_POINT;
        //j=iFontWidth/pFont[2];
        
        if (iWidth<j)        //iWidth is how many byte on this region
            break;
        else
            iWidth-=j;
        
        //if necessary,program will compare OSD region high with font 
        //if (iFontHigh>p->osd_h)
        //    iFontHigh=p->osd_h;
        
        //get pattern entry 
        pFont+=3;
        
        //calucation font width for BYTE, 32/4=8 byte/2=4 word
        space=j;
        
        //initialize buffer start        
        pTopLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (p->osd_header[0]+OSD_DATA_OFFSET(p->osd_format))*32);
        pBtmLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (p->osd_header[1]+OSD_DATA_OFFSET(p->osd_format))*32);
        
    //osd_printf("pTopLine:%x pBtmLine:%x \n",pTopLine,pBtmLine);
        //start to draw        
#ifdef DRAW_BLACK_FRAME        
        nibble_changed = 0;
        unFontMemLoc = 0;
#endif                
        for (j=0;j<iFontHigh;j++) 
        {
#ifdef DRAW_BLACK_FRAME         
            BYTE    bTempc = 0;
            BYTE    bTemp = 0;
            BYTE    bCurrLost = 0;
            BYTE    bPrevLost = 0;
            BYTE    bNextLost = 0;
            BYTE    bPrevRowLost = 0;
            BYTE    bNextRowLost = 0;
            BYTE    bHighLow = 0;
            BYTE    bNextRow = 0;
            BYTE    bPrevRow = 0;
            UINT16  unSpaceCopy = 0;
            BYTE    bTempImage = 0;
            UINT16  unOffset = 0;
#endif            
            //top         
            for (i=0; i<space; i++) 
            {
#ifndef DRAW_BLACK_FRAME               
                if (i%2==0) {
                    pTopLine[i+unDispLoc] = pPattern[ (pFont[i/2] >> 4) ];
                } else {
                    pTopLine[i+unDispLoc] = pPattern[ (pFont[i/2] & 0x0f) ];
                }
#else 
                //if(nibble_changed == 1)
                if (i%2==1)
                {

                    if(pPattern != pattern_4)
                        pTopLine[i + unDispLoc] = pPattern[(pFont[i/2] & 0x0f)];
                    else
                    {
                        bTempc = pPattern[(pFont[i/2] & 0x0f)];
                        bTemp = (pFont[i/2] & 0x0f) << 4;
                        bTemp |= ((pFont[i/2 + 1] & 0xf0) >> 4);
                        bTemp &= 0x78;
                        bTemp >>= 3;
                        if(i == space - 1)
                            bTemp = 0;
                    }

                }
                else
                {
                    if(pPattern != pattern_4)
                        pTopLine[i + unDispLoc] =
                            pPattern[((pFont[i/2] & 0xf0) >> 4)];
                    else
                    {
                        bTempc = pPattern[(pFont[i/2] & 0xf0) >> 4];
                        bTemp = pFont[i/2];
                        bTemp &= 0x78;
                        bTemp >>= 3;
                        if(i == space - 1)
                            bTemp = 0;
                    }
                }
                if(pPattern == pattern_4)
                {
                    bHighLow = nibble_changed;
                    unSpaceCopy = space;
                    unOffset = 0;
                    while(unSpaceCopy--)
                    {
                        if(bHighLow == 1)
                        {
                            bHighLow = 0;
                            unOffset++;
                        }
                        else
                            bHighLow = 1;
                    }
                    if(j == (iFontHigh - 1))
                        bNextRow = 0;
                    else
                        bNextRow = pFont[i/2 + unOffset];
                    if(bHighLow == 1)
                        bNextRow &= 0x0f;
                    else
                    {
                        bNextRow &= 0xf0;
                        bNextRow >>= 4;
                    }
                    bHighLow = nibble_changed;
                    unSpaceCopy = space;
                    unOffset = 0;
                    while(unSpaceCopy--)
                    {
                        if(bHighLow == 1)
                            bHighLow = 0;
                        else
                        {
                            bHighLow = 1;
                            unOffset++;
                        }
                    }
                    if(j == 0)
                        bPrevRow = 0;
                    else
                        bPrevRow = pFont[i/2 - unOffset];
                    if(bHighLow == 1)
                        bPrevRow &= 0x0f;
                    else
                    {
                        bPrevRow &= 0xf0;
                        bPrevRow >>= 4;
                    }
                    bPrevLost = bNextLost;
                    bTemp = pPattern[bTemp];
                    bCurrLost = (bTemp & 0x0c) >> 2;
                    bNextLost = (bTemp & 0x03) << 6;
                    bNextRowLost = PatternEdge[bNextRow];
                    bPrevRowLost = PatternEdge[bPrevRow];
                    bTempImage =
                        bCurrLost | bPrevLost | bNextRowLost | bPrevRowLost | bTempc;
                    pTopLine[i + unDispLoc] = bTempImage;
                }
                if(nibble_changed == 1)
                {
                    nibble_changed = 0;
                    //unFontMemLoc++;
                }
                else
                    nibble_changed = 1;
                unOffset = 0;
#endif  
            }            
            
            pTopLine += W;                        
            if(p_scan==0)
            {
               //move the font pattern point
               if (space%2==1) {
                  //odd bytes per line
                  k = 1;
                  pBtmLine[0+unDispLoc] = pPattern[ (pFont[space/2] & 0x0f) ];
                  pFont = pFont + (iFontWidth/8) + 1;
               } else {
                  k = 0;
                  pFont += (iFontWidth/8);
               }            
            
               //bottom               
               for (i=k; i<space; i++) {
                  if ((i-k)%2==0) {
                      pBtmLine[i+unDispLoc] = pPattern[ (pFont[(i-k)/2] >> 4) ];
                  } else {
                      pBtmLine[i+unDispLoc] = pPattern[ (pFont[(i-k)/2] & 0x0f) ];
                  }
               }
            
               pBtmLine+=W;  
            }
            pFont+=(iFontWidth/8);  
        }//for charactor high  
        
        //change to next OSD buffer point    
        unDispLoc += (iFontWidth/4);
        
    } //while ( (c=((BYTE *)s0)[unFontLoc])!='\0' )
    
    //clear last data to space
    
    //the region high
    //iFontHigh=p->osd_h/2;
    iFontHigh=p->osd_h;
    if(p_scan==0) iFontHigh>>=1;
    //the last space need to fill
    //iWidth=iWidth;

    if( (iWidth)&&(full_scrn!=PROGRAM) )
    {
        //initialize buffer start         
        pTopLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (p->osd_header[0]+OSD_DATA_OFFSET(p->osd_format))*32);
        pBtmLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (p->osd_header[1]+OSD_DATA_OFFSET(p->osd_format))*32);        
        for (j=0;j<iFontHigh;j++) 
        {
            for (i=0;i<iWidth;i++) {
#ifdef DRAW_BLACK_FRAME                
                pTopLine[i+unDispLoc] =  0x00;
                pBtmLine[i+unDispLoc] =  0x00;                   
#else
                pTopLine[i+unDispLoc] =  0x55;
                pBtmLine[i+unDispLoc] =  0x55;  
#endif                
            }
            pTopLine+=W;
            pBtmLine+=W;
        }
    }

    antic_begin=antic_end=0;
}
#else//#ifdef BBK_DVD//nono 20040118
void osd_print_region2(t_osd_region *p, const char *s0, BYTE y_start,BYTE x_start) 
{ 
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    int         iHeight, iWidth; 
    int         W; 
    BYTE        *pTopLine; 
    BYTE        *pBtmLine; 
    const BYTE        *pFont;      
    BYTE        *pPattern; 
    UINT16      space;      
    UINT16      unFontLoc; 
    UINT16      unDispLoc;           
    int         i, j, k; 
    int         iFontHigh,iFontWidth; 
    BYTE        c; 
#ifdef DRAW_BLACK_FRAME 
    int        nibble_changed = 0; 
    int        unFontMemLoc = 0; 
#endif          
 
    iWidth = p->osd_w; 
    iHeight = p->osd_h; 
 
    //osd_printf("osd_print_region2 %x %x %d %d (%d %d)\n", p, s0, y_start, x_start, iWidth, iHeight); 
 
    W = iWidth; 
 
    pPattern = (BYTE *)pattern_4; 
 
    unFontLoc = 0;     
    c=1; 
    
#ifdef OSD_BMP_REGION1 
// initialize some value,suqiaoli add 2004-8-30,

    //region1 info x start and y strat
    if(p_scan == 0) y_start = y_start>>1;
	unDispLoc = x_start;
    
    //region width and high
    if(p_scan == 0) iHeight = p->osd_h>>1;
	iWidth = iWidth - x_start;
    
	//printf("\n=====  Play %s   =====\n",s0);
	//printf("strlen(s0)=%d\n",strlen(s0));

    /* old region high is 24,same as high of font,so use font bg as region bg and don't draw region bg
       but now region high is 32,must specially draw region bg color and only draw (string + x_start)width  
    */ 
    pTopLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (p->osd_header[0]+OSD_DATA_OFFSET(p->osd_format))*32); 
    pBtmLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (p->osd_header[1]+OSD_DATA_OFFSET(p->osd_format))*32);         
    if (full_scrn!=PROGRAM)
    {
    	for (j=0;j<iHeight;j++)  
	    { 
			for (i=0;i<StringLength(s0)*4 + x_start;i++)
			//for (i=0;i<strlen(s0)*4 + x_start;i++) //libing marked 2005-2-24 17:49
			{
		    	pTopLine[i] =  0x00; 
		    	pBtmLine[i] =  0x00;   
			} 
			pTopLine+=W; 
			pBtmLine+=W; 
	    }
	}
#else
    unDispLoc = 0;     
#endif
     
    //process each charactor 
    while ( c!='\0' )     
    { 
        c=((BYTE *)s0)[unFontLoc]; 
        
        if( c=='\0' )  break;
        
        unFontLoc++; 
         
        //if( (c=='\n')||((unFontLoc==1)&&(c==' ')) ) 
        if (c=='\r') {                                  //prefix characher:to use font_table2 Jeff 20010906 
            if ( (c=((BYTE *)s0)[unFontLoc])=='\0' ) break; 
            unFontLoc++; 
             
            if ((pFont = get_font_entry(1,c))==NULL) continue; 
             
            //get pattern table 
            if ((unFontLoc>antic_begin)&& (unFontLoc<antic_end)) 
                pPattern=(BYTE *)pattern_a4; 
            else 
                pPattern=(BYTE *)pattern_4; 
        }  
#ifdef SUPPORT_PLAYBACK_ICON 
        else if (c == '\a') { 
            if ( (c=((BYTE *)s0)[unFontLoc])=='\0' ) break; 
             
            unFontLoc++; 
 
            if ((pFont = get_font_entry(3,c))==NULL) continue; 
 
            //get pattern table 
            if ((unFontLoc>antic_begin)&& (unFontLoc<antic_end)) 
                pPattern=(BYTE *)pattern_b4; 
            else 
                pPattern=(BYTE *)pattern_4; 
        } 
#endif         
        else { 
            if (c=='\n') { 
                c=' '; 
                //get pattern table 
                pPattern=(BYTE *)pattern_4; 
            } else { 
                //get pattern table 
                if ((unFontLoc>antic_begin)&& (unFontLoc<antic_end)) 
                    pPattern=(BYTE *)pattern_a4; 
                else 
                    pPattern=(BYTE *)pattern_4; 
            } 
             
            //get current char entry 
            if ((pFont = get_font_entry(0,c))==NULL) continue; 
        } //if (c=='\r') 
         
        //get font information 
        iFontWidth=(int)pFont[0]; 
        //iFontHigh=(int)(pFont[1]/2);        
        iFontHigh=(int)(pFont[1]);        
         
    #ifndef OSD_BMP_REGION1 
        if(unDispLoc==0) 
        { 
          if( (y_start+iFontHigh) <= (p->osd_h) ) 
             unDispLoc = y_start*iWidth + x_start; 
        } 
    #endif
         
        if(p_scan==0) iFontHigh>>=1; 
         
        //how many byte need for is word          
        j=iFontWidth/ONE_BYTE_POINT; 
        //j=iFontWidth/pFont[2]; 
         
        if (iWidth<j)        //iWidth is how many byte on this region 
            break; 
        else 
            iWidth-=j; 
         
        //if necessary,program will compare OSD region high with font  
        //if (iFontHigh>p->osd_h) 
        //    iFontHigh=p->osd_h; 
         
        //get pattern entry  
        pFont+=3; 
         
        //calucation font width for BYTE, 32/4=8 byte/2=4 word 
        space=j; 
         
        //initialize buffer start         
        pTopLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (p->osd_header[0]+OSD_DATA_OFFSET(p->osd_format))*32); 
        pBtmLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (p->osd_header[1]+OSD_DATA_OFFSET(p->osd_format))*32); 
         
        #ifdef OSD_BMP_REGION1
        pTopLine = pTopLine + y_start * p->osd_w; 
        pBtmLine = pBtmLine + y_start * p->osd_w; 
        #endif   
    //osd_printf("pTopLine:%x pBtmLine:%x \n",pTopLine,pBtmLine); 
        //start to draw         
#ifdef DRAW_BLACK_FRAME         
        nibble_changed = 0; 
        unFontMemLoc = 0; 
#endif                 

        #ifdef USE_SMALL_FONT//libing 2005-2-18 14:30
        if(iFontWidth==12)
        {
        pTopLine = pTopLine + (y_start) * p->osd_w; 
        pBtmLine = pBtmLine + (y_start) * p->osd_w; 
        }
        else
        {
        pTopLine = pTopLine + (y_start - 2) * p->osd_w;
        pBtmLine = pBtmLine + (y_start - 2) * p->osd_w;
        }
        #endif 
              
        for (j=0;j<iFontHigh;j++)  
        { 
#ifdef DRAW_BLACK_FRAME          
            BYTE    bTempc = 0; 
            BYTE    bTemp = 0; 
            BYTE    bCurrLost = 0; 
            BYTE    bPrevLost = 0; 
            BYTE    bNextLost = 0; 
            BYTE    bPrevRowLost = 0; 
            BYTE    bNextRowLost = 0; 
            BYTE    bHighLow = 0; 
            BYTE    bNextRow = 0; 
            BYTE    bPrevRow = 0; 
            UINT16  unSpaceCopy = 0; 
            BYTE    bTempImage = 0; 
            UINT16  unOffset = 0; 
#endif             
            //top          
            for (i=0; i<space; i++)  
            { 
#ifndef DRAW_BLACK_FRAME                
//modify by libing for p_scan font 2005-1-5 21:04              
                if (i%2==0) { 
                    pTopLine[i+unDispLoc] = pPattern[ (pFont[i/2] >> 4) ]; 
                } else { 
                    pTopLine[i+unDispLoc] = pPattern[ (pFont[i/2] & 0x0f) ]; 
                } 

#ifdef USE_SMALL_FONT     
            BYTE ch;
            if(j%2==0)
        	{        	
        	    if(i%2==0)
        	    {   //++pFont;	
                    ch = (pFont[i/2])>>4;
                }    
                else
                {
                    ch = (pFont[i/2])&0x0f;
                    	
                }
            }else{                              
                if(i%2==0)
                {                				 
                ch = (pFont[i/2])&0x0f;                           
                }
                else
                { 
                ++pFont;	
                ch = (pFont[i/2])>>4;
                }
                }      
                pTopLine[i+unDispLoc] = pPattern[ch&0x0f];                     
#endif//#ifdef USE_SMALL_FONT                   
#else//#ifndef DRAW_BLACK_FRAME 
                //if(nibble_changed == 1) 
                if (i%2==1) 
                { 
 
                    if(pPattern != pattern_4) 
                        pTopLine[i + unDispLoc] = pPattern[(pFont[i/2] & 0x0f)]; 
                    else 
                    { 
                        bTempc = pPattern[(pFont[i/2] & 0x0f)]; 
                        bTemp = (pFont[i/2] & 0x0f) << 4; 
                        bTemp |= ((pFont[i/2 + 1] & 0xf0) >> 4); 
                        bTemp &= 0x78; 
                        bTemp >>= 3; 
                        if(i == space - 1) 
                            bTemp = 0; 
                    } 
 
                } 
                else 
                { 
                    if(pPattern != pattern_4) 
                        pTopLine[i + unDispLoc] = 
                            pPattern[((pFont[i/2] & 0xf0) >> 4)]; 
                    else 
                    { 
                        bTempc = pPattern[(pFont[i/2] & 0xf0) >> 4]; 
                        bTemp = pFont[i/2]; 
                        bTemp &= 0x78; 
                        bTemp >>= 3; 
                        if(i == space - 1) 
                            bTemp = 0; 
                    } 
                } 
                if(pPattern == pattern_4) 
                { 
                    bHighLow = nibble_changed; 
                    unSpaceCopy = space; 
                    unOffset = 0; 
                    while(unSpaceCopy--) 
                    { 
                        if(bHighLow == 1) 
                        { 
                            bHighLow = 0; 
                            unOffset++; 
                        } 
                        else 
                            bHighLow = 1; 
                    } 
                    if(j == (iFontHigh - 1)) 
                        bNextRow = 0; 
                    else 
                        bNextRow = pFont[i/2 + unOffset]; 
                    if(bHighLow == 1) 
                        bNextRow &= 0x0f; 
                    else 
                    { 
                        bNextRow &= 0xf0; 
                        bNextRow >>= 4; 
                    } 
                    bHighLow = nibble_changed; 
                    unSpaceCopy = space; 
                    unOffset = 0; 
                    while(unSpaceCopy--) 
                    { 
                        if(bHighLow == 1) 
                            bHighLow = 0; 
                        else 
                        { 
                            bHighLow = 1; 
                            unOffset++; 
                        } 
                    } 
                    if(j == 0) 
                        bPrevRow = 0; 
                    else 
                        bPrevRow = pFont[i/2 - unOffset]; 
                    if(bHighLow == 1) 
                        bPrevRow &= 0x0f; 
                    else 
                    { 
                        bPrevRow &= 0xf0; 
                        bPrevRow >>= 4; 
                    } 
                    bPrevLost = bNextLost; 
                    bTemp = pPattern[bTemp]; 
                    bCurrLost = (bTemp & 0x0c) >> 2; 
                    bNextLost = (bTemp & 0x03) << 6; 
                    bNextRowLost = PatternEdge[bNextRow]; 
                    bPrevRowLost = PatternEdge[bPrevRow]; 
                    bTempImage = 
                        bCurrLost | bPrevLost | bNextRowLost | bPrevRowLost | bTempc; 
                    pTopLine[i + unDispLoc] = bTempImage; 
                } 
                if(nibble_changed == 1) 
                { 
                    nibble_changed = 0; 
                    //unFontMemLoc++; 
                } 
                else 
                    nibble_changed = 1; 
                unOffset = 0; 
#endif   
            }             
             
            pTopLine += W;                         
            if(p_scan==0) 
            { 
               //move the font pattern point 
               if (space%2==1) { 
                  //odd bytes per line 
                  k = 1; 
                  pBtmLine[0+unDispLoc] = pPattern[ (pFont[space/2] & 0x0f) ]; 
                  pFont = pFont + (iFontWidth/8) + 1; 
               } else { 
                  k = 0; 
                  pFont += (iFontWidth/8); 
               }             
             
               //bottom                
               for (i=k; i<space; i++) { 
                  if ((i-k)%2==0) { 
                      pBtmLine[i+unDispLoc] = pPattern[ (pFont[(i-k)/2] >> 4) ]; 
                  } else { 
                      pBtmLine[i+unDispLoc] = pPattern[ (pFont[(i-k)/2] & 0x0f) ]; 
                  } 
               } 
             
               pBtmLine+=W;   
            } 
            pFont+=(iFontWidth/8);   
        }//for charactor high   
         
        //change to next OSD buffer point     
        unDispLoc += (iFontWidth/4); 
         
    } //while ( (c=((BYTE *)s0)[unFontLoc])!='\0' ) 
     
    //clear last data to space 
     
    //the region high 
    //iFontHigh=p->osd_h/2; 
    iFontHigh=p->osd_h; 
    if(p_scan==0) iFontHigh>>=1; 
    //the last space need to fill 
    //iWidth=iWidth; 
 
    if( (iWidth)&&(full_scrn!=PROGRAM) ) 
    { 
        //initialize buffer start          
        pTopLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (p->osd_header[0]+OSD_DATA_OFFSET(p->osd_format))*32); 
        pBtmLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (p->osd_header[1]+OSD_DATA_OFFSET(p->osd_format))*32);         
        for (j=0;j<iFontHigh;j++)  
        { 
            for (i=0;i<iWidth;i++) { 
#ifdef DRAW_BLACK_FRAME                 
                pTopLine[i+unDispLoc] =  0x00; 
                pBtmLine[i+unDispLoc] =  0x00;                    
#else 
                pTopLine[i+unDispLoc] =  0x55; 
                pBtmLine[i+unDispLoc] =  0x55;   
#endif                 
            } 
            pTopLine+=W; 
            pBtmLine+=W; 
        } 
    } 
 
#ifdef OSD_BMP_REGION1
/*
do some special act:1)special region blank:after last word in region,remain 8 pixel blank
                    2)special region height:region last 4 pixel height is transparent
                    3)special region width:region last 4 pixel width is transparent
suqiaoli add 2004-8-30.
*/ 
    BYTE ibgheight;
    ibgheight = 4;
    if(p_scan==0)	ibgheight >>=1;
    
	BYTE    *pBlankTopLine,*pBlankBtmLine; 
	BYTE    *pHeightTopLine,*pHeightBtmLine; 
	BYTE    *pWidthTopLine,*pWidthBtmLine; 
	
	pTopLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (p->osd_header[0]+OSD_DATA_OFFSET(p->osd_format))*32); 
	pBtmLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (p->osd_header[1]+OSD_DATA_OFFSET(p->osd_format))*32);         
	
    if( (iWidth)&&(full_scrn!=PROGRAM) )     
    { 
    	//for first act:special region blank
		pBlankTopLine = (BYTE *)pTopLine;
		pBlankBtmLine = (BYTE *)pBtmLine;		
		     	
        for (j=0;j<iFontHigh;j++)  
        { 
            for (i=0;i<2;i++) 
            {
                pBlankTopLine[i+unDispLoc] =  0x00; 
                pBlankBtmLine[i+unDispLoc] =  0x00;   
            } 
            pBlankTopLine += W; 
            pBlankBtmLine += W; 
        } 
        
        //for second act:special region height
        pHeightTopLine = pTopLine + (iFontHigh -ibgheight)*W;
        pHeightBtmLine = pBtmLine + (iFontHigh -ibgheight)*W;
        
        for (j=0;j<ibgheight;j++)  
        { 
            for (i=0;i< unDispLoc + 3;i++) 
            {
                pHeightTopLine[i] =  0xaa; 
                pHeightBtmLine[i] =  0xaa; 
            } 
            pHeightTopLine += W; 
            pHeightBtmLine += W; 
        }         
        
        //for third act:special region width 
        pWidthTopLine = pTopLine + ibgheight*W;
        pWidthBtmLine = pBtmLine + ibgheight*W;
        
        for (j=0;j<iFontHigh -ibgheight;j++)  
        { 
            for (i=unDispLoc + 2;i< unDispLoc + 3;i++) 
            {
                pWidthTopLine[i] =  0xaa; 
                pWidthBtmLine[i] =  0xaa;                      
            } 
            pWidthTopLine += W; 
            pWidthBtmLine += W;         
    	}
    }
   
#endif
 
    antic_begin=antic_end=0; 
} 
#endif//#ifdef BBK_DVD//nono 20040118


//Function : draw a string on OSD region using second font
//Action   : now the font width has two size, one is 16 point for english
//           and one is 32 point for chinese
//
//Notice   : 1. The font width must is time of 8
//           2. if the font high is more then region area, program will be fail
//           3. the font high must be even
//
/*
void osd_print_regionEQ(t_osd_region *p, const char *s0)
{
    
    int       iWidth    = p->osd_w;
    int        W        = iWidth/2;
    UINT16 *pTopLine;
    UINT16 *pBtmLine;
    BYTE   *pFont;     
    BYTE   *pPattern;
    UINT16    space;     
    UINT16    unFontLoc;
    UINT16    unDispLoc;      
    int     i,j;
    int        iFontHigh,iFontWidth;
    BYTE    c;
       
    
    unDispLoc=unFontLoc=0;
    
    //In second font table, we only support 0~9, B, d, K, -, space, and ? characters
    //process each charactor
    while ( (c=((BYTE *)s0)[unFontLoc])!='\0' )    {
        unFontLoc++;
        
        if (c=='\n') {
            c=' ';
            //get pattern table
            pPattern=(BYTE *)pattern_a4;
        } else {      
            //get pattern table
            if ((unFontLoc>antic_begin)&& (unFontLoc<antic_end))             
                pPattern=(BYTE *)pattern_b4;
            else
                pPattern=(BYTE *)pattern_4;             
        }
        
        //re-index character mapping
        switch (c) {
        case '1':case '2':case '3':case '4':case '5':
        case '6':case '7':case '8':case '9':
            c = c - '0';
            break;
        case '0':
            c = 0x0a;
            break;
        case 'B':
            c = 0x0b;
            break;
        case 'd':
            c = 0x0c;
            break;
        case 'K':
            c = 0x0d;
            break;
        case '-':
            c = 0x0e;
            break;
        case ' ':
            c = 0x10;
            break;
        default:
            c = 0x0f;
            break;
        }
        
        //get current char entry
        if ((pFont = get_font_entry(1,c))==NULL) continue;
        //get font information
        iFontWidth=(int)pFont[0];
        iFontHigh=(int)(pFont[1]);       
        if(p_scan==0)
           iFontHigh>>=1;
        
        //how many byte need for is word         
        j=iFontWidth/ONE_BYTE_POINT;
        //j=iFontWidth/pFont[2];
        
        if (iWidth<j)        //iWidth is how many byte on this region
            break;
        else
            iWidth-=j;
        
        
        //get pattern entry 
        pFont+=3;
        
        //calucation font width for UINT16, 32/4=8 byte/2=4 word
        space=j/2;
        
        //initialize buffer start
        pTopLine = (UINT16 *)(((BYTE *)get_osdbuf_baseptr()) + (p->osd_header[0]+OSD_DATA_OFFSET(p->osd_format))*32);
        pBtmLine = (UINT16 *)(((BYTE *)get_osdbuf_baseptr()) + (p->osd_header[1]+OSD_DATA_OFFSET(p->osd_format))*32);
        
        //start to draw        
           for (j=0;j<iFontHigh;j++) {
            //top
            for (i=0;i<space;i++)        
                pTopLine[i+unDispLoc] =  (pPattern[pFont[i]>>4])|(pPattern[pFont[i]&0x0f]<<8);
            
            pTopLine+=W;
            
            //move the font pattern point 
            pFont+=(iFontWidth/8);  
            
            if(p_scan==0)
            {
              //bottom
              for (i=0;i<space;i++)
                pBtmLine[i+unDispLoc] =  (pPattern[pFont[i]>>4])|(pPattern[pFont[i]&0x0f]<<8);
            
              pBtmLine+=W;  
            
              //move the font pattern point 
              pFont+=(iFontWidth/8);  
            }
        }//for charactor high  
        
        //change to next OSD buffer point    
        unDispLoc+=(iFontWidth/8);
        
    }//while
}
*/


/*
Function :  Draw EQ setting status on screen by OSD
Input     :  UINT8 r            : region for draw
UINT8 unSele    : which frequency is choice now

Note     :    The each freq energy 0 ~ 24        
Modify  : 	   feeling
  
*/
 #ifdef OSD_BMP_SOUND
    	#define EQ_XSTART_BYTE	152  //304/2
    	#define EQ_YSTART	38
	#define EQ_CURSOR_CENTER_RECT 0x0c
    	#define EQ_SELECTED_CENTER_RECT  0x0e
    	#define EQ_CURSOR_OTHER_RECT 0x02
    	#define EQ_SELECTED_OTHER_RECT 0x09
    	#define BAND_XSTART_BYTE	87
    	#define BAND_YSTART	38
    	#define BAND_TOP_SEL_RECT	0x0c//yellow
    	#define BAND_SELECTED_RECT  0x09
    	#define BAND_OTHER_RECT 0x07
    	#define RECT_XOFFSET_BYTE	9   //18/2
    	#define RECT_WIDTH_BYTE	6	//12/2
    	#define RECT_YOFFSET      6
    	#define RECT_HEIGHT		4
    #else
    	#define EQ_XSTART_BYTE	120
    	#define EQ_YSTART	60
    	#define EQ_CURSOR_CENTER_RECT DRK_GREEN_COLOR
    	#define EQ_SELECTED_CENTER_RECT  YELLOW_COLOR
    	#define EQ_CURSOR_OTHER_RECT GRAY_COLOR
    	#define EQ_SELECTED_OTHER_RECT GRAY_COLOR
    	#define BAND_XSTART_BYTE	60
    	#define BAND_YSTART	60
    	#define BAND_TOP_SEL_RECT  BR_RED_COLOR
    	#define BAND_SELECTED_RECT  bColorTab[j/4]
    	#define BAND_OTHER_RECT GRAY_COLOR
 	#define RECT_XOFFSET_BYTE	8
    	#define RECT_WIDTH_BYTE	6
    	#define RECT_YOFFSET      4
    	#define RECT_HEIGHT		2

    #endif	
void    osd_print_eq_setting(UINT8 r,UINT8 unSele)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    UINT8     iWidth    = region[r].osd_w/2;
    UINT16    i,j,iBlock,data,step,k,uiRectX;
    UINT8     *pTopLine,*pBtmLine;
    BYTE    *p;
    UINT8    unColor;    
    BYTE    bChannelVal[14];
    
    
    //osd_printf("W=%d,h=%d \n",iWidth*2,region[r].osd_h);
    
    //calcuate the interpolate data
    //The data is mapping to 0 ~ 24
    //p=&RegionValStr[2][0];
        p=&RegionValStr[r][0];
        
    for (i=0;i<14;i=i+2)
    {
        bChannelVal[i]=MAX_VOLUME-*p;
        bChannelVal[i+1]=MAX_VOLUME-((*(p)+*(p+1))/2);
        p++;
    }
    
    
    //for (i=0;i<13;i++)
    //    osd_printf("%02d,",bChannelVal[i]);
    //osd_printf("\n");        
    
    
    //plot the background block
    data=(region[r].osd_header[0]+OSD_DATA_OFFSET(region[r].osd_format));
    if (p_scan==0)
    {
        pTopLine = (UINT8 *)(((BYTE *)get_osdbuf_baseptr()) + data*32 +EQ_XSTART_BYTE+iWidth*EQ_YSTART);    
        data=(region[r].osd_header[1]+OSD_DATA_OFFSET(region[r].osd_format));
        pBtmLine = (UINT8 *)(((BYTE *)get_osdbuf_baseptr()) + data*32 +EQ_XSTART_BYTE+iWidth*EQ_YSTART);    
    } else {
        pTopLine = (UINT8 *)(((BYTE *)get_osdbuf_baseptr()) + data*32 +EQ_XSTART_BYTE+iWidth*EQ_YSTART*2);    
        pBtmLine=pTopLine;
    }
    
    //Totally has 25 block for each freq (0 ~ 24 )    
    //from line 1
    //pTopLine=pTopLine+iWidth;
    
    //osd_printf("pTopLine:%x\n",pTopLine);
//    memset((UINT8 *)pTopLine,0,(region[r-1].osd_header[0]-data)*32 );

    if(p_scan==0)  
        step=1;
    else 
        step=2;
    
    for (j=0;j<25;j++)
    {      
        for(k=0;k<step*RECT_HEIGHT/2;k++)
        {
            //pTopLine[0]=TRANS_COLOR;
            
		for (i=0,iBlock=0;iBlock<13;i=i+RECT_XOFFSET_BYTE,iBlock++) 
            {    
                //make sure color
			if (j==bChannelVal[iBlock])//center
                	{
                    if (unSele==iBlock)
                        		unColor=EQ_CURSOR_CENTER_RECT;//yellow
                    else                
                        		unColor=EQ_SELECTED_CENTER_RECT;//gray
                	}
			else //others
			{
				if (unSele==iBlock)
                        		unColor=EQ_CURSOR_OTHER_RECT;//bg blue
                    else
                        		unColor=EQ_SELECTED_OTHER_RECT;//blue

			}
				//unColor=EQ_OTHER_RECT; 

                       for(uiRectX = 0; uiRectX < RECT_WIDTH_BYTE + 1; uiRectX++)
                        {
                        	 pTopLine[i + uiRectX] =  unColor;  //fill the colored rects
                        }
                    
                if (p_scan==0)
                {
	                       for(uiRectX = 0; uiRectX < RECT_WIDTH_BYTE + 1; uiRectX++)
	                        {
	                        	 pBtmLine[i + uiRectX] =  unColor;  //fill the colored rects
                }
                
        }
                
        }
		pTopLine+=iWidth*2;
		if (p_scan==0)
			pBtmLine+=iWidth*2;
        }
        
        //step 2 pixel
        pTopLine+=(iWidth*step*(RECT_YOFFSET - RECT_HEIGHT));
        if (p_scan==0) 
            pBtmLine+=(iWidth*step*(RECT_YOFFSET - RECT_HEIGHT));
        //osd_printf("pTopLine:%x\n",pTopLine);
    }
}

/*
Function :  Draw EQ status on screen by OSD
Input     :  UINT8 r            : region for draw
BYTE  *p :  input 7 band EQ value 

Note     :    The each band energy range is 0 ~ 24        
modify: feeling
*/
//The each freq energy 0 ~ 25    0= nothing, 1 ~ 25 engry
#ifdef SUPPORT_3DSOUND
void   
osd_print_eq(UINT8 r, const BYTE *p)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    UINT8  iWidth;
    UINT16  i,j,iBlock,step,k,uiRectX;
    UINT8  *pTopLine,*pBtmLine;
    UINT8  unColor;    
    BYTE    bChannelVal[14];    //byte 13 is garbage

    iWidth = region[r].osd_w/2;

    osd_puts("print eq\n");
    
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
    if (p_scan==0) {
        pTopLine = (UINT8 *) (get_osdbuf_region_ptr(r,0)+BAND_XSTART_BYTE+iWidth*BAND_YSTART);
        pBtmLine = (UINT8 *) (get_osdbuf_region_ptr(r,1)+BAND_XSTART_BYTE+iWidth*BAND_YSTART);
    } else {
        pTopLine = (UINT8 *) (get_osdbuf_region_ptr(r,0)+BAND_XSTART_BYTE+iWidth*BAND_YSTART*2);//nono 2003-7-25 23:12
        pBtmLine=pTopLine;
    }
    

    //Totally has 25 block for each freq (0 ~ 24 )
    
    //from line 1
    //pTopLine=pTopLine+iWidth;
    if(p_scan==0)  step=1;
    else step=2;
    
    for (j=25;j>0;j--)
    {      
        for(k=0;k<step*RECT_HEIGHT/2;k++)
        {
            //pTopLine[0]=TRANS_COLOR;
            
            for (i=1,iBlock=0;iBlock<13;i=i+RECT_XOFFSET_BYTE,iBlock++)
            {    
                //make sure color
                if (j==bEqEnergyMax[iBlock])
                    unColor= BAND_TOP_SEL_RECT;//BR_RED_COLOR;BAND_TOP_SELECTED
                else {
                    if (j<bChannelVal[iBlock])
                        unColor=BAND_SELECTED_RECT;//bColorTab[j/4];
                    else
                        unColor=BAND_OTHER_RECT;//GRAY_COLOR;   
                }            
                                  
                   for(uiRectX = 0; uiRectX < RECT_WIDTH_BYTE + 1; uiRectX++)
                    {
                    	 pTopLine[i + uiRectX] =  unColor;  //fill the colored rects
                }            
                                  
                if (p_scan==0)
                {
                       for(uiRectX = 0; uiRectX < RECT_WIDTH_BYTE + 1; uiRectX++)
                        {
                        	 pBtmLine[i + uiRectX] =  unColor;  //fill the colored rects
                }
                }
            }
            pTopLine+=iWidth*2;    
            if (p_scan==0) pBtmLine+=iWidth*2;
        }
        
        //step 2 line
        pTopLine+=(iWidth*step*(RECT_YOFFSET - RECT_HEIGHT));    
        if (p_scan==0) pBtmLine+=(iWidth*step*(RECT_YOFFSET - RECT_HEIGHT));
    } 
}
#else
void osd_print_eq(UINT8 r, const BYTE *p) {}   //alan, 2003/10/8
#endif

#else
#include "osd2.c"
#endif

#if defined(LARGE_SCORES_DISPLAY)//&&defined(GBM_DVD)//wuxiaofeng copy the code from the rear 02-23
/****************************************
 *** function :draw the font bitmap ;
 *** pFont: the pointer of the font bitmap data
 *** xStart,yStart: the coordinate
 *** fontcolor: the font color 
 *** bgcolor : the background color of the font 
 *** FigureColor: the figure color of the font
 *** FontType : the font type 
 *** number: the OSD region NO.
 ****************************************/
void draw_midi_bitmap_HZnew(const UINT8* pFont, int xStart, int yStart,
    BYTE fontcolor, BYTE bgcolor, BYTE  FigureColor, BYTE FontType,
    BYTE number)
{
    BYTE CurrentByte, CurrentByte1, CurrentBit, CurrentBit1;
    BYTE NewFormatFlag,bDispHalfByte;
    UINT8* p1Font;
    UINT8* pTopLine, * pBtmLine, * pLine;
    UINT32 iDispLoc, disploc = 0;
    int iRegionWidth = region[number].osd_w ;
    int osd_format = region[number].osd_format;
    unsigned int     fwidth,fhight,fbit=0;
    unsigned int     i, j, Bperpixel,shift_num,tempi;

    pTopLine = (BYTE *)(((BYTE *) get_osdbuf_baseptr()) +
        (region[number].osd_header[0] + OSD_DATA_OFFSET(region[number].osd_format)) * 32);
    pBtmLine = (BYTE *)(((BYTE *) get_osdbuf_baseptr()) +
        (region[number].osd_header[1] + OSD_DATA_OFFSET(region[number].osd_format)) * 32);

    yStart = (p_scan) ? yStart : yStart>>1;
    iDispLoc = (yStart ) * iRegionWidth  + xStart;
    bDispHalfByte = iDispLoc & 0x01;
    iDispLoc = (((yStart - ((yStart) & 0x01)) * iRegionWidth ) + (xStart))>>1;

    switch (osd_format)
    {
    case OSD_FORMAT_4COLOR:
        Bperpixel = 2; // 4
        shift_num = 2;
        break;
    case OSD_FORMAT_256COLOR:
        Bperpixel = 0; // 1
        shift_num = 8;
        break;
    case OSD_FORMAT_16COLOR:
        Bperpixel = 1; // 2
        shift_num = 4;
        break;
    default:
        Bperpixel = 1; // 2
        shift_num = 4;
        break;
    }

    //judge the format
    NewFormatFlag = pFont[0];
    if (NewFormatFlag != 0xff)
    {
        fwidth = pFont[0];
        fhight = pFont[1];
    }
    else
    {
        fhight = (pFont[4] << 8) | pFont[3];
        fwidth = (pFont[6] << 8) | pFont[5];
        fbit = fwidth * fhight;
    }

    if (NewFormatFlag != 0xff)
    {
        disploc = 0;
        for (i = 0; i < fhight; i++)
        {
            if (((i + yStart) & 0x01)||(p_scan ==1))
                    pLine = pBtmLine;
                else
                    pLine = pTopLine;

            for (j = 0; j < fwidth; j++)
            {
                tempi = (j+bDispHalfByte) >> Bperpixel;

                if (pFont[((j + disploc) >> 3) + 3] & (0x80 >>
                    ((j + disploc) & 0x07)))
                    pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] <<
                        shift_num) |
                        fontcolor;
                else
                    pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] <<
                        shift_num) |
                        bgcolor;
            }
            disploc += fwidth ;        
            if (((i + yStart) & 0x01)||(p_scan ==1))
                    iDispLoc += iRegionWidth;
            }
        }
    else
    {
        switch(FontType)
        {
            case 0:
                fontcolor=bgcolor;
                break;
            case 1:
                FigureColor=bgcolor;
                break;
            case 2:
            //  FigureColor = 11;
                break;
            default:
                break;
        }

        if (fbit & 0x07)
        {
            p1Font = (UINT8 *)pFont + (fbit >> 3) + 1;
        }
        else
        {
            p1Font = (UINT8 *)pFont + (fbit >> 3);
        }

        disploc = 0;
        for (i = 0; i < fhight; i++)
        {
            if (((i + yStart) & 0x01)||(p_scan ==1))
                    pLine = pBtmLine;
                else
                    pLine = pTopLine;

            for (j = 0; j < fwidth; j++)
            {
                CurrentByte = pFont[((j + disploc) >> 3) + 10];
                CurrentByte1 = p1Font[((j + disploc) >> 3) + 10];
                CurrentBit = CurrentByte & (0x80 >> ((j + disploc) & 0x07));
                CurrentBit1 = CurrentByte1 & (0x80 >> ((j + disploc) & 0x07));
                tempi = (j+bDispHalfByte) >> Bperpixel;

                if (CurrentBit != 0 && CurrentBit1 != 0)
                {
                    pLine[iDispLoc + tempi] = ((pLine[iDispLoc + tempi] <<
                        shift_num) & 0xf0) |
                        fontcolor; //0x02;//
                }
                else if (CurrentBit == 0 && CurrentBit1 != 0)
                {
                    pLine[iDispLoc + tempi] = ((pLine[iDispLoc + tempi] <<
                        shift_num) & 0xf0) |
                        FigureColor;//0x0b;//
                }
                else
                {
                    pLine[iDispLoc + tempi] = ((pLine[iDispLoc + tempi] <<
                        shift_num) & 0xf0) |
                        bgcolor; // 0x00;//
                }
            }
            disploc += fwidth ;  
            if (((i + yStart) & 0x01)||(p_scan ==1))
                    iDispLoc += iRegionWidth;
            }
        }
    //osd_tog_region(number, OSD_ON);
}
//*************************************************
//***clear the Rect region
// only for OSD_FORMAT_16COLOR 
//***int xx, int yy,:the position
//***int xlen, int ylen: the x&y length 
//***BYTE colour: the color that fill in the osd region
//***BYTE regNum:the region NO.
//*************************************************
void Osd_Clear_Rect(int xx, int yy, int xlen, int ylen, BYTE colour,
    BYTE regNum)
{
    BYTE* pTopLine, * pBtmLine, * pLine;
    BYTE colbyte;//bDispHalfByte;
    UINT32 iDispLoc;
    int i, j;
    int iRegionWidth = region[regNum].osd_w;

    if (p_scan ==1)
    {
        yy<<=1;
        ylen<<=1;
    }
    
    pTopLine = (BYTE *) (((BYTE *) get_osdbuf_baseptr()) +
        (region[regNum].osd_header[0] + OSD_DATA_OFFSET(region[regNum].osd_format)) * 32);
    pBtmLine = (BYTE *)(((BYTE *) get_osdbuf_baseptr()) +
        (region[regNum].osd_header[1] + OSD_DATA_OFFSET(region[regNum].osd_format)) * 32);

 //   iDispLoc = (yy ) * iRegionWidth  + xx;
//    bDispHalfByte = iDispLoc & 0x01;
//    xlen += bDispHalfByte;
    iDispLoc = (((yy - ((yy) & 0x01)) * iRegionWidth ) + (xx))>>1;

    colbyte =  (((colour & 0x0f) << 4) | (colour & 0x0f));
    for (j = 0; j < ylen; j++)
    {
        if ((j + yy) & 0x01)
            pLine = pBtmLine;
        else
            pLine = pTopLine;
        for (i = 0; i < xlen; i++) //print one point per time
        {
           if (i & 0x01)
            {
                pLine[iDispLoc + (i >> 1)] = colbyte;//&0x0f;
            }
        }
        if ((j + yy) & 0x01)
            iDispLoc += iRegionWidth;
    }
}
void osd_Clear_Region(BYTE reg, BYTE bkColor)
{
    Osd_Clear_Rect(0,0,region[reg].osd_w<<1,region[reg].osd_h,bkColor,reg);
}
#endif//#if defined(LARGE_SCORES_DISPLAY)&&defined(GBM_DVD)//wuxiaofeng copy the code from the rear 02-23

#ifdef SUPPORT_OSDLYRIC             //ouyang 2004-8-17 14:05 
#include "osd_midi.c"
#endif

#ifdef OSD_FONT_API//liweihua mod 2004-3-12 18:48
/*
 *Funciton Description:
 *   to show chinse/Englisch word/number in OSD
 *
 * INPUT:
 *   vid    -----> 0:  draw chinese 
 *          -----> 1:  draw English word/number
 *          -----> 2:  clear font (size: fwidth * fhight)
 *   
 *   pFont  -----> font lattice informaiton of a word
 *   xStart -----> word x axis start positon
 *   yStart -----> word y axis start positon
 *   fwidth -----> font width
 *   fhight -----> font hight
 *   number -----> region number
 *      
 *   liweihua and zhaoyanhua add 2004-1-9 14:56
 *   2004/09/03 yltseng modify
 */
 
void osd_draw_gbfont(BYTE vid, BYTE pFont[], int xStart, int yStart, unsigned int  fwidth, unsigned int  fhight, BYTE fontcolor,BYTE number)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    UINT8* pTopLine, * pBtmLine, * pLine;
    UINT32 iDispLoc, disploc = 0;
    BYTE bDispHalfByte;
    int iRegionWidth = region[number].osd_w ;
    int osd_format = region[number].osd_format;
    unsigned int     i, j, Bperpixel,shift_num,tempi;

#ifdef SUBTITLE_ADD_EDGE//zxb2005-4-24 0:18
	BYTE For_add_edge=0,For_add_edge_i=0,For_add_edge_j=0;
		#ifndef SUBTITLE_EDGE_COLOR
		#define SUBTITLE_EDGE_COLOR 1
		#endif
			if(vid==1)
				pFont+=3;
#endif

    pTopLine = (BYTE *)(((BYTE *) get_osdbuf_baseptr()) +
        (region[number].osd_header[0] + OSD_DATA_OFFSET(osd_format)) * 32);
    pBtmLine = (BYTE *)(((BYTE *) get_osdbuf_baseptr()) +
        (region[number].osd_header[1] + OSD_DATA_OFFSET(osd_format)) * 32);

    yStart = (p_scan) ? yStart : yStart>>1;

    //iDispLoc = (yStart ) * iRegionWidth  + xStart;
    bDispHalfByte = 0;//iDispLoc & 0x01;
    iDispLoc = ((yStart - ((yStart) & 0x01)) * iRegionWidth ) + (xStart);

    switch (osd_format)
    {
        case OSD_FORMAT_4COLOR:
            Bperpixel =  2; // 4
            shift_num = 2;
            break;
        default:
            Bperpixel = 1; // 4
            shift_num = 4;
            break;
    }

    fwidth += bDispHalfByte;
    disploc = 0;
    for (i = 0; i < fhight; i++)
    {
        if ((i + yStart) & 0x01)
        {
            if(p_scan)
                pLine = pTopLine;
            else
                pLine = pBtmLine;
        }
        else
            pLine = pTopLine;

#if(!defined(SUBTITLE_ADD_EDGE)) //zxb2005-4-24 0:19
            for (j = bDispHalfByte; j < fwidth; j++)
            {
                tempi = j >> Bperpixel;
                if (vid==0)  //chinese   get font info from gb2312font.c
                {
                    if(pFont[((j+disploc)>>3)]&(0x80>>((j+disploc)&0x07)))  
                    {
                        pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] << shift_num) | fontcolor;
                    }
                }else  if(vid == 1)//English word/number   get font info from font.c
                {
                    if(pFont[((j+disploc)>>3)+3]&(0x80>>((j+disploc)&0x07)))  
                    {
                        pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] << shift_num) | fontcolor;
                    }
                }
                else //vid = 2  clear font
                {
                    pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] << shift_num) | fontcolor;
                }
#else//#if(!defined(SUBTITLE_ADD_EDGE)) //zxb2005-4-24 0:19
          
	for (j = 0; j < fwidth; j++)
        {   
           if(j%8==0)
            	{
            		For_add_edge_i = ((j+disploc)>>3);
            		if(i==0)
						For_add_edge_j=(pFont[For_add_edge_i]<<1)|(pFont[For_add_edge_i]>>1)|(pFont[For_add_edge_i+fwidth/8]);
					else
						if(i<fhight-1)
							For_add_edge_j=(pFont[For_add_edge_i]<<1)|(pFont[For_add_edge_i]>>1)|(pFont[For_add_edge_i-fwidth/8])|(pFont[For_add_edge_i+fwidth/8]);
						else
							For_add_edge_j=(pFont[For_add_edge_i]<<1)|(pFont[For_add_edge_i]>>1)|(pFont[For_add_edge_i-fwidth/8]);
					For_add_edge=(~pFont[For_add_edge_i])&For_add_edge_j;
            	}
            			
            	if(vid>=2)
            	{
            		//no color
            		pLine[iDispLoc+j/2	]=0;
            		j++;            		
            	} 
            	else
            	{
            		if(pFont[((j+disploc)>>3)]&(0x80>>((j+disploc)&0x07)))
            		{
            			//fontcolor
            			pLine[iDispLoc+j/2	] =  (j%2) ? ((pLine[iDispLoc+j/2]&0xf0)|fontcolor) : ((pLine[iDispLoc+j/2]&0x0f)|(fontcolor<<4));
            			}
            		else if(For_add_edge&(0x80>>((j+disploc)&0x07)))
            		{
            			//edgecolor
            			pLine[iDispLoc+j/2	] =  (j%2) ? ((pLine[iDispLoc+j/2]&0xf0)|SUBTITLE_EDGE_COLOR) : ((pLine[iDispLoc+j/2]&0x0f)|(SUBTITLE_EDGE_COLOR<<4));
            			
            			}
            			else
            			{
            				//no color
            				pLine[iDispLoc+j/2	] =  (j%2) ? ((pLine[iDispLoc+j/2]&0xf0)|0) : ((pLine[iDispLoc+j/2]&0x0f)|(0<<4));            			
            				} 
            			}          	        			                        	 
#endif//#if(!defined(SUBTITLE_ADD_EDGE)) //zxb2005-4-24 0:19
            }
        disploc += (fwidth - bDispHalfByte); 
            
        if(p_scan == 0)
        {
            if ((i + yStart) & 0x01)
                iDispLoc += iRegionWidth;
        }
        else
            iDispLoc += iRegionWidth;
    }
    osd_tog_region(number, OSD_ON);
}

/*
 *Funciton Description:
 *   
 *   clear  reigon.
 */
void osd_ClearOneRegion(BYTE number, BYTE bkColor)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

    int width = region[number].osd_w <<1;
    int hight = region[number].osd_h;
    
    osd_draw_gbfont(2,"ABCD",0, 0, width, hight,bkColor,number);
}
#endif

#if defined(OSD_FONT_API)||defined (OSD_BMP)
//move out this function,because it must be used in OSD_BMP,suqiaoli modified,2004-12-22
//this function can be used when tv format change from NTSC to PAL
//move region r to a new location
//liweihua add 2004-1-13 16:00
void MoveRegion(BYTE r,UINT16 x,UINT16 y)
{
#ifdef OSD_DYNAMIC_ONOFF
    if(OSD_Dynamic_onoff == 0)
    return;
#endif

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

#ifdef TONIC_DVD
void draw_osd_board_pscan(UINT8 r, UINT8 board_type)
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
        for (i=0;i<w;i++) 
        {
                pTopLine[i] =  0xff;
                pBtmLine[i] =  0xff;                   
        }
    }
    if(board_type&BOARD_DOWN_LINE)
    {   
        if (r!=1)
        {
            for (i=(h-1)*w;i<(h*w);i++) 
            {
                    pTopLine[i] =  0xff;
                    pBtmLine[i] =  0xff;                   
            }
        }
    }
    if(board_type&BOARD_LEFT_LINE)
    {   
        for(i=0;i<(h*w);i+=w) 
        {
            pTopLine[i] =  0xff;
            pBtmLine[i] =  0xff;                   
        }
    }
    if(board_type&BOARD_RIGHT_LINE)
    {   
        for(i=w-1;i<(h*w);i+=w) 
        {
            pTopLine[i] =  0xff;
            pBtmLine[i] =  0xff;                   
        }
    }
    //board_type=0;
}
void OsdShowPscan(BYTE onoff)
{
        SetOsdCol(3,7,0, __palette4F(  10, 10, 10,0xff));          
        SetOsdCol(3,7,1, __palette4F(  10, 10, 10,0xff));                               
        draw_osd_board_pscan(3,BOARD_UP_LINE);
        draw_osd_board_pscan(3,BOARD_RIGHT_LINE);
        draw_osd_board_pscan(3,BOARD_LEFT_LINE);     
        if(onoff==0)
        osd_print_region2(&region[4]," P.SCAN SWITCH OFF",0,0);       
        else
        osd_print_region2(&region[4]," P.SCAN SWITCH ON",0,0);       
        draw_osd_board_pscan(4,BOARD_LEFT_LINE); 
        draw_osd_board_pscan(4,BOARD_RIGHT_LINE);    
        osd_print_region2(&region[5]," RESTART PLAYER FOR THE",0,0);       
        draw_osd_board_pscan(5,BOARD_LEFT_LINE); 
        draw_osd_board_pscan(5,BOARD_RIGHT_LINE);
        osd_print_region2(&region[6]," CHANGE TO BE EFFECTIVE",0,0);       
        draw_osd_board_pscan(6,BOARD_LEFT_LINE); 
        draw_osd_board_pscan(6,BOARD_RIGHT_LINE);
        draw_osd_board_pscan(7,BOARD_DOWN_LINE);
        draw_osd_board_pscan(7,BOARD_RIGHT_LINE);
        draw_osd_board_pscan(7,BOARD_LEFT_LINE);                            
        osd_tog_region(3,OSD_ON);   
        osd_tog_region(4,OSD_ON);                   
        osd_tog_region(5,OSD_ON);   
        osd_tog_region(6,OSD_ON);   
        osd_tog_region(7,OSD_ON);           
}
#endif//#ifdef TONIC_DVD


//wanghaoying moved to \\higui\\osd.c for no used

#ifdef DISP_REGION_BOTTOM
#include "fsNAV.h"
/*
Purpose: Get to know disp posion 
Return Value:1 show disp in bottom position
             0: show disp in top position
*/
extern UINT8 Jpg_Show_Usage_Flag;
UINT8 OSD_ShowBottomDisp()
{
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

/*
Purpose: Get to know true disp region 

*/
UINT8 OSD_GetTrueDispRegion()
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
   	
    //printf("disp_region=%d\n",disp_region);
    	
    return  disp_region;
      
}

#endif//#ifdef DISP_REGION_BOTTOM

#ifdef NEW_HDMI_FLOW
UINT8 UpDateHDMI_StateDisplayi;
void UpDateHDMI_StateDisplay(void)
{
    //psprintf(linebuf,"i=%d\n",UpDateHDMI_StateDisplayi);
    //io_write_wait(linebuf);
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
#endif//#ifdef NEW_HDMI_FLOW
#ifdef OP_PLAYMODE
#include "opui.c"
#endif
//#endif //#ifdef SPHE1000_DVDSTATE_CALLBACK


