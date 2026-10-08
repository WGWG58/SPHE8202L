#define	DSPcode		DSP3_SPDIF_2CH_code

#include "dsp3rom.d16.spdif.2ch.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_SPDIF_2CH =
{
    (BYTE*)DSPcode,
    DSP3_SPDIF_2CH_IM,
    DSP3_SPDIF_2CH_DM,
    DSP3_SPDIF_2CH_PM,
};

#undef	DSPcode
