
#include "user_init.h"
#include "flash.h"
#include "global.h"

// Dummy functions
UINT16 ifunc1_flash_dummy(void) {return 0;}
int ifunc2_flash_dummy(UINT32 a1 __attribute__((unused))) {return 0;}
int ifunc3_flash_dummy(UINT32 iStartAddr __attribute__((unused)), BYTE *pBuf __attribute__((unused)), UINT32 iLen __attribute__((unused))) {return 0;}
int ifunc4_flash_dummy(UINT32 a1 __attribute__((unused)), UINT32 a2 __attribute__((unused))) {return 0;}
int ifunc5_flash_dummy(unsigned char *a1 __attribute__((unused)), unsigned int a2 __attribute__((unused))) {return 0;}

//Function pointers for general purposes
UINT16 (*FlashReadID)(void) = ifunc1_flash_dummy;
int (*FlashRead)(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen) = ifunc3_flash_dummy;
int (*FlashWrite)(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen) = ifunc3_flash_dummy;
int (*FlashEraseSector)(UINT32 sector_num) = ifunc2_flash_dummy;
int (*FlashEraseUpgrade)(unsigned char *pBuf, unsigned int dwSize) = ifunc5_flash_dummy;

//Function pointers for resume purposes
int (*Resume_FlashRead)(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen) = ifunc3_flash_dummy;
int (*Resume_FlashWrite)(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen) = ifunc3_flash_dummy;
int (*Resume_FlashEraseSector)(UINT32 type, UINT32 addr) = ifunc4_flash_dummy;


void init_spi_flash_functions(void)
{
    #ifdef SUPPORT_SPI_FLASH
    
        printf_w("SPI init functions\n");
        FlashReadID = SPI_FlashReadID;
        FlashRead = SPI_FlashRead;
        FlashWrite = SPI_FlashWrite;
        FlashEraseSector = SPI_FlashEraseSector;
        FlashEraseUpgrade = SPI_FlashEraseUpgrade;
        
        system_flash_id = FlashReadID();
        printf_w("<M>system_flash_id=%x\n", system_flash_id);
        SPI_APP_set_funcPointer(system_flash_id);
        
        SPI_APP_flash_init();

        regs0->sft_cfg14 &= ~0x7;   //joshua, 20051114, let SPI CS1, CS2, CS3 equals to zero(disable)

        #if defined(DISC_ID_IN_FLASH) && defined(SAME_DISC_RESUME)
        
            Resume_FlashRead = SPI_Resume_FlashRead;
            Resume_FlashWrite = SPI_Resume_FlashWrite;
            Resume_FlashEraseSector = SPI_Resume_FlashEraseSector;
            
            if(((system_flash_id&0xffff)==0x1c42)||((system_flash_id&0xffff)==0x7f12))
            {
                //for Eon, Amic spi flash    
                rsm_flash_start_addr = 0x7f000;
                rsm_flash_sec_type = TYPE_NORMAL;                 //for spi boot sector
                rsm_flash_sec_size = (4<<10);           //8KB
            }    
            else
            {
                rsm_flash_start_addr = 0x0;
                rsm_flash_sec_type = TYPE_BOOT;                 //for spi boot sector
                rsm_flash_sec_size = (8<<10);           //8KB                
            }            
                rsm_free_section_idx_array_size = 10;   //1024bytes
                rsm_free_section_size = 10;             //10:1024bytes, 11:2048bytes, 12:4096bytes, 13:8192
                rsm_flash_erasing_keyword = 0xFF;
        #endif                    
        
    #endif        
}

void init_parallel_flash_functions(void)
{
    #ifdef SUPPORT_PARALLEL_FLASH
    
        printf_w("Parallel init functions\n");
        FlashReadID = Parallel_FlashReadID;
        FlashRead = Parallel_FlashRead;
        FlashWrite = Parallel_FlashWrite;
        FlashEraseSector = Parallel_FlashEraseSector;
        FlashEraseUpgrade = Parallel_FlashEraseUpgrade;        
        
        //system_flash_id = FlashReadID();
        //printf_w("<M>system_flash_id=%x\n", system_flash_id);
        
        #if defined(DISC_ID_IN_FLASH) && defined(SAME_DISC_RESUME)
        
            Resume_FlashRead = Parallel_Resume_FlashRead;
            Resume_FlashWrite = Parallel_Resume_FlashWrite;
            Resume_FlashEraseSector = Parallel_Resume_FlashEraseSector;
        
            rsm_flash_start_addr = 0xf0000;
            rsm_flash_sec_type = 0;                 //meaningless for parallel flash
            rsm_flash_sec_size = (64<<10);          //64KB
            rsm_free_section_idx_array_size = 10;   //1024bytes
            rsm_free_section_size = 10;             //10:1024bytes, 11:2048bytes, 12:4096bytes, 13:8192
            //swpong 2006 0508 rsm_flash_erasing_keyword = 0x5A;
            rsm_flash_erasing_keyword = 0xFF;
        
        #endif
            
    #endif
    
}

int get_flash_type(void)
{
    
    #ifdef SUPPORT_SPI_FLASH
        UINT32 is_spi_flash =0;
        is_spi_flash = (regs0->sft_cfg19 &0x0300) >> 8;
    
        #ifdef IC_8202L
            is_spi_flash = 1;            
        #endif
    
        if(is_spi_flash!=0) //it means that SPI flash is on the board
        {                        
            return SPI_FLASH;
        }    
    #endif
    
        return PARALLEL_FLASH;    
}


void SPI_APP_set_funcPointer(UINT32 id)
{
    if((id&0xffff)==0x1c42)
    {
        //for Eon spi flash
        SPI_APP_flash_init = SPI_api_switch_2_EonSp2bitMode;
        SPI_APP_upgrade_init = SPI_api_switch_2_Eon1bitMode;
        spi_api_reading_command = 0x0393;
        spi_api_normal_writing_command = 0x0200;
        spi_api_writing_command = 0x0200;
        printf_w("<Eon spi flash>\n");
    }
    else if((id&0xffff)==0x7f12)
    {
        //for Amic spi flash
        SPI_APP_flash_init = SPI_api_switch_2_Sp2bitMode;
        SPI_APP_upgrade_init = SPI_api_switch_2_Sp1bitMode;
        spi_api_reading_command = 0x0393;
        spi_api_normal_writing_command = 0x0200;
        spi_api_writing_command = 0x0200;
        printf_w("<Amic spi flash>\n");
    }
    else
    {
        //for sunplus spi flash
        SPI_APP_flash_init =SPI_api_switch_2_Sp4bitMode;
        SPI_APP_upgrade_init = SPI_api_switch_2_Sp4bitUpgradeMode;
        spi_api_reading_command = 0x2593;   // fast read data	in BOOT sector
        spi_api_normal_writing_command = 0x1200;   // page program data in Normal sector
        spi_api_writing_command = 0x2600;   // page program data in BOOT sector
        printf_w("<sunplus spi flash>\n");
        
    }
        
}

