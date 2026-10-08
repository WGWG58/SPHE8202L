#ifndef	__SYSCLK_H
#define __SYSCLK_H

#include "syscfg.h"

#define FSYS_MULT_6_75      0.25        // 1/16
#define FSYS_MULT_13_5      0.5         // 1/8
#define FSYS_MULT_20_25     0.75        // 9/8
#define FSYS_MULT_27        1.0         // 1/4
#define FSYS_MULT_33_75     1.25        // 5/4
#define FSYS_MULT_40_5      1.5         // 9/4
#define FSYS_MULT_47_25     1.75        // 13/4
#define FSYS_MULT_54        2.0         // 1/2
#define FSYS_MULT_60_75     2.25        // 3x/2
#define FSYS_MULT_67_5      2.5         // 5/2
#define FSYS_MULT_74_25     2.75        // 7/2
#define FSYS_MULT_81        3.0         // 9/2
#define FSYS_MULT_87_75     3.25        // 11/2
#define FSYS_MULT_94_5      3.5         // 13/2
#define FSYS_MULT_101_25    3.75        // 0 (base frequency)
#define FSYS_MULT_108       4.0         // 1
#define FSYS_MULT_114_75    4.25        // 2x
#define FSYS_MULT_121_5     4.5         // 3x
#define FSYS_MULT_128_25    4.75        // 4
#define FSYS_MULT_135       5.0         // 5
#define FSYS_MULT_141_75    5.25        // 6
#define FSYS_MULT_148_5     5.5         // 7
#define FSYS_MULT_155_25    5.75        // 8
#define FSYS_MULT_162       6.0         // 9
#define FSYS_MULT_168_75    6.25        // 10
#define FSYS_MULT_175_5     6.5         // 11
#define FSYS_MULT_182_25    6.75        // 12
#define FSYS_MULT_189       7.0         // 13

#define FSYS_UV_6_75        1
#define FSYS_UV_13_5        2
#define FSYS_UV_20_25       3
#define FSYS_UV_27          4
#define FSYS_UV_33_75       5
#define FSYS_UV_40_5        6
#define FSYS_UV_47_25       7
#define FSYS_UV_54          8
#define FSYS_UV_60_75       9
#define FSYS_UV_67_5        10
#define FSYS_UV_74_25       11
#define FSYS_UV_81          12
#define FSYS_UV_87_75       13
#define FSYS_UV_94_5        14
#define FSYS_UV_101_25      15
#define FSYS_UV_108         16
#define FSYS_UV_114_75      17
#define FSYS_UV_121_5       18
#define FSYS_UV_128_25      19
#define FSYS_UV_135         20
#define FSYS_UV_141_75      21
#define FSYS_UV_148_5       22
#define FSYS_UV_155_25      23
#define FSYS_UV_162         24
#define FSYS_UV_168_75      25
#define FSYS_UV_175_5       26
#define FSYS_UV_182_25      27
#define FSYS_UV_189         28

#ifndef EMULATION
/*
** REAL
*/
#if defined(F114_75)
#define	FSYS_MULT       FSYS_MULT_114_75
#elif defined(F121_5)
#define	FSYS_MULT       FSYS_MULT_121_5
#elif defined(F128_25)
#define	FSYS_MULT       FSYS_MULT_128_25
#elif defined(F135)
#define	FSYS_MULT       FSYS_MULT_135
#elif defined(F141_75)
#define	FSYS_MULT       FSYS_MULT_141_75
#elif defined(F148_5)
#define	FSYS_MULT       FSYS_MULT_148_5
#elif defined(F155_25)
#define	FSYS_MULT       FSYS_MULT_155_25
#elif defined(F162)
#define	FSYS_MULT       FSYS_MULT_162
#elif defined(F175_5)
#define	FSYS_MULT       FSYS_MULT_175_5
#elif defined(F189)
#define	FSYS_MULT       FSYS_MULT_189
#elif defined(F6_25)
#define	FSYS_MULT       FSYS_MULT_6_25
#elif defined(F13_5)
#define	FSYS_MULT       FSYS_MULT_13_5
#elif defined(F27)
#define	FSYS_MULT       FSYS_MULT_27
#elif defined(F33_75)
#define	FSYS_MULT       FSYS_MULT_33_75
#elif defined(F40_5)
#define	FSYS_MULT       FSYS_MULT_40_5
#elif defined(F47_25)
#define	FSYS_MULT       FSYS_MULT_47_25
#elif defined(F54)
#define	FSYS_MULT       FSYS_MULT_54
#elif defined(F60_75)
#define	FSYS_MULT       FSYS_MULT_60_75
#elif defined(F67_5)
#define	FSYS_MULT       FSYS_MULT_67_5
#elif defined(F74_25)
#define	FSYS_MULT       FSYS_MULT_74_25
#elif defined(F81)
#define	FSYS_MULT       FSYS_MULT_81
#elif defined(F87_75)
#define	FSYS_MULT       FSYS_MULT_87_75
#elif defined(F94_5)
#define	FSYS_MULT       FSYS_MULT_94_5
#elif defined(F101_25)
#define	FSYS_MULT       FSYS_MULT_101_25
#else
#define	FSYS_MULT       FSYS_MULT_108               // DEFAULT
#endif

#define	SYSCLK		((int)(FSYS_MULT * 27000000))
#define	DISCLK          SYSCLK

#else/*EMULATION*/

/*
** EMULATION
*/
#undef SYSCLK
#ifdef NO_AUDIO_DSP
#define SYSCLK		((int)(10 * 1000000))	// 10MHZ
#else
#define SYSCLK		((int)(5 * 1000000))	// 10MHZ
#endif

#ifdef DTH_CFG_ENABLE
#define DISCLK		((int)(27.0 * 4.5 * 1000000))	// 121.5MHZ
#else
#define DISCLK		((int)(27.0 * 4 * 1000000))	// 108MHZ
#endif

#endif/*EMULATION*/

#define	STC_DIVISOR	(((int)(DISCLK/90000.0+0.5))-1)

#endif
