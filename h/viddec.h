#ifndef	__VIDDEC_H
#define	__VIDDEC_H

#include "types.h"

#ifndef	EXTERN
#define	EXTERN	extern
#endif

/*
** sequence_info
*/
typedef	struct {
    UINT16  horizontal_size_value;
    UINT16  vertical_size_value;
    UINT32  bit_rate_value;                     // bit_rate_extension
    UINT32  vbv_buffer_size_value;              // vbv_buffer_size_extension
    UINT8   mpeg2_flag;                         // 
    UINT8   constrained_parameters_flag;        //
    UINT8   aspect_ratio_information;
    UINT8   frame_rate_code;
	// The following is for MP4 only.    
    UINT8   mp4_type;
	UINT16	vld_pkt_hdr;
	UINT16	vld_vol_hdr;
	UINT16	vld_vop_hdr;   
	UINT16	vld_gob_num;	
	UINT16	invq_vol_hdr;		    
} t_seq_info;


EXTERN	t_seq_info	seq_info;

EXTERN	UINT8		back_wait_copy;
EXTERN	UINT16		back_field_cntr;

// this variable is used by kernel, move it out from SUPPORT_SLOWBACKWARD
EXTERN	UINT8		back_st;

#ifdef  SUPPORT_SLOWBACKWARD
//
// SLOW_BACKWARD
EXTERN	UINT8		back_finished;
EXTERN	UINT8		back_vobu_cntr;         // 
EXTERN	UINT8		back_vobu_ref_cntr;
EXTERN	INT8		back_cntr;
EXTERN	INT8		back_cntr_all;          // 
#define	PICIF	72
EXTERN	UINT8		picif_cntr;
EXTERN	UINT8		picif[PICIF];
#endif


// option
#define	PIC_RESET_VIDEO	(1<<7)
#define	PIC_VALID	(1<<6)
#define PIC_HLEXIST	(1<<5)
#define	PIC_FIRST	(1<<4)
#define PIC_MPEG4	(1<<3)
#define	PIC_MPEG2	(1<<2)
#define	PIC_CHK_DTS	(1<<1)
#define	PIC_CHK_PTS	(1<<0)

// mpeg2 flag
#define ISO_MPEG2	(1<<0)
#define ISO_MPEG4	(1<<1)

//
// LINE21
// see DVD spec. part 3., 5.4.1.4
//
#define	LINE21_SIZE	128
EXTERN	INT8    line21_dumping;
EXTERN	INT8    line21_decoding;
EXTERN	UINT8   line21_data_rp;
EXTERN	UINT8   line21_data_wp;
EXTERN	UINT8   line21_data[3*LINE21_SIZE];	// 128-fields line21 buffers

// dump
EXTERN	UINT8   line21_d[12];		// 4-byte parsing line21 buffers
EXTERN	UINT8   line21_dump_num;	// l21 dump 
EXTERN	UINT8   line21_dump_cnt;	// l21 dump pointer
EXTERN	INT8    line21_f;
EXTERN	UINT8   line21_flag;

// decode
EXTERN	UINT8   line21_now;		// flag to send L21

// 
#define	VPP_PAUSE_AUTO	0
#define	VPP_PAUSE_FRAME	1
#define	VPP_PAUSE_FIELD	2
EXTERN	UINT8   vpp_pause_operation;

#define	ext0_progressive_frame(x)	((x) & RF_CODING_EXT0_PROGRESSIVE_FRAME)
#define	ext0_repeat_first_field(x)	((x) & RF_CODING_EXT0_REPEAT_FIRST_FIELD)
#define	ext0_top_field_first(x)		((x) & RF_CODING_EXT0_TOP_FIELD_FIRST)
#define	ext0_second_field(x)		((x) & RF_CODING_EXT0_SECOND_FIELD)

EXTERN	UINT8   SML_CNTR;
EXTERN	UINT8   SML_CNTR_NOW;

//
//
//
#define	avd_get_decode_mode()	(mode_decode)

#define	get_disbuf()    	get_disbuf_now()

#define	viddec_terminate()	(regs0->vld_ctrl=1)

#define	viddec_block_sw(n)	(regs0->agdc_mon_ubound = 1|((n)<<1))
#define	viddec_block_hw()	(regs0->agdc_mon_ubound = 0)
#define	viddec_block_on()	viddec_block_sw(1)
#define	viddec_block_off()	viddec_block_sw(0)

int	get_disbuf_now();
int	get_disbuf_set();
void	set_disbuf(int);
void	set_disbuf_now(int);
int	wait_disbuf_sync(void);

void	init_video_decoder();
void	reset_video_decoder();
int	wait_decode_finish(int timeout);

void	setup_sequence_info(t_seq_info *p);
void	save_sequence_info(t_seq_info *d);
//void	copy_sequence_info(t_seq_info *d, t_seq_info *s);
#define copy_sequence_info(d, s)    memcpy((void *)(d), (void *)(s), sizeof (t_seq_info))

void	resync_picture_state(void);

#define	reset_viddec_pause_flag()	(viddec_paused=0)
#define	is_viddec_paused()		(viddec_paused)

#endif

