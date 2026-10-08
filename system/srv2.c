//
// FILE
// srv2.c
//
// DESCRIPTION
// service of stream
//
// Modified cyue 2002/11/4 01:39下午, move hd_pump() to hdd_play.c, and call in polling()!!
//
//
//



#if	!(defined(DVDRELEASE) || defined(SIMULATION_FAST))
//#define SERVICE_DBG 1
#endif

//
// inclusion
//

#include "config.h"
#include "global.h"
#include "pu8560.h"
#include "regmap.h"
#include "global.h"
#include "memmap.h"

#include "stc.h"
#include "avd.h"
#include "avdctrl.h"
#include "dvdpe.h"
#include "avsync.h"
//


#include "estd.h"

//#include "vld.h"
#include "mpegsys.h"

#include "sio.h"
#include "emuio.h"

#include "navif.h"
#include "framebuf.h"
#include "func.h"
#include "hdd_if.h"

#include "auddrv.h" //2004AUDDRV oliver 20041004 for using audio driver purpose
//#include "audif.h" //cyue: use system audio define!! 2002/11/2 10:13上午
#include "srv2.h" // cyue, move defs in stream.h 2002/11/4 01:26下午








extern PLAY_BLOCK PlayBlock; 
#ifdef SUPPORT_STREAM_BUFFER

extern void volume_init(void);
//2004AUDDRV extern int init_audio(void);

#if 0 // Move to stream.h"
// 
// 0x88400000, 4th mega in SDRAM
//    block0   | block1    | ..........| block15
//  -----------+-----------+------------------ 
//	|  32k	   |  32k      |           |
//  (power of 2)

#define STREAM_MAX_ACCESS 32768 // Not too much for one access!!
#define STREAM_DATA_BASE	(0x88400000)
#define STREAM_BLK_NUM		8 //POWER of 2
#define STREAM_BLK_LEN_PWR 17 // 15=32k
#define	STREAM_BLK_LEN	(1<<STREAM_BLK_LEN_PWR)
#define START_BUFF_KEEP (STREAM_BLK_NUM-3)
//
// USEAGE:
// 1. DURING YOUR SOURCE POLLING:
//		1. stream_full() to check if we can put data in
//		2. call stream_putheader to get the pointer to write to
//		3. copy len(<2k) into stream_putheader
//		4. call stream_append(len) to let stream system know 
//		   data appended
//
// 2. Sample playing:
//		stream_init();
//		play_state = VCD_STATE_NORMAL;
//		while (1)
//		{
//			audif_set_coding_mode(AUDIF_CODING_MODE_MP2);	  
//			MacroPlayStream();
//			MediaMainLoop();
//		}
//
// Limitation: NOT to append more than STREAM_MAX_ACCESS
//             to stream in each access !!
//
//
#endif



BYTE	*bCurrMpegBuff=((BYTE *)STREAM_DATA_BASE);
UINT32 	rlen;
UINT16	str_time,str_lasttime;
BYTE	bCurBlock;
BYTE	bPlayBlock;
UINT32	unMpegDataLen[STREAM_BLK_NUM];
BYTE	bBufferKeep;

//======================================================
//void stream_init()
//      initial stream buffer
//INPUT  ARGUMENTS: NONE 
//OUTPUT ARGUMENTS: NONE;
//RETURN: NONE
//======================================================
void stream_init()
{
	int i;
	bPlayBlock=STREAM_BLK_NUM-1;
	rlen=0;
	bCurBlock=0;
	*bCurrMpegBuff=((BYTE *)STREAM_DATA_BASE);
	bBufferKeep=0;
	for(i=0;i<STREAM_BLK_NUM;i++)
	{
		unMpegDataLen[i]=0; // Each block no length!!
	}
	str_time=str_lasttime=0;
}

//======================================================
//int stream_full()
//      Check if stream buffer is full
//INPUT  ARGUMENTS: NONE;
//OUTPUT ARGUMENTS: NONE;
//RETURN: nonzero means full
//======================================================
int stream_full()
{
	return unMpegDataLen[bCurBlock];
}

//======================================================
//void *stream_putheader()
//      Get the stream-buffer header
//      Thus we can put data there
//INPUT  ARGUMENTS: NONE;
//OUTPUT ARGUMENTS: NONE;
//RETURN: buffer header to put buffer
//======================================================
void *stream_putheader()
{
	return (void*)bCurrMpegBuff;
}

//======================================================
//void stream_append(UINT32 len)
//      append stream with putted length
//INPUT  ARGUMENTS: 
//      len: length to append to stream. 0 means block end
//OUTPUT ARGUMENTS: NONE;
//RETURN: NONE
//======================================================
void stream_append(UINT32 len)
{
	rlen+=len;				
	bCurrMpegBuff+=len;		
	if ((!len)||(rlen>STREAM_BLK_LEN-STREAM_MAX_ACCESS))				
	{
		unMpegDataLen[bCurBlock]=rlen;
		bCurBlock=(bCurBlock+1)&(STREAM_BLK_NUM-1);//cyue: (...)%STREAM_BLK_NUM;
		rlen=0;
		bCurrMpegBuff=(BYTE *)(STREAM_DATA_BASE+(bCurBlock<<STREAM_BLK_LEN_PWR));
		if (bBufferKeep<START_BUFF_KEEP)	
			bBufferKeep++;
		if(!len) // Append Zero: Let data in buffer can be out!!
		{
			bCurBlock=bPlayBlock;
			bBufferKeep=START_BUFF_KEEP;
		}
	}
}


//======================================================
//unsigned	stream_get_buffer(UINT8 **p)
//      get data pointer to play
//INPUT  ARGUMENTS: none
//OUTPUT ARGUMENTS: 
//     **p: data pointer return
//RETURN: 0: no data in stream
//     otherwize: stream len
//======================================================
unsigned	stream_get_buffer(UINT8 **p)
{
	if(bBufferKeep<START_BUFF_KEEP)
	{
		*p=NULL; return 0; // No Enough Playing Buffer
	}
	unMpegDataLen[bPlayBlock]=0;	
	bPlayBlock=(bPlayBlock+1)&(STREAM_BLK_NUM-1);	  	
	if (unMpegDataLen[bPlayBlock]==0)// No Data Here?
	{
		*p=NULL; return 0; // No data block rightnow
	}	
	*p = (UINT8 *)(((BYTE *)(STREAM_DATA_BASE+(bPlayBlock<<STREAM_BLK_LEN_PWR)))); 
	//printf(" StreamHead:0x%x len:%d\n",(UINT32)*p,unMpegDataLen[bPlayBlock]);
	return unMpegDataLen[bPlayBlock];
}


//========================================================================================
//
//  DSP Initial block!! cyue modified 2002/11/2 10:17上午
//  using audif.h, CODING_MODE_XXX
//========================================================================================
//2004AUDDRV init_cdda(void);//kenny
//2004AUDDRV extern void    init_dtscd(void);
//2004AUDDRV extern void    init_mp3(void);
extern int  do_mp3(void);
extern int  do_audio_cdda(void);

int AudioMode;

int GetAudioMode()
{
	return AudioMode;
}

void AudioSet(int atype)
{
	AudioMode=atype;
	//dac_turn_on(); //20020729
	volume_init(); 
	AUDIF_Init_Audio();//2004AUDDRV init_audio();
	play_state = VCD_STATE_POWER;
	//VCD_STATE_NORMAL DOSENT WORK IN DVD
	switch(atype)
	{
	case CODING_MODE_AC3:
		audio_only = 0;
        //20020729 according to file type select audio_coding_mode,in audif.h
        AUDIF_Set_CodingMode(AUDIF_CODING_MODE_AC3);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_AC3);
        AUDIF_Set_SampleRate(FS_48K);//2004AUDDRV audif_set_sample_rate(FS_48K);
		AUDIF_Set_Channel(1);//2004AUDDRV audif_set_channel(1); 
		break;
	case CODING_MODE_MP2:
		audio_only = 0;
		AUDIF_Set_CodingMode(AUDIF_CODING_MODE_MP2);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_MP2);
        AUDIF_Set_SampleRate(FS_44K);//2004AUDDRV audif_set_sample_rate(FS_44K);
		AUDIF_Set_Channel(0);//2004AUDDRV audif_set_channel(0); 
		break;
	case CODING_MODE_MP3:
		audio_only = 1; //Jeff 20011116
		AUDIF_Init_MP3();//2004AUDDRV init_mp3();
		break;
	}
	
}




















//======================================================
//int srv_stream(void)
//      Service Routine for kernel callback
//INPUT  ARGUMENTS: NONE 
//OUTPUT ARGUMENTS: NONE;
//RETURN: 0: no meaning now
//======================================================
int srv_stream(void)
{
	unsigned len = 0;
	unsigned batch;
	while (1)
	{
		//hd_pump(); call from polling();
		if (len==0)
			len = stream_get_buffer(&stream_ptr);
		if (len==0)
		{	
			// Calc timeout!!
			str_time = regs0->rtc_15_0;
			if(	str_lasttime ==0)
				str_lasttime=	str_time;
			if((str_time-str_lasttime)>500) //have no data about 5sec	
			{
				AVD_SetMediaTimeout();
			}			
			return 0;
		}
		else //have data
		{
			str_lasttime =0; // Skip timeout!!
			dma_iptr	= 0;
			switch(GetAudioMode())
			{
#if 1
			case  CODING_MODE_MP3:
				batch	= (len>1024) ? 1024 : len;
			dma_ilen	= batch;
			do 
				{	//hd_pump(); call from polling();
				polling();
				if (IsAVDMediaInterrupt()) return 0;//break;
				} while(do_mp3());
				break;	
#endif
			case  CODING_MODE_PCM:
			case  CODING_MODE_DTSCD:
				batch	= (len>1024) ? 1024 : len;
				dma_ilen	= batch;
				do 
				{	//hd_pump(); call from polling();
					polling();
					if (IsAVDMediaInterrupt()) return 0;//break;
				} while(do_audio_cdda());
				break;	
			default: // CODING_MODE_MP2					case 
				batch	= (len>STREAM_MAX_ACCESS) ? STREAM_MAX_ACCESS : len;
				dma_ilen	= batch;
				do 
				{	//hd_pump(); call from polling();
					polling();
					if (IsAVDMediaInterrupt()) return 0;//break;
				} while(do_system());
				break;
			}
			if (IsAVDMediaInterrupt()) 
				return 0;
			len		-= batch;
			stream_ptr +=batch;
		}
	}
}











#endif


