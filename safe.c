/*nono 2-5-20 17:25 modified for differenrt customer with different screen_saver */
//terry,2004/2/6 11:42AM,test condition....



#include "user_init.h"
#include "memmap0.h"    // 2004/08/26 yltseng
#include "global.h"
#include "sio.h"
#include "func.h"
#include "kernel.h"
#include "timer.h"
#include "viddec.h"
#include "setup.h"
#ifdef PMP_UI
#include "fsNAV_PMP.h"/////////yangli 2005/8/2
#include "fsNAV.h"
#endif

#include "osd.h"
#include "vpp.h"
#include "ircode.h"//lijd 2005-6-16 21:26

#if defined(SUPPORT_OTHER_FILES_SSCREEN)&&defined(REALCOLOR_SCREENSAVER)
#include "fsNAV.h"
#endif

//#undef  SAFE_WAIT_TIME
//#define SAFE_WAIT_TIME 500
//#undef SAFE_POWEROFF_WAIT_TIME
//#define SAFE_POWEROFF_WAIT_TIME 500

#ifdef REALCOLOR_QSI //liulifeng add 2004-7-12 13:00
extern const UINT32 *osd__pal[];
extern const UINT32 palette_256color_sreensaver[5][256];
#endif

#ifdef EASTWIN
extern UINT8 bIS_LOWBAT;		// Kevin Sep 10,04 
#endif

#ifndef NO_SHOW_PIC_SAVER//lizhx 20040505

#include "safe_include.c"
//nono move to safe_include.c

#endif//NO_SHOW_PIC_SAVER

#ifdef SUPPORT_DVB_GUI_NEW 
#include "..\dvb_h\dvb_func.h"
#endif

//========================================================================
// var. declare
//========================================================================
//slow down screen saver image moving speed
UINT32 save_srn_start_t;
UINT8  safe_on=0; //0:system is active, 1:system enter screen-saver, 2:exit screen-saver
INT8   safeMode;
BYTE   safeForceEnter=0;
BYTE   safe_state=0;

static UINT32 s_uOSDAddressBackUp;
void BackUpOSDAddress(UINT32 uOSDAddress)
{
    s_uOSDAddressBackUp = uOSDAddress;
}

UINT32 GetOSDBackUpAddress()
{
    return s_uOSDAddressBackUp;
}

enum {
    SAFE_INIT=0,
    SAFE_DISPLAYING=1,
};


#ifdef NO_SHOW_PIC_SAVER//lizhx 20040505
#undef OSD_SAVER_W
#undef OSD_SAVER_H
#define OSD_SAVER_W     56
#define OSD_SAVER_H     24
#endif


/*
#define NORMAL_HEADER   0
#define EQ_HEADER       1
#define SETUP_HEADER    2
#define NES_HEADER      3
*/

#ifdef NODISC_SHOW_IN_DIFF_REGION
extern void nodisc_osd_init(void);//for warning
#endif
extern void setup_ExitPage(void);//for warning
extern BYTE osd0_state;
extern BYTE header_id;
extern const UINT8 osd_header_offset[8];


#ifdef NEW_OSD_DRIVER
extern void wait_v_blank(void);
extern void osd_create_region1(UINT8 region_index, int X, int Y, t_osd_region *prev,BYTE bColorMode,BYTE bScanMode);
#else
extern void osd_create_region1(t_osd_region*, int, int, t_osd_region*, BYTE, BYTE);
extern void osd_init_screensaver(void);
extern void osd_draw_256color_bmp(int,int, const BYTE*,BYTE);
extern void ENABLE_OSD(void);
extern void DISABLE_OSD(void);
#endif

extern void DispPolling(BYTE bReset);
extern int dsp3_decompress(const BYTE*, BYTE*);
extern void SetOsdCol(UINT8, UINT8, UINT8, UINT32);
extern void DispFadeOut();

extern BYTE setup_GetSSaveType();
#ifdef CD_PLAYER
extern void osd_init_cdplayer();
#endif

#ifdef VIRTUAL_KEYBOARD
extern BYTE KeyID;
extern void osd_draw_virtual_keyboard(int xStart, int yStart,BYTE r);   
extern void hl_keyboard_button(BYTE KeyID);
#endif

#ifdef NEWSTYLE_WINDOW
extern void exit_browse_func(void);
#endif

#if defined(SUPPORT_MP4_SUBTITLE) && defined(SCRN_SAVER_WHEN_PAUSE)
extern int supInitSubtitle(void);
#endif

void DrawOsdScreenSaver(UINT32 xPos, UINT32 yPos);
void ChangeColorTable(void);
void GetNewSaverLoc(void);
void MovePointer(void);
void SetMovePointer(UINT8 reg,UINT16 reg_x,UINT16 reg_y);//nono 2004-5-4 12:23
void DisplayScreenSaver(void);
void ExitOsdScreenSaver(void);
void InitOsdScreenSaver(void);
void ColorDisplay(void);

#if (defined(DVB_SETUP)&&!defined(SUPPORT_DVD_OSD)&&defined(OSD_SCREEN_SAVER)) //xsyan add
static void enable_osd_saver(void);
#endif

#define OSD_DATA_OFFSET(f)      (osd_header_offset[(f)&OSD_FORMAT_MASK])
#define OBV_BASE                (SDRAM_BASE + regs0->osd_base_addr*1024)
#define get_osdbuf_baseptr()    ((void *)OBV_BASE)



static const BYTE Pattern_Saver[] =
{
    0xff,       //0000-->11111111
    0xfd,       //0001-->11111101
    0xf7,       //0010-->11110111
    0xf5,       //0011-->11110101
    0xdf,       //0100-->11011111
    0xdd,       //0101-->11011101
    0xd7,       //0110-->11010111
    0xd5,       //0111-->11010101
    0x7f,       //1000-->01111111
    0x7d,       //1001-->01111101
    0x77,       //1010-->01110111
    0x75,       //1011-->01110101
    0x5f,       //1100-->01011111
    0x5d,       //1101-->01011101
    0x57,       //1110-->01010111
    0x55,       //1111-->01010101
};

#define __palette4F(G,B,R,A) \
        (((UINT32)((G) & 0xff) << 24) | ((UINT32)((B) & 0xff) << 16) | ((UINT32)((R) & 0xff) << 8) | ((A) & 0xff))

#ifdef COLORFUL_SCREENSAVER
#define PAL4_YELLOW     __palette4F(198, 0, 198, 0xff)        //yellow
#define PAL4_BLUE       __palette4F(128, 192, 0, 0xff)        //blue

#define PAL4_GREEN1     __palette4F(255, 0, 0, 0xff)         //green
#define PAL4_WHITE      __palette4F(129, 163, 242, 0xff)  //white

#define PAL4_RED        __palette4F(10, 140, 216, 0xff)        //red
#define PAL4_YELLOW     __palette4F(198, 0, 198, 0xff)        //yellow

#define PAL4_ORAGNGE    __palette4F(103, 0, 206, 0xff)         //orange
#define PAL4_GREEN2     __palette4F(255, 0, 0, 0xff)         //green

#define PAL4_PINK       __palette4F(40,148,255, 0xff)       //pink        //xulf0721
#define PAL4_PURPEL1    __palette4F(58,215,176, 0xff)         //purpel
#define PAL4_PURPEL2    __palette4F(68,138,68, 0xff)        //purpel


#else
#define PAL4_ORIGIN     __palette4F(0xa2, 0x2c, 0x8e, 0xff)
#define PAL4_WHITE      __palette4F(0xff, 0x80, 0x80, 0xff)
#define PAL4_LGREEN     __palette4F(177, 141, 73, 0xff)
#define PAL4_PURPEL     __palette4F(136, 165, 182, 0xff)
#define PAL4_BLUE       __palette4F(107, 187, 115, 0xff)
#endif

int    *safeVar;
BYTE   *gpImgAddr;
#define nSaverLocX      (safeVar[0])
#define nSaverLocY      (safeVar[1])
#define nSaverW         (safeVar[2])
#define nSaverH         (safeVar[3])
#define nSaverOffsetX   (safeVar[4])
#define nSaverOffsetY   (safeVar[5])
#define nSaverColor     (safeVar[6])
#define SAFEMAXVAR      (7)

void SetMovePointer(UINT8 reg,UINT16 reg_x,UINT16 reg_y)
{
    UINT16* pOSDHeader1 = (UINT16*)(get_osdbuf_baseptr() + region[reg].osd_header[0] * 32);
    UINT16* pOSDHeader2 = (UINT16*)(get_osdbuf_baseptr() + region[reg].osd_header[1] * 32); 
    

    wbe16(pOSDHeader1 + 4, reg_y);
    wbe16(pOSDHeader2 + 4, reg_y);
    wbe16(pOSDHeader1 + 5, reg_x);
    wbe16(pOSDHeader2 + 5, reg_x);

#ifdef SUPPORT_SW_OSD_SCALING
    if( ((GET_TV_RESOLUTION()  == HD_720) || (GET_TV_RESOLUTION()  == HD_1080)) && IS_OSD_SCALE_BUF_OK() ) {
        UINT16* pScalOsdHder1 = (UINT16*)(get_osdbuf_baseptr() + scaling_region[reg].osd_header[0] * 32);
        UINT16* pScalOsdHder2 = (UINT16*)(get_osdbuf_baseptr() + scaling_region[reg].osd_header[1] * 32); 
        
        wbe16(pScalOsdHder1 + 4, reg_y);
        wbe16(pScalOsdHder2 + 4, reg_y);
        wbe16(pScalOsdHder1 + 5, reg_x);
        wbe16(pScalOsdHder2 + 5, reg_x);
    }
 
#endif


//  printf("pHeader1Row = %x\n", pHeader1Row);
//  printf("val = %x\n", *pHeader1Row);
}

void MovePointer()
{
    UINT16 nCol, nRow;

    nRow = nSaverLocY & 0x3ff; // Row
    nCol = nSaverLocX & 0x3ff;

    SetMovePointer(0,nCol,nRow);

//  printf("pHeader1Row = %x\n", pHeader1Row);
//  printf("val = %x\n", *pHeader1Row);
}


#ifdef REALCOLOR_SCREENSAVER
void InitOsdScreenSaver(void)
{
    // force display off
    while (!((osd0_state == 1) || (osd0_state == 0)))
        DispPolling(1);

    disable_video();
    DISABLE_OSD();

    #ifdef ALCO_MODIFY_PAL_OSD
    if(getVPP_TVsystem()/*old_vppsetup_tv_system*/ == 1)
        regs0->osd_base_addr=JPEG_YA;
    #endif
    
    safeVar = (int*)(SDRAM_BASE + (TEMPYA * 1024));
    
    // setup first free address
    //osd_free = addr_vxvy(0,0);

    // get saver size
    nSaverW = OSD_SAVER_W;
    nSaverH = OSD_SAVER_H;

    if ((nSaverW % 16) != 0)
        nSaverW = (nSaverW / 16 + 1) * 16;

    if ((nSaverW % 2) != 0)
        nSaverH += 1;

    // reset saver offset
    nSaverOffsetX = 1;
    nSaverOffsetY = 1;
    nSaverLocX = 2;
    nSaverLocY = 2;
    nSaverColor = 0;

    osd__pal[4] = palette_256color_sreensaver[nSaverColor];//jhuang 2004/8/2
    osd_init_screensaver();
//  osd_create_region1(&region[0], 0, 0, NULL, OSD_FORMAT_4COLOR, OSD_NONINTERLACED);
   
    
    osd_draw_256color_bmp(0, 0, (BYTE*)realcolor_saver,0);
    
    //SetOsdCol(0, 0, 0,0x000000ff);//black color
#ifdef COLORFUL_SCREENSAVER       //xulf0722
    ColorDisplay();
#endif

#if (defined(DVB_SETUP)&&!defined(SUPPORT_DVD_OSD)&&defined(OSD_SCREEN_SAVER)) //xsyan add
    enable_osd_saver();
#else
    ENABLE_OSD();
#endif
}
void DisplayScreenSaver(void)
{
    //change X, Y-axes position

    GetNewSaverLoc();
#ifndef REALCOLOR_QSI //liulifeng add 2004-7-12 13:00   
    delay_1ms(8);
#endif
    //move start pointer
    MovePointer();

#ifdef SAFE_AUTO_POWEROFF
    {
        unsigned rtc,diff;      // zhangyu ,3-10-2 10:40
        
        rtc = get_rtc_val();
        diff=rtc-save_srn_start_t;
        if (diff > SAFE_POWEROFF_WAIT_TIME) 
        { 
            powerdown_time_counter=1;//nono add.2006-4-28 21:54
            //call_ir_func(IRC_POWER);//lijd 2005-6-16 21:25 
        }else
            powerdown_time_counter=0;//nono add.2006-4-28 21:54
    }
#endif

}


#ifdef REALCOLOR_QSI //liulifeng add 2004-7-12 13:00
//extern const UINT32 *osd__pal[];//jhuang move top 2004/8/2
//extern const UINT32 palette_256color_sreensaver[5][256];//jhuang move top
//const BYTE change_realcolor=0;

void ChangeColor_256real ( void )
{
    int id;
     nSaverColor++;
    if (nSaverColor >= 5)
        nSaverColor = 0;
    osd__pal[4] = palette_256color_sreensaver[nSaverColor];

    for ( id = 0 ;id < 256 ; id++)    SetOsdCol ( 0 , 0 , id , osd__pal[4][id] );
    //osd_init_screensaver();
    //delay_1ms(13);
    delay_1ms(18);//jhuang 2004/8/2
    osd_draw_256color_bmp(0, 0, (BYTE*)realcolor_saver[nSaverColor],0);

}

#endif

void GetNewSaverLoc()
{
    //change X-axes position
    if (nSaverOffsetX > 0)
    {
        if ((nSaverLocX + nSaverW / 2 + nSaverOffsetX) > (720 / 2 - 1))
        {
            nSaverOffsetX *= (-1);
    #ifdef REALCOLOR_QSI //liulifeng add 2004-7-12 13:00
            ChangeColor_256real ();
            //change_realcolor=1;

    #endif
        }
        nSaverLocX += nSaverOffsetX;
    }
    else
    {
        if ((nSaverLocX + nSaverOffsetX) < 1)
        {
            nSaverOffsetX *= (-1);
        #ifdef REALCOLOR_QSI //liulifeng add 2004-7-12 13:00
            ChangeColor_256real ();
            //change_realcolor=1;
        #endif
        }
        nSaverLocX += nSaverOffsetX;
    }

    //change Y-axes position
    if (nSaverOffsetY > 0)
    {
        UINT32  ySize;
        if ( getVPP_TVsystem()==1) { //Jeff 20030827
            ySize = 576;
        } else {
            ySize = 480;
        }
        if (p_scan == 0)
        {
            if ((nSaverLocY + nSaverH / 2 + nSaverOffsetY) > (ySize / 2 - 1))
            {
                nSaverOffsetY *= (-1);
            #ifdef REALCOLOR_QSI //liulifeng add 2004-7-12 13:00
            ChangeColor_256real ();
            //change_realcolor=1;
            #endif
            }
        }
        else
        {
            if ((nSaverLocY + nSaverH + nSaverOffsetY) > (ySize - 1))
            {
                nSaverOffsetY *= (-1);
            #ifdef REALCOLOR_QSI //liulifeng add 2004-7-12 13:00
            ChangeColor_256real ();
            //change_realcolor=1;
            #endif
            }
        }
        nSaverLocY += nSaverOffsetY;
    }
    else
    {
        if ((nSaverLocY + nSaverOffsetY) < 1)
        {
            nSaverOffsetY *= (-1);
        #ifdef REALCOLOR_QSI //liulifeng add 2004-7-12 13:00
            ChangeColor_256real ();
            //change_realcolor=1;
        #endif
        }
        nSaverLocY += nSaverOffsetY;
    }
}

#else
void DecompressOSDPic()
{
    safeVar = (int*)(SDRAM_BASE + (TEMPYA * 1024));
        
    gpImgAddr = (BYTE*)(SDRAM_BASE + (TEMPYA * 1024) + SAFEMAXVAR *4 );
    #ifndef NO_SHOW_PIC_SAVER//lizhx 20040505
	#ifdef SUPPORT_TWO_SAFELOGO_FOR_DVD_DVB    
	extern UINT8 DVD2DVB_switch_flag;
	if((Is_Dvb_State())||(DVD2DVB_switch_flag == 1)) 
	{
		dsp3_decompress((const BYTE *)romimg_OSD_DVB_Saver, gpImgAddr);  	}
	else
	{
                 dsp3_decompress((const BYTE *)romimg_OSDSaver, gpImgAddr);  
	}
 	 #else//else=>#ifdef SUPPORT_TWO_SAFELOGO_FOR_DVD_DVB 
    dsp3_decompress((const BYTE *)romimg_OSDSaver, gpImgAddr);  
	 #endif//end=>#ifdef SUPPORT_TWO_SAFELOGO_FOR_DVD_DVB 
    #endif
}

void InitOsdScreenSaver(void)
{
    // force display off
    while (!((osd0_state == 1) || (osd0_state == 0)))
        DispPolling(1);

    disable_video();
    DISABLE_OSD();

    // setup first free address
    osd_free = addr_vxvy(0,0);

    DecompressOSDPic();

    // get saver size
#ifdef SUPPORT_SW_OSD_SCALING
    scaling_t_osd_region *scale_region_p = &scaling_region[0];
    if( ((GET_TV_RESOLUTION()  == HD_720) || (GET_TV_RESOLUTION()  == HD_1080)) && IS_OSD_SCALE_BUF_OK() ) {
        nSaverW = OSD_SAVER_W*(scale_region_p->ratio.x_dividend)/(scale_region_p->ratio.x_divisor);
        nSaverH = OSD_SAVER_H*(scale_region_p->ratio.y_dividend)/(scale_region_p->ratio.y_divisor);
    }
    else
#endif
    {
        nSaverW = OSD_SAVER_W;
        nSaverH = OSD_SAVER_H;
    }

    if ((nSaverW % 16) != 0)
        nSaverW = (nSaverW / 16 + 1) * 16;

    if ((nSaverW % 2) != 0)
        nSaverH += 1;

    // reset saver offset
#ifdef SUPPORT_SW_OSD_SCALING
    if(GET_TV_RESOLUTION()  == HD_720) {
        nSaverOffsetX = 2;
        nSaverOffsetY = 2;
    }
    else if(GET_TV_RESOLUTION()  == HD_1080) {
        nSaverOffsetX = 2;
        nSaverOffsetY = 2;
    }        
    else 
#endif
    {
        nSaverOffsetX = 1;
        nSaverOffsetY = 1;
    }    
    nSaverLocX = 2;
    nSaverLocY = 2;
    nSaverColor = 0;
#ifdef ALCO_DVD_UI //shenyj modify 2006-9-7 08:56ÏÂÎç
    region[0].osd_w = nSaverW * 2 / 8; // bytes
    region[0].osd_h = nSaverH;
    
#ifdef SCREENSAVER_ZOOM_IN_2
        header_id = NES_HEADER;//NORMAL_HEADER;
#else
    header_id = NORMAL_HEADER;
#endif
        
#ifdef NEW_OSD_DRIVER
    osd_create_region1(0, 0, 0, NULL, OSD_FORMAT_4COLOR, OSD_INTERLACED);
#else
    osd_create_region1(&region[0], 0, 0, NULL, OSD_FORMAT_4COLOR, OSD_INTERLACED);
#endif    

    DrawOsdScreenSaver(0, 0);
    SetOsdCol(0, 0, 0,0x000000ff);//black color
#else
    //joshua, 20050823, modified osd initial function of screensaver
    osd_init_screensaver();   
    DrawOsdScreenSaver(0, 0);
#endif    

    ColorDisplay();

#if (defined(DVB_SETUP)&&!defined(SUPPORT_DVD_OSD)&&defined(OSD_SCREEN_SAVER)) //xsyan add
    enable_osd_saver();
#else
    ENABLE_OSD();
#endif
}

void DisplayScreenSaver(void)
{
    //change X, Y-axes position
    GetNewSaverLoc();
    #ifdef USE_SINGLE_COLOR_SCREENSAVER
    SetOsdCol(0, 0, 3, __palette4F(128, 192, 0, 0xff));
    #endif   //end USE_SINGLE_COLOR_SCREENSAVER
    //move start pointer
    MovePointer();

#ifdef SAFE_AUTO_POWEROFF
    {
        unsigned rtc,diff;      // zhangyu ,3-10-2 10:40
        
        rtc = get_rtc_val();
        diff=rtc-save_srn_start_t;


        if (diff > SAFE_POWEROFF_WAIT_TIME) 
        { 
            powerdown_time_counter=1;//nono add.2006-4-28 21:54
            //call_ir_func(IRC_POWER);//lijd 2005-6-16 21:25 
        }else
            powerdown_time_counter=0;//nono add.2006-4-28 21:54
    }
#endif
}


void GetNewSaverLoc()
{
    //change X-axes position
    if (nSaverOffsetX > 0)
    {
        INT32  xSize = 720; 

#ifdef SUPPORT_SW_OSD_SCALING
        if(GET_TV_RESOLUTION()  == HD_720) {
            xSize = 1280;
        }
        else if(GET_TV_RESOLUTION()  == HD_1080) {
            xSize = 1920;
        }
#endif
        
        if ((nSaverLocX + nSaverW / 2 + nSaverOffsetX) > (xSize / 2 - 1))
        {
            nSaverOffsetX *= (-1);
            ChangeColorTable();
        }
        nSaverLocX += nSaverOffsetX;
        #ifdef NO_SHOW_PIC_SAVER//lizhx 20040505
        PrintOsdMsg(STR_OS_DVD, REGION0, 1,0);
        #endif
    }
    else
    {
        if ((nSaverLocX + nSaverOffsetX) < 1)
        {
            nSaverOffsetX *= (-1);
            ChangeColorTable();
        }
        nSaverLocX += nSaverOffsetX;
        #ifdef NO_SHOW_PIC_SAVER//lizhx 20040505
        PrintOsdMsg(STR_OS_DVD, REGION0, 1,0);
        #endif
    }

    //change Y-axes position
    if (nSaverOffsetY > 0)
    {
        INT32  ySize;
        if ( getVPP_TVsystem()==1) { //Jeff 20030827
            ySize = 576;
        } else {
            ySize = 480;
        }
        
#ifdef SUPPORT_SW_OSD_SCALING
        if(GET_TV_RESOLUTION()  == HD_720) {
            ySize = 720;
        }
        else if(GET_TV_RESOLUTION()  == HD_1080) {
            ySize = 1080;
        }
#endif
        
        if (p_scan == 0)
        {
            if ((nSaverLocY + nSaverH / 2 + nSaverOffsetY) > (ySize / 2 - 1))
            {
                nSaverOffsetY *= (-1);
                ChangeColorTable();
            }
        }
        else
        {
            if ((nSaverLocY + nSaverH + nSaverOffsetY) > (ySize - 1))
            {
                nSaverOffsetY *= (-1);
                ChangeColorTable();
            }
        }
        nSaverLocY += nSaverOffsetY;
        #ifdef NO_SHOW_PIC_SAVER//lizhx 20040505
        PrintOsdMsg(STR_OS_DVD, REGION0, 1,0);
        #endif
    }
    else
    {
        if ((nSaverLocY + nSaverOffsetY) < 1)
        {
            nSaverOffsetY *= (-1);
            ChangeColorTable();
        }
        nSaverLocY += nSaverOffsetY;

        #ifdef NO_SHOW_PIC_SAVER//lizhx 20040505
        PrintOsdMsg(STR_OS_DVD, REGION0, 1,0);
        #endif


    }
}

#endif

void ExitOsdScreenSaver(void)
{
    enable_video();
    
    #if defined(SUPPORT_OTHER_FILES_SSCREEN)&&defined(REALCOLOR_SCREENSAVER)
    //if(Is_JPEG_STATE()) //mark it 04/12/09
        regs0->osd_base_addr=GetOSDBackUpAddress();
    #endif
    
#ifdef DYNAMIC_SPECTRUM
    if(bEqDisplay)
        Show3dspectrum();
    else
#endif
    #ifdef NODISC_SHOW_IN_DIFF_REGION
    if(system_state == SYSTEM_NODISC)
      nodisc_osd_init();
    else
    #endif 
    osd_init();

#if defined(SUPPORT_MP4_SUBTITLE) && defined(SCRN_SAVER_WHEN_PAUSE) //zhongshan for after screen saver sup not init 2005-7-30 15:28
	if(GetCurrentFileType() == CDROM_MP4)	//linrc update 2006-3-7 16:49,Fix CDG would display wrong when return from screenSaver 
	{
		supInitSubtitleParam();
		supInitSubtitle();//zhongshan
	}
#endif

#ifndef SDRAM_16Mb_Mode//nono 2004-5-12 20:50 to avoid the bug when exit saver,show display incorrectly
    t_disp = old_t_disp;

    if (t_disp != 0)
    {
        //#ifdef SDRAM_16Mb_Mode
    //to avoid the bug when exit saver,show display incorrectly
    //zhaoyanhua add 2003-11-14 10:35
        //    DispPolling(3);
        //#else
        osd0_state = 1;
        //#endif
    }
    #endif

}



#ifdef COLORFUL_SCREENSAVER    
const UINT32 col_tbl[ ]={PAL4_YELLOW, PAL4_BLUE, PAL4_PURPEL1,PAL4_ORAGNGE,PAL4_GREEN1, PAL4_WHITE,  PAL4_RED, PAL4_YELLOW, PAL4_ORAGNGE, PAL4_GREEN2, PAL4_PINK, PAL4_PURPEL2};
#else
const UINT32 col_tbl[5]={PAL4_ORIGIN,PAL4_WHITE,PAL4_LGREEN,PAL4_PURPEL,PAL4_BLUE}; 
#endif//COLORFUL_SCREENSAVER    

void ChangeColorTable()
{
#ifdef COLORFUL_SCREENSAVER     
    
    nSaverColor  = nSaverColor  +2;
    if (nSaverColor >= 12)
        nSaverColor = 0;
    SetOsdCol(0, 0, 3, col_tbl[nSaverColor]);
    SetOsdCol(0, 0, 2, col_tbl[nSaverColor+1]);
    
#else
    #ifdef USE_SINGLE_COLOR_SCREENSAVER //shenyj add 
    SetOsdCol(0, 0, 3, __palette4F(128, 192, 0, 0xff));
    #else 
    nSaverColor++;
    if (nSaverColor >= 5)
        nSaverColor = 0;
    
    #ifdef BBK_DVD//zhaoyanhua add 03-10-28 13:43
    SetOsdCol(0, 0, 3, col_tbl[nSaverColor]);
    SetOsdCol(0, 0, 1, 0x000000ff);
    #else
    SetOsdCol(0, 0, 3, col_tbl[nSaverColor]);
    #endif
    #endif///end USE_SINGLE_COLOR_SCREENSAVER
#endif
}

#ifdef COLORFUL_SCREENSAVER    

 /*********************************
   *Colorful ScreenSaver
   *Added by xulf and zhaoyanhua 0721
 **********************************/
void ColorDisplay(void)
{
    if (p_scan == 0)
    {
        //display DVD color
        ChangeColorValue(0, 30, 0, 21, 3, 2, 0); 
        //renew the color of the edge of disk(top right corner)  
        ChangeColorValue( 24, 28, 0, 15, 2, 3, 1); 
        //renew the color of the edge of disk(left corner)
        ChangeColorValue(11, 14, 14, 16, 2, 3, 0); 
        ChangeColorValue(10, 13, 16, 22, 2, 3, 0); 
        //renew the color of the edge of disk(in the middle of DVD)
        ChangeColorValue(20, 22, 5, 9, 2, 3, -1); 
        ChangeColorValue(17, 18, 9, 11, 2, 3, 0);
        //display two dot color
        ChangeColorValue(25, 38, 41, 55, 3, 2, 0); 
    }
    else
    {
        //display DVD color
        ChangeColorValue(0, 30, 0, 42, 3, 2, 0); 
        //renew the color of the edge of disk(top right corner)  
        ChangeColorValue( 25, 29, 5, 20, 2, 3, 1); 
        //renew the color of the edge of disk(left corner)
        ChangeColorValue(11, 14, 28, 32, 2, 3, 0); 
        ChangeColorValue(10, 13, 32, 44, 2, 3, 0); 
        //renew the color of the edge of disk(in the middle of DVD)
        ChangeColorValue(20, 22, 10, 14, 2, 3, 0);
        ChangeColorValue(17, 20, 12, 19, 2, 3, 0);       
        //display two dot color
        ChangeColorValue(25, 38, 81, 110, 3, 2, 0); 
    }
}

/******************************************
*This is for the 4-color bitmap. 
*modify the part of bitmap data in order to change 
*original color to another color.
*
*INPUT:
*       SrcColIndex :   0-3, original color
        DstColIndex :   0-3, changed color
                    step :   line offset
*creat: xulf and zhaoyanhua  2003/07/31
*******************************************/
void ChangeColorValue(UINT16 xStart, UINT16 xEnd, UINT16 yStart, UINT16 yEnd, UINT8 SrcColIndex, UINT8 DstColIndex, INT16 step)
{
    BYTE    *pTopLine, *pBtmLine;             
    UINT32  nStartLoc, xPos=0, yPos=0;
    UINT16  j, k, m;    
    UINT16  nRegionWidth = region[0].osd_w * 4;
    UINT16  nSaverWidth, nSaverHigh;
    UINT16  nSpace;
    INT16   i=0;

    nStartLoc = (yPos * nRegionWidth / 8) + (xPos / 4);

    nSaverWidth = OSD_SAVER_W; 
    nSaverHigh = OSD_SAVER_H; 
    nSpace = nSaverWidth/4 ;
    nSaverHigh /= 2;
    m = DstColIndex-SrcColIndex;

    if (yEnd>region[0].osd_h/2) yEnd=region[0].osd_h/2; //potatooo, 20030827
    
    for(j=yStart;j<yEnd;j++)                                                                     
    {
        for (k =xStart; k <xEnd; k++)
        {
            pTopLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (region[0].osd_header[0] + OSD_DATA_OFFSET(region[0].osd_format)) * 32+j*nRegionWidth / 4+i);
            pBtmLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (region[0].osd_header[1] + OSD_DATA_OFFSET(region[0].osd_format)) * 32+j*nRegionWidth / 4+i);

            if((pTopLine[k + nStartLoc]&0x03) == SrcColIndex)
                pTopLine[k + nStartLoc]+=m;
            if((pTopLine[k + nStartLoc]&0x0c ) == (SrcColIndex<<2))
                pTopLine[k + nStartLoc]+=m*4;
            if((pTopLine[k + nStartLoc]&0x30)  == (SrcColIndex<<4))
                pTopLine[k + nStartLoc]+=m*16;
            if((pTopLine[k + nStartLoc]&0xc0)  == (SrcColIndex<<6))
                pTopLine[k + nStartLoc]+=m*64;
            if(p_scan==0)
            {
                if((pBtmLine[k + nStartLoc]&0x03) == SrcColIndex)
                    pBtmLine[k + nStartLoc]+=m;
                if((pBtmLine[k + nStartLoc]&0x0c ) == (SrcColIndex<<2))
                    pBtmLine[k + nStartLoc]+=m*4;
                if((pBtmLine[k + nStartLoc]&0x30)  == (SrcColIndex<<4))
                    pBtmLine[k+ nStartLoc]+=m*16;
                if((pBtmLine[k + nStartLoc]&0xc0)  == (SrcColIndex<<6))
                    pBtmLine[k + nStartLoc]+=m*64;
            }
        }
        i = i+step;
    }

}
#else
void ColorDisplay(void)
{}
#endif


void DrawOsdScreenSaver(UINT32 xPos, UINT32 yPos)
{   
    BYTE    *pTopLine, *pBtmLine;
    UINT32  nStartLoc;
    UINT16  i, j, k;
    UINT16  nSaverWidth, nSaverHigh;
    UINT16  nRegionWidth = region[0].osd_w * 4; // pixel
    UINT16  nSpace;

    osd_tog_region(0, OSD_ON);

    //initialize buffer start
    pTopLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (region[0].osd_header[0] + OSD_DATA_OFFSET(region[0].osd_format)) * 32);
    pBtmLine = (BYTE *)(((BYTE *)get_osdbuf_baseptr()) + (region[0].osd_header[1] + OSD_DATA_OFFSET(region[0].osd_format)) * 32);

    nStartLoc = (yPos * nRegionWidth / 8) + (xPos / 4);
//  printf("get_osdbuf_baseptr = %x\n", get_osdbuf_baseptr());

    //get saver information
    nSaverWidth = OSD_SAVER_W; // in pixel
    nSaverHigh = OSD_SAVER_H; // interlace mode

    nSpace = nSaverWidth / 4; // in byte

    if (p_scan == 0)
        nSaverHigh /= 2;

    for (j = 0; j < nSaverHigh; j++)
    {
        for (i = 0; i < nSpace; i++)
        {
            if (i % 2 == 0)
                pTopLine[i + nStartLoc] = Pattern_Saver[(gpImgAddr[i / 2] >> 4)];
            else
                pTopLine[i + nStartLoc] = Pattern_Saver[(gpImgAddr[i / 2] & 0x0f)];
        }
        pTopLine += nRegionWidth / 4;

        if (p_scan == 0)
        {
            if (nSpace % 2 == 1)
            {
                k = 1;
                pBtmLine[nStartLoc] = Pattern_Saver[(gpImgAddr[nSpace / 2] & 0x0f)];
                gpImgAddr += (nSaverWidth / 8 + 1);
            }
            else
            {
                k = 0;
                gpImgAddr += (nSaverWidth / 8);
            }
            
            for (i = k; i < nSpace; i++)
            {
                if ((i - k) % 2 == 0)
                    pBtmLine[i + nStartLoc] = Pattern_Saver[(gpImgAddr[(i - k) / 2] >> 4)];
                else
                    pBtmLine[i + nStartLoc] = Pattern_Saver[(gpImgAddr[(i - k) / 2] & 0x0f)];
            }
            pBtmLine += nRegionWidth / 4;
        }
        gpImgAddr += (nSaverWidth / 8);
    }

#ifdef SUPPORT_SW_OSD_SCALING

    if( ((GET_TV_RESOLUTION()  == HD_720) || (GET_TV_RESOLUTION()  == HD_1080)) && IS_OSD_SCALE_BUF_OK() ) {
        DrawDimension scale_section;
        scale_section.draw_start.x = xPos;
        scale_section.draw_start.y = yPos;        
        scale_section.draw_dimension.x_length = OSD_SAVER_W;
        scale_section.draw_dimension.y_length = OSD_SAVER_H*2;  
        
        osd_region_scaling(0, &scale_section);
    }
 
#endif

    timeout_osd[0] = 0;
}


void safe_srn_cooking2()
{
  if(safe_state==SAFE_INIT)
  {
    InitOsdScreenSaver();
    safe_state = SAFE_DISPLAYING;
  }
/*
  // move to DoSyncJob()
  else if(safe_state == SAFE_DISPLAYING)
  {
      DisplayScreenSaver();
  }
*/
}

void safe_srn_on(void)
{

#ifdef  SUPPORT_NO_SAFELOGO_FOR_DVB
if(Is_Dvb_State())
{
   return;
}
#endif//end=> #ifdef  SUPPORT_NO_SAFELOGO_FOR_DVB

#ifndef SETUP_CAN_ENTER_SAFECREEN//shenyj add for alco 11/23
if( (full_scrn & SETUP)==0)//nono add.5-8-23 14:27 for screen_saver.
{//if( ((full_scrn & SETUP)==0)&&((full_scrn & PROGRAM)==0) )
#endif
  if (safeForceEnter==1)
  {
    //force to enter screen saver
    safeForceEnter = 2;
    safe_on = 1;
    safeMode = 1; //only support type-1         
    safe_state = SAFE_INIT;     
  }else if (!safe_on)
  { //system is active
    unsigned diff,rtc;
    
    rtc = get_rtc_val();
    
    #if 1//def SUPPORT_LG//Jack added 06/04/04
    if(save_srn_start_t > rtc)
        save_srn_start_t = rtc;
    #endif
    
    diff=rtc-save_srn_start_t;

       safeMode = setup_GetSSaveType(); //Get screen type

    #ifdef QSI_SETUP_MENU//liweihua for SQI setup menu 2004-6-15
    extern UINT16 safe_wait_time;
    if (diff > safe_wait_time)
    #else
    #ifdef EASTWIN
    if ((diff > SAFE_WAIT_TIME)&&(!bIS_LOWBAT))		// Kevin Sep 10,04 
    #else
    if (diff > SAFE_WAIT_TIME)
    #endif
    #endif
    {
       save_srn_start_t = rtc;
       #ifdef SDRAM_16Mb_Mode   // 2004/08/26 yltseng
       
       #if !defined(SUPPORT_OTHER_FILES_SSCREEN)||defined(REALCOLOR_SCREENSAVER) //Jack added 04/11/16
       #ifdef ALCO_MODIFY_PAL_OSD
       if(getVPP_TVsystem()/*old_vppsetup_tv_system*/ != 1)
       #endif
       regs0->osd_base_addr=JPEG_YA;
       #endif
       //Mark the below by Jack!
       /* 
       #ifndef SUPPORT_OTHER_FILES_SSCREEN //Jack added 04/11/16
       if(safeMode)	//linrc add for if screen save is OFF and is stop, no OSD display affter 
       {			// savf wait time is arrive.....2005-1-19 17:21
       regs0->osd_base_addr=JPEG_YA;
       }
       #endif
       */
       #endif
       
       if ( (full_scrn&SETUP) || (full_scrn&CUSTM) ) 
       {
       	#ifdef OP_PLAYMODE
       		ExitSetupPage(1);
       	#else	
            #if defined(ALCO_DVD_UI)&&defined(DVD_SETUP_REENG)  
            setup_ExitPage();
            #else
            setup_save_exit();
            #endif    
        #endif    
          
          
          #ifdef SDRAM_16Mb_Mode   
          #if defined(SUPPORT_OTHER_FILES_SSCREEN)&&defined(REALCOLOR_SCREENSAVER) //Jack added 04/12/07
          #ifdef SETUP_CAN_ENTER_SAFECREEN
          #ifdef ALCO_MODIFY_PAL_OSD
          if(getVPP_TVsystem()/*old_vppsetup_tv_system*/ != 1)
          #endif
          regs0->osd_base_addr=JPEG_YA;
          #endif
          #endif
          #endif
       
       }
       
#ifdef NEWSTYLE_WINDOW  // alan, 2003/8/11 09:11PM
       if (full_scrn&MESSAGE)   // alan, 2003/8/11 09:11PM
       {
            exit_browse_func();
       }
#endif

       //safeMode = setup_GetSSaveType(); //Get screen type
       //printf("safeMode=%d\n", safeMode);
       if (safeMode>0)
       {
         safeMode = 1; //only support type-1                    
         safe_on  = 1;
         safe_state = SAFE_INIT;

         old_t_disp = t_disp;
         if (t_disp>0) DispFadeOut();
         
         if (full_scrn) 
            full_scrn=0;            
       }
     } 
  }
  else
  {
     if(safeMode==1) safe_srn_cooking2();
     else safe_on = 1;
  }
#ifndef SETUP_CAN_ENTER_SAFECREEN
}//if( ((full_scrn & SETUP)==0)&&((full_scrn & PROGRAM)==0) )
#endif
}

//force to enter screen saver
void safe_srn_forceON(void)
{
    //printf("safe_srn_forceON\n");
    safeForceEnter=1;
}

void safe_srn_forceOFF(void)
{
#if (defined(DVB_SETUP)&&!defined(SUPPORT_DVD_OSD)&&defined(OSD_SCREEN_SAVER)) //xsyan add
    DISABLE_OSD();
#endif
    //printf("safe_srn_forceOFF\n");
    safeForceEnter=0;
}

void safe_srn_off(void)
{
#if (defined(DVB_SETUP)&&!defined(SUPPORT_DVD_OSD)&&defined(OSD_SCREEN_SAVER)) //xsyan add
    DISABLE_OSD();
#endif
    
    if (safeForceEnter==2) return;
    
    if (safe_on==1)
    {
        safe_on=0;
        safe_state = SAFE_INIT;

#ifdef OSD_SCREEN_SAVER

      #ifdef SDRAM_16Mb_Mode   // 2004/11/26 lyc  when  safe_srn_on function regs0->osd_base_addr = JPEG_YA 
         regs0->osd_base_addr = GetOSDBackUpAddress();  //now addr reset;
      #endif  
        ExitOsdScreenSaver();//terry 20050618 move from above.
#else
        ShowTitle();
        sys_cmd=0;//2-8-21 21:54
#endif
        
#ifdef CD_PLAYER//liweihua 2003-9-18
    if(cd_type_loaded==CDDA)
    {
        osd_init_cdplayer();
#ifdef VIRTUAL_KEYBOARD//liweihua 2003-9-18
    osd_draw_virtual_keyboard(0,0,4);   
    hl_keyboard_button(KeyID);
        full_scrn |= KEYBOARD;
    #endif
    }
#endif

#ifdef DYNAMIC_SPECTRUM//zhaoyanhua add 03-11-3 19:29
    //if(bEqDisplay)
    {//terry,mark it,2003/12/24 10:32PM
        //Show3dspectrum();
    }
#endif
#ifdef PMP_UI////////////////////////yangli add for safe 2005/8/2
osd_init_show_setup_pmp();
if(pFsJpeg->gifsState == FS_STATE_MP3)
 show_id3();
if(pFsJpeg->gifsState == FS_STATE_OTHER)
 osd_init_OSDSRT();
#endif     ////////#ifdef PMP_UI

#ifdef SUPPORT_DVB_GUI_NEW             //sunzhh add 20051027
    if(Is_Dvb_State())
        osd_init_new_dvb_menu();
#endif
    }
}




extern BYTE safe_state;

void DoSyncJob(void)
{
    /*
    if ((play_state == VCD_STATE_IDLE) ||
        (play_state == VCD_STATE_STOP) ||
        (play_state == VCD_STATE_OPEN) ||
        (play_state == VCD_STATE_PAUSE))
    {
        //safe_srn_on();
    }
    */

    #ifdef OSD_SCREEN_SAVER
    if (safe_state == 1)
        DisplayScreenSaver();
    #endif
    
    #ifdef MP3_NO_DISPLAY   //2004-4-23 12:50ÕÅÓîM
    if (t_disp==1)
    mp3_noshow_diplay();
    #endif
}

#if (defined(DVB_SETUP)&&!defined(SUPPORT_DVD_OSD)&&defined(OSD_SCREEN_SAVER)) //xsyan add
static void enable_osd_saver(void)
{
     regs0->osd_tlink_addr  = region[0].osd_header[0];
         regs0->osd_blink_addr  = region[0].osd_header[1];
         regs0->osd_en= 1;
}
#endif

