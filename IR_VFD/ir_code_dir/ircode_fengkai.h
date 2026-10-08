#ifndef __IRCODE_SVA_H
#define	__IRCODE_SVA_H

#define _IRCODE_INC_V //kenny add it 891004
#define	IR_NEC
#define IR_ADDR_PATT	0x00ff
#include "irconfig.h"

#define IR_RETURN	0x70
#define IR_EJECT	0x00
#define IR_STOP		0xEA
#define IR_POWER	0x30    //No POWER button in NINTAUS_DVD, Jeff 20020524
#define IR_VOLUME_UP	0x0A
#define IR_VOLUME_DOWN	0x8A

#endif/*__IRCODE_SVA_H*/
