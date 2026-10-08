#ifndef	__MEM_H
#define	__MEM_H

void	*__memcpy(void *d, const void *s, int n);
void	*__memmove(void *d, const void *s, int n);

#ifdef	USE_MEM_H
#define	memcpy(d,s,n)	__memcpy(d,s,n)
#define	memmove(d,s,n)	__memmove(d,s,n)
#endif/*USE_MEM_H*/

#endif/*__MEM_H*/

