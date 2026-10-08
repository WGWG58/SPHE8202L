#define	DSPcode		DSP3_MP3_JPG_code

#include "dsp3rom.d16.mp3.jpg.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_MP3_JPG =
{
    (BYTE*)DSPcode,
    DSP3_MP3_JPG_IM,
    DSP3_MP3_JPG_DM,
    DSP3_MP3_JPG_PM,
};

#undef	DSPcode
