#ifndef __IF_FILTER_H
#define __IF_FILTER_H

#include "user_init.h"

#define IR_FILTER_REJECT			0x01
#define IR_FILTER_NOP       		0x02
#define IR_FILTER_EXCEPTION		0x03

int	(*pfnIR_IRFilter1)(BYTE);
int IRFilter_No_Pass(BYTE rx);
int IRFilter_All_Pass(BYTE rx);


#ifdef SUPPORT_MP3_ENCODER
int IRFilter_MP3_ENCODER(BYTE rx);
#endif

#endif		//__IF_FILTER_H

