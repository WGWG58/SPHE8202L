//for QSI PIPO and MECHA test
//#define IRCMD_QSI_DBG

extern UINT32 dwDiscLBA;

void QSI_setMSF(int QSIkey);

#if defined(QSI_PORTABLE_DVD) || defined(QSI_PLATFORM)
BYTE MSF_trigger,PIPO_key,PIPO_key_old;
UINT32 QSI_PIPO_MSF_old;
#endif

void QSI_setMSF(int QSIkey)
{
#ifdef QSI_PLATFORM
    QSI_PIPO_MSF_old =  QSI_PIPO_MSF;
#endif
    QSI_PIPO_MSF=l2msf((dwDiscLBA/11)*(QSIkey+1));

    QSI_PIPO_FLAG = (0x1<<1)|(0x1);     //bit 1: MSF change flag, bit 0: PIPO test flag.

#ifdef IRCMD_QSI_DBG
    psprintf(linebuf, "QSI PIPO: QSI_PIPO_FLAG [%x]\n", QSI_PIPO_FLAG);
    UART0_puts(linebuf);
#endif
#ifdef QSI_PLATFORM
    MSF_trigger=1;
    PIPO_key_old = PIPO_key;
    PIPO_key=QSIkey;
#endif  


}


