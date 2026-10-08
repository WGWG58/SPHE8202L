#define	DSPcode		DSP3_TUNER_code

#include "dsp3rom.d16.tuner.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_TUNER =
{
    (BYTE*)DSPcode,
    DSP3_TUNER_IM,
    DSP3_TUNER_DM,
    DSP3_TUNER_PM,
};

#undef	DSPcode
