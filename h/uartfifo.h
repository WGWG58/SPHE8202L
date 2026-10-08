#ifndef	__UARTFIFO_H
#define	__UARTFIFO_H

void	reset_uart1_fifo(void);
int		is_uart1_fifo_empty(void);
int		is_uart1_fifo_full(void);
void	write_uart1(int c);
void	write_uart1_exact(int c);

void	intr_uart1(void);

#ifdef DVD728
// UART 0
void	reset_uart0_fifo(void);
int		is_uart0_fifo_empty(void);
int		is_uart0_fifo_full(void);
void	write_uart0(int c);
void	write_uart0_exact(int c);

void	intr_uart0(void);
#endif

#endif/*__UARTFIFO_H*/

