#include "config.h"
#include "regmap.h"
#include "global.h"
#include "cpu.h"

#include "uart.h"

static inline void flush_lbc(void)
{
    int o_md;
    regs0->lbc_control = 3;
    for (o_md=0;o_md<10000;o_md++) if ((regs0->lbc_control&1)==0) break;
}



#define REPORT_ONLY_PASS
//#define TSTART  0x180000                      // start from 1.5MB 
//#define TLEN    0x40000                    // test 1MB

#define TSTART  (128*1024)                      // from 128k
#define TLEN    (2048*1024 - TSTART)

void  
test_sdram(void)
{
    int o_md,o_dly,i_md,i_dly;
    int hwd_drv, bt1_drv, bt0_drv, ctl_drv, clko_drv;
    int i_bypass;
    UINT32 *p;

    cpu_intr_disable();

    UART0_puts("sdram_test\n");
    o_md = regs0->hw_cfg;
    UART0_puts("hwcfg mode:"); UART0_puthex(o_md); UART0_puts("\n");
    o_md = regs0->sysclk_sel; o_dly = regs0->sysclk_div_sel;
    UART0_puts("pllsel mode:"); UART0_puthex4(o_md); UART0_puts(" "); UART0_puthex4(o_dly); UART0_puts("\n");

    UART0_puts("test from $"); UART0_puthex(TSTART); UART0_puts("\n");
    UART0_puts("test leng $"); UART0_puthex(TLEN); UART0_puts("\n");

    regs0->sdram_clko_cfg  = 0x33;                       // 05    5      (0014)  
    regs0->sdram_clki_cfg  = 0x0;                        // 06    6      (0018)
    regs0->sdram_clki_dly_cfg = 0x80;                    // 07    7      (001c)
    regs0->pad_ctrl = 0xaaff; // all 20mA drive
//    regs0->pad_ctrl = 0xaaaa; // all 12mA drive
//    regs0->pad_ctrl = 0x5555; // all 8mA drive
  //   regs0->pad_ctrl = 0x555B; // all 8mA drive

    p = (UINT32 *)(0xa0000000 + TSTART);


//    for (hwd_drv=1;hwd_drv<=3;hwd_drv++)
//    {
//    for (bt1_drv=1;bt1_drv<=3;bt1_drv++)
//    {
//    for (bt0_drv=1;bt0_drv<=3;bt0_drv++)
//    {
//    for (ctl_drv=1;ctl_drv<=3;ctl_drv++)
//    {
//    for (clko_drv=1;clko_drv<=3;clko_drv++)
//    {
    
          hwd_drv = 1;
          bt1_drv = 1;
          bt0_drv = 1;
          ctl_drv = 2;
          clko_drv = 3;
//            regs0->pad_ctrl = 0x5000 | 
            regs0->pad_ctrl = 0x5000 | 
            		(hwd_drv<<10) |
            		(hwd_drv<<8) |
            		(bt1_drv<<6) |
            		(bt0_drv<<4) |
            		(ctl_drv<<2) |
            		 clko_drv; 
		//regs0->pad_ctrl = 0xaaff;
            UART0_puts("\nhwd-bt1-bt0-ctl-clko drv = ");
            UART0_puthex4(hwd_drv);UART0_puts("-");
            UART0_puthex4(bt1_drv);UART0_puts("-");
            UART0_puthex4(bt0_drv);UART0_puts("-");
            UART0_puthex4(ctl_drv);UART0_puts("-");
            UART0_puthex4(clko_drv);UART0_puts(" ");
            UART0_puthex4(regs0->pad_ctrl);UART0_puts("\n");

//    for (i_bypass=0; i_bypass<2; i_bypass++)
    for (i_bypass=1; i_bypass<2; i_bypass++)
    {
    for (o_md=0;o_md<=5;o_md++)
    {
    for (o_dly=0;o_dly<16;o_dly++)
    {
        int j_pass=0;
        // OUT: o_dly:o_md
        if (o_md!=0 && o_md!=1) continue;

        for (i_md=0;i_md<8;i_md++)
        {
            if (i_md==2) continue;
            if (i_md==3) continue;
            if (i_md==4) continue;
            if (i_md==5) continue;
        for (i_dly=0;i_dly<16;i_dly++)
        {
            // IN: i_dly:i_md
            int tst, failed, failed_total;
            failed_total = 0;

            UART0_puts("\r");
            UART0_puthex4(o_dly); UART0_puthex4(o_md);
            UART0_puthex4(i_dly); UART0_puthex4(i_md);

#ifndef REPORT_ONLY_PASS
            UART0_puts("\rsdram_test");
            UART0_puts(" OUT ");
            UART0_puthex4(o_dly); UART0_puts("-"); UART0_puthex4(o_md);
            UART0_puts(" IN ");
            UART0_puthex4(i_dly); UART0_puts("-"); UART0_puthex4(i_md);
            UART0_puts("\n");
#endif
o_md = 0;
            regs0->sdram_clko_cfg       = (o_dly<<3)|(o_md);
            if (i_bypass==0) {
                regs0->sdram_clki_cfg       = (i_dly<<3)|(i_md);
            } else {
                regs0->sdram_clki_dly_cfg   = (1<<7) | (i_dly<<3)|(i_md);
            }
            regs0->sdctrl_mrs       = 1;
            for (tst=0;tst<1024;tst++) asm volatile ("nop");
            for (tst=0;tst<TLEN/4;tst++) p[tst] = 0;

            // write 0
            for (tst=0;tst<TLEN/4;tst++) p[tst] = 0x00000000;
            flush_lbc();
            for (tst=failed=0;tst<TLEN/4;tst++) if (p[tst]!=0x00000000) {
                failed++;}
#ifdef REPORT_ONLY_PASS
            if (failed!=0) continue;
#else
            if (failed!=0) {
                UART0_puts("\ttst0 failed "); UART0_puthex(failed);
                UART0_puts("\n");
            }
//            else UART0_puts("\ttst0 ok\n");
#endif
            failed_total += failed;

            // write 00000000-ffffffff
            for (tst=0;tst<TLEN/4;tst+=2) {
                p[tst+0] = 0xffffffff;
                p[tst+1] = 0x00000000;
            }
            flush_lbc();
            for (tst=failed=0;tst<TLEN/4;tst+=2) {
                if (p[tst+0]!=0xffffffff) {failed++;}
                if (p[tst+1]!=0x00000000) {failed++;}
            }
#ifdef REPORT_ONLY_PASS
            if (failed!=0) continue;
#else
            if (failed!=0) {
                UART0_puts("\ttst1 failed "); UART0_puthex(failed);
                UART0_puts("\n");
            }
//            else UART0_puts("\ttst1 ok\n");
#endif
            failed_total += failed;

            // write 5555aaaa
            for (tst=0;tst<TLEN/4;tst+=2) {
                p[tst+0] = 0x5555aaaa;
                p[tst+1] = 0xffff0000;
            }
            flush_lbc();
            for (tst=failed=0;tst<TLEN/4;tst+=2) {
                if (p[tst+0]!=0x5555aaaa) {failed++;}
                if (p[tst+1]!=0xffff0000) {failed++;}
            }
#ifdef REPORT_ONLY_PASS
            if (failed!=0) continue;
#else
            if (failed!=0) {
                UART0_puts("\ttst2 failed "); UART0_puthex(failed);
                UART0_puts("\n");
            }
//            else UART0_puts("\ttst2 ok\n");
#endif
            failed_total += failed;

            // write sequential number
            for (tst=0;tst<TLEN/4;tst++) p[tst] = tst;
            flush_lbc();
            for (tst=failed=0;tst<TLEN/4;tst++) if (p[tst]!=(UINT32)tst) {failed++;}
#ifdef REPORT_ONLY_PASS
            if (failed!=0) continue;
#else
            if (failed!=0) {
                UART0_puts("\ttst3 failed "); UART0_puthex(failed);
                UART0_puts("\n");
            }
//            else UART0_puts("\ttst3 ok\n");
#endif
            failed_total += failed;

            // write sequential number and toggle pattern
            for (tst=0;tst<TLEN/4;tst++) p[tst] = (tst<<16)|(0x55aa);
            flush_lbc();
            for (tst=failed=0;tst<TLEN/4;tst++) if (p[tst]!=(((UINT32)tst<<16)|(0x55aa))) {failed++;}
#ifdef REPORT_ONLY_PASS
            if (failed!=0) continue;
#else
            if (failed!=0) {
                UART0_puts("\ttst4 failed "); UART0_puthex(failed);
                UART0_puts("\n");
            }
//            else UART0_puts("\ttst4 ok\n");
#endif
            failed_total += failed;


#ifdef REPORT_ONLY_PASS
            if (failed_total==0)
#endif
            {
                UART0_puts("\r    sdram_test config ");
                if (i_bypass) UART0_puts("bypass ");
                UART0_puts(" OUT ");
                UART0_puthex4(o_dly); UART0_puts("-"); UART0_puthex4(o_md);
                UART0_puts(" IN ");
                UART0_puthex4(i_dly); UART0_puts("-"); UART0_puthex4(i_md);
                if (failed_total)
                    UART0_puts(" failed\n");
                else
                    UART0_puts(" passed\n");
            }
            if (failed_total==0)
                j_pass++;
        }
        }
#ifdef REPORT_ONLY_PASS
        if (j_pass)
#endif
        {
            UART0_puts("\r    sdram_test config ");
            UART0_puts(" OUT ");
            UART0_puthex4(o_dly); UART0_puts("-"); UART0_puthex4(o_md);
            UART0_puts(" passed ");
            UART0_puthex4(j_pass); 
            UART0_puts("\n");
        }
    }
    }
    }

//    }
//    }
//    }
//    }
//    }


    UART0_puts("sdram test finished\n");
    while (1);
}

