#ifndef __IRCODE_DESAY_H
#define	__IRCODE_DESAY_H

#define _IRCODE_INC_V //kenny add it 891004
//#define	IR_NEC
#define	IR_PHILIPS
#define IR_ADDR_PATT	0x0011
#define IR_ADDR_PATT2	0x001f
#define IR_ADDR_PATT3	0x0051
#define IR_ADDR_PATT4	0x005f
#include "irconfig.h"

#define IR_RETURN		0xf0
#define IR_EJECT		0xb8
#define IR_STOP			0x20
#define IR_POWER		0xff    //No POWER button in NINTAUS_DVD, Jeff 20020524
#define IR_VOLUME_UP	0x98
#define IR_VOLUME_DOWN	0xf8


#endif/*__IRCODE_DESAY_H*/
