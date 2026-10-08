#define	DSPcode		DSP3_CD_MP3_ENCODER_code
#include "global.h"

#ifdef INCLUDE_MP3_ENCODER
#include "dsp3rom.d16.cd.mp3.encoder.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_CD_MP3_ENCODER =
{
    (BYTE*)DSPcode,
    DSP3_CD_MP3_ENCODER_IM,
    DSP3_CD_MP3_ENCODER_DM,
    DSP3_CD_MP3_ENCODER_PM,
};
#endif

#undef	DSPcode

