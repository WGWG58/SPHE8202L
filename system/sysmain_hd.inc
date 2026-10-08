//
// FILE
// sysmain_hd.inc
//
// DESCRIPTION
// sysmain() HD related functions
//

#ifdef SUPPORT_HDD_ACCESS
int load_hdd_init()
{
    int i;
    UINT32  lbaRoot;

    watchdog_onoff(0);
    atapi_share_rom_bus();
    MIPS_flush_LBC_cache();
    delay_1ms(3000);

    for(i=0;i<10;i++) {
//        if(CardIsExist()) {
        if(FSIsExist()) {
            printf("Sunplus DVD load HDD driver OK!!\n");
            break;
        }
        delay_1ms(100);
    }
//    lbaRoot = CardGetRoot();
    lbaRoot = FSGetRoot();
}
#endif

