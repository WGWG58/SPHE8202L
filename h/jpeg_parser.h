/**************************************************************************
 *                                                                        *
 *         Copyright (c) 2002 by Sunplus Technology Co., Ltd.             *
 *                                                                        *
 *  This software is copyrighted by and is the property of Sunplus        *
 *  Technology Co., Ltd. All rights are reserved by Sunplus Technology    *
 *  Co., Ltd. This software may only be used in accordance with the       *
 *  corresponding license agreement. Any unauthorized use, duplication,   *
 *  distribution, or disclosure of this software is expressly forbidden.  *
 *                                                                        *
 *  This Copyright notice MUST not be removed or modified without prior   *
 *  written consent of Sunplus Technology Co., Ltd.                       *
 *                                                                        *
 *  Sunplus Technology Co., Ltd. reserves the right to modify this        *
 *  software without notice.                                              *
 *                                                                        *
 *  Sunplus Technology Co., Ltd.                                          *
 *  19, Innovation First Road, Science-Based Industrial Park,             *
 *  Hsin-Chu, Taiwan, R.O.C.                                              *
 **************************************************************************/

#ifndef JPEG_PARSER_H
#define JPEG_PARSER_H

#include "global.h"
#include "stdlib.h"
#include "drv.h"

#include "memmap0.h"
#include "kinf.h"
#include "util.h"
#include "stc.h" 

#include "image.h"

#include "graph.h"
#include "memcfg.h"

#ifdef IC_8202L
#include "pic_if.h"
#endif

// support two decoding methods for progressive jpeg
// default is multiscan method
#define  ENABLE_TWO_PS_METHOD

//***************************************************************
// debug option
//***************************************************************			
//#define		JPEG_CHECKSUM 
#define		JPEG_ERROR_INFO
//#define		JPEG_PARSER_INFO
//#define		JPEG_HEADER_INFO


#define jpeg_error_print(s...) ((void)0)
#define jpeg_parser_print(s...) ((void)0)
#define jpeg_header_print(s...) ((void)0)

#ifdef JPEG_ERROR_INFO
#undef  jpeg_error_print
#define jpeg_error_print	printf_w
#endif

#ifdef JPEG_PARSER_INFO
#undef	jpeg_parser_print
#define jpeg_parser_print	printf_w
#endif

#ifdef JPEG_HEADER_INFO
#undef	jpeg_header_print
#define jpeg_header_print	printf_w
#endif

//***************************************************************
// jpeg_type_info 
//***************************************************************
enum{
    BASELINE_DCT = 0,
    EXTENDED_SEQUENTIAL_DCT,
    PROGRESSIVE_DCT,    
};

//***************************************************************
// jpeg_bug_info 
//***************************************************************
#define		BI_DEFAULT				(-1)
#define		BI_DECODE_OK			0
#define		BI_ERROR				1
#define		BI_SIZE_LOW				2
#define		BI_PS_SIZE_LOW			3
#define		BI_MS_SIZE_LOW			4
#define		BI_NON_SUPPORT			5
#define		BI_FETCH_ERROR			6

//***************************************************************
// Decode one frame state
//***************************************************************
#define		JPEG_END				0
#define		JPEG_ENTRANCE			1
#define		JPEG_FUNCTION_INIT		2
#define		JPEG_MCU_INIT			3
#define		JPEG_MCU_DECODE			4
#define		JPEG_HEADER_MNG			5
#define		JPEG_SCALE_MBLG			6
#define		JPEG_MCU_END			7
#define		JPEG_PD_INIT			8
#define		JPEG_ERROR				(-1)

//***************************************************************
// Multiscan state
//***************************************************************
#define		FIRST_SCAN				0
#define		REMAIN_SCAN				1
#define		JUMP_SOS				2

#define 	NULL 					((void *)0)

// API structure
typedef struct pd_structure
{
	UINT32 start_x;
	UINT32 start_y;
	UINT32 offset_x;
	UINT32 offset_y;
}pd_structure;
 
extern ifunc   do_jpeg;

//***************************************************************
// function prototype
//***************************************************************
INT32  __jpg_quick_init_params();
INT32  __jpg_init_params();																																									
INT32  jpg_decode_1frame();																																								
INT32  jpg_entrance();																																							
INT32  jpg_header();
INT32  jpg_function_init();																																								
INT32  jpg_pd_init();																																								
INT32  jpg_fetch_data();																																								
INT32  jpg_drop_data();
INT32  jpg_stop();
INT32  jpg_scale_ms();	

void   scale_y(UINT8* out, INT32 n, INT32 m);
void   scale_cbcr(UINT8* out, INT32 n, INT32 m);
void   scale_vertical(INT32 n, INT32 m);
																							
INT32  store_APP0();
INT32  store_DQT();																																								
INT32  store_SOFn();																																								
INT32  store_DHT();																																								
INT32  store_SOS();

#ifdef ENABLE_TWO_PS_METHOD
INT32  store_SOS_ps();
#endif //ENABLE_TWO_PS_METHOD

INT32  store_SOS_ms();																																								
INT32  store_DRI();
INT32  store_RDx();

INT32  decode_mcus_bs_init();
INT32  decode_mcus_bs();
INT32  decode_mcus_bs_end();

#ifdef ENABLE_TWO_PS_METHOD
INT32  decode_mcus_ps_init();
INT32  decode_mcus_interleave_ps();
INT32  decode_mcus_noninterleave_ps();
INT32  decode_mcus_ps_end();
#endif //ENABLE_TWO_PS_METHOD

INT32  decode_mcus_ms_init();
INT32  decode_mcus_interleave_ms();
INT32  decode_mcus_noninterleave_ms();
INT32  decode_mcus_ms_end();

void   dec_block_sequential(UINT32 component);

#ifdef ENABLE_TWO_PS_METHOD
void   dec_block_DC_first_ps(UINT32 component);
void   dec_block_DC_redefine_ps(UINT32 component);
void   dec_block_AC_first_ps(UINT32 component);
void   dec_block_AC_redefine_ps(UINT32 component);
#endif //ENABLE_TWO_PS_METHOD

void   dec_block_DC_first_ms(UINT32 component);
void   dec_block_DC_redefine_ms(UINT32 component);
void   dec_block_AC_first_ms(UINT32 component);
void   dec_block_AC_redefine_ms(UINT32 component);

void   skip_bits(UINT8 bits);
UINT16 get_bits_vlc(UINT8 bits);

void   graph_idct_8x8(UINT32 component);
void   graph_idct_1x1(UINT32 component);

#ifdef JPEG_CHECKSUM
void checksum(UINT16 *block);
void checksum_32(UINT32 *block);
#endif //JPEG_CHECKSUM

#ifdef  JPEG_HEADER_INFO
void   show_app0(void);
void   show_dqt(void);
void   show_sofn(void);
void   show_dht(void);
void   show_sos(void);
void   show_dri(void);
#endif

// API
INT32   jpg_setup_partial_decode(UINT32 do_partial_decode, pd_structure *ptr);
//INT32  jpg_setup_partial_decode_init();
INT32   jpg_setup_multiscan(UINT32 do_multiscan);
INT32   jpg_setup_scan_time(UINT32 time);
INT32   jpg_setup_bitstream_buffer(UINT8 *buf_add, UINT32 buf_size);
INT32   jpg_setup_working_buffer(UINT8 *buf_add, UINT32 buf_size, UINT32 min_size);
INT32   jpg_setup_decoding_framebuffer(UINT32 frame_num);
INT32   jpg_setup_default_huffman();
INT32   jpg_setup_display_box(UINT32 start_x, UINT32 start_y, UINT32 offset_x, UINT32 offset_y);
INT32   jpg_setup_max_mcus(UINT32 num);
INT32   jpg_setup_file_info(UINT32 msf, UINT32 len);
INT32   jpg_setup_display_start_coordinate(UINT32 width_offset, UINT32 height_offset, UINT32 set_center);
INT32   jpg_get_type();
INT32   jpg_get_downsample_rate();
INT32   jpg_get_actual_resoluation(UINT16 *w, UINT16 *h);
INT32 	jpg_get_sof_nf();
INT32   jpg_is_decoding_process();
//***************************************************************
// type define
//***************************************************************

typedef void (* dec_func)(UINT32 component);

//***************************************************************
// Extern Variable
//***************************************************************

// DQT
extern UINT8  dqt_Qk[4];	// only save DC value

// SOF
extern UINT32 sof_n;
extern UINT16 sof_Y;
extern UINT16 sof_X;
extern UINT8  sof_Nf;
extern UINT8  sof_Ci[3];
extern UINT8  sof_Hi[3];
extern UINT8  sof_Vi[3];
extern UINT8  sof_Tqi[3];

// DHT
extern UINT8  *DC_table;
extern UINT8  *AC_table;
extern UINT8  *AC_value;

// SOS
extern UINT8  sos_Ns;
extern UINT8  sos_Cs[3];
extern UINT8  sos_Td[3];
extern UINT8  sos_Ta[3];
extern UINT8  sos_Ss;
extern UINT8  sos_Se;
extern UINT8  sos_Ah;
extern UINT8  sos_Al;

// jpeg_state and state definitions
extern UINT32	jpeg_state, jpeg_state_next;
extern ifunc   do_jpeg;
extern ifunc   do_jpeg_backup, decode_mcus_init, decode_mcus , decode_mcus_end, jpg_scale;
extern dec_func dec_block;
extern dec_func graph_idct;

// check pic had been decoded or not
extern UINT32 pic_decode;

// fetch data
extern UINT8  *jpeg_buf_ptr;             // working pointer point to the start of bitstream buffer
extern UINT8  *jpeg_buf_end;             // working pointer point to the end of bitstream buffer
extern UINT32 jpeg_file_pos;             // current address of working file
extern UINT32 jpeg_file_size;

// a buffter to hold VLD value
extern UINT32 vld_buf;                   // 4-byte buffer for vld decoding
extern UINT32 last_bit;                  // available bits in 4-byte buffer
extern UINT32 LDC[3];                    // previous DC values(for IDPCM), [0]:Y  [1]:Cb  [2]:Cr
extern UINT32 jpeg_marker_size;          // header size
extern UINT32 eobrun;                    // runs of End-Of-Bands
extern UINT32 clear_buf;                 // reset 4-byte buffer, if 1
extern UINT32 write_to_buffer;           // write idct&iq result to frame buffe, if 1 

//  mcu control state
extern UINT32 mcu_start, mcu_end, mcu_total, mcu_dri_count, max_mcus, work_mcus;
extern UINT32 horizontal_mcu;            // number of horizontal mcus in one row of pic 
extern UINT32 vertical_mcu;              // number of vertical mcus in one column of pic 
extern UINT32 horizontal_mb_mcu;         // number of horizontal 2x2 blocks in one row of pic 
extern UINT32 horizontal_b_mcu;          // number of horizontal blocks in one row of pic
extern UINT32 sof_Hi_0, sof_Vi_0;        // number of horizontal or vertical block in one MB
extern UINT32 dri_remain;                // number of MB need to be decoded in one RDx
extern UINT32 cur_x, cur_y;              // working index of horizontal or vertical block in vld decoding

// for partial decode
extern UINT32 is_partial_decode;         // enable partial decode mode, if 1
extern UINT32 actual_x, actual_y;        // the start address and size of scaling pic stores in frame buffer
extern UINT32 actual_w, actual_h;
extern UINT32 set_actual_x, set_actual_y;        
extern UINT32 set_actual_w, set_actual_h;
extern UINT32 pd_top_x, pd_top_y;        // left-top and right-down coordinates in partial doecode
extern UINT32 pd_down_x, pd_down_y;
extern UINT32 *pd_mbl_info;

//  idct & iq
extern UINT32 *gbIDCTi, *gbIDCTo;        // input and output buffers are used for IDCT&IQ hardware

//  scalar
extern UINT16 *y_in;
extern UINT16 *cbcr_in;
extern UINT32 downsample_rate_w;         // down sample factor (1-8)
extern UINT32 downsample_rate_h;         // down sample factor (1-8)
extern UINT32 downsample_rate_w_2;       // down sample factor (1-8)
extern UINT32 downsample_rate_h_2;       // down sample factor (1-8)
extern UINT32 new_start_luma;            // start address offset from luma frame buffer to scaling pic
extern UINT32 new_start_chroma;          // start address offset from chroma frame buffer to scaling pic
extern UINT32 scale_b_x, scale_b_y;      // working index of horizontal or vertical block in scaling
extern INT32  scale_offset;              // row length during scaling buffer
extern UINT32 scale_width_luma, scale_height_luma;
extern UINT8  *luma_framebuf, *chroma_framebuf;

// progressive 
extern UINT8  *check_table;               // working pointer point to y, cb, or cr check table
extern UINT8  *y_check_table;             // point to y check table which records non-zero value and sign value
extern UINT8  *cb_check_table;            // point to cb check table which records non-zero value and sign value
extern UINT8  *cr_check_table;            // point to cr check table which records non-zero value and sign value

// mulitscan
extern UINT32 *ms_table_add;
extern UINT32 *ms_sos_add;
extern UINT32 *ms_last_bit;
extern UINT32 *ms_vld_buf;
extern UINT32 *ms_eobrun;
extern UINT8  *ms_sos_Ns;
extern UINT8  *ms_sos_Ss;
extern UINT8  *ms_sos_Se;
extern UINT8  *ms_sos_Ah;
extern UINT8  *ms_sos_Al;
extern UINT8  *ms_sos_Cs;
extern UINT8  *ms_sos_Td;
extern UINT8  *ms_sos_Ta;

extern UINT32 is_multiscan;              // enable multiscan mode, if 1
extern UINT32 cur_sos_run, num_sos_run, max_sos_run;
extern UINT16 *vld_add;                  // working pointer point to vld result 
extern UINT32 multiscan_state;           // working state in multiscan mode
extern UINT32 num_mbl;                   // number of MBL can be processed in one decoding cycle
extern UINT32 work_y;                    // working index of vertical block in vld

// bug information
extern INT32 jpeg_bug_info;

// for check sum
#ifdef JPEG_CHECKSUM
extern UINT32 checksum_value;
#endif

extern const UINT8 de_zig_zag_tab[64];

#endif
