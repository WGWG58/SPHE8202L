#define	DSPcode		DSP3_SPDIFINCD_8200_code

#include "dsp3rom.d16.cd.spi.8200.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_SPDIFINCD_8200 =
{
    (BYTE*)DSPcode,
    DSP3_SPDIFINCD_8200_IM,
    DSP3_SPDIFINCD_8200_DM,
    DSP3_SPDIFINCD_8200_PM,
};

#undef	DSPcode
