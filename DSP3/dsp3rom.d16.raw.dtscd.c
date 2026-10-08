#define	DSPcode		DSP3_RAW_DTSCD_code

#include "dsp3rom.d16.raw.dtscd.inc"    // 2004/11/11 yltseng
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_RAW_DTSCD =
{
    (BYTE*)DSPcode,
    DSP3_RAW_DTSCD_IM,
    DSP3_RAW_DTSCD_DM,
    DSP3_RAW_DTSCD_PM,
};

#undef	DSPcode
