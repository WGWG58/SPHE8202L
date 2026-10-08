#ifndef	__PCM1723_H
#define	__PCM1723_H

#define	PCM1723_R2_MUTE_ON		(1<<0)
#define	PCM1723_R2_MUTE_OFF		(0<<0)

#define	PCM1723_R2_DEM_ON		(1<<1)
#define	PCM1723_R2_DEM_OFF		(0<<1)

#define	PCM1723_R2_IW_16B		(0<<3)
#define	PCM1723_R2_IW_20B		(1<<3)
#define	PCM1723_R2_IW_24B		(2<<3)

#define	PCM1723_R2_PL_MM		(0x00<<5)
#define	PCM1723_R2_PL_MR		(0x01<<5)
#define	PCM1723_R2_PL_ML		(0x02<<5)
#define	PCM1723_R2_PL_MC		(0x03<<5)
#define	PCM1723_R2_PL_RM		(0x04<<5)
#define	PCM1723_R2_PL_RR		(0x05<<5)
#define	PCM1723_R2_PL_RL		(0x06<<5)
#define	PCM1723_R2_PL_RC		(0x07<<5)
#define	PCM1723_R2_PL_LM		(0x08<<5)
#define	PCM1723_R2_PL_LR		(0x09<<5)

// PCM1723 register 3  [rrrr_rAAi_SSDD_sALI]
//
// rrrrr:	reserved
// i=0:		zero-detect off
// i=1:		zero-detect on
// SS=00:	44.1kHz group
// SS=01:	48kHz group
// SS=10:	32kHz group
// DD=00:	normal frequency
// DD=01:	double frequency
// DD=10:	half frequency
// s=0:		384fs
// s=1:		256fs
// A=0:		separate attenuate factor
// A=1:		register0
// L=0:		LRCKIN=1 -> left
// L=1:		LRCKIN=0 -> left
// I=0:		normal format (right justify)
// I=1:		i2s format (left justify)
//

#define	PCM1723_R3_FORMAT_I2S		(1<<0)

#define	PCM1723_R3_LRP_LOW_LEFT		(0<<1)
#define	PCM1723_R3_LRP_LOW_RIGHT	(1<<1)

#define	PCM1723_R3_ATC_LR		(0<<2)
#define	PCM1723_R3_ATC_BOTH		(1<<2)

#define	PCM1723_R3_SYS_384fs		(0<<3)
#define	PCM1723_R3_SYS_256fs		(1<<3)

#define	PCM1723_R3_DSR_NORMAL		(0<<4)
#define	PCM1723_R3_DSR_DOUBLE		(1<<4)
#define	PCM1723_R3_DSR_HALF		(2<<4)

#define	PCM1723_R3_SF_44		(0<<6)		// 44.1k group
#define	PCM1723_R3_SF_48		(1<<6)		// 48k group
#define	PCM1723_R3_SF_32		(2<<6)		// 32k group

#define	PCM1723_R3_IZD_OFF		(0<<8)
#define	PCM1723_R3_IZD_ON		(1<<8)		// zero-detect on

#endif/*__PCM1723_H*/

