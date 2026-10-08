/*
** FILE
** uartsup.h
**
** DESCRIPTION
** UART debugging support function
**
** NOTE
** These inline functions are standalone and use only register file access.
** Important for debugging.
*/

#ifndef	__UARTSUP_H
#define	__UARTSUP_H

// LSR	0: tx-rdy	1: tx-fifo not-full
//	1: rx-rdy	1: rx-fifo not-empty

#define	UART_LSR_TX_RDY     (1<<0)
#define	UART_LSR_RX_RDY     (1<<1)
#define	UART_TX_EMPTY       (1<<6)
#define	UART_RX_EMPTY       (1<<7)

#define	UART0_tx_rdy()		(regs0->uart0_lsr & UART_LSR_TX_RDY)
#define	UART0_rx_rdy()		(regs0->uart0_lsr & UART_LSR_RX_RDY)
#define	UART0_tx_empty()	(regs0->uart0_lsr & UART_TX_EMPTY)
#define UART0_putc_nw(c)        (regs0->uart0_data = (c))

#define	UART1_tx_rdy()		(regs0->uart1_lsr & UART_LSR_TX_RDY)
#define	UART1_rx_rdy()		(regs0->uart1_lsr & UART_LSR_RX_RDY)
#define	UART1_tx_empty()	(regs0->uart1_lsr & UART_TX_EMPTY)
#define UART1_putc_nw(c)        (regs0->uart1_data = (c))


// UART0
#define UART0_wait()            do { while (!UART0_tx_rdy()) ; } while (0)
#define UART0_flush()           do { while (!UART0_tx_empty()) ; } while (0)
#define	UART0_putc(c)           do { UART0_wait(); UART0_putc_nw(c); } while (0)
#define	UART0_putc_nl(c)        do { UART0_putc(c); if (c==0x0a) UART0_putc(0x0d); } while (0)

#define UART0_puthex(c)		do {                            \
                                    int __i;			\
                                    unsigned __v = (c);		\
                                    for (__i=0;__i<8;__i++)	\
                                    {                           \
                                        UART0_putc(radix_table[(__v>>28)&0x0f]); \
                                        __v <<= 4;              \
                                    }                           \
				} while (0)

#define UART0_puthex4(c)	do {                            \
                                    int __i;                    \
                                    unsigned __v = (unsigned)(c); \
                                    for (__i=0;__i<4;__i++)     \
                                    {				\
                                        UART0_putc(radix_table[(__v>>12)&0x0f]); \
                                        __v <<= 4;              \
                                    }                           \
                                } while (0)

#define UART0_puthex2(c)	do {                            \
                                    unsigned __v = (unsigned)(c); \
                                    UART0_putc(radix_table[(__v>>4)&0x0f]); \
                                    UART0_putc(radix_table[(__v>>0)&0x0f]); \
                                } while (0)

#define UART0_puts(s)		do {				\
                                    int __c;			\
                                    const char *__s = (const char *)(s); \
                                    while ((__c=*__s++))	\
                                    {				\
                                        UART0_putc_nl(__c);     \
                                    }				\
                                } while (0)


// UART1
#define UART1_wait()            do { while (!UART1_tx_rdy()) ; } while (0)
#define UART1_flush()           do { while (!UART1_tx_empty()) ; } while (0)
#define	UART1_putc(c)           do { UART1_wait(); UART1_putc_nw(c); } while (0)

#define UART1_puthex(c)		do {                            \
                                    int __i;			\
                                    unsigned __v = (c);		\
                                    for (__i=0;__i<8;__i++)	\
                                    {                           \
                                        UART1_putc(radix_table[(__v>>28)&0x0f]); \
                                        __v <<= 4;              \
                                    }                           \
				} while (0)

#define UART1_puthex4(c)	do {                            \
                                    int __i;                    \
                                    unsigned __v = (c);         \
                                    for (__i=0;__i<4;__i++)     \
                                    {				\
                                        UART1_putc(radix_table[(__v>>12)&0x0f]); \
                                        __v <<= 4;              \
                                    }                           \
                                } while (0)

#define UART1_puthex2(c)	do {                            \
                                    unsigned __v = (unsigned)(c); \
                                    UART1_putc(radix_table[(__v>>4)&0x0f]); \
                                    UART1_putc(radix_table[(__v>>0)&0x0f]); \
                                } while (0)

#define UART1_puts(s)		do {				\
                                    int __c;			\
                                    const char *__s = (const char *)(s); \
                                    while ((__c=*__s++))	\
                                    {				\
                                        UART1_putc(__c);        \
                                        if (__c==0x0a) UART1_putc(0x0d); \
                                    }				\
                                } while (0)


#endif /*__UARTSUP_H*/

