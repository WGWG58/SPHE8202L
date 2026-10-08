//
// FILE
// crt0.S
// 
// DESCRIPTION
// initialize system and jump to C program
//
#include "regdef.h"
#include "gpio.h"
#include "config.h"
#include "regmapa.h"
#include "user_init.h"
#include "rommap_rom.h" //terry,2005/3/6 09:04PM

#define PROBE_SDRAM
#define CLEAR_SDRAM
#define CLEAR_STACK

#ifndef DVDRELEASE //terry,2005/6/27 08:32¤U¤È
#define SDRAM_DBG
#endif

//#define BOOTSTRAP_STAMP
//#define BOOTSTRAP_SETUP_UART
//#define BOOTSTRAP_WRITE_UART


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


//
// HWCFG
//
#ifdef  SPHE8202
	#ifdef  SPHE8202_NONSHARED
		#ifdef  SDRAM_BUS_32BITS
			#define HWCFG_SET   0x3f       // 32-bit SDRAM 8-bit ROM mode f (non-shared)
		#else
			#define HWCFG_SET   0x1f       // 16-bit SDRAM 8-bit ROM mode f (non-shared)
		#endif
	#else
		#ifdef  SDRAM_BUS_32BITS
			#define HWCFG_SET   0x31       // 32-bit SDRAM 8-bit ROM mode 1 (shared)
		#else
			#define HWCFG_SET   0x11       // 16-bit SDRAM 8-bit ROM mode 1 (shared)
		#endif
	#endif
#else
	// ORIGINAL 8200
	#ifdef  SDRAM_BUS_32BITS
		#define HWCFG_SET   1          // hw config fig.1 MPEG+servo+32b
	#else
		#define HWCFG_SET   2          // hw config fig.2 MPEG+servo+16b
	#endif
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



                .text
                .global     start
                .global     __main
                .global     s_gp
                .global     set_sdram_timing
                .global     set_sdram_timing_low

                .extern     _stkbtm

                .rdata    
s_gp:           .word    _gp
s_rominit:      .word    rominit

                .text

#ifdef SPHE1000
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
				li		s0, 0x10101010
				bne		t8, s0, start_4189
				jr		t9
			.end	start_4189
#endif

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
#ifdef SPHE1000
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
#else
                // write HWCFG
                li      t1, ('X'<<8)|HWCFG_SET
                sw      t1, RF_HW_CFG_CHG(s6)           // write HWCFG
1:              lw      t2, RF_HW_CFG_CHG(s6)           // wait update HWCFG
                andi    t2, (1<<11)
                bnez    t2, 1b

#ifdef  BOOT_HALF
                // change sysclk back to 114.75*2
                li      t1, 4
                li      t2, 2
                sw      t1, RF_SYSCLK_DIV_SEL(s6)
                sw      t2, RF_SYSCLK_SEL(s6)
                li      t3, 1000
1:              addiu   t3, -1
                bnez    t3, 1b
                sw      zero, RF_SYSCLK_DIV_SEL(s6)     // (2,0) (229.5, 114.75*2)
#else
                // change sysclk back to 108mhz
                li      t1, 4
                li      t2, 1
                sw      t1, RF_SYSCLK_DIV_SEL(s6)
                sw      t2, RF_SYSCLK_SEL(s6)
                li      t3, 1000
1:              addiu   t3, -1
                bnez    t3, 1b
                sw      zero, RF_SYSCLK_DIV_SEL(s6)     // (1,0)
#endif
#endif


                // reset sub-systems
#ifdef RISC_ALIVE_STANDBY  
                //terry,2005/4/4 04:47¤U¤È, 
                //fix standby to power on risc GPIO floating .
                li      t2, 0x8010                
                sw      t2, RF_RESET2(s6)               // reset #2
#else                
                li      t1, 0xffe0
                li      t2, 0xffff
                sw      t1, RF_RESET(s6)                // reset #1 
                sw      t2, RF_RESET2(s6)               // reset #2
#endif                

                sw      zero, RF_RESET(s6)              // freerun #1
                sw      zero, RF_RESET2(s6)             // freerun #2

                nop; nop; nop; nop;                     // must delay??

                WRITESTAMP(STAMP_STARTUP)

#if 0
                li      t1, ROM_CFG_VAL
                sw      t1, ROM_CONFIG(s6)
#endif

#ifdef  BOOTSTRAP_SETUP_UART
                // init uart
                #if defined(IC_8202L)
                li      t1, 0x24
                sw      t1, RF_SFT_CFG2(s6)
                #endif
                
                li      t1, 0
                li      t2, 58                          // 115200@108MHz
                sw      t1, RF_UART0_DIV_H(s6)
                sw      t2, RF_UART0_DIV_L(s6)
                sw      t1, RF_UART1_DIV_H(s6)
                sw      t2, RF_UART1_DIV_L(s6)
                PUTC('R'); PUTC('O'); PUTC('M'); 
                PUTC(' '); PUTC('S'); PUTC('T'); PUTC('A'); PUTC('R'); PUTC('T'); 
                PUTC(0x0d); PUTC(0x0a)
#endif

                
                
#ifdef  BOOTSTRAP_WRITE_UART
#ifdef  BOOT_LOAD_ROMA //terry,2005/3/6 08:07PM
                PUTC('R'); PUTC('O'); PUTC('M'); PUTC('A');                
#endif                
#ifdef  BOOT_LOAD_ROMB
                PUTC('R'); PUTC('O'); PUTC('M'); PUTC('B');                
#endif          
                PUTC('T'); PUTC('S'); PUTC('T');
                lw a0,RF_HW_CFG(s6); PUTA0
                PUTC(0x0d); PUTC(0x0a)
#endif


#ifdef BOOT_LOAD_ROMA //terry,2005/3/6 08:07PM
                li     a0,ROMB_CHK_SUM_ST
                li     a1,ROMB_CHK_SUM_END
                jal    rom_checksum_per_kbyte

                move   a0,v0
                move   t0,v0
                PUTA0
                PUTC(0x0d); PUTC(0x0a)                
                
                move   v0,t0
                beqz   v0,2f
                li     t1,0x88000000+ORG_romB_real_start  // real romB code address
                jr     t1                
2:
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


#ifdef  CLEAR_SDRAM
                // clear SDRAM (2MByte)
                la      a0, 0x80000000
                la      a1, 0x80000000 + 2048*1024
                li      v0, 0x00
1:
                sw      v0, 0(a0)
                sw      v0, 4(a0)
                sw      v0, 8(a0)
                sw      v0, 12(a0)
                addiu   a0, 16
                bne     a0,a1,1b
#endif

                // reset STK buffer 
                WRITESTAMP(STAMP_CLEAR_STACK)
                la      sp, _stkptr                     // set up stack pointer
#ifdef CLEAR_STACK
                la      t0, _stkbtm        
                lui     v0, 0xfade
                ori     v0, 0xfade
1:              sw      v0, 0(t0)                        // writing initial value
                addiu   t0, 4
                bne     t0, sp, 1b
#endif

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

#ifdef  BOOTSTRAP_WRITE_UART
                PUTC('A'); PUTC(0x0d); PUTC(0x0a)
                PUTC('d'); PUTC('v'); PUTC('d'); PUTC('_');                
                PUTC('m'); PUTC('a'); PUTC('i'); PUTC('n');                
                PUTC(0x0d); PUTC(0x0a)
#endif

#ifdef  BOOTSTRAP_TEST_SDRAM
                .extern test_sdram
                j       test_sdram
#endif

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
#include "sdctrl_8202.inc"

//
// __main
//
                .ent    __main
__main:
                lw    gp, s_gp
                jr    ra
                .end    __main


