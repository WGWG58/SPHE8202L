#define	DSPcode		DSP3_DTSCD_code

#include "dsp3rom.d16.dtscd.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_DTSCD =
{
    (BYTE*)DSPcode,
    DSP3_DTSCD_IM,
    DSP3_DTSCD_DM,
    DSP3_DTSCD_PM,
};

#undef	DSPcode
