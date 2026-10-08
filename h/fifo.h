#ifndef __FIFO_H__
#define __FIFO_H__

#include "regmap.h"
#include "types.h"
#include "stdlib.h"

typedef struct 
{
  unsigned char *data;
  int size;
  int head;
  int tail;

  unsigned	word;
  int		bit_left;
} tFifo;

#ifdef ENABLE_INLINE
static inline int  WRAPl(int r, int s) {return (r<0) ? (r+s) : r;}
static inline int  WRAPr(int r, int s) {return (r>=s) ? (r-s) : r;}
static inline void FifoTailAdv(tFifo *fifo, int n) {fifo->tail = WRAPr(fifo->tail+n,fifo->size);}
static inline void FifoHeadAdv(tFifo *fifo, int n) {fifo->head = WRAPr(fifo->head+n,fifo->size);}
#else
#define	WRAPl(r,s) (((r)<0) ? ((r)+(s)) : (r))
#define	WRAPr(r,s) (((r)>=(s)) ? ((r)-(s)) : (r))
#define	FifoTailAdv(f, n) (f->tail = WRAPr(f->tail+n,f->size))
#endif

/*
static inline unsigned FifoGetByte(tFifo *fifo)
{
  int   size = fifo->size;
  int   tail = fifo->tail;
  unsigned c = fifo->data[tail];
  fifo->tail = WRAPr(tail+1,size);
  return c;
}
*/

#ifdef ENABLE_INLINE
static inline unsigned FifoRetrieve(tFifo *fifo, int i)
{
  int   size = fifo->size;
  int   tail = fifo->tail;
  return fifo->data[WRAPr(tail+i, size)];
}
#endif


#define FifoGetLength(fifo)	(WRAPl((fifo)->head-(fifo)->tail, (fifo)->size))
#define FifoGetFree(fifo)	((fifo)->size - FifoGetLength(fifo))
#define FifoGetBitInit(fifo)	((fifo)->bit_left=0)
#define FifoGetBitRestart(fifo)	(FifoGetBitInit(fifo))

unsigned	FifoGetByte(tFifo *);
unsigned	FifoGetWord(tFifo *);
unsigned	FifoGetBits(tFifo *, int);

#ifdef __GNUC__
static inline void FifoLoad(tFifo *f, char *p, int len)
{
  int l1;
  int head = f->head;
  int size = f->size;

  if ((l1=size-head)<len)
  {
    memcpy(f->data+head, p, l1);
    len -= l1;
    p += l1;
    head = 0;
  }
  memcpy(f->data+head, p, len);
  f->head = head+len;
}
#endif

int	FifoDMARead(tFifo *, int, int );

#endif/*__FIFO_H__*/

