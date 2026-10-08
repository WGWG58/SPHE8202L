#ifndef __FRAMEBUF_IF_H
#define	__FRAMEBUF_IF_H

#include "types.h"
#include "framebuf_def.h" //swpong 2006 0530
// framebuffer location definition

#define GetDisplayingFrameBuffer() 	(1<<(regs0->dis_pic_id))

//
// basic operations

// luma/chroma location 
unsigned fbuf_get_luma(int s);
unsigned fbuf_get_chroma(int s);

// fill and copy
int	fbuf_fill(UINT32 bitmask);
int	fbuf_copy(unsigned t, unsigned s);

// bitblt
void	bitblt_frame(int dx, int dy, int dstf, int srcf, int w, int h, int zx, int zy, int p2n);
void	bitblt_frame_22(int dx, int dy, int dstf, int srcf, int w, int h, int p2n);
void	bitblt_frame_34(int dx, int dy, int dstf, int srcf, int w, int h, int p2n);
void	bitblt_frame_24(int dx, int dy, int dstf, int srcf, int w, int h, int p2n);
void	bitblt_frame_44(int dx, int dy, int dstf, int srcf, int w, int h, int p2n);

// pixel operation
UINT8   get_pixel_luma(int fb, int x, int y);
UINT16  get_pixel_chroma(int fb, int x, int y);
void    set_pixel_luma(int fb, int x, int y, unsigned luma);
void    set_pixel_chroma(int fb, int x, int y, unsigned chroma);

// legacy function
#define clrFrameBuffer(m)	fbuf_fill(m)

#endif/*__FRAMEBUF_IF_H*/
