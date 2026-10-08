//====================================================================================
// memmap0b.h
// 8200 (before) 32M memory mapping
// Creator  : wthsin
// Maintain :  
// -----------------------------------------------------------------------------------
// Revision History   
//          2004.11.12 create this file
//====================================================================================
#include "user_init.h"

 
//PMP segment
#ifdef SUPPORT_HIGH_DEFINITION_VIDEO


#define HD_FAT_TABLE_YA         (HD_BIDIR_CHROMA_END+1) 
#define HD_FAT_TABLE_SIZE       (50)
#define CF_FAT_TABLE_YA         (HD_FAT_TABLE_YA+HD_FAT_TABLE_SIZE) 
#define CF_FAT_TABLE_SIZE       (50)

#define HD_PARENT_DIR_YA        (CF_FAT_TABLE_YA+CF_FAT_TABLE_SIZE)//kenny 2005/8/16
#define HD_PARENT_DIR_SIZE      (1) 
#define HD_FS_STRUCTURE_YA      (HD_PARENT_DIR_YA+HD_PARENT_DIR_SIZE)
#define HD_FS_STRUCTURE_SIZE    (511) 


#define FS_INFO_YA              (HD_FS_STRUCTURE_YA+HD_FS_STRUCTURE_SIZE)
#define FS_INFO_SIZE            3
#define CF_HDD_INFO_YA          (FS_INFO_YA+FS_INFO_SIZE)
#define CF_HDD_INFO_SIZE        1



#define HD_FONT_YA              (CF_HDD_INFO_YA+CF_HDD_INFO_SIZE)
#define HD_FONT_SIZE            (2048)  //kenny 2005/8/31


//The following only for CF exist and copy function 
#define CF_FS_STRUCTURE_YA      (HD_FONT_YA+HD_FONT_SIZE)
#define CF_FS_STRUCTURE_SIZE    (512) 
#define CF_HD_COPY_YA           (CF_FS_STRUCTURE_YA+CF_FS_STRUCTURE_SIZE) 
#define CF_HD_COPY_SIZE         (1024)
#define CF_HDD_TEMP_YA          (CF_HD_COPY_YA+CF_HD_COPY_SIZE)
#define CF_HDD_TEMP_SIZE        1   

//liweihua 2004-12-10 14:03
#define FAT_WRITE_TEMP_YA       (CF_HDD_TEMP_YA)
#define FAT_WRITE_TEMP_SIZE     (CF_HDD_TEMP_SIZE)
#define FAT_COPY_YA             (CF_HD_COPY_YA) 
#define FAT_COPY_SIZE           (CF_HD_COPY_SIZE)
    
#else //SUPPORT_HIGH_DEFINITION_VIDEO

//PMP segment

#define HD_FAT_TABLE_YA         (4096) 
#define HD_FAT_TABLE_SIZE       (50)
#define CF_FAT_TABLE_YA         (HD_FAT_TABLE_YA+HD_FAT_TABLE_SIZE) 
#define CF_FAT_TABLE_SIZE       (50)

#define HD_PARENT_DIR_YA        (CF_FAT_TABLE_YA+CF_FAT_TABLE_SIZE)//kenny 2005/8/16
#define HD_PARENT_DIR_SIZE      (1) 
#define HD_FS_STRUCTURE_YA      (HD_PARENT_DIR_YA+HD_PARENT_DIR_SIZE)
#define HD_FS_STRUCTURE_SIZE    (511) 

#define FS_INFO_YA              (HD_FS_STRUCTURE_YA+HD_FS_STRUCTURE_SIZE)
#define FS_INFO_SIZE            3
#define CF_HDD_INFO_YA          (FS_INFO_YA+FS_INFO_SIZE)
#define CF_HDD_INFO_SIZE        1

#define HD_FONT_YA              (CF_HDD_INFO_YA+CF_HDD_INFO_SIZE)
#define HD_FONT_SIZE            (1943)  


//The following only for CF exist and copy function 
#define CF_FS_STRUCTURE_YA      (HD_FONT_YA+HD_FONT_SIZE)
#define CF_FS_STRUCTURE_SIZE    (512) 
#define CF_HD_COPY_YA           (CF_FS_STRUCTURE_YA+CF_FS_STRUCTURE_SIZE) 
#define CF_HD_COPY_SIZE         (1024)
#define CF_HDD_TEMP_YA          (CF_HD_COPY_YA+CF_HD_COPY_SIZE)
#define CF_HDD_TEMP_SIZE        1   

//liweihua 2004-12-10 14:03
#define FAT_WRITE_TEMP_YA       (CF_HDD_TEMP_YA)
#define FAT_WRITE_TEMP_SIZE     (CF_HDD_TEMP_SIZE)
#define FAT_COPY_YA             (CF_HD_COPY_YA) 
#define FAT_COPY_SIZE           (CF_HD_COPY_SIZE)
    


#endif //SUPPORT_HIGH_DEFINITION_VIDEO
