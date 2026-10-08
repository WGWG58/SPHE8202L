#ifndef	__TVIF_H
#define	__TVIF_H

//
// for supporting 2 tv-encoder you must be careful about
// the hvsync.
//#define SUPPORT_SP721
//#define SUPPORT_ADV7176
#define SUPPORT_SP8200


#include "sp721.h"
#include "sp8200tv.h"
#include "adv7176.h"

enum
{
	TVOUT_SVIDEO1=1,
	TVOUT_YCbCr=0,
	TVOUT_RGB=1,
	TVOUT_YPbPr=2,
	TVOUT_VGA=3,
#ifdef EASTWIN
	TVOUT_SVIDEO=4,
	TVOUT_OFF=5//jhuang eastwin 2004/8/16
#else
	TVOUT_SVIDEO=4
#endif
};

// for 8202L, zyl
enum
{
	HD_1080I_F60 = 0,
	HD_1080I_F50 = 1,
	HD_720P_F60 = 2,
	HD_720P_F50 = 3,
	HD_1080P_F60 = 4,
	HD_1080P_F50 = 5
};

static	inline	void	tv_setup_int(void)
{
#ifdef SUPPORT_SP8200
  sp8200tv_setup_int();
#endif
}


static	inline	void	tv_setup_nint(void)
{
#ifdef SUPPORT_SP8200
  sp8200tv_setup_nint();
#endif
}

// NTSC systems
static	inline	void	tv_setup_ntsc(void)
{
#ifdef SUPPORT_SP8200
  sp8200tv_setup_ntsc();
#endif
#ifdef SUPPORT_SP721
  sp721_setup_ntsc();
#endif
#ifdef	SUPPORT_ADV7176
  adv7176_setup_ntsc();
#endif
}

static	inline	void	tv_setup_ntscj(void)
{
#ifdef SUPPORT_SP8200
  sp8200tv_setup_ntscj();
#endif
}

// PAL systems
static	inline	void	tv_setup_pal60(void)
{
#ifdef SUPPORT_SP8200
  sp8200tv_setup_pal60();
#endif
#ifdef	SUPPORT_SP721
  sp721_setup_pal60();
#endif
#ifdef	SUPPORT_ADV7176
  adv7176_setup_pal60();
#endif
}

static	inline	void	tv_setup_pal(void)
{
#ifdef SUPPORT_SP8200
  sp8200tv_setup_pal();
#endif
#ifdef	SUPPORT_SP721
  sp721_setup_pal();
#endif
#ifdef	SUPPORT_ADV7176
  adv7176_setup_pal();
#endif
}

static	inline	void	tv_setup_pal_m(void)
{
#ifdef SUPPORT_SP8200
  sp8200tv_setup_pal_m();
#endif
}

static	inline	void	tv_setup_pal_n(void)
{
#ifdef SUPPORT_SP8200
  sp8200tv_setup_pal_n();
#endif
}

static	inline	void	tv_setup_pal_nc(void)
{
#ifdef SUPPORT_SP8200
  sp8200tv_setup_pal_nc();
#endif
}

static	inline	void	tv_setup_output(int opt)
{
#ifdef SUPPORT_SP8200
  sp8200tv_setup_output(opt);
#endif
#ifdef	SUPPORT_SP721
  sp721_setup_output(opt);
#endif
#ifdef	SUPPORT_ADV7176
  adv7176_setup_output(opt);
#endif
}


static	inline	void	tv_setup_custom_output(int opt)
{
  sp8200tv_setup_custom_output(opt);
}


static	inline	void	tv_setup(void)
{
#ifdef SUPPORT_SP8200
  sp8200tv_setup();
#endif
#ifdef	SUPPORT_SP721
  sp721_setup();
#endif
#ifdef	SUPPORT_ADV7176
  adv7176_setup();
#endif
}


static	inline	void	tv_setup_aspect(int aspect)
{
#ifdef SUPPORT_SP8200
    sp8200tv_setup_aspect(aspect);
#endif
#ifdef	SUPPORT_SP721
    sp721_setup_aspect(aspect);
#endif
}


static	inline	void	tv_l21_enable(int enable)
{
#ifdef  SUPPORT_SP8200
    sp8200tv_setup_line21_onoff(enable);
#endif
#ifdef  SUPPORT_SP721
    sp721_l21_enable(enable);
#endif
}


static	inline	void	tv_setup_misc(int type)
{
#ifdef SUPPORT_SP8200
  sp8200tv_set_misc(type);
#endif
#ifdef	SUPPORT_SP721
  sp721_set_misc(type);
#endif
}


static	inline	void	tv_writel21_data(int n, unsigned d)
{
#ifdef SUPPORT_SP8200
  n=n;
  d=d;
#endif
#ifdef	SUPPORT_SP721
  sp721_writel21_data(n,d);
#endif
#ifdef	SUPPORT_ADV7176
  adv7176_writel21_data(n,d);
#endif
}

#define TV_DAC_A    (1<<0)
#define TV_DAC_B    (1<<1)
#define TV_DAC_C    (1<<2)
#define TV_DAC_D    (1<<3)
#define TV_DAC_E    (1<<4)
#define TV_DAC_F    (1<<5)

#ifdef	IC_8202E
#define TV_DAC_A_HALF    (6<<0)
#define TV_DAC_B_HALF    (6<<3)
#define TV_DAC_C_HALF    (6<<6)
#define TV_DAC_D_HALF    (6<<9)
#define TV_DAC_E_HALF    (6<<12)
#define TV_DAC_F_HALF    (6<<15)

#define TV_DAC_A_QUART   (7<<0)
#define TV_DAC_B_QUART   (7<<3)
#define TV_DAC_C_QUART   (7<<6)
#define TV_DAC_D_QUART   (7<<9)
#define TV_DAC_E_QUART   (7<<12)
#define TV_DAC_F_QUART   (7<<15)
#endif	// IC_8202E

#ifdef	IC_8202L
#define TV_DAC_A_QUART   (7<<0)
#define TV_DAC_B_QUART   (7<<3)
#define TV_DAC_C_QUART   (7<<6)
#define TV_DAC_D_QUART   (7<<9)
#endif

static	inline	void	tv_dachalf(unsigned v)
{
#ifdef  SUPPORT_SP8200
    sp8200tv_setup_dachalf(v);
#endif
}

static	inline	void	tv_dac_current(UINT32 v)
{
#ifdef  SUPPORT_SP8200
    sp8200tv_setup_dac_current(v);
#endif
}



static	inline	void	tv_dacoff(unsigned v)
{
#ifdef  SUPPORT_SP8200
    sp8200tv_setup_dacoff(v);
#endif
}

static	inline	void	tv_sleep(void)
{
#ifdef	SUPPORT_SP721
	sp721_sleep();
#endif
#ifdef	SUPPORT_ADV7176
	adv7176_sleep();
#endif
#ifdef  SUPPORT_SP8200
	sp8200tv_setup_dacoff(0xff);
#endif
}


static	inline	void	tv_resume(void)
{
#ifdef	SUPPORT_SP721
  sp721_resume();
#endif
#ifdef	SUPPORT_ADV7176
  adv7176_resume();
#endif
}

static inline void sp8200tv_vdac_clk_54mhz_output(void){

#ifdef SUPPORT_SP8200
    sp8200tv_setup_54mhz_output();
#endif
}

/*#ifdef SUPPORT_6500
extern void SCL_6500_setup_mv(const UINT8 mv_type, const UINT8 p[], const UINT16 amamp);
#endif


static inline void sp8200tv_external_mv(const UINT8 mv_type __UNUSED, const UINT8 p[] __UNUSED, const UINT16 amamp __UNUSED){

#ifdef SUPPORT_6500
	// seanlin 20060313 , define in kernel.c
    SCL_6500_setup_mv(mv_type, p, amamp);
#endif
}*/ //mark it ,eric lin 2006-07-20 ,function pointer for 6500 DAC Marcovision  

void (*sp8200tv_external_mv)(int a, int b, int c);////eric lin 2006-07-20 ,function pointer for 6500 DAC Marcovision  

#endif/*__TVIF_H*/

