#include "UartComm.h"
#include "global.h"
#include "io_uart1.h"
#include "emuio.h"
#include "memmap.h"
#include "memmap0.h"
#include "memcfg.h"
#include "kernel.h"

#include "osd.h"
#include "iop.h"
#include "ircode.h"
#include "cchar.h"
#include "epp.h"
#include "fsGUI1.h"
#include "fsGUI.h"
#include "func.h"
#include "setup.h"
#include "timer.h"

extern const BYTE ir_mapcode[256];  //Jefftest 20020606

// external functions
extern UINT16 FlashReadID();
extern void osd_init_setup(void);
extern void osd_draw_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor);
extern void osd_DrawLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth);
extern void DrawOSD_XO(BYTE bXO);
extern int FlashEraseUpgrade(unsigned char *pBuf, unsigned int dwSize);

// external variables
extern UINT16 save_srn_start_t;


#ifdef SUPPORT_UART_UPGRADE

int	nInputLevel = 0;
UINT32 g_dwFileSize = 0;
//UINT16 g_uID;

inline int pollingUARTRx(void)
{
    while (!IsEPPRxEmpty())
    {
        char c = EPP_GETC();
		
        if (c == 'u')
            nInputLevel = 1;
        else if (c == 'a')
            nInputLevel = (nInputLevel == 1) ? 2 : 0;
        else if (c == 'r')
            nInputLevel = (nInputLevel == 2) ? 3 : 0;
        else if (c == 't' && nInputLevel == 3)
        {
            nInputLevel = 0;
            EPP_PUTC_EXACT('3'); // the character '3' is just for communication with pc side AP.
            return 1;
        }
        else nInputLevel = 0;
    }
    return 0;
}

inline void DoMoveUARTRxData(void)
{
    BYTE szFileSize[4] = {0};
    UINT32 nIndex = 0;
    BYTE* pDVDROM;
    BYTE c;
	
    // check file size.
    do
    {
        if (!IsEPPRxEmpty())
        {
            c = EPP_GETC();
            szFileSize[nIndex] = c;
            nIndex++;
        }
    }
    while (nIndex <= 3);
	
    g_dwFileSize = getUINT32_li(szFileSize);
	
    //printf("g_dwFileSize = %d\n", g_dwFileSize);
    EPP_PUTC_EXACT('1'); // communication signal
	
    // should disable screen saver and show upgrade menu here...
    disable_video();
    delay_1ms(20);
    config_memory(MEMORY_GRAPH_SMALL);
    setup_tv_format(tv_format);
    setVPP_TVformat(tv_format);
    FSGUI_FillFrameBuf(0, 0, 352, 288, BK_GROUNDY, BK_GROUNDCRCB);
    delay_1ms(20);
    enable_video();
    FSGUI_UpdateInfoArea("DOWNLOADING ROM FILE...");
    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
	
    //receive file data and put into SDRAM
    nIndex = 0;
    pDVDROM = (BYTE *)(SDRAM_BASE + (A_UDF_WORK_BUF+UDF_WORK_BUF_SIZE) * 1024);
	
    do
    {
        if (!IsEPPRxEmpty())
        {
            c = EPP_GETC();
			
            *(pDVDROM + nIndex) = c;
            save_srn_start_t = get_rtc_val(); // prevent entering screen saver
            nIndex++;
            if ((nIndex % 12) == 0) // send a response every 12 bytes
                EPP_PUTC_EXACT('=');
        }
    }
    while (nIndex < g_dwFileSize);
    EPP_PUTC_EXACT('=');
	
    //epp_write_wait("\nFinish downloading rom file.\n");
	
    if (g_dwFileSize)
    {
        BYTE    strVersion[10];
        int     i;
			
        for (i = 0; i < 7; i++)
        {
            strVersion[i] = *(pDVDROM + 0x30 + i);
        }
        strVersion[7] = '\0';
        //g_uID = FlashReadID();
			
        if (system_flash_id != 0xdead) //Jeff 20021023
        {
            // call upgrading function here...
            FSGUI_UpdateInfoArea("CHECKING ROM FILE...");
            DoUpgrade(strVersion);
        }
        else
        {
            // Flash rom ID doesn't match.
            FSGUI_UpdateInfoArea("FLASH ID IS WRONG!!");
            while(1);
        }
    }
}

void DoUpgrade(BYTE* strVersion)
{
    BYTE buf[30];
    BYTE len, bOK = 0;
    BYTE *pDVDROM = (BYTE *)(SDRAM_BASE + (A_UDF_WORK_BUF+UDF_WORK_BUF_SIZE) * 1024);
	
    ircmd_callback_check = NULL;
    cd_subtype = CDROM_BIN;
    osd_init_setup();
	
    if (IsOSDChinese())
        psprintf(buf, "         %s           ", &_OsdMessegeFont1[osd_font_mode][STR_OS_SMART_UPGRADE][0]);
    else
        psprintf(buf, "        %s       ", &_OsdMessegeFont1[osd_font_mode][STR_OS_SMART_UPGRADE][0]);
	
    len = strlen(buf);
	
    osd_draw_rect(4*16, 3*26, 28*16, 7*26, 6);
    
    //top
    osd_DrawLine(4*16, 3*26, 4*16+28*16, 3*26, 2, 1);
    //left
    osd_DrawLine(4*16-2, 3*26, 4*16-2, 3*26+7*26, 2, 1);
    //bottom
    osd_DrawLine(4*16, 3*26+7*26, 4*16+28*16, 3*26+7*26, 11, 1);
    //right
    osd_DrawLine(4*16+28*16, 3*26, 4*16+7*26, 3*26+28*16, 11, 1);
	
    osd_DrawString(4, 3, buf, 2, 6); //2:font color, 6:background color
	
    //psprintf(buf, "%s", "LOADING...");
    psprintf(buf, "%s", &_OsdMessegeFont1[osd_font_mode][STR_OS_READ][0]); //Jeff 20020527
    len = strlen(buf);
    osd_DrawString(6, 5, buf, 2, 6); //2:font color, 6:background color
    
    //Calculate CheckSum
    {
        BYTE    *p, bl, bh;
        UINT32  *pSum, iSum = 0, iNext = 0;
        UINT32  iIndex = 31;
		
        //we store check in 20th byte
        pSum = (UINT32 *)(pDVDROM + 0x20);
        //printf("Origional checksum=%08x\n", *pSum);
		
        //from 80th byte to caculate checksum
        p = (BYTE *)(pDVDROM + 0x50);
		
        while (iIndex < g_dwFileSize)
        {
            bl = *p++;
            iIndex++;
            
            if (iIndex < g_dwFileSize)
            {
                bh = *p++;
                iIndex++;
            }
            else
            {
                bl = 0;
                bh = 0;
            }
			
            iSum = iSum + iNext;
            iNext = (unsigned int)bh * 256U + (unsigned int)bl;
        }
        iNext &= 0xFF;
        iSum += iNext;
        //printf("Read checksum=%08x\n", iSum);
        
        if (*pSum != iSum)
        {
            //printf("Checksum Error\n");
            FSGUI_UpdateInfoArea("CHECKSUM ERROR...");
            while(1);
        }
    }
	
    /*
    //check FLASH id, Jeff 20020708
    {
	BYTE    *p;
	UINT16  iFlashID;
	
	  //we add flash-id in init0.s, offset=0x30
	  p = (BYTE *)(SDRAM_BASE + (P_BIDIR_LUMA) * 1024 + 0x30);
	  iFlashID = ((*(p + 1)) << 8) & 0xff00;
	  iFlashID = iFlashID | *(p);
	  
        //for old version, iFlashID should be 0
        if (iFlashID)
        {
		if (iFlashID != g_uID)
		{
		psprintf(buf, "%s:%x %x\n", "FLASH MISMATCH", iFlashID, g_uID);
		len = strlen(buf);
		osd_DrawString(6, 5, buf, 2, 6); //2:font color, 6:background color
		while(1);
		}
        }
		}
    */
	
    if (IsOSDChinese())
        psprintf(buf, "%s %s %s %s", &_OsdMessegeFont1[osd_font_mode][STR_OS_UPGRADE_TO][0], strVersion, Ch_ban, Ch_question);
    else
        psprintf(buf, "%s%s %s", &_OsdMessegeFont1[osd_font_mode][STR_OS_UPGRADE_TO][0], strVersion, Ch_question);
	
    len = strlen(buf);
    
    osd_DrawString(6, 5, buf, 2, 6); //2:font color, 6:background color
	
    //Draw O-X selection
    DrawOSD_XO(0);
    
    // pop up an OSD menu for users to decide to upgrade flash or not
    do
    {
        UINT32  rx;
#ifndef OLD_VFD_DRV
        UINT32  nVFDkey = 0;
		
		nVFDkey = CheckVFDkey();
#endif
        extern UINT16 GetIRCode();  // 2004/10/01 yltseng, move to ir_parser.c GetIRCode()
        rx = GetIRCode();
        
        if( rx != IR_CODE_MAX_NUM )
        {            
            if (rx == IRC_LEFT) 
            {
                if (bOK == 1)
                {
                    bOK = 0;
                    DrawOSD_XO(0);
                }
            }
            else if (rx == IRC_RIGHT)
            {
                if (bOK == 0)
                {
                    bOK = 1;
                    DrawOSD_XO(1);
                }
            }
            else if( (rx == IRC_SELECT)||(rx == IRC_PLAY_SELECT) )
            {
                if (bOK == 1)
                {
                    bOK = 2;
                }
                // user don't want to do the upgrading action.
                break;
            }
        }
        
#ifndef OLD_VFD_DRV     // 2004/10/14 yltseng
        if (nVFDkey != IR_CODE_MAX_NUM)
        {
            if (nVFDkey == IRC_LEFT)
            {
                if (bOK == 1)
                {
                    bOK = 0;
                    DrawOSD_XO(0);
                }
            }
            else if (nVFDkey == IRC_RIGHT)
            {
                if (bOK == 0)
                {
                    bOK = 1;
                    DrawOSD_XO(1);
                }
            }
            else if ((nVFDkey == IRC_PLAY) || (nVFDkey == IRC_PAUSEPLAY))
            {
                if (bOK == 1)
                {
                    bOK = 2;
                }
                break;
            }
        }
#endif        
    } while (bOK != 2);
	
    if (bOK == 2)
    {
        FSGUI_UpdateInfoArea("UPGRADING...");
		
        //write system image to flash
        osd_init_setup();
        
        if (IsOSDChinese())
            psprintf(buf, "         %s           ", &_OsdMessegeFont1[osd_font_mode][STR_OS_SMART_UPGRADE][0]);
        else
            psprintf(buf, "        %s       ", &_OsdMessegeFont1[osd_font_mode][STR_OS_SMART_UPGRADE][0]);
		
        len = strlen(buf);
		
        osd_draw_rect(4*16, 3*26, 28*16, 7*26, 6);
        //top
        osd_DrawLine(4*16, 3*26, 4*16+28*16, 3*26, 2, 1);
        //left
        osd_DrawLine(4*16-2, 3*26, 4*16-2, 3*26+7*26, 2, 1);
        //bottom
        osd_DrawLine(4*16, 3*26+7*26, 4*16+28*16, 3*26+7*26, 11, 1);
        //right
        osd_DrawLine(4*16+28*16, 3*26, 4*16+7*26, 3*26+28*16, 11, 1);
		
        osd_DrawString(4, 3, buf, 2, 6); //2:font color, 6:background color
		
        psprintf(buf, "%s...", &_OsdMessegeFont1[osd_font_mode][STR_OS_UPGRADING][0]);
        osd_DrawString(6, 5, buf, 2, 6); //2:font color, 6:background color
		
        psprintf(buf, "%s", &_OsdMessegeFont1[osd_font_mode][STR_OS_NOT_POWEROFF][0]);
        osd_DrawString(6, 6, buf, 2, 5); //2:font color, 6:background color
		
        FlashEraseUpgrade(pDVDROM, g_dwFileSize);
        while (1);
    }
    FSGUI_UpdateInfoArea("PLEASE REBOOT THE MACHINE.");
    while (1);
}

#endif
