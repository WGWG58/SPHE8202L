#ifndef __CPPM_H
#define __CPPM_H

#include "types.h"

#ifndef WORD32
#define WORD32  UINT32
#endif

void C2_D(const BYTE key[7], const WORD32 *p, WORD32 *q);
void C2_E(const BYTE key[7], const WORD32 *p, WORD32 *q);
void C2_G(const BYTE key[7], const WORD32 *p, WORD32 *q);

#endif

