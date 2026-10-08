#define	DSPcode		DSP3_DTS_5_1CH_16M_code

#include "dsp3rom.d16.dts.5.1ch.16M.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_DTS_5_1CH_16M =
{
    (BYTE*)DSPcode,
    DSP3_DTS_5_1CH_16M_IM,
    DSP3_DTS_5_1CH_16M_DM,
    DSP3_DTS_5_1CH_16M_PM,
};

#undef	DSPcode

