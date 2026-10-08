#ifndef __EMUIO_H
#define __EMUIO_H

#ifdef	SUPPORT_EPP
void	reset_io(void);
int	polling_io(void);

void	io_putc(int c);
void	io_putc_wait(int c);
void	io_write_flush(void);
void	io_write(const char *);
void	io_write_slow(const char *);
void	io_write_wait(const char *);
void	io_write_exact(const char *);
void    mon_break(UINT8);
void    mon_polling_break(UINT8);

extern	UINT8	linebuf[];

#include "sio.h"

// printf_w
// printf_nw
#define	printf_w(s...) \
	do { psprintf(linebuf, ##s); io_write_wait(linebuf); } while (0)

#define	printf_nw(s...) \
	do { psprintf(linebuf, ##s); io_write(linebuf); } while (0)

#else
// disable EPP functions
#define	reset_io()		(0)
#define	polling_io()		(0)

#define	io_putc(c)		((void)0)
#define	io_putc_wait(c)		((void)0)
#define	io_write_flush()	((void)0)
#define	io_write(s)		((void)0)
#define	io_write_slow(s)	((void)0)
#define	io_write_wait(s)	((void)0)
#define	io_write_exact(s)	((void)0)

#define printf_nw(s...)		((void)0)
#define printf_w(s...)		((void)0)

#define mon_break(c)            ((void)0)
#define mon_polling_break(c)    ((void)0)

#endif

#define	putc_w(c)		io_putc_wait(c)
#define	putc_nw(c)		io_putc(c)
#define	puts_w(s)		io_write_wait(s)
#define	puts_nw(s)		io_write(s)

#ifndef	printf
#define	printf		printf_w
#endif

#endif/*__EMUIO_H*/
