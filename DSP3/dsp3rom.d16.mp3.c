#define	DSPcode		DSP3_MP3_code

#include "dsp3rom.d16.mp3.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_MP3 =
{
    (BYTE*)DSPcode,
    DSP3_MP3_IM,
    DSP3_MP3_DM,
    DSP3_MP3_PM,
};

#undef	DSPcode
