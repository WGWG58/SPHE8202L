#ifndef __FILE_DEF_H__
#define __FILE_DEF_H__

// file buffer
#define FILEBUFSIZE			    (30 * 1024)
#define	FILEBUFSTART		    (SDRAM_BASE_UNCACHED + ((A_FILE_BUF_YA+A_FILE_BUF_SIZE) << 10) - FILEBUFSIZE)

// file_type
#define	FILE_TYPE_UNKNOWN		0
#define	FILE_TYPE_AVI			1
#define	FILE_TYPE_ASF			2
#define	FILE_TYPE_QT			3
#define	FILE_TYPE_ND			4
#define FILE_TYPE_MPG           5
#define	FILE_TYPE_WAVE			6
#define	FILE_TYPE_CDXA			7
#define FILE_TYPE_OGG           8

// file_media_support
#define	FILE_MODE_ALL			0xFFFF
#define	FILE_SUPPORT_AUDIO		(1<<0)
#define	FILE_SUPPORT_VIDEO		(1<<1)
#define	FILE_SUPPORT_SUPIC		(1<<2)
#define	FILE_SUPPORT_IDX		(1<<3)
#define	FILE_SUPPORT_SUBT		(1<<4)

// file_media_flag
#define FILE_STRM_FLAG_NONE		0
#define FILE_AUDIO				(1<<0)
#define FILE_VIDEO				(1<<1)
#define FILE_SUPIC				(1<<2)

#define FILE_SUPPORTED_AUDIO	(1<<4)
#define FILE_SUPPORTED_VIDEO	(1<<5)
#define FILE_SUPPORTED_SUPIC	(1<<6)

#define FILE_AUDIO_VBR			(1<<8)
#define FILE_AV_INTERLEAVED		(1<<9)

// file_play_state
#define	FILE_NORMAL_STATE		0
#define	FILE_DROPA_STATE		(1<<0)
#define	FILE_DROPV_STATE		(1<<1)
#define	FILE_DROPS_STATE		(1<<2)

// file_error_flag

#endif	// __FILE_DEF_H__
