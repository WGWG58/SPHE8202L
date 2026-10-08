#ifndef __REGMAP_6600_H
#define __REGMAP_6600_H

//GROUP 0~31  DEMUX PID Table Registers 
//GROUP 32~63 DEMUX Match Mask Registers 
#define DEMUX_PVR_DMA_GROUP             39                
#define DEMUX_I2C_HOST_GROUP           123 
#define DEMUX_SD_DEVICE_GROUP          124 
#define DEMUX_SMART_CARD_GROUP         125 
#define DEMUX_GPIO_GROUP               126 
#define DEMUX_SYSTEM_REG_GROUP         127 

// GROUP 38 : DEMUX_PVR_DMA_GROUP
#define	DEMUX_PVR_DMA_BASE    0x08
#define	DEMUX_PVR_DMA_LIMIT   0x09
#define	DEMUX_PVR_DMA_VY      0x0A
#define	DEMUX_PVR_DMA_RY      0x0B
#define	DEMUX_PVR_DMA_VX      0x0C
#define	DEMUX_PVR_DMA_WPTR    0x0D
 

// GROUP 123 : DEMUX_I2C_HOST_GROUP
#define	DEMUX_I2C_ADDR    0
#define	DEMUX_I2C_CMD     1
#define	DEMUX_I2C_IDX     2
#define	DEMUX_I2C_DATA    3
#define	DEMUX_I2C_CFG     4
#define	DEMUX_I2C_FUNC    5
#define	DEMUX_I2C_SPARE   6

// GROUP 124 : DEMUX_SD_DEVICE_GROUP
#define	DEMUX_SD_SPARE0   0
#define	DEMUX_SD_SPARE1   1
#define	DEMUX_SD_SPARE2   2
#define	DEMUX_SD_SPARE3   3

// GROUP 125 : DEMUX_SMART_CARD_GROUP

// GROUP 126 : DEMUX_GPIO_GROUP
#define	DEMUX_GPIO_OE     0
#define	DEMUX_GPIO_OUT    1
#define	DEMUX_GPIO_IN     2

// GROUP 127 : DEMUX_SYSTEM_REG_GROUP
#define	DEMUX_SYSREG_STAMP              0
#define	DEMUX_SYSREG_RESET              1
#define	DEMUX_SYSREG_CLKEN              2
#define	DEMUX_SYSREG_GCLKEN             3
#define	DEMUX_SYSREG_SYSCLK_DIV_SEL     4  //SunIf
#define	DEMUX_SYSREG_SYSCLK_SEL         5
#define	DEMUX_SYSREG_PLLV_CFG           6
#define	DEMUX_SYSREG_SFT_CFG0           7
#define	DEMUX_SYSREG_INT                8

#endif/*__REGMAP_6600_H*/

