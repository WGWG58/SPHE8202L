// 2004/10/07 yltseng
#include "user_init.h"

#include "global.h"
#include "avd.h" 
#include "osd.h"

#include "memcfg.h"
#include "ircode.h"
#include "timer.h"
#include "userlogo.h"
#include "memmap0.h"
#include "vpp.h"
#include "macro.h"
#include "tvif.h"
#include "fsnav.h"
#include "kinf.h"

//FLASH related
#include "flash.h"

extern void     reset_sup(void);

#define WRITE_FLASH

// **************************************************************************************** //
#ifdef JPG_LOGO

extern	char	_stextf[];
extern  INT8    dis_pic_id_saved_0;
UINT8           Use_Ref0_Flag;

//Terry,2003/9/12 11:40PM
//these code only for reference,we will be not maintain it
static void show_jpg_logo(void)
{
    if(!Is_Jpg_Logo())
    {
    BYTE *p;
    UINT32	unOffset;

    #ifdef MONE_LOGO
    printf("logo in\n");
    #endif

    LoadModual(MODUAL_MPEG);
    show_logo=1;

    //terry,2003/1/15 08:32¤U¤È
    //delay_1ms(50);//add time to avoid TV noise when power on
    Abort();

    config_memory(MEMORY_DVD_NTSC); //note: default ntsc logo , if customer's logo is pal then must chg to pal
                                  //      else will black video twice times
//    p=DVDTitle;
	unOffset = ((UINT32 *)_stextf)[MODUAL_ROM3];
	p = (BYTE *)(_stextf + unOffset + (MODUAL_Ns * 4));

    #ifdef DOUBLE_LOGO
    if(OsdIsEnglish())
        p=DVDTitle1;
    #endif

    #ifdef CD_PLAYER    //liweihua 2003-9-3
    if((cd_type_loaded==CDDA)&&(play_state!=VCD_STATE_OPEN))
    	p=CDPlayerTitle;
    #endif
    PlayRomSlide(p);
    MediaMainLoop();
    PlayRomSlide(p);
    MediaMainLoop();

    tv_setup_misc(0);
    reset_sup();
    Sync();

    show_logo=0;
    }
    else
    ShowJpgTitle();
}

// **************************************************************************************** //
extern void ShowJpgTitle()
{
    extern int Do_Jpg_Main(UINT32 msf, UINT32 len, UINT16 xStart, UINT16 yStart, UINT16 xWidth, UINT16 yHeight, UINT8 uiFromSDram, UINT8 uiInterruptable );
    
	UINT32 Jpglen;
	UINT16 *p,temp;
	p = (int *)&temp;
//	BYTE * pJpglogo=(BYTE *)(SDRAM_BASE_CACHED+5*1024*1024);
    BYTE * pJpglogo = (UINT8 *)(SDRAM_BASE_CACHED + SSAVER_YA*1024);

	ReadFromI2c(0xa0, 0xf1, p, 2);
	Jpglen=((UINT8 *)(p))[0]<<8|((UINT8 *)(p))[1];
	FlashRead(0x70000+28*1024,pJpglogo, Jpglen);
    config_memory(MEMORY_GRAPH_PAL);
    Do_Jpg_Main((UINT32) pJpglogo, Jpglen, 0, 0, 720, 576, TRUE, FALSE );
    LoadModual(MODUAL_MPEG);
}

// **************************************************************************************** //
extern UINT8 Is_Jpg_Logo()
{
	UINT8 *p,temp;
	
	p=(BYTE *)&temp;
	if(ReadFromI2c(0xa0,0xf0,p,1)>0)
	{
		if(*p==0x55)  //User jpg logo tag!
		{
			return 1;
		}
		return 0;
	}
	return 0;
}

// **************************************************************************************** //
extern void Fetch_Jpg_Logo()
{
	BYTE temp,*p,* pJpglogo;
	UINT32 Jpglen;
	UINT32 Jpgloc;
	int *pImgSrc,*pImgDst,i;
	p= (BYTE *)&temp;
//	BYTE * pJpglogo=SDRAM_BASE_CACHED+5*1024*1024;
	if(Is_JPEG_STATE()&&(pFsJpeg->gifsState == FS_STATE_JPEG)&&(dis_pic_id_saved_0 == 1))
	{
		Use_Ref0_Flag=1;
    	pJpglogo = (UINT8 *)(SDRAM_BASE_CACHED + GP_REF0_LUMA*1024);
    }
    else
    {
    	Use_Ref0_Flag=0;
    	pJpglogo = (UINT8 *)(SDRAM_BASE_CACHED + GP_REF1_LUMA*1024);
    }

	Jpgloc=iso9660_file[pFsJpeg->file_array[pFsJpeg->file_will]].loc;
	Jpglen=iso9660_file[pFsJpeg->file_array[pFsJpeg->file_will]].size;
	if(Jpglen>30*1024)
		{
//			printf("File size too large!\n");
            psprintf(RegionValStr[REGION2], "PICTURE SIZE TOO LARGE:%dK BYTES",Jpglen/1024);
            PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
			return;
		}
    psprintf(RegionValStr[REGION2], "SAVING ... PICTURE SIZE:%dK BYTES",Jpglen/1024);
    PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
//	printf("File size is %d\n",Jpglen);
    ran_read(pJpglogo, Jpgloc, Jpglen);

	FlashRead(0x70000,pJpglogo+64*1024, (64-37)*1024);

//	printf("Erase Sector 7 now...\n");
    FlashEraseSector(7);
//    printf("Erase Sector OK!\n");
//    printf("Write Jpg to Flash...\n");
	FlashWrite(0x70000, pJpglogo+64*1024, (64-37)*1024);
    if(FlashWrite(0x70000+28*1024, pJpglogo, Jpglen)==0)
    {
//    	printf("Write Finish!\n");
    	*p=0x55;
		WriteToI2c(0xa0,0xf0,p,1);
		temp=Jpglen>>8;
		p=(BYTE *)&temp;
		WriteToI2c(0xa0,0xf1,p,1);
		temp=Jpglen&0xff;
		p=(BYTE *)&temp;
		WriteToI2c(0xa0,0xf2,p,1);

        pImgSrc = (int *)(SDRAM_BASE_CACHED + GP_REF1_LUMA*1024);
        pImgDst = (int *)(SDRAM_BASE_CACHED + GP_REF0_LUMA*1024);
		if(Use_Ref0_Flag == 1)
		{
        	for (i = 0; i < 105984; i++)
                *pImgDst++ = *pImgSrc++;
		}
		else
		{
        	for (i = 0; i < 105984; i++)
                *pImgSrc++ = *pImgDst++;
		}

	    psprintf(RegionValStr[REGION2], "OK");
	    PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
	}
    else
    {
  //  	printf("Write Error!\n");
	    psprintf(RegionValStr[REGION2], "FAILED");
	    PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
	}
}
#endif//#ifdef JPG_LOGO

// **************************************************************************************** //
#ifdef USER_MPEG_LOGO
static void
Save_Mpeg_Logo_Erase()
{
    //FlashEraseSector(12);   //2004-7-19 04:42ˆÓîP  if flash address begin from 896 delete it .// alan, 2003/9/24 11:33AM
    //FlashEraseSector(13);   
    FlashEraseSector(14);
    printf("Erase Sector OK!\n");
}

// **************************************************************************************** //
static void
Save_Mpeg_Logo_Write(UINT8 *output, int len)
{
    printf("Write mpeg logo to Flash...\n");
    //if(FlashWrite(768*1024, output, len)==0)   
    if(FlashWrite(896*1024, output, len)==0)  //2004-7-19 04:41ˆÓîP flash address from 896 
    {
    	printf("Write Finish!\n");
    	//*p=0x88;
        //WriteToI2c(0xa0,0xe0,p,1);//CLEAD	2003-8-1 
        psprintf(RegionValStr[REGION2], "OK");
        PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
    }
    else
    {
    	printf("Write Error!\n");
        psprintf(RegionValStr[REGION2], "FAILED");
        PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
    }	
}

// **************************************************************************************** //
extern void
Save_Mpeg_Logo()
{
    UINT8   *p,*temp,*output,old_dip_enable;
    int N;

    printf("Save_Mpeg_Logo()\n");
	
#if !defined(DVD_ESP_2S)//4-2-21 0:10
    old_dip_enable = dip_enable;
    dip_enable = 0;
#endif//#if !defined(DVD_ESP_2S)&& !defined(DIP_CFG_ENABLE)

    // mzhen, 2003/8/26 10:41PM
//	UINT8 *temp=(UINT8 *)(SDRAM_BASE_CACHED+6*1024*1024);
//	UINT8 *output=(UINT8 *)(SDRAM_BASE_CACHED+(6*1024+4)*1024);

    // setup
    if(pFsJpeg->gifsState == FS_STATE_JPEG)	// mzhen, 2003/8/26 10:41PM
    {
    	temp = (UINT8 *)(SDRAM_BASE_CACHED+P_BIDIR_CHROMA*1024);
    	output = (UINT8 *)(SDRAM_BASE_CACHED+(P_BIDIR_CHROMA+4)*1024);
    }
    else
    {

#if defined(DVD_ESP_2S)
        temp = (UINT8 *)(SDRAM_BASE_CACHED+N_NAVYA*1024);//4-2-21 0:07
        output = (UINT8 *)(SDRAM_BASE_CACHED+(N_NAVYA+4)*1024);//4-2-21 0:07

        // 2004/07/16 yltseng
        wb_tag_init();//4-2-21 0:07
#else//#if defined(DVD_ESP_2S)
    	temp = (UINT8 *)(SDRAM_BASE_CACHED+A_DEINTLACE_YA*1024);
    	output = (UINT8 *)(SDRAM_BASE_CACHED+(A_DEINTLACE_YA+4)*1024);
#endif//#if defined(DVD_ESP_2S)

    }
	
#ifdef  WRITE_FLASH
    // erase
    Save_Mpeg_Logo_Erase();
#endif

    // encode
#if 1//defined(DVD_ESP_2S)  2004-7-19 04:41ˆÓîP 
    mpeg_encode_target(50*1024*8);
#else//#if defined(DVD_ESP_2S)||defined(DIP_CFG_ENABLE)
    mpeg_encode_target(160*1024*8);
#endif//#if defined(DVD_ESP_2S)||defined(DIP_CFG_ENABLE)
    
    N=mpeg_encode(0,getVPP_PictureWidth(),getVPP_PictureHeight(),2,temp,output);
    printf("the output mpeg bit is %d (%d-byte)\n", N, N/8);

#ifdef  WRITE_FLASH
    // write-flash
    Save_Mpeg_Logo_Write(output, N/8);
#endif

#if !defined(DVD_ESP_2S)//4-2-21 0:10
    dip_enable = old_dip_enable;//4-2-21 0:07
#endif//#if !defined(DVD_ESP_2S)//4-2-21 0:10
    watchdog_onoff(1);  // alan, 2003/9/23 03:05PM
}

// **************************************************************************************** //
extern void Change_User_Logo()
{
    extern BYTE mpeg_logo_onoff;
	UINT8 temp,*p;
	p=(BYTE *)&temp;
   	if(mpeg_logo_onoff)
   	*p=0x88;  //Manufacture Logo tag!
   	else
   	*p=0x55;  //Manufacture Logo tag!	
   	//WriteToI2c(0xa0,0xe0,p,1);		
   	WriteToI2c(0xa0,0xd2,p,1);			//gerry for vcd disc,2003-12-24 15:11
    //psprintf(RegionValStr[REGION2], "DEFAULT LOGO");  // alan, 2003/9/16 05:04PM
    //PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
	
}

// **************************************************************************************** //
extern UINT8 Is_User_Mpeg_Logo()
{
	UINT8 *p,temp;
	
	p=(BYTE *)&temp;
	//if(ReadFromI2c(0xa0,0xe0,p,1)>0)

	if(
    	  (ReadFromI2c(0xa0,0xd2,p,1)>0)
#ifdef YUXING_MIDI_DVD 	 // nono 2004-10-28 14:43
    	&&(setup_GetMPEGLogoItem()==3)
#endif
      )
	{
		if(*p==0x88)  //User Mpeg logo tag!
		{
			return 1;
		}
		return 0;
	}
	return 0;
}
#endif

// **************************************************************************************** //
