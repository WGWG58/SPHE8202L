#ifndef	__VFDFUNC_H
#define	__VFDFUNC_H

#include "vfd.h"
//#include "vfd_7seg.h"  //jjding 2000/11/09
//#include "user_init.h"

//#define  HT1621_PANNEL     //zyf 2000/10/09
/*
** VARIABLE
** vfd_mem[]
**
** DESCRIPTION
** VFD memory content
*/
#ifdef ALCO_PORTABLE
#define DISABLE_VFD 
#endif

//#define VFD_ENABLE zyf mark it 2000/11/3
#define VFD_READ        0
#define VFD_WRITE       1
#define VFD_WRITE_BUSY  2
#define VFD_READ_BUSY   3
//#define VFD_READ_BUSY   4 //terry,2002/6/27 11:04PM

/** zyf 2000/11/02 add ***/
#ifdef  HT1621_PANNEL
#define	VFD_MEM_LEN	16
#else
#define	VFD_MEM_LEN	50
#endif 

BYTE	vfd_mem[VFD_MEM_LEN];

/*
** LED_table
**
**  VFD_NEC16312 LCD PORT DATA SET
*/   
#ifdef VFD_EXTERN_KEY  //zyf 2000/11/17
static const   BYTE LED_table[4]  = {0x0e,0x0d,0x0b,0x07};
#endif 

//#endif


void	reset_vfd(void);
void	erase_vfd_mem(void);
void	erase0_vfd_mem(void);

void vfd_dot_pgm(BYTE,UINT16); //zhyf 1-2-17 12:01 for JINZH        

//int	polling_vfd(void);
void	polling_vfdr(void);

#ifdef PDVD_USE_IO_SCAN_KEY//Jack clear warning msg 05/09/29
void check_portable_key(void);
#endif
#ifdef PORTABLE_DVD//Jack clear warning msg 05/09/29
void check_portable_gpio(void);
#endif
#ifdef  SUPPORT_DVD_POWER_ONOFF
void  dvd_power_onoff(BYTE  onoff);
#endif

void	vfd_dot(UINT32, UINT32);
void	vfd_set_7seg(UINT32, UINT32);
void    vfd_prog_dis(BYTE,UINT16);   //zyf 2000/10/03
void	__vfd_set_pause(void);
void	__vfd_set_open(void);
void	__vfd_set_close(void);
void	__vfd_set_play(void);
void	__vfd_set_step(void);
void	__vfd_set_read(void);
void	__vfd_set_pgm(BYTE);
void    vfd_set_nodisk(void);

void vfd_set_p3disc(void);     //zhyf 1-2-7 18:48 for jinzheng

#ifdef	DISABLE_VFD
#define	vfd_set_pause()
#define	vfd_set_step()
#define	vfd_set_open()
#define	vfd_set_close()
#define	vfd_set_play()
#else
#define	vfd_set_pause()	__vfd_set_pause()
#define	vfd_set_step()	__vfd_set_step()
#define	vfd_set_open()	__vfd_set_open()
#define	vfd_set_close()	__vfd_set_close()
#define	vfd_set_play()	__vfd_set_play()
#define vfd_set_read()  __vfd_set_read()
#endif

#if	0
#define	__vfd_set_pp(pp)	
#define	__vfd_set_mm(mm)
#define	__vfd_set_ss(ss)
#define	__vfd_set_dot(p)
#define	__vfd_reset_dot(p)
#define	__vfd_toggle_dot(p)

#else
#define	__vfd_set_pp(pp)	vfd_set_7seg(0,(pp))
#define	__vfd_set_mm(mm)	vfd_set_7seg(1,(mm))
#define	__vfd_set_ss(ss)	vfd_set_7seg(2,(ss))
#define __vfd_set_tt(trk)   vfd_set_7seg(3,(trk))
#define	__vfd_set_dot(p)	vfd_dot(0,p)
#define	__vfd_reset_dot(p)	vfd_dot(1,p)
#define	__vfd_toggle_dot(p)	vfd_dot(2,p)
#endif

#ifdef	DISABLE_VFD
#define vfd_set_tt(trk)//kenny add it 891129
#define	vfd_set_pp(pp)
#define	vfd_set_mm(mm)
#define	vfd_set_ss(ss)
#define	vfd_set_dot(p)
#define	vfd_reset_dot(p)
#define	vfd_toggle_dot(p)
#define	vfd_set_pgm(p)//kenny add it 8911129

#else
							   /*
							   #define vfd_set_tt(trk)     (__vfd_set_tt(trk),polling_vfd())
							   #define	vfd_set_pp(pp)		(__vfd_set_pp(pp), polling_vfd())
							   #define	vfd_set_mm(mm)		(__vfd_set_mm(mm), polling_vfd())
							   #define	vfd_set_ss(ss)		(__vfd_set_ss(ss), polling_vfd())
							   #define	vfd_set_dot(p)		(__vfd_set_dot(p), polling_vfd())
							   #define	vfd_reset_dot(p)	(__vfd_reset_dot(p), polling_vfd())
							   #define	vfd_toggle_dot(p)	(__vfd_toggle_dot(p), polling_vfd())
							   #define	vfd_set_pgm(p)      (__vfd_set_pgm(p), polling_vfd())
*/
#define vfd_set_tt(trk)     __vfd_set_tt(trk)
#define	vfd_set_pp(pp)		__vfd_set_pp(pp)
#define	vfd_set_mm(mm)		__vfd_set_mm(mm)
#define	vfd_set_ss(ss)		__vfd_set_ss(ss)
#define	vfd_set_dot(p)		__vfd_set_dot(p)
#define	vfd_reset_dot(p)	__vfd_reset_dot(p)
#define	vfd_toggle_dot(p)	__vfd_toggle_dot(p)
#define	vfd_set_pgm(p)      __vfd_set_pgm(p)
#endif

#endif /* __VFDFUNC_H */
