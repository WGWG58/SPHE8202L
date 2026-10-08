//
// FILE
// sdctrl.inc
// 
// DESCRIPTION
// SDRAM related 
//
#include "regdef.h"
#include "gpio.h"
#include "config.h"
#include "regmapa.h"
#include "user_init.h"


#define PROBE_SDRAM

/*
** SDRAM interface setup
*/
#include "sdctrl.h"


//#define SPCA728_720_TIMING

#define SDRAM_USE_K4S641632
#ifdef  SDRAM_USE_K4S641632     // K4S641632F-75 CL=3
//#define FSYS    1215            // in 0.1MHz
#define FSYS    1080            // in 0.1MHz
#define TRAS    450             // in 0.1ns scale
#define TRCD    200             // in 0.1ns scale
#define TRC     650             // in 0.1ns scale
#define TRP     200             // in 0.1ns scale
#define TCYC    (100000/FSYS)   // in 0.1ns
// cal
#define nRASv   (TRAS+TCYC-1)/TCYC
#define nRCDv   (TRCD+TCYC-1)/TCYC
#define nRCv    (TRC+TCYC-1)/TCYC
#define nRPv    (TRP+TCYC-1)/TCYC
// setup
#define nRAS    nRASv 
#define nRC     nRCv
#define nMRD    2   
#define nRFC    nRC
#define nRCD    nRCDv           // 2    2
#define nRP     nRPv            // 2    2
#define nRRD    2               // 1    2       
#define nWR     2               // 2    2
#define nCL     3               // 2    3
#endif


// check SDRAM timing limit
#if nRAS>8
#error SDRAM timing nRAS<=8
#endif
#if nRCD>4
#error SDRAM timing nRCD<=4
#endif


// CFG0 (default 0x023c)
#define SDCTRL_CFG0_VAL_0       SDCTRL_CFG0_RAS(nRAS)           \
                                | SDCTRL_CFG0_RC(nRC)           \
                                | SDCTRL_CFG0_MRD(nMRD)

#define SDCTRL_CFG0_VAL_SET     SDCTRL_CFG0_VAL_0

// CFG1 (default 0x59A7)
#define SDCTRL_CFG1_VAL_0       SDCTRL_CFG1_RFC(nRFC)           \
                                | SDCTRL_CFG1_RCD(nRCD)         \
                                | SDCTRL_CFG1_RP(nRP)           \
                                | SDCTRL_CFG1_RRD(nRRD)         \
                                | SDCTRL_CFG1_WR(nWR) 
#define SDCTRL_CFG1_VAL_1       SDCTRL_CFG1_CL(nCL)

#define SDCTRL_CFG1_VAL_SET     SDCTRL_CFG1_VAL_0 | SDCTRL_CFG1_VAL_1


// CFG2 (default 0x0037)
#define SDCTRL_CFG2_VAL_0       SDCTRL_CFG2_BL_8                \
                                | SDCTRL_CFG2_BT_SEQUENTIAL     \
                                | SDCTRL_CFG2_OP_NORMAL         \
                                | SDCTRL_CFG2_BE_PROGRAMMED
#define SDCTRL_CFG2_VAL_1       SDCTRL_CFG2_CL_3
#define SDCTRL_CFG2_VAL_SET     SDCTRL_CFG2_VAL_0 | SDCTRL_CFG2_VAL_1

// CFG3
#define SDCTRL_CFG3_VAL_0       (SDCTRL_CFG3_CKE_EN | SDCTRL_CFG3_PRERAS_EN | SDCTRL_CFG3_BURST_8)
#define SDCTRL_CFG3_VAL_1       SDCTRL_CFG3_INF_16B
#define SDCTRL_CFG3_VAL_DEF     (SDCTRL_CFG3_VAL_0 | SDCTRL_CFG3_VAL_1)                // when using probing
#define SDCTRL_CFG3_VAL_2       (SDCTRL_CFG3_2PS)
#define SDCTRL_CFG3_VAL_SET     (SDCTRL_CFG3_VAL_0 | SDCTRL_CFG3_VAL_1 | SDCTRL_CFG3_VAL_2)


// CFG4
#define SDCTRL_CFG4_VAL_16M     (SDCTRL_CFG4_CW(7) | SDCTRL_CFG4_RW(10) | SDCTRL_CFG4_PALL(10) | SDCTRL_CFG4_BANK4(0))
#define SDCTRL_CFG4_VAL_64M     (SDCTRL_CFG4_CW(7) | SDCTRL_CFG4_RW(11) | SDCTRL_CFG4_PALL(10) | SDCTRL_CFG4_BANK4(1))
#define SDCTRL_CFG4_VAL_128M    (SDCTRL_CFG4_CW(8) | SDCTRL_CFG4_RW(12) | SDCTRL_CFG4_PALL(10) | SDCTRL_CFG4_BANK4(1))
#define SDCTRL_CFG4_VAL_256M    (SDCTRL_CFG4_CW(8) | SDCTRL_CFG4_RW(12) | SDCTRL_CFG4_PALL(10) | SDCTRL_CFG4_BANK4(1))
#define SDCTRL_CFG4_VAL_SET     SDCTRL_CFG4_VAL_16M

// SREF
#define SDCTRL_SREF_VAL_SET SDCTRL_SREF_SEL(1)        // 63 cycle

// AREF
#define SDCTRL_AREF1_VAL_SET    (SDCTRL_AREF1_ENABLE \
                                | SDCTRL_AREF1_AUTOREF \
                                | SDCTRL_AREF1_REFCNT(4) \
                                | SDCTRL_AREF1_SEL(AREF1_SEL(SDCLK,4)) )

                .text
                .global     set_sdram_timing
                .global     set_sdram_timing_low
                .global     setup_sdctrl
                .global     setup_sdctrl_sref

                .text

//
// FUNCTION
// setup_sdctrl()
//
// Setup SDRAM controller
//
                .ent    setup_sdctrl
setup_sdctrl:
                // configure sdram timing
                li      t0, SDCTRL_CFG0_VAL_SET
                li      t1, SDCTRL_CFG1_VAL_SET
                li      t2, SDCTRL_CFG2_VAL_SET
    
                sw      t0, RF_SDCTRL_CFG0(s6)
                sw      t1, RF_SDCTRL_CFG1(s6)
                sw      t2, RF_SDCTRL_CFG2(s6)

                li      t1, SDCTRL_SREF_VAL_SET
                sw      t1, RF_SDCTRL_SREF_CFG(s6)

                li      t1, SDCTRL_AREF1_VAL_SET
                sw      t1, RF_SDCTRL_AREF1_CFG(s6)

                // CFG3: configure sdram interface
                li      t3, SDCTRL_CFG3_VAL_SET
                sw      t3, RF_SDCTRL_CFG3(s6)

                // write sdram mrs
                WRITESTAMP(STAMP_SDRAM_MRS)
                li      t1, 1
                sw      t1, RF_SDCTRL_MRS(s6)            // write MRS

                // wait MRS
                WAIT(0x4000)

                // return
                jr      ra
                .end    setup_sdctrl


//
// FUNCTION
// setup_sdctrl_sref()
//
                .ent    setup_sdctrl_sref
setup_sdctrl_sref:
                li      t1, SDCTRL_SREF_SEL(100)
                sw      t1, RF_SDCTRL_SREF_CFG(s6)
                li      t1, SDCTRL_AREF1_ENABLE|SDCTRL_AREF1_SELFREF|SDCTRL_AREF1_REFCNT(4)|SDCTRL_AREF1_SEL(200)
                sw      t1, RF_SDCTRL_AREF1_CFG(s6)
                jr      ra
                .end    setup_sdctrl_sref


//
// FUNCTION
// set_sdram_timing
//
                .ent    set_sdram_timing
set_sdram_timing:
                // new style timing setting                
                la      t0, CFG_sdram_config            // (t0): SDRAM config table (in init0.S)
 
                lhu     t1, 0(t0)                       // get OUT cfg
                lhu     t2, 2(t0)                       // get IN cfg
                lhu     t3, 4(t0)                       // get IN_DLY cfg
                lhu     t4, 6(t0)                       // get PADCTRL cfg
                sw      t1, RF_SDRAM_CLKO_CFG(s6)       // write OUT cfg
                sw      t2, RF_SDRAM_CLKI_CFG(s6)       // write IN cfg
                sw      t3, RF_SDRAM_CLKI_DLY_CFG(s6)   // write IN_DLY cfg
                sw      t4, RF_PAD_CTRL(s6)             // write PADCTRL cfg
                
                jr      ra
                .end    set_sdram_timing


//
// FUNCTION
// set_sdram_timing_low()
//
// DESCRIPTION
// System low-speed SDRAM timing setting
//
                .ent    set_sdram_timing_low
set_sdram_timing_low:
                li v0,(0x04<<3)|(0x00); sw v0,RF_SDRAM_CLKO_CFG(s6)
                li v0,(0x04<<3)|(0x00); sw v0,RF_SDRAM_CLKI_CFG(s6)
                li v0,(0x00); sw v0,RF_SDRAM_CLKI_DLY_CFG(s6)
                jr      ra
                .end    set_sdram_timing_low


//
// FUNCTION
// probe_sdram_type
//
// DESCRIPTION
// This function will probe SDRAM type from 256MB to 16MB
// and set RF_SDCTRL_CFG3 register accordingly.
//
// *NOTE*
// 1. Default value SDCTRL_CFG3_VAL_DEF will be used.
// 2. Assume x16 and 2-SDRAM configuration.
//
#define    SDRAM_BASE_TESTED    0xA0000000

                .ent    probe_sdram_type
error_sdram:
#ifdef BOOTSTRAP_WRITE_UART
                PUTC('E'); PUTC('R'); PUTC('R');
                PUTCR(v0);
                PUTC(0x0d); PUTC(0x0a)

                // try write 00000000
                li      v0, 0x00000000
                sw      v0, (t3)
                jal     flush_lbc_buffer
                lw      a0, (t3)
                PUTA0

                // try write FFFFFFFF
                li      v0, 0xffffffff
                sw      v0, (t3)
                jal     flush_lbc_buffer
                lw      a0, (t3)
                PUTA0

                // try write 01234567
                li      v0, 0x01234567
                sw      v0, (t3)
                jal     flush_lbc_buffer
                lw      a0, (t3)
                PUTA0

                // try write ABCDEF01
                li      v0, 0xabcdef01
                sw      v0, (t3)
                jal     flush_lbc_buffer
                lw      a0, (t3)
                PUTA0

1:
                li      v0, 0x01234567
                sw      v0, (t3)
                jal     flush_lbc_buffer
                b       1b
#endif	// BOOTSTRAP_WRITE_UART
1:
                b       1b

probe_sdram_type:
                move    a3, ra
                li      t1, 0x01234567            // t1: tag #1
                li      t2, 0xfedcba98            // t2: tag #2
                la      t3, 0xA0000000            // t3: sdram startingpoint

                // default to 4-bank and max row/column
                li      t7, SDCTRL_CFG4_CW(13)|SDCTRL_CFG4_RW(13)|SDCTRL_CFG4_PALL(10)|SDCTRL_CFG4_BANK4(1)
                sw      t7, RF_SDCTRL_CFG4(s6)
                sw      zero, (t3)              // store 0 to column 0

                li      t4, 6                   // scan from 6: (col=a0~a6)
                li      t6, 128*2*2             // 128 2-bank 16-bit
1:
                addu    t7, t3, t6
                sw      t1, (t7)                // store tag#1 column +256/512/....
                jal     flush_lbc_buffer
                lw      t7, (t3)                // reload column 0
                bnez    t7, column_probed       // has been overwrittened by something

                addiu   t4, 1
                sll     t6, 1
                b       1b

column_probed:
                li      v0, '0'
                bne     t7, t1, error_sdram

                /*
                ** PROBE ROW
                */
                // set to cw=a0~a5 (64w)
                li      t7, SDCTRL_CFG4_CW(5)|SDCTRL_CFG4_RW(15)|SDCTRL_CFG4_PALL(10)|SDCTRL_CFG4_BANK4(1)
                sw      t7, RF_SDCTRL_CFG4(s6)
                sw      zero, (t3)              // store 0 to column 0 (t3)

                li      t5, 6<<4                // row: a0~a6
                li      t6, 128*64*2*2          // bank 2 column 64 width 2
2:
                addu    t7, t3, t6
                sw      t1, (t7)                // store row+t6
                jal     flush_lbc_buffer
                lw      t7, (t3)                // load row0
                bnez    t7, row_probed

                addiu   t5, 1<<4
                sll     t6, 1
                b       2b

row_probed:
                li      v0, '1'
                bne     t7, t1, error_sdram
                or      t4, t5                    // save to t4                
                /*
                ** PROBE BANK
                */
                // set to cw=a0~a5 (64w)  rw=a0~a1
                li      t7, SDCTRL_CFG4_CW(5)|SDCTRL_CFG4_RW(1)|SDCTRL_CFG4_PALL(10)|SDCTRL_CFG4_BANK4(1)
                sw      t7, RF_SDCTRL_CFG4(s6)
                sw      zero, (t3)                // store column 0

                li      t6, 64*4*2*2

                addu    t7, t3, t6
                sw      t1, (t7)                // load column +256/512/....
                jal     flush_lbc_buffer
                lw      t7, (t3)                // load column 0
                bnez    t7, bank_probed
                ori     t4, SDCTRL_CFG4_BANK4(1)
bank_probed:

                /*
                ** PROBE FINISHED
                */
                ori     t4, SDCTRL_CFG4_PALL(10)
                sw      t4, RF_SDCTRL_CFG4(s6)

                jr      a3


flush_lbc_buffer:
                li      v0, 3
                sw      v0, RF_LBC_CONTROL(s6)
1:
                lw      v0, RF_LBC_CONTROL(s6)
                andi    v0, 1
                bnez    v0, 1b
                jr      ra

                .end    probe_sdram_type


