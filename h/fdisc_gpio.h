#ifndef FDISC_GPIO_H
#define FDISC_GPIO_H

#define	USE_ROM_BUS_CONTROL_FLUNGER


#ifndef USE_ROM_BUS_CONTROL_FLUNGER
	//========SET(8202_256pin) PIN77 OUTPUT PORT ======
	#define	FDISC_FLUNGER_GPIO	17			//FDISC SOL +/-
#endif

//========SET(8202_256pin) PIN59 OUTPUT PORT ======
#define	FDISC_DEC_MM_GPIO	68 //2			//FDISC MM -

//========SET(8202_256pin) PIN60 OUTPUT PORT ======
#define	FDISC_PLUS_MM_GPIO	69 //3			//FDISC MM +


//========SET(8202_256pin) PIN78 INPUT PORT ======
#define	FDISC_SW8_GPIO		18			//FDISC SW8

//========SET(8202_256pin) PIN62 INPUT PORT ======
#define FDISC_PHOTO_GPIO	5			//FDISC PHOTO

#ifdef FDISC_CONTROL_PORT_HAS_HDMI
	//========SET(8202_256pin) PIN67 INPUT PORT ===
	#define	FDISC_SW4_GPIO		9		//FDISC SW4
	
	//========SET(8202_256pin) PIN68 INPUT PORT ==
	#define FDISC_SW3_GPIO		10		//FDISC SW3

	//========SET(8202_256pin) PIN69 INPUT PORT ==
	#define FDISC_SW5_GPIO		11		//FDISC SW5

	//========SET(8202_256pin) PIN71 INPUT PORT ==
	#define FDISC_SW6_GPIO		12		//FDISC SW6	

	//========SET(8202_256pin) PIN72 INPUT PORT ==
	#define FDISC_SW2_GPIO		13		//FDISC SW2

	//========SET(8202_256pin) PIN73 INPUT PORT ==
	#define FDISC_SW1_GPIO		14		//FDISC SW1

	//========SET(8202_256pin) PIN75 INPUT PORT ==
	#define FDISC_SW7_GPIO		15		//FDISC SW7
#else 
	//========SET(8202_256pin) PIN225 INPUT PORT ==
	#define	FDISC_SW4_GPIO		92		//FDISC SW4
	
	//========SET(8202_256pin) PIN226 INPUT PORT ==
	#define FDISC_SW3_GPIO		93		//FDISC SW3

	//========SET(8202_256pin) PIN227 INPUT PORT ==
	#define FDISC_SW5_GPIO		94		//FDISC SW5

	//========SET(8202_256pin) PIN230 INPUT PORT ==
	#define FDISC_SW6_GPIO		97		//FDISC SW6

	//========SET(8202_256pin) PIN231 INPUT PORT ==
	#define FDISC_SW2_GPIO		98		//FDISC SW2

	//========SET(8202_256pin) PIN232 INPUT PORT ==
	#define FDISC_SW1_GPIO		99		//FDISC SW1

	//========SET(8202_256pin) PIN233 INPUT PORT ==
	#define FDISC_SW7_GPIO		100		//FDISC SW7
#endif 

void reset_5disc_gpio(void);
void set_5disc_plunger_status(int set);
//FDISC MM +
void set_5disc_control_1(int set);
//FDISC MM -
void set_5disc_control_2(int set);
//FDISC PHOTO
int get_5disc_photo_status(void);
//FDISC DISC DETECT 
int get_5disc_disc_detect_status(void);
//FDISC_SW1
int get_5disc_sw1_status(void);
//FDISC_SW2
int get_5disc_sw2_status(void);
//FDISC_SW3
int get_5disc_sw3_status(void);
//FDISC SW4
int get_5disc_sw4_status(void);
//FDISC_SW5
int get_5disc_sw5_status(void);
//FDISC_SW6
int get_5disc_sw6_status(void);
//FDISC_SW7
int get_5disc_sw7_status(void);
//FDISC_SW8
int get_5disc_sw8_status(void);

void set_io_port(int set);

#endif
