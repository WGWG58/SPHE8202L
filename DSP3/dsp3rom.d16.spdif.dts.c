#define	DSPcode		DSP3_SPDIF_ONLY_DTS_code

#include "dsp3rom.d16.spdif.dts.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_SPDIF_ONLY_DTS =
{
    (BYTE*)DSPcode,
    DSP3_SPDIF_ONLY_DTS_IM,
    DSP3_SPDIF_ONLY_DTS_DM,
    DSP3_SPDIF_ONLY_DTS_PM,
};

#undef	DSPcode
