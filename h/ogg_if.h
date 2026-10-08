#ifndef OGG_IF_H
#define OGG_IF_H

#ifdef	OGGEXTERN_HERE
#define	OGGEXTERN
#else
#define	OGGEXTERN		extern
#endif

//ogg header data
OGGEXTERN	BYTE	ogg_hdr_type_flag;  //5
OGGEXTERN	UINT64	ogg_granule_pos;    //6-13
OGGEXTERN	UINT32	ogg_stream_ser_no;  //14-17
OGGEXTERN	UINT32	ogg_page_seq_no;    //18-21
OGGEXTERN	UINT32	ogg_page_chksum;    //22-25
OGGEXTERN	BYTE	ogg_page_segs;      //26

// file parser
UINT32	Is_OGG_file(BYTE* srcptr, UINT32 bufsize);
UINT32  ogg_support_tricky_play();
UINT32  ogg_set_goto(UINT32 goto_time);
int     ogg_init_audio_stream(int aud_strm_num);
int     initOGGParam();
int     ogg_get_next_I(int speed, UINT32* p_frm_offset);
UINT32  ogg_ready_to_jump(int speed);
int     ogg_find_sync_word(BYTE** srcptr, UINT32 bufsize);
void    ogg_clr_bufparam();
int     ogg_set_fast(int avs);
int     ogg_set_slow(int avs);
void    ogg_set_jump_packet(UINT32 _bitrate);

//ogg parser
int     doOGGPreParser(BYTE *srcptr, INT32 bufsize);
int     doOGGSync();
int     doOGGHeader();
int     doOGGFillHeader();
int     doOGGFillSegTB();
int     doOGGFillPayload();
int     doOGGFillAudio();
int     doOGGDropPayload();

#ifdef DSP_DEBUG_MODE //Parse OGG Header on PC, and dump bitsream to dsp directly.
int     doOGGDebugDump();
#endif

UINT32  GET_OGG_TIME();
#ifdef OGG_DBG_DUMP_DATA
void    dbg_dump_data(BYTE dump_byte);
#endif

extern  UINT32	l2msf(UINT32);


#endif //#ifndef OGG_IF_H

