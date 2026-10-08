/*****************************************
**FILE : 
**    fsMP3TXT.h
**
**DESCRIPTION 
**  for fsMP3TXT.c
**
**Creator : zhaoyanhua 
**Date    : 2003-8-20 10:47
******************************************/
#ifndef  _FS_MP3TXT_H
#define  _FS_MP3TXT_H

#include "memmap0.h"

//MACRO definition
//------------------------------------------------------------
//for "WriteFlag" value
#define READ_MP3LRC_OK      0
#define READ_MP3LRC_ERROR   1


//for "FoundChinese" value
#define  FOUND_ASCII   0x01 //bit 0
#define  FOUND_GB2312 0x02//bit 1
#define  FOUND_BIG5   0x04//bit 2

//linrc change because after call setup menu,LRC display error 2005-11-3 17:20
#define MP3LRC_MEM_START     (SDRAM_BASE + (A_MP3LRC_MEM_YA)*1024)
#define MP3LRC_INFO_START     (SDRAM_BASE + (A_MP3LRC_INFO_YA) *1024)
#define MAX_LRC_BUF  2*1024
#define LYRICS_MAX  100
#define MAX_WORD   100

//for  "WriteFlag"
#define WRITE_OK    1//has written.
#define NOT_WRITE   0// to be write.

//wanghaoying move to fsGUI1.h, 2004-5-11 18:02
//for "MP3_Lyrics_Drawed" 
//#define  MP3_LYRICS_IN_DIR_AREA  1
//#define  DIR_LIST_IN_DIR_AREA        0


//for screen display
#define ONE_LINE_CHARS 18 //18 ASCII = 9 CHINESE
#define ITEM_START     1
#define ITEM_END       8
//clear rect
#define	FS_DIRLIST_YSTART				70              //dir string start-y
#define FS_FILELIST_YSTEP				16              //file(dir) list item height
#define LYRECT_XSIZE      145
#define LYRECT_XSTART     26
#define PER_PAGE  10
//----------------------------------------------------------

//variables definition
//----------------------------------------------------------
//for display 
UINT16 MP3TotalNo = 0;
UINT16 MP3PlayNo = 0;
BYTE   WriteFlag = NOT_WRITE;
int    ItemCurrent = 0;
UINT16  LineNo = 0;
BYTE     MP3_Lyrics_Drawed = 0;  
BYTE   OneScreenDrawLines = 0;
//if found BIG5 FONT£¬then not show
//only support GB2312_FONT
// 0: has no chinese.
// 1: GB2312_FONT
// 2: BIG5_FONT
BYTE FoundChinese = 0;
// for count time in polling.
UINT16   SecCounter = 0;//unit :s
BYTE     MSecCounter = 0; //unit: ms
   
//wanghaoying mark 2004-8-3 8:50, for same declare in fsGUI1.h
/*
typedef struct
{
	UINT16  xStart;
	UINT16  yStart;
	UINT16  xSize;
	UINT16  ySize;
} BTNAREA;*/


typedef struct
{   
    BYTE     title[50];//song title
    BYTE     artist[50];//singer
    UINT16   sec[LYRICS_MAX]; //second
    BYTE     song[LYRICS_MAX][MAX_WORD]; //Lyrics information
} LRCInfo;
  
LRCInfo *MP3LRCInfo =(LRCInfo *)MP3LRC_INFO_START;

BYTE *MP3LRCBuf = (BYTE *)MP3LRC_MEM_START;
//----------------------------------------------------------

//Function declaration
//----------------------------------------------------------
void DelExtraChars(BYTE *str, BYTE len);
UINT32 iso9660_seach_MP3txt_files(int MP3TrkNow);
UINT32 str2val(BYTE *str,UINT8 n);
void ParseMP3LRCFile(int MP3LrcFile);
void sort();
int SearchMatchTime();
void polling_10ms_show_MP3Lycris(void);
extern BYTE ran_read(UINT8*, UINT32, UINT32);
//BYTE DrawOneLine(int PlayNo, BYTE StartItem,int FontColor_Y,int FontColor_CRCB);
UINT16 DrawOneLine(int PlayNo, BYTE StartItem,int FontColor_Y,int FontColor_CRCB);
UINT16 AnalyseOneLine(BYTE str[]);
void ShowOneScreen();
void ShowLyricsWhileHL(void);
void  GetMP3Lyrics(void);
//----------------------------------------------------------
#endif// _FS_MP3TXT_H



