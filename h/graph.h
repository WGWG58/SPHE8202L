#ifndef	__GRAPH_H
#define	__GRAPH_H

#include "color.h"
#include "osdfont.h"

#include "memmap.h"
#include "framebuf.h"

#define	BASE_LUMA	REF0_LUMA
#define	BASE_CHROMA	REF0_CHROMA

//
// LINE_OFFSET
// 352/704 for EDO compact version
// 1024 for SDRAM loose version
//
extern UINT16 line_offset;
#define	LINE_OFFSET	line_offset


#define	OFFSET_LUMA	(BASE_LUMA * 1024)
#define	OFFSET_CHROMA	(BASE_CHROMA *1024)

#define	LUMA_START_ADDR		(SDRAM_BASE+ BASE_LUMA * 1024)
#define	CHROMA_START_ADDR	(SDRAM_BASE+ BASE_CHROMA *1024)

#define	OFFSET_Y(Y)	((Y)*LINE_OFFSET)
#define	OFFSET_C(Y)	((Y)*LINE_OFFSET)

#ifdef SDRAM_NO_REORDER
#define	SFFB(X)		(X)
#define	SFFS(X)		(X)
#define	SFFW(X)		(X)
#define	SFF(X)		SFFB(X)
#else
// shuffle in 32-byte
#define	SFFB(X)		((((X)&0x08)<<1) | (((X)&0x10)>>1) | ((X)&~(0x18)))
#define	SFFS(X)		((((X)&0x04)<<1) | (((X)&0x08)>>1) | ((X)&~(0x0C)))
#define	SFFW(X)		((((X)&0x02)<<1) | (((X)&0x04)>>1) | ((X)&~(0x06)))
#define	SFF(X)		SFFB(X)
#endif

#define	Y_XY(X,Y)	((BYTE *)  (FRM0L_PTR()+OFFSET_Y(Y)+SFF(X) ))
//20060104, joshua modified for font blotted problem on framebuf
//#define	C_XY(X,Y)	((UINT16 *)(FRM0C_PTR()+OFFSET_C((Y)>>1)+2*(SFF(X)>>1)))
#define	C_XY(X,Y)	((UINT16 *)(FRM0C_PTR()+OFFSET_C((Y)>>1)+2*(SFF(X)>>1)))
#define	Y_XY1(X,Y)	((BYTE *)  (FRM1L_PTR()+OFFSET_Y(Y)+SFF(X) ))
#define	C_XY1(X,Y)	((UINT16 *)(FRM1C_PTR()+OFFSET_C((Y)>>1)+2*(SFF(X)>>1)))
#define	Y_XYB(X,Y)	((BYTE *)  (FRM2L_PTR()+OFFSET_Y(Y)+SFF(X) ))
#define	C_XYB(X,Y)	((UINT16 *)(FRM2C_PTR()+OFFSET_C((Y)>>1)+2*(SFF(X)>>1)))


#define	SFFB_SR(X)      ((((X)&0x08)<<1) | (((X)&0x10)>>1) | ((X)&~(0x18)))
#define	SFFS_SR(X)      ((((X)&0x04)<<1) | (((X)&0x08)>>1) | ((X)&~(0x0C)))
#define	SFFW_SR(X)      ((((X)&0x02)<<1) | (((X)&0x04)>>1) | ((X)&~(0x06)))
#define	SFF_SR(X)       SFFB_SR(X)
#define	Y_XYB_SR(X,Y)   ((BYTE *)  (FRM2L_PTR()+OFFSET_Y(Y)+SFF_SR(X) ))
#define	C_XYB_SR(X,Y)   ((UINT16 *)(FRM2C_PTR()+OFFSET_C((Y)>>1)+2*(SFF_SR(X)>>1)))

//
// prototype
//
//void	setColor(UINT32);
//void    plotXY(int, int); 
//void    drawLine(int SX, int SY, int EX, int EY);

//extern	const BYTE	**graph_font;
//#define	setFont(f)	(graph_font=f)

//int     drawChar(int, int, UINT32);
//int     drawString(int x, int y, const char *);

void	gph_fill_color(int pic, int x, int y, int w, int h, unsigned Y, unsigned CrCb);
void	gph_show_image(int pic, BYTE *image, BYTE *idx0, UINT16 *idx1, int x, int y, int w, int h);

#endif/*__GRAPH_H*/
