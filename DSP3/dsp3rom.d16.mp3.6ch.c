#define	DSPcode		DSP3_MP3_6CH_code       //mp36CH

#include "dsp3rom.d16.mp3.6ch.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_MP3_6CH =
{
    (BYTE*)DSPcode,
    DSP3_MP3_6CH_IM,
    DSP3_MP3_6CH_DM,
    DSP3_MP3_6CH_PM,
};

#undef	DSPcode
