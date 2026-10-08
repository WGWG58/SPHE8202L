#ifndef __ATA_H
#define __ATA_H

#include "config.h"

#define	PRM	(1)	/* primary device or not */
#define	DEV	(0)	/* device 0 or not */
 
#if	defined(__BORLANDC__)
/* IDE I/O address:read */
#define	IDE_DATA			(0x00)
#define	IDE_ERROR			(0x01)
#define	IDE_SECTOR_CNT			(0x02)
#define	IDE_SECTOR_NUM			(0x03)
#define	IDE_CYLINDER_LO			(0x04)
#define	IDE_CYLINDER_HI			(0x05)
#define	IDE_DEVICE_HEAD			(0x06)
#define	IDE_STATUS			(0x07)
#define	IDE_ALT_STATUS			(0x206)

/* IDE I/O address:write */
#define	IDE_FEATURE	IDE_ERROR
#define	IDE_COMMAND	IDE_STATUS
#define	IDE_DEVICE_CTRL	IDE_ALT_STATUS

/* packet I/O address */
#define	IDEPORT(n,x)	(((n) ? 0x170 : 0x1f0) + (UINT16) (x))
#endif	/*__BORLANDC__*/



#if	defined(__EMU__)
/* IDE I/O address:read */
#define	IDE_DATA			(0x00+0x10)
#define	IDE_ERROR			(0x01+0x10)
#define	IDE_SECTOR_CNT			(0x02+0x10)
#define	IDE_SECTOR_NUM			(0x03+0x10)
#define	IDE_CYLINDER_LO			(0x04+0x10)
#define	IDE_CYLINDER_HI			(0x05+0x10)
#define	IDE_DEVICE_HEAD			(0x06+0x10)
#define	IDE_STATUS			(0x07+0x10)
#define	IDE_ALT_STATUS			(0x0E)

/* IDE I/O address:write */
#define	IDE_FEATURE			IDE_ERROR
#define	IDE_COMMAND			IDE_STATUS
#define	IDE_DEVICE_CTRL	IDE_ALT_STATUS

// DVDDSP_CONFIG
#define ATAPI_DEV_HRESET		(1<<0)
#define ATAPI_HOST_RESET		(1<<1)
#define ATAPI_CSS_ENABLE		(1<<2)
#define ATAPI_FIFO_FLUSH		(1<<3)
#define ATAPI_CPPM_ENABLE       (1<<8)

#define CDDSP_FIFOIN          (1<<10)

#ifdef  DVD728
#define PIO_MODE4               (1<<11)
#define PIO_MODE3               (0<<11)
#define PIO_MODE2               (3<<11)
#define PIO_MODE2_REG           (2<<11)
#define ATAPI_INTR_MODE     	(1<<4)
#define ATAPI_DEVICE_INT    	(1<<5)
#define ATAPI_ADV_POLLING		(1<<5)
#else

#define PIO_MODE4			      (0<<11)
#define PIO_MODE3			      (1<<11)
#define PIO_MODE2			      (2<<11)

#define ATAPI_INTR_MODE     	(0)
#define ATAPI_DEVICE_INT    	(0)
#define ATAPI_ADV_POLLING		(0)

#endif


#define E10MHZ_MODE           (3<<11)

#define UDE_ASYNC_MODE        (1<<14)
#define UDE_SYNC_MODE         (0<<14)

#define ATAPI_DEVICE          (0<<15)
#define UDE_DEVICE            (1<<15)

// DVDDSP_FUNCTION
#define DEVICE_INT			(1<<12)

#define ATAPI_READ		   	(1<<13)
#define ATAPI_WRITE			(0<<13)

#define REG_MODE			(1<<14)
#define DATA_MODE			(0<<14)

#define HOST_START			(1<<15)
#define HOST_BUSY			(1<<15)

#endif	/*__EMU__*/

//#define	IDEC_IDENTIFY		0xec
//#define 	IDEC_PACKET             0xa0
//#define	IDEC_IDENTIFY_PACKET	0xa1

#define STATUS_BSY              (0x80)
#define STATUS_DRDY             (0x40)
#define STATUS_DF               (0x20)
#define STATUS_DRQ              (0x08)
#define STATUS_ERR              (0x01)

/* packet command */
//#define PKTC_READ10		0x28
//#define PKTC_READ12		0xa8
//#define PKTC_LOAD		0xa6

// PUBLIC
#define ATA_DMA_MODE			(1<<0)
#define ATA_POLLING_MODE		(1<<4)
#define ATA_INTR_MODE			(0<<4)
#define ATA_NO_BYTECNT			(1<<5)
#define ATA_PIO_DATAIN			(1<<8)

// ATA command
#define ATAC_CHECK_PWR			0xe5
#define ATAC_DIAGNOSTIC			0x90
#define ATAC_SET_FEA			0xef
#define ATAC_ID_PACK			0xa1
#define ATAC_ID_DEV				0xec
#define ATAC_IDLE_IMME			0xe1
#define ATAC_STAND_IMME			0xe0
#define ATAC_SLEEP				0xe6
#define ATAC_RD_SEC				0x20
#define ATAC_WR_SEC				0x30
#define ATAC_WR_DMA				0xca

// ATAPI command
#define PKTC_REQ_SENSE			0x03
#define PKTC_READ_CAPACITY		0x25
#define PKTC_READ10				0x28
#define PKTC_WRITE10			0x2a


#endif/*__ATA_H*/

