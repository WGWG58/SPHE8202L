#include "setup_VA.h"
/*
history:
2004-7-19 14:43
         wanghaoying move the following functions for nec16312 here
2004-7-7 14:25  
        lijd
        Process 16312sw use for:
        1. extern pannel key
        2. volume button 
        note: need define NEC16312SW in cust_def.h
*/

/*
** FUNCTION
** reset_vfd
**
** DESCRIPTION
** setup VFD.  Should only called at power-up or emergency.
*/
void erase_vfd_mem2()
{  
    UINT8   i;
    for(i=0;i<5;i++)
    {
        vfd_mem2[i]=0; 
    } 
}

void reset_vfd(void)
{
    
	UINT16 nIndex = 0;
     
    erase_vfd_mem2();

	vfd_set_idle_state(nIndex);
	WaitIopFunRdy(IOP_RDY_WAIT);
}

//
//    LED: 
//
//    MSB   LSB
//    ---- 0000  turn on all led
//    ---- 1111  turn off all led
//
void write_vfd_led(UINT8 led_id)
{
	regs0->iop_data[VFD_CMD] = 0x41;
	regs0->iop_data[VFD_DAT0] = 0xff00 | led_id;
	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) | (FUN_VFD_WRITE | VFD_DAT_LEN1);
	WaitIopFunRdy(IOP_RDY_WAIT);
}


/*
** FUNCTION
** polling_vfdr
**
** DESCRIPTION
** check if polling-ready
*/

void polling_vfdr(void)  //nec16321 type vfd
{
#ifdef SUPPORT_VFD

	static UINT8   prologic_cmdflag=0;
	static UINT8   downmix_cmdflag=0;
	//UINT32  temp;
	//UINT32  key_data;
	 UINT8 count ;
	//static UINT32 key_previ = 0;
	
	//static BYTE bWriteState=0;
	static  UINT8	flag_init_cnt=5;	
	
	UINT8 *VfdReadData;
   // UINT8 *VfdReadData2;

    
	
	if(regs0->iop_data[0] & 0xf000)
		return;
       
	
	update_vfd_data();
					
   // VfdReadData2 = ((UINT8 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x01ff));      
	VfdReadData = ((UINT8 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x05E0));		

//	*VfdReadData=4; 
//	 VfdReadData++;  
//	*VfdReadData=*VfdReadData2;
//	 VfdReadData++;
//	*VfdReadData=5;
//	VfdReadData++;
//	*VfdReadData=*VfdReadData2;
	
	for(count=4;count<VFD_DISPLAY_SIZE-2;count++)
	{   
	    *VfdReadData=count; 
	     VfdReadData++;        
	   
	    if(count==0x10)
	    {
            *VfdReadData=vfd_mem[count]&0xFE;
        }
	    else
	    {   
	        *VfdReadData=vfd_mem[count];
        }        
        VfdReadData++;  
    }	
    	
	
				
	if(flag_init_cnt==0) 
    {  
        if(setup_VA[SET_VA_DEFAULT]==1)
        {     
            regs0->iop_data[2]= 0x1540;
            regs0->iop_data[0] = regs0->iop_data[0]|0x9000 ;
            setup_VA[SET_VA_DEFAULT]=0;
            printf("\r\n========================\r\n78E58 CMD OK:1540 \r\n============\r\n");
        }      
        else if (setup_VA[SETUP_VA_DOWNMIX]!=downmix_cmdflag)
        {   
            downmix_cmdflag=setup_VA[SETUP_VA_DOWNMIX];
            if(downmix_cmdflag!=4)
    	        regs0->iop_data[2]= 0x1520;
    	    else 
    	        regs0->iop_data[2]= 0x1580;
    	   
    	    regs0->iop_data[0] = regs0->iop_data[0]|0x9000 ;
           
        }      
        else  
            regs0->iop_data[0] = regs0->iop_data[0]|0x2000;
    
    }
	else //k==1
	{  
        //printf("-------------flag_init_cnt=1-----------------\n");

	   downmix_cmdflag=setup_VA[SETUP_VA_DOWNMIX];
	   if(downmix_cmdflag!=4)
	    {
	        //regs0->iop_data[2] = 0x0;
	        delay_srv_10ms(5);
	        printf(" send iop_data[2] 0x1520\n");
	        regs0->iop_data[2]= 0x1524;
	    }
	   else 
	    { 
	        //regs0->iop_data[2] = 0x0;
	        delay_srv_10ms(5);
	        printf(" send iop_data[2] 0x1580\n");
	        regs0->iop_data[2]= 0x1584; 
	    }
	   
	   regs0->iop_data[0] = regs0->iop_data[0]|0x9000 ;

        flag_init_cnt--; 
        printf("-------------flag_init_cnt=0-----------------\n");
    }
#endif//SUPPORT_VFD

}



