#ifndef _DSP3_CODEC_EXTERN_PARAM_H_
#define _DSP3_CODEC_EXTERN_PARAM_H_

#include "user_init.h"
#include "types.h"
#include "memmap_dsp3.h"

#define DSP3_LIBRARY_VERSION        "001"

typedef struct
{
    BYTE*       pDSPcode            __attribute__ ((packed));
    UINT16      uiDSPIM             __attribute__ ((packed));
    UINT16      uiDSPDM             __attribute__ ((packed));
    UINT16      uiDSPPM             __attribute__ ((packed));
} DSP3_CODEC_INFO;

// **************************************************************************************** //
// * AC3 Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.ac3.5.1ch.16M
extern const DSP3_CODEC_INFO    g_stDSP3Info_AC3_5_1CH_16M;

// dsp3rom.d16.ac3.raw.analog.2ch
extern const DSP3_CODEC_INFO    g_stDSP3Info_AC3_RAW_ANALOG_2CH;

// dsp3rom.d16.ac3.2ch
extern const DSP3_CODEC_INFO    g_stDSP3Info_AC3_2CH;

// dsp3rom.d16.945.ac3
extern const DSP3_CODEC_INFO    g_stDSP3Info_945_AC3;

// dsp3rom.d16.ac3
extern const DSP3_CODEC_INFO    g_stDSP3Info_AC3;

// **************************************************************************************** //
// * CD Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.cd.2ch
extern const DSP3_CODEC_INFO    g_stDSP3Info_CD_2CH;

// dsp3rom.d16.cd
extern const DSP3_CODEC_INFO    g_stDSP3Info_CD;

// dsp3rom.d16.cd.mp3.encoder
extern const DSP3_CODEC_INFO    g_stDSP3Info_CD_MP3_ENCODER;
// **************************************************************************************** //
// * LPCM Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.lpcm.2ch.eq.16M
extern const DSP3_CODEC_INFO    g_stDSP3Info_LPCM_2CH_EQ_16M;

// dsp3rom.d16.lpcm.2ch
extern const DSP3_CODEC_INFO    g_stDSP3Info_LPCM_2CH;

// dsp3rom.d16.lpcm.fudo
extern const DSP3_CODEC_INFO    g_stDSP3Info_LPCM_FUDO;

// dsp3rom.d16.lpcm
extern const DSP3_CODEC_INFO    g_stDSP3Info_LPCM;

// **************************************************************************************** //
// * DTS Codec Setup
// **************************************************************************************** //

// dsp3rom.d16_dts.dts
extern const DSP3_CODEC_INFO    g_stDSP3Info_DTS_DTS;

// dsp3rom.d16.dts.5.1ch.16M
extern const DSP3_CODEC_INFO    g_stDSP3Info_DTS_5_1CH_16M;

// dsp3rom.d16.945.dts
extern const DSP3_CODEC_INFO    g_stDSP3Info_945_DTS;

// dsp3rom.d16.dts.8202
extern const DSP3_CODEC_INFO    g_stDSP3Info_DTS_8202;

// dsp3rom.d16.dts.8200
extern const DSP3_CODEC_INFO    g_stDSP3Info_DTS_8200;

// **************************************************************************************** //
// * NES Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.nes.2ch
extern const DSP3_CODEC_INFO    g_stDSP3Info_NES_2CH;

// dsp3rom.d16.nes
extern const DSP3_CODEC_INFO    g_stDSP3Info_NES;

// **************************************************************************************** //
// * SPDIF Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.spdif.dts
extern const DSP3_CODEC_INFO    g_stDSP3Info_SPDIF_ONLY_DTS;

// dsp3rom.d16.spdif.2ch
extern const DSP3_CODEC_INFO    g_stDSP3Info_SPDIF_2CH;

/*
// dsp3rom.d16.spdif
extern const DSP3_CODEC_INFO    g_stDSP3Info_SPDIF;
*/
// **************************************************************************************** //
// * DTSCD Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.raw.dtscd
extern const DSP3_CODEC_INFO    g_stDSP3Info_RAW_DTSCD;

// dsp3rom.d16.108.dtscd 
extern const DSP3_CODEC_INFO    g_stDSP3Info_108_DTSCD;

// dsp3rom.d16.dtscd
extern const DSP3_CODEC_INFO    g_stDSP3Info_DTSCD;

// **************************************************************************************** //
// * WMA Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.wma.2ch
extern const DSP3_CODEC_INFO    g_stDSP3Info_WMA_2CH;

// dsp3rom.d16.wma
extern const DSP3_CODEC_INFO    g_stDSP3Info_WMA;

// **************************************************************************************** //
// * PPCM Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.ppcm
extern const DSP3_CODEC_INFO    g_stDSP3Info_PPCM;

// **************************************************************************************** //
// * SPG Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.spg
extern const DSP3_CODEC_INFO    g_stDSP3Info_SPG;

// **************************************************************************************** //
// * MP3 Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.mp3.2ch.EQ.16M
extern const DSP3_CODEC_INFO    g_stDSP3Info_MP3_2CH_EQ_16M;

// dsp3rom.d16.mp3.2ch
extern const DSP3_CODEC_INFO    g_stDSP3Info_MP3_2CH;

// dsp3rom.d16.mp3.mix
extern const DSP3_CODEC_INFO    g_stDSP3Info_MP3_MIX;

// dsp3rom.d16.mp3.jpg
extern const DSP3_CODEC_INFO    g_stDSP3Info_MP3_JPG;

// dsp3rom.d16.mp3
extern const DSP3_CODEC_INFO    g_stDSP3Info_MP3;

// dsp3rom.d16.mp3.6ch
extern const DSP3_CODEC_INFO    g_stDSP3Info_MP3_6CH;
// **************************************************************************************** //
// * AAC Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.aac
extern const DSP3_CODEC_INFO    g_stDSP3Info_AAC;

extern  const   unsigned char   DSPAACDMTab[];
extern  const   unsigned        DSPAACDMlen;

// **************************************************************************************** //
// * HDCD Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.hdcd
extern const DSP3_CODEC_INFO    g_stDSP3Info_HDCD;

// **************************************************************************************** //
// * MIDI Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.midi
extern const DSP3_CODEC_INFO    g_stDSP3Info_MIDI;

// **************************************************************************************** //
// * SPI Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.cd.spi.8202
extern const DSP3_CODEC_INFO    g_stDSP3Info_SPDIFINCD_8202;

// dsp3rom.d16.ac3.spi.8202
extern const DSP3_CODEC_INFO    g_stDSP3Info_SPDIFINAC3_8202;

// dsp3rom.d16.dts.spi.8202
extern const DSP3_CODEC_INFO    g_stDSP3Info_SPDIFINDTS_8202;

// dsp3rom.d16.cd.spi.8200
extern const DSP3_CODEC_INFO    g_stDSP3Info_SPDIFINCD_8200;

// dsp3rom.d16.ac3.spi.8200
extern const DSP3_CODEC_INFO    g_stDSP3Info_SPDIFINAC3_8200;

// dsp3rom.d16.dts.spi.8200
extern const DSP3_CODEC_INFO    g_stDSP3Info_SPDIFINDTS_8200;

// **************************************************************************************** //
// * TUNER Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.tuner
extern const DSP3_CODEC_INFO    g_stDSP3Info_TUNER;

// **************************************************************************************** //
// * NOISE Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.noise
extern const DSP3_CODEC_INFO    g_stDSP3Info_NOISE;

// dsp3rom.d16.noise.8200
extern const DSP3_CODEC_INFO    g_stDSP3Info_NOISE_8200;

// **************************************************************************************** //
// * OGG Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.ogg
extern const DSP3_CODEC_INFO    g_stDSP3Info_OGG;


// **************************************************************************************** //
// * OTHER Codec Setup
// **************************************************************************************** //

extern  const   unsigned char   DSPMP3DMTab[];
extern  const   unsigned        DSPMP3DMlen;

extern  const   unsigned char   DSPMP3PMTab[];
extern  const   unsigned        DSPMP3PMlen;

// MP3 encoder DM table 
extern  const   unsigned char   DSPMP3EDMTab[];	
extern  const   unsigned        DSPMP3EDMlen;

// OGG DM table
extern  const   unsigned char   DSPOGGDMTab[];	
extern  const   unsigned        DSPOGGDMlen;

#endif

