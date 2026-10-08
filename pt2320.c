//======================================================================
//	NOTICE: NOT ALL THE FUNCTION HAVE BEEN TEST IN IC PT2320!!!
//======================================================================

#include "config.h"
#include "regmap.h"
#include "global.h"
#include "gpio.h"
#include "iop.h"
#include "audctrl.h"

#ifndef DVDRELEASE
//#define PT2320_DBG
#endif

BYTE    FUNC_EFFECT = 0x0f;

const BYTE tone_value[16] = 
{0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0xf,0xe,0xd,0xc,0xb,0xa,0x9,0x8};
//the values in the up table are the component of i2c command word
//the format and sequence are from datasheet of pt2320
/**************************************
**  bit3    bit2    bit1    bit0     dB
**   0       0       0       0      -14
**   0       0       0       1      -12
**   0       0       1       0      -10
**   0       0       1       1      -8
**   0       1       0       0      -6
**   0       1       0       1      -4
**   0       1       1       0      -2
**   0       1       1       1      -0
**   1       0       0       0      +14
**   1       0       0       1      +12
**   1       0       1       0      +10
**   1       0       1       1      +8
**   1       1       0       0      +6
**   1       1       0       1      +4
**   1       1       1       0      +2
**   1       1       1       1      +0
****************************************/

/*
**  This function is the first function be called when use chip pt2322
**  You have to initial the chip just at the time power is turned ON
*/
void init_pt_audio(void)
{
	middle_level= 8;
	base_level = 8;
	treble_level = 8;
	front_level = 15;
	center_level = 15;
	rear_level = 15;
	woofer_level = 15;
	old_level = 0;
#ifdef VFD_VOLUME_DISPLAY
	//maybe here not the right place to init vfd_mode_state
	//vfd_mode_state=DVD_NORMAL_MODE;
	timeout_vfd = 0;
#endif 

//freyman, in pt2320 no need to wake up it	
//	set_chip_act();
//	set_demute();
//freyman, set 3d off to avoid attenuation of audio sigal 2002-07-01 21:01
	set_3d_off();
//
	set_tone_defeat();
//freyman remarked 2002-07-03, have checked by the GB test disc
//	AudioIOControl(2,15,0);
	set_volume(VOL_VALUE);
	set_front();
	set_middle();
	set_base();
	set_treble();
}

/*  
**  After power is turned ON, PT2322 must be sent a Code - "11000111"(C7H)
**  - to active Input SW.
*/
void set_chip_act(void)
{
    PT2320_WRITE_SBUS(INPUT_SW,SW_ON);
}
/*
** The following three function is about tone control: 
** bass,treble,middle
*/

void set_base(void)
{
	#ifdef PT2320_DBG
    printf("set base\n");
    #endif
    
    FUNC_EFFECT &=TONE_CONTROL_ON;
    PT2320_WRITE_SBUS(FUNC_SEL,FUNC_EFFECT);
    PT2320_WRITE_SBUS(BASE,tone_value[base_level]);
}

void set_treble(void)
{
    #ifdef PT2320_DBG
    printf("set_treble\n");
    #endif
    
    FUNC_EFFECT &=TONE_CONTROL_ON;
    PT2320_WRITE_SBUS(FUNC_SEL,FUNC_EFFECT);
    PT2320_WRITE_SBUS(TREBLE,tone_value[treble_level]);
}

void set_middle(void)
{
    #ifdef PT2320_DBG
    printf("set_middle:%d\n",middle_level);
    #endif
    
    FUNC_EFFECT &=TONE_CONTROL_ON;
    PT2320_WRITE_SBUS(FUNC_SEL,FUNC_EFFECT);
    PT2320_WRITE_SBUS(MIDDLE,tone_value[middle_level]);
}

/*
**  Following function is to trim 5.1 channel
*/
void set_front(void)
{
    #ifdef PT2320_DBG
    printf("set front\n");
    #endif
    
    PT2320_WRITE_SBUS(LEFT_FRONT,15-front_level);
    PT2320_WRITE_SBUS(RIGHT_FRONT,15-front_level);
}
void set_center(void)
{
    #ifdef PT2320_DBG
    printf("set_center\n"); 
    #endif
    
    PT2320_WRITE_SBUS(CENTER,15-center_level);
}

void set_rear(void)
{
    #ifdef PT2320_DBG
    printf("set_rear\n");   
    #endif
    
    PT2320_WRITE_SBUS(LEFT_REAR,15-rear_level);
    PT2320_WRITE_SBUS(RIGHT_REAR,15-rear_level);
}

void set_woofer(void)
{
    #ifdef PT2320_DBG
    printf("set_woofer\n"); 
    #endif
    
    PT2320_WRITE_SBUS(SUBWOOFER,15-woofer_level);
}
/*
**  Following function is to volume:
**  set the audio value,mute,demute, etc
*/
void set_volume(BYTE x)//maybe there are some troubles in Nesinit.c, freyman
{
    #ifdef PT2320_DBG
    printf("set_volume:%d\n",x); 
    #endif
    
    PT2320_WRITE_SBUS(VOLUME_10_CONTROL,((80-x)/10));
    PT2320_WRITE_SBUS(VOLUME_1_CONTROL,((80-x)%10));
}

void set_mute(void)
{
    #ifdef PT2320_DBG
    printf("set mute in pt2322\n");
    #endif
    
    FUNC_EFFECT |=PT_MUTE_ON;
    PT2320_WRITE_SBUS(FUNC_SEL,FUNC_EFFECT);
}

void set_demute(void)
{
    #ifdef PT2320_DBG
    printf("set demute\n");
    #endif
    
    FUNC_EFFECT &=PT_MUTE_OFF;
    PT2320_WRITE_SBUS(FUNC_SEL,FUNC_EFFECT);
}

/*
**  Following function is for 3d effect 
**  but now I can't get the any effect
*/
void set_3d_on(void)
{
    #ifdef PT2320_DBG
    printf("set 3d on\n");
    #endif
    
    FUNC_EFFECT &=THREED_ON;
    PT2320_WRITE_SBUS(FUNC_SEL,FUNC_EFFECT);
}

void set_3d_off(void)
{
    #ifdef PT2320_DBG
    printf("set 3D OFF\n");
    #endif
    
    FUNC_EFFECT |=THREED_OFF;
    PT2320_WRITE_SBUS(FUNC_SEL,FUNC_EFFECT);
}
void set_tone_defeat(void)
{
    FUNC_EFFECT |=TONE_DEFEAT;
    PT2320_WRITE_SBUS(FUNC_SEL,FUNC_EFFECT);    
}
void set_tone_on(void)
{
    FUNC_EFFECT &=TONE_CONTROL_ON;
    PT2320_WRITE_SBUS(FUNC_SEL,FUNC_EFFECT);    
}
