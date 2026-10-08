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

/*WMA/HDCD:
* "This product is protected by certain intellectual property rights of
* Microsoft and cannot be used or further
* distributed without a license from Microsoft.
*/

//
// FILE
// dsp3_config.c
//

//
//  Terry,2004/2/17 04:59PM
//  a.add in write24 function  b.add LmRm/DTS 9624 config.
//

#include "user_init.h"//nono 2003-10-21 21:04
#include "config.h"
#include "regmap.h"
#include "global.h"

#include "memmap.h"
#include "lbc.h"

#include "NESinit.h"
#include "gpio.h"

extern UINT8 power_on_mute;//terry 20030805
extern UINT32 setupGetSetting(BYTE x);
extern int setup_IsSet2SPDIF_Bitstream();
extern void setup_SetFreqMaskConfig(void);
extern int is_dts_force_spdif_bitstream(void);
extern int check_chipinfo(int n);

#include "dsp3rom.h"    //Jeff 20010807
#include "dsp3_if.h"
#include "auddrv.h" //2004AUDDRV oliver 20041004 for using audio driver purpose
//#include "audif.h"
#ifdef	MP3_JPEG_COWORK
#include "fsNav.h"
#endif
#ifdef SUPPORT_MIDI//axelchen for midi MP3 sync 2005/9/15 
#include "fsmidi.h"
#endif

//
// DEBUG
//
#ifndef	DVDRELEASE
//#define DSP3_DBG        1
#endif

#define	dsp3_puts(s)		((void)0)
#define	dsp3_printf(s...)	((void)0)

#ifdef	DSP3_DBG
#include "sio.h"
#include "emuio.h"
#undef	dsp3_puts
#undef	dsp3_printf
#define	dsp3_puts   		puts_nw
#define	dsp3_printf             printf_w
//#define MONE_DSP3_LOAD
//#define MONE_DSP3_ERROR
//#define DBG_DSP_CMD
#endif

#if defined(SPHE1000) && !defined(DVB1000_NON_OS)
//#define MONE_LINUX_TRAP
#endif

#ifdef MONE_LINUX_TRAP
extern BYTE mone_trap;
#define LOAD_LINUX_TRAP()	{if (mone_trap) load_linux_trap();}
#else
#define LOAD_LINUX_TRAP()
#endif

/***************************************************************************
Steven 2006/10/04 replace cache to uncache way to handshake with DSP module
      use  get_dsp_xxx_uptr(x,y) instead of get_dsp_xxx_ptr(x,y)
***************************************************************************/     
/**************************************************************************
 *  Function Name: set_aud_buf
 *  Purposes:
 *    Set audio buffer address
 *  Descriptions:
 *    Set start buffer address of IM,PM and DM for DSP
 *  Arguments:
 *    a in : IM start address
 *    b in : PM start address
 *    c in : DM start address
 *  Returns:
 *
 *  See also:
 *
 **************************************************************************/
void
set_aud_buf(unsigned a, unsigned b, unsigned c)
{
  printf("\n\n --->set audio buffer address a:%x b:%x c:%x\n",a,b,c);

  regs0->dsp24ya	= dsp24ya	= a;
  regs0->audya		= audya		= b;
  regs0->pcmya		= pcmya		= c;
  //Steven 2006/10/04 replace cache to uncache way to handshake with DSP module//
  bpcm_ya_ptr = get_dsp_pcm_uptr(0,0);//terry,2004/1/14 02:23PM
}


/**************************************************************************
 *  Function Name: write_24
 *  Purposes:
 *    write data to DSP PM
 *  Descriptions:
 *
 *  Arguments:
 *    q in/out : Start address for writing data
 *    offset in : Offset for writing data
 *    x in : Data for writing
 *  Returns:
 *    Address after writing data
 *  See also:
 *
 **************************************************************************/
//
// FUNCTION
// write_24()
//
#if 0
BYTE *write_24(BYTE *q, int offset, UINT32 x)
{
#ifdef DBG_DSP_CMD
  printf("q:%x offset:%x x:%x\n",q,offset,x);
#endif
  q     += offset*3;
  q[0]  = (x>>16) & 0x00ff;	// MSB first
  q[1]  = (x>> 8) & 0x00ff;	//
  q[2]  = (x>> 0) & 0x00ff;	// LSB last
  return q;
}
#else
void write24(int offset, UINT32 x)
{
#ifdef DBG_DSP_CMD
  printf("offset:%x x:%x\n",offset,x);
#endif
  //BYTE *q = (BYTE*)get_dsp3_pm_ptr();

  set_dsp3_pcm_value(offset,x);//Steven 2006/10/04 modify , use get_dsp3_pcm_value() instead of directly access address //

  //q     += offset*3;
  //q[0]  = (x>>16) & 0x00ff;	// MSB first
  //q[1]  = (x>> 8) & 0x00ff;	//
  //q[2]  = (x>> 0) & 0x00ff;	// LSB last
}
#endif


/**************************************************************************
 *  Function Name: set_dsp3_pcm_value
 *  Purposes:
 *    Write data to DSP PCM buffer
 *  Descriptions:
 *
 *  Arguments:
 *    off in : Offset for writing data
 *    value in : Data for writing
 *  Returns:
 *
 *  See also:
 *
 **************************************************************************/
//
// void set_dsp3_pcm_value(unsigned x_off, unsigned value)
//
void set_dsp3_pcm_value(unsigned x_off, unsigned value)
{
  #ifdef MESSAGE_QUEUE
    DSP_AudioIOControl(WRITE2PCM ,x_off,value);
  #else
	BYTE *pcm_ptr=get_dsp_pcm_uptr(x_off*3, 0);//Steven 2006/10/04 replace cache to uncache way to handshake with DSP module//

//	dsp3_printf(" set PCM @ %x %x : %x\n", x_off, pcm_ptr, value);
	*(pcm_ptr)		= (value>>16) & 0xff;
	*(pcm_ptr+1)	= (value>>8) & 0xff;
	*(pcm_ptr+2)	= (value>>0) & 0xff;
  #endif  
}

/**************************************************************************
 *  Function Name: get_dsp3_pcm_value
 *  Purposes:
 *    Read data from DSP PCM buffer
 *  Descriptions:
 *
 *  Arguments:
 *    off in : Offset for reading data
 *  Returns:
 *    Data read
 *  See also:
 *
 **************************************************************************/
//#if defined( SUPPORT_REP_READ)||defined (SUPPORT_TESTSPK) || defined(SUPPORT_AAC)//Steven 2006/10/04 mark//
UINT32 get_dsp3_pcm_value(unsigned x_off)
{
	UINT32 value;
	BYTE *pcm_ptr=get_dsp_pcm_uptr(x_off*3, 0);//Steven 2006/10/04 replace cache to uncache way to handshake with DSP module//

	value = (*pcm_ptr << 16) | (*(pcm_ptr+1) << 8) | *(pcm_ptr+2);
	dsp3_printf(" get PCM @ %x %x : %x\n", x_off, pcm_ptr, value);

	return value;
}
//#endif  //#ifdef SUPPORT_REP_READ

/**************************************************************************
 *  Function Name: dsp3_get_rest_buf_size
 *  Purposes:
 *    Get rest space of audio buffer
 *  Descriptions:
 *    Distance between Dump pointer and Barrier pointer in bytes.
 *  Arguments:
 *
 *  Returns:
 *    Rest buffer size in bytes.
 *  See also:
 *
 **************************************************************************/
inline int dsp3_get_rest_buf_size()
{
	int barN = (int)AudioGetBarrier()*3;
	int apb  = (int)AudioGetBytePtr();
	int free;

	free = barN - apb;
	if (free <= 0)
	    free += abv_size;

	return free;
}

/**************************************************************************
 *  Function Name: set_aud_buf_size
 *  Purposes:
 *    Set audio bitstream size
 *  Descriptions:
 *    Set buffer size to AUDIO_BITSTREAM_LEN*3, *3 because the unit in DSP is WORD (3 bytes)
 *  Arguments:
 *
 *  Returns:
 *
 *  See also:
 *
 **************************************************************************/
void set_aud_buf_size(void)
{
    extern UINT32 coding_mode_now;
        	
    if ((coding_mode_now==AUDIF_CODING_MODE_DTS)||(coding_mode_now==AUDIF_CODING_MODE_DTSCD))
    {
        abv_size      = DTS_AUDIO_BITSTREAM_LEN*3;
    }
#ifdef LPCM_EXTEND_BUF
    else if(coding_mode_now==AUDIF_CODING_MODE_LPCM)
    {
        abv_size      = LPCM_AUDIO_BITSTREAM_LEN*3;
    }
#endif    
#ifdef MP3_JPEG_COWORK //ycwen 2005/1/21 allocate 48K bytes for mp3 when mp3_jpeg_cowork    
    else if( (coding_mode_now==AUDIF_CODING_MODE_MP3)&&(cd_type_loaded==CDROM)&&((GetCurrentFileType()==CDROM)||(GetCurrentFileType()==CDROM_JPEG)) )
    {
        abv_size      = MP3_AUDIO_BITSTREAM_LEN*3;  
    }
#endif
//Steven 2006/08/10 enlarge LPCM playback bitstream buufer(12k) to avoid pop noise when servo ECC is 127k only//
    else if(coding_mode_now==AUDIF_CODING_MODE_LPCM)//Remark:#define DVD_SRV_BUF_SMALL also need to modify LPCM PM BUFFER to 12k in memmap_dsp3_82xx.h//
    {
        abv_size      = AUDIO_BITSTREAM_LEN*4;
    }
    else
    {
        abv_size      = AUDIO_BITSTREAM_LEN*3;
    }
        
    if(coding_mode_now!=AUDIF_CODING_MODE_JPG)
    {    
        write24(1,abv_size/3);
    }	
}

/**************************************************************************
 *  Function Name: reset_audio_buf
 *  Purposes:
 *    Reset audio buffer size, and set Dump/Barrier pointer to 0
 *  Descriptions:
 *
 *  Arguments:
 *
 *  Returns:
 *
 *  See also:
 *
 **************************************************************************/
//
// FUNCTION
// reset_audio_buf
//
void
reset_audio_buf(void)
{

#ifdef	MP3_JPEG_COWORK//screen the operation when in JPEG side
    if(pFsJpeg->gifsFuncBtn!=FS_FUNC_JPEG)//mark the action of reseting buffer
#endif
#ifdef SUPPORT_MIDI //axelchen for midi MP3 sync 2005/9/15 
    if(!bLyricSyn) 
#endif
    {
        abv_start     = get_dsp3_dm_ptr() + AUDIO_BITSTREAM_START*3;
        set_aud_buf_size();
        AudioSetBytePtr(0);
        AudioSetDumpPointer(0);
    }
}

/**************************************************************************
 *  Function Name: setup_eq_display
 *  Purposes:
 *    Turn on or turn off EQ display
 *  Descriptions:
 *
 *  Arguments:
 *    val in : 0 - off, 1 - on
 *  Returns:
 *
 *  See also:
 *
 **************************************************************************/
void setup_eq_display(UINT8 val)
{//terry,2003/9/26 04:42PM
  bEqDisplay = val;
//wanghaoying add 2003-12-11 9:56
//Problem: when change sound page or close sound menu, the effect shut off.
#if 1//!defined(YUXING_SOUND)&&!defined(REMB_3DSOUND)//yanlb add REMB_3DSOUND 2004-07-11 16:00
if (val == 0xf)//Steven 2006/08/15 add to avoid calling EQ func repeatly 
  AUDIF_Set_EQType(bEqDisplay);//2004AUDDRV AudioSetEQType(bEqDisplay);
#endif
}

/**************************************************************************
 *  Function Name: dsp3_config
 *  Purposes:
 *    Set dsp3 memory space, memory based arguments. (through DM)
 *  Descriptions:
 *
 *  Arguments:
 *
 *  Returns:
 *
 *  See also:
 *    Documents such as DSPProtocol.doc in /doc
 **************************************************************************/
//
// FUNCTION
// dsp3_config
//
// DESCRIPTION
// setup dsp3 memory space, memory based arguments.
//
extern  const short DTSrom[];

#ifdef CHANGE_DSP_SPDIF_OFF//nono 2003-10-21 21:06
extern BYTE audioNotContinuous;
#endif

void    dsp3_config(void)
{
  int	i, v;
  //BYTE *q;

  // reset all DSP24 mailbox ports
  //for (i=0;i<16;i++) regs0->dsp24_port[i] = 0; //Jeff 20011029

// reset risc32 audio buffer pointers
  reset_audio_buf();

#ifdef CE2746  //solved the noise issue when standby status,FanGang added 2005-4-28 16:48
WriteI2c(0x6a,0x01,0x00,1);  ;
#endif

#if !defined(NO_DTS_OUTPUT)||defined(FORCE_NO_DTS_OUTPUT)//nono 4-5-5 13:50
  DTSSetRomLocation((UINT32)DTSrom);
#endif

  //q = get_dsp3_pm_uptr();

  // clear configs
  for (i=0;i<128;i++) write24(i,0);

  //ycwen 2005/6/15 : 8202D ver. C and ver. D AUD HW issue. 
  //For 8202D before ver. D, DSP Code adjust a sample.
  #if (defined(HW_AUDIO_ADJUST_ONE_SAMPLE) && defined(INTERNAL_AUDIO_DAC)) //2006-04-12, mimitsai add for IC_8202xx relative
  if (coding_mode_now!=AUDIF_CODING_MODE_WMA)
        write24(88,0);    
  #endif
    
  // write configs
  write24(0,AUDIO_BITSTREAM_START);
  write24(1,abv_size/3);
  //write24(2,0);

  // write configs
  write24(3, setupGetSetting(3) );     //Time of Mic auto on after sound detect on
  write24(4, setupGetSetting(4) );     //Time of Mic auto off after sound detect off
  write24(5, setupGetSetting(5) );     //Mic sound detect gain threshold
  write24(6, setupGetSetting(6) );     //Mic switch
  write24(7, setupGetSetting(7) );     //Aduio gain
#ifdef LINE_IN_ENCODE //huziqin 2006-9-29 set ADC input gain
write24(8, 0); 
#else  
  write24(8, setupGetSetting(8) );     //MIC gain
#endif 
  write24(9, setupGetSetting(9) );     //Key shift
  write24(10,setupGetSetting(10));     //Echo delay
  write24(11,setupGetSetting(11));     //Echo gain
  write24(12,setupGetSetting(12));     //3D surround
  write24(13,setupGetSetting(13));     //subwoof

    // 14
    v = setupGetSetting(14);
#ifdef CHANGE_DSP_SPDIF_OFF
    if( (power_on_mute==0)&&(audioNotContinuous==0) ) {//2003-8-15 20:56 for avoid SPDIF noise when power on.
#else//#ifdef CHANGE_DSP_SPDIF_OFF
    if(power_on_mute==0) {//2003-8-15 20:56 for avoid SPDIF noise when power on.
#endif//#ifdef CHANGE_DSP_SPDIF_OFF

#if !defined(DTS_CD_OUT_RAW_A)&&!defined(NO_DTS_OUTPUT)//NONO 20040117
        if ( (cd_type_loaded==CDDA) && (setup_IsSet2SPDIF_Bitstream()) )
        {
            if (force_set_cd_md==0)
                v = 2;
            else
                v = 1;
        }
#endif
        #ifdef DTS_PCM_MODE_NO_SPDIF_OUT //chenzhao on 2006-9-21 15:12 .
        if (v==1 && is_dts_force_spdif_bitstream()) v=0;
        #else
        if (v==1 && is_dts_force_spdif_bitstream()) v=2;
        #endif
        write24(14,v);   //PCM mode
    }

  write24(15,setupGetSetting(15));     //EQ
  write24(16,setupGetSetting(16));     //SPDIF

  //Jeff 20020521
  write24(17,DACFORMAT);               //audio DAC format
  write24(18,DAC_INVERT);              //dac polarity
  
#ifndef IC_8202L   //add by Steven 2006/5/2// //for 8202L harware(L,R Channel)mapping upside down//
    write24(19,DACOUTLm);
    write24(20,DACOUTRm);
    write24(21,DACOUT0L);
    write24(22,DACOUT0R);
    write24(23,DACOUT1L);
    write24(24,DACOUT1R);
    write24(25,DACOUT2L);
    write24(26,DACOUT2R);
#else
    //update by johnwu 2006/7/28// //for 8202L harware(L,R Channel)mapping upside down, map to DAC0,  not to Lm/Rm pair
    write24(19,DACOUT0R);
    write24(20,DACOUT0L);
#endif
  // Bass Management
  // 0: Out 1, No Bass Management for 5 full-range spks and subwoofer output
  // 1: Out 2, Configuration 1 for 5 satellites spks
  // 2: Out 3, Simplified Bass Management for multi-channel source products
  //           with fixed to L/R
    #ifdef AC3_BASS_MANAGEMENT
	write24(27,setupGetSetting(27));     //Bass Management
    #else
	//write24(27,0);
    #endif

    #if 1//def SPDIF_PLUS_ANALOG
	write24(28,1);
    #else
	//write24(28,0);
    #endif


    if (cd_type_loaded==CDDA) { //Jeff update 20031223
#ifdef DTS_CD_OUT_RAW_A
         if ( (force_set_cd_md==0) && (cd_subtype==CD_DTS))

#else
        if ( (force_set_cd_md==0) &&
             ( (setup_Is_DTSCD_Set2SPDIF_Bitstream()) || (cd_subtype==CD_DTS) ) //jiangxl 2006-7-8 04:17ÏÂÎç
           )
#endif
        {
            UINT32  dtscdbstmidx=0;

            if (smp_rate_now==FS_44K)
                dtscdbstmidx=1;
            else if (smp_rate_now==FS_48K)
                dtscdbstmidx=2;
            else if (smp_rate_now==FS_32K)
                dtscdbstmidx=3;

            write24(29,dtscdbstmidx);
        } //else {
            //write24(29,0);
        //}
    } //else {
        //write24(29,0);
    //}

/*
#ifdef USE_FREQ_MASK
    setup_SetFreqMaskConfig();//terry,2003/12/15 11:07AM
#else
    AUDIF_Set_FrqMsk(FREQ_MASK_DEFAULT);//2004AUDDRV audif_set_frequency_mask(FREQ_MASK_DEFAULT);
#endif
*/
	//20041222 JSLin	// always goest to setup_SetFreqMaskConfig()
	setup_SetFreqMaskConfig();

    //write24(31,0);

    //set_dsp3_pcm_value(32, frequency_multiple);
    write24(32,frequency_multiple);

    write24(33,setupGetSetting(33));
#ifdef SUPPORT_PROLOGIC_II
    write24(35,setupGetSetting(35));
#endif

    // ADC config ( default: 0)
    // 0: Select Line_in L/R capability,but only mix right channel
    // 1: Select Mic_Amp capability (only left channel capability)
    // 2: Select Line_in L/R capability,mix left channel
    // 3: Select Line_in L/R capability, Stereo ADC mic function
    //write24(36,0);
    write24(36,ADC_CONFIG_MODE);//nono 20030730

    //CD pcm content under DTSCD and HDCD (default: 0)
    // bit0: 1: If DTSCD is not allowable for customer,do not mute PCM output.
    //       0: mute
    // bit1: 1: Force CD type to do HDCD filter.
    //       0: CD PCM output do not any modify.
    // bit2: 1: HDCD function disable.
    //       0: HDCD function enable.

    //write24(37,0);

#if defined(PLAY_HDCD_AS_CD)
        write24(37,4);   //heqiang add for Ngailik, output with CD format when HDCD is loaded 4-2-23 17:38
#endif


    //RISC set ADC gain for custumer request (default:2)
    // DSP will range it between 1~5
    #ifdef ENHANCE_MIC_VOL_4   //axel add to enhancing MIC VOL 2003/11/26 11:46am
    write24(38,4);
    #else
    write24(38,2);
    #endif

    write24(39, setupGetSetting(39) ); //Left channel gain , Jeff 20030901
    write24(40, setupGetSetting(40) ); //Right channel gain
    write24(41, setupGetSetting(41) ); //Left surround channel gain
    write24(42, setupGetSetting(42) ); //Right surround channel gain
    write24(43, setupGetSetting(43) ); //Center channel gain
    write24(44, setupGetSetting(44) ); //MIC-2 gain
    write24(46, setupGetSetting(46) ); //Sub-woofer channel gain, Jeff 20031028

    //write24(47, setupGetSetting(46) ); //DTS/DVD-Audio Enable

    // bit 0: DTS 96/24 function (0: disable, 1:enable, default 0)
    // bit 1: decoder enable/disable (1: disable, 0:enable, default 0)
    #ifdef DTS_94_24_CFG
    extern UINT32 get_auhw_info();
    write24(48, DTS_94_24_CFG|(get_auhw_info()<<1));
	#endif

    #ifdef LmRm_CFG
    write24(49, LmRm_CFG ); //Lm/Rm channel mapping to the same with L/R (0: disable, 1:enable, default 0)
    #endif

    #ifdef SPHE8202//terry,2004/4/9 10:39AM
    write24(50,SPHE8202);  
	#ifdef IC_8202D
	//8202/8200/8202D/1000/7300 platform}
	//0: 8200,               		 
	//1: 8202                          		 
	//2:1000                           		 
	//3:8202D without supporting AGC   	 
	//4:7300                            		
	//5:8202D with AGC
	//6:8202L                 	
	write24(50,3);
    #elif defined(IC_8202L)//Steven,2006/4/11 //        	
	write24(50,6);
	#endif
    #endif
    
    #ifdef SPHE1000 //MIKEY 2004.07.15 for SPDIF
    write24(50,1);
    #endif


    
#ifdef SUPPORT_RECEIVER
    write24(52,1); /*for tuner ADC gain,range 1--5*/
#endif
     #ifdef SUPPORT_TESTSPK   // benson     2004/7/2 04:37¤U¤È
    //for decoder AUDIF_CODING_MODE_SPK only
    //Sequence 0-L, 1-C, 2-R, 3-Ls, 4-Rs
    //we follow dolby's definition L C R Rs Ls
    // => 0 1 2 4 3
    write24(53,0); // L
    write24(54,1); // C
    write24(55,2); // R
    write24(56,4); // Rs
    write24(57,3); // Ls
    write24(58,0x2dde00);    // gain for noise generation (VOL=Max)
                                // -30dBFB(rms power)
                                // 0x7fffff ~ 0x000000
    write24(59,375);         // duration of noise gen for each ch
                                // default=375
                                //   1*256/48000=5.3 ms
                                // 375*256/48000= 2 sec
    #endif


    #ifdef SUPPORT_MULTI_CHANNEL_5_BAND_EQ
    write24(89,1);         // 0:2 channel 7 band eq; 1:multi-channel 5 band eq.
    #endif//#ifdef SUPPORT_MULTI_CHANNEL_5_BAND_EQ



   if (!user_mute)
   {
#ifdef VOLUME_RECODE
        {
            int read_volume;
            int i=0;
        #ifdef CNTR_5SPK_VOLUME
	    for (i=0; i<7; i++) {
        #endif

            read_volume=ReadFromI2c(0xa0,ADDR_I2C_VOLUME+i,(BYTE *)&audio_volume,sizeof(audio_volume));
            //printf("read_volume==<%d>:audio_volume=====>%d\n",read_volume,audio_volume);

        #ifdef CNTR_5SPK_VOLUME

                volume_5SPK[i]      = audio_volume;//VOL_VALUE; //set to maximum volume
                if(i==0)//wangfeng 2003-11-03 15:33
                idVolume_5SPK[0]    = Volume_Font_ID;
                else
                idVolume_5SPK[i]    = VOL_FL_ID+i-1;

            //AudioSetVolume(audio_volume);

            } //for
            audio_volume  = volume_5SPK[0] ;
            volume_Switch = 0;     //set to main volume
        #endif
        }

#endif //VOLUME_RECODE

		#ifdef  CNTR_5SPK_VOLUME
		{
		int i,read_volume;
		for (i=0; i<7; i++) 
        {
            read_volume=ReadFromI2c(0xa0,ADDR_I2C_VOLUME+i,(BYTE *)&audio_volume,sizeof(audio_volume));
	        if(i==0)
	        {
	            #ifdef CNTR_5SPK_TYPE_2  // linrc add 2004-10-12 9:48
	            if(IS_AUDIF_CODING_MODE_LPCM || IS_AUDIF_CODING_MODE_DTS
	             || IS_AUDIF_CODING_MODE_PCM || IS_AUDIF_CODING_MODE_WMA
	             || IS_AUDIF_CODING_MODE_DTSCD)
	            {
    	    	    AUDIF_Set_Volume(volume_5SPK[0]);//2004AUDDRV AudioSetVolume(volume_5SPK[0]);
	            }
	            else
		    		AUDIF_Set_Volume(15);//2004AUDDRV AudioSetVolume(15);
	            #else
	            AUDIF_Set_Volume(volume_5SPK[0]);//2004AUDDRV AudioSetVolume(volume_5SPK[0]);
	            #endif
	        }
	        else
    	        DSP_AudioIOControl(FLSPKGAIN+i-1,volume_5SPK[i],0);// 2004AUDDRV AudioIOControl(FLSPKGAIN+i-1,volume_5SPK[i],0);
            }
        }
        #else//#ifdef  CNTR_5SPK_VOLUME
		AUDIF_Set_Volume(audio_volume);//2004AUDDRV AudioSetVolume(audio_volume);
        #endif//#ifdef  CNTR_5SPK_VOLUME
   }
   
   //(1) Cutoff at 100 Hz

    // 32kHz HPF
    write24(64,0x7E3C31);	//b0,b2
    write24(65,0x83879D);	//1+b1 
    write24(66,0x838DD7);	//1+a1 
    write24(67,0x7C7E9D);	//a2   
    // 32kHz LPF                        
    write24(68,0x00031D);	//b0,b2
    write24(69,0x00063B);	//b1   
    write24(70,0x838DD7);	//1+a1 
    write24(71,0x7C7E9D);	//a2   
    
    // 44kHz HPF
    write24(72,0x7EB789);	//b0,b2
    write24(73,0x8290EE);	//1+b1 
    write24(74,0x829439);	//1+a1 
    write24(75,0x7D725C);	//a2   
    // 44kHz LPF                        
    write24(76,0x0001A5);	//b0,b2
    write24(77,0x00034B);	//b1   
    write24(78,0x829439);	//1+a1 
    write24(79,0x7D725C);	//a2   
    
    // 48kHz HPF
    write24(80,0x7ED219);	//b0,b2
    write24(81,0x825BCD);	//1+b1
    write24(82,0x825E95);	//1+a1
    write24(83,0x7DA6FB);	//a2
    // 48kHz LPF
    write24(84,0x000164);	//b0,b2
    write24(85,0x0002c8);	//b1
    write24(86,0x825E95);	//1+a1
    write24(87,0x7DA6FB);	//a2
   //ycwen 2005/6/15 : 8202D ver. C and ver. D AUDIO HW issue. 
   //For 8202D before ver. D, DSP Code adjust a sample.
   #if (defined(HW_AUDIO_ADJUST_ONE_SAMPLE)&& defined(INTERNAL_AUDIO_DAC)) //2006-04-12, mimitsai add for IC_8202xx relative
   if (coding_mode_now!=AUDIF_CODING_MODE_WMA)
   {        
        write24(88,1);    
   }
   #endif
    		//Lm/Rm and SPDIF/PCM post-process flag              
	   	//0: Lm/Rm and SPDIF/PCM will do post-process      
	   	//1: Lm/Rm and SPDIF/PCM will skip post-process    
   	write24(93,0);
     	//	{bit 0 : 0->DAC 0 off ,1->DAC 0 on}
	//	{bit 1 : 0->DAC 1 off ,1->DAC 1 on}
	//	{0:DAC 0 off, DAC 1 off}
	//	{1:DAC 0 on , DAC 1 off}
	//	{2:DAC 0 off, DAC 1 on}
	//	{3:DAC 0 on , DAC 1 on}
   write24(94,1);
	#ifdef INCLUDE_MP3_ENCODER
		//initially set sampling freq. in DM(62)=yy, bitrate in DM(63)=zz, encode speed in DM(95)=xx
		/*
		    yy = 0: 44100 Hz (default)
		    yy = 1: 48000 Hz
		    yy = 2: 32000 Hz    
		    zz = 1~14 ¨Ì§Ç¬° 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320 kbps
		    (default 128 kbps)
		    xx = 0: realtime encode with audio output
		    xx = 1: fast encode without audio output
		*/    
		if(IS_AUDIF_CODING_MODE_CD_MP3_ENCODER)
		{
			write24(62,0);	        
			write24(63,9);
			write24(95,0);
		}
	#endif

    write24(99,AUDIF_Get_MICSupport());// add by Steven 2006/4/10 avoid SPDIF silent when MIC ON/OFF switch continuously//
    

	
}


//
// FUNCTION
// dsp3_copy(dst,src,len)
//
//static inline void
//dsp3_copy(void *dst, void *src, unsigned len)
//{
//	UINT32 *p, *q;
//
//	p = (UINT32 *) src;
//	q = (UINT32 *) dst;
//	len = (len+3) /4;
//	while (len-->0) {*q++ = *p++;}
//}

/**************************************************************************
 *  Function Name: dsp3_decompress
 *  Purposes:
 *    Download dsp code and call gzip to decompress binary
 *  Descriptions:
 *
 *  Arguments:
 *    rom in : address of dsp codec
 *    dst in : address to put decompress binary
 *  Returns:
 *    if ret >= 0 means size after gunzip.
 *       ret <  0 means error during gunzip.
 *  See also:
 *
 **************************************************************************/
#include "bitop.h"

//
// FUNCTION
// setupim()
//
// DESCRIPTION
// download gzip compressed binary.
// RETURN
// >=0 size after gunzip.
// <0  error during gunzip.
//
int
dsp3_decompress(const BYTE *rom, BYTE *dst)
{
    int v;
    t_getbit	gb;

    LOAD_LINUX_TRAP();

    getbits_init(&gb, rom);
    v = gunzip(&gb, dst);
#ifdef	MONE_DSP3_LOAD
    dsp3_printf("[dspl] %d\n", v);
#endif
    MIPS_flush_LBC_cache();

    return v;
}

//Steven 2006/10/04 replace cache to uncache way to handshake with DSP module//
#define	dsp3_setupim(rom,len)		dsp3_decompress(rom,get_dsp3_im_uptr()+0)
#define	dsp3_setupdm(rom,len,off)	dsp3_decompress(rom,get_dsp3_dm_uptr()+off)
#define	dsp3_setuppm(rom,len,off)	dsp3_decompress(rom,get_dsp3_pm_uptr()+off)

#if 0 //terry,2004/2/6 04:26PM
//
// dsp3_hw_reset
//
void dsp3_hw_reset(void)
{
  regs0->reset		= 0x20;		// reset audio sub-system
  regs0->reset		= 0x0;
  regs0->dsp24_control	= RF_DSP24_RESET;
}
#endif


#ifdef IC_8202L
#define	DSP_RESET()	do{						\
				regs0->aud_reset=1;			\
				delay_srv_10ms(3);			\
				regs0->dsp24_control=0x3;	\
			}while(0)
#else
#define	DSP_RESET()	(regs0->dsp24_control=RF_DSP24_RESET)
#endif

#define	DSP_STALL()	(regs0->dsp24_control=RF_DSP24_STALL)
#define	DSP_GO()	(regs0->dsp24_control=0)

//
// FUNCTION
// dsp3_stop
// DESCRIPTION
// stop DSP3 operation
//
void
dsp3_stop(void)
{
    DSP_RESET();
}

#ifdef SPEAKER_CONFIG//chenzhao20060116
void set_speaker_config_default_value(void)
{
    #ifdef FIX_2_1_SPEAKER_CONFIG
    speaker_front=SPEAKER_SMALL;
    speaker_center=SPEAKER_OFF;
    speaker_surround=SPEAKER_OFF;
    speaker_subwoofer=STATUS_ON;
    #elif defined(FIX_5_1_SPEAKER_CONFIG)
    speaker_front=SPEAKER_SMALL;
    speaker_center=SPEAKER_SMALL;
    speaker_surround=SPEAKER_SMALL;
    speaker_subwoofer=STATUS_ON;
    #else //standard setting
    speaker_front=SPEAKER_LARGE;
    speaker_center=SPEAKER_LARGE;
    speaker_surround=SPEAKER_LARGE; 
    speaker_subwoofer=STATUS_ON;
    #endif
}
#endif
#if 0
/**************************************************************************
 *  Function Name: dsp3_download
 *  Purposes:
 *    Download DSP Codec
 *  Descriptions:
 *    Stop DSP, set DSP im, and let dsp go
 *  Arguments:
 *    rom in : address of dsp codec table
 *    len : length of dsp codec
 *  Returns:
 *
 *  See also:
 *
 **************************************************************************/
//
// FUNCTION
// dsp3_download
//
// DESCRIPTION
// generic dsp3 program download
//
void
dsp3_download(const BYTE *rom, int len)
{

    //if(len){}   //wanghaoying 2003-8-12 20:55

	// 2003/06/06, Bug fixed for AC3->VCD playback switch
        // disable audio output before DSP reset, to cancel any noises of decoder change
        // audio will be enabled automatically by DSP.

	regs0->aud_enable = 0;  // disable PCM H/W (PCM, SPDIF, ADC)

	// reset dsp24
	DSP_RESET(); // always disable audio before dsp_reset

	LOAD_LINUX_TRAP();

	// config pdm and audio bitstream buffer
	dsp3_config();

	// Move MP3 PM, DM table
	if(rom == DSP3Info_MP3.pDSPcode)
	{
		#ifdef	MP3_JPEG_COWORK//enlarge the audio buffer size
		//refer to line 67
		dsp3_setuppm(DSPMP3DMTab,DSPMP3DMlen,0x1420*3);
		dsp3_setuppm(DSPMP3PMTab,DSPMP3PMlen,0x24c0*3);
		#else
		//refer to line 70
		dsp3_setupdm(DSPMP3PMTab,DSPMP3PMlen,0x0c00*3);
		dsp3_setuppm(DSPMP3DMTab,DSPMP3DMlen,0x1420*3);
		#endif
#if 0
		int  iLen;
		UINT32 *p,*q;

		//Move MP3 PM table
		p = (UINT32 *) DSPMP3PMTab;
		q = (UINT32 *) (SDRAM_BASE + MEM_AUDYA * 1024 + 0x0c00*3);
		iLen = (DSPMP3PMlen+3) & ~0x03;
		//printf("Move MP3 PM table iLen=%d\n", iLen);
		iLen = iLen/4;
		while (iLen-->0)
		{
			*q++ = *p++;
		}

		//Move MP3 DM table
		p = (UINT32 *) DSPMP3DMTab;
		q = (UINT32 *) (SDRAM_BASE + MEM_PCMYA * 1024 + 0x1420*3);
		iLen = (DSPMP3DMlen+3) & ~0x03;
		//printf("Move MP3 DM table iLen=%d\n", iLen);
		iLen = iLen/4;
		while (iLen-->0)
		{
			*q++ = *p++;
		}
#endif
	}

	// copy im
	if (dsp3_setupim(rom,len) < 0)
	{
#ifdef	MONE_DSP3_ERROR
		dsp3_puts("*ERROR* gunzip dsp code error\n");
#endif
	}
	else
	{
#ifdef SUPPORT_NESGAME
		//jackie for nes
		int i;
		if(rom == DSP3Info_NES.pDSPcode)
		{
			for (i=0;i<15;i++)
				regs0->dsp24_port[i]=0;

			//DAC initialize format bit8~15, set playback rate(bit-0 ~ bit-1)
			regs0->dsp24_port[4]|=(DACFORMAT<<8)|SOUND_PLAYBACK_ID;
		}
#endif	// end of SUPPORT_NESGAME
#ifdef NO_AUDIO_DSP
		return;
#endif


#ifdef SETUP_DONT_PAUSE
#ifdef SUPPORT_NESGAME
                if(coding_mode_now!=AUDIF_CODING_MODE_NES)
#endif
                regs0->dsp24_port[5]=-1;
#endif

		DSP_GO();

/*	marked by Robert 030806
		if(power_on_mute==0)
		{//terry,2003-8-5 3:15
			GPIO_DEMUTE(); // Robert030806
		}//power_on_mute
*/
	}
}
#endif

