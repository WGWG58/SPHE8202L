#ifndef __SYSTEM_SETUP_API_H

#define __SYSTEM_SETUP_API_H
#include "types.h"
#include "user_init.h"
#include "global.h"
#include "osd.h"
#include "kernel.h"
#include "setup_def.h"

#ifdef DVD_SETUP_REENG
#include "setup_VA.h"
#else
#include "setup_page.h"
#endif //DVD_SETUP_REENG




void Set_SetUp_Item_Value(int page,int index,BYTE data);
UINT8  Get_Setup_Item_Value(int page,int index);

UINT8 Get_TV_SYSTEM_Format(int page,int index);
void  Set_TV_SYSTEM_Format(int page,int index,int id,int data);

void Set_Video_Type(int page,int index,int id,int data);
UINT8 Get_Video_Type(int page,int index);

void Set_TV_Type(int page,int index,int data);
UINT8 Get_TV_Type(int page,int index);

void Set_Screen_Save(int page,int index,int id,int data);
UINT8 Get_Screen_Sav(int page,int index);

#endif
