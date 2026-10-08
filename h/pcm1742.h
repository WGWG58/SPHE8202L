#ifndef	__PCM1742_H
#define	__PCM1742_H

//Register-18
#define	PCM1742_R18_MUTE_ON             (3<<0)
#define	PCM1742_R18_MUTE_OFF            (0<<0)

#define	PCM1742_R18_OVER_SAMPLE_ON      (1<<6)
#define	PCM1742_R18_OVER_SAMPLE_OFF     (0<<6)

//Register-19
#define	PCM1742_R19_SF_44               (0<<5)
#define	PCM1742_R19_SF_48               (1<<5)
#define	PCM1742_R19_SF_32               (2<<5)

//Register-20
#define	PCM1742_R20_FMT_24RJ            (0<<0)
#define	PCM1742_R20_FMT_20RJ            (1<<0)
#define	PCM1742_R20_FMT_18RJ            (2<<0)
#define	PCM1742_R20_FMT_16RJ            (3<<0)
#define	PCM1742_R20_FMT_I2S             (4<<0)
#define	PCM1742_R20_FMT_LJ              (5<<0)

#ifdef PCM1742_COMMON_ZERO_FLAG
#define SET_PCM1742_COMMON_ZERO				(0x04)
#endif

#endif  //__PCM1742_H

