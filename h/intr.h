#ifndef	__INTR_H
#define	__INTR_H

#ifdef	UNIX
#define	r3k_intr_enable()
#define	r3k_intr_disable()
#define	r3k_set_intr_mask(x)
#define	r3k_get_intr_mask()	(0)
#else
void	r3k_intr_config(int);
void	r3k_intr_enable(void);
void	r3k_intr_disable(void);

UINT32	r3k_set_intr_mask(UINT32);
UINT32	r3k_get_intr_mask(void);
#endif

#endif/*__INTR_H*/

