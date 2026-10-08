#define	DSPcode		DSP3_DTS_8202_code

#include "dsp3rom.d16.dts.8202.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_DTS_8202 =
{
    (BYTE*)DSPcode,
    DSP3_DTS_8202_IM,
    DSP3_DTS_8202_DM,
    DSP3_DTS_8202_PM,
};

#undef	DSPcode
