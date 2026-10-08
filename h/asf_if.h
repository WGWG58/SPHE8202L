#ifndef __ASF_IF_H
#define __ASF_IF_H

#include "types.h"
#include "wave_fmt.h"


//#define	SUPPORT_ASF
#define	SUPPORT_ASF_PTS

#ifdef	ASFEXTERN_HERE
#define	ASFEXTERN
#else
#define	ASFEXTERN		extern
#endif

typedef struct tASFAUDOBJECT
{
    UINT8           nAudSN;         // audio stream number
    WAVFORMATMACRO  wfmt;           // waveformat structure

} ASFAUDOBJECT;

// file property variables
ASFEXTERN	UINT64	asf_data_pck_count;
ASFEXTERN	UINT64	asf_file_duration;		// in 100-ns unit
ASFEXTERN	UINT64	asf_send_duration;		// in 100-ns unit
ASFEXTERN	UINT64	asf_preroll;			// in milliseconde unit
ASFEXTERN	UINT32	asf_file_flag;
ASFEXTERN	UINT32	asf_pck_size;
ASFEXTERN	UINT32	asf_max_bitrate;
ASFEXTERN	UINT32	asf_head_obj_count;
ASFEXTERN	UINT16	asf_pck_duration;
ASFEXTERN	UINT64	asf_header_size, asf_pck_count, asf_pck_num;
ASFEXTERN	UINT64	asf_idx_duration;
ASFEXTERN	BYTE	bPldProperty;
ASFEXTERN	BYTE	bCheckPldProperty;
ASFEXTERN	INT64	asf_cur_pl_pts;		// in 90 khz
ASFEXTERN	UINT32	asf_pl_base_size;		
ASFEXTERN	UINT32	asf_apb_base;		
ASFEXTERN	UINT64	asf_skip_packet_num;		
ASFEXTERN	UINT32	asf_one_packet_time;
ASFEXTERN	UINT32	asf_ext_header_offset;
ASFEXTERN	UINT32	asf_ext_header_size;
ASFEXTERN	UINT32	asf_ext_cnt_des_offset;
ASFEXTERN	UINT32	asf_ext_cnt_des_size;
ASFEXTERN	UINT32	asf_aud_idx_offset;
ASFEXTERN	UINT32	asf_aud_idx_size;
ASFEXTERN	UINT32	asf_aud_idx_cnt;
ASFEXTERN	UINT32	asf_aud_idx_duration;
ASFEXTERN	UINT64	asf_aud_idx_blk_offset;
ASFEXTERN	UINT64	asf_framerate;
ASFEXTERN	INT32	asf_packet_framerate;
ASFEXTERN	UINT32	asf_pts_vid_start;
ASFEXTERN	UINT32	asf_pts_aud_start;
ASFEXTERN	UINT32	asf_pre_vid_object;
ASFEXTERN	UINT32	asf_pre_aud_object;
ASFEXTERN	BYTE	b_start_count_time;
ASFEXTERN	UINT32	asf_aud_duration;
ASFEXTERN	BYTE	b_set_aud_duration;
ASFEXTERN	BYTE	b_set_pck_framerate;	
ASFEXTERN	BYTE	b_after_k_frame;	
ASFEXTERN	UINT32	asf_k_frame_object;	
ASFEXTERN	BYTE	bNeedAddpreroll;

#ifdef	SUPPORT_WMA
// flow control variables
ASFEXTERN   BYTE    asf_file_start;
//ASFEXTERN   UINT64	asf_file_duration;
ASFEXTERN   BYTE    asf_first_pck;
ASFEXTERN   BYTE    snVidTab[8], snAudioCnt, snVideoCnt, nAudio, nVideo;
ASFEXTERN   BYTE    ASFAudioStream, ASFVideoStream;
ASFEXTERN   ASFAUDOBJECT    snAudTab[8];

//ASFEXTERN   UINT32  asf_pck_size;
ASFEXTERN   UINT8	asf_pck_state;
ASFEXTERN   UINT64  asf_data_size, asf_header_size_keep;
ASFEXTERN   UINT64  asf_pck_current;
ASFEXTERN   UINT32	asf_pck_time;
ASFEXTERN   UINT32	asf_AB_start_pck;
ASFEXTERN   UINT32  asf_AB_end_pck;
ASFEXTERN   UINT32  asf_resume_pck;
ASFEXTERN   UINT32  asf_resume_len;
#endif	// SUPPORT_WMA

#ifdef SUPPORT_ASF
UINT32	Is_ASF_File(BYTE* srcptr, UINT32 bufsize);
int		doASFPreParser(BYTE *srcptr, INT32 bufsize);
int		asf_init_audio_stream(int aud_strm_num);
UINT32	asf_ready_to_jump(int speed);
int		asf_get_next_I(int speed, UINT32* p_frm_offset);
//UINT32 GET_ASF_TIME();
INT64 GET_ASF_TIME_STC();
#ifdef SUPPORT_ASF_PTS
ASFEXTERN UINT8 latch_audio_state;
ASFEXTERN UINT32 latch_pld_position;
ASFEXTERN UINT64 latch_audio_pts;
ASFEXTERN UINT64 jump_audio_pts;
ASFEXTERN UINT8  dsp_ring_back;
ASFEXTERN UINT16 latch_pld_buffer;
#define	ASF_LATCH_AUDIO_RESET	0
#define	ASF_LATCH_AUDIO_START	1
#define	ASF_LATCH_AUDIO_PLDIN	2
#define	ASF_LATCH_AUDIO_JUMP	3
ASFEXTERN UINT64 latch_video_pts;
ASFEXTERN UINT64 jump_video_pts;
#endif


#endif

void ASF_init(void);
int doASFFillHeader(void);//Steven 2006/09/19 add
int doASFHeader(void);
int doASFData(void);
int doASFPckInit(void);
int doASFSPload(void);
int doASFMPload(void);

inline void ASF_PCK_Init(void);
inline UINT32 get_asf_pck_time(void);

#endif  //__ASF_IF_H

