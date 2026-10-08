#ifndef RW_NVMEM_H
#define RW_NVMEM_H

#include "global.h"
#include "types.h"
#include "setup_VA.h"
#include "memmap_I2C.h"

#define TYPE_SETUP     0
#define TYPE_SETUP_W   1
#define TYPE_SETUP_NW  2
#define TYPE_RESUME    3
#define TYPE_DISC_ID   4
#define TYPE_DRM       5
#define ID_LEN 4


#define SETUP_INF_SIZE (SEG_1_I2C_END - ROMCHECKSUM_I2C_YA)

#if (defined(SAME_DISC_RESUME) || defined(POWER_RESUME) || defined(RECORD_KEY)) && defined(RW_NVMEM)
#define RESUME_INF_SIZE (SEG_2_I2C_END - SEG_2_I2C_YA)
#endif

#define DRM_INF_SIZE DRM_REG_CODE_I2C_ADD_LEN



int WriteToNVMEM(int inf_type, int addr, BYTE *pBuffer, UINT32 size);
int ReadFromNVMEM(int inf_type, int addr, BYTE *pBuffer, UINT32 size);

#endif
