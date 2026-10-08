/*
* jpeglib.h
*
* 
* 
* 
*
* This file defines the application interface for the JPEG library.
* Most applications using the library need only include this file,
* and perhaps
*/
#ifndef JPEGLIB_H
#define JPEGLIB_H
#include "types.h"

enum {
    JPGDSP_RESULT_NG = -1,
	JPGDSP_RESULT_OK = 1,
    JPGDSP_RESULT_BREAK = 2,
};


/* This part borrowed from the bsd386 isofs */

#define ISODCL(from, to) (to - from + 1)
#define SOI		0xFFD8
#define APP0	0xFFE0
#define EOI		0xFFD9
#define DQT		0xFFDB
#define DHT		0xFFC4
#define SOF0	0xFFC0
#define SOS		0xFFDA
#define DRI		0xFFDD
#define RST		0xFFD0
#define RST0	0xFFD0
#define RST7	0xFFD7

#define SOF1    0xFFC1
#define SOF2    0xFFC2
#define SOF3    0xFFC3
#define SOF5    0xFFC5
#define SOF6    0xFFC6
#define SOF7    0xFFC7
#define SOF9    0xFFC9
#define SOFA    0xFFCA
#define SOFB    0xFFCB
#define SOFD    0xFFCD
#define SOFE    0xFFCE
#define SOFF    0xFFCF
#define DAC     0xFFCC

//#define JPGPreX         720
//#define JPGPreY         480
//#define JPGFullX        720
//#define JPGFullY        480
#define JPGPreX         720
#define JPGPreY         576
#define JPGFullX        720
#define JPGFullY        576

//#define	JPEGDEBUG	        1
//#define   JPGMONPERFORMANCE0   1    //only measure total time
//#define   JPGMONPERFORMANCE1   1    //measure all components time  

//0608 change INT16->int
typedef struct { 
	int P;
	int Nf;
	//int Y;
	UINT32  Y;
	int X;
	int HxV[4];
	int QTableIndex[4];
} T_SOF0;

//0608 change INT16->BYTE
typedef struct {
	INT16 NHT;
	BYTE Tc[4];
	BYTE Th[4];
	BYTE L[4][16];
	BYTE V[4][256];
} T_DHT;

//0608 change INT16->int
typedef struct {
	int Ns;
	int Cs[4];
	int Td[4];
	int Ta[4];
	int Ss;
	int Se;
	int Ah;
	int Al;
} T_SOS;

typedef struct {
    UINT32 Necs;
    UINT32 Nhecs;
    UINT32 Nvecs;
    UINT32 Nhdct;
    UINT32 Nvdct;
    UINT32 Ndct;
} T_ECS;

typedef struct {
    //UINT16 	marker;
    //UINT16 	tbl_len;
    //UINT16  gcJpgState;
    UINT32  rd_ptr;
    //UINT32  giPos;
    UINT16  gIthBits;
    BYTE    latch;
	
    UINT32  iReadLen;
    UINT32  iLeaveLen;
    UINT32  iAllLen;
    UINT32  iProcessedLen;
    UINT32  Vmcu;
    UINT32  Hmcu;
	
    //UINT32  xWidth;
    //UINT32  yHeight;
    int     restart_interval;
    int     ri;
    UINT16  gbDecodeECS;
    //int     iiii;
    UINT32  nextMSF;
    UINT32  needFrames;
	
#ifdef JPGMONPERFORMANCE0
    UINT32  iIDPCM;
    UINT32  iIVLC;
    UINT32  iIDCT;
    UINT32  iAll;
    UINT32  iAll1;
    UINT32  iMove;
    UINT32  iCopyCD;
    UINT32  iTime1;
    UINT32  iTime2;
#endif
	
    //UINT32  xBlocks;
    //UINT32  yBlocks;
	
    UINT16  xTVStart;
    UINT16  yTVStart;
    UINT16  xTVWidth;
    UINT16  yTVHeight;
	
    UINT16    xOffset;
    UINT16    yOffset;
    BYTE    iFactor;
    BYTE    *gfp;
    BYTE    *pCbCr;
    UINT16    cStep;
    BYTE    scanState;
    BYTE    checkRST;
} MYJPEG;

typedef struct {
    int tmp0;
    int tmp1;
    int tmp2;
    int tmp3;
    int tmp4;
    int tmp5;
    int tmp6;
    int tmp7;
    int tmp10;
    int tmp11;
    int tmp12;
    int tmp13;
    int z5;
    int z10;
    int z11;
    int z12;
    int z13;
    UINT32  Vdct;
    UINT32  Hdct;
    UINT32  bx;
    UINT32  by;
    UINT32  hh;
    UINT32  vv;
    UINT32  xNew;
    UINT32  yNew;
	UINT32	component;
} JPGTEMP;


#define MAXJSAMPLE 			255
#define RANGE_MASK 			(MAXJSAMPLE*4+3)

#define DCTSIZE 			8
#define DCTSIZE2 			64

#ifndef JPGDSP

#define RIGHT_SHIFT(x,shft) ((x) >> (shft))
#define ONE     			((INT32) 1)


//#define IDCT_FAST

#ifdef IDCT_FAST

#define FIX_1_082392200  ((INT32)  277)         // FIX(1.082392200) 
#define FIX_1_414213562  ((INT32)  362)         // FIX(1.414213562) 
#define FIX_1_847759065  ((INT32)  473)         // FIX(1.847759065) 
#define FIX_2_613125930  ((INT32)  669)         // FIX(2.613125930) 

#define CONST_BITS 			8
#define PASS1_BITS  		2

// tyt's notes, 0417/2001
// for accurate rounding, select the first macro
// for faster operation, select the second macro
#define DESCALE(x,n)                RIGHT_SHIFT((x) + (ONE << ((n)-1)), n)
//#define DESCALE(x,n)  				RIGHT_SHIFT(x, n)
#define MULTIPLY(var,const)  		((INT16) DESCALE((var) * (const), CONST_BITS))
#define DEQUANTIZE(coef,quantval)   (((INT16) (coef)) * (quantval))

#else

/*
#define CONST_BITS  10      //13 -> 10
#define PASS1_BITS  2
#define FIX_0_298631336  ((INT32)  306)     // FIX(0.298631336)     2446/8
#define FIX_0_390180644  ((INT32)  400)     // FIX(0.390180644)     3196/8
#define FIX_0_541196100  ((INT32)  554)     // FIX(0.541196100)     4433/8
#define FIX_0_765366865  ((INT32)  784)     // FIX(0.765366865)     6270/8
#define FIX_0_899976223  ((INT32)  922)     // FIX(0.899976223)     7373/8
#define FIX_1_175875602  ((INT32)  1204)    // FIX(1.175875602)     9633/8
#define FIX_1_501321110  ((INT32)  1537)    // FIX(1.501321110)     12299/8
#define FIX_1_847759065  ((INT32)  1892)    // FIX(1.847759065)     15137/8
#define FIX_1_961570560  ((INT32)  2009)    // FIX(1.961570560)     16069/8
#define FIX_2_053119869  ((INT32)  2102)    // FIX(2.053119869)     16819/8
#define FIX_2_562915447  ((INT32)  2624)    // FIX(2.562915447)     20995/8
#define FIX_3_072711026  ((INT32)  3147)    // FIX(3.072711026)     25172/8

#define FIX_0_211164243  ((INT32)  216)     // FIX(0.211164243)     1730/8
#define FIX_0_509795579  ((INT32)  522)     // FIX(0.509795579)     4176/8
#define FIX_0_601344887  ((INT32)  616)     // FIX(0.601344887)     4926/8
#define FIX_0_720959822  ((INT32)  738)     // FIX(0.720959822)     5906/8
#define FIX_0_850430095  ((INT32)  871)     // FIX(0.850430095)     6967/8
#define FIX_1_061594337  ((INT32)  1087)    // FIX(1.061594337)     8697/8
#define FIX_1_272758580  ((INT32)  1303)    // FIX(1.272758580)     10426/8
#define FIX_1_451774981  ((INT32)  1487)    // FIX(1.451774981)     11893/8
#define FIX_2_172734803  ((INT32)  2225)    // FIX(2.172734803)     17799/8
#define FIX_3_624509785  ((INT32)  3712)    // FIX(3.624509785)     29692/8
*/

/*
#define CONST_BITS  9      //13 -> 9
#define PASS1_BITS  2
#define FIX_0_298631336  ((INT32)  153)     // FIX(0.298631336)     2446/16=153
#define FIX_0_390180644  ((INT32)  200)     // FIX(0.390180644)     3196/16=200
#define FIX_0_541196100  ((INT32)  277)     // FIX(0.541196100)     4433/16=277
#define FIX_0_765366865  ((INT32)  277)     // FIX(0.765366865)     6270/16=277
#define FIX_0_899976223  ((INT32)  461)     // FIX(0.899976223)     7373/16=461
#define FIX_1_175875602  ((INT32)  602)     // FIX(1.175875602)     9633/16=602
#define FIX_1_501321110  ((INT32)  769)     // FIX(1.501321110)     12299/16=769
#define FIX_1_847759065  ((INT32)  946)     // FIX(1.847759065)     15137/16=946
#define FIX_1_961570560  ((INT32)  1004)    // FIX(1.961570560)     16069/16=1004
#define FIX_2_053119869  ((INT32)  1051)    // FIX(2.053119869)     16819/16=1051
#define FIX_2_562915447  ((INT32)  1312)    // FIX(2.562915447)     20995/16=1312
#define FIX_3_072711026  ((INT32)  1573)    // FIX(3.072711026)     25172/16=1573

#define FIX_0_211164243  ((INT32)  108)     // FIX(0.211164243)     1730/16=108
#define FIX_0_509795579  ((INT32)  261)     // FIX(0.509795579)     4176/16=261
#define FIX_0_601344887  ((INT32)  308)     // FIX(0.601344887)     4926/16=308
#define FIX_0_720959822  ((INT32)  369)     // FIX(0.720959822)     5906/16=369
#define FIX_0_850430095  ((INT32)  435)     // FIX(0.850430095)     6967/16=435
#define FIX_1_061594337  ((INT32)  544)     // FIX(1.061594337)     8697/16=544
#define FIX_1_272758580  ((INT32)  652)     // FIX(1.272758580)     10426/16=652
#define FIX_1_451774981  ((INT32)  743)     // FIX(1.451774981)     11893/16=743
#define FIX_2_172734803  ((INT32)  1112)    // FIX(2.172734803)     17799/16=1112
#define FIX_3_624509785  ((INT32)  1856)    // FIX(3.624509785)     29692/16=1856
*/

#define CONST_BITS  8      //13 -> 8
#define PASS1_BITS  2
#define FIX_0_298631336  ((INT32)  76)      // FIX(0.298631336)     2446/32=76
#define FIX_0_390180644  ((INT32)  100)     // FIX(0.390180644)     3196/32=100
#define FIX_0_541196100  ((INT32)  139)     // FIX(0.541196100)     4433/32=139
#define FIX_0_765366865  ((INT32)  196)     // FIX(0.765366865)     6270/32=196
#define FIX_0_899976223  ((INT32)  230)     // FIX(0.899976223)     7373/32=230
#define FIX_1_175875602  ((INT32)  301)     // FIX(1.175875602)     9633/32=301
#define FIX_1_501321110  ((INT32)  384)     // FIX(1.501321110)     12299/32=384
#define FIX_1_847759065  ((INT32)  473)     // FIX(1.847759065)     15137/32=473
#define FIX_1_961570560  ((INT32)  502)     // FIX(1.961570560)     16069/32=502
#define FIX_2_053119869  ((INT32)  526)     // FIX(2.053119869)     16819/32=526
#define FIX_2_562915447  ((INT32)  656)     // FIX(2.562915447)     20995/32=656
#define FIX_3_072711026  ((INT32)  787)     // FIX(3.072711026)     25172/32=787

#define FIX_0_211164243  ((INT32)  54)      // FIX(0.211164243)     1730/32=54
#define FIX_0_509795579  ((INT32)  131)     // FIX(0.509795579)     4176/32=131
#define FIX_0_601344887  ((INT32)  154)     // FIX(0.601344887)     4926/32=154
#define FIX_0_720959822  ((INT32)  185)     // FIX(0.720959822)     5906/32=185
#define FIX_0_850430095  ((INT32)  218)     // FIX(0.850430095)     6967/32=218
#define FIX_1_061594337  ((INT32)  272)     // FIX(1.061594337)     8697/32=272
#define FIX_1_272758580  ((INT32)  326)     // FIX(1.272758580)     10426/32=326
#define FIX_1_451774981  ((INT32)  372)     // FIX(1.451774981)     11893/32=372
#define FIX_2_172734803  ((INT32)  556)     // FIX(2.172734803)     17799/32=556
#define FIX_3_624509785  ((INT32)  928)     // FIX(3.624509785)     29692/32=928

// tyt's notes, 0417/2001
// for accurate rounding, select the first macro
// for faster operation, select the second macro

//#define DESCALE(x,n)                RIGHT_SHIFT((x) + (ONE << ((n)-1)), n)
#define DESCALE(x,n)  				RIGHT_SHIFT(x, n)

//#define MULTIPLY(var,const)  		((INT16)(var)) * ((INT16)(const))
#define MULTIPLY(var,const)  		((INT32)(var)) * ((INT32)(const))
//#define MULTIPLY(var,const)  		(var * const)
//#define DEQUANTIZE(coef,quantval)   (((int) (coef)) * (quantval))
#define DEQUANTIZE(coef,quantval)   (((INT32) (coef)) * (quantval))

#endif

#endif

#endif /* JPEGLIB_H */
