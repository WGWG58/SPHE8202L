#define	DSPcode		DSP3_MIDI_code

#include "dsp3rom.d16.midi.inc"
#include "dsp3_codec_extern_param.h"

const DSP3_CODEC_INFO     g_stDSP3Info_MIDI =
{
    (BYTE*)DSPcode,
    DSP3_MIDI_IM,
    DSP3_MIDI_DM,
    DSP3_MIDI_PM,
};

#undef	DSPcode
