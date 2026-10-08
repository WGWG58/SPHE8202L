//Kenny 2002/7/16 for UART to communicate with external MCU

#include "global.h"
#include "uart.h"
#include "uartfifo.h"
#include "osd.h"
#include "iop.h"
#include "setup.h"
#include "UartTxd.h"
#include "func.h"
#include "user_init.h"

//#define OSD_DBG_TXD
//#define UART_DBG_TXD

/////////////////////////////////////////////////////////////
// Maybe software UART would be used to communicate with 8051.
// Now I use it to print debug message.

#ifdef SOFT_UART_OUT
extern int PutSoftUartChar(BYTE *, int);
extern int GetSoftUartChar(BYTE *, int);

#define PutString(x, y) PutSoftUartChar(x, y)
#define GetString(x, y) GetSoftUartChar(x, y)

#else

#define PutString(x, y) 0
#define PutString(x, y) 0

#endif
//////////////////////////////////////////////////////
#ifdef SERVO_UART
extern UINT8 gcRS232Data[5];
extern UINT8 gwWPtr;
extern UINT8 cReveiveRs232,cTranRs232;

void reset_uart_servo(void)
{
    UART1_set_baudrate(UART_BAUD_88200);
    //UART1_set_baudrate(UART_BAUD_44100);
}


extern void RS232SevoLink(UINT8 cmd);

int pollingUARTServo(void)
{

#if 0
	if ( cTranRs232==1 )
	{
	     cTranRs232 = 0;
		
         gcParam0 = 0x00;//UL_BYTE3(dwTargetPBA);
         gcParam1 = 0x0a;//UL_BYTE2(dwTargetPBA);
         gcParam2 = 0x00;//UL_BYTE1(dwTargetPBA);
         gcParam3 = 0x00;//UL_BYTE0(dwTargetPBA);
		 
		 //RS232SevoLink(55);	 // Start-Up
		 RS232SevoLink(11);	 // Seek

		 return 0;
	}
#endif

  while (UART1_rx_rdy())
  {
      gcRS232Data[gwWPtr] = (regs0->uart1_data);
	  //printf("Rcv : %x\n",gcRS232Data[gwWPtr]);
	  //io_write("R");			 
	  if (gwWPtr >= 2)
	  {
			cReveiveRs232 = 1;
			gwWPtr = 0;	
			//io_write("U2\n");			 
	  }
	  else
	  {
			cReveiveRs232 = 0;
		    gwWPtr ++;
	  }
  }

	return 0;
}
#endif								  


#ifdef SUPPORT_UART_COMMAND

#ifndef NEW_UART_COMMAND   //CONTROL VALUE
int	nInputLevel = 0;
BYTE aryCommandBuf[UART_REV_MAX_BYTE];
BYTE aryTXDBuf[UART_TXD_MAX_BYTE];

int nCommandIndex = 0;
int nCommandSize;

// for sending
#ifdef UART_DBG_TXD
BYTE aryDbgBuf[UART_REV_MAX_BYTE];
#endif

// temporary initialize some global variables here. The values should be set from 51
BYTE nCurrentDVDMode = MODE_DVD;
BYTE nCurrentVolMode = VOL_MODE_MAIN;
BYTE nMainVol = 8;
BYTE nFrontVol = 8;
BYTE nCenterVol = 8;
BYTE nRearVol = 8;
int nMainLRBalance = 0;
int nSurLRBalance = 0;
BYTE nQSEffect = 4;
BYTE nTreble = 8;
BYTE nBass = 8;

#else    //NEW UART CONTROL VALUE

int	nInputLevel = 0;
BYTE aryCommandBuf[UART_REV_MAX_BYTE];
BYTE aryTXDBuf[UART_TXD_MAX_BYTE];

int nCommandIndex = 0;
int nCommandSize;

// for sending
#ifdef UART_DBG_TXD
BYTE aryDbgBuf[UART_REV_MAX_BYTE];
#endif

// temporary initialize some global variables here. The values should be set from 51
BYTE nCurrentDVDMode = MODE_DVD;
BYTE nCurrentVolMode = VOL_MODE_MAIN;
BYTE nMainVol = MAINVOL;
int  nFrontVol = FRONTVOL;
int  nCenterVol = CENTERVOL;
int  nRearVol = REARVOL;
int  nSubwooferVol=SUBWOOFERVOL;
int nMainBalance_L= MAINBALANCE_L;
int nMainBalance_R= MAINBALANCE_R;
int nSurBalance_L= SURBALANCE_L;
int nSurBalance_R= SURBALANCE_R;
BYTE nQSEffect = QSEFFECT;
int nTreble = TREBLEVOL;
int nBass = BASSVOL;
#endif       //END IF DEFINE VALUE
void uart_io_write_wait(const char *s);

#define hex2asc(x) (((x)>=10)?(x)+'A'-10:(x)+'0')

char asc2hex(char c)
{
    if ((c >= '0') && (c < '9' + 1))
        return c - '0';
    if ((c >= 'A') && (c < 'F' + 1))
        return c - 'A' + 10;
    if ((c >= 'a') && (c < 'f' + 1))
        return c - 'a' + 10;
    return 0;
}


void uart_io_write_wait(const char *s)
{
    int  c;
    while ((c = *s++) != 0)
    {
        IO_PUTC_WAIT(c);
    }
}


#define	UART_PUTS(s...) \
	do { \
	   psprintf(linebuf, ##s); uart_io_write_wait(linebuf); \
	} while (0)

#define	TO_8051_PUTS(s...) \
	do { \
	   psprintf(linebuf, "X %s",##s); uart_io_write_wait(linebuf); \
	} while (0)


void putdec(char c)
{
    if (c >= 100)
    {
        UART_PUTC(hex2asc(c / 100));
        c = c % 100;
    }
    if (c >= 10)
    {
        UART_PUTC(hex2asc(c / 10));
        c = c % 10;
    }
    else
        UART_PUTC('0');
    UART_PUTC(hex2asc(c));
}

void puthex(BYTE b)
{
    UART_PUTS(" 0x");
	UART_PUTC(hex2asc(b >> 4));
	UART_PUTC(hex2asc(b & 0xF));
	UART_PUTC(' ');
}

void reset_uart(void)
{
    //UART1_set_baudrate(UART_BAUD_115200);
    UART1_set_baudrate(UART_BAUD_9600);
}

void Inform_MCUOK(void)
{// send power-on command to 8051
	//BYTE i;           //we send 10 times
	// for(i=0;i<5;i++)
    // {  
	UART_PUTC_EXACT(COMMAND_START);
	UART_PUTC_EXACT(POWER_ON);
	UART_PUTC_EXACT(POWER_ON_OK);
	UART_PUTC_EXACT(COMMAND_END);     
	//delay_1ms(10);
    //} 
} 
int pollingUART51(void)
{
    while (!IsUARTRxEmpty())
    {
        BYTE c = UART_GETC();
		
        PutString(&c, 1);
		
        switch (nInputLevel)
        {
        case 0:
            if (COMMAND_START == c)
            {
                nInputLevel = 1;
                nCommandIndex = 0;
                nCommandSize = 0;
            }
            break;
			
        case 1:
            if ((COMMAND_END == c) || (nCommandIndex >= UART_REV_MAX_BYTE))
            {
                nInputLevel = 0;
                nCommandSize = nCommandIndex;
                return 1;
            }
            else
                aryCommandBuf[nCommandIndex++] = c;
			
        default:
            break;
        }
    }
    return 0;
}

void do_uart_command(void)
{
    int i;
	
#ifdef UART_DBG_TXD
    PutString("\n\rEXC--", 7);
#endif
	
#ifdef UART_DBG_TXD
    for (i = 0; i < nCommandSize; i++)
    {
        puthex(aryCommandBuf[i]);
        PutString(" ", 1);
    }
    PutString("\n\r", 2);
#endif
	
#ifdef OSD_DBG_TXD
	/*
    for (i = nCommandSize; i < UART_REV_MAX_BYTE; i++)
	aryCommandBuf[i] = 0;
    
	  if((aryCommandBuf[0] == 0x01) && (aryCommandBuf[1] == 0x02) && (aryCommandBuf[2] == 0x03) && (aryCommandBuf[3] == 0x04) && 
	  (aryCommandBuf[4] == 0x05) && (aryCommandBuf[5] == 0x06) && (aryCommandBuf[6] == 0x07) && (aryCommandBuf[7] == 0x08) && 
	  (aryCommandBuf[8] == 0x09) && (aryCommandBuf[9] == 0x0a) && (aryCommandBuf[10] == 0x0b) && (aryCommandBuf[11] == 0x0c) &&
	  (aryCommandBuf[12] == 0x0d) && (aryCommandBuf[13] == 0x0e) && (aryCommandBuf[14] == 0x0f))
	  {
	  //psprintf(RegionValStr[REGION1],"EXC %02x:%02x:%02x:%02x:%02x",aryCommandBuf[1],aryCommandBuf[2],aryCommandBuf[3],aryCommandBuf[4],aryCommandBuf[5]);
	  psprintf(RegionValStr[REGION1], "OK");
	  PrintOsdMsg(STR_OS_SPACE,REGION1, 1, 1);
	  }
	  else
	  {
	  //psprintf(RegionValStr[REGION1],"EXC %02x:%02x:%02x:%02x:%02x",aryCommandBuf[1],aryCommandBuf[2],aryCommandBuf[3],aryCommandBuf[4],aryCommandBuf[5]);
	  psprintf(RegionValStr[REGION1], "NG");
	  PrintOsdMsg(STR_OS_SPACE,REGION1, 1, 1);
	  }
	*/
#endif
	
    switch (aryCommandBuf[0])
    {
    case DIGI_ELEC_VAL:
        // show aryCommandBuf[1] (volume value) on VFD for 3 seconds
        nCurrentVolMode=VOL_MODE_MAIN;
        nMainVol = aryCommandBuf[1];
        psprintf(RegionValStr[REGION1], "MAIN VOL %d",aryCommandBuf[1]);
        PrintOsdMsg(STR_OS_SPACE, REGION1, 2, 1);
        do_updata_vfd_vol();
        break;
		
    case ELEC_VOL:
        // get aryCommandBuf[1] (TOTAL_VOL), aryCommandBuf[2] (FRONT_VOL), aryCommandBuf[3] (CENT_VOL),
        // aryCommandBuf[4] (REAR_VOL), aryCommandBuf[5] (FRONT_BALANCE), aryCommandBuf[6] (READ_BALANCE),
        // aryCommandBuf[7] (QS_EFFECT), aryCommandBuf[8] (TREBLE_EFFECT), aryCommandBuf[9] (BASS_EFFECT)
        nMainVol = aryCommandBuf[1];
#ifndef  NEW_UART_COMMAND  
        nFrontVol = aryCommandBuf[2];
        nCenterVol = aryCommandBuf[3];
        nRearVol = aryCommandBuf[4];
        nMainLRBalance = aryCommandBuf[5];
        nSurLRBalance = aryCommandBuf[6];
        nQSEffect = aryCommandBuf[7];
        nTreble = aryCommandBuf[8];
        nBass = aryCommandBuf[9];
#else
        if(aryCommandBuf[2]&0x80)
			nFrontVol=(0-(aryCommandBuf[2]&0x0f));
        else
			nFrontVol=((aryCommandBuf[2]&0x0f));
        if(aryCommandBuf[3]&0x80)
			nCenterVol=(0-(aryCommandBuf[3]&0x0f));
        else
			nCenterVol=((aryCommandBuf[3]&0x0f));
        if(aryCommandBuf[4]&0x80)
			nRearVol=(0-(aryCommandBuf[4]&0x0f));
        else
			nRearVol=((aryCommandBuf[4]&0x0f));   
        
        if(aryCommandBuf[5]&0x80)
			nSubwooferVol= (0-(aryCommandBuf[5]&0x0f));
        else
			nSubwooferVol= (aryCommandBuf[5]&0x0f);
        if(aryCommandBuf[6]&0x80)
			nMainBalance_L= (0-(aryCommandBuf[6]&0x0f));
        else
			nMainBalance_L= (aryCommandBuf[6]&0x0f);
        if(aryCommandBuf[7]&0x80)
			nMainBalance_R= (0-(aryCommandBuf[7]&0x0f));
        else
			nMainBalance_R= (aryCommandBuf[7]&0x0f);
        if(aryCommandBuf[8]&0x80)
			nSurBalance_L= (0-(aryCommandBuf[8]&0x0f));
        else
			nSurBalance_L= (aryCommandBuf[8]&0x0f);
        if(aryCommandBuf[9]&0x80)
			nSurBalance_R= (0-(aryCommandBuf[9]&0x0f));
        else
			nSurBalance_R= (aryCommandBuf[9]&0x0f);
        nQSEffect = aryCommandBuf[10];
        if(aryCommandBuf[11]&0x80)
			nTreble=(0-(aryCommandBuf[11]&0x0f));
        else
			nTreble = (aryCommandBuf[11]&0x0f);
        if(aryCommandBuf[12]&0x80)
			nBass=(0-(aryCommandBuf[12]));
        else
			nBass = (aryCommandBuf[12]&0x0f);
#endif
#if 1
        psprintf(RegionValStr[REGION3], "%d %d %d %d %d %d %d %d %d %d %d %d",
			nMainVol, nFrontVol, nCenterVol,
			nRearVol, nSubwooferVol, nMainBalance_L,
			nMainBalance_R, nSurBalance_L, nSurBalance_R,
			nQSEffect,nTreble,nBass);
        PrintOsdMsg(STR_OS_SPACE, REGION3, 2, 1);
#endif
        break;
		
    default:
        break;
    }
}
#ifndef NEW_UART_COMMAND
void IRSwitchMode()
{
    BYTE bModeChanged = 0;
	
    if (action_click)
    {
        bModeChanged = 1;
        if (MODE_DVD == nCurrentDVDMode)
            nCurrentDVDMode = MODE_AV1;
        else
            nCurrentDVDMode++;
    }
	
    switch (nCurrentDVDMode)
    {
    case MODE_AV1:
        psprintf(RegionValStr[REGION1], "AV1 MODE");
        // send mode command to 8051
        if (bModeChanged)
        {
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(AV_MODE);
            UART_PUTC_EXACT(AV1_MODE);
            UART_PUTC_EXACT(COMMAND_END);
			//            aryDbgBuf[0] = COMMAND_START;
			//            aryDbgBuf[1] = AV_MODE;
			//            aryDbgBuf[2] = AV1_MODE;
			//            aryDbgBuf[3] = COMMAND_END;
			//            PutString(aryDbgBuf, 4);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 AV1_MODE");
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        break;
		
    case MODE_AV2:
        psprintf(RegionValStr[REGION1], "AV2 MODE");
        // send mode command to 8051
        if (bModeChanged)
        {
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(AV_MODE);
            UART_PUTC_EXACT(AV2_MODE);
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 AV2_MODE");
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        break;
		
    case MODE_TUNER:
        psprintf(RegionValStr[REGION1], "TUNER MODE");
        // send mode command to 8051
        if (bModeChanged)
        {
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(AV_MODE);
            UART_PUTC_EXACT(TUNER_MODE);
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 TUNER_MODE");
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        break;
		
    case MODE_DVD:
        psprintf(RegionValStr[REGION1], "DVD MODE");
        // send mode command to 8051
        if (bModeChanged)
        {
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(AV_MODE);
            UART_PUTC_EXACT(DVD_MODE);
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 DVD_MODE");
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        break;
		
    default:
        return;
    }
    PrintOsdMsg(STR_OS_SPACE, REGION1, 3, 1);
}

void IRSwitchVolMode()
{
    BYTE bModeChanged = 0;
	
    if (action_click)
    {
        bModeChanged = 1;
        if (VOL_MODE_BASS == nCurrentVolMode)
            nCurrentVolMode = VOL_MODE_MAIN;
        else
            nCurrentVolMode++;
    }
	
    switch (nCurrentVolMode)
    {
    case VOL_MODE_MAIN:
        psprintf(RegionValStr[REGION1], "VOLUME MODE MAIN: %d", nMainVol);
        break;
		
    case VOL_MODE_FRONT:
        psprintf(RegionValStr[REGION1], "VOLUME MODE FRONT: %d", nFrontVol);
        break;
		
    case VOL_MODE_CENTER:
        psprintf(RegionValStr[REGION1], "VOLUME MODE CENTER: %d", nCenterVol);
        break;
		
    case VOL_MODE_REAR:
        psprintf(RegionValStr[REGION1], "VOLUME MODE REAR: %d", nRearVol);
        break;
		
    case VOL_MODE_MAIN_LR_BALANCE:
        psprintf(RegionValStr[REGION1], "MAIN_LR_BALANCE: %d", nMainLRBalance);
        break;
		
    case VOL_MODE_SUR_LR_BALANCE:
        psprintf(RegionValStr[REGION1], "SUR_LR_BALANCE: %d", nSurLRBalance);
        break;
		
    case VOL_MODE_QS_EFFECT:
        psprintf(RegionValStr[REGION1], "QS EFFECT: %d", nQSEffect);
        break;
		
    case VOL_MODE_TREBLE:
        psprintf(RegionValStr[REGION1], "TREBLE: %d", nTreble);
        break;
		
    case VOL_MODE_BASS:
        psprintf(RegionValStr[REGION1], "BASS: %d", nBass);
        break;
		
    default:
        return;
    }
    PrintOsdMsg(STR_OS_SPACE, REGION1, 3, 1);
}

void IRAdjustVol(int nUpOrDown) // 1:up, 0:down
{
    BYTE bVolChanged = 0;
	
    if (action_click)
        bVolChanged = 1;
	
    switch (nCurrentVolMode)
    {
    case VOL_MODE_MAIN:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nMainVol < VOL_MAX))
                nMainVol++;
            else if ((0 == nUpOrDown) && (nMainVol > VOL_MIN))
                nMainVol--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(TOTAL_VOL);
            UART_PUTC_EXACT(nMainVol);
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 MAIN VOL: -%d", nMainVol);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "VOLUME MODE MAIN: -%d", nMainVol);
        break;
		
    case VOL_MODE_FRONT:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nFrontVol < VOL_MAX))
                nFrontVol++;
            else if ((0 == nUpOrDown) && (nFrontVol > VOL_MIN))
                nFrontVol--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(FRONT_VOL);
            UART_PUTC_EXACT(nFrontVol);
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 FRONT VOL: -%d", nFrontVol);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "VOLUME MODE FRONT: -%d", nFrontVol);
        break;
		
    case VOL_MODE_CENTER:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nCenterVol < VOL_MAX))
                nCenterVol++;
            else if ((0 == nUpOrDown) && (nCenterVol > VOL_MIN))
                nCenterVol--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(CENT_VOL);
            UART_PUTC_EXACT(nCenterVol);
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 CENTER VOL: -%d", nCenterVol);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "VOLUME MODE CENTER: -%d", nCenterVol);
        break;
		
    case VOL_MODE_REAR:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nRearVol < VOL_MAX))
                nRearVol++;
            else if ((0 == nUpOrDown) && (nRearVol > VOL_MIN))
                nRearVol--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(REAR_VOL);
            UART_PUTC_EXACT(nRearVol);
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 REAR VOL: -%d", nRearVol);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "VOLUME MODE REAR: -%d", nRearVol);
        break;
		
    case VOL_MODE_MAIN_LR_BALANCE:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nMainLRBalance < BALANCE_MAX))
                nMainLRBalance++;
            else if ((0 == nUpOrDown) && (nMainLRBalance > BALANCE_MIN))
                nMainLRBalance--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(FRONT_BALANCE);
            switch (nMainLRBalance)
            {
            case -1:
                UART_PUTC_EXACT(0x81);
                break;
				
            case -2:
                UART_PUTC_EXACT(0x82);
                break;
				
            case -3:
                UART_PUTC_EXACT(0x83);
                break;
				
            default:
                UART_PUTC_EXACT((BYTE)nMainLRBalance);
                break;
            }
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 FRONT LR BAL: %d", nMainLRBalance);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "MAIN_LR_BALANCE: %d", nMainLRBalance);
        break;
		
    case VOL_MODE_SUR_LR_BALANCE:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nSurLRBalance < BALANCE_MAX))
                nSurLRBalance++;
            else if ((0 == nUpOrDown) && (nSurLRBalance > BALANCE_MIN))
                nSurLRBalance--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(REAR_BALANCE);
            switch (nSurLRBalance)
            {
            case -1:
                UART_PUTC_EXACT(0x81);
                break;
				
            case -2:
                UART_PUTC_EXACT(0x82);
                break;
				
            case -3:
                UART_PUTC_EXACT(0x83);
                break;
				
            default:
                UART_PUTC_EXACT((BYTE)nSurLRBalance);
                break;
            }
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 SUR LR BAL: %d", nSurLRBalance);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "SUR_LR_BALANCE: %d", nSurLRBalance);
        break;
		
    case VOL_MODE_QS_EFFECT:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nQSEffect < QS_MAX))
                nQSEffect++;
            else if ((0 == nUpOrDown) && (nQSEffect > QS_MIN))
                nQSEffect--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(QS_EFFECT);
            UART_PUTC_EXACT(nQSEffect);
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 QS: %d", nQSEffect);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "QS EFFECT: %d", nQSEffect);
        break;
		
    case VOL_MODE_TREBLE:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nTreble < VOL_MAX))
                nTreble++;
            else if ((0 == nUpOrDown) && (nTreble > VOL_MIN))
                nTreble--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(TREBLE_EFFECT);
            UART_PUTC_EXACT(nTreble);
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 TREBLE: %d", nTreble);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "TREBLE: %d", nTreble);
        break;
		
    case VOL_MODE_BASS:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nBass < VOL_MAX))
                nBass++;
            else if ((0 == nUpOrDown) && (nBass > VOL_MIN))
                nBass--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(BASS_EFFECT);
            UART_PUTC_EXACT(nBass);
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 BASS: %d", nBass);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "BASS: %d", nBass);
        break;
		
    default:
        return;
    }
    PrintOsdMsg(STR_OS_SPACE, REGION1, 3, 1);
}
#else   //FOR NEW UART COMMAND
void IRSwitchMode()
{
    //BYTE bModeChanged = 0;
	
	/* if (action_click)
    {
	bModeChanged = 1;
	if (MODE_DVD == nCurrentDVDMode)
	nCurrentDVDMode = MODE_AV1;
	else
	nCurrentDVDMode++;
    }
	*/
    switch (nCurrentDVDMode)
    {
    case MODE_AV1:
        psprintf(RegionValStr[REGION1], "AV1 MODE");
        // send mode command to 8051
        //if (bModeChanged)
        {
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(AV1_MODE);
            UART_PUTC_EXACT(AV1_MODE_D);
            UART_PUTC_EXACT(COMMAND_END);
			//            aryDbgBuf[0] = COMMAND_START;
			//            aryDbgBuf[1] = AV_MODE;
			//            aryDbgBuf[2] = AV1_MODE;
			//            aryDbgBuf[3] = COMMAND_END;
			//            PutString(aryDbgBuf, 4);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 AV1_MODE");
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        break;
		
    case MODE_AV2:
        psprintf(RegionValStr[REGION1], "AV2 MODE");
        // send mode command to 8051
        //if (bModeChanged)
        {
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(AV2_MODE);
            UART_PUTC_EXACT(AV2_MODE_D);
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 AV2_MODE");
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        break;
		
    case MODE_TUNER:
        psprintf(RegionValStr[REGION1], "TUNER MODE");
        // send mode command to 8051
		// if (bModeChanged)
        {
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(TUNER_MODE);
            UART_PUTC_EXACT(TUNER_MODE_D);
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 TUNER_MODE");
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        break;
		
    case MODE_DVD:
        psprintf(RegionValStr[REGION1], "DVD MODE");
        // send mode command to 8051
        //if (bModeChanged)
        {
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(DVD_MODE);
            UART_PUTC_EXACT(DVD_MODE_D);
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 DVD_MODE");
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        break;
		
    default:
        return;
    }
    PrintOsdMsg(STR_OS_SPACE, REGION1, 2, 1);
}

void IRSwitchVolMode()
{
    //BYTE bModeChanged = 0;
	
    /*if (action_click)
    {
	bModeChanged = 1;
	if (VOL_MODE_BASS == nCurrentVolMode)
	nCurrentVolMode = VOL_MODE_MAIN;
	else
	nCurrentVolMode++;
    }
    */
    switch (nCurrentVolMode)
    {
    case VOL_MODE_MAIN:
        psprintf(RegionValStr[REGION1], "MAIN VOL: %dDB", nMainVol);
        break;
		
    case VOL_MODE_FRONT:
        psprintf(RegionValStr[REGION1], "FRONT VOL: %dDB", nFrontVol);
        break;
		
    case VOL_MODE_CENTER:
        psprintf(RegionValStr[REGION1], "CENTER VOL: %dDB", nCenterVol);
        break;
		
    case VOL_MODE_REAR:
        psprintf(RegionValStr[REGION1], "REAR VOL: %dDB", nRearVol);
        break;
    case VOL_MODE_SUBWOOFER:
        psprintf(RegionValStr[REGION1],"SW VOL: %dDB",nSubwooferVol);
        break ;
    case VOL_MODE_MAIN_BALANCE_L:
        psprintf(RegionValStr[REGION1], "BALANCE FL VOL: %dDB", nMainBalance_L);
        break;
		
    case VOL_MODE_MAIN_BALANCE_R:
        psprintf(RegionValStr[REGION1], "BALANCE FR VOL: %dDB", nMainBalance_R);
        break;
    case VOL_MODE_SUR_BALANCE_L:
        psprintf(RegionValStr[REGION1], "BALANCE SL VOL: %dDB", nSurBalance_L);
        break;
		
    case VOL_MODE_SUR_BALANCE_R:
        psprintf(RegionValStr[REGION1], "BALANCE SR VOL: %dDB", nSurBalance_R);
        break;
		
    case VOL_MODE_QS_EFFECT:
        psprintf(RegionValStr[REGION1], "QSOUND: %d", nQSEffect);
        break;
		
    case VOL_MODE_TREBLE:
        psprintf(RegionValStr[REGION1], "TREBLE VOL: %dDB", 2*nTreble);
        break;
		
    case VOL_MODE_BASS:
        psprintf(RegionValStr[REGION1], "BASS VOL: %dDB", 2*nBass);
        break;
		
    default:
        return;
    }
    PrintOsdMsg(STR_OS_SPACE, REGION1, 2, 1);
    do_updata_vfd_vol();
}

void IRAdjustVol(int nUpOrDown) // 1:up, 0:down
{
    BYTE bVolChanged = 0;
	
    if (action_click||timeout_vfd)
        bVolChanged = 1;
    switch (nCurrentVolMode)
    {
    case VOL_MODE_MAIN:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nMainVol < VOL_MAX))
                nMainVol++;
            else if ((0 == nUpOrDown) && (nMainVol > VOL_MIN))
                nMainVol--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(TOTAL_VOL);
            UART_PUTC_EXACT(nMainVol);
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 MAIN VOL: %d", nMainVol);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "MAIN VOL: %dDB", nMainVol);
        break;
		
    case VOL_MODE_FRONT:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nFrontVol < VOL_ADJUST_MAN))
                nFrontVol++;
            else if ((0 == nUpOrDown) && (nFrontVol > VOL_ADJUST_MIN))
                nFrontVol--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(FRONT_VOL);
            switch(nFrontVol)
			{
			case -6 :
				UART_PUTC_EXACT(0x86);	
				break ;
			case -5 :
				UART_PUTC_EXACT(0x85);
				break ;
			case -4 :
				UART_PUTC_EXACT(0x84);
				break ;
			case -3 :
				UART_PUTC_EXACT(0x83);
				break ;
			case -2 :
				UART_PUTC_EXACT(0x82);
				break ;
			case -1 :
				UART_PUTC_EXACT(0x81);
				break ;
			default :
				UART_PUTC_EXACT((BYTE)(nFrontVol));
				break ; 
				
			}
            //UART_PUTC_EXACT(nFrontVol);
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 FRONT VOL: %d", nFrontVol);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "FRONT VOL: %dDB", nFrontVol);
        break;
		
    case VOL_MODE_CENTER:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nCenterVol < VOL_ADJUST_MAN))
                nCenterVol++;
            else if ((0 == nUpOrDown) && (nCenterVol > VOL_ADJUST_MIN))
                nCenterVol--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(CENT_VOL);
            switch(nCenterVol)
			{
			case -6 :
				UART_PUTC_EXACT(0x86);	
				break ;
			case -5 :
				UART_PUTC_EXACT(0x85);
				break ;
			case -4 :
				UART_PUTC_EXACT(0x84);
				break ;
			case -3 :
				UART_PUTC_EXACT(0x83);
				break ;
			case -2 :
				UART_PUTC_EXACT(0x82);
				break ;
			case -1 :
				UART_PUTC_EXACT(0x81);
				break ;
			default :
				UART_PUTC_EXACT((BYTE)(nCenterVol));
				break ; 
				
			}
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 CENTER VOL: %d", nCenterVol);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "CENTER VOL: %dDB", nCenterVol);
        break;
		
    case VOL_MODE_REAR:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nRearVol < VOL_ADJUST_MAN))
                nRearVol++;
            else if ((0 == nUpOrDown) && (nRearVol > VOL_ADJUST_MIN))
                nRearVol--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(REAR_VOL);
            switch(nRearVol)
			{
			case -6 :
				UART_PUTC_EXACT(0x86);	
				break ;
			case -5 :
				UART_PUTC_EXACT(0x85);
				break ;
			case -4 :
				UART_PUTC_EXACT(0x84);
				break ;
			case -3 :
				UART_PUTC_EXACT(0x83);
				break ;
			case -2 :
				UART_PUTC_EXACT(0x82);
				break ;
			case -1 :
				UART_PUTC_EXACT(0x81);
				break ;
			default :
				UART_PUTC_EXACT((BYTE)(nRearVol));
				break ; 
				
			}
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 REAR VOL: %d", nRearVol);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "REAR VOL: %dDB", nRearVol);
        break;
		
	case VOL_MODE_SUBWOOFER:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nSubwooferVol < VOL_ADJUST_MAN))
                nSubwooferVol++;
            else if ((0 == nUpOrDown) && (nSubwooferVol > VOL_ADJUST_MIN))
                nSubwooferVol--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(SUBWOOFER_VOL);
            switch(nSubwooferVol)
			{
			case -6 :
				UART_PUTC_EXACT(0x86);	
				break ;
			case -5 :
				UART_PUTC_EXACT(0x85);
				break ;
			case -4 :
				UART_PUTC_EXACT(0x84);
				break ;
			case -3 :
				UART_PUTC_EXACT(0x83);
				break ;
			case -2 :
				UART_PUTC_EXACT(0x82);
				break ;
			case -1 :
				UART_PUTC_EXACT(0x81);
				break ;
			default :
				UART_PUTC_EXACT((BYTE)(nSubwooferVol));
				break ; 
				
			}
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 SW VOL: %d", nSubwooferVol);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "SW VOL: %dDB", nSubwooferVol);
        break;
    case VOL_MODE_MAIN_BALANCE_L:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nMainBalance_L < BALANCE_MAX))
                nMainBalance_L++;
            else if ((0 == nUpOrDown) && (nMainBalance_L > BALANCE_MIN))
                nMainBalance_L--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(FRONT_BALANCE_L);
            switch (nMainBalance_L)
            {
            case -1:
                UART_PUTC_EXACT(0x81);
                break;
				
            case -2:
                UART_PUTC_EXACT(0x82);
                break;
				
            case -3:
                UART_PUTC_EXACT(0x83);
                break;
				
            default:
                UART_PUTC_EXACT((BYTE)nMainBalance_L);
                break;
            }
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 FRONT BAL L: %d", nMainBalance_L);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "BALANCE FL VOL: %dDB", nMainBalance_L);
        break;
		
    case VOL_MODE_MAIN_BALANCE_R:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nMainBalance_R < BALANCE_MAX))
                nMainBalance_R++;
            else if ((0 == nUpOrDown) && (nMainBalance_R > BALANCE_MIN))
                nMainBalance_R--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(FRONT_BALANCE_R);
            switch (nMainBalance_R)
            {
            case -1:
                UART_PUTC_EXACT(0x81);
                break;
				
            case -2:
                UART_PUTC_EXACT(0x82);
                break;
				
            case -3:
                UART_PUTC_EXACT(0x83);
                break;
				
            default:
                UART_PUTC_EXACT((BYTE)nMainBalance_R);
                break;
            }
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 FRONT BAL R: %d", nMainBalance_R);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "BALANCE FR VOL: %dDB", nMainBalance_R);
        break;
        
    case VOL_MODE_SUR_BALANCE_L:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nSurBalance_L < BALANCE_MAX))
                nSurBalance_L++;
            else if ((0 == nUpOrDown) && (nSurBalance_L > BALANCE_MIN))
                nSurBalance_L--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(REAR_BALANCE_L);
            switch (nSurBalance_L)
            {
            case -1:
                UART_PUTC_EXACT(0x81);
                break;
				
            case -2:
                UART_PUTC_EXACT(0x82);
                break;
				
            case -3:
                UART_PUTC_EXACT(0x83);
                break;
				
            default:
                UART_PUTC_EXACT((BYTE)nSurBalance_L);
                break;
            }
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 SUR BAL L: %d", nSurBalance_L);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "BALANCE SL VOL: %dDB", nSurBalance_L);
        break;
		
    case VOL_MODE_SUR_BALANCE_R:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nSurBalance_R < BALANCE_MAX))
                nSurBalance_R++;
            else if ((0 == nUpOrDown) && (nSurBalance_R > BALANCE_MIN))
                nSurBalance_R--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(REAR_BALANCE_R);
            switch (nSurBalance_R)
            {
            case -1:
                UART_PUTC_EXACT(0x81);
                break;
				
            case -2:
                UART_PUTC_EXACT(0x82);
                break;
				
            case -3:
                UART_PUTC_EXACT(0x83);
                break;
				
            default:
                UART_PUTC_EXACT((BYTE)nSurBalance_R);
                break;
            }
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 SUR BAL R: %d", nSurBalance_R);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "BALANCE SR VOL: %dDB", nSurBalance_R);
        break;
		
    case VOL_MODE_QS_EFFECT:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nQSEffect < QS_MAX))
                nQSEffect++;
            //else if ((0 == nUpOrDown) && (nQSEffect > QS_MIN))
			//  nQSEffect--;
            else
                nQSEffect=QS_MIN;
			//break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(QS_EFFECT);
            UART_PUTC_EXACT(nQSEffect);
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 QS: %d", nQSEffect);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "QSOUND: %d", nQSEffect);
        break;
		
    case VOL_MODE_TREBLE:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nTreble < VOL_ADJUST_MAN-1))
                nTreble++;
            else if ((0 == nUpOrDown) && (nTreble > VOL_ADJUST_MIN+1))
                nTreble--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(TREBLE_EFFECT);
            switch (nTreble)
            {
            case -1:
                UART_PUTC_EXACT(0x81);
                break;
				
            case -2:
                UART_PUTC_EXACT(0x82);
                break;
				
            case -3:
                UART_PUTC_EXACT(0x83);
                break;
            case -4:
                UART_PUTC_EXACT(0x84);
                break;
            case -5:
                UART_PUTC_EXACT(0x85);
                break;
            default:
                UART_PUTC_EXACT((BYTE)nTreble);
                break;
            }
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 TREBLE: %d", nTreble);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "TREBLE VOL: %dDB", 2*nTreble);
        break;
		
    case VOL_MODE_BASS:
        if (bVolChanged)
        {
            if ((1 == nUpOrDown) && (nBass < VOL_ADJUST_MAN-1))
                nBass++;
            else if ((0 == nUpOrDown) && (nBass > VOL_ADJUST_MIN+1))
                nBass--;
            else
                break;
			
            // send volume change command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(BASS_EFFECT);
            switch (nBass)
            {
            case -1:
                UART_PUTC_EXACT(0x81);
                break;
				
            case -2:
                UART_PUTC_EXACT(0x82);
                break;
				
            case -3:
                UART_PUTC_EXACT(0x83);
                break;
            case -4:
                UART_PUTC_EXACT(0x84);
                break ;
            case -5:
                UART_PUTC_EXACT(0x85);
            default:
                UART_PUTC_EXACT((BYTE)nBass);
                break;
            }
            UART_PUTC_EXACT(COMMAND_END);
			
#ifdef OSD_DBG_TXD
            psprintf(RegionValStr[REGION3], "SEND 8051 BASS: %d", nBass);
            PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
        }
        psprintf(RegionValStr[REGION1], "BASS VOL: %dDB", 2*nBass);
        break;
		
    default:
        return;
    }
    PrintOsdMsg(STR_OS_SPACE, REGION1, 2, 1);
    do_updata_vfd_vol();
}
void Set_Default_Vol(void)
{
	nCurrentDVDMode=MODE_DVD;
	nCurrentVolMode=VOL_MODE_MAIN;
	nMainVol=MAINVOL;
	nFrontVol=FRONTVOL;
	nCenterVol=CENTERVOL;
	nRearVol=REARVOL;
	nSubwooferVol=SUBWOOFERVOL;
	nMainBalance_L=MAINBALANCE_L;
	nMainBalance_R=MAINBALANCE_R;
	nSurBalance_L=SURBALANCE_L;
	nSurBalance_R=SURBALANCE_R;
	nQSEffect=QSEFFECT;
	nTreble=TREBLEVOL;
	nBass=BASSVOL;
	UART_PUTC_EXACT(COMMAND_START);
	UART_PUTC_EXACT(VOL_DEFAULT);
	UART_PUTC_EXACT(VOL_DEFAULT_D);
	UART_PUTC_EXACT(COMMAND_END);
	psprintf(RegionValStr[REGION1], "SETUP DEFAULT VOL");
	PrintOsdMsg(STR_OS_SPACE, REGION1, 2, 1);
	do_updata_vfd_vol();
}
#endif //NEW UART COMMAND FOR FUSS
#endif


