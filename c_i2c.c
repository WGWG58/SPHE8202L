/*=================================================================
c_i2c.c: 
	Description:
	This is a C implement of i2c.Compare to the previous IOP 
	implement,it is more fast and easy to modify by programer.
	On the other hand,it consume more system time.So,delay must 
	be carefully considered.
	This code is currently use by HD DVD,for we need such a high
	speed I2C interface to initialize SPV311 and maintain the HDCP
	protocol.
	Read/Write operation for 24C02 is also using this way in HD 
	DVD case.For some types of 24C02 may not work well in high 
	speed,engineer should adjust some timming to improve the 
	capability. 

				huziqin 2004-11-23



================================================================*/
#include "config.h"
#include "regmap.h"
#include "global.h"
#include "user_init.h"
#include "gpio.h"

#if defined(DVI_I2C_SET)&&defined(SPHE8202)
#include "c_i2c.h"//chenzhao20050620

#ifdef SPHE8202
    #if defined(SUPPORT_HD_DVD) && !defined(SCALER_6500)
    #define	I2C_SDA	56
    #define	I2C_SCL	51
    #elif defined(SCALER_6500) //helm for scaler i2c 050729
	#if defined(MP_BOARD_216_PIN_NON_SHARE) && defined(SUPPORT_6500)    
    	#define	I2C_SDA	 85 //for 8202D 216pin + 6500, pin158, ronnie
    	#define	I2C_SCL	 87 //for 8220D 216pin + 6500, pin159, ronnie
      #elif defined(HDMI_16_BIT_256PIN_BOARD)||defined(ORITRON_HK_HDMI_CARD)  // lxg 2006-4-18  For 16 bit HDMI Demo Board .
          #define	I2C_SDA	 39            
          #define	I2C_SCL	 38 
    #else
    	#define	I2C_SDA	 49 //96  helm
    	#define	I2C_SCL	 48 //95  helm
    #endif
    #elif defined(MP_BOARD_216_PIN_NON_SHARE)
    #define	I2C_SDA	18
    #define	I2C_SCL	17
    #elif defined(MP_BOARD_256_PIN_NON_SHARE)&&(defined(SDRAM_BUS_32BITS)||defined(SDRAM_128Mx1)||defined(SCALER_6500))//chenzhao20060110
        #define	I2C_SDA	 49 //96  helm
        #define	I2C_SCL	 48 //95  helm
    #elif defined(MP_BOARD_256_PIN_NON_SHARE)
    #define	I2C_SDA	96
    #define	I2C_SCL	95
    #else
    #error must config i2c pin.
    #endif
#else
#define	I2C_SDA	1		// GPIOE[0]
#define	I2C_SCL	0		// GPIOE[1]
#endif

#ifdef SUPPORT_HD_DVD
#ifdef SPHE8202
    #ifdef NEW_HDDVD_GPIO//add by chenzhao on 2004-12-14 16:11  
    #define	DDC_SDA	32
    #define	DDC_SCL	33
    #else
    #define	DDC_SDA	44
    #define	DDC_SCL	43
    #endif
#else
#error define
#define	DDC_SDA			// GPIOE[0]
#define	DDC_SCL			// GPIOE[1]
#endif
#endif//#ifdef SUPPORT_HD_DVD

//======================================================
#define I2C_PULL_HIGH//Addedd by ChenZhao on 2004-10-13 13:59  
#define	I2C_SCL_SET(d)	GPIO_O_SET(I2C_SCL,d)
#define	I2C_SDA_SET(d)	GPIO_O_SET(I2C_SDA,d)
#define	I2C_SDA_GET()	GPIO_I_GET(I2C_SDA)
#define	I2C_SCL_IN()	GPIO_E_SET(I2C_SCL,0)
#define	I2C_SDA_IN()	GPIO_E_SET(I2C_SDA,0)
#define	I2C_SCL_OUT()	GPIO_E_SET(I2C_SCL,1)
#define	I2C_SDA_OUT()	GPIO_E_SET(I2C_SDA,1)
#ifdef I2C_PULL_HIGH
    #define I2C_SDA_H()     GPIO_E_SET(I2C_SDA,0)
    #define I2C_SDA_L()     {I2C_SDA_SET(0);GPIO_E_SET(I2C_SDA,1);}
    #define I2C_SCL_H()     GPIO_E_SET(I2C_SCL,0)
    #define I2C_SCL_L()     {I2C_SCL_SET(0);GPIO_E_SET(I2C_SCL,1);}
#else
    #define I2C_SDA_H()     {I2C_SDA_SET(1);GPIO_E_SET(I2C_SDA,1);}
    #define I2C_SDA_L()     {I2C_SDA_SET(0);GPIO_E_SET(I2C_SDA,1);}
    #define I2C_SCL_H()     {I2C_SCL_SET(1);GPIO_E_SET(I2C_SCL,1);}
    #define I2C_SCL_L()     {I2C_SCL_SET(0);GPIO_E_SET(I2C_SCL,1);}
#endif//I2C_PULL_HIGH




#ifdef SUPPORT_HD_DVD
#define DDC_PULL_HIGH//Addedd by ChenZhao on 2004-10-13 13:59  

#define	DDC_SCL_SET(d)	GPIO_O_SET(DDC_SCL,d)
#define	DDC_SDA_SET(d)	GPIO_O_SET(DDC_SDA,d)
#define	DDC_SDA_GET()	GPIO_I_GET(DDC_SDA)
#define	DDC_SCL_IN()	GPIO_E_SET(DDC_SCL,0)
#define	DDC_SDA_IN()	GPIO_E_SET(DDC_SDA,0)
#define	DDC_SCL_OUT()	GPIO_E_SET(DDC_SCL,1)
#define	DDC_SDA_OUT()	GPIO_E_SET(DDC_SDA,1)
#ifdef DDC_PULL_HIGH
    #define DDC_SDA_H()     GPIO_E_SET(DDC_SDA,0)
    #define DDC_SDA_L()     {DDC_SDA_SET(0);GPIO_E_SET(DDC_SDA,1);}
    #define DDC_SCL_H()     GPIO_E_SET(DDC_SCL,0)
    #define DDC_SCL_L()     {DDC_SCL_SET(0);GPIO_E_SET(DDC_SCL,1);}
#else
    #define DDC_SDA_H()     {DDC_SDA_SET(1);GPIO_E_SET(DDC_SDA,1);}
    #define DDC_SDA_L()     {DDC_SDA_SET(0);GPIO_E_SET(DDC_SDA,1);}
    #define DDC_SCL_H()     {DDC_SCL_SET(1);GPIO_E_SET(DDC_SCL,1);}
    #define DDC_SCL_L()     {DDC_SCL_SET(0);GPIO_E_SET(DDC_SCL,1);}
#endif//DDC_PULL_HIGH

/*
BIT 1 ; NORMAL I2C BUS ERR
BIT 2 : DDC ERROR
*/
BYTE i2c_err_flag = 0;  
#endif//#ifdef SUPPORT_HD_DVD

//moved to c_i2c.h chenzhao20050620

void i2c_init_io_risc()
{
    GPIO_M_SET(I2C_SDA, 1);
    GPIO_M_SET(I2C_SCL, 1);
}


static void delay_gpio(int i)
{
  do {

#ifdef 	SCALER_6500

    /*
    ** helm for 6500 platform, 050729
    ** helm changes gpio delay to 60
    ** Be aware of the performance of this function.
    ** it will affect on the success of repeater 
    ** authentication
    */
    int j =60; 
#else    
    int j =6;//kevin change add it to 100 it should be also OK if setted to 2 without HDCP
#endif

    do {
      asm volatile ("nop");
    } while (--j>=0);
  } while (--i>=0);
}

#define	delay_i2c(i)	delay_gpio(i)
#define i2c_delay()   delay_i2c(1)

#ifdef SUPPORT_HD_DVD
#define	delay_ddc(i)	delay_gpio(2*i)
#define ddc_delay()   delay_ddc(2*1)
#endif//#ifdef SUPPORT_HD_DVD

//
// i2c_start_sig()
// SCL: --
// SDA: -\_
//
void i2c_start_sig()
{	
	I2C_SCL_H();
	I2C_SDA_H();	
	delay_i2c(1);
    I2C_SDA_L();
	delay_i2c(1);
    
}

//
// i2c_byte_w(data)
// SCL: _/-\_/-\_/-\_/-\_/-\_/-\_/-\_/-\_/-\_
// SDA: _<D7><D6><D5><D4><D3><D2><D1><D0>ACK__
//
int i2c_byte_w(int data)
{	int i;
	I2C_SCL_L()
	//delay_i2c(1);
	for(i=8;i;i--)
	{	if(data&0x80){I2C_SDA_H();}
		else {I2C_SDA_L();}
		delay_i2c(1);						// scl -- low
		I2C_SCL_H(); delay_i2c(1);	//hawk	// scl -> high
		data<<=1;
		I2C_SCL_L(); 		// scl -> low
	}
	// Get ACK
	I2C_SDA_IN();	 delay_i2c(1);			// scl -- low
	I2C_SCL_H(); delay_i2c(1);			// scl -> high
	i= I2C_SDA_GET();	// 0 for no error
	//printf(" state=%d  ",i);
	I2C_SCL_L(); delay_i2c(1);			// scl -> low

	return ((i)?1:0);              //helm: 6500B i2c ACK is ok 051011
}


//
// i2c_stop_sig()
// SCL: _/-
// SDA: __/
//
void i2c_stop_sig()
{	I2C_SDA_L(); I2C_SCL_L();delay_i2c(1);
	I2C_SCL_H(); delay_i2c(1);	
	I2C_SDA_H();
}

void i2c_stop(void)
{
    I2C_SCL_L();
    I2C_SDA_L();
	i2c_delay();
	I2C_SCL_H();
	i2c_delay();
	I2C_SDA_H();
	i2c_delay();
	I2C_SCL_L();
 	i2c_delay();
	I2C_SCL_H();
	I2C_SDA_H();	
}

void init_i2c(void)
{
       I2C_SCL_H();
       I2C_SDA_H();
       i2c_delay();
       i2c_stop();
}

//
// i2c_byte_r()
// SCL: _/-\_/-\_/-\_/-\_/-\_/-\_/-\_/-\_/-\_
// SDA: _<D7><D6><D5><D4><D3><D2><D1><D0>ACK____
//
unsigned char i2c_byte_r(BYTE ack)
{	int i;
      unsigned char data=0;
	I2C_SCL_L();
	I2C_SDA_IN();// delay_i2c(1);			// scl -> low
	for(i=8;i;i--)
	{
            delay_i2c(1); I2C_SCL_IN();		// scl -> high
            delay_i2c(1);
		data = (data<<1) | (I2C_SDA_GET() ? 1 : 0);
	    I2C_SCL_L(); 		// scl -> low
	}
	// Set ACK !!
    if(ack==1)
	I2C_SDA_H();						// scl -- low
    else
    	I2C_SDA_L();						// scl -- low
	delay_i2c(1);			// scl -- low
	I2C_SCL_H(); delay_i2c(1);			// scl -> high
	I2C_SCL_L(); delay_i2c(1);			// scl -> low
	return data;
}
#ifdef XM_MODEL
	void XMStart(void)
	{
		I2C_SCL_H();
		I2C_SDA_H();	
		delay_i2c(20);
    	I2C_SDA_L();
		delay_i2c(20);
	}
	void XMStop(void)
	{
		I2C_SCL_L();
		I2C_SDA_L();
		delay_i2c(20);
		I2C_SCL_H(); 
		delay_i2c(20);	
		I2C_SDA_H();
		delay_i2c(20);
	}
	void XM_init_IIC(void)
	{
		I2C_SCL_H();
       	I2C_SDA_H();
       	delay_i2c(20);
       	XMStop();
	}
	int XM_Write8Bit(BYTE data)
	{	int i,j_wait;
		I2C_SCL_L()
		for(i=8;i;i--)
		{	if(data&0x80){I2C_SDA_H();}
			else {I2C_SDA_L();}
			delay_i2c(10);						// scl -- low
			I2C_SCL_H(); 
			delay_i2c(10);		//hawk	// scl -> high
			data<<=1;
			I2C_SCL_L(); 		// scl -> low
		}
		I2C_SDA_IN();	 
		delay_i2c(10);			// scl -- low
		I2C_SCL_H(); 
		delay_i2c(10);			// scl -> high
		j_wait=0;
		i=1;
		while(i==1&&j_wait<10)
		{
			i= I2C_SDA_GET();	// 0 for no error
			delay_i2c(1);
			j_wait++;
		}
		I2C_SCL_L(); 
		delay_i2c(1);			// scl -> low
       	return ((i)?1:0);
	}
	unsigned char XMRead8Bit(unsigned char nack)
	{
		int i;
      	unsigned char data=0;
		I2C_SCL_L();
		I2C_SDA_IN();// delay_i2c(1);			// scl -> low
		for(i=8;i;i--)
		{
            delay_i2c(10); 
            I2C_SCL_IN();		// scl -> high
            delay_i2c(10);
			data = (data<<1) | (I2C_SDA_GET() ? 1 : 0);
	    	I2C_SCL_L(); 		// scl -> low
		}
		// Set ACK !!
    	if(nack==1)I2C_SDA_H();						// scl -- low
    	else
    		I2C_SDA_L();						// scl -- low
		delay_i2c(10);			// scl -- low
		I2C_SCL_H(); 
		delay_i2c(10);			// scl -> high
		I2C_SCL_L();
		delay_i2c(1);			// scl -> low
		return data;
	}
	unsigned char XM_Send_cmd(unsigned char dev_id,unsigned char key_cmd)
	{
		int i;
		XM_init_IIC();
		XMStart();
		i=XM_Write8Bit(dev_id & 0xfe);
		if(i)
		{
			XMStop();
			return 0;
		}
		delay_i2c(120);
		i=XM_Write8Bit(key_cmd);
		XMStop();
		delay_i2c(80);
		return 1;
	}
	unsigned char XM_read_byte(unsigned char dev_id, unsigned int addr,unsigned char *data,unsigned char num)
	{
		int i;
			XM_init_IIC();
			XMStart();
    		i=XM_Write8Bit(dev_id & 0xfe);	
    		if(i)
			{
				XMStop();
				return 0;
			}
    		delay_i2c(120);
    		i=XM_Write8Bit(addr);
    		XMStop();
    		if(i)return 0; 
    		delay_i2c(200);
    		XMStart();
    		i=XM_Write8Bit(dev_id | 0x01);
    		if(i)
    		{
    			XMStop();
    			return 0;	
    		}
    		while(num)
    		{
    			num--;
    			delay_i2c(120);
    			if(num)*data=XMRead8Bit(0);	//ack
    			else *data=XMRead8Bit(1);	//nack
    			data ++;
    		}
    		XMStop();	
			delay_i2c(200);
			return 1;
	}
	unsigned char XM_read_TXT(unsigned char dev_id, unsigned int addr,unsigned char *data)
	{
		unsigned char txt_len,txt_len_bak;
		int i;
			XM_init_IIC();
			XMStart();
    		i=XM_Write8Bit(dev_id & 0xfe);	
    		if(i)
			{
				XMStop();
				return 0;
			}
    		delay_i2c(120);
    		i=XM_Write8Bit(addr);
    		XMStop();
    		if(i)return 0;
    		delay_i2c(200);
    		XMStart();
    		i=XM_Write8Bit(dev_id | 0x01);
    		if(i)
    		{
				XMStop();
				return 0;
			}
    		delay_i2c(120);
    		txt_len=XMRead8Bit(0);
    		if(txt_len==0||txt_len>64)
    		{
    			XMStop();	
    			return 0;
    		}
    		txt_len_bak=txt_len;
    		while(txt_len)
    		{
    			delay_i2c(120);
    			txt_len--;
    			if(txt_len)*data=XMRead8Bit(0);
    			else *data=XMRead8Bit(1);
    			data ++;
    		}
    		XMStop();	
			delay_i2c(200);
			return txt_len_bak;
	}
#endif//#ifdef XM_MODEL
#ifdef SUPPORT_HD_DVD
 void	write_i2c(unsigned char addr, unsigned char  aa, unsigned char  data)
{
	// Write Addr & DATA
	unsigned char loop;

	//i2c_init_io_risc();

	for (loop=0;loop<K_loopMax;loop++)
	{
        i2c_start_sig();
        if(0==i2c_byte_w(addr)) //W add data(addr<<1|0); //W add data
            if(0==i2c_byte_w(aa))
                if(0==i2c_byte_w(data))
                {
                    i2c_stop_sig();  
                    break;
                }
        init_i2c();
	}
    #ifndef DVDRELEASE
	if (loop == K_loopMax) 
        printf("\t I2C Write error Sub-addr 0x%x\n",addr);
    #endif

	//i2c_init_io_iop();
}




unsigned char read_i2c(unsigned char addr, unsigned char aa)
{
	unsigned char data=0;
	// Write ADDR
	unsigned char loop;

	//i2c_init_io_risc();

	for (loop=0;loop<K_loopMax;loop++)
	{
    	i2c_start_sig();
    	if(0==i2c_byte_w(addr)) //W add
            if(0==i2c_byte_w(aa))
            {
                // Read DATA
                i2c_start_sig();
                if(0==i2c_byte_w(addr|1)) //R data
                {
                data=i2c_byte_r(1);
                i2c_stop_sig();  
                break;
                }
            }
    	init_i2c();
	}
    #ifndef DVDRELEASE
	if (loop == K_loopMax) 
        printf("\t I2C Read error Sub-addr 0x%x\n",addr);
    #endif

	//i2c_init_io_iop();

	 return data;
}



//
// ddc_start_sig()
// SCL: --
// SDA: -\_
//
void ddc_start_sig()
{	
	DDC_SCL_H();
	DDC_SDA_H();	
	delay_ddc(1);
    DDC_SDA_L();
	delay_ddc(1);
    
}
//
// ddc_byte_w(data)
// SCL: _/-\_/-\_/-\_/-\_/-\_/-\_/-\_/-\_/-\_
// SDA: _<D7><D6><D5><D4><D3><D2><D1><D0>ACK__
//
int ddc_byte_w(int data)
{	int i;
	DDC_SCL_L()
	//delay_ddc(1);
	for(i=8;i;i--)
	{	if(data&0x80){DDC_SDA_H();}
		else {DDC_SDA_L();}
		delay_ddc(1);						// scl -- low
		DDC_SCL_H(); delay_ddc(1);	//hawk	// scl -> high
		data<<=1;
		DDC_SCL_L(); 		// scl -> low
	}
	// Get ACK
	DDC_SDA_IN();	 delay_ddc(1);			// scl -- low
	DDC_SCL_H(); delay_ddc(1);			// scl -> high
	i= DDC_SDA_GET();	// 0 for no error
	//printf(" state=%d  ",i);
	DDC_SCL_L(); delay_ddc(1);			// scl -> low
	return ((i)?1:0);
}

//
// ddc_stop_sig()
// SCL: _/-
// SDA: __/
//
void ddc_stop_sig()
{	DDC_SDA_L(); DDC_SCL_L();delay_ddc(1);
	DDC_SCL_H(); delay_ddc(1);	
	DDC_SDA_H();
}
void ddc_stop(void)
{
    DDC_SCL_L();
    DDC_SDA_L();
	ddc_delay();
	DDC_SCL_H();
	ddc_delay();
	DDC_SDA_H();
	ddc_delay();
	DDC_SCL_L();
 	ddc_delay();
	DDC_SCL_H();
	DDC_SDA_H();	
}
void init_ddc(void)
{
       DDC_SCL_H();
       DDC_SDA_H();
       ddc_delay();
       ddc_stop();
}

void	write_ddc(unsigned char addr, unsigned char  aa, unsigned char  data)
{
	// Write Addr & DATA
	unsigned char loop;

	//ddc_init_io_risc();

	for (loop=0;loop<K_loopMax;loop++)
    {
        ddc_start_sig();
        if(0==ddc_byte_w(addr)) //W add data(addr<<1|0); //W add data
            if(0==ddc_byte_w(aa))
                if(0==ddc_byte_w(data))
                {
                    ddc_stop_sig();  
                    break;
                }
        init_ddc();
    }
    #ifndef DVDRELEASE
	if (loop == K_loopMax) 
        printf("\t DDC Write error Sub-addr 0x%x\n",addr);
    #endif

	//ddc_init_io_iop();
}

//
// ddc_byte_r()
// SCL: _/-\_/-\_/-\_/-\_/-\_/-\_/-\_/-\_/-\_
// SDA: _<D7><D6><D5><D4><D3><D2><D1><D0>ACK____
//
unsigned char ddc_byte_r()
{
	int i;
    unsigned char data=0;
	DDC_SCL_L();
	DDC_SDA_IN(); //delay_ddc(1);			// scl -> low
	for(i=8;i;i--)
	{	delay_ddc(1);DDC_SCL_IN(); 		// scl -> high
         delay_ddc(1);
		data = (data<<1) | (DDC_SDA_GET() ? 1 : 0);
		DDC_SCL_L();		// scl -> low
	}
	// Set ACK !!
	DDC_SDA_H();						// scl -- low
	delay_ddc(1);			// scl -- low
	DDC_SCL_H(); delay_ddc(1);			// scl -> high
	DDC_SCL_L(); delay_ddc(1);			// scl -> low
	return data;
}
unsigned char read_ddc(unsigned char addr, unsigned char aa)
{
	unsigned char data=0;
	// Write ADDR
	unsigned char loop;

	//ddc_init_io_risc();

	for (loop=0;loop<K_loopMax;loop++)
    {
        ddc_start_sig();
        if(0==ddc_byte_w(addr)) //W add
            if(0==ddc_byte_w(aa))
            {
                // Read DATA
                ddc_start_sig();
            	if(0==ddc_byte_w(addr|1)) //R data
                {
                    data=ddc_byte_r();
                    ddc_stop_sig();  
                    break;
                }
            }
        init_ddc();
    }
    #ifndef DVDRELEASE
	 if (loop == K_loopMax) 
        printf("\t DDC Read error Sub-addr 0x%x\n",addr);
    #endif

	//ddc_init_io_iop();

	 return data;
}
#endif//#ifdef SUPPORT_HD_DVD

#endif//#if defined(DVI_I2C_SET)&&defined(SPHE8202)


