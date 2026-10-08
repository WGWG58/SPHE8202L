#ifndef __FILE_IF_H__
#define __FILE_IF_H__

#include "avi_if.h"
#include "file_var.h"
#include "file_def.h"

// macros for file_type
#define	RESET_FILE_TYPE()				(SET_FILE_TYPE(FILE_TYPE_UNKNOWN))
#define	SET_FILE_TYPE(x)				(file_type = (x))
#define	GET_FILE_TYPE(x)				(file_type)

#define	IS_FILE_TYPE_AVI()				(file_type == FILE_TYPE_AVI)
#define	IS_FILE_TYPE_ASF()				(file_type == FILE_TYPE_ASF)
#define	IS_FILE_TYPE_QT()				(file_type == FILE_TYPE_QT)
#define	IS_FILE_TYPE_ND()				(file_type == FILE_TYPE_ND)
#define	IS_FILE_TYPE_MPG()				(file_type == FILE_TYPE_MPG)
#define	IS_FILE_TYPE_WAVE()				(file_type == FILE_TYPE_WAVE)
#define	IS_FILE_TYPE_CDXA()				(file_type == FILE_TYPE_CDXA)
#define	IS_FILE_TYPE_OGG()				(file_type == FILE_TYPE_OGG)
#define IS_FILE_TYPE_MPG12()            (IS_FILE_TYPE_MPG()||IS_FILE_TYPE_CDXA())

// macros for file_flag
#define	RESET_FILE_FLAG()				(SET_FILE_FLAG(0))
#define SET_FILE_FLAG(x)				(file_flag = (x))
#define ADD_FILE_FLAG(x)				(file_flag |= (x))
#define SUB_FILE_FLAG(x)				(file_flag &= ~(x))
#define GET_FILE_FLAG()					(file_flag)

// macros for file_media_support
#define	RESET_FILE_SUPPORT_MEDIA()		(file_media_support = FILE_MODE_ALL)
#define SET_FILE_SUPPORT_MEDIA(x)		(file_media_support = (x))
#define ADD_FILE_SUPPORT_MEDIA(x)		(file_media_support|= (x))
#define SUB_FILE_SUPPORT_MEDIA(x)		(file_media_support &= ~(x))
#define GET_FILE_SUPPORT_MEDIA()		(file_media_support)

#define	FILE_AUDIO_SUPPORTED()			((file_media_support&FILE_SUPPORT_AUDIO) > 0)
#define	FILE_VIDEO_SUPPORTED()			((file_media_support&FILE_SUPPORT_VIDEO) > 0)
#define	FILE_SUPIC_SUPPORTED()			((file_media_support&FILE_SUPPORT_SUPIC) > 0)
#define	FILE_SUBT_SUPPORTED()			((file_media_support&FILE_SUPPORT_SUBT) > 0)
#define	FILE_IDX_SUPPORTED()			((file_media_support&FILE_SUPPORT_IDX) > 0)

// macros for file_media_flag
#define	RESET_FILE_MEDIA_FLAG()			(file_media_flag = FILE_STRM_FLAG_NONE | FILE_AV_INTERLEAVED)
#define SET_FILE_MEDIA_FLAG(x)			(file_media_flag = (x))
#define ADD_FILE_MEDIA_FLAG(x)			(file_media_flag |= (x))
#define SUB_FILE_MEDIA_FLAG(x)			(file_media_flag &= ~(x))
#define GET_FILE_MEDIA_FLAG()			(file_media_flag)

#define FILE_HAS_AUDIO()				((file_media_flag&FILE_AUDIO) > 0)
#define FILE_HAS_VIDEO()				((file_media_flag&FILE_VIDEO) > 0)
#define FILE_HAS_SUPIC()				((file_media_flag&FILE_SUPIC) > 0)

#define FILE_UNSUPPORT_AUDIO()			((file_media_flag&FILE_SUPPORTED_AUDIO) == 0)
#define FILE_UNSUPPORT_VIDEO()			((file_media_flag&FILE_SUPPORTED_VIDEO) == 0)
#define FILE_UNSUPPORT_SUPIC()			((file_media_flag&FILE_SUPPORTED_SUPIC) == 0)

#define IS_FILE_AUDIO_VBR()				((file_media_flag&FILE_AUDIO_VBR) > 0)
#define IS_FILE_AV_INTERLEAVED()		((file_media_flag&FILE_AV_INTERLEAVED) > 0)

// macros for file_play_state
#define	RESET_FILE_PLAY_STATE()			(file_play_state = FILE_NORMAL_STATE)
#define SET_FILE_PLAY_STATE(x)			(file_play_state = (x))
#define ADD_FILE_PLAY_STATE(x)			(file_play_state |= (x))
#define SUB_FILE_PLAY_STATE(x)			(file_play_state &= ~(x))
#define GET_FILE_PLAY_STATE()			(file_play_state)

#define	IS_FILE_DROP_AUDIO()			((file_play_state&FILE_DROPA_STATE) > 0)
#define	IS_FILE_DROP_VIDEO()			((file_play_state&FILE_DROPV_STATE) > 0)
#define	IS_FILE_DROP_SUPIC()			((file_play_state&FILE_DROPS_STATE) > 0)

// macros for file_error_flag
#define	IS_FILE_ERROR()					(file_error_flag >= AVI_ERR_CNT_THRESHOLD)
#define	CLEAR_FILE_ERROR()				(file_error_flag = 0)

// check normal playback
#define viddec_play()					(AVD_state==STATE_PLAY && AVD_playback_state==AVDST_PLAYBACK_NORMAL)

// APIs
int		file_init_playback(UINT32 msf, UINT32 len);
int		file_init_audio();
int		file_init_video();
int		file_init_supic();
int		file_set_audio_stream(int aud_strm_num);
int		file_set_video_stream(int vid_strm_num);
int		file_set_supic_stream(int sup_strm_num);
void	file_clear_param(void);
//void	calc_accm_audio_fPTS();

int		do_file_video();
int		do_file_audio();
int		do_file_drop();

////////////////////////////////////////////////////////////////////////
// Dummy function declarations
int 	ifunc1_file_parser_dummy();
int 	ifunc2_file_parser_dummy(int a1 __attribute__((unused)));
int 	ifunc3_file_parser_dummy(UINT32* a1 __attribute__((unused)));
int 	ifunc4_file_parser_dummy(int a1 __attribute__((unused)), UINT32* a2 __attribute__((unused)));
int		ifunc5_file_parser_dummy(BYTE* a1 __attribute__((unused)), UINT32 a2 __attribute__((unused)));

void	vfunc1_file_parser_dummy();
UINT32	u32func1_file_parser_dummy(UINT32 a1 __attribute__((unused)));
UINT32	u32func2_file_parser_dummy(int a1 __attribute__((unused)));
UINT32	u32func3_file_parser_dummy();

int		(*file_restruct_sync_table)();
int		(*file_preparser)(BYTE*, UINT32);
int		(*file_get_next_sync)(int, UINT32*);
UINT32	(*file_set_goto)(UINT32);
UINT32	(*file_ready_to_jump)(int);
UINT32  file_ready_to_resume();
int		(*file_set_fast)(int);
int		(*file_set_slow)(int);
void	(*file_reset_parser)();
UINT32	(*file_support_tricky_play)();
UINT32	(*file_goto_next_frame)();

#ifdef SUPPORT_FILE_CHAPTER
UINT32  (*file_get_num_of_chapter)();
UINT32  (*file_set_chapter)( UINT32 );
#endif

#ifdef SUPPORT_QUICKTIME
int  (*file_set_subp_status)(int);
#endif //SUPPORT_QUICKTIME

int		(*file_init_audio_stream)(int);
int		(*file_init_video_stream)(int);
int		(*file_init_supic_stream)(int);

#ifdef SUPPORT_MPG_FILE_PARSER
int Is_MPG_file(BYTE *pSrcPtr, UINT32 bufsize);
int doMPG_PreParser(BYTE *srcptr, INT32 bufsize);
int doCDXA_PreParser(BYTE *srcptr, INT32 bufsize);
#endif	// SUPPORT_MPG_FILE_PARSER

UINT32 FS_Get_File_Position();
void do_avi_audio_sync();
int file_get_show_time();
void do_adpcm_align();
UINT32 GET_MP4_TIME();
INT64 GET_MP4_TIME_STC();
#if 0
int file_preparser_init(UINT32 msf, UINT32 len, UINT32 mode);

UINT32	file_set_aud_stream(int aud_strm_num);
UINT32	file_set_vid_stream(int vid_strm_num);
UINT32	file_set_sup_stream(int sup_strm_num);

ifunc	file_preparser;
ifunc	file_is_errored;
ifunc	file_clear_error;
ifunc	file_reset_buffer;
ifunc	file_sync_audio_buffer;
ifunc2	file_set_audio_fPTS;
ifunc2	file_set_goto;
ifunc	file_set_goto_next_frame;
ifunc2	file_fast_get_next_I;
ifunc	avi_error_get_next_I;
ifunc2	file_set_fast;
ifunc2	file_set_slow;
#endif

#endif	// __FILE_IF_H__
