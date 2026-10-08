#ifndef __FILEMODE_H
#define __FILEMODE_H


void Draw_File_Mode_Menu(void);
void HDD_Card_List(void);
void Draw_Mode_Menu(void);
void Disk_FileMode_DirList(UINT16 iDirIndex);
void Card_FileMode_DirList(UINT16 iDirIndex);
void Draw_FAT_Mode_GUI(void);
void FSGUI_Refresh_Disk(void);
void FSGUI_Refresh_Card(void);
void ShowItem(int hl_index);
void FSShowFileIcon(UINT16 index, BYTE area, int yLoc);
void FSGUI_FileMode_Init(void);
void show_fat_mode_select_menu(void);
UINT16 JudgeDir(INT16 iDirIndex);
UINT16 JudgeDelDir(UINT16 iDirIndex ,UINT16 del_file_index);
UINT16 GetParentDir(UINT16 sub_dir);
void FAT_File_Mode_Nav_MainLoop(void);
void CardCopyFile2HD(UINT16 iCardFileIndex, UINT16 iHddDirIndex);
void CardCopyDir2HD(UINT16 iCardDirIndex, UINT16 iHddDirIndex);
void FATCopy(void);
void CardCopy(void);
void AddHddFileStru(UINT32 lba, UINT16 iParentDir, UINT16 iCardFileIndex);
UINT16 AddHddDirStru(UINT32 lba, UINT16 iParentDir, char name[12]);

//2006-06-02, mimitsai add for HD ui.
extern void ClearRectArea(BTNAREA  Rect, UINT16 RectColorStep, UINT8 Y_1, UINT8 Y_2, UINT16 CbCr,int iIndex,int iItem);
extern void DrawRectCorner( BTNAREA  Rect, int CornerRad,  BYTE updown, UINT8 step, BYTE Y_1, BYTE Y_2, UINT16 CbCr);

extern void DrawRect(int x, int y, int xSize, int ySize, UINT16 selected, UINT16 color_Y, UINT16 color_CrCb);
extern void DrawFolderIcon(int x, int y, BYTE type);
extern void ShowHL(void);
extern int PMP_CF_Card_IsPlugIn();
#endif


