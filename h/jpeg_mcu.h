#ifndef __JPEG_MCU_H
#define __JPEG_MCU_H

#include "jpeg_parser.h"

// Hardware IDCT&IQ
#define 	INVQ_JPEG_MODE      	(1<<1)
#define 	INVQ_JPEG_BYPASS    	(1<<0)
#define 	INVQ_JPEG_NOBYPASS  	(0<<0)

#define 	HW_CLKEN0_INVQ          (1<<10)
#define 	HW_CLKEN0_IDCT          (1<<9)
#define 	HW_CLKEN0_GRFX          (1<<7)

#define 	GRAPH_JPEG				(1<<4)
#define 	GRAPH_JPEG_32			(1<<10)
#define 	GRAPH_JPEG_SAT			(1<<12)

#endif //__JPEG_MCU_H
