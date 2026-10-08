//
// FILE
// sdctrl.h
//
#ifndef __SDCTRL_H
#define __SDCTRL_H

//
// SDCTRL_CFG0      timing control #0
// [xsr]    [13:10]
// [mrd]    [9:8]
// [rc]     [7:3]
// [ras]    [3:0]
//
#define SDCTRL_CFG0_RAS(n)          ((n-1)<<0)
#define SDCTRL_CFG0_RC(n)           ((n-1)<<3)
#define SDCTRL_CFG0_MRD(n)          ((n-1)<<8)

//
// SDCTRL_CFG1      timing control #1
// [wr]     [13:12]
// [cl]     [11:10]
// [rrd]    [9:8]
// [rp]     [7:6]
// [rcd]    [5:4]
// [rfc]    [3:0]
//
#define SDCTRL_CFG1_RFC(n)          ((n-1)<<0)
#define SDCTRL_CFG1_RCD(n)          ((n-1)<<4)
#define SDCTRL_CFG1_RP(n)           ((n-1)<<6)
#define SDCTRL_CFG1_RRD(n)          ((n-1)<<8)
#define SDCTRL_CFG1_CL(n)           ((n-1)<<10)
#define SDCTRL_CFG1_WR(n)           ((n-1)<<12)

//
// SDCTRL_CFG2      mrs
//
#define SDCTRL_CFG2_BL_1            (0x00<<0)
#define SDCTRL_CFG2_BL_2            (0x01<<0)
#define SDCTRL_CFG2_BL_4            (0x02<<0)
#define SDCTRL_CFG2_BL_8            (0x03<<0)
#define SDCTRL_CFG2_BL_FULLPAGE     (0x07<<0)

#define SDCTRL_CFG2_BT_SEQUENTIAL   (0x00<<3)
#define SDCTRL_CFG2_BT_INTERLEAVED  (0x01<<3)

#define SDCTRL_CFG2_CL_2            (0x02<<4)
#define SDCTRL_CFG2_CL_3            (0x03<<4)

#define SDCTRL_CFG2_OP_NORMAL       (0x00<<7)

#define SDCTRL_CFG2_BE_PROGRAMMED   (0x00<<9)
#define SDCTRL_CFG2_BE_SINGLE       (0x01<<9)


// 
// SDCTRL_CFG3      sdram type
//

// [0]
#define SDCTRL_CFG3_INF_32B         (0<<0)
#define SDCTRL_CFG3_INF_16B         (1<<0)

#if 0
// [3:1]
#define SDCTRL_CFG3_16MB            (0<<1)
#define SDCTRL_CFG3_32MB            (1<<1)
#define SDCTRL_CFG3_64MB            (2<<1)
#define SDCTRL_CFG3_128MB           (3<<1)
#define SDCTRL_CFG3_256MB           (4<<1)
#define SDCTRL_CFG3_512MB           (5<<1)
// [5:4]
#define SDCTRL_CFG3_NIBBLE          (0<<4)
#define SDCTRL_CFG3_BYTE            (1<<4)
#define SDCTRL_CFG3_SHORT           (2<<4)
#define SDCTRL_CFG3_WORD            (3<<4)
#endif

// [7:6]
#define SDCTRL_CFG3_1PS             (0<<6)
#define SDCTRL_CFG3_2PS             (1<<6)
#define SDCTRL_CFG3_4PS             (2<<6)
#define SDCTRL_CFG3_8PS             (3<<6)
// [8]
#define SDCTRL_CFG3_CKE_DIS         (0<<8)
#define SDCTRL_CFG3_CKE_EN          (1<<8)
// [9]
#define SDCTRL_CFG3_PRERAS_EN       (0<<9)
#define SDCTRL_CFG3_PRERAS_DIS      (1<<9)
// [10]
#define SDCTRL_CFG3_BURST_256       (0<<10)
#define SDCTRL_CFG3_BURST_8         (1<<10)     


#define SDCTRL_CFG4_CW(n)           ((n)<<0)            // column width 7:256 8:512 9:1024
#define SDCTRL_CFG4_RW(n)           ((n)<<4)            // row width 8:512 9:1024 10:2048
#define SDCTRL_CFG4_PALL(n)         ((n)<<8)            // normal at 10
#define SDCTRL_CFG4_BANK4(n)        ((n)<<12)           // 0: 2-bank  1: 4-bank


//
// SDCTRL_SREF  (SREF)
//
#define SDCTRL_SREF_SEL(n)          (n & 0x3ff)         // n = 0~1023, cycle=(n<<5) + 31

//
// SDCTRL_AREF1
//
#define SDCTRL_AREF1_SEL(n)         (n & 0x3ff)         // n = 0~1023, cycle=(n<<5) + 31
#define SDCTRL_AREF1_DISABLE        (0<<10)
#define SDCTRL_AREF1_ENABLE         (1<<10)
#define SDCTRL_AREF1_AUTOREF        (0<<11)             // normal refresh mode
#define SDCTRL_AREF1_SELFREF        (1<<11)             // self-refresh mode
#define SDCTRL_AREF1_REFCNT(n)      ((n-1)<<12)         // 1~4

#define SDCLK                       100000000           // 100-mhz
#define AREF1_SEL(clk, n)           ((156 * clk * n / 10000000) / 32)


//
// 720 style setting
//

//                  720        720  DEF
#define nRASX       4       // 4    5
#define nRCX        5       // 5    7
#define nMRDX       2       // 2    2
#define nRFCX       5       // 5    7
#define nRCDX       2       // 2    2
#define nRPX        2       // 2    2
#define nRRDX       1       // 1    2
#define nWRX        2       // 2    2
#define nCLX        2       // 2    3

#define SDCTRL_CFG0_VAL_720     SDCTRL_CFG0_RAS(nRASX)           \
                                | SDCTRL_CFG0_RC(nRCX)           \
                                | SDCTRL_CFG0_MRD(nMRDX)

#define SDCTRL_CFG1_VAL_720     SDCTRL_CFG1_RFC(nRFCX)           \
                                | SDCTRL_CFG1_RCD(nRCDX)         \
                                | SDCTRL_CFG1_RP(nRPX)           \
                                | SDCTRL_CFG1_RRD(nRRDX)         \
                                | SDCTRL_CFG1_WR(nWRX)           \
                                | SDCTRL_CFG1_CL(nCLX)

#define SDCTRL_CFG2_VAL_720     SDCTRL_CFG2_BL_8                \
                                | SDCTRL_CFG2_BT_SEQUENTIAL     \
                                | SDCTRL_CFG2_OP_NORMAL         \
                                | SDCTRL_CFG2_BE_PROGRAMMED     \
                                | SDCTRL_CFG2_CL_2
#if 0
#define SDCTRL_CFG2_VAL_720     SDCTRL_CFG2_BL_FULLPAGE         \
                                | SDCTRL_CFG2_BT_SEQUENTIAL     \
                                | SDCTRL_CFG2_OP_NORMAL         \
                                | SDCTRL_CFG2_BE_PROGRAMMED     \
                                | SDCTRL_CFG2_CL_2
#endif

//728
//L-type memory
#define SDCTRL_L_TYPE_EN      (1<<12)   
#define SDCTRL_L_TYPE_DIS     (0<<12)   
#define SDCTRL_L_TYPE_W_128   (0<<13)   
#define SDCTRL_L_TYPE_W_256   (1<<13)   

#endif/*__SDCTRL_H*/

