//2004AUDDRV oliver 20041006 for using audio driver purpose, the followings were moved to audkernel.c .h
#if 0

#ifndef __HWSETUP_H
#define	__HWSETUP_H

void    audhw_clk_init();
void	audhw_set_samp_rate(unsigned fs);
void    audhw_spdif_off(unsigned fs);

#endif/*__HWSETUP_H*/

#endif
