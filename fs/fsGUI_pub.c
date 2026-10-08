/**************************************************************
** FILE
** fsGUI_new.c
**
** DESCRIPTION
** To collect the public function in fsGUI1.c and fsGUI_new.c
**
**
**   Creator:   Freyman
** 	 Date:     2004-4-19 19:07
****************************************************************/
#include "global.h"
#include "func.h"
#include "memmap.h"
#include "util.h"
#include "graph.h"
#include "memcfg.h"
#include "framebuf.h"
#include "macro.h"
#include "stc.h"
#include "cfont.h"
#include "vfdfunc.h"
#include "osd.h"
#include "image.h"
#include "nesinit.h"
#include "fs96602.h"
#include "fsNAV.h"
#include "fsGUI.h"
#include "fsGUI1.h"
#include "user_if.h"
#include "fsGUIX.h"

#include "pic_if.h"
#include "pic_mainproc.h"


#if defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)
	#ifdef INDIGO_STYLE_FSGUI
	const BTNAREA Rect[] ={
		//path  Rect
		{( 52*NUMERATOE_X/DENOMINATOR_X), 			(40*NUMERATOE_Y/DENOMINATOR_Y),
		 (277*NUMERATOE_X/DENOMINATOR_X), 			(17*NUMERATOE_Y/DENOMINATOR_Y)},
		 
		//background Rect
		{0, 										0								,
		(352*NUMERATOE_X/DENOMINATOR_X), 			(288*NUMERATOE_Y/DENOMINATOR_Y)},
		 
		//Dir  Rect
		{( 28*NUMERATOE_X/DENOMINATOR_X), 			( 75*NUMERATOE_Y/DENOMINATOR_Y),
		 (150*NUMERATOE_X/DENOMINATOR_X),			(149*NUMERATOE_Y/DENOMINATOR_Y)},
		  
		//File Rect
		{(182*NUMERATOE_X/DENOMINATOR_X), 			( 75*NUMERATOE_Y/DENOMINATOR_Y),	
		 (150*NUMERATOE_X/DENOMINATOR_X),			(149*NUMERATOE_Y/DENOMINATOR_Y)},
		  
		//preview Rect .it is to clear the previous JPEG.
		{((28+ 10)*NUMERATOE_X/DENOMINATOR_X), 		((75+ 10)*NUMERATOE_Y/DENOMINATOR_Y),
		((150-( 10*2))*NUMERATOE_X/DENOMINATOR_X), 	((149-( 10*2))*NUMERATOE_Y/DENOMINATOR_Y)},
		
		//JPEG size When at preview state.
		{((28+10)*NUMERATOE_X/DENOMINATOR_X), 		((75+10)*NUMERATOE_Y/DENOMINATOR_Y), 
		((150-(10*2))*NUMERATOE_X/DENOMINATOR_X), 	((149-(10*2))*NUMERATOE_Y/DENOMINATOR_Y)},
		
		#ifdef SUPPORT_MULTI_PARTITION
		//multiple HDD 
			#ifdef SUPPORT_UNICODE_FONT
		{( 32*NUMERATOE_X/DENOMINATOR_X), 			( 65*NUMERATOE_Y/DENOMINATOR_Y),
		 (280*NUMERATOE_X/DENOMINATOR_X), 			(180*NUMERATOE_Y/DENOMINATOR_Y)},
			#else
		
		{( 32*NUMERATOE_X/DENOMINATOR_X), 			( 65*NUMERATOE_Y/DENOMINATOR_Y), 
		 (280*NUMERATOE_X/DENOMINATOR_X), 			(170*NUMERATOE_Y/DENOMINATOR_Y)},
			#endif
		#endif
	};
	#else //#ifdef INDIGO_STYLE_FSGUI
		#ifdef MP3_LARGE_GUI
	const BTNAREA Rect[] ={
        //path  Rect
        {120,		50,        	540,		28},

        //background Rect
        {  0,		  0,       	720,		470},

        //Dir  Rect
        { 50,		 90,       	295,		300},

        //File Rect
        {365,		 90,       	295,		300},

        //preview Rect .it is to clear the previous JPEG.
		{ 72,		100,       	245,		280},
        
        //JPEG size When at preview state.
        { 72,		100,       	245,		280}
	};
		#else //#ifdef MP3_LARGE_GUI
	const BTNAREA Rect[] ={
		//path  Rect
		{ 51,      40,			280,		17},

		//background Rect
		{ 0,      	0,			352,		280},

		//Dir  Rect
		{ 24,      65,			150,		170},

		//File Rect
		{ 178,     65,			150, 	   	170},

		//preview Rect .it is to clear the previous JPEG.
		{ 30, 	   66,			130,     	168},

		//JPEG size When at preview state.
		{ 40,     70,			120,	   	160},

			#ifdef SUPPORT_MULTI_PARTITION//liweihua 2004-8-26
		//multiple HDD 
				#ifdef SUPPORT_UNICODE_FONT ///////////yangli mod for unicode UI change bigger2005-9-29
		{ 32,     65,		280,    	180},
				#else
		{ 32,     65,		280,    	170},
				#endif
			#endif

			#ifdef FAT_FILE_MODE
		//Disk title rect
		{  24+5,      34+15,	150,	    22},
		    
		//Card title rect
		{ 178+5,     34+15,		150,		22},
		    
		//Warning rect
		{    24,      240,		304,		27},
		    
		//Disk icon rect
		{	 24,	   65,		150,		170},
		  
		//card icon rect
		{   178,     65,		150,		50},
		    
		//disk item rect
		{  24+8,     65,		150-8,     170},
			#endif
		
			#ifdef FILE_MODE_WRITE     //sunzhh 20041225
		//SRCE title rect
		{  24+5,      34+15,	150,       22},
		//DEST title rect
		{ 178+5,     34+15,		150,       22},
		//infomation rect
		{   24,        25,		304,       17},				
			#endif				
	};
		#endif //#ifdef MP3_LARGE_GUI
	#endif // INDIGO_STYLE_FSGUI
#endif //#if defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)

#ifdef FS_BMP_GUI //suqiaoli 2004-6-11
	#ifdef	GPS_MP3_UI//frank.huang 050915
	const BTNAREA fsArea[] = {	
		// background area												0
		{	0,											0, //x, y start
			720,										480}, //x-size, y-size

		// dir icon area												1
		{	DIR_AREA_XSTART + 11,						DIR_AREA_YSTART + 15,
			FS_DIRICON_XLEN,							FS_FILELIST_YSTEP},

		// dir item area												2
		{	DIR_AREA_XSTART + 5,						DIR_AREA_YSTART + 12 ,
			FS_DIRITEM_XLEN,		    				PER_PAGE * FS_FILELIST_YSTEP},

		// file icon area												3
		{	FILE_AREA_XSTART + 11,						FILE_AREA_YSTART +15 ,
			FS_FILEICON_XLEN,							FS_FILELIST_YSTEP},

		// file item area												4
		{	FILE_AREA_XSTART + 5,	    				FILE_AREA_YSTART + 12 ,
			FS_FILEITEM_XLEN,							PER_PAGE * FS_FILELIST_YSTEP},

		// file scroll bar area											5
		{	FS_DIRSCROLLLEN_XSTART + LEN_DIRFILE  ,		FS_DIESCROLLLEN_YSTART,
			1,		            						FS_DIRSCROLLLEN_YSIZE},

		// file move bar area											6
		{	FS_DIRSCROLLLEN_XSTART + LEN_DIRFILE + 7,	FS_DIESCROLLLEN_YSTART + 7  ,
			FS_DIRSCROLLLEN_XSIZE - 10,                 FS_DIRSCROLLLEN_YSIZE - 14	},

		// path info area												7
		{	132,										99,
			300,										18},
		// preview area													8
	    {   DIR_AREA_XSTART + 28,	    				DIR_AREA_YSTART ,
	        210,                        				280},

	    //button title area												9
		{	100,										45,
			0,											0},
			
	    //button title background area									10
	    {	100,										27,
	    	100,										1},

		//path background												11
		{	120,										95,
			515,										1},

		//button background												12
		{	73,											27,
			646,										1},

		// dir scroll bar area											13
		{	FS_DIRSCROLLLEN_XSTART ,					FS_DIESCROLLLEN_YSTART,
			FS_DIRSCROLLLEN_XSIZE,						FS_DIRSCROLLLEN_YSIZE},

		// dir move bar area											14
		{	FS_DIRSCROLLLEN_XSTART + 7,					FS_DIESCROLLLEN_YSTART + 7 ,
			FS_DIRSCROLLLEN_XSIZE - 10,					FS_DIRSCROLLLEN_YSIZE - 14},

		// ARTIST info area
		{	120,										50 ,
			380,										1},
		
		// time info area
		{	510,										50 ,
			124,										1},
	};
	#define MID_BAR_LOC		(fsArea[FS_AREA_PATHBACKGROUND].yStart+fsArea[FS_AREA_ARTIST_INFO].yStart)/2

	#else//ifdef GPS_MP3_UI
	const BTNAREA fsArea[] =
	{
		// background area
		{	0,										0,
			720,									480},

		// dir icon area
		{	DIR_AREA_XSTART + 11,					DIR_AREA_YSTART + 15,
			FS_DIRICON_XLEN,						FS_FILELIST_YSTEP},

		// dir item area
		{	DIR_AREA_XSTART + 5,					DIR_AREA_YSTART + 12,
			FS_DIRITEM_XLEN,		    			PER_PAGE * FS_FILELIST_YSTEP},

		// file icon area
		{	FILE_AREA_XSTART + 11,					FILE_AREA_YSTART +15,
			FS_FILEICON_XLEN,						FS_FILELIST_YSTEP},

		// file item area
		{	FILE_AREA_XSTART + 5,	    			FILE_AREA_YSTART + 12,
			FS_FILEITEM_XLEN,						PER_PAGE * FS_FILELIST_YSTEP},

		// file scroll bar area
		{	FS_DIRSCROLLLEN_XSTART + LEN_DIRFILE  ,	FS_DIESCROLLLEN_YSTART,
			FS_DIRSCROLLLEN_XSIZE,		            FS_DIRSCROLLLEN_YSIZE},

		// file move bar area
		{	FS_DIRSCROLLLEN_XSTART + LEN_DIRFILE+5,	FS_DIESCROLLLEN_YSTART + 7,
			FS_DIRSCROLLLEN_XSIZE - 10,             FS_DIRSCROLLLEN_YSIZE - 14},

		// path info area
		{	132,									84,
			300,									18},
		// preview area
	    {   DIR_AREA_XSTART + 28,	    			DIR_AREA_YSTART,
	        210,                        			280},

	    //button title area
		{	100,									45,
			0,										0},
			
	    //button title background area
	    {	100,									27,
	    	100,									1},

		//path background
		{	89,										76,
			546,									1},

		//button background
		{	73,										27,
			646,									1},

		// dir scroll bar area
		{	FS_DIRSCROLLLEN_XSTART ,				FS_DIESCROLLLEN_YSTART,
			FS_DIRSCROLLLEN_XSIZE,					FS_DIRSCROLLLEN_YSIZE},

		// dir move bar area
		{	FS_DIRSCROLLLEN_XSTART + 5,				FS_DIESCROLLLEN_YSTART + 7 ,
			FS_DIRSCROLLLEN_XSIZE - 10,				FS_DIRSCROLLLEN_YSIZE - 14},
	};
	#endif//ifdef GPS_MP3_UI
	
#elif defined(MP3_LARGE_GUI) //#ifdef FS_BMP_GUI
	const BTNAREA fsArea[] ={
	    // background area
	    {   0,                      							0,
	        720,                        						480},

	    // dir icon area
	    {   FS_DIRLIST_XSTART - 60,     						FS_DIRLIST_YSTART,
			32,													PER_PAGE*FS_FILELIST_YSTEP},

	    // dir item area
	    {   FS_DIRLIST_XSTART-20 ,      						FS_DIRLIST_YSTART,
			X1 - FS_DIRLIST_XSTART + 20,						PER_PAGE * FS_FILELIST_YSTEP},

	    // file icon area
	    {   FS_FILEICON_XSTART,         						FS_DIRLIST_YSTART,
			32,													24},
	        // file item area
	    {   FS_FILEICON_XSTART + 36,    						FS_DIRLIST_YSTART,
	        240,                        						PER_PAGE * FS_FILELIST_YSTEP},
	    // scroll bar area
	    {   FILE_AREA_XSTART+FILE_AREA_XLEN- ARROW_SIZE-2-1,    FS_DIRLIST_YSTART  ,
	        ARROW_SIZE,                 						PER_PAGE * FS_FILELIST_YSTEP},

	    // move bar area
	    {   FILE_AREA_XSTART+FILE_AREA_XLEN -ARROW_SIZE-2-1,    FS_DIRLIST_YSTART +ARROW_SIZE,
	        ARROW_SIZE,                 						PER_PAGE * FS_FILELIST_YSTEP   - ARROW_SIZE*2 },

	    // path info area
	    {   120,				50,
	        540,				28},

	#ifdef JPG_EFFECT
	    //preview help message area
	    {    60,				10,
	        600,				28},
	#else
	    // preview area
	    {   32,					236,
	        48,					36},
	#endif
	    // button area
	    {   400,				400,
	        150,				48},
	};

#elif defined(INDIGO_STYLE_FSGUI) //#ifdef FS_BMP_GUI
	const BTNAREA fsArea[] =
	{
		// background area
		{0,									0, 
		 FSGUI_SCREEN_WIDTH, 				FSGUI_SCREEN_HEIGHT},

		// dir icon area
		{FS_DIRICON_XSTART,					FS_DIRLIST_YSTART,	
		(22*NUMERATOE_X/DENOMINATOR_X), 	PER_PAGE * FS_FILELIST_YSTEP},//xingbo 200608 21->22
		
		// dir item area
		{FS_DIRLIST_XSTART,					FS_DIRLIST_YSTART,
		(118*NUMERATOE_X/DENOMINATOR_X), 	PER_PAGE * FS_FILELIST_YSTEP},
		
		// file icon area
		{FS_FILEICON_XSTART,				FS_DIRLIST_YSTART,
		(22*NUMERATOE_X/DENOMINATOR_X), 	(12*NUMERATOE_X/DENOMINATOR_X)},//xingbo 200608 21->22

		// file item area
		{FS_FILELIST_XSTART,				FS_DIRLIST_YSTART,
		(118*NUMERATOE_X/DENOMINATOR_X),	PER_PAGE * FS_FILELIST_YSTEP},
		
	#ifdef DIR_SCROLL_BAR
		// scroll bar area
		{FS_DIRSCROLL_XSTART,				FS_DIRLIST_YSTART,
		(4*NUMERATOE_X/DENOMINATOR_X), 		141 * NUMERATOE_Y/DENOMINATOR_Y},

		// move bar area
		{FS_DIRSCROLL_XSTART,				FS_DIRLIST_YSTART,
		(4*NUMERATOE_X/DENOMINATOR_X), 		141 * NUMERATOE_Y/DENOMINATOR_Y},
	#endif

		// scroll bar area
		{FS_FILESCROLL_XSTART,				FS_DIRLIST_YSTART,
		(4*NUMERATOE_X/DENOMINATOR_X), 		141 * NUMERATOE_Y/DENOMINATOR_Y},

		// move bar area
		{FS_FILESCROLL_XSTART,				FS_DIRLIST_YSTART,
		(4*NUMERATOE_X/DENOMINATOR_X), 		141 * NUMERATOE_Y/DENOMINATOR_Y},

		// path info area
		{( 30*NUMERATOE_X/DENOMINATOR_X),  	( 41*NUMERATOE_Y/DENOMINATOR_Y), 
		 (277*NUMERATOE_X/DENOMINATOR_X), 	( 15*NUMERATOE_Y/DENOMINATOR_Y)},

		// preview help message area
		{( 33*NUMERATOE_X/DENOMINATOR_X),  	( 84*NUMERATOE_Y/DENOMINATOR_Y), 
		 (138*NUMERATOE_X/DENOMINATOR_X), 	(150*NUMERATOE_Y/DENOMINATOR_Y)},

		// button area
		{( 83*NUMERATOE_X/DENOMINATOR_X),  	(239*NUMERATOE_Y/DENOMINATOR_Y),
		 ( 59*NUMERATOE_X/DENOMINATOR_X),  	( 33*NUMERATOE_Y/DENOMINATOR_Y)},

	#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
		// mp3 button area
		{( 52*NUMERATOE_X/DENOMINATOR_X),  	(239*NUMERATOE_Y/DENOMINATOR_Y),
		 ( 59*NUMERATOE_X/DENOMINATOR_X),  	( 33*NUMERATOE_Y/DENOMINATOR_Y)},

		// jpeg button area
		{(115*NUMERATOE_X/DENOMINATOR_X), 	(239*NUMERATOE_Y/DENOMINATOR_Y),
		 ( 59*NUMERATOE_X/DENOMINATOR_X),  	( 33*NUMERATOE_Y/DENOMINATOR_Y)},

		// other button area
		{(241*NUMERATOE_X/DENOMINATOR_X), 	(239*NUMERATOE_Y/DENOMINATOR_Y),
		 ( 59*NUMERATOE_X/DENOMINATOR_X),  	( 33*NUMERATOE_Y/DENOMINATOR_Y)},

		// game button area
		{(178*NUMERATOE_X/DENOMINATOR_X), 	(239*NUMERATOE_Y/DENOMINATOR_Y),
		 ( 59*NUMERATOE_X/DENOMINATOR_X),  	( 33*NUMERATOE_Y/DENOMINATOR_Y)},
	#else
		// mp3 button area
		{( 83*NUMERATOE_X/DENOMINATOR_X),  	(239*NUMERATOE_Y/DENOMINATOR_Y),
		 ( 59*NUMERATOE_X/DENOMINATOR_X),  	( 33*NUMERATOE_Y/DENOMINATOR_Y)},

		// jpeg button area
		{(146*NUMERATOE_X/DENOMINATOR_X), 	(239*NUMERATOE_Y/DENOMINATOR_Y),
		 ( 59*NUMERATOE_X/DENOMINATOR_X),  	( 33*NUMERATOE_Y/DENOMINATOR_Y)},

		// other button area
		{(209*NUMERATOE_X/DENOMINATOR_X), 	(239*NUMERATOE_Y/DENOMINATOR_Y),
		 ( 59*NUMERATOE_X/DENOMINATOR_X),  	( 33*NUMERATOE_Y/DENOMINATOR_Y)},

	#endif
	};

#else //#ifdef FS_BMP_GUI
	const BTNAREA fsArea[] =
	{
		// background area
		{	0,													0,
			352,												288},

		// dir icon area
		{	FS_DIRLIST_XSTART - 32,								FS_DIRLIST_YSTART,
			20,													PER_PAGE*FS_FILELIST_YSTEP},

	    //Maoyong 2004.06.23 HL too long will cause GUI bug when chang dir page use UP/DOWN.
	#if defined (SUPPORT_FONT_UTIL) || defined (SUPPORT_JOLIET_FORMAT)  // 2005/02/16 yltseng
		// dir item area
		{	FS_DIRLIST_XSTART -11,								FS_DIRLIST_YSTART,
			X1 - FS_DIRLIST_XSTART -4,							PER_PAGE * FS_FILELIST_YSTEP},
	#else
	    {	FS_DIRLIST_XSTART -11,								FS_DIRLIST_YSTART,
			X1 - FS_DIRLIST_XSTART-10,							PER_PAGE * FS_FILELIST_YSTEP},
	#endif
		
	#if defined(FAT_FILE_MODE)||defined(FILE_MODE_WRITE)//liweihua add 2004-11-2//sunzhh 2005-1-13
	    // file icon area
		{	FS_FILEICON_XSTART,									FS_DIRLIST_YSTART,
			12+4,												12},
	#else
		// file icon area
		{	FS_FILEICON_XSTART,									FS_DIRLIST_YSTART,
			12,													12},
	#endif//#ifdef FAT_FILE_MODE

	#ifdef NEW_MP3_GUI
	    #if defined(FAT_FILE_MODE)||defined(FILE_MODE_WRITE)//liweihua add 2004-11-2//sunzhh 2005-1-13
	    // file item area
		{	FS_FILEICON_XSTART + 15 +2+4,	   					FS_DIRLIST_YSTART,
			120,												PER_PAGE * FS_FILELIST_YSTEP},
	    #else
			// file item area
		{	FS_FILEICON_XSTART + 15 +2,	   						FS_DIRLIST_YSTART,
			120,												PER_PAGE * FS_FILELIST_YSTEP},
	    #endif//#ifdef FAT_FILE_MODE

		#ifdef DIR_SCROLL_BAR
		// scroll bar area
		{	FS_DIRLIST_XSTART+FILE_AREA_XLEN-48,				FS_DIRLIST_YSTART - 1,
			ARROW_SIZE,											PER_PAGE * FS_FILELIST_YSTEP},

		// move bar area
		{	FS_DIRLIST_XSTART+FILE_AREA_XLEN-48,				FS_DIRLIST_YSTART +ARROW_SIZE,
			ARROW_SIZE,											PER_PAGE * FS_FILELIST_YSTEP - 2 - ARROW_SIZE*2 },
		#endif
		// scroll bar area
		{	FILE_AREA_XSTART+FILE_AREA_XLEN- ARROW_SIZE-1-1,	FS_DIRLIST_YSTART - 1,
			ARROW_SIZE,											PER_PAGE * FS_FILELIST_YSTEP},

		// move bar area
		{	FILE_AREA_XSTART+FILE_AREA_XLEN -ARROW_SIZE-1-1,	FS_DIRLIST_YSTART +ARROW_SIZE,
			ARROW_SIZE,											PER_PAGE * FS_FILELIST_YSTEP - 2 - ARROW_SIZE*2 },

	#else
		// file item area
		{	FS_FILEICON_XSTART + 15,							FS_DIRLIST_YSTART,
			120,												PER_PAGE * FS_FILELIST_YSTEP},

		#ifdef DIR_SCROLL_BAR
		// scroll bar area
		{	FS_DIRLIST_XSTART+FILE_AREA_XLEN-50,				FS_DIRLIST_YSTART - 1,
			ARROW_SIZE+2,										PER_PAGE * FS_FILELIST_YSTEP},

		// move bar area
		{	FS_DIRLIST_XSTART+FILE_AREA_XLEN-48,				FS_DIRLIST_YSTART +ARROW_SIZE,
			ARROW_SIZE,											PER_PAGE * FS_FILELIST_YSTEP - 2 - ARROW_SIZE*2 },
		#endif

		// scroll bar area
		{	320,												FS_DIRLIST_YSTART - 1,
			8,													PER_PAGE * FS_FILELIST_YSTEP},

		// move bar area
		{	321,												FS_DIRLIST_YSTART,
			6,													PER_PAGE * FS_FILELIST_YSTEP - 2},
	#endif
		// path info area
		#ifdef HANYANG_FS_LONGNAME
		{	14,				Y1 - 18,
			200,			18},
		#else
		{	25,				Y1 - 18,
			300,			18},
		#endif

	#ifdef NEW_MP3_GUI//nono 2004-4-29 23:28
		//preview help message area
		{	60,				20,
			260,			16},
	#else
		// preview area
		{	32,				236,
			48,				36}, // xSize : ySize = 4 : 3
	#endif

	#ifdef FILE_MODE_WRITE    //sunzhh 20041225
		// button area
		{	90,				245,
			82,				25},		
	#else
		// button area
		{	180,			245,
			82,				25},
	#endif
			
		#ifdef FAT_FILE_MODE//liweihua 2004-10-9 21:59
		// disk icon area
		{	FS_DIRLIST_XSTART - 26-8,		FS_DIRLIST_YSTART,
			20,								PER_PAGE*FS_FILELIST_YSTEP},

		// disk list area
	    //Maoyong 2004.06.23 HL too long will cause GUI bug when chang dir page use UP/DOWN.
	    	#if defined (SUPPORT_FONT_UTIL) || defined (SUPPORT_JOLIET_FORMAT)  // 2005/02/16 yltseng
		{	FS_DIRLIST_XSTART - 5-8,		FS_DIRLIST_YSTART,
			X1 - FS_DIRLIST_XSTART + 6,		PER_PAGE * FS_FILELIST_YSTEP},
	    	#else
	    {	FS_DIRLIST_XSTART - 5-8,		FS_DIRLIST_YSTART,
			X1 - FS_DIRLIST_XSTART,			PER_PAGE * FS_FILELIST_YSTEP},
	    	#endif

		//warning message area
		{	24+5,      		240+5,
			304-5,    		27-5},
		//dir slot area
		{	FS_DIRSCROLLLEN_XSTART ,		FS_DIESCROLLLEN_YSTART,
			FS_DIRSCROLLLEN_XSIZE,			FS_DIRSCROLLLEN_YSIZE},
		
		//dir movebar area
		{	FS_DIRSCROLLLEN_XSTART + 5,		FS_DIESCROLLLEN_YSTART + 7 ,
			FS_DIRSCROLLLEN_XSIZE - 10,		FS_DIRSCROLLLEN_YSIZE - 14},
		#endif
			
		#ifdef FILE_MODE_WRITE//sunzhh 2004-12-25
		// disk icon area
		{	FS_DIRLIST_XSTART - 26-8,		FS_DIRLIST_YSTART,
			20,								PER_PAGE*FS_FILELIST_YSTEP},
		// disk list area
	    //Maoyong 2004.06.23 HL too long will cause GUI bug when chang dir page use UP/DOWN.
	    	#if defined (SUPPORT_FONT_UTIL) || defined (SUPPORT_JOLIET_FORMAT)  // 2005/02/16 yltseng
		{	FS_DIRLIST_XSTART - 5-8,		FS_DIRLIST_YSTART,
			X1 - FS_DIRLIST_XSTART + 6,		PER_PAGE * FS_FILELIST_YSTEP},
	    	#else
	    {	FS_DIRLIST_XSTART - 5-8,		FS_DIRLIST_YSTART,
			X1 - FS_DIRLIST_XSTART,			PER_PAGE * FS_FILELIST_YSTEP},
	    	#endif

		//warning message area
		{   30,                         	26,
		    304,                        	17},	
		    
		//dir slot area
		{	FS_DIRSCROLLLEN_XSTART ,		FS_DIESCROLLLEN_YSTART,
			FS_DIRSCROLLLEN_XSIZE,			FS_DIRSCROLLLEN_YSIZE},

		//dir movebar area
		{	FS_DIRSCROLLLEN_XSTART + 5,		FS_DIESCROLLLEN_YSTART + 7,
			FS_DIRSCROLLLEN_XSIZE - 10,		FS_DIRSCROLLLEN_YSIZE - 14},
		#endif //#ifdef FILE_MODE_WRITE
	};
#endif //#ifdef FS_BMP_GUI


#ifdef APEX_MP3_ICON
const BYTE mp3fileIcon[24][72] =
{
 {0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, },
 {0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, },
 {0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, },
 {0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, },
 {0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, },
 {0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, },
 {0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, },
 {0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, },
 {0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, },
 {0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, },
 {0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0xff, 0xff, 0xff, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, },
 {0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, },
 {0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, },
 {0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, },
 {0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, },
 {0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, },
 {0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, },
 {0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, },
 {0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, },
 {0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0xff, 0xff, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0xff, 0xff, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0xff, 0xff, 0x57, 0x57, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, },
 {0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0x57, 0xff, 0xff, 0x57, 0xff, 0xff, 0x57, 0xff, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, },
 {0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0x57, 0x57, 0xff, 0x57, 0xff, 0xff, 0x57, 0xff, 0x57, 0x57, 0xff, 0x57, 0xff, 0xff, 0x57, 0x57, 0xff, 0xff, 0x57, 0x57, 0xff, 0x57, 0x57, 0xff, 0x57, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, },
 {0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0x57, 0xff, 0xff, 0x57, 0xff, 0xff, 0x57, 0xff, 0xff, 0x57, 0xff, 0x57, 0xff, 0xff, 0x57, 0x57, 0xff, 0xff, 0x57, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, },
 {0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0x57, 0xff, 0xff, 0x57, 0x57, 0xff, 0xff, 0xff, 0x57, 0xff, 0xff, 0x57, 0x57, 0xff, 0xff, 0x57, 0x57, 0xff, 0x57, 0x57, 0xff, 0x57, 0xff, 0xff, 0xff, 0xff, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, 0x57, },
};
#endif//APEX_MP3_ICON



#ifdef GPS_MP3_UI
   #include "icon.h"
   char timebuf[5]={0};//sunxin 050922 add for show time and play_state
#endif

#ifdef MP3_POWER_RESUME //0//def POWER_RESUME//mp3 power_resume need to be fix again later.
	extern UINT32 ReadSameMP3Para ( UINT8 para ) ;
	extern UINT8 IsTheSameMP3 ( void ) ;
#endif   // POWER_RESUME , added by caiyh , 14:12 , Nov 5th , 2004

#ifdef JPG_OLD_PARSER_FLOW
    #ifdef JPG_EFFECT
    #include "jpegeffect.h"
    #endif
#else
    #include "pic_effect.h"
#endif

#ifdef FS_BMP_GUI
#include "fsGUI_BmpUI.h"
#endif

#ifdef SHUFFLE_ACCOMPLISH_BY_ARITHMETIC
#include"shuffle_new.h"
#endif

#ifdef SUPPORT_OTHER_FILES_SSCREEN//add for alco
extern int get_rtc_val(void);
#endif
#ifdef SHOW_CDROM_TOTAL_FILE//add for alco
extern UINT16 mp3_file_count(void);
#endif

//2006-06-02, mimitsai add for HD ui.move to fsGUIArea.h

////////////////////////////module global functions for internal reference/////////////////////////
//void    DirList();
//void    FileList(void);

void    DrawFolderIcon(int x, int y, BYTE type);
void    ShowDirItem(int iItem, const char *s);
//void    FSShowDirIcon(void);
//void    ShowFileIcon(void);

//2006-03-16, mimitsai modify
#if (defined(NEW_MP3_GUI)|| defined(INDIGO_STYLE_FSGUI)) && !defined(MP3_LARGE_GUI)
void    DrawScroll(UINT8 area);
#else
	void    DrawScroll(); //2006-03-23, mimitsai add
#endif
void    ClearArea(UINT16 iIndex);
void    SelectHL();
void    ShowButtonHL(int x, int y,int len);
void    FSGUI_FlashFileIcon(int iFlash);

void	DrawButton(void);
#if defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)
void	ShowHL(void);
void    DrawFileIconX(int x, int y, int type, int mono);
#define DrawFileIcon(x,y,t) DrawFileIconX(x,y,t,0)
    #ifdef PHILIPS_FSGUI//chenzhao20050613
    UINT16  file_focus_y = FS_FONTCOLOR_FILE_Y;
    UINT16  file_focus_CrCb = FS_FONTCOLOR_FILE_CrCb;
    #endif
#elif defined FS_BMP_GUI//zhaoyanhua add 2004-6-8 10:15
void ShowHL(void);
void    DrawFileIcon(int x, int y, int type);
UINT16  file_focus_y = FS_FONTCOLOR_FILE_Y;
UINT16  file_focus_CrCb = FS_FONTCOLOR_FILE_CrCb;
#else
void    ShowHL(int x, int y,int len,int high);
void    DrawFileIcon(int x, int y, int type);
#endif

UINT16  CountSpecifyFile(int iDir);
//int     PrepareForChangeFilePage(UINT16 iPage, UINT16 iSpecialTrk,UINT16 iDirect);
//void    CalcDirNow(UINT16 *iDir);

///////////for MP3_Lyrics_Drawed////////////////////
#ifdef MP3_TXT_DISPLAY
extern UINT16 MP3TotalNo;
extern BYTE MP3_Lyrics_Drawed;
extern void ShowLyricsWhileHL(void);
#endif
///////////////////////////////////////////////////////////////////////
#if defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)
void   DrawArrow(int xStart, int yStart, BYTE updown);
void	FSGUI_CalcuteDirFileScrollLen();

void   ShowPlayFrame(int x, int y,int len,int high);
void   ShowCurrentDirPlaying();
void   ShowCurrentFilePlaying();

#elif defined (FS_BMP_GUI)//zhaoyanhua 2004-6-8 10:15
//temp has the same function with NEW_MP3_GUI.
//we will modify the functions later.
void   ShowPlayFrame(int x, int y,int len,int high);
void   ShowCurrentDirPlaying();
void   ShowCurrentFilePlaying();
#endif
///////////////////////////////////////////////////////////////////////

#ifdef APEX_MP3_ICON
void    DrawMp3ApexIcon(int x, int y);
#endif//#ifdef APEX_MP3_ICON
//======================================================================
#ifdef FSGUI_NO_BLINK_SCROLL
void MoveScroll(UINT16 , INT8);
#else
	//2006-03-16, mimitsai modify
	#if (defined(NEW_MP3_GUI)||defined(INDIGO_STYLE_FSGUI)) && !defined(MP3_LARGE_GUI)
		void MoveScroll(UINT16, UINT8);
	#else
		void MoveScroll(UINT16);
	#endif
#endif

#ifdef HANYANG_LR_CHANGE_PAGE
//When enter in DIR area, right to file area
void FSGUI_Dir2FileArea(void);
void FSGUI_File2DirArea(void);
#endif

#ifdef	GPS_MP3_UI//suxin 050923
void FSGUI_DisplayState();
void FSGUI_Displaytime();
#endif

#ifdef AUDIO_SHOW_SAVER
BYTE    bDisableGUI = 0;
#endif
//David add 2004-01-05
#ifdef FSGUI_NO_BLINK_SCROLL
BYTE up_down_done=0;
char tempbuf[22];
#define SCROLLBAR_UP 1
#define SCROLLBAR_REFRESH 0
#define SCROLLBAR_DOWN -1
#endif

extern BYTE jpg_break_up_down;	//Maoyong 2004.04.19

//===================================================================
//zhaoyanhua new add 3-7-25 15:16
//for HL
#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
int    fsnav_dir_HL =0; //save the current playing dir
int    fsnav_file_HL=0; //save the current playing file
int    HL_Width =0, HL_Heighth = HL_RECT_HEIGHTH;//HL width and heighth.
int    old_ControlArea=0; //record last ControlArea.
int    HL_show=0;//record HL .

//
// a flag to avoid blinkling when show JPEG.
// when show the first JPEG , need draw the whole rectangle.
// But the following JPEG will only  clear the part of the rectangle.
BYTE   JPEG_Preview_drawed = DIR_LIST_IN_DIR_AREA;
BYTE   flagRefresh;
#endif
//===================================================================

//2006-06-02, mimitsai add for HD ui.
int is_show_path_info_string;

#ifndef JPG_OLD_PARSER_FLOW

void FSNav_JPEGInit()
{
    AUDIF_Set_Stop();//2004AUDDRV AudioSetStop();
    
    #ifdef SUPPORT_JPEG_MIC     	    	
        chg_dsp_codec_addr(1);
    #endif
    
    cd_subtype = CDROM_JPEG;
	pFsJpeg->gifsFuncBtn = FS_FUNC_JPEG;
#ifdef	DVD_SERVO	
	hostx_servo_buf_init();
#endif	// DVD_SERVO
    pFsJpeg->gbfsSlide = 0;
    pFsJpeg->g_nJpegMode = JPEG_NORMAL_MODE; // Robert 20020508. Default mode is normal mode.
    disp_time = 0;
    show_time();
    resumeMSF = 0;
    pFsJpeg->fsnav_dir_will = 0;

	pFsJpeg->file_current = pFsJpeg->file_will = 0; //Robert 031020
	FSGUI_JpgUpdateOSD();

    FSGUI_PreChangeDir(&(pFsJpeg->fsnav_dir_will), 0);
    pFsJpeg->fsnav_dir_now = pFsJpeg->fsnav_dir_will;
 
    dsp3_stop(); //halt DSP, JPEG module use some temp buffer shared with DSP, Jeff 20030502

    #if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
    	FSGUI_Refresh();
    #endif
}

#endif//#ifndef JPG_OLD_PARSER_FLOW

#ifdef SUPPORT_FILE_SYSTEM_MODE
extern UINT16 IsOtherStatePlayMode(void);
#endif

void DrawRect(int x, int y, int xSize, int ySize, UINT16 selected, UINT16 color_Y, UINT16 color_CrCb)
{
	#ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
	#endif

	FSGUI_FillFrameBuf(x, y, xSize, ySize, color_Y, color_CrCb);

	if (selected == 1)
	{
		// rect selected
		FSGUI_FillFrameBuf(x, y, xSize, DEMENSION_SIZE, BLACK_Y, BLACK_CRCB);
		FSGUI_FillFrameBuf(x, y, DEMENSION_SIZE, ySize, BLACK_Y, BLACK_CRCB);
		FSGUI_FillFrameBuf(x + xSize - DEMENSION_SIZE, y + DEMENSION_SIZE, DEMENSION_SIZE, ySize - DEMENSION_SIZE, WHITE_Y, WHITE_CRCB);
		FSGUI_FillFrameBuf(x + DEMENSION_SIZE, y + ySize - DEMENSION_SIZE, xSize - DEMENSION_SIZE, DEMENSION_SIZE ,WHITE_Y, WHITE_CRCB);
	}
	else
	{
		// rect release
		FSGUI_FillFrameBuf(x, y, xSize, DEMENSION_SIZE, WHITE_Y, WHITE_CRCB);
		FSGUI_FillFrameBuf(x, y, DEMENSION_SIZE, ySize, WHITE_Y, WHITE_CRCB);
		FSGUI_FillFrameBuf(x + xSize - DEMENSION_SIZE, y, DEMENSION_SIZE, ySize, BLACK_Y, BLACK_CRCB);
		FSGUI_FillFrameBuf(x, y + ySize - DEMENSION_SIZE, xSize ,DEMENSION_SIZE ,BLACK_Y, BLACK_CRCB);
	}
}
#ifdef INDIGO_STYLE_FSGUI
extern void DrawBottomOutLine(UINT16 x, UINT16 y, UINT16 wid, UINT16 hei, UINT8 color_y, UINT16 color_cbcr);
extern void DrawSelectedBottomOutLine(UINT16 x, UINT16 y, UINT16 wid, UINT16 hei);
void DrawButton(void)
{
	//printf_w("finish draw file icon bottom\n\n");
	DrawFileIcon(fsArea[FS_AREA_MP3_BUTTON].xStart  +BTN_XOFFSET_FROM_OUTLINE,
				 fsArea[FS_AREA_MP3_BUTTON].yStart  +BTN_YOFFSET_FROM_OUTLINE,
				 CNT_TAB_MP3BUTTON   - 2);
	DrawFileIcon(fsArea[FS_AREA_JPG_BUTTON].xStart  +BTN_XOFFSET_FROM_OUTLINE,
				 fsArea[FS_AREA_JPG_BUTTON].yStart  +BTN_YOFFSET_FROM_OUTLINE,
				 CNT_TAB_JPEGBUTTON  - 2);
	DrawFileIcon(fsArea[FS_AREA_OTHER_BUTTON].xStart+BTN_XOFFSET_FROM_OUTLINE,
				 fsArea[FS_AREA_OTHER_BUTTON].yStart+BTN_YOFFSET_FROM_OUTLINE,
				 CNT_TAB_OTHERBUTTON - 2);
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
	DrawFileIcon(fsArea[FS_AREA_GAME_BUTTON].xStart +BTN_XOFFSET_FROM_OUTLINE,
				 fsArea[FS_AREA_GAME_BUTTON].yStart +BTN_YOFFSET_FROM_OUTLINE,
				 CNT_TAB_GAMEBUTTON - 2);
#endif

	int iconType;
	if(pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)			iconType = FS_AREA_MP3_BUTTON;
	else if(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)	iconType = FS_AREA_JPG_BUTTON;
	else if(pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)	iconType = FS_AREA_OTHER_BUTTON;
	else if(pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)	iconType = FS_AREA_OTHER_BUTTON;
	

	if(pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
		DrawSelectedBottomOutLine(fsArea[FS_AREA_MP3_BUTTON].xStart,
								  fsArea[FS_AREA_MP3_BUTTON].yStart,
								  fsArea[FS_AREA_MP3_BUTTON].xSize,
								  fsArea[FS_AREA_MP3_BUTTON].ySize);	
	else
		DrawBottomOutLine(		  fsArea[FS_AREA_MP3_BUTTON].xStart,
						  		  fsArea[FS_AREA_MP3_BUTTON].yStart, 
						  		  fsArea[FS_AREA_MP3_BUTTON].xSize,
						  		  fsArea[FS_AREA_MP3_BUTTON].ySize,
						  		  HIGHLIGHT_BG_COLOR_Y, HIGHLIGHT_BG_COLOR_CbCr);

	if(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)	
		DrawSelectedBottomOutLine(fsArea[FS_AREA_JPG_BUTTON].xStart,
								  fsArea[FS_AREA_JPG_BUTTON].yStart,
								  fsArea[FS_AREA_JPG_BUTTON].xSize,
								  fsArea[FS_AREA_JPG_BUTTON].ySize);	
	else
		DrawBottomOutLine(		  fsArea[FS_AREA_JPG_BUTTON].xStart,
						  		  fsArea[FS_AREA_JPG_BUTTON].yStart,
						  		  fsArea[FS_AREA_JPG_BUTTON].xSize,
						  		  fsArea[FS_AREA_JPG_BUTTON].ySize,
						  		  HIGHLIGHT_BG_COLOR_Y, HIGHLIGHT_BG_COLOR_CbCr);
	
	if(pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)	
		DrawSelectedBottomOutLine(fsArea[FS_AREA_OTHER_BUTTON].xStart,
								  fsArea[FS_AREA_OTHER_BUTTON].yStart,
								  fsArea[FS_AREA_OTHER_BUTTON].xSize, 
								  fsArea[FS_AREA_OTHER_BUTTON].ySize);	
	else
		DrawBottomOutLine(		  fsArea[FS_AREA_OTHER_BUTTON].xStart,
								  fsArea[FS_AREA_OTHER_BUTTON].yStart,
								  fsArea[FS_AREA_OTHER_BUTTON].xSize,
								  fsArea[FS_AREA_OTHER_BUTTON].ySize,
								  HIGHLIGHT_BG_COLOR_Y, HIGHLIGHT_BG_COLOR_CbCr);
	
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
	if(pFsJpeg->gifsFuncBtn == FS_FUNC_GAME)	
		DrawSelectedBottomOutLine(fsArea[FS_AREA_GAME_BUTTON].xStart,
								  fsArea[FS_AREA_GAME_BUTTON].yStart,
								  fsArea[FS_AREA_GAME_BUTTON].xSize,
								  fsArea[FS_AREA_GAME_BUTTON].ySize);	
	else
		DrawBottomOutLine(		  fsArea[FS_AREA_GAME_BUTTON].xStart,
							      fsArea[FS_AREA_GAME_BUTTON].yStart, 
							      fsArea[FS_AREA_GAME_BUTTON].xSize,
							      fsArea[FS_AREA_GAME_BUTTON].ySize,
							      HIGHLIGHT_BG_COLOR_Y, HIGHLIGHT_BG_COLOR_CbCr);
#endif
}

#else

#if !defined(FS_BMP_GUI)&& !defined(MP3_LARGE_GUI)
void DrawButton(void)
{
	#ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
	#endif

	#ifdef APEX_MP3_ICON
	DrawMp3ApexIcon(fsArea[FS_AREA_BUTTON].xStart -90, fsArea[FS_AREA_BUTTON].yStart );
	#endif

	//draw MP3 icon
	if (pFsJpeg->gifsMP3Count)
	{
	    #ifdef MP3_NOICON     //caohui 2004-4-23 06:36

		DrawRect(fsArea[FS_AREA_BUTTON].xStart+40, fsArea[FS_AREA_BUTTON].yStart-205,
			50, 17,
			pFsJpeg->gifsFuncBtn == FS_FUNC_MP3 ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);

	    #else

		DrawRect(fsArea[FS_AREA_BUTTON].xStart, fsArea[FS_AREA_BUTTON].yStart,
			25, 25,
			pFsJpeg->gifsFuncBtn == FS_FUNC_MP3 ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);

	    #endif
	}
	else
	{
		#ifdef MP3_NOICON //caohui 2004-4-23 06:36

		FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart+48, fsArea[FS_AREA_BUTTON].yStart-205,
			50, 17,
			BK_GROUNDY, BK_GROUNDCRCB);

	   #else

		FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart, fsArea[FS_AREA_BUTTON].yStart,
			25, 25,
			BK_GROUNDY, BK_GROUNDCRCB);

		#endif
	}


#ifdef MP3_NOICON   //2004-4-17 01:05张宇P
	strcpy(linebuf, "MP3");

	FSGUI_ShowString(fsArea[FS_AREA_BUTTON].xStart + 50,
			fsArea[FS_AREA_BUTTON].yStart -204,
			linebuf, FS_FONTCOLOR_FILE_Y1, FS_FONTCOLOR_FILE_CrCb1);

#else
	DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 6, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MP3BUTTON - 2);
#endif

#ifdef HJ_APEX_ONLY_SHOW_MP3_ICON_WHEN_NO_JPG//nono 20031018
	if (pFsJpeg->gifsJPEGCount)
	{
#endif

	//draw JPEG icon
	if (pFsJpeg->gifsJPEGCount)
	{
	    #ifdef MP3_NOICON     //caohui 2004-4-23 06:36
		{
		DrawRect(fsArea[FS_AREA_BUTTON].xStart + 92, fsArea[FS_AREA_BUTTON].yStart-205, 50, 17,
			pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
	   	}
	   	#else
	   	{
			DrawRect(fsArea[FS_AREA_BUTTON].xStart + 27, fsArea[FS_AREA_BUTTON].yStart, 25, 25, pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG ? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
		}
	   	#endif
	}
	else
	{
	    #ifdef MP3_NOICON     //caohui 2004-4-23 06:36
		{
		FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 92, fsArea[FS_AREA_BUTTON].yStart,
			50, 15,
			BK_GROUNDY, BK_GROUNDCRCB);
		}
		#else
		{
			FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 27, fsArea[FS_AREA_BUTTON].yStart, 25, 25, BK_GROUNDY, BK_GROUNDCRCB);
		}
		#endif
	}

    #ifdef MP3_NOICON    //2004-4-17 01:07张宇P
	psprintf(linebuf, "JPEG");//, "M", s);

	FSGUI_ShowString(fsArea[FS_AREA_BUTTON].xStart + 92+4,
			fsArea[FS_AREA_BUTTON].yStart -204,
			linebuf, FS_FONTCOLOR_FILE_Y1, FS_FONTCOLOR_FILE_CrCb1);
	#else
	DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 33, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_JPEGBUTTON - 2);
    #endif

#ifdef HJ_APEX_ONLY_SHOW_MP3_ICON_WHEN_NO_JPG//nono 20031018
  	}//if (pFsJpeg->gifsJPEGCount)
#endif

#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)

#ifdef HJ_APEX_ONLY_SHOW_MP3_ICON_WHEN_NO_JPG//nono 20031018
  	if (pFsJpeg->gifsGAMECount)
#endif
  	{
	//draw GAME icon
	if (pFsJpeg->gifsGAMECount)
	{
		DrawRect(fsArea[FS_AREA_BUTTON].xStart + 54,fsArea[FS_AREA_BUTTON].yStart, 25, 25,
			pFsJpeg->gifsFuncBtn == FS_FUNC_GAME? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
	}
	else
	{
		FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 54, fsArea[FS_AREA_BUTTON].yStart,
			25, 25,
			BK_GROUNDY, BK_GROUNDCRCB);
	}
	DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 60, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_GAMEBUTTON - 2);

  	}//if (pFsJpeg->gifsGAMECount)

#endif//#ifdef SUPPORT_NESGAME


#ifdef SUPPORT_FILE_SYSTEM_MODE
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)

#ifdef HJ_APEX_ONLY_SHOW_MP3_ICON_WHEN_NO_JPG
  	if (pFsJpeg->gifsOtherCount)
#endif
  	{

	if (pFsJpeg->gifsOtherCount)
	{
		DrawRect(fsArea[FS_AREA_BUTTON].xStart + 81, fsArea[FS_AREA_BUTTON].yStart, 25, 25,
			pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
	}
	else
	{
		FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 81, fsArea[FS_AREA_BUTTON].yStart,
			25, 25,
			BK_GROUNDY, BK_GROUNDCRCB);
	}
	DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 87, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_OTHERBUTTON - 2);

  	}//if (pFsJpeg->gifsOtherCount)

#else//#ifdef SUPPORT_NESGAME

#ifdef HJ_APEX_ONLY_SHOW_MP3_ICON_WHEN_NO_JPG
  	if (pFsJpeg->gifsOtherCount)
#endif
  	{

	if (pFsJpeg->gifsOtherCount)
	{
		DrawRect(fsArea[FS_AREA_BUTTON].xStart + 54, fsArea[FS_AREA_BUTTON].yStart, 25, 25,
			pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
	}
	else
	{
		FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 54, fsArea[FS_AREA_BUTTON].yStart,
			25, 25,
			BK_GROUNDY, BK_GROUNDCRCB);
	}
	DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 60, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_OTHERBUTTON - 2);

  	}//if (pFsJpeg->gifsOtherCount)

#endif//#ifdef SUPPORT_NESGAME
#endif//#ifdef SUPPORT_FILE_SYSTEM_MODE

#if defined(SUPPORT_MIDI)&&defined(SHOW_MIDI_ICON)//axel 2004/8/8
    #if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)

	if (pFsJpeg->gifsMidiCount)
	{
		DrawRect(fsArea[FS_AREA_BUTTON].xStart + 108, fsArea[FS_AREA_BUTTON].yStart,
			25, 25,
			pFsJpeg->gifsFuncBtn == FS_FUNC_MIDI? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
	}
	else
	{
		FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 108, fsArea[FS_AREA_BUTTON].yStart,
			25, 25,
			BK_GROUNDY, BK_GROUNDCRCB);
	}
	DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 114, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MIDIBUTTON - 2);
#else
        if (pFsJpeg->gifsMidiCount)
        {
            DrawRect(fsArea[FS_AREA_BUTTON].xStart + 81, fsArea[FS_AREA_BUTTON].yStart,
                25, 25,
                pFsJpeg->gifsFuncBtn == FS_FUNC_MIDI? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
        }
        else
        {
            FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 108, fsArea[FS_AREA_BUTTON].yStart,
                25, 25,
                BK_GROUNDY, BK_GROUNDCRCB);
        }
        DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 87, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_MIDIBUTTON - 2);
    #endif
#endif

#ifdef SUPPORT_PLAYLIST	//wanghaoying 2005-9-28 19:23
    #if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
    #define POFFSET 27
    #else
    #define POFFSET 0
    #endif
    
    if (pFsJpeg->gifsPlayListCount)
    {
        DrawRect(fsArea[FS_AREA_BUTTON].xStart + 81 + POFFSET, fsArea[FS_AREA_BUTTON].yStart,
            25, 25,
            pFsJpeg->gifsFuncBtn == FS_FUNC_PLAYLIST? 1 : 0, BK_GROUNDY, BK_GROUNDCRCB);
    }
    else
    {
        FSGUI_FillFrameBuf(fsArea[FS_AREA_BUTTON].xStart + 81 + POFFSET, fsArea[FS_AREA_BUTTON].yStart,
            25, 25,
            BK_GROUNDY, BK_GROUNDCRCB);
    }
    DrawFileIcon(fsArea[FS_AREA_BUTTON].xStart + 87 + POFFSET, fsArea[FS_AREA_BUTTON].yStart + 6, CNT_AREA_PLAYLISTBUTTON - 2);
#endif

	return;
}
#endif //#if !defined(FS_BMP_GUI)&& !defined(MP3_LARGE_GUI)

#endif//#ifdef INDIGO_STYLE_FSGUI

#include "fsgui_icon_discx.inc"


#ifdef INDIGO_STYLE_FSGUI
void FSGUI_RotateDiscIcon(int iRotate)
{
    int x = fsArea[FS_AREA_PATHINFO].xStart; //2006-06-02, mimitsai add for HD ui.
    int y = fsArea[FS_AREA_PATHINFO].yStart;
    if (iRotate) iRotate=1;

	if(iRotate)
    	FSGUI_DrawIcon(x, y, ICON_Disc1X, DISC1_Y, DISC1_CbCr, 0);
	else
		FSGUI_DrawIcon(x, y, ICON_Disc2X, DISC2_Y, DISC2_CbCr, 0);
}

#elif defined(NEW_MP3_GUI)
//#ifdef NEW_MP3_GUI // mimitsai modify for new GUI 11.22
//#if !defined (FS_BMP_GUI)
void FSGUI_RotateDiscIcon(int iRotate)
{
    #ifdef PMP_UI//liweihua 2005-1-5
    #ifdef UNSHOW_FSGUI_ROTATEDISCICON              //////////yangli modify for samboo 2005/7/12
    return;
    #endif
    int x = fsArea[FS_AREA_DIRICON].xStart + 610;
    #else
    int x = fsArea[FS_AREA_DIRICON].xStart;
    #endif
    int y = Y1 - 17;

    //wanghaoying 2004-8-3 11:40, different defination different position.
    #ifdef MP3_LARGE_GUI
    x = x + 20;
    y = y - 19;
    #endif

    static  const   UINT8   cluty[2][4] = {
        {BK_GROUNDY, BLACK_Y, YELLOW_Y, RED_Y},
        {BK_GROUNDY, BLACK_Y, RED_Y, YELLOW_Y},
    };
    static  const   UINT16  clutc[2][4] = {
        {BK_GROUNDCRCB, BLACK_CRCB, YELLOW_CRCB, RED_CRCB},
        {BK_GROUNDCRCB, BLACK_CRCB, RED_CRCB, YELLOW_CRCB},
    };

	#ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
	#endif

    if (iRotate) iRotate=1;
    FSGUI_DrawIcon(x, y, ICON_DiscX, cluty[iRotate], clutc[iRotate], 0);
}

#else //#if !defined (FS_BMP_GUI)
/*
 * Description:
 *      Draw all rotate disc 2 icons
 * INPUT:
 *	To change the iRotate factor in polling_mp3(),
 *	It decides to show different icons each time,so it looks like rotating the icon.
 *Creater:
 *	feeling
 *Date: 2004-06-08
 * Update : zhaoyanhua 2004-6-28 14:51
 *
 */
extern void FSGUI_DrawReverseBmp(UINT16 xStart, UINT16 yStart, BYTE iLayoutIndex, BYTE iMode);
void FSGUI_RotateDiscIcon(int iRotate __attribute__((unused)))
{
    BYTE iBmpIndex = 0;

#ifdef	GPS_MP3_UI//frank.huang 050923
	switch(pFsJpeg->gifsFuncBtn)
		{
		case FS_FUNC_MP3:
			iBmpIndex = MP3_PAGE_ICON;
			break;
		case FS_FUNC_JPEG:
			iBmpIndex = JPEG_PAGE_ICON;
			break;
		case FS_FUNC_OTHER:
			iBmpIndex = VIDEO_PAGE_ICON;
			break;
		}
	FSGUI_LayoutBmp(iBmpIndex);

#else//ifdef	GPS_MP3_UI
    switch(iRotate)
    {
        case 0:
            iBmpIndex = LAY_ANIMATION1;
            FSGUI_LayoutBmp(iBmpIndex);
            break;
        case 1:
            iBmpIndex = LAY_ANIMATION2;
            FSGUI_DrawReverseBmp(
                                fsArea[FS_AREA_PATHINFO].xStart - 33,
		                        fsArea[FS_AREA_PATHINFO].yStart,
		                        iBmpIndex,1);

            break;
        case 2:
            iBmpIndex = LAY_ANIMATION1;
            FSGUI_DrawReverseBmp(
                                fsArea[FS_AREA_PATHINFO].xStart - 33,
		                        fsArea[FS_AREA_PATHINFO].yStart,
		                        iBmpIndex,1);

            break;
        case 3:
            iBmpIndex = LAY_ANIMATION2;
            FSGUI_LayoutBmp(iBmpIndex);

            break;
    }
#endif//ifdef	GPS_MP3_UI

}
#endif //#if !defined (FS_BMP_GUI) //#ifdef INDIGO_STYLE_FSGUI

void FSGUI_FlashFileIcon(int iFlash)
{
    if (pFsJpeg->fsnav_trk_now == (pFsJpeg->file_array[pFsJpeg->file_current] - pFsJpeg->first_mp3_entry))
    {
        if (iFlash)
        {
            int x = fsArea[FS_AREA_FILEICON].xStart;
            int y = fsArea[FS_AREA_FILEICON].yStart + FS_FILELIST_YSTEP * pFsJpeg->file_current;
            int icon = pFsJpeg->gifsFuncBtn - 1;
        	DrawFileIcon(x, y, icon);
        }
        else
        {
		//2006-06-02, mimitsai add for HD ui.        
        #ifndef FS_BMP_GUI
			ClearRectArea(Rect[FILE_RECT], FILE_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, FILE_AREA_BKGROUND_CRCB, FS_AREA_FILEICON, -1);
        #endif
        }
    }
}

void ShowFileIcon(void)
{
    int i = 0;

    if (refresh_file_page == 1)
    {
    #ifdef FS_BMP_GUI
        FSGUI_ClearArea(FS_AREA_FILEICON,PER_PAGE+1);
	//2006-06-02, mimitsai add for HD ui.
	#else
        ClearRectArea(Rect[FILE_RECT], FILE_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, FILE_AREA_BKGROUND_CRCB,FS_AREA_FILEICON, -1 );
    #endif
    }

    for (i = 0; i < pFsJpeg->File_Count ; i++)
    {
        DrawFileIcon(fsArea[FS_AREA_FILEICON].xStart,
            (fsArea[FS_AREA_FILEICON].yStart + FS_FILELIST_YSTEP * i),
            pFsJpeg->gifsFuncBtn - 1);
    }
}

void FSShowDirIcon(void)
{
	int i = 0;

	#ifdef FS_BMP_GUI
    	if ( (refresh_dir_page == 1)||(refresh_dir_icon == 1))
                FSGUI_ClearArea(FS_AREA_DIRICON,PER_PAGE + 1);
	#else

	if ((!refresh_dir_page) && (!refresh_dir_icon))
		return;
	//2006-06-02, mimitsai add for HD ui.
    ClearRectArea(Rect[DIR_RECT], DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB, FS_AREA_DIRICON,-1);
	#endif

	for (i = 0; i < pFsJpeg->Dir_Count ; i++)
	{
		BYTE mode;

		if (pFsJpeg->dir_array[i] != pFsJpeg->fsnav_dir_now)
			mode = 0;
		else
			mode = 1;

		DrawFolderIcon(fsArea[FS_AREA_DIRICON].xStart, (FS_DIRLIST_YSTART + FS_FILELIST_YSTEP * i), mode);
	}
	refresh_dir_icon = 0;
}

#ifdef APEX_MP3_ICON
void DrawMp3ApexIcon(int x, int y)
{
    int i, j;

	#ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
	#endif

    for (i=0; i<24; i++) {
        for (j=0; j<72; j++) {
            //if ( fileIcon[type][i][j] == 0xff) continue;
            FSGUI_DrawPixel(
                x+j, y+i,
	        RGB8_Y[ mp3fileIcon[i][j] ],
                RGB8_CrCb[ mp3fileIcon[i][j] ]
            );
        }
    }
}
#endif//#ifdef APEX_MP3_ICON

void FSShowFileItem(int iItem, const char *s)
{
	#ifdef MP3_TXT_DISPLAY
    char buf[100];
	#else
	char	buf[20];
	#endif

	UINT16	first_seq;

	#ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
	#endif

	if ((iItem < 0) || (iItem >= PER_PAGE) || (iItem >= pFsJpeg->File_Count))
		return;

	#ifdef MP3_DIRECT_SELECT
	first_seq = pFsJpeg->first_mp3_seq + PER_PAGE * pFsJpeg->file_page_will;
	#else
	first_seq = PER_PAGE * pFsJpeg->file_page_will;
	#endif

#ifdef MP3_DIRECT_SELECT
	if(pFsJpeg->count_file[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3] >= 1000)
		psprintf(buf, "%04d.%s", first_seq + iItem + 1, s);
	else if(pFsJpeg->count_file[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3] >= 100)
#else
	if(pFsJpeg->file_specify_in_dir >= 1000)
		psprintf(buf, "%04d.%s", first_seq + iItem + 1, s);
	if(pFsJpeg->file_specify_in_dir >= 100)
#endif
		psprintf(buf, "%03d.%s", first_seq + iItem + 1, s);
	else
		psprintf(buf, "%02d.%s", first_seq+iItem + 1, s);

#ifdef FS_BMP_GUI
    FSGUI_ShowString(fsArea[FS_AREA_FILEITEM].xStart + 46,
			(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * iItem),
			buf, file_focus_y, file_focus_CrCb );
#elif defined(PHILIPS_FSGUI)//chenzhao20050613
    FSGUI_ShowString(fsArea[FS_AREA_FILEITEM].xStart,
            (FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * iItem),
            buf, file_focus_y, file_focus_CrCb);

#elif defined(INDIGO_STYLE_FSGUI)
	if(((PER_PAGE*pFsJpeg->file_page_will+iItem == pFsJpeg->fsnav_trk_now) && (PER_PAGE*pFsJpeg->file_page_will+iItem!= pFsJpeg->fsnav_trk_will))
	 ||((PER_PAGE*pFsJpeg->file_page_will+iItem == pFsJpeg->fsnav_trk_now) && (pFsJpeg->ControlArea != CNT_AREA_FILE)))
	{  // when HL, the font must be different color.
		FSGUI_ShowString(fsArea[FS_AREA_FILEITEM].xStart,
			(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * iItem),
			buf, TEXT_SELECT_COLODR_Y, TEXT_SELECT_COLODR_CbCr );
	}
	else
	{
		FSGUI_ShowString(fsArea[FS_AREA_FILEITEM].xStart,
			(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * iItem),
			buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb );
	}
#else
	FSGUI_ShowString(fsArea[FS_AREA_FILEITEM].xStart,
			(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * iItem),
			buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb );
#endif
}

void ShowDirItem(int iItem, const char *s)
{
	char    buf[20];
	UINT16  first_seq;

	#ifdef AUDIO_SHOW_SAVER
	if (bDisableGUI) return;
	#endif

	if ( (iItem < 0) || (iItem >= PER_PAGE) || (iItem >= pFsJpeg->Dir_Count)) {
		return;
	}

	first_seq = PER_PAGE * pFsJpeg->dir_page_now;

	if ( strcmp(s, "")==0 ) {
		psprintf(buf, "%02d.\\", first_seq+iItem+1);
	} else {
		psprintf(buf, "%02d.%s",first_seq+iItem+1, s);
	}

#ifdef FS_BMP_GUI
    FSGUI_ShowString( fsArea[FS_AREA_DIRITEM].xStart + 46,
		(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * iItem ),
		buf, file_focus_y, file_focus_CrCb );
#elif defined(PHILIPS_FSGUI)//chenzhao20050613
    FSGUI_ShowString( fsArea[FS_AREA_DIRITEM].xStart,
        (FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * iItem ),
        buf, file_focus_y, file_focus_CrCb);
#elif defined(INDIGO_STYLE_FSGUI)

	if(((pFsJpeg->dir_array[iItem] == pFsJpeg->fsnav_dir_now) && (pFsJpeg->dir_array[iItem]!= pFsJpeg->fsnav_dir_will))
	 ||((pFsJpeg->dir_array[iItem] == pFsJpeg->fsnav_dir_now) && (pFsJpeg->ControlArea != CNT_AREA_DIR)))
	{	// when HL, the font must be different color.
		FSGUI_ShowString( fsArea[FS_AREA_DIRITEM].xStart,
			(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * iItem ),
			buf, TEXT_SELECT_COLODR_Y, TEXT_SELECT_COLODR_CbCr );
	}
	else
		FSGUI_ShowString( fsArea[FS_AREA_DIRITEM].xStart,
			(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * iItem ),
			buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb );
#else
	FSGUI_ShowString( fsArea[FS_AREA_DIRITEM].xStart,
		(FS_DIRLIST_YSTART+ FS_FILELIST_YSTEP * iItem ),
		buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb );
#endif
}

//
// DrawFileIcon()
// Draw icon for file types
// type = 0->mp3, = 1->jpeg  , 2->game
//
#include "fsgui_icon_filex.inc"


#ifdef INDIGO_STYLE_FSGUI
void DrawFileIconX(int x, int y, int type, int mono __UNUSED)
{
	if(type == CNT_AREA_MP3BUTTON -2)		FSGUI_DrawIcon(x, y, ICON_FileX[type], MP3_ICON_Y,     MP3_ICON_CbCr,     0);
	else if(type == CNT_AREA_JPEGBUTTON -2)	FSGUI_DrawIcon(x, y, ICON_FileX[type], JPG_ICON_Y,     JPG_ICON_CbCr,     0);
#if defined(SUPPORT_NESGAME)
	else if(type == CNT_AREA_GAMEBUTTON -2)	FSGUI_DrawIcon(x, y, ICON_FileX[type], GAME_ICON_Y,    GAME_ICON_CbCr,    0);	
#endif
	else if(type == CNT_AREA_OTHERBUTTON-2)	FSGUI_DrawIcon(x, y, ICON_FileX[type], OTHER_ICON_Y,   OTHER_ICON_CbCr,   0);
	else if(type == CNT_TAB_MP3BUTTON   -2)	FSGUI_DrawIcon(x, y, ICON_FileX[type], MP3_BOTTOM_Y,   MP3_BOTTOM_CbCr,   0);
	else if(type == CNT_TAB_JPEGBUTTON  -2)	FSGUI_DrawIcon(x, y, ICON_FileX[type], JPG_BOTTOM_Y,   JPG_BOTTOM_CbCr,   0);
#if defined(SUPPORT_NESGAME)
	else if(type == CNT_TAB_GAMEBUTTON  -2)	FSGUI_DrawIcon(x, y, ICON_FileX[type], GAME_BOTTOM_Y,  GAME_BOTTOM_CbCr,  0);	
#endif
	else if(type == CNT_TAB_OTHERBUTTON -2)	FSGUI_DrawIcon(x, y, ICON_FileX[type], OTHER_BOTTOM_Y, OTHER_BOTTOM_CbCr, 0);	
}
#elif defined(NEW_MP3_GUI)
void DrawFileIconX(int x, int y, int type, int mono)
{
	#ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
	#endif

    FSGUI_DrawIcon(x, y, ICON_FileX[type], RGB8_Y, RGB8_CrCb, (mono? FSGUI_ICON_MONO : 0));
}
#else
void DrawFileIcon(int x, int y, int type)
{
	#ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
	#endif

#ifdef FS_BMP_GUI //suqiaoli add 2004-6-10 10:25
    FSGUI_LayPosVariableBmp(x, y,LAY_MP3_ICON_S + type);
#else
    FSGUI_DrawIcon(x, y, ICON_FileX[type], RGB8_Y, RGB8_CrCb, 0);
#endif

}
#endif

//
// DrawFolderIcon()
// Draw icon for directory types
// type=0: unselected, = 1: opened
//
#include "fsgui_icon_folderx.inc"
const UINT8  cluty_fsgui[2] =
{
    YELLOW_Y,
    BLACK_Y,
};

const UINT16  clutc_fsgui[2] =
{
    YELLOW_CRCB,
    BLACK_CRCB,
};
void DrawFolderIcon(int x, int y, BYTE type)
{
#ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
#endif

#ifdef FS_BMP_GUI //suqiaoli add 2004-6-10 10:26
	#ifdef	GPS_MP3_UI//frank.huang 050915
		if(type)
			FSGUI_LayPosVariableBmp(x, y,LAY_FOLDER_OPEN_ICON);
		else
    		FSGUI_LayPosVariableBmp(x, y,LAY_FOLDER_ICON);
	#else
    	FSGUI_LayPosVariableBmp(x, y,LAY_FOLDER_ICON);
	#endif
#else
	#ifdef INDIGO_STYLE_FSGUI
    	FSGUI_DrawIcon(x, y, ICON_FolderX[type], folder_Y, folder_CbCr, 0);
	#else
    FSGUI_DrawIcon(x, y, ICON_FolderX[type], cluty_fsgui, clutc_fsgui, 0);
#endif
#endif
}

void DrawRectEdge(int x,int y, int xSize,int ySize,UINT16 color_Y,UINT16 color_CrCb)
{
#ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
#endif

//wanghaoying notice 2004-8-4 17:24,
//maybe when Large-GUI DEMENSION_SIZE should be (DEMENSION_SIZE+1)

	FSGUI_FillFrameBuf(x,y,xSize,DEMENSION_SIZE,color_Y,color_CrCb);
	FSGUI_FillFrameBuf(x,y,DEMENSION_SIZE,ySize,color_Y,color_CrCb);
	FSGUI_FillFrameBuf(x+xSize-DEMENSION_SIZE,y,DEMENSION_SIZE,ySize,color_Y,color_CrCb);
	FSGUI_FillFrameBuf(x,y+ySize-DEMENSION_SIZE,xSize,DEMENSION_SIZE,color_Y,color_CrCb);
}

//
// List File item and clear refresh_file_page
//
void FileList(void)
{
    UINT16 i;

    if (pFsJpeg->gifsState == FS_STATE_JPEG)
        return;

    if (!refresh_file_page)
        return;

	#ifdef FS_BMP_GUI
	    FSGUI_ClearArea(FS_AREA_FILEITEM,PER_PAGE+1);
	//2006-06-02, mimitsai add for HD ui.
	#else
        ClearRectArea(Rect[FILE_RECT], FILE_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, FILE_AREA_BKGROUND_CRCB, FS_AREA_FILEITEM, -1);
    #endif

	#ifdef JPG_EFFECT
	    #if !defined ( HELP_BMP_GUI)
    	jpeg_effect_draw_help();
		#endif
	#endif

    for (i = 0; i < pFsJpeg->File_Count; i++)
    {
        DrawFileIcon(fsArea[FS_AREA_FILEICON].xStart,
            (fsArea[FS_AREA_FILEICON].yStart + FS_FILELIST_YSTEP * i), pFsJpeg->gifsFuncBtn - 1);
        FSShowFileItem(i, iso9660_file[pFsJpeg->file_array[i]].name);
    }
    refresh_file_page = 0;
}

//
// Calculat location of the first file specified style -> fsnav_trk_now
// and how many page needed to show these files -> File_Page_Count
// and first_mp3_entry, last_mp3_entry
// file_page_now and file_current clear to 0
// and calculate length of scroll bar
//
UINT16 CalcFileFirstPage(int iDirSelect)
{
	int iFile;

	pFsJpeg->first_mp3_seq = 0;

	pFsJpeg->first_mp3_entry = pFsJpeg->Dir_entry[iDirSelect];

	if(iDirSelect == pFsJpeg->fsnav_dir_cnt - 1)
		pFsJpeg->last_mp3_entry = pFsJpeg->iso9660_file_cnt - 1;
	else
		pFsJpeg->last_mp3_entry = pFsJpeg->Dir_entry[iDirSelect + 1] - 1;

	#ifdef	USE_FSGUI_TO_PLAY_CD//frank.huang add 051014
	if(cd_type_loaded!=CDDA)
	#endif
	pFsJpeg->file_specify_in_dir = CountSpecifyFile(iDirSelect);

#ifdef FS_LOAD_DIR_SEPARATELY
	for(iFile = 0; iFile < iDirSelect; iFile++)
	{
        pFsJpeg->first_mp3_seq += FS_DirectoryFileCountGetField(iFile,pFsJpeg->gifsFuncBtn);
	}
#else   //!FS_LOAD_DIR_SEPARATELY, all file info in memory, scan through entries to get first_mp3_seq.
	for(iFile = 0; iFile < pFsJpeg->first_mp3_entry; iFile++)
	{
		if (iso9660_file[iFile].type == pFsJpeg->gifsFuncBtn)
			pFsJpeg->first_mp3_seq++;
	}
#endif //#ifdef FS_LOAD_DIR_SEPARATELY , dealing with pFsJpeg->first_mp3_seq
	iFile = pFsJpeg->first_mp3_entry;

	while (iFile <= pFsJpeg->last_mp3_entry)
	{
		if (iso9660_file[iFile].type == pFsJpeg->gifsFuncBtn)
		{
			pFsJpeg->fsnav_trk_now = iFile - pFsJpeg->first_mp3_entry;
			break;
		}
		iFile++;
	}

	FSGUI_CalcuteDirFileScrollLen();

	pFsJpeg->file_page_will = 0;
	pFsJpeg->file_will = 0;
	refresh_file_page = 1;

	return pFsJpeg->file_specify_in_dir;
}



//
// locate the directory
//
UINT16 AnchorDir(int iSeq)
{
	int dir;
	int j = 0;

	for (dir = 0; dir < pFsJpeg->fsnav_dir_cnt; dir++)
	{
		if (iso9660_dir[dir].type & (0x01 << pFsJpeg->gifsFuncBtn))
		{
			if(j == iSeq)
				break;
			j++;
		}
	}

	return dir;
}

UINT16 AnchorFile(int iSeq)
{
	UINT16 file;
	UINT16 j = 0;

	for (file = 0; file <= (pFsJpeg->last_mp3_entry - pFsJpeg->first_mp3_entry); file++)
	{
		if (iso9660_file[file + pFsJpeg->first_mp3_entry].type == pFsJpeg->gifsFuncBtn)
		{
			if(j == iSeq)
				break;
			j++;
		}
	}
	return (file);
}

UINT16 antiAnchorDir(int iDir)
{
    int seq = 0;
    int i;

    for(i = 0; i <= iDir; i++)
    {
        if (iso9660_dir[i].type & (0x01 << pFsJpeg->gifsFuncBtn))
            seq++;
    }

    return (seq-1);
}


UINT16 CountSpecifyFile(int iDir __UNUSED)
{

#ifdef FS_LOAD_DIR_SEPARATELY  
    return FS_DirectoryFileCountGetField(iDir,pFsJpeg->gifsFuncBtn);
#else   //normal 32mb situation, no FS_LOAD_DIR_SEPARATELY
    int iCount = 0;
    int iFirst,iLast;
    int i;

    iFirst = pFsJpeg->Dir_entry[iDir];

    if (iDir == pFsJpeg->fsnav_dir_cnt - 1)
        iLast = pFsJpeg->iso9660_file_cnt - 1;
    else
        iLast = pFsJpeg->Dir_entry[iDir + 1] - 1;

    i = iFirst;

    while (i <= iLast)
    {
        if (iso9660_file[i].type == pFsJpeg->gifsFuncBtn)
            iCount++;
        i++;
    }

    return iCount;
#endif  //#ifdef FS_LOAD_DIR_SEPARATELY
}

//Jeff update, 20020715
void FSGUI_ProgSelect(UINT16 index)
{
    BYTE oldbSlide;

    pFsJpeg->fsnav_dir_will = AnchorDir(prog[index][0] - 1);    // calculate fsnav_dir_will, panxing,2002-1-29

    refresh_dir_icon = 1;
    FSGUI_PreChangeDir(&(pFsJpeg->fsnav_dir_will), 0);
    pFsJpeg->fsnav_dir_now = pFsJpeg->fsnav_dir_will;

    oldbSlide = pFsJpeg->gbfsSlide;
    FSGUI_FileSelect( prog[index][1] );

    pFsJpeg->gbfsSlide = oldbSlide;
}


void FSGUI_FileSelect(int iSelect)
{
    if (iSelect > 0 && iSelect <= pFsJpeg->file_specify_in_dir)
    {
#ifdef  JPEG_SELECT_IN_REPEAT_MODE //wuxiaofeng 2004-03-10
        if(rep_mode==0)//hold pFsJpeg->gbfsSlide=1
#endif
        #if !defined(SELECT_JPEG_NOT_STOP_SLIDE)&&!defined(NUM_SELECT_SLIDE_PLAY) //wangap 2005-5-8 10:08
        pFsJpeg->gbfsSlide = 0;
         #endif
         
        iSelect = iSelect - 1;  // file_current begin from 0, panxing, 2002-1-22

        if ((pFsJpeg->file_page_will * PER_PAGE <= iSelect) && ((pFsJpeg->file_page_will * PER_PAGE + pFsJpeg->File_Count - 1) >= iSelect))
        {
            // selecting is in current file page, panxing, 2002-1-22
            pFsJpeg->file_will = iSelect - pFsJpeg->file_page_will * PER_PAGE;
            pFsJpeg->fsnav_trk_will = pFsJpeg->file_array[pFsJpeg->file_will] - pFsJpeg->first_mp3_entry;
        }
        else
        {
            // selecting isn't in current file page,so need change file page,panxing, 2002-1-22
            pFsJpeg->file_page_will = iSelect / PER_PAGE;
            PrepareForChangeFilePage(iSelect / PER_PAGE, iSelect, 2);
        }
        Will2Playing();
    }
}

//Maoyong 2004.03.10 Find pre selected file's dir for STOP state right search/select
void FindPreSelectFileDir(UINT16 *iSelect)
{
#ifdef MP3_DIRECT_SELECT
        int i, tmp;
        int iCount = 0;
        if ((*iSelect > 0) && (*iSelect <= pFsJpeg->count_file[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3]))
        {
            for(i = 0; i < pFsJpeg->fsnav_dir_cnt; i++)
            {
                tmp = CountSpecifyFile(i);
                if((iCount + tmp) >= *iSelect)
                    break;
                iCount += tmp;
            }
            pFsJpeg->fsnav_dir_now = i;
            *iSelect = *iSelect - iCount;
            printf(" FIND SEL DIR: pFsJpeg->fsnav_dir_now = %d\n", pFsJpeg->fsnav_dir_now) ;
        }
#else
    *iSelect = *iSelect;
#endif
}

#ifdef AUDIO_SHOW_SAVER

void FSGUI_Force2Menu(void)
{
    #if defined(MP3_LARGE_GUI) || defined(INDIGO_STYLE_LARGE_FSGUI)//2006-06-02, mimitsai add for HD ui.
    config_memory(MEMORY_GRAPH_NTSC);
    #else
    config_memory(MEMORY_GRAPH_SMALL);
    #endif
    ClearOsdMsg(2);
    FSGUI_Menu();
    pFsJpeg->gbfsSlide	= 0;
    pFsJpeg->gifsbPreview = 1; // Robert 20020715
    refresh_file_page 	= 1; // insure refresh dir page, panxing, 2002-1-22
    refresh_dir_page 	= 1;

    FSGUI_Refresh();
    AVD_ResetMediaStatus();

    reset_zoom_state();
}

void FSGUI_Disable()
{
    bDisableGUI = 1;
}

void FSGUI_Ensable()
{
    bDisableGUI = 0;
}

#endif


int FSGUI_NormalNext(void)
{
	int done = 0;
	int files = 0;
	int CurAsWill = 0;
	int bChangeHL;  //Jeff 20020418
    int iCurDir;

#ifdef  MP3_JPEG_COWORK
    old_time=get_stc_32_inline();//get the press time
#endif

#ifdef RECORD_PER_SECOND		//avoid bug when playing mp3  gerry  2-12-3 19:46
	resumeMSF = 0;
#endif

    //joshua, 2006.5.19, modified for repeating-track behavior, move to FS_ParseCommand()
    if(rep_mode == REPEAT_TRACK)
    {
        PrintOsdMsg(STR_OS_REP_1, REGION1, 1, 0);
        done = 0;
        return done;             
    }
        

	if ((pFsJpeg->file_will == pFsJpeg->file_current) && (pFsJpeg->file_page_now == pFsJpeg->file_page_will)) // Robert modify 021025
		bChangeHL = 1;
	else
		bChangeHL = 0;

	SetAVDState(0);

	if ((pFsJpeg->file_page_now == pFsJpeg->file_page_will) && (pFsJpeg->file_current == pFsJpeg->file_will))
		CurAsWill = 1;

	if (pFsJpeg->file_page_now == (pFsJpeg->File_Page_Count - 1))
		files = pFsJpeg->file_specify_in_dir - pFsJpeg->file_page_now * PER_PAGE;
	else
		files = PER_PAGE;
	(pFsJpeg->file_current)++;

    // 2004/04/13 yltseng, fix the method to find out whether we reach the final file or not
	if (pFsJpeg->file_current >= files)
	{
		// need change file page,panxing,2002-4-15
		refresh_file_page = 1;
		pFsJpeg->file_page_now++;
		pFsJpeg->file_current = 0;

		if (pFsJpeg->file_page_now >= pFsJpeg->File_Page_Count)
		{
			//  need change directory
			refresh_dir_icon = 1;
			Restore2PlayingDir();	//panxing,2002-4-13
			if(rep_mode != REPEAT_DIRECTORY)
			{
			    pFsJpeg->dir_current++;
			    pFsJpeg->fsnav_dir_will++;  //Maoyong 2004.05.27
			}
			else
				PrintOsdMsg(STR_OS_REP_DIR, REGION1, 1, 0);

            //pFsJpeg->fsnav_dir_will = pFsJpeg->dir_page_now * PER_PAGE + pFsJpeg->dir_current;
            //dir_in_button = pFsJpeg->dir_page_now * PER_PAGE + pFsJpeg->dir_current;
            //if( pFsJpeg->fsnav_dir_will >= pFsJpeg->Dir_Count )
            //if( dir_in_button >= pFsJpeg->Dir_Count )

            //Maoyong marked and changed 2004-7-6 20:01 More than 10 dirs will enter to stop after 10th dir!!!
            iCurDir = pFsJpeg->dir_page_now * PER_PAGE + pFsJpeg->dir_current;
            if( iCurDir >= pFsJpeg->count_dir[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3] )
			{
				// total disc complete
				#ifdef JPEG_AUTO_REPEAT_PLAY
                if((rep_mode!=REPEAT_DISC) && (pFsJpeg->gifsFuncBtn!=FS_FUNC_JPEG))
				#else
				if (rep_mode != REPEAT_DISC)
				#endif
				{
					//locate to last dir and last file
			#if defined(MP4_DISC_DIRECT_PLAY)&& defined(JPEG_MP4_FRIST_STOP_TO_GUI)  //qinhua ,add 2005-10-14 16:18
					if(GetCurrentFileType() == CDROM_MP4)
					{
					ReturnFromOtherModeToMenu();
					pFsJpeg->gifsState = FS_STATE_LIST;
					ircmd_stop();
				    mp4_to_logo = 1;
		          }
		          else
		           FSGUI_2Last();
		           play_state = VCD_STATE_STOP;
				   done = 1;	 
			 #else 
					#if defined(MP3_ONLY_STOP_TO_GUI)&&!defined(MP3_STOP_IN_GUI_AND_LOGO) //chenzhao 2006-4-19 10:19 .//linrc for Stop in GUI when after the last MP3 end 2005-12-2 17:09
                    if(pFsJpeg->gifsFuncBtn == FS_FUNC_MP3) //chenzhao Add for Stop after the last JPEG end 2006-4-10 14:1 .
					{
					pFsJpeg->fsnav_dir_will = 0;
					FSGUI_PreChangeDir(&(pFsJpeg->fsnav_dir_will), 0);
					pFsJpeg->fsnav_dir_now = pFsJpeg->fsnav_dir_will;
					if (sys_cmd == (CMD_FUNC|CMD_FUNC_TIMEOUT))
							sys_cmd = 0;
				    }
                    else
                    #endif 
                    {
					FSGUI_2Last();
                    #if defined(ALCO_DVD_UI)          
                      if(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
                      ircmd_stop();
                      #endif
                    #ifdef SUPPORT_OTHER_FILES_SSCREEN
					extern UINT32 save_srn_start_t;
                    save_srn_start_t = get_rtc_val();
                    #endif
					// stop now
					play_state = VCD_STATE_STOP;
					done = 1;
                    }
			#endif 
				}
				else
				{
					// start again
					pFsJpeg->fsnav_dir_will = 0;
					FSGUI_PreChangeDir(&(pFsJpeg->fsnav_dir_will), 0);
					pFsJpeg->fsnav_dir_now = pFsJpeg->fsnav_dir_will;
					#ifdef JPEG_AUTO_REPEAT_PLAY
                    if(rep_mode)
                    #endif	
					PrintOsdMsg(STR_OS_REP_ALL, REGION1, 1, 0);
				}
			}
			else
			{
				// change directory now
				if (FSGUI_PreChangeDir(&(pFsJpeg->fsnav_dir_will), 0))
				{
					if(rep_mode != REPEAT_DISC)
					{
                        //locate to last dir and last file
					    FSGUI_2Last();

                        // stop now
					    play_state = VCD_STATE_STOP;
						done = 1;
					}
					else
					{
						refresh_dir_icon = 1;
						pFsJpeg->fsnav_dir_will = 0;
						FSGUI_PreChangeDir(&(pFsJpeg->fsnav_dir_will), 0);
						PrintOsdMsg(STR_OS_REP_ALL, REGION1, 1, 0);
					}
				}
				pFsJpeg->fsnav_dir_now = pFsJpeg->fsnav_dir_will;
			}
		}
		else
		{
			// needn't change directory but need change file page
			if(CurAsWill)
			{
				pFsJpeg->file_page_will = pFsJpeg->file_page_now;
				PrepareForChangeFilePage(pFsJpeg->file_page_now, 0, 0);
				Will2Playing();
			}
			else
				pFsJpeg->fsnav_trk_now = AnchorFile(pFsJpeg->file_page_now * PER_PAGE + pFsJpeg->file_current);
		}
	}
	else
	{
		// needn't change file page
		if (CurAsWill)
			pFsJpeg->fsnav_trk_now = pFsJpeg->file_array[pFsJpeg->file_current] - pFsJpeg->first_mp3_entry;
		else
			pFsJpeg->fsnav_trk_now = AnchorFile(pFsJpeg->file_page_now * PER_PAGE + pFsJpeg->file_current);
	}

#if 0
	printf("=============Info of mp3 navigation NEXT============\n");
	printf("file_current=%3d, file_page_now  =%3d, fsnav_trk_now =%3d\n", file_current, pFsJpeg->file_page_now, pFsJpeg->fsnav_trk_now);
	printf("file_will   =%3d, file_page_will =%3d, fsnav_trk_will=%3d\n",file_will, pFsJpeg->file_page_will, pFsJpeg->fsnav_trk_will);
	printf("File_Count  =%3d, File_Page_Count=%3d, file_specify_in_dir=%3d\n", pFsJpeg->File_Count,pFsJpeg->File_Page_Count,file_specify_in_dir);
	printf("dir_current =%3d, fsnav_dir_now  =%3d\n", pFsJpeg->dir_current, pFsJpeg->fsnav_dir_now);
	printf("dir_page_now=%3d, fsnav_dir_will =%3d\n", pFsJpeg->dir_page_now, pFsJpeg->fsnav_dir_will);
	printf("refresh_dir_icon=%d,refresh_file_page=%d,refresh_dir_page=%d\n",refresh_dir_icon,
		refresh_file_page,refresh_dir_page);
#endif

	if (bChangeHL)
		Playing2Will();
	return done;
}

int FSGUI_NormalPrev(void)
{
    int done = 0;
    int CurAsWill = 0;
    #if 0//def MP3_FORWD_BACKWD_PLAY   //wsf  2004-7-26 12:59
    done = 0;
    return done;
    #endif
#ifdef  MP3_JPEG_COWORK
        old_time=get_stc_32_inline();//get the press time
#endif
    SetAVDState(0);
#ifdef RECORD_PER_SECOND        //avoid bug when playing mp3  gerry  2-12-3 19:46
    resumeMSF = 0;
#endif

    if ((pFsJpeg->file_page_now == pFsJpeg->file_page_will) && (pFsJpeg->file_current == pFsJpeg->file_will))
        CurAsWill = 1;
    else
		CurAsWill = 0;

/*  2004/06/21 yltseng mark, it's no use now
#ifdef SUPPORT_NESGAME
    if ((pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG) || (pFsJpeg->gifsFuncBtn == FS_FUNC_GAME))
#else
    if (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
#endif
        pFsJpeg->gifsbPreview = 1;
*/
    if (pFsJpeg->file_current != 0)
    {
        // needn't change file page
        refresh_file_page = 0;
        (pFsJpeg->file_current)--;

        if(CurAsWill)
            pFsJpeg->fsnav_trk_now = pFsJpeg->file_array[pFsJpeg->file_current] - pFsJpeg->first_mp3_entry;
        else
            pFsJpeg->fsnav_trk_now = AnchorFile(pFsJpeg->file_page_now * PER_PAGE + pFsJpeg->file_current);
    }
    else
    {
        // need change file page;
        refresh_file_page = 1;

        if (pFsJpeg->file_page_now != 0)
        {
            // change file page now
            pFsJpeg->file_page_now--;
            if(CurAsWill)
            {
                pFsJpeg->file_page_will = pFsJpeg->file_page_now;
                PrepareForChangeFilePage(pFsJpeg->file_page_now, 0, 1);
                Will2Playing();
            }
            else
            {
                pFsJpeg->file_current = PER_PAGE;
                pFsJpeg->fsnav_trk_now = AnchorFile(pFsJpeg->file_page_now * PER_PAGE + pFsJpeg->file_current);
            }
        }
        else
        {
            //  change directory
            refresh_dir_icon = 1;
            Restore2PlayingDir();   // panxing, 2002-4-13
            #ifdef MP3_FB_PLAY_AT_STARTDIR
            if(pFsJpeg->fsnav_dir_will != 0)    //linrc 2004-8-9 16:21
            #else
            if ((pFsJpeg->fsnav_dir_will != 0) || (rep_mode == REPEAT_DIRECTORY)) //panxing, 2002-3-13
            #endif
            {
                if(rep_mode != REPEAT_DIRECTORY)
                    pFsJpeg->fsnav_dir_will--;
                else
                    PrintOsdMsg(STR_OS_REP_DIR, REGION1, 1, 0);

                if (FSGUI_PreChangeDir(&(pFsJpeg->fsnav_dir_will), 1))
                {
                    if (rep_mode != REPEAT_DISC)
                        done = 1;
                    else
                    {
                        //locate to last dir and last file
                        FSGUI_2Last();
                    }
                }
                else
                {
                    pFsJpeg->fsnav_dir_now = pFsJpeg->fsnav_dir_will;
                    // correct the list of prev directory's file, panxing, 2002-1-18
                    pFsJpeg->file_page_will = pFsJpeg->File_Page_Count - 1;
                    PrepareForChangeFilePage(pFsJpeg->File_Page_Count - 1, 0, 1);
                    Will2Playing();
                }
            }
            else
            {
                // total disc complete
                #ifdef MP3_FB_PLAY_AT_STARTDIR  //when FB at dir start,it replay
                if(1)                           //and cancel repeat mode,so I marke it
                #else                           //linrc 2004-8-9 16:20
                if (rep_mode != REPEAT_DISC)
                #endif
                {
                    #ifdef MP3_FB_PLAY_AT_STARTDIR
                    rep_mode = REPEAT_IDLE;
                    #endif
                    // stop now
                    if ((pFsJpeg->fsnav_dir_now == 0) && (adv_search_time < 0))
                    {
                        //terry, debug: bf 1st trk , repeat refresh and bf
                        //2002/4/29 03:56PM
                        adv_search_time = 0;
                        refresh_file_page = 0;
                    }
                    pFsJpeg->fsnav_dir_will  = 0;
                    pFsJpeg->dir_current     = 0;
                    pFsJpeg->fsnav_trk_now   = 0;
                    pFsJpeg->dir_page_now    = 0;
                    pFsJpeg->file_page_now   = 0;
                    old_file_page   = 0xffff;
                    old_dir_page    = 0xffff;
                    play_state      = VCD_STATE_STOP;
                    done            = 1;
                    FSGUI_PreChangeDir(&(pFsJpeg->fsnav_dir_now), 0);//2004-3-10 18:38
                }
                else
                {
                    //locate to last dir and last file
                    FSGUI_2Last();
                    PrintOsdMsg(STR_OS_REP_ALL, REGION1, 1, 0);
                }
            }
        }
    }
/*
    printf("=============Info of mp3 navigation PREV============\n");
    printf("file_current=%3d, file_page_now  =%3d, fsnav_trk_now =%3d\n",file_current, pFsJpeg->file_page_now, pFsJpeg->fsnav_trk_now);
    printf("file_will   =%3d, file_page_will =%3d, fsnav_trk_will=%3d\n", file_will, pFsJpeg->file_page_will, pFsJpeg->fsnav_trk_will);
    printf("File_Count  =%3d, File_Page_Count=%3d, file_specify_in_dir=%3d\n", pFsJpeg->File_Count,pFsJpeg->File_Page_Count,file_specify_in_dir);
    printf("dir_current =%3d, fsnav_dir_now  =%3d\n", pFsJpeg->dir_current, pFsJpeg->fsnav_dir_now);
    printf("dir_page_now=%3d, fsnav_dir_will =%3d\n", pFsJpeg->dir_page_now, pFsJpeg->fsnav_dir_will);
    printf("refresh_dir_icon=%d,refresh_file_page=%d,refresh_dir_page=%d\n",refresh_dir_icon,
    refresh_file_page,refresh_dir_page);
*/
	if (CurAsWill)
		Playing2Will();
    return done;
}
#ifdef GPS_MP3_UI//sunxin add 050920
void FSGUI_CookFileItem(BYTE iItem)
{
	char buf[26] = {0};     // 2005/02/16 yltseng

	if ((iItem >= PER_PAGE) || (iItem >= pFsJpeg->File_Count))
		return;

	if (pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
	{
	// 2004/04/18 yltseng, If not mark it, when turn on SUPPORT_CHINESE_FONT, all CDROM & CDROM_WMA file don't show
    // extension file name even though we turn ISO9660_FILE_NOT_SHOW_EXTEND_NAME off.
		if (GetCurrentFileType() == CDROM)
		{
			psprintf(buf, "\x02 [%s]%s.MP3", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name); // panxing,2002-4-13
		}
		else
#ifdef SUPPORT_AAC//Steven 2006/6/1 add (GetCurrentFileType() == CDROM_AAC) for aac audio//
		if (GetCurrentFileType() == CDROM_AAC)
		{
			psprintf(buf, "\x02 [%s]%s.AAC", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name); // panxing,2002-4-13
		}
		else
#endif
#ifdef SUPPORT_WMA
		if (GetCurrentFileType() == CDROM_WMA)
		{
			psprintf(buf, "\x02 [%s]%s.WMA", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name); // panxing,2002-4-13
		}
		else
#endif
    //#endif
		{
			psprintf(buf, "\x02 [%s]%s", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name); // panxing,2002-4-13
		}
	}
	else if (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
	{
	
#ifdef SUPPORT_GIF
		if (GetCurrentFileType() == CDROM_GIF)
		{
			psprintf(buf, "[%s]%s.GIF", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
		}
		else
#endif

#ifdef SUPPORT_BMP
		if (GetCurrentFileType() == CDROM_BMP)
		{
			psprintf(buf, "[%s]%s.BMP", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
		}
		else
#endif
		psprintf(buf, "[%s]%s.JPG", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
	}

#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 021001
	else if (pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)
    {   // yltseng 20040412 show file extension
        #ifndef ISO9660_FILE_NOT_SHOW_EXTEND_NAME
        #ifdef TELL_FROM_MP4_EXT_NAME   //Maoyong
        if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].file_type == CDROM_MP4 )
        {
            #ifdef TEMPORARY_FIX_WMA_EXTENSION
                #if defined(SUPPORT_AUD_WMA) && defined(SUPPORT_ASF)
                    if(iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].dir == CDROM_WMA)
                        psprintf(buf, "[%s]%s.WMA", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
                    else
                #endif
            #endif  //#ifdef TEMPORARY_FIX_WMA_EXTENSION
            psprintf(buf, "[%s]%s.MP4", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        }else if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].file_type == CDROM_AVI )
        {
            #ifdef TEMPORARY_FIX_WMA_EXTENSION
                #if defined(SUPPORT_AUD_WMA) && defined(SUPPORT_ASF)
                    if(iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].dir == CDROM_WMA)
                        psprintf(buf, "[%s]%s.WMA", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
                    else
                #endif
            #endif  //#ifdef TEMPORARY_FIX_WMA_EXTENSION
            psprintf(buf, "[%s]%s.AVI", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        }
        #ifdef SUPPORT_QUICKTIME
        else if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].file_type == CDROM_M4A )
        {
            #ifdef TEMPORARY_FIX_WMA_EXTENSION
                #if defined(SUPPORT_AUD_WMA) && defined(SUPPORT_ASF)
                    if(iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].dir == CDROM_WMA)
                        psprintf(buf, "[%s]%s.WMA", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
                    else
                #endif
            #endif  //#ifdef TEMPORARY_FIX_WMA_EXTENSION
            psprintf(buf, "[%s]%s.M4A", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        }
        #endif //#ifdef SUPPORT_QUICKTIME
        else if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].file_type == CDROM_DIV )
        {
            #ifdef TEMPORARY_FIX_WMA_EXTENSION
                #if defined(SUPPORT_AUD_WMA) && defined(SUPPORT_ASF)
                    if(iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].dir == CDROM_WMA)
                        psprintf(buf, "[%s]%s.WMA", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
                    else
                #endif
            #endif  //#ifdef TEMPORARY_FIX_WMA_EXTENSION
            psprintf(buf, "[%s]%s.DIV", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        }
        #else
        if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].file_type == CDROM_MP4 )
        {
            #ifdef TEMPORARY_FIX_WMA_EXTENSION
                #if defined(SUPPORT_AUD_WMA) && defined(SUPPORT_ASF)
            if(iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].dir == CDROM_WMA)
                psprintf(buf, "[%s]%s.WMA", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
            else
                #endif
            #endif  //#ifdef TEMPORARY_FIX_WMA_EXTENSION
            psprintf(buf, "[%s]%s.MP4", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        }
        #endif  //#ifdef TELL_FROM_MP4_EXT_NAME
        else if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].file_type == CDROM_MPG )
            psprintf(buf, "[%s]%s.MPG", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        #ifdef SUPPORT_PLAY_SWD
        else if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].file_type == CDROM_SWD )
            psprintf(buf, "[%s]%s.SWD", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        #endif
        else
        #endif  //#ifndef ISO9660_FILE_NOT_SHOW_EXTEND_NAME
		psprintf(buf, "[%s]%s", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
    }
#endif

#ifdef SUPPORT_FS_LONGNAME  //Maoyong 2004.06.24
//suxin change 2005-09-22,display filename for malata GPS_DVD
    #define MAX_FILENAME_LEN    24
    if( GetFileFullName(pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry) )
    {
        if((strlen(iso9660_dir[pFsJpeg->fsnav_dir_now].name) + strlen(uFullFilename)) > MAX_FILENAME_LEN)
            uFullFilename[MAX_FILENAME_LEN - (strlen(iso9660_dir[pFsJpeg->fsnav_dir_now].name))] = '\0';
        //Steven 2006/6/1 add (GetCurrentFileType() == CDROM_AAC) for aac audio//
        if((GetCurrentFileType() == CDROM)||(GetCurrentFileType() == CDROM_WMA) || (GetCurrentFileType() == CDROM_AAC))
            psprintf(linebuf, "\x02 [%s]%s", iso9660_dir[pFsJpeg->fsnav_dir_now].name, uFullFilename);
        else
            psprintf(linebuf, "[%s]%s", iso9660_dir[pFsJpeg->fsnav_dir_now].name, uFullFilename);

		#ifdef USE_FSGUI_TO_PLAY_CD//frank.huang add 051014
		if(cd_type_loaded==CDDA)
			 FSGUI_UpdateInfoArea(buf);
		else
		#endif
            FSGUI_UpdateInfoArea(linebuf);
    }
    else   //can't read succesfully, just use the old way for file name
    	FSGUI_UpdateInfoArea(buf);
#else   //#ifdef SUPPORT_FS_LONGNAME
        FSGUI_UpdateInfoArea(buf);
#endif  //#ifdef SUPPORT_FS_LONGNAME
}

#else	//#ifdef GPS_MP3_UI

void FSGUI_CookFileItem(BYTE iItem)
{
	#ifdef HANYANG_DVD
	#ifdef HANYANG_FS_LONGNAME
	FSGUI_UpdateInfoArea("");
	if( (pFsJpeg->gifsFuncBtn == FS_FUNC_MP3) && GetFileFullName(pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry) ){
        if( uScrollDispFilenameFlag ==1 ){
            uScrollDispFilenameFlag = SCROLL_SHOW_500MS_CNT;    //for first display
            FS_ScrollDispFileName();
        }
    }
	#endif
	return;
	#endif

	char buf[26] = {0};     // 2005/02/16 yltseng
	#ifdef SHOW_CDROM_TOTAL_FILE
	char buf2[15] = {0};
	#endif

	if ((iItem >= PER_PAGE) || (iItem >= pFsJpeg->File_Count))
		return;
#ifdef SUPPORT_ID3//CLEAD_UNICODE
	#if defined(ALCO_ID3)
	FSGUI_FillFrameBuf(36,8,148+172,30, BK_GROUNDY, BK_GROUNDCRCB);//clead_unicode
	#else
	FSGUI_FillFrameBuf(36,8,148+172,50, BK_GROUNDY, BK_GROUNDCRCB);//clead_unicode
    #endif
#endif
    /*============================MP3=======================*/
	if (pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
	{
#if !defined(SUPPORT_ID3)||defined(ALCO_ID3)
    // 2004/04/18 yltseng, If not mark it, when turn on SUPPORT_CHINESE_FONT, all CDROM & CDROM_WMA file don't show
    // extension file name even though we turn ISO9660_FILE_NOT_SHOW_EXTEND_NAME off.
    //#ifndef SUPPORT_CHINESE_FONT
		if (GetCurrentFileType() == CDROM)
		{
    #ifdef ISO9660_FILE_NOT_SHOW_EXTEND_NAME     //gerry,2004-2-26 10:53
			psprintf(buf, "[%s]%s", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name); // panxing,2002-4-13
    #else//ISO9660_FILE_NOT_SHOW_EXTEND_NAME
			#ifdef SHOW_CDROM_TOTAL_FILE
			psprintf(buf, "%s.MP3",iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name); // panxing,2002-4-13
			#else
			psprintf(buf, "[%s]%s.MP3", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name); // panxing,2002-4-13
			#endif
    #endif//ISO9660_FILE_NOT_SHOW_EXTEND_NAME
		}
		else
    #ifdef SUPPORT_AAC//Steven 2006/6/1 add (GetCurrentFileType() == CDROM_AAC) for aac audio//
		if (GetCurrentFileType() == CDROM_AAC)
		{
        #ifdef ISO9660_FILE_NOT_SHOW_EXTEND_NAME     //gerry,2004-2-26 10:53
			psprintf(buf, "[%s]%s", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name); // panxing,2002-4-13
        #else//ISO9660_FILE_NOT_SHOW_EXTEND_NAME
			#ifdef SHOW_CDROM_TOTAL_FILE
			psprintf(buf, "%s.AAC",iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name); // panxing,2002-4-13
			#else
			psprintf(buf, "[%s]%s.AAC", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name); // panxing,2002-4-13
			#endif
        #endif//ISO9660_FILE_NOT_SHOW_EXTEND_NAME
		}
		else
    #endif

    #ifdef SUPPORT_WMA
		if (GetCurrentFileType() == CDROM_WMA)
		{
        #ifdef ISO9660_FILE_NOT_SHOW_EXTEND_NAME     //gerry,2004-2-26 10:53
			psprintf(buf, "[%s]%s", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name); // panxing,2002-4-13
        #else//ISO9660_FILE_NOT_SHOW_EXTEND_NAME
			#ifdef SHOW_CDROM_TOTAL_FILE
			psprintf(buf, "%s.WMA",iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name); // panxing,2002-4-13
			#else
			psprintf(buf, "[%s]%s.WMA", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name); // panxing,2002-4-13
			#endif
        #endif//ISO9660_FILE_NOT_SHOW_EXTEND_NAME
		}
		else
    #endif
    //#endif
		{
			#ifdef SHOW_CDROM_TOTAL_FILE
			psprintf(buf, "%s",iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name); // panxing,2002-4-13
			#else
			psprintf(buf, "[%s ]%s", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name); // panxing,2002-4-13
		    #endif
		}
#endif
	}
    /*============================JPEG=======================*/
	else if (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
	{
#ifdef SUPPORT_GIF
		if (GetCurrentFileType() == CDROM_GIF)
		{
    #ifdef ISO9660_FILE_NOT_SHOW_EXTEND_NAME     //gerry,2004-2-26 10:53
			psprintf(buf, "[%s]%s", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
    #else//ISO9660_FILE_NOT_SHOW_EXTEND_NAME
			#ifdef SHOW_CDROM_TOTAL_FILE
			psprintf(buf, "%s.GIF", iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
			#else
			psprintf(buf, "[%s]%s.GIF", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
			#endif
    #endif//ISO9660_FILE_NOT_SHOW_EXTEND_NAME
		}
		else
#endif
#ifdef SUPPORT_BMP
	if (GetCurrentFileType() == CDROM_BMP)
	{
    #ifdef ISO9660_FILE_NOT_SHOW_EXTEND_NAME     //gerry,2004-2-26 10:53
		psprintf(buf, "[%s]%s", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
    #else//ISO9660_FILE_NOT_SHOW_EXTEND_NAME
		#ifdef SHOW_CDROM_TOTAL_FILE
		psprintf(buf, "%s.BMP", iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
		#else
		psprintf(buf, "[%s]%s.BMP", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
		#endif
    #endif//ISO9660_FILE_NOT_SHOW_EXTEND_NAME
	}
	else
#endif
#ifdef MINTON_DVD//wuxiaofeng changed here 02-27 for minton DVD.
        psprintf(buf, "[%s]%s.JPEG", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
#else
    #ifdef ISO9660_FILE_NOT_SHOW_EXTEND_NAME     //gerry,2004-2-26 10:53
		psprintf(buf, "[%s]%s", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
    #else//ISO9660_FILE_NOT_SHOW_EXTEND_NAME
		#ifdef SHOW_CDROM_TOTAL_FILE
		psprintf(buf, "%s.JPG", iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
		#else
		psprintf(buf, "[%s]%s.JPG", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
                   #endif
    #endif//ISO9660_FILE_NOT_SHOW_EXTEND_NAME
#endif
	}
    /*============================GAME=======================*/
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
	else if (pFsJpeg->gifsFuncBtn == FS_FUNC_GAME)
		psprintf(buf, "%s [%dK]", iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].size / 1000);
#endif
    /*============================OTHER=======================*/
#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 021001
	else if (pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)
    {   // yltseng 20040412 show file extension
    #ifndef ISO9660_FILE_NOT_SHOW_EXTEND_NAME
        #ifdef TELL_FROM_MP4_EXT_NAME   //Maoyong
        if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].file_type == CDROM_MP4 )
        {
            #ifdef TEMPORARY_FIX_WMA_EXTENSION
                #if defined(SUPPORT_AUD_WMA) && defined(SUPPORT_ASF)
                    if(iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].dir == CDROM_WMA)
                        psprintf(buf, "[%s]%s.WMA", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
                    else
                #endif
            #endif  //#ifdef TEMPORARY_FIX_WMA_EXTENSION
            #ifdef MPEG_FILE_TELL_THE_CORRECT_EXTER_NAME//libing 2005-9-27 14:00
            if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].dir == CDROM_MPEG )
            {
            	psprintf(buf, "[%s]%s.MPEG", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        	}
        	else
        	if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].dir == CDROM_MPG )
            {
            	psprintf(buf, "[%s]%s.MPG", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        	}
        	else
        	if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].dir == CDROM_DAT )
            {
            	psprintf(buf, "[%s]%s.DAT", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        	}
        	else
        	#endif
        	#ifdef TEMPORARY_FIX_OGG_EXTENSION                
            if(iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].dir == CDROM_OGG)
                psprintf(buf, "[%s]%s.OGG", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
            else                
            #endif
            psprintf(buf, "[%s]%s.MP4", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        }
        else if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].file_type == CDROM_AVI )
        {
            #ifdef TEMPORARY_FIX_WMA_EXTENSION
                #if defined(SUPPORT_AUD_WMA) && defined(SUPPORT_ASF)
                    if(iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].dir == CDROM_WMA)
                        psprintf(buf, "[%s]%s.WMA", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
                    else
                #endif
            #endif  //#ifdef TEMPORARY_FIX_WMA_EXTENSION
            psprintf(buf, "[%s]%s.AVI", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        }
        #ifdef SUPPORT_QUICKTIME
        else if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].file_type == CDROM_M4A )
        {
            #ifdef TEMPORARY_FIX_WMA_EXTENSION
                #if defined(SUPPORT_AUD_WMA) && defined(SUPPORT_ASF)
                    if(iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].dir == CDROM_WMA)
                        psprintf(buf, "[%s]%s.WMA", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
                    else
                #endif
            #endif  //#ifdef TEMPORARY_FIX_WMA_EXTENSION
            psprintf(buf, "[%s]%s.M4A", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        }
        #endif //#ifdef SUPPORT_QUICKTIME
        else if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].file_type == CDROM_DIV )
        {
            #ifdef TEMPORARY_FIX_WMA_EXTENSION
                #if defined(SUPPORT_AUD_WMA) && defined(SUPPORT_ASF)
                    if(iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].dir == CDROM_WMA)
                        psprintf(buf, "[%s]%s.WMA", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
                    else
                #endif
            #endif  //#ifdef TEMPORARY_FIX_WMA_EXTENSION
            psprintf(buf, "[%s]%s.DIV", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        }
        #else
        if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].file_type == CDROM_MP4 )
        {
            #ifdef TEMPORARY_FIX_WMA_EXTENSION
                #if defined(SUPPORT_AUD_WMA) && defined(SUPPORT_ASF)
            if(iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].dir == CDROM_WMA)
                psprintf(buf, "[%s]%s.WMA", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
            else
                #endif
            #endif  //#ifdef TEMPORARY_FIX_WMA_EXTENSION
            psprintf(buf, "[%s]%s.MP4", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        }
        #endif  //#ifdef TELL_FROM_MP4_EXT_NAME
        else if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].file_type == CDROM_MPG )
        {    
            psprintf(buf, "[%s]%s.MPG", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        }
        #ifdef SUPPORT_PLAY_SWD
        else if( iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].file_type == CDROM_SWD )
            psprintf(buf, "[%s]%s.SWD", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
        #endif
        else
    #endif  //#ifndef ISO9660_FILE_NOT_SHOW_EXTEND_NAME
		psprintf(buf, "[%s]%s", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
    }
#endif
    /*============================MIDI=======================*/
#ifdef SUPPORT_MIDI
	else if (pFsJpeg->gifsFuncBtn == FS_FUNC_MIDI)
		psprintf(buf, "[%s]%s", iso9660_dir[pFsJpeg->fsnav_dir_now].name, iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);
#endif

#ifdef SHOW_CDROM_TOTAL_FILE
	psprintf(buf2," %d/%d",FSGUI_GetDispTrack(),mp3_file_count());
	strcat1(buf,buf2);
#endif

#ifdef SUPPORT_FS_LONGNAME  //Maoyong 2004.06.24
    if( GetFileFullName(pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry) ){
        if( uScrollDispFilenameFlag ==1 ){
            uScrollDispFilenameFlag = SCROLL_SHOW_500MS_CNT;    //for first display
            FS_ScrollDispFileName();
        }else{
            psprintf(linebuf, "[%s]%s", iso9660_dir[pFsJpeg->fsnav_dir_now].name, uFullFilename);
            FSGUI_UpdateInfoArea(linebuf);
        }
    }else   //can't read succesfully, just use the old way for file name
	FSGUI_UpdateInfoArea(buf);
#else   //#ifdef SUPPORT_FS_LONGNAME
        FSGUI_UpdateInfoArea(buf);
#endif  //#ifdef SUPPORT_FS_LONGNAME

#ifdef FSGUI_NO_BLINK_SCROLL
	strcpy(tempbuf,buf);
#endif
}
#endif	//#ifdef GPS_MP3_UI




int PrepareForChangeFilePage(UINT16 iPage, UINT16 iSpecialTrk, UINT16 iDirect)
{
	int i, j = 0;
	UINT16 iFileFirst;

	iFileFirst = AnchorFile(iPage * PER_PAGE);

	if(iPage == pFsJpeg->File_Page_Count - 1) // the last page
		pFsJpeg->File_Count = pFsJpeg->file_specify_in_dir - (pFsJpeg->File_Page_Count - 1) * PER_PAGE;
	else
		pFsJpeg->File_Count = PER_PAGE;

	i = iFileFirst + pFsJpeg->first_mp3_entry;

	while (j < PER_PAGE )
	{
		if (iso9660_file[i].type == pFsJpeg->gifsFuncBtn)
		{
			pFsJpeg->file_array[j] = i;
			j++;
		}
		i++;

    #ifdef FS_LOAD_DIR_SEPARATELY
		if(i>pFsJpeg->last_mp3_entry) break;//kevinmonkey 050428 why not this?
    #else  //!FS_LOAD_DIR_SEPARATELY
		if(i>pFsJpeg->iso9660_file_cnt) break;//terry,2004/2/25 06:42PM
    #endif //#ifdef FS_LOAD_DIR_SEPARATELY
	}

	if(iDirect == 0)
	{
		// next page operation
		pFsJpeg->file_will = 0;
	}
	else if(iDirect == 1)
	{
		// prev page operation
		pFsJpeg->file_will = pFsJpeg->File_Count - 1;
	}
	else if(iDirect == 2)
	{
		// direct select operation
		pFsJpeg->file_will = iSpecialTrk % PER_PAGE;
	}
	pFsJpeg->fsnav_trk_will = pFsJpeg->file_array[pFsJpeg->file_will] - pFsJpeg->first_mp3_entry;

	refresh_file_page = 1;
	if (pFsJpeg->File_Count != PER_PAGE)
	{
		for(i = pFsJpeg->File_Count; i < PER_PAGE; i++)
			pFsJpeg->file_array[i] = 0;		// for check whether flash file icon,panxing,2002-4-13
	}
	return 0;
}


//
// Base on fsnav_dir_now to prepare for when change directory(indexing to page-0 file-0).
// iDirect = 0 means: select next directory
// iDirect = 1 means: select prev directory
//
int FSGUI_PreChangeDir(UINT16 *iDir,UINT16 iDirect)
{
	int done = 0;
 #if defined(MP3_POWER_RESUME)||defined(FS_FILE_POWER_RESUME)
	 UINT32 fsnav_trk_now = 0 ;
 #endif 

#ifdef MP3_POWER_RESUME// 0//def POWER_RESUME//mp3 power_resume need to be fix again later.
	UINT32 fsnav_trk_now = 0 ;
	fsnav_trk_now = ReadSameMP3Para ( 1 ) ;
#endif   // POWER_RESUME , added by caiyh , 14:12 , Nov 5th , 2004

#ifdef FS_FILE_POWER_RESUME //qinhua,2006-6-13 05:03下午 //UINT32 fsnav_trk_now = 0 ;
if(IsTheSameDisc())
	{	
	 fsnav_trk_now = resumeTRK; 
   resumeTRK=0;
  }
#endif    

	done =FSGUI_PreFindDir(iDir,iDirect);

	CalcDirNow(iDir);

#ifdef FS_LOAD_DIR_SEPARATELY  //kevinmonkey 050428 load the directory
    extern int gi_FSLoadedDir;
    //the condition below (*iDir != gi_FSLoadedDir)->when choose the same dir, no need to reload
    //(pFsJpeg->dir_current == 0)->when a directory has both mp3 and jpeg, and it just happens to 
    //be the first dir of both category, then it becomes the situation that it the same directory 
    //but need to reload. Note: we need pFsJpeg->dir_current here, which is calculated in CalcDirNow
    //so CalcDirNow is moved to above.
    if((*iDir != gi_FSLoadedDir) || (pFsJpeg->dir_current == 0))  //kevinmonkey 0510
    {
//        PrintOsdMsg(STR_OS_READ, REGION1, 1, 1);
//        osd_tog_region(1, OSD_ON);  //show read before OPU moves
        extern int load_iso9660_files(int index);
        load_iso9660_files(*iDir);
    }
#endif
printf("pFsJpeg->iso9660_file_cnt in prechange dir : %d\n",pFsJpeg->iso9660_file_cnt);
	CalcFileFirstPage(*iDir);


#ifdef MP3_POWER_RESUME// 0//def POWER_RESUME//mp3 power_resume need to be fix again later.
	if ( IsTheSameMP3 ( ) )
		PrepareForChangeFilePage( fsnav_trk_now / PER_PAGE , 
			fsnav_trk_now , 2 ) ;
		// show the page for resuming , added by caiyh , 14:12 , Nov 5th , 2004
	else
#endif   // POWER_RESUME , added by caiyh , 14:12 , Nov 5th , 2004

#ifdef FS_FILE_POWER_RESUME //qinhua,2006-6-13 05:03下午 
	 if(IsTheSameDisc()) 
		{
		 PrepareForChangeFilePage( fsnav_trk_now / PER_PAGE , fsnav_trk_now , 2 ) ;
		}
	 else
#endif  
	PrepareForChangeFilePage(0,0,0);
	Will2Playing();
	//refresh_file_page 	= 1;
	return done;
}

int FSGUI_PreFindDir(UINT16 *iDir,UINT16 iDirect)
{
	int done = 0;
	UINT16 old_mp3_dir = 0;

	old_mp3_dir = *iDir;

	while(!(iso9660_dir[*iDir].type & (0x01 << pFsJpeg->gifsFuncBtn)))
	{
		if(iDirect == 0)
		{
			if(*iDir < pFsJpeg->fsnav_dir_cnt - 1)
				(*iDir)++;
			else
			{
				// old_mp3_dir is the last directory include file specified style, panxing, 2002-1-22
				done = 1;
				break;
			}
		}
		else
		{
			if(*iDir>0)
				(*iDir)--;
			else
			{
				// old_mp3_dir is the first directory include file specified style, panxing, 2002-1-22
				done = 1;
				break;
			}
		}
	}

	if(done)
	{
		// restore fsnav_dir_now, panxing, 2002-1-22
		if(iDirect == 0)
			*iDir = (old_mp3_dir - 1);
		else
			*iDir = (old_mp3_dir + 1);
		refresh_dir_icon = 0;
	}
	return done;
}
//
// List directory item and clear refresh_dir_page
//
void DirList()
{
	UINT16 i;
	UINT16 j;

	if (!refresh_dir_page)
		return;

	#ifdef FS_BMP_GUI
	    FSGUI_ClearArea(FS_AREA_DIRITEM,PER_PAGE+1);
	//2006-06-02, mimitsai add for HD ui.
	#else
	   	ClearRectArea(Rect[DIR_RECT], DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB, FS_AREA_DIRITEM, -1);//zhaoyanhua add
    #endif

	i = pFsJpeg->dir_page_now * PER_PAGE;
	j = 0;

	while (j < pFsJpeg->Dir_Count && i < pFsJpeg->fsnav_dir_cnt)
	{
		if (iso9660_dir[i].dir > 0 ) {
			ShowDirItem(j, iso9660_dir[pFsJpeg->dir_array[j]].name);
			j++;
		}
		i++;
	}

	refresh_dir_page = 0;
}


//
// Calculate dir_page_now,dir_current,Dir_Count according to fsnav_dir_now
// and refresh_dir_page is determine
// dir_page_now: range=(0 ~ x)
// dir_current:  range=(0 ~ x)
// Dir_Count:    range=(1 ~ x)
//
void CalcDirNow(UINT16 *iDir)
{
	int i;
	int j = 0;
	int seq = 0;
	int first = 0;

	old_dir_page = pFsJpeg->dir_page_now;

	seq = antiAnchorDir(*iDir);
	pFsJpeg->dir_page_now = seq / PER_PAGE;

	seq = 0;

	for (i = 0; i < pFsJpeg->fsnav_dir_cnt; i++)
	{
		if (iso9660_dir[i].type & (0x01 << pFsJpeg->gifsFuncBtn))
		{
			if(first == pFsJpeg->dir_page_now * PER_PAGE)
			{
				// Now seq is the first directory in this dir page, panxing, 2002-1-29
				break;
			}
			first++;
		}
		seq++;
	}

	pFsJpeg->Dir_Count = 0;
	j = 0;

	//	printf("dir_page_now = %d, first = %d, seq = %d\n", pFsJpeg->dir_page_now,first,seq);

	for (i = seq; i < pFsJpeg->fsnav_dir_cnt; i++)
	{
		if (iso9660_dir[i].type & (0x01 << pFsJpeg->gifsFuncBtn))
		{
			pFsJpeg->dir_array[j] = i;
			if(i == *iDir)
				pFsJpeg->dir_current = j;
			j++;
		}
		if(j == PER_PAGE)
			break;
	}

	pFsJpeg->Dir_Count = j;

	//printf("old_dir_page = %d, dir_page_now = %d\n", old_dir_page, pFsJpeg->dir_page_now);

	if(old_dir_page != pFsJpeg->dir_page_now)
	{
		refresh_dir_page = 1;
		refresh_dir_icon = 1;
	}

	return;
}

void FS_ForceReturn2Menu(void)//used when NEW_STYLE_SETUP
{
#ifdef NEW_STYLE_SETUP  //to return from setup state. zhaoyanhua add 2003-8-7 8:58
	pFsJpeg->gifsState	= FS_STATE_LIST;
	play_state = VCD_STATE_MP3_FILELIST;
	adv_search_time = 0;
	video_slow = 0;

   	#ifdef MEM_GRAPH_LARGE //2006-06-02, mimitsai add for HD ui.
	config_memeory(MEMORY_GRAPH_NTSC);
	#else
	config_memory(MEMORY_GRAPH_SMALL);
	#endif

	setup_tv_format(tv_format);
    #endif//NEW_STYLE_SETUP

    FSGUI_Menu();
	pFsJpeg->gbfsSlide	= 0;
	//zhaoyanhua masked for NEW_MP3_GUI for NEW_STYLE_SETUP. 3-7-25 20:17
	#if !(defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI))//2006-06-02, mimitsai add for HD ui.
	pFsJpeg->gifsbPreview = 1; // Robert 20020715
	refresh_file_page 	= 1; // insure refresh dir page, panxing, 2002-1-22
	refresh_dir_page 	= 1;
	#endif
	pFsJpeg->gifsState	= FS_STATE_LIST;

#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
	//zhaoyanhua add 3-7-25 20:17
    if ((JPEG_Preview_drawed == JPEG_PREVIEW_IN_DIR_AREA ) )
    {
    	JPEG_Preview_drawed = DIR_LIST_IN_DIR_AREA;
        pFsJpeg->gifsbPreview = 1;
        flagRefresh = 1;//note now state is refresh.
        refresh_dir_page  = 0;//when return to JPEG preview ,not show DIR.
        FileList();//to avoid the bug: when MENU/RETURN, can not show correctly in FILE AREA zhaoyanhua add 2004-1-12 18:09
        #ifdef INDIGO_STYLE_FSGUI
		FSGUI_Refresh();        
		#endif
	}
    else
    {
    	refresh_file_page   = 1;
        refresh_dir_page = 1;
        FSGUI_Refresh();
	}
#else
	FSGUI_Refresh();
#endif
}

void FSGUI_Return2Menu(void)
{
    if ((pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG) && (pFsJpeg->gifsState == FS_STATE_JPEG))
    {
        //set to normal display ratio/offset, Jeff 20030722
        reset_zoom_state();//return menu
        startup_vpp();

        //Maoyong added 2004-8-12 18:04 for initialization when define ZOOM_DIRECT_STOP_SLIDE, normally do seq play again
        #ifdef ZOOM_DIRECT_STOP_SLIDE
        jpg_slide_time = JPEG_SLIDE_TIME;
        #endif

#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined (INDIGO_STYLE_FSGUI)
        ClearOsdMsg(2);
        pFsJpeg->gbfsSlide  = 0;
        pFsJpeg->gifsState  = FS_STATE_LIST;
#else
	//#if !defined(JPEG_SLIDE_SHOW_USE_PROG)
		ClearOsdMsg(2);//nono 3-12-24 22:48 for PROG ON, it will turn off PROG MENU.
	//#endif
#endif

        AVD_ResetMediaStatus();
       #if defined(FALSE_POWER)&&defined(STOP_LOADER)//zhuyanfeng20041008	
		pFsJpeg->gifsbPreview = 0;
		ShowTitle();
        #else
        FS_ForceReturn2Menu();
		#endif	
    }
    pFsJpeg->ControlArea = CNT_AREA_FILE;
}

#ifdef INDIGO_STYLE_FSGUI
void FSGUI_UpdateInfoArea(BYTE* strInfo)
{
	//2006-06-02, mimitsai add for HD ui.
	DrawRectCorner(Rect[PATH_RECT], 6,1, 0, INFO_AREA_BG_Y, INFO_AREA_BG_Y, INFO_AREA_BG_CbCr);
	
	is_show_path_info_string =1;
    FSGUI_ShowString(fsArea[FS_AREA_PATHINFO].xStart+INFO_X_OFFSET,
        			 fsArea[FS_AREA_PATHINFO].yStart,
        			 strInfo, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
}

#elif defined(NEW_MP3_GUI)
void FSGUI_UpdateInfoArea(BYTE* strInfo)
{

	#ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
	#endif

#ifdef NEW_MP3_GUI

	#ifdef MONO_FSGUI   //mono FS GUI, axel 2003-12-29 23:26
	//2006-06-02, mimitsai add for HD ui.
    DrawRectCorner(Rect[PATH_RECT], 6,1,  1, 0x36, 0xc1, DIR_AREA_BKGROUND_CRCB );
	#else
    DrawRectCorner(Rect[PATH_RECT], 6,1, DIR_STEP, 0x36, 0xc1, DIR_AREA_BKGROUND_CRCB );//chenzhao20050613 PHILIPS_FSGUI
	#endif

	#ifdef MP3_LARGE_GUI
	FSGUI_ShowString(fsArea[FS_AREA_PATHINFO].xStart /*+ 40*/, //denghg modify display 2006-6-10 10:10
        fsArea[FS_AREA_PATHINFO].yStart + 2,
        strInfo, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
	#else
	is_show_path_info_string =1;//wangw add 20060831
    FSGUI_ShowString(fsArea[FS_AREA_PATHINFO].xStart+INFO_X_OFFSET,
        Y1-18,
        strInfo, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
	#endif
#else	//NEW_MP3_GUI

	FSGUI_FillFrameBuf(fsArea[FS_AREA_PATHINFO].xStart+INFO_X_OFFSET,fsArea[FS_AREA_PATHINFO].yStart,
		fsArea[FS_AREA_PATHINFO].xSize,fsArea[FS_AREA_PATHINFO].ySize,
		BK_GROUNDY,BK_GROUNDCRCB);

	FSGUI_ShowString(fsArea[FS_AREA_PATHINFO].xStart+INFO_X_OFFSET,
		Y1-18,
		strInfo, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
#endif	//#ifdef NEW_MP3_GUI
}

#else //#if !defined (FS_BMP_GUI)
/*
 * Description:
 *      Update the Info area about current dir and file.
 * INPUT:
 *	The string infomation about current dir and file.
 *	And it is decided by func FSGUI_CookFileItem()
 *Creater:
 *	feeling
 *Date:
 *	2004-06-08
 */
void FSGUI_UpdateInfoArea(BYTE* strInfo)
{
	#ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
	#endif

    //update the background,
    //note:avoid redraw the rotating icon and the left and right sides
    //the width of the icon and left side totally are about 45
	#define INFO_STR_XSTART	45
	
#ifdef GPS_MP3_UI//frank.huang 050915


	if(pFsJpeg->gifsFuncBtn == FS_FUNC_MP3
		#ifdef USE_FSGUI_TO_PLAY_CD//frank.huang add 051014
		&&cd_type_loaded==CDROM
		#endif
		)
	{
		FSGUI_FillFrameBuf(140,0,580,135,BK_GROUNDY,BK_GROUNDCRCB);//frank.huang 050927 move this in order not to show in jpeg page
		FSGUI_DrawBackGround(fsArea[FS_AREA_PATHBACKGROUND].xStart + INFO_STR_XSTART,//or it will flash in jpeg when FSGUI_CmdDown run
		fsArea[FS_AREA_PATHBACKGROUND].yStart,
		fsArea[FS_AREA_PATHBACKGROUND].xSize - INFO_STR_XSTART,
		fsArea[FS_AREA_PATHBACKGROUND].ySize,
		LAY_PLAYING_BAR_3_2);	

		FSGUI_DrawBackGround(fsArea[FS_AREA_ARTIST_INFO].xStart+INFO_STR_XSTART ,
		fsArea[FS_AREA_ARTIST_INFO].yStart,
		fsArea[FS_AREA_ARTIST_INFO].xSize - INFO_STR_XSTART,
		fsArea[FS_AREA_ARTIST_INFO].ySize,
		LAY_PLAYING_BAR_3_2);	



		FSGUI_LayPosVariableBmp(fsArea[FS_AREA_PATHBACKGROUND].xStart+INFO_STR_XSTART-23, 
		  	fsArea[FS_AREA_PATHBACKGROUND].yStart,PATH_INFO_BAR_L);
		
		FSGUI_LayPosVariableBmp(fsArea[FS_AREA_PATHBACKGROUND].xStart+fsArea[FS_AREA_PATHBACKGROUND].xSize, 
			fsArea[FS_AREA_PATHBACKGROUND].yStart,PATH_INFO_BAR_R);

		FSGUI_LayPosVariableBmp(fsArea[FS_AREA_ARTIST_INFO].xStart+INFO_STR_XSTART-23, 
		  	fsArea[FS_AREA_ARTIST_INFO].yStart,PATH_INFO_BAR_L);
		
		FSGUI_LayPosVariableBmp(fsArea[FS_AREA_ARTIST_INFO].xStart+fsArea[FS_AREA_ARTIST_INFO].xSize, 
			fsArea[FS_AREA_ARTIST_INFO].yStart,PATH_INFO_BAR_R);

		
		FSGUI_LayPosVariableBmp(fsArea[FS_AREA_TIME_INFO].xStart+INFO_STR_XSTART-23, 
			fsArea[FS_AREA_TIME_INFO].yStart,PATH_INFO_BAR_L);
				
		FSGUI_LayPosVariableBmp(fsArea[FS_AREA_TIME_INFO].xStart+fsArea[FS_AREA_TIME_INFO].xSize, 
			fsArea[FS_AREA_TIME_INFO].yStart,PATH_INFO_BAR_R);

		FSGUI_DrawBackGround(fsArea[FS_AREA_TIME_INFO].xStart+INFO_STR_XSTART ,
		        fsArea[FS_AREA_TIME_INFO].yStart,
		        fsArea[FS_AREA_TIME_INFO].xSize - INFO_STR_XSTART,
		        fsArea[FS_AREA_TIME_INFO].ySize,
		        LAY_PLAYING_BAR_3_2);			
		
	    psprintf(timebuf,"%02d:%02d",0,0);								//S:fix bug:当时间00：00，时间显示会闪烁。suxin 2005-09-21
	    FSGUI_ShowString(fsArea[FS_AREA_TIME_INFO].xStart+INFO_STR_XSTART,
		    fsArea[FS_AREA_TIME_INFO].yStart+3,timebuf, 
		    FS_FONTCOLOR_PATH_Y, FS_FONTCOLOR_PATH_CrCb);
		
		FSGUI_ShowString(fsArea[FS_AREA_PATHINFO].xStart+35,
			fsArea[FS_AREA_PATHINFO].yStart, strInfo,
			FS_FONTCOLOR_PATH_Y,
			FS_FONTCOLOR_PATH_CrCb);
			
	}
	else
	{
	FSGUI_FillFrameBuf(140,0,580,135,BK_GROUNDY,BK_GROUNDCRCB);
	FSGUI_DrawBackGround(fsArea[FS_AREA_PATHBACKGROUND].xStart + INFO_STR_XSTART,
		MID_BAR_LOC,
		fsArea[FS_AREA_PATHBACKGROUND].xSize - INFO_STR_XSTART,
		fsArea[FS_AREA_PATHBACKGROUND].ySize,
		LAY_PLAYING_BAR_3_2);	
	
	    #ifdef USE_FSGUI_TO_PLAY_CD//frank.huang add 051014
	    if(cd_type_loaded==CDDA)
	    {
		    psprintf(timebuf,"%02d:%02d",0,0);		//S:fix bug:当时间00：00，时间显示会闪烁。suxin 2005-09-21
		    FSGUI_ShowString(fsArea[FS_AREA_TIME_INFO].xStart+INFO_STR_XSTART,
				        MID_BAR_LOC+3,timebuf, FS_FONTCOLOR_PATH_Y, FS_FONTCOLOR_PATH_CrCb);
	    }
	    #endif

	FSGUI_LayPosVariableBmp(fsArea[FS_AREA_PATHBACKGROUND].xStart+INFO_STR_XSTART-23, 
		MID_BAR_LOC,PATH_INFO_BAR_L);

	FSGUI_LayPosVariableBmp(fsArea[FS_AREA_PATHBACKGROUND].xStart+fsArea[FS_AREA_PATHBACKGROUND].xSize, 
		MID_BAR_LOC,PATH_INFO_BAR_R);
	
    //show the dir and file playing string
	FSGUI_ShowString(fsArea[FS_AREA_PATHINFO].xStart + 35,
		MID_BAR_LOC+3, strInfo,//wanghaoying 2->3 20051026
		FS_FONTCOLOR_PATH_Y,
		FS_FONTCOLOR_PATH_CrCb);
	}

#else//#ifdef GPS_MP3_UI

    //show the dir and file playing string
	FSGUI_DrawBackGround(fsArea[FS_AREA_PATHBACKGROUND].xStart + INFO_STR_XSTART,
		fsArea[FS_AREA_PATHBACKGROUND].yStart,
		fsArea[FS_AREA_PATHBACKGROUND].xSize - INFO_STR_XSTART,
		fsArea[FS_AREA_PATHBACKGROUND].ySize,
		LAY_PLAYING_BAR_3_2);
	FSGUI_ShowString(fsArea[FS_AREA_PATHINFO].xStart,
		fsArea[FS_AREA_PATHINFO].yStart, strInfo,
		FS_FONTCOLOR_PATH_Y,
		FS_FONTCOLOR_PATH_CrCb);
#endif	//#ifdef GPS_MP3_UI

}
#endif //#if !defined (FS_BMP_GUI)
void FSGUI_Shuffle()
{
	// generate a random directory, panxing, 2002-1-22
	// use one while loop to avoid no specify style file in the random directory, panxing, 2002-1-22
	do
	{
		pFsJpeg->fsnav_dir_will = regs0->stc_15_0 % pFsJpeg->fsnav_dir_cnt;
	} while (FSGUI_PreChangeDir(&(pFsJpeg->fsnav_dir_will), 0));

	pFsJpeg->fsnav_dir_now = pFsJpeg->fsnav_dir_will;
	// generate a random file page, panxing, 2002-1-22
	pFsJpeg->file_page_will = regs0->stc_15_0 % pFsJpeg->File_Page_Count;
	PrepareForChangeFilePage(pFsJpeg->file_page_will, pFsJpeg->file_page_will * PER_PAGE, 2);

	// generate a random file_curent pointer, panxing, 2002-1-22
	pFsJpeg->file_will = regs0->stc_15_0 % pFsJpeg->File_Count;
	pFsJpeg->fsnav_trk_will = pFsJpeg->file_array[pFsJpeg->file_will] - pFsJpeg->first_mp3_entry;
	Will2Playing();
	refresh_file_page = 1;
	refresh_dir_page = 1;
	refresh_dir_icon = 1;
}

#ifdef SHUFFLE_ACCOMPLISH_BY_ARITHMETIC
int shuffle_frist_trk;
int shuffle_file_repeat_flag = 0;
int shuffle_file_now;
extern UINT8 root_dir_have_file_flag;

void FSGUI_Shuffle_New()
{
     int shuffle_file_begin;
     int cnt = 0,cnt2 = 0;
     int shuffle_temp;
     int fsnav_trk_now_temp,same_type_file_in_dir=0;
     
     #ifdef SHUFFLE_ABA_DEBUG
            psprintf(linebuf,"pFsJpeg->fsnav_trk_now= %d........\n",pFsJpeg->fsnav_trk_now);
            io_write_wait(linebuf);
      #endif
      
     shuffle_file_begin = pFsJpeg->first_mp3_entry + pFsJpeg->fsnav_trk_now;
     shuffle_temp = shuffle_new(shuffle_file_begin, pFsJpeg->iso9660_file_cnt - 1);
     
     while( cnt  <=  pFsJpeg->iso9660_file_cnt  )
     {
         if( iso9660_file[shuffle_temp].type != pFsJpeg->gifsFuncBtn )
         {
             shuffle_temp = shuffle_next(shuffle_temp);
         }
         else
         { 
              #ifdef SHUFFLE_ABA_DEBUG
                    psprintf(linebuf,"cntbefore = %d........\n",cnt);
                    io_write_wait(linebuf);
              #endif
             cnt = 0;
             break;
         }
         cnt++;         
      }
      
    #ifdef SHUFFLE_ABA_DEBUG
        psprintf(linebuf,"shuffle_temp = %d........\n",shuffle_temp);
        io_write_wait(linebuf);
    #endif
    
      if(cnt == pFsJpeg->iso9660_file_cnt + 1)
      {
          ircmd_stop();
          shuffle_file_repeat_flag = 0;
          return;

      }
      else
      {
          shuffle_frist_trk = shuffle_temp;
          shuffle_file_now = shuffle_temp;
          
            #ifdef SHUFFLE_ABA_DEBUG
                psprintf(linebuf,"shuffle_frist_trk  = %d........\n", shuffle_frist_trk );
                io_write_wait(linebuf);
            #endif
            
          for( cnt = pFsJpeg->fsnav_dir_cnt - 1; cnt>=0; cnt-- )
          {
                if( (shuffle_temp -pFsJpeg->Dir_entry[ cnt ]) >= 0 )
                {
                    break;
                }
          }

            #ifdef SHUFFLE_ABA_DEBUG
                psprintf(linebuf,"cnt  = %d........\n", cnt );
                io_write_wait(linebuf);
                psprintf(linebuf,"pFsJpeg->Dir_entry[ cnt ] = %d........\n",pFsJpeg->Dir_entry[ cnt ]);
                io_write_wait(linebuf);
                psprintf(linebuf,"shuffle_temp = %d........\n",shuffle_temp);
                io_write_wait(linebuf);
            #endif
            
          if( cnt < 0 )
          {
              ircmd_stop();
              shuffle_file_repeat_flag = 0;
              return;

          }
          else if( cnt >= 0 )
          {
              fsnav_trk_now_temp = shuffle_temp -pFsJpeg->Dir_entry[ cnt ];
             // frist_mp3_entry_temp = pFsJpeg->Dir_entry[ cnt ];
              for( cnt2 = 0; cnt2 < fsnav_trk_now_temp ; cnt2++ )
              {
                  if( iso9660_file[ cnt2 + pFsJpeg->Dir_entry[ cnt ] ].type == pFsJpeg->gifsFuncBtn )
                      same_type_file_in_dir ++;
              }
               pFsJpeg->fsnav_dir_now = pFsJpeg->fsnav_dir_will = cnt;
              FSGUI_PreChangeDir(&( pFsJpeg->fsnav_dir_now), 0);
              pFsJpeg->file_page_will= (same_type_file_in_dir/*-1*/) / PER_PAGE; //denghg modify 2006-3-16 10:47
              if( root_dir_have_file_flag == 1)
              {
                  if( pFsJpeg->fsnav_dir_now == 0 )
                     pFsJpeg->dir_current =  pFsJpeg->fsnav_dir_now;
                  else
                     pFsJpeg->dir_current =  pFsJpeg->fsnav_dir_now - 1;
               }
              else
                  pFsJpeg->dir_current =  pFsJpeg->fsnav_dir_now;
              PrepareForChangeFilePage(pFsJpeg->file_page_will,same_type_file_in_dir,2);
	       Will2Playing();
             refresh_file_page = 1;
	      refresh_dir_page = 1;
	      refresh_dir_icon = 1;
          }
     }
     FSGUI_Refresh();
}

void FSGUI_Shuffle_Next()   //wangmin add for real shuffle in cdrom 051021
{
        //int shuffle_file_now;
        int cnt = 0,cnt2 = 0;
        int shuffle_temp;
        int fsnav_trk_now_temp,same_type_file_in_dir=0;
        
        //shuffle_file_now = pFsJpeg->first_mp3_entry + pFsJpeg->fsnav_trk_now;
        shuffle_temp = shuffle_next(shuffle_file_now);

      while( cnt  <=  pFsJpeg->iso9660_file_cnt  )
     {
         if( iso9660_file[shuffle_temp].type != pFsJpeg->gifsFuncBtn )
         {
             shuffle_temp = shuffle_next(shuffle_temp);
         }
         else
         {
             cnt = 0;
             break;
         }
         cnt++;         
      }
      
       #ifdef SHUFFLE_ABA_DEBUG
            psprintf(linebuf,"shuffle_temp = %d........\n",shuffle_temp);
            io_write_wait(linebuf);
        #endif
        
      if(cnt == pFsJpeg->iso9660_file_cnt +1 )
      {
       #ifdef SHUFFLE_ABA_DEBUG
           io_write_wait("more than iso9660_file_cnt so out......\n");
       #endif
           ircmd_stop();
           shuffle_file_repeat_flag = 0;
           return;

      }
      else
      {
          for( cnt = pFsJpeg->fsnav_dir_cnt - 1; cnt >= 0; cnt-- )
          {
                if( (shuffle_temp -pFsJpeg->Dir_entry[ cnt ]) >= 0 )
                {
                    break;
                }
                
          }

        #ifdef SHUFFLE_ABA_DEBUG
                psprintf(linebuf,"cnt  = %d........\n", cnt );
                io_write_wait(linebuf);
                psprintf(linebuf,"pFsJpeg->Dir_entry[ cnt ] = %d........\n",pFsJpeg->Dir_entry[ cnt ]);
                io_write_wait(linebuf);
                psprintf(linebuf,"shuffle_temp = %d........\n",shuffle_temp);
                io_write_wait(linebuf);
        #endif
          if( cnt < 0 )
          {
              ircmd_stop();
              shuffle_file_repeat_flag = 0;
              return;

          }
          else if( cnt >= 0 )
          {
             if( shuffle_temp == 0 )         //when the frist file of one disc is the type which shuffle now, if we suffle_next == 0,the frist will be play.
             {                                         //actually when the shuffle_next's result is 0 , that means the shuffle is over(after that the shuffle_next will be remain 0). but we need the frist file to play.
                 if( shuffle_file_repeat_flag == 0 )   //so i add "if(shuffle_temp == 0)" to make the frist file play one time, and stop after this time.
                 {
                    shuffle_file_repeat_flag = 1;
                 }
                 else
                 {
                     ircmd_stop();
                     shuffle_file_repeat_flag = 0;
                     return;
                 }
             }
             shuffle_file_now = shuffle_temp;
              fsnav_trk_now_temp = shuffle_temp -pFsJpeg->Dir_entry[ cnt ];
             // frist_mp3_entry_temp = pFsJpeg->Dir_entry[ cnt ];
              for( cnt2 = 0; cnt2 < fsnav_trk_now_temp ; cnt2++ )
              {
                  if( iso9660_file[ cnt2 + pFsJpeg->Dir_entry[ cnt ] ].type == pFsJpeg->gifsFuncBtn )
                      same_type_file_in_dir ++;
              }
              pFsJpeg->fsnav_dir_now = pFsJpeg->fsnav_dir_will = cnt;
              FSGUI_PreChangeDir(&( pFsJpeg->fsnav_dir_now), 0);
              pFsJpeg->file_page_will= (same_type_file_in_dir/*-1*/) / PER_PAGE; //denghg modify for same_type_file_in_dir==10,will play 1,not is 11 2006-3-15 22:17
              if( root_dir_have_file_flag == 1)
               {
                  if( pFsJpeg->fsnav_dir_now == 0 )
                     pFsJpeg->dir_current =  pFsJpeg->fsnav_dir_now;
                  else
                     pFsJpeg->dir_current =  pFsJpeg->fsnav_dir_now - 1;
               }
              else
                  pFsJpeg->dir_current =  pFsJpeg->fsnav_dir_now;
              PrepareForChangeFilePage(pFsJpeg->file_page_will,same_type_file_in_dir,2);
	       Will2Playing();
          }
     }
	refresh_file_page = 1;
	refresh_dir_page = 1;
	refresh_dir_icon = 1;
	FSGUI_Refresh();
}

void FSGUI_Shuffle_Prev()   //wangmin add for real shuffle in cdrom 051021
{
	       // int shuffle_file_now;
        int cnt = 0,cnt2 = 0;
        int shuffle_temp;
        int fsnav_trk_now_temp,same_type_file_in_dir=0;
        
        //shuffle_file_now = pFsJpeg->first_mp3_entry + pFsJpeg->fsnav_trk_now;
        shuffle_temp = shuffle_prev(shuffle_file_now);

      while( cnt  <=  pFsJpeg->iso9660_file_cnt  )
     {
         if( iso9660_file[shuffle_temp].type != pFsJpeg->gifsFuncBtn )
         {
             shuffle_temp = shuffle_prev(shuffle_temp);
         }
         else
         {
             cnt = 0;
             break;
         }
         cnt++;         
      }
      
      if(cnt == pFsJpeg->iso9660_file_cnt + 1  )
      {
        #ifdef SHUFFLE_ABA_DEBUG
            io_write_wait("more than iso9660_file_cnt so out......\n");
        #endif
          ircmd_stop();
          shuffle_file_repeat_flag = 0;
          return;
      }
      else
      {
              if( shuffle_temp == shuffle_frist_trk )
              {
                  shuffle_file_repeat_flag= 1;
              }
              if(((shuffle_file_repeat_flag==1) && (shuffle_temp == 0)) || ( shuffle_temp == 0 ) ) 
              {
                #ifdef SHUFFLE_ABA_DEBUG
                    io_write_wait(" prve when frist trk play so out......\n");
                #endif
                  ircmd_stop();
                  shuffle_file_repeat_flag = 0;
                  return;
              }
              for( cnt = pFsJpeg->fsnav_dir_cnt - 1; cnt>=0; cnt-- )
              {
                    if( (shuffle_temp -pFsJpeg->Dir_entry[ cnt ]) >= 0 )
                    {
                        break;
                    }
              }

            #ifdef SHUFFLE_ABA_DEBUG
                    psprintf(linebuf,"cnt  = %d........\n", cnt );
                    io_write_wait(linebuf);
                    psprintf(linebuf,"pFsJpeg->Dir_entry[ cnt ] = %d........\n",pFsJpeg->Dir_entry[ cnt ]);
                    io_write_wait(linebuf);
                    psprintf(linebuf,"shuffle_temp = %d........\n",shuffle_temp);
                    io_write_wait(linebuf);
            #endif
            
              if( cnt < 0 )
              {  
                          ircmd_stop();
                          shuffle_file_repeat_flag = 0;
                          return;

              }
              else if( cnt >= 0 )
              {
              shuffle_file_now = shuffle_temp;
                  fsnav_trk_now_temp = shuffle_temp -pFsJpeg->Dir_entry[ cnt ];
                 // frist_mp3_entry_temp = pFsJpeg->Dir_entry[ cnt ];
                  for( cnt2 = 0; cnt2 < fsnav_trk_now_temp ; cnt2++ )
                  {
                      if( iso9660_file[ cnt2 + pFsJpeg->Dir_entry[ cnt ] ].type == pFsJpeg->gifsFuncBtn )
                          same_type_file_in_dir ++;
                  }
                      pFsJpeg->fsnav_dir_now = pFsJpeg->fsnav_dir_will = cnt;
                     FSGUI_PreChangeDir(&( pFsJpeg->fsnav_dir_now), 0);
                     pFsJpeg->file_page_will= (same_type_file_in_dir/*-1*/) / PER_PAGE;//denghg modify for same_type_file_in_dir==10,will play 1,not is 11 2006-3-15 22:17
                     if( root_dir_have_file_flag == 1)
                    {
                        if( pFsJpeg->fsnav_dir_now == 0 )
                            pFsJpeg->dir_current =  pFsJpeg->fsnav_dir_now;
                        else
                            pFsJpeg->dir_current =  pFsJpeg->fsnav_dir_now - 1;
                    }
                    else
                         pFsJpeg->dir_current =  pFsJpeg->fsnav_dir_now;
                     PrepareForChangeFilePage(pFsJpeg->file_page_will,same_type_file_in_dir,2);
                     Will2Playing();
              }
          
     }
	refresh_file_page = 1;
	refresh_dir_page = 1;
	refresh_dir_icon = 1;
	FSGUI_Refresh();
}

#endif

void FSGUI_JpgUpdateOSD(void)
{
#ifdef MP3_DIRECT_SELECT  //fengjl  edit to update VFD //axel 2003-12-26 14:36 update jpg info on VFD
		disp_trk_now = pFsJpeg->first_mp3_seq + pFsJpeg->file_page_now * PER_PAGE + pFsJpeg->file_current + 1;
#else
		disp_trk_now = pFsJpeg->file_page_now * PER_PAGE + pFsJpeg->file_current + 1;
#endif

    if(t_disp)
    {
        DispCookOSD0(1);
        DispPolling(0);
    }
}


int FSChkProg(BYTE iPage, BYTE iItem)
{
	int iRes=0;
	int iFileCount;

	// iPage is not page but directory, panxing, 2002-1-29
	if(iPage > pFsJpeg->count_dir[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3])
	{
		return 0;
	}

	iFileCount = CountSpecifyFile(AnchorDir(iPage-1));

	if(iFileCount == 0)
	{
		iRes = 0;
	}
	else
	{
		if (iItem <= iFileCount)
		{
			iRes = 1;
		}
	}

    return iRes;
}

int  FSGUI_GetDispTrack()
{
	int iRes;

#ifdef MP3_DIRECT_SELECT
	iRes = pFsJpeg->first_mp3_seq + pFsJpeg->file_page_now * PER_PAGE + pFsJpeg->file_current + 1;
#else
	iRes = pFsJpeg->file_page_now * PER_PAGE + pFsJpeg->file_current + 1;
#endif

	return iRes;
}


void FSGUI_2Last()
{
    refresh_dir_icon = 1;
    pFsJpeg->fsnav_dir_now = AnchorDir(pFsJpeg->count_dir[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3] - 1);
    pFsJpeg->dir_current = pFsJpeg->count_dir[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3] % PER_PAGE;

    FSGUI_PreChangeDir(&(pFsJpeg->fsnav_dir_now), 0);
    FSGUI_FileSelect(pFsJpeg->file_specify_in_dir);

    pFsJpeg->fsnav_dir_will = pFsJpeg->fsnav_dir_now; //Jeff 20020524
}

// 2006-03-16, mimitsai add
// calcute Dir and File scroll length, step.
void FSGUI_CalcuteDirFileScrollLen()
{
#ifdef FS_BMP_GUI
    //this for file scroll bar
    if (pFsJpeg->File_Page_Count != 1)// > PER_PAGE files all
    {
        pFsJpeg->scroll_len = ( fsArea[FS_AREA_MOVEBAR].ySize * PER_PAGE) /pFsJpeg->file_specify_in_dir;
        pFsJpeg->scroll_step = pFsJpeg->scroll_len;
    }
    else // <= PER_PAGE files all
    {
        pFsJpeg->scroll_step = 0;
        pFsJpeg->scroll_len = 0;
    }

    //this is for dir scroll bar
    dir_count_page = ( pFsJpeg->count_dir[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3]+ PER_PAGE - 1) / PER_PAGE;

    UINT16 dir_sum = pFsJpeg->count_dir[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3];

    if (dir_count_page != 1) // > PER_PAGE dirs all
    {
        dir_scroll_len = ( fsArea[FS_AREA_DIR_MOVEBAR].ySize * PER_PAGE) /dir_sum;
        dir_scroll_step = dir_scroll_len;
    }
    else // <= PER_PAGE files all
    {
        dir_scroll_step = 0;
        dir_scroll_len  = 0;
    }
#else
	// calcute the file area scroll bar and scroll length.
	pFsJpeg->File_Page_Count = (pFsJpeg->file_specify_in_dir + PER_PAGE - 1) / PER_PAGE;

	if (pFsJpeg->File_Page_Count != 1)
		pFsJpeg->scroll_len = fsArea[FS_AREA_MOVEBAR].ySize / pFsJpeg->File_Page_Count;
	else if (pFsJpeg->file_specify_in_dir != 1)
		pFsJpeg->scroll_len = fsArea[FS_AREA_MOVEBAR].ySize / 2;
	else
		pFsJpeg->scroll_len = fsArea[FS_AREA_MOVEBAR].ySize;

	if (pFsJpeg->scroll_len < 4)
		pFsJpeg->scroll_len = 4;

	if ((fsArea[FS_AREA_MOVEBAR].ySize - pFsJpeg->scroll_len) >= (pFsJpeg->file_specify_in_dir - 1))
	{
		// added by Jack Ciao 2006/10/3 12:53 for divide zero exception
		if (pFsJpeg->file_specify_in_dir == 1)
			pFsJpeg->scroll_step = 0;
		else
			pFsJpeg->scroll_step = (fsArea[FS_AREA_MOVEBAR].ySize - pFsJpeg->scroll_len) / (pFsJpeg->file_specify_in_dir - 1);
		pFsJpeg->scroll_len = fsArea[FS_AREA_MOVEBAR].ySize - pFsJpeg->scroll_step * (pFsJpeg->file_specify_in_dir - 1);
	}
	else
	{
		pFsJpeg->scroll_step = 10 * (fsArea[FS_AREA_MOVEBAR].ySize - pFsJpeg->scroll_len) / (pFsJpeg->file_specify_in_dir - 1);
		pFsJpeg->scroll_len = fsArea[FS_AREA_MOVEBAR].ySize - pFsJpeg->scroll_step * (pFsJpeg->file_specify_in_dir - 1) / 10;
	}

//	#ifdef DIR_SCROLL_BAR//zhongshan mark.

	// calcute the dir area scroll bar and scroll length.
	int iDirCount=0, total_dir=0;
	for (iDirCount = 0; iDirCount < pFsJpeg->fsnav_dir_cnt; iDirCount++)
	{
		if (iso9660_dir[iDirCount].type & (0x01 << pFsJpeg->gifsFuncBtn))
            total_dir++;
	}
    pFsJpeg->dir_count_in_specity_Category = total_dir;
	pFsJpeg->Dir_Page_Count = (pFsJpeg->dir_count_in_specity_Category + PER_PAGE - 1) / PER_PAGE;

	#ifdef DIR_SCROLL_BAR//zhongshan move here.20060414

	if (pFsJpeg->Dir_Page_Count != 1)
		pFsJpeg->dir1_scroll_len = fsArea[FS_DIR_AREA_MOVEBAR].ySize / pFsJpeg->Dir_Page_Count;
	else if (pFsJpeg->dir_count_in_specity_Category != 1)
		pFsJpeg->dir1_scroll_len = fsArea[FS_DIR_AREA_MOVEBAR].ySize / 2;
	else
		pFsJpeg->dir1_scroll_len = fsArea[FS_DIR_AREA_MOVEBAR].ySize;

	if (pFsJpeg->dir1_scroll_len < 4)
		pFsJpeg->dir1_scroll_len = 4;

	if ((fsArea[FS_DIR_AREA_MOVEBAR].ySize - pFsJpeg->dir1_scroll_len) >= (pFsJpeg->dir_count_in_specity_Category - 1))
	{
		// added by Jack Ciao 2006/10/3 12:53 for divide zero exception
		if (pFsJpeg->dir_count_in_specity_Category == 1)
			pFsJpeg->dir1_scroll_step = 0;
		else
			pFsJpeg->dir1_scroll_step = (fsArea[FS_DIR_AREA_MOVEBAR].ySize - pFsJpeg->dir1_scroll_len) / (pFsJpeg->dir_count_in_specity_Category - 1);
		pFsJpeg->dir1_scroll_len = fsArea[FS_DIR_AREA_MOVEBAR].ySize - pFsJpeg->dir1_scroll_step * (pFsJpeg->dir_count_in_specity_Category - 1);
	}
	else
	{
		pFsJpeg->dir1_scroll_step = 10 * (fsArea[FS_DIR_AREA_MOVEBAR].ySize - pFsJpeg->dir1_scroll_len) / (pFsJpeg->dir_count_in_specity_Category - 1);
		pFsJpeg->dir1_scroll_len = fsArea[FS_DIR_AREA_MOVEBAR].ySize - pFsJpeg->dir1_scroll_step * (pFsJpeg->dir_count_in_specity_Category - 1) / 10;
	}
	#endif	// DIR_SCROLL_BAR
#endif	// FS_BMP_GUI
}


void FSGUI_Refresh(void)
{
#if 0
	printf("=============Info of mp3 navigation============\n");
	printf("file_current=%3d, file_page_now  =%3d, fsnav_trk_now =%3d\n", pFsJpeg->file_current, pFsJpeg->file_page_now, pFsJpeg->fsnav_trk_now);
	printf("file_will   =%3d, file_page_will =%3d, fsnav_trk_will=%3d\n",pFsJpeg->file_will, pFsJpeg->file_page_will, pFsJpeg->fsnav_trk_will);
	printf("File_Count  =%3d, File_Page_Count=%3d, file_specify_in_dir=%3d\n", pFsJpeg->File_Count, pFsJpeg->File_Page_Count, file_specify_in_dir);
	printf("dir_current =%3d, fsnav_dir_now  =%3d\n", pFsJpeg->dir_current, pFsJpeg->fsnav_dir_now);
	printf("dir_page_now=%3d, fsnav_dir_will =%3d\n", pFsJpeg->dir_page_now, pFsJpeg->fsnav_dir_will);
	printf("refresh_dir_icon=%d,refresh_file_page=%d,refresh_dir_page=%d\n",refresh_dir_icon,
		refresh_file_page,refresh_dir_page);
#endif

#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
    FSGUI_RotateDiscIcon(0);//solve the problem when enter"return",the disc icon disappeared.zhaoyanhua 3-7-10 15:36
#endif

#ifdef FS_BMP_GUI//for display playing or HL Dir
	DirList();
	FSShowDirIcon();
#else
    DrawButton();
	FSShowDirIcon();
	//refresh_dir_page=1;
	DirList();
#endif

	FSGUI_CalcuteDirFileScrollLen();
#ifndef MP3_LARGE_GUI // 2006-03-23, mimitsai add
	//2006-03-16,mimitsai add for Dir scroll bar
	#ifdef DIR_SCROLL_BAR	
	MoveScroll(pFsJpeg->dir_page_now * PER_PAGE + pFsJpeg->dir_current, FS_DIR_AREA_MOVEBAR);
	#endif
#endif	

	ShowFileIcon();
	//refresh_file_page=1;
	FileList();
   
	SelectHL();
#ifdef FSGUI_NO_BLINK_SCROLL
	if(up_down_done && (pFsJpeg->ControlArea == CNT_AREA_FILE))
	    up_down_done=0;
	else
	    MoveScroll(pFsJpeg->file_page_will * PER_PAGE + pFsJpeg->file_will,SCROLLBAR_REFRESH);
#elif defined (FS_BMP_GUI)
	MoveScroll(pFsJpeg->file_page_now);//show file scroll bar
	DIR_MoveScroll(pFsJpeg->dir_page_now);
#else

	#if (defined(NEW_MP3_GUI)|| defined(INDIGO_STYLE_FSGUI)) && !defined(MP3_LARGE_GUI) //2006-03-23, mimitsai add
	// 2006-03-16, mimitsai modify 
	MoveScroll(pFsJpeg->file_page_will * PER_PAGE + pFsJpeg->file_will, FS_AREA_MOVEBAR);
	#else
		MoveScroll(pFsJpeg->file_page_will * PER_PAGE + pFsJpeg->file_will);
	#endif
#endif

	FSGUI_CookFileItem(pFsJpeg->file_current);
}

//
// FSGUI_Select :
//       return : 0 -> invalid-key or change folder
//                1 -> valid select

int FSGUI_Select(int iSelect)       // select file range of all disc,panxing,2002-4-8
{
    int iRes = 1;
#ifdef RECORD_PER_SECOND        //avoid bug when playing mp3  gerry  2-12-3 19:46
    resumeMSF = 0;
#endif
    if (pFsJpeg->ControlArea == CNT_AREA_DIR)
    {
        if (iSelect > 0 && iSelect <= pFsJpeg->count_dir[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3])
        {
            pFsJpeg->fsnav_dir_will = AnchorDir(iSelect - 1);
            FSGUI_PreChangeDir(&(pFsJpeg->fsnav_dir_will), 0);
            pFsJpeg->fsnav_dir_now = pFsJpeg->fsnav_dir_will;
#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined (INDIGO_STYLE_FSGUI)
            pFsJpeg->gifsbPreview = 0;//zhaoyanhua add 2004-2-24 17:25
#else
			pFsJpeg->gifsbPreview = 1;
#endif
            iRes = 1;
            refresh_dir_icon = 1;
            Restore2PlayingDir();

            #ifdef HANYANG_LR_CHANGE_PAGE
            //When enter in DIR area, right to file area
            FSGUI_Dir2FileArea();
            #endif
            //kevinmonkey sz 050609
            //for select directory (track now) of display (track now)/(total track) does not refresh
            if(!(full_scrn&GOTO))
                disp_trk_now = pFsJpeg->fsnav_trk_now + 1;
        }
        else
        {
            invalid_key();
            iRes = 0;
        }
    }
    else    //It is File Area Now
    {
#if defined(MP3_DIRECT_SELECT)||defined(SUPPORT_CHANGE_FILE_DIR_PAGE)
        if ((iSelect > 0) && (iSelect <= pFsJpeg->count_file[pFsJpeg->gifsFuncBtn - FS_FUNC_MP3]))
        {
            int i, tmp;
            int iCount = 0;
            int oldfsnav_dir_will; //Jeff 20020603

            oldfsnav_dir_will = pFsJpeg->fsnav_dir_will;

            for(i = 0; i < pFsJpeg->fsnav_dir_cnt; i++)
            {
                tmp = CountSpecifyFile(i);
                if((iCount + tmp) >= iSelect)
                    break;
                iCount += tmp;
            }
            pFsJpeg->fsnav_dir_will = i;
            FSGUI_PreChangeDir(&(pFsJpeg->fsnav_dir_will), 0);
            pFsJpeg->fsnav_dir_now = pFsJpeg->fsnav_dir_will;
            iSelect = iSelect - iCount;
            pFsJpeg->ControlArea = CNT_AREA_FILE; // Robert 20020521

            //Jeff 20020627
            if (pFsJpeg->gifsbZoomOK == 0)
			{
                if (oldfsnav_dir_will != pFsJpeg->fsnav_dir_will)
				{
                    refresh_dir_page=1;

#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
                    //Maoyong changed 2004.03.12, When select a file in other dir, avoid
                    //(1)not draw dir in JPEG full screen mode, not destroy decoded graph in Frame Buf 0
                    //(2)In preview, can't refresh dir because there is preivewed picture
                    //(3)When Other type movie if playing
                    if(pFsJpeg->iGraphMode == 0)
                    {
                        // 2004/04/28 yltseng, add one more condition that should not refresh DirIcon & DirList
                        //if( !( pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG || IsOtherStatePlayMode() ) )
						if( ( pFsJpeg->gifsFuncBtn != FS_FUNC_JPEG )
#ifdef SUPPORT_FILE_SYSTEM_MODE	// 2004/06/10 yltseng
							&& ( !IsOtherStatePlayMode() )
#endif
#ifdef SUPPORT_MP4			//linrc 2005-11-16 14:07
    					&&( GetCurrentFileType() != CDROM_MP4 )
#endif
							)
                        {
                            FSShowDirIcon();
                            DirList();
                        }
                    }
#else
					FSShowDirIcon();
					DirList();
#endif
                }
			}
        }
#endif
        if ((iSelect > 0) && (iSelect <= pFsJpeg->file_specify_in_dir))
        {
            FSGUI_FileSelect(iSelect);
            pFsJpeg->ControlArea = CNT_AREA_FILE;  // Robert 20020521
#if defined(NEW_MP3_GUI ) || defined(FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
            //Maoyong 2004.06.10 for GUI Bug in Preview.
            if( (pFsJpeg->gifsbPreview == 1)&&(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG) && !pFsJpeg->gbfsSlide )
            {
                #ifdef FS_BMP_GUI//zhaoyanhua dd 2004-6-11 11:21
                ClearJpegPreviewBg();
			#elif defined(INDIGO_STYLE_FSGUI)
				//2006-06-02, mimitsai add for HD ui.
				DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y,DIR_AREA_BKGROUND_CRCB);
                #else
                DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, 0x36, 0xc1, DIR_AREA_BKGROUND_CRCB);
                #endif
                pFsJpeg->gifsbPreview = 0;
            }
#endif

            //wanghaoying add 2003-11-10 17:16
            //Des: VFD show the number selected
            //if(!(full_scrn&GOTO)) // qisheng liych for select jpeg show num error
            //    disp_trk_now = iSelect;

            iRes = 1;
            return 1;
        }
        else
            invalid_key();
        iRes = 0;
    }
    return iRes;
}

void FSGUI_Stop()
{
    FSGUI_PreChangeDir(&(pFsJpeg->fsnav_dir_now), 0);
#ifdef NEW_MP3_GUI
    if (JPEG_Preview_drawed == JPEG_PREVIEW_IN_DIR_AREA )
        ClearJpegPreviewBg();//zhaoyanhua changed 2004-6-11 11:29
#endif
    refresh_dir_page = 1;   // insure dir page area can be refresh, panxing, 2002-1-22
    refresh_file_page = 1;

    FSGUI_Refresh();
#if !(defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI))
	//ClearArea(FS_AREA_PREVIEWJPG);
	//2006-06-02, mimitsai add for HD ui.
  	ClearRectArea(0, 0, 0, 0x36, 0xc1, FS_AREA_PREVIEWJPG, 0);//zhaoyanhua add
#endif

    if ((pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
        || (pFsJpeg->gifsFuncBtn == FS_FUNC_GAME)
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE
        || (pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)
#endif
        )
    {
        pFsJpeg->file_current = 0;
        pFsJpeg->file_will = 0;
        pFsJpeg->dir_current = 0;
        pFsJpeg->fsnav_dir_will = 0;
        pFsJpeg->fsnav_dir_now = 0;
        FSGUI_PreChangeDir(&(pFsJpeg->fsnav_dir_now), 0);

#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
        if (!(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)) //when show JPEG,STOP should not change pFsJpeg->gifsbPreview.zhaoyanhua 3-7-9 9:08
#endif
            pFsJpeg->gifsbPreview = 1;
    }

    FSGUI_JpgUpdateOSD();
}

#ifdef INDIGO_STYLE_FSGUI
/*
 * FUNC : Draw a repeat icon or image.
 * NOTE:  The icon or image must Xx1 or 1xX restriction.
 * INPUT:
 *	 	Rect:			startX, startY.
 *   	repWid:			Repeat width or height.
 *		dir:   			Repeat direction, 0: repeat x coord., 1: repeat y coord.
 *   	direction:		The varient color direction.
 *	 	bg:				Color index of icon/image.
 *		BG_Y:			Luma value of color index of bg.
 *		BG_CbCr:		Chroma value of color index of bg.
 * Creator: mimitsai
 * Date: 2006-03-10
 */
void FSGUI_DrawImgRepeat(BTNAREA Rect, int repWid, UINT8 dir, const UINT8 *bg, const UINT8* bg_Y, const UINT16* bg_CbCr)
{
	int x=0,y=0, yCnt;
	switch(dir)
	{
		case 0:	// repeat x coord.
			// draw first column bg
			FSGUI_DrawIcon(Rect.xStart, Rect.yStart, bg, bg_Y, bg_CbCr, 0);

			// repeat first column
			for(y=Rect.yStart; y< Rect.yStart+bg[1]; y++)  // bg[0]:x_wid, bg[1]:y_hei
			{
				UINT8 *YPtr = Y_XY(Rect.xStart+1,y);
				UINT8  YVal = *Y_XY(Rect.xStart,y);
				for(x=Rect.xStart+1; x<Rect.xStart+repWid; x++)
				{
					*YPtr = YVal;
					YPtr++;
				}
				UINT16* CPtr = C_XY(Rect.xStart+1,y);
				UINT16  CVal = *C_XY(Rect.xStart,y);
				yCnt = C_XY(Rect.xStart+repWid,y) - C_XY(Rect.xStart,y);
				for(x=Rect.xStart+1; x<yCnt; x++)
				{
					*CPtr = CVal;
					CPtr++;
				}
			}
			break;

		case 1:	// repeat y coord.
			// draw first row bg
			FSGUI_DrawIcon(Rect.xStart, Rect.yStart, bg, bg_Y, bg_CbCr, 0);

			//copy each line from the line above(repeat first row)
			for(y = Rect.yStart + 1; y < (Rect.yStart+ repWid); y++)
				memcpy(Y_XY((Rect.xStart),y),Y_XY((Rect.xStart),(y-1)), bg[0]);

			for(y = Rect.yStart + 1; y < (Rect.yStart+repWid); y++)
				memcpy(C_XY((Rect.xStart),y),C_XY((Rect.xStart),(y-1)), bg[0]);
			break;

		default:
			break;
	}
}
#endif
//
// Draw mp3 main menu, fill framebuf by some difference color
//
void FSGUI_Menu()
{
#ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
#endif

    refresh_dir_page=1;
    refresh_file_page=1;
    
//suqiaoli add 2004-10-10 ,solve FS_BMP_GUI LOGO mosaic bug ,
//move set_disbuf_now(0) from fs9660.c ReadFile Function.
#if defined (MP3_LARGE_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_LARGE_FSGUI)//2006-06-02, mimitsai add for HD ui.
	extern void set_disbuf_now(int);
    set_disbuf_now(0);
#endif

#ifdef INDIGO_STYLE_FSGUI
	BTNAREA Rect1;
	Rect1.xStart=0;
	Rect1.yStart=0;
	//2006-06-02, mimitsai add for HD ui.
	FSGUI_DrawImgRepeat(Rect1, FSGUI_SCREEN_WIDTH, 0, bg_up, BG_UP_Y, BG_UP_CbCr);
	Rect1.yStart = FSGUI_SCREEN_HEIGHT/2;
	FSGUI_DrawImgRepeat(Rect1, FSGUI_SCREEN_WIDTH, 0, bg_down, BG_UP_Y, BG_UP_CbCr);
	DrawRectCorner(Rect[DIR_RECT],  CORNER_RAD, 1, DIR_STEP,  FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB);
	DrawRectCorner(Rect[FILE_RECT], CORNER_RAD, 1, FILE_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB);

#elif defined (NEW_MP3_GUI)
    // background
    FSGUI_FillFrameBuf(0,0, FSGUI_SCREEN_WIDTH, FSGUI_SCREEN_HEIGHT, BK_GROUNDY,BK_CRCB);//2006-06-02, mimitsai add for HD ui.

	#ifdef MONO_FSGUI //FS GUI, axel 2003-12-29 23:26
	//2006-06-02, mimitsai add for HD ui.
    DrawRectCorner(Rect[DIR_RECT],  CORNER_RAD, 1, 1, 0x36, 0xc1, DIR_AREA_BKGROUND_CRCB);
    DrawRectCorner(Rect[FILE_RECT], CORNER_RAD, 1, 1, 0x36, 0xc1, FILE_AREA_BKGROUND_CRCB);
	#else
    DrawRectCorner(Rect[DIR_RECT],  CORNER_RAD, 1, DIR_STEP,  0x36, 0xc1, DIR_AREA_BKGROUND_CRCB);
    DrawRectCorner(Rect[FILE_RECT], CORNER_RAD, 1, FILE_STEP, 0x36, 0xc1, FILE_AREA_BKGROUND_CRCB);
#endif

    DrawButton();//to avoid GUI blinking zhaoyanhua add 2004-2-3 16:09
#elif defined FS_BMP_GUI

    // show background
#ifdef GPS_MP3_UI//frank.huang 050928
    FSGUI_DrawBackGround(BG_XSTART, BG_YSTART + 0, BG_XREPEAT, BG_YREPEAT,LAY_BG_3_1);
    FSGUI_DrawBackGround(BG_XSTART, BG_YSTART + 0xaa, BG_XREPEAT, BG_YREPEAT,LAY_BG_3_2);
	FSGUI_DrawBackGround(BG_XSTART, BG_YSTART + 0x174, BG_XREPEAT, BG_YREPEAT, LAY_BG_3_3);
	// dir background and file background
    FSGUI_ShowBmpCornerRect(DIR_AREA_XSTART, DIR_AREA_YSTART, DIR_AREA_XLEN, DIR_AREA_YLEN);
    FSGUI_ShowBmpCornerRect(FILE_AREA_XSTART, FILE_AREA_YSTART, FILE_AREA_XLEN, FILE_AREA_YLEN);
#else
    FSGUI_DrawBackGround(BG_XSTART, BG_YSTART + 0, BG_XREPEAT, BG_YREPEAT,LAY_BG_3_1);
    FSGUI_DrawBackGround(BG_XSTART, BG_YSTART + 0xaa, BG_XREPEAT, BG_YREPEAT,LAY_BG_3_2);
    FSGUI_DrawBackGround(BG_XSTART, BG_YSTART + 0x17d, BG_XREPEAT, BG_YREPEAT, LAY_BG_3_3);

    // dir background and file background
    FSGUI_ShowBmpCornerRect(DIR_AREA_XSTART, DIR_AREA_YSTART, DIR_AREA_XLEN, DIR_AREA_YLEN);
    FSGUI_ShowBmpCornerRect(FILE_AREA_XSTART, FILE_AREA_YSTART, FILE_AREA_XLEN, FILE_AREA_YLEN);

	DrawButton();//show top buttons,add by feeling 2004-06-14

	//draw the left and right edge of the info area
	FSGUI_LayoutBmp(LAY_PLAYING_BAR_3_1);
	FSGUI_LayoutBmp(LAY_PLAYING_BAR_3_3);

    	//draw the info area background
	FSGUI_DrawBackGround(fsArea[FS_AREA_PATHBACKGROUND].xStart ,
		fsArea[FS_AREA_PATHBACKGROUND].yStart,
		fsArea[FS_AREA_PATHBACKGROUND].xSize,
		fsArea[FS_AREA_PATHBACKGROUND].ySize,
		LAY_PLAYING_BAR_3_2);
#endif//#ifdef GPS_MP3_UI

#else	//NEW_MP3_GUI
	// background
	FSGUI_FillFrameBuf(0,0,352,288,BK_GROUNDY,BK_GROUNDCRCB);

	// high line
	FSGUI_FillFrameBuf(0,Y1,352,LIGHT_WID,WHITE_Y,WHITE_CRCB);

	FSGUI_FillFrameBuf(0, Y1+LIGHT_WID,
		X1, SHADOW_WID,
		BLACK_Y, BLACK_CRCB);

	FSGUI_FillFrameBuf(X1+LIGHT_WID+SHADOW_WID, Y1+LIGHT_WID,
		352-X1-LIGHT_WID-SHADOW_WID, SHADOW_WID,
		BLACK_Y, BLACK_CRCB);

	FSGUI_FillFrameBuf(0, Y3,
		X1, LIGHT_WID,
		WHITE_Y,WHITE_CRCB);

	FSGUI_FillFrameBuf(X1+LIGHT_WID+SHADOW_WID, Y3,
		352-X1-LIGHT_WID-SHADOW_WID, LIGHT_WID,
		WHITE_Y,WHITE_CRCB);

	FSGUI_FillFrameBuf(0, Y3+LIGHT_WID,
		352, SHADOW_WID,
		BLACK_Y,BLACK_CRCB);

	FSGUI_FillFrameBuf(X1, Y1+LIGHT_WID,
		LIGHT_WID, Y3-Y1,
		WHITE_Y,WHITE_CRCB);

	FSGUI_FillFrameBuf(X1+LIGHT_WID, Y1+LIGHT_WID,
		SHADOW_WID, Y3-Y1-LIGHT_WID,
		BLACK_Y,BLACK_CRCB);

        // 2006-03-16, mimitsai modify 
	DrawScroll(FS_AREA_MOVEBAR);
#ifdef DIR_SCROLL_BAR
	DrawScroll(FS_DIR_AREA_MOVEBAR);
#endif

#endif	//NEW_MP3_GUI

#ifndef AUDIO_SHOW_SAVER
	#ifdef USE_FSGUI_TO_PLAY_CD//frank.huang add 051014
	if(cd_type_loaded!=CDDA)
	#endif
    play_state = VCD_STATE_MP3_FILELIST;
#endif

#ifdef DISP_REGION_BOTTOM
	{
		if(t_disp)
		{
			osd_init();
			DispCookOSD0(1);//feeling, update the disp buf,2004/12/30

		}
	}	
#endif
}


UINT32  FSGUI_IsSelectable()
{
    //Jeff 20020521
    if (((pFsJpeg->ControlArea == CNT_AREA_MP3BUTTON) && (pFsJpeg->gifsFuncBtn != FS_FUNC_MP3)) ||
        (pFsJpeg->ControlArea==CNT_AREA_JPEGBUTTON) ||
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
        (pFsJpeg->ControlArea==CNT_AREA_GAMEBUTTON) ||
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 021001
        (pFsJpeg->ControlArea==CNT_AREA_OTHERBUTTON) ||
#endif
#ifdef SUPPORT_MIDI
        (pFsJpeg->ControlArea==CNT_AREA_MIDIBUTTON) ||
#endif
        (pFsJpeg->ControlArea == CNT_AREA_DIR)
        )
    {
        return 1;
    } else
        return 0;
}
#ifdef MP3_JPEG_COWORK
BYTE need_refresh_dirarea;//hongfeng 2006/2/18 show GUI correctly after press UP/DOWN/LEFT/RIGHT quickly when jpeg preview
#endif

#ifdef JPG_OLD_PARSER_FLOW
void FSGUI_JpgPreview()
{
    UINT32 msf, len;
    int iResJPG;
#ifdef MP3_JPEG_COWORK	
    int last_file_pressed; //ycwen 2005/1/21 for JPEG Preview GUI
#endif
#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
    //refresh file list, not refresh dir list
    FSGUI_RotateDiscIcon(0);//solve the problem when enter"return",the disc icon disappeared.zhaoyanhua 3-7-10 15:36

    FSGUI_CookFileItem(pFsJpeg->file_current);
    //ShowHL();
    ShowCurrentFilePlaying();
    ShowHL();//zhaoyanhua move it here. 2004-2-2 17:24
#if defined (FS_BMP_GUI)
    if (flagRefresh == 1)//when return from refresh,show file scroll
    {
        MoveScroll(pFsJpeg->file_page_will);
        flagRefresh = 0;
    }
    else if (pFsJpeg->file_current % PER_PAGE == 0)
        MoveScroll(pFsJpeg->file_page_will);
#else

	#if (defined(NEW_MP3_GUI)||defined(INDIGO_STYLE_FSGUI)) && !defined(MP3_LARGE_GUI) //2006-03-23, mimitsai add
    // 2006-03-16, mimitsai modify 
	MoveScroll(pFsJpeg->file_page_will * PER_PAGE + pFsJpeg->file_will, FS_AREA_MOVEBAR);
	#else
		MoveScroll(pFsJpeg->file_page_will * PER_PAGE + pFsJpeg->file_will);
	#endif
#endif

#else
	//2006-06-02, mimitsai add for HD ui.
  	ClearRectArea(0, 0, 0, 0x36, 0xc1, FS_AREA_PREVIEWJPG, 0);//zhaoyanhua add

	// list directories and files, scroll bar,etc, panxing, 2002-1-22
	FSGUI_Refresh();
#endif

    disp_trk_now = FSGUI_GetDispTrack(); //Jeff 20020607
    FSGUI_JpgUpdateOSD();// same as dvdcode0115, panxing, 2002-1-19

    msf = iso9660_file[pFsJpeg->file_array[pFsJpeg->file_current]].loc;
    len = iso9660_file[pFsJpeg->file_array[pFsJpeg->file_current]].size;

    ClearCommand();

#if defined (NEW_MP3_GUI)|| defined(INDIGO_STYLE_FSGUI)
    if (JPEG_Preview_drawed == DIR_LIST_IN_DIR_AREA )
    {

		#ifdef INDIGO_STYLE_FSGUI
			//2006-06-02, mimitsai add for HD ui.
			DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB);
		#else
        	DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, 0, 0x36, 0xc1,PREVIEW_BKGROUND_CRCB);
		#endif
        JPEG_Preview_drawed = JPEG_PREVIEW_IN_DIR_AREA ;
    }
    else   //not redraw all the background to avoid blinkling when preview picture. zhaoyanhua note
   	{
		#ifdef INDIGO_STYLE_FSGUI
		//2006-06-02, mimitsai add for HD ui.
		DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB);
		#else
        FSGUI_FillFrameBuf(Rect[ PREVIEW_RECT].xStart, Rect[ PREVIEW_RECT].yStart,
                           Rect[ PREVIEW_RECT].xSize,  Rect[ PREVIEW_RECT].ySize,
                           PREVIEW_BKGROUND_Y, PREVIEW_BKGROUND_CRCB);
		#endif

   	}

#elif defined FS_BMP_GUI

    ClearJpegPreviewBg();
    if (JPEG_Preview_drawed == DIR_LIST_IN_DIR_AREA )
    {
        JPEG_Preview_drawed = JPEG_PREVIEW_IN_DIR_AREA ;
        //when preview jpg pic,dir scroll bar cannot exit.
        DIR_DrawScroll();
    }

#endif

#ifdef  MP3_JPEG_COWORK
    need_refresh_dirarea = 1;//hongfeng 2006/2/18 show GUI correctly after press UP/DOWN/LEFT/RIGHT quickly when jpeg preview

    last_file_pressed = pFsJpeg->file_current; //ycwen 2005/1/21 Show highlight correctly when press UP/DOWN quickly when preview jpg
    while(check_input_interval()==0)
    {
        if((pFsJpeg->gifsFuncBtn==FS_FUNC_MP3)&&(back_sign==1))
        {
            //FSGUI_Refresh();//refresh the mp3 GUI
            return;//prevent conflict between JPEG and mp3
        }
        polling();
        if(last_file_pressed!=pFsJpeg->file_current)
        {
            SelectHL();
            last_file_pressed = pFsJpeg->file_current; 
        }
        //for the msf and len of current jpeg pic
        msf = iso9660_file[pFsJpeg->file_array[pFsJpeg->file_current]].loc;
        len = iso9660_file[pFsJpeg->file_array[pFsJpeg->file_current]].size;
    }
    need_refresh_dirarea = 0;//hongfeng 2006/2/18 show GUI correctly after press UP/DOWN/LEFT/RIGHT quickly when jpeg preview

    //pFsJpeg->gifsbPreview = 0;//prevent next enter!//wuxiaofeng marked 2004-04-19
    //ycwen 2005/1/31 If user switch to NONE-JPEG Area, then we should STOP the Jpeg function.
    //                (For example, if user switch to MPEG file, and Jpeg still call decode function, then system will reset)
    if (! ((pFsJpeg->ControlArea==CNT_AREA_JPEGBUTTON)||(pFsJpeg->ControlArea==CNT_AREA_FILE)) )
        return;

    #if defined (NEW_MP3_GUI)|| defined(INDIGO_STYLE_FSGUI)//hongfeng 2006/2/18 show GUI correctly after press UP/DOWN/LEFT/RIGHT quickly when jpeg preview
    if (JPEG_Preview_drawed == DIR_LIST_IN_DIR_AREA )
    {

		#ifdef INDIGO_STYLE_FSGUI
		//2006-06-02, mimitsai add for HD ui.
        DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB);
		#else
        DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, 0, 0x36, 0xc1, PREVIEW_BKGROUND_CRCB);
		#endif
        JPEG_Preview_drawed = JPEG_PREVIEW_IN_DIR_AREA ;
    }
    else   //not redraw all the background to avoid blinkling when preview picture. zhaoyanhua note
   	{
		#ifdef INDIGO_STYLE_FSGUI
		//2006-06-02, mimitsai add for HD ui.
        DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB);
		#else
        FSGUI_FillFrameBuf(Rect[ PREVIEW_RECT].xStart, Rect[ PREVIEW_RECT].yStart,
                           Rect[ PREVIEW_RECT].xSize,  Rect[ PREVIEW_RECT].ySize,
                           PREVIEW_BKGROUND_Y, PREVIEW_BKGROUND_CRCB);
		#endif
   	}
    #endif//defined (NEW_MP3_GUI)|| defined(NEW_STYLE_UI)
    
#endif//#ifdef  MP3_JPEG_COWORK


#if defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)
    // joshua, 2004/10/18, added for clearing special-effect mode
    #ifdef JPG_EFFECT
        Jpg_effect_mode = 0; 
    #endif

    iResJPG = Jpg_Main(msf, len,
        Rect[SHOW_JPEG_RECT].xStart,
        Rect[SHOW_JPEG_RECT].yStart,
        Rect[SHOW_JPEG_RECT].xSize,
        Rect[SHOW_JPEG_RECT].ySize);
#elif defined FS_BMP_GUI//zhaoyanhua 2004-6-11 9:04
    iResJPG = Jpg_Main(msf, len,
		fsArea[FS_AREA_PREVIEWJPG].xStart, //x must be 8*x
		fsArea[FS_AREA_PREVIEWJPG].yStart-(8-PER_PAGE)*16, //y must be 2*x//frank.huang 050915
		fsArea[FS_AREA_PREVIEWJPG].xSize,
		fsArea[FS_AREA_PREVIEWJPG].ySize);
#else
	iResJPG = Jpg_Main(msf, len,
		fsArea[FS_AREA_PREVIEWJPG].xStart+2, //x must be 8*x
		fsArea[FS_AREA_PREVIEWJPG].yStart+2, //y must be 2*x
		fsArea[FS_AREA_PREVIEWJPG].xSize-4,
		fsArea[FS_AREA_PREVIEWJPG].ySize-4);
#endif

#ifdef NOT_SHOW_X_WHEN_JPEG_ERROR //Juse as the name!Jack added 04/11/16 
  #ifndef NOT_SHOW_X_AND_MSG_WHEN_JPEG_ERR //zxb for philips
    #ifdef  MP3_JPEG_COWORK
    if(pFsJpeg->gifsFuncBtn!=FS_FUNC_MP3)
    #endif
    {
        if (iResJPG < 0)
        {
            #ifndef ALCO_DVD_UI
            psprintf(RegionValStr[REGION1],"JPEG ERROR");
            PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
            #endif
        }
    }    
   #endif
#else
#ifdef  MP3_JPEG_COWORK//prevent drawing the X when switching to mp3
    if(pFsJpeg->gifsFuncBtn!=FS_FUNC_MP3)
#endif
    {
#if defined (NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)
        //Maoyong 2004.04.19 for JPEG preview display and flow bug.
        if (iResJPG < 0)
        {
            if(pFsJpeg->ControlArea != CNT_AREA_DIR)    //Maoyong 2004.03.11
            {
                BYTE x __attribute__((unused)) = 90, y __attribute__((unused))  = 140;

                //wanghaoying 2004-8-4 20:48, only for different defination
                #ifdef MP3_LARGE_GUI
                x = 140; y = 240;
                #endif

		        // deal with error, panxing, 2002-1-22
		        #if (defined(BBK_DVD)||defined(YADAI_DVD))//2004-3-30 16:30 LIJD
		        FSGUI_ShowString(90,140,"", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		        #else
		        FSGUI_ShowString(90,140,"X", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		        #endif
        	}
    	}
#else
		if (iResJPG < 0) {
			// deal with error, panxing, 2002-1-22
			FSGUI_ShowString(fsArea[FS_AREA_PREVIEWJPG].xStart+(fsArea[FS_AREA_PREVIEWJPG].xSize-10)/2,
				fsArea[FS_AREA_PREVIEWJPG].yStart+(fsArea[FS_AREA_PREVIEWJPG].ySize-12)/2,
				"X", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		}
#endif
    }
#endif //end #ifdef NOT_SHOW_X_WHEN_JPEG_ERROR    
}
#endif  //#ifdef JPG_OLD_PARSER_FLOW

#ifdef ONLY_SELECT_PLAY_DISPLAY_SEQ_PLAY//hongfeng add for OP 2006-1-5
extern BYTE display_seq_play;
#endif

UINT32 FSGUI_CmdPlay()
{
	UINT32  iRes;

	iRes = CMD_FUNC | CMD_FUNC_PLAY;

	//Jeff 20020418
	if ((pFsJpeg->ControlArea==CNT_AREA_MP3BUTTON) || (pFsJpeg->ControlArea==CNT_AREA_JPEGBUTTON)
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
		|| (pFsJpeg->ControlArea==CNT_AREA_GAMEBUTTON)
#endif
		)
	{
		iRes = FSGUI_CmdEnter();
		return iRes;
	}//NONO 2-4-2 18:09
	//#endif
	if (pFsJpeg->ControlArea == CNT_AREA_DIR) {
		iRes = FSGUI_CmdEnter();
		return iRes;

	}

	if ((pFsJpeg->ControlArea == CNT_AREA_FILE) && ((pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
		|| (pFsJpeg->gifsFuncBtn == FS_FUNC_GAME)
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE
		|| (pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER) // Robert 021007
#endif
#ifdef SUPPORT_MIDI
		|| (pFsJpeg->gifsFuncBtn==FS_FUNC_MIDI)
#endif
		))
	{
		iRes = FSGUI_CmdEnter();
		#if defined(MP3_STOP_IN_GUI_AND_NEED_RESUME_TRACK)||defined(MP3_STOP_IN_GUI_AND_NEED_RESUME_MSF)
		iRes = CMD_FUNC | CMD_FUNC_PLAY;
		#endif
		return iRes;
	}

	if (((pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
#ifdef SUPPORT_MIDI
		    || (pFsJpeg->gifsFuncBtn==FS_FUNC_MIDI)
#endif
        )
        && (play_state != VCD_STATE_MP3_FILELIST))
	{
		sys_cmd = 0;
		iRes=0;
	}
	else if (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
	{
#ifdef MENU_STOP_EXCHANGE
#ifndef SDRAM_16Mb_Mode
       if(pFsJpeg->ControlArea != CNT_AREA_OTHERBUTTON)
           pFsJpeg->g_nJpegMode=JPEG_THUMBNAIL_MODE;       //xulf 2003-12-6
#endif
#endif

#ifdef SUPPORT_FILE_SYSTEM_MODE
	   if(pFsJpeg->ControlArea != CNT_AREA_OTHERBUTTON)
#endif//nono 20040109
	   {
		pFsJpeg->gbfsSlide = 1;

#ifdef NOT_SHOW_PIC_READ_RATE//terry,2004/1/8 06:33PM
extern const UINT8 pic_cd_str[17];//axel 2004/5/17 09:45
        if( (strncmp(RegionValStr[REGION1], pic_cd_str, 15) != 0)||(timeout_osd[REGION1]==0) )
#endif
        {
            #ifdef ONLY_SELECT_PLAY_DISPLAY_SEQ_PLAY//hongfeng add for OP 2006-1-5
            if(display_seq_play)
            #endif
			{
			#ifdef ALCO_PORTABLE
			PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);
			#else
			PrintOsdMsg(STR_OS_SEQUENCE,REGION1,1,0);

                #ifdef ONLY_SELECT_PLAY_DISPLAY_SEQ_PLAY//hongfeng add for OP 2006-1-5
                display_seq_play = 0;
                #endif

			#endif
			}
		}
		if (rep_mode==REPEAT_TRACK) {
			rep_mode = 0;
		}
	   }
#ifdef SUPPORT_FILE_SYSTEM_MODE//nono 20040109
	   else//if(pFsJpeg->ControlArea != CNT_AREA_OTHERBUTTON )
	   {
	    iRes = FSGUI_CmdEnter();
		return iRes;
	   }
#endif//#ifdef SUPPORT_FILE_SYSTEM_MODE
	}

	return iRes;
}

void Will2Playing(void)
{
#if defined(MP3_POWER_RESUME)||defined(FS_FILE_POWER_RESUME)// 0//def POWER_RESUME//mp3 power_resume need to be fix again later.
	
	#ifdef MP3_POWER_RESUME
	 if( Is_MP3_STATE()&&IsTheSameMP3 ( ) )
     pFsJpeg -> fsnav_trk_will = ReadSameMP3Para ( 1 ) ; //mp3
	#elif defined(FS_FILE_POWER_RESUME)  
		 if(IsTheSameDisc()) 
	     pFsJpeg -> fsnav_trk_will = resumeTRK; 
	#endif 	
		pFsJpeg -> file_will = pFsJpeg->fsnav_trk_will % PER_PAGE ;
		pFsJpeg -> file_page_will = pFsJpeg->fsnav_trk_will / PER_PAGE ;

#endif   
	
	pFsJpeg->file_current = pFsJpeg->file_will;
	pFsJpeg->file_page_now = pFsJpeg->file_page_will;
	pFsJpeg->fsnav_trk_now = pFsJpeg->fsnav_trk_will;
}

void Playing2Will(void)
{
	pFsJpeg->file_will = pFsJpeg->file_current;
	pFsJpeg->file_page_will = pFsJpeg->file_page_now;
	pFsJpeg->fsnav_trk_will = pFsJpeg->fsnav_trk_now;
}

void Restore2PlayingFile(void)
{
	if (pFsJpeg->file_page_now != pFsJpeg->file_page_will)
	{
		pFsJpeg->file_page_will = pFsJpeg->file_page_now;
		PrepareForChangeFilePage(pFsJpeg->file_page_now, pFsJpeg->fsnav_trk_now, 2);
		if ((pFsJpeg->gifsState != FS_STATE_JPEG) || (pFsJpeg->gifsState != FS_STATE_GAME))
		{
			ShowFileIcon();
			FileList();
		}
	}
	Playing2Will();
}

void Restore2PlayingDir(void)
{
    int playing;
    int will;


    playing = antiAnchorDir(pFsJpeg->fsnav_dir_now);
    will = antiAnchorDir(pFsJpeg->fsnav_dir_will);

    // for restore dir hl's location, panxing, 2002-4-12
	if ((will / PER_PAGE) != (playing / PER_PAGE))
    {
        // in different dir page,panxing,2002-4-12
		CalcDirNow(&(pFsJpeg->fsnav_dir_now));
        if ((pFsJpeg->gifsState != FS_STATE_JPEG) && (pFsJpeg->gifsState != FS_STATE_GAME))
        {
            FSShowDirIcon();
            DirList();
        }
    }
	pFsJpeg->dir_current = playing % PER_PAGE;
	pFsJpeg->fsnav_dir_will = pFsJpeg->fsnav_dir_now;
}

UINT32  FSGUI_CmdRight()
{
    UINT32 iRes=0;
#ifdef  MP3_JPEG_COWORK
        old_time=get_stc_32_inline();//get the press time
#endif
    if (pFsJpeg->gifsState == FS_STATE_JPEG)
    {
#ifdef JPG_EFFECT
		sys_cmd = (CMD_SELECT | CMD_FUNC_GAME_R);
#else
		sys_cmd = iRes;
#endif

        return sys_cmd;
    }

    if (pFsJpeg->ControlArea == CNT_AREA_FILE)
    {
#ifdef SUPPORT_PLAYLIST 	//wanghaoying 2005-9-28 19:31
        if(pFsJpeg->gifsPlayListCount)
            pFsJpeg->ControlArea = CNT_AREA_PLAYLISTBUTTON;
        else
#endif
#ifdef SUPPORT_MIDI
        if (pFsJpeg->gifsMidiCount)
            pFsJpeg->ControlArea = CNT_AREA_MIDIBUTTON;
        else
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 021001
	#ifndef	GPS_MP3_UI	//suxin add 050922 for GPS_MP3_UI change media page
        if (pFsJpeg->gifsOtherCount)
            pFsJpeg->ControlArea = CNT_AREA_OTHERBUTTON;
        else
	#endif
#endif
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
            if (pFsJpeg->gifsGAMECount)
                pFsJpeg->ControlArea = CNT_AREA_GAMEBUTTON;
            else
#endif

#ifndef	GPS_MP3_UI
                if (pFsJpeg->gifsJPEGCount)
                    pFsJpeg->ControlArea = CNT_AREA_JPEGBUTTON;
                else
                    pFsJpeg->ControlArea = CNT_AREA_MP3BUTTON;
#endif		//	#ifndef	GPS_MP3_UI
    }
    else if(pFsJpeg->ControlArea == CNT_AREA_DIR)
    {
        pFsJpeg->ControlArea = CNT_AREA_FILE;
        
        #ifdef JPG_OLD_PARSER_FLOW
        pFsJpeg->gifsbPreview = 1;  //Maoyong 2004.05.31
        #endif
#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
        JPEG_Preview_drawed = DIR_LIST_IN_DIR_AREA;
#endif
    }
    else if (pFsJpeg->ControlArea == CNT_AREA_MP3BUTTON)
    {
        if (pFsJpeg->gifsJPEGCount)
            pFsJpeg->ControlArea = CNT_AREA_JPEGBUTTON;
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
        else if (pFsJpeg->gifsGAMECount)
            pFsJpeg->ControlArea = CNT_AREA_GAMEBUTTON;
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 021001
        else if (pFsJpeg->gifsOtherCount)
            pFsJpeg->ControlArea = CNT_AREA_OTHERBUTTON;
#endif
#ifdef SUPPORT_MIDI
        else if (pFsJpeg->gifsMidiCount)
            pFsJpeg->ControlArea = CNT_AREA_MIDIBUTTON;
#endif
#ifdef SUPPORT_PLAYLIST		//wanghaoying 2005-9-28 19:31
        else if(pFsJpeg->gifsPlayListCount)
            pFsJpeg->ControlArea = CNT_AREA_PLAYLISTBUTTON;
#endif
        else
            pFsJpeg->ControlArea = CNT_AREA_FILE;
    }
    else if (pFsJpeg->ControlArea == CNT_AREA_JPEGBUTTON)
    {
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
        if (pFsJpeg->gifsGAMECount)
            pFsJpeg->ControlArea = CNT_AREA_GAMEBUTTON;
        else
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 021001
            if (pFsJpeg->gifsOtherCount)
                pFsJpeg->ControlArea = CNT_AREA_OTHERBUTTON;
            else
#endif
#ifdef SUPPORT_MIDI
        if(pFsJpeg->gifsMidiCount)
            pFsJpeg->ControlArea = CNT_AREA_MIDIBUTTON;
        else
#endif
#ifdef SUPPORT_PLAYLIST		//wanghaoying 2005-9-28 19:31
        if(pFsJpeg->gifsPlayListCount)
            pFsJpeg->ControlArea = CNT_AREA_PLAYLISTBUTTON;
        else
#endif
        {
            pFsJpeg->ControlArea = CNT_AREA_FILE;
#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
            JPEG_Preview_drawed = DIR_LIST_IN_DIR_AREA;
            #ifdef JPG_OLD_PARSER_FLOW
            pFsJpeg->gifsbPreview = 1;
			#endif
#endif
        }
    }
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
    else if (pFsJpeg->ControlArea == CNT_AREA_GAMEBUTTON)
    {
#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 021001
        if (pFsJpeg->gifsOtherCount)
            pFsJpeg->ControlArea = CNT_AREA_OTHERBUTTON;
        else
#endif
         {
            pFsJpeg->ControlArea = CNT_AREA_FILE;
#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
            if (pFsJpeg->g_nJpegMode == JPEG_NORMAL_MODE)
                pFsJpeg->gifsbPreview = 1;
#endif
         }
    }
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 021001
    else if (pFsJpeg->ControlArea == CNT_AREA_OTHERBUTTON)
    {
#ifdef SUPPORT_MIDI
        if (pFsJpeg->gifsMidiCount)
            pFsJpeg->ControlArea = CNT_AREA_MIDIBUTTON;
        else
#endif
#ifdef SUPPORT_PLAYLIST		//wanghaoying 2005-9-28 19:31
        if(pFsJpeg->gifsPlayListCount)
            pFsJpeg->ControlArea = CNT_AREA_PLAYLISTBUTTON;
        else
#endif
        pFsJpeg->ControlArea = CNT_AREA_FILE;
    }
#endif

#ifdef SUPPORT_MIDI
    else if (pFsJpeg->ControlArea == CNT_AREA_MIDIBUTTON)
    {
#ifdef SUPPORT_PLAYLIST		//wanghaoying 2005-9-28 19:31
        if(pFsJpeg->gifsPlayListCount)
            pFsJpeg->ControlArea = CNT_AREA_PLAYLISTBUTTON;
        else
#endif
        pFsJpeg->ControlArea = CNT_AREA_FILE;
    }
#endif
#ifdef SUPPORT_PLAYLIST		//wanghaoying 2005-9-28 19:31
    else if (pFsJpeg->ControlArea == CNT_AREA_PLAYLISTBUTTON)
    {
        pFsJpeg->ControlArea = CNT_AREA_FILE;
    }
#endif

#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
    //avoid GUI blinking.zhaoyanhua add 2004-2-3 11:16
    //SelectHL();
    ShowHL();
#else
	SelectHL();
#endif
    iRes = 0x20000 | sys_cmd;
    sys_cmd = 0;

    return iRes;
}
//Maoyong 2004.05.31 for clear JPEG Preview Background
void ClearJpegPreviewBg(void)
{
#ifdef INDIGO_STYLE_FSGUI
	//2006-06-02, mimitsai add for HD ui.
    DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB );//chenzhao20050613 PHILIPS_FSGUI
    JPEG_Preview_drawed = DIR_LIST_IN_DIR_AREA;
#elif defined(NEW_MP3_GUI)
	//2006-06-02, mimitsai add for HD ui.
    DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, 0x36, 0xc1, DIR_AREA_BKGROUND_CRCB);//chenzhao20050613 PHILIPS_FSGUI
    JPEG_Preview_drawed = DIR_LIST_IN_DIR_AREA;
#elif defined (FS_BMP_GUI)//zhaoyanhua add 2004-6-11 10:47
    int i = 0;
    FSGUI_DrawBackGround(fsArea[FS_AREA_DIRITEM].xStart + 8,
                            fsArea[FS_AREA_DIRITEM].yStart - 12  ,
                            fsArea[FS_AREA_DIRITEM].xSize- 16,
                            1,LAY_FILE_BG_10_0);
	
    for (i = 0; i < PER_PAGE; i++)//8 sections
    {
        //clear from the position of icon.
        FSGUI_DrawBackGround(fsArea[FS_AREA_DIRITEM].xStart,
                            fsArea[FS_AREA_DIRITEM].yStart + 32 * i ,
                            fsArea[FS_AREA_DIRITEM].xSize,
                            1,
                            LAY_FILE_BG_10_1 + i );
    }
    FSGUI_DrawBackGround(fsArea[FS_AREA_DIRITEM].xStart + 8,
                            fsArea[FS_AREA_DIRITEM].yStart + 32 * PER_PAGE  ,
                            fsArea[FS_AREA_DIRITEM].xSize - 16,
                            1,LAY_FILE_BG_10_9);
    JPEG_Preview_drawed = DIR_LIST_IN_DIR_AREA;
#else
	//2006-06-02, mimitsai add for HD ui.
  	ClearRectArea(0, 0, 0, 0x36, 0xc1, FS_AREA_DIRITEM, 0);//zhaoyanhua add
#endif
}

//Maoyong 2004.07.01 when in JPEG state, enter DIR area should refresh for newer GUI types
void FSGUI_ChkJpgStRedrawDirArea(void)
{
#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
        if( (pFsJpeg->gifsState == FS_STATE_LIST)
        && (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
        )
        {
            //Maoyong changed 2004.03.13.When exit preview to DIR, directly clear preview bground.
            //Avoid Bug:Rapid Operation will make DIR bground has preview bground in part.
            //The Bug will happen when picture take long time to show, user enter L/R rapidly
            pFsJpeg->gifsbPreview = 0;
		#ifdef INDIGO_STYLE_FSGUI
			//2006-06-02, mimitsai add for HD ui.
			DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB);//chenzhao20050613 PHILIPS_FSGUI				    
		#elif defined(NEW_MP3_GUI)
			//2006-06-02, mimitsai add for HD ui.
	        DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, 0x36, 0xc1, DIR_AREA_BKGROUND_CRCB);//chenzhao20050613 PHILIPS_FSGUI
            #endif
            JPEG_Preview_drawed = DIR_LIST_IN_DIR_AREA;

            refresh_dir_icon = 1;
            FSShowDirIcon();
            refresh_dir_page = 1;
            #ifdef FS_BMP_GUI
            DIR_MoveScroll(pFsJpeg->dir_page_now);//show dir scroll bar
            #endif
            DirList();
            ShowCurrentDirPlaying();
        }
#endif //#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
}


#if defined(HANYANG_LR_CHANGE_PAGE)||defined (SUPPORT_CHANGE_FILE_DIR_PAGE)||defined(MP3_TXT_DISPLAY)
//Maoyong for hanyang 2004.07.01
void FSGUI_Dir2FileArea(void)
{
    //When enter in DIR area, enter/select right to file area
    pFsJpeg->ControlArea = CNT_AREA_FILE;
    #if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
    ShowHL();
    #else
	SelectHL();
    #endif
}
void FSGUI_File2DirArea(void)
{
    pFsJpeg->ControlArea = CNT_AREA_DIR;
    FSGUI_ChkJpgStRedrawDirArea();
#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
    ShowHL();
#else
	SelectHL();
#endif
}
#endif  //HANYANG_LR_CHANGE_PAGE

void FSGUI_FileAreaUpdownRefresh(void)
{

    if ((pFsJpeg->gifsState == FS_STATE_LIST) && (pFsJpeg->gifsFuncBtn != FS_FUNC_MP3))
    {
        Will2Playing();
        pFsJpeg->gifsbPreview = 1;
    }
#ifdef FSGUI_NO_BLINK_SCROLL
	MoveScroll(pFsJpeg->file_page_will * PER_PAGE + pFsJpeg->file_will,SCROLLBAR_UP);
	up_down_done=1;
#elif !defined(FS_BMP_GUI)
	#if (defined(NEW_MP3_GUI)||defined(INDIGO_STYLE_FSGUI)) && !defined(MP3_LARGE_GUI) //2006-03-23, mimitsai add
// 2006-03-16, mimitsai modify 
	MoveScroll(pFsJpeg->file_page_will * PER_PAGE + pFsJpeg->file_will, FS_AREA_MOVEBAR);
	#else
		MoveScroll(pFsJpeg->file_page_will * PER_PAGE + pFsJpeg->file_will);
	#endif
#endif

#ifdef JPG_OLD_PARSER_FLOW
    if (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
    {
        _JPGBreak();
        jpg_break_up_down = 1;    //Maoyong 2004.05.19

//Maoyong 2004.05.31,when IR up/down, should clear current preview picture
#ifdef INDIGO_STYLE_FSGUI
		//2006-06-02, mimitsai add for HD ui.
		DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB);
                    
#elif defined (NEW_MP3_GUI)
        FSGUI_FillFrameBuf(Rect[ PREVIEW_RECT].xStart, Rect[ PREVIEW_RECT].yStart,
                           Rect[ PREVIEW_RECT].xSize,  Rect[ PREVIEW_RECT].ySize,
                           PREVIEW_BKGROUND_Y, PREVIEW_BKGROUND_CRCB);
#else
    #if !defined (FS_BMP_GUI)
	//2006-06-02, mimitsai add for HD ui.
  	ClearRectArea(0, 0, 0, 0x36, 0xc1, FS_AREA_PREVIEWJPG, 0);//zhaoyanhua add
	#endif
#endif
    }
#endif//#ifdef JPG_OLD_PARSER_FLOW
}

UINT32  FSGUI_CmdLeft()
{
    UINT32 iRes=0;
#ifdef  MP3_JPEG_COWORK
        old_time=get_stc_32_inline();//get the press time
#endif
    if (pFsJpeg->gifsState == FS_STATE_JPEG)
    {
#ifdef JPG_EFFECT
		sys_cmd = (CMD_SELECT | CMD_FUNC_GAME_L);
#else
		sys_cmd = iRes;
#endif

        return sys_cmd;
    }

    if (pFsJpeg->ControlArea == CNT_AREA_FILE)
    {
        pFsJpeg->ControlArea = CNT_AREA_DIR;
        FSGUI_ChkJpgStRedrawDirArea();
        iRes = 0x20000 | sys_cmd;
        sys_cmd = 0;
    }
#ifndef GPS_MP3_UI			//suxin add 050922 for GPS_MP3_UI change media page
    else if (pFsJpeg->ControlArea == CNT_AREA_DIR)
    {
        if (pFsJpeg->gifsMP3Count)
            pFsJpeg->ControlArea = CNT_AREA_MP3BUTTON;
        else if (pFsJpeg->gifsJPEGCount)
            pFsJpeg->ControlArea = CNT_AREA_JPEGBUTTON;
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
        else if (pFsJpeg->gifsGAMECount)
            pFsJpeg->ControlArea = CNT_AREA_GAMEBUTTON;
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 020930
        else if (pFsJpeg->gifsOtherCount)
            pFsJpeg->ControlArea = CNT_AREA_OTHERBUTTON;
#endif
#ifdef SUPPORT_MIDI
        else if (pFsJpeg->gifsMidiCount)
            pFsJpeg->ControlArea = CNT_AREA_MIDIBUTTON;
#endif
    }
    else if (pFsJpeg->ControlArea == CNT_AREA_MP3BUTTON)
    {
        pFsJpeg->ControlArea = CNT_AREA_DIR;
        FSGUI_ChkJpgStRedrawDirArea();
    }
    else if(pFsJpeg->ControlArea == CNT_AREA_JPEGBUTTON)
    {
        if (pFsJpeg->gifsMP3Count)
            pFsJpeg->ControlArea = CNT_AREA_MP3BUTTON;
        else
        {
            pFsJpeg->ControlArea = CNT_AREA_DIR;
            FSGUI_ChkJpgStRedrawDirArea();
        }
    }
#endif      //#ifndef GPS_MP3_UI	

#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
    else if(pFsJpeg->ControlArea == CNT_AREA_GAMEBUTTON)
    {
        if (pFsJpeg->gifsJPEGCount)
            pFsJpeg->ControlArea = CNT_AREA_JPEGBUTTON;
        else if (pFsJpeg->gifsMP3Count)
            pFsJpeg->ControlArea = CNT_AREA_MP3BUTTON;
        else
            pFsJpeg->ControlArea = CNT_AREA_DIR;
    }
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 020930
    #ifndef GPS_MP3_UI	//suxin add 050922 for GPS_MP3_UI change media page
    else if (pFsJpeg->ControlArea == CNT_AREA_OTHERBUTTON)
    {
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
        if (pFsJpeg->gifsGAMECount)
            pFsJpeg->ControlArea = CNT_AREA_GAMEBUTTON;
        else
#endif
            if (pFsJpeg->gifsJPEGCount)
                pFsJpeg->ControlArea = CNT_AREA_JPEGBUTTON;
            else if (pFsJpeg->gifsMP3Count)
                pFsJpeg->ControlArea = CNT_AREA_MP3BUTTON;
            else
                pFsJpeg->ControlArea = CNT_AREA_DIR;
    }
    #endif	//#ifndef GPS_MP3_UI
#endif	//#ifdef SUPPORT_FILE_SYSTEM_MODE

#ifdef SUPPORT_MIDI
    else if (pFsJpeg->ControlArea == CNT_AREA_MIDIBUTTON)
    {
        #ifdef SUPPORT_FILE_SYSTEM_MODE
        if (pFsJpeg->gifsOtherCount)
            pFsJpeg->ControlArea = CNT_AREA_OTHERBUTTON;
        else
        #endif

        #if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
        if (pFsJpeg->gifsGAMECount) //axel modified 2004/7/28
            pFsJpeg->ControlArea = CNT_AREA_GAMEBUTTON;
        else
        #endif

            if(pFsJpeg->gifsJPEGCount)
                pFsJpeg->ControlArea = CNT_AREA_JPEGBUTTON;
            else if(pFsJpeg->gifsMP3Count)
                pFsJpeg->ControlArea = CNT_AREA_MP3BUTTON;
            else
                pFsJpeg->ControlArea = CNT_AREA_DIR;
    }
#endif //SUPPORT_MIDI
#ifdef SUPPORT_PLAYLIST		//wanghaoying 2005-9-28 19:31
    else if (pFsJpeg->ControlArea == CNT_AREA_PLAYLISTBUTTON)
    {
        #ifdef SUPPORT_FILE_SYSTEM_MODE
        if (pFsJpeg->gifsOtherCount)
            pFsJpeg->ControlArea = CNT_AREA_OTHERBUTTON;
        else
        #endif
        #if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
        if (pFsJpeg->gifsGAMECount) //axel modified 2004/7/28
            pFsJpeg->ControlArea = CNT_AREA_GAMEBUTTON;
        else
        #endif
        if(pFsJpeg->gifsJPEGCount)
            pFsJpeg->ControlArea = CNT_AREA_JPEGBUTTON;
        else if(pFsJpeg->gifsMP3Count)
            pFsJpeg->ControlArea = CNT_AREA_MP3BUTTON;
        else
            pFsJpeg->ControlArea = CNT_AREA_DIR;
    }
#endif

#ifdef MP3_TXT_DISPLAY//zhaoyanhua add 2003-9-1 17:49
    if (((MP3_Lyrics_Drawed == MP3_LYRICS_IN_DIR_AREA)
      && (pFsJpeg->ControlArea == CNT_AREA_DIR)
      && (pFsJpeg->gifsFuncBtn == FS_FUNC_MP3))
      ||(!MP3TotalNo))
    {
		//2006-06-02, mimitsai add for HD ui.
        DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, 0x36, 0xc1, DIR_AREA_BKGROUND_CRCB);
        refresh_dir_icon = 1;
        FSShowDirIcon();
        refresh_dir_page = 1;
        DirList();
        MP3_Lyrics_Drawed = DIR_LIST_IN_DIR_AREA;
    }
#endif/*MP3_TXT_DISPLAY*/

#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
    //avoid GUI blinking.zhaoyanhua 2004-2-2 16:25
    //SelectHL();
    ShowHL();

#ifndef MP3_LARGE_GUI  //2006-03-23, mimitsai add
// 2006-03-16, mimitsai modify 
#ifdef DIR_SCROLL_BAR
    if(pFsJpeg->ControlArea == CNT_AREA_DIR)
		MoveScroll(pFsJpeg->dir_page_now * PER_PAGE + pFsJpeg->dir_current, FS_DIR_AREA_MOVEBAR);
#endif
#endif

#else
	SelectHL();
#endif
    iRes = 0x20000 | sys_cmd;
    sys_cmd = 0;

    return iRes;
}

UINT32  FSGUI_CmdDown()
{
    UINT32 iRes=0;
#ifdef  MP3_JPEG_COWORK
    old_time=get_stc_32_inline();//get the press time
#endif
    if (pFsJpeg->gifsState == FS_STATE_JPEG)
    {
#ifdef JPG_EFFECT
		sys_cmd = (CMD_SELECT | CMD_FUNC_GAME_DN);
#else
		sys_cmd = iRes;
#endif

        return sys_cmd;
    }

    if ((pFsJpeg->ControlArea == CNT_AREA_FILE)) {
        if (pFsJpeg->file_will < (pFsJpeg->File_Count - 1))
        {
            // needn't change file page,panxing,2002-4-15
            (pFsJpeg->file_will)++;
            pFsJpeg->fsnav_trk_will = pFsJpeg->file_array[pFsJpeg->file_will] - pFsJpeg->first_mp3_entry;
        }
        else
        {
            // change file page now, panxing, 2002-4-15
            if (pFsJpeg->file_page_will < (pFsJpeg->File_Page_Count - 1))
            {
                pFsJpeg->file_page_will++;
                PrepareForChangeFilePage(pFsJpeg->file_page_will, 0, 0);
                ShowFileIcon();
                FileList();
#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
                ShowCurrentFilePlaying();//if refresh page, must redraw the current file playing .zhaoyanhua add 2004-2-3 9:12
    #ifdef FS_BMP_GUI
                MoveScroll(pFsJpeg->file_page_will);
	#endif
#endif
            }
//when show last file in a dir,down button can't use,suqiaoli add 2004-10-9            
#if defined(FSGUI_NO_BLINK_SCROLL) || defined (FS_BMP_GUI)
			else
			{
				invalid_key();       //xulf
				sys_cmd = iRes;
				return iRes;
			}
#endif
        }
#ifdef MP3_LARGE_GUI
        if ((pFsJpeg->gifsState == FS_STATE_LIST) && (pFsJpeg->gifsFuncBtn != FS_FUNC_MP3))
        {
            Will2Playing();  // do preview, panxing,2002-4-15
            pFsJpeg->gifsbPreview = 1;
        }
        MoveScroll(pFsJpeg->file_page_will * PER_PAGE + pFsJpeg->file_will);
#else//#ifdef MP3_LARGE_GUI
        #ifdef MP3_JPEG_COWORK//hongfeng 2006/2/18 show GUI correctly after press UP/DOWN/LEFT/RIGHT quickly when jpeg preview
        if(need_refresh_dirarea && (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG))//libing 2006-5-20 avoid Jpeg->mp3 show jpg preview frame.
        {
            if (JPEG_Preview_drawed == DIR_LIST_IN_DIR_AREA )
            {
        		#ifdef INDIGO_STYLE_FSGUI
				//2006-06-02, mimitsai add for HD ui.
                DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB);
        		#else
                DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, 0, 0x36, 0xc1, PREVIEW_BKGROUND_CRCB);
        		#endif
                JPEG_Preview_drawed = JPEG_PREVIEW_IN_DIR_AREA ;
            }
            else   //not redraw all the background to avoid blinkling when preview picture. zhaoyanhua note
           	{
        		#ifdef INDIGO_STYLE_FSGUI
				//2006-06-02, mimitsai add for HD ui.
                DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB);
        		#else
                FSGUI_FillFrameBuf(Rect[ PREVIEW_RECT].xStart, Rect[ PREVIEW_RECT].yStart,
                                   Rect[ PREVIEW_RECT].xSize,  Rect[ PREVIEW_RECT].ySize,
                                   PREVIEW_BKGROUND_Y, PREVIEW_BKGROUND_CRCB);
        		#endif
           	}
        }
        #endif//#ifdef MP3_JPEG_COWORK//hongfeng 2006/2/18 show GUI correctly after press UP/DOWN/LEFT/RIGHT quickly when jpeg preview
        FSGUI_FileAreaUpdownRefresh();
#endif//#ifdef MP3_LARGE_GUI
        sys_cmd = CMD_SELECT|CMD_FUNC_GAME_DN;
        iRes = 0x20000|sys_cmd;
        sys_cmd = 0;        //avoid to receive another sys_cmd when out mainloop,panxing,2002-4-13

#if defined(MP3_LARGE_GUI)&&defined(JPG_OLD_PARSER_FLOW)
        //Jeff 20020509
        if (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
        {
            _JPGBreak();
            jpg_break_up_down = 0x20;   //Maoyong 2004.04.19, down break preview flag
            FSGUI_FillFrameBuf(Rect[ PREVIEW_RECT].xStart, Rect[ PREVIEW_RECT].yStart,
                           Rect[ PREVIEW_RECT].xSize,  Rect[ PREVIEW_RECT].ySize,
                           PREVIEW_BKGROUND_Y, PREVIEW_BKGROUND_CRCB);
        }
#endif
    } else if (pFsJpeg->ControlArea == CNT_AREA_DIR) {

        if (pFsJpeg->fsnav_dir_will < (pFsJpeg->fsnav_dir_cnt - 1))
        {
            pFsJpeg->fsnav_dir_will++;
            FSGUI_PreFindDir(&(pFsJpeg->fsnav_dir_will), 0); //panxing for yuxing,2002-4-11
            CalcDirNow(&(pFsJpeg->fsnav_dir_will));
            FSShowDirIcon();
            DirList();

#ifndef MP3_LARGE_GUI  //2006-03-23, mimitsai add
	#ifdef DIR_SCROLL_BAR			
			//2006-03-16, mimitsai add for Dir scroll bar
			MoveScroll(pFsJpeg->dir_page_now * PER_PAGE + pFsJpeg->dir_current, FS_DIR_AREA_MOVEBAR);
#endif
#endif	

        #ifdef FS_BMP_GUI
            if (pFsJpeg->dir_current % PER_PAGE == 0)
                DIR_MoveScroll(pFsJpeg->dir_page_now);
        #endif

		//wanghaoying 2004-8-4 21:27, maybe this block not need for MP3_LARGE_GUI
        #if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
            //when return to prev page,must show the current playing dir . zhaoyanhua 2004-6-30 10:14
            int  dir_index = antiAnchorDir(pFsJpeg->fsnav_dir_will);

            if ( dir_index == ((pFsJpeg->dir_page_now) * PER_PAGE))//pFsJpeg->dir_page_now
                ShowCurrentDirPlaying();
        #endif//  #if defined (NEW_MP3_GUI) || defined (FS_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)
            sys_cmd = CMD_SELECT|CMD_FUNC_GAME_DN;
            iRes = 0x20000|sys_cmd;
            sys_cmd = 0;    // avoid receive another command,panxing,2002-4-13
        }
    }

#ifdef FS_BMP_GUI  //when control area is buttons, press down to move to files, add by feeling 2004-07-05
	else  if (pFsJpeg->ControlArea >  CNT_AREA_DIR)
	{
		pFsJpeg->ControlArea = CNT_AREA_FILE;
        if (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)//zhaoyanhua  3-7-10 11:23
	    {
		    if (JPEG_Preview_drawed == JPEG_PREVIEW_IN_DIR_AREA)
			{
				JPEG_Preview_drawed = DIR_LIST_IN_DIR_AREA ;
			}
	        // to solve when UP to preview JPEG,restart. 3-7-24 16:51
			pFsJpeg->gifsbPreview = 1;
	    }
		sys_cmd = CMD_SELECT|CMD_FUNC_GAME_DN;
		iRes = 0x20000|sys_cmd;
		sys_cmd = 0;    // avoid receive another command,panxing,2002-4-13
	}
#endif
    else
    {
        iRes = 0;
        sys_cmd = 0;

    }
#if (defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI))&& !(defined (MP3_JPEG_COWORK))
//ycwen  2005/1/21 When MP3_JPEG_COWORK, ShowHL is needed when mp3/jpg long seek
//#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI)
    //avoid GUI blinking.zhaoyanhua 2004-2-2 16:25
    //reduce flash,when preview jpeg,suqiaoli add 2004-10-9     
    #ifdef JPG_OLD_PARSER_FLOW
    if( (pFsJpeg->gifsFuncBtn != FS_FUNC_JPEG)||(pFsJpeg->ControlArea == CNT_AREA_DIR))
    #endif
    	ShowHL();
#else
    SelectHL();
#endif

// 2006-09-08, add for refreshing display trk info of game and video clip when selected by user highlight.
#if defined(SUPPORT_FILE_SYSTEM_MODE)
	if((pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)
    #if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
	||(pFsJpeg->gifsFuncBtn == FS_FUNC_GAME)
	#endif
	)
		FSGUI_JpgUpdateOSD();
#endif

    return iRes;
}

UINT32  FSGUI_CmdUp()
{
    UINT32  iRes=0;
#ifdef  MP3_JPEG_COWORK
        old_time=get_stc_32_inline();//get the press time
#endif
    if (pFsJpeg->gifsState == FS_STATE_JPEG)
	{//terry,2004/1/30 06:38PM
#ifdef JPG_EFFECT
        sys_cmd = (CMD_SELECT | CMD_FUNC_GAME_UL);
#else
        sys_cmd = iRes;
#endif

        return sys_cmd;
    }

    if ((pFsJpeg->ControlArea == CNT_AREA_FILE)) {
        // Now in File area, panxing, 2002-1-29
        if (pFsJpeg->file_will > 0)
        {
            // needn't change file page, panxing, 2002-4-15
            (pFsJpeg->file_will)--;
            pFsJpeg->fsnav_trk_will = pFsJpeg->file_array[pFsJpeg->file_will] - pFsJpeg->first_mp3_entry;
        }
        else
        {
            // change file page now, panxing, 2002-4-15
            if (pFsJpeg->file_page_will)
            {
                pFsJpeg->file_page_will--;
                PrepareForChangeFilePage(pFsJpeg->file_page_will, 0, 1);
                ShowFileIcon();
                FileList();
#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
                ShowCurrentFilePlaying();//If refresh page,must redraw the current file playing.zhaoyanhua add 2004-2-3 9:09
    #ifdef FS_BMP_GUI
                MoveScroll(pFsJpeg->file_page_will);
    #endif
#endif
            }
#if defined(FS_BMP_GUI)&&!defined(GPS_MP3_UI)  	//suxin add 050922 for GPS_MP3_UI change media page
		    else//when control area is the first file in the file list, press up to move to the correspond button, add by feeling 2004-07-05
		    {
		    	#ifdef USE_FSGUI_TO_PLAY_CD//frank.huang add 051014
				if(cd_type_loaded==CDDA)
					invalid_key();
				else
				#endif
 			    pFsJpeg->ControlArea = pFsJpeg->gifsFuncBtn +1;//CNT_AREA_MP3BUTTON;
		    }
#endif

#ifdef FSGUI_NO_BLINK_SCROLL
			else
			{
				invalid_key();
				sys_cmd = iRes;
				return iRes;
			}
#endif
        }
#ifdef MP3_LARGE_GUI
        if ((pFsJpeg->gifsState == FS_STATE_LIST) && (pFsJpeg->gifsFuncBtn != FS_FUNC_MP3))
        {
            Will2Playing();
            pFsJpeg->gifsbPreview = 1;
        }
        MoveScroll(pFsJpeg->file_page_will * PER_PAGE + pFsJpeg->file_will);
        sys_cmd = CMD_SELECT|CMD_FUNC_GAME_UL;

#else
        #ifdef MP3_JPEG_COWORK//hongfeng 2006/2/18 show GUI correctly after press UP/DOWN/LEFT/RIGHT quickly when jpeg preview
        if(need_refresh_dirarea && (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG))//libing 2006-5-20 avoid Jpeg->mp3 show jpg preview frame.
        {
            if (JPEG_Preview_drawed == DIR_LIST_IN_DIR_AREA )
            {
        		#ifdef INDIGO_STYLE_FSGUI
				//2006-06-02, mimitsai add for HD ui.
                DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB);
        		#else
                DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, 0, 0x36, 0xc1, PREVIEW_BKGROUND_CRCB);
        		#endif
                JPEG_Preview_drawed = JPEG_PREVIEW_IN_DIR_AREA ;
            }
            else   //not redraw all the background to avoid blinkling when preview picture. zhaoyanhua note
           	{
        		#ifdef INDIGO_STYLE_FSGUI
				//2006-06-02, mimitsai add for HD ui.
                DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB);
        		#else
                FSGUI_FillFrameBuf(Rect[ PREVIEW_RECT].xStart, Rect[ PREVIEW_RECT].yStart,
                                   Rect[ PREVIEW_RECT].xSize,  Rect[ PREVIEW_RECT].ySize,
                                   PREVIEW_BKGROUND_Y, PREVIEW_BKGROUND_CRCB);
        		#endif
           	}
        }
        #endif//#ifdef MP3_JPEG_COWORK

        FSGUI_FileAreaUpdownRefresh();
        sys_cmd = CMD_SELECT|CMD_FUNC_GAME_DN;
#endif
        iRes = 0x20000|sys_cmd;
        sys_cmd = 0;        //avoid to receive another sys_cmd when out mainloop,panxing,2002-4-13

#ifdef JPG_OLD_PARSER_FLOW
        //Jeff 20020509
        if (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
        {
            //suqiaoli delete old part here,in order to show correctly Jpeg dir.
            _JPGBreak();
			#ifdef MP3_LARGE_GUI
			jpg_break_up_down = 0x10;
			#else
            jpg_break_up_down = 1;    //Maoyong 2004.05.19
			#endif

	//Maoyong 2004.05.31,when IR up/down, should clear current preview picture

	#ifdef INDIGO_STYLE_FSGUI
			//2006-06-02, mimitsai add for HD ui.
			DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB);
	#elif defined(NEW_MP3_GUI)
            FSGUI_FillFrameBuf(Rect[ PREVIEW_RECT].xStart, Rect[ PREVIEW_RECT].yStart,
                           Rect[ PREVIEW_RECT].xSize,  Rect[ PREVIEW_RECT].ySize,
                           PREVIEW_BKGROUND_Y, PREVIEW_BKGROUND_CRCB);
	#elif !defined (FS_BMP_GUI)
		//2006-06-02, mimitsai add for HD ui.
	  	ClearRectArea(0, 0, 0, 0x36, 0xc1, FS_AREA_PREVIEWJPG, 0);//zhaoyanhua add
	#endif
        }//end   if (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
#endif  //#ifdef JPG_OLD_PARSER_FLOW         
        
    } //end  if ((pFsJpeg->ControlArea == CNT_AREA_FILE))
    else if (pFsJpeg->ControlArea == CNT_AREA_DIR) {
#ifdef FS_BMP_GUI //when control area is the first dir in the dir list, press up to move to the correspond button, add by feeling 2004-07-05
	if  ( (pFsJpeg->dir_current == 0) && (pFsJpeg->dir_page_now == 0))
    {
		#ifndef	GPS_MP3_UI
	    pFsJpeg->ControlArea = pFsJpeg->gifsFuncBtn +1;//CNT_AREA_MP3BUTTON;
		#endif
		sys_cmd = CMD_SELECT|CMD_FUNC_GAME_UL;
		iRes = 0x20000 | sys_cmd;
        sys_cmd = 0;
    }
	else
#endif

        // Now in dir area, panxing, 2002-1-22
        if (pFsJpeg->fsnav_dir_will)
        {
            pFsJpeg->fsnav_dir_will--;
            FSGUI_PreFindDir(&(pFsJpeg->fsnav_dir_will), 1); //panxing for yuxing,2002-4-11
            CalcDirNow(&(pFsJpeg->fsnav_dir_will));
            FSShowDirIcon();
            DirList();

#ifndef MP3_LARGE_GUI  //2006-03-23, mimitsai add
			//2006-03-16, mimitsai add for Dir scroll bar
#ifdef DIR_SCROLL_BAR			
			MoveScroll(pFsJpeg->dir_page_now * PER_PAGE + pFsJpeg->dir_current, FS_DIR_AREA_MOVEBAR);
#endif
#endif	

        #ifdef FS_BMP_GUI
            if (pFsJpeg->dir_current % PER_PAGE == PER_PAGE - 1)
                DIR_MoveScroll(pFsJpeg->dir_page_now);
        #endif

		//wanghaoying 2004-8-4 21:27, maybe this block not need for MP3_LARGE_GUI
        #if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
            //when return to prev page,must show the current playing dir . zhaoyanhua 2004-6-30 10:14
            int  dir_index = antiAnchorDir(pFsJpeg->fsnav_dir_will);

            if ( dir_index == ((pFsJpeg->dir_page_now+1) * PER_PAGE - 1))//pFsJpeg->dir_page_now
                ShowCurrentDirPlaying();
        #endif// #if defined (NEW_MP3_GUI) || defined (FS_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)

            sys_cmd = CMD_SELECT|CMD_FUNC_GAME_UL;
            iRes = 0x20000|sys_cmd;
            sys_cmd = 0;    //avoid to receive another commmand when timeout mainloop,panxing,2002-4-13
        }//end if (pFsJpeg->fsnav_dir_will)
    } //end if (pFsJpeg->ControlArea == CNT_AREA_DIR)
#ifdef FS_BMP_GUI //when control area is button,when press up to reture invalid key, by feeling 2004-07-05
	else
	{
		invalid_key();
		sys_cmd = iRes;
		return iRes;
        }
#else
    else
    {
        // Now in control button area, panxing, 2002-1-22
        pFsJpeg->ControlArea = CNT_AREA_FILE;
        iRes = 0x20000 | sys_cmd;
        sys_cmd = 0;
#ifdef JPG_OLD_PARSER_FLOW
#if defined (NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)//|| defined (FS_BMP_GUI)
        if (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)//zhaoyanhua  3-7-10 11:23
        {
            if (JPEG_Preview_drawed == JPEG_PREVIEW_IN_DIR_AREA)
            {
                JPEG_Preview_drawed = DIR_LIST_IN_DIR_AREA ;
            }
            // to solve when UP to preview JPEG,restart. 3-7-24 16:51
            pFsJpeg->gifsbPreview = 1;
        }
#endif//end #if defined (NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI) //|| defined (FS_BMP_GUI)
#endif//#ifdef JPG_OLD_PARSER_FLOW
    }
#endif//end #ifdef FS_BMP_GUI

#if (defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)) && !(defined (MP3_JPEG_COWORK)) //ycwen
//ycwen : 2005/1/21 When MP3_JPEG_COWORK, ShowHL is needed when mp3/jpg long seek    
//#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
    //avoid GUI blinking.zhaoyanhua 2004-2-2 16:25
    //reduce flash,when preview jpeg,suqiaoli add 2004-10-9 
    //if( (pFsJpeg->gifsFuncBtn != FS_FUNC_JPEG)||(pFsJpeg->ControlArea == CNT_AREA_DIR))
    #ifdef JPG_OLD_PARSER_FLOW
    if(!( (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)&&(pFsJpeg->ControlArea == CNT_AREA_FILE)))
    #endif
    //replace by liudan,to avoid when up from first jpg dir to jpbbutton the key is invalid,2004-11-6 9:28
    ShowHL();
#else
	SelectHL();
#endif

// 2006-09-08, add for refreshing display trk info of game and video clip when selected by user highlight.
#if defined(SUPPORT_FILE_SYSTEM_MODE)
	if((pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)
    #if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
	||(pFsJpeg->gifsFuncBtn == FS_FUNC_GAME)
	#endif
	)
		FSGUI_JpgUpdateOSD();
#endif

    return iRes;
}

UINT32 FSGUI_CmdEnter()
{
    UINT32  iRes=0;
    BYTE    bSorb=1;

#ifdef RECORD_PER_SECOND        //avoid bug when playing mp3  gerry  2-12-3 19:46
    resumeMSF = 0;
#endif

#ifdef MP3_TXT_DISPLAY //zhaoyanhua add 2003-9-2 16:06
    if ((MP3_Lyrics_Drawed == MP3_LYRICS_IN_DIR_AREA) && (pFsJpeg->ControlArea != CNT_AREA_FILE))
    {
        MP3_Lyrics_Drawed = DIR_LIST_IN_DIR_AREA;
		//2006-06-02, mimitsai add for HD ui.
        DrawRectCorner(Rect[DIR_RECT], CORNER_RAD, 1, DIR_STEP, 0x36, 0xc1,DIR_AREA_BKGROUND_CRCB);
    }
	if ((MP3_Lyrics_Drawed == DIR_LIST_IN_DIR_AREA) && (pFsJpeg->ControlArea != CNT_AREA_FILE))
    {
		MP3TotalNo = 0;
    }

#endif

#ifdef JPG_EFFECT
    #ifdef JPG_OLD_PARSER_FLOW
    jpeg_effect_init();
	#endif
#endif
    if (pFsJpeg->ControlArea == CNT_AREA_FILE)
    {
        #ifdef SELECT_FILE_DIR_CANCEL_REPEAT  //hongfeng add 2006/2/21
        if(rep_mode == REPEAT_TRACK)
        {
            rep_mode = REPEAT_IDLE;
            ShowRepInfo();
        }    
        #endif

        if (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
        {
#ifdef JPG_OLD_PARSER_FLOW            
    #ifdef MENU_STOP_EXCHANGE
                pFsJpeg->g_nJpegMode=JPEG_THUMBNAIL_MODE;       //xulf 2003-12-6
    #endif
    
                pFsJpeg->gifsState = FS_STATE_JPEG;
    
    #if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
                osd_tog_region(1, OSD_OFF);     //Maoyong 2004.03.11, When show "STOP", enter should make osd disappear
    #endif
#endif//#ifdef JPG_OLD_PARSER_FLOW
        }
        else if (pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
        {
            #ifdef USE_FSGUI_TO_PLAY_CD//frank.huang add 051014
		    if(cd_type_loaded==CDDA)
		    {
			    ircmd_post_func(CMD_SELECT | (pFsJpeg->fsnav_trk_will+1));
		    }	
		    #endif
            pFsJpeg->gifsState = FS_STATE_MP3;
            Will2Playing();
        }

#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
        else if (pFsJpeg->gifsFuncBtn == FS_FUNC_GAME)
        {
            pFsJpeg->gifsState = FS_STATE_GAME;
        }
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 021001    2004/01/07 yltseng
        else if (pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)
        {
            pFsJpeg->gifsState = FS_STATE_OTHER;
            Will2Playing();
        }
#endif
#ifdef SUPPORT_MIDI
        else if (pFsJpeg->gifsFuncBtn == FS_FUNC_MIDI)
        {
            pFsJpeg->gifsState = FS_STATE_MIDI;
            Will2Playing();
        }
#endif

	//2006-06-02, mimitsai add for HD ui.
	#if defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)//2006-06-02, mimitsai add for HD ui.
		ClearRectArea(Rect[FILE_RECT], FILE_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, FILE_AREA_BKGROUND_CRCB,FS_AREA_FILEITEM, fsnav_file_HL);
	#elif defined(FS_BMP_GUI)
        FSGUI_ClearArea(FS_AREA_FILEITEM, fsnav_file_HL);
        ShowFileIcon();//avoid disppearing file icon,suqiaoli add 2004-10-9
    #endif
        FSShowFileItem(fsnav_file_HL, iso9660_file[pFsJpeg->file_array[fsnav_file_HL]].name);//resume the last HL


		#ifdef USE_FSGUI_TO_PLAY_CD//frank.huang add 051014
		if(cd_type_loaded!=CDDA)
		#endif
        sys_cmd = CMD_FUNC | CMD_FUNC_SELECT;
        iRes = sys_cmd;
        bSorb = 0;
    }
    else if (pFsJpeg->ControlArea == CNT_AREA_DIR)
    {
        #ifdef SELECT_FILE_DIR_CANCEL_REPEAT  //hongfeng add 2006/2/21
        if((rep_mode == REPEAT_DIRECTORY)||(rep_mode == REPEAT_TRACK))
        {
            rep_mode = REPEAT_IDLE;
            ShowRepInfo();
        }    
        #endif
        pFsJpeg->fsnav_dir_now = pFsJpeg->fsnav_dir_will;
        FSGUI_PreChangeDir(&(pFsJpeg->fsnav_dir_now), 0);
        sys_cmd = CMD_FUNC_SELECT;//qinhua,modify for 8202L 16M code jpeg total track error,2006-7-20 10:24上午
        //sys_cmd = CMD_FUNC|CMD_FUNC_SELECT;
        iRes = sys_cmd;
        bSorb = 0;

    #if !defined (FS_BMP_GUI)//zhaoyanhua add 2004-6-14 14:20
        refresh_dir_icon = 1;
    #endif//ifndef FS_BMP_GUI

        if (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)//when change to DIR area, must refresh.zhaoyanhua note 3-7-10 11:12
            refresh_dir_page = 1;

	//2006-06-02, mimitsai add for HD ui.
	#if defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)//2006-06-02, mimitsai add for HD ui.
    	ClearRectArea(Rect[DIR_RECT], DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB, FS_AREA_DIRITEM, fsnav_dir_HL);
	#elif defined(FS_BMP_GUI)
        FSGUI_ClearArea(FS_AREA_DIRITEM, fsnav_dir_HL);
    #endif

    //clear the last HL DirItem.
	//2006-06-02, mimitsai add for HD ui.    
	#if defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)//2006-06-02, mimitsai add for HD ui.
        ClearRectArea(Rect[DIR_RECT], DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB, FS_AREA_DIRITEM, fsnav_dir_HL);    
	#endif
	
        ShowDirItem(fsnav_dir_HL, iso9660_dir[pFsJpeg->dir_array[fsnav_dir_HL]].name);//resume the last HL
        FSGUI_Refresh();

#if defined(HANYANG_LR_CHANGE_PAGE)||defined(MP3_TXT_DISPLAY)
        //When enter in DIR area, right to file area
        FSGUI_Dir2FileArea();
#endif
        //kevinmonkey sz 050609 // 2005/07/13 yltseng
        //for select directory (track now) of display (track now)/(total track) does not refresh
        disp_trk_now = 1;
    }
    else
    {
        // Now in button area, panxing, 2002-1-22
        int iChange = 0;

#ifdef SETUP_PROGRAM_IN_PLACE_UNDER_16M
        // 2004/11/26 yltseng, When exit mp3 tab, pFsJpeg->gifsState will update to FS_STATE_LIST
        // only after leave MediaMainLoop; But during this little period of time, if we use this
        // variable to do something, we may get wrong data. So I update this variable here.
        pFsJpeg->gifsState = FS_STATE_LIST; 
#endif
        
#ifdef FS_BMP_GUI
    //press enter to clear the down button
    //if hl is on the down button, the down button would not be changed,add by feeling 2004-07-05
	if (pFsJpeg->ControlArea != pFsJpeg->gifsFuncBtn +1)
	    FSGUI_DrawOneButton(pFsJpeg->gifsFuncBtn,UP_STATE);
#endif
        if ((pFsJpeg->ControlArea == CNT_AREA_MP3BUTTON) && (pFsJpeg->gifsFuncBtn != FS_FUNC_MP3))
        {
#ifndef MP3_LARGE_GUI  //2006-03-23, mimitsai add
			//2006-03-16, mimitsai add for Dir scroll bar
#ifdef DIR_SCROLL_BAR			
			MoveScroll(pFsJpeg->dir_page_now * PER_PAGE + pFsJpeg->dir_current, FS_DIR_AREA_MOVEBAR);
#endif        
#endif	
            //Maoyong 2004.05.31 when preview JPEG, enter the MP3 , must redraw the background.
            if( (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG) && (pFsJpeg->gifsState == FS_STATE_LIST) )
                ClearJpegPreviewBg();

#ifdef  MP3_JPEG_COWORK
        	back_sign=1;
        	pFsJpeg->gifsFuncBtn=FS_FUNC_MP3;
#else
            #ifdef WHEN_CHANGE_BETWEEN_MP3_JPG_DIVX_CANCEL_REPEAT
            rep_mode=REPEAT_IDLE;//shenyj add for alco 2006/03/31
            #endif
            FSNav_MP3Init();
#endif

            iChange = 1;
        }
        else if ((pFsJpeg->ControlArea == CNT_AREA_JPEGBUTTON) && (pFsJpeg->gifsFuncBtn != FS_FUNC_JPEG))
        {
#ifndef MP3_LARGE_GUI  //2006-03-23, mimitsai add
			//2006-03-16, mimitsai add for Dir scroll bar
#ifdef DIR_SCROLL_BAR			
			MoveScroll(pFsJpeg->dir_page_now * PER_PAGE + pFsJpeg->dir_current, FS_DIR_AREA_MOVEBAR);
#endif
#endif	

#ifdef IR_PROG_ON//nono 4-1-12 17:08
            if(prog_cnt)
            {
            prog_cnt = 0;
            #ifndef BEAUTIFUL_DVD//zhongshan 20050515 for beautiful dvd don't show "prog cnl"
            PrintOsdMsg(STR_OS_PROG_CNL,REGION1,1,0);
            #endif
            }
#endif//#ifdef IR_PROG_ON

#ifdef FSGUI_NO_BLINK_SCROLL
			up_down_done=0;
#endif

#if defined ( NEW_MP3_GUI) || defined ( FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
            refresh_dir_page = 1;   //Maoyong 2004.05.19
#endif
            #ifdef WHEN_CHANGE_BETWEEN_MP3_JPG_DIVX_CANCEL_REPEAT
            rep_mode=REPEAT_IDLE;//shenyj add for alco 2006/03/31
            #endif
            FSNav_JPEGInit();
#ifndef JPG_OLD_PARSER_FLOW
            AVD_SetMediaInterrupt();
#endif
#ifdef JPG_EFFECT
            Jpg_Show_Usage_Page=0;
            Jpg_Show_Usage_Flag=0;
#endif

#if defined(IR_KODAK_EFFECT_KEY_USE_DISPLAY)//nono 20031122
            if (t_disp)
			{
			        DispFadeOut();
			        disp_mode=0;
			}
#endif//defined(IR_KODAK_EFFECT_KEY_USE_DISPLAY)

            iChange = 1;
        }
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
        else if ((pFsJpeg->ControlArea == CNT_AREA_GAMEBUTTON) && (pFsJpeg->gifsFuncBtn != FS_FUNC_GAME))
        {

#ifdef IR_PROG_ON//nono 4-1-12 17:08
            if(prog_cnt)
            {
            prog_cnt = 0;
             #ifndef BEAUTIFUL_DVD//zhongshan 20050515 for beautiful dvd don't show "prog cnl"
            PrintOsdMsg(STR_OS_PROG_CNL,REGION1,1,0);
            #endif
            }
#endif//#ifdef IR_PROG_ON
/* nes driver is put into ROM, Robert 03/04/29
            if (pFsJpeg->gifsNESDrvSize > 0)
*/
            {
                AVD_SetMediaTimeout();
                iChange = 0;

                refresh_dir_page = 1;
                //Maoyong 2004.05.31 when preview JPEG, enter the MP3 , must redraw the background.
                if( (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG) && (pFsJpeg->gifsState == FS_STATE_LIST) )
                    ClearJpegPreviewBg();
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
                extern void FSNav_GameInit();
                FSNav_GameInit();
#endif                

#ifdef FS_BMP_GUI
		        FSGUI_ShowBtnTitle();//feeling 2004-07-29
#endif

                sys_cmd = CMD_FUNC | CMD_FUNC_SELECT;
                iRes = 0x20000 | sys_cmd;
                return iRes;
            }
        }
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 021001
        else if ((pFsJpeg->ControlArea == CNT_AREA_OTHERBUTTON) && (pFsJpeg->gifsFuncBtn != FS_FUNC_OTHER))
        {
#ifndef MP3_LARGE_GUI  //2006-03-23, mimitsai add
			//2006-03-16, mimitsai add for Dir scroll bar
#ifdef DIR_SCROLL_BAR			
			MoveScroll(pFsJpeg->dir_page_now * PER_PAGE + pFsJpeg->dir_current, FS_DIR_AREA_MOVEBAR);
#endif
#endif	

            disp_trk_now = 1;   // 2005/07/12 yltseng, reset display track num when switch to OTHER type media
//wanghaoying changed, 2004-5-13 9:15
#if defined(IR_PROG_ON)&& (defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI))
            if(prog_cnt)
            {
            	prog_cnt = 0;
             #ifndef BEAUTIFUL_DVD//zhongshan 20050515 for beautiful dvd don't show "prog cnl"
            	PrintOsdMsg(STR_OS_PROG_CNL,REGION1,1,0);
            #endif
            }
#endif//#ifdef IR_PROG_ON

            //Maoyong 2004.05.31 when preview JPEG, enter the MP3 , must redraw the background.
            if( (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG) && (pFsJpeg->gifsState == FS_STATE_LIST) )
                ClearJpegPreviewBg();

//yanlb 2004.08.09 when support id3,preview MP3, enter the Other , must clear id3 region.
#ifdef SUPPORT_OSDID3
			if(Is_MP3_STATE()){
				osd_tog_region(REGION3, OSD_OFF);
    		}
#endif

#if defined(NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
             refresh_dir_page = 1;
#endif
            #ifdef WHEN_CHANGE_BETWEEN_MP3_JPG_DIVX_CANCEL_REPEAT
            rep_mode=REPEAT_IDLE;//shenyj add for alco 2006/03/31
            #endif
            FSNav_OtherInit();
            //FSGUI_Refresh();//jiangxl for set other not refresh GUI
            iChange = 1;
        }
#endif
#ifdef SUPPORT_MIDI
        else if ((pFsJpeg->ControlArea == CNT_AREA_MIDIBUTTON) && (pFsJpeg->gifsFuncBtn != FS_FUNC_MIDI))
        {
            MidiCreate();
            iChange = 1;
        }
#endif
#ifdef SUPPORT_PLAYLIST		//wanghaoying 2005-9-28 19:31
        else if((pFsJpeg->ControlArea == CNT_AREA_PLAYLISTBUTTON)&&(pFsJpeg->gifsFuncBtn != FS_FUNC_PLAYLIST))
        {
            if( (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG) && (pFsJpeg->gifsState == FS_STATE_LIST) )
                ClearJpegPreviewBg();
    #ifdef IR_PROG_ON//nono 4-1-12 17:08
            if(prog_cnt)
            {
                prog_cnt = 0;
        #ifndef BEAUTIFUL_DVD//zhongshan 20050515 for beautiful dvd don't show "prog cnl"
                PrintOsdMsg(STR_OS_PROG_CNL,REGION1,1,0);
        #endif
            }
    #endif//#ifdef IR_PROG_ON

            FSNav_PlayListInit();

            iChange = 1;
            
        }
#endif

        if(iChange)
        {
			#if !(defined(NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI))
			//2006-06-02, mimitsai add for HD ui.
		  	ClearRectArea(0, 0, 0, 0x36, 0xc1, FS_AREA_PREVIEWJPG, 0);//zhaoyanhua add
			#endif

            #ifdef DISPLAY_FBWARD_OSD //Maoyong added 2004-8-13 23:56
		    if( (RegionOnOff[1][2]==STR_OS_FF)||(RegionOnOff[1][2]==STR_OS_FB) ) {
		        timeout_osd[1]=1;//nono 2003-8-11 22:51
                adv_search_time = 0;
            }
            #endif//DISPLAY_FBWARD_OSD
			#ifndef FS_BMP_GUI
            refresh_dir_page = 1;//frank.huang add to avoid an error about highlight folder icon in mp4 page 050929
			#endif
            sys_cmd = CMD_FUNC | CMD_FUNC_SELECT;
            iRes = sys_cmd;
            bSorb = 0;
        }
        #ifdef HANYANG_LR_CHANGE_PAGE
        //after selecting button, change to dir area
        FSGUI_File2DirArea();
        #endif
    }

    if (bSorb == 1)
    {
        sys_cmd = 0;
        iRes=0;
    }
#ifdef FS_BMP_GUI
	if (pFsJpeg->ControlArea >= CNT_AREA_MP3BUTTON)
		FSGUI_ShowBtnTitle();
#endif
    return iRes;
}

#ifdef MP3_TXT_DISPLAY
#define LYRECT_XSIZE      145
#define LYRECT_XSTART     25
void ClearLycArea(BTNAREA  Rect, UINT16 RectColorStep,UINT16 RegionColor_C,int ItemStart, int ItemNumber)
{
    int i =0;
    int  x0=0,y0=0;
    UINT8 RegionColor_Y[60];
    int Region[60];
    UINT8 StepCount =0;
    int  xAreaStart=0,yAreaStart = 0, xAreaSize=0,yAreaSize=0;

    // calulate the Y and Region width according to the given step.
    for ( i = 0; i < RectColorStep; i++ )
    {
        Region[i] = Rect.xStart + i*(Rect.xSize / RectColorStep);
        RegionColor_Y[i] = 0x36 + i*((0xc1 - 0x36)/RectColorStep);

    }

    xAreaStart = LYRECT_XSTART;
    yAreaStart = FS_DIRLIST_YSTART + ItemStart *FS_FILELIST_YSTEP;
    xAreaSize =  LYRECT_XSIZE ;
    yAreaSize =  ItemNumber*FS_FILELIST_YSTEP;

    StepCount = 0;

    //printf("Region[ 1 ] = %d\n",Region[1]);

    while(xAreaStart >= Region[StepCount])
    {
        StepCount++;
    }
    StepCount = StepCount-1;
    //printf("xAreaStart=%d,Region[%d]=%d\n",xAreaStart,StepCount,Region[StepCount]);

    for (x0 = xAreaStart; x0 < (xAreaStart+ xAreaSize); x0++)
    {
        if((StepCount +1) < RectColorStep)
        {
            if ((x0 >= Region[StepCount]) && (x0 < Region[StepCount + 1]))
            {
                StepCount++;

            }
        }
        else
            StepCount = RectColorStep -1;

        for (y0 = yAreaStart; y0 < (yAreaStart+yAreaSize); y0++)
        {
            *Y_XY((x0),(y0)) = RegionColor_Y[StepCount];
            *C_XY((x0),(y0)) = RegionColor_C;
        }
    }

}
#endif	//#ifdef MP3_TXT_DISPLAY

#if ! (defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI))
void ClearArea(UINT16 iIndex)
{
#ifdef AUDIO_SHOW_SAVER
    if (bDisableGUI) return;
#endif

	if ((pFsJpeg->gifsState == FS_STATE_JPEG) && (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG))
		return;

	if ((iIndex == FS_AREA_FILEICON) && (refresh_file_page==0))
	{
		// need clear current file icon
		FSGUI_FillFrameBuf(fsArea[iIndex].xStart,
			fsArea[iIndex].yStart + pFsJpeg->file_current * FS_FILELIST_YSTEP,
			fsArea[iIndex].xSize, fsArea[iIndex].ySize,
			BK_GROUNDY, BK_GROUNDCRCB);
	}
	else if ((iIndex == FS_AREA_FILEICON) && (refresh_file_page == 1))
	{
		// clear all file icon
		FSGUI_FillFrameBuf(fsArea[iIndex].xStart, fsArea[iIndex].yStart,
			fsArea[iIndex].xSize, PER_PAGE * FS_FILELIST_YSTEP,
			BK_GROUNDY, BK_GROUNDCRCB);
	}
	else
	{
//		FSGUI_FillFrameBuf(fsArea[iIndex].xStart, fsArea[iIndex].yStart,
		FSGUI_FillFrameBuf(fsArea[iIndex].xStart - 2, fsArea[iIndex].yStart, // Robert 030506 for file area UI issue
			fsArea[iIndex].xSize, fsArea[iIndex].ySize,
			BK_GROUNDY, BK_GROUNDCRCB);
	}
}
#endif // if !(defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI))


/*
 * FUNC : Draw a rectangle with varient color.
 * NOTE:  
 * INPUT:
 *	 	Rect:			startX, startY.
 *   	stColor1:		luma and chroma value of the left side.
 *		stColor2:   	luma and chroma value of the right side.
 *   	direction:		the varient color direction.
 * Creator: mimitsai
 * Date: 2006-03-10
 */
void DrawVarientRect(BTNAREA Rect, YUV_COLOR stColor1, YUV_COLOR stColor2, int direction)
{
    int  x0=0,y0=0;
	UINT16 uTemp1,uTemp2;

	switch(direction)
	{
		case VERTICAL_SHADING:
			for(y0 = Rect.yStart; y0 < (Rect.yStart+Rect.ySize); y0++)
				memset(Y_XY((Rect.xStart),(y0)),stColor1.Y+ ((stColor2.Y-stColor1.Y)*(y0-Rect.yStart)/Rect.ySize),Rect.xSize);
			for(y0 = Rect.yStart; y0 < (Rect.yStart+Rect.ySize); y0+=2)
			{
				// calcute Cr and Cb of y0.
				UINT16 uTemp1 = (stColor1.Cb)+ ((stColor2.Cb-stColor1.Cb)*(y0-Rect.yStart)/Rect.ySize);/*->Cb*/
				UINT16 uTemp2 = (stColor1.Cr)+ ((stColor2.Cr-stColor1.Cr)*(y0-Rect.yStart)/Rect.ySize);/*->Cr*/
				uTemp1 = (uTemp2 << 8 ) | uTemp1;//Cr<<8|Cb, the chroma value for current line
				uTemp2 = C_XY((Rect.xStart + Rect.xSize),(y0)) - C_XY((Rect.xStart),(y0));//how many pixel to draw

				UINT16* ChromaPtr;
				ChromaPtr = C_XY((Rect.xStart),(y0));
				for(x0 = 0;x0<uTemp2;x0++) //copy every point from the CrCb value of first point.
				{
					*ChromaPtr = uTemp1;
					ChromaPtr++;
				}
			}
		break;

		case HORIZONTAL_SHADING:
			for(x0 = Rect.xStart; x0 < (Rect.xStart+Rect.xSize); x0++)
			{
				*Y_XY((x0),(Rect.yStart)) = stColor1.Y+ ((stColor2.Y-stColor1.Y)*(x0-Rect.xStart)/Rect.xSize);
				uTemp1 = (stColor1.Cb)+ ((stColor2.Cb-stColor1.Cb)*(x0-Rect.xStart)/Rect.xSize);/*->Cb*/
				uTemp2 = (stColor1.Cr)+ ((stColor2.Cr-stColor1.Cr)*(x0-Rect.xStart)/Rect.xSize);/*->Cr*/ 
				*C_XY((x0),(Rect.yStart)) = (uTemp2 << 8 ) | uTemp1;
			}
			//copy each line from the line above
			for(y0 = Rect.yStart + 1; y0 < (Rect.yStart+Rect.ySize); y0++)
				memcpy(Y_XY((Rect.xStart),(y0)),Y_XY((Rect.xStart),(y0-1)),Rect.xSize);

			for(y0 = Rect.yStart + 1; y0 < (Rect.yStart+Rect.ySize); y0++)
				memcpy(C_XY((Rect.xStart),(y0)),C_XY((Rect.xStart),(y0-1)),Rect.xSize);
			break;
			
		case DIAGONAL_SHADING:
			break;
        default:
			break;
	}			
}

#if defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)
/*
 * FUNC : Clear the item in Rectangle with four corner.
 * NOTE:  Rectangle dipslay with varient colors, so when clear the item
 *        must use the same varient colors.
 * INPUT:
 *        RectColorStep:	to calculate the same varient color as Rectangle.
 *   	  Y_1, Y2:   		Y_1 is the luma value of the left side, and the Y_2 is the luma value of the right side.
 *   	  CbCr:				the base Chrominance of varient fill colors
 *        RgionIndex: 		FILE/DIR/PATH
 *        iIndex :   		Area index.
 *        iItem  :   		if iItem >=0, it means that only clear item (file,dir) not clear the whole Area.
 * Creator: zhaoyanhua
 * modify:  mimitsai 2005-12-12
 * Date: 3-6-30 19:47
 */
void ClearRectArea(BTNAREA  Rect, UINT16 RectColorStep, UINT8 Y_1, UINT8 Y_2, UINT16 CbCr,int iIndex,int iItem)
{
    int  	x0=0,y0=0,StepCount =0;
    int  	xAreaStart=0,yAreaStart = 0, xAreaSize=0,yAreaSize=0;

	#if defined(MONO_FSGUI) || defined(PHILIPS_FSGUI)
    UINT8   RegionColorStep_Y = 0;
	#endif
	
    #ifdef PHILIPS_FSGUI//chenzhao20050613
    if(RectColorStep==0)
        RectColorStep=1;
    #endif

	#ifdef MONO_FSGUI //mono FS GUI, axel 2003-12-29 23:26
	RectColorStep=1;
    RegionColorStep_Y=PREVIEW_BKGROUND_Y;
	#endif
	
    #ifdef PHILIPS_FSGUI//chenzhao20050613
    if(RectColorStep==1)
        RegionColorStep_Y=PREVIEW_BKGROUND_Y-0x36;
    #endif
	
    if ((iIndex == FS_AREA_FILEICON) && (refresh_file_page == 0))
    {
        // need clear current file icon
        xAreaStart = fsArea[iIndex].xStart;
        yAreaStart = fsArea[iIndex].yStart + pFsJpeg->file_current * FS_FILELIST_YSTEP;
        xAreaSize  = fsArea[iIndex].xSize;
        yAreaSize  = fsArea[iIndex].ySize;
    }
    else if ((iIndex == FS_AREA_FILEICON) && (refresh_file_page == 1))
    {
        // clear all file icon
        xAreaStart = fsArea[iIndex].xStart;
        yAreaStart = fsArea[iIndex].yStart;
        xAreaSize  = fsArea[iIndex].xSize;
        yAreaSize  = PER_PAGE * FS_FILELIST_YSTEP;
    }
    else if (iItem >= 0) //for clear last FILE or DIR item when show Current playing.
    {
        xAreaStart = fsArea[iIndex].xStart - 2;
        yAreaStart = FS_DIRLIST_YSTART - DEMENSION_SIZE + iItem * FS_FILELIST_YSTEP;
        xAreaSize  = ITEM_MAX_WIDTH;//clear width;
        yAreaSize  = FS_FILELIST_YSTEP;
        
        //joshua, 20050928, modified for PMP UI with unicode font 16X16 
        #ifdef SUPPORT_UNICODE_FONT
            yAreaSize = FS_FILELIST_YSTEP+2;
        #endif
    }
    else
    {
        xAreaStart = fsArea[iIndex].xStart -2;
        yAreaStart = fsArea[iIndex].yStart;
        xAreaSize = fsArea[iIndex].xSize;
        yAreaSize = fsArea[iIndex].ySize;
    }

	// Because of using memory copy, xAreaSize must be even number,
	// avoid 4 points sharing different CbCr value.
	if((xAreaStart%2 == 1) && (xAreaSize%2 ==0))
		xAreaSize  = ((xAreaSize+3)>>1)<<1 ;
	else
		xAreaSize  = ((xAreaSize+1)>>1)<<1;
	xAreaStart = (xAreaStart>>1)<<1;
	
    StepCount = 0;
#ifdef INDIGO_STYLE_FSGUI
	while(xAreaStart >= (Rect.xStart + Rect.xSize  * StepCount / RectColorStep))
#else
    while(xAreaStart >= (Rect.xStart + (Rect.xSize / RectColorStep) * StepCount))
#endif
        StepCount++;

    StepCount = StepCount-1;
	
    for (x0 = xAreaStart; x0 < (xAreaStart+ xAreaSize); x0++)
    {
        if((StepCount +1) < RectColorStep)
        {
        #ifdef INDIGO_STYLE_FSGUI
            if ((x0 >= (Rect.xStart + Rect.xSize * StepCount   / RectColorStep)) 
			 && (x0 <  (Rect.xStart + Rect.xSize *(StepCount+1)/ RectColorStep)))
		#else
            if ((x0 >= (Rect.xStart + (Rect.xSize / RectColorStep) * StepCount))
			 && (x0 <  (Rect.xStart + (Rect.xSize / RectColorStep) * (StepCount+1))))
		#endif
                StepCount++;
        }
        else
            StepCount = RectColorStep -1;

        #ifdef PHILIPS_FSGUI//chenzhao20050613
        if(RectColorStep==1)
            StepCount = 1;
        #endif

		#ifdef INDIGO_STYLE_FSGUI
		*Y_XY(x0,yAreaStart) = Y_1+ ((Y_2-Y_1)*StepCount)/RectColorStep;
		#else
		*Y_XY(x0,yAreaStart) = 0x36+ StepCount*((0xc1-0x36)/RectColorStep);
		#endif
		*C_XY(x0,yAreaStart) = CbCr;
    }
	
	//copy each line from the line above
	for(y0 = yAreaStart + 1; y0 < (yAreaStart+yAreaSize); y0++)
	{
		memcpy(Y_XY(xAreaStart,y0),Y_XY(xAreaStart,(y0-1)),xAreaSize);
		memcpy(C_XY(xAreaStart,y0),C_XY(xAreaStart,(y0-1)),xAreaSize);
	}
}

/*                                                                                                                                                       Date   : 3-6-30 17:10
 *  FUNC: Draw a rectangle with 4 circle corner,
 *        which is filled with varient colors.
 *
 *  NOTE:
 *      1) if draw  a rectangle neither UP nor DOWN, the function
 *         will auto set the frame line color to be white .
 *      2) MAX_STEP is the max steps that the function can show.
 *
 *  INPUT:
 *   CornerRad:       the corner radius
 *   step:            use to calculate a varient color.
 *                    if step = 0, only fill with default luminance value.
 *   Y_1, Y2:   	Y_1 is the luma value of the left side, and the Y_2 is the luma value of the right side.
 *   CbCr:			the base Chrominance of varient fill colors
 *
 *  modify by mimitsai
 *  Date:2005-12-12
 */
 //for draw corner.
const BYTE  CornerLT[6][6] = {
							{0,0,0,0,1,1},
							{0,0,1,1,2,2},
							{0,1,1,2,2,2},
							{0,1,2,2,2,2},
							{1,2,2,2,2,2},
							{1,2,2,2,2,2},
                            };// Left_TOP 1/4 circle
const BYTE CornerRT[6][6] = {
							{3,1,1,0,0,0},
							{2,3,1,1,0,0},
							{2,2,3,1,1,0},
							{2,2,2,1,1,1},
							{2,2,2,2,1,1},
							{2,2,2,2,1,1},
	                        };// Right_Left 1/4 circle
const BYTE CornerLB[6][6] = {
							{1,2,2,2,2,2},
							{1,2,2,2,2,2},
							{0,1,2,2,2,2},
							{0,1,1,2,2,2},
							{0,0,1,1,2,2},
							{0,0,0,0,1,1},
	                         };// Right_Top 1/4 circle
const BYTE CornerRB[6][6] = {
							{2,2,2,2,2,1},
							{2,2,2,2,2,1},
							{2,2,2,2,1,0},
							{2,2,2,1,1,0},
							{2,2,1,1,0,0},
							{1,1,0,0,0,0},
                            };	 // Right_Bottom 1/4 circle
void DrawRectCorner( BTNAREA  Rect, int CornerRad,  BYTE updown __UNUSED, UINT8 step, BYTE Y_1, BYTE Y_2, UINT16 CbCr)
{
    //Note :
    //      "i" "j"  to find the correct pixel value in the array Corner[i][j]
    //    	"x0" "y0" is the real position of one pixel in the framebuf.
    //      To a array Corner[i][j], "i" adds in vertical while "j" add in horizonal.
    //     	In display, "y0" adds in vertical while "x0" adds in "horizonal".

    int  i=0,j=0, x0=0,y0=0;
    UINT8  RegionColor_Y[MAX_STEP];
    UINT16 Region[MAX_STEP];
    UINT8 StepCount =0;
    // to draw up or down.
    UINT16 LTColor_Y = 0,LTColor_CRCB = 0;//left ,top line use this color.
    UINT16 RBColor_Y = 0,RBColor_CRCB = 0;//right,bottom line use this color.
    int xStart=0,yStart=0,xLen =0,yLen=0;

    xStart = Rect.xStart;
    yStart = Rect.yStart;
    xLen = Rect.xSize;
    yLen = Rect.ySize;

    if (step)
    {// calulate the Y and Region width according to the given step.
#ifdef MONO_FSGUI //mono FS GUI, axel 2003-12-29 23:26
		Region[0] = xLen;
        RegionColor_Y[0] = 0x36;//PREVIEW_BKGROUND_Y;
#else
        for (i = 0; i < step; i++ )
        {
            Region[i] = i*(xLen / step);
		#ifdef INDIGO_STYLE_FSGUI
            RegionColor_Y[i] = Y_1 + i*(Y_2 - Y_1)/step;
		#else
            RegionColor_Y[i] = Y_1 + i*((Y_2 - Y_1)/step);
		#endif
        }
#endif
    }
    else //not draw step color. main for PREVIEW.
    {
        Region[0] = xLen;
	#ifdef INDIGO_STYLE_FSGUI
        RegionColor_Y[0] = Y_1;
	#else
		RegionColor_Y[0] = PREVIEW_BKGROUND_Y;
	#endif
    }

	// assign the corner color for INDIGO_STYLE_FSGUI
#ifdef INDIGO_STYLE_FSGUI
    LTColor_Y 		= ( RGB2Y (149,156,194));
    LTColor_CRCB 	= ( RGB2Cr(149,156,194) << 8 | RGB2Cb(149,156,194));
    RBColor_Y 		= ( RGB2Y (149,156,194));
    RBColor_CRCB 	= ( RGB2Cr(149,156,194) << 8 | RGB2Cb(149,156,194));
#else
    if (updown == 1)//down
    {
        LTColor_Y 		= BLACK_Y;
        LTColor_CRCB 	= BLACK_CRCB;
        RBColor_Y 		= WHITE_Y;
        RBColor_CRCB	= WHITE_CRCB;
    }
    else if(updown == 2)//up
    {
        LTColor_Y 		= WHITE_Y;
        LTColor_CRCB 	= WHITE_CRCB;
        RBColor_Y 		= BLACK_Y;
        RBColor_CRCB 	= BLACK_CRCB;
    }
    else//neither up nor down ,draw frame with the given paremeter"color_Y,color_CRCB"
    {
        LTColor_Y 		= WHITE_Y;
        LTColor_CRCB 	= WHITE_CRCB;
        RBColor_Y 		= WHITE_Y;
        RBColor_CRCB 	= WHITE_CRCB;
    }
#endif

    // draw x-majored
    for (x0 = 0; x0 < xLen; x0++)
    {
        // decide step-count
        if (step)
        {
            if((StepCount +1) < step)
        	{	
                if ((x0 >= Region[StepCount]) && (x0 < Region[StepCount + 1]))
	                StepCount++;
            }
        	else
            	StepCount = step -1;
        }
        else
            StepCount = 0;

		#define DDD_TRANSPARENT 0
		#define DDD_REGION      1
		#define DDD_LT          2
		#define DDD_RB          3

         for (y0 = 0; y0 < yLen; y0++)
        {
        	if((y0 < CornerRad+1) || (y0 > yLen-CornerRad-1))
        	{
	            int ccc = DDD_TRANSPARENT;
	            if ((y0<CornerRad) && (x0<CornerRad)) 
	        	{//Left Top
	            	i= y0;
	            	j= x0;
	            	if (CornerLT[i][j]==1)  	ccc=DDD_LT;
	                else if (CornerLT[i][j]==2) ccc=DDD_REGION;
	            }
	        	else if ((x0>=(xLen-CornerRad)) && (x0<xLen) && (y0<CornerRad)) 
	            {//Right_TOP
	            	i = y0;
	            	j = x0 - (xLen - CornerRad);
	            	if (CornerRT[i][j]==1) ccc=DDD_RB;
	            	else if (CornerRT[i][j]==2) ccc=DDD_REGION;
	            	else if (CornerRT[i][j]==3) ccc=DDD_LT;
	            }
	        	else if ((x0<CornerRad) && (y0>=(yLen-CornerRad))&& (y0<yLen))
	        	{//Left_Bottom
	            	j = x0;
	            	i = y0 - (yLen - CornerRad);
	            	if (CornerLB[i][j]==1) 		ccc=DDD_LT;
	                else if (CornerLB[i][j]==2) ccc=DDD_REGION;
	            }
	        	else if ((x0>=(xLen-CornerRad)) && (x0<xLen)&& (y0>=(yLen-CornerRad)) && (y0<yLen))
	        	{//Right_Bottom
	            	j = x0 - (xLen - CornerRad);
	            	i = y0 - (yLen - CornerRad);
	            	if (CornerRB[i][j]==1) 		ccc=DDD_RB;
	                else if (CornerRB[i][j]==2) ccc=DDD_REGION;
	        	}
	        	else
	                ccc = DDD_REGION;

	            if (ccc!=DDD_TRANSPARENT)
	            {
	                unsigned __y, __c;
	                switch (ccc) {
	                case DDD_LT:	__y=LTColor_Y; __c=LTColor_CRCB; break;
	                case DDD_RB:	__y=RBColor_Y; __c=RBColor_CRCB; break;
	                default:		__y=RegionColor_Y[StepCount];
	                 				__c=CbCr;
	                }
	                FSGUI_DrawPixel(xStart+x0, yStart+y0, __y, __c);
	            }
          	}
        } //end for y0
    }//end for x0

	//copy each line from the line above
	for(y0 = yStart+CornerRad ; y0 < yStart+yLen-CornerRad; y0++)
	{
		memcpy(Y_XY(xStart,y0),Y_XY(xStart,(y0-1)), xLen);
		memcpy(C_XY(xStart,y0),C_XY(xStart,(y0-1)), xLen);
	}

    //draw frame line
    #ifdef INDIGO_STYLE_FSGUI
    FSGUI_FillFrameBuf(     xStart+CornerRad,              yStart,(xLen - 2*CornerRad),                   1, FILE_LIST_UP_LINE_Y,FILE_LIST_UP_LINE_CbCr); //the top line
    FSGUI_FillFrameBuf(      (xStart+xLen-1),(yStart + CornerRad),                   1,(yLen - 2*CornerRad), FILE_LIST_DOWN_LINE_Y,FILE_LIST_DOWN_LINE_CbCr); //the right line
    FSGUI_FillFrameBuf((xStart + CornerRad ),     (yStart + yLen),(xLen - 2*CornerRad),                   1, FILE_LIST_RIGHT_LINE_Y,FILE_LIST_RIGHT_LINE_CbCr); //the bottom line
    FSGUI_FillFrameBuf(               xStart,(yStart + CornerRad),                   1,(yLen - 2*CornerRad), FILE_LIST_LEFT_LINE_Y,FILE_LIST_LEFT_LINE_CbCr); //the left line
	#else    
    FSGUI_FillFrameBuf(xStart+CornerRad, yStart, (xLen - 2*CornerRad), DEMENSION_SIZE, LTColor_Y, LTColor_CRCB); //the top line
    FSGUI_FillFrameBuf((xStart+xLen-DEMENSION_SIZE), (yStart + CornerRad), DEMENSION_SIZE, (yLen - 2*CornerRad), RBColor_Y, RBColor_CRCB);//the right line
    FSGUI_FillFrameBuf((xStart + CornerRad ), (yStart + yLen),(xLen - 2*CornerRad), DEMENSION_SIZE, RBColor_Y, RBColor_CRCB);//the bottom line
    FSGUI_FillFrameBuf(xStart, (yStart + CornerRad), DEMENSION_SIZE, (yLen - 2*CornerRad), LTColor_Y, LTColor_CRCB);//the left line
	#endif
}

#endif	//#if defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)

//
// ARROW
//
// FUNCTION
// DrawArrow(x, y, updown)
//
// updown=1 --> UP
// updown=x --> DOWN
//
#include "fsgui_icon_arrowx.inc"

void  DrawArrow(int xStart, int yStart, BYTE updown)
{
    FSGUI_DrawIcon(xStart, yStart, ICON_ArrowX, cluty_fsgui, clutc_fsgui, ((updown!=1) ? 0 : FSGUI_ICON_YFLIP));

    FSGUI_FillFrameBuf(xStart, yStart, ARROW_SIZE, DEMENSION_SIZE, WHITE_Y,WHITE_CRCB);  //top line
    FSGUI_FillFrameBuf(xStart, yStart, DEMENSION_SIZE, ARROW_SIZE, WHITE_Y,WHITE_CRCB);      //left line
    FSGUI_FillFrameBuf(xStart+ARROW_SIZE-DEMENSION_SIZE, yStart, DEMENSION_SIZE, ARROW_SIZE, BLACK_Y,BLACK_CRCB); //Right line
    FSGUI_FillFrameBuf(xStart, yStart+ARROW_SIZE, ARROW_SIZE, DEMENSION_SIZE, BLACK_Y,BLACK_CRCB);//bottom line
}


/*
 * FUNC: to show current dir which is playing.
 *
 * Creator: zhaoyanhua
 * date: 3-7-2 12:56
 */

void ShowCurrentDirPlaying()
{
    UINT16  dir_now = 0,dir_will = 0;

    //clear the last HL DirItem.
	//2006-06-02, mimitsai add for HD ui.
	ClearRectArea(Rect[DIR_RECT], DIR_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, DIR_AREA_BKGROUND_CRCB, FS_AREA_DIRITEM, fsnav_dir_HL);
	
	ShowDirItem(fsnav_dir_HL, iso9660_dir[pFsJpeg->dir_array[fsnav_dir_HL]].name);//resume the last HL

    //locate the positon of fsnav_dir_will and fsnav_dir_now  in the current type(MP3/JPEG/GAME).
    dir_will = antiAnchorDir(pFsJpeg->fsnav_dir_will);
    dir_now  =  antiAnchorDir(pFsJpeg->fsnav_dir_now);

    //In the same page ,show the HL.
    if ((dir_will / PER_PAGE) == (dir_now / PER_PAGE) )
    {
        fsnav_dir_HL = dir_now % PER_PAGE;
        ShowPlayFrame(fsArea[FS_AREA_DIRITEM].xStart-2, FS_DIRLIST_YSTART + fsnav_dir_HL * FS_FILELIST_YSTEP,HL_Width, HL_Heighth);//draw the current HL
	ShowDirItem(fsnav_dir_HL, iso9660_dir[pFsJpeg->dir_array[fsnav_dir_HL]].name);//resume the last HL
    }
}

/*
 * FUNC: to show current file which is playing
 *
 *  Creator: zhaoyanhua
 *  Date: 3-7-2 12:56
 */

void ShowCurrentFilePlaying()
{
	//2006-06-02, mimitsai add for HD ui.
    ClearRectArea(Rect[FILE_RECT], FILE_STEP, FILE_LIST_LEFT_Y, FILE_LIST_RIGHT_Y, FILE_AREA_BKGROUND_CRCB,FS_AREA_FILEITEM, fsnav_file_HL);

    FSShowFileItem(fsnav_file_HL, iso9660_file[pFsJpeg->file_array[fsnav_file_HL]].name);//resume the last HL

    //In the same page ,show the HL.
    if ((pFsJpeg->file_page_will) == (pFsJpeg->file_page_now) )
    {
        fsnav_file_HL = (pFsJpeg->file_current);
        ShowPlayFrame(fsArea[FS_AREA_FILEITEM].xStart-2, FS_DIRLIST_YSTART + fsnav_file_HL * FS_FILELIST_YSTEP,HL_Width, HL_Heighth);//draw the current HL
FSShowFileItem(fsnav_file_HL, iso9660_file[pFsJpeg->file_array[fsnav_file_HL]].name);//resume the last HL
    }
}

/*
 * FUNC : draw the frame line to show the current playing file or dir.
 *
 * zhaoyanhua 3-7-1 19:21
 */
void ShowPlayFrame(int x, int y,int len __UNUSED,int high __UNUSED)
{
#ifdef INDIGO_STYLE_FSGUI
		FSGUI_FillFrameBuf(x, y, HL_Width, HL_Heighth, SELECT_BG_COLOR_Y, SELECT_BG_COLOR_CbCr);
#else//#ifdef INDIGO_STYLE_FSGUI
    if((len!=0)&&(high!=0)) {
        #ifdef BEAUTIFUL_STYLE  //2005-5-16 9:48 zhongshan for beautiful different highlight 
         FSGUI_FillFrameBuf(x,y,len,DEMENSION_SIZE,YELLOW_Y,YELLOW_CRCB);
         FSGUI_FillFrameBuf(x,y,DEMENSION_SIZE, high,YELLOW_Y,YELLOW_CRCB);
        #else
        FSGUI_FillFrameBuf(x,y,len,DEMENSION_SIZE,BLACK_Y,BLACK_CRCB);
        FSGUI_FillFrameBuf(x,y,DEMENSION_SIZE, high,BLACK_Y,BLACK_CRCB);
        #endif
    }


    //draw light line
    if((len!=0)&&(high!=0)) {
     #ifdef BEAUTIFUL_STYLE//2005-5-16 9:48 zhongshan for beautiful different highlight
        FSGUI_FillFrameBuf(x+DEMENSION_SIZE,     y+high-DEMENSION_SIZE,len-DEMENSION_SIZE,DEMENSION_SIZE,YELLOW_Y,YELLOW_CRCB);
        FSGUI_FillFrameBuf(x+len-DEMENSION_SIZE, y+DEMENSION_SIZE,    DEMENSION_SIZE,  high-DEMENSION_SIZE,YELLOW_Y,YELLOW_CRCB);    
     #else
        FSGUI_FillFrameBuf(x+DEMENSION_SIZE,     y+high-DEMENSION_SIZE,len-DEMENSION_SIZE,DEMENSION_SIZE,WHITE_Y,WHITE_CRCB);
        FSGUI_FillFrameBuf(x+len-DEMENSION_SIZE, y+DEMENSION_SIZE,    DEMENSION_SIZE,  high-DEMENSION_SIZE,WHITE_Y,WHITE_CRCB);
     #endif
    }
#endif//#ifdef INDIGO_STYLE_FSGUI
   
}

//-------------------------------------------------------------------
// Refresh():
//      Refresh the GUI to display the real-time copying file process
// liweihua 2004-12-9 14:00
//-------------------------------------------------------------------
#ifdef FAT_FILE_MODE//lijd 2005-1-5 19:15
void Refresh(BYTE copy_process)
{
    if(copy_process<=100)
    {
        psprintf(linebuf, "COPYING FILE[%d%s]", copy_process,"%");   
        ShowWarning(linebuf);    
    }
    if(copy_process >= 100)
    {
        psprintf(linebuf, "COPYING FILE[100%s]", "%");
        ShowWarning(linebuf);
    }    
}
#elif defined(SUPPORT_MULTI_PARTITION)
void Refresh(BYTE copy_process)
{
    if(copy_process<=100)
    {
        psprintf(linebuf, "COPYING FILE[%d%s]", copy_process,"%");   
        FSGUI_UpdateInfoArea(linebuf);
        FSGUI_FillFrameBuf(49,237+1,(49+copy_process*2),4,HL_Y,HL_CRCB);    
    }
    if(copy_process >= 100)
    {
        psprintf(linebuf, "COPYING FILE[100%s]", "%");
        FSGUI_UpdateInfoArea(linebuf);
        FSGUI_FillFrameBuf(46,237,255,6,BK_GROUNDY,BK_CRCB);
    }
}
//#else
//void Refresh(BYTE copy_process)
//{}
#endif

#ifdef GPS_MP3_UI
void FSGUI_Displaytime()                        //suxin add,2005-09-21,for display play time
{
	static	BYTE show_time_ss_old;
    if((show_time_ss_old!=show_time_ss)&&(disp_time!=0))
    {
        psprintf(timebuf,"%02d:%02d",show_time_mm,show_time_ss);
		#ifdef USE_FSGUI_TO_PLAY_CD
		if(cd_type_loaded==CDDA)//frank.huang add 051018
		{
			FSGUI_DrawBackGround(fsArea[FS_AREA_TIME_INFO].xStart+INFO_STR_XSTART ,
			    MID_BAR_LOC,
			    fsArea[FS_AREA_TIME_INFO].xSize - INFO_STR_XSTART,
			    fsArea[FS_AREA_TIME_INFO].ySize,
			    LAY_PLAYING_BAR_3_2);
			FSGUI_ShowString(fsArea[FS_AREA_TIME_INFO].xStart+INFO_STR_XSTART,
			    MID_BAR_LOC+3,timebuf, 
			    FS_FONTCOLOR_PATH_Y, FS_FONTCOLOR_PATH_CrCb);
		}
		else
		#endif
		{
		FSGUI_DrawBackGround(fsArea[FS_AREA_TIME_INFO].xStart+INFO_STR_XSTART ,
		    fsArea[FS_AREA_TIME_INFO].yStart,
		    fsArea[FS_AREA_TIME_INFO].xSize - INFO_STR_XSTART,
		    fsArea[FS_AREA_TIME_INFO].ySize,
		    LAY_PLAYING_BAR_3_2);
		FSGUI_ShowString(fsArea[FS_AREA_TIME_INFO].xStart+INFO_STR_XSTART,
		    fsArea[FS_AREA_TIME_INFO].yStart+3,timebuf, 
		    FS_FONTCOLOR_PATH_Y, FS_FONTCOLOR_PATH_CrCb);
		}
		show_time_ss_old=show_time_ss;
   }

}

void FSGUI_DisplayState()		//suxin add,2005-09-21,for display playstate
{
	static	BYTE play_state_old;

	if(play_state_old!=play_state)
	{
		switch (play_state)
		{
			case VCD_STATE_NORMAL:
				psprintf(timebuf,"\x02");
				play_state_old = VCD_STATE_NORMAL;
				break;
			case VCD_STATE_PAUSE:
				psprintf(timebuf, "\x03"); 
				play_state_old = VCD_STATE_PAUSE;
				break;
			case VCD_STATE_FASTFORWARD:
				psprintf(timebuf, "\x08");
				play_state_old = VCD_STATE_FASTFORWARD;
				break;
			case VCD_STATE_FASTBACKWARD:
				psprintf(timebuf, "\x07");
				play_state_old = VCD_STATE_FASTBACKWARD;
				break;	
			case VCD_STATE_STOP:
				play_state_old = VCD_STATE_STOP;
				break;	
			default:
				psprintf(timebuf, "\x02"); 
				play_state_old = VCD_STATE_NORMAL;
				break;
		}
	#ifdef USE_FSGUI_TO_PLAY_CD//frank.huang add 051014
		if(cd_type_loaded==CDDA)
		{
		    FSGUI_DrawBackGround(fsArea[FS_AREA_PATHBACKGROUND].xStart + INFO_STR_XSTART,
			    MID_BAR_LOC,
			    35,
			    fsArea[FS_AREA_PATHBACKGROUND].ySize,
				    LAY_PLAYING_BAR_3_2);
		    FSGUI_ShowString(fsArea[FS_AREA_PATHINFO].xStart + 35,
		        MID_BAR_LOC+3, timebuf,
		        FS_FONTCOLOR_PATH_Y,FS_FONTCOLOR_PATH_CrCb);
		}
		else
	#endif
		{
		    FSGUI_DrawBackGround(fsArea[FS_AREA_PATHBACKGROUND].xStart + INFO_STR_XSTART,
			    fsArea[FS_AREA_PATHBACKGROUND].yStart,
			    35,
			    fsArea[FS_AREA_PATHBACKGROUND].ySize,
				    LAY_PLAYING_BAR_3_2);
		    FSGUI_ShowString(fsArea[FS_AREA_PATHINFO].xStart + 35,
		        fsArea[FS_AREA_PATHINFO].yStart, timebuf,
		        FS_FONTCOLOR_PATH_Y,FS_FONTCOLOR_PATH_CrCb);
		}
	}
}

#endif		//#ifdef GPS_MP3_UI

