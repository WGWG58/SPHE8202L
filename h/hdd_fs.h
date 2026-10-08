/*=================================================================

  hdd_info.h: Header for Some FileSystem Info Function for HDD
  
	2002-04-28 10:00AM Created  by Verdure
	2002-06-12 08:42AM Modified by cyue
	
	  Copyright(c)2000-2002 by Worldplus Technology (ShenZhen) Co., Ltd.
	  ALL RIGHTS RESERVED
=================================================================*/
#ifndef __HDD_FS_H
#define __HDD_FS_H


UINT8  HDD_Mount(void);
FILE_INFO *HDD_SearchFile(UINT8* name);
FILE_INFO *HDD_CreatFile(UINT8* name);
UINT32   HDD_DelFile(UINT8* name);


#endif/*__HDD_FS_H*/
