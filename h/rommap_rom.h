/*-----------------------------------------------------------------------------------------------------------------------------
File name: rommap.h
History:
2005.1.25  Creat By Terry
2005.3.06  Terry
-------------------------------------------------------------------------------------------------------------------------------
0x0000    __romstart
0x0008    __realstart
0x0018    VERSION_STRING .................................ex. "CUS-000" in cfg_customer.h
0x0020    Check Sum (in rom.bin)
0x0030    MPEG_UI_VERSION...............................ex. "206." in ver.h
0x0040    Check Sum (in romL.bin)
0x0050    MPEG_UI_VERSION...............................ex. "206." in ver.h
0x0060    intr_null
0x0070    __boot_entry
0x0080    __exception_bev0
0x0090    CFG_sdram_config :  CFG_SDRAM_OUT,CFG_SDRAM_IN,CFG_SDRAM_IN_DLY,CFG_SDRAM_PADCTRL.....ex.sdram.h
0x00A0    CFG_kernel0,  CFG_kernel1
0x00B0    CUSTOMER_ID_STRING.....................ex.  "SUNPLUS"
0x00C0    invalidate_dcache
0x0100    reserved area
0x0200    CFG_kernel2,CFG_kernel3,CFG_kernel4,CFG_kernel5
0x0220    __realstart 

-------------------------
Boot Load
-------------------------
0x88000000  ----------------------------+
            |                           |
            |ROMA(256KBytes)            |
            |    (0x40000)              |
0x88040000  +---------------------------+
            |                           |
            |ROMB(2048-256=1792KBytes)  |
            |                           |
0x88200000  +---------------------------+
 ----------------------------------------------------------------------------------------------------------------------------------*/   
 #define ROM_SIZE                               (1024)    //2048, terry,2005/3/6 08:55PM, romter ram size is lim.

 #define ROMA_SIZE                              (256)
 
 #define ROMB_SIZE                              (ROM_SIZE-ROMA_SIZE)   
 #define ROMA_ST                                (0)
 #define ROMB_ST                                (ROMA_ST + ROMA_SIZE)
 
 //romB check sum
 #define ROMB_CHK_SUM_ST                        (ROMB_ST+1)
 #define ROMB_CHK_SUM_END                       (ROM_SIZE)
 
 #define ROMB_START                             (ROMB_ST*1024)  //0x40000
 #define ROMA_START                             (ROMA_ST*1024)  //0
 
 #ifdef BOOT_LOAD_ROMB
 #ifdef ONLY_ROMB
 #define BOOT_OFFSET                            (ROMA_START)
 #else 
 #define BOOT_OFFSET                            (ROMB_START)
 #endif
 #elif defined(BOOT_LOAD_ROMA)
 #define BOOT_OFFSET                            (ROMA_START)
 #else
 #define BOOT_OFFSET                            (0)
 #endif
 
 #define ORG_VERSION_STRING                     (0x18+BOOT_OFFSET)
 #define ORG_MPEG_UI_VERSION                    (0x30+BOOT_OFFSET)
 #define ORG_BOOT_ROM_CHK_SUM                   (0x50+BOOT_OFFSET)
 #define ORG_BOOT_ROMB_CHK_SUM                  (0x34+ROMB_START)//(0x50+ROMB_START)
 #define ROM_SIZE_ADDR							(0x38+ROMB_START)//(0x54+ROMB_START)
 #define ORG__boot_entry                        (0x70+BOOT_OFFSET)
 #define ORG__exception_bev0                    (0x80+BOOT_OFFSET)
 #define ORG_CFG_sdram_config                   (0x90+BOOT_OFFSET)
 #define ORG_CFG_kernel0                        (0xa0+BOOT_OFFSET)
 #define ORG_CUSTOMER_ID_STRING                 (0xb0+BOOT_OFFSET)
 #define ORG_reserved_area                      (0x100+BOOT_OFFSET)
 #define ORG_CFG_kernel2                        (0x200+BOOT_OFFSET)
 #define ORG_real_start                         (0x220+BOOT_OFFSET)
 #define ORG_romB_real_start                         (0x220+ROMB_START)

