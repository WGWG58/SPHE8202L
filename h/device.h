#ifndef __DEVICE_H
#define __DEVICE_H

#include "config.h"
#include "regmap.h"

#define setreg_intr_flag(c)         (regs0->intr_flag=(c))
#define getreg_intr_flag()          (regs0->intr_flag)

#define getreg_mc_compress()        (regs0->mc_compress)

#define setreg_timerw_ctrl(c)       (regs0->timerw_ctrl=(c))
#define setreg_timerw_cnt(c)        (regs0->timerw_cnt=(c))

// UART0
#define setreg_uart0_isc(c)         (regs0->uart0_isc=(c))
#define setreg_uart0_data(c)        (regs0->uart0_data=(c))
#define getreg_uart0_isc()          (regs0->uart0_isc)
#define getreg_uart0_data()         (regs0->uart0_data)

// UART1
#define setreg_uart1_isc(c)         (regs0->uart1_isc=(c))
#define setreg_uart1_data(c)        (regs0->uart1_data=(c))
#define getreg_uart1_isc()          (regs0->uart1_isc)
#define getreg_uart1_data()         (regs0->uart1_data)

#endif/*__DEVICE_H*/
