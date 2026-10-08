#define	DSPcode		DSP3_PPCM_code

#include "dsp3rom.d16.ppcm.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_PPCM =
{
    (BYTE*)DSPcode,
    DSP3_PPCM_IM,
    DSP3_PPCM_DM,
    DSP3_PPCM_PM,
};

#undef	DSPcode
