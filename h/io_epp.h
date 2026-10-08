#ifndef	__IO_EPP_H
#define	__IO_EPP_H

//#define	RESET_EPP()		do {regs0->epp_status = 0xf000;} while (0)
#define EPP_PUTC_EXACT(c)	EPP_PUTC(c)

static inline int
EPP_GETC(void)
{
//  int c = regs0->epp_data;
//  (void)regs0->epp_status;
  asm volatile ("nop");
  return c;
}

static inline void
EPP_PUTC(int c)
{
//  regs0->epp_data = c;
//  (void)regs0->epp_status;
  asm volatile ("nop");
}

//#define EPP_STATUS              (regs0->epp_status)
//#define IsEPPRxFull()           (EPP_STATUS & RF_EPP_IN_FULL)
//#define IsEPPRxEmpty()          (EPP_STATUS & RF_EPP_IN_EMPTY)
//#define IsEPPTxFull()           (EPP_STATUS & RF_EPP_OUT_FULL)
//#define IsEPPTxEmpty()          (EPP_STATUS & RF_EPP_OUT_EMPTY)

#endif

