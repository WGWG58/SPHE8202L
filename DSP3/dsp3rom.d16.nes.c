#define	DSPcode		DSP3_NES_code

#include "dsp3rom.d16.nes.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_NES =
{
    (BYTE*)DSPcode,
    DSP3_NES_IM,
    DSP3_NES_DM,
    DSP3_NES_PM,
};

#undef	DSPcode
