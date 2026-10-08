#if defined(GPIO_KEY_LIGHT)

	//   DATA        gpio56       IN/OUT
	//   STB         gpio57       IN/OUT
	//   CLK         gpio58       IN/OUT

#ifdef HANYANG_DP02CD_WF_8202S_16//added by wangwei,2005-2-3 15:33
void check_hanyang_dp02cd_wf_key_status(void)
{

	UINT32  key_data;
	static int key_state = 0;
	static UINT32 key_previ = 0x80E1;
	
	//init_keylight_io();
    /*regs0->gpio_oe[21 / 16] &= (~0x1 << (21 % 16));
	regs0->gpio_oe[22 / 16] &= (~0x1 << (22 % 16));
	regs0->gpio_oe[23 / 16] &= (~0x1 << (23 % 16));
	*/
	/*regs0->gpio_oe[15 / 16] &= (~0x1 << (15 % 16));
	regs0->gpio_oe[16 / 16] &= (~0x1 << (16 % 16));
*/
	key_data = (regs0->gpio_in[21 / 16] & 0x00e1)|(regs0->gpio_in[15 / 16]&0x8000);///yangli 

	if(key_data != key_previ)
	{
		//printf("1.key_previ=%x\n",key_previ);
		//key_previ = 0xf0;
		#ifdef VFD_KEY_TEST
	    psprintf(RegionValStr[REGION1], "KEY %x", key_data);
	    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        #endif
		switch (key_data)
		{
		
		case 0x80c1:
		
			if(key_state == 2)
			{
				
				call_ir_func(IRC_PLAY);
				//printf("EJECT\n");
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			
			break;
		case 0x80e0:
		
			if(key_state == 2)
			{
			    call_ir_func(IRC_EJECT); //call_ir_func(IRC_PAUSEPLAY);//HHQ
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			
			break;
		case 0x80a1:
		
			if(key_state == 2)
			{
				call_ir_func(IRC_STOP);
				//printf("STOP\n");
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			
			break;
		/*case 0x00E1:
		
			if(key_state == 2)
			{
				call_ir_func(IRC_BACKWARD);
				//printf("EJECT\n");
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			break;

		case 0x80E0:
		
			if(key_state == 2)
			{
				call_ir_func(IRC_FORWARD);
				//printf("EJECT\n");
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			
			break;*/
		default:
			key_state = 2;
			break;
		}
	}
	else
	{
		//printf("out:key_state=%x\n",key_state);
		key_previ = key_data;
		key_state = 2;
#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)
		key_data_flag=0;
#endif//#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)	
	}
		
}

#elif defined(HANYANG_DP02CD_WG_8202S_16)
void delay_time(UINT32 counter)
{
    UINT32 i,j;
    for(i=0;i<counter;i++)
    {
        j++;
    }    
}
static inline void check_hanyang_dp02cd_wg_led(void)
{
    #ifdef READ_DISC_LED_BLINKING
    static BYTE counter = 0;
    if(play_state == VCD_STATE_CLOSE)
    {
        counter++;
        if(counter < 7)
        {
            GPIO_O_SET(21,0);
            GPIO_O_SET(22,0);
        }
        else
        {
            GPIO_O_SET(21,1);
            GPIO_O_SET(22,0);
            if(counter > 12)
                counter = 0;
        }
    }
    else
    #endif//READ_DISC_LED_BLINKING
    {
        GPIO_O_SET(21, 1);// GREEN : NORMAL
        GPIO_O_SET(22, 0);// RED   : STANDBY
    }
}

#define GET_GPIO_15    0x0010
#define GET_GPIO_16    0x0020
#define GET_GPIO_23    0x0040
#define GPIO_21_OUTPUT 0x0001
#define GPIO_22_OUTPUT 0x0002
void check_hanyang_dp02cd_wg_keylight_status(void)
{
    //PIN65    : GPIO 15 
    //PIN66    : GPIO 16 -> PULL LOW,INPUT PIN.
    //VFD_DATA : GPIO 23 
    //VFD_CLK  : GPIO 21  
    //VFD_STB  : GPIO 22 -  PULL HIGH,OUTPUT PIN.
    
    UINT32 key_output_data = 0;
    UINT32 key_data;
    static int key_state = 0;
    static UINT32 key_previ = 0xfff;
    //////////////////////////////////////////////////////////////////////////////////////////
    GPIO_O_SET(21, 1);
    GPIO_O_SET(22, 0);
    delay_time(0xff);// 1ms is too long for LED,it'll blink.
    key_output_data = GPIO_21_OUTPUT;
    if(GPIO_I_GET(15) && (!GPIO_I_GET(16)) && (!GPIO_I_GET(23)))
    {
        key_data = key_output_data | GET_GPIO_15;
    }
    else if((!GPIO_I_GET(15)) && GPIO_I_GET(16) && (!GPIO_I_GET(23)))
    {
        key_data = key_output_data | GET_GPIO_16;
    }
    else if((!GPIO_I_GET(15)) && (!GPIO_I_GET(16)) && GPIO_I_GET(23))
    {
        key_data = key_output_data | GET_GPIO_23;    
    }
    
    if((key_data != 0x11) && (key_data != 0x21) && (key_data != 0x41))
    {
        GPIO_O_SET(21, 0);
        GPIO_O_SET(22, 1);
        delay_time(0xff);
        key_output_data = GPIO_22_OUTPUT;
        if(GPIO_I_GET(15) && (!GPIO_I_GET(16)) && (!GPIO_I_GET(23)))
        {
            key_data = key_output_data | GET_GPIO_15;
        }
        else if((!GPIO_I_GET(15)) && GPIO_I_GET(16) && (!GPIO_I_GET(23)))
        {
            key_data = key_output_data | GET_GPIO_16;
        }
        else if((!GPIO_I_GET(15)) && (!GPIO_I_GET(16)) && GPIO_I_GET(23))
        {
            key_data = key_output_data | GET_GPIO_23;    
        }
    }
    GPIO_O_SET(21, 0);
    GPIO_O_SET(22, 0);

    if((key_data != 0x11)&&(key_data != 0x21)&&(key_data != 0x41)&&(key_data != 0x12)&&(key_data != 0x22)&&(key_data != 0x42))
        key_data = 0;
    //////////////////////////////////////////////////////////////////////////////////////////
    #if 0
    psprintf(RegionValStr[REGION1], "KEY %x", key_data);
    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
    #endif

    check_hanyang_dp02cd_wg_led();// lighting LED

    #if (defined(GPIO_LONG_NEXT_SHORT_FORWARD_IN_A_KEY)||defined(GPIO_LONG_FORWARD_SHORT_NEXT_IN_A_KEY))
	static int gpio_func_prev_key_flag = 0;
	static int gpio_func_next_key_flag = 0;
	static int gpio_func_key_data = 0;
    #endif//(defined(GPIO_LONG_NEXT_SHORT_FORWARD_IN_A_KEY)||defined(GPIO_LONG_FORWARD_SHORT_NEXT_IN_A_KEY))

	if(key_previ != key_data)
	{
		key_previ = key_data;
		key_state = 2;

        #ifdef GPIO_LONG_NEXT_SHORT_FORWARD_IN_A_KEY
        if(gpio_func_prev_key_flag==1)
        {
            call_ir_func(IRC_BACKWARD);
            gpio_func_prev_key_flag=0;
        }    
        if(gpio_func_next_key_flag==1)
        {
            call_ir_func(IRC_FORWARD);
            gpio_func_next_key_flag=0;
        }
        gpio_func_key_data=0;
        #elif defined(GPIO_LONG_FORWARD_SHORT_NEXT_IN_A_KEY)
        if(gpio_func_prev_key_flag==1)
        {
            call_ir_func(IRC_PREV);
            gpio_func_prev_key_flag=0;
        }    
        if(gpio_func_next_key_flag==1)
        {
            call_ir_func(IRC_NEXT);
            gpio_func_next_key_flag=0;
        }
        gpio_func_key_data=0;
        #endif//GPIO_LONG_NEXT_SHORT_FORWARD_IN_A_KEY
	}
    else
	{
		switch (key_data)
		{
            case 0x11:
                if(key_state == 2)
                {
                    call_ir_func(IRC_PAUSEPLAY);
                }
                key_state = 1;
                break;
            case 0x12:
                if(key_state == 2)
                {
                    call_ir_func(IRC_EJECT);
                }
                key_state = 1;
                break;
            case 0x21:
                if(key_state == 2)
                {
                    call_ir_func(IRC_STOP);
                }
                key_state = 1;
                break;
            case 0x41:
                if(key_state == 2)
                {
                    call_ir_func(IRC_POWER);
                }
                key_state = 1;
                break;
            case 0x42:
                #ifdef GPIO_LONG_NEXT_SHORT_FORWARD_IN_A_KEY
                if(key_state == 2)
                {
                    gpio_func_key_data++;
                    if((gpio_func_key_data>5)&&(gpio_func_key_data<40))
                        gpio_func_prev_key_flag=1;
                    else if(gpio_func_key_data>=40)
                        gpio_func_prev_key_flag=2;

                    if((gpio_func_prev_key_flag==2)&&(gpio_func_key_data%60==0))
                    {
                        call_ir_func(IRC_PREV);
                    }    
                }
                break;
                #elif defined(GPIO_LONG_FORWARD_SHORT_NEXT_IN_A_KEY)
                {
                    gpio_func_key_data++;
                    if((gpio_func_key_data>5)&&(gpio_func_key_data<40))
                        gpio_func_prev_key_flag=1;
                    else if(gpio_func_key_data>=40)
                        gpio_func_prev_key_flag=2;

                    if((gpio_func_prev_key_flag==2)&&(gpio_func_key_data%60==0))
                    {
                        call_ir_func(IRC_BACKWARD);
                    }    
                }
                break;
                #else
                if(key_state == 2)
                {
                    call_ir_func(IRC_PREV);
                }
                key_state = 1;
                break;
                #endif//GPIO_LONG_NEXT_SHORT_FORWARD_IN_A_KEY	
            case 0x22:
                #ifdef GPIO_LONG_NEXT_SHORT_FORWARD_IN_A_KEY
                if(key_state == 2)
                {
                    gpio_func_key_data++;
                    if((gpio_func_key_data>5)&&(gpio_func_key_data<40))
                        gpio_func_next_key_flag=1;
                    else if(gpio_func_key_data>=40)
                        gpio_func_next_key_flag=2;

                    if((gpio_func_next_key_flag==2)&&(gpio_func_key_data%60==0))
                    {
                        call_ir_func(IRC_NEXT);
                    }    
                }
                break;
                #elif defined(GPIO_LONG_FORWARD_SHORT_NEXT_IN_A_KEY)
                if(key_state == 2)
                {
                    gpio_func_key_data++;
                    if((gpio_func_key_data>5)&&(gpio_func_key_data<40))
                        gpio_func_next_key_flag=1;
                    else if(gpio_func_key_data>=40)
                        gpio_func_next_key_flag=2;

                    if((gpio_func_next_key_flag==2)&&(gpio_func_key_data%60==0))
                    {
                        call_ir_func(IRC_FORWARD);
                    }    
                }
                break;
                #else
                if(key_state == 2)
                {
                    call_ir_func(IRC_NEXT);
                }
                key_state = 1;
                break;
                #endif//GPIO_LONG_NEXT_SHORT_FORWARD_IN_A_KEY
            default:
                key_state = 2;
                break;
		}
	}
}
#endif//define HANYANG_DP02CD_WF_8202S_16

#if defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ)

#ifdef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_2326

void check_hj_keylight_status(void)
{

	UINT32  key_data;
	UINT32  key_data1;
	UINT32  key_data2;
//	UINT32  key_data3;
	static int key_state = 0;
	static UINT32 key_previ = 0xffff;
	
//	regs0->gpio_oe[54 / 16] &= ~(0x7 << (54 % 16));
//	regs0->gpio_oe[42 / 16] &= ~(0x3 << (42 % 16));

	//key_data = ((regs0->gpio_in[42 / 16] & (0x3 << (42 % 16))) |(regs0->gpio_in[54 / 16] & (0x7 << (54 % 16))) );
	//key_data =(( regs0->gpio_in[42 / 16] & (0x3 << (42 % 16))) |(regs0->gpio_in[54 / 16] & (0x7 << (54 % 16))) );
	key_data1 = regs0->gpio_in[14 / 16] & (0x3 << (14 % 16));//14
	key_data2 = regs0->gpio_in[54 / 16] & (0x7 << (54 % 16));//6,7,8
//	key_data2 = regs0->gpio_in[4 / 16] & (0x1 << (4 % 16));//4
//	key_data3 = regs0->gpio_in[54 / 16] & (0x7 << (54 % 16));//6,7,8
	key_data =(key_data1|key_data2);//15,14,6,7,8
	
	//printf("key_data=%x\n",key_data);
	//return;
	//printf("regs0->sft_cfg6=%x\n",regs0->sft_cfg6);
	//printf("regs0->gpio_oe[14 / 16]=%x\n",regs0->gpio_oe[14 / 16] );

	//printf("key_state=%x\n",key_state);
	//printf("key_previ=%x\n",key_previ);
	//regs0->gpio_out[56 / 16] &= ~(0x1 << (56 % 16));



	if(key_data == key_previ)
	{
		//printf("1.key_previ=%x\n",key_previ);
		//key_previ = 0xf0;

		switch (key_data)
		{
		case 0x81C0:

			if(key_state == 2)
			{
				call_ir_func(IRC_EJECT);
				//printf("EJECT\n");
            }
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			break;

		case 0xc0c0:

			if(key_state == 2)
			{
				call_ir_func(IRC_ONLY_PAUSE);
				//printf("EJECT\n");
            }
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			break;

		case 0x40C0:

			if(key_state == 2)
			{
				call_ir_func(IRC_BACKWARD);
				//printf("EJECT\n");
            }
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			break;

		case 0x4180:

			if(key_state == 2)
			{
				call_ir_func(IRC_FORWARD);
				//printf("EJECT\n");
            }
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			break;


		case 0xc180://GPIO14 IO2//PIN109


			if(key_state == 2)
			{
				call_ir_func(IRC_PREV);
				//printf("EJECT\n");
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			break;


		case 0xC140://VFD DATA


			if(key_state == 2)
			{
				//printf("STOP\n");
				call_ir_func(IRC_STOP);
			}
			//printf("SS:key_state=%x\n",key_state);
			key_state = 1;
			break;

		case 0xC100:


			if(key_state == 2)
			{
				call_ir_func(IRC_NEXT);
				//printf("EJECT\n");
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			break;

		case 0x41C0:

			//printf("Ppppppp:key_state=%x\n",key_state);
			if(key_state == 2)
			{
				//printf("PAUSEPLAY\n");
				
				if(Is_JPEG_SlideMode())
				{
					if(bJpgVFDPause == 0)
					{
						//bJpgVFDPause = 1;
						if(play_state == VCD_STATE_PAUSE)	//nono 2-6-28 14:00
						{
							bJpgVFDPause = 2;
							PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
						}
						else
							bJpgVFDPause = 1;
					}
					else if(bJpgVFDPause == 1)
					{
						bJpgVFDPause = 2;
					}
				}
				else
					call_ir_func(IRC_PLAY);
				
			}
			//printf("P:key_state=%x\n",key_state);
			key_state = 1;
			break;

		default:
			key_state = 2;
			break;
		}
	}
	else
	{
		//printf("out:key_state=%x\n",key_state);
		key_previ = key_data;
		key_state = 2;
		
	}

	
}

#elif defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_2290)



void check_hj_keylight_status(void)
{
	UINT32  key_data;//,key_data2;
	static int key_state = 0;//,key_state2 = 0;
	static UINT32 key_previ = 0xfff;//,key_previ2 = 0xfff;
	
	
	
	regs0->gpio_oe[54 / 16] &= (~0x1 << (54 % 16));
	regs0->gpio_oe[55 / 16] &= (~0x1 << (55 % 16));
	regs0->gpio_oe[56 / 16] &= (~0x1 << (56 % 16));
	key_data = (regs0->gpio_in[54 / 16] & (0x7 << (54 % 16)));
	
	           //printf("key_data=%x\n",key_data);
	//           printf("key_state=%x\n",key_state);
	//           printf("key_previ=%x\n",key_previ);
	
	
	if(key_data == key_previ)
	{
		//printf("1.key_previ=%x\n",key_previ);
		//key_previ = 0xf0;
		switch (key_data)
		{
			
		case 0x180://CLK GPIO54
			if(key_state == 2)
			{
				call_ir_func(IRC_EJECT);
				//printf("EJECT\n");
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			
			break;
			
		case 0x140://STB GPIO55
			//printf("Ppppppp:key_state2=%x\n",key_state2);
			if(key_state == 2)
			{
				//printf("PAUSEPLAY\n");
				
				if(Is_JPEG_SlideMode())
				{
					if(bJpgVFDPause == 0)
					{
						//bJpgVFDPause = 1;
						if(play_state == VCD_STATE_PAUSE)	//nono 2-6-28 14:00
						{
							bJpgVFDPause = 2;
							PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
						}
						else
							bJpgVFDPause = 1;
					}
					else if(bJpgVFDPause == 1)
					{
						bJpgVFDPause = 2;
					}
				}
				else
					call_ir_func(IRC_PLAY);
				
			}
			
			key_state = 1;
			//check_keylight_light_status();
			break;
		case 0x0C0://DATA GPIO56
			if(key_state == 2)
			{
				//printf("STOP\n");
				call_ir_func(IRC_STOP);
			}
			
			key_state = 1;
			break;
		
		
		default:
			key_state = 2;
			break;
		}
	}
	else
	{
		//printf("out:key_state=%x\n",key_state);
		key_previ = key_data;
		key_state = 2;
		
	}//if(key_data==key_previ) else ........
	
	
	
}

	//dingzhy   3-11-17 11:02
#elif defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313)

void CD_MP3_DVD_LIGHT_FOR_HJ( void )
{
    if(cd_type_loaded==CDDVD)
    {
        GPIO_O_SET(3,1);
        GPIO_O_SET(62,0);
        GPIO_O_SET(63,1);
    }
    else if(cd_type_loaded==CDROM)
    {
        GPIO_O_SET(3,0);
        GPIO_O_SET(62,1);
        GPIO_O_SET(63,1);
    }
    else if(cd_type_loaded==CDDA || cd_type_loaded==CDVCD10 || cd_type_loaded==CDVCD20 || cd_type_loaded==CDSVCD)
    {
        GPIO_O_SET(3,1);
        GPIO_O_SET(62,1);
        GPIO_O_SET(63,0);
    }
    else if(play_state == VCD_STATE_OPEN)
	{
        GPIO_O_SET(3,1);
        GPIO_O_SET(62,1);
        GPIO_O_SET(63,1);
    }     	
}


void check_hj_keylight_status(void)
{
	UINT32  key_data,key_data1,key_data2,key_data3,key_data4,key_data5;//,key_data2;
	static int key_state = 0;//,key_state2 = 0;
	static UINT32 key_previ = 0xfff;//,key_previ2 = 0xfff;
	
	
	key_data1 = (regs0->gpio_in[54 / 16] & (0x1 << (54 % 16)));
	key_data2 = (regs0->gpio_in[55 / 16] & (0x1 << (55 % 16)));
	key_data3 = (regs0->gpio_in[56 / 16] & (0x1 << (56 % 16)));
	key_data4 = (regs0->gpio_in[14 / 16] & (0x1 << (14 % 16)));
	key_data5 = (regs0->gpio_in[15 / 16] & (0x1 << (15 % 16)));
//	printf("key_data1=%x\n",key_data1);
//	printf("key_data2=%x\n",key_data2);
//	printf("key_data3=%x\n",key_data3);
	key_data =(key_data1|key_data2|key_data3|key_data4|key_data5);//15,14,6,7,8
	
	

//	printf("key_data=%x\n",key_data);
//	printf("key_previ=%x\n",key_previ);
	



	if(key_data == key_previ)
	{
		//printf("1.key_previ=%x\n",key_previ);
		//key_previ = 0xf0;

		switch (key_data)
		{
		case 0xc180:
#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY
			if(key_state == 2)
			{
				call_ir_func(IRC_STOP);
				
			}
			
			key_state = 1;
			break;
#else//USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY
			if(key_state == 2)
			{
				call_ir_func(IRC_BACKWARD);
				
			}
			
			key_state = 1;
			break; 
#endif//USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY

	    case 0xc140:
#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY
			if(key_state == 2)
			{
				call_ir_func(IRC_BACKWARD);
				
			}
			
			key_state = 1;
			break;  
#else//#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY

			if(key_state == 2)
			{
				call_ir_func(IRC_FORWARD);
				
			}
			
			key_state = 1;
			break;  
#endif//#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY
		case 0xc0c0:
#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY
			if(key_state == 2)
			{
				call_ir_func(IRC_FORWARD);
				
			}
			
			key_state = 1;
			break;  
#else//#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY

			if(key_state == 2)
			{
				call_ir_func(IRC_DEFAULT_SETUP);
				
			}
			
			key_state = 1;
			break;  
#endif//#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY

		case 0x81c0:
#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY
		       if(key_state == 2)	
		        {		 
				if(Is_JPEG_SlideMode())
				{
					if( (bJpgVFDPause == 1)||(bJpgVFDPause == 0) )
						{
							bJpgVFDPause = 2;
							PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
						}
				}
				else
					call_ir_func(IRC_PLAY);	
					

				
			   }			 			 
			   key_state = 1;
			break;  
#else//#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY

			//printf("Ppppppp:key_state=%x\n",key_state);
			if(key_state == 2)
			{
				//printf("PAUSEPLAY\n");
				
				if(Is_JPEG_SlideMode())
				{
					if(bJpgVFDPause == 0)
					{
						//bJpgVFDPause = 1;
						if(play_state == VCD_STATE_PAUSE)	//nono 2-6-28 14:00
						{
							bJpgVFDPause = 2;
							PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
						}
						else
							bJpgVFDPause = 1;
					}
					else if(bJpgVFDPause == 1)
					{
						bJpgVFDPause = 2;
					}
				}
				else
					call_ir_func(IRC_PAUSEPLAY);
				
			}
			//printf("P:key_state=%x\n",key_state);
			key_state = 1;
			break;
#endif//#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY

		case 0x41c0:
#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY
		       if(key_state == 2)			 
		      {			 
				if(Is_JPEG_SlideMode())
				{
				bJpgVFDPause = 1;
				
				}else
				call_ir_func(IRC_ONLY_PAUSE);			 			 
			  }		 			 
			   key_state = 1;
			break;  
#else//#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY

			if(key_state == 2)
			{
				call_ir_func(IRC_STOP);
				
			}
			
			key_state = 1;
			break;
#endif//#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY

		case 0x1c0:

			if(key_state == 2)
			{
				call_ir_func(IRC_EJECT);
				
			}
			
			key_state = 1;
			break; 
		default:
			key_state = 2;
			break;  
		       
	    }
	}
    else
	{
		//printf("out:key_state=%x\n",key_state);
		key_previ = key_data;
		key_state = 2;
		
	}
    //dingzhy  3-11-17 10:08
    CD_MP3_DVD_LIGHT_FOR_HJ();


}


#else//USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_2326

void check_hj_keylight_status(void)
{

	UINT32  key_data;
	UINT32  key_data1;
	UINT32  key_data2;
//	UINT32  key_data3;
	static int key_state = 0;
	static UINT32 key_previ = 0xffff;
	
//	regs0->gpio_oe[54 / 16] &= ~(0x7 << (54 % 16));
//	regs0->gpio_oe[42 / 16] &= ~(0x3 << (42 % 16));

	//key_data = ((regs0->gpio_in[42 / 16] & (0x3 << (42 % 16))) |(regs0->gpio_in[54 / 16] & (0x7 << (54 % 16))) );
	//key_data =(( regs0->gpio_in[42 / 16] & (0x3 << (42 % 16))) |(regs0->gpio_in[54 / 16] & (0x7 << (54 % 16))) );
	key_data1 = regs0->gpio_in[14 / 16] & (0x3 << (14 % 16));//14
	key_data2 = regs0->gpio_in[54 / 16] & (0x7 << (54 % 16));//6,7,8
//	key_data2 = regs0->gpio_in[4 / 16] & (0x1 << (4 % 16));//4
//	key_data3 = regs0->gpio_in[54 / 16] & (0x7 << (54 % 16));//6,7,8
	key_data =(key_data1|key_data2);//15,14,6,7,8
	
	//printf("key_data=%x\n",key_data);
	//return;
	//printf("regs0->sft_cfg6=%x\n",regs0->sft_cfg6);
	//printf("regs0->gpio_oe[14 / 16]=%x\n",regs0->gpio_oe[14 / 16] );

	//printf("key_state=%x\n",key_state);
	//printf("key_previ=%x\n",key_previ);
	//regs0->gpio_out[56 / 16] &= ~(0x1 << (56 % 16));



	if(key_data == key_previ)
	{
		//printf("1.key_previ=%x\n",key_previ);
		//key_previ = 0xf0;

		switch (key_data)
		{
		case 0x81C0://GPIO15 IO1//PIN121


			if(key_state == 2)
			{
				call_ir_func(IRC_NEXT);
				//printf("EJECT\n");
            }
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			break;


		case 0x41C0://GPIO14 IO2//PIN109


			if(key_state == 2)
			{
				call_ir_func(IRC_PREV);
				//printf("EJECT\n");
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			break;


		case 0xC0C0://VFD DATA


			if(key_state == 2)
			{
				//printf("STOP\n");
				call_ir_func(IRC_STOP);
			}
			//printf("SS:key_state=%x\n",key_state);
			key_state = 1;
			break;

		case 0xC180://VFD CLK


			if(key_state == 2)
			{
				call_ir_func(IRC_EJECT);
				//printf("EJECT\n");
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			break;

		case 0xC140://VFD STB

			//printf("Ppppppp:key_state=%x\n",key_state);
			if(key_state == 2)
			{
				//printf("PAUSEPLAY\n");
				
				if(Is_JPEG_SlideMode())
				{
					if(bJpgVFDPause == 0)
					{
						//bJpgVFDPause = 1;
						if(play_state == VCD_STATE_PAUSE)	//nono 2-6-28 14:00
						{
							bJpgVFDPause = 2;
							PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
						}
						else
							bJpgVFDPause = 1;
					}
					else if(bJpgVFDPause == 1)
					{
						bJpgVFDPause = 2;
					}
				}
				else
					call_ir_func(IRC_PAUSEPLAY);
				
			}
			//printf("P:key_state=%x\n",key_state);
			key_state = 1;
			break;

		default:
			key_state = 2;
			break;
		}
	}
	else
	{
		//printf("out:key_state=%x\n",key_state);
		key_previ = key_data;
		key_state = 2;
		
	}

	
}

#endif//USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_2326

#elif defined(USE_VFDPORT_TO_KEYLIGHT_GBM)

#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)
extern BYTE key_data_flag;
#endif//#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)

#ifdef NEW_GBM_VFD_GPIO_KEY				//gerry,2004/2/11 05:58¤U¤È
void check_gbm_keylight_status(void)
{

	UINT32  key_data;
	static int key_state = 0;
	static UINT32 key_previ = 0xfff;
	
	//init_keylight_io();
	regs0->gpio_oe[56 / 16] &= (~0x1 << (56 % 16));
	regs0->gpio_oe[54 / 16] &= (~0x1 << (54 % 16));
	regs0->gpio_oe[55 / 16] &= (~0x1 << (55 % 16));

	key_data = (regs0->gpio_in[54 / 16] & (0x7 << (54 % 16)));
	
	if(key_data == key_previ)
	{
		//printf("1.key_previ=%x\n",key_previ);
		//key_previ = 0xf0;
		switch (key_data)
		{
		
		case 0x180:
		
			if(key_state == 2)
			{
				
				call_ir_func(IRC_PLAY);
				//printf("EJECT\n");
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			
			break;
		case 0x140:
		
			if(key_state == 2)
			{
			    call_ir_func(IRC_EJECT); //call_ir_func(IRC_PAUSEPLAY);//HHQ
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			
			break;
		case 0xC0:
		
			if(key_state == 2)
			{
				call_ir_func(IRC_STOP);
				//printf("STOP\n");
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			
			break;
		case 0x80:
		
			if(key_state == 2)
			{
				//gpio_key_only_next();
				//gpio_key_only_prev();
				#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)
				key_data_flag=1;
				#endif//#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)
				call_ir_func(IRC_PREV);
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			
			break;
		case 0x100:
		
			if(key_state == 2)
			{
				//gpio_key_only_prev();
				//gpio_key_only_next();
				#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)
				key_data_flag=1;
				#endif//#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)
				call_ir_func(IRC_NEXT);
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			
			break;
		default:
			key_state = 2;
			break;
		}
	}
	else
	{
		//printf("out:key_state=%x\n",key_state);
		key_previ = key_data;
		key_state = 2;
#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)
		key_data_flag=0;
#endif//#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)	
	}
		
}

#else//NEW_GBM_VFD_GPIO_KEY
void check_gbm_keylight_status(void)
{

	UINT32  key_data;
	static int key_state = 0;
	static UINT32 key_previ = 0xfff;

	//init_keylight_io();
//	regs0->gpio_oe[56 / 16] |= (0x1 << (56 % 16));
	regs0->gpio_oe[54 / 16] &= (~0x1 << (57 % 16));
	regs0->gpio_oe[55 / 16] &= (~0x1 << (58 % 16));
//	regs0->gpio_out[58 / 16] &= ~(0x1 << (58 % 16));
//	return;
	key_data = (regs0->gpio_in[54 / 16] & (0x3 << (54 % 16)));
	
	//printf("key_data=%x\n",key_data);
	//printf("key_state=%x\n",key_state);
	//printf("key_previ=%x\n",key_previ);
	//regs0->gpio_out[56 / 16] &= ~(0x1 << (56 % 16));

	regs0->gpio_oe[54 / 16] |= (0x7 << (54 % 16));
	regs0->gpio_out[56 / 16] &= ~(0x1 << (56 % 16));
	regs0->gpio_out[54 / 16] |= (0x3 << (54 % 16));
		
	if(key_data == key_previ)
	{
		//printf("1.key_previ=%x\n",key_previ);
		//key_previ = 0xf0;
		switch (key_data)
		{
		
		case 0x80:
		
			if(key_state == 2)
			{
				
				call_ir_func(IRC_EJECT);
				//printf("EJECT\n");
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			
			break;
		case 0x00:
		
			if(key_state == 2)
			{
                safe_srn_off();
                save_srn_start_t = get_rtc_val();
   				if(Is_JPEG_SlideMode())
				{
					if(bJpgVFDPause == 0)
					{
						if(play_state == VCD_STATE_PAUSE)	//nono 2-6-28 14:00
						{
							bJpgVFDPause = 2;
							PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);
							return;
						}
						else
						{
							bJpgVFDPause = 1;
						}
					}
					else if(bJpgVFDPause == 1)
					{
						bJpgVFDPause = 2;
						PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);
					}
				}
				else
				    call_ir_func(IRC_PAUSEPLAY);
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			
			break;
		case 0x40:
		
			if(key_state == 2)
			{
				call_ir_func(IRC_STOP);
				//printf("STOP\n");
			}
			//printf("EEE:key_state=%x\n",key_state);
			key_state = 1;
			
			break;
		default:
			key_state = 2;
			break;
		}
	}
	else
	{
		//printf("out:key_state=%x\n",key_state);
		key_previ = key_data;
		key_state = 2;
		
	}
	
	regs0->gpio_oe[54 / 16] |= (0x7 << (54 % 16));
	regs0->gpio_out[56 / 16] &= ~(0x1 << (56 % 16));
	regs0->gpio_out[54 / 16] |= (0x3 << (54 % 16));
	
}
#endif//NEW_GBM_VFD_GPIO_KEY

#elif defined(USE_VFDPORT_TO_KEYLIGHT_MINTON)

#if defined(MINTON_YILI_DVD1003_2CH)

void check_light_status(void)  
{

	static BYTE minton_led_flag;
	
	if( (play_state == VCD_STATE_STOP)||(play_state == VCD_STATE_OPEN)||(system_state == SYSTEM_NODISC) )
		GPIO_O_SET(14,0);//off
	else if( (play_state == VCD_STATE_READTOC)||(play_state == VCD_STATE_CLOSE) )
	{
		
		minton_led_flag++;		
		if(minton_led_flag<=10)
		{
			GPIO_O_SET(14,1);//on
		}
		else if( (minton_led_flag<=20)&&(minton_led_flag>10) )
			GPIO_O_SET(14,0);//off
			
		if(minton_led_flag==20)
			minton_led_flag=0;
		
	}
	else 
		GPIO_O_SET(14,1);//on
}

//*********************************************
#define SCAN_KEY_1	54
#define SCAN_KEY_2	55
#define SCAN_KEY_3	56	
void check_minton_keylight_status(void)
{
	static BYTE key_previ = 0xff;	//for debounce,2004-3-16 18:49
	BYTE  key_data = 0;				
	static int key_state = 0;		//a flag, 0:scan key, 1~15: free
	
	check_light_status();           //PLAY-LED blink when loading disk
	
	if(key_state<1)
	{   
		//use GPIO 54~56 as input port, scan panel-key, 2004-3-16 18:54
		GPIO_E_SET(SCAN_KEY_1, 0);		//0 for input.
		GPIO_E_SET(SCAN_KEY_2, 0);
		GPIO_E_SET(SCAN_KEY_3, 0);
		key_data =(GPIO_I_GET(SCAN_KEY_1)<<2)|(GPIO_I_GET(SCAN_KEY_2)<<1)|GPIO_I_GET(SCAN_KEY_3);
	}
	else
	{   
		key_data = 0x07;
	}

	key_state++;
	if(key_state==15)
		key_state = 0;
	
	///////////////////////////////////////////////////2004-3-16 18:58
	//process the keys.
	
	if(key_data==0x07)//all three GPIO lines input HIGH. that is, no press any key.
	{
		//set GPIO 54~56 output LOW for three LEDs. 2004-3-16 18:54		
		GPIO_E_SET(SCAN_KEY_1, 1);
		GPIO_E_SET(SCAN_KEY_2, 1);
		GPIO_E_SET(SCAN_KEY_3, 1);

		GPIO_O_SET(SCAN_KEY_1, 0);
		GPIO_O_SET(SCAN_KEY_2, 0);
		GPIO_O_SET(SCAN_KEY_3, 0);
		return 0;
	}	
	
	#ifdef VFD_KEY_TEST
	psprintf(RegionValStr[REGION1], "KEY %02d", key_data);
	PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);			
	return 0;
	#endif
	
	if(key_data==key_previ)	
	{
		key_previ= 0xff;
		switch (key_data)
		{
			case 0x05:  //PREV
	    	   	call_ir_func(IRC_PREV);			 
		   		break;
		   		
			case 0x01:  //PAUSE		    	 
				if(Is_JPEG_SlideMode())
				{
					bJpgVFDPause = 1;
					return;
				}else
					call_ir_func(IRC_ONLY_PAUSE);	
		   		break;
		   		
			case 0x04:  //PLAY	           		 
				if(Is_JPEG_SlideMode())
				{
					if( (bJpgVFDPause == 1)||(bJpgVFDPause == 0) )
					{
						bJpgVFDPause = 2;
						PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
					}
				}
				else
					call_ir_func(IRC_PLAY_RESUME);	
		        break;

			case 0x02:  //STOP		           
				call_ir_func(IRC_STOP); 	
		        break;

			case 0x06:  //NEXT		           		 
				call_ir_func(IRC_NEXT);		
		        break; 
		          
			default:	
				break;
		}//end switch(key_data)
	}
	else//first check Gpio key state
	{
		key_previ=key_data;			
	}	
			return 0;
}
#elif defined(MINTON_YILI_LCD1003_6CH)//MINTON_YILI_DVD1003_2CH, 2004-3-19 22:39

void check_light_status(void)         /////alex 20040228
{  	if(system_state!=SYSTEM_POWER)
	{
	 	GPIO_O_SET(14,0);//off
	}
	else 
	{
		GPIO_O_SET(14,1);//on	
	}
}

void check_minton_keylight_status(void)
{
	check_light_status();
}

#else//MINTON_YILI_DVD1003_2CH

void check_light_status(void)  
{

	static BYTE minton_led_flag;
	
	if( (play_state == VCD_STATE_STOP)||(play_state == VCD_STATE_OPEN)||(system_state == SYSTEM_NODISC) )
		GPIO_O_SET(14,0);//off
	else if( (play_state == VCD_STATE_READTOC)||(play_state == VCD_STATE_CLOSE) )
	{
		
		minton_led_flag++;		
		if(minton_led_flag<=10)
		{
			GPIO_O_SET(14,1);//on
		}
		else if( (minton_led_flag<=20)&&(minton_led_flag>10) )
			GPIO_O_SET(14,0);//off
			
		if(minton_led_flag==20)
			minton_led_flag=0;
		
	}
	else 
		GPIO_O_SET(14,1);//on
}

//******************************************
	//   DATA        gpio56       IN/OUT
	//   STB         gpio57       IN/OUT
	//   CLK         gpio58       IN/OUT
void check_minton_keylight_status(void)
{
	UINT32  key_data;
	static int key_state = 0;
	static UINT32 key_previ = 0xfff;
	static BYTE minton_key_flag;

	check_light_status();
	
    if(minton_key_flag<3)
    {
	    regs0->gpio_oe[54 / 16] &= ~(0x7 << (54 % 16));
	
	 
    	key_data = regs0->gpio_in[54 / 16] & (0x7 << (54 % 16));
    	//printf("key_data=%x\n",key_data);
    	//printf("key_state=%x\n",key_state);
    	//printf("key_previ=%x\n",key_previ);
    	//regs0->gpio_out[56 / 16] &= ~(0x7 << (56 % 16));
    	
    	if(key_data == key_previ)
    	{
    		switch (key_data)
    		{
    		case 0x180:  //PREV
    		    if(key_state == 2)			 
    				call_ir_func(IRC_PREV);			 			 
    		    key_state = 1;
    		    break;
    		case 0x100:  //PAUSE
    		    if(key_state == 2)			 
    		    {			 
    		        if(Is_JPEG_SlideMode())
    				{
    				    bJpgVFDPause = 1;
    				
    				}else
    				call_ir_func(IRC_ONLY_PAUSE);			 			 
    		    }		 			 
    		    key_state = 1;
    		    break;
    		case 0x80:  //PLAY
    		    if(key_state == 2)	
    		    {		 
    				if(Is_JPEG_SlideMode())
    				{
    					if( (bJpgVFDPause == 1)||(bJpgVFDPause == 0) )
    			        {
    					    bJpgVFDPause = 2;
    					    PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
    				    }
    				}
    				else
    					call_ir_func(IRC_PLAY_RESUME);	
    		    }			 			 
    		    key_state = 1;
    		    break;
    		case 0x40:  //STOP
    		    if(key_state == 2)
    		        call_ir_func(IRC_STOP); 
    		    key_state = 1;
    		    break;
    		case 0xC0:  //NEXT
    		    if(key_state == 2)			 
    				call_ir_func(IRC_NEXT);			 			 
    		    key_state = 1;
    		    break;           
    		 		 
    		 
    		default:
    			key_state = 2;
    			break;
    		}
    	}
    	else
    	{
    		//printf("out:key_state=%x\n",key_state);
    		key_previ = key_data;
    		key_state = 2;
    		
    	}
    }else if( (minton_key_flag>=3)&&(minton_key_flag<20) )//if(minton_key_flag<5)	
    {
    	regs0->gpio_oe[54 / 16] |= (0x7 << (54 % 16));
    	regs0->gpio_out[54 / 16] &= ~(0x3 << (54 % 16));
    	regs0->gpio_out[56 / 16] |= (0x1 << (56 % 16));
    }	

	minton_key_flag++;
	if(minton_key_flag==20) minton_key_flag=0;

}
#endif//MINTON_YILI_DVD1003_2CH

//void check_light_status(void)               
//moved before  check_minton_keylight_status(), hq,2004-3-19 22:43
		
#elif defined(USE_VFDPORT_TO_KEYLIGHT_IDALL)
void check_idall_keylight_status(void)
{
    UINT32 key_data1=0, key_data2=0, key_data3=0;
    UINT32 key_data = 0;
    static UINT8 key_state = 0;
    static UINT32 key_prev = 0xffffffff;
    static UINT8 key_scan = 0;
    
    regs0->gpio_out[55/16] |= (0x1<<(55%16));
    regs0->gpio_out[56/16] &= ~(0x1<<(56%16));
    key_scan = 1;

    key_data1 = regs0->gpio_in[14 / 16] & (0x1 << (14 % 16));
    
    key_data2 = regs0->gpio_in[36 / 16] & (0x1 << (36 % 16));
    
    key_data3 = regs0->gpio_in[54 / 16] & (0x1 << (54 % 16));
    
    key_data = key_data1|key_data2|key_data3;

    if(key_data==0)
    {
        regs0->gpio_out[55/16] &= ~(0x1<<(55%16));
        regs0->gpio_out[56/16] |= (0x1<<(56%16));
        key_scan = 2;
        key_data1 = regs0->gpio_in[14 / 16] & (0x1 << (14 % 16));
    
        key_data2 = regs0->gpio_in[36 / 16] & (0x1 << (36 % 16));
        
        key_data3 = regs0->gpio_in[54 / 16] & (0x1 << (54 % 16));
        
       
        key_data = key_data1|key_data2|key_data3;
		
        if(key_data==0)
        {
            key_scan = 0;
        }
    }
	
    if(key_data==key_prev)
    {
        switch(key_data)
        {
            case 0x4000:
                if(key_state==2)
                {
                    if(key_scan ==1)
                        call_ir_func(IRC_PREV);
                    else if(key_scan==2)
                        call_ir_func(IRC_EJECT);
                }
                key_state = 1;
                break;
            case 0x0010:
                if(key_state==2)
                {
                    if(key_scan==1)
                        call_ir_func(IRC_NEXT);
                    else if(key_scan==2)
                        call_ir_func(IRC_CHANNEL);
                }
                key_state = 1;
                break;
            case 0x0040:
                if(key_state ==2)
                {
                    if(key_scan==1)
                        call_ir_func(IRC_PAUSEPLAY);
                    else if(key_scan==2)
                        call_ir_func(IRC_STOP);
                }
                key_state = 1;
                break;
            default:
                key_state = 2;
                break;
        }
        if(key_state==1)
        {
            UINT32 temp = 0;

            for(temp = 0;temp<0xffff;temp++)
            {
                regs0->gpio_out[55/16] &= ~(0x1<<(55%16));
                regs0->gpio_out[56/16] |= (0x1<<(56%16));
            }
            
        }
    }
    else
    {
        key_prev = key_data;
        key_state = 2;
    }
    regs0->gpio_out[55/16] |= (0x1<<(55%16));
    regs0->gpio_out[56/16] &= ~(0x1<<(56%16));
	
}

#elif defined(USE_VFDPORT_TO_KEYLIGHT_THAKRAL)
void check_thakral_keylight_status(void)
{
    //pin70--gpio35 control the light
    //others to scan the key input
    UINT32 key_data1=0; //-->gpio54 pin154
    UINT32 key_data2=0; //-->gpio55 pin155
    UINT32 key_data3=0; //-->gpio56 pin156
    UINT32 key_data4=0; //-->gpio36 pin71
    UINT32 key_data = 0;
    #define TIME_MASK   0x10
    static UINT8 key_state = 0;
    static UINT32 key_prev = 0xffffffff;
    static UINT8 key_scan = 0;
    static UINT8 counter_0 = TIME_MASK;
    static UINT8 counter_1 = 1;//TIME_MASK;
    
    if((counter_1 == 1))
    {
    
    regs0->gpio_out[35/16] |= (0x1<<(35%16));
    regs0->gpio_oe[36/16] |= (0x1<<(36%16));
    regs0->gpio_out[36/16] &= ~(0x1<<(36%16));
    
    key_scan = 1;

    key_data1 = regs0->gpio_in[54 / 16] & (0x1 << (54 % 16));    
    key_data2 = regs0->gpio_in[55 / 16] & (0x1 << (55 % 16));    
    key_data3 = regs0->gpio_in[56 / 16] & (0x1 << (56 % 16));    
    //key_data4 = regs0->gpio_in[36 / 16] & (0x1 << (36 % 16));

    key_data = key_data1|key_data2|key_data3;
    //if(key_data!=0x01d0)
//    printf("\n thakral key_data1 = 0x%04x\n",key_data1);
//    printf("\n thakral key_data2 = 0x%04x\n",key_data2);
//    printf("\n thakral key_data3 = 0x%04x\n",key_data3);
//    printf("\n thakral key_data4 = 0x%04x\n",key_data4);
//    printf("\n thakral key_data = 0x%04x\n",key_data);

        counter_0--;
        //printf("000 counter_0 : %x counter_1 : %x\n",counter_0,counter_1);
        if(counter_0==1)
            counter_1 = TIME_MASK;
    }
       
    //if((key_data==0x01c0)&&(counter_0==1))
    if(counter_0 == 1)
    {
        regs0->gpio_out[35/16] &= ~(0x1<<(35%16));
        regs0->gpio_oe[36/16] &=  ~(0x1<<(36%16));
        //regs0->gpio_out[36/16] &= ~(0x1<<(35%16));

        key_scan = 2;

        key_data1 = regs0->gpio_in[54 / 16] & (0x1 << (54 % 16));    
        key_data2 = regs0->gpio_in[55 / 16] & (0x1 << (55 % 16));    
        key_data3 = regs0->gpio_in[56 / 16] & (0x1 << (56 % 16));    
        key_data4 = regs0->gpio_in[36 / 16] & (0x1 << (36 % 16));        
       
        key_data = key_data1|key_data2|key_data3;
		    
        if(key_data4==0x0)
        {
            regs0->gpio_out[35/16] |= (0x1<<(35%16));
            regs0->gpio_oe[36/16] |= (0x1<<(36%16));
            regs0->gpio_out[36/16] |= (0x1<<(36%16));
            call_ir_func(IRC_POWER);
        }
        
        if(key_data==0x01c0)
        {
            key_scan = 0;
        }
        //if((counter_1 > 1))
            counter_1--;
        //printf("111 counter_0 : %x counter_1 : %x\n",counter_0,counter_1);
        if(counter_1 == 1)
            counter_0 = TIME_MASK;
            //printf("\n thakral key_data4 = 0x%04x\n",key_data4);
    }
	
    if(key_data==key_prev)
    {
        switch(key_data)
        {            
            case 0x00c0:
                if(key_state ==2)
                {
                    if(key_scan ==1)
                    {
                        call_ir_func(IRC_PLAY_RESUME);
                    }
                    else if(key_scan ==2)
                    {
                        call_ir_func(IRC_STOP);
                    }
                }
                key_state = 1;
                break;
            case 0x0140:
                if(key_state==2)
                {
                    if(key_scan ==1)
                    {
                        call_ir_func(IRC_EJECT);
                    }
                    else if(key_scan ==2)
                    {
                        call_ir_func(IRC_ONLY_PAUSE);
                    }
                }
                key_state = 1;
                break;
            case 0x0180:
                if(key_state ==2)
                {
                    if(key_scan ==1)
                    {
                        call_ir_func(IRC_NEXT);
                    }
                    else if(key_scan ==2)
                    {
                        call_ir_func(IRC_PREV);
                    }
                }
                key_state = 1;
                break;
            default:
                key_state = 2;
                break;
        }
        if(key_state==1)
        {
            UINT32 temp = 0;

            for(temp = 0;temp<0xffff;temp++)
            {/*
                if(key_scan==1)
                regs0->gpio_out[35/16] |= (0x1<<(35%16));
                else if(key_scan==2)
                regs0->gpio_out[35/16] &= ~(0x1<<(35%16));
                //regs0->gpio_out[56/16] |= (0x1<<(56%16));
           */ }            
            counter_0 = TIME_MASK;counter_1 = 1;        
            }            
        
    }
    else
    {
        key_prev = key_data;
        key_state = 2;
    }
}

#elif defined(HANYANG_SCAN_KEY)
/*
void check_hanyang_led(void)//2004/6/14 09:25ÏÂÎç caoh
{
    static BYTE change_led = 0;
    
    if(play_state==VCD_STATE_CLOSE)
    {
        GPIO_E_SET(54,1);//set  CLK as output
        GPIO_E_SET(56,1);//set  DATA as output  
     
        change_led++;
        
        if(change_led<50)           
        {     
            GPIO_O_SET(54,0);
            GPIO_O_SET(56,0);
        }      
        else
        {      
            GPIO_O_SET(54,0);
            GPIO_O_SET(56,1);
            if(change_led>200)
                change_led = 0;
        }    
    }    
}

void check_hanyang_next_and_prev(void)
{
    static BYTE key_state1 = 0;  
    static int count0=0,count1=0,count2=1,count3=1;
    static BYTE key_state_flagkey1=0,key_state_flagkey2=0;
    switch(key_state1)
    {
      case  0:
            GPIO_E_SET(54,0);//set  CLK as input
            GPIO_E_SET(56,0);//set  DATA as input
            GPIO_O_SET(55,0);
            GPIO_O_SET(57,1);
            GPIO_O_SET(18,1);
            if(!key_state_flagkey1)
			{
             if((GPIO_I_GET(56))&&(!GPIO_I_GET(54)))
                {
                	count0++;
                    if(count0>150*count2)
                    { 
                    	call_ir_func(IRC_FORWARD);
                        count2++;
                   	}
                } 
             else
                {
                	key_state_flagkey1 = 0;
                    key_state1 = 1; 
                    if(play_state==VCD_STATE_CLOSE)
                    {
                        check_hanyang_led();
                    }       
                  else
                  {
                   if(count0<40&&count0>10)
                   	{
                         call_ir_func(IRC_NEXT);
                         count0=0;
                   	}	 
                   	else
                   	{
                          count0=0;
                          count2=1;
                     }
                        GPIO_E_SET(54,1);//set  CLK as output
                        GPIO_E_SET(56,1);//set  DATA as output
                        GPIO_O_SET(54,0);
                        GPIO_O_SET(56,1);
                    }
                  }                   
                  }                   
             if((GPIO_I_GET(56))&&(GPIO_I_GET(54)))
              {
                key_state_flagkey1 = 0;
               }  
             break;
       case  1:
            GPIO_E_SET(54,0);//set  CLK as input
            GPIO_E_SET(56,0);//set  DATA as input
            GPIO_O_SET(55,1);
            GPIO_O_SET(57,1);
            GPIO_O_SET(18,0);
            if(!key_state_flagkey2)
            {
               if((GPIO_I_GET(56))&&(!GPIO_I_GET(54)))
                {
                    count1++;
                    if(count1>150*count3)
                    { 
                        call_ir_func(IRC_BACKWARD);
                        count3++;       
                    }     
                } 
                else
                {
                    key_state_flagkey2 = 0;
                    key_state1 = 0; 
                    if(play_state==VCD_STATE_CLOSE)
                    {
                        check_hanyang_led();
                    }       
                    else
                    {    
                        if(count1<40&&count1>10)
                        {
                            call_ir_func(IRC_PREV);
                            count1=0;
                        }   
                        else
                        {
                            count1=0;
                            count3=1;
                        }      
                        GPIO_E_SET(54,1);//set  CLK as output
                        GPIO_E_SET(56,1);//set  DATA as output
                        GPIO_O_SET(54,0);
                        GPIO_O_SET(56,1);
                    }   
                }             
                }             
            if((GPIO_I_GET(56))&&(GPIO_I_GET(54)))
            {
                key_state_flagkey2 = 0;
            }    
            break;
       default : break;
       }
}

void check_hanyang_keylight_status(void)  //caoh 2004-4-19 11:30
{
	static BYTE key_state = 0;  
	static BYTE key_state_flag1=0,key_state_flag2=0, key_state_flag3=0;  
	switch(key_state)
    {
		case  0:
            GPIO_E_SET(54,0);//set  CLK as input
            GPIO_E_SET(56,0);//set  DATA as input
            GPIO_O_SET(55,0);
            GPIO_O_SET(57,1);
            GPIO_O_SET(18,1);
			if(!key_state_flag1)
			{
            	if((!GPIO_I_GET(56))&&(GPIO_I_GET(54)))
				{ 
                    call_ir_func(IRC_POWER);
                    key_state_flag1=1;
                }
                else
                {
                	key_state_flag1=0;
                    key_state = 1; 
                    
                    if(play_state==VCD_STATE_CLOSE)
                    {
                    	check_hanyang_led();
                    }                      
                    else
                    {
                        GPIO_E_SET(54,1);//set  CLK as output
                        GPIO_E_SET(56,1);//set  DATA as output
                        GPIO_O_SET(54,0);
                        GPIO_O_SET(56,1);
                    }
                 }
              }
                   
             if((GPIO_I_GET(56))&&(GPIO_I_GET(54)))
             {
                key_state_flag1=0;
             }  
             break;
        case  1:
            GPIO_E_SET(54,0);//set  CLK as input
            GPIO_E_SET(56,0);//set  DATA as input
            GPIO_O_SET(55,1);
            GPIO_O_SET(57,1);
            GPIO_O_SET(18,0);
            if(!key_state_flag2)
            {
                if((!GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                { 
                    call_ir_func(IRC_STOP);
                    key_state_flag2=1;
                }
                else
                {
                    key_state = 2; 
                    if(play_state==VCD_STATE_CLOSE)
                    {
                        check_hanyang_led();
                    }        
                    else
                    {
                        GPIO_E_SET(54,1);//set  CLK as output
                        GPIO_E_SET(56,1);//set  DATA as output
                        GPIO_O_SET(54,0);
                        GPIO_O_SET(56,1);
                    }   
                }
            }              
            if((GPIO_I_GET(56))&&(GPIO_I_GET(54)))
            {
                key_state_flag2=0;
            }    
            break;
        case  2:
            GPIO_E_SET(54,0);//set  CLK as input
            GPIO_E_SET(56,0);//set  DATA as input
            GPIO_O_SET(55,1);
            GPIO_O_SET(57,0);
            GPIO_O_SET(18,1);
            if(!key_state_flag3)
            {
                if((!GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                { 
                    call_ir_func(IRC_PAUSEPLAY);
                    save_srn_start_t = get_rtc_val();
                    key_state_flag3=1;
                }
                else if((GPIO_I_GET(56))&&(!GPIO_I_GET(54)))
                {
                    call_ir_func(IRC_EJECT);
                    save_srn_start_t = get_rtc_val();
                    key_state_flag3=1;                           
                } 
                else
                {
                    key_state = 0; 
                    if(play_state==VCD_STATE_CLOSE)
                    {
                        check_hanyang_led();
                    }        
                    else
                    {
                        GPIO_E_SET(54,1);//set  CLK as output
                        GPIO_E_SET(56,1);//set  DATA as output
                        GPIO_O_SET(54,0);
                        GPIO_O_SET(56,1);
                    }
                }
            }
            
            if((GPIO_I_GET(56))&&(GPIO_I_GET(54)))
            {
                key_state_flag3=0;
            }  
            break; 
    	default :  break;
    }
}*/
void check_hanyang_led(void)//2004/6/14 09:25ÏÂÎç caoh
{
  static BYTE change_led = 0;
  if(play_state==VCD_STATE_CLOSE)
   {
     GPIO_E_SET(54,1);//set  CLK as output
     GPIO_E_SET(56,1);//set  DATA as output

     change_led++;
     if(change_led<15)
     {
        GPIO_O_SET(54,0);
        GPIO_O_SET(56,0);
      }

     else
     {
        GPIO_O_SET(54,0);
        GPIO_O_SET(56,1);
         if(change_led>30)
           change_led = 0;
     }
   }
}

void check_hanyang_keylight_status(void)  //caoh 2004-4-19 11:30
{
   static BYTE key_state = 0;
   static int count0=0,count1=0,count2=1,count3=1;
   static BYTE key_state_flag1=0,key_state_flag2=0, key_state_flag3=0;

   switch(key_state)
    {
           case  0:

                   GPIO_E_SET(54,0);//set  CLK as input
                   GPIO_E_SET(56,0);//set  DATA as input
                   GPIO_O_SET(55,0);
                   GPIO_O_SET(57,1);
                   GPIO_O_SET(18,1);
                   if(!key_state_flag1)
                   {
                   if((!GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   {
                           call_ir_func(IRC_POWER);
                           key_state_flag1=1;
                   }
                   else if((GPIO_I_GET(56))&&(!GPIO_I_GET(54)))
                   {
                             count0++;
                             if(count0>150*count2)
                            {
                           call_ir_func(IRC_FORWARD);
                            count2++;
                          }
                   }
                   else
                   {
                         key_state_flag1=0;
                            if(play_state==VCD_STATE_CLOSE)
                                {
                                  check_hanyang_led();
                                  key_state = 1;
                                }
                             else
                                {
                           if(count0<40&&count0>10)
                           {
                            call_ir_func(IRC_NEXT);
                            count0=0;
                           }
                           else
                           {
                            count0=0;
                            count2=1;
                           }
                        GPIO_E_SET(54,1);//set  CLK as output
                        GPIO_E_SET(56,1);//set  DATA as output
                        GPIO_O_SET(54,0);
                        GPIO_O_SET(56,1);
                                    key_state = 1;
                        }
                    }
                   }

                  if((GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   {
                         key_state_flag1=0;
                   }
                   break;
           case  1:

                   GPIO_E_SET(54,0);//set  CLK as input
                   GPIO_E_SET(56,0);//set  DATA as input
                   GPIO_O_SET(55,1);
                   GPIO_O_SET(57,1);
                   GPIO_O_SET(18,0);
                   if(!key_state_flag2)
                   {
                   if((!GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   {
                           call_ir_func(IRC_STOP);
                           key_state_flag2=1;
                   }
                   else if((GPIO_I_GET(56))&&(!GPIO_I_GET(54)))
                   {
                            count1++;
                           if(count1>150*count3)
                            {
                           call_ir_func(IRC_BACKWARD);
                            count3++;
                            }
                   }
                   else
                   {
                           if(play_state==VCD_STATE_CLOSE)
                                {
                                  check_hanyang_led();
                                  key_state = 2;
                                }
                           else
                           {
                           if(count1<40&&count1>10)
                           {
                            call_ir_func(IRC_PREV);
                            count1=0;
                           }
                           else
                           {
                           count1=0;
                           count3=1;
                           }
                        GPIO_E_SET(54,1);//set  CLK as output
                        GPIO_E_SET(56,1);//set  DATA as output
                        GPIO_O_SET(54,0);
                        GPIO_O_SET(56,1);
                                      key_state = 2;
                     }
                    }
                   }
                   if((GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   {
                         key_state_flag2=0;
                   }
                   break;
           case  2:

                   GPIO_E_SET(54,0);//set  CLK as input
                   GPIO_E_SET(56,0);//set  DATA as input
                   GPIO_O_SET(55,1);
                   GPIO_O_SET(57,0);
                   GPIO_O_SET(18,1);
                    if(!key_state_flag3)
                   {
                   if((!GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   {
                           call_ir_func(IRC_PAUSEPLAY);
                           save_srn_start_t = get_rtc_val();
                           key_state_flag3=1;

                   }
                   else if((GPIO_I_GET(56))&&(!GPIO_I_GET(54)))
                   {
                           call_ir_func(IRC_EJECT);
                           save_srn_start_t = get_rtc_val();
                           key_state_flag3=1;
                   }
                   else
                   {
                          if(play_state==VCD_STATE_CLOSE)
                                {
                                  check_hanyang_led();
                                  key_state = 0;
                                }
                           else
                    {
                        GPIO_E_SET(54,1);//set  CLK as output
                        GPIO_E_SET(56,1);//set  DATA as output
                        GPIO_O_SET(54,0);
                        GPIO_O_SET(56,1);
                    key_state=0;
                    }
                    }
                   }
                   if((GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   {
                         key_state_flag3=0;
                   }
                   break;
                  default:break;
       }
}

#elif defined(HJ2439_SCAN_KEY) 
void check_HJ2439_keylight_status(void)  //caoh 2004-4-19 11:30
{
   static BYTE key_state = 0;  
   static BYTE key_state_flag1=0,key_state_flag2=0,key_state_flag3=0;  
   static BYTE pause_play_counter=0;  
   static BYTE power_key_exist=0; //lijd test   
   switch(key_state)
    {
           case  0:                             
                   GPIO_E_SET(54,0);//set  CLK as input
                   GPIO_E_SET(56,0);//set  DATA as input
 //                  GPIO_O_SET(55,0);
 //                  GPIO_O_SET(57,1);
                   GPIO_O_SET(18,1);
                   GPIO_O_SET(15,0);
                   GPIO_O_SET(14,1);
                   if(!key_state_flag1)
                   {
                   if((!GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   { 
                           power_key_exist=1;//lijd test
                           //call_ir_func(IRC_POWER);
                           //key_state_flag1=1;
                   }
                   else if((GPIO_I_GET(56))&&(!GPIO_I_GET(54)))
                   {                            
                            call_ir_func(IRC_FORWARD);
                            key_state_flag1=1;                           
                   } 
                   else
                   {                                                           
                         if(power_key_exist==1)//lijd test
                         {
                           call_ir_func(IRC_POWER);
                           power_key_exist=0;
                         }                                                
                        GPIO_E_SET(54,1);//set  CLK as output
                        GPIO_E_SET(56,1);//set  DATA as output
                        GPIO_O_SET(54,0);
                        GPIO_O_SET(56,1);
                        key_state = 1;                          
                    }
                   }                   
                  if((GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   {
                         key_state_flag1=0;
                   }  
                   break;
           case  1:
                                      
                   GPIO_E_SET(54,0);//set  CLK as input
                   GPIO_E_SET(56,0);//set  DATA as input
                   GPIO_O_SET(18,0);

//                   GPIO_O_SET(55,1);
//                   GPIO_O_SET(57,1);
                   GPIO_O_SET(15,1);
                   GPIO_O_SET(14,1);

                   if(!key_state_flag2)
                   {
                   if((!GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   { 
                           call_ir_func(IRC_STOP);
                           key_state_flag2=1;
                   }
                   else if((GPIO_I_GET(56))&&(!GPIO_I_GET(54)))
                   {                            
                            call_ir_func(IRC_BACKWARD);
                            key_state_flag2=1;                                    
                   } 
                   else
                   {                                                                                      
                        GPIO_E_SET(54,1);//set  CLK as output
                        GPIO_E_SET(56,1);//set  DATA as output
                        GPIO_O_SET(54,0);
                        GPIO_O_SET(56,1);                        
                        key_state = 2;
                     }
                    }   
                     
                   if((GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   {
                         key_state_flag2=0;
                   }    
                   break;
           case  2:
                   GPIO_E_SET(54,0);//set  CLK as input
                   GPIO_E_SET(56,0);//set  DATA as input
                   GPIO_O_SET(18,1);
//                   GPIO_O_SET(55,1);
//                   GPIO_O_SET(57,0);
                   GPIO_O_SET(15,1);
                   GPIO_O_SET(14,0);
                    if(!key_state_flag3)
                   {
                   if((!GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   { 
                           pause_play_counter++;
                           if(pause_play_counter>5)
                    {
                           pause_play_counter=0;                             
                           call_ir_func(IRC_PAUSEPLAY);
                           save_srn_start_t = get_rtc_val();
                           key_state_flag3=1;
                    }       
                   }
                   else if((GPIO_I_GET(56))&&(!GPIO_I_GET(54)))
                   {
                           call_ir_func(IRC_EJECT);
                           save_srn_start_t = get_rtc_val();
                           key_state_flag3=1;                           
                   } 
                   else
                   {                                               
                        GPIO_E_SET(54,1);//set  CLK as output
                        GPIO_E_SET(56,1);//set  DATA as output
                        GPIO_O_SET(54,0);
                        GPIO_O_SET(56,1);
                        key_state=0; 
                    }                   
                   }
                   if((GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   {
                         key_state_flag3=0;
                   }  
                   break; 
                  default:break;
       }    
 }    

#elif defined(DP30H0_KEY_SCAN)  //wsf  040730
#define  SCAN_KEY1 	93	//226 //INPUT
#define  SCAN_KEY2 	94  //227 

#define  SCAN_KEY3 	97	//230  //OUTPUT
#define  SCAN_KEY4 	98	//231
#define  SCAN_KEY6 	100	//233

//int key_state = 0;  
static unsigned char temp_count=0;
static unsigned char temp_play_led=0;
unsigned char led_flash_flag=0;
BYTE 	pre_key=IRC_NULL;
BYTE      repeat_play_pause_key=0;
BYTE	current_key=IRC_NULL;
BYTE      repeat_open_close_key=0;
BYTE      repeat_ir_key_mod=0;
BYTE      repeat_next_key_mod=0;
BYTE      repeat_stop_key_mod=0;

static int key_state = 0;  
void check_dp30h0_panel_key_status(void)  //caoh 2004-4-19 11:30
{
 	 
	
#if  1
    	temp_play_led++;
    	if(temp_play_led>=70) 
    	{
		temp_play_led=0;
	//	if(play_state==VCD_STATE_NORMAL)
		if(play_state!=VCD_STATE_POWER)
		{
		//	if(led_flash_flag)
		//	{
			//	led_flash_flag=0	;
				GPIO_O_SET(PANEL_LED_PLAY,0);			         
		//	}
		//	else
		//	{
		//		led_flash_flag=1;
		//		GPIO_O_SET(PANEL_LED_PLAY,0);
		
		//	}
			//GPIO_O_SET(TOP_LOADER_GPIO,1);
		}
		else
		{
			//GPIO_O_SET(TOP_LOADER_GPIO,0);
			GPIO_O_SET(PANEL_LED_PLAY,1);			
		}
    	}
    	
	temp_count++;
	if(temp_count>=9)
		temp_count=0;
	else
		return;
       regs0->sft_cfg1 &= ~(0x1 << 4);
       #define GPIO_SCART_RELEASE_SW               93 
       GPIO_E_SET(93,0);   //key1
       GPIO_M_SET(SCAN_KEY3,1);    	//KEY1
       GPIO_M_SET(SCAN_KEY4,1);          //key4
       GPIO_M_SET(SCAN_KEY6,1);         //key6    
       GPIO_E_SET(SCAN_KEY3,1);       	//KEY3
       GPIO_E_SET(SCAN_KEY4,1);           //KEY4
       GPIO_E_SET(SCAN_KEY6,1);		//KEY6
   switch(key_state)
    {
           case  0:      	
                    GPIO_O_SET(SCAN_KEY3,1);      //key3 
                    GPIO_O_SET(SCAN_KEY4,0);    	//KEY4    	          
    	            GPIO_O_SET(SCAN_KEY6,0);	//KEY6
                if(GPIO_I_GET(SCAN_KEY1)==0 &&repeat_open_close_key)
                    repeat_open_close_key=0;
                           
                   if((!GPIO_I_GET(SCAN_KEY1))&&(GPIO_I_GET(SCAN_KEY2)))
                   {                         
                            current_key=IRC_POWER;
                    }
                   else
                    if((GPIO_I_GET(SCAN_KEY1))&&(!GPIO_I_GET(SCAN_KEY2)))
                   {
                       if( repeat_open_close_key)
                        ;
                       else
                        {
                        call_ir_func(IRC_EJECT);
                        repeat_open_close_key=1;
                        }
                   }                   
                    key_state=1;                                             
                  // break;
           case  1:           	
                   GPIO_O_SET(SCAN_KEY3,0);    	//KEY3
    	             GPIO_O_SET(SCAN_KEY4,1);      //key4
    	             GPIO_O_SET(SCAN_KEY6,0);		//KEY6
    	             
                    if(GPIO_I_GET(SCAN_KEY2)==0&& repeat_play_pause_key)
                        repeat_play_pause_key=0;
                    if(GPIO_I_GET(SCAN_KEY1)==0&& repeat_ir_key_mod)
                             repeat_ir_key_mod=0;

                    if((!GPIO_I_GET(SCAN_KEY1))&&(GPIO_I_GET(SCAN_KEY2)))
                    { 
                        if(repeat_play_pause_key)
                            ;                        
                        else
                        {                         
                          //call_ir_func(IRC_PAUSEPLAY);
                           //liumzh 2004-8-19 1:18 due to KODAK CD pause panel key not stop slide
                             if(Is_JPEG_SlideMode())
				{
					if(bJpgVFDPause == 0)
					{
						if(play_state == VCD_STATE_PAUSE)	//nono 2-6-28 14:00
						{
							bJpgVFDPause = 2;
							PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);
							return;
						}
						else
						{
#ifdef ZOOM_DIRECT_STOP_SLIDE//nono 4-9-4 
                if(jpg_slide_time == 0xffffffff)
                {
    
                 if(Is_JPEG_SlideMode())
                    {
                        jpg_slide_time = JPEG_SLIDE_TIME;//NONO 4-8-31 17:17
                         //ForceStopJpgSlide();
                        ircmd_post_func(CMD_FUNC|CMD_FUNC_PLAY);
                    }
                    
                }else
#endif           
							
							bJpgVFDPause = 1;
						}
					}
					else if(bJpgVFDPause == 1)
					{
						bJpgVFDPause = 2;
						PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);
					}
				}
				else
				 {
				    //call_ir_func(IRC_PAUSEPLAY);
                           current_key=IRC_PAUSEPLAY;                       
                           	}                      
                           repeat_play_pause_key=1;
                           	
                        }                 
                   }
                    else
                      if((GPIO_I_GET(SCAN_KEY1))&&(!GPIO_I_GET(SCAN_KEY2)))
                   {
                      if (repeat_ir_key_mod)
                            ;                        
                      else
                        {
                   	         //call_ir_func(IRC_PREV);
                   	        bIrSkipState = 1;
                           current_key=IRC_PREV; 
				  repeat_ir_key_mod=1;
                        }
                   }                   
                   
                   key_state=2; 
                  // break;
           case  2:
                   GPIO_O_SET(SCAN_KEY3,0);    	//KEY3
    	             GPIO_O_SET(SCAN_KEY4,0);     //key 4
    	             GPIO_O_SET(SCAN_KEY6,1);	//KEY6                   
                   if (GPIO_I_GET(SCAN_KEY2)==0&&repeat_stop_key_mod)
                       repeat_stop_key_mod=0;
                   if (GPIO_I_GET(SCAN_KEY1)==0&&repeat_next_key_mod)
                          repeat_next_key_mod=0;

                     if((!GPIO_I_GET(SCAN_KEY1))&&(GPIO_I_GET(SCAN_KEY2)))
                    { 
                        if (repeat_stop_key_mod)
                            ;
                        else
                            {
                          //call_ir_func(IRC_STOP);
                            current_key=IRC_STOP;	
                          repeat_stop_key_mod=1;
                            }
                    }
                   else
                     if((GPIO_I_GET(SCAN_KEY1))&&(!GPIO_I_GET(SCAN_KEY2)))
                   {
                         if(repeat_next_key_mod)
                             ;                            
                         else
                            {
				//call_ir_func(IRC_NEXT);
				  bIrSkipState = 2;
                           current_key=IRC_NEXT;  
				 repeat_next_key_mod=1;
                            }
                   }                
                  
                    key_state=0; 
                   break; 
                 
       }     
   	//regs0->fm_gpio_mode = 8;                    // Set FM GPIO TABLE to ALL IN ONE case
    	//regs0->fm_gpio_len  = 12                    // Set FMGPIO_B[41:0] turn on
       //                |  (0xf << 4);          // Set FMGPIO_B[41:0] enable   
	if(pre_key==current_key &&  pre_key!=IRC_NULL)
	{
		call_ir_func(current_key);
		pre_key=current_key=IRC_NULL;
	}
	else
	{
		pre_key=current_key;
	}
   #endif
}   
#elif defined(DP3240_KEY_SCAN)   //add xrh 
#define KEY_GPIO_21 21  //pin 72
#define KEY_GPIO_22 22  //pin 73
#define KEY_GPIO_23 23  //pin 74
static unsigned char play_led=0;
/*
const BYTE key_call_ir_table[10]={
    IRC_NULL,   //0
    IRC_POWER,  //1
    IRC_EJECT,  //2
    IRC_STOP,   //3
    IRC_PREV,   //4
    IRC_NEXT,   //5
    IRC_PAUSEPLAY,  //6
    IRC_FORWARD,    //7
    IRC_BACKWARD,   //8
    IRC_REPEAT,     //9
}; */
const BYTE key_call_ir_table[10]={
    IRC_NULL,  
    IRC_NULL,
    IRC_NULL, 
    IRC_NULL,
    IRC_POWER,   //4
    IRC_NULL,   
    IRC_EJECT, 
#ifdef EASTECH_DVD_DP3240_D
    IRC_PAUSEPLAY,
#else
    IRC_PLAY_SELECT,
#endif
    IRC_NULL,
    IRC_STOP,
};

BYTE check_other_key_state(BYTE output_IO_number,BYTE test_IO_number1,BYTE test_IO_number2,BYTE return_key_num_base,BYTE* more_than_one_key_press)
{
    BYTE key_value=0;    
    GPIO_E_SET(output_IO_number,1);    GPIO_E_SET(test_IO_number1,1);    GPIO_E_SET(test_IO_number2,1); 
    GPIO_O_SET(output_IO_number,0);    GPIO_O_SET(test_IO_number1,0);    GPIO_O_SET(test_IO_number2,0);  
    GPIO_E_SET(output_IO_number,0);    GPIO_E_SET(test_IO_number1,0);    GPIO_E_SET(test_IO_number2,0); 
    
    GPIO_E_SET(output_IO_number,1);  
    GPIO_O_SET(output_IO_number,0); 
    GPIO_O_SET(output_IO_number,0); //delay    
    if(!GPIO_I_GET(test_IO_number1))key_value = return_key_num_base + 1;         
    if(!GPIO_I_GET(test_IO_number2))key_value = return_key_num_base + 2;     
    if((GPIO_I_GET(test_IO_number1)+GPIO_I_GET(test_IO_number2)) < 1)
    {   // too many keys press if this value more than (I/O_total_number - 2 )
        key_value=0;
        (*more_than_one_key_press)+=2;//tell us too many keys press now
    }    
    GPIO_E_SET(output_IO_number,0); 
    if(key_value) (*more_than_one_key_press)++;  
    return key_value;
}
 
void polling_vfd_key_3IO(void)
{      
    
    BYTE key_value=0,key_value_copy=0,more_than_one_key_press=0;
    static BYTE key_value_save,key_press_before,valid_key,key_press;   
	play_led++;
    	if(play_led>=20) 
    	{
		play_led=0;	
		if(play_state!=VCD_STATE_POWER)
		{
		GPIO_O_SET(POWER_LED_2,1);	
#ifndef EASTECH_DVD_DP3240_D	
		GPIO_O_SET(PLAY_LED_1,0);
#endif
		}
		else
		{		
		GPIO_O_SET(POWER_LED_2,0);
#ifndef EASTECH_DVD_DP3240_D	
		GPIO_O_SET(PLAY_LED_1,1);			
#endif			
		}
    	}
   
#ifdef LED_FLASH_WHEN_PAUSE
    //liumzh for play LED flash when pause
	static BYTE temp_play_led=0,led_flash_flag=0;
	if(play_state==VCD_STATE_NORMAL ||play_state==VCD_STATE_FASTBACKWARD ||
	play_state==VCD_STATE_FASTFORWARD || play_state==VCD_STATE_SLOW
	||play_state==VCD_STATE_CLOSE)      
	{
		GPIO_O_SET(PLAY_LED_1,0);	
	}	
	else
	{
    		temp_play_led++;
    		if(temp_play_led>=120) 
    		{
			temp_play_led=0;
			if(play_state==VCD_STATE_PAUSE)
			{
				if(led_flash_flag)
				{
					led_flash_flag=0	;
		GPIO_O_SET(PLAY_LED_1,1);			
		}
				else
				{
					led_flash_flag=1;
					GPIO_O_SET(PLAY_LED_1,0);
				}
			}	
			else
			{
		GPIO_O_SET(PLAY_LED_1,1);			
		}
    	}
    	}
#endif //LED_FLASH_WHEN_PAUSE
   
    switch((GPIO_I_GET(KEY_GPIO_21)+GPIO_I_GET(KEY_GPIO_22)+GPIO_I_GET(KEY_GPIO_23)))
    {
        case 0:        
        case 1: // too many keys press if this value less than (I/O_total_number - 1 )  
                break;
        case 2: // just one advance key press,don't check other keys                
                if(!GPIO_I_GET(KEY_GPIO_21))key_value=1; //power        
                if(!GPIO_I_GET(KEY_GPIO_22))key_value=2; //eject       
                if(!GPIO_I_GET(KEY_GPIO_23))key_value=3; //stop                 
                break;                
        case 3: // no advance key press,check other keys                                         
                key_value_copy = check_other_key_state(KEY_GPIO_23,KEY_GPIO_21,KEY_GPIO_22,3,&more_than_one_key_press);
                if(key_value_copy)key_value = key_value_copy;                            
                key_value_copy = check_other_key_state(KEY_GPIO_22,KEY_GPIO_21,KEY_GPIO_23,5,&more_than_one_key_press);
                if(key_value_copy)key_value = key_value_copy;                 
                key_value_copy = check_other_key_state(KEY_GPIO_21,KEY_GPIO_22,KEY_GPIO_23,7,&more_than_one_key_press);
                if(key_value_copy)key_value = key_value_copy;                 
                if(more_than_one_key_press > (3-2))    key_value=0;    
                break;              
        default:                
                break;
    }  
        
    if(key_value){
        if(key_press_before){
            if(key_press && (key_value_save == key_value) ){                
                    call_ir_func(key_call_ir_table[key_value_save]);
                    key_press=0;
                    key_value=0;
                    key_value_save=0;                    
            }            
        }else{
            key_value_save=key_value;
            key_press_before=1;
            key_press=1;
        }        
    }else{        
            valid_key=0;
            key_press_before=0;
            key_value_save=0;  
            key_press=0;   
    }    
}
// mimitsai merge from dp2070/dp3240
#elif defined(DP2070_KEY_SCAN)   //add xrh 
#define KEY_GPIO_21 21  //pin 72
#define KEY_GPIO_22 22  //pin 73
#define KEY_GPIO_23 23  //pin 74
#define KEY_GPIO_70 70  //pin 45
static unsigned char play_led=0;
/*
const BYTE key_call_ir_table[10]={
    IRC_NULL,   //0
    IRC_POWER,  //1
    IRC_EJECT,  //2
    IRC_STOP,   //3
    IRC_PREV,   //4
    IRC_NEXT,   //5
    IRC_PAUSEPLAY,  //6
    IRC_FORWARD,    //7
    IRC_BACKWARD,   //8
    IRC_REPEAT,     //9
}; */
const BYTE key_call_ir_table[10]={
    IRC_NULL,   //0
    IRC_PREV, ///1
    IRC_NEXT,   ////2
    IRC_POWER,    //  //3
    IRC_STOP, //  //4
    IRC_PAUSEPLAY,//IRC_PLAY,  // //5
    IRC_NULL,  //6
    IRC_NULL,    //7
    IRC_NULL,   //8
    IRC_NULL,     //9
};

#include "uart.h"

// V3.2 ylseng
UINT8 g_uiFirstTime = TRUE;
UINT8 g_uiPowerActive = TRUE;

BYTE scan_DP2070_key(void)
{
    GPIO_E_SET(KEY_GPIO_22,0) ; 
    GPIO_E_SET(KEY_GPIO_23,0) ;  
    
    GPIO_E_SET(KEY_GPIO_21,1) ; 
    GPIO_O_SET(KEY_GPIO_21,0) ; 
    
    delay_1us(1);
    if(GPIO_I_GET(KEY_GPIO_22)==0)
    {
        //printf("PREV\n");
        return 1;
    }  
    
    if(GPIO_I_GET(KEY_GPIO_23)==0)
    {
        //printf("NEXT\n");
        return 2;
    }  
    
    GPIO_E_SET(KEY_GPIO_21,0) ; 
    GPIO_E_SET(KEY_GPIO_23,0) ; 
    
    GPIO_E_SET(KEY_GPIO_22,1) ; 
    GPIO_O_SET(KEY_GPIO_22,0) ; 
    
    delay_1us(1);
    //if(GPIO_I_GET(KEY_GPIO_21)==0)
    //  printf("Power+Play\n");
    
    if(GPIO_I_GET(KEY_GPIO_23)==0)
    {
        //printf("POWER\n");
        //psprintf(linebuf,"P ");
        //UART0_puts(linebuf);
        
        if( g_uiPowerActive )
        {
            //psprintf(linebuf,"A ");
            //UART0_puts(linebuf);
            
            if( g_uiFirstTime )
            {
                //psprintf(linebuf,"FFF ");    
                //UART0_puts(linebuf);
                
                g_uiFirstTime = FALSE;
                g_uiPowerActive = FALSE;
            }
            else
        return 3;
    }  
    
        return 0;
    }
    else
    {
        //psprintf(linebuf,"R ");
        //UART0_puts(linebuf);
        g_uiFirstTime   = FALSE;
        g_uiPowerActive = TRUE;
    }
    
    GPIO_E_SET(KEY_GPIO_21,0) ; 
    GPIO_E_SET(KEY_GPIO_22,0) ; 
    
    GPIO_E_SET(KEY_GPIO_23,1) ; 
    GPIO_O_SET(KEY_GPIO_23,0) ; 
    
    delay_1us(1);
    if(GPIO_I_GET(KEY_GPIO_22)==0)
    {
        //printf("STOP\n");
        return 4;
    }  
    
    if(GPIO_I_GET(KEY_GPIO_21)==0)
    {
        //printf("PLAY\n");
        return 5;
    }  
/*
    GPIO_E_SET(KEY_GPIO_70,0);
    static UINT8 key_tray = 1;
    UINT8 key_current = GPIO_I_GET(KEY_GPIO_70);
    
    if( key_tray != key_current )
    {
        ircmd_eject_toggle();
        
        psprintf(RegionValStr[REGION1], "%d %d", key_tray, key_current );
        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);    
        
        key_tray = key_current;
    }
*/
    return 0;  
}    

void polling_DP2070_key(void)
{
    //BYTE key_value=0;
    static int time_100ms_pressed_count=0,key_value_save=0, led_time_count=0,key_value=0;
  
    time_100ms_pressed_count++;
    led_time_count++;
  
    if(time_100ms_pressed_count>1)
        time_100ms_pressed_count=0;
    else
        key_value=scan_DP2070_key() ;
  
    if(led_time_count>10)
    {
        led_time_count=0;
        //if((play_state==VCD_STATE_STOP)||(play_state==VCD_STATE_OPEN)||(play_state==VCD_STATE_IDLE))
            //GPIO_O_SET(PLAY_LED_1, 0);
        //else
        if( system_state == SYSTEM_BROWSE )
            GPIO_O_SET(PLAY_LED_1, 1);
        else
            GPIO_O_SET(PLAY_LED_1, 0);
    } 
  
    //printf("key_value=%d, key_value_save=%d,t=%d\n",key_value,key_value_save,time_100ms_pressed_count);

    if(key_value!=key_value_save)
    {
        time_100ms_pressed_count=0;
        key_value_save=key_value;
        if(key_value_save!=0)
        {
            if(key_value_save==3) //power
            {
                GPIO_O_SET(PLAY_LED_1, 0);
                GPIO_O_SET(POWERON_LED_0, 1);    
            }        
            else if(key_value_save==4) //stop
               GPIO_O_SET(PLAY_LED_1, 0);
            //else if(key_value_save==5) //play
               //GPIO_O_SET(PLAY_LED_1, 1);
    
            call_ir_func(key_call_ir_table[key_value_save]);
        }
    // printf("key_value=%d, key_value_save=%d,t=%d\n",key_value,key_value_save,time_100ms_pressed_count);
    }
}

BYTE check_other_key_state(BYTE output_IO_number,BYTE test_IO_number1,BYTE test_IO_number2,BYTE return_key_num_base,BYTE* more_than_one_key_press)
{
    BYTE key_value=0;    
    GPIO_E_SET(output_IO_number,1);    GPIO_E_SET(test_IO_number1,1);    GPIO_E_SET(test_IO_number2,1); 
    GPIO_O_SET(output_IO_number,0);    GPIO_O_SET(test_IO_number1,0);    GPIO_O_SET(test_IO_number2,0);  
    GPIO_E_SET(output_IO_number,0);    GPIO_E_SET(test_IO_number1,0);    GPIO_E_SET(test_IO_number2,0); 
    
    GPIO_E_SET(output_IO_number,1);  
    GPIO_O_SET(output_IO_number,0); 
    GPIO_O_SET(output_IO_number,0); //delay    
    if(!GPIO_I_GET(test_IO_number1))key_value = return_key_num_base + 1;         
    if(!GPIO_I_GET(test_IO_number2))key_value = return_key_num_base + 2;     
    if((GPIO_I_GET(test_IO_number1)+GPIO_I_GET(test_IO_number2)) < 1)
    {   // too many keys press if this value more than (I/O_total_number - 2 )
        key_value=0;
        (*more_than_one_key_press)+=2;//tell us too many keys press now
    }    
    GPIO_E_SET(output_IO_number,0); 
    if(key_value) (*more_than_one_key_press)++;  
    return key_value;
}
 
void polling_vfd_key_3IO(void)
{      
    
    BYTE key_value=0,key_value_copy=0,more_than_one_key_press=0,i;
    static BYTE key_value_save,key_press_before,valid_key,key_press;   
	play_led++;
    	if(play_led>=20) 
    	{
		play_led=0;	
		if(play_state!=VCD_STATE_POWER)
		{
		GPIO_O_SET(POWER_LED_2,1);	
              GPIO_O_SET(POWERON_LED_0,0);	
		GPIO_O_SET(PLAY_LED_1,0);
		}
		else
		{		
		GPIO_O_SET(POWER_LED_2,0);
              GPIO_O_SET(POWERON_LED_0,1);	
		GPIO_O_SET(PLAY_LED_1,1);			
		}
    	}
   
    switch((GPIO_I_GET(KEY_GPIO_21)+GPIO_I_GET(KEY_GPIO_22)+GPIO_I_GET(KEY_GPIO_23)))
    {
        case 0:        
        case 1: // too many keys press if this value less than (I/O_total_number - 1 )  
                break;
        case 2: // just one advan6ce key press,don't check other keys                
                if(!GPIO_I_GET(KEY_GPIO_21))key_value=1; //power        
                if(!GPIO_I_GET(KEY_GPIO_22))key_value=2; //eject       
                if(!GPIO_I_GET(KEY_GPIO_23))key_value=3; //stop                 
                break;                
        case 3: // no advance key press,check other keys                                         
                key_value_copy = check_other_key_state(KEY_GPIO_23,KEY_GPIO_21,KEY_GPIO_22,3,&more_than_one_key_press);
                if(key_value_copy)key_value = key_value_copy;                            
                key_value_copy = check_other_key_state(KEY_GPIO_22,KEY_GPIO_21,KEY_GPIO_23,5,&more_than_one_key_press);
                if(key_value_copy)key_value = key_value_copy;                 
                key_value_copy = check_other_key_state(KEY_GPIO_21,KEY_GPIO_22,KEY_GPIO_23,7,&more_than_one_key_press);
                if(key_value_copy)key_value = key_value_copy;                 
                if(more_than_one_key_press > (3-2))    key_value=0;    
                break;              
        default:                
                break;
    }  
        
    if(key_value){
        if(key_press_before){
            if(key_press && (key_value_save == key_value) ){                
                    call_ir_func(key_call_ir_table[key_value_save]);
                    key_press=0;
                    key_value=0;
                    key_value_save=0;                    
            }            
        }else{
            key_value_save=key_value;
            key_press_before=1;
            key_press=1;
        }        
    }else{        
            valid_key=0;
            key_press_before=0;
            key_value_save=0;  
            key_press=0;   
    }    
}  //DP2070_SCAN_KEY

#elif defined(DP2030_SCAN_KEY)//eastech2030

#define  SCAN_KEY3 	94  	//Pin22	Input
#define  SCAN_KEY4 	97	//Pin230
#define  SCAN_KEY6 	100	//Pin233

#define  SCAN_KEY5 	98   // pin231   Output
#define  SCAN_KEY2 	93	//Pin226
#define  SCAN_KEY1 	23	//Pin84

//int key_state = 0;  
static unsigned char temp_count=0;
static unsigned char temp_play_led=0;
unsigned char led_flash_flag=0;
BYTE 	pre_key=IRC_NULL;
BYTE	current_key=IRC_NULL;
BYTE 	key_flag0=0;
BYTE	key_flag1=0;
BYTE 	key_flag2=0;
BYTE	exe_key_cnt=0;
BYTE 	power_key_cnt=0;
BYTE	back_current_key=IRC_NULL;
static int key_state = 0;  
void check_panel_key_status(void)  //caoh 2004-4-19 11:30
{
	
	if(play_state==VCD_STATE_NORMAL ||play_state==VCD_STATE_FASTBACKWARD ||
	play_state==VCD_STATE_FASTFORWARD || play_state==VCD_STATE_SLOW
	||play_state==VCD_STATE_CLOSE)      //LEE 2004/8/10 03:36PM
	{
		GPIO_O_SET(PANEL_LED_PLAY,0);	
	}	
	else
	{
    		temp_play_led++;
    		if(temp_play_led>=60) 
    		{
			temp_play_led=0;
			if(play_state==VCD_STATE_PAUSE)
			{
				if(led_flash_flag)
				{
					led_flash_flag=0	;
					GPIO_O_SET(PANEL_LED_PLAY,1);	
				}
				else
				{
					led_flash_flag=1;
					GPIO_O_SET(PANEL_LED_PLAY,0);
				}
			}	
			else
			{
				GPIO_O_SET(PANEL_LED_PLAY,1);
			}
		}
    	}

	temp_count++;
	if(temp_count>=11)
		temp_count=0;
	else
		return;        
	SFT_CFG_GPIO93();
	SFT_CFG_GPIO94();   
	GPIO_M_SET(SCAN_KEY1,1);    	//KEY1
    	GPIO_M_SET(SCAN_KEY2,1);
   	GPIO_M_SET(SCAN_KEY5,1);		//KEY5
    
    	GPIO_E_SET(SCAN_KEY1,1);    	//KEY1   Output
    	GPIO_E_SET(SCAN_KEY2,1);
    	GPIO_E_SET(SCAN_KEY5,1);		//KEY5
   switch(key_state)
    {
           case  0:           	
                   GPIO_E_SET(SCAN_KEY3,1);
                   GPIO_O_SET(SCAN_KEY3,0);

                   GPIO_O_SET(SCAN_KEY5,1);
                   GPIO_O_SET(SCAN_KEY2,0);
                   GPIO_O_SET(SCAN_KEY1,0);
			
                   GPIO_E_SET(SCAN_KEY3,0);                
	           if(!key_flag0)
	           {			
                   if((!GPIO_I_GET(SCAN_KEY6))&&(!GPIO_I_GET(SCAN_KEY3))&&(GPIO_I_GET(SCAN_KEY4)))
                   { 
                           //call_ir_func(IRC_PLAY_RESUME);
                           		current_key=IRC_PLAY_RESUME;
                           key_flag0 = 1;                           	
                           
                   }
                   else if((!GPIO_I_GET(SCAN_KEY6))&&(GPIO_I_GET(SCAN_KEY3))&&(!GPIO_I_GET(SCAN_KEY4)))
                   {
                           //call_ir_func(IRC_NEXT);
                           		current_key=IRC_NEXT;
                           		bIrSkipState = 2;//liumzh
                           key_flag0 = 1;                        	
                   } 
                   else	if((GPIO_I_GET(SCAN_KEY6))&&(!GPIO_I_GET(SCAN_KEY3))&&(!GPIO_I_GET(SCAN_KEY4)))
                   {
                   		//call_ir_func(IRC_VOLUME_UP);
                   		current_key=IRC_VOLUME_UP;
                   }
                   }
                   if((!GPIO_I_GET(SCAN_KEY6))&&(!GPIO_I_GET(SCAN_KEY3))&&(!GPIO_I_GET(SCAN_KEY4)))
                    {
                    	       key_flag0 = 0;
                    key_state=1;                                             
                    }                                             
                  break;
           case  1:           	
                   GPIO_E_SET(SCAN_KEY3,1);
                   GPIO_O_SET(SCAN_KEY3,0);

                   GPIO_O_SET(SCAN_KEY5,0);
                   GPIO_O_SET(SCAN_KEY2,1);
                   GPIO_O_SET(SCAN_KEY1,0);

                   GPIO_E_SET(SCAN_KEY3,0);        
	           if(!key_flag1)
	           {	
                   if((!GPIO_I_GET(SCAN_KEY6))&&(GPIO_I_GET(SCAN_KEY3))&&(!GPIO_I_GET(SCAN_KEY4)))
                   {
                           //call_ir_func(IRC_PREV);
                           		current_key=IRC_PREV;
                           key_flag1 = 1;
                           		bIrSkipState = 1;//liumzh 2004-8-24 15:44
                   } 
                   else	if((GPIO_I_GET(SCAN_KEY6))&&(!GPIO_I_GET(SCAN_KEY3))&&(!GPIO_I_GET(SCAN_KEY4)))
                   {
                   		//call_ir_func(IRC_VOLUME_DN);
                   		current_key=IRC_VOLUME_DN;
                   }
                           	}
                   if((!GPIO_I_GET(SCAN_KEY6))&&(!GPIO_I_GET(SCAN_KEY3))&&(!GPIO_I_GET(SCAN_KEY4)))
                   {                            
                    	       key_flag1 = 0;
                   key_state=2; 
                           	}
                    break;
           case  2:
                   GPIO_E_SET(SCAN_KEY3,1);
                   GPIO_O_SET(SCAN_KEY3,0);
                   
                   GPIO_O_SET(SCAN_KEY5,0);
                   GPIO_O_SET(SCAN_KEY2,0);
                   GPIO_O_SET(SCAN_KEY1,1);
                   
                   GPIO_E_SET(SCAN_KEY3,0); 
                   if(!key_flag2)
	           {	                   
                   if((!GPIO_I_GET(SCAN_KEY6))&&(!GPIO_I_GET(SCAN_KEY3))&&(GPIO_I_GET(SCAN_KEY4)))
                   { 
                           //call_ir_func(IRC_STOP);
                           		current_key=IRC_STOP;
                           key_flag2 = 1;
                           	}
                   else if((!GPIO_I_GET(SCAN_KEY6))&&(GPIO_I_GET(SCAN_KEY3))&&(!GPIO_I_GET(SCAN_KEY4)))
                   {
                           //call_ir_func(IRC_REPEAT);
                           		current_key=IRC_REPEAT;
                          key_flag2 = 1;
                   } 
                   else	if((GPIO_I_GET(SCAN_KEY6))&&(!GPIO_I_GET(SCAN_KEY3))&&(!GPIO_I_GET(SCAN_KEY4)))
                   {
                   		//call_ir_func(IRC_POWER);
                   		current_key=IRC_POWER;
                   		key_flag2 = 1;
                   }
                   }
                  if((!GPIO_I_GET(SCAN_KEY6))&&(!GPIO_I_GET(SCAN_KEY3))&&(!GPIO_I_GET(SCAN_KEY4)))
                    {
                    	       key_flag2 = 0;
                    key_state=0; 
                    }       
                   break; 
       }     
	if(pre_key==current_key &&  pre_key!=IRC_NULL)
	{	
		 //printf("  test   key\n");
		call_ir_func(current_key);
		pre_key=current_key=IRC_NULL;
	}
	else
	{
		pre_key=current_key;
	}
}   

#elif defined(NINTAUS_612_SCAN_KEY)         //linrc 2004-6-8 9:23
BYTE key_press_hold=0x00;
void vfdIO_scan_6key(void)
{   
    static BYTE Led_Counter = 0;
    BYTE key_scan_temp=0x03;

    if(play_state==VCD_STATE_CLOSE)
    {
        if(Led_Counter<5)
        {
            GPIO_O_SET(3,1);
            GPIO_O_SET(4,0);    
        }
        if(Led_Counter>5)
        {
            GPIO_O_SET(4,1);
            GPIO_O_SET(3,0);          
        }
        if(Led_Counter==10) Led_Counter = 0;    
        Led_Counter++;
    }
    else
    {
        GPIO_O_SET(4,0);
        GPIO_O_SET(3,0);
        if(cd_type_loaded == CDDA || cd_type_loaded == CDVCD10 || cd_type_loaded == CDVCD20 || cd_type_loaded == CDSVCD) 
            GPIO_O_SET(4,1);
        if(cd_type_loaded == CDROM || cd_type_loaded == CDDVD) 
            GPIO_O_SET(3,1);                  
    }    
      
    GPIO_O_SET(56,1);//output high level.
    
    if (!GPIO_I_GET(54))
       key_scan_temp&=0x02;
       
    if (!GPIO_I_GET(55))
       key_scan_temp&=0x01;
       
    if (key_scan_temp!=0x03&&key_press_hold==0)
    {   
        key_press_hold=1;
        switch  (key_scan_temp)
        {
           case 0  :  call_ir_func(IRC_PLAY_RESUME); break;
           case 1  :  call_ir_func(IRC_EJECT); break;
           case 2  :  call_ir_func(IRC_POWER); break;
           default :  break;
        }
    }

    if (key_scan_temp==0x03) //(key_scan_temp==0x03)
    {
        key_scan_temp=0x03;   
        GPIO_O_SET(56,0);//output low level. 
        
        if (!GPIO_I_GET(54))
            key_scan_temp&=0x02;
            
        if (!GPIO_I_GET(55))
            key_scan_temp&=0x01;
            
        if (key_scan_temp!=0x03&&key_press_hold==0)
        { 
            key_press_hold=1;
            switch  (key_scan_temp)
            {
                 case 0  :  call_ir_func(IRC_PREV); break;
                 case 1  :  call_ir_func(IRC_STOP); break;
                 case 2  :  call_ir_func(IRC_NEXT); break;
                 default :  break;
            }
        }
        if (key_scan_temp==0x03)
            key_press_hold=0;        
    }                
}

#endif//#if defined(USE_VFDPORT_TO_KEYLIGHT_GBM)

#if defined(VFD_GPIO_KEY)&&defined(SYBER_DVD)
UINT8 gpio_stb_level=0;
UINT8 gpio_data_level=0;
UINT8 old_gpio_stb_level=1;
UINT8 old_gpio_data_level=1;
void check_syber_key_status(void)
{
   	regs0->gpio_master[55 / 16] |= (0x1 << (55 % 16));  
	regs0->gpio_oe[55/16] &= ~(1<<(55%16));  //input port

	regs0->gpio_master[56/ 16] |= (0x1 << (56 % 16));  
	regs0->gpio_oe[56/16] &= ~(1<<(56%16));  //input port
	
    gpio_data_level = GPIO_I_GET(OPEN_CLOSE_KEY);
    gpio_stb_level = GPIO_I_GET(PLAY_PAUSE_KEY);
   	if(gpio_data_level == 0 && old_gpio_data_level !=0)
   	{
   		call_ir_func(0x0c);  //ircmd_eject_toggle()
          // old_gpio_stb_level = gpio_stb_level;
   	}
  	
   	if(gpio_stb_level == 0 && old_gpio_stb_level !=0)
   	{
   		ircmd_play_pause();
        //   old_gpio_data_level = gpio_data_level;
    }
    old_gpio_stb_level = gpio_stb_level;
    old_gpio_data_level = gpio_data_level;

}

#endif

#ifdef AKI_2CH_KEY_SCAN     //linrc add for AKI 2004-12-31 10:42
BYTE gpio_key,gpio_key_old;
void Check_AKI_2CH_Key(void)
{
    BYTE mm;
    GPIO_M_SET(22,1);
    GPIO_M_SET(23,1);
    GPIO_E_SET(22,0);
    GPIO_E_SET(23,0);

    for(mm=0;mm<20;mm++); 

    if(GPIO_I_GET(22)==0)
    {
       gpio_key=1;
    }
    else if(GPIO_I_GET(23)==0)
    {
       gpio_key=2;
    }
    else
    {
          gpio_key=0;
    }
	
    if(gpio_key_old!=gpio_key)
    {
       if(gpio_key==1)
        {
            call_ir_func(IRC_EJECT);
       }
       else if(gpio_key==2)
        {
            call_ir_func(IRC_PAUSEPLAY);
       }
       gpio_key_old=gpio_key;
    }   
}
#endif

#if defined(USE_GPIO_TO_KEYLIGHT_WINGSUM)
void check_wingsum_keylight_status(void)
{
    #if defined(KEY_DIRECT_LOW_WORK)
    static BYTE 	pre_key = 0;
    static BYTE    cur_key = 0;
    
    cur_key = (GPIO_I_GET(13)<<3)|(GPIO_I_GET(14)<<2)|(GPIO_I_GET(16)<<0);
    
    if(cur_key==0x0d)
    {
        switch(pre_key)
        {
            case 0x0d: break;
            case 0x0c: call_ir_func(IRC_EJECT);     break;
            case 0x09: call_ir_func(IRC_PAUSEPLAY); break;
            case 0x05: call_ir_func(IRC_STOP);      break;
            default:   printf(" wingsum key light error !!!!!!!\n");
                break;
        }
    }
        pre_key = cur_key;
    #endif
    
    #if defined(KEY_SELECT_MAX_SIX)
    
    #endif
}
#endif

#ifdef OP_4110_SCAN_KEY_USE_GPIO//caoh 2005-7-27 22:06
void Check_panel_key_by_gpio(void)
{
	UINT8  key_data,key_data1,key_data2,key_data3;
    static BYTE key_state = 0;
    static BYTE Flag = 0;
    key_data1 = (BYTE)(regs0->gpio_in[CLK / 16] & (0x1 << (CLK % 16)));
    key_data2 = (BYTE)(regs0->gpio_in[STB / 16] & (0x1 << (STB % 16)));
    key_data3 = (BYTE)(regs0->gpio_in[DAT / 16] & (0x1 << (DAT % 16)));   
    key_data =(key_data1|key_data2|key_data3);
    key_data= key_data >> 5;
    if(key_data==0x07) Flag=0;
    if(Flag!=1)
    {
        switch (key_data)
        {
	        case 0x01://SW1
	             call_ir_func(IRC_EJECT);
	             Flag=1;
	             break; 
	        case 0x03://SW3
	        	 call_ir_func(IRC_PLAY_RESUME);
	             Flag=1;
	             break; 
	        case 0x04://SW4
	             call_ir_func(IRC_STOP);
	             Flag=1;
	             break; 
	        case 0x05://PAUSE
	        	 call_ir_func(IRC_PAUSE);
	             Flag=1;
	             break;  	               
	    }
    }   
}
#elif defined(OP_5116_SCAN_KEY_USE_GPIO)//caoh 2005-7-27 22:06
void Check_panel_key_by_gpio(void)
{
	UINT8  key_data,key_data1,key_data2,key_data3;
    static BYTE key_state = 0;
    static BYTE Flag = 0;
    key_data1 = (BYTE)(regs0->gpio_in[CLK / 16] & (0x1 << (CLK % 16)));
    key_data2 = (BYTE)(regs0->gpio_in[STB / 16] & (0x1 << (STB % 16)));
    key_data3 = (BYTE)(regs0->gpio_in[DAT / 16] & (0x1 << (DAT % 16)));   
    key_data =(key_data1|key_data2|key_data3);
    key_data= key_data >> 5;
    if(key_data==0x07) Flag=0;
    if(Flag!=1)
    {
        switch (key_data)
        {
	        case 0x06://SW1
	             call_ir_func(IRC_EJECT);
	             Flag=1;
	             break; 
	        case 0x03://SW3
	        	 call_ir_func(IRC_PAUSEPLAY);
	             Flag=1;
	             break; 
	        case 0x05://SW4
	             call_ir_func(IRC_STOP);
	             Flag=1;
	             break; 	                      
	    }
    }   
}
#elif defined(OP_5112_SCAN_KEY_USE_GPIO)//lijd 2005-6-13 18:45  
void Check_panel_key_by_gpio(void)
{
	UINT8  key_data,key_data1,key_data2,key_data3;
    static BYTE key_state = 0;
    static BYTE Flag = 0;
    key_data1 = (BYTE)(regs0->gpio_in[CLK / 16] & (0x1 << (CLK % 16)));
    key_data2 = (BYTE)(regs0->gpio_in[STB / 16] & (0x1 << (STB % 16)));
    key_data3 = (BYTE)(regs0->gpio_in[DAT / 16] & (0x1 << (DAT % 16)));   
    key_data =(key_data1|key_data2|key_data3);
    key_data= key_data >> 5;
    if(key_data==0x07) Flag=0;
    if(Flag!=1)
    {
        switch (key_data)
        {
	        case 0x06://SW1
	             call_ir_func(IRC_EJECT);
	             Flag=1;
	             break; 
	        case 0x03://SW3
	        	 call_ir_func(IRC_PAUSEPLAY);
	             Flag=1;
	             break; 
	        case 0x05://SW4
	             call_ir_func(IRC_STOP);
	             Flag=1;
	             break; 	                      
	    }
    }   
}
#endif


void check_gpio_keylight_status(void)
{
#if defined(USE_VFDPORT_TO_KEYLIGHT_GBM)
check_gbm_keylight_status();
#elif defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ)
check_hj_keylight_status();
#elif defined(USE_VFDPORT_TO_KEYLIGHT_MINTON)
check_minton_keylight_status();
#elif defined(USE_VFDPORT_TO_KEYLIGHT_IDALL)
check_idall_keylight_status();
#elif defined(USE_VFDPORT_TO_KEYLIGHT_THAKRAL)
check_thakral_keylight_status();
#elif defined(VFD_GPIO_KEY)
check_syber_key_status();
#elif defined(HANYANG_SCAN_KEY)
check_hanyang_keylight_status();  //caoh 2004-4-19 11:30
//check_hanyang_next_and_prev();
#elif defined(HJ2439_SCAN_KEY) 
check_HJ2439_keylight_status();
#elif defined(NINTAUS_612_SCAN_KEY) //linrc add 2004-6-7 15:25
vfdIO_scan_6key();
#elif defined(DP2030_SCAN_KEY)	
check_panel_key_status();
#elif defined(DP30H0_KEY_SCAN)	
check_dp30h0_panel_key_status();
#elif defined(AKI_2CH_KEY_SCAN)    //linrc add for AKI 2004-12-31 10:42
Check_AKI_2CH_Key();
#elif defined(DP3240_KEY_SCAN)	 //add xrh
polling_vfd_key_3IO();
#elif defined(DP2070_KEY_SCAN)	 //add xrh
polling_DP2070_key();
//polling_vfd_key_3IO();
#elif defined(HANYANG_DP02CD_WF_8202S_16)//added by wangwei,2005-2-4 10:33
check_hanyang_dp02cd_wf_key_status();
#elif defined(HANYANG_DP02CD_WG_8202S_16)//added by wangwei,2005-3-14 22:15
check_hanyang_dp02cd_wg_keylight_status();
#elif defined(USE_GPIO_TO_KEYLIGHT_WINGSUM)
check_wingsum_keylight_status();
#elif defined(OP_4110_SCAN_KEY_USE_GPIO)//lijd 2005-6-13 18:23
Check_panel_key_by_gpio();
#elif defined(OP_5112_SCAN_KEY_USE_GPIO)//caoh 2005-7-27 22:08
Check_panel_key_by_gpio();
#elif defined(OP_5116_SCAN_KEY_USE_GPIO)//caoh 2005-7-27 22:08
Check_panel_key_by_gpio();
#endif
}



#endif//defined(GPIO_KEY_LIGHT)



#ifdef PORTABLE_DVD //Jack open for all portable dvd
#include "vfd_portable.c" //0725 splitted for portable
#endif

#if defined(ALCO_PORTABLE)
#include "key_io_portable.c"
#endif

