
#include "config.h"
#include "regmap.h"
#include "global.h"
#include "sio.h"
#include "epp.h"
#include "cpu.h"
#include "gpio.h"
#include "user_init.h"
#include "uartsup.h"
#include "ver.h"
#include "types.h"

//#define FLASH_SECOND_ROM                //used as 2nd ROM(for developing)
#ifdef FLASH_SECOND_ROM
    #define ROM1_OFFSET                     0x800000      //800B flash used as 2nd ROM for developing
#else
    #define ROM1_OFFSET                     0               //use 800B to boot-up for release
#endif

#define TYPE_NORMAL             0
#define TYPE_BOOT               1
#define TYPE_TROM               2

enum{
    PARALLEL_FLASH = 0, 
    SPI_FLASH, 
};


//General functions
extern void FlashDelay(int n);
extern void FlashRomEncStop(void);
extern void FlashRomEncStart(void);
extern int get_flash_type(void);

//SPI flash related variables

extern UINT32 spi_api_flash_id;
extern UINT32 spi_api_writing_command;
extern UINT32 spi_api_reading_command;
extern UINT32  spi_api_normal_writing_command;

//SPI flash related functions
extern UINT32 SPI_FlashReadID(void);
extern int SPI_FlashRead(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen);
extern int SPI_FlashWrite(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen);
extern int SPI_FlashEraseSector(UINT32 unSectorNum);
extern int SPI_FlashEraseUpgrade(unsigned char *pBuf, unsigned int dwSize);

extern void(*SPI_APP_flash_init)(void);
extern void(*SPI_APP_upgrade_init)(void);
extern void SPI_APP_set_funcPointer(UINT32 id);
extern void SPI_api_switch_2_EonSp2bitMode(void);
extern void SPI_api_switch_2_Sp2bitMode(void);
extern void SPI_api_switch_2_Sp4bitMode(void);
extern void SPI_api_switch_2_Eon1bitMode();
extern void SPI_api_switch_2_Sp1bitMode();
extern void SPI_api_switch_2_Sp4bitUpgradeMode();



//Parallel flash related functions
extern UINT16 Parallel_FlashReadID(void);
extern int Parallel_FlashRead(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen);
extern int Parallel_FlashWrite(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen);
extern int Parallel_FlashEraseSector(UINT32 unSectorNum);
extern int Parallel_FlashEraseUpgrade(unsigned char *pBuf, unsigned int dwSize);

//General function pointers for AP
extern UINT16 (*FlashReadID)(void);
extern int (*FlashRead)(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen);
extern int (*FlashWrite)(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen);
extern int (*FlashEraseSector)(UINT32 sector_num);
extern int (*FlashEraseUpgrade)(unsigned char *pBuf, unsigned int dwSize);

//resume function pointers for AP
extern int (*Resume_FlashRead)(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen);
extern int (*Resume_FlashWrite)(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen);
extern int (*Resume_FlashEraseSector)(UINT32 type, UINT32 addr);

//Initialize function pointers
extern void init_spi_flash_functions(void);
extern void init_parallel_flash_functions(void);

//resume related functions
extern int Parallel_Resume_FlashRead(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen);
extern int Parallel_Resume_FlashWrite(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen);
extern int Parallel_Resume_FlashEraseSector(UINT32 type __attribute__((unused)), UINT32 addr __attribute__((unused)));
extern  void rwdk_0000(BYTE *target, BYTE *src, int len);

extern int SPI_Resume_FlashWrite(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen);
extern int SPI_Resume_FlashRead(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen);
extern int SPI_Resume_FlashEraseSector(UINT32 type, UINT32 addr);

//resume related variables

extern UINT32 rsm_flash_start_addr;
extern UINT32 rsm_flash_sec_type;
extern UINT32 rsm_flash_sec_size;
extern UINT32 rsm_free_section_idx_array_size;
extern UINT32 rsm_free_section_size;
extern UINT32 rsm_flash_erasing_keyword;


