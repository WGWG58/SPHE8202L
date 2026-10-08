#if !defined(_UDF_167_H)
#define _UDF_167_H
/*
* udf_167.h
*
* DESCRIPTION
*	Definitions from the ECMA 167 standard.
*	http://www.ecma.ch/
*
*	These abbreviations are used to keep the symbols short:
*		Alloc	Allocation
*		App	Application
*		Attr	Attribute
*		Char	Characters
*		Desc	Descriptor
*		Descs	Descriptors
*		Ext	Extent
*		Ident	Identifier
*		Imp	Implementation
*		Lvl	Level
*		Max	Maximum
*		Num	Number
*		Ptr	Pointer
*		Seq	Sequence
*		Std	Standard
*		Struct	Structure
*		Vol	Volume
*	The symbols are otherwise identical to the standard, and the
*	sections of the standard to refer to are indicated.
*
* CONTACTS
*	E-mail regarding any portion of the Linux UDF file system should be
*	directed to the development team mailing list (run by majordomo):
*		linux_udf@hootie.lvld.hp.com
*
* COPYRIGHT
*	This file is distributed under the terms of the GNU General Public
*	License (GPL). Copies of the GPL can be obtained from:
*		ftp://prep.ai.mit.edu/pub/gnu/GPL
*	Each contributing author retains all rights to their own work.
*
* HISTORY
*	July 12, 1997 - Andrew E. Mileski
*	Adapted from the ECMA-167 standard.
*
* 10/2/98 dgb	Adaptation
* 10/4/98 	Changes by HJA Sandkuyl
* 10/7/98	Changed FILE_EXISTENCE to FILE_HIDDEN, per UDF 2.0 spec
* 11/26/98	Modifed some entries for UDF 1.5/2.0
* 11/26/98 bf  Fixed typos, non-linux types, more structures
* 12/5/98 dgb  Adjusted structure and content of include files.
*/

#include "types.h"
typedef UINT8	dstring;

/* make sure all structures are packed! */

/* CS0 Charspec (ECMA 167 1/7.2.1) */
typedef struct {
	UINT8 charSetType			__attribute__ ((packed));
	UINT8 charSetInfo[63]	__attribute__ ((packed));
} charspec;

/* Timestamp (ECMA 167 1/7.3) */
typedef struct {
	UINT16 typeAndTimezone	__attribute__ ((packed));
	UINT16 year					__attribute__ ((packed));
	UINT8 month					__attribute__ ((packed));
	UINT8 day					__attribute__ ((packed));
	UINT8 hour					__attribute__ ((packed));
	UINT8 minute				__attribute__ ((packed));
	UINT8 second				__attribute__ ((packed));
	UINT8 centiseconds		__attribute__ ((packed));
	UINT8 hundredsOfMicroseconds	__attribute__ ((packed));
	UINT8 microseconds		__attribute__ ((packed));
} timestamp;

/* Timestamp types (ECMA 167 1/7.3.1) */
#define TIMESTAMP_TYPE_CUT			0x0000U
#define TIMESTAMP_TYPE_LOCAL		0x0001U
#define TIMESTAMP_TYPE_AGREEMENT	0x0002U

/* Entity Identifier (ECMA 167 1/7.4) */
typedef struct {
	UINT8 flags				__attribute__ ((packed));
	UINT8 ident[23]		__attribute__ ((packed));
	UINT8 identSuffix[8]	__attribute__ ((packed));
} EntityID;
#define regid EntityID

/* Entity identifier flags (ECMA 167 1/7.4.1) */
#define ENTITYID_FLAGS_DIRTY		0x01U
#define ENTITYID_FLAGS_PROTECTED	0x02U

/* Volume Structure Descriptor (ECMA 167 2/9.1) */
#define STD_ID_LEN	5
struct VolStructDesc {
	UINT8 structType				__attribute__ ((packed));
	UINT8 stdIdent[STD_ID_LEN]	__attribute__ ((packed));
	UINT8 structVersion			__attribute__ ((packed));
	UINT8 structData[2041]		__attribute__ ((packed));
};

/* Std structure identifiers (ECMA 167 2/9.1.2) */
#define STD_ID_BEA01	"BEA01"
#define STD_ID_BOOT2	"BOOT2"
#define STD_ID_CD001	"CD001"
#define STD_ID_CDW02	"CDW02"
#define STD_ID_NSR02	"NSR02"
#define STD_ID_NSR03	"NSR03"
#define STD_ID_TEA01	"TEA01"

/* Beginning Extended Area Descriptor (ECMA 167 2/9.2) */
struct BeginningExtendedAreaDesc {
	UINT8 structType				__attribute__ ((packed));
	UINT8 stdIdent[STD_ID_LEN]	__attribute__ ((packed));
	UINT8 structVersion			__attribute__ ((packed));
	UINT8 structData[2041]		__attribute__ ((packed));
};

/* Terminating Extended Area Descriptor (ECMA 167 2/9.3) */
struct TerminatingExtendedAreaDesc {
	UINT8 structType				__attribute__ ((packed));
	UINT8 stdIdent[STD_ID_LEN]	__attribute__ ((packed));
	UINT8 structVersion			__attribute__ ((packed));
	UINT8 structData[2041]		__attribute__ ((packed));
};

/* Boot Descriptor (ECMA 167 2/9.4) */
struct BootDesc {
	UINT8 structType				__attribute__ ((packed));
	UINT8 stdIdent[STD_ID_LEN]	__attribute__ ((packed));
	UINT8 structVersion			__attribute__ ((packed));
	UINT8 reserved1				__attribute__ ((packed));
	EntityID architectureType	__attribute__ ((packed));
	EntityID bootIdent			__attribute__ ((packed));
	UINT32 bootExtLocation		__attribute__ ((packed));
	UINT32 bootExtLength			__attribute__ ((packed));
	UINT8 loadAddress[8]		   __attribute__ ((packed));
	UINT8 startAddress[8]		__attribute__ ((packed));
	timestamp descCreationDateAndTime	__attribute__ ((packed));
	UINT16 flags					__attribute__ ((packed));
	UINT8 reserved2[32]			__attribute__ ((packed));
	UINT8 bootUse[1906]			__attribute__ ((packed));
};

/* Boot flags (ECMA 167 2/9.4.12) */
#define BOOT_FLAGS_ERASE	1

/* Extent Descriptor (ECMA 167 3/7.1) */
typedef struct {
	UINT32 extLength		__attribute__ ((packed));
	UINT32 extLocation	__attribute__ ((packed));
} extent_ad;

/* Descriptor Tag (ECMA 167 3/7.2) */
typedef struct {
	UINT16 tagIdent		__attribute__ ((packed));
	UINT16 descVersion	__attribute__ ((packed));
	UINT8 tagChecksum		__attribute__ ((packed));
	UINT8 reserved			__attribute__ ((packed));
	UINT16 tagSerialNum	__attribute__ ((packed));
	UINT16 descCRC			__attribute__ ((packed));
	UINT16 descCRCLength	__attribute__ ((packed));
	UINT32 tagLocation	__attribute__ ((packed));
} tag;

/* Tag Identifiers (ECMA 167 3/7.2.1) */
#define TID_UNUSED_DESC					0x0000U
#define TID_PRIMARY_VOL_DESC			0x0001U
#define TID_ANCHOR_VOL_DESC_PTR		0x0002U
#define TID_VOL_DESC_PTR				0x0003U
#define TID_IMP_USE_VOL_DESC			0x0004U
#define TID_PARTITION_DESC				0x0005U
#define TID_LOGICAL_VOL_DESC			0x0006U
#define TID_UNALLOC_SPACE_DESC		0x0007U
#define TID_TERMINATING_DESC			0x0008U
#define TID_LOGICAL_VOL_INTEGRITY_DESC	0x0009U

/* Tag Identifiers (ECMA 167 4/7.2.1) */
#define TID_FILE_SET_DESC			0x0100U
#define TID_FILE_IDENT_DESC		0x0101U
#define TID_ALLOC_EXTENT_DESC		0x0102U
#define TID_INDIRECT_ENTRY			0x0103U
#define TID_TERMINAL_ENTRY			0x0104U
#define TID_FILE_ENTRY				0x0105U
#define TID_EXTENDED_ATTRE_HEADER_DESC	0x0106U
#define TID_UNALLOCATED_SPACE_ENTRY	0x0107U
#define TID_SPACE_BITMAP_DESC		0x0108U
#define TID_PARTITION_INTEGRITY_ENTRY	0x0109U
#define TID_EXTENDED_FILE_ENTRY	0x010AU

/* NSR Descriptor (ECMA 167 3/9.1) */
struct NSRDesc {
	UINT8 structType				__attribute__ ((packed));
	UINT8 stdIdent[STD_ID_LEN]	__attribute__ ((packed));
	UINT8 structVersion			__attribute__ ((packed));
	UINT8 reserved					__attribute__ ((packed));
	UINT8 structData[2040]		__attribute__ ((packed));
};

/* Primary Volume Descriptor (ECMA 167 3/10.1) */
struct PrimaryVolDesc {
	tag descTag						__attribute__ ((packed));
	UINT32 volDescSeqNum			__attribute__ ((packed));
	UINT32 primaryVolDescNum	__attribute__ ((packed));
	dstring volIdent[32]			__attribute__ ((packed));
	UINT16 volSeqNum				__attribute__ ((packed));
	UINT16 maxVolSeqNum			__attribute__ ((packed));
	UINT16 interchangeLvl		__attribute__ ((packed));
	UINT16 maxInterchangeLvl	__attribute__ ((packed));
	UINT32 charSetList			__attribute__ ((packed));
	UINT32 maxCharSetList		__attribute__ ((packed));
	dstring volSetIdent[128]	__attribute__ ((packed));
	charspec descCharSet			__attribute__ ((packed));
	charspec explanatoryCharSet	__attribute__ ((packed));
	extent_ad volAbstract		__attribute__ ((packed));
	extent_ad volCopyright		__attribute__ ((packed));
	EntityID appIdent				__attribute__ ((packed));
	timestamp recordingDateAndTime	__attribute__ ((packed));
	EntityID impIdent				__attribute__ ((packed));
	UINT8 impUse[64]				__attribute__ ((packed));
	UINT32 predecessorVolDescSeqLocation	__attribute__ ((packed));
	UINT16 flags					__attribute__ ((packed));
	UINT8 reserved[22]			__attribute__ ((packed));
};

/* Primary volume descriptor flags (ECMA 167 3/10.1.21) */
#define VOL_SET_IDENT	1

/* Anchor Volume Descriptor Pointer (ECMA 167 3/10.2) */
struct AnchorVolDescPtr {
	tag descTag								__attribute__ ((packed));
	extent_ad mainVolDescSeqExt		__attribute__ ((packed));
	extent_ad reserveVolDescSeqExt	__attribute__ ((packed));
	UINT8 reserved[480]					__attribute__ ((packed));
};

/* Volume Descriptor Pointer (ECMA 167 3/10.3) */
struct VolDescPtr {
	tag descTag							__attribute__ ((packed));
	UINT32 volDescSeqNum				__attribute__ ((packed));
	extent_ad nextVolDescSeqExt	__attribute__ ((packed));
	UINT8 reserved[484]				__attribute__ ((packed));
};

/* Implementation Use Volume Descriptor (ECMA 167 3/10.4) */
struct ImpUseVolDesc {
	tag descTag				__attribute__ ((packed));
	UINT32 volDescSeqNum	__attribute__ ((packed));
	EntityID impIdent		__attribute__ ((packed));
	UINT8 impUse[460]		__attribute__ ((packed));
};

/* Partition Descriptor (ECMA 167 3/10.5) */
struct PartitionDesc {
	tag descTag								__attribute__ ((packed));
	UINT32 volDescSeqNum					__attribute__ ((packed));
	UINT16 partitionFlags				__attribute__ ((packed));
	UINT16 partitionNumber				__attribute__ ((packed));
	EntityID partitionContents			__attribute__ ((packed));
	UINT8 partitionContentsUse[128]	__attribute__ ((packed));
	UINT32 accessType						__attribute__ ((packed));
	UINT32 partitionStartingLocation	__attribute__ ((packed));
	UINT32 partitionLength				__attribute__ ((packed));
	EntityID impIdent						__attribute__ ((packed));
	UINT8 impUse[128]						__attribute__ ((packed));
	UINT8 reserved[156]					__attribute__ ((packed));
};

/* Partition Flags (ECMA 167 3/10.5.3) */
#define PARTITION_FLAGS_ALLOC	1

/* Partition Contents (ECMA 167 3/10.5.5) */
#define PARTITION_CONTENTS_FDC01	"+FDC01"
#define PARTITION_CONTENTS_CD001	"+CD001"
#define PARTITION_CONTENTS_CDW02	"+CDW02"
#define PARTITION_CONTENTS_NSR02	"+NSR02"
#define PARTITION_CONTENTS_NSR03	"+NSR03"

/* Partition Access Types (ECMA 167 3/10.5.7) */
#define PARTITION_ACCESS_NONE	0
#define PARTITION_ACCESS_R		1
#define PARTITION_ACCESS_WO	2
#define PARTITION_ACCESS_RW	3
#define PARTITION_ACCESS_OW	4

/* Logical Volume Descriptor (ECMA 167 3/10.6) */
struct LogicalVolDesc {
	tag descTag								__attribute__ ((packed));
	UINT32 volDescSeqNum					__attribute__ ((packed));
	charspec descCharSet					__attribute__ ((packed));
	dstring logicalVolIdent[128]		__attribute__ ((packed));
	UINT32 logicalBlockSize				__attribute__ ((packed));
	EntityID domainIdent					__attribute__ ((packed));
	UINT8 logicalVolContentsUse[16]	__attribute__ ((packed)); /* used to find fileset */
	UINT32 mapTableLength				__attribute__ ((packed));
	UINT32 numPartitionMaps				__attribute__ ((packed));
	EntityID impIdent						__attribute__ ((packed));
	UINT8 impUse[128]						__attribute__ ((packed));
	extent_ad integritySeqExt			__attribute__ ((packed));
};

/* Generic Partition Map (ECMA 167 3/10.7.1) */
struct GenericPartitionMap {
	UINT8 partitionMapType		__attribute__ ((packed));
	UINT8 partitionMapLength	__attribute__ ((packed));
};

/* Partition Map Type (ECMA 167 3/10.7.1.1) */
#define PARTITION_MAP_TYPE_NONE		0
#define PARTITION_MAP_TYPE_1			1
#define PARTITION_MAP_TYPE_2			2

/* Type 1 Partition Map (ECMA 167 3/10.7.2) */
struct GenericPartitionMap1 {
	UINT8 partitionMapType			__attribute__ ((packed));
	UINT8 partitionMapLength		__attribute__ ((packed));
	UINT16 volSeqNum					__attribute__ ((packed));
	UINT16 partitionNum				__attribute__ ((packed));
};

/* Type 2 Partition Map (ECMA 167 3/10.7.3) */
struct GenericPartitionMap2 {
	UINT8 partitionMapType		__attribute__ ((packed)); /* 2 */
	UINT8 partitionMapLength	__attribute__ ((packed));
	UINT8 partitionIdent[62]	__attribute__ ((packed));
};

/* Unallocated Space Descriptor (ECMA 167 3/10.8) */
struct UnallocatedSpaceDesc {
	tag descTag				__attribute__ ((packed));
	UINT32 volDescSeqNum	__attribute__ ((packed));
	UINT32 numAllocDescs	__attribute__ ((packed));
};

/* Terminating Descriptor (ECMA 3/10.9) */
struct TerminatingDesc {
	tag descTag				__attribute__ ((packed));
	UINT8 reserved[496]	__attribute__ ((packed));
};

struct GenericDesc
{
	tag descTag				__attribute__ ((packed));
	UINT32 volDescSeqNum	__attribute__ ((packed));
};

/* Logical Volume Integrity Descriptor (ECMA 167 3/10.10) */
struct LogicalVolIntegrityDesc {
	tag descTag								__attribute__ ((packed));
	timestamp recordingDateAndTime	__attribute__ ((packed));
	UINT32 integrityType					__attribute__ ((packed));
	extent_ad nextIntegrityExt			__attribute__ ((packed));
	UINT8 logicalVolContentsUse[32]	__attribute__ ((packed));
	UINT32 numOfPartitions				__attribute__ ((packed));
	UINT32 lengthOfImpUse				__attribute__ ((packed));
};

/* Integrity Types (ECMA 167 3/10.10.3) */
#define INTEGRITY_TYPE_OPEN	0
#define INTEGRITY_TYPE_CLOSE	1

/* Recorded Address (ECMA 167 4/7.1) */
typedef struct {
	UINT32 logicalBlockNum 			__attribute__ ((packed));
	UINT16 partitionReferenceNum	__attribute__ ((packed));
} lb_addr;

/* Extent interpretation (ECMA 167 4/14.14.1.1) */
#define EXTENT_RECORDED_ALLOCATED               0x00
#define EXTENT_NOT_RECORDED_ALLOCATED           0x01
#define EXTENT_NOT_RECORDED_NOT_ALLOCATED       0x02
#define EXTENT_NEXT_EXTENT_ALLOCDECS            0x03

/* Long Allocation Descriptor (ECMA 167 4/14.14.2) */
typedef struct {
	UINT32 extLength		__attribute__ ((packed));
	lb_addr extLocation	__attribute__ ((packed));
	UINT8 impUse[6]		__attribute__ ((packed));
} long_ad;
/* upper 2 bits of extLength indicate type */

/* File Set Descriptor (ECMA 167 4/14.1) */
struct FileSetDesc {
	tag descTag								__attribute__ ((packed));
	timestamp recordingDateAndTime	__attribute__ ((packed));
	UINT16 interchangeLvl				__attribute__ ((packed));
	UINT16 maxInterchangeLvl			__attribute__ ((packed));
	UINT32 charSetList					__attribute__ ((packed));
	UINT32 maxCharSetList				__attribute__ ((packed));
	UINT32 fileSetNum						__attribute__ ((packed));
	UINT32 fileSetDescNum				__attribute__ ((packed));
	charspec logicalVolIdentCharSet	__attribute__ ((packed));
	dstring logicalVolIdent[128]		__attribute__ ((packed));
	charspec fileSetCharSet				__attribute__ ((packed));
	dstring fileSetIdent[32]			__attribute__ ((packed));
	dstring copyrightFileIdent[32]	__attribute__ ((packed));
	dstring abstractFileIdent[32]		__attribute__ ((packed));
	long_ad rootDirectoryICB			__attribute__ ((packed));
	EntityID domainIdent					__attribute__ ((packed));
	long_ad nextExt						__attribute__ ((packed));
	long_ad streamDirectoryICB			__attribute__ ((packed));
	UINT8 reserved[32]					__attribute__ ((packed));
};

/* Short Allocation Descriptor (ECMA 167 4/14.14.1) */
typedef struct {
	UINT32 extLength		__attribute__ ((packed));
	UINT32 extPosition	__attribute__ ((packed));
} short_ad;

/* Partition Header Descriptor (ECMA 167 4/14.3) */
struct PartitionHeaderDesc {
	short_ad unallocatedSpaceTable	__attribute__ ((packed));
	short_ad unallocatedSpaceBitmap	__attribute__ ((packed));
	short_ad partitionIntegrityTable	__attribute__ ((packed));
	short_ad freedSpaceTable			__attribute__ ((packed));
	short_ad freedSpaceBitmap			__attribute__ ((packed));
	UINT8 reserved[88]					__attribute__ ((packed));
};

/* File Identifier Descriptor (ECMA 167 4/14.4) */
struct FileIdentDesc
{
	tag descTag						__attribute__ ((packed));
	UINT16 fileVersionNum		__attribute__ ((packed)); /* 1 */
	UINT8 fileCharacteristics	__attribute__ ((packed));
	UINT8 lengthFileIdent		__attribute__ ((packed));
	long_ad icb						__attribute__ ((packed));
	UINT16 lengthOfImpUse		__attribute__ ((packed));
};

/* File Characteristics (ECMA 167 4/14.4.3) */
#define FILE_HIDDEN		1
#define FILE_DIRECTORY	2
#define FILE_DELETED		4
#define FILE_PARENT		8
#define FILE_METADATA	0x10 /* UDF 2.0 */

/* Allocation Ext Descriptor (ECMA 167 4/14.5) */
struct AllocExtDesc
{
	tag descTag								__attribute__ ((packed));
	UINT32 previousAllocExtLocation	__attribute__ ((packed));
	UINT32 lengthAllocDescs				__attribute__ ((packed));
};

/* ICB Tag (ECMA 167 4/14.6) */
typedef struct {
	UINT32 priorRecordedNumDirectEntries	__attribute__ ((packed));
	UINT16 strategyType							__attribute__ ((packed));
	UINT16 strategyParameter					__attribute__ ((packed));
	UINT16 numEntries								__attribute__ ((packed));
	UINT8 reserved									__attribute__ ((packed));
	UINT8 fileType									__attribute__ ((packed));
	lb_addr parentICBLocation					__attribute__ ((packed));
	UINT16 flags									__attribute__ ((packed));
} icbtag;

/* ICB File Type (ECMA 167 4/14.6.6) */
#define FILE_TYPE_NONE			0x00U
#define FILE_TYPE_UNALLOC		0x01U
#define FILE_TYPE_INTEGRITY	0x02U
#define FILE_TYPE_INDIRECT		0x03U
#define FILE_TYPE_DIRECTORY	0x04U
#define FILE_TYPE_REGULAR		0x05U
#define FILE_TYPE_BLOCK			0x06U
#define FILE_TYPE_CHAR			0x07U
#define FILE_TYPE_EXTENDED		0x08U
#define FILE_TYPE_FIFO			0x09U
#define FILE_TYPE_SOCKET		0x0aU
#define FILE_TYPE_TERMINAL		0x0bU
#define FILE_TYPE_SYMLINK		0x0cU
#define FILE_TYPE_STREAMDIR	0x0dU /* ECMA 167 4/13 */

/* ICB Flags (ECMA 167 4/14.6.8) */
#define ICB_FLAG_ALLOC_MASK		0x0007U
#define ICB_FLAG_SORTED				0x0008U
#define ICB_FLAG_NONRELOCATABLE	0x0010U
#define ICB_FLAG_ARCHIVE			0x0020U
#define ICB_FLAG_SETUID				0x0040U
#define ICB_FLAG_SETGID				0x0080U
#define ICB_FLAG_STICKY				0x0100U
#define ICB_FLAG_CONTIGUOUS		0x0200U
#define ICB_FLAG_SYSTEM				0x0400U
#define ICB_FLAG_TRANSFORMED		0x0800U
#define ICB_FLAG_MULTIVERSIONS	0x1000U

/* ICB Flags Allocation type(ECMA 167 4/14.6.8) */
#define ICB_FLAG_AD_SHORT		0
#define ICB_FLAG_AD_LONG		1
#define ICB_FLAG_AD_EXTENDED	2
#define ICB_FLAG_AD_IN_ICB		3

/* Indirect Entry (ECMA 167 4/14.7) */
struct IndirectEntry {
	tag descTag				__attribute__ ((packed));
	icbtag icbTag			__attribute__ ((packed));
	long_ad indirectICB	__attribute__ ((packed));
};

/* Terminal Entry (ECMA 167 4/14.8) */
struct TerminalEntry {
	tag descTag		__attribute__ ((packed));
	icbtag icbTag	__attribute__ ((packed));
};

/* File Entry (ECMA 167 4/14.9) */
struct FileEntry {
	tag			descTag				__attribute__ ((packed));
	icbtag		icbTag				__attribute__ ((packed));
	UINT32		uid					__attribute__ ((packed));
	UINT32		gid					__attribute__ ((packed));
	UINT32		permissions			__attribute__ ((packed));
	UINT16		fileLinkCount		__attribute__ ((packed));
	UINT8			recordFormat		__attribute__ ((packed));
	UINT8			recordDisplayAttr	__attribute__ ((packed));
	UINT32		recordLength		__attribute__ ((packed));
	UINT8		   informationLength[8]	__attribute__ ((packed));
	UINT8		   logicalBlocksRecorded[8]	__attribute__ ((packed));
	timestamp	accessTime			__attribute__ ((packed));
	timestamp	modificationTime	__attribute__ ((packed));
	timestamp	attrTime				__attribute__ ((packed));
	UINT32		checkpoint			__attribute__ ((packed));
	long_ad		extendedAttrICB	__attribute__ ((packed));
	EntityID		impIdent				__attribute__ ((packed));
	UINT8		   uniqueID[8] 			__attribute__ ((packed)); /* 0= root, 16- (2^32-1) */
	UINT32		lengthExtendedAttr	__attribute__ ((packed));
	UINT32		lengthAllocDescs	__attribute__ ((packed));
};

/* File Permissions (ECMA 167 4/14.9.5) */
#define PERM_O_EXEC		0x00000001U
#define PERM_O_WRITE		0x00000002U
#define PERM_O_READ		0x00000004U
#define PERM_O_CHATTR	0x00000008U
#define PERM_O_DELETE	0x00000010U
#define PERM_G_EXEC		0x00000020U
#define PERM_G_WRITE		0x00000040U
#define PERM_G_READ		0x00000080U
#define PERM_G_CHATTR	0x00000100U
#define PERM_G_DELETE	0x00000200U
#define PERM_U_EXEC		0x00000400U
#define PERM_U_WRITE		0x00000800U
#define PERM_U_READ		0x00001000U
#define PERM_U_CHATTR	0x00002000U
#define PERM_U_DELETE	0x00004000U

/* File Record Format (ECMA 167 4/14.9.7) */
#define RECORD_FMT_NONE				0
#define RECORD_FMT_FIXED_PAD		1
#define RECORD_FMT_FIXED			2
#define RECORD_FMT_VARIABLE8		3
#define RECORD_FMT_VARIABLE16		4
#define RECORD_FMT_VARIABLE16_MSB	5
#define RECORD_FMT_VARIABLE32		6
#define RECORD_FMT_PRINT			7
#define RECORD_FMT_LF				8
#define RECORD_FMT_CR				9
#define RECORD_FMT_CRLF				10
#define RECORD_FMT_LFCR				10

/* Extended Attribute Header Descriptor (ECMA 167 4/14.10.1) */
struct ExtendedAttrHeaderDesc {
	tag descTag					__attribute__ ((packed));
	UINT32 impAttrLocation	__attribute__ ((packed));
	UINT32 appAttrLocation	__attribute__ ((packed));
};

/* Generic Attribute Format (ECMA 4/14.10.2) */
struct GenericAttrFormat {
	UINT32 attrType	__attribute__ ((packed));
	UINT8 attrSubtype	__attribute__ ((packed));
	UINT8 reserved[3]	__attribute__ ((packed));
	UINT32 attrLength	__attribute__ ((packed));
};

/* Character Set Attribute Format (ECMA 4/14.10.3) */
struct CharSetAttrFormat {
	UINT32 attrType	__attribute__ ((packed));		/* 1 */
	UINT8 attrSubtype	__attribute__ ((packed));		/* 1 */
	UINT8 reserved[3]	__attribute__ ((packed));
	UINT32 attrLength	__attribute__ ((packed));
	UINT32 escapeSeqLength	__attribute__ ((packed));
	UINT8 charSetType	__attribute__ ((packed));
};

/* Alternate Permissions (ECMA 167 4/14.10.4) */
struct AlternatePermissionsExtendedAttr {
	UINT32 attrType	__attribute__ ((packed));		/* 3 */
	UINT8 attrSubtype	__attribute__ ((packed));		/* 1 */
	UINT8 reserved[3]	__attribute__ ((packed));
	UINT32 attrLength	__attribute__ ((packed));
	UINT16 ownerIdent	__attribute__ ((packed));
	UINT16 groupIdent	__attribute__ ((packed));
	UINT16 permission	__attribute__ ((packed));
};

/* File Times Extended Attribute (ECMA 167 4/14.10.5) */
struct FileTimesExtendedAttr {
	UINT32 attrType	__attribute__ ((packed));		/* 5 */
	UINT8 attrSubtype	__attribute__ ((packed));		/* 1 */
	UINT8 reserved[3]	__attribute__ ((packed));
	UINT32 attrLength	__attribute__ ((packed));
	UINT32 dataLength	__attribute__ ((packed));
	UINT32 fileTimeExistence	__attribute__ ((packed));
	UINT8 fileTimes	__attribute__ ((packed));
};

/* FileTimeExistence (ECMA 167 4/14.10.5.6) */
#define FTE_CREATION		0
#define FTE_DELETION		2
#define FTE_EFFECTIVE	3
#define FTE_BACKUP		5

/* Information Times Extended Attribute (ECMA 167 4/14.10.6) */
struct InfoTimesExtendedAttr {
	UINT32 attrType				__attribute__ ((packed));		/* 6 */
	UINT8 attrSubtype				__attribute__ ((packed));		/* 1 */
	UINT8 reserved[3]				__attribute__ ((packed));
	UINT32 attrLength				__attribute__ ((packed));
	UINT32 dataLength				__attribute__ ((packed));
	UINT32 infoTimeExistence	__attribute__ ((packed));
};

/* Device Specification Extended Attribute (ECMA 167 4/14.10.7) */
struct DeviceSpecificationExtendedAttr {
	UINT32 attrType			__attribute__ ((packed));		/* 12 */
	UINT8 attrSubtype			__attribute__ ((packed));		/* 1 */
	UINT8 reserved[3]			__attribute__ ((packed));
	UINT32 attrLength			__attribute__ ((packed));
	UINT32 impUseLength		__attribute__ ((packed));
	UINT32 majorDeviceIdent	__attribute__ ((packed));
	UINT32 minorDeviceIdent	__attribute__ ((packed));
};

/* Implementation Use Extended Attr (ECMA 167 4/14.10.8) */
struct ImpUseExtendedAttr {
	UINT32 attrType		__attribute__ ((packed));		/* 2048 */
	UINT8 attrSubtype		__attribute__ ((packed));		/* 1 */
	UINT8 reserved[3]		__attribute__ ((packed));
	UINT32 attrLength		__attribute__ ((packed));
	UINT32 impUseLength	__attribute__ ((packed));
	EntityID impIdent		__attribute__ ((packed));
};

// support for CGMS, added by robert.chang, 2006/04/04
/* Copyright Management Infomation */
struct CopyrightManaInfoOfUdf {
	UINT16 headChecksum  __attribute__ ((packed));
	UINT8 cgmsInfo             __attribute__ ((packed));
	UINT8 dataStructType    __attribute__ ((packed));
	UINT32 protectSysInfo   __attribute__ ((packed));
};	

struct CopyrightManaInfoOfIso {
	UINT8 cgmsInfo             __attribute__ ((packed));
	UINT8 dataStructType    __attribute__ ((packed));
	UINT32 protectSysInfo   __attribute__ ((packed));
};	

/* Application Use Extended Attribute (ECMA 167 4/14.10.9) */
struct AppUseExtendedAttr {
	UINT32 attrType		__attribute__ ((packed));		/* 65536 */
	UINT8 attrSubtype		__attribute__ ((packed));		/* 1 */
	UINT8 reserved[3]		__attribute__ ((packed));
	UINT32 attrLength		__attribute__ ((packed));
	UINT32 appUseLength	__attribute__ ((packed));
	EntityID appIdent		__attribute__ ((packed));
};

#define EXTATTR_CHAR_SET	1
#define EXTATTR_ALT_PERMS	3
#define EXTATTR_FILE_TIMES	5
#define EXTATTR_INFO_TIMES	6
#define EXTATTR_DEV_SPEC	12
#define EXTATTR_IMP_USE		2048
#define EXTATTR_APP_USE		65536


/* Unallocated Space Entry (ECMA 167 4/14.11) */
struct UnallocatedSpaceEntry {
	tag descTag					__attribute__ ((packed));
	icbtag icbTag				__attribute__ ((packed));
	UINT32 lengthAllocDescs	__attribute__ ((packed));
};

/* Space Bitmap Descriptor (ECMA 167 4/14.12) */
struct SpaceBitmapDesc {
	tag descTag			__attribute__ ((packed));
	UINT32 numOfBits	__attribute__ ((packed));
	UINT32 numOfBytes	__attribute__ ((packed));
};

/* Partition Integrity Entry (ECMA 167 4/14.13) */
struct PartitionIntegrityEntry {
	tag descTag								__attribute__ ((packed));
	icbtag icbTag							__attribute__ ((packed));
	timestamp recordingDateAndTime	__attribute__ ((packed));
	UINT8 integrityType					__attribute__ ((packed));
	UINT8 reserved[175]					__attribute__ ((packed));
	EntityID impIdent						__attribute__ ((packed));
	UINT8 impUse[256]						__attribute__ ((packed));
};

/* Extended Allocation Descriptor (ECMA 167 4/14.14.3) */
typedef struct { /* ECMA 167 4/14.14.3 */
	UINT32 extLength				__attribute__ ((packed));
	UINT32 recordedLength		__attribute__ ((packed));
	UINT32 informationLength	__attribute__ ((packed));
	lb_addr extLocation			__attribute__ ((packed));
} ext_ad;

/* Logical Volume Header Descriptor (ECMA 167 4/14.5) */
struct LogicalVolHeaderDesc {
	UINT8 uniqueID[8]		__attribute__ ((packed));
	UINT8 reserved[24]	__attribute__ ((packed));
};

/* Path Component (ECMA 167 4/14.16.1) */
struct PathComponent {
	UINT8 componentType					__attribute__ ((packed));
	UINT8 lengthComponentIdent			__attribute__ ((packed));
	UINT16 componentFileVersionNum	__attribute__ ((packed));
};

/* File Entry (ECMA 167 4/14.17) */
struct ExtendedFileEntry {
	tag			descTag						__attribute__ ((packed));
	icbtag		icbTag						__attribute__ ((packed));
	UINT32		uid							__attribute__ ((packed));
	UINT32		gid							__attribute__ ((packed));
	UINT32		permissions					__attribute__ ((packed));
	UINT16		fileLinkCount				__attribute__ ((packed));
	UINT8			recordFormat				__attribute__ ((packed));
	UINT8			recordDisplayAttr			__attribute__ ((packed));
	UINT32		recordLength				__attribute__ ((packed));
	UINT8		   informationLength[8]		__attribute__ ((packed));
	UINT8		   objectSize[8]				__attribute__ ((packed));
	UINT8		   logicalBlocksRecorded[8]	__attribute__ ((packed));
	timestamp	accessTime					__attribute__ ((packed));
	timestamp	modificationTime			__attribute__ ((packed));
	timestamp	createTime					__attribute__ ((packed));
	timestamp	attrTime						__attribute__ ((packed));
	UINT32		checkpoint					__attribute__ ((packed));
	UINT32		reserved						__attribute__ ((packed));
	long_ad		extendedAttrICB			__attribute__ ((packed));
	long_ad		streamDirectoryICB		__attribute__ ((packed));
	EntityID		impIdent						__attribute__ ((packed));
	UINT8		   uniqueID[8]					__attribute__ ((packed));
	UINT32		lengthExtendedAttr		__attribute__ ((packed));
	UINT32		lengthAllocDescs			__attribute__ ((packed));
};

#endif /* !defined(_UDF_167_H) */
