//---------------------------------------------------------------------------
// jpeglib.h
// 
// Purpose: JPEG Decoding Function Library Include file
//
// Version: 1.0
// Compiler: GCC for MIPS(R3000)
// Platform: Sunplus SPCA720A DVD Player
// Author: Jeff Lin
// Date: 03/03/2003
// Last Revised: 03/03/2003
//
// History
//    03/03/2003 create
//     
//---------------------------------------------------------------------------

#ifndef JPEGLIB_H
#define JPEGLIB_H

#ifdef JPG_OLD_PARSER_FLOW

#include "types.h"
#include "memmap0.h"



#ifdef JPG_READ_SPEED_UP
	#include	"drv.h"		//joshua 2004.0706 for #define JPG_READ_SPEED_UP
	#include	"sinf.h"	//joshua 2004.0706 for #define JPG_READ_SPEED_UP	
#endif


//=================================================================================
//JPEG Bit-stream FIFO
//=================================================================================
#define     JPGCDBUFSTART   (SDRAM_BASE_UNCACHED+(JPEG_YA*1024))     //file working buffer
#define     JPGGVSIZE       (4*1024)        //use JPGGVSIZE Bytes as global variables
//#define     JPGCDBUFSIZE    (JPEG_CDBUF_SIZE*1024)
#define     JPGCDBUFSIZE    (JPEG_CDBUF_SIZE*1024-JPGGVSIZE)
//#define     JPGCDBUFLOW     (JPGCDBUFSIZE-40*1024)
#ifdef JPG_READ_SPEED_UP
	#define		JPGBUFALARM		(8*1024)//joshua 20040706
	#define     JPGCDBUFLOW     (JPGCDBUFSIZE-JPGBUFALARM)//joshua 20040706
#else
	#define     JPGCDBUFLOW     (JPGCDBUFSIZE-20*1024)//Jeff 20040405
#endif



//===========================================================================
// JPEG related video frame address define
//===========================================================================
//#define JPG_PS_YP   (SDRAM_BASE_UNCACHED + (GP_REF1_LUMA*1024))  //Y coefs buffer start
#define JPG_PS_YP   (SDRAM_BASE_UNCACHED + (P_JPEG_PS*1024))  //Y coefs buffer start
//=====================================
enum {
    JPGDSP_RESULT_NG = -1,
	JPGDSP_RESULT_OK = 1,
    JPGDSP_RESULT_BREAK = 2,
};



enum {
    JPG_START=0,
	JPG_STOP=1,
	JPG_WAIT_BITSTREAM,
	JPG_JFIF,
	JPG_TAG,
	JPG_SCAN,
	JPG_MCU,
	JPG_END_OF_FRAME,
    //JPG_BREAK_BY_USER,
};

#ifdef  JPG_BETTER_QUALITY
UINT16   downsample_rate;
#endif

#ifdef THUMBNAIL_BMP_GUI
#define JPGPreX         720
#define JPGPreY         480
#define JPGFullX        720
#define JPGFullY        480
#else
#define JPGPreX         720
#define JPGPreY         576
#define JPGFullX        720
#define JPGFullY        576
#endif


#endif  //JPG_OLD_PARSER_FLOW

#endif /* JPEGLIB_H */



