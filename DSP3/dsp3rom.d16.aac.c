#define	DSPcode		DSP3_AAC_code

#include "dsp3rom.d16.aac.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_AAC =
{
    (BYTE*)DSPcode,
    DSP3_AAC_IM,
    DSP3_AAC_DM,
    DSP3_AAC_PM,
};

#undef	DSPcode
