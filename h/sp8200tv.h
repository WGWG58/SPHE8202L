#ifndef	__8200TV_H
#define	__8200TV_H

#define TV_OUT_CScCSc			(0)
#define TV_OUT_CScCCC			(1)
#define TV_OUT_CScYUV			(2)
#define TV_OUT_CScRGB			(3)
#define TV_OUT_CScYBR			(4)
#define TV_OUT_CScRgb			(5)
#define TV_OUT_CScYuv			(6)
#define TV_OUT_YUVRGB			(7)
#define TV_OUT_YUVYUV			(8)
#define TV_OUT_YBRYBR			(9)
#define TV_OUT_RgbRgb			(10)
#define TV_OUT_YuvYuv			(11)
#define TV_OUT_YBRRgb			(12)
#define TV_OUT_YUVRgb			(13)
#define TV_OUT_RGBYBR			(14)
#define TV_OUT_RGBYuv			(15)


void    setup_display(int fmt, int pscan);
void	setup_sync_on_G (int sync);
int     set_tv_clipping_mode(int mode);

void	sp8200tv_setup_output(int output);		// see TV_OUT_*

void	sp8200tv_setup_line21_onoff(int onoff);		// turn-on/off line21 output

void	sp8200tv_setup_dacoff(unsigned);
void	sp8200tv_setup_dachalf(unsigned);
void	sp8200tv_setup_dac_current(UINT32);

void	sp8200tv_setup_ntsc(void);
void	sp8200tv_setup_ntscj(void);

void	sp8200tv_setup_pal(void);
void	sp8200tv_setup_pal60(void);
void	sp8200tv_setup_pal_m(void);
void	sp8200tv_setup_pal_n(void);
void	sp8200tv_setup_pal_nc(void);

void	sp8200tv_setup_aspect(int);
void	sp8200tv_setup_int(void);
void	sp8200tv_setup_nint(void);
void	sp8200tv_setup(void);
void	sp8200tv_set_misc(int);


void	sp8200tv_setup_custom_output(int output);
void 	sp8200tv_setup_54mhz_output(void);
void 	sp8200tv_setup_27mhz_output(void);

// for 8202L, zyl
void	sp8200tv_set_hd_mode(int hd_mode, int hd_dispformat);
void	sp8200tv_setup_dac_clock(int dac_clk_mode);
void	sp8200tv_init_setup(void);


#endif

