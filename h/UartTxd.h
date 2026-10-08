#ifndef __UARTCOMM_H
#define __UARTCOMM_H
#include "emuiodrv.h"

#define UART_WRITE_WAIT_SLOW    20000
#define	UART_WRITE_WAIT_MAX     10000

#ifdef EMUIO_UART1

#define IsUARTRxEmpty()          (!UART1_rx_rdy())
#define UART_GETC()              (regs0->uart1_data)
#define IsUARTTxFull()           (is_uart1_fifo_full())
#define IsUARTTxEmpty()          (is_uart1_fifo_empty())
#define UART_PUTC(c)             (write_uart1(c))
#define UART_PUTC_EXACT(c)       (write_uart1_exact(c)) 

#else

#define IsUARTRxEmpty()          (!UART0_rx_rdy())
#define UART_GETC()              (regs0->uart0_data)
#define IsUARTTxFull()           (is_uart0_fifo_full())
#define IsUARTTxEmpty()          (is_uart0_fifo_empty())
#define UART_PUTC(c)             (write_uart0(c))
#define UART_PUTC_EXACT(c)       (write_uart0_exact(c)) 

#endif

#define	IO_WAIT()	\
	do {					\
		  int timeout = UART_WRITE_WAIT_MAX;	\
		  do {					\
		  if (!IsUARTTxFull()) break;		\
		  } while (--timeout>0);		\
	} while (0)

#define	IO_WAIT_EMPTY()	\
	do {					\
		  int timeout = UART_WRITE_WAIT_MAX;	\
		  do {					\
		  if (IsUARTTxEmpty()) break;		\
		  } while (--timeout>0);		\
	} while (0)

#define	IO_PUTC(c)	\
  		do {					\
		UART_PUTC(c);				\
		if ((c)==0x0a) UART_PUTC(0x0d);	\
		} while (0)

#define	IO_PUTC_WAIT(c)	\
	do {					\
		  IO_WAIT();				\
		  UART_PUTC(c);				\
		  if ((c)==0x0a) {			\
		  IO_WAIT();				\
		  UART_PUTC(0x0d);			\
		  }					\
	} while (0)

#define	IO_PUTC_EXACT(c) \
	do {					\
		  UART_PUTC_EXACT(c);			\
		  if ((c)==0x0a) {			\
		  IO_WAIT();				\
		  EPP_PUTC_EXACT(0x0d);		\
		  }					\
	} while (0)


#define UART_REV_MAX_BYTE 16
#define UART_TXD_MAX_BYTE 16              //
#define COMMAND_START	0xCC//'X'
#define COMMAND_END	0xDD//	'Z'	
#ifndef NEW_UART_COMMAND        //for fuss new uart command
//define Ca720 to 8051 command
#define POWER_ON                0x01
#define MUTE_AMP                0x02
#define AV_MODE                 0x03
#define POWER_OFF               0x04
#define TOTAL_VOL               0x05
#define FRONT_VOL               0x06
#define CENT_VOL                0x07
#define REAR_VOL                0x08
#define FRONT_BALANCE           0x09
#define REAR_BALANCE            0x0A
#define QS_EFFECT               0x0B
#define TREBLE_EFFECT           0x0C
#define BASS_EFFECT             0x0D
#define AC3_STATUS              0x0E
#define ERROR_720               0x7F

//define 8051 to Ca720 command
#define DIGI_ELEC_VAL           0x80
#define ELEC_VOL                0x90
#define ERROR_8051              0xFF

//define POWER ON index
#define POWER_ON_FAIL           0x00
#define POWER_ON_OK	            0x01

//define MUTE index
#define MUTE_OFF                0x00
#define MUTE_ON	                0x01

//define MODE index
#define AV1_MODE                0x00
#define AV2_MODE                0x01
#define TUNER_MODE              0x02
#define DVD_MODE                0x03

//define POWER-OFF index
#define POWER_OFF_OK            0x01

//define AC3 index
#define NOT_AC3                 0x00
#define IS_AC3                  0x01

#define VOL_MAX     15
#define VOL_MIN     0

#define QS_MAX     7
#define QS_MIN     0

#define BALANCE_MAX 3
#define BALANCE_MIN -3

#else            //it's fuss new uart command

//define Ca720 to 8051 command
#define POWER_ON                0x01
#define MUTE_AMP                0x02
#define AV1_MODE                0x03
#define AV2_MODE                0x04
#define TUNER_MODE              0x05
#define DVD_MODE                0x06
#define POWER_OFF               0x07
#define TOTAL_VOL               0x08
#define FRONT_VOL               0x09
#define CENT_VOL                0x0A
#define REAR_VOL                0x0B
#define SUBWOOFER_VOL           0x0C
#define FRONT_BALANCE_L         0x0D
#define FRONT_BALANCE_R         0x0E
#define REAR_BALANCE_L          0x0F
#define REAR_BALANCE_R          0x10
#define QS_EFFECT               0x11
#define TREBLE_EFFECT           0x12
#define BASS_EFFECT             0x13
#define VOL_DEFAULT				0x14
#define AC3_STATUS              0x15
#define ERROR_720               0x7F

//define 8051 to Ca720 command
#define DIGI_ELEC_VAL           0x80
#define ELEC_VOL                0x90
#define ERROR_8051              0xFF

//define POWER ON index
#define POWER_ON_FAIL           0x00
#define POWER_ON_OK	            0x01

//define MUTE index
#define MUTE_OFF                0x00
#define MUTE_ON	                0x01

//define MODE index
#define AV1_MODE_D              0x00
#define AV2_MODE_D              0x01
#define TUNER_MODE_D            0x02
#define DVD_MODE_D              0x03

//define POWER-OFF index
#define POWER_OFF_OK            0x01
#define VOL_DEFAULT_D			0x00
//define AC3 index
#define NOT_AC3                 0x00
#define IS_AC3                  0x01
#define VOL_MAX     0x3C
#define VOL_MIN     0x00
#define VOL_ADJUST_MAN  6
#define VOL_ADJUST_MIN  -6
#define QS_MAX     5
#define QS_MIN     0

#define BALANCE_MAX 3
#define BALANCE_MIN -3
#define MAINVOL  8
#define FRONTVOL 0
#define CENTERVOL 0
#define REARVOL   0
#define SUBWOOFERVOL 0
#define MAINBALANCE_L 0
#define MAINBALANCE_R 0
#define SURBALANCE_L  0
#define SURBALANCE_R  0
#define QSEFFECT      0
#define TREBLEVOL     0
#define BASSVOL       0

#endif           //end if fuss new uart command


#include "types.h"

int pollingUART51(void);
void do_uart_command(void);
void reset_uart(void);

void IRSwitchMode(void);
void IRSwitchVolMode(void);
void IRAdjustVol(int nUpOrDown);
#ifdef NEW_UART_COMMAND
void Set_Default_Vol(void);
#endif
void Inform_MCUOK(void);
#endif //__UARTCOMM_H
