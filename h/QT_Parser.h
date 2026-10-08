#ifndef QT_PARSER_H
#define QT_PARSER_H

#include "memmap0.h"
#include "QT_definition.h"
#include "auddrv.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
//	API Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////
int 	is_QT_file(UINT32 msf,UINT32 len, UINT32 bufsize);
int		QT_reset_parser(UINT32 msf,UINT32 len);

int		QT_DispatchMemory(UINT32 config_mode, UINT32 uPreparseTableMemorySize);

int		QT_PreParse(BYTE *srcptr, UINT32 bufsize);
int		QT_InitializeTableCache(void);
void	CalculateChunkSize(int media_type);
UINT32	QueryEntry(UINT32 table_code,UINT32 entry_index,UINT32 *value);

//int		GetSamplePTS(UINT32 uSampleNum,UINT32 *pResultPTS,int iMediaType);
//int		GetSampleFileOffset(UINT32 uSampleNum,UINT32 *pResult,int iMediaType);
int		GetSampleChunkPosition(UINT32 uSampleNum,UINT32 *pResultPosition,int iMediaType);
//int		GetChunkSampleInfo(int iChunkNum,UINT32 *pResultCount,int iMediaType);
int		GetChunkSize(int iChunkNum,UINT32 *pResultSize,int iMediaType);
int		GenerateSyncEntryTable(int iMediaType);
int		CalculateCorrespondSyncEntriesTable(int iMediaType);

int		FillTable(UINT32 uTableCode,UINT32 uStartEntryIndex);
int		GetSTSCEntrySampleRange(int iEntryNum,UINT32 *pResultRange,int iMediaType);

int		SkipBitstream(UINT32 iByteCount);
//int		SkipBitstream(int iByteCount);

int 	RefillFileBuffer(void);
int 	GetField_Return(int iByteCount,UINT32 *pResult);
int 	GetField_Print(int iByteCount,char *pTitle,int iFormat);

int 	SkipAtom(void);
int 	ParseAtom(void);
void	FlushStack(void);
//int		SearchCorrespondingSyncSample(UINT32 uSamplePTS,UINT32 *pResultSample,int iMediaType);
int		CalculateSyncEntryTable(int iScaling,int iMediaType);

inline
void	printTAB(int iNum);

inline
int		IsInBetween(UINT32 uValue,UINT32 uLowBound,UINT32 uHighBound);
////////////////////////////////////////////////////////////////////////////////////////////////////////

//UINT32 SAMPLE_TABLE_BUFFER_SIZE;


////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Defines
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BUFFER_SIZE_UNIT 4  		//on 8202, memory map size uint is byte

#define VIDEO_STTSTABLE_START   SAMPLE_TABLE_BUFFER_START
#define VIDEO_STTSTABLE_SIZE    MAX_STTS_ENTRIES*2*BUFFER_SIZE_UNIT
#define VIDEO_STTSTABLE_END     VIDEO_STTSTABLE_START + VIDEO_STTSTABLE_SIZE

#define VIDEO_STSSTABLE_START   VIDEO_STTSTABLE_END
#define VIDEO_STSSTABLE_SIZE    MAX_STSS_ENTRIES*1*BUFFER_SIZE_UNIT
#define VIDEO_STSSTABLE_END     VIDEO_STSSTABLE_START + VIDEO_STSSTABLE_SIZE

#define VIDEO_STSCTABLE_START   VIDEO_STSSTABLE_END
#define VIDEO_STSCTABLE_SIZE    MAX_STSC_ENTRIES*3*BUFFER_SIZE_UNIT
#define VIDEO_STSCTABLE_END     VIDEO_STSCTABLE_START + VIDEO_STSCTABLE_SIZE

#define VIDEO_STSZTABLE_START   VIDEO_STSCTABLE_END
#define VIDEO_STSZTABLE_SIZE    MAX_STSZ_ENTRIES*1*BUFFER_SIZE_UNIT
#define VIDEO_STSZTABLE_END     VIDEO_STSZTABLE_START + VIDEO_STSZTABLE_SIZE

#define VIDEO_STCOTABLE_START   VIDEO_STSZTABLE_END
#define VIDEO_STCOTABLE_SIZE    MAX_STCO_ENTRIES*1*BUFFER_SIZE_UNIT
#define VIDEO_STCOTABLE_END     VIDEO_STCOTABLE_START + VIDEO_STCOTABLE_SIZE

#define SOUND_STTSTABLE_START   VIDEO_STCOTABLE_END
#define SOUND_STTSTABLE_SIZE    MAX_STTS_ENTRIES*2*BUFFER_SIZE_UNIT
#define SOUND_STTSTABLE_END     SOUND_STTSTABLE_START + SOUND_STTSTABLE_SIZE

#define SOUND_STSSTABLE_START   SOUND_STTSTABLE_END
#define SOUND_STSSTABLE_SIZE    MAX_STSS_ENTRIES*1*BUFFER_SIZE_UNIT
#define SOUND_STSSTABLE_END     SOUND_STSSTABLE_START + SOUND_STSSTABLE_SIZE

#define SOUND_STSCTABLE_START   SOUND_STSSTABLE_END
#define SOUND_STSCTABLE_SIZE    MAX_STSC_ENTRIES*3*BUFFER_SIZE_UNIT
#define SOUND_STSCTABLE_END     SOUND_STSCTABLE_START + SOUND_STSCTABLE_SIZE

#define SOUND_STSZTABLE_START   SOUND_STSCTABLE_END
#define SOUND_STSZTABLE_SIZE    MAX_STSZ_ENTRIES*1*BUFFER_SIZE_UNIT
#define SOUND_STSZTABLE_END     SOUND_STSZTABLE_START + SOUND_STSZTABLE_SIZE

#define SOUND_STCOTABLE_START   SOUND_STSZTABLE_END
#define SOUND_STCOTABLE_SIZE    MAX_STCO_ENTRIES*1*BUFFER_SIZE_UNIT
#define SOUND_STCOTABLE_END     SOUND_STCOTABLE_START + SOUND_STCOTABLE_SIZE


//////////////////////////////////////////////////////////////////////////
// memory config    //reference avi configuration
//////////////////////////////////////////////////////////////////////////
//#define	QTFILEBUFFERSTART	(SDRAM_BASE_UNCACHED + ((A_FILE_BUF_YA) << 10))
#define	QTFILEBUFFERSTART	(SDRAM_BASE_UNCACHED + (NERO_DIGITAL_MEMORY_YA) * 1024)
#define QTFILEBUFFERSIZE	QT_FILE_BUFFER_SIZE
#define QTFILEBUFFEREND		(QTFILEBUFFERSTART + QTFILEBUFFERSIZE)

//#define SAMPLE_TABLE_BUFFER_START   (QTFILEBUFFEREND + 1024)

#define CHUNKMAP_START              SOUND_STCOTABLE_END
#define CHUNKMAP_SIZE               MAX_CHUNKSIZE_ENTRIES*1*BUFFER_SIZE_UNIT
#define CHUNKMAP_END                CHUNKMAP_START + CHUNKMAP_SIZE
#define VIDEO_SYNCENTRIES_START     CHUNKMAP_END
#define VIDEO_SYNCENTRIES_SIZE      MAX_SYNCENTRY_ENTRIES*4*BUFFER_SIZE_UNIT
#define VIDEO_SYNCENTRIES_END       VIDEO_SYNCENTRIES_SIZE + VIDEO_SYNCENTRIES_SIZE
#define SOUND_SYNCENTRIES_START     VIDEO_SYNCENTRIES_END
#define SOUND_SYNCENTRIES_SIZE      MAX_SYNCENTRY_ENTRIES*4*BUFFER_SIZE_UNIT
#define SOUND_SYNCENTRIES_END       SOUND_SYNCENTRIES_START + SOUND_SYNCENTRIES_SIZE
////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
