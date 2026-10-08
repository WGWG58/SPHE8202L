//
// FILE
// dsp3_tuner.c
//
#include "set.h"
#include "user_init.h"

#ifdef SUPPORT_TESTSPK

#define	DSPcode		DSP3code_noise
#define	DSPcodelen	DSP3codelen_noise

#include "dsp3noise.inc"

const	unsigned	DSPcodelen = sizeof(DSPcode);

#undef	DSPcode
#undef	DSPcodelen

#endif

