#ifndef	__DVDDSP_H
#define	__DVDDSP_H

//#define	DVDDSP_busy()	((regs0->dvddsp_function & (1<<15)))

// || regs0->dvddsp_blocklength)

//DVD_SERVO
#ifdef DVD_SERVO
extern UINT16 dvddsp_sw_busy;
#define	DVDDSP_busy()	(dvddsp_sw_busy)
#else
#define	DVDDSP_busy()	((regs0->dvddsp_function & (1<<15)))
#endif

#define DRQ_BIT()	((regs0->dvddsp_function & (1<<3)))	
#define BSY_BIT()	((regs0->dvddsp_function & (1<<7)))	
#define CHECK_BIT()	((regs0->dvddsp_function & (1<<0)))	

#ifdef DVD_SERVO
  extern UINT8 cIDEStatus;
  #define atapi_status() cIDEStatus
#else
  #define atapi_status() (regs0->dvddsp_function)
#endif

#define BIT_DRQ  (1<<3)
#define BIT_BSY  (1<<7)
#define BIT_CHECK (1<<0)
#define BIT_DRDY (1<<6)
#define BIT_DSC (1<<4)		

#endif/*__DVDDSP_H*/

