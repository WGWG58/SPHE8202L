#include "config.h"
#include "regmap.h"
#include "global.h"
#include "gpio.h"
#include "iop.h"
#include "audctrl.h"

#ifndef DVDRELEASE
//#define PT_DBG
#endif

#ifndef   PT_DBG
#undef printf
#undef print_block
#define printf(f, a...) do {} while (0)
#define print_block(x,y) do {} while (0)
#endif


void set_chip_act(void);
void set_tone_defeat(void);


BYTE    FUNC_EFFECT = 0x0f; 
//freyman add 2002-9-10 8:32
//#ifdef SVA_SAMPLE
BYTE    pt_vol;
//#endif 

const BYTE tone_value[16] = 
{0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0xf,0xe,0xd,0xc,0xb,0xa,0x9,0x8};
//the values in the up table are the component of i2c command word
//the format and sequence are from datasheet of pt2322
/*
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
*/

/*
**  This function is the first function be called when use chip pt2322
**  You have to initial the chip just at the time power is turned ON
*/
void init_pt_audio(void)
{
	middle_level= 8;
	base_level = 8;
	treble_level = 8;
	front_level = 8;
	center_level = 8;
	rear_level = 8;
	woofer_level = 8;
/*freyman marked 2004-3-23 15:08, for no use
#ifdef SVA_SAMPLE
	rfront_level = 8;
	lfront_level = 8;
	rrear_level = 8;
	lrear_level = 8;
	pt_vol = 10;
#endif 
*/
//	old_level = 0;
#ifdef VFD_VOLUME_DISPLAY
	/*
	**maybe here not the right place to init vfd_mode_state
	**vfd_mode_state=DVD_NORMAL_MODE;
	*/
	timeout_vfd = 0;
#endif 
	set_chip_act();
	delay_1ms(300);
	
	/*
	** freyman add 2002-7-27 14:23
	** Des:when power on, player works in DVD mode, audio output to TV
	**		so set mute the pt2322
	*/
	set_mute();
	
	/*
	** freyman, 2002-07-01 21:01
	** Des: when 3d on, the audio signal will be attenuated, 
	**		maybe 50 percents. For the ephase angle is 180.
	** 		So set 3d off.
	*/
	set_3d_off();  
	
	
	
	/*	set_volume(AUX_VOL_MAX);*/
	set_front();
	set_center();
	set_rear();
	set_woofer();
	set_middle();
	set_base();
	set_treble();
	/*               
	** freyman, 2002-7-3 14:28
	** set tone defeat to avoid FL and FR output connect together 
	*/	
	//	set_tone_defeat();
}

/*
**
*/
void init_volume(void)
{
	//	AudioIOControl(2,15,0);
	set_volume(AUX_VOL_MAX);
	set_front();
	set_middle();
	set_base();
	set_treble();
	set_demute();
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
#ifdef PT_DBG
    printf("set base\n");
#endif
    
    FUNC_EFFECT &=TONE_CONTROL_ON;
    PT2320_WRITE_SBUS(FUNC_SEL,FUNC_EFFECT);
    PT2320_WRITE_SBUS(BASE,tone_value[base_level]);
}

void set_treble(void)
{
#ifdef PT_DBG
    printf("set_treble\n");
#endif
    
    FUNC_EFFECT &=TONE_CONTROL_ON;
    PT2320_WRITE_SBUS(FUNC_SEL,FUNC_EFFECT);
    PT2320_WRITE_SBUS(TREBLE,tone_value[treble_level]);
}

void set_middle(void)
{
#ifdef PT_DBG
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
#ifdef PT_DBG
    printf("set front\n");
#endif
    
    PT2320_WRITE_SBUS(LEFT_FRONT,15-front_level);
    PT2320_WRITE_SBUS(RIGHT_FRONT,15-front_level);
}
void set_center(void)
{
#ifdef PT_DBG
    printf("set_center\n"); 
#endif
    
    PT2320_WRITE_SBUS(CENTER,15-center_level);
}

void set_rear(void)
{
#ifdef PT_DBG
    printf("set_rear\n");   
#endif
    
    PT2320_WRITE_SBUS(LEFT_REAR,15-rear_level);
    PT2320_WRITE_SBUS(RIGHT_REAR,15-rear_level);
}

void set_woofer(void)
{
#ifdef PT_DBG
    printf("set_woofer\n"); 
#endif
    
    PT2320_WRITE_SBUS(SUBWOOFER,15-woofer_level);
}
/*
**  Following function is to volume:
**  set the audio value,mute,demute, etc
**  the value of parameter:x
**		1: volume up
**		0: volume down
**      else: set pt2322 to the max volume, almost when power on to initial
*/
void set_volume(BYTE x)//maybe there are some troubles in Nesinit.c, freyman
{
#ifdef PT_DBG
    printf("set_volume:%d\n",x); 
#endif
    if(x<=1)
    {
//#ifdef SVA_SAMPLE
    extern void show_level(int id,INT8 level,BYTE total_level);
    if((x==1)&&(pt_vol<20))
        pt_vol++;
    else if((x==0)&&(pt_vol>0))
        pt_vol--;
    if(pt_vol<=0)
        pt_vol = 0;
    x = pt_vol;
    show_level(AMP_VOL_ID,x,21);
    x = pt_vol*2;
//#endif 
    //freyman mod 2002-9-12 18:03
    PT2320_WRITE_SBUS(VOLUME_10_CONTROL,((80-x-40)/10));
    PT2320_WRITE_SBUS(VOLUME_1_CONTROL,((80-x-40)%10));
    }
	else
	{
		pt_vol = 20;
		PT2320_WRITE_SBUS(VOLUME_10_CONTROL,(80/10));
    	PT2320_WRITE_SBUS(VOLUME_1_CONTROL,(80%10));
	}
}

void set_mute(void)
{
#ifdef PT_DBG
    printf("set mute in pt2322\n");
#endif
	
    FUNC_EFFECT |=PT_MUTE_ON;
    PT2320_WRITE_SBUS(FUNC_SEL,FUNC_EFFECT);
	
}

void set_demute(void)
{
#ifdef PT_DBG
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
#ifdef PT_DBG
    printf("set 3d on\n");
#endif
    
    FUNC_EFFECT &=THREED_ON;
    PT2320_WRITE_SBUS(FUNC_SEL,FUNC_EFFECT);
}

void set_3d_off(void)
{
#ifdef PT_DBG
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
/* freyman marked 2004-3-23 15:09, for no use
#ifdef SVA_SAMPLE
void set_lfront(void)
{
    PT2320_WRITE_SBUS(LEFT_FRONT,15-lfront_level);
}
void set_rfront(void)
{
    PT2320_WRITE_SBUS(RIGHT_FRONT,15-rfront_level);
}
void set_lrear(void)
{    
    PT2320_WRITE_SBUS(LEFT_REAR,15-lrear_level);
}
void set_rrear(void)
{
    PT2320_WRITE_SBUS(RIGHT_REAR,15-rrear_level);
}
#endif 
*/


