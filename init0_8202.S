/*
** FILE
** init0.S
**
** DESCRIPTION
** the bootstrap ROM code for VCD/SVCD/DVD systems.
** it located in several places and serves as the 
** exception-handler, also.
*/

#include "regdef.h"
#include "regmapa.h"
#include "intdef.h"
#include "pu8560.h"
#include "user_init.h"

#include "rommap_rom.h" //terry,2005/3/6 09:34PM

//
// CONSTANT
// CUSTOMER_ID_STRING[16]
//
// Used for all code to identify the system vender
//
#ifndef CUSTOMER_ID_STRING
#define CUSTOMER_ID_STRING  "SUNPLUS"
#endif


#define RGST_BASE    0xbffe8000
#define SPURIOUS_PANIC
//#define CACHE_SMALL

//
//    RESET:    0xbfc0_0000
//
// BEV0:
//    TLBL:    0x8000_0000
//    GENINT:    0x8000_0080
// BEV1:
//    TLBL:    0xbfc0_0100
//    GENINT: 0xbfc0_0180
//


                .text
                
                .global __romstart
                .global __boot_entry
                .extern rom_checksum_per_kbyte
                
                .extern    start
                .extern    s_gp

#ifdef SPHE1000
                .global s_gp

                .rdata    
s_gp:           .word   _gp
#endif

                .text


                //
                // 8800 start
                //
                .ent     __romstart
__romstart:
                .set    noreorder
#if defined(IC_8202D) || defined(IC_8203A) || defined(IC_8202L)
                ori v0, 0xabcd          // for detecting SPI flash on PS2.5
#else                
                nop                     // required tag        
#endif                
                nop
                b       __realstart
                nop
                .set        reorder

                .global     CFG_sdram_config
                .global     CFG_sdram_config_PS21
                .global     CFG_kernel

                .org        ORG_VERSION_STRING
                .asciiz     VERSION_STRING

                //recode MPEG UI Version(Kernal version move to Kernel.a)//nono 2004-4-17 17:47
                .org        ORG_MPEG_UI_VERSION
                //.asciiz     KERNEL_VERSION
                .asciiz     MPEG_UI_VERSION
                .org        ORG_BOOT_ROM_CHK_SUM
                #ifdef SPHE1000		//wrwu,2005/04/25, Linux kernel will read KERNEL_VERSION to block old rom code
                .asciiz     KERNEL_VERSION
                #else
                .asciiz     MPEG_UI_VERSION
                #endif

                .end        __romstart


                // FATAL interrupt sources
                .extern    exception_panic            // Other sources of exception
                .extern    exception_mmu            // MMU caused exception
                .extern    intr_panic                // Spurious interrupt panic

                .extern    intr_ri_watchdog        // RI Watchdog interrupt (fatal)
                .extern    intr_sd                 // SDRAM over-range interrupt (fatal)
                .extern    intr_ls_watchdog        // LSWITCH Watchdog interrupt (fatal)
                .extern    intr_watchdog            // Watchdog timer interrupt (fatal)

                // #0
                .extern    intr_field_end
                .extern    intr_field_start
                .extern    intr_pic_end
                .extern    intr_h_pio
                .extern    intr_h_device
                .extern    intr_timer0
                .extern    intr_timer1
                .extern    intr_decerr
                .extern    intr_risc4
                .extern    intr_risc3
                .extern    intr_risc2
                .extern    intr_risc1

                // #1
                .extern    intr_timer3b
                .extern    intr_timer3a
                .extern    intr_timer2b
                .extern    intr_timer2a
                .extern    intr_tdmtx
                .extern    intr_tdmrx
        

                .text
                .align  4
/*
** intr_null:
*/
intr_null:
                jr        ra                    // do nothing, just return.

/*
** pseudo entry point
*/
                .org    ORG__boot_entry
__boot_entry:
                .set    noreorder
                nop
                nop
                b       __realstart
                nop
                .set    reorder

/*
** EXCEPTION ENTRY POINT: 8000_0080
**
** when STATUS.BEV = 0
*/
                .org    ORG__exception_bev0
                .global    __exception_bev0
__exception_bev0:
#if 0
                // fall thru __exception_arise
#include "intdrv.S"
#else
                .extern    __exception_arise
                j        __exception_arise
#endif                

                //
                // SDRAM configuration table, currently not used
                //
                .org        ORG_CFG_sdram_config

CFG_sdram_config:        
#if defined(SPHE8202)||defined(SPHE1000)
#include "sdram.h"
                .short      CFG_SDRAM_OUT           // 90
                .short      CFG_SDRAM_IN            // 92
                .short      CFG_SDRAM_IN_DLY        // 94
                .short      CFG_SDRAM_PADCTRL       // 96
                
CFG_sdram_config_PS21:                
                .short      CFG_SDRAM_OUT_PS21      // 98
                .short      CFG_SDRAM_IN_PS21       // 9a
                .short      CFG_SDRAM_IN_DLY_PS21   // 9c
                .short      CFG_SDRAM_PADCTRL_PS21  // 9e
#else
                // 8200
                .short      (1<<3)|(0)              // 90: OUT0
                .short      (3<<3)|(1)              // 92: IN0
                .short      (0<<3)|(0)              // 94: OUT1 (not used now)
                .short      (2<<3)|(1)              // 96: IN1  (not used now)
                .short      (0<<3)|(0)              // 98: OUT2 (not used now)
                .short      (2<<3)|(1)              // 9a: IN2  (not used now)
#endif

                .org        ORG_CFG_kernel0
CFG_kernel0:    .byte       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
CFG_kernel1:    .byte       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff

                .org        ORG_CUSTOMER_ID_STRING
CFG_customers:  .asciiz     CUSTOMER_ID_STRING

                .text
                .align  4
//
// invalidate data cache
//
                .global invalidate_dcache
                .global invalidate_idcache
                .ent    invalidate_dcache
invalidate_dcache:
invalidate_idcache:

#define CCTL_DInval     (1<<0)
#define CCTL_IInval     (1<<1)
#define CCTL_ILockOn    (1<<2)
#define CCTL_ILockMode  (1<<3)
#define CCTL_IWFreeze   (1<<4)
#define CCTL_IC2way     (1<<5)
#define CCTL_IC2wayEn   (1<<6)

#ifdef  CACHE_SMALL
#define CCTL_MASK       (CCTL_DInval|CCTL_IInval|CCTL_IWFreeze|CCTL_ILockOn|CCTL_ILockMode)
#else
#define CCTL_MASK       (CCTL_DInval|CCTL_IInval|CCTL_IWFreeze)
//#define CCTL_MASK       (CCTL_DInval|CCTL_IInval|CCTL_IC2way|CCTL_IC2wayEn)
#endif
                // invalidate/reset instruction/data cache
                mfc0    v1, C0_CCTL
                andi    v1, 0xFFFF^(CCTL_IWFreeze)
                andi    v0, v1, 0xFFFF^CCTL_MASK
                ori     v1, CCTL_MASK
                mtc0    v0, C0_CCTL         //
                nop; nop; nop; nop
                mtc0    v1, C0_CCTL         //
                nop; nop; nop; nop
                jr     ra
                .end    invalidate_dcache


//
// reserved external filled data area
//
                .org        ORG_reserved_area
                .asciiz     "reserved area"

                .org        ORG_CFG_kernel2
CFG_kernel2:    .byte       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
CFG_kernel3:    .byte       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
CFG_kernel4:    .byte       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
CFG_kernel5:    .byte       0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff

//
// __realstart
//
                .ent    __realstart
__realstart:

#ifdef    EJTAG_DEBUG
                mfc0    t0, C0_STATUS
                li      t1, 0x02000000
                or      t0, t1
                mtc0    t0, C0_STATUS

                nop
                nop
                la      t0, 0xa1100000        // write to the maic address
                sw      zero, 0(t0)         
                la      t2, 0x10101010        // check data pattern
1:
                lw      t1, 0(t0)
                bne     t2, t1, 1b

                la      t0, 0xa1100004        // load t1 with address
                lw      t1, 0(t0)
                nop

                jr    t1
#endif    /*EJTAG_DEBUG*/


#ifdef ALCO_PORTABLE
//terry add for alco reset & screen issue 0912//shenyj
#define         DLY_TIMES  0xfff

#if 0
                li      s6, 0xbffe8000
                li      t1, 0xffe0
                li      t2, 0xffff
                sw      t1, RF_RESET(s6)                // reset #1 
                sw      t2, RF_RESET2(s6)               // reset #2
                sw      t1, 0
                sw      t2, 0
                li      t1, -1
                sw      t1, RF_TV_MODE_6+5*4(s6)
#endif
                
                li      t2, DLY_TIMES
               
2:                
                addiu   t2,-1
                bnez    t2,2b
#endif //end #ifdef ALCO_PORTABLE

                jal     invalidate_idcache

#ifdef BOOT_LOAD_ROMA //terry,2005/3/6 09:34PM,move to crt0.s
/*                li     a0,ROMB_CHK_SUM_ST
                li     a1,ROMB_CHK_SUM_END
                jal    rom_checksum_per_kbyte
                
                beqz    v0,2f
                li      t1,0x88000000+ROMB_START  // real romB code address
                jr      t1                
2:*/
#endif
                //
                // jump to cached region
                //                
                la      t0, start
                jr      t0
                .end    __realstart


#if 0
                .ent    invalidate_idcache
                .global invalidate_idcache
invalidate_idcache:
                //
                // invalidate/reset cache
                //
                .set    noreorder
                mtc0    zero, C0_CCTL
                li      t0, 0x0073      // ??
                mtc0    t0, C0_CCTL
                nop; nop
                li      t0, 0x0010      // IWFreeze
                mtc0    t0, C0_CCTL
                .set    reorder
                nop; nop
                jr      ra
                .end    invalidate_idcache
#endif


