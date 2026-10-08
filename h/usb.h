/*--------------------------------------------------------------------------
|  File Name   : usb.h
|
|  Description : This module contains   usb interface
|
|  Version    :  0.1  
| 
| 
|---------------------------------------------------------------------------------
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2003/11/27       wthsin         Creating
|  0.2  2003/12/19       Liweihua       
|--------------------------------------------------------------------------------*/
#ifndef   USB_H
#define   USB_H

//#define USB_DEVICE  0x01  //Maoyong marked 2004-8-12, already defined in gb_def.h
#define uDisk_ADDR  0x02
#define ISO_BIT     0x10
#define MAX_DEV    	0x05    //Address #0 + Slave(one device)//0x06     // maximum number of devices (Address #0 + Slave + 4 Hub's device)
#define MAX_EP    	0x05    // maximum number of endpoints (Ep0 + max of 4 data endpoints)

#define TIMEOUT_RETRY		0x06	// Maximum no. of timeout retry during USB xfer
#define ep0       0

typedef struct
{
    UINT16  wVID, wPID;       // Vendor ID and Product ID
    UINT8  bClass;           // 
    UINT8  bNumOfEPs;        // actual number endpoint from slave
    UINT8  iMfg;				// Manufacturer ID
    UINT8  iPdt;				// Product ID
    UINT8  bId1;
    UINT8  bId2;
    UINT8  bEPAddr[MAX_EP];   // bit 7 = 1 = use PID_IN, 
    UINT8  bAttr[MAX_EP];     // ISO | Bulk | Interrupt | Control
    UINT8  wPayLoadL[MAX_EP];  // ISO range: 1-1023, Bulk: 1-64, etc,dayong,but the sl811 only support ISO 255!!!!
    UINT8  wPayLoadH[MAX_EP];  // ISO range: 1-1023, Bulk: 1-64, etc
    UINT16  bInterval[MAX_EP]; // polling interval (for LS)
    UINT8  bData1[MAX_EP];    // DataToggle value
} pUSBDEV, *PUSBDEV;

// USB specific request
typedef struct
{
    UINT8 bmRequest;
    UINT8 bRequest;
    UINT16 wValue;
    UINT16 wIndex;
    UINT16 wLength;
} SetupPKG, *pSetupPKG;

// Standard Device Descriptor
typedef struct
{   UINT8 bLength;
    UINT8 bDescriptorType;
    UINT16 bcdUSB;
    UINT8 bDeviceClass;
    UINT8 bDeviceSubClass;
    UINT8 bDeviceProtocol;
    UINT8 bMaxPacketSize0;
    UINT16 idVendor;
    UINT16 idProduct;
    UINT16 bcdDevice;
    UINT8 iManufacturer;
    UINT8 iProduct;
    UINT8 iSerialNumber;
    UINT8 bNumConfigurations;
} sDevDesc, *pDevDesc;

// Standard Configuration Descriptor
typedef struct
{	
    UINT8 bLength;                 // Size of descriptor in Byte
	UINT8 bType;			 // Configuration type
	UINT16 wLength;           // Total length
	UINT8 bNumIntf;		 // Number of interface
	UINT8 bCV;             	 // bConfigurationValue
	UINT8 bIndex;          	 // iConfiguration
	UINT8 bAttr;                  // Configuration Characteristic
	UINT8 bMaxPower;	 // Power config
} sCfgDesc, *pCfgDesc;

// Standard Interface Descriptor
typedef struct
{	UINT8 bLength;
	UINT8 bType;
	UINT8 iNum;
	UINT8 iAltString;
	UINT8 bEndPoints;
	UINT8 iClass;
	UINT8 iSub; 
	UINT8 iProto;
	UINT8 iIndex; 
} sIntfDesc, *pIntfDesc;

// Standard HID Descripor
typedef struct
{   UINT8  bLength;       // Size of this descriptor in bytes  0x09
    UINT8  bType;         // HID descriptor tyep (assigned by USB)  0x21
    UINT16 bcdHID;        // HID Class Specifacation telease number
    UINT8  bCountryCode;  // Hardware target country
    UINT8  bNumDesc;      // Number of HID class descriptors to follow
    UINT8  bDescType;     // Report descriptor type
    UINT8 wItemLengthL;   // Total Length of Report descriptor low byte
    UINT8 wItemLengthH;   // Total Length of Report descriptor high byte
} sHidDesc,*pHidDesc;

// Standard EndPoint Descriptor
typedef struct
{	UINT8 bLength;
	UINT8 bType;
	UINT8 bEPAdd;
	UINT8 bAttr;                  //transfer type
	UINT8 wPayLoadL;        // low-speed this must be 0x08
	UINT8 wPayLoadH;       //endpoint wPayLoad <=64
	UINT8 bInterval;
} sEPDesc, *pEPDesc;

//joshua, 20050715, modified for supporting Apple iPod(2 partition)
extern UINT8 IsAppleiPod;

/*-------------------------------------------------------------------------
 * Standard Chapter 9 definition
 *-------------------------------------------------------------------------
 */
#define GET_STATUS         0x00																  
#define CLEAR_FEATURE   0x01
#define SET_FEATURE       0x03
#define SET_ADDRESS       0x05
#define GET_DESCRIPTOR  0x06
#define SET_DESCRIPTOR  0x07
#define GET_CONFIG          0x08
#define SET_CONFIG          0x09
#define GET_INTERFACE    0x0a
#define SET_INTERFACE    0x0b
#define SYNCH_FRAME       0x0c


#define DEVICE                  0x01
#define CONFIGURATION   0x02
#define STRING                  0x03
#define INTERFACE            0x04
#define ENDPOINT              0x05
#define REPORTDESC      0x22

#define STDCLASS              0x00
#define HIDCLASS              0x03
#define HUBCLASS	 	0x09      // bDeviceClass, bInterfaceClass
#define MassCLASS            0x08     //Mass Storage class
#define USB_IN               0x80

#define HubDescriptorOffset       25
#define HubNbrPortsOffset          2
#define HubDeviceRemovableOffset   7
//*****************************************************************************************
// function  section
//***************************************************************************************** 
int ep0Xfer(UINT8 usbaddr, UINT8 payload, pSetupPKG setup, UINT8 *pData);
int VendorCmd(UINT8 usbaddr,UINT8 bReq, UINT8 bCmd, UINT16 wValue, UINT16 wIndex,UINT16 wLen,UINT8* pData);
int GetDesc(UINT8 usbaddr, UINT16 wValue, 	UINT16 wIndex, UINT16 wLen, UINT8 *desc);
int GetStatus(UINT8 usbaddr, UINT8 *desc);
int SetAddress(UINT16 addr);
int Set_Configuration(UINT8 usbaddr,UINT16 wVal);
int EnumUsbDev(UINT8 DevAddr);
UINT16 WordSwap(UINT16 input);
UINT32 DWordSwap(UINT32 input);
int Get_Configuration(UINT8 usbaddr,UINT8 *pdata);
UINT8 GetMaxLUN(UINT8 usbaddr);
UINT8 BulkOnlyReset(UINT8 usbaddr);
UINT8 BulkOnlyClear(UINT8 usbaddr);
UINT8 BulkInClear(UINT8 usbaddr,UINT8 bulkinendp);
UINT8 BulkOutClear(UINT8 usbaddr,UINT8 bulkoutendp);
UINT32 BulkXfer(UINT8 usbaddr,UINT8 pid,UINT16 wLen, UINT8 *buffer);
int  UsbIsPlugIn(); 
BYTE IsUSBCardReader(void);
int HubUDisk_Function(UINT8);

#if 1//def SUPPORT_MP3_ENCODER
UINT32 BulkXfer_nonBlock(UINT8 usbaddr,UINT8 pid,UINT16 wLen, UINT8 *buffer);
#endif

#endif //end USB_H
