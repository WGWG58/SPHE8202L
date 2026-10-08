extern	char	_data[];
extern	char	_edata[];
extern	char	_data_ps[];
extern	char	_data_pe[];
extern	char	_bstart[];
extern 	char	_bend[];

extern	char	_sdram[];
extern	char	_esdram[];

#include "config.h"
#include "global.h"
#include "reset.h"

//#define     ROMINIT2_DBG        1

/*
** FUNCTION
** rominit
**
** DESCRIPTION
** Initialize memory contents that need to be initialized.
*/
void	rominit(void)
{
  char *src;
  char *dst;

  /* ROM has data at end of text; copy it. */
  src = _data_ps;
  dst = _data;
  do {
    *dst++ = *src++;
  } while (dst<_edata);

  /* Zero out bss */
  dst = _bstart;
  do {
    *dst++ = 0;
  } while (dst<_bend);
 
  /*
  ** reset system interface
  */
  reset_system();
}

