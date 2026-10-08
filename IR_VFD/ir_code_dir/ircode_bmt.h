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
#define IR_ADDR_PATT    0x10ef
#include "irconfig.h"

#define IR_RETURN       0xf8//0x0a//0xf0//nono 20020710
#define IR_EJECT        0xfa//0xb8
#define IR_STOP         0xff//0x20
#define IR_VOLUME_UP    0xa8//0x98
#define IR_VOLUME_DOWN  0x38//0xf8
#define IR_POWER    0xda

#endif/*__IRCODE_FUSS_MASCO_H*/
