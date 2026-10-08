/*=================================================================

  hdd_play.c: Some FileSystem Info Function for HDD
  
	2002-04-28 10:00AM Created  by Verdure
	2002-06-12 08:42AM Modified by cyue
	
	  Copyright(c)2000-2002 by Worldplus Technology (ShenZhen) Co., Ltd.
	  ALL RIGHTS RESERVED
=================================================================*/

#include "config.h"
#include "global.h"
#include "hdd_if.h"
#include "hdd_fs.h"

#include "fsNav.h"

#include "user_init.h"

#ifdef SUPPORT_HDD_ACCESS

#define	D	printf("MIKEY: __%d__(%s:%s)\n",__LINE__,__FILE__,__FUNCTION__);


int ucosmain();
char *strcpy();
void *memcpy();
unsigned strlen();

BYTE ran_read();
UINT32 addmsf();

UINT8 FS_cd();
UINT8 FS_dir();
UINT8 FS_mkdir();
UINT8 FS_rm();

UINT8 FILE_filesize();
UINT32 FILE_write();
FILE_INFO *FILE_create();


UINT32 mikey_timer0_count=0;
UINT32 mikey_ucos_loaded=0;
UINT8 f_do_copy_vcd=0;
UINT8 f_vcd=0;
UINT8 f_hdd=0;
FILE_INFO copy_vcd_fd;
extern UINT8 f_force_browser;
extern UINT8 f_browser_mode;

int do_copy_file()
{
#ifdef SUPPORT_CARD_STORAGE
	if (media_type==MEDIA_CARD) {
		fsgui_del();
	}
	else
#endif
	if(f_browser_mode) {
		watchdog_onoff(0);
//		if(cd_type_loaded==CDVCD10 || cd_type_loaded==CDVCD20 || cd_type_loaded==CDSVCD) {
		if(f_browser_mode==CDVCD10 || f_browser_mode==CDVCD20 || f_browser_mode==CDSVCD) {
			f_vcd=1; // the vcd type
		}
		fsgui_copy();
		return 0;
	}	
	if(cd_type_loaded==CDVCD10 || cd_type_loaded==CDVCD20 || cd_type_loaded==CDSVCD || cd_type_loaded==CDDVD) {
		f_force_browser++;
		ircmd_eject_toggle();
//		ircmd_eject_toggle();
	}
	else
	fsgui_copy();
	return 0;
}

#if 0
int dvd_start_ucos()
{
	LoadModual(MODUAL_UCOS);
	delay_1ms(100);
	mikey_ucos_loaded=1;
	ucosmain(0,0);
	D	while(1);
}
#endif

//#define	COPYCOUNT	(100)
#define	COPYCOUNT	(20)
#define	COPYBUFSIZE	(2048*COPYCOUNT)
#define	COPYBUFSTART	(0xa03c0000+ 2048)		// 0xa03c0000 40k
#define	COPYVCDBUFSTART	(COPYBUFSTART+ COPYBUFSIZE)	// 0xa03c0000 40k
//#define	COPYBUFSTART	(JPGCDBUFSTART)	// 0xA03AA800 208k MIKEY_BUG: why reinsert the CD DISK will panic!!

int do_mount_hdd()
{
	// check hdd
	if(f_hdd==0) {
		if(HDD_Mount()==1) {
			f_hdd=1;
#ifdef MIKEY_CREATE_DIR
#else			
			FS_cd("/");
			// MIKEY_BUG: we need 11 chars. dirname, and donot with pathname
			FS_mkdir("JPEG       ");
			FS_mkdir("MP3        ");
			FS_mkdir("GAME       ");
			FS_mkdir("MOVIES     ");
			FS_dir();
#endif
		}
	}
	return f_hdd;
}



UINT32 copy_cd_to_hdd(UINT8 *filename, UINT32 cd_msf, UINT32 cd_size, UINT32 fs_state)
{
	UINT32 msf=cd_msf;
	UINT32 count;
	UINT8 *buf=(UINT8 *)(COPYBUFSTART);


	UINT32 i;
	UINT8 name[16];
	UINT8 dirname[16];
	FILE_INFO fd;
	FILE_INFO *fp=NULL;
	UINT8 f_copy=0;
	UINT8 f_try=0;
	static UINT32 f_error=0;
	UINT32 bufsize=COPYBUFSIZE;
	UINT32 lastbufsize=0;
	
	printf("\nINFO: buf[%x]\n",buf);

	count=(cd_size+COPYBUFSIZE-1) / COPYBUFSIZE;
	lastbufsize = cd_size % COPYBUFSIZE;
	printf("\nINFO: COPY this file[%s] msf[%x] len(%d) fs_state[%x] count(%d)\n",filename, msf, cd_size, fs_state, count);
	fsgui_100(0);

	if(do_mount_hdd()) {
//MIKEY_BUG
//D		return;
		FS_cd("/");
		switch(fs_state) {
			case 	FS_STATE_MP3:
				strcpy(dirname, "/MP3");
				strcpy(name, "        MP3");
				break;
			case 	FS_STATE_JPEG:
				strcpy(dirname, "/JPEG");
				strcpy(name, "        JPG");
				break;
			case 	FS_STATE_GAME:
				strcpy(dirname, "/GAME");
				strcpy(name, "        NES");
				break;
			case 	FS_STATE_OTHER:										
				strcpy(dirname, "/MOVIES");
				strcpy(name, "        MPG");
				break;
			default:
				strcpy(dirname, "/");
				strcpy(name, "        MPG");
				break;
		}
		for(i=0;i<strlen(filename);i++) {
			name[i] = filename[i];
		}
		printf("INFO: DIR[%s] filename[%s]\n",dirname ,name);
		FS_cd(dirname);
		FS_dir();

D		FS_rm(name); //MIKEY
D		if((fp=FILE_create(name))!=NULL) {
			memcpy(&fd, fp,sizeof(FILE_INFO));
			if(f_do_copy_vcd) { // f_do_copy_vcd=1 skip do copy
				memcpy(&copy_vcd_fd, fp,sizeof(FILE_INFO));
				copy_vcd_fd.fsize=cd_size;
			}
			fp = &fd;
			printf("MIKEY: create file [%s/%s] OK!!\n",dirname,name);
			f_copy=1;
		}
		else {
			printf("MIKEY: create file [%s/%s] ERROR!!\n",dirname,name);
			f_copy=0;
		}

	}
#define ATAPI_OK	(0)
D	if(f_do_copy_vcd) { // f_do_copy_vcd=1 skip do copy
		printf("INFO: DO VCD/SVCD COPY [%s/%s]!!\n",dirname,name);
#define	VCD_SECLEN	2352
		f_do_copy_vcd=0;
		buf=(UINT8 *)(COPYVCDBUFSTART);
		bufsize=VCD_SECLEN;
		count=(cd_size+bufsize-1) / bufsize;
		lastbufsize = cd_size % bufsize;
		for(i=0;i<count;i++) {
			if((i==(count-1)) && (lastbufsize!=0)) {
				bufsize=lastbufsize;
				printf("INFO: COPY LAST [%4d] msf[%x] bufsize[%x](%d)\n",i,msf,bufsize,bufsize);
			}	
			for(f_try=0;f_try<100;f_try++) {
				if(ran_read_vcd(buf, msf, bufsize)==ATAPI_OK)
					break;
				f_error++;
				printf("INFO: TRY(%d): COPY [%4d] msf[%x] f_error(%ld)\n",f_try,i,msf,f_error);
			}		
			if(f_copy) {
				stream_FILE_write(buf, bufsize);
			}
			msf = addmsf(msf, 1);
			fsgui_100(1+ ((i+1)*99/count) % 100);
		}
		flush_stream_FILE_write();
	}
	else { // do MP3, JPG, MPG file copy from CD to HDD
	for(i=0;i<count;i++) {
		if((i==(count-1)) && (lastbufsize!=0)) {
			bufsize=lastbufsize;
			printf("INFO: COPY LAST [%4d] msf[%x] bufsize[%x](%d)\n",i,msf,bufsize,bufsize);
		}	
		for(f_try=0;f_try<100;f_try++) {
			if(ran_read(buf, msf, bufsize)==ATAPI_OK)
				break;
			f_error++;
			printf("INFO: TRY(%d): COPY [%4d] msf[%x] f_error(%ld)\n",f_try,i,msf,f_error);
		}		
		if(f_copy) {
			FILE_write(fp, buf, bufsize);
		}
		msf = addmsf(msf, COPYCOUNT);
		fsgui_100(1+ ((i+1)*99/count) % 100);
//		fsgui_100((i+1)*100/count);
	}
	} //f_do_copy_vcd

	if(f_copy) {
		FILE_filesize(fp, cd_size); 
	}
	printf("INFO: COPY END!! [%s/%s]\n",dirname,name);
	return 0;
}


UINT32 rm_file_from_hdd(UINT8 *filename, UINT32 cd_msf, UINT32 cd_size, UINT32 fs_state)
{
	UINT32 i;
	UINT8 name[16];
	UINT8 dirname[16];

	printf("\nINFO: del this file[%s] msf[%x] len(%d) fs_state[%x]\n",filename, cd_msf, cd_size, fs_state);
	if(do_mount_hdd()) {
		FS_cd("/");
		switch(fs_state) {
			case 	FS_STATE_MP3:
				strcpy(dirname, "/MP3");
				strcpy(name, "        MP3");
				break;
			case 	FS_STATE_JPEG:
				strcpy(dirname, "/JPEG");
				strcpy(name, "        JPG");
				break;
			case 	FS_STATE_GAME:
				strcpy(dirname, "/GAME");
				strcpy(name, "        NES");
				break;
			case 	FS_STATE_OTHER:										
				strcpy(dirname, "/MOVIES");
				strcpy(name, "        MPG");
				break;
			default:
				strcpy(dirname, "/");
				strcpy(name, "        MPG");
				break;
		}
		for(i=0;i<strlen(filename);i++) {
			name[i] = filename[i];
		}
		printf("INFO: DIR[%s] filename[%s]\n",dirname ,name);
		FS_cd(dirname);
		FS_dir();
		FS_rm(name); //MIKEY
		FS_dir();
	}
}


UINT32 rename_file_from_hdd(UINT8 *newfilename, UINT8 *filename, UINT32 cd_msf, UINT32 cd_size, UINT32 fs_state)
{
	UINT32 i;
	UINT8 name[16];
	UINT8 newname[16];
	UINT8 oldname[16];
	UINT8 dirname[16];

	printf("\nINFO: rename this file[%s]->[%s] msf[%x] len(%d) fs_state[%x]\n",filename,newfilename, cd_msf, cd_size, fs_state);
	if(do_mount_hdd()) {
		FS_cd("/");
		switch(fs_state) {
			case 	FS_STATE_MP3:
				strcpy(dirname, "/MP3");
				strcpy(name, "        MP3");
				break;
			case 	FS_STATE_JPEG:
				strcpy(dirname, "/JPEG");
				strcpy(name, "        JPG");
				break;
			case 	FS_STATE_GAME:
				strcpy(dirname, "/GAME");
				strcpy(name, "        NES");
				break;
			case 	FS_STATE_OTHER:										
				strcpy(dirname, "/MOVIES");
				strcpy(name, "        MPG");
				break;
			default:
				strcpy(dirname, "/");
				strcpy(name, "        MPG");
				break;
		}

		strcpy(oldname, name);
		for(i=0;i<strlen(filename);i++) {
			oldname[i] = filename[i];
		}

		strcpy(newname, name);
		for(i=0;i<strlen(newfilename);i++) {
			newname[i] = newfilename[i];
		}
		
		printf("INFO: DIR[%s] oldname[%s]->[%s]\n",dirname ,oldname, newname);
		FS_cd(dirname);
		FS_dir();
		FS_rename(newname, oldname); //MIKEY
		FS_dir();
	}
}


int cache_FILE_write(FILE_INFO *fp, void *buf, UINT32 count, UINT8 opt) // opt=1 flush_cache, force write to hdd
{
	UINT8 *cachebuf=(BYTE *)(COPYBUFSTART);
	UINT8 *dst;
	static UINT32 leftlen=0;
	int newcount=0;

	if(opt) { // force write cache(leftlen) to hdd
		FILE_write(fp, cachebuf, leftlen);	// write cache(200k) to hdd
		printf("INFO: WRITE CACHE bufsize[%x] leftlen(%d):(%d)\n",COPYBUFSIZE,leftlen,count);
		leftlen=0;
		return 0; // write cache OK
	}

	while(1) {
		if((count+leftlen)>=COPYBUFSIZE) {
			if(leftlen) { // cache not empty
				dst=(UINT8 *) (cachebuf + leftlen);
				newcount = COPYBUFSIZE - leftlen;
				memcpy(dst, buf, newcount);				
				FILE_write(fp, cachebuf, COPYBUFSIZE);	// write cache(COPYBUFSIZE) to hdd
//				printf("INFO: WRITE CACHE bufsize[%x] leftlen(%d):(%d)\n",COPYBUFSIZE,leftlen,count);
				buf= (UINT8 *)(buf + newcount);
				count-=newcount;
				leftlen=0;
			}	
			else { // >=COPYBUFSIZE, write to hdd 
				FILE_write(fp, buf, COPYBUFSIZE); 	// write buf(COPYBUFSIZE) to hdd
//				printf("INFO: WRITE BUF bufsize[%x] leftlen(%d):(%d)\n",COPYBUFSIZE,leftlen,count);
				buf= (UINT8 *)(buf + COPYBUFSIZE);
				count-=COPYBUFSIZE;
			}
		}
		else { // <COPYBUFSIZE, write to cache
			dst=(UINT8 *) (cachebuf + leftlen);
			memcpy(dst, buf, count);
			leftlen+=count;
//			printf("INFO: CACHE dst[%x] leftlen(%d):(%d)\n",dst,leftlen,count);
			return 0; // write cache OK
		}
	}
}

UINT32 stream_FILE_write(void *buf, UINT32 count)
{
	FILE_INFO *fp=&copy_vcd_fd;
	return cache_FILE_write(fp, buf, count, 0);	// opt=1 flush_cache, force write to hdd
}

UINT32 flush_stream_FILE_write()
{
	FILE_INFO *fp=&copy_vcd_fd;
	return cache_FILE_write(fp, NULL, 0, 1);	// opt=1 flush_cache, force write to hdd
}

#endif //#ifdef SUPPORT_HDD_ACCESS


