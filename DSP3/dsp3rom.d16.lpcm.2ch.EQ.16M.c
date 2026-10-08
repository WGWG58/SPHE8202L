#define	DSPcode		DSP3_LPCM_2CH_EQ_16M_code

#include "dsp3rom.d16.lpcm.2ch.EQ.16M.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_LPCM_2CH_EQ_16M =
{
    (BYTE*)DSPcode,
    DSP3_LPCM_2CH_EQ_16M_IM,
    DSP3_LPCM_2CH_EQ_16M_DM,
    DSP3_LPCM_2CH_EQ_16M_PM,
};

#undef	DSPcode
