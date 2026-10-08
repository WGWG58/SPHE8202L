#ifndef __FS_SHOW_H
#define __FS_SHOW_H

//fs_message_show.c
//*************************************************************
#ifdef SUPPORT_MP4
#define MP4_INI    1       
#define UNSUPPORT_MESSAGE   2
#define UNSUPPORT_FORMAT    3
#endif

#ifdef SUPPORT_QUICKTIME
#define UNSUPPORT_DRM 4
#endif //SUPPORT_QUICKTIME
//-------------------------------------
#if defined(SUPPORT_ID3)||defined(SUPPORT_OSDID3)//liweihua 2003-12-28
#include "memmap0.h"
#ifdef S16Mb_Mode_ID3      //2004-4-16 05:27’≈”ÓP
#define ID3_MEM_START     (SDRAM_BASE + (A_MP3ID3YA)*1024)
#else
#define ID3_MEM_START     (SDRAM_BASE + (A_SUPYA)*1024)
#endif
#define LYRICS_MAX 100
#define MAX_WORD   50
#define MAX_SN_LEN 30
#define ID3_V1     0x1
#define ID3_V2     0x2

typedef struct
{
    int s[LYRICS_MAX]; //second
    char song[LYRICS_MAX][MAX_WORD]; //50 isn't limited
} LYRICS;

typedef struct
{
    LYRICS l;
    int no;
    int play_no;
    int id3_exist; //0:no id3 ,1:exist id3 info
    char song[MAX_SN_LEN + 1]; //add str end:\0
    char artist[MAX_SN_LEN + 1];
} LYR;

typedef struct
{
    BYTE tag[3];
    BYTE song_title[30];
    BYTE artist[30];
    BYTE album[30];
    BYTE year[4];
    BYTE comment[30];
    BYTE genre;
} ID3_TAG;

#endif
//*****************************************************************
//linrc add "SUPPORT_MP3_ENCODER"2006-4-17 19:40
#if defined(SUPPORT_CD_RIPPING)||defined(SUPPORT_MP3_ENCODER)//qinhua add "SUPPORT_CD_RIPPING",060530
typedef enum
{
	NO_DEVICE = 1,
	USB_READY,
	USB_ERROR,
	USB_FULL,
	DEVICE_FULL,
	SD_MMC_READY,
	SD_MMC_ERROR,
	UNSUPPORT_DEVICE,
	DEVICE_WRITE_PROTECT,
	OPEN_FILE,
	CLOSE_FILE,
	REC_MESSAGE,	
//qinhua add for "SUPPORT_CD_RIPPING"
	RECODER_NOMARL,
	RECODER_2X,	
        FOLDER_ERROR,
        FILE_ERROR,
        DEVICE_READY,
        UNSUPPORTED_DEVICE,
        ERROR
 
} Message_type;

void Mp3_Encoder_message_show(Message_type message);
#endif

#endif

