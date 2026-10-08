#ifndef __FS_NEW_H
#define __FS_NEW_H

#define FS_ENABLE_WRITE
#define FS_REPLACE_OLD

enum
{
	error_none					= 0,
	error_USB_init				= 1 << 0,
	error_SD_MMC_init			= 1 << 1,
	error_unsupport_device		= 1 << 2,
	error_device_missed			= 1 << 3,
	error_device_write_protect	= 1 << 4,
	error_FS_init               = 1 << 5,
	error_FS_operation          = 1 << 6,
	error_drive_full            = 1 << 7,
	error_file_name             = 1 << 8,
	error_write                 = 1 << 9,
	error_allocation            = 1 << 10,
};

#define FS_NO_ERROR     (0)
#define FS_ERROR        (-1)
#define FS_DISK_FULL    (-2)
#define FS_FILE_ERROR   (-3)
#define FS_FILE_EOF     (-4)

#define FS_STRING_UTF16   (0)
#define FS_STRING_ASCII   (1)

#define FS_NODE_NULL    (0)
#define FS_NODE_ROOT    (1)
#define FS_NODE_FOLDER  (2)
#define FS_NODE_FILE    (3)
#define FS_NODE_OTHER   (4)

#define FS_FILE_READ    (0)
#define FS_FILE_WRITE   (1)

#define FS_BLOCKING_IO  (0) //blocking I/O
#define FS_NBLOCKING_IO (1) //non-blocking I/O

#define FS_SEEK_SET   (0) //start of file
#define FS_SEEK_CUR   (1) //current position
#define FS_SEEK_END   (2) //end of file

#define FS_FOLDER_DEPTH (6)
#define FS_NODE_SIZE    (16)

typedef struct {
    UINT8 value[FS_NODE_SIZE];
} API_NODE_T;

typedef struct {
} API_DRIVE_T;

typedef struct {
} API_FOLDER_T;

typedef struct {
} API_FILE_T;

/* ----------------------------------------------------------
fs_new Interface
---------------------------------------------------------- */
void    fs_reset(void);
void    fs_startup(UINT32 sAddr);
void    fs_shutdown(void);
int     fs_check_device(void);
int     fs_init_disk(void);
int     fs_get_device_type(void);
void    fs_remove_device(void);
int     fs_check_disk(void);
void    fs_polling_write(void);

API_DRIVE_T * fs_malloc_drive(void);
API_FOLDER_T * fs_malloc_folder(void);
API_FILE_T * fs_malloc_file(void);

void    fs_free_drive(API_DRIVE_T*);
void    fs_free_folder(API_FOLDER_T*);
void    fs_free_file(API_FILE_T*);

int     fs_mount_drive(API_DRIVE_T *pAPIDrive, UINT32 device);
void    fs_unmount_drive(API_DRIVE_T *pAPIDrive);
int     fs_mount_root(API_DRIVE_T *pAPIDrive, API_FOLDER_T *pAPIFolder);
void    fs_unmount_folder(API_FOLDER_T *pAPIFolder);
int     fs_parent_folder(API_FOLDER_T *pAPIFolder);

int     fs_get_node(API_FOLDER_T *pAPIFolder, API_NODE_T *pNode, char *nodeName);
int     fs_get_node_by_index(API_FOLDER_T *pAPIFolder, API_NODE_T *pNode, int indexNo);
int     fs_create_node(API_FOLDER_T *pAPIFolder, API_NODE_T *pNode, char *nodeName, int nodeType);
int     fs_enter_node(API_FOLDER_T *pAPIFolder, API_NODE_T *pNode);
int     fs_delete_node(API_FOLDER_T *pAPIFolder, API_NODE_T *pNode);

int     fs_file_open(API_FOLDER_T *pAPIFolder, API_FILE_T *pAPIFile, API_NODE_T *pNode, int mode);
int     fs_file_open2(API_DRIVE_T *pAPIDrive, API_FILE_T *pAPIFile, UINT32 start, UINT32 size);

UINT32  fs_file_getpos(API_FILE_T *pAPIFile);
int     fs_file_setpos(API_FILE_T *pAPIFile, UINT32 pos);
UINT32  fs_file_getsize(API_FILE_T *pAPIFile);
int     fs_file_seek(API_FILE_T *pAPIFile, int offset, int whence);

int     fs_file_read(API_FILE_T *pAPIFile, UINT8 *buf, UINT32 len, int mode);
int     fs_file_write(API_FILE_T *pAPIFile, UINT8 *buf, UINT32 len, int mode);
int     fs_file_close(API_FILE_T *pAPIFile);

/* ----------------------------------------------------------
fs_mem Interface
---------------------------------------------------------- */
typedef unsigned int size_t;
typedef unsigned int fs_mem_handle_t;

void    fs_mem_reset(UINT8 *sAddr);
fs_mem_handle_t fs_mem_allocate(size_t size);
void    *fs_mem_pointer(fs_mem_handle_t h);
void    fs_mem_free(fs_mem_handle_t h);

/* ----------------------------------------------------------
Defined in fs_new.c
---------------------------------------------------------- */
extern API_DRIVE_T * pReadDrive;
extern API_FOLDER_T * pReadFolder;
extern API_FILE_T * pReadFile;
extern API_FILE_T * pSubFile;

extern UINT32 subStLBA; 

#endif //__FS_NEW_H

