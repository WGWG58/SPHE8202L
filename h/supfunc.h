#ifndef	__SUPFUNC_H
#define	__SUPFUNC_H

// peif/sup.c
extern  void    hl0_set_location(BYTE *);
extern  void    hl0_set_color(UINT32 color, UINT32 contr);

// kernel/sup0.c
extern  void	init_sup(void);
extern  void    reset_sup(void);

extern  void	sup_enable();
extern  void	sup_disable();
extern  void	sup_on();
extern  void	sup_off();
extern  void	sup_set_channel(int chn);

#endif/*__SUPFUNC_*/

