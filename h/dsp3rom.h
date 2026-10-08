#ifndef __DSP3ROM_H
#define __DSP3ROM_H

#include "user_init.h"
#include "dsp3_codec_extern_param.h"

extern  const   short           DTSrom[];

/*ONLY_USE_MP3_DSP:linrc only use in making romA.bin for BootLoad*/
#if defined(SP1000_NO_DVD)||defined(ONLY_USE_MP3_DSP)

#ifdef ONLY_USE_MP3_DSP
#define     DSP3Info_MP3        g_stDSP3Info_MP3_2CH
#else
#define     DSP3Info_MP3        g_stDSP3Info_MP3
#endif

//#define     DSP3Info_AC3        NULL
#define     DSP3Info_AC3        g_stDSP3Info_MP3

#define     DSP3Info_CD         NULL

//#define     DSP3Info_LPCM       NULL
#define     DSP3Info_LPCM       g_stDSP3Info_MP3

#define     DSP3Info_DTS        NULL
#define     DSP3Info_NES        NULL

//#define     DSP3Info_SPDIF      NULL
#define     DSP3Info_SPDIF      g_stDSP3Info_SPDIF_2CH

#define     DSP3Info_DTSCD      NULL

#ifdef SUPPORT_WMA
#define     DSP3Info_WMA        g_stDSP3Info_WMA
#else
#define     DSP3Info_WMA        NULL
#endif

#define     DSP3Info_PPCM       NULL
#define     DSP3Info_AAC        NULL
#define     DSP3Info_HDCD       NULL
#define     DSP3Info_MIDI       NULL
#define     DSP3Info_SPDIFINCD  NULL
#define     DSP3Info_SPDIFINAC3 NULL
#define     DSP3Info_SPDIFINDTS NULL
#define     DSP3Info_TUNER      NULL
#define     DSP3Info_NOISE      NULL
#define     DSP3Info_NOISE_8200      NULL
#else //#ifdef SP1000_NO_DVD

// **************************************************************************************** //
// * AC3 Codec Setup
// **************************************************************************************** //
#ifdef SDRAM_16Mb_Mode
    
    #if defined(SUPPORT_SDRAM16M_AC3_5_1CH_OUTPUT)
// dsp3rom.d16.ac3.5.1ch.16M
#define     DSP3Info_AC3        g_stDSP3Info_AC3_5_1CH_16M

    #elif defined(RAW_HAVE_ANALOG_OUTPUT)
// dsp3rom.d16.ac3.raw.analog.2ch
#define     DSP3Info_AC3        g_stDSP3Info_AC3_RAW_ANALOG_2CH

    #else
// dsp3rom.d16.ac3.2ch
#define     DSP3Info_AC3        g_stDSP3Info_AC3_2CH

    #endif

#else

    #ifdef F94_5
// dsp3rom.d16.945.ac3
#define     DSP3Info_AC3        g_stDSP3Info_945_AC3

    #else
// dsp3rom.d16.ac3
#define     DSP3Info_AC3        g_stDSP3Info_AC3

    #endif

#endif

// **************************************************************************************** //
// * CD Codec Setup
// **************************************************************************************** //
#ifdef SDRAM_16Mb_Mode

// dsp3rom.d16.cd.2ch
#define     DSP3Info_CD         g_stDSP3Info_CD_2CH

#else

// dsp3rom.d16.cd
#define     DSP3Info_CD         g_stDSP3Info_CD

#endif

#ifdef INCLUDE_MP3_ENCODER
	// dsp3rom.d16.cd.mp3.encoder
	#define     DSP3Info_CD_MP3_ENCODER         g_stDSP3Info_CD_MP3_ENCODER
#endif

// **************************************************************************************** //
// * LPCM Codec Setup
// **************************************************************************************** //
#ifdef SDRAM_16Mb_Mode

    #ifdef SUPPORT_EQ_SDRAM_16Mb
// dsp3rom.d16.lpcm.2ch.eq.16M
#define     DSP3Info_LPCM       g_stDSP3Info_LPCM_2CH_EQ_16M

    #else
// dsp3rom.d16.lpcm.2ch
#define     DSP3Info_LPCM       g_stDSP3Info_LPCM_2CH

    #endif
    
#elif defined(SUPPORT_REP_READ)
// dsp3rom.d16.lpcm.fudo
#define     DSP3Info_LPCM       g_stDSP3Info_LPCM_FUDO

#else
// dsp3rom.d16.lpcm
#define     DSP3Info_LPCM       g_stDSP3Info_LPCM

#endif

// **************************************************************************************** //
// * DTS Codec Setup
// **************************************************************************************** //
#ifdef NO_DTS_OUTPUT

    #ifdef FORCE_NO_DTS_OUTPUT
// dsp3rom.d16_dts.dts
#define     DSP3Info_DTS        g_stDSP3Info_DTS_DTS

    #endif
    
#else

    #ifdef SDRAM_16Mb_Mode

        #ifdef SPHE8202
// dsp3rom.d16.dts.5.1ch.16M
#define     DSP3Info_DTS        g_stDSP3Info_DTS_5_1CH_16M

        #endif
        
    #else
    
        #ifdef F94_5
// dsp3rom.d16.945.dts
#define     DSP3Info_DTS        g_stDSP3Info_945_DTS

        #else

            #ifdef SPHE8202
// dsp3rom.d16.dts.8202
#define     DSP3Info_DTS        g_stDSP3Info_DTS_8202

            #else
// dsp3rom.d16.dts.8200
#define     DSP3Info_DTS        g_stDSP3Info_DTS_8200

            #endif
        
        #endif
        
    #endif
    
#endif

// **************************************************************************************** //
// * NES Codec Setup
// **************************************************************************************** //
#ifdef SUPPORT_NESGAME

    #ifdef SDRAM_16Mb_Mode
// dsp3rom.d16.nes.2ch
#define     DSP3Info_NES        g_stDSP3Info_NES_2CH

    #else
// dsp3rom.d16.nes
#define     DSP3Info_NES        g_stDSP3Info_NES

    #endif
    
#endif

// **************************************************************************************** //
// * SPDIF Codec Setup
// **************************************************************************************** //

//ycwen 2006/01/02 Only DTS needs a dedicated  spdif output dsp code. 
#define     DSP3Info_SPDIF      g_stDSP3Info_SPDIF_ONLY_DTS

/*
#if defined( SDRAM_16Mb_Mode ) && ( !defined( SUPPORT_SDRAM16M_DTS_5_1CH_OUTPUT )&&(defined( SUPPORT_SDRAM16M_AC3_5_1CH_OUTPUT ) || defined( RAW_HAVE_ANALOG_OUTPUT )) )
// dsp3rom.d16.spdif.dts
    #define     DSP3Info_SPDIF      g_stDSP3Info_SPDIF_ONLY_DTS
#else
// dsp3rom.d16.spdif.2ch
    #define     DSP3Info_SPDIF      g_stDSP3Info_SPDIF_2CH
#endif
*/

// **************************************************************************************** //
// * DTSCD Codec Setup
// **************************************************************************************** //

#if defined(DTS_CD_OUT_RAW_A)       // 2004/11/11 yltseng
// dsp3rom.d16.raw.dtscd
#define     DSP3Info_DTSCD      g_stDSP3Info_RAW_DTSCD

#elif defined(F108)||defined(F94_5)
// dsp3rom.d16.108.dtscd 
#define     DSP3Info_DTSCD      g_stDSP3Info_108_DTSCD

#else
// dsp3rom.d16.dtscd
#define     DSP3Info_DTSCD      g_stDSP3Info_DTSCD

#endif
    
// **************************************************************************************** //
// * WMA Codec Setup
// **************************************************************************************** //

#ifdef SDRAM_16Mb_Mode
// dsp3rom.d16.wma.2ch
#define     DSP3Info_WMA        g_stDSP3Info_WMA_2CH

#else
// dsp3rom.d16.wma
#define     DSP3Info_WMA        g_stDSP3Info_WMA

#endif
    
// **************************************************************************************** //
// * PPCM Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.ppcm
#define     DSP3Info_PPCM       g_stDSP3Info_PPCM

// **************************************************************************************** //
// * SPG Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.spg
#define     DSP3Info_SPG        g_stDSP3Info_SPG
    
// **************************************************************************************** //
// * MP3 Codec Setup
// **************************************************************************************** //
#ifdef SDRAM_16Mb_Mode
    #ifdef SUPPORT_EQ_SDRAM_16Mb
        // dsp3rom.d16.mp3.2ch.EQ.16M
        #define     DSP3Info_MP3        g_stDSP3Info_MP3_2CH_EQ_16M
    #else
        // dsp3rom.d16.mp3.2ch
        #define     DSP3Info_MP3        g_stDSP3Info_MP3_2CH
    #endif            
#else
    #if defined( MP3_JPEG_COWORK )
        // dsp3rom.d16.mp3.jpg
        #define     DSP3Info_MP3        g_stDSP3Info_MP3_JPG    
    #else
        // dsp3rom.d16.mp3
        #define     DSP3Info_MP3        g_stDSP3Info_MP3
    #endif    
#endif

#define     DSP3Info_MP3_6CH        g_stDSP3Info_MP3_6CH    

// dsp3rom.d16.mp3.mix
#define     DSP3Info_MP3_MIX        g_stDSP3Info_MP3_MIX


// **************************************************************************************** //
// * AAC Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.aac
#define     DSP3Info_AAC        g_stDSP3Info_AAC

// **************************************************************************************** //
// * HDCD Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.hdcd
#define     DSP3Info_HDCD       g_stDSP3Info_HDCD

// **************************************************************************************** //
// * MIDI Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.midi
#define     DSP3Info_MIDI       g_stDSP3Info_MIDI

// **************************************************************************************** //
// * SPI Codec Setup
// **************************************************************************************** //

#ifdef SPHE8202

// dsp3rom.d16.cd.spi.8202
#define     DSP3Info_SPDIFINCD          g_stDSP3Info_SPDIFINCD_8202

// dsp3rom.d16.ac3.spi.8202
#define     DSP3Info_SPDIFINAC3         g_stDSP3Info_SPDIFINAC3_8202

// dsp3rom.d16.dts.spi.8202
#define     DSP3Info_SPDIFINDTS         g_stDSP3Info_SPDIFINDTS_8202

#else

// dsp3rom.d16.cd.spi.8200
#define     DSP3Info_SPDIFINCD          g_stDSP3Info_SPDIFINCD_8200

// dsp3rom.d16.ac3.spi.8200
#define     DSP3Info_SPDIFINAC3         g_stDSP3Info_SPDIFINAC3_8200

// dsp3rom.d16.dts.spi.8200
#define     DSP3Info_SPDIFINDTS         g_stDSP3Info_SPDIFINDTS_8200

#endif

// **************************************************************************************** //
// * TUNER Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.tuner
#define     DSP3Info_TUNER      g_stDSP3Info_TUNER

// **************************************************************************************** //
// * NOISE Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.tuner
#define     DSP3Info_NOISE      g_stDSP3Info_NOISE

// dsp3rom.d16.noise.8200
#define     DSP3Info_NOISE_8200      g_stDSP3Info_NOISE_8200


// **************************************************************************************** //
// * OGG Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.ogg
#define     DSP3Info_OGG      g_stDSP3Info_OGG

#endif //#ifdef SP1000_NO_DVD

#endif/*__DSP3ROM_H*/

