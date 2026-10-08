#ifndef	__IO_UART0_H
#define	__IO_UART0_H

#include "set.h"
#include "uart.h"
#include "uartfifo.h"

#ifdef NO_AUDIO_DSP
#define RESET_EPP()		UART0_set_baudrate(UART_BAUD_115200)
#else
#define RESET_EPP()		UART0_set_baudrate(UART_BAUD_115200)
#endif
#define IsEPPRxEmpty()          (!UART0_rx_rdy())
#define EPP_GETC()              (regs0->uart0_data)

#if 0
// direct put
#define IsEPPTxFull()           (!UART0_tx_rdy())
#define IsEPPTxEmpty()          (UART0_tx_empty())
#define EPP_PUTC(c)             (regs0->uart0_data = (c))
#define EPP_PUTC_EXACT(c)        (regs0->uart0_data = (c))
#else
#define IsEPPTxFull()           (is_uart0_fifo_full())
#define IsEPPTxEmpty()          (is_uart0_fifo_empty())
#define EPP_PUTC(c)             (write_uart0(c))
#define EPP_PUTC_EXACT(c)       (write_uart0_exact(c))
#endif

#endif/*__UARTOUT_H*/
