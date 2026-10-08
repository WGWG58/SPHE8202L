#include "user_init.h"
#include "osd.h"

BYTE  subvol_time_out = 0 ;
BYTE current_channel = 0;

#if  defined(TDA7448)
#include "tda7448.c"
#endif

#if  defined(PT2258)
#include "pt2258.c"
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
#endif
}
#endif

#if  defined(TDA7448)||defined(PT2258)||defined(DOLBY_AMP_VOLUME_CTRL)

#ifdef DOLBY_AMP_VOLUME_CTRL
#ifdef  TAS_5026_PWM
char *channel_str[6]={"FRONT L","FRONT R","SURROUND L","SURROUND R","CENTER","LFE",};
#else
char *channel_str[6]={"LFE","SURROUND R","SURROUND L","CENTER","FRONT R","FRONT L"};
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
*/
BYTE volum_list[7];
BYTE channel_vol_offset[6] = {CH1_VOL,CH2_VOL,CH3_VOL,CH4_VOL,CH5_VOL,CH6_VOL};

#define  GET_ABSOLUTE_VALUE(channel)     (volum_list[0]+channel_vol_offset[channel-1]-(CH_VOL_MAX/2))

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

#define  AMPLIFIER_START  228
extern BYTE ddx_Bass_lev;
extern BYTE ddx_Treble_lev;



void save_amp_variable(BYTE ch)
{
	BYTE data;
#ifdef  SUPPORT_APOGEE_AMP	
	data = ddx_Treble_lev;
	WriteToI2c(I2C_ID_MEMORY, AMPLIFIER_START+8,&data, 1);
#endif
	if(ch==0)
	{

	}
	else if ((ch > 0)&&(ch<7))
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
	for(ch = 1;ch<7;ch++)
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

#ifdef PT2258
	init_pt2258();
#endif

#ifdef TAS_5026_PWM
	init_tas_5026();
#endif

	volum_list[0] = MAIN_VOL;
#ifdef SAVE_AMP_VOLUME
	load_amp_variable();
#endif	
	for(ch = 1;ch<7;ch++)
	{
		volum_list[ch] = GET_ABSOLUTE_VALUE(ch);
		subvol_channel_volume(ch,volum_list[ch]);
	}
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
#define SUBVOL_TIME_OUT  8 //decrease in 500ms polling

void subvol_next_channel()
{
	if(current_channel == 6)
		current_channel = 0;
	else
		current_channel ++;

	if(current_channel == 0)
		psprintf(RegionValStr[REGION1], "MAIN");
	else
		{
		subvol_time_out = SUBVOL_TIME_OUT;
		psprintf(RegionValStr[REGION1], "%s",channel_str[current_channel-1]);
		}
 	PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);	
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

void polling_channel_timeout()
{
	if(subvol_time_out>0)
	{
		subvol_time_out--;
		if(current_channel > 0)
		{
			show_channel_msg();
			
		}
	}
	else
	{
		current_channel = 0;
	}
}


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




/*
	global -- volum_list[]
*/
void subvol_vol_up()
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

		psprintf(RegionValStr[REGION1], "MAIN %d",volum_list[0]);
		PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);	
		
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
		PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);	
	
	}
#ifdef SAVE_AMP_VOLUME
	save_amp_variable(current_channel);
#endif

}



void subvol_vol_down()
{
	
	if(current_channel == 0) //main vol
		{
	
		if(volum_list[0]>0)
			volum_list[0] --;
		subvol_main_vol();

		psprintf(RegionValStr[REGION1], "MAIN %d",volum_list[0]);
		PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);	
		
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


#endif//defined(TDA7448)||defined(PT2258)

#ifdef DOLBY_AMP_VOLUME_CTRL
void  ircmd_set_treble()
{
#ifdef SUPPORT_APOGEE_AMP
//	 ddx_OSDTrebleAdjust();
#endif
}
void  ircmd_set_bass()
{
#ifdef SUPPORT_APOGEE_AMP
//    ddx_OSDBassAdjust();
#endif
}
#endif


#ifdef  NO_INTERNAL_VOLUME_CTRL
void  ircmd_volume_up(void)
{
#if defined(SUPPORT_BASS_TREBLE)//xyy 2004-3-8
 //xulf 2004-01-12
 #ifdef SUPPORT_APOGEE_AMP
	if(flag_BassAdjust)
	{	
		ddx_ircmd_BassAdjust(1);
		return;
	}
	if(flag_TrebleAdjust)
	{	
		ddx_ircmd_TrebleAdjust(1);
		return;
	}	
#endif	
#endif


	subvol_vol_up();
	/*tell vfd to show volume*/
	subvol_time_out = 10;

}

void  ircmd_volume_down(void)
{

#if defined(SUPPORT_BASS_TREBLE)//xyy 2004-3-8
 //xulf 2004-01-12
 #ifdef SUPPORT_APOGEE_AMP
	if(flag_BassAdjust)
	{
		ddx_ircmd_BassAdjust(-1);

		return;
	}
	if(flag_TrebleAdjust)
	{	
		ddx_ircmd_TrebleAdjust(-1);
		
		return;
	}
#endif	
#endif

	subvol_vol_down();

	/*tell vfd to show volume*/
	subvol_time_out = 10;
	
}

#endif  //NO_INTERNAL_VOLUME_CTRL

