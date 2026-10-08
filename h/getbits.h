#ifndef __GETBITS_H
#define __GETBITS_H


typedef	struct 
{
  // bit-level cache
  unsigned    	word;
  int         	bit_left;
} getbit_struct;

#define	GetBitInit(gb)	(gb.bit_left=0)

#endif/*__GETBITS_H*/

