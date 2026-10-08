#include "user_init.h"
#include "rw_nvmem.h"
#include "total_rsm.h"

#ifdef FLASH_HISTORY
#include "rsm_upd.h"
#endif

extern int current_resume;
extern BYTE disc_resume_index[TOTAL_RESUME];
extern UINT32 rsm_flash_start_addr;


#if (defined(SAME_DISC_RESUME) || defined(POWER_RESUME) || defined(RECORD_KEY)) && defined(RW_NVMEM)
typedef struct
{
  BYTE setup_info[SETUP_INF_SIZE];

  BYTE resume_info[TOTAL_RESUME][RESUME_INF_SIZE];
  //[0 ~ TOTAL_RESUME-1] : disc_id, [TOTAL_RESUME] : disc_resume_index
  BYTE disc_id[TOTAL_RESUME+1][ID_LEN];  
  BYTE drm_info[DRM_INF_SIZE];
  // can extent other type information ...
} NVMEM_INFO;

NVMEM_INFO nv_info; 

/*** end of new data structure ***/


/* write to new nv_info structure */
int WriteToNVMEM(int inf_type, int addr, BYTE *pBuffer, UINT32 size)
{
  BYTE *p, *q;
  UINT32 iStart1, i;
  int ret=1;
  #ifdef FLASH_HISTORY
  UINT32 iStart2;
  #endif
  
  UINT32  is_write_flash =1;

  #ifdef  RW_NVMEM_DBG
  printf_w("Write to NV_MEM\n");
  FlashDelay(1000);
  #endif

  //ret = Resume_FlashEraseSector(1, 0); //for boot sector
  
  switch (inf_type)
  {
    case TYPE_SETUP_W:
      p = nv_info.setup_info;
      //printf_w("Write To NV_MEM : TYPE_SETUP_W, is_write_flash = %d\n", is_write_flash);
      break;   
    case TYPE_SETUP_NW:
      p = nv_info.setup_info;
      is_write_flash = 0;
      //printf_w("Write To NV_MEM : TYPE_SETUP, is_write_flash = %d\n", is_write_flash);
      break;   
    case TYPE_RESUME:
      p = nv_info.resume_info[current_resume];
      is_write_flash = addr;  //0 or others
      //printf_w("Write To NV_MEM : TYPE_RESUME, is_write_flash = %d\n", is_write_flash);
      break;
    case TYPE_DISC_ID:
      p = nv_info.disc_id[current_resume];
      //printf_w("Write To NV_MEM : TYPE_DISC_ID, is_write_flash = %d\n", is_write_flash);
      break;        
    case TYPE_DRM:
      p = nv_info.drm_info;
      //printf_w("Write To NV_MEM : TYPE_DRM, is_write_flash = %d\n", is_write_flash);
      break;
      
    default:
      //printf_w("Write To NV_MEM : UNKNOWN, is_write_flash = %d\n", is_write_flash);
      return -1;
  }
  iStart1 = (UINT32)p-(UINT32)&nv_info;
  
  q = pBuffer;
  for (i=0; i<size; i++)
  {
  	p[addr+i] = *q++;
  }
  if (inf_type == TYPE_DISC_ID)
  {
  	p = nv_info.disc_id[TOTAL_RESUME];
  	q = disc_resume_index;
  	#ifdef FLASH_HISTORY
  	  iStart2 = (UINT32)p-(UINT32)&nv_info;
  	  i = sizeof(nv_info);
  	  ret = Resume_Info_Write_Update(iStart2,(BYTE*)&nv_info, i, q, sizeof(disc_resume_index));
  	#endif 
  	for (i=0; i<sizeof(disc_resume_index); i++)
  	{
  		*p++ = 	*q++;
  	}
  	
  }

  #ifdef FLASH_HISTORY
    i = sizeof(nv_info);
    ret = Resume_Info_Write_Update(iStart1+addr, (BYTE*)&nv_info, i, pBuffer, size); //swpong 2006 0410
  #else  	       	 	
    if (is_write_flash)
    {
   	   ret = Resume_Info_Write(rsm_flash_start_addr,(BYTE *)&nv_info,sizeof(nv_info));
    }
  #endif 
  return ret;
  
}


/* Read from new nv_info structure */
int ReadFromNVMEM(int inf_type, int addr, BYTE *pBuffer, UINT32 size)
{
  UINT32 i;
  BYTE *p, *q;
  int result;
  
  #ifdef  RW_NVMEM_DBG
  printf_w("Read from NV_MEM\n");
  FlashDelay(1000);
  #endif
  
  //Flash_Read(&nv_info)
  //result = FlashRead(rsm_flash_start_addr, &nv_info, sizeof(nv_info)); 
  #ifdef FLASH_HISTORY
             i = sizeof(nv_info);
             result = Resume_Info_Read_Update((BYTE*)&nv_info, i);   //swpong 2006 0410
  #else  	       	 	
        result = Resume_Info_Read(rsm_flash_start_addr, (BYTE *)&nv_info,sizeof(nv_info));
  #endif        

  switch (inf_type)
  {
    case TYPE_SETUP:
      p = nv_info.setup_info;
      //printf_w("Read from NV_MEM, TYPE_SETUP\n");
      break;   
    case TYPE_RESUME:
      p = nv_info.resume_info[current_resume];
      //printf_w("Read from NV_MEM, TYPE_RESUME\n");
      break;
    case TYPE_DISC_ID:
      p = nv_info.disc_id[current_resume];
      //printf_w("Read from NV_MEM, TYPE_DISC_ID\n");
      break;        
    case TYPE_DRM:
      p = nv_info.drm_info;
      //printf_w("Read from NV_MEM, TYPE_DRM\n");
      break;
      
    default:
      return -1;
  }
  q = pBuffer;
  for (i=0; i<size; i++)
  {
  	*q++ = p[addr+i];
  }
  return result;
}  
#endif  //RW_NVMEM
