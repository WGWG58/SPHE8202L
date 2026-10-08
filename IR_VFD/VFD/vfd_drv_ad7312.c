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
void reset_vfd(void)
{
	UINT16 nIndex = 0;

	init_vfd_clear();

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
	vfd_set_idle_state(nIndex);
	WaitIopFunRdy(IOP_RDY_WAIT);	
}

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
    static UINT8 count = 0;
    static UINT32 key_previ = 0;
    
    static BYTE bWriteState=0;
        
    UINT32 *VfdReadData;
    
    if(regs0->iop_data[0] & FUN_MASK)       return;
       

    if(vfd_state == VFD_READ)
    {
        #ifndef USE_C_IOP//2004-2-12 12:08 lijd     
        VfdReadData = ((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x688));       //fengjl edit 2004-07-02 18:05
        
        //current is read 3 byte on io
        key_data = *VfdReadData & 0x00ffffff;

        *VfdReadData = 0; // Robert 030313

        #else//USE_C_IOP
        key_data =(regs0->iop_data[3]);
        #endif//USE_C_IOP
        
        if(key_data == 0xffffff)
            return;
        if(key_data != key_previ)
        {
            
#ifdef TWO_FUN_IN_ONE_VFD_KEY
            //num_add_flag = 0;   //dingzhy 
            key_previ_temp = key_previ;
#endif //TWO_FUN_IN_ONE_VFD_KEY

            key_previ = key_data;

            if(key_data != 0)
            {
                #ifdef TWO_FUN_IN_ONE_VFD_KEY
                key_press_time_count=0;
                #endif
                                
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
                
                save_srn_start_t = get_rtc_val();
                
#ifdef VFD_KEY_TEST
                psprintf(RegionValStr[REGION1], "KEY %02d F:%d", key_data, vfd_keycode[key_data - 1]);
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
                    bJpgVFDPause = 2;           //Jeff 20020525
                    PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
                    ircmd_play();//nono 20031210
                }
                else if((Is_JPEG_SlideMode()) &&    //Jeff 20020527
                    (vfd_keycode[key_data - 1] == IRC_PAUSEPLAY))
                {
                    if(bJpgVFDPause == 0)
                    {
                        //bJpgVFDPause = 1;
                        if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
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

                    #ifdef NEXT_FORWARD_IN_A_KEY                    
                    key_data_flag = 1;
                    #endif

                    if(power_on == 2)           //2-6-18 13:36 to avoid accepting a VFD_key in the beginning. 
                    {
                        power_on--;
                        if(key_data != 1)
                        {
#ifdef TWO_FUN_IN_ONE_VFD_KEY                           
                            if((vfd_keycode[key_data-1]!=IRC_NEXT) && (vfd_keycode[key_data-1]!=IRC_PREV))
#endif //TWO_FUN_IN_ONE_VFD_KEY
                            //save_srn_start_t = get_rtc_val();//axel moved to top 2004/2/4 06:13PM
                            call_ir_func(vfd_keycode[key_data - 1]);
                        }
                    }
                    else
                    {
                        //save_srn_start_t = get_rtc_val(); //axel moved to top 2004/2/4 06:13PM
#ifdef USE_VFD_LED_TO_KEY_SOUND_INDICATE        //gerry for PANDA6950,3-8-23 17:19                  
                        write_vfd_led(0);
#elif defined(USE_VFD_LED_TO_KEY_SOUND_INDICATE_HI_ON)      //NONO 2003-10-15 16:14
                        write_vfd_led(0xf);
#endif                      
                    
#ifdef TWO_FUN_IN_ONE_VFD_KEY
                        if((vfd_keycode[key_data-1]!=IRC_NEXT) && (vfd_keycode[key_data-1]!=IRC_PREV))
#endif //TWO_FUN_IN_ONE_VFD_KEY
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
            if((key_press_time_count>0)&&(key_press_time_count<15))
            {
                if(vfd_keycode[keycode_to_num(key_previ_temp)-1]==IRC_NEXT)
                    call_ir_func(IRC_VFD_NEXT);                 
                else if(vfd_keycode[keycode_to_num(key_previ_temp)-1]==IRC_PREV)
                    call_ir_func(IRC_VFD_PREV);
            }
            key_press_time_count=0;  
#endif //TWO_FUN_IN_ONE_VFD_KEY

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
            if(auto_standby_timer==100*60*25)
            ircmd_power();
        }
        else
            auto_standby_timer=0;
#endif
        switch (bWriteState)
        {
        case 0:
            //update to reset mode
#ifndef TEST_VFD
            regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | VFD_DISPLAY_MODE;
#else
            regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | COMMAND_MODE;
#endif      
            
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN0);
            
            bWriteState++;
            break;
            
        case 1:
            regs0->iop_data[VFD_CMD] =
                VFDC_DISP_CTRL | VFDC_DISP_CTRL_ON | VFDC_DISP_CTRL_10_16;
            
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN0);
            
            bWriteState++;
            break;

#ifdef  SM1623_DRIVER_VFD
        case 2:             
            
//#if 1
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

/*#else//#if 1
            //update by polling 10ms
            regs0->iop_data[VFD_CMD] = (0xc0 | count);
            if(count>=12)
            {
                regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
            }
            else
            {
                    regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
                    regs0->iop_data[VFD_DAT1] = vfd_mem[count + 3] << 8 | vfd_mem[count + 2];
            }
            //regs0->iop_data[VFD_DAT2] = vfd_mem[count + 5] << 8 | vfd_mem[count + 4];
            if(count>=12)
            {
                    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN2);
            }
            else
            {
                regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN4);
                
                }
            // transfer data size add by chichang 2001 6/6 
            count += 4;
            if(count >= VFD_DISPLAY_SIZE)
            {
                count = 0;
                vfd_state = VFD_READ;
            }
#endif//#if 1*/
            bWriteState=0;
            break;

#elif defined(GBM_LED6961_PANEL)            //gerry for GBM_LED_PANEL,2004-2-4 22:41
        case 2:             

            for(i=0;i<VFD_DISPLAY_SIZE;i+=2)
            {
                regs0->iop_data[VFD_CMD] = (0xc0 | i);

                regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
                regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN2);
                WaitIopFunRdy(IOP_RDY_WAIT);        
            }   
            vfd_state = VFD_READ;   
            bWriteState=0;
            break;

#else//GBM_LED6961_PANEL
            
        case 2:             
            
#if !defined(TP6311_DRIVER_VFD) && !defined(XINGQIU_RECEIVER_PANNEL)    //xyy
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
#else//#ifndef TP6311_DRIVER_VFD                                                     //marked by xyy 2003-10-31 19:42   
            for(i = 0; i < VFD_DISPLAY_SIZE; i += 6)    //xyy 2003-10-31 19:42
            {
                regs0->iop_data[VFD_CMD] = (0xc0 | i);
                regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
                regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
                regs0->iop_data[VFD_DAT2] = vfd_mem[i + 5] << 8 | vfd_mem[i + 4];
                
                regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                    (FUN_VFD_WRITE | VFD_DAT_LEN6);
                
                WaitIopFunRdy(IOP_RDY_WAIT);
            }
            vfd_state = VFD_READ;
#endif//#ifndef TP6311_DRIVER_VFD
            bWriteState=0;
            break;
#endif//#ifdef  SM1623_DRIVER_VFD
        }//write state control
    }
#elif defined(GPIO_KEY_LIGHT)//SUPPORT_VFD nono 3-8-18 14:41
    check_gpio_keylight_status();
#elif defined(USE_VFDPORT_TRANDATA)
    Communication_And_MCU4051();       
#endif//SUPPORT_VFD
#endif//spi qsi
}