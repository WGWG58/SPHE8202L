#ifndef TAS5508_PWM_H
#define TAS5508_PWM_H

typedef enum
{
    VOL_CH_MAIN=0,
    VOL_CH_FL,
    VOL_CH_FR,
    VOL_CH_SL,
    VOL_CH_SR,
    VOL_CH_C,
    VOL_CH_SUB,
    VOL_CH_BASS,
    VOL_CH_TREBEL,
    VOL_CH_BSL,
    VOL_CH_BSR,
    VOL_CH_MAX,
}VOL_CH_TYPE;

#define NUM28 UINT32
#define NUM48 UINT64
#define DB0_INT32 ((INT32)0x8000000)
#define DB0_INT64 ((INT64)0x8000000000)
#define INT32_MAX ((INT32)0x7ffffff0)
#define INT64_MAX ((INT64)0x7fffffffffff0000)
#define NUM32TO28(x) (((UINT32)x)>>4)
#define NUM28TO32(x) ((INT32)(((UINT32)x)<<4))
#define NUM64TO48(x) (((UINT64)x)>>16)
#define NUM48TO64(x) ((INT64)(((UINT64)x)<<16))


#define CH_CFG_INPUT_MIX_MASK 0xff        // config  ALL channel

#define CH_CFG_OUTPUT_MIX_MASK 0xff        // config  ALL channel

#define CH_CFG_BASSTREBEL_MASK  0xcf // config without line out L/R
#ifdef UNMUTE_LINE_OUT
    #define CH_MASTER_MUTE_MASK 0xcf
#else//UNMUTE_LINE_OUT
    #define CH_MASTER_MUTE_MASK 0xff
#endif//UNMUTE_LINE_OUT

void init_tas_5508_input_mixer(BYTE cfg_mask);
#ifdef ORITRON_RECEIVER_6001    //hongfeng 2005-08-08
void init_tas_5508_output_mixer(BYTE cfg_mask);
#endif
void init_tas_5508_bass_treble(BYTE cfg_mask);
BYTE test_tas5508(void);
void init_tas_5508();
UINT32 converDB(int db); //n <-> -n dB
void tas_5508_channel_vol(BYTE ch,BYTE vol);
void tas_5508_power_down();
void tas_5508_mute(BYTE val);

#ifdef AMP_SUPPORT_EQ
void tas_5508_set_eq(EQ_TYPE eq);
#endif

#ifdef SUPPORT_HEADPHONE
void tas_5508_enable_headphone(void);
void tas_5508_disable_headphone(void);
#endif  //SUPPORT_HEADPHONE

#endif//#ifndef TAS5508_PWM_H

