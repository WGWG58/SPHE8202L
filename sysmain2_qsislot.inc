//
// FILE
// sysmain2_qsi.inc
//
// DESCRIPTION
//

#ifdef QSI_SUPPORT_SLOT_TEST
extern  BYTE SERVO_GetRunInState(void);

BYTE is_do_slot_test(void)
{
    if(SERVO_GetRunInState()==PRODUCTION_RUNIN_ST_IS_SLOT_TEST)
    {
        return(1);
    }
    return(0);
}

UINT16  slot_test_cnt=0;

static inline void qsi_slot_test()
{
    if(is_do_slot_test())
    {
            if(play_state==VCD_STATE_READTOC)
            {
                slot_test_cnt++;
                psprintf(linebuf,"SLOT-IN/OUT TEST: %d", slot_test_cnt);
                strcpy(RegionValStr[REGION2], linebuf);
                PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);
                printf("ap_main>Eject disc! test cnt = %d\n",slot_test_cnt);
                ircmd_trayout();
            }
    }
    else if(slot_test_cnt!=0)
    {
            slot_test_cnt=0;
            ClearOsdMsg(REGION2);
    }
}
#endif

