#ifndef	__AVSYNC_H
#define	__AVSYNC_H


//
// when audio out of sync (with stc), update stc with
// new pts (with some offset).
//
#define	AVSYNC_ADJUST_STC_WITH_AUDIO_PTS

//
// STC_CLK
// a 90 kHz system time counter/stamp
//
#define	STC_CLK				90000
#define	INVALID_PTS			(-1)
#define B_FRAME_DELAY		(3000)

//
// PACK_SCR_BUFFERING
// NAVI_SCR_BUFFERING
//
// when pack_scr used to initialize STC (mpeg1 or mpeg2 svcd), 
// we set STC to (pack_scr-PACK_SCR_BUFFERING) in order to 
// compensate SCR to STC buffering effect
//
#define	PACK_SCR_BUFFERING	((int)(0.15 * STC_CLK))
#define	NAVI_SCR_BUFFERING	((int)(0.10 * STC_CLK))

//
// SCR_MAX
// 
// used to control the bitstream enter the decoder time.
// if the (SCR-STC) of the following packet is greater than
// this value we will stop the bitstream incoming.
//
// PTS_JUMP: 2 (20011121)
//
#define	AVSYNC_SCR_MAX		((int)( 0.1 * STC_CLK))
#ifdef ORITRON_HK_DVD //caoh 05/08/02 aviod <MARIAH> interupter Audio
#define	AVSYNC_SCR_SETUP	((int)( 14.0 * STC_CLK))
#else
#define	AVSYNC_SCR_SETUP	((int)(3.0 * STC_CLK))
#endif
#define	AVSYNC_SCR_JUMP_MAX	((int)(10.0 * STC_CLK))
#define	AVSYNC_PTS_JUMP_MAX	((int)( 2.0 * STC_CLK))
#define	AVSYNC_VPTS_JUMP_MAX	((int)(20.0 * STC_CLK))

//
// STC_PDIFF_SETUP
// (PTSa - STC)
// the difference of audio PTS and STC.  I think real
// audio PTS is about 0.1s (CENTER) slower then we receive.
// therefore when we receive PTSa=0.5s, that means it 
// should enter decoder at about STC=0.4s.
//
// NDIFF:
// audio is too slow. need to speed up??
//
#define	AVD_STC_AUDIO_CENTER        ((int)( 0.10 * STC_CLK))
#define	AVD_STC_PDIFF_SETUP         ((int)( 2.0  * STC_CLK) + AVD_STC_AUDIO_CENTER)
#define	AVD_STC_NDIFF_SETUP         ((int)(-2.0  * STC_CLK) + AVD_STC_AUDIO_CENTER)
#define	AVD_STC_ASDIFF_WARNING      ((int)(0.5	* STC_CLK) + AVD_STC_AUDIO_CENTER)

#define	AVD_STC_AV_IN_SYNC          ((int)(0.7	* STC_CLK))

//
// (PTSv - STC)
// video should be a little slow with audio since
// audio has some delay buffer. i think -0.2 is a good 
// value
// (that is: WAIT<SKIP)
//
// DIFF_WAIT: when PTS-STC is greater than this value: wait
// DIFF_SKIP: when PTS-STC is less than this value: skip
//
#define	AVD_VIDEO_DIFF_WAIT	((int)(0.1 * STC_CLK))
#define	AVD_VIDEO_DIFF_SKIP	((int)(-0.80 * STC_CLK))

//
// AVD_PTS_OUT_OF_SYNC
//
// if the PTS-difference is greater than this value
// then we will filter this out and record.  only 2
// consecutive PTS (of the same kind) will take effect.
//
#define	AVD_PTS_OUT_OF_SYNC	((int)(20.0 * STC_CLK))

#endif/*__AVSYNC_H*/
