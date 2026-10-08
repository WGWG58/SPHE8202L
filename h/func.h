#ifndef __FUNC_H
#define __FUNC_H

#include "user_init.h"
#include "types.h"
#include "endian.h"
#include "stdlib.h"

#include "sio.h"
#include "epp.h"

/************************************************************\
polling.c head file
\************************************************************/
#include "polling.h"
/************************************************************\
kenny define for IOP Device address and High sub address
\************************************************************/
#define IOP_DEVICE_ADDR(da)             (((da&0x78)<<1)&0xf0)//load Device address for IOP
#define IOP_HIGH_SUB_ADDR(sa)           (UINT32)((sa&0x07)<<8)//load High sub address(A8~A10) for IOP
#define IOP_CONFIG_PDVD     0xF0;       //jhuang pdvd 2003/12/2
/************************************************************\
psd.c v11.c fs9660.c svcd.c head file
\************************************************************/
UINT32  psd_callback_check(UINT32 func);
UINT32  dvd_callback_check(UINT32 func);
UINT32  fs_callback_check(UINT32 func);
int psd_getlist(int ListID);
int psd_navigation(void);
int v11_navigation(void);
int read_iso9660(void);
int check_cdtype(void);
void Chg2PlayMd(void) ;
UINT8 ReadFile(int *);
#ifdef SUPPORT_MULTI_PARTITION
int HddCardBrowse(void);
#endif
/************************************************************\
gpio.c head file
\************************************************************/
void    reset_gpio(void);
/************************************************************\
ir.c head file
\************************************************************/
void    reset_ir(void);
BYTE    polling_ir(void);
int reverse_fun(int rx);
#ifdef SPHE1000_DVDSTATE_CALLBACK
/************************************************************\
SPHE1000_DVDSTATE_CALLBACK head file
\************************************************************/
inline void osdisp_status(BYTE osdisp_state,BYTE osdisp_ir);        //wjzhang
#endif
/************************************************************\
osd1.c head file
\************************************************************/
#ifdef NEW_OSD_DRIVER

#include "osd_AppAPI.h"

#else	//#ifdef NEW_OSD_DRIVER

inline void osd_enable(void);
inline void osd_disable(void);
inline void polling_osd(int);

void    reset_osd(void);
void    osd_init(void);
void    osd_tog_region(BYTE, int MODE);
void    osd_init_music(void);
UINT8   *get_lang_name(int);
UINT8   *get_audio_mode();
void    osdshow(UINT8 r,char *buf);

#ifdef NODISC_SHOW_IN_DIFF_REGION
void nodisc_osd_init(void);
#endif

typedef struct {
    UINT8 xst, yst;
    UINT8 *str;
} t_osd_str;

void    osd_DrawString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor);
void    osd_DrawStrings(const t_osd_str *p, BYTE fg, BYTE bg);

#ifdef SOFT_MENU//Modifed by ChenZhao on 2004-9-7 11:24 WP
void    osd_DrawString_ori(UINT32 xStart, UINT32 yStart, const BYTE *str, BYTE fontColor, BYTE bkColor);//Modifed by ChenZhao on 2004-9-7 11:24 WP
#else
void    osd_DrawString_ori(BYTE xStart, UINT32 yStart, const BYTE *str, BYTE fontColor, BYTE bkColor);//nono 2004-4-12 1:02
#endif//SOFT_MENU

#ifdef SETUPMENU_16Mb_NO_ICON
void osd_DrawSetupIconString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor);
#endif

#define OSD_OnOffRegion(m,r) osd_tog_region(r,m)

void    wait_v_blank(void);
void    DispPolling(BYTE bReset);
BYTE    bin2asc(BYTE pp);
void    PrintOsdMsg(UINT32 id,UINT8 r,int t,BYTE m);
void    ClearOsdMsg(int i);
void    OsdRegionOff(BYTE r);
//void    PrintOsdMsg2(BYTE r, int t);
void    osd_replace_rect_color(BYTE bkColor, BYTE destColor);
void    SetOsdCol(UINT8 rb,UINT8 re,UINT8 id,UINT32 color);

#endif	//#ifdef NEW_OSD_DRIVER
/************************************************************\
osdutil.c head file
\************************************************************/
#define AudKey_Font_ID          0x01
#define Volume_Font_ID          0x02
#define Echo_Font_ID            0x03
#define Score_Font_ID           0x04
#define Mic_Font_ID             0x05
#if defined(Ti3001_OSD_UI_1)||defined(Ti5026_OSD_UI_1)
//#define VOL_BALANCE_ID          0x06
#define VOL_TREBLE_ID           0x07
#define VOL_BASS_ID             0x08
#define VOL_DRC_ID              0x09
#define AMP_F_VOL_ID            0x0a   // FRONT VOLUME
#define AMP_F_BAL_ID            0x0b   // FRONT BALANCE
#define AMP_S_VOL_ID            0x0c   // surround volume
#define AMP_S_BAL_ID            0x0d   // surround BALANCE
#define AMP_C_VOL_ID            0x0e   // center volume
#define AMP_SW_VOL_ID           0x0f   // subwoofer volume
#endif

#define VOL_FL_ID               0x10
#define VOL_FR_ID               0x11
#define VOL_SL_ID               0x12
#define VOL_SR_ID               0x13
#define VOL_C_ID                0x14
#define VOL_SW_ID               0x15    //Jeff 20031028

#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-2-10 17:50
#define VIDEO_BIGHT_ID          0x16
#define VIDEO_CONTRAST_ID       0x17
#define VIDEO_HUE_ID            0x18
#define VIDEO_SATURATION_ID     0x19
#define VIDEO_DEINTERLACE_ID    0x20
#endif//ifdef VIDEO_SETUP_NEW_GUI
    
#if defined(SUPPORT_FUNCTION_MENU)||defined(BRIGHTNESS_COLOR_KEY)
#define BRIGHTNESS_PLUS_ID          0x21
#endif   

#ifdef BRIGHTNESS_COLOR_KEY 
#define COLOR_PLUS_ID           0x22
#endif

#ifdef MP4_SHOW_PARSING_PROGRESS
#define SHOW_LEVEL_NO_ID        0x23
#endif  //MP4_SHOW_PARSING_PROGRESS

//freyman add 2002-9-10 20:22 and mark 2004-3-23 16:04
//#ifdef SVA_SAMPLE
//#define AMP_VOL_ID              0x06
//#endif

/************************************************************\
search.c head file
\************************************************************/
void vcd_mode_search(BYTE,BYTE,BYTE);
void dvd_search(BYTE,BYTE );//kenny add it 2001/5/8
//void vcd_search(BYTE, BYTE ,BYTE,BYTE );//kenny add it 2001/5/8
void show_search(BYTE, BYTE ,BYTE,BYTE );//kenny add it 2001/5/8
void search_func_input(void); //kenny 2001/5/16
void search_func_up(void);
void search_func_down(void);
void search_func_left(void);
void search_func_right(void);
void search_func_clear(void);
void search_func_select(void);

void show_level(int ,INT8 ,BYTE);
int atapi_open_tray(void);
int atapi_close_tray(UINT8); // for normal close tray, we use 0 as parameter;
                             // for close tray before standby mode, we use 1.
//search.c
void pbcoff_init(void);

/*
**
*/
void    MediaMainLoop(void);
void    restart_audio_engine(void);
void    resync_audio_engine(void);



/************************************************************\
setup.c head file
\************************************************************/
void read_setup_select(void);
void Showdirpicture(UINT8 mode);
void ShowSetupSel(UINT8 mode);
void TestOsdFonts(void);
void ShowSetupPage(BYTE refresh);
void setup_func_down(void);
void setup_func_up(void);
void setup_func_left(void);
void setup_func_right(void);
void run_save_cmd(void);
void setup_func_prepage(void);
void setup_func_nextpage(void);
void setup_func_select(void);
void setup_password(void);
void show_password(BYTE num);

/************************************************************\
opui.c head file//libing
\************************************************************/
#ifdef OP_PLAYMODE
void show_op_menu(void);
void op_func_up(void);
void op_func_down(void);
void op_func_select(void);
void op_func_left(void);
void op_func_right(void);
#endif
#ifdef ORITRON_TRAY_PASSWORD
void tray_pwd_left(void);
void tray_pwd_right(void);
void tray_pwd_select(void);
#endif
#ifdef SUPPORT_OP_REGION_UI
void Show_Oritron_Region_UI(void);
void Region_Func_Left(void);
void Region_Func_Right(void);
void Region_Func_Select(void);
void Dislay_Op_Region_ui(void);
#endif
/******************************************************
end
******************************************************/

void custm_setup_menu(void);//jhuang
void read_custm_setup_select(void);//jhuang
void startup_vpp(void);
void ExitSetupPage(BYTE save);
#ifdef KONKA_DVD//20020904
void setup_func_clear(void);    //konka clead
#endif

#ifdef SUPPORT_FUNCTION_MENU
void ShowSetupPage_plus(BYTE refresh);
#endif 
#ifdef SUPPORT_DISPLAY_MENU
void exe_display_function(BYTE RightKey);
void polling_display_menu_plus(void);
#endif//end #ifdef SUPPORT_DISPLAY_MENU

/************************************************************\
  Prog.c head file
\************************************************************/
void prog_func_clear(void);
void prog_show_play(void);
void prog_func_select(void);
void prog_func_play(void);
void prog_func_input(UINT8 num);
void ShowProgSel(UINT8 mode);
void ShowProgPage(void);
void prog_func_down(void);
void prog_func_up(void);
void prog_func_left(void);
void prog_func_right(void);
void prog_func_off(void);
BYTE prog_next(void);
BYTE prog_prev(void);

//void prog_next(void);
//void prog_prev(void);
int is_clear_pos(void);//2002-4-19 1:53

/************************************************************\
 safe.c head file
\************************************************************/
void safe_srn_off(void);
void safe_srn_on(void);
void ChgColor(int c);
void MoveBox(UINT16 s_x,UINT16 size,UINT16 d_x);
void safe_srn_forceOFF(void);
/************************************************************\
 book.c head file
\************************************************************/
void book_cancel(void);
void book_func_up(void);
void book_func_down(void);
void book_func_select(void);
void book_func_clear(void);
void book_func_play(void);
void book_func_number(void);
void show_book_tt(BYTE );
void mark_func_right(void);
void mark_func_left(void);
/************************************************************\
 read.c head file
\************************************************************/
void ShowReadPage(void);
void read_func_left(void);
void read_func_right(void);
void read_func_down(void);
void read_func_input(void);
void read_func_up(void);
void read_func_select(void);
/************************************************************\
 sound.c head file
\************************************************************/
//void ShowSoundSel(void);
void init_sound(void);
void ShowSoundPage(void);
void sound_func_down(void);
void sound_func_input(UINT8 num);
void sound_func_up(void);
void sound_func_select(void);
void sound_func_right(void);
void sound_func_left(void);
void sound_draw_key(UINT8, UINT8);

/************************************************************\
 browse_func.c head file
\************************************************************/

#ifdef NEWSTYLE_WINDOW
void browse_func_up(void);
void browse_func_down(void);
void browse_func_left(void);
void browse_func_right(void);
void browse_func_select(void);
void exe_browse_func(void);
void UpdateTT_CHP_info(void);
void browse_func_input(void);

//void exe_browse_func(BYTE item_index,BYTE loc_index,BYTE fontColor,BYTE bkColor);
//void browse_DrawLeftItem_HL(BYTE index,BYTE pre_bkColor,BYTE bkColor);
#endif


/************************************************************\
 virtual_keyboard.c head file
\************************************************************/
#ifdef VIRTUAL_KEYBOARD // alan, 2003/8/16 05:32AM
void virtual_keyboard_up();//WSLEE add up and down function 20050518 20:00
void virtual_keyboard_down();
void virtual_keyboard_left();
void virtual_keyboard_right();
void virtual_keyboard_select();
#endif

/************************************************************\
 double_title.c head file
\************************************************************/
#ifdef DOUBLE_TITLE//susu 2003-8-26 13:54
void double_title_func_up(void);
void double_title_func_down(void);
void double_title_func_left(void);
void double_title_func_right(void);
void double_title_func_select(void);
void exe_double_title(void);
#endif

//freyman add 2002-9-6 17:13 and mark 2004-3-23 16:04
/*#ifdef SVA_SAMPLE
//void osd_init_ampvol(void);
void ampvol_func(void);
void ampvol_init(void);
void ampvol_func_down(void);
void ampvol_func_up(void);
void ampvol_func_right(void);
void ampvol_func_left(void);
void ampvol_exit(void);
#endif*/


#ifdef SUPPORT_APOGEE_AMP //xyy 2003-9-17 9:50
void ddx_ampvol_func_left(void);
void ddx_ampvol_func_right(void);
void ddx_ampvol_func_up(void);
void ddx_ampvol_func_down(void);
#endif


//I2C function declare
//void    WriteI2c(int,int,int,int);
int WriteToI2c(int,int,BYTE *,int);
int ReadFromI2c(int,int,BYTE *,int);
void    CheckI2c(void);         /*jhuang 2001/7/15 07:55PM*/
#ifdef I2C_PAGE_MODE//chenzhao20050606
int WriteToI2cPageMode(int iDeviceAddr,int iAddr,BYTE *bData,int len);
int ReadFromI2cPageMode(int iDeviceAddr,int iAddr,BYTE *bData,int len);
#endif

//sysmain2.c
void system_stop(void);
void system_play(void);

//sysmain2.c
void delay_srv_10ms(int tms);

int atapi_read_toc(void);
int atapi_abort_play(void);
//UINT8 get_cd_type_osd_id(void);
UINT8 is_user_opened(void);
UINT8 is_test_unit(void);//2001/10/23
//navif.c
UINT8 ExeHLBm(UINT8 mode,int val);

//vpp.c
void setVPP_OffsetMode(int mode);

// other.S
void    delay_1us(unsigned);
void    delay_1ms(unsigned);
void    delay(unsigned);

//mpegsys.c
void    setup_vcd_motion_pal(void);
void    setup_vcd_motion_ntsc(void);

//audif.c
//void dac_set_fs(BYTE fs);

//util.c
UINT32 get_next_trk_msf(UINT8 trk);
BYTE show_trk_num(BYTE trk);

/************************************************************\
 ircmd.c head file
\************************************************************/
void    get_cdkit_time(BYTE flag);
void    ShowRepInfo(void);
int     is_dvd_menu(void);
void    ir_num_select(int x);
void    init_ir_num(void);
void    show_repeatAB(int t);
void    show_zoom(int t);
void    show_angle_osd(void);
void    ircmd_post_func(UINT32 );
void    show_time(void);

#ifdef CONTINUOUS_NUM_KEY_SELECT
void ir_continuous_num_clr(void);
#endif

//auddac.c
void mic_mute();

//cdfunc.c
void make_toc_tab(UINT32 msf);

#endif/*__FUNC_H*/

//disp.c
UINT8 *get_audio_mode(void);



//avb_if.c
int avbGetStatus(void);
void avbCloseTray(void);
void avbOpenTray(void);
void avbAbortPlay(void);
void avbGetTOC(UINT8 , UINT8 );


//hostx
void ClearServoCacheBuffer(void) __WEAK;
void hostx_servo_buf_init(void) __WEAK;
//card reader
int srv_cardfile(void);
// srv
int srv_cd(void);
int srv_cdda(void);
int srv_cdmp3(void);
int srv_rom(void);

//iop.c
int WriteI2c(int iDeviceAddr,int iAddr,int iData,int iLen);

//ircmd_util.c
void setup_tv_out(UINT8 id);

int dsp3_decompress(const BYTE*, BYTE*);

//init0.s
void invalidate_dcache(void);

//emu.c
void setup_emu(void);

//idemain.c
void ServoDecMainLoop(void);

//osd1.c
void draw_osd_board(UINT8 r,UINT8 board_type);
void osd_DrawIcon(int xStart, int yStart, unsigned index, unsigned page);
const BYTE *get_font_entry(int tbl, int entry);

//2004AUDDRV the following APIs were move to audio driver related files
#if 0
//audif.c
void    audif_set_sample_rate(int smp_rate);
void    audif_set_smp_rate(UINT32 freq);
void    DSPReset();
int     audif_auto_download_codec(UINT8 chn);
void    audif_set_coding_mode(int coding_mode);
void    audif_set_channel(int chn);
UINT16  audif_set_frequency_mask(UINT16 mask);
UINT16  audif_get_frequency_mask();
#endif

//setup.c
void draw_3rd_menu();

//sp8200tv.c
void setup_osd_chroma(unsigned amp1, unsigned amp2, unsigned amp3);
void setup_osd_hue (unsigned Cb_b_phase, unsigned Cb_r_phase, unsigned Cr_r_phase, unsigned Cr_b_phase);
void setup_vpp_curve (int Src1, int Dest1, int Src2, int Dest2);
void setup_tv_luma_scaling (BYTE nVal);

//dvd navigation
UINT8 Track_Play(UINT8, UINT8);
void set_disbuf(int);
void ATS_Load_ASV_PBIT(UINT8, UINT8);
void load_ASVU_to_mem(UINT8 ASVU_N, UINT8 ASVN, UINT8 load);

//sysmain_inc.h
void LoadModual(UINT16 iModuleIndex);


/************************************************************\
 vfd.c file
\************************************************************/
#ifdef GPIO_KEY_LIGHT
void check_gpio_keylight_status(void);
    #if defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ)
    void check_hj_keylight_status(void);
    #elif defined(USE_VFDPORT_TO_KEYLIGHT_GBM)
void check_gbm_keylight_status(void);
    #elif defined(USE_VFDPORT_TO_KEYLIGHT_MINTON)//wanghaoying 2003-8-19 20:02
    void check_minton_keylight_status(void);
    #elif defined(USE_VFDPORT_TO_KEYLIGHT_IDALL)
    void check_idall_keylight_status(void);
    #elif defined(USE_VFDPORT_TO_KEYLIGHT_THAKRAL)
    void check_thakral_keylight_status(void);
    #elif defined(VFD_GPIO_KEY)
    void check_syber_key_status(void);    
    #elif defined(HANYANG_SCAN_KEY)
    void check_hanyang_keylight_status(void);  //caoh 2004-4-19 11:30   
    #elif defined(NINTAUS_612_SCAN_KEY)         //linrc add 2004-6-8 9:21
    void vfdIO_scan_6key(void);   
#endif
#endif
/************************************************************\
periphGUI.c header file
\************************************************************/
#if defined(CF_CARD_WRITE)||defined(FAT_Write_UI)//||defined(WRITE_USB)
void switch_left();
void switch_right();
void switch_down();
void switch_up();
void switch_select();
#endif
/************************************************************\
switch cd/card/usb
\************************************************************/
#ifdef SWITCH_CD_CARD_USB
void switch_gui_up(void);
void switch_gui_down(void);
void switch_gui_select(void);
#endif

//full scrn ircmd function pointer for UP/Down/Left/Right/Select, please use SetFullscrnCmdFuncPtr
//to set your function pointers.
void SetFullscrnCmdFuncPtr( void (*up), void (*down), void (*left), void (*right),void (*sel));
void (*ircmd_full_scrn_up)();
void (*ircmd_full_scrn_down)();
void (*ircmd_full_scrn_left)();
void (*ircmd_full_scrn_right)();
void (*ircmd_full_scrn_select)();

//Jeff 20041025
#ifdef SPHE1000_DVDSTATE_CALLBACK
//only valid when you define SPHE1000
#define OSD1000ISP_STATUS(stat, ir)     osdisp_status(stat, ir)
#else
#define OSD1000ISP_STATUS(stat, ir)     do{}while(0)
#endif //SPHE1000_DVDSTATE_CALLBACK

#ifdef SUPPORT_DSPMUTE //kenny 2005/4/21

void count_dsp_mute_flag(void);
int get_dsp_mute_flag_count(void);
void set_dsp_mute_flag_count(int i);
void reset_mute_flag(void);
#endif

//#ifdef AV_IN_THROUGH_EXT_ADC
void enable_video_DAC_out(BYTE enable_disable);
//#endif


#ifdef RIPPING_MODE_SELECT //qinhua,add 2006-5-30 11:01ÏÂÎç
void rip_func_down(void);
void rip_func_up(void);	
void rip_func_select(void);
void show_rip_gui(void);
void rip_func_exit(void);
void Show_Rip_Step(void);
void Show_Rip_Step_GUI(void);
#endif 


