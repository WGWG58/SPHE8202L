#ifndef __DMA_H
#define __DMA_H

#ifndef	EXTERN
#define	EXTERN	extern
#endif
#include "config.h"
#include "regmap.h"
#include "dmabuf.h"


#define VADDR_MODE_GLOBAL_PHY   0
#define VADDR_MODE_CDDSP        1
#define VADDR_MODE_OSD		2
#define	VADDR_MODE_SUP		3
#define	VADDR_MODE_OGT		VADDR_MODE_SUP
#define	VADDR_MODE_AUD		4
#define	VADDR_MODE_VID		5
#define	VADDR_MODE_DSP16	6
#define	VADDR_MODE_DSP24	7
#define VADDR_MODE_GLOBAL	15

#define DMA_LEN_32   (0<<3)
#define DMA_LEN_64   (1<<3)
//#define DMA_LEN_96   (2<<3)
#define DMA_LEN_128  (2<<3)
#define DMA_LEN_256  (3<<3)
#define DMA_LEN_512  (4<<3)
#define DMA_LEN_1024 (5<<3)
#define DMA_READ_MD  (0<<5)
#define DMA_WRITE_MD (1<<5)


#define dma_buf		(*(WorkBuf *)(DATA_RAM_BASE)) // regs0p->dmab.dma_mem
//#define dma_buf1	(regs0->reg_dma_buf512)
#ifdef KERNEL_SUPPORT_2DMA
#define DMA_load(AddrMode, VAddr, HAddr, DAddr, Len)	{		\
  regs0->dma1_mode     = (UINT32)(Len<<8)|(AddrMode&0x07);\
  regs0->dma1_start_addr  = (UINT32)((DAddr>>2)&0x7ff);			\
  regs0->dma1_xaddr    = (HAddr);					\
  regs0->dma1_yaddr    = (VAddr);					\
  }
#define DMA_save(AddrMode, VAddr, HAddr, DAddr, Len)  {			\
  regs0->dma1_mode     = (UINT32)(Len<<8)|(1<<5)|(AddrMode&0x07);	\
  regs0->dma1_start_addr  = (UINT32)((DAddr>>2)&0x7ff);			\
  regs0->dma1_xaddr    = (HAddr);					\
  regs0->dma1_yaddr    = (VAddr);					\
}
#define	DMA_wait()	{while (!(regs0->dma1_done));}
#else //KERNEL_SUPPORT_2DMA

#define DMA_load(AddrMode, VAddr, HAddr, DAddr, Len)	{		\
  regs0->dma_mode=((((UINT32)(DAddr))&0xff)<<8)|((((Len)>>5)-1)<<3)|(AddrMode);\
  regs0->dma_xaddr    = (HAddr);					\
  regs0->dma_yaddr    = (VAddr);					\
  }
#define DMA_save(AddrMode, VAddr, HAddr, DAddr, Len)  {		\
  regs0->dma_mode=((((UINT32)(DAddr))&0xff)<<8)|((0x01)<<5)|((((Len)>>5)-1)<<3)|(AddrMode);\
  regs0->dma_xaddr    = (HAddr);					\
  regs0->dma_yaddr    = (VAddr);					\
  }

#define	DMA_wait()	{while (!(regs0->dma_done));}
#endif //KERNEL_SUPPORT_2DMA

#endif/*__DMA_H*/

