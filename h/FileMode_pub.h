#ifndef   __FILEMODE_PUB_H
#define   __FILEMODE_PUB_H
#ifdef FILE_MODE_WRITE
//********************************************************************************************//
//*                                                                                          *//
//*                                  FileMode_pub.c related                                  *//
//*                                                                                          *//
//********************************************************************************************//
//***********************************¡¾ enumeration section ¡¿********************************//
//File System support
enum
{
    CARD_FAT_UNKNOWN=0,
    CARD_FAT12=1,
    CARD_FAT16=2,
    CARD_FAT32=3,
};
//************************************¡¾ micro definition ¡¿**********************************//
//size of FDB
#define FDBSIZE 32

//pFsJpeg->copy_dir_file
#define COPY_DIR  1  //copy dir
#define COPY_FILE 2  //copy file

//buffer.
#define DirFileCount1  ((UINT16*)(SDRAM_BASE + INDEX_BUF_SRC_YA * 1024))
#define DirFileCount2  ((UINT16*)(SDRAM_BASE + INDEX_BUF_DES_YA * 1024))
//************************************¡¾ function section ¡¿**********************************//
void FATCopy(void);
void CreateDir(void);
void FATDelete(void);
void RenameFileDir(void);
void FileModeGetInfo(void);
void StorageGetCapacityInfo(void);
void Switch2SrcDesBuf(BYTE SrcOrDes);
void FATDeleteDir (UINT16 iDirIndex);
void FATDeleteFile(UINT16 iFileIndex);
void RenameFile(char *foldername, DIR_REC *OriFileInfo);
void SrcCopyDir2Des(UINT16 iSrcDirIndex, UINT16 iDesDirIndex);
void SrcCopyFile2Des(UINT16 iSrcFileIndex, UINT16 iDesDirIndex);
void AddDesFileStru(UINT32 lba, UINT16 iParentDir, UINT16 iSrcFileIndex);
UINT16 GetParentDir(UINT16 sub_dir);
UINT16 JudgeDelDir(UINT16 iDirIndex ,UINT16 del_file_index);
UINT16 AddDesDirStru(UINT32 lba, UINT16 iParentDir, char name[12]);
//********************************************************************************************//
//*                                                                                          *//
//*                                  FileModeGUI_pub.c related                               *//
//*                                                                                          *//
//********************************************************************************************//
//************************************¡¾ micro definition ¡¿**********************************//
//Color Mix Table, RGB to YCbCr arithmetic & so on
#define RGB2Y(r,g,b)      (((71*(r) + 141*g + 27*b + 0x1000)&0xFF00)>>8)
#define RGB2Cr(r,g,b)     (((127*(r)-106*(g)-21*(b)+0x8000)&0xFF00)>>8)
#define RGB2Cb(r,g,b)     ((((-43)*(r)-85*(g)+127*(b)+0x8000)>>8)&0xFF)
#define RGB2CrCb(r,g,b)   (((127*(r)-106*(g)-21*(b)+0x8000)&0xFF00)|((((-43)*(r)-85*(g)+127*(b)+0x8000)>>8)&0xFF))

#define __palette4F(G,B,R,A)  (((UINT32)((G)&0xff)<<24)|((UINT32)((B)&0xff)<<16)|((UINT32)((R)&0xff)<<8)|(A&0xff)) 

#define	FUNCTION_REGION	3
#define	MESSAGE_REGION	2
#define OSD_FONT_HEIGHT 24

#define COLOR_LBLUE         0
#define	COLOR_WHITE         2
#define	COLOR_GRAY          3
#define	COLOR_DBLUE         4
#define	COLOR_YELLOW	    7
#define	COLOR_YELLOWGREEN   9
#define COLOR_GREEN         13
#define	COLOR_GRAYWHITE     14

//progress bar related
#define FS_BOTTOM_AREA_X_START 20
#define FS_BOTTOM_AREA_Y_START 237
#define FS_BOTTOM_AREA_X_SIZE  300
#define FS_BOTTOM_AREA_Y_SIZE  50

//flags of control areas
#define SRCE 0
#define DEST 1
//************************************¡¾ function section ¡¿**********************************//
int  Media_detect(void);
void ButtonNew(void);
void ButtonCopy(void);
void input_page(void);
void ButtonDelete(void);
void ButtonFormat(void);
void ButtonRename(void);
void FileModeGUI_up(void);
void ButtonCapacity(void);
void FileModeMainLoop(void);
void FileModeGUI_down(void);
void FileModeGUI_left(void);
void FileModeGUI_play(void);
void ShowCapacityInfo(void);
void FileModeGUI_right(void);
void input_str_func_up(void);
void input_str_clear_HL(void);
void FileModeGUI_select(void);
void FileModeGUI_return(void);
void Draw_FileMode_Menu(void);
void input_str_func_exit(void);
void input_str_func_left(void);
void input_str_func_down(void);
void FileModeGUI_Refresh(void);
void FileModeSwitchMedia(void);
void FSGUI_FileMode_Init(void);
void DrawProgressBarInit(void);
void input_str_func_enter(void);
void input_str_func_right(void);
void ShowWarning(const char *s);
void FileModeJudgeSelMedia(void);
void Draw_File_Mode_Button(void);
void input_str_func_select(void);
void show_fat_dir_file_info(void);
void input_str_clear_variable(void);
void FileMode_DirList(UINT16 iDirIndex);
void input_HL_ItemStr(BYTE itemstr_index);
void FSShowFatIcon(UINT16 xStart,UINT16 yLoc);
void ShowFileItem(UINT16 xStart,int hl_index);
void MediaItem_List(UINT16 xStart,BYTE media_flag);
void FSShowFileIcon(UINT16 index, BYTE area, int yLoc);
void ShowSrceItem(UINT16 xStart,int iItem, const char *s);
UINT16 JudgeDir(INT16 iDirIndex);

#endif //FILE_MODE_WRITE
#endif //#define __FILEMODE_PUB_H
