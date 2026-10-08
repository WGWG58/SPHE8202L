#ifndef DIVX6_IF_H
#define DIVX6_IF_H


#include "stc.h"
#include "avi_type.h"
#include "divx6_type.h"

/////////////////////////
// DivX 6
/////////////////////////

//////////////////////////////////////////////////////////////////////
// Constrain Defines  //kevinmonkey where should I place these?
#define DIVX6_MAX_SUPFRAME_NUM      (200)
//if DIVX6_SUPFRAME_BUFFER_SIZE is set to only two, we can't guarantee that 
//there is enough bits for do_time and do_header
#define DIVX6_SUPFRAME_BUFFER_SIZE   (4)    
//when dynamic loading supframe data while menu playback, load at most 
//DIVX6_REQUEST_SUPFRAME_NUM number of button one time to avoid too long operating lag
#define DIVX6_REQUEST_SUPFRAME_NUM    (1)    
//menu sup don't need index,use it as file bit stream buffer
#define DIVX6_LOAD_SUPFRAME_FILE_BUF  (AVISUPIDX_START) 

#ifdef DIVX6_REDUCE_STACK_USAGE
#define DIVX6_WORKING_MEMORY_LOAD_SUP  (DIVX6_LOAD_SUPFRAME_FILE_BUF + DIVX6_SUPFRAME_BUFFER_SIZE*1024)
#define DIVX6_WORKING_MEMORY_SUP_SCALE (DIVX6_WORKING_MEMORY_LOAD_SUP + 1*1024)
#endif

#define AUDIO_CHANGE_DELAY_SEC  (3)
#define AUDIO_CHANGE_DELAY      (90000*AUDIO_CHANGE_DELAY_SEC)   // delay audio track change for 5 sec
//////////////////////////////////////////////////////////////////////

// Function Declarations
//////////////////////////////////////////////////////////////////////
// Initialize
UINT32	initDIVX6Param();
int		divx6_InitAVIParam();
// This function is called everytime the menu repeats or plays the first time
// External use only
UINT32	divx6_menu_init_start();
// This function is used by the navigator to calculate the menu play information
// Internal use only

//////////////////////////////////////////////////////////////////////
// Set functions
int		divx6_set_default_audio(UINT32 uAudioTrackID);
int		divx6_set_default_sup(UINT32 uSupTrackID);
UINT32	divx6_set_title_audio(UINT32 id, UINT32 audio_track);
UINT32	divx6_set_title_subpic(UINT32 id, UINT32 subpic_track);

//////////////////////////////////////////////////////////////////////
// Main functions
int		do_divx6_preparse(BYTE *srcptr, INT32 bufsize);
// main divx 6 navigator
// External use only
int do_divx6_navigator(void);
int do_divx6_navigator2(void);

//////////////////////////////////////////////////////////////////////
// Dispatch memory
UINT32	divx6_dispatch_menu_struct_memory(UINT32 memory_size);
UINT32	divx6_dispatch_id_table_memory(UINT32 id_entries);
UINT32	divx6_dispatch_menu_object_memory(UINT32 memory_size);

//////////////////////////////////////////////////////////////////////
// Reset functions
void divx6_reset_for_riff_change();
void divx6_reset_for_scene_change();
inline void divx6_reset_title_key_frame_table();
int		divx6_reset_sup_frame_table();

//////////////////////////////////////////////////////////////////////
// Execute Actions
UINT32	divx6_get_action_list(UINT32 action_id);
UINT32	divx6_get_action_list_length(UINT32	action_ptr);
UINT32	divx6_execute_action();
UINT32	divx6_execute_subtitle_select_action(UINT32 action_ptr, UINT32 action_size);
UINT32	divx6_execute_audio_select_action(UINT32 action_ptr, UINT32 action_size);
UINT32	divx6_execute_play_action(UINT32 action_ptr, UINT32 action_size);
UINT32	divx6_execute_return_to_play_action(UINT32 action_ptr, UINT32 action_size);
UINT32	divx6_execute_menu_transition_action(UINT32 action_ptr, UINT32 action_size);
UINT32	divx6_execute_button_transition_action(UINT32 action_ptr, UINT32 action_size);

//////////////////////////////////////////////////////////////////////
// Parser
int		divx6_parse_menu(void);
UINT32	divx6_is_parent(FOURCC parent_type);
UINT32	divx6_skipBitstream(INT32 bufsize, UINT32 byteCount);
UINT32	divx6_getField_Return(int byteCount, UINT32 *pResult);
UINT32	divx6_insert_id(UINT32 object_id, UINT32 object_offset);
UINT32	divx6_insert_key_frame(UINT32 key_frame_type, UINT32 start_frame_number, UINT32 end_frame_number);
UINT32	divx6_insert_lgmn_id(UINT32 lgmn_id);
UINT32	divx6_insert_title(UINT32 new_title_id, UINT32 new_audio_id, UINT32 new_subpic_id);
UINT32	divx6_build_id_table();
int		divx6_doAVIPreParseTitle();

//////////////////////////////////////////////////////////////////////
// Callback check
int divx6_ShowOverlay(UINT32 iOverlayID);

//////////////////////////////////////////////////////////////////////
// Chapter
void    divx6_SetChapterParameter(UINT32 uVideoStartFrame);

//////////////////////////////////////////////////////////////////////
// Access functions
UINT32	divx6_report_id(UINT32 object_id, UINT32 object_offset);
UINT32	divx6_lookup_offset_exhaust(UINT32 object_id,UINT32 uPresumedType);
int		divx6_CheckFileResume(void);

UINT32	divx6_load_menu(UINT32 uID);
UINT32	divx6_load_media_object(UINT32 uID);
UINT32	divx6_load_title_key_frames(UINT32 title_id);
int		divx6_LoadBMEN(UINT32 uID);
int		divx6_LoadSupFrameEntry(UINT32 uMediaSourceID);
int divx6_LoadSupFrameData2(UINT32 uIndex,UINT32 uMaxLoadingNumber);

UINT32	divx6_lookup_offset(UINT32 object_id,UINT32 uPresumedType);
FOURCC	divx6_lookup_object(UINT32 object_id,UINT32 uPresumedType);
UINT32	divx6_lookup_chapter(UINT32 chapter_number, DivXChapterTable *chapter);
UINT32	divx6_lookup_title_audio(UINT32 id);
UINT32	divx6_lookup_title_subpic(UINT32 id);
UINT32	divx6_menu_key_frame(UINT32	frame_number);
UINT32	divx6_title_key_frame(UINT32 frame_number);
UINT32	divx6_check_chapter(UINT32 frame_number);
//////////////////////////////////////////////////////////////////////
// Subpicture resize
int		do_avi_sup_body_buffer();
void	divx6_set_sup_alignment(UINT32 on_off);
int		do_avi_sup_scale();

//////////////////////////////////////////////////////////////////////
// Audio/Subpicture track information
UINT8	divx6_get_track_info(UINT8 track_type, UINT8 track_number);
void	divx6_display_audio_track(UINT8 aud_strm_num);
void	divx6_display_subpic_track(UINT8 sup_strm_num);
UINT8	convert_audio_type_to_string(char* audio_type);
UINT8	convert_subpic_type_to_string(char* subpic_type);
UINT8	convert_iso639_to_string(char* stream_info);

//////////////////////////////////////////////////////////////////////
// Utility functions
FOURCC	divx6_swap_fourcc(FOURCC normal_fourcc);
FOURCC	divx6_reverse_fourcc(FOURCC normal_fourcc);
void	divx6_print_id_table();
void	divx6_print_menu_key_frame_table();
void	divx6_print_title_key_frame_table();
void	divx6_print_subpic_info();
void	divx6_print_lgmn_id_table();
int		divx6_PrintSupFrameTable(UINT32 uEntryNum);
void	printTAB(int iNum);
void	divx6_wchar_to_char(char *data, char *dest, UINT32 size);

#endif
