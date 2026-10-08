//
// FILE
// hwif.c
//

#include "config.h"
#include "regmap.h"

#include "uart.h"
#include "cpu.h"
#include "lbc.h"

#include "hwif.h"
#include "hw.h"

#include "func.h"

//not remove this, add a password to see servo source code version, that we release, Jeff 20030818
#include "../IR_VFD/ircode.h"
#ifdef DVD_SERVO
const BYTE Servo_Password[8]={IRC_3,IRC_4,IRC_4,IRC_3,IRC_3,IRC_4,IRC_4,IRC_1};
#endif

/*
*  Debug Option
*/

#ifndef   DVDRELEASE
#define HWIF_DBG
#endif

#ifdef HWIF_DBG
#define hwif_printf(s...) {psprintf(linebuf,##s); UART0_puts(linebuf);}
#else
#define hwif_printf(s...) do {} while (0)
#endif



//
// crt0.S
extern  void    setup_sdctrl_sref();            // setup SDRAM to use self-refresh
extern  void    set_sdram_timing(void);
extern  void    set_sdram_timing_low(void);

// sdram.S (obsolete)
extern  void    configure_sdram_timing(int);


// reset.c
extern int change_system_clock(int);

//
//
//
static inline void hwif_bypass_pllv(void)
{
    // bypass PLLV
#ifdef SPHE1000
	hwif_clkdiv(0x0606);
	regs0->sysclk_sel = 0x41;
	while (regs0->sysclk_sel & 0x1810)
		asm volatile ("nop");
#else
    regs0->sysclk_sel = 0x4001;
    while (regs0->sysclk_sel & 0x1800) ;
#endif
}


static inline void hwif_clkdiv(int n)
{
    regs0->sysclk_div_sel = n;
}


static inline void hwif_disable_clk27(void)
{
    // turn-off CK27
    regs0->sysclk_sel = 0xe001;
}


static inline void hwif_disable_plla(void)
{
#ifdef SPHE1000
	regs0->sft_cfg6         |= (1<<12);
#else
    regs0->sft_cfg6         &= ~((1<<10)|(1<<11));
#endif
}


static inline void hwif_disable_audio(void)
{
    regs0->aud_adc_mono_cfg = 0x0010;
    regs0->aud_enable       = 0x0000;
}


static  inline  void    hwif_disable_tvdacs(void)
{
    // disable TV DAC
    regs0->tv_mode[5] = 0x60bf;
}


static  inline  void    hwif_enable_iop_rstsys(void)
{
    // enable IOP to reset system
#ifdef SPHE1000
	regs0->sft_cfg5 |= (1<<14);	// sphe1000 enable iop reset system
#else
    regs0->sft_cfg2 |= (1<<1);
#endif

    // inform IOP could enter mechanism of reseting RISC
    regs0->iop_data[6] = 1;
}


//
// FUNCTION
// hwif_reset_all
//
// DESCRIPTION
// reset all but global
//
void hwif_reset_all(void)
{
    UART0_puts("hwif_reset_all()\n");
    delay_1ms(100);

    while (1) {
#if 0
        regs0->reset = 0xffff;
        regs0->reset2 = 0xffff;
//        regs0->reset = ~HW_RESET_GLOBAL;
//        regs0->reset2 = 1;
#else
        extern  void __boot_entry();
        __boot_entry();
#endif
    }
}


//
// FUNCTION
// hwif_reset_sleep
//
// DESCRIPTION
// enable-sleep..
//
// current status
// kernel: about 30mA
// io: about 45mA
//
void hwif_reset_sleep(void)
{
#if 0
    // all reset
    regs0->rom_config = 0xf000;
    regs0->reset  = 0x0000;
    regs0->reset2  = 0x0000;
    regs0->g6_reserved[10] = 0x2;
    regs0->g2_reserved[13] |= 0x2000;
#if 0
    WriteServoReg(0x036, 0xff);
    WriteServoReg(0x33e, 0x02);
    WriteServoReg(0x403, 0x04);
    WriteServoReg(0x40e, 0x02);
#endif
    regs0->tv_mode[5] = 0x60bf;
    regs0->aud_adc_mono_cfg = 0x0010;
    regs0->aud_enable  = 0x0000;
    regs0->sft_cfg6 = 0x01f7;
    regs0->sysclk_sel = 0x4001;
    while (regs0->sysclk_sel & 0x1800) ;
    regs0->sysclk_sel = 0xe001;
    while (1);
#endif

    hwif_disable_tvdacs();          // disable TV-DAC output
    hwif_disable_audio();           // disable audio

    //
    // disable sub-systems
    regs0->reset2 = (
        HW_RESET_OGT        
        | HW_RESET_VPP        
        | HW_RESET_OSD       
        | HW_RESET_DSP       
        | HW_RESET_STC      
        | HW_RESET_CD        
        | HW_RESET_CSS       
        | HW_RESET_HOST 
        | HW_RESET_LPT 
        | HW_RESET_UA0
        | HW_RESET_UA1        
        | HW_RESET_TDM        
        | HW_RESET_BRIDGE         
//       | HW_RESET_TV       
//       | HW_RESET_IOP      
        );

    regs0->clken1 &= ~ (
        HW_RESET_TV
#ifndef SPHE1000
        | HW_RESET_SRV
#endif
        ) ;

    hwif_disable_plla();            // disable audio PLL
//    setup_sdctrl_sref();            // setup SDRAM to use self-refresh
//potatooo suggest to mark it.20050823 When 8202d-32M-RISC-ALIVE-STANDBY, player can't power on.

    // bypass PLL and use CK27/2 as system-clock source
    {
        int cfg;
        cfg = cpu_intr_disable();
#ifdef SPHE1000
        hwif_bypass_pllv(); set_sdram_timing_low();
#else
	#ifdef HW_RESTRICTION_CHANGE_SYS_CLOCK //2006-04-12, mimitsai add for IC_8202xx relative
        change_system_clock(1);
#else
        hwif_bypass_pllv(); hwif_clkdiv(0); set_sdram_timing_low();
#endif      
#endif
        cpu_intr_config(cfg);
    }

    hwif_enable_iop_rstsys();


#if defined(SPHE8202) || defined(SPHE1000)

#else
    // disable sdram pads
    regs0->pad_ctrl = 0x00;
    // (8200) enable sdram output when tri-state
    regs0->g6_reserved[10] = 0x2;
    regs0->g2_reserved[13] |= 0x2000;
#endif


#if 1
    regs0->reset = 
        HW_RESET_RISC       |
        HW_RESET_BOOTROM    |
        HW_RESET_FLASHIF    |
//        HW_RESET_RI         |
//        HW_RESET_SDCTRL     |
        HW_RESET_AGDC       |
        HW_RESET_GRFX       |
        HW_RESET_PARM       |
        HW_RESET_IDCT       |
        HW_RESET_INVQ       |
        HW_RESET_VLD        |
        HW_RESET_MC         |
        HW_RESET_TRANS      |
        HW_RESET_MMU        |
        HW_RESET_BUFCTL;
#endif

    while(1);
}


#define AWAKE_STOP_HW
//#define AWAKE_STOP_PLL

//
// FUNCTION
// hwif_reset_sleep2
//
// DESCRIPTION
// enable-sleep..
//
// current status
// kernel: about 30mA
// io: about 45mA
//
void hwif_reset_sleep2(int awake)
{    
    hwif_printf("<hwif_reset_sleep2, in>\n");

    if (awake==0) 
    {
        hwif_printf("<hwif_reset_sleep,in>\n");
        hwif_reset_sleep();
        hwif_printf("<hwif_reset_sleep,out>\n");
    }

#if !defined(SPHE1000) && !defined(SPHE8202)
    // (8200) enable sdram output when tri-state
    regs0->g6_reserved[10] = 0x2;
    regs0->g2_reserved[13] |= 0x2000;
#endif

#ifdef  AWAKE_STOP_HW
    regs0->reset2 = 
        HW_RESET_OGT        
        | HW_RESET_VPP        
        | HW_RESET_OSD       
//       | HW_RESET_TV       
//       | HW_RESET_IOP      
        | HW_RESET_DSP       
        #if !defined(SUPPORT_DVB_BOOKING)&&!defined(USE_STANDBY_STC)    //Jack added USE_STANDBY_STC for general use 06/08/14
        |HW_RESET_STC  ///yangli mark ,for dvb booking,2005-11-30 10:01    
        #endif
        | HW_RESET_CD        
        | HW_RESET_CSS       
        | HW_RESET_HOST 
        | HW_RESET_LPT 
//        | HW_RESET_UA0
//        | HW_RESET_UA1        
        | HW_RESET_TDM        
        | HW_RESET_BRIDGE         
        ;

    regs0->clken1 &= ~ (
        HW_RESET_TV
#ifndef SPHE1000
        | HW_RESET_SRV
#endif
        );
#endif

    // wait until VPP/OSD idle
    {
        int i;
        for (i=0;i<100;i++) asm volatile ("nop");
    }

    hwif_printf("<tv,audio,plla off>\n");
    hwif_disable_tvdacs();                  // disable TV DAC
    hwif_disable_audio();                   // disable audio

#ifdef  AWAKE_STOP_PLL
    hwif_disable_plla();                // disable audio PLLs
#endif

    hwif_printf("<setup_sdctrl_sref>\n");
//    setup_sdctrl_sref();            // setup SDRAM to use self-refresh
//potatooo suggest to mark it.20050823 When 8202d-32M-RISC-ALIVE-STANDBY, player can't power on.

#ifdef  AWAKE_SLOWDOWN
    // change system clock
    {
        extern int change_system_clock(int);
        int cfg;
        cfg = cpu_intr_disable();

#ifdef HWIF_DBG        
        hwif_printf("<note:> baud rate set to 9600\n");delay_1ms(100);        
#endif        
        change_system_clock(1);  //potatooo,2004/7/5 10:48PM
        cpu_intr_config(cfg);
        UART0_set_baudrate(BAUDCC(9600, 6750000));
        hwif_printf("<note:> baud rate,testing ...\n");
    }
#endif
    
    hwif_printf("<hwif_enable_iop_rstsys,in>\n");
    hwif_enable_iop_rstsys();

    // final reset
#ifdef  AWAKE_STOP_HW
    regs0->reset = 
//        HW_RESET_RISC       |
//        HW_RESET_BOOTROM    |
//        HW_RESET_FLASHIF    |
//        HW_RESET_RI         |
//        HW_RESET_SDCTRL     |
        HW_RESET_AGDC       |
        HW_RESET_GRFX       |
        HW_RESET_PARM       |
        HW_RESET_IDCT       |
        HW_RESET_INVQ       |
        HW_RESET_VLD        |
        HW_RESET_MC         |
        HW_RESET_TRANS      |
        HW_RESET_MMU        |
        HW_RESET_BUFCTL;
#endif

        hwif_printf("<hwif_reset_sleep2, out>\n");
}


#if 0
//
// FUNCTION
// hwif_doze
//
void hwif_doze(int n)
{
  if (n<16) configure_sdram_timing(n<<12);
}

//
// FUNCTION
// hwif_chipver()
//
int
hwif_chipver(void)
{
    return regs0->stamp & 0xff;
}
#endif

