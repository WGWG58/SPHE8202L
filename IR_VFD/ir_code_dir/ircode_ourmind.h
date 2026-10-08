#ifndef __IRCODE_N700_H
#define	__IRCODE_N700_H

#define _IRCODE_INC_V //kenny add it 891004
#define	IR_NEC
#define IR_ADDR_PATT	0x00ff
#include "irconfig.h"

#define IR_RETURN               0x88
#define IR_EJECT                0x20
#define IR_STOP                 0xa9
#define IR_POWER                0x08    //No POWER button in NINTAUS_DVD, Jeff 20020524
#define IR_VOLUME_UP            0x10
#define IR_VOLUME_DOWN          0xa0


#endif/*__IRCODE_N700_H*/
