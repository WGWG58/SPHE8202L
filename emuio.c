/*
** FILE
** emuio.c
** DESCRIPTION
*/

#include "config.h"
#include "regmap.h"
#include "global.h"

#include "emuiodrv.h"
#include "emuio.h"


#ifdef	DVDRELEASE
//#define IOWRITE_NOWAIT
#endif

#ifndef	DVDRELEASE
#define EMUIO_DBG     1
#endif

#define IOWRITE_WAIT_SLOW	20000
#define IOWRITE_WAIT_MAX	(0x4000000)

#ifdef	IOWRITE_NOWAIT
#undef	IOWRITE_WAIT_MAX
#define	IOWRITE_WAIT_MAX	10000
#endif

//
// FUNCTION
// io_getc(c)
//
int
io_getc(void)
{
   int c;

   if (!IsEPPRxEmpty())
      c = EPP_GETC();
   else
      c = 0;
   return c;
}


//
// FUNCTION
// polling_io()
//
// DESCRIPTION
// check IO interface for incoming command
//

#ifdef SUPPORT_EPP

#if EMUIO_DBG
BYTE	key_trick=0;
#endif

int polling_io(void)
{
#ifndef	SUPPORT_UART_UPGRADE
    while (!IsEPPRxEmpty())
    {
        int c = EPP_GETC();
#if EMUIO_DBG
        if (c == 'm')
            key_trick = 1;
        else if (c == 'o')
            key_trick = (key_trick == 1) ? 2 : 0;
        else if (c == 'n' && key_trick == 2)
        {
            key_trick = 0;
            return 1;
        }
        else key_trick = 0;
#endif
    }
#endif
    return 0;
}


//
// FUNCTION
// reset_io
//
void reset_io(void)
{
    RESET_EPP();
#ifdef EMUIO_DBG
    io_write("EMUIO\n");
#endif
}



#define	IO_WAIT()	\
		do {					\
		  int timeout = IOWRITE_WAIT_MAX;	\
    		  do {					\
		    if (!IsEPPTxFull()) break;		\
		  } while (--timeout>0);		\
		} while (0)

#define	IO_WAIT_EMPTY()	\
		do {					\
		  int timeout = IOWRITE_WAIT_MAX;	\
    		  do {					\
		    if (IsEPPTxEmpty()) break;		\
		  } while (--timeout>0);		\
		} while (0)

#define	IO_PUTC(c)	\
  		do {					\
		  EPP_PUTC(c);				\
		  if ((c)==0x0a) EPP_PUTC(0x0d);	\
		} while (0)

#define	IO_PUTC_WAIT(c)	\
		do {					\
		  IO_WAIT();				\
		  EPP_PUTC(c);				\
		  if ((c)==0x0a) {			\
		    IO_WAIT();				\
		    EPP_PUTC(0x0d);			\
		  }					\
		} while (0)

#define	IO_PUTC_EXACT(c) \
		do {					\
		  EPP_PUTC_EXACT(c);			\
		  if ((c)==0x0a) {			\
		    IO_WAIT();				\
		    EPP_PUTC_EXACT(0x0d);		\
		  }					\
		} while (0)


//
// FUNCTION
// io_write_flush
//
// DESCRIPTION
// Wait until output fifo empty
//
// *NOTE*
// this might hang the system if IO system failed.
//
void
io_write_flush(void)
{
  IO_WAIT_EMPTY();
}


//
// FUNCTION
// io_putc(c)
//
void
io_putc(int c)
{
    IO_PUTC(c);
}


void
io_putc_wait(int c)
{
    IO_PUTC_WAIT(c);
}


void
io_puthex4(unsigned x)
{
    IO_PUTC(radix_table[(x>>12)&0x0f]);
    IO_PUTC(radix_table[(x>>8)&0x0f]);
    IO_PUTC(radix_table[(x>>4)&0x0f]);
    IO_PUTC(radix_table[(x>>0)&0x0f]);
}


void
io_puthex(unsigned x)
{
    IO_PUTC(radix_table[(x>>28)&0x0f]);
    IO_PUTC(radix_table[(x>>24)&0x0f]);
    IO_PUTC(radix_table[(x>>20)&0x0f]);
    IO_PUTC(radix_table[(x>>16)&0x0f]);
    IO_PUTC(radix_table[(x>>12)&0x0f]);
    IO_PUTC(radix_table[(x>>8)&0x0f]);
    IO_PUTC(radix_table[(x>>4)&0x0f]);
    IO_PUTC(radix_table[(x>>0)&0x0f]);
}


//
// FUNCTION
// io_write(s)
//
// DESCRIPTION
// write to EPP port without waiting for FIFO.
// will reset EPP port when FIFO fulled.
//
void
io_write(const char *s)
{
  int	c;
  while ((c=*s++))
  {
    IO_PUTC(c);
  }
}


//
// FUNCTION
// io_write_slow
//
// DESCRIPTION
// wait a specific time (or until FIFO not full) before write.
//
void
io_write_slow(const char *s)
{
  int  c;
  while ((c=*s++)!=0)
  {
    int	 timeout = IOWRITE_WAIT_SLOW;
    do {
      if (!IsEPPTxFull()) break;
    } while (--timeout);
    IO_PUTC(c);
  } while (1);  
}


//
// FUNCTION
// io_write_wait
//
// DESCRIPTION
// write and wait
//
// *NOTE*
// we might have a timeout on this, like for a second..
//
void
io_write_wait(const char *s)
{
  int  c;
  while ((c=*s++)!=0)
  {
    IO_PUTC_WAIT(c);
  }
}


//
// FUNCTION
// io_write_exact(s)
//
void
io_write_exact(const char *s)
{
  int c;
  while ((c=*s++)!=0)
  {
    EPP_PUTC_EXACT(c);
    if (c==0x0a)
    {
      EPP_PUTC_EXACT(0x0d);
    }
  } 
}


void
mon_polling_break(UINT8 flg)
{
    if (monflg == flg)
    {
        monflg = 1;
        while (monflg == 1)
            polling();
    }
}

void
mon_break(UINT8 flg)
{
    if (monflg == flg)
    {
        monflg = 1;
        while (monflg == 1)
            ;
    }
}

#endif
