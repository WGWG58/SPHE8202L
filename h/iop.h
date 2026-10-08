#ifndef	__IOP_H
#define __IOP_H

//I2C device ID
#define I2C_ID_MEMORY			0xa0
#define I2C_ID_TV_ENCODE		0x40
#define I2C_ID_AUDIO_DAC		0x20

//IOP function call define
#define FUN_PORT			0
#define FUN_MASK			0xf000 
#define FUN_VFD_READ		(0x1<<12)
#define FUN_VFD_WRITE		(0x2<<12)
#define FUN_IR_CUSTID		(0x4<<12)
#define FUN_IR_GET_CUSTID	(0x5<<12)
#define FUN_UART_SEND		(0x6<<12)
#define FUN_I2C_WRITE		(0x7<<12)
#define FUN_I2C_READ		(0x8<<12)
#define FUN_GPAD_READ		(0x9<<12)

#ifdef PMP_MCU810
#define FUN_PMP_MCU810      (0xa<<12)
#endif

//IOP IR control interface
//register mapping of RISC register
#define IR_PORT			5
//control flag
#define IR_RDY			(1<<15)
#define IR_REPEAT		(1<<14)
#define IR_REPLACE		(1<<13)

#define IrRepeatRate(x)	(x<<8)


//IOP vfd control interface

//register mapping of RISC register
#define VFD_CMD			1  
#define VFD_DAT0		2  
#define VFD_DAT1		3  
#define VFD_DAT2		4
//control flag  
#define VFD_DATLEN_MASK	(~0x0007)
#define VFD_DAT_LEN0	0
#define VFD_DAT_LEN1	1  
#define VFD_DAT_LEN2	2 
#define VFD_DAT_LEN3	3
#define VFD_DAT_LEN4	4  
#define VFD_DAT_LEN5	5 
#define VFD_DAT_LEN6	6

//IOP UART control interface
#define UART_DAT		1
 
//I2C control interface
#define I2C_CTRL_ADDR		1
#define I2C_DATA			4

#define I2C_READ_ONE	(0<<5)
#define I2C_READ_CONT	(1<<5)

#define I2C_WRITE_BYTE	(0<<6)
#define I2C_WRITE_PAGE	(1<<6)
#define I2C_READ_IMMEDIATE 	(1<<8)/*add by fred*/
#define I2C_ACK_NACK 	(1<<7)/*add by fred*/
#define I2C_RW_ERR		(1<<4)
#define I2C_RD_RDY		(1<<3)
#define I2C_WR_RDY		(1<<3)

#define I2C_SEQUENTIAL_ORER     (1<<8)//xyy 2003-11-30 17:12

#define	IOP_RDY_WAIT	4000000

// for IOP frequency
#define IOP_13_5MHz		1
#define IOP_27MHz		2
#define IOP_40_5MHz		3
#define IOP_54MHz		4
#define IOP_67_5MHz		5
#define IOP_81MHz		6
#define IOP_94_5MHz		7
#define IOP_108MHz		8
#define IOP_121_5MHz	9
#define IOP_135MHz		10

#define IOP_10MHz		20

int	IsIopFunRdy(void);
int	WaitIopFunRdy(int);
void SetIopFreq(BYTE);


#endif/*__IOP_H*/
