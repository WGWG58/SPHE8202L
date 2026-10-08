#define	DSPcode		DSP3_945_DTS_code

#include "dsp3rom.d16.945.dts.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_945_DTS =
{
    (BYTE*)DSPcode,
    DSP3_945_DTS_IM,
    DSP3_945_DTS_DM,
    DSP3_945_DTS_PM,
};

#undef	DSPcode
