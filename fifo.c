#include "config.h"
#include "regmap.h"
#include "global.h"
#include "dma.h"
#include "fifo.h"


unsigned FifoGetByte(tFifo *fifo)
{
  unsigned c = fifo->data[fifo->tail];
  FifoTailAdv(fifo, 1);
  return c;
}

unsigned FifoGetWord(tFifo *fifo)
{
  int  t,s;
  BYTE *d;
  unsigned c;

  t = fifo->tail;
  s = fifo->size;
  d = fifo->data;

  c = d[t];
  t = WRAPl(t+1,s);
  c = (c<<8) | d[t];
  fifo->tail = WRAPl(t+1,s);
  return c;
}


int FifoDMARead(tFifo *f, int p, int len)
{
  int	i;
  BYTE	c;

  for (i=0; i<len; i++)
  {
    c = FifoGetByte(f);
    dma_buf.b[i+p] = c;
  }
  return 0;
}


