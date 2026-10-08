/*! \ingroup kern_if
 * @{
 */
//
// FILE
// kern_if.h
//
// DESCRIPTION
// This file is to provide an interface between kernel programs
// and upper software.  Don't place anything other than kernel
// definitions.
// Also always make sure this file is coherent with the kernel
// program.
//

#ifndef	KERNINF_H
#define	KERNINF_H

#include "types.h"

#include "cpu.h"
//swpong 2006 0530 #include "framebuf.h"
#include "viddec.h"
//swpong 2006 0530, add the following
#include "mpegsys.h"
#include "mpgkern.h"
#include "mpgvid.h"




// chip part number & version

extern UINT16 CHIP_VERSION;

/**
 * \fn static inline void SET_CHIP_VERSION(int val)
 * \brief Set Chip Version.
 * \param val: chip version number.
 * \return none.
 * \note none.
***************************************************/ 
static inline void SET_CHIP_VERSION(int val)
{
	CHIP_VERSION = val;
}

extern const UINT8 KernelVersion[];


// NAV
extern  UINT8   new_cell;

// DIP
extern  UINT8   dip_sel;
extern  UINT8   dip_enable;

// MB22
extern  UINT8   mb22_en;

// hardware clock gating
extern  UINT8   kernel_clock_gating;

// error concealment
extern  UINT32  kernel_error_counter;
extern  UINT8   kernel_error_concealment;
extern  UINT8   kernel_error_mb_threshold;

#define	IS_DECERR()			((kernel_error_counter>0) && (viddec_nodecode>5))
#define	CLR_DECERR()		(kernel_error_counter=0)

// for portable
extern	UINT8	kernel_portable_bonding;

// system-layer
extern  UINT8   kiPckType;

#define KI_IS_VOB_PCK()             (KI_PCKTYPE_VOB == kiPckType)
#define KI_IS_AOB_PCK()             (KI_PCKTYPE_AOB == kiPckType)

extern  UINT8   kiAuStream;
extern  UINT8   kiAuStreamNum;


// buffer control function and defines
void set_av_time_stamp(UINT32 media, UINT32 type, INT64 time_stamp);
void av_check_buf_full(int avflg, UINT32 mode);

extern void set_avsync_option(UINT32 option);

// frame rate control
inline void frctl_setup_mode(int mode);
void frctl_clear_count();
void frctl_set_display_rate();
void frctl_set_frame_rate(int rate, int scale);
int frctl_frame_match();
INT64 frctl_frame_to_stc(UINT32 frame);
INT64 frctl_cur_frame_to_stc();
UINT32 frctl_frame_to_time(UINT32 frame);
UINT32 frctl_time_to_frame(UINT32 time);

// field decoding
int flddec_init(int enable, int b_mbline);

int do_video_parsing();
int do_mp4_parsing();

//#ifdef	SUPPORT_MP4
extern int (*calc_accm_audio_fPTS)();
extern INT64 (*calc_accm_video_fPTS)();
extern int (*do_audio_sync)();
// get_mp4_video_codec()

// video_property_flag
extern	UINT32 video_property_flag;

// mp4vid_status
// set by video parser, and cleared by file parser
extern	UINT8 mp4vid_status;

void set_mp4_frame(UINT32 frame);

#define	GET_MP4_FRAME()			(decoded_frame)
//#define	GET_MP4_STC()			frctl_frame_to_stc(decoded_frame)

//#define	GET_MP4_TIME()			frctl_frame_to_time(decoded_frame)	// in seconds
//UINT32	GET_MP4_TIME();			// in seconds
//INT64	GET_MP4_TIME_STC();		// in 90,000
UINT32	GET_MP4_DECODED_FRAME();// get precise decoded frame number.

// Initialization for each MPEG-4 file
int mp4vid_init(int width, int height, UINT32, UINT32);
// Initialization of an AVI chunk of MPEG-4.
inline void mp4vid_chunk_initialize();
void restart_mp4_video_engine();
// GOTO request. If 0 is returned, the GOTO request can not be performed.
int mp4vid_goto(int skip_vop_number);
void mp4_avfilled(int avflg);
inline UINT32 get_mp4_video_codec();
void add_skip_frame(int x);

//#endif	// SUPPORT_MP4

extern  INT8    R_skip;             /* used to skip REF pictures    */
extern  INT16   B_skip;             /* used to skip B picture   */
extern  INT8    P_frame;            // play P_frame and stop, if (P_frame==0) normal play
                                    // if (P_frame<0) stop
extern  INT8    P_vobu;             // play P_vobu and stop, if (P_vobu==0) normal play
                                    // if (P_vobu<0) stop
                                    //

extern	UINT8	vobu_DSI_valid;
extern  UINT8   nav_pck_cntr;
extern  BYTE    sequence_start;

extern  UINT32  play_finish_time;
extern  INT64   scr_current;

extern  INT64   PTS_audio;
extern  INT64   PTS_video;
extern  UINT8   picture_parsing_entry;
extern  UINT8   picture_parsed_entry;
extern  UINT8   picture_decoding_entry;

extern  UINT8   picture_coding_type;
extern  UINT16  pic_coding_ext0;

extern  INT16   vbv_y;
extern  INT16   vbv_x;
extern  INT16   vbv_by;
extern  INT16   vbv_bx;
#define video_parsing_barrier   vbv_by


/*
** STREAM ID
*/
extern  UINT8   stream_video;
extern  UINT8   stream_audio;
extern  UINT8   stream_audio_table[8];
extern  UINT8   stream_sup_table[32];
extern  UINT8   sub_stream_id_sup;
extern  UINT8   sub_stream_id_sup_2;


/*
*/
extern  UINT8   audio_filled;
extern  UINT8   video_filled;
extern  UINT8   avbuf_filled;
extern  UINT16   video_slow_wait;

extern  UINT8   forward_ref_option;
extern  INT8    dis_pic_id_saved_0;

extern  UINT32  decoded_pic;
extern  UINT32  decoded_frame;
extern	UINT32  video_dec_opt;

#define get_decoded_pic()   (decoded_pic)

extern  UINT8   frame_rate;

extern  UINT8   chk_first_B;

//
extern  UINT8   viddec_format;
#define get_decode_format()     (viddec_format)
#define set_decode_format(f)    (viddec_format=(f))


extern  UINT8   viddec_nodecode;

//

//swpong 2006 0526
static	inline	void	set_video_stream_id(unsigned id)
{
    stream_video = id;
}

static	inline	void	set_audio_stream_id(unsigned id)
{
    stream_audio = id;
}

static	inline	void	set_sub_stream_id_sup(unsigned id)
{
    sub_stream_id_sup = id;
}

static	inline	void	set_sub_stream_id_sup_2(unsigned id)
{
    sub_stream_id_sup_2 = id;
}
///////////////////////////////////////////////////////////////

#if defined(SPHE1000)||defined(SUPPORT_SOFT_HW_TTX)  ///yangli add for hwttx ,2006-9-28 9:32
#define CHK_TELETEXT	(1<<0)
extern UINT8 kernel_feature;
static	inline	void	setup_kernel_feature(BYTE val)
{
	kernel_feature = val;
}
static	inline	int		get_kernel_feature()
{
	return kernel_feature;
}
#endif

//
// kernel interface
//
extern  void    kernel_init(void);
extern	void	kernel_set_mode(UINT32 mode, UINT8* input);
extern  void    init_video_decoder(void);
extern	void	resync_av(void);
extern	void	resync_video(void);
extern	void	resync_audio(void);
extern	void	resync_video_bitstream(void);
extern	void	resync_audio_bitstream(void);
extern	void	clear_video_decoder();
extern	int     do_system_layer(void);


extern	int		ki_set_nav_info(UINT32, BYTE*);
extern	UINT32	ki_get_vbv_kused();
extern	UINT32	ki_get_vbv_kfree();
extern	int		ki_quick_callback(UINT32, BYTE*);
extern	UINT32	ki_get_video_bitrate();
extern	int		ki_check_stream_offset(UINT32, UINT32);
extern	void	dsi_update_kernel(void);
extern  void    ki_set_pck_type(UINT8);
extern  void    ki_set_au_stream(UINT8);

// for calculating (a * b * c) / d, in 64-bit resolution
extern	INT64 __cal64_type1(UINT32 a, UINT32 b, UINT32 c, UINT32 d);
// for calculating (a * b * aud_frequency) / (aud_frame_size * c)
extern	UINT32 __cal64_type2(UINT32 a, UINT32 b, UINT32 c);


/*
**	WATCHDOGWATCHDOG
*/
void    watchdog_renew(int n);
void    watchdog_onoff(int n);


/*
**	SUP	SUP	SUP	SUP	SUP	SUP	SUP
*/
#include "supfunc.h"
extern  void    set_sup_hwbuf(unsigned ya, unsigned ye);
extern  void    set_sup_hwbuf2(unsigned ya, unsigned ye);


/*
**      VPP     VPP     VPP     VPP     VPP     VPP     VPP
*/

#if 0
extern void		setup_vpp_par_mode(int flag);

extern  void    setup_vpp_mapping(int mapping, int sdram_reorder);
extern  int     get_vpp_mapping(void);
extern  void    vpp_set_bg_color(int y, int cb_cr);
#endif


/*
**      ENCODE
*/
extern  int     mpeg_encode(int id, int w, int h, int qscale, UINT8 *temp, UINT8 *output);
extern  void    mpeg_encode_target(int bits);



/*
**      TEST    TEST    TEST    TEST    TEST    TEST    TEST
*/
extern  UINT8   sys_test_reg_00;
extern  UINT8   sys_test_reg_01;
extern  UINT8   sys_test_reg_02;
extern  UINT8   sys_test_reg_03;



#endif/*__KINF_H*/

