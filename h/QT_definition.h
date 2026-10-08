#ifndef QT_DEFINITION_H
#define QT_DEFINITION_H

#include "stdlib.h"
#include "global.h" //for some typedef
#include "atapi_if.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Defines
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define FLAT_SWITCH
//message printing controls
//#define QT_PRINT_PARSE_ATOM_TYPE
//#define QT_PARSE_PRINT_TABLE
#define QT_PRINT_CHUNK_MAP
#define QT_PRINT_SYNC_ENTRY
#define QT_PRINT_MOVIE_INFO
#define QT_PRINT_MOVIE_STATUS

//most memory segmentation fault comes from these restrictions.
//these table restrictions should be modified to accomodate big files.
#define MAX_TRACK_NUM                   10
#define MAX_SOUND_TRACK			2
#define MAX_VIDEO_SAMPLE_DESCRIPTION    1
#define MAX_SOUND_SAMPLE_DESCRIPTION    1
#define MAX_SUBP_SAMPLE_DESCRIPTION     1
#define MAX_SUBT_SAMPLE_DESCRIPTION     1

#define MAX_UNRECOGNIZED_ATOM_ALLOWED   100
#define MAX_STTS_ENTRIES                10
#define MAX_STSS_ENTRIES                10
#define MAX_STSC_ENTRIES                10
#define MAX_STSZ_ENTRIES                10
#define MAX_STCO_ENTRIES                10
#define MAX_CHPL_ENTRIES                256

#define MAX_CHUNKSIZE_ENTRIES           500
#define MAX_SYNCENTRY_ENTRIES           500
#define MAX_ENTRY_NUMBER                    150

#define WORKING_BUFFER_SIZE             10
//UINT32 QT_FILE_BUFFER_SIZE = 0;
#define QT_FILE_BUFFER_SIZE    12*1024   //since ran_read simulates CD reading behavior
                                        //it reads multiples of 2048 bytes at a time, so
                                        //buffer size should be at least 2048.
//#define MAX_PRINTING_USER_DATA          150
#define MAX_NESTED_LEVEL                10    //maximum nested level for stack size restriction
#define MAX_ERROR_LIMIT                 10

typedef int (*ifuncQTP)(void);//(QTPARSER *);

#define  true   1
#define  false  0

#define TABUFSIZE       16  //table buffer infomation entries
#define STTSTABLE       0x0
#define STSSTABLE       0x1 //0001
#define STSCTABLE       0x2 //0010
#define STSZTABLE       0x3 //0011
#define STCOTABLE       0x4 //0100
#define VIDEO_TABLE     0x0
#define SOUND_TABLE     0x10

//Video
#define VIDEO_STTSTABLE 0x00 //0000
#define VIDEO_STSSTABLE 0x01 //0001
#define VIDEO_STSCTABLE 0x02 //0010
#define VIDEO_STSZTABLE 0x03 //0011
#define VIDEO_STCOTABLE 0x04 //0100
//Sound
#define SOUND_STTSTABLE 0x10
#define SOUND_STSSTABLE 0x11
#define SOUND_STSCTABLE 0x12
#define SOUND_STSZTABLE 0x13
#define SOUND_STCOTABLE 0x14
//SubP
#define SUBP_STTSTABLE 0x20
#define SUBP_STSSTABLE 0x21
#define SUBP_STSCTABLE 0x22
#define SUBP_STSZTABLE 0x23
#define SUBP_STCOTABLE 0x24
//SubT
#define SUBT_STTSTABLE 0x30
#define SUBT_STSSTABLE 0x31
#define SUBT_STSCTABLE 0x32
#define SUBT_STSZTABLE 0x33
#define SUBT_STCOTABLE 0x34

#define VIDEO_STTSTABLE_EntrySize	8
#define VIDEO_STSSTABLE_EntrySize	4
#define VIDEO_STSCTABLE_EntrySize	12
#define VIDEO_STSZTABLE_EntrySize	4
#define VIDEO_STCOTABLE_EntrySize	4

#define SOUND_STTSTABLE_EntrySize	8
#define SOUND_STSSTABLE_EntrySize	4
#define SOUND_STSCTABLE_EntrySize	12
#define SOUND_STSZTABLE_EntrySize	4
#define SOUND_STCOTABLE_EntrySize	4
#define ND_CHPLTABLE_EntrySize         4

#define IS_QT_VIDEO			0x1
#define IS_QT_SOUND			0x2
#define IS_QT_SUBPICTURE	        0x3
#define IS_QT_SUBTITLE		        0x4
#define IS_DROP				0x5
#define IS_END				0x6
#define IS_QT_UNKNOWN		0xF

#define	HAS_VIDEO_TRACK                     1
#define HAS_MORE_THAN_ONE_VIDEO_TRACK       1<<16
#define HAS_SOUND_TRACK                     1<<1
#define HAS_MORE_THAN_ONE_SOUND_TRACK       1<<17
#define HAS_STBL_FOR_VIDEO_TRACK            1<<2
#define HAS_STSD_FOR_VIDEO_TRACK            1<<3
#define HAS_STTS_FOR_VIDEO_TRACK            1<<4
#define HAS_STSZ_FOR_VIDEO_TRACK            1<<5
#define HAS_STSC_FOR_VIDEO_TRACK            1<<6
#define HAS_STCO_FOR_VIDEO_TRACK            1<<7
#define HAS_STSS_FOR_VIDEO_TRACK            1<<18
#define HAS_STBL_FOR_SOUND_TRACK            1<<8
#define HAS_STSD_FOR_SOUND_TRACK            1<<9
#define HAS_STTS_FOR_SOUND_TRACK            1<<10
#define HAS_STSZ_FOR_SOUND_TRACK            1<<11
#define HAS_STSC_FOR_SOUND_TRACK            1<<12
#define HAS_STCO_FOR_SOUND_TRACK            1<<13
#define HAS_STSS_FOR_SOUND_TRACK            1<<19
#define CONSTANT_VIDEO_FRAME_RATE           1<<20
#define VIDEO_IS_SELF_CONTAINED                 1<<21
#define SOUND_IS_SELF_CONTAINED                1<<22
#define HAS_UNKNOWN_TRACKS			     1<<23	// Unknow tracks does not include 'sdsm' & 'odsm'
#define HAS_SUBP_TRACK                                  1<<24
#define HAS_SUBT_TRACK                                  1<<25

#define HAS_STBL_TRACK            1
#define HAS_STSD_TRACK            1<<1
#define HAS_STTS_TRACK            1<<2
#define HAS_STSZ_TRACK            1<<3
#define HAS_STSC_TRACK            1<<4
#define HAS_STCO_TRACK            1<<5
#define HAS_STSS_TRACK            1<<6
////////////////////////////////////////////////////////////////////////////////////////////////////////



typedef struct
{
    UINT32  uDuration;
    UINT32  uTimeScale;
} MovieInfo;

typedef struct
{
    //UINT32  uEntrySize;     //size of one entry in bytes. BYTE is enough though.
    UINT32  uBufferredEntryCount; //keep this value configurable by not using #define makes us able to dispatch memory dynamically
    //now we know we should allocate uEntrySize*uBufferredEntryCount to each table buffer
    UINT32  uStartEntry;
    UINT32  uValidEntryCount;
    UINT32  uTotalEntryCount;
} TabufInfo;    //table buffer information

typedef struct
{
    UINT32  uWidth;
    UINT32  uHeight;
    char    sFourCC[4]; //stored in string fashion,maybe transform to UINT32 is better.
} VideoSampleDescription;

typedef struct
{
    UINT32  uNumChannel;
    UINT32  uSampleRate;
    UINT32  uSampleSize;

    UINT32  uSamplesPerPacket;
    UINT32  uBytesPerPacket;
    UINT32  uBytesPerFrame;
    UINT32  uBytesPerSample;
    char    sFourCC[4];
} SoundSampleDescription;

typedef struct
{
    UINT32  uSampleCount;
    UINT32  uSampleDuration;
} STTSEntry;

typedef struct
{
    UINT32  uFirstChunk;
    UINT32  uSamplePerChunk;
    UINT32  uSampleDescriptionID;
} STSCEntry;

typedef struct
{
    UINT32  uSamplePTS;
    UINT32  uSampleFileOffset;
} SyncEntry;    //randon accessible sync point

typedef struct
{
    UINT32 uEntryCount;
    SyncEntry *pEntryTable;
} SyncEntryTable;

typedef struct
{
    UINT32  uFixedSampleSize;
/////////////////////////////////////////////////////////////////////////
    STTSEntry *pSTTSTable;
    int     iSTTSEntryCount;
    UINT32  uSTTSTable_FileOffset;
    UINT32  uSTTSCachePTS;          //for use of GetSamplePTS, stores the PTS of uSTTSCacheFrameCount,which is
                                    //the accumulated frame count before uSTTSCacheEntry. Direct usage or modification
                                    //of these cached variable is not recommended.
    UINT32  uSTTSCacheSampleNum;    //for use of GetSamplePTS, stores the frame number at presentation time
                                    //uSTTSCachePTS, which is the accumulated time before uSTTSCacheEntry
    UINT32  uSTTSCacheEntry;        //for use of GetSamplePTS, represent the next entry to accumulate
/////////////////////////////////////////////////////////////////////////
    UINT32  *pSTSSTable;
    int     iSTSSEntryCount;        //iSTSSEntryCount == 0 implies that every sample is sync-able!
    UINT32  uSTSSTable_FileOffset;
/////////////////////////////////////////////////////////////////////////
    STSCEntry *pSTSCTable;
    int     iSTSCEntryCount;
    UINT32  uSTSCTable_FileOffset;
    UINT32  uSTSCCacheSampleRangeHigh;  //for use of GetSamplePTS, stores the PTS of uSTTSCacheFrameCount,which is
                                        //the accumulated frame count before uSTTSCacheEntry
    UINT32  uSTSCCacheSampleRangeLow;   //for use of GetSamplePTS, stores the frame number at presentation time
                                        //uSTTSCachePTS, which is the accumulated time before uSTTSCacheEntry
    UINT32  uSTSCCacheEntry;            //for use of GetSamplePTS, represent the next entry to accumulate
/////////////////////////////////////////////////////////////////////////
    UINT32  *pSTSZTable;
    int     iSTSZEntryCount;
    UINT32  uSTSZTable_FileOffset;
/////////////////////////////////////////////////////////////////////////
    UINT32  *pSTCOTable;
    int     iSTCOEntryCount;			//this is total chunk number as well
    UINT32  uSTCOTable_FileOffset;
/////////////////////////////////////////////////////////////////////////
    UINT32  *uChunkSizeTable;
    UINT32  uChunkSizeTableStartEntry;
    UINT32  uChunkSizeTableValidEntryCount;
    /*maybe i should interleave chunk size table with chunk offset table
    to improves memory access locality.*/
} SampleTable;

typedef struct
{
    UINT32 uTrackID;
    UINT32 uChunkOffset;
    UINT32 uFinishCheck;
}ChunkListInfo;

typedef struct
{
    UINT32 uEntryCnt; //Entry Count
    TabufInfo tCHPLTableInfo;
    UINT64 uMediaTime[256]; //MAX_CHPL_ENTRYCNT
    UINT32 uVersion;
}ChapterListInfo;

typedef struct
{
    char cSubTDispData[100];    
} SubTDispData;

typedef struct
{
    UINT32  uStartTime;
    UINT32  uEndTime;    
} DisplayInfo;

typedef struct
{
    DisplayInfo dDisplayInfo[100];    
} SubTDisplayInfo;

typedef struct
{
    UINT32  uStartTime;
    UINT32  uDuration;
    UINT32  uTimeScale;
    VideoSampleDescription aVideoSampleDescription[MAX_VIDEO_SAMPLE_DESCRIPTION];
    SampleTable stSampleTable;
    BYTE    bFixedFPS;  //not implemented yet.if fixed frame rate,stores fps.if not,0. (what about fraction like 29.997?)
    UINT32	uMediaRate;
    TabufInfo tVideoTableInfo[5]; // 0: Video STTS // 1: Video STSS // 2: Video STSC // 3: Video STSZ // 4: Video STCO
    UINT32 uCurParseIndex[MAX_ENTRY_NUMBER];
    UINT32 uPrevParseIndex[MAX_ENTRY_NUMBER];
} VideoInfo;

typedef struct
{
    BYTE    uCBR;
    UINT32  uStartTime;
    UINT32  uDuration;
    UINT32  uTimeScale;
    SoundSampleDescription aSoundSampleDescription[MAX_SOUND_SAMPLE_DESCRIPTION];
    SampleTable stSampleTable;
    UINT32	uMediaRate;
    UINT32	uTrackNumber;
    TabufInfo tSoundTableInfo[5]; // 0: Sound STTS // 1: Sound STSS // 2: Sound STSC // 3: Sound STSZ // 4: Sound STCO
    UINT32 uCurParseIndex[MAX_ENTRY_NUMBER];
    UINT32 uPrevParseIndex[MAX_ENTRY_NUMBER];
} SoundInfo;

//For Sub-Picture -------------------------------
typedef struct
{
    UINT8 reserved;
    UINT8 Y;
    UINT8 U;
    UINT8 V;
}PalleteData;

typedef struct
{
    UINT32                            uWidth;
    UINT32                            uHeight;
    UINT32  				uStartTime;
    UINT32  				uDuration;
    UINT32  				uTimeScale;
    SampleTable 			stSampleTable;
    UINT32				uMediaRate;
    UINT32				uTrackNumber;
    char    uSubpBelCountry[3] ;  //lyc add 2005-12-22,for subp language name  maybe subt or audio language name can be shown also;     
    TabufInfo tSubPTableInfo[5]; // 0: Sound STTS // 1: Sound STSS // 2: Sound STSC // 3: Sound STSZ // 4: Sound STCO
    PalleteData pPalleteTable[16]; //16 Entries
    UINT32 uCurParseIndex[MAX_ENTRY_NUMBER];
    UINT32 uPrevParseIndex[MAX_ENTRY_NUMBER];
} SubPInfo;

//For Sub-Title ---------------------------------
typedef struct
{
    UINT32  				uStartTime;
    UINT32  				uDuration;
    UINT32  				uTimeScale;
   SampleTable 			stSampleTable;
    UINT32				uMediaRate;
    UINT32				uTrackNumber;
   // char    uSubpBelCountry[3] ;  //lyc add 2005-12-22,for subp language name  maybe subt or audio language name can be shown also;
    TabufInfo tSubTTableInfo[5]; // 0: Sound STTS // 1: Sound STSS // 2: Sound STSC // 3: Sound STSZ // 4: Sound STCO
    UINT32 uCurParseIndex[MAX_ENTRY_NUMBER];
    UINT32 uPrevParseIndex[MAX_ENTRY_NUMBER];
} SubTInfo;

typedef struct
{
	// others
    char    uSubpBelCountry[3]  ; //lyc add 2005-12-22,for subp language name  maybe subt or audio language name can be shown also;
// Common
    UINT32  uStartTime;
    UINT32  uDuration;
    UINT32  uTimeScale;
    char    sFourCC[4];
    UINT32	uMediaRate;
    UINT32	uTrackNumber;
    SampleTable	stSampleTable;
    UINT32	track_type;
    UINT32 uMovieStatus;
	
// Video
    UINT32  uWidth;
    UINT32  uHeight;
    BYTE    bFixedFPS;  //not implemented yet.if fixed frame rate,stores fps.if not,0. (what about fraction like 29.997?)

// Sound
    UINT32  uNumChannel;
    UINT32  uSampleRate;
    UINT32  uSampleSize;
    UINT32  uSamplesPerPacket;
    UINT32  uBytesPerPacket;
    UINT32  uBytesPerFrame;
    UINT32  uBytesPerSample;
    BYTE  	uCBR;
    TabufInfo tTableInfo[5]; // 0: Sound STTS // 1: Sound STSS // 2: Sound STSC // 3: Sound STSZ // 4: Sound STCO
    PalleteData pPalleteTable[16]; //16 Entries
    UINT32 uSubpWidth;
    UINT32 uSubpHeight;
} CommonTrakInfo;

typedef struct
{
    UINT32  uSize;
    char    sType[4];
    UINT32	uLeftToParse;
    //uLeftToParse stores the progress of atom parsing
    UINT32  uData;	//can store single data field.
					/*This is currently for track atom to store track uID.
					  Since we have to know that which track we are parsing.*/
} ATOM;

typedef struct
{
    //FILE	*stream;     //replaced by disc_file stream
    UINT32 	uQTTotalFileSize;
    UINT32 	uQTParsedByte;
    UINT32	uQTMdatSize;
    ATOM    aParsingStack[MAX_NESTED_LEVEL]; //may be freed to after parsing since it's not used then
    int     iStackPtr;  //storing nested level of the stack while parsing. when empty,
                        //it takes the value -1
} QTPARSER;

typedef struct
{
    UINT32  uID;
    char    sType[4];   	//note!! this never stores "trak" since we knew that already.
                        	//instead, we store whether it's "vide" or "soun" or else
    char    sFouCC[4];  	//not used currently, video fcc and audio fcc are stored in g_stVideoProperties and g_stSoundProperties seperately.
    UINT32  uDuration;
    UINT32  uMediaDuration;
    UINT32  uMediaTimeScale;
    UINT32  uWidth;
    UINT32  uHeight;
    UINT32	uMediaRate;
//    char	sTrackName[10];	// used to store Nero Digital language information
} TrackInfo;


enum {
    SUCCESSFUL                  =1  ,
    ERROR_READING_FILE          =2  ,
    TOO_MANY_UNRECOGNIZED_ATOM  =3  ,    //set threshold MAX_UNRECOGNIZED_ATOM_ALLOWED in QT_definition
    REQUEST_EXCEEDS_FILE_SIZE       ,    //usaully happens when the file is not a QT file or implicit parse error
    INVALID_NEGATIVE_PARAMETER      ,
    ATOM_SIZE_EXCEEDS_FILE_SIZE     ,    //usually happens when not QT file
    ATOM_SIZE_EQUALS_ZERO_ILLEGALLY ,
    ATOM_SIZE_IS_64BIT              ,    //should become supportted in a short time
    CURRENTLY_UNSUPPORT_FEATURE     ,
    NOT_REASONABLE_ATOM_STRUCTURE   ,    //some atom supposed to be in a track atom appears elsewhere
    INVALID_TABLE_REQUEST           ,    //invalid table value request, either a not existing table or too big entry number or table buffer does not work correctly
    INVALID_PARAMETER               ,    //passing invalid parameter into function
    NOT_VALID_INFOMATION            ,    //error table information, maybe caused by error bitstream, or malicious content.
    INVALID_FUNCTION_REQUEST        ,
    UNKNOWN_ERROR                   ,    //caused by unconsiderred situation or uncategorized error
    NOT_ENOUGH_BUFFER               ,
    NOT_ENOUGH_MEMORY               ,   //given memory size is too small when dispatching memory ourselve.
    ND_DRM_NOTALLOWED               ,   //DRM 
    NOT_SUPPORT_NERODIGITAL     , //
    INVALID_TRACK_TYPE              ,
    
};

typedef struct  {
    int (*do_sup)();                // 00~03

    UINT32  PTS_sup_new;            // 04~07
    UINT32  spd_pts;                // 08~0B next PTS
    UINT32  spd_pts_stop;           // 

    UINT32  svcd_sup_timecmd;       // 0C~0F (SVCD)

    UINT16  spd_decode_hdr_ptr;     // 10~11 SPD header for decoding
    UINT16  spd_decoded_hdr_ptr;    // 12~13 SPD header (decoded)
    UINT16  spd_dump_hdr_ptr;       // 14~15 SPD header for parsing

    UINT16  spd_dcsq_ptr;           // SPD DECODE pointer (sbv_fetch())
    UINT16  spd_dcsq_ptr_now;       // SPD DECODE pointer of current DCSQ
    UINT16  spd_dcsq_ptr_next;      // SPD DECODE pointer to next DCSQ 

    UINT16  sup_start;              // 
    UINT16  sup_dumpcnt;            // 
    UINT16  sup_writeptr;           //

    UINT16  sup_freespace;          // SPD buffer-free
    UINT16  sup_freespace_return;   // scheduled calculated return free-space of SPD
    UINT16  sup_freespace_return2;  // scheduled actual return free-space of SPD

    UINT16  supya;                  // sub-picture SDRAM buffer start row
    UINT16  supye;                  // sub-picture SDRAM buffer end row

    INT16   sup_offset_y;           // Display extra vertical offset

    UINT16  sup_tlx,                // Bitmap region size window
            sup_brx;                // 
    UINT16  sup_tly,                //
            sup_bry;                //

    UINT16  sup_cmd_addr;           // SPH hardware command address (DVD only)

    UINT16  sup_tlink,              // SPH bitmap top-field address
            sup_blink;              // SPH bitmap bottm-field address

    UINT8   sup_link_changed;
    UINT16  sup_empty;
    UINT16  sup_empty2;
    UINT16  sup_tlink_n, sup_blink_n;

    UINT16  sup_hl0_color;
    UINT16  sup_hl0_contr;

    UINT16  sup_hl_tlx[2];
    UINT16  sup_hl_brx[2];
    UINT16  sup_hl_tly[2];
    UINT16  sup_hl_bry[2];
#if 0
    UINT16  sup_hl0_tlx, sup_hl0_brx;
    UINT16  sup_hl0_tly, sup_hl0_bry;
    UINT16  sup_hl1_tlx, sup_hl1_brx;
    UINT16  sup_hl1_tly, sup_hl1_bry;
#endif

    // DVD
    UINT16  sup_pxcd;
    UINT16  sup_pxcd_len;
    INT8    sup_pxcd_offset;

    BYTE    sup_buf[4];
    BYTE    sup_buf_cnt;

    UINT16   sup_state;
}t_supvar;


#endif


