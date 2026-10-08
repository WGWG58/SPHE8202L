/*
*  File     : dsp_intr.c 
*  Function : dsp3 interrupt to risc
*  History  :
*            2003.3.12 Creat by Terry
*
*/
#include "config.h"
#include "regmap.h"

#ifndef	DVDRELEASE
//#define DSP_INTR_DBG   1
#endif

#define	dintr_puts(s)		((void)0)
#define	dintr_printf(s...)	((void)0)

#ifdef	DSP_INTR_DBG
#include "sio.h"
#include "emuio.h"
#define	MONE_DOWNLOAD_CODEC
#undef	dintr_puts
#undef	dintr_printf
#define	dintr_puts(s)	io_write(s)
#define	dintr_printf(s...)	\
	do { \
	  psprintf(linebuf, ##s); io_write(linebuf); \
	} while (0)
#endif

void dsp_intr(void)
{
    dintr_printf("dsp:%04x\n", regs0->dsp24_port[15]);
    regs0->dsp24_port[15] = 0;
}
