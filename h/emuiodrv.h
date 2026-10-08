#ifndef	__EMUIODRV_H
#define	__EMUIODRV_H

#include "config.h"

#ifdef DVD728
#define EMUIO_UART0
#else
#define EMUIO_UART1
#endif

#ifdef  EMUIO_UART1
#include "io_uart1.h"
#elif	defined(EMUIO_UART0)
#include "io_uart0.h"
#else
#include "io_epp.h"
#endif

#endif
