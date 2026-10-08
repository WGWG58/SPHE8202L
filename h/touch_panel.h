#ifndef _TSC2003_H
#define _TSC2003_H

void write_tsc2003(unsigned  char deviceadd,unsigned char command);
unsigned char read_tsc2003(unsigned char deviceadd);
void polling_tsc2003_10ms();
void polling_tsc2003_100ms();
void CalibrateTouchScreen();
void coordinate_exchange();

int   get_x_coordinate();
int   get_y_coordinate();
int   get_tem0();
int   get_tem1();
int   is_left();
int  store_tsc();
int  get_stored_tsc();
//void  osd_init_tsc(void);
void caculate_centerpoint();
int is_still_touched();

 #ifdef Touch_Panel_PQ063XRA    
int   is_touched();
int judge_operating_temp();
#endif

#endif



