#ifndef	__IO_UART1_H
#define	__IO_UART1_H

#include "uart.h"
#include "uartfifo.h"

#define RESET_EPP()		UART1_set_baudrate(UART_BAUD_115200)
#define IsEPPRxEmpty()          (!UART1_rx_rdy())
#define EPP_GETC()              (regs0->uart1_data)

#if 0
// direct put
#define IsEPPTxFull()           (!UART1_tx_rdy())
#define IsEPPTxEmpty()          (UART1_tx_empty())
#define EPP_PUTC(c)             (regs0->uart1_data = (c))
#define EPP_PUTC_EXACT(c)        (regs0->uart1_data = (c))
#else
#define IsEPPTxFull()           (is_uart1_fifo_full())
#define IsEPPTxEmpty()          (is_uart1_fifo_empty())
#define EPP_PUTC(c)             (write_uart1(c))
#define EPP_PUTC_EXACT(c)       (write_uart1_exact(c))
#endif

#endif/*__UARTOUT_H*/
