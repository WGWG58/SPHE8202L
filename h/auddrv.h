#ifndef __AUDDRV_H__
#define __AUDDRV_H__

#include "global.h"
#include "user_init.h"

#include "auddef.h"
#include "dsp3_def.h"
#include "dsp3_if.h"
#include "dsp3rom.h"
#include "audkernel.h"

#ifdef	MP3_JPEG_COWORK //ycwen 2005/1/21 : this header file is needed 
#include "fsNav.h"
#endif

/*======================================*/
/*=====    Wave format related     =====*/
/*======================================*/
#include "wave_fmt.h"
extern WAVFORMATMACRO   wfmt;
extern UINT32           aud_frequency;
extern UINT32           aud_frame_size;
extern UINT32      		lpcm_flag;
extern UINT32      		lpcm_frame_size;

/*======================================*/
/*=====     WMA format related     =====*/
/*======================================*/
#if defined(SUPPORT_WMA) || defined(SUPPORT_AUD_WMA)
extern WMAHEADER    wma_header;
extern BYTE	        wmabuf[8];
extern UINT32	    ploadlen;
extern BYTE	        wmambn;
#endif
extern BYTE	        apf;
extern UINT32	    pldcnt;

/*============================================================*/
#define	AUDIF_RampDown_DSP(x)			\
	do {								\
		regs0->aud_pcm_ramp_delta = 1;	\
		regs0->aud_pcm_ramp_cfg = 1;	\
	} while (0)

#define	AUDIF_RampUp_DSP(x)				\
	do {								\
		regs0->aud_pcm_ramp_delta = 1;	\
		regs0->aud_pcm_ramp_cfg = 2;	\
	} while (0)
        
//change AUDIF_RampWait_DSP method equals to to delay_srv_10ms(3) to prevent dead loop
#define	AUDIF_RampWait_DSP() delay_srv_10ms(5)
/*
#define	dsp3_ramp_wait()					\
            do {                                    \
                polling();                          \
            } while (regs0->aud_pcm_ramp_value>0)   \
*/

/***********************************************************************
 *  RISC Macro & Declaration Session
 ***********************************************************************/
//#ifdef SUPPORT_RECEIVER
void AUDIF_Init_NewDSPCodec(UINT32 coding_mode);
//#else
//void AUDIF_Init_NewDSPCodec(UINT16 coding_mode);
//#endif

UINT16 AUDIF_Set_FrqMsk(UINT16 mask);
UINT16 AUDIF_Get_FrqMsk(void);

void AUDIF_Set_Channel(int chn);
int AUDIF_AutoDownload_Codec(UINT8 chn);
void AUDIF_Set_CodingMode(UINT32 coding_mode);

void AUDIF_Set_SampleRate(int smp_rate);
void AUDIF_Set_SmpRate(UINT32 freq);

/*======================================*/
/*===== Media Initialization APIs ======*/
/*======================================*/
void AUDIF_Init_DSPCodingMode(void);
void AUDIF_Init_Audio(void);
void AUDIF_Init_CDDA(void);
void AUDIF_Init_DTSCD(void);
void AUDIF_Init_AC3CD(void);
void AUDIF_Init_MIDI(void);
void AUDIF_Init_WMA(void);
void AUDIF_Init_AAC(WAVFORMATMACRO *wfmt);
void AUDIF_Init_MP3(void);
void AUDIF_Init_JPG(void);

#ifdef INCLUDE_MP3_ENCODER
void AUDIF_Init_CD_MP3_ENCODER(void);
#endif

/***********************************************************************
 *  DSP Macro & Declaration Session
 ***********************************************************************/


/*======================================*///add by Steven 2006/4/10 // 
/*=====    MIC Support Setting related     =====*/
/*======================================*/

//set to support mic or not// 
extern void AUDIF_Set_MICSupport(UINT8 mic_status);

//get the support info of mic//
extern UINT8 AUDIF_Get_MICSupport(void);

/*======================================*/
/*=====    Flow Control APIs    ======*/
/*======================================*/
int AUDIF_Set_FastForward(BYTE speed);
int AUDIF_Set_Play(void);
int AUDIF_Set_Pause(void);
int AUDIF_Set_Stop(void);
int AUDIF_Set_Continue(void);
void AUDIF_Reset_DSP(void);
void AUDIF_Wait_DSPReady(int dspChanged);

//Audio DSP SPDIF control command ( 0:OFF, 1:PCM, 2:BITSTREAM )
inline int AUDIF_Set_SPDIF(UINT8 mode); //(UINT32 mode);

//Audio DSP Output Mode control command
//0x01:Stereo(L/R), 0x02:L/L, 0x03:R/R, 0x04:Auto-L, 0x05:Auto-R, 
//0x06:5.1 channel, 0x07:2 channel, 0x08:DownMix Lx,Rx(for ProLogic)
//0x10:RF_MODE-K3, 0x20:LINE_MODE-K2, 0x30:no vocal, 0x40:left vocal, 
//0x50:right vocal, 0x60:both vocal
inline int AUDIF_Set_OutputMode(UINT8 outmode, UINT16 outparam); //(UINT32 outmode, UINT32 outparam);

/*======================================*/
/*=====    Volume Related APIs    ======*/
/*======================================*/
int AUDIF_Set_Volume(UINT8 x); //(UINT16 x);
int AUDIF_Demute();

//Audio DSP key-shift control command ( 1~15 )
inline int AUDIF_Set_Key(UINT8 keyshift); //(UINT32 keyshift);
//Audio DSP 3D-Surround control command ( 0:off, 1~..:type )
inline int AUDIF_Set_Surround(UINT8 stype); //(UINT32 stype);
//Audio DSP set EQ type command (0:standard, 0x0010:user-defined )
inline int AUDIF_Set_EQType(UINT8 eqtype); //(UINT32 eqtype);
//Audio DSP ECHO control command ( level:0(off)  (light)1~8(heavy) )
inline int AUDIF_Set_Echo(UINT8 delay, UINT16 decay); //(UINT32 delay, UINT32 decay);
inline int AUDIF_Set_EchoPara(UINT8 x); //(UINT16 x);

//Audio DSP MIC control command
//threshold://(0~0xff:0x55:for Yuxing, 0x35 for small board, 0x25 for large board)
//sensitivity:(1~7:default=1)
//on:threshold=0, sensitivity=0 //off:threshold=0xff, sensitivity=0xff
inline int AUDIF_Set_MICStatus(UINT8 threshold, UINT16 sensitivity); //(UINT32 threshold, UINT32 sensitivity);
//Audio DSP MIC Vol(gain) control command ( 0~8(0:off) )
inline int AUDIF_Set_MICVol(UINT8 tblval); //(UINT32 tblval);
inline int AUDIF_Set_MICVol2(UINT8 tblval); //(UINT32 tblval);
//Pro LogicII control
inline int AUDIF_Set_ProLogicII(UINT8 mode); //(UINT32 mode);

/*======================================*/
/*=====   Speaker Related APIs    ======*/
/*======================================*/

//Audio DSP Speaker Delay control command
//spk : 1(center spk), 2(surround spk)  //delay: time(ms)
inline int AUDIF_Set_SpkDelay(UINT8 spktype, UINT16 delay); //(UINT32 spktype, UINT32 delay);
//Audio DSP Front Speaker Gain control command ( 0~8(0:off) )
inline int AUDIF_Set_FSPKGain(UINT8 gainval); //(UINT32 gainval);
//Audio DSP Center Speaker Gain control command ( 0~8(0:off) )
inline int AUDIF_Set_CSPKGain(UINT8 gainval); //(UINT32 gainval);
//Audio DSP Surround Speaker Gain control command ( 0~8(0:off) )
inline int AUDIF_Set_SSPKGain(UINT8 gainval); //(UINT32 gainval);
//Audio DSP 5 Speaker Gain control command ( s:speaker_type x:gain)
inline int AUDIF_Set_5SPKGain(UINT8 spktype, UINT8 gainval); //(UINT32 spktype, UINT32 gainval);

void AUDIF_Set_SubWoof(UINT8 status); //Audio DSP Sub-woof control command //0:OFF, 1:ON

inline void AUDIF_Set_BassConfig(UINT16 spktype, INT16 setupvalue); //(UINT8 ufront, UINT8 ucenter, UINT8 usurround, UINT8 usub);
inline UINT16 AUDIF_Get_BassConfig(void);
//#define AUDIF_Set_BassMag(x) DSP_AudioIOControl(BASSMANAGEMENT,0,x) 

inline int AUDIF_Flush_Buffer(void);
inline int AUDIF_Set_VCDFF2PLAY(void);

/*==============================*/
/*=====  WMA related APIs  =====*/
/*==============================*/
void AUDIF_WMA_Init_Parm();

/*======================================*/
/*=====  Wave format related APIs  =====*/
/*======================================*/
void lpcm_check_param(BYTE* pType);
void AUDIF_LPCM_Init_Parm(UINT32 mode, WAVFORMATMACRO *wfmt);
int AUDIF_Init_Wave_Audio(WAVFORMATMACRO *wfmt);
void	AUDIF_AAC_Init_Parm(WAVFORMATMACRO *wfmt);
void	AUDIF_AAC_Init_Freq(UINT32 sample_freq_index);

/*======================================*/
/*=====     Message Queue APIs     =====*/
/*======================================*/
#ifdef MESSAGE_QUEUE
INT32 AUDIF_Wait_GeneralAck(void); // wait_genwait_ack();
INT32 AUDIF_Wait_StateTransAck(void); // wait_statewait_ack();
void  AUDIF_Polling_MQ(void);
#endif

/*=====================================*/
/*======     DSP buffers          =====*/
/*=====================================*/
#define get_dsp3_im_ptr()	get_dsp_im_ptr(0,0)
#define	get_dsp3_pm_ptr()	get_dsp_pcm_ptr(0,0)
#define	get_dsp3_dm_ptr()	get_dsp_aud_ptr(0,0)

#define AUDIO_BITSTREAM_START   0               // in 24-b word
//ycwen 2005/1/21 : 
//When mp3_jpeg_cowork, we allocate 48k bytes PM for mp3
//But must adjust back to 9k bytes when WMA or AC3 decoder is using
#ifdef	MP3_JPEG_COWORK 
    #define MP3_AUDIO_BITSTREAM_LEN         16*1024          // in 24-b word     
    #define NON_DTS_AUDIO_BITSTREAM_LEN     3*1024          // in 24-b word
#else
    //Use the common dsp code file "dsp3rom.d16.mp3".
    #define NON_DTS_AUDIO_BITSTREAM_LEN     3*1024          // in 24-b word
#endif
#ifdef SDRAM_16Mb_Mode//nono 3-12-2 14:09
    #define DTS_AUDIO_BITSTREAM_LEN         3*1024          // in 24-b word
#else//SDRAM_16Mb_Mode
    #define DTS_AUDIO_BITSTREAM_LEN         4*1024          // in 24-b word
#endif//SDRAM_16Mb_Mode

#define LPCM_AUDIO_BITSTREAM_LEN        (5*1024)        //terry,2004/3/26 11:14AM
#define AUDIO_BITSTREAM_LEN             NON_DTS_AUDIO_BITSTREAM_LEN

UINT16	dsp24ya, audya, pcmya;
UINT8   force_set_cd_md;


#endif		// __AUDDRV_H__
