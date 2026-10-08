#ifndef __CLOCK_FUNC_H_
#define __CLOCK_FUNC_H_

/*****************************************************\
Creater: xiongyuyue
Date   : 2004-10-11
Description: for oritron power receiver clock function
             when the system enter into standby mode.
\*****************************************************/

#define PCF8563 0xa2

//register define
#define CONTRL1  0x00   //bit7--bit0: TEST  0  STOP  0  TESTC  0  0  0
#define CONTRL2  0x01   //bit7--bit0: 0  0  0  TI/TF  AF  TF  AIE  TIE

#define SECONDS  0x02   //current seconds value coded in BCD format 00--59
#define MINUTES  0x03   //current minutes value coded in BCD format 00--59
#define HOURS    0x04   //current hours value coded in BCD format   00--23

#define RTC_NORMAL 0x00
#define RTC_SET  0x01

#define RTC_DISP  0
#define RTC_INPUT 1

BYTE uRtcMode;
BYTE uInputIndex;

BYTE uRtcTimeHour;
BYTE uRtcTimeMin;
BYTE uRtcTimeSec;

BYTE uRtcState;
UINT32 uTimeSetVal;


#endif


