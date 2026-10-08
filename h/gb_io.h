//================================================================ vfd
#if defined(VFD_VOLUME_DISPLAY) || defined(SUPPORT_TUNER_MV114) || defined(SUPPORT_TUNER_ALPS)
EXTERN UINT16 timeout_vfd;
#endif
//================================================================ amp
#ifdef SUPPORT_AMP//2002-7-26 15:48
EXTERN BYTE amp_onoff_flag;
#endif
#if defined(PT2322)||defined(PT2320)
EXTERN BYTE middle_level;
EXTERN BYTE base_level;
EXTERN BYTE treble_level;
EXTERN BYTE front_level;
EXTERN BYTE center_level;
EXTERN BYTE rear_level;
EXTERN BYTE woofer_level;

/* freyman marked 2004-3-23 16:04 for no use any more
#ifdef SVA_SAMPLE
EXTERN BYTE lfront_level;
EXTERN BYTE rfront_level; 
EXTERN BYTE lrear_level;
EXTERN BYTE rrear_level;
#endif 
*/
#endif //defined(PT2322)||defined(PT2320)


// -------------------------------------------------------------
// Variables used for communicating with 8051, Robert 020729
#ifdef SUPPORT_UART_COMMAND // Support UART to communicate with external MCU


#ifdef NEW_UART_COMMAND
typedef void (*SHOWVFDVOL) ();
#endif

EXTERN BYTE nCurrentDVDMode; // indicate current mode (av1, av2, tuner or DVD)
EXTERN BYTE nCurrentVolMode; // indicate current volume mode (main, front, center, etc.)
#ifndef  NEW_UART_COMMAND     //lijinhai use define unmark confliting
EXTERN BYTE nMainVol;        // main volume value
EXTERN BYTE nFrontVol;       // front volume value
EXTERN BYTE nCenterVol;      // center volume value
EXTERN BYTE nRearVol;        // rear volume value
EXTERN int nMainLRBalance;   // front volume balance
EXTERN int nSurLRBalance;    // surround volume balance 
EXTERN BYTE nQSEffect;       // QS effect (0~7)
EXTERN BYTE nTreble;         // treble value 
EXTERN BYTE nBass;           // bass value 
#endif
#endif // SUPPORT_UART_COMMAND

#if defined(TOP_DOOR_LOADER)||defined(CHECK_PORTABLE_OPCLSW)
BYTE    bDoorStatus;
#endif //#ifdef TOP_DOOR_LOADER

#ifdef TEST_SERVO
EXTERN BYTE     iTestServoMode;
EXTERN UINT32   iTestServoCount;
#endif //#ifdef TEST_SERVO



