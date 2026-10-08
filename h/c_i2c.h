#ifndef _C_I2C_H
#define _C_I2C_H

#if defined(DVI_I2C_SET)&&defined(SPHE8202)
#define K_loopMax 100//chenzhao on 2004-12-14 17:2  



void i2c_init_io_risc();
void i2c_init_io_iop();
void i2c_start_sig();
void i2c_stop_sig();
int i2c_byte_w(int data);
void i2c_stop(void);
void init_i2c(void);
unsigned char i2c_byte_r(BYTE ack);
#ifdef SUPPORT_HD_DVD
extern BYTE i2c_err_flag;  
void	write_i2c(unsigned char addr, unsigned char  aa, unsigned char  data);
unsigned char read_i2c(unsigned char addr, unsigned char aa);

void ddc_start_sig();
int ddc_byte_w(int data);
void ddc_stop_sig();
void ddc_stop(void);
void init_ddc(void);
void	write_ddc(unsigned char addr, unsigned char  aa, unsigned char  data);
unsigned char ddc_byte_r();
unsigned char read_ddc(unsigned char addr, unsigned char aa);
#endif
#endif//#if defined(DVI_I2C_SET)&&defined(SPHE8202)
#endif//#ifndef _C_I2C_H

