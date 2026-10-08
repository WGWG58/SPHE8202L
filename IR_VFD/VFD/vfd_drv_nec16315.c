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
BYTE Need_disp_vfd;

#ifdef HK_ORITRON_PANNEL//lijd 2005-5-26 14:01
void SendDataToSM1623LED(void)
{	
	int i;
	for(i=0;i<VFD_DISPLAY_SIZE;i+=4)        
		{
		    regs0->iop_data[VFD_CMD] = (0xc0 | i);   // transfer  address   
		    if((VFD_DISPLAY_SIZE-i)<=4)//modefied by wangfeng,2003-11-24 10:41
		       {
		        	regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
		        	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
		        		                     (FUN_VFD_WRITE | VFD_DAT_LEN2);
		       }
		     else
		       {
		        	regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
		        	regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
		        	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
		        		                     (FUN_VFD_WRITE | VFD_DAT_LEN4);
		       }		
		            WaitIopFunRdy(IOP_RDY_WAIT);
		}		      
}
#endif//#ifdef ORITRON_PANNEL//lijd 2005-5-26 14:01
void reset_vfd(void)
{

	UINT16 nIndex = 0;

	#ifdef HK_ORITRON_PANNEL//lijd 2005-5-26 14:01
     int i;
	 for(i = 0; i < 14; i++)				
		vfd_mem[i] = 0x00;	
				
	    SendDataToSM1623LED();	
	#else
	init_vfd_clear();
	#endif	

	/* display mode ? 13d15s or 6d16s add by chichang 2001/6/6 */
	
	
#ifndef TEST_VFD								//shawn modify at 910131
	regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | VFD_DISPLAY_MODE;	//2001/10/23
#else
	regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | COMMAND_MODE;	//2002/01/31
#endif

	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
		(FUN_VFD_WRITE | VFD_DAT_LEN0);
	
	//erase_vfd_mem();
	
	WaitIopFunRdy(IOP_RDY_WAIT);
	
#ifdef USE_VFD_LED_POWER
    #if defined(USE_VFD_LED_POWER_LOW)&&!defined(VFD_SHOW_LOAD_TOGGLE)
	write_vfd_led(0x0f);
    #elif defined(PROVIEW_DV_509)	
	write_vfd_led(4);
    #else
    write_vfd_led(0);
    #endif
#endif

#ifdef TONIC_DVD//20040206
	write_vfd_led(0);
#endif//TONIC_DVD

	vfd_set_idle_state(nIndex);
	WaitIopFunRdy(IOP_RDY_WAIT);
#ifdef SHOW_HELLO_ON_VFD_WHEN_POWERON//zxb 2005-5-8 13:52
	vfd_set_str(0, "HELLO");	
#endif
#ifdef HK_ORITRON_PANNEL//lijd 2005-5-26 14:01     
		vfd_set_str(0, "ON");	
#endif	 
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


#ifdef NEC16312SW
#define USE_16312SW_EXTEND_KEY
//#define USE_16312SW_VOLUME_BUTTON


#ifdef  USE_16312SW_EXTEND_KEY
#define SW_KEY1     31
#define SW_KEY2     35
#endif

#ifdef USE_16312SW_VOLUME_BUTTON
    #define VFD_SW_SPEED 3
#endif

void polling_vfdsw(void)
{
#ifdef  USE_16312SW_EXTEND_KEY   
    BYTE key_datasw;
#ifdef THAKRAL_USE_SW_KEY
	static BYTE flag=0;
	static BYTE pre_key_datasw;
   	key_datasw= (BYTE)regs0->iop_data[7];

//    psprintf(RegionValStr[REGION1], "KEY %02x ", key_datasw);
//    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
    
    #ifdef VFD_KEY_TEST
    if(key_datasw != 0xF0)
    {
        key_datasw>>=4;
        key_datasw+=24;

        {
			  printf("data=%d\n",key_datasw);
			  psprintf(RegionValStr[REGION1], "KEY %02d F:%d", key_datasw,
				  vfd_keycode[key_datasw - 1]);
			  PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        }
        regs0->iop_data[7] = 0xF0;            
     } 
    #endif
    
    if(key_datasw != 0xf0)
    {
        pre_key_datasw = key_datasw;
        flag = 1;
    }
    
    if((key_datasw==0xf0)&&(flag==1))
    {
        flag = 0;


        //pre_key_datasw>>=4;
        //pre_key_datasw+=24;

        save_srn_start_t = get_rtc_val();
        
        #if defined(SW1_POWER)
        if(pre_key_datasw==0x70)
            call_ir_func(IRC_POWER);
        else if(pre_key_datasw==0xb0)
            call_ir_func(IRC_EJECT);
        #elif defined(SW4_POWER)
        if(pre_key_datasw==0x70)
            call_ir_func(IRC_ONLY_PAUSE);
        else if(pre_key_datasw==0xb0)
            call_ir_func(IRC_PLAY_RESUME);
        else if(pre_key_datasw==0xd0)
            call_ir_func(IRC_STOP);
        else if(pre_key_datasw==0xe0)
            call_ir_func(IRC_POWER);
        #else
        call_ir_func(vfd_keycode[key_datasw-1]);
        #endif 
//        pre_key_datasw = key_datasw;

    }
    
//	if((key_datasw&0x80)==0)
//    { 
//		flag=1;
//	}
//	if(((key_datasw&0x80)==0x80)&&(flag==1))
//	{
//		flag=0;
//		//call_ir_func(vfd_keycode[key_datasw - 1]);
//		call_ir_func(IRC_POWER);
//	}
#else
    key_datasw= (BYTE)regs0->iop_data[7];
    
    if(key_datasw != 0xF0)
    {
        key_datasw>>=4;
        key_datasw+=24;

	#ifdef FUSS_SW
        if( (key_datasw == SW_KEY1) || (key_datasw == SW_KEY2) )
    #endif
        {
    #ifdef VFD_KEY_TEST
			  printf("data=%d\n",key_datasw);
			  psprintf(RegionValStr[REGION1], "KEY %02d F:%d", key_datasw,
				  vfd_keycode[key_datasw - 1]);
			  PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
    #else
			  save_srn_start_t = get_rtc_val();
			  call_ir_func(vfd_keycode[key_datasw - 1]);
    #endif
        }
        regs0->iop_data[7] = 0xF0;            
     } 
#endif    //#ifdef THAKRAL_USE_SW_KEY
#endif    //#ifdef  USE_16312SW_EXTEND_KEY   

#ifdef USE_16312SW_VOLUME_BUTTON
    BYTE key_datasw;
    static BYTE prev = 0;
    BYTE updown = 0;
    static BYTE up_cnt = 0;
    static BYTE down_cnt = 0;
    
    key_datasw= (BYTE)regs0->iop_data[7];  
    
    if(prev != key_datasw)
    {
    
        switch(prev)
        {
        case 0x00:
            if (key_datasw == 0x80)
                updown = 2;    
            else if(key_datasw == 0x40)
                updown = 1;    
            break;
    
        case 0x80:
            if(key_datasw == 0xc0)
                updown = 2;
            else if (key_datasw == 0x00)
                updown = 1;    
            break;
        
        case 0xc0:
            if(key_datasw == 0x40)
                updown = 2;
            else if (key_datasw == 0x80)
                updown = 1;    
            break;
        
        case 0x40: 
            if(key_datasw == 0x00)
                updown = 2;
            else if (key_datasw == 0xc0)
                updown = 1;    
            break;   
       
       default:
            updown = 0;
            break;     
        }
        
        if(updown == 1)
        {
            down_cnt++;
            up_cnt = 0;     
            if(down_cnt >VFD_SW_SPEED )
            {
                down_cnt = 0;               
                ircmd_volume_up();   
            }
        }
        
        if(updown == 2)
        {
            up_cnt++;
            down_cnt = 0;    
            if(up_cnt >VFD_SW_SPEED )
            {
                up_cnt = 0;               
                ircmd_volume_down(); 
            }
    
        }
        prev = key_datasw;  
    }
#endif      //#ifdef USE_16312SW_VOLUME_BUTTON
}
#endif      //#ifdef NEC16312SW

/*
** FUNCTION
** polling_vfdr
**
** DESCRIPTION
** check if polling-ready
*/

#ifdef QISHENG_DVD
int standby_cnt=0;
#endif 

#ifdef AUTO_INTO_STANDBY    //oujx for tonic dvd//20040206
int auto_standby_timer=0;
#endif

#ifdef SUPPORT_GPIO_P_SCAN
BYTE PscanPortStatus=0;
BYTE PscanStatus=0;
BYTE PscanCount=0;
#endif

#if defined(TWO_FUN_IN_ONE_VFD_KEY) || defined(TWO_FUNC_IN_LEFT_RIGHT_KEY)//xyy add for Oritron 2004-11-10 
BYTE num_add_flag = 0;
BYTE command_flag = 1;
#endif

#ifdef PUSH_TRAY_IN   //LYC 05/04/13 
  #define TRAY_IS_OUT_NUM  18  //because   #define TRAY_IS_OUT_GPIO	18
  BYTE tray_in_flag=0;
#endif
#ifdef HOLD_VOL_KEY_FAST_REPEAT//chenzhao add for Oritron 2005-8-20
UINT32 keycode_to_num(UINT32 key_data);
#endif

void polling_vfdr(void)  //nec16321 type vfd
{
    
	//op-joke : add ,fixed vfd flash problem when power on 
    #if 0//ndef MERGE_TEMP
	if(Get_VfdModeState()!=3) //NORMAL_MODE_STATE
		return;
    #endif
    
#ifdef SUPPORT_SPI_QSI
  //not use
#endif


#ifndef  SUPPORT_SPI_QSI

  
    
#ifdef SUPPORT_VFD

	UINT8   i;
	UINT32  temp;
	UINT32  key_data;
	static UINT32 key_previ = 0;
	
	static BYTE bWriteState=0;
	
#ifdef TWO_FUN_IN_ONE_VFD_KEY
	static UINT32 key_previ_temp = 0;
	static UINT16 key_press_time_count = 0;
#endif //TWO_FUN_IN_ONE_VFD_KEY
	
#ifdef TWO_FUNC_IN_LEFT_RIGHT_KEY//xyy add for Oritron 2004-11-10
	static UINT32 uPrevKey = 0;
	static UINT16 uTimeCount = 0;
#endif	
	
    #ifdef HOLD_VOL_KEY_FAST_REPEAT//chenzhao add for Oritron 2005-8-20
	static UINT16 vol_key_press_time_count = 0;
    #define VOL_KEY_HOLD_TIME 15
    #endif
	
    #ifdef KENLOON_PANEL3
	write_vfd_led(0xe);
	#endif
	
	#if defined(SUPPORT_VFD_SHOW_P_SCAN)&&defined(TONIC_DVD)//20040206
	if(vfd_intr_timer)
	    vfd_intr_timer--;	
	#endif
	
	UINT32 *VfdReadData;

	#ifdef GET_5BYTES_KEY_DATA//lijd 2005-5-30 13:54
	UINT32 *VfdReadData1;
	UINT32  key_data_5byte;
	static UINT32 key_previ_5byte = 0;
	#endif



#ifdef  SUPPORT_SPI
    return;
#endif

    #ifdef SUPPORT_GPIO_P_SCAN    //oujx for tonic only
    if(full_scrn==0&&(system_state==SYSTEM_READ_TITLE||system_state==SYSTEM_SETUP_BROWSER||system_state==SYSTEM_BROWSE||system_state==SYSTEM_OPEN||play_state==VCD_STATE_STOP||system_state==SYSTEM_NODISC))	
    {
    	if(PscanStatus==0)
    	{
    	
    		if(GPIO_I_GET(36)==0)
    		    PscanPortStatus=0;
    		else
    		    PscanPortStatus=1;
    		    
    		PscanCount=0;
    		PscanStatus=1;
    	}
    	else
    	if(PscanStatus==1)
    	{
    		PscanCount++;
    		if(PscanCount>50)
    		{
    			if(GPIO_I_GET(36)==PscanPortStatus)
    			{
    				if(PscanPortStatus==0)
    		            ircmd_p_scan_only();
    		        else
    		            ircmd_yuv_only();
    		
    	        }
    			PscanStatus=0;
    		}
    	}
    }		
	#endif//#ifdef SUPPORT_GPIO_P_SCAN    //oujx for tonic only
	
	if(regs0->iop_data[0] & FUN_MASK)
		return;
       
#ifdef PUSH_TRAY_IN   //LYC 05/04/13 
    if(GPIO_I_GET(TRAY_IS_OUT_NUM)==0)
       tray_in_flag=1;
    if((tray_in_flag)&&(GPIO_I_GET(TRAY_IS_OUT_NUM)))
      {
      	play_state = VCD_STATE_CLOSE;
      	tray_in_flag=0;
      	update_vfd_data();
     }	
#endif     

	if(vfd_state == VFD_READ)
	{
#ifndef USE_C_IOP//2004-2-12 12:08 lijd
		//update_vfd_data();//nono 2003-7-24 0:41 mark

		#ifdef  SUPPORT_RECEIVER  //huziqin 2004-4-27
		VfdReadData = ((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x588));
		#elif defined( SPHE8202)
		VfdReadData = ((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x588));//for 8202 2004-3-31 16:47 lijd	
		#elif defined(TWINHAN_8222_PANNEL)  //haoy 2005/03/31 16:17 for twinhan led
		VfdReadData =((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x5E8));
		#elif defined(XINGQIU_RECEIVER_PANNEL)
		VfdReadData = ((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x588));
		#else
		VfdReadData = ((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x5b8));		//gerry,2004-3-24 12:53		
		#endif
		
		#ifdef GET_5BYTES_KEY_DATA
		VfdReadData1 = ((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x5bc));		//gerry,2004-3-24 12:53	
		#endif
		
		//current is read 3 byte on io
        #ifdef GET_5BYTES_KEY_DATA
            key_data_5byte= *VfdReadData1 & 0x000000ff;    
            key_data = *VfdReadData & 0xffffffff;      
        #else
            key_data = *VfdReadData & 0x00ffffff;
        #endif
		*VfdReadData = 0; // Robert 030313
#else//USE_C_IOP
		key_data =(regs0->iop_data[3]);
#endif//USE_C_IOP

        #ifdef GET_5BYTES_KEY_DATA
        if((key_data == 0xffffff)||(key_data_5byte == 0xff))
			return;
        #endif
		if(key_data == 0xffffff)
			return;

        #ifdef USE_VFD_LED_TO_KEY_SOUND_INDICATE		//gerry for PANDA6950,3-8-23 17:17
		write_vfd_led(0xf);
        #elif defined(USE_VFD_LED_TO_KEY_SOUND_INDICATE_HI_ON)		//NONO 2003-10-15 16:14
		write_vfd_led(0x0);
        #endif

#ifdef TWO_FUN_IN_ONE_VFD_KEY
		if((vfd_keycode[keycode_to_num(key_data)-1]==IRC_NEXT)||(vfd_keycode[keycode_to_num(key_data)-1]==IRC_PREV))
		{
			key_press_time_count++;
		    printf("key_press_time_count= %d \n",key_press_time_count);   
		}
		    
		if(key_press_time_count>=15)
		{
			if(vfd_keycode[keycode_to_num(key_data)-1]==IRC_NEXT)
			{
				call_ir_func(IRC_VFD_NEXT);
			    key_press_time_count=0;
			    num_add_flag = 1;
			}
			else if(vfd_keycode[keycode_to_num(key_data)-1]==IRC_PREV)
			{
				call_ir_func(IRC_VFD_PREV);
			    key_press_time_count=0;
			    num_add_flag = 1;
			}
		}
		
#endif //TWO_FUN_IN_ONE_VFD_KEY 

#ifdef TWO_FUNC_IN_LEFT_RIGHT_KEY//xyy add for Oritron 2004-11-10
		if((vfd_keycode[keycode_to_num(key_data)-1]==IRC_LEFT)||(vfd_keycode[keycode_to_num(key_data)-1]==IRC_RIGHT))
		{
			uTimeCount++;
		    printf("uTimeCount= %d \n",uTimeCount);   
		}
		    
		if(uTimeCount>=20)
		{
			if(vfd_keycode[keycode_to_num(key_data)-1]==IRC_LEFT)
			{
				call_ir_func(IRC_VFD_LEFT);
			    uTimeCount=0;
			    num_add_flag = 1;
			}
			else if(vfd_keycode[keycode_to_num(key_data)-1]==IRC_RIGHT)
			{
				call_ir_func(IRC_VFD_RIGHT);
			    uTimeCount=0;
			    num_add_flag = 1;
			}
		}
#endif

        #ifdef HOLD_VOL_KEY_FAST_REPEAT//chenzhao add for Oritron 2005-8-20
        if(key_data != key_previ)
        {
            vol_key_press_time_count=0;
        }
        else if ((vfd_keycode[keycode_to_num(key_data)-1]==IRC_VOLUME_UP)||(vfd_keycode[keycode_to_num(key_data)-1]==IRC_VOLUME_DN))
        {
            if(vol_key_press_time_count>=VOL_KEY_HOLD_TIME)
            {
                if(vfd_keycode[keycode_to_num(key_data)-1]==IRC_VOLUME_UP)
                {
                    call_ir_func(IRC_VOLUME_UP);
                }
                else if(vfd_keycode[keycode_to_num(key_data)-1]==IRC_VOLUME_DN)
                {
                    call_ir_func(IRC_VOLUME_DN);
                }
            }
            else
            vol_key_press_time_count++;
        }
        #endif
        
 		#ifdef GET_5BYTES_KEY_DATA
        if((key_data != key_previ)||(key_data_5byte != key_previ_5byte))
        #else
		if(key_data != key_previ)
		#endif
		{
			
#ifdef TWO_FUN_IN_ONE_VFD_KEY
            //num_add_flag = 0;   //dingzhy 
			key_previ_temp = key_previ;
#endif //TWO_FUN_IN_ONE_VFD_KEY

#ifdef TWO_FUNC_IN_LEFT_RIGHT_KEY  //xyy add for Oritron 2004-11-10
			uPrevKey = key_previ;
#endif

			key_previ = key_data;
			#ifdef GET_5BYTES_KEY_DATA
			key_previ_5byte=key_data_5byte;
			#endif
			#ifdef GET_5BYTES_KEY_DATA
	        if((key_data != 0)||(key_data_5byte != 0))
	        #else
			if(key_data != 0)
			#endif
			
			{
#ifdef TWO_FUN_IN_ONE_VFD_KEY
				//key_press_time_count=0;
				if((vfd_keycode[keycode_to_num(key_data)-1]==IRC_NEXT)||(vfd_keycode[keycode_to_num(key_data)-1]==IRC_PREV))
		        {
		            key_press_time_count++;
		        }
#endif //TWO_FUN_IN_ONE_VFD_KEY

#ifdef TWO_FUNC_IN_LEFT_RIGHT_KEY //xyy add for Oritron 2004-11-10
				if((vfd_keycode[keycode_to_num(key_data)-1]==IRC_LEFT)||(vfd_keycode[keycode_to_num(key_data)-1]==IRC_RIGHT))
				{
					uTimeCount++;
				}
#endif

				#ifdef XINGQIU_RECEIVER_PANNEL
				if(key_data == 0x111111)     //xulf 2004-3-9
					return;
				key_data -= 0x111111;  
				#endif
				#ifdef GET_5BYTES_KEY_DATA	//lijd 2005-5-30 16:20			
				for(i = 0; i < 24; i++)
				#else	
					for(i = 0; i < 32; i++)
				#endif
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
				
				#ifdef GET_5BYTES_KEY_DATA				
				for(i = 0; i < 8; i++)
				{
					temp = 0x01 << i;
					if((BYTE)key_data_5byte & temp)
					{
						if (key_data_5byte > temp) // Robert 030224 for preventing illegal key_data
						{
							key_data_5byte = 0;
							return;
						}
						else
						{
							key_data_5byte = i + 1;
							break;
						}
					}
				}
				if(key_data_5byte)
				   key_data=32 + key_data_5byte;
				#endif
				 
				save_srn_start_t = get_rtc_val();

#if defined(TONIC_DVD)//20040206
				if(KeyLockStatus==1)
				{
					extern const char *const KeyLockString[4][10];
    				//psprintf(RegionValStr[REGION1],"KEY LOCK ON");
    				
    				//PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
    				psprintf(RegionValStr[REGION1],KeyLockString[osd_font_mode][0]);
    				PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
    				vfd_state = VFD_WRITE;
    				return;
				}
#endif//defined(TONIC_DVD)				

#ifdef VFD_KEY_TEST
				psprintf(RegionValStr[REGION1], "KEY %02d F:%d", key_data,vfd_keycode[key_data - 1]);
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
					PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
					ircmd_play();//nono 20031210
				}
				else if((Is_JPEG_SlideMode()) &&	//Jeff 20020527
					(vfd_keycode[key_data - 1] == IRC_PAUSEPLAY))
				{
					if(bJpgVFDPause == 0)
					{
						//bJpgVFDPause = 1;
						if(play_state == VCD_STATE_PAUSE)	//nono 2-6-28 14:00
							//bJpgVFDPause = 2;
							
						{
							bJpgVFDPause = 2;
							PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
							ircmd_play();//nono 20031210
						}							
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
					
#ifdef QISHENG_DVD
		            standby_cnt=0;
                    if((vfd_keycode[key_data - 1])==IRC_STOP)
                    	standby_cnt=1;
#endif//#ifdef QISHENG_DVD

#ifdef NEXT_FORWARD_IN_A_KEY					
					key_data_flag = 1;
#endif//#ifdef NEXT_FORWARD_IN_A_KEY					

					if(power_on == 2)			//2-6-18 13:36 to avoid accepting a VFD_key in the beginning. 
					{
						power_on--;
						if(key_data != 1)
						{
#ifdef TWO_FUN_IN_ONE_VFD_KEY							
                            if((vfd_keycode[key_data-1]!=IRC_NEXT) && (vfd_keycode[key_data-1]!=IRC_PREV))
#endif //TWO_FUN_IN_ONE_VFD_KEY

#ifdef TWO_FUNC_IN_LEFT_RIGHT_KEY //xyy add for Oritron 2004-11-10
                            if((vfd_keycode[key_data-1]!=IRC_LEFT) && (vfd_keycode[key_data-1]!=IRC_RIGHT))
#endif
							//save_srn_start_t = get_rtc_val();//axel moved to top 2004/2/4 06:13PM
							call_ir_func(vfd_keycode[key_data - 1]);
						}
					}
					else
					{
						//save_srn_start_t = get_rtc_val(); //axel moved to top 2004/2/4 06:13PM
                        #ifdef USE_VFD_LED_TO_KEY_SOUND_INDICATE		//gerry for PANDA6950,3-8-23 17:19					
						write_vfd_led(0);
                        #elif defined(USE_VFD_LED_TO_KEY_SOUND_INDICATE_HI_ON)		//NONO 2003-10-15 16:14
						write_vfd_led(0xf);
                        #endif						
					
#ifdef TWO_FUN_IN_ONE_VFD_KEY
                        if((vfd_keycode[key_data-1]!=IRC_NEXT) && (vfd_keycode[key_data-1]!=IRC_PREV))
#endif //TWO_FUN_IN_ONE_VFD_KEY
#ifdef TWO_FUNC_IN_LEFT_RIGHT_KEY //xyy add for Oritron 2004-11-10
                            if((vfd_keycode[key_data-1]!=IRC_LEFT) && (vfd_keycode[key_data-1]!=IRC_RIGHT))
#endif
						call_ir_func(vfd_keycode[key_data - 1]);
					}

#ifdef NEXT_FORWARD_IN_A_KEY					
					key_data_flag = 0;
#endif//#ifdef NEXT_FORWARD_IN_A_KEY
				}
#endif

		    }

		    else{
#ifdef TWO_FUN_IN_ONE_VFD_KEY
			    if((key_press_time_count>0)&&(key_press_time_count<15)&&(num_add_flag==0)&&(command_flag))
			    {
    				if(vfd_keycode[keycode_to_num(key_previ_temp)-1]==IRC_NEXT)
    				{
    					call_ir_func(IRC_NEXT);
    					command_flag=0;
    				}
    			    				
    				else if(vfd_keycode[keycode_to_num(key_previ_temp)-1]==IRC_PREV)
    			    {
    					call_ir_func(IRC_PREV);
    					command_flag=0;
    			    }
    		    }
    			key_press_time_count=0;	 
    			num_add_flag = 0;	
    			
#endif //TWO_FUN_IN_ONE_VFD_KEY

#ifdef TWO_FUNC_IN_LEFT_RIGHT_KEY //xyy add for Oritron 2004-11-10 9:58
			    if((uTimeCount>0)&&(uTimeCount<20)&&(num_add_flag==0)&&(command_flag))
			    {
    				if(vfd_keycode[keycode_to_num(uPrevKey)-1]==IRC_LEFT)
    				{
    					call_ir_func(IRC_LEFT);
    					command_flag=0;
    				}
    			    				
    				else if(vfd_keycode[keycode_to_num(uPrevKey)-1]==IRC_RIGHT)
    			    {
    					call_ir_func(IRC_RIGHT);
    					command_flag=0;
    			    }
    		    }
    			uTimeCount=0;	 
    			num_add_flag = 0;	
#endif


#ifdef QISHENG_DVD		   	 
		   	    standby_cnt = 0;
#endif 
		    }
		}
#ifdef QISHENG_DVD
        else if ((key_data!=0))
        {
        	if(standby_cnt)
        	{
        		standby_cnt++;
        		printf("*");
        		if(standby_cnt==50)
        		{
        			vfd_state = VFD_WRITE;
        			call_ir_func(IRC_POWER);
        		}
        	}
        }
#endif
	
#if defined(TWO_FUN_IN_ONE_VFD_KEY) || defined(TWO_FUNC_IN_LEFT_RIGHT_KEY)//xyy add for Oritron 2004-11-10
		else
		{
		    command_flag=1;
		}	
#endif			
		vfd_state = VFD_WRITE;
	}	
	else
	{
		update_vfd_data();
#if defined(SUPPORT_APOGEE_AMP) && defined(AMPVOL_ADJUST_TYPE1)//xyy 2004-4-14
    	if(full_scrn==APOGEEAMPVOL && timeout_osd[REGION1] == 0)
    	{
    		full_scrn = 0;
    		erase_vfd_mem();
    	}
#endif
        //int i;
#ifdef AUTO_INTO_STANDBY   //for tonic dvd//20040206
    	//if(play_state==VCD_STATE_STOP||system_state==SYSTEM_NODISC)
	    if(system_state==SYSTEM_STOP||system_state==SYSTEM_NODISC||play_state==VCD_STATE_STOP)
        {
        	//auto_standby_timer++;
	    	//if(auto_standby_timer==100*60*30)
            #ifndef MAX_AUTO_STANDBY_TIME
	    	if(auto_standby_timer==100*60*25)
            #else
               if(auto_standby_timer>=MAX_AUTO_STANDBY_TIME)//zxb 2005-4-28 14:13
            #endif
	        	ircmd_power();
        }
        else
	        auto_standby_timer=0;
#endif

					
#ifdef BCT72328_DRIVER_VFD//lijd 2005-6-23 13:39
	switch (bWriteState)
		{
		case 0:
			//update to reset mode
#ifndef TEST_VFD
			regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | VFD_DISPLAY_MODE;
#else
			regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | COMMAND_MODE;
#endif		
			
			regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) | (FUN_VFD_WRITE | VFD_DAT_LEN0);
			
			bWriteState++;
			break;
			
		case 1:
			regs0->iop_data[VFD_CMD] =0x44;				
			regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
				(FUN_VFD_WRITE | VFD_DAT_LEN0);
			
			bWriteState++;
			break;	

		case 2:	       
			printf("joke: vfd address  ......1  \n");  
		    i=0;  
			regs0->iop_data[VFD_CMD] = (0xc0 | i);
			regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
            regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
            regs0->iop_data[VFD_DAT2] = vfd_mem[i + 5] << 8 | vfd_mem[i + 4];
			regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) | (FUN_VFD_WRITE | VFD_DAT_LEN6);
			WaitIopFunRdy(IOP_RDY_WAIT);	
			i=6;
			regs0->iop_data[VFD_CMD] = (0xc0 | i);
			regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
            regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
            regs0->iop_data[VFD_DAT2] = vfd_mem[i + 5] << 8 | vfd_mem[i + 4];
			regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) | (FUN_VFD_WRITE | VFD_DAT_LEN6);
			WaitIopFunRdy(IOP_RDY_WAIT);
			i=12;
			regs0->iop_data[VFD_CMD] = (0xc0 | i);
			regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];                
			regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) | (FUN_VFD_WRITE | VFD_DAT_LEN2);
			WaitIopFunRdy(IOP_RDY_WAIT);	
			
			bWriteState++;
			break;
		case 3:
			regs0->iop_data[VFD_CMD] =
				VFDC_DISP_CTRL | VFDC_DISP_CTRL_ON | VFDC_DISP_CTRL_10_16;
			
			regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
				(FUN_VFD_WRITE | VFD_DAT_LEN0);	
			vfd_state = VFD_READ;
			bWriteState=0;
			break;	
		}
#else//BCT72328_DRIVER_VFD
	
		//printf("joke:  bWriteState= %d   \n",bWriteState);
		switch (bWriteState)
		{
		case 0:
			//update to reset mode
#ifndef TEST_VFD
			regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | VFD_DISPLAY_MODE;
#else
			regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | COMMAND_MODE;
#endif		
			
			regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) | (FUN_VFD_WRITE | VFD_DAT_LEN0);
			
			bWriteState++;
			break;
			
		case 1:
			regs0->iop_data[VFD_CMD] =
				VFDC_DISP_CTRL | VFDC_DISP_CTRL_ON | VFDC_DISP_CTRL_10_16 | VFDC_SET_DISP_10D18S;
			
			regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
				(FUN_VFD_WRITE | VFD_DAT_LEN0);
			
			bWriteState++;
			break;

#ifdef  SM1623_DRIVER_VFD
		case 2:				
		//update in one polling
            for(i=0;i<VFD_DISPLAY_SIZE;i+=4)       // fengjl upload  3-11-23 17:33
            {
    			regs0->iop_data[VFD_CMD] = (0xc0 | i);   // transfer  address   
    			if((VFD_DISPLAY_SIZE-i)<=4)//modefied by wangfeng,2003-11-24 10:41
    			{
    			    regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
    			    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
    				(FUN_VFD_WRITE | VFD_DAT_LEN2);
    			}
    			else
    			{
    			    regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
    			    regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
    				regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
    				(FUN_VFD_WRITE | VFD_DAT_LEN4);
    			}
    			
    			WaitIopFunRdy(IOP_RDY_WAIT);
            }			
			vfd_state = VFD_READ;
			bWriteState=0;
			break;

#elif defined(GBM_LED6961_PANEL)||defined(ET6201_PANNEL)||defined(GBM_PBCY_8202_PANNEL)            //gerry for GBM_LED_PANEL,2004-2-4 22:41
		case 2:				

			for(i=0;i<VFD_DISPLAY_SIZE;i+=2)
			{
				regs0->iop_data[VFD_CMD] = (0xc0 | i);

				regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
				regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) | (FUN_VFD_WRITE | VFD_DAT_LEN2);
				WaitIopFunRdy(IOP_RDY_WAIT);		
			}	
			vfd_state = VFD_READ;	
			bWriteState=0;
			break;

#else//GBM_LED6961_PANEL
			
		case 2:				
			
#if !defined(TP6311_DRIVER_VFD) && !defined(XINGQIU_RECEIVER_PANNEL)&& !defined(KENLOON_PANEL3)	&& !defined(ORITRON_PANEL)//xyy
            static UINT8 count = 0;
			regs0->iop_data[VFD_CMD] = (0xc0 | count);
			regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
			regs0->iop_data[VFD_DAT1] = vfd_mem[count + 3] << 8 | vfd_mem[count + 2];
			#ifndef SKYWORTH_DVD
			regs0->iop_data[VFD_DAT2] = vfd_mem[count + 5] << 8 | vfd_mem[count + 4];
			#endif
			regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
			#ifndef SKYWORTH_DVD
				(FUN_VFD_WRITE | VFD_DAT_LEN6);
			
			/* transfer data size add by chichang 2001 6/6 */
			count += 6;
			#else
			(FUN_VFD_WRITE | VFD_DAT_LEN4);
			/* transfer data size add by chichang 2001 6/6 */
			count += 4;
			#endif
			
			if(count == VFD_DISPLAY_SIZE)
			{
				count = 0;
				vfd_state = VFD_READ;
			}
#else//#ifndef TP6311_DRIVER_VFD		                                             //marked by xyy 2003-10-31 19:42	
    		//printf("joke<16315>: VFD_DISPLAY_SIZE= %d   \n",VFD_DISPLAY_SIZE);
    		for(i = 0; i < VFD_DISPLAY_SIZE; i += 6)    //xyy 2003-10-31 19:42
    		{
    			regs0->iop_data[VFD_CMD] = (0xc0 | i);
    			regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
    			regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
    			regs0->iop_data[VFD_DAT2] = vfd_mem[i + 5] << 8 | vfd_mem[i + 4];
    			
    			regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) | (FUN_VFD_WRITE | VFD_DAT_LEN6);
    			
    			WaitIopFunRdy(IOP_RDY_WAIT);
    		}
			vfd_state = VFD_READ;
#endif//#ifndef TP6311_DRIVER_VFD
			bWriteState=0;
			break;
#endif//#ifdef  SM1623_DRIVER_VFD
		}//write state control
#endif//BCT72328_DRIVER_VFD
	}
#elif defined(GPIO_KEY_LIGHT)//SUPPORT_VFD nono 3-8-18 14:41
    check_gpio_keylight_status();
#elif defined(USE_VFDPORT_TRANDATA)
    Communication_And_MCU4051();	   
#endif//SUPPORT_VFD

#endif //support spi qsi
}

#ifdef TP6317_PANNEL   //yaowh add 04-10-25
BYTE Read_SW(void)
{
   BYTE key_datasw ;
   key_datasw= (BYTE)regs0->iop_data[7] ;	  
   //regs0->iop_data[7] = 0xF0 ;            
   return  key_datasw ;
}
void write_vfd_data(BYTE bAddr, BYTE bData)
{
	regs0->iop_data[VFD_CMD] = 0x40;//Writes data to display memory
	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) | (FUN_VFD_WRITE | VFD_DAT_LEN0);
	regs0->iop_data[VFD_CMD] = (0xc0 | bAddr);//Assress setting command
	regs0->iop_data[VFD_DAT0] = 0xff00 | bData;
	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) | (FUN_VFD_WRITE | VFD_DAT_LEN1);
	WaitIopFunRdy(IOP_RDY_WAIT);
}
void define_standbykey(void)
{
    write_vfd_data(0x16,IR_USER_CODE_LOW8 & 0xff);
    write_vfd_data(0x17,IR_USER_CODE_HIGHT8 & 0xff);
    write_vfd_data(0x18,TP6317_IR_CODE1 & 0xff);
    write_vfd_data(0x19,TP6317_IR_CODE2 & 0xff);
    write_vfd_data(0x1a,TP6317_IR_CODE3 & 0xff);
    write_vfd_data(0x1b,TP6317_IR_CODE4 & 0xff);
    write_vfd_data(0x1c,TP6317_IR_CODE5 & 0xff);
    write_vfd_data(0x1d,TP6317_IR_CODE6 & 0xff);
    write_vfd_data(0x1e,TP6317_IR_CODE7 & 0xff);
    write_vfd_data(0x1f,TP6317_IR_CODE8 & 0xff);
    write_vfd_data(0x20,TP6317_VFD_KEY_CODE1 & 0xff);
    write_vfd_data(0x21,TP6317_VFD_KEY_CODE2 & 0xff);
    write_vfd_data(0x22,TP6317_VFD_KEY_CODE3 & 0xff);
    	
}
void  Power_off_define_TP6317_standbykey(void) 
{
    define_standbykey();
}
void TP6317_int(void)
{
    define_standbykey();
}
#endif

