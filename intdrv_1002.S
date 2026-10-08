//
// FILE
// intdrv.S
//
// DESCRIPTION
// interrupt service routines.
//

#include "ver.h"
#include "regdef.h"
#include "intdef.h"
#include "user_init.h"
#include "set.h"
#include "rommap_rom.h"  //terry,2005/3/6 11:24PM
#include "regmapa.h"

#define RGST_BASE    0xbffe8000
#define TASK_ENTRY    4

//#define SPURIOUS_PANIC

//#define SUPPORT_INTR_SW0
//#define SUPPORT_INTR_SW1
//#define SUPPORT_INTR_HW2
//#define SUPPORT_INTR_HW3
//#define SUPPORT_INTR_HW4
//#define SUPPORT_INTR_HW5

#ifndef DVDRELEASE
#define SUPPORT_UART0_FIFO
#endif

#define INTR_UART0_VECTOR   intr_uart0_null
#define INTR_UART1_VECTOR   intr_uart1_null

#ifdef  SUPPORT_UART0_FIFO
#undef  INTR_UART0_VECTOR
#define INTR_UART0_VECTOR   intr_uart0_fifo
#endif
#ifdef  SUPPORT_UART1_FIFO
#undef  INTR_UART1_VECTOR
#define INTR_UART1_VECTOR   intr_uart1_fifo
#endif

#define ERET(r)             \
        .set    noreorder;      \
        jr      r;              \
        rfe;                    \
        .set    reorder

//Madison_Modify [2005.10.28]
// ==================================
#define WAIT(n)     \
        .set noat; li AT,(n); 100: addiu AT,-1; bnez AT,100b; .set at

#define TX_EMPTY    (1<<6)
#define WAITUART()  \
        .set noat; 100: lw AT,RF_UART0_LSR(s6); andi AT,TX_EMPTY; beqz AT,100b; .set at

#define PUTC(c)     \
        WAITUART(); \
        .set noat; li AT,(c); sw AT,RF_UART0_DATA(s6); .set at

#define PUTCR(c)     \
        WAITUART(); \
        sw c,RF_UART0_DATA(s6)


// PUTA0_0
// write v0(v1) to UART (v1 should be radix-table)
#define PUTA0_0 \
        andi v1,0x0f; add v1,v0; lbu v1,(v1); PUTCR(v1)


// PUTA0
// write a0 to UART
        .extern radix_table
#define PUTK1  \
        la  v0,radix_table;     \
        srl v1,k1,28; PUTA0_0; \
        srl v1,k1,24; PUTA0_0; \
        srl v1,k1,20; PUTA0_0; \
        srl v1,k1,16; PUTA0_0; \
        srl v1,k1,12; PUTA0_0; \
        srl v1,k1,8; PUTA0_0;  \
        srl v1,k1,4; PUTA0_0;  \
        srl v1,k1,0; PUTA0_0;  \
        PUTC(0x0d); PUTC(0x0a)

// ==================================

/*
** FUNCTION
** __exception_arise
**
** DESCRIPTION
** first exception-handler
** 1. check C0_CAUSE for exception_cause [IP7-IP0]
*/
                .global    __exception_arise
                .ent    __exception_arise
                .extern    start_boot_romB_intr_tbl
                
__exception_arise:

#ifdef BOOT_LOAD_ROMA   //terry,2005/2/21 10:54AM             
               
                la      k0,start_boot_romB_intr_tbl
                lb      k1,0(k0)
                beqz    k1,__exception_arise1
                
                li      k0,0x88000000+ROMB_START+ORG__exception_bev0
                jr      k0

__exception_arise1:
#endif
                mfc0    k0, C0_CAUSE            // load C0_CAUSE
                li      k1, EXCCODE_Int<<2    
                andi    k0, (0x001f<<2)         // extract exception-code field
                                                // .EEE-EE..
                                                // CP0_CAUSE[6:2]
                beq     k1, k0, __exception_chk_intr

#ifndef	DVDRELEASE                
                li      k1, EXCCODE_Sys<<2    
                beq     k1, k0, __exception_chk_syscall
#endif
                
                li      k1, EXCCODE_RI<<2
                beq     k1, k0, __exception_chk_ri
                li      k1, EXCCODE_Bp<<2
                beq     k1, k0, __exception_chk_bp
                li      k1, EXCCODE_CpU<<2
                beq     k1, k0, __exception_chk_cpu        
                li      k1, EXCCODE_Ov<<2
                beq     k1, k0, __exception_chk_ov
                li      k1, EXCCODE_AdEL<<2
                beq     k1, k0, __exception_chk_adel
                li      k1, EXCCODE_AdES<<2
                beq     k1, k0, __exception_chk_ades

__exception_chk_ri:
__exception_chk_bp:
__exception_chk_cpu:
__exception_chk_ov:
__exception_chk_adel:
__exception_chk_ades:
                la      k0, exception_panic
                b       __panic_service

__exception_mmu:
                la      k0, exception_mmu
                b       __panic_service
    

//
// __exception_chk_intr:
//
// checking IP7-0
// currently the external interrupt are all wired
// into IntreqN[0] (IntreqN[5:0]), and that is mapped
// into IP2.  Since there are no other interrupt enabled,
// we simple jump to exception_intr
//
__exception_chk_intr:
                mfc0    k0, C0_CAUSE
__exception_chk_intr7:
                andi    k1, k0, CAUSE_IP2            /* INT_GRP_0 */
                bnez    k1, check_inthw0_sources

                andi    k1, k0, CAUSE_IP3            /* INT_GRP_1 */
                bnez    k1, check_inthw1_sources

#ifdef  SUPPORT_INTR_HW2
                andi    k1, k0, CAUSE_IP4          
                bnez    k1, check_inthw2_sources
#endif

#ifdef  SUPPORT_INTR_HW3
                andi    k1, k0, CAUSE_IP5         
                bnez    k1, check_inthw3_sources
#endif

#ifdef  SUPPORT_INTR_HW4
                andi    k1, k0, CAUSE_IP6        
                bnez    k1, check_inthw4_sources
#endif

#ifdef  SUPPORT_INTR_HW5
                andi    k1, k0, CAUSE_IP7       
                bnez    k1, check_inthw5_sources
#endif

#ifdef  SUPPORT_INTR_SW0
                andi    k1, k0, CAUSE_IP0      
                bnez    k1, check_intsw0_sources
#endif

#ifdef  SUPPORT_INTR_SW1
                andi    k1, k0, CAUSE_IP1      
                bnez    k1, check_intsw1_sources
#endif

                b         __exception_leave
        
#ifdef  SUPPORT_INTR_SW0
check_intsw0_sources:
                li      k0, 0
                la      k1, intr_sw0
                b        __interrupt_service
#endif

#ifdef  SUPPORT_INTR_SW1
check_intsw1_sources:
                li      k0, 0
                la      k1, intr_sw1
                b        __interrupt_service
#endif

#ifdef  SUPPORT_INTR_HW2
check_inthw2_sources:
                li      k0, 0
                la      k1, intr_hw2
                b        __interrupt_service
#endif

#ifdef  SUPPORT_INTR_HW3
check_inthw3_sources:
                li      k0, 0
                la      k1, intr_hw3
                b        __interrupt_service
#endif

#ifdef  SUPPORT_INTR_HW4
check_inthw4_sources:
                li      k0, 0
                la      k1, intr_hw4
                b        __interrupt_service
#endif

#ifdef  SUPPORT_INTR_HW5
check_inthw5_sources:
                li      k0, 0
                la      k1, intr_hw5
                b        __interrupt_service
#endif

__exception_leave:
                mfc0    k0, C0_EPC
                ERET(k0)
                .end    __exception_arise


/*
** ENTRY HW0 bit
** check_inthw0_sources:
*/
check_inthw0_sources:
                li      k0, RGST_BASE                   // load register-file-base
                lw      k1, RF_INTR_MASKED_FLAG(k0)     // k1 = int-flag-0
                beqz    k1, __exception_leave

                andi    k0, k1, INTR_FIELD_END          // 10: field_end interrupt
                bnez    k0, __entry_field_end           // 

                andi    k0, k1, INTR_DECERR             // 15: dec-err
                bnez    k0, __entry_decerr

                andi    k0, k1, INTR_PIC_END            // 5: v_pic_end interrupt
                bnez    k0, __entry_pic_end

                andi    k0, k1, INTR_FIELD_START        // 9: field_start interrupt
                bnez    k0, __entry_field_start         // 

                andi    k0, k1, INTR_TIMER0             // 12: timer0 interrupt
                bnez    k0, __entry_timer0

                andi    k0, k1, INTR_TIMER1             // 13: timer1 interrupt
                bnez    k0, __entry_timer1

#if defined(SPHE1000) && defined(SUPPORT_USB)
                andi    k0, k1, INTR_USB             // 13: timer1 interrupt
                bnez    k0, __entry_usb
#endif

//                andi    k0, k1, INTR_H_PIO_INT          // 8: h_pio_int interrupt
//                bnez    k0, __entry_h_pio
//				andi	k0, k1, INTR_DISPATCH_MIPZ		// 1: DISPATCH MIPZ
//				bnez	k0, __entry_srv0

//                andi    k0, k1, INTR_DSP_INT            // 0: dsp interrupt
//                bnez    k0, __entry_dsp
                  
                //Madison_Modify [2005.12.22]      
                andi    k0, k1, INTR_UART0_INT          // 6: UART0
                bnez    k0, __entry_uart0

                andi    k0, k1, INTR_UART1_INT          // 7: UART1
                bnez    k0, __entry_uart1

                // this interrupts is FATAL-ERROR
                andi    k0, k1, INTR_RI_WATCHDOG
                bnez    k0, __entry_ri_watchdog

#ifdef    SPURIOUS_PANIC
                b       spurious_panic
#endif
                // clear this spurious int-flag (#0) and leave
                li      k0, RGST_BASE
                sw      k1, RF_INTR_FLAG(k0)
                b       __exception_leave

/*
** spurious_panic
*/
spurious_panic:
                la      k0, intr_panic                  // intr_panic(intr_flag, epc)
                b       __panic_service

__entry_lswitch_intr:
                la      k0, intr_ls_watchdog
                b       __panic_service

__entry_sdctrl:
                la      k0, intr_sd
                b       __panic_service


__entry_ri_watchdog:
                la      k0, intr_ri_watchdog
                b       __panic_service

__entry_watchdog:
                la      k0, intr_watchdog
                b       __panic_service


/*
** ENTRY
** check_inthw1_sources:
*/
check_inthw1_sources:
                li      k0, RGST_BASE                   // load register-file-base
                lw      k1, RF_INTR1_MASKED_FLAG(k0)    // k1 = int-flag-1
                beqz    k1, __exception_leave
                                
                andi    k0, k1, INTR1_TIMERW
                bnez    k0, __entry_watchdog            // WATCHDOG

//                andi    k0, k1, INTR1_TIMER2A
//                bnez    k0, __entry_timer2a             // TIMER2a

//                andi    k0, k1, INTR1_TIMER2B
//                bnez    k0, __entry_timer2b             // TIMER2b

//                andi    k0, k1, INTR1_TIMER3A
//                bnez    k0, __entry_timer3a             // TIMER3a

//                andi    k0, k1, INTR1_TIMER3B
//                bnez    k0, __entry_timer3b             // TIMER3b
				
				
                // these interrupts are FATAL-ERROR
                andi    k0, k1, INTR1_LSWITCH_INTR_FLAG
                bnez    k0, __entry_ri_watchdog         // WATCHDOG
                
                andi    k0, k1, INTR1_SD
                bnez    k0, __entry_sdctrl              // SDRAM controller

#ifdef    SPURIOUS_PANIC
                b        spurious_panic
#endif

                // clear other unknown interrupt flags and leave
                li        k0, RGST_BASE            
                sw        k1, RF_INTR1_FLAG(k0)
                b        __exception_leave


//
// interrupt vectors #0
//
__entry_field_end:
                la        k1, intr_field_end
                b        __interrupt_service

__entry_field_start:
                la        k1, intr_field_start
                b        __interrupt_service

__entry_pic_end:
                la        k1, intr_pic_end
                b        __interrupt_service

__entry_timer0:
#ifdef	DVDRELEASE
                la        k1, intr_timer0
                b        __interrupt_service
#else
                la        k1, intr_timer0
                b        __taskX_service
#endif

__entry_h_pio:
                la        k1, intr_host_pio
                b        __interrupt_service

__entry_timer1:
                la        k1, intr_timer1
                b        __interrupt_service

__entry_decerr:
                la        k1, intr_decerr
                b        __interrupt_service

__entry_uart0:
                la        k1, INTR_UART0_VECTOR
                b        __interrupt_service

__entry_uart1:
                la        k1, INTR_UART1_VECTOR
                b        __interrupt_service

#if defined(SPHE1000) && defined(SUPPORT_USB)
__entry_usb:    la        k1, uhci_USBISR
				b		 __interrupt_service
#endif

__entry_srv3:
                b        __interrupt_service

__entry_srv2:
                b        __interrupt_service

__entry_srv1:
                b        __interrupt_service
                
__entry_srv0:
#if defined(SPHE1000) && !defined(SINGLE_CPU)
				la        k1, intr_dispatch_mipz
#endif
                b        __interrupt_service

__entry_dsp:
                la        k1,dsp_intr
                b        __interrupt_service

//
// interrupt vectors #1
//
//__entry_risc4:
//                la        k1, intr_risc4
//                b        __interrupt_service

//__entry_risc3:
//                la        k1, intr_risc3
//                b        __interrupt_service

//__entry_risc2:
//                la        k1, intr_risc2
//                b        __interrupt_service

//__entry_risc1:
//                la        k1, intr_risc1
//                b        __interrupt_service
                
//__entry_risc0:
//                la        k1, intr_risc0
//                b        __interrupt1_service

__entry_timer2a:
                la        k1, intr_timer2a
                b        __interrupt1_service

__entry_timer2b:
                la        k1, intr_timer2b
                b        __interrupt1_service

__entry_timer3a:
                la        k1, intr_timer3a
                b        __interrupt1_service

__entry_timer3b:
                la        k1, intr_timer3b
                b        __interrupt1_service
                

/*
** SAVE_REG/LOAD_REG
*/
#include "regloc.h"

#define    SAVE_REG(a,b,c)        sw    a, 4*b(c)
#define    LOAD_REG(a,b,c)        lw    a, 4*b(c)

/*
** INTR_SAVE_REG
** save AT/v0~v1/a0~a3/t0~t9/s6/gp/ra/EPC registers
*/
#define INTR_SAVE_REG()     \
        subu    sp, +4*REGLOCi_NUM;     \
        .set noat;                      \
        SAVE_REG(AT, REGLOCi_AT, sp);   \
        .set at;                        \
        SAVE_REG(v0, REGLOCi_v0, sp);   \
        SAVE_REG(v1, REGLOCi_v1, sp);   \
        mfc0    v0, C0_EPC;             \
        SAVE_REG(a0, REGLOCi_a0, sp);   \
        SAVE_REG(a1, REGLOCi_a1, sp);   \
        SAVE_REG(a2, REGLOCi_a2, sp);   \
        SAVE_REG(a3, REGLOCi_a3, sp);   \
        SAVE_REG(t0, REGLOCi_t0, sp);   \
        SAVE_REG(t1, REGLOCi_t1, sp);   \
        SAVE_REG(t2, REGLOCi_t2, sp);   \
        SAVE_REG(t3, REGLOCi_t3, sp);   \
        SAVE_REG(t4, REGLOCi_t4, sp);   \
        SAVE_REG(t5, REGLOCi_t5, sp);   \
        SAVE_REG(t6, REGLOCi_t6, sp);   \
        SAVE_REG(t7, REGLOCi_t7, sp);   \
        SAVE_REG(t8, REGLOCi_t8, sp);   \
        SAVE_REG(t9, REGLOCi_t9, sp);   \
        SAVE_REG(s6, REGLOCi_s6, sp);   \
        SAVE_REG(gp, REGLOCi_gp, sp);   \
        SAVE_REG(ra, REGLOCi_ra, sp);   \
        SAVE_REG(v0, REGLOCi_EPC, sp); 


/*
** INTR_LOAD_REG
** load AT/v0~v1/a0~a3/t0~t9/s6/gp/ra registers
** load EPC to k1
*/
#define INTR_LOAD_REG()     \
        .set noat;                      \
        LOAD_REG(AT, REGLOCi_AT, sp);   \
        .set at;                        \
        LOAD_REG(v0, REGLOCi_v0, sp);   \
        LOAD_REG(v1, REGLOCi_v1, sp);   \
        LOAD_REG(a0, REGLOCi_a0, sp);   \
        LOAD_REG(a1, REGLOCi_a1, sp);   \
        LOAD_REG(a2, REGLOCi_a2, sp);   \
        LOAD_REG(a3, REGLOCi_a3, sp);   \
        LOAD_REG(t0, REGLOCi_t0, sp);   \
        LOAD_REG(t1, REGLOCi_t1, sp);   \
        LOAD_REG(t2, REGLOCi_t2, sp);   \
        LOAD_REG(t3, REGLOCi_t3, sp);   \
        LOAD_REG(t4, REGLOCi_t4, sp);   \
        LOAD_REG(t5, REGLOCi_t5, sp);   \
        LOAD_REG(t6, REGLOCi_t6, sp);   \
        LOAD_REG(t7, REGLOCi_t7, sp);   \
        LOAD_REG(t8, REGLOCi_t8, sp);   \
        LOAD_REG(t9, REGLOCi_t9, sp);   \
        LOAD_REG(s6, REGLOCi_s6, sp);   \
        LOAD_REG(gp, REGLOCi_gp, sp);   \
        LOAD_REG(ra, REGLOCi_ra, sp);   \
        LOAD_REG(k1, REGLOCi_EPC, sp);  \
        addiu    sp, +4*REGLOCi_NUM;


#define TASK_LOAD_REG(r)       \
        .set noat;                      \
        LOAD_REG(k1, REGLOC_EPC, r);    \
        LOAD_REG(AT, REGLOC_AT, r);     \
        LOAD_REG(v0, REGLOC_v0, r);     \
        LOAD_REG(v1, REGLOC_v1, r);     \
        LOAD_REG(a0, REGLOC_a0, r);     \
        LOAD_REG(a1, REGLOC_a1, r);     \
        LOAD_REG(a2, REGLOC_a2, r);     \
        LOAD_REG(a3, REGLOC_a3, r);     \
        LOAD_REG(t0, REGLOC_t0, r);     \
        LOAD_REG(t1, REGLOC_t1, r);     \
        LOAD_REG(t2, REGLOC_t2, r);     \
        LOAD_REG(t3, REGLOC_t3, r);     \
        LOAD_REG(t4, REGLOC_t4, r);     \
        LOAD_REG(t5, REGLOC_t5, r);     \
        LOAD_REG(t6, REGLOC_t6, r);     \
        LOAD_REG(t7, REGLOC_t7, r);     \
        LOAD_REG(s0, REGLOC_s0, r);     \
        LOAD_REG(s1, REGLOC_s1, r);     \
        LOAD_REG(s2, REGLOC_s2, r);     \
        LOAD_REG(s3, REGLOC_s3, r);     \
        LOAD_REG(s4, REGLOC_s4, r);     \
        LOAD_REG(s5, REGLOC_s5, r);     \
        LOAD_REG(s6, REGLOC_s6, r);     \
        LOAD_REG(s7, REGLOC_s7, r);     \
        LOAD_REG(t8, REGLOC_t8, r);     \
        LOAD_REG(t9, REGLOC_t9, r);     \
        LOAD_REG(gp, REGLOC_gp, r);     \
        LOAD_REG(sp, REGLOC_sp, r);     \
        LOAD_REG(fp, REGLOC_fp, r);     \
        LOAD_REG(ra, REGLOC_ra, r);     \
        .set at

/*
** __interrupt_service:
**
** when entering this point:
**    k0: interrupt_flag (to be cleared)
**    k1: interrupt routine
**
** save only caller-saved registers
** AT
** v0/v1
** a0/a1/a2/a3
** t0/t1/t2/t3/t4/t5/t6/t7/t8/t9
** s6 (load with register-pointer)
** gp (load with global-pointer)
** ra
*/
                .global __interrupt_service
                .ent    __interrupt_service
__interrupt_service:

                INTR_SAVE_REG()

                lw      gp, s_gp                        /* setup $gp                    */
                li      s6, RGST_BASE                   /* load global pointer (s6)     */
                lw      v0, RF_INTR_FLAG(s6)            /* load interrupt flag in v0    */
                sw      k0, RF_INTR_FLAG(s6)            /* clear interrupt flag         */

__interruptXXX:
//#ifdef  DVDRELEASE
#if 1
                jalr    k1                              /* call to service routine      */
#else
                move    a0, k1
                addiu   sp, -8

                lw      v0, RF_INTR_MASK(s6)
                lw      v1, RF_INTR1_MASK(s6)
                sw      v0, 4(sp)
                sw      v1, 0(sp)
                li      v0, INTR_RI_WATCHDOG
#ifdef ENABLE_SDRAM_OV_RANGE_INTR
                li      v1, INTR1_SD|INTR1_LSWITCH_INTR_FLAG|INTR1_TIMERW
#else
                li      v1, INTR1_LSWITCH_INTR_FLAG|INTR1_TIMERW
#endif

                sw      v0, RF_INTR_MASK(s6)
                sw      v1, RF_INTR1_MASK(s6)

                // enable interrupt
                mfc0    v1, C0_STATUS     
                ori     v1, STATUS_IEc
                mtc0    v1, C0_STATUS
                jalr    a0

                // disable interrupt
                mfc0    v1, C0_STATUS     
                ori     v1, STATUS_IEc
                xori    v1, STATUS_IEc
                mtc0    v1, C0_STATUS

                // restore mask
                lw      v0, 4(sp)
                lw      v1, 0(sp)
                sw      v0, RF_INTR_MASK(s6)
                sw      v1, RF_INTR1_MASK(s6)
                addiu   sp, 8
#endif

                INTR_LOAD_REG()
                ERET(k1)
                .end    __interrupt_service


/*
** __interrupt1_service:
**
** when entering this point:
**    k0: interrupt_flag (to be cleared)
**    k1: interrupt routine
**
** save only caller-saved registers
** AT
** v0/v1
** a0/a1/a2/a3
** t0/t1/t2/t3/t4/t5/t6/t7/t8/t9
** s6 (load with register-pointer)
** gp (load with global-pointer)
** ra
*/

                .global __interrupt1_service
                .ent    __interrupt1_service
__interrupt1_service:

                INTR_SAVE_REG()

                lw      gp, s_gp                    /* setup $gp                    */
                li      s6, RGST_BASE                /* load global pointer (s6)        */
                lw      v0, RF_INTR1_FLAG(s6)        /* load interrupt flag in v0    */
                sw      k0, RF_INTR1_FLAG(s6)        /* clear interrupt flag            */
                b       __interruptXXX
#if 0
                jalr    k1                            /* call to service routine        */

                INTR_LOAD_REG()
                ERET(k1)
#endif
                .end    __interrupt1_service



/*
** __taskX_service:
**
** when entering this point:
**    k0: interrupt_flag (to be cleared)
**    k1: interrupt routine
**
** save ALL registers
** fp/ra
*/
#ifndef	DVDRELEASE
                .extern task_state;
                .global __taskX_service
                .ent    __taskX_service
__taskX_service:
                sw      t0, -4(sp)

                la      t0, task_state
                lw      t0, TASK_ENTRY(t0)    /* task_table_entry        */

                SAVE_REG(v0, REGLOC_v0, t0)
                SAVE_REG(v1, REGLOC_v1, t0)
        
                move    v0, t0
                lw      t0, -4(sp)

                .set    noat
                SAVE_REG(AT, REGLOC_AT, v0)
                .set    at

                mfc0    v1, C0_EPC        /* load EPC in v1        */
__taskX_service2:
                SAVE_REG(a0, REGLOC_a0, v0)
                SAVE_REG(a1, REGLOC_a1, v0)
                SAVE_REG(a2, REGLOC_a2, v0)
                SAVE_REG(a3, REGLOC_a3, v0)
                SAVE_REG(t0, REGLOC_t0, v0)
                SAVE_REG(t1, REGLOC_t1, v0)
                SAVE_REG(t2, REGLOC_t2, v0)
                SAVE_REG(t3, REGLOC_t3, v0)
                SAVE_REG(t4, REGLOC_t4, v0)
                SAVE_REG(t5, REGLOC_t5, v0)
                SAVE_REG(t6, REGLOC_t6, v0)
                SAVE_REG(t7, REGLOC_t7, v0)
                SAVE_REG(s0, REGLOC_s0, v0)
                SAVE_REG(s1, REGLOC_s1, v0)
                SAVE_REG(s2, REGLOC_s2, v0)
                SAVE_REG(s3, REGLOC_s3, v0)
                SAVE_REG(s4, REGLOC_s4, v0)
                SAVE_REG(s5, REGLOC_s5, v0)
                SAVE_REG(s6, REGLOC_s6, v0)
                SAVE_REG(s7, REGLOC_s7, v0)
                SAVE_REG(t8, REGLOC_t8, v0)
                SAVE_REG(t9, REGLOC_t9, v0)
                SAVE_REG(gp, REGLOC_gp, v0)
                SAVE_REG(sp, REGLOC_sp, v0)
                SAVE_REG(fp, REGLOC_fp, v0)
                SAVE_REG(ra, REGLOC_ra, v0)

                SAVE_REG(v1, REGLOC_EPC, v0)    /* save EPC            */

                lw      gp, s_gp                /* reload gp                */
                li      s6, RGST_BASE           /* load global pointer S6   */
                sw      k0, RF_INTR_FLAG(s6)    /* clear interrupt flag     */
                jalr    k1                      /* call to service routine  */

                la      k0, task_state
                lw      k0, TASK_ENTRY(k0)      /* task_table_entry         */

                TASK_LOAD_REG(k0)               /* load reg from k0 and write EPC to k1 */
                ERET(k1)
                .end    __taskX_service

#endif
/*
** __panic_service
**
** when entering this point:
**    k0: interrupt routine
**
** NOTE:
**   1. save ALL registers
**   2. no return
*/
                .ent    __panic_service
__panic_service:

#ifndef	DVDRELEASE
                la    k1, task_state
                lw    k1, TASK_ENTRY(k1)            /* load task_table_entry */

                SAVE_REG(v0, REGLOC_v0, k1)
                SAVE_REG(v1, REGLOC_v1, k1)
        
                mfc0 v1, C0_EPC                     /* load EPC in v1        */
                move v0, k1

                lw   zero, 0(v1)                    /* load in d-cache      */
                lw   zero, 16(v1)                   /* load in d-cache      */
                lw   zero, 32(v1)                   /* load in d-cache      */
                lw   zero, 48(v1)                   /* load in d-cache      */

                .set    noat
                SAVE_REG(AT, REGLOC_AT, v0)
                .set    at
                SAVE_REG(a0, REGLOC_a0, v0)
                SAVE_REG(a1, REGLOC_a1, v0)
                SAVE_REG(a2, REGLOC_a2, v0)
                SAVE_REG(a3, REGLOC_a3, v0)
                SAVE_REG(t0, REGLOC_t0, v0)
                SAVE_REG(t1, REGLOC_t1, v0)
                SAVE_REG(t2, REGLOC_t2, v0)
                SAVE_REG(t3, REGLOC_t3, v0)
                SAVE_REG(t4, REGLOC_t4, v0)
                SAVE_REG(t5, REGLOC_t5, v0)
                SAVE_REG(t6, REGLOC_t6, v0)
                SAVE_REG(t7, REGLOC_t7, v0)
                SAVE_REG(s0, REGLOC_s0, v0)
                SAVE_REG(s1, REGLOC_s1, v0)
                SAVE_REG(s2, REGLOC_s2, v0)
                SAVE_REG(s3, REGLOC_s3, v0)
                SAVE_REG(s4, REGLOC_s4, v0)
                SAVE_REG(s5, REGLOC_s5, v0)
                SAVE_REG(s6, REGLOC_s6, v0)
                SAVE_REG(s7, REGLOC_s7, v0)
                SAVE_REG(t8, REGLOC_t8, v0)
                SAVE_REG(t9, REGLOC_t9, v0)
                SAVE_REG(gp, REGLOC_gp, v0)
                SAVE_REG(sp, REGLOC_sp, v0)
                SAVE_REG(fp, REGLOC_fp, v0)
                SAVE_REG(ra, REGLOC_ra, v0)
                SAVE_REG(v1, REGLOC_EPC, v0)        /* save EPC            */

#endif
                lw      gp, s_gp                    // reload gp
                li      s6, RGST_BASE               // load global pointer s6
                jalr    k0                          // jump to target
                // no return
                .end    __panic_service


#ifndef	DVDRELEASE
//
// SYSCALL handler
//
__exception_chk_syscall:
                la      k0, task_state
                lw      k0, TASK_ENTRY(k0)        // k0: task_table_entry

                // save at/v0/v1 into task-table
                .set    noat
                SAVE_REG(v0, REGLOC_v0, k0)
                SAVE_REG(v1, REGLOC_v1, k0)
                move v0, k0
                SAVE_REG(AT, REGLOC_AT, v0)
                .set    at

                //
                // call to task-switching routine
                //
                // v0/v1/at saved
                // k0: flag
                // k1: intr-vect
                // v1: EPC
                //
                mfc0    v1, C0_EPC              // load EPC in v1
                li      k0, 0                   // FLAG: 0
                la      k1, intr_timer0         // INTR: timer0
                addiu   v1, 4                   // v1=v1+4
                b       __taskX_service2
#endif

