#ifdef SUPPORT_SPI_QSI
#include "kernel.h"

#define SPI_CVBS_ON             0x41
#define SPI_S_ON                0x42
#define SPI_S_ON_CVBS_ON        0x43
#define SPI_YUV_ON_CVBS_ON      0x44
#define SPI_YUV_ON_480I         0x45
#define SPI_YBR_ON_480P         0x46
#define SPI_YUV_ON_576I         0x47
#define SPI_YBR_ON_576P         0x48
#define SPI_REGION0_CMD         0x50
#define SPI_PAL_CMD             0x57
#define SPI_NTSC_CMD            0x58


UINT8 uSpiRxData;

extern void setup_SPI_ssaver_onoff(UINT32 uOnOff);
extern void custm_SPI_region_setting(UINT32 uRegion);
void spi_cmd_play(void)           //0x05  play from beginning while disc is stop
{
    if( play_state == VCD_STATE_STOP ){
        resumeMSF = 0;
        //ircmd_play();
    }//else
        //invalid_key();
        
        ircmd_play();
}

#ifdef SUPPORT_CARD_STORAGE
void spi_cmd_switch_2_disc(void)
{
    if(source_type_now == source_card)
        ircmd_source_switch();
    else
        invalid_key();  
}

void spi_cmd_switch_2_card(void)
{
    if(source_type_now == source_disc)
        ircmd_source_switch();
    else
        invalid_key();  
}
#ifdef QSI_PLATFORM //qsi: added by johnson 20040811
extern void system_check_source_switch(void);
void spi_cmd_switch_media_to_dvd(void) //qsi: added by johnson 20040811
{
    printf("spi_cmd_switch_media_to_dvd>\n");
    if(source_type_now!=source_disc)
    {
        ircmd_source_switch(/*source_disc*/); 
        system_check_source_switch();
    }
    psprintf(RegionValStr[REGION2], "DVD");  
    PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1); 
}

void spi_cmd_switch_media_to_card(void) //qsi: added by johnson 20040811
{
    printf("spi_cmd_switch_media_to_card>\n");
    if(source_type_now!=source_card)
    {
        ircmd_source_switch(/*source_card*/); 
        system_check_source_switch();
    }
    psprintf(RegionValStr[REGION2], "CARD");  
    PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1); 

}
#endif
#endif //SUPPORT_CARD_STORAGE

void spi_cmd_ssaver_on(void)
{
    setup_SPI_ssaver_onoff(0);
}

void spi_cmd_ssaver_off(void)
{
    setup_SPI_ssaver_onoff(1);
}

void spi_cmd_stop2eject(void)
{
    if( play_state == VCD_STATE_STOP)
        ircmd_trayout();
    else
        ircmd_stop();
}

void spi_cmd_play_pause(void)
{
    if( play_state == VCD_STATE_STOP ){
        resumeMSF = 0;
        ircmd_play();
    }else if( play_state == VCD_STATE_PAUSE )
        ircmd_play();
    else
        ircmd_pause();
}

void spi_cmd_only_pause(void)
{
    if( play_state == VCD_STATE_PAUSE )
        invalid_key();
    else
        ircmd_pause();

}

void spi_cmd_pre_stop(void)
{
    if( (resumeMSF == 0) && (play_state != VCD_STATE_STOP) )
        ircmd_stop();
    else
        invalid_key();
}

void spi_cmd_system(void)
{
}

void spi_cmd_region(void)
{
    custm_SPI_region_setting(uSpiRxData - SPI_REGION0_CMD);
}

void spi_cmd_tvsys(void)
{
    UINT8 uID;

    if(uSpiRxData == SPI_PAL_CMD){
        tv_format = MODE_PAL;
        uID = STR_OS_PAL;
    }else{  //0x58 for NTSC
        tv_format = MODE_NTSC;
        uID = STR_OS_NTSC;
    }
    setup_tv_format(tv_format);
    setup_SetTV_format(uID); //update setup menu item
    PrintOsdMsg(STR_OS_TV_SYS|(uID<<OSDSTR_ID_TOTL_BIT),REGION1,1,4);
}

void spi_cmd_tvout(void)
{
    //tv_dacoff(0);

    switch(uSpiRxData)
    {
        case SPI_CVBS_ON:
                //sp8200tv_setup_custom_output(TV_OUT_CScCSc);
                //tv_dacoff(TV_DAC_D|TV_DAC_E|TV_DAC_F);
                
                psprintf(RegionValStr[REGION1],"CVBS ON");
                PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                sp8200tv_setup_custom_output(TV_OUT_CScCSc);

				// qsi: add by alexcheng 20041208
				#if	(QSI_PCB_REVISION >= QSI_PCB_REV_01)
		  		tv_dacoff(TV_DAC_B|TV_DAC_C|TV_DAC_D|TV_DAC_E|TV_DAC_F);
                #else
                tv_dacoff(TV_DAC_A|TV_DAC_B|TV_DAC_C|TV_DAC_E|TV_DAC_F);
                #endif
            break;
        case SPI_S_ON:
                //sp8200tv_setup_custom_output(TV_OUT_CScCSc);
                //tv_dacoff(TV_DAC_A|TV_DAC_D);
                
                psprintf(RegionValStr[REGION1],"SVIDEO ON");
                PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                sp8200tv_setup_custom_output(TV_OUT_CScCSc);

				// qsi: add by alexcheng 20041208
				#if	(QSI_PCB_REVISION < QSI_PCB_REV_01)
                tv_dacoff(TV_DAC_A|TV_DAC_D|TV_DAC_E|TV_DAC_F);
                #else
                tv_dacoff(TV_DAC_A|TV_DAC_B|TV_DAC_C);
                #endif
            break;
        case SPI_S_ON_CVBS_ON:
                //sp8200tv_setup_custom_output(TV_OUT_CScCSc);
                //tv_dacoff(TV_DAC_D);
                
                psprintf(RegionValStr[REGION1],"CVBS_SVIDEO ON");
                PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                sp8200tv_setup_custom_output(TV_OUT_CScCSc);
				
				// qsi: add by alexcheng 20041208
				#if	(QSI_PCB_REVISION >= QSI_PCB_REV_01)
				tv_dacoff(TV_DAC_B|TV_DAC_C|TV_DAC_D);
				#else
                tv_dacoff(TV_DAC_A|TV_DAC_E|TV_DAC_F);
				#endif
            break;
        case SPI_YUV_ON_CVBS_ON:
                //sp8200tv_setup_custom_output(TV_OUT_CScYuv);
                //tv_dacoff(TV_DAC_A);
				// qsi: add by alexcheng 20041208
				#if	(QSI_PCB_REVISION >= QSI_PCB_REV_01)
				psprintf(RegionValStr[REGION1],"YUV_CVBS_ON");
                PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                sp8200tv_setup_custom_output(TV_OUT_CScYUV);
                tv_dacoff(TV_DAC_B|TV_DAC_C);
                #else
                psprintf(RegionValStr[REGION1],"SETTING ERROR");
                PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                #endif
            break;
        case SPI_YUV_ON_480I:
                //sp8200tv_setup_custom_output(TV_OUT_CScYuv);
                //tv_dacoff(TV_DAC_A);
                
                psprintf(RegionValStr[REGION1],"YUV_480I");
                PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                sp8200tv_setup_custom_output(TV_OUT_YUVYUV);
				// qsi: add by alexcheng 20041208
				#if	(QSI_PCB_REVISION >= QSI_PCB_REV_01)
                tv_dacoff(TV_DAC_A|TV_DAC_B|TV_DAC_C);                 
                #else
                tv_dacoff(TV_DAC_D|TV_DAC_E|TV_DAC_F);
				#endif
                 setup_tv_format(MODE_NTSC);
            break;
        case SPI_YBR_ON_480P:
                //sp8200tv_setup_custom_output(TV_OUT_CScYBR);
                //tv_dacoff(TV_DAC_A);
                
                psprintf(RegionValStr[REGION1],"YBY_480P");
                PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                sp8200tv_setup_custom_output(TV_OUT_YBRYBR);
				// qsi: add by alexcheng 20041208
				#if	(QSI_PCB_REVISION >= QSI_PCB_REV_01)
                tv_dacoff(TV_DAC_A|TV_DAC_B|TV_DAC_C);                 
                #else
                tv_dacoff(TV_DAC_D|TV_DAC_E|TV_DAC_F);
				#endif
                setup_tv_format(MODE_NTSC);                
            break;
        case SPI_YUV_ON_576I:
                //sp8200tv_setup_custom_output(TV_OUT_CScYuv);
                //tv_dacoff(TV_DAC_A);
                
                psprintf(RegionValStr[REGION1],"YUV_576I");
                PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                sp8200tv_setup_custom_output(TV_OUT_YBRYBR);
				// qsi: add by alexcheng 20041208
				#if	(QSI_PCB_REVISION >= QSI_PCB_REV_01)
                tv_dacoff(TV_DAC_A|TV_DAC_B|TV_DAC_C);                 
                #else
                tv_dacoff(TV_DAC_D|TV_DAC_E|TV_DAC_F);
				#endif
                setup_tv_format(MODE_PAL);
            break;
        case SPI_YBR_ON_576P:
                //sp8200tv_setup_custom_output(TV_OUT_CScYBR);
                //tv_dacoff(TV_DAC_A);
                
                psprintf(RegionValStr[REGION1],"YBY_576P");
                PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                sp8200tv_setup_custom_output(TV_OUT_YBRYBR);
				// qsi: add by alexcheng 20041208
				#if	(QSI_PCB_REVISION >= QSI_PCB_REV_01)
                tv_dacoff(TV_DAC_A|TV_DAC_B|TV_DAC_C);                 
                #else
                tv_dacoff(TV_DAC_D|TV_DAC_E|TV_DAC_F);
				#endif
                setup_tv_format(MODE_PAL);
            break;
    }

        //tv_dacoff(TV_DAC_B|TV_DAC_C);

}

void spi_cmd_wakeup(void)
{
    if(system_state==SYSTEM_POWER)
     ircmd_power();
}

void spi_cmd_version_display(void)
{
extern UINT16 full_scrn;
extern void display_custm_menu_full(void);

	if(full_scrn==(SETUP|CUSTM))
	{
    	ExitSetupPage(0);
	}
	else
	{
    	//////display_custm_menu_full();
	}
}

void spi_cmd_production_reset(void)
{
BYTE    mbReset=0;

    WriteToI2c(I2C_ID_MEMORY,PRODUCTION_TESTING,&mbReset,sizeof(mbReset));
#ifdef QSI_SUPPORT_SLED_TEST    
    mbReset=SLED_REQ_FROM_RESET;
    WriteToI2c(I2C_ID_MEMORY,SLED_REQ_INFO_POS,&mbReset,sizeof(mbReset));
#endif    
    psprintf(linebuf,"PRODUCTION: RESET");           
    strcpy(RegionValStr[REGION2], linebuf);
    PrintOsdMsg(STR_OS_SPACE, REGION2, 3, 1);

    psprintf(linebuf,"Manufacture> Change to Reset phase.(PCB Testing)\n");
    UART0_puts(linebuf);

}

void spi_cmd_run_in(void)
{
BYTE    mbReset=1;

    WriteToI2c(I2C_ID_MEMORY,PRODUCTION_TESTING,&mbReset,sizeof(mbReset));
    psprintf(linebuf,"PRODUCTION: RUN IN");           
    strcpy(RegionValStr[REGION2], linebuf);
    PrintOsdMsg(STR_OS_SPACE, REGION2, 3, 1);
    psprintf(linebuf,"Manufacture> Change to Run-In phase.\n");
    UART0_puts(linebuf);
}
#ifdef QSI_SUPPORT_PIPO_ADJUST
void spi_cmd_pipo_adjustment(void)
{
BYTE    mbReset=PRODUCTION_RUNIN_ST_IS_PIPO_TEST;

    WriteToI2c(I2C_ID_MEMORY,PRODUCTION_TESTING,&mbReset,sizeof(mbReset));
    psprintf(linebuf,"PRODUCTION: INTO PIPO TESTING");           
    strcpy(RegionValStr[REGION2], linebuf);
    PrintOsdMsg(STR_OS_SPACE, REGION2, 3, 1);
    psprintf(linebuf,"Manufacture> Change to PIPO Testing\n");
    UART0_puts(linebuf);
}
#else
void spi_cmd_pipo_adjustment(void)
{
	psprintf(linebuf,"Manufacture> PIPO adjust inhibit.\n");
    UART0_puts(linebuf);

}
#endif
void spi_cmd_run_in_final(void)
{
BYTE    mbReset=0xff;

    WriteToI2c(I2C_ID_MEMORY,PRODUCTION_TESTING,&mbReset,sizeof(mbReset));
#ifdef QSI_SUPPORT_SLED_TEST    
    mbReset=SLED_REQ_NONE;
    WriteToI2c(I2C_ID_MEMORY,SLED_REQ_INFO_POS,&mbReset,sizeof(mbReset));
#endif    
    psprintf(linebuf,"PRODUCTION: FINAL");           
    strcpy(RegionValStr[REGION2], linebuf);
    PrintOsdMsg(STR_OS_SPACE, REGION2, 3, 1);
    psprintf(linebuf,"Manufacture> Change to Final phase.(Normal)\n");
    UART0_puts(linebuf);
#ifdef QSI_SUPPORT_SLED_TEST
extern int Is_Sled_Test;
    Is_Sled_Test=0;
#endif

}


#if defined(QSI_PORTABLE_DVD) || defined(QSI_PLATFORM) //qsi: added by johnson 20040715
void spi_cmd_invalid_key(void)
{
    invalid_key();
}


void spi_cmd_mecha_test(void)
{
BYTE    mbReset=PRODUCTION_RUNIN_ST_IS_MECHA_TEST;
    printf("spi_cmd_mecha_test>\n");
    WriteToI2c(I2C_ID_MEMORY,PRODUCTION_TESTING,&mbReset,sizeof(mbReset));
}

void spi_cmd_slot_test(void) 
{
BYTE    mbReset=PRODUCTION_RUNIN_ST_IS_SLOT_TEST;
    printf("spi_cmd_slot_test>\n");
    WriteToI2c(I2C_ID_MEMORY,PRODUCTION_TESTING,&mbReset,sizeof(mbReset));
}

#ifdef QSI_SUPPORT_SLED_TEST
void spi_cmd_sled_test(void)
{
BYTE    mbReset=PRODUCTION_RUNIN_ST_IS_SLED_TEST;
extern int Is_Sled_Test;
    WriteToI2c(I2C_ID_MEMORY,PRODUCTION_TESTING,&mbReset,sizeof(mbReset));
    mbReset=SLED_REQ_FROM_SPI;
    WriteToI2c(I2C_ID_MEMORY,SLED_REQ_INFO_POS,&mbReset,sizeof(mbReset));
	psprintf(linebuf,"PRODUCTION: SLED TEST");           
    strcpy(RegionValStr[REGION2], linebuf);
    PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);
    psprintf(linebuf,"Manufacture> Change to sled test.\n");
    UART0_puts(linebuf);
    Is_Sled_Test=1;
}
#else
void spi_cmd_sled_test(void)
{
	psprintf(linebuf,"Manufacture> SLED test isn't supported.\n");
    UART0_puts(linebuf);
}
#endif


void spi_cmd_mtbf_test(void)
{
	psprintf(linebuf,"Manufacture> MTBF isn't supported.\n");
    UART0_puts(linebuf);
}

#endif


//qsi: added by johnson 20041222
#ifdef DIGITAL_VIDEO_OUT
void spi_cmd_ccir656_on(void)
{
	int i;
	
	SET_GPIO_OUTPUT(GPIO_IS_FOR_CCIR656_CLK);
	for(i=0; i<8; i++)
	{
		SET_GPIO_OUTPUT(GPIO_IS_FOR_CCIR656_D0+i);
	}

	regs0->sft_cfg6 |= (0x1 << 14);
	printf("spi_cmd_ccir656_on\n");
}


void spi_cmd_ccir656_off(void)
{
	int i;
	
	regs0->sft_cfg6 &= ~(0x1 << 14);
	
	printf("spi_cmd_ccir656_off\n");
	SET_GPIO_INPUT(GPIO_IS_FOR_CCIR656_CLK);
	for(i=0; i<8; i++)
	{
		SET_GPIO_INPUT(GPIO_IS_FOR_CCIR656_D0+i);
	}
}
#else
void spi_cmd_ccir656_on(void)
{
}


void spi_cmd_ccir656_off(void)
{
}

#endif

#endif  //#ifdef SUPPORT_SPI_QSI
