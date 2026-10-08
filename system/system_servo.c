/*
*  Terry,2004/1/28 09:51AM
*/

#if defined(IC_8202L)//terry,2006/4/7 04:59¤U¤È
    #define TRAY_IS_IN_GPIO		7
	#define TRAY_IS_OUT_GPIO	8
	#define SRV_TRIG_GPIO		15  //pin65
#elif defined(SPHE8202) //define 8202 SERVO TRAY SENSOR,cmchang
	#ifdef EMU_BOARD_256_SHARE
		        #define TRAY_IS_IN_GPIO		84
		        #define TRAY_IS_OUT_GPIO	85
	
	#elif defined(EMU_BOARD_216_PIN)
			
			#define DISC_IS_IN_GPIO		8
			#define TRAY_IS_IN_GPIO		9
			#define TRAY_IS_OUT_GPIO	10
			#define SRV_TRIG_GPIO		70
	#elif defined(EMU_BOARD_256_NON_SHARE)
			
	#elif defined(MP_BOARD_256_PIN_NON_SHARE)
			#ifdef PORTABLE_DVD
                #ifdef TR0QS3_SLM
				#define TRAY_IS_IN_GPIO 	 100  //99	//pin232
				#define TRAY_IS_OUT_GPIO	 99 //98 //pin231
				#define DISC_IS_STANDBY_GPIO 98	
				#define DISC_IS_IN_GPIO	     97
				#define SLED_IS_OUT_GPIO     93
                #else
				#define TRAY_IS_IN_GPIO 	6  //99	//pin232
				#define TRAY_IS_OUT_GPIO	18 //98 //pin231		
				#define SRV_TRIG_GPIO		97  //pin230
				#endif
			#else
				#define TRAY_IS_IN_GPIO 	5
				#define DISC_IS_IN_GPIO		8
				#define TRAY_IS_OUT_GPIO	18		
				#define SRV_TRIG_GPIO		97  //pin230
			#endif
	#elif defined(MP_BOARD_216_PIN_NON_SHARE)//kenny 2004/7/14
			#define TRAY_IS_IN_GPIO		70
			#define TRAY_IS_OUT_GPIO	71
			#define SRV_TRIG_GPIO		15  //pin65
	#elif defined(MP_BOARD_216_PIN)
			#define TRAY_IS_IN_GPIO		70
			#define TRAY_IS_OUT_GPIO	71
			
	#elif defined(MP_BOARD_256_PIN_SHARE)
			#define TRAY_IS_IN_GPIO		5
			#define TRAY_IS_OUT_GPIO	18		
	
	
	#endif

	#if defined(PORTABLE_DVD)
		//#define LOAD_IN_GPIO		56
		//#define LOAD_OUT_GPIO		55
		#define DISC_IS_IN_GPIO		55  //100
	#endif

//#else //define 8200 SERVO TRIGER GPIO
	//#define SRV_TRIG_GPIO		14
#endif


static inline void system_init_servo_var(void)
{
#ifdef DVD_SERVO
#ifdef PREAMP_GPIO_ENABLE
	gbSrvFuncSW = 0x01;
#else
	gbSrvFuncSW = 0x00;
#endif

#ifdef TRAY_AVAILABLE
	gbSrvFuncSW |= 0x02;
#endif
#ifdef DISC_TYPE_RETRY
	gbSrvFuncSW |= 0x04;	
#endif
#ifdef CHANGE_TRAY_DIRECTION_FUNC
	gbSrvFuncSW |= 0x08;
#endif
#ifdef POWER_ON_TOPDOOR_PRESTOP
	gbSrvFuncSW |= 0x10;
#endif
#ifdef POWER_ON_SERVO_STARTUP
	gbSrvFuncSW |= 0x20;
#endif
#ifdef PH0PH0_STD
	gbSrvFuncSW |= 0x40;
#endif
#ifdef STOP_LOADER_WHEN_NO_DVD_MODE//#ifdef POWER_ON_SERVO_STOP //yangli ,axel 2006/1/10 for power_on, servo enters sleep.
   	gbSrvFuncSW |= 0x100;
#endif
#ifdef POWER_ON_SERVO_STOP //axel 2006/1/10 for power_on, servo enters sleep.
	gbSrvFuncSW |= 0x100;
#endif

#ifdef NEW_DEBOUNCE_COUNTER
	gbDebounce = NEW_DEBOUNCE_COUNTER;
#endif

// SERVO Eject Speed
#ifdef TRAY_SPEED
gbEjectSpeed = TRAY_SPEED;
#endif

#ifdef TRAY_OUT_SPEED1
gbEjectSpeed1 = TRAY_OUT_SPEED1;
#endif

#ifdef TRAY_OUT_SPEED2
gbEjectSpeed2 = TRAY_OUT_SPEED2;
#endif

#ifdef TRAY_IN_SPEED1
gbEjectSpeed3 = TRAY_IN_SPEED1;
#endif

#ifdef TRAY_IN_SPEED2
gbEjectSpeed4 = TRAY_IN_SPEED2;
#endif

#ifdef TRAY_OUT_CNT
gbTray_Out_Cnt = TRAY_OUT_CNT;
#endif

#ifdef TRAY_IN_CNT
gbTray_In_Cnt = TRAY_IN_CNT;
#endif

#ifdef TRAY_OUT_BRAKE_TIMER
gbTrayOutBrakeTimer=TRAY_OUT_BRAKE_TIMER;
#endif

// 8202 SERVO TRAY Sensor,cmchang
#ifdef TRAY_IS_IN_GPIO
    gbGPIO_TrayIsIn = TRAY_IS_IN_GPIO;
#endif
#ifdef TRAY_IS_OUT_GPIO
    gbGPIO_TrayIsOut = TRAY_IS_OUT_GPIO;
#endif
#ifdef DISC_IS_IN_GPIO
    gbGPIO_DiscIsIn = DISC_IS_IN_GPIO;
#endif

#ifdef DISC_IS_STANDBY_GPIO
    gbGPIO_TrayIsMid = DISC_IS_STANDBY_GPIO;
#endif

#ifdef SLED_IS_OUT_GPIO
    gbGPIO_SledIsOut = SLED_IS_OUT_GPIO;
#endif

// 8202 SERVO DeBUG LED2, longson
#ifdef SRV_TRIG_GPIO
	gbGPIO_TrigLED1 = SRV_TRIG_GPIO;
#endif

#endif

// 8202 SERVO LOAD IN/OUT GPIO  2004/07/20/hcchang
#ifdef LOAD_IN_GPIO
    gbGPIO_LoadIn = LOAD_IN_GPIO;
#endif
#ifdef LOAD_OUT_GPIO
    gbGPIO_LoadOut = LOAD_OUT_GPIO;
#endif

// 8202 Servo Table
#ifdef SPHE8202
	extern BYTE (*_gpbEQSetting)[4];
	
	#if defined (IC_SUPPORT_SERVO_EXTERNAL_EQ_TABLE_8202D)
	extern BYTE _gpbEQ_PS2P5[][4];
	_gpbEQSetting = _gpbEQ_PS2P5;
	#elif defined (IC_SUPPORT_SERVO_EXTERNAL_EQ_TABLE_8202E)
	extern BYTE _gpbEQ_PJ8202A[][4];
	_gpbEQSetting = _gpbEQ_PJ8202A;
	#elif defined (IC_SUPPORT_SERVO_EXTERNAL_EQ_TABLE_LEGACY)
	if (regs0->stamp==0x82)	// PS2.1
	{
		extern BYTE _gpbEQ_PS2P1[][4];
		_gpbEQSetting = _gpbEQ_PS2P1;
	}
	else	// PA8202A
	{
		extern BYTE _gpbEQ_PA8202[][4];
		_gpbEQSetting = _gpbEQ_PA8202;
	}
	#endif
#endif
	
//------------------Slot-in--------------//TEAC
#ifdef TEAC_PORTABLE_DVD
	gbGPIO_TrayIsMid = GPIO_SW_A;
	gbGPIO_TrayIsIn	 = GPIO_LDCMPLT;
	gbGPIO_TrayIsOut = GPIO_EJCMPLT;
	gbGPIO_DiscIsIn  = GPIO_PRELOAD;
	gbGPIO_SledIsOut = GPIO_OUT_SW;	
#endif	
//---------------------------------------	

}

// SERVO_LIGHT hcchang
// 2005/04/03 yltseng, to eliminate warning message
UCHAR DecFunctionNull() {return 0;}

#ifdef SUPPORT_CD_TEXT
extern void CheckCDText_(void);
extern void InitCDText_(void);
extern void ReadCDText_(void);
void (* CheckCDText)() = CheckCDText_;
void (* InitCDText)() = InitCDText_;
void (* ReadCDText)() = ReadCDText_;
#else
void (* CheckCDText)() = (void *)DecFunctionNull;
void (* InitCDText)() = (void *)DecFunctionNull;
void (* ReadCDText)() = (void *)DecFunctionNull;
#endif

#if defined(SUPPORT_CDG) && !defined(SUPPORT_ECC)
extern UCHAR CDSubCodeProc_(void);
extern void CDSubCodeBackUp_(void);
extern void CDSubCodeECCInit_(void);
extern void CDSubCodeECCClear_(void);
UCHAR (* CDSubCodeProc)()       = CDSubCodeProc_;
void (* CDSubCodeBackUp)()      = CDSubCodeBackUp_;
void (* CDSubCodeECCInit)()     = CDSubCodeECCInit_;
void (* CDSubCodeECCClear)()    = CDSubCodeECCClear_;
#else
UCHAR (* CDSubCodeProc)()       = DecFunctionNull;
void (* CDSubCodeBackUp)()      = (void(*)())DecFunctionNull;
void (* CDSubCodeECCInit)()     = (void(*)())DecFunctionNull;
void (* CDSubCodeECCClear)()    = (void(*)())DecFunctionNull;
#endif

#ifdef SERVO_LIGHT
UCHAR (* DecOptionalFunc1)()    = DecFunctionNull;
void (* DecOptionalFunc2)()     = (void(*)())DecFunctionNull;
void (* DecOptionalFunc3)()     = (void(*)())DecFunctionNull;
void (* DecOptionalFunc4)()     = (void(*)())DecFunctionNull;
void (* DecOptionalFunc5)()     = (void(*)())DecFunctionNull;
void (* DecOptionalFunc6)()     = (void(*)())DecFunctionNull;

#else
extern UCHAR DecOptionalFunc1a();
extern void DecOptionalFunc2a();
extern void DecOptionalFunc3a();
extern void DecOptionalFunc4a();
extern void DecOptionalFunc5a();
extern void DecOptionalFunc6a();

UCHAR (* DecOptionalFunc1)()    = DecOptionalFunc1a;
void (* DecOptionalFunc2)()     = DecOptionalFunc2a;
void (* DecOptionalFunc3)()     = DecOptionalFunc3a;
void (* DecOptionalFunc4)()     = DecOptionalFunc4a;
void (* DecOptionalFunc5)()     = DecOptionalFunc5a;
void (* DecOptionalFunc6)()     = DecOptionalFunc6a;
#endif

//-----------------------------------------ending----------------------------------------------

