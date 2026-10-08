/*
*  Terry,2003/9/10 12:18AM
*  Servo QRE using
*/
#ifdef TEST_SERVO
void srv_mode_test_polling(void)
{
    if (iTestServoMode==3) {
        if (system_state==SYSTEM_BROWSE) {
            UINT32 iTime=get_rtc_val();

            if (iTime>=180000) { //30*60*100
            //if (iTime>=12000) { //30*60*100
                psprintf(RegionValStr[REGION2], "MTBF:%010d", iTestServoCount);
                PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);
                call_ir_func(IRC_EJECT);
                //ircmd_eject_toggle();
                polling();
                ShowTitle();
                delay_srv_10ms(600);
                polling();
                return;
            }
        }
    }
}

void srv_test_mode1_open(void)
{
    if (iTestServoMode==1) 
    {
        if (system_state==SYSTEM_NODISC) {
            //open/close servo testing mode
            call_ir_func(IRC_EJECT);
            delay_srv_10ms(200);//1s
            iTestServoCount++;
            psprintf(RegionValStr[REGION2], "DO OPEN/CLOSE TESTING:%05d", iTestServoCount);
            PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);
        }
    }
}

void srv_test_mode_play(void)
{
    if (iTestServoMode==1) {
        //open/close servo testing mode
        call_ir_func(IRC_EJECT);
        delay_srv_10ms(600);
        iTestServoCount++;
        psprintf(RegionValStr[REGION2], "DO OPEN/CLOSE TESTING:%05d", iTestServoCount);
        PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);
    } else if (iTestServoMode==3) {
        extern UINT32 dwDiscLBA;
        extern UINT32 dwLayerLBA;
        
        UINT32  i, iTestLBA;
        //do 10 times full stroke
        for (i=0; i<=20; i++) {
            iTestLBA = get_stc_val_32();
            iTestLBA %= dwDiscLBA;
            //ran_read(pwb, l2msf(iTestLBA), 2048);
            
            if(i%2 == 0)
                 ran_read(pwb, l2msf(0), 2048);
            else
            {
                 if(cd_type_loaded==CDDVD)
                 ran_read(pwb, l2msf(dwLayerLBA), 2048);
                 else
                 ran_read(pwb, gettrkmsf_leadout(), 2048);
                    
            }
            
            psprintf(RegionValStr[REGION2], "MTBF:%010d LBA:0X%08x", iTestServoCount, iTestLBA);
            PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);
            polling_osd(1);
        }
        iTestServoCount++;
        psprintf(RegionValStr[REGION2], "MTBF:%010d", iTestServoCount, iTestLBA);
        PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);
        polling_osd(1);
        //ircmd_shuffle();
        call_ir_func(IRC_RANDOM);
        browser();
     }
}

void srv_test_mode1_no_disc(void)
{
  if (iTestServoMode==1) 
  {
    //open/close servo testing mode
    call_ir_func(IRC_EJECT);
    delay_srv_10ms(600);//1s
    iTestServoCount++;
    psprintf(RegionValStr[REGION2], "DO OPEN/CLOSE TESTING:%05d", iTestServoCount);
    PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);
  }
}
void init_srv_test_mode(void)
{
    iTestServoMode  = 0;
    iTestServoCount = 0;
}
void test_mode_chk_close_tray(void)
{        
        if (iTestServoMode==1) {
            if (CDOpened()) {
                //close tray
                call_ir_func(IRC_EJECT);
                system_state=SYSTEM_OPEN;
                no_disk_cnt=DETECT_TIMES;
            }

            if (iTestServoCount>=20000) {
                iTestServoMode  = 0;
                iTestServoCount = 0;
            }
        } else if (iTestServoMode==3) {
            if (CDOpened()) {
                //close tray
                call_ir_func(IRC_EJECT);
                delay_srv_10ms(600);
                system_state=SYSTEM_OPEN;
                no_disk_cnt=DETECT_TIMES;
            }
        }
}
#else
#define test_mode_chk_close_tray();
#define init_srv_test_mode();
#define srv_test_mode1_no_disc();
#define srv_test_mode_play();
#define srv_test_mode1_open();
#endif //#ifdef TEST_SERVO


