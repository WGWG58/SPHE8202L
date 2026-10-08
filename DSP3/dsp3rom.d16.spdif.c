#define	DSPcode		DSP3_SPDIF_code

#include "dsp3rom.d16.spdif.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_SPDIF =
{
    (BYTE*)DSPcode,
    DSP3_SPDIF_IM,
    DSP3_SPDIF_DM,
    DSP3_SPDIF_PM,
};

#undef	DSPcode
