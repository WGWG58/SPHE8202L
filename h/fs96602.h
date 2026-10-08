#ifndef __FS9660_H
#define __FS9660_H

#include "memmap.h"
#include "user_init.h"

#if (defined( SDRAM_16Mb_Mode ) && defined( SUPPORT_FILE_SYSTEM_MODE ))||defined(FAT_FILE_MODE)||defined(FILE_MODE_WRITE)  //sunzhh mod 20041230//liweihua mod 2004-11-2// 2004/06/12 yltseng
extern  UINT32      _fs9660_buf;
#else
extern  UINT8    _fs9660_buf [];
#endif

#ifdef PMP_DVD
extern  UINT32   hdd_dir_parent_add;//kenny add 2005/6/15
#define ISO9660_HDD_DIR_PARENT_OFFSET   hdd_dir_parent_add
#define hdd_dir_parent  ((DIR_REC *) ISO9660_HDD_DIR_PARENT_OFFSET)

#endif

#define ISO9660_DIR_OFFSET              _fs9660_buf

#if defined( SDRAM_16Mb_Mode ) && defined( SUPPORT_FILE_SYSTEM_MODE )
    #ifdef REDUCE_SUP_SRT_FOR_FS9660
#define ISO9660_FILE_OFFSET             (_fs9660_buf+7*1024)
    #else
#define ISO9660_FILE_OFFSET             (_fs9660_buf+1*1024)
    #endif
#else
#define ISO9660_FILE_OFFSET             (_fs9660_buf+10*1024)
#endif

#if defined(SUPPORT_UNICODE_FONT)&& defined(PMP_DVD) //kenny 2005/8/22
UINT32 unicode_font_address;
UINT32 unicode_font_size;
#define unicode_font_buf ((BYTE *)SDRAM_BASE + HD_FONT_YA * 1024)

#endif

// 2004/02/17 yltseng
#if defined( SDRAM_16Mb_Mode ) && defined( SUPPORT_FILE_SYSTEM_MODE )
    #ifdef REDUCE_SUP_SRT_FOR_FS9660
        #ifdef FS_LOAD_DIR_SEPARATELY //SAVE_EACH_DIR_FILE_COUNT
#define ISO_DIR_MAX                     (7*1024/(sizeof(DIR_REC)+FS_DIR_FILE_COUNT_MEMBERS_PER_ENTRY*sizeof(UINT16)))//add max-dir limition,7k
        #else   //!FS_LOAD_DIR_SEPARATELY
#define ISO_DIR_MAX                     (7*1024/sizeof(DIR_REC))    //add max-dir limition,7k
        #endif  //#ifdef FS_LOAD_DIR_SEPARATELY
#define ISO_FILE_MAX                    (980)       //add max-file limition,27k buffer needed
    #else   //!REDUCE_SUP_SRT_FOR_FS9660
#define ISO_DIR_MAX                     (30)        //add max-dir limition
#define ISO_FILE_MAX                    (250)       //add max-file limition
    #endif  //#ifdef REDUCE_SUP_SRT_FOR_FS9660
#else
    #if defined(READ_DIR_AS_PC) || defined (FAT_FILE_MODE) || defined (FILE_MODE_WRITE) || defined(SUPPORT_FS_LONGNAME) || defined(SPHE8202_FAT_WRITE_API) || defined(SPHE8202_FAT_Write_Function) || defined( SUPPORT_ISO9660_MULTI_FILE_SECTION )
#define ISO_DIR_MAX                     (200)       //add max-dir limition
#define ISO_FILE_MAX                    (1200)      //add max-file limition
#define	MAX_SUBDIR_NUM                  (10)		//add max-subdir to support copying frank.huang 050905
    #else
#define ISO_DIR_MAX                     (300)       //add max-dir limition
#define ISO_FILE_MAX                    (3000)      //add max-file limition

    #endif
#endif

#define iso9660_dir                     ((DIR_REC *)ISO9660_DIR_OFFSET)

//kevinmonkey 051228
#ifdef FS_LOAD_DIR_SEPARATELY 
//used by SAVE_EACH_DIR_FILE_COUNT
    #if defined(SUPPORT_NESGAME) //both others and game are supported
#define FS_DIR_FILE_COUNT_MEMBERS_PER_ENTRY     4
    #elif defined(SUPPORT_FILE_SYSTEM_MODE)//only others is supported
#define FS_DIR_FILE_COUNT_MEMBERS_PER_ENTRY     3
    #else   //none of them are supported
#define FS_DIR_FILE_COUNT_MEMBERS_PER_ENTRY     2
    #endif  //determine of how many kind of file count we should remember (only others and game are considerred)

#define FS_DIR_FILE_COUNT_MEMBER_MP3            0
#define FS_DIR_FILE_COUNT_MEMBER_JPEG           1
    #ifdef SUPPORT_FILE_SYSTEM_MODE
#define FS_DIR_FILE_COUNT_MEMBER_OTHER          2
    #endif  //#ifdef SUPPORT_FILE_SYSTEM_MODE
    #ifdef SUPPORT_NESGAME
#define FS_DIR_FILE_COUNT_MEMBER_GAME           3
    #endif  //#ifdef SUPPORT_NESGAME

//should consider alignment, or this direct assign may result in access error and halt.
#define iso9660_dir_file_count          ((UINT16*)(ISO9660_DIR_OFFSET + ISO_DIR_MAX*sizeof(DIR_REC)))

//separate loading use iso9660_file as a pointer adjusted by the index we want to access
UINT8*  iso9660_file_ptr;
#define iso9660_file ((DIR_REC *)iso9660_file_ptr)
extern int gi_FSLoadedDir;
#else   //normal case

#define iso9660_file                    ((DIR_REC *)ISO9660_FILE_OFFSET)
#endif //#ifdef FS_LOAD_DIR_SEPARATELY

#if defined(FAT_FILE_MODE)
#define CurrentFiles1                    ((UINT16*)(SDRAM_BASE + FS9660YA * 1024+108*1024))
#define CurrentFiles2                    ((UINT16*)(SDRAM_BASE + FS9660YA * 1024+109*1024))
#endif

#define DIR_REC_LEN                     sizeof(DIR_REC) //30


typedef struct
{
    BYTE            len_of_record;
    BYTE            len_of_attr;
    BYTE            location_le[4];
    BYTE            location_be[4];
    BYTE            length_le[4];
    BYTE            length_be[4];
    BYTE            time_stamp[7];
    BYTE            file_flag;
    BYTE            file_unit_size;
    BYTE            interleave_gap;
    UINT16          volume_seq_le;
    UINT16          volume_seq_be;
    BYTE            len_of_filename;
    BYTE            filename[31];
} CDDirRecord;

typedef struct
{
    BYTE            len_of_dirid;
    BYTE            len_of_attr;
    BYTE            location_of_ext[4];
    BYTE            parent_dir_num[2];
    BYTE            dirname[31];
} ISO_PATH_TABLE;

// 2005/09/12 yltseng
#define FS_FILE_NAME_LEN    12

typedef struct
{
    UINT32          loc;                                // mmssff 
    int             size;                               // in sectors 
    UINT32          AD_lba; 
    char            name[FS_FILE_NAME_LEN];             // 2005/02/16 yltseng
    UINT16          dir;                                // amount of MP3+JPEG+GAME files under the directory
#if defined(READ_DIR_AS_PC) || defined (FAT_FILE_MODE) || defined (FILE_MODE_WRITE) || defined(SUPPORT_FAT_FS_RESUME) //sunzhh 20041230
    INT16           parent_dir;                         //record its parent dir index
#endif
    
#if defined( SUPPORT_FS_LONGNAME ) || defined( SUPPORT_ISO9660_MULTI_FILE_SECTION ) // 2005/06/13 yltseng
    UINT32          rec_lba;
    UINT32          rec_offset;
#endif

    BYTE            type;
    BYTE            file_type;                          //20020730 #ifdef  SUPPORT_FILE_SYSTEM_MODE   
#if defined (FAT_FILE_MODE)||defined(FILE_MODE_WRITE) || defined(SUPPORT_FAT_LFN)   //lijd 2005-1-7 16:56 
    #if defined(READ_FAT_LONGNAME)&&defined(SUPPORT_FS_LONGNAME) 
    char            file_short_name[9];                 //linrc 2004-12-13 11:18 USE it checksum longfile name
    #endif
    char            file_ext_name[4];
#endif     

//#if defined(SPHE8202_FAT_WRITE_API)||defined(SPHE8202_FAT_Write_Function) //||defined(WRITE_USB) //liweihua 2004-8-16
#if defined(SPHE8202_FAT_WRITE_API)||defined(SPHE8202_FAT_Write_Function)//liweihua mod 2004-12-9 14:37//lijd 2005-1-5 18:16
    UINT16          presave_time;
    UINT32          save_time;
    UINT32          ext_info;
#endif
}DIR_REC;

/*
enum
{
    TYPE_UNKNOWN,
    TYPE_GB,
    TYPE_BIG5,
};
*/

// 2004/04/18 yltseng, Use this struct to represent supported file type
typedef struct
{
    char            FileExt[5];
    UINT8           uiFileType;
    UINT8           uiCategoryOfFile;
} FILE_EXT_INFO_TABLE;

//for OKO used, to record dir_index
#define MAX_MENU_NO 10
#define MAX_FILE_NAME_LEN 12
typedef struct
{
    int trk_no;    // how many files which a oko menu include
    char filename[MAX_FILE_NAME_LEN];
} OKO_MENU_DATA;

OKO_MENU_DATA oko_menu[MAX_MENU_NO];


//functions for external reference
int     read_iso9660(void);
UINT32  mp3_file_msf(UINT16);
UINT32  mp3_file_length(UINT16);
void    get_mergefile_info();
void    CalMergefilelength(UINT32*);
void    iso9660_assign_name(char*, char*, int, BYTE);
int     iso_search_str(char*, char*, int);
void    ConvertNameFormat( char*, char*, int*, int );


// 2004/04/16 yltseng, Use this function to find out if pFileName has the extension of pExtStr
// note, pExtStr should not store '.', eg 'WMA' or 'MP3'
int     FindFileExt( const char* pFileName, char* pExtStr );

// 2004/04/16 yltseng, Use this function to convert english in pStr from lower case to upper case
void    ConvertLowerCaseToUpperCase( char* pStr );

// 2004/04/16 yltseng, Use this function to find last occurance of c from pStr
char*   strrchr( const char* pStr, int c );

// 2004/04/18 yltseng, Use this function to fill iso9660_file data structure
#if defined( SUPPORT_FS_LONGNAME ) || defined( SUPPORT_ISO9660_MULTI_FILE_SECTION ) // 2005/06/13 yltseng
    void SetISO9660FileInfo( UINT32 uiLoc, UINT32 uiSize, UINT32 uiDir, char* pFileName, int iType, UINT32 AD_lba, UINT32 uiRecLba, UINT32 uiRecOffset );
#else
    void SetISO9660FileInfo( UINT32 uiLoc, UINT32 uiSize, UINT32 uiDir, char* pFileName, int iType, UINT32 AD_lba );
#endif

// 2004/04/18 yltseng, Use this function to process general file type ( defined in g_aFileExtInfoTable[] )
int     ProcessGeneralFileType( char* pFileName, UINT32 uiFileSize );

// 2004/04/18 yltseng, Use this function to process non-general file type
int     ProcessNonGeneralFileType( char* pFileName, UINT32 loc, UINT32 sz, int dir_index );

#if defined (MP4_DISC_DIRECT_PLAY) || defined(CDROM_MOVIE_DIRECT_PLAY)      //Maoyong 2004.04.14 // 2005/07/23 yltseng
    extern void         fsCheckSpecialMovieDisc();
#else
    static inline void  fsCheckSpecialMovieDisc() {}
#endif

char*   strinstr( const char* pStr, const char* pStrSearch, int iSrcLen );

#ifdef SUPPORT_FS_LONGNAME  //Maoyong 2004.06.24
    #ifdef HANYANG_FS_LONGNAME   //Maoyong 2004-7-6 23:29
        #define SCROLL_SHOW_500MS_CNT   3
        #define MAX_DISP_LEN            12
        #define SCROLL_STEP_LEN         4
        #define HL_LENGTH          240
        #define HL_HEIGHT          16
    #elif defined(FOLDER_FILE_LONGNAME)&&defined(HDD_SCROLLDISP) //zxb 2005-8-9 0:30
        #define SCROLL_SHOW_500MS_CNT   2
        #define MAX_DISP_LEN            12
        #define SCROLL_STEP_LEN         1
        #define HL_LENGTH          240
        #define HL_HEIGHT          16
    #else
        #define SCROLL_SHOW_500MS_CNT   2
        #define MAX_DISP_LEN            20
        #define SCROLL_STEP_LEN         4
        #define HL_LENGTH          240
        #define HL_HEIGHT          16
    #endif
    
    #ifdef SUPPORT_UNICODE_FONT
        UINT16 uFullFilename[128];  //total 256 bytes
    #else
        UINT8  uFullFilename[256];
    #endif
        
    UINT16 uFullFileLength;
    UINT8  uScrollDispFilenameSt;
    extern UINT8 uScrollDispFilenameFlag;
    extern UINT8 *wb_loc(UINT32 lsn, UINT32 offset);
    UINT8 GetFileFullName(int nIndex);
    UINT8 GetUDFFileFullName(int nIndex);
    void FS_ScrollDispFileName(void);
#endif  //#ifdef SUPPORT_FS_LONGNAME

#ifdef FS_LOAD_DIR_SEPARATELY  //SAVE_EACH_DIR_FILE_COUNT
void    FS_DirectoryFileCountInit(void);
UINT16  FS_DirectoryFileCountGetField(UINT32 uDirectoryOffset,int iType);
UINT16* FS_DirectoryFileCountGetEntry(UINT32 uIndex);
void    FS_DirectoryFileCountResetEntry(UINT32 uIndex);
void    FS_DirectoryFileCountCopyEntry(UINT32 uDestinationIndex,UINT32 uSourceIndex);
void    FS_DirectoryFileCountSetField(UINT32 uDirectoryOffset,UINT16 uValue,int iType);
void    FS_DirectoryFileCountAccumulateField(UINT32 uDirectoryOffset,UINT16 uAddingCount,int iType);
#endif  //#ifdef FS_LOAD_DIR_SEPARATELY

#endif //__FS9660.H
