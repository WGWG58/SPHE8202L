//
// FILE
// setup_tab.c
//

//--------------------------------------
//Modefied by wangfeng, 2003-08-29 15:18
//For new setup menu
//--------------------------------------

#include "user_init.h"

extern int user_input_pwd;


#ifdef NEW_SETUP_OSD    // majinping 2002-05-02 for new setup menu
#error


#include "setup_new.c"
#elif defined(KONKA_DVD)    // 2-7-16 14:44 for new setup menu

#include "setup_konka.c"

#else

/*****************************************************\
Creater: Terry
Date   : 2001/5/11 12:49PM
Description: Setup menu using
\*****************************************************/
//#define USE_MIC_ECHO_PARAM
#include "global.h"
#include "osd.h"
#include "func.h"
#include "navdata.h"
#include "kernel.h"
#include "vpp.h"
#include "user_if.h"
#include "dsp3_if.h"
#include "cchar.h"
#include "ircmd.h"
#include "auddrv.h" //2004AUDDRV oliver 20041004 for using audio driver purpose
//#include "audif.h"
#include "tvif.h"
#include "memmap.h"
#include "stdlib.h"
#include "kinf.h"
#include "gpio.h"//nono 2004-4-26 20:57

#ifdef SUPPORT_MIDI  //ouyang 2004-10-18 22:44
#include "fsmidi.h"
#endif


#ifdef SUPPORT_DISPLAY_MENU
#include "ircode.h"
#include "irconfig.h"
#endif//end #ifdef DISPLAY_MENUs


#ifdef TAS3001_AMP //Ti3001_OSD_UI_2  // TAS3001_AMP use setup menu control /jsaon 2-8-30 21:30
#include "ti3001.h"
#endif
#ifdef SUPPORT_APOGEE_AMP//xyy 2004-1-12 17:40
#include "ddx8000.h"

#endif

#ifdef SUPPORT_SPI
#include "spi.h"
#endif

#ifdef DVB_SETUP_MENU
#include "dvbmenu.h"
#endif

#ifdef VOLUME_RECODE
#include "memmap_I2C.h"
#endif	

#ifndef DVDRELEASE
#define SETUP_DBG        1
//#define MONE_SETUP
#endif

#ifndef SETUP_DBG
#undef printf
#undef print_block
#define printf(f, a...) do {} while (0)
#define print_block(x,y) do {} while (0)
#endif

#if defined (YI_XIAN_TONG)||defined (TONIC_DVD)//zhaoyanhua add 03-11-3 22:20
#include "gpio.h"
#endif

extern UINT16 echo_para_tbl[9][2];//echo_para[9][2]; for using audio driver purpose
#ifdef VGA_CTRL_FORMAT//wangfeng 2003-12-18 16:12
BYTE    temp_format=0;
#endif

#ifdef MIC_FUNCTION_KEY
extern BYTE bFuncStep;//nono 20040107
#endif//MIC_FUNCTION_KEY

//wangap add for downmix off volume
#ifndef AC3_BASS_MANAGEMENT
  BYTE    cspk_volume;
  BYTE    fspk_volume;
  BYTE    sspk_volume;
#endif
#ifdef USE_PROLOGIC_II_KEY
BYTE    prologic_val;//clead 2003-8-7
#endif

#if defined(GBM_DVD)&&!defined(GBM_FULL_FUNCTION)&&!defined(USER_MPEG_LOGO)
#undef SAME_DISC_RESUME
BYTE    same_disc_onoff = 1;
#endif

#ifdef   DYNAMIC_SPECTRUM       //fengjl  3-10-21 20:38
#undef SAME_DISC_RESUME
BYTE   band_onoff = 0;//inital value must be 0.zhaoyanhua modify 2004-1-12 15:01
#endif



#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)    //fengjl add for bbk's new setup  3-11-12 16:17
extern void osd_init_bbk_setup(void);
BYTE    one_key_pass_flag = 0;
BYTE    main_setup = 0;
#elif defined(BBK_DSS_555_DVD)||defined(BBK_DV911S)
BYTE    main_setup = 0;
#endif

#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-7 17:18
extern int GetVideoSetValue(int id);
#endif//end VIDEO_SETUP_NEW_GUI

#ifdef AUDIO_2CH_5_1CH//zhaoyanhua add 03-11-1 17:33
extern BYTE ChannelFlag;
#endif

#ifdef  KARAOKE_MENU//wangfeng
BYTE    KARAOKE_MENU_FLAG=0;
#endif

//#define MONE_SETUP
//=======================
#ifdef NEW_STYLE_SETUP
#define BUTTON_COLOR   7

//zhaoyanhua add 3-7-14 17:49
//a flag decide to operate setupmenu or not.
//if 0,only show setup menu, now at level 0, can not operate.
//if 1,now at level 1, can operate setup menu with UP/DOWN/LEFT/RIGHT/SELECT key.
int   GBM_run_setupmenu_flag = 0;
#endif

//define setup pages(including MAX_SETUP_PAGE+MAX_CUSTM_SETUP_PAGE)
#include "setup_def.h"

const BYTE OSD_LANG_MAP[8] = OSD_LANG_SETUP_MAP; //Jeff 20030217

const BYTE upgrade_file_name[] = UPGRADE_FILE_NAME;//nono 3-6-17 14:03

extern void RsmInfo2Flash(int);
extern void audif_set_SPDIF_BITSTREAM();
//extern void ircmd_stop(void);
#ifdef SAME_DISC_RESUME
BYTE    same_disc_onoff;
#endif

extern UINT8 ap_tv_out_id;//nono 2003-8-1 18:08

#ifdef USER_MPEG_LOGO
BYTE    mpeg_logo_onoff=0;
BYTE    need_show_logo=0;
extern void Change_User_Logo();
#endif

#ifdef DVB_SETUP_MENU
extern const char * osd_str_dvb_submenu[N_OSD_LANGS][5];
#endif

#if defined(NEW_PARENTAL_GUI)||defined(MODIFY_PARENTAL_GUI)//zhaoyanhua add 2003-11-28 10:46

#if defined(NEW_PARENTAL_GUI)
extern void osd_init_parental_gui(void);
    BYTE   new_parental_gui = 0;
#endif

#if defined(MODIFY_PARENTAL_GUI)
    BYTE    parental_gui_flag = 0;
#endif//#if defined(MODIFY_PARENTAL_GUI)

void check_parent_password(void);
void ExitParentalGUI(void);


#endif
//osd related function
extern void osd_init_setup(void);
extern void osd_disable(void);
extern void osd_DrawLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth);
extern void osd_draw_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor);
extern void osd_draw_setup_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown);

extern void setVPP_OffsetX(int X);
extern void setVPP_OffsetY(int Y);

//3D sound(EQ, Surround) related setting
extern BYTE soundGetSurroundType();

//misc functions
extern void set_aud_buf_size(void);

void setup_DrawItem(BYTE level, BYTE yStart, BYTE updowngray);
const char * setup_SetItemString(void);
void run_save_tv_cmd(UINT8 item,UINT8 sel);
UINT16 run_save_unChk_cmd(UINT8 save);
void set_video_aspect(void);
int is_aspect_menu(void);

void run_save_sel_cmd(BYTE page,BYTE index);
void run_save_total_sel(void);
void rep_run_the_menu(void);

void show_lock(int s,int mode);
void setup_ShowAC3Config();
void setup_CookScaleItem(UINT8 id, UINT8 dir);
void setup_PrepareScaleItem(BYTE id, BYTE up1down);
void setup_ShowVolCtrlConfig();
void ShowPasswordGUI();
void setup_ShowAC3DynamicRange(void);
void set_AC3DynamicRange(void);

void reset_passwd_cnt(void);

void setup_func_return_main(void);

int IsOSDChinese();

//void SetSharpness(BYTE nVal);
void SetBrightness(BYTE nVal);
void SetContrast(BYTE nVal);

void setup_save_exit(void);

#ifdef IR_KEY_SET_VIDEO_MODE
void SetBrightnessAdjust(BYTE nVal, BYTE nVal2);
void SetContrastAdjust(BYTE nVal, BYTE nVal2);
#endif//IR_KEY_SET_VIDEO_MODE

void SetHUE(BYTE nVal);
void SetSaturation(BYTE nVal);

#ifdef DIP_CFG_ENABLE
void SetDeInterlace(BYTE nVal);
#endif

#ifdef BBK_DVD//zhaoyanhua add 03-10-19 10:43
void AudioSet2chOutput(void);
void AudioSet5_1chOutput(void);
void AudioSetPrologic_IIOutput(void);
#endif//end BBK_DVD

#ifdef SHOW_STANDBY_TIMER        //suqiaoli add 2003-8-2
#define STANDBY_TIMER_ITEM         3
void polling_setup_standby_timer(void);
#endif

extern void search_ap_tv_out_id(void);
extern void update_tv_format_sel(void);
extern int check_chipinfo(int n);

#ifdef SPHE1000	
#include "driver/message.h"
extern share_info_t *pDVB;
#endif
/***********   Item description  **********************\

  BYTE    function
  0       mode(MSB 4bits)  ==>show direction picture
  0x0:no effect
  0x1:basic select function
  0x2:can enter number
  0x3:need run function by osd id
  0x4:left/right shift only
  0x5:only show text,can't move to this area
  1       title       ---sw region 1
  2~6     select item ---sw region 2

\******************************************************/
enum
{
    SET_NE=0,
    SET_BS=0x1,
    SET_NM=0x2,
    SET_FUNC=0x3,
    SET_SH=0x4,
    SET_SHOW=0x5,
    SET_SCALE=0x6,
    SET_SPACE=0x7,
};

UINT8   setup_page,setup_id __attribute__((unused)),setup_sel_item;

#define page    setup_page
#define id  setup_id
#define sel     setup_sel_item

UINT8   id,sel,page;
#ifdef SETUP_6_DIGIT_PASSWORD//zhaoyanhua add 03-10-14 14:22
UINT32  tmp_passwd;
#else
UINT16  tmp_passwd;
#endif

UINT32  romCheckSum;

#ifdef Ti3001_OSD_UI_2
    INT8  amp_volume_level;
    INT8  amp_fspk_level;
    INT8  amp_fspk_balance_level;
    INT8  amp_sspk_level;
    INT8  amp_sspk_balance_level;
    INT8  amp_cspk_level;
    INT8  amp_subwoofer_level;
    INT8  amp_bass_level;
    INT8  amp_tremble_level;
    INT8  amp_dynamic_level;
#endif

BYTE    index_y=0;          //item index for 1st-level page, 2nd-level page
BYTE    index_y2=0;         //item index for 3rd-level page
BYTE    index_y_start=0;
BYTE    index_y2_start=0;
#ifdef EASTECH_SETUPMENU
BYTE    index_pscan_ok=0;
#endif
BYTE    submenuStart=SETUP_MENU_YSTART;
BYTE    setupLevel=0;       //0:main menu, 1:sub-menu, 2:selection-menu(menu of sub-menu)

BYTE    setupItemNum[3] = { //max item num in every sub-menu
    MAX_PAGE_ITEM,          //main menu items count
    MAX_PAGE_ITEM,          //second-level menu items count
    MAX_PAGE_ITEM           //third-level menu
};

//define setup page
#include "setup_page.h"

//PS:this command line doesn't be used in macro define
//run_save_sel_cmd(0, 5);


#ifdef Ti3001_OSD_UI_2
    const UINT8 setup_MainP[][2] =
    {
        {STR_OS_SYS_SETUP, 0},
        {STR_OS_LANG_SETUP, 1},
        {STR_OS_AUD_SETUP, 2},
        //{STR_OS_SPK_SETUP, 3},
        {STR_OS_SPK_SETUP, 3},
        {STR_OS_DIGTAL_SETUP, 4},
        {STR_OS_AMP_SETUP1,5},       //S:"功放设定1"
        {STR_OS_AMP_SETUP2,6},       //S:"功放设定2"
        {STR_OS_EXIT_MENU, 7},
    };
#elif defined(DVB_SETUP_MENU)    //sunzhh 20050430
    const UINT8 setup_MainP[][2] =
    {
	{STR_OS_INSTALL_SETUP, 0},
	{STR_OS_CHANNEL_SETUP, 1},
	{STR_OS_SYS_SETUP, 2},
	{STR_OS_LANG_SETUP, 3},
	{STR_OS_AUD_SETUP, 4},
        {STR_OS_VIDEO_SETUP, 5},
        {STR_OS_SPK_SETUP, 6},
        {STR_OS_DIGTAL_SETUP, 7},
        {STR_OS_SPACE, 0},
        {STR_OS_EXIT_MENU, 8},
        {STR_OS_NO, 0},
    };
#else//take off SOFT_MENU special setup_MainP,share with old setup_MainP.chenzhao on 2004-11-15 11:3
    const UINT8 setup_MainP[][2] =
    {
        {STR_OS_SYS_SETUP, 0},
        {STR_OS_LANG_SETUP, 1},
        {STR_OS_AUD_SETUP, 2},
        #ifdef QSI_SETUP_MENU//liweihua 2004-6-15
        {STR_OS_KARAOKE_SETUP,3},
        #else
        #ifndef BBK_SIMPLE_SETUP
         #ifndef SETUP_DONGLI459//20040206
        {STR_OS_VIDEO_SETUP, 3},
        {STR_OS_SPK_SETUP, 4},
        {STR_OS_DIGTAL_SETUP, 5},
       #else
       {STR_OS_SPK_SETUP, 3},
        {STR_OS_DIGTAL_SETUP, 4},
       #endif
        {STR_OS_SPACE, 0},
        #else//#ifndef BBK_SIMPLE_SETUP
        {STR_OS_VIDEO, 0},
        #endif//#ifndef BBK_SIMPLE_SETUP
        #endif//#ifdef QSI_SETUP_MENU
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE
        {STR_OS_ONEKEY_SETUP, 7},
        {STR_OS_EXIT_MENU,8},
#else
        {STR_OS_EXIT_MENU, 7},
#endif
        {STR_OS_NO, 0},
    };
#endif

//
// If you change the sequence of the menu items, please check up the following definition
// and
// set_default_value()
// run_set_variable()
// setup_func_down()
// setup_SetAC3Config()
//
UINT8 setup_sel[MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE][MAX_PAGE_ITEM];//Item number
#ifdef SUPPORT_FUNCTION_MENU
UINT8 setup_sel_plus[MAX_SETUP_PAGE_PLUS][MAX_PAGE_ITEM_PLUS];
#endif

//const UINT8 setup_item[MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE][MAX_PAGE_ITEM][MAX_ITEM_SEL]
//exe_setup_function,terry,2004/2/10 03:36PM
//take off SOFT_MENU special setup_item,share with old setup_item.chenzhao on 2004-11-15 11:3
#include "setup_item.c"
#include "setup_exe.c"
#include "setup_if.c"
#ifdef SUPPORT_FUNCTION_MENU
#include "setup_plus.c"
#endif

#ifdef SUPPORT_8202_DVB
#include "system_setup_api.c"
#endif

int setup_IsSpkSubwooferOn(void)
{
    int res;
    if(SETUP_SPK_SUBWOOFER==3)
        res=1;
    else
        res=0;
    return res;
}


int WillKeyShiftNotDo(void)//nono 2-5-12 20:54
{

    int res=0;

#ifndef SETUP_ALL_VALID//nono 2003-9-25 16:54
    if( ((SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF)||(coding_mode_now==AUDIF_CODING_MODE_LPCM) )&&(cd_type_loaded==CDDVD) )
        res=1;
    else if( (SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF)&&(coding_mode_now==AUDIF_CODING_MODE_DTSCD) )
        res=1;
#endif

    return res;
}


#ifdef USER_MPEG_LOGO
UINT8 setup_GetMPEGLogoItem(void)
{
    return (SETUP_MPEG_LOGO);
}

void setup_SetMPEGLogo(void)//nono 2-5-16 18:05
{

    //setup_sel[SysNextPage][MPEG_LOGO_ITEM]=3;
    SETUP_MPEG_LOGO = MPEG_LOGO_ON;//3
    //exe_setup_function(STR_OS_SELECT_LOGO,STR_OS_DEFAULT_SETUP,0);  // alan, 2003/9/16 05:03PM
    exe_setup_function(STR_OS_SELECT_LOGO,STR_OS_MPEG_LOGO,0);  //NONO 2004-2-17 17:02
    //setup_sel[7][2]=3;
    run_save_sel_cmd(SysNextPage, MPEG_LOGO_ITEM);//nono 2004-2-17 17:02

}

#ifdef YUXING_MIDI_DVD        //nono 2004-10-28 14:34
void setup_SetDefaultLogo(void)//nono 2-5-16 18:05
{
    SETUP_MPEG_LOGO = 2;//3
    exe_setup_function(STR_OS_SELECT_LOGO,STR_OS_DEFAULT_SETUP,0);  // alan, 2003/9/16 05:03PM
    run_save_sel_cmd(SysNextPage, MPEG_LOGO_ITEM);//nono 2004-2-17 17:02
}
#endif
#endif//USER_MPEG_LOGO


int setup_IsSpkDownmixOff(void)//nono 2-5-16 18:05
{

    if(SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF)
        return 1;
    else
        return 0;

}
void setup_Showredframe(UINT8 page_val)
{
#ifndef SETUPMENU_16Mb_NO_ICON
        UINT16 line=SETUP_MAX_WIDTH*16-20;

        if(page_val==7) page_val=0;
        osd_DrawLine(line*page_val/6+30,14,line*page_val/6+80,14,SANTIBGCOLOR,1);
        osd_DrawLine(line*page_val/6+30,50,line*page_val/6+80,50,SANTIBGCOLOR,1);
        osd_DrawLine(line*page_val/6+30,14,line*page_val/6+30,50,SANTIBGCOLOR,1);
        osd_DrawLine(line*page_val/6+80,14,line*page_val/6+80,50,SANTIBGCOLOR,1);
#endif
}

void setup_ShowAC3DynamicRange(void)
{
    BYTE    buf[40];
    BYTE    fontColor;

    if ( (page!=AC3DIGITALPAGE) ||
        (setupLevel!=2) ||
        (index_y!=AC3OUTMODEITEM)
        )
    {
        return;
    }


    if ( (SETUP_AC3DIGITAL_OUTMODE==AC3DYNAMICITEM2) && 1
//      (SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF)
        )
    {
        fontColor = SFONTCOLOR;
    } else {
        fontColor = SGRAYCOLOR;
    }

    id = setup_item[page][AC3DYNAMICITEM1][1];
    psprintf(buf, "%s", _OsdMessegeFont1[osd_font_mode][id]);
    osd_DrawString(SETUP_MENU_XSTART+1, AC3DYNAMICITEM1+SETUP_MENU_YSTART, buf, fontColor, SBGCOLOR);
}



void set_AC3DynamicRange(void)
{
    if (ac3_dynarange) {
        AUDIF_Set_OutputMode(OUT_CustomModeB_DigitalDialnormK1, ac3_dynarange * 0x2020 - 0x0101);//2004AUDDRV AudioSetOutputMode(0x80, ac3_dynarange * 0x2020 - 0x0101);
    } else {
        AUDIF_Set_OutputMode(OUT_CustomModeB_DigitalDialnormK1, 0);//2004AUDDRV AudioSetOutputMode(0x80, 0);
    }
}

#ifdef AUDIO_2CH_5_1CH
int setup_IsSpkStereo(void)
{
    if(SETUP_SPK_DOWNMIX == DOWNMIXSTEREO)
        return 1;
    else
        return 0;
}


/*
 * to set 5.1 channel output mode
 *
 */
void AudioSet5_1chOutput(void)
{
    exe_setup_function(STR_OS_DOWNMIX_SETUP,STR_OS_OFF,0);//turn off mix off
    SETUP_SPK_DOWNMIX = AC3DOWNMIXOFF;

#ifdef YI_XIAN_TONG//zhaoyanhua add 2003-12-17 9:51
        Gpio5ChOutput();
#endif
}

/*
 * to set PROLOGIC_II channel output mode
 *
 */
#ifdef SUPPORT_PROLOGIC_II  //axel 2004/1/28 10:30
void AudioSetPrologic_IIOutput(void)
{
    //abstract from setup_tab_ui.c
    //NOTE:
    // can not change the order.
    //zhaoyanhua note 03-11-1 18:58
    exe_setup_function(STR_OS_PROLOGIC,STR_OS_PL_MUSIC,0);
    SETUP_PROLOGIC_II= 3;//STR_OS_PL_MUSIC  to update SETUP in time.
    //set AUDIO output SIMULATE
    //because BBK need SIMULATE and DIGITAL ouput at the same time
    //so we must mask the following sentences.
    //zhaoyanhua mask 2003-11-29 20:29
    #if 0
    SETUP_SPDIF=2;
    exe_setup_function(STR_OS_AUD_OUT,STR_OS_SIMULATE,0);
    #endif
    //set DOWNMIX OFF
    SETUP_SPK_DOWNMIX = AC3DOWNMIXOFF;
    exe_setup_function(STR_OS_DOWNMIX_SETUP,STR_OS_OFF,0);

}
void AudioSetPrologic_II_Movie()
{
    exe_setup_function(STR_OS_PROLOGIC,STR_OS_PL_MUSIC,0);
    SETUP_PROLOGIC_II= 2;//STR_OS_PL_Movie  to update SETUP in time.
    run_save_sel_cmd(AUDPAGE,PROLOGIC_II);//clead 2003-10-21 

}
void AudioSetPrologic_II_Music()
{
    exe_setup_function(STR_OS_PROLOGIC,STR_OS_PL_MUSIC,0);
    SETUP_PROLOGIC_II= 3;//STR_OS_PL_MUSIC  to update SETUP in time.
    run_save_sel_cmd(AUDPAGE,PROLOGIC_II);//clead 2003-10-21 
}
void AudioSetPrologic_II_Off()
{
    exe_setup_function(STR_OS_PROLOGIC,STR_OS_PL_MUSIC,0);
    SETUP_PROLOGIC_II= 4;//STR_OS_PL_MUSIC  to update SETUP in time.
    run_save_sel_cmd(AUDPAGE,PROLOGIC_II);//clead 2003-10-21 
}
#endif //SUPPORT_PROLOGIC_II //axel 2004/1/28 10:30
#endif// AUDIO_2CH_5_1CH

//terry,2004/2/5 12:08PM
void setup_SetTV_format(UINT8 id)
{//terry,2004/2/5 12:02PM
#ifndef NO_TV_FORMAT
   #ifndef FUSS_TV_DVD//nono 2-8-20 12:55
   int i;

   for(i=2;i<MAX_ITEM_SEL;i++)
   {
      if(setup_item[SYSPAGE][TV_FORMAT][i]==id)
      {
    SETUP_TV_FORMAT=i;
    run_save_sel_cmd(SYSPAGE,TV_FORMAT);//terry,2004/2/3 03:35PM
    break;
      }
   }
   #endif
#endif
}

#ifdef FORCE_RETURN_TO_DEFAULT_TV_FORMAT//nono 20030913
void setup_SetTV_default_format(void)
{
    SETUP_TV_FORMAT = MIN_ITEM_SEL+DEFAULT_TV_SYS;
    //setup_tv_format(DEFAULT_TV_SYS); // Robert 020919
    //exe_setup_function(STR_OS_TV_SYS,STR_OS_NTSC,0);
//modefied by wangfeng,2004-2-9 17:39
#if defined(TV_FORMAT)&& !defined(FORCE_RETURN_TO_DEFAULT_TV_FORMAT)//terry,2004/2/3 01:34PM

    exe_setup_function(STR_OS_TV_SYS,setup_item[SYSPAGE][TV_FORMAT][SETUP_TV_FORMAT],1);
#else
        //exe_setup_function(STR_OS_TV_SYS,STR_OS_NTSC,1);
        #ifdef FORCE_RETURN_TO_FORMAT_PAL
        tv_format=MODE_PAL;//MODE_NTSC;
        #elif defined(FORCE_RETURN_TO_FORMAT_AUTO)   //fengjl  add 2004-03-09 15:47
        tv_format=MODE_AUTO;
        #else
        tv_format=MODE_NTSC;
        #endif
        update_tv_format_sel();
        setup_tv_format(tv_format);
        #ifdef FORCE_RETURN_TO_FORMAT_PAL
        setup_SetTV_format(STR_OS_PAL);
        #elif defined(FORCE_RETURN_TO_FORMAT_AUTO)
        setup_SetTV_format(STR_OS_AUTO);
        #else
        setup_SetTV_format(STR_OS_NTSC);
        #endif
         //exe_setup_function(STR_OS_TV_SYS,STR_OS_PAL,1);
#endif
}
#endif//FORCE_RETURN_TO_DEFAULT_TV_FORMAT

#ifdef USE_PROLOGIC_II_KEY  /*2005-6-7 14:52 huziqin modified,add mode*/ 
//#define DEBUG_PROLOGIC

void set_prologic_val(BYTE prologic_mode)
{
    BYTE type= 0x10;
    UINT32 P, I;

    switch (prologic_mode)
    {
        case PROLOGIC_MODE_MOVIE:
            pl2_init_val|=(1<<20);      // set prologic-II enable
            pl2_init_val &= (~(0x0f<<16)); /*clear mode*/
            pl2_init_val |= (3<<16);      // set init-val to movie mode                       
            
            AUDIF_Set_ProLogicII(0x11);
            type=0x23; //Oliver : prologic-II Decoder Mode - Movie/Standard Mode
            #ifdef DEBUG_PROLOGIC
            printf("<MOVIE>, pl2_init_val=0x%06x\n",pl2_init_val);
            #endif
            break;
        case PROLOGIC_MODE_MUSIC:     
            pl2_init_val|=(1<<20);      // set prologic-II enable
            pl2_init_val &= (~(0x0f<<16)); /*clear mode*/
            pl2_init_val |= (2<<16);   // set init-val to music mode
            AUDIF_Set_ProLogicII(0x11);
            type=0x22; //Oliver : prologic-II Decoder Mode - Music Mode
            #ifdef DEBUG_PROLOGIC
            printf("<MUSIC>, pl2_init_val=0x%06x\n",pl2_init_val);
            #endif
            break;
        case PROLOGIC_MODE_OFF:                 
            pl2_init_val=PROLOGICII_OFF_DSP_INIT;
            AUDIF_Set_ProLogicII(0x10);
            #ifdef DEBUG_PROLOGIC
            printf("<OFF>, pl2_init_val=0x%06x\n",pl2_init_val);
            #endif
            break;
        case PROLOGIC_MODE_EMU:
            pl2_init_val|=(1<<20);      // set prologic-II enable
            pl2_init_val &= (~(0x0f<<16)); /*clear mode*/
            
            AUDIF_Set_ProLogicII(0x11);

            type=0x20;
            //printf("<PRO LOGIC EMU MODE>, pl2_init_val=0x%06x\n",pl2_init_val);
            break;
        case PROLOGIC_MODE_VIRTUAL:
            pl2_init_val|=(1<<20);      // set prologic-II enable
            pl2_init_val &= (~(0x0f<<16)); /*clear mode*/
            pl2_init_val |= (1<<16);   
            
            AUDIF_Set_ProLogicII(0x11);

            type=0x21;
            #ifdef DEBUG_PROLOGIC
            printf("<PRO LOGIC VIRTUAL>, pl2_init_val=0x%06x\n",pl2_init_val);
            #endif
            break;
        case PROLOGIC_MODE_MATRIX:
            pl2_init_val|=(1<<20);      // set prologic-II enable
            pl2_init_val &= (~(0x0f<<16)); /*clear mode*/
            pl2_init_val |= (4<<16);   
            
            AUDIF_Set_ProLogicII(0x11);

            type=0x24;
            #ifdef DEBUG_PROLOGIC
            printf("<PRO LOGIC EMU MODE>, pl2_init_val=0x%06x\n",pl2_init_val);
            #endif
            break;
        default:
            printf("unknow prologic mode!!!!\n");
            break;
            
    }
    AUDIF_Set_ProLogicII(type);

#ifdef USE_PROLOGIC_II_KEY_FOR_SURROUND
    I2c_write_surrond_mode();
#endif   
    SETUP_PROLOGIC_II=prologic_mode+2;
    exe_setup_function(STR_OS_PROLOGIC, setup_item[AUDPAGE][PROLOGIC_II][SETUP_PROLOGIC_II], 1);
    run_save_sel_cmd(AUDPAGE,PROLOGIC_II);//clead 2003-10-21
     
}
#endif //USE_PROLOGIC_II_KEY






void setup_SetPScan(void)
{
    #ifndef FUSS_TV_DVD//nono 2-8-20 12:55
    SETUP_VIDEO_FORMAT = ap_tv_out_id+2;

#if defined(SCART_TV)||defined(KSD_SCART_TV)||defined(SCART_TV_2)||defined(SCART_TV_4)||defined(SCART_TV_5)//wangfeng 2003-12-2 23:03
        //if(tv_out_id==PC_VGA||tv_out_id==TV_RGB)
        if(tv_out_id==TV_RGB)//nono 2003-8-24 21:08
        SET_SCART_RGB(1);
        else
        SET_SCART_RGB(0);
#elif defined(SCART_TV_3)
    if(tv_out_id==TV_RGB)
        SET_SCART_RGB(0);
    else
        SET_SCART_RGB(1);
#endif

#ifdef SUPPORT_SCART_TV//SPHE8202//nono 4-3-27 21:35
    if(tv_out_id==TV_RGB)
    {
        SET_SCART_GPIO_SFT_CFG_CTRL();
        SET_SCART_TO_RGB();
    }
    else
    {
        SET_SCART_GPIO_SFT_CFG_CTRL();
        SET_SCART_TO_CVBS();
    }
#endif//SPHE8202

    //run_save_cmd();
    run_save_sel_cmd(SYSPAGE,2);
    #endif
}

//////////////////////////////////
#if 0//def IR_KEY_SET_VIDEO_MODE
void set_video_val(BYTE video_mode)
{
    int i=0;
        UINT8 parm[6][3] = { {8,8,8},//0
                             {7,9,6},//1
                             {9,8,10},//2
                             {8,9,9},//3
                             {11,10,9},//4
                             {7,5,7},//5
                           };

        if(video_mode<6)
        {
                SETUP_BRIGHTNESS=parm[video_mode][0];
                SETUP_CONTRAST=parm[video_mode][1];
                SETUP_HUE=parm[video_mode][2];
        }else
        {
            ReadFromI2c(0xa0, 240,(BYTE *)&SETUP_BRIGHTNESS,1);
            ReadFromI2c(0xa0, 241,(BYTE *)&SETUP_CONTRAST,1);
            ReadFromI2c(0xa0, 242,(BYTE *)&SETUP_HUE,1);
        }
        SetBrightness(SETUP_BRIGHTNESS - 2);
        SetContrast(SETUP_CONTRAST - 2);
        SetHUE(SETUP_HUE - 2);
        //SetSaturation(SETUP_SATURATION - 2);
        do{
        run_save_sel_cmd(VIDEOPAGE,i);
        i++;
        }while(i<4);
}
#endif
//

//
#ifdef IR_KEY_SET_VIDEO_MODE
void set_video_val(BYTE video_mode)
{

        UINT8 b,c,h,s;
    //b:SETUP_BRIGHTNESS
    //c:SETUP_CONTRAST
    //h:SETUP_HUE
    UINT8 parm[6][3] = { {8,8,8},//0
                         {7,9,6},//1
                         {9,8,10},//2
#ifndef SET_4_VIDEO_MODE
                         {8,9,9},//3
                         {11,10,9},//4
                         {7,5,7},//5
#endif//SET_4_VIDEO_MODE
                       };
#ifdef SET_4_VIDEO_MODE
    if(video_mode<3)
#else//SET_4_VIDEO_MODE
    if(video_mode<6)
#endif//SET_4_VIDEO_MODE
    {
        b=parm[video_mode][0];
        c=parm[video_mode][1];
        h=parm[video_mode][2];
                s=2;
                SetBrightnessAdjust(b - 2,c);
                SetContrastAdjust(c - 2,b);
    }else
    {
        b=SETUP_BRIGHTNESS;
            c=SETUP_CONTRAST;
            h=SETUP_HUE;
                s=SETUP_SATURATION;
                SetBrightness(b - 2);
                SetContrast(c - 2);

    }

        //SetBrightness(SETUP_BRIGHTNESS - 2);
        //SetContrast(SETUP_CONTRAST - 2);
    //SetSaturation(SETUP_SATURATION - 2);
        //SetHUE(SETUP_HUE - 2);


        //SetSaturation(SETUP_SATURATION - 2);
        SetHUE(h - 2);
        SetSaturation(s - 2);
        //if(video_mode_val==6)

}

#endif
//
#ifdef  AUTO_ADJUST_TV_TYPE  //lijd 2004-9-15 13:33
void auto_adjust_tv_type(void)
{
    int  mode;
    mode=(pDSV->dV_ATR>>8)&0x0f;
    switch(mode)
    {
         case 0x0e:  //16:9
                   SETUP_TV_TYPE=4;
                   exe_setup_function(STR_OS_TV_RATIO,STR_OS_16_9,1);
                   run_save_sel_cmd(0,3);
                   ExitSetupPage(1);
                   break;
         case 0x0d:  //4:3LB
                   SETUP_TV_TYPE=3;
                   exe_setup_function(STR_OS_TV_RATIO,STR_OS_4_3LB,1);
                   run_save_sel_cmd(0,3);
                   ExitSetupPage(1);
                   break;
         case 0x03:  //4:3PS
                   SETUP_TV_TYPE=2;
                   exe_setup_function(STR_OS_TV_RATIO,STR_OS_4_3PS,1);
                   run_save_sel_cmd(0,3);
                   ExitSetupPage(1);
                   break;
         default:

                   break;

     }

}
#endif
//
//
#ifdef ADD_DVI311_SETUP
#include "spv301.h"
extern void scaler_main(void);

void set_default_value_dvi(void)
{
    if(getVPP_TVsystem())
    	dvi311_tv_mode = 0x84; //0x85:NTSC, 0x86:PAL60, 0x84:PAL, 0x7a:AUTO
	else
        dvi311_tv_mode = 0x85; //0x85:NTSC, 0x86:PAL60, 0x84:PAL, 0x7a:AUTO

	//dvi311_format = STR_OS_DIGIT_OUTPUT; //output format:0xb7:模拟输出, 0xb8:数字输出 //for default digital output.Modifed by ChenZhao on 2004-10-19 11:15

    #ifdef DVI311_NO_PC_MODE
        dvi311_mode = Mode_480P;
    #else
        dvi311_mode =Mode_XGA;// 3; //output mode:0:720P, 1:576P, 2:480P, 3:SXGA, 4:XGA, 5:SVGA, 6:VGA
    #endif

    SETUP_DVI_MODE=dvi311_mode+2;
	Power_off_311=1;   //kevin0710
}


#endif

void set_default_value(void)
{
    int     i,j;

    #ifdef SUPPORT_FUNCTION_MENU
    {
          for(i=0;i<MAX_PAGE_ITEM_PLUS;i++)
          {

            if(setup_item_plus[0][i][1] == STR_OS_BRIGHTNESS)
            {
                setup_sel_plus[0][i] = DEFAULT_BRIGHTNESS;
            }
            else if(setup_item_plus[0][i][1] == STR_OS_TV_RATIO)
            {
                setup_sel_plus[0][i] = MIN_ITEM_SEL_PLUS;
            }
            else
            {
                setup_sel_plus[0][i] = MIN_ITEM_SEL_PLUS;
            }
          }
        }
    #endif //end #ifdef SUPPORT_FUNCTION_MENU

    for(i=0;i<(MAX_SETUP_PAGE+MAX_CUSTM_SETUP_PAGE);i++) {
        for(j=0;j<MAX_PAGE_ITEM;j++) {

        #if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)//zhaoyanhua add 2003-11-29 20:52
            if(i == ONEKEYPASSPAGE)
                continue;
        #endif

            //rating and password
            if((setup_item[i][j][1]==STR_OS_RATING)||(setup_item[i][j][1]==STR_OS_PASSWORD)||(setup_item[i][j][1]==STR_OS_REGION_CODE))//nono 20031122
                continue; //grade item need not load default value

#ifdef SUPER_DEFAULT_OSD_LANG
            if(i==CUSTMPAGEINDEX)
            {
                if(setup_item[i][j][1]==STR_OS_OSD)
                    continue;
            }
#endif
            #ifndef ARGUS_PORTABLE_DVD
            if(setup_item[i][j][1]==STR_OS_TV_SYS)
            {
                setup_sel[i][j]=MIN_ITEM_SEL+DEFAULT_TV_SYS;
                //setup_tv_format(DEFAULT_TV_SYS); // Robert 020919
                exe_setup_function(STR_OS_TV_SYS,setup_item[SYSPAGE][TV_FORMAT][setup_sel[i][j]],1);//terry.2004/2/3 01:41PM
            }
            else
            #endif
            
            #ifdef OP_MODE_DEFAULT_RF	//zxb 2005-5-8 12:55				
	    	if(setup_item[i][j][1]==STR_OS_DOLBY_OP_SETUP)            
                setup_sel[i][j]=MIN_ITEM_SEL+1;                             
            else      	
            #endif	
            
            if(setup_item[i][j][1] == STR_OS_SUBTITLE_LANG_SETUP) {  //Jeff 20021007
                setup_sel[i][j] = DEFAULT_SUBT_LANG;
            }
            #ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-25 0:13
            else if(setup_item[i][j][1] == STR_OS_SUBTITLE_LANG_2ND_SETUP) {
                setup_sel[i][j] = DEFAULT_SUBT_LANG_2ND;
            }
            #endif
            else if(setup_item[i][j][1] == STR_OS_AUDIO_LANG_SETUP) {   //Jeff 20021007
                setup_sel[i][j] = DEFAULT_AUDIO_LANG;
            }

            else if(setup_item[i][j][1] == STR_OS_MENU_LANG_SETUP) {   //Jeff 20021007
                setup_sel[i][j] = DEFAULT_MENU_LANG;
            }

//gerry mark it,2003-12-23 15:59
/*
#ifdef DEFAULT_S_VIDEO_OUTOUT           //gerry for panda dvd,3-8-23 18:30
            else if(setup_item[i][j][1] == STR_OS_VIDEO) {
                setup_sel[i][j] = MIN_ITEM_SEL+4;
            }
#endif
*/

#ifdef EASTECH_DEFAULT_S_VIDEO_OUTOUT
            else if(setup_item[i][j][1] == STR_OS_VIDEO) {
                setup_sel[i][j] = MIN_ITEM_SEL+1;
            }
#endif
#ifdef SETUP_ITEM_NO_DOWNSAMPLE_AND_DEFAULT_96K
            else if(setup_item[i][j][1] == STR_OS_FREQ_MASK) {
                setup_sel[i][j] = MIN_ITEM_SEL+1;
            }
#endif
#ifdef SETUP_ITEM_NO_DOWNMIX_AND_DEFAULT_STEREO
            else if(setup_item[i][j][1] == STR_OS_DOWNMIX_SETUP) {
                setup_sel[i][j] = MIN_ITEM_SEL+1;
            }
#endif

#ifdef GBM_PORTABLE_DVD
#ifdef USE_RGB_TFT
            else if(setup_item[i][j][1] == STR_OS_VIDEO) {
                setup_sel[i][j] = MIN_ITEM_SEL+3;
            }
#endif
#endif

#if defined(DEFAULT_MIC_OFF)            //gerry for panda dvd,3-9-2 18:06
            else if(setup_item[i][j][1] == STR_OS_MIC_ONOFF) {
                setup_sel[i][j] = MIN_ITEM_SEL+1;
            }
#endif

#ifdef SOUND_EFFECT_MENU   //sunzhh add  2004-4-28 13:56
        else if(setup_item[i][j][1] == STR_OS_EQ){
                    setup_sel[i][j] = MIN_ITEM_SEL+0;
            }
        else if(setup_item[i][j][1] == STR_OS_SURR){
                    setup_sel[i][j] = MIN_ITEM_SEL+5;
            }
#endif                          //#ifdef SOUND_EFFECT_MENU

#ifdef  JIEKE_DVD
        else if(setup_item[i][j][1] == STR_OS_SSAVER_SETUP){
                    setup_sel[i][j] = MIN_ITEM_SEL+1;
            }
        else if(setup_item[i][j][1] ==STR_OS_AUD_OUT){
                    setup_sel[i][j] = MIN_ITEM_SEL+1;
            }
#endif
#if defined(BBK_NEW_SETUP)||defined(BBK_SIMPLE_SETUP)||defined(TV_TYPE_DEFAULT_43LB)//ZXB 2005-5-8 12:57
        else if(setup_item[i][j][1] == STR_OS_TV_RATIO){
                    setup_sel[i][j] = MIN_ITEM_SEL+1;
            }
#endif

#if defined(SSAVER_DEFAULT_OFF)
        else if(setup_item[i][j][1] == STR_OS_SSAVER_SETUP){
                    setup_sel[i][j] = MIN_ITEM_SEL+1;
            }
#endif
#if defined(SLEEP_DEFAULT_OFF)
        else if(setup_item[i][j][1] == STR_OS_SLEEP_SETUP){
                    setup_sel[i][j] = MIN_ITEM_SEL+6;
            }
#endif

#ifdef  GBM_SAME_DISC_RESUME_DEFAULT_ON         //gerry,2004-1-30 20:45
        else if(setup_item[i][j][1] == STR_OS_RESUME){
                    setup_sel[i][j] = MIN_ITEM_SEL+1;
            }
#endif
#if defined(ADD_P_SCAN_ONOFF)
        else if(setup_item[i][j][1] == STR_OS_P_SCAN_YUV){
                    setup_sel[i][j] = MIN_ITEM_SEL+1;
            }
#endif
        #if defined(ADD_DVI311_SETUP)//for default digital output.Added by ChenZhao on 2004-10-19 11:18
        else if(setup_item[i][j][1] == STR_OS_DVI311_FORMAT){
                    setup_sel[i][j] = MIN_ITEM_SEL+1;//+0 analog/+1 digital
            }
    #endif
        #ifdef HDMI
        else if(setup_item[i][j][1] ==STR_OS_AUD_OUT){
            setup_sel[i][j] = MIN_ITEM_SEL+2;//for default spdif PCM output for HDMI output.Modifed by ChenZhao on 2004-10-21 10:51
            }
#endif
            else {
                setup_sel[i][j]=MIN_ITEM_SEL;
            }
        } //for(j=0;j<MAX_PAGE_ITEM;j++) {
    } //for(i=0;i<(MAX_SETUP_PAGE+MAX_CUSTM_SETUP_PAGE);i++) {

#ifdef TONIC_DVD
    SETUP_BASS_MODE = 2;        //dingzhy  for tonic   2004-2-11 13:24
#endif

#ifdef SUPER_DEFAULT_OSD_LANG
    SETUP_OSD_LANG = UserSet.setup_default_osd_lang + 2;
#else
    SETUP_OSD_LANG = DEFAULT_OSD_LANG+2;
#endif


#ifdef SUPPORT_PROLOGIC_II  //axel 2004/1/26 11:43
#ifdef DEFAULT_PROLOGIC_MUSIC     //HIMAGE1251   //fengjl add 2004-02-25 09:39
    SETUP_PROLOGIC_II=3;//4;    // alan, 3-8-8 18:30
#else
    SETUP_PROLOGIC_II=4;//4;    // alan, 3-8-8 18:30
#endif
    //assign default value for special items(such as scaleable items, echo, key...)
#endif

#ifdef NOT_SHOW_MIC_SETUP_DAFAULT_AUTO
    AUDIF_Set_MICStatus(STATUS_AUTO, 0);//2004AUDDRV AudioSetMIC(2, 0); //Set MIC auto detect(the second parameter:unsed now)
#endif//NOT_SHOW_MIC_SETUP_DAFAULT_AUTO


#ifdef DIG_AND_AUD//2004-7-2 1:57
    AUDIF_Set_OutputMode(OUT_51DownmixLtRt, 0);//2004AUDDRV AudioSetOutputMode(0x08, 0); //Set Output mode(8:AC3 downmix Lt/Rt)
                        if (full_scrn & SETUP)
                            setup_ShowAC3Config();

    AUDIF_Set_FSPKGain(8);//2004AUDDRV AudioSetFSPKGain(8);
#endif

    //echo
#ifdef KSD_DVD  //wangap 03/08/13
    #ifdef NO_MIC   // liweihua add 03-8-8 21:09
    SETUP_ECHO = 2;
    #else
    SETUP_ECHO = 8;
    #endif
    echo_level = 6;
#elif defined(VTREK_DVD)
    #ifdef NO_MIC
    SETUP_ECHO = 2;
    #else
    SETUP_ECHO = 6;
    #endif
    echo_level = 0;
#elif defined(HUAJIA_DVD)
    #ifdef NO_MIC
    SETUP_ECHO = 2;
    #else
    SETUP_ECHO = 9;
    #endif
    echo_level = 7;
#elif defined(NINTAUS_DVD)
    #ifdef NO_MIC
    SETUP_ECHO = 2;
    #else
    SETUP_ECHO = 9;
    #endif
    echo_level = 7;
#elif defined(INIT_MAX_ECHO)//axel 2004/2/6 10:04PM
    #ifdef NO_MIC
    SETUP_ECHO = 2;
    #else
    SETUP_ECHO = 10;
    #endif
    echo_level = 8;
#elif defined(SUPPORT_EXT_AD_SHOW_MIC_AUTO_SING)  //ouyang add for extern AD achieve AUTO sing 2004-12-10 19:15
    #ifdef NO_MIC
    SETUP_ECHO = 2;
    #else
    SETUP_ECHO = 2;
    #endif
    echo_level = 0;
#else
    #ifdef NO_MIC
    SETUP_ECHO = 2;
    #else
    SETUP_ECHO = 6;
    #endif
    echo_level = 4;
#endif

#ifndef BBK_DVD    //fengjl  add 3-12-3 21:10
#ifdef DELETE_VIDEO_ITEM
        setup_tv_out(TV_SVIDEO);
        //ap_tv_out_id=TV_SVIDEO;//nono 2003-8-1 18:05
        search_ap_tv_out_id();//terry,2003/8/19 03:21PM
#endif//DELETE_VIDEO_ITEM
#endif

#ifdef SET_RETURN_TO_DEFAULT_TV_FORMAT_PAL
    setup_tv_format(MODE_PAL);
#endif//SET_RETURN_TO_DEFAULT_TV_FORMAT_PAL

    #ifdef  Ti3001_OSD_UI_2
        SETUP_AMP_VOLUME = 8;
        amp_volume_level = 6;

        SETUP_AMP_FSPK = 8;
        amp_fspk_level = 6;

        SETUP_AMP_FSPK_BALANCE = 8;
        amp_fspk_balance_level = 6;

        SETUP_AMP_SSPK = 8;
        amp_sspk_level = 6;

        SETUP_AMP_SSPK_BALANCE = 8;
        amp_sspk_balance_level = 6;

        SETUP_AMP_CSPK = 8;
        amp_cspk_level = 6;

        SETUP_AMP_SUBWOOFER = 8;
        amp_subwoofer_level = 6;

        SETUP_AMP_BASS = 8;
        amp_bass_level = 6;

        SETUP_AMP_TREMBLE = 8;
        amp_tremble_level = 6;

        SETUP_AMP_DYNAMIC= 8;
        amp_dynamic_level = 12;//6
    #endif //#ifdef  Ti3001_OSD_UI_2

    // Video related
    //SETUP_SHARPNESS = 1 + 2;

#if 1//!defined(IR_KEY_SET_VIDEO_MODE)
    SETUP_BRIGHTNESS = 6 + 2;
    SETUP_CONTRAST = 6 + 2;
    SETUP_HUE = 6 + 2;
    SETUP_SATURATION = 0 + 2;

#endif

#ifdef IR_KEY_SET_VIDEO_MODE
    //video_mode_val=ReadFromI2c(0xa0, 220,(BYTE *)&video_mode_val,1);
    video_mode_val=0;
    set_video_val(video_mode_val);
#endif

#ifdef CNTR_5SPK_VOLUME
    {
        int volume;
        int i,read_volume;
        for (i=0; i<7; i++){
            read_volume=ReadFromI2c(0xa0,ADDR_I2C_VOLUME+i,(BYTE *)&audio_volume,sizeof(audio_volume));
            volume_5SPK[i]      = audio_volume;//VOL_VALUE; //set to maximum volume
            if(i==0)
            idVolume_5SPK[i]    = Volume_Font_ID;
            else
            idVolume_5SPK[i]    = VOL_FL_ID+i-1;
            //DSPReset();
        }
    }
#endif//#ifdef CNTR_5SPK_VOLUME

    #ifdef DIP_CFG_ENABLE
    SETUP_DE_INTERLACE = 3 + 2;//2 + 2;//0 + 2;
    #endif//#ifdef DIP_CFG_ENABLE

    //key
    SETUP_KEY = 8;
    audio_key = 0;

    //mic-volume
    #ifdef NO_MIC_VOL       //gerry for EXT MIC default volume is max,3-10-6 9:31
    SETUP_MIC_VOL = 10;
    mic_volume = 8;
    #else
        #ifdef HUAJIA_DVD    //HIMAGE1251//wangfeng 2004-2-11 21:49  //fengjl edit 2004-02-25 10:42
                SETUP_MIC_VOL = 9;
        #else
    SETUP_MIC_VOL = 8;
                #endif
    #ifdef  MIC_2CHANNEL    //wangfeng 2003-09-12 22:20
    SETUP_MIC_VOL_2 = 8;
    #endif
        #if defined( HUAJIA_DVD )  //HIMAGE1251//wangfeng 2004-2-11 21:49  //fengjl edit 2004-02-25 10:42
             mic_volume = 7;
        #elif defined( SUPPORT_EXT_AD_SHOW_MIC_AUTO_SING )    //ouyang add for extern AD achieve AUTO sing 2004-12-10 19:15
             mic_volume = 0;
        #else
    mic_volume = 6;
    #endif
    #endif


#ifdef USE_PT2257_ECHO_CONTROL   //dingzhy 2005-3-7 19:10
    mcu_control_echo(echo_level);
    mcu_control_micvol(mic_volume);
#endif


    //AC3 setting

    #if defined(FUSS_TCHINESE_CUSTOMER_DEF_STEREO)||defined(DOWNMIX_DEFAULT_STEREO)
        //SETUP_SPK_DOWNMIX = 3;              //hq marked, 2004-3-21 15:21
        SETUP_SPK_DOWNMIX = DOWNMIXSTEREO;
    #elif defined(DOWNMIX_DEFAULT_LR)         //hq, 2004-3-10 16:16
        SETUP_SPK_DOWNMIX = DOWNMIXLTRT;      //2004-3-21 15:34
    #elif defined(DOWNMIX_DEFAULT_OFF)
        //SETUP_SPK_DOWNMIX = 5;              //hq marked, 2004-3-21 15:21
        SETUP_SPK_DOWNMIX = AC3DOWNMIXOFF;    //had better use macro-define. hq, 2004-3-21 15:23
    #elif defined(JIEKE_DVD)
        SETUP_SPK_DOWNMIX = 3;
    #elif defined(DOWNMIX_DEFAULT_DOWNMIXVSRND)
        //SETUP_SPK_DOWNMIX = 4;//axel 2004/1/19 05:14   4--->DOWNMIXVSRND
        SETUP_SPK_DOWNMIX = DOWNMIXVSRND;     //hq, 2004-3-21 15:37
    #elif defined(TONIC_DVD)  //oujx
        SETUP_SPK_DOWNMIX = 2;
    #else
        SETUP_SPK_DOWNMIX = 4;
    #endif


#ifdef DEFAULT_SPDIF_RAW
    #if defined(BBK_NEW_SETUP)||defined(EASTECH_NEW_SETUP_MENU)||defined(EASTECH_DP3240_SETUP_MENU)
        SETUP_SPDIF = 2;
    #else//BBK_NEW_SETUP
        SETUP_SPDIF = 3;
    #endif//BBK_NEW_SETUP

#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)&&defined(DEFAULT_SPDIF_PCM_ON)
    SETUP_SPDIF_PCM=3;
#endif

#elif defined(DEFAULT_SPDIF_PCM)
        SETUP_SPDIF = 4;
#endif

    #ifndef AC3_BASS_MANAGEMENT
        SETUP_SPK_FRONT = 10;               //0 ~ 8
        SETUP_SPK_CENTER = 10;              //0 ~ 8
        SETUP_SPK_SURROUND = 10;            //0 ~ 8
        cspk_volume=SETUP_SPK_CENTER-4;
        sspk_volume=SETUP_SPK_SURROUND-4;
        fspk_volume=SETUP_SPK_FRONT-4;
    #elif defined(BASS_MODE_DEFAULT_SM_SPK)   //fengjl add 2004-03-30 21:54
        SETUP_BASS_MODE=3;
    #endif

    SETUP_SPK_SUBWOOFER = 3;            //0:off, 1:on
    SETUP_SPK_CENTER_DELAY = 2;         //0 ~ 5, 2:0 ms
    SETUP_SPK_SURROUND_DELAY = 4;       //0 ~ 5, 4:6 ms


    //Dolby Digital Setup
    #if defined(DUAL_MONO_DEFAULT_STEREO)//fengjl  add 2004-03-12 19:21
        SETUP_AC3DIGITAL_LnR = 5-3;    //stero, nono 2-8-26 21:06
    #else
        SETUP_AC3DIGITAL_LnR = 5;    //Mixed channel, Jeff 20020513
    #endif

    #ifdef DVB_MENU_SETUP_STYLE //Maoyong 2004-12-23 11:41
    SETUP_DVB_LANG = DEFAULT_OSD_LANG + 2;
    SETUP_DVB_TIME_ZONE = DEFAULT_TIME_ZONE + 2;
    #endif
//gerry move it,2004-2-6 13:47
/*
    #if 1//defined(VTREK_DVD)||defined(MINTON_DVD)//nono 20031117
    SETUP_AC3DIGITAL_DYNA = 2; //Jeff 20020604
    #else
    SETUP_AC3DIGITAL_DYNA = 10; //Jeff 20020604
    #endif
*/
    #ifdef FUSS_TV_DVD//nono 2-8-20 12:55
        UserSet.P_V_CFG = 0x0d00;
    #endif

    //SETUP_CUSTM_REGION = REGION_NUM+2;   //Jeff 20021012//nono marked 2003-11-21 10:46

/*
#if 1//def MINTON_DVD//nono 20031117
    ac3_dynarange = 0; //hq,3-11-10 20:11
    SETUP_AC3DIGITAL_DYNA = 2;
#else
    ac3_dynarange = 8;
    SETUP_AC3DIGITAL_DYNA = 10;
#endif
*/
#ifdef HUAJIA_DVD //wangfeng 2004-2-18 14:34
    ac3_dynarange = 8;
    SETUP_AC3DIGITAL_DYNA = 10;
#elif defined(SETUP_DONGLI459)//||defined(EASTECH_NEW_SETUP_MENU)
    ac3_dynarange = 8;
    SETUP_AC3DIGITAL_DYNA = 10;
#else
    ac3_dynarange = 0;
    SETUP_AC3DIGITAL_DYNA = 2;
#endif

#ifdef ADD_DVI311_SETUP
set_default_value_dvi();
#endif

    if (audio_channel!=0) { //Jeff 20030919
        AUDIF_Set_OutputMode(0+1, 0);//2004AUDDRV AudioSetOutputMode(0+1, 0); //set to audio_channel default
    }
    audio_channel = 0; // Robert 021008

//#if (defined(SAME_DISC_RESUME)&&!defined(GBM_FULL_FUNCTION))||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)       //freyman 2004-3-25 23:59
    page = SysNextPage;
    #ifdef SAME_DISC_RESUME
    same_disc_onoff = 0;
    #endif
#else
    page = 0;
#endif

#ifdef USE_FREQ_MASK    //default output 48K fengjl add  3-12-1 22:38
SETUP_FREQ_MASK   = 2;
#endif

#ifdef TUNR_OFF_PARENTAL_LVL
    bTurnOffParentalLVL=0;//zhaoyanhua 2003-12-1 20:10
#endif

#if defined(ONLY_DOWNMIX)
    #ifdef USE_4334_OR_4344_DAC
   /*caoh 2005-3-16
   If you use 4334 Or 4344 when 1*16M,the DAC no audio
   */
    AUDIF_RampDown_DSP(1);;
    AUDIF_RampUp_DSP(1);
    AUDIF_RampWait_DSP();
    #endif
    exe_setup_function(STR_OS_BASS_MANAGEMENT,STR_OS_BASS_MODE_1,0);//nono 4-3-11 18:34
#endif

#ifdef  DYNAMIC_SPECTRUM  //fengjl   3-10-27 21:08
 SETUP_BAND=3;
 bEqDisplay = 0;
#endif
    #ifdef SETUP_DONGLI459
    if(GPIO_I_GET(36)==0)
    setup_tv_out(P_SCAN);
    else
    setup_tv_out(INTERLACE);
    search_ap_tv_out_id();
    #endif  //#ifdef SETUP_DONGLI459
//xyy deleted 2004-3-8
//the amp default status setting is moved to amp_gui.c
 #ifdef SUPPORT_DEFAULT_CHANGE_REGION
    SETUP_CUSTM_REGION=REGION_NUM+2;
    UserSet.P_RCD = REGION_NUM;
 #endif

//#ifdef MINTON_YILI_LCD1003_6CH         //hq,2004-4-22 17:35
#if defined(MINTON_YILI_LCD1003_6CH)||defined(QSI_SETUP_MENU)//liweihua mod for QSI 2004-6-17
    SetBrightness(SETUP_BRIGHTNESS - 2);
    SetContrast(SETUP_CONTRAST - 2);
    SetHUE(SETUP_HUE - 2);
    SetSaturation(SETUP_SATURATION - 2);
#endif//DELETE_VIDEO_ITEM

    //added by wangwei,2004-9-17 16:05
    //(when press "DEFAULT" button in SETUP MENU,3D sound will be restored.)
    #ifdef SETUP_RESTORE_ALSO_RESTORE_3D
    restore_3Dsound();
#endif

#ifdef SET_AMP_VOL_DEFAULT  //xyy add for Oritron 2004-11-11
	extern void set_amp_default_vol(void);
	set_amp_default_vol();
#endif
}

//    xyy deleted 2004-3-8
//the amp default status settint is moved to amp_gui.c
//void set_ampsetup_default(void)

void run_set_variable(void)
{
    int     i,j;
//freyman 2004-3-26 0:00, for when next page used MAX_SETUP_PAGE is defined 7 in setup_def.h
//#if (defined(SAME_DISC_RESUME)&&!defined(GBM_FULL_FUNCTION))||defined(SHOW_STANDBY_TIMER)//for the next sys-page is P.7,wangfeng 2003-12-1 17:49
//    for(i=0;i<MAX_SETUP_PAGE+1;i++)
//#else
    for(i=0;i<MAX_SETUP_PAGE;i++)
//#endif
        for(j=0;j<MAX_PAGE_ITEM;j++)
        {
        #if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)
            if(i == ONEKEYPASSPAGE)
            {
                SETUP_SPK_DOWNMIX = DOWNMIXSTEREO;
                //TV format
                SETUP_TV_FORMAT = 2;//NTSC;
                exe_setup_function(setup_item[i][0][1],setup_item[i][0][DOWNMIXSTEREO],1);
                exe_setup_function(setup_item[i][1][1],setup_item[i][1][2],1);
                continue;
            }
        #endif

            sel=setup_sel[i][j];

            if (setup_item[i][j][1]!=STR_OS_SSAVER_SETUP)
            {
            	#ifdef SELECT_MEDIA_IN_SETUPMENU	//Maoyong 2004/8/11 run default setting should ignore media selection item
            	if(setup_item[i][j][1] ==STR_OS_MEDIA_TYPE)
            		continue;
            	#endif

                //only setting variable ,not run function...
                //printf("i:%d  j:%d sel:%d",i,j,sel);
                if(setup_item[i][j][1]==STR_OS_RATING)
                {
                    if( (sel<RATE_LOW)||(sel>RATE_HIGH) )
                    {
                        sel = RATE_DEFAULT;
                        setup_sel[i][j]=sel;
                    }
                }
#ifdef GBM_DVD
                if (setup_item[i][j][1]==STR_OS_TV_SYS)
                {
                    exe_setup_function(setup_item[i][j][1],setup_item[i][j][sel],1);
                }
                else
#endif
                exe_setup_function(setup_item[i][j][1],setup_item[i][j][sel],0);
            }
        }

        //added by wangwei,2004-9-17 16:05
    	   //(when press "DEFAULT" button in SETUP MENU,3D default set will be saved and loaded.)
		#ifdef REMB_3DSOUND
        run_sound_save(sound_sel);
        load_3Dsound(sound_sel,user_osd_set);
        sound_set_EQ_again();  //(after restore SETUP MENU,when comeback to play and don't show 3D menu,there will be no sound effect,so add it here.)
        #endif

        safe_srn_forceOFF();
		#ifdef OSD_DYNAMIC_ONOFF
			//printf("*****Load setup value to shared memory!!!\n");
			pDVB->tv_format = tv_format;
			pDVB->tv_out_id = tv_out_id;
			pDVB->osd_font_mode = osd_font_mode;
			pDVB->menu_on = 0;
			//printf("***** tv format = %d\n", tv_format);		
			//printf("***** tv_out_id = %d\n", tv_out_id);
		#endif
}

#ifdef SUPPORT_PASSWD3
extern UINT8 setup_audio_mode;
void chg_audio_default_mode(void)
{
   WriteToI2c(0xa0, 0,(BYTE *)&setup_audio_mode,1);//audio mode
}
#endif

void init_mode_val(void)
{
#ifdef VOLUME_RECODE
{
   int r;
   int i;

   #ifdef CNTR_5SPK_VOLUME//wangfeng 2003-11-11 21:27
   for (i=0; i<7; i++)
   {
    #ifdef SW_VOL_63
      if(i==6) audio_volume  = SUB_DEFAULT;
          else audio_volume = DEFAULT_VOL;
        #else
          audio_volume = DEFAULT_VOL;
        #endif

        //audio_volume = VOL_VALUE;       //set to max volume  at the first time  gerry 2-11-6 9:24
        r=WriteToI2c(0xa0, ADDR_I2C_VOLUME+i, (BYTE *)&audio_volume,sizeof(audio_volume));
   }//for

   audio_volume=DEFAULT_VOL;
   volume_Switch=0;

   #else//CNTR_5SPK_VOLUME//wangfeng 2003-11-11 21:27
    audio_volume = DEFAULT_VOL;       //set to max volume when we default gerry 2-11-6 9:26;
    r=WriteToI2c(0xa0, ADDR_I2C_VOLUME+i, (BYTE *)&audio_volume,sizeof(audio_volume));
   #endif
}
#endif//#ifdef VOLUME_RECODE

#ifdef IR_KEY_SET_VIDEO_MODE
   video_mode_val=0;
   WriteToI2c(0xa0, VIDEO_MODE_I2C_ADDRESS,(BYTE *)&video_mode_val,1);
#endif

#ifdef SUPPORT_PASSWD3
   setup_audio_mode=0;
   chg_audio_default_mode();
#endif

}

void read_record_val(void)
{

#ifdef VOLUME_RECODE     //read volume from I2C    gerry  2-11-5 16:47
    int i,r;

  #ifdef CNTR_5SPK_VOLUME
  for (i=0; i<7; i++)
  {
    r=ReadFromI2c(0xa0,ADDR_I2C_VOLUME+i,(BYTE *)&audio_volume,sizeof(audio_volume));
    //printf("%%%%%%^^^^^^r==<%d>:audio_volume=====>%d\n",r,audio_volume);

    if(r<=0) audio_volume = DEFAULT_VOL;       //set to max volume when we default gerry 2-11-6 9:26;
    volume_5SPK[i] = audio_volume;//VOL_VALUE; //set to maximum volume
    if(i==0) idVolume_5SPK[i]    = Volume_Font_ID;
    else     idVolume_5SPK[i]    = VOL_FL_ID+i-1;
  } //for

  audio_volume  = volume_5SPK[0] ;
  volume_Switch = 0;     //set to main volume
  #else
  r=ReadFromI2c(0xa0,ADDR_I2C_VOLUME+i,(BYTE *)&audio_volume,sizeof(audio_volume));
  audio_volume = (audio_volume <= DEFAULT_VOL)?audio_volume:DEFAULT_VOL;
  //printf("%%%%%%^^^^^^r==<%d>:audio_volume=====>%d\n",r,audio_volume);
  #endif
#endif //VOLUME_RECODE

#ifdef IR_KEY_SET_VIDEO_MODE
  int r;
  r=ReadFromI2c(0xa0, VIDEO_MODE_I2C_ADDRESS,(BYTE *)&video_mode_val,1);
  //printf("%%%%%%^^^^^^r==<%d>:video_mode_val=====>%d\n",r,video_mode_val);
  if(r<=0) video_mode_val=0;
  set_video_val(video_mode_val);
#endif

#ifdef SUPPORT_PASSWD3
  ReadFromI2c(0xa0,0,(BYTE *)&setup_audio_mode,1);
#endif

}

void init_val_by_record(void)
{
    //echo: shift to 0 ~ 8
        #ifdef NOT_REWRITE_MIC_VALUE  //axel 2004/2/8 10:05PM
        echo_level = 8;
        #else
        echo_level = SETUP_ECHO - 2;
        #endif  //NOT_REWRITE_MIC_VALUE

        //key: shift to -6 ~ 6
        #ifdef NOT_REWRITE_MIC_VALUE  //axel 2004/2/8 10:05PM
        audio_key = 0;
        #else
        audio_key = SETUP_KEY - 2 - 6;
        #endif  //NOT_REWRITE_MIC_VALUE

        //mic-volume: shift to 0 ~
        #ifdef  MIC_2CHANNEL    //wangfeng 2003-09-12 22:20
        if(id==STR_OS_MIC_VOL_1)
        #endif
        #ifdef NOT_REWRITE_MIC_VALUE  //axel 2004/2/8 10:05PM
        mic_volume = 6;
        #else
        mic_volume = SETUP_MIC_VOL - 2;
        #endif //NOT_REWRITE_MIC_VALUE

        #ifdef  MIC_2CHANNEL
        else if(id==STR_OS_MIC_VOL_2)
        mic_volume = SETUP_MIC_VOL_2 - 2;
        #endif

        ac3_dynarange = SETUP_AC3DIGITAL_DYNA - 2;

#ifdef DYNAMIC_SPECTRUM       //zhaoyanhua add  2003-12-3 11:42
       if(SETUP_BAND == 2)
       {
            band_onoff = 1;
            bEqDisplay = 1;
       }
#endif
}

#ifdef MONE_SETUP
void dump_setup_val(void)
{
  int i, j;

  printf("read eeprom setup menu,ok!!\n");
  for (i=0; i<MAX_SETUP_PAGE+MAX_CUSTM_SETUP_PAGE; i++) {
    for (j=0; j<7; j++) {
        printf("setup_sel[%d][%d]=%d\n", i, j, setup_sel[i][j]);
    }
  }
}
#else
#define dump_setup_val();
#endif

#ifdef DIVX_DRM//nono 5-5-23 23:59 setup this function.
//linrc move to memmap_I2C.h
//#define DRM_REG_CODE_I2C_ADD_ST 208
//#define DRM_REG_CODE_I2C_ADD_LEN 48

void clear_drm_reg_code_buf(void)
{

    char buf[DRM_REG_CODE_I2C_ADD_LEN];
    int i;
    for (i=0;i<DRM_REG_CODE_I2C_ADD_LEN;i++)
    buf[i] = 0;

    if(WriteToI2c(0xa0, DRM_REG_CODE_I2C_ADD_ST, buf, DRM_REG_CODE_I2C_ADD_LEN) >= 0)
    {
        printf("DRM: clear EEPROM data.\n");
    }
    else
    {
        printf("DRM: clear EEPROM error !\n");
    } 

}
#endif//#ifdef DIVX_DRM

#if defined(FORCE_REWRITE_WHEN_UPGRADE)||defined(FORCE_REWRITE_DRM_WHEN_UPGRADE)//terry,2004/1/8 05:28PM
//nono add FORCE_REWRITE_DRM_WHEN_UPGRADE.for EASTECH 5-5-27 1:26
void load_user_setup(UINT8 force_update)
#else
void load_user_setup(void)
#endif
{
//    int     i,j;
    int     iRts;
    UINT16  unChksum,unTmp;
    BYTE    *p;
    UINT32      romSum=0;

    #ifdef MONE_SETUP
    printf("load setup menu,in\n");
    #endif

    //get ROM-code-checksum from ROM(20th ~ 23th Byte)
    {
        UINT32  *pSum;
        pSum = (UINT32 *)(ROM_BASE_UNCACHED+0x40);
        romCheckSum = *pSum &0xffffff;
    }

    //read ROM-code-checksum from setup EEPROM(flash)(0-th Byte)
    p = (BYTE *)(&romSum);
    iRts = ReadFromI2c(0xa0, 1, p, 3);
    WriteToI2c(0xa0, 1, (BYTE *)&romCheckSum,3);//save rom check sum
    printf("romCheckSum:%x %x\n",romCheckSum,romSum);

#ifdef FORCE_REWRITE_WHEN_UPGRADE//terry,2004/1/8 05:28PM
    if(force_update==1)
    {
        romSum = 0;
    setup_sel[SYSPAGE][GRADEITEM]=RATE_DEFAULT;
        NP_PTL_LVL = 8;//zhaoyanhua  2004-3-9 11:32 after UPGRADE, must set parent level is 8.
    }
#endif

#if defined(FORCE_REWRITE_DRM_WHEN_UPGRADE)
    if(force_update==1)
    {
	clear_drm_reg_code_buf();
    }
#endif//FORCE_REWRITE_DRM_WHEN_UPGRADE

    #ifdef SELECT_MEDIA_IN_SETUPMENU //Maoyong always default as Disc 2004-8-9 15:33
    SETUP_MEDIA_TYPE = DISC_ITEM + 2;
    #endif

    if (iRts > 0)
    {//read ok
        if (romSum==romCheckSum)
        {//read setup setting from setup EEPROM(2-th Byte)
             #ifdef Ti3001_OSD_UI_1
              load_amplifier_setup();   // jason add 2-10-5 15:59
             #endif
            p=(BYTE *)setup_sel;
            iRts=ReadFromI2c(0xa0, sizeof(UINT32), p, sizeof(setup_sel));
            //yanlb added 2004/07/07
    	    #ifdef  REMB_3DSOUND
		        load_3Dsound(sound_sel,user_osd_set);
	        #endif
        } else
        {//flash upgrade
            iRts = -1;
            //if rom0-check-sum is not equal, set to default password, Jeff 20020703
            #ifdef SUPER_DEFAULT_OSD_LANG
            UserSet.setup_default_osd_lang = DEFAULT_OSD_LANG;
            #endif
            UserSet.parent_passwd = DEFAULT_PASSWORD;
            WriteToI2c(0xa0, sizeof(UINT32)+sizeof(setup_sel)+2, (BYTE *)&UserSet, sizeof(t_USER_SET));



#if defined(RADIO_2006)//huziqin 2006-4-19
            init_tuner_var();
#endif
            //init mode
            init_mode_val();
        } //if (romSum==romCheckSum) {
    } //if (iRts > 0) {

    //read audio/video mode
    read_record_val();

    if(iRts>0)
    {
        init_val_by_record();
        dump_setup_val();

        //read setup checksum from setup EEPROM
        iRts=ReadFromI2c(0xa0, sizeof(UINT32)+sizeof(setup_sel), (BYTE *)&unChksum, 2);
        if (iRts>0)
        {
            printf("read eeprom setup check success\n");
            //count setup checksum
            unTmp = run_save_unChk_cmd(0);
            //check setup checksum and counted checksum
            if (unTmp!=unChksum)
            {
                printf("check sum error, uTmp=%d unCkhsum=%d\n",unTmp,unChksum);
                iRts=-2;
            }
            else
            {
                printf("check sum success\n");
#ifdef EASTWIN
                if(SETUP_VIDEO_FORMAT==5)//jhuang eastwin 2004/8/16
                {
                	SETUP_VIDEO_FORMAT = MIN_ITEM_SEL;
                	run_save_sel_cmd(SYSPAGE,2);
                	setup_tv_out(INTERLACE);

                }
#endif
            }

        }
        else
        {
            printf("read eeprom setup check error\n");
        }

        #ifdef MONE_SETUP
        printf("chksum=%02x\n",unChksum);
        #endif
    }

    if (iRts < 0)
    {
        //set to default, when
        //1. different ROM-code-checksum(setup-EEPROM vs. ROM)
        //2. counted setup-checksum != stored in setup EEPROM

        #ifdef MONE_SETUP
        printf("read eeprom setup menu,fail!!\n");
        #endif

        SETUP_CUSTM_REGION = REGION_NUM+2; //nono 20031121
        UserSet.P_RCD = REGION_NUM;

        set_default_value();
        run_save_total_sel();



        #ifdef Ti3001_OSD_UI_1    // jason 2-10-5 15:30
    reset_amplifier_default_setup();
        #endif

        #ifdef POWER_RESUME
        RsmInfo2Flash(1); //clear resume flash memory, Jeff 20020928
        #endif

#ifdef DIVX_DRM//nono test 5-5-23 23:58 for clearing registration code.
    #ifndef SUPPORT_DIVX6 //for divx6 certification, this should not be cleared
	clear_drm_reg_code_buf();
    #endif  //#ifndef SUPPORT_DIVX6 
/*
	if(ReadFromI2c(0xa0, 208, buf, 48) >= 0)
	{
		printf("setup: read from EEPROM data.\n");
		
		for (j=0;j<48;j++)
		printf("Addr: %d, %d, %08x\n", 0xa0, 208, buf[j]);
    }
*/
#endif
	
    }

    //read UserSet for DVD-related
    //if (iRts>0)
    iRts=ReadFromI2c(0xa0, sizeof(UINT32)+sizeof(setup_sel)+2, (BYTE *)&UserSet, sizeof(t_USER_SET));
    if(iRts>0)
    {
        printf("read eeprom system menu,ok!!\n");
        UserSet.P_RCD = SETUP_CUSTM_REGION - 2;
    } else
    {
        printf("read eeprom system menu,fail!!\n");

        SETUP_CUSTM_REGION = REGION_NUM+2; //Jeff 20021012
        UserSet.P_RCD = REGION_NUM;
    }

    SETUP_CUSTM_REGION = UserSet.P_RCD+2;

    #ifdef SUPER_DEFAULT_OSD_LANG
    SETUP_CUSTM_OSDLANG = UserSet.setup_default_osd_lang + 2;
    #endif

    run_set_variable();

//David added 2003-12-17 23:01 temp
//Syber required: No need switch video output, only YUV default
#if defined(YUV_DEFAULT_OUTPUT) && defined(DELETE_VIDEO_ITEM)
        #ifdef S_VIDEO_OUT
       regs0->emu_cfg[1]|=0x100;
        #endif //#ifdef S_VIDEO_OUT
        setup_tv_out(INTERLACE);//set S-video output(composited+component)(0x00:D0-D1-D2-D3=CVBS-V-Y-U)
        search_ap_tv_out_id();//terry,2003/8/19 03:21PM
#endif
    //UserSet.M_LCD = 'z' * 256 + 'h';
    //china zh ,taiwan tw
    //china

    UserSet.CTY_CD=('C'<<8)|('N');

    UserSet.P_A_CFG=0xffff;// should be config//uinted states:US ,china:CN , taiwan:TW

    if (SETUP_PASSWORD == (MIN_ITEM_SEL+1) ) {
        UserSet.parental_ststus=C_UNLOCK;
    } else {
        UserSet.parental_ststus=C_LOCK;
        SETUP_PASSWORD = MIN_ITEM_SEL;
    }


#ifdef ADJUST_JPEG_SLIDE_TIME  //lyc  2005-3-7 17:38
    BYTE  JpegSlideTimeFlag = UserSet.SETUP_JpegSlideTimeFlag;
    //iRts=ReadFromI2c(0xa0, ADDR_I2C_JPEG_SLIDE_TIME,&JpegSlideTimeFlag ,1);
    //if(iRts>0)
    //{
      switch(JpegSlideTimeFlag)
      {
        case 1:
           jpg_slide_time = 1500;
           break;
        case 2:
           jpg_slide_time = 3000;
           break;
        case 3:
           jpg_slide_time = 4500;
           break;
        default://lijd 2005-4-21 16:49
       jpg_slide_time = JPEG_SLIDE_TIME;
           break;
       }

    // }
    // else
    //   jpg_slide_time = JPEG_SLIDE_TIME;
#else//#ifdef ADJUST_JPEG_SLIDE_TIME  //lyc  2005-3-7 17:38
       jpg_slide_time = JPEG_SLIDE_TIME;
#endif//#ifdef ADJUST_JPEG_SLIDE_TIME  //lyc  2005-3-7 17:38


    #ifdef MONE_SETUP
    printf("load setup menu,out\n");
    #endif

    //check password and grade
    #ifdef RATING_8
#ifdef EASTECH_NO_PARENTAL_CONTROL
        if ( (SETUP_GRADE<2) || (SETUP_GRADE>RATE_HIGH) ) {
            SETUP_GRADE = RATE_HIGH;
#else
        if ( (SETUP_GRADE<2) || (SETUP_GRADE>9) ) {
            SETUP_GRADE = 9;
#endif
//            UserSet.parent_passwd = 0;//NONO mark it.3-11-23 22:17
//            UserSet.parental_ststus = C_UNLOCK;//NONO mark it.3-11-23 22:17
            UserSet.parent_passwd = DEFAULT_PASSWORD; //Jeff 20020703
        }
    #else
        if ( (SETUP_GRADE<2) || (SETUP_GRADE>4) ) {
            SETUP_GRADE = 4;
            UserSet.parent_passwd = 0;
            UserSet.parental_ststus = C_UNLOCK;
            UserSet.parent_passwd = DEFAULT_PASSWORD; //Jeff 20020703
        }
    #endif
#ifdef SETUP_6_DIGIT_PASSWORD//zhaoyanhua add 03-10-14 14:10
    if (UserSet.parent_passwd > 999999)
#else //4 digit
    if (UserSet.parent_passwd > 9999)
#endif   //end   SETUP_6_DIGIT_PASSWORD
    {
        UserSet.parent_passwd = 0;
        UserSet.parental_ststus = C_UNLOCK;
    }

    setupLevel = 0;

	#ifdef SAME_DISC_RESUME //zxb if define SAME_DISC_RESUME without resume item 
	                        //,default resume on.
	same_disc_onoff=1;	
	#endif

    #if defined(SAME_DISC_RESUME)&&defined(NEXTPAGE_SYS)//freyman 2004-3-26 0:01 alan, 3-9-30 18:59
    if(setup_sel[SysNextPage][SAME_DISC_RESUME_ITEM]==3)
    same_disc_onoff=1;
    else
    same_disc_onoff=0;//CLEAD 2003-9-29
    printf("\n\n====same_disc_onoff:%d====\n",same_disc_onoff);
#endif

#ifdef BBK_DVD   //fengjl add 3-11-25 22:09  for YUV output when next power on
    #define   VIDEO_OUTPUT_OFFSET   240
    int res = ReadFromI2c(0xa0, VIDEO_OUTPUT_OFFSET,(BYTE *)&tv_out_id,sizeof(tv_out_id));
    if(res < 0)    tv_out_id = INTERLACE;
    setup_tv_out(tv_out_id);
    //audio key set default value.zhaoyanhua add 2003-12-4 11:44
    audio_key = 0;
#endif

#ifdef VGA_CTRL_FORMAT//wangfeng 2003-12-18 18:55
    int res = ReadFromI2c(0xa0, ADDR_I2C_VGA,(BYTE *)&temp_format,sizeof(temp_format));
    if(res)
        if(temp_format)
        {
            exe_setup_function(STR_OS_TV_SYS,temp_format,1);//terry,2004/2/3 01:34PM
        }
#endif

}



void show_main_title(int id)
{
    #ifndef SPE_SETUP   //2004-4-22 06:51张宇P
    const char *str;
    int start,len;

#ifdef DVB_SETUP_MENU         //sunzhh 20050430
    extern const char *osd_str_dvb_mainmenu[N_OSD_LANGS][2];
	if(system_state == SYSTEM_TS)
	{
		if((page == INSTALLPAGE))
		{
    		osd_DrawString(2, 2, osd_str_dvb_mainmenu[osd_font_mode][0], 7,SBLACKCOLOR/*SWHITECOLOR, SBLACKCOLOR*/);
    		return;
		}
		else if((page == CHANNELPAGE))
		{
    		osd_DrawString(2, 2, osd_str_dvb_mainmenu[osd_font_mode][1], 7,SBLACKCOLOR/*SWHITECOLOR, SBLACKCOLOR*/);
    		return;
		}
    }

#endif

    //count main menu title string length
    str   = _OsdMessegeFont1[osd_font_mode][id];
    len = strlen(str);
    if ( IsOSDChinese() ) {
        len = len*2;
    }

    start = SETUP_MAX_WIDTH/2-len+2;
    #ifdef  SETUP_COLOR_TYPE1       //wangfeng 2003-08-29 17:16
    osd_DrawString(3, 2, (char *)str, 7,SBLACKCOLOR/*SWHITECOLOR, SBLACKCOLOR*/);
    #elif defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-2 18:02
        if(id == STR_OS_SYS_SETUP)
        osd_DrawRegionString(2, 13, (char *)str, 12,SBLACKCOLOR,0);
        else if(id == STR_OS_LANG_SETUP)
        osd_DrawRegionString(8, 13, (char *)str, 12,SBLACKCOLOR,0);
        else if(id == STR_OS_AUD_SETUP)
        osd_DrawRegionString(16, 13, (char *)str, 12,SBLACKCOLOR,0);
        else if(id == STR_OS_KARAOKE_SETUP)
        osd_DrawRegionString(22, 13, (char *)str, 12,SBLACKCOLOR,0);
    #else
    osd_DrawString(2, 2, (char *)str, 7,SBLACKCOLOR/*SWHITECOLOR, SBLACKCOLOR*/);
    #endif
    #endif
}




void draw_3rd_menu()
{
    int i;
    BYTE    fontColor, bgColor;
    BYTE    upDown;
    const char   *str;
    //draw ">" between sub-mean and it's corresponding selection area
    #ifdef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 17:12
    osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SANTIFONTCOLOR, SBGCOLOR);
    #else
    osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SFONTCOLOR, SBGCOLOR);
    #endif// QSI_SETUP_MENU_DESIGN

#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-7 17:15
    if(page == VIDEOPAGE)
    {
        for(i = 0; i < (setupItemNum[1]); i++ )
        {

            if(setup_item[page][i][0] == SET_SCALE)//"EXIT" item, return
            {
                if(index_y == i)
                    fontColor = 4;
                else
                    fontColor = SFONTCOLOR;

                setup_VideoItemValue(i, fontColor,SBGCOLOR);
            }
        }
        return;
    }
#endif

    //show first selection menu of third-level menu
    for (i=2; i<MAX_ITEM_SEL; i++)
    {
        //get select item
#ifdef BBK_NEW_SETUP//zhaoyanhua add 2003-11-18 17:15
        #if !defined(BBK_DSS_555_DVD)&&!defined(BBK_DV911S) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE
        if(one_key_pass_flag)//OENKEYPASSPAGE
        {
            sel = GetOneKeyPageSel(index_y);
        }
        else
        #endif
            sel=setup_sel[page][index_y];

#else
        sel = setup_sel[page][index_y+index_y_start];
#endif
        id = setup_item[page][index_y+index_y_start][i];
        if (id==0)
        {
            if (setup_item[page][index_y+index_y_start][0]==SET_SCALE)
                setup_PrepareScaleItem(setup_item[page][index_y+index_y_start][1], 0);
            break;
        }

        str = setup_SetItemString();

        #ifdef  SETUP_COLOR_TYPE1       //wangfeng 2003-08-29 17:16
        if (sel == i)
        {
            fontColor = SDEFAULTCOLOR;//4; //SFONTCOLOR;
            bgColor =   SBGCOLOR; // SANTIBGCOLOR;
            upDown = 1;
        } else {
            fontColor = 2;//SFONTCOLOR;
            bgColor = SBGCOLOR;
            upDown = 0;
        }
    #elif defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-4 16:52
        if (sel == i)
        {
            fontColor = SDEFAULTCOLOR;//4; //SFONTCOLOR;
            bgColor =   SBGCOLOR; // SANTIBGCOLOR;
            upDown = 1;
    }
    else {
            fontColor = SFONTCOLOR;
            bgColor = SBGCOLOR;
            upDown = 0;
        }
    #else
    if (sel == i)
    {
            fontColor = 4; //SFONTCOLOR;
            bgColor =   SBGCOLOR; // SANTIBGCOLOR;
            upDown = 1;
        } else {
            #ifdef SELECT_MEDIA_IN_SETUPMENU
            if( IsSetupMediaItemDisable(i) )
                fontColor = SGRAYCOLOR;
            else
            #endif
            fontColor = SFONTCOLOR;
            bgColor = SBGCOLOR;
            upDown = 0;
        }
        #endif
        //special item(PASSWORD), page-0, item-4
        if (setup_item[page][index_y+index_y_start][0]==SET_NM)
        {
            submenuStart = index_y+SETUP_MENU_YSTART;//zhaoyanhua add 2004-1-16 11:03

            if (UserSet.parental_ststus==C_LOCK)
            {
                 setup_sel[page][index_y+index_y_start] = MIN_ITEM_SEL;
                str = _OsdMessegeFont1[osd_font_mode][STR_OS_LOCK];
            } else {
                setup_sel[page][index_y+index_y_start] = MIN_ITEM_SEL + 1;
                str = _OsdMessegeFont1[osd_font_mode][STR_OS_UNLOCK];
            }
            #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 16:41
            osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 1);
            #endif
            osd_DrawString(SETUP_SUB_XSTART+1, (submenuStart)+1, str, SANTIFONTCOLOR, SANTIBGCOLOR);
        }
        else
        {
#ifdef RATING_8
            //when I draw PASSWORD GUI, return main seutp with"ShowSetupPage()",
            //rating8 show uncorrectly. so I add the following codes
            //zhaoyanhua 2004-1-16 10:44
            if ( (page==SYSPAGE) && (index_y == GRADEITEM) )
            {
                submenuStart = SETUP_MENU_YSTART;
            }
            else
#endif
#ifdef SUPER_DEFAULT_OSD_LANG
            if(index_y==CUSTMOSDITEM)
            {
                if((8-N_OSD_LANGS)>=4)
                    submenuStart = index_y + SETUP_MENU_YSTART;
                else
                    submenuStart = SETUP_MENU_YSTART + (8-N_OSD_LANGS) + 1;
            }else
#endif
            submenuStart = index_y+SETUP_MENU_YSTART;

            #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 16:41
            osd_draw_setup_button(SETUP_SUB_XSTART, (i-2)+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, bgColor, upDown);
            #endif
            //printf("#### in draw3rdmenu    --- draw string ---\n");
            osd_DrawString(SETUP_SUB_XSTART+1, (i-2)+submenuStart+1, str, fontColor, bgColor);

        }
    }
    setupItemNum[2] = i-2;
}



void setup_func_return_main(void)
{
    setupLevel=0;
    index_y = 0;
    index_y_start=0;

    ShowSetupPage(1);
}

void ShowSel(BYTE xStart, BYTE yStart,BYTE xLen,BYTE down)
{
    BYTE        fnColor,bgColor;
    const char *str;
    str = setup_SetItemString();
    //#ifdef    SETUP_COLOR_TYPE1       //wangfeng 2003-08-29 17:16
    #if defined(SETUP_COLOR_TYPE1) || defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-4 16:46
    if (down)
        fnColor=SDEFAULTCOLOR;//4;
    else
        fnColor=SFONTCOLOR;

        bgColor = SBGCOLOR;
    #else
    if (down)
        fnColor=4;
    else
        fnColor=SFONTCOLOR;

        bgColor = SBGCOLOR;
    #endif
    #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 16:41
    osd_draw_setup_button(xStart,yStart,xLen, bgColor, down);
    #endif
    osd_DrawString(xStart+1, yStart, str, fnColor, bgColor);
}



//NOTE: the following .h files only include UI function,such as
//      LEFT,RIGHT, UP, DOWN,  SELECT, ShowSetupPage.
#ifdef NEW_STYLE_SETUP//zhaoyanhua add 3-7-25 17:29
#include "setup_newstyle_ui.c"
#elif defined(SOFT_MENU)//Modifed by ChenZhao on 2004-9-8 17:39 WP
#include "setup_tab_ui_SFM.c"
#else
#include "setup_tab_ui.c"
#endif //NEW_STYLE_SETUP



#ifdef NEW_STYLE_SETUP //zhaoyanhua add 3-7-25 19:18
void init_setup(void)
{
    page = 0;
    index_y=0;
    index_y_start=0;
    setupLevel=0;
    GBM_run_setupmenu_flag = 0;

    //setup_tv_format(MODE_NTSC);//force to NTSC zhaoyanhua note 2003-07-19 21:39
    full_scrn=SETUP;       //setup menu
    //read_setup_select();   // read data from EEPROM or Flush

    //printf("IN Init_SETUP NEW STYLE\n");

    //osd_init_setup();//zhaoyanhuamask
    //ShowSetupPage(2);//zhaoyanhua amsk
    //zhaoyanhua add the following page.
    //printf("getVPP_TVsystem():%x\n",getVPP_TVsystem());
    if(getVPP_TVsystem() ==  1)//terry,0813
    {

        osd_init_hand_ICON_for_PAL();
        setupLevel=1;
        ShowSetupPage(0);//must showsetuppage,because it will clear the rect.
        setupLevel=0;
        ShowCurrentPage_for_PAL(page);

    }else

    //if (tv_format ==  MODE_NTSC)
    {
        osd_init_hand_ICON_for_NTSC();
        setupLevel=1;
        ShowSetupPage(0);//must showsetuppage,because it will clear the rect.
        setupLevel=0;
        ShowCurrentPage_for_NTSC(page);

    }

}

#elif defined(SOFT_MENU)//Modifed by ChenZhao on 2004-9-2 14:46 WP
void init_setup(void)
{
    page = 0;
    index_y=0;
    index_y_start=0;

    setupLevel=0;   // alan, 2003/9/5 02:31と
    full_scrn=SETUP;       //setup menu
    //read_setup_select();   // read data from EEPROM or Flush
    osd_init_setup();
    ShowSetupPage(REFRESH_SETUP);
//kubby 2003-8-9 13:32 added to show focus on the title bar after enter the setup menu
}
#else  //not NEW_STYLE_SETUP
void init_setup(void)
{
#ifndef DVB_SETUP_MENU   //sunzhh 20050430
    page = 0;
#else
	if(system_state != SYSTEM_TS)
		page = SYSPAGE;
	else
		page = 0;
	dvbpage = 0;
#endif

    index_y=0;
    index_y_start=0;
#ifndef DVB_SETUP_MENU
    setupItemNum[1]=MAX_PAGE_ITEM;  // ALAN, 2003/9/9 03:32PM, to initial setupItemNum
#else
if(system_state == SYSTEM_TS)
    	setupItemNum[1]=MAX_PAGE_ITEM-3;//eric 2005-01-06 10:00 fix -1 -> -3
    else
    	setupItemNum[1]=MAX_PAGE_ITEM;
#endif

#ifdef DVB_SETUP_MENU
    set_dvb_vpp(SCREEN_TYPE_FULL);
#endif

    setupLevel=0;   // alan, 2003/9/5 02:31と
    full_scrn=SETUP;       //setup menu
    //read_setup_select();   // read data from EEPROM or Flush

#ifdef DYNAMIC_SPECTRUM//zhaoyanhua 2003-12-2 11:41
    //to avoid the bug:
    //when open SPECTRUM,then DEFAULT, cause SETUP OSD error.
    bEqDisplay = 0;
#endif

#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)
    osd_init_bbk_setup();
    index_x = ONE_KEY_PASS_X ;
    main_setup = 1;
    ShowSetupMainPage(1);
#else
    osd_init_setup();
    ShowSetupPage(2);
#endif

//kubby 2003-8-9 13:32 added to show focus on the title bar after enter the setup menu
#ifdef DESAY_DVD
    osd_draw_rect((SETUP_SUB_XSTART-1)*16,
        SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT,
        (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
        (SETUP_MAX_LINE-SETUP_MENU_YSTART-1)*SETUP_BUTTON_HEIGHT,
        SBGCOLOR);

    setupLevel=0;
    id=setup_item[page][index_y][1];
    setup_DrawItem(1, SETUP_MENU_YSTART+1, 0);

    // highlight : draw a frame to identify which tab is enable
    #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-2 17:32
    SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffff);
    #endif
    
#ifndef DVB_SETUP_MENU
        setup_Showredframe(page);
#else
        setup_Showredframe(dvbpage);
#endif
#endif

#ifdef OSD_DYNAMIC_ONOFF
	//printf("*****Into Setup Menu!!!\n");
	pDVB->menu_on = 1;
#endif

}
#endif // NEW_STYLE_SETUP


#ifdef OSD_COLOR_ADJUST_BY_BRIGHTNESS_AND_CONTRAST  // 2004/10/16 yltseng

void UpdateSetupmenuPalette()
{
    extern void osd_update_setupmenu_palette();
    osd_update_setupmenu_palette();
    #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-2 17:38
        #ifdef SETUPMENU_NOT_TRANSPARENT
    SetOsdCol(mn_osd_col2);
        #else
    SetOsdCol(mn_osd_col1);
        #endif
    #endif

}
#else

#define UpdateSetupmenuPalette()

#endif

void setup_DrawItem(BYTE level, BYTE yStart, BYTE updowngray)
{
    const char *str;
    BYTE    xStart, xWidth;
    BYTE    xOffset;

    BYTE    cFont, cBackground;
    BYTE    idString;

    #ifdef SUPPORT_FUNCTION_MENU
    if(full_scrn&SETUP_PLUS)
    {
        if (level==1)
        {
          xStart = SETUP_MENU_XSTART_PLUS;
          #ifdef SUPPORT_DISPLAY_MENU
          if(In_Display_Menu())
            xWidth = DISPLAY_MENU_LENGTH;
          else
          #endif
          xWidth = SETUP_SUB_XSTART_PLUS-SETUP_MENU_XSTART_PLUS-1;
          xOffset = 1;
          idString = id;
        }
    }
    else
    {
    #endif //end #ifdef SUPPORT_FUNCTION_MENU
    if (level==0) {
        xStart = SETUP_MENU_XSTART;
        xWidth = SETUP_MAX_WIDTH-2*SETUP_MENU_XSTART;
        xOffset = 8;
        idString = setup_MainP[page][0];
    } else if (level==1)
    {
        xStart = SETUP_MENU_XSTART;
        xWidth = SETUP_SUB_XSTART-SETUP_MENU_XSTART-1;
        xOffset = 1;
        idString = id;
    } else {
        xStart = SETUP_SUB_XSTART;
        xWidth = SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2;
        xOffset = 1;
        idString = id;
    }
    #ifdef SUPPORT_FUNCTION_MENU
    }
    #endif //end #ifdef SUPPORT_FUNCTION_MENU

    #ifdef SUPPORT_DISPLAY_MENU
    if((In_Display_Menu()) && (index_y == TITLE_TRACK_ITEM) \
         && (cd_type_loaded != CDDVD))
       	idString = id = setup_item_plus[page][index_y][1] = STR_OS_TRACK;
    else if((In_Display_Menu()) && (index_y == PBC_MENU_ITEM) \
         && (cd_type_loaded == CDDVD))
        idString = id = setup_item_plus[page][index_y][1] = STR_OS_MENU;
   	#endif


    if (updowngray==0) {        //up
        cFont = SFONTCOLOR;
        cBackground = SBGCOLOR;
    } else if (updowngray==1) { //down
        cFont = SANTIFONTCOLOR;
        cBackground = SANTIBGCOLOR;
    } else
        //if (updowngray==2)
    { //gray
        cFont = SGRAYCOLOR;
        cBackground = SBGCOLOR;
        updowngray = 0;
    }
    #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 16:41
    osd_draw_setup_button(xStart, yStart, xWidth, cBackground, updowngray);
    #endif
/*
    #ifndef BBK_NEW_SETUP//zhaoyanhua add for BBK_DVD
    if (idString==STR_OS_RETURN_MAIN_SETUP)  // no main page, so this item changes to exit_setup_menu
        idString=STR_OS_EXIT_MENU;
    #endif
*/
    #ifdef BBK_NEW_SETUP    //fengjl edit 4-1-28 14:23
    #if defined(BBK_DSS_555_DVD)||defined(BBK_DV911S)
    if (idString==STR_OS_RETURN_MAIN_SETUP)
        idString=STR_OS_EXIT_MENU;
    #endif
    #else
    if (idString==STR_OS_RETURN_MAIN_SETUP)  // no main page, so this item changes to exit_setup_menu
        idString=STR_OS_EXIT_MENU;
    #endif
#ifdef SUPER_DEFAULT_OSD_LANG
    if((page==CUSTMPAGEINDEX)&&(index_y==CUSTMOSDITEM)&&(setupLevel!=1))
    {
        str = lang_names[osd_font_mode][id];
    }
    else
#endif

		#ifndef DVB_SETUP_MENU
    		str = _OsdMessegeFont1[osd_font_mode][idString];
        #else
        	str = SetDvbItemString(idString);
        #endif //DVB_SETUP_MENU

    #ifdef SUPPORT_DISPLAY_MENU
    if((In_Display_Menu()) && (index_y == PBC_MENU_ITEM)\
        && (cd_type_loaded == CDDVD))
    {
      BYTE buf[7];

      osd_DrawString(SETUP_MENU_XSTART_PLUS+6, index_y+SETUP_MENU_YSTART_PLUS, str, cFont, cBackground);
      psprintf(buf,"GOTO");
      osd_DrawString(SETUP_MENU_XSTART_PLUS+1, index_y+SETUP_MENU_YSTART_PLUS, buf, cFont, cBackground);
    }
    else
    if(index_y != BATTERY_ITEM)
    #endif//end #ifdef SUPPORT_DISPLAY_MENU
    osd_DrawString(xStart+xOffset, yStart, (char *)str, cFont, cBackground);
#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-7 18:36
    if(page == VIDEOPAGE)
    {
        if(setup_item[page][index_y][0] == SET_SCALE)
        {
            if(updowngray)
                cFont = 4;//HLCOLOR
            else
                cFont = SFONTCOLOR;
            setup_VideoItemValue(index_y, cFont,SBGCOLOR);//show value with HL color.
        }                               //draw_3rd_menu();
    }
#endif  //VIDEO_SETUP_NEW_GUI

   #ifdef SUPPORT_DISPLAY_MENU
   if(In_Display_Menu())
   {
   	 Set_Update_Item_Flag();

     if(updowngray == 1)
       show_display_item_content(index_y,SANTIFONTCOLOR,SANTIBGCOLOR);
   	 else
   	   show_display_item_content(index_y,SFONTCOLOR,SBGCOLOR);
   }
   #endif
}



UINT16 run_save_unChk_cmd(UINT8 save)
{
    int     test,i,j;
    UINT16  unChksum;

    unChksum=0;

    for(i=0;i<(MAX_SETUP_PAGE+MAX_CUSTM_SETUP_PAGE);i++) {

    #if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)
            if(i == ONEKEYPASSPAGE)
                continue;
        //not calculate the last item :RETURN_TO_MAIN_PAGE
        for(j=0;j<MAX_PAGE_ITEM-1;j++)
    #else

#ifdef EASTECH_NEW_SETUP_MENU//nono 4-8-31 10:34
        if(i == CUSTMPAGEINDEX)
                continue;
#endif
 #ifdef  EASTECH_DP3240_SETUP_MENU//add xrh 2004_12_08
        if(i == CUSTMPAGEINDEX)
                continue;
#endif
        for(j=0;j<MAX_PAGE_ITEM;j++)
    #endif
        {
            #ifdef SELECT_MEDIA_IN_SETUPMENU //Maoyong 2004-8-10 17:28 check sum not consider media switch
            if( setup_item[i][j][1]==STR_OS_MEDIA_TYPE )
                continue;
            #endif

           #ifdef  EASTECH_DNOT_SAVE_SLEEP_SETUP  //LYC 2005/03/28
           if( setup_item[i][j][1]==STR_OS_SLEEP_SETUP)
                continue;
           #endif
           
            //rating and password
            if((setup_item[i][j][1]==STR_OS_RATING)||(setup_item[i][j][1]==STR_OS_PASSWORD) )//||(setup_item[i][j][1]==STR_OS_REGION_CODE))
                continue; //grade item need not load default value

            #ifdef SUPER_DEFAULT_OSD_LANG
            if(i==CUSTMPAGEINDEX)
            {
                if(setup_item[i][j][1]==STR_OS_OSD)
                    continue;
            }
            #endif

            unChksum+=(UINT16)(setup_sel[i][j]);
        }
    }

        if(save==1)
        {
       test=WriteToI2c(0xa0, sizeof(UINT32)+sizeof(setup_sel), (BYTE *)&unChksum, 2);

    #ifdef MONE_SETUP
    if(test==1)
        printf("SAVE unChksum=%d,sizeof(setup_sel)=%d OK\n",unChksum,sizeof(setup_sel));
    else
        printf("SAVE unChksum=%d,sizeof(setup_sel)=%d ERROR\n",unChksum,sizeof(setup_sel));
    #endif
       }
       return unChksum;
}



void run_save_sel_cmd(BYTE page,BYTE index)
{
    BYTE    *p;

    #ifdef MONE_SETUP
    printf("!!!RUN SEL CMD=%d,%d %d %d\n",page,index,(page*MAX_PAGE_ITEM+index),setup_sel[page][index]);
    #endif
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)
    if(page == ONEKEYPASSPAGE)
        return;
#endif

#ifdef  EASTECH_DNOT_SAVE_SLEEP_SETUP//?????????
if((page == 0) && (index == 2))
    return;
#endif

#ifdef  EASTECH_DNOT_SAVE_VIDEO_SETUP
//if((page == 3) && (index == 4))
 if(STR_OS_P_SCAN_YUV==setup_item[page][index_y][index_y2])
    return;
#endif


    //run_save_romChk_cmd();//terry,2003/12/15 05:11PM

    p=(BYTE *)&setup_sel[page][index];

    WriteToI2c(0xa0, sizeof(UINT32)+(page*MAX_PAGE_ITEM+index), p, 1);
    run_save_unChk_cmd(1);
}



void run_save_total_sel(void)
{
    BYTE    *p;
    int test;

    #ifdef MONE_SETUP
    printf("!!!!RUN TOTAL SEL CMD\n");
    #endif

    //run_save_romChk_cmd();
    p=(BYTE *)setup_sel;
    test=WriteToI2c(0xa0, sizeof(UINT32), p, sizeof(setup_sel));
    run_save_unChk_cmd(1);
}


void run_save_userSet_cmd(UINT8 *update)
{
    int test;

    #ifdef MONE_SETUP
    printf("!!!run_save_userSet_cmd\n");
    #endif

    test=WriteToI2c(0xa0, sizeof(UINT32)+sizeof(setup_sel)+2, update, sizeof(update));
}

#ifdef SETUP_DONT_PAUSE//terry,2004/2/23 03:58PM
UINT8 user_set_write_cnt=sizeof(t_USER_SET);
void polling_10ms_save(void)
{
   int test;

   if(user_set_write_cnt<sizeof(t_USER_SET))
   {
      test=WriteToI2c(0xa0, sizeof(UINT32)+sizeof(setup_sel)+2+user_set_write_cnt, (BYTE *)&UserSet+user_set_write_cnt,1);
      user_set_write_cnt++;
      //printf("-%d",user_set_write_cnt);
   }
}
#endif


void run_save_total_userSet(void)
{
    int test;

    #ifdef NEW_SEARCH_OSD
        // YW:020725
        sound_type = SETUP_SPK_DOWNMIX;
        sound_type = ITEM_SPK_DOWNMIX[sound_type];
    #endif

    #ifdef MONE_SETUP
        printf("!!!run_save_total_userSet\n");
    #endif

#ifdef SETUP_DONT_PAUSE//4-2-14 13:45
    user_set_write_cnt=0;
    printf("sizeof(t_USER_SET):%d\n",sizeof(t_USER_SET));
    //polling_10ms_save();
#else
    test=WriteToI2c(0xa0, sizeof(UINT32)+sizeof(setup_sel)+2, (BYTE *)&UserSet, sizeof(t_USER_SET));
#endif

    #ifdef MONE_SETUP
    {
        int i, j;

        for (i=0; i<4; i++) {
            for (j=0; j<7; j++) {
                printf("setup_sel[%d][%d]=%d\n", i, j, setup_sel[i][j]);
            }
        }
    }
    #endif

}


void setup_save_exit(void)
{
    if (cd_type_loaded==CDDVD)
        nav_param_by_user();

    if (full_scrn&CUSTM) {
        SETUP_GRADE = SETUP_CUSTM_GRADE;
    }

    run_save_total_userSet();
}


int setup_IsLock()//nono 20020707
{
    if ( UserSet.parental_ststus==C_LOCK)
        return 1;
    else
        return 0;
}



void show_lock(int s,int mode)
{
    //s     :  0:lock 1:unlock
    //mode :  0:normal 1:ANTI
    int font,bg;
    const char *str;

    UserSet.parental_ststus=s;
    setup_sel[page][index_y] = (MIN_ITEM_SEL+s);
    if(mode)
    {
        font=SANTIFONTCOLOR;
        bg=SANTIBGCOLOR;
    }
    else
    {
        #ifdef JIEKE_DVD
        font = SBLACKCOLOR;
        #else
        font = SFONTCOLOR;
        #endif
        bg = SBGCOLOR;
    }
    str = _OsdMessegeFont1[osd_font_mode][STR_OS_LOCK+s];
#ifdef TONIC_DVD
    if(ShowPasswordErr==0)
    osd_DrawString(SETUP_SUB_XSTART+1, submenuStart+1, (char *)str , font, bg);
    else
    osd_DrawString(SETUP_SUB_XSTART+1, submenuStart+1, "ERROR" , font, bg);
#else//#ifdef TONIC_DVD
    osd_DrawString(SETUP_SUB_XSTART+1, submenuStart+1, (char *)str , font, bg);
#endif//#ifdef TONIC_DVD
}

const char * setup_SetItemString()
{
    const char *str;
    if(page==LANGPAGE
    #ifdef DVB_SETUP_MENU
    ||IsDvbSetupLanguage()
    #endif
    )
    {
        if (id==STR_OS_OFF)
            str = _OsdMessegeFont1[osd_font_mode][id];
        else
            str = lang_names[osd_font_mode][id];
    }
#ifdef DVB_SETUP_MENU
    else if(IsDvbSubItem())
    {
        str = osd_str_dvb_submenu[osd_font_mode][id - STR_DVB_BASE_INDEX];
    }
#endif
#ifdef SUPER_DEFAULT_OSD_LANG
    else if((page==CUSTMPAGEINDEX)&&(index_y==CUSTMOSDITEM))
        str = lang_names[osd_font_mode][id];
#endif
    else
        str = _OsdMessegeFont1[osd_font_mode][id];

    return str;
}



void setup_password(void)
{
    if (
#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-16 10:27
    ((passwdGUI_state != NO_GUI_STATE)&&(passwdGUI_state != SHOW_OK_STATE ) && (full_scrn & SETUP))//SETUP state
    || ((setup_item[page][index_y][0]==SET_NM) && (full_scrn & CUSTM))//CUSTM state
#else //NOT  SETUP_PASSWORD_GUI
    (setup_item[page][index_y][0]==SET_NM)
#endif//SETUP_PASSWORD_GUI
    #ifdef NEW_PARENTAL_GUI//zhaoyanhua add 2003-11-28 13:34
    || (new_parental_gui)//show PARENTAL GUI
    #endif
    )
    {
        if(ir_select_number>10) return;

        id=setup_item[page][index_y][1];

        if(digit_cnt>=PASSWORD_LENGTH)
            digit_cnt=0;

        digit_cnt++;
        show_password(ir_select_number);

  #ifdef DIRECT_PASSWORD_IN  //2004-2-25 11:05张宇P
        if((digit_cnt==PASSWORD_LENGTH)&&(new_parental_gui==1))
    {
#if defined(DVD_AUDIO)//20040302
if(pDSV->hid_gp_chk_pwd==2)
        check_dvd_audio_password();//nono 2004/3/2 05:40PM
else
#endif//#if defined(NEW_PARENTAL_GUI)&&defined(DVD_AUDIO)

        setup_func_select();
           user_input_pwd=0;

   }
else
return;
    #endif    //end DIRECT_PASSWORD_IN
    }
}




//
// show_password
//
void show_password(BYTE num)  /*jhuang 2001/5/15 10:39AM*/
{
    UINT8   i;
    BYTE    yStart;
    BYTE    buf[40];

    #define CH_STAR 0x58//X  //jhuang pending
    #define CH_DASH 0x2d//-
    #define CH_SPACE 0x20
    #define CH_LOCK   0xff
    #if defined(USE_SCHINESE_OSD)||defined(USE_JAPANESE_OSD)||defined(USE_TCHINESE_OSD)||defined(USE_THAI_OSD)||defined(USE_KOREAN_OSD)||defined(USE_HEBRAIC_OSD)||defined(USE_ARABIC_OSD)//jiangxl 2005-8-25 14:49
    #define CH_UNLOCK 0x67
    #else 
    #define CH_UNLOCK 0x7f
    #endif
    

    if(num == CLREAR_PASSWD) {
        reset_passwd_cnt();
    }

#ifdef SETUP_6_DIGIT_PASSWORD
    tmp_passwd=(tmp_passwd*10+num)%1000000;
#else
    tmp_passwd=(tmp_passwd*10+num)%10000;
#endif

    if(full_scrn&CUSTM) {
        #ifdef SETUP_6_DIGIT_PASSWORD
        psprintf(linebuf,"%06d", tmp_passwd);
        #else
        psprintf(linebuf,"%04d", tmp_passwd);
        #endif
        UserSet.parent_passwd = tmp_passwd;
    } else {
        if ((setupLevel!=2)
        #ifdef NEW_PARENTAL_GUI//zhaoyanhua add 2003-11-28 13:38
       &&(!new_parental_gui)
        #endif
        )
        {
            reset_passwd_cnt();
            return;
        }

        // fill char
        for(i=1;i<=digit_cnt;i++)
            linebuf[i-1] = CH_STAR;
        for(i=digit_cnt+1;i<=PASSWORD_LENGTH;i++)
            linebuf[i-1] = CH_DASH;

        linebuf[PASSWORD_LENGTH] = CH_SPACE;

#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-15 13:54
        if(passwdGUI_state == NO_GUI_STATE)//NOTE: they are all defined in setup_tab_ui.c
        {
#endif//SETUP_PASSWORD_GUI
#if defined(NEW_PARENTAL_GUI)&&defined(DVD_AUDIO)//20040302
            if(pDSV->hid_gp_chk_pwd==2)//20040305
            {
                linebuf[PASSWORD_LENGTH+1] = CH_UNLOCK;
            }
            else
#endif//#if defined(NEW_PARENTAL_GUI)&&defined(DVD_AUDIO)//20040302
            {
                if(UserSet.parental_ststus==C_LOCK)
                    linebuf[PASSWORD_LENGTH+1] = CH_LOCK;
                else
                    linebuf[PASSWORD_LENGTH+1] = CH_UNLOCK;
            }
            linebuf[PASSWORD_LENGTH+2] = 0;
			#ifdef SOFT_MENU//Modifed by ChenZhao on 2004-9-14 11:39 WP
			linebuf[PASSWORD_LENGTH] = 0;
			#endif //SOFT_MENU
#ifdef  SETUP_PASSWORD_GUI  //zhaoyanhua add 2004-1-15 13:58
        }
        else
        {
            linebuf[PASSWORD_LENGTH+1]= 0;
        }
#endif//SETUP_PASSWORD_GUI
    }

    id=STR_OS_SPACE;
    psprintf(buf,"%s",linebuf);

    if (full_scrn&CUSTM) {
        yStart = (CUSTMPASSWDITEM+2);   //correct CUSTM page PASSWD item display position, Jeff 20020510
    } else {
        yStart = (PASSWDITEM+2);
    }
#ifdef NEW_PARENTAL_GUI//zhaoyanhua add 2003-11-28 13:39
    if(new_parental_gui)
    {
        osd_DrawRegionString(PASSWORD_XSTART, PASSWORD_YSTART, buf, PASSWORD_FONT_HL_COLOR,PASSWORD_BK_HL_COLOR,0);
    }
    else
#endif
#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-15 12:01
    {
#define OLD_PASSWD_WORD_X  18
#define OLD_PASSWD_WORD_Y  4
#define NEW_PASSWD_WORD_X  OLD_PASSWD_WORD_X
#define NEW_PASSWD_WORD_Y  OLD_PASSWD_WORD_Y +2

        int passwd_x= 0, passwd_y = 0;

        if (full_scrn&CUSTM)//CUSTM state password
        {
            passwd_x = SETUP_SUB_XSTART+1;
            passwd_y = CUSTMPASSWDITEM+3;
        }
        else//normal SETUP state password
        {
        switch(passwdGUI_state)
        {
            case INPUT_OLD_PASSWD_STATE:
                passwd_x = OLD_PASSWD_WORD_X;
                passwd_y = OLD_PASSWD_WORD_Y;
                break;
            case INPUT_NEW_PASSWD_STATE:
                passwd_x = NEW_PASSWD_WORD_X;
                passwd_y = NEW_PASSWD_WORD_Y;
                break;
            case INPUT_GRADE_PASSWD_STATE: //for grade password
                passwd_x = OLD_PASSWD_WORD_X;
                passwd_y = OLD_PASSWD_WORD_Y;
                break;
            default:
                break;
        }
        }
        osd_DrawString(passwd_x, passwd_y, buf, SANTIFONTCOLOR, SANTIBGCOLOR);
    }
#elif defined(SOFT_MENU)//Modifed by ChenZhao on 2004-9-14 11:39 WP
	if(full_scrn&CUSTM)
		ShowSetupPasswordCustm(buf);
	else
		ShowSetupPassword(buf);
#else
    osd_DrawString(SETUP_SUB_XSTART+1, yStart+1, buf, SANTIFONTCOLOR, SANTIBGCOLOR);
#endif//SETUP_PASSWORD_GUI
}




void reset_passwd_cnt(void)  /*jhuang 2001/5/17 05:13PM*/
{
    tmp_passwd = 0;
    digit_cnt = 0;
}


void read_custm_setup_select(void)
{
    reset_passwd_cnt(); /*jhuang pending 2001/5/15 08:16PM*/

    UserSet.parental_ststus=C_UNLOCK;
    SETUP_CUSTM_GRADE=SETUP_GRADE;
    page=CUSTMPAGEINDEX;
}


void setup_ShowVolCtrlConfig()
{
    const char *str;
    BYTE    fontColor;
    BYTE    i;

    if ( (page!=AUDPAGE) ||
        (index_y!=DIGIOUTITEM)
        )
    {
        return;
    }

    if (SETUP_SPDIF!=SPDIFBITSTREAM) {
        fontColor = SFONTCOLOR;

    } else {
        if ( (coding_mode_now&(AUDIF_CODING_MODE_DTS|
            AUDIF_CODING_MODE_DTSCD|
            //AUDIF_CODING_MODE_PCM|   //DTSCD-BITSTREAM MODE, Jeff 20020719
            AUDIF_CODING_MODE_AC3)
            )||(cd_subtype==CD_DTS) )//nono 2-7-25 17:29
        {
            fontColor = SFONTCOLOR;
            //fontColor = SGRAYCOLOR;
        } else {
            fontColor = SFONTCOLOR;
        }

    }

    for (i=VOLCTRLSTART; i<=VOLCTRLEND; i++) {
        if (coding_mode_now==AUDIF_CODING_MODE_LPCM) { //Jeff 20020703
            if (i==KEYITEM) {
                fontColor = SFONTCOLOR;
                //fontColor = SGRAYCOLOR;
            } else {
                fontColor = SFONTCOLOR;
            }
        } else
            if ( (SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF) &&
                (i==KEYITEM)
                )
            {
                if( ( coding_mode_now&(AUDIF_CODING_MODE_DTS| AUDIF_CODING_MODE_DTSCD|AUDIF_CODING_MODE_AC3|AUDIF_CODING_MODE_LPCM) )||(cd_subtype==CD_DTS) )//nono 2-8-5 15:05
                {
                    fontColor = SFONTCOLOR;
                    //fontColor = SGRAYCOLOR;
                } else {
                    fontColor = SFONTCOLOR;
                }

            }

        #ifdef KARAOKE_MENU //wangfeng 2003-10-30 10:19
            if((page==AUDPAGE)&&(KARAOKE_MENU_FLAG)&&((i<2)||(i>5)))
            {
                fontColor = SBGCOLOR;

            }
            //wangfeng 2003-11-11 14:06
            else if((page==AUDPAGE)&&(KARAOKE_MENU_FLAG==0)&&((i>=2)&&(i<=5)))
            {
                fontColor = SBGCOLOR;

            }
            #ifdef PROLOGIC_ON_51CH//wangfeng 2003-12-22 16:40
            else if ((page==AUDPAGE)&&(KARAOKE_MENU_FLAG==0)
                    && !setup_IsSpkDownmixOff()&&(i==1))
                {
                    fontColor = SGRAYCOLOR;
                }
            #endif
            else
        #endif
            id = setup_item[page][i][1];
#ifdef TONIC_DVD
            if(id==STR_OS_RETURN_MAIN_SETUP)
            id=STR_OS_EXIT_MENU;
#endif//#ifdef TONIC_DVD
            str = _OsdMessegeFont1[osd_font_mode][id];
            osd_DrawString(SETUP_MENU_XSTART+1, i+SETUP_MENU_YSTART+1, str, fontColor, SBGCOLOR);
    }
}


//To do speaker(AC3) config
void setup_ShowAC3Config()
{
    BYTE    buf[40];
    BYTE    fontColor;
    BYTE    i;

    if ( (page!=MULTISPKPAGE) ||
        (setupLevel!=2) ||
        (index_y!=AC3DOWNMIXITEM)
        )
    {
        return;
    }

#if defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE)//2003-8-13 23:32

    if (SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF) { //set to 5.1 channel
        fontColor = SFONTCOLOR;

    } else
    {
        fontColor = SGRAYCOLOR;
    }

#elif !defined(SETUP_ALL_VALID)
    if ( (SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF) && (SETUP_SPDIF==SPDIFSIMULATE) ) { //set to 5.1 channel
        fontColor = SFONTCOLOR;

    } else
    {
        fontColor = SGRAYCOLOR;
    }
#elif defined(SET_FCR_SPEAKER)//xyy changed 2004-10-23 10:48
    if (SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF) {        //xulf 2004-01-06
        fontColor = SFONTCOLOR;
    } else
    {
        fontColor = SGRAYCOLOR;
    }
#else
        fontColor = SFONTCOLOR;
#endif

    for (i=SPKSTART; i<=SPKEND; i++) {
        id = setup_item[page][i][1];
        psprintf(buf, "%s", _OsdMessegeFont1[osd_font_mode][id]);
        osd_DrawString(SETUP_MENU_XSTART+1, i+SETUP_MENU_YSTART+1, buf, fontColor, SBGCOLOR);

    }
}


int setup_IsSet2SPDIF_PCM()
{
#ifdef DIVIDE_AC3_DTS_SPDIF_OUTPUTS
    if (SETUP_SPDIF_PCM==SPDIFBITSTREAM)
#else
    if (SETUP_SPDIF==SPDIFPCM)
#endif
        return 1;

    return 0;
}

void setup_SetAC3PCMConfig()//nono 2004-8-3 22:41
{
#if !defined(SPHE8202)
    if( (cd_type_loaded==CDDVD)&&(coding_mode_now == AUDIF_CODING_MODE_AC3)&&(setup_IsSet2SPDIF_PCM()==1) )//nono  4-5-26 21:49
    {
        AUDIF_Set_OutputMode(OUT_51DownmixLtRt, 0);//2004AUDDRV AudioSetOutputMode(8, 0); //Set Output mode(7:2 channel)
    }
#endif

}


void setup_SetAC3Config()
{
    BYTE newid, newsel;

    //set speaker setting
    /*newsel = SETUP_SPK_DOWNMIX;
    newid = ITEM_SPK_DOWNMIX[newsel];

    #ifdef NEW_SEARCH_OSD
    // YW:020725
    sound_type = newid;
    #endif

    //to run speaker setup downmix mode
    // run twice to prevent from losing the very 1st cmd, we have to check risc-dsp to see
    // why the 1st cmd lost by curr handshake, status report okay, ??????, 2003-05-13
    exe_setup_function( ITEM_SPK_DOWNMIX[1], newid, 0);
    exe_setup_function( ITEM_SPK_DOWNMIX[1], newid, 0);*/

    printf("ac3 setup function ..STR_OS_DOLBY_OP_SETUP:%x STR_OS_DUAL_MONO_SETUP:%x\n",STR_OS_DOLBY_OP_SETUP,STR_OS_DUAL_MONO_SETUP);
    //set AC3 digital setting
    newsel = SETUP_AC3DIGITAL_OUTMODE;
    newid = ITEM_AC3DIGITAL_OUTMODE[newsel];

    printf("ITEM_AC3DIGITAL_OUTMODE[1]:%x out: newsel:%x newid:%x\n",ITEM_AC3DIGITAL_OUTMODE[1],newsel,newid);
    //exe_setup_function( ITEM_AC3DIGITAL_OUTMODE[1], newid, 0);
     exe_setup_function( STR_OS_DOLBY_OP_SETUP, newid, 0);
    if (newsel == AC3DYNAMICITEM2) {
        set_AC3DynamicRange();
    }

    newsel = SETUP_AC3DIGITAL_LnR;
    newid = ITEM_AC3DIGITAL_LnR[newsel];
    printf("ITEM_AC3DIGITAL_OUTMODE[1]:%x out: newsel:%x newid:%x\n",ITEM_AC3DIGITAL_LnR[1],newsel,newid);
    //exe_setup_function( ITEM_AC3DIGITAL_OUTMODE[1], newid, 0);
    exe_setup_function( STR_OS_DUAL_MONO_SETUP, newid, 0); //axelchen 20040105 Panasonic 瑈ē

    //terry,2004/6/30 04:57PM
    //set center speaker delay, 1:center speaker
    AUDIF_Set_SpkDelay(1, SETUP_SPK_CENTER_DELAY-2);//2004AUDDRV AudioSetSpkDelay(1, SETUP_SPK_CENTER_DELAY-2);
    //set surround speaker delay, 2:surround speaker
    AUDIF_Set_SpkDelay(2, (SETUP_SPK_SURROUND_DELAY-2)*3);//2004AUDDRV AudioSetSpkDelay(2, (SETUP_SPK_SURROUND_DELAY-2)*3);
    
    if (SETUP_SPDIF==SPDIFPCM)  //jiangxl 2005-11-7 10:09
    {
    AUDIF_Set_OutputMode(OUT_51DownmixL0R0, 0);
    }

}
#ifdef QSI_SETUP_MENU//liweihua add 2004-6-15
UINT16 safe_wait_time = 1* 60 * 100;
BYTE select_save_time(BYTE res)
{
    BYTE i;
    UINT16 save_time[]={1* 60 * 100, 5* 60 * 100, 10* 60 * 100, 30* 60 * 100};
    if(res <= 5)
    {
        safe_wait_time = save_time[res-2];
        res = 1;
    }
    else
        res=0;
    return res;
}
#endif

BYTE setup_GetSSaveType()
{
    // In stup menu, we use screen saver item as the auto play item
    // when AUTO_PLAY, always return 1 ==> screen saver always turn on
#ifdef AUTO_PLAY
    #ifdef JIEKE_DVD//no saver, wangfeng 2003-10-28 11:19
    return 0;
    #else
    return 1;
    #endif
#else
    BYTE res;

    res = SETUP_SSAVER;
    if (res < 2) res=2;
    #ifdef QSI_SETUP_MENU//liweihua add for SQI 2004-6-15
    res = select_save_time(res);
    #else
    if (res==2) {
        res = 1;
    } else {
        res = 0;
    }
    #endif
    return res;
#endif
}


//up1down : 0 -> up, 1-> down
#define X_60   SETUP_SUB_XSTART*16+60
#define X_76   SETUP_SUB_XSTART*16+76
#define X_94   SETUP_SUB_XSTART*16+94
#define X_96   SETUP_SUB_XSTART*16+96
#define Y_0    SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT
#define Y_8    SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+8


void setup_DrawScaleItem(BYTE id, BYTE up1down, int val)
{
    BYTE uColor, dColor;
    BYTE fontColor, bgColor;
    BYTE clrCursorColor;// to clear cursor. zhaoyanhua add 2003-12-16 10:56
    UINT32  yStart=0, yDelta=0;
    UINT32  yNew, yNew_8;

    if (up1down) {
        uColor = SBLACKCOLOR;
        dColor = SWHITECOLOR;
        #ifdef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 17:45
        fontColor = SFONTCOLOR;
        bgColor = SANTIFONTCOLOR;
        #else
        fontColor = SANTIFONTCOLOR;
        bgColor = SANTIBGCOLOR;
        #endif

    #ifdef HL_CURSOR_ONLY//zhaoyanhua add 2003-12-16 10:58
        clrCursorColor = SBGCOLOR;
    #else
        clrCursorColor = SANTIBGCOLOR;
    #endif


    } else {
        uColor = SWHITECOLOR;
        dColor = SBLACKCOLOR;
        fontColor = SFONTCOLOR;
        #ifdef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 17:45
        bgColor = SDEFAULTCOLOR;
        #else
        bgColor = SBGCOLOR;
        #endif
        clrCursorColor = SBGCOLOR;
    }

        if (id==STR_OS_ECHO) {//echo_level(0 ~ 8)
            //yStart = SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+26;
            //yDelta = 5 * SETUP_BUTTON_HEIGHT-30;
            yStart = SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+12;
            yDelta = 5 * SETUP_BUTTON_HEIGHT-16;
        } else

#ifdef  Ti3001_OSD_UI_2
        if ((id==STR_OS_AMP_MAINVOLUME)||(id==STR_OS_AMP_FSPK)||(id==STR_OS_AMP_FSPK_BALANCE)||
            (id==STR_OS_AMP_SSPK)||(id==STR_OS_AMP_SSPK_BALANCE)||(id==STR_OS_AMP_CSPK)||(id==STR_OS_AMP_SUBWOOFER))
        {//level(1 ~ 15)

            yStart = SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+12;
            yDelta = 8 * SETUP_BUTTON_HEIGHT-16;             //中间刻度线的长度。2-8-27 9:59  gerry
        } else
        if ((id==STR_OS_AMP_BASS)||(id==STR_OS_AMP_TREMBLE))
        {//level(1 ~ 15)

            yStart = SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+12;
            yDelta = 7 * SETUP_BUTTON_HEIGHT-16;
        } else
        if (id==STR_OS_AMP_DYNAMICRANGE)
        {//level(1 ~ 15)

            yStart = SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+12;
            yDelta = 7 * SETUP_BUTTON_HEIGHT-16;
        } else
#endif

        if (id==STR_OS_KEY) {//audio_key(-6 ~ 6)
            yStart = SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+12;
            yDelta = 7 * SETUP_BUTTON_HEIGHT-16;
            val+=6;
        } else
        if (id==STR_OS_MIC_VOL||id==STR_OS_MIC_VOL_1||id==STR_OS_MIC_VOL_2) {//mic_volume(0 ~ 8)
            yStart = SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+12;//wangfeng 2003-09-12 20:30
            yDelta = 5 * SETUP_BUTTON_HEIGHT-16;
        } else
        if ( (id==STR_OS_FSPK) || (id==STR_OS_CSPK) || (id==STR_OS_SSPK) ) { //0 ~ 8
            yStart = SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+12;
            yDelta = 5 * SETUP_BUTTON_HEIGHT-16;
            //val=0;
        } else
        if ( (id==STR_OS_CSPK_DELAY) || (id==STR_OS_SSPK_DELAY) ) { //0 ~ 5

        #ifdef  NO_SHOW_ADD_ICON//zhaoyanhua add 2003-12-9 17:18
            yStart = (SETUP_MENU_YSTART+2)*SETUP_BUTTON_HEIGHT+18;
            yDelta = 4 * SETUP_BUTTON_HEIGHT-30-2;
        #else
            yStart = (SETUP_MENU_YSTART+2)*SETUP_BUTTON_HEIGHT+24;
            yDelta = 4 * SETUP_BUTTON_HEIGHT-30;
        #endif


            //val=0;
        } else
        if (id==STR_OS_DYNAMICRANGE) {
            yStart = SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+12;
            yDelta = 5 * SETUP_BUTTON_HEIGHT-16;
        }
		#ifdef ADD_DVI311_SETUP     //kevin@040804      //cursor bar
	    	#ifdef DVI311_NO_PC_MODE
			    else if(id == STR_SPHE6500_FMT)
	            	    {
	        		    yStart = (SETUP_MENU_YSTART+2) * SETUP_BUTTON_HEIGHT + 12;
		      		    yDelta =4 * SETUP_BUTTON_HEIGHT - 16; //vertical stick long
			    }

	        #else
			    else if(id == STR_SPHE6500_FMT)
	            	    {
	        		    yStart = SETUP_MENU_YSTART * SETUP_BUTTON_HEIGHT + 12;
		      		    yDelta =8 * SETUP_BUTTON_HEIGHT - 16; //vertical stick long
			    }
	        #endif
		#endif
        else if (id == STR_OS_BRIGHTNESS ||
                 id == STR_OS_CONTRAST ||
                 id == STR_OS_HUE ||
                 id == STR_OS_SATURATION)
        {
            yStart = SETUP_MENU_YSTART * SETUP_BUTTON_HEIGHT + 12;
            yDelta = 7 * SETUP_BUTTON_HEIGHT - 16;
        }
#ifdef DIP_CFG_ENABLE
        else if (id == STR_OS_DEINTLC)
        {
            yStart = (SETUP_MENU_YSTART+1) * SETUP_BUTTON_HEIGHT + 12;
            yDelta = 4 * SETUP_BUTTON_HEIGHT - 16;
        }
#endif//#ifdef DIP_CFG_ENABLE
         osd_draw_rect(X_60, yStart+32, 36, yDelta, bgColor);  //yufeng re-open 05/11/24// alan, 2003/08/06

        //osd_DrawLine(X_76, yStart+28, X_76, yStart+yDelta+32, fontColor, 3);  // alan, 2003/08/06
		#ifdef ADD_DVI311_SETUP
		if(id==STR_SPHE6500_FMT)
			yNew = yStart+yDelta-16 - (val*SETUP_BUTTON_HEIGHT);
		else
		#endif

        yNew = yStart+yDelta-16 - (val*SETUP_BUTTON_HEIGHT/2);
        #ifdef NO_SHOW_ADD_ICON//zhaoyanhua add 2003-12-9 17:41
        if ( (id==STR_OS_CSPK_DELAY) || (id==STR_OS_SSPK_DELAY) )
        yNew+=32+8;
        else
        #endif
        yNew+=32;
        yNew_8=yNew+8;

        // alan,3-8-6 14:34
        {
            UINT32 yyStart,yyLen;

            if ( (yNew-20)<(yStart+32) )
                yyStart=yStart+32;
            else
                yyStart=yNew-20;

            if ( (yNew-20+8+40)>(yStart+32+yDelta) )
            {
                UINT32 diff=(yNew-20+8+40)-(yStart+32+yDelta);
                yyLen=8+40-diff;
            } else
                yyLen=8+40;

            //osd_draw_rect(X_60-4, yNew-20, 32+8, 8+40, bgColor);
            //osd_draw_rect(X_60-4, yyStart, 32+8, yyLen, bgColor);
            #ifdef  NO_SHOW_ADD_ICON//zhaoyanhua add 2003-12-9 17:41
            if ( (id==STR_OS_CSPK_DELAY) || (id==STR_OS_SSPK_DELAY) )
                osd_draw_rect(X_60-4, yyStart-2-8, 32+8, yyLen+10+4,clrCursorColor);
            else
            #endif
			#ifdef ADD_DVI311_SETUP
			if(id == STR_SPHE6500_FMT) //clear Cursor Color
			{
				osd_draw_rect(X_60+30-4,  yStart+28, 32+8, yDelta+4, clrCursorColor);
				/*
				#ifdef SOFT_MENU//Modifed by ChenZhao on 2004-9-16 14:10 WP
				osd_draw_rect(X_60+30-4,  yStart+28, 32+8, yDelta+4, clrCursorColor);
				#else//SOFT_MENU
				osd_draw_rect(X_60+30-4, 108-2, 32+8, 48, clrCursorColor);
				osd_draw_rect(X_60+30-4, 120-2, 32+8, 48, clrCursorColor);
				osd_draw_rect(X_60+30-4, 152-2, 32+8, 48, clrCursorColor);
				osd_draw_rect(X_60+30-4, 184-2, 32+8, 48, clrCursorColor);
				osd_draw_rect(X_60+30-4, 216-2, 32+8, 48, clrCursorColor);
				osd_draw_rect(X_60+30-4, 248-2, 32+8, 48, clrCursorColor);
				osd_draw_rect(X_60+30-4, 280-2, 32+8, 48, clrCursorColor);///kevin @040804    ->( ,36,clrCursorColor);)
				osd_draw_rect(X_60+30-4, 312-2, 32+8, 36, clrCursorColor);////kevin @040804
				#endif//SOFT_MENU
				*/
			}
			else
				#endif
                    osd_draw_rect(X_60-4, yyStart-2, 32+8, yyLen, clrCursorColor);

        }
        #ifdef NO_SHOW_ADD_ICON//zhaoyanhua add 2003-12-9 17:41
        if ( (id==STR_OS_CSPK_DELAY) || (id==STR_OS_SSPK_DELAY) )
            osd_DrawLine(X_76, yStart+28-4, X_76, yStart+yDelta+32+8, fontColor, 3);
        else
        #endif
		#ifdef ADD_DVI311_SETUP
		if(id == STR_SPHE6500_FMT)
		{
			#define X_60_1   SETUP_SUB_XSTART*16+60+30
			#define X_76_1   SETUP_SUB_XSTART*16+76+30
			#define X_94_1   SETUP_SUB_XSTART*16+94+30
			#define X_96_1   SETUP_SUB_XSTART*16+96+30
			osd_DrawLine(X_76_1, yStart+28, X_76_1, yStart+yDelta+32, fontColor, 3);
			osd_draw_rect(X_60_1, yNew, 32, 8, bgColor);
			//top
			if (p_scan==1)
				osd_DrawLine(X_60_1, yNew, X_96_1, yNew, uColor, 2);
			else
				osd_DrawLine(X_60_1, yNew, X_96_1, yNew, uColor, 1);
			//left
			osd_DrawLine(X_60_1, yNew, X_60_1, yNew_8, uColor, 1);
			//botton
			if (p_scan==1)
				osd_DrawLine(X_60_1, yNew_8, X_96_1, yNew_8, dColor, 2);
			else
				osd_DrawLine(X_60_1, yNew_8, X_96_1, yNew_8, dColor, 1);
			//right
			osd_DrawLine(X_94_1, yNew, X_94_1, yNew_8, dColor, 1);
		}
		else
 		#endif//#ifdef ADD_DVI311_SETUP
		{
        osd_DrawLine(X_76, yStart+28, X_76, yStart+yDelta+32, fontColor, 3);

        osd_draw_rect(X_60, yNew, 32, 8, bgColor);
        //top
        if (p_scan==1)
            osd_DrawLine(X_60, yNew, X_96, yNew, uColor, 2);
        else
            osd_DrawLine(X_60, yNew, X_96, yNew, uColor, 1);
        //left
        osd_DrawLine(X_60, yNew, X_60, yNew_8, uColor, 1);
        //botton
        if (p_scan==1)
            osd_DrawLine(X_60, yNew_8, X_96, yNew_8, dColor, 2);
        else
            osd_DrawLine(X_60, yNew_8, X_96, yNew_8, dColor, 1);
        //right
        osd_DrawLine(X_94, yNew, X_94, yNew_8, dColor, 1);
    }
}



void revise_val(int dir, INT8 *x,int max,int min)
{
    if (dir)
    {
       if (*x < max)  (*x)++;
    } else
    {
       if (*x > min)  (*x)--;
    }
}



//If the item(id) is scaleable, here we will do it's corresponding action by dir(down=0, up=1)
void setup_CookScaleItem(UINT8 id, UINT8 dir)
{
    int val = SETUP_ECHO; // give a default value

        if (id==STR_OS_ECHO) {
            //echo_level(0 ~ 8)
            revise_val(dir,&echo_level,8,0);
            SETUP_ECHO = echo_level+2;
#ifdef USE_MIC_ECHO_PARAM
            AUDIF_Set_EchoPara(echo_level);//2004AUDDRV AudioSetEchoPara(echo_level);
#else

            AUDIF_Set_Echo(echo_level, echo_level);//2004AUDDRV AudioSetEcho(echo_level, echo_level);
#endif
            val=SETUP_ECHO;
        } else

#ifdef  Ti3001_OSD_UI_2
	if (id==STR_OS_AMP_MAINVOLUME)
	{
		//echo_level(0 ~ 8)
		revise_val(dir,&amp_volume_level,14,0);
		SETUP_AMP_VOLUME = amp_volume_level+2;
		//AudioSetEcho(echo_level, echo_decay);
		//printf("amp_volume_level=%d\n",amp_volume_level);
		//audio_volume=amp_volume_level;
		//AudioSetVolume(audio_volume);
		ti_set_volume(SET_TOTAL_VOLUME,amp_volume_level*7);
		val=SETUP_AMP_VOLUME;
	} else
	if (id==STR_OS_AMP_FSPK)
	{
		//echo_decay(0 ~ 8)
		revise_val(dir,&amp_fspk_level,14,0);
		SETUP_AMP_FSPK = amp_fspk_level+2;
		//AudioSetEcho(echo_level, echo_decay);
		//printf("amp_fspk_level=%d,amp_fspk_balance_level=%d\n",amp_fspk_level,amp_fspk_balance_level);
		set_tas3001ch_volume(FSPK,amp_fspk_balance_level,amp_fspk_level*7);
		val=SETUP_AMP_FSPK;
	} else
	if (id==STR_OS_AMP_FSPK_BALANCE)
	{
		//echo_decay(0 ~ 8)
		revise_val(dir,&amp_fspk_balance_level,14,0);
		SETUP_AMP_FSPK_BALANCE = amp_fspk_balance_level+2;
		//printf("amp_fspk_level=%d,amp_fspk_balance_level=%d\n",amp_fspk_level,amp_fspk_balance_level);
		set_tas3001ch_volume(FSPK,amp_fspk_balance_level,amp_fspk_level*7);
		//AudioSetEcho(echo_level, echo_decay);
		val=SETUP_AMP_FSPK_BALANCE;
	} else
	if (id==STR_OS_AMP_SSPK)
	{
		//echo_decay(0 ~ 8)
		revise_val(dir,&amp_sspk_level,14,0);
		SETUP_AMP_SSPK = amp_sspk_level+2;
		//AudioSetEcho(echo_level, echo_decay);
		//printf("amp_sspk_level=%d,amp_sspk_balance_level=%d\n",amp_sspk_level,amp_sspk_balance_level);
		set_tas3001ch_volume(SSPK,amp_sspk_balance_level,amp_sspk_level*7);

		val=SETUP_AMP_SSPK;
	} else
	if (id==STR_OS_AMP_SSPK_BALANCE)
	{
		//echo_decay(0 ~ 8)
		revise_val(dir,&amp_sspk_balance_level,14,0);
		SETUP_AMP_SSPK_BALANCE = amp_sspk_balance_level+2;
		//AudioSetEcho(echo_level, echo_decay);
		//printf("amp_sspk_level=%d,amp_sspk_balance_level=%d\n",amp_sspk_level,amp_sspk_balance_level);
		set_tas3001ch_volume(SSPK,amp_sspk_balance_level,amp_sspk_level*7);
		val=SETUP_AMP_SSPK_BALANCE;
	} else
	if (id==STR_OS_AMP_CSPK)
	{
		//echo_decay(0 ~ 8)
		revise_val(dir,&amp_cspk_level,14,0);
		SETUP_AMP_CSPK = amp_cspk_level+2;
		//AudioSetEcho(echo_level, echo_decay);
		//printf("amp_cspk_level=%d,amp_subwoofer_level=%d\n",amp_cspk_level,amp_subwoofer_level);
		set_tas3001ch_volume(CSSPK,amp_cspk_level/(amp_subwoofer_level+1),amp_cspk_level*7);
		val=SETUP_AMP_CSPK;
	} else
	if (id==STR_OS_AMP_SUBWOOFER)
	{
		//echo_decay(0 ~ 8)
		revise_val(dir,&amp_subwoofer_level,14,0);
		SETUP_AMP_SUBWOOFER = amp_subwoofer_level+2;
		//AudioSetEcho(echo_level, echo_decay);
		//printf("amp_cspk_level=%d,amp_subwoofer_level=%d\n",amp_cspk_level,amp_subwoofer_level);
		set_tas3001ch_volume(CSSPK,amp_cspk_level/(amp_subwoofer_level+1),amp_subwoofer_level*7);
		val=SETUP_AMP_SUBWOOFER;
	} else
	if (id==STR_OS_AMP_BASS)
	{
		//echo_decay(0 ~ 8)
		revise_val(dir,&amp_bass_level,12,0);
		SETUP_AMP_BASS = amp_bass_level+2;
		//AudioSetEcho(echo_level, echo_decay);
		//printf("amp_bass_level=%d\n",amp_bass_level);
		ti_set_volume(SET_BASS ,(amp_bass_level-6)*2);
		val=SETUP_AMP_BASS;
	} else
	if (id==STR_OS_AMP_TREMBLE)
	{
		//echo_decay(0 ~ 8)
		revise_val(dir,&amp_tremble_level,12,0);
		SETUP_AMP_TREMBLE = amp_tremble_level+2;
		//AudioSetEcho(echo_level, echo_decay);
		//printf("amp_tremble_level=%d\n",amp_tremble_level);
		ti_set_volume(SET_TREBLE ,(amp_tremble_level-6)*2);
		val=SETUP_AMP_TREMBLE;
	} else
	if (id==STR_OS_AMP_DYNAMICRANGE)
	{
		//echo_decay(0 ~ 8)
		revise_val(dir,&amp_dynamic_level,12,0);
		SETUP_AMP_DYNAMIC = amp_dynamic_level+2;
		//AudioSetEcho(echo_level, echo_decay);
		//printf("amp_dynamic_level=%d\n",amp_dynamic_level);
		ti_set_volume(SET_DRC ,6-amp_dynamic_level/2);

		val=SETUP_AMP_DYNAMIC;
	} else
#endif

	if (id==STR_OS_KEY) {
		//audio_key(-6 ~ 6)
		#ifdef SUPPORT_PROLOGIC_II
		if (SETUP_PROLOGIC_II!=4)
		{
			SETUP_PROLOGIC_II=4;    // alan, 2003/8/11 01:56PM
			exe_setup_function(STR_OS_PROLOGIC,STR_OS_OFF,0);
			run_save_sel_cmd(AUDPAGE, PROLOGIC_II);//nono 2004-2-16 9:28
		}
		#endif
		revise_val(dir,&audio_key,6,-6);
		val=audio_key+2;
		SETUP_KEY = val+6;
		AUDIF_Set_Key(SETUP_KEY);//2004AUDDRV AudioSetKey(SETUP_KEY); //audio_key:-6 ~ 6, map to 1~15
	} else
	if (id==STR_OS_MIC_VOL||id==STR_OS_MIC_VOL_1||id==STR_OS_MIC_VOL_2) {//wangfeng 2003-09-12 17:12
		//mic_volume(0 ~ 8)
		revise_val(dir,&mic_volume,8,0);
		//#ifdef	MIC_2CHANNEL	//wangfeng 2003-09-12 21:40
		//if(id==STR_OS_MIC_VOL||id==STR_OS_MIC_VOL_1)
		//mic_volume=SETUP_MIC_VOL;
		//else if(id==STR_OS_MIC_VOL_2)
		//mic_volume=SETUP_MIC_VOL_2;
		//#endif
		if(id==STR_OS_MIC_VOL||id==STR_OS_MIC_VOL_1)
		{
			SETUP_MIC_VOL = mic_volume+2;
            AUDIF_Set_MICVol(mic_volume);//2004AUDDRV AudioSetMICVol(mic_volume);
			//AudioSetMICVol(SETUP_MIC_VOL-2);
			val=SETUP_MIC_VOL;
		}
		#ifdef	MIC_2CHANNEL
		else if(id==STR_OS_MIC_VOL_2)
		{
			SETUP_MIC_VOL_2 = mic_volume+2;
            AUDIF_Set_MICVol2(mic_volume);//2004AUDDRV AudioSetMICVol_2(mic_volume);
			val=SETUP_MIC_VOL_2;
		}
		#endif

#ifdef FUSS_DVD //Jeff 20020524
		if ( setup_IsMICOff() ) {
			setup_SetMICAuto();
		}
#endif

		//AudioSetMICVol(mic_volume);
		//val=SETUP_MIC_VOL;
	} else
#ifndef AC3_BASS_MANAGEMENT
	if (id==STR_OS_FSPK) {
		revise_val(dir,&SETUP_SPK_FRONT,10,2);
		val=SETUP_SPK_FRONT;
#ifdef YUXING_DVD
		fspk_volume=SETUP_SPK_FRONT-4;
#endif
		//set front speaker gain
        AUDIF_Set_FSPKGain(SETUP_SPK_FRONT-2);//2004AUDDRV AudioSetFSPKGain(SETUP_SPK_FRONT-2);
	} else
	if (id==STR_OS_CSPK) {
		revise_val(dir,&SETUP_SPK_CENTER,10,2);
		val=SETUP_SPK_CENTER;
#ifdef YUXING_DVD
		cspk_volume=SETUP_SPK_CENTER-4;
#endif
		//set center speaker gain
        AUDIF_Set_CSPKGain(SETUP_SPK_CENTER-2);//2004AUDDRV AudioSetCSPKGain(SETUP_SPK_CENTER-2);
	} else
	if (id==STR_OS_SSPK) {
		revise_val(dir,&SETUP_SPK_SURROUND,10,2);
		val=SETUP_SPK_SURROUND;
#ifdef YUXING_DVD
		sspk_volume=SETUP_SPK_SURROUND-4;
#endif
		//set surround speaker gain
        AUDIF_Set_SSPKGain(SETUP_SPK_SURROUND-2);//2004AUDDRV AudioSetSSPKGain(SETUP_SPK_SURROUND-2);
	} else
#endif
	if (id==STR_OS_CSPK_DELAY) {
		#ifdef NO_SHOW_ADD_ICON//zhaoyanhua add 2003-12-9 17:18
		revise_val(dir,&SETUP_SPK_CENTER_DELAY,8,2);//0~6MS
		#else
		revise_val(dir,&SETUP_SPK_CENTER_DELAY,7,2);
		#endif
		val=SETUP_SPK_CENTER_DELAY;
		//set center speaker delay, 1:center speaker
        AUDIF_Set_SpkDelay(1, SETUP_SPK_CENTER_DELAY-2);//2004AUDDRV AudioSetSpkDelay(1, SETUP_SPK_CENTER_DELAY-2);
	} else
	#ifdef ADD_DVI311_SETUP
	if (id==STR_SPHE6500_FMT)
	{
	    #ifdef DVI311_NO_PC_MODE
                if(dvi311_tv_mode>0x84)     //NTSC or PAL60
        	revise_val(dir,&dvi311_mode,3,0);
                else if(dvi311_tv_mode==0x84)   //PAL
                    revise_val(dir, &dvi311_mode, 2, 0);
        #else
			revise_val(dir,&dvi311_mode,7,0);//7 为等级数
	    #endif
		//kevin add for limit the functions of display                           @2k40514
		if (((dvi311_tv_mode>0x84)//NTSC or PAL60
			&&(dvi311_mode==Mode_576P))//576P
			||((dvi311_tv_mode==0x84)//PAL
			&& (dvi311_mode==Mode_480P)))//480P
		{
			if(dir)
				dvi311_mode+=1;
			else
				dvi311_mode-=1;
		}
		val = dvi311_mode+2;
        SETUP_DVI_MODE=val;
              psprintf(linebuf, "dvi311_mode %x\n", dvi311_mode);
              epp_write_wait(linebuf);
		scaler_main(); //040512
	}else
#endif
	if (id==STR_OS_DYNAMICRANGE) { //Jeff 20020604
		revise_val(dir,&ac3_dynarange,8,0);
		SETUP_AC3DIGITAL_DYNA = ac3_dynarange+2;
		val = SETUP_AC3DIGITAL_DYNA;

		set_AC3DynamicRange();
	} else if (id==STR_OS_SSPK_DELAY)
	{
		#ifdef NO_SHOW_ADD_ICON//zhaoyanhua add 2003-12-9 17:18
		revise_val(dir,&SETUP_SPK_SURROUND_DELAY,8,2);//0~18MS
		#else
		revise_val(dir,&SETUP_SPK_SURROUND_DELAY,7,2);
		#endif
		val=SETUP_SPK_SURROUND_DELAY;
		//set surround speaker delay, 2:surround speaker
        AUDIF_Set_SpkDelay(2, (SETUP_SPK_SURROUND_DELAY-2)*3);//2004AUDDRV AudioSetSpkDelay(2, (SETUP_SPK_SURROUND_DELAY-2)*3);
	}
	else if (id == STR_OS_BRIGHTNESS)
	{
		revise_val(dir, &SETUP_BRIGHTNESS, 14, 2);
		val = SETUP_BRIGHTNESS;
		SetBrightness(val - 2);
		UpdateSetupmenuPalette();   // 2004/10/16 yltseng
	}
	else if (id == STR_OS_CONTRAST)
	{
		revise_val(dir,&SETUP_CONTRAST, 14, 2);
		val=SETUP_CONTRAST;
		SetContrast(val - 2);
		UpdateSetupmenuPalette();   // 2004/10/16 yltseng
	}
	else if (id == STR_OS_HUE)
	{
		revise_val(dir,&SETUP_HUE, 14, 2);
		val=SETUP_HUE;
		SetHUE(val - 2);
	}
	else if (id == STR_OS_SATURATION)
	{
		revise_val(dir,&SETUP_SATURATION, 14, 2);
		val=SETUP_SATURATION;
		SetSaturation(val - 2);
	}
	#ifdef DIP_CFG_ENABLE
	else if (id == STR_OS_DEINTLC)
	{
		revise_val(dir,&SETUP_DE_INTERLACE, 8, 2);
		val=SETUP_DE_INTERLACE;
		SetDeInterlace(val - 2);
	}
	#endif//#ifdef DIP_CFG_ENABLE
	#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 16:46
	if ((id == STR_OS_BRIGHTNESS) ||
		(id == STR_OS_CONTRAST) ||
		(id == STR_OS_HUE) ||
		(id == STR_OS_SATURATION)
        #ifdef DIP_CFG_ENABLE
		||(id == STR_OS_DEINTLC)
        #endif//#ifdef DIP_CFG_ENABL
        )
    {
    	setup_CookVideoGUIString(id);
    }
    else
	#endif//VIDEO_SETUP_NEW_GUI
		setup_DrawScaleItem(id, 1, val-2);
}





//
// setup_PrepareScaleItem   : draw scale item, including rectangle, and blank calibration
//
// input    :   id      -> scale item string id
//              up1down -> 0:up state
//                      -> 1:down state
//
void setup_PrepareScaleItem(BYTE id, BYTE up1down)
{
    BYTE    uColor, dColor; //up, down
    BYTE    fontColor, bgColor; //font, background color
    UINT32  xStart, yStart;
    UINT32  yDelta=0;
    BYTE    buf[15];
    BYTE    xWidth;
    int val = echo_level; // give a default value
    if (up1down) {
        uColor = SBLACKCOLOR;
        dColor = SWHITECOLOR;
        #ifdef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 17:45
        fontColor = SFONTCOLOR;
        #else
        fontColor = SANTIFONTCOLOR;
        #endif//#ifdef QSI_SETUP_MENU_DESIGN
    #ifdef HL_CURSOR_ONLY//only hilight cursor ,not whole SCALE.zhaoyanhua add 2003-12-16 10:17
        bgColor = SBGCOLOR;
    #else
        bgColor = SANTIBGCOLOR;
    #endif
    } else {
        uColor = SWHITECOLOR;
        dColor = SBLACKCOLOR;
        fontColor = SFONTCOLOR;
        bgColor = SBGCOLOR;
    }

    xStart = SETUP_SUB_XSTART*16;
    yStart = SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+32;
    xWidth = 14;

    if (id==STR_OS_ECHO) {
        static const t_osd_str osdstr_echo[] = {
                        { SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+1, " -    - 8"},
                        { SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2, " -    - 6"},
                        { SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+3, " -    - 4"},
                        { SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+4, " -    - 2"},
                        { SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+5, " -    - OFF"},
                        { 0, 0, NULL}
                    };

        //echo_level(0 ~ 8)
        yDelta = 5 * SETUP_BUTTON_HEIGHT;
        //draw area bgcolor
        osd_draw_rect(xStart, yStart, xWidth*16, yDelta, bgColor);
        //draw strings
        osd_DrawStrings(osdstr_echo, fontColor, bgColor);
        //
        val=echo_level;
    } else

#ifdef  Ti3001_OSD_UI_2
    if ((id==STR_OS_AMP_MAINVOLUME)||(id==STR_OS_AMP_FSPK)||(id==STR_OS_AMP_FSPK_BALANCE)||
                (id==STR_OS_AMP_SSPK)||(id==STR_OS_AMP_SSPK_BALANCE)||(id==STR_OS_AMP_CSPK)||(id==STR_OS_AMP_SUBWOOFER))
    {
        //level(1 ~ 15)
        yDelta =8 * SETUP_BUTTON_HEIGHT-1;    //   减1是为消去最下面的一条线。2-8-25 14:59 GERRY
        //draw area bgcolor
        osd_draw_rect(xStart, yStart, xWidth*16, yDelta, bgColor);
        //draw calibration
        //psprintf(buf, " -    +");

        static t_osd_str osdstr_vol[] = {
                    SETUP_SUB_X_START+1, SETUP_MENU_YSTART+0, " -    - +10DB",
                    SETUP_SUB_X_START+1, SETUP_MENU_YSTART+1, " -    -   0",
                    SETUP_SUB_X_START+1, SETUP_MENU_YSTART+2, " -    -  -10",
                    SETUP_SUB_X_START+1, SETUP_MENU_YSTART+3, " -    -  -20",
                    SETUP_SUB_X_START+1, SETUP_MENU_YSTART+4, " -    -  -30",
                    SETUP_SUB_X_START+1, SETUP_MENU_YSTART+5, " -    -  -40",
                    SETUP_SUB_X_START+1, SETUP_MENU_YSTART+6, " -    - -50DB",
                    SETUP_SUB_X_START+1, SETUP_MENU_YSTART+7, " -    -  OFF",
                                    0, 0, NULL
                                };
        osd_DrawStrings(osdstr_vol, fontColor, bgColor);

        if (id==STR_OS_AMP_MAINVOLUME)
        {
            val=amp_volume_level;
        }else
        if (id==STR_OS_AMP_FSPK)
        {
            val=amp_fspk_level;
        }else
        if (id==STR_OS_AMP_FSPK_BALANCE)
        {
            val=amp_fspk_balance_level;
        }else
        if (id==STR_OS_AMP_SSPK)
        {
            val=amp_sspk_level;
        }else
        if (id==STR_OS_AMP_SSPK_BALANCE)
        {
            val=amp_sspk_balance_level;
        }else
        if (id==STR_OS_AMP_CSPK)
        {
            val=amp_cspk_level;
        }else
        if (id==STR_OS_AMP_SUBWOOFER)
        {
            val=amp_subwoofer_level;
        }
    } else
    if ((id==STR_OS_AMP_BASS)||(id==STR_OS_AMP_TREMBLE))      //低音和高音。 2-8-25 15:10 GERRY
    {
        //level(1 ~ 15)
        yDelta =7 * SETUP_BUTTON_HEIGHT;
        //draw area bgcolor
        osd_draw_rect(xStart, yStart, xWidth*16, yDelta, bgColor);
        //draw calibration
        //psprintf(buf, " -    +");
        psprintf(buf, " -    - +18DB");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART, buf, fontColor, bgColor);
        psprintf(buf, " -    -   12");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+1, buf, fontColor, bgColor);
        psprintf(buf, " -    -   6");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2, buf, fontColor, bgColor);
        psprintf(buf, " -    -   0");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+3, buf, fontColor, bgColor);
        psprintf(buf, " -    -  -6");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+4, buf, fontColor, bgColor);
        psprintf(buf, " -    -  -12");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+5, buf, fontColor, bgColor);
        psprintf(buf, " -    - -18DB");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+6, buf, fontColor, bgColor);
        // psprintf(buf, " -    - -60");
        //osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+7, buf, fontColor, bgColor);
        //psprintf(buf, " -    - -18DB");
        //osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+7, buf, fontColor, bgColor);

        if (id==STR_OS_AMP_BASS)
        {
            val=amp_bass_level;
        }
        else
        {
            val=amp_tremble_level;
        }
    } else
    if (id==STR_OS_AMP_DYNAMICRANGE)     //动态范围    2-8-25 15:08  GERRY
    {
        //level(1 ~ 15)
        yDelta =7 * SETUP_BUTTON_HEIGHT;
        //draw area bgcolor
        osd_draw_rect(xStart, yStart, xWidth*16, yDelta, bgColor);
        //draw calibration
        //psprintf(buf, " -    +");
        psprintf(buf, " -    -  0DB");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART, buf, fontColor, bgColor);
        psprintf(buf, " -    -  -6");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+1, buf, fontColor, bgColor);
        psprintf(buf, " -    -  -12");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2, buf, fontColor, bgColor);
        psprintf(buf, " -    -  -18");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+3, buf, fontColor, bgColor);
        psprintf(buf, " -    -  -24");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+4, buf, fontColor, bgColor);
        psprintf(buf, " -    -  -32");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+5, buf, fontColor, bgColor);
        psprintf(buf, " -    - -36DB");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+6, buf, fontColor, bgColor);
        // psprintf(buf, " -    - -60");
        //osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+7, buf, fontColor, bgColor);
        //psprintf(buf, " -    - -36DB");
        //osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+7, buf, fontColor, bgColor);

        val=amp_dynamic_level;
    } else
#endif
    if (id==STR_OS_KEY) {
        static t_osd_str osdstr_key[] = {
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+1, " -    " Ch_ukey},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2, " -    - +4"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+3, " -    - +2"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+4, " -    -  0"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+5, " -    - -2"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+6, " -    - -4"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+7, " -    " Ch_dkey},
            {0, 0, NULL},
        };

        //audio_key(-6 ~ 6)
        yDelta = 7 * SETUP_BUTTON_HEIGHT;

        //draw area bgcolor
        osd_draw_rect(xStart, yStart, xWidth*16, yDelta, bgColor);

        //draw calibration
        osd_DrawStrings(osdstr_key, fontColor, bgColor);

        val=audio_key;
    }else
    if ( (id==STR_OS_FSPK) || (id==STR_OS_CSPK) || (id==STR_OS_SSPK)||(id==STR_OS_MIC_VOL)||(id==STR_OS_MIC_VOL_1)|| (id==STR_OS_MIC_VOL_2))
    {
        if(id!=STR_OS_MIC_VOL&&id!=STR_OS_MIC_VOL_1&&id!=STR_OS_MIC_VOL_2)
            yStart = SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+32;//wanghaoying 2003-12-1 21:57

        //spk_volume(0 ~ 8)
        yDelta = 5 * SETUP_BUTTON_HEIGHT;
        //draw area bgcolor
        osd_draw_rect(xStart, yStart, xWidth*16, yDelta, bgColor);
        //draw calibration
        psprintf(buf, " -    - 8");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+1, buf, fontColor, bgColor);
        buf[8]='6';//psprintf(buf, " -    - 6");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2, buf, fontColor, bgColor);
        buf[8]='4';//psprintf(buf, " -    - 4");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+3, buf, fontColor, bgColor);
        buf[8]='2';//psprintf(buf, " -    - 2");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+4, buf, fontColor, bgColor);
        psprintf(buf, " -    - OFF");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+5, buf, fontColor, bgColor);

#ifndef AC3_BASS_MANAGEMENT
        if (id==STR_OS_FSPK) {
            val=SETUP_SPK_FRONT-2;
        } else
        if (id==STR_OS_CSPK) {
            val=SETUP_SPK_CENTER-2;
        } else
        if (id==STR_OS_SSPK) {
            val=SETUP_SPK_SURROUND-2;
        }else
#endif
        {//wangfeng 2003-09-12 21:36
            #ifdef  MIC_2CHANNEL
            if(id==STR_OS_MIC_VOL||id==STR_OS_MIC_VOL_1)
                mic_volume=SETUP_MIC_VOL-2;
            else if(id==STR_OS_MIC_VOL_2)
                mic_volume=SETUP_MIC_VOL_2-2;
            #endif
            val=mic_volume;
        }

    } else
    if (id==STR_OS_CSPK_DELAY) {
        //center speaker delay 0 ~ 5 ms(step=1)
        yStart = (SETUP_MENU_YSTART+3)*SETUP_BUTTON_HEIGHT;

        yDelta = 4 * SETUP_BUTTON_HEIGHT;
        //draw area bgcolor
        osd_draw_rect(xStart, yStart, xWidth*16, yDelta, bgColor);
        //draw calibration
        #ifdef NO_SHOW_ADD_ICON   //fengjl add 3-11-28 23:32
            #ifdef  SHOW_SPK_DELAY_BY_DISTANCE  //Maoyong 2004.04.21
            psprintf(buf, " -    - 180CM");
            #else
            psprintf(buf, " -    - 6 MS");
            #endif
        #else   //#ifdef NO_SHOW_ADD_ICON
        psprintf(buf, " -    - +");
        #endif  //#ifdef NO_SHOW_ADD_ICON
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+3, buf, fontColor, bgColor);

        #ifdef AD_TCL//2004-3-22 13:04 lijd
        psprintf(buf, " -    - 4 %s",Ch_zu);
        #elif defined(SHOW_SPK_DELAY_BY_DISTANCE)   //Maoyong 2004.04.21
        psprintf(buf, " -    - 120CM");
        #else
        psprintf(buf, " -    - 4 MS");
        #endif
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+4, buf, fontColor, bgColor);

        #if defined(SHOW_SPK_DELAY_BY_DISTANCE) //Maoyong 2004.04.21
        psprintf(buf, " -    - 60 CM");
        #else
        buf[8]='2';//psprintf(buf, " -    - 2 MS");
        #endif
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+5, buf, fontColor, bgColor);

        #if defined(SHOW_SPK_DELAY_BY_DISTANCE) //Maoyong 2004.04.21
        psprintf(buf, " -    - 0  CM");
        #else
        buf[8]='0';//psprintf(buf, " -    - 2 MS");
        #endif
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+6, buf, fontColor, bgColor);

        val=SETUP_SPK_CENTER_DELAY-2;
    } else
	#ifdef ADD_DVI311_SETUP     //setting string and scale form
    	#ifdef DVI311_NO_PC_MODE
           	if (id==STR_SPHE6500_FMT) {
            	yStart = (SETUP_MENU_YSTART+1+2)*SETUP_BUTTON_HEIGHT;

            	//ac3_dynarange(0 ~ 8)
            	yDelta = 4 * SETUP_BUTTON_HEIGHT;
            	//draw area bgcolor
            	osd_draw_rect(xStart, yStart, xWidth*16, yDelta, bgColor);
            	//draw calibration
            	/*
            	psprintf(buf, " VGA    6OHZ");
            	osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+1, buf, fontColor, bgColor);
            	psprintf(buf, "SVGA    60HZ");
            	osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2, buf, fontColor, bgColor);
            	psprintf(buf, " XGA    60HZ");
            	osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+3, buf, fontColor, bgColor);
            	psprintf(buf, "SXGA    60HZ");
            	osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+4, buf, fontColor, bgColor);
                */
            	//kevin @2k40514
            	if(dvi311_tv_mode==0x84) //PAL
            	psprintf(buf, "            ");
            	else
            	psprintf(buf, "480P    60HZ");
            	osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2+1, buf, fontColor, bgColor);
            	if(dvi311_tv_mode>0x84) //PAL60&NTSC
            	psprintf(buf, "            ");
            	else
            	psprintf(buf, "576P    50HZ");
            	osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2+2, buf, fontColor, bgColor);
            	if(dvi311_tv_mode>0x84) //PAL60&NTSC
            	psprintf(buf, "720P    60HZ");
            	else
            	psprintf(buf, "720P    50HZ");
            	//osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+6, buf, fontColor, bgColor);
                //psprintf(buf, "720P    60HZ");
               	osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2+3, buf, fontColor, bgColor);
               	psprintf(buf, "1080    60HZ");	//kevin 040804
               	osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2+4, buf, fontColor, bgColor);
               	//val=SETUP_AC3DIGITAL_DYNA-2;
               	val=dvi311_mode;
               	}
        #else//#ifdef DVI311_NO_PC_MODE

			if (id==STR_SPHE6500_FMT) {
				yStart = (SETUP_MENU_YSTART+1)*SETUP_BUTTON_HEIGHT;

				//ac3_dynarange(0 ~ 8)
				yDelta = 8 * SETUP_BUTTON_HEIGHT;
				//draw area bgcolor
				osd_draw_rect(xStart, yStart, xWidth*16, yDelta, bgColor);
				//draw calibration
				psprintf(buf, " VGA    6OHZ");
				osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+1, buf, fontColor, bgColor);
				psprintf(buf, "SVGA    60HZ");
				osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2, buf, fontColor, bgColor);
				psprintf(buf, " XGA    60HZ");
				osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+3, buf, fontColor, bgColor);
				psprintf(buf, "SXGA    60HZ");
				osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+4, buf, fontColor, bgColor);
				//kevin @2k40514
				if(dvi311_tv_mode==0x84) //PAL
				psprintf(buf, "            ");
				else
				psprintf(buf, "480P    60HZ");
				osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+5, buf, fontColor, bgColor);
				if(dvi311_tv_mode>0x84) //PAL60&NTSC
				psprintf(buf, "            ");
				else
				psprintf(buf, "576P    50HZ");
				osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+6, buf, fontColor, bgColor);
				if(dvi311_tv_mode>0x84) //PAL60&NTSC
				psprintf(buf, "720P    60HZ");
				else
				psprintf(buf, "720P    50HZ");
		//		osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+6, buf, fontColor, bgColor);
		//		psprintf(buf, "720P    60HZ");
				osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+7, buf, fontColor, bgColor);
				psprintf(buf, "1080    60HZ");	//kevin 040804
				osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+8, buf, fontColor, bgColor);
				//val=SETUP_AC3DIGITAL_DYNA-2;
				val=dvi311_mode;
				}
	#endif//#ifdef DVI311_NO_PC_MODE
#endif
    if (id==STR_OS_DYNAMICRANGE) { //Jeff 20020604
        //ac3_dynarange:0~8
        yStart = (SETUP_MENU_YSTART+1)*SETUP_BUTTON_HEIGHT;

        //ac3_dynarange(0 ~ 8)
        yDelta = 5 * SETUP_BUTTON_HEIGHT;
        //draw area bgcolor
        osd_draw_rect(xStart, yStart, xWidth*16, yDelta, bgColor);
        //draw calibration
        psprintf(buf, " -    - FULL");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+1, buf, fontColor, bgColor);
        psprintf(buf, " -    - 6/8");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2, buf, fontColor, bgColor);
        psprintf(buf, " -    - 4/8");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+3, buf, fontColor, bgColor);
        psprintf(buf, " -    - 2/8");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+4, buf, fontColor, bgColor);
        psprintf(buf, " -    - OFF");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+5, buf, fontColor, bgColor);

        val=SETUP_AC3DIGITAL_DYNA-2;
    } else if (id==STR_OS_SSPK_DELAY)
    {
        //surround speaker delay 0 ~ 15 ms(step=3)
        yStart = (SETUP_MENU_YSTART+3)*SETUP_BUTTON_HEIGHT;

        //spk_volume(0 ~ 8)
        yDelta = 4 * SETUP_BUTTON_HEIGHT;
        //draw area bgcolor
        osd_draw_rect(xStart, yStart, xWidth*16, yDelta, bgColor);
        //draw calibration
        #ifdef NO_SHOW_ADD_ICON   //fengjl add 3-11-28 23:32
            #ifdef  SHOW_SPK_DELAY_BY_DISTANCE  //Maoyong 2004.04.21
            psprintf(buf, " -    - 540CM");
            #else
            psprintf(buf, " -    - 18 MS");
            #endif
        #else   //NO_SHOW_ADD_ICON
        psprintf(buf, " -    - +");
        #endif  //NO_SHOW_ADD_ICON

        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+3, buf, fontColor, bgColor);

        #ifdef AD_TCL//2004-3-22 13:05 lijd
        psprintf(buf, " -    - 12 %s",Ch_zu);
        #elif defined(SHOW_SPK_DELAY_BY_DISTANCE)   //Maoyong 2004.04.21
        psprintf(buf, " -    - 360CM");
        #else
        psprintf(buf, " -    - 12 MS");
        #endif

        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+4, buf, fontColor, bgColor);

        #ifdef AD_TCL//2004-3-22 13:06 lijd
        psprintf(buf, " -    - 6 %s",Ch_zu);
        #elif defined(SHOW_SPK_DELAY_BY_DISTANCE)   //Maoyong 2004.04.21
        psprintf(buf, " -    - 180CM");
        #else
        psprintf(buf, " -    - 6 MS");
        #endif

        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+5, buf, fontColor, bgColor);
        #ifdef SHOW_SPK_DELAY_BY_DISTANCE   //Maoyong 2004.04.21
        psprintf(buf, " -    - 0  CM");
        #else
        buf[8]='0';//psprintf(buf, " -    - 0 MS");
        #endif
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+6, buf, fontColor, bgColor);

        val=SETUP_SPK_SURROUND_DELAY-2;
    }
    else if (id==STR_OS_BRIGHTNESS)
    {
        static const t_osd_str osdstr_brightness[] = {
                {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+1, " -    -  12"},
                {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2, " -    -  10"},
                {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+3, " -    -   8"},
                {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+4, " -    -   6"},
                {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+5, " -    -   4"},
                {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+6, " -    -   2"},
                {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+7, " -    -   0"},
                {0, 0, NULL}
                };
        yDelta = 7 * SETUP_BUTTON_HEIGHT;
        osd_draw_rect(xStart, yStart, xWidth*16, yDelta, bgColor);
        osd_DrawStrings(osdstr_brightness, fontColor, bgColor);
	 #ifdef DP3240_SETUP_MENU
	 osd_DrawLine(xStart, yStart,xStart+60*4-15, yStart,10,3);
	 osd_DrawLine(xStart,  yDelta+63, xStart+60*4-15,yDelta+63,10,2);
	 osd_DrawLine(xStart, yStart,xStart, yDelta+63,10,3);
	 osd_DrawLine(xStart+60*4-17, yStart, xStart+60*4-17,yDelta+63,10,2);
	 #endif

        val = SETUP_BRIGHTNESS - 2;
    }
    else if (id==STR_OS_CONTRAST)
    {
        static const t_osd_str osdstr_contrast[] = {
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+1, " -    -  12"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2, " -    -  10"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+3, " -    -   8"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+4, " -    -   6"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+5, " -    -   4"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+6, " -    -   2"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+7, " -    -   0"},
            {0, 0, NULL}
        };
        yDelta = 7 * SETUP_BUTTON_HEIGHT;
        osd_draw_rect(xStart, yStart, xWidth*16, yDelta, bgColor);
        osd_DrawStrings(osdstr_contrast, fontColor, bgColor);
	 #ifdef DP3240_SETUP_MENU
	 osd_DrawLine(xStart, yStart,xStart+60*4-15, yStart,10,3);
	 osd_DrawLine(xStart,  yDelta+63, xStart+60*4-15,yDelta+63,10,2);
	 osd_DrawLine(xStart, yStart,xStart, yDelta+63,10,3);
	 osd_DrawLine(xStart+60*4-17, yStart, xStart+60*4-17,yDelta+63,10,2);
	 #endif

        val = SETUP_CONTRAST - 2;
    }
    else if (id==STR_OS_HUE)
    {
        static const t_osd_str osdstr_hue[] = {
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+1, " -    -  +6"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2, " -    -  +4"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+3, " -    -  +2"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+4, " -    -   0"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+5, " -    -  -2"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+6, " -    -  -4"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+7, " -    -  -6"},
            {0, 0, NULL}
        };
        yDelta = 7 * SETUP_BUTTON_HEIGHT;
        osd_draw_rect(xStart, yStart, xWidth*16, yDelta, bgColor);
        osd_DrawStrings(osdstr_hue, fontColor, bgColor);
	 #ifdef DP3240_SETUP_MENU
	 osd_DrawLine(xStart, yStart,xStart+60*4-15, yStart,10,3);
	 osd_DrawLine(xStart,  yDelta+63, xStart+60*4-15,yDelta+63,10,2);
	 osd_DrawLine(xStart, yStart,xStart, yDelta+63,10,3);
	 osd_DrawLine(xStart+60*4-17, yStart, xStart+60*4-17,yDelta+63,10,2);
	 #endif
        val = SETUP_HUE - 2;
    }
    else if (id==STR_OS_SATURATION)
    {
        static const t_osd_str osdstr_saturation[] = {
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+1, " -    -  12"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2, " -    -  10"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+3, " -    -   8"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+4, " -    -   6"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+5, " -    -   4"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+6, " -    -   2"},
            {SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+7, " -    -   0"},
            {0, 0, NULL}
        };
        yDelta = 7 * SETUP_BUTTON_HEIGHT;
        osd_draw_rect(xStart, yStart, xWidth*16, yDelta, bgColor);
        osd_DrawStrings(osdstr_saturation, fontColor, bgColor);
	 #ifdef DP3240_SETUP_MENU
	 osd_DrawLine(xStart, yStart,xStart+60*4-15, yStart,10,3);
	 osd_DrawLine(xStart,  yDelta+63, xStart+60*4-15,yDelta+63,10,2);
	 osd_DrawLine(xStart, yStart,xStart, yDelta+63,10,3);
	 osd_DrawLine(xStart+60*4-17, yStart, xStart+60*4-17,yDelta+63,10,2);
	 #endif

        val = SETUP_SATURATION - 2;
    }

#ifdef DIP_CFG_ENABLE
    else if (id==STR_OS_DEINTLC)
    {
        yStart = (SETUP_MENU_YSTART+2)*SETUP_BUTTON_HEIGHT;
        yDelta = 4 * SETUP_BUTTON_HEIGHT;
        osd_draw_rect(xStart, yStart, xWidth*16, yDelta, bgColor);

        psprintf(buf, " -    -   6");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+2, buf, fontColor, bgColor);
        psprintf(buf, " -    -   4");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+3, buf, fontColor, bgColor);
        psprintf(buf, " -    -   2");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+4, buf, fontColor, bgColor);
        psprintf(buf, " -    -   0");
        osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+5, buf, fontColor, bgColor);

        val = SETUP_DE_INTERLACE- 2;
    }
#endif//#ifdef DIP_CFG_ENABLE
    setup_DrawScaleItem(id, up1down, val);
    //top
    if (p_scan==1)
        osd_DrawLine(xStart, yStart, xStart+xWidth*16, yStart, uColor, 2);
    else
        osd_DrawLine(xStart, yStart, xStart+xWidth*16, yStart, uColor, 1);
    //left
    osd_DrawLine(xStart, yStart, xStart, yStart+yDelta, uColor, 1);
    //bottom
    if (p_scan==1)
        osd_DrawLine(xStart, yStart+yDelta, xStart+xWidth*16, yStart+yDelta, dColor, 2);
    else
        osd_DrawLine(xStart, yStart+yDelta, xStart+xWidth*16, yStart+yDelta, dColor, 1);
    //right
    osd_DrawLine(xStart+xWidth*16, yStart, xStart+xWidth*16, yStart+yDelta, dColor, 1);
}



//Jeff 20031110
// 2004/01/30 yltseng, these should reference to 'const' variable
#ifdef  VOL_80
extern const BYTE  VolTab[17+65];
#elif defined(VOL_20)     //fengjl add 2004-03-08 21:38
extern const BYTE  VolTab[22];
#else
extern const BYTE  VolTab[17];
#endif

extern const BYTE  MICVolTab[9];


//
// setupGetSetting : to get some system setting about audio for DSP initialization
//
UINT32 setupGetSetting(BYTE x)
{
    UINT32  iVal=0;
    BYTE    sel;

    switch (x) {
    case 3:     //Time of Mic auto on after sound detect on
        iVal = MIC_PRESENSITIVITY;
        break;

    case 4:     //Time of Mic auto off after sound detect off
        iVal = MIC_AFTERSENSITIVITY;
        break;

    case 5:     //Mic sound detect gain threshold
        iVal = MIC_THRESHOLD;
        break;

    case 6:     //Mic switch

    #ifdef NOT_SHOW_MIC_SETUP_DAFAULT_AUTO//nono 4-1-11 18:52
            sel = 0;
    #else
    	#ifdef NO_MIC
    		sel = 2;  // setup-> off, DSP->off
    	#else
        	sel = SETUP_MIC_ONF-2;
        #endif
    #endif//NOT_SHOW_MIC_SETUP_DAFAULT_AUTO

#ifdef DVDRELEASE
        //setup :   0->auto, 1->off
        //output:   0->off,  1->on, others:auto
        if (sel == 0) {     //auto
            iVal = 2;
#ifndef NOT_SHOW_MIC_SETUP_DAFAULT_AUTO
            SETUP_MIC_ONF = 2;
#endif//#ifdef NOT_SHOW_MIC_SETUP_DAFAULT_AUTO

        }
        else
        {
            #if defined(NO_MIC)  //fengjl add to avoid mic output when define no_mic 2004-03-19 11:45
            {
                iVal = 0; //off
            }
            #else
            {            //off
            	iVal = 0;
            	SETUP_MIC_ONF = 3;
        	}
            #endif
        }
        //printf("release:SETUP_MIC_ONF = %d, iVal=%d\n", SETUP_MIC_ONF, iVal);
#else
        //setup :   0->auto, 1->on, 2->off
        //output:   0->off,  1->on, others:auto
        if (sel == 0) {     //auto
            iVal = 2;
            #ifndef NO_MIC
	            SETUP_MIC_ONF = 2;
	        #endif
        } else if (sel == 1) {     //on
            iVal = 1;
            #ifndef NO_MIC
	            SETUP_MIC_ONF = 3;
	        #endif
        } else {
            iVal=0;
            #ifndef NO_MIC
	            SETUP_MIC_ONF = 4;
	        #endif
        }
        //printf("debug:SETUP_MIC_ONF = %d, iVal=%d\n", SETUP_MIC_ONF, iVal);
#endif
        break;

    case 7:     //Audio gain
        if (user_mute) {
            iVal=0x7fffff;
        } else
        {
            //iVal=0x7fffff-(audio_volume*0x7fffff/VOL_VALUE);
            #ifdef CNTR_5SPK_VOLUME
            //iVal=0x7fffff-(volume_5SPK[0]*0x7fffff/VOL_VALUE);
             #ifdef CNTR_5SPK_TYPE_2                    //linrc add 2004-10-12 9:53
	         if(IS_AUDIF_CODING_MODE_LPCM || IS_AUDIF_CODING_MODE_DTS
	             || IS_AUDIF_CODING_MODE_PCM || IS_AUDIF_CODING_MODE_WMA
	             || IS_AUDIF_CODING_MODE_DTSCD)
	         {
	            iVal=0x7fffff - ( (VolTab[volume_5SPK[0]]<<16) | 0xffff);
	         }
	         else iVal=0x7fffff - ( (VolTab[15]<<16) | 0xffff);
            #else
              iVal=0x7fffff - ( (VolTab[volume_5SPK[0]]<<16) | 0xffff); //Jeff 20031114
            #endif
            #else
            //iVal=0x7fffff-(audio_volume*0x7fffff/VOL_VALUE);
            iVal=0x7fffff-( (VolTab[audio_volume]<<16) | 0xffff); //Jeff 20031114
            #endif
        }
        break;

    case 44: //MIC-2 gain, if we want to set different gain, we can seperate these two, Jeff 20030901
      #ifndef MIC_2CHANNEL//nono 5-10-13 17:10 At this time, MIC_2 need to be mute.//felix
      iVal=0x7fffff;
      break;
    #endif 
    case 8:     //MIC gain
#ifdef NO_MIC
    #ifdef NO_MIC_ITEM_ENABLE_MIC       //kubby add for BBK_DVD,3-10-19 23:07
        //iVal=0x7fffff-(mic_volume*0x7fffff/8);
        iVal = 0x7fffff - ( (MICVolTab[mic_volume]<<16) | 0xffff); //Jeff 20031110
    #else
        iVal=0x7fffff;
    #endif
#else
        //iVal=0x7fffff-(mic_volume*0x7fffff/8);
        iVal = 0x7fffff - (( MICVolTab[mic_volume]<<16) | 0xffff); //Jeff 20031110
#endif
/*huziqin 2004-3-5*/
//#ifdef SUPPORT_RECEIVER
    //iVal = (0x7fffff-(( MICVolTab[8]<<16) | 0xffff));
//#endif
        break;

    case 9:     //Key shift
        iVal = audio_key+8;
        break;

    case 10:    //Echo delay
#ifdef USE_MIC_ECHO_PARAM
                 iVal = echo_para_tbl[echo_level][1];//2004AUDDRV echo_para[echo_level][1];
#else
        iVal = echo_level;
#endif
        break;

    case 11:    //Echo gain
#ifdef USE_MIC_ECHO_PARAM
                  iVal = echo_para_tbl[echo_level][0];//2004AUDDRV echo_para[echo_level][0];
#else
        iVal = ECHO_DECAY_INIT;
#endif
        break;

    case 12:    //3D surround
        iVal = soundGetSurroundType();  //0:off other:different type
        break;

    case 13:    //subwoof

    #ifdef ONLY_DOWNMIX//4-1-15 18:31
        iVal = 0;
    #elif defined(SPEAKER_CONFIG)
        iVal = speaker_subwoofer;
    #else//ONLY_DOWNMIX

        sel=SETUP_SPK_SUBWOOFER-2;
        iVal = sel;
    #endif//ONLY_DOWNMIX
        break;

    case 14: //S/PDIF,terry,2003/12/12 06:13PM
                //bbk setup:2->source,  3->PCM
                //setup:    2:spdif off 3->source,  4->PCM
        //output:   0->0ff,     1->PCM,         2->source

#ifdef DIVIDE_AC3_DTS_SPDIF_OUTPUTS
if(coding_mode_now&(AUDIF_CODING_MODE_AC3))
{
    if(SETUP_SPDIF == SPDIFBITSTREAM)
        iVal = 2;
    else if(SETUP_SPDIF == SPDIFPCM)
        iVal = 1;
    else
        iVal = 0;

}else if ((coding_mode_now&(AUDIF_CODING_MODE_DTS ) )|| ((cd_type_loaded==CDDA) && (cd_subtype==CD_DTS)) )

    if(SETUP_SPDIF_DTS == SPDIFBITSTREAM)
        iVal = 2;
    else
        iVal = 0;

else
{
        if(SETUP_SPDIF_PCM==SPDIFBITSTREAM)
            iVal = 1;
        else
            iVal = 0;
}
#else//DIVIDE_AC3_DTS_SPDIF_OUTPUTS
    if(SETUP_SPDIF == SPDIFBITSTREAM)
        iVal = 2;
    else if(SETUP_SPDIF == SPDIFPCM)
        iVal = 1;
    else
        iVal = 0;
#endif//DIVIDE_AC3_DTS_SPDIF_OUTPUTS


#ifdef NO_DTS_OUTPUT
        if (
            ((cd_type_loaded == CDDA) && (cd_subtype == CD_DTS))
#ifdef FORCE_NO_DTS_OUTPUT//nono 4-5-5 13:31
            ||(coding_mode_now&AUDIF_CODING_MODE_DTS)
#endif//#ifdef FORCE_NO_DTS_OUTPUT
#ifdef DIVIDE_AC3_DTS_SPDIF_OUTPUTS
            &&(SETUP_SPDIF_DTS==SPDIFBITSTREAM)
#endif//#ifdef DIVIDE_AC3_DTS_SPDIF_OUTPUTS
           )
            iVal = 2;
#endif//#ifdef NO_DTS_OUTPUT

    #if defined(NO_SPDIF)//nono 20031027
        iVal = 0;
    #endif//NO_SPDIF
        printf("===>spdif out:%x\n",iVal);
        break;
#ifdef LPCM_NO_SHOW_BAND  //fengjl add 2004-03-19 18:51
    case 15:    //EQ            ,terry,2003/9/26 04:51PM
        if(coding_mode_now==AUDIF_CODING_MODE_LPCM)//2004-03-19 18:30
        //iVal = bEqDisplay;
        iVal = 0;
        break;
#endif
    case 16:
        if (coding_mode_now==AUDIF_CODING_MODE_AC3) {
            iVal = 1;
        } else if (coding_mode_now==AUDIF_CODING_MODE_DTS) {
            iVal = 11;
        } else {
            iVal = 0;
        }
        break;

#ifdef AC3_BASS_MANAGEMENT
    case 27: //Jeff 20021030
        #ifdef ONLY_DOWNMIX//4-1-15 18:31
        iVal = 0;
        #elif defined(SUPPORT_APOGEE_AMP)
        iVal = SETUP_FRONT_SPEAKER -2;   //xulf 2004-01-05
        #elif defined(TEST_BASS_MANAGEMENT) //Andrew Wen 20040803
        // use SPK setting to find config and setting value, set into to word 27
        iVal = AUDIF_Get_BassConfig();//2004AUDDRV SetBassConfig();
        #else//ONLY_DOWNMIX
        iVal = SETUP_BASS_MODE-2;
        #endif//ONLY_DOWNMIX
        break;
#endif

    case 32:
        break;

    case 33:
        {
        /*
         SETUP_SPK_DOWNMIX (2-5)
         AC3/DTS/LPCM/PPCM multichannel mode downmix mode(0x06-0x09)
            2 --> Lt/Rt         0x08
            3 --> Lo/Ro         0x07
            4 --> Ls/Rs         0x09
            5 --> 5.1 channel   0x06
        */
#ifdef NO_VSURROUND_CHANNEL
            BYTE downmix_init[4]={0x08,0x07,0x06,0x09};
#else
    #ifdef JIEKE_DVD//wangfeng 2003-10-28 11:18
            BYTE downmix_init[4]={0x08,0x07,0x06,0x09};
    #else
            BYTE downmix_init[4]={0x08,0x07,0x09,0x06};
    #endif
#endif

#ifdef DIG_AND_AUD
            iVal=0x08;
#else
            iVal=downmix_init[SETUP_SPK_DOWNMIX-2];
#endif
            break;
        }

#ifdef SUPPORT_PROLOGIC_II
    case 35:
    {
     
        if (SETUP_PROLOGIC_II==2)
        {
            pl2_init_val = PROLOGICII_MOVIE_DSP_INIT ;//added by STEVEN 2006/5/17
            
        } else if (SETUP_PROLOGIC_II==3)           //add definefor prologicII initial value
        {
            pl2_init_val = PROLOGICII_MUSIC_DSP_INIT;
        } else if (SETUP_PROLOGIC_II==4)
        {
            pl2_init_val = PROLOGICII_OFF_DSP_INIT;
        }

    if( !check_chipinfo(6) )
        pl2_init_val=PROLOGICII_OFF_DSP_INIT;

        iVal=pl2_init_val;
        break;
    }
#endif
    case 39:    //Left channel gain , Jeff 20030901
    case 40:    //Right channel gain
    case 41:    //Left surround channel gain
    case 42:    //Right surround channel gain
    case 43:    //Center channel gain

    #ifdef CNTR_5SPK_VOLUME
        //iVal=0x7fffff-(volume_5SPK[x-38]*0x7fffff/VOL_VALUE);   //[x-38]:1->left-channel 2...
        iVal=0x7fffff- ( (VolTab[volume_5SPK[x-38]]<<16) | 0xffff);   //[x-38]:1->left-channel 2...
    #else
        iVal=0; //max. volume
    #endif
        break;

     case 46:
         //Sub-Woofer channel gain, Jeff 20031028
         //printf("volume_5SPK[x-40]=%d\n",volume_5SPK[x-40]);
    #ifdef CNTR_5SPK_VOLUME
         //iVal=0x7fffff-(volume_5SPK[x-40]*0x7fffff/VOL_VALUE);   //[x-38]:1->left-channel 2...
         iVal=0x7fffff- ( (VolTab[volume_5SPK[x-40]]<<16) | 0xffff);   //[x-38]:1->left-channel 2...
    #endif
         break;

    } //switch (x) {

    return iVal;
}



int setup_IsSet2SPDIF_Bitstream()
{
//2004AUDDRV 20041014 Oliver
//    if(( (SETUP_SPDIF==SPDIFBITSTREAM)
//#ifdef DIVIDE_AC3_DTS_SPDIF_OUTPUTS
//             && (cd_type_loaded==CDDVD)
//#endif//#ifdef DIVIDE_AC3_DTS_SPDIF_OUTPUTS
//         )
//#ifdef DIVIDE_AC3_DTS_SPDIF_OUTPUTS
//    ||( (SETUP_SPDIF_DTS==SPDIFBITSTREAM) && (cd_type_loaded==CDDVD) )
//#endif
//    )
  //2004AUDDRV 20041014 Oliver
  //  The following behavior is the same as above...
#ifdef DIVIDE_AC3_DTS_SPDIF_OUTPUTS
    if((cd_type_loaded==CDDVD)&&((SETUP_SPDIF==SPDIFBITSTREAM)||(SETUP_SPDIF_DTS==SPDIFBITSTREAM)))
  #else
    if(SETUP_SPDIF==SPDIFBITSTREAM)
#endif
    return 1;

    if((coding_mode_now&AUDIF_CODING_MODE_DTS) || (cd_subtype==CD_DTS)){
#ifdef  NO_DTS_OUTPUT
        return 1;
#endif
        if (!check_chipinfo(2)) return 1;
    }
    return 0;
}



#ifndef DELETE_SPDIF_OFF_ITEM//zhaoyanhua add 2003-12-8 17:36
int setup_IsSet2SPDIF_OFF()
{
    if (SETUP_SPDIF==SPDIFSIMULATE)
        return 1;
    else
        return 0;
}
#endif

int setup_DTSCD_IsSet2SPDIF_PCMAndOff()//nono 20030816
{
#ifdef DELETE_SPDIF_OFF_ITEM//zhaoyanhau add 2003-12-8 17:53
#define is_SPDIF_PCMAndOff()    (SETUP_SPDIF==SPDIFPCM)
#elif defined(NO_DTS_OUTPUT)
#define is_SPDIF_PCMAndOff()    (SETUP_SPDIF==SPDIFSIMULATE)
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
#define is_SPDIF_PCMAndOff()    (SETUP_SPDIF_PCM==SPDIFSIMULATE || SETUP_SPDIF==SPDIFSIMULATE)
#else
#define is_SPDIF_PCMAndOff()    (0)// (SETUP_SPDIF==SPDIFSIMULATE)||(SETUP_SPDIF==SPDIFPCM) )
#endif

    if(
          (is_SPDIF_PCMAndOff() ) &&
           (
              ( (cd_subtype == CD_DTS)&&(cd_type_loaded == CDDA) )
              ||(coding_mode_now&AUDIF_CODING_MODE_DTS)
           )
      )
        return 1;
    else
        return 0;
}

void setup_Set2SPDIF_PCM()
{
    SETUP_SPDIF = SPDIFPCM;

    run_save_sel_cmd(AUDPAGE, DIGIOUTITEM);
}



int setup_IsMICoff()
{
    int iRes=0;

#ifdef DVDRELEASE
    if (SETUP_MIC_ONF==3) iRes=1;
#else
    if (SETUP_MIC_ONF==4) iRes=1;
#endif

    return iRes;
}

#if defined(NEW_PARENTAL_GUI)||defined(MODIFY_PARENTAL_GUI) //zhaoyanhua add 2003-11-28 10:46
/*
 * exit parental GUI.
 */
void ExitParentalGUI(void)
{
    full_scrn = 0;
#if defined(NEW_PARENTAL_GUI)
    new_parental_gui = 0;////avoid the error:when TRAY OUT enter SETUP ,show error infomation.
#elif defined(MODIFY_PARENTAL_GUI)
    parental_gui_flag = 0;                    //nono 2004-5-7 0:24
#endif//defined(MODIFY_PARENTAL_GUI)

#ifdef DYNAMIC_SPECTRUM    //fengjl 2004-06-23 09:57
if (band_onoff)
{
    #ifdef LPCM_NO_SHOW_BAND
        if(coding_mode_now!=AUDIF_CODING_MODE_LPCM)
    #endif
        bEqDisplay=1;
        Show3dspectrum();
}
else
#endif

#ifdef SDRAM_16Mb_Mode  //Maoyong 2004.07.03
    regs0->osd_base_addr=GetOSDBackUpAddress();
#endif
    osd_init();

//  if(cd_type_loaded==CDDVD)//nono 2004-5-7 0:13
    nav_param_by_user();

}
#endif//#ifdef NEW_PARENTAL_GUI//zhaoyanhua add 2003-11-28 10:46
#ifdef NEW_PARENTAL_GUI//zhaoyanhua add 2003-11-28 10:46

/*
 *  Show password GUI when playing parental disc
 */
void ShowPasswordGUI()
{
    const char *str;

    new_parental_gui = 1;

#if defined(SDRAM_16Mb_Mode)//&&defined(NEW_STYLE_SETUP)
            //NOTE:
            //when SDRAM_16M_Mode,ShowTitle() may destroyed
            // OSD memory. So must evaluate osd_base_addr again.
            //zhaoyanhua add 2003-11-10 17:06
            regs0->osd_base_addr=OSD_BASE_USE_ADDR;//P_BIDIR_LUMA;
            //clead 2004-3-26 add
#endif

    full_scrn = SETUP;
    osd_init_parental_gui();

    #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-2 17:32
    SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffff);
    #endif

#ifdef NEW_PARENTAL_GUI_SHOW_MULTI_LANG   //2004-2-20 09:21张宇M
    str =_OsdMessegeFont1[osd_font_mode][STR_OS_PASSWORD];   //wsf 2004-2-6 16:50
#else//NEW_PARENTAL_GUI_SHOW_MULTI_LANG
    str ="PASSWORD:";//2004-2-20 09:21张宇M
#endif//NEW_PARENTAL_GUI_SHOW_MULTI_LANG

    osd_DrawRegionString(MESSAGE_XSTART, MESSAGE_YSTART, str, MESSAGE_FONT_COLOR, MESSAGE_BK_COLOR, 0);

     //show current focus
    osd_draw_region_rect(PASSWD_BUTTON_XSTART,PASSWD_BUTTON_YSTART,PASSWD_BUTTON_XLEN,PASSWD_BUTTON_YLEN,PASSWORD_BK_HL_COLOR,0);
    str = _OsdMessegeFont1[osd_font_mode][STR_OS_LOCK];
    osd_DrawRegionString(PASSWORD_XSTART, PASSWORD_YSTART, str, PASSWORD_FONT_COLOR, PASSWORD_BK_HL_COLOR, 0);

}


/*
 * check if the password is correct
 */

void show_NewParentalGui_page_OK(void)
{

        const char *str;


        osd_draw_region_rect(PASSWD_BUTTON_XSTART,PASSWD_BUTTON_YSTART,PASSWD_BUTTON_XLEN,PASSWD_BUTTON_YLEN,PASSWORD_BK_COLOR,0);
        //show UNLOCK state
        str = _OsdMessegeFont1[osd_font_mode][STR_OS_UNLOCK];
        osd_DrawRegionString(PASSWORD_XSTART, PASSWORD_YSTART, str , PASSWORD_FONT_COLOR, PASSWORD_BK_COLOR,0);
        osd_draw_region_rect(OKERROR_BUTTON_XSTART,OKERROR_BUTTON_YSTART,OKERROR_BUTTON_XLEN,OKERROR_BUTTON_YLEN,OKERROR_BK_COLOR,0);
        //show "OK"
        #ifdef PASSWORD_IN_CH

        osd_DrawRegionString(OKERROR_XSTART-1, OKERROR_YSTART, _OsdMessegeFont1[osd_font_mode][STR_OS_PASSWORD_RIGHT] , OKERROR_FONT_COLOR, OKERROR_BK_COLOR,0);  //2004-2-20 09:24张宇M
        #else
        osd_DrawRegionString(OKERROR_XSTART-1, OKERROR_YSTART,"OK" , OKERROR_FONT_COLOR, OKERROR_BK_COLOR,0);  //2004-2-20 09:24张宇M
        #endif
        delay_srv_10ms(200);//20040302


}

void show_NewParentalGui_page_ERROR(void)
{
        const char *str;

        osd_draw_region_rect(PASSWD_BUTTON_XSTART,PASSWD_BUTTON_YSTART,PASSWD_BUTTON_XLEN,PASSWD_BUTTON_YLEN,PASSWORD_BK_COLOR,0);
        //show UNLOCK state
        //show LOCK state
        str = _OsdMessegeFont1[osd_font_mode][STR_OS_LOCK];
        osd_DrawRegionString(PASSWORD_XSTART-2, PASSWORD_YSTART, str , PASSWORD_FONT_COLOR, PASSWORD_BK_COLOR,0);
       // str = osd_err_str[osd_font_mode][PARENTAL_ERR-1];
        osd_draw_region_rect(OKERROR_BUTTON_XSTART,OKERROR_BUTTON_YSTART,OKERROR_BUTTON_XLEN,OKERROR_BUTTON_YLEN,OKERROR_BK_COLOR,0);
        #ifdef PASSWORD_IN_CH
        osd_DrawRegionString(OKERROR_XSTART-1, OKERROR_YSTART, _OsdMessegeFont1[osd_font_mode][STR_OS_PASSWORD_ERROR]  , OKERROR_FONT_COLOR, OKERROR_BK_COLOR,0);     //2004-2-20 09:24张宇M
        #else
        osd_DrawRegionString(OKERROR_XSTART-1, OKERROR_YSTART,"ERROR" , OKERROR_FONT_COLOR, OKERROR_BK_COLOR,0);  //2004-2-20 09:24张宇M
        #endif
        delay_srv_10ms(200);//20040302


}

void check_parent_password(void)
{
    extern const char *const osd_err_str[N_OSD_LANGS][3];
    const char *str;


    //if ((UserSet.parental_ststus == C_LOCK)&&    //hq marked, avoid entering play when double cliked ENTER Key without inputing password. 2004-3-5 13:28
#ifdef SETUP_6_DIGIT_PASSWORD
    if ((UserSet.parental_ststus == C_LOCK)&&(digit_cnt == PASSWORD_LENGTH)&&
#else//SETUP_6_DIGIT_PASSWORD
    if ((UserSet.parental_ststus == C_LOCK)&&(digit_cnt == PASSWORD_LENGTH)&&
#endif//SETUP_6_DIGIT_PASSWORD
#ifdef USER_SUPER_PASSWD_ALSO_PLAY      //heqiang,2004-3-5 11:44
       ((tmp_passwd == UserSet.parent_passwd )||(tmp_passwd == USER_SUPER_PASSWORD )))
#elif defined(MODIFY_PASSWORD_3308)
       ((tmp_passwd == UserSet.parent_passwd )||(tmp_passwd == USER_SUPER_PASSWORD )))
#else//USER_SUPER_PASSWD_ALSO_PLAY
       (tmp_passwd == UserSet.parent_passwd ))
#endif//USER_SUPER_PASSWD_ALSO_PLAY
    {
        UserSet.parental_ststus = C_UNLOCK;

/*
        osd_draw_region_rect(PASSWD_BUTTON_XSTART,PASSWD_BUTTON_YSTART,PASSWD_BUTTON_XLEN,PASSWD_BUTTON_YLEN,PASSWORD_BK_COLOR,0);
        //show UNLOCK state
        str = _OsdMessegeFont1[osd_font_mode][STR_OS_UNLOCK];
        osd_DrawRegionString(PASSWORD_XSTART, PASSWORD_YSTART, str , PASSWORD_FONT_COLOR, PASSWORD_BK_COLOR,0);
        osd_draw_region_rect(OKERROR_BUTTON_XSTART,OKERROR_BUTTON_YSTART,OKERROR_BUTTON_XLEN,OKERROR_BUTTON_YLEN,OKERROR_BK_COLOR,0);
        //show "OK"
        #ifdef PASSWORD_IN_CH

        osd_DrawRegionString(OKERROR_XSTART-1, OKERROR_YSTART, _OsdMessegeFont1[osd_font_mode][STR_OS_PASSWORD_RIGHT] , OKERROR_FONT_COLOR, OKERROR_BK_COLOR,0);  //2004-2-20 09:24张宇M
        #else
        osd_DrawRegionString(OKERROR_XSTART-1, OKERROR_YSTART,"OK" , OKERROR_FONT_COLOR, OKERROR_BK_COLOR,0);  //2004-2-20 09:24张宇M
        #endif
        delay_srv_10ms(200);//20040302
*/
        show_NewParentalGui_page_OK();

    }
    else//if password id incorrect,show error message.
    {
        printf("uuuuuuu   show dvd error\n\n");
        //show grade error
        //draw rect
        osd_draw_region_rect(PASSWD_BUTTON_XSTART,PASSWD_BUTTON_YSTART,PASSWD_BUTTON_XLEN,PASSWD_BUTTON_YLEN,PASSWORD_BK_COLOR,0);
        //show UNLOCK state
        //show LOCK state
        str = _OsdMessegeFont1[osd_font_mode][STR_OS_LOCK];
        osd_DrawRegionString(PASSWORD_XSTART-2, PASSWORD_YSTART, str , PASSWORD_FONT_COLOR, PASSWORD_BK_COLOR,0);
       // str = osd_err_str[osd_font_mode][PARENTAL_ERR-1];
        osd_draw_region_rect(OKERROR_BUTTON_XSTART,OKERROR_BUTTON_YSTART,OKERROR_BUTTON_XLEN,OKERROR_BUTTON_YLEN,OKERROR_BK_COLOR,0);
        #ifdef PASSWORD_IN_CH
        osd_DrawRegionString(OKERROR_XSTART-1, OKERROR_YSTART, _OsdMessegeFont1[osd_font_mode][STR_OS_PASSWORD_ERROR]  , OKERROR_FONT_COLOR, OKERROR_BK_COLOR,0);     //2004-2-20 09:24张宇M
        #else
        osd_DrawRegionString(OKERROR_XSTART-1, OKERROR_YSTART,"ERROR" , OKERROR_FONT_COLOR, OKERROR_BK_COLOR,0);  //2004-2-20 09:24张宇M
        #endif
        delay_srv_10ms(200);//20040302

        show_NewParentalGui_page_ERROR();
    }
     reset_passwd_cnt();    //dingzhy 04-02-09 10:31AM
}


#else//#ifdef NEW_PARENTAL_GUI//zhaoyanhua add 2003-11-28 10:46

//function inital name is setup_Checkpassword()
//zhaoyanhua modify the function name 2003-11-29 20:34
void ShowPasswordGUI()
{
#ifdef NEW_STYLE_SETUP
    GBM_run_setupmenu_flag =1;
#endif

#ifdef MODIFY_PARENTAL_GUI
    parental_gui_flag = 1;
#endif//MODIFY_PARENTAL_GUI

#if defined(SDRAM_16Mb_Mode)//&&defined(NEW_STYLE_SETUP)
            //NOTE:
            //when SDRAM_16M_Mode,ShowTitle() may destroyed
            // OSD memory. So must evaluate osd_base_addr again.
            //zhaoyanhua add 2003-11-10 17:06
            regs0->osd_base_addr=OSD_BASE_USE_ADDR;//P_BIDIR_LUMA;
            //clead 2004-3-26 add
#endif

    full_scrn=SETUP;
    osd_init_setup();

    setupLevel=2;
#ifdef GBM_FULL_FUNCTION
    page = SysNextPage;
#else//GBM_FULL_FUNCTION
    page = SYSPAGE;
#endif//GBM_FULL_FUNCTION

    index_y=PASSWDITEM;
    index_y_start=0;

    index_y2=0;
    submenuStart=PASSWDITEM+2;
    ShowSetupPage(1);

}
#endif//#ifdef NEW_PARENTAL_GUI//zhaoyanhua add 2003-11-28 10:46



#if defined(DVD_AUDIO)//20040302
void check_dvd_audio_password(void)
{
//    extern const char *const osd_err_str[N_OSD_LANGS][3];
//    const char *str;

    printf("tmp_passwd=%d\n",tmp_passwd);
    if (pDSV->HGR_INF==tmp_passwd)
    {

//        osd_draw_region_rect(PASSWD_BUTTON_XSTART,PASSWD_BUTTON_YSTART,PASSWD_BUTTON_XLEN,PASSWD_BUTTON_YLEN,PASSWORD_BK_COLOR,0);
        //show UNLOCK state
//        str = _OsdMessegeFont1[osd_font_mode][STR_OS_UNLOCK];
//        osd_DrawRegionString(PASSWORD_XSTART, PASSWORD_YSTART, str , PASSWORD_FONT_COLOR, PASSWORD_BK_COLOR,0);
/*
        osd_draw_region_rect(OKERROR_BUTTON_XSTART,OKERROR_BUTTON_YSTART,OKERROR_BUTTON_XLEN,OKERROR_BUTTON_YLEN,OKERROR_BK_COLOR,0);
        //show "OK"
        #ifdef PASSWORD_IN_CH

        osd_DrawRegionString(OKERROR_XSTART-1, OKERROR_YSTART, _OsdMessegeFont1[osd_font_mode][STR_OS_PASSWORD_RIGHT] , OKERROR_FONT_COLOR, OKERROR_BK_COLOR,0);  //2004-2-20 09:24张宇M
        #else
        osd_DrawRegionString(OKERROR_XSTART-1, OKERROR_YSTART,"OK" , OKERROR_FONT_COLOR, OKERROR_BK_COLOR,0);  //2004-2-20 09:24张宇M
        #endif
*/
#ifdef NEW_PARENTAL_GUI
        show_NewParentalGui_page_OK();
#endif

        pDSV->hid_gp_chk_pwd=0;



    }
    else//if password id incorrect,show error message.
    {
        printf("uuuuuuu   show dvd error\n\n");
        //show grade error
        //draw rect

//        osd_draw_region_rect(PASSWD_BUTTON_XSTART,PASSWD_BUTTON_YSTART,PASSWD_BUTTON_XLEN,PASSWD_BUTTON_YLEN,PASSWORD_BK_COLOR,0);
        //show UNLOCK state
        //show LOCK state
//        str = _OsdMessegeFont1[osd_font_mode][STR_OS_LOCK];
//        osd_DrawRegionString(PASSWORD_XSTART-2, PASSWORD_YSTART, str , PASSWORD_FONT_COLOR, PASSWORD_BK_COLOR,0);
/*
       // str = osd_err_str[osd_font_mode][PARENTAL_ERR-1];
        osd_draw_region_rect(OKERROR_BUTTON_XSTART,OKERROR_BUTTON_YSTART,OKERROR_BUTTON_XLEN,OKERROR_BUTTON_YLEN,OKERROR_BK_COLOR,0);
        #ifdef PASSWORD_IN_CH
        osd_DrawRegionString(OKERROR_XSTART-1, OKERROR_YSTART, _OsdMessegeFont1[osd_font_mode][STR_OS_PASSWORD_ERROR]  , OKERROR_FONT_COLOR, OKERROR_BK_COLOR,0);     //2004-2-20 09:24张宇M
        #else
        osd_DrawRegionString(OKERROR_XSTART-1, OKERROR_YSTART,"ERROR" , OKERROR_FONT_COLOR, OKERROR_BK_COLOR,0);  //2004-2-20 09:24张宇M
        #endif
*/


#ifdef NEW_PARENTAL_GUI
        show_NewParentalGui_page_ERROR();
#endif
    }
       delay_srv_10ms(200);

}

void ExitDVDAudioGUI(void)
{
    full_scrn = 0;
#ifdef NEW_PARENTAL_GUI
    new_parental_gui = 0;////avoid the error:when TRAY OUT enter SETUP ,show error infomation.
#endif

#if defined(MODIFY_PARENTAL_GUI)
    parental_gui_flag = 0;
#endif//#if defined(MODIFY_PARENTAL_GUI)
                        //zhaoyanhua add 2004-2-9 11:24
#ifdef SDRAM_16Mb_Mode  //Maoyong 2004.07.03
    regs0->osd_base_addr=GetOSDBackUpAddress();
#endif
    osd_init();
//    nav_param_by_user();
}
#endif//#if defined(DVD_AUDIO)//20040302

/*
 * Show password GUI and get input password
 * NOTE:
 *    these sentences are abstracted from ncmd_exe.
 *
 * zhaoyanhua 2003-11-28 22:23
 */
UINT32 setup_CheckPasswd()
{
    UINT32 isPasswdRight;
    extern int user_input_pwd;

    UserSet.parental_ststus=0;  //nono 2003-11-21 14:19

    //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 11:11
    SetFullscrnCmdFuncPtr( setup_func_up, setup_func_down, setup_func_left,
                           setup_func_right,  setup_func_select);
    ShowPasswordGUI();

    user_input_pwd=1;
    while(user_input_pwd==1)
        polling();

    if(UserSet.parental_ststus==1)
    {
        isPasswdRight = 1;
    }    
    else
    {
        isPasswdRight = 0;
    }
    
   #ifdef SOFT_MENU         //lyc 2005-1-4 note:when play rating disc show new_parent_gui
      #ifdef NEW_PARENTAL_GUI
        if(new_parental_gui)
       {
         check_parent_password();
         new_parental_gui = 0;

       }
      #endif
  #endif

    if(user_input_pwd==2)//nono 2-6-6 23:45 to avoid parental contrl invalid.
    {
        //Maoyong 2004.03.06 , Record disc check Level in SYSTEM_SETUP_BROWSER,
        //I use (user_input_pwd ==2 ) to check specical exit PTL Level Check(IRC_POWER , IRC_EJECT)
        #ifdef  CHECK_RECORD_DISK_PARENT_LVL
        if( (system_state == SYSTEM_BROWSE) )
        #endif
        user_input_pwd=0;
    }
    else
#ifdef NEW_PARENTAL_GUI//zhaoyanhua add 2003-11-28 19:50
        ExitParentalGUI();
#else
        ircmd_setup();
#endif

    return isPasswdRight;
}

//#if defined(NEW_PARENTAL_GUI)&&defined(DVD_AUDIO)//20040302
#if defined(DVD_AUDIO)//20040302
void setup_CheckDVDAudioPasswd()
{
    extern int user_input_pwd;
    extern UINT8   polling_avoid_reentry;

    ShowPasswordGUI();

    user_input_pwd=1;
    polling_avoid_reentry=0;
    while(user_input_pwd==1)
        polling();

    if(user_input_pwd==2)//nono 2-6-6 23:45 to avoid parental contrl invalid.
        user_input_pwd=0;
    else
#ifdef NEW_PARENTAL_GUI
        ExitDVDAudioGUI();
#else
        ircmd_setup();
#endif
}
#endif//#if defined(NEW_PARENTAL_GUI)&&defined(DVD_AUDIO)//20040302

void setup_SetKey()
{
    SETUP_KEY = audio_key+8;
    AUDIF_Set_Key(SETUP_KEY);//2004AUDDRV AudioSetKey(audio_key+8); //Key-shift command to DSP(1~15)
#ifndef NOT_REWRITE_MIC_VALUE //axel 2004/2/14 03:19PM
    run_save_sel_cmd(AUDPAGE, KEYITEM);
#endif  //NOT_REWRITE_MIC_VALUE //axel 2004/2/14 03:19PM
}



void setup_SetEcho()
{
    SETUP_ECHO = echo_level+2;

#ifdef USE_MIC_ECHO_PARAM
    AUDIF_Set_EchoPara(echo_level);//2004AUDDRV AudioSetEchoPara(echo_level);
#else
    AUDIF_Set_Echo(echo_level, echo_level);//2004AUDDRV AudioSetEcho(echo_level, echo_level); //Echo command to DSP
#endif //USE_MIC_ECHO_PARAM
#ifndef NOT_REWRITE_MIC_VALUE     //axel 2004/2/8 10:05PM
    run_save_sel_cmd(AUDPAGE, ECHOITEM);
#endif //NOT_REWRITE_MIC_VALUE //axel 2004/2/14 03:19PM
}



void setup_SetMic()
{
    //#ifdef    MIC_2CHANNEL
    //if(id==STR_OS_MIC_VOL||id==STR_OS_MIC_VOL_1)
    //#endif
#if defined(MIC_2CHANNEL)&&defined(MIC_FUNCTION_KEY)
if(bFuncStep==1)
{
    SETUP_MIC_VOL = mic_volume+2;
    AUDIF_Set_MICVol(mic_volume);//2004AUDDRV AudioSetMICVol(mic_volume);
    //#ifdef    MIC_2CHANNEL
}
else if(bFuncStep==5)
{
    SETUP_MIC_VOL_2 = mic_volume+2;
    AUDIF_Set_MICVol2(mic_volume);//2004AUDDRV AudioSetMICVol_2(mic_volume);
}
    //if(id==STR_OS_MIC_VOL_2)
    //SETUP_MIC_VOL_2 = mic_volume+2;
    //#endif
    run_save_sel_cmd(AUDPAGE, 4);
    run_save_sel_cmd(AUDPAGE, 5);
#else// //#ifdef    MIC_2CHANNEL
    SETUP_MIC_VOL = mic_volume+2;
    AUDIF_Set_MICVol(mic_volume);//2004AUDDRV AudioSetMICVol(mic_volume);  //fengjl edit it 2004-06-17 21:51
#endif//    //#ifdef    MIC_2CHANNEL

#ifndef NOT_REWRITE_MIC_VALUE   //axel 2004/2/14 03:19PM
    run_save_sel_cmd(AUDPAGE, MICITEM);
#endif //NOT_REWRITE_MIC_VALUE //axel 2004/2/14 03:19PM
}



int IsOSDChinese()
{
    if (setup_item[LANGPAGE][LANGITEM][osd_font_mode+2]==LCD_ZH)  return 1;
    else    return 0;
}


#ifdef DOUBLE_LOGO  //terry,2004/2/10 04:18PM
//xiaosan 2-7-19 13:36
//input :void
//ouput :1->en,0->zh
int OsdIsEnglish(void)
{
    if(setup_item[LANGPAGE][LANGITEM][osd_font_mode+2]==LCD_EN)
        return 1;
    else
        return 0;
}
#endif

// 20041222 JSLin   //this function should always exist!!
void setup_SetFreqMaskConfig()//terry,2003/12/15 11:05AM
{
#ifdef USE_FREQ_MASK
	#ifdef SPHE1000
    	exe_setup_function(STR_OS_FREQ_MASK,setup_item[AUDPAGE][1][ SETUP_FREQ_MASK ],0);
	#else
    	exe_setup_function(STR_OS_FREQ_MASK,setup_item[AUDPAGE][LPCM_ITEM][ SETUP_FREQ_MASK ],0);
	#endif
#else
    #ifdef SUPPORT_SPDIF_IN /*2005-6-6 20:14 huziqin*/
    if((system_state == SYSTEM_DOING_COAXIAL)||(system_state == SYSTEM_DOING_SPDIF))
    {
        printf("setup set FREQ_MASK_DEFAULT\n");
    }
    else
    #endif //SUPPORT_SPDIF_IN
    {
	AUDIF_Set_FrqMsk(FREQ_MASK_DEFAULT);
    }

#endif
}

void setup_SetDTSCDConfig()
{
    printf("\n\nsetup_SetDTSCDConfig in1\n");
    exe_setup_function(setup_item[AUDPAGE][DIGIOUTITEM][1],setup_item[AUDPAGE][DIGIOUTITEM][ SETUP_SPDIF ],0);
    //setup_SetDTSConfig();//terry,2004/2/10 03:51PM
    printf("\n\nsetup_SetDTSCDConfig out\n");
}

void setup_SetSPDIFConfig()//2003-8-15 20:56 for avoid SPDIF noise when power on.
{
    exe_setup_function(setup_item[AUDPAGE][DIGIOUTITEM][1],setup_item[AUDPAGE][DIGIOUTITEM][ SETUP_SPDIF ],0);

}

void setup_SetDTSDOWNMIXConfig()//NONO force set downmix 2003-11-24 14:23
{
//3-12-9 19:04 NONO MARKED.uopdate dsp code.
if(  ( (cd_type_loaded ==CDDA)&&(cd_subtype==CD_DTS) )||(coding_mode_now==AUDIF_CODING_MODE_DTS))
    exe_setup_function(setup_item[MULTISPKPAGE][AC3DOWNMIXITEM][1],
                    setup_item[MULTISPKPAGE][AC3DOWNMIXITEM][ SETUP_SPK_DOWNMIX ],0);//nono 2003-8-26 0:50
}

//check whether MIC is OFF, Jeff 20020524
int setup_IsMICOff()
{
    if ( (SETUP_MIC_ONF-1)==MICOFF) return 1;
    else return 0;
}



//Set MIC to Auto mode
void setup_SetMICAuto()
{
    SETUP_MIC_ONF = MICAUTO;
    AUDIF_Set_MICStatus(STATUS_AUTO, 0);//2004AUDDRV AudioSetMIC(2, 0); //Set MIC auto detect, 2:auto, (the second parameter:unsed now)
    run_save_sel_cmd(AUDPAGE, MICONOFFITEM);    //gerry,3-10-20 17:10
}



void setup_SetMICOff()//nono 20020707
{
    SETUP_MIC_ONF = MICOFF+1;
    AUDIF_Set_MICStatus(STATUS_OFF, 0);//2004AUDDRV AudioSetMIC(0, 0); //Set MIC Off(the second parameter:unsed now)
    run_save_sel_cmd(AUDPAGE, MICONOFFITEM);    //gerry,3-10-20 17:10
}

//wanghaoying 2003-9-15 15:15
//*****    0: mic auto
//*****    1: mic off
#ifdef DEFAULT_MIC_OFF
BYTE mic_flag=1;
#else
BYTE mic_flag=0;
#endif

void setup_MIC(BYTE set __attribute__((unused)))//nono 20020707
{
#ifndef NO_MIC //Jack added 04/07/03
    int id;
    //BYTE font[]={STR_OS_ON,STR_OS_OFF};

    if(setup_IsMICOff())
        id= STR_OS_OFF; //mic_flag=1;
    else
        id= STR_OS_ON;

    if (set) {
        if(mic_flag==1)
        {
            id= STR_OS_ON;
            mic_flag=0;
            setup_SetMICAuto();
        }
        else
        {
            id= STR_OS_OFF;
            mic_flag=1;
            setup_SetMICOff();
        }

    }

    //id = font[mic_flag];
    //PrintOsdMsg(STR_OS_MIC_ONOFF|(id<<8),REGION1,1,4);
    PrintOsdMsg(STR_OS_MIC_ONOFF|(id<<OSDSTR_ID_TOTL_BIT),REGION1,1,4);
#endif
}
/*
**wanghaoying 2003-9-11 14:12
**return value: 2--->DOWNMIXLTRT
**              3--->DOWNMIXSTEREO
**              4--->DOWNMIXVSRND
**              5--->AC3DOWNMIXOFF
*/
UINT8 setup_GetDownmixMode(void)
{
    return (SETUP_SPK_DOWNMIX);
}

#ifdef SUPPORT_PROLOGIC_II  //axel 2004/1/26 11:45
/*
**wanghaoying 2003-9-18 11:29
**return value:
**
**
*/

UINT8 setup_GetPrologicII(void)
{
    return (SETUP_PROLOGIC_II);
}
#endif

#ifdef MIC_2CHANNEL//NONO 4-1-5 12:10//FOR MUTE_EXECUTE_MIC

UINT8 setup_GetMICVol(void)
{
    return (SETUP_MIC_VOL);
}
UINT8 setup_GetMICVol2(void)
{
    return (SETUP_MIC_VOL_2);
}
#endif//MIC_2CHANNEL

//gerry add for gbm,when we set to S-VIDEO,tv dac3 will be off,2004-5-13 15:44
#if defined(S_VIDEO_OUT)&&defined(S_VIDEO_SET_TV_DAC3_OFF)
/*
** gerry,2004-5-19 15:36
**return value: 2--->S_VIDEO
*/
UINT8 setup_GetVideoMode(void)
{
    return (SETUP_VIDEO_FORMAT);
}
#endif


/*
void SetSharpness(BYTE nVal)
{
    printf("....SetSharpness = %d\n", nVal);
}
*/
// video adjustment default setting ,seanlin 2004/08/17

//#define CUSTOMER_ADJ_CURVE
//#define EXTEND_CURVE_SCALE


#define DEFAULT_CURVE1   16
#define DEFAULT_CURVE2   235

#ifdef  CUSTOMER_ADJ_CURVE
    #define ADJ_SATURATION   2
    #define ADJ_CURVE1      16
    #define ADJ_CURVE2      235

#else
    #define ADJ_SATURATION   0
    #define ADJ_CURVE1      16
    #define ADJ_CURVE2      235
#endif



#ifdef EXTEND_CURVE_SCALE
	#define CURVE_SCALE 10
#else
	#define CURVE_SCALE 5
#endif

void SetBrightness(BYTE nVal)
{
    int Src1, Src2, Dest1, Dest2;

    Src1  = DEFAULT_CURVE1 + (SETUP_CONTRAST - 8) * CURVE_SCALE;
    Dest1 = ADJ_CURVE1 + (nVal - 6) * CURVE_SCALE;
    if(Dest1<0) Dest1 =0;
    if(Src1<0) Src1 =0;


    Src2  = DEFAULT_CURVE2 - (SETUP_CONTRAST - 8) * CURVE_SCALE;
    Dest2 = ADJ_CURVE2 + (nVal - 6) * CURVE_SCALE;

    setup_vpp_curve (Src1,Dest1,Src2,Dest2);

}



void SetContrast(BYTE nVal)
{
    int Src1, Src2, Dest1, Dest2;

    Src1 = DEFAULT_CURVE1 + (nVal - 6) * CURVE_SCALE;
    Dest1 = ADJ_CURVE1 + (SETUP_BRIGHTNESS - 8) * CURVE_SCALE;
    if(Dest1<0) Dest1 =0;
    if(Src1<0) Src1 =0;
    Src2 = DEFAULT_CURVE2 - (nVal - 6) * CURVE_SCALE;
    Dest2 = ADJ_CURVE2 + (SETUP_BRIGHTNESS - 8) * CURVE_SCALE;

    setup_vpp_curve (Src1,Dest1,Src2,Dest2);


}

#ifdef IR_KEY_SET_VIDEO_MODE
void SetBrightnessAdjust(BYTE nVal, BYTE nVal2)
{
    int Src1, Src2, Dest1, Dest2;

    Src1 = DEFAULT_CURVE1 + (nVal2 - 8) * CURVE_SCALE;
    Dest1 = ADJ_CURVE1 + (nVal - 6) * CURVE_SCALE;
    if(Dest1<0) Dest1 =0;
    if(Src1<0) Src1 =0;
    Src2 = DEFAULT_CURVE2 - (nVal2 - 8) * CURVE_SCALE;
    Dest2 = ADJ_CURVE2 + (nVal - 6) * CURVE_SCALE;

    setup_vpp_curve (Src1,Dest1,Src2,Dest2);


}


void SetContrastAdjust(BYTE nVal, BYTE nVal2)
{
    int Src1, Src2, Dest1, Dest2;

    Src1 = DEFAULT_CURVE1 + (nVal - 6) * CURVE_SCALE;
    Dest1 = ADJ_CURVE1 + (nVal2 - 8) * CURVE_SCALE;
    if(Dest1<0) Dest1 =0;
    if(Src1<0) Src1 =0;

    Src2 = DEFAULT_CURVE2 - (nVal - 6) * CURVE_SCALE;
    Dest2 = ADJ_CURVE2 + (nVal2 - 8) * CURVE_SCALE;

    setup_vpp_curve (Src1,Dest1,Src2,Dest2);

}
#endif//IR_KEY_SET_VIDEO_MODE

#include <math.h>

// the accepted range are from 0 to 100

void SetHUE(BYTE nVal)
{
    static const UINT8 lookup_table[][4] = {
        //bb br rb rr
        {1, 6,  0,  0}, // 0
        {0, 5,  0,  0}, // 1
       {0, 4,  0,  0}, // 2
        {0, 3,  0,  0}, // 3
        {0, 2,  0,  0}, // 4
        {0, 1,  0,  0}, // 5
        {0, 0,  0,  0}, // 6
        {0, 0,  1,  0}, // 7
        {0, 0,  2,  0}, // 8
        {0, 0,  3,  0}, // 9
        {0, 0,  4,  0}, // 10
        {0, 0,  5,  0}, // 11
        {0, 0,  6,  1}, // 12
    };

    if (nVal>12) nVal=6;
    setup_osd_hue (
        lookup_table[nVal][0],  // bb
        lookup_table[nVal][1],  // br
        lookup_table[nVal][3],  // rr
        lookup_table[nVal][2]   // rb
    );

    //printf("....SetHUE = %d\n", nVal);
}



void SetSaturation(BYTE nVal)
{
    // the input value is from (0,0,0) to (7,7,0)
    // here uses (0,0,0), (1,1,0), (2,2,0), (3,3,0), (4,4,0), (5,5,0), (6,6,0),
    // (7,2,0), (7,3,0), (7,4,0), (7,5,0), (7,6,0), (7,7,0),
    nVal += ADJ_SATURATION ;

    setup_osd_chroma(nVal, 0, 0);

    //printf("....SetSaturation = %d\n", nVal);
}


#ifdef DIP_CFG_ENABLE
void SetDeInterlace(BYTE nVal)
{
    if(nVal <= 6)
        dip_sel = nVal;

    if( (dip_sel == 0)||(cd_type_loaded!=CDDVD) )
        dip_enable = 0;
    else
        dip_enable = 1;

    //printf("....dip_sel = %d\n", dip_sel);
    //printf("....dip_enable = %d\n", dip_enable);
}
#endif //#ifdef DIP_CFG_ENABLE


#ifndef DVD_3D_SHOW_SPECTRUM  //terry,2004/2/10 04:58PM
void setup_DVD3DSound(BYTE set)
{
    BYTE newsel, newid;

    newsel = SETUP_SPK_DOWNMIX;
    newid = ITEM_SPK_DOWNMIX[newsel]; //Jeff 20020604

    if (set) {
        AUDIF_Set_Pause();//2004AUDDRV AudioSetPause(); //Jeff 20020605
        //delay_1ms(100);

#ifdef NEW_SEARCH_OSD
        if(key_up_down == 1)
        {
            newsel++;
        }
        else if(key_up_down == 0)
        {
            newsel--;
        }
#else
        newsel++;
#endif

#ifdef NEW_SEARCH_OSD
        if (newsel > AC3DOWNMIXOFF) newsel=SPKSTART;
        if (newsel < SPKSTART) newsel=AC3DOWNMIXOFF;
#elif defined(VTREK_DVD)        //wanghaoying 2003-9-20 18:55
        if (newsel < DOWNMIXSTEREO)
            newsel = DOWNMIXSTEREO;
        else if ((newsel > DOWNMIXSTEREO)&&(newsel < AC3DOWNMIXOFF))
            newsel = AC3DOWNMIXOFF;
        else if (newsel > AC3DOWNMIXOFF)
            newsel = DOWNMIXSTEREO;
#else
        if (newsel > AC3DOWNMIXOFF) newsel=2;
#endif

        SETUP_SPK_DOWNMIX = newsel;
        newid = ITEM_SPK_DOWNMIX[newsel]; //Jeff 20020604

        //to run speaker setup downmix mode
        exe_setup_function( ITEM_SPK_DOWNMIX[1], newid, 0);
        AUDIF_Set_Play();//2004AUDDRV AudioSetPlay(); //Jeff 20020605

#ifdef NEW_SEARCH_OSD
        sound_type = newid;
#endif
    }
    //PrintOsdMsg(STR_OS_SURR|(newid<<8),REGION1,1,4);
    PrintOsdMsg(STR_OS_SURR|(newid<<OSDSTR_ID_TOTL_BIT),REGION1,1,4);
}
#endif

#endif

#ifdef USE_IR_TO_CHANGE_TVTYPE
void setup_DVD_TVType(BYTE set)
{
    BYTE newsel, newid;

    newsel = SETUP_TV_TYPE;
    newid = ITEM_TV_TYPE[newsel]; //Jeff 20020604

    if (set) {

        newsel++;

        if (newsel > 4) newsel=2;

        SETUP_TV_TYPE = newsel;
        newid = ITEM_TV_TYPE[newsel]; //Jeff 20020604

        //to run speaker setup downmix mode
        exe_setup_function( ITEM_TV_TYPE[1], newid, 0);

     ExitSetupPage(1);   //nono 20031213
     if( 0 )//NP_P_CFG_for_Video != UserSet.P_V_CFG)
    {
        if(cd_type_loaded==CDDVD)
        {

            osd_disable();
            set_video_aspect();

            if( is_aspect_menu()== 0x02 )
            {
            osd_init();
            delay_srv_10ms(10);
            rep_run_the_menu();
            }
        }
    }


    }
    //PrintOsdMsg(STR_OS_SURR|(newid<<8),REGION1,1,4);
    PrintOsdMsg(STR_OS_TV_RATIO|(newid<<OSDSTR_ID_TOTL_BIT),REGION1,1,4);

    run_save_sel_cmd(SYSPAGE,2);
}
#endif//USE_IR_TO_CHANGE_TVTYPE

#ifdef AUTO_PLAY
BYTE auto_play_on()
{
    BYTE res;

    res = SETUP_SSAVER;
    if (res < 2) res=2;

    if (res==2) {
        res = 1;
    } else {
        res = 0;
    }

    return res;
}
#endif
#ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU    //linrc add 2004-11-4 17:31
extern BYTE CDG_IsCDGNow();                 //when "MNP" what define in setupmenu is on
BYTE VcdControlFlag()                       //VCD & CDG play one TRK in one time....
{
    BYTE res;

    res = SETUP_SSAVER;
    if (res < 2) res=2;

    if (res==2)
    {
        if((cd_type_loaded==CDVCD10)||(cd_type_loaded==CDVCD20)
		        ||(cd_type_loaded==CDSVCD)
		        #ifdef SUPPORT_CDG
		        ||(CDG_IsCDGNow())
		        #endif
		        )
                res = 1;
          else res = 0;
    } else {
        res = 0;
    }

    return res;
}
#endif

#ifdef  VGA_CTRL_FORMAT
int setup_IsVGAOn() //wangfeng,2003-10-23 13:15
{
    int iRes=0;
    if ((id==STR_OS_TV_SYS)&&(tv_out_id==PC_VGA)) iRes=1;
    return iRes;
}
#endif

#ifdef  KARAOKE_MENU
void setup_KARAOKE()
{
#ifdef NEW_STYLE_SETUP
    GBM_run_setupmenu_flag =1;
#endif
    if(KARAOKE_MENU_FLAG)
    KARAOKE_MENU_FLAG=0;

    else{
    full_scrn=SETUP;
    KARAOKE_MENU_FLAG=1;
    osd_init_setup();

    setupLevel=1;//2;
    page = AUDPAGE;

    index_y=MICONOFFITEM;//PASSWDITEM;
    index_y_start=0;

    index_y2=0;
    submenuStart=MICONOFFITEM+2;//PASSWDITEM+2;

    ShowSetupPage(2);

    }

}
#endif

#ifdef  SUPPORT_PROLOGIC_II
int setup_IsPrologicOn()    //wangfeng,2003-10-23 13:15
{
    int iRes=0;
    if (SETUP_PROLOGIC_II!=PROLOGIC_OFF) iRes=1;
    return iRes;
}

/*
 * turn OFF PROLOGIC II
 * zhaoyanhua 2004-2-11 13:48
 */
 void setup_OffPrologic_II(void)
 {
#define PROLOGIC_OFF 4

    printf("#### hehehehehehehhehehhe-----PRGLOCOG ---\n");
    exe_setup_function(STR_OS_PROLOGIC,STR_OS_OFF,0);
    SETUP_PROLOGIC_II = PROLOGIC_OFF;
 }
#endif

//Maoyong 2004.05.19 for record password input state, used in ir_parser.c now
BYTE setup_IsSettingPassword(void)
{
    if( (full_scrn & SETUP) && (setup_item[page][index_y][1] == STR_OS_PASSWORD) )
        return 1;
    else
        return 0;
}

#ifdef SHOW_STANDBY_TIMER     //suqiaoli add 2003-8-2
void polling_setup_standby_timer(void)
{
    if((setup_item[page][index_y][1]==STR_OS_VFD_TIME)&&(setupLevel==1))
    {
        psprintf(linebuf, "%02d:%02d:%02d",show_standby_hour, show_standby_min, show_standby_sec);
        osd_DrawString(SETUP_SUB_XSTART+1,STANDBY_TIMER_ITEM+index_y, linebuf, SDEFAULTCOLOR,SBGCOLOR);

    }

    if (setup_item[page][index_y][1]==STR_OS_VFD_TIME)
        flag_standby_timer=1;
    else
        flag_standby_timer=0;
}
#endif

#ifdef CORTROL_VCD_ONF
int setup_IsVCD_OFF() //wangap add 2005/5/27
{
 if ( (SETUP_CUSTM_VCD_ONF)==3) return 1;
    else return 0;
}
#endif

#ifdef SUPPORT_SPI_QSI
//for spi cmd to setup ssaver uOnOff = 0: on, 1: off
void setup_SPI_ssaver_onoff(UINT32 uOnOff)
{
    if(uOnOff==0)//on
    SETUP_SSAVER = MIN_ITEM_SEL + uOnOff;
    else//off
    SETUP_SSAVER = MIN_ITEM_SEL + 4;

    run_save_sel_cmd(SYSPAGE,SSAVERITEM);
}

void custm_SPI_region_setting(UINT32 uRegion)
{
    UINT8 uID;

    UserSet.P_RCD = uRegion;
    //printf("-=-=-=-=-=--=-=-reg=%d UID=%d\n",uRegion,UserSet.P_RCD);
    SETUP_CUSTM_REGION = uRegion + 2; //setup item update
    run_save_total_userSet();   //save user set update
    uID = setup_item[CUSTMPAGEINDEX][2][SETUP_CUSTM_REGION];
    //PrintOsdMsg(uID, REGION1, 1, 0);
}
#endif

#ifdef  TEST_BASS_MANAGEMENT
UINT16 SetBassConfig()
{
    UINT16 bass_config;
    int front,center,surround,sub;

    front = SETUP_SPK_FRONT-2;
    center = SETUP_SPK_CENTER-2;
    surround = SETUP_SPK_SURROUND-2;
    sub = SETUP_SPK_SUBWOOFER-2;
    bass_config = 0;

    printf("test : front=%d,center=%d,surround=%d,sub=%d\n",front,center,surround,sub);

    //mapping table
    switch (front)
    {
        case 0:  //Front Large
            if (surround==0) //Surround Large
            {
                if ((sub==0)||((sub==1)&&(center==1)))
                    bass_config = 3; //config3
                else
                    bass_config = 0; //x
            }
            else if(surround==2) //Surround None
            {
                if (center==1) //Center Small
                    bass_config = 2; //simplified
                else //Center Large or None
                    bass_config = 0; //x
            }
            else    //Surround Small
            {
                bass_config = 2; //simplified
            }
            break;
        case 1:  //Front Small
            if (surround==0) //Surround Large
                bass_config = 4; //car-simplified
            else
                bass_config = 1; //config1;
            break;
    }
    bass_config = 0x00ffff & ((front<<12)+(center<<8)+(surround<<4)+bass_config);
    printf ("test : return bass_config = %x,%d\n",bass_config,bass_config);
    return bass_config;
}
#endif  //TEST_BASS_MANAGEMENT


#ifdef SELECT_MEDIA_IN_SETUPMENU    //Maoyong 2004-8-9 18:12
void setupSettingMediaItem(void)
{
    if(media_type == MEDIA_CD)
        SETUP_MEDIA_TYPE = DISC_ITEM + 2;
    else if(storage_type == USB_DEVICE)
        SETUP_MEDIA_TYPE = USB_ITEM + 2;
    else
        SETUP_MEDIA_TYPE = CARD_ITEM + 2;
    //run_save_sel_cmd(SYSPAGE, ITEM_MEDIA_TYPE);
}
#endif


