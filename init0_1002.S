#include "regdef.h"
#include "regmapa.h"
#include "intdef.h"
#include "pu8560.h"
#include "user_init.h"


//
// CONSTANT
// CUSTOMER_ID_STRING[16]
//
// Used for all code to identify the system vender
//
#ifndef CUSTOMER_ID_STRING
#define CUSTOMER_ID_STRING  "SUNPLUS"
#endif


#define    RGST_BASE    0xbffe8000
#define    SPURIOUS_PANIC

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

                .global s_gp

                .rdata    
s_gp:           .word   _gp

                .text


                //
                // 8800 start
                //
                .ent     __romstart
__romstart:
                .set    noreorder
                
                ori v0, 0xabcd          // for detecting SPI flash on PS2.5
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
//                .asciiz     KERNEL_VERSION

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
                //.extern    intr_risc4
                //.extern    intr_risc3
                //.extern    intr_risc2
                //.extern    intr_risc1

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
                .extern    __exception_arise
                j        __exception_arise

                //
                // SDRAM configuration table, currently not used
                //
                .org        ORG_CFG_sdram_config

CFG_sdram_config:        
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
                .ent    invalidate_dcache
invalidate_dcache:
                // invalidate/reset data cache
                mfc0    v1, C0_CCTL
                andi    v0, v1, 0xFFFC      // mask LSB=0
                ori     v1, 0x0003
                mtc0    v0, C0_CCTL         //
                nop; nop
                nop; nop
                mtc0    v1, C0_CCTL         //
                nop; nop
                nop; nop
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

                //Madison_Modify [2006.03.03]
                jal     invalidate_idcache
                
                //Madison_Modify [2006.03.03]
                /*
                // ============================================
                //invalidate_idcache
                
                
                //change to write-back mode
                ori    t0, zero, 0x80
                mfc0   t1, $20
                or     t2, t0, t1
                mtc0   t2, $20
                nop
                
                //invalidate_idcache
                
                // ============================================
                */

                //
                // jump to cached region
                //                
                la      t0, start
                jr      t0
                .end    __realstart


                .ent    invalidate_idcache
                .global invalidate_idcache
invalidate_idcache:
                //
                // invalidate/reset cache
                //
                .set    noreorder
                mtc0    zero, C0_CCTL
                li      t0, 0x00000073
                mtc0    t0, C0_CCTL
                nop; nop
                li      t0, 0x00000010
                mtc0    t0, C0_CCTL
                .set    reorder
                nop; nop
                jr      ra
                .end    invalidate_idcache

