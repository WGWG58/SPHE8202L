#ifndef __UARTCOMM_H
#define __UARTCOMM_H

#include "types.h"

inline int pollingUARTRx(void);

inline void DoMoveUARTRxData(void);

void DoUpgrade(BYTE* strVersion);

#endif //__UARTCOMM_H
