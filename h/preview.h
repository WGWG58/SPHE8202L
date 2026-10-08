#ifndef	__PREVIEW_H
#define	__PREVIEW_H

#include "framebuf.h"
#include "memcfg.h"
#include "reset.h"

#define	FRAME_PREVIEW	2

#define	FillDigestBackground()	\
		clrFrameBuffer(FRAME_REF0|FRAME_REF1|FRAME_BIDIR|FRAME_FILL_BLUE)

#define	SetupDigestBackground()	\
		do { \
		  config_memory(MEMORY_PREVIEW);	\
		  FillDigestBackground();		\
		} while (0)
#endif
