/*****************************************************\
Creater: Kenny
Date   : 2001/5/15 02:39PM
Description: Display menu using
\*****************************************************/

#include "global.h"
#include "osd.h"
#include "func.h"
#include "cfont.h"
#include "navdata.h"
#include "user_if.h"
#include "osdfont.h"
#include "auddrv.h" //2004AUDDRV oliver 20041004 for using audio driver purpose
//#include "audif.h"
#include "setup.h"
#include "user_init.h"   // alan added : for OSD_FONT_COMPRESS
#include "stdlib.h"

#ifdef OSD_BMP
#include "osd_BmpUI.h"
#endif

#ifndef DVDRELEASE
//#define DISP_DBG    1
#endif

#ifndef DISP_DBG
#undef printf
#undef print_block
#define printf(f, a...) do {} while (0)
#define print_block(x,y) do {} while (0)
#endif

#define     DISP_SLOW_DOWN      0
#define     DISP_HOLD_COUNT     20

//OSD disp color definition(the color index are defined in palette_16color_setup[])
#ifdef GREY_OSD_DISP               // ych 2-7-8 17:39
    #define DISP_WHITE      2
    #define DISP_GRAY       3
    #define DISP_GBLUE      4
    #define DISP_GREEN      2//8
    #define DISP_YGREEN     2//9
    #define DISP_ORANGE     2//10   //2-7-6 15:29
    #define DISP_SHADOW     0
#elif defined(OSD_BMP_DISPLAY)
    #define DISP_SHADOW 7
    #ifdef DISP_REGION_BOTTOM
        #define DISP_SHADOW_CDROM		0
    #endif
    #define DISP_FONT_GRAY	10
    #define DISP_FONT_YELLOW	11
    #define DISP_GBLUE      9
    #define DISP_GREEN     8 
    #define DISP_YGREEN     11
	#define DISP_ORANGE     8
    #define DISP_GRAY       10
    #define DISP_WHITE	10
    #define DISP_LITTLE_CHAR_WIDTH	8
#elif defined(PHILIPS_SETUP)
    #define DISP_WHITE      2
    #define DISP_GRAY       3
    #define DISP_GBLUE      4
    #define DISP_GREEN     10// 8zhangyu
    #define DISP_YGREEN     1//9
    #define DISP_ORANGE     12//5
    #define DISP_SHADOW     0
    #define DISP_HLFONT     14
    #define DISP_HLGROUND   2
#elif defined(SETUP_COLOR_TYPE2)     //zhangyu 
  #ifdef INDIGO_STYLE_OSDUI // INDIGO_STYLE_OSDUI for display color setup
    #define DISP_WHITE		7	// 
    #define DISP_GRAY		6	// disable color
    #define DISP_GBLUE		2	// goto highlight bg
    #define DISP_GREEN		2	// TRK, CLOCK, REPEAT, TT, CH, LANG(VAL), SUB(VAL), ANGEL(VAL)
    #define DISP_YGREEN		1	// number color
    #define DISP_ORANGE		4	// disk type color 
    #define DISP_SHADOW		0	// bg color
  #else
    #define DISP_WHITE      2
    #define DISP_GRAY       3
    #define DISP_GBLUE      4
    #define DISP_GREEN     10// 8zhangyu
    #define DISP_YGREEN     1//9
    #define DISP_ORANGE     12//5
    #define DISP_SHADOW     0
  #endif
#else
    #define DISP_WHITE      2
    #define DISP_GRAY       3
    #define DISP_GBLUE      4
    #define DISP_GREEN      8
    #define DISP_YGREEN     9
    #ifdef  NOSHOW_CDROM_WHEN_DISP
    #define DISP_ORANGE     2
    #else
    #define DISP_ORANGE     5
    #endif
    #define DISP_SHADOW     0
#endif //GREY_OSD_DISP

#ifndef OSD_BMP_DISPLAY
//page 1
//SVCD,VCD,CDDA
    #define COOK_CD                 0

    #if defined(SYBER_DVD)||defined(SHOW_VCD_VER_INFO)   //yaowh add 04-12-17//xulf 2003-11-18
    #define COOK_TRK                COOK_CD+7               //6
    #elif defined(USE_COOK_TRK_6)//20040210
    #define COOK_TRK                COOK_CD+5+1               //5
    #else
    #ifdef ALCO_DIVX_UI//shenyj modify for alco divx 12/09
    #define COOK_TRK                COOK_CD+6//5               //6
    #else
    #define COOK_TRK                COOK_CD+5               //5
    #endif
    #endif

    #define COOK_TRK_VAL            COOK_TRK+4              //9
    #define COOK_SPK                COOK_TRK_VAL+6          //15
    #define COOK_PBC                COOK_SPK+3              //18
    #define COOK_REP                COOK_PBC+4              //22

    #ifdef FUSS_DVD
    #define COOK_CLOCK              COOK_REP+3+1+1              //27//25
    #elif defined(USE_COOK_TRK_6)//20040210
    #define COOK_CLOCK              COOK_REP+3-1              //25
    #else
    #define COOK_CLOCK              COOK_REP+3              //25
    #endif

    #if defined(USE_COOK_TRK_6) || defined(NINTAUS_DVD)//20040210
    #define COOK_CLOCK_VAL          COOK_CLOCK+2+2            //27
    #else//#elif defined(USE_COOK_TRK_6)//20040210
    #define COOK_CLOCK_VAL          COOK_CLOCK+2            //27
    #endif//#elif defined(USE_COOK_TRK_6)//20040210

//DVD
    #ifdef FUSS_DVD
    #define COOK_CHP                COOK_TRK_VAL+5+1          //15//14
    #else
        //yw020909 #define COOK_CHP                COOK_TRK_VAL+5          //14
        #ifdef NEW_SEARCH_OSD
        // YW ------- osd ---------- [Top]
        // Modify 020725
        #define COOK_CHP                COOK_TRK_VAL+6          //14
        // YW ------- osd ---------- [Bottom]
        #else
        #define COOK_CHP				COOK_TRK_VAL+5
        #endif
    #endif

    #define COOK_CHP_VAL            COOK_CHP+4              //18
    //CDROM(MP3,JPEG)
    //#define COOK_SPK_MP3            COOK_TRK_VAL+8          //17
    #define COOK_SPK_MP3            COOK_TRK_VAL+9          //17   TRK_VAL=xxxx/xxxx Jeff 20020503

//page 2
    //#define COOK_AUDIO              0
    //#define COOK_AUDIO_VAL          COOK_AUDIO+3            //3
    //#define COOK_AUDIO_LANG         COOK_AUDIO_VAL+4        //7
    //#define COOK_AUDIO_TYPE         COOK_AUDIO_LANG+5       //12
    //#define COOK_SUBTITLE           COOK_AUDIO_TYPE+7       //19
    //#define COOK_SUBTITLE_VAL       COOK_SUBTITLE+3         //22
    //#define COOK_SUBTITLE_LANG      COOK_SUBTITLE_VAL+5     //26
    //#define COOK_ANGLE              COOK_SUBTITLE_LANG+6    //32
    //#define COOK_ANGLE_VAL          COOK_ANGLE+3            //35
    
    #ifdef FUSS_DVD
    #define COOK_AUDIO              0
    #define COOK_AUDIO_VAL          COOK_AUDIO+2            //2
    #define COOK_AUDIO_TYPE         COOK_AUDIO_VAL+3       //5
    #define COOK_AUDIO_LANG         COOK_AUDIO_TYPE+6+3        //14
    #define COOK_SUBTITLE           COOK_AUDIO_LANG+9-3        //20
    #define COOK_SUBTITLE_VAL       COOK_SUBTITLE+2         //22
    #define COOK_SUBTITLE_LANG      COOK_SUBTITLE_VAL+5     //27
    #define COOK_ANGLE              COOK_SUBTITLE_LANG+6    //33
    #define COOK_ANGLE_VAL          COOK_ANGLE+2            //35
    #else//#ifdef FUSS_DVD
    #ifdef NEW_SEARCH_OSD
    #define COOK_ANGLE              14
    #define COOK_ANGLE_VAL          16
    #define COOK_AUDIO              5
    #define COOK_AUDIO_VAL          COOK_AUDIO+2
    #define COOK_AUDIO_LANG         COOK_AUDIO_VAL+3
    #define COOK_AUDIO_TYPE         COOK_AUDIO_LANG+4
    #define COOK_SUBTITLE           COOK_AUDIO_TYPE+9
    #define COOK_SUBTITLE_VAL       COOK_SUBTITLE+2
    #define COOK_SUBTITLE_LANG      COOK_SUBTITLE_VAL+5
    #else // NEW_SEARCH_OSD
    #define COOK_AUDIO              0
    #define COOK_AUDIO_VAL          COOK_AUDIO+2            //2
    #if defined(PORTABLE_8202D)&&defined(ALCO_DVD_UI)
    #define COOK_AUDIO_LANG         COOK_AUDIO_VAL+4        //5
    #else
    #define COOK_AUDIO_LANG         COOK_AUDIO_VAL+3        //5
    #endif//#if defined(PORTABLE_8202D)&&defined(ALCO_DVD_UI)

    #if defined(DOLBY_INDICATOR_FOR_ALCO)
    #define COOK_AUDIO_TYPE         COOK_AUDIO_LANG+4       //9
    #define COOK_SUBTITLE           COOK_AUDIO_TYPE+13       //20
    #define COOK_SUBTITLE_VAL       COOK_SUBTITLE+3         //22
    #define COOK_SUBTITLE_LANG      COOK_SUBTITLE_VAL+1     //27
    #define COOK_ANGLE              COOK_SUBTITLE_LANG+5    //33
    #define COOK_ANGLE_VAL          COOK_ANGLE+2            //35
    #elif (defined(PORTABLE_8202D)||defined(ALCO_PORTABLE_DVD_8202D_DVB))&&defined(ALCO_DVD_UI)
    #define COOK_AUDIO_TYPE         COOK_AUDIO_LANG+4       //11
    #define COOK_SUBTITLE           COOK_AUDIO_TYPE+11       //20
    #define COOK_SUBTITLE_VAL       COOK_SUBTITLE+3         //22
    #define COOK_SUBTITLE_LANG      COOK_SUBTITLE_VAL+4     //27
    #define COOK_ANGLE              COOK_SUBTITLE_LANG+5    //33
    #define COOK_ANGLE_VAL          COOK_ANGLE+2            //35
    #elif defined(PORTABLE_8202S)&&defined(ALCO_DVD_UI) 
    #undef COOK_TRK_VAL
    #define COOK_TRK_VAL            COOK_TRK+3
    #undef COOK_CHP
    #define COOK_CHP                COOK_TRK_VAL+6
    #undef COOK_CHP_VAL
    #define COOK_CHP_VAL            COOK_CHP+3
    #undef COOK_CLOCK  
    #define COOK_CLOCK              COOK_REP+4 
    #undef  COOK_CLOCK_VAL          
    #define COOK_CLOCK_VAL          COOK_CLOCK+2 
    #define COOK_AUDIO_TYPE         COOK_AUDIO_LANG+4       //11
    #define COOK_SUBTITLE           COOK_AUDIO_TYPE+11      //20
    #define COOK_SUBTITLE_VAL       COOK_SUBTITLE+3         //22
    #define COOK_SUBTITLE_LANG      COOK_SUBTITLE_VAL+4     //27
    #define COOK_ANGLE              COOK_SUBTITLE_LANG+5    //33
    #define COOK_ANGLE_VAL          COOK_ANGLE+2            //35
    #else//#if defined(DOLBY_INDICATOR_FOR_ALCO)
    #define COOK_AUDIO_TYPE         COOK_AUDIO_LANG+6       //11
    #define COOK_SUBTITLE           COOK_AUDIO_TYPE+9       //20
    #define COOK_SUBTITLE_VAL       COOK_SUBTITLE+2         //22
    #define COOK_SUBTITLE_LANG      COOK_SUBTITLE_VAL+5     //27
    #define COOK_ANGLE              COOK_SUBTITLE_LANG+6    //33
    #define COOK_ANGLE_VAL          COOK_ANGLE+2            //35
    #endif//#if defined(DOLBY_INDICATOR_FOR_ALCO)

    #endif//#ifdef NEW_SEARCH_OSD
    #endif//#ifdef FUSS_DVD

    //special define
    #define COOK_S_TIMER            0x1<<16
    #define COOK_S_LANG             0x1<<17
    #define COOK_S_MODE             0x1<<18

//Jeff 20020411
//page 3
    #define COOK_MARK               0
    #define COOK_MARK_VAL           COOK_MARK+5             //5
    //#define COOK_MARK_VAL           COOK_MARK+4             //4 Jeff 20020621

#else//OSD_BMP_DISPLAY
//page 1
//SVCD,VCD,CDDA
    #define COOK_CD                 53
    #define COOK_CDROM		77

	#if defined(SYBER_DVD)
    #define COOK_TRK                COOK_CD+68+22
    #define COOK_TRK_CDROM		COOK_CDROM+68+22
    #elif defined(USE_COOK_TRK_6)//20040210
    #define COOK_TRK                COOK_CD+68+22
    #define COOK_TRK_CDROM		COOK_CDROM+68+22
    #else
    #define COOK_TRK            COOK_CD+68+22 //COOK_CD+68+22+24-2//libing2004-11-24 12:46
                                              //zhuyanfeng modified 02/12/2004 14:40  //to avoid the bug "dis"or"hdcd"cover with rep icon.
    #define COOK_TRK_CDROM		COOK_CDROM+68+22
    #endif//SYBER_DVD

	#define COOK_TRK_VAL            COOK_TRK+2*16+6+26//libing2004-11-24 12:46
    #define COOK_TRK_VAL_CDROM	COOK_TRK_CDROM+2*16+6
    #define COOK_SPK                404
    #define COOK_SPK_CDROM		410
    #define COOK_PBC                COOK_REP-12-48
    #define COOK_REP               350-22//350 //zhuyanfeng modified 02/12/2004 14:40  //to avoid the bug "dis"or"hdcd"cover with rep icon.
    #define COOK_REP_CDROM	  356

	#ifdef FUSS_DVD
    #define COOK_CLOCK              458
    #define COOK_CLOCK_CDROM	464
    #elif defined(USE_COOK_TRK_6)//20040210
    #define COOK_CLOCK              458
    #define COOK_CLOCK_CDROM	464
    #else
    #define COOK_CLOCK            458//  458
    #define COOK_CLOCK_CDROM	464
    #endif//FUSS_DVD

    #if defined(USE_COOK_TRK_6) || defined(NINTAUS_DVD)//20040210
    #define COOK_CLOCK_VAL          COOK_CLOCK+16+6
    #define COOK_CLOCK_VAL_CDROM	COOK_CLOCK_CDROM+16+6
    #else//#elif defined(USE_COOK_TRK_6)//20040210
    #define COOK_CLOCK_VAL          COOK_CLOCK+16+6
    #define COOK_CLOCK_VAL_CDROM	COOK_CLOCK_CDROM+16+6
    #endif//#elif defined(USE_COOK_TRK_6)//20040210

    //DVD
    #ifdef FUSS_DVD
    #define COOK_CHP                COOK_TRK_VAL+40+26
    #else
    #ifdef NEW_SEARCH_OSD
    // YW ------- osd ---------- [Top]
    // Modify 020725
    #define COOK_CHP                COOK_TRK_VAL+40+26
    // YW ------- osd ---------- [Bottom]
    #else
    #define COOK_CHP			COOK_TRK_VAL+40+26-2//libing2004-11-24 12:46

    #endif
    #endif

    #define COOK_CHP_VAL            COOK_CHP+2*16+6+28//libing2004-11-24 12:46
    #define COOK_SPK_MP3            COOK_TRK_VAL+9*8          //17   TRK_VAL=xxxx/xxxx Jeff 20020503

//page 2
    #ifdef FUSS_DVD
    #define COOK_AUDIO              COOK_CD+68+22
    #define COOK_AUDIO_VAL          COOK_AUDIO+30+6
    #define COOK_AUDIO_TYPE         381+38+6
    #define COOK_AUDIO_LANG         COOK_AUDIO_VAL+6*8
    #define COOK_SUBTITLE           COOK_AUDIO_VAL+4*8+3*8+26
    #define COOK_SUBTITLE_VAL     COOK_SUBTITLE+32+6
    #define COOK_SUBTITLE_LANG      COOK_SUBTITLE_VAL+6*8
    #define COOK_ANGLE              COOK_AUDIO_TYPE+7*8+26
    #define COOK_ANGLE_VAL          COOK_ANGLE+32+6
    #else
        #ifdef NEW_SEARCH_OSD
        #define COOK_ANGLE              507
        #define COOK_ANGLE_VAL          COOK_ANGLE+32+6
        #define COOK_AUDIO              COOK_CD+68+22
        #define COOK_AUDIO_VAL          COOK_AUDIO+30+6
        #define COOK_AUDIO_LANG         COOK_AUDIO_VAL+6*8
        #define COOK_AUDIO_TYPE         381+38+6
        #define COOK_SUBTITLE           COOK_AUDIO_VAL+4*8+3*8+26
        #define COOK_SUBTITLE_VAL     COOK_SUBTITLE+32+6
        #define COOK_SUBTITLE_LANG      COOK_SUBTITLE_VAL+6*8
        #else // NEW_SEARCH_OSD
        #define COOK_AUDIO              COOK_CD+68+22
        #define COOK_AUDIO_VAL          COOK_AUDIO+30+6
        #define COOK_AUDIO_TYPE         381+38+6
        #define COOK_AUDIO_LANG         COOK_AUDIO_VAL+6*8
        #define COOK_SUBTITLE           COOK_AUDIO_VAL+4*8+3*8+26
        #define COOK_SUBTITLE_VAL       COOK_SUBTITLE+32+6
        #define COOK_SUBTITLE_LANG      COOK_SUBTITLE_VAL+6*8
        #define COOK_ANGLE              507
        #define COOK_ANGLE_VAL          COOK_ANGLE+32+6
        #endif
    #endif

//special define
#define COOK_S_TIMER            0x1<<16
#define COOK_S_LANG             0x1<<17
#define COOK_S_MODE             0x1<<18

//Jeff 20020411
//page 3
#define COOK_MARK               0
#define COOK_MARK_VAL           COOK_MARK+5             //5
//#define COOK_MARK_VAL           COOK_MARK+4             //4 Jeff 20020621
#endif //OSD_BMP_DISPLAY

extern int getCDDAType();
//#ifdef SUPPORT_BOOK	//zhongshan marked for warning (ifndef book the function must be nop )2006-2-28 13:46
extern void mark_UpdateOSD();
//#endif
extern UINT8 DVD_check_state(void);
extern void osd_Move2OSD0(BYTE iLine);
extern void osd_ClearOSD0(BYTE iSLine, BYTE iELine);
extern UINT16 mp3_file_count(void);
extern UINT16 Is_JPEG_STATE(void);
extern void FSGUI_JpgUpdateOSD(void);
extern const UINT8 osd_cd_id[];

#ifdef REMAIN_TIME//nono 2-7-13 11:28 for fuss
extern BYTE polling_clock;//2-7-13 9:12
#endif

extern UINT32 coding_mode_now;

#ifdef DVD_AUDIO
extern UINT32 dAMG_LSN;		// alan, 2002/11/13 02:12§U§»
#endif

UINT8 *get_lang_name(int mode);
void DispPolling(BYTE bReset);

enum {
    OSD0_STATE_INIT=0,
	OSD0_STATE_HIDE,
	OSD0_STATE_FADE_IN,
	OSD0_STATE_FULL_SHOW,
	OSD0_STATE_FADE_OUT,
};
BYTE    osd0_state=OSD0_STATE_INIT;           //OSD0 state

BYTE    osd0_show_line=0;       //OSD0 show length for fade-in and fade-out(0~24)
UINT32  osd0_hold_count=0;      //OSD0 hold count between fade-in and fade-out
//UINT32  osd0_slow_down=0;       //OSD0 slow down factor: for fade-in and fade-out effect,
//DispPolling will increase osd0_slow_down every call

BYTE    cddaType=0;             //0->CDDA, 1->HDCD

#ifdef SDRAM_16Mb_Mode

UINT32 *pTopLine;
UINT32 *pBtmLine;
UINT32 *pOSD;

#define OSD_16b_BUG
#define ALIGN_32B(x) ((x+31)/32)

extern  const	UINT8	osd_header_offset[8];
/* =
{
	ALIGN_32B(16 + 2*4),
#ifdef OSD_16b_BUG
	ALIGN_32B(16 + 4*16),
#else
    ALIGN_32B(16 + 2*16),
#endif
	ALIGN_32B(16 + 2*256),
	ALIGN_32B(16),
	ALIGN_32B(16),
	ALIGN_32B(16),
	ALIGN_32B(16),
	ALIGN_32B(16)
};*/

#define	OSD_DATA_OFFSET(f)	    (osd_header_offset[(f)&OSD_FORMAT_MASK])
#define	OBV_BASE		        (SDRAM_BASE + regs0->osd_base_addr*1024)
#define	get_osdbuf_baseptr()	((void *)OBV_BASE)

#endif

extern  UINT8   osd_temp_buf[];
#ifdef USE_NEW_SCHINESE_OSD//liyl add 20060301
static int hi_light_index = -1;
#endif

#ifdef SDRAM_16Mb_Mode

void do_DispOSD0String(BYTE xStart, BYTE yStart __attribute__((unused)), BYTE *pStr, BYTE fgColor, BYTE bgColor)
{

    BYTE        c;
    UINT32      iStrLoc=0;
    const BYTE* pFont;
	
    font_palette temp_palette;
    dimension out_dimension;
    coordinate  temp_coordinate;	
	
    temp_coordinate.x = xStart*16;
    temp_coordinate.y = yStart;

    temp_palette.font_color = fgColor;
    temp_palette.background_color = bgColor;

    //process each charactor until string ending('\0')
    while ( (c = ((BYTE *)pStr)[iStrLoc]) != '\0' ) {

        iStrLoc++;

        if (c == '\r') { //prefix characher:to use font_table2
            if ( (c = ((BYTE *)pStr)[iStrLoc])=='\0' )
                break;
            iStrLoc++;

            if ((pFont = get_font_entry(1,c))==NULL) continue;
        // mimitsai merge from dp2070/dp3240

        } else if( c == '\t' ) {        // yltseng v2.3
            if ( (c = ((BYTE *)pStr)[iStrLoc])=='\0' )
                break;
            iStrLoc++;

            if ((pFont = get_font_entry(2,c))==NULL) continue;
        } else {
            //get current char entry
	     	pFont = get_font_entry(0,c);
        }


        out_dimension.x_length = pFont[0];      // width  of font
	 out_dimension.y_length = pFont[1];   // height of font

	 pFont +=3;
     
        osd_draw_bitmap(0, &temp_coordinate, pFont, &out_dimension, 1, 0, &temp_palette);	
//        osd_draw_font_bitmap(pFont, &temp_coordinate,&out_dimension, &temp_palette, 0, 0);        
        temp_coordinate.x +=out_dimension.x_length;

    }
    
}


/*********************************************************************** mark by robert.chang, 2006/03/16  

void do_DispOSD0String(BYTE xStart, BYTE yStart __attribute__((unused)), BYTE *pStr, BYTE fgColor, BYTE bgColor)
{
    UINT32      i, j, k;
    BYTE        c;
    UINT32      iStrLoc=0;
    UINT32      iFontWidth, iFontHigh;
    const BYTE* pFont;

    pTopLine = (UINT32 *)(((BYTE *)get_osdbuf_baseptr()) + (region[0].osd_header[0]+OSD_DATA_OFFSET(region[0].osd_format))*32 );
    pBtmLine = (UINT32 *)(((BYTE *)get_osdbuf_baseptr()) + (region[0].osd_header[1]+OSD_DATA_OFFSET(region[0].osd_format))*32 );

    //process each charactor until string ending('\0')
    while ( (c = ((BYTE *)pStr)[iStrLoc]) != '\0' ) {
        UINT16 curByte;
        UINT32 pixel_16;
        UINT32 pos;

        iStrLoc++;

        if (c == '\r') { //prefix characher:to use font_table2
            if ( (c = ((BYTE *)pStr)[iStrLoc])=='\0' )
                break;
            iStrLoc++;

			if ((pFont = get_font_entry(1,c))==NULL) continue;
        // mimitsai merge from dp2070/dp3240

        } else if( c == '\t' ) {        // yltseng v2.3
            if ( (c = ((BYTE *)pStr)[iStrLoc])=='\0' )
                break;
            iStrLoc++;

			if ((pFont = get_font_entry(2,c))==NULL) continue;
        } else {
            //get current char entry
			pFont = get_font_entry(0,c);
        }

        //start to process
        pos = 2;

        //get font information
        iFontWidth = (int)pFont[0];
        iFontHigh = (int)pFont[1];

        //start to draw
        for (j=0; j<iFontHigh; j++) {
        	BYTE ch;
        	curByte=0;

        	pOSD=pTopLine+xStart;
        	if ((p_scan==0) && (j%2==1))
        		pOSD=pBtmLine+xStart;

            for (i=0; i<(iFontWidth/16); i++) {

                ch = pFont[++pos];
                curByte=(ch<<8);
                ch = pFont[++pos];
                curByte|=ch;

				curByte = ((curByte & 0xF000)>>12) | ((curByte & 0x0F00)>>4) | ((curByte & 0x00F0)<<4) | ((curByte & 0x000F)<<12);

                pixel_16 = 0;

                for (k=0; k<16; k++) {
                    if ( (1<<k) & curByte ) {
                        pixel_16 = pixel_16 | (fgColor<<(k*2));
                    } else {
                        pixel_16 = pixel_16 | (bgColor<<(k*2));
                    }
                }

#ifdef NEW_DISPLAY_GOTO_OSD
				if (p_scan)
					pOSD[16*j+i]=pixel_16;
				else
					pOSD[16*(j/2)+i]=pixel_16;
#else//#ifdef NEW_DISPLAY_GOTO_OSD
				if (p_scan)
					pOSD[38*j+i]=pixel_16;
				else
					pOSD[38*(j/2)+i]=pixel_16;
#endif//#ifdef NEW_DISPLAY_GOTO_OSD
            }

            if (iFontWidth%16!=0)
            {
            	ch = pFont[++pos];
            	curByte = (  (ch & 0xF0)>>4 | (ch & 0x0F)<<4       ) ;
            	pixel_16 = 0;

                for (k=0; k<8; k++) {
                    if ( (1<<k) & curByte ) {
                        pixel_16 = pixel_16 | (fgColor<<(k*2));
                    } else {
                        pixel_16 = pixel_16 | (bgColor<<(k*2));
                    }
                }

#ifdef NEW_DISPLAY_GOTO_OSD
                                if (p_scan)
                                    pOSD[16*j+i]=pixel_16;
                                else
                                    pOSD[16*(j/2)+i]=pixel_16;
#else//#ifdef NEW_DISPLAY_GOTO_OSD
                if (p_scan)
                	pOSD[38*j+i]=pixel_16;
                else
                	pOSD[38*(j/2)+i]=pixel_16;
#endif//#ifdef NEW_DISPLAY_GOTO_OSD

            }
        }
		pTopLine+=(iFontWidth/16);
		pBtmLine+=(iFontWidth/16);
    }

}
**************************************************************************************/
#else //SDRAM_16Mb_Mode
//
// do_DispOSD0String
//      helper function of DispCookOSD0
#ifdef OSD_BMP_DISPLAY//feeling

/*
 * Description;
 *      Draw a 8 * 12 font size string in display osd0
 *
 * INPUT:
 *      xStart  -->  the string x start position, it ranges between 0 ~ 360,and the screen ranges between 0~720 pixel
 *      yStart  -->  the string y start position, it must be the even number
 *      *pStr    -->   the string
 *      fgColor    -->  the string font color
 *      bgColor  --> the background color the string
 *
 * Creator : feeling
 * Date :  2004-8-25
 *
 */
void do_DispOSD0LittleString(UINT32 xStart, UINT32 yStart, BYTE *pStr, BYTE fgColor, BYTE bgColor)
{
    #ifdef OSD_VARIABLE_TEMP_DISPLAY_BUF 
        osd_Draw_Bmp_Little_RegionString(xStart, yStart, pStr, fgColor, bgColor, temp_region);
	    return;
	#endif	
	
	BYTE  *buf;
    BYTE    *pFont, c,div=4;
    UINT32  iDispLoc, iStrLoc;
    int     i, j, k;
    int     iFontWidth, iFontHigh;
    
#ifdef DISP_REGION_BOTTOM
    UINT8 uiRegion = disp_region;
#else
	UINT8    uiRegion = 0;
#endif
    int     iRegionWidth = region[uiRegion].osd_w;

    //osd_tog_region(0, OSD_ON);  

    iStrLoc = 0;

    buf = (BYTE *)osd_temp_buf;
	iDispLoc = (yStart*iRegionWidth+xStart/2) *2;

    //process each charactor until string ending('\0')
    while ( (c = ((BYTE *)pStr)[iStrLoc]) != '\0' ) {
        BYTE curByte;
        UINT32 pixel2;
        UINT32 pos;

        iStrLoc++;

        if (c == '\r') { //prefix characher:to use font_table2
            if ( (c = ((BYTE *)pStr)[iStrLoc])=='\0' )
                break;

            iStrLoc++;
            if ((pFont = get_font_entry(1,c))==NULL) continue;
        }
	    else if(c>='a' && c<='z')
		{
    		pFont=get_font_entry(0,c-'a'+0xc0);
    		//printf("c=%c,c=%x\n",c,c);
		}
        else {
            //get current char entry
            pFont = get_font_entry(0,c);
        }

        //start to process
        pos = 3;
        //get font information
        iFontWidth = (int)pFont[0];
        iFontHigh = (int)pFont[1];



        //start to draw
        for (j=0; j<iFontHigh; j++) {
            //For every string line = 1 blank line(in pixel) + OSD_FONT_HEIGHT-line strings + 1 blank line

            //draw top line
            for (i=0; i<iFontWidth/2; i++) //access 2 pixel per time,that is to say 1 byte in 16 color mode
            {
                 BYTE c;
                 c=pFont[pos+i/4];
             	   pixel2 = 0;

	          	switch(i%4)
          	   	{
          	   	    case 0:
				        curByte=(c&0xc0)>>6;
				        break;
			        case 1:
				        curByte=(c&0x30)>>4;
	                     break;
	                case 2:
                        curByte=(c&0x0c)>>2;
                        break;
              	    case 3:
              		    curByte=(c&0x03);
              		    break;
          		}

          		for (k=0; k<2; k++) //two pixel every time
                {
                    if ( (1<<k) & curByte )
                    {
                		pixel2 = (pixel2 & (~( 0x0f<<k*4))) |(fgColor<<(k*4));//zhao add 2004-2-27 14:41
                    } else
                    {
                        if(bgColor != 0)//if color index is 0, no need to change the vlaue fo pixel8
                        	pixel2 = (pixel2& (~( 0x0f<<k*4))) | (bgColor<<(k*4));//zhao add 2004-2-27 14:41
                    }
           	    }
          		if((i % 2 == 0) &&(j % 2 == 0)) //four dots ---> one dot
                    buf[(iDispLoc+i)/2] = pixel2;
             		// printf("pTopLine=%x,pTopLine[%x]=%x\n",pTopLine+iDispLoc+i,iDispLoc+i,pTopLine[iDispLoc+i]);
            }


            iDispLoc += iRegionWidth;

   		    if(iFontWidth%8)
			    pos=pos+iFontWidth/8+1;
        	else
        		pos=pos+iFontWidth/8;
        }//for charactor heigh

         //move to next character and move up to first line of this string
        iDispLoc = iDispLoc + (iFontWidth/2) - (iRegionWidth*iFontHigh);
    } // end of while ( (c=((BYTE *)str)[unFontLoc])!='\0' )
}//end do_DispOSD0LittleString()


/*
 * Description;
 *      Draw a  16* 24 font size string in display osd0
 *
 * INPUT:
 *      xStart  -->  the string x start position, it ranges between 0 ~ 720
 *      yStart  -->  the string y start position, it must be the even number
 *      *pStr    -->   the string
 *      fgColor    -->  the string font color
 *      bgColor  --> the background color the string
 *
 * Creator : feeling
 * Date :  2004-8-19
 *
 */

void do_DispOSD0String(UINT32 xStart, UINT32 yStart, BYTE *pStr, BYTE fgColor, BYTE bgColor)
{
    #ifdef OSD_VARIABLE_TEMP_DISPLAY_BUF 
        osd_Draw_Bmp_RegionString(xStart, yStart, pStr, fgColor, bgColor, temp_region);
	    return;
	#endif	
    
	BYTE  *buf;
    BYTE    *pFont, c,div=4;
    UINT32  iDispLoc, iStrLoc;
    int     i, j, k;
    int     iFontWidth, iFontHigh;
    
    #ifdef DISP_REGION_BOTTOM
    	UINT8 uiRegion = disp_region;
	#else
	    UINT8  uiRegion = 0;
    #endif
    
    int     iRegionWidth = region[uiRegion].osd_w;

    //osd_tog_region(0, OSD_ON);  

    iStrLoc = 0;

    buf = (BYTE *)osd_temp_buf;

	iDispLoc = (yStart*iRegionWidth+xStart/2);

    //process each charactor until string ending('\0')
    while ( (c = ((BYTE *)pStr)[iStrLoc]) != '\0' ) {
        BYTE curByte;
        UINT32 pixel2;
        UINT32 pos;

        iStrLoc++;

        if (c == '\r') { //prefix characher:to use font_table2
            if ( (c = ((BYTE *)pStr)[iStrLoc])=='\0' )
                break;

            iStrLoc++;
            if ((pFont = get_font_entry(1,c))==NULL) continue;
        }
	else if(c>='a' && c<='z')
    {
		pFont=get_font_entry(0,c-'a'+0xc0);
		//printf("c=%c,c=%x\n",c,c);
    }
    else {
        //get current char entry
        pFont = get_font_entry(0,c);
    }

    //start to process
    pos = 3;
    //get font information
    iFontWidth = (int)pFont[0];
    iFontHigh = (int)pFont[1];

    //start to draw
    for (j=0; j<iFontHigh; j++) {
    //For every string line = 1 blank line(in pixel) + OSD_FONT_HEIGHT-line strings + 1 blank line
    //iDispLoc = (yStart*iRegionWidth)  + (xStart/2) ;

    //draw top line
    for (i=0; i<iFontWidth/2; i++) //access 2 pixel per time,that is to say 1 byte in 16 color mode
    {
        BYTE c;
        c=pFont[pos+i/4];
        pixel2 = 0;


      	switch(i%4)
  	   	{
  	   	    case 0:
		        curByte=(c&0xc0)>>6;
		        break;
	        case 1:
		        curByte=(c&0x30)>>4;
                 break;
            case 2:
                 curByte=(c&0x0c)>>2;
      		    break;
      	    case 3:
      		    curByte=(c&0x03);
      		    break;
  		}



  		for (k=0; k<2; k++) //two pixel every time
        	{
                if ( (1<<k) & curByte )
                	{
            		pixel2 = (pixel2 & (~( 0x0f<<k*4))) |(fgColor<<(k*4));//zhao add 2004-2-27 14:41
                	} else
                {
                    if(bgColor != 0)//if color index is 0, no need to change the vlaue fo pixel8
                    	pixel2 = (pixel2& (~( 0x0f<<k*4))) | (bgColor<<(k*4));//zhao add 2004-2-27 14:41
                }
       	 }

        buf[iDispLoc+i] = pixel2;//put pixel to osd temp buf
    }
        iDispLoc += iRegionWidth;//next line of a char

   		if(iFontWidth%8)
			pos=pos+iFontWidth/8+1;
        	else
        		pos=pos+iFontWidth/8;
        }//for charactor heigh

        //move to next character and move up to first line of this string
        iDispLoc = iDispLoc + (iFontWidth/2) - (iRegionWidth*iFontHigh);
    } // end of while ( (c=((BYTE *)str)[unFontLoc])!='\0' )
}//end do_DispOSD0String

#elif defined(USE_SMALL_FONT)//libing
void do_DispOSD0String(BYTE xStart, BYTE yStart, BYTE *pStr, BYTE fgColor, BYTE bgColor)
{
    UINT16  *buf;
    UINT32  iDispLoc;
    int     i, j, k;
    BYTE    *pFont, c;
    UINT32  iStrLoc=0;
    int  iFontWidth, iFontHigh;
	

    iDispLoc = 0;
	
    //process each charactor until string ending('\0')
    while ( (c = ((BYTE *)pStr)[iStrLoc]) != '\0' ) {
        BYTE curByte;
        UINT16 pixel4;
        UINT32 pos;
        UINT8 fourbit;

        //get font information
        iFontWidth = (int)pFont[0];
        iFontHigh = (int)pFont[1];
		if(iFontWidth ==12)
        {
        yStart = yStart - 0;    
        buf = (UINT16 *)(osd_temp_buf + yStart*38*8 + xStart*8 + iDispLoc*4);
        }
        else
        {
        yStart = yStart - 4;    
        buf = (UINT16 *)(osd_temp_buf + yStart*38*8 + xStart*8 + iDispLoc*4);
         }
        
        iStrLoc++;
        
        if (c == '\r') { //prefix characher:to use font_table2
            if ( (c = ((BYTE *)pStr)[iStrLoc])=='\0' )
                break;
			
            iStrLoc++;
			
			if ((pFont = get_font_entry(1,c))==NULL) continue;            
        } else {
            //get current char entry
			pFont = get_font_entry(0,c);
        }
		
        //start to process
        pos = 2;
        fourbit=1;

		
        //start to draw        
        for (j=0; j<iFontHigh; j++) {
        {
            for (i=0; i<iFontWidth/4; i++) 
            {
                BYTE ch;
                if(fourbit)
        		{		
                ch = (pFont[++pos])&0xf0;
                fourbit=0;
                }
                else
                {
                ch = (pFont[pos])<<4;
                fourbit=1;
                }               
                curByte = ((ch & 0xc0)>>6) | ((ch & 0x30)>>2);
                pixel4 = 0;
				
                for (k=0; k<4; k++) {          
                    if ( (1<<k) & curByte ) {          
                        pixel4 = pixel4 | (fgColor<<(k*4));
                    } else {
                        pixel4 = pixel4 | (bgColor<<(k*4));
                    }
                }			
                buf[152*j + i] = pixel4; //Bytes per line(37*16*4/8), DWORD/Line=74
          }
        }
} //for charactor heigh
if (iFontWidth==12)

	iDispLoc += (iFontWidth/6);//iRegionWidth;	
else
        iDispLoc += (iFontWidth/8);        
    } // end of while ( (c=((BYTE *)str)[unFontLoc])!='\0' )	
}

#else//OSD_BMP_DISPLAY
#ifdef USE_NEW_SCHINESE_OSD
void draw_disp_bitmap(const UINT8 *pFont, coordinate *start, dimension *in_dimension, font_palette *palette)
{
	UINT8 font_color = palette->font_color;
	UINT8 bkg_color = palette->background_color;
    UINT8 temp_color;
    
	UINT32 coordinate_x, coordinate_y;
	unsigned int font_width,font_height;
    
	unsigned int i, j, Bperpixel, shift_num, tempi;
	BYTE bEscapePixelNum;
	UINT32 pixels_in_first_byte, pixels_in_last_byte, pixels_in_byte, temp_pixels;
    
	UINT32 iDispLoc, disploc;
    UINT8 *buf;
    
    coordinate_x = start->x;
    coordinate_y = start->y;
	font_width = in_dimension->x_length;
	font_height = in_dimension->y_length;
    
    //OSD_FORMAT_16COLOR
	Bperpixel = 1;
	shift_num = 4;
    bEscapePixelNum = coordinate_x & 0x01;
    
	pixels_in_byte = 8/shift_num;
	pixels_in_first_byte = pixels_in_byte - bEscapePixelNum;
    pixels_in_last_byte = (font_width - pixels_in_first_byte) % pixels_in_byte;
    
    iDispLoc = (coordinate_y * 608 + coordinate_x) >> Bperpixel;
    disploc = 0;
    buf = osd_temp_buf;
    
    tempi = 0;
    
    for (i = 0; i < font_height; i++)
    {
        for (j = 0; j < font_width; j++)
        {
            tempi = (j + bEscapePixelNum) >> Bperpixel;
            
    		if (pFont[(j + disploc) >> 3] & (0x80 >> ((j + disploc) & 0x07)))
    		{
    		    temp_color = font_color;
    		}
    		else
    		{
    		    temp_color = bkg_color;
    		}
            
			if((bEscapePixelNum != 0) && (j == 0))  //coordinate_x is odd, so clear and then shift first pixel
			    buf[iDispLoc + tempi] = ((buf[iDispLoc + tempi] >> shift_num) << shift_num) | temp_color;			
			else			
			    buf[iDispLoc + tempi] = (buf[iDispLoc + tempi] << shift_num) | temp_color;
        }
        
		if(pixels_in_last_byte != 0)
		{
		    buf[iDispLoc + tempi] = (buf[iDispLoc + tempi] << (8 - pixels_in_last_byte * shift_num));		    
		    
		    //bkg-color pixels in last byte should be set bkg-color not 0
		    temp_pixels = pixels_in_byte - pixels_in_last_byte;
		    while(temp_pixels != 0)
		    {
		        buf[iDispLoc + tempi] |= bkg_color << (shift_num * (temp_pixels - 1));
		        temp_pixels--;
		    }
		}
        
        disploc += font_width ;
        iDispLoc += 608 >> Bperpixel;
    }
}

void do_DispOSD0String(BYTE xStart, BYTE yStart, BYTE *pStr, BYTE fgColor, BYTE bgColor)
{
    BYTE c;
    UINT32 iStrLoc;
    const BYTE *pFont;

    coordinate  temp_coordinate;
    dimension out_dimension;
    font_palette temp_palette;
    
    //buf = (UINT32 *)(osd_temp_buf + yStart*38*8 + xStart*8 + iDispLoc*4);
    //(iDispLoc *4)(byte) *2(pixel/byte) -> iDispLoc is times of 8(pixel)
    temp_coordinate.x = (xStart * 8) * 2;//(xStart * 8)(byte) * 2(pixel/byte) -> xStart is times of 16(pixel)
    temp_coordinate.y = yStart;//(38 * 8)(byte) * 2(pixel/byte)
    
	temp_palette.font_color = fgColor;
	temp_palette.background_color = bgColor;
    
    iStrLoc = 0;
    
    while ((c = ((BYTE *)pStr)[iStrLoc]) != '\0')
    {
        iStrLoc++;
        
        if (c == '\r')
        {
            if ((c = ((BYTE *)pStr)[iStrLoc]) == '\0')
                break;
            iStrLoc++;
			if ((pFont = get_font_entry(1, c)) == NULL)
                continue;
        }
        else if(c == '\t')
        {
            if ((c = ((BYTE *)pStr)[iStrLoc]) == '\0')
                break;
            iStrLoc++;
			if ((pFont = get_font_entry(2, c)) == NULL)
                continue;
        }
#ifdef USE_NEW_SCHINESE_OSD //liyl add 20060116
        else if (c == '\a')
        {
            if ((c = ((BYTE *)pStr)[iStrLoc]) == '\0')
                break;
            iStrLoc++;
            if ((pFont = get_font_entry(3, c)) == NULL)
                continue;
        }
        else if (c == '\f')
        {
            if ((c = ((BYTE *)pStr)[iStrLoc]) == '\0')
                break;
            iStrLoc++;
            if ((pFont = get_font_entry(4, c)) == NULL)
                continue;
        }
#endif
        else
        {
			if ((pFont = get_font_entry(0,c)) == NULL)
                continue;
        }
        
        out_dimension.x_length = pFont[0];
	    out_dimension.y_length = pFont[1];
        pFont +=3;

        if (hi_light_index >= 0)//liyl add 20060301
        {
            temp_coordinate.x += hi_light_index * out_dimension.x_length;
            hi_light_index = -1;
        }
        
        draw_disp_bitmap(pFont, &temp_coordinate, &out_dimension, &temp_palette);
        
        temp_coordinate.x += out_dimension.x_length;
    }
}
#else   //else=>  #ifdef USE_NEW_SCHINESE_OSD
void do_DispOSD0String(BYTE xStart, BYTE yStart, BYTE *pStr, BYTE fgColor, BYTE bgColor)
{
    UINT32  *buf;
    UINT32  iDispLoc;
    UINT32  i, j, k;
    BYTE    c;
    UINT32  iStrLoc=0;
    UINT32  iFontWidth, iFontHigh;
    const BYTE    *pFont;

    iDispLoc = 0;

    //process each charactor until string ending('\0')
    while ( (c = ((BYTE *)pStr)[iStrLoc]) != '\0' ) {
        BYTE curByte;
        UINT32 pixel8;
        UINT32 pos;

        buf = (UINT32 *)(osd_temp_buf + yStart*38*8 + xStart*8 + iDispLoc*4);
        iStrLoc++;

        if (c == '\r') { //prefix characher:to use font_table2
            if ( (c = ((BYTE *)pStr)[iStrLoc])=='\0' )
                break;

            iStrLoc++;

			if ((pFont = get_font_entry(1,c))==NULL) continue;
        // mimitsai merge from dp2070/dp3240

            } else if( c == '\t' ) {        // yltseng v2.3
            if ( (c = ((BYTE *)pStr)[iStrLoc])=='\0' )
                break;
            iStrLoc++;

			if ((pFont = get_font_entry(2,c))==NULL) continue;
        } else {
            //get current char entry
			pFont = get_font_entry(0,c);
        }

        //start to process
        pos = 2;

        //get font information
        iFontWidth = (int)pFont[0];
        iFontHigh = (int)pFont[1];

        //start to draw
        for (j=0; j<iFontHigh; j++) {
            for (i=0; i<(iFontWidth/8); i++) {
                BYTE ch;

                ch = pFont[++pos];
                curByte = ((ch & 0xc0)>>6) | ((ch & 0x30)>>2) | ((ch & 0x0c)<<2) | ((ch & 0x03)<<6);
                pixel8 = 0;

                for (k=0; k<8; k++) {
                    if ( (1<<k) & curByte ) {
                        pixel8 = pixel8 | (fgColor<<(k*4));
                    } else {
                        pixel8 = pixel8 | (bgColor<<(k*4));
                    }
                }
#ifndef SDRAM_16Mb_Mode
                buf[76*j + i] = pixel8; //Bytes per line(37*16*4/8), DWORD/Line=74
#else
                {
                    UINT32 q,r,x;

                    x=(yStart*38*8 + xStart*8 + iDispLoc*4)/4;
                    q=j+(i+x)/76;
                    r=(i+x)%76;

                    if (p_scan)
                    {
                    	pTopLine[76*j+r]=pixel8;
                    } else {
						if (j%2==0)
						{
							pTopLine[76*(q/2)+r]=pixel8;
						} else {
							pBtmLine[76*((q-1)/2)+r]=pixel8;
						}
                    }
                }
#endif
            } //for (i=0; i<iFontWidth/8; i++)
        } //for charactor heigh

        iDispLoc += (iFontWidth/8);
                
    } // end of while ( (c=((BYTE *)str)[unFontLoc])!='\0' )

}
#endif    //end=> #ifdef USE_NEW_SCHINESE_OSD
#endif//osd_bmp_display
#endif //SDRAM_16Mb_Mode



#ifdef DIV_GOTO_DISPLAY
/*****************************************
 *   DVD                   VCD/CD
 *page 0:                page 0:
 *   TRK: CHP               TRK
 *
 *page 1:                page 1:
 *   TRK: TIME             disc TIME
 *
 *page 2:                page 2:
 *   CHP: TIME             trk TIME
 *
 ****************************************/
//for page 0
#define GOTO_TRK0      0
#define GOTO_TRK0_VAL  4
#define GOTO_CHP0      10
#define GOTO_CHP0_VAL  14
//fo page 1
#ifdef MODIFY_DIV_GOTO_DISPLAY//20040224 for nintaus
#define GOTO_S_TIMER    4
#define GOTO_TIMER_VAL  8
#else
#define GOTO_S_TIMER    11
#define GOTO_TIMER_VAL  15
#endif
#define GOTO_TRK1      0
#define GOTO_TRK1_VAL  4
//page 2
#define GOTO_CHP2      0
#define GOTO_CHP2_VAL  4


#define TITLE          1
#define CHARPTER       2
#define TIME           3

#endif//DEVIDE_GOTO_DISPLAY

#ifdef NEW_DISPLAY_GOTO_OSD//add 2004-06-02
#define POS_DVD_TITLE   0
#define POS_DVD_CHAP    7
#define POS_TRACK       0
#define POS_TIME            3
#define OFFSET_TITLE    2
#define OFFSET_CHAP     2
#define OFFSET_TRACK    5
#endif//#ifdef NEW_DISPLAY_GOTO_OSD

//The english(not Chinese) display will be limited on language.
#define     MAX_ENG_WORDS 3

void tm2hms(UINT32 time,UINT8 *h,UINT8 *m,UINT8 *s)
{
	*h=time/3600;
	time=time%3600;
	*m=time/60;
	*s=time%60;
}


#ifdef NEW_SEARCH_OSD
   #include "display_aviq.h"
#else
   #include "display_hl.h"
#endif





#ifdef SUPPORT_BOOK
//Jeff 20020411
void DispUpdateMark(BYTE xStart, BYTE *pStr, BYTE bFocus)
{
	BYTE    fontColor, bkColor;
    #ifdef SHOW_12_BOOKMARK//libing 2005-4-26 19:03
	extern  BYTE    bookIndex;//libing 2005-6-23 21:57
	BYTE    i=bookIndex;
    #endif

	//Jeff 200204120
    #ifdef SDRAM_16Mb_Mode    //2004-4-12  00:45’≈”ÓM
	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR	
	 if (bFocus) {
		fontColor = 0;
		bkColor = 1;
	} else {
		fontColor = 1;
		bkColor = 0;
	}
	#else
	 if (bFocus) {
		fontColor = 0;
		bkColor = 2;
	} else {
		fontColor = 2;
		bkColor = 0;
	}
	#endif
   #else
	if (bFocus) {
		fontColor = DISP_ORANGE;
		bkColor = DISP_GBLUE;
	} else {
		fontColor = DISP_WHITE;
		bkColor = DISP_SHADOW;
	}
   #endif //end SDRAM_16Mb_Mode




    io_write("0");


	do_DispOSD0String(COOK_MARK_VAL+xStart, 0, pStr, fontColor, bkColor);//2004-4-12 12:48’≈”ÓM



	//Jeff 20020621
	//2-6-22 0:28 nono modified them.
#ifdef SHOW_12_BOOKMARK//libing 2005-4-26 19:03
    if(book[bookIndex][0]!=0)
    {	
	    if(i<12)
	    {
	    if(cd_type_loaded==CDDVD)
	    {
			    Print2OSDmem(STR_OS_ICON_T, 0, COOK_TRK+COOK_MARK_VAL+8);
			    Print2OSDmem(book[i][0], get_tt_info(DISP_TT_Ns), COOK_TRK_VAL+COOK_MARK_VAL+6);
			    Print2OSDmem(STR_OS_ICON_C, 0, COOK_CHP+COOK_MARK_VAL+4);
			    Print2OSDmem(book[i][1], get_tt_info(DISP_CH_Ns), COOK_CHP_VAL+COOK_MARK_VAL+2);
		    }
		    else
		    {			
			    Print2OSDmem(STR_OS_TRACK, 0, COOK_TRK+COOK_MARK_VAL+8);
		    if((cd_type_loaded==CDVCD20)||(cd_type_loaded==CDVCD10)||(cd_type_loaded==CDSVCD))
			    Print2OSDmem(book[i][0]-1, get_tt_info(DISP_TT_Ns), COOK_TRK_VAL+COOK_MARK_VAL+9);
		    else
			    Print2OSDmem(book[i][0], get_tt_info(DISP_TT_Ns), COOK_TRK_VAL+COOK_MARK_VAL+9);
		    }
	    }
    }
    else	
    {
		{
	        if(cd_type_loaded==CDDVD)//LIBING 2005-4-26 23:41
	        {
		        Print2OSDmem(STR_OS_ICON_T, 0, COOK_TRK+COOK_MARK_VAL+8);
		        Print2OSDmem(get_tt_info(DISP_TT), get_tt_info(DISP_TT_Ns), COOK_TRK_VAL+COOK_MARK_VAL+6);
		        Print2OSDmem(STR_OS_ICON_C, 0, COOK_CHP+COOK_MARK_VAL+4);
		        Print2OSDmem(get_tt_info(DISP_CH), get_tt_info(DISP_CH_Ns), COOK_CHP_VAL+COOK_MARK_VAL+2);
	        }
	        else
	        {
			        Print2OSDmem(STR_OS_TRACK, 0, COOK_TRK+COOK_MARK_VAL+8);
			        Print2OSDmem(disp_trk_now, get_tt_info(DISP_TT_Ns), COOK_TRK_VAL+COOK_MARK_VAL+9);
	        }
    	}
	}
#else
	if(cd_type_loaded==CDDVD)//LIBING 2005-4-26 23:41
	{
		Print2OSDmem(STR_OS_TT, 0, COOK_TRK+COOK_MARK_VAL+8);
		Print2OSDmem(get_tt_info(DISP_TT), get_tt_info(DISP_TT_Ns), COOK_TRK_VAL+COOK_MARK_VAL+7);
		Print2OSDmem(STR_OS_CHP, 0, COOK_CHP+COOK_MARK_VAL+4);
		Print2OSDmem(get_tt_info(DISP_CH), get_tt_info(DISP_CH_Ns), COOK_CHP_VAL+COOK_MARK_VAL+3);
	}
	else
	{
		Print2OSDmem(STR_OS_TRACK, 0, COOK_TRK+COOK_MARK_VAL+7);
		Print2OSDmem(disp_trk_now, get_tt_info(DISP_TT_Ns), COOK_TRK_VAL+COOK_MARK_VAL+9);
	}
	#endif//#ifdef SHOW_12_BOOK_MARK
}
#endif //#ifndef SUPPORT_BOOK

//
// DispPolling
//
//      input : bReset  1   -> force osd0_state to INIT state
//
void DispPolling(BYTE bReset)
{
int down_offset_num = 4;
int up_offset_num = 2; 
#ifdef SUPPORT_SW_OSD_SCALING
    if((GET_TV_RESOLUTION()  == HD_720)) {
        down_offset_num = 8;
        up_offset_num =  4;    
    }
    else if((GET_TV_RESOLUTION()  == HD_1080)) {
        down_offset_num = 12;
        up_offset_num =  6;    
    }
#endif
        #define    down_offset    down_offset_num
        #define    up_offset        up_offset_num


#ifdef DISP_REGION_BOTTOM
    UINT8 uiRegion = OSD_GetTrueDispRegion();
    #ifdef OSD_VARIABLE_TEMP_DISPLAY_BUF
        osd_tog_region(temp_region,OSD_OFF);
    #endif
#else
    UINT8 uiRegion = 0;
#endif//DISP_REGION_BOTTOM

//    printf("osd0_state=%d\n",osd0_state);
    if(bReset==2)
    {
        if( (osd0_state!=OSD0_STATE_FADE_IN)&&(osd0_state!=OSD0_STATE_FADE_OUT) )
            return;
    }
    if (bReset==1) {
        osd0_state = OSD0_STATE_INIT;
    }
#ifdef SDRAM_16Mb_Mode
    if (bReset==3)
    {
    	osd0_state = OSD0_STATE_FADE_IN;
    	osd0_show_line = region[uiRegion].osd_h;
        osd0_hold_count = 0;
    }
#endif
    switch (osd0_state) {
	case OSD0_STATE_INIT:
		osd0_show_line = 0;
		DispCookOSD0(1);
		//DispCookOSD0(1.. will change osd0_state to OSD0_STATE_HIDE
		break;

	case OSD0_STATE_HIDE:
		osd0_show_line = 0;
		#ifdef EASTECH_DVD//?
		//osd0_state = OSD0_STATE_FADE_IN;//lyc 2005-5-8 9:21 it's for make not show the display when a song is finished
		#else
		osd0_state = OSD0_STATE_FADE_IN;
		#endif
		break;

	case OSD0_STATE_FADE_IN:
		//            osd0_slow_down++;
		//            if (osd0_slow_down > DISP_SLOW_DOWN)
		{
			//                osd0_slow_down = 0;

			if (osd0_show_line < region[uiRegion].osd_h) {
				osd0_show_line += down_offset;
			} else {
				osd0_show_line = region[uiRegion].osd_h;
				osd0_hold_count = 0;
				osd0_state = OSD0_STATE_FULL_SHOW;
			}
			osd_Move2OSD0(osd0_show_line);
		}

		break;

	case OSD0_STATE_FULL_SHOW:
		osd_Move2OSD0(osd0_show_line);
		break;

	case OSD0_STATE_FADE_OUT:
		{
			//osd0_slow_down = 0;

			if (osd0_show_line > 1) {
				osd0_show_line -= up_offset;
			} else {
				osd0_show_line = 0;
				osd0_hold_count = 0;
				osd0_state = OSD0_STATE_HIDE;
				//t_disp = 0;
			}
			//osd_ClearOSD0(osd0_show_line, osd0_show_line+up_offset);
			osd_Move2OSD0(osd0_show_line);
#ifdef SDRAM_16Mb_Mode
			osd_tog_region(0,OSD_OFF);
#endif
		}
		break;
    } //switch (osd0_state)
#ifdef SUPPORT_SW_OSD_SCALING
    if( ((GET_TV_RESOLUTION()  == HD_720) || (GET_TV_RESOLUTION()  == HD_1080)) && IS_OSD_SCALE_BUF_OK() ) {

        t_osd_region *region_pointer = &region[0];
        DrawDimension scale_section;
        scale_section.draw_start.x = 0;
        scale_section.draw_start.y = 0;
        scale_section.draw_dimension.x_length = region_pointer->osd_visible_w;
        scale_section.draw_dimension.y_length = region_pointer->osd_h;
        osd_region_scaling(0, &scale_section);
        
    }
#endif
    
}



void DispFadeIn()
{
    //printf("DispFadeIn:osd0_state=%d\n", osd0_state);

    if(Is_JPEG_STATE())//for jpeg fadeIn
    {
    #ifdef OSD_BMP_DISPLAY
		osd0_show_line = region[disp_region].osd_h;
    #else
    		osd0_show_line = region[0].osd_h;
    #endif
		osd0_state =OSD0_STATE_FULL_SHOW;
		FSGUI_JpgUpdateOSD();

    }
    else
		if( (osd0_state==OSD0_STATE_INIT)||(osd0_state==OSD0_STATE_HIDE) )
		{
			DispPolling(1);
			osd0_state = OSD0_STATE_FADE_IN;
		}
}



void DispFadeOut()
{
    #ifdef MP3_NO_DISPLAY   //2004-4-22 04:42’≈”ÓP
    if(Is_MP3_STATE())
    {
        FSGUI_FillFrameBuf(25,256,160,20,BK_GROUNDY, BK_GROUNDCRCB );
	FSGUI_FillFrameBuf(260,256,12,12,BK_GROUNDY, BK_GROUNDCRCB );// caohui 2004-4-22 21:00
    }
   #endif
    //printf("DispFadeOut:osd0_state=%d\n", osd0_state);
    t_disp = 0;
    if(Is_JPEG_STATE())//for jpeg fadeOut
    {
		osd0_show_line = 0;
		osd0_state =OSD0_STATE_FADE_OUT;

		DispPolling(0);
    }
    else
		if(osd0_state==OSD0_STATE_FULL_SHOW)
		{
			//        osd0_slow_down = 0;
			osd0_state = OSD0_STATE_FADE_OUT;
		}

	//maoyong for avoid bar twinkle when KEYBOARD show out. 2004.02.25
#ifdef DISPLAY_MENU_BUG_FIX
    osd_tog_region(0,OSD_OFF);
#endif
	#ifdef	VIRTUAL_KEYBOARD
	osd_tog_region(0,OSD_OFF);
	#endif
	//feeling for avoid bar twinkle when Thumbnail
#ifdef OSD_BMP_DISPLAY
	osd_tog_region(disp_region,OSD_OFF);
#endif
}




