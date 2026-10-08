#ifndef DIVX6_TYPE_H
#define DIVX6_TYPE_H

#include "stc.h"
#include "avi_type.h"
#include "config.h"

// Stores all the DivX menu structure's object ID's
typedef struct
{
	UINT32	menu_obj_id;
	UINT32	menu_obj_offset;
} DivXIDTable;

// Stores the chapter information
typedef struct
{
	UINT32	chap_video_start_frame;
	UINT32	chap_video_end_frame;
} DivXChapterTable;

// Stores the total titles for this file
typedef struct
{
	UINT32	title_id;
	UINT32	audio_track_id;
	UINT32	subtitle_track_id;
	UINT32	resume_video_frame;
} DivXTitleTable;

// Stores the language object ID's for this file
typedef struct
{
	UINT32	menu_obj_id;
} DivXLanguageTable;

// Stores the language and type of audio or subpic tracks
typedef struct
{
	char	language_tag[20];
	char	type_tag[35];
} DivXTrackInfoTable;

typedef struct
{
	FOURCC	FourCC;
	INT32	ChunkSize;
	INT32	ObjectID;
} DivXBasicType;

typedef struct
{
    UINT32  uSize;
    UINT32	uType;
//    char    sType[4];
    UINT32	uLeftToParse;
    //uLeftToParse stores the progress of atom parsing
} DivXAtom;

#define MAX_NESTED_LEVEL                10    //maximun nested level for stack size restriction
typedef struct
{
    UINT32		total_file_size;
    UINT32		parsed_byte;
    DivXAtom    aParsingStack[MAX_NESTED_LEVEL]; //may be freed to after parsing since it's not used then
    int     	iStackPtr;  //storing nested level of the stack while parsing. when empty, 
                       		//it takes the value -1
} DivXParser;

typedef struct
{
	UINT32	uObjectID;
	UINT32	uBackgroundVideoID;
	UINT32	uBackgroundAudioID;
	UINT32	uStartingMenuItemID;
	UINT32	uEnterAction;
	UINT32	uExitAction;
	UINT32	uMenuTypeLength;
	char	uMenuTypeString[40];
} divx6_tWMENTable;

//kevinmonkey for temp highlight implementation
typedef struct tDivX6_SupFrame
{
    UINT32  uObjectID;
    UINT32  uFileOffset;
    union
    {
        UINT32  uSupBufferPointer;    
        UINT32  uMEDTMatchingField;
    }param;
    
}divX6_tSupFrame;

typedef struct tDivx6_ButtonMenuTable
{
    UINT32  uObjectID;
    UINT32  uOverlayID;
    UINT32  uUpAction;
    UINT32  uDownAction;
    UINT32  uLeftAction;
    UINT32  uRightAction;
    UINT32  uSelectAction;
}divx6_tBMENTable;

//kevinmonkey 050728 need this structure when trying to dump subpicture directly
typedef struct  {
    int (*do_sup)();                // 00~03

    UINT32  PTS_sup_new;            // 04~07
    UINT32  spd_pts;                // 08~0B next PTS
    UINT32  spd_pts_stop;           // 

    UINT32  svcd_sup_timecmd;       // 0C~0F (SVCD)

    UINT16  spd_decode_hdr_ptr;     // 10~11 SPD header for decoding
    UINT16  spd_decoded_hdr_ptr;    // 12~13 SPD header (decoded)
    UINT16  spd_dump_hdr_ptr;       // 14~15 SPD header for parsing

    UINT16  spd_dcsq_ptr;           // SPD DECODE pointer (sbv_fetch())
    UINT16  spd_dcsq_ptr_now;       // SPD DECODE pointer of current DCSQ
    UINT16  spd_dcsq_ptr_next;      // SPD DECODE pointer to next DCSQ 

    UINT16  sup_start;              // 
    UINT16  sup_dumpcnt;            // 
    UINT16  sup_writeptr;           //

    UINT16  sup_freespace;          // SPD buffer-free
    UINT16  sup_freespace_return;   // scheduled calculated return free-space of SPD
    UINT16  sup_freespace_return2;  // scheduled actual return free-space of SPD

    UINT16  supya;                  // sub-picture SDRAM buffer start row
    UINT16  supye;                  // sub-picture SDRAM buffer end row

    INT16   sup_offset_y;           // Display extra vertical offset

    UINT16  sup_tlx,                // Bitmap region size window
            sup_brx;                // 
    UINT16  sup_tly,                //
            sup_bry;                //

    UINT16  sup_cmd_addr;           // SPH hardware command address (DVD only)

    UINT16  sup_tlink,              // SPH bitmap top-field address
            sup_blink;              // SPH bitmap bottm-field address

    UINT8   sup_link_changed;
    UINT16  sup_empty;
    UINT16  sup_empty2;
    UINT16  sup_tlink_n, sup_blink_n;

    UINT16  sup_hl0_color;
    UINT16  sup_hl0_contr;

    UINT16  sup_hl_tlx[2];
    UINT16  sup_hl_brx[2];
    UINT16  sup_hl_tly[2];
    UINT16  sup_hl_bry[2];
#if 0
    UINT16  sup_hl0_tlx, sup_hl0_brx;
    UINT16  sup_hl0_tly, sup_hl0_bry;
    UINT16  sup_hl1_tlx, sup_hl1_brx;
    UINT16  sup_hl1_tly, sup_hl1_bry;
#endif

    // DVD
    UINT16  sup_pxcd;
    UINT16  sup_pxcd_len;
    INT8    sup_pxcd_offset;

    BYTE    sup_buf[4];
    BYTE    sup_buf_cnt;

    UINT16   sup_state;
} t_supvar;
//extern t_supvar    *supnow;

//////////////////////////////////////////////////////////////////////////////////
typedef	struct	{
	UINT8	CB, CR, Y, BL;
} t_CLUTv1;     

typedef struct {
    UINT16  TLY, BRY, TLX, BRX;
} t_SUP_svcd_rgn;

typedef	struct 
{
	t_CLUTv1	CLUT[16];	// 0~63
	
	UINT16	TLINK;		// 0
	UINT16	BLINK;		// 2
	UINT16	PXCD;		// 4
	UINT16	ORG_START_LINE;	// 6
	UINT16	NEW_START_LINE;	// 8
	UINT16	TL_Y;		// 10
	UINT16	BR_Y;		// 12
	UINT16	TL_X;		// 14
	UINT16	BR_X;		// 16
	UINT16	PR_PALETTE;	// 18
	UINT16	PR_CONTRAST;	// 20
	UINT16	HL_TL_Y;	// 22
	UINT16	HL_BR_Y;	// 24
	UINT16	HL_TL_X;	// 26
	UINT16	HL_BR_X;	// 28
	UINT16	HL_PALETTE;	// 30
	UINT16	HL_CONTRAST;	// 32
} t_SUP_HDR_dvd_v1;

//
// t_SUP_HDR_svcd_v1
//
// SVCD/CVD format	(100-byte)
//
typedef	struct
{
	t_CLUTv1	CLUT[3][4];         // 3*16B
	UINT16		TLINK;	            // 
	UINT16		BLINK;              //
	UINT16		ORG_START_LINE;	
	UINT16		NEW_START_LINE;	
        t_SUP_svcd_rgn  region[3];          // 0: primary, 1:hl#0, 2:hl#1
} t_SUP_HDR_svcd_v1;

typedef	struct
{
	// hardware register table
	union {
#ifdef DVD728
		t_SUP_HDR_svcd_v1	svcd;
		t_SUP_HDR_dvd_v1	dvd;
#else
		t_SUP_HDR_svcd		svcd;
		t_SUP_HDR_dvd		dvd;
#endif
	} reg;			// 100
	
	// sub-picture decoder internal variables.
        // 23B
	UINT32	pts;		// 4 SPH command decode PTS
	UINT32	next_pts;	// 4 next SPU pts (if next SPU exist)
	UINT32	stop_pts;	// 4 STOP pts
	UINT16	spu_sa;		// 2 SPH start address (not header)
	UINT16	dcsqt_sa;	// 2 DCSQ start address
	UINT16	next;		// 2 next SPU
	UINT16	sup_size;	// 2 bytes used in this SPU
	UINT8	SPU_TYPE;	// 1 60
	UINT8   SPU_SML_CNTR;	// 1 61
	UINT8   SUP_STATE;	// 1 62
} t_SUP_REGION;

typedef struct
{
	SUPBITMAPHEADER		supheader;
	
	UINT32	pixel;
	UINT32	bit;
	UINT32	color;

	UINT32	sbuf;
	UINT32	top_sbuf;
	UINT32	btm_sbuf;

	UINT32	initial_sup_offset;

    int		top_sp_p;
    int		btm_sp_p;
	int		last_line_sp_p;
	
	UINT32	bit_count;
	UINT32	top_bit_count;
	UINT32	btm_bit_count;

	UINT32	read_top_field;
	UINT32	write_top_field;
	UINT32	pixel_count;
	
	int		px_diff;
	int		px_count;
	int		px_scale_diff;
	UINT32	need_to_insert_px;
	UINT32	need_to_remove_px;

	int		ln_diff;
	int		ln_count;
	int		ln_scale_diff;

	UINT32	skip_line;

	UINT32	write_half_byte;
	UINT32	top_write_half_byte;
	UINT32	btm_write_half_byte;

	UINT32	read_half_byte;
	UINT32	top_read_half_byte;
	UINT32	btm_read_half_byte;

	UINT32	new_read_half_byte;

	UINT32	new_chunk;
	UINT32	total_line;
	UINT32	total_width;
	UINT32	j;
	
	UINT32	lines_deleted;

    int		last_line_top_fld;
	
	int		pixels_inserted;
	int		pixels_inserted_max;
	int		lines_inserted_max;
	
    UINT32  line_type_count;
    UINT32  line_type;                              // 0=initial, 1=empty line, 2=non empty line
	
	UINT32	pic_width;
	UINT32	pic_height;
	UINT32	pic_width_scaled;
	UINT32	pic_height_scaled;
	UINT32	tv_width;
	UINT32	tv_height;
	UINT32	nw;
	UINT32	HEXP_value;
	UINT32	VFAC_value;
	UINT32	h_center_offset;
	
	t_SUP_REGION      *p;
} avi_sup_scale_struct;


////////////////////////////////////////////////////////////////////////////////////////




typedef int (*ifuncDivX6P)(void);//(QTPARSER *);

//IR command macro
#define DIVX6_NAV_IR_VOID		(0)
#define DIVX6_NAV_IR_LEFT		(1)
#define DIVX6_NAV_IR_RIGHT	    (2)
#define DIVX6_NAV_IR_UP		    (3)
#define DIVX6_NAV_IR_DOWN		(4)
#define DIVX6_NAV_IR_SELECT	    (6)

#define DIVX6_OFFSET_MASK	0x7FFFF
#define	DIVX6_TYPE_MASK		0xF8000000
#define DIVX6_MENU			(1 << 27)
#define DIVX6_LGMN			(2 << 27)
#define DIVX6_WMEN			(3 << 27)
#define DIVX6_BMEN			(4 << 27)
#define DIVX6_MREC			(5 << 27)
#define DIVX6_PLAY			(6 << 27)
#define DIVX6_PLY0			(7 << 27)
#define DIVX6_MNTX			(8 << 27)
#define DIVX6_BNTX			(9 << 27)
#define DIVX6_MDIA			(10 << 27)
#define DIVX6_MEDS			(11 << 27)
#define DIVX6_MEDT			(12 << 27)
#define DIVX6_ACTN			(13 << 27)
#define DIVX6_STAC			(14 << 27)
#define DIVX6_ASAC			(15 << 27)
#define DIVX6_MNTK			(16 << 27)
#define DIVX6_TITL			(17 << 27)
#define DIVX6_CHAP			(18 << 27)
#define DIVX6_TRTB			(19 << 27)
#define DIVX6_TRLK			(20 << 27)
#define DIVX6_TRAN			(21 << 27)
#define DIVX6_NONE			(0xF8 << 27)

#define DIVX6_MENU_FLAG		(1 <<  1)
#define DIVX6_LGMN_FLAG		(1 <<  2)
#define DIVX6_WMEN_FLAG		(1 <<  3)
#define DIVX6_BMEN_FLAG		(1 <<  4)
#define DIVX6_MREC_FLAG		(1 <<  5)
#define DIVX6_PLAY_FLAG		(1 <<  6)
#define DIVX6_PLY0_FLAG		(1 <<  7)
#define DIVX6_MNTX_FLAG		(1 <<  8)
#define DIVX6_BNTX_FLAG		(1 <<  9)
#define DIVX6_MDIA_FLAG		(1 << 10)
#define DIVX6_MEDS_FLAG		(1 << 11)
#define DIVX6_MEDT_FLAG		(1 << 12)
#define DIVX6_ACTN_FLAG		(1 << 13)
#define DIVX6_STAC_FLAG		(1 << 14)
#define DIVX6_ASAC_FLAG		(1 << 15)
#define DIVX6_MNTK_FLAG		(1 << 16)
#define DIVX6_TITL_FLAG		(1 << 17)
#define DIVX6_CHAP_FLAG		(1 << 18)
#define DIVX6_TRTB_FLAG		(1 << 19)
#define DIVX6_TRLK_FLAG		(1 << 20)
#define DIVX6_TRAN_FLAG		(1 << 21)
#define DIVX6_ALL_FLAG		(0xFFFFFFFF)

//Event macro
#define DIVX6_IR_EVENT          (0x1000)
#define DIVX6_PLAYBACK_EVENT    (0x2000)
#define DIVX6_ACTION_REQUEST    (0x2000)

#define Divx6GetEventType(a)    (a & 0xF000)
#define Divx6GetEventContent(a) (a & 0x0FFF)

#define DIVX6_EVENT_MNTX            (0x0001)
#define DIVX6_EVENT_BNTX            (0x0002)
#define DIVX6_EVENT_NO_EVENT        (0x0003)
#define DIVX6_EVENT_PLAY            (0x0004)
#define DIVX6_EVENT_STOP			(0x0005)
#define DIVX6_EVENT_PLAY_FINISHED   (0x0006)
#define DIVX6_EVENT_PLAY_INTERRUPTED (0x0007)
#define DIVX6_EVENT_RESUME_PLAY		(0x0008)
#define DIVX6_EVENT_FATAL_ERROR		(0x0009)

#define DIVX6_NAV_CMD_PLAY_MENU     	(0x0001)
#define DIVX6_NAV_CMD_PLAY_CHAP     	(0x0002)
#define DIVX6_NAV_CMD_NOP           	(0x0003)
#define DIVX6_NAV_CMD_EXE_ACTION    	(0x0004)
#define DIVX6_NAV_CMD_END_NAV       	(0x0005)
#define DIVX6_NAV_CMD_FALAL_ERROR		(0x0006)
#define DIVX6_NAV_CMD_EXCEED_PROFILE	(0x0007)
#define DIVX6_NAV_CMD_DRM_ERROR			(0x0008)



#define DIVX6_MENU_KEY_FRAME_TYPE		(0x0001)
#define DIVX6_TITLE_KEY_FRAME_TYPE		(0x0002)

#define DIVX6_SUCCESSFUL        (1)
#define DIVX6_ABORT_PARSING     (2)

#endif
