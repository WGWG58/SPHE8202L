/*=================================================================

hdd_fs.c: Some FileSystem Info Function for HDD

2002-04-28 10:00AM Created  by Verdure
2002-06-12 08:42AM Modified by cyue

Copyright(c)2000-2002 by Worldplus Technology (ShenZhen) Co., Ltd.
                   ALL RIGHTS RESERVED 
=================================================================*/

#include "config.h"
#include "set.h"
#include "global.h"
#include "hdd_if.h"

#include "user_init.h"

#ifdef SUPPORT_HDD_ACCESS

#define	D	printf("INFO: __%d__(%s:%s)\n",__LINE__,__FILE__,__FUNCTION__);

#define	SUPPORT_FAT2			//MIKEY 2003.09.18 write FAT2
//#define	SUPPORT_BACKUP_FAT	//MIKEY 2003.09.18 copy FAT1 to FAT2

#define DBG_HDD_FS			//MIKEY_DEBUG


#ifndef DBG_HDD_FS
#undef printf
#define printf(f, a...)  {}
#endif


UINT32  keep_lba=-1;
//==============================================================
//
//==============================================================
// Global for FAT FS
extern UINT8  pwb[];

//UINT8 *Info_buff=pwb+0;
#define	NAVBUFSTART	(0xa03c0000)		// 0xa03c0000 40k
UINT8 *Info_buff=(UINT8 *)(NAVBUFSTART+0);
UINT8  HD_EXIST;
HDD_INFO HDD_Info;
BPB_INFO BPB;

UINT32 Data_Start_Clus;
UINT32 File_FDB_Lba;
UINT32 Start_LBA;
UINT32 Data_Curr_Clus;
UINT32 Data_Next_Clus;

int FS_Get_BPBPara(UINT8*);

PARTITION_INFO* HDD_AddPE(HDD_INFO* HDD_Info,UINT32 MBR,PARTITION_ENTRY* pe)
{
	PARTITION_INFO *pi=0;
#ifdef PI_USE_MATRIX
	int j;
	for(j=0;j<MAX_PART_INFO;j++)
	     if(!HDD_Info->part[j].type) break;
	pi=&HDD_Info->part[j]; 
#else
	PARTITION_INFO *hddpi;
	pi=(PARTITION_INFO*)malloc(sizeof(PARTITION_INFO));
#endif
	pi->type=pe->type;
	pi->next=NULL;
	pi->startlba=MBR+(pe->secfrommbr_hi<<16|pe->secfrommbr_lo);	
	Start_LBA=pi->startlba;
        // printf("\n startlba:%x\n",Start_LBA);//jichuan
	pi->seccnt=pe->seccnt_hi<<16|pe->seccnt_lo;
	pi->act=pe->act; 
#ifndef PI_USE_MATRIX
	if(HDD_Info->partition_list==NULL)
		HDD_Info->partition_list=pi;
	else {
		for(hddpi=HDD_Info->partition_list;hddpi->next!=NULL;hddpi=hddpi->next);
			hddpi->next=pi;
	}
#endif 
	return pi; 
}

int HDD_MakeInfo(HDD_INFO *HDD_Info,UINT8* buff)
{	
	PARTITION_ENTRY *pe;
	UINT32 i;     
	UINT32 MBR=0,secfrommbr,seccnt;

#ifdef PI_USE_MATRIX
	for(i=0;i<MAX_PART_INFO;i++)
		HDD_Info->part[i].type=0;
#else
	HDD_Info->partition_list=NULL;
#endif

	HDD_ReadSec(buff,MBR,1);
	//print_sector(buff);
	for(i=0;i<4;i++) { //Parse Primary partitions
		pe=(PARTITION_ENTRY*)(buff+ 0x1be +i*16);
		secfrommbr=pe->secfrommbr_hi<<16|pe->secfrommbr_lo;
		seccnt=pe->seccnt_hi<<16|pe->seccnt_lo;  
		printf("\n--secfrommbr=%lx--\n",secfrommbr);
		if (!pe->type)
			continue;
		if ((pe->type==0x0f)||(pe->type==0x05)) {
			// Extended Partition!!
			UINT32 MBREXT=MBR+secfrommbr;
			do {
				HDD_ReadSec(buff,MBREXT,1);
				printf("\n Parse EXT %lu... ",MBREXT);
				if (*(UINT16*)(buff+510)!=0xaa55) {
					printf("\n Fail EXT Partition!!");
					break;
				}
				pe=(PARTITION_ENTRY*)(buff + 0x1be);
				secfrommbr=pe->secfrommbr_hi<<16|pe->secfrommbr_lo;
				seccnt=pe->seccnt_hi<<16|pe->seccnt_lo;
				if (pe->type) {
#ifdef MIKEY
					HDD_AddPE(HDD_Info,MBREXT,pe);
#else
					printf("MIKEY: skip add EXT partition type[%x]\n",pe->type);
					break;
#endif
				}
				else
					break;
				pe=(PARTITION_ENTRY*)(buff+ 0x1be +16);
				if(!pe->type) {
					printf("\nLast MBR!!");
					MBREXT=HDD_Info->seccnt - seccnt;
				}
				else {
					MBREXT=MBREXT+secfrommbr+seccnt;
				}
			}while((pe->type==0x0f)||(pe->type==0x05));
		} 
		else {
			HDD_AddPE(HDD_Info,MBR,pe);
			printf("\n primary=%d \n",i);
		}
	}
	return 0;
}

void HDD_Dump_Info(HDD_INFO* HDD_Info)
{
	PARTITION_INFO *pi;
	int i;
	printf("\n\nHDD: C=%lu H=%lu S=%lu",HDD_Info->cyl,HDD_Info->head,HDD_Info->sec);
	printf("\nHDD total Sectors = %lu, %lu MB ",HDD_Info->seccnt,HDD_Info->seccnt/2000);
	printf("\nPAR  A TYPE START LBA       COUNT"); 
#ifdef PI_USE_MATRIX
	for(i=0;i<MAX_PART_INFO;i++) {
		pi= &HDD_Info->part[i];
		if(pi->type)
			printf("\n%2d  %02x  %02x %10lu  %10lu\n",i,pi->act,pi->type,pi->startlba,pi->seccnt);
	}
#else	
	for(i=0,pi=HDD_Info->partition_list;pi!=NULL;i++,pi=pi->next) {
		printf("\n%2d  %02x  %02x  %10lu  %10lu",i,pi->act,pi->type,pi->startlba,pi->seccnt);
	}
#endif
}


static int FS_check_SecPerClus(unsigned SecPerClus)
{
	unsigned char log;

	for(log = 0; log < 8; log++) {
		if(SecPerClus & 1) {
			SecPerClus >>= 1;
			return (SecPerClus != 0) ? -1 : log;
		}
		SecPerClus >>= 1;
	}
	return -1;
}

int FS_check_BootSec(UINT8* buf)
{
	UINT16 temp;

	//check Jump Code + NOP
	if(buf[0] == 0xE9)
		/* OK */;
	else if(buf[0] == 0xEB && buf[2] == 0x90)
		/* OK */;
	else {
		printf("Missing JMP/NOP\n");
		return 1;
	}

	//check Sectors Per Cluster
	temp = buf[13];
	if(FS_check_SecPerClus(temp) < 0) {
		printf("Sectors per cluster (%u) is not a power of 2\n",temp);
		return 1;
	}
	
	//check the Number of FATs
	temp = buf[16];
	if(temp != 1 && temp != 2) {
		printf("Invalid number of FATs (%u)\n",temp);
		return 1;
	}
	    
	//check Sectors Per Track
	temp = read_le16(buf + 24);
	if(temp == 0 || temp > 63) {
		printf("Invalid number of sectors (%u)\n",temp);
		return 1;
	}
	
	//check Number of Heads
	temp = read_le16(buf + 26);
	if(temp == 0 || temp > 255) {
		printf("Invalid number of heads (%u)\n",temp);
		return 1;
	}
	return FS_Get_BPBPara(buf);
}


int FS_Get_BPBPara(UINT8* buf)
{
	BPB.BytesPerSec=(buf[12]<<8)|buf[11];
	switch(BPB.BytesPerSec) {
		case 512: BPB.BytesPerSecPwr=9; break;
		case 2048: BPB.BytesPerSecPwr=11; break;
		case 256: BPB.BytesPerSecPwr=8; break;
	}
	printf("\n## BytesPerSec:%d ",BPB.BytesPerSec);
     
	BPB.SecPerClus=buf[13];
	switch(BPB.SecPerClus) {
		case 128: BPB.SecPerClusPwr=7; break; //64K allocation unit
		case  64: BPB.SecPerClusPwr=6; break; //32K allocation unit
		case  32: BPB.SecPerClusPwr=5; break; //16K allocation unit
		case  16: BPB.SecPerClusPwr=4; break; // 8K allocation unit
		case   8: BPB.SecPerClusPwr=3; break; // 4K allocation unit
		case   4: BPB.SecPerClusPwr=2; break; // 2K allocation unit
	}

	printf("\n## SecPerClus:%d ",BPB.SecPerClus);
	printf("\n## SecPerClusPwr:%d ",BPB.SecPerClusPwr);
     
	BPB.ReserSecCnt=read_le16(buf + 14);
	BPB.NumFATs=buf[16];
//	BPB.MediaDescriptor=buf[21];
//	BPB.SecPerTrack=read_le16(buf + 24);
//	BPB.NumHeads=read_le16(buf + 26);
//	BPB.HiddenSecCnt=read_le32(buf + 28);
//	BPB.TolSec32=read_le32(buf + 32);

	BPB.FATSize32=read_le32(buf + 36);
	printf("\n## FATSize32:%d ",BPB.FATSize32);
	BPB.CurrDirClus=BPB.RootClus=read_le32(buf + 44);
	BPB.FAT1_Start=Start_LBA+BPB.ReserSecCnt;
	printf("\n## BPB.FAT1_Start:%d ",BPB.FAT1_Start);
	if (BPB.NumFATs==1) 
		BPB.FAT2_Start=0;
	if (BPB.NumFATs==2)
		BPB.FAT2_Start=BPB.FAT1_Start+BPB.FATSize32;

	BPB.Data_Area_Start=((BPB.RootClus-2)*BPB.SecPerClus) + BPB.FAT1_Start+BPB.FATSize32*BPB.NumFATs;
	printf("\n## BPB.Data_Area_Start:%d \n",BPB.Data_Area_Start);
	return 0;
}

UINT32 Last_FAT_Lba=0x0FFFFFFF; // cyue: Try to make a cache 2002-06-11 11:14PM
UINT8 *FS_ReadInfoSec(UINT32 lba,int seccnt)
{
	if(Last_FAT_Lba!=lba) {
		HDD_ReadSec(Info_buff,lba,seccnt);
	}
	return Info_buff;
}


void FS_flush_cache()
{
	keep_lba=-1;
}


UINT32  FS_Get_NextClus(UINT32 clus)	//MIKEY 2003.09.02 for speed up
{
	UINT32 lba;
	UINT32 nOffset;
//	static UINT32  keep_lba=-1;
	static UINT32  keep_count=0;
//	extern UINT8  pwb[];
//	UINT8 *buff512=pwb+512;
	UINT8 *buff512=(UINT8 *)(NAVBUFSTART+512);

    keep_lba=-1; //MIKEY disable cache

	nOffset=clus&0x7F;//%128;
	lba=(clus>>7)+BPB.FAT1_Start;

	if(keep_lba!=lba) { //MIKEY_CACHE
		keep_lba=lba;
		HDD_ReadSec(buff512, lba, 1);
	}
	else {
		keep_count++;
		if((keep_count % 100)==99)
			printf("INFO: FS_Get_NextClus keep_count(%ld)\n",keep_count);
	}		
	Data_Next_Clus=read_le32(buff512+(nOffset<<2))&0x0fffffff;
	return Data_Next_Clus;
}

//==============================================================
//
//==============================================================
//extern BYTE CardReadSector();
extern BYTE FSReadSector();
extern BYTE CardWriteSector();
extern void *memcpy();
extern unsigned strlen();

/* Check whether HD present */
UINT8 HDD_DEV_Existence(void)
{
	return 0;
}

int HDD_ReadSec(UINT8 *buff, UINT32 lba, int seccnt)
{
	int i;
	int ret=0;
	for(i=0;i<5;i++) { // retry?
//		if((ret=CardReadSector(lba, seccnt, buff))==0)
		if((ret=FSReadSector(lba, seccnt, buff))==0)
			break; //OK
		printf("ERROR: HDD_ReadSec retry(%d)\n",i+1);
	}
	return ret;
} 

int HDD_WriteSec(UINT8 *buff, UINT32 lba, int seccnt)
{
	int i;
	int ret=0;
	for(i=0;i<5;i++) { // retry?
		if((ret=CardWriteSector(lba, seccnt, buff))==0)
			break; //OK
		printf("ERROR: HDD_WriteSec retry(%d)\n",i+1);
	}
	return ret;
} 


UINT32 FS_LBA2Clus(UINT32 lba)
{
	UINT32 clus;

	clus = (lba - BPB.Data_Area_Start)/BPB.SecPerClus + 2;
	return clus;
}

UINT32 FS_LBAinClus(UINT32 lba)
{
	UINT32 curClus, nextClus;
	int i;
    
	curClus = FS_LBA2Clus(lba);
	for (i=0; i<BPB.SecPerClus; i++) {
		nextClus = FS_LBA2Clus(lba+i+1);
		if (curClus != nextClus)
			break;
	}
	return i;
}


//==============================================================
//
//==============================================================
#ifdef SUPPORT_BACKUP_FAT
void  HDD_Backup_FAT(void)
{
	UINT32 i;
	if(BPB.NumFATs<2)
		return;
	
	for(i=0; i<BPB.FATSize32; i++) {
		HDD_ReadSec (Info_buff, BPB.FAT1_Start+i, 1);
		HDD_WriteSec(Info_buff, BPB.FAT2_Start+i, 1);
	}	
}
#endif //SUPPORT_BACKUP_FAT

int HDD_list_clus(FILE_INFO *fp)
{
	UINT32 st,next;
//	UINT32 lba_count=LBA_COUNT(fp->fsize),sec_count=BPB.SecPerClus; 
	int i=0;
	st=fp->start_clus;
	next=0;
//printf("MIKEY: lba_count(%d)/(%d)=(%d)\n",lba_count,sec_count,(lba_count+sec_count-1)/sec_count);
	while(1) {
		printf("$$ clus(%4d):[%x]\n",i,st);
		if(st>=0x0FFFFFF8) {//End?
			break;
		}
		next=FS_Get_NextClus(st);
		st=next;
		i++;
	}
	return 0;
}

//==============================================================
//
//==============================================================
UINT8  FS_Emu_stricmp(UINT8* s1, UINT8* s2)
{
	UINT16 i;

//MIKEY_BUG
//	for(i=0;(i<11)&&(*s1)&&(*s2);i++,s1++,s2++) {
	for(i=0;i<11;i++) {
		if(((s1[i])&~0x20)!=((s2[i])&~0x20))
    			return 1;
	}
	return 0;
}


UINT8  HDD_Mount(void)
{
	UINT8 i;
    
	if ((HD_EXIST = HDD_DEV_Existence()))
		return 0;
	HDD_MakeInfo(&HDD_Info,Info_buff);
	for(i=0;HDD_Info.part[i].type;i++) { /*檢測每一個分區*/
		Start_LBA=HDD_Info.part[i].startlba;
		printf("\nStart_LBA:%d\n",Start_LBA);
		FS_ReadInfoSec(Start_LBA,1);
		FS_check_BootSec(Info_buff);
	}
	return 1;
}

void  FS_del_chain(UINT32 start_clus)
{
	UINT32 clus_lba=BPB.FAT1_Start;
	UINT32 curClus=start_clus;
	UINT32 nextClus;	

	FS_ReadInfoSec((curClus>>7)+BPB.FAT1_Start,1);
	while(curClus<0x0FFFFFF8) {
		nextClus=FS_Get_NextClus(curClus);
		read_le32(Info_buff+((curClus&0x7F)<<2))=0;
		clus_lba=(curClus>>7)+BPB.FAT1_Start;
		HDD_WriteSec(Info_buff,clus_lba,1);
#ifdef SUPPORT_FAT2
		if(BPB.NumFATs>=2)
			HDD_WriteSec(Info_buff,clus_lba+BPB.FATSize32,1);
#endif //SUPPORT_FAT2
		if((nextClus>>7)!=(curClus>>7))
			FS_ReadInfoSec(clus_lba,1);
		curClus=nextClus;
	}
	read_le32(Info_buff+((curClus&0x7F)<<2))=0;
	clus_lba=(curClus>>7)+BPB.FAT1_Start;
	HDD_WriteSec(Info_buff,clus_lba,1); 
#ifdef SUPPORT_FAT2
	if(BPB.NumFATs>=2)
		HDD_WriteSec(Info_buff,clus_lba+BPB.FATSize32,1);
#endif //SUPPORT_FAT2
}

UINT8 FILE_update_clus(FILE_INFO *fp, UINT32 start_clus)
{
	printf("INFO: FILE_update_clus start_clus[%x] fdb_lba[%x]\n", start_clus,fp->fdb_lba);
	if ( HDD_ReadSec(Info_buff, fp->fdb_lba, 1) ) {
		printf("ERROR: HDD_ReadSec fdb_lba[%x]\n",fp->fdb_lba);
		return 1;
	}
        read_le16(Info_buff+fp->fdb_offset+20)=(start_clus>>16)&0xfff;
        read_le16(Info_buff+fp->fdb_offset+26)=start_clus&0xffff;
	HDD_WriteSec(Info_buff, fp->fdb_lba, 1);
	return 0; //No ERR
}

FILE_INFO *FS_fileinfo(FAT32_FDB *fdb,FILE_INFO *pfinfo)
{	UINT16 i;

	Data_Start_Clus=pfinfo->start_clus=(UINT32)((fdb->start_hi)<<16|(fdb->start_lo));
	if(pfinfo->start_clus==0) //cyue: '..' to root!!
	{	
		printf(" It's Root !! ");
		Data_Start_Clus=pfinfo->start_clus=BPB.RootClus;
	}

	pfinfo->l_time[0]=fdb->unused[0];
	pfinfo->l_time[1]=fdb->unused[1];
	pfinfo->l_time[2]=fdb->unused[2];
	pfinfo->l_time[3]=fdb->unused[3];
	
	pfinfo->time[0]=fdb->edit_time;
	pfinfo->time[1]=fdb->edit_date;	

	pfinfo->start_lba=FS_Clus2LBA(pfinfo->start_clus);
	pfinfo->fsize=fdb->fsize;
	pfinfo->attrib=fdb->attrib;
	i=BPB.BytesPerSecPwr;
	return pfinfo;	
}

FILE_INFO* SearchFile(UINT32 dir_clus, UINT8 *name)
{
	UINT32 lba;
	UINT32 i,offset;
	static FILE_INFO finfo;
	for(;dir_clus<0x0FFFFFF8;dir_clus=FS_Get_NextClus(dir_clus)) {
		lba=FS_Clus2LBA(dir_clus);
		for(i=BPB.SecPerClus;i;i--,lba++) {
			//printf("### DirLBA:0x%lx\n",lba);     jichuan_del
			FS_ReadInfoSec(lba,1);
			for(offset=0;offset<BPB.BytesPerSec;offset+=32) {
				switch(Info_buff[offset]) {
					case 0:	// free FDB, End!!
						printf("\nNo Such File Here!! %s\n",name);
						BPB.curr_fdb_lba=lba; // store file info location
						BPB.curr_fdb_offset=offset; // store file info location
						
						return NULL; 
					case 0xE5: //deleted FDB
						continue;
#if 0
					case '.'://Parrent or this dir
						if(Info_buff[offset+1]=='.') {
							printf("\n Parrent Dir(..)");
						}
						else {
							printf("\n This Dir(.)");
						}
						continue;
#endif
					default:
						if(FS_Emu_stricmp(&Info_buff[offset],name)==0) {
							BPB.curr_fdb_lba=lba; // store file info location
							BPB.curr_fdb_offset=offset; // store file info location
							FS_fileinfo((FAT32_FDB*)(&Info_buff[offset]),&finfo);
							finfo.fdb_lba=lba;
							finfo.fdb_offset=offset;
							return &finfo;
						}
						break;
				}
			}
		}
	}
	return NULL;
}

FILE_INFO*  HDD_SearchFile(UINT8 *s)
{
	FILE_INFO* ret=NULL;
	UINT32 clus,i;
	UINT8 part_name[12],*d;

#ifdef MIKEY_CACHE
#else
	FS_flush_cache();
#endif
	if(*s=='/') { //FROM ROOT
		clus=BPB.RootClus;
		s++;
	}
	else { //FROM CURRENT
		clus=BPB.CurrDirClus;
	}

	while(1) {
		// clear part_name buff;
		for(i=0,d=part_name;i<11;i++,d++)
			*d=' ';
		*d=0;
		d=part_name;
		// clear leading '/'
		if(*s=='/')
			s++;
		
		if(*s=='.') { // self or parrent?
			*(d++)='.';
			if(*(s+1)=='.') {// parrent?
				*(d++)='.'; s++;
			}
			*d=0; s++;
		}
		else {
			//copy part_name
			while((*s!='/')&&(*s!=0)) {
				if(*s=='.') {
					d=&part_name[8];
				}
				else {
					*d++=*s;
				}
				s++;
			}
			*d=0;
		}

		// Get Part-File Info
#ifdef MIKEY_BUG
#else
		if(part_name[0]==0x0) { // MIKEY: root dir.
			BPB.CurrDirClus = BPB.RootClus;
			printf("MIKEY: ROOT dir. HDD_cd change CurrDirClus[%x] to dirname[%s]\n",BPB.CurrDirClus, s);
			return NULL;
		}	
#endif

		if((ret=SearchFile(clus,part_name))==NULL)
			return NULL;

		if(ret->attrib&FAT_ATTR_D) { // Is this a subdir file?
			if(*s==0) {// End Search string => just get the dir info
//				printf(" CD to new dir (%s)!!",part_name);
				return ret;
			}
		}
		else { // A real file finded
			//printf(" Final Name: %s\n",ret->name);
			return ret;
		} 
		clus=ret->start_clus;
	}
}

UINT8  FS_cd(UINT8 *s)
{
	FILE_INFO* ret;

//	printf("INFO: FS_cd change CurrDirClus[%x] to dirname[%s]\n",BPB.CurrDirClus, s);
	if((ret=HDD_SearchFile(s))==NULL)
		return 0;

	if(ret->attrib&FAT_ATTR_D) {// Is this a subdir file?
		BPB.CurrDirClus=ret->start_clus;
//		printf("INFO: after FS_cd change CurrDirClus[%x] to dirname[%s]\n",BPB.CurrDirClus, s);
		return 1;
	}
	return 0; // No such dir, but such file!!
}    	
       	    	 
UINT8 FS_dir(void)
{	
	UINT32 dir_clus,lba;
	UINT32 i,j;
	UINT8 name[12];

	printf("\nDIR:\n");
	for(dir_clus=BPB.CurrDirClus; dir_clus<0x0FFFFFF8; dir_clus=FS_Get_NextClus(dir_clus)) {
		lba=FS_Clus2LBA(dir_clus);
		for(i=0; i<BPB.SecPerClus; i++) {
			FS_ReadInfoSec(lba+i, 1);
			for(j=0; j<BPB.BytesPerSec; j+=32) {
				UINT8 *s;
				s=&Info_buff[j];
				if(*s==0) {	// MIKEY: No more file in dir
					printf("\n");
					return 0; 
				}
				if(*s==0xE5)	// MIKEY: skip deleted file
					continue;
				if(s[11]==0x0f)	// MIKEY: skip longname
					continue;
				memcpy(name, s, 11);
				name[11]=0;
				printf("\t[%s]\n",name);
			}
		}
	}
	return 1;
}

UINT32 FS_getfreeclus(UINT32 first_clus)  
{
	UINT32 fat_lba=BPB.FAT1_Start+(first_clus>>(BPB.BytesPerSecPwr-2));	
	UINT32 offset;

	while(fat_lba<BPB.FAT2_Start) {//at the end of FAT1
		FS_ReadInfoSec(fat_lba,1);
		for(offset=0;offset<BPB.BytesPerSec;offset+=4) {
			if(read_le32(Info_buff+offset)==0) {
				Data_Next_Clus=(((fat_lba-BPB.FAT1_Start)<<7)+(offset>>2));
				read_le32(Info_buff+offset)=0x0FFFFFF8; // MIKEY_BUG 0x0FFFFFFF;
				HDD_WriteSec(Info_buff,fat_lba, 1);
#ifdef SUPPORT_FAT2
				if(BPB.NumFATs>=2)
					HDD_WriteSec(Info_buff,fat_lba+BPB.FATSize32,1);
#endif //SUPPORT_FAT2
				return Data_Next_Clus; // OK
			}
		}
		fat_lba ++;
	}
	if(fat_lba>=BPB.FAT2_Start)
		printf("ERROR: The HD is Full\n");
	return 0; // ERROR: The HDD is Full
}

UINT8  HDD_setfdb(UINT8 *name_buff, UINT32 start_clus, UINT8 dirflag) // MIKEY 2003.09.17
{
	UINT8 FDB_name[12];   //jichuan_add 2002.9.27
	UINT32 dir_clus,lba;
	UINT32 i,j;
	UINT32 n;
	UINT8 *s;
	UINT32 curClus=BPB.CurrDirClus;
	UINT32 f_room=0;
     
	for(i=0;i<12;i++) {
		FDB_name[i]=0;
	}

	for(i=0;i<12;i++) {
		FDB_name[i]=name_buff[i];
	}

#ifdef MIKEY_CACHE
#else
	FS_flush_cache();
#endif
#ifdef MIKEY_CHECK_EXIST
#else
	for(dir_clus=BPB.CurrDirClus; dir_clus<0x0FFFFFF8; dir_clus=FS_Get_NextClus(dir_clus)) {
		curClus=dir_clus;
		lba=FS_Clus2LBA(dir_clus);
		for(i=0; i<BPB.SecPerClus; i++) {
			FS_ReadInfoSec(lba+i, 1);
			for(j=0; j<BPB.BytesPerSec; j+=32) {
				s=&Info_buff[j];
				if(*s==0x00) { // MIKEY: No more file in dir
					f_room++;
					break;
				}
				if(*s==0xE5) { // MIKEY: skip deleted file
					f_room++;
					continue;
				}
				if(*s=='.')  // MIKEY: skip "." ".." dir
					continue;
				if(FS_Emu_stricmp(s,FDB_name)==0) {
					printf("ERROR: EXIST\n");
					printf("ERROR: curClus[%x] i[%x] j[%x] \n");
					return 0;	// ERRROR: EXIST
				}
			}
		}
	}

	if(f_room==0) {
		printf("ERROR: NO ROOM for file or dir. entry\n");
		if((dir_clus=(FS_getfreeclus(0)))==0) {
			return 0; // ERROR: HDD FULL
		}
		lba=(curClus>>7)+BPB.FAT1_Start;
		FS_ReadInfoSec(lba, 1);
		read_le32(Info_buff+ ((curClus&0x7F)<<2))=dir_clus;
		HDD_WriteSec(Info_buff,lba,1);
#ifdef SUPPORT_FAT2
		if(BPB.NumFATs>=2)
			HDD_WriteSec(Info_buff,lba+BPB.FATSize32,1);
#endif //SUPPORT_FAT2
		lba=FS_Clus2LBA(dir_clus);
		for(i=0;i<512;i++)   
			Info_buff[i]=0;        
		//clean entry : 1 cluster 
		for(i=0;i<BPB.SecPerClus;i++)
			HDD_WriteSec(Info_buff, lba + i, 1);
	}		
#endif // MIKEY_CHECK_EXIST

	for(dir_clus=BPB.CurrDirClus; dir_clus<0x0FFFFFF8; dir_clus=FS_Get_NextClus(dir_clus)) {
		lba=FS_Clus2LBA(dir_clus);
		for(i=0; i<BPB.SecPerClus; i++) {
			FS_ReadInfoSec(lba+i, 1);
			for(j=0; j<BPB.BytesPerSec; j+=32) {
				s=&Info_buff[j];
				if((s[0]!=0xE5) && (s[0]!=0x00)) // MIKEY: skip normal file or dir
					continue;					

				for(n=0;n<32;n++) // clean entry
					s[n]=0x0;
				for(n=0;n<11;n++) // set name
					s[n]=FDB_name[n];
				if(dirflag==1)
					s[11]=0x21; //file
				else
					s[11]=0x10; //dir
				read_le16(s+20)=(start_clus>>16)&0xfff;
				read_le16(s+26)=start_clus&0xffff;
//				read_le16(s+28)=filesize&0xffff;
//				read_le16(s+30)=(filesize>>16)&0xfff;
				HDD_WriteSec(Info_buff, lba+i, 1);
				return 1;	// OK
			}
		}
	}

	return 0;	// ERRROR: NO ROOM
}

UINT8  FS_mkdir(UINT8* dirname)	//MIKEY 2003.09.17
{
	UINT32 data_lba;
	UINT32 start_clus;
	UINT16 i;
    
	// check dirname first char 0xe5 or <0x20 = ' ' SPACE
	if(dirname[0]==0x0 || dirname[0]==0xE5 || dirname[0]<=0x20) {
		printf("ERROR: dirname first char=[0x%x], donot 0xE5 or <=0x20\n",dirname[0]);
		return 0;
	}

	// check dirname 11 chars.
	if(strlen(dirname)!=11) {
		printf("ERROR: the dirname need 11 chars\n");
		return 0;
	}

	for(i=0;i<11;i++) {
		if(dirname[i]==0x0 || dirname[i]=='/' || dirname[i]<0x20) {
			printf("ERROR: dirname[%d]=[0x%x]char[%c] need change\n",i,dirname[i],dirname[i]);
			return 0;
		}		
		if(dirname[i]>='a' && dirname[i]<='z') {
			dirname[i] -= 0x20;
		}
	}

	// check HDD FULL?
	if((start_clus=(FS_getfreeclus(0)))==0) {
		printf("Can't Creat File,HD is Full\n");
		return 0; // ERROR: HDD FULL
	}		

	// check DIR EXIST?
	if(HDD_setfdb(dirname, start_clus, 0)!=1) {
		printf("Can't Creat Dir, Dir %s is exist\n",dirname);
		return 0; // ERROR: DIR EXIST
	}

	data_lba=FS_Clus2LBA(start_clus);

	for(i=0;i<512;i++)   
		Info_buff[i]=0;        

	//clean entry : 1 cluster 
	for(i=0;i<BPB.SecPerClus;i++)
		HDD_WriteSec(Info_buff, data_lba + i, 1);

	// "." dir
	Info_buff[0]=0x2E;
	for(i=1;i<11;i++) 
		Info_buff[i]=0x20;
	Info_buff[11]=0x10; 
	// set the access cluster
//	printf("DIR[%s] clus[%x]\n",dirname, start_clus);
	read_le16(Info_buff+20)=(start_clus>>16)&0xfff;
	read_le16(Info_buff+26)=start_clus&0xffff;	        

	// ".." dir
	Info_buff[32]=0x2E;
	Info_buff[33]=0x2E;
	for(i=34;i<43;i++) 
		Info_buff[i]=0x20;
	Info_buff[43]=0x10;
            
	if(BPB.CurrDirClus==BPB.RootClus) {
		read_le16(Info_buff+52)=0;
		read_le16(Info_buff+58)=0;
	}
	else {
		read_le16(Info_buff+52)=(BPB.CurrDirClus>>16)&0xfff;
		read_le16(Info_buff+58)=BPB.CurrDirClus&0xffff;	
	}

	// write to HDD
	HDD_WriteSec(Info_buff, data_lba, 1);
        return 1;
}


UINT8 FS_rm(UINT8* name)
{
	FILE_INFO *fp;

	if(NULL==(fp=HDD_SearchFile(name)))
		return 1; //No File ERR
	Info_buff[fp->fdb_offset]=0xE5;
	HDD_WriteSec(Info_buff,fp->fdb_lba,1);
	FS_del_chain(fp->start_clus);//clear FAT chain
	return 0; //No ERR
}


UINT8 FS_rmdir(UINT8* dirname)
{
	return FS_rm(dirname);
}


FILE_INFO *FILE_open(UINT8 *filename)
{
	FILE_INFO *fp;

	printf("INFO: FILE_open[%s]\n",filename);
	if(NULL==(fp=HDD_SearchFile(filename)))
		return NULL; // ERROR: file not found
	fp->read_ptr  = fp->write_ptr  = 0;
	fp->read_lba  = fp->write_lba  = fp->start_lba;
	fp->read_clus = fp->write_clus = fp->start_clus;
	fp->f_need_new_clus=0;
	if(fp->start_clus<=2) {
		fp->f_need_new_clus=1;
	}	
        return fp; // OK
}

FILE_INFO *FILE_create(UINT8 *filename)
{
	UINT32 start_clus=2;	// MIKEY: new empty file default start_clus set to 2
	// check DIR EXIST?
	if(HDD_setfdb(filename, start_clus, 1)!=1) {
		printf("Can't Creat File, File %s is exist\n",filename);
		return NULL;
	}
        return FILE_open(filename);
}


UINT32 FILE_read(FILE_INFO *fp, void *buf, UINT32 count)
{
	UINT32 i;
	UINT32 offset=0;
	UINT32 nSec;


	if(fp->read_clus>=0x0FFFFFF8 || fp->read_clus<=2)
		return 2;

	nSec = (count+BPB.BytesPerSec-1) / BPB.BytesPerSec;
	for(i=0; i<nSec; i++) {
		if(HDD_ReadSec(buf+offset, fp->read_lba, 1) ) {
			return 1; // ERROR
		}
		// check need get next clus?
		if(FS_LBAinClus(fp->read_lba) == 0) {
			fp->read_clus = FS_Get_NextClus(fp->read_clus);
			fp->read_lba = FS_Clus2LBA(fp->read_clus);
		}
		else {
			fp->read_lba++;
		}
		offset += BPB.BytesPerSec;
		fp->read_ptr += BPB.BytesPerSec;
		// check EOF
		if (fp->read_ptr > fp->fsize) {
			return 0; // OK: EOF
		}
	}
	return 0; // OK
}


UINT32 FILE_write(FILE_INFO *fp, void *buf, UINT32 count)
{
	UINT32 i;
	UINT32 clus_lba=BPB.FAT1_Start;
	UINT32 offset=0;
	UINT32 nSec;

	nSec = (count+BPB.BytesPerSec-1) / BPB.BytesPerSec;
    
	for (i=0; i<nSec; i++) {
		if(fp->f_need_new_clus) {
			// check HDD FULL?
			clus_lba=(fp->write_clus>>7)+BPB.FAT1_Start;
			if((FS_getfreeclus(fp->write_clus))==0) {
				return 0; // ERROR: HDD FULL
			}

			if(fp->start_clus<=2) { // for new file
				fp->write_clus = Data_Next_Clus;
				fp->write_lba = FS_Clus2LBA(fp->write_clus);

				fp->start_clus = fp->read_clus = fp->write_clus;
				fp->start_lba  = fp->read_lba  = fp->write_lba;
				fp->read_ptr  = fp->write_ptr  = 0;
				FILE_update_clus(fp, fp->start_clus);
				clus_lba=(fp->write_clus>>7)+BPB.FAT1_Start;
				FS_ReadInfoSec(clus_lba,1);
				read_le32(Info_buff+ ((fp->write_clus&0x7F)<<2) )=0x0FFFFFFF; // MIKEY_BUG 
				HDD_WriteSec(Info_buff,clus_lba,1);
#ifdef SUPPORT_FAT2
				if(BPB.NumFATs>=2)
					HDD_WriteSec(Info_buff,clus_lba+BPB.FATSize32,1);
#endif //SUPPORT_FAT2
			}
			else {
				clus_lba=(fp->write_clus>>7)+BPB.FAT1_Start;
				FS_ReadInfoSec(clus_lba,1);
				read_le32(Info_buff+ ((fp->write_clus&0x7F)<<2) )=Data_Next_Clus;
				HDD_WriteSec(Info_buff,clus_lba,1);
#ifdef SUPPORT_FAT2
				if(BPB.NumFATs>=2)
					HDD_WriteSec(Info_buff,clus_lba+BPB.FATSize32,1);
#endif //SUPPORT_FAT2
				fp->write_clus = Data_Next_Clus;
				fp->write_lba = FS_Clus2LBA(fp->write_clus);			
			}
			fp->f_need_new_clus = 0;
		}			
		if(HDD_WriteSec(buf+offset, fp->write_lba, 1) ) {
			return 1;
		}
		if(FS_LBAinClus(fp->write_lba) == 0) {
			fp->f_need_new_clus=1;	// MIKEY: next time need FS_getfreeclus to find write space
		} else {
			fp->write_lba++;
		}
		offset += BPB.BytesPerSec;
		fp->write_ptr += BPB.BytesPerSec;
		if (fp->write_lba < fp->start_lba) {
			return 0;
		}
	}
	return 0;
}


UINT8 FS_rename(UINT8 *newname, UINT8 *oldname)
{
	FILE_INFO *fp;
	UINT8 *s;
	int i;

	printf("INFO: FS_rename [%s]->[%s]\n",oldname,newname);
	if(NULL==(fp=FILE_open(oldname)))
		return 1; // ERROR: file not found
	if(HDD_ReadSec(Info_buff, fp->fdb_lba, 1)) {
		return 2; // ERROR: HDD_ReadSec
	}
	s = Info_buff+fp->fdb_offset +0;
	memcpy(s, newname, 11);
	HDD_WriteSec(Info_buff,fp->fdb_lba,1);
	return 0; // OK: No ERR
}

UINT8 FILE_filesize(FILE_INFO *fp, UINT32 size)
{
	printf("INFO: filesize(%d) fdb_lba[%x]\n", size, fp->fdb_lba);
	if(HDD_ReadSec(Info_buff, fp->fdb_lba, 1)) {
		return 1; // ERROR: HDD_ReadSec
	}
	read_le16(Info_buff+fp->fdb_offset+28)=size&0xffff;
	read_le16(Info_buff+fp->fdb_offset+30)=(size>>16)&0xffff;
	HDD_WriteSec(Info_buff,fp->fdb_lba,1);
	return 0; // OK: No ERR
}

UINT8 FILE_close(FILE_INFO *fp)
{
	printf("INFO: filesize(%d)\n", fp->write_ptr);
	return 0; // OK: No ERR
}


#endif //#ifdef SUPPORT_HDD_ACCESS

