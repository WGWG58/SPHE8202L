#include "config.h"
#include "regmap.h"
#include "global.h"
#include "sio.h"
#include "epp.h"
#include "func.h"
#include "memmap.h"

#ifdef CS8403_ENABLE

#define CS8403A_BASE_64     (32)		//32 * 64K(2^16)
#define CS8403A_BASE_S      (ROM_BASE_UNCACHED | ((CS8403A_BASE_64*2)<<16))
//#define CS8403A_BASE_64     (0x100)		//32 * 64K(2^16)
//#define CS8403A_BASE_S      (ROM_BASE_UNCACHED | (0x1000000) )

void write_cs8403a(BYTE StartAdd,BYTE CmdData);



static	inline	void	SET_RW_0(void)
{
    
    
    #ifdef SPHE8202
   // GPIO_O_SET(17,0);
    
    GPIO_O_SET(16,0);
    #else
    regs0->gpio_out[55 / 16] &= ~(0x1 << (55 % 16));
    #endif
    
    
}



static	inline	void	SET_RW_1(void)
{
    #ifndef SPHE8202
    regs0->gpio_out[55 / 16] |= (0x1 << (55 % 16));
    #endif
    //GPIO_O_SET(17,1);
    //delay_1ms(10);
    GPIO_O_SET(16,1);
    
    
}



static inline void init_cs8403a(void)
{
    //UINT32	u;
    BYTE 		i;
  
    write_cs8403a(1,0x00);
    //write_cs8403a(2,0x80);//CHIP DIABLE and MUTE
    write_cs8403a(2,0x83);//CHIP ENABLE and MUTE
    write_cs8403a(3,0x0D);//I2S LEft alignment
  
    write_cs8403a(4,0x00);//USER data
    write_cs8403a(5,0x00);//USER data
    write_cs8403a(6,0x00);//USER data
    write_cs8403a(7,0x00);//USER data	
  
    write_cs8403a(8,0x00);//CHANELL STATUS
    write_cs8403a(9,0x98);//CHANELL STATUS
    write_cs8403a(10,0x00);//CHANELL STATUS
    write_cs8403a(11,0x40);//CHANELL STATUS 48kHZ
    //write_cs8403a(11,0x00);//CHANELL STATUS 44kHZ

    for(i=12;i<32;i++)
    {
    	
        write_cs8403a(i,0x00);//CHANELL STATUS	
        
    }
    
    regs0->sft_cfg1=regs0->sft_cfg1&(~(1<<0x02));//pin77,GPIO 17
    GPIO_M_SET(17,1);
    GPIO_E_SET(17,1);
	GPIO_O_SET(17,1);
    
}	



void init_cs8403a__(void)
{
    BYTE i;

    regs0->rom1_base	= CS8403A_BASE_64;
    regs0->rom2_base	= CS8403A_BASE_64*2;
    regs0->rom3_base	= CS8403A_BASE_64*3;

	#ifdef SPHE8202
    regs0->sft_cfg1=regs0->sft_cfg1&(~(1<<0x03));//pin76,GPIO 16
	GPIO_M_SET(16,1);
    GPIO_E_SET(16,1);
	//regs0->sft_cfg1=regs0->sft_cfg1&(~(1<<0x02));//pin77,GPIO 17
	regs0->sft_cfg1=regs0->sft_cfg1|((1<<0x02));//pin77,GPIO 17
	//GPIO_M_SET(17,1);
    //GPIO_E_SET(17,1);
	//GPIO_O_SET(17,1);
	#else
	regs0->sft_cfg1 |= (0x7<<1);
	#endif
	
	
	
    for(i=0;i<2;i++)
    {
    	
        init_cs8403a();
        
        
        
    }
}


void write_cs8403a(BYTE StartAdd,BYTE CmdData)
{
    BYTE 		*sndPtr;	//write pointer   

    sndPtr = (BYTE *)(CS8403A_BASE_S+StartAdd);

    SET_RW_0();
       
    *sndPtr= CmdData;

    SET_RW_1();
}	


#endif

