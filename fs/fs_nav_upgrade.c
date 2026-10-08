/*
*  Terry,2004/3/30 05:13PM
*/
#include "global.h"
#include "cmd.h"
#include "func.h" 
#include "memmap.h"
#include "memmap0.h"
#include "util.h" 
#include "kernel.h"
#include "cfont.h"
#include "vfdfunc.h"
#include "osd.h"
#include "image.h"
#include "iop.h"
#include "memcfg.h"

#include "ircode.h"

#include "user_init.h"

#include "fsNAV.h"
#include "fsGUI.h"
#include "setup.h"
#include "fs96602.h"

#include "fsGUI1.h"
#include "timer.h"

// Added by houyiwu 9/18/2004 for defining "SPHE1000"
#ifndef SPHE1000
#include "ver.h"
#endif

#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)//liweihua mod 20031219
#include "cardfs.h"
extern CARD_FILE       cardFile;
extern CARD_INFO       cardP;
#if defined(CF_CARD_WRITE) || defined(SPHE8202_FAT_Write_Function)//|| defined(WRITE_USB)
extern BYTE read_card_sign,flag_cf2cd,flag_cd2cf;
#endif
extern BYTE IsCardMediaRemove(void);
#endif

extern const BYTE ir_mapcode[256];  //Jefftest 20020606
//OSD related
extern void     osd_init(void);
extern void     osd_draw_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor);
extern void     osd_init_setup(void);
extern void     osd_DrawLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth);
extern void     DrawOSD_XO(BYTE bXO);


//FLASH related
#include "flash.h"
//extern UINT16   giFlashReadID; //Jeff 20020708

#ifdef SUPPORT_28X_FLASH	//yaowh add 2006-1-17 0:08
extern int		Parallel_FlashEraseUpgrade_28X(unsigned char *pBuf, unsigned int dwSize);
#endif

#ifndef DVDRELEASE
#define FSNAV_DBG
#endif

#define fsnav_printf(s...)  ((void)0)

#ifdef  FSNAV_DBG
#include "sio.h"
#include "emuio.h"
#undef  fsnav_printf
#define fsnav_printf        printf_w
#endif


#ifdef UPGRADE_TRAYOUT  //joshua add    04-07-13
    int trayout_flag = 0;
#endif    

#ifdef SUPPORT_SPI
#include "spi.h"
#endif

#ifdef SPHE1000
#define SMART_UPLOAD_BASE		0x80a00000
#endif

#ifdef DVD_AUDIO//2004-4-27 1:11
	extern UINT32 g_nAKeyFileLoc;
	extern UINT32 g_nAKeyFileSize;
#endif

void FSNav_clear_I2C_data(void);

void FSNav_UpgradeCountDown(UINT32  iCount)
{
	#ifdef UPGRADE_NOT_COUNT//libing 2005-6-30 23:06
	return;
	#endif
    BYTE    buf[10];

    psprintf(buf, "%02d", iCount);
    osd_DrawString(6, 3, buf, 2, 6);
}


int FSNav_DoUpgrade(BYTE* strVersion)
{
    
#ifdef UPGRADE_TRAYOUT    
    trayout_flag = 1;
#endif    
    BYTE buf[30];
    BYTE len, bOK = 1;
    BYTE *pDVDROM;
    int iRes = 0;
    UINT32  iCount;

#ifdef SUPPORT_28X_FLASH
	unsigned char	idM, idD;
	//UINT16			uFlashID;
#endif

#if defined(SUPPORT_CARD_STORAGE) || defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
   watchdog_onoff(0);    //fengjl add 2004-05-20 09:39  for usb upgrade
#endif

#ifdef DVD_AUDIO
	BYTE* pKeyFile;
	UINT32 nKeyAmount = 0;
	UINT32 nKeySize = 0;
	UINT32 nEnterNum = 0;
	UINT32 nPos = 0;
	BYTE b0, b1, b2, b3, b4;

	b0 = b1 = b2 = b3 = b4 = 0;
	pKeyFile = (BYTE *)(SDRAM_BASE + (A_JPEG_SERVO_YA + JPEG_SERVO_SIZE) * 1024);
#endif

#if defined(QSI_PORTABLE_DVD) && defined(QSI_PLATFORM)	 //qsi: added by johnson 20040720
	printf("FSNav_DoUpgrade> New Firmware Version = %s\n",strVersion);
#endif

#if defined(QSI_PORTABLE_DVD) && defined(QSI_PLATFORM)//qsi: modify by johnson 20040720
	#define COUNTDOWN_MAX   QSI_QUERY_FW_UPGRADE_WAITING_TIME
#else
	#define COUNTDOWN_MAX   20
#endif 
    
    ircmd_callback_check = NULL;
    cd_subtype = CDROM_BIN;

#ifdef SDRAM_16Mb_Mode//3-12-9 0:31 nono
    //find a good place for osd...  kevinmonkey 050926
    #if defined(COMPRESS_ROM_CODE_040) && defined(SUPPORT_DVD_FULL_SUBTITLE)
        #ifdef SUPPORT_MP4
    regs0->osd_base_addr = P_BIDIR_LUMA;
        #else   //COMPRESS_ROM_CODE_040&& SUPPORT_DVD_FULL_SUBTITLE but !SUPPORT_MP4
    regs0->osd_base_addr = (CDROM_CODE_YA+CDROM_CODE_SIZE);
        #endif
    #else   //!defined(COMPRESS_ROM_CODE_040) || !defined(SUPPORT_DVD_FULL_SUBTITLE)
    regs0->osd_base_addr = P_BIDIR_LUMA;
    #endif  //#if defined(COMPRESS_ROM_CODE_040) && defined(SUPPORT_DVD_FULL_SUBTITLE)*/
#endif//SDRAM_16Mb_Mode
   
    osd_init_setup();
	
    if (IsOSDChinese())
        psprintf(buf, "         %s           ", &_OsdMessegeFont1[osd_font_mode][STR_OS_SMART_UPGRADE][0]);
    else
        psprintf(buf, "        %s       ", &_OsdMessegeFont1[osd_font_mode][STR_OS_SMART_UPGRADE][0]);
	
    len = strlen(buf);
	
    osd_draw_rect(4*16, 3*26, 28*16, 9*26, 6);
    
    //top
    osd_DrawLine(4*16, 3*26, 4*16+28*16, 3*26, 2, 1);
    //left
    osd_DrawLine(4*16-2, 3*26, 4*16-2, 3*26+9*26, 2, 1);
    //bottom
    osd_DrawLine(4*16, 3*26+9*26, 4*16+28*16, 3*26+7*26, 11, 1);
    //right
    osd_DrawLine(4*16+28*16, 3*26, 4*16+9*26, 3*26+28*16, 11, 1);
	
    osd_DrawString(4, 3, buf, 2, 6); //2:font color, 6:background color
	
    psprintf(buf, "%s", &_OsdMessegeFont1[osd_font_mode][STR_OS_READ][0]); //Jeff 20020527
    len = strlen(buf);

    osd_DrawString(6, 5, buf, 2, 6); //2:font color, 6:background color
    
    
    #if defined(SPHE1000) && !defined(DVB1000_NON_OS)
    pDVDROM = (BYTE *)(SMART_UPLOAD_BASE);
    	
    #else
    //Move system image to DRAM
      #ifdef MEM_GRAPH_LARGE
    //note:when define MP3_LARGE_GUI,A_UDF_WORK_BUF = GP_REF1_CHROMA + GP_CHROMA_SIZE,JPEG PS is not enough;
    //when NTSC mode,"dvdrom.bin" is not put into UDF buf,but put buf after GP chroma.suqiaoli add 2004-10-16
        pDVDROM = (BYTE *)(SDRAM_BASE + (GP_REF0_CHROMA + GP_CHROMA_SIZE) * 1024);
    #else
    pDVDROM = (BYTE *)(SDRAM_BASE + (A_UDF_WORK_BUF+UDF_WORK_BUF_SIZE) * 1024);
    #endif
	
    #endif
	
#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
    if (media_type==MEDIA_CARD) {
        UINT32  nLBA;
		
        cardFile.stLBA = msf2l(pFsJpeg->gifsMSFDVDRom);
//        cardFile.stClus = CardLBA2Clus( cardFile.stLBA );
        cardFile.stClus = FSLBA2Clus( cardFile.stLBA );//linrc rename.20041204
        cardFile.iFileSize = pFsJpeg->gifsDVDRomSize;
        cardFile.curLBA = cardFile.stLBA;
        cardFile.curClus = cardFile.stClus;
        cardFile.iLeaveSize = cardFile.iFileSize;
		
        nLBA = (pFsJpeg->gifsDVDRomSize + cardP.bytePerSec - 1) / cardP.bytePerSec;
		
//        CardReadStream(&cardFile, nLBA, pDVDROM);
        FSReadStream(&cardFile, nLBA, pDVDROM);//linrc rename.20041205
    } else
#endif
    {
		ran_read(pDVDROM, pFsJpeg->gifsMSFDVDRom, pFsJpeg->gifsDVDRomSize);
    }

	// read DVD_AUDIO key file, Robert 030820
#ifdef DVD_AUDIO
	if (g_nAKeyFileLoc != 0)
	{
		ran_read(pKeyFile, g_nAKeyFileLoc, 2048); // robert 2004/02/18, read 2048 bytes only to identify file header
	}
#endif
	
    //Calculate CheckSum
    {
        BYTE    *p, bl, bh;
        UINT32  *pSum, iSum = 0, iNext = 0;
        UINT32  iIndex = 0x4f;
		
        //we store check in 0x20th byte
        pSum = (UINT32 *)(pDVDROM + 0x20);
        //printf("Origional checksum=%08x\n", *pSum);
		
        //from 0x50th byte to caculate checksum
        p = (BYTE *)(pDVDROM + 0x50);
		
        while (iIndex < pFsJpeg->gifsDVDRomSize)
        {
            bl = *p++;
            iIndex++;
            
            if (iIndex < pFsJpeg->gifsDVDRomSize)
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
            printf("Checksum Error\n");
            return -1;
        }
        else if((*pSum == 0)&&(iSum == 0))  //hongfeng add for when read rom.bin error 2006/9/28 19:46
        {
            printf("read rom.bin Error\n");
            return -1;
        }

    }
    
    #if defined(UPGRADE_TRAYOUT)&&(!defined(EASTECH_DVD)) //jwk mark 050811
            ircmd_trayout();
            delay_srv_10ms(500);
            trayout_flag = 0;
    #endif

#ifdef DVD_AUDIO
	if (g_nAKeyFileLoc != 0)
	{
		BYTE buf[10];

		// check key numbers
		nKeyAmount = getUINT32(pKeyFile + 5);
		nKeySize = getUINT32(pKeyFile + 9);

		if (nKeyAmount > 99999) // max key counts up to 99999
			nKeyAmount = 99999;

		//psprintf(buf, "%d %d", nKeyAmount, nKeySize);
		//osd_DrawString(23, 3, buf, 2, 6);

		psprintf(buf, "ENTER 0~%d:", nKeyAmount);
		osd_DrawString(8, 6, buf, 2, 6);

		// show a region to enter number
		psprintf(buf, "%d", b4);
		osd_DrawString(23, 6, buf, 2, 5);
		psprintf(buf, "%d", b3);
		osd_DrawString(24, 6, buf, 2, 4);
		psprintf(buf, "%d", b2);
		osd_DrawString(25, 6, buf, 2, 4);
		psprintf(buf, "%d", b1);
		osd_DrawString(26, 6, buf, 2, 4);
		psprintf(buf, "%d", b0);
		osd_DrawString(27, 6, buf, 2, 4);
	}
#endif

#ifdef QSI_PLATFORM
#ifdef QSI_SUPPORT_QSIVER_INFO_WHEN_UPGRADE
    psprintf(buf," OLD VER: %s%s",QSI_MASTER_VER,QSI_SLAVE_VER);
    osd_DrawString(4, 5, buf, 2, 6);
    
    if (IsOSDChinese())
        #ifdef USE_KOREAN_OSD       //clead korean 2003-10-23 
        psprintf(buf, " %s%s %s", &_OsdMessegeFont1[osd_font_mode][STR_OS_UPGRADE_TO][0], strVersion, Ch_question);
        #else
        psprintf(buf, " %s%s%s %s", &_OsdMessegeFont1[osd_font_mode][STR_OS_UPGRADE_TO][0], strVersion, Ch_ban, Ch_question);
        #endif
    else
        psprintf(buf, " %s%s %s", &_OsdMessegeFont1[osd_font_mode][STR_OS_UPGRADE_TO][0], strVersion, Ch_question);
    
    len = strlen(buf);
    
    //osd_DrawString(6, 5, buf, 2, 6); //2:font color, 6:background color
    osd_DrawString(4, 6, buf, 2, 6); //2:font color, 6:background color

#else
    if (IsOSDChinese())
        #ifdef USE_KOREAN_OSD		//clead korean 2003-10-23 
        psprintf(buf, "%s%s%s", &_OsdMessegeFont1[osd_font_mode][STR_OS_UPGRADE_TO][0], strVersion, Ch_question);
        #else
        psprintf(buf, "%s%s%s%s", &_OsdMessegeFont1[osd_font_mode][STR_OS_UPGRADE_TO][0], strVersion, Ch_ban, Ch_question);
        #endif
    else
        psprintf(buf, "%s%s%s", &_OsdMessegeFont1[osd_font_mode][STR_OS_UPGRADE_TO][0], strVersion, Ch_question);
	
    len = strlen(buf);
    
    //osd_DrawString(6, 5, buf, 2, 6); //2:font color, 6:background color
    osd_DrawString(4, 5, buf, 2, 6); //2:font color, 6:background color
#endif    //#ifdef QSI_SUPPORT_QSIVER_INFO_WHEN_UPGRADE
#else
    if (IsOSDChinese())
        #ifdef USE_KOREAN_OSD       //clead korean 2003-10-23 
        psprintf(buf, "%s%s%s", &_OsdMessegeFont1[osd_font_mode][STR_OS_UPGRADE_TO][0], strVersion, Ch_question);
        #else
        psprintf(buf, "%s%s%s%s", &_OsdMessegeFont1[osd_font_mode][STR_OS_UPGRADE_TO][0], strVersion, Ch_ban, Ch_question);
        #endif
    else
        psprintf(buf, "%s%s%s", &_OsdMessegeFont1[osd_font_mode][STR_OS_UPGRADE_TO][0], strVersion, Ch_question);
	
    len = strlen(buf);
    
    //osd_DrawString(6, 5, buf, 2, 6); //2:font color, 6:background color
    osd_DrawString(4, 5, buf, 2, 6); //2:font color, 6:background color
#endif  //#ifdef QSI_PLATFORM
    //Draw O-X selection
    DrawOSD_XO(1);

    set_rtc_val(0);
    iCount = COUNTDOWN_MAX;
    FSNav_UpgradeCountDown(iCount);

    do
    {
        UINT32  rx;
        UINT32  iTime;
#ifndef OLD_VFD_DRV
        UINT32  nVFDkey = 0;
		
		//nVFDkey = CheckVFDkey();
#endif
				watchdog_renew(WATCHDOG_RENEW_TIME);    //for usb upgrade no reset after 11s hongfeng 2005-07-11 
        iTime = get_rtc_val();
        
        #ifdef SUPPORT_SPI
        if(!(iTime%50))
          polling_spi();
        #endif
        iTime = COUNTDOWN_MAX - (iTime/100);

        if (iCount==0) {
        #ifndef UPGRADE_NOT_COUNT//libing 2005-6-30 23:06
            if (bOK == 1)   bOK=2;
            break;
        #endif
        } else {
            if (iTime != iCount) {
                iCount = iTime;
                FSNav_UpgradeCountDown(iCount);
            }
        }

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
                    set_rtc_val(0);
                    iCount = COUNTDOWN_MAX;
                    FSNav_UpgradeCountDown(iCount);
                }
            }
            else if (rx == IRC_RIGHT)
            {
                if (bOK == 0)
                {
                    bOK = 1;
                    DrawOSD_XO(1);
                    set_rtc_val(0);
                    iCount = COUNTDOWN_MAX;
                    FSNav_UpgradeCountDown(iCount);
                }
            }
#ifdef DVD_AUDIO
            else if ((rx == IRC_0) || (rx == IRC_1) || (rx == IRC_2) ||
					 (rx == IRC_3) || (rx == IRC_4) || (rx == IRC_5) ||
					 (rx == IRC_6) || (rx == IRC_7) || (rx == IRC_8) ||
					 (rx == IRC_9))
            {
				set_rtc_val(0);
				iCount = COUNTDOWN_MAX;
				FSNav_UpgradeCountDown(iCount);

				if (g_nAKeyFileLoc != 0)
				{
					BYTE bVal;
					bVal = rx - IRC_0;

					psprintf(buf, "%d", bVal);
					osd_DrawString(23 + nPos, 6, buf, 2, 4);

					// write to nPos position
					switch (nPos)
					{
					case 0: 
						b0 = bVal;
						psprintf(buf, "%d", b1);
						nPos = 1;
						break;

					case 1:
						b1 = bVal;
						psprintf(buf, "%d", b2);
						nPos = 2;
						break;

					case 2:
						b2 = bVal;
						psprintf(buf, "%d", b3);
						nPos = 3;
						break;

					case 3:
						b3 = bVal;
						psprintf(buf, "%d", b4);
						nPos = 4;
						break;
					
					case 4:
						b4 = bVal;
						psprintf(buf, "%d", b0);
						nPos = 0;
						break;
					}
					osd_DrawString(23 + nPos, 6, buf, 2, 5);
				}
            }
#endif
            else if ((rx == IRC_SELECT) || (rx == IRC_PLAY_SELECT))
            {
                if (bOK == 1)
                {
		#ifdef DVD_AUDIO
					if (g_nAKeyFileLoc != 0)
					{
						// get user selected number
						nEnterNum = 10000 * b0 + 1000 * b1 + 100 * b2 + 10 * b3 + b4;

						if (nEnterNum > nKeyAmount)
						{

							b4 = b3 = b2 = b1 = b0 = 0;
							nPos = 0;

							// show a region to enter number
							psprintf(buf, "%d", b4);
							osd_DrawString(23, 6, buf, 2, 5);
							psprintf(buf, "%d", b3);
							osd_DrawString(24, 6, buf, 2, 4);
							psprintf(buf, "%d", b2);
							osd_DrawString(25, 6, buf, 2, 4);
							psprintf(buf, "%d", b1);
							osd_DrawString(26, 6, buf, 2, 4);
							psprintf(buf, "%d", b0);
							osd_DrawString(27, 6, buf, 2, 4);
						}
						else
						{
							bOK = 2;
						}
					}
					else
						bOK = 2;
		#else
					bOK = 2;
		#endif
                }
				if (bOK == 0)
					break;
            }
        } //end of if (rx & IR_RDY)
		
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
		#ifdef DVD_AUDIO
					if (g_nAKeyFileLoc != 0)
					{
						// get user selected number
						nEnterNum = 10000 * b0 + 1000 * b1 + 100 * b2 + 10 * b3 + b4;

						if (nEnterNum > nKeyAmount)
						{

							b4 = b3 = b2 = b1 = b0 = 0;
							
							// show a region to enter number
							psprintf(buf, "%d", b4);
							osd_DrawString(23, 6, buf, 2, 5);
							psprintf(buf, "%d", b3);
							osd_DrawString(24, 6, buf, 2, 4);
							psprintf(buf, "%d", b2);
							osd_DrawString(25, 6, buf, 2, 4);
							psprintf(buf, "%d", b1);
							osd_DrawString(26, 6, buf, 2, 4);
							psprintf(buf, "%d", b0);
							osd_DrawString(27, 6, buf, 2, 4);
						}
						else
						{
							bOK = 2;
						}
					}
					else
						bOK = 2;
		#else
					bOK = 2;
		#endif
                }
				if (bOK == 0)
					break;
            }
        }
#endif//#ifndef OLD_VFD_DRV     // 2004/10/01 yltseng
    } while (bOK != 2);
	
    if (bOK == 2)
    {        
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
		
        //psprintf(buf, "%s...", &_OsdMessegeFont1[STR_OS_UPGRADING][osd_font_mode][0]);
        psprintf(buf, "%s...", &_OsdMessegeFont1[osd_font_mode][STR_OS_UPGRADING][0]);
        osd_DrawString(6, 5, buf, 2, 6); //2:font color, 6:background color
		
        //psprintf(buf, "%s", &_OsdMessegeFont1[STR_OS_NOT_POWEROFF][osd_font_mode][0]);
        psprintf(buf, "%s", &_OsdMessegeFont1[osd_font_mode][STR_OS_NOT_POWEROFF][0]);
        osd_DrawString(6, 6, buf, 2, 5); //2:font color, 6:background color
        
    #if defined(PORTABLE_DVD)||defined(ALCO_PORTABLE_DVD_8202D_DVB)       
        osd_DrawString(6, 7, "DISC CAN BE REMOVED", 2, 4);
    #endif
              

#ifdef DVD_AUDIO
		// copy key data to pDVDROM
		if ((g_nAKeyFileLoc != 0) && (nEnterNum > 0))
		{
			//psprintf(buf, "%d ", nEnterNum);
			//osd_DrawString(27, 3, buf, 2, 6);
			UINT32 nSelectedSector, nOffset;
			nSelectedSector = 13 + nKeySize * (nEnterNum - 1);
			nOffset = (nSelectedSector & 0x7ff);
			nSelectedSector >>= 11;
			g_nAKeyFileLoc = addmsf(g_nAKeyFileLoc, nSelectedSector);

			ran_read(pKeyFile, g_nAKeyFileLoc, nKeySize + 2048);

			*((BYTE*)(pDVDROM + 0x100)) = 0x44;
			*((BYTE*)(pDVDROM + 0x101)) = 0x45;
			*((BYTE*)(pDVDROM + 0x102)) = 0x56;
			*((BYTE*)(pDVDROM + 0x103)) = 0x4B;
			memcpy((BYTE*)(pDVDROM + 0x104), (BYTE*)(pKeyFile + nOffset), nKeySize);
		}
#endif                
        //joshua, 20050811, modified for clearing all I2C data when disc smart upgrade
        #ifndef SAME_DISC_RESUME    //if data keep in flash, erasing chip will clear all data, so omit this function here
        FSNav_clear_I2C_data();
        #endif
                
		#ifdef SUPPORT_28X_FLASH	//yaowh add 2006-1-17 9:54
			
		system_flash_id = FlashReadID();
		idM = system_flash_id & 0xff;
		idD = ( (system_flash_id & 0xff00) >> 8);
			
		if ( ((system_flash_id & 0xf0ff) == 0x1089) || ((idM == 0xB0)&&(idD == 0x58)) || ((idM == 0xB0)&&(idD == 0x5A))
				|| ((idM == 0xB0)&&(idD == 0xED)) || ((idM == 0xB0)&&(idD == 0xEC)) )
		{ 
			#ifdef UART0_DBG
			UART0_puts("28-series Flash Upgrade");
			#endif
			
			Parallel_FlashEraseUpgrade_28X(pDVDROM, pFsJpeg->gifsDVDRomSize);
		}
		else
		{
			#ifdef UART0_DBG
			UART0_puts("29/39-series Flash Upgrade");
			#endif
			
        FlashEraseUpgrade(pDVDROM, pFsJpeg->gifsDVDRomSize);
		}
		
		#else//#ifdef SUPPORT_28X_FLASH	//yaowh add 2006-1-17 9:54

		FlashEraseUpgrade(pDVDROM, pFsJpeg->gifsDVDRomSize);
		
		#endif//#ifdef SUPPORT_28X_FLASH	//yaowh add 2006-1-17 9:54
        
        ircmd_callback_check = fs_callback_check;

        //while (1);
    }
#if defined(SUPPORT_CARD_STORAGE) || defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
    watchdog_onoff(1);   //fengjl add 2004-05-20 09:39  for usb upgrade
#endif
    return iRes;
}

void FSNav_GetRomVersion(BYTE* strVersion)//jhuang 2004/9/3 11:29¤U¤È
{
int i;
	
#if defined(QSI_PORTABLE_DVD)//qsi: modify by johnson 20040721
	#ifdef QSI_SUPPORT_QSIVER_INFO_WHEN_UPGRADE
        //for (i=0; i<8; i++)//Extend version string length to 8 Bytes, Jeff 20020715
        for (i=0; i<QSI_MASTER_VER_LEN; i++)//NOW Extend version string length to 4 Bytes, nono 2004-5-11 22:22
        {
            strVersion[i] = *(pwb+QSI_MASTER_VER_LOCATION+i);
        }
        for (i=0; i<QSI_SLAVE_VER_LEN; i++)
        {
            //strVersion[8+i] = *(pwb+24+i);
            strVersion[QSI_MASTER_VER_LEN+i] = *(pwb+QSI_SLAVE_VER_LOCATION+i);//nono 2004-5-11 22:23
        }
        
        strVersion[(QSI_MASTER_VER_LEN+QSI_SLAVE_VER_LEN)] = '\0'; //Extend version string length to 8 Bytes, Jeff 20020715
        printf("read_iso9660> new ver:%s\n",strVersion);
	#else
        //for (i=0; i<8; i++)//Extend version string length to 8 Bytes, Jeff 20020715
        for (i=0; i<4; i++)//NOW Extend version string length to 4 Bytes, nono 2004-5-11 22:22
        {
            strVersion[i] = *(pwb+48+i);
        }
        for (i=0; i<7; i++)
        {
            //strVersion[8+i] = *(pwb+24+i);
            strVersion[4+i] = *(pwb+24+i);//nono 2004-5-11 22:23
        }
        //strVersion[15] = '\0'; //Extend version string length to 8 Bytes, Jeff 20020715
        strVersion[11] = '\0'; //Extend version string length to 8 Bytes, Jeff 20020715

	#endif
#else        
        //for (i=0; i<8; i++)//Extend version string length to 8 Bytes, Jeff 20020715
        for (i=0; i<4; i++)//NOW Extend version string length to 4 Bytes, nono 2004-5-11 22:22
        {
            strVersion[i] = *(pwb+48+i);
        }
        for (i=0; i<7; i++)
        {
            //strVersion[8+i] = *(pwb+24+i);
            strVersion[4+i] = *(pwb+24+i);//nono 2004-5-11 22:23
        }
        //strVersion[15] = '\0'; //Extend version string length to 8 Bytes, Jeff 20020715
        strVersion[11] = '\0'; //Extend version string length to 8 Bytes, Jeff 20020715
#endif
}
//joshua, 20050811, modified for clearing all I2C data when disc smart upgrade
void FSNav_clear_I2C_data(void)
{
    //set all I2C data to zero
    int i=0;
    BYTE kbuf __UNUSED, temp_value = 0;

    for(i=0;i<256;i++)
    {
        watchdog_renew(WATCHDOG_RENEW_TIME);
        #ifdef AUTO_LOAD_MODE_SETUP  //denghg add for AUTO_LOAD_MODE_SETUP2005-11-18 07:55     
        #include "setup_va.h"
        if(!(i==updateromFlagAdr)||(i==updateromFlagAdr+1)||(i==sizeof(UINT32)+SETUP_VA_MODE_ID))
        #endif 
        WriteToI2c(0xa0, i, (BYTE *)&temp_value,1);    
        //ReadFromI2c(0xa0,i,&kbuf,1);
        //printf_w("<1>kbuf=%x\n",kbuf);
    }    
}

//=====================================================ending==================================


