#ifndef	__RINGBUF_H
#define	__RINGBUF_H

/*
** ring buffer control
**
**	..uuudddddd...
**	  B  R    W
**
*/
#if 0
//static inline int  WRAPl(int r, int s) {return (r<0) ? (r+s) : r;}
//static inline int  WRAPr(int r, int s) {return (r>=s) ? (r-s) : r;}
#endif

#ifdef ENABLE_INLINE
static inline int  WRAPl(int r, int s) {return (r<0) ? (r+s) : r;}
static inline int  WRAPr(int r, int s) {return (r>=s) ? (r-s) : r;}
#else
#define WRAPl(r,s) (((r)<0) ? ((r)+(s)) : (r))
#define WRAPr(r,s) (((r)>=(s)) ? ((r)-(s)) : (r))
#endif

//#define WRAPl(r,s) (((r)<0) ? ((r)+(s)) : (r))
//#define WRAPr(r,s) (((r)>=(s)) ? ((r)-(s)) : (r))
int	RingBufferSize(int Wp, int Rp, int L);
int	RingBufferFree(int Wp, int Bp, int L);


#endif/*__RINGBUF_H*/

