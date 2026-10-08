#ifdef HC165
#define HC165_NOP delay_1us(2)

#define HC165_SH_LD   98   // pin231
#define HC165_DAT   8   // DFCT pin65
#define HC165_CLK   100  //pin233

#define HC165_SH_LD_INIT {GPIO_M_SET(HC165_SH_LD,1);GPIO_E_SET(HC165_SH_LD, 1);}
#define HC165_DAT_INIT {GPIO_M_SET(HC165_DAT,1);GPIO_E_SET(HC165_DAT, 0);}
#define HC165_CLK_INIT {GPIO_M_SET(HC165_CLK,1);GPIO_E_SET(HC165_CLK, 1);}

#define HC165_SH_LD_SET(d) GPIO_O_SET(HC165_SH_LD, d)
#define HC165_DAT_GET() GPIO_I_GET(HC165_DAT)
#define HC165_CLK_SET(d) GPIO_O_SET(HC165_CLK, d)

void hc165_set_cfg(void)
{
	regs0->sft_cfg7 &= ~(0x17<<1);
	regs0->sft_cfg0 &= (~(0x01<<14))|(0x01<<11);
	regs0->fm_gpio_len &= ~(0x0f);

	regs0->sft_cfg2 &= ~(0x03<<10);
	regs0->sft_cfg4 &= ~(0x01<<6);
	regs0->sft_cfg8 &= ~(0x01<<9);
}

/*
74HC165 -- 8 bits parallel load shift register 
return
Q0--Q7
bit 0--bit 7

SH_LD:  ~~~~~\__/~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CLK:    ______________/~\___/~\___/~\___/~\___/~\___/~\___/~\___/~\__
DAT:    -----------[0]---[1]---[2]---[3]---[4]---[5]---[6]---[7]-----


*/
BYTE hc165_get_io(void)
{
	BYTE i;
	BYTE data = 0;

	hc165_set_cfg();
	HC165_SH_LD_INIT;
	HC165_DAT_INIT;
	HC165_CLK_INIT;

	HC165_SH_LD_SET(1);
	HC165_CLK_SET(0);
	HC165_SH_LD_SET(0);
	HC165_NOP;
	HC165_CLK_SET(1);
	HC165_NOP;
	HC165_SH_LD_SET(1);
	HC165_CLK_SET(0);
	HC165_NOP;
	for(i = 0;i < 8;i++)
	{
		if(HC165_DAT_GET())
		{
			data |= (0x01<<i);
		}

		HC165_CLK_SET(1);
		HC165_NOP;

		HC165_CLK_SET(0);
		HC165_NOP;
	}
	printf("74hc165 data:%x\n",data);
	return data;
}
#endif  //HC165

