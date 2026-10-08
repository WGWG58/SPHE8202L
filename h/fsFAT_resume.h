#ifndef __FSFAT_RESUME_H__
#define __FSFAT_RESUME_H__


/****************************************************************************************\
**                                    type definition                                   **
\****************************************************************************************/
//resume information structure, for saving use
typedef struct {
    BYTE shortName[12]       __attribute__ ((packed));   //short name
    BYTE fileSize[4]         __attribute__ ((packed));   //in Byte
} FATFS_RSM_INFO_SAVE_T;

//original
typedef struct {
    BYTE   short_name[12]    __attribute__ ((packed));   //short name
    UINT32 file_size         __attribute__ ((packed));   //in Byte
} FATFS_RSM_INFO_T;


/****************************************************************************************\
**                                       Micros                                         **
\****************************************************************************************/
#define EEPROM_DEV_ADDR             ( 0xa0 )
#define FATFS_RSM_INFO_SAVE_ADDR    ( 255 - sizeof( FATFS_RSM_INFO_SAVE_T ) )


/****************************************************************************************\
**                           gloable variable declaration                               **
\****************************************************************************************/
extern int g_fsFatRsmCnt;
extern int g_iRsmFileIdx;


/****************************************************************************************\
**                                Function Declaration                                  **
\****************************************************************************************/
extern int  fsFatRsm_search_rsm_file( void );
extern int  fsFatRsm_get_curr_file_nav_dir_now( int iRsmFileIdx );
extern void print_dir_file_info( void );
extern void fsFatRsm_rec_rsm_info( void );
//extern void polling_rec_fat_rsm_info( void );
extern void fsFatRsm_fsgui_select_file( int iRsmFileIdx );
extern void fsFatRsm_clear_eeprom_save_area( UINT32 uiAddr );


#endif //__FSFAT_RESUME_H__


