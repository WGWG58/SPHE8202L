#include "config.h"
#include "regmap.h"
#include "uart.h"


#ifndef DVDRELEASE

#ifdef SOFT_UART_OUT   
	extern int PutSoftUartChar(BYTE *,int);
#endif	

UINT16	uart_rp;
UINT16	uart_wp;

#define	FIFOS	256

char	uart_buf[FIFOS];


void	reset_uart1_fifo()
{
  uart_rp = uart_wp = 0;
  regs0->uart1_isc  = 0;	// disable interrupt
}


int	is_uart1_fifo_empty()
{
#if 0
  unsigned rp = uart_rp;
  unsigned wp = uart_wp;

  if (wp==rp) return 1;
  else
  {
    if (UART1_tx_rdy())
    {
      regs0->uart1_data = uart_buf[rp];
      rp = rp+1;
      if (rp>=FIFOS) rp=0;
    }
    uart_rp = rp;
  }
  return 0;
#endif
  return (uart_rp==uart_wp);
}

#define	ENABLE_UART1_INTR()	(regs0->uart1_isc=(1<<4))


int	is_uart1_fifo_full()
{
  int wp = uart_wp;
  int rp = uart_rp;
  int wpn;

  wpn = wp+1;
  if (wpn>=FIFOS) wpn=0;
  if (wp!=rp) ENABLE_UART1_INTR();	// not-empty: enable interrupt
  return (wpn==rp);			// full-condition
}


void	write_uart1(int c)
{

#ifdef SOFT_UART_OUT   
  PutSoftUartChar((BYTE *)&c,1);
#else 	
  int wp = uart_wp;
  int rp = uart_rp;
  int wpn;
	
  wpn = wp+1;
  if (wpn>=FIFOS) wpn=0;
  if (wpn!=rp) {uart_buf[wp] = c; uart_wp = wpn;}
  ENABLE_UART1_INTR();					// enable it.
#endif  
}


void	write_uart1_exact(int c)
{

#ifdef SOFT_UART_OUT   
	PutSoftUartChar((BYTE *)&c,1);
#else
  UART1_putc(c);
#endif  
}



#include "intdef.h"

#ifdef SERVO_UART
UINT8 gcRS232Data[5];
UINT8 gwWPtr=0;
UINT8 cReveiveRs232=0;
#endif

void	intr_uart1(void)
{
  int wp = uart_wp;
  int rp = uart_rp;

#ifdef SERVO_UART
 #if 0
  if (UART1_rx_rdy())
  {
      gcRS232Data[gwWPtr] = (regs0->uart1_data);
	  if (gwWPtr >= 4)
	  {
			cReveiveRs232 = 1;
			gwWPtr = 0;
	  }
	  else
	  {
			cReveiveRs232 = 0;
		    gwWPtr ++;
	  }
  }
 #endif
#else
  if (regs0->uart1_isc & 0x01)
  {
    while (wp!=rp && UART1_tx_rdy())
    {
      regs0->uart1_data = uart_buf[rp];
      rp = rp+1;
      if (rp>=FIFOS) rp=0;
    }
  }
  if (rp==wp) regs0->uart1_isc = 0;
  uart_rp = rp;
#endif
  regs0->intr_flag	= INTR_UART1_INT;
}


#ifdef DVD728
//
// UART 0
void	reset_uart0_fifo()
{
  uart_rp = uart_wp = 0;
  regs0->uart0_isc  = 0;	// disable interrupt
}

int	is_uart0_fifo_empty()
{
  return (uart_rp==uart_wp);
}

#define	ENABLE_UART0_INTR()	(regs0->uart0_isc=(1<<4))


int	is_uart0_fifo_full()
{
  int wp = uart_wp;
  int rp = uart_rp;
  int wpn;

  wpn = wp+1;
  if (wpn>=FIFOS) wpn=0;
  if (wp!=rp) ENABLE_UART0_INTR();	// not-empty: enable interrupt
  return (wpn==rp);			// full-condition
}


void	write_uart0(int c)
{
#ifdef SOFT_UART_OUT   
  PutSoftUartChar((BYTE *)&c,1);
#else 	
  int wp = uart_wp;
  int rp = uart_rp;
  int wpn;
	
  wpn = wp+1;
  if (wpn>=FIFOS) wpn=0;
  if (wpn!=rp) {uart_buf[wp] = c; uart_wp = wpn;}
  ENABLE_UART0_INTR();					// enable it.
#endif  
}


void	write_uart0_exact(int c)
{

#ifdef SOFT_UART_OUT   
	PutSoftUartChar((BYTE *)&c,1);
#else
  UART0_putc(c);
#endif  
}

void	intr_uart0(void)
{
  int wp = uart_wp;
  int rp = uart_rp;

#if 1
  if (regs0->uart0_isc & 0x01)
  {
    while (wp!=rp && UART0_tx_rdy())
    {
      regs0->uart0_data = uart_buf[rp];
      rp = rp+1;
      if (rp>=FIFOS) rp=0;
    }
  }
  if (rp==wp) regs0->uart0_isc = 0;
  uart_rp = rp;
#endif
  regs0->intr_flag	= INTR_UART0_INT;
}
#endif
#else
void	intr_uart0(void) {}
void	intr_uart1(void) {}
#endif

