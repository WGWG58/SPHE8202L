//for QSI PIPO and MECHA test

//#define QSI_DBG

extern void SrvResetErrCnt(UINT16 mwMaxCounter);
extern UINT32 SrvReadErrCnt(void);

void QSI_PIPO_routine(void);
void QSI_PIPO_pre_check(int current_SS);


#ifdef QSI_PLATFORM

extern BYTE MSF_trigger,PIPO_key,PIPO_key_old;
extern UINT32 QSI_PIPO_MSF_old;

enum {
        CURRENT_ERR_CNT_MAX = 0,
        CURRENT_ERR_CNT_MIN,
        LAST_ERR_CNT_MAX,
        LAST_ERR_CNT_MIN,
        ERR_REC_MAX
    };

UINT32 ErrcntRec[4];

void QSI_PIPO_ShowLastInfo(BYTE item,UINT32 adrs,UINT16 len,UINT32 max_err,UINT32 min_err)
{
    
    psprintf(linebuf, "\x1b[02;00H");
    UART0_puts(linebuf);
    delay_1ms(10);
    psprintf(linebuf, "Before testing result:\n");
    UART0_puts(linebuf);
    psprintf(linebuf, "\tSelect Item: %02d \t MSF-Adrs: 0x%08x \t Length: %d \n",item,adrs,len);
    UART0_puts(linebuf);
    psprintf(linebuf, "\tMax PO ErrCnt: %4d \t Min PO ErrCnt: %4d\n",max_err,min_err);
    UART0_puts(linebuf);
    psprintf(linebuf,"\t==============================================================\n");
    UART0_puts(linebuf);
}

void QSI_PIPO_ShowCurrentInfo(BYTE item,UINT32 adrs,UINT16 len,UINT32 max_err,UINT32 min_err)
{

    psprintf(linebuf, "\x1b[06;00H");
    UART0_puts(linebuf);
    delay_1ms(10);
    psprintf(linebuf, "Current testing result:\n");
    UART0_puts(linebuf);
    psprintf(linebuf, "\tSelect Item: %02d \t MSF-Adrs: 0x%08x \t Length: %d\n",item,adrs,len);
    UART0_puts(linebuf);
    psprintf(linebuf, "\tMax PO ErrCnt: %4d \t Min PO ErrCnt: %4d\n",max_err,min_err);
    UART0_puts(linebuf);
    psprintf(linebuf,"    ====[Press number 0(inside) to 9(outside) to select testing position]====\n");
    UART0_puts(linebuf);
}

void QSI_PIPO_UpdateErrcntInfo(UINT32 max_err,UINT32 min_err)
{

    psprintf(linebuf, "\x1b[08;00H");
    UART0_puts(linebuf);
    delay_1ms(10);
    psprintf(linebuf, "\tMax PO ErrCnt: %4d \t Min PO ErrCnt: %4d\n",max_err,min_err);
    UART0_puts(linebuf);
    psprintf(linebuf, "\x1b[24;00H");
    UART0_puts(linebuf);
    delay_1ms(10);
}

void QSI_PIPO_Menu_init(void)
{
    int i;

    for(i=0; i<ERR_REC_MAX; i++)
    {
        ErrcntRec[i]=0;
    }
    //Clear screen
    psprintf(linebuf, "\x1b[2J");
    UART0_puts(linebuf);
    delay_1ms(10);
    psprintf(linebuf, "\t\t\t-----[ PI-PO Adjustment ]-----");
    UART0_puts(linebuf);
    
    QSI_PIPO_ShowLastInfo(0,0,0,0,0);
    psprintf(linebuf, "\x1b[10;24r");
    UART0_puts(linebuf);
    delay_1ms(10);
}


#endif



void QSI_PIPO_pre_check(int current_SS)
{
#include "iop.h"
    
#ifdef QSI_DBG
    psprintf(linebuf, "QSI_PIPO_pre_check   [in]    current_SS:%d\n", current_SS);
    UART0_puts(linebuf);
#endif  
    
    ReadFromI2c(I2C_ID_MEMORY , PRODUCTION_TESTING , &QSI_PIPO_TEST , sizeof(QSI_PIPO_TEST));
    //QSI_PIPO_TEST=0x1;  //this value should read from EEPROM  //aging byte
    
        
    if(QSI_PIPO_TEST != 0x1) {
        psprintf(linebuf, "QSI PIPO> skip PIPO test\n");
        UART0_puts(linebuf);
#ifdef QSI_PLATFORM
        psprintf(linebuf, "\x1b[01;24r");
        UART0_puts(linebuf);
#endif
        return; //no need to do the PIPO test
    } else { 
        if(current_SS==SYSTEM_OPEN) {
            if (system_state == SYSTEM_NODISC) {
                psprintf(linebuf, "QSI PIPO> system read disc failed,please chagne one.\n");
                UART0_puts(linebuf);
                return;
            }
        } else if(current_SS==SYSTEM_READ_TITLE){   
            #ifdef QSI_PLATFORM
            psprintf(linebuf, "\x1b[2J");
                UART0_puts(linebuf);
            delay_1ms(10);
            psprintf(linebuf, "\x1b[01;24r");
            UART0_puts(linebuf);
            #endif
            if (system_state == SYSTEM_NODISC) {
                psprintf(linebuf, "QSI PIPO> system read TOC failed\n");
                UART0_puts(linebuf);
                return;
            }
            else {
                psprintf(linebuf, "QSI PIPO> disc type [%d]\n", cd_type_loaded);
                UART0_puts(linebuf);    
                //system_state=SYSTEM_QSI_PIPO_TEST;            
                psprintf(linebuf, "QSI PIPO> please enter msf point(Num 0-9)\n");
                UART0_puts(linebuf);
                QSI_PIPO_FLAG = 0x0;
            }
        }   
    }
    return;
}


void QSI_PIPO_routine(void)
{

    BYTE  res;
    UINT16 mwMaxCounter;
    UINT32 ErrCnt;
#ifdef QSI_PLATFORM
    BYTE i;
    static BYTE menu_init_flag;
    static UINT16 mwMaxCounter_old;

    if(menu_init_flag==0)
    {
        menu_init_flag=1;
        QSI_PIPO_Menu_init();
    }

    if(MSF_trigger==1)
    {
        MSF_trigger=0;
        ErrcntRec[LAST_ERR_CNT_MAX]=ErrcntRec[CURRENT_ERR_CNT_MAX];
        ErrcntRec[LAST_ERR_CNT_MIN]=ErrcntRec[CURRENT_ERR_CNT_MIN];
        ErrcntRec[CURRENT_ERR_CNT_MAX] = 0;
        ErrcntRec[CURRENT_ERR_CNT_MIN] = 0;
        QSI_PIPO_ShowLastInfo(PIPO_key_old,QSI_PIPO_MSF_old,mwMaxCounter_old,ErrcntRec[LAST_ERR_CNT_MAX],ErrcntRec[LAST_ERR_CNT_MIN]);
    }   
#endif  
    if(QSI_PIPO_FLAG>>1){
        if(cd_type_loaded == CDDVD) {
            mwMaxCounter = 1; // 1 ECC block, 16 sector     
            #ifdef QSI_PLATFORM
            mwMaxCounter_old = mwMaxCounter;
            QSI_PIPO_ShowCurrentInfo(PIPO_key,QSI_PIPO_MSF,mwMaxCounter,0,0);
            psprintf(linebuf, "\x1b[J");
            #else       
            psprintf(linebuf, "QSI PIPO:goto MSF:%x    length: %d ECC blocks\n" , QSI_PIPO_MSF, mwMaxCounter);
            #endif

        }else{
            mwMaxCounter = 16; // 16 sector
            #ifdef QSI_PLATFORM
            mwMaxCounter_old = mwMaxCounter;
            QSI_PIPO_ShowCurrentInfo(PIPO_key,QSI_PIPO_MSF,mwMaxCounter,0,0);
            psprintf(linebuf, "\x1b[2J");
            #else       
            psprintf(linebuf, "QSI PIPO:goto MSF:%x    length: %d sectors\n" , QSI_PIPO_MSF, mwMaxCounter);
            #endif  
        }
        UART0_puts(linebuf);
        
        QSI_PIPO_FLAG=0x1;
    }
    
        if(cd_type_loaded == CDDVD) {
            SrvResetErrCnt(mwMaxCounter);
            res=ran_read((UINT8 *)(SDRAM_BASE +PCM_ST*1024), QSI_PIPO_MSF, 2048*mwMaxCounter*16);           
        } else {
            SrvResetErrCnt(mwMaxCounter);
            res=ran_read((UINT8 *)(SDRAM_BASE +PCM_ST*1024), QSI_PIPO_MSF, 2048*mwMaxCounter);                          
            delay_1ms(5);
        }
        
        #ifdef QSI_DBG      
            psprintf(linebuf, "res= %x\n", res);
            UART0_puts(linebuf);
        #endif
        
        flush_atapi();
        ErrCnt = SrvReadErrCnt();
#ifdef QSI_PLATFORM
        if(ErrCnt > ErrcntRec[CURRENT_ERR_CNT_MAX])
        {
            ErrcntRec[CURRENT_ERR_CNT_MAX]=ErrCnt;
            QSI_PIPO_UpdateErrcntInfo(ErrcntRec[CURRENT_ERR_CNT_MAX],ErrcntRec[CURRENT_ERR_CNT_MIN]);
        }
        else if(ErrCnt < ErrcntRec[CURRENT_ERR_CNT_MIN] || ErrcntRec[CURRENT_ERR_CNT_MIN]==0)
        {
            ErrcntRec[CURRENT_ERR_CNT_MIN]=ErrCnt;
            QSI_PIPO_UpdateErrcntInfo(ErrcntRec[CURRENT_ERR_CNT_MAX],ErrcntRec[CURRENT_ERR_CNT_MIN]);           
        }
#endif
        psprintf(linebuf, "QSI PIPO> ErrCnt: %4d (0x%04x)\n" , ErrCnt, ErrCnt);
        UART0_puts(linebuf);
        delay_1ms(80); //time interval between tests

    return;
}

