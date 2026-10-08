#ifdef FILE_MODE_WRITE
#include "user_init.h"
#include "global.h"
#include "kinf.h"
#include "osd.h"
#include "fs96602.h"
#include "fsNAV.h"
#include "cardfs.h"
#include "memmap0.h"
#include "util.h"
#include "playmode.h"

//for USB & CARD information
UINT32 uiUsedCapacity;
UINT32 uiRemainCapacity;
UINT32 uiTotalCapacity;
extern UINT8  MaxLUN;
extern UINT32 zeroFAT_cnt;
BYTE   copy_dir_or_file;//copy dir or file,COPY_DIR or COPY_FILE
UINT64  current_dir_size;//selected dir size,in sector,added by wangwei,2005-1-21 10:50
UINT64  dir_copied_size;//copied size of current dir.

//functions
extern UINT32 UsbTestReady(void);
extern int FSSearchFile(UINT32, char*);
extern int DetectUdiskIsProtect(void);

CARD_INFO  *cardDes;
extern CARD_INFO       cardP;
extern CARD_FILE       cardFile;

#ifndef DVDRELEASE
#define FILE_MODE_WRITE_DBG  1
#endif

#define	D	printf("INFO: __%d__(%s:%s)\n",__LINE__,__FILE__,__FUNCTION__);

#ifndef FILE_MODE_WRITE_DBG
    #undef printf
    #undef print_block
    #define printf(f, a...) do {} while (0)
    #define print_block(x,y) do {} while (0)
#endif

/****************************************************************************************\
 *                                                                                       *
 *  Function Name : AddDesFileStru                                                       *
 *                                                                                       *
 *  Purposes      : add the copied file struction                                        *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void AddDesFileStru(UINT32 lba, UINT16 iParentDir, UINT16 iSrcFileIndex)
{
    printf("=================AddDesFileStru======================\n");     
    int i,file_type;
    char name[12];
    UINT16 file_index;
    UINT32 file_size;
    
    //switch to src pFsJpeg,fs9660dir and fs9660file buf         
    Switch2SrcDesBuf(SRCE);
    
    for(i=0;i<12;i++)
        name[i]=iso9660_file[iSrcFileIndex].name[i];
    file_type = iso9660_file[iSrcFileIndex].file_type;
    file_size = iso9660_file[iSrcFileIndex].size;
    
    //switch to des pFsJpeg,fs9660dir and fs9660file buf      
    Switch2SrcDesBuf(DEST);
    
    printf("======pFsJpeg->iso9660_file_cnt=%d=========\n",pFsJpeg->iso9660_file_cnt);
    printf("======DirFileCount2[0]=%d=========\n",DirFileCount2[0]);
    printf("======DirFileCount2[1]=%d=========\n",DirFileCount2[1]);
    printf("======pFsJpeg->file_count_in_dir=%d=========\n",pFsJpeg->file_count_in_dir);
   
    if(pFsJpeg->iso9660_file_cnt==0)
    {
        file_index = 0;
    }   
    else
    {
        printf("====i:%d==DirFileCount2[pFsJpeg->file_count_in_dir-1]===%d======\n",pFsJpeg->file_count_in_dir-1,DirFileCount2[pFsJpeg->file_count_in_dir-1]);
        file_index = DirFileCount2[pFsJpeg->file_count_in_dir-1]+1;
        if(file_index>ISO_FILE_MAX)
        {
            file_index-=ISO_FILE_MAX;
        } 
        printf("======file_index===%d======\n",file_index);    
    }
    pFsJpeg->iso9660_file_cnt++;
    
    for(i= pFsJpeg->iso9660_file_cnt-1;i>file_index;i--)
        iso9660_file[i]=iso9660_file[i-1];
        
        
    pFsJpeg->file_count_in_dir++;
    DirFileCount2[pFsJpeg->file_count_in_dir-1]=file_index;
    
    iso9660_file[file_index].loc = lba;            
    iso9660_file[file_index].dir = 0;
    iso9660_file[file_index].parent_dir = iParentDir;
    iso9660_file[file_index].size = file_size;
    for(i=0;i<12;i++)
        iso9660_file[file_index].name[i] = name[i];
    iso9660_file[file_index].file_type = file_type;
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : AddDesDirStru                                                        *
 *                                                                                       *
 *  Purposes      : Add des dir structure                                                *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
UINT16 AddDesDirStru(UINT32 lba, UINT16 iParentDir, char name[12])
{
    printf("=================AddDesDirStru======================\n");     
    UINT16 dir;
    int i;
    //switch to des pFsJpeg,fs9660dir and fs9660file buf      
    Switch2SrcDesBuf(DEST);
        
    pFsJpeg->iso9660_dir_cnt++;
    iso9660_dir[pFsJpeg->iso9660_dir_cnt-1].loc = lba;
    iso9660_dir[pFsJpeg->iso9660_dir_cnt-1].dir = 0;
    iso9660_dir[pFsJpeg->iso9660_dir_cnt-1].parent_dir = iParentDir;
    
    for(i=0;i<12;i++)
        iso9660_dir[pFsJpeg->iso9660_dir_cnt-1].name[i] = name[i];
    
    dir = pFsJpeg->iso9660_dir_cnt-1;
    return dir;
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : SrcCopyFile2Des                                                      *
 *                                                                                       *
 *  Purposes      : Copy file from source media to destination media.                    *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
extern char    OriFileName[200][12];
void SrcCopyFile2Des(UINT16 iSrcFileIndex, UINT16 iDesDirIndex)
{
    UINT32	lba;
    UINT32 filelen,fileloc;
    char *filename;
    //int i;
    
    //get the location and length of selected file from src
    fileloc = iso9660_file[ iSrcFileIndex ].loc;
    filelen = iso9660_file[ iSrcFileIndex ].size;
    filename = iso9660_file[ iSrcFileIndex ].name;
    
    //init current file (des)information 
    cardFile.stLBA = msf2l(fileloc);
    cardFile.stClus = FSLBA2Clus(cardFile.stLBA);
    cardFile.iFileSize = filelen;
    cardFile.curLBA = cardFile.stLBA;
    cardFile.curClus = cardFile.stClus;
    cardFile.iLeaveSize = cardFile.iFileSize;
    #if 0
    printf("Copy file from Src to Des:\n");
    printf("---------the file location in Src is 0x%x\n",cardFile.stLBA);
    printf("---------the file size in Src is 0x%x\n",filelen);
    #endif
    
    //switch to des pFsJpeg,fs9660dir and fs9660file buf      
    Switch2SrcDesBuf(DEST);
    
    lba=FSGetRoot();
    //*cardDes = cardP;//important!
    
    //if copy to dir in HDD,get the dir's location
    if(iDesDirIndex != 0)
    {
        lba = msf2l(iso9660_dir[iDesDirIndex].loc);
    }

    if(FSSearchFile(lba,filename))
    {        
        ShowWarning("THE DIR IS ALREADY EXISTED.");       
        return;
    }
    else
    {
        if(copy_dir_or_file == COPY_FILE)
        {
            DrawProgressBarInit(); 
        }

    //switch to src pFsJpeg,fs9660dir and fs9660file buf         
    Switch2SrcDesBuf(SRCE);
    //wanghaoying delete the block 2005-7-13 16:25, for no name copied file
    //for(i=0;i<12;i++)
    //{
    //    iso9660_file[iSrcFileIndex].name[i]=OriFileName[iSrcFileIndex+1][i];
    //}
    //printf("===============iso9660_file[iSrcFileIndex].name%s=====================================\n",iso9660_file[iSrcFileIndex].name );
    
    //write file and get the file loc 
    lba = FSCopyFile(lba,&(iso9660_file[iSrcFileIndex]));
    printf("===============lba %d=====================================\n",lba );
  
    AddDesFileStru(l2msf(lba), iDesDirIndex, iSrcFileIndex);
}
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : GetParentDir                                                       *
 *                                                                                       *
 *  Purposes      : Get parent dir of sub dir.                                           *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
UINT16 GetParentDir(UINT16 sub_dir)
{
    UINT16 parent_dir;
    parent_dir=iso9660_dir[sub_dir].parent_dir;
    return parent_dir;
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : SrcCopyDir2Des                                                       *
 *                                                                                       *
 *  Purposes      : Copy dir from source media to destination media .                    *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void SrcCopyDir2Des(UINT16 iSrcDirIndex, UINT16 iDesDirIndex)
{
    printf("===============SrcCopyDir2Des()================================\n");
    UINT32 lba;
    UINT16 count;
    char *dirname;
    int i;
	UINT16 srcdirindex[MAX_SUBDIR_NUM];//frankhuang add to store subdir index to copy
	UINT16 subdirnum=0;
    //switch to src pFsJpeg,fs9660dir and fs9660file buf         
    Switch2SrcDesBuf(SRCE);
	pFsJpeg->file_array[pFsJpeg->dir_current]=iSrcDirIndex;//frank.huang add to support copy dir with date&time info 050905
    dirname=iso9660_dir[iSrcDirIndex].name;
    printf("======FSCreateDir=========dirname===%s====================\n",dirname);
    
    
    //switch to des pFsJpeg,fs9660dir and fs9660file buf      
    Switch2SrcDesBuf(DEST);
    
    
    lba=FSGetRoot();
    printf("======lba=FSGetRoot()=========lba %d==========================\n",lba );
    //*cardDes = cardP;//important!
    printf("===============iDesDirIndex %d======================\n",iDesDirIndex );
    //get the location of dir we will copy to
    if(iDesDirIndex != 0)
    {
        //lba = iso9660_dir[iDesDirIndex].loc;
        lba = msf2l(iso9660_dir[iDesDirIndex].loc);
        printf("======msf2l(====lba %d===================================\n",lba );
    }
    
    if(FSSearchDir(lba,dirname))
    {        
        printf("===============FSSearchDir()================================\n");
        ShowWarning("THE DIR IS ALREADY EXISTED.");       
        return;
    }
    else
    {
        printf("===============FSCreateDir()================================\n");
        //create the copied dir and get the new dir's location
        lba = FSCreateDir(lba, dirname);                 
        iDesDirIndex = AddDesDirStru(l2msf(lba), iDesDirIndex, dirname);
    }
    
    //added by wangwei,2004-12-21 11:05(to avoid the back rut of the progress bar blinking.)
    DrawProgressBarInit(); 
    
    //switch to src pFsJpeg,fs9660dir and fs9660file buf         
    Switch2SrcDesBuf(SRCE);
    pFsJpeg->ControlArea = CNT_AREA_SRCE;   
    
    count = JudgeDir(iSrcDirIndex);    
    //whb move to FATCopy() in order not to copy empty dir
    //if(count==1)       //sunzhh add for copying empty dir 2005-1-27
    //{
    //    BYTE copy_process = 100;
    //    Refresh(copy_process);
    //}
    //else
        
    //write the subdir and file in dir
    for(i = 1; i < count; i++)
    {
        if(DirFileCount1[i] < ISO_FILE_MAX)
        {                  
            printf("===============FSCreateDir()=======file=========================\n");     
            SrcCopyFile2Des(DirFileCount1[i], iDesDirIndex);
        }
        else if(DirFileCount1[i] > ISO_FILE_MAX)
        {            
            printf("===============FSCreateDir()========dir========================\n");    
            if(iso9660_dir[DirFileCount1[i]-ISO_FILE_MAX].dir)
            {
	            srcdirindex[subdirnum]=(DirFileCount1[i]-ISO_FILE_MAX);
				if(subdirnum<MAX_SUBDIR_NUM)
					subdirnum++;
            }
            else
            {
 				//SrcCopyDir2Des((DirFileCount1[i]-ISO_FILE_MAX),iDesDirIndex);//frank.huang 050905 mark bucause subdir will be copied after files copied
				srcdirindex[subdirnum]=(DirFileCount1[i]-ISO_FILE_MAX);
                if(subdirnum<MAX_SUBDIR_NUM)
					subdirnum++;
			}
        }
    }
	if(subdirnum)//frank.huang add 050905 to copy subdir
	{
		for(i=0;i<subdirnum;i++)
		{	
			SrcCopyDir2Des(srcdirindex[i],iDesDirIndex);
		}
    }
    
}

/****************************************************************************************\
 *                                                                                       *
 *  Function Name : FATDelete                                                            *
 *                                                                                       *
 *  Purposes      : Delete destination media files or dir                                *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void FATDelete(void)
{
    printf("=================FATDelete()=================\n");  
    UINT16 index,current_dir_index;
    int Res;
    //switch to des pFsJpeg,fs9660dir and fs9660file buf      
    Switch2SrcDesBuf(DEST);
   
        index = pFsJpeg->file_current_in_page + PER_PAGE*( pFsJpeg->file_page_index);
    printf("======1====index %d===================================\n",index );
        index = DirFileCount2[index];
    printf("======2====index %d===================================\n",index );
    
    
    if(index > ISO_FILE_MAX)
    {
        printf("=================DeleteDir=================\n");  
            ShowWarning("DELETING DIR...");
            FATDeleteDir(index-ISO_FILE_MAX);
            ShowWarning("DELETING DIR IS OK.");
        }
        else if(index < ISO_FILE_MAX)
        {
        printf("=================DeleteFile==================\n");  
            ShowWarning("DELETING FILE...");
            FATDeleteFile(index);
            ShowWarning("DELETING FILE IS OK.");
        }
        else if(index == ISO_FILE_MAX)
        {
        printf("=================invalid_key()=================\n");  
            invalid_key();
            return;   
        }
    current_dir_index = pFsJpeg->dir_current;
    ReadFile(&Res);
    pFsJpeg->dir_current = current_dir_index;
    pFsJpeg->file_index_in_dir--;
    if(pFsJpeg->file_current_in_page > 0)
        pFsJpeg->file_current_in_page--;
    else
    {
        pFsJpeg->file_current_in_page = PER_PAGE-1;
        pFsJpeg->file_page_index--;    
    }            
    FileModeGUI_Refresh();
    FileMode_DirList(current_dir_index);                            
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : FATDeleteFile                                                        *
 *                                                                                       *
 *  Purposes      : Delete destination media files                                       *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void FATDeleteFile(UINT16 iFileIndex)
{
	//UINT32	lba;
	
	//lba=FSGetRoot();
	FSDeleteData(&(iso9660_file[iFileIndex])); 
}

/****************************************************************************************\
 *                                                                                       *
 *  Function Name : FATDeleteDir                                                         *
 *                                                                                       *
 *  Purposes      : Delete destination media  dir                                        *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void FATDeleteDir (UINT16 iDirIndex)
{
    //UINT32 lba;
    //UINT16 i,file_cnt = 0;
    //UINT16 index;
    //lba = FSGetRoot ();
    
    FSDeleteData( &(iso9660_dir[iDirIndex]) );
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : JudgeDir                                                             *
 *                                                                                       *
 *  Purposes      :                                                                      *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/

UINT16 JudgeDir(INT16 iDirIndex)
{
    int i,j = 0;
    
    if(1)//set parent path flag for subdir
    {
        if(pFsJpeg->ControlArea == CNT_AREA_SRCE)
            DirFileCount1[j] = ISO_FILE_MAX;//flag as path to parent dir
        else if(pFsJpeg->ControlArea == CNT_AREA_DEST)        
            DirFileCount2[j] = ISO_FILE_MAX;//flag as path to parent dir
        j++;
    }
    
    for (i = 1; i < pFsJpeg->iso9660_dir_cnt; i++)//skip No.0 dir
    {
        if((iso9660_dir[i].parent_dir == iDirIndex))
        {
           if(pFsJpeg->ControlArea == CNT_AREA_SRCE)
                DirFileCount1[j] = i + ISO_FILE_MAX;//flag as path to parent dir
            else if(pFsJpeg->ControlArea == CNT_AREA_DEST)  
            {
                DirFileCount2[j] = i + ISO_FILE_MAX;
                printf("=====1====DirFileCount2[%d]:%d=============\n",j,DirFileCount2[j]);
            }
			j++;
        }
    }
    for(i = 0; i < pFsJpeg->iso9660_file_cnt; i++)
    {
        if((iso9660_file[i].parent_dir == iDirIndex ))
        {
            if(pFsJpeg->ControlArea == CNT_AREA_SRCE)
            {
                DirFileCount1[j] = i ;//flag as path to parent dir
                current_dir_size += iso9660_file[i].size;
            }
            else if(pFsJpeg->ControlArea == CNT_AREA_DEST) 
            {
                DirFileCount2[j]= i;
                printf("=====2====DirFileCount2[%d]:%d=============\n",j,DirFileCount2[j]);
            }
			j++;
        }
    }  
    return j;    
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : JudgeDelDir                                                          *
 *                                                                                       *
 *  Purposes      : Calculate the deleted dir contain the count of dir and files.        *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
UINT16 JudgeDelDir(UINT16 iDirIndex ,UINT16 del_file_index)
{
    UINT16 i,j ;
    j = del_file_index;
    printf("\n================JudgeDelDir==============================\n");

    for (i = 0; i < pFsJpeg->iso9660_dir_cnt; i++)
    {
        if(iso9660_dir[i].parent_dir == iDirIndex)//find the sub-dir in the current dir
        {
                DirFileCount2[j] = i + ISO_FILE_MAX;
            printf("dir-----DirFileCount2[%d]= %d\n",j,(i+ISO_FILE_MAX));
            j++;
            j = JudgeDelDir( i, j );
        }
    }

    for(i = 0; i < pFsJpeg->iso9660_file_cnt; i++)
    {
        if((iso9660_file[i].parent_dir == iDirIndex ))//find the files in the current dir
        {
                DirFileCount2[j]= i;
			printf("file-----DirFileCount2[%d]= %d\n",j,i);
			j++;
        }
    }
    return j;

}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : FATCopy                                                              *
 *                                                                                       *
 *  Purposes      : Calculate the deleted dir contain the count of dir and files.        *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void FATCopy(void)
{
    UINT16 dircount;
    UINT64 dirsize;
    int i;
    
    printf("=================FATCopy()=================\n");  
    UINT16 src_file_index,des_dir_index,current_dir_index;      
    BYTE   UdiskWP; 
    int Res;            
    if(storage_type == USB_DEVICE)
	{
	    UdiskWP=DetectUdiskIsProtect();
	    if(UdiskWP)   
	    {
	        printf("=================udisk protect=================\n");  
	        ShowWarning("UDISK PROTECTED");      
	        return; 
	    }  
		 
	}
    media_type = MEDIA_CD ;//lijd 2005-1-18 17:11 
    //switch to des pFsJpeg,fs9660dir and fs9660file buf      
    Switch2SrcDesBuf(DEST);
    des_dir_index = pFsJpeg->dir_current;
    printf("+++++++++ pFsJpeg->dir_current = %x+++++++++\n",pFsJpeg->dir_current);
    
    //switch to src pFsJpeg,fs9660dir and fs9660file buf         
    Switch2SrcDesBuf(SRCE);
    
    //get the file/dir index of card we will copy
    src_file_index = pFsJpeg->file_current_in_page + PER_PAGE*( pFsJpeg->file_page_index);
    src_file_index = DirFileCount1[src_file_index];
	
    if(src_file_index> ISO_FILE_MAX)//copy dir 
    {
	//whb modified
     /* judge dir and get remain capacity of U disk:
            dir is empty: do not copy & ShowWarning
            dir is not empty:
                total size of dir is less than remain capacity of U disk:  copy 
                else:  do not cooy & ShowWarning
     */
     
        dircount = JudgeDir( (src_file_index-ISO_FILE_MAX) );    
        if(dircount==1)
        {
            ShowWarning("EMPTY DIR."); 
        }
        else
        {
            dirsize = 0;
            for(i = 1; i < dircount; i++)
            {
            if(DirFileCount1[i] < ISO_FILE_MAX)
                dirsize += (iso9660_file[ DirFileCount1[i] ].size);
            }
        
            FSGetRoot();
            FSJudgeFAT();
         
            if( dirsize < (zeroFAT_cnt * cardP.secPerClus * 512) )
    {
        ShowWarning("COPYING DIR...");        
        current_dir_size = 0;
        dir_copied_size = 0;
        copy_dir_or_file = COPY_DIR;
        SrcCopyDir2Des((src_file_index-ISO_FILE_MAX), des_dir_index);       
        current_dir_size = 0;
        dir_copied_size = 0;
        copy_dir_or_file = 0;
        ShowWarning("COPYING DIR IS OK.");                                      
                FSGUI_FillFrameBuf(FS_BOTTOM_AREA_X_START, FS_BOTTOM_AREA_Y_START,FS_BOTTOM_AREA_X_SIZE, FS_BOTTOM_AREA_Y_SIZE, BK_GROUNDY, BK_CRCB);
        Switch2SrcDesBuf(SRCE);
        FileModeGUI_Refresh();
        FileMode_DirList(iso9660_dir[src_file_index - ISO_FILE_MAX].parent_dir);
            }
            else
            {
            	FileMode_DirList(iso9660_dir[src_file_index - ISO_FILE_MAX].parent_dir);
                ShowWarning("SORRY. NO ENOUGH CAPACITY");
            }
        }
        
    }
    else if(src_file_index < ISO_FILE_MAX)//copy file
    {
//whb modified          
/*
get remain capacity of U disk:
    file size is less than remain capacity of U disk:  copy 
    else:  do not cooy & ShowWarning
*/       
       FSGetRoot();
       FSJudgeFAT();
       
       if( (iso9660_file[ src_file_index ].size) < (zeroFAT_cnt * cardP.secPerClus * 512) )
       {
            ShowWarning("COPYING FILE...");      
            copy_dir_or_file = COPY_FILE;
            printf("========src_file_index=%d\n",src_file_index); 
            printf("========des_dir_index=%d\n",des_dir_index);     
            SrcCopyFile2Des(src_file_index, des_dir_index);     
            ShowWarning("COPYING FILE IS OK.");
            FSGUI_FillFrameBuf(FS_BOTTOM_AREA_X_START, FS_BOTTOM_AREA_Y_START,FS_BOTTOM_AREA_X_SIZE, FS_BOTTOM_AREA_Y_SIZE, BK_GROUNDY, BK_CRCB);
        }
        else
            ShowWarning("SORRY. NO ENOUGH CAPACITY");
    }
    else
    {
        invalid_key();
        return;  
    }

    Switch2SrcDesBuf(DEST);
    
    FileModeJudgeSelMedia();
    if(media_type == MEDIA_CARD)
    {
        BYTE n;
        n = pFsJpeg->media_will;     //to avoid pFsJpeg->media_will being changed
        CardTestReady();             
        FileModeGetInfo();
        pFsJpeg->media_will = n;
    }
    else if(media_type == MEDIA_CD)
    {
        media_type = MEDIA_CD;
        LoadModual(MODUAL_CDROM);
        sys_cmd=(CMD_FUNC|CMD_FUNC_CLOSE);
        ReadCDTitle();
        system_state=SYSTEM_SETUP_BROWSER;          
    }             
    current_dir_index = pFsJpeg->dir_current;
    ReadFile(&Res);
    pFsJpeg->dir_current = current_dir_index;
      
    FileModeGUI_Refresh();
    show_fat_dir_file_info();
    FileMode_DirList(des_dir_index);                                   
}

/****************************************************************************************\
*                                                                                        *
*  Function Name : StorageGetCapacityInfo                                                *
*                                                                                        *
*  Purposes      : get the the capacity informations of the storage.                     *
*                                                                                        *
*  Descriptions  : get the the capacity informations of the storage.                     *
*                                                                                        *
*  Arguments     : (none)                                                                *
*                                                                                        *
*  Returns       : (none)                                                                *
*                                                                                        *
*  See also      : Creator : wangwei,2004-11-15 21:07                                    *
*                                                                                        *
\****************************************************************************************/
void StorageGetCapacityInfo(void)
{
    if(storage_type == USB_DEVICE)
    {
        MaxLUN=0;
        UsbTestReady();
    }
    else
        CardTestReady();

    FSGetRoot();
    FSJudgeFAT();

    if(storage_type == USB_DEVICE)
    {
        uiTotalCapacity  = uiTotalCapacity>>20;//in Mega
        uiRemainCapacity = (zeroFAT_cnt * cardP.secPerClus * 512) >> 20;//in Mega
    }

    #ifdef SPHE8202_ALL_TYPE_CARD_WRITE	//dingzhy
    uiTotalCapacity  = card_uiTotalCapacity;
    uiRemainCapacity = (zeroFAT_cnt * cardP.secPerClus * 512) / 1024000;
    #endif
    
    uiUsedCapacity = uiTotalCapacity - uiRemainCapacity;//in Mega
    
    #ifdef FILE_MODE_WRITE_DBG
    printf("zeroFAT_cnt     =%dCluster\n",zeroFAT_cnt);
    printf("cardP.secPerClus=%dSector/Cluster\n",cardP.secPerClus);
    printf("total capacity  =%dM\n",uiTotalCapacity);
    printf("used capacity   =%dM\n",uiUsedCapacity);
    printf("uiRemainCapacity=%dM\n",uiRemainCapacity);
    #endif
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : CreateDir                                                            *
 *                                                                                       *
 *  Purposes      : Create Dir                                                           *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void CreateDir(void)
{
    printf("==================== CreateDir IN!!!===================^\n");

    UINT32 lba;
    UINT16 des_dir_index;

    //switch to destination related buffer
    Switch2SrcDesBuf(DEST);

    des_dir_index = pFsJpeg->dir_current;
    printf("+++++++++ pFsJpeg->dir_current = %x+++++++++\n",pFsJpeg->dir_current);

    //root dir's lba
    lba = FSGetRoot();

    //selected dir's lba
    if(des_dir_index != 0)// ! root dir
    {
        lba = msf2l(iso9660_dir[des_dir_index].loc);
        printf("+++++++++++++++ iso9660_dir[des_dir_index].name = %s +++++++++++++++++\n",iso9660_dir[des_dir_index].name);
        printf("+++++++++++++++ lba = %x +++++++++++++++++\n",lba);
    }

    printf("+++++++++++++++ created dir name = %s +++++++++++++++++\n",GetString);

    if(FSSearchDir(lba, GetString))//check same name dir
    {
        //ShowWarning("THE DIR IS ALREADY EXISTED.");
        printf("================= THE DIR IS ALREADY EXISTED.===============\n");
        return;
    }
    else//create the new dir
    {
        lba = FSCreateDir(lba, GetString);
        AddDesDirStru(l2msf(lba), des_dir_index, GetString);
        printf("+++++++++++++++ des_dir_index = %x +++++++++++++++++\n",des_dir_index);
    }
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : RenameFileDir                                                        *
 *                                                                                       *
 *  Purposes      : Rename file or dir                                                   *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void RenameFileDir(void)
{
    UINT32 lba;
    UINT16 index, des_dir_index;

    //switch to destination related buffer
    Switch2SrcDesBuf(DEST);

    index = pFsJpeg->file_current_in_page + PER_PAGE*( pFsJpeg->file_page_index);
    index = DirFileCount2[index];

    des_dir_index = pFsJpeg->dir_current;
    
    //root dir's lba
    lba = FSGetRoot();

    //selected dir's lba
    if(des_dir_index != 0)// ! root dir
    {
        lba = msf2l(iso9660_dir[des_dir_index].loc);
    }

    if(index > ISO_FILE_MAX)
    {
        ShowWarning("RENAMING DIR...");
        if(FSSearchDir(lba, GetString))//check same name dir
        {
            ShowWarning("THE DIR IS ALREADY EXISTED.");
            //printf("<<<<<<<<<<<<<<<<<<<<<<<<<<< THE DIR IS ALREADY EXISTED.>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
            return;
        }
        else//rename dir
        {
            RenameFile(GetString,&(iso9660_dir[index - ISO_FILE_MAX]));
            strcpy(iso9660_dir[index - ISO_FILE_MAX].name, GetString);
        }
        ShowWarning("DIR IS RENAMED.");
    }
    else if(index < ISO_FILE_MAX)
    {
        ShowWarning("RENAMING FILE...");
        if(FSSearchFile(lba, GetString))//check same name dir
        {
            ShowWarning("THE FILE IS ALREADY EXISTED.");
            //printf("<<<<<<<<<<<<<<<<<<<<<<<<<<< THE FILE IS ALREADY EXISTED.>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
            return;
        }
        else//rename file
        {
            RenameFile(GetString,&(iso9660_file[index]));
            strcpy(iso9660_file[index].name, GetString);
        }
        ShowWarning("FILE IS RENAMED.");
    }
    else if(index == ISO_FILE_MAX)
    {
        invalid_key();
        return;   
    }
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : RenameFile                                                           *
 *                                                                                       *
 *  Purposes      : Rename file or dir                                                   *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :  only for develope use.                                              *
 *                                                                                       *
\****************************************************************************************/
void RenameFile(char *foldername, DIR_REC *OriFileInfo)
{
	BYTE	assignName[12];
	UINT32	lba, fileloc, assignlba, filelba, nextLBA;
	UINT32	index=0;
	UINT32  iRes;
	BYTE	FileName[12];
	BYTE	srcFDB[33];
	UINT32	startClus;
	BYTE 	i;
	BYTE	*dstpwb= (BYTE *)(SDRAM_BASE + (167+1242) * 1024); //pointer address

	printf("foldername = '%s'\n",foldername);//jerry

	fileloc = OriFileInfo->loc;
	assignlba = msf2l(fileloc);
	strcpy(assignName, OriFileInfo->name); //get the user input file name!!!

	lba = msf2l(iso9660_dir[ OriFileInfo->parent_dir ].loc);

	nextLBA = lba;
	do{
		iRes=FSGetFDB(lba, index++, srcFDB);
		iso9660_assign_name(srcFDB, FileName, 8, 0);
		if(cardP.typeFAT==CARD_FAT32){//liweihua 2004-8-4 17:50
		    startClus=(getBiUINT16(srcFDB+26))|(getBiUINT16(srcFDB+20)<<16);
		}
		else
		{
		    startClus=getBiUINT16(srcFDB+26);
		}
		filelba=FSClus2LBA(startClus);

		if((assignlba==filelba) && (strcmp(assignName, FileName)==0)) //add condition
		{
			index=(index-1)%(cardP.bytePerSec/FDBSIZE); 	//get the offset of n-th FDB in LBA
			FSReadSector(nextLBA, 1, dstpwb);
			for(i=0; i<8; i++)//give the assigned name to the current file.
				dstpwb[(index)*FDBSIZE+i]=foldername[i];
			FSWriteSector(nextLBA, 1, dstpwb);
			return ;
		}
		else
		{
			nextLBA=iRes;
		}
	}while(iRes);
}

/****************************************************************************************\
 *                                                                                       *
 *  Function Name : FileModeGetInfo                                                      *
 *                                                                                       *
 *  Purposes      : Get information of Card & Hard Disc                                  *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : (none)                                                               *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void FileModeGetInfo(void)
{
    if(1)//(pFsJpeg->ControlArea == CNT_AREA_DEST)
    {
        FSGetRoot();
    }
}
/****************************************************************************************\
 *                                                                                       *
 *  Function Name : SwitchSrcDesBuffer                                                   *
 *                                                                                       *
 *  Purposes      : Switch to destination's buffer of source's buffer                    *
 *                                                                                       *
 *  Descriptions  :                                                                      *
 *                                                                                       *
 *  Arguments     : SrcOrDes :                                                           *
 *                             SRCE : source                                             *
 *                             DEST : destination                                        *
 *                                                                                       *
 *  Returns       : (none)                                                               *
 *                                                                                       *
 *  See also      :                                                                      *
 *                                                                                       *
\****************************************************************************************/
void Switch2SrcDesBuf(BYTE SrcOrDes)
{
    if(SrcOrDes == SRCE)//switch to source's pFsJpeg,fs9660dir and fs9660file buffer
    {
        pFsJpeg = &(share_data.JPEG);
        _fs9660_buf = iso9660buf_src;
    }
    else if(SrcOrDes == DEST)//switch to destination's pFsJpeg,fs9660dir and fs9660file buffer
    {
        pFsJpeg = pFsJpeg_des_buf;
        _fs9660_buf = iso9660buf_des;   
    }
}
/****************************************************************************************/
#endif
