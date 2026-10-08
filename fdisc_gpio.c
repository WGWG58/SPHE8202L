#include "user_init.h"
#include "config.h"
#include "global.h"
#include "gpio.h"
#include "fdisc_gpio.h"
#include "rom_bus_io.h"



//#define	FDISC_DB

#define SET_INTPUT_PORT

#ifdef SET_INTPUT_PORT
	#define IO_SET	0	//INPUT PORT
#else
	#define IO_SET	1	//OUTPUT PORT	
#endif

void reset_5disc_gpio(void)
{
	
#ifndef USE_ROM_BUS_CONTROL_FLUNGER	
	//========SET(8202_256pin) PIN77 OUTPUT PORT ================
	regs0->sft_cfg1 &= ~(0x1 << 2);	//FDISC SOL +/-	
	GPIO_M_SET(FDISC_FLUNGER_GPIO,1);
	GPIO_E_SET(FDISC_FLUNGER_GPIO,1);
#endif	
	set_5disc_plunger_status(0);	

	//========SET(8202_256pin) PIN59 OUTPUT PORT ================
	regs0->sft_cfg4 &= ~(0x1 << 2);	//FDISC MM-
	GPIO_M_SET(FDISC_DEC_MM_GPIO,1);
	GPIO_E_SET(FDISC_DEC_MM_GPIO,1);
	set_5disc_control_2(0);
	
	//========SET(8202_256pin) PIN60 OUTPUT PORT ================
	regs0->sft_cfg4 &= ~(0x1 << 3);	//FDISC MM+
	GPIO_M_SET(FDISC_PLUS_MM_GPIO,1);
	GPIO_E_SET(FDISC_PLUS_MM_GPIO,1);	
	set_5disc_control_1(0);
	
	//========SET(8202_256pin) PIN62 INPUT PORT =================
	regs0->sft_cfg4 &= ~(0x1 << 5); //FDISC PHOTO
	GPIO_M_SET(FDISC_PHOTO_GPIO,1);
	GPIO_E_SET(FDISC_PHOTO_GPIO,IO_SET);
	
	//========SET(8202_256pin) PIN78 INPUT PORT =================
	regs0->sft_cfg1 &= ~(0x1 << 1); //FDISC_SW8
	GPIO_M_SET(FDISC_SW8_GPIO,1);
	GPIO_E_SET(FDISC_SW8_GPIO,IO_SET);	

	//========SET(8202_256pin) PIN225/PIN67 INPUT PORT ==========
	GPIO_M_SET(FDISC_SW4_GPIO,1);		//FDISC SW3
	GPIO_E_SET(FDISC_SW4_GPIO,IO_SET);	
	
	//========SET(8202_256pin) PIN226/PIN68 INPUT PORT ==========
	GPIO_M_SET(FDISC_SW3_GPIO,1);		//FDISC SW4
	GPIO_E_SET(FDISC_SW3_GPIO,IO_SET);	

	//========SET(8202_256pin) PIN227/PIN69 INPUT PORT ==========
	GPIO_M_SET(FDISC_SW5_GPIO,1);		//FDISC SW5
	GPIO_E_SET(FDISC_SW5_GPIO,IO_SET);	

	//========SET(8202_256pin) PIN227/PIN71 INPUT PORT ==========
	GPIO_M_SET(FDISC_SW6_GPIO,1);		//FDISC SW6
	GPIO_E_SET(FDISC_SW6_GPIO,IO_SET);	

	//========SET(8202_256pin) PIN231/PIN72 INPUT PORT ==========
	GPIO_M_SET(FDISC_SW2_GPIO,1);		//FDISC SW2
	GPIO_E_SET(FDISC_SW2_GPIO,IO_SET);		

	//========SET(8202_256pin) PIN232/PIN73 INPUT PORT ==========
	GPIO_M_SET(FDISC_SW1_GPIO,1);		//FDISC SW1
	GPIO_E_SET(FDISC_SW1_GPIO,IO_SET);		

	//========SET(8202_256pin) PIN233/PIN75 INPUT PORT ==========
	GPIO_M_SET(FDISC_SW7_GPIO,1);		//FDISC SW7
	GPIO_E_SET(FDISC_SW7_GPIO,IO_SET);		
}	

//================= comment ====================================================================================
//	a. control_1: Drawer out/up
//	b. control_2: Drawer in/down
//	c. plunger  : Turn on/off electric current
//==============================================================================================================
//	a. when set_5disc_plunger_status(1) , + 12v 
//  b. when set_5disc_plunger_status(0) , 0 v
//	c. set below status for tray in/loader up in loader position,or from loader position to middle position move	
//		set_5disc_control_1(0);
//		set_5disc_control_2(1);
//	d. set below status for tray out/loader down in loader position,or from middle position to loader position move 
//		set_5disc_control_1(1);
//		set_5disc_control_2(0);
//	e. set below status for stop
//		set_5disc_control_1(0);
//		set_5disc_control_2(0);
//
//==============================================================================================================

//FDISC SOL +/-
void set_5disc_plunger_status(int set)
{
#ifdef FDISC_DB
	printf("5disc:  set_5disc_plunger_status      ... set= %d  \n",set);
#endif		

#ifdef USE_ROM_BUS_CONTROL_FLUNGER
	set_5disc_plunger(set);
#else
	GPIO_O_SET(FDISC_FLUNGER_GPIO,set);
#endif	
}
//FDISC MM + 
//if set = 1 ,then loader will run down
void set_5disc_control_1(int set)
{
#ifdef FDISC_DB
	printf("5disc:  set_5disc_control_1      ... set= %d  \n",set);
#endif	
	GPIO_O_SET(FDISC_PLUS_MM_GPIO,set);
}
//FDISC MM -
void set_5disc_control_2(int set)
{
#ifdef FDISC_DB
	printf("5disc:  set_5disc_control_2      ... set= %d  \n",set);
#endif	
	GPIO_O_SET(FDISC_DEC_MM_GPIO,set);	
}

//FDISC PHOTO / PH1 OUT
int get_5disc_photo_status(void)
{
	if(GPIO_I_GET(FDISC_PHOTO_GPIO))
	{
#ifdef FDISC_DB
		printf("5disc:  photo      ... 1  \n");
#endif	
		return 1;
	}
#ifdef FDISC_DB
		printf("5disc:  photo      ... 0  \n");
#endif	
	return 0;	
}
//FDISC DISC DETECT / PH2 OUT
int get_5disc_disc_detect_status(void)
{
	if(rom_ext_get_disc_dect_status())
	{
#ifdef FDISC_DB
		printf("5disc:  disc dect      ... 1  \n");
#endif	
		return 1;
	}
#ifdef FDISC_DB
		printf("5disc:  disc dect      ... 0  \n");
#endif	
	return 0;		
}	
//================= comment ====================================================================================
//	a. SW1-4: Set positions of step ( step 1-5),ALL LOCK, and Middle position.
//  b. SW5	: Carriage is on at Stock position.
//	c. SW6	: Eject Close is on, and Eject Open is on.
//	d. SW7	: Carriage Play position is on.
//  e. SW8	: Eject Close is on
//  f. PHOTO: Select Carriage on play mode and on Eject mode at each steps.


//FDISC_SW1
int get_5disc_sw1_status(void)
{
	if(GPIO_I_GET(FDISC_SW1_GPIO))
	{
#ifdef FDISC_DB
		printf("5disc:  sw1      ... 1  \n");
#endif	
		return 1;
	}
#ifdef FDISC_DB
		printf("5disc:  sw1      ... 0  \n");
#endif	
	return 0;			
}
//FDISC_SW2
int get_5disc_sw2_status(void)
{
	if(GPIO_I_GET(FDISC_SW2_GPIO))
	{
#ifdef FDISC_DB
		printf("5disc:  sw2      ... 1  \n");
#endif	
		return 1;
	}
#ifdef FDISC_DB
		printf("5disc:  sw2      ... 0  \n");
#endif	
	return 0;			
}
//FDISC_SW3
int get_5disc_sw3_status(void)
{
	if(GPIO_I_GET(FDISC_SW3_GPIO))
	{
#ifdef FDISC_DB
		printf("5disc:  sw3      ... 1  \n");
#endif	
		return 1;
	}
#ifdef FDISC_DB
		printf("5disc:  sw3      ... 0  \n");
#endif	
	return 0;			
}
//FDISC SW4
int get_5disc_sw4_status(void)
{
	if(GPIO_I_GET(FDISC_SW4_GPIO))
	{
#ifdef FDISC_DB
		printf("5disc:  sw4      ... 1  \n");
#endif	
		return 1;
	}
#ifdef FDISC_DB
		printf("5disc:  sw4      ... 0  \n");
#endif		
	return 0;		
}
//FDISC_SW5
int get_5disc_sw5_status(void)
{
	if(GPIO_I_GET(FDISC_SW5_GPIO))
	{
#ifdef FDISC_DB
		printf("5disc:  sw5      ... 1  \n");
#endif	
		return 1;
	}
#ifdef FDISC_DB
		printf("5disc:  sw5      ... 0  \n");
#endif	
	return 0;			
}
//FDISC_SW6
int get_5disc_sw6_status(void)
{
	if(GPIO_I_GET(FDISC_SW6_GPIO))
	{
#ifdef FDISC_DB
		printf("5disc:  sw6      ... 1  \n");
#endif	
		return 1;
	}
#ifdef FDISC_DB
		printf("5disc:  sw6      ... 0  \n");
#endif	
	return 0;			
}
//FDISC_SW7
int get_5disc_sw7_status(void)
{
	if(GPIO_I_GET(FDISC_SW7_GPIO))
	{
#ifdef FDISC_DB
		printf("5disc:  sw7      ... 1  \n");
#endif	
		return 1;
	}
#ifdef FDISC_DB
		printf("5disc:  sw7      ... 0  \n");
#endif	
	return 0;			
}	
//FDISC_SW8
int get_5disc_sw8_status(void)
{
	if(GPIO_I_GET(FDISC_SW8_GPIO))
	{
#ifdef FDISC_DB
		printf("5disc:  sw8      ... 1  \n");
#endif	
		return 1;
	}
#ifdef FDISC_DB
		printf("5disc:  sw8      ... 0  \n");
#endif	
	return 0;			
}

//for Test IO Port.
void set_io_port(int set)
{	
	GPIO_O_SET(FDISC_SW8_GPIO,set);	
	//GPIO_O_SET(FDISC_PHOTO_GPIO,set);	
	//GPIO_O_SET(FDISC_FLUNGER_GPIO,set);	
	//GPIO_O_SET(FDISC_DEC_MM_GPIO,set);	
	//GPIO_O_SET(FDISC_SW8_GPIO,set);	
}



