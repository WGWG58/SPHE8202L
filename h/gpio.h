#ifndef __GPIO_H
#define __GPIO_H

// sft_cfg0[0]
#define SFTCFG0_0_RA19_EN           (0<<0)  // (default)
#define SFTCFG0_0_RA19_DIS          (1<<0)

// sft_cfg0[2:1]
#define SFTCFG0_21_RA20_DIS         (0<<1)
#define SFTCFG0_21_RA20_P19         (1<<1)  // (default), when HW config at 3
#define SFTCFG0_21_RA20_P129        (2<<1)  // (default), when HW config at 2

// sft_cfg0[4:3]
#define SFTCFG0_43_RA21_DIS         (0<<3)
#define SFTCFG0_43_RA21_P20         (1<<3)  // (default), when HW config at 3
#define SFTCFG0_43_RA21_P130        (2<<3)  // (default), when HW config at 2

// sft_cfg0[6:5]
#define SFTCFG0_65_RA22_DIS         (0<<5)
#define SFTCFG0_65_RA22_P21         (1<<5)  // (default), when HW config at 3
#define SFTCFG0_65_RA22_P131        (2<<5)  // (default), when HW config at 2

// sft_cfg0[8:7]
#define SFTCFG0_87_RA23_DIS         (0<<7)
#define SFTCFG0_87_RA23_256         (1<<7)  // only available at 256 pin package
#define SFTCFG0_87_RA23_P133        (2<<7)  // (default), when HW config at 2

// sft_cfg0[10:9]
#define SFTCFG0_A9_RA24_DIS         (0<<9)
#define SFTCFG0_A9_RA24_256         (1<<9)  // only available at 256 pin package
#define SFTCFG0_A9_RA24_P134        (2<<9)  // (default), when HW config at 2

// sft_cfg0[12:11]
#define SFTCFG0_CB_RA25_DIS         (0<<11)
#define SFTCFG0_CB_RA25_256         (1<<11) // only available at 256 pin package
#define SFTCFG0_CB_RA25_P135        (2<<11) // (default), when HW config at 2

// sft_cfg0[14:13]
#define SFTCFG0_ED_RA26_DIS         (0<<13)
#define SFTCFG0_ED_RA26_256         (1<<13) // only available at 256 pin package
#define SFTCFG0_ED_RA26_P136        (2<<13) // (default), when HW config at 2

// sft_cfg1[0]
#define SFTCFG1_0_CS1_DIS           (0<<0)  // use pin 69 as GPIO13
#define SFTCFG1_0_CS1_EN            (1<<0)  // (default)

// sft_cfg1[1]
#define SFTCFG1_1_CS2_DIS           (0<<1)
#define SFTCFG1_1_CS2_EN            (1<<1)  // (default)

// sft_cfg1[2]
#define SFTCFG1_2_CS3_DIS           (0<<2)
#define SFTCFG1_2_CS3_EN            (1<<2)  // (default)

// sft_cfg1[3]
#define SFTCFG1_3_CS4_DIS           (0<<3)
#define SFTCFG1_3_CS4_EN            (1<<3)  // (default)

// sft_cfg1[4]
#define SFTCFG1_4_OE_DIS            (0<<4)
#define SFTCFG1_4_OE_EN             (1<<4)  // (default)

// sft_cfg1[5]
#define SFTCFG1_5_WE_DIS            (0<<5)
#define SFTCFG1_5_WE_EN             (1<<5)  // (default)

// sft_cfg1[6]
#define SFTCFG1_6_CHRDY_DIS         (0<<6)  // (default)
#define SFTCFG1_6_CHRDY_EN          (1<<6)

// sft_cfg1[9:7]
#define SFTCFG1_97_IORW_DIS         (0<<7)  // (default)
#define SFTCFG1_97_IORW_P19_P20     (1<<7)  // IOR from pin 19, IOW from pin 20
#define SFTCFG1_97_IORW_P135_P136   (2<<7)  // IOR from pin 135, IOW from pin 136
#define SFTCFG1_97_IORW_P58_P59     (3<<7)  // IOR from pin 58, IOW from pin 59
#define SFTCFG1_97_IORW_256         (4<<7)  // only available at 256 pin package

// sft_cfg1[12:10]
#define SFTCFG1_CA_WAIT_DIS         (0<<10) // (default)
#define SFTCFG1_CA_WAIT_P21         (1<<10) // PCMCIA_WAIT_B from pin 21
#define SFTCFG1_CA_WAIT_P61         (2<<10) // PCMCIA_WAIT_B from pin 61
#define SFTCFG1_CA_WAIT_P129        (3<<10) // PCMCIA_WAIT_B from pin 129
#define SFTCFG1_CA_WAIT_P138        (4<<10) // PCMCIA_WAIT_B from pin 138
#define SFTCFG1_CA_WAIT_256         (5<<10) // only available at 256 pin package

// sft_cfg1[13]
#define SFTCFG1_D_BOOT_ROM          (0<<13) // (default), boot from bfc00000 (internal ROM)
#define SFTCFG1_D_BOOT_SDRAM        (1<<13) // boot from 80000000 (SDRAM)

// sft_cfg1[15:14]
#define SFTCFG1_FE_LPT_DIS          (0<<14) // (default)
#define SFTCFG1_FE_LPT_P62_64       (1<<14) // STB from pin 62, ACK from pin 64
#define SFTCFG1_FE_LPT_P135_136     (2<<14) // STB from pin 135, ACK from pin 136
#define SFTCFG1_FE_LPT_256          (3<<14) // only available at 256 pin package

// sft_cfg2[0]
#define SFTCFG2_0_ATAPI_DIS         (0<<0)  // (default)
#define SFTCFG2_0_ATAPI_EN          (1<<0)

// sft_cfg2[1]
#define SFTCFG2_1_IOP_RESET_DIS     (0<<1)  // (default)
#define SFTCFG2_1_IOP_RESET_EN      (1<<1)  // enable IOP reset RISC

// sft_cfg2[4:2]
#define SFTCFG2_42_UART0_DIS        (0<<2)  // disable UART0
#define SFTCFG2_42_UART0_P19_20     (1<<2)  // UART0 RX from pin 19, TX from pin 20
#define SFTCFG2_42_UART0_P65_66     (2<<2)  // UART0 RX from pin 65, TX from pin 66
#define SFTCFG2_42_UART0_P130_131   (3<<2)  // UART0 RX from pin 130, TX from pin 131
#define SFTCFG2_42_UART0_P144_145   (4<<2)  // UART0 RX from pin 144, TX from pin 145
#define SFTCFG2_42_UART0_P175_176   (5<<2)  // (default), UART0 RX from pin 175, TX from pin 176
#define SFTCFG2_42_UART0_256_1      (6<<2)  // only available at 256 pin package
#define SFTCFG2_42_UART0_256_2      (7<<2)  // only available at 256 pin package

// sft_cfg2[8:5]
#define SFTCFG2_85_UART1_DIS        (0x0<<5)    // (default)
#define SFTCFG2_85_UART1_CFG3       (0x3<<5)    // UART1 RX from pin 41, TX from pin 43
#define SFTCFG2_85_UART1_CFG4       (0x4<<5)    // UART1 CTS from pin 39, RTS from pin 40, RX from pin 41, TX from pin 43
#define SFTCFG2_85_UART1_CFG5       (0x5<<5)    // UART1 DCD from pin 34, RI from pin 35, DSR from pin 37, DTR from pin 38, CTS from pin 39, RTS from pin 40, RX from pin 41, TX from pin 43
#define SFTCFG2_85_UART1_CFG6       (0x6<<5)    // UART1 RX from pin 134, TX from pin 135
#define SFTCFG2_85_UART1_CFG7       (0x7<<5)    // UART1 CTS from pin 136, RTS from pin 138, RX from pin 134, TX from pin 135
#define SFTCFG2_85_UART1_CFG8       (0x8<<5)    // UART1 DCD from pin 145, RI from pin 144, DSR from pin 141, DTR from pin 143, CTS from pin 136, RTS from pin 138, RX from pin 134, TX from pin 135
#define SFTCFG2_85_UART1_CFG9       (0x9<<5)    // UART1 RX from pin 141, TX from pin 143
#define SFTCFG2_85_UART1_CFG10      (0xa<<5)    // UART1 CTS from pin 144, RTS from pin 145, RX from pin 141, TX from pin 143
#define SFTCFG2_85_UART1_CFG11      (0xb<<5)    // UART1 DCD from pin 150, RI from pin 149, DSR from pin 146, DTR from pin 148, CTS from pin 144, RTS from pin 145, RX from pin 141, TX from pin 143
#define SFTCFG2_85_UART1_CFG14      (0xe<<5)    // UART1 RX from pin 29, TX from pin 31
#define SFTCFG2_85_UART1_CFG15      (0xf<<5)    // UART1 RX from pin 70, TX from pin 71

// sft_cfg2[11:9]
#define SFTCFG2_B9_TVLCD_DIS        (0<<9)  // (default)

// sft_cfg2[12]
#define SFTCFG2_C_BRE_DIS           (0<<12) // (default), disable bootstrap
#define SFTCFG2_C_BRE_EN            (1<<12) // enable bootstrap

// sft_cfg2[13]
#define SFTCFG2_D_BRP_DIS           (0<<13) // (default), disable internal pull up at bootstrap RXD (pin 175)
#define SFTCFG2_D_BRP_EN            (1<<13)

// sft_cfg2[14]
#define SFTCFG2_E_BRS_DIS           (0<<14) // (default), bootstrap from UART0
#define SFTCFG2_E_BRS_EN            (1<<14) // from UART1

// sft_cfg2[15]
#define SFTCFG2_F_SWAP_DIS          (0<<15) // (default)
#define SFTCFG2_F_SWAP_EN           (1<<15) // swap UART0 and UART1 signals

// sft_cfg3[2:0]
#define SFTCFG3_20_EADC_DIS         (0<<0)  // (default)
#define SFTCFG3_20_EADC_CFG1        (1<<0)  // BCK from pin 19, LRCK from pin 20, DATA from pin 21
#define SFTCFG3_20_EADC_CFG2        (2<<0)  // BCK from pin 58, LRCK from pin 59, DATA from pin 60
#define SFTCFG3_20_EADC_CFG3        (3<<0)  // BCK from pin 34, LRCK from pin 35, DATA from pin 37
#define SFTCFG3_20_EADC_CFG4        (4<<0)  // BCK from pin 130, LRCK from pin 131, DATA from pin 133
#define SFTCFG3_20_EADC_CFG5        (5<<0)  // BCK from pin 141, LRCK from pin 143, DATA from pin 144
#define SFTCFG3_20_EADC_CFG6        (6<<0)  // only available at 256 pin package

// sft_cfg3[3]
#define SFTCFG3_3_AU2_DIS           (0<<3)  // pin 169 used as GPIO 59
#define SFTCFG3_3_AU2_EN            (1<<3)  // (default)

// sft_cfg3[4]
#define SFTCFG3_4_AU3_DIS           (0<<4)  // pin 170 used as GPIO 60
#define SFTCFG3_4_AU3_EN            (1<<4)  // (default)

// sft_cfg3[5]
#define SFTCFG3_5_AU4_DIS           (0<<5)  // pin 163 used as GPIO 57
#define SFTCFG3_5_AU4_EN            (1<<5)  // (default)

// sft_cfg3[6]
#define SFTCFG3_6_LRCK_DIS          (0<<6)  // pin 171 used as GPIO 61
#define SFTCFG3_6_LRCK_EN           (1<<6)  // (default)

// sft_cfg3[7]
#define SFTCFG3_7_AUD_DIS           (0<<7)  // pin 164 used as GPIO 58, pin 165 used as GPIO 19, pin 166 used as GPIO 20, pin 168 used as GPIO 21, pin 173 used as GPIO 22, pin 174 used as GPIO 23
#define SFTCFG3_7_AUD_EN            (1<<7)  // (default)

// sft_cfg3[8]
#define SFTCFG3_8_SPEED_DIS         (0<<8)  // (default)
#define SFTCFG3_8_SPEED_EN          (1<<8)

// sft_cfg3[11:9]
#define SFTCFG3_B9_SYNC_DIS         (0<<9)  // (default)
#define SFTCFG3_B9_SYNC_CFG1        (2<<9)  // slave mode, HSYNC from pin 146, VSYNC from pin 148
#define SFTCFG3_B9_SYNC_CFG2        (3<<9)  // master mode, HSYNC on pin 146, VSYNC on pin 148
#define SFTCFG3_B9_SYNC_CFG3        (4<<9)  // slave mode, HSYNC from pin 34, VSYNC from pin 35
#define SFTCFG3_B9_SYNC_CFG4        (5<<9)  // master mode, HSYNC on pin 34, VSYNC on pin 35
#define SFTCFG3_B9_SYNC_256_1       (6<<9)  // only available at 256 pin package
#define SFTCFG3_B9_SYNC_256_2       (7<<9)  // only available at 256 pin package

// sft_cfg3[13:12]
#define SFTCFG3_DC_TELETEXT_DIS     (0<<12) // (default)
#define SFTCFG3_DC_TELETEXT_CFG1    (1<<12) // Teletext BIT from pin 149, REQ from pin 150
#define SFTCFG3_DC_TELETEXT_CFG2    (2<<12) // Teletext BIT from pin 37, REQ from pin 38
#define SFTCFG3_DC_TELETEXT_256     (3<<12) // only available at 256 pin package

// sft_cfg3[15:14]
#define SFTCFG3_FE_PCSYNC_DIS       (0<<14) // (default)
#define SFTCFG3_FE_PCSYNC_P175_176  (1<<14) // HSYNC_PC on pin 175, VSYNC_PC on pin 176
#define SFTCFG3_FE_PCSYNC_P146_148  (2<<14) // HSYNC_PC on pin 146, VSYNC_PC on pin 148
#define SFTCFG3_FE_PCSYNC_P144_145  (3<<14) // HSYNC_PC on pin 144, VSYNC_PC on pin 145

// sft_cfg4[2:0]
#define SFTCFG4_20_DSP_FL0_DIS      (0<<0)  // (default)
#define SFTCFG4_20_DSP_FL0_P146     (1<<0)  // DSP_FL0 from pin 146
#define SFTCFG4_20_DSP_FL0_P19      (2<<0)  // DSP_FL0 from pin 19
#define SFTCFG4_20_DSP_FL0_P53      (3<<0)  // DSP_FL0 from pin 53
#define SFTCFG4_20_DSP_FL0_P67      (4<<0)  // DSP_FL0 from pin 67
#define SFTCFG4_20_DSP_FL0_256      (5<<0)  // only available at 256 pin package

// sft_cfg4[5:3]
#define SFTCFG4_53_DSP_FL1_DIS      (0<<3)  // (default)
#define SFTCFG4_53_DSP_FL1_P148     (1<<3)  // DSP_FL1 from pin 148
#define SFTCFG4_53_DSP_FL1_P20      (2<<3)  // DSP_FL1 from pin 20
#define SFTCFG4_53_DSP_FL1_P54      (3<<3)  // DSP_FL1 from pin 54
#define SFTCFG4_53_DSP_FL1_P68      (4<<3)  // DSP_FL1 from pin 68
#define SFTCFG4_53_DSP_FL1_256      (5<<3)  // only available at 256 pin package

// sft_cfg4[8:6]
#define SFTCFG4_86_DSP_FL2_DIS      (0<<6)  // (default)
#define SFTCFG4_86_DSP_FL2_P149     (1<<6)  // DSP_FL1 from pin 149
#define SFTCFG4_86_DSP_FL2_P56      (3<<6)  // DSP_FL1 from pin 56
#define SFTCFG4_86_DSP_FL2_P70      (4<<6)  // DSP_FL1 from pin 70
#define SFTCFG4_86_DSP_FL2_256      (5<<6)  // only available at 256 pin package

// sft_cfg4[11:9]
#define SFTCFG4_B9_DSP_FO_DIS       (0<<9)  // (default)
#define SFTCFG4_B9_DSP_FO_P150      (1<<9)  // DSP_FO from pin 150
#define SFTCFG4_B9_DSP_FO_P21       (2<<9)  // DSP_FO from pin 21
#define SFTCFG4_B9_DSP_FO_P57       (3<<9)  // DSP_FO from pin 57
#define SFTCFG4_B9_DSP_FO_P71       (4<<9)  // DSP_FO from pin 71
#define SFTCFG4_B9_DSP_FO_256       (5<<9)  // only available at 256 pin package

// sft_cfg4[12]
#define SFTCFG4_C_TTIO_DIS          (0<<12) // (default)
#define SFTCFG4_C_TTIO_CFG          (1<<12) // TTIO use pin 26,27,28,29

// sft_cfg4[14:13]
#define SFTCFG4_ED_TDM_DIS          (0<<13) // (default)
#define SFTCFG4_ED_TDM_CFG1         (1<<13) // DX from pin 26, CLK from pin 27, FSXR from pin 28, DR from pin 29
#define SFTCFG4_ED_TDM_CFG2         (2<<13) // DX from pin 153, CLK from pin 154, FSXR from pin 155, DR from pin 156

// sft_cfg5[2:0]
#define SFTCFG5_20_DSP_IN_DIS       (0<<0)  // (default)
#define SFTCFG5_20_DSP_IN_CFG1      (1<<0)  // IN from pin 149, IRQE from pin 150
#define SFTCFG5_20_DSP_IN_CFG2      (2<<0)  // IN from pin 136, IRQE from pin 138
#define SFTCFG5_20_DSP_IN_CFG3      (3<<0)  // IN from pin 29, IRQE from pin 31
#define SFTCFG5_20_DSP_IN_256       (4<<0)  // only available at 256 pin package

// sft_cfg5[8:6]
#define SFTCFG5_86_RISC_INT1_DIS    (0<<6)  // (default)
#define SFTCFG5_86_RISC_INT1_CFG1   (1<<6)  // INT1[11] from pin 141, INT1[12] from pin 143, INT1[13] from pin 144, INT1[14] from pin 145, INT1[15] from pin 146
#define SFTCFG5_86_RISC_INT1_CFG2   (2<<6)  // INT1[11] from pin 129, INT1[12] from pin 130, INT1[13] from pin 131, INT1[14] from pin 133, INT1[15] from pin 134
#define SFTCFG5_86_RISC_INT1_CFG3   (3<<6)  // INT1[11] from pin 29, INT1[12] from pin 31, INT1[13] from pin 34, INT1[14] from pin 35, INT1[15] from pin 37
#define SFTCFG5_86_RISC_INT1_256    (4<<6)  // only available at 256 pin package

// sft_cfg5[11:9]
#define SFTCFG5_B9_RISC_INT52_DIS   (0<<9)  // (default)
#define SFTCFG5_B9_RISC_INT52_CFG1  (1<<9)  // INTRQ_N[2] from pin 141, INTRQ_N[3] from pin 143, INTRQ_N[4] from pin 144, INTRQ_N[5] from pin 145
#define SFTCFG5_B9_RISC_INT52_CFG2  (2<<9)  // INTRQ_N[2] from pin 129, INTRQ_N[3] from pin 130, INTRQ_N[4] from pin 131, INTRQ_N[5] from pin 133
#define SFTCFG5_B9_RISC_INT52_CFG3  (3<<9)  // INTRQ_N[2] from pin 29, INTRQ_N[3] from pin 31, INTRQ_N[4] from pin 34, INTRQ_N[5] from pin 35
#define SFTCFG5_B9_RISC_INT52_256   (4<<9)  // only available at 256 pin package

// sft_cfg5[14:12]
#define SFTCFG5_EC_RISC_INTEXT_DIS  (0<<12) // (default)
#define SFTCFG5_EC_RISC_INTEXT_CFG1 (1<<12) // INTRQ_N[0] from pin 141, INTRQ_N[1] from pin 143, INTRQ_N[2] from pin 144, INTRQ_N[3] from pin 145, INTRQ_N[4] from pin 146, INTRQ_N[5] from pin 148
#define SFTCFG5_EC_RISC_INTEXT_CFG2 (2<<12) // INTRQ_N[0] from pin 129, INTRQ_N[1] from pin 130, INTRQ_N[2] from pin 131, INTRQ_N[3] from pin 133, INTRQ_N[4] from pin 134, INTRQ_N[5] from pin 135
#define SFTCFG5_EC_RISC_INTEXT_CFG3 (3<<12) // INTRQ_N[0] from pin 29, INTRQ_N[1] from pin 31, INTRQ_N[2] from pin 34, INTRQ_N[3] from pin 35, INTRQ_N[4] from pin 37, INTRQ_N[5] from pin 38
#define SFTCFG5_EC_RISC_INTEXT_256  (4<<12) // only available at 256 pin package

// sft_cfg5[15]
#define SFTCFG5_F_BRIT_DIS          (0<<15) // (default)
#define SFTCFG5_F_BRIT_256          (1<<15) // only available at 256 pin package

// sft_cfg6[0]
#define SFTCFG6_0_SCLK_NOT_INVERT   (0<<0)  // MPEG_CLK not invert
#define SFTCFG6_0_SCLK_INVERT       (1<<0)  // (default), invert

// sft_cfg6[1]
#define SFTCFG6_1_SMEM_DIS          (0<<1)
#define SFTCFG6_1_SMEM_EN           (1<<1)  // (default), SERVO/MPEG SDRAM interface enable

// sft_cfg6[2]
#define SFTCFG6_2_SREG_DIS          (0<<2)
#define SFTCFG6_2_SREG_EN           (1<<2)  // (default), SERVO/MPEG register interface enable

// sft_cfg6[3]
#define SFTCFG6_3_SMODE_DIS         (0<<3)  // (default)
#define SFTCFG6_3_SMODE_EN          (1<<3)  // bit2-0 is used to config SERVO/MPEG interface

// sft_cfg6[4]
#define SFTCFG6_4_SA11_DIS          (0<<4)  // pin 109 used as GPIO 14
#define SFTCFG6_4_SA11_EN           (1<<4)  // (default)

// sft_cfg6[5]
#define SFTCFG6_5_SA12_DIS          (0<<5)  // pin 151 used as GPIO 18
#define SFTCFG6_5_SA12_EN           (1<<5)  // (default)

// sft_cfg6[6]
#define SFTCFG6_6_SBA1_DIS          (0<<6)  // pin 121 used as GPIO 15
#define SFTCFG6_6_SBA1_EN           (1<<6)  // (default)

// sft_cfg6[7]
#define SFTCFG6_7_SDQM2_DIS         (0<<7)  // pin 140 used as GPIO 17
#define SFTCFG6_7_SDQM2_EN          (1<<7)  // (default)

// sft_cfg6[8]
#define SFTCFG6_8_SDQM3_DIS         (0<<8)  // pin 139 used as GPIO 16
#define SFTCFG6_8_SDQM3_EN          (1<<8)  // (default)

// sft_cfg6[9]
#define SFTCFG6_9_SPD_DIS           (0<<9)  // (default)
#define SFTCFG6_9_SPD_EN            (1<<9)  // share mode: pin 34,35,37; non-share mode: pin 56,57,58

// sft_cfg6[10]
#define SFTCFG6_A_PLLA1_DIS         (0<<10) // 135 MHz PLLA disable
#define SFTCFG6_A_PLLA1_EN          (1<<10) // (default)

// sft_cfg6[11]
#define SFTCFG6_B_PLLA2_DIS         (0<<11) // 147 MHz PLLA disable
#define SFTCFG6_B_PLLA2_EN          (1<<11) // (default)

// sft_cfg6[12]
#define SFTCFG6_C_TVTET_DIS         (0<<12) // (default)
#define SFTCFG6_C_TVTST_EN          (1<<12)

// sft_cfg6[13]
#define SFTCFG6_D_OSD_TV            (0<<13) // (default)
#define SFTCFG6_D_OSD_PIN           (1<<13)

// sft_cfg6[14]
#define SFTCFG6_E_656_TV            (0<<14) // (default)
#define SFTCFG6_E_656_PIN           (1<<14)




/*
#define GPIOSEL_8_HVSYNC    (1<<8)

//
// GPIO_SEL[]
//

// GPIO_SEL[1:0]
#define GPIOSEL_10_EPP      (0x0<<0)    // EPP
#define GPIOSEL_10_MODEM    (0x1<<0)
#define GPIOSEL_10_UARTS    (0x2<<0)    // 2 UART, for extra GPIO and UART debugging
#define GPIOSEL_10_GPIOS    (0x3<<0)

// GPIO_SEL[5:2]
#define GPIOSEL_52_ATAPI    (0x0<<2)
#define GPIOSEL_52_UDE      (0x1<<2)
#define GPIOSEL_52_UDE2     (0x8<<2)
#define GPIOSEL_52_GPIO     (0xc<<2)

// GPIO_SEL[6]
#define GPIOSEL_6_GPIO      (0<<6)      // 0: RISC_INT3 and IRQE3_L
#define GPIOSEL_6_CLK27M    (1<<6)      // 1: TV-encoder 27M

// GPIO_SEL[7]
#define GPIOSEL_7_GPIO      (0<<7)      // 0: RISC_INT2 and IRQE2_L
#define GPIOSEL_7_PALNTSC   (1<<7)      // 1: O_PAL_NTSC

// GPIO_SEL[8]
#define GPIOSEL_8_HVSYNC_IN (0<<8)      // 0: GPIO
#define GPIOSEL_8_GPIO      (1<<8)      // 1: DSP FL0

// GPIO_SEL[9]
#define GPIOSEL_9_UART_NORMAL   (0<<9)      // 0: UART1/UART2
#define GPIOSEL_9_UART_SWAPPED  (1<<9)      // 1: UART2/UART1

// GPIO_SEL[10]
#define GPIOSEL_A_GPIO20    (0<<10)     // 0: GPIO[20]
#define GPIOSEL_A_FL0       (1<<10)     // 1: DSP FL0

// GPIO_SEL[11]
#define GPIOSEL_B_GPIO21    (0<<11)     // 0: GPIO[21]
#define GPIOSEL_B_FL1       (1<<11)     // 1: DSP FL1

// GPIO_SEL[12]
#define GPIOSEL_C_GPIO59    (0<<12)     // 0: GPIO[59]
#define GPIOSEL_C_FL2       (1<<12)     // 1: DSP FL2

// GPIO_SEL[14:13]
#define GPIOSEL_ED_TVOUT_ALYS   (0<<13)     // 0b00: always output
#define GPIOSEL_ED_TVOUT_TRI    (2<<13)     // 0b10: HZ when GPIOE[2]==1
#define GPIOSEL_ED_TVOUT_TRIN   (3<<13)     // 0b11: HZ when GPIOE[2]==0



//
// GPIO_SEL_AUX
//

// GPIO_SEL_AUX[0]
#define GPIOAUX_0_ROMADDR21 (0<<0)      // 0: ROM_ADDR[21] (default)
#define GPIOAUX_0_GPIO0     (1<<0)      // 1: GPIO[0]

// GPIO_SEL_AUX[1]
#define GPIOAUX_1_ROMADDR20 (0<<1)      // 0: ROM_ADDR[20] (default)
#define GPIOAUX_1_GPIO1     (1<<1)      // 1: GPIO[1]

// GPIO_SEL_AUX[2]
#define GPIOAUX_2_MEMWEB    (0<<2)      // 0: MEMWE_B (default)
#define GPIOAUX_2_GPIO2     (1<<2)      // 1: GPIO[2]

// GPIO_SEL_AUX[3]
#define GPIOAUX_3_MEMOEB    (0<<3)      // 0: MEMOE_B (default)
#define GPIOAUX_3_GPIO12    (1<<3)      // 1: GPIO[12]

// GPIO_SEL_AUX[6:4]
#define GPIOAUX_64_MEMCS3_CSX   (1<<4)      // 000: normal
#define GPIOAUX_64_MEMCS3_CS1   (0<<4)      // 001: direct CS3 to CS1 (for CS1 programming)
#define GPIOAUX_64_MEMCS3_CS2   (2<<4)      // 010: direct CS3 to CS2 (for CS2 programming)
#define GPIOAUX_64_MEMCS3_CS3   (3<<4)      // 011: direct CS3 to CS2 (for CS3 programming)
#define GPIOAUX_64_MEMCS3_GPIO  (4<<4)      // 100: GPIO[15:13]

// GPIO_SEL_AUX[7]
#define GPIOAUX_7_ROMADDR22 (0<<7)      // 0: ROM_ADDR[22]
#define GPIOAUX_7_GPIO16    (1<<7)      // 1: GPIO[16]

// GPIO_SEL_AUX[8]
#define GPIOAUX_8_ROMADDR23 (0<<8)      // 0: ROM_ADDR[23]
#define GPIOAUX_8_GPIO17    (1<<8)      // 1: GPIO[17]

// GPIO_SEL_AUX[9]
#define GPIOAUX_9_ROMADDR24 (0<<9)      // 0: ROM_ADDR[24]
#define GPIOAUX_9_GPIO18    (1<<9)      // 1: GPIO[18]

// GPIO_SEL_AUX[10]
#define GPIOAUX_A_ROMADDR25 (0<<10)     // 0: ROM_ADDR[25]
#define GPIOAUX_A_GPIO19    (1<<10)     // 1: GPIO[19]


// aux: 10
// sel: 00
#define GPIO_SEL_DEFAULT    ( GPIOSEL_10_EPP    \
                | GPIOSEL_52_ATAPI  \
                | GPIOSEL_6_GPIO    \
                | GPIOSEL_7_GPIO    \
                | GPIOSEL_8_HVSYNC_IN   \
                | GPIOSEL_9_UART_NORMAL \
                | GPIOSEL_A_FL0     \
                | GPIOSEL_B_FL1     \
                | GPIOSEL_C_GPIO59  \
                | GPIOSEL_ED_TVOUT_ALYS \
                )

#define GPIO_SEL_AUX_DEFAULT    ( GPIOAUX_0_GPIO0   \
                | GPIOAUX_1_GPIO1   \
                | GPIOAUX_2_GPIO2   \
                | GPIOAUX_3_MEMOEB  \
                | GPIOAUX_64_MEMCS3_CSX \
                | GPIOAUX_7_ROMADDR22   \
                | GPIOAUX_8_ROMADDR23   \
                | GPIOAUX_9_ROMADDR24   \
                | GPIOAUX_A_ROMADDR25   \
                )

*/
//
// generic GPIO operations
// 
#define GPIO_I_GET(a)   ((regs0->gpio_in[a/16] >> (a%16)) & 0x01)
#define GPIO_O_SET(a,d) ((d) ? (regs0->gpio_out[a/16] |= (1<<(a%16))) \
                             : (regs0->gpio_out[a/16] &= ~(1<<(a%16))) )
#define GPIO_E_SET(a,d) ((d) ? (regs0->gpio_oe[a/16] |= (1<<(a%16))) \
                             : (regs0->gpio_oe[a/16] &= ~(1<<(a%16))) )
#define GPIO_M_SET(a,d) ((d) ? (regs0->gpio_master[a/16] |= (1<<(a%16))) \
                             : (regs0->gpio_master[a/16] &= ~(1<<(a%16))) )

#if defined(IC_8202L) //terry,2006/4/7 05:17¤U¤È
    #include "gpio_8202L.h"
#elif defined(IC_8203A)
    #include "gpio_8203A.h"
#elif defined(SPHE8202)
    #if defined(MP_BOARD_216_PIN_NON_SHARE)&&!defined(IC_8202D)&&!defined(IC_8202E)
	#include "gpio_8202s.h"
    #else
	#include "gpio_8202.h"
    #endif
#elif defined(SPHE1000)
	#include "gpio_1000.h"
#else
	#include "gpio_mute_8200.h"
#endif

#if defined(TOP_DOOR_LOADER)||defined(CHECK_PORTABLE_OPCLSW)
	#ifdef USE_2_DOOR_SENSE_GPIO		//gerry,2004-1-10 9:51
    #define GPIO_GET_DOOR_STATUS()          (GPIO_I_GET(DOOR_SENSE_GPIO)|GPIO_I_GET(DOOR_SENSE_GPIO_2))
	#else
    #define GPIO_GET_DOOR_STATUS()          GPIO_I_GET(DOOR_SENSE_GPIO)
    #endif
    #define DOOR_OPEN                       1
#endif //#ifdef TOP_DOOR_LOADER

#ifdef PORTABLE_DVD //Jack for Portable DVD 04/06/03
    #include "gpio_portable.h" //0725 splitted for portable
#endif

#ifdef ALCO_PORTABLE //Jack for Alco Portable 04/09/06
    #include "gpio_alco_portable.h" 
#endif


//GPIO Function
#ifdef SUPPORT_VIDEO_BUFFER_STANDBY
void video_buff_power_off(void);
void video_buff_power_on(void);
#endif
                             
#ifdef SUPPORT_EXTERNAL_MIC                          
void extern_mic_detect_on(void);
int extern_mic_is_detected(void);
void extern_mic_unmute(void);
void extern_mic_mute(void);

#endif
                             
#ifdef GPIO_KEY_LIGHT
void init_keylight_io(void);
	#if defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ)
	void init_hj_keylight_io(void);
	#elif defined(USE_VFDPORT_TO_KEYLIGHT_GBM)
	void init_gbm_keylight_io(void);
	#elif defined(USE_VFDPORT_TO_KEYLIGHT_IDALL)
    void init_idall_keylight_io(void);
    #elif defined(USE_VFDPORT_TO_KEYLIGHT_THAKRAL)
    void init_thakral_keylight_io(void);
	#endif
#endif
                             
#ifdef SUPPORT_Auo_2inch_Digital_panel
void init_auo_digital_panel(void);
#endif


#ifdef SUPPORT_Auo_UPS053_Digital_panel
void init_auo_ups053_digital_panel(void);                               
#endif

#ifdef SUPPORT_Auo_UPS018_Digital_panel
void init_auo_ups018_digital_panel(void); 
#endif
                            
#endif/*__GPIO_H*/

