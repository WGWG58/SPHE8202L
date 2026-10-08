/***********************************
Creater: xiongyuyue
Date   : 2003/8/14 
Description: Amplifier function using
Reference:DDX8000 Datasheet(APOGEE CO.)
***********************************/
#include "user_init.h"
//#include "config.h"
//#include "regmap.h"
#include "global.h"
#include "ircode.h"
#include "osd.h"
//#include "gpio.h"
//#include "iop.h"
#include "audctrl.h"
//#include "ddx8000.h"
#include "ddx8000_xq.h" //xyy 2004-3-2 9:45  for temporary using
#include "cchar.h"

#define NOP delay_1us(10000)

int ddx_amp_mode = 0;

extern BYTE * lev_list[7];

BYTE channel_addr[6] = 
{
	0x09,//front left
	0x0a,//front right
	0x0b,//surround left
	0x0c,//surround right
	0x0d,//center
	0x0e//subwoofer
};


//Reset DDX8000
void ddx_reset_all(void)
{
	BYTE data;
//Reset Configuration Register A
	data = 0x83;
	WriteToI2c(DDX8K_ADDR,CONFIGREG_A,&data,1);
//Reset Configuration Register B
	data = 0x42;
	WriteToI2c(DDX8K_ADDR,CONFIGREG_B,&data,1);
//Reset Configuration Register C
	data = 0x7c;
	WriteToI2c(DDX8K_ADDR,CONFIGREG_C,&data,1);
//Reset Configuration Register D
	data = 0x20;
	WriteToI2c(DDX8K_ADDR,CONFIGREG_D,&data,1);
//Reset Configuration Register E
	data = 0x02;
	WriteToI2c(DDX8K_ADDR,CONFIGREG_E,&data,1);
//Reset Configuration Register F
	data = 0x00;
	WriteToI2c(DDX8K_ADDR,CONFIGREG_F,&data,1);
//Master Mute
	data = 0x00;
	WriteToI2c(DDX8K_ADDR,MASTER_MUTE_REG,&data,1);
//Master Volume
	data = 0xff;
	WriteToI2c(DDX8K_ADDR,MASTER_VOL_REG,&data,1);
//Channel 1,2,3,4,5,6,7,8 mute
	data = 0x00;
	WriteToI2c(DDX8K_ADDR,CHANEL_MUTE_REG,&data,1);
//Channel 1,2,3,4,5,6,7,8 Volume
	data = 0x30;
	WriteToI2c(DDX8K_ADDR,C1V_REG,&data,8);
//Channel Input Mapping
	data = 0x10;
	WriteToI2c(DDX8K_ADDR,C12MAP_REG,&data,1);
	data = 0x32;
	WriteToI2c(DDX8K_ADDR,C34MAP_REG,&data,1);
	data = 0x54;
	WriteToI2c(DDX8K_ADDR,C56MAP_REG,&data,1);
	data = 0x76;
	WriteToI2c(DDX8K_ADDR,C78MAP_REG,&data,1);
//Limiter Selection
	data = 0x00;
	WriteToI2c(DDX8K_ADDR,CLIMITER_SEL0,&data,2);
//Limiter 1 & 2 Rates and Thresholds
	data = 0xa6;
	WriteToI2c(DDX8K_ADDR,L1RATE_REG,&data,1);
	data = 0x67;
	WriteToI2c(DDX8K_ADDR,L1THRESHOLDS_REG,&data,1);
	data = 0xa6;
	WriteToI2c(DDX8K_ADDR,L2RATE_REG,&data,1);
	data = 0x67;
	WriteToI2c(DDX8K_ADDR,L2THRESHOLDS_REG,&data,1);
//Tone control
	data = 0x77;
	WriteToI2c(DDX8K_ADDR,TONE_CTRL_REG,&data,1);
}

void write_reg_bit(int addr,BYTE bit,BYTE val)
{
	BYTE tmp = 0;
	int res;
	res = ReadFromI2c(DDX8K_ADDR,addr,&tmp,1);
	NOP;
//	printf("11-----------------tmp = :%x,res :%d**********\n",tmp,res);
	if(val)
		tmp |= 0x01<<bit;
	else
		tmp &= ~(0x01<<bit);
	NOP;
	res = WriteToI2c(DDX8K_ADDR,addr,&tmp,1);
	printf("1addr :%x,tmp = :%x,res :%d\n",addr,tmp,res);
	NOP;

	res = ReadFromI2c(DDX8K_ADDR,addr,&tmp,1);
	printf("2addr :%x,tmp = :%x,res :%d\n",addr,tmp,res);
}

//Enable or Disable External Amplifier Power Down
void ddx_enableEPAD(void)
{
	write_reg_bit(CONFIGREG_F,7,1);
}

void ddx_disableEPAD(void)
{
	write_reg_bit(CONFIGREG_F,7,0);
}

/*///////////////////////////////////////////////////////////////
sample_rate     ctrl        input data format
   32fs         ¡Á010        MSB First Right/Left-Justified 16-bit data
   48fs         0001        MSB First Left-Justified Data
                1001        LSB First Left-Justified Data
                ¡Á010        Right-Justified 16-bit Data
                ¡Á011        Right-Justified 18-bit Data
                ¡Á100        Right-Justified 20-bit Data
                ¡Á101        Right-Justified 24-bit Data
   64fs         0000        I2S 16 to 24-bit Data          default input data format
   				0001        MSB First Left-Justified Data
                1001        LSB First Left-Justified Data
                ¡Á010        Right-Justified 16-bit Data
                ¡Á011        Right-Justified 18-bit Data
                ¡Á100        Right-Justified 20-bit Data
                ¡Á101        Right-Justified 24-bit Data
*////////////////////////////////////////////////////////////////
void set_inputData_format(BYTE ctrl)
{
    UINT16      romSum=0;
    BYTE *p = (BYTE *)(&romSum);
	ReadFromI2c(DDX8K_ADDR,CONFIGREG_B,p,1);
	*p = (ctrl<<2) | (*p & 0xc3);
	WriteToI2c(DDX8K_ADDR,CONFIGREG_B,p,1);
}

//channel mapping
//par:  pch---processing channel number; ich---input channel number
void ddx_channel_map(BYTE pch,BYTE ich)
{
    UINT16      romSum=0;
    BYTE *p = (BYTE *)(&romSum);
	switch(pch)
	{
		case 1:
			*p = (*p & 0xf8) | (ich-1);
			WriteToI2c(DDX8K_ADDR,C12MAP_REG,p,1);
			break;
		case 2:
			*p = (*p & 0x8f) | ((ich-1)<<4);
			WriteToI2c(DDX8K_ADDR,C12MAP_REG,p,1);
			break;
		case 3:
			*p = (*p & 0xf8) | (ich-1);
			WriteToI2c(DDX8K_ADDR,C34MAP_REG,p,1);
			break;
		case 4:
			*p = (*p & 0x8f) | ((ich-1)<<4);
			WriteToI2c(DDX8K_ADDR,C34MAP_REG,p,1);
			break;
		case 5:
			*p = (*p & 0xf8) | (ich-1);
			WriteToI2c(DDX8K_ADDR,C56MAP_REG,p,1);
			break;
		case 6:
			*p = (*p & 0x8f) | ((ich-1)<<4);
			WriteToI2c(DDX8K_ADDR,C56MAP_REG,p,1);
			break;
		case 7:
			*p = (*p & 0xf8) | (ich-1);
			WriteToI2c(DDX8K_ADDR,C78MAP_REG,p,1);
			break;
		case 8:
			*p = (*p & 0x8f) | ((ich-1)<<4);
			WriteToI2c(DDX8K_ADDR,C78MAP_REG,p,1);
			break;
	}
}

//////////////////////////////////////////////////////////////////
//Configuration Register A
/*
sample rate(kHz)  |  IR(D4~D3)  |            MCS(D2~D0)
-----------------------------------------------------------------------
                  |             |  1¡Á¡Á   | 011   | 010   | 001   | 000
-----------------------------------------------------------------------
32, 44.1, 48      |     00      |  128fs | 256fs | 384fs | 512fs | 768fs
88.2, 96          |     01      |  64fs  | 128fs | 192fs | 256fs | 384fs
176.4, 192        |     10      |  64fs  | 128fs | 192fs | 256fs | 384fs
Reserved          |     NA      |    NA  |   NA  |   NA  |   NA  |   NA
-----------------------------------------------------------------------
*/
///////////////////////////////////////////////////////////////////
void set_inputClock(BYTE IR,BYTE MCS)
{
    UINT16      romSum=0;
    BYTE *p = (BYTE *)(&romSum);
	*p = (*p & 0xe0) | ((IR<<3) | MCS);	
	WriteToI2c(DDX8K_ADDR,CONFIGREG_A,p,1);	
}

//Bass Management
//set Configuration Register A bit 5 will enable or disable bass management
void ddx_enable_BassManagement(void)
{
	write_reg_bit(CONFIGREG_A,5,1);
}

void ddx_disable_BassManagement(void)
{
	write_reg_bit(CONFIGREG_A,5,0);
}

//Reading a Coefficient Value From RAM
UINT32 ddx_readCoefVal(BYTE regAddr)
{
	UINT32 tmp;
    UINT16      romSum=0;
    BYTE *p = (BYTE *)(&romSum);
    
//    printf("**********************************************\n");
    //write 8-bit address to I2C register 1Ch
    *p = regAddr;
	WriteToI2c(DDX8K_ADDR,0x1c,p,1);

	*p = 0;
	ReadFromI2c(DDX8K_ADDR,0x1c,p,1);
//	printf("the val of register 0x1c is:%x\n",*p);

	//read top 8-bits of coefficient in I2C address 1Dh
	*p = 0;
	ReadFromI2c(DDX8K_ADDR,0x1d,p,1);

//	printf("the val of register 0x1d is:%x\n",*p);

	tmp = (*p << 16) & 0xff0000;

	//read middle 8-bits of coefficient in I2C address 1Fh
	*p = 0;
	ReadFromI2c(DDX8K_ADDR,0x1e,p,1);

//	printf("the val of register 0x1e is:%x\n",*p);

	tmp = tmp | ((*p << 8) & 0xff00);

	//read bottom 8-bits of coefficient in I2C address 1Fh
	*p=0;
	ReadFromI2c(DDX8K_ADDR,0x1f,p,1);

//	printf("the val of register 0x1f is:%x\n",*p);

	tmp = tmp | *p;
	return tmp;
}
//Writing a single Coefficient Value to RAM
void ddx_writeCoefVal(BYTE regAddr,UINT32 coefVal)
{
	
    UINT16      romSum=0;
    BYTE *p = (BYTE *)(&romSum);
    
    //write 8-bit address to I2C register 1Ch
    *p = regAddr;
	WriteToI2c(DDX8K_ADDR,0x1c,p,1);
	
	//write top 8-bits of coefficient in I2C address 1Dh
	*p = (coefVal & 0xff0000) >> 16;
	WriteToI2c(DDX8K_ADDR,0x1d,p,1);

	//write middle 8-bits of coefficient in I2C address 1Eh
	*p = (coefVal & 0x00ff00) >> 8;
	WriteToI2c(DDX8K_ADDR,0x1e,p,1);

	//write bottom 8-bits of coefficient in I2C address 1Fh
	*p = (coefVal & 0x0000ff);
	WriteToI2c(DDX8K_ADDR,0x1f,p,1);

	//write control
	write_reg_bit(0x2c,0,1);
}


//Writing a set of Coefficient Values to RAM
void ddx_writeCoefValSets(BYTE startAddr,coef_factor factor)
{
    UINT16      romSum=0;
    BYTE *p = (BYTE *)(&romSum);
    //write 8-bit address to I2C register 1Ch
    *p = startAddr;
	WriteToI2c(DDX8K_ADDR,0x1c,p,1);
//write factor b2
	*p = (factor.b2 & 0xff0000) >> 16;
	WriteToI2c(DDX8K_ADDR,0x1d,p,1);

	*p = (factor.b2 & 0x00ff00) >> 8;
	WriteToI2c(DDX8K_ADDR,0x1e,p,1);

	*p = (factor.b2 & 0x0000ff);
	WriteToI2c(DDX8K_ADDR,0x1f,p,1);
//write factor b0
	*p = (factor.b0 & 0xff0000) >> 16;
	WriteToI2c(DDX8K_ADDR,0x20,p,1);

	*p = (factor.b0 & 0x00ff00) >> 8;
	WriteToI2c(DDX8K_ADDR,0x21,p,1);

	*p = (factor.b0 & 0x0000ff);
	WriteToI2c(DDX8K_ADDR,0x22,p,1);
//write factor a2
	*p = (factor.a2 & 0xff0000) >> 16;
	WriteToI2c(DDX8K_ADDR,0x23,p,1);

	*p = (factor.a2 & 0x00ff00) >> 8;
	WriteToI2c(DDX8K_ADDR,0x24,p,1);

	*p = (factor.a2 & 0x0000ff);
	WriteToI2c(DDX8K_ADDR,0x25,p,1);
//write factor a1
	*p = (factor.a1 & 0xff0000) >> 16;
	WriteToI2c(DDX8K_ADDR,0x26,p,1);

	*p = (factor.a1 & 0x00ff00) >> 8;
	WriteToI2c(DDX8K_ADDR,0x27,p,1);

	*p = (factor.a1 & 0x0000ff);
	WriteToI2c(DDX8K_ADDR,0x28,p,1);
//write factor b1
	*p = (factor.b1 & 0xff0000) >> 16;
	WriteToI2c(DDX8K_ADDR,0x29,p,1);

	*p = (factor.b1 & 0x00ff00) >> 8;
	WriteToI2c(DDX8K_ADDR,0x2a,p,1);

	*p = (factor.b1 & 0x0000ff);
	WriteToI2c(DDX8K_ADDR,0x2b,p,1);

//write control
	write_reg_bit(0x2c,1,1);
}
//HPB register i.e. Configuation Register C-02h,Bit 7
//1: disable this feature
//0: enable this feature	
//input:1---disable,0---enable
//enable High Pass Filter
void enable_hpf(void)
{
	write_reg_bit(CONFIGREG_C,7,0);	
}

void disable_hpf(void)
{
 	write_reg_bit(CONFIGREG_C,7,1);
}

//tone control:  include treble control and bass control
//input:
//updown: 1---boost tone -1---cut tone
BYTE ddx_trebleCtrl(int updown)   //xulf modified 2004-01-13
{
    BYTE romSum=0;
    BYTE *p = (BYTE *)(&romSum);
    
	ReadFromI2c(DDX8K_ADDR,TONE_CTRL_REG,p,1);
	if(updown==1)
	{
		if(amp_userSet.ddx_Treble_lev < 0x0d)
			amp_userSet.ddx_Treble_lev++;
	}
	else if(updown==-1)
	{
		if(amp_userSet.ddx_Treble_lev > 0x1)
			amp_userSet.ddx_Treble_lev--;
	}
	*p = (amp_userSet.ddx_Treble_lev<<4) | (*p & 0x0f);
	WriteToI2c(DDX8K_ADDR,TONE_CTRL_REG,p,1);
	WriteToI2c(0xa0, TREBLE_GAIN_ADDR, &amp_userSet.ddx_Treble_lev, 1);
}	

BYTE  ddx_bassCtrl(int updown) //xulf modified 2004-01-13
{
    BYTE romSum=0;
    BYTE *p = (BYTE *)(&romSum);
    
	ReadFromI2c(DDX8K_ADDR,TONE_CTRL_REG,p,1);
	if(updown==1)
	{
		if(amp_userSet.ddx_Bass_lev < 0x0d)      
			amp_userSet.ddx_Bass_lev++;
	}
	else if(updown==-1)
	{
		if(amp_userSet.ddx_Bass_lev > 0x1)
			amp_userSet.ddx_Bass_lev--;
	}
	*p = amp_userSet.ddx_Bass_lev | (*p & 0xf0);
	WriteToI2c(DDX8K_ADDR,TONE_CTRL_REG,p,1);
	WriteToI2c(0xa0, BASS_GAIN_ADDR, &amp_userSet.ddx_Bass_lev, 1);
}

//volume control:  include master volume control and channel volume control
//input:
/*
updown:  1---boost,  -1---cut
mute:    1---Hard Master Mute,  0---not mute,adjust volume
*/
void ddx_master_volume_adjust(int updown,BYTE mute)
{
    BYTE tmp_var;
    
    if(mute)
    {
		amp_userSet.mainvol = 0xff;
		WriteToI2c(DDX8K_ADDR,MASTER_VOL_REG,&amp_userSet.mainvol,1);
		return;
    }
    else
    {
//    	ddx_masterMute(1);
		ReadFromI2c(DDX8K_ADDR,MASTER_VOL_REG,&amp_userSet.mainvol,1);
		tmp_var = amp_userSet.mainvol;
    	if(updown==1)
    	{
    		if(tmp_var>0x00)
    			tmp_var--;
    	}
    	else if(updown==-1)
    			tmp_var++;
    	if(*lev_list[0]==1)
    		tmp_var = 0x31;
    	else if(*lev_list[0]==0)
    		tmp_var = 0xff;
    	amp_userSet.mainvol = tmp_var;
    	WriteToI2c(DDX8K_ADDR,MASTER_VOL_REG,&amp_userSet.mainvol,1);
		WriteToI2c(0xa0,AMP_I2CADDR_START+(2*y_index),lev_list[y_index],1);
		WriteToI2c(0xa0,AMP_I2CADDR_START+(2*y_index + 1),&amp_userSet.mainvol,1);
//    	ddx_masterMute(0);
    }
}

//Set Master Volume Gain
void ddx_setMVG(BYTE chAddr,BYTE ctrl)
{
	WriteToI2c(DDX8K_ADDR,chAddr,&ctrl,1);
}
//input:
/*
chAddr:  channel volume regsiter address
updown:  1---boost,  -1---cut
*/

void ddx_channel_volume_adjust(BYTE chAddr,int updown)
{
//    UINT16      romSum=0;
    BYTE *p = (BYTE *)(&amp_userSet);
    BYTE tmp_var;
	
//	ddx_masterMute(1);
	ReadFromI2c(DDX8K_ADDR,chAddr,p,1);
	tmp_var = *(p+(2*y_index+1));
	if(updown==1)
	{
		if(tmp_var>0x00)
			tmp_var -=1;
	}
	else if(updown==-1)
	{
		if(tmp_var<0xfe)
			tmp_var +=1;
	}
	*(p+(2*y_index+1)) = tmp_var;
	WriteToI2c(DDX8K_ADDR,chAddr,(p+(2*y_index+1)),1);
	WriteToI2c(0xa0,AMP_I2CADDR_START+(2*y_index),lev_list[y_index],1);
	WriteToI2c(0xa0,AMP_I2CADDR_START+(2*y_index + 1),(p+(2*y_index+1)),1);
//	ddx_masterMute(0);
}

//Set Channel Volume Gain
void ddx_setCVG(BYTE chAddr,BYTE ctrl)
{
	WriteToI2c(DDX8K_ADDR,chAddr,&ctrl,1);
}

//all changes in volume take place at digital zero-crossing
//will create the smoothest possible volume transition
void ddx_enZeroCross(void)
{
	write_reg_bit(CONFIGREG_B,6,1);
}
void ddx_disZeroCross(void)
{//volume updates immediately
	write_reg_bit(CONFIGREG_B,6,0);
}

//Master Volume Mute
//mute all channels simultaneously
//mute   1: mute       0: demute
void ddx_masterMute(BYTE mute)
{
	if(mute)
		write_reg_bit(MASTER_MUTE_REG,0,1);
	else
		write_reg_bit(MASTER_MUTE_REG,0,0);
}

//channel mute individually
//mute   1: mute       0: demute
void ddx_channelMute(BYTE chNum,BYTE mute)
{
	if(mute)
		write_reg_bit(CHANEL_MUTE_REG,chNum,1);
	else
		write_reg_bit(CHANEL_MUTE_REG,chNum,0);
}

//Channel Limiter Selection
/*
CxLS(1,0)   Channel Limiter Mapping
-------------------------------------------
   00       Channel has limiting disabled
   01       Channel is mapped to limiter #1
   10       Channel is mapped to limiter #2
   11       Reserved.Don't use this setting
--------------------------------------------
*/
void ddx_ch1_limiterSel(BYTE selCtrl)
{
	BYTE data;
	ReadFromI2c(DDX8K_ADDR,CLIMITER_SEL0,&data,1);
	data = selCtrl | (data & 0xfc); 
	if(selCtrl<0x03)
		WriteToI2c(DDX8K_ADDR,CLIMITER_SEL0,&data,1);
}

void ddx_ch2_limiterSel(BYTE selCtrl)
{
	BYTE data;
	ReadFromI2c(DDX8K_ADDR,CLIMITER_SEL0,&data,1);
	data = (selCtrl << 2) | (data & 0xf3); 
	if(selCtrl<0x03)
		WriteToI2c(DDX8K_ADDR,CLIMITER_SEL0,&data,1);
}

void ddx_ch3_limiterSel(BYTE selCtrl)
{
	BYTE data;
	ReadFromI2c(DDX8K_ADDR,CLIMITER_SEL0,&data,1);
	data = (selCtrl << 4) | (data & 0xcf); 
	if(selCtrl<0x03)
		WriteToI2c(DDX8K_ADDR,CLIMITER_SEL0,&data,1);
}
void ddx_ch4_limiterSel(BYTE selCtrl)
{
	BYTE data;
	ReadFromI2c(DDX8K_ADDR,CLIMITER_SEL0,&data,1);
	data = (selCtrl << 6) | (data & 0x3f); 
	if(selCtrl<0x03)
		WriteToI2c(DDX8K_ADDR,CLIMITER_SEL0,&data,1);
}
void ddx_ch5_limiterSel(BYTE selCtrl)
{
	BYTE data;
	ReadFromI2c(DDX8K_ADDR,CLIMITER_SEL1,&data,1);
	data = selCtrl | (data & 0xfc); 
	if(selCtrl<0x03)
		WriteToI2c(DDX8K_ADDR,CLIMITER_SEL1,&data,1);
}

void ddx_ch6_limiterSel(BYTE selCtrl)
{
	BYTE data;
	ReadFromI2c(DDX8K_ADDR,CLIMITER_SEL1,&data,1);
	data = (selCtrl << 2) | (data & 0xf3); 
	if(selCtrl<0x03)
		WriteToI2c(DDX8K_ADDR,CLIMITER_SEL1,&data,1);
}

void ddx_ch7_limiterSel(BYTE selCtrl)
{
	BYTE data;
	ReadFromI2c(DDX8K_ADDR,CLIMITER_SEL1,&data,1);
	data = (selCtrl << 4) | (data & 0xcf); 
	if(selCtrl<0x03)
		WriteToI2c(DDX8K_ADDR,CLIMITER_SEL1,&data,1);
}
void ddx_ch8_limiterSel(BYTE selCtrl)
{
	BYTE data;
	ReadFromI2c(DDX8K_ADDR,CLIMITER_SEL1,&data,1);
	data = (selCtrl << 6) | (data & 0x3f); 
	if(selCtrl<0x03)
		WriteToI2c(DDX8K_ADDR,CLIMITER_SEL1,&data,1);
}

//Set Compression and Release Rates of Limiter
void ddx_setL1CRrates(BYTE ctrl)
{
	WriteToI2c(DDX8K_ADDR,L1RATE_REG,&ctrl,1);
}

void ddx_setL2CRrates(BYTE ctrl)
{
	WriteToI2c(DDX8K_ADDR,L2RATE_REG,&ctrl,1);
}

//Set Compression and Release Threshold of Limiter
void ddx_setL1CRthreshold(BYTE ctrl)
{
	WriteToI2c(DDX8K_ADDR,L1THRESHOLDS_REG,&ctrl,1);
}

void ddx_setL2CRthreshold(BYTE ctrl)
{
	WriteToI2c(DDX8K_ADDR,L2THRESHOLDS_REG,&ctrl,1);
}

//Set Dynamic Range Compression mode
//drc: 1----Dynamic Range Compression mode
//     0----Anti-Clipping Mode(default)
void ddx_setDRCmode(BYTE drc)
{
	write_reg_bit(CONFIGREG_B,7,drc);
}

//Set Max Power Correction
void ddx_setMPC(void)
{
	write_reg_bit(CONFIGREG_A,7,1);
}
//Head Phone Enable or Disable
void ddx_enHeadPhone(void)
{
	write_reg_bit(CONFIGREG_A,6,1);
}
void ddx_disHeadPhone(void)
{
	write_reg_bit(CONFIGREG_A,6,0);
}

//AM Mode Enable or Disable
void ddx_enableAM_mode(void)
{
	write_reg_bit(CONFIGREG_F,3,1);
}
void ddx_disableAM_mode(void)
{
	write_reg_bit(CONFIGREG_F,3,0);
}

void ddx_set_BassManagement(void)
{
	coef_factor bass_coef;
	//set pre-scale factor
    ddx_writeCoefVal(0xd0,FL_SCALE_FACTOR);

    ddx_writeCoefVal(0xd1,FR_SCALE_FACTOR);

    ddx_writeCoefVal(0xd2,SL_SCALE_FACTOR);

    ddx_writeCoefVal(0xd3,SL_SCALE_FACTOR);

    ddx_writeCoefVal(0xd4,CE_SCALE_FACTOR);

    ddx_writeCoefVal(0xd5,LFE_SCALE_FACTOR);
    
	//set channel 1,2,3,4,5 filter coefficient
	bass_coef.b2 = HPF_COEF_B2;
	bass_coef.b0 = HPF_COEF_B0;
	bass_coef.a2 = HPF_COEF_A2;
	bass_coef.a1 = HPF_COEF_A1;
	bass_coef.b1 = HPF_COEF_B1;
	ddx_writeCoefValSets(0x00,bass_coef);
	ddx_writeCoefValSets(0x19,bass_coef);
	ddx_writeCoefValSets(0x32,bass_coef);
	ddx_writeCoefValSets(0x4b,bass_coef);
	ddx_writeCoefValSets(0x64,bass_coef);
	
	//set channel 6 filter coefficient
	bass_coef.b2 = LPF_COEF_B2;
	bass_coef.b0 = LPF_COEF_B0;
	bass_coef.a2 = LPF_COEF_A2;
	bass_coef.a1 = LPF_COEF_A1;
	bass_coef.b1 = LPF_COEF_B1;
	ddx_writeCoefValSets(0x7d,bass_coef);
}

//Initialize volume gain
void ddx_init_volumeGain(void)
{
	//set volume gain 
//	ddx_setMVG(MASTER_VOL_REG,0x2c/*-20dB*/);
//	ddx_setMVG(MASTER_VOL_REG,0x3c/*-30dB*/);
	ddx_setMVG(MASTER_VOL_REG,amp_userSet.mainvol);
	ddx_setCVG(C1V_REG,amp_userSet.lfrontvol);
	ddx_setCVG(C2V_REG,amp_userSet.rfrontvol);
	ddx_setCVG(C3V_REG,amp_userSet.lrearvol);
	ddx_setCVG(C4V_REG,amp_userSet.rrearvol);
	ddx_setCVG(C5V_REG,amp_userSet.centervol);
	ddx_setCVG(C6V_REG,amp_userSet.woofervol);
	ddx_setCVG(C7V_REG,0xff);
	ddx_setCVG(C8V_REG,0xff);

}
//Initialization
void ddx_initialization(void)
{
    printf("ddx_initialization()\n");
/*	//disable external amplifier
	ddx_disableEPAD();
	//mute all channels
	ddx_masterMute(1);
*/
	enable_hpf();
	NOP;
	set_inputClock(0x00,0x03);//256Fs
	NOP;
	//set input data format
	//set input data format   :DVD,VCD,MP3,CD,
#if defined(WM8746)//Right-Justified 24-bit Data
	set_inputData_format(0x05);
#elif defined(WM8746I2S24)//I2S 24-bit Data
	set_inputData_format(0x00);
#endif
//	BYTE data = 0x27;
//	WriteToI2c(DDX8K_ADDR,0x03,&data,1);
	
	//enable bass management
	ddx_enable_BassManagement();
	//Enable Zero Crossing
	ddx_enZeroCross();
	//set Anti-clipping Mode for 5.1 Channels
	ddx_setDRCmode(0);
	//initialize volume gain
	ddx_init_volumeGain();
	//set bass management
	ddx_set_BassManagement();
	//limiter selection: channel 1,2,3,4,5 select limiter 1
	//channel 6 select limiter 2
	ddx_ch1_limiterSel(0x01);
	ddx_ch2_limiterSel(0x01);
	ddx_ch3_limiterSel(0x01);
	ddx_ch4_limiterSel(0x01);
	ddx_ch5_limiterSel(0x01);
	ddx_ch6_limiterSel(0x02);
	//set limiter 1,2 Attack Rate and Release Rate
	ddx_setL1CRrates(0xa4);
	ddx_setL2CRrates(0xf7);
	//set limiter 1,2 Attack Threshold and Release Threshold
	ddx_setL1CRthreshold(0x65);
	ddx_setL1CRthreshold(0x75);
	
//	write_reg_bit(0x30,
//	BYTE data = 0x00;
//	WriteToI2c(DDX8K_ADDR,0x03,&data,1);
	//unmute all channels
//	ddx_enableAM_mode();
/*	NOP;
	ddx_masterMute(0);	
	NOP;
	ddx_enableEPAD();
*/
}
	
void ddx_ampvol_func_left(void);
void ddx_ampvol_func_right(void);
void ddx_ampvol_func_up(void);
void ddx_ampvol_func_down(void);
	
void ddx_volume_adjust(UINT32 key)
{
	switch(key)
	{
		case IRC_UP:
			ddx_ampvol_func_up();
			break;
		case IRC_DOWN:
			ddx_ampvol_func_down();
			break;
		case IRC_LEFT:
			ddx_ampvol_func_left();
			break;
		case IRC_RIGHT:
			ddx_ampvol_func_right();
			break;
	}
}

void load_amp_setup(void)//xyy 2004-1-13 10:20
{
    int iRts,i;
    BYTE tmp = 0;
    BYTE *p = (BYTE *)(&tmp);
    printf("-----*********------load_amp_setup()-----***********-------\n");
    iRts=ReadFromI2c(0xa0, AMP_I2CADDR_START, &amp_userSet, sizeof(amp_userSet));   
/*    
	ReadFromI2c(0xa0, BASS_GAIN_ADDR, &amp_userSet.ddx_Bass_lev, 1);   
    ReadFromI2c(0xa0, TREBLE_GAIN_ADDR, &amp_userSet.ddx_Treble_lev, 1);   
    ReadFromI2c(0xa0, DDX_EQ_TYPE_ADDR, &amp_userSet.ddx_EQ_sel, 1);   
    ReadFromI2c(0xa0, DDX_REVB_TYPE_ADDR, &amp_userSet.ddx_Revb_sel, 1);   
*/
    printf("===iRts : %d====\n",iRts);
    if(iRts<0)
    {
    	set_ampsetup_default();
		WriteToI2c(0xa0,AMP_I2CADDR_START,&amp_userSet,sizeof(amp_userSet));
    }
/*	printf("1=========channel mv volume is: %x========\n",amp_userSet.mainvol);
	printf("1=========channel 1 volume is: %x========\n",amp_userSet.lfrontvol);
	printf("1=========channel 2 volume is: %x========\n",amp_userSet.rfrontvol);
	printf("1=========channel 3 volume is: %x========\n",amp_userSet.lrearvol);
	printf("1=========channel 4 volume is: %x========\n",amp_userSet.rrearvol);
	printf("1=========channel 5 volume is: %x========\n",amp_userSet.centervol);
	printf("1=========channel 6 volume is: %x========\n",amp_userSet.woofervol);
*/
	WriteToI2c(DDX8K_ADDR,MASTER_VOL_REG,&amp_userSet.mainvol,1);
	WriteToI2c(DDX8K_ADDR,C1V_REG,&amp_userSet.lfrontvol,1);
	WriteToI2c(DDX8K_ADDR,C2V_REG,&amp_userSet.rfrontvol,1);
	WriteToI2c(DDX8K_ADDR,C3V_REG,&amp_userSet.lrearvol,1);
	WriteToI2c(DDX8K_ADDR,C4V_REG,&amp_userSet.rrearvol,1);
	WriteToI2c(DDX8K_ADDR,C5V_REG,&amp_userSet.centervol,1);
	WriteToI2c(DDX8K_ADDR,C6V_REG,&amp_userSet.woofervol,1);
	ddx_Set_EQ(amp_userSet.ddx_EQ_sel);
	 *p = (amp_userSet.ddx_Treble_lev<<4)|amp_userSet.ddx_Bass_lev;
	WriteToI2c(DDX8K_ADDR,TONE_CTRL_REG,p,1);
}	

/*****************************************
/Function: ddx_Set_EQ()
/Description: Set coefficient values of biquads for preset EQ settings. 
/Creator: xulf
/Date: 2003-12-27
/*****************************************/
void ddx_Set_EQ(BYTE EQtype)
{
    coef_factor biquad_coef;
//    ddx_disableEPAD();   //EAPD
    ddx_masterMute(1);  //mute all channels
    switch(EQtype)
    {
	case NONE:
	    //set the channel pre-scale. 
	    ddx_writeCoefVal(0xc8,0xe36809);  //channel 1 
    	biquad_coef.b2 = 0x000000;
	    biquad_coef.b0 = 0x3fffff;
	    biquad_coef.a2 = 0x000000;
	    biquad_coef.a1 = 0x000000;
	    biquad_coef.b1 = 0x000000;
	    ddx_writeCoefValSets(0x05,biquad_coef);  //channel 1 biquad2
	    ddx_writeCoefValSets(0x0a,biquad_coef);  //channel 1 biquad3	    
	    ddx_writeCoefValSets(0x0f,biquad_coef);  //channel 1 biquad4	    
	    ddx_writeCoefValSets(0x14,biquad_coef);  //channel 1 biquad5
	    //each channel uses channel 1 coefficient values.
    	write_reg_bit(CONFIGREG_D,7,1); 	
	    break;	
	case ROCK:
	    ddx_writeCoefVal(0xc8,0xaf3cc5);  //channel 1 
	    biquad_coef.b2 = 0x7fcf05;
	    biquad_coef.b0 = 0x40058a;
	    biquad_coef.a2 = 0x8025e6;
	    biquad_coef.a1 = 0x7fed02;
	    biquad_coef.b1 = 0x8012fe;
	    ddx_writeCoefValSets(0x05,biquad_coef);  //channel 1 biquad2
    	biquad_coef.b2 = 0x7fd80a;
	    biquad_coef.b0 = 0x4006a3;
	    biquad_coef.a2 = 0x801aaf;
	    biquad_coef.a1 = 0x7ff28c;
	    biquad_coef.b1 = 0x800d74;
	    ddx_writeCoefValSets(0x0a,biquad_coef);  //channel 1 biquad3	    
    	biquad_coef.b2 = 0x7ead9f;
	    biquad_coef.b0 = 0x3fc7c8;
	    biquad_coef.a2 = 0x81c2d0;
	    biquad_coef.a1 = 0x7f1d06;
	    biquad_coef.b1 = 0x80e2fa;
	    ddx_writeCoefValSets(0x0f,biquad_coef);  //channel 1 biquad4	    
    	biquad_coef.b2 = 0x5d3dab;
	    biquad_coef.b0 = 0x46a5ae;
	    biquad_coef.a2 = 0x9576f8;
	    biquad_coef.a1 = 0x714597;
	    biquad_coef.b1 = 0x8eba69;
	    ddx_writeCoefValSets(0x14,biquad_coef);  //channel 1 biquad5
	    //each channel uses channel 1 coefficient values.
    	write_reg_bit(CONFIGREG_D,7,1); 	
	    break;	
	case POP:
	    ddx_writeCoefVal(0xc8,0xdb759b);  //channel 1 
    	biquad_coef.b2 = 0x7fe781;
	    biquad_coef.b0 = 0x3ffd3a;
	    biquad_coef.a2 = 0x801e09;
	    biquad_coef.a1 = 0x7ff0f8;
	    biquad_coef.b1 = 0x800f08;
	    ddx_writeCoefValSets(0x05,biquad_coef);  //channel 1 biquad2
    	biquad_coef.b2 = 0x7cc19b;
	    biquad_coef.b0 = 0x40e89e;
	    biquad_coef.a2 = 0x816d29;
	    biquad_coef.a1 = 0x7f40df;
	    biquad_coef.b1 = 0x80bf21;
	    ddx_writeCoefValSets(0x0a,biquad_coef);  //channel 1 biquad3	    
    	biquad_coef.b2 = 0x640c0d;
	    biquad_coef.b0 = 0x3cd666;
	    biquad_coef.a2 = 0xa24727;
	    biquad_coef.a1 = 0x6cbb1a;
	    biquad_coef.b1 = 0x9344e6;
	    ddx_writeCoefValSets(0x0f,biquad_coef);  //channel 1 biquad4	    
    	biquad_coef.b2 = 0x4274ad;
	    biquad_coef.b0 = 0x37613b;
	    biquad_coef.a2 = 0xcec8dd;
	    biquad_coef.a1 = 0x4cbc8c;
	    biquad_coef.b1 = 0xb34374;
	    ddx_writeCoefValSets(0x14,biquad_coef);  //channel 1 biquad5
	    //each channel uses channel 1 coefficient values.
    	write_reg_bit(CONFIGREG_D,7,1); 
	    break;
	case PARTY:
	    ddx_writeCoefVal(0xc8,0xe4a917);  //channel 1 
    	biquad_coef.b2 = 0x7fc83b;
	    biquad_coef.b0 = 0x400e7c;
	    biquad_coef.a2 = 0x801acd;
	    biquad_coef.a1 = 0x7ff297;
	    biquad_coef.b1 = 0x800d69;
	    ddx_writeCoefValSets(0x05,biquad_coef);  //channel 1 biquad2
    	biquad_coef.b2 = 0x7f4db3;
	    biquad_coef.b0 = 0x402e50;
	    biquad_coef.a2 = 0x8055ad;
	    biquad_coef.a1 = 0x7fd50c;
	    biquad_coef.b1 = 0x802af4;
	    ddx_writeCoefValSets(0x0a,biquad_coef);  //channel 1 biquad3	    
    	biquad_coef.b2 = 0x7908a0;
	    biquad_coef.b0 = 0x412849;
	    biquad_coef.a2 = 0x84a6cc;
	    biquad_coef.a1 = 0x7d8082;
	    biquad_coef.b1 = 0x827f7e;
	    ddx_writeCoefValSets(0x0f,biquad_coef);  //channel 1 biquad4	    
    	biquad_coef.b2 = 0x2688b9;
	    biquad_coef.b0 = 0x4edd22;
	    biquad_coef.a2 = 0xbbbd01;
	    biquad_coef.a1 = 0x4dda39;
	    biquad_coef.b1 = 0xb225c7;
	    ddx_writeCoefValSets(0x14,biquad_coef);  //channel 1 biquad5
	    //each channel uses channel 1 coefficient values.
    	write_reg_bit(CONFIGREG_D,7,1); 	
	    break;
	    case DANCE:
	    ddx_writeCoefVal(0xc8,0xddef46);  //channel 1 
    	biquad_coef.b2 = 0x7fd0f2;
	    biquad_coef.b0 = 0x400a20;
	    biquad_coef.a2 = 0x801acd;
	    biquad_coef.a1 = 0x7ff297;
	    biquad_coef.b1 = 0x800d69;
	    ddx_writeCoefValSets(0x05,biquad_coef);  //channel 1 biquad2
    	biquad_coef.b2 = 0x7f2132;
	    biquad_coef.b0 = 0x4039df;
	    biquad_coef.a2 = 0x806b0f;
	    biquad_coef.a1 = 0x7fca4b;
	    biquad_coef.b1 = 0x8035b5;
	    ddx_writeCoefValSets(0x0a,biquad_coef);  //channel 1 biquad3	    
    	biquad_coef.b2 = 0x7a469f;
	    biquad_coef.b0 = 0x40cd3f;
	    biquad_coef.a2 = 0x841ee2;
	    biquad_coef.a1 = 0x7ddf4c;
	    biquad_coef.b1 = 0x8220b4;
	    ddx_writeCoefValSets(0x0f,biquad_coef);  //channel 1 biquad4	    
    	biquad_coef.b2 = 0x2ca6df;
	    biquad_coef.b0 = 0x4dd8f0;
	    biquad_coef.a2 = 0xb7a741;
	    biquad_coef.a1 = 0x534a84;
	    biquad_coef.b1 = 0xacb57c;
	    ddx_writeCoefValSets(0x14,biquad_coef);  //channel 1 biquad5
	    //each channel uses channel 1 coefficient values.
    	write_reg_bit(CONFIGREG_D,7,1); 
	    break;
	case HARD:
	    ddx_writeCoefVal(0xc8,0xdfd91e);  //channel 1 
    	biquad_coef.b2 = 0x7fdeb7;
	    biquad_coef.b0 = 0x400729;
	    biquad_coef.a2 = 0x8012f5;
	    biquad_coef.a1 = 0x7ff683;
	    biquad_coef.b1 = 0x80097d;
	    ddx_writeCoefValSets(0x05,biquad_coef);  //channel 1 biquad2
    	biquad_coef.b2 = 0x7fbd74;
	    biquad_coef.b0 = 0x400e52;
	    biquad_coef.a2 = 0x8025e6;
	    biquad_coef.a1 = 0x7fed02;
	    biquad_coef.b1 = 0x8012fe;
	    ddx_writeCoefValSets(0x0a,biquad_coef);  //channel 1 biquad3	    
    	biquad_coef.b2 = 0x007c0c;
	    biquad_coef.b0 = 0x662860;
	    biquad_coef.a2 = 0xb33334;
	    biquad_coef.a1 = 0x58ae56;
	    biquad_coef.b1 = 0xa751aa;
	    ddx_writeCoefValSets(0x0f,biquad_coef);  //channel 1 biquad4	    
    	biquad_coef.b2 = 0x000000;
	    biquad_coef.b0 = 0x3fffff;
	    biquad_coef.a2 = 0x000000;
	    biquad_coef.a1 = 0x000000;
	    biquad_coef.b1 = 0x000000;
	    ddx_writeCoefValSets(0x14,biquad_coef);  //channel 1 biquad5
	    //each channel uses channel 1 coefficient values.
    	write_reg_bit(CONFIGREG_D,7,1); 	    
	    break;
	case CLASSIC:
	    ddx_writeCoefVal(0xc8,0xaf3cc5);  //channel 1 
    	biquad_coef.b2 = 0x7f4977;
	    biquad_coef.b0 = 0x400f9b;
	    biquad_coef.a2 = 0x809753;
	    biquad_coef.a1 = 0x7fb3a3;
	    biquad_coef.b1 = 0x804c5d;
	    ddx_writeCoefValSets(0x05,biquad_coef);  //channel 1 biquad2
    	biquad_coef.b2 = 0x7b9d6f;
	    biquad_coef.b0 = 0x40ba80;
	    biquad_coef.a2 = 0x82ed90;
	    biquad_coef.a1 = 0x7e77e0;
	    biquad_coef.b1 = 0x818820;
	    ddx_writeCoefValSets(0x0a,biquad_coef);  //channel 1 biquad3	    
    	biquad_coef.b2 = 0x4e4a5f;
	    biquad_coef.b0 = 0x459fbc;
	    biquad_coef.a2 = 0xa67628;
	    biquad_coef.a1 = 0x5e3269;
	    biquad_coef.b1 = 0xa1cd97;
	    ddx_writeCoefValSets(0x0f,biquad_coef);  //channel 1 biquad4	    
    	biquad_coef.b2 = 0x000000;
	    biquad_coef.b0 = 0x3fffff;
	    biquad_coef.a2 = 0x000000;
	    biquad_coef.a1 = 0x000000;
	    biquad_coef.b1 = 0x000000;
	    ddx_writeCoefValSets(0x14,biquad_coef);  //channel 1 biquad5
	    //each channel uses channel 1 coefficient values.
    	write_reg_bit(CONFIGREG_D,7,1); 
	    break;
	case SOFT:
	    ddx_writeCoefVal(0xc8,0xd77b6);  //channel 1 
    	biquad_coef.b2 = 0x7fdd5d;
	    biquad_coef.b0 = 0x4003eb;
	    biquad_coef.a2 = 0x801acd;
	    biquad_coef.a1 = 0x7ff297;
	    biquad_coef.b1 = 0x800d69;
	    ddx_writeCoefValSets(0x05,biquad_coef);  //channel 1 biquad2
    	biquad_coef.b2 = 0x7fa8c6;
	    biquad_coef.b0 = 0x4009de;
	    biquad_coef.a2 = 0x80437d;
	    biquad_coef.a1 = 0x7fde2f;
	    biquad_coef.b1 = 0x8021d1;
	    ddx_writeCoefValSets(0x0a,biquad_coef);  //channel 1 biquad3	    
    	biquad_coef.b2 = 0x7d21e7;
	    biquad_coef.b0 = 0x3f992d;
	    biquad_coef.a2 = 0x83abbd;
	    biquad_coef.a1 = 0x7e25ce;
	    biquad_coef.b1 = 0x81da32;
	    ddx_writeCoefValSets(0x0f,biquad_coef);  //channel 1 biquad4	    
    	biquad_coef.b2 = 0x157218;
	    biquad_coef.b0 = 0x5bad59;
	    biquad_coef.a2 = 0xb33334;
	    biquad_coef.a1 = 0x58ae56;
	    biquad_coef.b1 = 0xa751aa;
	    ddx_writeCoefValSets(0x14,biquad_coef);  //channel 1 biquad5
	    //each channel uses channel 1 coefficient values.
    	write_reg_bit(CONFIGREG_D,7,1); 
	    break;
	default:
    }	
//    ddx_enableEPAD();   //unEAPD
    ddx_masterMute(0);  //demute all channels			
}

/******************************************
/Function: ddx_TunerOutput_VSS()
/description: Specific stereo to "virtual 5.1 effect" 
			setting for tuner input mode 
/creator: xulf 
/date: 2003-12-24
/******************************************/
void ddx_TunerOutput_VSS(void)
{
    BYTE data;
    coef_factor bass_coef;
    
    ddx_disableEPAD();   //EAPD
    ddx_masterMute(1);  //mute all channels
    //disable bass management mode
    ddx_disable_BassManagement();
    //enable adjacent channel-mixing mode
    write_reg_bit(CONFIGREG_E,0,1);

    //SDI_12-->LT/RT; SDI_34-->0; SDI_56-->0; SDI_78-->0
    //7 5 4 2 1 6-->FL FR VirtualCE  VirtualSL VirtualSR VirtualSW
	data = 0x01;
	WriteToI2c(DDX8K_ADDR,C12MAP_REG,&data,1);
	data = 0x01;
	WriteToI2c(DDX8K_ADDR,C34MAP_REG,&data,1);
	data = 0x01;
	WriteToI2c(DDX8K_ADDR,C56MAP_REG,&data,1);
	data = 0x00;
	WriteToI2c(DDX8K_ADDR,C78MAP_REG,&data,1);
    
    //set pre-scale factor
    ddx_writeCoefVal(0xd0,0x000000);  //X-Full attenuation
    ddx_writeCoefVal(0xd1,0x7FFFFF);  //0dB
    ddx_writeCoefVal(0xd2,0x400000);  //-6dB
    ddx_writeCoefVal(0xd3,0x400000);
    ddx_writeCoefVal(0xd4,0x400000);
    ddx_writeCoefVal(0xd5,0x400000);
    ddx_writeCoefVal(0xd6,0x000000);
    
    //set channel 7,5,4,2,1 filter coefficient
    bass_coef.b2 = HPF_COEF_B2;
    bass_coef.b0 = HPF_COEF_B0;
    bass_coef.a2 = HPF_COEF_A2;
    bass_coef.a1 = HPF_COEF_A1;
    bass_coef.b1 = HPF_COEF_B1;
    ddx_writeCoefValSets(0x96,bass_coef);  //channel 7    xulf 2003-12-15
    ddx_writeCoefValSets(0x64,bass_coef);  //channel 5
    ddx_writeCoefValSets(0x4b,bass_coef);  //channel 4
    ddx_writeCoefValSets(0x19,bass_coef);  //channel 2
    ddx_writeCoefValSets(0x00,bass_coef);  //channel 1
	
    //set channel 6 filter coefficient
    bass_coef.b2 = LPF_COEF_B2;
    bass_coef.b0 = LPF_COEF_B0;
    bass_coef.a2 = LPF_COEF_A2;
    bass_coef.a1 = LPF_COEF_A1;
    bass_coef.b1 = LPF_COEF_B1;
    ddx_writeCoefValSets(0x7d,bass_coef);    
	
    ddx_enableEPAD();   //unEAPD
    ddx_masterMute(0);  //demute all channels
    
}


