#define	DSPcode		DSP3_WMA_code

#include "dsp3rom.d16.wma.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_WMA =
{
    (BYTE*)DSPcode,
    DSP3_WMA_IM,
    DSP3_WMA_DM,
    DSP3_WMA_PM,
};

#undef	DSPcode
