#ifndef __OSD_ARC_TABLE_H
#define __OSD_ARC_TABLE_H

#ifdef NEWSTYLE_WINDOW
#define LT                       1
#define RT                       2
#define LB                       3
#define RB                       4

	
BYTE bBrowseLevel;
/*
int st_rtval;
int lang_rtval;
int agl_rtval;
*///xyy  2003-7-30 11:43
typedef struct
{
    UINT32 xStart;
    UINT32 yStart;
    UINT32 xLen;
    UINT32 yLen;
    BYTE   radius;
    BYTE   bkColor;
    BYTE   blackColor;
    BYTE   whiteColor;
    BYTE   region;
}ARC_REGION_LOC;

ARC_REGION_LOC arc_region_loc;
#endif    

		    
#endif
