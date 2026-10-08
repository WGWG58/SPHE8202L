#ifdef PT2258
#define PT2258_ADDR  0x88

#define  PT2258_ALL_1dB  0xe0
#define  PT2258_ALL_10dB  0xd0
#define  PT2258_CH1_1dB  0x90
#define  PT2258_CH1_10dB  0x80
#define  PT2258_CH2_1dB  0x50
#define  PT2258_CH2_10dB  0x40
#define  PT2258_CH3_1dB  0x10
#define  PT2258_CH3_10dB  0x00
#define  PT2258_CH4_1dB  0x30
#define  PT2258_CH4_10dB  0x20
#define  PT2258_CH5_1dB  0x70
#define  PT2258_CH5_10dB  0x60
#define  PT2258_CH6_1dB  0xb0
#define  PT2258_CH6_10dB  0xa0
#define  PT2258_CLR_ALL  0xf0
#define  PT2258_MUTE_ALL  0xf9
#define  PT2258_UNMUTE_ALL  0xf8


BYTE channel_reg[14] ={
	PT2258_ALL_1dB,PT2258_ALL_10dB,
	PT2258_CH1_1dB,PT2258_CH1_10dB,
	PT2258_CH2_1dB,PT2258_CH2_1dB,
	PT2258_CH3_1dB,PT2258_CH3_10dB,
	PT2258_CH4_1dB,PT2258_CH4_10dB,
	PT2258_CH5_1dB,PT2258_CH5_10dB,
	PT2258_CH6_1dB,PT2258_CH6_10dB,
};





/*
channel: 0--6
 0-->main vol
 1-6->sub channel vol
vol:0-->79dB
*/
void subvol_channel_volume(BYTE channel,BYTE vol)
{
	BYTE data1,data2;
	vol = 79 -vol;
	vol = bin2bcd(vol);
	
	data1 = channel_reg[channel*2];
	data1 |=(0x0f&vol);
	data2 = channel_reg[channel*2+1];
	data2 |= (0x0f&(vol>>4));
	WriteToI2c(PT2258_ADDR, data1, &data2, 1);
}

void init_pt2258(void)
{
	BYTE data1,data2,ch;
	
	data1 = PT2258_CLR_ALL;
	data2 = PT2258_UNMUTE_ALL;
	WriteToI2c(PT2258_ADDR,data1,&data2,1);
}



#endif

