extern	char	_etext[];
extern	char	_data[];
extern	char	_edata[];
extern	char	_bstart[];
extern 	char	_bend[];

extern	char	_stextf[];
extern	char	_textf[];
extern	char	_etextf[];

#include "config.h"
#include "regmap.h"
#include "global.h"
#include "dma.h"
#include "reset.h"

//#define     ROMFINIT_DBG        1

void	rominit(void)
{
	char *src = _etext;
	char *dst = _data;
	
	/*
	** ROM has initial data at end of text
	** copy from _etext to (_data,_edata) 
	*/
	do {
		*dst++ = *src++;
	} while (dst<_edata);
	
	/* Zero bss */
	dst = _bstart;
	do {
		*dst++ = 0;
	} while (dst<_bend);
	
	/*
	** reset system interface
	*/
	reset_system();


#if 0	
	/*
	** Copy shadowed rom code to SDRAM.
	**
	** ROM has fast-text (in SDRAM) at end of
	** copy from (_stextf,_etext) to _textf
	*/
	{
		int i;
		int rx = 0;
		int ry = 0;
		int rw = RBV_W;
		
		src = _stextf;
#ifdef DOWNLOAD_WITH_DMA
		do {
			for (i=0;i<32;i++)
			{
				dma_buf.b[i] = *src++;
			}
			DMA_save(VADDR_MODE_ROMIMAGE, ry, rx, 0, 32);
			ADDR_adv_one(rx,ry,rw,32);
			DMA_wait();
		} while (src<_etextf);
#else
		dst = _textf;
		do {
			*dst++ = *src++;
		} while (src<_etextf);
#endif
        }
#endif
}

