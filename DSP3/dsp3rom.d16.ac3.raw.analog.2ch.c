#define	DSPcode		DSP3_AC3_RAW_ANALOG_2CH_code

#include "dsp3rom.d16.ac3.raw.analog.2ch.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_AC3_RAW_ANALOG_2CH =
{
    (BYTE*)DSPcode,
    DSP3_AC3_RAW_ANALOG_2CH_IM,
    DSP3_AC3_RAW_ANALOG_2CH_DM,
    DSP3_AC3_RAW_ANALOG_2CH_PM,
};

#undef	DSPcode
