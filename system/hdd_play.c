/*=================================================================

  hdd_play.c: Some FileSystem Info Function for HDD
  
	2002-04-28 10:00AM Created  by Verdure
	2002-06-12 08:42AM Modified by cyue
	
	  Copyright(c)2000-2002 by Worldplus Technology (ShenZhen) Co., Ltd.
	  ALL RIGHTS RESERVED
=================================================================*/

#include "config.h"
#include "global.h"
#include "ata.h"
#include "atapi_if.h"
#include "hdd_if.h"
#include "hdd_fs.h"
#include "macro.h"
#include "auddrv.h" //2004AUDDRV oliver 20041004 for using audio driver purpose
//#include "audif.h"//20020729
#include "srv2.h"
#ifdef USE_HDD //cyue: only build HDD code when need!!
#include "ninf.h"

PLAY_BLOCK PlayBlock; // Interface for lbaif.c !!
extern char  hd_play;


/*
========================================================
=   int hd_pump(char *fname)
=      polling function for HDD -streaming play!!
=  ARGUMENT(S):
=      NONE
=                     format
=  RETURN VALUE:
=      0 for no ERR
=  GLOBAL USING:
=      PlayBlock
=  2002-06-12 08:38AM Modified by cyue
=                     play continue LBAs currently 
========================================================
*/
inline int hd_pump()
{
	static int lba,bat;
	//printf(" PumpLBA=0x%x ",lba);
	if(!hd_play) return 0;
	if(!stream_full())
	{
		FILE_LINK_ITEM *pfl;
		UINT32 end_lba;
		pfl=&(PlayBlock.block[PlayBlock.curr_blk]);
		end_lba=pfl->lba+pfl->len; // should -1 for real num!!
		// Calc lba
		lba=PlayBlock.curr_lba;
		if(lba>=end_lba) //block overflow!!
		{
			pfl=&(PlayBlock.block[++PlayBlock.curr_blk]);
			if(PlayBlock.curr_blk>=MAX_FILE_LINK_ITEM) // block over
			{
				printf(" Block over!! ");
				AVD_SetMediaInterrupt();
				return 0;
			}
			else if(!(pfl->lba)) // no next block
			{
				printf(" No Next Block!! ");
				stream_append(0);
				//AVD_SetMediaInterrupt();
				return 0;
			}
			else // have next block
			{
				end_lba=pfl->lba+pfl->len;
				lba=PlayBlock.curr_lba=pfl->lba;
				printf("!!! Next Block Lba= 0x%lx !!!\n",lba);
			}
		}
		// Calc bat
		bat=STREAM_MAX_ACCESS>>9;
		if(lba+bat>=end_lba)
		{
			bat=end_lba-lba; // should +1 for real num!!
		}
		// Now lba,bat is caculated.
		//printf("Read %x-%x\n",lba,bat);
		HDD_ReadSec(stream_putheader(),lba,bat);
		stream_append(bat<<9);
		PlayBlock.curr_lba=(lba+=bat);
		polling();
	}
	return 1;
}


/*
========================================================
=   void HDD_Play(char *fname)
=      Play a file in HDD
=  ARGUMENT(S):
=      char   *fname: filename to play, 11 CHAR in 8.3 
=                     format
=  RETURN VALUE:
=      NONE
=  GLOBAL USING:
=      FDB
=  2002-06-12 08:38AM Modified by cyue
=                     play continue LBAs currently 
========================================================
*/

void HDD_Play(char *fname)
{
	UINT32 len,i,CurrentClus;
	FILE_INFO* pfdb;
	hd_play=1; // This will let polling HDD_Pump()!!
	if((pfdb=HDD_SearchFile(fname))!=NULL)
	{
		sup_set_channel(0);
		sup_on();
		HDD_BuildPlayBlock(pfdb,&PlayBlock);
		printf("\n=====  Play %s   =====\n",fname);
		// cyue test 2002/11/2 11:01¤W¤È
		{
			play_state=VCD_STATE_NORMAL;
			//play_state=VCD_STATE_IDLE;
			system_state=SYSTEM_BROWSE;
			cd_type_loaded=CDDVD;
			osd_init();
			ClearOsdMsg(0);//kenny add it 2001/5/8
		}
#ifndef SUPPORT_STREAM_BUFFER
		PlayBackStartLBA = pfdb->start_lba;
		PlayBackLength= LBA_COUNT(pfdb->fsize);
		Data_Curr_Clus=pfdb->start_clus;
		play_state = VCD_STATE_NORMAL;
		AUDIF_Set_CodingMode(AUDIF_CODING_MODE_MP2);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_MP2);
		PlayLBA(PlayBackStartLBA, PlayBackLength);
		MediaMainLoop();
#else
		stream_init();
		MacroPlayStream();
		printf("\n\n Stream Play Setted!!\n\n\n");
		MediaMainLoop();
		stream_init();
#endif
	}
	hd_play=0;
}

/*
========================================================
=   void HDD_Test()
=      Test HDD FAT Filesystem
=  ARGUMENT(S):
=      char   *fname: filename to play, 11 CHAR in 8.3 
=                     format
=  RETURN VALUE:
=      NONE
=  
=  2002-06-12 08:38AM Modified by cyue
=                     play continue LBAs currently 
========================================================
*/

//HDD_INFO HDD_Info;
void HDD_Test()
{  
	//UINT8* aa;
	UINT8* bb;
	UINT8* cc;
	//aa="test    vob";//"DREAM   MP3"
	bb="DREAM      ";
	cc="12345678   ";
	printf(__FUNCTION__" in\n");
	ata_init();//20020729
	if (HDD_Mount()==1)
	{
		{	//HDD_ReadSec(Info_buff,4205,1);
			//FS_Get_FDB(64);
			//HDD_DelFile(bb);
			//HDD_SearchFile(aa);
			//HDD_ResetFAT();
			//HDD_CreatFile(bb);
			//HDD_DelFile(bb);
			//HDD_ReadSec(buff,16583,1); 
			//print_block(buff,512*1);
			//HDD_FindFreeClus(BPB.FAT1_Start);
			//HDD_Set_FDB(aa);
			//HDD_ResetFAT();
			//FS_Get_NextClus(6);
			//HDD_LinkFileClus();
		}
		HDD_cd("/test_vob");
		HDD_dir();
		AudioSet(CODING_MODE_MP2);
		HDD_Play("/test_vob/avseq01.mpg");
		AudioSet(CODING_MODE_MP3);
		HDD_Play("01test.mp3");
		
		AudioSet(CODING_MODE_AC3);
		HDD_Play("vts_01_1.vob");
		//		while(1);
		//		HDD_Sleep(); 
	}
	printf(__FUNCTION__" out\n");
}



#endif //def USE_HDD
