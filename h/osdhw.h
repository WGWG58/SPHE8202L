#ifndef __OSDHW_H
#define	__OSDHW_H  

#define	OSD_CLUT_UPDATE	1
#define	OSD_CLUT_REMAIN	0

/*
**	CLUT type
**			HIGH_COLOR	COLOR_RESOLUTION
**	4-color		0		1
**	16-color	0		0
**	256-color	1		0
**	reserved	1		1
**
*/
#define	OSD_CLUT_4      1
#define	OSD_CLUT_16     0
#define	OSD_CLUT_256	2
#define	OSD_CLUT_HIGH	3


#define	LINK_NULL	(0xffff)
#define	__palette2(Y,Cb,Cr,Blend,Fill) \
	(\
	   (((UINT32)(Y)     & 0x3f)<<10)	\
	 | (((UINT32)(Cb)    & 0x0f)<<6)	\
	 | (((UINT32)(Cr)    & 0x0f)<<2)	\
         | ((Blend) ? 0x02 : 0x01)		\
         | ((Fill)  ? 0x01 : 0x00)		\
)

#define	__palette2F(Y,B,R,Blend,Fill) \
	__palette2((Y)>>2, (B)>>4, (R)>>4, (Blend), (Fill))

/*
**	COLOR	Y	Cr	Cb
**
**	WHITE	0xeb	0x80	0x80
**	YELLOW	0xa2	0x8e	0x2c
**	CYAN	0x83	0x2c	0x9c
**	GREEN	0x70	0x3a	0x48
**	MAGENTA	0x54	0xc6	0xb8
**	RED	0x41	0xd4	0x64
**	BLUE	0x23	0x72	0xd4
**	BLACK	0x10	0x80	0x80
**
*/

#endif/*__OSD_H*/

