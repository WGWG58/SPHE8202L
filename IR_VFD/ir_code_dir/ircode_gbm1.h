#ifndef __IRCODE_N700_H
#define	__IRCODE_N700_H

#define _IRCODE_INC_V //kenny add it 891004
#define	IR_NEC
#define IR_ADDR_PATT	0x04fb
#include "irconfig.h"

#define IR_RETURN		0xff//
#define IR_EJECT		0x58//0x1a
#define IR_STOP			0x8a//0x5d
#define IR_POWER		0x70//0x0e    //No POWER button in NINTAUS_DVD, Jeff 20020524
#define IR_VOLUME_UP	0xaa//0x55
#define IR_VOLUME_DOWN	0xa8//0x15


#endif/*__IRCODE_N700_H*/
