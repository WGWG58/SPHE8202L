
#include "pic_mainproc.h"
#include "vpp_if.h"


//extern void set_vpp_disp_window(UINT32,UINT32,UINT32,UINT32);
extern void setup_SetTV_format(UINT8);

#ifdef SUPPORT_MP4_SUBTITLE
extern int IS_EXT_SUP_ACTIVATED(void);
#endif

/*
*  for HD 720P output
*
*  robert.chang, 2006-07-13
*/
void str_os_hd_720p(void)
{
    int old_mode=p_scan;
    int old_tv_resolution = GET_TV_RESOLUTION();
    
    SET_TV_RESOLUTION(HD_720);

    if(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)        
    {            
        jpg_redecode_byTvResolution();
    }    
            
    p_scan = 1;
    // When HD,  if tv_format is MODE_NTSC, MODE_PAL60, and MODE_AUTO, will be change to STR_OS_NTSC.                
    if( (tv_format==MODE_NTSC) || (tv_format==MODE_PAL60) ||(tv_format==MODE_AUTO) ) {
        sp8200tv_set_hd_mode(HD_720P_F60, 1);
        set_vpp_disp_window(0,0,1280,720);
        tv_format = MODE_NTSC;
        setup_SetTV_format(STR_OS_NTSC);
        update_tv_format_sel();
    }                
    else if(tv_format == MODE_PAL) {
        sp8200tv_set_hd_mode(HD_720P_F50, 1);
        set_vpp_disp_window(0,0,1280,720);                
    }

    if((p_scan!=old_mode) || (old_tv_resolution != GET_TV_RESOLUTION() ))  
    {
        if (full_scrn & SETUP)
        {            
            osd_init_setup();

#ifdef SETUP_TAB
            ShowSetupPage(2);
#else
            ShowSetupPage();
#endif
        }else //if(srv_on)
        {            

            //initializing infomation displaying OSD
#ifdef SUPPORT_MP4_SUBTITLE
                if(IS_EXT_SUP_ACTIVATED()) {  // if support subtitle, then call osd_init_OSDSRT().
                    osd_init_OSDSRT();
                }        
                else
#endif
                {
#ifdef SUPPORT_OSDID3
                    if(Is_MP3_STATE())
                    {
                        osd_init_OSDID3();
                        show_id3();
                    } else
#endif
                    {
                        osd_init();               
                    }
            }
        
        }
    }
    
#ifdef SUPPORT_SW_OSD_SCALING            
#if 0           
            char hd_warrning[] = "    Do you reserve        this setting?";
            char capture_txt[] = "HD OUTPUT WARNNING";
            UINT8 ui_res  =  Warning_box( 0, capture_txt, hd_warrning, MB_YESNO, 1, 10 );
            if(ui_res == IDNO) {
                SETUP_HD_OUTPUT = 2;
                sp8200tv_setup_custom_output(TV_OUT_YUVRGB);
            }
#endif         
#endif
//            else if(ui_res == IDYES) {
//                SET_TV_RESOLUTION(HD_720);
//            }     
//            printf_w(__FUNCTION__  "  The warrning mesg is %d SETUP_HD_OUTPUT:%d \n", ui_res, SETUP_HD_OUTPUT);

}

/*
*  for HD 1080i output
*
*  robert.chang, 2006-07-13
*/
void str_os_hd_1080i(void)
{
    int old_mode=p_scan;
    int old_tv_resolution = GET_TV_RESOLUTION();

    SET_TV_RESOLUTION(HD_1080);
    
    if(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)        
    {
        jpg_redecode_byTvResolution();        
    }    
            
    p_scan = 0;
    // When HD,  if tv_format is MODE_NTSC, MODE_PAL60, and MODE_AUTO, will be change to STR_OS_NTSC.
    if( (tv_format==MODE_NTSC) || (tv_format==MODE_PAL60) ||(tv_format==MODE_AUTO) ) {
        sp8200tv_set_hd_mode(HD_1080I_F60, 1);
        set_vpp_disp_window(0,0,1920,1080);
        tv_format = MODE_NTSC;
        setup_SetTV_format(STR_OS_NTSC);
        update_tv_format_sel();        
    }                
    else if(tv_format == MODE_PAL) {
        sp8200tv_set_hd_mode(HD_1080I_F50, 1);
        set_vpp_disp_window(0,0,1920,1080);                
    }

    if((p_scan!=old_mode) || (old_tv_resolution != GET_TV_RESOLUTION() ))
    {
        if (full_scrn & SETUP)
        {            
            osd_init_setup();

#ifdef SETUP_TAB
            ShowSetupPage(2);
#else
            ShowSetupPage();
#endif
        }else //if(srv_on)
        {            

            //initializing infomation displaying OSD
#ifdef SUPPORT_MP4_SUBTITLE
                if(IS_EXT_SUP_ACTIVATED()) {  // if support subtitle, then call osd_init_OSDSRT().
                    osd_init_OSDSRT();
                }        
                else
#endif
                {
#ifdef SUPPORT_OSDID3
                    if(Is_MP3_STATE())
                    {
                        osd_init_OSDID3();
                        show_id3();
                    } else
#endif
                    {
                        osd_init();               
                    }
            }

        }
    }    
#ifdef SUPPORT_SW_OSD_SCALING              
#if 0            
            char hd_warrning[] = "    Do you reserve        this setting?";
            char capture_txt[] = "HD OUTPUT WARNNING";
            UINT8 ui_res  =  Warning_box( 0, capture_txt, hd_warrning, MB_YESNO, 1, 10 );
            if(ui_res == IDNO) {
                SETUP_HD_OUTPUT = 2;
                sp8200tv_setup_custom_output(TV_OUT_YUVRGB);
            }
#endif          
#endif
//            else if(ui_res == IDYES) {
//                SET_TV_RESOLUTION(HD_1080);
//            }     
//            printf_w(__FUNCTION__  "  The warrning mesg is %d SETUP_HD_OUTPUT:%d \n", ui_res, SETUP_HD_OUTPUT);

}

