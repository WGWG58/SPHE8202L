//
// FILE
// kern_def.h
//
// DESCRIPTION
// This file is to provide an definition used between kernel programs
// and upper software.  Don't place anything other than kernel
// definitions.
// Also always make sure this file is coherent with the kernel
// program.
//

#ifndef	KERNDEF_H
#define	KERNDEF_H

#include "types.h"

#include "cpu.h"
//swpong 2006 0530#include "framebuf.h"
#include "viddec.h"



// chip part number & version


// chipversion_flag
#define CHIP_8202E   (1<<0)  // 9992
#define CHIP_8202D   (1<<1)  // PS2.5



// for portable

// system-layer
#define KI_PCKTYPE_VOB              0
#define KI_PCKTYPE_AOB              1


#define KI_AU_STREAM_PCM            0xa0
#define KI_AU_STREAM_AC3            0x80
#define KI_AU_STREAM_DTS            0x88
#define KI_AU_STREAM_MPG            0xc0

#define KI_AU_TYPE_MASK             0xf8
#define KI_AU_MPG_MASK              0xe0
#define KI_AU_STREAM_MASK           0x07

#define		AUDIO_TIME_STAMP			0
#define		VIDEO_TIME_STAMP			1
#define		SUPIC_TIME_STAMP			2

#define		TIME_TYPE_DTS				PIC_CHK_DTS
#define		TIME_TYPE_PTS				PIC_CHK_PTS

#define		IS_DTS_TIME_STAMP(type)		(((type)&TIME_TYPE_DTS) == TIME_TYPE_DTS)
#define		IS_PTS_TIME_STAMP(type)		(((type)&TIME_TYPE_PTS) == TIME_TYPE_PTS)

// video information
#define		IS_SRC_MPEG1(opt)			((opt&(PIC_MPEG2|PIC_MPEG4)) == 0)
#define		IS_SRC_MPEG2(opt)			(opt&PIC_MPEG2)
#define		IS_SRC_MPEG4(opt)			(opt&PIC_MPEG4)

#define		IS_DEC_MPEG1()	    		((regs0->seq_ext&0x7)==0 || (regs0->seq_ext&0x7)==1) 
#define		IS_DEC_MPEG2()	    		((regs0->seq_ext&0x7)==2) 
#define		IS_DEC_MPEG4()	            ((regs0->seq_ext&0x7)==4 || (regs0->seq_ext&0x7)==5 || (regs0->seq_ext&0x7)==6)

extern UINT16	src_progressive_cnt;
#define		IS_SRC_PROGRESSIVE()	    (src_progressive_cnt==0)
#define		SET_SRC_PROGRESSIVE()	    (src_progressive_cnt=0)

// buffer control function and defines
#define	DVD_SYNC_MODE				0x0
#define	SIMPLE_SYNC_MODE			0x1

#define	AUDIO_FULL					0x0
#define	VIDEO_FULL					0x1
#define	SUPIC_FULL					0x2

// video decode option
#define	VID_NORMAL_DEC			0
#define	VID_SKIP_B				(1 << 0)
#define	VID_FLD_DEC				(1 << 1)
#define	VID_PEND_DEC			(1 << 2)
#define	VID_SKIP_P				(1 << 3)
#define	VID_DISABLE_AVSYNC		(1 << 4)
#define	VID_DISABLE_FRCTL		(1 << 5)
#define	VID_VFULL_DEC			(1 << 6)

#define	IS_VID_NORMAL_DEC()		(video_dec_opt == VID_NORMAL_DEC)
#define	IS_VID_SKIP_B()			((video_dec_opt&VID_SKIP_B) > 0)
#define	IS_VID_SKIP_P()			((video_dec_opt&VID_SKIP_P) > 0)
#define	IS_VID_FLD_DEC()		((video_dec_opt&VID_FLD_DEC) > 0)
#define	IS_VID_PEND_DEC()		((video_dec_opt&VID_PEND_DEC) > 0)
#define	IS_VID_DIS_AVSYNC()		((video_dec_opt&VID_DISABLE_AVSYNC) > 0)
#define	IS_VID_DIS_FRCTL()		((video_dec_opt&VID_DISABLE_FRCTL) > 0)
#define	IS_VID_VFULL_DEC()		((video_dec_opt&VID_VFULL_DEC) > 0)

#define	SET_VIDDEC_OPT(x)		(video_dec_opt = (x))
#define	GET_VIDDEC_OPT()		(video_dec_opt)


// frame rate control
#define FRCTL_MP2_ALWAYS_INTERLACED_FLAG		(1<<0)

// field decoding


//#ifdef	SUPPORT_MP4

// get_mp4_video_codec()
#define	MPEG4_ISO				0
#define	MPEG4_SHORT_HEADER		1
#define	MPEG4_DIVX_311			2
#define	MPEG4_DIVX_412			3
#define	MPEG4_DIVX_5			4
#define	MPEG4_XVID			    5

// video_property_flag
#define MPEG4_TYPE_FLAG			(1 << 0)	// MPEG-4
#define MPEG4_INTERLACED_FLAG	(1 << 1)	// Interlaced
#define MPEG4_SHORT_FLAG		(1 << 2)	// Short Header
#define MPEG4_GMC_FLAG			(1 << 3)	// Global Motion Compensation
#define MPEG4_QPEL_FLAG			(1 << 4)	// Quarter Pixel

#define IS_MPEG4_INTERLACED()	((video_property_flag&MPEG4_INTERLACED_FLAG) > 0)
#define IS_MPEG4_SHORT_HEADER()	((video_property_flag&MPEG4_SHORT_FLAG) > 0)
#define IS_MPEG4_GMC()			((video_property_flag&MPEG4_GMC_FLAG) > 0)
#define IS_MPEG4_QPEL()			((video_property_flag&MPEG4_QPEL_FLAG) > 0)

// mp4vid_status
// set by video parser, and cleared by file parser
#define MPEG4_STATUS_NEED_DATA			0		// need more data
#define MPEG4_STATUS_ERROR_UNSUPPORTED	1		// error of unsupported options
#define MPEG4_STATUS_ERROR_SEQUENCE		2		// error of parsing the sequence header
#define MPEG4_STATUS_ERROR_PICTURE		3		// error of parsing the picture
#define MPEG4_STATUS_OK					MPEG4_STATUS_NEED_DATA


//#define	GET_MP4_TIME()			frctl_frame_to_time(decoded_frame)	// in seconds


//#endif	// SUPPORT_MP4



//
#define DECODE_FORMAT_525   0
#define DECODE_FORMAT_625   1
#define DECODE_FORMAT_OTHER 2


extern  UINT8   viddec_nodecode;

//
// FRAMEBUF
// framebuf_mb_width    macroblock-mode
// framebuf_line_width



/*
**      VPP     VPP     VPP     VPP     VPP     VPP     VPP
*/
#if 0
// Pixel Aspect Ratio
#define VPP_PAR_MP_FORCE_SQUARE		(1<<0)
#define VPP_PAR_MP4_FORCE_SQUARE	(1<<1)
#define VPP_PAR_MP4_GUESS_43TV		(1<<2)
#define VPP_PAR_MP4_REVERSE_169TV	(1<<3)
#define VPP_PAR_MP4_PARTIAL_169TV	(1<<4)
#endif


/*
**      ENCODE
*/

/*
**      TEST    TEST    TEST    TEST    TEST    TEST    TEST
*/

#endif/*__KDEF_H*/

