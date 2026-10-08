#define	DSPcode		DSP3_SPDIFINAC3_8202_code

#include "dsp3rom.d16.ac3.spi.8202.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_SPDIFINAC3_8202 =
{
    (BYTE*)DSPcode,
    DSP3_SPDIFINAC3_8202_IM,
    DSP3_SPDIFINAC3_8202_DM,
    DSP3_SPDIFINAC3_8202_PM,
};

#undef	DSPcode
