/**************************************************************************
 *                                                                        *
 *         Copyright (c) 2002 by Sunplus Technology Co., Ltd.             *
 *                                                                        *
 *  This software is copyrighted by and is the property of Sunplus        *
 *  Technology Co., Ltd. All rights are reserved by Sunplus Technology    *
 *  Co., Ltd. This software may only be used in accordance with the       *
 *  corresponding license agreement. Any unauthorized use, duplication,   *
 *  distribution, or disclosure of this software is expressly forbidden.  *
 *                                                                        *
 *  This Copyright notice MUST not be removed or modified without prior   *
 *  written consent of Sunplus Technology Co., Ltd.                       *
 *                                                                        *
 *  Sunplus Technology Co., Ltd. reserves the right to modify this        *
 *  software without notice.                                              *
 *                                                                        *
 *  Sunplus Technology Co., Ltd.                                          *
 *  19, Innovation First Road, Science-Based Industrial Park,             *
 *  Hsin-Chu, Taiwan, R.O.C.                                              *
 **************************************************************************/
/*--------------------------------------------------------------------------
|  File Name   :  8202_usb_card_if.c
|
|  Description :  8202 Usb and Card Interface
|
|  Version    :  0.1  
| 
| 
|  Rev  Date            Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1  2004/9/18         wthsin         Creating
|--------------------------------------------------------------------------------*/ 
#include "user_init.h"
#include "global.h"
#include "emuio.h"
#include "gpio.h"
#include "func.h"
#include "cpu.h"//wanghaoying 20030812
#include "macro.h"
#include "memmap.h"
#include "memmap0.h"
#include "fsNav.h"//liweihua 2004-3-30 14:34
#include "cderr.h"
#include "cardfs.h"
#include "osd.h"
#include "scsi.h"
#include "usb.h"
#if defined(HOST_UHCI) 
 #include "uhci.h"
#elif defined(USB_HOST_DRV)  //wthsin
 #include "usb_host_drv.h"
#endif  
#if defined(SPHE8202_CARD_STORAGE)  
 #include "card_main.h"
 #include "sd.h"
 #include "cf.h"
 #include "ms.h"
#endif

#ifdef SUPPORT_MIDI         ///xlluo add 04-1-21
#include "fsmidi.h"
#include "fsMidiUI.h"
#endif

//Simon 2006.5.5
//New FS support, and New CD-ripping
#include "fs_new.h"
#ifdef SUPPORT_CD_RIPPING//qinhua add 200607
#include "fs_new_app.h"
#endif

#ifdef PLUG_IN_USB_CLOSE_LOADER//chenzhao20060214//hongfeng add for OP 2006-1-7
    #ifdef MULTIDISC_LOADER
    #include "multidisc_loader.h"
    #else
    #include "CD.h"
    #endif
#endif

#ifdef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-4-5 15:05
#include "ircmd_switch_media.h"
#include "atapi_if.h"
#endif//DIRECT_ACCESS_MEDIA

#ifdef SPHE8202_ALL_TYPE_CARD_WRITE
extern BYTE card_browse_sign;//dingzhy 4-11-18 9:40
#endif

#ifdef FILE_MODE_WRITE                  //sunzhh add for file mode 2005-1-14
extern BYTE file_mode_flag;                   
#endif    

#if defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE) 
    extern UINT8 MediaIsEmpty;
    extern void show_card_reading_osd(BYTE type);
    extern void ircmd_stop(void);
    extern void SwitchMedia(BYTE direction);
#endif

#ifdef USBCARD_PLUG_OUT_CLEAR_SETUP_PROG
extern CARD_FILE    cardFile;
#endif

#if defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE) 
 //0x01: USB ,0x02: CF ,0x04: SD_MMC ,0x08: MS ,0x10: SMC  
 const UINT8 storage_parity_type[]=  { 0x00, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
                                       0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
                                       0x10, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,
                                       0x08, 0x01, 0x02, 0x01, 0x04, 0x01, 0x02, 0x01,};
#endif

#ifndef DVDRELEASE
 #define USB_CARD_IF_DBG       1
#endif

#define D   printf("INFO: __%d__(%s:%s)\n",__LINE__,__FILE__,__FUNCTION__);

#ifndef USB_CARD_IF_DBG
 #undef printf
 #undef print_block
 #define printf(f, a...) do {} while (0)
 #define print_block(x,y) do {} while (0)
#endif

#ifdef MP3_ONLY_STOP_TO_GUI 
extern void ShowTitle();
#endif 
#if defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE) 
#ifdef SPHE8202_CARD_STORAGE  
UINT8   CardEna=0;  

#ifdef IR_SWITCH_CD_USB_CF_OTHER  //dingzhy for bus switch 04-10-22
EXTERN  BYTE detect_result_last;
EXTERN  BYTE now_valid_type;
#endif

#ifdef CARD_SETUP_TYPE_5
 UINT8 PMP_CF_Card_Insert=0;
 UINT8 PMP_CF_Card_Play=0;
 #ifdef SUPPORT_MULTI_PARTITION
  extern void Refresh_Partition_Menu(void);
  #ifdef FAT_FILE_MODE
  extern UINT16 fat_play_mode;
  extern void Refresh_FAT_Mode_GUI(void); 
  #endif//#ifdef FAT_FILE_MODE
 #endif//#ifdef SUPPORT_MULTI_PARTITION
#endif //#ifdef CARD_SETUP_TYPE_5

#ifdef EASTECH_VFD_DISP //make sure VFD's right display
extern void erase_vfd_mem(void); //lyc 05-04-15
extern void  vfd_set_str(UINT8 id, char *s);
BYTE clear_old_show_time = 0 ; //lyc 2005-4-15
#endif


#ifdef PMP_DVD

//kenny 2005/5/12 reduce warning
void PMP_PC_Usb_PlugInOut();
    #ifdef PMP_UI
    extern void pmpkey_return(void);
    #endif
#endif

#ifdef IDE_CF_SW
extern void IdeSetSequence(UINT8 sequence);
extern void hwCfCardStandby(UINT8 on);//kenny 2005/5/12
extern void ioPowerOn(void);
#endif


#ifdef SUPPORT_MP3_ENCODER
extern void check_target_device(void);		
#endif

#if defined(MP3_ONLY_STOP_TO_GUI)||defined(EASTECH_VFD_DISP)
extern void ShowTitle(void);
#endif
/**************************************************************************
 *                                                                        *
 *  Function Name: Card_power_reset                                       *
 *                                                                        *
 *  Purposes:                                                             *
 *    USE GPIO to reset card power                                        *
 *  Descriptions:                                                         *
 *    USE GPIO to reset card power                                        *
 *  Arguments:                                                            *
 *          NONE                                                          *
 *  Returns:     NONE                                                     *
 *                                                                        *
 *  See also:    NONE                                                     *
 *                                                                        *
 **************************************************************************/
void Card_power_reset()
{
    GPIO_O_SET(CARD_POWER_RESET,1);  //Power Off
    delay_srv_10ms(30);  
    GPIO_O_SET(CARD_POWER_RESET,0);  //Power On
   #if defined(CARD_SETUP_TYPE_1)||defined(CARD_SETUP_TYPE_2)  
    regs0->fm_gpio_len  = 12                    // Set FMGPIO_B[41:0] turn on
                        |  (0xf << 4);          // Set FMGPIO_B[41:0] enable   
   #elif defined(CARD_SETUP_TYPE_3)||defined(CARD_SETUP_TYPE_5)          
       #ifdef HDMI_SMC_CLE//for HDDVD Non CF config.chenzhao on 2005-3-9
       regs0->fm_gpio_len  = 10                    
                           |  (0xf << 4);          // Set FMGPIO_B[26:0] enable  
       #else
    regs0->fm_gpio_len  = 11                    // Set FMGPIO_B[26:0] turn on
                        |  (0xf << 4);          // Set FMGPIO_B[26:0] enable  
       #endif//HDMI_SMC_CLE
   #elif defined(CARD_SETUP_TYPE_4)      
     regs0->fm_gpio_len  = 3                    // Set FMGPIO_B[5:0] turn on
                        |  (0x1 << 4);          // Set FMGPIO_B[5:0] enable                     
   #endif                                        
    delay_srv_10ms(30); 
}    
/**************************************************************************
 *                                                                        *
 *  Function Name: Card_power_off                                         *
 *                                                                        *
 *  Purposes:                                                             *
 *    turn off card power, let card invalid                               *
 *  Descriptions:                                                         *
 *    turn off card power, let card invalid                               *
 *  Arguments:                                                            *
 *          NONE                                                          *
 *  Returns:     NONE                                                     *
 *                                                                        *
 *  See also:    NONE                                                     *
 *                                                                        *
 **************************************************************************/
void Card_power_off()
{
    GPIO_O_SET(CARD_POWER_RESET,1);  //Power Off
    regs0->fm_gpio_len  = 0; 
}    
/**************************************************************************
 *                                                                        *
 *  Function Name: Card_gpio_init                                         *
 *                                                                        *
 *  Purposes:                                                             *
 *    initialize card GPIO, Set card GPIO valid                           *
 *  Descriptions:                                                         *
 *    initialize card GPIO, Set card GPIO valid                           *
 *  Arguments:                                                            *
 *          NONE                                                          *
 *  Returns:     NONE                                                     *
 *                                                                        *
 *  See also:    NONE                                                     *
 *                                                                        *
 **************************************************************************/
void Card_gpio_init()
{
  #ifdef CARD_SETUP_TYPE_1  
    regs0->sft_cfg3 &= ~(0x1 << 5);  //set GPIO 50 ca8202 pin193    
    regs0->sft_cfg1 &= ~(0x1 << 2);  //set GPIO 17 ca8202 pin77 
    GPIO_M_SET(CARD_SENSE1_PIN, 1); 
    GPIO_M_SET(CARD_POWER_RESET,1);
  #elif defined(CARD_SETUP_TYPE_2)  
    regs0->sft_cfg1 &= ~(0x1 << 3);  //set GPIO 16 ca8202 pin76 
    GPIO_M_SET(CARD_SENSE1_PIN, 1); 
    GPIO_M_SET(CARD_POWER_RESET,1);
  #elif defined(CARD_SETUP_TYPE_3)  
    regs0->sft_cfg3 &= ~(0x1 << 5);  //set AUD4 disable, wthsin 2004/6/14 04:23pm
    regs0->sft_cfg0 &= ~(0x1 << 7);  //set CS1  disable
    regs0->sft_cfg1 &= ~(0x1 << 5);  //set A12  disable

     #ifdef PORTABLE_DVD
        regs0->sft_cfg0 &= ~(0x1 << 5);  //set GPIO 38 ca8202 pin161
     #elif defined(IDE_CF_SW)
     regs0->sft_cfg0 &= ~(0x1 << 5);     //set GPIO 38 ca8202 pin161
     #elif defined(COSMIC_CARD_READER) //FanGang added 2005-1-10 17:32
     regs0->sft_cfg0 &= ~(0x1 << 4);     //set GPIO 39 ca8202 pin162
     #elif defined(USE_PIN162_AS_CARD_SENSE3)//wangap 2005/2/24
     regs0->sft_cfg0 &= ~(0x1 << 4);   //set GPIO39 ca8202 pin162
     #else//#ifdef PORTABLE_DVD
     
    #ifdef CARD_SENSE3_USE_GPIO39 /*2005-6-6 huziqin*/
     regs0->sft_cfg0 &= ~(0x1 << 4);	//set GPIO 39 ca8202 pin162 
    #elif defined(CARD_SENSE3_USE_GPIO38)
     regs0->sft_cfg0 &= ~(0x1 << 5);	//set GPIO 38 ca8202 pin161 
	#elif !defined(IC_8202D) //zhongshan add 2005-8-23 12:22
     regs0->sft_cfg0 &= ~(0x1 << 6);  //set GPIO 29 ca8202 pin145
    #endif
    #endif//#ifdef PORTABLE_DVD
    regs0->sft_cfg1 &= ~(0x1 << 3);  //set GPIO 16 ca8202 pin76 
    GPIO_M_SET(CARD_SENSE1_PIN, 1); 
    GPIO_M_SET(CARD_POWER_RESET,1); 
    #ifdef HDMI_SMC_CLE
        GPIO_M_SET(CARD_SMC_CLE_PIN, 1);    // benson 2004/11/17 01:40PM  set gpio 36
        GPIO_E_SET(CARD_SMC_CLE_PIN, 1);    // benson 2004/11/17 01:40PM  set gpio 36
    #endif
    
     #ifdef IC_8202D //kenny 2005/3/4 add for 8202D
     regs0->sft_cfg15 = 1 | (1<<3) | (1<<6) | (1<<9) | (1<<12); 
     regs0->sft_cfg16 = 1 | (1<<4) | (1<<8) | (1<<12);  
     #ifdef SCALER_6500//caoh 2006-1-12 11:32
         #if defined(ORITRON_HK_HDMI_CARD)||defined(HDMI_16_BIT_256PIN_BOARD)   // caoh 2006-01-12   // lxg add HDMI_16_BIT_256PIN_BOARD 2006-4-18
       regs0->sdc_data_cnt[9][0] |= 0xc0;
       #else
     regs0->sdc_data_cnt[9][1] |= 0x03;//caoh for I2C data & clk re-set.20051220
       #endif
     #endif
     regs0->sft_cfg17 = 1 | (1<<4) | (1<<8) | (1<<12);
     #endif 
    
    
  #elif defined(CARD_SETUP_TYPE_4)  
    #if defined(MP_BOARD_256_PIN_NON_SHARE)//kenny 2004/7/14
    regs0->sft_cfg1 &= ~(0x1 << 3);  //set GPIO 16 ca8202 pin76 
    GPIO_M_SET(CARD_SENSE1_PIN, 1); 
    GPIO_M_SET(CARD_POWER_RESET,1);     
    #elif defined(MP_BOARD_216_PIN_NON_SHARE)
    regs0->sft_cfg1 &= ~(0x1 << 3);  //set GPIO 16 ca8202 ns-216 pin66  
    #ifdef USE_SERVO_DFCT_GPIO //if define USE_SERVO_DFCT_GPIO, then we  set pin55 to be GPIO
    regs0->sft_cfg4 &= ~(0x1 << 6);  //set GPIO 8 ca8202 ns-216 pin55 (servo DFCT pin)
    
    #endif
    GPIO_M_SET(CARD_SENSE1_PIN, 1); 
    GPIO_M_SET(CARD_POWER_RESET,1); 
    #else   
    regs0->sft_cfg1 &= ~(0x1 << 3);  //set GPIO 16 ca8202 pin76 
    GPIO_M_SET(CARD_SENSE1_PIN, 1); 
    GPIO_M_SET(CARD_POWER_RESET,1); 
    #endif
    
    #ifdef IC_8202D //kenny 2005/3/4
    regs0->sft_cfg15=1 | (1<<3) | (1<<6);//2005/2/18;
    #endif
    
  #elif defined(CARD_SETUP_TYPE_5)  
    regs0->sft_cfg0 &= ~(0x1 << 7);  //set CS1  disable
    regs0->sft_cfg1 &= ~(0x1 << 5);  //set A12  disable
    #ifdef PMP_PCB_VER_B 
    regs0->sft_cfg1 &= ~(0x1 << 3);  //set GPIO 16 ca8202 pin76 
    #else  //PMP_PCB_VER_C
     regs0->sft_cfg0 &= ~(0x1 << 4);     //set GPIO 39 ca8202 pin162    
    #endif 
    regs0->sft_cfg1 &= ~(0x1 << 1);  //set GPIO 18 ca8202 pin78  
    GPIO_M_SET(CF_INS_SENSE, 1);    
    GPIO_M_SET(CARD_POWER_RESET,1); 
    GPIO_E_SET(CF_INS_SENSE, 0);
    
     #ifdef IC_8202D //kenny 2005/5/19 add for 8202D
     regs0->sft_cfg15 = 1 | (1<<3) | (1<<6) | (1<<9) | (1<<12); 
     regs0->sft_cfg16 = 1 | (1<<4) | (1<<8) | (1<<12);  
     regs0->sft_cfg17 = 1 | (1<<4) | (1<<8) | (1<<12);
     #endif 
    
  #endif
  #ifndef CARD_SETUP_TYPE_5
    GPIO_E_SET(CARD_SENSE1_PIN, 0);
    GPIO_E_SET(CARD_SENSE2_PIN, 0);
  #endif        
  #if !defined(CARD_SETUP_TYPE_4)&&!defined(CARD_SETUP_TYPE_5)      
    GPIO_E_SET(CARD_SENSE3_PIN, 0);
  #endif    
    GPIO_E_SET(CARD_POWER_RESET,1);
    CardEna=TRUE;
    
    GPIO_O_SET(CARD_POWER_RESET,1);  //Power Off
    
    #ifdef CARD_SENSE3_USE_GPIO38  //denghg modify force  set GPIO FIRST.Because it is been change other Function sometimes 2006-9-20 9:30
    regs0->sdc_data_cnt[9][0] |= (0x1 << 6);
    GPIO_M_SET( CARD_SENSE3_PIN ,1);
    GPIO_E_SET( CARD_SENSE3_PIN, 0);
    #endif
    
}   
/**************************************************************************
 *                                                                        *
 *  Function Name: CardStorageIsPlugIn                                    *
 *                                                                        *
 *  Purposes:                                                             *
 *    Check card  Storage plug in or not                                  *
 *  Descriptions:                                                         *
 *    Check card  Storage plug in or not                                  *
 *  Arguments:                                                            *
 *          NONE                                                          *
 *  Returns:                                                              *
 *          0: FALSE                                                               *
 *          1: TRUE                                                             *
 *                                                                        *
 *  See also:    NONE                                                     *
 *                                                                        *
 **************************************************************************/
int CardStorageIsPlugIn(void)
{
    UINT8 card_result=0;
    switch(storage_type)
    {
        #if defined(COMPACT_FLASH)    
         case CF_CARD_DEVICE:
                        #if defined(CARD_SETUP_TYPE_5)
                         if((PMP_CF_Card_Play==1)&&(PMP_CF_Card_Insert==0))
                              ircmd_return();   //card_result=1;
                         else     
                              card_result=0;
                        #else 
                         if(GPIO_I_GET(CARD_SENSE2_PIN))  card_result=1;
                        #endif  
                         break; 
        #endif     
        #if defined(SD_MMC_CARD)    
         case SD_CARD_DEVICE:
                        #ifdef CARD_SETUP_TYPE_4    
                         if(GPIO_I_GET(CARD_SENSE1_PIN))  card_result=1;
                        #else  
                         if(GPIO_I_GET(CARD_SENSE3_PIN))  card_result=1;
                        #endif 
                         break; 
        #endif  
        #if defined(MEMORY_STICK)    
         case MS_CARD_DEVICE:
                        #ifdef CARD_SETUP_TYPE_4    
                         if(GPIO_I_GET(CARD_SENSE2_PIN))  card_result=1;
                        #else 
                         if(GPIO_I_GET(CARD_SENSE1_PIN))  card_result=1;
                        #endif 
                         break; 
        #endif  
        #if defined(SMART_MEDIA)    
         case SMC_CARD_DEVICE:
                         if(GPIO_I_GET(CARD_SENSE1_PIN))  card_result=1;
                         break; 
        #endif  
         default:
            break;
    }     
    
    if(card_result)  return FALSE;
    else             return TRUE;
}
/**************************************************************************
 *                                                                        *
 *  Function Name: Detect_Card_Storage                                    *
 *                                                                        *
 *  Purposes:                                                             *
 *    Detect which card exist                                             *
 *  Descriptions:                                                         *
 *    Use card GPIO to Detect which card exist                            *
 *  Arguments:                                                            *
 *          NONE                                                          *
 *  Returns:                                                              *
 *          0x02: CF ,0x04: SD_MMC ,0x08: MS ,0x10: SMC                   *
 *          0x06: SD+CF ,0x0a: CF+MS ,0x12: CF+SMC                        *
 *                                                                        *
 *  See also:    NONE                                                     *
 *                                                                        *
 **************************************************************************/
BYTE Detect_Card_Storage()
{
     UINT8 card_sense=0;
     BYTE  card_storage_type=0;
    
    #ifndef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-4-11 16:48
    detect_type &= USB_DEVICE;//liweihua 2004-6-7 
    #endif//DIRECT_ACCESS_MEDIA
    
   #ifdef CARD_SETUP_TYPE_4
     card_sense=GPIO_I_GET(CARD_SENSE1_PIN)<<1;
     card_sense|=GPIO_I_GET(CARD_SENSE2_PIN);    
         
     //printf("card_sense =%x!\n",card_sense);
     switch(card_sense)
     {
      case 2:
             card_storage_type|=MS_CARD_DEVICE; 
             break; 
      case 1:
             card_storage_type|=SD_CARD_DEVICE;              
             break; 
      default: 
             card_storage_type=0;
             break; 
     }   
   #elif defined(CARD_SETUP_TYPE_5)  
        card_storage_type|=CF_CARD_DEVICE; 
        //liweihua mod 2004-12-1
        int check_result=PMP_CF_Card_IsPlugIn();
        #ifdef SUPPORT_MULTI_PARTITION//liweihua 2004-12-10
        if((check_result>1) || (check_result<0)) 
        {
            #if defined(FAT_FILE_MODE) && (!defined(PMP_UI))//liweihua 2005-1-5
            if(fat_play_mode == 1)
                Refresh_FAT_Mode_GUI();
            else if((fat_play_mode == 2)&&(pFsJpeg->gifsState == FS_STATE_HDD))
            #else
            if(pFsJpeg->gifsState == FS_STATE_HDD)
            #endif
                Refresh_Partition_Menu();
        }
        else
        #endif
        if(check_result==1) 
         PMP_CF_Card_Insert=1;
        else
         PMP_CF_Card_Insert=0;
   #else  //CARD_SETUP_TYPE_1 ,CARD_SETUP_TYPE_2,CARD_SETUP_TYPE_3
     card_sense=GPIO_I_GET(CARD_SENSE1_PIN)<<2;
     card_sense|=GPIO_I_GET(CARD_SENSE2_PIN)<<1;
     card_sense|=GPIO_I_GET(CARD_SENSE3_PIN);
     //printf("card_sense =%x!\n",card_sense);
     switch(card_sense)
     {
      case 7:
             card_storage_type=0;
             break;  
      case 6:
             card_storage_type|=SD_CARD_DEVICE; 
             break; 
      case 5:
             card_storage_type|=CF_CARD_DEVICE; 
             break; 
      case 4:
             card_storage_type|=CF_CARD_DEVICE; 
             card_storage_type|=SD_CARD_DEVICE; 
             break; 
      case 3:
             card_storage_type|=MS_CARD_DEVICE; 
             break; 
      case 2:
             card_storage_type|=SMC_CARD_DEVICE;
             break; 
      case 1:
             card_storage_type|=CF_CARD_DEVICE; 
             card_storage_type|=MS_CARD_DEVICE; 
             break; 
      case 0:
             card_storage_type|=CF_CARD_DEVICE; 
             card_storage_type|=SMC_CARD_DEVICE;
             break; 
      default: 
             card_storage_type=0;
             break; 
     }   
   #endif    
   
    #ifdef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-4-11 16:50
    detect_type = card_storage_type;
    #else//DIRECT_ACCESS_MEDIA
     detect_type |=card_storage_type;//liweihua 2004-6-7
    #endif//DIRECT_ACCESS_MEDIA 
     
#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
        if((source_play_mode==CARD_PLAY_MODE) && (card_storage_type) && (system_state!=SYSTEM_BROWSE) && (detect_result_last!=storage_parity_type[detect_type&(~USB_DEVICE)]))
        {
            #ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
            printf_w("CARD is plug in when in CARD state(have USB in).....\n");
            #endif
            usb_card_state = HAS_CARD_AND_SWITCH_TO_CARD;
            now_valid_type = (detect_type & 0x1e);
            storage_type = 0;
        }
#endif
     return card_storage_type;
}   
#endif //#ifdef SPHE8202_CARD_STORAGE  
//-----------------------------------------------------------
#ifdef SUPPORT_USB
extern UINT8 UsbTestUnitReady(BYTE dev_lun);
extern BYTE IsUSBCardReader(void);
extern UINT8 USBEna;  
extern UINT8 CBWLUN;
extern UINT8 SLAVE_ENUMERATED;
extern UINT8 USB_ADDR; 
extern UINT8 MaxLUN;
extern void USBCardReaderDetect(void);
/**************************************************************************
 *                                                                        *
 *  Function Name: UsbIsPlugIn                                            *
 *                                                                        *
 *  Purposes:                                                             *
 *    Detect if the U disk is pluged                                      *
 *  Descriptions:                                                         *
 *    use UHCI command Detect if the U disk is pluged                                      *
 *  Arguments:                                                            *
 *          NONE                                                          *
 *  Returns:                                                              *
 *          TRUE or FALSE                                                 *
 *                                                                        *
 *  See also:    NONE                                                     *
 *                                                                        *
 **************************************************************************/
int UsbIsPlugIn(void)
{
    int detect_result = 0;
    detect_result = uhci_slaveDetect();
    if((detect_result == 0) && (card_plug_state ==  USER_DO_PLUG_IN))
        return TRUE;
    else if((detect_result == 0) && (card_plug_state == USER_DO_PLUG_OUT))
        return FALSE;
    else
        return FALSE;
}
/**************************************************************************
 *                                                *
 *  Function Name: uhci_slaveDetect                                       *
 *                                                *
 *  Purposes:                                                             *
 *    detect whether the U-Device is plugged in or not                    *
 *  Descriptions:                                                         *
 *    This function detect whether the U-Device is plugged in or not.     *
 *  Arguments:                                                            *
 *          NONE                                                          *
 *  Returns:                                                              *
 *          0: nothing  1: plug in  2: detached                           *
 *  See also:    NONE                                                     *
 *                                                *
 **************************************************************************/
/**************************************************************************************************
 *                                                *
 * Description: This function detect whether the U-Device is plugged in or not.           *
 *                                                *
 * Author     : wthsin                                *
 * Date       : 2004/1/14 08:31pm                                     *
 *                                                *
 * Update     : liweihua 2004-6-7
 **************************************************************************************************/
BYTE usb_plug_out_flag; //for USB plug out when copying lijd 2004-11-19 16:15
#ifdef  SUPPORT_USB_HID	
BYTE usb_mouse_in_flag=0;
#endif
#ifdef PLUG_IN_USB_CLOSE_LOADER//chenzhao200602014//hongfeng add for OP 2006-1-11
BYTE need_close_door=1;//hongfeng add 2006-1-11
#endif


#ifndef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-4-7 18:11
UINT32 uhci_slaveDetect(void)
{
    int  result;
    
    #if !defined(SUPPORT_CD_RIPPING)&&!defined(SUPPORT_FILE_COPYING)&&!defined(SUPPORT_MP3_ENCODER)
     if((play_state>=VCD_STATE_NORMAL&&play_state<=VCD_STATE_9FRAMES)||(play_state<=VCD_STATE_MP3_FILELIST))
     return 0;  //lyc 2006-9-20,Don't detect others media type at playing-process [mantis:8395] 
    #endif
    //-------------------------------------------------------------------------
    // Wait for USB enumeration
    //-------------------------------------------------------------------------
    if(!SLAVE_ENUMERATED)
    {                    // wait for an USB device to be inserted  
        if(uhci_PlugInOutDetect())
        {                    
             printf("slave is plug in!!!\n");
             #ifdef PLUG_IN_USB_CLOSE_LOADER//chenzhao200602014//hongfeng add for OP 2006-1-7
                 #ifdef MULTIDISC_LOADER
                 if(is_multidisc_open_state()&&(need_close_door == 1))
                     multidisc_loader_post_cmd(MULTIDISC_CMD_CLOSE);
                 #else
                 if(CDOpened()&&(need_close_door == 1))//modify hongfeng 2006-1-11
                     close_tray(0);
                 #endif
             #endif
               #ifdef SUPPORT_STOP_PLAY_READ_USB_CARD //caoh 2005-8-31 9:54 
                  if(media_change_flag_mark)
                 media_change_flag = 0;
               #endif
             if((storage_type == 0)&&(cd_type_loaded == CDUNKNOWN)) //sunzhh modify 2005-4-5
             AVD_SetMediaInterrupt();    //sunzhh add for card not being recognized in the USB cardreader 2005-3-10
             usb_plug_out_flag=0;
            #if defined(HOST_UHCI)  
             uhci_reset(); //wthsin   2003/12/30 04:43
            #elif defined(USB_HOST_DRV)  
              extern UINT8    dev_Is_FullSpeed;
              usb_host_init();
              dev_Is_FullSpeed=set_usb_host_bus_reset();           //Usb Bus Reset
            #endif  
             USB_ADDR=uDisk_ADDR;
             result=EnumUsbDev(USB_ADDR);
          if(no_disk_cnt == 1)//liweihua 20040324
                 system_state=SYSTEM_OPEN;   //wthsin,    2004/3/16 07:36pm    
         if(result)
         {                      // enumerate USB device, assign USB address = #1
                SLAVE_ENUMERATED = TRUE;    // Set slave USB device enumerated flag
             #ifdef  SUPPORT_USB_HID	
		     	if(usb_mouse_in_flag)
		            return 1;  
             #endif
                
                #ifdef SUPPORT_SLOT_IN_LOADER
                card_plug_state = USER_DO_PLUG_IN;
                #elif defined(NO_DVD_SERVO)	//yaowh add 2005-11-4 15:50
                	card_plug_state = USER_DO_PLUG_IN;
                #else
                if((play_state != VCD_STATE_OPEN)&&!IsUSBCardReader())//liweihua add 2004-3-11 //sunzhh modify 2005-3-16
                card_plug_state = USER_DO_PLUG_IN;
                else
                    card_plug_state = 0;
                #endif  
                
                #ifdef SP1000_NO_DVD
                card_plug_state = USER_DO_PLUG_IN;
                #endif  
                detect_type |= USB_DEVICE;   //wthsin ,2004/3/1 03:16pm
                MaxLUN = 0;     //Maoyong 2004.05.19
                #ifdef PLUG_IN_USB_CLOSE_LOADER//chenzhao200602014//hongfeng add for OP 2006-1-11
                need_close_door = 0;
                #endif
                #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
                if((media_type==MEDIA_CARD) && (system_state!=SYSTEM_BROWSE))
                {
                    if((source_play_mode==USB_PLAY_MODE) && (detect_type&USB_DEVICE))
                    {
                        #ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
                        printf_w("USB is plug in when in USB state(have card in).....\n");
                        #endif
                        usb_card_state = HAS_USB_AND_SWITCH_TO_USB;
                        now_valid_type = USB_DEVICE;                 
                    }

                }
                #endif
            return 1;
         }          
        }
    }
    //-------------------------------------------------------------------------
    // USB enumerated, proceed accordingly
    //-------------------------------------------------------------------------
    else
    {
       if(!uhci_PlugInOutDetect())          // test for slave device detach  
       {                    
        #ifdef SUPPORT_MIDI
        #ifdef SUPPORT_CARDREADER_TEST//added by ouyang, 2006-4-18 16:41			if(iMidi_storage_type == USB_DEVICE)
	     {	
               printf_w("usb is out==============\n");		    
               MidiCardReadInit(); 
               iMidi_storage_type = 0;
	     }
       	#endif//SUPPORT_CARDREADER_TEST   
        #endif              
       #ifdef SUPPORT_MP3_ENCODER //qinhua,2005-11-10 20:34
               ripping_flag=0;   
       #endif            

        #if 0//def SUPPORT_CD_RIPPING//TW mark it.200607
            fs_shutdown();
        #endif

        
            fs_remove_device(); //Simon 2006.6.30
        
            printf("slave is detached!!!\n");
	   	    
         #ifdef   FIX_PLAY_CARD_THEN_OUT_USB_BECAME_STOP
	  #ifdef   IR_SWITCH_DVD_USB_CARD_AVIN_DVB	 
         if(source_play_mode == CARD_PLAY_MODE)
         {
               detect_type &= (~USB_DEVICE);
               storage_type &= (~USB_DEVICE);
               return 2;
         }
	 #endif//end=> #ifdef   IR_SWITCH_DVD_USB_CARD_AVIN_DVB	 
	 #endif//end=> #ifdef   FIX_PLAY_CARD_THEN_OUT_USB_BECAME_STOP
            #ifdef PLUG_IN_USB_CLOSE_LOADER//hongfeng add for OP 2006-1-11
            need_close_door = 1;
            #endif
	   	    #ifdef USBCARD_PLUG_OUT_CLEAR_SETUP_PROG
            if(source_play_mode == USB_PLAY_MODE)
                usb_card_state = USB_CARD_WAS_PLUG_OUT;
            if(is_setup_prog_menu() && (source_play_mode==USB_PLAY_MODE))
            {
                if(full_scrn&SETUP)
                    ExitSetupPage(0);
                else
                    osd_init();
            }
            #endif
            
	   	   #ifdef  SUPPORT_USB_HID 
	   	    if(usb_mouse_in_flag)
	   	    {
	   	   	    SLAVE_ENUMERATED = FALSE;
	   	   	    usb_mouse_in_flag=0;
	   	        return 2;
	   	    }				
           #endif

#ifdef SUPPORT_STOP_PLAY_READ_USB_CARD  //caoh 2005-8-31 9:54 
  #ifdef ADJUST_JPEG_SLIDE_TIME
    if(((media_type == MEDIA_CARD)||(storage_type == USB_DEVICE))&&(Is_JPEG_PLAY_STATE()) )
      //qinhua ,2005-9-13 14:18,add for after usb plugout JPEG show long time
     {    
     	   SwitchMedia(CARD2CD);   
     }
  #endif
#endif      

           #if defined(USB_HOST_DRV)   
            usb_host_drv_reg_wr(USB_HOST_SOF_CTL,0x0fff0003);  //STOP SOF
           #endif    
            usb_plug_out_flag=1;
     #ifdef MP3_ONLY_STOP_TO_GUI 
            if( (play_state==VCD_STATE_MP3_FILELIST) && (media_type==MEDIA_CARD) )
            {
             ShowTitle();
             SwitchMedia(CARD2CD);      //wsf 2004-9-16 16:43
            }
     #endif 
     
     #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB   /////////YANGLI, 2006-2-28 13:14
            if(source_play_mode==USB_PLAY_MODE)
            {
                ircmd_stop();
            }
     #endif
            #ifdef USBCARD_PLUG_OUT_CLEAR_SETUP_PROG
            if(is_setup_prog_menu() && (source_play_mode==USB_PLAY_MODE))
            {
                ircmd_stop();
                
                cardFile.status = CARD_STATUS_NG;
            }
            #endif
            
            #ifdef SUPPORT_SETUP_POPUP_MEDIA_GUI
            if( (full_scrn&SETUP) && (media_type==MEDIA_CARD)&&(storage_type == USB_DEVICE) )
            {
                ExitSetupPage(0);
            }
            #endif
            
            SLAVE_ENUMERATED = FALSE;               // return to un-enumeration
            if((media_type == MEDIA_CARD)&&(storage_type == USB_DEVICE))    //liweihua mod 2004-3-30
            {
                if(Mp3ReadFinish)
                {
                    Mp3ReadFinish = 0;
                    cd_type_loaded = CDUNKNOWN;       //sunzhh 2005-3-15    
                }      
                if((play_state == VCD_STATE_PAUSE)||(GetCurrentFileType() == CDROM_WMA))//liweihua mod 2004-4-19
                    ircmd_stop();           
                AVD_SetMediaInterrupt();        //wthsin ,  2004/4/19 02:47pm           
            }
            if(play_state != VCD_STATE_OPEN) //liweihua add 2004-2-1
            {
                if((media_type == MEDIA_CARD)&&(storage_type == USB_DEVICE))
                play_state = VCD_STATE_STOP;
             
            card_plug_state = USER_DO_PLUG_OUT;
            }

		#ifdef   FIX_CARD_USB_IN_THEN_DETACHED_USB_FSUI_NOT_DISAPPEAR
		#ifdef   IR_SWITCH_DVD_USB_CARD_AVIN_DVB
	       card_plug_state = USER_DO_PLUG_OUT;//20060419 tiany add debug
              cardFile.status = CARD_STATUS_NG;	  //20060419 tiany add debug
		#endif//end=>  #ifdef   IR_SWITCH_DVD_USB_CARD_AVIN_DVB		
		#endif//end=> #ifdef   FIX_CARD_USB_IN_THEN_DETACHED_USB_FSUI_NOT_DISAPPEAR		

			
            detect_type &= (~USB_DEVICE);
            storage_type &= (~USB_DEVICE);
        return 2;                       // exit now.
       }
    }   
    //-------------------------------------------------------------------------
    //USB Card reader special process
    //-------------------------------------------------------------------------
    USBCardReaderDetect();
       
    return 0;
}     
#else//DIRECT_ACCESS_MEDIA
UINT32 uhci_slaveDetect(void)
{
    int  result;

    //-------------------------------------------------------------------------
    // Wait for USB enumeration
    //-------------------------------------------------------------------------
    if(!SLAVE_ENUMERATED)
    {   // wait for an USB device to be inserted
        if(uhci_PlugInOutDetect())
        {
            printf_w("slave is plug in!!!\n");

            usb_plug_out_flag=0;

            #if defined(HOST_UHCI)
            uhci_reset(); //wthsin   2003/12/30 04:43
            #elif defined(USB_HOST_DRV)
            extern UINT8    dev_Is_FullSpeed;
            usb_host_init();
            dev_Is_FullSpeed=set_usb_host_bus_reset();           //Usb Bus Reset
            #endif

            USB_ADDR = uDisk_ADDR;

            result = EnumUsbDev(USB_ADDR);

            if(no_disk_cnt == 1)//liweihua 20040324
                system_state=SYSTEM_OPEN;   //wthsin,    2004/3/16 07:36pm

            if(result)
            {                      // enumerate USB device, assign USB address = #1
                SLAVE_ENUMERATED = TRUE;    // Set slave USB device enumerated flag

                #ifdef  SUPPORT_USB_HID
                if(usb_mouse_in_flag)
                    return 1;
                #endif

                card_plug_state = USER_DO_PLUG_IN;
                detect_type = USB_DEVICE;   //wthsin ,2004/3/1 03:16pm
                MaxLUN = 0;     //Maoyong 2004.05.19

            return 1;
        	}
    	}
    }
    //-------------------------------------------------------------------------
    // USB enumerated, proceed accordingly
    //-------------------------------------------------------------------------
    else
    {
        if(!uhci_PlugInOutDetect())          // test for slave device detach  
        {
            printf_w("slave is detached!!!\n");
	   	    
            #ifdef  SUPPORT_USB_HID 
            if(usb_mouse_in_flag)
            {
                SLAVE_ENUMERATED = FALSE;
                usb_mouse_in_flag=0;
                return 2;
            }				
            #endif

            #if defined(USB_HOST_DRV)
            usb_host_drv_reg_wr(USB_HOST_SOF_CTL,0x0fff0003);  //STOP SOF
            #endif

            usb_plug_out_flag=1;
            
            SLAVE_ENUMERATED = FALSE;               // return to un-enumeration

            if((media_type == MEDIA_CARD)&&(storage_type == USB_DEVICE))    //liweihua mod 2004-3-30
            {
                if(Mp3ReadFinish)
                {
                    Mp3ReadFinish = 0;
                    cd_type_loaded = CDUNKNOWN;       //sunzhh 2005-3-15    
                }      
                
                if((play_state == VCD_STATE_PAUSE)||(GetCurrentFileType() == CDROM_WMA))//liweihua mod 2004-4-19
                    ircmd_stop();
                    
                AVD_SetMediaInterrupt();        //wthsin ,  2004/4/19 02:47pm           
            }

            if(play_state != VCD_STATE_OPEN) //liweihua add 2004-2-1
            {
                if((media_type == MEDIA_CARD)&&(storage_type == USB_DEVICE))
                    play_state = VCD_STATE_STOP;
             
                card_plug_state = USER_DO_PLUG_OUT;
            }
            
            AVD_SetMediaInterrupt();
            atapi_p_start_stop_unit(Immed_1,START_STOP_DO_STOP);
            play_state = VCD_STATE_CLOSE;
            ircmd_post_func(CMD_FUNC | CMD_FUNC_OPEN);
            system_state = SYSTEM_OPEN;
            detect_type = 0;
            storage_type = 0;
            media_type = MEDIA_NOTHING;
            full_scrn = 0;
            ClearOsdMsg(0);
            t_disp = 0;
            osd_init();

            return 2;                       // exit now.
        }
    }

    return 0;
}
#endif//DIRECT_ACCESS_MEDIA

#endif//end SUPPORT_USB
/**************************************************************************
 *                                                                        *
 *  Function Name: CardTestReady                                          *
 *                                                                        *
 *  Purposes:                                                             *
 *    detect and initialize card/usb, then set card to browse             *
 *  Descriptions:                                                         *
 *    detect and initialize card/usb, then set card to browse             *
 *  Arguments:                                                            *
 *          NONE                                                          *
 *  Returns:     NONE                                                     *
 *                                                                        *
 *  See also:    NONE                                                     *
 *                                                                        *
 **************************************************************************/
void CardTestReady(void)
{   
    UINT8 media_exit=0;
    
#ifdef  IR_SWITCH_CD_USB_CF_OTHER
    storage_type = detect_result_last;        
        now_valid_type = storage_type; //for bug:read cf,insert usb,will read cf again.
        #ifndef NO_SWITCH_GPIO
        	#ifdef HIGH_CORTROL_CF
        		GPIO_O_SET(SWITCH_GPIO,0);//dingzhy for switch bus 4-10-22 10:43
        	#else
        		GPIO_O_SET(SWITCH_GPIO,1);
        	#endif
		#endif
#endif

    if(storage_type!=0)
    {
        #ifdef SPHE8202_CARD_STORAGE    //Maoyong 2004-8-12 do card power reset.
        if(storage_type != USB_DEVICE)
            Card_power_reset();
        #endif
    switch(storage_type)
    {         
            #ifdef SPHE8202_CARD_STORAGE         
        #if defined(COMPACT_FLASH)    
         case CF_CARD_DEVICE:
            #ifdef IR_SWITCH_CD_USB_CF_OTHER  //dingzhy 4-10-22 10:41
                #ifndef NO_SWITCH_GPIO
                	#ifdef HIGH_CORTROL_CF
                		GPIO_O_SET(SWITCH_GPIO,1);//dingzhy use vfd data for test switch bus 4-10-22 10:43
                	#else
                		GPIO_O_SET(SWITCH_GPIO,0);
                	#endif
            	#endif         
            #endif         
                         #ifdef CARD_SETUP_TYPE_2
                           regs0->fm_gpio_mode = 8;  
                         #elif defined(CARD_SETUP_TYPE_3)||defined(CARD_SETUP_TYPE_5)   
                           regs0->gpio_mode_B=2;
                           regs0->fm_gpio_mode = 3;
                         #endif  
                         
                        #ifdef PMP_DVD
                        ioPowerOn();//kenny 2005/5/12 move the code from pmp_drv.c
                        #endif
                         
                   #ifdef IDE_CF_SW 
                   IdeSetSequence(HD);//kenny 2004/8/29
                   #endif
                         cfIdeDetect();
                         media_exit=1;
                         break; 
        	#endif  //#if defined(COMPACT_FLASH)   
        #if defined(SD_MMC_CARD)    
         case SD_CARD_DEVICE:
                        
                        
                        #ifdef CARD_SETUP_TYPE_2 //kenny 2005/3/8
                        regs0->fm_gpio_mode = 3;  
                        #elif defined(CARD_SETUP_TYPE_3)||defined(CARD_SETUP_TYPE_4)    
                            regs0->gpio_mode_B=0;
                            regs0->fm_gpio_mode = 3;   
                            
                        #endif //CARD_SETUP_TYPE_2
                        
                        
                        if(sdDetect())    //wthsin, 2004/6/24 07:40pm
                        {
                           psprintf(RegionValStr[REGION1], "SD Err");
                           PrintOsdMsg(STR_OS_SPACE, REGION1, 0, 1);  
                        }
                        else    
                          media_exit=1;     
                        break; 
        #endif  //#if defined(SD_MMC_CARD)
        #if defined(MEMORY_STICK)    
         case MS_CARD_DEVICE:
                        
                        
                        #ifdef CARD_SETUP_TYPE_2 //kenny 2005/3/8
                            regs0->fm_gpio_mode = 4;   
                        #elif defined(CARD_SETUP_TYPE_3)||defined(CARD_SETUP_TYPE_4)        
                        regs0->gpio_mode_B=0;
                            regs0->fm_gpio_mode = 4;  
                            
                        #endif //CARD_SETUP_TYPE_2
                        
                        // 2006-08-09, mimitsai modify, when detect card fail, the media_exit should not be 1.
                        if(msDetect()!=MS_CMD_FAIL)
                          media_exit=1;
                                
                        break; 
        #endif  //#if defined(MEMORY_STICK)
        #if defined(SMART_MEDIA)    
         case SMC_CARD_DEVICE:
                        #ifdef CARD_SETUP_TYPE_2
                          regs0->fm_gpio_mode = 8;  
                        #elif defined(CARD_SETUP_TYPE_3)    
                          regs0->fm_gpio_mode = 3;  
                          regs0->gpio_mode_B=1;
                        #endif //CARD_SETUP_TYPE_2
                        if(smcDetect())
                        {
                           psprintf(RegionValStr[REGION1], "SMC Err");
                           PrintOsdMsg(STR_OS_SPACE, REGION1, 0, 1);  
                        }
                        else 
                          media_exit=1;              
                        break; 
        #endif  //#if defined(SMART_MEDIA)
            #endif//#ifdef SPHE8202_CARD_STORAGE
            #ifdef SUPPORT_USB//liweihua 2004-6-7
            case  USB_DEVICE:
                #if defined(IR_SWITCH_CD_USB_CF_OTHER)||defined(SPHE8202_USB_Write)||defined(FILE_MODE_WRITE)||defined(SELECT_MEDIA_IN_SETUPMENU)||defined(SWITCH_CD_CARD_USB)||defined(DIRECT_ACCESS_MEDIA)  //dingzhy add it//sunzhh modify 2005-3-11
                UsbTestReady();    //for bug:power on without usb,then insert usb,but can't play usb; dingzhy 04-10-22
                #endif      

                media_exit=1;
                break;
            #endif//#ifdef SUPPORT_USB
         default:
                         return;
    } 
    } 
    //#endif 
    if((media_exit)&&!(full_scrn&(SETUP|PROGRAM)) )   //sunzhh modify 2005-3-9
    { 
        #ifdef SPHE8202_ALL_TYPE_CARD_WRITE
        if(card_browse_sign)
        #endif
        #ifdef FILE_MODE_WRITE                  //sunzhh add for file mode 2005-1-14
        if(!file_mode_flag)                   
        #endif          
        CardSetBrowse();
    }
}


/**************************************************************************
 *                                                                        *
 *  Function Name: CARDIsPlugIn                                           *
 *                                                                        *
 *  Purposes:                                                             *
 *    Detect if the USB or CARD is pluged                                        *
 *  Descriptions:                                                         *
 *    Detect if the USB or CARD is pluged                                        *
 *  Arguments:                                                            *
 *          NONE                                                          *
 *  Returns:                                                              *
 *          0: FALSE                                                               *
 *          1: TRUE                                                             *
 *  See also:    NONE                                                     *
 *                                                                        *
 **************************************************************************/
int CARDIsPlugIn(void)
{//liweihua update 2004-6-8
    int detect_result = 0;  
    if(storage_type!=0)
    {
     #ifdef SUPPORT_USB
        if(storage_type == USB_DEVICE)
            detect_result=UsbIsPlugIn();
     #endif
     #if defined(SUPPORT_USB)&&defined(SPHE8202_CARD_STORAGE)       
        else    
     #endif 
     #ifdef SPHE8202_CARD_STORAGE
        detect_result=CardStorageIsPlugIn();  
     #endif       
    }  
   return  detect_result; 
}


/**************************************************************************
 *                                                                        *
 *  Function Name: polling_storage                                        *
 *                                                                        *
 *  Purposes:                                                             *
 *    polling to detect usb/card plus in or plug out                      *
 *  Descriptions:                                                         *
 *    polling to detect usb/card plus in or plug out                      *
 *  Arguments:                                                            *
 *          NONE                                                          *
 *  Returns:     NONE                                                     *
 *                                                                        *
 *  See also:    NONE                                                     *
 *                                                                        *
 **************************************************************************/
extern int check_support_usb(void); //wthsin, 2004/5/27 01:34pm
#ifndef DIRECT_ACCESS_MEDIA//added by wangwei,2005-11-15 15:46
    #ifdef SUPPORT_SETUP_POPUP_MEDIA_GUI
    extern void show_setup_popup_media_gui(void);
    #endif
void polling_storage()
{//liweihua update 2004-6-8         
    BYTE detect_result = 0;

    #ifdef SPHE8202_CARD_STORAGE
    if(CardEna == TRUE)   //only after card init then polling.
        Detect_Card_Storage();
    #endif
    
  #if defined(SUPPORT_USB)                  
     if(USBEna == TRUE)    //only after USB init then polling.
    {
        #ifdef SPHE1000
            #ifdef HOST_UHCI 
              uhci_slaveDetect();
            #endif
        #else
            #if defined(HOST_UHCI)||defined(USB_HOST_DRV) 
            if(check_support_usb()==0)   return;  
            #endif//defined(HOST_UHCI)||defined(USB_HOST_DRV) 

             #ifdef UNPOLLING_USB_WHEN_SYSTEM_STATE_IS_TS
              if(system_state == SYSTEM_TS) 
              return;
             #endif 
              uhci_slaveDetect();
            #endif//#ifdef SPHE1000
    }
  #endif//defined(SUPPORT_USB)
  
    detect_result=storage_parity_type[detect_type];
        
    #ifdef SUPPORT_MIDI
    #ifdef SUPPORT_CARDREADER_TEST//added by ouyang, 2006-4-18 16:41
    if((iMidi_storage_type == SD_CARD_DEVICE)&&((detect_type & SD_CARD_DEVICE) == 0)
    || (iMidi_storage_type == MS_CARD_DEVICE)&&((detect_type & MS_CARD_DEVICE) == 0))
       {
        printf_w("CARD is out==============\n");		    
        MidiCardReadInit(); 
        iMidi_storage_type = 0;
       }
    #endif//SUPPORT_CARDREADER_TEST
    #if 0
    psprintf(RegionValStr[REGION2], "DT %x ST %x DR %x",detect_type,storage_type,detect_result);
    PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
    #endif
    #endif
    
    #ifdef SWITCH_CD_CARD_USB//liweihua 2004-6-9
    extern BYTE select_media_type;
    if(detect_type&select_media_type)
        detect_result = select_media_type;
    else
        select_media_type = 0;
    #endif
    
    #ifdef IR_SWITCH_CD_USB_CF_OTHER   //dingzhy for bus switch 04-10-22
    if((detect_type)&&(now_valid_type))
    {
    detect_result = storage_parity_type[now_valid_type];
    }
    else
        now_valid_type = 0;
        
        detect_result_last = detect_result;
    //dingzhy for debug switch function
        //psprintf(RegionValStr[REGION2], "D %x L %x V %x",detect_type,detect_result_last,now_valid_type);
    //PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
    #endif
    
	#ifdef SUPPORT_MP3_ENCODER
	if(mp3_encoder_state == test_wait_command)
	{
		check_target_device();
	}
	#endif
    if((detect_result==0)&&(storage_type==0)) 
    {
        //printf("-------- Do nothing! ------\n");
        #ifdef SUPPORT_SETUP_POPUP_MEDIA_GUI
        if(need_popup_menu!=1)
        {
            if((full_scrn==SETUP) && (need_popup_menu==2))
            {
                DISABLE_OSD();
                delay_srv_10ms(4);
                ExitSetupPage(0);
            }
            if(full_scrn==0 && cd_type_loaded!=CDUNKNOWN)
                need_popup_menu=1;
            else
                need_popup_menu=0;
        }
        #endif//#ifdef SUPPORT_SETUP_POPUP_MEDIA_GUI
        #ifdef SUPPORT_STOP_PLAY_READ_USB_CARD //caoh 2005-8-31 9:54 
                  if(media_change_flag_mark)
                 media_change_flag = 0;
        #endif
        return;
    }
    #ifdef SUPPORT_STOP_PLAY_READ_USB_CARD //caoh 2005-8-31 9:54 
     else if((media_type == MEDIA_CD)&&(!detect_result==0)) //dingzhy 05-3-22 13:32
    #else
     else if(media_type == MEDIA_CD)
    #endif
    {
        #ifdef SUPPORT_STOP_PLAY_READ_USB_CARD //caoh 2005-8-31 9:54         
            if(((play_state==VCD_STATE_STOP)||(play_state==VCD_STATE_MP3_FILELIST)||(play_state==VCD_STATE_NORMAL)||(system_state==SYSTEM_NODISC))&&(!media_change_flag))           	 
             	if(detect_type)
                 {SwitchMedia(CD2CARD);
                 }    
       #else         
            #ifdef SUPPORT_SETUP_POPUP_MEDIA_GUI
            if(need_popup_menu==1)
            {
                if(full_scrn==0 && cd_type_loaded!=CDUNKNOWN)
                {
                    need_popup_menu=2;
                    safe_srn_off();
                    show_setup_popup_media_gui();
                }
                else
                    need_popup_menu=0;
            }
            #endif//#ifdef SUPPORT_SETUP_POPUP_MEDIA_GUI
        storage_type = detect_result;
        return;
       #endif
    }    
    else if((detect_result!=0)&&((storage_type)==0))   //dingzhy 05-3-22 13:07
    //else if((detect_result!=0)&&(storage_type!=detect_result))//dingzhy for can't play as storage_parity_type[] 05-3-17 13:29
    {
        printf("-------- Card/USB Insert! ------\n");
        #ifdef EASTECH_VFD_DISP//make sure VFD's right display
        clear_old_show_time = 1; //lyc 2005-4-15
          #endif
        #ifndef SWITCH_CD_CARD_USB//liweihua 2004-6-9
        if(no_disk_cnt == 1)             //liweihua 20040324
        #endif
            system_state=SYSTEM_OPEN;   
        #ifndef SP1000_NO_DVD   
        if(play_state != VCD_STATE_OPEN) //liweihua add 2004-3-11
        #endif
            card_plug_state = USER_DO_PLUG_IN;    
        storage_type = detect_result;
     if(media_type != MEDIA_CD)//nono 2004-9-24 20:17
     {
        t_disp = 0;     //wthsin, 2004/7/6 11:39pm
        remain= 0;
     }
     


#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
        if((media_type==MEDIA_CARD) && (system_state!=SYSTEM_BROWSE))
        {
            if((source_play_mode==USB_PLAY_MODE) && (detect_type&USB_DEVICE))
            {
                #ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
                printf_w("USB is plug in when in USB state(have no card in).....\n");
                #endif
                usb_card_state = HAS_USB_AND_SWITCH_TO_USB;
                SwitchMedia(CD2CARD);
            }
            else if((source_play_mode==CARD_PLAY_MODE) && (detect_type&0x1e) && (!usb_plug_out_flag))
            {
                #ifdef DEBUG_SWITCH_DVD_USB_CARD_AVIN_DVB
                printf_w("CARD is plug in when in CARD state(have no USB in).....\n");
                #endif
                usb_card_state = HAS_CARD_AND_SWITCH_TO_CARD;
                SwitchMedia(CARD2CARD);
                setup_first_value();  ///yangli ,debug ,setup white,2006-3-9 10:47
                
            }
        }
#else
        if(media_type == MEDIA_CARD)
            SwitchMedia(CD2CARD);
#endif
            
#ifdef SUPPORT_CARDREADER_TEST
        else if ((Is_MIDI_STATE())&&(gIsMidiSelMenu))
        {
            printf("polling_storage MidiCard_GetCardFile \n");
            MidiCard_GetCardFile();
        }
#endif
    }
    //else if((storage_type!=0)&&(storage_type!=detect_result))
    else if( (storage_type!=0)&& ((storage_type & detect_type) == 0) )
    {
        printf("-------- Card/USB Remove! ------\n");

        MediaIsEmpty = MEDIA_NOT_EMPTY;//dingzhy 05-1-11 20:26

        #ifdef IR_SWITCH_CD_USB_CF_OTHER   //dingzhy for tonic 4-10-22 13:19
            now_valid_type = 0;    //for bug:move media,always show no media
        #endif

#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
        if((source_play_mode==USB_PLAY_MODE) || (source_play_mode==CARD_PLAY_MODE))
        {
            usb_card_state = USB_CARD_WAS_PLUG_OUT;
              
        }
        if(play_state == VCD_STATE_PAUSE)   /////YANGLI, 2006-2-28 13:14
        {
            ircmd_stop();
        }
        #ifdef USBCARD_PLUG_OUT_CLEAR_SETUP_PROG
        if(is_setup_prog_menu())
        {
            ircmd_stop();
               
            if(full_scrn&SETUP)
                ExitSetupPage(0);
            else
                osd_init();
                   
            cardFile.status = CARD_STATUS_NG;
        }
        #endif
#else
            
     #ifdef MP3_ONLY_STOP_TO_GUI 
            if( (play_state==VCD_STATE_MP3_FILELIST) && (media_type==MEDIA_CARD) )
            {
             ShowTitle();
             SwitchMedia(CARD2CD);      //wsf 2004-9-16 16:43
            }
     #endif 
     
        #ifdef USBCARD_PLUG_OUT_CLEAR_SETUP_PROG
        if(is_setup_prog_menu())
        {
            ircmd_stop();
               
            if(full_scrn&SETUP)
                ExitSetupPage(0);
            else
                osd_init();
                   
            cardFile.status = CARD_STATUS_NG;
        }
        #endif 
       
        if(media_type == MEDIA_CARD)
        { 
            SwitchMedia(CARD2CD);   //Maoyong 2004-8-11 22:52 marked above and add this.
        }
#ifdef SUPPORT_CARDREADER_TEST
        if ((Is_MIDI_STATE())&&(gIsMidiSelMenu))
        {
            MidiCardReadInit();
        }
#endif

#endif//end #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
        
        if(play_state != VCD_STATE_OPEN)
            card_plug_state = USER_DO_PLUG_OUT;

     #ifdef SPHE8202_CARD_STORAGE
        if(storage_type!=USB_DEVICE)    //wthsin, 2004/6/28 10:09am
         Card_power_off();      //Power Off      
     #endif//SPHE8202_CARD_STORAGE

        detect_result = 0;
        storage_type = 0;   
        t_disp = 0;     //wthsin, 2004/7/6 11:39pm
        remain= 0;
     }
      #ifdef EASTECH_VFD_DISP//make sure VFD's right display
     ShowTitle(); //lyc 05-04-21
     erase_vfd_mem();//lyc 05-04-15
     vfd_set_str(STR_OS_OPEN,""); //lyc 05-04-15
     #endif
}
#else//DIRECT_ACCESS_MEDIA
#include "atapi_if.h"
void polling_storage()
{
    #ifdef DVD_SERVO
    if((media_status == STATUS_NON) || (media_status == STATUS_DISC))
        return;
    #endif
     
    #if defined(SUPPORT_USB)                  
    if(media_status == STATUS_USB)
    {
    	if(USBEna == TRUE)    //only after USB init then polling.
    	{
            #if defined(HOST_UHCI)||defined(USB_HOST_DRV) 
            if(check_support_usb()==0)
                return;  
            uhci_slaveDetect();
            #endif
    	}
    }
    #endif

    #ifdef SPHE8202_CARD_STORAGE
    if(media_status == STATUS_CARD)
    {
        if(CardEna == TRUE)   //only after card init then polling.
            Detect_Card_Storage();

        //detect card plug out.
        if((storage_type != 0) && ((storage_type & detect_type) == 0))
    {
            //printf_w("-------------- card storage is detached! -------------\n");

        AVD_SetMediaInterrupt();
            
            //reset DMA
            regs0->reset2 |=(0x01<<9); 
            regs0->reset2 &=~(0x01<<9); 
    
            atapi_p_start_stop_unit(Immed_1,START_STOP_DO_STOP);
            system_state = SYSTEM_OPEN;
            play_state = VCD_STATE_CLOSE;
            ircmd_post_func(CMD_FUNC | CMD_FUNC_OPEN);
            storage_type = 0;
            media_type = MEDIA_NOTHING;
            t_disp = 0;
            remain = 0;
     
        if(play_state != VCD_STATE_OPEN)
            card_plug_state = USER_DO_PLUG_OUT;

        #ifdef SPHE8202_CARD_STORAGE
            if(storage_type != USB_DEVICE)
            Card_power_off();             //Power Off
        #endif//SPHE8202_CARD_STORAGE
        }
    }
    #endif

    //osd_print_storage_detect_info();
}
#endif//DIRECT_ACCESS_MEDIA


/**************************************************************************
 *                                                                        *
 *  Function Name: CardSetBrowse                                          *
 *                                                                        *
 *  Purposes:                                                             *
 *    set system to play card media                                       *
 *  Descriptions:                                                         *
 *    set system to play card media                                       *
 *  Arguments:                                                            *
 *          NONE                                                          *
 *  Returns:     NONE                                                     *
 *                                                                        *
 *  See also:    NONE                                                     *
 *                                                                        *
 **************************************************************************/
//commone function to make system play card media now. Maoyong 2004.05.17
void CardSetBrowse(void)
{
     full_scrn = 0;  //Maoyong 2004-8-11 23:02 for clear setup menu, must place before ClearOsdMsg
     ClearOsdMsg(0);
     t_disp = 0;
     #ifdef SUPPORT_MULTI_PARTITION//liweihua 2004-10-25 8:56
     browser = HddCardBrowse;
     #else
     browser = read_iso9660;
     #endif
     cd_type_loaded=CDROM;
     cd_type=CDROM;
     play_state=VCD_STATE_CLOSE;
     Mp3ReadFinish = 0;//liweihua 2004-5-13
     memset(pFsJpeg, 0, sizeof(FSJPEGDATA));//liweihua add 2004-5-8 9:11
     system_state=SYSTEM_BROWSE;
     sys_cmd=CMD_FUNC|CMD_FUNC_CLOSE;
     media_type = MEDIA_CARD;
     
     //customized osd information for card reading
     //Maoyong 2004.05.25 build funtions in ircmd.card.c, need to make osd display until
     //read all card files for some cards has too many files and take long times
     show_card_reading_osd(SHOW_MEDIA);
}
/**************************************************************************
 *                                                                        *
 *  Function Name: PMP_CF_Card_IsPlugIn                                   *
 *                                                                        *
 *  Purposes:                                                             *
 *    Detect if the PMP'CF is pluged                                      *
 *  Descriptions:                                                         *
 *    Detect if the PMP'CF is pluged                                      *
 *  Arguments:                                                            *
 *          NONE                                                          *
 *  Returns:                                                              *
 *          0: nothing  2: CF plug in  -2: CF plug out                    *
 *  See also:    NONE                                                     *
 *                                                                        *
 **************************************************************************/
#ifdef CARD_SETUP_TYPE_5
UINT8 sense_check_result=0;//liweihua add 2004-11-30
int PMP_CF_Card_IsPlugIn()
{
    UINT8 cf_card_result=0;
    UINT8 check_result;
    
    check_result = sense_check_result;
    sense_check_result = GPIO_I_GET(CF_INS_SENSE);
    
    if(check_result != sense_check_result)
    {
        if(!sense_check_result)
        {
            printf("CF plug in!\n");
            return 2;
        }
        else
        {
            printf("CF plug out!\n");
            return -2;
        }   
    }     
    if(!sense_check_result)  cf_card_result=1;
     //printf("cf_card_result =%x!\n",cf_card_result);
     return cf_card_result;
}       
#endif// CARD_SETUP_TYPE_5

#endif //#if defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)

/**************************************************************************
 *                                                                        *
 *  Function Name: pc_usb_access_mode                                     *
 *                                                                        *
 *  Purposes:                                                             *
 *    Set system to  PC USB MODE                                          *
 *  Descriptions:                                                         *
 *    when connect computer with usb, Set system to  PC USB MODE          *
 *  Arguments:                                                            *
 *          NONE                                                          *
 *  Returns:     NONE                                                     *
 *                                                                        *
 *  See also:    NONE                                                     *
 *                                                                        *
 **************************************************************************/
#ifdef PMP_DVD 
void pc_usb_access_mode()
{
   delay_1ms(50); //Continous 50ms Detect "USB INSERT"
   if(!GPIO_I_GET(PC_USB_CONNECT_PIN)) return;
   watchdog_onoff(0);    // disable watchdog 
   psprintf(RegionValStr[REGION1], "PC USB MODE");
   PrintOsdMsg(STR_OS_SPACE, REGION1, 0, 1); 
  #ifdef PMP_PCB_VER_C 
   regs0->fm_gpio_mode = 9; //8202 IDE PIN => Hi-Z
   UINT16 temp;
   temp=regs0->gpio_mode_B;
   regs0->gpio_mode_B=0;
  #endif //#ifdef PMP_PCB_VER_C
   GPIO_O_SET(IDE_BUS_SWITCH_CONTROL_PIN,0);
  #ifdef PMP_PCB_VER_C 
   GPIO_O_SET(USB_DEVICE_CHIP_POWER_PIN,0);
   delay_1ms(300); 
  #endif //#ifdef PMP_PCB_VER_C
   GPIO_O_SET(USB_DEVICE_CHIP_POWER_PIN,1);
   GPIO_O_SET(CARD_POWER_RESET,0); 
   
   while(GPIO_I_GET(PC_USB_CONNECT_PIN));
   
   GPIO_O_SET(IDE_BUS_SWITCH_CONTROL_PIN,1);
  #ifdef PMP_PCB_VER_B 
   GPIO_O_SET(USB_DEVICE_CHIP_POWER_PIN,0);
  #else //PMP_PCB_VER_C
   regs0->gpio_mode_B=temp;
  #endif //#ifdef PMP_PCB_VER_B
   watchdog_onoff(1);      // enable watchdog
   watchdog_renew(0xffff);//reset watchdog
   ClearOsdMsg(1); 
   system_state= SYSTEM_OPEN;
   ircmd_stop();
   ircmd_return();
}
/**************************************************************************
 *                                                                        *
 *  Function Name: PMP_PC_Usb_PlugInOut                                   *
 *                                                                        *
 *  Purposes:                                                             *
 *    detect if usb connect to computer                                   *
 *  Descriptions:                                                         *
 *    detect if usb connect to computer                                   *
 *  Arguments:                                                            *
 *          NONE                                                          *
 *  Returns:     NONE                                                     *
 *                                                                        *
 *  See also:    NONE                                                     *
 *                                                                        *
 **************************************************************************/
UINT8 pc_usb_vcc_flag=0;
void PMP_PC_Usb_PlugInOut()
{
   if(pc_usb_vcc_flag==0)
   {
     if(GPIO_I_GET(PC_USB_CONNECT_PIN))
     {
        #ifdef PMP_UI//liweihua 2005-1-17
        pmpkey_return();
        #endif
        pc_usb_access_mode();
        pc_usb_vcc_flag=1;
     }    
   } 
   else //(pc_usb_vcc_flag==0)
   {
     if(!GPIO_I_GET(PC_USB_CONNECT_PIN))
     {
        pc_usb_vcc_flag=0;
     }
   }  
}  
#endif //#ifdef PMP_DVD 

#ifdef FIX_STATE_CHANE_NOT_READ_USB  
void force_detached();
void force_detached()
{
		SLAVE_ENUMERATED = FALSE ;
		detect_type &= (~USB_DEVICE);
        storage_type &= (~USB_DEVICE);
}
#endif// end=>  #ifdef FIX_STATE_CHANE_NOT_READ_USB 



