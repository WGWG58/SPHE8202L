////////////////////////////////////////////////////////////////////////////////
// SUNPLUS---WORLDPLUS
////////////////////////////////////////////////////////////////////////////////
// File:		host_811.h
// Purpose:	    SPHE8200 firmware to master SL811 Embedded Host. 
//              Contains SL811-related control firmware. 
//              
// H/W Target:  SL811HST + SPHE8200 DVD SYSTEM
// IMPORTANT:  
//              the hardware could sustain USB host and USB slave. 
// Creator:     Liweihua and Zhaoyanhua 2003-9-20
// Updated by Liweihua 2003-12-19
////////////////////////////////////////////////////////////////////////////////
#ifndef   HOST_811_H
#define   HOST_811_H

//-----------------------------------------------------------------------------
// Constant Defines
//-----------------------------------------------------------------------------
#define	TRUE 	1
#define FALSE	0
#define USB_ADDR      0x02

#define ISO_BIT     0x10

/*-------------------------------------------------------------------------
 * SL811H Register Control memory map
 * --Note: 
 *      --SL11H only has one control register set from 0x00-0x04
 *      --SL811H has two control register set from 0x00-0x04 and 0x08-0x0c
 *------------------------------------------------------------------------*/
#define EP0_Buf		    0x10	// define start of EP0 64-byte buffer
#define EP1_Buf		    0x50	// define start of EP1 64-byte buffer

#define EP0Control       0x00
#define EP0Address     0x01
#define EP0XferLen      0x02
#define EP0Status        0x03
#define EP0PIDEP         0x03
#define EP0Counter      0x04
#define EP0USBAddr      0x04

#define EP1Control       0x08
#define EP1Address      0x09
#define EP1XferLen       0x0a
#define EP1Status         0x0b
#define EP1PIDEP         0x0b
#define EP1Counter       0x0c
#define EP1USBAddr      0x0c

#define CtrlReg         0x05
#define IntEna          0x06
                               // 0x07 is reserved
#define IntStatus       0x0d
#define cDATASet      0x0e
#define cSOFcnt         0x0f   // Master=1 Slave=0, D+/D-Pol Swap=1 0=not [0-5] SOF Count 
                               // 0xAE = 1100 1110
                               // 0xEE = 1110 1110

//Interrupt Status Mask
#define USB_A_DONE		0x01
#define USB_B_DONE		0x02
#define BABBLE_DETECT	0x04
#define INT_RESERVE		0x08
#define SOF_TIMER		0x10
#define INSERT_REMOVE	0x20
#define USB_RESET		0x40
#define USB_DPLUS		0x80
#define INT_CLEAR		0xFF//clear the bit to set "1"
    


//EP0 Status Mask
#define EP0_ACK			0x01	// EPxStatus bits mask during a read
#define EP0_ERROR		0x02
#define EP0_TIMEOUT		0x04
#define EP0_SEQUENCE	0x08
#define EP0_SETUP		0x10
#define EP0_OVERFLOW	0x20
#define EP0_NAK			0x40
#define EP0_STALL		0x80

// drive error
#define USB_STALL_ERR    -501
#define USB_NAK_ERR       -502
#define USB_CONTINAK_ERR  -503

/*-------------------------------------------------------------------------
 * SL811H definition
 *-------------------------------------------------------------------------
 */

                           // USB-A, USB-B Host Control Register [00H, 08H]
                           // Pre  Reserved
                           //  DatT Dir [1=Trans, 0=Recv]
                           //   SOF Enable
                           //    ISO  Arm 
#define DATA0_WR   	0x07   // 0000 0111 (      Data0 +       OUT + Enable + Arm)
#define sDATA0_WR  	0x27   // 0010 0111 (      Data0 + SOF + OUT + Enable + Arm)
#define pDATA0_WR   0x87   // 1000 0111 (Pre + Data0 +       OUT + Enable + Arm)
#define psDATA0_WR 0xA7   // 1010 0111 (Pre + Data0 + SOF + OUT + Enable + Arm)

#define DATA0_RD      0x03   // 0000 0011 (      Data0 +       IN +  Enable + Arm)
#define sDATA0_RD    0x23   // 0010 0011 (      Data0 + SOF + IN +  Enable + Arm)
#define pDATA0_RD    0x83   // 1000 0011 (Pre + Data0 +       IN +  Enable + Arm)
#define psDATA0_RD  0xA3   // 1010 0011 (Pre + Data0 + SOF + IN +  Enable + Arm)

#define PID_SETUP   0xD0 
#define PID_IN      0x90
#define PID_OUT     0x10

/*-------------------------------------------------------------------------
 * Function Protocol
 *-------------------------------------------------------------------------
 */
void sl811h_init(void);
int   slave_detect(void);
int   speed_detect(void);
inline BYTE SL811Read(register BYTE a);
inline void SL811Write(register BYTE a,register  BYTE d);
inline BYTE SL811Read_DATA(void);
inline void SL811Write_DATA(register  BYTE d);
inline void SL811BufRead(register UINT8 addr, register UINT8 *s, register UINT8 c);
inline void SL811BufWrite(register UINT8 addr, register UINT8 *s, register UINT8 c);
void CardReset();
INT32 usbXfer(UINT8 usbaddr, UINT8 endpoint, UINT8 pid, UINT8 iso, UINT8 Payload, UINT16 wLen, UINT8 *buffer);
int    Slave_Detach(void);
 
#endif //end HOST_811_H
