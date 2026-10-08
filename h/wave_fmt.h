#ifndef __WAVE_FMT_H
#define __WAVE_FMT_H

#include "types.h"

// wFormatTag definitions in mmreg.h
#define	WAVE_FORMAT_UNKNOWN			0x0000
#define	WAVE_FORMAT_PCM				0x0001
#define	WAVE_FORMAT_ADPCM			0x0002
#define	WAVE_FORMAT_IEEE_FLOAT		0x0003
#define	WAVE_FORMAT_G723_ADPCM		0x0014
#define	WAVE_FORMAT_G721_ADPCM		0x0040
#define	WAVE_FORMAT_G728_CELP		0x0041
#define WAVE_FORMAT_G726_ADPCM		0x0064
#define	WAVE_FORMAT_DOLBY_AC2		0x0030
#define	WAVE_FORMAT_DOLBY_AC3		0x2000
#define	WAVE_FORMAT_DOLBY_DTS		0x2001
#define	WAVE_FORMAT_MPEG			0x0050
#define	WAVE_FORMAT_MPEGLAYER3		0x0055
#define	WAVE_FORMAT_IMA_ADPCM		0x0011//add by Roger 06-04-18 for support ASF IMA ADPCM

#define WAVE_FORMAT_WMA_OLD			0x0160		// WMA version type 1, not supported any more ->ycchou
#define WAVE_FORMAT_WMA_STEREO		0x0161		// could be supported, version 7, 8, 9
#define WAVE_FORMAT_WMA_PRO			0x0162
#define WAVE_FORMAT_WMA_LOSSLESS	0x0163
#define WAVE_FORMAT_WMA_VOICE		0x000A

#define	WAVE_FORMAT_NEC_AAC			0x00B0		// NEC AAC
#define	WAVE_FORMAT_MPEG2AAC		0x0180		// MP2 AAC
#define	WAVE_FORMAT_DIVIO_AAC		0x4143		// DIVIO AAC
#define	WAVE_FORMAT_AAC				0xa106		// MP4 AAC

// proprietary wma header
typedef	struct _wmaheader
{
	UINT16	wFormatTag;
	UINT32	dwSampRate;
	UINT32	dwBytePerSec;
	UINT16	wBlockAlign;
	UINT16	wReserve1;		// nChannels+nBitsPerSample
	UINT32	dwSampPerBlk;
	UINT16	wEncOption;
	UINT16	wTag;
} WMAHEADER;

typedef struct tWAVEFORMATEX
{
    UINT16	wFormatTag       __attribute__ ((packed));   /* format type */
    UINT16	nChannels        __attribute__ ((packed));   /* number of channels (i.e. mono, stereo...) */
    UINT32	nSamplesPerSec   __attribute__ ((packed));   /* sample rate */
    UINT32	nAvgBytesPerSec  __attribute__ ((packed));   /* for buffer estimation */
    UINT16	nBlockAlign      __attribute__ ((packed));   /* block size of data */
    UINT16	wBitsPerSample   __attribute__ ((packed));   /* Number of bits per sample of mono data */
    UINT16	cbSize           __attribute__ ((packed));   /* The count in bytes of the size of extra information (after cbSize) */
} WAVEFORMATEX;

typedef struct tWMAUDIO2WAVEFORMAT
{
    WAVEFORMATEX wfx                __attribute__ ((packed));
    UINT32      dwSamplesPerBlock   __attribute__ ((packed));
    UINT16      wEncodeOptions      __attribute__ ((packed));
    UINT32      dwSuperBlockAlign   __attribute__ ((packed));
}   WMAUDIO2WAVEFORMAT;

typedef struct mpeg1waveformat_tag {
    WAVEFORMATEX    wfx				__attribute__ ((packed));
    UINT16            fwHeadLayer		__attribute__ ((packed));
    UINT32           dwHeadBitrate	__attribute__ ((packed));
    UINT16            fwHeadMode		__attribute__ ((packed));
    UINT16            fwHeadModeExt	__attribute__ ((packed));
    UINT16            wHeadEmphasis	__attribute__ ((packed));
    UINT16            fwHeadFlags		__attribute__ ((packed));
    UINT32           dwPTSLow		__attribute__ ((packed));
    UINT32           dwPTSHigh		__attribute__ ((packed));
} MPEG1WAVEFORMAT;

typedef struct mpeglayer3waveformat_tag {
  WAVEFORMATEX  wfx					__attribute__ ((packed));
  UINT16          wID					__attribute__ ((packed));
  UINT32         fdwFlags			__attribute__ ((packed));
  UINT16          nBlockSize			__attribute__ ((packed));
  UINT16          nFramesPerBlock		__attribute__ ((packed));
  UINT16          nCodecDelay			__attribute__ ((packed));
} MPEGLAYER3WAVEFORMAT;

typedef struct tWAVFORMATMACRO
{
    WAVEFORMATEX    wfx             __attribute__ ((packed));
    UINT8           reserve[30]     __attribute__ ((packed));
}   WAVFORMATMACRO;

#endif      // __WAVE_FMT_H

