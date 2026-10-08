#ifndef	__WM8720_H
#define	__WM8720_H

//Register-0

//Register-1

//Register-2
//bit-0
#define WM8720_2_MUTE_ON    (1<<0)
#define WM8720_2_MUTE_OFF   (0<<0)      //default
//bit-1
#define WM8720_2_DEEMPH_ON  (1<<1)
#define WM8720_2_DEEMPH_OFF (0<<1)      //default
//bit-2
#define WM8720_2_OPE_ON     (1<<2)
#define WM8720_2_OPE_Off    (0<<2)      //default
//bit-43
#define WM8720_2_IW_16      (0<<3)      //default
#define WM8720_2_IW_20      (1<<3)
#define WM8720_2_IW_24      (2<<3)
#define WM8720_2_IW_18      (3<<3)
//bit-8765
#define	WM8720_2_PL_MM      (0x0<<5)
#define	WM8720_2_PL_LM      (0x1<<5)
#define	WM8720_2_PL_RM      (0x2<<5)
#define	WM8720_2_PL_CM      (0x3<<5)
#define	WM8720_2_PL_ML      (0x4<<5)
#define	WM8720_2_PL_LL      (0x5<<5)
#define	WM8720_2_PL_RL      (0x6<<5)
#define	WM8720_2_PL_CL      (0x7<<5)
#define	WM8720_2_PL_MR      (0x8<<5)
#define	WM8720_2_PL_LR      (0x9<<5)    //default
#define	WM8720_2_PL_RR      (0xA<<5)
#define	WM8720_2_PL_CR      (0xB<<5)
#define	WM8720_2_PL_MC      (0xC<<5)
#define	WM8720_2_PL_LC      (0xD<<5)
#define	WM8720_2_PL_RC      (0xE<<5)
#define	WM8720_2_PL_CC      (0xF<<5)

//Register-3
//bit-0
#define WM8720_2_FMT_RJ     (0<<0)      //default
#define WM8720_2_FMT_I2S    (1<<0)
//bit-1
#define WM8720_3_LRP_STD	(0<<1)      //default
#define WM8720_3_LRP_INV	(1<<1)
//bit-2
//bit-43
#define WM8720_3_SF_44K     (0<<3)      //default
#define WM8720_3_SF_48K     (1<<3)
#define WM8720_3_SF_32K     (2<<3)

#endif	//__WM8720_H

