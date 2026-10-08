#ifndef  __RADIO_MV114_H
#define  __RADIO_MV114_H


#define INC_SPEED_TIMES 1

#if 1
#define AM_FREQ_MAX  1620
#define AM_FREQ_MIN  522
#define AM_STEP  9
#endif
#if 0
#define AM_FREQ_MAX  1620
#define AM_FREQ_MIN  520
#define AM_STEP  10
#endif

#define FM_FREQ_MIN  8750 
#define FM_FREQ_MAX  10800 
#define FM_STEP  5  /*50kHz*/


#define SEARCHADD  1
#define SEARCHDEC  2

#define AUTOSEARCHUP 1
#define AUTOSEARCHDOWN 2


#define NO_MEM_MODE     0
#define MEM_MODE        1 

#define RECALL_STATION  1
#define STORAGE_STATION 2

#define NORMAL_TUNE     1
#define RECALL_OR_STORE 2

#define AUTO_SEARCH     3    //2004-7-27
#define FREQ_DIRECT_CALL 4

#if defined(XINGQIU_DVD_RECEIVER)
#define MAX_MEM_BAND  50//xyy 2004-5-24
#else
#define MAX_MEM_BAND  20
#endif
#define MIN_MEM_BAND  1

/*start point from 24c02*/
//#define TUNER_START 128 moved to e2prom_map.h.chenzhao20050622

typedef struct
{
/*
* default memory band  
*/
	BYTE memory_status;
	BYTE bandswitch;                /*0,fm;1,am*/
	BYTE st_mono;                    /*0--mono ; 1--st*/
	//BYTE Istuning[2];
	//BYTE in2_data1;
	BYTE fm_ch;
	BYTE am_ch;
	UINT16 fmfreq[MAX_MEM_BAND];
	UINT16 amfreq[MAX_MEM_BAND];
	
	UINT16 ambak;
	UINT16 fmbak;   
	UINT16 checksum;
} t_tuner;
t_tuner tuner;

void   tuner_main(void);

void init_tuner_var(void);
void search(BYTE search_status);
void Fmautosearch( BYTE );
void Amautosearch( BYTE );
void tuner_auto_search( void );
void save_tuner_E2PROM(void);
void load_tuner_E2PROM(void);
void tuner_st_mono(void);
void radio_key_input(BYTE num);
void call_ir_func_tuner(BYTE rx);
void auto_search_all_am();
void auto_search_all_fm();

void radio_key_mute();
void radio_key_rds();
void radio_key_search_up();
void radio_key_search_down();
void radio_key_prev_station();
void radio_key_next_station();
void radio_key_mono_st();
void radio_key_am_fm();
void radio_key_auto();
void radio_key_memory();
void radio_key_number(BYTE station)    ;
void radio_key_input(BYTE num);
BYTE look_up_radio_key(BYTE rx);
void radio_key(BYTE key);

void disfreq(void);
void output_vfd_msg(void);
void vfd_set_freq();
void vfd_set_stationNm();
void vfd_set_band();
void vfd_set_st_mono();
void vfd_set_tuner_select_number_state();
void vfd_set_tuner_stereo_state();
void vfd_clear_tuner_stereo_state();
void set_vfd_timeout();


#ifdef SUPPORT_RDS_FUNCTION
void disp_rds(BYTE enter_flag);
void disp_rds_func(BYTE enter_flag);
#endif



#endif

