#ifndef __SPIF_H
#define __SPIF_H

#include "types.h"

unsigned spiflash_read_id(void);
void spiflash_write_enable(void);
void spiflash_write_disable(void);
void spiflash_write_status(unsigned);
unsigned spiflash_read_status(void);
void spiflash_program(UINT8 *src, unsigned address, unsigned len);
void spiflash_fast_read(UINT8 *dst, unsigned address, unsigned len);

#endif/*__SPIF_H*/

