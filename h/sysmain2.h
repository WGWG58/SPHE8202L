//=================================================================
//extern function decalre
//=================================================================
#ifndef __SYSMAIN2_H
#define __SYSMAIN2_H

void playmode_sel(BYTE flag); /*jhuang 2000/11/27 reduce warning*/
void stop_init(void);  /*jhuang 2000/11/27 reduce warning*/
void volume_init(void); //zyf 0-12-12 11:20 added it for user
//2004AUDDRV void init_mp3(void); //Jeff 20010806
//2004AUDDRV void init_cdda(void); //Jeff 20010717
void  state_stop_navigation(void);//terry,2003/12/29 08:32PM
UINT8 atapi_do_set_features(void);
void disc_init(void);
void    reset_sup(void);
UINT8 atapi_p_test_unit_ready(void);
UINT8 DiscType;
UINT8 atapi_p_mechanism_status(void);
//2004AUDDRV int init_audio(void);
void init_audio_dsp_coding_mode(void);
void init_ir_num(void);
//void dac_turn_on();
void init_book(void);
void __system_stop(void);
void init_tuner_io(void);
void output_vfd_msg(void);
void tuner_main(void);
void init_button_io(void);
void init_button_io_ourmind(void);
void LoadModule(UINT8 iModuleIndex);

#ifdef CD_PLAYER    //liweihua 2003-9-3
extern BYTE    CDPlayerTitle[];
#endif

//=================================================================
//extern variable decalre
//=================================================================
extern UINT8 CSSEnable;
extern UINT32 PlayBackStartLBA;
extern UINT32 PlayBackLength;
extern UINT32 read_sector;
extern UINT8 safe_on;
extern int resume_time_ourmind;
extern BYTE    DVDTitle1[];
extern BYTE    DVDTitle[];

#ifdef  SUPPORT_TWO_LOGO_FOR_DVD_DVB//tianye 200607
extern BYTE    DVBTitle[];
#endif//end=> #ifdef SUPPORT_TWO_LOGO_FOR_DVD_DVB

#ifdef PMP_UI//liweihua 2005-3-16
extern BYTE    SETUPTitle[];
#endif

//=================================================================
//define decalre
//=================================================================
#define DEV_RDY_TM            30000
#define DEV_RDY_TM_IN_SCRNER  60
//=================================================================
//global variable decalre
//=================================================================
static  const   char    copyright[] = 
#if CONFIG==CONFIG_VCD
    "Ss VCD solution \n";
#elif   OCNFIG==CONFIG_SVCD
    "Ss SVCD solution\n";
#elif   CONFIG==CONFIG_DVD
    "Ss DVD solution\n";
#else
    "WARNING: unknown configuration\n";
#endif

#ifdef CARD_MASTER //Jeff 20021206
    BYTE    idIDECard=0; //master in IDE bus
#else
    BYTE    idIDECard=1; //DVD-loader is master, IDE-Storage-Card is slave
#endif


UINT8 power_on;

const UINT8 osd_cd_id[] = 
{
      	STR_OS_SPACE,
      	STR_OS_CDDA,
        STR_OS_CDROM,
        STR_OS_VCD10,
    #if defined(SHOW_VCD_VER_INFO)||defined(SYBER_DVD)   //xulf 2003-11-18//yaowh modify for kenloon 04-08-03
        STR_OS_VCD20,
    #else
        STR_OS_VCD10,
    #endif
        STR_OS_SVCD,
        STR_OS_DVD
};


#ifdef SYSMAIN2_DBG
UINT8 old_state;
const char system_state_str[][30]=
{
  {"SYSTEM_IDLE"},
  {"SYSTEM_NODISC"},
  {"SYSTEM_OPEN"},
  {"SYSTEM_STOP"},    
  {"SYSTEM_READ_TITLE"},
  {"SYSTEM_SETUP_BROWSER"},  
  {"SYSTEM_POWER"}, 
  {"SYSTEM_BROWSE"}, 
  {"SYSTEM_PLAYGAME"},
  {"SYSTEM_FINISH"},
#ifdef SPHE1000
  {"SYSTEM_DVD"},
  {"SYSTEM_TS"},
  {"SYSTEM_FILESTREAM"},
#endif
};
#endif

#endif //SYSMAIN2_H
