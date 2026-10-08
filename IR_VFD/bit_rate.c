/*
*  Terry,2004/3/25 04:10PM
*/

#include "bit_rate.h"
#include "global.h"
#include "util.h"
#include "atapi_if.h"
#include "image.h"
#include "kinf.h"
#include "stc.h"

#ifndef DVDRELEASE
    //#define DBG_BIT_RATE    1
#endif

#ifdef DBG_BIT_RATE
    //#define DBG_PRE_PARSE_MP3
    //#define DBG_MP3_HEADER_STREAM
    //#define DBG_AV_BITRATE
#endif

#ifndef DBG_BIT_RATE
    #undef printf
    #undef print_block
    #define printf(f, a...) do {} while (0)
    #define print_block(x,y) do {} while (0)
#endif

// **************************************************************************************** //
#ifdef DISPLAY_DATA_BIT_RATE

UINT16 bit_rate_val = 0;
UINT32 sample_addr  = 0;

// **************************************************************************************** //
void init_bit_rate(void)
{
    bit_rate_val    =   0;
    sample_addr     =   0;
}

// **************************************************************************************** //
//bit-rate range: 8K ~ 10Mbits
//bit_rate_val:   8~10K 
#define MAX_BIT_RATE  (10*1024*1024)
#define MAX_BYTE_RATE (MAX_BIT_RATE/8)
#define MAX_SECTOR_NS (MAX_BYTE_RATE/2048)
#define MAX_KB_NS     (MAX_BYTE_RATE/1024) //1280

#define MIN_BIT_RATE  (8*1024)
#define MIN_BYTE_RATE (MIN_BIT_RATE/8)
#define MIN_SECTOR_NS (MIN_BYTE_RATE/2048)
#define MIN_KB_NS     (MIN_BYTE_RATE/1024) //1

// **************************************************************************************** //
void sample_bit_rate_per_sec(void)
{
    int tmp;
    
    if( adv_search_time == 0 )
    {
        if( cd_type_loaded == CDDVD ) 
            tmp = play_abs_addr;
        else 
            tmp = msf2l( s_msf );
        
        if( tmp > sample_addr )
        {
            tmp = ( tmp - sample_addr ) * 2;
            if( ( tmp >= MIN_KB_NS ) && ( tmp <= MAX_KB_NS ) )
            {
                bit_rate_val = tmp * 8; // 8 ~ 10240
                printf( "<%d>\n", bit_rate_val );
            }
        }
        
        sample_addr = tmp;
    }
}

// **************************************************************************************** //
#else

void    init_bit_rate(void)             {}
void    sample_bit_rate_per_sec(void)   {}

#endif


#ifdef SUPPORT_PRECALCULATE_VIDEOBITRATE_FOR_FILE_MODE
// **************************************************************************************** //
UINT32 GetBPS()
{
    if( adv_search_time != 0 )
        return 0;
        
    UINT32 video_bitrate    = ki_get_video_bitrate();
    if( video_bitrate == 0 )
        return 0;
	//Steven 2006/10/04 modify , use get_dsp3_pcm_value() instead of directly access address //  
    UINT32 audio_bitrate = (get_dsp3_pcm_value(DSP_RUNTIME_MPEG_BITRATE)) << 10;

    UINT32 uiBitrate;
    if( pDSV->dAv_AST_Ns > 0 )
        uiBitrate = video_bitrate + audio_bitrate * pDSV->dAv_AST_Ns;
    else
        uiBitrate = video_bitrate + audio_bitrate;

    #ifdef DBG_AV_BITRATE	
    printf("\tt: %d, v: %d, a: %d\n", uiBitrate, video_bitrate, audio_bitrate );
    #endif
        
    return uiBitrate;
}

#else
// **************************************************************************************** //
extern void     StartBPS( UINT8 uiInterval )    { uiInterval = uiInterval; }
extern UINT32   GetBPS()                        { return 0; }

// **************************************************************************************** //
#endif


#ifdef REMAIN_TIME	
// **************************************************************************************** //
typedef enum 
{
    VBR_MP3_PARSE_FIRST_FRAME,
    VBR_MP3_PARSE_ALL_FRAME,
}   VBR_MP3_FRAME_TYPE;

typedef struct{
    int bitrate;
    char *nextHeaderPtr;
}   MP3INFORM;

// **************************************************************************************** //
static void GetBitRateInform( MP3INFORM* pHeaderInform,UINT32 length )
{
    if( !pHeaderInform || length == 0 )
        return;

    UINT8   layerTable[4] = {0,3,2,1};
    
    UINT16  freqTable[3][3] = {{44100, 48000, 32000,}, 
    			       {22050, 24000, 16000 ,},
    			       {11025 , 12000 , 8000 }};
    
    UINT16  bitrateTable[3][3][16] = { 
       { {0,32,64,96,128,160,192,224,256,288,320,352,384,416,448,},
         {0,32,48,56, 64, 80, 96,112,128,160,192,224,256,320,384,},
         {0,32,40,48, 56, 64, 80, 96,112,128,160,192,224,256,320,} },
    
       { {0,32,48,56,64,80,96,112,128,144,160,176,192,224,256,},
         {0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,},
         {0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,} },
         
      { {0,32,48,56,64,80,96,112,128,144,160,176,192,224,256,},
         {0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,},
         {0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,} }
         
    }; //MPEG1,MPEG2,MPEG2.5
    
    char*   stream          = pHeaderInform->nextHeaderPtr;
    UINT32  Header          = 0xFFFFFFFF;
    UINT32  NextHeader      = 0xFFFFFFFF;
    UINT32  syncwordMask    = 0xFFE00000; 
    UINT32  layerMask       = 0x00060000;
    UINT32  bitrateMask     = 0x0000F000;
    UINT32  sampleMask      = 0x00000C00;
    char*   NextSyncPtr     = NULL;
    int     syncshift       = 20;
    int     layershift      = 17;
    int     bitrateshift    = 12;
    int     sampleshift     = 10;
    int     hitSyncWord     = 0;
    int     layerNo         = 0;
    int     bitrate         = 0;
    int     freqs           = 0;
    int     bitrateIndex, ID,slotNo,MPEG_Ver;
    UINT32  syncLag;
    
    Header=((unsigned int)(*stream))<<24;                   stream++;
    Header=Header|((((unsigned int)(*stream))<<24)>>8);     stream++;
    Header=Header|((((unsigned int)(*stream))<<24)>>16);    stream++;
    Header=Header|(((unsigned int)(*stream)<<24)>>24);      stream++;
    length=length-4;

    #ifdef DBG_MP3_HEADER_STREAM    
    printf("Header = %x \n", Header);
    #endif

    //find the sync word
    while((hitSyncWord==0)&&(length!=0))
    {
        if(((Header&syncwordMask)>>syncshift)==0xFFE) //check sync word
        {
        	layerNo=layerTable[((Header&layerMask)>>layershift)];
        	if(layerNo!=0)  //check layer No
        	{
        		bitrateIndex=((Header&bitrateMask)>>bitrateshift);
        		if(bitrateIndex!=0xf&&bitrateIndex!=0x0)//check bitrate index
        		{
        			MPEG_Ver=(Header & (1<<20)) ? 0x1 : 0x2;
        			ID=(Header & (1<<19)) ? 0x0 : 0x1;
        			if(MPEG_Ver==1)
        			{
        			MPEG_Ver=ID;
        			}
        			bitrate=bitrateTable[MPEG_Ver][layerNo-1][bitrateIndex];
        			if(((Header&sampleMask)>>sampleshift)!=0x3) //check sampling frequency
        			{
        			freqs=freqTable[MPEG_Ver][((Header&sampleMask)>>sampleshift)];
        				if(layerNo==1)
        				{//layer I
        				syncLag=12*bitrate*1000/freqs;
        				}
        				else
        				{//layer II,III
        					syncLag=144*bitrate*1000/freqs;
        				}
        				for(slotNo=0;slotNo<2;slotNo++)
        				{
        					NextSyncPtr=stream-4+syncLag+slotNo;
        					if(length>syncLag)
        					{
        						NextHeader=((unsigned int)(*NextSyncPtr))<<24;                      NextSyncPtr++;
        						NextHeader=NextHeader|((((unsigned int)(*NextSyncPtr))<<24)>>8);    NextSyncPtr++;
        						NextHeader=NextHeader|((((unsigned int)(*NextSyncPtr))<<24)>>16);   NextSyncPtr++;
        						NextHeader=NextHeader|(((unsigned int)(*NextSyncPtr)<<24)>>24);     NextSyncPtr++;
        					
        						if(((NextHeader&syncwordMask)>>syncshift)==0xFFE) //confirm sync word
        						{
                                    if((((NextHeader&layerMask)>>layershift)!=0x0)&&((NextHeader&layerMask)==(Header&layerMask))) //chenzhao 2006-10-13 14:26 .NextHeader and Header should have the same layer.
        							{
        								if(((NextHeader&bitrateMask)>>bitrateshift)!=0xf&&((NextHeader&bitrateMask)>>bitrateshift)!=0x0)
        								{
        									if(((NextHeader&sampleMask)>>sampleshift)!=0x3)
        									{
        										hitSyncWord=1;
        										
    #ifdef DBG_MP3_HEADER_STREAM
        										printf("len=%d,header=%x ",length,Header);	
    #endif
   											break;
        									}	
        						    		}	
                                				}
        						}		
        					}
        					else
        					{
    #ifdef DBG_MP3_HEADER_STREAM
            						printf("syncLag=%d,length=%d\n",syncLag,length);	
    #endif
            						bitrate=0;	
        					}
        				}		
        			}	
        		}
        	}		
        }
        
        if(hitSyncWord==0) //shift
        {
            Header=Header<<8;  
            Header=Header|(((unsigned int)(*stream)<<24)>>24);
            stream++;
            length--;
        }
    }
    
    #ifdef DBG_PRE_PARSE_MP3    
    printf("bitrate =%d,layer=%d,freq=%d \n",bitrate,layerNo,freqs);
    #endif    
    
    if( hitSyncWord == 1 )
    {
    	pHeaderInform->bitrate          = bitrate;
    	pHeaderInform->nextHeaderPtr    = stream;
    }	
    else
    {
    	pHeaderInform->bitrate          = 0;
    	pHeaderInform->nextHeaderPtr    = 0;
    }
}

// **************************************************************************************** //
static UINT32 ParseMP3BitRateFromAudioStream( VBR_MP3_FRAME_TYPE enType, char* pBuf, UINT32 uiLen )
{
    if( !pBuf || uiLen == 0 )
        return 0;

    MP3INFORM HeaderInform;
    HeaderInform.nextHeaderPtr = pBuf;
    
    if( enType == VBR_MP3_PARSE_FIRST_FRAME )
    {   
        GetBitRateInform( &HeaderInform, uiLen );
        return HeaderInform.bitrate;
    }
    else if( enType == VBR_MP3_PARSE_ALL_FRAME )
    {
        int     lastpBuf        = (int)pBuf + uiLen;
        int     sumBitRate      = 0;
        UINT32  uiBitRateCount  = 0;

        GetBitRateInform( &HeaderInform, uiLen );
        
        while( HeaderInform.bitrate != 0 )
        {
            sumBitRate += HeaderInform.bitrate;
            uiBitRateCount++;
            int lengthRemain = lastpBuf - (UINT32)(HeaderInform.nextHeaderPtr);
            GetBitRateInform( &HeaderInform, lengthRemain );
        }

    #ifdef DBG_PRE_PARSE_MP3
        printf( "average bitrate of LBA %d\n", ( uiBitRateCount > 0 ) ? ( sumBitRate / uiBitRateCount ) : 0 );
    #endif    
        return ( uiBitRateCount > 0 ) ? ( sumBitRate / uiBitRateCount ) : 0;    
    }
    
    return 0;
}

// **************************************************************************************** //
UINT32 PreParseMP3BitRate( VBR_MP3_LBA_TYPE enType, UINT32 uiParam, UINT32 uiLba, UINT32 uiLen )
{
    int     i           = 0;
    UINT32  uiLbaOffset = 0;
    UINT32  uiBitRate   = 0;
    UINT32  uiCount     = 0;
    UINT32  uiLbaCount  = 0;
    UINT32  uiStart     = uiLba;
        
    switch( enType )
    {
    case VBR_MP3_INTERVAL_N_LBA:
        uiLbaCount  = uiLen;
        uiLbaOffset = uiParam;
        break;
        
    case VBR_MP3_FIRST_N_LBA:
        uiLbaCount  = uiParam > uiLen ? uiLen : uiParam;
        uiLbaOffset = 1;
        break;

    case VBR_MP3_CENTER_N_LBA:  // 2004/08/10 yltseng
    {
        UINT32 uiTmp = ( uiLen + uiParam ) >> 1;
        uiLbaCount  = uiParam > uiTmp ? uiTmp : uiParam;
        uiLbaOffset = 1;
        uiStart     = uiLba + ( ( uiLen - uiParam ) > 1 );
    }
        break;
        
    case VBR_MP3_N_LBA:
        uiLbaCount  = uiLen;
        uiLbaOffset = uiLen / uiParam;
        break;
    }
  
    while( i < (int) uiLbaCount )
    {
        if( ran_read( pwb, l2msf( ( uiStart + i ) ), 2048 ) == ATAPI_OK )
        {
            UINT32 uiCurLbaBitRate = ParseMP3BitRateFromAudioStream( VBR_MP3_PARSE_FIRST_FRAME, pwb, 2048 );    // 2004/12/17 yltseng
            if( uiCurLbaBitRate )
            {
                uiBitRate += uiCurLbaBitRate;
                uiCount++;
            }
        }

        i += uiLbaOffset;
    }
    
    #ifdef DBG_PRE_PARSE_MP3
    printf( "average bitrate of MP3 file %d\n", ( uiCount > 0 ) ? ( uiBitRate / uiCount ) : 0 );
    #endif

    return ( uiCount > 0 ) ? ( uiBitRate / uiCount ) : 0;
}

// **************************************************************************************** //
#else

UINT32 PreParseMP3BitRate( VBR_MP3_LBA_TYPE enType, UINT32 uiParam, UINT32 uiLba, UINT32 uiLen ) 
{ enType = enType; uiParam = uiParam; uiLba = uiLba, uiLen = uiLen; return 0; }

#endif

// **************************************************************************************** //
