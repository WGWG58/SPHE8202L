#ifndef __ISO9660_H
#define __ISO9660_H

#include "types.h"

#ifndef	CDFS_FILEHANDLES
#define	CDFS_FILEHANDLES	2
#endif

#define	CDFS_FILE_OPENED	1
#define	CDFS_FILE_DIRECTORY	2

enum {
	ERROR_FILE_NOT_FOUND		= -100,
	ERROR_FILE_ENTRY_FULL		= -101,
	ERROR_FILE_ENTRY_INVALID	= -102,
	ERROR_FILE_PATH		= -103,
	ERROR_FILE_SUBPATH_TOO_LONG	= -105,
	ERROR_PARAMETER		= -2,
	ERROR_GENERIC			= -1
};

#if 0
typedef	struct
{
	BYTE		len_of_record	__attribute__ ((packed));
	BYTE		len_of_attr	__attribute__ ((packed));
	BYTE		location_le[4]	__attribute__ ((packed));
	BYTE		location_be[4]	__attribute__ ((packed));
	BYTE		length_le[4]	__attribute__ ((packed));
	BYTE		length_be[4]	__attribute__ ((packed));
	BYTE		time_stamp[7]	__attribute__ ((packed));
	BYTE		file_flag	__attribute__ ((packed));
	BYTE		file_unit_size	__attribute__ ((packed));
	BYTE		interleave_gap	__attribute__ ((packed));
	UINT16	volume_seq_le	__attribute__ ((packed));
	UINT16	volume_seq_be	__attribute__ ((packed));
	BYTE		len_of_filename	__attribute__ ((packed));
	BYTE		filename[2]	__attribute__ ((packed));
} CDDirRecord;

typedef	struct
{
	UINT32	extent;
	UINT32	length;
	UINT32	pos;
	BYTE		filestatus	__attribute__ ((packed));
	BYTE		fileflag	__attribute__ ((packed));
	BYTE		interleave_unit	__attribute__ ((packed));
	BYTE		interleave_gap	__attribute__ ((packed));
} CDFileHandle;
#else

typedef	struct
{
	BYTE		len_of_record;
	BYTE		len_of_attr;
	BYTE		location_le[4];
	BYTE		location_be[4];
	BYTE		length_le[4];
	BYTE		length_be[4];
	BYTE		time_stamp[7];
	BYTE		file_flag;
	BYTE		file_unit_size;
	BYTE		interleave_gap;
	UINT16	volume_seq_le;
	UINT16	volume_seq_be;
	BYTE		len_of_filename;
	BYTE		filename[31];
} CDDirRecord;

typedef	struct
{
	UINT32	extent;
	UINT32	length;
	UINT32	pos;
	BYTE		filestatus;
	BYTE		fileflag;
	BYTE		interleave_unit;
	BYTE		interleave_gap;
} CDFileHandle;
#endif


typedef struct
{
	UINT32        volumesize;
	UINT32	pathtable;
	
	UINT32	root_dir;
	UINT32	root_dir_length;
	UINT32	current_dir;
	UINT32	current_dir_length;
	
	CDFileHandle	files[CDFS_FILEHANDLES];
} CDVolume;


int     initFileSystem(void);

int	open_path(const char *path);
#define	open_file(path)	open_path(path)
#define	open_dir(path)	open_path(path)

int	close_file(int handle);

UINT32	get_file_msf(int handle);
UINT32	get_file_length(int handle);

int     read_file(void *buf, int size, int fh);
int     read_directory_record(CDDirRecord *buf, int fh);
int	pfeof(int fh);
int	pfmode(int fh);
int	pftell(int fh);

#endif

