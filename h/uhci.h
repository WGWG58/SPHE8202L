#ifndef _UHCI_H_
#define _UHCI_H_

#include "types.h"
/*
 * Universal Host Controller Interface data structures and defines.
 *
 * Created by Hou-Yi Wu 11/20/2003
 */


#if  defined(SUPPORT_USB)&&defined(HOST_UHCI) 
//--------------------------------------------------------------------------------------
// New TD/QH-structure	
//-------------------------------------------------------------------------------------- 

// Here TD_TYPE = 0, QH_TYPE = 1;   
typedef enum {
	TD_TYPE, QH_TYPE
} uhci_desc_type;


/*
 * This uhci_qh structure must be aligned by 16 bytes becuase the last 4 bits of each link pointer is not used.
 */
typedef struct {
	/* Hardware fields */
	UINT32 nextQHLinkPointer;			// Next queue header link pointer.
	UINT32 elementLinkPointer;			// Element link pointer.
	UINT32 dumy1;					// This dumy is used for memory aligned. Why? In UHCI hardware the
	UINT32 dumy2;					// address of QH is available for its left 28 bits. That means the right
							// 4 bit of data is useless for it address. But These right most 4 bits
							// can point to 16 bytes of data, but each QH has only 8 bytes of data
							// In order to align the memory, we add two 4bytes of data into QH structure
							// so that each time we increment the address of qh by 1, it will increment 16 bytes.
}uhci_qh, *puhci_qh;//__attribute__((aligned(16)));				

typedef struct {
	UINT32 linkPointer;
	UINT32 controlStatus;
	UINT32 token;
	UINT32 buffer;
} uhci_td, *puhci_td;

/*
typedef struct {
	union {
		puhci_td pTD;
		puhci_qh pQH;
	}hw;

		
} uhci_qh_to_td_chain, *puhci_qh_to_td_chain;
*/

typedef struct {
	
	uhci_qh	*control_chain;
	uhci_qh	*bulk_chain;
	
//	UINT32 *lastCtrTDAddr;	
//	UINT32 *lastBlkTDAddr;
//	UINT32 *frameList;

//	uhci_qh	control_chain;
//	uhci_qh	bulk_chain;
	
	UINT32 lastCtrTDAddr;	
	UINT32 lastBlkTDAddr;
	UINT32 frameList;

	
} uhci_qh_list, *puhci_qh_list;


//-------------------------------------------------------------------------------------------------
//  IO_SPACE command registers 
//-------------------------------------------------------------------------------------------------
#define CLEAN			0x0000  // Used as clean variable to clean register.
/* (00h) USBCMD*/
#define	USBCMD			0 	/* The start address of USBCMD is 0 with size of 2 bytes.*/
#define	USBCMD_RS		0x0001  /* Run/Stop: 1 = Run. 0 = Stop.*/
#define USBCMD_HCRESET	0x0002  /* Host Contrl Reset */
#define USBCMD_GRESET	0x0004  /* 0 = This bit is reset by the software after a minimum of 10ms has elapsed.
					   				1 = Global reset*/
#define USBCMD_EGSM		0x0008  /* Enter Global Suspend Mode: 0 = Software resets this bit to 0 to come out of Global Suspend mode.
					   			1 = Host Controller enters the Global Suspend mode. No USB transaction occur during this times. */					      		
#define USBCMD_FGR		0x0010  /* Force Global Resume:
					   			0 = Software resets this bit to 0 after 20ms has elapsed to stop sending the Global resume signal.
					   			1 = Host Controller sends the Global Resume signal on the USB and set this bit to 1 when a resume event is detected
					       		while in global suspend mode. */
#define USBCMD_CF		0x0040  /* Configure Flag: This bit has no effect on the hardware. It is provided only as a semaphore service for software.
   					   0 = Indicates that software has not comleted host controller configuration.
   					   1 = HCD software sets this bit as the last action in its process of configuring the Host Contrller. */
#define USBCMD_MAXP_64		0x0080  /* MAX PACKET:[7,6]: 01 = 64 bytes. */    					   					       					   
#define USBCMD_MAXP_32		0x0000  /* MAX PACKET:[7,6]: 00 = 32 bytes. */



/* (02h) USBSTS */
#define USBSTS			2
#define	USBSTS_INT		0x0001  /* 0 = Software resets this bit to 0 by writing a 1 to the bit position. 
					   1 = The Host Controller sets this bit when the cause of an interrupt is a completion */
#define USBSTS_ERRINT		0x0002  /* 0 = Software resets this bit to 0 by writing a 1 to the bit position.
					   1 = Completion of a USB transaction resulted in an error condition. */
#define USBSTS_HCHalted		0x0020  /* 0 = Software resets this bit to 0 by writing a 1 to the bit positiion.
				           1 = The Host Controller has stopped executing as a result of the Run/Stop bit being set to 0 */

/* (04h) USBINTR */
#define USBINTR			4
#define USBINTR_IOC		0x0004  /* Interrupt on Complete (IOC) Enable:
					   0 = Disabled. 1 = Enabled. */				           					   					   
#define USBINTR_SPINTR		0X0008  /* Short Packet Interrupt Enable:
					   0 = Disabled. 1 = Enabled. */

/* (08h) USBFRNUM */
#define USBFRNUM		8
//#define USBFRNUM_FLINDEX	

/* (0Ah) USBFLBASEADDR	*/
#define USBFLBASEADDR 		10

/* (10h) portsc */
#define USBPORTSC		16
#define USBPORTSC_CCS		0x0001 /* Current Connect Status: This value reflects the current state of the port.
					  0 = No device is present. 1 = Device is present on port. */
#define USBPORTSC_CSC		0x0002 /* Connect Status Change: Indicates that a change has occurred in the port's Current Connect Status (bit0).
					  0 =  No change. 1 = Change in Current Connect Status. */
#define USBPORTSC_PORT_EN	0x0004 /* Port Enabled/Disabled: Port can be enabled by host software only. Port can be disabled only by host software or fault condition.
					  0 = Disable. 1 = Enabled. */
#define USBPORTSC_PORT_EN_CHAN  0x0008 /* Port Enable/ Disalbe Change:  For root hub, this bit gets set only when a port is disabled due to disconnect on that port.
					  0 = No change. Software clears this bit by writing a 1 to the bit location.
					  1 = Port enable/disabled status has changed. */
#define USBPORTSC_RSM_DET	0x0040 /* Resume Detect (RSM_SET):	
					  0 = No resume detected/driven on port.
					  1 = Resume detected/driven on port. */
#define USBPORTSC_LS		0x0100 /* Low Speed Device Attached (LS) -- RO. Write have no effect.
					  0 = Full speed device is attached.
					  1 = Low speed device is attached to this port. */					 						  					  
#define USBPORTSC_PORT_RESET	0x0200 /* Port Reset:
					  0 = Port is not in Reset.
					  1 = Port is in Reset. When set, the port is disabled and sends the USB Reset signaling. */					  					  					  					  
#define USBPORTSC_SUSP		0x1000    /* Suspend: This bit should not be written to a 1 if global suspend is active */					  


#define UHCI_MAXNUM_FRAMES	1024      // There are 1024 frame pointer in UHCI frame list table.


//-------------------------------------------------------------------------------------------------
// For TD structure mask:
//-------------------------------------------------------------------------------------------------
#define TD_LINKPOINTER_MASK		0xFFF0
#define TD_LINKPOINTER_DEPTH_BREADTH_SE 0x04
#define TD_LINKPOINTER_QH_TD_SEL	0x02
#define TD_LINKPOINTER_TERMINATE	0x01


#define TD_CTRL_SPD			(1<<29)		// SHORT PACKET DETECT
#define TD_CTRL_C_ERR			(3<<27)		// ERROR COUNTER BITS
#define TD_CTRL_LS			(1<<26)		// LOW SPEED DEVICE
#define TD_CTRL_ISO			(1<<25)		// ISOCHRONOUS SELECT
#define TD_CTRL_IOC			(1<<24)		// INTERRUPT ON COMPLETE
#define TD_CTRL_STATUS_ACTIVE   	(1<<23)		// ACTIVE BIT IN STATUS
#define TD_CTRL_STATUS_STALLED  	(1<<22)		// STALL BIT IN STATUS
#define TD_CTRL_STATUS_BUFFERR  	(1<<21)		// DATA BUFFER ERROR BIT IN STATUS
#define TD_CTRL_STATUS_BABBLE   	(1<<20)		// BABBLE DETECTED BIT IN STATUS
#define TD_CTRL_STATUS_NAK		(1<<19)		// NAK RECEIVED BIT IN STATUS
#define TD_CTRL_STATUS_CRCTIMEOUTERR    (1<<18)		// CRC/TIME OUT ERROR
#define TD_CTRL_STATUS_BITSTUFFERR	(1<<17)		// BITSTUFF ERROR 
#define TD_CTRL_STATUS_ACTLEN		 0x7FF		// ACTUAL LENGTH

#define TD_CTRL_ANY_ERROR		(TD_CTRL_STATUS_STALLED | TD_CTRL_STATUS_DBUFFERR | TD_CTRL_STATUS_BABBLE | \
					 TD_CTRL_STATUS_CRCTIMEOUTERR | TD_CTRL_STATUS_BITSTUFFERR)

#define TD_TOKEN_MAXLEN			0x7FF		// Maximum Length
#define TD_TOKEN_DATA_TOGGLE		(1<<19)		// Data toggle
#define TD_TOKEN_ENDPOINT		(0x0F<<15)	// Endpoint
#define TD_TOKEN_DEVICE_ADDRESS		(0x7F<<8)	// Device Address
#define TD_TOKEN_PID			0xFF		// PID


//-------------------------------------------------------------------------------------------------
//  Queue Header Mask
//-------------------------------------------------------------------------------------------------
#define QH_LINK_POINT			0xFFF0		// Queue Header link pointer
#define QH_LINK_POINT_QH_TD_SEL		(1<<1)		// QH and TD select in Queue Header link pointer
#define QH_LINK_POINT_TERMINATE		0x01		// Terminate.

#define QH_ELEMENT_POINT		0XFFF0		// QUEUE ELEMENT LINK PONITER.
#define QH_ELEMENT_POINT_QH_TD_SEL	(1<<1)		// QH AND TD SELECTION IN QUEUE ELEMENT LINK POINTER.
#define QH_ELEMENT_POINT_TERMINATE	0x01		// Terminate.


//-------------------------------------------------------------------------------------------------
// DEFINED ERROR MESSAGE
//-------------------------------------------------------------------------------------------------
#define SUCCESS					1
#define INSERT_TD_FAIL			2000
#define UNAVAILABLE_TD_TYPE 	2001
#define USB_STALL_ERR			1000
#define USB_PLUG_OUT_ERROR      0xFF
//-------------------------------------------------------------------------------------------------
// Memory space define
//-------------------------------------------------------------------------------------------------


//#define USB_FRAME_LIST_BUF_ADDR			0x80800000	// Start address for frame list table in sdram.
//#define USB_FRAME_LIST_BUF_ADDR_PHY		0x00800000  // Physical address
#define USB_FRAME_LIST_BUF_ADDR                 (SDRAM_BASE_CACHED + USB_YA*1024)  //0x802ae000 - 0x802aefff
#define USB_FRAME_LIST_BUF_ADDR_PHY             (USB_YA*1024)
#define USB_FRAME_LIST_BUF_SIZE			0x00001000 	// 4k

#define USB_TD_BUF_START_ADDR			(USB_FRAME_LIST_BUF_ADDR + USB_FRAME_LIST_BUF_SIZE)	    // Start address in sdram where TDs are located. 0x802af000 - 0x802af7ff
// 0x80801000										
#define USB_TD_BUF_START_ADDR_PHY		(USB_FRAME_LIST_BUF_ADDR_PHY + USB_FRAME_LIST_BUF_SIZE)	// Start address in sdram where TDs are located. 
// 0x00801000
#define USB_TD_BUF_SIZE					0x00000900	// 2k+256 byte //wthsin,20040528										
#define USB_TD_BUF_END_ADDR				(USB_TD_BUF_START_ADDR +  USB_TD_BUF_SIZE - 1)			// End address in sdram where TDs are located. 
// 0x808017ff 

#define USB_QH_BUF_START_ADDR			(USB_TD_BUF_START_ADDR + USB_TD_BUF_SIZE)			// Start address in sdram where qh are located. 0xa02af800 - 0x802a84f
// 0x80801800
#define USB_QH_BUF_START_ADDR_PHY		(USB_TD_BUF_START_ADDR_PHY + USB_TD_BUF_SIZE)		// Physical start address in sdram where qh are located.
// 0x00801800
#define USB_QH_BUF_SIZE					0x00000050	// 80 bytes.


#define USB_SCSI_CMD_BUF_POINTER		(USB_QH_BUF_START_ADDR + USB_QH_BUF_SIZE) 			
//0x80801850
#define USB_SCSI_CMD_BUF_POINTER_PHY	(USB_QH_BUF_START_ADR_PHY + USB_QH_BUF_SIZE)
//0x00801850
#define USB_SCSI_CMD_BUF_SIZE			0x00000020

#define USB_CSW_BUF_POINTER				(USB_SCSI_CMD_BUF_POINTER + USB_SCSI_CMD_BUF_SIZE)
#define USB_CSW_BUF_POINTER_PHY    		(USB_SCSI_CMD_BUF_POINTER_PHY + USB_SCSI_CMD_BUF_SIZE)
#define USB_CSW_BUF_SIZE				0X00000010 
//-------------------------------------------------------------------------------------------------
// Global variables declaration
//-------------------------------------------------------------------------------------------------
#define CONTROL_TD	100		// This kind of TD will be inserted under control QH.
#define BULK_TD		101		// This kind of TD will be inserted under bulk QH.
#define PID_SETUP	0x0d		// Setup token: 1101b.
#define PID_OUT		0x01		// Out token:0001b.
#define PID_IN		0x09		// IN token:1001b.

// Create QH list and assigne physical address 0x00500000 to it.
extern puhci_qh_list puhciQHList;		// control_QH-->bulk_QH list

extern UINT32 *curTDFreeBufAddr; 	
extern BYTE   	*curFreeBufPointer;
extern UINT32 	ACK;
extern UINT32   BulkInEpAddr;   //bulk in endpoint address
extern UINT32   BulkInEpMaxP;   //bulk in endpoint maxpackage
extern UINT32   BulkOutEpAddr;
extern UINT32   BulkOutEpMaxP;
extern UINT32   BulkInToggle;
extern UINT32   BulkOutToggle;

 
//-------------------------------------------------------------------------------------------------
//  SDRAM MEMORY MAP
//-------------------------------------------------------------------------------------------------
//UINT32 *frameListTablePhy = 0x00400000;		// physical base address for frame list table.

//UINT32 *qHtDdAtaPhy       = 0x00500000;		// physical base address for QH, TD, Data structure.

//extern UINT32 *UHCI_IO_BASE;
//extern UINT32 *UHCI_CFG_BASE;

#ifdef	IC_8202L
	#define UHCI_IO_BASE_VIR	0xbc020280
	#define UHCI_CFG_BASE_VIR   0xbc030000		// no longer exist
	#define UHCI_IO_BASE_PHY	0x1c020280
	#define UHCI_CFG_BASE_PHY   0x1c030000		// no longer exist
	#define	UHCI_DATA_WTPORT	0xbc020178
	#define	UHCI_DATA_RDPORT	0xbc02017c
#else	// IC_8202L
	#define UHCI_IO_BASE_VIR	0xbc020000;
	#define UHCI_CFG_BASE_VIR   0xbc030000;
	#define UHCI_IO_BASE_PHY	0x1c020000;
	#define UHCI_CFG_BASE_PHY   0x1c030000;
#endif	// IC_8202L


//-------------------------------------------------------------------------------------------------
// Local function declaration
//-------------------------------------------------------------------------------------------------

UINT32 uhci_bulkXfer (BYTE usbaddr, BYTE endpoint, BYTE pid, BYTE sectorNum, BYTE *CBWBuffer, BYTE *InOutBuffer, BYTE *CSWBuffer);
UINT32 		usbXfer (BYTE usbaddr, BYTE endpoint, BYTE pid, BYTE iso, BYTE payload, WORD wLen, BYTE *buffer);
void 		uhci_cleanSdramUnit4Bytes (UINT32 *startAddr, UINT32 bufferSize, UINT32 defaultValue);
UINT32 		uhci_QHInit();
void 		uhci_HardwareInit();
UINT32 		uhci_memAllocForBufPointer(UINT32 bufferSize);			
UINT32 		uhci_memAllocForTD ();
puhci_td 	uhci_createTD (UINT32 tdTYPE, UINT32 maxLen, BYTE toggleBit, BYTE endPoint, BYTE deviceAddr, BYTE pid);//, UINT32 *ErrMsg)
UINT32 		uhci_insertTD (unsigned char TDTYPE, uhci_td *pTD);
BYTE 		uhci_getNewPidWithCheckSum (BYTE pid);
void 		uhci_memoryCopy (BYTE *bufferAddr, BYTE* sourceBufAddr, WORD wLen);
void 		uhci_FrameListInit();
void 		uhci_killTD(BYTE tdType, UINT32 tdNum, UINT32 bufferPointerSize);
UINT32 		uhci_slaveDetect(void);
UINT32          uhci_PlugInOutDetect(void);
extern  void uhci_flush_TD_BUFF();
extern  void uhci_reset();
void uhci_ErrorProcess(void);
#endif

 
extern void  uhci_USBISR (void);
 

#endif
