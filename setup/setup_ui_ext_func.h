/*
*  Terry,2004/3/28 05:00PM
*/

void ShowCUSTMMsg(void);
void setup_SetDTSDOWNMIXConfig();

#ifdef SETUP_PASSWORD_GUI
BYTE passwdGUI_state = NO_GUI_STATE;//record the current state in password GUI
#endif//SETUP_PASSWORD_GUI


#include "one_key_pass.h"


#ifdef SCART_TV_5	//wangfeng 2003-12-3 16:49
extern void SetScartTV5();
extern void ReSetScartTV5();
#endif
#ifdef TONIC_DVD
int ShowPasswordErr;
#endif//TONIC

#ifdef PROLOGICII_3D_MUTEX
extern BYTE soundGetSurroundType(void);
extern BYTE soundGetEQType(void);
extern BYTE soundGetEQType(void);
#endif//PROLOGICII_3D_MUTEX

#ifdef SHOW_STANDBY_TIMER  //suqiaoli  add 8-13
extern void exe_standby_timer(void);
extern void polling_setup_standby_timer(void);
extern void reset_standby_timer_pos(void);
#endif

#ifdef SUPPORT_FUNCTION_MENU
//#ifdef SUPPORT_SPI
void show_FW_MCU_servoV(void);
//#endif
#endif

