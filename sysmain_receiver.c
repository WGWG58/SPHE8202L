#if defined (SUPPORT_RECEIVER)

extern UINT16 audif_get_frequency_mask(); // benson 2005/4/17 06:57¤U¤È
UINT16 freq_mask_temp; 
extern  void tuner_power_set(BYTE d);
extern  void save_rcvr_mode(BYTE mode);

static inline void mode_chang(void);
static inline void dvd_mode(void);
static inline void av1_mode(void);
static inline void av2_mode(void);

#ifdef LINE_IN_ENCODE
static inline void av_mode_encoder(void);
extern void fs_mp3_encoder_restart();
extern void fs_mp3_encoder_main();
extern inline void move_mp3_encode_data();
extern void do_write_data(void);
#endif

#if defined(SUPPORT_SPDIF_IN) && !defined(SPDIFIN_AVIN_IN_ONE_MODE)//chenzhao 20060118
static inline void spdif_in_mode(void);
#endif
static inline void tuner_mode(void);
static inline void eject_chang(void);

#include "hc4094.c"
#include "hc165.c"
#include "rom_bus_io.h"
#include "e2prom_map.h"
#include "amp_gui.h"

#ifdef SUPPORT_OP_FIVE_DISC//chenzhao20050107
#include "fdisc_gpio.h"
#endif

#ifdef SUPPORT_VFD_MENU//chenzhao20050118
#include ".\\Customers\\oritron\\vfd_setmenu.h"
#endif

#ifdef WAIT_SERVO_FLAG//chenzhao 2006-3-23 21:32 .
#include "dvddsp.h"
#endif

#if defined(RECEIVER_AV_MODE_DISABLE_VIDEO)&& defined(SCALER_6500)//chenzhao 2006-3-2 20:44 .
extern void SCA_DAC_HDMI_PwDown(void);
extern void scaler_6500_main(void);
#endif
#ifdef SUPPORT_COAXIAL_IN  //xyy 2004-4-29  for XQ
BYTE bCoaxialIn;
#endif
/*
 huziqin 2004-2-26
 call by tuner application and power amp's
*/
UINT16 check_sum(BYTE *data,BYTE len)
{
    UINT16 sum = 0;

    //printf("len %d\n",len);
    while(len>0)
        {
        sum += *data;
        len --;
        data ++;
    };
    //printf("sum %x\n",sum);

    return sum;
}


/*======================================================
switch audio and video by gpio
video: lower 4 bits
0--DVD
1--Video 1 in
2--Video 2 in

Audio: upper 4 bits
0--MIC
1--AUDIO 1 in
2--AUDIO 2 in
3--TUNER in

=======================================================*/
//extern void set_downmix_off();//UINT8 setup_sel[MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE][MAX_PAGE_ITEM];

/*
When use av input function, the sft_cfg(part of GPIO setting) setting is done in this function.
*/

void set_av_in_sft_cfg(void)//xyy 2004-3-23
{
    #if defined(SUNPLUS_RECEIVER_DVD)
    regs0->sft_cfg6 &= ~(0x1 << 5);
    #elif defined(XINGQIU_DVD_RECEIVER)
    //
    #endif
}

void av_in_switch(BYTE mode)
{
    mode = mode;
        printf("av_in_switch\n");
#if 0        
    set_av_in_sft_cfg();//xyy 2004-3-23
    GPIO_M_SET(AUIN_SL0, 1);             //xulf modified at 2004-2-20
    GPIO_M_SET(AUIN_SL1, 1);
    GPIO_M_SET(VIDEO_SL0, 1);
    GPIO_M_SET(VIDEO_SL1, 1);

    GPIO_E_SET(AUIN_SL0, 1);
    GPIO_E_SET(AUIN_SL1, 1);
    GPIO_E_SET(VIDEO_SL0, 1);
    GPIO_E_SET(VIDEO_SL1, 1);

    //AudioSetEcho(0,0);
    //echo_level = 0;
    //setup_SetEcho();

    //AudioSetMIC(1, 0); //Set MIC always on, 1:always on, (the second parameter:unsed now)
    //AudioSetMIC(1,1); 

    //AudioSetMICVol(8);
    //AudioSetMICVol_2(8); 

    //downmix off
    //set_downmix_off();
    //AudioSetOutputMode(6, 0); //Set Output mode(4:AC3 5.1 channel)
    //run_save_sel_cmd(3, 0);
//Audio ======================================  
    if((mode>>4) == 0)
    {
        printf("mic input\n");
        GPIO_O_SET(AUIN_SL1, 0);
        GPIO_O_SET(AUIN_SL0, 0);
    }

    if((mode>>4) == 1)
    {
        printf("audio 1 input\n");
        GPIO_O_SET(AUIN_SL1, 0);
        GPIO_O_SET(AUIN_SL0, 1);
    }

    if((mode>>4) == 2)
    {
        printf("audio 2 input\n");
        GPIO_O_SET(AUIN_SL1, 1);
        GPIO_O_SET(AUIN_SL0, 0);
    }

    if((mode>>4) == 3)
    {
        printf("tuner input\n");
        GPIO_O_SET(AUIN_SL1, 1);
        GPIO_O_SET(AUIN_SL0, 1);
    }

//Video ======================================
    if((mode&0x0f) == 0)
    {
        printf("out_0\n");
        GPIO_O_SET(VIDEO_SL1, 0);
        GPIO_O_SET(VIDEO_SL0, 0);
    }

    if((mode&0x0f) == 1)
    {
        printf("out_1\n");
        GPIO_O_SET(VIDEO_SL1, 1);
        GPIO_O_SET(VIDEO_SL0, 0);
    }

    if((mode&0x0f) == 2)
    {
        printf("out_2\n");
        GPIO_O_SET(VIDEO_SL1, 0);
        GPIO_O_SET(VIDEO_SL0, 1);
    }
#endif    
}

void SetTunerPower(BYTE power)//0 power off;1 power on
{
    #ifdef ORITRON_RECEIVER_6001    //hongfeng 2005-08-10
    if(power)
        GPIO_O_SET(56, 1);
    else
        GPIO_O_SET(56, 0);
    #elif defined(USE_ROM_CONTROL_TUNER_POWER)//chenzhao20060120//hongfeng 2005-08-01
        tuner_power_set(power);
    #endif
}

void receiver_startup()
{
    #ifndef SUPPORT_RECEIVER_MODE_MEMORY
    next_rcvr_mode =RECEIVER_MODE_DVD;  // this is changeable
    #endif
    last_non_dvd_rcvr_mode=0;//20060120
 
    // Simon 12-4-2003
    // Calculate support bits
    rcvr_support_bits = 0;
    #ifdef SUPPORT_DVD_PLAYER
    rcvr_support_bits += (1 << RECEIVER_MODE_DVD);
    #endif
    #ifdef SUPPORT_AV_IN
    rcvr_support_bits += (1 << RECEIVER_MODE_AV1);
    #endif
    #ifdef SUPPORT_SECOND_AV_IN
    rcvr_support_bits += (1 << RECEIVER_MODE_AV2);
    #endif
    #ifndef SPDIFIN_AVIN_IN_ONE_MODE//chenzhao 20060118
        #ifdef SUPPORT_SPDIF_IN
        rcvr_support_bits += (1 << RECEIVER_MODE_SPDIF);
        #endif
        #ifdef SUPPORT_COAXIAL_IN  //xyy 2004-4-29 for XQ
        rcvr_support_bits += (1 << RECEIVER_MODE_COAXIAL);
        #endif
    #endif
    #ifdef RADIO_2006 //huziqin 2006-4-19
    rcvr_support_bits += (1 << RECEIVER_MODE_TUNER);
    #endif
    #ifdef SUPPORT_DUMMY_MODE
    rcvr_support_bits += (1 << RECEIVER_MODE_DUMMY);
    #endif

    if (next_rcvr_mode == RECEIVER_MODE_DVD)
    {
        // original code moved to dvd_startup()
        // The code is right before ap_main()
        dvd_startup();
        switch_modes_now = 0;
        servo_inited = 1;
        #if defined(SUPPORT_8202D_EXT_ADC) && defined(NO_MIC)//chenzhao2000118
        disable_8202D_EXT_ADC();
        #endif
        #ifdef ROM_BUS_EXTENT_IO
            #ifdef ORITRON_RECEIVER_6505
        	video_sel_dvd();
            #endif
        audio_sel_gnd();
        #endif //ROM_BUS_EXTENT_IO    
        //psprintf(RegionValStr[REGION2], "DVD");
        //PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);
    } 
    else   // Start in a non-DVD mode
    {
        // In the future, we will enter this first,
        // as soon as I figure out how to manage the states and loader
        // correctly.
        // 12-16-2003 Update:  DVD works w/o starting in DVD

        #if DISC_SYSTEM==DISC_SYSTEM_ATAPI
            #if defined(SUPPORT_RECEIVER_MODE_MEMORY)
            servo_inited = 0;//chenzhao for stop servo on power on non dvd mode;2005-4-18 15:37  
            #else
            servo_inited = 1;
            #endif
        #endif
        switch_modes_now = 1;
        system_state = SYSTEM_MODE_CHANGE;
        play_state = VCD_STATE_STOP;
        power_on_gpio_demute(1);//chenzhao20060118.demute spdif out.
        power_on=0;
    }
    //init_amp();//move to sysmain.c chenzhao20050808

    #ifdef ORITRON_RECEIVER_6505//chenzhao 20060107
    set_video_mute(1); //1:demute, 0: mute
    #endif
}

#if 0 /*2005-6-6 19:56 huziqin mask not use now*/
void show_noise_channel(ch)
{
	switch(ch)
	{
		case 0: 
			psprintf(RegionValStr[REGION2], "TEST FL");
			break;
		case 1:
			psprintf(RegionValStr[REGION2], "TEST CE");
			break;
		case 2:
			psprintf(RegionValStr[REGION2], "TEST FR");
			break;
		case 3:
			psprintf(RegionValStr[REGION2], "TEST SR");
			break;
		case 4:
			psprintf(RegionValStr[REGION2], "TEST SL");
			break;
		default:
			break;
		

	}
	
    PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);
}

void do_noise_sequencer(void)
{
	BYTE ch = 0;

    AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
    //init_audio_dsp_coding_mode();                
    AUDIF_Init_DSPCodingMode();
    AUDIF_Set_SampleRate(FS_44K);//2004AUDDRV audif_set_sample_rate(FS_44K);
    AUDIF_Set_CodingMode(AUDIF_CODING_MODE_NOISE);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_NOISE);
    GPIO_DEMUTE();
    watchdog_onoff(0);
    system_state = SYSTEM_DOING_NOISE;
    while (system_state == SYSTEM_DOING_NOISE)
    {
        ch = get_dsp3_pcm_value(22);
        show_noise_channel(ch);
    
    	polling();
    }
                

}

#endif //0

#ifdef TP6311_DRIVER_VFD
extern UINT16  vfd_set_av1(UINT16 index);
extern UINT16  vfd_set_av2(UINT16 index);
extern UINT16  vfd_set_spdifin(UINT16 index);
#endif
extern void stop_loader(void);

//#define STOP_SERVO_IN_OTHER_MODE//chenzhao 20060107  //huziqin 2004-4-27

#ifdef STOP_SERVO_IN_OTHER_MODE
void wait_servo_stop(void)
{
	//drv_init();
    delay_srv_10ms(100);
    //system_stop();
    stop_loader();
    delay_srv_10ms(5);
}
#endif

static inline void mode_chang(void)
{
          switch_modes_now = 0;
          ClearOsdMsg(0);
          #ifdef SUPPORT_VFD_MENU//chenzhao20060118
          switch_mode_to_clear();
          #endif          
          if(current_rcvr_mode != RECEIVER_MODE_DVD)//chenzhao20060120
              last_non_dvd_rcvr_mode = current_rcvr_mode;
          #ifdef STOP_SERVO_IN_OTHER_MODE
          //chenzhao 20051031.Reduce switch time of non DVD mode. 
          if((current_rcvr_mode ==RECEIVER_MODE_DVD)&&(next_rcvr_mode!=RECEIVER_MODE_DVD))
          {
              #ifdef SUPPORT_OP_FIVE_DISC  //OP add
			  turn_on_5disc_led(1); //turn off led 
              #endif
              if(CDOpened())
              {
                  close_tray(0);
                  CDSetStop();//chenzhao10051110
                  delay_srv_10ms(100);//chenzhao20051123
                  stop_loder_cnt=2;
                  #ifdef PUSH_TRAY_IN_DISPLAY//chenzhao20051123
                  void push_tray_in_detect(void);
                  current_rcvr_mode = next_rcvr_mode;
                  push_tray_in_detect();
                  #endif     
                  //wait_servo_stop();
              
              }
              else if(servo_inited)//chenzhao10051110
                  stop_loader();
              //if(servo_inited==0)//chenzhao 20051031.for stop servo with disc on power on non dvd mode;
              //    delay_srv_10ms(5);
              //else
              //    delay_srv_10ms(5);
              //delay_srv_10ms(5);
              //wait_servo_stop();
              servo_inited = 1;//chenzhao for stop servo on power on non dvd mode;2005-4-18 15:37  
              //Wait_LOAD_stop=5;
          }
          else if((current_rcvr_mode!=RECEIVER_MODE_DVD)&&(next_rcvr_mode==RECEIVER_MODE_DVD)&&(stop_loder_cnt<4))//hongfeng add 2005-11-16
          {
              //psprintf(linebuf,"stop_loder_cnt =%d  \n",stop_loder_cnt);
              //io_write_wait(linebuf);
              PrintOsdMsg(STR_OS_READ,REGION1,1,0);
              delay_srv_10ms((4-stop_loder_cnt)*50);
          }
	
	#elif defined(POWER_ON_SERVO_STOP)//STOP_SERVO_IN_OTHER_MODE //hongfeng 2006/3/8
    if((current_rcvr_mode ==RECEIVER_MODE_DVD)&&(next_rcvr_mode!=RECEIVER_MODE_DVD))
	{
		#ifdef SUPPORT_OP_FIVE_DISC  //OP add
		turn_on_5disc_led(1); //turn off led 
		#endif
		if(CDOpened())
		{
		  close_tray(0);
		  CDSetStop();//chenzhao10051110
		  delay_srv_10ms(100);//chenzhao20051123
		  #ifdef PUSH_TRAY_IN_DISPLAY//chenzhao20051123
		  void push_tray_in_detect(void);
		  current_rcvr_mode = next_rcvr_mode;
		  push_tray_in_detect();
		  #endif     		
		}
		//else if(servo_inited)//chenzhao10051110
		  //stop_loader();
		atapi_p_start_stop_unit(Immed_0,START_STOP_DO_STOP);//hongfeng add 2006/3/8
		//if(servo_inited==0)//chenzhao 20051031.for stop servo with disc on power on non dvd mode;
		//    delay_srv_10ms(5);
		//else
		//    delay_srv_10ms(5);
		//delay_srv_10ms(5);
		//wait_servo_stop();
		servo_inited = 1;//chenzhao for stop servo on power on non dvd mode;2005-4-18 15:37  
		//Wait_LOAD_stop=5;
        power_on_gpio_demute(1);//chenzhao20060217.avoid power on receiver state no spdif output.
        		
		//by joke fixed dpl937 thomson #QAE-A10
		#ifdef OP_PROGRAM_LIST_OPER 
			clear_prog_list();
		#endif
    }
    #endif//STOP_SERVO_IN_OTHER_MODE
    	
    #ifdef RECEIVER_AV_MODE_DISABLE_VIDEO//chenzhao 2006-3-2 20:39 .
    if(next_rcvr_mode==RECEIVER_MODE_AV1 || next_rcvr_mode==RECEIVER_MODE_AV2)
    {
              tv_dacoff(0x3f);//chenzhao 2006-3-23 20:55 .
         #ifdef SCALER_6500
         SCA_DAC_HDMI_PwDown();
         #endif
    }
    else if(current_rcvr_mode==RECEIVER_MODE_AV1 || current_rcvr_mode==RECEIVER_MODE_AV2)
    {
              tv_dacoff(0);//chenzhao 2006-3-23 20:55 .
         #ifdef SCALER_6500
         scaler_6500_main();
         #endif
    }
   #endif
   
          current_rcvr_mode = next_rcvr_mode;
 #ifdef SUPPORT_COAXIAL_IN  //xyy 2004-4-29  for XQ
 		if(current_rcvr_mode == RECEIVER_MODE_SPDIF)
 		{
    		bCoaxialIn = 0;
			GPIO_O_SET(OPT_COAX_SEL,0);
  		}
  		else if(current_rcvr_mode == RECEIVER_MODE_COAXIAL)
  		{
  			bCoaxialIn = 1;
			GPIO_O_SET(OPT_COAX_SEL,1);
   		}
 #endif
          
          
        #ifdef PORTABLE_POWER_ON_MUTE
        if(current_rcvr_mode!=RECEIVER_MODE_DVD)
            regs0->sft_cfg3 |=((0x01<<6));//CHENZZ FOR LRCK=1.for power on noise.
        #endif
        #ifdef SUPPORT_VFD_MENU//chenzhao 20060118
        init_vfd_set_menu();
        #endif               
	
	#ifdef SUPPORT_VFD_MESSAGE
		if(current_rcvr_mode!=RECEIVER_MODE_TUNER)
			set_vfd_message_state(VFD_MESSAGE_IDLE,0);
	#endif
}

static inline void dvd_mode(void)
{
            		/*when change aviod noise hongfeng 2005-03-09*/
        		AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
                AUDIF_Set_CodingMode(AUDIF_CODING_MODE_DEFAULT);//chenzhao20060119
                //init_audio_dsp_coding_mode();    
                AUDIF_Init_DSPCodingMode();
                
                #if defined(SUPPORT_8202D_EXT_ADC) && defined(NO_MIC)//chenzhao2000118
                disable_8202D_EXT_ADC();
                #endif
            #ifdef HC4094
                 hc4094_set_io(HC4094_DVD_MODE);	// wzj 2004-7-13
            #endif
            #ifdef ROM_BUS_EXTENT_IO    
                audio_sel_gnd();
            #endif //ROM_BUS_EXTENT_IO    
                if (!servo_inited)
                {
                    drv_init();
                    servo_inited = 1;
                }
                else 
                {
                    close_tray(0);
                }
                dvd_startup();
                
}

#ifdef LINE_IN_ENCODE

static inline void av_mode_encoder(void)
{

                AUDIF_Set_Volume(0);
                user_mute =1;//to avoid reset dsp auto demute.
                //we should switch the audio switch first and mute,to avoid pop noise.chenzhao20060118
                #ifdef HC4094
                hc4094_set_io(HC4094_AV1_MODE);
                #endif  
                #ifdef ROM_BUS_EXTENT_IO
                audio_sel_aux1();
                #endif //ROM_BUS_EXTENT_IO
                
                psprintf(RegionValStr[REGION2], "AV1");
                PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);

                #ifdef ADC_EXT_RESET
                reset_ext_adc();
                #endif
            
                #if defined(SUPPORT_8202D_EXT_ADC) && defined(NO_MIC)//chenzhao2000118
                init_8202D_EXT_ADC();
                #endif  // SUPPORT_8202D_EXT_ADC
                
                #ifdef SPDIFIN_AVIN_IN_ONE_MODE
                set_outside_inputflag(1);//chenzhao 20060119
                #else
                switch_to_tuner_dsp();
                #endif//#ifndef SPDIFIN_AVIN_IN_ONE_MODE



    while(1)
    {
        polling();
        switch(linein_state)
        {
            case 0: //idle
            //printf(" ==============  line in state 0====");
            break;

            case 1: //set
               // printf(" ==============  line in state 1=============\n");
				fs_mp3_encoder_restart();
                //----------------------------------------------//
                //wait_servo_stop();
                //-----------------------------------------------//
            #if 0
                GPIO_O_SET(EXT_ADC_RESET,0);        //qiut move here avoid noise when switch line in
            #endif
    			if(mp3_encoder_state == test_device_exist)
	    		{
    				printf("\n\nMP3_ENCODER init device\n\n");
    				fs_mp3_encoder_main();
    				printf("\n\nMP3_ENCODER init FS\n\n");
    				fs_mp3_encoder_main();
    				printf("\n\nMP3_ENCODER test DIR\n\n");
    				fs_mp3_encoder_main();
		    	}

    			if(mp3_encoder_state == test_wait_command)
    			{
    				mp3_encoder_state = test_target_file;
    			}

    			if(mp3_encoder_state == test_stop)
    			{
    				fs_mp3_encoder_main();
    			}
				if(mp3_encoder_state == test_target_file)
				{
					printf("\n\nMP3_ENCODER new file\n\n");
					fs_mp3_encoder_main();
					printf("file write preset\n");
					fs_mp3_encoder_main();
					if(mp3_encoder_state == test_write_data)
					{
						printf("switch to DSP3Info_CD_MP3_ENCODER\n");
                        printf("--------------->dsp config %x\n",encoder_type);
						AUDIF_Init_CD_MP3_ENCODER();
						AUDIF_Reset_DSP();
						AUDIF_Init_CD_MP3_ENCODER();
						printf("WAV_BARRIER_PTR=%x,WAV_DUMP_PTR=%x\n",WAV_BARRIER_PTR,WAV_DUMP_PTR);
						if(IS_AUDIF_CODING_MODE_CD_MP3_ENCODER)
						   io_write_wait("IS_AUDIF_CODING_MODE_CD_MP3_ENCODER mode now....\n");

					}
				}    
				linein_state=3;
				psprintf(RegionValStr[REGION1], "LINE IN REC");
	            PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
                 
                break;
                
            case 3:
                //io_write_wait(" ==============  line in state 3=============\n");
                  psprintf(RegionValStr[REGION1], "LINE IN REC");
	              PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
                  move_mp3_encode_data();
                  //do_write_data();
                break;

            case 2: //close
                //printf(" ==============  line in state 2=============\n");
				if(mp3_encoder_state == test_write_data)
				{
	                printf("finish file write\n");
	                polling_MP3_encoder = 2;
	                fs_mp3_encoder_main();
	                printf("close file\n");
	                fs_mp3_encoder_main();
					if(mp3_encoder_state == test_stop)
					{
						fs_mp3_encoder_main();
					}
					psprintf(RegionValStr[REGION1], "CLOSE FILE ");
	                PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
				}  
#if 0
                regs0->sft_cfg0 |= ((0x1)<<4);         //disable ext AD data IO  qiut 
#endif
                AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
				linein_state=0;
                break;
        }

        
        if(system_state == SYSTEM_OPEN)
            break;
    }

}

#endif //LINE_IN_ENCODE

void switch_to_tuner_dsp(void)
{
    AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
    //init_audio_dsp_coding_mode();    
    AUDIF_Init_DSPCodingMode();            
    AUDIF_Set_SampleRate(FS_44K);//2004AUDDRV audif_set_sample_rate(FS_44K);
    AUDIF_Set_CodingMode(AUDIF_CODING_MODE_TUNER);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_TUNER);
    //av_in_switch(0x11);
    AUDIF_Set_Echo(0,0);//2004AUDDRV AudioSetEcho(0,0);  //huziqin 2004-2-26
    
    GPIO_DEMUTE();
    AUDIF_Demute();
    #if defined(USE_AMP_MUTE)   //chenzhao20060211
    if(!user_amp_mute) 
        sub_masterMute(AMP_DEMUTE);
    #endif
}

#if defined(SUPPORT_SPDIF_IN) //by joke add
void switch_to_spdifin_dsp(void)//chenzhao20060211
{
    AUDIF_Set_CodingMode(AUDIF_CODING_MODE_SPDIFINCD);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_SPDIFINCD);
    AUDIF_Set_SampleRate(FS_44K);//2004AUDDRV audif_set_sample_rate(FS_44K);
    //AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
    freq_mask_temp = audif_get_frequency_mask();
    AUDIF_Set_FrqMsk(1);           
    spdifin_type = 0xff; /*2005-6-6 20:08 huziqin avoid AC3 no sound*/
    
    spdif_in_init();
    
    GPIO_DEMUTE();
    AUDIF_Demute();
    #ifdef USE_AMP_MUTE//chenzhao20060211
    if(!user_amp_mute)
        sub_masterMute(AMP_DEMUTE);
    #endif
}
#endif

#ifdef SPDIFIN_AVIN_IN_ONE_MODE//chenzhao 20060118
void outside_input_handle(void)
{
	int coaxal_input=0;//chenzhao20051207
	
	if(get_outside_inputflag())
	{
        AUDIF_Set_Volume(0);
        user_mute =1;//to avoid reset dsp auto demute.
        
		set_outside_inputflag(0);
		
		if(current_rcvr_mode == RECEIVER_MODE_AV1)
		{
			coaxal_input = get_av1_input();	
		}
		else if(current_rcvr_mode == RECEIVER_MODE_AV2)
		{
			coaxal_input = get_av2_input();	
		}
		
		psprintf(linebuf,"coaxal_input= %d\n",coaxal_input);
        io_write_wait(linebuf);
		if(coaxal_input)	
		{
			//coaxal input
            //init_audio_dsp_coding_mode();
            switch_to_spdifin_dsp();//chenzhao20060211
		}
		else  
		{
			//analog input
            switch_to_tuner_dsp();
		}
	}	
}
#endif

static inline void av1_mode(void)
{
                AUDIF_Set_Volume(0);
                user_mute =1;//to avoid reset dsp auto demute.
                //we should switch the audio switch first and mute,to avoid pop noise.chenzhao20060118
                #ifdef HC4094
                hc4094_set_io(HC4094_AV1_MODE);
                #endif  
                #ifdef ROM_BUS_EXTENT_IO
                audio_sel_aux1();
                #endif //ROM_BUS_EXTENT_IO
                
                psprintf(RegionValStr[REGION2], "AV1");
                PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);

                #ifdef ADC_EXT_RESET
                reset_ext_adc();
                #endif
            
                #if defined(SUPPORT_8202D_EXT_ADC) && defined(NO_MIC)//chenzhao2000118
                init_8202D_EXT_ADC();
                #endif  // SUPPORT_8202D_EXT_ADC
                
                #ifdef SPDIFIN_AVIN_IN_ONE_MODE
                set_outside_inputflag(1);//chenzhao 20060119
                #else
                switch_to_tuner_dsp();
                #endif//#ifndef SPDIFIN_AVIN_IN_ONE_MODE

                system_state = SYSTEM_DOING_AV1;            
            	while (system_state == SYSTEM_DOING_AV1)
                {
                	polling();
                    #ifdef SPDIFIN_AVIN_IN_ONE_MODE
                    outside_input_handle();
                    #endif
                }
}

static inline void av2_mode(void)
{
                AUDIF_Set_Volume(0);
                user_mute =1;//to avoid reset dsp auto demute.

                #ifdef ROM_BUS_EXTENT_IO
                audio_sel_aux2();
                #endif //ROM_BUS_EXTENT_IO

                psprintf(RegionValStr[REGION2], "AV2");
                PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);
                
                #ifdef ADC_EXT_RESET
                reset_ext_adc();
                #endif
                
                #if defined(SUPPORT_8202D_EXT_ADC) && defined(NO_MIC)//chenzhao2000118
                init_8202D_EXT_ADC();
                #endif  // SUPPORT_8202D_EXT_ADC
                
                #ifdef SPDIFIN_AVIN_IN_ONE_MODE
                set_outside_inputflag(1);//chenzhao 20060119
                #else
                switch_to_tuner_dsp();
                #endif//#ifndef SPDIFIN_AVIN_IN_ONE_MODE
                
                system_state = SYSTEM_DOING_AV2;            
            	while (system_state == SYSTEM_DOING_AV2)
                {
                	polling();
                    #ifdef SPDIFIN_AVIN_IN_ONE_MODE
                    outside_input_handle();
                    #endif
                }
}

#if defined(SUPPORT_SPDIF_IN) && !defined(SPDIFIN_AVIN_IN_ONE_MODE)//chenzhao 20060118
static inline void spdif_in_mode(void)
{
#ifdef SUPPORT_COAXIAL_IN  //xyy 2004-4-29 for XQ
               vfd_set_spdifin(bCoaxialIn);
#else
               //vfd_set_spdifin(0);
#endif
                switch_to_spdifin_dsp();//chenzhao20060211
            #ifdef SUPPORT_VFD
               //vfd_set_spdifin(0);
#endif
                system_state = SYSTEM_DOING_SPDIF;
            while (system_state == SYSTEM_DOING_SPDIF) 
            {                
                polling();
            }
            freq_mask_temp = audif_get_frequency_mask();   // benson 2005/4/17 06:59¤U¤È
            AUDIF_Set_FrqMsk(freq_mask_temp);
            //spdifin_type = 0xff; moved into switch_to_spdifin_dsp()//chenzhao20060211/*2005-6-6 20:08 huziqin avoid AC3 no sound*/

}
#endif//#ifdef SUPPORT_SPDIF_IN

static inline void tuner_mode(void)
{
                AUDIF_Set_Volume(0);
                user_mute =1;//to avoid reset dsp auto demute.

                SetTunerPower(1);
                #ifdef HC4094
                hc4094_set_io(HC4094_TUNER_MODE);
                #endif    
                #ifdef ROM_BUS_EXTENT_IO
                audio_sel_tuner();
                #endif //ROM_BUS_EXTENT_IO

                #ifdef ADC_EXT_RESET
                reset_ext_adc();
                #endif
                #if defined(SUPPORT_8202D_EXT_ADC) && defined(NO_MIC)//chenzhao2000118
                init_8202D_EXT_ADC();
                #endif  // SUPPORT_8202D_EXT_ADC
                


                ShowTitle();

                switch_to_tuner_dsp();
                
                watchdog_onoff(0);      //close watchdog for tuner auto search no reset hongfeng 2005-01-21
                system_state = SYSTEM_DOING_TUNER;
            	tuner_main();
                SetTunerPower(0);
}



static inline void eject_chang(void)
{
        next_rcvr_mode = RECEIVER_MODE_DVD;
        last_non_dvd_rcvr_mode = current_rcvr_mode;//chenzhao20060120
        #ifdef RECEIVER_AV_MODE_DISABLE_VIDEO//chenzhao 2006-3-23 21:10 .
        if(current_rcvr_mode==RECEIVER_MODE_AV1 || current_rcvr_mode==RECEIVER_MODE_AV2)
        {
            tv_dacoff(0);//chenzhao 2006-3-23 20:55 .
            #ifdef SCALER_6500
            scaler_6500_main();
            #endif
        }
        #endif
        current_rcvr_mode = next_rcvr_mode;
        switch_modes_now = 0;

	    erase_vfd_mem();
	
        #if defined(SUPPORT_8202D_EXT_ADC) && defined(NO_MIC)//chenzhao2000118
        disable_8202D_EXT_ADC();
        #endif

        AUDIF_Set_CodingMode(AUDIF_CODING_MODE_DEFAULT);//chenzhao20060119
        #ifdef ROM_BUS_EXTENT_IO
        audio_sel_gnd();
        #endif //ROM_BUS_EXTENT_IO
        #ifdef HC4094
         hc4094_set_io(HC4094_DVD_MODE);    // wzj 2004-7-13
        #endif
        
        #ifdef SUPPORT_RECEIVER_MODE_MEMORY
        save_rcvr_mode(current_rcvr_mode);//chenzhao20051118
        #endif

        #ifdef SUPPORT_VFD_MENU//chenzhao 20060118
        init_vfd_set_menu();
        #endif               
        #ifdef SUPPORT_VFD_MESSAGE
	    set_vfd_message_state(VFD_MESSAGE_IDLE,0);
        #endif

       #ifdef SUPPORT_OP_FIVE_DISC  //chenzhao20060109
        set_video_mute(1); 
        turn_on_5disc_led(0); //turn On led 
        reset_5disc_gpio();
        #endif
        #ifdef ORITRON_RECEIVER_6505
        osd_tog_region(REGION2, OSD_OFF);
        #else
        psprintf(RegionValStr[REGION2], "DVD");
        PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);
        #endif
        #ifdef POWER_ON_SERVO_STOP//chenzhao 2006-3-23 21:38 .
        if(need_power_on_servo == 1)
        {
            //printf_w("POWER_ON_SERVO_STOP eject\n"); 
            atapi_p_start_stop_unit(Immed_1,START_STOP_DO_LOAD);
            need_power_on_servo = 0;
            #if defined(WAIT_SERVO_FLAG)&&defined(MULTIDISC_LOADER)
            {
                BYTE i=0;
                do
                {
                    delay_srv_10ms(1);
                    i++;
                    //printf_w("_0x%x_E %d ",cIDEStatus,i);
                }
                while(cIDEStatus==BIT_BSY && i<120);
            }
            #endif
        }
        #endif//#ifdef POWER_ON_SERVO_STOP
        ircmd_trayout();
        system_state = SYSTEM_OPEN;
}



void receiver_check_system_state()
{
	//int init_cnt=0;no use.chenzhao.20050620
	
    switch(system_state)
    {
        case SYSTEM_MODE_CHANGE:
        mode_chang();
        switch (current_rcvr_mode)
        {
            case RECEIVER_MODE_DVD:
                dvd_mode();
                break;          
            case RECEIVER_MODE_AV1:
            #ifdef LINE_IN_ENCODE            
                av_mode_encoder();
                //av1_mode();
            #else
                av1_mode();

            #endif
            	break;
            case RECEIVER_MODE_AV2:
                av2_mode();
            	break;
#if defined(SUPPORT_SPDIF_IN) && !defined(SPDIFIN_AVIN_IN_ONE_MODE)//chenzhao 20060118
            case RECEIVER_MODE_SPDIF:
#ifdef SUPPORT_COAXIAL_IN  //xyy 2004-4-29 for XQ
            case RECEIVER_MODE_COAXIAL:
#endif
                spdif_in_mode();
                break;
#endif  // SUPPORT_SPDIF_IN         

            case RECEIVER_MODE_TUNER:
                tuner_mode();
                break;

          }
        break;

    // Simon: 1-7-2004
    // This state occurs when we use eject
    // To switch back to DVD mode
    case SYSTEM_EJECT_CHANGE:
        eject_chang();
        break;
        }   
}    
#endif

#ifdef SUPPORT_RECEIVER_MODE_MEMORY
void save_rcvr_mode(BYTE mode)
{
    if(0<WriteToI2c(0xa0, RECEIVER_MODE_MEMORY_ADDR, (BYTE *)&mode,sizeof(BYTE)))
    {
        printf("save_rcvr_mode ok\n");
    }
    else
    {
        printf("save_rcvr_mode fail\n");
    }
    printf("mode=%d\n",mode);
}
#endif


