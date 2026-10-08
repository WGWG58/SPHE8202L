#include "osd_palette.h"

/************************************************************
Setup
************************************************************/

#if defined(ALCO_MODIFY_PAL_OSD)||defined(SETUP_PAL_ADJUST_IN_INDIGO_UI)
#ifdef ALCO_MODIFY_PAL_OSD
const   _t_osd_hdr osd_setup_pal[] = 
{  
    {35*8*2, 12*SETUP_BTN_HEIGHT, 38, 24+22, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},
};
		#endif

		#ifdef SETUP_PAL_ADJUST_IN_INDIGO_UI   // lxg 2006-8-11 02:09  Add for auto adjust setup position when set to PAL ,with INDIGO_STYLE_OSDUI
const   _t_osd_hdr osd_setup_pal[] = 
{
    {576, 360, 33, 53, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},
};
#endif
#endif

#ifdef INDIGO_STYLE_OSDUI // mimitsai add for new ui 2005.11.01
const   _t_osd_hdr osd_setup[] = {
    {576, 360, 33, 24, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},
};
  
#else
const   _t_osd_hdr osd_setup[] = {
	#ifdef NGAILIK_MENU    //liudan add for 1006 setup menu.
    {37*8*2, 12*SETUP_BTN_HEIGHT, 38, 24, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},
    #else
    {35*8*2, 12*SETUP_BTN_HEIGHT, 38, 24, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},
    #endif

};
#endif

/************************************************************
Media Switch GUI for FAT
************************************************************/
#if defined(FAT_Write_UI)||defined(FILE_MODE_WRITE)//sunzhh 20041120
const   _t_osd_hdr osd_MediaswitchGUI[] = {
    
    #ifdef DISP_REGION_BOTTOM
    {360*2, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
    #endif
    
    #ifdef CARD_SETUP_TYPE_3 
    {64*2*2, (OSD_FONT_HEIGHT+8)*9, 50+65, 40, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 3      
    #else
    {64*2*2, (OSD_FONT_HEIGHT+8)*9, 50+65, 25, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 3
    #endif
    
    {64*3*2, (OSD_FONT_HEIGHT)*2,   80,    48, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 2
    {36*4*4, OSD_FONT_HEIGHT,       32,    34, NORMAL_HEADER,OSD_FORMAT_4COLOR,   OSD_INTERLACED},     // 1

    #ifndef OSD_BMP_DISPLAY
    {38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #else
    {360*2, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #endif//OSD_BMP
};
#endif

/************************************************************
SWITCH MEIDA
************************************************************/
#ifdef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-4-12 10:59
const   _t_osd_hdr osd_hdr_SwitchMedia[] = {
    #ifdef INDIGO_STYLE_OSDUI
    {200, 160, 128, 80, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},                   // 3
    {36*4*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2
    {36*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
    {38*8*2, OSD_FONT_HEIGHT, 26, 20, DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},   // 0
    #else//INDIGO_STYLE_OSDUI
    {200, 160, 128, 80, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},                   // 3
    {36*4*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2
    {36*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
    {38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #endif//INDIGO_STYLE_OSDUI
};
#endif



/************************************************************
Periph GUI for FAT
************************************************************/
#if defined(CF_CARD_WRITE)||defined(FAT_Write_UI)||defined(FILE_MODE_WRITE)//liweihua add 2003-10-30 9:15
const   _t_osd_hdr osd_periphGUI[] = {
    #ifdef DISP_REGION_BOTTOM
    {360*2, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
    #endif
    
    {64*4*2, (OSD_FONT_HEIGHT+8)*9, 50, 72, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},       // 3
    {64*3*2, (OSD_FONT_HEIGHT)*2, 80, 48, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},         // 2
    {36*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},             // 1
    
    #ifndef OSD_BMP_DISPLAY
    {38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #else
    {360*2, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #endif//OSD_BMP
};
#endif


/************************************************************
ID3
************************************************************/
#ifdef SUPPORT_OSDID3//liweihua 2003-12-28
const   _t_osd_hdr osd_OSDID3[] = {
    #ifdef DISP_REGION_BOTTOM
    {360*2, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
    #endif
    
    {38*8*2, OSD_FONT_HEIGHT*5, 26, 134, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},  // 3//liweihua mod 2004-1-14 10:26
    {36*4*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2
    {36*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
    
    
    #ifndef SDRAM_16Mb_Mode
    
        #ifndef OSD_BMP_DISPLAY
        {38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
        #else
        {360*2, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
        #endif//OSD_BMP
    #else
        #ifdef  NEW_DISPLAY_GOTO_OSD
        // 0 Temporarily set the last para as non-interlace. wuxiaofeng 2004-06-02
        {16*4*4, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_4COLOR,  OSD_NONINTERLACED}      // 
        #else
        {38*4*4, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_4COLOR,  OSD_INTERLACED}      // 0
        #endif    
    #endif    
};
#endif


/************************************************************
CD/CARD/USB Switch
************************************************************/
#ifdef SWITCH_CD_CARD_USB //liweihua mod 2004-6-8 14:45
const   _t_osd_hdr osd_switchGUI[] = {
    #ifdef DISP_REGION_BOTTOM
    {360*2, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
    #endif
    
    {64*2*2, (OSD_FONT_HEIGHT+8)*9, 50+65, 72, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},    // 3
    {64*3*2, (OSD_FONT_HEIGHT)*2, 80, 48, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},         // 2
    {36*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},             // 1

    #ifndef OSD_BMP_DISPLAY
    {38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #else
    {360*2, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #endif//OSD_BMP_DISPLAY
};
#endif


/************************************************************
MP4 Subtitle    // 2005/07/12 yltseng
************************************************************/
// 2005/12/28 yltseng
#ifdef SUPPORT_OSDSRT
    #ifndef SDRAM_16Mb_Mode
    
        #ifdef ALCO_DVD_UI
        #define OSD_SRT_REGION_NTSC_Y   58 //shenyj modify for alco 2006-9-2 11:07ÉÏÎç
        #define OSD_SRT_REGION_PAL_Y    100
        #else
        #define OSD_SRT_REGION_NTSC_Y   102
        #define OSD_SRT_REGION_PAL_Y    150
        #endif
        const   _t_osd_hdr osd_OSDSRT[] = {
        
        #ifdef DISP_REGION_BOTTOM
        {360*2, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // last region for cdrom display region
        #endif

	#ifdef	SUPPORT_FONT_OUTLINE
	    {38*8*2, (OSD_FONT_HEIGHT+10)*7, 26, OSD_SRT_REGION_NTSC_Y, NORMAL_HEADER, OSD_FORMAT_4COLOR,   OSD_INTERLACED},    // 3
	#else
        {38*8*2, (OSD_FONT_HEIGHT+10)*7, 26, OSD_SRT_REGION_NTSC_Y, SETUP_HEADER, OSD_FORMAT_16COLOR,   OSD_INTERLACED},    // 3
	#endif
        
        #ifdef OSD_BMP_REGION1
        {36*4*4, OSD_FONT_HEIGHT, 32, 56, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},              // 2
        {40*4*4, OSD_FONT_HEIGHT + 8 , 0, 37, BMP_REGION1_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
        #else
        {36*4*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},              // 2
        {36*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},             // 1
        #endif
    
        #ifdef INDIGO_STYLE_OSDUI //2006-03-20, mimitsai add for display color
        {38*8*2, OSD_FONT_HEIGHT, 26, 20, DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}              // 0
        #elif !defined( OSD_BMP_DISPLAY)
        {38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}              // 0
        #else
        {360*2, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
        #endif
    };
    #else
    
        #define OSD_SRT_REGION_NTSC_Y   182
        #define OSD_SRT_REGION_PAL_Y    218
        
        const   _t_osd_hdr osd_OSDSRT[] = {

        #ifdef OSD_SUPPORT_2_COLOR
        {38*4*4, OSD_FONT_HEIGHT*2, 26, OSD_SRT_REGION_NTSC_Y, SIMPLE_HEADER,  OSD_FORMAT_2COLOR,   OSD_INTERLACED},       // 3
        #else
        {38*4*4, OSD_FONT_HEIGHT*2, 26, OSD_SRT_REGION_NTSC_Y, NORMAL_HEADER,  OSD_FORMAT_4COLOR,   OSD_INTERLACED},       // 3
        #endif

        { 4*4*4, OSD_FONT_HEIGHT,   32, 46,  NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},             // 2
        {18*4*4, OSD_FONT_HEIGHT,   32, 34,  NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},             // 1
    
        #ifdef  NEW_DISPLAY_GOTO_OSD
        // 0 Temporarily set the last para as non-interlace. wuxiaofeng 2004-06-02
        {16*4*4, OSD_FONT_HEIGHT,   26, 20,  SETUP_HEADER,  OSD_FORMAT_4COLOR,  OSD_NONINTERLACED}           // 0
        #else
        {38*4*4, OSD_FONT_HEIGHT,   26, 20,  SETUP_HEADER,  OSD_FORMAT_4COLOR,  OSD_INTERLACED}              // 0
        #endif
        };
    #endif
#endif


/************************************************************
Common OSD Region
************************************************************/
#ifndef SDRAM_16Mb_Mode
const   _t_osd_hdr osd_hdr_0[] = {
    
    #if defined(LARGE_SCORES_DISPLAY)//&& defined(GBM_DVD)
    {24*4*2, (OSD_FONT_HEIGHT)*6, 120, 80, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 3
    #endif

    #ifdef DIV_GOTO_DISPLAY    
    {(36*5+16)*2, OSD_FONT_HEIGHT+6, 32, 46, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 2//{36*4, OSD_FONT_HEIGHT*2, 32, 46+6, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2
    #else
        #ifdef SUPPORT_GPIO_P_SCAN
    {36*3*4, OSD_FONT_HEIGHT, 80, 46+OSD_FONT_HEIGHT+12+64+24+12, SETUP_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 7
    {36*3*4, OSD_FONT_HEIGHT, 80, 46+OSD_FONT_HEIGHT+12+64+24, SETUP_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 6
    {36*3*4, OSD_FONT_HEIGHT, 80, 46+OSD_FONT_HEIGHT+64+24, SETUP_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 5
    {36*3*4, OSD_FONT_HEIGHT, 80, 46+OSD_FONT_HEIGHT+12+64, SETUP_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 4
    {36*3*4, OSD_FONT_HEIGHT, 80, 46+OSD_FONT_HEIGHT+64, SETUP_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 3
        #endif //#ifdef SUPPORT_GPIO_P_SCAN        
    #endif//DIV_GOTO_DISPLAY
    
    #ifdef DISP_REGION_BOTTOM
    {360*2, OSD_FONT_HEIGHT + 8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},      // 3 for cdrom display

        #ifdef SUPPORT_MP4
    {38*8*2, OSD_FONT_HEIGHT * 6, 26, 134,    SETUP_HEADER,   OSD_FORMAT_16COLOR, OSD_NONINTERLACED},    // 3 for mp4 subtitle
        #endif

    {36*4*4, OSD_FONT_HEIGHT + 8, 0, 56, BMP_REGION1_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2     //liudan add it,2004-11-17 11:07
    #else
    {36*4*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2     //liudan add it,2004-11-17 11:07
    #endif

    #ifdef OSD_BMP_REGION1//libing modify 36*4=>>40*4  2004-11-26 21:19
    {40*4*4, OSD_FONT_HEIGHT + 8 , 0, 37, BMP_REGION1_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
    #else
    {36*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
    #endif

    #ifndef OSD_BMP_DISPLAY
	// 2006-03-20, mimitsa modify for display color
	#ifdef INDIGO_STYLE_OSDUI
	{38*8*2, OSD_FONT_HEIGHT, 26, 20, DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},      // 0
	#else
    {38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
	#endif
    #else
    {360*2, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #endif//OSD_BMP
};
#else
// 16Mb small-memory mode
const   _t_osd_hdr osd_hdr_0[] = {
    // 2004/11/26 yltseng add region2, in order to show ANGLE
    #ifdef ORITRON_HK_DVD//libing 2005-9-13 10:26
    {24*4*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},      // 2
    #else
         #ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR  // change 4 to 2 color for 8202L,  modify by robert.chang 
    		{4*4*4, OSD_FONT_HEIGHT, 32, 46, SIMPLE_HEADER, OSD_FORMAT_2COLOR,  OSD_INTERLACED},      // 2
         #else	
    		{4*4*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},      // 2
	  	 #endif
    #endif
#ifdef ORITRON_HK_DVD//libing 2005-9-13 10:26    0//pls liumzh check.20050806 
    // 20050802 mimitsai modify, for showing longer osd message
    {30*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
#elif defined(DOLBY_INDICATOR_FOR_ALCO)||defined(ADD_D_FOR_DOLBY_DISPLAY)//shenyj modify for alco 
    {25*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
#else
     #ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR // change 4 to 2 color for 8202L,  modify by robert.chang 
    	{20*4*4, OSD_FONT_HEIGHT, 32, 34, SIMPLE_HEADER, OSD_FORMAT_2COLOR,  OSD_INTERLACED},     // 1
	 #else
  // {20*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
  // 16M 040Mode, reg0+reg1+reg2 maybe larger than 6K, so we reduce the size of osd region 1 
    	{18*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
     #endif  
#endif
    
    #ifdef  NEW_DISPLAY_GOTO_OSD
    // 0 Temporarily set the last para as non-interlace. wuxiaofeng 2004-06-02
    {16*4*4, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_4COLOR,  OSD_NONINTERLACED}      // 
    #else
       #ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR  // change 4 to 2 color for 8202L,  modify by robert.chang 
    		{38*4*4, OSD_FONT_HEIGHT, 26, 20, SIMPLE_HEADER,  OSD_FORMAT_2COLOR,  OSD_INTERLACED}      // 0
	   #else	 
    		{38*4*4, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_4COLOR,  OSD_INTERLACED}      // 0
       #endif 
    #endif
};
#endif


/************************************************************
Record Key
************************************************************/
#ifdef  RECORD_KEY//zhaoyanhua add 
const   _t_osd_hdr osd_hdr_record[] = {
    #ifdef DISP_REGION_BOTTOM
    {360*2, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
    #endif

    #ifndef OSD_BMP_DISPLAY
    {38*8*2, OSD_FONT_HEIGHT*4, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR,  OSD_INTERLACED}      // 0
    #else
    {360*2, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #endif//OSD_BMP
};
#endif


/************************************************************
Program OSD
************************************************************/
#ifdef INDIGO_STYLE_OSDUI
const   _t_osd_hdr osd_hdr_prog[] = {

    //{576, 300, 35, 50, SETUP_HEADER, OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 1    
    {610, 300, 25, 50, SETUP_HEADER, OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 1    
#ifdef SDRAM_16Mb_Mode//terry,2003/12/10 03:34PM
    {38*4*4, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_4COLOR,  OSD_INTERLACED}      // 0
#else
    {38*8*2, OSD_FONT_HEIGHT, 26, 20, DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},      // 0
    
#endif//#ifdef SDRAM_16Mb_Mode
};

#else //#ifdef INDIGO_STYLE_OSDUI

const   _t_osd_hdr osd_hdr_prog[] = {

#ifdef DISP_REGION_BOTTOM
    {360*2, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // last region, for cdrom display region
#endif

#ifdef OSD_BMP_PROG

    {37*8*2, 20,  31, 37+7+17+6+131,  BMP_REGION_F_HEADER,  OSD_FORMAT_16COLOR,	OSD_INTERLACED},  	// 5
    {37*8*2, 262, 31, 37+7+17+6,      BMP_REGION_E_HEADER,  OSD_FORMAT_16COLOR,	OSD_INTERLACED},  	// 4
    {37*8*2, 12,  31, 37+7+17,        BMP_REGION_D_HEADER,  OSD_FORMAT_16COLOR,	OSD_INTERLACED},  	// 3
    {37*8*2, 34,  31, 37+7,           BMP_REGION_B_HEADER,  OSD_FORMAT_16COLOR,  	OSD_INTERLACED},    // 2
    {37*8*2, 14,  31, 37,             BMP_REGION_A_HEADER,  OSD_FORMAT_16COLOR,  	OSD_INTERLACED},    // 1
#else    
    #if defined(ALCO_PROG_STYLE)
    {36*4*4, OSD_FONT_HEIGHT+8, 32, 150+4+4+4+2, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 7
    {36*4*4, OSD_FONT_HEIGHT*2, 32, 126+4+4+4+2, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 6
    {36*4*4, OSD_FONT_HEIGHT*2, 32, 102+4+4+4+2, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 5
    {36*4*4, OSD_FONT_HEIGHT*2, 32, 78+4+4+4+2,  NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 4
    {36*4*4, OSD_FONT_HEIGHT*2, 32, 54+4+4+4+2,  NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 3
    {36*4*4, OSD_FONT_HEIGHT+8, 32, 42+4+4+2,    NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 2
    {5*4*4,  OSD_FONT_HEIGHT+8, 32, 30+4+2,      NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 1
    #elif defined(USE_NEW_SCHINESE_OSD)
    {28*4*4, OSD_FONT_HEIGHT+8, 66, 150+4+4+4, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 7
    {28*4*4, OSD_FONT_HEIGHT*2, 66, 126+4+4+4, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 6
    {28*4*4, OSD_FONT_HEIGHT*2, 66, 102+4+4+4, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 5
    {28*4*4, OSD_FONT_HEIGHT*2, 66, 78+4+4+4,  NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 4
    {28*4*4, OSD_FONT_HEIGHT*2, 66, 54+4+4+4,  NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 3
    {28*4*4, OSD_FONT_HEIGHT+8, 66, 42+4+4,    NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 2
    {4*4*4,  OSD_FONT_HEIGHT+8, 66, 30+4,      NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 1
    #else
    {36*4*4, OSD_FONT_HEIGHT+8, 32, 150+4+4+4, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 7
    {36*4*4, OSD_FONT_HEIGHT*2, 32, 126+4+4+4, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 6
    {36*4*4, OSD_FONT_HEIGHT*2, 32, 102+4+4+4, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 5
    {36*4*4, OSD_FONT_HEIGHT*2, 32, 78+4+4+4,  NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 4
    {36*4*4, OSD_FONT_HEIGHT*2, 32, 54+4+4+4,  NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 3
    {36*4*4, OSD_FONT_HEIGHT+8, 32, 42+4+4,    NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 2
    {5*4*4,  OSD_FONT_HEIGHT+8, 32, 30+4,      NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},    // 1
	#endif//#ifdef ALCO_PROG_STYLE
#endif

#ifdef SDRAM_16Mb_Mode//terry,2003/12/10 03:34PM
    {38*4*4, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_4COLOR,  OSD_INTERLACED}      // 0
#elif defined(OSD_BMP_DISPLAY)
    {360*2, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#else
	{38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#endif//#ifdef SDRAM_16Mb_Mode
};
#endif // INDIGO_STYLE_OSDUI

/************************************************************
Password OSD - OP PASSWORD CHECK UI//libing 
************************************************************/
#if defined(ORITRON_TRAY_PASSWORD)||defined(SUPPORT_OP_SW_VERSION_UI)//libing 2005-4-25 10:06
const   _t_osd_hdr osd_hdr_op_psd[] = {
	
	{28*8*2, OSD_FONT_HEIGHT+14, 36, 40, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},      // 3
	//{36*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2
    //{36*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
    //{38*8, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
};
#endif

/************************************************************
Music OSD - 3D Sound
************************************************************/
#ifdef INDIGO_STYLE_OSDUI
const   _t_osd_hdr osd_hdr_music[] = {
    {    576-96,             280, 55, 50,  SETUP_HEADER, OSD_FORMAT_16COLOR, OSD_INTERLACED},  // 2    
    {    576, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER,  OSD_FORMAT_4COLOR, OSD_INTERLACED},  // 1
    { 38*8*2, OSD_FONT_HEIGHT,  26, 20, DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},      // 0
#else  //INDIGO_STYLE_OSDUI

const   _t_osd_hdr osd_hdr_music[] = {
#ifdef DISP_REGION_BOTTOM
    {360*2, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},      // 6 for cdrom display
#endif

#ifdef OSD_BMP_SOUND
	{288*2, 20,  35, 58+7+17 +6+107, BMP_REGION_F_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 5, used as bmp sound region E
	{288*2, 214, 35, 58+7+17 +6,     BMP_REGION_E_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 4 ,used as bmp sound region D
	{288*2, 12,  35, 58+7+17,        BMP_REGION_D_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 3 ,used as bmp sound region C
	{288*2, 34,  35, 58+7,           BMP_REGION_B_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 2 ,used as bmp sound region B
	{288*2, 14,  35, 58,             BMP_REGION_A_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 1 ,used as bmp sound region A
#else//OSD_BMP_SOUND   
    
    #ifdef  DYNAMIC_SPECTRUM  //fengjl   add 3-11-30 17:34
    {29*8*2,(OSD_FONT_HEIGHT+8)*7,64,  110,SETUP_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 3
    #else
    {29*8*2,(OSD_FONT_HEIGHT+8)*7,64,  64+4,SETUP_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 3
    #endif
    
    #if  (defined DIV_GOTO_DISPLAY) && (defined BBK_DVD) //zhaoyanhua add 2003-11-10 11:52  
    {(36*5+16)*2, OSD_FONT_HEIGHT+6, 32, 46, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},        // 2
    #else
    {29*8*2,OSD_FONT_HEIGHT+12,   64,  46+4,SETUP_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 2
    #endif
    
    #ifdef OSD_BMP_REGION1//libing modify 36*4=>>40*4 2004-11-26 21:19
    {40*4*4, OSD_FONT_HEIGHT + 8 , 0, 37, BMP_REGION1_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
    #else
    {36*4*4,OSD_FONT_HEIGHT,      32,  34,  NORMAL_HEADER,OSD_FORMAT_4COLOR,OSD_INTERLACED},  // 1
    #endif
#endif//OSD_BMP_SOUND

#ifndef OSD_BMP_DISPLAY
    {38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#else
    {360*2, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
#endif//OSD_BMP

#endif // INDIGO_STYLE_OSDUI
};
/************************************************************
PLAYMODE MENU - OSD//libing
************************************************************/
#ifndef SDRAM_16Mb_Mode
const   _t_osd_hdr osd_hdr_menu[] = {
	//{30*8, 6*OSD_FONT_HEIGHT, 62, 40, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},  // 3
	{30*8*2, 4*OSD_FONT_HEIGHT+60, 56, 60, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},		// 3
	{36*4*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2
	{36*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},  // 1
	{38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
};
#else
const   _t_osd_hdr osd_hdr_menu[] = {

	{28*8*2, 5*OSD_FONT_HEIGHT-8, 78, 40, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_NONINTERLACED},  // 1	
	{38*4*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_4COLOR,  OSD_INTERLACED}      // 0
};	
#endif

/************************************************************
OP_REGION_OSD//libing
************************************************************/
#ifdef SUPPORT_OP_REGION_UI//libing 2005-8-23 17:45
const   _t_osd_hdr osd_hdr_region_code[] = {
	{30*8*2,OSD_FONT_HEIGHT+14, 36, 40, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED} //0
};
#endif

/************************************************************
Double Title
************************************************************/
#ifdef DOUBLE_TITLE //susu add 2003-8-20 14:43

const   _t_osd_hdr osd_hdr_double_title[] = {

    #ifdef DISP_REGION_BOTTOM
    {360*2, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
    #endif

    {36*4*2*2,OSD_FONT_HEIGHT+5,32,34,  SETUP_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, // 1

    #ifndef OSD_BMP_DISPLAY
    {38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #else
    {360*2, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #endif//OSD_BMP
};
#endif


/************************************************************
Virtual Keyboard
1. WSLEE modified the fourth regions parameters 
************************************************************/
#ifdef VIRTUAL_KEYBOARD //liweihua add 03-8-15

const   _t_osd_hdr osd_keyboard[] = {

    #ifdef DISP_REGION_BOTTOM
    {360*2, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
    #endif

    #ifdef  NINTAUS_DVD //Maoyong 2004.03.11
    {160, 140,256,154, KEYBOARD_HEADER, OSD_FORMAT_256COLOR,OSD_INTERLACED},  // 4//20040225
    #else
      {144, 118,256,168, KEYBOARD_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED}, //WSLEE for 16 color palette 050518
//    {160, 140,256,168, KEYBOARD_HEADER, OSD_FORMAT_256COLOR,OSD_INTERLACED},  // 4//20040225 WSLEE mark
    #endif
    
    #ifdef CD_PLAYER
    {(38*4-44)*2,(OSD_FONT_HEIGHT+8)*6,32+60+37,72, EQ_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED},  // 3
    #endif
    
    {36*4*4, OSD_FONT_HEIGHT, 32, 46, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2
    {36*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
    
    #ifndef OSD_BMP_DISPLAY
    {38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #else
    {360*2, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #endif//OSD_BMP
};
#endif


/************************************************************
PMP UI
************************************************************/
#ifdef PMP_UI  //liweihua 2004-12-28
const   _t_osd_hdr osd_pmp[] = {

      {38*8*2,(OSD_FONT_HEIGHT+8)*11,32,46, EQ_HEADER, OSD_FORMAT_4COLOR,OSD_INTERLACED},  // 3//YANGLI    mod 2005-6-8
	//{38*8*2,(OSD_FONT_HEIGHT+8)*11,32,46, EQ_HEADER, OSD_FORMAT_16COLOR,OSD_INTERLACED},  // 3//liweihua mod 2005-3-16
    // 2
    {36*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1

    #ifndef OSD_BMP
    {38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #else
    {360*2, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #endif//OSD_BMP    
};
#endif


/************************************************************
Real Color Screen Saver
************************************************************/
#ifdef REALCOLOR_SCREENSAVER
const   _t_osd_hdr osd_screensaver[] = {
    {60*3, (OSD_FONT_HEIGHT+9)*6,2,2, SCREENSAVER_HEADER, OSD_FORMAT_256COLOR,OSD_INTERLACED}  // 0
};

#else//#ifdef REALCOLOR_SCREENSAVER
const   _t_osd_hdr osd_screensaver[] = {
    
#ifdef SCREENSAVER_ZOOM_IN_2
    {40*4, 108,0,0, NES_HEADER, OSD_FORMAT_4COLOR,OSD_INTERLACED}  // 0
#else
    //joshua, 20050823, modified osd initial function of screensaver
    {40*4, 108,0,0, NORMAL_HEADER, OSD_FORMAT_4COLOR,OSD_INTERLACED}  // 0
#endif
};
#endif//#ifdef REALCOLOR_SCREENSAVER


/************************************************************
Parental GUI
************************************************************/
#ifdef NEW_PARENTAL_GUI//zhaoyanhua add for BBK DVD 2003-11-28 10:49
const   _t_osd_hdr osd_hdr_parental[] = {
   {38*6*2, OSD_FONT_HEIGHT*6, 80, 67, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
};
#endif


/************************************************************
Repeat Read
************************************************************/
#ifdef SUPPORT_REP_READ
const   _t_osd_hdr osd_hdr_rep_read[] = {

    #ifdef DISP_REGION_BOTTOM
    {360*2, OSD_FONT_HEIGHT+8 , 10, 216, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED},    // 8 for cdrom display region
    #endif
    
    {READ_REG_W*8*2, READ_REG_H, 80, 48, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 2
    {36*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
    
    #ifndef OSD_BMP_DISPLAY
    {38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #else
    {360*2, OSD_FONT_HEIGHT+8 , 0, 20, BMP_DISPLAY_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0
    #endif//OSD_BMP
};
#endif
#ifdef DVB_SETUP_MENU
#include "..\dvb_h\Dvb_menu.h"
//#include "dvbmenu.h"
const   _t_osd_hdr osd_hdr_dvb_menu[] = {
	{(38*8 + 20)*2, OSD_FONT_HEIGHT * 16, 10, 28, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},
};
#endif
#ifdef SUPPORT_TELETEXT
#include "..\dvb_h\dvb_menu.h"  //tcf added 2005-11-1 21:19
const   _t_osd_hdr osd_hdr_dvb_ttx_menu_ntsc[] = {
    {TTX_REGION_W , TTX_REGION_H_NTSC, TTX_REGION_X, TTX_REGION_Y_NTSC, TTX_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 0
};
const   _t_osd_hdr osd_hdr_dvb_ttx_menu_pal[] = {
    {TTX_REGION_W , TTX_REGION_H_PAL, TTX_REGION_X, TTX_REGION_Y_PAL, TTX_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 0
};
#endif

#ifdef SUPPORT_SUBTITLE
#include "..\dvb_h\Dvb_menu.h"
_t_osd_hdr osd_hdr_dvb_subtitle_menu[] = {
    {SUBTITLE_REGION_W , SUBTITLE_REGION_H, SUBTITLE_REGION_X, SUBTITLE_REGION_Y, SUBTITLE_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},     // 0
};
#endif

#ifdef SUPPORT_DVB_GUI_NEW
/************************************************************
8202+6600 GUI(Version2 Gui with 16 color)//taolin
************************************************************/
#include "..\dvb_h\Dvb_Macro_Def.h"
const  _t_osd_hdr stOSD_Header[] = 
    {
        {
            DVB_MENU_REGION_WIDTH ,
            DVB_MENU_REGION_HEIGHT,
            0,
            DVB_MENU_REGION_START_Y_P,
            NONOSDVBS_HEADER,//SETUP_HEADER,//, 
            OSD_FORMAT_16COLOR,
            OSD_INTERLACED,
        }
    };
////sunzhh add for Program Info display 20051027
const  _t_osd_hdr stOSD_InfoHeader[] = 
    {
        {
            DVB_MENU_REGION_WIDTH ,
            DVB_MENU_REGION_HEIGHT,
            0,
            DVB_MENU_REGION_START_Y_P,
            INFO_HEADER,
            OSD_FORMAT_16COLOR,
            OSD_INTERLACED,
        }
    };    
    
#endif
      
#ifdef GPS_KEYBOARD
const _t_osd_hdr osd_gps_keyboard[] = {

    //{368, 160, 0, 394, NORMAL_HEADER, OSD_FORMAT_4COLOR,	OSD_INTERLACED},	 // 3
		
	{720,250, 0,115, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},	      // 3//frank.huang change it 050919
	
	{368, OSD_FONT_HEIGHT*1, 82, 60, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2
			
	//{600, 240, 24, 60, NORMAL_HEADER,  OSD_FORMAT_4COLOR, OSD_INTERLACED},	 //2
		
	{36*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},	  // 1
		
	{38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}	  // 0
};
#endif
#ifdef GPS_MENU
const _t_osd_hdr osd_gps_menu[] = {
    
	//{368, 160, 0, 394, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 3

 	{720,88, 0,180, SETUP_HEADER, OSD_FORMAT_16COLOR,  OSD_INTERLACED},	     // 3
 	
    {368, 352, 88, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2//frank.huang change it 050926
    
    //{600, 240, 24, 60, NORMAL_HEADER,  OSD_FORMAT_4COLOR, OSD_INTERLACED},     //2

    {36*4*4, 0, 32, 33, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1

    {38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0

};

/*const _t_osd_hdr osd_gps_keyboard[] = {

			//{368, 160, 0, 394, NORMAL_HEADER, OSD_FORMAT_4COLOR,	OSD_INTERLACED},	 // 3
		
			{720,88, 0,180, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},	  // 2
    
    //{600, 240, 24, 60, NORMAL_HEADER,  OSD_FORMAT_4COLOR, OSD_INTERLACED},     //2

    {36*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1

    {38*8*2, OSD_FONT_HEIGHT, 26, 20, SETUP_HEADER,  OSD_FORMAT_16COLOR, OSD_INTERLACED}      // 0

		};*/


#endif

#ifdef NODISC_SHOW_IN_DIFF_REGION
const   _t_osd_hdr osd_hdr_0n[] = {
    //{36*4, OSD_FONT_HEIGHT, 32, 180+14+12, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 2
    {18*4*4, OSD_FONT_HEIGHT, 32, 180+14, NORMAL_HEADER, OSD_FORMAT_4COLOR,  OSD_INTERLACED},     // 1
    {36*4*4, OSD_FONT_HEIGHT, 32, 34, NORMAL_HEADER,  OSD_FORMAT_4COLOR, OSD_INTERLACED}      // 0   
};    
#endif

