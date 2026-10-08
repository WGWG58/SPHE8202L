#ifndef __AUDDEF_H__
#define __AUDDEF_H__

/***********************************************************************
 *  Define Session
 ***********************************************************************/
#define STATUS_OFF  0
#define STATUS_ON   1
#define STATUS_AUTO 2

/*======================================*///add by Steven 2006/4/10 // 
/*=====    MIC Support Setting related     =====*/
/*======================================*/
#define MIC_NOT_SUPPORT 0
#define MIC_SUPPORT     1


/*======================================*///add by Steven 2006/5/17 // 
/*=====     Pro Logic II Initial Setting    =====*/
/*======================================*/

#define PROLOGICII_MOVIE_DSP_INIT 0x137330
#define PROLOGICII_MUSIC_DSP_INIT 0x127330
#define PROLOGICII_OFF_DSP_INIT 0x037330



/******* Frequency definition *******/
#define FS_16K  0x1000
#define FS_22K  0x2000
#define FS_24K  0x4000
#define FS_32K  0x0001
#define FS_44K  0x0002
#define FS_48K  0x0004
#define FS_64K  0x0010
#define FS_88K  0x0020
#define FS_96K  0x0040
#define FS_128K 0x0100
#define FS_176K 0x0200
#define FS_192K 0x0400
#define FS_MAX  0x8000

#define FS_DEFAULT  FS_48K

/******* Output Mode definition *******/
#define OUT_STEREO              0x01
#define OUT_LL                  0x02
#define OUT_RR                  0x03
#define OUT_LL_AutoADDetect     0x04
#define OUT_RR_AutoADDetect     0x05
#define OUT_51Channel           0x06
#define OUT_51DownmixL0R0       0x07
#define OUT_51DownmixLtRt       0x08
#define OUT_51DownmixLsRs       0x09
#define OUT_RFModeK3            0x10
#define OUT_LineModeK2          0x20
#define OUT_NoVocal             0x30
#define OUT_LeftVocal           0x40
#define OUT_RightVocal          0x50
#define OUT_BothVocal           0x60
#define OUT_CustomModeA_AnalogDialnormK0    0x70
#define OUT_CustomModeB_DigitalDialnormK1   0x80


#ifndef FRNT_SPK
    #define FRNT_SPK 1
#endif
#ifndef CNTR_SPK
    #define CNTR_SPK 1
#endif
#ifndef SRND_SPK
    #define SRND_SPK 1
#endif
#ifndef SBWF_SPK
    #define SBWF_SPK 1
#endif

/******* Wave format related definition *******/
#define	LPCM_MODE_AOB			0x00
#define	LPCM_MODE_VOB			0x20
#define	LPCM_MODE_WAVE			0x40
#define	LPCM_MODE_CDDA			0x60
#define	LPCM_MODE_ADPCM			0x80//add by Roger 06-04-14 for support ASF IMA ADPCM
#define	LPCM_MODE_MASK			0xC0


/******* Speaker Config definition *******/
#define SPEAKER_LARGE           0
#define SPEAKER_SMALL           1
#define SPEAKER_OFF             2

/******* For Debugging purpose *******/
#ifndef DVDRELEASE
//#define AUDDRV_DBG    // audio driver layer debug
//#define AUDKRNL_DBG   // audio kernel layer debug
#endif
#define AUDDRV

#ifdef IC_8202D//CUSTOMERS_8202D_DVD nono modify.5-3-25 14:01
 // #define MESSAGE_QUEUE // 20050113 Oliver : introducing MQ mechanism into audio driver
#endif

#endif //#ifndef __AUDDEF_H__
