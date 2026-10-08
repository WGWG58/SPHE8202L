#ifndef __AVI_TYPES_H
#define __AVI_TYPES_H

#include "types.h"

typedef UINT32	FOURCC;

// structure for avi stream table
typedef struct _strm_table
{
	BYTE	strm_num;
	UINT32	strm_offset;
} STRM_TABLE;

typedef	struct _cset
{
	UINT16	wCodePage				__attribute__ ((packed));
	UINT16	wCountryCode			__attribute__ ((packed));
	UINT16	wLanguageCode			__attribute__ ((packed));
	UINT16	wDialect				__attribute__ ((packed));
} CSET, *PCSET, TEXTINFO, *PTEXTINFO;

typedef struct _rect
{
    UINT32	left					__attribute__ ((packed));
    UINT32	top						__attribute__ ((packed));
    UINT32	right					__attribute__ ((packed));
    UINT32	bottom					__attribute__ ((packed));
} RECT, *PRECT;

typedef struct _colorrgb
{
	BYTE	bRed					__attribute__ ((packed));
	BYTE	bGreen					__attribute__ ((packed));
	BYTE	bBlue					__attribute__ ((packed));
} CLRRGB;

typedef struct tagPALETTEENTRY
{
	BYTE	peRed					__attribute__ ((packed));
	BYTE	peGreen					__attribute__ ((packed));
	BYTE	peBlue					__attribute__ ((packed));
	BYTE	peFlags					__attribute__ ((packed));
} PALETTEENTRY, *PPALETTEENTRY;

typedef struct
{
	BYTE	bFirstEntry				__attribute__ ((packed));		// first entry to change
	BYTE	bNumEntries				__attribute__ ((packed));		// # entries to change (0 if 256)
	UINT16	wFlags					__attribute__ ((packed));		// Mostly to preserve alignment...
	PALETTEENTRY	peNew[]			__attribute__ ((packed));		// New color specifications
} AVIPALCHANGE;

typedef struct _bitmapinfoheader
{
	UINT32	biSize					__attribute__ ((packed));
	INT32	biWidth					__attribute__ ((packed));
	INT32	biHeight				__attribute__ ((packed));
	UINT16	biPlanes				__attribute__ ((packed));
	UINT16	biBitCount				__attribute__ ((packed));
	UINT32	biCompression			__attribute__ ((packed));
	UINT32	biSizeImage				__attribute__ ((packed));
	INT32	biXPelsPerMeter			__attribute__ ((packed));
	INT32	biYPelsPerMeter			__attribute__ ((packed));
	UINT32	biClrUsed				__attribute__ ((packed));
	UINT32	biClrImportant			__attribute__ ((packed));
} BITMAPINFOHEADER;

typedef struct _supbipmapheader
{
	UINT16	wWidth					__attribute__ ((packed));
	UINT16	wHeight					__attribute__ ((packed));
	UINT16	wLeft					__attribute__ ((packed));
	UINT16	wTop					__attribute__ ((packed));
	UINT16	wRight					__attribute__ ((packed));
	UINT16	wBottom					__attribute__ ((packed));
	UINT16	wFoffset				__attribute__ ((packed));
	CLRRGB	CBackground				__attribute__ ((packed));
	CLRRGB	CPattern				__attribute__ ((packed));
	CLRRGB	CEmphasis1				__attribute__ ((packed));
	CLRRGB	CEmphasis2				__attribute__ ((packed));
} SUPBITMAPHEADER;

// main AVI header list
typedef struct _mainaviheader
{
	UINT32	dwMicroSecPerFrame		__attribute__ ((packed));		// frame display rate (or 0L)
	UINT32	dwMaxBytesPerSec		__attribute__ ((packed));		// max. transfer rate
	UINT32	dwPaddingGranularity	__attribute__ ((packed));
	UINT32	dwFlags					__attribute__ ((packed));
	UINT32	dwTotalFrames			__attribute__ ((packed));		// # frames in file
	UINT32	dwInitialFrames			__attribute__ ((packed));
	UINT32	dwStreams				__attribute__ ((packed));
	UINT32	dwSuggestedBufferSize	__attribute__ ((packed));
	UINT32	dwWidth					__attribute__ ((packed));
	UINT32	dwHeight				__attribute__ ((packed));
	UINT32	dwScale					__attribute__ ((packed));
	UINT32	dwRate					__attribute__ ((packed));
	UINT32	dwStart					__attribute__ ((packed));
	UINT32	dwlength				__attribute__ ((packed));
} MainAVIHeader, *PMainAVIHeader;

// stream header
typedef struct _avistreamheader
{
	FOURCC	fccType					__attribute__ ((packed));
	FOURCC	fccHandler				__attribute__ ((packed));
	UINT32	dwFlags					__attribute__ ((packed));
	UINT16	wPriority				__attribute__ ((packed));
	UINT16	wLanguage				__attribute__ ((packed));
	UINT32	dwInitialFrames			__attribute__ ((packed));
	UINT32	dwScale					__attribute__ ((packed));
	UINT32	dwRate					__attribute__ ((packed));		// dwRate / dwScale == samples/second
	UINT32	dwStart					__attribute__ ((packed));
	UINT32	dwLength				__attribute__ ((packed));
	UINT32	dwSuggestedBufferSize	__attribute__ ((packed));
	UINT32	dwQuality				__attribute__ ((packed));
	UINT32	dwSampleSize			__attribute__ ((packed));
	RECT	rcFrame					__attribute__ ((packed));
} AVIStreamHeader, *PAVIStreamHeader;

// idx1 structure
typedef	struct _aviindexentry
{
	UINT32	ckid					__attribute__ ((packed));
	UINT32	dwFlags					__attribute__ ((packed));
	UINT32	dwChunkOffset			__attribute__ ((packed));		// Position of chunk
	UINT32	dwChunkLength			__attribute__ ((packed));		// Length of chunk
} AVIINDEXENTRY, *PAVIINDEXENTRY;

// base index form 'indx'
typedef struct	_avioldindex
{
	FOURCC	fcc						__attribute__ ((packed));
	UINT32	cb						__attribute__ ((packed));
	UINT16	wLongsPerEntry			__attribute__ ((packed));		// must be sizeof(aIndex[0])/sizeof(DWORD)
	BYTE	bIndexSubType			__attribute__ ((packed));		// must be 0
	BYTE	bIndexType				__attribute__ ((packed));		// must be AVI_INDEX_OF_CHUNKS
	UINT32	nEntriesInUse			__attribute__ ((packed));		// index of first unused member in aIndex array
	UINT32	dwChunkID				__attribute__ ((packed));		// fcc of what is indexed
	UINT32	dwReserved[3]			__attribute__ ((packed));		// meaning differs for each index type/subtype. 0 if unused
	struct	_aviindex_entry {
		UINT32	asw;
	} aIndex[];
} AVIOLDINDEX, *PAVIOLDINDEX;

// AVI standard index chunk
typedef struct	_avistdindex_chunk
{
	FOURCC	fcc;				// 'ix##'
	UINT32	cb;
	UINT16	wLongsPerEntry;		// must be sizeof(aIndex[0])/sizeof(DWORD)
	BYTE	bIndexSubType;		// must be 0
	BYTE	bIndexType;			// must be AVI_INDEX_OF_CHUNKS
	UINT32	nEntriesInUse;		// index of first unused member in aIndex array
	UINT32	dwChunkID;			// '##dc' or '##db' or '##wb' etc..
	UINT64	qwBaseOffset;		// all dwOffsets in aIndex array are relative to this
	UINT32	dwReserved3;		// must be 0
	struct	_avistdindex_entry {
		UINT32	dwOffset;		// qwBaseOffset + this is absolute file offset
		UINT32	dwSize;			// bit 31 is set if tis is NOT a keyframe
	} aIndex[];
} AVISTDINDEX, *PAVISTDINDEX;

// AVI field index chunk
typedef struct	_avifieldindex_chunk
{
	FOURCC	fcc;				// 'ix##'
	UINT32	cb;
	UINT16	wLongsPerEntry;		// must be 3 (size of each entry in aIndex array)
	BYTE	bIndexSubType;		// AVI_INDEX_2FIELD
	BYTE	bIndexType;			// must be AVI_INDEX_OF_CHUNKS
	UINT32	nEntriesInUse;		//
	UINT32	dwChunkID;			// '##dc' or '##db'
	UINT64	qwBaseOffset;		// all dwOffsets in aIndex array are relative to this
	UINT32	dwReserved3;		// must be 0
	struct	_avifieldindex_entry {
		UINT32	dwOffset;		// qwBaseOffset + this is absolute file offset
		UINT32	dwSize;			// size of all fields (bit 31 set for NON-keyframes)
		UINT32	dwOffsetField2;	// offset to second field
	} aIndex[];
} AVIFIELDINDEX, *PAVIFIELDINDEX;

// AVI super index chunk
typedef struct	_avisuperindex_chunk
{
	FOURCC	fcc;				// 'indx'
	UINT32	cb;
	UINT16	wLongsPerEntry;		// must be 4 (size of each entry in aIndex array)
	BYTE	bIndexSubType;		// must be 0 or AVI_INDEX_2FIELD
	BYTE	bIndexType;			// must be AVI_INDEX_OFINDEXES
	UINT32	nEntriesInUse;		//
	UINT32	dwChunkID;			// '##dc' or '##db' or '##wb' etc..
	UINT32	dwReserved[3];		// must be 0
	struct	_avisuperindex_entry {
		UINT64	qwOffset;		// absolute file offset, offset is unused entry??
		UINT32	dwSize;			// size of index chunk at this offset
		UINT32	dwDuration;		// time span in stream ticks
		UINT32	dwOffsetField2;	// offset to second field
	} aIndex[];
} AVISUPERINDEX, *PAVISUPERINDEX;

typedef struct _avi_video_info
{
	BYTE	version_str[6];
	UINT16	width;
	UINT16	height;
} avi_video_info;

#endif	// __AVI_TYPES_H
