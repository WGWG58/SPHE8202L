#ifndef __NESINIT_H
#define	__NESINIT_H

#include "auddrv.h" //2004AUDDRV oliver 20041004 for using audio driver purpose
//#include "audif.h" 


#define NES_SOUND_PLAYBACK 	44

#if NES_SOUND_PLAYBACK==32
		#define SOUND_PLAYBACK_ID	1
		#define SPS_FOR_WAIT	  	320  		
		#define NES_DAC_SPEED		FS_32K
#else
 		//NES_SOUND_PLAYBACK==44
		#define SOUND_PLAYBACK_ID	2
		#define SPS_FOR_WAIT	  	441
		#define NES_DAC_SPEED		FS_44K
		
#endif


#define PIXEL_PER_OSDLINE  288


#if 0
//old driver
typedef struct  
{  
//video	
	BYTE	TVMode;	

//option
	BYTE	bRunOption;
	
//osd
	BYTE 	*pRegion0DataStart;
	BYTE 	*pRegion1DataStart;   
   UINT32	unRegion0Offset;
   UINT32	unRegion1Offset;   
	
//audio	
	BYTE 	*pPCMStart;
	BYTE 	*pPCMEnd;
	int 	PCMLen;     
	UINT32 	unVolume;     
	BYTE 	unVolumeMaxStep;     
	BYTE 	unVolumeCurStep;           	
	    
//game	
	BYTE 	*pNESFile;    
	BYTE 	bNESOK;
	
//IR key 
	BYTE	bBreakIrKey[8];	 

//end status
	int		iRtsStatus;   
	    
} S_HARDWARE;


//error code and break code define
#define BREAK_NES_BY_IR				0x0100
#define BREAK_NES_BY_GAMEPAD		0x0200
#define ERR_NES_FILE_HEADER			-1
#define ERR_NES_TR_NO_SUPPORT		-2
#define ERR_NES_4SCR_NO_SUPPORT		-3
#define ERR_NES_DECODE_NO_SUPPORT	-4
#define ERR_CPU_INST				-5

#else

//new driver
typedef struct  
{  

//stack point		
	UINT32	unProgramStack;
	
//video	
	BYTE 		TVMode;	

//option
	BYTE		bRunOption;
	
//osd
	BYTE 	*pRegion0DataStart;
	BYTE 	*pRegion1DataStart;   
   	UINT32	unRegion0Offset;
   	UINT32	unRegion1Offset;   
	
//audio	
	BYTE 	*pPCMStart;
	BYTE 	*pPCMEnd;
	int 	PCMLen;           	
	UINT32 	unVolume;     
	BYTE 	unVolumeMaxStep;     
	BYTE 	unVolumeCurStep;     
	
//game	
	BYTE 	*pNESFile;    
	BYTE 	bNesFlag;			//bit 0 	-> 1: use outside option
								//bit 1 	-> h/v
								//bit 2     -> split flag
								//bit 3,7	-> decode type				
	BYTE 	bNesPrgDataSize;	//bit7~5 	-> prog
								//bit4~0	-> data 
								
	BYTE    bSplitPos;
	
	UINT32	unMemoryLen;		//totally free spec for game rom
	
	//IR key 
	BYTE	bBreakIrKey[12];

	//Game PAD key 
	BYTE	bBreakGamePad[2];

#ifdef SUPPORT_IR_GAME
    //IR Control key
	BYTE	bControlIRKey[19];
#endif

	// vfd array address
	BYTE*	pVFDAddr;
	
//end status
	int		iRtsStatus;   
	
	UINT32 pVFDBufAddr;
	    
} S_HARDWARE;


enum
{ T_NULL, T_LA, T_LB, T_LC, T_LD, T_LF, T_LC2, T_C3, T_C1, T_M7 };
enum
{ T_H, T_V, T_HV0, T_HV1 };



//error code and break code define
#define BREAK_NES_BY_IR				0x0100
#define BREAK_NES_BY_GAMEPAD		0x0200
#define ERR_NES_FILE_HEADER			-1
#define ERR_NES_TR_NO_SUPPORT		-2
#define ERR_NES_4SCR_NO_SUPPORT		-3
#define ERR_NES_DECODE_NO_SUPPORT	-4
#define ERR_CPU_INST				-5
#define ERR_OLD_NES_FILE			-6


//NES_RUN_MODE      
#define NES_BREAK_A_START 	(1<<0)		// 0-> is A+B+start
#define NES_GAMEPAD_AB_SWAP (1<<2)
#define NES_DEBUG_ON		(1<<6)
#define NES_LIGHT_GUN_ON	(1<<7)

// lignt gun GPIO assignment
#define GPIO_CPAD_D1	3
#define GPIO_CPAD_GUN	36

#endif	//driver select

#endif
