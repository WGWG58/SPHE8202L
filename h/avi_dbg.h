#ifndef	AVI_DBG_H
#define AVI_DBG_H

#define	avi_puts(s)			((void)0)
#define	avi_putc(c)			((void)0)
#define	avi_printf(s...)	((void)0)

#ifndef DVDRELEASE
#define AVI_PARSER_DBG
#endif

#ifdef	AVI_PARSER_DBG
//#define AVI_GENERAL_DBG
//#define AVI_FILE_INFO
//#define AVI_FCC_DBG
//#define AVI_DUMP_SUBCHUNK
//#define AVI_AUDIO_DBG
//#define AVI_IDX1_DBG
//#define AVI_STC_DBG
//#define AVI_GOTO_DBG
//#define AVI_NEXTI_DBG
//#define AVI_DRM_CHK
//#define AVI_LIMITATION_DBG

//#define AVI_DROP_V
//#define AVI_DROP_A

#include "emuio.h"
#include "sio.h"
#undef	avi_puts
#undef	avi_putc
#undef	avi_printf
#define	avi_puts(s)		io_write(s)
#define	avi_putc(c)		io_putc(c)
#define	avi_printf(s...)	\
	do { \
	psprintf(linebuf, ##s); io_write_wait(linebuf); \
	} while (0)
#endif	// AVI_PARSER_DBG

#endif	// AVI_DBG_H
