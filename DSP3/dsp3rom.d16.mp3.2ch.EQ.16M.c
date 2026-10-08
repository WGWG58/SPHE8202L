#define	DSPcode		DSP3_MP3_2CH_EQ_16M_code

#include "dsp3rom.d16.mp3.2ch.EQ.16M.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_MP3_2CH_EQ_16M =
{
    (BYTE*)DSPcode,
    DSP3_MP3_2CH_EQ_16M_IM,
    DSP3_MP3_2CH_EQ_16M_DM,
    DSP3_MP3_2CH_EQ_16M_PM,
};

#undef	DSPcode
