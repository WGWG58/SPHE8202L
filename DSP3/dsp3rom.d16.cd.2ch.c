#define	DSPcode		DSP3_CD_2CH_code

#include "dsp3rom.d16.cd.2ch.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_CD_2CH =
{
    (BYTE*)DSPcode,
    DSP3_CD_2CH_IM,
    DSP3_CD_2CH_DM,
    DSP3_CD_2CH_PM,
};

#undef	DSPcode
