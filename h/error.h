#ifndef	__ERROR_H
#define	__ERROR_H

#define	MAX_OVERFLOW	128
int	overflow;
int	overflow_vy[MAX_OVERFLOW];
int	overflow_cddsp_y[MAX_OVERFLOW];
int	overflow_cy[MAX_OVERFLOW];

#define	MAX_UNDERFLOW	128
int	underflow;
int	underflow_vy[MAX_UNDERFLOW];
int	underflow_cddsp_y[MAX_UNDERFLOW];
int	underflow_cy[MAX_UNDERFLOW];

#endif/*__ERROR_H*/
