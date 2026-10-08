#ifndef	__EPP_H
#define	__EPP_H

#include "emuio.h"

#define reset_epp()		reset_io()
#define polling_epp()		polling_io()
#define epp_flush()		io_write_flush()
#define	epp_write(s)		io_write(s)
#define	epp_write_slow(s)	io_write_slow(s)
#define	epp_write_wait(s)	io_write_wait(s)

#endif
