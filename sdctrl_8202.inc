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


//#define PROBE_SDRAM

/*
** SDRAM interface setup
*/
#include "sdctrl.h"

#if !defined(IC_8202L)
#define SDRAM_BOOTROM_USE		// get sdram timing parameters from BootROM
#endif

#ifdef SDRAM_BOOTROM_USE
	#define SDRAM_BOOTROM_ADDR	0xbfc00200
	#define SDRAM_BOOTROM_KW	0x4d544453	// 'S', 'D', 'T', 'M'
#endif

#if 0 // orig
#define nRAS    6 
#define nRC     8 
#define nMRD    2
#define nRFC    8
#define nRCD    3
#define nRP     3
#define nRRD    2
#define nWR     2
#define nCL     3
#endif

#if defined(F135)||defined(F141_75)||defined(F148_5)//nono add. 20060413. Because of Potatooo's comment.

#define nRAS    6               // 4    5   6
#define nRC     8               // 5    7   8
#define nMRD    2               // 2    2   2
#define nRFC    8               // 5    7   8
#define nRCD    2               // 2    2   3
#define nRP     2               // 2    2   3
#define nRRD    2               // 1    2   2
#define nWR     2               // 2    2   2
#define nCL     3               // 2    3   3

#else//#if defined(F135)||defined(F141_75)||defined(F148_5)

#ifdef  SDRAM_BUS_32BITS
#define SDRAM_USE_K4S161622
#else
#define SDRAM_USE_K4S641632
#endif


// 16MB
#ifdef  SDRAM_USE_K4S161622     // K4S161622D-TC/L60 CL=3
#define nRAS    7               // tRAS
#define nRC     10              // tRC
#define nMRD    2               // 
#define nRFC    10              // use tRC
#define nRCD    3               // tRCD
#define nRP     3               // tRP
#define nRRD    2               // tRRD
#define nWR     2               // tRDL
#define nCL     3               // CAS latency
#endif


// SLOWER
#ifdef  SDRAM_USE_SLOWER        // slower
#define nRAS    8               // tRAS
#define nRC     11              // tRC
#define nMRD    2               //
#define nRFC    11              // (tRC)
#define nRCD    4               // tRCD
#define nRP     3               // tRP
#define nRRD    2               // tRRD
#define nWR     2               // tRDL
#define nCL     3               // CAS latency
#endif



#ifdef  SDRAM_USE_K4S641632     // K4S641632F-75 CL=3
#define FSYS    1215            // in 0.1MHz
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


#endif//#if defined(F135)||defined(F141_75)||defined(F148_5)


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
#if defined(F135)||defined(F141_75)||defined(F148_5)

#define SDCTRL_CFG2_VAL_0       SDCTRL_CFG2_BL_FULLPAGE         \
                                | SDCTRL_CFG2_BT_SEQUENTIAL     \
                                | SDCTRL_CFG2_OP_NORMAL         \
                                | SDCTRL_CFG2_BE_PROGRAMMED

#else//#if defined(F135)||defined(F141_75)||defined(F148_5)

#define SDCTRL_CFG2_VAL_0       SDCTRL_CFG2_BL_8                \
                                | SDCTRL_CFG2_BT_SEQUENTIAL     \
                                | SDCTRL_CFG2_OP_NORMAL         \
                                | SDCTRL_CFG2_BE_PROGRAMMED
#endif//#if defined(F135)||defined(F141_75)||defined(F148_5)

#if (nCL==2)
#define SDCTRL_CFG2_VAL_1       SDCTRL_CFG2_CL_2
#else
#define SDCTRL_CFG2_VAL_1       SDCTRL_CFG2_CL_3
#endif

#define SDCTRL_CFG2_VAL_SET     SDCTRL_CFG2_VAL_0 | SDCTRL_CFG2_VAL_1

// CFG3
#if defined(F135)||defined(F141_75)||defined(F148_5)
#define SDCTRL_CFG3_VAL_0       (SDCTRL_CFG3_CKE_EN | SDCTRL_CFG3_PRERAS_EN | SDCTRL_CFG3_BURST_256)
#else//#if defined(F135)||defined(F141_75)||defined(F148_5)
#define SDCTRL_CFG3_VAL_0       (SDCTRL_CFG3_CKE_EN | SDCTRL_CFG3_PRERAS_EN | SDCTRL_CFG3_BURST_8)
#endif//#if defined(F135)||defined(F141_75)||defined(F148_5)

#ifdef    SDRAM_BUS_32BITS
#define SDCTRL_CFG3_VAL_1       SDCTRL_CFG3_INF_32B
#else
#define SDCTRL_CFG3_VAL_1       SDCTRL_CFG3_INF_16B
#endif
#define SDCTRL_CFG3_VAL_DEF     (SDCTRL_CFG3_VAL_0 | SDCTRL_CFG3_VAL_1)                // when using probing
#ifdef SDRAM_1PCS
#define SDCTRL_CFG3_VAL_2       (SDCTRL_CFG3_1PS)
#else
#define SDCTRL_CFG3_VAL_2       (SDCTRL_CFG3_2PS)
#endif

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


//
// override previous definition CFG0/1/2 for 720 mode configuration
//
#ifdef SPCA728_720_TIMING
#undef  SDCTRL_CFG0_VAL_SET
#undef  SDCTRL_CFG1_VAL_SET
#undef  SDCTRL_CFG2_VAL_SET
#define SDCTRL_CFG0_VAL_SET    SDCTRL_CFG0_VAL_720
#define SDCTRL_CFG1_VAL_SET    SDCTRL_CFG1_VAL_720
#define SDCTRL_CFG2_VAL_SET    SDCTRL_CFG2_VAL_720
#endif


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
#ifdef    FIX_SDRAM_BOOTING_PROBLEM
                li      t0, 0
                sw      t0, RF_SDC_REQ_T_RESET(s6)
                WAIT(0x400)
#endif

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


#ifdef  SPHE8202
                // sphe8202
                lw      t1, RF_SFT_CFG8(s6)
                andi    t1, 0x0FFF
                ori     t1, 0x1000
                sw      t1, RF_SFT_CFG8(s6)             // ROM-SDRAM delay max.
                
#if defined(IC_8202E) || defined(IC_8202D) || defined(IC_8202L) || defined(IC_8203A)
                lw      t2, RF_SDCTRL_MISC_B0(s6)
                ori     t2, (1<<15)                     // Use 3-stage pipeline
                ori		t2, (1<<0)						// different SDRAM access the same databus must delay 1 cycle
                sw      t2, RF_SDCTRL_MISC_B0(s6)    
#endif

#if 0
                lw      t2, RF_SDCTRL_MISC_B0(s6)
                ori     t2, (1<<1)
                sw      t2, RF_SDCTRL_MISC_B0(s6)       // Force SDRAM output always
#endif

#else

                // sphe8200
#ifdef SDRAM_BUS_32BITS
                li      t0, 0x5A;
                sw      t0, RF_PAD_CTRL(s6)             // Control pins: full-power
                                                        // DQ pins: 8mA
#endif
#endif

#ifdef SDRAM_BOOTROM_USE
				// check BootROM first
				la      t0, SDRAM_BOOTROM_ADDR            		// (t0): SDRAM config table (in BootROM)
				lw		t1, 0(t0)
				li      t2, SDRAM_BOOTROM_KW            		
				addiu	t0, 6
				beq		t1,t2,9f
				nop
#endif

                // new style timing setting                
                la      t0, CFG_sdram_config            // (t0): SDRAM config table (in init0.S)
#ifdef SPHE8202                
                lw      t2, RF_STAMP(s6)
                li      t1, 0x82                        //  PS2.1 stamp:0x82 ,terry,2005/1/30 08:14PM
                bne     t2,t1,9f
                la      t0, CFG_sdram_config_PS21       // (t0): SDRAM config table (in init0.S)                
#endif
9:             
 
#if defined(SPHE8202)||defined(SPHE1000)
                lhu     t1, 0(t0)                       // get OUT cfg
                lhu     t2, 2(t0)                       // get IN cfg
                lhu     t3, 4(t0)                       // get IN_DLY cfg
                lhu     t4, 6(t0)                       // get PADCTRL cfg
                sw      t1, RF_SDRAM_CLKO_CFG(s6)       // write OUT cfg
                sw      t2, RF_SDRAM_CLKI_CFG(s6)       // write IN cfg
                sw      t3, RF_SDRAM_CLKI_DLY_CFG(s6)   // write IN_DLY cfg
                sw      t4, RF_PAD_CTRL(s6)             // write PADCTRL cfg
                
#else
                lhu     t1, 0(t0)                       // get OUT cfg
                lhu     t2, 2(t0)                       // get IN cfg
                sw      t1, RF_SDRAM_CLKO_CFG(s6)       // write OUT cfg
                sw      t2, RF_SDRAM_CLKI_CFG(s6)       // write IN cfg
#endif

#ifdef SDRAM_DBG //terry,2005/1/31 09:52AM
                lw      a0, RF_STAMP(s6);PUTA0
                move    a0,t0;PUTA0
                move    a0,t1;PUTA0
                move    a0,t2;PUTA0
                move    a0,t3;PUTA0
                move    a0,t4;PUTA0
#endif

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
#endif
#ifdef ERROR_SDRAM_PROBE
                .extern test_sdram
                j       test_sdram
#endif
                WRITESTAMP(STAMP_SDRAM_PROBE_ERROR)
1:
                b       1b


probe_sdram_type:
#ifndef PROBE_SDRAM
                li      t3, SDCTRL_CFG4_VAL_SET
                sw      t3, RF_SDCTRL_CFG4(s6)
                jr      ra
#endif

                move    a3, ra
                li      t1, 0x01234567            // t1: tag #1
                li      t2, 0xfedcba98            // t2: tag #2
                la      t3, 0xA0000000            // t3: sdram startingpoint

                // default to 4-bank and max row/column
                li      t7, SDCTRL_CFG4_CW(13)|SDCTRL_CFG4_RW(13)|SDCTRL_CFG4_PALL(10)|SDCTRL_CFG4_BANK4(1)
                sw      t7, RF_SDCTRL_CFG4(s6)
                sw      zero, (t3)              // store 0 to column 0

                li      t4, 6                   // scan from 6: (col=a0~a6)
#ifdef SDRAM_BUS_32BITS
                li      t6, 128*2*4             // 128 2-bank 32-bit 
#else
                li      t6, 128*2*2             // 128 2-bank 16-bit
#endif
1:
                addu    t7, t3, t6
                sw      t1, (t7)                // store tag#1 column +256/512/....
                jal     flush_lbc_buffer
                lw      t7, (t3)                // reload column 0
#ifdef  BOOTSTRAP_WRITE_UART
                move a0, t7; PUTA0
#endif
                bnez    t7, column_probed       // has been overwrittened by something

                addiu   t4, 1
                sll     t6, 1
                b       1b

column_probed:
                li      v0, '0'
                bne     t7, t1, error_sdram

                WRITESTAMP(STAMP_SDRAM_PROBE | 2)

                /*
                ** PROBE ROW
                */
                // set to cw=a0~a5 (64w)
                li      t7, SDCTRL_CFG4_CW(5)|SDCTRL_CFG4_RW(15)|SDCTRL_CFG4_PALL(10)|SDCTRL_CFG4_BANK4(1)
                sw      t7, RF_SDCTRL_CFG4(s6)
                sw      zero, (t3)              // store 0 to column 0 (t3)

                li      t5, 6<<4                // row: a0~a6
#ifdef SDRAM_BUS_32BITS
                li      t6, 128*64*2*4          // bank 2 column 64 width 4
#else
                li      t6, 128*64*2*2          // bank 2 column 64 width 2
#endif
2:
                addu    t7, t3, t6
                sw      t1, (t7)                // store row+t6
                jal     flush_lbc_buffer
                lw      t7, (t3)                // load row0
#ifdef  BOOTSTRAP_WRITE_UART
                move a0, t7; PUTA0
#endif
                bnez    t7, row_probed

                addiu   t5, 1<<4
                sll     t6, 1
                b       2b

row_probed:
                li      v0, '1'
                bne     t7, t1, error_sdram
                or      t4, t5                    // save to t4

                WRITESTAMP(STAMP_SDRAM_PROBE | 3)
                
                /*
                ** PROBE BANK
                */
                // set to cw=a0~a5 (64w)  rw=a0~a1
                li      t7, SDCTRL_CFG4_CW(5)|SDCTRL_CFG4_RW(1)|SDCTRL_CFG4_PALL(10)|SDCTRL_CFG4_BANK4(1)
                sw      t7, RF_SDCTRL_CFG4(s6)
                sw      zero, (t3)                // store column 0

#ifdef SDRAM_BUS_32BITS
                li      t6, 64*4*2*4
#else
                li      t6, 64*4*2*2
#endif

                addu    t7, t3, t6
                sw      t1, (t7)                // load column +256/512/....
                jal     flush_lbc_buffer
                lw      t7, (t3)                // load column 0
                bnez    t7, bank_probed
                ori     t4, SDCTRL_CFG4_BANK4(1)
bank_probed:

                WRITESTAMP(STAMP_SDRAM_PROBE | 4)

                /*
                ** PROBE FINISHED
                */
                ori     t4, SDCTRL_CFG4_PALL(10)
                sw      t4, RF_SDCTRL_CFG4(s6)

                jr      a3


flush_lbc_buffer:
                WRITESTAMP(STAMP_SDRAM_PROBE | 0x80)
                li      v0, 3
                sw      v0, RF_LBC_CONTROL(s6)
1:
                lw      v0, RF_LBC_CONTROL(s6)
                andi    v0, 1
                bnez    v0, 1b
                jr      ra

                .end    probe_sdram_type


