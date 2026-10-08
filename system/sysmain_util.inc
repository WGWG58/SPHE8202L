//
// FILE
// sysmain_util.inc
//
#ifdef SPEAKER_CONFIG//chenzhao20060116	//zhongshan for warning 2006-2-28 18:12
    extern void set_speaker_config_default_value(void);
#endif
//
// FUNCTION
// sysmain_boot_message()
//
// DESCRIPTION
// booting message
void sysmain_boot_message(void)
{
    printf("Sunplus DVD driver " __DATE__ "\n");
    printf("FSJPEGDATA:%x DataSaved:%x\n",sizeof(FSJPEGDATA),sizeof(DataSaved));
}


//
// FUNCTION
// sysmain_load_setup()
//
// DESCRIPTION
// load setup 
static  inline  void sysmain_load_setup(void)
{
    #ifdef SPEAKER_CONFIG//chenzhao20060116
    set_speaker_config_default_value();
    #endif
    // Initialize user setup with default value
    set_default_value();

    // Load user_setup from i2c eeprom
#if defined(FORCE_REWRITE_WHEN_UPGRADE)||defined(FORCE_REWRITE_DRM_WHEN_UPGRADE)//terry,2004/1/8 05:32PM
    //nono add FORCE_REWRITE_DRM_WHEN_UPGRADE.20050525
    load_user_setup(0);  
#else
    load_user_setup();  
#endif    
#ifdef SET_TV_SYSTEM_AUTO_RIGHT_VALUE  //winking.J 2006-1-19 16:59
    setup_SetTV_auto_format();
#endif
#ifdef FORCE_RETURN_TO_DEFAULT_TV_FORMAT
    // restore default TV
    extern void setup_SetTV_default_format(void);//for warning
    setup_SetTV_default_format();
#endif//FORCE_RETURN_TO_DEFAULT_TV_FORMAT

}


#ifdef  IC_8202E
static  inline  void   sysmain_setup_vdac_current_sphe8202e()
{
    sp8200tv_setup_dac_current(
        TV_DAC_A_QUART|TV_DAC_B_QUART|TV_DAC_C_QUART|TV_DAC_D_QUART|TV_DAC_E_QUART|TV_DAC_F_QUART);
}
#endif


static  inline  void   sysmain_setup_vdac_current_sphe8202()
{
#ifdef TV_USE_HALF_SWING    
    tv_dachalf(TV_DAC_F|TV_DAC_E|TV_DAC_D|TV_DAC_C|TV_DAC_B);   // dac f/e/d/c/b half-swing
#elif defined(TV_USE_QUART_SWING)
    sp8200tv_setup_dac_current(TV_DAC_B_QUART|TV_DAC_C_QUART|TV_DAC_D_QUART);   // 8202L dac b/c/d quart-swing    
#else
    tv_dachalf(0); 
#endif
}


static  inline  void    sysmain_setup_vdac_current()
{
#ifdef  IC_8202E
    sysmain_setup_vdac_current_sphe8202e();
#else
    sysmain_setup_vdac_current_sphe8202();
#endif  
}


//
// Video DAC on/off control
//
#define tv_dac_all_on()     tv_dacoff(0)
#define tv_dac_a_only()     tv_dacoff(TV_DAC_F|TV_DAC_E|TV_DAC_D|TV_DAC_C|TV_DAC_B)
#define tv_dac_abcd()       tv_dacoff(TV_DAC_F|TV_DAC_E)
#define tv_dac_adef()       tv_dacoff(TV_DAC_C|TV_DAC_B)
#define tv_dac_def()        tv_dacoff(TV_DAC_C|TV_DAC_B|TV_DAC_A)
#define tv_dac_def()        tv_dacoff(TV_DAC_C|TV_DAC_B|TV_DAC_A)
#define tv_dac_aef()        tv_dacoff(TV_DAC_C|TV_DAC_B|TV_DAC_D)

#ifdef ALCO_PORTABLE
static  inline  void    alco_portable_video_dac_set(void)
{
#if defined(USE_035_DAC_CVBS)
    #ifdef ALCO_PVS1090_AVIN//shenyj add 12/05
        sp8200tv_setup_custom_output(TV_OUT_CScCSc);
    #else
        sp8200tv_setup_custom_output(TV_OUT_CScCCC);
    #endif
    tv_dacoff(TV_DAC_E|TV_DAC_C|TV_DAC_B);
#elif defined(USE_034_DAC_CVBS)
    sp8200tv_setup_custom_output(TV_OUT_CScCCC);
    #ifdef PORTABLE_8202D
        tv_dacoff(TV_DAC_F);
    #else
        tv_dacoff(TV_DAC_F|TV_DAC_C|TV_DAC_B);
    #endif
#elif defined(USE_0345_DAC_CVBS)
    #if defined(ALCO_PVS1262)||defined(ALCO_PVS8712)||defined(ALCO_PVS1090)//shenyj add 1102
        sp8200tv_setup_custom_output(TV_OUT_CScRGB);
    #else
        sp8200tv_setup_custom_output(TV_OUT_CScCSc);
    #endif
#endif
}
#endif//#ifdef ALCO_PORTABLE

static  inline  void    sysmain_setup_vdac_onoff_sphe8202_4dac_default()
{
#if defined (HW_HAS_6_DAC_DISABLE_2_DAC)
    tv_dac_adef();
#endif
}

static  inline  void    sysmain_setup_vdac_onoff_sphe1000()
{
    tv_dac_abcd();
}

extern UINT8 setup_GetVideoMode(void);


// 8202 4-DAC
static  inline  void    sysmain_setup_vdac_onoff_sphe8202_4dac()
{
#ifdef GBM_PORTABLE_DVD
    tv_dac_abcd();
#else
    //gerry add for gbm,when we set to S-VIDEO,tv dac3 will be off,2004-5-13 15:44
    #if defined(S_VIDEO_OUT)&&defined(S_VIDEO_SET_TV_DAC3_OFF)
        if(setup_GetVideoMode()==2)                     //default S_VIDEO out
        {
            tv_dac_aef();
            return;
        }
    #endif
        sysmain_setup_vdac_onoff_sphe8202_4dac_default();
#endif
}


// 8202 6-DAC
static  inline  void    sysmain_setup_vdac_onoff_sphe8202_6dac()
{
#ifndef SLEEP_WHEN_POWER_ON        //hq,3-11-25 22:39
    #ifndef USE_SUNPLUS_EMU_BOARD
    #ifdef SUPPORT_FUNCTION_MENU //Jack added for argus portable dvd
    #ifdef SUPPORT_SPI
        if(pdvd_mode == PDVD_MODE)
        {
            sp8200tv_setup_custom_output(TV_OUT_CScRGB);
            tv_dac_def();
            return;
        }
    #endif
    #endif
    #endif
    #ifdef GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE//gerry,2004-7-30 17:11
        tv_dac_a_only();
    #else //GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE
        tv_dac_all_on();
    #endif //GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE
#endif
}


static  inline  void    sysmain_setup_vdac_onoff_sphe8202()
{
#ifndef TVOUT6_4DAC_ON
    #ifdef TV_USE_4_DAC
        sysmain_setup_vdac_onoff_sphe8202_4dac();
    #else
        sysmain_setup_vdac_onoff_sphe8202_6dac();
    #endif
#endif

#ifdef ALCO_PORTABLE
    alco_portable_video_dac_set();
#endif
}


static  inline  void    sysmain_setup_vdac_onoff()
{
    // setup TV-encoder DAC output
#ifdef SPHE1000
    sysmain_setup_vdac_onoff_sphe1000();        // SPHE1000
#else
    sysmain_setup_vdac_onoff_sphe8202();        // SPHE8202
#endif   
}


//
// FUNCTION
// sysmain_setup_errorconcealment()
//
// DESCRIPTION
// sysmain functions
static  inline  void    sysmain_setup_errorconcealment()
{
#ifdef  ERROR_CONCEALMENT
    setup_error_mb_limit(ERROR_MB_LIMIT_NUM);        // ERROR_MB_LIMIT_NUM*16 MB default=4 
    setup_error_concealment(ERROR_CONCEALMENT_MODE);  // detect error and skip
#endif
}


//
// FUNCTION
// sysmain_setup_errorconcealment()
//
// DESCRIPTION
// sysmain functions
static inline void sysmain_init_flash(void)
{
    // Initialize flash related function pointers    
    if(get_flash_type()==PARALLEL_FLASH)
    {
        init_parallel_flash_functions();
    }    
    else
    {
        init_spi_flash_functions();
    }
}


//
// FUNCTION
// sysmain_setup_hardware()
//
// DESCRIPTION
// setup some hardware configurations
//
static  inline  void    sysmain_setup_hardware(void)
{
    sysmain_setup_vdac_current();
    sysmain_setup_vdac_onoff();
}


//
// FUNCTION
// sysmain_run_tests()
//
// DESCRIPTION
// run test programs after booting
//
static  inline  void sysmain_run_tests()
{
#ifdef  RUN_TESTS
    //tv_setup_output(TVOUT_SVIDEO);//set S-video output(composited+S-Video)(0x00:D0-D1-D2-D3=CVBS-C-Y-CVBS)
    
#ifdef  TEST_ROM
    test_rom_based_video();
#endif

#ifdef  TEST_CPPM
    test_cppm();
#endif

#ifdef  TEST_JPEG
    test_jpeg();
#endif
#endif
}


//
// FUNCTION
// sysmain_setup_tvg()
//
// DESCRIPTION
// Setup TV-Guardian function
//
static  inline  void    sysmain_setup_tvg()
{
    // For TV Guardian initialization
    #include "TVGApp.h"     
    TVGInitSystem( FALSE );
}


//
// INLINE
// sysmain_osd_init_font()
//
//
static inline void sysmain_osd_init_font()
{
#ifdef OSD_FONT_COMPRESS  
    // decompress osd font
    if (font_decompress()<0) {
        printf("***ERROR*** font de_compress fail!!\n\n");
        delay(1000);
    }
#endif

#ifdef SUPPORT_FONT_UTIL
    langInitSupportedFont();    // 2005/09/12 yltseng
#endif
}


