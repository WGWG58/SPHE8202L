#define	DSPcode		DSP3_SPG_code

#include "dsp3rom.d16.spg.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_SPG =
{
    (BYTE*)DSPcode,
    DSP3_SPG_IM,
    DSP3_SPG_DM,
    DSP3_SPG_PM,
};

#undef	DSPcode
