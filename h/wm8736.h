#ifndef	__WM8736_H
#define	__WM8736_H

#define	WM8736_2_MUTE_ON	(1<<0)		// 1001_10_000
#define	WM8736_2_MUTE_OFF	(0<<0)
#define	WM8736_2_DEEMPH_ON	(1<<1)
#define	WM8736_2_DEEMPH_OFF	(0<<1)
#define	WM8736_2_PWDN_ON	(1<<2)
#define	WM8736_2_PWDN_OFF	(0<<2)
#define	WM8736_2_IW_16		(0<<3)
#define	WM8736_2_IW_20		(1<<3)
#define	WM8736_2_IW_24		(2<<3)
#define	WM8736_2_IW_18		(3<<3)

#define	WM8736_2_PL_MM		(0x0<<5)
#define	WM8736_2_PL_LM		(0x1<<5)
#define	WM8736_2_PL_RM		(0x2<<5)
#define	WM8736_2_PL_CM		(0x3<<5)
#define	WM8736_2_PL_ML		(0x4<<5)
#define	WM8736_2_PL_LL		(0x5<<5)
#define	WM8736_2_PL_RL		(0x6<<5)
#define	WM8736_2_PL_CL		(0x7<<5)
#define	WM8736_2_PL_MR		(0x8<<5)
#define	WM8736_2_PL_LR		(0x9<<5)
#define	WM8736_2_PL_RR		(0xA<<5)
#define	WM8736_2_PL_CR		(0xB<<5)
#define	WM8736_2_PL_MC		(0xC<<5)
#define	WM8736_2_PL_LC		(0xD<<5)
#define	WM8736_2_PL_RC		(0xE<<5)
#define	WM8736_2_PL_CC		(0xF<<5)
//3
#define	WM8736_3_I2S_OFF	(0<<0)
#define	WM8736_3_I2S_ON		(1<<0)
#define WM8736_3_LRP_STD	(0<<1)
#define WM8736_3_LRP_INV	(1<<1)
#define	WM8736_3_SF_44k		(0<<6)
#define	WM8736_3_SF_48k		(1<<6)
#define	WM8736_3_SF_32k		(2<<6)
#define	WM8736_3_IZD_OFF	(0<<8)
#define	WM8736_3_IZD_ON		(1<<8)

#endif	/*__WM8736_H*/

