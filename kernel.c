//
// FILE
// kernel.c
//
// DESCRIPTION
// kernel interface
//
#include "config.h"
#include "regmap.h"
#include "global.h"
#include "avd.h"
#include "avdctrl.h"
#include "vpp.h"
#include "tvif.h"
#include "aspect.h"

#include "kernel.h"
#include "kinf.h"
#ifdef PNGPIO_CON_TFT
#include "gpio.h"
#endif
#ifdef SUPPORT_SPI
#include "spi.h"
#endif
#ifdef DVD_SETUP_REENG
#include "setup_VA.h"
#include "setup_def.h"
#endif
#ifdef ADD_DVI311_SETUP
#include "spv301.h"
#endif
#ifndef DVDRELEASE
//#define KERNEL_DBG
#endif

#define kern_puts(s)            ((void)0)
#define kern_printf(s...)       ((void)0)
#define kern_show_function()    ((void)0)

#ifdef  KERNEL_DBG
#include "sio.h"
#include "emuio.h"
#include"spv301.h"
#undef  kern_puts
#undef  kern_printf
#undef  kern_show_function
#define kern_puts               puts_w
#define kern_printf             printf_w
#define kern_show_function()    do {kern_puts(__FUNCTION__); kern_puts("\n"); } while (0)
#define MONE_TVSETUP
//#define MONE_SIZECHG
#endif


UINT8   Ksetup_tv_format=0xFF;          // PAL / NTSC / ..
UINT8   Ksetup_tv_aspect=0xFF;          // 0:4:3 1:16:9
UINT8   Ksetup_jpeg_h_aspect=0xFF;          // 0:4:3 1:16:9
UINT8   Ksetup_jpeg_v_aspect=0xFF;          // 0:4:3 1:16:9


//
// FUNCTION
// setup_decode_service
//

void
setup_decode_service(int srv)
{
  switch (srv)
  {
    case SERVICE_ROMV:
      srv_kernel = srv_rom; break;
    case SERVICE_CDDA:
      srv_kernel = srv_cdda; break;

#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
    case SERVICE_CARDFILE:
        {
            extern int srv_cardfile(void);
            srv_kernel = srv_cardfile;
        }
        break;
#endif
#ifdef	SUPPORT_STREAM_BUFFER
    case SERVICE_STREAMING:
        {
            extern int srv_stream(void);
            srv_kernel = srv_stream;
        }
        break;
#endif
#if defined(SUPPORT_DVB) && defined(SPHE1000)
    case SERVICE_TS:
        {
            extern int srv_stream(void);
            srv_kernel = srv_stream;
        }
        break;
#endif
    case SERVICE_CD:
    default:
      srv_kernel = srv_cd; break;
  }
#if defined(SUPPORT_DVB) && defined(SPHE1000)
  kctx_init();
#endif
}


void
setup_clock_gating(int onoff)
{
    kernel_clock_gating = onoff;
}

void
setup_error_concealment(int onoff)
{
    kernel_error_concealment = onoff;
}

void
enable_portable_bonding(UINT8 onoff)
{
	kernel_portable_bonding = onoff;
}

void
setup_error_mb_limit(int n)
{
    kernel_error_mb_threshold = n;
}


//
// FUNCTION
// setup_tv_format(tvfmt)
//
// DESCRIPTION
// setup TV format
// see kernel.h for supported formats
// if auto then adjust TV format according to current decoding format.
//
void
setup_tv_format(int tvfmt)
{
    #ifdef SUPPORT_HD_RESOLUTION  
    if((GET_TV_RESOLUTION() == HD_720) || (GET_TV_RESOLUTION() == HD_1080) ) {
        if( (tv_format==MODE_NTSC) || (tv_format==MODE_PAL60) ||(tv_format==MODE_AUTO) ) 
            setVPP_TVformat(0);
        else    
            setVPP_TVformat(1);
        
        frctl_set_display_rate();
        return;
    }
    #endif

    #ifdef SUPPORT_FUNCTION_MENU
    #ifdef SUPPORT_SPI
    if(((pdvd_mode == PDVD_MODE) && (tvfmt != TV_FORMAT_NTSC)) || (pdvd_timer))
      return;
    #endif
    #endif
#ifdef ADD_DVI311_SETUP//@Kevin For outo set 2k40525
static unsigned char format_change_sign=0x84;
format_change_sign=dvi311_tv_mode;
#endif

    // now update system tv-format
    #ifdef ALCO_DVD_UI
    if (tvfmt==TV_FORMAT_AUTO && is_avd_tv_auto() 
        && !((play_state==VCD_STATE_STOP)||(play_state==VCD_STATE_IDLE)||(play_state==VCD_STATE_OPEN)))
    #else
    if (tvfmt==TV_FORMAT_AUTO && is_avd_tv_auto())
    #endif
    {
        unsigned decfmt = get_decode_format();
        if (decfmt==DECODE_FORMAT_525)
		{
			tvfmt=TV_FORMAT_525_DEFAULT;
			#ifdef ADD_DVI311_SETUP
			dvi311_tv_mode=0x85;    //kevin@2k40517
			#endif
		}
#ifdef GBM_FORCE_PAL_OUTPUT_NTSC_WHEN_PALM_PALN_AUTO		//gerry,2004-2-10 15:04
        else if (decfmt==DECODE_FORMAT_625)
		{
			tvfmt=TV_FORMAT_525_DEFAULT;
			#ifdef ADD_DVI311_SETUP
			dvi311_tv_mode=0x85;    //kevin@2k40517
			#endif
		}
#elif defined(EASTECH_AUTO_PAL_TO_PALM)
        else if (decfmt==DECODE_FORMAT_625) 
		{
			tvfmt=TV_FORMAT_PALM;
			#ifdef ADD_DVI311_SETUP
			dvi311_tv_mode=0x84;    //kevin@2k40517
			#endif
		}
#else//GBM_FORCE_PAL_OUTPUT_NTSC_WHEN_PALM_PALN_AUTO
        else if (decfmt==DECODE_FORMAT_625)
		{
			tvfmt=TV_FORMAT_625_DEFAULT;
			#ifdef ADD_DVI311_SETUP
			dvi311_tv_mode=0x84;    //kevin@2k40517
			#endif
		}
#endif//GBM_FORCE_PAL_OUTPUT_NTSC_WHEN_PALM_PALN_AUTO
    }

#ifdef EASTECH_TV_FORMAT_FORCE_AS_LOGO
    if (tvfmt==TV_FORMAT_AUTO)
    {
        tvfmt = LOGO_TV_FORMAT;
    }
#endif

    // force initial selection when tvfmt==AUTO
    if (Ksetup_tv_format==0xFF && tvfmt==TV_FORMAT_AUTO)
    {
        tvfmt=TV_FORMAT_AUTO_DEFAULT;
#ifdef ADD_DVI311_SETUP
dvi311_tv_mode=0x84;    //kevin@2k40517
#endif
    }

#ifdef ADD_DVI311_SETUP
if(format_change_sign!=dvi311_tv_mode)
    {   
        if(dvi311_tv_mode>0x84 && dvi311_mode==Mode_576P)// NTSC and 480P   @kevin 2k40708
            dvi311_mode=Mode_480P;
        if(dvi311_tv_mode==0x84 && dvi311_mode==Mode_480P)// PAL and 576P   @kevin 2k40708
            dvi311_mode=Mode_576P;
        #ifdef DVD_SETUP_REENG//Modifed by chenzhao on 2004-11-24 21:8   
            setup_VA[SETUP_VA_SPV311MODE]=dvi311_mode+MIN_ITEM_SEL;
        #endif
	scaler_main();
    }
#endif

    // setup tvfmt.
    if (tvfmt!=TV_FORMAT_AUTO && tvfmt!=Ksetup_tv_format)
    {
        int line625;

#ifdef TCON_DRIVER_EL8332
	set_tft_tcon_tv_format(tvfmt);
#endif

        Ksetup_tv_format = tvfmt;

#ifdef	MONE_TVSETUP
        kern_printf("\t %x\n", tvfmt);
#endif

        if (tvfmt==TV_FORMAT_PAL)
        {
            line625 = 1;
            #ifdef PNGPIO_CON_TFT//reset gpio59
            PAL_SET();
            #ifdef EASTWIN
            init_an2526h_pal();
            #endif
            #endif
            tv_setup_pal();
        }
#ifdef  SUPPORT_PALN
        else if (tvfmt==TV_FORMAT_PALN)
        {
            line625 = 1;
            tv_setup_pal_n();
        }
#endif
#ifdef  SUPPORT_PALNc
        else if (tvfmt==TV_FORMAT_PALNC)
        {
            line625 = 1;
            tv_setup_pal_nc();
        }
#endif
#ifdef  SUPPORT_PALM
        else if (tvfmt==TV_FORMAT_PALM)
        {
            line625 = 0;
            tv_setup_pal_m();
        }
#endif
#ifdef  SUPPORT_PAL60
        else if (tvfmt==TV_FORMAT_PAL60)
        {
            line625 = 0;
            #ifdef PNGPIO_CON_TFT //gpio59 is set high
            PAL_SET();
            #ifdef EASTWIN
            init_an2526h_pal();
            #endif
            #endif
            tv_setup_pal60();
        }
#endif
#ifdef  SUPPORT_NTSCJ
        else if (tvfmt==TV_FORMAT_NTSCJ)
        {
            line625 = 0;
            tv_setup_ntscj();
        }
#endif
        else                // default to support NTSC
        {
            line625 = 0;
            #ifdef PNGPIO_CON_TFT //gpio59 is set high
            NTSC_SET();
            #ifdef EASTWIN
            init_an2526h_ntsc();
            #endif
            #endif
            tv_setup_ntsc();
        }
        setVPP_TVformat(line625);

		frctl_set_display_rate();
    }

#ifdef GBM_DEFAULT_NTSC_CAPTION_OFF			//gerry,2004-2-13 14:18
	tv_l21_enable(0);
#endif//GBM_DEFAULT_NTSC_CAPTION_OFF

#ifdef SUPPORT_TOPPOLY_UPS051_Digital_panel
     if(getVPP_TVsystem()==1)
        {
            regs0->tv_pccon[0] = 52;   		// a. HSYNC falling pixel
            regs0->tv_pccon[1] = 53+20;		// b. HSYNC rising pixel
            regs0->tv_pccon[6] = 1;     		// c. Top Vsync falling line       
            regs0->tv_pccon[7] = 4;              		// d. Top Vsync rising line        
            regs0->tv_pccon[8] = 313;   		// e. Bottom Vsync falling line
            regs0->tv_pccon[9] = 316;   		// f. Bottom Vsync rising line 
            send_toppoly_panel_cmd((0x02<<10)+0xd); 
        }
     else 
        { 
            regs0->tv_pccon[0] = 22;           // a. HSYNC falling pixel
            regs0->tv_pccon[1] = 23+20;        // b. HSYNC rising pixel
            regs0->tv_pccon[6] = 525;                 // c. Top Vsync falling line
            regs0->tv_pccon[7] = 3;                         // d. Top Vsync rising line
            regs0->tv_pccon[8] = 263;           // e. Bottom Vsync falling line
            regs0->tv_pccon[9] = 266;  
            send_toppoly_panel_cmd((0x02<<10)+0x9);          
        }
#endif//#ifdef SUPPORT_TOPPOLY_UPS051_Digital_panel

}


//
//
//
void
setup_tv_aspect(int aspect)
{
    if (aspect!=Ksetup_tv_aspect)
    {
        Ksetup_tv_aspect = aspect;
        tv_setup_aspect(aspect);
    }
}


//
//
void
setup_display_brightness(int br)
{
    setVPP_YOffset(br);
}


//
// FUNCTION
// setup_display_format
//
void
setup_display_format(int __hsize, int __vsize, int __src_aspect, int __zoom, int __progressive)
{
    set_vpp_src_aspect(__src_aspect);               // set video-source aspect-ratio
    setVPP_PictureSize(__hsize, __vsize);       // set-size
    if (__progressive)                          // progressive?
    {
        setVPP_chroma_vint_frame();             // chroma: full-frame
        setVPP_luma_vint_frame();               // luma: full-frame
    }
    else
    {
        setVPP_chroma_vint_field();             // chroma: previous-line
        setVPP_luma_vint_field();               // luma: current field
    }
    setVPP_Display(__zoom);                     // other display parameters
}



//
//
//

void set_jpeg_aspect_ratio(int h_ratio, int v_ratio)
{

Ksetup_jpeg_h_aspect = h_ratio;
Ksetup_jpeg_v_aspect = v_ratio;

}


void
set_jpeg_pic_size(int __hsize, int __vsize, int __zoom)
{    
    kern_printf("set_jpeg_pic_size(%d,%d,%d);\n", __hsize, __vsize, __zoom);
    setVPP_ExpansionMode(VPP_EXPANSION_ASPECT);
    setup_display_format(__hsize, __vsize, PIXEL_ASPECT_ALMOST_FULL, __zoom, 1);
    set_jpeg_aspect_ratio(240,240); // max 255;
    setVPP_DoItNow();
}


UINT16  old_hsize;
UINT16  old_vsize;


//
// FUNCTION
// void set_dis_pic_size(h,v)
//
// DESCRIPTION
// generic vpp setup
// setup video according to
//  __hsize,
//  __vsize,
//
// will depends on following characterists
//  preview?
//  vpp_zoom
//  tv_format
//  mode_aspect
//
void
set_dis_pic_size(int __hsize, int __vsize)
{
    int __zoom;
    int __progressive;
    int __src_aspect;
    int __out_aspect;

#ifdef MONE_SIZECHG
    if (old_hsize!=__hsize || old_vsize!=__vsize) {
        printf_nw("change resolution to %dx%d\n", __hsize, __vsize);
    }
#endif

    //
    old_hsize = __hsize;
    old_vsize = __vsize;

    //
    // fix parameter for PREVIEW mode
    if (IsAVDPreview()) {
        // PREVIEW
        __hsize         = 720;          // override fixed size
        __vsize         = 480;
        __zoom          = 0;
        __src_aspect    = ASPECT_4_3;
        __out_aspect    = OUTPUT_ASPECT_NORMAL;
    } else {
        // NORMAL
        __zoom          = vpp_zoom;
        __src_aspect    = mode_aspect;
        __out_aspect    = get_output_aspect();
    }
    __progressive = 1;

    // Setup TV format
    setup_tv_format(tv_format);

    // Setup TV output-aspect (wss signal)
    setup_tv_aspect(__out_aspect);

    // Setup VPP expansion mode
    setVPP_ExpansionMode(VPP_EXPANSION_FIXED);

    // Setup VPP parameters (size, aspect and zoom)
    setup_display_format(__hsize,__vsize,__src_aspect,__zoom,__progressive);
}

