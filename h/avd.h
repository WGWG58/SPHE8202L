#ifndef	__AVD_H
#define	__AVD_H

#include "types.h"
#ifndef	EXTERN
#define	EXTERN	extern
#endif

/*
**	MPEG1 AV Decoder States.
*/
enum
{
    STATE_IDLE              = 0x00, // 00
    STATE_PLAY              = 0x10, // 10
    STATE_PLAYONEROMSLIDE,          // 11
    STATE_PLAYROMSLIDE,             // 12
    STATE_PLAYSLIDE,                // 13
    STATE_PLAYMP3,                  // 14
    STATE_FAST,                     // 15
    STATE_FREEZE,                   // 16
    STATE_PAUSE,                    // 17
    STATE_PREVIEW,		    // 18
    STATE_READCD,
    STATE_SLOWMOTION,
    STATE_SINGLESTEP,
    STATE_FINDFIRSTNAV,
    STATE_FINDFIRSTSEQ,
    STATE_1STREF,
    STATE_REFS,				// play reference picture only
    STATE_BACKWARD,
    STATE_SEARCH            = 0x40,
};


/*
** VARIABLE
** AVD_state
**
** MPEG A/V Decoder State
*/
EXTERN	BYTE	AVD_state;
EXTERN	UINT8	AVD_playback_state;
EXTERN	UINT8	AVD_pause_mode;
EXTERN	INT8	AVD_fast_factor;
EXTERN	INT8	AVD_slow_factor;

#define	AVD_PAUSE_PAUSE		1
#define	AVD_PAUSE_STEP		2
#define	AVD_PAUSE_OFF		0

//
// LBA state
EXTERN	INT8	batch_fast_time;
EXTERN	INT8	ready_to_jump;
EXTERN	UINT8	VOBU_DIS;
EXTERN	UINT8	VOBU_PARSE;

#define	SetAVDState(x)		(AVD_state=(x))


//
// VARIABLE
// AVD_ctrl_flag
//
// MPEG A/V Decoder State Generated Flags.
//
#define	AVD_REALTIME	0x20		/* realtime playback??		*/
#define	AVD_SLIDE	0x10		/* playing current-decoding	*/
#define	AVD_PREVIEW	0x08		/* 9x9 preview??		*/
#define AVD_NOAUDIO	0x04
#define	AVD_PLAY_I	0x02		/* play I only			*/
#define	AVD_PLAY_IP	0x01		/* play IP only			*/

EXTERN	UINT8	AVD_ctrl_flag;

#define	IsAVDPlayIPB()		((AVD_ctrl_flag & (AVD_PLAY_I|AVD_PLAY_IP))==0)
#define	IsAVDRealTime()		(AVD_ctrl_flag & AVD_REALTIME)
#define	IsAVDPreview()		(AVD_ctrl_flag & AVD_PREVIEW)


#define IsAVDSkipB()	        0


//
// VARIABLE
//
// program playback state
//
// normal
// fast-forward
// fast-backward
// slow-forward		(slow-factor)
// slow-backward	(fast-factor)
// step
// pause
//
#define	AVDST_PLAYBACK_NORMAL		0x10
#define	AVDST_PLAYBACK_FASTFORWARD	0x11
#define	AVDST_PLAYBACK_FASTBACKWARD	0x12
#define	AVDST_PLAYBACK_SLOWFORWARD	0x13
#define	AVDST_PLAYBACK_SLOWBACKWARD	0x14
#define	AVDST_PLAYBACK_STEP		0x15
#define	AVDST_PLAYBACK_PAUSE		0x16

#define	IsAVDPaused()	        (P_frame<0)
#define	is_avd_playback_step()		(P_frame>0)
#define	is_avd_playback_pause()		(P_frame<0)
#define	is_avd_playback_fastforward()	(AVD_fast_factor>0)
#define	is_avd_playback_fastbackward()	(AVD_fast_factor<0)
#define	is_avd_playback_slowforward()	(AVD_slow_factor>0)
#define	is_avd_playback_slowbackward()	(AVD_slow_factor<0)
#define is_avd_playback_repeat_ab()	(rep_ab_mode == REPEAT_FIND_B)

// combo
#define	is_avd_playback_step_or_pause()	(P_frame!=0)
#define	is_avd_playback_slow()		(AVD_slow_factor)
#define	is_avd_playback_fast()		(AVD_fast_factor)


#define is_avd_no_audio()		(AVD_ctrl_flag & AVD_NOAUDIO)

#define	get_avd_frame_to_play()		(P_frame)
#define set_avd_frame_to_play(n)	(P_frame = (n))

#define	is_avd_play_romslide()          (AVD_state==STATE_PLAYROMSLIDE \
                                        || AVD_state==STATE_PLAYONEROMSLIDE)
#define	is_avd_preview()                (IsAVDPreview())



//
// VARIABLE
// AVD_video_flag
//
// video bitstream level status.	
//
// 1. NTSC/PAL frame-rate
// 2. NTSC/PAL size
//
EXTERN	UINT8	AVD_video_flags;

// decode type
#define	AVD_VIDEO_FRAMERATE_UNKNOWN	0
#define	AVD_VIDEO_FRAMERATE_NTSC        1
#define	AVD_VIDEO_FRAMERATE_PAL		2
#define	AVD_VIDEO_FRAMERATE_MOVIE	3
#define	AVD_VIDEO_FRAMERATE_MASK        3

// decode size
#define	AVD_VIDEO_SIZE_PAL              (1<<2)
#define	AVD_VIDEO_SIZE_MASK             (1<<2)

// decode framerate
#define	AVD_VIDEO_FRAMERATE             (1<<7)


//
// VARIABLE
// AVD_video_status
//
// AVD_VIDEO_DECODED        has start to decoding at least 1 frame
// AVD_VIDEO_DECODED_MULTI  has start to decoding more then 1 frame
//
EXTERN	UINT8	AVD_video_status;

#define	AVD_VIDEO_DECODED		(1<<2)
#define	AVD_VIDEO_DECODED_MULTI		(1<<3)

#define	avd_set_decoded()	\
	do {    \
            unsigned status = AVD_video_status;     \
            if (status&AVD_VIDEO_DECODED) status |= AVD_VIDEO_DECODED_MULTI;    \
            AVD_video_status = status | AVD_VIDEO_DECODED;  \
	} while (0)

#define	is_avd_decoded()	(AVD_video_status & AVD_VIDEO_DECODED)
#define is_avd_decoded_first()	((AVD_video_status & (AVD_VIDEO_DECODED|AVD_VIDEO_DECODED_MULTI))==AVD_VIDEO_DECODED)


//
// VARIABLE
// AVD_media_status
//
// indicate current playback interrupt/timeout/end/error
//
// AVD_MEDIA_TIMEOUT
// request to stop playback as soon as possible
//
// AVD_MEDIA_INTERRUPT
// request to stop playback immediately
//
// AVD_MEDIA_ERROR
// internal error, stop playback immediately.
//
#define	AVD_MEDIA_TIMEOUT	(1<<0)
#define	AVD_MEDIA_INTERRUPT	(1<<1)
#define	AVD_MEDIA_ERROR		(1<<7)

EXTERN	UINT8	AVD_media_status;

int IsAVDMediaTimeout(void);
int IsAVDMediaInterrupt(void);
int IsAVDMediaError(void);
int AVD_SetMediaTimeout(void);
int AVD_SetMediaInterrupt(void);
int AVD_SetMediaError(void);
void AVD_ResetMediaStatus(void);


//
// VARIABLE
// avd_src_realtime()
//
// DESCRIPTION
// source is to be playbacked in realtime control
// (rom-based slide has no realtime control)
//
EXTERN  UINT8   avd_src_realtime;
#define	is_avd_src_realtime()	(avd_src_realtime)


//
// is_avd_tv_auto()
// decide if we have to do tv-format auto-switching
// don't auto-switch tv-format when (preview or rom-based title/fixed-sequence)
//
#define	is_avd_tv_auto()	(!(is_avd_play_romslide() || is_avd_preview()))


EXTERN	UINT8	avd_slow_factor;

void	avd_idle_state();
void	avd_play_state();
void	avd_fast_state();
void	avd_preview_state(void);
void	avd_playoneromslide_state(void);
void	avd_playromslide_state(void);
void	avd_pause_on();
void	avd_pause_off();
void	avd_step_state(int);
void	avd_slow_state(int);

#define	avd_play_frame(n)	avd_step_state(n)
#define	avd_slow(n)		avd_slow_state(n)

//
// VARIABLE
// avd_interpolation
// Display-Interpolation
//
#define	AVD_DISP_INTP_AUTO		0
#define	AVD_DISP_INTP_PROGRESSIVE	1
#define	AVD_DISP_INTP_SINGLE		2
EXTERN	UINT8	avd_interpolation;
#define	avd_disp_intp_mode(md)	(avd_interpolation = (md))

#define	is_avd_forced_progressive()	(avd_interpolation==AVD_DISP_INTP_PROGRESSIVE)
#define	is_avd_forced_single()		(avd_interpolation==AVD_DISP_INTP_SINGLE)

//
// VARIABLE
// avd_pause_interpolation
// Display-Interpolation during pause
// (same definition as avd_interpolation)
//
EXTERN	UINT8	avd_pause_interpolation;
#define	avd_disp_pause_intp_mode(md)	(avd_pause_interpolation = (md))



//
// vcd/dvd
#define	avd_is_vcd()		(cd_type_loaded==CDVCD20 || cd_type_loaded==CDVCD10)
#define	avd_is_dvd()		(cd_type_loaded==CDDVD)
#define	avd_is_cdrom()		(cd_type_loaded==CDROM)
#define	avd_is_svcd()		(cd_type_loaded==CDSVCD)
#define	avd_is_cvd()		(cd_type_loaded==CDCVD)
#define	avd_is_cdda()		(cd_type_loaded==CDDA)

extern  int avd_is_midi(void);



#endif/*__AVD_H*/

