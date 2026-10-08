//
// fsGUI_new.h
//
//      fs9660-NEW GUI macro definition for fsGUI_NEW.c.
//
//
// 	Creator :zhaoyanhua
//	Date:    3-7-25 14:53
//
/*
#ifndef   _FS_GUI_NEW_H
#define   _FS_GUI_NEW_H


//============RGB -> YCbCr================================================
#define RGB2Y(r,g,b)  (((71*(r) + 141*g + 27*b + 0x1000)&0xFF00)>>8)
#define RGB2Cr(r,g,b) (((127*(r)-106*(g)-21*(b)+0x8000)&0xFF00)>>8)
#define RGB2Cb(r,g,b) ((((-43)*(r)-85*(g)+127*(b)+0x8000)>>8)&0xFF)

//===============fill color================================================
//preview area . when preview JPEG,draw the background with following colors.
#define PREVIEW_BKGROUND_CRCB    		(RGB2Cr( 66, 181, 181)<<8)|(RGB2Cb(66, 181, 181))
#define PREVIEW_BKGROUND_Y               0x80
//
#define DIR_AREA_BKGROUND_CRCB   		(RGB2Cr(52, 172,193)<<8)|(RGB2Cb(52, 172, 193))
#define FILE_AREA_BKGROUND_CRCB  		DIR_AREA_BKGROUND_CRCB  //(RGB2Cr(52, 172, 193)<<8)|(RGB2Cb(52, 172, 193))
//whole background color
#define BK_CRCB							(RGB2Cr(129,187,218)<<8)|(RGB2Cb(129,187,218))
//BUTTON color
#define BUTTON_CRCB						(RGB2Cr(108, 172, 206)<<8)|(RGB2Cb(108, 172, 206))
#define BUTTON_Y						 RGB2Y(108, 172, 206)

//================rectangle AREA index====================================

#define PATH_RECT  0
#define BK_RECT    1
#define DIR_RECT   2
#define FILE_RECT  3
#define PREVIEW_RECT 4
#define SHOW_JPEG_RECT 5

//=============FILE  AREA================================================
#define FILE_STEP             40
#ifdef MP3_LARGE_GUI	//Maoyong 2004.04.15
#define FILE_AREA_XSTART      366//FS_FILEICON_XSTART-2
#define FILE_AREA_YSTART      65 //In fact no use	
#define FILE_AREA_XLEN        295//JUST AS RECT FILE WIDTH
#define FILE_AREA_YLEN        300//JUST AS RECT FILE HEIGHT	
#else //#ifdef MP3_LARGE_GUI	//Maoyong 2004.04.15
#define FILE_AREA_XSTART   	  178//FS_FILEICON_XSTART-2
#define FILE_AREA_YSTART      65 //In fact no use
#define FILE_AREA_XLEN        150
#define FILE_AREA_YLEN        170
#endif //#ifdef MP3_LARGE_GUI	//Maoyong 2004.04.15

//=================others pareameter=====================================
//DIR AREA 
#define DIR_STEP              40
//for "JPEG_Preview_Drawed" value 
//zhaoyanhua add 2003-9-15 10:57
#define DIR_LIST_IN_DIR_AREA        0
#define JPEG_PREVIEW_IN_DIR_AREA    1

#ifdef	MP3_LARGE_GUI
#define ITEM_MAX_WIDTH		  216
#else	
#define ITEM_MAX_WIDTH        118  //max item width to clear.
#endif	//MP3_LARGE_GUI

// for scroll arrow.
#ifdef MP3_LARGE_GUI	//Maoyong 2004.04.15
#define  ARROW_SIZE   20 //when change this value,must change the array ArrowUP[] and ArrowDOWN[] accordingly.
#else
#define  ARROW_SIZE   11 //when change this value,must change the array ArrowUP[] and ArrowDOWN[] accordingly.
#endif
//for rectangle corner
//NOTE : when change this value,must change the array CornerLB[] CornerLT[],CornerRB[],CornerRT[] accordingly.
#define  CORNER_RAD   6 
//max step
#define MAX_STEP   70
*/

//#endif //ifndef  _FS_GUI_NEW_H


