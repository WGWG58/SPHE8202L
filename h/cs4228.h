#ifndef	__CS4228_H
#define	__CS4228_H

// reg 1
// CI: MCLK/LRCK
// BRM/HRM: base-rate mode / high-rate mode
#define	CS4228_1_CI_128	(0<<2)
#define	CS4228_1_CI_256	(1<<2)
#define	CS4228_1_CI_384	(2<<2)
#define	CS4228_1_CI_512	(3<<2)
#define	CS4228_1_HRM	(1<<7)
#define	CS4228_1_BRM	(0<<7)

// reg 2
// power down control

#define	CS4228_2_DPWN	(0<<7)
#define	CS4228_2_DNRM	(1<<7)
#define	CS4228_2_APWN	(1<<4)
#define	CS4228_2_ANRM	(0<<4)
#define	CS4228_2_A56PWN	(1<<3)
#define	CS4228_2_A56NRM	(0<<3)
#define	CS4228_2_A34PWN	(1<<2)
#define	CS4228_2_A34NRM	(0<<2)
#define	CS4228_2_A12PWN	(1<<1)
#define	CS4228_2_A12NRM	(0<<1)

// reg 3
// adc control
#define CS4228_3_ADC_MUTEL_NRM	(0<<7)
#define CS4228_3_ADC_MUTEL_ON	(1<<7)
#define CS4228_3_ADC_MUTER_NRM	(0<<6)
#define CS4228_3_ADC_MUTER_ON	(1<<6)
#define CS4228_3_ADC_HPF_EN	(0<<5)
#define CS4228_3_ADC_HPF_DIS	(1<<5)
#define CS4228_3_ADC_HPFZ_NRM	(0<<4)
#define CS4228_3_ADC_HPFZ_FRZ	(1<<4)

// reg 4 
// mute control
#define CS4228_4_MUT1_ON	(1<<2)
#define CS4228_4_MUT2_ON	(1<<3)
#define CS4228_4_MUT3_ON	(1<<4)
#define CS4228_4_MUT4_ON	(1<<5)
#define CS4228_4_MUT5_ON	(1<<6)
#define CS4228_4_MUT6_ON	(1<<7)
#define CS4228_4_MUT1_OFF	(0<<2)
#define CS4228_4_MUT2_OFF	(0<<3)
#define CS4228_4_MUT3_OFF	(0<<4)
#define CS4228_4_MUT4_OFF	(0<<5)
#define CS4228_4_MUT5_OFF	(0<<6)
#define CS4228_4_MUT6_OFF	(0<<7)
#define CS4228_4_RMP_4LRCK	(0<<0)		// per 0.5dB
#define CS4228_4_RMP_8LRCK	(1<<0)
#define CS4228_4_RMP_16LRCK	(2<<0)
#define CS4228_4_RMP_32LRCK	(3<<0)

// reg 5
// mute2 control
#define CS4228_5_MUTEC_NRM	(0<<7)
#define CS4228_5_MUTEC_LOW	(1<<7)
#define CS4228_5_MUTCZ_DIS	(0<<6)
#define CS4228_5_MUTCZ_EN	(1<<6)
#define CS4228_5_HMUTE56_OFF	(0<<3)
#define CS4228_5_HMUTE56_ON	(1<<3)
#define CS4228_5_HMUTE34_OFF	(0<<2)
#define CS4228_5_HMUTE34_ON	(1<<2)
#define CS4228_5_HMUTE12_OFF	(0<<1)
#define CS4228_5_HMUTE12_ON	(1<<1)

// reg 6
// deemphasis control
#define CS4228_6_DEMS_48K	(1<<6)
#define CS4228_6_DEMS_44K	(2<<6)
#define CS4228_6_DEMS_32K	(3<<6)
#define	CS4228_6_DEM1_ON	(1<<0)
#define	CS4228_6_DEM2_ON	(1<<1)
#define	CS4228_6_DEM3_ON	(1<<2)
#define	CS4228_6_DEM4_ON	(1<<3)
#define	CS4228_6_DEM5_ON	(1<<4)
#define	CS4228_6_DEM6_ON	(1<<5)
#define	CS4228_6_DEM1_OFF	(0<<0)
#define	CS4228_6_DEM2_OFF	(0<<1)
#define	CS4228_6_DEM3_OFF	(0<<2)
#define	CS4228_6_DEM4_OFF	(0<<3)
#define	CS4228_6_DEM5_OFF	(0<<4)
#define	CS4228_6_DEM6_OFF	(0<<5)

// reg 7/8/9/a/b/c
// digital volume control
// 0: maximum volume (no attenuation) 255:muted (maximum attenuation) 

// reg d
#define	CS4228_D_DCK_32		(0<<6)
#define	CS4228_D_DCK_48		(1<<6)
#define	CS4228_D_DCK_64		(2<<6)
#define	CS4228_D_DCK_128	(3<<6)
#define	CS4228_D_DMS_SLAVE	(0<<4)
#define	CS4228_D_DMS_MASTER	(3<<4)
#define	CS4228_D_DDF_RJ24	(0<<0)
#define	CS4228_D_DDF_RJ20	(1<<0)
#define	CS4228_D_DDF_RJ16	(2<<0)
#define	CS4228_D_DDF_LJ		(3<<0)
#define	CS4228_D_DDF_I2S	(4<<0)
#define	CS4228_D_DDF_OLDM	(5<<0)

#endif/*__CS4228_H*/


