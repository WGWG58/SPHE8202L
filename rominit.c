#include "ver.h"
#include "load.h"

extern	int	_data[];
extern	int	_edata[];
extern	int	_data_ps[];
extern	int	_data_pe[];
extern	int	_bstart[];
extern 	int	_bend[];

extern	int	_sdram[];
extern	int	_esdram[];

extern	int	_textf_ps[];
extern	int	_textf[];
extern	int	_etextf[];

extern	void	reset_system(void);

//#define     ROMINIT_DBG     1

/*
** FUNCTION
** rominit
**
** DESCRIPTION
** Initialize memory contents that need to be initialized.
*/
void	rominit(void)
{
  int *src;
  int *dst;
  int *ending;


  /* ROM has data at end of text; copy it. */
  src    = _data_ps;
  dst    = _data;
  ending = _edata;
  do {
    *dst++ = *src++;
  } while (dst<ending);


  /* Zero out bss */
  dst    = _bstart;
  ending = _bend;
  do {
    *dst++ = 0;
  } while (dst<ending);

#ifdef SPHE1000
#ifdef LOAD_BOOTCODE
extern	int	_boot_start[];
extern 	int	_boot_end[];
extern 	int	_bstext[];
  src    = _bstext;
  dst    = _boot_start;
  ending = _boot_end;
  do {
    *dst++ = *src++;
  } while (dst<ending);
#endif // LOAD_BOOTCODE

#ifndef SINGLE_CPU
  src    = 0x88000080;
  dst    = 0x80000480;
  ending = 0x80000490;
  do {
    *dst++ = *src++;
  } while (dst<ending);
#endif // SINGLE_CPU
#endif // SPHE1000

#if 0
  //
  src    = _textf_ps;
  dst    = _textf;
  ending = _etextf;
  while (dst<ending)
  {
    *dst++ = *src++;
  }
#endif
  /*
  ** reset system interface
  */
  //reset_system();
}


void	ramfinit()
{
#if 0
  int *src;
  int *dst;
  int *ending;

  src    = _textf_ps;
  dst    = _textf;
  ending = _etextf;
  while (dst<ending)
  {
    *dst++ = *src++;
  }
#endif
}

