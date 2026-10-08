#include "user_init.h"

#ifdef USE_IR_FILTER
#include "global.h"
#include "ircode.h"
#include "irconfig.h"
#include "ir_filter.h"

int IRFilter_No_Pass(BYTE rx __UNUSED)
{
    printf("IR rejected by no pass filter.\n");
    return IR_FILTER_REJECT;
}

int IRFilter_All_Pass(BYTE rx __UNUSED)
{
	printf("IR filter all pass.\n");
    return IR_FILTER_NOP;
}

#ifdef SUPPORT_MP3_ENCODER
int IRFilter_MP3_ENCODER(BYTE rx)
{
    switch(rx)
    {
		case IRC_ANGLE:
        case IRC_POWER:
        case IRC_EJECT:
        case IRC_STOP:
		case IRC_PAUSE:
		case IRC_PLAY:
		case IRC_PLAY_RESUME:
        case IRC_NEXT:
		case IRC_PREV:
        case IRC_SELECT:
        case IRC_DISPLAY:
        case IRC_VOLUME_UP:
        case IRC_VOLUME_DN:
        case IRC_MUTE:
		case IRC_SUBP:
		#ifdef ORITRON_HK_DVD
		case IRC_ANGLE:		  //qinhua,modify for OP code,2005-11-10 20:34
        #else
		case 0x62:		// sub-title2 in IR200
        #endif
        if(dataInPtr != dataOutPtr)  //no key need during open file zhongshan modified 20051216
		{
            printf("IRFilter_MP3_ENCODER : pass\n");
            return IR_FILTER_NOP;
            break;
		}
		else
		{
			printf("IRFilter_MP3_ENCODER : reject\n");
            return IR_FILTER_REJECT;
			break;
		}
        default:
            printf("IRFilter_MP3_ENCODER : reject\n");
            return IR_FILTER_REJECT;
    }
    return IR_FILTER_EXCEPTION;
}


#endif

#ifdef SUPPORT_DIVX6
extern int divx6_SignalIRAccepted();
extern int divx6_SignalIRBlocked();

int divx6_MenuIRFilter(BYTE rx)
{
    switch(rx)
    {
        case IRC_POWER:
        case IRC_EJECT:
        case IRC_RETURN:
        case IRC_STOP:
        
        case IRC_TITLEMENU:
        case IRC_PBC:
        case IRC_UP:
        case IRC_LEFT:
        case IRC_RIGHT:
        case IRC_DOWN:
        case IRC_SELECT:
    #ifdef IR_PLAY_RESUME
        case IRC_PLAY_RESUME:
    #else
        case IRC_PLAY:
    #endif
        case IRC_DISPLAY:
        case IRC_P_SCAN:
        case IRC_FORMAT:
        case IRC_VOLUME_UP:
        case IRC_VOLUME_DN:
        case IRC_MUTE:
            divx6_SignalIRAccepted();
            printf("Accepted by Divx6 menu\n");
            return IR_FILTER_NOP;
            break;
        case IRC_NEXT:
		case IRC_PAUSE:
        default:
            divx6_SignalIRBlocked();
            printf("Turned down by Divx6 menu\n");
            return IR_FILTER_REJECT;
    }
    return IR_FILTER_EXCEPTION;
}

int divx6_TitleIRFilter(BYTE rx __UNUSED)
{
    divx6_SignalIRAccepted();
    return IR_FILTER_NOP;
}
#endif  //#ifdef SUPPORT_DIVX6


#endif

