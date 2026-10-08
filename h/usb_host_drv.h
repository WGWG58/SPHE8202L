#ifndef _USB_HOST_DRV_H_
#define _USB_HOST_DRV_H_

#include "types.h"
 

#if  defined(SUPPORT_USB)&&defined(USB_HOST_DRV) 
  
//-------------------------------------------------------------------------------------------------
// Memory space define
//-------------------------------------------------------------------------------------------------
//set usb buffer to sdram 

#define USB_SCSI_CMD_BUF_SIZE			0x00000020    //dannykao 2005/11/16
UINT8 USB_SCSI_CMD_BUF[USB_SCSI_CMD_BUF_SIZE];
//#define USB_SCSI_CMD_BUF_POINTER		(SDRAM_BASE_UNCACHED + USB_YA*1024) 		
#define USB_SCSI_CMD_BUF_POINTER		((UINT32)USB_SCSI_CMD_BUF) 		

//#define USB_CSW_BUF_POINTER				(USB_SCSI_CMD_BUF_POINTER + USB_SCSI_CMD_BUF_SIZE)
//#define USB_CSW_BUF_SIZE				0x00000010 
//UINT8 USB_CSW_BUF[USB_CSW_BUF_SIZE];
//#define USB_CSW_BUF_POINTER				((UINT32)USB_CSW_BUF)

//-------------------------------------------------------------------------------------------------
// Global variables declaration
//-------------------------------------------------------------------------------------------------
#define USB_PLUG_OUT_ERROR      0xFF    
 
#define PID_SETUP	0x0d		// Setup token: 1101b.
#define PID_OUT		0x01		// Out token  : 0001b.
#define PID_IN		0x09		// IN token   : 1001b.

#define USB_TURNAROUND_TIMEOUT_ERR     1000
#define USB_CRC16_ERR                  1001
#define USB_PID_ERR                    1002
#define USB_BIT_STUFFING_ERR           1003
#define USB_STALL_ERR			       1004
#define USB_SHORT_PACKET_ERR           1005          
 
#define sizeOfCBW    31
#define sizeOfCSW    13 
//-------------------------------------------------------------------------------------------------
//  USB SIMPLY HOST REGISTER
//-------------------------------------------------------------------------------------------------
#ifdef	IC_1002
	#define USB_HOST_MODE_SELECTOR			0xBC020080

	#define USB_HOST_DRV_REG_BASE_ADR		0xbc020280
	#define	USB_HOST_DRV_WTPORT				0xbc020178
	#define	USB_HOST_DRV_RDPORT				0xbc02017c
	
	#define USB_HOST_VERSION				0x00 
	#define USB_HOST_CTL					0x01
	#define USB_HOST_TRANS_PARA				0x02  
	#define USB_HOST_TRANS_LENGTH			0x03
	#define USB_HOST_PORT_CTL				0x04 
	#define USB_HOST_SOF_CTL				0x05 
	#define USB_HOST_INTERRUPT_STATUS		0x08 
	#define USB_HOST_INTERRUPT_ENABLE		0x09  
	#define USB_HOST_TRANS_STATUS			0x0A
	
	#define USB_HOST_MODE					0
	#define USB_DEVICE_MODE					1
	
	#define USB_HOST_SOF_ON					0x00001000
	
	#define USB_HOST_PORT_RESET_DONE		0x00
	#define USB_HOST_PORT_RESET				0x01
	#define USB_HOST_PORT_FORCE_FULL_SPEED	0x02
	#define USB_HOST_PORT_RESET_FORCE_FULL	0x03
	#define USB_HOST_PORT_IS_FULL_SPEED		0x10
#elif	defined(IC_8202L)
	#define USB_HOST_DRV_REG_BASE_ADR	0xbc020280
	#define	USB_HOST_DRV_WTPORT			0xbc020178
	#define	USB_HOST_DRV_RDPORT			0xbc02017c

	#define USB_HOST_VERSION			0xC00
	#define USB_HOST_CTL				0xC01
	#define USB_HOST_TRANS_PARA			0xC02
	#define USB_HOST_TRANS_LENGTH		0xC03
	#define USB_HOST_PORT_CTL			0xC04
	#define USB_HOST_SOF_CTL			0xC05
	#define USB_HOST_INTERRUPT_STATUS	0xC08
	#define USB_HOST_INTERRUPT_ENABLE	0xC09
	#define USB_HOST_TRANS_STATUS		0xC0A
	
	#define USB_DEVICE_MODE				0
	#define USB_HOST_MODE				1
#else
	#define USB_HOST_DRV_REG_BASE_ADR	0xbc020000
	
	#define USB_HOST_VERSION			0xC00
	#define USB_HOST_CTL				0xC01
	#define USB_HOST_TRANS_PARA			0xC02
	#define USB_HOST_TRANS_LENGTH		0xC03
	#define USB_HOST_PORT_CTL			0xC04
	#define USB_HOST_SOF_CTL			0xC05
	#define USB_HOST_INTERRUPT_STATUS	0xC08
	#define USB_HOST_INTERRUPT_ENABLE	0xC09
	#define USB_HOST_TRANS_STATUS		0xC0A
	
	#define USB_DEVICE_MODE				0
	#define USB_HOST_MODE				1
#endif	// IC_8202L

#define USB_CTL_REG                          20

#define USB_HOST_DMA_TX_ADDR                 24
#define USB_HOST_DMA_TX_LEN                  25
#define USB_HOST_DMA_RX_ADDR                 26
#define USB_HOST_DMA_RX_LEN                  27
#define USB_HOST_DMA_CSR                     28 

#define USB_HOST_DRV_DATA_PORT            0x400	// should be redirected to UHCI_DATA_WTPORT, UHCI_DATA_RDPORT


#define reset_usb_host_hw()            usb_host_drv_reg_wr(USB_HOST_CTL,0x04)   
#define usb_host_transaction_go()      usb_host_drv_reg_wr(USB_HOST_CTL,0x01) 
#define get_usb_host_version()         usb_host_drv_reg_rd(USB_HOST_VERSION)     
//-------------------------------------------------------------------------------------------------
// Local function declaration
//-------------------------------------------------------------------------------------------------
extern void    usb_host_drv_reg_wr( UINT32 ,UINT32 );
extern UINT32  usb_host_drv_reg_rd( UINT32  );
extern void    set_usb_mode_select(UINT32 );
extern void    set_usb_host_trans_para(UINT32 ,UINT32 ,UINT32 ,UINT32 );
extern void    set_usb_host_trans_len(UINT32 );
extern UINT32  set_usb_host_bus_reset();
extern void    set_usb_dma_Tx_addr_and_len(UINT32 ,UINT32 );
extern void    set_usb_dma_Rx_addr_and_len(UINT32 ,UINT32 );
extern UINT32  usb_Tx_dma_start();
extern UINT32  usb_Rx_dma_start();
extern void    read_usb_fifo_data_port(UINT8 *,UINT32 );
extern void    write_usb_fifo_data_port(UINT8 *,UINT32 );
extern void    usb_host_drv_hw_Init();

extern UINT32  usb_host_drv_bulkXfer(BYTE  , BYTE  , BYTE  , BYTE  , BYTE * , BYTE * , BYTE * );
extern UINT32  usbXfer (BYTE  , BYTE  , BYTE  , BYTE  , BYTE  , WORD  , BYTE * );
extern UINT32  uhci_PlugInOutDetect(void);
extern void    usb_host_init();
extern void    uhci_ErrorProcess(void);

#if 1//def SUPPORT_MP3_ENCODER
extern UINT32 usbXfer_nonBlock (BYTE deviceAddr, BYTE endpoint, BYTE pid, BYTE toggle, BYTE payload, WORD wLen, BYTE *buffer);
#endif

#endif  //#if  defined(SUPPORT_USB)&&defined(USB_HOST_DRV) 

extern void    uhci_USBISR (void); 
extern UINT32 uhci_slaveDetect(void);


#endif //_USB_HOST_DRV_H_
