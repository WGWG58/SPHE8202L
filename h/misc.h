#ifndef __MISC_H
#define __MISC_H

#include "types.h"
#include "global.h"

#ifdef __BORLANDC__
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#include <fcntl.h>
#include <io.h>


#ifdef NPRINTF
#define printf(f, a...) do {} while (0)
#else
#endif /* NPRINTF */

#ifdef NEPRINTF
#define eprintf(f, a...) do {} while (0)
#else
#define eprintf	printf
#endif /* NEPRINTF */


#endif /* __BORLANDC__ */

#ifdef __EMU__
#include "config.h"
#include "regmap.h"
#include "epp.h"
#include "sio.h"

#define  CONFIG   CONFIG_DVD
#include "memmap.h"

int mon_read(char *p);
int getch(void);
void delay(unsigned);
extern UINT8 write_buf[128];

#ifdef NPRINTF
//#define printf(f, a...) do {} while (0)
/*#else
#  define printf(f, a...) \
{ \
psprintf(write_buf, ## f, ## a); \
epp_write_wait(write_buf); \
} */
#endif /* NPRINTF */

#ifdef NEPRINTF
#define eprintf(f, a...) do {} while (0)
#else
#define eprintf	printf
#endif /* NPRINTF */

#endif /* __EMU__ */

#ifdef __SIM__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include "image.h"
#include "fs.h"
#include "navdata.h"
#include "nav.h"

int getch(void);

#ifdef NPRINTF
#define printf(f, a...) do {} while (0)
#else
#endif /* NPRINTF */

#ifdef NEPRINTF
#define eprintf(f, a...) do {} while (0)
#else
#efine eprintf	printf
#endif /* NPRINTF */



#endif /* __SIM__ */


// for all

void print_block(UINT8 *, int);

UINT16 udf_crc(UINT8 *, UINT32, UINT16);

//void Halt_ok(void);
//void Halt_fail(void);

#endif /* __MISC_H */

