#ifndef	__INTDEF_H
#define	__INTDEF_H

// 2001.02.01 updated from glchen
#include "config.h"

// INTERRUPT CONTROLLER #0
#ifdef DVD728
	// 728

	// INTERRUPT CONTROLLER #0
	#define	_INTNUM_DECERR				15
	#define	_INTNUM_LPT					14
	#define	_INTNUM_TIMER1				13
	#define	_INTNUM_TIMER0				12
	#define	_INTNUM_PIC_END				11
	#define	_INTNUM_FIELD_END			10
	#define	_INTNUM_FIELD_START			9
	#define	_INTNUM_H_PIO_INT			8	
	#define	_INTNUM_UART1_INT			7
	#define	_INTNUM_UART0_INT			6
	#define	_INTNUM_RI_WATCHDOG			5
	 #ifdef SPHE1000
	#define _INTNUM_USB					4
	#define _INTNUM_DSP_INT2			3
	#define _INTNUM_DISPATCH_4189		2
	#define _INTNUM_DISPATCH_MIPZ		1
	 #else
	#define	_INTNUM_SRV_INT3			4		// Servo Interrupt
	#define	_INTNUM_SRV_INT2			3		// Servo Interrupt
	#define	_INTNUM_SRV_INT1			2		// Servo Interrupt
	#define	_INTNUM_SRV_INT0			1		// Servo Interrupt
	 #endif
	#define	_INTNUM_DSP_INT				0		

	#define INTR_DECERR					(1<<_INTNUM_DECERR)
	#define	INTR_LPT					(1<<_INTNUM_LPT)
	#define INTR_TIMER1					(1<<_INTNUM_TIMER1)
	#define INTR_TIMER0					(1<<_INTNUM_TIMER0)
	#define INTR_PIC_END				(1<<_INTNUM_PIC_END)
	#define INTR_FIELD_END				(1<<_INTNUM_FIELD_END)
	#define INTR_FIELD_START			(1<<_INTNUM_FIELD_START)
	#define INTR_H_PIO_INT				(1<<_INTNUM_H_PIO_INT)
	#define INTR_UART0_INT				(1<<_INTNUM_UART0_INT)
	#define INTR_UART1_INT				(1<<_INTNUM_UART1_INT)
	#define INTR_RI_WATCHDOG			(1<<_INTNUM_RI_WATCHDOG)
	 #ifdef SPHE1000
	#define INTR_USB					(1<<_INTNUM_USB)
	#define INTR_DSP_INT2				(1<<_INTNUM_DSP_INT2)
	#define INTR_DISPATCH_4189			(1<<_INTNUM_DISPATCH_4189)
	#define INTR_DISPATCH_MIPZ			(1<<_INTNUM_DISPATCH_MIPZ)
	 #else
	#define INTR_SRV_INT3				(1<<_INTNUM_SRV_INT3)
	#define INTR_SRV_INT2				(1<<_INTNUM_SRV_INT2)
	#define INTR_SRV_INT1				(1<<_INTNUM_SRV_INT1)
	#define INTR_SRV_INT0				(1<<_INTNUM_SRV_INT0)
	 #endif
	#define INTR_DSP_INT 				(1<<_INTNUM_DSP_INT)
	

	// INTERRUPT CONTROLLER #1
	 #ifdef SPHE1000
	#define	_INTNUM1_IOP_MIPZ			15
	#define	_INTNUM1_PCI1				14
	#define	_INTNUM1_PCI0				13
	#define	_INTNUM1_DEMUX1				12
	#define	_INTNUM1_DEMUX0				11
	 #else
	#define	_INTNUM1_RISC_INT4			15
	#define	_INTNUM1_RISC_INT3			14
	#define	_INTNUM1_RISC_INT2			13
	#define	_INTNUM1_RISC_INT1			12
	#define	_INTNUM1_RISC_INT0			11
	 #endif
	#define	_INTNUM1_H_DEVICE_INT		9
	#define	_INTNUM1_LSWITCH_INTR_FLAG	8
	#define	_INTNUM1_SD_INT				7
     #ifdef SPHE8202	
	#define	_INTNUM1_USB				6
	#define	_INTNUM1_FM				5
     #else	
	#define	_INTNUM1_TDM_TX				6
	#define	_INTNUM1_TDM_RX				5
     #endif	
	#define	_INTNUM1_TIMERW				4
	#define	_INTNUM1_TIMER2A			3
	#define	_INTNUM1_TIMER2B			2
	#define	_INTNUM1_TIMER3A			1
	#define	_INTNUM1_TIMER3B			0

	 #ifdef SPHE1000
	#define	INTR1_IOP_MIPZ				(1<<_INTNUM1_IOP_MIPZ)
	#define	INTR1_PCI1					(1<<_INTNUM1_PCI1)
	#define	INTR1_PCI0					(1<<_INTNUM1_PCI0)
	#define	INTR1_DEMUX1				(1<<_INTNUM1_DEMUX1)
	#define	INTR1_DEMUX0				(1<<_INTNUM1_DEMUX0)
	 #else
	#define INTR1_RISC_INT4				(1<<_INTNUM1_RISC_INT4)
	#define INTR1_RISC_INT3				(1<<_INTNUM1_RISC_INT3)
	#define INTR1_RISC_INT2				(1<<_INTNUM1_RISC_INT2)
	#define INTR1_RISC_INT1				(1<<_INTNUM1_RISC_INT1)
	#define INTR1_RISC_INT0				(1<<_INTNUM1_RISC_INT0)
	 #endif
	#define INTR1_SD       				(1<<_INTNUM1_SD_INT)
     #ifdef SPHE8202	
	#define	INTR1_USB				(1<<_INTNUM1_USB)
	#define	INTR1_FM				(1<<_INTNUM1_FM)
     #else
	#define	INTR1_TDM_TX				(1<<_INTNUM1_TDM_TX)
	#define	INTR1_TDM_RX				(1<<_INTNUM1_TDM_RX)
     #endif	
	#define	INTR1_TIMERW				(1<<_INTNUM1_TIMERW)
	#define	INTR1_TIMER2A				(1<<_INTNUM1_TIMER2A)
	#define	INTR1_TIMER2B				(1<<_INTNUM1_TIMER2B)
	#define	INTR1_TIMER3A				(1<<_INTNUM1_TIMER3A)
	#define	INTR1_TIMER3B				(1<<_INTNUM1_TIMER3B)
	#define INTR1_LSWITCH_INTR_FLAG		(1<<_INTNUM1_LSWITCH_INTR_FLAG)
	#define INTR1_H_DEVICE_INT			(1<<_INTNUM1_H_DEVICE_INT)
#else
	// 720
	#define	_INTNUM_DECERR				15
	#define	_INTNUM_EXCEPTION			14
	#define	_INTNUM_TIMER1				13
	#define	_INTNUM_TIMER0				12
	#define	_INTNUM_PIC_END				11
	#define	_INTNUM_FIELD_END			10
	#define	_INTNUM_H_DEVICE_INT		9
	#define	_INTNUM_H_PIO_INT			8	
	#define	_INTNUM_UART0_INT			7
	#define	_INTNUM_UART1_INT			6
	#define	_INTNUM_X_UNMAP_FLAG		5		// IOP un-map
	#define	_INTNUM_LSWITCH_INTR_FLAG	5
	#define	_INTNUM_UNMAP_ERROR			4		// RISC un-map
	#define	_INTNUM_RISC_INT4			4		// ext. INT4
	#define	_INTNUM_RISC_INT3			3		// ext. INT3
	#define	_INTNUM_RISC_INT2			2		// ext. INT2
	#define	_INTNUM_RISC_INT1			1		// ext. INT1
	#define	_INTNUM_RISC_INT0			0		// ext. INT0

	#define INTR_DECERR					(1<<_INTNUM_DECERR)
	#define	INTR_EXCEPTION				(1<<_INTNUM_EXCEPTION)
	#define INTR_TIMER1					(1<<_INTNUM_TIMER1)
	#define INTR_TIMER0					(1<<_INTNUM_TIMER0)
	#define INTR_PIC_END				(1<<_INTNUM_PIC_END)
	#define INTR_FIELD_END				(1<<_INTNUM_FIELD_END)
	#define INTR_H_DEVICE_INT			(1<<_INTNUM_H_DEVICE_INT)
	#define INTR_H_PIO_INT				(1<<_INTNUM_H_PIO_INT)
	#define INTR_UART0_INT				(1<<_INTNUM_UART0_INT)
	#define INTR_UART1_INT				(1<<_INTNUM_UART1_INT)
	#define INTR_X_UNMAP_FLAG			(1<<_INTNUM_X_UNMAP_FLAG)
	#define INTR_UNMAP_ERROR			(1<<_INTNUM_UNMAP_ERROR)
	#define INTR_RISC_INT4				(1<<_INTNUM_RISC_INT4)
	#define INTR_RISC_INT3				(1<<_INTNUM_RISC_INT3)
	#define INTR_RISC_INT2				(1<<_INTNUM_RISC_INT2)
	#define INTR_RISC_INT1				(1<<_INTNUM_RISC_INT1)
	#define INTR_RISC_INT0				(1<<_INTNUM_RISC_INT0)
#endif


	
#endif/*__INTDEF_H*/
