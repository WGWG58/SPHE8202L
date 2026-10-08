/**************************************************************************
 *                                                                        *
 *         Copyright (c) 2002 by Sunplus Technology Co., Ltd.             *
 *                                                                        *
 *  This software is copyrighted by and is the property of Sunplus        *
 *  Technology Co., Ltd. All rights are reserved by Sunplus Technology    *
 *  Co., Ltd. This software may only be used in accordance with the       *
 *  corresponding license agreement. Any unauthorized use, duplication,   *
 *  distribution, or disclosure of this software is expressly forbidden.  *
 *                                                                        *
 *  This Copyright notice MUST not be removed or modified without prior   *
 *  written consent of Sunplus Technology Co., Ltd.                       *
 *                                                                        *
 *  Sunplus Technology Co., Ltd. reserves the right to modify this        *
 *  software without notice.                                              *
 *                                                                        *
 *  Sunplus Technology Co., Ltd.                                          *
 *  19, Innovation First Road, Science-Based Industrial Park,             *
 *  Hsin-Chu, Taiwan, R.O.C.                                              *
 **************************************************************************/
/*
*  Terry,2004/2/17 11:08AM
*  a.modify warning message
*/
//#define USE_MIC_ECHO_PARAM
#include "config.h"
#include "regmap.h"
#include "global.h"
#include "macro.h"
#include "func.h"
#include "util.h"
#include "stdlib.h"    //huo 2000.12.14
#include "cdfunc.h"
#include "cfont.h"
#include "sio.h"
#include "vfdfunc.h"
#include "ringbuf.h"
#include "ircmd.h"
#include "ircode.h"
#include "cd.h"
#include "auctrl.h"
#include "user_init.h"  //terry,2001/1/9 03:29PM

#include "avd.h"
#include "dvdpe.h"

#include "fs96602.h"
#include "osd.h"
#include "framebuf.h"
#include "cderr.h"
#include "vpp.h"
#include "user_if.h"
#include "dsp3_if.h"
#include "atapi_if.h"
#include "dma.h" //Jeff 20010919
#include "auddrv.h" //2004AUDDRV oliver 20041004 for using audio driver purpose
//#include "audif.h"
#include "setup.h"
#include "fsGUI.h"
#include "tvif.h"
#include "drv.h"
//#include "auddac.h"

#include "iop.h"//2-7-9 9:40
#include "UartTxd.h"

#ifdef TUNER_T988
#include "radio_t988.h"  //jinping 2-6-20 14:04
#elif defined(TUNER_MV114)
#include "radio_mv114.h"  //jinping 2002-7-1 20:30
#endif

#if defined(PT2322)||defined(PT2320)
#include "audctrl.h"
#endif 

#if defined(TAS3001_AMP)   //use TI 3001 amplifier  jason ych add 2-8-9 10:10
#include "ti3001.h"
#endif 

#if defined(TAS5026_AMP)   //use TI 3001 amplifier  jason ych add 2-8-9 10:10
#include "ti5026.h"
#endif 

#ifdef SUPPORT_CDG  //Jeff 20020824
#include "cdg.h"
#endif

#ifdef	MP3_JPEG_COWORK
#include "fsNav.h"
#endif


#ifndef DVDRELEASE
//#define DSPADUIODBG
#endif


#ifndef DSPADUIODBG
#undef printf
#undef print_block
#define printf(f, a...) do {} while (0)
#define print_block(x,y) do {} while (0)
#endif

extern int check_chipinfo(int n);

/**************************************************************************
 *  Function Name: is_dts_force_spdif_bitstream                           
 *  Purposes:                                                             
 *    Should DTS SPDIF out set to raw data?                               
 *  Descriptions:                                                         
 *    Under some situation, SPDIF should output DTS raw bitstream only    
 *  Arguments:                                                            
 *    
 *  Returns:                                                              
 *    1 : DTS SPDIF output shuld set to raw data
 *    0 : DTS SPDIF output with no restriction
 *  See also:                                                             
 *    
 **************************************************************************/
int is_dts_force_spdif_bitstream()
{
    if ((cd_type_loaded==CDDA && cd_subtype==CD_DTS) || (coding_mode_now&AUDIF_CODING_MODE_DTS) )
    {
#if defined(NO_DTS_OUTPUT) || defined(FORCE_NO_DTS_OUTPUT)
        return 1;
#endif
        if (!check_chipinfo(2)) return 1;
    }
    return 0;
}


extern BYTE wait_dsp_port0_5(int port0,int port5,int val,UINT32 risc_waiting_dsp_tm);

UINT16 oldDSPbarrier=0;
extern BYTE bOutVol; //2004AUDDRV:declaration move to dspkernel.c
//BYTE de_mute;
INT8 audio_key;
INT8 echo_level=4; //range:0~8, 0:off
INT8 echo_decay=4; //range:0~8, 0:off
extern INT8 mic_volume;  //2004AUDDRV:declaration move to auddrv.h

#ifndef AC3_BASS_MANAGEMENT
extern  BYTE    cspk_volume;
extern  BYTE    fspk_volume;
extern  BYTE    sspk_volume;
extern  int    downmix_off;
#endif

#if 0 //2004AUDDRV : move to auddrv.c
#ifdef USE_MIC_ECHO_PARAM
// decay : 0 ~ 127
// delay : 0 ~ 12000
#ifdef ECHO_SPECIAL_PARA
UINT16 echo_para[9][2]={
        {0,0},
        {76,2976},   // decay : 76/128= 0.6  , delay: 2976/44100=67ms
        {79,3648},
        {81,4320},
        {84,4992},
        {87,5664},
        {89,6336},
        {92,7008},
        {94,7680}, 
};
#elif defined(SUPPORT_MIDI) //Jeff 20040303
UINT16 echo_para[9][2]={
	{0,0},
	{7,12000},
	{15,13000},
	{23,12000},
	{31,12000},
	{39,12000},
	{47,12000},
	{55,12000},
	{63,12000},	
};

#else//ECHO_SPECIAL_PARA	
UINT16 echo_para[9][2]={
	{0,0},
	{7,10000},
	{15,10000},
	{23,10000},
	{31,10000},
	{39,10000},
	{47,10000},
	{55,10000},
	{63,10000},
	
};
#endif//ECHO_SPECIAL_PARA

#endif
#endif //2004AUDDRV

//terry,2004/2/11 01:22PM
#ifdef	VOL_80
const BYTE  VolTab[17+65] = {
#ifdef HIMAGE1251   //fengjl TEST 2004-03-02 14:57
		0x00,   //0
		
        0x01, 0x02, 0x03, 0x03, 0x04,		//01--05
        0x06, 0x07, 0x08, 0x08, 0x09, 		//06--10
        0x0b, 0x0c, 0x0d, 0x0d, 0x0e,  		//11--15
        0x10, 0x11, 0x12, 0x12, 0x13,    	//16--20
        0x15, 0x16, 0x17, 0x17, 0x18,   	//21--25
        0x1a, 0x1b, 0x1c, 0x1c, 0x1d,   	//26--30
        0x20, 0x21, 0x22, 0x22, 0x23,   	//31--25
        0x25, 0x26, 0x27, 0x27, 0x28,   	//35--40
        0x2a, 0x2b, 0x2c, 0x2c, 0x2a,   	//41--45
        0x31, 0x33, 0x35, 0x35, 0x36,   	//46--50
        0x39, 0x3a, 0x3b, 0x3b, 0x3c,   	//51--55
        0x3e, 0x3f, 0x40, 0x41, 0x43,   	//56--60
        0x46, 0x48, 0x4a, 0x4b, 0x4c,   	//61--65
        0x4f, 0x50, 0x51, 0x52, 0x54,   	//66--70
        0x58, 0x5a, 0x5d, 0x60, 0x65,   	//71--75
        0x6c, 0x70, 0x74, 0x76, 0x7a,   	//76--80

		0x7f,   //81
#else
    	0x00,   //0

        0x01, 0x02, 0x03, 0x04, 0x05,		//01--05
        0x06, 0x07, 0x08, 0x09, 0x0a, 		//06--10
        0x0b, 0x0c, 0x0d, 0x0e, 0x0f,  		//11--15
        0x10, 0x11, 0x12, 0x13, 0x14,    	//16--20
        0x15, 0x16, 0x17, 0x18, 0x19,   	//21--25
        0x1a, 0x1b, 0x1c, 0x1d, 0x1f,   	//26--30
        0x20, 0x21, 0x22, 0x23, 0x24,   	//31--25
        0x25, 0x26, 0x27, 0x28, 0x29,   	//35--40
        0x2a, 0x2b, 0x2c, 0x2d, 0x30,   	//41--45
        0x31, 0x33, 0x35, 0x36, 0x37,   	//46--50
        0x39, 0x3a, 0x3b, 0x3c, 0x3d,   	//51--55
        0x3e, 0x3f, 0x40, 0x42, 0x44,   	//56--60
        0x46, 0x48, 0x4a, 0x4c, 0x4d,   	//61--65
        0x4f, 0x50, 0x51, 0x53, 0x55,   	//66--70
        0x58, 0x5a, 0x5d, 0x62, 0x67,   	//71--75
        0x6c, 0x70, 0x74, 0x78, 0x7f,   	//76--80

		0x7f,   //81
#endif
};
#elif defined(VOL_20)   //fengjl add 2004-03-08 21:33
const BYTE  VolTab[22] = {
	0x00,   //0
        0x01,   //1
        0x02,   //2
        0x03,   //3
        0x04,   //4
        0x05,   //5
        0x07,   //6
        0x0a,   //7
        0x0d,   //8
        0x11,   //9
        0x15,   //10
        0x19,   //11
        0x1d,   //12
        0x22,   //13
        0x28,   //14
        0x2f,   //15
        0x3f,   //16
        0x4f,   //17
        0x5f,   //18
        0x6f,   //19
        0x7f,   //20
        0x7f,   //21
};
#else
const BYTE  VolTab[17] = {
#ifdef ALL_DISC_DECREASE_VOLUME
	    0x00,   //0
        0x02,   //1
        0x03,   //2
        0x04,   //3
        0x05,   //4
        0x07,   //5
        0x09,   //6
        0x0c,   //7
        0x11,   //8
        0x16,   //9
        0x1e,   //10
        0x28,   //11
        0x36,   //12
        0x45,   //13
        0x50,   //14
        0x5f,   //15
        0x6a,   //16
#else//#ifdef ALL_DISC_DECREASE_VOLUME
	    0x00,   //0
        0x02,   //1
        0x03,   //2
        0x04,   //3
        0x05,   //4
        0x07,   //5
        0x09,   //6
        0x0c,   //7
        0x11,   //8
        0x16,   //9
        0x1e,   //10
        0x28,   //11
        0x36,   //12
        0x47,   //13
        0x5f,   //14
        #ifdef ALCO_DVD_UI
        0x75,   //15
        #else
        0x7f,   //15
        #endif
        0x7f,   //16
#endif//#ifdef ALL_DISC_DECREASE_VOLUME
};
#endif //VOL_80

#ifdef DECREASE_CDDA_VOLUME
const BYTE  CDDAVolTab[17] = {
	    0x00,   //0
        0x02,   //1
        0x03,   //2
        0x04,   //3
        0x05,   //4
        0x07,   //5
        0x09,//0x09,   //6
        0x0c,//0x0c,   //7
        0x11,//0x11,   //8
        0x16,//0x16,   //9
        0x1e,//0x1e,   //10
        0x25,//0x28,   //11
        0x30,//0x36,   //12
        0x38,//0x47,   //13
        0x4a,//0x5f,   //14
        0x5f,//0x7f,   //15
        0x6f,//0x7f,   //16
};
#endif//#ifdef ALL_DISC_DECREASE_VOLUME

#ifdef GBM_DVD
const BYTE  MICVolTab[9] = {
		0x00,   //0
        0x0f,   //1
        0x16,   //2
        0x20,   //3
        0x36,   //4
        0x47,   //5
        0x55,//0x57,   //6
        0x60,//0x64,   //7
        0x64,//0x7f,   //8
};
#else//GBM_DVD
const BYTE  MICVolTab[9] = {
	0x00,   //0
        0x0f,   //1
        0x16,   //2
        0x20,   //3
        0x36,   //4
        0x47,   //5
        0x57,   //6
        0x64,   //7
        0x7f,   //8
};
#endif//GBM_DVD


/**************************************************************************
 *  Function Name: dsp_watchdog                           
 *  Purposes:                                                             
 *    DSP watch dog mechanism                             
 *  Descriptions:                                                         
 *    We use DSP watch dog to monitor DSP. 
 *    If DSP behavier abnormally, watch dog will reset DSP.
 *  Arguments:                                                            
 *    
 *  Returns:                                                              
 *
 *  See also:                                                             
 *    
 **************************************************************************/
inline void dsp_watchdog(void)
{
	//DSP watchdog
	if(dspWatchDog!=DSP_WD_INIT)
	{
		extern const UINT32 ir_invalid_state[];
		int reset_cnt=0;
		
		if(ir_invalid_state[IRC_RESET_DSP]&(0x01<<play_state))
			reset_cnt=1;
		
		if(audio_only&&(adv_search_time||video_slow))
			reset_cnt=0;
		
		if( (oldDSPbarrier!=AudioGetBarrier())||reset_cnt||(pe_run==0) )//terry 2003-8-6 18:02
		{
			oldDSPbarrier = AudioGetBarrier();
			dspWatchDog = 0;
		}
		else
		{
			dspWatchDog++;
			if (dspWatchDog > DSPWATCHDOG)
			{
				dspWatchDog = 0;
				if(!spg_game_pad) //axel for avoiding SMF->SPG DSP always reset 20051220
				AUDIF_Reset_DSP();//2004AUDDRV DSPReset();//reset DSP				
				printf("reset DSP\n");				
			}
		}
	} //DSP watchdog
}

/**************************************************************************
 *  Function Name: AudioSetEchoPara                           
 *  Purposes:                                                             
 *    Set Echo Parameter                             
 *  Descriptions:                                                         
 *    Set Echo parameter through AuioIOControl
 *  Arguments:                                                            
 *    x in : Echo Parameter
 *  Returns:                                                              
 *    1 : success 
 *    0 : fail  
 *   -1 : not support
 *  See also:                                                             
 *    
 **************************************************************************/
#if 0 //2004AUDDRV : move to auddrv.c
#ifdef USE_MIC_ECHO_PARAM
int AudioSetEchoPara(UINT16 x)
{
    int res;
    
    res = AudioSetEcho(echo_para[x][0],echo_para[x][1] );
	
    return res;
}
#endif

/**************************************************************************
 *  Function Name: AudioSetVolume                          
 *  Purposes:                                                             
 *    Set Audio Volume                             
 *  Descriptions:                                                         
 *    Set Audio Volume through AuioIOControl
 *  Arguments:                                                            
 *    x in : Audio Volume
 *  Returns:                                                              
 *    1 : success 
 *    0 : fail  
 *   -1 : not support
 *  See also:                                                             
 *    
 **************************************************************************/
//freyman 2002-7-26 21:40
//2002-7-27 11:53
#ifdef SUPPORT_AMP
int AudioSetVolume(UINT16 x)
{
    int res;
    
    res = AudioIOControl(VOLUME, x, 0);
	
    return res;
}
#endif



#ifdef      NO_AUD_MIC_OFF
int AudioSetVolume(UINT16 x)
{   
    int res=AudioIOControl(VOLUME, x, 0);
    
    //printf("<x:%x>\n",x);
    if(x)
		x=mic_volume;
    
    AudioSetMICVol(x);
    
    return res;    
}
#endif
#ifdef      NO_AUD_ECHO_OFF
int AudioSetVolume(UINT16 x)
{   
    int res=AudioIOControl(VOLUME, x, 0);
    
    //printf("<x:%x>\n",x);
    if(x)
		x=echo_level;
    
    AudioSetEcho(x, x);
    
    return res;    
}
#endif
#endif //2004AUDDRV

/**************************************************************************
 *  Function Name: dsp_AD_cmd                          
 *  Purposes:                                                             
 *      Set command to A/D gain channel 1 and channel 2                          
 *  Descriptions:                                                         
 *    
 *  Arguments:                                                            
 *    cmd in : 1200 for A/D gain channel 1, 1700 for A/D gain channel 2
 *    cType  : parameter to A/D
 *  Returns:                                                              
 *    
 *  See also:                                                             
 *    
 **************************************************************************/
void dsp_AD_cmd(UINT16 cmd,UINT16 cType)
{	
	if(cType!=0)//2002-5-29 for fuss mic
			regs0->dsp24_port[1] = 0xffff;
			regs0->dsp24_port[0] = cmd | (MICVolTab[cType]);
			
            #ifdef DSPADUIODBG
            printf("AD:0x%x ", (VolTab[cType*2]));
            #endif
}


/**************************************************************************
 *  Function Name: dsp3_if_set_vol                         
 *  Purposes:                                                             
 *      Set Audio Volume directly (didn't through AudioIOControl)                          
 *  Descriptions:                                                         
 *    
 *  Arguments:                                                            
 *    cType in : Index for VolTab[ ]
 *  Returns:                                                              
 *    
 *  See also:                                                             
 *    
 **************************************************************************/
#if 0 //2004AUDDRV
/*
*  Terry,2004/2/11 04:58PM
*/
//#define VOL0_IS_NO_VOICE
//mute: cType=0 , port1=0
//vol0: cType=0 , port1=1
//BBK vol0: cType=0 , port1=1
void dsp3_if_set_vol(UINT8 cType)
{
   printf("cType:%d\n",cType);
 
   if (user_mute)  regs0->dsp24_port[1] = 0;
//nono mark it.4-8-31 10:52
#if defined(NO_DTS_OUTPUT)&&!defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)&&!defined(EASTECH_NEW_SETUP_MENU)//4-2-12 18:36
   else if(setup_DTSCD_IsSet2SPDIF_PCMAndOff()==1)
   {
      regs0->dsp24_port[1] = 0;
      cType=0;
   } 
#endif
   else if( ( (audio_only==1)&&((adv_search_time<4)&&(adv_search_time>(-4))) )||(cType==0))
   {
      if (  (cd_subtype==CD_DTS) &&(adv_search_time)	)    regs0->dsp24_port[1]= 0;
      else 
      {
#ifdef  MP3_CD_FF1_BF1_MUTE//YX822BC//nono 20020822
        //mix YUXING822BC when forward||backwardX2,pressing SELECT,demute will be run.
        if(adv_search_time)
           regs0->dsp24_port[1] = 0;
        else
#endif

#ifdef VOL0_IS_NO_VOICE
        regs0->dsp24_port[1]=0;
#else
	regs0->dsp24_port[1]=1;
#endif	
					
       }
   }
            
   //Jeff 20020530
   if(cType!=0)  regs0->dsp24_port[1] = 0xffff;   
			
   if (bOutVol != VolTab[cType]) 
   {
        regs0->dsp24_port[0] = 0x1100 | (VolTab[cType]);
        bOutVol = VolTab[cType];
#ifdef Ti3001_OSD_UI_1
        amp_setup[ADDR_M_VOL]=audio_volume;
        save_amplifier_setup(ADDR_M_VOL+ADDR_I2C_START,&audio_volume);
#endif

#ifdef VOLUME_RECODE
       {  
         int volume;			     	
#ifdef CNTR_5SPK_VOLUME
         volume=WriteToI2c(0xa0, ADDR_I2C_VOLUME, (BYTE *)&volume_5SPK[0],1);
#else
         volume=WriteToI2c(0xa0, ADDR_I2C_VOLUME, (BYTE *)&audio_volume, 1);
#endif
       }
#endif

   } else if (bOutVol==0) 
   {
     //there are two types of volume-0: one is sound-0(0x1100-0x0001), and the other one is mute(0x1100-0x0000)
     //bOutVol only record 0x1100(not include 0x0001 or 0x0000), so we force to send it
     regs0->dsp24_port[0] = 0x1100;
   }
   
#ifdef DSPADUIODBG
   printf("Source VOLUME,VolTab[cType]:%d cType:%d bOutVol:%d",VolTab[cType],cType,bOutVol);
   printf("regs0->dsp24_port[1]=%x\n", regs0->dsp24_port[1]);
#endif   
}
	

/**************************************************************************
 *  Function Name: AudioIOControl                         
 *  Purposes:                                                             
 *     Set command to DSP                          
 *  Descriptions:                                                         
 *     Set command to DSP through dsp24_port[0] and dsp24_port[1]
 *  Arguments:                                                            
 *     wCode in : Command code
 *     cType in : sub-command or parameter
 *     wParam in : optional parameter
 *  Returns:                                                              
 *     1 : success 
 *     0 : fail  
 *    -1 : not support
 *  See also:                                                             
 *    
 **************************************************************************/	
//Do DSP Audio-IO-Control
//wCode:Command code
//cType:sub-command or parameter
//wParam:optional parameter
#ifdef SUPPORT_SOUND_EFFECT
int AudioIOControl(UINT16 wCode, UINT32 cType, UINT32 wParam)
#else
int AudioIOControl(UINT16 wCode, BYTE cType, UINT16 wParam)
#endif
{
    //int i;  //terry,2004/2/10 05:08PM
    int iRes = 0;
    //UINT32 unVol=0;

#ifdef NO_AUDIO_DSP
    return 1;
#endif    
    
    //these DSP code doesn't support generic audio command
    if (coding_mode_now&(AUDIF_CODING_MODE_NES) ) {
        return 1;
    }

    #ifdef SUPPORT_MIDI_MENU_SEL // Jeff 20031104
    if (coding_mode_now&AUDIF_CODING_MODE_MIDI)
    {
        //extern BYTE bMidiPlayerBoolean;
        //if (bMidiPlayerBoolean==0) 
        extern BYTE midiState;   //dtb in 20040109
        if(midiState != 2) //MIDI_STATE_PAYLOAD
            return 1;
    }
    #endif
	
    regs0->dsp24_port[1] = wParam;
	
    switch (wCode) {
	case FLOW:
		regs0->dsp24_port[0] = 0x0200 | cType;
		
		switch (cType) {
		case AUDIOPLAY:
            #ifdef DSPADUIODBG
			printf("AUDIOPLAY ");
            #endif
			break;
		case AUDIOCONTINUE:
            #ifdef DSPADUIODBG
			printf("AUDIOCONTINUE ");
            #endif
			break;
		case AUDIOSTOP:
            #ifdef DSPADUIODBG
			printf("AUDIOSTOP ");
            #endif
			break;
		case AUDIOPAUSE:
            #ifdef DSPADUIODBG
			printf("AUDIOPAUSE ");
            #endif
			break;
		case AUDIOFLUSH:
            #ifdef DSPADUIODBG
			printf("AUDIOFLUSH ");
            #endif
			break;
			
		case AUDIOFF2X:
		case AUDIOFF4X:
		case AUDIOFF5X:		//NONO 4-2-10 22:22
		case AUDIOFF8X:
		case AUDIOFF10X:	//NONO 4-2-10 22:22
		case AUDIOFF20X:
		case AUDIOFF16X:	// Robert 2003/12/14
		case AUDIOFF30X:	//NONO 4-2-10 22:22
		case AUDIOFF32X:
		case AUDIOFF60X:	//NONO 4-2-10 22:22
		    #ifdef DSPADUIODBG
			printf("AUDIOFF\n");
			#endif
			//to check DSP mode
			if (regs0->dsp24_port[5]!=0) {
				regs0->dsp24_port[0] = 0x0200 | cType;
                #ifdef DSPADUIODBG
				printf("AUDIOFF-%d x ", cType);
                #endif
			}
			break;
			
		case AUDIOFF2PLAY:
            #ifdef DSPADUIODBG
			printf("AUDIOFF2PLAY ");
            #endif
			break;
			
		default:
			iRes = -1;
			break;
		} //end of switch (cType)
		
		break;
        case OUTMODE:
            regs0->dsp24_port[0] = 0x0300 | cType;
			
            #ifdef DSPADUIODBG
            printf("OUTMODE:%d %x", cType, regs0->dsp24_port[1]);
            #endif
            break;
        case VOLUME:            
            dsp3_if_set_vol(cType);//terry,2004/2/11 05:40PM
	    break;
        case KEY:
            regs0->dsp24_port[0] = 0x0500 | cType;
			
            #ifdef DSPADUIODBG
            printf("KEY:%d ", cType);
            #endif
            break;
        case ECHO:
            regs0->dsp24_port[0] = 0x0600 | cType;
			
            #ifdef DSPADUIODBG
            printf("ECHO:%d ", cType);
            #endif
            break;
        case SURROUND:
            regs0->dsp24_port[0] = 0x0700 | cType;
			
            #ifdef DSPADUIODBG
            printf("SURROUND:%d ", cType);
            #endif
            break;
        case SUBWOOF:
            regs0->dsp24_port[0] = 0x0800 | cType;
			
            #ifdef DSPADUIODBG
            printf("SUBWOOF:%d ", cType);
            #endif
            break;
        #ifdef TEST_BASS_MANAGEMENT 
            #ifdef TEST_BASS_COMMAND
        case BASSMANAGEMENT:        
             regs0->dsp24_port[0] = 0x2000 | cType;			                  
                #ifdef DSPADUIODBG
                printf("test: BASS_MANAGEMENT:%x\n", wParam);
                #endif
             break;   
            #endif
        #endif    
        case SPDIF:
            if (is_dts_force_spdif_bitstream() && cType==1) cType=2;
            regs0->dsp24_port[0] = 0x0900 | cType;
			
            #ifdef DSPADUIODBG
            printf("SPDIF:%d ", cType);
            #endif
            break;
        case EQ:
            regs0->dsp24_port[0] = 0x0a00 | cType;
			
            #ifdef DSPADUIODBG
            printf("EQ:%d ", cType);
            #endif
            break;
        case MIC:
            regs0->dsp24_port[0] = 0x0d00 | cType;
			
            #ifdef DSPADUIODBG
            printf("MIC:%d ", cType);
            #endif
            break;
        case AD:
        	dsp_AD_cmd(0x1200,cType);
            break;
        case AD_2:  //wangfeng 2003-09-12 17:11
        	dsp_AD_cmd(0x1700,cType);
            break;
        case SPKDELAY:
            regs0->dsp24_port[0] = 0x0c00 | cType;
			
            #ifdef DSPADUIODBG
            printf("SPKDELAY(%d):%d ms\n", cType, wParam);
            #endif
			
            break;
			
        case FSPKGAIN:
            regs0->dsp24_port[0] = 0x1300 | (VolTab[cType*2]);//nono 2003-9-3 11:54 add"*2"
			
            #ifdef DSPADUIODBG
            printf("FSPKGAIN:%d\n", cType);
            #endif
			
            break;
//wanghaoying add 2003-12-12 18:03
#if     !defined(CNTR_5SPK_VOLUME)
        case CSPKGAIN:
#ifdef YUXING_DVD
            //wangap add it when CSPKGAIN is 0/1 the volumn is wrong 2003/12/23
            if((cType+2)==257)
            regs0->dsp24_port[0] = 0x1500 | 0x02;
            else if((cType+2)==256)
            regs0->dsp24_port[0] = 0x1500 | 0x00;
            else
            regs0->dsp24_port[0] = 0x1500 | (VolTab[(cType+2)*2]);
#else
            regs0->dsp24_port[0] = 0x1500 | (VolTab[cType*2]);
#endif
            #ifdef DSPADUIODBG
            printf("CSPKGAIN:%d\n", cType);
            #endif
			
            break;
#endif

        case SSPKGAIN:
            regs0->dsp24_port[0] = 0x1400 | (VolTab[cType*2]);//nono 2003-9-3 11:54 add"*2"
			
            #ifdef DSPADUIODBG
            printf("SSPKGAIN:%d\n", cType);
            #endif
			
            break;

#ifdef CNTR_5SPK_VOLUME
        case FLSPKGAIN:
            regs0->dsp24_port[0] = 0x1A00 | (VolTab[cType]);
			
	    #ifdef VOLUME_RECODE
			     {  
			     	int volume;			     	
				//printf("audio_vol=%d\n",audio_volume);
				
				//if(action_click)
				volume=WriteToI2c(0xa0, ADDR_I2C_VOLUME+1, (BYTE *)&volume_5SPK[1], 1);
			     }
	    #endif
	    			
            #ifdef DSPADUIODBG
            printf("FLSPKGAIN:%d\n", cType);
            #endif
            break;

        case FRSPKGAIN:
            regs0->dsp24_port[0] = 0x1B00 | (VolTab[cType]);
	    #ifdef VOLUME_RECODE
			     {  
			     	int volume;			     	
				printf("audio_vol=%d\n",audio_volume);
			
				//if(action_click)
				volume=WriteToI2c(0xa0, ADDR_I2C_VOLUME+2, (BYTE *)&volume_5SPK[2], 1);
			     }
	    #endif		
            #ifdef DSPADUIODBG
            printf("FRSPKGAIN:%d\n", cType);
            #endif
            break;

        case SLSPKGAIN:
            regs0->dsp24_port[0] = 0x1C00 | (VolTab[cType]);
	    #ifdef VOLUME_RECODE
			     {  
			     	int volume;			     	
				printf("audio_vol=%d\n",audio_volume);
			
				//if(action_click)
				volume=WriteToI2c(0xa0, ADDR_I2C_VOLUME+3, (BYTE *)&volume_5SPK[3], 1);
			     }
	    #endif	
            #ifdef DSPADUIODBG
            printf("SLSPKGAIN:%d\n", cType);
            #endif
            break;

        case SRSPKGAIN:
            regs0->dsp24_port[0] = 0x1D00 | (VolTab[cType]);
	    #ifdef VOLUME_RECODE
			     {  
			     	int volume;			     	
				printf("audio_vol=%d\n",audio_volume);
			
				//if(action_click)
				volume=WriteToI2c(0xa0, ADDR_I2C_VOLUME+4, (BYTE *)&volume_5SPK[4], 1);
			     }
	    #endif	
            #ifdef DSPADUIODBG
            printf("SRSPKGAIN:%d\n", cType);
            #endif
            break;


        case CSPKGAIN:
            regs0->dsp24_port[0] = 0x1500 | (VolTab[cType]);
	    #ifdef VOLUME_RECODE
			     {  
			     	int volume;			     	
				printf("audio_vol=%d\n",audio_volume);
			
				//if(action_click)
				volume=WriteToI2c(0xa0, ADDR_I2C_VOLUME+5, (BYTE *)&volume_5SPK[5], 1);
			     }
	    #endif	
            #ifdef DSPADUIODBG
            printf("CSPKGAIN:%d\n", cType);
            #endif
			
            break;

        case SWSPKGAIN: //Jeff 20031028
            regs0->dsp24_port[0] = 0x1E00 | (VolTab[cType]);

        #ifdef VOLUME_RECODE
            {  
                int volume;			     	
                printf("audio_vol=%d\n",audio_volume);
			
                //if(action_click)
                volume=WriteToI2c(0xa0, ADDR_I2C_VOLUME+6, (BYTE *)&volume_5SPK[6], 1);
            }
        #endif	

            #ifdef DSPADUIODBG
            printf("SWSPKGAIN:%d\n", cType);
            #endif

            break;

/*        case Volume_Font_ID:
        	if (user_mute) 
            {
                regs0->dsp24_port[1] = 0;
               
            }

            else if( ( (audio_only==1)&&((adv_search_time<4)&&(adv_search_time>(-4))) )||(cType==0)) //nono 20020822
            {//nono 2-4-30 0:35
                if (  (cd_subtype==CD_DTS) &&//20020725
					(adv_search_time)//>1) //|| (adv_search_time<-1) )//2-6-20 23:43
					) 
					
                { //Jeff 20020614
                    regs0->dsp24_port[1] = 0;
                } else {
#ifdef  MP3_CD_FF1_BF1_MUTE//YX822BC//nono 20020822
					//mix YUXING822BC when forward||backwardX2,pressing SELECT,demute will be run.
					if(adv_search_time)
						regs0->dsp24_port[1] = 0;
					else
#endif
						regs0->dsp24_port[1] = 1;
					
                }
            }
            
            //Jeff 20020530
            if(cType!=0)//2002-5-29 for fuss mic
				regs0->dsp24_port[1] = 0xffff;
			
            //To reduce redundant volume setting, Jeff 20020702
            //regs0->dsp24_port[0] = 0x1100 | (VolTab[cType]);
            if (bOutVol != VolTab[cType]) {
				regs0->dsp24_port[0] = 0x1100 | (VolTab[cType]);
				bOutVol = VolTab[cType];

#ifdef VOLUME_RECODE
			     {  
			     	int volume;			     	
				printf("audio_vol=%d\n",audio_volume);
				
				if(action_click)
				volume=WriteToI2c(0xa0, ADDR_I2C_VOLUME, (BYTE *)&audio_volume, 1);
			     }
#endif

            } else //Jeff 20020726
				if (bOutVol==0) {
                    //there are two types of volume-0: one is sound-0(0x1100-0x0001), and the other one is mute(0x1100-0x0000)
                    //bOutVol only record 0x1100(not include 0x0001 or 0x0000), so we force to send it
                    regs0->dsp24_port[0] = 0x1100;
		                   
	}
        	break;
*/        	
#endif //#ifdef CNTR_5SPK_VOLUME

#ifdef SUPPORT_PROLOGIC_II		// alan, 2003/7/11 03:28¤U¤È
    	case PROLOGIC:
        if( check_chipinfo(6)==0 ) cType = 0x10;
    		regs0->dsp24_port[0] = 0x0E00 | cType;
#ifdef DSPADUIODBG
    		printf("PROLOGIC set command %x to DSP\n",cType);	
#endif
    		break;
#endif
		case SCORING:	// alan, 2003/9/3 02:38¤U¤È
			regs0->dsp24_port[0] = 0x0B00 | 0x01 ;
			break;
#ifdef SUPPORT_REP_READ
		case RECORDMIC:
			regs0->dsp24_port[0] = 0x1F00 | cType;
			break;	
#endif
#ifdef	SUPPORT_SOUND_EFFECT
	case SNDEFFECT://sound effect shawn 2004.10.07
		//printf("cType=%x,wParam=%d\n",cType,wParam);
		cType=cType/3;//transfer to word-based ptr 
		regs0->dsp24_port[0] = 0x2000 |(UINT16) ((cType>>16)&0xff); // word pointer from DSP viewpoint	
		regs0->dsp24_port[1] = (UINT16)(cType&0x0000ffff);
		wait_dsp_port0_5(1,0,0,100000);
		regs0->dsp24_port[0] = 0x2000 |(UINT16) ((wParam>>16)&0xff); //size
		regs0->dsp24_port[1] = (UINT16)(wParam&0x0000ffff);
			break;
#endif	
        default:
            iRes = -1;
            break;
    } //end of switch
	
    if (iRes != -1) 
    {
        iRes = wait_dsp_port0_5(1,0,0,100000);//terry,2003/8/8 03:45AM
    }
	
    return iRes;
}

/**************************************************************************
 *  Function Name: AudioDemute                         
 *  Purposes:                                                             
 *     Demute Audio                          
 *  Descriptions:                                                         
 *     Set volumes of speakers to the originals before mute.
 *  Arguments:                                                            
 *
 *  Returns:                                                              
 *     1 : success 
 *     0 : fail  
 *    -1 : not support
 *  See also:                                                             
 *    
 **************************************************************************/
inline int AudioDemute()
{
    int iRes;
    
    user_mute = 0;
    
#ifdef MUTE_EXECUTE_MIC

#ifdef	MIC_2CHANNEL//nono 4-1-5 11:51
	AudioSetMICVol_2(setup_GetMICVol2());
    AudioSetMICVol(setup_GetMICVol());
#else
    AudioSetMICVol(mic_volume);
#endif//#ifdef	MIC_2CHANNEL

#endif//#ifdef MUTE_EXECUTE_MIC
    
    
#ifdef CNTR_5SPK_VOLUME
{//terry,2004/2/17 10:57AM
      int i;
      
      for (i=0; i<7; i++) 
      {        
         iRes=ReadFromI2c(0xa0,ADDR_I2C_VOLUME+i,(BYTE *)&audio_volume,sizeof(audio_volume));//terry,2004/2/17 10:56AM
         if(i==0)
         {
	         #ifdef CNTR_5SPK_TYPE_2    //linrc add 2004-10-12 9:51
	         if(IS_AUDIF_CODING_MODE_LPCM || IS_AUDIF_CODING_MODE_DTS 
	             || IS_AUDIF_CODING_MODE_PCM || IS_AUDIF_CODING_MODE_WMA
	             || IS_AUDIF_CODING_MODE_DTSCD)
	         {
	    iRes = AudioSetVolume(volume_5SPK[0]);
	         }   
	         else iRes = AudioSetVolume(15);  
	         #else
	         iRes = AudioSetVolume(volume_5SPK[0]);
	         #endif	          
	     }
	 else
	    AudioIOControl(FLSPKGAIN+i-1,volume_5SPK[i],0);
	     
      }
}		
#else//#ifdef CNTR_5SPK_VOLUME

#ifndef AC3_BASS_MANAGEMENT
                                if(downmix_off){
	iRes = AudioSetVolume(audio_volume);
	                            //set front speaker gain
								AudioSetFSPKGain(fspk_volume/2);
								//set center speaker gain
								AudioSetCSPKGain(cspk_volume/2);
								//set surround speaker gain
								AudioSetSSPKGain(sspk_volume/2);   
                                }
                                else								    
#endif   
              
	iRes = AudioSetVolume(audio_volume);//wangap
#endif//#ifdef CNTR_5SPK_VOLUME	
    return iRes;
}

/**************************************************************************
 *  Function Name: AudioSetPlay
 *  Purposes:                                                             
 *     Set DSP to Play state                         
 *  Descriptions:                                                         
 *     
 *  Arguments:                                                            
 *
 *  Returns:                                                              
 *     1 : success 
 *     0 : fail  
 *  See also:                                                             
 *    
 **************************************************************************/
//Send Play command to DSP
// return 1: success
//        0: fail
int AudioSetPlay()
{
    int i;
    int iRes;

    printf("audio play 1\n");
	
    if (show_logo==1)
        return 1;
	
    i = regs0->dsp24_port[5];
    if (i==1) 
    {//DVD is under PLAY mode
        printf("audio play ,o2\n");
		
		//avoid volume0 noise when play mpeg dat file.xulf 2004-5-25                
	    //AudioSetVolume(audio_volume); //nono mark it.4-6-10 13:09 Now the bug is fixed OK.
        
        return 1;
    }
	
    #ifdef SDRAM_16Mb_Mode//wangap 2004/11/18
    dsp3_ramp_up(1);
    #endif
    if(!user_mute)
    {
#ifdef MP3_CD_FF1_BF1_MUTE//YX822BC//nono 2-8-23 18:39
		//mix YUXING822BC when forward||backwardX2,pressing SELECT,demute will be run.
		if(!adv_search_time)
#else//#if 1//def FUSS_DVD//nono 2-4-29 23:26
			//terry,2002/4/29 05:10PM
			//cdda,mix vcd and cdda,cdrom in ff>=4 bf<=-4
			//demute cannot be run
			//if( (audio_only)&&(cd_type_loaded!=CDROM) )//nono 2-4-25 0:35
			if( (audio_only==0)||((adv_search_time<4)&&(adv_search_time>(-4)))
				)
#endif
			{
                AudioDemute();
			}
			//printf(__FUNCTION__"<a3>\n");//2-4-25 0:22
			//AudioSetVolume(audio_volume);//jeff 2002-04-29
    }
	
    //for MP3
    if (cd_type_loaded == CDROM) {
        iRes = AudioIOControl(FLOW, AUDIOPLAY, 1); //PLAY command
    } else {
        iRes = AudioIOControl(FLOW, AUDIOPLAY, 0); //PLAY command
    }
	
    //Jeff 20020411
    if ( (adv_search_time > 1) &&
		( (cd_type_loaded == CDROM) ||
		(cd_subtype==CD_DTS) //nono 20020705
		//(coding_mode_now==AUDIF_CODING_MODE_DTSCD)
		)
		)
    { //set DSP to FF mode
        AudioFastForward(adv_search_time);
    }

    printf("audio play ,o2\n");	
    return iRes;
}

/**************************************************************************
 *  Function Name: AudioSetStop
 *  Purposes:                                                             
 *     Set DSP to Stop state                         
 *  Descriptions:                                                         
 *     
 *  Arguments:                                                            
 *
 *  Returns:                                                              
 *     1 : success 
 *     0 : fail  
 *  See also:                                                             
 *    
 **************************************************************************/
//Send Stop command to DSP
// return 1: success
//        0: fail
int AudioSetStop()
{
//    int i;
    int iRes,stop;
	
    if (show_logo==1)
        return 1;
	
    //to check DSP mode
    if (regs0->dsp24_port[5]==0) {
        //The status of DSP in under STOP, so we skip this command
        return 1;
    }
    #ifdef SDRAM_16Mb_Mode 
    //2004/11/18 wangap add this SDRAM_16Mb_Mode condition to avoid mic no effect when implement stop
    dsp3_ramp_down(1);
    dsp3_ramp_wait();
    #endif
    iRes = AudioIOControl(FLOW, AUDIOSTOP, 0); //STOP command
	
    //wait until DSP enters STOP mode
    stop = wait_dsp_port0_5(1,1,0,100000);//terry,2003/8/8 03:45AM
    /*
    for (i=0; i<100000; i++) {
        if ( ( (regs0->dsp24_port[0] & 0x8000) == 0x8000)
            && (regs0->dsp24_port[5]==0) ) //DSP enters STOP mode
        {
            break;
        }
    }*/
	
    //if ( (iRes>0) && (i<100000) ) 
    if ( (iRes>0) && stop ) 
    {
        iRes = 1;
		
#ifdef DSPADUIODBG
        printf("AudioSetStop SUCCESS\n");
#endif
    } else {
        iRes = 0;
		
#ifdef DSPADUIODBG
        printf("AudioSetStop FAIL\n");
#endif
    }
	
    return iRes;
}
#endif //2004AUDDRV

//terry,2004/2/17 10:53AM
#ifdef DVD_AUDIO	
//mode:0 premitted stero playback mode
//mode:1 prohibited stero playback mode
/*void AudioSetSteroMode(int mode)
{	
   printf("stereo:%x\n",mode);
   
}*/
#endif

/**************************************************************************
 *  Function Name: AudioSetPause
 *  Purposes:                                                             
 *     Set DSP to Pause state                         
 *  Descriptions:                                                         
 *     
 *  Arguments:                                                            
 *
 *  Returns:                                                              
 *     1 : success 
 *     0 : fail  
 *  See also:                                                             
 *    
 **************************************************************************/
#if 0 //2004AUDDRV move to auddrv.c
//Send Pause command to DSP
// return 1: success
//        0: fail
int AudioSetPause()
{
//    int i;
    int iRes;
	
printf("audio pause 1\n");

	#ifdef	MP3_JPEG_COWORK
	if(pFsJpeg->gifsFuncBtn==FS_FUNC_JPEG)//if JPEG, then do not pause
		return	0;
	#endif
	
    //to check DSP mode
    if (regs0->dsp24_port[5]==2) {
        //The status of DSP in under PAUSE, so we skip this command
printf("audio pause,o1\n");        
        return 1;
    }
	
    iRes = AudioIOControl(FLOW, AUDIOPAUSE, 0); //PAUSE command
	
    //wait until DSP enters PAUSE mode
    wait_dsp_port0_5(1,1,2,100000);//terry,2003/8/8 03:45AM
    //for (i=0; i<100000; i++) { //Jeff 20011121
    //    if ( ( (regs0->dsp24_port[0] & 0x8000) == 0x8000)
    //        && (regs0->dsp24_port[5]==2) ) //DSP enters PAUSE mode
    //    {
    //        break;
    //    }
    //}
	
    AudioSetVolume(0);//terry,2002/5/10 12:05¤W¤È, no audio when pause

    printf("audio pause,o2\n");
    return iRes;
}

/**************************************************************************
 *  Function Name: AudioSetContinue
 *  Purposes:                                                             
 *     Set DSP to Continue state                         
 *  Descriptions:                                                         
 *     
 *  Arguments:                                                            
 *
 *  Returns:                                                              
 *     1 : success 
 *     0 : fail  
 *  See also:                                                             
 *    
 **************************************************************************/
//Send Continue command to DSP
// return 1: success
//        0: fail
int AudioSetContinue()
{
    int i;
    int iRes=1;
	
#ifdef	MP3_JPEG_COWORK
	if(pFsJpeg->gifsFuncBtn==FS_FUNC_JPEG)//if JPEG, then do not continue
		return	0;
#endif

    if(show_logo==1)
		return 1;
      #ifdef SDRAM_16Mb_Mode//wangap 2004/11/18
      dsp3_ramp_up(1);
      #endif
    //to check DSP mode
    i = regs0->dsp24_port[5];
    if (i==0) {//DSP is under STOP mode, so we send PLAY command to DSP
        AudioIOControl(FLOW, AUDIOPLAY, 0);
        return 1;
    }
	
    iRes = AudioIOControl(FLOW, AUDIOCONTINUE, 0); //CONTINUE command
	
    return iRes;
}

/**************************************************************************
 *  Function Name: AudioSetFastForward
 *  Purposes:                                                             
 *     Set DSP to FastForward state                         
 *  Descriptions:                                                         
 *     
 *  Arguments:                                                            
 *
 *  Returns:                                                              
 *     1 : success 
 *     0 : fail  
 *  See also:                                                             
 *    
 **************************************************************************/
int AudioFastForward(BYTE speed)
{
    int     iRes = 0;
    BYTE    cFF = AUDIOFF2X;
	
    switch (speed) {
	case 2:
		cFF = AUDIOFF2X;
		break;
	case 4:
		cFF = AUDIOFF4X;
		break;
	case 5://nono 4-2-10 20:27
		//cFF = AUDIOFF5X;
		cFF = AUDIOFF4X;
		break;
	case 8:
		cFF = AUDIOFF8X;
		break;
	case 10://nono 4-2-10 20:27
		//cFF = AUDIOFF10X;
		cFF = AUDIOFF8X;
		break;
	case 20:
		cFF = AUDIOFF20X;
		break;
	case 16:
		cFF = AUDIOFF16X;
		break;
	case 30://nono 4-2-10 20:27
		//cFF = AUDIOFF30X;
		cFF = AUDIOFF20X;
		break;
	case 32:
		cFF = AUDIOFF32X;
		break;
	case 60://nono 4-2-10 20:27
		//cFF = AUDIOFF60X;
		cFF = AUDIOFF32X;
		break;
    }

    iRes = AudioIOControl(FLOW, cFF, 0);
	
    return iRes;
}
#endif //2004AUDDRV

/**************************************************************************
 *  Function Name: getCDDAType
 *  Purposes:                                                             
 *     Get the CDDA Type from DSP (HDCD/CDDA)
 *  Descriptions:                                                         
 *     
 *  Arguments:                                                            
 *
 *  Returns:                                                              
 *     1 : HDCD 
 *     0 : CDDA  
 *  See also:                                                             
 *    
 **************************************************************************/
int getCDDAType()
{
	//BYTE    *q=(BYTE *)(SDRAM_BASE_UNCACHED+regs0->pcmya*1024);
	UINT32  idCDDA;
	//UINT32  c0, c1, c2;
	
	//Steven 2006/10/04 modify , use get_dsp3_pcm_value() instead of directly access address //
	//c0 = *(bpcm_ya_ptr+98);
	//c1 = *(bpcm_ya_ptr+97);
	//c2 = *(bpcm_ya_ptr+96);
	//idCDDA = (UINT32)( c0 | (c1<<8) | (c2<<16) ); //3*32+2
	idCDDA = get_dsp3_pcm_value(DSP_RUNTIME_HDCD_FLAG);
	//printf("idCDDA=%08x\n", idCDDA);


	if (idCDDA==0x7E0FA0)
		return 1;
	
	return 0;
}

#if 0
/**************************************************************************
 *  Function Name: MidiAudioCtrl
 *  Purposes:                                                             
 *     Set DSP state when play MIDI
 *  Descriptions:                                                         
 *     
 *  Arguments:                                                            
 *
 *  Returns:                                                              
 *     1 : success 
 *     0 : fail  
 *  See also:                                                             
 *    
 **************************************************************************/
#ifdef SUPPORT_MIDI
// fast-forward, slow-forward, normal-play
int MidiAudioCtrl(UINT16 wCode, BYTE cType, UINT16 wParam)
{
    int iRes = 0;

    regs0->dsp24_port[1] = wParam;

    printf("MidiAudioCtrl:cType=%x\n", cType);
	
    switch (wCode) {
	case FLOW:
		regs0->dsp24_port[0] = 0x0200 | cType;
		
		switch (cType) {
		case AUDIOPLAY:
            iRes = 1;
            if (coding_mode_now & AUDIF_CODING_MODE_MP3) {
                regs0->dsp24_port[0] = 0x0200 | 0x19; //special command for Midi-MP3 change to normal play, Jeff 20031119
            }
            break;
        case AUDIOFF1_25X:
        case AUDIOFF1_50X:
        case AUDIOFF1_75X:
        //case AUDIOFF2_00X:
        case AUDIOFF2_00X:
        case AUDIOSF1_25X:
        case AUDIOSF1_50X:
        case AUDIOSF1_75X:
        case AUDIOSF2_00X:
            printf("Jefftest\n");
            iRes = 1;
            //to check DSP mode
			if (regs0->dsp24_port[5]!=0) 
            {
				regs0->dsp24_port[0] = 0x0200 | cType;
			}

            #ifdef DSPADUIODBG
            printf("MidiAudioCtrl-%x\n", cType);
            #endif

            break;
        }
    }

    if (iRes) {
        iRes = wait_dsp_port0_5(1,0,0,100000);
    }

    return iRes;
}
#endif
#endif // end #if 0

