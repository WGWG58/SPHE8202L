#ifndef __SINF_H
#define __SINF_H

#include "types.h"
#define UCHAR   UINT8
#define UINT    UINT16
#define ULONG   UINT32

extern  UINT    servo_max_buffer;
extern  BYTE    *pTrackBuf;
extern  BYTE    *pServoUserInfo;
extern  UCHAR   cServoWrongDataPass;
extern  UINT    gbSrvFuncSW;// axelchen 2006/1/10 
extern  BYTE    gbEjectSpeed;
extern  BYTE    gbEjectSpeed1;
extern  BYTE    gbEjectSpeed2;
extern  BYTE    gbEjectSpeed3;
extern  BYTE    gbEjectSpeed4;
extern  BYTE 	gbTray_Out_Cnt;	
extern  BYTE 	gbTray_In_Cnt;	
extern  BYTE    gbTrayOutBrakeTimer;
//extern  BYTE	gbGPIO_TrigLED1;
#ifdef SPHE8202
extern  BYTE	gbGPIO_TrigLED1;
extern  BYTE    gbGPIO_TrayIsIn;//for 8202,cmchang
extern  BYTE    gbGPIO_TrayIsOut;//for 8202,cmchang
extern  BYTE    gbGPIO_TrayIsMid;//for 8202,cmchang
extern  BYTE    gbGPIO_DiscIsIn;//for 8202,hcchang
extern	BYTE	gbGPIO_LoadIn;//for 8202,hcchang
extern	BYTE	gbGPIO_LoadOut;//for 8202,hcchang
extern	BYTE	gbGPIO_SledIsOut;//for 8202,hcchang
#endif
extern 	BYTE	gbDebounce;

// setup CDDVD Mode
extern  void    SetCDDVDMode(void);

#ifdef DVD_SERVO    // 2005/02/15 yltseng
    extern  UINT    is_svo_dvd(void);
#else
    #define         is_svo_dvd()  1
#endif

#endif

