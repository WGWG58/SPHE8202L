#ifndef __PLAYMODE_H
#define __PLAYMODE_H

void FSNav_HDDInit();
void FSNav_InitPartion();
//int  HDDPreLoop(void);//kenny mark it 2005/6/6

void Refresh(BYTE copy_process);

void HDDCard_down(void);
void HDDCard_return(void);
void HDDCard_select(void);
void HDDCard_up(void);

void FSGUI_Partition_Menu(void);
void FSShowFatIcon(UINT16 xStart,UINT16 yLoc);//liweihua mod 2004-11-16
void ShowHDDItem(UINT16 xStart,int iItem, const char *s, BYTE flag);
void ShowCurrentMultiPart(void);

#ifdef FAT_FILE_MODE
void HDDCard_left(void);
void HDDCard_right(void);
void ShowCardItem(int iItem, const char *s, BYTE flag);
void ShowWarning(const char *s);
#endif

extern void  show_card_reading_osd(BYTE type);
//extern int CardReadMBR(void);
extern int FSReadMBR(void);
extern UINT8 IdeGetSequence(void);
extern void IdeSetSequence(UINT8 sequence);
extern void SwitchMedia(BYTE direction);
extern int  CardStorageIsPlugIn(); 
//extern void CardGetInfo(void);
extern void FSGetInfo(void);
extern void invalid_key(void);
extern void read_iso9660_gui_disp(BYTE *bShow);

#endif//#ifndef __PLAYMODE_H

