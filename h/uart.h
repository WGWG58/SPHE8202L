#ifndef	__UART_H
#define	__UART_H

// standard value
#define	BAUDCC(f,c)		((UINT32)((2*(c)+16*(f)) / (32*(f)))-1)

#include "sysclk.h"
#define	BAUDC(f)		BAUDCC(f,SYSCLK)

//
// uart clock divisor
// 		81MHz
//	9600	020e
//	115200	002b	3f
//
#define	UART_BAUD_9600		BAUDC(9600)
#define	UART_BAUD_57600		BAUDC(57600)
#define	UART_BAUD_115200	BAUDC(115200)
#define	UART_BAUD_230400	BAUDC(230400)
#define	UART_BAUD_460800	BAUDC(460800)
#define	UART_BAUD_921600	BAUDC(921600)

#define	UART_BAUD_88200 	BAUDC(88200)

#define	UART0_set_baudrate(x)	do { 				\
				  regs0->uart0_div_h = (x>>8);	\
				  regs0->uart0_div_l = (x);	\
				} while (0)			\

#define	UART1_set_baudrate(x)	do { 				\
				  regs0->uart1_div_h = (x>>8);	\
				  regs0->uart1_div_l = (x);	\
				} while (0)			\



#include "uartsup.h"

#endif/*__UART_H*/

