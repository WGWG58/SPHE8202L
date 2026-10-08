#include "user_init.h"
#include "global.h"
#include "polling.h"

#include "assert.h"
#include "fdisc_gpio.h"
#include "fdisc_tray.h"
//#include "lc72131.h" chenzhao mark it.20060110
#include "drv.h"
#include "osd.h"
#include "vfdfunc.h"
#include "e2prom_map.h"
#include "func.h"
#include "setup_VA.h"
#include "cd.h"

#ifdef OPEN_OR_CLOSE_ERROR_TO_POWER_OFF
	#define	TRAY_ERROR_POWER_OFF_TIME		20		//10 s
	BYTE power_off_flag;
	BYTE power_off_time;
	BYTE tray_error_power_off;
#endif
BYTE hand_sense_flag =2;//chenzhao 20060110 .0:normal,1:waiting,2:power on
int hand_sense_delay;
const unsigned char step_pos_num[MAX_5DISC_STEP] ={STEP_1_POS,STEP_2_POS,STEP_3_POS,STEP_4_POS,STEP_5_POS,STEP_6_POS};
const unsigned char middle_pos_num[MAX_5DISC_STEP]={START_POS,MIDDLE_62_POS,MIDDLE_23_POS,MIDDLE_34_POS,MIDDLE_45_POS,MIDDLE_16_POS};

const unsigned char discN_stepN[5]={STEP_5_POS,STEP_4_POS,STEP_3_POS,STEP_2_POS,STEP_1_POS};

const unsigned char Run_Forward[MAX_5DISC_STEP][13]={
	{START_POS,0,0,0,0,0,0,0,0,0,0,0,0,},																			//step 1
	{START_POS,STEP_1_POS,MIDDLE_16_POS,STEP_6_POS,MIDDLE_62_POS,0,0,0,0,0,0,0,0,},									//step 2
	{START_POS,STEP_1_POS,MIDDLE_16_POS,STEP_6_POS,MIDDLE_62_POS,STEP_2_POS,MIDDLE_23_POS,0,0,0,0,0,0,},			//step 3
	{START_POS,STEP_1_POS,MIDDLE_16_POS,STEP_6_POS,MIDDLE_62_POS,STEP_2_POS,MIDDLE_23_POS,STEP_3_POS,MIDDLE_34_POS,0,0,0,0,},//step 4
	{START_POS,STEP_1_POS,MIDDLE_16_POS,STEP_6_POS,MIDDLE_62_POS,STEP_2_POS,MIDDLE_23_POS,STEP_3_POS,MIDDLE_34_POS,STEP_4_POS,MIDDLE_45_POS,0,0,},//step 5
	{START_POS,STEP_1_POS,MIDDLE_16_POS,0,0,0,0,0,0,0,0,0,0,},			//step 6
};
const int  DM_GSS_UNKNOWN					= 0x00;		// Slot status unknown
const int  DM_GSS_DISC_PRESENT				= 0x01;		// Disc present in slot    (has disc)
const int  DM_GSS_DISC_NOT_PRESENT			= 0x02;		// Disc not preset in slot (no disc)

unsigned char aim_photo_tab[7]={0,6,5,4,3,2,1};
unsigned char eject_step_aim_photo_tab[5] = {0,STEP6_C_ALL_EJECT,STEP6_B_ALL_EJECT,STEP6_A_ALL_EJECT,STEP6_ALL_LOCK};
unsigned char slotStatus[5];
unsigned char c_is_all_eject_flag;
unsigned char check_jump_disc =0;
unsigned char led_on_flag;
unsigned char exchange;
int 		  hand_sense_counter = 0;
//-------------------------------------------------
//for exchange value
//-------------------------------------------------
STEP_TYPE step_Number;
BYTE 	  substep_Number;
BYTE	  aimphoto_Number;
BYTE 	  photocounter_flag;
BYTE      counter_photo;
BYTE      runForward;
BYTE 	  middle_stepNumber;
STEP_RUN  step_operate=STEP_RUN_IDLE;
//-------------------------------------------------
WAIT_CLOSE waiting_close=WAITCLOSE_IDLE;
WAIT_EJECT waiting_eject=WAITEJECT_IDLE;
EXCHANGE_TYPE exchang_type = EXCHANGE_IDLE;
//-------------------------------------------------

FDISC_TRAY_TYPE 	fdisc_tray 		= FDISC_TRAY_FINISH;
MOTOR_STATUS		motor_status	= MOTOR_STOP;
FLUNGER_STATUS		flunger_status	= PLUNGER_OFF;	
OPER_MODE 			set_oper_mode	= OPER_DISC_IDLE;


//---------------------------------------------------------------------------------------------------------
//	5 Disc Load Control.
//		Name: TOKYO PIGEON CO. LTD.	
//		
//	
//
//																			create by opv-joke  2005/10/4
//---------------------------------------------------------------------------------------------------------
extern void ircmd_trayout(void);
extern void ircmd_play(void);
extern void invalid_key(void);


extern UINT8 cIDEStatus;
extern UINT8   polling_avoid_reentry;
unsigned char disNumber;
int fdisc_tray_time_out;
//int tt_counter=0;
unsigned char detect_disc_delay_flag;
unsigned char detect_disc_delay_time;
int disc_detect_time;
unsigned char start_counter_flag;


unsigned char fdisc_tray_time_out_flag;
unsigned char fdisc_tray_timout_over_flag;

BYTE delay_run_mm_flag;
BYTE run_mm_flag=0;     //0: run mm 1:stop mm
BYTE runmm_flag;

#ifndef DVDRELEASE
	#define	FDISC_TRAY_DB	
#endif

#define TRAY_TIMEOUT_DB
#define	TRAY_DB
#define  NOP  delay_1us(10)

#ifndef FDISC_TRAY_DB
	#undef printf
	#undef print_block
	#define printf(f, a...) do {} while (0)
	#define print_block(x,y) do {} while (0)
#endif

//===================================================================================================
#ifdef OPEN_OR_CLOSE_ERROR_TO_POWER_OFF
void set_tray_error_poweroff_time(BYTE time)
{
	power_off_flag = 0;
	if(time)
		power_off_flag = 1;

	power_off_time = time;
}
void tray_error_auto_power_off_polling_500ms(void)
{
	if(power_off_flag)
	{
		if(power_off_time<=0)
		{
			power_off_flag = 0;
			tray_error_power_off = 1;
			ircmd_power();
		}
		else
			power_off_time=power_off_time - 1;
	}
}
#endif 

//===================================================================================================
//interrupter counter time
//
//					-by joke 
//===================================================================================================
static UINT16 cTS,cTE;
// how to calculate time(ms): TIME = ( time * 2 ) ms
// time unit 2ms
//
void Set_control_timer(UINT16 time)
{
    cTS=NewRTC;
    cTE=time;
    if(0xffff-cTE>=cTS)
        cTE+=cTS;
    else
        cTE-=(0xffff-cTS)+1;

    if(time)    
		detect_disc_delay_flag = 1;
	else	
		detect_disc_delay_flag = 0;
	detect_disc_delay_time = 0;	    	        
}
inline BYTE check_control_timer(void)
{
	return (((cTE>=cTS)&&(NewRTC>=cTE||NewRTC<cTS)) || ((cTE<cTS)&&(NewRTC>=cTE&&NewRTC<cTS)));
}

void control_timer_polling(void)
{
    if(check_control_timer())
    {
    	if(delay_run_mm_flag==1)
    	{
    		if(run_mm_flag)
    		{
    			set_tray_stop();	
    			Set_control_timer(3); //delay 6ms
    			run_mm_flag = 0;
    		}
    		else
    		{
				//set_mm_run(!runForward); //runmm_flag
				set_mm_run(runmm_flag); //runmm_flag
    			Set_control_timer(5); //delay 10ms
    			run_mm_flag = 1;
			}
    	}
    	
		if(detect_disc_delay_flag)
			detect_disc_delay_time = 1;
		
		if(start_counter_flag)
		{	
			if(DETECT_DISC())
				disc_detect_time ++;				
		}
    }
}

//===================================================================================================

void set_5disc_tray_timeout_time(int set)
{
	fdisc_tray_time_out_flag = set;
	fdisc_tray_time_out = set;
	fdisc_tray_timout_over_flag = 0; 

#ifdef TRAY_TIMEOUT_DB
	printf("5disc: set tray timeout time = %d   \n",set);
#endif
		
}

unsigned char get_5disc_tray_timeout_end(void)
{
	return fdisc_tray_timout_over_flag;
}

void polling_fdisc_tray_timeout_time(void)
{
	if(fdisc_tray_time_out_flag)	
	{
#ifdef TRAY_TIMEOUT_DB
		//printf("5disc: fdisc tray time out !!!!fdisc_tray_time_out= %d   \n",fdisc_tray_time_out);
#endif								
		if(!fdisc_tray_time_out)
		{
#ifdef TRAY_TIMEOUT_DB
			printf("5disc: fdisc tray time out !!!!............   \n");
#endif						
			fdisc_tray_time_out_flag=0;
			fdisc_tray_timout_over_flag = 1;
		}
		else
			--fdisc_tray_time_out;
	}
}


void delay_5disc_1ms(void)
{
	int i;
	
	for(i=0;i<=100;i++) //1ms
	{
		NOP;	//1us	
	}
}

void delay_5disc_ms(int mstime)
{
	int loop;
	
	loop = mstime;
	
	while(loop)
	{
		delay_5disc_1ms();
		loop =loop- 1;
	}
}
unsigned char is_tray_out(void)
{
	if(DET_SW8())
		delay_5disc_ms(10);//delay 10ms

	return DET_SW8();	
}

unsigned char is_play_position(void)
{
	
	//printf("5disc<is_play_position>:DET_SW7()= %d  , DET_SW5()= %d    \n",DET_SW7(),DET_SW5());
	
	if(DET_SW7() && !DET_SW5())
		return 0;
	return 1;	
}

unsigned char is_tray_middle(void)
{
	//if(is_tray_out())
	//	return 0;	
		
	if(get_5disc_sw7_status() && (get_5disc_sw5_status()==0))	
		return 1;
	return 0;	
}
BYTE test_5disc_tray(void)
{
	if(DET_SW1() && DET_SW2() && DET_SW3() && DET_SW4() && DET_SW5() && DET_SW6() && DET_SW7() && DET_SW8())
	{
		//no 5disc tray
		return 1;
	}
	return 0;
}

void set_tray_in(void)
{
	set_5disc_control_1(0);
	set_5disc_control_2(1);					
}
void set_loader_up(void)
{
	set_5disc_control_1(0);
	set_5disc_control_2(1);					
}
void set_tray_out_from_load_to_middle(void)
{
	set_5disc_control_1(0);
	set_5disc_control_2(1);					
}

void set_tray_out(void)
{
	set_5disc_control_1(1);
	set_5disc_control_2(0);					
}
void set_loader_down(void)
{
	set_5disc_control_1(1);
	set_5disc_control_2(0);					
}
void set_tray_in_from_middle_to_loader(void)
{
	set_5disc_control_1(1);
	set_5disc_control_2(0);					
}
void set_mm_run(unsigned char run_forward)
{
	if(run_forward)
	{
		//set below status for tray in/loader up in loader position,or from loader position to middle position move
		set_5disc_control_1(0);
		set_5disc_control_2(1);					
	}
	else
	{
		//set below status for tray out/loader down in loader position,or from middle position to loader position move 
		set_5disc_control_1(1);
		set_5disc_control_2(0);					
	}
}
void set_tray_stop(void)
{
	set_5disc_control_1(0);
	set_5disc_control_2(0);					
}		
//when tray move from out to in  
//					  -----------------
//					 | 	
//	SW5			_____|
//
//
//when tray move from in to out 
//		______
//	SW5		  |
//			  |
//			  ----------------------
//
unsigned char get_step_pos_number(STEP_TYPE step_type)
{
	return step_pos_num[step_type-1];
}

unsigned char get_middle_pos_for_step_left_border(STEP_TYPE step_type)
{
	return middle_pos_num[step_type-1];
}

//===========================================================================================
// forware:  start <--> step1 <--> step6 <--> step2 <--> step3 <--> step4 <--> step5 <--> end 
//	
//	current step for step6. if you need find step3,the run forware is 1.
//
unsigned char is_run_forward(STEP_TYPE step_type)
{
	unsigned char curr_pos,i;
		
	curr_pos = SETP_POS();
	
	for(i=0;i<13;i++){
		
		if(curr_pos == Run_Forward[step_type-1][i])
			return 1;
	}
	return 0;		
}

void error_stop(void)
{
	set_tray_stop();
	set_5disc_plunger_status(0);	
	set_5disc_tray_timeout_time(0);
	fdisc_tray = FDISC_TRAY_FINISH;
}
//=======================================================================================
//	kernel of software. 
//	OUTPUT: 	0:  true
//				1:  error (time out over!)
//
//
//=======================================================================================
BYTE set_step_positon(STEP_TYPE set_step_type,unsigned char sub_step_fun)
{
	unsigned char counter_flag,middle_pos;
	unsigned char photo_counter,aim_photo;
	unsigned char run_forward;
	
	set_5disc_tray_timeout_time(24); //set time out : 12s
	
	set_tray_stop();
	set_5disc_plunger_status(1);

	//delay_5disc_ms(80);	//delay 20ms
	
	run_forward = 0;
	aim_photo 	=sub_step_fun;
	counter_flag = 0;
	photo_counter = 0;

#ifdef TRAY_DB	
	if(is_run_forward(set_step_type))
		printf("5disc:  is run forward 1  . SETP_POS()= %x !!!!!!!!!!! \n",SETP_POS());
	else		
		printf("5disc:  is run forward 0  . SETP_POS()= %x !!!!!!!!!!! \n",SETP_POS());
	
	printf("5disc: DET_PHOTO()= %d   \n",DET_PHOTO());	
#endif
	
	if(SETP_POS()==get_step_pos_number(set_step_type))
	{
//#ifdef TRAY_DB			
		printf("5disc: as same step type SETP_POS()= %x !!!!!!!!  \n",SETP_POS());
//#endif		
		middle_pos = get_middle_pos_for_step_left_border(set_step_type);	
		
		set_mm_run(0);
	#if 0	
		delay_5disc_ms(24); //delay 24ms
	#endif
		while(1){

			polling_avoid_reentry=0;
			polling();				
			
			if(SETP_POS()==middle_pos && DET_PHOTO())
			{
#ifdef TRAY_DB					
				printf("1.5disc:SETP_POS()= %x ,middle_pos= %x ,DET_PHOTO()=%d \n",SETP_POS(),middle_pos,DET_PHOTO());  				
#endif			
			#if 0
				set_mm_run(1);
				delay_5disc_ms(5); //delay 10ms	
				set_tray_stop();
				delay_5disc_ms(10);
			#else
				set_tray_stop();
			#endif	
#ifdef TRAY_DB					
				printf("2.5disc:SETP_POS()= %x ,middle_pos= %x ,DET_PHOTO()= %d \n",SETP_POS(),middle_pos,DET_PHOTO());  				
#endif				
				if(SETP_POS()==middle_pos && DET_PHOTO())
					break;
			}
			
			if(get_5disc_tray_timeout_end())
			{
				printf("5disc<set_step_positon>:  same step time out !!!!!!!!!!!!!! \n");
				error_stop();
				return 1;
			}
		}
	}
	
	if(is_run_forward(set_step_type))
		run_forward = 1;
	else
	{
		if(set_step_type==TYPE_STEP_6)
			aim_photo = eject_step_aim_photo_tab[sub_step_fun];
		else 
			aim_photo = aim_photo_tab[sub_step_fun];
	}
	
#ifdef TRAY_DB		
	printf("5disc: 	aim_photo= %d ,SETP_POS()= %x  ,run_forward= %d \n",aim_photo,SETP_POS(),run_forward);	
	printf("5disc: DET_PHOTO() = %d  \n",DET_PHOTO());
#endif
		
	//2005/11/30 fixed a bug, disc number 1, from open to close ,tray can't close to tray postion. bug#322	
	set_mm_run(!run_forward);	
	delay_5disc_ms(10); 
	
	set_mm_run(run_forward);	
	
	while(1)
	{
		polling_avoid_reentry=0;
		polling();					

		if(SETP_POS()==get_step_pos_number(set_step_type))
		{
			//waiting photo from low to high
			while(!DET_PHOTO())
			{
				polling_avoid_reentry=0;
				polling();	
				counter_flag = 1;	
				if(get_5disc_tray_timeout_end())
				{
					printf("5disc<set_step_positon>: photo still low time out !!!!!!!!!!!!!! \n");
					error_stop();
					return 1;
				}									
			}
			if(counter_flag)
			{
				counter_flag  = 0;
				photo_counter = photo_counter + 1;
			}
		}
		
		if((SETP_POS()==get_step_pos_number(set_step_type)) && (photo_counter==aim_photo))
			break;

		if(get_5disc_tray_timeout_end())
		{
			printf("5disc:SETP_POS()= %x,photo_counter=%d , get_step_pos_number(set_step_type)= %d \n",SETP_POS(),photo_counter,get_step_pos_number(set_step_type));
			printf("5disc<set_step_positon>: counter photo != aim photo time out !!!!!!!!!!!!!! \n");
			error_stop();
			return 1;
		}			
	}

#if 0	
	set_mm_run(!run_forward);
	delay_5disc_ms(24); //delay 24ms	
	set_tray_stop();	
	delay_5disc_ms(10); //delay 10ms	
#endif

	//waiting photo from high to low
	do{
		polling_avoid_reentry=0;
		polling();					

		set_mm_run(!run_forward);
		delay_5disc_ms(6); //delay 5ms	
		set_tray_stop();	
		delay_5disc_ms(10); //delay 10ms	

		if(get_5disc_tray_timeout_end())
		{
			printf("1. 5disc<set_step_positon>: photo still high time out !!!!!!!!!!!!!! \n");
			error_stop();
			return 1;
		}		
	}while(DET_PHOTO());
	
	//waiting photo from low to high	
	do{
		polling_avoid_reentry=0;
		polling();					

		set_mm_run(!run_forward);
		delay_5disc_ms(6); //delay 5ms	
		set_tray_stop();	
		delay_5disc_ms(10); //delay 10ms	

		if(get_5disc_tray_timeout_end())
		{
			printf("5disc<set_step_positon>: photo still low time out !!!!!!!!!!!!!! \n");
			error_stop();
			return 1;
		}

	}while(!DET_PHOTO());

	//waiting photo from high to low
	do{
		polling_avoid_reentry=0;
		polling();					

		set_mm_run(run_forward);
		delay_5disc_ms(6); //delay 5ms	
		set_tray_stop();	
		delay_5disc_ms(10); //delay 10ms	

		if(get_5disc_tray_timeout_end())
		{
			printf("2. 5disc<set_step_positon>: photo still high time out !!!!!!!!!!!!!! \n");
			error_stop();
			return 1;
		}

	}while(DET_PHOTO());

	set_5disc_tray_timeout_time(0);

	set_mm_run(!run_forward);
	delay_5disc_ms(10); //delay 10ms		
	set_tray_stop();	
#if 0	
	delay_5disc_ms(200); //delay 10ms			
	set_5disc_plunger_status(0);		
	delay_5disc_ms(200); //delay 10ms			
	set_mm_run(!run_forward);
	delay_5disc_ms(5); //delay 5ms		
	set_tray_stop();
#else
	set_5disc_plunger_status(0);		
#endif
		
#ifdef TRAY_DB				
	printf("5disc<set_step_positon>: !!!!!! set step position over !!!!!!!!!!!!!!! \n");	
#endif
	
	return 0;	
}
#ifdef SUPPORT_5DISC_TRAY_SAVE_FUNC
void set_5disc_tray_default(void)
{
	//tray_slot
	//bit 0, bit 1 :  0x00 -> unknown disc  0x01 -> no disc , 0x02 -> DISC_PRESENT for disN 1
	//bit 2, bit 3 :  0x00 -> unknown disc  0x01 -> no disc , 0x02 -> DISC_PRESENT for disN 2
	//bit 4, bit 5 :  0x00 -> unknown disc  0x01 -> no disc , 0x02 -> DISC_PRESENT for disN 3
	//bit 6, bit 7 :  0x00 -> unknown disc  0x01 -> no disc , 0x02 -> DISC_PRESENT for disN 4
	//disN
	//bit 0 ~ bit 3:  current disc Number 
	//bit 4, bit 5 :  0x00 -> unknown disc  0x01 -> no disc , 0x02 -> DISC_PRESENT for disN 5
	BYTE tray_slot;
	BYTE disN;
	
	disNumber = 1;
	init_5disc_driver();
		
	tray_slot = ((slotStatus[0]) |	(slotStatus[1]<<2) | (slotStatus[2])<<4 | (slotStatus[3])<<6);	
	WriteToI2c(0xa0, ADDR_5DISC_TRAY_STATE,&tray_slot, 1);	
	
	disN =  (disNumber & 0x0f) | ((slotStatus[4]<<4));
	WriteToI2c(0xa0, ADDR_5DISC_CURR_DisN,&disN, 1);	
}

void save_5disc_tray(void)
{
	BYTE tray_slot;
	BYTE disN;
	
	tray_slot = ((slotStatus[0]) |	(slotStatus[1]<<2) | (slotStatus[2])<<4 | (slotStatus[3])<<6);	
	
	//printf("5disc<save_5disc_tray>:  tray_slot = %x  \n",tray_slot);
	
	WriteToI2c(0xa0, ADDR_5DISC_TRAY_STATE,&tray_slot, 1);	
	
	disN =  (disNumber & 0x0f) | ((slotStatus[4]<<4));
	//printf("5disc<save_5disc_tray>:  disN = %x  \n",disN);
	WriteToI2c(0xa0, ADDR_5DISC_CURR_DisN,&disN, 1);	
	
}
void load_5disc_tray_data(void)
{
	BYTE tray_slot;
	BYTE disN,i;
	
	ReadFromI2c(0xa0, ADDR_5DISC_TRAY_STATE,&tray_slot, 1); 
	slotStatus[0] = (tray_slot & 0x03);
	slotStatus[1] = (tray_slot & 0x0c)>>2;
	slotStatus[2] = (tray_slot & 0x30)>>4;
	slotStatus[3] = (tray_slot & 0xc0)>>6;
		
	ReadFromI2c(0xa0, ADDR_5DISC_CURR_DisN,&disN, 1); 
	disNumber = (disN & 0x0f);
	slotStatus[4] = (disN & 0x30)>>4;
	
	//printf("5disc:  &&&&&&&&&&&&&&&&&&& disNumber = %d  \n",disNumber);
	//for(i=0;i<5;i++)
	//	printf("5disc: slotStatus[%d]= %d ,disNumber= %d \n",i,slotStatus[i],disNumber);
	
	if(disNumber<1 && disNumber>5)
	{
		disNumber = 1;
	}
}
#endif

//when power on,init 5disc tray 
int init_5disc_tray(void)
{
	if(test_5disc_tray())
		return 1;
		
#ifdef SUPPORT_5DISC_TRAY_SAVE_FUNC	
	load_5disc_tray_data();
#else
	disNumber = 1;
	init_5disc_driver();
#endif	
	//printf("5disc: ************************is out *****************************************is_tray_out()= %d \n",is_tray_out());		
	
	if(is_tray_out())
	{
#ifdef SUPPORT_5DISC_ALL_EJECT		
		ALL_Close_Handle();	
#else 		
		Individual_CLOSE_Handle();
#endif
		
	}
	else
	{
		reset_5disc_tray();
	}
	
	//if(next_rcvr_mode == RECEIVER_MODE_DVD)
	//	turn_on_5disc_led(0);	
	//else
	turn_on_5disc_led(1); //off led
		
		
	return 0;	
}

void reset_5disc_tray(void)
{
	BYTE disN;
	
	//when sw5 & sw7 for high,then show tray position error
	//printf("5disc: DET_SW5()= %d ,DET_SW7()= %d  \n",DET_SW5(),DET_SW7());
	if(DET_SW5() && DET_SW7())
		delay_5disc_ms(10); //delay 10ms		
	
	if(DET_SW5() && DET_SW7())
	{
		fdisc_tray = FDISC_TRAY_RESET;
		set_tray_to_close();		
		fdisc_tray = FDISC_TRAY_FINISH;
	}
	
	if(DET_SW5() && !DET_SW7())
	{
		for(disN=1;disN<5;disN++)
		{
			if(SETP_POS() == discN_stepN[disN-1])
			{
				if(disNumber!=disN)
				{
				disNumber = disN;
#ifdef SUPPORT_5DISC_TRAY_SAVE_FUNC	
					save_5disc_tray();
					//printf("5disc:=============== disNumber= %d  ,disN= %d \n",disNumber,disN);
#endif
				}	
				break;
			}
		}	
	}
	//printf("5disc:=============== disNumber= %d  \n",disNumber);
	
}

void set_play_step(unsigned char disN)
{

#ifdef TRAY_DB	
	printf("5disc: disN =  %d  \n",disN);
#endif
	fdisc_tray = FDISC_TRAY_PLAY;
	
	switch(disN)
	{
	case 1:	//disc 1
		if(set_step_positon(TYPE_STEP_5,STEP5_1PLAY))
		{
			printf("5disc: PLAY_1 position error !!!!!!!!!!!  \n");
			return ;
		}		
	break;

	case 2:	//disc 2
		if(set_step_positon(TYPE_STEP_4,STEP4_2PLAY))
		{
			printf("5disc: PLAY_2 position error !!!!!!!!!!!  \n");
			return ;
		}		
	break;
	
	case 3:	//disc 3
		if(set_step_positon(TYPE_STEP_3,STEP3_3PLAY))
		{
			printf("5disc: PLAY_3 position error !!!!!!!!!!!  \n");
			return ;
		}
	break;

	case 4:	//disc 4
		if(set_step_positon(TYPE_STEP_2,STEP2_4PLAY))
		{
			printf("5disc: PLAY_4 position error !!!!!!!!!!!  \n");
			return ;
		}
	break;

	case 5:	//disc 5
		if(set_step_positon(TYPE_STEP_1,STEP1_5PLAY))
		{
			printf("5disc: PLAY_5 position error !!!!!!!!!!!  \n");
			return ;
		}
	break;
	
	default:
	break;
	}
	
	if(disN>=1 && disN<=5)
	{
		set_tray_to_close();	
		
			
	}
	
	fdisc_tray = FDISC_TRAY_FINISH;
	
}

void set_tray_to_close(void)
{
	set_tray_in_from_middle_to_loader();
	set_5disc_tray_timeout_time(4); //set time out 2s
	
	while(1){
		
		polling_avoid_reentry=0;
		polling();	
		
		if(DET_SW5() && !DET_SW7())
			break;				
		
		if(get_5disc_tray_timeout_end())
		{
			printf("5disc<set_tray_to_close>: time out  DET_SW5()= %d, DET_SW7()= %d  \n",DET_SW5(), DET_SW7());
			break;
		}			
	}
	set_5disc_tray_timeout_time(0);
	delay_5disc_ms(52); //delay 52ms		
	set_tray_out_from_load_to_middle();
	delay_5disc_ms(32); //delay 32ms	
	set_tray_stop();	

#ifdef TRAY_DB		
	//send play command
	printf("5disc: !!!!!!!!!!!!!!! send play command to play !!!!!!!!!!!!!!!!!  \n");
#endif
	
	if(fdisc_tray != FDISC_TRAY_RESET)
	{
		open_tray();
		//delay_5disc_ms(52); //delay 52ms		
		close_tray(0);
		play_state = VCD_STATE_CLOSE;	
    	PrintOsdMsg(STR_OS_READ,REGION1,0,0);
		ircmd_play();
	}
}
void set_tray_to_middle(void)
{
	set_tray_in_from_middle_to_loader();
	delay_5disc_ms(6); //delay 6ms		
	set_tray_stop();	
	delay_5disc_ms(100); //delay 100ms		
	set_5disc_tray_timeout_time(4); //set time out 2s
	
	printf("1. 5disc: 	set_tray_to_middle  ================== \n");
	//set from loader position to standard position move	
	set_tray_out_from_load_to_middle();	
	
	while(1){
		
		polling_avoid_reentry=0;
		polling();
		
		if(!DET_SW5() && DET_SW7())
			break;	
		
		if(get_5disc_tray_timeout_end())
		{
			printf("5disc<set_tray_to_middle>: time out  DET_SW5()= %d, DET_SW7()= %d  \n",DET_SW5(), DET_SW7());
			break;
		}
	}
	set_5disc_tray_timeout_time(0);
	
	printf("2. 5disc: 	set_tray_to_middle  ================== \n");
	delay_5disc_ms(200); //delay 200ms		
	set_tray_in_from_middle_to_loader();
	delay_5disc_ms(100); //delay 100ms			
	set_tray_stop();	
}

//==================================================================================================
//
//
//
//==================================================================================================
unsigned char is_same_disc(unsigned char disN)
{
	if(is_play_position())
	{
		if(SETP_POS() == discN_stepN[disN-1])
		{
			invalid_key();		
			return 1;
		}
	}
	return 0;
}


//==================================================================================================
//	5Disc Play  handle
//		input: 
//
//
//
//
//==================================================================================================
void Play_Handle(unsigned char disN)
{
	if(is_tray_out() || (disN <=0) || (disN >=6))
	{
		invalid_key();		
		printf("5disc:&&&&&&&&&& < Play_Handle > is    tray  out  , can't to play  disc  is_tray_out()= %d ,disN= %d\n",is_tray_out(),disN);
		return ;
	}	

	if(is_same_disc(disN))
	{
		printf("5disc:&&&&&&&&&& < Play_Handle > is_same_disc disN =  %d   \n", disN);
		return ;
	}
	

	ircmd_post_func(CMD_FUNC | CMD_FUNC_OPEN);
	fdisc_tray = FDISC_TRAY_PLAY;
	if(is_play_position())
	{	
		//set from loader position to standard position move		
		set_tray_to_middle();
	}
	disNumber = disN;
	play_state = VCD_STATE_IDLE;//chenzhao20060107//VCD_STATE_5DISC
	play_5disc_state = FDISC_CHANGE_DISC;
	set_play_step(disN);	
	play_5disc_state = FDISC_NORMAL_DISC;
}

//==================================================================================================
//	5Disc ALL Eject handle
//		input: 
//
//
//
//
//==================================================================================================
#ifdef SUPPORT_5DISC_ALL_EJECT
void ALL_Eject_Handle(void)
{

#ifdef TRAY_DB		
	printf("5disc:<ALL_Eject_Handle> fdisc_tray= %d  \n",fdisc_tray);
#endif
	if(test_5disc_tray())
		return ;
	
	if(fdisc_tray  == FDISC_TRAY_FINISH)
	{	
		Eject_Handle(TYPE_STEP_6,STEP6_B_ALL_EJECT);
	}
		
}
int ALL_Close_Handle(void)
{
#ifdef TRAY_DB		
	printf("5disc:<ALL_Close_Handle> fdisc_tray= %d  \n",fdisc_tray);
#endif
	if(test_5disc_tray())
		return 0;
	
	if(fdisc_tray  == FDISC_TRAY_FINISH)
	{
		play_state = VCD_STATE_CLOSE;
		Close_Handle(TYPE_STEP_6,0);
		return 1;
	}
	return 0;	
}
#endif
//==================================================================================================
//	5Disc Individual Eject handle
//		input: 
//
//
//
//
//==================================================================================================
void Individual_Eject_Handle(void)
{
#ifdef TRAY_DB		
	printf("5disc:<Individual_Eject_Handle> fdisc_tray= %d ,disNumber=%d \n",fdisc_tray,disNumber);
#endif 
	if(test_5disc_tray())
		return ;
		
	if(fdisc_tray  == FDISC_TRAY_FINISH)
	{			
		switch(disNumber)
		{
		case 1:
			Eject_Handle(TYPE_STEP_4,STEP4_1EJECT);
		break;

		case 2:
			Eject_Handle(TYPE_STEP_5,STEP5_2EJECT);
		break;

		case 3:
			Eject_Handle(TYPE_STEP_4,STEP4_3EJECT);
		break;

		case 4:
			Eject_Handle(TYPE_STEP_3,STEP3_4EJECT);
		break;

		case 5:
			Eject_Handle(TYPE_STEP_2,STEP2_5EJECT);
		break;
		
		default:
		break;		
		}
	}
}

int Individual_CLOSE_Handle(void)
{
	char *s;
#ifdef TRAY_DB		
	printf("5disc:<Individual_CLOSE_Handle> fdisc_tray= %d  \n",fdisc_tray);
#endif 
	
	if(test_5disc_tray())
		return 0;
		
	if(fdisc_tray  == FDISC_TRAY_FINISH)
	{
		play_state = VCD_STATE_CLOSE;
		s=(char *)&(_OsdMessegeFont1[0][STR_OS_CLOSE][0]);
		osdshow(REGION1,s);
		Close_Handle(TYPE_STEP_1,0);
		return 1;
	}
	return 0;	
}

unsigned char tray_oper_finish(void)
{
	if(fdisc_tray  == FDISC_TRAY_FINISH)
		return 1;
	return 0;	
}

//==================================================================================================
//	5Disc ALL Eject Waiting 
//					 -----------		 -----------
//  				|			|		|			|
//					|			|		|			|
//  SW6 ------------			--------- 		    ----------------
//
//						--------------------------------------------
//						|
//						|
//  SW8 ----------------
//
//==================================================================================================
void ALL_Eject_Waiting(void)
{
	//set tray out !!!!
	set_tray_out();						
	
	do{
		polling_avoid_reentry=0;
		polling();							
	}while(!DET_SW8()); //wait for high

	//waiting sw6 low
	do{				
		polling_avoid_reentry=0;
		polling();					
	}while(DET_SW6());

	//waiting sw6 high			
	do{				
		polling_avoid_reentry=0;
		polling();					
	}while(!DET_SW6());
	
	//waiting sw6 low
	do{				
		polling_avoid_reentry=0;
		polling();					
	}while(DET_SW6());

	delay_5disc_ms(800);  //delay 800ms 			
	set_tray_stop();								
	delay_5disc_ms(10);  //delay 10ms 			


}
//==================================================================================================
//	5Disc Individual Eject Waiting 
//					 -----------------------------------------------
//  				|												|
//					|												|
//  SW6 ------------			 		    						--------------------------
//
//						----------------------------------------------------------------------
//						|
//						|
//  SW8 ----------------
//
//==================================================================================================
void Individual_Eject_Waiting(void)
{
	//set tray out !!!!
	set_tray_out();						
	
#ifdef OPEN_OR_CLOSE_ERROR_TO_POWER_OFF	
	set_tray_error_poweroff_time(TRAY_ERROR_POWER_OFF_TIME);
#endif	
	//printf("5disc: DET_SW8()= %d   \n",DET_SW8());		
	do{
		polling_avoid_reentry=0;
		polling();							
	}while(!DET_SW8()); //wait for high

	//waiting sw6 low
	do{				
		polling_avoid_reentry=0;
		polling();					
	}while(DET_SW6());
		
#ifdef OPEN_OR_CLOSE_ERROR_TO_POWER_OFF	
	set_tray_error_poweroff_time(0);
#endif
		
	set_tray_stop();								
	delay_5disc_ms(10);  //delay 10ms 			

}
//==================================================================================================
//	5Disc Individual Close Waiting 
//					 -----------------------------------------------
//  				|												|
//					|												|
//  SW6 ------------			 		    						--------------------------
//
//	SW8	----------------------------------------------------
//															|
//															|
//  														----------------------------------	
//
//==================================================================================================
void Individual_CLOSE_Waiting(void)
{
	set_tray_in();	
	delay_5disc_ms(5);  //delay 5ms 	
#ifdef OPEN_OR_CLOSE_ERROR_TO_POWER_OFF	
	set_tray_error_poweroff_time(TRAY_ERROR_POWER_OFF_TIME);
#endif
	
	//printf("1. 5disc<Individual_CLOSE_Waiting>:  ======= DET_SW6() = %d ,DET_SW8()= %d  \n",DET_SW6(),DET_SW8());
	
	//waiting sw6 high
	do{				
		polling_avoid_reentry=0;
		polling();					
	}while(!DET_SW6());

	do{
		polling_avoid_reentry=0;
		polling();							
	}while(DET_SW8()); //wait for low

	//waiting sw6 low
	do{				
		polling_avoid_reentry=0;
		polling();					
	}while(DET_SW6());

#ifdef OPEN_OR_CLOSE_ERROR_TO_POWER_OFF	
	set_tray_error_poweroff_time(0);
#endif
	//printf("4. 5disc<Individual_CLOSE_Waiting>:  ======= DET_SW6() = %d ,DET_SW8()= %d  \n",DET_SW6(),DET_SW8());
	
	delay_5disc_ms(10);
	set_tray_stop();					
	delay_5disc_ms(150);	//waiting time long !!!!!!!!!!!!!!!!!!!!!
}

//==================================================================================================
//	5Disc ALL Close Waiting 
//					 -----------		 -----------
//  				|			|		|			|
//					|			|		|			|
//  SW6 ------------			--------- 		    ----------------
//
//  SW8 -------------------------------------
//											|
//											|
//											------------------------
//
//==================================================================================================
void ALL_CLOSE_Waiting(void)
{	
	unsigned char out_flag,one_flag;
	
	out_flag = 0;
	one_flag = 1;
	
	set_tray_in();	
	delay_5disc_ms(5);  //delay 5ms 	
	
	//waiting sw6 high
	do{				
		polling_avoid_reentry=0;
		polling();					
	}while(!DET_SW6());
	
	//waiting sw6 low			
	do{				
		polling_avoid_reentry=0;
		polling();					
	}while(DET_SW6());
	
	//waiting sw6 high
	do{				
		polling_avoid_reentry=0;
		polling();					
	}while(!DET_SW6());
		
	//waiting sw6 low			
	do{				
		polling_avoid_reentry=0;
		polling();
							
	}while(DET_SW6());

	do{
		polling_avoid_reentry=0;
		polling();							
	}while(DET_SW8()); //wait for low
	
	delay_5disc_ms(50);  //delay 50ms

	delay_5disc_ms(10);
	set_tray_stop();				
	delay_5disc_ms(10);	
}

//==================================================================================================
//	5Disc Eject handle
//		input:  select type for eject.
//		output: none
//
//							by joke
//							2005/10/07
//==================================================================================================
void Eject_Handle(STEP_TYPE step_type,unsigned char eject_type) 
{		
	if(!is_tray_out())
	{
		fdisc_tray = FDISC_TRAY_OPEN;

#ifdef TRAY_DB		
		//set tray to open.		
		printf("5disc: tray is = %d \n",is_play_position());
#endif		
		if(is_play_position())
		{	
			//set from loader position to standard position move		
			set_tray_to_middle();
		}

		if(set_step_positon(step_type,eject_type))
		{
			printf("5disc:2 Eject search position error !!!!!!!!!!!  \n");
			return ;
		}
		
#ifdef SUPPORT_5DISC_ALL_EJECT		
		if(step_type == TYPE_STEP_6)
			ALL_Eject_Waiting();
		else
#endif
			Individual_Eject_Waiting();	

#ifdef TRAY_DB				
		printf("5disc: eject over !!!!! ............... \n");				
#endif
		fdisc_tray  = FDISC_TRAY_FINISH;
		
		//if(step_type == TYPE_STEP_6)
		init_5disc_driver();
		
		set_5disc_tray_timeout_time(0);
	}
}

//==================================================================================================
//	5Disc Close handle
//		input:  none
//		output: none
//
//							by joke
//							2005/10/07
//==================================================================================================
void Close_Handle(STEP_TYPE step_type,unsigned char no_close_key) 
{
	int i,play_pos;
	
	if(is_tray_out())
	{
		fdisc_tray = FDISC_TRAY_CLOSE;
		//set tray close & set to play
#ifdef TRAY_DB		
		printf("5disc: tray is out...........  \n");
#endif		
		if(step_type==TYPE_STEP_6)
		{
			ALL_CLOSE_Waiting();
			detect_all_disc();
			if(no_close_key==1)
			{
				Play_Handle(disNumber);
				fdisc_tray  = FDISC_TRAY_FINISH;
				set_5disc_tray_timeout_time(0);
				return ;
			}
		}
		else		
		{
			Individual_CLOSE_Waiting();
			Play_Handle(disNumber);
#ifdef TRAY_DB					
			printf("5disc: tray close[Individual] over !!!!!!!!!!!.....  \n");		
#endif			
			fdisc_tray  = FDISC_TRAY_FINISH;
			set_5disc_tray_timeout_time(0);
			return ;
		}
		
		play_pos = 0;
		if(is_no_disc())
		{
			//play_state = VCD_STATE_CLOSE;
			//system_state = SYSTEM_NODISC;
			open_tray();
			close_tray(0);
			play_state = VCD_STATE_CLOSE;	
			ircmd_play();
				
			if(set_step_positon(TYPE_STEP_6,STEP6_ALL_LOCK))
			{
				printf("5disc: Eject search all_lock position error !!!!!!!!!!!  \n");
				return ;			
			}
		}
		else
		{
			for(i=1;i<=NUMBER_OF_DISC;i++)
			{
				if(get_disc_number(i))
				{
					play_pos = i;
					break;
				}
			}
			Play_Handle(play_pos);
		}

		fdisc_tray  = FDISC_TRAY_FINISH;
		set_5disc_tray_timeout_time(0);

#ifdef TRAY_DB		
		printf("5disc: tray close[ALL] over !!!!!!!!!!!.....  \n");		
#endif
		
	}
}
//==================================================================================================
//	init 5disc driver
//		input:  none
//		output: none
//
//							by joke
//							2005/10/07
//==================================================================================================
void init_5disc_driver(void)
{
	int i;
	
	for (i=0; i<NUMBER_OF_DISC; ++i)
		slotStatus[i] = DM_GSS_UNKNOWN;
}		

void set_current_disc(void)
{
	//printf("5disc<no disc>: disNumber= %d  \n",disNumber);
	switch(system_state)
	{
		case SYSTEM_NODISC:
		{
			if(slotStatus[disNumber-1] != DM_GSS_DISC_NOT_PRESENT)
			{
			slotStatus[disNumber-1]  = DM_GSS_DISC_NOT_PRESENT;
#ifdef SUPPORT_5DISC_TRAY_SAVE_FUNC				
				save_5disc_tray();
#endif		
			}	
		}
		break;
		
		case SYSTEM_READ_TITLE:
		{
			slotStatus[disNumber-1]  = DM_GSS_DISC_PRESENT;		
#ifdef SUPPORT_5DISC_TRAY_SAVE_FUNC			
			save_5disc_tray();
#endif			
		}
		break;
	}
}
void delete_driver_exchange_mode(void)
{
	int i;
	
	for (i=0; i<NUMBER_OF_DISC; ++i)
	{
		if((disNumber-1)!=i)
			slotStatus[i] = DM_GSS_UNKNOWN;	
	}
#ifdef SUPPORT_5DISC_TRAY_SAVE_FUNC		
	save_5disc_tray();
#endif	
}


//==================================================================================================
//	5Disc detect disc handle
//		input:  none
//		output: none
//
//							by joke
//							2005/10/07
//==================================================================================================
void detect_all_disc(void)
{
	int i;

	play_state = VCD_STATE_IDLE;//chenzhao20060107//VCD_STATE_5DISC
	play_5disc_state = FDISC_DETECT_DISC;

	//for(i=TYPE_STEP_5;i>=TYPE_STEP_1;i--)
	for(i=TYPE_STEP_1;i<=TYPE_STEP_5;i++)
	{
		disNumber = TYPE_STEP_6 - i; 
		detect_disc(i,STEP1_5PLAY);
	}

}



void detect_disc(STEP_TYPE step_type,unsigned char sub_step_type)
{
	
	if(set_step_positon(step_type,sub_step_type))
	{
		printf("5disc: detect disc %d find position error !!!!!!!!!!!  \n",step_type);
		return ;
	}
	set_tray_stop();
	set_5disc_plunger_status(0);	
	set_5disc_tray_timeout_time(0);	
	set_tray_in_from_middle_to_loader();
	
	//waiting sw5 high
	do{
		polling_avoid_reentry=0;
		polling();
	}			
	while(!DET_SW5());
		
	printf("5disc:1: DETECT_DISC()= %d   \n",	DETECT_DISC());
	//waiting disc detect high
	do{
		polling_avoid_reentry=0;
		polling();	
	}
	while(!DETECT_DISC());
	//start counter disc detect 
	printf("5disc:2: DETECT_DISC()= %d   \n",	DETECT_DISC());
	
	start_counter_flag = 1;
	disc_detect_time = 0;
	
	Set_control_timer(56);  //delay 112ms
	
	do{
		polling_avoid_reentry=0;
		polling();					
	}while(!detect_disc_delay_time);	
	

	Set_control_timer(16);  //delay 32ms
	set_tray_out_from_load_to_middle();	
	do{
		polling_avoid_reentry=0;
		polling();		
	}while(!detect_disc_delay_time);	

	Set_control_timer(252);  //delay 504ms
	set_tray_stop();
	do{
		polling_avoid_reentry=0;
		polling();		
	}while(!detect_disc_delay_time);	
	
	Set_control_timer(0);
	set_tray_out_from_load_to_middle();	
	
	//waiting sw5 low
	do{
		polling_avoid_reentry=0;
		polling();
	}			
	while(DET_SW5());
	//counter disc detect over
	start_counter_flag = 0;

#ifdef TRAY_DB	
	printf("5disc: disN= %d : disc_detect_time= %d   \n",step_type,disc_detect_time);
#endif
	
	if(disc_detect_time>=DISC_DETECT_TIME)
		slotStatus[TYPE_STEP_5 - step_type] = DM_GSS_DISC_PRESENT;
	else
		slotStatus[TYPE_STEP_5 - step_type] = DM_GSS_DISC_NOT_PRESENT;	
	
	disc_detect_time = 0;

	delay_5disc_ms(200);
	set_tray_in_from_middle_to_loader();
	delay_5disc_ms(80);
	set_tray_stop();
	delay_5disc_ms(200);
	
	printf("5disc: detect over a disc \n");
	
}

unsigned char is_no_disc(void)
{
	int i;
	
	for(i=0;i<NUMBER_OF_DISC;i++)
	{
		if(slotStatus[i]==DM_GSS_DISC_PRESENT)
			return 0;
	}
	return 1;
}

// disN = 1~5
//
//
unsigned char get_disc_number(BYTE disN)
{
	if(disN <=0 || disN >NUMBER_OF_DISC)
		return 0;
		
	if(slotStatus[disN-1]==DM_GSS_DISC_PRESENT)
	{
		return disN;
	}
	return 0;	
}

unsigned char disc_in_slot(BYTE disN)
{
	if(slotStatus[disN-1]==DM_GSS_DISC_PRESENT || slotStatus[disN-1]==DM_GSS_UNKNOWN)
		return 1;
	return 0;	
}

void set_exchange_command(void)
{
	set_oper_mode = FDISC_EXCHANGE;
}

void set_jump_disc_mode(void)
{
	check_jump_disc = 1;	
}
void set_clear_jump_disc_mode(void)
{
	check_jump_disc = 0;		
}
unsigned char is_jump_disc_mode(void)
{
	return check_jump_disc;
}

void set_oper_idle_command(void)
{
	set_oper_mode = OPER_DISC_IDLE;

}
void set_jump_disc_command(void)
{
	set_oper_mode = JUMP_DISC;
}
void set_all_open_command(void)
{
#ifdef SUPPORT_5DISC_ALL_EJECT	
	set_oper_mode = ALL_OPEN;
	c_is_all_eject_flag = 1;
#endif 	
}
void set_individual_open_command(void)
{
	set_oper_mode = INDIVIDUAL_OPEN;
	c_is_all_eject_flag = 0;
}
unsigned char get_is_all_eject(void)
{
	return c_is_all_eject_flag;
}

void skip_disc_func(void)
{
	unsigned char disN;
	
	if(test_5disc_tray())
		return ;
	
	if(is_exchange())
		return ;
	
	disN = disNumber;
	if(fdisc_tray != FDISC_TRAY_FINISH)
		return ;
	
	if(is_tray_out())
	{
			disN +=1;
			if(disN >NUMBER_OF_DISC)	
				disN = 1;		
	}
	else
	{
		printf("5disc: disNumber= %d   \n",disNumber);
		do
		{
			disN +=1;
			if(disN >NUMBER_OF_DISC)	
				disN = 1;		
				
		}while((slotStatus[disN-1] & DM_GSS_DISC_NOT_PRESENT) && ( disN != disNumber));
		
		printf("5disc: disN= %d   \n",disN);
	}
	set_skip_disc(disN);
}

void set_skip_disc(unsigned char disN)
{	
	if(test_5disc_tray())
		return ;
	
	if(is_exchange())
		return ;
	
	if(is_same_disc(disN) || fdisc_tray != FDISC_TRAY_FINISH)
	{
		printf("5disc: fdisc_tray= %d   \n",fdisc_tray);
		return ;
	}
	
	if(!disc_in_slot(disN))
	{
		printf("5disc:<in slot> disN= %d   \n",disN);
		invalid_key();	
		return ;
	}
#if 0		
	open_tray();
	ircmd_post_func(CMD_FUNC | CMD_FUNC_OPEN);
	play_state = VCD_STATE_OPEN;
	disNumber = disN;
	ShowTitle();						//display logo
#endif	
	disNumber = disN;
	
	set_jump_disc_mode();
	ircmd_trayout();
	//set_clear_jump_disc_mode();
	
	set_jump_disc_command();
}	


		
			
void polling_5disc_oper(void)
{
	switch(set_oper_mode)
	{
		case OPER_DISC_IDLE:
			Hand_Sense_Handle();
		break;
	
		case JUMP_DISC:
		if((cIDEStatus&0x80)==0x00) //check disc stop problem 
		{
			char *s;
			
			if(test_5disc_tray())
				return ;
			set_oper_idle_command();
		
			#ifdef OP_PROGRAM_LIST_OPER //by joke: fixed bug#206
				clear_prog_list();
			#endif
			printf("5disc<command>: disNumber = %d   \n",disNumber);
			if(is_tray_out())
			{
#ifdef SUPPORT_5DISC_ALL_EJECT				
				if(get_is_all_eject())
				{
					play_state = VCD_STATE_CLOSE;
					Close_Handle(TYPE_STEP_6,1);
				}
				else
#endif				
				{
					play_state = VCD_STATE_CLOSE;
					s=(char *)&(_OsdMessegeFont1[0][STR_OS_CLOSE][0]);
					osdshow(REGION1,s);
					Close_Handle(TYPE_STEP_1,1);

					//by joke: fixed 6505 bug#245
			        CDSetStop();
			        ircmd_post_func(CMD_FUNC | CMD_FUNC_CLOSE);//kenny 2001/6/11  add it
			        play_state = VCD_STATE_CLOSE;
                    play_5disc_state = FDISC_NORMAL_DISC;//chenzhao20060107
				}
			}
			else
			{
#if (defined(SUPPORT_USB) && defined(USB_MODE_CHANGE_DISC_TO_PLAY_DISC))
				setup_VA[SETUP_VA_MEDIA_TYPE] = 2; //playback disc , no usb
				media_type = MEDIA_CD;
#endif				
				Play_Handle(disNumber);
			}
			set_clear_jump_disc_mode();
			
#ifdef SUPPORT_5DISC_TRAY_SAVE_FUNC				
			save_5disc_tray();
#endif			
		}
		break;
	
#ifdef SUPPORT_5DISC_ALL_EJECT
		case ALL_OPEN:
		if((cIDEStatus&0x80)==0x00) 
		{
			if(test_5disc_tray())
				return ;
			#ifdef OP_PROGRAM_LIST_OPER //by joke: fixed bug#206
				clear_prog_list();
			#endif

			vfd_clear_Digit_icon();
			clear_icon_except_speaker();	
			//ircmd_post_func(CMD_FUNC | CMD_FUNC_OPEN);
			play_state = VCD_STATE_OPEN;
			set_oper_idle_command();
			printf("5disc<command>: send all eject command !!!!!!!   \n");
			ALL_Eject_Handle();
#ifdef SUPPORT_5DISC_TRAY_SAVE_FUNC				
			save_5disc_tray();
#endif			
		}
		break;
#endif
	
		case INDIVIDUAL_OPEN:
		if((cIDEStatus&0x80)==0x00) 
		{			
			if(test_5disc_tray())
				return ;

			vfd_clear_Digit_icon();
			clear_icon_except_speaker();
			
			#ifdef OP_PROGRAM_LIST_OPER //by joke: fixed bug#206
				clear_prog_list();
			#endif
			
			play_state = VCD_STATE_OPEN;
			set_oper_idle_command();
			printf("5disc<command>: send Individual eject command !!!!!!!   \n");
			Individual_Eject_Handle();
#ifdef SUPPORT_5DISC_TRAY_SAVE_FUNC				
			save_5disc_tray();
#endif			
//			vfd_clear_Digit_icon();
//			clear_icon_except_speaker();

		}
		break;	
		
		case FDISC_EXCHANGE:
		{
			if(test_5disc_tray())
				return ;
			set_oper_idle_command();
			Exchange_Handle();
		}
		break;					
	}
}

//============================================================================================================
//	hand sense handle 
//
//
//============================================================================================================
void hand_sense_polling_500ms(void)
{
	if(hand_sense_flag==1)
	{
		hand_sense_delay ++;
		if(hand_sense_delay>20) //10ms
		{
			hand_sense_flag = 0;	
			hand_sense_delay = 0;	
		}
	}
}
void Hand_Sense_Handle(void)
{
		
	if(test_5disc_tray() || current_rcvr_mode!=RECEIVER_MODE_DVD)
		return ;
		
	if(is_exchange())
		return ;
			
    #ifndef MERGE_TEMP
	if(Get_VfdModeState()!=3) //NORMAL_MODE_STATE
	{
		hand_sense_delay = 0;
		hand_sense_flag = 1;
		return 0;
	}
    #endif
	if(hand_sense_flag>0)
	{
		//printf("5disc: &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& OK &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&  \n");
		return ;
	}
	
	if(DET_SW6() && tray_oper_finish() && is_tray_out())
	{
		hand_sense_counter +=1;
		printf("5disc: hand_sense_counter= %x  \n",hand_sense_counter);
	}
	else 
		hand_sense_counter =0;
		
	if(tray_oper_finish() && hand_sense_counter>=5)
	{	
		hand_sense_counter =0;	
		if(is_tray_out())
		{
			
#ifndef SUPPORT_5DISC_EXCHANGE							
			if(get_is_all_eject())
				ALL_Close_Handle();
			else
#endif			
				Individual_CLOSE_Handle();	
		}
	}
}
//============================================================================================================
//	for exchange use , set step position
//
//============================================================================================================
BYTE set_step_postion_polling(STEP_TYPE steptype,BYTE substepNumber)
{
	step_Number 	= steptype;
	substep_Number 	=substepNumber;
	aimphoto_Number =substepNumber; 
	runForward      = 0;
	photocounter_flag = 0;
	counter_photo     = 0;
	
	set_5disc_tray_timeout_time(24); //set time out : 12s	
	set_tray_stop();
	set_5disc_plunger_status(1);
	printf("5disc: 1   &&&&&&&&&&&&&&&&&&&&&&& set plunger HIGH  &&&&&&&&&&&&&&&&&&&&&&  \n");
	if(SETP_POS()==get_step_pos_number(step_Number))
	{
		middle_stepNumber = get_middle_pos_for_step_left_border(step_Number);
		set_mm_run(0);
		step_operate = SEARCH_MIDDLE_STEP;
		return 1;
	}
	step_operate = SEARCH_PHOTO;
	return 2;	
}

void init_exchange_operate(void)
{
	step_operate =STEP_RUN_IDLE;
	waiting_close =WAITCLOSE_IDLE;
	waiting_eject =WAITEJECT_IDLE;
	exchang_type  = EXCHANGE_IDLE;
}

BYTE step_operate_polling(void)
{
	switch(step_operate)
	{
		case STEP_RUN_IDLE:
		break;
		
		case SEARCH_MIDDLE_STEP:
		{
			if(SETP_POS()==middle_stepNumber && DET_PHOTO())
			{
				set_tray_stop();
				if(SETP_POS()==middle_stepNumber && DET_PHOTO())
				{
					step_operate = SEARCH_PHOTO;
					printf("5disc:from SEARCH_MIDDLE_STEP to SEARCH_PHOTO \n");
					break;
				}
			}
			
			if(get_5disc_tray_timeout_end())
			{
				printf("5disc: error SEARCH_MIDDLE_STEP  \n");
				return 1;
			}		
		}
		break;
				
		case SEARCH_PHOTO:
		{
			if(is_run_forward(step_Number))
				runForward = 1;
			else
			{
				if(step_Number==TYPE_STEP_6)
					aimphoto_Number = eject_step_aim_photo_tab[substep_Number];
				else 
					aimphoto_Number = aim_photo_tab[substep_Number];
			}
			set_mm_run(runForward);	
			
			step_operate = STEP_PHOTO_COUNTER;			
			printf("5disc:from SEARCH_PHOTO to STEP_PHOTO_COUNTER \n");
		}
		break;
		
		case STEP_PHOTO_COUNTER:
		{
			if(SETP_POS()==get_step_pos_number(step_Number))
			{
				//waiting photo from low to high
				if(!DET_PHOTO())
				{
					photocounter_flag = 1;	
					if(get_5disc_tray_timeout_end())
					{
						printf("5disc: error STEP_PHOTO_COUNTER 1 \n");						
						return 1;
					}	
					return 0;								
				}
				
				if(photocounter_flag)
				{
					photocounter_flag  = 0;
					counter_photo = counter_photo + 1;
					printf("5disc: counter_photo = %d ,aimphoto_Number= %d  \n",counter_photo,aimphoto_Number);
				}
			}
			if((SETP_POS()==get_step_pos_number(step_Number)) && (counter_photo==aimphoto_Number))
			{
				step_operate = WAIT_PHOTO_HIGH_TO_LOW_1;
				Set_control_timer(3);  //delay 6ms
				set_mm_run(!runForward);
				run_mm_flag = 1;
				runmm_flag = !runForward;
				printf("5disc:from STEP_PHOTO_COUNTER to WAIT_PHOTO_LOW_TO_HIGH \n");
				break;
			}
			
			if(get_5disc_tray_timeout_end())
			{
				printf("5disc: error STEP_PHOTO_COUNTER 2 \n");						
				return 1;
			}			
		}
		break;
		
		case WAIT_PHOTO_HIGH_TO_LOW_1:
		{
			//waiting photo from high to low
			//set_mm_run(!runForward);
			//delay_5disc_ms(6); //delay 5ms	
			//set_tray_stop();	
			//delay_5disc_ms(10); //delay 10ms	
			delay_run_mm_flag = 1;
			if(get_5disc_tray_timeout_end())
			{
				delay_run_mm_flag = 0;
				printf("5disc: error WAIT_PHOTO_LOW_TO_HIGH  \n");						
				return 1;
			}

			if(!DET_PHOTO())
			{
				step_operate = WAIT_PHOTO_LOW_TO_HIGH;	
				Set_control_timer(3);  //delay 6ms				
				set_mm_run(!runForward);
				run_mm_flag = 1;
				runmm_flag = !runForward;
				printf("5disc:from WAIT_PHOTO_HIGH_TO_LOW_1 to WAIT_PHOTO_LOW_TO_HIGH \n");
			}
		}
		break;
		
		case WAIT_PHOTO_LOW_TO_HIGH:
		{
			//waiting photo from low to high	
			//set_mm_run(!runForward);
			//delay_5disc_ms(6); //delay 5ms	
			//set_tray_stop();	
			//delay_5disc_ms(10); //delay 10ms	
	
			if(get_5disc_tray_timeout_end())
			{
				delay_run_mm_flag = 0;
				printf("5disc: error WAIT_PHOTO_HIGH_TO_LOW  \n");						
				return 1;
			}
			if(DET_PHOTO())	
			{
				step_operate = WAIT_PHOTO_HIGH_TO_LOW_2;
				Set_control_timer(3);  //delay 6ms				
				set_mm_run(runForward);
				run_mm_flag = 1;
				runmm_flag = runForward;
				printf("5disc:from WAIT_PHOTO_HIGH_TO_LOW to STEP_RUN_FINISH \n");			
			}
		
		}
		break;
		
		case WAIT_PHOTO_HIGH_TO_LOW_2:
		{
			//set_mm_run(runForward);
			//delay_5disc_ms(6); //delay 5ms	
			//set_tray_stop();	
			//delay_5disc_ms(10); //delay 10ms	
	
			if(get_5disc_tray_timeout_end())
			{
				printf("5disc: error WAIT_PHOTO_LOW_TO_HIGH_2  \n");						
				return 1;
			}
			if(!DET_PHOTO())	
			{
				step_operate = STEP_RUN_FINISH;
				delay_run_mm_flag = 0;
				set_tray_stop();
				printf("5disc:from WAIT_PHOTO_HIGH_TO_LOW to STEP_RUN_FINISH \n");			
			}
		}
		break;
		
		case STEP_RUN_FINISH:
		{
			set_5disc_tray_timeout_time(0);
			set_mm_run(!runForward);
			delay_5disc_ms(2); //delay 10ms		
			//delay_5disc_ms(10); //delay 10ms		
			set_tray_stop();	
			
			set_5disc_plunger_status(0);	
			step_operate = STEP_RUN_IDLE;
			
			if(exchang_type == EXCHANGE_CLOSE)
			{
				set_exchange(0);		
				fdisc_tray = FDISC_TRAY_FINISH;			
				printf("5disc: STEP_RUN_FINISH,exchange close over!!!!  \n");						
			}
			else if(exchang_type == EXCHANGE_OPEN)
			{
				waiting_eject = WAITEJECT_SW8_HIGH;//WAITCLOSE_SW6_HIGH;	
#ifdef OPEN_OR_CLOSE_ERROR_TO_POWER_OFF	
				set_tray_error_poweroff_time(TRAY_ERROR_POWER_OFF_TIME);
#endif							
				printf("5disc: STEP_RUN_FINISH, VIEW OVER TO exchange eject begin!!!  \n");						
			}
		}
		break;
	}
	return 0;
}
void Exchange_Handle_WaitClose_Polling(void)
{
	switch(waiting_close)
	{
		case WAITCLOSE_IDLE:
		break;
		
		case WAITCLOSE_SW6_HIGH:
		{
			//waiting sw6 high
			if(DET_SW6())
				waiting_close = WAITCLOSE_SW8_LOW;	
		}
		break;
		
		case WAITCLOSE_SW8_LOW:
		{
			//wait for low
			if(!DET_SW8())
				waiting_close = WAITCLOSE_SW6_LOW;				
		}
		break;
		
		case WAITCLOSE_SW6_LOW:
		{
			//waiting sw6 low
			if(!DET_SW6())
			{
				waiting_close = WAITCLOSE_FINISH;
				Set_control_timer(56);  //delay 112ms
			}
		}
		break;
		
		case WAITCLOSE_FINISH:
		{
			set_tray_stop();
			if(detect_disc_delay_time)
			{	
				waiting_close = WAITCLOSE_IDLE;
				set_step_postion_polling(step_Number,STEP1_5PLAY);	
			}
#ifdef OPEN_OR_CLOSE_ERROR_TO_POWER_OFF	
			set_tray_error_poweroff_time(0);
#endif				
		}
		break;
	}

}
void Exchange_Handle_WaitEject_Polling(void)
{
	switch(waiting_eject)
	{
		case WAITEJECT_IDLE:
		break;
		
		case WAITEJECT_SW8_HIGH:
		{
			set_tray_out();	
			if(DET_SW8()) //waiting sw8 high
				waiting_eject = WAITEJECT_SW6_LOW;	
		}
		break;
		
		case WAITEJECT_SW6_LOW:
		{
			//waiting sw6 low
			if(!DET_SW6())
			{
				waiting_eject = WAITEJECT_FINISH;	
				Set_control_timer(300);  //delay600ms
			}
		}
		break;
		
		case WAITEJECT_FINISH:
		{
			if(detect_disc_delay_time)
			{
				set_tray_stop();								
				//delay_5disc_ms(10);  //delay 10ms 	
				waiting_eject = WAITEJECT_IDLE;	
				
				if(exchang_type == EXCHANGE_OPEN)
				{
#ifdef OPEN_OR_CLOSE_ERROR_TO_POWER_OFF	
					set_tray_error_poweroff_time(0);
#endif							
					set_exchange(1);
					fdisc_tray = FDISC_TRAY_FINISH;
					delete_driver_exchange_mode();
					printf("5disc: exchange eject over!!!!  \n");
				}
			}
		}
		break;
	}
}

//============================================================================================================
//	exchange handle 
//
//
//============================================================================================================
void set_exchange(unsigned char set)
{
	exchange = set;
}
unsigned char is_exchange(void)
{
	return exchange;	
}

void Exchange_Handle(void)
{
	STEP_TYPE step_N;
	
	if(test_5disc_tray())
		return ;
	
	if(fdisc_tray != FDISC_TRAY_FINISH)
		return ;
		
	printf("5disc: PLAY_STATE()= %d ,is_play_position()= %d \n",PLAY_STATE(),is_play_position());		
	if(!(PLAY_STATE() && is_play_position()))
		return ;
		

	step_N = TYPE_STEP_6 - disNumber; 
#if 1
	if(is_tray_out())	
	{
		fdisc_tray = FDISC_TRAY_CLOSE;
		set_tray_in();	
		waiting_close = WAITCLOSE_SW6_HIGH;
		step_Number = step_N;
		exchang_type = EXCHANGE_CLOSE;
#ifdef OPEN_OR_CLOSE_ERROR_TO_POWER_OFF	
		set_tray_error_poweroff_time(TRAY_ERROR_POWER_OFF_TIME);
#endif			
		//set_step_postion_polling(step_N,STEP1_5PLAY);	
		//set_exchange(0);		
		//fdisc_tray = FDISC_TRAY_FINISH;
	}
	else
	{
		exchang_type = EXCHANGE_OPEN;
		fdisc_tray = FDISC_TRAY_DISC_VIEW;
		set_step_postion_polling(step_N,STEP1_Disc_VIEW);	
		//Individual_Eject_Waiting();
		//set_exchange(1);
		//fdisc_tray = FDISC_TRAY_FINISH;
	
	}
#else
	if(is_tray_out())	
	{
		fdisc_tray = FDISC_TRAY_CLOSE;
		printf("5disc<exchange close>: step_N = %d  \n",step_N);
		Individual_CLOSE_Waiting();
		if(set_step_positon(step_N,STEP1_5PLAY))
		{
			printf("5disc:  exchange close fail   ..... \n");
			return ;					
		}
		set_exchange(0);		
		fdisc_tray = FDISC_TRAY_FINISH;
	}
	else
	{
		fdisc_tray = FDISC_TRAY_DISC_VIEW;
		printf("5disc<exchange>: step_N = %d  \n",step_N);
		if(set_step_positon(step_N,STEP1_Disc_VIEW))
		{
			printf("5disc:  exchange fail   ..... \n");
			return ;
		}				
		Individual_Eject_Waiting();
		set_exchange(1);
		fdisc_tray = FDISC_TRAY_FINISH;
	}
	printf("5disc: exchange over !!!!!!!!!!!!!  \n");
#endif
}
//============================================================================================================
//standby to close ,if tray is open
//
//
//============================================================================================================
void standby_to_close_fun(void)
{
#ifdef SUPPORT_VFD_MENU
    Set_VfdModeState(0); //POWER_ON_STATE
#endif
	set_video_mute(0); //mute video

	if(test_5disc_tray())
		return ;
#ifdef OPEN_OR_CLOSE_ERROR_TO_POWER_OFF		
	if(tray_error_power_off)
	{
		printf("5disc: tray error to standby  ......  \n");
		return ;
	}
#endif
	
	STEP_TYPE step_N;
	if(is_exchange())
	{
		step_N = TYPE_STEP_6 - disNumber; 
		
		fdisc_tray = FDISC_TRAY_CLOSE;
		printf("5disc<standby_to_close_fun>: step_N = %d  \n",step_N);
		Individual_CLOSE_Waiting();		
		if(set_step_positon(step_N,STEP1_5PLAY))
		{
			printf("5disc:  standby_to_close_fun fail   ..... \n");
			return ;					
		}
		set_exchange(0);		
		fdisc_tray = FDISC_TRAY_FINISH;
		return ;
	}
	
	if(is_tray_out())
		Individual_CLOSE_Handle();
}
//============================================================================================================
//
//
//
//============================================================================================================
unsigned char turn_on_5disc_led(BYTE Off_Led)
{
	int led_id;
	
	if(Off_Led) //off led 
	{
		led_on_flag = 0;		
		led_id = 12; //off all led
		write_vfd_led(led_id);
		return 0;
	}
	
	if(disNumber<=0 || disNumber>5 || led_on_flag==disNumber)
		return 1;
		
	if(disNumber==1)
		led_id = 10;
	else if(disNumber==2)
		led_id = 2;
	else if(disNumber==3)
		led_id = 4;
	else if(disNumber==4)
		led_id = 6;
	else if(disNumber==5)
		led_id = 8;
	
	led_on_flag = disNumber;		
	write_vfd_led(led_id);

	return 0;
}

void polling_5disc_control(void)
{	
	//exchange polling func.	
	if(step_operate_polling())
	{
		error_stop();
		step_operate = STEP_RUN_IDLE;
		if(exchang_type == EXCHANGE_CLOSE)
		{
			set_exchange(0);		
			fdisc_tray = FDISC_TRAY_FINISH;			
		}
	}
	Exchange_Handle_WaitClose_Polling();
	Exchange_Handle_WaitEject_Polling();
	//exchange polling func end.
	
	control_timer_polling();
	polling_5disc_oper();
		
	
#if 0
    psprintf(linebuf,"P%1d   %02d",DET_PHOTO(), SETP_POS());
	erase_vfd_mem();        
	vfd_set_str(0,0,0,linebuf);
#endif	
}

void polling_5disc_control_500ms()//chenzhao20060107
{
    polling_fdisc_tray_timeout_time();
    #ifdef OPEN_OR_CLOSE_ERROR_TO_POWER_OFF
    tray_error_auto_power_off_polling_500ms();
    #endif
    hand_sense_polling_500ms();
    #ifdef STOP_SERVO_IN_OTHER_MODE
    call_loader_to_stop_polling_500ms();
    #endif
}

void test_disc(void)
{
	int i;
	for(i=0;i<5;i++)
		printf("5disc: slotStatus[%d] = %x \n",i,slotStatus[i]);
}

void look_fdisc_tray(void)
{
	printf("5disc: fdisc_tray = %d \n" ,fdisc_tray);
}

#ifdef STOP_SERVO_IN_OTHER_MODE
void stop_loader(void);
BYTE cnt_stop_flag;
BYTE cnt_loader_time;
#define	LOADER_STOP_TIME	8 //5

void call_loader_to_stop_polling_500ms(void)
{
	if(current_rcvr_mode ==RECEIVER_MODE_DVD)
	{
	    stop_loder_cnt=0;
	    cnt_stop_flag = 0;
	    cnt_loader_time = 0;
		return ;
	}

    if(stop_loder_cnt>=LOADER_STOP_TIME) //12
    {
        if(stop_loder_cnt==LOADER_STOP_TIME)//12
        {
        	printf("5disc : stop loader in polling ....................  \n");
            stop_loader();
            stop_loder_cnt++;
            cnt_stop_flag = 1;
            return ;
        }
    }
    else
        stop_loder_cnt++;

    if((cIDEStatus&0x80)!=0x00)
    {
		if(cnt_stop_flag)
		{
	    	printf("5disc: cnt_stop_flag= %d  \n",cnt_stop_flag);
			stop_loader();
			cnt_loader_time++;
			if(cnt_loader_time>5)
			{
				cnt_loader_time = 0;
				cnt_stop_flag = 0;
			}
		}
	}
    
}
#endif

