#define	DSPcode		DSP3_CD_code

#include "dsp3rom.d16.cd.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_CD =
{
    (BYTE*)DSPcode,
    DSP3_CD_IM,
    DSP3_CD_DM,
    DSP3_CD_PM,
};

#undef	DSPcode
