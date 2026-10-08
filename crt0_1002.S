//
// FILE
// crt0_1002.S
// 
// DESCRIPTION
// initialize system and jump to C program
//

#include "regdef.h"
#include "gpio.h"
#include "config.h"
#include "regmapa.h"
#include "user_init.h"

#define PROBE_SDRAM
#define CLEAR_STACK
#define SDRAM_DBG
#define BOOTSTRAP_STAMP
#define BOOTSTRAP_SETUP_UART
#define BOOTSTRAP_WRITE_UART
#define BOOTSTRAP_TEST_SDRAM


#define STATUS_ENDIAN_LITTLE    (0<<25)

#define STATUS_SETUP            STATUS_COP0|STATUS_ENDIAN_LITTLE|STATUS_BEV
                                // | STATUS_COP3        \
                                // | STATUS_BEV         \
                                // | STATUS_ENDIAN_BIG

//
// Debug
// terry,2005/1/31 09:56AM
#ifdef SDRAM_DBG
#define BOOTSTRAP_SETUP_UART
#define BOOTSTRAP_WRITE_UART
#endif

#define STATUS_SETUP_B          STATUS_COP0|STATUS_ENDIAN_LITTLE

//
// HWCFG
//
// ORIGINAL 8200
#ifdef  SDRAM_BUS_32BITS
#define HWCFG_SET   1          // hw config fig.1 MPEG+servo+32b
#else
#define HWCFG_SET   2          // hw config fig.2 MPEG+servo+16b
#endif


//
// STAMPS
//
#define STAMP_STARTUP           (0<<8)
#define STAMP_SDRAM_MRS         (1<<8)
#define STAMP_SDRAM_PROBE       (2<<8)
#define STAMP_SDRAM_PROBE_ERROR (STAMP_SDRAM_PROBE|0xf0)
#define STAMP_CLEAR_STACK       (5<<8)
#define STAMP_SETUP_GP          (6<<8)
#define STAMP_ROMINIT           (7<<8)
#define STAMP_MAIN              (9<<8)


#ifdef BOOTSRAP_STAMP
#define WRITESTAMP(n) \
        .set noat; \
        li AT,(n); \
        sw AT,RF_STAMP(s6); \
        .set at
#else
#define WRITESTAMP(n)
#endif


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
#define PUTA0  \
        la  v0,radix_table;     \
        srl v1,a0,28; PUTA0_0; \
        srl v1,a0,24; PUTA0_0; \
        srl v1,a0,20; PUTA0_0; \
        srl v1,a0,16; PUTA0_0; \
        srl v1,a0,12; PUTA0_0; \
        srl v1,a0,8; PUTA0_0;  \
        srl v1,a0,4; PUTA0_0;  \
        srl v1,a0,0; PUTA0_0;  \
        PUTC(0x0d); PUTC(0x0a)

#if 0
	#undef	PUTC
	#define	PUTC(c)
	
	#undef	PUTA0
	#define	PUTA0
#endif
                .text
                .global     start
                .global     __main
                .global     ss_gp
                .extern		s_gp
                .global     set_sdram_timing
                .global     set_sdram_timing_low

                .extern     _stkbtm

                .rdata    
ss_gp:          .word    _gp
s_rominit:      .word    rominit

                .text

//
// Definition for sunplus's processors
//
#define PRID_SUNPLUS_LX4189		(0x9B407286)
#define PRID_SUNPLUS_MIPZ		(0x97350120)

//
// void start_4189
//
			.ent	start_4189
start_4189:
halt_4189:		j		halt_4189

			.end	start_4189

//
// void start(void)
//
// *no-return*
//
                .ent     start
start:
                // ENABLE COP0/3
                mfc0    t1, C0_STATUS
                li      t0, STATUS_SETUP
                mtc0    t0, C0_STATUS
                nop
                nop
                
                // setup register-file pointer
                li      s6, RGST_OFFSET

                //
                // Setup hardware configuration
                //
                mfc0	t1, C0_PRID
                li      t2, PRID_SUNPLUS_LX4189
                beq     t1, t2, start_4189

                // write HWCFG
                lw      a0, RF_HW_CFG(s6)
                ori     a0, a0, (0x8000)
                sw      a0, RF_HW_CFG_CHG(s6)
1:              lw      t2, RF_HW_CFG_CHG(s6)           // wait update HWCFG
                andi    t2, (1<<11)
                bnez    t2, 1b
continue:

                // reset sub-systems
                li      t1, 0xffe0
                li      t2, 0xffff
                sw      t1, RF_RESET(s6)                // reset #1 
                sw      t2, RF_RESET2(s6)               // reset #2
                sw      zero, RF_RESET(s6)              // freerun #1
                sw      zero, RF_RESET2(s6)             // freerun #2
                nop; nop; nop; nop;                     // must delay??

                WRITESTAMP(STAMP_STARTUP)

				li		t1, 0x0cf9
				sw		t1, 5888(s6)

                // init uart
                li      t1, 0
                li      t2, 58
                sw      t1, RF_UART0_DIV_H(s6)
                sw      t2, RF_UART0_DIV_L(s6)
                sw      t1, RF_UART1_DIV_H(s6)
                sw      t2, RF_UART1_DIV_L(s6)                               
                

#ifdef  BOOTSTRAP_WRITE_UART
                PUTC('T'); PUTC('S'); PUTC('T');
                lw a0,RF_HW_CFG(s6); PUTA0
                PUTC(0x0d); PUTC(0x0a)
#endif
                //
                // Setup SDRAM controller
                //

                // setup SDRAM interface timing
                move    a0, zero
                jal     set_sdram_timing

                // setup SDRAM controller
                jal     setup_sdctrl

                // probe external SDRAM type
                WRITESTAMP(STAMP_SDRAM_PROBE)
                jal     probe_sdram_type


                // reset STK buffer 
                WRITESTAMP(STAMP_CLEAR_STACK)
                la      sp, _stkptr                     // set up stack pointer
                la      t0, _stkbtm        
                lui     v0, 0xfade
                ori     v0, 0xfade
1:              sw      v0, 0(t0)                        // writing initial value
                addiu   t0, 4
                bne     t0, sp, 1b

                // setup others variables.
                WRITESTAMP(STAMP_SETUP_GP)
                lw      gp, s_gp                        // set up GP

                // setup
                WRITESTAMP(STAMP_ROMINIT)
                lw      t0, s_rominit                    // init ROM image of data section
                jalr    t0

                // setup others
                jal     setup_systems
                WRITESTAMP(STAMP_MAIN)

                //==============================================================
                PUTC('D');PUTC('V');PUTC('D');PUTC('_');
                PUTC('M');PUTC('A');PUTC('I');PUTC('N');
                PUTC(0x0D);PUTC(0x0A);
                //--------------------------------------------------------------
                j       dvd_main                        // jump to main routine
                .end    start

//

                .ent    setup_systems
setup_systems:
                jr      ra
                .end    setup_systems

//
// INCLUDE "sdctrl.inc"
// SDRAM related routines
//
#include "sdctrl_1002.inc"

//
// __main
//
                .ent    __main
__main:
                lw    gp, s_gp
                jr    ra
                .end    __main


