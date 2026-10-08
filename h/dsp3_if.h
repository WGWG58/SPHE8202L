#ifndef	__DSP3_IF_H
#define	__DSP3_IF_H

#include "types.h"
#include "func.h"
#include "regmap.h"
#include "dsp3_def.h"

void	dsp3_hw_reset(void);
void	dsp3_stop(void);
void	dsp3_download(const BYTE *DspRom, int DspRomLen);
int     dsp3_mp3init(const void *DspRom, unsigned DspRomLen);
void    set_aud_buf(unsigned a, unsigned b, unsigned c);


void	reset_audio_buf();
void	set_dsp3_pcm_value(unsigned x_off, unsigned value);
UINT32	get_dsp3_pcm_value(unsigned x_off);
int     dsp3_get_rest_buf_size();
#define dsp3_get_data_size()        (abv_size - dsp3_get_rest_buf_size())
#define get_abv_free_exact()        dsp3_get_rest_buf_size()

#if 0 //2004AUDDRV move to auddrv.h
#define	dsp3_ramp_down(x)					\
	do {									\
		regs0->aud_pcm_ramp_delta = 1;		\
		regs0->aud_pcm_ramp_cfg = 1;		\
	} while (0)

#define	dsp3_ramp_up(x)						\
	do {									\
		regs0->aud_pcm_ramp_delta = 1;		\
		regs0->aud_pcm_ramp_cfg = 2;		\
	} while (0)

//change dsp3_ramp_wait() method equals to to delay_srv_10ms(3) to prevent dead loop
#define	dsp3_ramp_wait()				delay_srv_10ms(3)
/*
#define	dsp3_ramp_wait()					\
	do {									\
		polling();							\
	} while (regs0->aud_pcm_ramp_value>0)	\
*/
#endif //2004AUDDRV
//============================
//Audio Driver Service Provider Interface Function
//============================

//return: 0:fail, 1:success
#ifdef SUPPORT_SOUND_EFFECT
extern int AudioIOControl(UINT16 wCode, UINT32 cType, UINT32 wParam);
#else
extern int AudioIOControl(UINT16 wCode, BYTE cType, UINT16 wParam);

#endif
//return: -1: error, others
extern int AudioIOStatus(UINT16 wCode);

//============================
//Audio Application Programming Interface Function
//============================

#if 0 //2004AUDDRV
//Audio DSP flow control command
extern int AudioSetPlay();      //AudioIOControl(FLOW, AUDIOPLAY, 0) for VCD
                                //AudioIOControl(FLOW, AUDIOPLAY, 1) for MP3(pure audio)

extern int AudioSetContinue();  //AudioIOControl(FLOW, AUDIOCONTINUE, 0)
extern int AudioSetStop();      //AudioIOControl(FLOW, AUDIOSTOP, 0)
extern int AudioSetPause();     //AudioIOControl(FLOW, AUDIOPAUSE, 0)

#define AudioFlushBuffer()        AudioIOControl(FLOW, AUDIOFLUSH, 0)
#define AudioSetVCD_FF2PLAY()     AudioIOControl(FLOW, AUDIOFF2PLAY, 0)

extern int AudioFastForward(BYTE speed);  //AudioIOControl(FLOW, AUDIOFFxx, 0)

//Audio DSP set volume command


#define AudioSetVolume(x)         AudioIOControl(VOLUME, x, 0)
//freyman 2002-7-26 21:34
#ifdef SUPPORT_AMP
#undef AudioSetVolume(x)
int AudioSetVolume(UINT16 x);
#endif

#if 0 //kennymark it 2002/2/29
#if defined(TAS3001_AMP)  // jason ych add ti3001 2-8-10 11:36
#undef AudioSetVolume(x)
extern void set_volume(BYTE);
#define AudioSetVolume(x)       set_volume(x)
#endif 
#endif
//terry,0508 ,test audio whilt noise            
#ifdef      NO_AUD_MIC_OFF
#undef AudioSetVolume(x)
int AudioSetVolume(UINT16 x);
                        
#endif

#ifdef      NO_AUD_ECHO_OFF
#undef AudioSetVolume(x)
int AudioSetVolume(UINT16 x);

#endif



extern inline int AudioDemute();

//Audio DSP key-shift control command
//1~15
#define AudioSetKey(x)            AudioIOControl(KEY, x, 0)

//Audio DSP 3D-Surround control command
//0:off, 1~..:type
#define AudioSetSurround(x)       AudioIOControl(SURROUND, x, 0)

//Audio DSP Sub-woof control command
//0:OFF, 1:ON
#define AudioSetSubWoof(x)        AudioIOControl(SUBWOOF, x, 0)

//Audio DSP SPDIF control command
//0:OFF, 1:PCM, 2:BITSTREAM
#define AudioSetSPDIF(x)          AudioIOControl(SPDIF, x, 0)

//Audio DSP set EQ type command
//0:standard, 0x0010:user-defined
#define AudioSetEQType(x)         AudioIOControl(EQ, x, 0)

//Audio DSP Output Mode control command
//0x01:Stereo(L/R), 0x02:L/L, 0x03:R/R, 0x04:Auto-L, 0x05:Auto-R, 0x06:5.1 channel, 0x07:2 channel, 0x08:DownMix Lx,Rx(for ProLogic)
//0x10:RF_MODE-K3, 0x20:LINE_MODE-K2, 0x30:no vocal, 0x40:left vocal, 0x50:right vocal, 0x60:both vocal
#define AudioSetOutputMode(x, y)     AudioIOControl(OUTMODE, x, y)

//Audio DSP ECHO control command
//level:0(off)  (light)1~8(heavy)
#define AudioSetEcho(delay, decay)       AudioIOControl(ECHO, delay, decay)
#ifdef USE_MIC_ECHO_PARAM
int AudioSetEchoPara(UINT16 x);
#endif
//Audio DSP MIC control command
//threshold://(0~0xff:0x55:for Yuxing, 0x35 for small board, 0x25 for large board)
//sensitivity:(1~7:default=1)
//always on:threshold=0, sensitivity=0
//always off:threshold=0xff, sensitivity=0xff
#define AudioSetMIC(threshold, sensitivity)    AudioIOControl(MIC, threshold, sensitivity)

//Audio DSP MIC Vol(gain) control command
//0~8(0:off)
#define AudioSetMICVol(x)          AudioIOControl(AD, x, 0)
#define	AudioSetMICVol_2(x)		   AudioIOControl(AD_2, x, 0)	//wangfeng 2003-09-12 17:11


//Jeff 20020129
//Audio DSP Speaker Delay control command
//spk : 1(center spk), 2(surround spk)
//delay: time(ms)
#define AudioSetSpkDelay(spk, delay)    AudioIOControl(SPKDELAY, spk, delay)

//Audio DSP Front Speaker Gain control command
//0~8(0:off)
#define AudioSetFSPKGain(x)             AudioIOControl(FSPKGAIN, x, 0)

//Audio DSP Center Speaker Gain control command
//0~8(0:off)
#define AudioSetCSPKGain(x)             AudioIOControl(CSPKGAIN, (x*2), 0)

//Audio DSP Surround Speaker Gain control command
//0~8(0:off)
#define AudioSetSSPKGain(x)             AudioIOControl(SSPKGAIN, x, 0)

#define AudioSet5SPKGain(s, x)          AudioIOControl(s, x, 0)
#endif //#if 0 //2004AUDDRV

#endif

#if 0 //2004AUDDRV
#ifdef  TEST_BASS_MANAGEMENT //Andew 20040803
    #ifdef  TEST_BASS_COMMAND   
        #define AudioSetBassMag(x)    AudioIOControl(BASSMANAGEMENT,0,x) 
    #endif
#endif
#endif
