#include "user_init.h"
#include "global.h"
#include "func.h" 
#include "memmap.h"
#include "util.h" 
#include "graph.h"
#include "framebuf.h"
#include "macro.h"
#include "stc.h"
#include "cfont.h"
#include "vfdfunc.h"
#include "osd.h"
#include "image.h"
#include "nesinit.h"
#include "fs96602.h"
#include "fsNAV.h"
#include "fsGUI.h"
#include "fsGUI1.h"
#include "user_if.h"
#include "user_init.h"

#ifdef SUPPORT_HDD_ACCESS

//MIKEY
#define	D	printf("INFO: __%d__(%s:%s)\n",__LINE__,__FILE__,__FUNCTION__);
char *strcpy();

//IOP IR control interface
//register mapping of RISC register
#define IR_PORT			5
//control flag
#define IR_RDY			(1<<15)
#define IR_REPEAT		(1<<14)
#define IR_REPLACE		(1<<13)
extern const BYTE ir_mapcode[256];
#include "ircode.h"

#ifdef HDD_MODIFY_INDEX_TEST
#include "fsMidiUI.h" 
#include "alpha.h"

#define SUPPORT_PINYIN_INPUT
extern void osd_Clear_Region(BYTE , BYTE );
#endif//#ifdef HDD_MODIFY_INDEX_TEST

UINT32 ir_rx_empty()
{
	UINT32 rx;
	rx = regs0->iop_data[IR_PORT];
	if (rx & IR_RDY)
		return 0;
	return 1;	
}


UINT32 ir_getch()
{
	UINT32 rx;	

	rx = regs0->iop_data[IR_PORT];
	if (rx & IR_RDY) {
		regs0->iop_data[IR_PORT]=rx & ~IR_RDY;
        	rx = reverse_fun(rx);
        	rx = ir_mapcode[(BYTE) rx];
		printf("INFO: IR[%x]\n",rx);
		return rx; //OK
	}
	return IRC_NULL; // ERROR
}


#define	CD_FP	iso9660_file[pFsJpeg->file_array[pFsJpeg->file_will]]
#define	STARTX		(5)
#define	LINEONE		(236+5)
#define	LINEONE_UL	(LINEONE+3)
#define	LINETWO		(LINEONE+15)
#define	LINETWO_UL	(LINETWO+3)






int do_copy(UINT8 *name)
{
	extern UINT8 f_do_copy_vcd;
	extern UINT8 f_vcd;
	extern int copy_cd_to_hdd();
	UINT8 states[10]={0, FS_STATE_MP3, FS_STATE_JPEG, FS_STATE_OTHER, 0};
	int state=0;
	if(CD_FP.type<=4)
		state = states[CD_FP.type];
	printf("\nINFO: COPY this file[%s]->[%s] msf[%x] len(%d) type(%d)->(%d)\n",CD_FP.name,name, CD_FP.loc, CD_FP.size, CD_FP.type, state);
	if(f_vcd) { // vcd/svcd
		UINT32 newvcdsize;
		f_do_copy_vcd=1;
		newvcdsize = ((CD_FP.size+2048-1)/2048) * 2352;
		printf("MIKEY: VCD: sz(%ld) -> newvcdsize(%ld)\n", CD_FP.size, newvcdsize);
		copy_cd_to_hdd(name, CD_FP.loc, newvcdsize, state);
	}
	else 
		copy_cd_to_hdd(name, CD_FP.loc, CD_FP.size, state);
	CD_FP.name[0]='<';	// FILE COPY MARK
	return 0;
}

int do_rm()
{
	extern UINT32 rm_file_from_hdd();
	UINT8 states[10]={0, FS_STATE_MP3, FS_STATE_JPEG, FS_STATE_OTHER, 0};
	int state=0;
	if(CD_FP.type<=4)
		state = states[CD_FP.type];
	printf("\nINFO: del this file[%s] msf[%x] len(%d) type(%d)->(%d)\n",CD_FP.name, CD_FP.loc, CD_FP.size, CD_FP.type, state);
	rm_file_from_hdd(CD_FP.name, CD_FP.loc, CD_FP.size, state);
	CD_FP.name[0]='/';	// FILE COPY MARK
	return 0;
}


int do_rename(UINT8 *newname)
{
	extern UINT32 rename_file_from_hdd();
	UINT8 states[10]={0, FS_STATE_MP3, FS_STATE_JPEG, FS_STATE_OTHER, 0};
	int state=0;
	if(CD_FP.type<=4)
		state = states[CD_FP.type];
	printf("\nINFO: rename this file[%s] msf[%x] len(%d) type(%d)->(%d)\n",CD_FP.name, CD_FP.loc, CD_FP.size, CD_FP.type, state);
	rename_file_from_hdd(newname, CD_FP.name,CD_FP.loc, CD_FP.size, state);
	strcpy(CD_FP.name, newname);
	return 0;
}


int fsgui_100(int p)
{
#ifdef HDD_FILE_MANAGEERUI
        fileManageui_DrawProcessBar(p);
        return 0;
#else
	static int pp=-1;
	UINT8 buf[64];
	if(pp==p)
		return 0;
	pp=p;	
	printf("INFO: COPY(%d%c)\n",p,'%');
	psprintf(buf, "%d%%", p);
	FSGUI_FillFrameBuf(STARTX + 16*9 , LINETWO ,4*9, 12,BK_GROUNDY,BK_GROUNDCRCB);
	FSGUI_ShowString(STARTX + 16*9, LINETWO, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
	FSGUI_FillFrameBuf(STARTX + 21*9 , LINETWO ,100, 12,WHITE_Y,WHITE_CRCB);
	FSGUI_FillFrameBuf(STARTX + 21*9 , LINETWO ,p, 12,YELLOW_Y,YELLOW_CRCB);
	if(pp==100)
		pp=-1;
	return 0;
#endif
}


int fsgui_rename()
{
	UINT8 buf[64];
	UINT8 name[16];
	int i;
	UINT32 ch=IRC_NULL;
	int run=1;
	int k=0;
	int ok=0;
	int f_update=0;


D	if(CD_FP.name[0]=='<' || CD_FP.name[0]=='/') // FILE MARK COPY'<' DEL'/'
		return 0;

	FSGUI_FillFrameBuf(0,236,352,48,BK_GROUNDY,BK_GROUNDCRCB);

	for(i=0;i<8;i++) {
		name[i]=0x20;
	}
	name[i]=0x0;
	for(i=0;i<8;i++) {
		if(CD_FP.name[i]==0x0) {
			break;
		}	
		name[i]=CD_FP.name[i];
	}
	
	psprintf(buf, "FROM [%s] SIZE:%ldK", name, (CD_FP.size)/1024);
	printf("%s\n",buf);
	FSGUI_ShowString(STARTX, LINEONE, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);


	psprintf(buf, "  TO [%s]", name);
	FSGUI_ShowString(STARTX, LINETWO, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
	psprintf(buf, "      ________");
	FSGUI_ShowString(STARTX, LINETWO_UL, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);

	FSGUI_ReplaceFrameBuf(STARTX + 6*9 , LINETWO ,8*9, 12,BK_GROUNDY,BK_GROUNDCRCB,HL_Y,HL_CRCB);

	while(run) {
		if(ir_rx_empty()) // IR EMPTY
			continue;

		ch = ir_getch();
		switch(ch) {
			case IRC_NULL:
				break;
			case IRC_SELECT:
				if(ok==1) {
					run=0;
					FSGUI_FillFrameBuf(STARTX + 16*9 , LINETWO ,4*9, 12,BK_GROUNDY,BK_GROUNDCRCB);
					do_rename(name);
					delay_1ms(1000);
					break;
				}	
				printf("COPY IR[%x]->[%s]",ch, "IRC_SELECT");
				psprintf(buf, "  TO [%s]  OK", name);
				FSGUI_FillFrameBuf(STARTX + 6*9 , LINETWO ,8*9, 12,BK_GROUNDY,BK_GROUNDCRCB);
				FSGUI_ShowString(STARTX, LINETWO, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
				FSGUI_ReplaceFrameBuf(STARTX + 16*9 , LINETWO ,4*9, 12,BK_GROUNDY,BK_GROUNDCRCB,HL_Y,HL_CRCB);
				k=0;
				ok=1;
				break;
#ifdef MIKEY_MOREKEY
#else
			case IRC_DOWN:
				if(k>=0) {
					name[k]= name[k]+1;
					if(name[k]<'A' || name[k]>'Z')
						name[k]= 'A';
					f_update++;
				}
				break;
			case IRC_UP:
				if(k>=0) {
					name[k]= name[k]-1;
					if(name[k]<'A' || name[k]>'Z')
						name[k]= 'Z';
					f_update++;
				}
				break;
			case IRC_LEFT:
				if(k>=0) {
					name[k]=' ';
					f_update++;
					k--;
					if(k<=0)
						k=0;
				}
				break;
			case IRC_RIGHT:
				k++;
				if(k>=7)
					k=7;
				f_update++;
				break;
			case IRC_P10:
#endif
			case IRC_0:
			case IRC_1:
			case IRC_2:
			case IRC_3:
			case IRC_4:
			case IRC_5:
			case IRC_6:
			case IRC_7:
			case IRC_8:
			case IRC_9:
				if(ok==1)
					break;
				if(k==0) {
					for(i=0;i<8;i++) {
						name[i]=0x20;
					}
				}	
#ifdef MIKEY_MOREKEY
#else
				if(ch==IRC_P10)
					name[k]='-';
				else
#endif
				name[k]=ch+0x30;
				f_update++;
				k++;
				if(k>=7) {
					k=7;
				}	
				break;
			case IRC_RETURN:
			case IRC_STOP:
				run=0;
				break;
			default:
				break;
		}

		if(f_update) {
			psprintf(buf, "  TO [%s]", name);
			FSGUI_FillFrameBuf(STARTX + 6*9 , LINETWO ,8*9, 12,HL_Y,HL_CRCB);
			FSGUI_ShowString(STARTX, LINETWO, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);			
			f_update=0;
		}	
	}

	FSGUI_FillFrameBuf(0,236,352,48,BK_GROUNDY,BK_GROUNDCRCB);
	FSGUI_Menu();
	FSGUI_Refresh();
	return 0;
}

int fsgui_del()
{
	UINT8 buf[64];
	UINT8 name[16];
	int i;
	UINT32 ch=IRC_NULL;
	int run=1;


D	if(CD_FP.name[0]=='<' || CD_FP.name[0]=='/') // FILE MARK COPY'<' DEL'/'
		return 0;

	FSGUI_FillFrameBuf(0,236,352,48,BK_GROUNDY,BK_GROUNDCRCB);

	for(i=0;i<8;i++) {
		name[i]=0x20;
	}
	name[i]=0x0;
	for(i=0;i<8;i++) {
		if(CD_FP.name[i]==0x0) {
			break;
		}	
		name[i]=CD_FP.name[i];
	}
	
	psprintf(buf, "FILE [%s] SIZE:%ldK", name, (CD_FP.size)/1024);
	printf("%s\n",buf);
	FSGUI_ShowString(STARTX, LINEONE, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);


	psprintf(buf, "PRESS KEY 1:DELETE 2:RENAME");
	FSGUI_ShowString(STARTX, LINETWO, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);

	while(run) {
		if(ir_rx_empty()) // IR EMPTY
			continue;

		ch = ir_getch();
		switch(ch) {
			case IRC_NULL:
				break;
			case IRC_1:
				FSGUI_ReplaceFrameBuf(STARTX + 10*9 , LINETWO ,8*9, 12,BK_GROUNDY,BK_GROUNDCRCB,HL_Y,HL_CRCB);
				do_rm();
				run=0;
				break;
			case IRC_2:
				FSGUI_ReplaceFrameBuf(STARTX + 19*9 , LINETWO ,8*9, 12,BK_GROUNDY,BK_GROUNDCRCB,HL_Y,HL_CRCB);
				fsgui_rename();
				run=0;
				break;
			case IRC_RETURN:
			case IRC_STOP:
				run=0;
				break;
			default:
				run=0;
				break;
			break;
		}
	}

	FSGUI_FillFrameBuf(0,236,352,48,BK_GROUNDY,BK_GROUNDCRCB);
	FSGUI_Menu();
	FSGUI_Refresh();
	return 0;
}

#define	IFP	iso9660_file[file_ptr]


int fsgui_cdcopy()
{
	extern UINT8 f_do_copy_vcd;
	extern UINT8 f_vcd;
	extern int copy_cd_to_hdd();
	UINT8 states[10]={0, FS_STATE_MP3, FS_STATE_JPEG, FS_STATE_OTHER, 0};
	int state=0;
	int file_ptr=0;
	UINT8 buf[64];
	UINT8 name[16];
	int i;

	for(file_ptr=0;file_ptr<pFsJpeg->iso9660_file_cnt;file_ptr++) {
		if(IFP.name[0]=='<' || IFP.name[0]=='/') // FILE MARK COPY'<' DEL'/'
			continue;
		if(IFP.type<=4)
			state = states[IFP.type];
		printf("\nINFO: COPY this file[%s] msf[%x] len(%d) type(%d)->(%d)\n",IFP.name, IFP.loc, IFP.size, IFP.type, state);

		FSGUI_FillFrameBuf(0,236,352,48,BK_GROUNDY,BK_GROUNDCRCB);

		for(i=0;i<8;i++) {
			name[i]=0x20;
		}
		name[i]=0x0;
		for(i=0;i<8;i++) {
			if(IFP.name[i]==0x0) {
				break;
			}	
			name[i]=IFP.name[i];
		}
	
		psprintf(buf, "COPY [%s] SIZE:%ldK", name, (IFP.size)/1024);
		printf("%s\n",buf);
		FSGUI_ShowString(STARTX, LINEONE, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);

		psprintf(buf, "%3d%c [%d/%d]",(file_ptr)*100/pFsJpeg->iso9660_file_cnt,'%', file_ptr+1, pFsJpeg->iso9660_file_cnt);
		FSGUI_ShowString(STARTX, LINETWO, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);

		if(f_vcd) { // vcd/svcd
			UINT32 newvcdsize;
			f_do_copy_vcd=1;
			newvcdsize = ((IFP.size+2048-1)/2048) * 2352;
			printf("MIKEY: VCD: sz(%ld) -> newvcdsize(%ld)\n", IFP.size, newvcdsize);
			copy_cd_to_hdd(IFP.name, IFP.loc, newvcdsize, state);
		}
		else 
			copy_cd_to_hdd(IFP.name, IFP.loc, IFP.size, state);
		IFP.name[0]='<';	// FILE COPY MARK
		psprintf(buf, "%3d%c [%d/%d]",(file_ptr+1)*100/pFsJpeg->iso9660_file_cnt,'%', file_ptr+1, pFsJpeg->iso9660_file_cnt);
		FSGUI_ShowString(STARTX, LINETWO, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
	}
	return 0;
}


int fsgui_copy()
{
#ifndef HDD_FILE_MANAGEERUI
	UINT8 buf[64];
#endif     
	UINT8 name[16];
	int i;
	UINT32 ch=IRC_NULL;
	int run=1;
	int ok=0;
#ifdef SUPPORT_HDD_DELETEFILE
        BYTE numName[6];
        int codeNo =0;
#ifndef SUPPORT_HDD_DELETEFILE
        BYTE IsDelFile =0;
#endif
#endif
        int k = 0;
#ifdef HDD_FILE_MANAGEERUI
        int retflag;
#endif
#ifndef SUPPORT_HDD_DELETEFILE
      if (CD_FP.name[0] == '<' || CD_FP.name[0] == '/') // FILE MARK COPY'<' DEL'/'
      		return;
#endif     
#ifdef HDD_FILE_MANAGEERUI
        Manageui_SetNewFile(CD_FP.name,(CD_FP.size)/1024);
        fileManageui_Init();
#else 
#ifdef SUPPORT_HDD_DELETEFILE
    if (!IsDelFile)
    {
#endif
	FSGUI_FillFrameBuf(0,236,352,48,BK_GROUNDY,BK_GROUNDCRCB);
      for (i = 0; i < 8; i++)
        {
		name[i]=0x20;
	}
	name[i]=0x0;
      for (i = 0; i < 8; i++)
        {
          if (CD_FP.name[i] == 0x0)
            {
			break;
		}	
		name[i]=CD_FP.name[i];
	}
	psprintf(buf, "COPY [%s] SIZE:%ldK", name, (CD_FP.size)/1024);
	printf("%s\n",buf);
	FSGUI_ShowString(STARTX, LINEONE, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);

#ifdef SUPPORT_HDD_DELETEFILE
        for (i = 0; i < 5; i++)
        {
            numName[i]=0x20;
        }

#ifdef ADD_NEWFILE_SEQUENCE
#ifdef SUPPORT_HDD_DELETEFILE
        if (!IsDelFile)
#endif
        {
            codeNo =GetNextNullCell();
            if (codeNo)
                printf("new code no is %d\n",codeNo);
            else
            {
                printf("Error:can't find code\n");
                return 0;
            }
        }
        for (i = 5; i > 0; i--)
        {
            numName[i-1]=(codeNo%10)+'0';
            codeNo/=10;
        }
//      print_block(numName,6);
        codeNo =GetNextNullCell();
        
#endif
        numName[5]=0x0;
        psprintf(buf, "  TO [%s]", numName);
#else
	psprintf(buf, "  TO [%s]", name);
#endif
	FSGUI_ShowString(STARTX, LINETWO, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
#ifdef SUPPORT_HDD_DELETEFILE
        psprintf(buf, "      _____");
        FSGUI_ShowString(STARTX, LINETWO_UL, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
        FSGUI_ReplaceFrameBuf(STARTX + 6*9 , LINETWO ,5*9, 12,BK_GROUNDY,BK_GROUNDCRCB,HL_Y,HL_CRCB);
#else
	FSGUI_ShowString(STARTX, LINETWO_UL, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
	FSGUI_ReplaceFrameBuf(STARTX + 6*9 , LINETWO ,8*9, 12,BK_GROUNDY,BK_GROUNDCRCB,HL_Y,HL_CRCB);
#endif  
#ifdef SUPPORT_HDD_DELETEFILE
        }
#endif
#endif
      while (run)
        {
		if(ir_rx_empty()) // IR EMPTY
			continue;
		ch = ir_getch();
                switch (ch)
                  {
			case IRC_UP:
#ifdef HDD_FILE_MANAGEERUI
                            fileManageui_IrUp();
#endif
				break;
			case IRC_DOWN:
#ifdef HDD_FILE_MANAGEERUI
                        fileManageui_IrDown();
                        break;
#else                        
#ifdef SUPPORT_HDD_DELETEFILE
			if (CD_FP.name[0] == '<' || CD_FP.name[0] == '/') // FILE MARK COPY'<' DEL'/'
				break;
                        if (IsDelFile)
                    {
                            IsDelFile =0;
                            FSGUI_FillFrameBuf(0,236,352,48,BK_GROUNDY,BK_GROUNDCRCB);
                            for (i = 0; i < 8; i++)
                        {
                                name[i]=0x20;
                    }
                            name[i]=0x0;
                            for (i = 0; i < 8; i++)
                    {
                                if (CD_FP.name[i] == 0x0)
                        {
                                    break;
                        }
                                name[i]=CD_FP.name[i];
                            }
                            psprintf(buf, "COPY [%s] SIZE:%ldK", name, (CD_FP.size)/1024);
                            FSGUI_ShowString(STARTX, LINEONE, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
                            for (i = 0; i < 5; i++)
                        {
                                numName[i]=0x20;
                        }
                            numName[i]=0x0;
                            psprintf(buf, "  TO [%s]", numName);
                            FSGUI_ShowString(STARTX, LINETWO, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
                            psprintf(buf, "      _____");
                            FSGUI_ShowString(STARTX, LINETWO_UL, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
                            FSGUI_ReplaceFrameBuf(STARTX + 6*9 , LINETWO ,5*9, 12,BK_GROUNDY,BK_GROUNDCRCB,HL_Y,HL_CRCB);
                    }
                        else
                    {
                            IsDelFile =1;
                            FSGUI_FillFrameBuf(0,236,352,48,BK_GROUNDY,BK_GROUNDCRCB);
                            for (i = 0; i < 5; i++)
                        {
                                numName[i]=0x20;
                        }
                            numName[i]=0x0;
                            psprintf(buf, "    DELETE FILE NO.[%s]", numName);
                            FSGUI_ShowString(STARTX+9, LINETWO, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
                            psprintf(buf, "_____");
                            FSGUI_ShowString(STARTX+ 21*9, LINETWO_UL, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
                            FSGUI_ReplaceFrameBuf(STARTX + 21*9 , LINETWO ,5*9, 12,BK_GROUNDY,BK_GROUNDCRCB,HL_Y,HL_CRCB);
                    }
                    break;
#endif
#endif
			case IRC_LEFT:
#ifdef HDD_FILE_MANAGEERUI
                        fileManagerui_IrLeft();
                        break;
#endif  
			case IRC_RIGHT:
                            printf("IRC_RIGHT\n");
#ifdef HDD_FILE_MANAGEERUI
                            fileManagerui_IrRight();
#endif
				break;
			case IRC_SELECT:
#ifndef HDD_FILE_MANAGEERUI
                            if (ok == 1)
                            {
#ifdef SUPPORT_HDD_DELETEFILE
                                if (IsDelFile)
                      {
                                    printf("DELETE FILE %d\n",codeNo);
                                    DeleteUserFile(codeNo);
                                    run = 0;
                                    break;
                      }
                                else
                                {
                                    if (SaveIndexFile(UpdataUIindex()))
                      {
                                        printf("stFileInfo.filename %s\n",stFileInfo.filename);
                                        strcpy(name,stFileInfo.filename);
                      }else
                      {
                                        printf("ERROR:Can't save MEGIDX\n");    
                                        run = 0;
				break;
                                    }
                                }
#endif
                                run=0;
                                FSGUI_FillFrameBuf(STARTX + 16 * 9, LINETWO, 4 * 9, 12,
                                    BK_GROUNDY, BK_GROUNDCRCB);
                                do_copy(name);
                                delay_1ms(1000);
                                break;
                            } 
#endif                            
#ifdef SUPPORT_HDD_DELETEFILE
#ifdef ADD_NEWFILE_SEQUENCE
#ifdef HDD_FILE_MANAGEERUI
                            retflag =fileManageui_IrSelect();
                            codeNo =fileManageui_GetSongCode();
                            printf("irselect return word %d  codeNo %d\n",retflag,codeNo);
                            
                            k = 0;
                            for (i = 0; i <5; i++)
                            {
                                numName[i]=0x20;
                            }
                            numName[i] =0;
                            if (retflag ==2)
                      {
                                printf("del code is %d\n",codeNo);
                                if (IsfailCode(codeNo) ==ERROR_REPEAT_CODE)
                          {
                                    printf("DELETE FILE %d\n",codeNo);
                                    DeleteUserFile(codeNo);
                                    fileManageui_IrReturn();
                                    break;
                                }
                            }
#else
                            if (IsDelFile)
                            {
                                if (IsfailCode(codeNo) ==ERROR_REPEAT_CODE)
                                {
                                    printf("name %s\n",numName);
                                    psprintf(buf, "    DELETE FILE NO.[%s] OK", numName);
                                    FSGUI_FillFrameBuf(STARTX + 21* 9, LINETWO, 5 * 9, 12, BK_GROUNDY,
                                                       BK_GROUNDCRCB);
                                    FSGUI_ShowString(STARTX+9, LINETWO, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
                                    FSGUI_ReplaceFrameBuf(STARTX +  28* 9, LINETWO, 2 * 9, 12,
                                                          BK_GROUNDY, BK_GROUNDCRCB, HL_Y, HL_CRCB);
                          }  
                                break;
                          }
#endif
                            else
#ifdef HDD_FILE_MANAGEERUI
                            if (retflag ==1)
#endif
                            {
					run=0;
                                if ((!IsfailCode(codeNo))&&(codeNo))
                                {
                                    SetDefaultFileInfo(codeNo);
                                }else
                                {
                                    printf("WARiNG:Overlap with exist fileCode\n");    
#ifdef HDD_FILE_MANAGEERUI
                                    fileManageui_close();
#endif
                                    break;
                                }
                                if (SaveIndexFile(UpdataUIindex()))
                                {
                                    printf("stFileInfo.filename %s\n",stFileInfo.filename);
                                    strcpy(name,stFileInfo.filename);
                                }else
                                {
                                    printf("ERROR:Can't save MEGIDX\n");    
#ifdef HDD_FILE_MANAGEERUI
                                    fileManageui_close();
#endif 
                                    break;
                                }
#ifndef HDD_FILE_MANAGEERUI
                                FSGUI_FillFrameBuf(0,236,352,48,BK_GROUNDY,BK_GROUNDCRCB);
                                psprintf(buf, "COPY [%s] SIZE:%ldK", name, (CD_FP.size)/1024);
                                printf("%s\n",buf);
                                FSGUI_ShowString(STARTX, LINEONE, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
                                psprintf(buf, "  TO [%05d]  OK",codeNo );
                                FSGUI_FillFrameBuf(STARTX + 6 * 9, LINETWO, 5 * 9, 12, BK_GROUNDY,
                                                   BK_GROUNDCRCB);
                                FSGUI_ShowString(STARTX, LINETWO, buf, FS_FONTCOLOR_FILE_Y,
                                                 FS_FONTCOLOR_FILE_CrCb);
                                FSGUI_ReplaceFrameBuf(STARTX + 12 * 9, LINETWO, 4 * 9, 12,
                                                      BK_GROUNDY, BK_GROUNDCRCB, HL_Y, HL_CRCB);
                        FSGUI_FillFrameBuf(STARTX + 16 * 9, LINETWO, 4 * 9, 12,
                                           BK_GROUNDY, BK_GROUNDCRCB);
#endif        
                        do_copy(name);
                        delay_1ms(1000);
#ifndef HDD_FILE_MANAGEERUI
                                fileManageui_close();
#endif        
                        break;
                      } 
#ifdef HDD_FILE_MANAGEERUI
                            else if(retflag ==3)
                            {
                                fileManageui_close();
                                run = 0;
                            }
                            break;
#endif
#else
                            if (k<5) {
                                    printf("input Num less than 5\n");
                                    break;
                    }
                            for (i=0;i<5;i++)
                                  {
                                codeNo*=10;
                                if (numName[i]!=0x20)
                                      {
                                    codeNo+=numName[i]-'0';
                                      } 
                                  }
                            printf("codeNo is %d k is %d\n",codeNo,k);
                            if (IsDelFile)
                                {
                                if (IsfailCode(codeNo) ==ERROR_REPEAT_CODE)
                                {
                                    printf("name %s\n",numName);
                                    psprintf(buf, "    DELETE FILE NO.[%s] OK", numName);
                                    FSGUI_FillFrameBuf(STARTX + 21* 9, LINETWO, 5 * 9, 12, BK_GROUNDY,
                                                       BK_GROUNDCRCB);
                                    FSGUI_ShowString(STARTX+9, LINETWO, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
                                    FSGUI_ReplaceFrameBuf(STARTX +  28* 9, LINETWO, 2 * 9, 12,
                                                          BK_GROUNDY, BK_GROUNDCRCB, HL_Y, HL_CRCB);

                            }
                        }
                            else
                            {
                                if ((!IsfailCode(codeNo))&&(codeNo))
                                {
                                    SetDefaultFileInfo(codeNo);
                                }else
                                {
                                    printf("WARiNG:Overlap with exist fileCode\n");    
                        run = 0;
					break;
				}	
                                printf("name %s\n",name);
                                psprintf(buf, "  TO [%s]  OK", numName);
                                FSGUI_FillFrameBuf(STARTX + 6 * 9, LINETWO, 5 * 9, 12, BK_GROUNDY,
                                                   BK_GROUNDCRCB);
                                FSGUI_ShowString(STARTX, LINETWO, buf, FS_FONTCOLOR_FILE_Y,
                                                 FS_FONTCOLOR_FILE_CrCb);
                                FSGUI_ReplaceFrameBuf(STARTX + 12 * 9, LINETWO, 4 * 9, 12,
                                                      BK_GROUNDY, BK_GROUNDCRCB, HL_Y, HL_CRCB);
                            }
#endif
#else
				printf("COPY IR[%x]->[%s]",ch, "IRC_SELECT");
				psprintf(buf, "  TO [%s]  OK", name);
                    FSGUI_FillFrameBuf(STARTX + 6 * 9, LINETWO, 8 * 9, 12, BK_GROUNDY,
                                       BK_GROUNDCRCB);
                    FSGUI_ShowString(STARTX, LINETWO, buf, FS_FONTCOLOR_FILE_Y,
                                     FS_FONTCOLOR_FILE_CrCb);
                    FSGUI_ReplaceFrameBuf(STARTX + 16 * 9, LINETWO, 4 * 9, 12,
                                          BK_GROUNDY, BK_GROUNDCRCB, HL_Y, HL_CRCB);
#endif
				k=0;
				ok=1;
				break;
			case IRC_GOTO:
				break;
			case IRC_REPEAT:
				printf("COPY IR[%x]->[%s]",ch, "IRC_REPEAT");
				fsgui_cdcopy();
				run=0;
				break;
			case IRC_0:
			case IRC_1:
			case IRC_2:
			case IRC_3:
			case IRC_4:
			case IRC_5:
			case IRC_6:
			case IRC_7:
			case IRC_8:
			case IRC_9:
#ifdef ADD_NEWFILE_SEQUENCE
                            break;
#else
				if(ok==1)
					break;
#ifdef  SUPPORT_HDD_DELETEFILE            
                            if (k == 0)
                                  {
                                for (i = 0; i <5; i++)
						{
                                    numName[i]=0x20;
						}
                                numName[i] =0;
						 }				
                            if(k>=5)
                                        break;
                            numName[k]=ch+0x30;
                            k++;
                          
                            printf(" numName %s\n",numName);
                            if (IsDelFile)
						{
                                psprintf(buf, "    DELETE FILE NO.[%s]", numName);
                                FSGUI_FillFrameBuf(STARTX + 21*9 , LINETWO ,5*9, 12,HL_Y,HL_CRCB);
                                FSGUI_ShowString(STARTX+9, LINETWO, buf, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
						}
					  else
					  	{			  	
                                psprintf(buf, "  TO [%s]", numName);
                                FSGUI_FillFrameBuf(STARTX + 6*9 , LINETWO ,5*9, 12,HL_Y,HL_CRCB);
                                FSGUI_ShowString(STARTX, LINETWO, buf, FS_FONTCOLOR_FILE_Y,
                                                 FS_FONTCOLOR_FILE_CrCb);
                          }
#else
                    if (k == 0)
                    {
                        for (i = 0; i < 8; i++)
                        {
						name[i]=0x20;
					}
				}	
				if(k>=8)
					break;
				name[k]=ch+0x30;
				k++;
				psprintf(buf, "  TO [%s]", name);
				FSGUI_FillFrameBuf(STARTX + 6*9 , LINETWO ,8*9, 12,HL_Y,HL_CRCB);
                    FSGUI_ShowString(STARTX, LINETWO, buf, FS_FONTCOLOR_FILE_Y,
                                     FS_FONTCOLOR_FILE_CrCb);
#endif
				break;
#endif
			case IRC_3D:
				break;
			case IRC_RETURN:
#ifdef HDD_FILE_MANAGEERUI
                        if (!fileManageui_IrReturn())
                            {
                                run =0;
                            }
#endif
                    break;
			case IRC_STOP:
#ifdef  HDD_FILE_MANAGEERUI              
#endif
				run=0;
				break;
			case IRC_NULL:
				break;
			default:
				printf("COPY IR[%x]",ch);
			break;
		}
            }
#ifdef  HDD_FILE_MANAGEERUI              
        fileManageui_close();
#endif      
	FSGUI_FillFrameBuf(0,236,352,48,BK_GROUNDY,BK_GROUNDCRCB);
	FSGUI_Menu();
	FSGUI_Refresh();
	return 0;
}


#endif //#ifdef SUPPORT_HDD_ACCESS

