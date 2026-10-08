/***************************************************************
 *
 * File Name :  USBGUI.c
 * 
 * Discription:
 *     Provide functions when executing UDisk operations 
 *     
 *
 * Creator:  liweihua
 * Date   :  2003-10-30 21:08
 *
 **************************************************************/
#ifdef SUPPORT_USB

#include "USBfs.h"
extern void USBJudgeFAT(void);
extern USB_INFO   USBInfo;
extern UINT32	USBZeroFAT_cnt; 
void cd2UDisk(void)
{
    full_scrn &= (~PERIPHERAL);//for release the IR
    osd_init();
    //atapi_close_tray(0);

    read_USB_flag = 1;
    flag_U=1;
    flag_cd=0;
    media_type=MEDIA_USB;
    ircmd_post_func(CMD_FUNC | CMD_FUNC_STOP);

}

void UDisk2cd(void)
{
    full_scrn &= (~PERIPHERAL);//for release the IR
    osd_init();
    		
    read_USB_flag=0;
    flag_U=0;															   //xulf
    flag_cd=1;
    media_type=MEDIA_CD;
    ircmd_post_func(CMD_FUNC | CMD_FUNC_STOP);
    bDiscType=CDUNKNOWN;
    sys_cmd=CMD_FUNC_PLAY;
}

int UDisk_delete(void)
{
    if(!USBIsPlugIn()){
        Message_Show(ERROR_MESSAGE);
        show_switch();
    }
    else{
        sign_PFun=PFUN_DELETE;//delete data
        Message_Show(PFUN_DELETING);
        if(USBSchedule(0)==-1){
            Message_Show(P_SPACEEMPTY);
            UDisk2cd();
            return -1;
        }
        else{
            Message_Show(PFUN_DELETE);
        }
    }
}

void UDisk_format(void)
{
    if(!USBIsPlugIn()){//very important!!!
        Message_Show(ERROR_MESSAGE);
        show_switch();
    }
    else{
        sign_PFun=PFUN_FORMAT;
        USBSchedule(0);
        Message_Show(PFUN_FORMAT);
    }
}

void rename_Udiskfile(void)
{
    if(!USBIsPlugIn()){//very important!!!
        Message_Show(ERROR_MESSAGE);
        show_switch();
    }
    else{   
        sign_PFun=PFUN_RENAME;
        USBSchedule(0);
        Message_Show(PFUN_RENAME);
        full_scrn &= (~PERIPHERAL);//for release the IR
        osd_init();    
        cd2UDisk(); 
    }
}
void UDisk_copy(BYTE copymod)
{
    int result;
    if(USBIsPlugIn()==0){
        Message_Show(ERROR_MESSAGE);
        show_switch();
    }
    else{
        sign_PFun=PFUN_WRITE;
        if(pFsJpeg->gifsFuncBtn == FS_FUNC_MP3){
            AVD_SetMediaInterrupt();
            Message_Show(PFUN_COPYING); 
            osd_DrawRegionString(20, 1, " 0%", 7, 0, 2);             
        }
        else if(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG){
            UINT32 lba;
            Message_Show(PFUN_COPYING);
        
            switch(copymod){
                case COPY_ROOTDIR:
                    result=USBSchedule(COPY_ROOTDIR);
                    if(result == -1){
                	    Message_Show(P_SPACEFULL);
                    }
                    else if(result == -3){
                        Message_Show(ERROR_MESSAGE);
                    }
                    else{
                        Message_Show(PFUN_WRITE);
                    }
                    break;
                case COPY_EXISTING:
                    result=USBSchedule(COPY_EXISTING);
                    if(result == -1){
                        Message_Show(P_SPACEFULL);
                    }
                    else if(result == -3){
                        Message_Show(ERROR_MESSAGE);
                    }
                    else if(result == -2){
                        Message_Show(P_NOMATCH);
                    }
                    else{
                        Message_Show(PFUN_WRITE);
                    }    
                    break;
                case COPY_NEWDIR:
                    result=USBSchedule(COPY_NEWDIR);
                    if(result == -1){
                	    Message_Show(P_SPACEFULL);
                    }
                    else if(result == -3){
                        Message_Show(ERROR_MESSAGE);
                    }
                    else{
                        Message_Show(PFUN_WRITE);
                    }
                    break; 
            }       
            full_scrn &= (~PERIPHERAL);//for release the IR
    	    osd_init(); 
        }  
    }
}

#endif	//#ifdef	SUPPORT_USB