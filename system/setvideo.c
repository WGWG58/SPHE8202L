//
// FILE
// setvideo.c
//
#include "user_init.h"
#include "config.h"
#include "regmap.h"
#include "global.h"

#include "aspect.h"
#include "vpp.h"

#ifndef	DVDRELEASE
//#define MONE_SETUP
#endif

/*
* Notify     : If you want to revise this function,you must note
*              both sel_disp_sp_ch and do_PCI_HL function.
*              Additionally, the function is complexly.
*
* Test disc  : MIB,Panasonic,NF002
* Compare IC : ESS,C-Cub
*
* MIB  content\type   16:9    LB    PS
*      Wide Screen     F      W     W
*      Full Screen     F      F     F
*
* Pan. content\type   16:9    LB    PS
*      Title menu      F      W     W
*      Menu            F      W     W
*      1/1             F      W     F
*
* NF2  content\type   16:9    LB    PS
*      ALL             F      L     W
*
*/
extern int is_menu(void);//shenyj add for clear warning 2006/04/24
void
set_video_default_offset(void)
{
    vpp_zoom_x = 0;
    vpp_zoom_y = 0;
    vpp_zoom_offset_mode = OFFSET_CENTER;
}


void
set_video_aspect(void)
{
    // 00_11 4:3
    // 11_00 16:9, both letter-box and pan-scan
    // 11_01 16:9, both pan-scan
    // 11_10 16:9, both letter-box
    //
#define MODE_NORMAL             0x03            // 0011
#define MODE_WIDE_BOTH          0x0c            // 1100
#define MODE_WIDE_PS            0x0d            // 1101
#define MODE_WIDE_LB            0x0e            // 1110
#define MODE_IS_WIDE(m)         ((m)&0x0c)
    int _src_mode;

    // 0x0c 16:9 TV (direct for anamorphic output
    // 0x0d 4:3, 16:9 will be displayed in pan-scan
    // 0x0e 4:3, 16:9 will be displayed in letterbox
    //
#define USER_TVASPECT_WIDE      0x0c
#define USER_TVASPECT_NORMAL_PS 0x0d
#define USER_TVASPECT_NORMAL_LB 0x0e
#define USER_TVASPECT_AUTOWSS   0x0f
    int user    = (UserSet.P_V_CFG)>>8;

    int _output_aspect;

#define ninf_get_dvd_VMGM_V_ATR()   (pDSV->dV_ATR)

#if defined(SUPPORT_DVB)
    if ((show_logo || (cd_type_loaded!=CDDVD)) && (!support_dvb()))
//#ifdef SPHE1000
//	if (show_logo)
#else
    if (show_logo || (cd_type_loaded!=CDDVD))
#endif
        _src_mode = MODE_NORMAL;                // always 4:3
    else
    {
    //beginning.shenyj modify for Alco dvd.20060422
/* nono mark it.2006-6-5 11:53//It made Panasonic disc play incorrectly.
    	if(is_menu())
    	{
        	if(((pDSV->dV_ATR_Menu>>8)&0x0f)!=((pDSV->dV_ATR>>8)&0x0f))
        		_src_mode =(pDSV->dV_ATR_Menu>>8)&0x0f;
        	else
        		_src_mode =(pDSV->dV_ATR>>8)&0x0f;
        }
        else
        {
        _src_mode = (ninf_get_dvd_VMGM_V_ATR()>>8)&0x0f;
        }
*/
//ending.shenyj modify for Alco dvd.20060422

        _src_mode = (ninf_get_dvd_VMGM_V_ATR()>>8)&0x0f;

    }



    #ifdef MONE_SETUP
    printf("set_video_aspect: cfg:%x mode:%x A:%x Z:%x\n",UserSet.P_V_CFG>>8,_src_mode,mode_aspect,vpp_zoom);
    #endif

    //
    // OUTPUT_ASPECT_NORMAL         4:3 source on 4:3 TV, (WSS=4:3)
    // OUTPUT_ASPECT_COMPRESSED     4:3 source on 16:9 TV, (WSS=16:9)
    // OUTPUT_ASPECT_ANAMORPHIC     16:9 source on 16:9 TV, (WSS=16:9)
    // OUTPUT_ASPECT_LETTERBOX      16:9 source on 4:3 TV, (WSS=4:3LB)
    // OUTPUT_ASPECT_PANSCAN        16:9 source on 4:3 TV, (WSS=4:3PS)
    //
    //              setup=4:3LB	setup=4:3PS setup=16:9  setup=autowss
    //  4:3 source  NORMAL	NORMAL	    COMPRESSED  NORMAL
    // 16:9 source  LB          PS	    ANAMORPHIC  ANAMORPHIC
    //
    if (!MODE_IS_WIDE(_src_mode)) {
#if defined(ENABLE_COMPRESSED_ASPECT) || defined(SUPPORT_ALL_VIDEO_CHANGE_ASPECT_RATIO)
        // 4:3 source  //linrc 2005-10-10 14:43 for all video can change Aspect ratio (4:3->16:9)
        #ifdef SUPPORT_ALL_VIDEO_CHANGE_ASPECT_RATIO
        if ((user==USER_TVASPECT_WIDE)&&(!show_logo))
        #else
        if (user==USER_TVASPECT_WIDE)
        #endif
            _output_aspect = OUTPUT_ASPECT_COMPRESSED;  // compress to 4:3 on 16:9 TV
        else
            _output_aspect = OUTPUT_ASPECT_NORMAL;      // display 4:3
#else
        _output_aspect = OUTPUT_ASPECT_NORMAL;      // display 4:3
#endif
    } else {
        // 16:9 source
        if (user==USER_TVASPECT_WIDE || user==USER_TVASPECT_AUTOWSS) {
            _output_aspect = OUTPUT_ASPECT_ANAMORPHIC;
        } else {
            // 16:9 source on 4:3 TV, depends on user selected letterbox/pan-scan favorite
            if (_src_mode==MODE_WIDE_LB)
                user=USER_TVASPECT_NORMAL_LB;   // limited to display letterbox only
            else if (_src_mode==MODE_WIDE_PS)
                user=USER_TVASPECT_NORMAL_PS;   // limited to display pan-scan only

            if (user==USER_TVASPECT_NORMAL_PS)
                _output_aspect = OUTPUT_ASPECT_PANSCAN;
            else
                _output_aspect = OUTPUT_ASPECT_LETTERBOX;
        }
    }

    set_output_aspect(_output_aspect);

    //
    // mode_aspect=0: no display compression
    // mode_aspect=1: vertical compression by 3:4
    // mode_aspect=2: horizontal compression by 3:4
    //
    switch(_output_aspect)
    {
        case OUTPUT_ASPECT_ANAMORPHIC:
            vpp_zoom=ZOOM_LB;   mode_aspect=0;  break;
        case OUTPUT_ASPECT_LETTERBOX:
            vpp_zoom=ZOOM_LB;   mode_aspect=1;  break;
        case OUTPUT_ASPECT_PANSCAN:
            vpp_zoom=ZOOM_PS;   mode_aspect=1;  break;
#if defined(ENABLE_COMPRESSED_ASPECT) || defined(SUPPORT_ALL_VIDEO_CHANGE_ASPECT_RATIO)
//linrc 2005-10-10 14:43 for all video can change Aspect ratio (4:3->16:9)
        case OUTPUT_ASPECT_COMPRESSED:
            vpp_zoom=ZOOM_LB;
            #ifdef SUPPORT_ALL_VIDEO_CHANGE_ASPECT_RATIO  
            mode_aspect=1;
            #else 
            mode_aspect=2;
            #endif  
            break;
#endif
        default:
        case OUTPUT_ASPECT_NORMAL:
            vpp_zoom=ZOOM_LB;   mode_aspect=0;  break;
    }

    set_video_default_offset();

    #ifdef MONE_SETUP
    printf("vtr:%x vpp:%x aspect:%x \n",pDSV->dV_ATR,vpp_zoom,mode_aspect);
    #endif
}


//
// FUNCTION
// startup_vpp
//
// DESCRIPTION
// use vpp_zoom/vpp_zoom_x/vpp_zoom_y to setup Offset/Display
//
// SIDE EFFECT
// change v
//
#ifdef ROTATE_RESTORE_ZOOM//dingzhy
UINT8 zoom_flag;
#endif

void startup_vpp(void)
{
    //set_zoom_max(vpp_zoom,&vpp_zoom_x,&vpp_zoom_y);
    setVPP_OffsetMode(vpp_zoom_offset_mode);
    setVPP_OffsetX(vpp_zoom_x);
    setVPP_OffsetY(vpp_zoom_y);
    setVPP_Display(vpp_zoom);
    setVPP_DoIt();
    #ifdef ROTATE_RESTORE_ZOOM//dingzhy
    zoom_flag = vpp_zoom;
    #endif

    #ifdef MONE_SETUP
    printf("startup_vpp , zoom:%x, (x,y):%d %d,  max(x,y):%d %d\n",
        vpp_zoom,vpp_zoom_x,vpp_zoom_y,getVPP_XOffsetMax(),getVPP_YOffsetMax());
    #endif
}


void startup_vpp_now(void)
{
    startup_vpp();
    setVPP_DoItNow();
}

