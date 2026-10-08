/*
** FUNCTION
** polling_vfdr
**
** DESCRIPTION
** check if polling-ready
** 
** history:
** 2004-7-19 15:09
** wanghaoying move the following functio for ht1621 here
*/
void reset_vfd(void)   //for ht1621 init 
{
	//#ifdef SUPPORT_VFD
	
	
	
	/* display mode ? 13d15s or 6d16s add by chichang 2001/6/6 */
	/*i want use arry and for statement to send init command
	but it's something wrong,so only do this.
	*/
	regs0->iop_data[VFD_CMD]=(SYS_EN<<4);	

	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
		(FUN_VFD_WRITE | VFD_DAT_LEN0);
	WaitIopFunRdy(IOP_RDY_WAIT); 
	regs0->iop_data[VFD_CMD]=(TIMER_DIS<<4);	

	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
		(FUN_VFD_WRITE | VFD_DAT_LEN0);
	WaitIopFunRdy(IOP_RDY_WAIT);
	regs0->iop_data[VFD_CMD]=(WDT_DIS<<4);	

	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
		(FUN_VFD_WRITE | VFD_DAT_LEN0);
	WaitIopFunRdy(IOP_RDY_WAIT);
	regs0->iop_data[VFD_CMD]=(BIAS_1_3<<4);	

	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
		(FUN_VFD_WRITE | VFD_DAT_LEN0);
	WaitIopFunRdy(IOP_RDY_WAIT);
	regs0->iop_data[VFD_CMD]=(LCD_ON<<4);	

	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
		(FUN_VFD_WRITE | VFD_DAT_LEN0);
	WaitIopFunRdy(IOP_RDY_WAIT);                    
	init_vfd_clear();     
	
}

void polling_vfdr(void)    //ht1621 type vfd
{
    
#ifdef SUPPORT_SPI_QSI
  //not use
#endif


#ifndef  SUPPORT_SPI_QSI

    
    
#ifdef CF_GPIO_CONTROL_COLOR	
    Polling_VFD_back_color();	
#endif

#ifdef SUPPORT_VFD

	static UINT8 count = 0;
	static BYTE bWriteState=0;
	
	
	//UINT32 *VfdReadData;
	
	
	if(regs0->iop_data[0] & FUN_MASK)
		return;
	
				
	if(vfd_state == VFD_READ)  //we only use it to update vfd data
	{
		vfd_state = VFD_WRITE;
		update_vfd_data();	
	}
	else
	{
		
		switch (bWriteState)
		{
			
		case 2:				
			
			regs0->iop_data[VFD_CMD] = (count*2);//in cmd we only send address! write cmd deal in iop!
			regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
			regs0->iop_data[VFD_DAT1] = vfd_mem[count + 3] << 8 | vfd_mem[count + 2];
			//regs0->iop_data[VFD_DAT2] = vfd_mem[count + 5] << 8 | vfd_mem[count + 4];
			
			regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
				(FUN_VFD_WRITE | VFD_DAT_LEN4);
			
			/* transfer data size add by chichang 2001 6/6 */
			count += 4;
			
			if(count == VFD_DISPLAY_SIZE)//vfd_display_size
			{
				count = 0;
				vfd_state = VFD_READ;
			}
			
			bWriteState=2;
			break;
		default:
			bWriteState=2;
		}//write state control
	}
#endif//SUPPORT_VFD
#endif  // support spi qsi
}


void write_vfd_led(UINT8 led_id)
{
}
