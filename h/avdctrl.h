#ifndef	__AVDCTRL_H
#define	__AVDCTRL_H

#include "types.h"

#ifndef	EXTERN
#define	EXTERN	extern
#endif

//#include "avd.h"
#include "vpp.h"
#include "kinf.h"

#define	CHK_IDLE	0
#define	CHK_FOR_I	1
#define	CHK_FOR_R	2

//
// current UI state
#define	avdst_fast_time()	(AVD_fast_factor)
#define AVD_FAST_JUMP		3

//
// current PE state
#define	is_avd_fast()		(batch_fast_time || is_avd_playback_fast())
#define	is_avd_slow()		is_avd_playback_slow()
#define	is_avd_step()		is_avd_playback_step()
#define	is_avd_paused()		is_avd_playback_pause()

//
// status updated every-field
//
EXTERN	UINT8	avdflg_not_realtime;
EXTERN	UINT8	avdflg_speed_normal;
EXTERN	UINT8	avdflg_reset_stc_when_play;
EXTERN	UINT8	avdflg_flush_pci_when_play;

void    avd_update_status(void);


//
// avd_not_realtime()
//
// NOT realtime playback (no user operation)
// user forces playback in a speed different than design.
// pause/fast/slow/step...
//
#define	avd_not_realtime()	(avdflg_not_realtime)

// 
// avd_realtime()
//
// realtime playback (no user operation)
//
#define	avd_realtime()		(!avd_not_realtime())


//
// avd_normal_speed():
// follow the bitstream speed
//
#define	avd_normal_speed()	(avdflg_speed_normal)

//
// single_field:
// 1. frame_rate_control
//    during frame-rate conversion
//
// 2. user operations
//    pause
//    fast
//    step
//    slow			(not_realtime)
// except following cases
// 1. 32 pulldown (must be frame-source??)
// 2. only single-frame sequence (showing first picture in sequence..)
//
#ifdef SUPPORT_VIDEO_BUFFER_SWITCHING
#define avd_single_field()	(!IS_SRC_PROGRESSIVE() && avd_not_realtime())
#else
#define avd_single_field()	(!IS_SRC_PROGRESSIVE() & ((!IS_VID_DIS_FRCTL() & !avd_normal_speed()) | avd_not_realtime()))
#endif

#define	avd_sync_find_I()	(chk_first_B==CHK_FOR_I)
#define	avd_sync_found()	(chk_first_B==CHK_IDLE)

#define	avd_play_ref1()		(AVD_state==STATE_1STREF)
#define	avd_play_refs()		(AVD_state==STATE_REFS)
#define	avd_play_only_ref()	(avd_play_ref1() | avd_play_refs())


//
//
#define	avd_decode_frame()      (avd_play_ref1() | is_avd_fast())

#define	avd_reset_stc_state()           (!avd_realtime())
#define	avd_pic_check_pts()             avd_realtime()
#define	avd_ignore_tpf_flag()           ((!IS_VID_DIS_FRCTL() & !avd_normal_speed()) | avd_not_realtime())
int avd_ignore_rff_flag(void);
int avd_framerate_ctrl(void);

#define	avd_drop_av_packet()            (0)

#define	avd_jump_at_1STREF()            (batch_fast_time<0)

#define	avd_support_mpeg2()		1
#define	avd_parse_user_data()		avd_is_dvd()
#define	avd_support_line21()		avd_is_dvd()

#define is_dsi_search_sup()             (dsi_state==DSI_SP_JUMP)
#define is_dsi_search_video()           (dsi_state==DSI_VIDEO_JUMP)
#define is_dsi_search()                 (is_dsi_search_sup() || is_dsi_search_video())
#define	avdkern_drop_audio()		(AVD_slow_factor | is_dsi_search() | is_avd_no_audio())
#define	avdkern_drop_private1_audio()	avdkern_drop_audio()


#define	avd_search_seq_header()		(AVD_state==STATE_FINDFIRSTSEQ)

int     avd_parse_private1(void);
int     avd_parse_private2(void);

int avd_slow_read();  
int avd_get_fast_time(void);
int avd_parse_drop_p_pic(void);
int avd_decode_drop_p_pic(void);
int avd_parse_drop_b_pic(void);
int avd_decode_drop_b_pic(void);
void dvd_batch_start(void);

#endif

