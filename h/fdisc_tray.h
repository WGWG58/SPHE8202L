#ifndef FDISC_TRAY_H
#define FDISC_TRAY_H



#define	FDISC_TRAY_ERROR		1
#define	FDISC_TRAY_NORMAL		2

#define	DISC_DETECT_TIME		30000

#define PLAY_STATE()	(play_state>=VCD_STATE_READTOC && play_state<VCD_STATE_9FRAMES || (play_state == VCD_STATE_STOP) || (play_state == VCD_STATE_MP3_FILELIST))

//
#define	DET_SW1()		get_5disc_sw1_status()
#define	DET_SW2()		get_5disc_sw2_status()
#define	DET_SW3()		get_5disc_sw3_status()
#define	DET_SW4()		get_5disc_sw4_status()

#define	DET_SW5()		get_5disc_sw5_status()
#define	DET_SW6()		get_5disc_sw6_status()
#define	DET_SW7()		get_5disc_sw7_status()
#define	DET_SW8()		get_5disc_sw8_status()
#define DET_PHOTO() 	get_5disc_photo_status()
#define DETECT_DISC() 	get_5disc_disc_detect_status()
					
#define SETP_POS()	(DET_SW1() | (DET_SW2()<<1) | (DET_SW3()<<2) | (DET_SW4()<<3))

 	
#define	NUMBER_OF_DISC		0x05
 	
//Indication Step Position
#define	START_POS			0x0d
#define	STEP_1_POS			0x09
#define MIDDLE_16_POS		0x08
#define STEP_6_POS			0x0a
#define MIDDLE_62_POS		0x0b
#define STEP_2_POS			0x03
#define MIDDLE_23_POS		0x07
#define STEP_3_POS			0x0f
#define	MIDDLE_34_POS		0x0e
#define STEP_4_POS			0x0c
#define MIDDLE_45_POS		0x04
#define STEP_5_POS			0x06
#define END_POS				0x02
#define ERROR_5_1			0x01			//error status.

#define MAX_5DISC_STEP 		0x06


typedef enum{
	
	TYPE_STEP_1=1,
	TYPE_STEP_2,
	TYPE_STEP_3,
	TYPE_STEP_4,
	TYPE_STEP_5,
	TYPE_STEP_6,
	}STEP_TYPE;


//1 SETP MODE
typedef enum{
	STEP1_5PLAY=1,		//5PLAY
	STEP1_Disc_VIEW,	//DISC VIEW
	STEP1_4EJECT,		//4EJECT
	STEP1_3EJECT,		//3EJECT
	STEP1_2EJECT,		//2EJECT
	STEP1_1EJECT,		//1EJECT
	}STEP1_TYPE; 
	
//6 STEP MODE 
typedef enum{
	STEP6_ALL_LOCK =1,
	STEP6_A_ALL_EJECT,
	STEP6_B_ALL_EJECT,
	STEP6_C_ALL_EJECT,	
	}STEP6_TYPE; 
	
//2 SETP MODE
typedef enum{
	STEP2_4PLAY=1,		//4PLAY
	STEP2_Disc_VIEW,	//DISC VIEW
	STEP2_5EJECT,		//5EJECT
	STEP2_3EJECT,		//3EJECT
	STEP2_2EJECT,		//2EJECT
	STEP2_1EJECT,		//1EJECT
	}STEP2_TYPE; 

//3 SETP MODE
typedef enum{
	STEP3_3PLAY=1,		//3PLAY
	STEP3_Disc_VIEW,	//DISC VIEW
	STEP3_5EJECT,		//5EJECT
	STEP3_4EJECT,		//4EJECT
	STEP3_2EJECT,		//2EJECT
	STEP3_1EJECT,		//1EJECT
	}STEP3_TYPE; 

//4 SETP MODE
typedef enum{
	STEP4_2PLAY=1,		//2PLAY
	STEP4_Disc_VIEW,	//DISC VIEW
	STEP4_5EJECT,		//5EJECT
	STEP4_4EJECT,		//4EJECT
	STEP4_3EJECT,		//3EJECT
	STEP4_1EJECT,		//1EJECT
	}STEP4_TYPE; 

//5 SETP MODE
typedef enum{
	STEP5_1PLAY=1,		//1PLAY
	STEP5_Disc_VIEW,	//DISC VIEW
	STEP5_5EJECT,		//5EJECT
	STEP5_4EJECT,		//4EJECT
	STEP5_3EJECT,		//3EJECT
	STEP5_2EJECT,		//2EJECT
	}STEP5_TYPE; 
	
	
//operation tray status.
typedef enum{
		
	FDISC_TRAY_INIT=1,
	FDISC_TRAY_BUSY,
	FDISC_TRAY_OPEN,
	FDISC_TRAY_CLOSE,
	FDISC_TRAY_DETE_DISC,
	FDISC_TRAY_PLAY,
	FDISC_TRAY_DISC_VIEW,
	FDISC_TRAY_RESET,	
	FDISC_TRAY_FINISH,//9
		
	}FDISC_TRAY_TYPE;

//motor MM status.
typedef enum{
	
	MOTOR_STOP,			//MM STOP 
	MOTOR_PLUS_ROTATE,	//MM + ROTATE
	MOTOR_DEC_ROTATE,	//MM - ROTATE
	}MOTOR_STATUS;

//funger status
typedef enum{
	
	PLUNGER_OFF,		//SET PLUNGER LOW
	PLUNGER_ON,			//SET PLUNGER HIGH
		
	}FLUNGER_STATUS;

typedef enum{
	OPER_DISC_IDLE = 0,
	JUMP_DISC ,
#ifdef SUPPORT_5DISC_ALL_EJECT
	ALL_OPEN ,	
#endif	
	INDIVIDUAL_OPEN,
	FDISC_EXCHANGE,
	
	}OPER_MODE;

//set step pos,exchange.
typedef enum{
	STEP_RUN_IDLE =0,
	SEARCH_MIDDLE_STEP,
	SEARCH_PHOTO,
	STEP_PHOTO_COUNTER,
	WAIT_PHOTO_HIGH_TO_LOW_1,
	WAIT_PHOTO_LOW_TO_HIGH,
	WAIT_PHOTO_HIGH_TO_LOW_2,
	STEP_RUN_FINISH,
	
	}STEP_RUN;	
//set waiting close,exchange
typedef enum{
	WAITCLOSE_IDLE=0,
	WAITCLOSE_SW6_HIGH,
	WAITCLOSE_SW8_LOW,
	WAITCLOSE_SW6_LOW,	
	WAITCLOSE_FINISH,
	
	}WAIT_CLOSE;	
	
typedef enum{
	WAITEJECT_IDLE=0,
	WAITEJECT_SW8_HIGH,
	WAITEJECT_SW6_LOW,
	WAITEJECT_FINISH,
	
	}WAIT_EJECT;	
	
//set waiting close,exchange
typedef enum{
		EXCHANGE_IDLE=0,
		EXCHANGE_CLOSE,
		EXCHANGE_OPEN,
		
	}EXCHANGE_TYPE;	

enum {
 FDISC_NORMAL_DISC	=0,
 FDISC_CHANGE_DISC  ,
 FDISC_DETECT_DISC  ,
};
	
void set_exchange(unsigned char set);
unsigned char is_exchange(void);
void init_5disc_driver(void);
unsigned char is_tray_out(void);
unsigned char is_tray_middle(void);
unsigned char is_play_position(void);
void set_mm_run(unsigned char run_forward);
unsigned char get_middle_pos_for_step_left_border(STEP_TYPE step_type);

BYTE set_step_positon(STEP_TYPE set_step_type,unsigned char sub_step_fun);
unsigned char get_step_pos_number(STEP_TYPE step_type);
unsigned char is_run_forward(STEP_TYPE step_type);
void ALL_Eject_Waiting(void);
void ALL_CLOSE_Waiting(void);

void set_tray_in(void);
void set_loader_up(void);
void set_tray_out_from_load_to_middle(void);
void set_tray_out(void);
void set_loader_down(void);
void set_tray_in_from_middle_to_loader(void);
void set_tray_stop(void);

void delay_5disc_1ms(void);
void delay_5disc_ms(int mstime);
void set_5disc_tray_timeout_time(int set);
unsigned char get_5disc_tray_timeout_end(void);
void polling_fdisc_tray_timeout_time(void);
int init_5disc_tray(void);
void Eject_Handle(STEP_TYPE step_type,unsigned char eject_type);
void Close_Handle(STEP_TYPE step_type,unsigned char no_close_key);

#ifdef SUPPORT_5DISC_ALL_EJECT
	int ALL_Close_Handle(void);
	void ALL_Eject_Handle(void);
#endif

void polling_5disc_control(void);
void polling_5disc_control_500ms();//chenzhao20060107
void detect_disc(STEP_TYPE step_type,unsigned char sub_step_type);
void detect_all_disc(void);
unsigned char is_no_disc(void);
unsigned char get_disc_number(BYTE disN);
void set_play_step(unsigned char disN);
void set_tray_to_close(void);
void set_tray_to_middle(void);
void Play_Handle(unsigned char disN);
void Individual_CLOSE_Waiting(void);
void Individual_Eject_Waiting(void);
int Individual_CLOSE_Handle(void);
void Individual_Eject_Handle(void);

void set_exchange_command(void);
void set_oper_idle_command(void);
void set_jump_disc_command(void);
void set_all_open_command(void);
void set_individual_open_command(void);
void polling_5disc_oper(void);
void set_skip_disc(unsigned char disN);
unsigned char is_same_disc(unsigned char disN);
unsigned char get_is_all_eject(void);
unsigned char tray_oper_finish(void);
void set_current_disc(void);
unsigned char disc_in_slot(BYTE disN);

void set_jump_disc_mode(void);
void set_clear_jump_disc_mode(void);
unsigned char is_jump_disc_mode(void);
void skip_disc_func(void);
void Hand_Sense_Handle(void);
void reset_5disc_tray(void);
void Exchange_Handle(void);
unsigned char turn_on_5disc_led(BYTE Off_Led);
void VolumeEncoder(void);
BYTE set_step_postion_polling(STEP_TYPE steptype,BYTE substepNumber);
void Exchange_Handle_WaitClose_Polling(void);
void Exchange_Handle_WaitEject_Polling(void);
void init_exchange_operate(void);
void standby_to_close_fun(void);
void test_disc(void);
void hand_sense_polling_500ms(void);
#ifdef OPEN_OR_CLOSE_ERROR_TO_POWER_OFF
void set_tray_error_poweroff_time(BYTE time);
void tray_error_auto_power_off_polling_500ms(void);
#endif 
#ifdef STOP_SERVO_IN_OTHER_MODE
void call_loader_to_stop_polling_500ms(void);
#endif 
extern BYTE hand_sense_flag;

#endif


