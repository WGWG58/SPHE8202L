/***********************************************************************
File name£º  ircmd_usboperation.c
Creator:     sunzhh creat 2004-10-17
Description: to show USB&CARD Fat write GUI
Update:      sunzhh 2004-11-24 
************************************************************************/
#if defined(FAT_Write_UI)   //sunzhh modified 20041121
#include "cardfs.h"
extern CARD_FILE    cardFile;//liweihua 2004-4-5
extern CARD_INFO    cardP;
extern void show_switch(BYTE Select_Media); 
extern void switch_up(void);
extern void switch_left(void);
extern void switch_right(void);
extern void switch_down(void);
extern void switch_select(void);
BYTE Select_Media;
BYTE pressnum_flag;
BYTE InfoGui_flag;
#endif

#ifdef FILE_MODE_WRITE
#include "fsgui.h"

extern const char *FileModeWarning[];
extern void  DrawFileIconX(int x, int y, int type, int mono);
extern void  Draw_FileMode_Menu(void);
extern void  MediaItem_List(UINT16,BYTE);
extern void ShowWarning(const char *s);
#if defined (NEW_MP3_GUI) || defined (FS_BMP_GUI) || defined(INDIGO_STYLE_FSGUI)
extern int    old_ControlArea; //record last ControlArea.
extern int    HL_show;//record HL .
#endif
#endif

void ircmd_media_control(void)
{
#ifdef NEW_STYLE_SETUP
    if ( Is_JPEG_SlideMode()
    #ifdef SUPPORT_FILE_SYSTEM_MODE
    ||(IsOtherStatePlayMode()) 
    #endif
    ) 
    {
        invalid_key();
        return;
    }
#endif
    if(play_state == VCD_STATE_OPEN)
        return;
#ifdef FAT_Write_UI       
    if (full_scrn & PERIPHERAL)
        {
            full_scrn &= (~PERIPHERAL);
            #ifdef CD_PLAYER 
                if(cd_type_loaded==CDDA)
                {
                    osd_init_cdplayer();
                }else               
                    osd_init();
            #else
                osd_init();
            #endif

            pressnum_flag=0;

            #ifdef SPHE8202_ALL_TYPE_CARD_WRITE
            card_browse_sign = 1;	//dingzhy
            #endif
        }
        else
        {
            if((full_scrn & MARK)||(full_scrn & GOTO))
            {
                invalid_key();
                return;
            }
            full_scrn |= PERIPHERAL;               
            #if defined(SUPPORT_FILE_SYSTEM_MODE)||defined(SUPPORT_MP4)
			if(IsOtherStatePlayMode())            
                ircmd_return();
            #endif   
            
            if ((pFsJpeg->gbfsSlide)&& (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG))
            {
  
                ircmd_return();
                FSChangeGraphMode();                     
                FS_Return2Menu();

            }             
            #if defined(STORAGE_WRITE_GUI)||defined(CARD_WRITE_GUI)               
            if((((detect_type&USB_DEVICE)&&(detect_type&0x1E))   //||((detect_type&CF_CARD_DEVICE!=0)&&(detect_type&0x1C!=0)))&&(media_type == MEDIA_CD))
            #ifdef CARD_SETUP_TYPE_3
                ||((detect_type&CF_CARD_DEVICE)&&(detect_type&0x1C))
            #endif
                )&&(media_type != MEDIA_CARD)) 
            {
                show_mediaswitch();
            }
            else    
            #endif
                show_switch(Select_Media);
                //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 9:54
            SetFullscrnCmdFuncPtr( switch_up, switch_down, switch_left,
                                       switch_right, switch_select);
                                       
            }
#endif

#ifdef FILE_MODE_WRITE   
    pFsJpeg->gifsState  =  FS_STATE_MEDIA;
    printf("================It is drawing =======================\n");
    Draw_FileMode_Menu();
    BYTE srce=0;
    BYTE dest=1;
    MediaItem_List(FS_DIRLIST_XSTART,srce);
    MediaItem_List(fsArea[FS_AREA_FILEITEM].xStart,dest);    
    ShowWarning("PLEASE SELECT TO ENTER");
//    HL_show = pFsJpeg->file_current_in_page;

        int Res=0;
//    BYTE bHasShowGUI = 0;   //clear fsGUI display flag

        if ( (play_state != VCD_STATE_OPEN) && (play_state != VCD_STATE_POWER) )//skip FSNav_MainLoop when user tray-out, Jeff 20020619
        {
            if ( Mp3ReadFinish || (Res >= 0) )
            {
                if (pFsJpeg->iso9660_file_cnt)
                {
                    Mp3ReadFinish   = 1;
                    disp_time = 0;
                    show_time();
    
                    //show_fat_dir_file_info();
                int iResLoop = 1;
            
                do
                {
                    polling();
                    //iResLoop=FileMode_MainLoop();
                    if(Mp3ReadFinish == 0)
                    {
                        iResLoop=0; 
                    }
                }while (iResLoop == 1);  

                    stop_init(); //Jeff 20010919
                }
                else
                {
                    ClearCommand();
                    FSGUI_UpdateInfoArea("");
                    Mp3ReadFinish   = 1;
                    play_state = VCD_STATE_STOP;
                }
            }
        }    
#endif
}









