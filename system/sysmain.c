/*
** FILE
** sysmain.c
**
** DESCRIPTION
**
** sysmain.c now contains system-level init functions, which
** must resides in ROM (well, non-volatile devices that is 
** reliable through failure.)
** History:
** Terry, 2005/2/21 01:14PM , arrangement of code in sysmain.c
** 2005/09/12 yltseng, Add new structure for font
*/

#include "config.h"
#include "global.h"
#include "regmap.h"
#include "pu8560.h"
#include "reset.h"
#include "drv.h"
#include "emuio.h"
#include "kernel.h"
#include "nav.h"
#include "tvif.h"
#include "user_init.h"
#include "sinf.h"
#include "gpio.h" 
#include "LanguageUtil.h"   // 2004/09/19 yltseng
#ifdef SUPPORT_SPI
#include "spi.h"
#endif

//flash related
#include "flash.h"

#include "rommap_rom.h"

#ifdef HDMI
#include "hdmi_api.h"
#endif
#ifdef SUPPORT_RECEIVER
#include "amp_gui.h"
#ifdef ROM_EXT_POWER_ON_MUTE
#include "Rom_bus_io.h"
#endif
#endif
#ifdef USE_TLV320_ADC	//fcr 2005-11-4 17:18
	#include "tlv320_adc.h"
#endif


#ifndef DVDRELEASE
//#define SYSMAIN_DBG     1
#endif

//#define ERROR_CONCEALMENT
//#define RUN_TESTS
#ifdef RUN_TEST
#include "test_rom.h"
#endif
//#define TEST_JPEG
//#define TEST_CPPM


/*
*  Declare External Function 
*/
 


extern void ShowTitle();
extern void InitVar(void);          // in sysmain2.c
extern void set_default_value(void);
extern void ap_main(void);          //Jeff 20010717
extern int  font_decompress(void);      // in osdfont_decompress.c
extern void init_I2C_panel(void);
#ifdef AUTO_CHECK_EEPROM_ADDR   //hongfeng 2005-09-05
extern void system_eeprom_init();
extern void tuner_eeprom_init();
#endif

#define check_drv_init_flag()	(1)

/*
*  Declare External Var.
*/
#ifdef SPHE1000 //MIKEY
extern UINT8 f_drv_init; // run drv_init
extern void read_profile(void);
extern void boot_linux(void);
extern void f_ExtendGPIOall(void);

#ifndef DVB1000_NON_OS
#undef check_drv_init_flag
#define check_drv_init_flag()	(f_drv_init)
#endif //DVB1000_NON_OS
#endif

#ifdef SUPPORT_SYS_POWER_ON_WAITING_MCUINFO
    extern   void waiting_mcu_info3(void);
#endif//end=> #ifdef  SUPPORT_SYS_POWER_ON_WAITING_MCUINFO


//
//  Local Variables
//  
#ifdef BOOT_LOAD_ROMA //terry,2005/2/21 10:56AM
UINT8  start_boot_romB_intr_tbl=0;
#elif defined(BOOT_LOAD_ROMB)
UINT8  start_boot_romB_intr_tbl=1;
#endif
share       share_data;
DataSaved   *pDSV;
FSJPEGDATA  *pFsJpeg;
UINT8       srv_on          = 0;
UINT8       power_on_mute   = 1;


/*
**  INCLUSIONS
*/
// STANDARD INCLUSION
#include "sysmain_inc.h"            //terry,2004/1/28 10:24AM

#ifdef DVD_SERVO
#include "system_servo.c"
#endif
#include "system_sleep.c"
//#include "system_jpeg_logo.c" // 2004/10/07 yltseng
#include "system_util.c"
#include "system_mjpeg.c"
#include "system_mp4.c"
#include "system_game16.c"
#include "system_audio.c" //ycwen 2005/11/15 use fun pointer to make auddrv.a clear!

#include "sysmain_util.inc"
#include "sysmain_user.inc"
#include "sysmain_hd.inc"
#include "sysmain_midi.inc"
#include "system_hdmi.c"  //eric lin 2006-07-20 ,function pointer for 6500 DAC Marcovision 
//
//
// main function
//
//
int dvd_main(void)
{	   
	// **STEP0** Just booting
	sysmain_user_step0();
	// **STEP0** Just booting
	
	// setup navigation data
	pDSV    = &(share_data.DSV);  
	pFsJpeg = &(share_data.JPEG);  

#ifdef EMULATION
	setup_emu();                    // setup FPGA-emulation system related controls.
#endif
#ifdef AUTO_CHECK_EEPROM_ADDR   //hongfeng 2005-09-05
	system_eeprom_init();
	tuner_eeprom_init();
#endif   

#ifdef SUPPORT_UPD68A_READY_PIN	
	set_readypin_flag_time(2);
#endif

	// initialize system hardware.
    reset_all();
    
#ifdef SUPPORT_LINE_OUT_MUTE	
        mute_line_out();  //opv-joke: mute line out
        set_line_out_demute_flag(1);
#endif
#ifdef ROM_EXT_POWER_ON_MUTE
	rom_bus_set_io(ROM_BUS_OUT_AMP_MUTE,1);
#endif    

    #ifdef DVI_I2C_SET
    #ifdef SPHE8202
        //  i2c_init_io_risc();
        
    #else
            // select GPIO 0,1 for mips I2C tjf 04-04-29
            regs0->gpio_master[0]|=0x3; //gpio 0,1 for risc
            regs0->gpio_oe[0]|=0x03;
    #endif
#endif

#ifdef VIDEO_IN_CONTROL
   #if defined(ALCO_PV1950)||defined(ALCO_PVS19251)
    if(!(GPIO_I_GET(INT_EXT_VIDEO_GPIO1)+GPIO_I_GET(INT_EXT_VIDEO_GPIO2)))
   #elif defined(ALCO_PVS177W)||defined(ALCO_PVS1090_AVIN)//shenyj add for alco177w
    if(GPIO_I_GET(INT_EXT_VIDEO_GPIO))
   #endif
#endif
    GPIO_MUTE();                    // AUDIO MUTE: terry 20030805
    sysmain_boot_message();         // write-out copyright
    atapi_share_rom_bus();          // enable ROM-bus shared ATAPI-interface
    sysmain_init_flash();
    
    // **STEP1** After hardware reset
    sysmain_user_step1();           // USER procedure #1
    // **STEP1** After hardware reset
    
    sysmain_osd_init_font();

    sysmain_setup_errorconcealment();
    sysmain_setup_tvg();            // setup TVG function
    sysmain_load_setup();           // set/load setup menu values
    AUDIF_Init_Audio();             // init audio after setup menu is loaded
    InitVar();                      // initialize DVD navigator variables
    #ifdef SUPPORT_SYS_POWER_ON_WAITING_MCUINFO
    waiting_mcu_info3();
    #endif//end=> #ifdef  SUPPORT_SYS_POWER_ON_WAITING_MCUINFO

    // **STEP2** After setup value read
    sysmain_user_step2();           // USER procedure #2
    // **STEP2** After setup value read

    sysmain_setup_hardware(); 

#ifdef  EMU_MODE  
    UserSet.ParentalLvl=8;          // disable parental control
#endif

    sysmain_run_tests();                    // run tests if required

#ifdef DVD_SERVO
    system_init_servo_var();        // Initialize different types of loader OPU
#endif
    counter_down = 5;               // terry,2003/8/11 11:42AM,move here

    // **STEP3** Just before ATAPI initialization
    sysmain_user_step3();           // USER procedure #3
    // **STEP3** Just before ATAPI initialization

    //hdd_init();                   // initialize hd
#ifdef	DVD_SERVO
    servo_test();                   // servo/hdd/atapi/avb/cf card init...  
    if (check_drv_init_flag())
        drv_init();                 // initialize atapi
#endif	// DVD_SERVO

    // **STEP4** ATAPI is initialized, ready to jump to main-loop ****
    sysmain_user_step4();           // USER procedure #4
    // **STEP4** ATAPI is initialized, ready to jump to main-loop ****

    srv_on = 1;                     // terry: enable servo operation
    
#ifndef DVDRELEASE
    disable_uop = 0;
#endif

#ifdef LINE_IN_ENCODE
    encoder_type = real_time_encoder;
    line_in_flag = 0;
#endif

#if defined(STOP_RESUME_DVD_VCD)&&defined(DISC_ID_IN_FLASH)//move from st
    need_record = 0;
#endif    

    // jump to AP
    while (1)
    {
        ap_main();
    }
  
    return 0;
}



