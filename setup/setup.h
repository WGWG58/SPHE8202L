//
// setup.h
//
//      define external interface of setup module
//
// notes:
//      side effect :   these function calls do synchronous IO, so if caller want to do real-time job, 
//                      please consider it's worst case(max. timeout time)
//
// history:
//  2002/02/07  : create
//

//AC3 related setting(including sperker gain, delay and Dolby digital setting)
//when we change DSP audio decoder to AC3, call this
void setup_SetAC3Config();

//DTS related setting(including sperker gain and delay)
//when we change DSP audio decoder to DTS, call this
void setup_SetDTSConfig();

//common DSP audio related setting
void setup_SetAudioConfig();

void setup_save_exit(void);

int setup_IsSet2SPDIF_Bitstream();
int setup_IsSet2SPDIF_PCM();
int setup_IsSet2SPDIF_OFF();

int setup_DTSCD_IsSet2SPDIF_PCMAndOff(void);

void setup_Set2SPDIF_PCM();

int setup_IsMICoff();

UINT32 setup_CheckPasswd();

void setup_SetKey();
void setup_SetEcho();
void setup_SetMic();

int IsOSDChinese();

int setup_IsMICOff(); //Jeff 20020524
void setup_SetMICAuto();
int setup_IsSpkSubwooferOn();//2-6-16 20:45

void setup_SetDTSCDConfig();
int setup_IsSpkDownmixOff(void);
int WillKeyShiftNotDo(void);
void setup_SetDTSDOWNMIXConfig();//nono 2003-11-24 14:47
void setup_SetAC3PCMConfig();//nono 2004-8-4 9:27

void setup_DVD3DSound(BYTE set);

UINT8 setup_GetDownmixMode(void); //wanghaoying 2003-9-11 14:12
UINT8 setup_GetPrologicII(void);    //wanghaoying 2003-9-18 11:36
int OsdIsEnglish(void);

#ifdef USE_IR_TO_CHANGE_TVTYPE
void setup_DVD_TVType(BYTE set);
#endif

int setup_IsVGAOn();	//wangfeng,2003-10-23 13:17
int setup_IsPrologicOn();	//wangfeng 2004-2-2 11:27

#ifdef USER_MPEG_LOGO
void setup_SetMPEGLogo(void);
#endif//#ifdef USER_MPEG_LOGO

#if defined(S_VIDEO_OUT)&&defined(S_VIDEO_SET_TV_DAC3_OFF)
UINT8 setup_GetVideoMode(void);
#endif

void setup_SetFreqMaskConfig(void);
void init_val_by_record(void);


#if (REGION_NUM == 0) //axel for setting default region number 2005/5/11 
#error  "illeagal region setting."
#endif

//=========================================ending========================================

