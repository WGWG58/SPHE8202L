
/*
** FUNCTION
** polling_vfdr
**
** DESCRIPTION
** check if polling-ready
** 
** history:
** 2004-7-19 15:17
** wanghaoying move the following functio for ht1621 here
*/
void reset_vfd(void)
{
	init_vfd_clear();
	regs0->iop_data[VFD_CMD]=(SPL10_DUTY_BIAS);	
	//regs0->iop_data[VFD_CMD]
	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
		(FUN_VFD_WRITE | VFD_DAT_LEN0);	
	WaitIopFunRdy(IOP_RDY_WAIT);
	regs0->iop_data[VFD_CMD]=(SPL10_KEY_MODE);	
	//regs0->iop_data[VFD_CMD]
	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
		(FUN_VFD_WRITE | VFD_DAT_LEN0); 	
	WaitIopFunRdy(IOP_RDY_WAIT);	
}

void polling_vfdr(void)  //HC164 type vfd
{
#ifdef SUPPORT_SPI_QSI
  //not use
#endif


#ifndef  SUPPORT_SPI_QSI

	
#ifdef SUPPORT_VFD
	UINT8   i;
	UINT32  temp;
	UINT32  key_data;
	static UINT8 count = 0;
	static UINT32 key_previ = 0;
	
	static BYTE bWriteState=0;
	
	
	UINT32 *VfdReadData;
	
	
	if(regs0->iop_data[0] & FUN_MASK)
		return;
	
	
	if(vfd_state == VFD_READ)
	{
		//read key data 		
		VfdReadData = ((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x588));

		//current is read 3 byte on io
		key_data = *VfdReadData & 0x000000ff;
		
		//if vfd is no connect, summer 20020912
		if(key_data != 0x0000ff)
			*VfdReadData = 0;					//clear key value            

		if(key_data != key_previ)
		{
			
			key_previ = key_data;
			
			if(key_data != 0)
			{

#ifdef VFD_KEY_TEST
				psprintf(RegionValStr[REGION1], "KEY %02d F:%d", key_data,
					vfd_keycode[key_data - 1]);
				PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
				
#else
				if((Is_JPEG_SlideMode()) && (vfd_keycode[key_data - 1] == IRC_PAUSE))
				{
					//Jeff 20020523
					bJpgVFDPause = 1;
				}
				else if((Is_JPEG_SlideMode()) &&
					((vfd_keycode[key_data - 1] == IRC_PLAY) ||
					(vfd_keycode[key_data - 1] == IRC_PLAY_SELECT) ||
					(vfd_keycode[key_data - 1] == IRC_PLAY_RESUME)))
				{
					//bJpgVFDPause=0;
					bJpgVFDPause = 2;			//Jeff 20020525
				}
				else if((Is_JPEG_SlideMode()) &&	//Jeff 20020527
					(vfd_keycode[key_data - 1] == IRC_PAUSEPLAY))
				{
					if(bJpgVFDPause == 0)
					{
						//bJpgVFDPause = 1;
						if(play_state == VCD_STATE_PAUSE)	//nono 2-6-28 14:00
							bJpgVFDPause = 2;
						else
							bJpgVFDPause = 1;
					}
					else if(bJpgVFDPause == 1)
					{
						bJpgVFDPause = 2;
					}
				}
				else if(key_data<40)
				{
					
					extern UINT8 power_on;
					
					if(power_on == 2)			//2-6-18 13:36 to avoid accepting a VFD_key in the beginning. 
					{
						power_on--;
						if(key_data != 1)
						{
							save_srn_start_t = get_rtc_val();
							call_ir_func(vfd_keycode[key_data - 1]);
						}
					}
					else
					{
						save_srn_start_t = get_rtc_val();
						call_ir_func(vfd_keycode[key_data - 1]);
					}
					
				}
#endif
			}
		}
		
		vfd_state = VFD_WRITE;
		update_vfd_data();
	}
	else
	{
		switch (bWriteState)
		{
		case 2:				
			
			regs0->iop_data[VFD_CMD] = (0xa0 | count);
			regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
			regs0->iop_data[VFD_DAT1] = vfd_mem[count + 3] << 8 | vfd_mem[count + 2];
			regs0->iop_data[VFD_DAT2] = vfd_mem[count + 5] << 8 | vfd_mem[count + 4];
			
			regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) | (FUN_VFD_WRITE | VFD_DAT_LEN6);
			
			/* transfer data size add by chichang 2001 6/6 */
			count += 6;
			if(count == VFD_DISPLAY_SIZE)
			{
				count = 0;
				vfd_state = VFD_READ;
			}
			
			bWriteState=2;
			break;
		default :
			bWriteState=2;	
		}//write state control
		
		
	}
#endif
#endif  //spi qsi
}