#ifndef	__BITOP_H
#define	__BITOP_H

// revn(): reverse #n LSB bit order
unsigned revn(unsigned u, int n);

//
// getbits utility for gunzip
// *note* this getbits utility is:
// 1. byte-oriented
// 2. LSB first
//

// t_getbit
typedef	struct {
    BYTE *p;
    int   r;
} t_getbit;

// showbits()
unsigned showbit(t_getbit *p);

// dumpbits()
#define	dumpbits(p,n)	(((p)->r)+=(n))

// getbits_bytealign()
static	inline
void
getbits_bytealign(t_getbit *p)
{
    p->r=(p->r+7) & ~7;
}

// maskbit()
static	inline
unsigned
maskbit(unsigned b, unsigned n)
{
    UINT32 mask = (n==32) ? 0xffffffffu : (1u<<n)-1;
    return b & mask;
}

// getbits()
static inline unsigned
getbits(t_getbit *p, int n)
{
    unsigned v = maskbit(showbit(p),n);
    dumpbits(p,n);
    return v;
}

// getbits_init()
static inline void
getbits_init(t_getbit *p, const void *ptr)
{
    p->p=(BYTE *)ptr;	// initialize input pointer
    p->r=0;		// initialize input bit-pointer
}

//
// gunzip()
// return <0 value for failure within gunzip process
// you need to initialize getbits structure before this.
//
int	gunzip(t_getbit *gb, BYTE *op);

#endif/*BITOP_H*/

