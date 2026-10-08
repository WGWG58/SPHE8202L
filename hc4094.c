#if defined(HC4094)||defined(USE_HC4094_IO_EXTEND)
#ifdef OP_HC4094_IO_EXTEND//lijd 2005-5-13 14:45
#define HC4094_STR   56   //pin176
#define HC4094_DAT   39   //pin142
#define HC4094_CLK   38   //pin141 
#else
#define HC4094_STR   98   // pin231
#define HC4094_DAT   99   // pin232
#define HC4094_CLK   100  //pin233
#endif

#define HC4094_STR_INIT {GPIO_M_SET(HC4094_STR,1);GPIO_E_SET(HC4094_STR, 1);}
#define HC4094_DAT_INIT {GPIO_M_SET(HC4094_DAT,1);GPIO_E_SET(HC4094_DAT, 1);}
#define HC4094_CLK_INIT {GPIO_M_SET(HC4094_CLK,1);GPIO_E_SET(HC4094_CLK, 1);}

#define HC4094_STR_SET(d) GPIO_O_SET(HC4094_STR, d)
#define HC4094_DAT_SET(d) GPIO_O_SET(HC4094_DAT, d)
#define HC4094_CLK_SET(d) GPIO_O_SET(HC4094_CLK, d)
#ifdef OP_HC4094_IO_EXTEND
#define READY		 (1<<0)
#define SCAT_DISP    (1<<1)
#define SCAT_SIG     (1<<2)
#define REL_SCAT     (1<<3)
#define AMUTE        (1<<4)
#else
#define AMP_STANDBY  (1<<0)
#define TUNER_ON     (1<<1)
#define SCA_DISP     (1<<2)
#define SCA_SIG      (1<<3)
#define REL_SCA      (1<<4)
#define SEL_B        (1<<5)
#define SEL_A        (1<<6)
#define AMP_MUTE     (1<<7)

#define HC4094_TUNER_MODE   (TUNER_ON|SEL_B)
#define HC4094_DVD_MODE     (SEL_B|SEL_A)
#define HC4094_AV1_MODE     (SEL_A)
#endif

void set_cfg(void)
{
	#ifdef OP_HC4094_IO_EXTEND
	regs0->sft_cfg0 &= ~(0x01<<5); //pin141
	regs0->sft_cfg0 &= ~(0x01<<4); //pin142
	regs0->sft_cfg3 &= ~(0x01<<4); //pin176
	#else
	regs0->sft_cfg7 &= ~(0x17<<1);
	regs0->sft_cfg0 &= (~(0x01<<14))|(0x01<<11);
	regs0->fm_gpio_len &= ~(0x0f);
	#endif
}

/*
74HC4094 -- 8 stage shit and store bus register ,three state
Q0--Q7
io bit 0--bit 7
*/
void hc4094_set_io(BYTE io)
{
	BYTE i;

	//regs0->sft_cfg6 &= ~(0x1 << 5); // SA12 as GPIO 18, pin 151
	//regs0->sft_cfg3 &= ~(0x1 << 5); // AU4 as GPIO 57, pin163
	set_cfg();
	HC4094_STR_INIT;
	HC4094_DAT_INIT;
	HC4094_CLK_INIT;

	HC4094_STR_SET(0);
	HC4094_CLK_SET(0);
	for(i=0;i<8;i++)
		{
		if(io&0x80)
			HC4094_DAT_SET(1);
		else
			HC4094_DAT_SET(0);
		io<<=1;
		HC4094_CLK_SET(1);
		HC4094_CLK_SET(0);
	}
	HC4094_STR_SET(1);
	HC4094_STR_SET(0);
}




#endif  //HC4094

