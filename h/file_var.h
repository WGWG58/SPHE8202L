#ifndef	__FILE_VAR_H__
#define	__FILE_VAR_H__

#include "types.h"

#ifdef	FILEPLAYVAR_HERE
#define	FILE_EXTERN
#else
#define	FILE_EXTERN		extern
#endif

#define	FILE_MAX_AUDIO		0x8
#define	FILE_MAX_VIDEO		0x1

FILE_EXTERN STRM_TABLE	file_audio_table[FILE_MAX_AUDIO];	// only FCC_strf fp is recored, need to retrieve WAVEFORMATEX
FILE_EXTERN STRM_TABLE	file_video_table[FILE_MAX_VIDEO];	// only FCC_strf fp is recored, need to retrieve BITMAPINFOHEADER

BITMAPINFOHEADER	bmp_info;
#ifdef	AVI_INTERNAL_SUP
AVIStreamHeader		sp_strm;
BITMAPINFOHEADER	sp_bmp_info;
#endif

// file position/length information
FILE_EXTERN UINT32	file_start_lba;				// file start lba (in lba)
FILE_EXTERN UINT32	file_size;					// file size (in byte)
FILE_EXTERN UINT32	file_data_offset;			// data start offset (in byte)
FILE_EXTERN UINT32	file_data_size;				// data size (in byte)
FILE_EXTERN UINT32	file_idx_offset;			// index offset
FILE_EXTERN UINT32	file_idx_size;				// index size
FILE_EXTERN UINT32	file_idx_cnt;				// index counter
FILE_EXTERN UINT32	file_len;					// file length, the max of a/v length (in sec)
FILE_EXTERN INT64	file_len_STC;				// file length, the max of a/v length (in 90kHz STC)
//FILE_EXTERN INT64	file_aud_len;				// audio length (in 90kHz STC)
INT64	file_aud_len;				// audio length (in 90kHz STC)
FILE_EXTERN INT64	file_vid_len;				// video length (in 90kHz STC)
FILE_EXTERN UINT32	file_chunk_size;			// file media chunk size
FILE_EXTERN UINT32	file_vid_skip;				// video data that must be skipped(frame base)
FILE_EXTERN UINT32	file_aud_skip;				// audio data that must be skipped(after a/v resync), note that vbr is in audio frame granule.
FILE_EXTERN UINT32	file_aud_accum_size;		// For CBR audio, this is the number of bytes accumulated.
												// For VBR audio, this is the number of audio frame accumulated.
FILE_EXTERN UINT32	file_cur_fp;				// file cur_fp
FILE_EXTERN INT32	file_buf_len;				// file init buffer unused size
FILE_EXTERN UINT32	file_last_jump_time;		// last jump time
FILE_EXTERN BYTE    file_resume_counter;        // read counts before really excute resume

// file media stream counters
FILE_EXTERN UINT32	file_aud_num;				// audio stream number
FILE_EXTERN UINT32	file_vid_num;				// video stream number
FILE_EXTERN UINT32	file_sup_num;				// subpicture stream number
FILE_EXTERN UINT32	file_default_aud;			// default audio stream
FILE_EXTERN UINT32	file_default_vid;			// default video stream
FILE_EXTERN UINT32	file_default_sup;			// default subpicture stream
FILE_EXTERN UINT32	file_audio_strm;			// selected audio stream
FILE_EXTERN UINT32	file_video_strm;			// selected video stream
FILE_EXTERN UINT32	file_supic_strm;			// selected subpicture stream

// file playback related flags
//FILE_EXTERN UINT32	file_type;					// file type, such as AVI/ASF/etc.
UINT32	file_type;					// file type, such as AVI/ASF/etc.
FILE_EXTERN UINT32	file_flag;					// file flag, for each kind of files, the meanings differ
FILE_EXTERN UINT32	file_media_support;			// disable the support for certain media
FILE_EXTERN UINT32	file_play_state;			// file playback state
FILE_EXTERN UINT32	file_error_flag;			// file error flag
FILE_EXTERN UINT32	file_fast_jump;				// file fast jump level
FILE_EXTERN UINT32  strm_offset;				// used for srv0 to drop redundant data since data come in in 2k byte unit.

// RISC audio large buffer, two layer buffer to reduce the DSP bitstream buffer
FILE_EXTERN UINT32	audio_prefilled;			// turn on DSP feeding function in polling
FILE_EXTERN UINT32	aud_time_marker;			// audio buffer ringback flag (input)

FILE_EXTERN	UINT32	file_aud_buf;				// audio system layer big buffer start
FILE_EXTERN	UINT32	file_aud_bufend;			// audio system layer big buffer end
FILE_EXTERN	UINT32	file_aud_buf_size;			// audio system layer big buffer size
FILE_EXTERN BYTE	*file_aud_wtptr;			// file parser write pointer
FILE_EXTERN BYTE	*file_aud_rdptr;			// file parser read pointer

FILE_EXTERN UINT32	file_vbr_buf;				// audio vbr buffer start
FILE_EXTERN UINT32	file_aud_smp_head;			// vbr large buffer marker for audio samples
FILE_EXTERN UINT32	file_aud_smp_tail;			// vbr large buffer marker for audio samples

#ifdef SUPPORT_MP4_SUBTITLE
FILE_EXTERN UINT32	file_extsub_buf;			// external subtitle buffer start
FILE_EXTERN UINT32	file_extsub_bufend;			// external subtitle buffer end
FILE_EXTERN UINT32	file_extsub_bufsize;		// external subtitle buffer size
FILE_EXTERN UINT32	file_extsub_idx_buf;		// external subtitle index buffer start
FILE_EXTERN UINT32	file_extsub_idx_bufend;		// external subtitle index buffer end
FILE_EXTERN UINT32	file_extsub_idx_bufsize;	// external subtitle index buffer size
#endif	// SUPPORT_MP4_SUBTITLE

#endif	// __FILE_VAR_H__

