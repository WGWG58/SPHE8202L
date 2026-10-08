#define MAX_BUF_NUM				5

//#define INIT_BUF_IDX			2
// Buffer
#define	BUFFER0					0
#define BUFFER1					1
#define BUFFER2					2
#define BUFFER3					3
#define BUFFER4					4

// Status
#define STATUS_DECODE			1
#define STATUS_DISPLAY			2
#define STATUS_DEINTERLACE		3
#define STATUS_FREE				4

// Type
#define TYPE_REF0				0
#define TYPE_REF1				1
#define TYPE_BDIR				2
#define TYPE_NONE				3

/*#define	P_BIDIR1_LUMA			4096
#define P_BIDIR1_LUMA_END       (P_BIDIR1_LUMA + LUMA_SIZE - 1)
#define P_BIDIR1_CHROMA			(P_BIDIR1_LUMA_END + 10)
#define P_BIDIR1_CHROMA_END		(P_BIDIR1_CHROMA + CHROMA_SIZE - 1)

#ifdef FIVE_BUFFER
#define	P_BIDIR2_LUMA			5120
#define P_BIDIR2_LUMA_END       (P_BIDIR2_LUMA + LUMA_SIZE - 1)
#define P_BIDIR2_CHROMA			(P_BIDIR2_LUMA_END + 10)
#define P_BIDIR2_CHROMA_END		(P_BIDIR2_CHROMA + CHROMA_SIZE - 1)
#endif*/

#define	FILL_LUMA_DARK		0x00000000      // safe for all mode
#define	FILL_LUMA_BLUE		0x28282828
#define	FILL_LUMA_LOW		0x40404040
#define	FILL_LUMA_HIGH		0xa0a0a0a0

#define	FILL_CHROMA_WHITE	0x80808080
#define	FILL_CHROMA_RED		0x9c209c20
#define	FILL_CHROMA_BLUE	0x7cc07cc0



void	update_n_frame_buf_anchor();
void	reset_n_frame_buf_mech();
void	reset_buffer_status_all();
void	reset_buffer_type_all();
void	update_buffer_ref(UINT32 new_ref_buffer);
void	set_display_anchor(UINT32 display_buffer);
void	update_vpp_anchor();
void	update_buffer_type();
void	reset_4th_buffer();
void	reset_5th_buffer();
UINT32	search_free_buffer(UINT32 new_coding_type);
void	set_buffer_status(UINT32 display_pic_id, UINT32 new_status);
void	set_exit_display_anc();
void	reset_display_anchor();
void	reset_nth_buffer(UINT32 buffer_number, UINT32 bitmask);
