// 2005/09/14 yltseng
#ifndef __AVI_IF_H
#define __AVI_IF_H

#include "avi_def.h"
#include "avi_type.h"

#include "file_if.h"
#include "audcodec.h"

#define AVI_FAST_JUMP		4

UINT32	Is_RIFF_file(BYTE *srcptr, UINT32 bufsize);

int		initAVIParam();
int		doAVIPreParser(BYTE *srcptr, INT32 bufsize);
#ifdef SUPPORT_DIVX6
int		divx6_preparse(BYTE *srcptr, INT32 bufsize);
#endif  //#ifdef SUPPORT_DIVX6
void	get_avi_video_version(avi_video_info* info);
int		do_avi_movi_parser(void);
//void avi_set_audio_fPTS();
//void do_avi_audio_sync();
//UINT32	avi_set_goto(UINT32);
UINT32	avi_set_goto_next_frame();

int		avi_init_idx1();
UINT32	avi_support_tricky_play();
int		avi_get_next_I(int speed, UINT32* p_frm_offset);
UINT32	avi_ready_to_jump(int speed);
UINT32	avi_set_goto(UINT32 goto_time);
int		avi_set_fast(int avs);
int		avi_set_slow(int avs);
void	avi_clr_bufparam();
int		avi_init_audio_stream(int aud_strm_num);
int		avi_init_video_stream(int vid_strm_num);
int		avi_init_supic_stream(int sup_strm_num);

int avi_restruct_sync_table(); // gary.huang

UINT32 CalcStreamNum(UINT32 uFCC, BYTE bNum);

extern	UINT32	file_play_state;
extern	UINT32	file_error_flag;
extern	UINT32	file_media_flag;
extern	UINT32	file_media_support;
extern	UINT32	file_len;
extern	UINT32	ext_sup_state;			// initialized/activated/

//#define	AVI_SUPPORT_TRICKY_PLAY()	(IS_FILE_TYPE_AVI() && ((GET_FILE_FLAG()&AVI_IDX1) > 0))
#define	IS_DIVX_DRM()				(IS_FILE_TYPE_AVI() && ((GET_FILE_FLAG()&AVI_DIVX_DRM) > 0))

#define GET_AVI_FILE_LEN()			(file_len)		// in seconds

#if 0
#define	IS_AVI_IN_DROPA()			((file_play_state&FILE_DROPA_STATE) > 0)
#define	IS_AVI_IN_DROPV()			((file_play_state&FILE_DROPV_STATE) > 0)

#define	SET_AVI_PLAY_STATE(x)		(file_play_state = (x))
#define	GET_AVI_PLAY_STATE()		(file_play_state)

#define AVI_HAS_AUDIO()				((file_media_flag&AVI_AUDIO) > 0)
#define AVI_HAS_VIDEO()				((file_media_flag&AVI_VIDEO) > 0)
#define AVI_HAS_SUPIC()				((file_media_flag&AVI_SUPIC) > 0)
#define IS_AVI_AUDIO_VBR()			((file_media_flag&AVI_AUDIO_VBR) > 0)
#define IS_AVI_AUDIO_UNSUPPORTED()	((file_media_flag&AVI_AUDIO_UNSUPPORTED) > 0)
#define IS_AVI_VIDEO_UNSUPPORTED()	((file_media_flag&AVI_VIDEO_UNSUPPORTED) > 0)

#define SET_AVI_STREAM_FLAG(x)		(file_media_flag = (x))
#define ADD_AVI_STREAM_FLAG(x)		(file_media_flag |= (x))
#define SUB_AVI_STREAM_FLAG(x)		(file_media_flag &= ~(x))
#define GET_AVI_STREAM_FLAG()		(file_media_flag)

#define SET_AVI_FILE_FLAG(x)		(avi_file_flag = (x))
#define ADD_AVI_FILE_FLAG(x)		(avi_file_flag |= (x))
#define SUB_AVI_FILE_FLAG(x)		(avi_file_flag &= ~(x))
#define GET_AVI_FILE_FLAG()			(avi_file_flag)
#define	AVI_SUPPORT_TRICKY_PLAY()	(((avi_file_flag&AVI_IDX1) > 0) && IS_FILE_TYPE_AVI())
#define	IS_DIVX_DRM()				(((avi_file_flag&AVI_DIVX_DRM) > 0) && IS_FILE_TYPE_AVI())

#define GET_AVI_FILE_LEN()			(file_len)		// in seconds

#endif	// #if 0

// mimitsai move from avi_if.c 050817
#if defined(SDRAM_16Mb_Mode) && !defined(TURBO_DECODE)
// memory config
#define	AVIIDX1START		(SDRAM_BASE_UNCACHED + ((A_FILE_BUF_YA) << 10))
#define AVIIDX1SIZE		    (10 << 10)
#define AVIIDX1END		    (AVIIDX1START + AVIIDX1SIZE)

#define	AVIBUFSTART		    AVIIDX1END
#define	AVIBUFSIZE		    (45 << 10)
#define	AVIAUDIOBUF		    AVIBUFSTART				// 8k should be enough, 1 sec for 8kHz * 1byte * 1chan source
#define AVIAUDIOBUFSIZE		(44 << 10)
#define	AVIAUDIOBUFEND		(AVIAUDIOBUF + AVIAUDIOBUFSIZE)

#define	AVIVIDEOBUF		    AVIAUDIOBUFEND
#define AVIVIDEOBUFSIZE		(100 << 10)				// 100k video buffer (the bigger, the better)
													// audio + video buffer size should not exceed 188k
#define AUD_CHK_SAVE_START	AVIBUFSTART
#define	AUD_CHK_SAVE_ENTRY	(3)
#define AUD_CHK_SAVE_NUM	512
#define AUD_CHK_SAVE_SIZE	(AUD_CHK_SAVE_NUM * AUD_CHK_SAVE_ENTRY * sizeof(UINT32))
#define AUD_CHK_SAVE_END	(AUD_CHK_SAVE_START + AUD_CHK_SAVE_SIZE)

// used to trace the VBR audio chunks
#define AVIAUDVBRSIZE       (2 << 10)
#define AUD_CHK_ENTRY_NUM   (AVIAUDVBRSIZE / sizeof(BYTE*))
#define AVIAUDVBRBUF		AVIAUDIOBUFEND
#define AVIAUDVBREND		(AVIAUDVBRBUF + AVIAUDVBRSIZE)

// external subtitle
#define AVISUPIDX_START     AVIAUDVBREND
#define AVISUPIDX_SIZE      (20)
#define AVISUPIDX_END       (AVISUPIDX_START + ((AVISUPIDX_SIZE) << 10))
#define AVISUPBUF_START     AVISUPIDX_END
#define AVISUPBUF_SIZE      (20)
#define AVISUPBUF_END       (AVISUPBUF_START + ((AVISUPBUF_SIZE) << 10))

// DivX DRM header
#define AVIDRMBUF		    AVISUPBUF_END
#define AVIDRMSIZE		    (3 << 10)//(3*1024)				// >= DRM_HEADER_SIZE
#define AVIDRMEND		    (AVIDRMBUF + AVIDRMSIZE)

#else   //32Mb or 16Mb with direct B frame output

// external subtitle
#if !defined( SUPPORT_MP4_SUBTITLE ) || defined( COMPRESS_ROM_CODE_040 )

#define AVISUPIDX_START     (SDRAM_BASE_UNCACHED + ((A_FILE_BUF_YA) << 10))
#define AVISUPIDX_SIZE      (0)
#define AVISUPIDX_END       (AVISUPIDX_START + ((AVISUPIDX_SIZE) << 10))
#define AVISUPBUF_START     AVISUPIDX_END
#define AVISUPBUF_SIZE      (0)
#define AVISUPBUF_END       (AVISUPBUF_START + ((AVISUPBUF_SIZE) << 10))
    
#else   //!COMPRESS_ROM_CODE_040
    
#define AVISUPIDX_START     (SDRAM_BASE_UNCACHED + ((A_FILE_BUF_YA) << 10))
#define AVISUPIDX_SIZE      (30)
#define AVISUPIDX_END       (AVISUPIDX_START + ((AVISUPIDX_SIZE) << 10))
#define AVISUPBUF_START     AVISUPIDX_END
    
        #if defined(SDRAM_16Mb_Mode) && defined(TURBO_DECODE)
#define AVISUPBUF_SIZE  (54 - EXTRA_FS9660BUF)
        #else
            #ifdef SUPPORT_DIVX6  //divx6 steal some memory from avi... kevinmonkey 051107
#define AVISUPBUF_SIZE          (40)
            #else  //!SUPPORT_DIVX6
#define AVISUPBUF_SIZE  (54)
            #endif  //#ifdef SUPPORT_DIVX6
        #endif  //  //#if defined(SDRAM_16Mb_Mode) && defined(TURBO_DECODE)

#define AVISUPBUF_END       (AVISUPBUF_START + ((AVISUPBUF_SIZE) << 10))
#endif

// avi index buffer
#define	AVIIDX1START		AVISUPBUF_END
#if defined(SDRAM_16Mb_Mode) && defined(TURBO_DECODE)
    #define AVIIDX1SIZE	    (10 << 10)
#else  //32Mb
    #ifdef SUPPORT_DIVX6  //divx6 steal some memory from avi... kevinmonkey 051107
#define AVIIDX1SIZE		(70 << 10)
    #else //!SUPPORT_DIVX6
    #define AVIIDX1SIZE		(100 << 10)
    #endif  //#ifdef SUPPORT_DIVX6
#endif  //#if defined(SDRAM_16Mb_Mode) && defined(TURBO_DECODE)
#define AVIIDX1END		    (AVIIDX1START + AVIIDX1SIZE)

// avi audio buffer
#define	AVIBUFSTART		    AVIIDX1END
#define	AVIBUFSIZE		    (80 << 10)
#define	AVIAUDIOBUF		    AVIBUFSTART				// 8k should be enough, 1 sec for 8kHz * 1byte * 1chan source
#if defined(SDRAM_16Mb_Mode) && defined(TURBO_DECODE)
    #ifdef COMPRESS_ROM_CODE_040
        #define AVIAUDIOBUFSIZE	(80 << 10)
    #else   //!COMPRESS_ROM_CODE_040 || !SDRAM_16Mb_Mode || !TURBO_DECODE
    #define AVIAUDIOBUFSIZE	(80 << 10)
    #endif  //#ifdef COMPRESS_ROM_CODE_040
#else   //32Mb
    #define AVIAUDIOBUFSIZE	(114 << 10)
#endif
#define	AVIAUDIOBUFEND		(AVIAUDIOBUF + AVIAUDIOBUFSIZE)

#define	AVIVIDEOBUF		    AVIAUDIOBUFEND
#define AVIVIDEOBUFSIZE		(100 << 10)				// 100k video buffer (the bigger, the better)
													// audio + video buffer size should not exceed 188k
													
// avi audio chunk buffer( temporarily )
#define AUD_CHK_SAVE_START	AVIBUFSTART
#define	AUD_CHK_SAVE_ENTRY	(3)
#define AUD_CHK_SAVE_NUM	512
#define AUD_CHK_SAVE_SIZE	(AUD_CHK_SAVE_NUM * AUD_CHK_SAVE_ENTRY * sizeof(UINT32))
#define AUD_CHK_SAVE_END	(AUD_CHK_SAVE_START + AUD_CHK_SAVE_SIZE)

// avi video chunk buffer( temporarily, debug only )
#ifdef AVI_LIMITATION_DBG
#define VID_CHK_SAVE_START  AUD_CHK_SAVE_END
#define VID_CHK_SAVE_ENTRY  (2)
#define VID_CHK_SAVE_NUM    512
#define VID_CHK_SAVE_SIZE   (VID_CHK_SAVE_NUM * VID_CHK_SAVE_ENTRY * sizeof(UINT32))
#define VID_CHK_SAVE_END    (VID_CHK_SAVE_START + VID_CHK_SAVE_SIZE)
#endif

// used to trace the VBR audio chunks
#define AVIAUDVBRSIZE       (2 << 10)
#define AUD_CHK_ENTRY_NUM   (AVIAUDVBRSIZE / sizeof(BYTE*))
#define AVIAUDVBRBUF		AVIAUDIOBUFEND
#define AVIAUDVBREND		(AVIAUDVBRBUF + AVIAUDVBRSIZE)

// DivX DRM header
#define AVIDRMBUF		    AVIAUDVBREND
#define AVIDRMSIZE		    (3 << 10)//(3*1024)				// >= DRM_HEADER_SIZE
#define AVIDRMEND		    (AVIDRMBUF + AVIDRMSIZE)

//conflict definition checking
#ifdef COMPRESS_ROM_CODE_040
    #ifdef SUPPORT_MP4_SUBTITLE
        #error "can't support sub title when 040 rom."
    #endif
    #ifndef TURBO_DECODE
        #error "This is specially for turbo decode mode."
    #endif    
    #ifndef SDRAM_16Mb_Mode
        #error "16Mb situation is not considerred."
    #endif  
#endif

#endif  //file buffer definition


#endif	// __AVI_IF_H
