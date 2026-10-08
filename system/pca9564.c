#include "pca9564.h"
#include "global.h"
#include "regmap.h"

/* Send a string of bytes to the I2C transmit buffer */
int I2C_Slave_Send_Data(UINT8 *tx_data, UINT8 nbytes)
{
  int result = SUCCESS;
  UINT8 i;
  
  /* Ensure that the message fits into the available tx buffer */
  /* Otherwise signal an error */
  if (nbytes <= I2C_Slave_Get_Tx_Buf_Avail())
  {
    for (i=0; i<nbytes; i++)
    {
      /* Ensure enough space to put the byte in */
      if (I2C_Slave_Is_Tx_Buf_Full() == FALSE)
      {
        /* Copy the tx data byte in */
        I2C_Slave_Tx_Buf_PutChar(tx_data[i]);
      }
      else
      {
        result = FAILURE;
        break;
      }
    }
  }
  else
  {
    result = FAILURE;
  }
  
  return result;
}

/* Read a string of bytes from the I2C receive buffer */
int I2C_Slave_Read_Data(UINT8 *rx_data, UINT8 nbytes)
{
  int result = SUCCESS;
  UINT8 i;  
  
  /* Check that receive buffer has at least nbytes */
  /* Else don't receive the data at all */
  /* HDI Interface : */
  /* - Control Command : 4 bytes */
  /* - System Command  : 4 bytes */
  /* - Info Command    : 4 bytes */
  /* - Set Command     : 37 bytes */
  if (I2C_Slave_Get_Rx_Buf_Length() < nbytes)
  {
    return FAILURE;
  }
  
  for (i=0; i<nbytes; i++)
  {
    if (I2C_Slave_Is_Rx_Buf_Empty() == FALSE)
    {
      *(rx_data + i) = I2C_Slave_Rx_Buf_GetChar();
    }
    else
    {
      result = FAILURE;
      break;
    }
  }
  
  return result;
}

/* Check if I2C receive buffer is empty */
UINT8 I2C_Slave_Is_Rx_Buf_Empty(void)
{
  if (I2C_Slave_Get_Rx_In_Ptr() != I2C_Slave_Get_Rx_Out_Ptr())
  {
    return FALSE;
  }
  else
  {
    return TRUE;
  }
}


/* Check if I2C receive buffer is full */
UINT8 I2C_Slave_Is_Rx_Buf_Full(void)
{     
  if ((I2C_Slave_Get_Rx_In_Ptr() + 1) == I2C_Slave_Get_Rx_Out_Ptr())
  {  
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

/* Check if I2C transmit buffer is empty */
UINT8 I2C_Slave_Is_Tx_Buf_Empty(void)
{
  if (I2C_Slave_Get_Tx_In_Ptr() != I2C_Slave_Get_Tx_Out_Ptr())
  {
    return FALSE;
  }
  else
  {
    return TRUE;
  }
}

/* Check if I2C receive buffer is full */
UINT8 I2C_Slave_Is_Tx_Buf_Full(void)
{
  UINT8 temp;
  
  temp = I2C_Slave_Get_Tx_In_Ptr() + 1;
  
  if (temp == MAX_I2C_SLAVE_TX_BUF_LEN)
  {
    temp = 0;
  }

  if (temp == I2C_Slave_Get_Tx_Out_Ptr())
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

/* Get Rx Buffer Empty Space */
UINT8 I2C_Slave_Get_Rx_Buf_Avail(void)
{
  UINT8 space_avail = 0;
  
  space_avail = (UINT8)(MAX_I2C_SLAVE_RX_BUF_LEN - I2C_Slave_Get_Rx_Buf_Length() - 1);
  
  return space_avail;
}
/* Get Rx Buffer Empty Space */
UINT8 I2C_Slave_Get_Rx_Buf_Length(void)
{
  UINT8 length = 0;
  UINT8 in_ptr, out_ptr;  
  
  in_ptr  = I2C_Slave_Get_Rx_In_Ptr();
  out_ptr = I2C_Slave_Get_Rx_Out_Ptr();
  
  if (in_ptr != out_ptr)
  {
    do
    { 
      out_ptr += 1;
      if (out_ptr == MAX_I2C_SLAVE_RX_BUF_LEN)
      {
        out_ptr = 0;
      }       
      length = length + 1;
    } while (in_ptr != out_ptr);
  }
  return length;
}

/* Get Tx Buffer Empty Space */
UINT8 I2C_Slave_Get_Tx_Buf_Avail(void)
{
  UINT8 space_avail = MAX_I2C_SLAVE_TX_BUF_LEN;
  
  space_avail = (UINT8)(MAX_I2C_SLAVE_TX_BUF_LEN - I2C_Slave_Get_Tx_Buf_Length() - 1);
  
  return space_avail; 
}

/* Calculate the length of the buffer used */
UINT8 I2C_Slave_Get_Tx_Buf_Length(void)
{
  UINT8 length = 0;
  UINT8 in_ptr, out_ptr;  
  
  in_ptr  = I2C_Slave_Get_Tx_In_Ptr();
  out_ptr = I2C_Slave_Get_Tx_Out_Ptr();
  
  if (in_ptr != out_ptr)
  {
    do
    { 
      out_ptr += 1;
      if (out_ptr == MAX_I2C_SLAVE_TX_BUF_LEN)
      {
        out_ptr = 0;
      } 
      length = length + 1;
    } while (in_ptr != out_ptr);
  }
  return length;
}

/* Get a data byte from the receive buffer */
UINT8 I2C_Slave_Rx_Buf_GetChar(void)
{
  UINT8 c = 0;  // NULL Character

  /* Check if receive buffer has something to retrieve */  
  if (I2C_Slave_Is_Rx_Buf_Empty() == FALSE)
  {  
    I2C_Slave_Set_Rx_Out_Ptr(I2C_Slave_Get_Rx_Out_Ptr() + 1);
    
    /* Allow roll-over */
    if (I2C_Slave_Get_Rx_Out_Ptr() > (MAX_I2C_SLAVE_RX_BUF_LEN-1))
    {
      I2C_Slave_Set_Rx_Out_Ptr(0);
    }

    /* Check if any character in the buffer */
    c = *((BYTE *)(I2C_Slave_Rx_Buf_Ptr() + I2C_Slave_Get_Rx_Out_Ptr())); 
  }
  
  return c;
}

/* Put a data byte to the transmit buffer */
int I2C_Slave_Tx_Buf_PutChar(UINT8 c)
{
  int result = FAILURE;
  
  //if (c != 0)
  {
    /* Ensure enough space in receive buffer */
    if (I2C_Slave_Is_Tx_Buf_Full() != TRUE)
    {
      I2C_Slave_Set_Tx_In_Ptr(I2C_Slave_Get_Tx_In_Ptr() + 1);
      
      /* Allow roll-over */
      if (I2C_Slave_Get_Tx_In_Ptr() == MAX_I2C_SLAVE_TX_BUF_LEN)
      {
        I2C_Slave_Set_Tx_In_Ptr(0);
      }
      
      /* Copy the data byte in */
      *((UINT8 *)((UINT32)(I2C_Slave_Tx_Buf_Ptr() + I2C_Slave_Get_Tx_In_Ptr()))) = c;
      result = SUCCESS;
    }
  }

  return result;   
}

// Rx In/Out Pointers
BYTE  I2C_Slave_Get_Rx_In_Ptr(void)
{
  return (BYTE)((regs0->iop_data[2]&0x00ff)>>0);//write by 6502
}    

BYTE  I2C_Slave_Get_Rx_Out_Ptr(void)
{
  return (BYTE)((regs0->iop_data[2]&0xff00)>>8);
}    

// Tx In/Out Pointers
BYTE  I2C_Slave_Get_Tx_In_Ptr(void)
{
  return (BYTE)((regs0->iop_data[3]&0x00ff)>>0);
}    

BYTE  I2C_Slave_Get_Tx_Out_Ptr(void)
{
  return (BYTE)((regs0->iop_data[3]&0xff00)>>8);
}

// Increment Rx Out Buffer
void  I2C_Slave_Set_Rx_Out_Ptr(UINT16 val)
{  
  UINT16 temp;  

  temp = ((UINT16)(regs0->iop_data[2] & 0x00ff));
  regs0->iop_data[2] = temp + (val*256);
}

// Increment Tx In Buffer
void  I2C_Slave_Set_Tx_In_Ptr(UINT16 val)
{ 
  UINT16 temp;
  
  temp = (UINT16)(regs0->iop_data[3] & 0xff00);
  
  regs0->iop_data[3] = (UINT16) (temp + val);
}    

// Return Receive Buffer Pointer Address
UINT32 I2C_Slave_Rx_Buf_Ptr(void)
{
  return ((UINT32)(SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x588));
}

// Return Transmit Buffer Pointer Address
UINT32 I2C_Slave_Tx_Buf_Ptr(void)
{
  //return ((UINT32)(SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x5C8));
  return ((UINT32)(SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x608));
}

#if 0
/* Get a data byte from the transmit buffer */
UINT8 I2C_Slave_Tx_Buf_GetChar(void)
{
  UINT8 c = 0;  // NULL Character
  
  /* Check if transmit buffer has data to be retrieved */
  if (I2C_Slave_Is_Tx_Buf_Empty() == FALSE)
  {
    //I2C_Slave_Get_Tx_Out_Ptr() = I2C_Slave_Get_Tx_Out_Ptr() + 1;
    
    
    /* Allow roll-over */
    //if (I2C_Slave_Get_Tx_Out_Ptr() > (MAX_I2C_SLAVE_TX_BUF_LEN-1))
    //{
    //  I2C_Slave_Get_Tx_Out_Ptr() = 0;
    // }

    /* Check if any character in the buffer */
    //c = I2C_Slave_Tx_Buf[I2C_Slave_Get_Tx_Out_Ptr()];    
    //c = *((UINT8 *)(SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x5C9));
    c = *((UINT8 *)(SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x608));
    
  }  
  
  return c;
}
#endif

#if 0
/* Put a data byte to the receive buffer */
int I2C_Slave_Rx_Buf_PutChar(UINT8 c)
{
  int result = FAILURE;
  
  if (c != 0)
  {
    /* Ensure enough space in receive buffer */
    if (I2C_Slave_Is_Rx_Buf_Full() != TRUE)
    {
      I2C_Slave_Get_Rx_In_Ptr() = I2C_Slave_Get_Rx_In_Ptr() + 1;
      
      /* Allow roll-over */
      if (I2C_Slave_Get_Rx_In_Ptr() > (MAX_I2C_SLAVE_RX_BUF_LEN-1))
      {
        I2C_Slave_Get_Rx_In_Ptr() = 0;
      }
      
      /* Copy the data byte in */
      I2C_Slave_Rx_Buf[I2C_Slave_Get_Rx_In_Ptr()] = c;
      result = SUCCESS;
    }
  }
  
  return result;
}
#endif


