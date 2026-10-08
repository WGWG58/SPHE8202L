#define	DSPcode		DSP3_HDCD_code

#include "dsp3rom.d16.hdcd.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_HDCD =
{
    (BYTE*)DSPcode,
    DSP3_HDCD_IM,
    DSP3_HDCD_DM,
    DSP3_HDCD_PM,
};

#undef	DSPcode
