//
// fsGUI.h
//
//      fs9660-GUI module internal include
//
// notes:
//
// history:
//  2002/02/26  : create
//

#ifndef __FS_GUI1_H
#define __FS_GUI1_H

//module global variables for internal reference
UINT16  Hl_x;
UINT16  Hl_y;
UINT16  Hl_len;
UINT16  Hl_high;
UINT16  Hl_x_btn;
UINT16  Hl_y_btn;
UINT16  Hl_len_btn;
UINT16  old_file_page;	        // index of current page
UINT16  old_dir_page;
UINT16  refresh_file_page;
UINT16  refresh_dir_page;
UINT16  refresh_dir_icon;

#ifdef INDIGO_STYLE_FSGUI
	#define FILE_LIST_UP_LINE_Y				(RGB2Y (158, 164, 201)) // DIR/FILE area frame outline color
	#define FILE_LIST_UP_LINE_CbCr			(RGB2Cr(158, 164, 201)<<8)|(RGB2Cb(158, 164, 201))
	#define FILE_LIST_DOWN_LINE_Y			(RGB2Y (149, 156, 194))
	#define FILE_LIST_DOWN_LINE_CbCr		(RGB2Cr(149, 156, 194)<<8)|(RGB2Cb(149, 156, 194))
	#define FILE_LIST_LEFT_LINE_Y			(RGB2Y (166, 171, 206))
	#define FILE_LIST_LEFT_LINE_CbCr		(RGB2Cr(166, 171, 206)<<8)|(RGB2Cb(166, 171, 206))
	#define FILE_LIST_RIGHT_LINE_Y			(RGB2Y (149, 156, 194))
	#define FILE_LIST_RIGHT_LINE_CbCr		(RGB2Cr(149, 156, 194)<<8)|(RGB2Cb(149, 156, 194))

	#define SCROLL_LINE_Y					(RGB2Y (132, 137, 181)) // scroll bar outline color
	#define SCROLL_LINE_CbCr				(RGB2Cr(132, 137, 181)<<8)|(RGB2Cb(132, 137, 181))

	#define HIGHLIGHT_COLOR_Y				(RGB2Y (249, 196,  23)) // Highlight rect color(yellow)
	#define HIGHLIGHT_COLOR_CbCr			(RGB2Cr(249, 196,  23)<<8)|(RGB2Cb(249, 196,  23))

	#define HIGHLIGHT_BG_COLOR_Y			0xa1 //(RGB2Y (152, 159, 198))// same as the bg color, clear the highlight outline
	#define HIGHLIGHT_BG_COLOR_CbCr			0x7994//(RGB2Cr(152, 159, 198)<<8)|(RGB2Cb(152, 159, 198))

	#define INFO_AREA_BG_Y					(RGB2Y (176, 180, 212)) // info area background color
	#define INFO_AREA_BG_CbCr				(RGB2Cr(176, 180, 212)<<8)|(RGB2Cb(176, 180, 212))

	#define SELECT_BG_COLOR_Y				(RGB2Y (105, 111, 163)) // selected dir/file rect color
	#define SELECT_BG_COLOR_CbCr			(RGB2Cr(105, 111, 163)<<8)|(RGB2Cb(105, 111, 163))
	#define TEXT_SELECT_COLODR_Y			(RGB2Y (198, 198, 198))
	#define TEXT_SELECT_COLODR_CbCr			(RGB2Cr(198, 198, 198)<<8)|(RGB2Cb(198, 198, 198))

	//for thumbnail drawing rect.
	#define THUMBNAIL_BG_UP_Y_1				RGB2Y (107,111,156)
	#define THUMBNAIL_BG_UP_Y_2				RGB2Y (123,127,167)
	#define THUMBNAIL_BG_UP_Cb_1			RGB2Cb(107,111,156)
	#define THUMBNAIL_BG_UP_Cb_2			RGB2Cb(123,127,167)
	#define THUMBNAIL_BG_UP_Cr_1			RGB2Cr(107,111,156)
	#define THUMBNAIL_BG_UP_Cr_2			RGB2Cr(123,127,167)
	
	#define THUMBNAIL_CONTENT_Y_1			RGB2Y ( 96,102,151)
	#define THUMBNAIL_CONTENT_Y_2			RGB2Y (160,165,204)
	#define THUMBNAIL_CONTENT_Cb_1			RGB2Cb( 96,102,151)
	#define THUMBNAIL_CONTENT_Cb_2			RGB2Cb(160,165,204)
	#define THUMBNAIL_CONTENT_Cr_1			RGB2Cr( 96,102,151)
	#define THUMBNAIL_CONTENT_Cr_2			RGB2Cr(160,165,204)

	#define THUMBNAIL_BG_DOWN_Y_1			RGB2Y (135,139,179)
	#define THUMBNAIL_BG_DOWN_Y_2			RGB2Y (116,122,166)
	#define THUMBNAIL_BG_DOWN_Cb_1			RGB2Cb(135,139,179)
	#define THUMBNAIL_BG_DOWN_Cb_2			RGB2Cb(116,122,166)
	#define THUMBNAIL_BG_DOWN_Cr_1			RGB2Cr(135,139,179)
	#define THUMBNAIL_BG_DOWN_Cr_2			RGB2Cr(116,122,166)
	
	#define THUMBNAIL_CONTENT_UP_RECT_Y_1	RGB2Y (129,134,178)
	#define THUMBNAIL_CONTENT_UP_RECT_Y_2	RGB2Y (158,159,187)
	#define THUMBNAIL_CONTENT_UP_RECT_Cb_1	RGB2Cb(129,134,178)
	#define THUMBNAIL_CONTENT_UP_RECT_Cb_2	RGB2Cb(158,159,187)
	#define THUMBNAIL_CONTENT_UP_RECT_Cr_1	RGB2Cr(129,134,178)
	#define THUMBNAIL_CONTENT_UP_RECT_Cr_2	RGB2Cr(158,159,187)

	#define THUMBNAIL_CONTENT_DOWN_RECT_Y_1		RGB2Y (167,170,196)
	#define THUMBNAIL_CONTENT_DOWN_RECT_Y_2		RGB2Y (184,186,207)
	#define THUMBNAIL_CONTENT_DOWN_RECT_Cb_1	RGB2Cb(167,170,196)
	#define THUMBNAIL_CONTENT_DOWN_RECT_Cb_2	RGB2Cb(184,186,207)
	#define THUMBNAIL_CONTENT_DOWN_RECT_Cr_1	RGB2Cr(167,170,196)
	#define THUMBNAIL_CONTENT_DOWN_RECT_Cr_2	RGB2Cr(184,186,207)
	

	#define JPEG_HELP_BG_Y					(RGB2Y (  89,  76, 129))
	#define JPEG_HELP_BG_CbCr				(RGB2Cr(  89,  76, 129)<<8)|(RGB2Cb(  89,  76, 129))
	#define JPEG_HELP_CONTENT_Y				(RGB2Y ( 159, 164, 202))	
	#define JPEG_HELP_CONTENT_CbCr			(RGB2Cr( 159, 164, 202)<<8)|(RGB2Cb( 159, 164, 202))
	#define JPEG_HELP_LINE_Y				(RGB2Y ( 153, 138, 131))	
	#define JPEG_HELP_LINE_CbCr				(RGB2Cr( 153, 138, 131)<<8)|(RGB2Cb( 153, 138, 131))
	#define JPEG_HELP_BG_FONT_Y				(RGB2Y ( 203, 203, 203))	
	#define JPEG_HELP_BG_FONT_CbCr			(RGB2Cr( 203, 203, 203)<<8)|(RGB2Cb( 203, 203, 203))
	#define JPEG_HELP_CONTENT_FONT_Y		(RGB2Y (  54,  69,  97))	
	#define JPEG_HELP_CONTENT_FONT_CbCr		(RGB2Cr(  54,  69,  97)<<8)|(RGB2Cb(  54,  69,  97))

	#define BG_WID							(FSGUI_SCREEN_WIDTH)//2006-06-02, mimitsai add for HD ui.
	#define BG_HEI							(FSGUI_SCREEN_HEIGHT)
	#define UP_HEI							( 90* NUMERATOE_Y/DENOMINATOR_Y)
	#define CONTENT_HEI						(130* NUMERATOE_Y/DENOMINATOR_Y)
	#define LINE_HEI						(  3* NUMERATOE_Y/DENOMINATOR_Y)
	#define DOWN_HEI						(BG_HEI-UP_HEI-CONTENT_HEI)	

	#define THUMBNAIL_BG_WID				720	
	#define THUMBNAIL_BG_HEI				576	
	#define THUMBNAIL_BG_UP_RECT_HEI		65
	
	#define THUMBNAIL_BG_DOWN_RECT_HEI		70
	#define THUMBNAIL_BG_MIDDLE_RECT_HEI	(THUMBNAIL_BG_HEI-THUMBNAIL_BG_UP_RECT_HEI-THUMBNAIL_BG_DOWN_RECT_HEI)

	#define CURSOR_X_GAP	0//6
	#define CURSOR_Y_GAP	0//6
	#define CURSOR_OUTER_LINE_COLOR_Y		(RGB2Y (249, 196,  23))
	#define CURSOR_OUTER_LINE_COLOR_CbCr	(RGB2Cr(249, 196,  23)<<8)|(RGB2Cb(249, 196,  23))
	#define BK_CURSOR_LINE_COLOR1_Y			(RGB2Y (147,153,194))
	#define BK_CURSOR_LINE_COLOR1_CbCr		(RGB2Cr(147,153,194)<<8)|(RGB2Cb(147,153,194))
	#define BK_CURSOR_LINE_COLOR2_Y			(RGB2Y (110,116,163))
	#define BK_CURSOR_LINE_COLOR2_CbCr		(RGB2Cr(110,116,163)<<8)|(RGB2Cb(110,116,163))
#endif

//2006-06-02, mimitsai add for HD ui.
#if defined(MP3_LARGE_GUI) || defined(INDIGO_STYLE_LARGE_FSGUI)
#define FSGUI_SCREEN_WIDTH			720
#define FSGUI_SCREEN_HEIGHT			480
#else
#define FSGUI_SCREEN_WIDTH			352
#define FSGUI_SCREEN_HEIGHT			288
#endif

#ifdef FS_BMP_GUI
    #ifdef GPS_MP3_UI//frank.huang 050915
        #define PER_PAGE			7    
    #else
        #define PER_PAGE			8
    #endif
#elif defined(INDIGO_STYLE_FSGUI)
	#define	PER_PAGE				9
#else
	#define	PER_PAGE				10
#endif

//2006-06-02, mimitsai add for HD ui.
#if defined(INDIGO_STYLE_LARGE_FSGUI) || defined(MP3_LARGE_GUI)
	#define NUMERATOE_X				720
	#define NUMERATOE_Y				480
	#define DENOMINATOR_X			352
	#define DENOMINATOR_Y			288
#else	
	#define NUMERATOE_X				1
	#define DENOMINATOR_X			1
	#define NUMERATOE_Y				1
	#define DENOMINATOR_Y			1
#endif


#ifdef PHILIPS_FSGUI//chenzhao20050613
	//black color
	#define BLACK_Y 				0xe0
	#define BLACK_CRCB				0x8080
	//white color
	#define WHITE_Y					0xe0
	#define WHITE_CRCB				0x8080
#else//PHILIPS_FSGUI
	//black color
	#define BLACK_Y					0x20
	#define BLACK_CRCB				0x8080
	//white color
	#define WHITE_Y					0xc0
	#define WHITE_CRCB				0x8080
#endif//PHILIPS_FSGUI


//background color
#if defined(BLUE_MP3_BK_GROUND)
	#define BK_GROUNDY				0x18     //blue corlor
	#define BK_GROUNDCRCB			0x6bb5  

#elif defined(MP3_BK_GROUND_GREEN) //li mao add 2004/4/27 
	#define BK_GROUNDY				0x40     //green corlor
	#define BK_GROUNDCRCB			0x5050

#elif defined(MP3_BK_GROUND_BLACK)              
	#define BK_GROUNDY				0x20     //black corlor.
	#define BK_GROUNDCRCB			0x8080

#elif defined(MP3_BK_GROUND_AQUA)   
   	#define BK_GROUNDY 				0x60     // aqua corlor
   	#define BK_GROUNDCRCB			0x7070

#elif defined(PHILIPS_FSGUI)   //chenzhao20050613
    #define BK_GROUNDY				0xe0
    #define BK_GROUNDCRCB			0x8080
    
#elif defined(INDIGO_STYLE_FSGUI)
    #define BK_GROUNDY				(RGB2Y(176, 180, 212))
    #define BK_GROUNDCRCB			(RGB2Cr(176, 180, 212)<<8)|(RGB2Cb(176, 180, 212))

#elif defined(NEW_MP3_GUI)
    #define BK_GROUNDY				(RGB2Y(108, 172, 206))
    #define BK_GROUNDCRCB			(RGB2Cr(108, 172, 206)<<8)|(RGB2Cb(108, 172, 206))
	#ifdef MINUS_VR_AUTH_PLAYBACK			//linrc 2006-3-29 13:48
		#ifdef SUPPORT_VR_MENU
	#define BUTTON_Y				(RGB2Y(108, 172, 206))
	#define BUTTON_CRCB				(RGB2Cr(108, 172, 206)<<8)|(RGB2Cb(108, 172, 206))
		#endif
	#endif

#elif defined(GPS_MP3_UI)
	#define BK_GROUNDY				0x24
	#define BK_GROUNDCRCB			0x7f81

#elif defined(THUMBNAIL_BMP_GUI)
	#define BK_GROUNDY				0x8f
	#define BK_GROUNDCRCB			0x738f

#else         
    #define BK_GROUNDY				0x80
    #define BK_GROUNDCRCB			0x7a85
#endif


#ifdef INDIGO_STYLE_FSGUI
	#define HL_Y					(RGB2Y (249, 196,  23))
	#define HL_CRCB                 (RGB2Cr(249, 196,  23)<<8)|(RGB2Cb(249, 196,  23))

#elif defined(NEW_MP3_GUI)
    #ifdef PHILIPS_FSGUI//chenzhao20050613
	#define HL_Y                    0xf3
	#define HL_CRCB                 0x8080
	#define BUTTOM_HL_Y             0xcd
	#define BUTTOM_HL_CRCB			0x7988
    #else
	#define HL_Y                   	0xa1
	#define HL_CRCB                 0xb266
    #endif

#elif defined(NEW_MP3_GUI)
	//#ifndef NEW_MP3_GUI
	//high line color
 	#ifdef BLUE_MP3_BK_GROUND
		#define HL_Y                0x18
 		#define HL_CRCB             0x6bb5
	#elif defined FS_BMP_GUI
	    #define HL_Y                (RGB2Y (253, 220, 7))
	    #define HL_CRCB             (RGB2Cr(253, 220, 7)<<8)|(RGB2Cb(253, 220, 7))
	    #define HL_SIDE_Y           (RGB2Y (186, 160, 0))
	    #define HL_SIDE_CRCB        (RGB2Cr(186, 160, 0)<<8)|(RGB2Cb(186, 160, 0))
	#else
		#define HL_Y                0x90
		#define HL_CRCB             0x7090
	#endif

#else
    #ifdef PHILIPS_FSGUI//chenzhao20050613
	#define HL_Y                    0xf3
	#define HL_CRCB                 0x8080
	#define BUTTOM_HL_Y             0xcd
	#define BUTTOM_HL_CRCB          0x7988
    #else
	#define HL_Y                    0xa1
	#define HL_CRCB                 0xb266
    #endif
#endif


#ifdef THUMBNAIL_BMP_GUI
	#define THUMBNAIL_BG_Y					0x7d//RGB2Y(106, 130, 150)
	#define THUMBNAIL_BG_CRCB				0x728e//(RGB2Cr( 106, 130, 150)<<8)|(RGB2Cb(106, 130, 150))

	#define THUMBNAIL_OUTER_FRAME_Y			0x9c//RGB2Y(189, 169, 0)
	#define THUMBNAIL_OUTER_FRAME_CRCB		0x9828//(RGB2Cr( 189, 169, 0)<<8)|(RGB2Cb(189, 169, 0))

	#define THUMBNAIL_MID_FRAME_Y			0xd0//RGB2Y(251, 226, 0)
	#define THUMBNAIL_MID_FRAME_CRCB		0x9f0b//(RGB2Cr( 251, 226, 0)<<8)|(RGB2Cb(251, 226, 0))

	#define THUMBNAIL_INNER_FRAME_Y			0x9c//RGB2Y(189, 169, 0)
	#define THUMBNAIL_INNER_FRAME_CRCB		0x9828//(RGB2Cr( 189, 169, 0)<<8)|(RGB2Cb(189, 169, 0))
#endif


#ifdef PHILIPS_FSGUI//chenzhao20050613
	//no longer means yellow,means Scroll front color,and icon light color
	#define YELLOW_Y                        0xcd
	#define YELLOW_CRCB                     0x7988

	//no longer means red,means icon black color
	#define RED_Y                           0x71
	#define RED_CRCB                        0x7987
#else//PHILIPS_FSGUI
	//yellow
	#define YELLOW_Y                        0xd0
	#define YELLOW_CRCB                     0x9050
	//red
	#if defined(ALCO_DVD_UI)
	#define RED_Y                           0x20
	#define RED_CRCB                        0x7090
	#else//#if defined(ALCO_DVD_UI)
	#define RED_Y                           0x41
	#define RED_CRCB                        0xd464
	#endif//#if defined(ALCO_DVD_UI)
#endif//PHILIPS_FSGUI

#define FILE_LIST_LEFT_Y					(RGB2Y (149, 152, 193)) // DIR/FILE list left bg color
#define FILE_LIST_RIGHT_Y					(RGB2Y (187, 192, 221)) // DIR/FILE list right bg color

#ifdef INDIGO_STYLE_FSGUI
	#define THUMBNAIL_OUTLINE_FRAME_COLOR_Y 	HIGHLIGHT_COLOR_Y
	#define THUMBNAIL_OUTLINE_FRAME_COLOR_CbCr 	HIGHLIGHT_COLOR_CbCr
	#define THUMBNAIL_BG_COLOR_Y				SCROLL_LINE_Y
	#define THUMBNAIL_BG_COLOR_CbCr				SCROLL_LINE_CbCr
	#define THUMBNAIL_FONT_COLOR_Y				0xea
	#define THUMBNAIL_FONT_COLOR_CbCr			0x8278
#else
	#define THUMBNAIL_OUTLINE_FRAME_COLOR_Y 	YELLOW_Y
	#define THUMBNAIL_OUTLINE_FRAME_COLOR_CbCr 	YELLOW_CRCB
	#define THUMBNAIL_BG_COLOR_Y				BK_GROUNDY
	#define THUMBNAIL_BG_COLOR_CbCr				BK_GROUNDCRCB
#endif


#ifdef PHILIPS_FSGUI//chenzhao20050613
	#define FS_FONTCOLOR_FILE_HL_Y             0x66
	#define FS_FONTCOLOR_FILE_HL_CrCb          0x3ab2
#endif

#define FS_FONTCOLOR_FILE_Y1             		0xea
#define FS_FONTCOLOR_FILE_CrCb1          		0x8278


#ifdef THUMBNAIL_BMP_GUI
	#define FS_FONTCOLOR_FILE_Y             	0xde
	#define FS_FONTCOLOR_FILE_CrCb          	0x8080
	#define FS_FONTCOLOR_THUMBNAIL_TITLE_Y 		0x3b//RGB2Y(49, 62, 68)
	#define FS_FONTCOLOR_THUMBNAIL_TITLE_CrCb 	0x7985//(RGB2Cr( 49, 62, 68)<<8)|(RGB2Cb(49, 62, 68))

#elif defined(PHILIPS_FSGUI)//chenzhao20050613
	#define FS_FONTCOLOR_FILE_Y             	0xf2
	#define FS_FONTCOLOR_FILE_CrCb          	0x8080

#elif defined(INDIGO_STYLE_FSGUI)
	#define FS_FONTCOLOR_FILE_Y           		(RGB2Y ( 54, 69, 97))// general font color
	#define FS_FONTCOLOR_FILE_CrCb        		(RGB2Cr( 54, 69, 97)<<8)|(RGB2Cb( 54, 69, 97))

#else
	#define FS_FONTCOLOR_FILE_Y             	0xea
	#define FS_FONTCOLOR_FILE_CrCb          	0x8278
#endif


#ifdef FS_SLECTE_FONT_COLOR //qinhua,2006-3-14 03:09ÏÂÎç
	#define FS_FONTCOLOR_FILE_Y_SL            	0x20  
	#define FS_FONTCOLOR_FILE_CrCb_SL          	0x8080
#endif 


#ifdef FS_BMP_GUI
	#ifdef	GPS_MP3_UI//frank.huang 050923
	#define FS_FONTCOLOR_PATH_Y             	(RGB2Y(0, 0, 0))
	#define FS_FONTCOLOR_PATH_CrCb          	(RGB2Cr( 0, 0, 0)<<8)|(RGB2Cb(0, 0, 0))
	#define FS_FONTCOLOR_TITLE_Y		    	0x08
	#define FS_FONTCOLOR_TITLE_CrCb	        	0x7aa3
	#else
	#define FS_FONTCOLOR_PATH_Y             	0xbd
	#define FS_FONTCOLOR_PATH_CrCb          	0xae15
	#define FS_FONTCOLOR_TITLE_Y		    	0x08
	#define FS_FONTCOLOR_TITLE_CrCb	        	0x7aa3
    #endif
#endif

#define FS_FONTCOLOR_PAGE_UY            		0x24
#define FS_FONTCOLOR_PAGE_UCrCb         		0x7ba6
#define FS_FONTCOLOR_PAGE_DY            		0x29
#define FS_FONTCOLOR_PAGE_DCrCb         		0xaf7c

///////////////////////////////////////////////////////////////////
//define main menu look-and-feel style
//Notes : to avoid blinking (when white/black line displaying in n/n+1 line, with interlace mode)
//        SHADOW_WID , LIGHT_WID should >=2
//        X1, Y1, Y3 should be 2*n
#define SHADOW_WID                      2
#define LIGHT_WID                       2

#if defined(FS_BMP_GUI)

    #define	X1                              170
    #define	Y1                              60
    #define	Y3                              232
    #define FS_FILEICON_XSTART				437            //file ICON start-x
    #define FS_FILEICON_ySTART				437            //file ICON start-x
    #define	FS_FILELIST_XSTART				130             //file string start-x
    #define	FS_FILELIST_YSTART				150              //file string start-y
    #define	FS_DIRLIST_XSTART				130             //dir string start-x
    #define	FS_DIRLIST_YSTART				150              //dir string start-y
    
    #define FS_FILELIST_YSTEP				32              //file(dir) list item height
    
    #define	FS_DIRICON_XLEN                 35
    #define	FS_FILEICON_XLEN                FS_DIRICON_XLEN
    #define	FS_DIRITEM_XLEN                 252+2 //199+40//190
    #define	FS_FILEITEM_XLEN                FS_DIRITEM_XLEN
    
	#ifdef	GPS_MP3_UI//frank.huang 050923
	#define	FS_DIRSCROLLLEN_XSTART          328//65+264
	#define	FS_DIESCROLLLEN_YSTART          171  
	#define	FS_DIRSCROLLLEN_XSIZE           22
	#define	FS_DIRSCROLLLEN_YSIZE           180//382-171
	#else
    #define	FS_DIRSCROLLLEN_XSTART          329//65+264
    #define	FS_DIESCROLLLEN_YSTART          171  
    #define	FS_DIRSCROLLLEN_XSIZE           22
    #define	FS_DIRSCROLLLEN_YSIZE           211//382-171
	#endif//#ifdef	GPS_MP3_UI

#elif defined(MP3_LARGE_GUI)
    #define X1                             	320
    #define Y1                              90
    #define Y3                              232
    #define FS_DIRLIST_YSTART               100             //dir string start-y
    #define FS_DIRLIST_XSTART               120             //dir string start-x
    #define FS_FILELIST_YSTEP               28             	//file(dir) list item height
    #define FS_FILEICON_XSTART              380             //file ICON start-x

#elif defined(INDIGO_STYLE_FSGUI)
	#define FS_DIRICON_XSTART				(32 * NUMERATOE_X/DENOMINATOR_X)
	#define	FS_DIRLIST_XSTART				(54 * NUMERATOE_X/DENOMINATOR_X)
    #define	FS_DIRLIST_YSTART				(79 * NUMERATOE_Y/DENOMINATOR_Y)

	#define FS_FILEICON_XSTART				(185* NUMERATOE_X/DENOMINATOR_X)
    #define FS_FILELIST_XSTART				(207* NUMERATOE_X/DENOMINATOR_X)

	#define FS_DIRSCROLL_XSTART				(170* NUMERATOE_X/DENOMINATOR_X)
	#define FS_FILESCROLL_XSTART			(324* NUMERATOE_X/DENOMINATOR_X)
    #define FS_FILELIST_YSTEP				(16 * NUMERATOE_Y/DENOMINATOR_Y)
#else
    #define	X1                              170
    #define	Y1                              60
    #define	Y3                              232
    #define	FS_DIRLIST_YSTART				70              //dir string start-y
    #define	FS_DIRLIST_XSTART				60              //dir string start-x
    #ifdef SUPPORT_UNICODE_FONT ///////////yangli mod for unicode UI change bigger2005-9-29
        #define FS_FILELIST_YSTEP			17            //file(dir) list item height
    #else
        #define FS_FILELIST_YSTEP			16
    #endif
        
    #define FS_FILEICON_XSTART				180             //file ICON start-x

    #if defined(FAT_FILE_MODE) || defined(FILE_MODE_WRITE)//liweihua 2004-10-9 22:28//sunzhh 2004-12-25
    #define	FS_DIRSCROLLLEN_XSTART          329//65+264
    #define	FS_DIESCROLLLEN_YSTART          171  
    #define	FS_DIRSCROLLLEN_XSIZE           22
    #define	FS_DIRSCROLLLEN_YSIZE           211//382-171
    #endif//#ifdef FAT_FILE_MODE

#endif//#if defined(FS_BMP_GUI)

#ifdef INDIGO_STYLE_FSGUI
	#ifdef INDIGO_STYLE_LARGE_FSGUI
	#define BTN_XOFFSET_FROM_OUTLINE		(14)
	#define BTN_YOFFSET_FROM_OUTLINE		(1)
	#else
	#define BTN_XOFFSET_FROM_OUTLINE		(15)		
	#define BTN_YOFFSET_FROM_OUTLINE		(6)
	#endif
#endif

#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)//defintion of gamepad buttons
	#define FS_GAMEPAD_RIGHT                0x0001
	#define FS_GAMEPAD_LEFT                 0x0002
	#define FS_GAMEPAD_DOWN                 0x0004
	#define FS_GAMEPAD_UP                   0x0008
	#define FS_GAMEPAD_START                0x0010
	#define FS_GAMEPAD_SELECT               0x0020
#endif


enum
{
	CNT_AREA_FILE 		= 0,
	CNT_AREA_DIR		= 1,
	CNT_AREA_MP3BUTTON	= 2,
	CNT_AREA_JPEGBUTTON	= 3,
	#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
	CNT_AREA_GAMEBUTTON,
	#endif

	#ifdef SUPPORT_FILE_SYSTEM_MODE
	CNT_AREA_OTHERBUTTON,
	#endif

	#ifdef SUPPORT_MIDI
	CNT_AREA_MIDIBUTTON,
	#endif

	#ifdef MINUS_VR_AUTH_PLAYBACK
	CNT_AREA_VR_PG,
	#endif

	#ifdef SUPPORT_PLAYLIST
    CNT_AREA_PLAYLISTBUTTON,
	#endif 

	#ifdef SUPPORT_MULTI_PARTITION
    CNT_AREA_MULTI_PART,
    	#ifdef FAT_FILE_MODE
    CNT_AREA_DISK,
    CNT_AREA_CARD,
    CNT_AREA_WARNING,
    	#endif
	#endif

	#ifdef FILE_MODE_WRITE      //sunzhh 2004-12-22 10:30
    CNT_AREA_SRCE,    
    CNT_AREA_DEST,
    CNT_AREA_COPYBUTTON,
    CNT_AREA_DELETEBUTTON,
    CNT_AREA_NEWBUTTON,
    CNT_AREA_RENAMEBUTTON,
    CNT_AREA_FORMATBUTTON,
    CNT_AREA_CAPACITYBUTTON,
	#endif    

	#ifdef INDIGO_STYLE_FSGUI
	CNT_TAB_MP3BUTTON,
	CNT_TAB_JPEGBUTTON,
		#ifdef SUPPORT_NESGAME
	CNT_TAB_GAMEBUTTON,
		#endif
	CNT_TAB_OTHERBUTTON,
	#endif
};


enum
{
	FS_AREA_BACKGROUND 	= 0,
	FS_AREA_DIRICON		= 1,
	FS_AREA_DIRITEM		= 2,
	FS_AREA_FILEICON	= 3,
	FS_AREA_FILEITEM	= 4,
	// 2006-03-16, mimitsai add
	#ifdef DIR_SCROLL_BAR
	FS_DIR_AREA_SLOT		,
	FS_DIR_AREA_MOVEBAR		,
	#endif	
	
	FS_AREA_SLOT		,
	FS_AREA_MOVEBAR		,
	FS_AREA_PATHINFO	,
	FS_AREA_PREVIEWJPG	,

	#if !defined (FS_BMP_GUI)
	FS_AREA_BUTTON		,

    	#ifdef FAT_FILE_MODE
    FS_AREA_DISKICON ,
    FS_AREA_DISKLIST ,
    FS_AREA_WARNING ,
    FS_AREA_DIR_SLOT ,
    FS_AREA_DIR_MOVEBAR ,
	    #endif      

		#ifdef FILE_MODE_WRITE      //sunzhh 20041225
    FS_AREA_DISKICON ,
    FS_AREA_DISKLIST ,
    FS_AREA_WARNING ,
    FS_AREA_DIR_SLOT ,
    FS_AREA_DIR_MOVEBAR ,
	    #endif      
	#else
    FS_AREA_BUTTONTITLE ,
    FS_AREA_BUTTONTITLE_BACKGROUND,
    FS_AREA_PATHBACKGROUND,
    FS_AREA_BUTTONBACKGROUND,
    FS_AREA_DIR_SLOT,
    FS_AREA_DIR_MOVEBAR,     
    	#ifdef	GPS_MP3_UI//frank.huang 050923
	FS_AREA_ARTIST_INFO,
	FS_AREA_TIME_INFO,
		#endif
	#endif

	#ifdef INDIGO_STYLE_FSGUI
	FS_AREA_MP3_BUTTON,
	FS_AREA_JPG_BUTTON,
	FS_AREA_OTHER_BUTTON,
		#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
	FS_AREA_GAME_BUTTON,
		#endif	

	#endif
};

typedef struct
{
	UINT16  xStart;
	UINT16  yStart;
	UINT16  xSize;
	UINT16  ySize;
} BTNAREA;

// 2006-03-10, mimitsai add
typedef struct
{
	UINT8 Y;
	UINT8 Cb;
	UINT8 Cr;
} YUV_COLOR;

// 2006-03-10, mimitsai add for draw variant color rec.
enum
{
	VERTICAL_SHADING,
	HORIZONTAL_SHADING,
	DIAGONAL_SHADING,
};

//============RGB -> YCbCr================================================
#define RGB2Y(r,g,b)  (((71*(r) + 141*g + 27*b + 0x1000)&0xFF00)>>8)
#define RGB2Cr(r,g,b) (((127*(r)-106*(g)-21*(b)+0x8000)&0xFF00)>>8)
#define RGB2Cb(r,g,b) ((((-43)*(r)-85*(g)+127*(b)+0x8000)>>8)&0xFF)

//========================================================================
#if defined(NEW_MP3_GUI)||defined(MP3_TXT_DISPLAY) || defined (FS_BMP_GUI) || defined (INDIGO_STYLE_FSGUI)
	#define MP3_LYRICS_IN_DIR_AREA    	1
	#define DIR_LIST_IN_DIR_AREA        0
	#define JPEG_PREVIEW_IN_DIR_AREA    1
#endif
//========================================================================

#if defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)
    #ifdef PHILIPS_FSGUI//chenzhao20050613
    //===============fill color================================================
    //preview area . when preview JPEG,draw the background with following colors.
    #define PREVIEW_BKGROUND_CRCB           0x768a
    #define PREVIEW_BKGROUND_Y               0x94
    //
    #define DIR_AREA_BKGROUND_CRCB          0x768a
    #define FILE_AREA_BKGROUND_CRCB         0x768a
    //whole background color
    #define BK_CRCB                         0x8080
    
    #else//PHILIPS_FSGUI
	//===============fill color================================================

	#ifdef INDIGO_STYLE_FSGUI
	#define DIR_AREA_BKGROUND_CRCB   		(RGB2Cr(149, 152,  193)<<8)|(RGB2Cb(149, 152,  193))
	#define FILE_AREA_BKGROUND_CRCB  		(DIR_AREA_BKGROUND_CRCB)
	#define PREVIEW_BKGROUND_CRCB    		(DIR_AREA_BKGROUND_CRCB)
	#define PREVIEW_BKGROUND_Y              (0x80)
	#else
	#define DIR_AREA_BKGROUND_CRCB   		(RGB2Cr(52, 172,193)<<8)|(RGB2Cb(52, 172, 193))
	#define FILE_AREA_BKGROUND_CRCB  		(DIR_AREA_BKGROUND_CRCB)  //(RGB2Cr(52, 172, 193)<<8)|(RGB2Cb(52, 172, 193))
	#define PREVIEW_BKGROUND_CRCB    		(RGB2Cr( 66, 181, 181)<<8)|(RGB2Cb(66, 181, 181))//preview area . when preview JPEG,draw the background with following colors.
	#define PREVIEW_BKGROUND_Y              (0x80)
	#endif

	//whole background color
	#define BK_CRCB							(RGB2Cr(129,187,218)<<8)|(RGB2Cb(129,187,218))
    #endif//PHILIPS_FSGUI

	//================rectangle AREA index====================================

	#define PATH_RECT  				0
	#define BK_RECT    				1
	#define DIR_RECT   				2
	#define FILE_RECT  				3
	#define PREVIEW_RECT 			4
	#define SHOW_JPEG_RECT 			5

	#ifdef SUPPORT_MULTI_PARTITION
	#define PARTITION_RECT  		SHOW_JPEG_RECT+1
	#else
	#define PARTITION_RECT  		SHOW_JPEG_RECT
	#endif
	
	#ifdef FAT_FILE_MODE
	#define DISK_TITILE_RECT    	PARTITION_RECT+1
	#define CARD_TITLE_RECT     	PARTITION_RECT+2
	#define INFO_RECT           	PARTITION_RECT+3
	#define DISK_ICON_RECT      	PARTITION_RECT+4
	#define CARD_ICON_RECT      	PARTITION_RECT+5
	#define DISK_ITEM_RECT      	PARTITION_RECT+6
	#endif

	#ifdef FILE_MODE_WRITE             //sunzhh add 20041225
	#define SRCE_TITILE_RECT    	6
	#define DEST_TITLE_RECT     	7
	#define INFO_RECT           	8
	#endif

	//=============FILE  AREA================================================
	#ifdef PHILIPS_FSGUI//chenzhao20050613
	#define FILE_STEP             	0
	#elif defined(INDIGO_STYLE_FSGUI)
	#define FILE_STEP             	20
	#else
	#define FILE_STEP             	40
	#endif

	#ifdef MP3_LARGE_GUI	//Maoyong 2004.04.15
	#define FILE_AREA_XSTART      	366//FS_FILEICON_XSTART-2
	#define FILE_AREA_YSTART      	65 //In fact no use	
	#define FILE_AREA_XLEN        	295//JUST AS RECT FILE WIDTH
	#define FILE_AREA_YLEN        	300//JUST AS RECT FILE HEIGHT	
	#else //#ifdef MP3_LARGE_GUI	//Maoyong 2004.04.15

	#define FILE_AREA_XSTART   	  	178//FS_FILEICON_XSTART-2	
	#define FILE_AREA_YSTART      	65 //In fact no use
	#define FILE_AREA_YLEN        	170

	#define FILE_AREA_XLEN        	(150* NUMERATOE_X/DENOMINATOR_X)	//2006-06-02, mimitsai add for HD ui.

	#endif //#ifdef MP3_LARGE_GUI	//Maoyong 2004.04.15

	//=================others pareameter=====================================
	//DIR AREA 
	#ifdef PHILIPS_FSGUI//chenzhao20050613
	#define DIR_STEP              	0
	#else
	#define DIR_STEP              	40
	#endif

	#ifdef MP3_LARGE_GUI
		#define ITEM_MAX_WIDTH		  	216
	#elif defined(INDIGO_STYLE_FSGUI)//2006-06-02, mimitsai add for HD ui.
		#ifdef DIR_SCROLL_BAR
			#define ITEM_MAX_WIDTH		(114*NUMERATOE_X/DENOMINATOR_X)
		#else
    		#define ITEM_MAX_WIDTH		(118*NUMERATOE_X/DENOMINATOR_X)
	    #endif
	#else
		#ifndef READ_FAT_LONGNAME
			#ifdef DIR_SCROLL_BAR
			#define ITEM_MAX_WIDTH		112  //max item width to clear.
			#else
        	#define ITEM_MAX_WIDTH		118  //max item width to clear.
		    #endif
        #else//READ_FAT_LONGNAME
            #ifdef SUPPORT_FAT_LFN
            #define ITEM_MAX_WIDTH        112
		#else
			#define ITEM_MAX_WIDTH		250
		#endif
        #endif//READ_FAT_LONGNAME
	#endif	//MP3_LARGE_GUI
	

	// for scroll arrow.
	#if defined(MP3_LARGE_GUI) || defined(INDIGO_STYLE_LARGE_FSGUI)//2006-06-02, mimitsai add for HD ui.	//Maoyong 2004.04.15
		#define  ARROW_SIZE   	20 //when change this value,must change the array ArrowUP[] and ArrowDOWN[] accordingly.
	#else
		#define  ARROW_SIZE   	10 //when change this value,must change the array ArrowUP[] and ArrowDOWN[] accordingly.
	#endif

	//for rectangle corner
	//NOTE : when change this value,must change the array CornerLB[] CornerLT[],CornerRB[],CornerRT[] accordingly.
	#define  CORNER_RAD   		6 

	//max step
	#if defined(INDIGO_STYLE_FSGUI) || defined(MP3_LARGE_GUI)
	#define MAX_STEP   			120
	#else
	#define MAX_STEP   			70
	#endif

#endif //#if defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)


#if defined(MP3_LARGE_GUI) || defined(INDIGO_STYLE_LARGE_FSGUI)//2006-06-02, mimitsai add for HD ui.
	#define DEMENSION_SIZE  	2
#else
	#define DEMENSION_SIZE  	1
#endif


#if defined(NEW_MP3_GUI)
    #ifdef MP3_LARGE_GUI
    #define HL_RECT_HEIGHTH     24
    #else
    #define HL_RECT_HEIGHTH     12
    #endif

#elif defined(INDIGO_STYLE_FSGUI)
    #define HL_RECT_HEIGHTH     (12* NUMERATOE_X/DENOMINATOR_X) //2006-06-02, mimitsai add for HD ui.

#elif defined(FS_BMP_GUI)
    #define HL_RECT_HEIGHTH     28//32
#endif


#ifdef FS_BMP_GUI //2006-06-02, mimitsai modify.
	UINT16 dir_count_page;
	UINT16 dir_scroll_step;
	UINT16 dir_scroll_len;
	BYTE help_stop_flag;//when help mode,show help page end,no show "stop"

	#define BG_XSTART           	0
	#define BG_YSTART          		0
	#define BG_XREPEAT          	720
	#define BG_YREPEAT          	1

	#define DIR_AREA_XSTART			65//DIR AREA X START 
	#define DIR_AREA_YSTART			137 //DIR AREA Y START    

	#define RECT_BG_BMP_WIDTH		1   //need repeat bmp width
	#define RECT_BG_BMP_HEIGHT		279 //need repeat bmp height

	//length of dir background and file background in x diction.
	#define LEN_DIRFILE				307

	#define RECTLINE_Y				(RGB2Y(136,150,255))
	#define RECTLINE_CRCB			(RGB2Cr(136,150,255) << 8 | RGB2Cb(136,150,255))        

	#define RECTSCROLL_LINE_Y 		(RGB2Y(81,94,186))
	#define RECTSCROLL_LINE_CRCB	(RGB2Cr(81,94,186) << 8 | RGB2Cb(81,94,186))
	#define BLUE_Y       			(RGB2Y(2,63,216))
	#define BLUE_CRCB    			(RGB2Cr(2,63,216) << 8 | RGB2Cb(2,63,216))
	#define SCROLL_Y        		(RGB2Y(83,128,226))
	#define SCROLL_CRCB     		(RGB2Cr(83,128,226) << 8 | RGB2Cb(83,128,226))
	
	#define UPARROW_Y       		(RGB2Y(81,94,186))
	#define UPARROW_CRCB    		(RGB2Cr(81,94,186) << 8 | RGB2Cb(81,94,186))

	#define DOWNARROW_Y     		(RGB2Y(83,128,226))
	#define DOWNARROW_CRCB  		(RGB2Cr(83,128,226) << 8 | RGB2Cb(83,128,226))

	//current playing file /dir background color
	#define PLAYING_Y 				(RGB2Y(165, 176, 255))
	#define PLAYING_CRCB			(RGB2Cr( 165, 176, 255)<<8)|(RGB2Cb(165, 176, 255))
	#define PLAYING_SIDE_Y			(RGB2Y(124, 141, 177))
	#define PLAYING_SIDE_CRCB		(RGB2Cr(124, 141, 177)<<8)|(RGB2Cb(124, 141, 177))

    #ifdef	GPS_MP3_UI//frank.huang 050923
	#define DIR_AREA_XLEN			290//JUST AS RECT DIR WIDTH
	#define DIR_AREA_YLEN			32*PER_PAGE//279//JUST AS RECT DIR HEIGHT
	
	#define FILE_AREA_XSTART		DIR_AREA_XSTART + LEN_DIRFILE//FILE AREA X START 
	#define FILE_AREA_YSTART		137 //DILE AREA X START 
	#define FILE_AREA_XLEN			290//JUST AS RECT DILE WIDTH
	#define FILE_AREA_YLEN			32*PER_PAGE//279//JUST AS RECT FILE HEIGHT
	#else//#ifdef	GPS_MP3_UI
	#define DIR_AREA_XLEN			261//JUST AS RECT DIR WIDTH
	#define DIR_AREA_YLEN			279//JUST AS RECT DIR HEIGHT

	#define FILE_AREA_XSTART		DIR_AREA_XSTART + LEN_DIRFILE//FILE AREA X START 
	#define FILE_AREA_YSTART		137 //DILE AREA X START 
	#define FILE_AREA_XLEN			261//JUST AS RECT DILE WIDTH
	#define FILE_AREA_YLEN			279//JUST AS RECT FILE HEIGHT
	#endif//#ifdef	GPS_MP3_UI
#endif//FS_BMP_GUI

//info area x offset definition         //Maoyong 2004-7-6 23:18
#ifdef NEW_MP3_GUI
    #define INFO_X_OFFSET   34
#else
    #ifdef HANYANG_FS_LONGNAME
    #define INFO_X_OFFSET   0
    #else
    #define INFO_X_OFFSET   (26*NUMERATOE_X/DENOMINATOR_X)//2006-06-02, mimitsai add for HD ui.
    #endif
#endif

//----------------------------------------------
#endif//#ifndef __FS_GUI1_H
