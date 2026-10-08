/**************************************************************************
 *                                                                        *
 *         Copyright (c) 2002 by Sunplus Technology Co., Ltd.             *
 *                                                                        *
 *  This software is copyrighted by and is the property of Sunplus        *
 *  Technology Co., Ltd. All rights are reserved by Sunplus Technology    *
 *  Co., Ltd. This software may only be used in accordance with the       *
 *  corresponding license agreement. Any unauthorized use, duplication,   *
 *  distribution, or disclosure of this software is expressly forbidden.  *
 *                                                                        *
 *  This Copyright notice MUST not be removed or modified without prior   *
 *  written consent of Sunplus Technology Co., Ltd.                       *
 *                                                                        *
 *  Sunplus Technology Co., Ltd. reserves the right to modify this        *
 *  software without notice.                                              *
 *                                                                        *
 *  Sunplus Technology Co., Ltd.                                          *
 *  19, Innovation First Road, Science-Based Industrial Park,             *
 *  Hsin-Chu, Taiwan, R.O.C.                                              *
 **************************************************************************/
/*--------------------------------------------------------------------------
|  File Name   :  reset.c
|
|  Description :   .... reset system
|                 when system need reset,it will goto the file.
|
|
|  Version    :  0.1
|
|  Rev    Date              Author(s)      Status & Comments
|-----------------------------------------------------------------------------------------
|  0.1  2004/2/7            Terry          Add DVD Preview function and re-structure code
|  0.1  2004/12/31          caoh           Add Comments
|-----------------------------------------------------------------------------------------*/

#include "config.h"
#include "regmap.h"
#include "global.h"

#include "syscfg.h"
#include "sysclk.h"

#include "load.h"
#include "macro.h"
#include "dma.h"
#include "memcfg.h"
#include "stc.h"
#include "func.h"
#include "cpu.h"
#include "intdef.h"

#include "gpio.h"
#include "uart.h"
#include "uartfifo.h"
#include "viddec.h"

#include "kernel.h"
#include "supfunc.h"

#include "hwif.h"
#include "framebuf.h"   //Jeff 20010717
#include "task.h"
#include "audio.h"
#include "lbaif.h"
#include "cs8403a.h"    //kenny
#include "dvdpe.h"
#include "preview.h"
#include "tvif.h"
#ifdef GPS_DVD
#include "io_uart0.h"
#endif
#include "test.h"
#include "sio.h"
#include "emuio.h"
#include "user_init.h"
#include "avi_if.h"
#include "file_if.h"
#include "sbar.inc"
#ifdef SERIAL_RGB
#include "srgb.h"
#include "srgb.c"
#endif 
#include "reset.h"
#if defined(PT2322)||defined(PT2320)
#include "audctrl.h"
#endif
#ifdef TAS3001_AMP    //
#include "ti3001.h"
#endif
#ifdef TAS5026_AMP    //
#include "ti5026.h"
#endif

//terry,2006/4/8 02:04下午
#if defined(IC_8202L)
//#undef DVD_SERVO  
#define __TEST_MODE
#endif

#ifndef DVDRELEASE
//#define RESET_DBG 1
//#define DRAM_TEST 1
//#define TASK_GBG  1//??
#define STAMP_UART_DBG
#endif

#define DRAM_TEST_16MB
//#define DRAM_TEST_64MB
#define BAUDRATE_DEFAULT    115200
//#define SHOW_SYSTEM_CLOCK

#ifndef DVB1000_NON_OS //David 2005-1-18 9:08
  #ifndef SDRAM_BUS_32BITS
    #ifndef SDRAM_16Mb_Mode//terry,2003/11/18 02:04PM
       #define  UART0_SHARE_WITH_UART1
    #endif
  #endif
#endif
#ifdef QSI_SHOW_ERR_RATE
    #undef  UART0_SHARE_WITH_UART1
#endif


#ifndef EMULATION
//#define SETUP_DAC
#endif


#ifdef  RESET_DBG   /* alan 02-05-24 */
//#define MONE_CHKSUM
#define MONE_CONFIG
#define reset_status_puts(s)        io_write_wait(s)
#define reset_status_puts_direct(s) io_write(s)
#endif

#ifndef reset_status_puts
#define reset_status_puts(s)        ((void)(s))
#endif

#ifndef reset_status_puts_direct
#define reset_status_puts_direct(s) ((void)(s))
#endif


//
// SPHE8202 tuning
//
#if 0
#undef  F135
#undef  F121_5
#undef  F114_75
#undef  F108
#undef  F94_5
#undef  F81
//#define F81
//#define F108
//#define F114_75
#define F121_5
//#define F128_25
//#define F135
#endif

#ifdef  SPHE8202
//#define ROM_SDRAM_SHARE_BUS //terry,2006/4/8 02:00下午,mark it
//#define SUPPORT_USB
#endif

#ifdef  SUPPORT_USB
#define USB_CONFIG_PLL
#define CLK54_USE_USBPLL
#endif

#ifdef SPHE1000
#define TIMER3_PERIOD   0.01       // in second
#define TIMER3_PRES     (SYSCLK/1000000)
#else
#define TIMER3_PERIOD   0.002       // in second
#define TIMER3_PRES     2000
#endif


//
// EPROM_WAIT_STATE
// *NOTE* ROM access time will be n+1 cycles.
//
//  value   cycle   108 94.5    81  67.5    54
//  --------------- ------------------------------- -----
//  3   4   36.8    42.33   48  59.2    74
//  4   5   46  52.91   60  74  92.5
//  5   6   55.2    63.49   72  88.8    111
//  6   7   64.4    74.07   84  103.6   129.5
//  7   8   73.6    84.66   96  118.4   148
//  8   9   82.8    95.24   108 133.2   166.5
//  9   10  92.6    105.82  123.5
//  10  11  101.9   116.40  135.8
//  11  12  111.1   126.98  148.1
//  12  13  120.37  137.57  160.49
//  13  14  129.63  148.15  172.84
//  14  15  138.89  158.73  185.19
//  15  16  148.18  169.31  197.53
//

//#undef ROM_TACC_DEFAULT
#ifndef ROM_TACC_DEFAULT
#define ROM_TACC_DEFAULT    85
#endif

#define SYSCLK_CYCLE    ((unsigned)(1.0E9/SYSCLK))      // in ns unit
#define ROM0_TACC       ROM_TACC_DEFAULT
#define ROM1_TACC       ROM_TACC_DEFAULT
#define ROM2_TACC       ROM_TACC_DEFAULT
#define ROM3_TACC       ROM_TACC_DEFAULT

#define ROM0_WAITST     (SYSCLK_CYCLE/ROM0_TACC)
#define ROM1_WAITST     (SYSCLK_CYCLE/ROM1_TACC)
#define ROM2_WAITST     (SYSCLK_CYCLE/ROM2_TACC)
#define ROM3_WAITST     (SYSCLK_CYCLE/ROM3_TACC)

#ifndef DVDRELEASE
#define SUPPORT_UART0_INTR
//#define SUPPORT_UART1_INTR
#define write_stamp(n)  (regs0->stamp = (n))
#endif

#ifdef STAMP_UART_DBG
#include "uartsup.h"
#undef	write_stamp
#define	write_stamp(n)	do { UART0_puthex(n); UART0_puts("\n");delay_1ms(10);} while (0)
#endif

#ifndef write_stamp
#define write_stamp(n)  ((void)0)
#endif

enum    {
    STAMP_RESET_START           = 0x01,
    STAMP_RESET_SYSTEM,
    STAMP_CHANGE_SYSCLK,
    STAMP_LOAD_MODULE_OTHER,
    STAMP_LOAD_MODULE_CDROM,
    STAMP_DISABLE_VIDEO,
    STAMP_ENABLE_INTR_0,
    STAMP_RESET_WATCHDOG,
    STAMP_LOAD_MODULE_MPEG,
    STAMP_LOAD_MODULE_AP,
    STAMP_LOAD_MODULE_AP2,
    STAMP_LOAD_MODULE_FREE,
    STAMP_RESET_OSD,
    STAMP_CONFIG_MEMORY,
    STAMP_ENABLE_INTR_1,
    STAMP_RESET_FINISHED,
    STAMP_LOAD_MODULE_DVB //terry,2005/10/13 01:32下午
};


//function declare
extern void dac_setup();
extern void reset_iop();
extern void reset_vfd(void);

// sysmain.c
extern void LoadModual(UINT16 iModuleIndex);

// crt0.S
extern void set_sdram_timing_low(void);
extern void set_sdram_timing(void);

extern void volume_init(void);
extern void AUDIF_Init_Audio_HW(void);
//
#ifdef SPHE1000
extern void msg_init(void);
extern void reset_gpio_1000(void);
#endif

#if defined(PORTABLE_DVD)||defined(ALCO_PORTABLE_DVD_8202D_DVB)
extern int is_iop_ready(void);
#endif

//servo
extern void ServoDecInit(void);
extern void ResetInterfaceProc(void);

            
// current file
UINT32 rom_checksum(void);
int reset_change_sysclk(void);
int reset_change_sysclk_27M(void);
int change_system_clock(int);
void config_cs4360(void);
void tcl_standby_gpio_ctrl(void);

#ifdef CS8403_ENABLE
//extern void init_cs8403a__(void);
#include "cs8403a.c"
#endif

/**************************************************************************
 *  Function Name: config_video_framerate_ctrl                            *
 *  Purposes:                                                             *
 *      config video frame rate control mode                              *
 *  Descriptions:                                                         *
 *      Video frame rate control                                          *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
void config_video_framerate_ctrl()
{
    int flag=0;
#ifdef FRCTL_MP2_ALWAYS_INTERLACED
    flag |= FRCTL_MP2_ALWAYS_INTERLACED_FLAG;
#endif
    frctl_setup_mode(flag);
}

/**************************************************************************
 *  Function Name: config_vpp_par                                          *
 *  Purposes:                                                             *
 *      config vpp_par_mode                                               *
 *  Descriptions:                                                         *
 *      VPP Pixel Aspect Ratio                                            *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
void config_vpp_par()
{
    int flag=0;

#ifdef PAR_MP_FORCE_SQUARE
    flag |= VPP_PAR_MP_FORCE_SQUARE;
#endif
#ifdef PAR_MP4_FORCE_SQUARE
    flag |= VPP_PAR_MP4_FORCE_SQUARE;
#endif
#ifdef PAR_MP4_GUESS_43TV
    flag |= VPP_PAR_MP4_GUESS_43TV;
#endif
#ifdef PAR_MP4_REVERSE_169TV
    flag |= VPP_PAR_MP4_REVERSE_169TV;
#endif

#ifdef PAR_MP4_PARTIAL_169TV
    flag |= VPP_PAR_MP4_PARTIAL_169TV;
#endif

    setup_vpp_par_mode(flag);
}

/**************************************************************************
 *  Function Name: reset_system                                           *
 *  Purposes:                                                             *
 *   1. setup register file pointer (regs0 / s6)                          *
 *   2. reset/enable hardware modules                                     *
 *   3. setup watchdog/scrambling                                         *
 *   4. setup rom1/2/3 bases                                              *
 *   5. setup ROM/FLASH interface                                         *
 *   6. setup system-bus arbitrator                                       *
 *   7. reset audio                                                       *
 *  Descriptions:                                                         *
 *    reset following subsystems to a known state                         *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
void
reset_system(void)
{
#if defined(MP_BOARD_216_PIN_NON_SHARE) && defined(SUPPORT_6500) && defined(SUPPORT_SPI_FLASH)
	regs0->RF_SPI_CFG0 |= 1 << 6;	// for use SPI flash, ronnie
#endif
	
	// setup register file pointer (regs0 / s6)
	InitRegFile();

    regs0->emulation    = 0;        // disable emulation functions
    regs0->reset        = 0x0000;   //
  
#ifdef SUPPORT_PIN189_AS_ROM_A20   // 8202A-256 pin189 set to RA20(default GPIO103),   //chyeh
                                   // To be RA20,pin189 must pull down(1K ohm) in PCB
	regs0->sft_cfg20 |= (0x1 << 9);   
#endif    

#ifdef SPHE1000
    regs0->reset2	|= 0x2080;	// (boot-strap / tdm / cddsp)
#else
    regs0->reset2	 = 0x3080;	// (boot-strap / tdm / cddsp)
#endif
    regs0->clken0	 = 0xff7f;	// (grfx)
    regs0->clken1	 = 0xffff;	// ()
    regs0->gclken0	 = 0xffff;
    regs0->gclken1	 = 0xffff;

    // [15:13] atg
    // [7:6] dtg
    // [1:0] watchdog
    regs0->lbc_watchdog = 0x03;     // disable watchdog/tog

    // setup rom1/2/3 bases
#ifdef SPHE1000 //MIKEY 2004.05.25
	regs0->rom1_base      = 0x00800000 >> 16;       // rom1 m*64k-base  8MB
	regs0->rom2_base      = 0x01000000 >> 16;       // rom2 n*64k-base 16MB
	regs0->rom3_base      = 0x02000000 >> 16;       // rom3 n*64k-base 32MB
#else
	regs0->rom1_base      = 32;       // rom1 m*64k-base
	regs0->rom2_base      = 32;       // rom2 n*64k-base
	regs0->rom3_base      = 32;       // rom2 n*64k-base
#endif

#define VPP_CONFIG1_URGE_EN     (1<<4)//terry,2->4
#define VPP_CONFIG1_URGE_DIS    (0<<4)
#define VPP_CONFIG1_MB45        0       // 720
#define VPP_CONFIG1_MB64        1       // 1024
#define VPP_CONFIG1_MB22        2       // 352
#define VPP_CONFIG1_MB30        3       // 480

	regs0->mc_mbwidth	= 45;
	regs0->vpp_config1	= VPP_CONFIG1_URGE_DIS|VPP_CONFIG1_MB45;
	
	vpp_zoom_max = VPP_ZOOM_MAX;

	//
	// setup ROM/FLASH interface
	regs0->rom_config = 0xf000;     // always no pre-fetch


	{
		unsigned u;
		u = (ROM0_TACC/SYSCLK_CYCLE) | ((ROM1_TACC/SYSCLK_CYCLE)<<8);
		regs0->wait_cyc1_0 = u;
		u = (ROM2_TACC/SYSCLK_CYCLE) | ((ROM3_TACC/SYSCLK_CYCLE)<<8);
		regs0->wait_cyc3_2 = u;
	}

	//
	// setup system-bus arbitrator
	{
		unsigned i;
		for (i=0;i<sizeof(sbar_prr)/sizeof(sbar_prr[0]);i++)
		    regs0->sbar_prr[i] = sbar_prr[i];
		
#ifdef	SUPPORT_DVB
		regs0->sbar_prr[13] = 0x1;
#endif	//SUPPORT_DVB
    }

#ifdef	HW_SWITCH_VPP_OSD_PRIORITY
	#ifndef	IC_1002
	regs0->sbar_config = 1;
	#endif	// IC_1002
#endif	// HW_SWITCH_VPP_OSD_PRIORITY

#ifndef NO_AUDIO_DSP
	// audio
	regs0->aud_reset = 1;
	regs0->aud_reset = 0;
#endif
}


#ifdef  MONE_CHKSUM
/**************************************************************************
 *  Function Name: rom_checksum                                           *
 *  Purposes:                                                             *
 *    At present, the funtion don't used                                  *
 *  Descriptions:                                                         *
 *    calculate rom check-sum (of first 512kbyte)                         *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
UINT32
rom_checksum(void)
{
    int i;
    UINT32 chksum=0;
    UINT32 *p = (UINT32 *)(ROM_BASE_CACHED);
    for (i=0;i<(512*1024/4); i++)
    {
        chksum += *p++;
    }
    return chksum;
}
#endif


#ifdef BOOT_LOAD_ROMA//terry,2006/4/8 02:03下午
#include "reset_boot_roma.c"
#endif

/////////////////////////////////////////////////////////////////////////////////////
// reset kernel
void reset_kernel()
{
    int chip_flag = 0;

	// load compile settings
    // 1. set chip version to kernel
#ifdef  IC_8202E
    chip_flag |= CHIP_8202E;
#elif defined(IC_8202D)||defined(IC_8202L)||defined(IC_8203A)
    chip_flag |= CHIP_8202D;
#endif
    SET_CHIP_VERSION(chip_flag);

	// 2. set sdram bus to kernel
	extern UINT8 half_pix_deinterlace;
#ifdef	SDRAM_BUS_32BITS
	half_pix_deinterlace = 0;
#else
	half_pix_deinterlace = 1;
#endif

	// hw related initializations
	kernel_init();

	// fw related initializations
    config_video_framerate_ctrl(); // Video frame rate control

    config_vpp_par(); // VPP Pixel Aspect Ratio

	// kernel customization, load kernel settings
	extern UINT32 vbv_h_var;
    vbv_h_var = VBV_H;
}

// End - reset kernel
///////////////////////////////////////////////////////////////////////////////////////////////

/**************************************************************************
 *  Function Name: init_timer                                             *
 *  Purposes:                                                             *
 *   1. setup STC 90kHz                                                   *
 *   2. setup RTC 100Hz                                                   *
 *   3. setup regs0->timer0_ctrl                                          *
 *   4. setup timer2                                                      *
 *   5. setup timer3                                                      *
 *  Descriptions:                                                         *
 *    reset following subsystems to a known state                         *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
void    init_timer(void)
{
  // setup STC 90kHz
#if defined(SPHE8202) || defined(SPHE1000)
  regs0->stc_divisor    = (1<<15) | (150-1);
#else
  regs0->stc_divisor    = STC_DIVISOR;
#endif

  // setup RTC 100Hz
  regs0->rtc_divisor    = 900-1;
//terry,2004/2/17 06:08PM
//if defined "SHOW_STANDBY_TIMER",timer0 would be used.suqiaoli modified 2004-2-26
#if (defined(DVDRELEASE)|| !defined(TASK_GBG))&&!defined(SHOW_STANDBY_TIMER)
     regs0->timer0_ctrl    = TIMER_CONFIG_STOP;
#else
  #ifdef DVD_SERVO
     #ifdef EMU_MODE
        regs0->timer0_ctrl    = TIMER_CONFIG_1ms;
     #else
        regs0->timer0_ctrl    = TIMER_CONFIG_10ms;
     #endif
  #else
     regs0->timer0_ctrl    = TIMER_CONFIG_4ms;
  #endif


#endif
//huziqin 2006-4-19 removed it.we start timer in tuner_main()
  #ifdef SUPPORT_DVB_BOOKING     ////YANGLI MOD FOR ,2006-6-8 14:06
   regs0->timer1_ctrl    = TIMER_CONFIG_10ms;    
  #else
  regs0->timer1_ctrl    = TIMER_CONFIG_STOP;
  #endif 


  regs0->timer2_reload  = 0x4;
  regs0->timer2_divisor = 0xffff;
  regs0->timer2_ctrl    = 0;                // stop: this timer is used in performance meter

  regs0->timer3_reload  = (unsigned)((TIMER3_PERIOD*SYSCLK)/TIMER3_PRES) - 1;
  regs0->timer3_divisor = TIMER3_PRES-1;
  regs0->timer3_ctrl    = 3;                // go and reload
}




//
// FUNCTION
// reset_all
//
// DESCRIPTION
// reset all, including some interface.
//
// *DISABLE INTR
// *REGF + ROMIF setup
// *EMUIO/UART setup (interrupt not yet enabled)
// *APLL setup (before GPIO for correct XCK)
// *GPIO setup
// *SDRAM size setup
// *TIMER setup
// *SDRAM memory mapping configuration
// *VIDDEC
// *SUP
// *MULTI-TASK
// *ENABLE INTR
// *IOP
// *IR      (iop)
// *VFD     (iop)
// *TV-encoder  (iop)
// *DAC     (iop)
//
//
/**************************************************************************
 *  Function Name: reset_all_enter                                        *
 *  Purposes:                                                             *
 *   1. disable CPU-level intr_enable                                     *
 *   2. disable watchdog                                                  *
 *   3. write stamp Start                                                 *
 *  Descriptions:                                                         *
 *    reset Start                                                         *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/

static void
reset_all_enter(void)
{
    // disable CPU-level intr_enable
    cpu_intr_disable();

    // disable watchdog, we are about to reset all sub-systems
    watchdog_onoff(0);

#ifdef  UART0_SHARE_WITH_UART1
	extern void sft_uart0_share_uart1_pins();
	sft_uart0_share_uart1_pins();
#endif

#ifdef  UART_SWAP //axel swap uart0 and uar1 2004/10/29
	sft_uart_swap();
#endif

    write_stamp(STAMP_RESET_START);
}

/**************************************************************************
 *  Function Name: reset_all_exit                                         *
 *  Purposes:                                                             *
 *   1. report fpga/sdram/rom/anchors                                     *
 *   2. test sdram                                                        *
 *   3. write stamp finished                                              *
 *  Descriptions:                                                         *
 *      reset Finished                                                    *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
extern int check_chipinfo(int n);
static void
reset_all_exit()
{
    //
    // report/testing
    //
#ifndef DVDRELEASE
//    report_fpga_status();
//    report_sdram_parameter();
//    report_rom_parameter();
//    report_anchors();
#endif

#ifdef  DRAM_TEST
#include "tstsdram.c"//4-3-30 21:40
    test_sdram();
#endif

    //
    // finished
    //
    write_stamp(STAMP_RESET_FINISHED);

    //
    // extra license check, don't remove (potatooo)
    if (check_chipinfo(4)==0) return;
}


/**************************************************************************
 *  Function Name: reset_all_enable_intr_only_uart                        *
 *  Purposes:                                                             *
 *   1. reset interrupt flags                                             *
 *   2. INTERRUPT for bootstrap is initialized                            *
 *   3. enable CPU-level intr_mask (IP2/IP3)                              *
 *   4. enable CPU-level intr_enable                                      *
 *  Descriptions:                                                         *
 *      Currently only UART is enabled during bootstrap (if required).    *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
static void
reset_all_enable_intr_only_uart()
{
    //
    // reset interrupt flags
    regs0->intr_flag        = -1;
    regs0->intr1_flag       = -1;

    //
    // INTERRUPT for bootstrap is initialized here.
    // Currently only UART is enabled during bootstrap (if required).
    //
    regs0->intr_mask = 0
#ifdef  SUPPORT_UART0_INTR
        | INTR_UART0_INT
#endif
#ifdef  SUPPORT_UART1_INTR
        | INTR_UART1_INT
#endif
        ;

    regs0->intr1_mask = 0;

    cpu_set_intr_mask((1<<2)|(1<<3));       // enable CPU-level intr_mask (IP2/IP3)
    cpu_intr_enable();                      // enable CPU-level intr_enable
}

/**************************************************************************
 *  Function Name: reset_all_enable_intr_all                              *
 *  Purposes:                                                             *
 *   1. reset intr_flag (bitwise-clear-upon-write-1)                      *
 *   2. reset intr_mask                                                   *
 *  Descriptions:                                                         *
 *      enable normal interrupt processing                                *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
static void
reset_all_enable_intr_all(void)
{
    //
    // reset intr_flag (bitwise-clear-upon-write-1)
    regs0->intr_flag        = -1;
    regs0->intr1_flag       = -1;

#ifndef DVDRELEASE
    regs0->sdctrl_int       = 0;
    regs0->sdctrl_int_mask  = 0x80; // sdram over-range
#endif

    // reset intr_mask
    regs0->intr_mask  = 0
        | INTR_FIELD_END | INTR_FIELD_START | INTR_PIC_END
        | INTR_RI_WATCHDOG
        | INTR_DECERR
        | INTR_TIMER0
        | INTR_TIMER1
#if defined(SPHE1000) && defined(SUPPORT_USB)
        | INTR_USB
#endif
#ifdef  SUPPORT_UART0_INTR
        | INTR_UART0_INT
#endif
#ifdef  SUPPORT_UART1_INTR
        | INTR_UART1_INT
#endif
#ifdef SUPPORT_UART_UPGRADE
        | INTR_UART1_INT // for performing flash upgrading via UART
#endif
#ifdef SUPPORT_UART_COMMAND //kenny support uart to communicate with external MCU
        | INTR_UART1_INT // for uart command
#endif
#ifdef DVD_SERVO
        | INTR_H_PIO_INT
#endif
#ifdef STB_2_0
        | INTR_RISC_INT3
#endif


#ifdef DVD_SERVO
        | INTR_SRV_INT3
        | INTR_SRV_INT2
        | INTR_SRV_INT1
        | INTR_SRV_INT0
#endif

            ;

  regs0->intr1_mask  = 0
        | INTR1_LSWITCH_INTR_FLAG   // lswitch watchdog
#ifdef DVD_SERVO
        | INTR1_TIMER3B             // timer for servo use
#endif
        | INTR1_TIMERW              // timer of watchdog
#ifndef DVDRELEASE
#ifdef ENABLE_SDRAM_OV_RANGE_INTR
        | INTR1_SD                  // sdram-controller out-of-range
#endif
#endif
#ifdef SPHE8202
        | INTR1_USB                 // USB
#endif
#if 0
        // not-used
        | INTR1_TIMER2A
        | INTR1_TIMER2B
        | INTR1_TIMER3A
#endif
            ;
}



/**************************************************************************
 *  Function Name: reset_tvdac                                            *
 *  Purposes:                                                             *
 *   1. disable video dac                                                 *
 *   2. enable osd                                                        *
 *   3. enable tv-encoder                                                 *
 *  Descriptions:                                                         *
 *      reset TV dac                                                      *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
static inline void
reset_tvdac(void)
{
#if 0
    regs0->tv_mode[5] = 0x60bf;
    regs0->tv_mode[5] = 0x003f;
    delay_1ms(1000);
#endif

    //
    regs0->vpp_bg_y     = 0x00;
    regs0->vpp_bg_cb_cr = 0x8080;
    regs0->dis_x_size = 0;
    regs0->dis_y_size = 0;

    // enable osd
    regs0->osd_mode[0]  = 0x8000;
    regs0->osd_tv_std   = 0;

    // enable tv-encoder
    regs0->tv_mode[0]   = 0x0400;
    regs0->tv_mode[2]   = 0x0000;
    regs0->tv_mode[5]   &= ~0x6080;     // enable tv-encoder

    regs0->tv_mode[5]   &= ~0x003f;     // enable DAC
#ifdef  SPHE8202
    regs0->tv_dac[0]    = (6<<6) | (6<<3) | (0<<0);
    regs0->tv_dac[1]    = (6<<6) | (6<<3) | (6<<0);
#endif
}

#if defined(DVB1000_NON_OS) && defined(SUPPORT_USB)
void reset_usb()
{
    UINT32 *iptr;

//    iptr = (UINT32*)0xbc030004;
    iptr = (UINT32*)(UHCI_CFG_BASE_VIR+4);
    *iptr = 0x1;    //??

//    iptr = (UINT32*) 0xbc030020;
    iptr = (UINT32*)(UHCI_CFG_BASE_VIR+20);
    *iptr = UHCI_IO_BASE_PHY;
    delay_1ms(1);

//    iptr = (UINT32*)0xbc020014;
	iptr = (UINT32*)(UHCI_IO_BASE_VIR+14);
    *iptr = 0x27777;

//    iptr = (UINT32*)0xbc030004;
    iptr = (UINT32*)(UHCI_CFG_BASE_VIR+4);
    *iptr = 0x0;
}
#endif //#if defined(DVB1000_NON_OS) && defined(SUPPORT_USB)

#ifdef USE_SETUP_SELECT_FONT  //liumzh 2005-11-25 20:19
static  void reset_font_map_setup()
{
	#define N_FONT_STRING_SIZE 8
	extern BYTE font_setup_map[8];
	int i,j; BYTE tp;

	for(j=0;j<N_FONT_STRING_SIZE-1;j++)  //bubble 
	{
		for(i=0;i<N_FONT_STRING_SIZE-j-1;i++)
		{
		     if( font_setup_map[i] > font_setup_map[i+1] )
		 	{
				tp = font_setup_map[i];
				font_setup_map[i] = font_setup_map[i+1];
				font_setup_map[i+1] = tp;
			}
		}
	}

	for( j=0; (!font_setup_map[0]) && (j < 8); j++ ) //move '0' to last
	{
		for(i=0;i<N_FONT_STRING_SIZE -1;i++)
				font_setup_map[i] =  font_setup_map[i+1];
		font_setup_map[N_FONT_STRING_SIZE -1] = 0;
	}
			
}
#endif

#ifdef IC_8202L
#include "reset_dvo_8202L.c"
#elif defined(IC_8203A)
#include "reset_dvo_8203A.c"
#else
#include "reset_dvo_8202.c"
#endif

#ifdef ENABLE_SSPLL
/**************************************************************************
 *  Function Name: set_sspll_reg                                         *
 *  Purposes:                                                             *
 *      setup regs0->sft_cfg24                                            *
 *      setup regs0->sysclk_sel                                            *
 *      setup regs0->pllv_cfg                                            *
 *  Descriptions:                                                         *
 *      setup SSPLL clock                                                     *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
static inline void set_sspll_reg()
{
	// fill out SSPLL MDS parameter
#if defined(SSPLL_TYPE1)
    //              CKREF_0964M  AUTO_BWS  SSPLL_MDS
    regs0->sft_cfg24 = (1<< 9) | (0 << 8) | (0x30) | SSPLL_STEP_VALUE;

    regs0->sysclk_sel = 0x83 | (1 << 4); // eanble SSPLL

    #ifdef SSPLL_F121_5
    //                   C2,	     C1	    MO_SSPLL_S  SSPLL_NS
    regs0->pllv_cfg = (1 << 13) | (1<< 12) | (6 << 8) | 0x7e;		//121MHz    type1
    #else
    // 		         C2, 	     C1	    MO_SSPLL_S	SSPLL_NS
    regs0->pllv_cfg = (1 << 13) | (1<< 12) | (6 << 8) | 0x8c;		//135MHz    type1
    #endif

#elif defined(SSPLL_TYPE2)
    //              CKREF_0964M  AUTO_BWS  SSPLL_MDS
    regs0->sft_cfg24 = (1<< 9) | (0 << 8) | (0x50) | SSPLL_STEP_VALUE;

    regs0->sysclk_sel = 0x83 | (1 << 4); // eanble SSPLL

    #ifdef SSPLL_F121_5
    // 		         C2, 	     C1	    MO_SSPLL_S	SSPLL_NS
    regs0->pllv_cfg = (1 << 13) | (1<< 12) | (4 << 8) | 0x5a;		//121MHz    type2
    #else
    // 		         C2, 	     C1	    MO_SSPLL_S	SSPLL_NS
    regs0->pllv_cfg = (1 << 13) | (1<< 12) | (4 << 8) | 0x64;		//135MHz    type2
    #endif

#elif defined(SSPLL_TYPE3)
    //              CKREF_0964M  AUTO_BWS  SSPLL_MDS
    regs0->sft_cfg24 = (1<< 9) | (0 << 8) | (0x70) | SSPLL_STEP_VALUE;

    regs0->sysclk_sel = 0x83 | (1 << 4); // eanble SSPLL

    #ifdef SSPLL_F121_5
    // 		         C2, 	     C1	    MO_SSPLL_S	SSPLL_NS
    regs0->pllv_cfg = (1 << 13) | (1<< 12) | (3 << 8) | 0x48;		//121MHz    type3
    #else
    // 		         C2, 	     C1	    MO_SSPLL_S	SSPLL_NS
    regs0->pllv_cfg = (1 << 13) | (1<< 12) | (3 << 8) | 0x50;		//135MHz    type3
    #endif
#endif

}
#else
#define set_sspll_reg()
#endif

static inline void reset_uart_func()
{
#ifdef SUPPORT_UART_COMMAND //kenny support uart to communicate with external MCU
	reset_uart();
#endif


#if defined(DVDRELEASE) && !defined(SPHE1000)
    #if defined(QSI_SHOW_ERR_RATE)
    
    UART0_set_baudrate(BAUDCC(BAUDRATE_DEFAULT, 121500000));
    psprintf(linebuf,"------------Release UART------------\n");
    UART0_puts(linebuf);
    
    #elif defined(UART_WITHOUT_DEBUG_MODE)//axel 2004/10/19 for the communication with external MCU
    
    UART0_set_baudrate(BAUDCC(9600, 121500000));
    //psprintf(linebuf,"------------Release UART------------\n");
    //UART0_puts(linebuf);
    
    #elif defined(GPS_DVD)
	
	UART0_set_baudrate(BAUDCC(56000, 121500000));//108000000));
	//EPP_PUTC_EXACT(0x22);
	//psprintf(linebuf,"---Release UART For GPS DVD---\n");
	//UART0_puts(linebuf);
    
    #elif defined(ENABLE_UART0_IN_RELEASE_MODE)
    
    //psprintf(linebuf,"------------Release UART------------\n");
    //UART0_puts(linebuf);

    #else
    
    extern void sft_hvsync();//4-4-6 0:43
    sft_hvsync();       //freyman 2004-2-27 12:01
    
    #endif
#endif

#ifdef UART_SWAP //axel swap uart0 and uar1 2004/10/29
    UART1_set_baudrate(BAUDCC(BAUDRATE_DEFAULT, 121500000));
    psprintf(linebuf,"------------Release UART------------\n");
    UART1_puts(linebuf);
#endif

#if 0
    // enable both UART
    regs0->sft_cfg2 |= 1<<15;
    UART0_set_baudrate(BAUDCC(BAUDRATE_DEFAULT, 121500000));
    UART1_set_baudrate(BAUDCC(BAUDRATE_DEFAULT, 121500000));
    UART0_puts("enable UART0\n");
    UART1_puts("enable UART1\n");
#endif    
}


/*
SSPLL_BWS           = SYSCLK_SEL[5];
SSPLL_SSCGON        = SYSCLK_SEL[4];

SSPLL_C2     	    = PLLV_CFG[13];
SSPLL_C1      	    = PLLV_CFG[12];
SSPLL_S     	    = PLLV_CFG[11:8];
SSPLL_NS            = PLLV_CFG[7:0];

SSPLL_CKREF         = SFT_CFG24[9];
SSPLL_AUTOBWS       = SFT_CFG24[8];
SSPLL_MDS 	    = SFT_CFG24[7:0];
*/


/**************************************************************************
 *  Function Name: reset_all                                              *
 *  Purposes:                                                             *
 *   1. DISABLE INTR                                                      *
 *   2. REGF + ROMIF setup                                                *
 *   3. EMUIO/UART setup (interrupt not yet enabled)                      *
 *   4. APLL setup (before GPIO for correct XCK)                          *
 *   5. GPIO setup                                                        *
 *   6. SDRAM size setup                                                  *
 *   7. TIMER setup                                                       *
 *   8. SDRAM memory mapping configuration                                *
 *   9. VIDDEC                                                            *
 *   10. SUP                                                              *
 *   11. MULTI-TASK                                                       *
 *   12. ENABLE INTR                                                      *
 *   13. IOP include IR ﹜VFD﹜TV-encoder﹜DAC                            *
 *  Descriptions:                                                         *
 *      reset all, including some interface.                              *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
extern void enable_portable_bonding(UINT8 onoff);
extern void AUDIF_Init_Audio(void);
void reset_all(void)
{
// longson 2004.02.16
#ifdef	SPHE8202            
	#ifndef IC_1002
	regs0->sft_cfg4 = 0x6073;	// disable  SC1_OUT and TRAY_OUT
	regs0->gpio_oe[0] = 0x0c;	// enable GPIO[2] and GPIO[3] output
	#endif	// IC_1002
#endif	// SPHE8202

    //
    // at this time only reset.c/crt0.S/lexra.S/sysmain.c are assumed to
    // be in memory
    //

    //
    // load code to sdram if required
    //
#ifdef SPHE1000
	#if defined(LOAD_OTHER)
	LoadModual(MODUAL_OTHER);           write_stamp(STAMP_LOAD_MODULE_OTHER);
	#endif
	msg_init();
#endif

    //
    // prolog
    reset_all_enter();

    //
    // reset basic system (again)
    reset_system();
    write_stamp(STAMP_RESET_SYSTEM);
    
#ifndef START_NO_VPP_DELAY //linrc add for nintaus 2004-7-12 19:51
    reset_tvdac();
#endif

#ifdef POWER_ON_VIDEO_DAC_OFF
	tv_dacoff( (0x01<<0)|(0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4)|(0x01<<5) );
#endif//POWER_ON_VIDEO_DAC_OFF

    //
    // change system clock from 108MHz to required frequency
#ifndef USE_DEFAULT_CLOCK           //2004/10/21 wjzhang , sphe1000B(stb-dvd): use default clock
	#ifdef SPHE1000
	{
		UINT32 CFG_board_config = regs0->hw_cfg;
		if (CFG_board_config == 9)	regs0->sft_cfg2 |= (3<<14);
		reset_change_sysclk();		write_stamp(STAMP_CHANGE_SYSCLK);
		if (CFG_board_config == 9)	regs0->sft_cfg2 &= ~(3<<14);
	}
	#else
	reset_change_sysclk();			write_stamp(STAMP_CHANGE_SYSCLK);
	#endif	// SPHE1000
#endif

#ifndef	IC_1002
	// SSPLL setting            // 2006/09/22 yltseng
	sspll_reg_backup();
	set_sspll_reg();
#endif	// IC_1002

#ifdef TCL_STANDBY
    tcl_standby_gpio_ctrl();
#endif

    //
    // load code to sdram if required
    //
#if defined(LOAD_OTHER)
    LoadModual(MODUAL_OTHER);           write_stamp(STAMP_LOAD_MODULE_OTHER);
#endif
    LoadModual(MODUAL_AP);              write_stamp(STAMP_LOAD_MODULE_AP);
    LoadModual(MODUAL_FREE);            write_stamp(STAMP_LOAD_MODULE_FREE);
    LoadModual(MODUAL_CDROM);           write_stamp(STAMP_LOAD_MODULE_CDROM);
#ifdef  SUPPORT_8202_DVB    
    LoadModual(MODUAL_DVB);            write_stamp(STAMP_LOAD_MODULE_DVB);
#endif    


    //
    // at this time all essential code is decompressed and loaded.
    // OTHER/AP/FREE/CDROM code are loaded
    //
    //
    // blank display
    disable_video();
    write_stamp(STAMP_DISABLE_VIDEO);

#ifdef SUPPORT_AUDIO_RESET
    GpioResetAudio();
#endif

    //720 generate DAC clock first, Jeff 20020712
#ifndef DVD728
    // setup audio clockgen (to correct format and XCK)
    hwsetup_audio_clkgen_init();
#endif

#ifdef  SUPPORT_EPP
	// reset emuio fifo
	reset_io();
#endif


    //
    // hardware initialization
#ifdef SPHE1000
	reset_gpio_1000();
#else
	reset_gpio();         // setup GPIO directions
#endif

	//uart relative function
	reset_uart_func();
    
	//
	// Enable UART interrupt here (to enable emuio access)
	reset_all_enable_intr_only_uart();	write_stamp(STAMP_ENABLE_INTR_0);
    
#if 0//def SUPPORT_UART_COMMAND    //inform external MCU Power is ok and releas vfd and ir
	Inform_MCUOK();
#endif

#ifdef SUPPORT_POWER_STB //jinping for power standby 2002-7-6 17:56
    POWER_STB_SET( STANDBY ); // power on;
#endif

#ifdef SUPPORT_AMP // for SVA DVD solution
    AMP_MUTE_SET(1);  // tripth amp. high mute; mute amp.
    amp_onoff_flag = 0;//default is 0. 0:amp off,out to TV; 1:amp on, out to amp
#endif


    //
    // Load other code modules
    LoadModual(MODUAL_MPEG);            write_stamp(STAMP_LOAD_MODULE_MPEG);
    LoadModual(MODUAL_AP2);             write_stamp(STAMP_LOAD_MODULE_AP2);

    //
    // setup framebuffer/memory initial configuration
    enable_portable_bonding(0);

    #if defined(PORTABLE_DVD)||defined(ALCO_PORTABLE_DVD_8202D_DVB)//jhuang 2003/12/3
        memory_config_saved = IOP_CONFIG_PDVD;
        is_iop_ready();
    #endif

    memory_config_saved = 0xff;
    config_memory(MEMORY_DVD_NTSC);
    write_stamp(STAMP_CONFIG_MEMORY);

    //
    // setup timer
    init_timer();

    // init_audio();  //terry mark it on 2002/2/24 02:40PM ,avoid A/D to be turned on at startup
    init_video_decoder();
    init_sup();
    pe_init();

    //
    // Abort previous decoding tasks
    MacroAbort();

    //
    // Reset interrupt routines
    // atapi: (not used now)
    // task: task-switching
    reset_atapi_intr();
#ifndef DVDRELEASE
    reset_task();
#endif

#if 0 //test rom bit stream mode
    setup_display(0,1);
    test_rom_based_video();
#endif



    //
    // Reset watchdog
    watchdog_renew(0xffff);     // n*16/90k, first time we set to maximum (about 12-second)
    watchdog_onoff(1);
    write_stamp(STAMP_RESET_WATCHDOG);

    //
    // Enable all used interrupts
    reset_all_enable_intr_all();            write_stamp(STAMP_ENABLE_INTR_1);

    //
    // Initialize OSD (before enable TV-encoder)
    reset_osd();                            write_stamp(STAMP_RESET_OSD);

    //
    // basic service on
    // interrupt has been on
    //

    //
    //  IOP     IOP     IOP     IOP     IOP     IOP
    //

    // setup iop
    reset_status_puts("setup iop.\n");
    reset_iop();

    // iop service #1
    reset_status_puts("setup ir inf.\n");
    reset_ir();

#ifdef AD_HL_USE    // lxg 2006-8-14 02:18
init_vfd_clear();
#endif    

    // iop service #2
#if defined(SUPPORT_VFD)&&defined(SUPPORT_VFD_PANEL) //lijd 2004-12-4 11:39
    reset_status_puts("setup vfd inf.\n");
    reset_vfd();
#endif

#if defined(GPIO_KEY_LIGHT)
    init_keylight_io();
#endif

    // iop service #3 (if 721/725)
    reset_status_puts("setup tv inf.\n");

#ifdef DVD728
    #define NO_SYNC_ON_G

    #ifdef NO_SYNC_ON_G
    setup_sync_on_G(0);     // support SCART TV, no sync signal on G channel
    #endif

    setup_display(0,1);     // FIX: this is for osd/tv-encoder to keep coherent.
//    delay_1ms(200); //terry,2003/8/11 11:44AM
    /*
    #ifdef BBK_DVD//zhaoyanhua add 2003-11-24 14:23
        tv_init_output();
    #endif
    */
#else
    tv_setup();
#endif
/*receiver use gpio 93 94 for RDS*/
#ifdef SUPPORT_RECEIVER
regs0->sdc_data_cnt[6][0] |= (0x0e);//Disable ROM_A20(Pin225),ROM_A21(Pin226),ROM_A22(Pin227) as GPIO92,93,94
#endif

  reset_setup_digital_video_out();

#ifdef USE_SETUP_SELECT_FONT
  reset_font_map_setup();
#endif

  // iop service #4
#ifdef  SETUP_DAC
    reset_status_puts("setup dac.\n");
    dac_setup();
#endif

    // iop service #5
#if defined(PT2322)||defined(PT2320)
    reset_status_puts("setup pt2322.\n");
    init_pt_audio();
#endif

#if defined(TAS3001_AMP)||defined(NO_AMP_ONLY_TUNER)     //use TI 3001  amplifier  2-8-22 12:58
    {
  //    extern int AudioIOControl(UINT16 wCode, BYTE cType, UINT16 wParam); //kenny mark it
   //    AudioIOControl(2, 15, 0);  //set 720 pcm volume 2==VOLUME,15=max volume
        regs0->gpio_sel |= GPIOSEL_10_GPIOS;   //use gpio22,23 communicate with MCU// jason 2-11-4 19:05
        regs0->gpio_out[23/16]&=(~(3<<(22%16)));
        regs0->gpio_oe[23/16] |=(3<<(22%16));
    #ifndef NO_AMP_ONLY_TUNER
       tas3001_reset();
#endif
    }
#endif
#if defined(TAS5026_AMP)     //use TI 3001  amplifier  2-8-22 12:58
    {
  //    extern int AudioIOControl(UINT16 wCode, BYTE cType, UINT16 wParam); //kenny mark it
   //    AudioIOControl(2, 15, 0);  //set 720 pcm volume 2==VOLUME,15=max volume
       tas5026_reset();
    }
#endif

    // setup dsp port
    {
        int i;
        for (i=0;i<16;i++) regs0->dsp24_port[i] = 0; //Jeff 20011029
    }


#ifdef  SETUP_UART1
    // enable UART1
    {
        UINT32 u;

        // setup baudrate
        UART1_set_baudrate(UART_BAUD_57600);

        // change pinmux
        u = regs0->sft_cfg2;
        u = (u & ~(0x0f<<5)) | (0x09<<5);
        regs0->sft_cfg2 = u;
        while (1) UART1_puts("test uart #1\n");
    }
#endif

/*
    // servo testing code
#ifdef DVD_SERVO
#ifndef SOFT_ATAPI //DVD_SERVO
    ServoDecInit(); // barry add for init servo
    ResetInterfaceProc();
#endif
    regs0->emu_cfg[16] = 0x00;              // ROM-pattern disable
    regs0->rf_servo_band_en = 0x00;         //
#endif
*/

#if defined(VOLUME_RECODE)||defined(VOLUME_RECODE_NEW)        //gerry add it before init audio,2004-7-6 9:36
    volume_init();
#endif//VOLUME_RECODE

    //
    // initialize audio, put it here to avoid CS4334 noise
    AUDIF_Init_Audio_HW();//2004AUDDRV init_audio();

    //
    // ???
#ifdef CS8403_ENABLE
   #ifdef SPHE8202
   init_cs8403a__();
   #else
    regs0->gpio_master[55 / 16] |= (0x1 << (55 % 16));  //pin155, GPIO[55]
    regs0->gpio_oe[55 / 16] |= (0x1 << (55 % 16));
    regs0->gpio_out[55 / 16] |= (0x1 << (55 % 16));
    init_cs8403a__();
   #endif
#endif

#ifdef PCM1742 //Jeff 20030917
    dac_turn_on();
#endif

#ifdef CS4360 //huziqin
    //printf("config 4360\n");
    config_cs4360();
#endif

    //
    // postlog
#ifdef PMP_MCU810        ////////add to wirte IR head H/L and keycode --yangli   2004-11-11

       SendIRIDPowerKeyToMCU();
#endif
/*#ifdef PMP_Video_Onlycvbs    ///yangli 2004-11-29.add to pmp video out only cvbs
    tv_dacoff(TV_DAC_B|TV_DAC_C|TV_DAC_D|TV_DAC_E|TV_DAC_F);//only cvb is on
 #endif
*/
#if 0	// no longer needed
#ifdef  IC_8202E
    regs0->tv_mode[4] = 0x1000; // turn off 54Mhz upsampling
    regs0->g21_reserved[4] = 0x80; // turn off 108Mhz upsampling
#endif    

#if defined(IC_8202D)||defined(IC_8202L)||defined(IC_8203A)
///// setup upsampling 54MHz CLK source
    regs0->sysclk_div_sel = (regs0->sysclk_div_sel & ~(7<<6)) | (1<<6);	// to set CLK54 be pumped by CLK27 (not 50% duty)
    regs0->g21_reserved[4] = 0x80; // turn off dithering, sharpness, 108Mhz upsampling and turn on cb/cr 27Mhz upsampling
#endif    
#endif	// #if 0
#ifdef IC_8202L
	#ifdef TV_USE_QUART_SWING
		regs0->tv2_dac_cor0 = (0x1)|(9<<4);	// DAC-A correction enable and scaling down to 94% (-6%) 
							// to improve yield and channel balance (with DAC-BCD)
	#endif	//TV_USE_QUART_SWING
#endif	//IC_8202L

#ifdef SPHE1000
#ifdef HE1001_TUNER //yarco 20041202
    regs0->sft_cfg3 &= 0xffcf; //disable ATAPI
    regs0->sft_cfg2 = (regs0->sft_cfg2 & 0xfff1) | 0x06; //select TS interface
#endif
#endif

#if defined(IC_8202D)||defined(IC_8202L)||defined(IC_8203A)
    delay_srv_10ms(50);             // temp FIX for startup screen blinking
#endif	// IC_8202D

#ifdef	IC_8202L
	regs0->sft_cfg26 |= 0x8000;		// enable OGT urgent control
#endif	// IC_8202L

    //
    // initialization of kernel
    reset_kernel();

    PCI_CNT_VAR = PCI_CNT;  //ycwen 2005/11/16 For flexibility, change "#define PCI_CNT" to a input vaiable "PCI_CNT_VAR".

    #ifdef SUPPORT_MP3_6CH   //ycwen 2005/5/26 for MPEG multi channel audio
    set_enable_mp2_mc();
    #endif
    
    reset_all_exit();

    #if defined(DVB1000_NON_OS) && defined(SUPPORT_USB)
    reset_usb();
    #endif
}

/**************************************************************************
 *  Function Name: reset_set_uart0_baudrate                               *
 *  Purposes:                                                             *
 *      reset baudrate of uart0                                           *
 *  Descriptions:                                                         *
 *      there are 9 type baudrate of uart0                                *
 *  Arguments:  None                                                      *
 *  Returns: 0                                                            *
 *  See also: None                                                        *
 **************************************************************************/
static  inline  void    reset_set_uart0_baudrate(void)
{
#if     defined(F135)
    UART0_set_baudrate(BAUDCC(BAUDRATE_DEFAULT, 135000000));
#elif   defined(F128_25)
    UART0_set_baudrate(BAUDCC(BAUDRATE_DEFAULT, 128250000));
#elif   defined(F121_5)
    UART0_set_baudrate(BAUDCC(BAUDRATE_DEFAULT, 121500000));
#elif   defined(F114_75)
    UART0_set_baudrate(BAUDCC(BAUDRATE_DEFAULT, 114750000));
#elif   defined(F108)
    UART0_set_baudrate(BAUDCC(BAUDRATE_DEFAULT, 108000000));
#elif   defined(F101_25)
    UART0_set_baudrate(BAUDCC(BAUDRATE_DEFAULT, 101250000));
#elif   defined(F94_5)
    UART0_set_baudrate(BAUDCC(BAUDRATE_DEFAULT,  94500000));
#elif   defined(F87_75)
    UART0_set_baudrate(BAUDCC(BAUDRATE_DEFAULT,  87750000));
#elif   defined(F81)
    UART0_set_baudrate(BAUDCC(BAUDRATE_DEFAULT,  81000000));
#endif
}

/**************************************************************************
 *  Function Name: reset_change_sysclk                                    *
 *  Purposes:                                                             *
 *      change system clock                                               *
 *  Descriptions:                                                         *
 *       there are 19 type of system clock                                *
 *  Arguments:  None                                                      *
 *  Returns: 0                                                            *
 *  See also: None                                                        *
 **************************************************************************/
int
reset_change_sysclk(void)
{
#if     defined(F168_75)    //wrwu, 2005-01-21, for over-clock
    change_system_clock(25);
#elif     defined(F162)
    change_system_clock(24);
#elif     defined(F155_25)
    change_system_clock(23);
#elif     defined(F148_5)
    change_system_clock(22);
#elif     defined(F141_75)
    change_system_clock(21);
#elif     defined(F135)
    change_system_clock(20);
#elif   defined(F128_25)
    change_system_clock(19);
#elif   defined(F121_5)
    change_system_clock(18);
#elif   defined(F114_75)
    change_system_clock(17);
#elif   defined(F108)
    change_system_clock(16);
#elif   defined(F101_25)
    change_system_clock(15);
#elif   defined(F94_5)
    change_system_clock(14);
#elif   defined(F87_75)
    change_system_clock(13);
#elif   defined(F81)
    change_system_clock(12);
#elif   defined(F74_25)
    change_system_clock(11);
#elif   defined(F67_5)
    change_system_clock(10);
#elif   defined(F60_75)
    change_system_clock(9);
#elif   defined(F54)
    change_system_clock(8);
#elif   defined(F47_25)
    change_system_clock(7);
#elif   defined(F40_5)
    change_system_clock(6);
#elif   defined(F33_75)
    change_system_clock(5);
#elif   defined(F27)
    change_system_clock(4);
#elif   defined(F13_5)
    change_system_clock(2);
#elif   defined(F6_75)
    change_system_clock(1);
#endif
    //reset_set_uart0_baudrate();
#ifdef IC_8202L
    reset_set_uart0_baudrate();
#endif
    return 0;
}

/**************************************************************************
 *  Function Name: reset_change_sysclk_27M                                *
 *  Purposes:                                                             *
 *      change system clock to 27M                                        *
 *  Descriptions:                                                         *
 *      change system clock                                               *
 *  Arguments:  None                                                      *
 *  Returns: 0                                                            *
 *  See also: None                                                        *
 **************************************************************************/
int
reset_change_sysclk_27M(void)
{
    change_system_clock(4);    UART0_set_baudrate(BAUDCC(BAUDRATE_DEFAULT, 27000000));
//  change_system_clock(10);    UART0_set_baudrate(BAUDCC(BAUDRATE_DEFAULT, 67500000));
    return 0;
}


#ifdef  SUPPORT_USB
/**************************************************************************
 *  Function Name: set_usbpll_reg                                         *
 *  Purposes:                                                             *
 *      setup regs0->sft_cfg9                                             *
 *  Descriptions:                                                         *
 *      setup USB clock                                                     *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
static inline void set_usbpll_reg(unsigned s, unsigned ns)
{
#ifdef SPHE1000
    unsigned cfg7;
    cfg7 = regs0->sft_cfg7;
    regs0->sft_cfg7 = (cfg7 & ~0xfff) | ((ns<<6)|(s));
#else
    unsigned cfg9;
    cfg9 = regs0->sft_cfg9;
    regs0->sft_cfg9 = (cfg9 & ~0xfff) | ((ns<<6)|(s));
#endif
}

#endif

//
// SYSTEM CLOCK
//

#ifdef SPHE1000
//#define LX_F256  //wrwu, 2005/03/07 , move the define to cfg_xxx.h
static inline void set_lx4189_overclock()
{
    // change lx4189 sysclk->270Mhz
    volatile UINT32 *ptr=(volatile UINT32*)0xbc010ce0;
    BYTE    NR=0, NF=0;
    BYTE    OD=0;

#if defined(LX_F251)
    NR=5; NF=93;
#elif defined(LX_F253)
    NR=5; NF=94;
#elif defined(LX_F256)
    NR=2; NF=38;
#elif defined(LX_F263)
    NR=2; NF=39;
#elif defined(LX_F270)
    NR=2; NF=40;
#elif defined(LX_F276)
    NR=2; NF=41;
#elif defined(LX_F283)
    NR=2; NF=42;
#elif defined(LX_F290)
    NR=2; NF=43;
#elif defined(LX_F297)
    NR=2; NF=44;
#elif defined(LX_F303)
    NR=2; NF=45;
#elif defined(LX_F310)
    NR=2; NF=46;
#else   // F270
    NR=2; NF=40;
#endif

    regs0->pllc_cfg = (OD<<14)|((NR-2)<<9)|(NF-2);
    *ptr = 1;
    delay_1us(500);
}
#endif  // SPHE1000


/**************************************************************************
 *  Function Name: set_syspll_reg                                         *
 *  Purposes:                                                             *
 *     setup regs0->sysclk_div_sel and regs0->sysclk_sel                  *
 *  Descriptions:                                                         *
 *      setup system clock                                                *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
static inline void set_syspll_reg(unsigned a, unsigned b)
{
    int i;
#ifdef SPHE1000
    regs0->sysclk_div_sel= 0x0404;       // slow it down
    regs0->sysclk_sel=((a)|(10<<4));
    for (i=0;i<1000 && (regs0->sysclk_sel&((1<<8)|(1<<11)|(1<<12))); i++) ;
    regs0->sysclk_div_sel= ((b)|(0<<8));
  #ifdef LX4189_OVERCLOCK   //wrwu, 2005/03/07 , the "LX4189_OVERCLOCK" define in cfg_xxx.h
    set_lx4189_overclock();
  #endif
#else
    regs0->sysclk_div_sel= 4;       // slow it down
    regs0->sysclk_sel=a;
    for (i=0;i<1000 && (regs0->sysclk_sel&((1<<11)|(1<<12))); i++) ;
#ifdef  CLK54_USE_USBPLL
    b |= (2<<6);        // CLK54 select USB OSCx2
    //b |= (3<<6);        // CLK54 select USB OSC
#endif
    regs0->sysclk_div_sel= b;
#endif
}


/**************************************************************************
 *  Function Name: reset_delayX                                           *
 *  Purposes: delay time                                                  *
 *  Descriptions: delay time                                              *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
static void reset_delayX(int n)
{
    while (n-->0) {
        asm volatile ("nop");
    }
}



#define     CLKUV(u,v)  (((u)<<4)|(v))
#define     CLKUV_U(uv)  ((uv)>>4)
#define     CLKUV_V(uv)  ((uv)&0x0f)

static  const   UINT8   sysclk_table[26] =      //wrwu, 2005-01-21, for over-clock
{
    CLKUV(1,0),     // 00: -----
    CLKUV(1,4),     // 01: 0.25x      6.75
    CLKUV(1,3),     // 02: 0.50x     13.5
    CLKUV(9,3),     // 03: 0.75x     20.25
    CLKUV(1,2),     // 04: 1.00x     27
    CLKUV(5,2),     // 05: 1.25x     33.75
    CLKUV(9,2),     // 06: 1.50x     40.5
    CLKUV(13,2),    // 07: 1.75x     47.25
    CLKUV(1,1),     // 08: 2.00x     54
    CLKUV(3,2),     // 09: 2.25x     60.75
    CLKUV(5,1),     // 10: 2.50x     67.5
    CLKUV(7,1),     // 11: 2.75x     74.25
    CLKUV(9,1),     // 12: 3.00x     81
    CLKUV(11,1),    // 13: 3.25x     87.75
    CLKUV(13,1),    // 14: 3.50x     94.5
    CLKUV(0,1),     // 15: 3.75x    101.25
    CLKUV(1,0),     // 16: 4.00x    108         xx
#if defined(IC_8202D)||defined(IC_8202L)||defined(IC_8203A)
    CLKUV(2,0),     // 17: 4.25x    114.75
    CLKUV(3,0),     // 18: 4.50x    121.50
#else
    CLKUV(2,1),     // 17: 4.25x    114.75
    CLKUV(3,1),     // 18: 4.50x    121.50
#endif
    CLKUV(4,0),     // 19: 4.75x    128.25      xx
    CLKUV(5,0),     // 20: 5.00x    135
    CLKUV(6,0),     // 21: 5.25x    141.75
    CLKUV(7,0),     // 22: 5.50x    148.5
    CLKUV(8,0),     // 23: 5.75x    155.25
    CLKUV(9,0),     // 24: 6.00x    162
    CLKUV(10,0),    // 25: 6.25x    168.75
#if 0
    CLKUV(11,0),    // 26: 6.50x    175.5
    CLKUV(12,0),    // 27: 6.75x    181.25
    CLKUV(13,0),    // 28: 7.00x    189
#endif
};


#if !defined(SPHE8202) && !defined(SPHE1000)
static  const   UINT8   baudrate_table[26] = {      //wrwu, 2005-01-21, for over-clock
    BAUDCC(BAUDRATE_DEFAULT,6750000*0),
    BAUDCC(BAUDRATE_DEFAULT,6750000*1),
    BAUDCC(BAUDRATE_DEFAULT,6750000*2),
    BAUDCC(BAUDRATE_DEFAULT,6750000*3),
    BAUDCC(BAUDRATE_DEFAULT,6750000*4),
    BAUDCC(BAUDRATE_DEFAULT,6750000*5),
    BAUDCC(BAUDRATE_DEFAULT,6750000*6),
    BAUDCC(BAUDRATE_DEFAULT,6750000*7),
    BAUDCC(BAUDRATE_DEFAULT,6750000*8),
    BAUDCC(BAUDRATE_DEFAULT,6750000*9),
    BAUDCC(BAUDRATE_DEFAULT,6750000*10),
    BAUDCC(BAUDRATE_DEFAULT,6750000*11),
    BAUDCC(BAUDRATE_DEFAULT,6750000*12),
    BAUDCC(BAUDRATE_DEFAULT,6750000*13),
    BAUDCC(BAUDRATE_DEFAULT,6750000*14),
    BAUDCC(BAUDRATE_DEFAULT,6750000*15),
    BAUDCC(BAUDRATE_DEFAULT,6750000*16),
    BAUDCC(BAUDRATE_DEFAULT,6750000*17),
    BAUDCC(BAUDRATE_DEFAULT,6750000*18),
    BAUDCC(BAUDRATE_DEFAULT,6750000*19),
    BAUDCC(BAUDRATE_DEFAULT,6750000*20),
    BAUDCC(BAUDRATE_DEFAULT,6750000*21),
    BAUDCC(BAUDRATE_DEFAULT,6750000*22),
    BAUDCC(BAUDRATE_DEFAULT,6750000*23),
    BAUDCC(BAUDRATE_DEFAULT,6750000*24),
    BAUDCC(BAUDRATE_DEFAULT,6750000*25)
};
#endif


#ifdef SHOW_SYSTEM_CLOCK//nono 4-4-6 0:29
int get_sysclk;
#endif//SHOW_SYSTEM_CLOCK
/**************************************************************************
 *  Function Name: change_system_clock                                    *
 *  Purposes:                                                             *
 *   1. disable interrupt                                                 *
 *   2. get idx                                                           *
 *   3. set syspll                                                        *
 *   4. set sdram-timing                                                  *
 *   5. restore interrupt setting                                         *
 *  Descriptions:                                                         *
 *      change system clock                                               *
 *  Arguments:  None                                                      *
 *  Returns: 0                                                            *
 *  See also: None                                                        *
 **************************************************************************/
int
change_system_clock(int uvidx)
{
    unsigned uv, u, v, IEc;

#ifdef SHOW_SYSTEM_CLOCK//nono 4-4-6 0:29
    //get get_sysclk;print on cus_menu
    get_sysclk = uvidx;
#endif//#ifdef SHOW_SYSTEM_CLOCK

    // disable interrupt
    IEc = cpu_intr_disable();

    // delay??
    reset_delayX(100);

    // get idx
    uv = sysclk_table[uvidx];
    u = CLKUV_U(uv);
    v = CLKUV_V(uv);

#if defined(BOOT_HALF) || defined(IC_8202E)
    if (v!=0) v--;
#endif

    // set syspll
    set_syspll_reg(u,v);

#ifdef  SUPPORT_USB
    //set_usbpll_reg(0x12,0x1b);        // 96mhz/48mhz
    //set_usbpll_reg(0x1b,0x1b);          // 54mhz/27mhz
    //regs0->sft_cfg7 |= (0xf<<8);        // clk27 select clk54/2
    //regs0->sft_cfg7 |= (3<<12);       // output clk54 to pin 65
#endif

    // set sdram-timing
    if (uvidx<10)
        set_sdram_timing_low();
    else
        set_sdram_timing();

    // restore interrupt setting
    cpu_intr_config(IEc);

#if !defined(SPHE8202) && !defined(SPHE1000)
    // initialize stc-divisor
    regs0->stc_divisor    = uvidx*75-1;
    UART0_set_baudrate(baudrate_table[uvidx]);
#endif
    return 0;
}


/**************************************************************************
 *  Function Name: slowdown_test                                          *
 *  Purposes:                                                             *
 *  Descriptions:                                                         *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
#if 0
void
slowdown_test(void)
{
    reset_change_sysclk_27M();
    UART0_set_baudrate(BAUDCC(BAUDRATE_DEFAULT, 27000000));
    delay_1ms(200);
    reset_change_sysclk();
    UART0_set_baudrate(BAUDCC(BAUDRATE_DEFAULT, 121500000));
}
#endif

#ifdef CS4360  //huziqin 2004-2-26
#define CS4360_ADDR   0x20
/*
mode control 1:
addr 01h
AMUTE  7
DIF  4-6
DEM 2-3
FM  0-1

mode control 2:
addr 0ch
SZC  6-7
CPEN 5
PDN  4
POPG 3
FREEZE  2
MCLKDIV  1
SNGLVOL  0
*/
/**************************************************************************
 *  Function Name: config_cs4360                                          *
 *  Purposes:                                                             *
 *     cofig cs4360 mode                                                  *
 *  Descriptions:                                                         *
 *     config_cs4360                                                      *
 *  Arguments:                                                            *
 *    mode control 1:                                                     *
 *    addr 01h                                                            *
 *    AMUTE  7                                                            *
 *    DIF  4-6                                                            *
 *    DEM 2-3                                                             *
 *    FM  0-1                                                             *
 *                                                                        *
 *    mode control 2:                                                     *
 *    addr 0ch                                                            *
 *    SZC  6-7                                                            *
 *    CPEN 5                                                              *
 *    PDN  4                                                              *
 *    POPG 3                                                              *
 *    FREEZE  2                                                           *
 *    MCLKDIV  1                                                          *
 *    SNGLVOL  0                                                          *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
void config_cs4360(void)
{
    BYTE data;
    int res;
    /*mode ctrl 2*/
    data = 0xa8;
    res = WriteToI2c(CS4360_ADDR, 0x0c, &data, 1);
    /*mode ctrl 1*/
    data = 0x90;
    res = WriteToI2c(CS4360_ADDR, 0x01, &data, 1);
    //printf("config 4360 res == %d\n ",res);
}
#endif //cs4360

#ifdef TCL_STANDBY
void tcl_standby_gpio_ctrl(void)
{
    regs0->sft_cfg1 &= ~(0x1 << 3);//gpio 3 enable
    regs0->gpio_master[ 3/16 ] |= 0x1 << (3%16);//gpio 3 for mips
    regs0->gpio_oe[ 3/16 ] |= 0x1 << (3%16);//output
    regs0->gpio_out[3/16 ] |= (0x1 << (3%16));
    //delay_1ms(500);

    regs0->gpio_master[ 2/16 ] |= 0x1 << (2%16);//gpio 2 for mips
    regs0->gpio_oe[ 2/16 ] &= ~(0x1 << (2%16));//input
}
#endif



