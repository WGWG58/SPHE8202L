
#ifdef SUPPORT_MULTI_CHANNEL_5_BAND_EQ
	#define MAX_BAND        5
#else
	#define MAX_BAND        7
#endif

#ifdef OSD_BMP_SOUND
    #define EQ_XSTART_PIXEL	            286
    #define EQ_YSTART	                38
    #define EQ_CURSOR_CENTER_RECT       0x0c
    #define EQ_SELECTED_CENTER_RECT     0x0e
    #define EQ_CURSOR_OTHER_RECT        0x02
    #define EQ_SELECTED_OTHER_RECT      0x09
    #define BAND_XSTART_PIXEL	        156
    #define BAND_YSTART	                38
    #define BAND_TOP_SEL_RECT	        0x0c//yellow
    #define BAND_SELECTED_RECT          0x09
    #define BAND_OTHER_RECT             0x07
    #define RECT_XOFFSET_PIXEL	        18   //18/2
    #define RECT_WIDTH_PIXEL	        12	
    #define RECT_YOFFSET                6
    #define RECT_HEIGHT		            4
#else
  	#ifdef INDIGO_STYLE_OSDUI
		#define EQ_XSTART_PIXEL	            (228+(7-MAX_BAND)*16-5)
	    #define BAND_XSTART_PIXEL	        ((108+(7-MAX_BAND)*16)+50)
	    #define EQ_YSTART	                (60+50)
	    #define EQ_CURSOR_CENTER_RECT       7  //user set center rect
	    #define EQ_SELECTED_CENTER_RECT     11 //user set rect       
	    #define EQ_CURSOR_OTHER_RECT        3  //selected bar rect   
	    #define EQ_SELECTED_OTHER_RECT      3  //all unselected rect 
	    #define BAND_YSTART	                (60+50)
	    #define BAND_TOP_SEL_RECT           7//BR_RED_COLOR
	    #define BAND_SELECTED_RECT          bColorTab[j/4]
	    #define BAND_OTHER_RECT             GRAY_COLOR
  	#else
	    #define EQ_XSTART_PIXEL	            (228+(7-MAX_BAND)*16)
	    #define EQ_YSTART	                60
	    #define EQ_CURSOR_CENTER_RECT       DRK_GREEN_COLOR
	    #define EQ_SELECTED_CENTER_RECT     YELLOW_COLOR
	    #define EQ_CURSOR_OTHER_RECT        GRAY_COLOR
	    #define EQ_SELECTED_OTHER_RECT      GRAY_COLOR
	    #define BAND_XSTART_PIXEL	        (108+(7-MAX_BAND)*16)
	    #define BAND_YSTART	                60
	    #define BAND_TOP_SEL_RECT           BR_RED_COLOR
	    #define BAND_SELECTED_RECT          bColorTab[j/4]
	    #define BAND_OTHER_RECT             GRAY_COLOR
 	#endif
   #define RECT_XOFFSET_PIXEL	        16
    #define RECT_WIDTH_PIXEL	        12
    #define RECT_YOFFSET                4
    #define RECT_HEIGHT		            2
#endif

#define DISP_R              0
#define SURROUND_R          2
#ifdef OSD_BMP_SOUND
	#define EQ_R			4
	#define BAND_R			4
#elif defined(INDIGO_STYLE_OSDUI)
	#define EQ_R            2
	#define BAND_R          2
#else
	#define EQ_R            3
	#define BAND_R          3
#endif
	#define BAND_NO         5

#define SOUND_MAX_PAGE_ITEM   4
#define SOUND_MAX_ITEM_SEL    11
#define SOUND_MIN_ITEM_SEL    2
#ifdef SUPPORT_MULTI_CHANNEL_5_BAND_EQ
	#define MAX_BAND        5
#else
	#define MAX_BAND        7
#endif

#ifdef SEVEN_OPTIONS_IN_EQ
	#define MAX_MUSIC       7
#else
	#define MAX_MUSIC       5
#endif	

#ifdef INDIGO_STYLE_OSDUI
	#define SBGCOLOR	        6
	#define SANTIBGCOLOR            5
	#define SBLACKCOLOR             11
	#define SWHITECOLOR             2
	#define SELECT_BTN_COLOR		12
	#define SELECT_PAGE_FONT_COLOR  1
	#define HIGHLIGHT_COLOR 		7
	#define PAGE_BG					8
	#define BAND_BG_COLOR			1
#else
	#define SBGCOLOR	        6
	#define SANTIBGCOLOR            5
	#define SBLACKCOLOR             11
	#define SWHITECOLOR             2
	#define SELECT_BTN_COLOR		12
	#define SELECT_PAGE_FONT_COLOR  1
	#define HIGHLIGHT_COLOR 		7
	#define PAGE_BG					8
	#define BAND_BG_COLOR			11
#endif

#ifdef SETUP_COLOR_TYPE2           //3-10-16 8:37’≈”ÓP
	#ifdef NINTAUS_DVD
		#define SDISABLECOLOR	        14//0
	#else//#ifdef NINTAUS_DVD
		#ifdef  ALCO_PORTABLE_DVD_8202D_DVB
            #define SDISABLECOLOR	    3//0//shenyj modify for alco 2006/03/27(for 3d)		
        #else		
			#define SDISABLECOLOR	        0
        #endif		
	#endif//#ifdef NINTAUS_DVD
#else
	#define SDISABLECOLOR	        1
#endif

#define BUTTON_UP	        0
#define BUTTON_DOWN	        1


#define PAGE_WIDTH  (29*16)
#ifdef INDIGO_STYLE_OSDUI
#define SOUND_WID			(576-96)
#define SOUND_HEI			(280)
#define ICON_BG_WID			(576-96)
#define ICON_BG_HEI			(46)
#define CONTENT_BG_WID		(568-96)
#define CONTENT_BG_HEI		(210)
#define LINE_WID			(1)  //2
#define PAGE_WID			(137-24)
#endif

#ifdef OSD_BMP_SOUND
#define SRND_PAGE	0
#define EQ_PAGE	1
#define BAND_PAGE	2
#define KEY_PAGE	3
#define ITEM_NUM	6
#endif

#define SW_REGION1	0x10
#define SW_REGION2	0x20
#define SW_REGION3	0x30
#define SW_REGION_ANTI 	0x20
#define SW_REGION_OFF	0x10

#ifdef REMB_3DSOUND       //define it to remember 3D Sound yanlb 2004/07/06
#define Addr_REMB_3D 0xD0
#define SAVE_NUM 2
#endif

#ifdef SETUP_RESTORE_ALSO_RESTORE_3D
    #define SURR_OFF               2
    #define EQ_STANDARD            2
    #define EQ_USER_DEFAULT_VAL   13
#endif	


