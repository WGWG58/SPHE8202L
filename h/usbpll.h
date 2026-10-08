#ifndef __USBPLL_H
#define __USBPLL_H
//
// USBPLL configuration
//
extern  set_usbpll_reg(unsigned s, unsigned ns);

#define NSMN(m,n)   ((((m)-1)<<3)|(((n)-1)<<0))
#define NS_30       NSMN(6,5)
#define NS_25       NSMN(5,5)
#define NS_18       NSMN(3,6)
#define NS_16       NSMN(4,4)
#define NS_9        NSMN(3,3)
#define NS_8        NSMN(4,2)
#define NS_4        NSMN(2,2)
#define NS_2        NSMN(2,1)
#define NS_1        NSMN(1,1)

//
// set_usbpll_reg(s,ns)     fosc/N(s) = 3mhz = fclkx2/2/M(ns)
//
#define set_usbpll_6mhz()   set_usbpll_reg(NS_9, NS_2)      // 27/9*2
#define set_usbpll_12mhz()  set_usbpll_reg(NS_9, NS_4)      // 27/9*4
#define set_usbpll_24mhz()  set_usbpll_reg(NS_9, NS_8)      // 27/9*8
#define set_usbpll_48mhz()  set_usbpll_reg(NS_9, NS_16)     // 27/9*16
#define set_usbpll_54mhz()  set_usbpll_reg(NS_9, NS_18)     // 27/9*18=54
#define set_usbpll_75mhz()  set_usbpll_reg(NS_9, NS_25)     // 27/9*25=75
#define set_usbpll_90mhz()  set_usbpll_reg(NS_9, NS_30)     // 27/9*30=90

#endif/*__USBPLL_H*/

