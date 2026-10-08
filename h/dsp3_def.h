#ifndef __DSP3_DEF_H
#define __DSP3_DEF_H

#include "types.h"
#include "gb_knl.h"

#define AudioGetDumpPointer()	(regs0->dsp24_port[2])
#define AudioSetDumpPointer(x)	(regs0->dsp24_port[2] = (x))
#define AudioGetBarrier()		(regs0->dsp24_port[3])
#define AudioSetBarrier(x)		(regs0->dsp24_port[3] = (x))
#define AudioGetEndPoint()		(regs0->dsp24_port[4])
#define AudioSetEndPoint(x)		(regs0->dsp24_port[4] = (x))
#define AudioGetBytePtr()		(abv_ptr_b)
#define AudioSetBytePtr(x)		(abv_ptr_b = (x))


#define DTSSetRomLocation(x)    \
    do {                        \
      regs0->rom_h = (x>>16)&0x0ffff;  \
      regs0->rom_l = x&0x0ffff;        \
    } while (0)



/***************************************************************
Steven 2006/10/04 replace x value of set_dsp3_pcm_value(x,y) and
   get_dsp3_pcm_value(x) by Audio Runtime R/W Command define
****************************************************************/

//*******Audio Runtime R/W Command Protocal********* //
// ********************START************************* //

//*************DSP report status to RISC**************//
#define DSP_RUNTIME_EQ_SPECTRUM                 0
#define DSP_RUNTIME_AAC_BITRATE                 14
#define DSP_RUNTIME_MPEG_BITRATE                14
#define DSP_RUNTIME_AAC_SMPRATE_GET             15
#define DSP_RUNTIME_MPEG_SMPRATE                15
#define DSP_RUNTIME_INST_SCORE                  16
#define DSP_RUNTIME_FINAL_SCORE                 17
#define DSP_RUNTIME_MIC_ENERGY                  18
#define DSP_RUNTIME_AUD_CHN_SELECT              19
#define DSP_RUNTIME_MIDI_END_FLAG               21
#define DSP_RUNTIME_MPEG_LAYER_NUM              22
#define DSP_RUNTIME_CDDA_MIC_BUF_FULLRATIO      22
#define DSP_RUNTIME_ACTIVE_NOISE_CHN            22
#define DSP_RUNTIME_MIC_EQ_SPECTRUM             23
#define DSP_RUNTIME_CODEC_ID                    30
#define DSP_RUNTIME_CODEC_VER                   31
#define DSP_RUNTIME_HDCD_FLAG                   32



//************RISC set parameters to DSP*************//
#define DSP_RUNTIME_EQ_GAIN                     7 
//************WMA Parameters Area********************//
#define DSP_RUNTIME_WMA_FORMAT_TAG              64
#define DSP_RUNTIME_WMA_VER                     65
#define DSP_RUNTIME_WMA_SMPRATE                 66
#define DSP_RUNTIME_WMA_BITRATE                 67
#define DSP_RUNTIME_WMA_BLOCK_ALIGN             68
#define DSP_RUNTIME_WMA_SAMPLE_BITS             69
#define DSP_RUNTIME_WMA_CHN_NUM                 70
#define DSP_RUNTIME_WMA_BLOCK_SAMPLES           71
#define DSP_RUNTIME_WMA_ENCODE_OPT              72
#define DSP_RUNTIME_WMA_AUD_STREAM_ID           73
//*************LPCM Parameters Area******************//
#define DSP_RUNTIME_LPCM_CHN_NUM                64 
#define DSP_RUNTIME_LPCM_FORMAT                 65
#define DSP_RUNTIME_LPCM_GR1_QBITS              66
#define DSP_RUNTIME_LPCM_GR1_FS                 67
#define DSP_RUNTIME_LPCM_GR2_QBITS              68
#define DSP_RUNTIME_LPCM_GR2_FS                 69
#define DSP_RUNTIME_LPCM_GR2_SHIFT_BITS         70
#define DSP_RUNTIME_LPCM_PREEMPHASYS_FLAG       71
#define DSP_RUNTIME_LPCM_BLOCK_ALIGN            72
//**************AAC Parameters Area*****************//
#define DSP_RUNTIME_AAC_PROFILE                 64
#define DSP_RUNTIME_AAC_SMPRATE_SET             65
#define DSP_RUNTIME_AAC_CHN_NUM                 66
#define DSP_RUNTIME_AAC_FORMAT                  67

//*******Audio Runtime R/W Command Protocal********* //
// **********************END************************* //




//Audio Command Code
enum {
    FLOW=0,
    OUTMODE,
    VOLUME,
    KEY,
    ECHO,
    SURROUND,
    SUBWOOF,
    SPDIF,
    EQ,
    MIC,
    AD,
    SPKDELAY,
    FSPKGAIN,
    SSPKGAIN,
    PROLOGIC,
    FLSPKGAIN,  //don't change the sequence, FLSPKGAIN/FRSPKGAIN/SLSPKGAIN/SRSPKGAIN/CSPKGAIN/SWSPKGAIN
    FRSPKGAIN,
    SLSPKGAIN,
    SRSPKGAIN,
    CSPKGAIN,
    SWSPKGAIN,  //Jeff 20031028
    SCORING,
    AD_2,
#ifdef SUPPORT_REP_READ//Maoyong 2004.05.26
    RECORDMIC,	
#endif     
    BASSMANAGEMENT,
#ifdef SUPPORT_SOUND_EFFECT  
    SNDEFFECT, //sound effect shawn 2004.10.7
#endif	      
#ifdef MESSAGE_QUEUE
    LPCMPARAMETER,
    CMDACK,
    STATACK,
    DSPSTATE,
    DSPDOWNLOAD,
    SETAC3CONFIG,
    WRITE2PCM,
#endif       
};


#ifdef MESSAGE_QUEUE
//DSP status
enum {
DSPINITSTATE=-1,	
DSPSTOPSTATE=0,	
DSPPLAYSTATE=1,
DSPPAUSESTATE=2,		
};	
#endif


//Audio FLOW, SubCommand
enum {
    AUDIOPLAY=1,
    AUDIOCONTINUE=2,
    AUDIOSTOP=3,
    AUDIOPAUSE=4,
    AUDIOFLUSH=5,
    AUDIOFF2X=6,
    AUDIOFF4X=7,
    AUDIOFF8X=8,
    AUDIOFF20X=9,
    AUDIOFF2PLAY=0x0a,
    AUDIOFF16X=0x0b, // Robert 2003/12/24
    AUDIOFF32X=0x0c, // Robert 2003/12/24
    
    AUDIOFF5X=0x0d,//nono 4-2-10 20:25
    AUDIOFF10X=0x0e,//nono 4-2-10 20:25
    AUDIOFF30X=0x0f,//nono 4-2-10 20:25
    AUDIOFF60X=0x10,//nono 4-2-10 20:25
    
    AUDIOFF1_25X=0x11,
    AUDIOFF1_50X=0x12,
    AUDIOFF1_75X=0x13,
    AUDIOFF2_00X=0x14,
    AUDIOSF1_25X=0x15,
    AUDIOSF1_50X=0x16,
    AUDIOSF1_75X=0x17,
    AUDIOSF2_00X=0x18,
#ifdef MESSAGE_QUEUE    
    MP3TONORM=0x19,
#endif    
};

#endif

