#ifndef QT_IF_H
#define QT_IF_H

#include "avi_type.h"

#define QT_PRELOAD_AUDIOSAMPLESIZEDATA

//#define PRECISE_GOTO_TABLE
//////////////////////////////////////////////////////////////
// Externs
extern	UINT32	goto_table_valid_entries;

//////////////////////////////////////////////////////////////
// Defines
#define	QT_FAST_JUMP		1	// If fastforward speed > QT_FAST_JUMP, it'll trigger QT_set_goto
#define QT_READY_TO_JUMP	4
#define QT_PRINT_FILE_REJECT_MESSAGE


#define FCC_jpeg				mmioFOURCC('j', 'p', 'e', 'g')
#define FCC_JPEG				mmioFOURCC('J', 'P', 'E', 'G')
//////////////////////////////////////////////////////////////
// Preparser & Initialization
int		is_QT_file(UINT32 msf,UINT32 len, UINT32 bufsize);
void	QT_reset_parameters();
int		QT_PreParse(BYTE *srcptr, UINT32 bufsize);
void	QT_initialize_function_pointers();
void	QT_copy_to_track();

//////////////////////////////////////////////////////////////
// Memory dispatch
int		QT_DispatchChunkSizeTableMemory();
int		QT_DispatchAudioBufferMemory();
int		QT_DispatchGotoTableMemory();
int 	QT_DispatchAudioSizeMemory();
int		QT_DispatchAudioBufTracking();

void	QT_InitializeAudioSizeMemory();

//////////////////////////////////////////////////////////////
// Video, audio & subpic initialization
int		QT_init_video(int vid_strm_num);
int		QT_init_audio(int aud_strm_num);
int 	QT_init_supic(int sup_strm_num);

//////////////////////////////////////////////////////////////
// Build tables
int 	QT_FillChunkSizeTable();
int 	QT_FillGotoTable();
UINT32	QT_get_last_chunk_size(UINT32 media_type);
int		QT_get_next_chunk_size();

//////////////////////////////////////////////////////////////
// Normal playback
int		do_QT_movie_parser();

//////////////////////////////////////////////////////////////
// Tricky play
UINT32	QT_support_tricky_play();

UINT32	QT_pts_to_goto_index(UINT32 video_pts, UINT32 mode);
UINT32	QT_get_A_chunkSizeLeft(UINT32 goto_index, UINT32 video_first);

void	QT_get_sound_chunk_begin_sample(UINT32 chunk_number, UINT32* chunk_begin_end_sample);
void	QT_get_video_chunk_begin_sample(UINT32 chunk_number, UINT32* chunk_begin_end_sample);

UINT32	QT_ready_to_jump(int speed);
int		QT_get_next_I(int speed, UINT32* p_frm_offset);
UINT32	QT_set_goto(UINT32 goto_time);
UINT32	QT_set_goto_next_frame();

void 	QT_set_video_fPTS();

void 	QT_clr_bufparam();
void 	QT_clear_parameter();

void	QT_get_pts_to_sample(UINT32 pts, UINT32* sample_info);
UINT32	QT_get_sample_pts(UINT32 media_type, UINT32 sample_number);
UINT32	QT_pts_to_pts(UINT32 media_type, UINT32 from_pts);
UINT32	QT_peek_chunk_size(UINT32 index);
int		QT_sec_to_pts(UINT32 seconds, UINT32 target_media);

#ifdef SUPPORT_FILE_CHAPTER
UINT32  QT_get_num_of_chapter();
UINT32  QT_set_chapter( UINT32 chp_num );
#endif

//////////////////////////////////////////////////////////////
// double buffering
void	QT_FillAudioSizeMemory();
void	QT_SwitchAudioSizeMemory();
int		QT_get_next_audio_sample_size();
void	QT_reset_audio_size_double_buffer();
void	QT_SwitchAudioSizeMemory();

int		QT_check_video_buffer();
int		QT_check_audio_buffer();

void	QT_check_need_audio_size_data();

//////////////////////////////////////////////////////////////
// Exception handling
UINT32	QT_check_table_size_exception();

//////////////////////////////////////////////////////////////
// Utility functions
FOURCC	QT_to_fcc(const char* fcc_char);
UINT32	QT_get_total_sample(UINT8 media_type);
UINT32	QT_get_sample_rate();
void	PrintChunkSizeTable();
void	PrintGotoTable();

//////////////////////////////////////////////////////////////

#ifdef PRECISE_GOTO_TABLE
typedef struct
{
    UINT32	V_absoluteOffset;	//	1
    UINT32	IVpts;				//	2
    UINT32	V_chunkSizeLeft;	//	3

    UINT32	A_chunkSizeLeft;	//	4

    UINT16	V_chunkNumber;		//	5

    UINT16	A_chunkNumber;		//	6
    INT16	A_relativePts;		//	7
    UINT16	A_sampleNumber;		//	8
} GotoEntry;
#else
typedef struct
{
    UINT32	V_absoluteOffset;	//	1	ok
    UINT32	IVpts;				//	2	ok
    UINT32	V_chunkSizeLeft;	//	3	ok

	UINT32	A_absoluteOffset;	//	4	ok

    UINT32	V_chunkNumber;		//	5	ok
    UINT32	A_chunkNumber;		//	6	ok
    INT32	       A_relativePts;		//	7	ok
    UINT32	Filling;
    //UINT16	V_chunkNumber;		//	5	ok
    //UINT16	A_chunkNumber;		//	6	ok
    //INT16	A_relativePts;		//	7	ok
    //UINT16	Filling;
    UINT32	A_sampleNumber;		//	8	ok
} GotoEntry;
#endif
#endif
