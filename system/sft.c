#include "config.h"
#include "regmap.h"

void sft_hvsync(void)   //freyman 2004-2-27 12:00
//sft_hvsync(int enable)
{
#ifdef  SPHE8202
#if defined(ADD_PC_VGA_OUT)&&defined(DVDRELEASE)//PC_VGA_OUT//nono change the name of the definition.5-8-22 21:14
    #ifndef UART_SWAP//axel swap uart0 and uar1 2004/10/29
    // select HV-sync in stead of UART0
    regs0->sft_cfg2 = regs0->sft_cfg2 & ~(3<<2);                // SFT_CFG[3:2]=0;
                                                                // disable UART
    regs0->sft_cfg3 = (regs0->sft_cfg3 & ~(3<<12)) | (0<<12);   // SFT_CFG3[13:12]=2'b00
                                                                // disable TV_SYNC
    regs0->sft_cfg4 = (regs0->sft_cfg4 & ~(7<<13)) | (3<<13);   // SFT_CFG4[15:13]=3'b011
    #endif //#ifndef UART_SWAP                                                                // select PC_sync
#endif	// PC_VGA_OUT

#else
        #ifdef QSI_SHOW_ERR_RATE
            //#include "uart.h"
            //#undef UART_SWAP
        
            //regs0->sft_cfg2 |= 1<<15;
            //UART0_set_baudrate(BAUDCC(115200, 121500000));
            //psprintf(linebuf,"cd trk hi=%d\n",cd_trk_hi);         
            //UART0_puts(linebuf);          
            //return;
        #endif   
    // select HV-sync in stead of UART0
    regs0->sft_cfg2 &= 0xFFE3;      // DISABLE UART0
    regs0->sft_cfg3 |= 0x4000;      // select H/V sync
#endif
}


void
sft_uart0_share_uart1_pins()
{
#ifndef SPHE8202
    //
    // move UART0 to UART1 location
    unsigned u;
    u = regs0->sft_cfg2;
    regs0->sft_cfg2 = (u&~((0x07<<2)|(0x0f<<5))) | ((0x04<<2)|(0x09<<5));
    u = regs0->sft_cfg3;
    regs0->sft_cfg3 = (u&~(0x03<<14)) | (0x01<<14);
#endif
}

void
sft_uart_swap()
{
    unsigned u;
    u = regs0->sft_cfg2;
    regs0->sft_cfg2 = ((u&~((0x03<<2)|(0x03<<4)|(0x03<<14))) | ((0x01<<2)|(0x03<<4)|(0x03<<14) ));
}

