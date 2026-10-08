#define	DSPcode		DSP3_DTS_DTS_code

#include "dsp3rom.d16_dts.dts.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_DTS_DTS =
{
    (BYTE*)DSPcode,
    DSP3_DTS_DTS_IM,
    DSP3_DTS_DTS_DM,
    DSP3_DTS_DTS_PM,
};

#undef	DSPcode
