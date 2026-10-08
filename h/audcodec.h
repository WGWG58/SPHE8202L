#ifndef __AUD_CODEC_H
#define __AUD_CODEC_H

#include "user_init.h"

#define CODING_MODE_AC3                 0
#define CODING_MODE_PPCM                1
#define CODING_MODE_MP1                 2   //  MC
#define CODING_MODE_MP2                 3   //  MC
#define CODING_MODE_LPCM                4
#define CODING_MODE_JPG                 5
#define CODING_MODE_DTS                 6
#define CODING_MODE_SDDS                7
#define CODING_MODE_MP3                 8
#define CODING_MODE_PCM                 9
#define CODING_MODE_MIDI                10
#define CODING_MODE_NES                 11
#define CODING_MODE_SPDIF               12
#define CODING_MODE_DTSCD               13
#define CODING_MODE_WMA                 14
#define CODING_MODE_SPDIFINCD           15     
#define CODING_MODE_SPDIFINAC3          16     
#define CODING_MODE_SPDIFINDTS          17    
#define CODING_MODE_TUNER               18
#define CODING_MODE_NOISE               19
#define CODING_MODE_AAC                 20
#define CODING_MODE_CD_MP3_ENCODER		21	//for MP3_ENCODER/CD_RIPPING
#define CODING_MODE_OGG                 22 
#define CODING_MODE_MP3_6CH             23 
#define CODING_MODE_MP3_MIX             24

#define AUDIF_CODING_MODE_AC3           (1<<CODING_MODE_AC3)
#define AUDIF_CODING_MODE_PPCM          (1<<CODING_MODE_PPCM)
#define AUDIF_CODING_MODE_MP1           (1<<CODING_MODE_MP1)    //  MC
#define AUDIF_CODING_MODE_MP2           (1<<CODING_MODE_MP2)    //  MC
#define AUDIF_CODING_MODE_LPCM          (1<<CODING_MODE_LPCM)
#define AUDIF_CODING_MODE_DTS           (1<<CODING_MODE_DTS)
#define AUDIF_CODING_MODE_SDDS          (1<<CODING_MODE_SDDS)
#define AUDIF_CODING_MODE_MP3           (1<<CODING_MODE_MP3)
#define AUDIF_CODING_MODE_PCM           (1<<CODING_MODE_PCM)    //0x200
#define AUDIF_CODING_MODE_JPG           (1<<CODING_MODE_JPG)
#define AUDIF_CODING_MODE_MIDI          (1<<CODING_MODE_MIDI)
#define AUDIF_CODING_MODE_NES           (1<<CODING_MODE_NES)
#define AUDIF_CODING_MODE_SPDIF         (1<<CODING_MODE_SPDIF)  //0x1000
#define AUDIF_CODING_MODE_DTSCD         (1<<CODING_MODE_DTSCD)  //0x2000
#define AUDIF_CODING_MODE_WMA           (1<<CODING_MODE_WMA)    //0x4000
#define AUDIF_CODING_MODE_SPDIFINCD     (1<<CODING_MODE_SPDIFINCD)   
#define AUDIF_CODING_MODE_SPDIFINAC3    (1<<CODING_MODE_SPDIFINAC3) 
#define AUDIF_CODING_MODE_SPDIFINDTS    (1<<CODING_MODE_SPDIFINDTS) 
#define AUDIF_CODING_MODE_TUNER         (1<<CODING_MODE_TUNER)
#define AUDIF_CODING_MODE_NOISE         (1<<CODING_MODE_NOISE)
#define AUDIF_CODING_MODE_AAC           (1<<CODING_MODE_AAC)
#define AUDIF_CODING_MODE_CD_MP3_ENCODER  (1<<CODING_MODE_CD_MP3_ENCODER)	//for MP3_ENCODER/CD_RIPPING
#define AUDIF_CODING_MODE_OGG           (1<<CODING_MODE_OGG)
#define AUDIF_CODING_MODE_MP3_MIX       (1<<CODING_MODE_MP3_MIX)

#define AUDIF_CODING_MODE_NOW                   (0xffff)

#define AUDIF_CODING_MODE_NONE          0

#ifdef SP1000_NO_DVD
#define AUDIF_CODING_MODE_DEFAULT       AUDIF_CODING_MODE_MP3
#else
#define AUDIF_CODING_MODE_DEFAULT       AUDIF_CODING_MODE_AC3
#endif

#define IS_AUDIF_CODING_MODE_AC3        (AUDIF_CODING_MODE_AC3 == coding_mode_now)
#define IS_AUDIF_CODING_MODE_PPCM       (AUDIF_CODING_MODE_PPCM == coding_mode_now)
#define IS_AUDIF_CODING_MODE_MP2        (AUDIF_CODING_MODE_MP2 == coding_mode_now)    //  MC
#define IS_AUDIF_CODING_MODE_LPCM       (AUDIF_CODING_MODE_LPCM == coding_mode_now)
#define IS_AUDIF_CODING_MODE_DTS        (AUDIF_CODING_MODE_DTS == coding_mode_now)
#define IS_AUDIF_CODING_MODE_SDDS       (ADUIF_CODING_MODE_SDDS == coding_mode_now)
#define IS_AUDIF_CODING_MODE_MP3        (AUDIF_CODING_MODE_MP3 == coding_mode_now)
#define IS_AUDIF_CODING_MODE_PCM        (AUDIF_CODING_MODE_PCM == coding_mode_now)    //0x200
#define IS_AUDIF_CODING_MODE_JPG        (AUDIF_CODING_MODE_JPG == coding_mode_now)
#define IS_AUDIF_CODING_MODE_MIDI       (AUDIF_CODING_MODE_MIDI == coding_mode_now)
#define IS_AUDIF_CODING_MODE_NES        (AUDIF_CODING_MODE_NES == coding_mode_now)
#define IS_AUDIF_CODING_MODE_SPDIF      (AUDIF_CODING_MODE_SPDIF == coding_mode_now)  //0x1000
#define IS_AUDIF_CODING_MODE_DTSCD      (AUDIF_CODING_MODE_DTSCD == coding_mode_now)  //0x2000
#define IS_AUDIF_CODING_MODE_WMA        (AUDIF_CODING_MODE_WMA == coding_mode_now)    //0x4000
#define IS_AUDIF_CODING_MODE_SPDIFINCD      (AUDIF_CODING_MODE_SPDIFINCD == coding_mode_now)
#define IS_AUDIF_CODING_MODE_SPDIFINAC3     (AUDIF_CODING_MODE_SPDIFINAC3 == coding_mode_now)
#define IS_AUDIF_CODING_MODE_SPDIFINDTS     (AUDIF_CODING_MODE_SPDIFINDTS == coding_mode_now)
#define IS_AUDIF_CODING_MODE_TUNER          (AUDIF_CODING_MODE_TUNER == coding_mode_now)
#define IS_AUDIF_CODING_MODE_NOISE          (AUDIF_CODING_MODE_NOISE == coding_mode_now) 
#define IS_AUDIF_CODING_MODE_CD_MP3_ENCODER          (AUDIF_CODING_MODE_CD_MP3_ENCODER == coding_mode_now) //for MP3_ENCODER/CD_RIPPING
#define IS_AUDIF_CODING_MODE_OGG          (AUDIF_CODING_MODE_OGG == coding_mode_now)
#define IS_AUDIF_CODING_MODE_MP3_MIX      (AUDIF_CODING_MODE_MP3_MIX == coding_mode_now)


//             DSP Decoder(Simulate)        DSP Decoder(SPDIF/BITSTREAM)    DSP Decoder(SPDIF/PCM)
//---------------------------------------------------------------------------------------------------------------
// CDDA        AUDIF_CODING_MODE_PCM        AUDIF_CODING_MODE_PCM(*)        AUDIF_CODING_MODE_PCM
// HDCD        AUDIF_CODING_MODE_PCM        AUDIF_CODING_MODE_PCM(*)        AUDIF_CODING_MODE_PCM
// DTSCD       AUDIF_CODING_MODE_DTSCD      AUDIF_CODING_MODE_PCM           AUDIF_CODING_MODE_DTSCD
// MP3         AUDIF_CODING_MODE_MP3        AUDIF_CODING_MODE_MP3(*)        AUDIF_CODING_MODE_MP3
// VCD         AUDIF_CODING_MODE_MP3        AUDIF_CODING_MODE_MP3(*)        AUDIF_CODING_MODE_MP3
// SVCD/CVD    AUDIF_CODING_MODE_MP3        AUDIF_CODING_MODE_MP3(*)        AUDIF_CODING_MODE_MP3
// DVD/AC3     AUDIF_CODING_MODE_AC3        AUDIF_CODING_MODE_SPDIF         AUDIF_CODING_MODE_AC3
// DVD/DTS     AUDIF_CODING_MODE_DTS        AUDIF_CODING_MODE_SPDIF         AUDIF_CODING_MODE_DTS
// DVD/MPx     AUDIF_CODING_MODE_MP3        AUDIF_CODING_MODE_MP3(*)        AUDIF_CODING_MODE_MP3
// DVD/LPCM    AUDIF_CODING_MODE_LPCM       AUDIF_CODING_MODE_LPCM(*)       AUDIF_CODING_MODE_LPCM
// JPEG        AUDIF_CODING_MODE_JPG        AUDIF_CODING_MODE_JPG           AUDIF_CODING_MODE_JPG
// NES         AUDIF_CODING_MODE_NES        AUDIF_CODING_MODE_NES           AUDIF_CODING_MODE_NES
//
// ps : (*)fake setting(use SPDIF/PCM)

#endif  //__AUD_CODEC_H
