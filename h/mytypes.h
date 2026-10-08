#ifndef __MY_TYPES_H
#define __MY_TYPES_H

//
//	Picture Coding Extension
//
typedef union
{
	UINT16	para;
	struct {
		unsigned progressiveframe	: 1;	// D[0]
		unsigned chroma420type		: 1;	// D[1]
		unsigned repeatfirstfield	: 1;	// D[2]
		unsigned alterscan		: 1;	// D[3]
		unsigned intraVLCformat		: 1;	// D[4]
		unsigned Qscaletype		: 1;	// D[5]
		unsigned concealMotionVectors	: 1;	// D[6]
		unsigned framePredframeDCT	: 1;	// D[7]
		unsigned topfieldfirst		: 1;	// D[8]
		unsigned picture_struct		: 2;	// D[9:10]
		unsigned intraDCprecision	: 2;	// D[11:12]
		unsigned reserved		: 1;	// D[13]
		unsigned last_picture		: 1;	// D[14]
		unsigned second_field		: 1;	// D[15]
	} ext0_field;

	struct {
		unsigned framepic	: 1;	// D[0]
		unsigned forwardframe	: 1;	// D[1]
		unsigned reconstframe	: 2;	// D[2:3]
		unsigned fieldId	: 1;	// D[4]
	} ext1_field;
} PicCod_Ext;

//
//	MacroBlock
//
typedef union
{
	UINT16	para;
	struct {
		unsigned quant		: 1;	// D[0]
		unsigned motionforward	: 1;	// D[1]
		unsigned motionbackward	: 1;	// D[2]
		unsigned pattern	: 1;	// D[3]
		unsigned intra		: 1;	// D[4]
		unsigned spatialtemporal: 1;	// D[5]
		unsigned motiontype	: 2;	// D[6:7]
		unsigned DCTtype	: 1;	// D[8]
	} field;
} MBType;

typedef union
{
	UINT16	para;
	struct {
		unsigned tv_mode					: 1;	// D[0]
		unsigned p_scan						: 1;	// D[1]
		unsigned line_buf_disable			: 1;	// D[2]
		unsigned luma_v_inter_disable		: 1;	// D[3]
		unsigned chroma_v_inter_disable		: 1;	// D[4]
		unsigned game_mode					: 1;	// D[5]
		unsigned color_index_trans_mode		: 1;	// D[6]
		unsigned sdram_reorder_disable		: 1;	// D[7]
		unsigned quasi_inter				: 1;	// D[8]
		unsigned mem_map_mode				: 2;	// D[9:10]
		unsigned dithering666				: 1;	// D[11]
	} _vpp;
	
	struct {
		unsigned video_disable				: 1;	// D[0]
		unsigned source_pic_structure		: 1;	// D[1]
		unsigned single_field_display_mode	: 1;	// D[2]
		unsigned display_field_id			: 1;	// D[3]
		unsigned chroma_resampling_mode		: 2;	// D[4:5]
		unsigned initial_accumulator		: 9;	// D[6:14]
	} _ds;
	
	struct {
		unsigned deinterlace_enable			: 1;	// D[0]
		unsigned deflicker					: 1;	// D[1]
		unsigned dipconfig					: 4;	// D[2:5]
		unsigned half_Ref_Pix_mode			: 1;	// D[6]
		unsigned double_ref_pix_distance	: 1;	// D[7]
	} _dip_cfg;

	struct {
		unsigned mv_detect_threshold		: 7;	// D[0:6]
		unsigned reserved1					: 1;	// D[7]
		unsigned cross_fading_speed			: 7;	// D[8:14]
		unsigned reserved2					: 1;	// D[15]
	} _dip_param;
} DS_CFG;

#endif //__MY_TYPES_H
