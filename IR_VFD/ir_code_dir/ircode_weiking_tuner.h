#ifndef __IRCODE_N700_H
#define	__IRCODE_N700_H

#define _IRCODE_INC_V //kenny add it 891004
#define	IR_NEC
#define IR_ADDR_PATT	0x00ff
#include "irconfig.h"

#define IR_RETURN		0x60
#define IR_EJECT		0x80
#define IR_STOP			0xea
#define IR_POWER		0xff    //No POWER button in NINTAUS_DVD, Jeff 20020524
#define IR_VOLUME_UP	0x4a
#define IR_VOLUME_DOWN	0xca


#endif/*__IRCODE_N700_H*/
