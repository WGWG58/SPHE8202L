#ifndef	__AUDCLK_H
#define	__AUDCLK_H

#include "regmap.h"

#define	AUDCLK_XCK_CHANGING   		    0x8000
#define	AUDCLK_XCK_ENABLE                   0x4000
#define	AUDCLK_XCKPAD_ENABLE                0x2000
#define AUDCLK_XCK_SRC_ZERO                 (0<<11)
#define AUDCLK_XCK_SRC_135                  (1<<11)
#define AUDCLK_XCK_SRC_147                  (2<<11)
#define AUDCLK_XCK_SRC_EXT                  (3<<11)
#define AUDCLK_XCK_SRC_MASK                 (3<<11)

#define	AUDCLK_128XCK_04096     		0x7183		// 147/36,		128*32k,
#define	AUDCLK_128XCK_05644	     		0x6887		// 135/24,		128*44.1k,
#define	AUDCLK_128XCK_06144     		0x7087		// 147/24,		128*48k,
#define	AUDCLK_128XCK_11290     		0x6883		// 135/12,		128*88.2k,
#define	AUDCLK_128XCK_12288     		0x7083		// 147/12,		128*96k,
#define	AUDCLK_128XCK_22579     		0x6881		// 135/6,		128*176.4k,
#define	AUDCLK_128XCK_24576     		0x7081		// 147/6,		128*192k,
#define	AUDCLK_256XCK_04096     		0x7183		// 147/36,		256*16k,
#define	AUDCLK_256XCK_05644     		0x6887		// 135/24,		256*22.5k,
#define	AUDCLK_256XCK_06144     		0x7083		// 147/24,		256*24k,
#define	AUDCLK_256XCK_08192     		0x7181		// 147/18,		256*32k,
#define	AUDCLK_384XCK_08467     		0x680f		// 135/16,		384*22.5k,
#define	AUDCLK_384XCK_09216     		0x700f		// 147/16,		384*24k,
#define	AUDCLK_256XCK_11290     		0x6883		// 135/12,		256*44.1k,
#define	AUDCLK_256XCK_12288     		0x7083		// 147/12,		256*48k,
#define	AUDCLK_384XCK_12288     		0x7083		// 147/12,		384*32k,
#define	AUDCLK_384XCK_16934     		0x6807		// 135/8,		384*44.1k,
#define	AUDCLK_384XCK_18432     		0x7007		// 147/8,		384*48k,
#define	AUDCLK_256XCK_22579     		0x6881		// 135/6,		256*88.2k,
#define	AUDCLK_256XCK_24576     		0x7081		// 147/6,		256*96k,
#define	AUDCLK_384XCK_33869     		0x6803		// 135/4,		384*88.2k,
#define	AUDCLK_384XCK_36864     		0x7003		// 147/4,		384*96k,
#define	AUDCLK_256XCK_45158     		0x6880		// 135/3,		256*176.4k,
#define	AUDCLK_256XCK_49152     		0x7080		// 147/3,		256*192k,
#define	AUDCLK_384XCK_67736     		0x6801		// 135/2,		384*176.4k,
#define	AUDCLK_384XCK_73728     		0x7001		// 147/2,		384*192k,

//
// BCK settings
#define	AUDCLK_32BCK_384        		0x6083		// 384/32
#define	AUDCLK_48BCK_384        		0x6007		// 384/48
#define	AUDCLK_64BCK_384        		0x6081		// 384/64
#define	AUDCLK_32BCK_256        		0x6007		// 256/32
#define	AUDCLK_64BCK_256        		0x6003		// 256/64
#define	AUDCLK_64BCK_128        		0x6001		// 128/64

//
// IEC BCK, always 128*fs
#define	AUDCLK_128IEC_384	        	0x6080		// 384/128
#define	AUDCLK_128IEC_256	        	0x6001		// 256/128

// ADC CLK, 64*fs, 128*fs for AD9735
#define	AUDCLK_64ADC_384	        	0x6081		// 384/64
#define	AUDCLK_64ADC_256	        	0x6003		// 256/64
#define	AUDCLK_128ADC_384	        	0x6080		// 384/128
#define	AUDCLK_128ADC_256	        	0x6001		// 256/128

#define XCKCFG      regs0->aud_xck_cfg
#define	AUD_IS_XCK_ON()			        ((XCKCFG & AUDCLK_XCK_SRC_MASK)!=AUDCLK_XCK_SRC_ZERO)
#define	AUD_IS_XCK_CHANGING()			(XCKCFG & AUDCLK_XCK_CHANGING)

#define	AUD_ENABLE_XCK_CLK()			(XCKCFG |= AUDCLK_XCK_ENABLE)
#define	AUD_DISABLE_XCK_CLK()			(XCKCFG &= ~AUDCLK_XCK_ENABLE)

#define	AUD_ENABLE_XCK_PAD()			(XCKCFG |= AUDCLK_XCKPAD_ENABLE)
#define	AUD_DISABLE_XCK_PAD()			(XCKCFG &= ~AUDCLK_XCKPAD_ENABLE)

#define	AUD_ENABLE_CLK_ALL()			(regs0->au)

#define	AUD_SET_XCK(x)					(regs0->aud_xck_cfg = (x))
#define	AUD_SET_BCK(x)					(regs0->aud_pcm_bck_cfg = (x))
#define	AUD_SET_IEC(x)					(regs0->aud_iec_bclk_cfg = (x))
#define	AUD_SET_ADC(x)					(regs0->aud_adc_mclk_cfg = (x))

#if defined(SPHE1000) || defined(IC_1002)
#define	AUD_CLR_PLLA()					(regs0->sft_cfg6 &= ~(0x800))
#define	AUD_SET_PLLA(x)					(regs0->sft_cfg6 |= (0x800*(x)))
#endif

#endif/*__AUDCLK_H*/
