#ifndef	__KERNEL_H
#define	__KERNEL_H

// include all other kernel definitions
#include "kinf.h"

//
// from kernel.c
//
void setup_clock_gating(int onoff);

void setup_error_concealment(int level);
void setup_error_mb_limit(int);

void setup_display_format(int hsize, int vsize, int aspect, int zoom, int prog);
void setup_tv_aspect(int aspect);
void setup_display_brightness(int bright);

void set_jpeg_pic_size(int h_size, int v_size, int zoom);
void set_dis_pic_size(int h_size, int v_size);
void set_jpeg_aspect_ratio(int h_ratio, int v_ratio);

//
// FUNCTION
// setup_decode_service(srv)
//
// this will setup srv_kernel(). in mainproc() we will call srv_kernel as
// the main decoding function
//
// SERVICE_CD		decode CD layer
// 			CD mode1 (optional when cd_type_loaded==*CD*)
// 			CD mode2 (optional when cd_type_loaded==*CD*)
// 			11172-1 system layer bitstream (auto detect)
// 			13818-1 system layer bitstream (auto detect)
// SERVICE_CDDA		decode CDDA layer ()
// SERVICE_ROMV		decode ROM (11172-2 video elementary bitstream)
// SERVICE_CARDFILE	decode CARDFILE layer (?)
//
#define	SERVICE_CD	    0
#define SERVICE_CDDA	    1
#define SERVICE_ROMV	    4
#define SERVICE_CARDFILE    8
#define SERVICE_STREAMING   16
#define SERVICE_TS			2
void setup_decode_service(int);


/*
**      TV      TV      TV      TV      TV      TV
*/
//
// setup_tv_format
//

enum {
	TV_FORMAT_NTSC,
        TV_FORMAT_NTSCJ,
	TV_FORMAT_PAL60,
	TV_FORMAT_PAL,
        TV_FORMAT_PALM,
   	TV_FORMAT_PALN,
   	TV_FORMAT_PALNC,
	TV_FORMAT_AUTO,
   	TV_FORMAT_MAX,
};

//#define TV_FORMAT_525_DEFAULT	TV_FORMAT_NTSC
//#define TV_FORMAT_625_DEFAULT	TV_FORMAT_PAL
//#define TV_FORMAT_AUTO_DEFAULT	TV_FORMAT_625_DEFAULT

void setup_tv_format(int fmt);

/* extra definitions */
#define MODE_NTSC   TV_FORMAT_NTSC
#define MODE_NTSCJ  TV_FORMAT_NTSCJ
#define MODE_PAL    TV_FORMAT_PAL
#define MODE_PAL60  TV_FORMAT_PAL60
#define MODE_PALM   TV_FORMAT_PALM
#define MODE_PALN   TV_FORMAT_PALN
#define MODE_PALNC  TV_FORMAT_PALNC
#define MODE_AUTO   TV_FORMAT_AUTO


/*
**
*/

#define	ZOOM_0		0
#define	ZOOM_1		1
#define	ZOOM_2		2
#define	ZOOM_3		3
#define	ZOOM_4		4
#define	ZOOM_5		5
#define	ZOOM_MAX	ZOOMx5
#define	ZOOM_AUTO	6
#define	ZOOM_AUTO2	7

#include "vpp.h"
#define	disable_video()		setVPP_DisableVideo()
#define	disable_video_fields(n)	setVPP_DisableVideoFields(n)
#define	enable_video()		setVPP_EnableVideo()
#define	setup_display_now()	setVPP_DoItNow()

#endif/*__KERNEL_H*/

