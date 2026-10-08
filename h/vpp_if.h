#ifndef	__VPPIF_H
#define	__VPPIF_H

#include "vpp_def.h" //swpong 2006 0530
#ifdef DVD728
#include "mytypes.h"
#endif

//
// setVPP_Display()
// parameter
//

void      setVPP_OffsetMode(int);
void      setVPP_OffsetX(int);
void      setVPP_OffsetY(int);

#define	  is_res_pal(res)     ((res)&0x01)

void      setVPP_ParamInit(int source_res, int source_aspect, int tv);

void      setVPP_SourceRes(int source_res);
void      setVPP_PictureSize(int w, int h);
unsigned  setVPP_PictureWidth(void);
unsigned  setVPP_PictureHeight(void);

//
// tv format
void      setVPP_TVformat(int);           // 0:525-line system,
                                                // 1:625-line system
// tv aspect-ratio
void      set_vpp_tv_aspect(int);         // 0:4:3, 1:16:9

// video-source aspect-ratio
void      set_vpp_src_aspect(int);        // 0:4:3, 1:16:9

// vpp on/off
void      setVPP_VideoOn(void);
void      setVPP_VideoOff(void);

void      setVPP_chroma_vint_field(void);
void      setVPP_chroma_vint_frame(void);
void      setVPP_luma_vint_field(void);
void      setVPP_luma_vint_frame(void);

void      setVPP_Display(int mode);
void      setVPP_DoIt(void);
void      setVPP_DoItNow(void);
void      setVPP_ExpansionMode(int exp_mode);

void      fieldintr_vpp(int field, int use_pixel_aspect_ratio);

void      setVPP_YOffset(int yoff);

int       getVPP_PictureWidth();
int       getVPP_PictureHeight();

int       getVPP_HOffset();
int       getVPP_VOffset();

void      vpp_reset_framebuf_state(void);

void      setVPP_EnableVideo();
void      setVPP_DisableVideoFields(int n);
void      update_dip_config(int will_be_top_field);
#define   setVPP_DisableVideo()	setVPP_DisableVideoFields(-1)

void      init_vpp(void);

extern	UINT8	pic_offsetx_max;
extern	UINT8	pic_offsety_max;
#define	getVPP_XOffsetMax()	pic_offsetx_max
#define	getVPP_YOffsetMax()	pic_offsety_max


extern	t_vpp_reg	vpp_reg;

//
// TV format and aspect-ratio
extern  INT8        vppsetup_tv_aspect;
extern	INT8		vppsetup_tv_system;
#define getVPP_TVsystem()	(vppsetup_tv_system)

//
// Source format and aspect-ratio
extern  INT8            vppsetup_src_aspect;

extern UINT8 	Ksetup_jpeg_h_aspect;
extern UINT8 	Ksetup_jpeg_v_aspect;

INT8    dec_field_dip_cntr;


//
// display size
void    set_vpp_disp_size(int w, int h);
int     get_vpp_disp_width(void);
int     get_vpp_disp_height(void);
void    set_vpp_disp_window(int x, int y, int w, int h);

//
// OLD
// for vpp.c compatible
void vpp_set_pic(int w, int h);


//8202L #define HD_DISPLAY_CONTROLLER related

extern UINT8	HD_display_controller;
extern void setVPP_HD_isplay_controller(UINT8 enable);
extern void setvpp_use_source_par(UINT32	input_use_source_par);
extern UINT32 getvpp_pixel_aspect_ratio();
extern UINT32 getvpp_user_par(UINT8 *width, UINT8 *height);
extern int getVPP_ExpansionMode();
extern void setVPP_ExpansionMode(int exp_mode);
extern void setvpp_pixel_aspect_ratio(UINT8 ratio);
extern void setvpp_user_par(UINT8 width, UINT8 height);


#endif/*__VPPIF_H*/

