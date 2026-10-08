#ifndef __SUP_H
#define	__SUP_H

#define	SPU_DVD		0x00
#define	SPU_SVCD	0x01
#define	SPU_CVD		0x02

#define	SPD_HEADER_NULL		0xffff

//
// function prototypes
//
int	do_sup_header(void);
int	do_sup_body(void);

#endif/*__SUP_H*/

