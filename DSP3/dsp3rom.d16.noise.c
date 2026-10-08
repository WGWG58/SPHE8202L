#define	DSPcode		DSP3_NOISE_code

#include "dsp3rom.d16.noise.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_NOISE =
{
    (BYTE*)DSPcode,
    DSP3_NOISE_IM,
    DSP3_NOISE_DM,
    DSP3_NOISE_PM,
};

#undef	DSPcode
