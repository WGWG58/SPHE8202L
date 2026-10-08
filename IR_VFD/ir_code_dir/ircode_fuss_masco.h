#ifndef __IRCODE_FUSS_MASCO_H
#define __IRCODE_FUSS_MASCO_H

/*
** MTK 42 key
**
** TYPE:    NEC
** ADDR:    0xff
*/

#define _IRCODE_INC_V //kenny add it 891004
#define IR_NEC
#define IR_ADDR_PATT    0xc2e2
#include "irconfig.h"

#define IR_RETURN       0x88//0x0a//0xf0//nono 20020710
#define IR_EJECT        0x18//0xb8
#define IR_STOP         0x20
#define IR_VOLUME_UP    0x90//0x98
#define IR_VOLUME_DOWN  0x12//0xf8
#define IR_POWER    0x38

#endif/*__IRCODE_FUSS_MASCO_H*/
