//#define USE_LPCM_REPLACE_PCM //terry,2004/3/4 08:40PM

#include "set.h"//terry,2004/1/12 05:01PM
#include "types.h"
#include "memmap.h"
#include "memmap0.h"//terry,2004/1/12 05:01PM
#include "regmap.h"
#include "config.h"
#include "global.h"
#include "func.h"

#include "dsp3_if.h"
#include "dsp3rom.h"

#include "auddrv.h" //2004AUDDRV oliver 20041004 for using audio driver purpose
//#include "audif.h"
#include "dsp3_if.h"
#include "mpgkern.h"

#include "setup.h"
#include "UartTxd.h"
#include "osd.h"

#include "gpio.h"
#include "kinf.h"

#ifdef SUPPORT_MIDI_MENU_SEL
#include "fsMidiUI.h"
#endif
#undef SPDIF_IN_POP_MUTE
//#define SPDIF_IN_INVALID_SOURCE_MUTE//chenzhao 2006-3-23 9:37 .

#ifndef DVDRELEASE
//#define AUDIF_DBG   1
#endif

#define audif_puts(s)       ((void)0)
#define audif_printf(s...)  ((void)0)

#ifdef  AUDIF_DBG
#include "sio.h"
#include "emuio.h"
#define MONE_DOWNLOAD_CODEC
#undef  audif_puts
#undef  audif_printf
#define audif_puts(s)   io_write(s)
#define audif_printf(s...)  \
    do { \
	psprintf(linebuf, ##s); io_write(linebuf); \
    } while (0)
#endif

#if 0 //2004AUDDRV move to auddrv.c
#ifdef SUPPORT_MP4
int mp4_aud_channel_flg=0;
#endif
#endif
#ifdef NEW_UART_COMMAND  //lijinhai solve for fuss ac3
BYTE first_init_disk_audio=0;
#endif

//2004AUDDRV #ifdef SUPPORT_RECEIVER
//2004AUDDRV void init_new_dsp_code(UINT32 coding_mode);    // benson modify 2004/3/1 03:31下午
//2004AUDDRV #else
//2004AUDDRV void init_new_dsp_code(UINT16 coding_mode);
//2004AUDDRV #endif

//2004AUDDRV void wait_dsp_busy(int dspChanged);//wanghaoying 2003-8-12 20:58

//2004AUDDRV #ifdef SUPPORT_MIDI
//2004AUDDRV extern UINT16 Is_MIDI_STATE(void);
//2004AUDDRV #endif


//2004AUDDRV extern int hardware_no_dts(void);
//2004AUDDRV extern int hardware_no_ac3(void);
//2004AUDDRV extern int hardware_no_mp3(void);
//2004AUDDRV extern int hardware_no_wma(void);
//2004AUDDRV extern int hardware_no_dvdaud(void);
//2004AUDDRV extern void    dsp3_config(void);
//2004AUDDRV extern UINT8 power_on_mute;//terry 20030805
//2004AUDDRV extern UINT8 setup_audio_mode;
//2004AUDDRV extern UINT8 band_onoff;
//2004AUDDRV extern BYTE wait_dsp_port0_5(int port0,int port5,int val,UINT32 risc_waiting_dsp_tm);



#ifdef SUPPORT_SPDIF_IN    //benson  add 2004/3/29  09:12上午
#define RATIONO 2
#define RATIOBUFLEN   40
#define FS_44K_IN_RATIOINFORM 0
#define FS_48K_IN_RATIOINFORM 1
#define SPDIFIN_PCM_MODE      0
#define SPDIFIN_AC3_MODE      1
#define SPDIFIN_DTS_MODE      2
#define SPDIFIN_DTSCD_MODE    3
#define SPDIFIN_NO_SIGNAL_MODE  7
  #if defined(F108) //wuzhj 2005/06/22
#define FS_44K_CENTRAL_PERIOD 18
#define FS_48K_CENTRAL_PERIOD 16
  #elif  defined(F114_75)
#define FS_44K_CENTRAL_PERIOD 20
#define FS_48K_CENTRAL_PERIOD 17
  #elif defined(F121_5)
#define FS_32K_CENTRAL_PERIOD 1     // benosn update 2005/4/17 06:39下午
#define FS_44K_CENTRAL_PERIOD 2
#define FS_48K_CENTRAL_PERIOD 3
#define FS_96K_CENTRAL_PERIOD 4 
  #endif//#if defined(F108) //wuzhj 2005/06/22
#define FS_44K_LEFT_MARGIN_PERIOD       FS_44K_CENTRAL_PERIOD-2
#define FS_44K_RIGHT_MARGIN_PERIOD      FS_44K_CENTRAL_PERIOD+2
#define FS_48K_LEFT_MARGIN_PERIOD       FS_48K_CENTRAL_PERIOD-2
#define FS_48K_RIGHT_MARGIN_PERIOD      FS_48K_CENTRAL_PERIOD+2

int ratioBufferFull=0;
int currentRatioIndex=0;
int ratioBuffer[RATIOBUFLEN];

//int amountPeriod[10];//0:44K 1:48K  2~8:reserved  9:the other period
// benson 2004/3/29 09:41
int spdifin_ac3_bps_table[19]={32,40,48,56,64,80,96,112,128,160,
								192,224,256,320,384,448,512,576,640};
int spdifin_dts_bps_table[29]={32,56,64,96,112,128,192,224,256,320,384,
								448,512,576,640,768,960,1024,1152,1280,1344,
								1408,1412,1472,1536,1920,2048,3072,3840};                               
int ratioInform[RATIONO][4]={{FS_44K_CENTRAL_PERIOD,FS_44K_LEFT_MARGIN_PERIOD,FS_44K_RIGHT_MARGIN_PERIOD,0},//44k {center,left boundary ,right boundary, distance}
								{FS_48K_CENTRAL_PERIOD,FS_48K_LEFT_MARGIN_PERIOD,FS_48K_RIGHT_MARGIN_PERIOD,0}};//48K
int previousRatio=FS_44K_CENTRAL_PERIOD;//default:44k                             

//int spdifin_type =SPDIFIN_NO_SIGNAL_MODE; //moved to global.h,chenzhao20060120

extern void ddx_set_96k_input();
extern void ddx_set_48k_input();

#endif // SUPPORT_SPDIF_IN 




#ifdef SUPPORT_COAXIAL_IN  //xyy 2004-4-29  for XQ
extern BYTE bCoaxialIn;
#endif

#if 0 //2004AUDDRV : move to auddrv.c
//
// FUNCTION
// init_audio
//
// DESCRIPTION
// initialize all audio hw/sw/decoder related parameters/variables/configurations.

void init_audio(void)
{
#ifdef AUDIF_DBG
    audif_puts("audio setup\n");
#endif
	
    // audio gpio mute if needed
	
    audhw_clk_init();
    
    coding_mode_now     = AUDIF_CODING_MODE_DEFAULT;        // reset (force coding-mode setup)
    smp_rate_now        = 0xff;     // reset (force sample-rate setup)
    smp_rate_down       = 0xff;
    frequency_mask      = 0xffff;
    frequency_multiple  = 0x1;
	
    audif_set_sample_rate(FS_DEFAULT);  // force set default frequency
	
    //init_audio_dsp_coding_mode();
	
    audif_set_channel(0x00);
	
#ifdef NEW_UART_COMMAND  //lijinhai solve for fuss ac3
    first_init_disk_audio=1;
#endif
}


void init_audio_dsp_coding_mode(void)
{
    if ( setup_IsSet2SPDIF_Bitstream() ) 
    {
        coding_mode_now = AUDIF_CODING_MODE_NONE;
        isSPDIFBitstream = 1;
        //audif_set_SPDIF_BITSTREAM();
    } else {
        //audif_set_coding_mode(AUDIF_CODING_MODE_LPCM);
        audif_printf("init audio dsp coding\n");
        AUDIF_Set_CodingMode(AUDIF_CODING_MODE_PCM);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_PCM);
        isSPDIFBitstream = 0;
    }
}


//
// init_cdda
//
void    init_cdda(void)
{
    audif_printf("init cdda\n");
    //cd_subtype = CD_DA; //terry,2003/12/17 11:12AM
    audif_set_sample_rate(FS_44K); //Jeff 20020805
    audif_set_coding_mode(AUDIF_CODING_MODE_PCM);
	
    //we use PCM as CDDA ans DTS-CD SPDIF/BITSTREAM DSP decoder
    //so, we use AudioSetSPDIF command to distinguish them
    //parameter 1:CDDA, 2:DTS-CD
    if ( setup_IsSet2SPDIF_Bitstream() ) { //Jeff 20020719
        //AudioSetSPDIF(1);
        AudioSetSPDIF(2); //ycwen : 2004/08/24, we don't need to use this command to distinguish CDDA/DTSCD anymore.
    }
}


//
// init_dtscd
//
void init_dtscd(void)
{
    audif_set_sample_rate(FS_44K); //Jeff 20020805
    audif_set_coding_mode(AUDIF_CODING_MODE_DTSCD);
	
    //we use PCM as CDDA ans DTS-CD SPDIF/BITSTREAM DSP decoder
    //so, we use AudioSetSPDIF command to distinguish them
    //parameter 1:CDDA, 2:DTS-CD
    if ( setup_IsSet2SPDIF_Bitstream() ) { //Jeff 20020719
        AudioSetSPDIF(2); 
    }
}

#ifdef SUPPORT_AC3_CD_DISC  //terry,2004/2/17 06:35PM
//Jeff 20040102
void init_ac3cd(void)
{
    audif_set_sample_rate(FS_44K);
    audif_set_coding_mode(AUDIF_CODING_MODE_AC3);
}
#endif

#ifdef SUPPORT_MIDI
//
// init_midi
//
void    init_midi(void)     //Jeff 20030318
{
    UINT32 i;
	
#ifdef AUDIF_DBG
    audif_puts("midi audio setup\n");
#endif
	
    audif_set_sample_rate(FS_44K);
    audif_set_coding_mode(AUDIF_CODING_MODE_MIDI);
	
    for (i=0; i<0xfffffff0; i++) {
        if (regs0->dsp24_port[0] != 0xffffffff)   break;
    }
}
#endif


#ifdef SUPPORT_WMA
//
// InitWma
//
void InitWma(void)
{
#ifdef AUDIF_DBG
    audif_puts("wma audio setup\n");
#endif
    coding_mode_now = 0;    //ycwen 2004/09/29 : To prevent DSP from sync error (4444) , we force codec download everytime.    
    audif_set_coding_mode(AUDIF_CODING_MODE_WMA);
#ifdef SDRAM_16Mb_Mode    //terry,2004/4/13 05:28PM
    asf_init_wma();
#endif    
}
#endif


#ifdef SUPPORT_AAC
//
// InitAac
//
void InitAac(void)
{
#ifdef AUDIF_DBG
    audif_puts("aac audio setup\n");
#endif

    audif_set_sample_rate(FS_44K);
    audif_set_coding_mode(AUDIF_CODING_MODE_AAC);
}
#endif


//
// init_mp3
//
void    init_mp3(void)      //Jeff 20010806
{
#ifdef AUDIF_DBG
    audif_puts("mp3 audio setup\n");
#endif
	
    audif_set_sample_rate(FS_44K);
#ifdef SDRAM_16Mb_Mode

    #ifdef BBK_AMP_NOISE_PROBLEM_GBM
    if(cd_type_loaded==CDROM)//gerry add,2004-6-10 13:33//wangwei modify
    {
        coding_mode_now = 0;//nono add 2004-5-15 15:48      //
        delay_srv_10ms(130);
    }
    #else
    if(cd_type_loaded!=CDSVCD)//gerry add,2004-6-10 13:33
        coding_mode_now = 0;//nono add 2004-5-15 15:48
#endif

#endif  //SDRAM_16Mb_Mode
    audif_set_coding_mode(AUDIF_CODING_MODE_MP3);
}


//
// init_jpg
//
#ifdef JPGDSP
void init_jpg(void)
{
#ifdef AUDIF_DBG
    audif_puts("jpeg setup\n");
#endif
    audif_set_coding_mode(AUDIF_CODING_MODE_JPG);
}
#endif
#endif

UINT16  audif_get_frequency_mask()
{
    return frequency_mask;
}

#ifdef SUPPORT_SPDIF_IN /*2005-6-6 20:05 huziqin*/
#define SPDIF_IN_DBG

void show_spdif_in_msg(int spdifin_mode,int sample_rate,int channel,int bitrate)
{
    
	switch(spdifin_mode)
	{
	case SPDIFIN_PCM_MODE:              
	    psprintf(RegionValStr[REGION1],"PCM %d K",sample_rate);    // benson update 2004.08.17
        break;
	case SPDIFIN_AC3_MODE:
		psprintf(RegionValStr[REGION1],"AC3 %d K",spdifin_ac3_bps_table[bitrate>>1]);
        
		break;    
	case SPDIFIN_DTS_MODE:     
	case SPDIFIN_DTSCD_MODE:     
		psprintf(RegionValStr[REGION1],"DTS %d K",spdifin_dts_bps_table[bitrate]);
        
		break;
	default:
#ifdef SPDIF_IN_DBG  	
         //printf("sp***ERROR***period =%d,mode=%d,oldmode=%d,bitrate=%d,channel=%d\n",period,regs0->dsp24_port[12],spdifin_type,regs0->dsp24_port[13],regs0->dsp24_port[14]);
        
#endif		
        ClearOsdMsg(2);
        psprintf(RegionValStr[REGION1],"NO SIGNAL");
        break;
    }   

    PrintOsdMsg(STR_OS_SPACE, REGION1, 0, 1);           
        
    if (spdifin_type < 4)
    {   
#ifdef SUPPORT_COAXIAL_IN //xyy add 2004-4-29 for XQ temporary using
		if (channel==0)
		{
			if(bCoaxialIn)
				psprintf(RegionValStr[REGION2]," CHANNEL :  2  CH   OPTICAL IN");
            else
				psprintf(RegionValStr[REGION2]," CHANNEL :  2  CH   COAXIAL IN");            
		}
		else
		{
			if(bCoaxialIn)
				psprintf(RegionValStr[REGION2]," CHANNEL : 5.1 CH   OPTICAL IN");  
			else
				psprintf(RegionValStr[REGION2]," CHANNEL : 5.1 CH   COAXIAL IN");           	
		}
#else
        if (channel==0)
        {
		    psprintf(RegionValStr[REGION2]," 2  CH  ");
        }
        else    
        {
		    psprintf(RegionValStr[REGION2],"5.1 CH  ");  
        }
#endif
        
        PrintOsdMsg(0, REGION2, 0, 1);
    }
	
}

void spdif_in_init(void)   
{
	int set_fs_sample_rate;   
	int period=0 , sample_rate=0 ;
	int hw_period =0;
	int ratioPointer=0; 
	int totalPeriod,accumulateNo=1;//benson   2004/03/29
	int bitrate;
	int channel;
	UINT32 spdifin_info;
	int spdifin_mode;
	int spdif_cnt = 0;
    
	hw_period = regs0->aud_spdif_period;
	spdif_cnt = regs0->dsp24_port[11];
	spdifin_info = regs0->dsp24_port[12];       
	bitrate = (0xff00 & spdifin_info)>>8;     // benson update 2004.08.17
	spdifin_mode =  0x07 & spdifin_info;
	channel = (0x38 & spdifin_info)>>3;     
	
    if((spdifin_mode == SPDIFIN_AC3_MODE)||(spdifin_mode == SPDIFIN_DTS_MODE)) /*AC3 or DTS*/
    {
        period = FS_48K_CENTRAL_PERIOD;
    } 
    #if 0 //chenzhao on 2006-3-2 20:1 .
    else if(spdifin_mode == SPDIFIN_DTSCD_MODE)
    {
        period = FS_44K_CENTRAL_PERIOD;
    }
    #endif
    else //detect sampling rate in PCM and NO Signal mode 
    {
	if(spdifin_mode!=spdifin_type)
	{  //reset 
		ratioBufferFull=0;
		currentRatioIndex=0;
	}
	else
	{ 
            if(spdifin_mode == SPDIFIN_PCM_MODE) 
	    {
                //vfd_set_spdif_in(spdifin_mode);
	    } 
            else if(spdifin_mode == SPDIFIN_NO_SIGNAL_MODE)
	    {
                printf("unknown spdif in mode\n");
	    }
#ifdef SPDIF_IN_DBG	    
            //printf("sampling rate= %d\n",spdif_cnt*160);		
#endif

			#ifndef HW_SUPPORT_SPDIF_IN
			ratioBuffer[currentRatioIndex]=spdif_cnt;
			#else
            if (((hw_period>64)&&(hw_period<84))||((hw_period>143)&&(hw_period<161))||((hw_period>161)&&(hw_period<177))||((hw_period>220)&&(hw_period<240)))
            ratioBuffer[currentRatioIndex]=hw_period;    			
			#endif

            if(ratioBufferFull==0&&currentRatioIndex==(RATIOBUFLEN-1))//the buffer is full
                ratioBufferFull=1;
			
            if(ratioBufferFull==0)
                accumulateNo=currentRatioIndex+1;  
            else
                accumulateNo=RATIOBUFLEN;  
            totalPeriod=0;
            for(ratioPointer=0;ratioPointer<accumulateNo;ratioPointer++)   
                totalPeriod=totalPeriod+ratioBuffer[ratioPointer];
                
            // 287.5 ==> 46K ...      // benson 2005/4/17 07:01下午
            // 237   ==> 38K ...
            // 375   ==> 60K ...
            #ifndef HW_SUPPORT_SPDIF_IN
            if(totalPeriod<=(237*accumulateNo))
	            period=FS_32K_CENTRAL_PERIOD;
            if((totalPeriod<=(287*accumulateNo))&&(totalPeriod>=(237*accumulateNo)))
	    	    period=FS_44K_CENTRAL_PERIOD;
	        if((totalPeriod<=(375*accumulateNo))&&(totalPeriod>=(287*accumulateNo)))
	    	    period=FS_48K_CENTRAL_PERIOD;
	        if(totalPeriod>=(375*accumulateNo))
	    	    period=FS_96K_CENTRAL_PERIOD;
            #else
            printf("hd period=%d," , hw_period);
	    	if (((totalPeriod>(220*accumulateNo))&&(totalPeriod<=(240*accumulateNo))))
	    	    period=FS_32K_CENTRAL_PERIOD;
	    	if (((totalPeriod>(161*accumulateNo))&&(totalPeriod<=(177*accumulateNo))))
	    	    period=FS_44K_CENTRAL_PERIOD;
	    	if (((totalPeriod>(143*accumulateNo))&&(totalPeriod<=(161*accumulateNo))))
	    	    period=FS_48K_CENTRAL_PERIOD;
	  	  	if (((totalPeriod>(64*accumulateNo))&&(totalPeriod<=(84*accumulateNo))))
	    	    period=FS_96K_CENTRAL_PERIOD;
	            
	       	printf("period=%d," , period);    	    
  	        printf(" totalperiod  = %d \n" , totalPeriod);
            #endif
            
			currentRatioIndex++;
			if(currentRatioIndex==RATIOBUFLEN)//circular buffer
			{
				currentRatioIndex=0;     
			}
        }	//spdifin_mode!=*spdifin_type       
	    }	


	
	switch (period)
	{
	case FS_32K_CENTRAL_PERIOD:
        if((smp_rate_now!=FS_32K)||(spdifin_mode!=spdifin_type))
        {
#ifdef SPDIF_IN_DBG        
            printf("FS 32K type %d\n",spdifin_mode);
            if(period!=previousRatio)
            {
                printf("period!=previousRatio\n");
            }

            if(spdifin_mode!=spdifin_type)
            {
                printf("spdifin_mode!=spdifin_type\n");
            }
#endif            
            AUDIF_Set_SampleRate(FS_32K);
            previousRatio=period;
            #ifdef SUPPORT_APOGEE_AMP
			ddx_set_48k_input();
            #endif//#ifdef SUPPORT_APOGEE_AMP
        } 
        #if defined(SPDIF_IN_INVALID_SOURCE_MUTE)//chenzhao 2006-3-23 9:38 .
        if((period!=previousRatio) && !user_mute) AUDIF_Demute();
        #endif            
        set_fs_sample_rate=FS_32K;
        sample_rate=32;  
        break;	
	case FS_44K_CENTRAL_PERIOD:
        if((smp_rate_now!=FS_44K)||(spdifin_mode!=spdifin_type))
        {
#ifdef SPDIF_IN_DBG          
            printf("FS 44K  type %d\n",spdifin_mode);
            if(period!=previousRatio)
            {
                printf("period!=previousRatio\n");
            }

            if(spdifin_mode!=spdifin_type)
            {
                printf("spdifin_mode!=spdifin_type\n");
            }
#endif            
            AUDIF_Set_SampleRate(FS_44K);
            previousRatio=period;
            #ifdef SUPPORT_APOGEE_AMP
            ddx_set_48k_input();
            #endif//#ifdef SUPPORT_APOGEE_AMP
        } 
        #if defined(SPDIF_IN_INVALID_SOURCE_MUTE)//chenzhao 2006-3-23 9:38 .
        if((period!=previousRatio) && !user_mute) AUDIF_Demute();
        #endif            
        set_fs_sample_rate=FS_44K;
        sample_rate=44;  
        break;
    case FS_48K_CENTRAL_PERIOD:                      
        if((smp_rate_now!=FS_48K)||(spdifin_mode!=spdifin_type))
        {
#ifdef SPDIF_IN_DBG          
            printf("FS 48K type %d\n",spdifin_mode);
            if(period!=previousRatio)
            {
                printf("period!=previousRatio\n");
            }

            if(spdifin_mode!=spdifin_type)
            {
                printf("spdifin_mode!=spdifin_type\n");
            }
#endif            
            AUDIF_Set_SampleRate(FS_48K);
            previousRatio=period;
            #ifdef SUPPORT_APOGEE_AMP
            ddx_set_48k_input();
            #endif//#ifdef SUPPORT_APOGEE_AMP
        }    
        #if defined(SPDIF_IN_INVALID_SOURCE_MUTE)//chenzhao 2006-3-23 9:38 .
        if((period!=previousRatio) && !user_mute) AUDIF_Demute();
        #endif            
        set_fs_sample_rate=FS_48K;
        sample_rate=48;
        break;
    case FS_96K_CENTRAL_PERIOD:
        if((smp_rate_now!=FS_96K)||(spdifin_mode!=spdifin_type))
        {
#ifdef SPDIF_IN_DBG          
            printf("FS 96K type %d\n",spdifin_mode);
            if(period!=previousRatio)
            {
                printf("period!=previousRatio\n");
            }

            if(spdifin_mode!=spdifin_type)
            {
                printf("spdifin_mode!=spdifin_type\n");
            }

            printf("frequency_mask %x\n",frequency_mask);
#endif            
            //frequency_mask = 0x67;
            AUDIF_Set_FrqMsk(1);
            AUDIF_Set_SampleRate(FS_96K);
            previousRatio=period;	
            #ifdef SUPPORT_APOGEE_AMP
            ddx_set_96k_input();
            #endif//#ifdef SUPPORT_APOGEE_AMP
        } 
        #if defined(SPDIF_IN_INVALID_SOURCE_MUTE)//chenzhao 2006-3-23 9:38 .
        if((period!=previousRatio) && !user_mute) AUDIF_Demute();
        #endif            
        set_fs_sample_rate=FS_96K;
        sample_rate=96;  
        break;   
        
        
    default:
#ifdef SPDIF_IN_DBG      
        printf("default type\n");
        if(period!=previousRatio)
            {
                printf("period!=previousRatio\n");
            }

            if(spdifin_mode!=spdifin_type)
            {
                printf("spdifin_mode!=spdifin_type\n");
            }
#endif            
        #if defined(SPDIF_IN_INVALID_SOURCE_MUTE)//chenzhao 2006-3-23 9:38 .
        if(period!=previousRatio)
            AUDIF_Set_Volume(0);
        #endif
        sample_rate=0;//chenzhao
        previousRatio=period;
    }

switch(spdifin_mode)
	{
	case SPDIFIN_PCM_MODE:              
	    if(spdifin_mode!=spdifin_type)
        {   
            printf("SPDIFIN_PCM_MODE\n");
            AUDIF_Set_CodingMode(AUDIF_CODING_MODE_SPDIFINCD);
            #if 0//defined(SPDIF_IN_INVALID_SOURCE_MUTE)//chenzhao20060217
            if(!user_mute) AUDIF_Demute();
            #endif
            spdifin_type=spdifin_mode;
        }
		break;
	case SPDIFIN_AC3_MODE:
		if ((bitrate>>1) > 18) bitrate=0;
        
		if(spdifin_mode!=spdifin_type)
        {          
            printf("SPDIFIN_AC3_MODE\n");
            AUDIF_Set_CodingMode(AUDIF_CODING_MODE_SPDIFINAC3);
            #if defined(SPDIF_IN_POP_MUTE)//chenzhao20060217
            if(!user_mute) AUDIF_Demute();
            #endif
            spdifin_type=spdifin_mode;
        }
        break;    
	case SPDIFIN_DTS_MODE:     
	case SPDIFIN_DTSCD_MODE:     
		if (bitrate > 28) bitrate=0;
        
		if(spdifin_mode!=spdifin_type)
        {
            if(spdifin_mode==SPDIFIN_DTSCD_MODE)
                printf("SPDIFIN_DTSCD_MODE\n");
            else
            printf("SPDIFIN_DTS_MODE\n");
            AUDIF_Set_CodingMode(AUDIF_CODING_MODE_SPDIFINDTS);
            spdifin_type=spdifin_mode;
            #if defined(SPDIF_IN_POP_MUTE)//chenzhao20060211
            if(!user_mute) AUDIF_Demute();
            #endif
        }
		break;
	default:
        previousRatio=FS_44K_CENTRAL_PERIOD;
        AUDIF_Set_CodingMode(AUDIF_CODING_MODE_SPDIFINCD);

        #if defined(SPDIF_IN_INVALID_SOURCE_MUTE)//chenzhao 2006-3-23 9:38 .
        AUDIF_Set_Volume(0);
        #endif
        printf("SPDIFIN_UNKNOW_MODE\n");
        spdifin_type=SPDIFIN_NO_SIGNAL_MODE;
        break;
    }   

    show_spdif_in_msg(spdifin_mode, sample_rate, channel, bitrate);
    spdif_in_channel=channel;//chenzhao20060118
    #if 0//def MERGE_TEMP
    spdif_in_sample_rate=sample_rate;
    #endif

	return ; 
}
#endif  // SUPPORT_SPDIF_IN





#if 0  //2004AUDDRV : move to auddrv.c
void audif_set_smp_rate(UINT32 freq)
{
#ifdef AUDIF_DBG
    audif_printf("audif_set_smp_rate: %x\n", freq);
#endif
	
	/*
    switch (freq)
    {
	case 8000:
	case 16000:
	case 32000:
	audif_set_sample_rate(FS_32K);
	break;
	case 11025:
	case 22050:
	case 44100:
	audif_set_sample_rate(FS_44K);
	break;
	default:
	audif_set_sample_rate(FS_48K);
	break;
    }
	*/
    if ((freq>=(8000-500) && freq<=(8000+500))      ||
        (freq>=(16000-500) && freq<=(16000+500))    ||
        (freq>=(32000-500) && freq<=(32000+500))    ) 
    {
        audif_set_sample_rate(FS_32K);
    }
    else if ((freq>=(11025-500) && freq<=(11025+500))   ||
		(freq>=(22050-500) && freq<=(22050+500))   ||
		(freq>=(44100-500) && freq<=(44100+500))   ) 
    {
        audif_set_sample_rate(FS_44K);
    }
    else
        audif_set_sample_rate(FS_48K);
}

//
// audif_set_sample_rate
// FS_44K
// FS_48K
// FS_96K
// FS_32K
//
void    audif_set_sample_rate(int smp_rate)
{
    UINT32 t1, t2;
	
#ifdef AUDIF_DBG
    audif_printf("audif_set_sample_rate: %x frequency_mask:%x frequency_multiple:%x\n", smp_rate,frequency_mask,frequency_multiple);
#endif
	
    // do frequency mask checking
    t1 = smp_rate;
    t2 = 1;
    while ((t1 & frequency_mask) == 0)
    {
        t2 <<= 1;
        t1 >>= 4;
        if (t1 <= 0)
            break;
    }
	
    // frequency not supported
    if ((t1&frequency_mask) == 0)
        t1 = FS_DEFAULT;
	
    if (t2 != frequency_multiple)
    {
        frequency_multiple = t2;
		
		//      audif_printf("## %x %x %x %x %x %x\n", smp_rate, smp_rate_now, t1, smp_rate_down, t2, frequency_multiple);
        init_new_dsp_code(coding_mode_now);
        wait_dsp_busy(0);
    }
	
    audhw_set_samp_rate(t1);
    
    smp_rate_now = smp_rate_down = smp_rate;
	
#ifdef PCM1742 //Jeff 20030917
    dac_set_fs(smp_rate);
#endif
	
    #ifdef EASTWIN_PORTABLE_DVD
    #include "setup_page.h"
	setup_SetFreqMaskConfig();//tulijuan040915
	//audif_set_frequency_mask(2);//SETUP_FREQ_MASK-2);//tulijuan040915
	#endif
    audif_printf("set SR:%x\n",t1);
}

//terry,2004/2/4 02:45PM
/*
sampling rate setting
nibble 3            nibble 2    nibble 1    nibble 0
bit resolution      4x          2x          1x

  nibble  0   1   2
  32k 44k 48k
*/
#define MASK_TBL_MAX_VAL 3
const UINT16 mask_table[MASK_TBL_MAX_VAL]={0x0007, 0x0067, 0x0667}; //we only support 44k/48k multiples
UINT16  audif_set_frequency_mask(UINT16 mask)
{
#ifdef AUDIF_DBG
    audif_printf("audif_set_frequency_mask,sel:%x\n", mask);
#endif
    
    if(mask<MASK_TBL_MAX_VAL) mask = mask_table[mask];
#ifdef AUDIF_DBG
    audif_printf("audif_set_frequency_mask: mask:%x\n", mask);
#endif
    
    if (frequency_mask == mask) return mask;
	
    frequency_mask = mask;
	
    AUDIF_Set_SampleRate(smp_rate_now);//2004AUDDRV audif_set_sample_rate(smp_rate_now);
	
    return frequency_mask;
}



UINT16  audif_get_frequency_mask()
{
    return frequency_mask;
}

#ifdef HDD_INDEX_TEST
extern BYTE bIsQueueEmpty(void);
#endif //#ifdef HDD_INDEX_TEST

//
// FUNCTION
// audif_set_channel
//
void    audif_set_channel(int chn)
{
	int		changed=0;
	UINT8	audsid;
	UINT8	audchn;
	UINT16	__mpeg_audio=0;

#ifdef SUPPORT_MIDI
#ifdef HDD_INDEX_TEST
    if(media_type==MEDIA_CARD) { //Jeff 20040315
        if ( bIsQueueEmpty() ) {
            chn = 0xf;
        }
    } else
#endif //#ifdef HDD_INDEX_TEST
#ifdef YUXING_MIDI_DVD    //ouyang add for no voice when playing mididisc title2004-11-9 14:40
    if ( Is_MIDI_STATE() )
	{
		chn = 0xf;
	}
#else	   
	if ( (Is_MIDI_STATE() )&&(!bIsPlayMidiTitle))
	{
		chn = 0xf;
	}else if (bIsPlayMidiTitle)
        {
		    chn = 0x0;
    	}
#endif   //#ifdef YUXING_MIDI_DVD      
#endif
		
#ifdef AUDIF_DBG
	audif_printf("set channel:%x\n",chn);
#endif

	// CGMS control for DSP code
	//regs0->dsp24_port[13] = 0x01;		// set default to "not used"
	//regs0->dsp24_port[13] = 0x03;		// set default to "no copy allowed"  
	// benson update for dsp request 2005/7/8 01:49下午
	regs0->dsp24_port[13] &= 0xfffc ;
	regs0->dsp24_port[13] |= 0x03;
	if (ninf_get_dvd_CPM())
           {
	    	regs0->dsp24_port[13] &= 0xfffc;
	 	regs0->dsp24_port[13] |= ninf_get_dvd_CGMS();
	   }	
	
	audsid	= stream_audio;
	audchn	= audio_chan_num;

#ifdef SUPPORT_MP4
    if (GetCurrentFileType() == CDROM_MP4)
    {
        if (audchn != chn)
        {
            mp4_aud_channel_flg = 1;
            audio_chan_num = chn;
        }
    }
#endif

	switch(coding_mode_now)
	{
	case AUDIF_CODING_MODE_AC3:
		audsid = 0x80 | chn; 
		break;
	case AUDIF_CODING_MODE_DTS:
		audsid = 0x88 | chn;
		break;
	case AUDIF_CODING_MODE_LPCM:
	case AUDIF_CODING_MODE_PPCM:
		audsid = 0xa0 | chn;
		break;
	case AUDIF_CODING_MODE_SDDS:    //Jeff 20010816
		audsid = 0x90 | chn; 
		break;
		
	case AUDIF_CODING_MODE_JPG:
	case AUDIF_CODING_MODE_NES:
	case AUDIF_CODING_MODE_PCM:
	case AUDIF_CODING_MODE_WMA:
#ifdef SUPPORT_AAC
    case AUDIF_CODING_MODE_AAC:
#endif
	case AUDIF_CODING_MODE_DTSCD:
#ifdef SUPPORT_SPDIF_IN
	case AUDIF_CODING_MODE_SPDIFINCD:       // benson modify 2004/2/25 02:11上午
	case AUDIF_CODING_MODE_SPDIFINAC3:
	case AUDIF_CODING_MODE_SPDIFINDTS:    
#endif
#ifdef SUPPORT_AV_IN
	case AUDIF_CODING_MODE_TUNER:
#endif
		break;
	default:    // mpeg audio 
        audsid     = 0xc0 | chn; 
		
		if(cd_type_loaded!=CDDVD) __mpeg_audio=1;
		break;    
	}
	
	mpeg_audio        = __mpeg_audio;
	
	if (stream_audio!=audsid)
	{
		stream_audio = audsid;
		changed = 1;
	}

	ki_set_au_stream(audsid);
	
	if ((changed)&&(cd_type_loaded!=CDSVCD))//nono 4-2-25 23:58
	{
    audif_printf("audio channel chg,run audio stop\n");
#ifndef CNTR_5SPK_VOLUME    //for 5_1ch,wangfeng 2004-2-4 15:15
		AudioSetStop();     
#endif
		
#ifdef SUPPORT_NESGAME    
        if(coding_mode_now!=AUDIF_CODING_MODE_NES)//terry,2004/5/12 04:38PM
#endif  
       	     resync_audio_bitstream();
		
#ifndef CNTR_5SPK_VOLUME    //for 5_1ch,wangfeng 2004-2-4 15:15
		AudioSetPlay(); 
#endif  
	}
}



int audif_auto_download_codec(UINT8 chn)
{
    int res=0;
    UINT8 stream_id,codec_id;
    
    //print_block(stream_audio_table,8);
    if(stream_audio_table[chn]==0)
		chn=0;
    
    stream_id=stream_audio_table[chn];
    if(stream_id>=0x80)
    {
        res=1;
        codec_id=CODING_MODE_MP2;
        if(stream_id<0x88)
        {//AC3
            codec_id=CODING_MODE_AC3;           
        }else  if(stream_id<0x90)
        {//DTS
            codec_id=CODING_MODE_DTS;
        }
        else if(stream_id<0xa8)
        {//LPCM
            codec_id=CODING_MODE_LPCM;
        }       
        audif_set_coding_mode(1<<codec_id);
        audif_set_channel(chn);
        audif_set_sample_rate(FS_48K);//default
    }
    
    return res;
}
#endif //2004AUDDRV

#if 0
//
// FUNCTION
// audif_download_codec
// DESCRIPTION
// download specific DSP codec
//
static void
audif_download_codec(int coding_mode)
{
#ifdef  MONE_DOWNLOAD_CODEC
    audif_printf("<download - coding_mode:%x>\n",coding_mode);
#endif
	
#ifndef SPHE1000	// barry remove it in HE1000 because in dsp3_download had stop it
    regs0->aud_enable = 0;  // disable PCM H/W (PCM, SPDIF, ADC)
    dsp3_stop();            // force dsp stop.
#endif
	// in fact, the codes were duplicated in the following dsp3_download()
    /*mark v2.04.00
    #ifdef PORTABLE_DVD
    if(cd_type_loaded==CDDA)
    {
	//is_iop_call_back(0,0,CDDA);
    }   
    #endif
    */
    
    //audhw_spdif_off(smp_rate_now); //terry,2004/2/18 06:03PM
	
#ifdef MOVE_WMA_DSP_CODEC_ADDR//terry,2004/1/12 05:02PM // 2004/09/16 yltseng
    if( (cd_type_loaded==CDROM)&&(coding_mode==AUDIF_CODING_MODE_WMA) )
		set_aud_buf(A_DSP24_WMA_YA,A_AUD_WMA_YA, A_PCM_WMA_YA);
#endif        
	
    switch(coding_mode)
    {
    case AUDIF_CODING_MODE_DTS:          
#if !defined(NO_DTS_OUTPUT)||defined(FORCE_NO_DTS_OUTPUT)//nono 4-5-5 13:45
        printf("\n\n ---> download dts\n");
        dsp3_download(DSP3code_DTS,DSP3codelen_DTS); break;
#elif defined(DTS_SPDIF_NO_OUTPUT)
        printf("\n\n ---> download AC3\n");
        dsp3_download(DSP3code_AC3,DSP3codelen_AC3); break;  // change by Tom 20040715
#else//#if !defined(NO_DTS_OUTPUT)||defined(FORCE_NO_DTS_OUTPUT)//nono 4-5-5 13:45
        printf("\n\n ---> download spdif\n");
        dsp3_download(DSP3code_SPDIF,DSP3codelen_SPDIF);break;      
#endif//#if !defined(NO_DTS_OUTPUT)||defined(FORCE_NO_DTS_OUTPUT)//nono 4-5-5 13:45
    case AUDIF_CODING_MODE_DTSCD:          
#if defined(NO_DTS_OUTPUT)&&!defined(FORCE_NO_DTS_OUTPUT)//terry,2004/1/28 02:19PM
#ifdef  USE_LPCM_REPLACE_PCM
	#if defined(DTS_SPDIF_NO_OUTPUT)
        printf("\n\n ---> download AC3\n");
        dsp3_download(DSP3code_AC3,DSP3codelen_AC3); break;  // change by Tom 20040715
	#else
		printf("\n\n ---> download LPCM\n");
		dsp3_download(DSP3code_LPCM,DSP3codelen_LPCM); break;    
	#endif
#else        
	#if defined(DTS_SPDIF_NO_OUTPUT)
        printf("\n\n ---> download AC3\n");
        dsp3_download(DSP3code_AC3,DSP3codelen_AC3); break;  // change by Tom 20040715
	#else
        printf("\n\n ---> download cdda\n");
		dsp3_download(DSP3code_CD,DSP3codelen_CD); break;
#endif        
#endif        
#else//#if defined(NO_DTS_OUTPUT)&&!defined(FORCE_NO_DTS_OUTPUT)//terry,2004/1/28 02:19PM
        
#if defined(SPHE8202) || defined(SPHE1000)
        printf("\n\n ---> download dts\n");
        dsp3_download(DSP3code_DTS,DSP3codelen_DTS); break;
#else        
        printf("\n\n ---> download dts-cd\n");
        dsp3_download(DSP3code_DTSCD,DSP3codelen_DTSCD); break;
#endif        
        
#endif//#if defined(NO_DTS_OUTPUT)&&!defined(FORCE_NO_DTS_OUTPUT)//terry,2004/1/28 02:19PM
		
#ifdef DVD_AUDIO        
    case AUDIF_CODING_MODE_PPCM:
        printf("\n\n ---> download ppcm\n");
        dsp3_download(DSP3code_PPCM,DSP3codelen_PPCM); break;
#endif
		
    case AUDIF_CODING_MODE_AC3:
#ifdef SDRAM_16Mb_Mode    //terry,2003/12/9 06:00PM

#if !defined(SUPPORT_SDRAM16M_AC3_5_1CH_OUTPUT)&&!defined(RAW_HAVE_ANALOG_OUTPUT)
        if( setup_IsSet2SPDIF_Bitstream() )
        {
			printf("\n\n ---> download spdif\n");
			dsp3_download(DSP3code_SPDIF,DSP3codelen_SPDIF);
        }
        else
#endif//SUPPORT_SDRAM16M_AC3_5_1CH_OUTPUT
        {
			printf("\n\n ---> download ac3\n");
			dsp3_download(DSP3code_AC3,DSP3codelen_AC3); 
        }   
        break;        
#else
        printf("\n\n ---> download ac3\n");
        dsp3_download(DSP3code_AC3,DSP3codelen_AC3); break;
#endif        
		
    case AUDIF_CODING_MODE_PCM:
        printf("\n\n ---> download cdda\n");
		
#ifdef  USE_LPCM_REPLACE_PCM
        printf("\n\n ---> download LPCM\n");
        dsp3_download(DSP3code_LPCM,DSP3codelen_LPCM); break;    
#else        
        printf("\n\n ---> download cdda\n");
        dsp3_download(DSP3code_CD,DSP3codelen_CD); break;
#endif        
        
#if defined(SUPPORT_WMA) || defined(SUPPORT_AUD_WMA)
    case AUDIF_CODING_MODE_WMA:
        printf("\n\n ---> download wma\n");
        dsp3_download(DSP3code_WMA,DSP3codelen_WMA); break;
#endif  

#ifdef SUPPORT_AAC    
    case AUDIF_CODING_MODE_AAC:
        printf("\n\n ---> download aac\n");
        dsp3_download(DSP3code_AAC,DSP3codelen_AAC); break; // 2004/10/12 yltseng
#endif  

        
#ifdef JPGDSP
    case AUDIF_CODING_MODE_JPG: 
        dsp3_download(DSP3code_JPG,DSP3codelen_JPG); break;
#endif
		
#ifdef SUPPORT_NESGAME
    case AUDIF_CODING_MODE_NES:
        dsp3_download(DSP3code_NES,DSP3codelen_NES); break;        
#endif
		
#if 0 //terry,2004/2/12 03:30PM
    case AUDIF_CODING_MODE_SPDIF:  
        if (coding_mode_now&AUDIF_CODING_MODE_AC3) {
            printf("\n\n ---> download ac3\n");
            dsp3_download(DSP3code_AC3,DSP3codelen_AC3);
        } else if (coding_mode_now&AUDIF_CODING_MODE_DTS) {
            printf("\n\n ---> download dts\n");
            dsp3_download(DSP3code_DTS,DSP3codelen_DTS);
        }
        break;        
#endif
#ifdef SUPPORT_SPDIF_IN   // benson 
	case AUDIF_CODING_MODE_SPDIFINCD: 
        dsp3_download(DSP3code_spdifincd,DSP3codelen_spdifincd); break;
	case AUDIF_CODING_MODE_SPDIFINAC3: 
        dsp3_download(DSP3code_spdifinac3,DSP3codelen_spdifinac3); break;
	case AUDIF_CODING_MODE_SPDIFINDTS: 
        dsp3_download(DSP3code_spdifindts,DSP3codelen_spdifindts); break;        
#endif
		
//#ifdef SUPPORT_AV_IN   // benson 2004/2/4 11:34上午
#if defined(SUPPORT_AV_IN) || defined(SUPPORT_SECOND_AV_IN) || defined(SUPPORT_TUNER_MV114)   // xyy 2004-8-12
	case AUDIF_CODING_MODE_TUNER:
        //printf("download tuner mode\n");
        dsp3_download(DSP3code_tuner,DSP3codelen_tuner); break;   
#endif         
		
#ifdef SUPPORT_TESTSPK
	case AUDIF_CODING_MODE_NOISE:
        //printf("download noise mode\n");
        dsp3_download(DSP3code_noise,DSP3codelen_noise); break;
#endif		
		
#ifdef SUPPORT_MIDI
    case AUDIF_CODING_MODE_MIDI:  
        //if ((regs0->stamp)>=2) //remark by axel 2004/4/19 10:24  
        dsp3_download(DSP3code_MIDI,DSP3codelen_MIDI);
        //else
        //dsp3_download(DSP3code_LPCM,DSP3codelen_LPCM);  
        
        break;
        
#endif
		
    case AUDIF_CODING_MODE_LPCM:
		printf("\n\n ---> download lpcm\n");
        dsp3_download(DSP3code_LPCM,DSP3codelen_LPCM); break;    
		
    case AUDIF_CODING_MODE_MP2:
    case AUDIF_CODING_MODE_MP3:
    default:
		printf("\n\n ---> download mpeg\n");
        dsp3_download(DSP3code_MP3,DSP3codelen_MP3); break; 
    }
}
#endif //2004AUDDRV

#if 0 //2004AUDDRV : move to auddrv.c
//
// wait_dsp_busy
//
void wait_dsp_busy(int dspChanged)
{
    //delay_srv_10ms(2);//2004/3/8 11:40PM,terry
    wait_dsp_port0_5(0,1,0,200000);//terry,2003/8/8 03:46AM
	
	
	
    if (coding_mode_now==AUDIF_CODING_MODE_AC3) {
        //If it is AC3, we need to set some configure(subwoofer, speaker gain, speaker delay)
        setup_SetAC3Config();
    }
	
    if (dspChanged) 
    {
		//set common audio configure when DSP audio change
		if ( (cd_type_loaded==CDDA) && (coding_mode_now==AUDIF_CODING_MODE_DTSCD) ) { //Jeff 20020719            
            delay_srv_10ms(15);
		}
         #ifdef SUPPORT_DSPMUTE
	regs0->dsp24_port[14] = 0x0;   // for dsp mute benson 2004/7/12 01:13下午
         #endif 
    }
	
#if defined(SUPPORT_AUDIO_RESET)&&defined(HANYANG_4340_AUDRESET)
     regs0->sft_cfg3 &= ~(0x1 << 4);
    regs0->gpio_master[60 / 16] |= (0x01 << (60 % 16));
    regs0->gpio_oe[60 / 16] |= (0x01 << (60 % 16));
    regs0->gpio_out[60 / 16] |= (0x01 << (60 % 16));
    delay_srv_10ms(30);
#endif
	
    // gpio demute
    if(power_on_mute==0)//terry,2003-8-5 3:16
    {
		GPIO_DEMUTE();
    }
	
	
    AudioSetPlay();
	
    //do extra mute when we switch to SPDIF/BITSTREAM, Jeff 20021202
    if ( setup_IsSet2SPDIF_Bitstream() && (coding_mode_now==AUDIF_CODING_MODE_PCM) )
    {
        extern BYTE audioNotContinuous;
		
        audioNotContinuous=20;
        AudioSetVolume(0); 
    }
}
#endif //2004AUDDRV

extern BYTE audioNotContinuous;

//
// init_new_dsp_code
//

#if 0 //2004AUDDRV move to auddrv.c AUDIF_Init_NewDSPCodec
#ifdef SUPPORT_RECEIVER
void init_new_dsp_code(UINT32 coding_mode)    // benson modify 2004/3/1 09:24上午
#else
void init_new_dsp_code(UINT16 coding_mode)
#endif
{
    dsp3_ramp_down(1);
    dsp3_ramp_wait();
    
    regs0->dsp24_port[5] = -1;
    audif_download_codec(coding_mode);
    dsp3_ramp_up(1);
	
    buf_barrier_size    = (coding_mode==AUDIF_CODING_MODE_LPCM) ? 1024 : 8;
    AudioSetPlay();
}
#endif

#if 0 //2004AUDDRV : no more useful
/*
* 2003/12/25 09:50PM
*/
int dts_audio_mute(void)
{
    int r;
	
    if (hardware_no_dts()) r=1;
    else r=0;
	
#ifdef SUPPORT_PASSWD3//for test    
    if (setup_audio_mode==1) r=0;
#endif
	
    return r;
}
#endif

/*
* Terry,2004/1/14 12:02PM
*/
#ifdef SUPPORT_UART_COMMAND // robert 020808
static inline void audif_uart_command(int coding_mode)
{
	// send AC3 command to 8051
	if (AUDIF_CODING_MODE_AC3 == coding_mode)
	{
		UART_PUTC_EXACT(COMMAND_START);
		UART_PUTC_EXACT(AC3_STATUS);
		UART_PUTC_EXACT(IS_AC3);
		UART_PUTC_EXACT(COMMAND_END);
		
#if 0
		psprintf(RegionValStr[REGION3], "SEND 8051 IS AC3");
		PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
	}
#ifdef NEW_UART_COMMAND  //lijinhai solve for fuss ac3
	else if(AUDIF_CODING_MODE_AC3 == coding_mode_now||first_init_disk_audio)   
#else
        else if(AUDIF_CODING_MODE_AC3 == coding_mode_now)
#endif  
	{
		UART_PUTC_EXACT(COMMAND_START);
		UART_PUTC_EXACT(AC3_STATUS);
		UART_PUTC_EXACT(NOT_AC3);
		UART_PUTC_EXACT(COMMAND_END);
#if 0
		psprintf(RegionValStr[REGION3], "SEND 8051 NOT AC3");
		PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif
	}
#ifdef NEW_UART_COMMAND
	first_init_disk_audio=0;
#endif     
}
#endif

#if 0 //2004AUDDRV : move to auddrv.c
//
// FUNCTION
// audif_set_coding_mode
//
void    audif_set_coding_mode(int coding_mode)
{
    int dspChanged;
	
#ifdef AUDIF_DBG
    audif_printf("set coding_mode:%x\n",coding_mode);
#endif
	
#if 1//nono 2004-8-4 17:43
    setup_SetAC3PCMConfig();
#endif//

	
    if( setup_IsSet2SPDIF_Bitstream()&&(cd_subtype != CD_DTS) ) //terry,2004/2/16 12:04PM
		isSPDIFBitstream = 1;
    else
		isSPDIFBitstream = 0;
	
    dspChanged=0;
	
#ifdef NEW_UART_COMMAND  //lijinhai solve for fuss ac3
    if (coding_mode_now!=coding_mode||first_init_disk_audio)
#elif defined(SUPPORT_MIDI_MENU_SEL)
		if(((coding_mode_now!=coding_mode)) ||(gIsMidiSelMenu))
#else
			if (coding_mode_now!=coding_mode)
#endif
			{       
#ifdef SUPPORT_UART_COMMAND     //freyman 2004-2-26 21:07
				audif_uart_command(coding_mode);
#endif
				//dac_turn_off();  //Jeff 20020603
				dspChanged = 1;
				
				if(coding_mode!=AUDIF_CODING_MODE_NOW)
					coding_mode_now = coding_mode;
				
				init_new_dsp_code(coding_mode_now);        
				audif_set_channel(0);
				wait_dsp_busy(dspChanged);
				
			} //end of if (coding_mode_now!=coding_mode)
			
#ifdef DYNAMIC_SPECTRUM
			if(band_onoff)
				setup_eq_display(0xf);
#endif      
			
}
#endif //2004AUDDRV

#if 0 //terry,2004/2/12 03:28PM
//Force to load SPDIF/BITSTREAM decoder
void    audif_set_SPDIF_BITSTREAM()
{
    init_new_dsp_code(AUDIF_CODING_MODE_SPDIF);    
    isSPDIFBitstream = 1;    
    //to start DSP and set system configure    
    wait_dsp_busy(0);        
}
#endif

#if 0 //2004AUDDRV : move to auddrv.c
//
// DSPReset
//
void    DSPReset()
{
	//    int i;
	
#ifdef AUDIF_DBG
    audif_printf("DSPReset() : coding_mode_now=%x\n",coding_mode_now);
#endif
    
	
    AudioSetStop();
    regs0->dsp24_port[5] = -1;
	
#if 0//ndef SETUP_DONT_PAUSE//4-2-14 13:45
    delay_srv_10ms(10);
#endif//SETUP_DONT_PAUSE
    
    //force to re-load same DSP audio decoder
    buf_barrier_size    = (coding_mode_now == AUDIF_CODING_MODE_LPCM) ? 1024 : 8;
    audif_download_codec(coding_mode_now);
	
	
    {
        //wait until DSP Audio is ready to receive command
        wait_dsp_port0_5(0,1,0,200000);//terry,2003/8/8 03:46AM
		
        if (coding_mode_now==AUDIF_CODING_MODE_AC3) {
            //If it is AC3, we need to set some configure(subwoofer, speaker gain, speaker delay)
            setup_SetAC3Config();
#if 1//nono 2004-8-4 17:44
            setup_SetAC3PCMConfig();
#endif

        }
		
#if 1//def SETUP_DONT_PAUSE//4-2-14 13:45
		delay_srv_10ms(10);
#endif//SETUP_DONT_PAUSE
		
        AudioSetPlay();
		
    }
}
#endif //2004AUDDRV

