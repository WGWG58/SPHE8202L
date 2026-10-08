#define	DSPcode		DSP3_AC3_code

#include "dsp3rom.d16.ac3.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_AC3 =
{
    (BYTE*)DSPcode,
    DSP3_AC3_IM,
    DSP3_AC3_DM,
    DSP3_AC3_PM,
};

#undef	DSPcode
