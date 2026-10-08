#ifndef __PCA9564_H__
#define __PCA9564_H__

#include "types.h"

#define MAX_I2C_SLAVE_RX_BUF_LEN  128
#define MAX_I2C_SLAVE_TX_BUF_LEN  128

#define FAILURE  0
#define SUCCESS  1

#define   HDI_CTRL_CMD_TYPE  0x51  // Control Command
#define   HDI_SYS_CMD_TYPE   0x62     // System Command
#define   HDI_INFO_CMD_TYPE  0x74    // Info Command
#define   HDI_SET_CMD_TYPE   0x75      // Set Command
#define   I2C_MASTER_ADDRESS 0x77
#define   FALSE    0
#define   TRUE     1

int I2C_Slave_Send_Data(UINT8 *tx_data, UINT8 nbytes);
int I2C_Slave_Read_Data(UINT8 *rx_data, UINT8 nbytes);
UINT8 I2C_Slave_Is_Rx_Buf_Empty(void);
UINT8 I2C_Slave_Is_Tx_Buf_Full(void);
UINT8 I2C_Slave_Get_Rx_Buf_Avail(void);
UINT8 I2C_Slave_Get_Rx_Buf_Length(void);
UINT8 I2C_Slave_Get_Tx_Buf_Avail(void);
UINT8 I2C_Slave_Get_Tx_Buf_Length(void);
UINT8 I2C_Slave_Rx_Buf_GetChar(void);
UINT8 I2C_Slave_Tx_Buf_GetChar(void);
int I2C_Slave_Tx_Buf_PutChar(UINT8 c);
BYTE  I2C_Slave_Get_Rx_In_Ptr(void);
BYTE  I2C_Slave_Get_Tx_In_Ptr(void);
BYTE  I2C_Slave_Get_Rx_Out_Ptr(void);
BYTE  I2C_Slave_Get_Tx_Out_Ptr(void);
void  I2C_Slave_Set_Tx_In_Ptr(UINT16 val);
void  I2C_Slave_Set_Rx_Out_Ptr(UINT16 val);
UINT32 I2C_Slave_Rx_Buf_Get4bytes(void);

#endif /* __PCA9564_H__ */


