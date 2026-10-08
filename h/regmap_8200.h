#ifndef __REGMAP_8200_H
#define __REGMAP_8200_H

/*
** FILE
** regmap.h
**
** DESCRIPTION
** define register-file structure.
**
** NOTE:
** specific for sphe8200
*/

#include "types.h"
#include "dmabuf.h"

/*
** TYPE
** RegisterFile
*/
typedef	struct 
{
  // GROUP 0:	Chip Information
  UINT32 stamp;                                 // 00    0      (0000) $bffe8000
  UINT32 emulation;                             // 01    1      (0004)
  UINT32 reset;                                 // 02    2      (0008)
  UINT32 reset2;                                // 03    3      (000c)
  UINT32 pad_ctrl;                              // 04    4      (0010)
  UINT32 sdram_clko_cfg;                        // 05    5      (0014)
  UINT32 sdram_clki_cfg;                        // 06    6      (0018)
  UINT32 sdram_clki_dly_cfg;                    // 07    7      (001c)
  UINT32 clk_mon_sel;                           // 08    8      (0020)
  UINT32 clk_mon_result;                        // 09    9      (0024)
  UINT32 clken0;                                // 0a   10      (0028)
  UINT32 clken1;                                // 0b   11      (002c)
  UINT32 gclken0;                               // 0c   12      (0030)
  UINT32 gclken1;                               // 0d   13      (0034)
  UINT32 sysclk_div_sel;                        // 0e   14      (0038)
  UINT32 sysclk_sel;                            // 0f   15      (003c)
  UINT32 pllv_cfg;                              // 10   16      (0040)
  UINT32 sft_cfg0;                              // 11   17      (0044)
  UINT32 sft_cfg1;                              // 12   18      (0048)
  UINT32 sft_cfg2;                              // 13   19      (004c)
  UINT32 sft_cfg3;                              // 14   20      (0050)
  UINT32 sft_cfg4;                              // 15   21      (0054)
  UINT32 sft_cfg5;                              // 16   22      (0058)
  UINT32 sft_cfg6;                              // 17   23      (005c)
  UINT32 sft_cfg7;                              // 18   24      (0060)
  UINT32 sft_cfg8;                              // 19   25      (0064)
  UINT32 hw_bo;                                 // 1a   26      (0068)
  UINT32 hw_cfg;                                // 1b   27      (006c)
  UINT32 hw_cfg_chg;                            // 1c   28      (0070)
  UINT32 sft_cfg9;                              // 1d   29      (0074)
  UINT32 sft_cfga;                              // 1e   30      (0078)
  UINT32 g0_reserved_1[1];                      // 1f   31~  31 (007c)

  // GROUP 1:	Timers
  UINT32 stc_15_0;                              // 00   32      (0080) $bffe8080
  UINT32 stc_31_16;                             // 01   33      (0084)
  UINT32 stc_32;                                // 02   34      (0088)
  UINT32 stc_divisor;                           // 03   35      (008c)
  UINT32 rtc_15_0;                              // 04   36      (0090)
  UINT32 rtc_31_16;                             // 05   37      (0094)
  UINT32 rtc_divisor;                           // 06   38      (0098)
  UINT32 stc_config;                            // 07   39      (009c)
  UINT32 timer0_ctrl;                           // 08   40      (00a0)
  UINT32 timer0_cnt;                            // 09   41      (00a4)
  UINT32 timer1_ctrl;                           // 0a   42      (00a8)
  UINT32 timer1_cnt;                            // 0b   43      (00ac)
  UINT32 timerw_ctrl;                           // 0c   44      (00b0)
  UINT32 timerw_cnt;                            // 0d   45      (00b4)
  UINT32 g1_unused_1[2];                        // 0e   46~  47 (00b8)
  UINT32 timer2_ctrl;                           // 10   48      (00c0)
  UINT32 timer2_divisor;                        // 11   49      (00c4)
  UINT32 timer2_reload;                         // 12   50      (00c8)
  UINT32 timer2_cnt;                            // 13   51      (00cc)
  UINT32 timer3_ctrl;                           // 14   52      (00d0)
  UINT32 timer3_divisor;                        // 15   53      (00d4)
  UINT32 timer3_reload;                         // 16   54      (00d8)
  UINT32 timer3_cnt;                            // 17   55      (00dc)
  UINT32 stcl_0;                                // 18   56      (00e0)
  UINT32 stcl_1;                                // 19   57      (00e4)
  UINT32 stcl_2;                                // 1a   58      (00e8)
  UINT32 atc_0;                                 // 1b   59      (00ec)
  UINT32 atc_1;                                 // 1c   60      (00f0)
  UINT32 atc_2;                                 // 1d   61      (00f4)
  UINT32 g1_reserved[2];                        // 1e   62~  63 (00f8)

  // GROUP 2:	RISC interface
  UINT32 intr_mask;                             // 00   64      (0100) $bffe8100
  UINT32 intr_flag;                             // 01   65      (0104)
  UINT32 intr_masked_flag;                      // 02   66      (0108)
  UINT32 intr_clear;                            // 03   67      (010c)
  UINT32 intr_polarity;                         // 04   68      (0110)
  UINT32 intr_edge;                             // 05   69      (0114)
  UINT32 intr1_mask;                            // 06   70      (0118)
  UINT32 intr1_flag;                            // 07   71      (011c)
  UINT32 intr1_masked_flag;                     // 08   72      (0120)
  UINT32 intr1_clear;                           // 09   73      (0124)
  UINT32 intr1_polarity;                        // 0a   74      (0128)
  UINT32 intr1_edge;                            // 0b   75      (012c)
  UINT32 lbc_control;                           // 0c   76      (0130)
  UINT32 lbc_watchdog;                          // 0d   77      (0134)
  UINT32 rec_start;                             // 0e   78      (0138)
  UINT32 rec_end;                               // 0f   79      (013c)
  UINT32 rec_l_m;                               // 10   80      (0140)
  UINT32 g2_reserved[13];                       // 11   81~  93 (0144)
  UINT32 ri_misc_b0;                            // 1e   94      (0178)
  UINT32 ri_misc_b1;                            // 1f   95      (017c)

  // GROUP 3:	Video bitstream parameters 
  UINT32 seq_ext;                               // 00   96      (0180) $bffe8180
  UINT32 h_size;                                // 01   97      (0184)
  UINT32 v_size;                                // 02   98      (0188)
  UINT32 g3_unused;                             // 03   99      (018c)
  UINT32 pic_coding_type;                       // 04  100      (0190)
  UINT32 pic_f_code;                            // 05  101      (0194)
  UINT32 pic_coding_ext0;                       // 06  102      (0198)
  UINT32 pic_coding_ext1;                       // 07  103      (019c)
  UINT32 pic_start;                             // 08  104      (01a0)
  UINT32 dis_pic_id;                            // 09  105      (01a4)
  UINT32 dis_seq_tag;                           // 0a  106      (01a8)
  UINT32 g3_reserved[21];                       // 0b  107~ 127 (01ac)

  // GROUP 4:	VLD parameters
  UINT32 vld_ctrl;                              // 00  128      (0200) $bffe8200
  UINT32 vld_status;                            // 01  129      (0204)
  UINT32 vld_decode_time;                       // 02  130      (0208)
  UINT32 g4_unused;                             // 03  131      (020c)
  UINT32 vld_mon0;                              // 04  132      (0210)
  UINT32 vld_mon1;                              // 05  133      (0214)
  UINT32 vld_mon2;                              // 06  134      (0218)
  UINT32 vld_mon3;                              // 07  135      (021c)
  UINT32 jpeg_control;                          // 08  136      (0220)
  UINT32 jpeg_write_addr;                       // 09  137      (0224)
  UINT32 jpeg_write_data;                       // 0a  138      (0228)
  UINT32 jpeg_read_addr;                        // 0b  139      (022c)
  UINT32 jpeg_read_data;                        // 0c  140      (0230)
  UINT32 error_mb_threshold;                    // 0d  141      (0234)
  UINT32 vld_config;                            // 0e  142      (0238)
  UINT32 g4_reserved[17];                       // 0f  143~ 159 (023c)

  // GROUP 5:	MC configuration zero registers
  UINT32 mc_config;                             // 00  160      (0280) $bffe8280
  UINT32 ref0_luma;                             // 01  161      (0284)
  UINT32 ref0_chroma;                           // 02  162      (0288)
  UINT32 ref1_luma;                             // 03  163      (028c)
  UINT32 ref1_chroma;                           // 04  164      (0290)
  UINT32 bidir_luma;                            // 05  165      (0294)
  UINT32 bidir_chroma;                          // 06  166      (0298)
  UINT32 g5_reserved[17];                       // 07  167~ 183 (029c)
  UINT32 mc_spare_0;                            // 18  184      (02e0)
  UINT32 mc_compress;                           // 19  185      (02e4)
  UINT32 mc_pardec_start;                       // 1a  186      (02e8)
  UINT32 mc_pardec_end;                         // 1b  187      (02ec)
  UINT32 mc_mbwidth;                            // 1c  188      (02f0)
  UINT32 mc_pardec_en;                          // 1d  189      (02f4)
  UINT32 mc_spare_6;                            // 1e  190      (02f8)
  UINT32 mc_spare_7;                            // 1f  191      (02fc)

  // GROUP 6:	SDRAM control
  UINT32 sdctrl_cfg0;                           // 00  192      (0300) $bffe8300
  UINT32 sdctrl_cfg1;                           // 01  193      (0304)
  UINT32 sdctrl_cfg2;                           // 02  194      (0308)
  UINT32 sdctrl_mrs;                            // 03  195      (030c)
  UINT32 sdctrl_sref_cfg;                       // 04  196      (0310)
  UINT32 sdctrl_cfg3;                           // 05  197      (0314)
  UINT32 sdctrl_data_mon_st;                    // 06  198      (0318)
  UINT32 sdctrl_data_cyc_l;                     // 07  199      (031c)
  UINT32 sdctrl_data_cyc_h;                     // 08  200      (0320)
  UINT32 sdctrl_data_cnt_l;                     // 09  201      (0324)
  UINT32 sdctrl_data_cnt_h;                     // 0a  202      (0328)
  UINT32 sdctrl_gclk_dis;                       // 0b  203      (032c)
  UINT32 sdctrl_aref1_cfg;                      // 0c  204      (0330)
  UINT32 sdctrl_int;                            // 0d  205      (0334)
  UINT32 sdctrl_int_mask;                       // 0e  206      (0338)
  UINT32 sdctrl_int_status;                     // 0f  207      (033c)
  UINT32 sdctrl_lmem_base;                      // 10  208      (0340)
  UINT32 sdctrl_lmem_row_st;                    // 11  209      (0344)
  UINT32 g6_unused_0;                           // 12  210      (0348)
  UINT32 sdctrl_cfg4;                           // 13  211      (034c)
  UINT32 g6_reserved[10];                       // 14  212~ 221 (0350)
  UINT32 sdctrl_misc_b0;                        // 1e  222      (0378)
  UINT32 sdctrl_misc_b1;                        // 1f  223      (037c)

  // GROUP 7:	VPP Control
  UINT32 dis_x_start;                           // 00  224      (0380) $bffe8380
  UINT32 dis_y_start;                           // 01  225      (0384)
  UINT32 dis_x_size;                            // 02  226      (0388)
  UINT32 dis_y_size;                            // 03  227      (038c)
  UINT32 v_offset;                              // 04  228      (0390)
  UINT32 h_offset;                              // 05  229      (0394)
  UINT32 vpp_bg_y;                              // 06  230      (0398)
  UINT32 vpp_bg_cb_cr;                          // 07  231      (039c)
  UINT32 v_filter0_setup;                       // 08  232      (03a0)
  UINT32 v_filter1_setup;                       // 09  233      (03a4)
  UINT32 h_filter_setup;                        // 0a  234      (03a8)
  UINT32 vpp_config;                            // 0b  235      (03ac)
  UINT32 vpp_config1;                           // 0c  236      (03b0)
  UINT32 ds_field_config;                       // 0d  237      (03b4)
  UINT32 dip_config;                            // 0e  238      (03b8)
  UINT32 dip_param;                             // 0f  239      (03bc)
  UINT32 dip_mv_ptr;                            // 10  240      (03c0)
  UINT32 vppref0_luma;                          // 11  241      (03c4)
  UINT32 vppref0_chroma;                        // 12  242      (03c8)
  UINT32 vppref1_luma;                          // 13  243      (03cc)
  UINT32 vppref1_chroma;                        // 14  244      (03d0)
  UINT32 vppbidir_luma;                         // 15  245      (03d4)
  UINT32 vppbidir_chroma;                       // 16  246      (03d8)
  UINT32 dip_ref_base;                          // 17  247      (03dc)
  UINT32 dip_param_threshold;                   // 18  248      (03e0)
  UINT32 dip_param_fading;                      // 19  249      (03e4)
  UINT32 vpp_act_region_top;                    // 1a  250      (03e8)
  UINT32 vpp_act_region_bottom;                 // 1b  251      (03ec)
  UINT32 vpp_spare_0;                           // 1c  252      (03f0)
  UINT32 vpp_clut_ay;                           // 1d  253      (03f4)
  UINT32 vpp_clut_uv;                           // 1e  254      (03f8)
  UINT32 vpp_spare_1;                           // 1f  255      (03fc)

  // GROUP 8:	TV0
  UINT32 tv_mode[6];                            // 00  256~ 261 (0400) $bffe8400
  UINT32 tv_subc_f[2];                          // 06  262~ 263 (0418)
  UINT32 tv_subc_p;                             // 08  264      (0420)
  UINT32 tv_line_t[2];                          // 09  265~ 266 (0424)
  UINT32 tv_line_b[2];                          // 0b  267~ 268 (042c)
  UINT32 tv_cc_t;                               // 0d  269      (0434)
  UINT32 tv_cc_b;                               // 0e  270      (0438)
  UINT32 tv_cgms[2];                            // 0f  271~ 272 (043c)
  UINT32 tv_id_status;                          // 11  273      (0444)
  UINT32 tv_dac[2];                             // 12  274~ 275 (0448)
  UINT32 tv_misc[12];                           // 14  276~ 287 (0450)

  // GROUP 9:	DSP24
  UINT32 dsp24_control;                         // 00  288      (0480) $bffe8480
  UINT32 dsp3dbg_mode;                          // 01  289      (0484)
  UINT32 dsp3dbg_break;                         // 02  290      (0488)
  UINT32 dsp3dbg_addr;                          // 03  291      (048c)
  UINT32 dsp3dbg_step;                          // 04  292      (0490)
  UINT32 dsp3dbg_rd_l;                          // 05  293      (0494)
  UINT32 dsp3dbg_rd_h;                          // 06  294      (0498)
  UINT32 dsp3dbg_wr_l;                          // 07  295      (049c)
  UINT32 dsp3dbg_wr_h;                          // 08  296      (04a0)
  UINT32 dsp3dbg_pc;                            // 09  297      (04a4)
  UINT32 rom_l;                                 // 0a  298      (04a8)
  UINT32 rom_h;                                 // 0b  299      (04ac)
  UINT32 dsp24ya;                               // 0c  300      (04b0)
  UINT32 pcmya;                                 // 0d  301      (04b4)
  UINT32 audya;                                 // 0e  302      (04b8)
  UINT32 g9_reserved;                           // 0f  303      (04bc)
  UINT32 dsp24_port[16];                        // 10  304~ 319 (04c0)

  // GROUP 10:	OSD control 
  UINT32 osd_tv_std;                            // 00  320      (0500) $bffe8500
  UINT32 osd_tv_out;                            // 01  321      (0504)
  UINT32 osd_mixer;                             // 02  322      (0508)
  UINT32 osd_display_status;                    // 03  323      (050c)
  UINT32 osd_en;                                // 04  324      (0510)
  UINT32 osd_tlink_addr;                        // 05  325      (0514)
  UINT32 osd_blink_addr;                        // 06  326      (0518)
  UINT32 y_clip;                                // 07  327      (051c)
  UINT32 cb_clip;                               // 08  328      (0520)
  UINT32 osd_base_addr;                         // 09  329      (0524)
  UINT32 osd_mode[12];                          // 0a  330~ 341 (0528)
  
  UINT32 g10_reserved[10];                      // 16  342~ 351 (0558)

  // GROUP 11:	Graphic control
  UINT32 graph_mode;                            // 00  352      (0580) $bffe8580
  UINT32 graph_status;                          // 01  353      (0584)
  UINT32 dma_mode;                              // 02  354      (0588)
  UINT32 dma_xaddr;                             // 03  355      (058c)
  UINT32 dma_yaddr;                             // 04  356      (0590)
  UINT32 dma_done;                              // 05  357      (0594)
  UINT32 g11_reserved[26];                      // 06  358~ 383 (0598)

  // GROUP 12:	HOST
  UINT32 g12_dvddsp_vy;                         // 00  384      (0600) $bffe8600
  UINT32 g12_dvddsp_vx;                         // 01  385      (0604)
  UINT32 dvddsp_function;                       // 02  386      (0608)
  UINT32 dvddsp_ata_config;                     // 03  387      (060c)
  UINT32 dvddsp_blocksize;                      // 04  388      (0610)
  UINT32 dvddsp_blocklength;                    // 05  389      (0614)
  UINT32 g12_dvddsp_ry;                         // 06  390      (0618)
  UINT32 dvddsp_rx;                             // 07  391      (061c)
  UINT32 dvddsp_public;                         // 08  392      (0620)
  UINT32 dvddsp_ude_config;                     // 09  393      (0624)
  UINT32 dvddsp_ata_pio_cycle;                  // 0a  394      (0628)
  UINT32 dvddsp_ata_udma_cycle;                 // 0b  395      (062c)
  UINT32 g12_reserved[4];                       // 0c  396~ 399 (0630)
  UINT32 dvddsp_mon[4];                         // 10  400~ 403 (0640)
  UINT32 g12_reserved1[12];                     // 14  404~ 415 (0650)

  // GROUP 13:	CSS
  UINT32 css_tk0;                               // 00  416      (0680) $bffe8680
  UINT32 css_tk1;                               // 01  417      (0684)
  UINT32 css_tk2;                               // 02  418      (0688)
  UINT32 css_tk3;                               // 03  419      (068c)
  UINT32 css_tbyte;                             // 04  420      (0690)
  UINT32 css_public;                            // 05  421      (0694)
  UINT32 css_config;                            // 06  422      (0698)
  UINT32 css_l0;                                // 07  423      (069c)
  UINT32 css_l1;                                // 08  424      (06a0)
  UINT32 css_r0;                                // 09  425      (06a4)
  UINT32 css_r1;                                // 0a  426      (06a8)
  UINT32 cppm_aukey3;                           // 0b  427      (06ac)
  UINT32 cppm_aukey2;                           // 0c  428      (06b0)
  UINT32 cppm_aukey1;                           // 0d  429      (06b4)
  UINT32 cppm_aukey0;                           // 0e  430      (06b8)
  UINT32 g13_reserved[17];                      // 0f  431~ 447 (06bc)

  // GROUP 14:  IOP
  UINT32 iop_control;                           // 00  448      (0700) $bffe8700
  UINT32 iop_status;                            // 01  449      (0704)
  UINT32 iop_bp;                                // 02  450      (0708)
  UINT32 iop_regsel;                            // 03  451      (070c)
  UINT32 iop_regout;                            // 04  452      (0710)
  UINT32 iop_memlimit;                          // 05  453      (0714)
  UINT32 g14_reserved[2];                       // 06  454~ 455 (0718)
  UINT32 iop_data[8];                           // 08  456~ 463 (0720)
  UINT32 g14_reserved1[16];                     // 10  464~ 479 (0740)

  // GROUP 15:  SUP
  UINT32 sup_fst_cmd_addr;                      // 00  480      (0780) $bffe8780
  UINT32 sup_snd_cmd_addr;                      // 01  481      (0784)
  UINT32 sup_h_size;                            // 02  482      (0788)
  UINT32 sup_mode;                              // 03  483      (078c)
  UINT32 sup_tv_mode;                           // 04  484      (0790)
  UINT32 sup_panning;                           // 05  485      (0794)
  UINT32 sup_aspect_ratio;                      // 06  486      (0798)
  UINT32 sup_mon[5];                            // 07  487~ 491 (079c)
  UINT32 sup_config;                            // 0c  492      (07b0)
  UINT32 sup_buffer_limit;                      // 0d  493      (07b4)
  UINT32 g15_reserved[18];                      // 0e  494~ 511 (07b8)

  // GROUP 16
  UINT32 g16_reserved[32];                      // 00  512~ 543 (0800) $bffe8800

  // GROUP 17
  UINT32 g17_reserved[32];                      // 00  544~ 575 (0880) $bffe8880

  // GROUP 18:  UARTs
  // UART0
  UINT32 uart0_data;                            // 00  576      (0900) $bffe8900
  UINT32 uart0_lsr;                             // 01  577      (0904)
  UINT32 uart0_msr;                             // 02  578      (0908)
  UINT32 uart0_lcr;                             // 03  579      (090c)
  UINT32 uart0_mcr;                             // 04  580      (0910)
  UINT32 uart0_div_l;                           // 05  581      (0914)
  UINT32 uart0_div_h;                           // 06  582      (0918)
  UINT32 uart0_isc;                             // 07  583      (091c)
  // UART1
  UINT32 uart1_data;                            // 08  584      (0920)
  UINT32 uart1_lsr;                             // 09  585      (0924)
  UINT32 uart1_msr;                             // 0a  586      (0928)
  UINT32 uart1_lcr;                             // 0b  587      (092c)
  UINT32 uart1_mcr;                             // 0c  588      (0930)
  UINT32 uart1_div_l;                           // 0d  589      (0934)
  UINT32 uart1_div_h;                           // 0e  590      (0938)
  UINT32 uart1_isc;                             // 0f  591      (093c)
  UINT32 g18_reserved[16];                      // 10  592~ 607 (0940)

  // GROUP 19:  GPIO control
  UINT32 gpio_master[4];                        // 00  608~ 611 (0980) $bffe8980
  UINT32 gpio_oe[4];                            // 04  612~ 615 (0990)
  UINT32 gpio_out[4];                           // 08  616~ 619 (09a0)
  UINT32 gpio_in[4];                            // 0c  620~ 623 (09b0)
  UINT32 gpio2_inout[2];                        // 10  624~ 625 (09c0)
  UINT32 gpio2_oe[2];                           // 12  626~ 627 (09c8)
  UINT32 g19_reserved1[12];                     // 14  628~ 639 (09d0)

  // GROUP 20:  CDDSP
  UINT32 cddsp_config;                          // 00  640      (0a00) $bffe8a00
  UINT32 cddsp_control;                         // 01  641      (0a04)
  UINT32 cddsp_mm_bcd;                          // 02  642      (0a08)
  UINT32 cddsp_ss_bcd;                          // 03  643      (0a0c)
  UINT32 cddsp_ff_bcd;                          // 04  644      (0a10)
  UINT32 cddsp_status;                          // 05  645      (0a14)
  UINT32 cddsp_mmss;                            // 06  646      (0a18)
  UINT32 cddsp_ffmm;                            // 07  647      (0a1c)
  UINT32 g20_reserved[24];                      // 08  648~ 671 (0a20)

  // GROUP 21:  TV1
  UINT32 tv_gamma[5];                           // 00  672~ 676 (0a80) $bffe8a80
  UINT32 tv_pccon[18];                          // 05  677~ 694 (0a94)
  UINT32 g21_reserved[9];                       // 17  695~ 703 (0adc)

  // GROUP 22:  MBUS 
  UINT32 mbus_bridge_config;                    // 00  704      (0b00) $bffe8b00
  UINT32 evbya;                                 // 01  705      (0b04)
  UINT32 osdya;                                 // 02  706      (0b08)
  UINT32 cdwya;                                 // 03  707      (0b0c)
  UINT32 cdrya;                                 // 04  708      (0b10)
  UINT32 supya;                                 // 05  709      (0b14)

  UINT32 evbya_limit;                           // 06  710      (0b18)
  UINT32 osdya_limit;                           // 07  711      (0b1c)
  UINT32 cdwya_limit;                           // 08  712      (0b20)
  UINT32 cdrya_limit;                           // 09  713      (0b24)
  UINT32 supya_limit;                           // 0a  714      (0b28)

  UINT32 bs_ystop;                              // 0b  715      (0b2c)
  UINT32 bs_ry;                                 // 0c  716      (0b30)
  UINT32 bs_yinit;                              // 0d  717      (0b34)
  UINT32 bs_xinit;                              // 0e  718      (0b38)
  UINT32 dvddsp_vy;                             // 0f  719      (0b3c)
  UINT32 dvddsp_vx;                             // 10  720      (0b40)
  UINT32 dvddsp_ry;                             // 11  721      (0b44)

  UINT32 cdr_vy;                                // 12  722      (0b48)
  UINT32 cdr_vx;                                // 13  723      (0b4c)
  UINT32 supya2;                                // 14  724      (0b50)
  UINT32 supya2_limit;                          // 15  725      (0b54)

  UINT32 iopya;                                 // 16  726      (0b58)
  UINT32 cdrya_xlimit;                          // 17  727      (0b5c)
  UINT32 mvcya;
  UINT32 g22_reserved[7];                       // 18  728~ 735 (0b60)

  // GROUP 23: VPP2
  UINT32 g23_vpp_contrast_adj[2];               // 00  736~ 737 (0b80) $bffe8b80
  UINT32 g23_vpp_contrast_slope[3];             // 02  738~ 740 (0b88)
  UINT32 g23_vpp_histogram[8];                  // 05  741~ 748 (0b94)
  UINT32 g23_vpp_chksum;                        // 0d  749      (0bb4)
  UINT32 g23_vpp_mv_ptr;                        // 0e  750      (0bb8)
  UINT32 g23_vpp_hue_adj[2];                    // 0f  751~ 752 (0bbc)
  UINT32 g23_reserved[15];                      // 11  753~ 767 (0bc4)

  // GROUP 24: Buffer Control
  UINT32 bufctl[8];                             // 00  768~ 775 (0c00) $bffe8c00
  UINT32 g24_reserved[24];                      // 08  776~ 799 (0c20)

  // GROUP 25: INVQ
  UINT32 invq_qmx_par;                          // 00  800      (0c80) $bffe8c80
  UINT32 invq_mode;                             // 01  801      (0c84)
  UINT32 invq_chksum;                           // 02  802      (0c88)
  UINT32 g25_reserved[29];                      // 03  803~ 831 (0c8c)

  // GROUP 26: RI/ROM
  UINT32 rom_config;                            // 00  832      (0d00) $bffe8d00
  UINT32 wait_cyc1_0;                           // 01  833      (0d04)
  UINT32 wait_cyc3_2;                           // 02  834      (0d08)
  UINT32 oe_wait_cyc1_0;                        // 03  835      (0d0c)
  UINT32 oe_wait_cyc3_2;                        // 04  836      (0d10)
  UINT32 we_wait_cyc1_0;                        // 05  837      (0d14)
  UINT32 we_wait_cyc3_2;                        // 06  838      (0d18)
  UINT32 iochrdy_wait_cyc;                      // 07  839      (0d1c)
  UINT32 rom1_base;                             // 08  840      (0d20)
  UINT32 rom2_base;                             // 09  841      (0d24)
  UINT32 rom3_base;                             // 0a  842      (0d28)
  UINT32 pcmcia_iorw_wait;                      // 0b  843      (0d2c)
  UINT32 pcmcia_ctrl;                           // 0c  844      (0d30)
  UINT32 g26_reserved1[8];                      // 0d  845~ 852 (0d34)
  UINT32 adt[4];                                // 15  853~ 856 (0d54)
  UINT32 dat[4];                                // 19  857~ 860 (0d64)
  UINT32 adm[2];                                // 1d  861~ 862 (0d74)
  UINT32 dar;                                   // 1f  863      (0d7c)

  // GROUP 27: System Bus Arbitrator
  UINT32 sbar_config;                           // 00  864      (0d80) $bffe8d80
  UINT32 sbar_prr[16];                          // 01  865~ 880 (0d84)
  UINT32 g27_reserved[15];                      // 11  881~ 895 (0dc4)

  // GROUP 28: Bridge
  UINT32 rf_sdramif_tbya;                       // 00  896      (0e00) $bffe8e00
  UINT32 rf_servo_band_en;                      // 01  897      (0e04)
  UINT32 rf_servo_band_val;                     // 02  898      (0e08)
  UINT32 g28_reserved[29];                      // 03  899~ 927 (0e0c)

  // GROUP 29: Servo
  UINT32 rf_regif_addr;                         // 00  928      (0e80) $bffe8e80
  UINT32 rf_regif_wdata;                        // 01  929      (0e84)
  UINT32 rf_regif_rdata;                        // 02  930      (0e88)
  UINT32 rf_regif_sample_ctrl;                  // 03  931      (0e8c)
  UINT32 rf_regif_intr_addr;                    // 04  932      (0e90)
  UINT32 rf_regif_intr_wdata;                   // 05  933      (0e94)
  UINT32 rf_regif_intr_rdata;                   // 06  934      (0e98)
  UINT32 g29_reserved[25];                      // 07  935~ 959 (0e9c)

  // GROUP 30: Emulation control
  UINT32 emu_cfg[32];                           // 00  960~ 991 (0f00) $bffe8f00
  
  // GROUP 31: Audio hardware control
  UINT32 aud_reset;                             // 00  992      (0f80) $bffe8f80
  UINT32 aud_pcm_cfg;                           // 01  993      (0f84)
  UINT32 aud_spdif_cfg;                         // 02  994      (0f88)
  UINT32 aud_enable;                            // 03  995      (0f8c)
  UINT32 aud_adc_stereo_cfg;                    // 04  996      (0f90)
  UINT32 aud_adc_mono_cfg;                      // 05  997      (0f94)
  UINT32 aud_pcm_ramp_delta;                    // 06  998      (0f98)
  UINT32 aud_pcm_ramp_cfg;                      // 07  999      (0f9c)
  UINT32 aud_pcm_ramp_value;                    // 08 1000      (0fa0)
  UINT32 aud_spdif_period;                      // 09 1001      (0fa4)
  UINT32 aud_fifo_flag;                         // 0a 1002      (0fa8)
  UINT32 aud_chn_pcm_cnt[10];                   // 0b 1003~1012 (0fac)
  UINT32 aud_xck_cfg;                           // 15 1013      (0fd4)
  UINT32 aud_pcm_bck_cfg;                       // 16 1014      (0fd8)
  UINT32 aud_iec_bclk_cfg;                      // 17 1015      (0fdc)
  UINT32 aud_adc_mclk_cfg;                      // 18 1016      (0fe0)
  UINT32 aud_dsp_run_cnt;                       // 19 1017      (0fe4)
  UINT32 aud_dsp_stall_cnt;                     // 1a 1018      (0fe8)
  UINT32 aud_dsp_reset_flag;                    // 1b 1019      (0fec)
  UINT32 aud_dsp_dec_cnt_toggle;                // 1c 1020      (0ff0)
  UINT32 aud_dsp_dec_cnt;                       // 1d 1021      (0ff4)
  UINT32 aud_fpga_v2[2];                        // 1e 1022~1023 (0ff8)
  
  // GROUP 32
  UINT32 g32_reserved[32];                      // 00 1024~1055 (1000) $bffe9000
  
  // GROUP 33
  UINT32 g33_reserved[32];                      // 00 1056~1087 (1080) $bffe9080
  
  // GROUP 34
  UINT32 g34_reserved[32];                      // 00 1088~1119 (1100) $bffe9100
  
  // GROUP 35
  UINT32 g35_reserved[32];                      // 00 1120~1151 (1180) $bffe9180
  
  // GROUP 36
  UINT32 g36_reserved[32];                      // 00 1152~1183 (1200) $bffe9200
  
  // GROUP 37
  UINT32 g37_reserved[32];                      // 00 1184~1215 (1280) $bffe9280

  // GROUP 38
  UINT32 g38_reserved[32];                      // 00 1216~1247 (1300) $bffe9300

  // GROUP 39
  UINT32 g39_reserved[32];                      // 00 1248~1279 (1380) $bffe9380
  
  // GROUP 40: (EMU) SDRAM 6B
  UINT32 sdc_req_t_reset;                       // 00 1280      (1400) $bffe9400
  UINT32 sdc_req_time[14][2];                   // 01 1281~1308
  UINT32 g40_reserved[3];                       // 1d 1309~1311 (1474)

  // GROUP 41: (EMU) SDRAM 6A
  UINT32 sdc_data_cnt[14][2];                   // 00 1312~1339 (0520) $bffe9480
  UINT32 sdc_n_req_cnt[2];                      // 1c 1340~1341 (14f0)
  UINT32 sdc_cke_cnt[2];                        // 1e 1342~1343 (14f8)

  // GROUP 42~49
  UINT32 g42_reserved[32];                      // 00 1344~1375 (1500) $bffe9500
  UINT32 g43_reserved[32];                      // 00 1376~1407 (1580) $bffe9580
  UINT32 g44_reserved[32];                      // 00 1408~1439 (1600) $bffe9600
  UINT32 g45_reserved[32];                      // 00 1440~1471 (1680) $bffe9680
  UINT32 g46_reserved[32];                      // 00 1472~1503 (1700) $bffe9700
  UINT32 g47_reserved[32];                      // 00 1504~1535 (1780) $bffe9780
  UINT32 g48_reserved[32];                      // 00 1536~1567 (1800) $bffe9800
  UINT32 g49_reserved[32];                      // 00 1568~1599 (1880) $bffe9880

  // GROUP 50
  UINT32 g50_reserved[29];                      // 00 1600~1628 (1900) $bffe9900
  UINT32 risc_fpga_version[3];                  // 1d 1629~1631 (1974)

  // GROUP 51
  UINT32 g51_reserved[29];                      // 00 1632~1660 (1980) $bffe9980
  UINT32 block_fpga_version[3];                 // 1d 1661~1663 (19f4)

  // GROUP 52
  UINT32 g52_reserved[29];                      // 00 1664~1692 (1a00) $bffe9a00
  UINT32 aud_fpga_version[3];                   // 1d 1693~1695 (1a74)

  // GROUP 53~63
  UINT32 g53_reserved[32];                      // 00 1696~1727 (1a80) $bffe9a80
  UINT32 g54_reserved[32];                      // 00 1728~1759 (1b00) $bffe9b00
  UINT32 g55_reserved[32];                      // 00 1760~1791 (1b80) $bffe9b80
  UINT32 g56_reserved[32];                      // 00 1792~1823 (1c00) $bffe9c00
  UINT32 g57_reserved[32];                      // 00 1824~1855 (1c80) $bffe9c80
  UINT32 g58_reserved[32];                      // 00 1856~1887 (1d00) $bffe9d00
  UINT32 g59_reserved[32];                      // 00 1888~1919 (1d80) $bffe9d80
  UINT32 g60_reserved[32];                      // 00 1920~1951 (1e00) $bffe9e00
  UINT32 g61_reserved[32];                      // 00 1952~1983 (1e80) $bffe9e80
  UINT32 g62_reserved[32];                      // 00 1984~2015 (1f00) $bffe9f00
  UINT32 g63_reserved[32];                      // 00 2016~2047 (1f80) $bffe9f80

  // GROUP 64~255
  UINT32 gxx_reserved[192][32];                 // 00 2048~8191 (0800) $bffea000

  // GROUP
  WorkBuf	reg_dma_buf;
  WorkBuf	reg_dma_buf256;
  WorkBuf	reg_dma_buf512;
  WorkBuf	reg_dma_buf768;

  //
  // (OLD hardware, just for compatible issue)
  //
//  UINT32 evbya2;                                // 00 8192      (8000) $bfff0000
//  UINT32 eabya;                                 // 01 8193      (8004)
//  UINT32 dsp16ya;                               // 02 8194      (8008)
//  UINT32 dma_addrmode;                          // 03 8195      (800c)
//  UINT32 dma_addrlen;                           // 04 8196      (8010)
//  UINT32 epp_status;                            // 05 8197      (8014)
//  UINT32 epp_data;                              // 06 8198      (8018)
//  UINT32 agdc_config;                           // 07 8199      (801c)
//  UINT32 video_compress;                        // 08 8200      (8020)
//  UINT32 dis_tv_out;                            // 09 8201      (8024)
//  UINT32 audio_clkgen;                          // 05    5      (0014)
  
} RegisterFile;


/*
** 	Video
*/
#define RF_CODING_EXT0_PROGRESSIVE_FRAME	(1<<0)
#define RF_CODING_EXT0_CHROMA_420_TYPE		(1<<1)
#define RF_CODING_EXT0_REPEAT_FIRST_FIELD	(1<<2)
#define RF_CODING_EXT0_ALTERNATE_SCAN		(1<<3)
#define RF_CODING_EXT0_INTRA_VLC_FORMAT		(1<<4)
#define RF_CODING_EXT0_Q_SCALE_TYPE		(1<<5)
#define RF_CODING_EXT0_CONCEAL_MOTION_VECTORS	(1<<6)
#define RF_CODING_EXT0_FRAME_PRED_FRAME_DCT	(1<<7)
#define RF_CODING_EXT0_TOP_FIELD_FIRST		(1<<8)
#define RF_CODING_EXT0_PICTURE_STRUCTURE	(0x03<<9)
#define RF_CODING_EXT0_INTRA_DC_PRECISION	(0x03<<11)
//#define RF_CODING_EXT0_LAST_PICTURE		(1<<14)
#define RF_CODING_EXT0_BACK_LAST		(1<<14)
#define RF_CODING_EXT0_SECOND_FIELD		(1<<15)

#define	ext0_pic_struct(x)	(((x)>>9)&0x03)

/*
**	Display Output Tweaking
*/
#define	RF_VOUT_SWAP_CBCR		(1<<1)
#define	RF_VOUT_SWAP_LC			(1<<2)

/*
** 	Display Status
*/
#define RF_Display_OSDRegion		0x00ff
#define	RF_Display_FieldNo		0x8000
#define	RF_Display_VSyncB		0x4000
#define	RF_Display_HSyncB		0x2000
#define	RF_Display_FieldEnd		0x1000

#define	DISPLAY_STATUS                  regs0->osd_display_status
#define	IsVSync()                       ((DISPLAY_STATUS & RF_Display_VSyncB)==0)
#define	IsHSync()                       ((DISPLAY_STATUS & RF_Display_HSyncB)==0)
#define	IsTopField()                    ((DISPLAY_STATUS & RF_Display_FieldNo)==0)
#define	IsBottomField()                 ((DISPLAY_STATUS & RF_Display_FieldNo))
#define	IsFieldEnd()                    ((DISPLAY_STATUS & RF_Display_FieldEnd))

#define	RF_Video_VPicEnd		0x0001
#define	RF_Video_VTblErr		0x0002
#define	RF_Video_VRunErr		0x0004
#define	RF_Video_VSliceErr		0x0008
#define	RF_Video_VErr			0x8000

/*
**	RISC Picture Start
*/
#define IsRPicStart			(regs0->pic_start)

/*
**	VLD Decoding Status
*/
#define	VLD_STATUS                      (regs0->vld_status)
#define	IsVPicEnd                       (VLD_STATUS & RF_Video_VPicEnd)
#define	IsVRunErr                       (VLD_STATUS & RF_Video_VRunErr)
#define	IsVTblErr                       (VLD_STATUS & RF_Video_VTblErr)
#define	IsVErr                          (VLD_STATUS & RF_Video_VErr)

#define	RF_CODING_EXT1_FORWARD_REF0	(0<<1)
#define	RF_CODING_EXT1_FORWARD_REF1	(1<<1)

#define	RF_CODING_EXT1_RECONST_REF0	(0<<2)
#define	RF_CODING_EXT1_RECONST_REF1	(1<<2)
#define	RF_CODING_EXT1_RECONST_B	(2<<2)

#define	RF_CODING_EXT1_FIELDID		(1<<4)


//
//	TIMER	TIMER	TIMER	TIMER	TIMER	TIMER	TIMER
//
#define	RF_TIMER_SRC_SYSCLK		(0<<14)
#define	RF_TIMER_SRC_STC		(1<<14)
#define	RF_TIMER_SRC_RTC		(2<<14)
#define	RF_TIMER_SRC_TIMER		(3<<14)
#define	RF_TIMER_RUN_ON			(1<<13)
#define	RF_TIMER_RUN_OFF		(0<<13)
#define	RF_TIMER_GO_ON			(1<<11)
#define	RF_TIMER_GO_OFF			(0<<11)
#define	RF_TIMER_MASK			(0x3ff)

#define	TIMER_CONFIG_STOP		( RF_TIMER_GO_OFF )
#define	TIMER_CONFIG_STC		( RF_TIMER_SRC_STC	\
					| RF_TIMER_RUN_ON	\
					| RF_TIMER_GO_ON)

#define	TIMER_CONFIG_10ms		( TIMER_CONFIG_STC | (900-1))
#define	TIMER_CONFIG_4ms		( TIMER_CONFIG_STC | (360-1))
#define	TIMER_CONFIG_1ms		( TIMER_CONFIG_STC | (90-1))

#define	TIMER_CONFIG_dly		( RF_TIMER_SRC_STC	\
    					| RF_TIMER_RUN_OFF	\
					| RF_TIMER_GO_ON)

#define	TIMER_CONFIG_dlys(n)		( TIMER_CONFIG_dly | (n-1))
#define	TIMER_CONFIG_90k(n)		( TIMER_CONFIG_STC | (n-1))


/*
**	VPP	VPP	VPP	VPP	VPP	VPP	VPP
*/
#define RF_HFACTOR_HEXP_ENABLE		(1<<8)
#define RF_HFACTOR_CIF_ENABLE		(1<<9)


/*
** 	CDDSP Control/Status
*/
#define	RF_CDDSP_RESET			0x0001
#define	RF_CDDSP_STOP			0x0002
#define	RF_CDDSP_PAUSE			0x0004
#define	RF_CDDSP_SEEK			0x0008

#define	RF_CDDSP_CRC_ERROR		0x0001
#define	RF_CDDSP_CRC_ERROR_LAST		0x0002
#define	RF_CDDSP_CRC_ERROR_MASK		0x0003

/*
**
*/
#define	RF_DSP24_RESET			(1<<0)
#define	RF_DSP24_STALL			(1<<1)

/*
** EPP status
*/
#define	RF_EPP_IN_FULL			(1<<3)
#define	RF_EPP_IN_EMPTY			(1<<2)
#define	RF_EPP_OUT_FULL			(1<<1)
#define	RF_EPP_OUT_EMPTY		(1<<0)

#define RF_Video_MPEG2_flag		0x08


/*
**	AGDC config
*/
#define	RF_AGDC_BPIC_LOC_RIGHT	(0 << 0)
#define	RF_AGDC_BPIC_LOC_BOTTOM	(1 << 0)
#define	RF_AGDC_BPIC_SIZE_LINE	(0 << 2)
#define	RF_AGDC_BPIC_SIZE_FIELD	(1 << 2)
#define	RF_AGDC_BPIC_SIZE_FULL	(2 << 2)
#define RF_AGDC_SDRAM_64MB	(0 << 6)
#define RF_AGDC_SDRAM_16MB	(1 << 6)

#define	set_dis_tv_std(n)	(regs0->osd_tv_std=(n))


/*
**	VIDEO	VIDEO	VIDEO	VIDEO	VIDEO	VIDEO	VIDEO	VIDEO
*/
#define	RF_COMPRESS_888		(0 << 0)
#define	RF_COMPRESS_866		(1 << 0)
#define	RF_COMPRESS_666		(2 << 0)
#define	RF_COMPRESS_8655	(3 << 0)
#define	RF_COMPRESS_DITHER_ON	(1 << 7)
#define	RF_COMPRESS_DITHER_OFF	(0 << 7)
#define	RF_COMPRESS_CHROMA_FULL	(0 << 8)
#define	RF_COMPRESS_CHROMA_HALF	(1 << 8)

/*
** regs0: register file pointer
*/
#ifdef  GLOBAL_REGISTER
register volatile       RegisterFile    *regs0  asm ("22"); 
#define InitRegFile()   (regs0 = (volatile RegisterFile *)RGST_OFFSET)
#else
#define regs0           ((volatile RegisterFile *)RGST_OFFSET)
#define InitRegFile()   {}
#endif

/*
** buffer position and size
*/
extern	UINT16	dsp24ya, audya, pcmya;
//subpicture buffer
#define	MEM_SUPYA	(regs0->supya)
#define	SBV_YS		MEM_SUPYA
#define	SBV_H		(regs0->supya_limit)
#define	SBV_YE		(SBV_YS + SBV_H)

//elementary video bitstream buffer
#define	MEM_EVBYA	(regs0->evbya)
#define MEM_EVBYA_LIMIT	(regs0->evbya_limit)
#define	VBV_YS		MEM_EVBYA
#define	VBV_H		(MEM_EVBYA_LIMIT)
#define	VBV_YE		(VBV_YS + VBV_H)

//IOP code position
#define	MEM_IOPYA	(regs0->iopya)
//#define	IOP_YE		(MEM_PCMYA) //kevinmonkey 060530 not always correct, depends on memmap...shouldn't use

//DSP stuff
#define	MEM_DSP24YA	dsp24ya
#define	DSP24_YS	MEM_DSP24YA
//#define	DSP24_YE	(MEM_DSP16YA)//kevinmonkey 060530 not always correct, depends on memmap...shouldn't use

#define	MEM_AUDYA	audya
#define AWV_YS 		MEM_AUDYA

#define	MEM_PCMYA	pcmya
#define	PCM_YS		MEM_PCMYA
//#define PCM_YE 		(MEM_AUDYA)//kevinmonkey 060530 not always correct, depends on memmap...shouldn't use

//host DMA buffer
#define	MEM_CDYA	(regs0->cdwya)
#define	CBV_YS		MEM_CDYA
#define	CBV_H		(regs0->cdwya_limit)
#define	CBV_YE		(MEM_CDYA+CBV_H)

//kevinmonkey 060530 old stuff, not used now...
//#define	MEM_OSDYA	(regs0->osd_base_addr)
//#define	OBV_YS		MEM_OSDYA
//#define	OBV_YE		(MEM_SUPYA)         //not used
//#define	OBV_H		(OBV_YE - OBV_YS)   //not used
//#define   ABV_YS      MEM_EABYA
//#define	ABV_YE		(MEM_CDYA)
//#define	ABV_H		(ABV_YE - ABV_YS)

#endif/*__REGMAP_DVD_H*/

