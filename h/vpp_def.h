#ifndef	__VPPDEC_H
#define	__VPPDEC_H

#ifdef DVD728
#include "mytypes.h"
#endif

//
// setVPP_Display()
// parameter
//
#define DISPLAY_NORMAL     (0)
#define DISPLAY_LETTERBOX  (0)
#define DISPLAY_PANSCAN    (1)
#define DISPLAY_ZOOM_1_2   (2)
#define DISPLAY_ZOOM_1_6   (3)
#define DISPLAY_ZOOM_2_0   (4)
#define DISPLAY_ZOOM_3_0   (5)
#define DISPLAY_ZOOM_4_0   (6)
#define DISPLAY_ZOOM_MAX   DISPLAY_ZOOM_4_0

#ifdef TWELVE_ZOOMFACTORS//axel2004/5/3 12:35pm
#define	VPP_ZOOM0	0
#define	VPP_ZOOM1	1
#define	VPP_ZOOM2	2
#define	VPP_ZOOM3	3
#define	VPP_ZOOM4	4
#define	VPP_ZOOM5	5
#define	VPP_ZOOM6	6
#define	VPP_ZOOM7	7
#define	VPP_ZOOM8	8
#define	VPP_ZOOM9	9
#define	VPP_ZOOMOUT1	10
#define	VPP_ZOOMOUT2	11
#define VPP_ZOOMOUT3    12
#define	VPP_ZOOM_MAX	VPP_ZOOMOUT3
#else
#define	VPP_ZOOM0	0
#define	VPP_ZOOM1	1
#define	VPP_ZOOM2	2
#define	VPP_ZOOM3	3
#define	VPP_ZOOM4	4
#define	VPP_ZOOM5	5
#define	VPP_ZOOMOUT1	6
#define	VPP_ZOOMOUT2	7
#define VPP_ZOOMOUT3    8
#define	VPP_ZOOM_MAX	VPP_ZOOMOUT3
#endif//#ifdef TWELVE_ZOOMFACTORS
// Source Aspect Ratio
#define ASPECT_4_3      		(0)
#define ASPECT_16_9     		(1)
#define ASPECT_ALMOST_FULL    (2)

// pixel aspect ratio: used for MPEG-4
#define PIXEL_ASPECT_FORBIDDEN	0	// forbidden
#define PIXEL_ASPECT_SQUARE		1	// 1:1		(square pixel)
#define PIXEL_ASPECT_PAL_4_3		2	// 12:11	(625 type for 4:3 picture)
#define PIXEL_ASPECT_NTSC_4_3		3	// 10:11	(525 type for 4:3 picture)
#define PIXEL_ASPECT_PAL_16_9		4	// 16:11	(625 type for 16:9 picture)
#define PIXEL_ASPECT_NTSC_16_9	5	// 40:33	(525 type for 16:9 picture)
#define PIXEL_ASPECT_ALMOST_FULL	6	// 40:33	(525 type for 16:9 picture)
#define PIXEL_ASPECT_EXTENDED		15	// extended parameters from MPEG-4

#define	VPP_EXPANSION_FIXED	0
#define	VPP_EXPANSION_ASPECT	1
#define	VPP_EXPANSION_FREE	2

#define	OFFSET_CENTER	    0
#define	OFFSET_ZERO         1
#define	OFFSET_USER         2
#define	OFFSET_USER_CENTER  3


#define	VPP_MATRIX_ENTRY(src,aspect,tv,zoom) \
	(((src)<<5) | ((aspect)<<4) | ((tv)<<3) | (zoom))

//
// Source Resoultion
//
#define VPP_RES_720x480    (0)
#define VPP_RES_720x576    (1)
#define VPP_RES_480x480    (2)
#define VPP_RES_480x576    (3)
#define VPP_RES_352x480    (4)
#define VPP_RES_352x576    (5)
#define VPP_RES_352x240    (6)
#define VPP_RES_352x288    (7)

#define	is_res_pal(res)		((res)&0x01)

//
#define	VPP_RES_PAL	(0x01)
#define	VPP_RES_720	(0x00)
#define	VPP_RES_480	(0x02)
#define	VPP_RES_352	(0x04)

//
// vpp register structure
//
typedef struct
{
   INT16	pic_w;		// 0
   INT16	pic_h;		// 2

   INT16	dis_x_start;	// 4
   INT16	dis_y_start;	// 6
   INT16	dis_x_size ;	// 8
   INT16	dis_y_size ;	// a

#ifdef DVD728
   UINT32	vfactor;	// c
   UINT16	hfactor;	// e

   DS_CFG	vpp_cfg;		// 10
   DS_CFG	ds_field_cfg;	// 12
   DS_CFG	dip_cfg;		// 14
   DS_CFG	dip_param;		// 16
#else
   UINT16	vfactor;	// c
   UINT16	hfactor;	// e

   UINT16	field_exchange;	// 10	vpp parameters
#endif

   UINT16	y_offset;	// 12
   UINT16	cbcr_offset;	// 14	[15:8] cb  [7:0] cr

#ifdef DVD728
   UINT16	line_offset;	// 1c
   UINT16	pix_offset;	// 1d
#else
   UINT8	line_offset;	// 15
   UINT8	pix_offset;	// 16
#endif
} t_vpp_reg;


//
// Source format and aspect-ratio

#define VPP_AUTOEXP         (1<<0)      // expansion or not
#define VPP_ASPECT_RATIO    (1<<1)      // keeping aspect ratio
#define VPP_CENTERED        (1<<2)      // put the picture in center

#endif/*__VPPDEC_H*/

