#define	DSPcode		DSP3_LPCM_code

#include "dsp3rom.d16.lpcm.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_LPCM =
{
    (BYTE*)DSPcode,
    DSP3_LPCM_IM,
    DSP3_LPCM_DM,
    DSP3_LPCM_PM,
};

#undef	DSPcode
