#define	DSPcode		DSP3_MP3_MIX_code

#include "dsp3rom.d16.mp3.mix.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_MP3_MIX =
{
    (BYTE*)DSPcode,
    DSP3_MP3_MIX_IM,
    DSP3_MP3_MIX_DM,
    DSP3_MP3_MIX_PM,
};

#undef	DSPcode
