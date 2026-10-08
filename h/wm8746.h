#ifndef	__WM8746_H
#define	__WM8746_H

#define	WM8746_2_MUTE_ON	(1<<0)
#define	WM8746_2_MUTE_OFF	(0<<0)
#define	WM8746_2_DEEMPH_ON	(1<<1)
#define	WM8746_2_DEEMPH_OFF	(0<<1)
#define	WM8746_2_PWDN_ON	(1<<2)
#define	WM8746_2_PWDN_OFF	(0<<2)
#define	WM8746_2_ATC_L		(1<<3)		// use L vol setting 
#define	WM8746_2_ATC_LR		(0<<3)		// separate vol setting 
#define	WM8746_2_IZD_ON		(1<<4)		// infinite zero detection ON
#define	WM8746_2_IZD_OFF	(0<<4)		// infinite zero detection OFF
#define	WM8746_2_PL_MM		(0x0<<5)
#define	WM8746_2_PL_LM		(0x1<<5)
#define	WM8746_2_PL_RM		(0x2<<5)
#define	WM8746_2_PL_CM		(0x3<<5)
#define	WM8746_2_PL_ML		(0x4<<5)
#define	WM8746_2_PL_LL		(0x5<<5)
#define	WM8746_2_PL_RL		(0x6<<5)
#define	WM8746_2_PL_CL		(0x7<<5)
#define	WM8746_2_PL_MR		(0x8<<5)
#define	WM8746_2_PL_LR		(0x9<<5)
#define	WM8746_2_PL_RR		(0xA<<5)
#define	WM8746_2_PL_CR		(0xB<<5)
#define	WM8746_2_PL_MC		(0xC<<5)
#define	WM8746_2_PL_LC		(0xD<<5)
#define	WM8746_2_PL_RC		(0xE<<5)
#define	WM8746_2_PL_CC		(0xF<<5)
//3
#define	WM8746_3_FMT_RJ		(0x0<<0)
#define	WM8746_3_FMT_LJ		(0x1<<0)
#define	WM8746_3_FMT_I2S	(0x2<<0)
#define	WM8746_3_FMT_DSP	(0x3<<0)
#define WM8746_3_LRP_STD	(0<<2)
#define WM8746_3_LRP_INV	(1<<2)
#define WM8746_3_BCP_STD	(0<<3)
#define WM8746_3_BCP_INV	(1<<3)
#define WM8746_3_WL_16		(0<<4)
#define WM8746_3_WL_20		(1<<4)
#define WM8746_3_WL_24		(2<<4)
#define WM8746_3_WL_32		(3<<4)		// not in RJ mode
#define	WM8746_3_PHASE0_STD	(0<<6)
#define	WM8746_3_PHASE1_STD	(0<<7)
#define	WM8746_3_PHASE2_STD	(0<<8)
#define	WM8746_3_PHASE0_INV	(1<<6)
#define	WM8746_3_PHASE1_INV	(1<<7)
#define	WM8746_3_PHASE2_INV	(1<<8)
//9
#define	WM8746_9_2SPD_ON	(1<<1)
#define	WM8746_9_ZCD_DISABLE	(1<<0)
#define	WM8746_9_2SPD_OFF	(0<<1)
#define	WM8746_9_ZCD_ENABLE	(0<<0)

#endif	/*__WM8746_H*/

