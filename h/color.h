#ifndef	__COLOR_H
#define	__COLOR_H

/*
** Color space conversion.
**
** from CCIR REC 601.4
**
**	Y          = .299R + .587G + .114B
**	Cr = (R-Y) = .701R - .587G - .114B
**	Cb = (B-Y) =-.299R - .587G + .886B
**
** CCIR recommendation
**	Y  = 219 * Y + 16
**	Cr = 224 * Cr + 128
**	Cb = 224 * Cb + 128
**
** CCIR fixed.
**
** 	Y  = ( 81 Rd +  145 Gd +  25 Bd) / 256 + 16
** 	Cr = (157 Rd + -131 Gd + -26 Bd) / 256 + 128
** 	Cb = (-67 Rd + -131 Gd + 198 Bd) / 256 + 128
**
** 	Y  = ( 77 Rd +  150 Gd +  29 Bd) / 256
** 	Cr = (131 Rd + -110 Gd + -21 Bd) / 256 + 128
** 	Cb = (-44 Rd +  -87 Gd + 131 Bd) / 256 + 128
**
** for example
**		   R   G   B	  Y  Cr  Cb
**	RED	 255   0   0	 76 255  84
**/

int CLIP_TOP(int x, int c);
int CLIP_BOT(int x, int c);
int CLIP_TWO(int x, int t, int b);

#define	RGB_CLIP_Y(x)	CLIP_TOP(x,255)
#define	RGB_CLIP_C(x)	CLIP_TWO(x,255,0)

int RGB_Y (int R, int G, int B);
int RGB_Cr(int R, int G, int B);
int RGB_Cb(int R, int G, int B);
#if 0
static	inline	int RGB_Y (int R, int G, int B)	{return (( 77*(R) + 150*(G) +  29*(B))/256);}
static	inline	int RGB_Cr(int R, int G, int B)	{return ((131*(R) - 110*(G) -  21*(B))/256 + 128);}
static	inline	int RGB_Cb(int R, int G, int B)	{return ((-44*(R) -  87*(G) + 131*(B))/256 + 128);}
#endif

#endif/*__COLOR_H*/

