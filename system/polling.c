/*
** FILE
** polling.c
**
** DESCRIPTION
** polling hardware response.
**
**
** HISTORY     terry, maintain
**             2003.03.07    reduce stack by inline function
**
**/
#include "config.h"
#include "global.h"
#include "memmap.h"
#include "memmap0.h"
#include "avd.h"
#include "util.h"
#include "stc.h"
#include "audio.h"
#include "cd.h"
#include "cddsp.h"
#include "ringbuf.h"
#include "sig.h"
#include "user_init.h"
#include "vfdfunc.h"
#include "func.h"
#include "cfont.h"
#include "osd.h"
#include "macro.h"
#include "dsp3_if.h"
#include "ircmd.h"
#include "kernel.h"
#include "fs96602.h"
#include "fs.h"
#include "nav.h"
#include "polling.h"
#include "fsnav.h"
#include "kinf.h"
#include "pinf.h"
#include "gpio.h"
#include "timer.h"
#include "ircode.h"//terry 20030822
#include "avi_if.h"
#ifdef USE_FSGUI_TO_PLAY_CD//frank.huang add 051018
#include "FSGUI.h"
	#ifdef FS_BMP_GUI
	#include "fsGUI_BmpUI.h"
	#endif
#endif

#ifdef SUPPORT_TOUCH_PANEL
      #include "touch_panel.h"
#endif
#ifdef MUSTEK_LCD_DRIVE_BITEK//QiaoHuilin:2005-9-1
//#include "lcd\menu.h"
extern void TimingClearLCDMessage(void);
#endif
#ifdef MUSTEK_K100D_MODEL//by justin 2005/09/30
int  IunTestPin84=0;
#endif

#ifdef TTE_HOST_DVD
#include "pca9564.c" //lijd for TTE PCA9564 2004-11-11 19:56
#endif

#ifdef UART_WITHOUT_DEBUG_MODE
#include "io_uart0.h"
#include "UartComm.h"
#endif

#ifdef UART_SWAP //axel swap uart0 and uar1 2004/10/29
#include "io_uart1.h"
#include "UartComm.h"
#endif

#ifdef GPS_DVD 
#include "io_uart0.h"
extern void polling_GPS_DVD(void);
#endif

#ifdef QSI_PLATFORM //qsi: merge by johnson 20040712
#include "drv.h"
//sharon
#endif

#ifdef SUPPORT_MIDI
#include "fsmidi.h"
    #ifdef SUPPORT_MIDI_MENU_SEL  //by dtb in 20040225
    #include "fsMidiUI.h"
    #endif
#endif

#if(defined(SUPPORT_ID3) || defined(SUPPORT_OSDID3))
#include "fs_show.h"
#endif

#if defined(RADIO_2006) //huziqin 2006-4-19
#include "radio.h"
#endif

#ifdef SUPPORT_UART_UPGRADE
#include "UartComm.h"
#endif

#ifdef SUPPORT_EXTERNAL_MIC
#include "gpio.h"
#endif

#ifdef  SUPPORT_MP4_SUBTITLE
#include "Subtitle.h"
#endif

#ifdef SUPPORT_REP_READ
#include "read.h"
#endif

#ifdef PROVIEW_GPIO_KEY     //BRUCE ADD 2003/2/14 12:20PM
#include ".\\Customers\\Conser\\proviewkey.c"
#endif

#ifdef  SUPPORT_SPI
#include "spi.h"
#endif

#ifdef SUPPORT_DISPLAY_MENU
#include "setup_def.h"
#endif

#ifdef DISPLAY_CD_TEXT
#include "CDTextUtil.h"
#endif

//for support SWD //jslin   //20041022
#ifdef SUPPORT_PS2
#include "polling_PS2.c"
#endif

#ifdef SUPPORT_MP3_ENCODER
#include "cardfs.h"
extern void fs_mp3_encoder_main(void);
#endif
#ifdef SUPPORT_8202_DVB
#include "..\dvb_h\Sp_dtv.h"
#include "..\dvb_h\dvb_func.h"
extern int get_total_number_channel(void);
extern void DVB_polling_1s(void);
extern void DVB_polling_100ms(void);
extern void DVB_polling_500ms(void);
extern void DVB_polling_1s();
extern void DVB_polling_10ms();
#endif

#ifdef SPHE1000
void peek_message(BYTE*);
int polling_audbuf(void);
#endif

#ifdef SUPPORT_UPGRADE_WHEN_RUNNING
#include "polling_upgrade.c"
extern void polling_upgrade_info();
#endif
#ifdef SUPPORT_PLAY_SWD
extern void polling_SWD(void);
#endif

#ifdef SUPPORT_PLAY_SWD//liweihua 2005-4-18
extern void polling_swd_timer(void);
#endif

#ifdef HDMI
//==========================kevin add for HDMI
//extern void   HDCP_polling(void);
#include "HDMI_API.h"
//=============================================================
#endif

#ifdef SUPPORT_RECEIVER  //chenzhao20050718
#include "amp_gui.h"
#endif
#ifdef MULTIDISC_LOADER//chenzhao20060112
    #include "multidisc_loader.h"
#endif
#ifdef SUPPORT_SETUP_POPUP_TESTSPK_GUI//chenzhao20060114
#include "TestSpk.h"
#endif
#if defined(SPDIFIN_AVIN_IN_ONE_MODE) && defined(SUPPORT_VFD_MENU)//chenzhao20060118
    #include ".\\Customers\\oritron\\vfd_setmenu.h"
#endif    
#if defined(SUPPORT_SPDIF_IN) || defined(SUPPORT_COAXIAL_IN)
    #include "audif.h"
#endif    

//Simon Lai, new FS
#include "fs_device.h"

//=====================================================
//* debug option
//=====================================================
#ifndef DVDRELEASE
//#define POLLING_DBG     1
#endif
 
#ifdef  POLLING_DBG
//#define MONE_TIMEOUT
//#define MONE_TIMEOUT_SRC
//#define MONE_DSP24
#endif

#ifndef POLLING_DBG
#undef printf
#undef print_block
#define printf(f, a...) do {} while (0)
#define print_block(x,y) do {} while (0)
#endif

#ifdef TTE_HOST_DVD  //lijd for TTE PCA9564 2004-11-11 19:56
#define HDI_STATE_IDLE               0
#define HDI_STATE_WAIT_CTL_RESERVED  1
#define HDI_STATE_WAIT_CTL_CODE      2
#define HDI_STATE_WAIT_SYS_RESERVED  3
#define HDI_STATE_WAIT_SYS_CODE      4
#define HDI_STATE_WAIT_INF_RESERVED  5
#define HDI_STATE_WAIT_INF_CODE      6
#define HDI_STATE_WAIT_SET_RESERVED  7
#define HDI_STATE_WAIT_SET_CODE      8
#endif

//=====================================================
//* extern function declare
//=====================================================
#ifdef ALCO_PORTABLE
extern void check_alco_portable_gpio(void);
#ifdef FORBACKWARD_MUTE_BUG
extern UINT16 Is_MP3_STATE(void);
#endif
#if(defined(STOP_RESUME_DVD_VCD)&&defined(DISC_ID_IN_FLASH))||defined(AFTER_RECORD_DELAY)
extern void RsmInfo2Flash(int);//shenyj add for worning
#endif
#endif


extern inline void  PollingI2CPageWrite();
extern inline void Score_Polling(); // in score.c
extern void ircmd_pre_paser(BYTE rx);
extern inline void dvd_hl_force_action(void);
extern void update_vfd_data(void);
extern void polling_dvd_timer(void);
extern inline void recover_hl_color(void);
extern void DisplayEq(void);

extern void DispPolling(BYTE bReset);
extern void tv_format_machine(void);
extern inline void dsp_watchdog(void);
extern void reset_vfd_again(void);
extern void polling_vfdsw(void);
extern void polling_phone(void);            //////yangli 2004-10-12
extern void AC3ShowReport();
extern inline void polling_mp3(void);
extern int ClockPolling(BYTE show);
extern void check_key_status(void);
extern void check_key_status_ourmind();
extern void check_ourmind_light_status();
extern void check_keyboard_status();
extern void check_keylight_status();

#ifdef DVD_SERVO
extern void ServoDecMainLoop(void);
#endif

extern void pollingUARTServo(void);
extern void ircmd_play(void);
extern inline void MPx_AAC_ChkSmpRate();//Steven 2006/6/1 add for get MP3 and AAC Sampling rate and bitrate//

extern UINT16 Is_JPEG_PLAY_STATE(void);

extern void check_keyboard_status();

#ifdef SUPPORT_CARD_STORAGE
extern void polling_card_plug(void);
#endif //SUPPORT_CARD_STORAGE

#if defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
extern void polling_storage();  //wthsin,2004/4/12 02:16pm
#endif 

#ifdef PMP_DVD 
 extern void PMP_PC_Usb_PlugInOut();
#endif //#ifdef PMP_DVD 

#if defined(PCM1742)&&defined(CHECK_DAC_ZERO_FLAG_TO_GPIO_MUTE)     //gerry,3-10-20 11:35
extern void check_pcm1742_zero_flag();
#endif

#ifdef  SETUP_DONT_PAUSE
extern void polling_10ms_save(void);
#endif

#ifdef POLLING_10MS_SAVE_RESUME //Maoyong, 2004.03.01 10:02
extern void polling_10ms_save_rsm(void);
#endif  

#ifdef SHOW_STANDBY_TIMER//suqiaoli 2003-8-7 
extern void polling_setup_standby_timer(void);
#endif  

#if defined(SUPPORT_FS_LONGNAME)
extern void FS_ScrollDispFileName(void);
#endif

#ifdef SUPPORT_DSPMUTE
//extern UINT32 coding_mode_now;      // benson add 2004-08-20 for receiver  //kenny mark it 2005/4/21
#endif 

#ifdef MIC_MUTE_PIN   // lxg 2006-7-14 03:56
extern int mic_mute_flag;
#endif 

#ifdef SUPPORT_UPGRADE_WHEN_RUNNING
extern void polling_upgrade_info();
#endif

#ifdef TEST_VFD_PANNEL_AND_KEY//lijd 2005-5-8 13:26
extern void polling_test_front_panel(void);
#endif

#if (defined(DIRECT_ACCESS_MEDIA) && defined(CARD_SETUP_TYPE_3))//added by wangwei,2005-11-15 14:30
int polling_card_conflict(void);
int iIsCardConflict = 0;
#endif//#if (defined(DIRECT_ACCESS_MEDIA) && defined(CARD_SETUP_TYPE_3))
//=====================================================
//* external var. decalare
//=====================================================
extern BYTE gAC3onoff;
extern BYTE audioNotContinuous;

//huziqin 2006-4-19 removed

extern BYTE polling_clock;

extern BYTE bJpgVFDPause;
extern UINT8  safe_on;

#if defined(SUPPORT_BASS_TREBLE)
extern BYTE flag_BassAdjust; //xulf
extern BYTE flag_TrebleAdjust; //xulf
#endif
//============================kevin add for HDMI==============
#if 0//def HDMI// move to hdmi_api.h,chenzhao on 2005-3-7 16:25  
extern void ResetAuthentStates();
extern void AuthenticationHandler();  //authenticate the RX include all processes
extern void DSIntegratyLinkCheck();
#endif

//===================================================



//=====================================================
//* define
//=====================================================
#define GET_RTC_15_0()  (regs0->rtc_15_0)

//=====================================================
//* local var.
//=====================================================
#ifdef CHECKPHONE
int phone_flag=0;   /////////////////yangli add it for 5.1ch phone,2004-10-10
int phone_flag_k=0;
#endif

#ifdef AUTO_CLOSE_LOADER
UINT16 auto_close_timer=0;
#endif

#ifdef RECORD_PER_SECOND
int resume_time_ourmind=0;
#endif

UINT8   polling_avoid_reentry=0;
UINT8   dsp_delay=0;


#ifdef AVOID_READDISC_WHEN_STARTUP  //xyy add for Oritron
UINT16 uStartCounter=0;
UINT16 uCounterFlag=0;
#endif

#ifdef SUPPORT_EXTERNAL_MIC
UINT16 auto_mute_extern_mic_timer=0;
#endif

#ifdef CD_PLAYER        //liweihua 2003-9-3
extern void DisplaycdEq(void);
#endif

#ifdef DVB1000_NON_OS //eric add 2005-01-04 13:53 
int progCount=0;
stProgramInfo_t *progInfo; 
int nTimeCounter = 0;
#endif

#ifdef SUPPORT_GAME_TETRIS
extern void TerisPolling(UINT32 iGameTime);//Jack clear warning msg 05/09/29
#endif 
#ifdef SUPPORT_GAME_HITRAT
extern void HitRat_Polling(UINT32 iGameTime);
#endif
                    
#ifdef SAFE_AUTO_POWEROFF//nono add.2006-4-28 21:53
static inline void polling_system_standby(void) 
{
    // polling system-standby.
    if (powerdown_time_counter) call_ir_func(IRC_POWER);
}
#endif
                    
//=====================================================
//* static inline function
//=====================================================
//#include "line21.c"
#include "polling_fun.h"
//=====================================================
//* Option function
//=====================================================
//terry,2004/2/11 04:44PM
//move asv function to asv.c
#ifdef AUTO_CLOSE_LOADER
static inline void auto_close_fun(void)
{
    if(auto_close_timer&0x8000)
    {
        auto_close_timer++;
        //printf("auto_close_timer=%x\n",auto_close_timer);
        if(auto_close_timer>0x8040)
        {
            if(system_state == SYSTEM_OPEN)
            {
                auto_close_timer=0;
                ircmd_play();
            }
            else
            {
                auto_close_timer=0;
            }
        }
   }
}
#else
#define auto_close_fun();
#endif

#ifdef RECORD_PER_SECOND
static inline void auto_record_per_s(void)
{
    if(play_state==VCD_STATE_NORMAL)
    {
        if(Is_MP3_STATE()||((cd_type_loaded!=CDROM)&&(!is_menu())))
        {   if(resume_time_ourmind<6)
            {
                resume_time_ourmind++;
                //printf("resume_time_ourmind=%d\n",resume_time_ourmind);
            }
            if(resume_time_ourmind>=6)
            {
                RsmInfo2Flash(0);
                resume_time_ourmind=0;
                //printf("resume_time_ourmind=%d\n",resume_time_ourmind);
            }
        }
    }
}
#else
#define auto_record_per_s();
#endif

#ifdef STB_2_0
static inline void polling_ethernet_access(void)
{
    //for Ethernet Access test
    if (iIntCnt != pr0Cnt)
    {
      printf("cnt=%d\n",iIntCnt);
      pr0Cnt=iIntCnt;
    }

    *pEth=0x01;
    p=*pEth;
    if (p!=0x01) printf("Eth Error!!\n");
}
#else
#define polling_ethernet_access()       ((void)(0))
#endif //STB_2_0


static inline void polling_dsp_dbg_fun(void)
{
#ifdef DVD_AUDIO    //ycwen 2005/5/9 DVD AUDIO Watermark      
extern unsigned char cCDType;  
    //DVD AUDIO with Watermark 
    if ( ((regs0->dsp24_port[10]|0x00FF)>0x00FF) && (regs0->dsp24_port[10]!=0xFFFF) ) 
    {                
        if (cCDType > 0x00) //if not DVD-ROM
        {
            ircmd_stop(); //STOP
            ircmd_stop();     
            regs0->dsp24_port[10]=0xFFFF;        
        }
    }
#endif

#ifndef MONE_DSP24
    regs0->dsp24_port[6] = 0;
#else
    if (regs0->dsp24_port[6])
    {
        UINT32 dbg_msg;
        dbg_msg = regs0->dsp24_port[7];
        regs0->dsp24_port[6] = 0;
    #ifndef  MONE_DSP24_LONG 
        printf("DSP: %04x\n", dbg_msg);
//      printf_w("DSP: %04x %x %x\n", dbg_msg, get_vbv_free_exact(vbv_y), dsp3_get_rest_buf_size());
//      check if pci buffer full
//      EXTERN	INT8		pci_parse_now;
//      EXTERN	INT8		pci_use_now;
//      printf("DSP: %04x %x %d %d %d\n", dbg_msg, get_vbv_free_exact(vbv_y), dsp3_get_rest_buf_size(),pci_use_now,pci_parse_now);
    #else
       {
            typedef struct {UINT16 id; const char *s;} t_msg;
            const t_msg msg[] = {
                {0xC011, "download dsp3rom.d16.ac3.2ch successfully"},
                {0xC012, "download dsp3rom.d16.ac3.5.1ch.16M successfully"},
                {0xC031, "download dsp3rom.d16.mp3.2ch successfully"},
                {0xC032, "download dsp3rom.d16.mp3.2ch.EQ.16M successfully"},
                {0xC041, "download dsp3rom.d16.lpcm.2ch successfully\n"},
                {0xC042, "download dsp3rom.d16.lpcm.2ch.EQ.16M successfully"},
                {0xC061, "download dsp3rom.d16.cd.2ch successfully"},
                {0xC071, "download dsp3rom.d16.wma.2ch successfully"},
                {0xC091, "download dsp3rom.d16.spdif.2ch successfully"},
                {0xC0B1, "download dsp3rom.d16.nes.2ch successfully"},
                {0xD011, "download dsp3rom.d16.ac3 successfully"},
                {0xD012, "download dsp3rom.d16.ac3.spi successfully"},
                {0xD013, "download dsp3rom.d16.945.ac3 successfully"},
                {0xD021, "download dsp3rom.d16.dts successfully"},
                {0xD022, "download dsp3rom.d16.dts.spi successfully"},
                {0xD023, "download dsp3rom.d16.dtscd successfully"},
                {0xD024, "download dsp3rom.d16.945.dts successfully"},
                {0xD025, "download dsp3rom.d16.108.dtscd successfully"},
                {0xD026, "download dsp3rom.d16.raw.dtscd successfully"},
                {0xD031, "download dsp3rom.d16.mp3 successfully"},
                {0xD041, "download dsp3rom.d16.lpcm successfully"},
                {0xD042, "download dsp3rom.d16.lpcm.fudo successfully"},
                {0xD051, "download dsp3rom.d16.ppcm successfully"},
                {0xD061, "download dsp3rom.d16.cd successfully"},
                {0xD062, "download dsp3rom.d16.cd.spi successfully"},
                {0xD071, "download dsp3rom.d16.wma successfully"},
                {0xD081, "download dsp3rom.d16.midi successfully"},
                {0xD091, "download dsp3rom.d16.spdif successfully"},
                {0xD0A1, "download dsp3rom.d16.noise successfully"},
                {0xD0B1, "download dsp3rom.d16.nes successfully"},
                {0xD0C1, "download dsp3rom.d16.tuner successfully"},
                {0xCDEF, "DSP PCM output underflow"},
                {0xDEAD, "bitstream error"},
                {0xFFFF, "(unknown)\n"},
            };

            int i;
            for (i=0; 1; i++)
            {
                UINT32 id_match = msg[i].id;
                if (id_match==0xFFFF || id_match==dbg_msg) break;
            }

            printf("DSP: %04x %s\n", dbg_msg, msg[i].s);
        }
    #endif 
    }   
#endif  
}


#ifdef TURN_OFF_POWER_RESUME
//wangap add 2004/4/21
void polling_resume(void)
{
RsmInfo2Flash(0);
}    
#endif

//=====================================================
//* function
//=====================================================
//
// FUNCTION
// polling_timeout()
//
// DESCRIPTION
// check if timeout
//
#ifdef USE_FSGUI_TO_PLAY_CD
void polling_cd_fsgui(void)//frank.huang add 051014
{
	#define current_file_play_loc 	(v11_trk_now-1)%PER_PAGE
	#define current_file_play_page	(v11_trk_now-1)/PER_PAGE
	
	extern void	MoveScroll(UINT16 locate);
	extern void ShowCurrentFilePlaying(void);
	extern int 	fsnav_file_HL;
	extern UINT16 refresh_file_page;
	extern BYTE enable_polling_fsgui;
	if(!enable_polling_fsgui)
		return;
	if(((current_file_play_loc!=fsnav_file_HL)&&(v11_trk_now>0))//item changed
		||(pFsJpeg->file_page_now!=current_file_play_page))//page changed
	{
		pFsJpeg->file_current=current_file_play_loc;
		pFsJpeg->file_will=current_file_play_loc;
		pFsJpeg->fsnav_trk_now=v11_trk_now-1;

		if(pFsJpeg->file_page_will!=current_file_play_page)//change the page
		{
				fsnav_file_HL=current_file_play_loc;
			 	pFsJpeg->file_page_will=(v11_trk_now-1)/PER_PAGE;
				pFsJpeg->file_page_now=(v11_trk_now-1)/PER_PAGE;
                PrepareForChangeFilePage(pFsJpeg->file_page_will, 0, 4);
                ShowFileIcon();
#if defined (NEW_MP3_GUI)|| defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
                ShowCurrentFilePlaying();//if refresh page, must redraw the current file playing .zhaoyanhua add 2004-2-3 9:12
    #ifdef FS_BMP_GUI
                MoveScroll(pFsJpeg->file_page_will);
	#endif
#endif
             FileList();
			 refresh_file_page=1;
		}
		FSGUI_Refresh();
		refresh_file_page=0;
	}
}
#endif

void polling_timeout(void)
{
    if( ( timeout_playback )        // 2004/12/29 yltseng
#ifndef SETUP_DONT_PAUSE
        && ( full_scrn != SETUP )
#endif
#ifndef PROG_DONT_PAUSE
        && ( full_scrn != PROGRAM )
#endif
    )
    {
        if (get_rtc() > timeout_playback)
        {
          //if (GetIntrMask()&INTR_TIMEOUT)
          //    SetIntrFlag(GetIntrFlag()|INTR_TIMEOUT);
#ifdef MONE_TIMEOUR_SRC
          printf(__FUNCTION__" timeout\n");
#endif

          if(auto_pause)
          {
            timeout_playback=0;
            ircmd_play();
          }
          else
            AVD_SetMediaTimeout();
        }
    }
}

#ifdef SUPPORT_HEADPHONE  //xyy 2004-10-9

#ifndef USE_ROM_EXT_DET_HEADPHONE   //hongfeng 2005-07-29
#define TEST_HEADPHONE_SENSE      (regs0->gpio_in[HEADPHONE_SENSE/16]&(1<<(HEADPHONE_SENSE%16)))    //pin71
#else
#define TEST_HEADPHONE_SENSE        rom_ext_detect_headphone()  //for OP hongfeng 2005-07-29
#endif  //USE_ROM_EXT_DET_HEADPHONE

extern void ddx_masterMute(BYTE mute);
extern void ddx_enableEPAD(void);
extern void ddx_disableEPAD(void);
extern void write_reg_bit(int addr,BYTE bit,BYTE val);

//BYTE bHpPlug;  // 1: headphone plug in   0:headphone not plug in,moved to global.h
BYTE bCounter[2];
void polling_headphone(void)
{
    static BYTE bOldStas,bNewStas;
    
    if(TEST_HEADPHONE_SENSE)
    {
        bCounter[0]++;
        if(bCounter[0]<5 && !TEST_HEADPHONE_SENSE)
            bCounter[0] = 0;
        if(bCounter[0] == 5)
        {
            bHpPlug = 1;
            bCounter[0] = 0;
        }
    }
    else
    {
        bCounter[1]++;
        if(bCounter[1]<5 && TEST_HEADPHONE_SENSE)
            bCounter[1] = 0;
        if(bCounter[1] == 5)
        {
            bHpPlug = 0;
            bCounter[1] = 0;
        }
    }
    bNewStas = bHpPlug;
    
    if(bHpPlug && (bNewStas!=bOldStas))
    {
        #ifdef SUPPORT_AMP_HEADPHONE //chenzhao 20060114
        //amp_mute();
        #ifdef USE_AMP_MUTE //for headphone hongfeng 2005-08-06
        sub_masterMute(AMP_MUTE);
        #endif
        
        amp_enable_headphone();
        
        #ifdef USE_AMP_MUTE //for headphone hongfeng 2005-08-06
        sub_masterMute(AMP_DEMUTE);
        #endif
        #elif defined(USE_AMP_MUTE) //for headphone hongfeng 2005-08-06
            if(user_amp_mute)
                sub_masterMute(AMP_MUTE);
        #endif

    }
    else if((!bHpPlug) && (bNewStas!=bOldStas))
    {
        #ifdef SUPPORT_AMP_HEADPHONE //chenzhao 20060114
        //amp_mute();
        #ifdef USE_AMP_MUTE //for headphone hongfeng 2005-08-06
        sub_masterMute(AMP_MUTE);
        #endif        
        
        amp_disable_headphone();
        
        #ifdef USE_AMP_MUTE //for headphone hongfeng 2005-08-06
        sub_masterMute(AMP_DEMUTE);
        #endif
        #elif defined(USE_AMP_MUTE) //for headphone hongfeng 2005-08-06
            if(user_amp_mute)
                sub_masterMute(AMP_MUTE);
        #endif

    }
    bOldStas = bNewStas;
}
#endif

#ifdef I2C_MASS_DATA_POLLING_WRITE//chenzhao20060117
void polling_I2C_mass_write(void)
{
    static BYTE i2c_polling_reg0=0;
    if(p_i2c_mass_data!=NULL)
    {
        //io_write_wait("polling_I2C_mass_write\n");
        BYTE data_len=p_i2c_mass_data[0];
        if(data_len>0 && data_len<=MAX_I2C_DATA_LEN)
        {
            WriteToI2cPageMode(0x36,p_i2c_mass_data[1],(BYTE *)(p_i2c_mass_data+2),data_len);
            p_i2c_mass_data+=data_len+2;
        }
        else if (data_len==I2C_CMD_DELAY)
        {
            if(i2c_polling_reg0<p_i2c_mass_data[1])
                i2c_polling_reg0++;
            else
            {
                i2c_polling_reg0=0;
                p_i2c_mass_data+=2;
            }
        }
        else if (data_len==I2C_CMD_ADDR_LOOP)
        {
            if(i2c_polling_reg0<p_i2c_mass_data[1])
            {
                WriteToI2cPageMode(0x36,p_i2c_mass_data[3+i2c_polling_reg0],(BYTE *)(p_i2c_mass_data+3+p_i2c_mass_data[1]),p_i2c_mass_data[2]);
                i2c_polling_reg0++;
            }
            else
            {
                i2c_polling_reg0=0;
                p_i2c_mass_data+=3+p_i2c_mass_data[1]+p_i2c_mass_data[2];
            }
        }
        else if (data_len==I2C_CMD_DEMUTE)
        {
            p_i2c_mass_data+=1;
            if(!user_amp_mute)
                sub_masterMute(AMP_DEMUTE);
        }
        else if (data_len==I2C_CMD_MUTE)
        {
            p_i2c_mass_data+=1;
            sub_masterMute(AMP_MUTE);
        }
		#ifdef I2C_CMD_DEMUTE_DSP
        else if (data_len==I2C_CMD_DEMUTE_DSP)
        {
            p_i2c_mass_data+=1;
            if(!user_mute)
                AUDIF_Demute();
        }
		#endif
        else
        {
            i2c_polling_reg0=0;
            p_i2c_mass_data=NULL;
        }
    }
}
#else
#define polling_I2C_mass_write();
#endif//#ifdef I2C_MASS_DATA_POLLING_WRITE//chenzhao20060117

void disp_fan_in(void)
{
    extern BYTE    osd0_state;           //OSD0 state

    if (osd0_state>1)
    {
        #ifdef SUPPORT_FUNCTION_MENU
        if ((full_scrn!=SETUP) && (full_scrn!=SETUP_PLUS))
        #else
        if (full_scrn!=SETUP)
        #endif //end #ifdef SUPPORT_FUNCTION_MENU
            DispPolling(2);
    }
}

#ifdef QSI_PLATFORM//liulifeng add 2004-10-13////jhuang 2004/11/23
enum  {
    ERROR_CODE_N = 0x0,
    ERROR_CODE_1,
    ERROR_CODE_2,
    ERROR_CODE_3,
    ERROR_CODE_4
};

BYTE QSI_PIPO_error_code_station = ERROR_CODE_3;
BYTE QSI_PIPO_error_code_time_flag=0;
static inline void QSI_PIPO_error_code ( void )
{
    if ( QSI_PIPO_error_code_station != 0 )//error occur
    {

        if ( QSI_PIPO_error_code_time_flag < 21)
        {
            if ( ( (QSI_PIPO_error_code_time_flag / 3) %2 )
               ||(  QSI_PIPO_error_code_time_flag  > ((QSI_PIPO_error_code_station - 1 )*6 + 3))
               )
                GPIO_O_SET(GPIO_IS_FOR_SYSTEM_LED,0); // led Off
            else
                GPIO_O_SET(GPIO_IS_FOR_SYSTEM_LED,1); // led On
        }
        else if ( QSI_PIPO_error_code_time_flag < 25 )
        {
            GPIO_O_SET(GPIO_IS_FOR_SYSTEM_LED,0); // led Off
        }
        else if ( QSI_PIPO_error_code_time_flag < 28 )
        {
            GPIO_O_SET(GPIO_IS_FOR_SYSTEM_LED,1); // led On
        }
        else if ( QSI_PIPO_error_code_time_flag < 50 )
        {
            GPIO_O_SET(GPIO_IS_FOR_SYSTEM_LED,0); // led Off
        }
        else
            QSI_PIPO_error_code_time_flag = 0xff;

        QSI_PIPO_error_code_time_flag++;
    }
}
#endif//#ifdef QSI_PLATFORM
    
//#define SUPPORT_DEBUG_FOR_TRAY_IN_AND_HOME_SWITCH   // 2004/12/17 yltseng

static inline void DebugFuncForTrayInAndHomeSwitch()
{
#ifdef SUPPORT_DEBUG_FOR_TRAY_IN_AND_HOME_SWITCH
    // First parameter is TryIn, Second is HomeSwitch
    // TrayIn     : Defined in sys_servo.c TRAY_IS_IN_GPIO
    // HomeSwitch : Fixed at GPIO 6
    psprintf( RegionValStr[REGION1], "%d %d", GPIO_I_GET(5), GPIO_I_GET(6) );
    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
#endif
}   

#ifdef AUTO_TRAY_IN_WHEN_TRAY_OUT_FAIL_3TIMES	//yaowh add for arlink(8202D-216) 2005-12-22 21:14
#define TRY_TRAY_OUT_TIME	10	//polling time = x*100ms
static int InOutTime = 0;
static int TrayOutTime = 0;
static inline void TrayOut3TimesTrayIn(void)
{
	//psprintf( RegionValStr[REGION1], "%d %d", GPIO_I_GET(70), GPIO_I_GET(71) );
    //PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
    
    if (CDOpened() && GPIO_I_GET(70) && GPIO_I_GET(71) && (TrayOutTime<3))
    {
    	
    	InOutTime++;
    	if (InOutTime>TRY_TRAY_OUT_TIME)
    	{
    		//printf("--tray out fail,close--\n");
    		InOutTime = 0;
    		TrayOutTime++;
    		call_ir_func(IRC_EJECT);
    	}
    }
    else if (!GPIO_I_GET(70) && GPIO_I_GET(71) && (TrayOutTime<3) && (TrayOutTime!=0))
    {
    	//printf("--tray out again--\n");
    	call_ir_func(IRC_EJECT);
    }
    else if ((TrayOutTime >2)||(GPIO_I_GET(70) && !GPIO_I_GET(71)))
    {
    	InOutTime = 0;
		TrayOutTime = 0;
    }
}
#endif//#ifdef AUTO_TRAY_IN_WHEN_TRAY_OUT_FAIL_3TIMES	//yaowh add for arlink(8202D-216) 2005-12-22 21:14

/*
** Function Name : polling_card_conflict
** Description   : detect if cards inserted more than two types.
** Creator       : wangwei,2005-11-16 14:56
*/
#if (defined(DIRECT_ACCESS_MEDIA) && defined(CARD_SETUP_TYPE_3) && defined(SPHE8202_CARD_STORAGE))//added by wangwei,2005-11-15 14:30
int polling_card_conflict(void)
{
    // Warning message, only support one card insert. 
    // A problem is that system can not judge the situation that Xd & SMC insert at the same time.
    if(((detect_type & CF_CARD_DEVICE) && (detect_type & SD_CARD_DEVICE))   // CF & SD
    || ((detect_type & CF_CARD_DEVICE) && (detect_type & MS_CARD_DEVICE))   // CF & MS
    || ((detect_type & CF_CARD_DEVICE) && (detect_type & SMC_CARD_DEVICE))  // CF & SMC
    || ((detect_type & SD_CARD_DEVICE) && (detect_type & SMC_CARD_DEVICE))  // SD & SMC
    || ((detect_type & MS_CARD_DEVICE) && (detect_type & SMC_CARD_DEVICE))  // MS & SMC
    || ((detect_type & CF_CARD_DEVICE) && (detect_type & SMC_CARD_DEVICE) && (detect_type & SD_CARD_DEVICE))  // CF & SMC & SD
    || ((detect_type & CF_CARD_DEVICE) && (detect_type & SMC_CARD_DEVICE) && (detect_type & SD_CARD_DEVICE))) // CF & SMC & MS
    {
        if(iIsCardConflict == 0)
        {
            iIsCardConflict = 1;

        psprintf(RegionValStr[REGION1], "PLEASE INSERT ONE CARD ONLY");
            PrintOsdMsg(STR_OS_SPACE, REGION1, 0, 1);
        
        // If CARD storage is playing, stop it.
        if((storage_type == CF_CARD_DEVICE)
        || (storage_type == SD_CARD_DEVICE)
        || (storage_type == MS_CARD_DEVICE)
        || (storage_type == SMC_CARD_DEVICE))
        {
            AVD_SetMediaInterrupt();//stop the current mp3, Can't be used for JPEG!!
            storage_type = 0;
            media_type = MEDIA_NOTHING;
                media_status = STATUS_CARD;
            system_state = SYSTEM_OPEN;
            play_state = VCD_STATE_CLOSE;    
                ircmd_post_func(CMD_FUNC | CMD_FUNC_OPEN);
                system_state = SYSTEM_OPEN;
                detect_type = 0;
        }
        }
    }
    else
        iIsCardConflict = 0;
    
    return iIsCardConflict;
}
#endif//#if (defined(DIRECT_ACCESS_MEDIA) && defined(CARD_SETUP_TYPE_3) && defined(SPHE8202_CARD_STORAGE))



	
//
// FUNCTION
// polling_100ms
//
static inline void polling_100ms(void)
{
#ifdef SUPPORT_DIVX6
    #include "divx6_if.h"
    #include "kinf.h"
    if (GetCurrentFileType() == CDROM_MP4)
    {
        extern UINT32 is_divx6_file;
        if (is_divx6_file == 1)
        {
            divx6_check_chapter(GET_MP4_DECODED_FRAME());
        }
    }
#endif  //#ifdef SUPPORT_DIVX6

#ifdef SUPPORT_TOUCH_PANEL
      polling_tsc2003_100ms();
#endif
    #ifdef SUPPORT_MP3_ENCODER
    if(polling_MP3_encoder == 1)
    {
		fs_mp3_encoder_main();
    }
    #endif
    
    #if (defined(DIRECT_ACCESS_MEDIA) && defined(CARD_SETUP_TYPE_3) && defined(SPHE8202_CARD_STORAGE))//added by wangwei,2005-11-15 14:30
    polling_card_conflict();
    #endif

#ifdef MUSTEK_LCD_DRIVE_BITEK//QiaoHuilin:2005-9-1 for timing for clear lcd message
    TimingClearLCDMessage();
#endif

// mimitsai, move from polling_10ms
//#if !defined(JIEKE_PANNEL_GK3800) && !defined(DP3240_KEY_SCAN)
#if defined(DP2070_KEY_SCAN)//NONO20050806
//for jieke's led pannel wangfeng 2003-11-19 19:07
#if defined(SUPPORT_VFD)||defined(GPIO_KEY_LIGHT)//NONO 3-8-18 14:39
    polling_vfdr();
#endif
#endif


#ifdef SUPPORT_SPDIF_IN  /*2005-6-6 20:17 huziqin*/  
    if(0
        #ifdef SPDIFIN_AVIN_IN_ONE_MODE//chenzhao 20060118
        ||(((system_state == SYSTEM_DOING_AV1)&&get_av1_input())||((system_state == SYSTEM_DOING_AV2)&&get_av2_input()))
        #else
            ||(system_state == SYSTEM_DOING_SPDIF)
#ifdef SUPPORT_COAXIAL_IN    
            ||(system_state == SYSTEM_DOING_COAXIAL)
            #endif    
        #endif    
        )
    {
        if(!(full_scrn & SOUND))
            spdif_in_init();
    }
#endif //SUPPORT_SPDIF_IN    
    
#ifdef 	NOT_SHOW_MIC_SETUP_detect_by_sensor//2005-4-27 10:01 zhoulin
    mic_on_off_check();
#endif
    
#ifdef OP_GPIO54_CHECK_MIC_ON_OFF //qinhua 2005-8-27
    mic_on_off_check();
#endif
   
    DebugFuncForTrayInAndHomeSwitch();
    
#ifdef AUTO_TRAY_IN_WHEN_TRAY_OUT_FAIL_3TIMES	//yaowh add 2005-12-22 21:12
	TrayOut3TimesTrayIn();
#endif
    
#ifdef SUPPORT_ELA //axel 20050325
    extern int pre_disp_id;
    extern UINT8 ElaPlayJPEGFlag;
if(ElaPlayJPEGFlag){
     if((regs0->game16_status & 0x100)!= pre_disp_id)
        {
             Polling_BitBLT();
             regs0->dis_pic_id = !(regs0->dis_pic_id);
         }    
     else 
         pre_disp_id = regs0->game16_status & 0x100;
}         
#endif

#ifdef QSI_PLATFORM//liulifeng add 2004-10-13//jhuang 2004/11/23
    QSI_PIPO_error_code ();
#endif

#ifdef TEAC_PORTABLE_DVD//check 8202s 216 pin142 eject button for slot-out only
    if (system_state != SYSTEM_IDLE)
    {     
        regs0->sft_cfg0 &= ~((0x1)<<4);//Enable GPIO39          
        GPIO_M_SET(EJECT_SW_ON,1);
        GPIO_E_SET(EJECT_SW_ON,0);
        
        if ( (!CDOpened()) && (GPIO_I_GET(EJECT_SW_ON)==0) ) 
            call_ir_func(IRC_EJECT);
    }        
#endif

#ifdef PMP_MCU810
  if((GetCurrentFileType() != CDROM_JPEG )&&(GetCurrentFileType() != CDROM_DAT )
      &&(GetCurrentFileType() != CDROM_MPG) &&(GetCurrentFileType() != CDROM_MP4) 
   ||(pFsJpeg->gifsState == FS_STATE_LIST||pFsJpeg->gifsState == FS_STATE_MP3))
     Show_PMP_Bat();
#endif

#ifdef CHECK_AV_JACK//yangli add for PMP.20050426
polling_av_jack();
#endif

#ifdef  SUPPORT_SPI
    polling_spi();
    spi_service();
#endif

#ifdef  SUPPORT_MP4_SUBTITLE
    if( (!(full_scrn) || (full_scrn & GOTO) ) && (play_state != VCD_STATE_PAUSE))
    {
        if (IS_EXT_SUP_ACTIVATED())
        {
            if(g_pfnPollingSubtitle)
                g_pfnPollingSubtitle();

        }
    }
#endif

#ifdef PDVD_USE_IO_SCAN_KEY //Jack modified 04/06/03
//#ifdef GBM_PORTABLE_DVD
  check_portable_key(); //rbhung for GBM Portable DVD
  #ifdef ALCO_PVS8712
  check_portable_key2();//shenyj add 0928
  #endif
#endif

//freyman 2002-7-4 11:30
#ifdef VFD_VOLUME_DISPLAY
{
    int diff;
    //diff=timenow-rtc_100ms;
    
    polling_vfdtime(diff);
}
#endif

#ifdef USE_GAMEPORT_TO_BUTTON//nono 20020824
    check_key_status();
#elif defined(OURMIND_VFDPORT_TO_BUTTON)//nono 20020824
    check_key_status_ourmind();
    check_ourmind_light_status();
#elif defined(USE_VFDPORT_TO_BUTTON)
    check_keyboard_status();
#elif defined(USE_VFDPORT_TO_KEYLIGHT)
    check_keylight_status();
#endif
#if defined(FAT_Write_UI)||defined(CF_CARD_WRITE)//||defined(WRITE_USB)//liweihua 2003-10-29
extern void polling_input_name(void);
extern BYTE input_flag;
if((full_scrn & PERIPHERAL) && (input_flag == 1))
    polling_input_name();
#endif

#ifdef AC3TEST
  if (gAC3onoff==1) {
    AC3ShowReport();
  }
  AC3CheckSampling();
#endif

    if ( (audioNotContinuous>0) && (play_state==VCD_STATE_NORMAL) ) { //count it when STATE_NORMAL, Jeff 20021202
        audioNotContinuous--;

        if (audioNotContinuous==0) {
      if (!user_mute) {
                AUDIF_Demute();//2004AUDDRV AudioDemute();
#ifdef CHANGE_DSP_SPDIF_OFF
                AUDIF_Set_SPDIF(setupGetSetting(14));//2004AUDDRV AudioSetSPDIF(setupGetSetting(14));
#endif//#ifdef CHANGE_DSP_SPDIF_OFF
      }
    }
  }

#ifdef NF_100
  if( (play_state!=VCD_STATE_PAUSE)&&(full_scrn!=SETUP) )
  {
    if( dvd_timer>0 )
    {
      //printf("polling_100ms  play_state = %d\n",play_state);
      polling_dvd_timer();
    }
  }
#else

    if( ( P_frame == 0 )            // 2004/12/29 yltseng
#ifndef SETUP_DONT_PAUSE
        && ( full_scrn != SETUP )
#endif
#ifndef PROG_DONT_PAUSE
        && ( full_scrn != PROGRAM )
#endif
    )
    {
        if(!IsAVDPaused() && (dvd_timer>0) )
          polling_dvd_timer();
    }
#endif
  if (hl_timer>0)
    recover_hl_color();

  if (auto_pause)
    polling_timeout();
    
    #ifdef SUPPORT_FUNCTION_MENU
    if(setup_menu_plus_timer)
      polling_setup_menu_plus();
    #endif //end #ifdef SUPPORT_FUNCTION_MENU
    
#ifdef SUPPORT_REP_READ
    if(IsReadMode())
        PollingRecBufStatus();
#endif
    
#ifdef FS_BMP_GUI//zhaoyanhua add 2004-6-29 15:58    
    if(cd_type_loaded == CDROM) // Robert 021004
    {
        //Steven 2006/6/1 add (GetCurrentFileType() == CDROM_AAC) for aac audio//
        if ((GetCurrentFileType() == CDROM) || (GetCurrentFileType() == CD_DA) || (GetCurrentFileType() == CDROM_WMA) || (GetCurrentFileType() == CDROM_AAC))
            polling_mp3();
    }
	#ifdef USE_FSGUI_TO_PLAY_CD//frank.huang add 051014
	if(cd_type_loaded==CDDA)
		polling_mp3();
	#endif
#endif//#ifdef FS_BMP_GUI   
 
#ifdef BRIGHTNESS_COLOR_KEY
    polling_BCtimer();
#endif
   
#ifdef SUPPORT_HEADPHONE  //xyy 2004-10-9 
    polling_headphone();
#endif

#ifdef ALONE_GPIO_KEY//Jack 20041008
    polling_portable_akey();
#endif

#ifdef CONTINUOUS_NUM_KEY_SELECT
  if(ir_num_timer)
    polling_ir_num();  
#endif 

#ifdef SUPPORT_8202_DVB
	if(Is_Dvb_State())
		DVB_polling_100ms();
#endif


#ifdef SUPPORT_SETUP_POPUP_TESTSPK_GUI
    polling_testspk_100ms(0);//1:reset timer; 0: normal
#endif

#ifdef DOLBY_AMP_VOLUME_CTRL//chenzhao20060117
    polling_volume_change();
#endif

//======================================================
#if(defined(STOP_RESUME_DVD_VCD)&&defined(DISC_ID_IN_FLASH))||defined(AFTER_RECORD_DELAY)
    if(need_record && (need_record!=PRE_STOP_FLAG) && (need_record!=POWER_ON_RECORD_FLAG))
    {
        need_record--;
        
        if((need_record==1) && (cd_type_loaded==CDSVCD))
        {
            need_record = REAL_RECORD_VALUE;
            LoadModual(MODUAL_CDROM);
            RsmInfo2Flash(0);
            need_record = 0;
        }
	}
#endif
#ifdef JPG_ROTATE_DELAY
    if(angle_key_timer)
        angle_key_timer--;
#endif
#ifdef DIVX_STOP_TO_PLAY_DELAY//shenyj add for alco divx 12/13
if((play_state==VCD_STATE_STOP)||(play_state==VCD_STATE_MP3_FILELIST))
{
    if(divx_stop_to_play_delay_timer<DIVX_STOP_TO_PLAY_DELAY_CNTTT)
       divx_stop_to_play_delay_timer++;    
}
else 
      divx_stop_to_play_delay_timer=0;
#endif
//======================================================

}


//
//
extern int gbm_gpio_led_flag;
extern  BYTE   cd_type_loaded;

#ifdef SunplusMoudleTest //axel 2004/4/2 11:55am while detected DVD, wait for 15 sec, tray out...

UINT16 ModuleTicks=0;
static inline void auto_modual_test(void)
{
    if(cd_type_loaded==CDDVD)
    {
        if(ModuleTicks>=45)
         {
            ModuleTicks=0;
            ircmd_stop();
            delay_srv_10ms(100);
            //ircmd_power();
/*          delay_srv_10ms(500);
            ircmd_trayin();*/
         }  
        else
         ModuleTicks++; 
        
    }   
}
#else
#define auto_modual_test();
#endif

/*
* polling_one_minute()  wangap add 2004/4/26 
*/
static inline void polling_one_minute(void)
{
  #ifdef TURN_OFF_POWER_RESUME //wangap 2004/4/21  
  if(play_state!=VCD_STATE_STOP)
  polling_resume();
  #endif  
}
                    
#ifdef  AUTO_ADJUST_TV_TYPE

BYTE  Adjust_TV_type =0;

#endif                    
#ifdef UART_WITHOUT_DEBUG_MODE //axelchen 2004/10/20 
              
void ReturnFromUart(void)
{
  int d;
    if (!IsEPPRxEmpty())
    {
        d = EPP_GETC();
        UART0_putc(d);
    }   
}
#endif
#if defined(SLEEP_CONTROL_COUNTER)||defined(SUPPORT_DVB_TIMER)   //liumzh 2004-12-10 23:53  //sunzhh add for DVB 20051019
    UINT32 counter_sleep_control = 0;
    UINT32 sleep_time = 15;//seconds
#endif
#ifdef  STOP_15M_AUTO_POWEROFF
extern UINT8 STOP_15M_STATE;
unsigned short int second_counter=0;
unsigned short int sleep_counter=0;
unsigned char one_second_flag=1;
int  timer_counter=0;
unsigned char sleep_show_flags;
#endif

/*
*   polling_500ms()
*/
#ifdef  IR_SLEEP //chenzhao 2006-4-20 11:14 .
inline void polling_sleep_500ms(void);
#endif
#ifdef SUPPORT_SPG_GAME
extern void SPG_Detect_Screen(void);
#endif
#ifdef SUPPORT_VFD_MESSAGE //chenzhao 20060117
void polling_vfd_message_time(void);
#endif
extern int is_dts_force_spdif_bitstream(void);
#ifdef SUPPORT_RECEIVER
extern void  cust_polling_500ms();    
#endif
#ifdef   SUPPORT_CHECK_MCU_INFO
extern void  check_mcu_info(void);
#endif//#ifdef   SUPPORT_CHECK_MCU_INFO
static inline void polling_500ms(void)
{
    #ifdef   SUPPORT_CHECK_MCU_INFO
    check_mcu_info();
    #endif//#ifdef   SUPPORT_CHECK_MCU_INFO
    #ifdef SUPPORT_RECEIVER
    cust_polling_500ms();    
    #endif

    #ifdef SUPPORT_OP_FIVE_DISC //chenzhao20060107 
    polling_5disc_control_500ms();
    #endif
    #ifdef MULTIDISC_LOADER //chenzhao20060112 
    polling_multidisc_loader_exchange();
    #endif
    #ifdef  IR_SLEEP //chenzhao 2006-4-20 11:15 .
    polling_sleep_500ms();
    #endif
    
#ifdef SUPPORT_NERODIGITAL  //lyc add 2005-12-23
    #include "file_if.h"
    if(((IS_FILE_TYPE_QT())||(IS_FILE_TYPE_ND()))&&!(audio_only && IsM4AFileType()))//qinhua,modify for m4a file reset,2006-2-18 11:39
    {
       	extern UINT32  QT_get_num_of_chapter();
       	 if(QT_get_num_of_chapter())
       	 {
       	      extern UINT32  QT_get_curchapter();
       	      UINT32 curChap = pFsJpeg->g_uiCurChapter; 
       	      if(curChap != QT_get_curchapter())
       	         DispCookOSD0(1);  
	       }
    }
#endif  //#ifdef SUPPORT_DIVX6

#ifdef SAFE_AUTO_POWEROFF//nono add. for fix this function.20060428
    polling_system_standby();
#endif

#ifdef SUPPORT_DVB_BOOKING
    static int i=0;
    if(i<30)
    {
        i++;
    }
    else
    {
        DVB_polling_500ms();
    }
#endif
#ifdef MUSTEK_LCD_DRIVE_BITEK//QiaoHuilin:2005-9-1
	YUV_Go();
#endif

#ifdef MUSTEK_K100D_MODEL//by justin 2005/09/30//about vfd_portable.c
    if(IunTestPin84<2)
        IunTestPin84++;
#endif

#ifdef DMA_DVD_SWITCH
extern void Check_Status_Change(void);
Check_Status_Change();
#endif	
#ifdef SUPPORT_SPG_GAME
if ((GamePadVal==0x10)&&(spg_game_pad))
    {
        SPG_Detect_Screen();
    }
#endif
/*#ifdef DVB1000_NON_OS
int iHasTDT=0;
iHasTDT=PollingTDT(5);//eric add 2004-12-16 15:12 use Demux channel 5
if((full_scrn == PROGRAMINFO)&&iHasTDT)
{
printf("full_scrn == PROGRAMINFO)&&PollingTDT(5)\n");
 DisplayProgramInfo(1);
}
#endif*/ //eric change  polling TDT to 1SEC 

  #ifdef SUPPORT_INITDELAY //ouyang add 2005.07.04
        if (bInitStatus)//add by xlluo 05-06-09
        {
            bInitStatus--;
            if (!bInitStatus)
            {
               if (((midiState ==MIDI_STATE_INIT)||
                        (midiState ==MIDI_STATE_PLAY_ONLYVIDEO))
                        &&(MenuState<MENU_MULTI_INDEX_SEL))
                        {
                            extern void Disp_SelectSongFlag();
                            Disp_SelectSongFlag();
                        }
                    printf("set bHoldInput zero!\n");
                    bHoldInput  = 0;                              
            }
        }
    #endif  //ouyang add for delay 2m show "qing xuan qu"2005.04.20
#ifdef SUPPORT_ELA //axelchen 20050325
extern void ELAPollingCommandMessage(void);
   if(spg_game_pad)  ELAPollingCommandMessage();
#endif

#ifdef PMP_KEYBOARD  //xyy 2005-1-10
    extern polling_pmpkey(void);
    polling_pmpkey();
#endif

#if defined(EASTECH_SETUPMENU) || defined(SETUP_POPUP_PSCAN_WARNING_GUI)
extern BYTE check_show_pscan_wait_time_mode;
extern void pscan_change_time_out(void);
extern void refresh_pscan_wait_time(BYTE wait_time);
static BYTE wait_time=CHANGE_TO_PSCAN_WAIT_TIME_TOTAL;
if(check_show_pscan_wait_time_mode==1){
    wait_time--;
    if(wait_time==0){
        pscan_change_time_out();
        wait_time=0;
        check_show_pscan_wait_time_mode=0;
        }
    else{
        refresh_pscan_wait_time(wait_time);
        }   
}
else wait_time=CHANGE_TO_PSCAN_WAIT_TIME_TOTAL;
#endif

#ifdef UART_WITHOUT_DEBUG_MODE //axelchen 2004/10/20 
ReturnFromUart();
#endif

#if defined(SLEEP_CONTROL_COUNTER)||defined(SUPPORT_DVB_TIMER)   //liumzh 2004-12-10 23:53  //sunzhh add for DVB 20051019
    if(counter_sleep_control)
    {
        sleep_time = sleep_time - 1; //(1 for 0.5 sec)
        if(sleep_time == 0)
    {
        counter_sleep_control = 0;
        sleep_time = 0;
        ircmd_power();
    }
    }
#endif

#ifdef  STOP_15M_AUTO_POWEROFF
    if(STOP_15M_STATE==1)
    {
	    if((sleep_counter)/*&&(system_state== SYSTEM_STOP)*/)
        {
		    sleep_show_flags--;
            if(!sleep_show_flags)
        	    ;//osd_sleep_disp(sleep_counter);
            second_counter++;
            if(second_counter>=60*2)
            {  
        	    second_counter=0;          	
                sleep_counter--;        
                if(sleep_counter==0)
                {
        		    if((system_state== SYSTEM_STOP)||(play_state==VCD_STATE_STOP))
            	    ircmd_power();              
                }
            }
        }
    }
#endif
    #ifdef DISPLAY_CD_TEXT             //lizhx  add 04/10/17
    if (cd_type_loaded == CDDA)
    {
        if(!((full_scrn & PROGRAM)||(full_scrn & SETUP)||(full_scrn & SOUND)))
            show_CDText_Title_Content(v11_trk_now);
    }
    #endif
    
	#ifdef  MIDI_SCORE_TEST //modify by xlluo for test
    extern BYTE gb_showScore;
    #endif


    auto_modual_test();//terry,2004/4/2 04:49PM
     #ifdef  AUTO_ADJUST_TV_TYPE
    if((play_state==VCD_STATE_NORMAL) && (Adjust_TV_type==1))
    {        
        auto_adjust_tv_type();       
    }
    #endif
    // mute mute
    //2005/4/7 mark by ycwen : rampdown is needless (and may cause problem), 
    //                         because the ability to decode DTS is control by chip now.
    /*if (is_dts_force_spdif_bitstream()) {
        regs0->aud_pcm_ramp_delta   = 0xff;
        regs0->aud_pcm_ramp_cfg     = 1;
    }*/
    

    #ifdef TEST_SERVO
    srv_mode_test_polling();//terry,2003/9/10 12:57AM
    #endif
#ifdef  RECORD_KEY//zhaoyanhua add 03-11-5 13:02
    if(same_disc_flag)
        same_disc_flag++;
    #endif

    auto_close_fun();
    auto_record_per_s();

#ifdef SCRN_SAVER_WHEN_PAUSE
    if (full_scrn & SETUP)//4-3-5 23:24
        safe_srn_off();
    else if(play_state == VCD_STATE_PAUSE)
        #ifdef SUPPORT_MIDI    //ouyang add for don't show saver in midi2005-1-12 19:22
        if(!gIsMidiSelMenu)  
        #endif 
        safe_srn_on();
#endif

#ifdef PMP_UI               //////////////////yangli add for safe  2005/8/2
     if((pFsJpeg->gifsState == FS_STATE_MODE)||
       (pFsJpeg->gifsState == FS_STATE_HDD)||
       (pFsJpeg->gifsState == FS_STATE_INIT)||
       (pFsJpeg->gifsState == FS_STATE_SETUP)||       
       (pFsJpeg->gifsState == FS_STATE_MP3)) //zxb 2005-9-23 11:44 for screen save when play MP3
       
    {
        safe_srn_on();    
    }
#endif                 //////////////#ifdef PMP_UI

#ifdef SUPPORT_8202_DVB //David add 2005-3-30 13:07
	#ifndef SUPPORT_DVB_GUI_NEW
	if(!full_scrn && ProgScrambleStatus)
	#else
	if((get_total_number_channel()<=0)&&(Is_Dvb_State())&&IsMenuHided())    //sunzhh add 20051027
	#endif
	{
		safe_srn_on();
	}

#endif

#ifdef USE_PIN31_CONTROL_POWER_LED      //gerry,2004-3-9 19:42
    if(gbm_gpio_led_flag<=4)
    gbm_gpio_led_flag++;
    else
    {
        GPIO_O_SET(4,1);
    }
#endif//USE_PIN31_CONTROL_POWER_LED

    if (regs0->dsp24_port[4]==1)
    { //to check whether MIC is on or off, Jeff 20020904
        mic_on = 1;
    } else {
        mic_on = 0;
    }

#ifdef SUPPORT_SCORE
  if ((full_scrn & SCORE)
#ifdef  MIDI_SCORE_TEST //modify by xlluo 
    ||(gb_showScore)
#endif    
#ifdef SUPPORT_SANJING_SCORE            //xlluo for sjspical score ui 04 -10 -15
    ||(bIsSJScoreInvaild)
#endif
    )
  { //Jeff 20020404
    Score_Polling();
  }
#endif
  // check mp2/mp3 sample-rate (reported from audio decoder)
  
  if(mpeg_audio) 
      MPx_AAC_ChkSmpRate();//Steven 2006/6/1 add for get MP3 and AAC Sampling rate and bitrate//
  #ifdef SUPPORT_AAC
  else if(aac_audio)//Steven 2006/6/1 add for aac audio flag//
      MPx_AAC_ChkSmpRate();
  #endif
  
  if(auto_download_audio_chn)
  {
       if(AUDIF_AutoDownload_Codec(auto_download_audio_chn-1))//2004AUDDRV audif_auto_download_codec(auto_download_audio_chn-1)
       {//sucess
           auto_download_audio_chn=0;
       }
  }
#ifndef FS_BMP_GUI//zhaoyanhua 2004-6-29 15:58 
  if(cd_type_loaded == CDROM) // Robert 021004
  {
      //Steven 2006/6/1 add (GetCurrentFileType() == CDROM_AAC) for aac audio//
      if ((GetCurrentFileType() == CDROM) || (GetCurrentFileType() == CD_DA) || (GetCurrentFileType() == CDROM_WMA) || (GetCurrentFileType() == CDROM_AAC)|| (GetCurrentFileType() == CDROM_WAV))
          polling_mp3();
  }
	#ifdef USE_FSGUI_TO_PLAY_CD//frank.huang add 051026
	if(cd_type_loaded==CDDA)
		polling_mp3();
	#endif
#endif//#ifndef FS_BMP_GUI

  #if defined(REMAIN_TIME)&&!defined(ALCO_DVD_UI)//nono 2-7-13 11:27

//  printf("polling:polling_clock=%d\n",polling_clock);
  if(polling_clock<7)
  {
    if( (polling_clock==6)&&(t_disp) )
      t_disp+=10;

    polling_clock++;
   }
  #endif

//huziqin 2006-4-19 removed

#ifdef SUPPORT_FS_LONGNAME  //Maoyong 2004.06.24
    #if defined(FOLDER_FILE_LONGNAME)&&defined(HDD_SCROLLDISP) //zxb 2005-8-9 0:30
    	HDD_ScrollDispLongName();
    #else
        #ifndef GPS_MP3_UI          //suxin 2005-09-22,for gps_mp3_ui
    if( (play_state != VCD_STATE_PAUSE) && (play_state != VCD_STATE_STOP) 
        &&(pFsJpeg->gifsState == FS_STATE_LIST||pFsJpeg->gifsState == FS_STATE_MP3))                    
        FS_ScrollDispFileName();
        #endif      //#ifndef GPS_MP3_UI
    #endif //defined(FOLDER_FILE_LONGNAME)&&defined(HDD_SCROLLDISP)
#endif

//nono add "&&defined(USE_GPIO_MUTE)  "20040821
#if defined(SUPPORT_DSPMUTE)&&defined(USE_GPIO_MUTE)     //2005 4/21 kenny add and mark some things
    int dsp_mute_count;
    dsp_mute_count= get_dsp_mute_flag_count()  ;
    
    if (
        ((dsp_mute_count&0xff)>=100)&&((dsp_mute_count&0x400) ==0x400)
    	   #ifdef MIC_MUTE_PIN    // lxg 2006-7-14 04:00
    	     &&( mic_mute_flag=1)
    	   #endif
       )
	{   
		set_dsp_mute_flag_count(dsp_mute_count&0x3ff);
        GPIO_MUTE();   
    }
   
#endif 


#ifdef SUPPORT_VFD_MESSAGE
    polling_vfd_message_time();
#else
#if defined(SUPPORT_APOGEE_AMP)||defined(TAS_5508_PWM) //xyy 2004-8-5
#ifdef DOLBY_AMP_VOLUME_CTRL
    polling_channel_timeout();
#endif
#endif
#endif

#if defined(SUPPORT_8202_DVB)
    if(Is_Dvb_State())
        DVB_polling_500ms();
#endif

#ifdef SUPPORT_ELA
    extern void  ElaPlay2Stop();
    ElaPlay2Stop();
#endif    

#ifdef MODE_SWITCH_DELAY
    if(mode_key_delay_cnt)
        mode_key_delay_cnt--;
#endif

#if 0//def FORBACKWARD_MUTE_BUG //Jack added 04/12/27 for Alco
    if(cd_type_loaded == CDROM)
    {
        if(Is_MP3_STATE()&&(adv_search_time))
        {
            AUDIF_Set_Volume(0);//AudioSetVolume(0);
            //GPIO_MUTE(); 
        }
    }
#endif
    
}

#ifdef  SUPPORT_MP4
extern UINT32 audio_prefilled;
extern int polling_audio();
#endif

#ifdef QSI_PLATFORM //qsi: added by johnosn 20040712
void update_system_led_status(void)
{
    if( is_dvddsp_hw_busy() && (play_state!=VCD_STATE_IDLE))
    {
        GPIO_O_SET(GPIO_IS_FOR_SYSTEM_LED,1); // led On   
    }
    else
    {
        GPIO_O_SET(GPIO_IS_FOR_SYSTEM_LED,0); // led Off
    }
}

#ifdef QSI_SUPPORT_EJECT_BUTTON
extern void ircmd_eject_toggle(void);
#define EJECT_BUTTON_IS_VAILD_TIME  100/10 //base on 10 ms polling loop  
#define EJECT_BUTTON_IS_VAILD_GAP_TIME  1000/10
void  polling_eject_button(void)
{
    static  BYTE eject_pressed_time=0;

    if(eject_pressed_time>EJECT_BUTTON_IS_VAILD_TIME)
    {
        eject_pressed_time++;
        if(eject_pressed_time>EJECT_BUTTON_IS_VAILD_GAP_TIME)
        {
            eject_pressed_time=0;
        }
        return;
    }

    if(GPIO_I_GET(GPIO_IS_FOR_EJECT_BUTTON)==0)
    {
        printf("polling_eject_button> Eject is pressed\n");
        eject_pressed_time++;
        if(eject_pressed_time >EJECT_BUTTON_IS_VAILD_TIME)
        {
            ircmd_eject_toggle();
        }
    }
    else
    {
        eject_pressed_time=0;
    }
}
#endif//QSI_SUPPORT_EJECT_BUTTON
#endif//QSI_PLATFORM

#ifdef _DYNAMIC_SPECRUM
extern void Dynamic_Spectrum(void);
#endif

#ifdef OSD_SPECIAL_MENU
UINT8 osdcount;
extern polling_MIPZ_TO_LX4189_msg(void);
#endif
//eric move here for 05/04/29 test 
#ifdef SUPPORT_EPG
extern int g_EPG_Mode;
#endif
static inline void polling_10ms(void)
{  
    //#ifdef SUPPORT_CONTROL_ANT_POWER////yangli add for antenna  power ,2006-1-5 17:50
    //polling_ant_power_overload();
    //#endif

    #ifdef SUPPORT_DVB_GUI_NEW
        DVB_polling_10ms();
    #endif
    
    #ifdef SUPPORT_TOUCH_PANEL
    polling_tsc2003_10ms();
    #endif
    
    #ifdef GPS_KEYBOARD//liweihua add 2005-6-1
    extern UINT32 timer_counter;
    if((full_scrn & TOUCH_KEYBOARD)&&(cd_type_loaded!=CDROM))//frank.huang 050922
    {
        if(timer_counter < KEEP_KEYBOARD_TIME)
            timer_counter++;   
        else
            GPS_key_board();
    }
    
    #endif  
	#ifdef USE_FSGUI_TO_PLAY_CD//frank.huang add 051018
	if(cd_type_loaded==CDDA)
		polling_cd_fsgui();
	#endif
#ifdef OSD_SPECIAL_MENU 
if(osdcount >= 2)
{
    osdcount=0;

       polling_MIPZ_TO_LX4189_msg();
}
else
    osdcount++; 
#endif  
    
#ifdef SUPPORT_DVB_VFD  //haoy 2005/03/31 18:20 display prog num by led
//   char xx[20];       // mask off by barry, we should not always declare local array any where
   psprintf(linebuf,"%d",currTVProgIndex);
   vfd_set_str(0,linebuf);
#endif

#ifdef TEST_VFD_PANNEL_AND_KEY//lijd 2005-5-8 13:45
    polling_test_front_panel();
#endif 

#ifdef _DYNAMIC_SPECRUM
    Dynamic_Spectrum();
    //print_block(bEqEnergyMax,sizeof(bEqEnergyMax));
#endif

    #ifdef SUPPORT_PS2
        if(START_POLLING_PS2)
        {
            polling_mouse();
        }
    #endif  

    
    #ifdef GPS_DVD
    polling_GPS_DVD();
    #endif
    
#ifdef SEND_BIT_RATE_TO_IOP  //wsf 040802
    send_bit_rate();
#endif
/*
  if(adv_search_time)
  {
     if(chk_speed_state(UOP_FW))
         ircmd_play();
  }*/

#ifdef AVOID_READDISC_WHEN_STARTUP  //xyy add for Oritron
    if(uCounterFlag==0)
        uStartCounter++;
    if(uStartCounter>=100)
    {
        uStartCounter=0;
        uCounterFlag=1;
    }
#endif



#ifdef QSI_PLATFORM //qsi: merge by johnson 20040712,for led(busy indicate)
   update_system_led_status();
#ifdef QSI_SUPPORT_EJECT_BUTTON
   polling_eject_button();
#endif
#endif

#ifdef SUPPORT_SPI_QSI
BYTE  spi_data = 0;
    extern UINT8 uSpiRxData;
#define SPI_RDY  0x0001
    if(regs0->iop_data[1]&SPI_RDY)
    {
        printf("iop data %x\n",regs0->iop_data[1]);
        uSpiRxData = spi_data = regs0->iop_data[1]>>8;   //get data
        regs0->iop_data[1] = 0x0;  //clear flag
        //printf("iop data --%x\n",regs0->iop_data[1]);
        //psprintf(RegionValStr[REGION2], "DATA %d",spi_data);
        //PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);

        spicmd_pre_parse(spi_data);//jhuang 2004/6/16 03:56下午
    spi_data = 0;//jhuang 2004/8/5

    }
#endif//SUPPORT_SPI_QSI

#ifdef  SPHE1000
    polling_audbuf();
#endif

#ifdef  SUPPORT_MP4
    if (audio_prefilled)
        polling_audio();
#endif


  #ifdef SETUP_DONT_PAUSE//terry,2004/2/23 03:58PM
    polling_10ms_save();    
  #endif

#ifdef POLLING_10MS_SAVE_RESUME //Maoyong, 2004.03.01 10:02
    polling_10ms_save_rsm();
#endif  

#ifdef AUTO_INTO_STANDBY
    extern int auto_standby_timer;
    if(system_state==SYSTEM_STOP||system_state==SYSTEM_NODISC||play_state==VCD_STATE_STOP)
    auto_standby_timer++;
#endif

#ifndef SDRAM_16Mb_Mode
    #ifndef  DYNAMIC_SPECTRUM       //fengjl  3-10-28 18:02
    if (full_scrn & SOUND)
    #ifndef MAKE_ONLY_UPDATE_CODE
//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
        DisplayEq();
    #endif
    #else//#ifndef  DYNAMIC_SPECTRUM
        if ((!(full_scrn & SETUP))
            &&(!(full_scrn&CUSTM))
            &&(!(full_scrn & MESSAGE))
#ifdef SAME_DISC_RESUME
            &&(!same_disc_flag)
#endif
            &&(!safe_on)//terry,2003/12/24 10:15PM
            &&(pe_run==1)//terry,2004/1/8 06:40PM
            )
    #ifndef MAKE_ONLY_UPDATE_CODE
        DisplayEq();
    #endif
#endif//#ifndef  DYNAMIC_SPECTRUM
    
#ifdef PORTABLE_DVD //Jack open for all 04/06/03
  check_portable_gpio();
#endif

#endif//SDRAM_16Mb_Mode
    
#ifdef ALCO_PORTABLE
  check_alco_portable_gpio();
#endif

#ifdef SUPPORT_REP_READ //Maoyong 2004.06.07
    DisplayReadEq(uReadEqType, READ_REGION);
#endif
    
    disp_fan_in();
#ifdef CD_PLAYER        //liweihua 2003-9-3
    if(cd_type_loaded==CDDA
        &&(!(full_scrn & PROGRAM))
        &&(!(full_scrn & SOUND))
        &&(!(full_scrn & SETUP))
        &&(!(full_scrn & MESSAGE))
        )
    {   
        DisplaycdEq();
    }
#endif//#ifdef CD_PLAYER 
//#if defined(SUPPORT_VFD)||defined(USE_VFDPORT_TO_KEYLIGHT_GBM)||defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ)

#if !defined(DP3240_KEY_SCAN) &&  !defined(DP2070_KEY_SCAN)
//for jieke's led pannel wangfeng 2003-11-19 19:07
#if defined(SUPPORT_VFD)||defined(GPIO_KEY_LIGHT)//NONO 3-8-18 14:39
    polling_vfdr();
#endif
#endif


// mimitsai, move to polling_100ms
#ifdef DP3240_KEY_SCAN  //1//ndef JIEKE_PANNEL_GK3800
static UINT32 wsf;
//for jieke's led pannel wangfeng 2003-11-19 19:07
#if defined(SUPPORT_VFD)||defined(GPIO_KEY_LIGHT)//NONO 3-8-18 14:39
    if( wsf & 0x03 )polling_vfdr();
    wsf++;
#endif
#endif

#if (defined(SPHE1000)&&defined(DVB_SETUP)&&defined(DMA_DVD)&&!defined(DVB1000_NON_OS))//whzhang add,kehw modify fixbug:
    VfdInfo2Linux();
#endif

#if defined(PCM1742)&&defined(CHECK_DAC_ZERO_FLAG_TO_GPIO_MUTE)     //gerry,3-10-20 11:28
    //printf("=====================polling mute===================\n");
    check_pcm1742_zero_flag();
#endif

#ifdef MINTON_STOP_MUTE//nono 2003-10-17 22:38
                if(
                    (play_state!=VCD_STATE_IDLE)
                    &&(play_state!=VCD_STATE_READTOC)
                    &&(play_state!=VCD_STATE_OPEN)
                    &&(play_state!=VCD_STATE_CLOSE)
#ifndef HUAJIA_DVD
                    &&(play_state!=VCD_STATE_STOP)

                    &&(system_state!=SYSTEM_NODISC)
#endif

                  )
                    GPIO_DEMUTE();
                else
                    GPIO_MUTE();   // mute
#endif//#ifdef MINTON_STOP_MUTE


#ifdef PROVIEW_GPIO_KEY
    Polling_VFDPanlBtm_2();
    update_vfd_data();
#elif 0//defined(USE_VFDPORT_TO_KEYLIGHT_GBM)   
    check_gbm_keylight_status();
    
#endif


    #ifdef TOP_DOOR_LOADER
    if (system_state != SYSTEM_IDLE) {
        extern UINT32 save_srn_start_t;
        extern UINT8 power_on;

        bDoorStatus = GPIO_GET_DOOR_STATUS();
        if ( (!CDOpened()) && (bDoorStatus==DOOR_OPEN) ) {
            call_ir_func(IRC_EJECT);
/*          
            if ( (full_scrn&SETUP) || (full_scrn&CUSTM) ) {
                ExitSetupPage(1);
            }
            bDoorStatus = GPIO_GET_DOOR_STATUS();
            if (bDoorStatus==DOOR_OPEN) {
                user_mute = 0;
                if ( (full_scrn&PROGRAM) || (prog_cnt && Is_JPEG_PLAY_STATE() ) ) 
                {
                    prog_cnt = 0; //disable prog function when we enter program page again
                    full_scrn = 0;
                    ClearOsdMsg(1);
                }
                save_srn_start_t = get_rtc_val();
                safe_srn_forceOFF();
                safe_srn_off();
                ircmd_trayout();
            }*/
        } else if ( CDOpened() && (bDoorStatus!=DOOR_OPEN) ) {
/*            bDoorStatus = GPIO_GET_DOOR_STATUS();
            if (bDoorStatus!=DOOR_OPEN) {
                save_srn_start_t = get_rtc_val();
                safe_srn_forceOFF();
                safe_srn_off();
                ircmd_trayin();
                if (!user_mute) AudioSetVolume(audio_volume);
            }*/
            call_ir_func(IRC_EJECT);
        }
    } //if (system_state != SYSTEM_IDLE) {
    #endif //#ifdef TOP_DOOR_LOADER

    //
    // only enable this when upgrading!!
    #ifdef SUPPORT_UART_UPGRADE
    #ifdef DVDRELEASE // we don't support this in debug mode.
    if (pollingUARTRx()) // check flash upgrade header (uart)
        DoMoveUARTRxData();
    #endif //DVDRELEASE
    #endif //SUPPORT_UART_UPGRADE

    #ifdef SUPPORT_UART_COMMAND //kenny for support to communicate with external MCU
    #ifdef DVDRELEASE // we don't support this in debug mode.
    if (pollingUART51())
        do_uart_command();
    #endif //DVDRELEASE
    #endif //SUPPORT_UART_COMMAND

    #if 0//def ROTARY_VOLUME
        polling_rotary();
    #endif

    #ifdef USE_HDD
       hd_pump();
    #endif
    
    #ifdef SHOW_STANDBY_TIMER //suqiaoli 2003-8-7
        polling_setup_standby_timer();
    #endif

    #ifdef MESSAGE_QUEUE // 2004AUDDRV::MESSAGE_QUEUE
        AUDIF_Polling_MQ();
    #endif    
    
    #if defined(SUPPORT_DSPMUTE)&&defined(USE_GPIO_MUTE) //2005 4/21 kenny add and mark some things
        
		count_dsp_mute_flag();
        
        if ( ((get_dsp_mute_flag_count()&0x100)==0x100)  
        	#ifdef MIC_MUTE_PIN   // lxg 2006-7-18 09:29
        	   || (mic_mute_flag=0)
        	#endif
        	 )     
        {
            set_dsp_mute_flag_count(0); //ycwen 2005/10/13 : for quickly mute->demute->mute, this flag may be wrong if we don't not reset it.
            GPIO_DEMUTE(); 
        }   
    #endif
     
    #ifdef PANEL_VOLUME_ENCODER//chenzhao20060117
        VolumeEncoder();
    #endif
    
     
}

static inline void polling_io_ph(void)
{
    #ifdef NEW_HOBOVFD
    Polling_VFDPanlBtm();
    #endif

    #ifdef TAS3001_AMP
    PollingTi3001_I2c();//jason 2-10-7 13:09
    #endif

    #ifdef PMP_DVD 
    extern UINT8 PMP_ENABLE;
     if(PMP_ENABLE)
      PMP_PC_Usb_PlugInOut();
    #endif //#ifdef PMP_DVD 
    #ifdef SUPPORT_CARD_STORAGE
        polling_card_plug();
    #endif //SUPPORT_CARD_STORAGE
    #if defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
       	#ifndef SP1000_NO_DVD
    		//In USB mode.
    		#if defined( SUPPORT_DVD_DVB_MODE_NOT_CHECK_USB)&&defined(IR_SWITCH_DVD_USB_CARD_AVIN_DVB)
			if((source_play_mode==USB_PLAY_MODE)||(source_play_mode==CARD_PLAY_MODE))
			#endif //endif => #ifdef SUPPORT_DVD_DVB_MODE_NOT_CHECK_USB
        		polling_storage();  //wthsin,2004/4/12 02:16pm
		#else        	
        	if(system_state != SYSTEM_TS) // houyiwu 2005/4/28 for USB mode only.
        	{
        		//In USB mode.
        		polling_storage();  //wthsin,2004/4/12 02:16pm
        	}// If the system state is in TS mode(DVB)then no need to polling USB device.
		#endif        	
    #endif 
    
}

#ifdef SUPPORT_STATION_INPUT  /*huziqin changed 2004-7-21*/  
extern void vfd_set_char(BYTE start_byte,char s);
extern void polling_vfdtime(int diff);
/*********************
Changed by xyy 2004-5-24
**********************/
extern BYTE search_station;
extern BYTE write2mem;
void polling_stationNm_input(void)
{
//      if(tuner.memory_status == MEM_MODE)
    if(tuner_oper_mode == RECALL_OR_STORE)
    {   
//      if(station_input_index == 1 && tunerCounter==8000)
//          erase_vfd_mem();
//      memset(linebuf,0,sizeof(linebuf)); 
/*      if(station_input_index == 1 && timeout_vfd<=2000)
        {   
            if(tuner.bandswitch) 
            {
                psprintf(RegionValStr[2],"%d%d %03d KHZ",stationNm/10,stationNm%10,(tuner.ambak>>4)*3-450); //ITEM number
            }
            else
            {
                int x=tuner.fmbak*5-1070;
                psprintf(RegionValStr[2],"%d%d %d.%02d MHZ",stationNm/10,stationNm%10,x/100,x%100); //ITEM number
            } 
//          vfd_set_str(0,linebuf);
#ifdef TP6311_DRIVER_VFD    //xyy 2003-11-6 13:23       
            vfd_set_char(6,stationNm/10+0x30);
            vfd_set_char(9,stationNm%10+0x30);
#endif

#ifdef XINGQIU_RECEIVER_PANNEL//xyy 2004-5-24
            vfd_set_char(27,stationNm/10+0x30);
            vfd_set_char(24,stationNm%10+0x30);
#endif
            PrintOsdMsg(STR_OS_SPACE,0x2,0,1);
        }   
*/  //marked by xyy 2004-5-24 15:56
        if(timeout_vfd <= 0)
        {
            tuner_oper_mode = NORMAL_TUNE;
        if(search_station==1)
        {
            search_station = 0;
            if(tuner.bandswitch)//am
                tuner.amfreq[tuner.am_ch]=tuner.ambak;
            else
                tuner.fmfreq[tuner.fm_ch]=tuner.fmbak;
            save_tuner_E2PROM();
        }
        else
        {
            if(tuner.bandswitch)//am
                set_station(tuner.am_ch);
            else
                set_station(tuner.fm_ch);
        }
                
            tunerflag = 1;
        }
    }
}
#endif

#ifdef   MP3_TXT_DISPLAY//10ms interval zhaoyanhua add 2003-8-27 10:36
extern  void polling_10ms_show_MP3Lycris(void);
#endif

static inline void polling_correct_osd(void)
{   
   if(cd_type_loaded==CDDVD)
   {
     UINT8 *p = (UINT8 *)(SDRAM_BASE+(regs0->osd_base_addr<<10));   
          
     if( !((*p==0xc0)||(*p==0x80)||(*p==0x81)) )
     {      
      printf("p:%x *p:%x %x %x t_disp:%x\n",p,*p,regs0->osd_base_addr,regs0->osdya,t_disp);
      if(t_disp) t_disp+=10;
      osd_init();
     }
   }
}

#ifdef SUPPORT_MP4
static inline void polling_video_property()
{
    if (GetCurrentFileType() == CDROM_MP4)
    {
        #ifdef NOT_SHOW_MP4_ERROR_MSG_ALWAYS
        if((play_state!=VCD_STATE_MP3_FILELIST) && (play_state!=VCD_STATE_STOP))
        #else
        if(play_state != VCD_STATE_MP3_FILELIST)    //dingzhy 04-5-3 16:59 not show GMC/QPEL at filelist
        #endif
        {
            if(GET_MP4_TIME()<1)
            {//terry,2004/4/16 09:51PM
                if(IS_MPEG4_GMC()) 
                {
                	#ifdef SHOW_GMC_INFO//liumzh 2005-5-8 16:00 for eastech
                    psprintf(RegionValStr[REGION1], "GMC:UNSUPPORT FORMAT");
                    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
                    #else
                        #if !defined(HW_SUPPORT_GMC)  //since IC support GMC, no need to remind
                    psprintf(RegionValStr[REGION1], "GMC");
                    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
                        #endif  //IC_8202D
                    #endif
                }
                if(IS_MPEG4_QPEL()) 
                {
                	#ifdef SHOW_QPEL_INFO//liumzh 2005-5-8 16:00 for eastech
                    psprintf(RegionValStr[REGION1], "QPEL:UNSUPPORT FORMAT");
                    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
                    #else
                        #if !defined(HW_SUPPORT_QPEL)  //since IC support QPEL, no need to remind
                    psprintf(RegionValStr[REGION1], "QPEL");
                    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
                        #endif  //IC_8202D
                    #endif
                    
                }
#ifndef DIVX_DRM
    #ifndef SUPPORT_DIVX6  //kevinmonkey 051121 divx certification request do not show DRM characters
                if((IS_DIVX_DRM())&& (play_state != VCD_STATE_STOP)&&(pFsJpeg->gifsFuncBtn!=FS_FUNC_OTHER))   //jwk 2005-8-23 15:28
                {
                    psprintf(RegionValStr[REGION1], "DRM");
                    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
                }
    #endif  //#ifndef SUPPORT_DIVX6
#endif	// DIVX_DRM
            }
        }//if(play_state != VCD_STATE_MP3_FILELIST)    //dingzhy 04-5-3 16:59 not show GMC/QPEL at filelist
    }
}
#endif


#ifdef TURN_OFF_POWER_RESUME    //linrc modify 2004-8-4 9:22
UINT8   Resume_Record_Time;
#endif



static inline void polling_mp3_jpg_cowork(void)
{
#ifdef  MP3_JPEG_COWORK
    if(pFsJpeg->gifsFuncBtn==FS_FUNC_JPEG) 
    {
        #if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)        
        if(media_type == MEDIA_CARD)        
            polling_feed_read_data(80); //ycwen 2005/1/26 for usb Read 40K = 80 Lba
        else
        #endif
            polling_feed_read_data(20);  //ycwen : Read data to mp3 buffer when polling
    }
#endif
}

static inline void polling_tcl_pre_stop(void)
{
#ifdef PRESTOP_TCL
    if (play_state!=VCD_STATE_STOP)
        pre_stop=0;
#endif  
}


static inline void polling_osdlyric(void)
{
#ifdef SUPPORT_OSDLYRIC
    #ifdef HDD_INDEX_TEST
    if ( Is_MIDI_STATE() )
    #endif
    {
        if (bIsPureMusic)//xlluo 04-11-23
            ClsPureMUCaption();
            
        if (bMidiPlayerBoolean)
        {
            MidiOSDLyricPolling();
            MidiServMP3();
        }
    }
#endif  
}


#ifdef NEC16312SW
#define polling_nec16312_vfdsw();    polling_vfdsw();
#else
#define polling_nec16312_vfdsw();
#endif


#ifdef TTE_HOST_DVD  
#define polling_tte_I2C();  polling_I2C();  
#else
#define polling_tte_I2C();    
#endif

#ifdef HDMI
#define polling_hdcp(); HDCP_polling();
#else
#define polling_hdcp();
#endif


#ifdef SUPPORT_UPGRADE_WHEN_RUNNING
#define polling_upgrade_info__();    polling_upgrade_info();     //David add the following...    
#else
#define polling_upgrade_info__();
#endif
#if 0 //eric move for 05/04/29 test move before polling_10ms
extern int g_Ttx_Mode;
extern int g_EPG_Mode;
#endif

#ifdef OSD_AUTO_RECOVER
UINT32	osd_auto_recover_delay_counter = 0;
#define	OSD_AUTO_RECOVER_DELAY	30	// in units of 1 second
void polling_osd_auto_recover(void)
{
	extern	UINT32	osd_auto_recover_delay_counter;
	osd_auto_recover_delay_counter = osd_auto_recover_delay_counter + 1;
	if (osd_auto_recover_delay_counter == OSD_AUTO_RECOVER_DELAY)
	{
		osd_auto_recover();
		osd_auto_recover_delay_counter = 0;
	}
}
#endif	// #ifdef OSD_AUTO-RECOVER

#if defined(SUPPORT_8202_DVB)||defined(OSD_AUTO_RECOVER)
static inline void polling_1s(void)
{
    #ifdef SUPPORT_CONTROL_ANT_POWER   ////yangli add for antenna  power ,2006-1-5 17:50
    polling_reset_ant_power();
    #endif

    #ifdef SUPPORT_DVB_GUI_NEW
    extern UINT8  safe_on;
    if(!safe_on)              //sunzhh add 20051027
    DVB_polling_1s();
    #endif

	#ifdef OSD_AUTO_RECOVER
	polling_osd_auto_recover();
	#endif
		
	#ifdef DVB1000_NON_OS//Just for reference /David
	int iHasTDT=0;
	iHasTDT=PollingTDT(5);//eric add 2004-12-16 15:12 use Demux channel 5
	#ifdef SUPPORT_DVB_TIMER
		PollingDvbTimer();//kehw add 2005-04-19
	#endif //SUPPORT_DVB_TIMER


	/* tcf move to dvb_polling.c 2005-11-14 11:57
	#ifdef SUPPORT_TELETEXT //Maoyong 2005-4-5 15:43
		PollingUpdateTtxTime();
		PollingDrawTtxPage();
	#endif //SUPPORT_TELETEXT
	*/

	#ifdef SUPPORT_DVB_PREVIEW_9FRAMES
		PollingPreviewSlideTime();
	#endif //SUPPORT_DVB_PREVIEW_9FRAMES

	#endif //DVB1000_NON_OS
}
#endif

static inline void polling_cpu_intr_enable(void)
{    
    if (cpu_intr_enable()==0) // check interrupt
    {   
        #ifdef  POLLING_DBG //terry,2005/4/5 06:29下午
        io_write_wait("\n\n\tERROR INTERRUPT DISABLED\n\n");        
        #endif        
    }
}

static inline void polling_dvd_hl_force_action(void)
{
    // check hl-force-action
    if(force_act_tm!=0xffffffff)
    {
        if( (HL_exist)&&(full_scrn!=SETUP) )
        dvd_hl_force_action();
    }
}

static inline void polling_system_timeout(void) 
{
    // polling system-timeout.
    if (GetIntrMask()&INTR_TIMEOUT) polling_timeout();
}


#ifdef TAS3001_AMP
#define polling_TAS3001_AMP_I2CPageWrite(); PollingI2CPageWrite(); //2002/8/21
#else
#define polling_TAS3001_AMP_I2CPageWrite();
#endif

#ifdef DVD_SERVO
#define polling_ServoDecMainLoop();     ServoDecMainLoop(); // barry add for polling servo status
#else
#define polling_ServoDecMainLoop();   
#endif


static inline void polling_vfd_stationNm_input(void)
{
#if defined(SUPPORT_STATION_INPUT)//xyy 2004-8-5
    polling_vfdtime(1);
    if(system_state== SYSTEM_DOING_TUNER)//xyy 2004-5-24
    { 
        polling_stationNm_input();      
    }
#endif
}


static inline void polling_swd_eng(void)
{
    //polling SWD callback function
#ifdef SUPPORT_PLAY_SWD
    if(START_POLLING_SWD) {polling_SWD();}
#endif
}


#ifdef ROTARY_VOLUME
#define polling_rotary__();    polling_rotary();
#else
#define polling_rotary__();
#endif

#if defined(SUPPORT_SW_OSD_SCALING)&&defined(INDIGO_STYLE_OSDUI) 
/***************************************************************************
* Function: polling_sound()   
* Purposes: Execute the every parts of ShowSoundPage() or sound_draw_key() individually.
* Description:                    
* Arguments: None
* Return: N/A
* Create: 
* Modify: robert.chang, 2006/09/18 
* Modify Purposes: Only for 8202L IC.
*                           When 3d-sound OSD is turned on or 3d-sound page switching, 
*                           it maybe cause the audio interrupted.To avoid the status,
*                           the function ShowSoundPage() and sound_draw_key() is partitioned into 
*                           several parts.Then polling_sound() will call ShowSoundPage() or 
*                           sound_draw_key()and execute the parts of it individually.
***************************************************************************/
static inline void polling_sound(void)
{
    #include "sound_def.h"
    static UINT8 sound_freq = 0;
    extern UINT8 draw_sound_flag ;
    extern UINT8 draw_sound_key_flag;  

        if(draw_sound_flag != 0) {
            if(sound_freq % 3 ==0) {
    		 ShowSoundPage();
            }
                sound_freq++;
        }
        else if(draw_sound_key_flag!=0) {            
            if(sound_freq % 3 ==0) {
    		 sound_draw_key(0, 0);
            } 
                sound_freq++;
        }        
}

#endif
    
//
// FUNCTION
// polling()
// Note: this is a very important function,pls take care performance
//
void    polling(void) 
{
 
#ifdef EN_FLASHSOUND	//add by xjliu for flash driver sound
    extern void FHServoMp3();
    extern BYTE g_bFHIsPlayStart;
    extern UINT32 g_iFHMP3Addr;
#endif
    UINT32  diff,timenow;

    // fastest polling
    // --  Note: Pls take care system performance --
    polling_mp3_jpg_cowork();
    polling_tcl_pre_stop();
    polling_osdlyric();
    polling_nec16312_vfdsw();
    polling_tte_I2C();    
    polling_ethernet_access();
    polling_dsp_dbg_fun();      // dsp debugging message
    polling_upgrade_info__();   //David add the following...    
  
    #ifdef SUPPORT_OP_FIVE_DISC  //chenzhao20060107//may need to move to 1.33ms polling
    polling_5disc_control();
    #endif
    #ifdef SUPPORT_8202_DVB
    polling_DVB_immediate(); 
    #endif 
                  
    #ifdef SUPPORT_PLAY_SWD//liweihua 2005-4-18
    polling_swd_timer();
    #endif

    // --  Note: Pls take care system performance --
#ifdef EN_FLASHSOUND	//add by xjliu for flash driver sound
    if (g_bFHIsPlayStart)
        FHServoMp3(g_iFHMP3Addr);
#endif

    timenow = regs0->stc_15_0;    
    diff = timenow-stc_polling;
    if(diff<120) return;//about 90k/120 = 1.33ms    
    stc_polling = timenow;


    // --  Note: Pls take care system performance --
    //--  1.33ms polling start --  
    polling_hdcp();             //kevin add 0923 for HDMI______8ms polling  
    polling_dvd_hl_force_action();
    polling_TAS3001_AMP_I2CPageWrite(); //polling for page write sequence
    polling_ServoDecMainLoop();   
    polling_system_timeout();
    polling_vfd_stationNm_input();
    polling_swd_eng();
    polling_rotary__();
    polling_I2C_mass_write();
    
	#ifdef SUPPORT_MP3_ENCODER
	if(deviceWriteFlag == 0)
	{
		deviceWriteFlag = FSWriteSector_handler(&DosWrite_handle);
	}
	#endif
	
	//Simon Lai -- for New FS
	fs_polling_device();
	
    //--  1.33ms polling end --     
    // --  Note: Pls take care system performance --
    
    timenow = GET_RTC_15_0();
    diff    = timenow-rtc_10ms;    
    if (diff>=1)
    {//10ms polling
       watchdog_renew(WATCHDOG_RENEW_TIME);     // (n*16)/90k, 0x3fff is about 3-second.
       polling_cpu_intr_enable(); //terry,2005/4/5 06:28下午

#if defined(SUPPORT_SW_OSD_SCALING)&&defined(INDIGO_STYLE_OSDUI)   // only for 8202L 
       polling_sound();   // for 3d-sound osd region   
#endif
       
#ifdef  SDRAM_16Mb_Mode
#ifdef  POLLING_CORRECT_OSD
        polling_correct_osd();
#endif
#endif        
 
        //10ms polling
        rtc_10ms=timenow;

        
        if (polling_avoid_reentry) return;
        polling_avoid_reentry=1;
        
        #ifdef SUPPORT_EXTERNAL_MIC
        if(extern_mic_is_detected())//kenny 2003/5/14
        {
            extern_mic_unmute();
            auto_mute_extern_mic_timer=0;
        }
        else
        {
            auto_mute_extern_mic_timer+=1;

        }

        if(auto_mute_extern_mic_timer>=200)
        {
            extern_mic_mute();
        }
        #endif

        #ifdef USE_PIN151CN_LED     //freyman 2004-3-16 11:49 for wuxi oritron
        if(system_state<=SYSTEM_READ_TITLE)
        {
            static UINT16 counter_ori = 0;
            if((counter_ori%5)==0)
            GPIO_O_SET(18,0);
            else
            GPIO_O_SET(18,1);
            counter_ori++;
        }
        else
        {
            GPIO_O_SET(18,1);
        }
        #endif        
       
        
        if(keep_cmd_code==IR_CODE_MAX_NUM)//2005/3/30 12:48下午
        {
            polling_10ms();

            // slower polling.
            diff = timenow-rtc_100ms;
            if(diff>=10)
            {//100 ms polling intrval
                rtc_100ms    = timenow;
                get_cdkit_time(CD_SS_CHANGED);

#ifdef SUPPORT_MP4
                // 2004/05/14 yltseng, move from time.c/get_cdkit_time to here
                polling_video_property();
#endif
                polling_io_ph();

                //printf("<%d>",counter_down);
                if ( (counter_down<=0)
                #ifdef NF_100//axel for seamless/non-seamless angle change 2005/5/12 
                    ||(pDSV->dAGL_Ns>1) 
                #endif
                   )        
                {
                   counter_down=-1;
                   polling_ir();
                }else
                {
                  counter_down--;
                }

                polling_osd(diff);
                polling_100ms();
                diff  = timenow-rtc_500ms;

#ifndef NO_AUDIO_DSP
                // to avoid 500 ms as a multiple of consuming speed.
                if (diff >= (UINT8)(50-dsp_delay) )
                {
                    dsp_delay = (dsp_delay + 0x2) & 0xf;
                    dsp_watchdog();
                }
#endif
                #ifdef SUPPORT_GAME_TETRIS
                TerisPolling(diff);
                #endif 
                #ifdef SUPPORT_GAME_HITRAT  //denglin@sunplus.com.cn in 20051107
               	#ifdef SUPPORT_DVD_NATIVE_GAME
                 	if(system_state == SYSTEM_DVDGAME)  //jiangxl 2006-3-20 17:20
                #elif defined(SUPPORT_DVB_NATIVE_GAME)      //added by tbdong in 20050622
            		if(system_state == SYSTEM_DVBGAME)
            	#endif  
                {
                	HitRat_Polling(diff);
               	} 
                #endif
                if (diff>=50)
                {//500ms
                #ifdef SUPPORT_OSDLYRIC
                    #ifdef SUPPORT_MIDI_MENU_SEL
                    //if (midiState == MIDI_STATE_PAYLOAD)
                    {
                       extern void Clear_TopTip(void);                   
                       Clear_TopTip();
                    }
                    #endif
                #endif
                   polling_500ms();

                   rtc_500ms = timenow;
                   #ifdef TURN_OFF_POWER_RESUME //wangap 2004/4/21  
                   if(cd_type_loaded!= CDROM)
                   {
                   Resume_Record_Time++;        //linrc modify 2004-8-4 9:22
                   diff  = timenow-rtc_60s;
                       if (Resume_Record_Time>=RECORDTIME)
                       {//1 miutme
                         polling_one_minute();
                         Resume_Record_Time = 0;
                         rtc_60s = timenow;
                       }
                   }
                   #endif  

                #if defined(SUPPORT_8202_DVB)||defined(OSD_AUTO_RECOVER)
                    diff  = timenow-rtc_1s;
                    if (diff >= 100)
                    { // 1 sec
                        polling_1s();
                        rtc_1s = timenow;
                    }
                #endif
            }
            }
        }else
        {
            UINT16 key;

            key=keep_cmd_code;
            //keep_cmd_code=0;
            keep_cmd_code=IR_CODE_MAX_NUM;//2004-3-30 19:19
            ircmd_pre_paser(key);        
        }
        
#ifdef   MP3_TXT_DISPLAY//10ms interval zhaoyanhua add 2003-8-27 10:36
    extern UINT16 MP3TotalNo;    
     
    if (  (pFsJpeg->gifsFuncBtn == FS_FUNC_MP3) 
         &&(MP3TotalNo)//to avoid when show WMA,show last MP3 lyrics.
         &&(  (play_state != VCD_STATE_STOP) 
            &&(play_state != VCD_STATE_PAUSE)))
        polling_10ms_show_MP3Lycris();
    
#endif

        polling_avoid_reentry=0;
    }
}



#ifdef NEW_HOBOVFD
#include "gpio.h"
#include "timer.h"

extern UINT32 save_srn_start_t;
extern void call_ir_func(BYTE rx);
void Polling_VFDPanlBtm()
{

 static   BYTE   same_levelContinous=0,gate=0;

 switch(gate)
   {

    case START:

      if((GPIO_I_GET(8))&&(GPIO_I_GET(9))&&(GPIO_I_GET(22))&&(GPIO_I_GET(23))&&(GPIO_I_GET(24))&&(GPIO_I_GET(25)))
       {

          if(same_levelContinous++>2)
         {
            same_levelContinous=0;
            gate=BTMDETECT;
         }
       }
       break;

    case BTMDETECT:
       if(!GPIO_I_GET(8))  { gate=BTMEJECT; break;}
       if(!GPIO_I_GET(9))  { gate=BTMPOWER; break;}
       if(!GPIO_I_GET(22)) { gate=BTMBACKWARD;
                             save_srn_start_t =  get_rtc_val();
                              break;
                          }
       if(!GPIO_I_GET(23)) { gate=BTMFORWARD;
                             save_srn_start_t =  get_rtc_val();
                             break;
                          }
       if(!GPIO_I_GET(24)) { gate=BTMSTOP; break;}
       if(!GPIO_I_GET(25)) { gate=BTMPLAY;
                           save_srn_start_t =  get_rtc_val();
                           break;
                         }
       break;
    case BTMEJECT:

       if(same_levelContinous++>2)
        {
           call_ir_func(0x0c);//ircmd_eject_toggle();
           same_levelContinous=1;
           gate=DETECTHIGH;
        }
       break;

    case BTMPOWER:

       if(same_levelContinous++>2)
        {
           call_ir_func(0x27);// ircmd_power();
           same_levelContinous=2;
           gate=DETECTHIGH;
        }
       break;

    case BTMBACKWARD:

       if(same_levelContinous++>1)
        {
            call_ir_func(0x1b);//ircmd_backward();
            same_levelContinous=3;
            gate=DETECTHIGH;
        }
      break;

    case BTMFORWARD:

        if(same_levelContinous++>1)
         {
            call_ir_func(0x1c);//ircmd_forward();
            same_levelContinous=4;
            gate=DETECTHIGH;
         }
      break;

    case BTMSTOP:

        if(same_levelContinous++>2)
         {
            call_ir_func(0x19);//ircmd_stop();
            same_levelContinous=5;
            gate=DETECTHIGH;
         }
      break;

    case BTMPLAY:

        if(same_levelContinous++>2)
        {
           call_ir_func(0x17);//ircmd_play_Resume();
           same_levelContinous=6;
           gate=DETECTHIGH;
        }
      break;

    case DETECTHIGH:

         switch(same_levelContinous)
         {
           case 1:
                 if(GPIO_I_GET(8))
                 {
                   same_levelContinous=0;
                   gate=BTMDETECT;
                 }
                  break;
           case 2:
                 if(GPIO_I_GET(9))
                 {
                   same_levelContinous=0;
                   gate=BTMDETECT;
                 }
                  break;

           case 3:
                 if(GPIO_I_GET(22))
                 {
                   same_levelContinous=0;
                   gate=BTMDETECT;
                 }
                  break;

           case 4:
                 if(GPIO_I_GET(23))
                 {
                   same_levelContinous=0;
                   gate=BTMDETECT;
                 }
                  break;

           case 5:
                 if(GPIO_I_GET(24))
                {
                   same_levelContinous=0;
                   gate=BTMDETECT;
                 }
                  break;
           case 6:
                 if(GPIO_I_GET(25))
                 {
                   same_levelContinous=0;
                   gate=BTMDETECT;
                 }
                  break;
        }
        break;

    default:
           gate=START;
      break;
   }
}
#endif


void PollingJpgVfd()
{
    #if defined(SUPPORT_VFD)||defined(USE_VFDPORT_TO_KEYLIGHT_GBM)||defined(GPIO_KEY_LIGHT)
    polling_vfdr();
    #elif defined(USE_GAMEPORT_TO_BUTTON)
    check_key_status();
    #elif defined(USE_VFDPORT_TO_BUTTON)
    check_keyboard_status();
    #elif defined(OURMIND_VFDPORT_TO_BUTTON)
    check_key_status_ourmind();
    #endif
    
    #ifdef PDVD_USE_IO_SCAN_KEY //Jack added 05/10/09
    check_portable_key();
    #ifdef ALCO_PVS8712
    check_portable_key2();//shenyj add 0928
    #endif
    #endif

    #ifdef PORTABLE_DVD
    check_portable_gpio();
    #endif
    
    #ifdef ALCO_PORTABLE
    check_alco_portable_gpio();
    #endif

    #ifdef TOP_DOOR_LOADER
    if (system_state != SYSTEM_IDLE)
     {
        extern UINT32 save_srn_start_t;
        extern UINT8 power_on;

        bDoorStatus = GPIO_GET_DOOR_STATUS();
        if ( (!CDOpened()) && (bDoorStatus==DOOR_OPEN) )
        call_ir_func(IRC_EJECT);
    else if ( CDOpened() && (bDoorStatus!=DOOR_OPEN) )
            call_ir_func(IRC_EJECT);
     }
     #endif //#ifdef TOP_DOOR_LOADER

    //bJpgVFDPause(1:PAUSE, 2:PLAY) will triggered by polling_vfdr
    if (bJpgVFDPause==1) {
        ircmd_pause();
        sys_cmd=0;
        do {
            polling();
        } while ( ( (sys_cmd==0)&&(play_state==VCD_STATE_PAUSE) ) &&
            (bJpgVFDPause==1)
            );

        if (bJpgVFDPause==2) {
            PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);
            ircmd_play();
        }
        bJpgVFDPause=0;
    }
}

#ifdef SUPPORT_FUNCTION_MENU
//Is it time to turn off the setup menu plus now??? 
//The setup menu plus showing time is 10 seconds 
void polling_setup_menu_plus(void)
{
    if(setup_menu_plus_timer > 1)
    {
        setup_menu_plus_timer--;
        #ifdef SUPPORT_DISPLAY_MENU
        if( (!(setup_menu_plus_timer%10)) && (In_Display_Menu()))
          polling_display_menu_plus();        
        #endif//end #ifdef SUPPORT_DISPLAY_MENU
    }
    else if(setup_menu_plus_timer == 1)
    {
        #ifdef DEBUG_FUNCTION_MENU
        printf("close the menu plus\n");
        #endif
        
        setup_menu_plus_timer = 0;
        if(full_scrn & SETUP_PLUS)
        ExitSetupPage(0);
    }  
}
#endif //end #ifdef SUPPORT_FUNCTION_MENU

#ifdef BRIGHTNESS_COLOR_KEY
void polling_BCtimer(void)
{
    if(BriCol_timer>1)
      BriCol_timer--;
    else if(BriCol_timer == 1)
    {
      //printf("BC adjust timeout......\n");
      osd_tog_region(1, OSD_OFF);
      timeout_osd[1] = 0;
      
      BriCol_timer = 0;
      
      //******************tell MCU**********************
      
      
      //write to 24C02
      //if(BriCol_state == BRIGHTNESS_STATE)
      //  WriteToI2c(I2C_ID_MEMORY,BRIGHTNESS_ADDR,&brightness_value,1);
      //else if(BriCol_state == COLOR_STATE)
      //  WriteToI2c(I2C_ID_MEMORY,COLOR_ADDR,&color_value,1);
      
      BriCol_state = IDLE_STATE;
    }
     
}
#endif


#ifdef SEND_BIT_RATE_TO_IOP  //wsf 040802
void send_bit_rate(void)
{             
             UINT8 send_bit=0;
             static UINT8 send_bit_total=0;
             static UINT8 send_bit_total_flag=1;
             static UINT8 send_flag=0;
             static UINT8 send_time=0;
             static UINT8 send_data=0;
             static UINT8 data_to_send [8]= {80,120,80,120,80,120,80,155};
             static UINT8 data_to_send_count;
                         
             if(send_time<3) send_bit=0;
             if(send_time==3) send_bit=1;
             if((send_time>3)&&(send_time<13)){
                send_bit_total+=send_data&0x01;
                if(send_data&0x01){
                    send_bit=0;
                    send_data&=0xfe;
                    send_flag=0;
                    send_time--;            
                }
                else{
                    if(send_flag){
                        send_bit=1;
                        send_data>>=1;                        
                        send_flag=0;                
                    }
                    else{
                        send_bit=0;
                        send_flag=1;
                        send_time--;                
                    }
                }
            }
            send_time++;    
            if((send_time==12)&&(send_bit_total_flag)){
                send_data=send_bit_total;
                send_bit_total_flag=0;
            }   
            if(send_time>13)send_bit=1; 
            if((send_time>13)&&(send_time<31))send_bit=0;
            if(send_time>30){
                send_time=0;
                send_bit_total=0;
                send_bit_total_flag=1;
                send_flag=0;
                send_time=0;                

                 if( (play_state==VCD_STATE_NORMAL)||(play_state==VCD_STATE_FASTFORWARD)
                    ||(play_state==VCD_STATE_FASTBACKWARD)||(play_state==VCD_STATE_SLOW)
                    ||(play_state==VCD_STATE_9FRAMES)||(play_state==VCD_STATE_PREVIEW)){
                    send_data=data_to_send[data_to_send_count&0x07];
                    data_to_send_count++;                    
                    }
                 else send_data=0;                
                 printf( "send_data=%d,bit_rate_val=%x ,play_state=%d\n",send_data,bit_rate_val,play_state);
         }
                GPIO_M_SET(23,1);
                GPIO_E_SET(23,1);
                GPIO_O_SET(23,!send_bit);
}
#endif 


#ifdef CHECKPHONE             ///////check phone in or out
void polling_phone(void)        /////////////yangli 2004-10-12
{
    
    
    if((phone_flag==0)&&(!GPIO_I_GET(58)))
    {
        phone_flag=1;
        AUDIF_Set_OutputMode(OUT_51Channel, 0);//2004AUDDRV AudioSetOutputMode(0x06, 0);
    }  //////0x06:5.1 channel
    
     if((phone_flag==1)&&(GPIO_I_GET(58)))
    {
        phone_flag=0;
        AUDIF_Set_OutputMode(OUT_51DownmixLtRt, 0);//2004AUDDRV AudioSetOutputMode(0x08, 0);
    }//////0x08:DownMix Lx,Rx(for ProLogic)
     if((phone_flag==1)&&(!GPIO_I_GET(58))&&(phone_flag_k<500))
    {
        phone_flag_k++;
         if(phone_flag_k==500)
            AUDIF_Set_OutputMode(OUT_51Channel, 0);//2004AUDDRV AudioSetOutputMode(0x06, 0);
       }
}
#endif

#ifdef CONTINUOUS_NUM_KEY_SELECT //Jack added 04/11/13
void polling_ir_num(void)
{
  
  ir_num_timer--;
  
  if(ir_num_timer==1)
  {
    if(ir_num_state == NUM_STATE4)
      ir_select_number = ir_num1*1000+ir_num2*100+ir_num3*10+ir_num4;
    else if(ir_num_state == NUM_STATE3)
      ir_select_number = ir_num1*100+ir_num2*10+ir_num3;
    else if(ir_num_state == NUM_STATE2)
      ir_select_number = ir_num1*10+ir_num2;
    else
      ir_select_number = ir_num1;
    
    ir_num_timer = 0;
    if(ir_select_number)    
      ir_num_select(ir_select_number);
    else
        invalid_key();  
      
      //ircmd_post_func(CMD_SELECT | (ir_select_number));
    #ifdef NEED_DIFF_IR_PANEL_KEY
    panel_key_flag = 0;
    #endif
      
    ir_select_number = 0;
    ir_num1 = ir_num2 = ir_num3 = ir_num4 = 0;  
    ir_num_state = NUM_STATE0;
  }
}  
#endif

#ifdef  TTE_HOST_DVD
void polling_I2C(void)
{
#if 1
  BYTE c = 0;
  BYTE status[MAX_I2C_SLAVE_TX_BUF_LEN];
  UINT8 info_length = 0;
  static UINT8 state = HDI_STATE_IDLE;
  
  psprintf(RegionValStr[REGION1], "TX AVAIL:%d STATE:%d", 
                                  I2C_Slave_Get_Tx_Buf_Avail(),
                                  state); 
  PrintOsdMsg(STR_OS_SPACE, REGION1, 0, 1);  
  
    psprintf(RegionValStr[REGION2], "KEY %x RI:%d RO:%d TI:%d TO:%d", 
                                c, 
                                I2C_Slave_Get_Rx_In_Ptr(), 
                                I2C_Slave_Get_Rx_Out_Ptr(),
                                I2C_Slave_Get_Tx_In_Ptr(),
                                I2C_Slave_Get_Tx_Out_Ptr());
    
    PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);    

  /* Check if got any data bytes received from the PCA9564 */
  if (I2C_Slave_Is_Rx_Buf_Empty() == FALSE)
  {
    c = I2C_Slave_Rx_Buf_GetChar();
  
    switch (state)
    {
      case HDI_STATE_IDLE :
      {
        state = Check_HDI_Command_Type(c);
        break;
      }

      case HDI_STATE_WAIT_CTL_RESERVED :
      {
        state = HDI_STATE_WAIT_CTL_CODE;
        break;
      }

      case HDI_STATE_WAIT_SYS_RESERVED :
      {
        state = HDI_STATE_WAIT_SYS_CODE;
        break;
      }

      case HDI_STATE_WAIT_INF_RESERVED :
      {
        state = HDI_STATE_WAIT_INF_CODE;
        break;
      }

      case HDI_STATE_WAIT_SET_RESERVED :
      {
        state = HDI_STATE_WAIT_SET_CODE;
        break;
      }

      case HDI_STATE_WAIT_CTL_CODE :
      case HDI_STATE_WAIT_SYS_CODE :
      case HDI_STATE_WAIT_INF_CODE :
      case HDI_STATE_WAIT_SET_CODE :
      {
        state = HDI_Process_Cmd(state, c);
        break;
      }

      default :
      { 
        state = HDI_STATE_IDLE;
        break;
      }
    }    
  }
#endif  
}

UINT8 Check_HDI_Command_Type(UINT8 c)
{
  UINT8 state;
  
  switch (c)
  {         
    /* Control Command Type */
    case HDI_CTRL_CMD_TYPE :
    { 
      state = HDI_STATE_WAIT_CTL_RESERVED;
      break;
    }
      
    /* System Command Type */
    case HDI_SYS_CMD_TYPE :
    {
      state = HDI_STATE_WAIT_SYS_RESERVED;          
      break;
    }
      
    /* Info Command Type */
    case HDI_INFO_CMD_TYPE :
    {
      state = HDI_STATE_WAIT_INF_RESERVED;                          
      break;
    }
      
    /* Set Command Type */
    case HDI_SET_CMD_TYPE :
    {
      state = HDI_STATE_WAIT_SET_RESERVED;                          
      break;
    }
      
    /* Unknown Command Type */
    default :
    {
      state = HDI_STATE_IDLE;               
      // printf("Unknown HDI command type received\n\r");
      break;
    }
  }
  
  return state;
}

UINT8 HDI_Process_Cmd(UINT8 state,UINT8 c)
{ 
  UINT8 status[MAX_I2C_SLAVE_TX_BUF_LEN];
  UINT8 info_length = 0;

  switch (state)
  {
    #if 0
    // Process Control Code
    case HDI_STATE_WAIT_CTL_CODE :
    {
   
      if (HDI_Process_Ctrl_Cmd(c) == FAILURE)
      {
        // printf("Error processing HDI control command\n\r");
      }
      break;
      
    }
    
    // Process System Code
    case HDI_STATE_WAIT_SYS_CODE :
    {
      
      if (HDI_Process_Sys_Cmd(c) == FAILURE)
      {
        // printf("Error processing HDI system command\n\r");
      }
      break;
     
    }
        
    // Process Info Code
    case HDI_STATE_WAIT_INF_CODE :
    {
      printf("Process Info Code c = %x\n\r", c);
      if ((HDI_Process_Info_Cmd(c, status, &info_length)) == SUCCESS)
      {
    /* Send the data out to the Host Chassis */
    *status = I2C_MASTER_ADDRESS;
    
    // length + 1 to include master address  
    if (I2C_Slave_Send_Data(status, info_length+1) == FAILURE)
    {
      printf("Unable to send HDI info status\n\r");
    }
    else
    {
          printf("TIN:%d TO:%d\n\r",
            I2C_Slave_Get_Tx_In_Ptr(),
            I2C_Slave_Get_Tx_Out_Ptr());        
    }   
      }
      else
      {
        printf("Error processing HDI info command\n\r");
      }
        
      break;
    }

    // Process Set Code
    case HDI_STATE_WAIT_SET_CODE :
    {
      #if 0
      // Set Command    
      if (I2C_Slave_Read_Data(status, NVM_STATUS_SIZE) == SUCCESS)  /* Get the NVM data bytes */
      {
        if (HDI_Process_Set_Cmd(c, status, NVM_STATUS_SIZE) == FAILURE)
        {
          // printf("Unable to send HDI info status\n\r");
        }
      }
      #endif
      break;
    }
    #endif
  }
  
  state = HDI_STATE_IDLE;
  
  return state;
}
#endif
#ifdef CHECK_AV_JACK//yangli add for PMP.20050426
#include "tvif.h"
void polling_av_jack(void)
{
	static int flag=0;
	static int k=0;
	if((flag==0)&&(GPIO_I_GET(2)))
	{
		flag=1;
		tv_dacoff(TV_DAC_B|TV_DAC_C|TV_DAC_D|TV_DAC_F);		
	}  
	
	 if((flag==1)&&(!GPIO_I_GET(2)))
	{
		flag=0;
		tv_dacoff(TV_DAC_B|TV_DAC_C|TV_DAC_D|TV_DAC_E|TV_DAC_F);
	}
	if((GPIO_I_GET(2))&&(k<500))
	{
		k++;
	    tv_dacoff(TV_DAC_B|TV_DAC_C|TV_DAC_D|TV_DAC_F);	   	
	 }
	
}
#endif

//////yangli move polling_pmp_mcu810 2004/12/29
