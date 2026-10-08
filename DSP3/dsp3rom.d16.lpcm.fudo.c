#define	DSPcode		DSP3_LPCM_FUDO_code

#include "dsp3rom.d16.lpcm.fudo.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_LPCM_FUDO =
{
    (BYTE*)DSPcode,
    DSP3_LPCM_FUDO_IM,
    DSP3_LPCM_FUDO_DM,
    DSP3_LPCM_FUDO_PM,
};

#undef	DSPcode
