
#include "osd.h"
#include "iop.h"
#include "e2prom_map.h"
#include "amp_gui.h"
#include "auddef.h" //hongfeng 2005-08-01
#ifdef ROM_BUS_EXTENT_IO//chenzhao20060114
#include "rom_bus_io.h"
#endif
#ifdef TDA7448
#include "tda7448.c"
#endif

#ifdef PT2258
#include "pt2258.c"
#endif

#ifdef TAS_5508_PWM
#include "Tas5508_pwm.h"
#endif

#ifdef SUPPORT_DDX8001
#include "ddx8001.h"
#endif

#if defined(TLV320_DAC)  //chenzhao20060118
#include "tlv320.h"
#endif 

#ifndef SUPPORT_VFD_MESSAGE
BYTE  subvol_time_out = 0 ;
#endif
BYTE current_channel = 0;
BYTE volume_changed =0;

#ifdef TREBLE_BASS_EQ_MENU_INTERFACE
#include "ircode.h" 
TONE_TYPE  amp_tone_mode = TONE_IDLE;
#endif

#ifdef SUPPORT_VFD_MESSAGE
void set_vfd_message_state(BYTE state,BYTE time);
#endif

#if defined(DOLBY_AMP_VOLUME_CTRL)
/*
channel: 0--6
 
 1-6->sub channel vol
vol:0-->79dB
*/
void subvol_channel_volume(BYTE channel,BYTE vol)
{
#ifdef SUPPORT_APOGEE_AMP
	ddx_set_channel_vol(channel, vol);
#endif

#ifdef TAS_5026_PWM
	tas_5026_channel_vol(channel,  vol);
#elif defined(TAS_5508_PWM)
    tas_5508_channel_vol(channel,  vol);
#endif
}
#endif

#if  defined(TDA7448)||defined(PT2258)||defined(DOLBY_AMP_VOLUME_CTRL)

#ifdef DOLBY_AMP_VOLUME_CTRL
#ifdef  SUPPORT_BASS_TREBLE
char *channel_str[MAX_VOLUM_CHANNEL]={"FRONT L","FRONT R","SURROUND L","SURROUND R","CENTER","LFE","BASS","TREBLE",};
#else
char *channel_str[MAX_VOLUM_CHANNEL]={"LFE","SURROUND R","SURROUND L","CENTER","FRONT R","FRONT L"};
#endif
#else
char *channel_str[6]={"SW","SR","SL","CE","FR","FL"};
//BYTE  channel_str[6]={STR_SUB_CH,STR_SR_CH,STR_SL_CH,STR_C_CH,STR_FR_CH,STR_FL_CH};
#endif

/*
current_channel:
0->main 
1->ch1
2->ch2
3->ch3
4->ch4
5->ch5
6->ch6
7->ch bass
8->ch treble
*/
BYTE volum_list[MAX_VOLUM_CHANNEL+1];
#ifdef  SUPPORT_BASS_TREBLE
BYTE channel_vol_offset[MAX_VOLUM_CHANNEL] = {CH1_VOL,CH2_VOL,CH3_VOL,CH4_VOL,CH5_VOL,CH6_VOL,CH_BASS_VOL,CH_TREBEL_VOL};
#else
BYTE channel_vol_offset[MAX_VOLUM_CHANNEL] = {CH1_VOL,CH2_VOL,CH3_VOL,CH4_VOL,CH5_VOL,CH6_VOL};
#endif

#ifdef TAS_5508_PWM
#define  GET_ABSOLUTE_VALUE(channel)     (MAIN_VOL_MAX+channel_vol_offset[channel-1]-(CH_VOL_MAX/2))
#else//#ifdef TAS_5508_PWM
#define  GET_ABSOLUTE_VALUE(channel)     (volum_list[0]+channel_vol_offset[channel-1]-(CH_VOL_MAX/2))
#endif//#ifdef TAS_5508_PWM

#ifdef SAVE_AMP_VOLUME
/*
  channel:
  main  0
  fl       1
  fr       2
  sl      3
  sr       4
  ce       5
  lfe     6

  global var: volum_list

  AMPLIFIER_START 228
  bass offset   7
  treble offset 8
*/

//#define  AMPLIFIER_START  228 moved to e2prom_map.h
extern BYTE ddx_Bass_lev;
extern BYTE ddx_Treble_lev;


void reset_amp_variable(void)
{
    int i;
    volum_list[0]=MAIN_VOL;
    channel_vol_offset[0]=CH1_VOL;
    channel_vol_offset[1]=CH2_VOL;
    channel_vol_offset[2]=CH3_VOL;
    channel_vol_offset[3]=CH4_VOL;
    channel_vol_offset[4]=CH5_VOL;
    channel_vol_offset[5]=CH6_VOL;
    #ifdef SUPPORT_BASS_TREBLE
    channel_vol_offset[6]=CH_BASS_VOL;
    channel_vol_offset[7]=CH_TREBEL_VOL;
    #endif//#ifdef SUPPORT_BASS_TREBLE
    for(i=1;i<MAX_VOLUM_CHANNEL;i++)
		volum_list[i] = GET_ABSOLUTE_VALUE(i);
    for(i=0;i<MAX_VOLUM_CHANNEL;i++)
        save_amp_variable(i);
}

void save_amp_variable(BYTE ch)
{
	BYTE data;
#if 0//def  SUPPORT_APOGEE_AMP	
	data = ddx_Treble_lev;
	WriteToI2c(I2C_ID_MEMORY, AMPLIFIER_START+8,&data, 1);
#endif
	if(ch==0)
	{
        #ifdef TAS_5508_PWM
        data = volum_list[0];
        WriteToI2c(I2C_ID_MEMORY, AMPLIFIER_START,&data, 1);
        #ifdef DEBUG_VOLUME
            printf("save ch %d data %d\n",ch,data);
        #endif
        #endif//#ifdef TAS_5508_PWM
	}
	else if ((ch > 0)&&(ch<=MAX_VOLUM_CHANNEL))
	{
		data = channel_vol_offset[ch-1];
		WriteToI2c(I2C_ID_MEMORY, AMPLIFIER_START+ch,&data, 1);
#ifdef DEBUG_VOLUME
		printf("save ch %d data %d\n",ch,data);
#endif
	}
}



void load_amp_variable()
{
	BYTE data,ch;
	int res;

    #ifdef TAS_5508_PWM
    res = ReadFromI2c(I2C_ID_MEMORY, AMPLIFIER_START,&data, 1);
    if(res>0)
        volum_list[0] = data;
    #endif//#ifdef TAS_5508_PWM
    
	for(ch = 1;ch<=MAX_VOLUM_CHANNEL;ch++)
	{
		res = ReadFromI2c(I2C_ID_MEMORY, AMPLIFIER_START+ch,&data, 1);
		
		if(res == 1)//no error
		{
#ifdef DEBUG_VOLUME
			printf("load ch %d data %d\n",ch,data);
#endif

			if(data <= CH_VOL_MAX)
				channel_vol_offset[ch-1] = data;
		}
	}
}

#endif	


extern void init_tas_5026();
void init_subvol()
{
	BYTE ch;

	volum_list[0] = MAIN_VOL;
#ifdef SAVE_AMP_VOLUME
	load_amp_variable();
#endif
#ifdef PT2258
	init_pt2258();
#endif

#ifdef TAS_5026_PWM
	init_tas_5026();
#elif defined(TAS_5508_PWM)
    init_tas_5508();
#endif

    #ifdef TAS_5508_PWM
    subvol_channel_volume(0, volum_list[0]);
    #endif
	for(ch = 1;ch<=MAX_VOLUM_CHANNEL;ch++)
	{
		volum_list[ch] = GET_ABSOLUTE_VALUE(ch);
		subvol_channel_volume(ch,volum_list[ch]);
	}
	/*init lineout volume*/
    #ifdef TAS_5508_PWM
	subvol_channel_volume(VOL_CH_BSL, LINE_OUT_VOL);
	subvol_channel_volume(VOL_CH_BSR, LINE_OUT_VOL);
    #else
	subvol_channel_volume(7, LINE_OUT_VOL);
	subvol_channel_volume(8, LINE_OUT_VOL);
    #endif
}

/*
current_channel:
0->main 
1->ch1
2->ch2
3->ch3
4->ch4
5->ch5
6->ch6
*/

void subvol_next_channel()
{
	if(current_channel == 6)
		current_channel = 0;
    #ifdef SUPPORT_BASS_TREBLE
    else if(current_channel == 0)
		current_channel = 7;
    else if(current_channel == 8)
		current_channel = 1;
    #endif
	else
		current_channel ++;

	if(current_channel == 0)
    {
		psprintf(RegionValStr[REGION1], "VOLUME %d",volum_list[0]);
     	PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
    }
	else
	{
        #ifdef SUPPORT_VFD_MESSAGE
        set_vfd_message_state(VFD_MESSAGE_VOL,SUBVOL_TIME_OUT);
        #else
		subvol_time_out = SUBVOL_TIME_OUT;
        #endif
        show_channel_msg();
	}
}

/*
  to come with dolby's demand
  sub channel adjust from -10dB to +10dB
*/
//char  channel_offset_str[];
void show_channel_msg()
{
#ifdef DEBUG_VOLUME
	printf("keep ch %d  %d\n",current_channel,(channel_vol_offset[current_channel-1]));
#endif

	if((channel_vol_offset[current_channel-1])==(CH_VOL_MAX/2))
	{
		psprintf(RegionValStr[REGION1],"%s 0",channel_str[current_channel-1]);
	}
	else if((channel_vol_offset[current_channel-1])<(CH_VOL_MAX/2))
	{
		psprintf(RegionValStr[REGION1],"%s -%d",channel_str[current_channel-1],(CH_VOL_MAX/2)-(channel_vol_offset[current_channel-1]));
	}
	else
	{
		psprintf(RegionValStr[REGION1],"%s +%d",channel_str[current_channel-1],(channel_vol_offset[current_channel-1])-(CH_VOL_MAX/2));
	}
	PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
}

/*
	I place this function at 500ms polling loop
	so,the time out is 500ms * 10 == 5 sec 
*/

#ifdef SUPPORT_VFD_MESSAGE

void exit_channel_volume(void)
{
    current_channel = 0;
}

#else
void polling_channel_timeout(void)
{
	if(subvol_time_out>0)
	{
		subvol_time_out--;
/*		if(current_channel > 0)
		{
			show_channel_msg();
		}*/
	}
	else
	{
		current_channel = 0;
	}
}
#endif


#ifdef TAS_5508_PWM
void subvol_main_vol()
{
    #if defined(USE_AMP_MUTE)&& !defined(CHANGE_VOL_DEMUTE) //chenzhao20050926
    if(!user_amp_mute)
    #endif//#ifdef USE_AMP_MUTE
    {
        #ifdef SUPPORT_AMP_IO_MUTE
        amp_io_demute();
        #endif
	    subvol_channel_volume(0,volum_list[0]);
    }
}
#else//#ifdef TAS_5508_PWM
/*
  according to DOLBY's specification.
  actually,we set each channel here.
*/
void subvol_main_vol()
{
	BYTE ch;
	for(ch = 1;ch<7;ch++)
	{
		volum_list[ch]=GET_ABSOLUTE_VALUE(ch);

		/*huziqin 2004-5-10 avoid volume turn to 255*/
		if(volum_list[ch]>(255-CH_VOL_MAX))
		{
			volum_list[ch] = 0;
			break;
		}	
		if(volum_list[0] == 0) //if main vol ==0,all channel set to zero
			subvol_channel_volume(ch,0);
			else
			subvol_channel_volume(ch,volum_list[ch]);
	}
}
#endif//#ifdef TAS_5508_PWM




/*
	global -- volum_list[]
*/
void subvol_vol_up()
{
    #ifndef TAS_5508_PWM
	BYTE ch;
    #endif//#ifndef TAS_5508_PWM
	
	if(current_channel == 0) //main vol
	{
		/*check if reach max,according to DOLBY's spec*/
        #ifdef TAS_5508_PWM
        if (volum_list[0]<MAIN_VOL_MAX)
            volum_list[0] ++;
        #else//#ifdef TAS_5508_PWM
        BYTE overflow =0;
		for(ch = 0;ch <7;ch ++)
		{
			if (volum_list[ch]>=(MAIN_VOL_MAX-1))
			{
                overflow=1;
    		}
		}
        if(overflow!=1)
    		volum_list[0] ++;
        #endif//#ifdef TAS_5508_PWM
    }	
	else//channel vol
	{
			
        #ifdef TAS_5508_PWM
		if((channel_vol_offset[current_channel-1])<CH_VOL_MAX)
			(channel_vol_offset[current_channel-1])++;
        #else//#ifdef TAS_5508_PWM
		if(volum_list[current_channel]>=(MAIN_VOL_MAX-1))
	    {
    		if((channel_vol_offset[current_channel-1])<CH_VOL_MAX)
    			(channel_vol_offset[current_channel-1])++;
	    }
        #endif//#ifdef TAS_5508_PWM
		volum_list[current_channel] = GET_ABSOLUTE_VALUE(current_channel);
	
	}
    #ifdef SUPPORT_VFD_MESSAGE
    set_vfd_message_state(VFD_MESSAGE_VOL,SUBVOL_TIME_OUT);
    #else
    subvol_time_out=SUBVOL_TIME_OUT;
    #endif
    volume_changed=1;
}



void subvol_vol_down()
{
	
	if(current_channel == 0) //main vol
	{
	
		if(volum_list[0]>0)
			volum_list[0] --;
	}
	else//channel vol
	{
		if(volum_list[current_channel]>0)
        {
    		if((channel_vol_offset[current_channel-1])>0)
    			(channel_vol_offset[current_channel-1])--;
    		volum_list[current_channel] =GET_ABSOLUTE_VALUE(current_channel);
	    }
	}
        
    #ifdef SUPPORT_VFD_MESSAGE
    set_vfd_message_state(VFD_MESSAGE_VOL,SUBVOL_TIME_OUT);
    #else
    subvol_time_out=SUBVOL_TIME_OUT;
    #endif
    volume_changed=1;
}

void polling_volume_change(void)
{
    #ifdef I2C_MASS_DATA_POLLING_WRITE
    if((volume_changed==1) && (NULL==p_i2c_mass_data))
    #else
    if(volume_changed==1)
    #endif
    {
        if(current_channel == 0) //main vol
        {
            subvol_main_vol();
            if(volum_list[0]>=MAIN_VOL_MAX)
            {
                psprintf(RegionValStr[REGION1], "VOLUME MAX");
            }
            else if (volum_list[0]<=0)
            {
                psprintf(RegionValStr[REGION1], "VOLUME MIN");
            }
            else
            {
                psprintf(RegionValStr[REGION1], "VOLUME %d",volum_list[0]);
            }
            PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);   
        }
        else//channel vol
        {
            subvol_channel_volume(current_channel, volum_list[current_channel]);
            show_channel_msg();
            PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);   
        }
        #ifdef SAVE_AMP_VOLUME
        save_amp_variable(current_channel);
        #endif
        #if defined(USE_AMP_MUTE)&&defined(CHANGE_VOL_DEMUTE) //chenzhao20050926
        user_amp_mute=0;
        #endif//#ifdef USE_AMP_MUTE
        volume_changed=0;
    }
}

#ifdef USE_AMP_MUTE
//Master Volume Mute
//mute all channels simultaneously
//mute   1: mute       0: demute
void sub_masterMute(BYTE mute)
{
    #ifdef SUPPORT_APOGEE_AMP
    ddx_masterMute(mute);
    #elif (defined(TAS_5508_PWM)||defined(TAS_5086_PWM))

    #if 1       
    if(mute==AMP_MUTE)
    {
        printf("tass5508 unmute  .......  \n");
        #ifdef TAS_5508_PWM
            #ifdef USE_TAS_5508_MUTE_REG
            tas_5508_mute(CH_MASTER_MUTE_MASK);
            #else
            tas_5508_software_mute();
            #endif
        #elif defined(TAS_5086_PWM)
        tas_5086_software_mute();
        #endif

        #ifndef MERGE_TEMP
        subvol_restore_line_out();
        #endif

        #ifdef TLV320_DAC          
        use_tlv320_mute_headphone();
        #endif
    }
    else
    { 
        {   
            printf("tass5508 unmute  .......  \n");
            #ifdef TLV320_DAC           
            mute_tlv320_line_out(0);    //unmute line out
            #endif

            #ifdef SUPPORT_AMP_IO_MUTE
            amp_io_demute();
            #endif
            
            #ifdef USE_TAS_5508_MUTE_REG
                tas_5508_mute(CH_MASTER_MUTE_MASK);
            #else
                subvol_main_vol();
                
                #ifndef MERGE_TEMP
                subvol_sub_vol();
                #endif
            
            #endif
            
            #ifndef MERGE_TEMP
            subvol_restore_line_out();
            #endif

            #ifdef SUPPORT_ACTIVE_SUBWOOFER
            active_subvol_sub_vol();
            #endif              
        }
    }   
    #else       
    if(mute==AMP_MUTE)
    tas_5508_mute(CH_MASTER_MUTE_MASK);
    else
    tas_5508_mute(0);
    #endif
    #endif
}
#endif
#ifdef SUPPORT_AMP_IO_MUTE//chenzhao20051205 for variable PWM processor.
inline void amp_io_mute(void)
{
    #ifdef ROM_BUS_EXTENT_IO
        #ifdef ORITRON_RECEIVER_6505
        rom_bus_set_io(ROM_BUS_OUT_AMP_MUTE,0);
        #else
        rom_bus_set_io(ROM_BUS_OUT_AMP_MUTE,1);
        #endif
    #endif
}
inline void amp_io_demute(void)
{
    #ifdef ROM_BUS_EXTENT_IO
        #ifdef ORITRON_RECEIVER_6505
        rom_bus_set_io(ROM_BUS_OUT_AMP_MUTE,1);
        #else
        rom_bus_set_io(ROM_BUS_OUT_AMP_MUTE,0);
        #endif
    #endif
}
#endif

#ifdef AMP_SUPPORT_EQ
const BYTE eq_str_id[EQ_MAX]={STR_OS_STANDARD,STR_OS_ROCK,STR_OS_POP,STR_OS_CLASSIC,STR_OS_JAZZ};
EQ_TYPE amp_eq=EQ_FLAT;
inline BYTE amp_set_eq(EQ_TYPE eq)
{
    #if defined(TAS_5508_PWM)
    return tas_5508_set_eq(eq);
    #elif defined(SUPPORT_DDX8001)
    ddx_Set_EQ(eq);
    return 1;
    #else
    #amp_should_support_eq
    #endif
}
void init_amp_eq(void)
{
    amp_eq=EQ_FLAT;
    amp_set_eq(amp_eq);
}
#ifdef I2C_MASS_DATA_POLLING_WRITE
void amp_toggle_EQ(void)
{
    if(action_click)
    {
        EQ_TYPE temp=amp_eq;
        amp_eq++;
        if(amp_eq>=EQ_MAX)
            amp_eq=EQ_FLAT;
        if(! amp_set_eq(amp_eq))
            amp_eq=temp;
    }
    PrintOsdMsg(eq_str_id[amp_eq], REGION1, 1, 0);
    #ifdef SUPPORT_VFD_SHOW_TONE
    set_vfd_message_state(VFD_MESSAGE_EQ,SUBVOL_TIME_OUT);
    #endif
    #ifdef TREBLE_BASS_EQ_MENU_INTERFACE
    amp_tone_mode = TONE_EQ;
    #endif

}
#else
void amp_toggle_EQ(void)
{
    //if(action_click)
    {
        #if defined(TAS_5508_PWM)
        EQ_TYPE amp_eq_last=amp_eq;
        if(amp_eq_last==EQ_FLAT)//to avoid pop noise when switch form flat to other.
            {
            sub_masterMute(AMP_MUTE);
            delay_srv_10ms(10);
            }
        #endif
        amp_eq++;
        if(amp_eq>=EQ_MAX)
            amp_eq=EQ_FLAT;
        amp_set_eq(amp_eq);
        #if defined(TAS_5508_PWM)
        if(amp_eq_last==EQ_FLAT)
            sub_masterMute(AMP_DEMUTE);
        #endif
    }
    PrintOsdMsg(eq_str_id[amp_eq], REGION1, 1, 0);
    #ifdef SUPPORT_VFD_SHOW_TONE
    set_vfd_message_state(VFD_MESSAGE_EQ,SUBVOL_TIME_OUT);
    #endif
    #ifdef TREBLE_BASS_EQ_MENU_INTERFACE
    amp_tone_mode = TONE_EQ;
    #endif
}
#endif//#ifdef I2C_MASS_DATA_POLLING_WRITE
#endif

#ifdef TREBLE_BASS_EQ_MENU_INTERFACE
void init_amp_tone_mode(void)
{
	amp_tone_mode = TONE_IDLE;
    current_channel=0;
}
void show_treble_bass_msg()
{
	if((channel_vol_offset[current_channel-1])==(CH_VOL_MAX/2))
	{
		psprintf(RegionValStr[REGION1],"%s 0",channel_str[current_channel-1]);
	}
	else if((channel_vol_offset[current_channel-1])<(CH_VOL_MAX/2))
	{
		psprintf(RegionValStr[REGION1],"%s -%d",channel_str[current_channel-1],(CH_VOL_MAX/2)-(channel_vol_offset[current_channel-1]));
	}
	else
	{
		psprintf(RegionValStr[REGION1],"%s +%d",channel_str[current_channel-1],(channel_vol_offset[current_channel-1])-(CH_VOL_MAX/2));
	}	
	PrintOsdMsg(STR_OS_SPACE, REGION1, 2, 1);
}
BYTE call_ir_func_tone_menu(BYTE rx)
{
    if(amp_tone_mode == TONE_IDLE)
        return 0;
	switch(rx)
	{
		case IRC_EQ: 	//TONE KEY
		{
			if(amp_tone_mode == TONE_EQ)
			{
                set_vfd_message_state(VFD_MESSAGE_EQ,SUBVOL_TIME_OUT);
			}
		}
		break;
		
		case IRC_SELECT:  //OK key
		{
			if(amp_tone_mode == TONE_EQ)
			{
                set_vfd_message_state(VFD_MESSAGE_EQ,SUBVOL_TIME_OUT);
				amp_tone_mode = TONE_BASS;
				current_channel = VOL_CH_BASS;  //for BASS Mode 
                show_channel_msg();
				//show_treble_bass_msg();
			}
		}
		break;
		
        #ifdef EXIT_KEY
		case IRC_EXIT: // setup/exit key
        #else
        case IRC_SETUP: // setup/exit key
		#endif
		{
			if(amp_tone_mode != TONE_EQ)
			{
				amp_tone_mode = TONE_EQ;
                PrintOsdMsg(eq_str_id[amp_eq], REGION1, 1, 0);
				return 1;
			}
		}
		break;
		
		case IRC_UP:
		{
			if(amp_tone_mode != TONE_EQ && amp_tone_mode != TONE_IDLE)
			{
                set_vfd_message_state(VFD_MESSAGE_EQ,SUBVOL_TIME_OUT);
				if(amp_tone_mode == TONE_TREBLE)
					current_channel = VOL_CH_TREBEL;
				else
					current_channel = VOL_CH_BASS;	
								
				//printf("joke: up key ,current_channel = %d ,vol= %d \n",current_channel,(channel_vol_offset[current_channel-1])); 
				if((channel_vol_offset[current_channel-1])<CH_VOL_MAX)
					(channel_vol_offset[current_channel-1])++;				

				volum_list[current_channel] = GET_ABSOLUTE_VALUE(current_channel);
                volume_changed=1;
				//subvol_channel_volume(current_channel, volum_list[current_channel]);
				//show_treble_bass_msg();
				//PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);	
//#ifdef SAVE_AMP_VOLUME
				//save_amp_variable(current_channel);
//#endif				
			}
		}		
		break;
		
		case  IRC_DOWN: 
		{
			if(amp_tone_mode != TONE_EQ && amp_tone_mode != TONE_IDLE)
			{
                set_vfd_message_state(VFD_MESSAGE_EQ,SUBVOL_TIME_OUT);
				if(amp_tone_mode == TONE_TREBLE)
					current_channel = VOL_CH_TREBEL;
				else
					current_channel = VOL_CH_BASS;	
				//printf("joke:1 down key ,current_channel = %d ,vol= %d \n",current_channel,(channel_vol_offset[current_channel-1])); 
					
				//if((channel_vol_offset[current_channel-1])==0)
				//	break;
					
				//printf("joke: down key ,current_channel = %d ,vol= %d \n",current_channel,(channel_vol_offset[current_channel-1])); 
				if((channel_vol_offset[current_channel-1])>0)
					(channel_vol_offset[current_channel-1])--;

                volum_list[current_channel] =GET_ABSOLUTE_VALUE(current_channel);
		
                volume_changed=1;
				//subvol_channel_volume(current_channel, volum_list[current_channel]);
				//show_treble_bass_msg();
				//PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);							
//#ifdef SAVE_AMP_VOLUME
				//save_amp_variable(current_channel);
//#endif				
			}
		}
		break;
		
		case IRC_LEFT:
		{
			if(amp_tone_mode!=TONE_EQ && amp_tone_mode != TONE_IDLE)
			{
                set_vfd_message_state(VFD_MESSAGE_EQ,SUBVOL_TIME_OUT);
				amp_tone_mode = amp_tone_mode - 1;
				if(amp_tone_mode<TONE_BASS)
				{
					current_channel = VOL_CH_TREBEL;  //for treble Mode 
					amp_tone_mode = TONE_TREBLE; 
				}
				else 
					current_channel = VOL_CH_BASS;  //for bass Mode 
                show_channel_msg();
			}				
		}
		break;
		
		case IRC_RIGHT:
		{	
			if(amp_tone_mode!=TONE_EQ && amp_tone_mode != TONE_IDLE)
			{
                set_vfd_message_state(VFD_MESSAGE_EQ,SUBVOL_TIME_OUT);
				amp_tone_mode = amp_tone_mode + 1;
				if(amp_tone_mode>=TONE_MAX)
				{
					current_channel = VOL_CH_BASS;  //for bass Mode 
					amp_tone_mode = TONE_BASS; 
				}
				else
					current_channel = VOL_CH_TREBEL;  //for treble Mode 
                show_channel_msg();
			}
		}
		break;		
	}
	if(amp_tone_mode == TONE_EQ || amp_tone_mode == TONE_IDLE)
		return 0;
	else 
		return 1;	
}
#endif//#ifdef OP_TREBLE_BASS_OPER_INTERFACE

void init_amp(void)
{
    
    #ifdef PT2258
        init_pt2258();
    #endif

    #ifdef TLV320_DAC //chenzhao20060118
        init_tlv320();
    #endif
    
    #ifdef TAS_5026_PWM
        init_tas_5026();
    #elif defined(TAS_5508_PWM)
        init_tas_5508();
    #elif defined(SUPPORT_APOGEE_AMP)
        //disable external amplifier
        ddx_disableEPAD();
        //mute all channels
        ddx_masterMute(1);
        ddx_initialization();
        ddx_masterMute(0);
        ddx_enableEPAD();
    #endif
    
    #ifdef DOLBY_AMP_VOLUME_CTRL
    init_subvol();
    #endif

    #ifdef AMP_SUPPORT_EQ
    init_amp_eq();
    #endif

    #ifdef SUPPORT_EX_BASS_FUNC//chenzhao20060117
    init_amp_exbass();
    #endif

}

#ifdef SUPPORT_AMP_HEADPHONE//chenzhao 20060116
extern inline int AUDIF_Set_OutputMode(UINT8 outmode, UINT16 outparam);
extern void rom_ext_select_headphone(void);
void amp_enable_headphone(void)
{
    if((cd_type_loaded==CDDVD)||(cd_subtype==CD_DTS))    
        AUDIF_Set_OutputMode(OUT_51DownmixL0R0,0);  //downmix 5.1ch to FL FR channel hongfeng 2005-08-01
#ifdef SUPPORT_APOGEE_AMP
    ddx_enable_headphone();
#endif

#ifdef TAS_5508_PWM 
    #ifdef USE_ROM_EXT_DET_HEADPHONE
        //rom_ext_select_headphone();
        tas_5508_enable_headphone();
    #endif  //USE_ROM_EXT_DET_HEADPHONE
#endif
}

void amp_disable_headphone(void)
{
    if((cd_type_loaded==CDDVD)||(cd_subtype==CD_DTS))    
        AUDIF_Set_OutputMode(OUT_51Channel,0);  //output 5.1ch hongfeng 2005-08-01
#ifdef SUPPORT_APOGEE_AMP
    ddx_disable_headphone();
#endif

#ifdef TAS_5508_PWM 
    #ifdef USE_ROM_EXT_DET_HEADPHONE
        //rom_ext_select_headphone();
        tas_5508_disable_headphone();
    #endif  //USE_ROM_EXT_DET_HEADPHONE
#endif

}
#endif//#ifdef SUPPORT_HEADPHONE

//--------------------------------------------------------
//For Speaker Test Mapping Speaker in Amplifer
// chenzhao 20060116
//--------------------------------------------------------
#ifdef SUPPORT_TESTSPK
inline void amp_testspk_ch(BYTE ch)
{
    #if defined(TAS_5508_PWM) || defined(TAS_5086_PWM)
	{
    	if(ch>=4)
        #ifdef TESTSPK_3CHANNEL    //for dav6008 2.1 channel use hongfeng modify 2005-10-24
        ch=ch-3;//kingslon add for 6008 pink noise
        #else
    	ch=ch+2;
        #endif
         
        #ifdef USE_TAS_5508_MUTE_REG
        tas_5508_mute((BYTE)(~(0x1<<ch))&0xcf);
        #else
            #if defined(TAS_5508_PWM)
            tas_5508_mute_inputmixer(ch);
            #elif defined(TAS_5086_PWM)
            tas_5086_mute_inputmixer(ch);
            #endif				
        #endif
    }
    #elif defined(SUPPORT_DDX8001)
    ddx_test_spk(ch);
    #endif
}
void amp_testspk_restore_ch(void)
{
    #ifdef TAS_5508_PWM
        init_tas_5508_input_mixer();
    #elif defined(TAS_5086_PWM)
        init_tas_5086_input_mixer();    
    #endif
}
#ifdef TESTSPK_CONTROL_VOL
void set_subvol_vol(BYTE channel,INT16 change)
{
    if((channel_vol_offset[channel]+change>=0)&&(channel_vol_offset[channel]+change<=CH_VOL_MAX))
        (channel_vol_offset[channel])+=change;
    volum_list[channel+1] =GET_ABSOLUTE_VALUE(channel+1);
    
    subvol_channel_volume(channel+1, volum_list[channel+1]);
    #ifdef SAVE_AMP_VOLUME
    save_amp_variable(channel+1);
    #endif
}
inline INT16 get_subvol_vol(BYTE channel)
{
    return (channel_vol_offset[channel]-CH_VOL_MAX/2);
}
#endif//#ifdef TESTSPK_CONTROL_VOL
#endif//#ifdef SUPPORT_TESTSPK
#ifdef SUPPORT_EX_BASS_FUNC//chenzhao 20060117
//================================================================
// subwoofer db  |	soft bass  |  balance bass |  powerful bass	 |	
//================================================================
// + 10	db		 |     --      |  	+04 db	   |   	 + 08 db	 | 
// + 09 db       |     --      |    +04 db     |     + 09 db     |
// + 08 db       |     --      |    +05 db     |     + 10 db     |
// + 07 db       |     --      |    +05 db     |	 + 11 db     |
// + 06 db       |     --      |    +06 db     |     + 12 db     |
// + 05 db       |     --      |    +06 db     |     + 13 db     |
// + 04 db       |     --      |    +07 db     |     + 14 db     |
// + 03 db       |     --      |    +07 db     |     + 15 db     |
// + 02 db       |     --      |    +08 db     |     + 16 db     |
// + 01 db       |     --      |    +08 db     |     + 17 db     |
//  00 ~ -10 db  |     --      |    +09 db     |     + 18 db     |
//================================================================
//comment: -- no change db 										 |
//================================================================

BYTE sub_volue_tab[10]={8,8,7,7,6,6,5,5,4,4};
EXBASS_TYPE amp_exbass_mode;
BYTE GetExBassVolume(void)
{
    BYTE sub_vloume=0,i;

    if(amp_exbass_mode == EXBASS_SOFT)
        sub_vloume = 0;  //0db
    else if(amp_exbass_mode == EXBASS_BALANCE)
    {
        if(GET_ABSOLUTE_VALUE(VOL_CH_SUB)<=MAIN_VOL_MAX)  //subwoofer 0 db
        {
            #ifdef ORITRON_RECEIVER_6008
            sub_vloume = 4;  //+9db
            #elif defined(ORITRON_RECEIVER_6505)
            sub_vloume = 9;  //+9db
            #else
            sub_vloume = 7;  //+9db
            #endif
        }
        else
        { 
            i = (GET_ABSOLUTE_VALUE(VOL_CH_SUB)-MAIN_VOL_MAX);
            if(i>=1 && i<=10)
            sub_vloume = sub_volue_tab[i-1];

            return sub_vloume; //+4db
        }
    }
    else if(amp_exbass_mode == EXBASS_POWERFUL)
    {
        if(GET_ABSOLUTE_VALUE(VOL_CH_SUB)<=MAIN_VOL_MAX)
        {
            #ifdef ORITRON_RECEIVER_6008
            sub_vloume = 8;  //+18db
            #elif defined(ORITRON_RECEIVER_6505)
            sub_vloume = 18;  //+18db
            #else
            sub_vloume = 14;  //+18db
            #endif
        }
        else 
        {
            #if defined(ORITRON_RECEIVER_6505)
            sub_vloume = (18 - (GET_ABSOLUTE_VALUE(VOL_CH_SUB)-MAIN_VOL_MAX));
            #else 
            sub_vloume = (14 - (GET_ABSOLUTE_VALUE(VOL_CH_SUB)-MAIN_VOL_MAX));
            #endif		
        }
    }
    //printf("GetExBassVolume %d,VOL_CH_SUB %d\n",sub_vloume,GET_ABSOLUTE_VALUE(VOL_CH_SUB));
    return sub_vloume;
}

#ifdef SAVE_EX_BASS_MODE//chenzhao20060220
void reset_amp_exbass(void)
{
    amp_exbass_mode = DEFAULT_EXBASS_MODE; //EXBASS_SOFT;
    BYTE data=(BYTE)amp_exbass_mode;
    WriteToI2c(I2C_ID_MEMORY, ADDR_EX_BASS_MODE,&data, 1);
}
#endif
void init_amp_exbass(void)
{
    #ifdef SAVE_EX_BASS_MODE//chenzhao20060220
    BYTE data;
    if(ReadFromI2c(I2C_ID_MEMORY, ADDR_EX_BASS_MODE,&data, 1)>0)
        amp_exbass_mode = data;
    else
        reset_amp_exbass();
    #else
	amp_exbass_mode = EXBASS_SOFT;
    #endif
	subvol_channel_volume(VOL_CH_SUB, volum_list[VOL_CH_SUB]);
}
#if defined(SUPPORT_TWO_MODE_EXBASS) //hongfeng add 2005-10-24
const char *amp_exbass_str[EXBASS_MAX]={"BASS ON","","BASS OFF",};
#elif defined(SUPPORT_THERE_MODE_EXBASS)
char *amp_exbass_str[EXBASS_MAX]={"SOFT BASS","BALANCE BASS","POWERFUL BASS",};
#else
    #error should select a exbass mode.
#endif
void amp_toggle_ExBass(void)
{
    if(action_click)
    #ifdef I2C_MASS_DATA_POLLING_WRITE
    if(NULL == p_i2c_mass_data)
    #endif
    {
        #if defined(SUPPORT_TWO_MODE_EXBASS) //hongfeng add 2005-10-24
        if(EXBASS_SOFT==amp_exbass_mode)
            amp_exbass_mode = EXBASS_POWERFUL;
        else
            amp_exbass_mode = EXBASS_SOFT;
#elif defined(SUPPORT_THERE_MODE_EXBASS)
        amp_exbass_mode ++;
        if(amp_exbass_mode>=EXBASS_MAX)
            amp_exbass_mode = EXBASS_SOFT;
        #else
            #error should select a exbass mode.
        #endif

        subvol_channel_volume(VOL_CH_SUB, volum_list[VOL_CH_SUB]);
        #ifdef AUDIO_EFFECT_MUTE
        set_audio_effect_mute_time(AUDIO_EFFECT_MUTE_TIME);
        sub_masterMute(AMP_MUTE);		
        #endif
        #ifdef SAVE_EX_BASS_MODE//chenzhao20060220
        BYTE data=(BYTE)amp_exbass_mode;
        WriteToI2c(I2C_ID_MEMORY, ADDR_EX_BASS_MODE,&data, 1);
        #endif
    }
    
	show_exbass_msg();
    #ifdef SUPPORT_VFD_SHOW_EXBASS	
    set_vfd_message_state(VFD_MESSAGE_EXBASS,SUBVOL_TIME_OUT);
    #endif
	
}		
		
void show_exbass_msg(void)
{
	psprintf(RegionValStr[REGION1], amp_exbass_str[amp_exbass_mode]);
    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);	   
}

#endif
//******************************************************
//wuzhj 2004/12/10
//for Radio new UI vol control
// Radio_vol_up();Radio_vol_down();Radio_main_vol()
//******************************************************
#ifdef SUPPORT_Radio_NEW_UI  //wuzhj  2004/12/10   
void Radio_vol_up()
{
	BYTE ch;
	
	if(current_channel == 0) //main vol
	{
		/*check if reach max,according to DOLBY's spec*/
		for(ch = 0;ch <7;ch ++)
		{
			if (volum_list[ch]>=(MAIN_VOL_MAX-1))
			{
				return;
			}
		}
		volum_list[0] ++;
		subvol_main_vol();

		psprintf(RegionValStr[REGION1], " MAIN %d",volum_list[0]);
        //PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        //osd_DrawString(18+8, 2-2, RegionValStr[REGION1], 2, 11);

}	
	else//channel vol
	{
		subvol_time_out = SUBVOL_TIME_OUT;
		volum_list[current_channel] = GET_ABSOLUTE_VALUE(current_channel);
			
		if(volum_list[current_channel]>=(MAIN_VOL_MAX-1))
		{
        return;
			}
		if((channel_vol_offset[current_channel-1])<CH_VOL_MAX)
			(channel_vol_offset[current_channel-1])++;
		subvol_channel_volume(current_channel, volum_list[current_channel]);
		show_channel_msg();
		//PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);	
	
	}
#ifdef SAVE_AMP_VOLUME
	save_amp_variable(current_channel);
#endif

}

void Radio_vol_down()
{
	
	if(current_channel == 0) //main vol
	{
	
		if(volum_list[0]>0)
			volum_list[0] --;
		subvol_main_vol();

		psprintf(RegionValStr[REGION1], " MAIN %d",volum_list[0]);
		//PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);	
		
	}
	else//channel vol
	{
		subvol_time_out = SUBVOL_TIME_OUT;
		volum_list[current_channel] =GET_ABSOLUTE_VALUE(current_channel);
			
		if(volum_list[current_channel]==0)
		{
        return;
			}
		if((channel_vol_offset[current_channel-1])>0)
			(channel_vol_offset[current_channel-1])--;

		subvol_channel_volume(current_channel, volum_list[current_channel]);
		show_channel_msg();
		PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);	
	
	}
#ifdef SAVE_AMP_VOLUME
	save_amp_variable(current_channel);
#endif

}

void Radio_main_vol()
{
	BYTE ch;
	for(ch = 1;ch<7;ch++)
	{
		volum_list[ch]=GET_ABSOLUTE_VALUE(ch);

		//huziqin 2004-5-10 avoid volume turn to 255
		if(volum_list[ch]>(255-CH_VOL_MAX))
		{
			volum_list[ch] = 0;
			break;
		}	
		if(volum_list[0] == 0) //if main vol ==0,all channel set to zero
			subvol_channel_volume(ch,0);
			else
			subvol_channel_volume(ch,volum_list[ch]);
	}
    psprintf(RegionValStr[REGION1], " MAIN %d",volum_list[0]);
}

#endif//#ifdef SUPPORT_Radio_NEW_UI  //wuzhj  2004/12/10   
#endif //defined(TDA7448)||defined(PT2258)
