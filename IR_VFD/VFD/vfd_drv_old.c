  
/*
** FUNCTION
** polling_vfdr
**
** DESCRIPTION
** check if polling-ready
*/
void polling_vfdr(void)
{
	
#ifdef SUPPORT_SPI_QSI
  //not use
#endif


#ifndef  SUPPORT_SPI_QSI


    
#ifdef SUPPORT_VFD
	UINT8   i;
	UINT32  temp;
	UINT32  key_data;
	static UINT8 key_state = 0, count = 0;
	static UINT32 key_previ = 0;
	
	
	if(regs0->iop_data[0] & FUN_MASK)
		return;
	
	if(vfd_state == VFD_READ)
	{
		regs0->iop_data[VFD_CMD] = 0x42;	//key polling
		regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
			(FUN_VFD_READ | 3);
		
		vfd_state = VFD_READ_BUSY;
	}
	else if(vfd_state == VFD_READ_BUSY)
	{
		
		key_data =
			(reverse_fun(regs0->iop_data[VFD_DAT0])) |
			(reverse_fun(regs0->iop_data[VFD_DAT0] >> 8) << 8) |
			(reverse_fun(regs0->iop_data[VFD_DAT1]) << 16);
		
		//printf("key_data=%x\n",key_data);
		//if (key_data == 0xffffff) 
		//{
		//break; //VFD buttons are pulled-high, if we don't connect VFD, we skip it, Jeff 20020612
		//printf("polling_vfdr:return\n");
		//return;
		//}           
		
		if(key_data == 0)
		{
			key_state = 0;
			key_previ = 0;
		}
		else
		{
			if(key_data != key_previ)
			{
				key_state = 1;
				key_previ = key_data;
			}
			else
			{
				if(key_state == 1)
				{
					key_state = 2;
					
					for(i = 0; i < 24; i++)
					{
						temp = 0x01 << i;
						if(key_data & temp)
						{
							if (key_data > temp) // Robert 030224 for preventing illegal key_data
							{
								key_data = 0;
								return;
							}
							else
							{
								key_data = i + 1;
								break;
							}
						}
					}
                                        save_srn_start_t = get_rtc_val();//axel 2004/1/15 05:31,avoid looping PAUSE<->PLAY VFD key and entering screen saver				
#ifdef VFD_KEY_TEST
					psprintf(RegionValStr[REGION1], "KEY %02d F:%d", key_data,
						vfd_keycode[key_data - 1]);
					PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
					
#else
					if((Is_JPEG_SlideMode()) &&
						(vfd_keycode[key_data - 1] == IRC_PAUSE))
					{											//Jeff 20020523
						bJpgVFDPause = 1;
					}
					else if((Is_JPEG_SlideMode()) &&
						((vfd_keycode[key_data - 1] == IRC_PLAY) ||
						(vfd_keycode[key_data - 1] == IRC_PLAY_SELECT) ||
						(vfd_keycode[key_data - 1] == IRC_PLAY_RESUME)))
					{
						//bJpgVFDPause=0;
						bJpgVFDPause = 2;		//Jeff 20020525
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
						
						if(power_on == 2)		//2-6-18 13:36 to avoid accepting a VFD_key in the beginning. 
						{
							power_on--;
							if(key_data != 1)
							{
								//save_srn_start_t = get_rtc_val();//axel, 2004/1/15 05:32 move to top
								call_ir_func(vfd_keycode[key_data - 1]);
							}
						}
						else
						{
							//save_srn_start_t = get_rtc_val();//axel,2004/1/15 05:33 move to top
							call_ir_func(vfd_keycode[key_data - 1]);
						}
					}
#endif
				}
			}
		}
		
		vfd_state = VFD_WRITE;
		update_vfd_data();
	}
	else
	{
		regs0->iop_data[VFD_CMD] = (0xc0 | count);
		regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
		regs0->iop_data[VFD_DAT1] = vfd_mem[count + 3] << 8 | vfd_mem[count + 2];
		regs0->iop_data[VFD_DAT2] = vfd_mem[count + 5] << 8 | vfd_mem[count + 4];
		
		regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
			(FUN_VFD_WRITE | VFD_DAT_LEN6);
		
		/* transfer data size add by chichang 2001 6/6 */
		count += 6;
		if(count == VFD_DISPLAY_SIZE)
		{
			count = 0;
			vfd_state = VFD_READ;
		}
		
	}
#endif
	
#endif //support spi qsi    
}