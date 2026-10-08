/*
** FILE
** vfd.c
**
** DESCRIPTION
** handle VFD functions.
*/
#include "user_init.h"
#include "config.h"
#include "global.h"
#include "memmap.h"
#include "sio.h"
//#include "epp.h"

//#include "fastmath.h"
//#include "auctrl.h"
//#include "user_init.h"
//#include "vfd.h"
#include "vfdfunc.h"
//#include "vfd_7seg.h"//kenny mark 2001/10/23
//#include "vfd_p.h"//kenny mark 2001/10/23
#include "ircode.h"
#include "ircmd.h"
#include "func.h"
//#include "sig.h"
//#include "fs96602.h"//kenny mark 2001/10/23
#include "osd.h"

#include "avd.h"                                //zyf 2000/11/22
//#include "vfd_prg.h"//kenny mark 2001/10/23
//#include "reverse.h"

#include "gpio.h"
#include "iop.h"
#include "cd.h"

#ifdef USE_VFDPORT_TRANDATA         //add by linrc 2004-3-24 21:56 for minidvd receive
    #include "8200_51MCU.c"     //program introduce in the /IR_VFD/8200_51MCU.c file
#endif    

UINT32  get_rtc_val();

//#ifdef P9c9_Panel //jacky 2003/10/23 07:35PM
#ifdef USE_VFD_CONTROL_P9C9_LED_ON_OFF      //gerry,2004-1-30 18:11
int led_flash_interval=0;
int led_flash_time=0;
#endif 

//#define     VFD_DBG     1
//#define VFD_KEY_TEST
#ifdef  BBK_DVD   //fengjl add  4-2-3 20:22
extern tv_output_vfd_time;  
#endif



static UINT16  counter, index;
BYTE    vfd_state = 0;
extern UINT32 save_srn_start_t;

#include "vfd_mod.c"

#ifdef HT1621_PANNEL//nono 4-5-9 23:56
const BYTE vfd_keycode[]={};
#endif//HT1621_PANNEL

#ifdef NEW_JPEG
extern BYTE bJpgVFDPause;
#else
#ifndef SHARE_NAV_VAR
extern BYTE bJpgVFDPause;               //Jeff 20020523
#else
#define bJpgVFDPause (pFsJpeg->bJpgVFDPause)
#endif
#endif

extern UINT16 Is_JPEG_SlideMode(void);

#if defined(SLEEP_WHEN_POWER_ON)&&defined(TONIC_DVD)//20040206
extern int power_on_flag;   //zhg 2004-1-4 15:46
#endif


#ifdef TWO_FUN_IN_ONE_VFD_KEY
UINT32 keycode_to_num(UINT32 key_data)
{
    UINT32 temp;
    UINT8   i;
    for(i = 0; i < 24; i++)
    {
        temp = 0x01 << i;
        if(key_data & temp)
        {
            if (key_data > temp) 
            {
                return 0;
            }
            else
            {
                key_data = i + 1;
                break;
            }
        }
    }
    return key_data; 
}
#endif //TWO_FUN_IN_ONE_VFD_KEY

#ifdef TEST_VFD                                 //shawn add at 910131

UINT8   SC_1 = 15;
UINT8   COMMAND_MODE = 2;

void update_vfd_dot_inc(void)       //shawn add at 910131
{
    if(SC_1 < 40)
        SC_1++;
    printf("\n SC_1(BYTE_INC)=%d\n\n", SC_1);
    
#ifdef VFD2OSD_DBG_TXD                  //nono 2-8-9 14:39
    psprintf(RegionValStr[REGION1], "SC_1 BYTE_INC: %d", SC_1);
    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
#endif
}


void update_vfd_dot_dec(void)       //shawn add at 910131
{
    UINT8   a;
    
    for(a = SC_1; a <= 25; a++)
        vfd_mem[a] = 0x00;
    if(SC_1 > 0)
        SC_1--;
    printf("\n SC_1(BYTE_DEC)=%d\n\n", SC_1);
    
#ifdef VFD2OSD_DBG_TXD                  //nono 2-8-9 14:39
    psprintf(RegionValStr[REGION1], "SC_1 BYTE_DEC: %d", SC_1);
    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
#endif
}

void update_vfd_mod_inc(void)       //shawn add at 910131
{
    //counter++;
    
    if(COMMAND_MODE < 16)
        COMMAND_MODE++;
    
    printf("\n COMMAND_MODE(INC)=%d\n\n", COMMAND_MODE);
    
#ifdef VFD2OSD_DBG_TXD                  //nono 2-8-9 14:40
    psprintf(RegionValStr[REGION3], "COMMAND_MODE INC: %d", COMMAND_MODE);
    PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
    
#endif
    
    reset_vfd();
}

void update_vfd_mod_dec(void)       //shawn add at 910131
{
    //counter--;
    
    if(COMMAND_MODE > 0)
        COMMAND_MODE--;
    printf("\n COMMAND_MODE(DEC)=%d\n\n", COMMAND_MODE);
    
#ifdef VFD2OSD_DBG_TXD                  //nono 2-8-9 14:40
    psprintf(RegionValStr[REGION1], "COMMAND_MODE DEC: %d", COMMAND_MODE);
    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
#endif
    
    reset_vfd();
}

void update_vfd_inc(void)               //shawn modify at 910131
{
    counter++;
}

void update_vfd_dec(void)               //shawn modify at 910131
{
    counter--;
}

#endif //TEST_VFD

#ifdef SHOW_VOL_ON_VFD //huziqin 2004-4-29.if setting channel volume.
extern  BYTE subvol_time_out;
#endif

#ifdef SUPPORT_VFD//nono 20031124
void update_vfd_data(void)
{

#ifdef VFD_SHOW_LOAD_TOGGLE//nono 2003-10-17 18:23      
static BYTE load_toggle_flag;
#endif//#ifdef VFD_SHOW_LOAD_TOGGLE

#ifdef SHOW_VOL_ON_VFD
    if(subvol_time_out)
        {
        show_amp_vol_on_vfd();
        return;
        }
#endif


#ifdef TEST_VFD
    UINT8   by, bit, i;                     //,j;            //shawn modify at 910131
    
    
    index++;
    if(index % 10)
        return;
    
    
    
    by = counter / 8;
    bit = counter % 8;
    
    #ifdef YADAI_PT6554_PANNEL
        for(i = 0; i < SC_1; i++)
        {
            if((i==5)||(i==11)||(i==17)||(i==23))
            {
                vfd_mem[i] = 0x00;
            }
            else
            {           
        vfd_mem[i] = 0xff;
            }
        }
    #else
    
        for(i = 0; i < SC_1; i++)               
        vfd_mem[i] = 0xff;  
    
    #endif  
    
    
    vfd_mem[by] = ~(0x01 << bit);
    
    
    //vfd_set_str(STR_OS_CLOSE,"");
    
    printf("BYTE:%d BIT:%d\n", by, bit);
    //psprintf(linebuf,"BYTE:%d BIT:%d",by,bit);
    
#ifdef VFD2OSD_DBG_TXD                  //nono 2-8-9 14:40
    psprintf(RegionValStr[REGION1], "BYTE:%d BIT:%d", by, bit);
    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
#endif
    //ShowOsdMsg(linebuf,0);
    return;
#endif
    
#ifdef BBK_DV961_DVD//zhaoyanhua add to show VFD Message for VGA/INTERLACE/P_SCAN  3-11-27 9:50
    if(tv_output_vfd_time != 0)
    {
        tv_output_vfd_time--; 
        switch(tv_out_id)
        {
            case INTERLACE:
                vfd_set_str(0,"1-    ");
                break;
            case PC_VGA:
                vfd_set_str(0,"2-    ");
                break;
            case P_SCAN:
                vfd_set_str(0,"3-    ");
                break;
        
        }
        
        //turn off ":"(min)":"(sec)
        vfd_reset_dot(VFD_DOT_MINSEC);
        vfd_reset_dot(VFD_DOT_MIN);
        return;
    }
#endif  
    
    
    if(play_state != VCD_STATE_TUNER)
    {
        //===========================================
#ifdef HUAJIA_DVD
#define INTV_TM 20
#else
#define INTV_TM 10
#endif  
        counter++;
        
        
        if(adv_search_time > 0)
        {
            if(counter % (INTV_TM / adv_search_time))
                return;
        }
        else if(adv_search_time < 0)
        {
            if(counter % (INTV_TM / (-adv_search_time)))
                return;
        }
        else if(video_slow)
        {
            {
                UINT8   rate = (UINT8) video_slow;
                
                if(counter % (INTV_TM * rate))
                    return;
            }
        }
        else if(play_state != VCD_STATE_CLOSE)
        {
                if(counter % INTV_TM)

                    return;
        }
        else if(counter % (INTV_TM / 2))
            return;
        counter = 0;
    }
    
    /********************************************************/
    // try the function by chichang 2001 6/5
    /********************************************************/
    /*
    vfd_mem[36]=0xff;
    vfd_mem[37]=0xff;
    
      vfd_set_dot(VFD_DOT_PLAY);
      vfd_set_dot(vfd_disc[index]);
      //vfd_set_str(0,"WELCOME");
      
        
          if(index>=11)
          {
          index=0;
          }else
          index++;
          vfd_reset_dot(vfd_disc[index]);
    */
    //===========================================================//
    // process the vfd display of volume and tone   2002-07-03 freyman
    /************************************************************/
#ifdef VFD_VOLUME_DISPLAY
    //  if(vfd_mode_state != DVD_NORMAL_MODE)
    if(timeout_vfd != 0)
        return;
#endif
    /************************************************************/
    // start the vfd program
    /************************************************************/
    #ifdef VOL_LED
    write_vfd_led(0xff);
    #endif

    #ifdef GBM_USE_VFD_CONTROL_LED      //GERRY,2004/2/12 04:14下午
//      write_vfd_led(0xff);
    #ifdef GBM_USE_VFD_CONTROL_P_SCAN_LED
        if(p_scan==0)
        write_vfd_led(0xf);     //3 led are all off,2004-2-19 21:03
        else
        write_vfd_led(0xe);     //only p-san led on,2004-2-19 21:03
    #else//GBM_USE_VFD_CONTROL_P_SCAN_LED
    write_vfd_led(0xff);
    #endif//GBM_USE_VFD_CONTROL_P_SCAN_LED
    #endif//GBM_USE_VFD_CONTROL_LED

    switch (play_state)
    {
    case VCD_STATE_POWER:           //power off
        
#ifdef N701_PANNEL
        erase_vfd_mem();
        vfd_set_welcome(index);
        index = index + 1;
        if(index >= 18)
        {
            index = 18;
        }
        
#else
        
        // erase_vfd_mem();
        // index=index+1;
        
        index = vfd_set_power_state(index);
//#if defined(TP6311_DRIVER_VFD) && defined(SUPPROT_APOGEE_AMP)//xyy 2003-11-6 10:52
#ifdef AMPVOL_VFD_DISP  //xyy 2004-3-11 
    
    if(full_scrn == APOGEEAMPVOL)
    {
        vfd_set_ampvol();  
        return;
    }
#endif  

#endif
        
        return;
        
    case VCD_STATE_IDLE:                //no disc
        
#ifdef N701_PANNEL
        erase_vfd_mem();
        vfd_set_welcome(index);
        index = index + 1;
        if(index >= 18)
        {
            index = 18;
        }
        
#else
        
        if(system_state == SYSTEM_NODISC)
            {
            index = vfd_set_no_disc_state(index);
//#ifdef P9c9_Panel //Jacky Led light off when NODISC 2003/10/24 11:27AM
#ifdef USE_VFD_CONTROL_P9C9_LED_ON_OFF          //gerry,2004-1-30 18:14
            write_vfd_led(0xff);
#endif
        }
        else
            index = vfd_set_idle_state(index);
#endif
        return;
    case VCD_STATE_CLOSE:

#ifdef VFD_SHOW_LOAD_TOGGLE
        if(load_toggle_flag<1)
        {
            write_vfd_led(0xf);
            erase_vfd_mem();
        }
        //vfd_set_str(STR_OS_CLOSE,0,0,"");
        //return;
        else
        {
            write_vfd_led(0);
        index = vfd_set_close_state(index);
        }
        
        load_toggle_flag++;
        if(load_toggle_flag==2) load_toggle_flag=0;
#else//#ifdef VFD_SHOW_LOAD_TOGGLE
        index = vfd_set_close_state(index);
#endif//#ifdef VFD_SHOW_LOAD_TOGGLE

        {
//#ifdef P9c9_Panel //Jacky for p9c9 panel
#ifdef USE_VFD_CONTROL_P9C9_LED_ON_OFF          //gerry,2004-1-30 18:14
               extern int led_flash_interval;
         if((led_flash_interval%5)==0)      
            write_vfd_led(0xff);
         else
            write_vfd_led(0x00);
          led_flash_interval++;
#endif //Jacky end
         }
        return;
        
    case VCD_STATE_READTOC:     //chk disc type loading...
        
#ifdef N701_PANNEL
        erase_vfd_mem();
        //vfd_set_str(0,"WELCOME");
        
        //printf("===== set_welcome=======\n");
        //vfd_set_dot(VFD_DOT_ANGLE);
        vfd_set_welcome(index);
        index = index + 1;
        if(index >= 18)
        {
            index = 18;
        }
#else
        //erase_vfd_mem();
        //index=index+1;
#ifdef VFD_SHOW_LOAD_TOGGLE     
        if(load_toggle_flag<1)
        {
            write_vfd_led(0xf);
            erase_vfd_mem();
        }

        else
        {
            write_vfd_led(0);
            index = vfd_set_toc_state(index);
        }
        
        load_toggle_flag++;
        if(load_toggle_flag==2) load_toggle_flag=0;
#else//#ifdef VFD_SHOW_LOAD_TOGGLE
        index = vfd_set_toc_state(index);
#endif//#ifdef VFD_SHOW_LOAD_TOGGLE     
        
#endif
        return;
        
    case VCD_STATE_OPEN:
        //erase_vfd_mem();
        //vfd_set_str(STR_OS_OPEN,0,0,"");
        //Maoyong 2004.05.26 avoid vfd display error when use CMD_FUNC_OPEN to break mainloop
        if(CDOpened())
        index = vfd_set_open_state(index);
        {
//#ifdef P9c9_Panel //Jacky for p9c9 panel
#ifdef USE_VFD_CONTROL_P9C9_LED_ON_OFF          //gerry,2004-1-30 18:15
          extern int led_flash_time;
          if((led_flash_time%5)==0)     
            write_vfd_led(0xff);
          else
            write_vfd_led(0x00);
          led_flash_time++;
#endif//Jacky end
        }
        return;
        
        /*
        
          case VCD_STATE_GAME:
          //vfd_reset_dot(VFD_DOT_PLAY);
          index=vfd_set_game_state(index);
        break;                  */
        
        //case VCD_STATE_STEP:
    case VCD_STATE_PAUSE:           //pause
        //vfd_reset_dot(VFD_DOT_PLAY);
        index = vfd_set_pause_state(index);
        
#ifdef GBM_USE_VFD_CONTROL_LED          //GERRY,2004/2/12 04:13下午
//      write_vfd_led(0xe);
    #ifdef GBM_USE_VFD_CONTROL_P_SCAN_LED
        if(p_scan==0)
        write_vfd_led(0xf);     //3 led are all off,2004-2-19 21:03
        else
        write_vfd_led(0xe);     //only p-san led on,2004-2-19 21:03
    #else//GBM_USE_VFD_CONTROL_P_SCAN_LED
        write_vfd_led(0xe);
    #endif//GBM_USE_VFD_CONTROL_P_SCAN_LED
#endif//GBM_USE_VFD_CONTROL_LED
        
        break;
        
    case VCD_STATE_MP3_FILELIST:    //Jeff 20010718
        //vfd_set_dot(VFD_DOT_PLAY);
        index = vfd_set_mp3_state(index);
        
        break;
        
    case VCD_STATE_STOP:
        
        //vfd_reset_dot(VFD_DOT_PLAY);
        index = vfd_set_stop_state(index);
        
        break;
        
    default:
        
#ifdef USE_VFD_CONTROL_P9C9_LED_ON_OFF          //gerry,2004-1-30 18:14
            write_vfd_led(0xff);
#endif
        
#ifdef GBM_USE_VFD_CONTROL_LED          //gerry,2004/2/12 04:13下午
//      write_vfd_led(0xd);         
    #ifdef GBM_USE_VFD_CONTROL_P_SCAN_LED
        if(p_scan==0)
        write_vfd_led(0xd);     //only play led on,2004-2-19 21:03
        else
        write_vfd_led(0xc);     //play & p-san led on,2004-2-19 21:03
    #else//GBM_USE_VFD_CONTROL_P_SCAN_LED
        write_vfd_led(0xd);         
    #endif//GBM_USE_VFD_CONTROL_P_SCAN_LED
#endif//GBM_USE_VFD_CONTROL_LED
        
        //vfd_set_dot(VFD_DOT_PLAY);
        //index=vfd_set_disc_run(index);
        index = vfd_set_normal_state(index);
        break;
        
    }                                                           // end of switch
//#if defined(TP6311_DRIVER_VFD) && defined(SUPPROT_APOGEE_AMP)//xyy 2003-11-6 10:52
#ifdef AMPVOL_VFD_DISP  //xyy 2004-3-11 
    
    if(full_scrn == APOGEEAMPVOL)
    {
        vfd_set_ampvol();  
        return;
    }
#endif
#ifdef BBK_DVD//when STOP,not show time again. zhaoyanhua add 3-11-27 10:20
    if(play_state != VCD_STATE_STOP)
#endif
    vfd_set_playback();
    
}
#else//SUPPORT_VFD//nono 20031124
void update_vfd_data(void)
{

}
#endif//SUPPORT_VFD

/*
The old/new vfd driver is different on IOP program, 
on new vfd driver is auto scan vfd key on each 10ms and keep the last
key status on SDRAM buffer. ( for power key sensibility )

*/
  
#ifdef NEXT_FORWARD_IN_A_KEY        //gerry move it here,3-10-29 17:50
BYTE key_data_flag=0;
#endif//#ifdef NEXT_FORWARD_IN_A_KEY
  
#if  OLD_VFD_DRV    //if use this type to control nec16312,OLD_VFD_DRV must set 1
  
/*
** FUNCTION
** polling_vfdr
**
** DESCRIPTION
** check if polling-ready
*/
void polling_vfdr(void)
{

#ifdef SUPPORT_SPI_QSI
  //not use
#endif


#ifndef  SUPPORT_SPI_QSI


    
#ifdef SUPPORT_VFD
    UINT8   i;
    UINT32  temp;
    UINT32  key_data;
    static UINT8 key_state = 0, count = 0;
    static UINT32 key_previ = 0;
    
    
    if(regs0->iop_data[0] & FUN_MASK)
        return;
    
    if(vfd_state == VFD_READ)
    {
        regs0->iop_data[VFD_CMD] = 0x42;    //key polling
        regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
            (FUN_VFD_READ | 3);
        
        vfd_state = VFD_READ_BUSY;
    }
    else if(vfd_state == VFD_READ_BUSY)
    {
        
        key_data =
            (reverse_fun(regs0->iop_data[VFD_DAT0])) |
            (reverse_fun(regs0->iop_data[VFD_DAT0] >> 8) << 8) |
            (reverse_fun(regs0->iop_data[VFD_DAT1]) << 16);
        
        //printf("key_data=%x\n",key_data);
        //if (key_data == 0xffffff) 
        //{
        //break; //VFD buttons are pulled-high, if we don't connect VFD, we skip it, Jeff 20020612
        //printf("polling_vfdr:return\n");
        //return;
        //}           
        
        if(key_data == 0)
        {
            key_state = 0;
            key_previ = 0;
        }
        else
        {
            if(key_data != key_previ)
            {
                key_state = 1;
                key_previ = key_data;
            }
            else
            {
                if(key_state == 1)
                {
                    key_state = 2;
                    
                    for(i = 0; i < 24; i++)
                    {
                        temp = 0x01 << i;
                        if(key_data & temp)
                        {
                            if (key_data > temp) // Robert 030224 for preventing illegal key_data
                            {
                                key_data = 0;
                                return;
                            }
                            else
                            {
                                key_data = i + 1;
                                break;
                            }
                        }
                    }
                                        save_srn_start_t = get_rtc_val();//axel 2004/1/15 05:31,avoid looping PAUSE<->PLAY VFD key and entering screen saver                
#ifdef VFD_KEY_TEST
                    psprintf(RegionValStr[REGION1], "KEY %02d F:%d", key_data,
                        vfd_keycode[key_data - 1]);
                    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
                    
#else
                    if((Is_JPEG_SlideMode()) &&
                        (vfd_keycode[key_data - 1] == IRC_PAUSE))
                    {                                           //Jeff 20020523
                        bJpgVFDPause = 1;
                    }
                    else if((Is_JPEG_SlideMode()) &&
                        ((vfd_keycode[key_data - 1] == IRC_PLAY) ||
                        (vfd_keycode[key_data - 1] == IRC_PLAY_SELECT) ||
                        (vfd_keycode[key_data - 1] == IRC_PLAY_RESUME)))
                    {
                        //bJpgVFDPause=0;
                        bJpgVFDPause = 2;       //Jeff 20020525
                    }
                    else if((Is_JPEG_SlideMode()) &&    //Jeff 20020527
                        (vfd_keycode[key_data - 1] == IRC_PAUSEPLAY))
                    {
                        if(bJpgVFDPause == 0)
                        {
                            //bJpgVFDPause = 1;
                            if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
                                bJpgVFDPause = 2;
                            else
                                bJpgVFDPause = 1;
                        }
                        else if(bJpgVFDPause == 1)
                        {
                            bJpgVFDPause = 2;
                        }
                    }
                    else if(key_data<40)
                    {
                        extern UINT8 power_on;
                        
                        if(power_on == 2)       //2-6-18 13:36 to avoid accepting a VFD_key in the beginning. 
                        {
                            power_on--;
                            if(key_data != 1)
                            {
                                //save_srn_start_t = get_rtc_val();//axel, 2004/1/15 05:32 move to top
                                call_ir_func(vfd_keycode[key_data - 1]);
                            }
                        }
                        else
                        {
                            //save_srn_start_t = get_rtc_val();//axel,2004/1/15 05:33 move to top
                            call_ir_func(vfd_keycode[key_data - 1]);
                        }
                    }
#endif
                } 
            }
        }
        
        vfd_state = VFD_WRITE;
        update_vfd_data();
    }
    else
    {
        regs0->iop_data[VFD_CMD] = (0xc0 | count);
        regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
        regs0->iop_data[VFD_DAT1] = vfd_mem[count + 3] << 8 | vfd_mem[count + 2];
        regs0->iop_data[VFD_DAT2] = vfd_mem[count + 5] << 8 | vfd_mem[count + 4];
        
        regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
            (FUN_VFD_WRITE | VFD_DAT_LEN6);
        
        /* transfer data size add by chichang 2001 6/6 */
        count += 6;
        if(count == VFD_DISPLAY_SIZE)
        {
            count = 0;
            vfd_state = VFD_READ;
        }
        
    }
#endif

#endif //support spi qsi    
}

#elif (VFD_DRIVER==NEC16312) 
/*
lijd 2004-7-7 14:25
Process 16312sw use for:
1. extern pannel key
2. volume button 
note: need define NEC16312SW in cust_def.h
*/
#ifdef NEC16312SW
//#define USE_16312SW_EXTEND_KEY
#define USE_16312SW_VOLUME_BUTTON


#ifdef  USE_16312SW_EXTEND_KEY
#define SW_KEY1     31
#define SW_KEY2     35
#endif

#ifdef USE_16312SW_VOLUME_BUTTON
    #define VFD_SW_SPEED 3
#endif

void polling_vfdsw(void)
{
#ifdef  USE_16312SW_EXTEND_KEY   
   BYTE key_datasw;
   key_datasw= (BYTE)regs0->iop_data[7];
   if(key_datasw != 0xF0)
       {
          key_datasw>>=4;
          key_datasw+=24;
    #ifdef FUSS_SW
          if( (key_datasw == SW_KEY1) || (key_datasw == SW_KEY2) )
    #endif
          {
    #ifdef VFD_KEY_TEST
              printf("data=%d\n",key_datasw);
              psprintf(RegionValStr[REGION1], "KEY %02d F:%d", key_datasw,
                  vfd_keycode[key_datasw - 1]);
              PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
    #else
              save_srn_start_t = get_rtc_val();
              call_ir_func(vfd_keycode[key_datasw - 1]);
    #endif
      }
      regs0->iop_data[7] = 0xF0;            
     } 
#endif    

#ifdef USE_16312SW_VOLUME_BUTTON
   BYTE key_datasw;
   static BYTE prev = 0;
   BYTE updown = 0;
   static BYTE up_cnt = 0;
   static BYTE down_cnt = 0;
   key_datasw= (BYTE)regs0->iop_data[7];  
   if(prev != key_datasw)
   {
    
    switch(prev)
    {
        case 0x00:
            if (key_datasw == 0x80)
            {
                updown = 2;    
            }
            else if(key_datasw == 0x40)
            {
                updown = 1;    
            }
            break;
        
        case 0x80:
            if(key_datasw == 0xc0)
            {
                updown = 2;
            }
            else if (key_datasw == 0x00)
            {
                updown = 1;    
            }
            break;
        case 0xc0:
            if(key_datasw == 0x40)
            {
                updown = 2;
            }
            else if (key_datasw == 0x80)
            {
                updown = 1;    
            }
            break;
        case 0x40: 
            if(key_datasw == 0x00)
            {
                updown = 2;
            }
            else if (key_datasw == 0xc0)
            {
                updown = 1;    
            }
            break;   
       default:
            updown = 0;
            break;     
    }
        if(updown == 1)
        {
            down_cnt++;
            up_cnt = 0;     
            if(down_cnt >VFD_SW_SPEED )
            {
                down_cnt = 0;               
                ircmd_volume_up();   
            }
        }
        
        if(updown == 2)
        {
            up_cnt++;
            down_cnt = 0;    
            if(up_cnt >VFD_SW_SPEED )
            {
                up_cnt = 0;               
                ircmd_volume_down(); 
            }
    
}
        prev = key_datasw;  
   }
#endif
}
#endif
/*
** FUNCTION
** polling_vfdr
**
** DESCRIPTION
** check if polling-ready
*/
#if 0//def NEXT_FORWARD_IN_A_KEY        //gerry mark it,3-10-29 17:50
BYTE key_data_flag=0;
#endif//#ifdef NEXT_FORWARD_IN_A_KEY
#ifdef QISHENG_DVD
int standby_cnt=0;
#endif 
#ifdef AUTO_INTO_STANDBY    //oujx for tonic dvd//20040206
int auto_standby_timer=0;
#endif
#ifdef SUPPORT_GPIO_P_SCAN
BYTE PscanPortStatus=0;
BYTE PscanStatus=0;
BYTE PscanCount=0;
#endif

#ifdef TWO_FUN_IN_ONE_VFD_KEY
BYTE num_add_flag = 0;
BYTE command_flag = 1;
#endif

#ifdef HANYANG_SCAN_KEY

void check_hanyang_led(void)//2004/6/14 09:25狟敁 caoh
{
  static BYTE change_led = 0;
  if(play_state==VCD_STATE_CLOSE)
   {
     GPIO_E_SET(54,1);//set  CLK as output
     GPIO_E_SET(56,1);//set  DATA as output  
     
     change_led++;
     if(change_led<15)           
     {     
        GPIO_O_SET(54,0);
        GPIO_O_SET(56,0);
      }
      
     else
     {      
        GPIO_O_SET(54,0);
        GPIO_O_SET(56,1);
         if(change_led>30)
           change_led = 0;
     }    
   }    
}

void check_hanyang_keylight_status(void)  //caoh 2004-4-19 11:30
{
   static BYTE key_state = 0;  
   static int count0=0,count1=0,count2=1,count3=1;
   static BYTE key_state_flag1=0,key_state_flag2=0, key_state_flag3=0;  
     
   switch(key_state)
    {
           case  0:
                              
                   GPIO_E_SET(54,0);//set  CLK as input
                   GPIO_E_SET(56,0);//set  DATA as input
                   GPIO_O_SET(55,0);
                   GPIO_O_SET(57,1);
                   GPIO_O_SET(18,1);
                   if(!key_state_flag1)
                   {
                   if((!GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   { 
                           call_ir_func(IRC_POWER);
                           key_state_flag1=1;
                   }
                   else if((GPIO_I_GET(56))&&(!GPIO_I_GET(54)))
                   {
                             count0++;
                             if(count0>150*count2)
                            { 
                           call_ir_func(IRC_FORWARD);
                            count2++;
                          } 
                   } 
                   else
                   {
                         key_state_flag1=0;
                            if(play_state==VCD_STATE_CLOSE)
                                {
                                  check_hanyang_led();
                                  key_state = 1; 
                                }                      
                             else
                                {
                           if(count0<40&&count0>10)
                           {
                            call_ir_func(IRC_NEXT);
                            count0=0;
                           }         
                           else
                           {
                            count0=0;
                            count2=1;
                           }
                        GPIO_E_SET(54,1);//set  CLK as output
                        GPIO_E_SET(56,1);//set  DATA as output
                        GPIO_O_SET(54,0);
                        GPIO_O_SET(56,1);
                                    key_state = 1;  
                        }
                    }
                   }
                   
                  if((GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   {
                         key_state_flag1=0;
                   }  
                   break;
           case  1:
                                      
                   GPIO_E_SET(54,0);//set  CLK as input
                   GPIO_E_SET(56,0);//set  DATA as input
                   GPIO_O_SET(55,1);
                   GPIO_O_SET(57,1);
                   GPIO_O_SET(18,0);
                   if(!key_state_flag2)
                   {
                   if((!GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   { 
                           call_ir_func(IRC_STOP);
                           key_state_flag2=1;
                   }
                   else if((GPIO_I_GET(56))&&(!GPIO_I_GET(54)))
                   {
                            count1++;
                           if(count1>150*count3)
                            { 
                           call_ir_func(IRC_BACKWARD);
                            count3++;       
                            }     
                   } 
                   else
                   {
                           if(play_state==VCD_STATE_CLOSE)
                                {
                                  check_hanyang_led();
                                  key_state = 2; 
                                }        
                           else
                           {
                           if(count1<40&&count1>10)
                           {
                            call_ir_func(IRC_PREV);
                            count1=0;
                           }   
                           else
                           {
                           count1=0;
                           count3=1;
                           }      
                        GPIO_E_SET(54,1);//set  CLK as output
                        GPIO_E_SET(56,1);//set  DATA as output
                        GPIO_O_SET(54,0);
                        GPIO_O_SET(56,1);
                                      key_state = 2;
                     }
                    }   
                   }  
                   if((GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   {
                         key_state_flag2=0;
                   }    
                   break;
           case  2:
                   
                   GPIO_E_SET(54,0);//set  CLK as input
                   GPIO_E_SET(56,0);//set  DATA as input
                   GPIO_O_SET(55,1);
                   GPIO_O_SET(57,0);
                   GPIO_O_SET(18,1);
                    if(!key_state_flag3)
                   {
                   if((!GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   { 
                           call_ir_func(IRC_PAUSEPLAY);
                           save_srn_start_t = get_rtc_val();
                           key_state_flag3=1;
                          
                   }
                   else if((GPIO_I_GET(56))&&(!GPIO_I_GET(54)))
                   {
                           call_ir_func(IRC_EJECT);
                           save_srn_start_t = get_rtc_val();
                           key_state_flag3=1;                           
                   } 
                   else
                   {
                          if(play_state==VCD_STATE_CLOSE)
                                {
                                  check_hanyang_led();
                                  key_state = 0; 
                                }        
                           else
                    {
                        GPIO_E_SET(54,1);//set  CLK as output
                        GPIO_E_SET(56,1);//set  DATA as output
                        GPIO_O_SET(54,0);
                        GPIO_O_SET(56,1);
                    key_state=0; 
                    }
                    }
                   }
                   if((GPIO_I_GET(56))&&(GPIO_I_GET(54)))
                   {
                         key_state_flag3=0;
                   }  
                   break; 
                  default:break;
       }      
}   
#endif//#ifdef HANYANG_SCAN_KEY
#ifdef NINTAUS_612_SCAN_KEY         //linrc 2004-6-8 9:23
BYTE key_press_hold=0x00;
void vfdIO_scan_6key(void)
{   
    static BYTE Led_Counter = 0;
    BYTE key_scan_temp=0x03;
    if(play_state==VCD_STATE_CLOSE)
    {
        if(Led_Counter<5)
        {
            GPIO_O_SET(3,1);
            GPIO_O_SET(4,0);    
        }
        if(Led_Counter>5)
        {
            GPIO_O_SET(4,1);
            GPIO_O_SET(3,0);          
        }
        if(Led_Counter==10) Led_Counter = 0;    
        Led_Counter++;
    }
    else
    {
        GPIO_O_SET(4,0);
        GPIO_O_SET(3,0);
        if(cd_type_loaded == CDDA || cd_type_loaded == CDVCD10 || cd_type_loaded == CDVCD20
            || cd_type_loaded == CDSVCD) GPIO_O_SET(4,1);
        if(cd_type_loaded == CDROM || cd_type_loaded == CDDVD) GPIO_O_SET(3,1);                  
    }    
      
    GPIO_O_SET(56,1);//output high level.
    if (!GPIO_I_GET(54))
       key_scan_temp&=0x02;
    if (!GPIO_I_GET(55))
       key_scan_temp&=0x01;
    if (key_scan_temp!=0x03&&key_press_hold==0)
    {   
      key_press_hold=1;
      switch  (key_scan_temp)
        {
           case 0  :  call_ir_func(IRC_PLAY_RESUME); break;
           case 1  :  call_ir_func(IRC_EJECT); break;
           case 2  :  call_ir_func(IRC_POWER); break;
           default :  break;
        }
    }
    if (key_scan_temp==0x03) //(key_scan_temp==0x03)
    {
       key_scan_temp=0x03;   
       GPIO_O_SET(56,0);//output low level. 
       if (!GPIO_I_GET(54))
          key_scan_temp&=0x02;
       if (!GPIO_I_GET(55))
          key_scan_temp&=0x01;
       if (key_scan_temp!=0x03&&key_press_hold==0)
          { 
            key_press_hold=1;
        switch  (key_scan_temp)
              {
                 case 0  :  call_ir_func(IRC_PREV); break;
                 case 1  :  call_ir_func(IRC_STOP); break;
                 case 2  :  call_ir_func(IRC_NEXT); break;
                 default :  break;
              }
          }
       if (key_scan_temp==0x03)
          key_press_hold=0;        
     }                
}
#endif

void polling_vfdr(void)  //nec16321 type vfd
{ 
  
#ifdef SUPPORT_SPI_QSI
  //not use
#endif


#ifndef  SUPPORT_SPI_QSI

  
    
#ifdef SUPPORT_VFD

    UINT8   i;
    UINT32  temp;
    UINT32  key_data;
    static UINT8 count = 0;
    static UINT32 key_previ = 0;
    
    static BYTE bWriteState=0;
    
#ifdef TWO_FUN_IN_ONE_VFD_KEY
    static UINT32 key_previ_temp = 0;
    static UINT16 key_press_time_count = 0;
#endif //TWO_FUN_IN_ONE_VFD_KEY
    
    #ifdef KENLOON_PANEL3
	
	write_vfd_led(0xff);
	#endif
	
    #if defined(SUPPORT_VFD_SHOW_P_SCAN)&&defined(TONIC_DVD)//20040206
    if(vfd_intr_timer)
    vfd_intr_timer--;   
    #endif
    
    UINT32 *VfdReadData;

#ifdef  SUPPORT_SPI
    return;
#endif

#ifdef SUPPORT_GPIO_P_SCAN    //oujx for tonic only
if(full_scrn==0&&(system_state==SYSTEM_READ_TITLE||system_state==SYSTEM_SETUP_BROWSER||system_state==SYSTEM_BROWSE||system_state==SYSTEM_OPEN||play_state==VCD_STATE_STOP||system_state==SYSTEM_NODISC))    
{
    if(PscanStatus==0)
    {
    
        if(GPIO_I_GET(36)==0)
        PscanPortStatus=0;
        else
        PscanPortStatus=1;
        PscanCount=0;
        PscanStatus=1;
    }
    else
    if(PscanStatus==1)
    {
        PscanCount++;
        if(PscanCount>50)
        {
            if(GPIO_I_GET(36)==PscanPortStatus)
            {
                if(PscanPortStatus==0)
        ircmd_p_scan_only();
        else
        ircmd_yuv_only();
        
    }
            PscanStatus=0;
        }
    }
}       
#endif//#ifdef SUPPORT_GPIO_P_SCAN    //oujx for tonic only
    
    if(regs0->iop_data[0] & FUN_MASK)
        return;
       

    if(vfd_state == VFD_READ)
    {
        #ifndef USE_C_IOP//2004-2-12 12:08 lijd
        //update_vfd_data();//nono 2003-7-24 0:41 mark

        #ifdef  SUPPORT_RECEIVER  //huziqin 2004-4-27
        VfdReadData =
        ((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x588));
        #elif defined( SPHE8202)
        VfdReadData =           
            ((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x588));//for 8202 2004-3-31 16:47 lijd    
        #elif defined(XINGQIU_RECEIVER_PANNEL)
        VfdReadData =
            ((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x588));
        #else
        VfdReadData =
            ((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x5b8));       //gerry,2004-3-24 12:53
        #endif
        //current is read 3 byte on io
        key_data = *VfdReadData & 0x00ffffff;

        *VfdReadData = 0; // Robert 030313
        #else//USE_C_IOP
                key_data =(regs0->iop_data[3]);
        #endif//USE_C_IOP
        if(key_data == 0xffffff)
            return;
#ifdef USE_VFD_LED_TO_KEY_SOUND_INDICATE        //gerry for PANDA6950,3-8-23 17:17
        write_vfd_led(0xf);
#elif defined(USE_VFD_LED_TO_KEY_SOUND_INDICATE_HI_ON)      //NONO 2003-10-15 16:14
        write_vfd_led(0x0);
#endif

#ifdef TWO_FUN_IN_ONE_VFD_KEY
		    if((vfd_keycode[keycode_to_num(key_data)-1]==IRC_NEXT)||(vfd_keycode[keycode_to_num(key_data)-1]==IRC_PREV))
            {
            key_press_time_count++;
		        printf("key_press_time_count= %d \n",key_press_time_count);   
            }
		    
            if(key_press_time_count>=15)
            {
                if(vfd_keycode[keycode_to_num(key_data)-1]==IRC_NEXT)
                    {
					    call_ir_func(IRC_VFD_NEXT);
                        key_press_time_count=0;
                        num_add_flag = 1;
                    }
                else if(vfd_keycode[keycode_to_num(key_data)-1]==IRC_PREV)
                    {
					    call_ir_func(IRC_VFD_PREV);
                        key_press_time_count=0;
                        num_add_flag = 1;
                    }
            }
		
#endif //TWO_FUN_IN_ONE_VFD_KEY 

        if(key_data != key_previ)
        {
            
#ifdef TWO_FUN_IN_ONE_VFD_KEY
            //num_add_flag = 0;   //dingzhy 
            key_previ_temp = key_previ;
#endif //TWO_FUN_IN_ONE_VFD_KEY

            key_previ = key_data;

            if(key_data != 0)
            {
#ifdef TWO_FUN_IN_ONE_VFD_KEY
				//key_press_time_count=0;
				if((vfd_keycode[keycode_to_num(key_data)-1]==IRC_NEXT)||(vfd_keycode[keycode_to_num(key_data)-1]==IRC_PREV))
		        {
		            key_press_time_count++;
		        }
#endif //TWO_FUN_IN_ONE_VFD_KEY
                #ifdef XINGQIU_RECEIVER_PANNEL
                if(key_data == 0x111111)     //xulf 2004-3-9
                    return;
                key_data-=0x111111;  
                #endif
                                
                for(i = 0; i < 24; i++)
                {
                    temp = 0x01 << i;
                    if(key_data & temp)
                    {
                        if (key_data > temp) // Robert 030224 for preventing illegal key_data
                        {
                            key_data = 0;
                            return;
                        }
                        else
                        {
                            key_data = i + 1;
                            break;
                        }
                    }
                }
                
                save_srn_start_t = get_rtc_val();
#if defined(TONIC_DVD)//20040206
                if(KeyLockStatus==1)
                {
                    extern const char *const KeyLockString[4][10];
                //psprintf(RegionValStr[REGION1],"KEY LOCK ON");
                
                //PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                psprintf(RegionValStr[REGION1],KeyLockString[osd_font_mode][0]);
                PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                vfd_state = VFD_WRITE;
                return;
                }
#endif//defined(TONIC_DVD)              
#ifdef VFD_KEY_TEST
                psprintf(RegionValStr[REGION1], "KEY %02d F:%d", key_data,
                    vfd_keycode[key_data - 1]);
                PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
#else
                if((Is_JPEG_SlideMode()) && (vfd_keycode[key_data - 1] == IRC_PAUSE))
                {
                    //Jeff 20020523
                    bJpgVFDPause = 1;
                }
                else if((Is_JPEG_SlideMode()) &&
                    ((vfd_keycode[key_data - 1] == IRC_PLAY) ||
                    (vfd_keycode[key_data - 1] == IRC_PLAY_SELECT) ||
                    (vfd_keycode[key_data - 1] == IRC_PLAY_RESUME)))
                {
                    //bJpgVFDPause=0;
                    bJpgVFDPause = 2;           //Jeff 20020525
                    PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
                    ircmd_play();//nono 20031210
                }
                else if((Is_JPEG_SlideMode()) &&    //Jeff 20020527
                    (vfd_keycode[key_data - 1] == IRC_PAUSEPLAY))
                {
                    if(bJpgVFDPause == 0)
                    {
                        //bJpgVFDPause = 1;
                        if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
                            //bJpgVFDPause = 2;
                            
                            {
                            bJpgVFDPause = 2;
                            PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
                            ircmd_play();//nono 20031210
                            }
                            
                        else
                            bJpgVFDPause = 1;
                    }
                    else if(bJpgVFDPause == 1)
                    {
                        bJpgVFDPause = 2;
                    }
                }
                else if(key_data<40)
                {
                    extern UINT8 power_on;
                    
#ifdef QISHENG_DVD
        standby_cnt=0;
                    if((vfd_keycode[key_data - 1])==IRC_STOP)
                        standby_cnt=1;
#endif//#ifdef QISHENG_DVD
#ifdef NEXT_FORWARD_IN_A_KEY                    
                    key_data_flag = 1;
#endif//#ifdef NEXT_FORWARD_IN_A_KEY                    

                    if(power_on == 2)           //2-6-18 13:36 to avoid accepting a VFD_key in the beginning. 
                    {
                        power_on--;
                        if(key_data != 1)
                        {
#ifdef TWO_FUN_IN_ONE_VFD_KEY                           
                            if((vfd_keycode[key_data-1]!=IRC_NEXT) && (vfd_keycode[key_data-1]!=IRC_PREV))
#endif //TWO_FUN_IN_ONE_VFD_KEY
                            //save_srn_start_t = get_rtc_val();//axel moved to top 2004/2/4 06:13PM
                            call_ir_func(vfd_keycode[key_data - 1]);
                        }
                    }
                    else
                    {
                        //save_srn_start_t = get_rtc_val(); //axel moved to top 2004/2/4 06:13PM
#ifdef USE_VFD_LED_TO_KEY_SOUND_INDICATE        //gerry for PANDA6950,3-8-23 17:19                  
                        write_vfd_led(0);
#elif defined(USE_VFD_LED_TO_KEY_SOUND_INDICATE_HI_ON)      //NONO 2003-10-15 16:14
                        write_vfd_led(0xf);
#endif                      
                    
#ifdef TWO_FUN_IN_ONE_VFD_KEY
                        if((vfd_keycode[key_data-1]!=IRC_NEXT) && (vfd_keycode[key_data-1]!=IRC_PREV))
#endif //TWO_FUN_IN_ONE_VFD_KEY
                        call_ir_func(vfd_keycode[key_data - 1]);
                    }

#ifdef NEXT_FORWARD_IN_A_KEY                    
                    key_data_flag = 0;
#endif//#ifdef NEXT_FORWARD_IN_A_KEY
                }
#endif
        }

        else{
#ifdef TWO_FUN_IN_ONE_VFD_KEY
			if((key_press_time_count>0)&&(key_press_time_count<15)&&(num_add_flag==0)&&(command_flag))
            {
            if(vfd_keycode[keycode_to_num(key_previ_temp)-1]==IRC_NEXT)
			   {
			     call_ir_func(IRC_NEXT);
			     command_flag=0;
			    }
			    				
            else if(vfd_keycode[keycode_to_num(key_previ_temp)-1]==IRC_PREV)
			    {
			    call_ir_func(IRC_PREV);
			    command_flag=0;
			    }
           }
            key_press_time_count=0;  
			num_add_flag = 0;	
			
#endif //TWO_FUN_IN_ONE_VFD_KEY

#ifdef QISHENG_DVD           
             standby_cnt = 0;
#endif 
           }

        }
#ifdef QISHENG_DVD
        else if ((key_data!=0))
        {
            if(standby_cnt)
            {
                standby_cnt++;
                printf("*");
                if(standby_cnt==50)
                {
                    vfd_state = VFD_WRITE;
                    call_ir_func(IRC_POWER);
                }
            }
        }

#endif      
#ifdef 	TWO_FUN_IN_ONE_VFD_KEY
		else
		{
		    command_flag=1;
		    }	
#endif			
        vfd_state = VFD_WRITE;
    }
    
    else
    {
        update_vfd_data();
#if defined(SUPPORT_APOGEE_AMP) && defined(AMPVOL_ADJUST_TYPE1)//xyy 2004-4-14
    if(full_scrn==APOGEEAMPVOL && timeout_osd[REGION1] == 0)
    {
        full_scrn = 0;
        erase_vfd_mem();
    }
#endif
        //int i;
    #ifdef AUTO_INTO_STANDBY   //for tonic dvd//20040206
    //if(play_state==VCD_STATE_STOP||system_state==SYSTEM_NODISC)
    if(system_state==SYSTEM_STOP||system_state==SYSTEM_NODISC||play_state==VCD_STATE_STOP)
    {
        //auto_standby_timer++;
        //if(auto_standby_timer==100*60*30)
        if(auto_standby_timer==100*60*25)
        ircmd_power();
    }
    else
    auto_standby_timer=0;
    #endif
        switch (bWriteState)
        {
        case 0:
            //update to reset mode
#ifndef TEST_VFD
            regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | VFD_DISPLAY_MODE;
#else
            regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | COMMAND_MODE;
#endif      
            
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN0);
            
            bWriteState++;
            break;
            
        case 1:
            regs0->iop_data[VFD_CMD] =
                VFDC_DISP_CTRL | VFDC_DISP_CTRL_ON | VFDC_DISP_CTRL_10_16;
            
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN0);
            
            bWriteState++;
            break;
        #ifdef  SM1623_DRIVER_VFD
        case 2:             
            
#if 1
        //update in one polling
               for(i=0;i<VFD_DISPLAY_SIZE;i+=4)       // fengjl upload  3-11-23 17:33
{
            regs0->iop_data[VFD_CMD] = (0xc0 | i);   // transfer  address   
            if((VFD_DISPLAY_SIZE-i)<=4)//modefied by wangfeng,2003-11-24 10:41
            {
                regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
                regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN2);
            }
            else
            {
                regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
                regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
                regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN4);
            }
            
            WaitIopFunRdy(IOP_RDY_WAIT);
}           
            vfd_state = VFD_READ;
#else//#if 1
            //update by polling 10ms
            regs0->iop_data[VFD_CMD] = (0xc0 | count);
            if(count>=12)
            {
                regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
            }
            else
            {
                    regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
                    regs0->iop_data[VFD_DAT1] = vfd_mem[count + 3] << 8 | vfd_mem[count + 2];
            }
            //regs0->iop_data[VFD_DAT2] = vfd_mem[count + 5] << 8 | vfd_mem[count + 4];
            if(count>=12)
            {
                    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN2);
            }
            else
            {
                regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN4);
                
                }
            // transfer data size add by chichang 2001 6/6 
            count += 4;
            if(count >= VFD_DISPLAY_SIZE)
            {
                count = 0;
                vfd_state = VFD_READ;
            }
#endif//#if 1
            bWriteState=0;
            break;

#elif defined(GBM_LED6961_PANEL)||defined(ET6201_PANNEL)            //gerry for GBM_LED_PANEL,2004-2-4 22:41
        case 2:             

            for(i=0;i<VFD_DISPLAY_SIZE;i+=2)
            {
                regs0->iop_data[VFD_CMD] = (0xc0 | i);

                regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
                regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN2);
                WaitIopFunRdy(IOP_RDY_WAIT);        
            }   
            vfd_state = VFD_READ;   
            bWriteState=0;
            break;

#else//GBM_LED6961_PANEL
            
        case 2:             
            
#if !defined(TP6311_DRIVER_VFD) && !defined(XINGQIU_RECEIVER_PANNEL)&& !defined(KENLOON_PANEL3)	//xyy
            regs0->iop_data[VFD_CMD] = (0xc0 | count);
            regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
            regs0->iop_data[VFD_DAT1] = vfd_mem[count + 3] << 8 | vfd_mem[count + 2];
            #ifndef SKYWORTH_DVD
            regs0->iop_data[VFD_DAT2] = vfd_mem[count + 5] << 8 | vfd_mem[count + 4];
            #endif
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
            #ifndef SKYWORTH_DVD
                (FUN_VFD_WRITE | VFD_DAT_LEN6);
            
            /* transfer data size add by chichang 2001 6/6 */
            count += 6;
            #else
            (FUN_VFD_WRITE | VFD_DAT_LEN4);
            /* transfer data size add by chichang 2001 6/6 */
            count += 4;
            #endif
            
            if(count == VFD_DISPLAY_SIZE)
            {
                count = 0;
                vfd_state = VFD_READ;
            }
#else//#ifndef TP6311_DRIVER_VFD                                                     //marked by xyy 2003-10-31 19:42   
        for(i = 0; i < VFD_DISPLAY_SIZE; i += 6)    //xyy 2003-10-31 19:42
        {
            regs0->iop_data[VFD_CMD] = (0xc0 | i);
            regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
            regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
            regs0->iop_data[VFD_DAT2] = vfd_mem[i + 5] << 8 | vfd_mem[i + 4];
            
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN6);
            
            WaitIopFunRdy(IOP_RDY_WAIT);
        }
            vfd_state = VFD_READ;
#endif//#ifndef TP6311_DRIVER_VFD
            bWriteState=0;
            break;
#endif//#ifdef  SM1623_DRIVER_VFD
            
            
        }//write state control
        
        
    }
#elif defined(GPIO_KEY_LIGHT)//SUPPORT_VFD nono 3-8-18 14:41
check_gpio_keylight_status();
#elif defined(USE_VFDPORT_TRANDATA)
    Communication_And_MCU4051();       
#endif//SUPPORT_VFD

#endif //support spi qsi
}

#elif (VFD_DRIVER==HT1621)
/*
** FUNCTION
** polling_vfdr
**
** DESCRIPTION
** check if polling-ready
*/
void polling_vfdr(void)    //ht1621 type vfd
{
    
#ifdef SUPPORT_SPI_QSI
  //not use
#endif


#ifndef  SUPPORT_SPI_QSI

    
    
#ifdef CF_GPIO_CONTROL_COLOR    
  Polling_VFD_back_color(); 
#endif
#ifdef SUPPORT_VFD

    static UINT8 count = 0;
    static BYTE bWriteState=0;
    
    
    //UINT32 *VfdReadData;
    
    
    if(regs0->iop_data[0] & FUN_MASK)
        return;
    
                
    if(vfd_state == VFD_READ)  //we only use it to update vfd data
    {
        vfd_state = VFD_WRITE;
        update_vfd_data();  
    }
    else
    {
        
        switch (bWriteState)
        {
            
        case 2:             
            
            regs0->iop_data[VFD_CMD] = (count*2);//in cmd we only send address! write cmd deal in iop!
            regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
            regs0->iop_data[VFD_DAT1] = vfd_mem[count + 3] << 8 | vfd_mem[count + 2];
            //regs0->iop_data[VFD_DAT2] = vfd_mem[count + 5] << 8 | vfd_mem[count + 4];
            
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN4);
            
            /* transfer data size add by chichang 2001 6/6 */
            count += 4;
            
            if(count == VFD_DISPLAY_SIZE)//vfd_display_size
            {
                count = 0;
                vfd_state = VFD_READ;
            }
            
            bWriteState=2;
            break;
        default:
            bWriteState=2;
        }//write state control
        
        
    }

#endif//SUPPORT_VFD
#endif  // support spi qsi
}

#elif (VFD_DRIVER==AD7312)
void polling_vfdr(void) 
{ 
#ifdef SUPPORT_SPI_QSI
  //not use
#endif


#ifndef  SUPPORT_SPI_QSI

    
#ifdef SUPPORT_VFD

    UINT8   i;
    UINT32  temp;
    UINT32  key_data;
    static UINT8 count = 0;
    static UINT32 key_previ = 0;
    
    static BYTE bWriteState=0;
        
    UINT32 *VfdReadData;
    
    if(regs0->iop_data[0] & FUN_MASK)       return;
       

    if(vfd_state == VFD_READ)
    {
        #ifndef USE_C_IOP//2004-2-12 12:08 lijd     
        VfdReadData =
            //((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x658));       //gerry,2004-3-24 12:53
            ((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x688));       //fengjl edit 2004-07-02 18:05
        
        //current is read 3 byte on io
        key_data = *VfdReadData & 0x00ffffff;

        *VfdReadData = 0; // Robert 030313
        #else//USE_C_IOP
                key_data =(regs0->iop_data[3]);
        #endif//USE_C_IOP
        if(key_data == 0xffffff)
            return;
        if(key_data != key_previ)
        {
            
#ifdef TWO_FUN_IN_ONE_VFD_KEY
            //num_add_flag = 0;   //dingzhy 
            key_previ_temp = key_previ;
#endif //TWO_FUN_IN_ONE_VFD_KEY

            key_previ = key_data;

            if(key_data != 0)
            {
#ifdef TWO_FUN_IN_ONE_VFD_KEY
                key_press_time_count=0;
#endif //TWO_FUN_IN_ONE_VFD_KEY             
                                
                for(i = 0; i < 24; i++)
                {
                    temp = 0x01 << i;
                    if(key_data & temp)
                    {
                        if (key_data > temp) // Robert 030224 for preventing illegal key_data
                        {
                            key_data = 0;
                            return;
                        }
                        else
                        {
                            key_data = i + 1;
                            break;
                        }
                    }
                }
                
                save_srn_start_t = get_rtc_val();
                
#ifdef VFD_KEY_TEST
                psprintf(RegionValStr[REGION1], "KEY %02d F:%d", key_data,
                    vfd_keycode[key_data - 1]);
                PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
#else
                if((Is_JPEG_SlideMode()) && (vfd_keycode[key_data - 1] == IRC_PAUSE))
                {
                    //Jeff 20020523
                    bJpgVFDPause = 1;
                }
                else if((Is_JPEG_SlideMode()) &&
                    ((vfd_keycode[key_data - 1] == IRC_PLAY) ||
                    (vfd_keycode[key_data - 1] == IRC_PLAY_SELECT) ||
                    (vfd_keycode[key_data - 1] == IRC_PLAY_RESUME)))
                {
                    //bJpgVFDPause=0;
                    bJpgVFDPause = 2;           //Jeff 20020525
                    PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
                    ircmd_play();//nono 20031210
                }
                else if((Is_JPEG_SlideMode()) &&    //Jeff 20020527
                    (vfd_keycode[key_data - 1] == IRC_PAUSEPLAY))
                {
                    if(bJpgVFDPause == 0)
                    {
                        //bJpgVFDPause = 1;
                        if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
                            //bJpgVFDPause = 2;
                            
                            {
                            bJpgVFDPause = 2;
                            PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
                            ircmd_play();//nono 20031210
                            }
                            
                        else
                            bJpgVFDPause = 1;
                    }
                    else if(bJpgVFDPause == 1)
                    {
                        bJpgVFDPause = 2;
                    }
                }
                else if(key_data<40)
                {
                    extern UINT8 power_on;
                    

#ifdef NEXT_FORWARD_IN_A_KEY                    
                    key_data_flag = 1;
#endif//#ifdef NEXT_FORWARD_IN_A_KEY                    

                    if(power_on == 2)           //2-6-18 13:36 to avoid accepting a VFD_key in the beginning. 
                    {
                        power_on--;
                        if(key_data != 1)
                        {
#ifdef TWO_FUN_IN_ONE_VFD_KEY                           
                            if((vfd_keycode[key_data-1]!=IRC_NEXT) && (vfd_keycode[key_data-1]!=IRC_PREV))
#endif //TWO_FUN_IN_ONE_VFD_KEY
                            //save_srn_start_t = get_rtc_val();//axel moved to top 2004/2/4 06:13PM
                            call_ir_func(vfd_keycode[key_data - 1]);
                        }
                    }
                    else
                    {
                        //save_srn_start_t = get_rtc_val(); //axel moved to top 2004/2/4 06:13PM
#ifdef USE_VFD_LED_TO_KEY_SOUND_INDICATE        //gerry for PANDA6950,3-8-23 17:19                  
                        write_vfd_led(0);
#elif defined(USE_VFD_LED_TO_KEY_SOUND_INDICATE_HI_ON)      //NONO 2003-10-15 16:14
                        write_vfd_led(0xf);
#endif                      
                    
#ifdef TWO_FUN_IN_ONE_VFD_KEY
                        if((vfd_keycode[key_data-1]!=IRC_NEXT) && (vfd_keycode[key_data-1]!=IRC_PREV))
#endif //TWO_FUN_IN_ONE_VFD_KEY
                        call_ir_func(vfd_keycode[key_data - 1]);
                    }

#ifdef NEXT_FORWARD_IN_A_KEY                    
                    key_data_flag = 0;
#endif//#ifdef NEXT_FORWARD_IN_A_KEY
                }
#endif
        }

        else{
#ifdef TWO_FUN_IN_ONE_VFD_KEY
            if((key_press_time_count>0)&&(key_press_time_count<15))
            {
            if(vfd_keycode[keycode_to_num(key_previ_temp)-1]==IRC_NEXT)
                call_ir_func(IRC_VFD_NEXT);                 
            else if(vfd_keycode[keycode_to_num(key_previ_temp)-1]==IRC_PREV)
                call_ir_func(IRC_VFD_PREV);
           }
            key_press_time_count=0;  
#endif //TWO_FUN_IN_ONE_VFD_KEY

#ifdef QISHENG_DVD           
             standby_cnt = 0;
#endif 
           }

        }
#ifdef QISHENG_DVD
        else if ((key_data!=0))
        {
            if(standby_cnt)
            {
                standby_cnt++;
                printf("*");
                if(standby_cnt==50)
                {
                    vfd_state = VFD_WRITE;
                    call_ir_func(IRC_POWER);
                }
            }
        }

#endif      
                
        vfd_state = VFD_WRITE;
    }
    
    else
    {
        update_vfd_data();
#if defined(SUPPORT_APOGEE_AMP) && defined(AMPVOL_ADJUST_TYPE1)//xyy 2004-4-14
    if(full_scrn==APOGEEAMPVOL && timeout_osd[REGION1] == 0)
    {
        full_scrn = 0;
        erase_vfd_mem();
    }
#endif
        //int i;
    #ifdef AUTO_INTO_STANDBY   //for tonic dvd//20040206
    //if(play_state==VCD_STATE_STOP||system_state==SYSTEM_NODISC)
    if(system_state==SYSTEM_STOP||system_state==SYSTEM_NODISC||play_state==VCD_STATE_STOP)
    {
        //auto_standby_timer++;
        //if(auto_standby_timer==100*60*30)
        if(auto_standby_timer==100*60*25)
        ircmd_power();
    }
    else
    auto_standby_timer=0;
    #endif
        switch (bWriteState)
        {
        case 0:
            //update to reset mode
#ifndef TEST_VFD
            regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | VFD_DISPLAY_MODE;
#else
            regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | COMMAND_MODE;
#endif      
            
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN0);
            
            bWriteState++;
            break;
            
        case 1:
            regs0->iop_data[VFD_CMD] =
                VFDC_DISP_CTRL | VFDC_DISP_CTRL_ON | VFDC_DISP_CTRL_10_16;
            
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN0);
            
            bWriteState++;
            break;
        #ifdef  SM1623_DRIVER_VFD
        case 2:             
            
#if 1
        //update in one polling
               for(i=0;i<VFD_DISPLAY_SIZE;i+=4)       // fengjl upload  3-11-23 17:33
{
            regs0->iop_data[VFD_CMD] = (0xc0 | i);   // transfer  address   
            if((VFD_DISPLAY_SIZE-i)<=4)//modefied by wangfeng,2003-11-24 10:41
            {
                regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
                regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN2);
            }
            else
            {
                regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
                regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
                regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN4);
            }
            
            WaitIopFunRdy(IOP_RDY_WAIT);
}           
            vfd_state = VFD_READ;
#else//#if 1
            //update by polling 10ms
            regs0->iop_data[VFD_CMD] = (0xc0 | count);
            if(count>=12)
            {
                regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
            }
            else
            {
                    regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
                    regs0->iop_data[VFD_DAT1] = vfd_mem[count + 3] << 8 | vfd_mem[count + 2];
            }
            //regs0->iop_data[VFD_DAT2] = vfd_mem[count + 5] << 8 | vfd_mem[count + 4];
            if(count>=12)
            {
                    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN2);
            }
            else
            {
                regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN4);
                
                }
            // transfer data size add by chichang 2001 6/6 
            count += 4;
            if(count >= VFD_DISPLAY_SIZE)
            {
                count = 0;
                vfd_state = VFD_READ;
            }
#endif//#if 1
            bWriteState=0;
            break;

#elif defined(GBM_LED6961_PANEL)            //gerry for GBM_LED_PANEL,2004-2-4 22:41
        case 2:             

            for(i=0;i<VFD_DISPLAY_SIZE;i+=2)
            {
                regs0->iop_data[VFD_CMD] = (0xc0 | i);

                regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
                regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN2);
                WaitIopFunRdy(IOP_RDY_WAIT);        
            }   
            vfd_state = VFD_READ;   
            bWriteState=0;
            break;

#else//GBM_LED6961_PANEL
            
        case 2:             
            
#if !defined(TP6311_DRIVER_VFD) && !defined(XINGQIU_RECEIVER_PANNEL)    //xyy
            regs0->iop_data[VFD_CMD] = (0xc0 | count);
            regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
            regs0->iop_data[VFD_DAT1] = vfd_mem[count + 3] << 8 | vfd_mem[count + 2];
            #ifndef SKYWORTH_DVD
            regs0->iop_data[VFD_DAT2] = vfd_mem[count + 5] << 8 | vfd_mem[count + 4];
            #endif
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
            #ifndef SKYWORTH_DVD
                (FUN_VFD_WRITE | VFD_DAT_LEN6);
            
            /* transfer data size add by chichang 2001 6/6 */
            count += 6;
            #else
            (FUN_VFD_WRITE | VFD_DAT_LEN4);
            /* transfer data size add by chichang 2001 6/6 */
            count += 4;
            #endif
            
            if(count == VFD_DISPLAY_SIZE)
            {
                count = 0;
                vfd_state = VFD_READ;
            }
#else//#ifndef TP6311_DRIVER_VFD                                                     //marked by xyy 2003-10-31 19:42   
        for(i = 0; i < VFD_DISPLAY_SIZE; i += 6)    //xyy 2003-10-31 19:42
        {
            regs0->iop_data[VFD_CMD] = (0xc0 | i);
            regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
            regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
            regs0->iop_data[VFD_DAT2] = vfd_mem[i + 5] << 8 | vfd_mem[i + 4];
            
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN6);
            
            WaitIopFunRdy(IOP_RDY_WAIT);
        }
            vfd_state = VFD_READ;
#endif//#ifndef TP6311_DRIVER_VFD
            bWriteState=0;
            break;
#endif//#ifdef  SM1623_DRIVER_VFD
            
            
        }//write state control
        
        
    }
#elif defined(GPIO_KEY_LIGHT)//SUPPORT_VFD nono 3-8-18 14:41
check_gpio_keylight_status();
#elif defined(USE_VFDPORT_TRANDATA)
    Communication_And_MCU4051();       
#endif//SUPPORT_VFD
#endif//spi qsi
}
/*
** FUNCTION
** polling_vfdr
**
** DESCRIPTION
** check if polling-ready
*/
#elif (VFD_DRIVER==HC164)
void polling_vfdr(void)  //HC164 type vfd
{
#ifdef SUPPORT_SPI_QSI
  //not use
#endif


#ifndef  SUPPORT_SPI_QSI

    
#ifdef SUPPORT_VFD
    UINT8   i;
    UINT32  temp;
    UINT32  key_data;
    static UINT8 count = 0;
    static UINT32 key_previ = 0;
    
    static BYTE bWriteState=0;
    
    
    UINT32 *VfdReadData;
    
    
    if(regs0->iop_data[0] & FUN_MASK)
        return;
    
    
    if(vfd_state == VFD_READ)
    {
        
        //read key data         
        VfdReadData =
            ((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x588));


        //current is read 3 byte on io
        key_data = *VfdReadData & 0x000000ff;
        
        //if vfd is no connect, summer 20020912
        if(key_data != 0x0000ff)
            *VfdReadData = 0;                   //clear key value            

        if(key_data != key_previ)
        {
            
            key_previ = key_data;
            
            if(key_data != 0)
            {
            /*for(i = 0; i < 24; i++)//in spl10 key is bcd 
            {
            temp = 0x01 << i;
            if(key_data & temp)
            {
            key_data = i + 1;
            break;                          //return;//nono 2-6-28 14:00
            }
            }*/

#ifdef VFD_KEY_TEST
                psprintf(RegionValStr[REGION1], "KEY %02d F:%d", key_data,
                    vfd_keycode[key_data - 1]);
                PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
                
#else
                if((Is_JPEG_SlideMode()) && (vfd_keycode[key_data - 1] == IRC_PAUSE))
                {
                    //Jeff 20020523
                    bJpgVFDPause = 1;
                }
                else if((Is_JPEG_SlideMode()) &&
                    ((vfd_keycode[key_data - 1] == IRC_PLAY) ||
                    (vfd_keycode[key_data - 1] == IRC_PLAY_SELECT) ||
                    (vfd_keycode[key_data - 1] == IRC_PLAY_RESUME)))
                {
                    //bJpgVFDPause=0;
                    bJpgVFDPause = 2;           //Jeff 20020525
                }
                else if((Is_JPEG_SlideMode()) &&    //Jeff 20020527
                    (vfd_keycode[key_data - 1] == IRC_PAUSEPLAY))
                {
                    if(bJpgVFDPause == 0)
                    {
                        //bJpgVFDPause = 1;
                        if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
                            bJpgVFDPause = 2;
                        else
                            bJpgVFDPause = 1;
                    }
                    else if(bJpgVFDPause == 1)
                    {
                        bJpgVFDPause = 2;
                    }
                }
                else if(key_data<40)
                {
                    
                    extern UINT8 power_on;
                    
                    if(power_on == 2)           //2-6-18 13:36 to avoid accepting a VFD_key in the beginning. 
                    {
                        power_on--;
                        if(key_data != 1)
                        {
                            save_srn_start_t = get_rtc_val();
                            call_ir_func(vfd_keycode[key_data - 1]);
                        }
                    }
                    else
                    {
                        save_srn_start_t = get_rtc_val();
                        call_ir_func(vfd_keycode[key_data - 1]);
                    }
                    
                }
#endif
            }
        }
        
        vfd_state = VFD_WRITE;
        update_vfd_data();
    }
    
    else
    {
        
        switch (bWriteState)
        {
#if 0   //spl10 don't send its system init!?? i don't know .
        case 0:
            //update to reset mode
#ifndef TEST_VFD
            regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | VFD_DISPLAY_MODE;
#else
            regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | COMMAND_MODE;
#endif      
            
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN0);
            
            bWriteState++;
            break;
            
        case 1:
            regs0->iop_data[VFD_CMD] =
                VFDC_DISP_CTRL | VFDC_DISP_CTRL_ON | VFDC_DISP_CTRL_10_16;
            
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN0);
            
            bWriteState++;
            break;
#endif
        case 2:             
            
            regs0->iop_data[VFD_CMD] = (0xa0 | count);
            regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
            regs0->iop_data[VFD_DAT1] = vfd_mem[count + 3] << 8 | vfd_mem[count + 2];
            regs0->iop_data[VFD_DAT2] = vfd_mem[count + 5] << 8 | vfd_mem[count + 4];
            
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN6);
            
            /* transfer data size add by chichang 2001 6/6 */
            count += 6;
            if(count == VFD_DISPLAY_SIZE)
            {
                count = 0;
                vfd_state = VFD_READ;
            }
            
            bWriteState=2;
            break;
        default :
            bWriteState=2;  
        }//write state control
        
        
    }
#endif
#endif  //spi qsi
}
#elif (VFD_DRIVER==PT6554)
void polling_vfdr(void)  //pt6554 type vfd
{    
#ifdef SUPPORT_SPI_QSI
  //not use
#endif


#ifndef  SUPPORT_SPI_QSI

      
      
#ifdef SUPPORT_VFD
    UINT8   i;
    UINT32  temp;
    UINT32  key_data;
    static UINT8 count = 0;
    static UINT32 key_previ = 0;
    static BYTE pt6554_flag=1;
    static BYTE bWriteState=0;
    
    
    UINT32 *VfdReadData;
    
    
    if(regs0->iop_data[0] & FUN_MASK)
        return;
    
    
    if(vfd_state == VFD_READ)
    {
        
        //read key data         
        VfdReadData =
            ((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x5d8));


        //current is read 3 byte on io
        key_data = *VfdReadData & 0x00ffffff;
        
        //if vfd is no connect, summer 20020912
        if(key_data != 0x00ffff)
            *VfdReadData = 0;                   //clear key value            

        if(key_data != key_previ)
        {
            
            key_previ = key_data;
            
            if(key_data != 0)
            {
            /*for(i = 0; i < 24; i++)//in spl10 key is bcd 
            {
            temp = 0x01 << i;
            if(key_data & temp)
            {
            key_data = i + 1;
            break;                          //return;//nono 2-6-28 14:00
            }
            }*/
                
#ifdef VFD_KEY_TEST
                psprintf(RegionValStr[REGION1], "KEY %02d F:%d", key_data,
                    vfd_keycode[key_data - 1]);
                PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
                
#else
                if((Is_JPEG_SlideMode()) && (vfd_keycode[key_data - 1] == IRC_PAUSE))
                {
                    //Jeff 20020523
                    bJpgVFDPause = 1;
                }
                else if((Is_JPEG_SlideMode()) &&
                    ((vfd_keycode[key_data - 1] == IRC_PLAY) ||
                    (vfd_keycode[key_data - 1] == IRC_PLAY_SELECT) ||
                    (vfd_keycode[key_data - 1] == IRC_PLAY_RESUME)))
                {
                    //bJpgVFDPause=0;
                    bJpgVFDPause = 2;           //Jeff 20020525
                }
                else if((Is_JPEG_SlideMode()) &&    //Jeff 20020527
                    (vfd_keycode[key_data - 1] == IRC_PAUSEPLAY))
                {
                    if(bJpgVFDPause == 0)
                    {
                        //bJpgVFDPause = 1;
                        if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
                            bJpgVFDPause = 2;
                        else
                            bJpgVFDPause = 1;
                    }
                    else if(bJpgVFDPause == 1)
                    {
                        bJpgVFDPause = 2;
                    }
                }
                else if(key_data<40)
                {
                    
                    extern UINT8 power_on;
                    
                    if(power_on == 2)           //2-6-18 13:36 to avoid accepting a VFD_key in the beginning. 
                    {
                        power_on--;
                        if(key_data != 1)
                        {
                            save_srn_start_t = get_rtc_val();
                            call_ir_func(vfd_keycode[key_data - 1]);
                        }
                    }
                    else
                    {
                        save_srn_start_t = get_rtc_val();
                        call_ir_func(vfd_keycode[key_data - 1]);
                    }
                    
                }
#endif
            }
        }
        
        vfd_state = VFD_WRITE;
        update_vfd_data();
    }
    
    else
    {
        
        switch (bWriteState)
        {


        case 2:             
            
            //regs0->iop_data[VFD_CMD] = (0xa0 | count);
            regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
            regs0->iop_data[VFD_DAT1] = vfd_mem[count + 3] << 8 | vfd_mem[count + 2];
            regs0->iop_data[VFD_DAT2] = vfd_mem[count + 5] << 8 | vfd_mem[count + 4];
            if(pt6554_flag==1)
            {
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN1);
                pt6554_flag=2;
            }
            else if(pt6554_flag==2)
            {
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN6);
                pt6554_flag=3;
            }
            else if(pt6554_flag==3)
            {
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN3);
                pt6554_flag=4;
            }
            else if(pt6554_flag==4)
            {
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN4);
                pt6554_flag=1;
            }   
                
            
            /* transfer data size add by chichang 2001 6/6 */
            count += 6;
            if(count == VFD_DISPLAY_SIZE)
            {
                count = 0;
                vfd_state = VFD_READ;
            }
            
            bWriteState=2;
            break;
        default :
            bWriteState=2;  
        }//write state control
        
        
    }
#endif
#endif //spi qsi
}
#else           //for spl10 type
/*
** FUNCTION
** polling_vfdr
**
** DESCRIPTION
** check if polling-ready
*/
void polling_vfdr(void)  //spl10 type vfd
{
#ifdef SUPPORT_SPI_QSI
  //not use
#endif


#ifndef  SUPPORT_SPI_QSI

    
#ifdef SUPPORT_VFD
    UINT8   i;
    UINT32  temp;
    UINT32  key_data;
    static UINT8 count = 0;
    static UINT32 key_previ = 0;
    
    static BYTE bWriteState=0;
    
    
    UINT32 *VfdReadData;
    
    
    if(regs0->iop_data[0] & FUN_MASK)
        return;
    
    
    if(vfd_state == VFD_READ)
    {
        
        //read key data         
        VfdReadData =
            ((UINT32 *) (SDRAM_BASE_UNCACHED + regs0->iopya * 1024 + 0x5E8));


        //current is read 3 byte on io
        key_data = *VfdReadData & 0x00ffffff;
        
        //if vfd is no connect, summer 20020912
        if(key_data != 0xffffff)
            *VfdReadData = 0;                   //clear key value            

        if(key_data != key_previ)
        {
            
            key_previ = key_data;
            
            if(key_data != 0)
            {
            /*for(i = 0; i < 24; i++)//in spl10 key is bcd 
            {
            temp = 0x01 << i;
            if(key_data & temp)
            {
            key_data = i + 1;
            break;                          //return;//nono 2-6-28 14:00
            }
            }*/
                
#ifdef VFD_KEY_TEST
                psprintf(RegionValStr[REGION1], "KEY %02d F:%d", key_data,
                    vfd_keycode[key_data - 1]);
                PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
                
#else
                if((Is_JPEG_SlideMode()) && (vfd_keycode[key_data - 1] == IRC_PAUSE))
                {
                    //Jeff 20020523
                    bJpgVFDPause = 1;
                }
                else if((Is_JPEG_SlideMode()) &&
                    ((vfd_keycode[key_data - 1] == IRC_PLAY) ||
                    (vfd_keycode[key_data - 1] == IRC_PLAY_SELECT) ||
                    (vfd_keycode[key_data - 1] == IRC_PLAY_RESUME)))
                {
                    //bJpgVFDPause=0;
                    bJpgVFDPause = 2;           //Jeff 20020525
                }
                else if((Is_JPEG_SlideMode()) &&    //Jeff 20020527
                    (vfd_keycode[key_data - 1] == IRC_PAUSEPLAY))
                {
                    if(bJpgVFDPause == 0)
                    {
                        //bJpgVFDPause = 1;
                        if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
                            bJpgVFDPause = 2;
                        else
                            bJpgVFDPause = 1;
                    }
                    else if(bJpgVFDPause == 1)
                    {
                        bJpgVFDPause = 2;
                    }
                }
                else if(key_data<40)
                {
                    
                    extern UINT8 power_on;
                    
                    if(power_on == 2)           //2-6-18 13:36 to avoid accepting a VFD_key in the beginning. 
                    {
                        power_on--;
                        if(key_data != 1)
                        {
                            save_srn_start_t = get_rtc_val();
                            call_ir_func(vfd_keycode[key_data - 1]);
                        }
                    }
                    else
                    {
                        save_srn_start_t = get_rtc_val();
                        call_ir_func(vfd_keycode[key_data - 1]);
                    }
                    
                }
#endif
            }
        }
        
        vfd_state = VFD_WRITE;
        update_vfd_data();
    }
    
    else
    {
        
        switch (bWriteState)
        {
#if 0   //spl10 don't send its system init!?? i don't know .
        case 0:
            //update to reset mode
#ifndef TEST_VFD
            regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | VFD_DISPLAY_MODE;
#else
            regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | COMMAND_MODE;
#endif      
            
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN0);
            
            bWriteState++;
            break;
            
        case 1:
            regs0->iop_data[VFD_CMD] =
                VFDC_DISP_CTRL | VFDC_DISP_CTRL_ON | VFDC_DISP_CTRL_10_16;
            
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN0);
            
            bWriteState++;
            break;
#endif
        case 2:             
            
            regs0->iop_data[VFD_CMD] = (0xa0 | count);
            regs0->iop_data[VFD_DAT0] = vfd_mem[count + 1] << 8 | vfd_mem[count];
            regs0->iop_data[VFD_DAT1] = vfd_mem[count + 3] << 8 | vfd_mem[count + 2];
            regs0->iop_data[VFD_DAT2] = vfd_mem[count + 5] << 8 | vfd_mem[count + 4];
            
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN6);
            
            /* transfer data size add by chichang 2001 6/6 */
            count += 6;
            if(count == VFD_DISPLAY_SIZE)
            {
                count = 0;
                vfd_state = VFD_READ;
            }
            
            bWriteState=2;
            break;
        default :
            bWriteState=2;  
        }//write state control
        
        
    }
#endif
#endif //spi qsi
}

#endif

/*
** freyman 2002-7-4 11:27
** 
** FUNCTION
** polling_vfdtime
**
** DESCRIPTION
** checking VFD timeout, every time 'diff' RTC ticks is subtracted
** from VFD timeout.
**
** NOTES: if timeout value is 0 then this check is ignored.
**
*/
#if defined(VFD_VOLUME_DISPLAY) || defined(SUPPORT_TUNER_MV114) || defined(SUPPORT_TUNER_ALPS)
void polling_vfdtime(int diff)
{
    //      int    i;
    int     TimeToLive;
    
    if(diff < 0)
        return;
    else if(diff > 100)
        diff = 100;
    //printf("timeout : %d  diff:%d\n", timeout_vfd, diff);
    if((TimeToLive = timeout_vfd) != 0)
    {
        if((TimeToLive -= diff) <= 0)
        {
            TimeToLive = 0;
            //PatternMode=0;                
            
            /*                  if(!TimeToLive)
            {
            printf("vfd_mode_state dvd normal mode\n");
            vfd_mode_state = DVD_NORMAL_MODE;               
        }*/
        }                                                       //end of if ((TimeToLive -= diff)<=0)
        timeout_vfd = TimeToLive;
    }
}
#endif
/*
** FUNCTION
** polling_vfd
**
** DESCRIPTION
** checking if we could issue VFD task
*/
#if 0
int polling_vfd(void)
{
#ifdef    SUPPORT_VFD
    static BYTE i = 0;
    
    //check IOP is free ?
    if(regs0->iop_data[0] & FUN_MASK)
        return 0;
    
    if(vfd_state == VFD_WRITE)
    {
        regs0->iop_data[VFD_CMD] = (0xc0 | i);
        regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
        regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
        regs0->iop_data[VFD_DAT2] = vfd_mem[i + 5] << 8 | vfd_mem[i + 4];
        
        regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
            (FUN_VFD_WRITE | VFD_DAT_LEN6);
        
        /* transfer data size add by chichang 2001 6/6 */
        i += 6;
        if(i == VFD_DISPLAY_SIZE)
        {
            i = 0;
            vfd_state = VFD_READ;
        }
        
    }
    /*
       else
       {
       vfd_state = VFD_READ;
       } 
    */
#endif
    return 0;
}

#endif


#ifdef SUPPORT_VFD//nono 20031124
void init_vfd_clear(void)
{
    int     i;                                      //,j;
    BYTE    mem_count;
    #if defined(POWER_OFF_SHOW)&&defined(TONIC_DVD)||defined(KENLOON_DVD)//20040206
    UINT32  power_timer=0;
    #endif
    
    erase_vfd_mem();
    #if (VFD_DRIVER==PT6554)//LIJD 2004-3-6 18:58
    regs0->iop_data[VFD_DAT0] = 0;
    regs0->iop_data[VFD_DAT1] = 0;
    regs0->iop_data[VFD_DAT2] = 0;

    WaitIopFunRdy(IOP_RDY_WAIT);
    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN1);

    WaitIopFunRdy(IOP_RDY_WAIT);
    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN6);

    WaitIopFunRdy(IOP_RDY_WAIT);
    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN3);

    WaitIopFunRdy(IOP_RDY_WAIT);
    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
                (FUN_VFD_WRITE | VFD_DAT_LEN4);
                
    return;
#endif//(VFD_DRIVER==PT6554)
    
    //send memory data to VFD

/*  
#if 0
#if VFD_MODULE == HT1611_LCD
    mem_count = 12;                             //42;
#elif VFD_MODULE == FUT_6_BT_269GK1
    mem_count = 12;
#endif
#endif
*/  
    #ifdef POWER_OFF_SHOW   //wangfeng 2003-10-13 18:03
    if (system_state==SYSTEM_POWER||play_state==VCD_STATE_POWER)
    {
        #ifdef BBK_DV961_DVD     //hq add,3-11-30 14:22
                vfd_set_str(0,"OFF"); 
        vfd_set_dot(VFD_DOT_LED);    
        #else
        vfd_set_str(0,"OFF");

#if defined(TONIC_DVD)||defined(KENLOON_DVD)   //oujx 0206
       power_timer=0x5ffffff;
#endif//defined(TONIC_DVD)
        
    #endif
    }   
    #endif// END POWER_OFF_SHOW
    
    mem_count = VFD_DISPLAY_SIZE;   //2001/10/23
#ifdef JIEKE_PANNEL_GK3800
        for(i = 0; i < mem_count; )
#else   
    for(i = 0; i < mem_count; i += 6)
#endif  //END JIEKE_PANNEL_GK3800
    {
        
#if (VFD_DRIVER==NEC16312) 
        regs0->iop_data[VFD_CMD] = (0xc0 | i);
#elif (VFD_DRIVER==HT1621)  //in ht1621 it don't send write cmd
        regs0->iop_data[VFD_CMD]=(i*2);
#else //for spl10
        regs0->iop_data[VFD_CMD]=(0xA0 | i);
#endif

#ifdef BBK_PANNEL   //fengjl add 3-12-22 13:57 to avoid dot mp3 when power on every time
for(i=0;i<VFD_DISPLAY_SIZE;i+=4)        
{
        regs0->iop_data[VFD_CMD] = (0xc0 | i);   // transfer  address   
    if((VFD_DISPLAY_SIZE-i)<=4)//modefied by wangfeng,2003-11-24 10:41
    {
        regs0->iop_data[VFD_DAT0] = vfd_mem[i];
        //regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
        regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
        (FUN_VFD_WRITE | VFD_DAT_LEN1);
    }
    else
    {
        regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
        regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
        regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
        (FUN_VFD_WRITE | VFD_DAT_LEN4);
    }       
        WaitIopFunRdy(IOP_RDY_WAIT);
}
#else
        regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
        regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
        regs0->iop_data[VFD_DAT2] = vfd_mem[i + 5] << 8 | vfd_mem[i + 4];

#ifdef JIEKE_PANNEL_GK3800
    if(i<mem_count-2)
    {
        regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
            (FUN_VFD_WRITE | VFD_DAT_LEN4);
        i+=4;
            }
    else
    {
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
            (FUN_VFD_WRITE | VFD_DAT_LEN1);
        i++;
        }
#else//#ifdef JIEKE_PANNEL_GK3800       
        regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
            (FUN_VFD_WRITE | VFD_DAT_LEN6);
#endif//#ifdef JIEKE_PANNEL_GK3800      
        WaitIopFunRdy(IOP_RDY_WAIT);
#endif
    }

    #if defined(POWER_OFF_SHOW)&&defined(TONIC_DVD)||defined(KENLOON_DVD)//20040206
    while(power_timer){power_timer--;}  
    if (system_state==SYSTEM_POWER||play_state==VCD_STATE_POWER)
    {
        erase_vfd_mem();
        mem_count = VFD_DISPLAY_SIZE;   //2001/10/23    
        for(i = 0; i < mem_count; i += 6)
        {       
            #if (VFD_DRIVER==NEC16312) 
            regs0->iop_data[VFD_CMD] = (0xc0 | i);
            #elif (VFD_DRIVER==HT1621)  //in ht1621 it don't send write cmd
            regs0->iop_data[VFD_CMD]=(i*2);
            #else //for spl10
            regs0->iop_data[VFD_CMD]=(0xA0 | i);
            #endif
            regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
            regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
            regs0->iop_data[VFD_DAT2] = vfd_mem[i + 5] << 8 | vfd_mem[i + 4];       
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
            (FUN_VFD_WRITE | VFD_DAT_LEN6);     
            WaitIopFunRdy(IOP_RDY_WAIT);
        }
    }
    #endif//#if defined(POWER_OFF_SHOW)&&defined(TONIC_DVD)//20040206

    
}
#else//SUPPORT_VFD
void init_vfd_clear(void)
{

}
#endif//SUPPORT_VFD


/*
** FUNCTION
** reset_vfd
**
** DESCRIPTION
** setup VFD.  Should only called at power-up or emergency.
*/
#ifdef SUPPORT_VFD//nono 20031124

#if (VFD_DRIVER==NEC16312)  //for nec16312 reset use

void reset_vfd(void)
{

    UINT16 nIndex = 0;

    init_vfd_clear();

    /* display mode ? 13d15s or 6d16s add by chichang 2001/6/6 */
    
    
#ifndef TEST_VFD                                //shawn modify at 910131
    regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | VFD_DISPLAY_MODE;    //2001/10/23
#else
    regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | COMMAND_MODE;    //2002/01/31
#endif

    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
        (FUN_VFD_WRITE | VFD_DAT_LEN0);
    
    //erase_vfd_mem();
    
    WaitIopFunRdy(IOP_RDY_WAIT);
    
#if 0 //def BBK_DVD    //fengjl mark it 3-12-19 22:37      //in order to light the STB-led when power-on-sleep, hq, 3-12-1 20:57
    regs0->iop_data[VFD_CMD] =
        VFDC_DISP_CTRL | VFDC_DISP_CTRL_ON | VFDC_DISP_CTRL_10_16;
    
    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
        (FUN_VFD_WRITE | VFD_DAT_LEN0);
#endif      
#if 0//ndef KSD_PANEL_2
    regs0->iop_data[VFD_CMD] =
        VFDC_DISP_CTRL | VFDC_DISP_CTRL_ON | VFDC_DISP_CTRL_10_16;
    
    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
        (FUN_VFD_WRITE | VFD_DAT_LEN0);
#endif

#ifdef USE_VFD_LED_POWER
#if defined(USE_VFD_LED_POWER_LOW)&&!defined(VFD_SHOW_LOAD_TOGGLE)
    write_vfd_led(0x0f);
#else   
    #ifdef  PROVIEW_DV_509  
    write_vfd_led(4);
    #else
        write_vfd_led(0);
    #endif  
#endif
#endif

#ifdef TONIC_DVD//20040206
write_vfd_led(0);
#endif//TONIC_DVD

//nono2003-8-8 7:54
    //vfd_set_toc_state(nIndex);
    vfd_set_idle_state(nIndex);
    WaitIopFunRdy(IOP_RDY_WAIT);

}

#elif (VFD_DRIVER==HT1621)

void reset_vfd(void)   //for ht1621 init 
{
    //#ifdef SUPPORT_VFD
    
    
    
    /* display mode ? 13d15s or 6d16s add by chichang 2001/6/6 */
    /*i want use arry and for statement to send init command
    but it's something wrong,so only do this.
    */
    regs0->iop_data[VFD_CMD]=(SYS_EN<<4);   
    //regs0->iop_data[VFD_CMD]
    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
        (FUN_VFD_WRITE | VFD_DAT_LEN0);
    WaitIopFunRdy(IOP_RDY_WAIT); 
    regs0->iop_data[VFD_CMD]=(TIMER_DIS<<4);    
    //regs0->iop_data[VFD_CMD]
    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
        (FUN_VFD_WRITE | VFD_DAT_LEN0);
    WaitIopFunRdy(IOP_RDY_WAIT);
    regs0->iop_data[VFD_CMD]=(WDT_DIS<<4);  
    //regs0->iop_data[VFD_CMD]
    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
        (FUN_VFD_WRITE | VFD_DAT_LEN0);
    WaitIopFunRdy(IOP_RDY_WAIT);
    regs0->iop_data[VFD_CMD]=(BIAS_1_3<<4); 
    //regs0->iop_data[VFD_CMD];
    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
        (FUN_VFD_WRITE | VFD_DAT_LEN0);
    WaitIopFunRdy(IOP_RDY_WAIT);
    regs0->iop_data[VFD_CMD]=(LCD_ON<<4);   
    //regs0->iop_data[VFD_CMD];
    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
        (FUN_VFD_WRITE | VFD_DAT_LEN0);
    WaitIopFunRdy(IOP_RDY_WAIT);                    
    init_vfd_clear();     
    
}
#elif (VFD_DRIVER==PT6554)//LIJD 2004-3-6 18:58

void reset_vfd(void)  
{
    init_vfd_clear();
    WaitIopFunRdy(IOP_RDY_WAIT);
    #ifdef YADAI_PT6554_PANNEL
    vfd_set_str(0, "HELLO");
    #endif
}
#else       //for spl10 init use

void reset_vfd(void)
{
    init_vfd_clear();
    regs0->iop_data[VFD_CMD]=(SPL10_DUTY_BIAS); 
    //regs0->iop_data[VFD_CMD]
    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
        (FUN_VFD_WRITE | VFD_DAT_LEN0); 
    WaitIopFunRdy(IOP_RDY_WAIT);
    regs0->iop_data[VFD_CMD]=(SPL10_KEY_MODE);  
    //regs0->iop_data[VFD_CMD]
    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
        (FUN_VFD_WRITE | VFD_DAT_LEN0);     
    WaitIopFunRdy(IOP_RDY_WAIT);    
}
#endif

#else//SUPPORT_VFD
void reset_vfd(void)
{

}
#endif//SUPPORT_VFD

#if 0
//remove to vfdr.c
/*
** FUNCTION
** reset_vfd_again
**
** DESCRIPTION
*/
void reset_vfd_again(void)
{
    
    //    init_vfd_clear();
    
#ifndef TEST_VFD                                //shawn modify at 910131
    regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | VFD_DISPLAY_MODE;    //2001/10/23
#else
    regs0->iop_data[VFD_CMD] = VFDC_SET_DISP | COMMAND_MODE;    //2002/01/31
#endif
    
    
    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
        (FUN_VFD_WRITE | VFD_DAT_LEN0);
    WaitIopFunRdy(IOP_RDY_WAIT);
    
    regs0->iop_data[VFD_CMD] =
        VFDC_DISP_CTRL | VFDC_DISP_CTRL_ON | VFDC_DISP_CTRL_10_16;
    
    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
        (FUN_VFD_WRITE | VFD_DAT_LEN0);
    
}
#endif


/*
** FUNCTION
** erase_vfd_mem
**
** DESCRIPTION
** clear vfd memory.
*/


void erase_vfd_mem(void)
{
#ifdef SUPPORT_VFD
    unsigned i;
    
    #if defined(SUPPORT_VFD_SHOW_P_SCAN)&&defined(TONIC_DVD)//20040206
    if(vfd_intr_timer)
    return;
    #endif  

    for(i = 0; i < VFD_MEM_LEN; i++)
    {
        vfd_mem[i] = 0;
    }
    //vfd_enable=VFD_CNT; //zhyf  1-4-27 9:14
#endif
}


void vfd_dot(UINT32 method, UINT32 p)
{

    UINT32  A = p >> 3;
    UINT32  tag = 1 << (p & 0x07);
    BYTE   *ptr = &vfd_mem[A];
    BYTE    x = *ptr;
    
    if(method == 0)
        x |= tag;
    else if(--method == 0)
        x &= ~tag;
    else
        x ^= tag;
    
    *ptr = x;
}




#if 0

#if VFD_MODULE == FUT_6_BT_269GK1
#include "vfd_shift.c"
#elif VFD_MODULE == HT1611_LCD
#include "vfd_shift.c"
#elif VFD_MODULE == HT1621_LCD
#ifdef HT1621_LCDX                          //zhyf 2001/04/27
#include "vfdhtx.c"
#else
#include "vfdht.c"
#endif
#else
#include "vfd_noshift.c"
#endif

#endif

//
//    LED: 
//
//    MSB   LSB
//    ---- 0000  turn on all led
//    ---- 1111  turn off all led
//
#if (VFD_DRIVER==NEC16312)//lijinhia  because in nec16312 can use vfd io
void write_vfd_led(UINT8 led_id)
{
    regs0->iop_data[VFD_CMD] = 0x41;
    regs0->iop_data[VFD_DAT0] = 0xff00 | led_id;
    regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) | (FUN_VFD_WRITE | VFD_DAT_LEN1);
    WaitIopFunRdy(IOP_RDY_WAIT);
}
#endif

#if (VFD_DRIVER==HT1621)
void write_vfd_led(UINT8 led_id)
{
}
#endif
//gpio_keylight_init() move to gpio.c//nono 3-8-18 15:16
#if defined(USE_GAMEPORT_TO_BUTTON)
/*
void init_button_io(void)
{
    //regs0->gpio_master[56/16] |=0x2<<(56%16);
    regs0->gpio_master[4 / 16] |= (0xf << (4 % 16));    // gpio[4~7]
    //   game           gpio     IN/OUT(for 720)
    //   CLK        gpio4       IN
    //   LATCH          gpio5       IN
    //   D0         gpio6       IN
    //   D1         gpio7       IN
    //regs0->gpio_oe[56/16] &= ~0x2<<(56%16); 
    regs0->gpio_oe[4 / 16] &= (~0xf << (4 % 16));
    //printf("regs0->gpio_oe[0]=%x\n", regs0->gpio_oe[0]);
}
#elif defined(OURMIND_VFDPORT_TO_BUTTON)
void init_button_io_ourmind(void)                 //gerry  use 8 gpio ports (4~11) as buttons  2-11-14 22:27
{
    //regs0->gpio_master[56/16] |=0x2<<(56%16);
    regs0->gpio_master[4 / 16] |= (0xff << (4 % 16));   // gpio[4~7]
    
    regs0->gpio_master[56/ 16] |= (0x1 << (56 % 16));   // gpio[56]     gerry 2-11-29 9:58

    //regs0->gpio_oe[56/16] &= ~0x2<<(56%16); 
    regs0->gpio_oe[4 / 16] &= (~(0xff << (4 % 16)));
    
    regs0->gpio_oe[56 / 16] |= (0x1 << (56 % 16));
    regs0->gpio_out[56 / 16] |= (0x1 << (56 % 16));
    //printf("regs0->gpio_oe[0]=%x\n", regs0->gpio_oe[0]);
}
#elif defined(USE_GAMEPORT_TO_DISCLIGHT)
void init_light_io_out(void)
{
    
    regs0->gpio_master[56 / 16] |= (0x7 << (56 % 16));  // gpio[56~58]
    //   vfd          gpio     IN/OUT(for 720)
    //   DATA        gpio56       OUT
    //   STB         gpio57       OUT
    //   CLK         gpio58       OUT
    
    
    regs0->gpio_oe[56 / 16] |= (0x7 << (56 % 16));
    regs0->gpio_out[56 / 16] |= (0x7 << (56 % 16));
    
    //printf("1.regs0->gpio_out[3]=%x\n", regs0->gpio_out[3]);
}

#elif defined(USE_VFDPORT_TO_BUTTON)
void init_keyboard_io(void)
{
    //regs0->gpio_master[4 / 16] |= (0x3 << (4 % 16));  // gpio[4~5]
    //   game           gpio     IN/OUT(for 720)
    //   CLK        gpio4          OUT
    //   LATCH          gpio5      OUT
    //regs0->gpio_oe[56/16] &= ~0x2<<(56%16); 
    //regs0->gpio_oe[4 / 16] |= (0x3 << (4 % 16));
    regs0->gpio_master[10 / 16] |= (0x3 << (10 % 16));  // gpio[10~11]
    regs0->gpio_oe[10 / 16] |= (0x3 << (10 % 16));
    
    regs0->gpio_master[56 / 16] |= (0x7 << (56 % 16));  // gpio[56~58]
    //   vfd          gpio     IN/OUT(for 720)
    //   DATA        gpio56       IN
    //   STB         gpio57       IN
    //   CLK         gpio58       IN
    
    
    regs0->gpio_oe[56 / 16] &= (~0x7 << (56 % 16));
    
    //printf("1.regs0->gpio_out[3]=%x\n", regs0->gpio_out[3]);
}
#elif defined(USE_VFDPORT_TO_KEYLIGHT)
void init_keylight_io(void)
{
    regs0->gpio_master[56 / 16] |= (0x7 << (56 % 16));  // gpio[56~58]
    //   vfd          gpio     IN/OUT(for 720)
    //   DATA        gpio56       IN/OUT
    //   STB         gpio57       IN/OUT
    //   CLK         gpio58       IN/OUT
    
    
    //regs0->gpio_oe[56 / 16] &= (~0x7 << (56 % 16));
    
    //printf("1.regs0->gpio_out[3]=%x\n", regs0->gpio_out[3]);
}

*/
#endif

#if defined(USE_GAMEPORT_TO_BUTTON)
/*
void check_key_status(void)
{
    UINT16  key_data;
    static int key_state = 0;
    static UINT16 key_previ = 0xf0;
    
    key_data = (regs0->gpio_in[4 / 16] & (0xf << (4 % 16)));
    
    //           printf("key_data=%x\n",key_data);
    //           printf("key_state=%x\n",key_state);
    //           printf("key_previ=%x\n",key_previ);
    
    
    if(key_data == key_previ)
    {
        //printf("1.key_previ=%x\n",key_previ);
        //key_previ = 0xf0;
        switch (key_data)
        {
        case 0x70://GAME D1
            //printf("Ppppppp:key_state=%x\n",key_state);
            if(key_state == 2)
            {
                //printf("PAUSEPLAY\n");
                
                if(Is_JPEG_SlideMode())
                {
                    if(bJpgVFDPause == 0)
                    {
                        //bJpgVFDPause = 1;
                        if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
                            bJpgVFDPause = 2;
                        else
                            bJpgVFDPause = 1;
                    }
                    else if(bJpgVFDPause == 1)
                    {
                        bJpgVFDPause = 2;
                    }
                }
                else
                    call_ir_func(IRC_PAUSEPLAY);
                
            }
            //printf("P:key_state=%x\n",key_state);
            key_state = 1;
            break;
        case 0xd0://GAME LATCH
            if(key_state == 2)
            {
                printf("STOP\n");
                call_ir_func(IRC_STOP);
            }
            //printf("SS:key_state=%x\n",key_state);
            key_state = 1;
            break;
        case 0xb0://GAME D0
            if(key_state == 2)
            {
                call_ir_func(IRC_EJECT);
                printf("EJECT\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;
        default:
            key_state = 2;
            break;
        }
    }
    else
    {
        //printf("out:key_state=%x\n",key_state);
        key_previ = key_data;
        key_state = 2;
    }                                                           //if(key_data==key_previ) else ........
    
}

#elif defined(OURMIND_VFDPORT_TO_BUTTON)      //gerry  use 8 gpio ports (4~11) as buttons  2-11-14 22:27
void check_key_status_ourmind(void)
{
    UINT32  key_data;
    static int key_state = 0;   
    static UINT32 key_previ = 0xffff;
    
    key_data = (regs0->gpio_in[4 / 16] & (0xff << (4 % 16)));
    
    //         printf("key_data=%x\n",key_data);
    //         printf("key_state=%x\n",key_state);
    //         printf("key_previ=%x\n",key_previ);
    
    
    if(key_data == key_previ)
    {
        //printf("1.key_previ=%x\n",key_previ);
        //key_previ = 0xf0;
        switch (key_data)
        {
        case 0xbf0://GAME D1
            //printf("Ppppppp:key_state=%x\n",key_state);
            if(key_state == 2)
            {
                //printf("PAUSEPLAY\n");
                
                if(Is_JPEG_SlideMode())
                {
                    if(bJpgVFDPause == 0)
                    {
                        //bJpgVFDPause = 1;
                        if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
                            bJpgVFDPause = 2;
                        else
                            bJpgVFDPause = 1;
                    }
                    else if(bJpgVFDPause == 1)
                    {
                        bJpgVFDPause = 2;
                    }
                }
                else
                    printf("this is vfd board\n");
                    call_ir_func(IRC_PLAY_RESUME);
                
            }
            //printf("P:key_state=%x\n",key_state);
            key_state = 1;
            break;
        case 0xfd0://GAME LATCH
            if(key_state == 2)
            {
                printf("STOP\n");
                call_ir_func(IRC_STOP);
            }
            //printf("SS:key_state=%x\n",key_state);
            key_state = 1;
            break;
        case 0x7f0://GAME D0
            if(key_state == 2)
            {
                call_ir_func(IRC_EJECT);
                printf("EJECT\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;
        case 0xdf0://GAME 
            if(key_state == 2)
            {
                call_ir_func(IRC_NEXT);
                printf("NEXT\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;  
        case 0xfe0://GAME 
            if(key_state == 2)
            {
                call_ir_func(IRC_POWER);
                printf("POWER\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;
        case 0xfb0://GAME 
            if(key_state == 2)
            {
                call_ir_func(IRC_BACKWARD);
                printf("BACKWARD\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;
        case 0xf70://GAME 
            if(key_state == 2)
            {
                call_ir_func(IRC_FORWARD);
                printf("FORWARD\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;  
        case 0xef0://GAME 
            if(key_state == 2)
            {
                call_ir_func(IRC_PREV);
                printf("PREV\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;  
        default:
            key_state = 2;
            break;
        }
    }
    else
    {
        //printf("out:key_state=%x\n",key_state);
        key_previ = key_data;
        key_state = 2;
    }                                                           //if(key_data==key_previ) else ........
    
}

void check_ourmind_light_status(void)
{
    if((system_state==SYSTEM_POWER)&&(play_state==VCD_STATE_POWER)) 
        {
            regs0->gpio_out[56 / 16] &= ~(0x1 << (56 % 16));
        //regs0->gpio_out[56 / 16] |=  (0x1 << (56 % 16));  
        }
    else 
        {
        regs0->gpio_out[56 / 16] |=  (0x1 << (56 % 16));    
        }
}   


#elif defined(USE_GAMEPORT_TO_DISCLIGHT)
void check_light_status(void)
{
    
    if( (cd_type_loaded==CDDA)||(cd_type_loaded==CDVCD10)||(cd_type_loaded==CDVCD20) )
    {
        
        regs0->gpio_out[56 / 16] &= ~(0x1 << (56 % 16));
        regs0->gpio_out[57 / 16] |= (0x1 << (57 % 16));
        regs0->gpio_out[58 / 16] |= (0x1 << (58 % 16));
        //printf("CDDA.regs0->gpio_out[3]=%x\n", regs0->gpio_out[3]);
    }
    else if(Is_JPEG_STATE()==1)
    {
        
        regs0->gpio_out[56 / 16] |= (0x1 << (56 % 16));
        regs0->gpio_out[57 / 16] &= ~(0x1 << (57 % 16));
        regs0->gpio_out[58 / 16] |= (0x1 << (58 % 16));
        
        //printf("DVD.regs0->gpio_out[3]=%x\n", regs0->gpio_out[3]);
    }
    else if(cd_type_loaded==CDDVD)
    {
        regs0->gpio_out[56 / 16] |= (0x1 << (56 % 16));
        regs0->gpio_out[57 / 16] |= (0x1 << (57 % 16));
        regs0->gpio_out[58 / 16] &= ~(0x1 << (58 % 16));
        
        //printf("JPG.regs0->gpio_out[3]=%x\n", regs0->gpio_out[3]);
    }
    else
    {
        regs0->gpio_out[58 / 16] |= (0x7 << (56 % 16));
        //printf("NONE.regs0->gpio_out[3]=%x\n", regs0->gpio_out[3]);
    }
    
}   

#elif defined(USE_VFDPORT_TO_BUTTON)
void check_keyboard_status(void)
{
    UINT32  key_data,key_data2;
    static int key_state = 0,key_state2 = 0;
    static UINT32 key_previ = 0xfff,key_previ2 = 0xfff;
    
    //regs0->gpio_out[5 / 16] |= (0x1 << (5 % 16));
    regs0->gpio_out[11 / 16] |= (0x1 << (11 % 16));
    //regs0->gpio_out[4 / 16] &= (~0x1 << (4 % 16));
    regs0->gpio_out[10 / 16] &= (~(0x1 << (10 % 16)));
    key_data = (regs0->gpio_in[56 / 16] & (0x7 << (56 % 16)));
    
    //printf("key_data=%x\n",key_data);
    //           printf("key_state=%x\n",key_state);
    //           printf("key_previ=%x\n",key_previ);
    //return;
    if((Is_JPEG_SlideMode()) && (key_data == 0x300))
    {
        //Jeff 20020523
        bJpgVFDPause = 1;
    }
    else if(key_data2==0x601)
    {
        //bJpgVFDPause=0;
        bJpgVFDPause = 2;           //Jeff 20020525
    }
    
    
    
    //regs0->gpio_out[5 / 16] &= (~0x1 << (5 % 16));
    regs0->gpio_out[11 / 16] &= (~(0x1 << (11 % 16)));
    //regs0->gpio_out[4 / 16] |= (0x1 << (4 % 16));
    regs0->gpio_out[10 / 16] |= (0x1 << (10 % 16));
    key_data2 = (regs0->gpio_in[56 / 16] & (0x7 << (56 % 16)))|0x1;
    
    if(key_data == key_previ)
    {
        //printf("1.key_previ=%x\n",key_previ);
        //key_previ = 0xf0;
        switch (key_data)
        {
        case 0x300://GAME D1
            //printf("Ppppppp:key_state=%x\n",key_state);
            if(key_state2 == 2)
            {
                
                printf("PAUSE\n");
                call_ir_func(IRC_PAUSE);
                
            }
            //printf("P:key_state=%x\n",key_state);
            key_state = 1;
            break;
        case 0x500://GAME LATCH
            if(key_state2 == 2)
            {
                printf("BACKWARD\n");
                //call_ir_func(IRC_BACKWARD);
                call_ir_func(IRC_PREV);
            }
            //printf("SS:key_state=%x\n",key_state);
            key_state2 = 1;
            break;
        case 0x600://GAME D0
            if(key_state2 == 2)
            {
                call_ir_func(IRC_EJECT);
                printf("EJECT\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state2 = 1;
            break;
            
            
        default:
            key_state = 2;
            break;
        }
    }
    else
    {
        //printf("out:key_state=%x\n",key_state);
        key_previ = key_data;
        key_state = 2;
    }                                                           //if(key_data==key_previ) else ........
    
    
    //printf("key_data2=%x\n",key_data2);
    
    if(key_data2 == key_previ2)
    {
        //printf("1.key_previ=%x\n",key_previ);
        //key_previ = 0xf0;
        switch (key_data2)
        {
        case 0x601://GAME D1
            //printf("Ppppppp:key_state=%x\n",key_state);
            if(key_state == 2)
            {
                //printf("PAUSEPLAY\n");
                
                call_ir_func(IRC_PLAY_RESUME);
                
            }
            //printf("P:key_state=%x\n",key_state);
            key_state = 1;
            break;
        case 0x301://GAME LATCH
            if(key_state == 2)
            {
                printf("STOP\n");
                call_ir_func(IRC_STOP);
            }
            //printf("SS:key_state=%x\n",key_state);
            key_state = 1;
            break;
        case 0x501://GAME D0
            if(key_state == 2)
            {
                //call_ir_func(IRC_FORWARD);
                call_ir_func(IRC_NEXT);
                printf("FORWARD\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;
        default:
            key_state2 = 2;
            break;
        }
    }
    else
    {
        //printf("out:key_state=%x\n",key_state);
        key_previ2 = key_data2;
        key_state2 = 2;
    }
    
}

#elif defined(USE_VFDPORT_TO_KEYLIGHT)

void check_keylight_light_status(void)
{
    regs0->gpio_oe[56 / 16] |= (0x7 << (56 % 16));
    regs0->gpio_out[56 / 16] |= (0x7 << (56 % 16));
    //  printf("LIGHT.regs0->gpio_out[3]=%x\n", regs0->gpio_out[3]);
    //printf("play_state=%x\n",play_state);
    if( (cd_type_loaded)&&(play_state!=VCD_STATE_STOP) )
    {
        regs0->gpio_out[56 / 16] |= (0x1 << (56 % 16));
        regs0->gpio_out[57 / 16] &= (~(0x1 << (57 % 16)));
        regs0->gpio_out[58 / 16] |= (0x1 << (58 % 16));
        
        //      printf("PLAY.regs0->gpio_out[3]=%x\n", regs0->gpio_out[3]);
    }else   
        if( play_state==VCD_STATE_STOP)
        {
            
            regs0->gpio_out[56 / 16] &= (~(0x1 << (56 % 16)));
            regs0->gpio_out[57 / 16] &= (~(0x1 << (57 % 16)));
            regs0->gpio_out[58 / 16] |= (0x1 << (58 % 16));
            //      printf("STOP.regs0->gpio_out[3]=%x\n", regs0->gpio_out[3]);
        }
        
        else
        {
            regs0->gpio_out[56 / 16] &= (~(0x1 << (56 % 16)));
            regs0->gpio_out[57 / 16] |= (0x1 << (57 % 16));
            regs0->gpio_out[58 / 16] |= (0x1 << (58 % 16));
            
            //      printf("IDLE.regs0->gpio_out[3]=%x\n", regs0->gpio_out[3]);
        }
        
}   


void check_keylight_status(void)
{
    UINT32  key_data,key_data2;
    static int key_state = 0,key_state2 = 0;
    static UINT32 key_previ = 0xfff,key_previ2 = 0xfff;
    
    
    regs0->gpio_oe[56 / 16] &= (~0x1 << (56 % 16));
    regs0->gpio_oe[57 / 16] &= (~0x1 << (57 % 16));
    regs0->gpio_oe[58 / 16] &= (~0x1 << (58 % 16));
    key_data = (regs0->gpio_in[56 / 16] & (0x7 << (56 % 16)));
    
    //           printf("key_data=%x\n",key_data);
    //           printf("key_state=%x\n",key_state);
    //           printf("key_previ=%x\n",key_previ);
    
    
    if(key_data == key_previ)
    {
        //printf("1.key_previ=%x\n",key_previ);
        //key_previ = 0xf0;
        switch (key_data)
        {
            
        case 0x300://GAME D0
            if(key_state == 2)
            {
                call_ir_func(IRC_EJECT);
                printf("EJECT\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            
            break;
        default:
            key_state = 2;
            break;
        }
    }
    else
    {
        //printf("out:key_state=%x\n",key_state);
        key_previ = key_data;
        key_state = 2;
        
    }//if(key_data==key_previ) else ........
    
    
    regs0->gpio_oe[56 / 16] &= (~0x1 << (56 % 16));
    regs0->gpio_oe[58 / 16] |= (0x1 << (58 % 16));
    regs0->gpio_oe[57 / 16] &= (~0x1 << (57 % 16));
    regs0->gpio_out[58 / 16] &= (~0x1 << (58 % 16));
    
    key_data2 =( (regs0->gpio_in[56 / 16] & (0x1 << (56 % 16)))|(regs0->gpio_in[57 / 16] & (0x1 << (57 % 16))) );
    
    //           printf("key_data2=%x\n",key_data2);
    //           printf("gpio_out[3]=%x\n",regs0->gpio_in[56 / 16]);
    //           printf("key_state=%x\n",key_state);
    //           printf("key_previ=%x\n",key_previ);
    check_keylight_light_status();
    
    if(key_data2 == key_previ2)
    {
        //printf("1.key_previ=%x\n",key_previ);
        //key_previ = 0xf0;
        switch (key_data2)
        {
        case 0x100://GAME D1
            //printf("Ppppppp:key_state2=%x\n",key_state2);
            if(key_state2 == 2)
            {
                //printf("PAUSEPLAY\n");
                
                if(Is_JPEG_SlideMode())
                {
                    if(bJpgVFDPause == 0)
                    {
                        //bJpgVFDPause = 1;
                        if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
                            bJpgVFDPause = 2;
                        else
                            bJpgVFDPause = 1;
                    }
                    else if(bJpgVFDPause == 1)
                    {
                        bJpgVFDPause = 2;
                    }
                }
                else
                    call_ir_func(IRC_PLAY);
                
            }
            
            key_state2 = 1;
            check_keylight_light_status();
            break;
        case 0x200://GAME LATCH
            if(key_state2 == 2)
            {
                printf("STOP\n");
                call_ir_func(IRC_STOP);
            }
            
            key_state2 = 1;
            break;
            
        default:
            key_state2 = 2;
            break;
        }
    }
    else
    {
        //printf("out:key_state2=%x\n",key_state2);
        key_previ2 = key_data2;
        key_state2 = 2;
    }//if(key_data==key_previ) else ........
    check_keylight_light_status();
    
    
}
*/
#elif defined(PCM1742)&&defined(CHECK_DAC_ZERO_FLAG_TO_GPIO_MUTE)       //gerry,3-10-20 11:36

void check_pcm1742_zero_flag(void)
{
    //printf("============= come here to mute=============\n");
    
    if((GPIO_I_GET(14))&&(setup_IsMICOff()))
    {
        //mute
        //printf("=== mute ======\n");
        GPIO_MUTE();
    }
    else
    {   
        //de-mute
        //printf("============= de mute=============\n");
        GPIO_DEMUTE();
    }
}

#elif defined(GPIO_KEY_LIGHT)

    //   DATA        gpio56       IN/OUT
    //   STB         gpio57       IN/OUT
    //   CLK         gpio58       IN/OUT
void check_gpio_keylight_status(void)
{
#if defined(USE_VFDPORT_TO_KEYLIGHT_GBM)
check_gbm_keylight_status();
#elif defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ)
check_hj_keylight_status();
#elif defined(USE_VFDPORT_TO_KEYLIGHT_MINTON)
check_minton_keylight_status();
#elif defined(USE_VFDPORT_TO_KEYLIGHT_IDALL)
check_idall_keylight_status();
#elif defined(VFD_GPIO_KEY)
check_syber_key_status();
#elif defined(HANYANG_SCAN_KEY)
check_hanyang_keylight_status();  //caoh 2004-4-19 11:30
#elif defined(NINTAUS_612_SCAN_KEY) //linrc add 2004-6-7 15:25
vfdIO_scan_6key();
#endif
}

#if defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ)

#ifdef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_2326

void check_hj_keylight_status(void)
{

    UINT32  key_data;
    UINT32  key_data1;
    UINT32  key_data2;
//  UINT32  key_data3;
    static int key_state = 0;
    static UINT32 key_previ = 0xffff;
    
//  regs0->gpio_oe[54 / 16] &= ~(0x7 << (54 % 16));
//  regs0->gpio_oe[42 / 16] &= ~(0x3 << (42 % 16));

    //key_data = ((regs0->gpio_in[42 / 16] & (0x3 << (42 % 16))) |(regs0->gpio_in[54 / 16] & (0x7 << (54 % 16))) );
    //key_data =(( regs0->gpio_in[42 / 16] & (0x3 << (42 % 16))) |(regs0->gpio_in[54 / 16] & (0x7 << (54 % 16))) );
    key_data1 = regs0->gpio_in[14 / 16] & (0x3 << (14 % 16));//14
    key_data2 = regs0->gpio_in[54 / 16] & (0x7 << (54 % 16));//6,7,8
//  key_data2 = regs0->gpio_in[4 / 16] & (0x1 << (4 % 16));//4
//  key_data3 = regs0->gpio_in[54 / 16] & (0x7 << (54 % 16));//6,7,8
    key_data =(key_data1|key_data2);//15,14,6,7,8
    
    //printf("key_data=%x\n",key_data);
    //return;
    //printf("regs0->sft_cfg6=%x\n",regs0->sft_cfg6);
    //printf("regs0->gpio_oe[14 / 16]=%x\n",regs0->gpio_oe[14 / 16] );

    //printf("key_state=%x\n",key_state);
    //printf("key_previ=%x\n",key_previ);
    //regs0->gpio_out[56 / 16] &= ~(0x1 << (56 % 16));



    if(key_data == key_previ)
    {
        //printf("1.key_previ=%x\n",key_previ);
        //key_previ = 0xf0;

        switch (key_data)
        {
        case 0x81C0:

            if(key_state == 2)
            {
                call_ir_func(IRC_EJECT);
                //printf("EJECT\n");
                        }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;

        case 0xc0c0:

            if(key_state == 2)
            {
                call_ir_func(IRC_ONLY_PAUSE);
                //printf("EJECT\n");
                        }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;

        case 0x40C0:

            if(key_state == 2)
            {
                call_ir_func(IRC_BACKWARD);
                //printf("EJECT\n");
                        }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;

        case 0x4180:

            if(key_state == 2)
            {
                call_ir_func(IRC_FORWARD);
                //printf("EJECT\n");
                        }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;


        case 0xc180://GPIO14 IO2//PIN109


            if(key_state == 2)
            {
                call_ir_func(IRC_PREV);
                //printf("EJECT\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;


        case 0xC140://VFD DATA


            if(key_state == 2)
            {
                //printf("STOP\n");
                call_ir_func(IRC_STOP);
            }
            //printf("SS:key_state=%x\n",key_state);
            key_state = 1;
            break;

        case 0xC100:


            if(key_state == 2)
            {
                call_ir_func(IRC_NEXT);
                //printf("EJECT\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;

        case 0x41C0:

            //printf("Ppppppp:key_state=%x\n",key_state);
            if(key_state == 2)
            {
                //printf("PAUSEPLAY\n");
                
                if(Is_JPEG_SlideMode())
                {
                    if(bJpgVFDPause == 0)
                    {
                        //bJpgVFDPause = 1;
                        if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
                        {
                            bJpgVFDPause = 2;
                            PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
                        }
                        else
                            bJpgVFDPause = 1;
                    }
                    else if(bJpgVFDPause == 1)
                    {
                        bJpgVFDPause = 2;
                    }
                }
                else
                    call_ir_func(IRC_PLAY);
                
            }
            //printf("P:key_state=%x\n",key_state);
            key_state = 1;
            break;

        default:
            key_state = 2;
            break;
        }
    }
    else
    {
        //printf("out:key_state=%x\n",key_state);
        key_previ = key_data;
        key_state = 2;
        
    }

    
}

#elif defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_2290)



void check_hj_keylight_status(void)
{
    UINT32  key_data;//,key_data2;
    static int key_state = 0;//,key_state2 = 0;
    static UINT32 key_previ = 0xfff;//,key_previ2 = 0xfff;
    
    
    
    regs0->gpio_oe[54 / 16] &= (~0x1 << (54 % 16));
    regs0->gpio_oe[55 / 16] &= (~0x1 << (55 % 16));
    regs0->gpio_oe[56 / 16] &= (~0x1 << (56 % 16));
    key_data = (regs0->gpio_in[54 / 16] & (0x7 << (54 % 16)));
    
               //printf("key_data=%x\n",key_data);
    //           printf("key_state=%x\n",key_state);
    //           printf("key_previ=%x\n",key_previ);
    
    
    if(key_data == key_previ)
    {
        //printf("1.key_previ=%x\n",key_previ);
        //key_previ = 0xf0;
        switch (key_data)
        {
            
        case 0x180://CLK GPIO54
            if(key_state == 2)
            {
                call_ir_func(IRC_EJECT);
                //printf("EJECT\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            
            break;
            
        case 0x140://STB GPIO55
            //printf("Ppppppp:key_state2=%x\n",key_state2);
            if(key_state == 2)
            {
                //printf("PAUSEPLAY\n");
                
                if(Is_JPEG_SlideMode())
                {
                    if(bJpgVFDPause == 0)
                    {
                        //bJpgVFDPause = 1;
                        if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
                        {
                            bJpgVFDPause = 2;
                            PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
                        }
                        else
                            bJpgVFDPause = 1;
                    }
                    else if(bJpgVFDPause == 1)
                    {
                        bJpgVFDPause = 2;
                    }
                }
                else
                    call_ir_func(IRC_PLAY);
                
            }
            
            key_state = 1;
            //check_keylight_light_status();
            break;
        case 0x0C0://DATA GPIO56
            if(key_state == 2)
            {
                //printf("STOP\n");
                call_ir_func(IRC_STOP);
            }
            
            key_state = 1;
            break;
        
        
        default:
            key_state = 2;
            break;
        }
    }
    else
    {
        //printf("out:key_state=%x\n",key_state);
        key_previ = key_data;
        key_state = 2;
        
    }//if(key_data==key_previ) else ........
    
    
    
}

    //dingzhy   3-11-17 11:02
#elif defined(USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313)

void CD_MP3_DVD_LIGHT_FOR_HJ( void )
{
 if(cd_type_loaded==CDDVD)
         {          GPIO_O_SET(3,1);
                    GPIO_O_SET(62,0);
                    GPIO_O_SET(63,1);
         }
else if(cd_type_loaded==CDROM)
     {
                GPIO_O_SET(3,0);
                    GPIO_O_SET(62,1);
                    GPIO_O_SET(63,1);
        }
else if(cd_type_loaded==CDDA || cd_type_loaded==CDVCD10 || cd_type_loaded==CDVCD20 || cd_type_loaded==CDSVCD)
     {
                GPIO_O_SET(3,1);
                    GPIO_O_SET(62,1);
                    GPIO_O_SET(63,0);
        }
else if(play_state == VCD_STATE_OPEN)
    {
                GPIO_O_SET(3,1);
                    GPIO_O_SET(62,1);
                    GPIO_O_SET(63,1);
        }
                
}


void check_hj_keylight_status(void)
{
    UINT32  key_data,key_data1,key_data2,key_data3,key_data4,key_data5;//,key_data2;
    static int key_state = 0;//,key_state2 = 0;
    static UINT32 key_previ = 0xfff;//,key_previ2 = 0xfff;
    
    
    key_data1 = (regs0->gpio_in[54 / 16] & (0x1 << (54 % 16)));
    key_data2 = (regs0->gpio_in[55 / 16] & (0x1 << (55 % 16)));
    key_data3 = (regs0->gpio_in[56 / 16] & (0x1 << (56 % 16)));
    key_data4 = (regs0->gpio_in[14 / 16] & (0x1 << (14 % 16)));
    key_data5 = (regs0->gpio_in[15 / 16] & (0x1 << (15 % 16)));
//  printf("key_data1=%x\n",key_data1);
//  printf("key_data2=%x\n",key_data2);
//  printf("key_data3=%x\n",key_data3);
    key_data =(key_data1|key_data2|key_data3|key_data4|key_data5);//15,14,6,7,8
    
    

//  printf("key_data=%x\n",key_data);
//  printf("key_previ=%x\n",key_previ);
    



    if(key_data == key_previ)
    {
        //printf("1.key_previ=%x\n",key_previ);
        //key_previ = 0xf0;

        switch (key_data)
        {
        case 0xc180:
#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY
            if(key_state == 2)
            {
                call_ir_func(IRC_STOP);
                
            }
            
            key_state = 1;
            break;
#else//USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY
            if(key_state == 2)
            {
                call_ir_func(IRC_BACKWARD);
                
            }
            
            key_state = 1;
            break; 
#endif//USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY

        case 0xc140:
#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY
            if(key_state == 2)
            {
                call_ir_func(IRC_BACKWARD);
                
            }
            
            key_state = 1;
            break; 
#else//#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY

            if(key_state == 2)
            {
                call_ir_func(IRC_FORWARD);
                
            }
            
            key_state = 1;
            break;  
#endif//#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY
        case 0xc0c0:
#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY
            if(key_state == 2)
            {
                call_ir_func(IRC_FORWARD);
                
            }
            
            key_state = 1;
            break;  
#else//#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY

            if(key_state == 2)
            {
                call_ir_func(IRC_DEFAULT_SETUP);
                
            }
            
            key_state = 1;
            break;  
#endif//#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY

        case 0x81c0:
#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY
               if(key_state == 2)   
                {        
                if(Is_JPEG_SlideMode())
                {
                    if( (bJpgVFDPause == 1)||(bJpgVFDPause == 0) )
                        {
                            bJpgVFDPause = 2;
                            PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
                        }
                }
                else
                    call_ir_func(IRC_PLAY); 
                    

                
               }                         
               key_state = 1;
            break;  
#else//#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY

            //printf("Ppppppp:key_state=%x\n",key_state);
            if(key_state == 2)
            {
                //printf("PAUSEPLAY\n");
                
                if(Is_JPEG_SlideMode())
                {
                    if(bJpgVFDPause == 0)
                    {
                        //bJpgVFDPause = 1;
                        if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
                        {
                            bJpgVFDPause = 2;
                            PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
                        }
                        else
                            bJpgVFDPause = 1;
                    }
                    else if(bJpgVFDPause == 1)
                    {
                        bJpgVFDPause = 2;
                    }
                }
                else
                    call_ir_func(IRC_PAUSEPLAY);
                
            }
            //printf("P:key_state=%x\n",key_state);
            key_state = 1;
            break;
#endif//#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY

        case 0x41c0:
#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY
               if(key_state == 2)            
              {          
                if(Is_JPEG_SlideMode())
                {
                bJpgVFDPause = 1;
                
                }else
                call_ir_func(IRC_ONLY_PAUSE);                        
              }                  
               key_state = 1;
            break;  
#else//#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY

            if(key_state == 2)
            {
                call_ir_func(IRC_STOP);
                
            }
            
            key_state = 1;
            break;
#endif//#ifndef USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_DP313_NEW_KEY

        case 0x1c0:

            if(key_state == 2)
            {
                call_ir_func(IRC_EJECT);
                
            }
            
            key_state = 1;
            break; 
        default:
            key_state = 2;
            break;  
               
       }
    }
        else
    {
        //printf("out:key_state=%x\n",key_state);
        key_previ = key_data;
        key_state = 2;
        
    }
//dingzhy  3-11-17 10:08
CD_MP3_DVD_LIGHT_FOR_HJ();


}


#else//USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_2326

void check_hj_keylight_status(void)
{

    UINT32  key_data;
    UINT32  key_data1;
    UINT32  key_data2;
//  UINT32  key_data3;
    static int key_state = 0;
    static UINT32 key_previ = 0xffff;
    
//  regs0->gpio_oe[54 / 16] &= ~(0x7 << (54 % 16));
//  regs0->gpio_oe[42 / 16] &= ~(0x3 << (42 % 16));

    //key_data = ((regs0->gpio_in[42 / 16] & (0x3 << (42 % 16))) |(regs0->gpio_in[54 / 16] & (0x7 << (54 % 16))) );
    //key_data =(( regs0->gpio_in[42 / 16] & (0x3 << (42 % 16))) |(regs0->gpio_in[54 / 16] & (0x7 << (54 % 16))) );
    key_data1 = regs0->gpio_in[14 / 16] & (0x3 << (14 % 16));//14
    key_data2 = regs0->gpio_in[54 / 16] & (0x7 << (54 % 16));//6,7,8
//  key_data2 = regs0->gpio_in[4 / 16] & (0x1 << (4 % 16));//4
//  key_data3 = regs0->gpio_in[54 / 16] & (0x7 << (54 % 16));//6,7,8
    key_data =(key_data1|key_data2);//15,14,6,7,8
    
    //printf("key_data=%x\n",key_data);
    //return;
    //printf("regs0->sft_cfg6=%x\n",regs0->sft_cfg6);
    //printf("regs0->gpio_oe[14 / 16]=%x\n",regs0->gpio_oe[14 / 16] );

    //printf("key_state=%x\n",key_state);
    //printf("key_previ=%x\n",key_previ);
    //regs0->gpio_out[56 / 16] &= ~(0x1 << (56 % 16));



    if(key_data == key_previ)
    {
        //printf("1.key_previ=%x\n",key_previ);
        //key_previ = 0xf0;

        switch (key_data)
        {
        case 0x81C0://GPIO15 IO1//PIN121


            if(key_state == 2)
            {
                call_ir_func(IRC_NEXT);
                //printf("EJECT\n");
                        }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;


        case 0x41C0://GPIO14 IO2//PIN109


            if(key_state == 2)
            {
                call_ir_func(IRC_PREV);
                //printf("EJECT\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;


        case 0xC0C0://VFD DATA


            if(key_state == 2)
            {
                //printf("STOP\n");
                call_ir_func(IRC_STOP);
            }
            //printf("SS:key_state=%x\n",key_state);
            key_state = 1;
            break;

        case 0xC180://VFD CLK


            if(key_state == 2)
            {
                call_ir_func(IRC_EJECT);
                //printf("EJECT\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            break;

        case 0xC140://VFD STB

            //printf("Ppppppp:key_state=%x\n",key_state);
            if(key_state == 2)
            {
                //printf("PAUSEPLAY\n");
                
                if(Is_JPEG_SlideMode())
                {
                    if(bJpgVFDPause == 0)
                    {
                        //bJpgVFDPause = 1;
                        if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
                        {
                            bJpgVFDPause = 2;
                            PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
                        }
                        else
                            bJpgVFDPause = 1;
                    }
                    else if(bJpgVFDPause == 1)
                    {
                        bJpgVFDPause = 2;
                    }
                }
                else
                    call_ir_func(IRC_PAUSEPLAY);
                
            }
            //printf("P:key_state=%x\n",key_state);
            key_state = 1;
            break;

        default:
            key_state = 2;
            break;
        }
    }
    else
    {
        //printf("out:key_state=%x\n",key_state);
        key_previ = key_data;
        key_state = 2;
        
    }

    
}

#endif//USE_VFD_GAME_PORT_TO_KEYBOARD_HJ_2326

#elif defined(USE_VFDPORT_TO_KEYLIGHT_GBM)
#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)
extern BYTE key_data_flag;
#endif//#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)
#ifdef NEW_GBM_VFD_GPIO_KEY             //gerry,2004/2/11 05:58下午
void check_gbm_keylight_status(void)
{

    UINT32  key_data;
    static int key_state = 0;
    static UINT32 key_previ = 0xfff;
    
    //init_keylight_io();
    regs0->gpio_oe[56 / 16] &= (~0x1 << (56 % 16));
    regs0->gpio_oe[54 / 16] &= (~0x1 << (54 % 16));
    regs0->gpio_oe[55 / 16] &= (~0x1 << (55 % 16));

    key_data = (regs0->gpio_in[54 / 16] & (0x7 << (54 % 16)));
    
/*
    psprintf(RegionValStr[REGION2], "KEY_DATA: %x", key_data);
    PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
    return;
*/
    
    if(key_data == key_previ)
    {
        //printf("1.key_previ=%x\n",key_previ);
        //key_previ = 0xf0;
        switch (key_data)
        {
        
        case 0x180:
        
            if(key_state == 2)
            {
                
                call_ir_func(IRC_PLAY);
                //printf("EJECT\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            
            break;
        case 0x140:
        
            if(key_state == 2)
            {

                /*if(Is_JPEG_SlideMode())
                {
                    if(bJpgVFDPause == 0)
                    {
                        //bJpgVFDPause = 1;
                        if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
                        {
                            bJpgVFDPause = 2;
                            PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
                            }
                        else
                            bJpgVFDPause = 1;
                    }
                    else if(bJpgVFDPause == 1)
                    {
                        bJpgVFDPause = 2;
                    }
                }
                else*/
                    #if 1//def DVD_SUOJIA_VFDPORT
                    call_ir_func(IRC_EJECT); //call_ir_func(IRC_PAUSEPLAY);//HHQ
                    #else
                    call_ir_func(IRC_EJECT);
                    #endif

            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            
            break;
        case 0xC0:
        
            if(key_state == 2)
            {
                call_ir_func(IRC_STOP);
                //printf("STOP\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            
            break;
        case 0x80:
        
            if(key_state == 2)
            {
                //gpio_key_only_next();
                //gpio_key_only_prev();
#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)
        key_data_flag=1;
#endif//#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)
                call_ir_func(IRC_PREV);
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            
            break;
        case 0x100:
        
            if(key_state == 2)
            {
                  //gpio_key_only_prev();
                  //gpio_key_only_next();
#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)
        key_data_flag=1;
#endif//#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)
                  call_ir_func(IRC_NEXT);
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            
            break;
        default:
            key_state = 2;
            break;
        }
    }
    else
    {
        //printf("out:key_state=%x\n",key_state);
        key_previ = key_data;
        key_state = 2;
#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)
        key_data_flag=0;
#endif//#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)  
    }

}

#else//NEW_GBM_VFD_GPIO_KEY
void check_gbm_keylight_status(void)
{

    UINT32  key_data;
    static int key_state = 0;
    static UINT32 key_previ = 0xfff;
    
    //init_keylight_io();
//  regs0->gpio_oe[56 / 16] |= (0x1 << (56 % 16));
    regs0->gpio_oe[54 / 16] &= (~0x1 << (57 % 16));
    regs0->gpio_oe[55 / 16] &= (~0x1 << (58 % 16));
//  regs0->gpio_out[58 / 16] &= ~(0x1 << (58 % 16));
//  return;
    key_data = (regs0->gpio_in[54 / 16] & (0x3 << (54 % 16)));
    
    //printf("key_data=%x\n",key_data);
    //printf("key_state=%x\n",key_state);
    //printf("key_previ=%x\n",key_previ);
    //regs0->gpio_out[56 / 16] &= ~(0x1 << (56 % 16));

    regs0->gpio_oe[54 / 16] |= (0x7 << (54 % 16));
    regs0->gpio_out[56 / 16] &= ~(0x1 << (56 % 16));
    regs0->gpio_out[54 / 16] |= (0x3 << (54 % 16));
    
    if(key_data == key_previ)
    {
        //printf("1.key_previ=%x\n",key_previ);
        //key_previ = 0xf0;
        switch (key_data)
        {
        
        case 0x80:
        
            if(key_state == 2)
            {
                
                call_ir_func(IRC_EJECT);
                //printf("EJECT\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            
            break;
        case 0x00:
        
            if(key_state == 2)
            {
                safe_srn_off();
                save_srn_start_t = get_rtc_val();
                if(Is_JPEG_SlideMode())
                {
                    if(bJpgVFDPause == 0)
                    {
                        if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
                        {
                            bJpgVFDPause = 2;
							PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);
							return;
                            }
                        else
						{
                            bJpgVFDPause = 1;
                    }
					}
                    else if(bJpgVFDPause == 1)
                    {
                        bJpgVFDPause = 2;
						PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);
                    }
                }
                else
                    call_ir_func(IRC_PAUSEPLAY);
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            
            break;
        case 0x40:
        
            if(key_state == 2)
            {
                call_ir_func(IRC_STOP);
                //printf("STOP\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            
            break;
        default:
            key_state = 2;
            break;
        }
    }
    else
    {
        //printf("out:key_state=%x\n",key_state);
        key_previ = key_data;
        key_state = 2;
        
    }
    
    regs0->gpio_oe[54 / 16] |= (0x7 << (54 % 16));
    regs0->gpio_out[56 / 16] &= ~(0x1 << (56 % 16));
    regs0->gpio_out[54 / 16] |= (0x3 << (54 % 16));
    
}
#endif//NEW_GBM_VFD_GPIO_KEY

//Just for AKI keylight   fengjl  3-11-2 18:42
#if 0  
//#elif defined(USE_VFDPORT_TO_KEYLIGHT_GBM)
void check_gbm_keylight_status(void)
{

    UINT32  key_data;
    static int key_state = 0;
    static UINT32 key_previ = 0xfff;

    regs0->gpio_oe[54 / 16] &= (~0x1 << (54 % 16));
    regs0->gpio_oe[55 / 16] &= (~0x1 << (55 % 16));
    regs0->gpio_oe[56 / 16] &= (~0x1 << (56 % 16));

    key_data = (regs0->gpio_in[54 / 16] & (0x7 << (54 % 16)));
    
    //printf("key_data=%x\n",key_data);
    //printf("key_state=%x\n",key_state);
    //printf("key_previ=%x\n",key_previ);
        
    if(key_data == key_previ)
    {
        //printf("1.key_previ=%x\n",key_previ);
        //key_previ = 0xf0;
        switch (key_data)
        {
        
        case 0x180:
        
            if(key_state == 2)
            {
                
                call_ir_func(IRC_PLAY);
                //printf("EJECT\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            
            break;
        case 0xc0:
        
            if(key_state == 2)
            {
                if(Is_JPEG_SlideMode())
                {
                    
                    if(bJpgVFDPause == 0)
                    {
                        //bJpgVFDPause = 1;
                        if(play_state == VCD_STATE_PAUSE)   //nono 2-6-28 14:00
                        {
                            
                            bJpgVFDPause = 2;
                            PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
                            }
                        else
                            bJpgVFDPause = 1;
                    }
                    else if(bJpgVFDPause == 1)
                    {
                        bJpgVFDPause = 2;
                    }
                }
                else
                        call_ir_func(IRC_STOP);                 
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            
            break;
        case 0x140:
        
            if(key_state == 2)
            {
                call_ir_func(IRC_EJECT);
                //printf("STOP\n");
            }
            //printf("EEE:key_state=%x\n",key_state);
            key_state = 1;
            
            break;
        default:
            key_state = 2;
            break;
        }
    }
    else
    {
        //printf("out:key_state=%x\n",key_state);
        key_previ = key_data;
        key_state = 2;
        
    }
    
    regs0->gpio_oe[54 / 16] |= (0x7 << (54 % 16));
    regs0->gpio_out[56 / 16] &= ~(0x1 << (56 % 16));
    regs0->gpio_out[54 / 16] |= (0x3 << (54 % 16));
    
}
#endif

#elif defined(USE_VFDPORT_TO_KEYLIGHT_MINTON)

#if defined(MINTON_YILI_DVD1003_2CH)

void check_light_status(void)  
{

    static BYTE minton_led_flag;
    
    if( (play_state == VCD_STATE_STOP)||(play_state == VCD_STATE_OPEN)||(system_state == SYSTEM_NODISC) )
        GPIO_O_SET(14,0);//off
    else if( (play_state == VCD_STATE_READTOC)||(play_state == VCD_STATE_CLOSE) )
    {
        
        minton_led_flag++;      
        if(minton_led_flag<=10)
        {
            GPIO_O_SET(14,1);//on
        }
        else if( (minton_led_flag<=20)&&(minton_led_flag>10) )
            GPIO_O_SET(14,0);//off
            
        if(minton_led_flag==20)
            minton_led_flag=0;
        
    }
    else 
        GPIO_O_SET(14,1);//on
}

//*********************************************
#define SCAN_KEY_1  54
#define SCAN_KEY_2  55
#define SCAN_KEY_3  56  
void check_minton_keylight_status(void)
{
    static BYTE key_previ = 0xff;   //for debounce,2004-3-16 18:49
    BYTE  key_data = 0;             
    static int key_state = 0;       //a flag, 0:scan key, 1~15: free
    
    check_light_status();           //PLAY-LED blink when loading disk
    
    if(key_state<1)
    {   
        //use GPIO 54~56 as input port, scan panel-key, 2004-3-16 18:54
        GPIO_E_SET(SCAN_KEY_1, 0);      //0 for input.
        GPIO_E_SET(SCAN_KEY_2, 0);
        GPIO_E_SET(SCAN_KEY_3, 0);
        key_data =(GPIO_I_GET(SCAN_KEY_1)<<2)|(GPIO_I_GET(SCAN_KEY_2)<<1)|GPIO_I_GET(SCAN_KEY_3);
    }
    else
    {   
        key_data = 0x07;
    }

    key_state++;
    if(key_state==15)
        key_state = 0;
    
    ///////////////////////////////////////////////////2004-3-16 18:58
    //process the keys.
    
    if(key_data==0x07)//all three GPIO lines input HIGH. that is, no press any key.
    {
        //set GPIO 54~56 output LOW for three LEDs. 2004-3-16 18:54     
        GPIO_E_SET(SCAN_KEY_1, 1);
        GPIO_E_SET(SCAN_KEY_2, 1);
        GPIO_E_SET(SCAN_KEY_3, 1);

        GPIO_O_SET(SCAN_KEY_1, 0);
        GPIO_O_SET(SCAN_KEY_2, 0);
        GPIO_O_SET(SCAN_KEY_3, 0);
        return 0;
    }   
    
    #ifdef VFD_KEY_TEST
    psprintf(RegionValStr[REGION1], "KEY %02d", key_data);
    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);           
    return 0;
    #endif
    
    if(key_data==key_previ) 
    {
        key_previ= 0xff;
        switch (key_data)
        {
            case 0x05:  //PREV
                call_ir_func(IRC_PREV);          
                break;
                
            case 0x01:  //PAUSE              
                if(Is_JPEG_SlideMode())
                {
                    bJpgVFDPause = 1;
                    return;
                }else
                    call_ir_func(IRC_ONLY_PAUSE);   
                break;
                
            case 0x04:  //PLAY                   
                if(Is_JPEG_SlideMode())
                {
                    if( (bJpgVFDPause == 1)||(bJpgVFDPause == 0) )
                    {
                        bJpgVFDPause = 2;
                        PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
                    }
                }
                else
                    call_ir_func(IRC_PLAY_RESUME);  
                break;

            case 0x02:  //STOP                 
                call_ir_func(IRC_STOP);     
                break;

            case 0x06:  //NEXT                       
                call_ir_func(IRC_NEXT);     
                break; 
                  
            default:    
                break;
        }//end switch(key_data)
    }
    else//first check Gpio key state
    {
        key_previ=key_data;         
    }   
            return 0;
}
#elif defined(MINTON_YILI_LCD1003_6CH)//MINTON_YILI_DVD1003_2CH, 2004-3-19 22:39

void check_light_status(void)         /////alex 20040228
{   if(system_state!=SYSTEM_POWER)
    {
        GPIO_O_SET(14,0);//off
    }
    else 
    {
        GPIO_O_SET(14,1);//on   
    }
}

void check_minton_keylight_status(void)
{
    check_light_status();
}

#else//MINTON_YILI_DVD1003_2CH

void check_light_status(void)  
{

    static BYTE minton_led_flag;
    
    if( (play_state == VCD_STATE_STOP)||(play_state == VCD_STATE_OPEN)||(system_state == SYSTEM_NODISC) )
        GPIO_O_SET(14,0);//off
    else if( (play_state == VCD_STATE_READTOC)||(play_state == VCD_STATE_CLOSE) )
    {
        
        minton_led_flag++;      
        if(minton_led_flag<=10)
        {
            GPIO_O_SET(14,1);//on
        }
        else if( (minton_led_flag<=20)&&(minton_led_flag>10) )
            GPIO_O_SET(14,0);//off
            
        if(minton_led_flag==20)
            minton_led_flag=0;
        
    }
    else 
        GPIO_O_SET(14,1);//on
}

//******************************************
    //   DATA        gpio56       IN/OUT
    //   STB         gpio57       IN/OUT
    //   CLK         gpio58       IN/OUT
void check_minton_keylight_status(void)
{
    UINT32  key_data;
    static int key_state = 0;
    static UINT32 key_previ = 0xfff;
    static BYTE minton_key_flag;

    check_light_status();
    
if(minton_key_flag<3)
{
    regs0->gpio_oe[54 / 16] &= ~(0x7 << (54 % 16));
    
     
    key_data = regs0->gpio_in[54 / 16] & (0x7 << (54 % 16));
    //printf("key_data=%x\n",key_data);
    //printf("key_state=%x\n",key_state);
    //printf("key_previ=%x\n",key_previ);
    //regs0->gpio_out[56 / 16] &= ~(0x7 << (56 % 16));
    
    if(key_data == key_previ)
    {
        switch (key_data)
        {
        case 0x180:  //PREV
                   if(key_state == 2)            
                call_ir_func(IRC_PREV);                      
               key_state = 1;
                   break;
        case 0x100:  //PAUSE
                   if(key_state == 2)            
              {          
                if(Is_JPEG_SlideMode())
                {
                bJpgVFDPause = 1;
                
                }else
                call_ir_func(IRC_ONLY_PAUSE);                        
              }                  
               key_state = 1;
                   break;
        case 0x80:  //PLAY
                   if(key_state == 2)   
                   {         
                if(Is_JPEG_SlideMode())
                {
                    if( (bJpgVFDPause == 1)||(bJpgVFDPause == 0) )
                        {
                            bJpgVFDPause = 2;
                            PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);//nono 20030804
                        }
                }
                else
                    call_ir_func(IRC_PLAY_RESUME);                  
               }                         
               key_state = 1;
                   break;
        case 0x40:  //STOP
                   if(key_state == 2)
                call_ir_func(IRC_STOP); 
               key_state = 1;
                   break;
        case 0xC0:  //NEXT
                   if(key_state == 2)            
                call_ir_func(IRC_NEXT);                      
               key_state = 1;
                   break;           
                 
         
        default:
            key_state = 2;
            break;
        }
    }
    else
    {
        //printf("out:key_state=%x\n",key_state);
        key_previ = key_data;
        key_state = 2;
        
    }
}else if( (minton_key_flag>=3)&&(minton_key_flag<20) )//if(minton_key_flag<5)   
{
    regs0->gpio_oe[54 / 16] |= (0x7 << (54 % 16));
    regs0->gpio_out[54 / 16] &= ~(0x3 << (54 % 16));
    regs0->gpio_out[56 / 16] |= (0x1 << (56 % 16));
}   

    minton_key_flag++;
    if(minton_key_flag==20) minton_key_flag=0;

}
#endif//MINTON_YILI_DVD1003_2CH

//void check_light_status(void)               
//moved before  check_minton_keylight_status(), hq,2004-3-19 22:43
        
#elif defined(USE_VFDPORT_TO_KEYLIGHT_IDALL)
void check_idall_keylight_status(void)
{
    UINT32 key_data1=0, key_data2=0, key_data3=0;
    UINT32 key_data = 0;
    static UINT8 key_state = 0;
    static UINT32 key_prev = 0xffffffff;
    static UINT8 key_scan = 0;
    
    regs0->gpio_out[55/16] |= (0x1<<(55%16));
    regs0->gpio_out[56/16] &= ~(0x1<<(56%16));
    key_scan = 1;

    key_data1 = regs0->gpio_in[14 / 16] & (0x1 << (14 % 16));
    
    key_data2 = regs0->gpio_in[36 / 16] & (0x1 << (36 % 16));
    
    key_data3 = regs0->gpio_in[54 / 16] & (0x1 << (54 % 16));
    
    key_data = key_data1|key_data2|key_data3;

    if(key_data==0)
    {
        regs0->gpio_out[55/16] &= ~(0x1<<(55%16));
        regs0->gpio_out[56/16] |= (0x1<<(56%16));
        key_scan = 2;
        key_data1 = regs0->gpio_in[14 / 16] & (0x1 << (14 % 16));
    
        key_data2 = regs0->gpio_in[36 / 16] & (0x1 << (36 % 16));
        
        key_data3 = regs0->gpio_in[54 / 16] & (0x1 << (54 % 16));
        
       
        key_data = key_data1|key_data2|key_data3;
        
        if(key_data==0)
        {
            key_scan = 0;
        }
    }
    
    if(key_data==key_prev)
    {
        switch(key_data)
        {
            case 0x4000:
                if(key_state==2)
                {
                    if(key_scan ==1)
                    call_ir_func(IRC_PREV);
                    else if(key_scan==2)
                    call_ir_func(IRC_EJECT);
                }
                key_state = 1;
                break;
            case 0x0010:
                if(key_state==2)
                {
                    if(key_scan==1)
                    call_ir_func(IRC_NEXT);
                    else if(key_scan==2)
                    call_ir_func(IRC_CHANNEL);
                }
                key_state = 1;
                break;
            case 0x0040:
                if(key_state ==2)
                {
                    if(key_scan==1)
                    call_ir_func(IRC_PAUSEPLAY);
                    else if(key_scan==2)
                    call_ir_func(IRC_STOP);
                }
                key_state = 1;
                break;
            default:
                key_state = 2;
                break;
        }
        if(key_state==1)
        {
            UINT32 temp = 0;

            for(temp = 0;temp<0xffff;temp++)
            {
                regs0->gpio_out[55/16] &= ~(0x1<<(55%16));
                regs0->gpio_out[56/16] |= (0x1<<(56%16));
            }
            
        }
    }
    else
    {
        key_prev = key_data;
        key_state = 2;
    }
    regs0->gpio_out[55/16] |= (0x1<<(55%16));
    regs0->gpio_out[56/16] &= ~(0x1<<(56%16));
    
}

#endif//#if defined(USE_VFDPORT_TO_KEYLIGHT_GBM)

#if defined(VFD_GPIO_KEY)&&defined(SYBER_DVD)
UINT8 gpio_stb_level=0;
UINT8 gpio_data_level=0;
UINT8 old_gpio_stb_level=1;
UINT8 old_gpio_data_level=1;
void check_syber_key_status(void)
{
    regs0->gpio_master[55 / 16] |= (0x1 << (55 % 16));  
    regs0->gpio_oe[55/16] &= ~(1<<(55%16));  //input port

    regs0->gpio_master[56/ 16] |= (0x1 << (56 % 16));  
    regs0->gpio_oe[56/16] &= ~(1<<(56%16));  //input port
    
    gpio_data_level = GPIO_I_GET(OPEN_CLOSE_KEY);
    gpio_stb_level = GPIO_I_GET(PLAY_PAUSE_KEY);
    if(gpio_data_level == 0 && old_gpio_data_level !=0)
    {
        call_ir_func(0x0c);  //ircmd_eject_toggle()
          // old_gpio_stb_level = gpio_stb_level;
    }

    if(gpio_stb_level == 0 && old_gpio_stb_level !=0)
    {
        ircmd_play_pause();
        //   old_gpio_data_level = gpio_data_level;
    }
    old_gpio_stb_level = gpio_stb_level;
    old_gpio_data_level = gpio_data_level;

}

#endif

#endif//defined(GPIO_KEY_LIGHT)


///********VFD Volume display******** 
//wangfeng 2003-09-29 15:47
#ifdef  VFD_VOLUME_DISPLAY
UINT16 vfd_set_volume(UINT16 index)
{
    BYTE    iVolume;
        BYTE    idVolumeFont;
    erase_vfd_mem();
    
#ifdef  CNTR_5SPK_VOLUME
    if (volume_Switch>=0) {
            iVolume         = volume_5SPK[volume_Switch];
            idVolumeFont    = idVolume_5SPK[volume_Switch];
        } 
    else {
            iVolume         = audio_volume;
            idVolumeFont    = Volume_Font_ID;
        }
    if(idVolumeFont==VOL_FL_ID)
        psprintf(linebuf,"FL VOL%02d",iVolume);
    else if(idVolumeFont==VOL_FR_ID)
        psprintf(linebuf,"FR VOL%02d",iVolume);
    else if(idVolumeFont==VOL_SL_ID)
        psprintf(linebuf,"SL VOL%02d",iVolume);
    else if(idVolumeFont==VOL_SR_ID)
        psprintf(linebuf,"SR VOL%02d",iVolume);
    else if(idVolumeFont==VOL_C_ID)
        psprintf(linebuf,"CENVOL%02d",iVolume);
    else if(idVolumeFont==VOL_SW_ID)
        psprintf(linebuf,"SW VOL%02d",iVolume);//WANGFENG 2003-10-28 14:08
    else {
        #ifdef MAIN_VOL_20// defined(HIMAGE1251) || defined(HIMAGE1250_03_185W)//wangfeng 2003-10-31 21:44
            if(volume_Switch==0)
            psprintf(linebuf,"VOL %02d",iVolume/4);
            else
        #endif
            psprintf(linebuf,"VOL %02d",iVolume);
        }
        
    #else   //CNTR_5SPK_VOLUME
    iVolume         = audio_volume;
    psprintf(linebuf,"VOL %02d",iVolume);//((80-5*(15-audio_volume))/5-1));
    #endif  //CNTR_5SPK_VOLUME
    vfd_set_str(0,linebuf);
    return index;   
}
#endif  //VFD_VOLUME_DISPLAY

#ifdef PORTABLE_DVD //Jack open for all portable dvd

void check_portable_gpio(void)
{
    UINT16 temp=0;
    
    #ifdef TFT_VIDEO_INOUT
    static BYTE AVin_step = 0;
    
    INT_EXT_GPIO_INIT();
   
    switch (GPIO_I_GET(INT_EXT_VIDEO_GPIO))
    {
      case 0://8210 input video to TFT
        if((system_state == SYSTEM_OPEN) && (AVin_step == 1))
        {//just now system was interrupted in reading disc 
              if(CDOpened())
              {
                call_ir_func(IRC_EJECT);
                AVin_step = 0;
                //printf("i am going to read disc.......\n");
              }
        }
        else if((system_state == SYSTEM_STOP) && (AVin_step == 2))
        {//just now system was interrupted in normal playing state
                ircmd_play();
                AVin_step = 0;
                //printf("i am going to play disc.......\n");
        }
        
        if(hold_state == 2)
          hold_state = 0;
          
      break;
      case 1://External AV input to TFT
        if(system_state == SYSTEM_READ_TITLE)
        {//in reading disc and 
            if(!CDOpened())
            {
              AVin_step = 1;
              call_ir_func(IRC_EJECT);
              //printf("video in when reading disc,then i go into open state\n");
            } 
            
        }
        else if(system_state == SYSTEM_BROWSE)
        {
            if(play_state != VCD_STATE_STOP)
            {
                AVin_step = 2;
                ircmd_stop();
                #ifdef STOP_LOADER
                stop_loader();
                #endif
                //printf("video in when playing disc,then i go into stop state\n");
            }
        } 
        
        if(hold_state == 0)
          hold_state = 2;       
      
      break;
      /*
      case 0: //No AV in
      if(play_state==VCD_STATE_OPEN)
      {       
        if(AVin_step==2)
        {
          //printf("Enter here4.\n");
          ircmd_trayin();
          AVin_step=0;
        }   
      }
      if(play_state==VCD_STATE_PAUSE)
      {
        if(AVin_step==3) 
        {
          //printf("Enter here5.\n");
          ircmd_play();        
          AVin_step=0;
        } 
      } 
      break;   
     
      case 1: //AV in
      if(system_state==SYSTEM_BROWSE&&play_state!=VCD_STATE_PAUSE)
      {    //printf("Enter here1.\n"); 
        printf("Enter here1.\n"); 
        AVin_step=3;
        ircmd_pause();
        stop_loader();
      }else if((play_state!=VCD_STATE_OPEN)&&AVin_step!=3)
      {
        //printf("Enter here2.\n");  
        ircmd_trayout();
        AVin_step=2;
      }else if((regs0->gpio_in[16 / 16] & (1 << (16 % 16)))) 
      {    
        //printf("Enter here3.\n");
        ircmd_trayout();
        //AVin_step=2;    
      }   
      break;
      */
    }
    
    if(!AVin_step)
    {
    #endif //end #ifdef TFT_VIDEO_INOUT
    
    #ifdef SUNPLUS_8202P_DEMOBOARD
    regs0->sft_cfg4 &= ~((0x03)<<2);    //Enable GPIO2,3 For COVER & TFT SW
    #endif
    
    #if 0	//for Cover detect
    temp=regs0->gpio_in[PDVD_OPCLSW_GPIO / 16] & (1 << (PDVD_OPCLSW_GPIO % 16));  //get gpio16(COVER_SW)
    
    if(temp)
    {
        if(!CDOpened())
        {
		    #ifdef ARGUS_PDVD_MENU_PLUS
            if(full_scrn & SETUP_PLUS)
              ircmd_setup_plus();
            #endif //end #ifdef ARGUS_PDVD_MENU_PLUS
            call_ir_func(IRC_EJECT);
            PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);
            }   
        }
        else
        {
            if(CDOpened())
              call_ir_func(IRC_EJECT);
        }
    #endif       
    #ifdef TFT_VIDEO_INOUT
    }
    #endif //end #ifdef TFT_VIDEO_INOUT
        
        

#if defined(GBM_PORTABLE_DVD)||defined(SUNPLUS_8202P_DEMOBOARD)     //rbhung for GBM Portable DVD
    #ifdef TFT_VIDEO_INOUT 
    if(!AVin_step)
    {
    #endif //end #ifdef TFT_VIDEO_INOUT 
    #ifdef HOLD_KEY_DETECT    
    temp=regs0->gpio_in[HOLD_GPIO / 16] & (1 << (HOLD_GPIO % 16));  //get (HOLD)
    if(temp)
        hold_state=1;
    else
        hold_state=0;           
    #endif
    
    temp=regs0->gpio_in[TFT_SW_GPIO / 16] & (1 << (TFT_SW_GPIO % 16));  //get (TFT_SW)
    if(temp)
        regs0->gpio_out[CTR_TFT_GPIO /16]|= (1 << (CTR_TFT_GPIO % 16));
    else
        regs0->gpio_out[CTR_TFT_GPIO /16]&= ~(1 << (CTR_TFT_GPIO % 16));
    #ifdef TFT_VIDEO_INOUT
    }
    #endif //end #ifdef TFT_VIDEO_INOUT
        
    temp=regs0->gpio_in[MCU_POWER_DET_GPIO / 16] & (1 << (MCU_POWER_DET_GPIO % 16));  //get gpio41(MCU_POWER_DET)
    if(temp)
    {
        powerdown_timer=0;
    }
    else
    {
        powerdown_timer++;
        if(powerdown_timer>100)
        {
            regs0->gpio_out[CTR_GLED_GPIO/16]|= (1 << (CTR_GLED_GPIO % 16));      //CTR_GLED->H,GREEN LED OFF
            regs0->gpio_out[DSP_RLED_GPIO/16]&= ~(1 << (DSP_RLED_GPIO % 16));     //DSP_RLED->L,RED LED ON    
        call_ir_func(IRC_POWER);
    }
    }   
            
        
    temp=regs0->gpio_in[LOWBAT_DET_GPIO / 16] & (1 << (LOWBAT_DET_GPIO % 16));  //get gpio42(LOWBAT_DET)
    if(temp)
    {   
        if(lowbat_timer==0)
          ClearOsdMsg(2);
        lowbat_timer=1;
        regs0->gpio_out[CTR_GLED_GPIO/16]&= ~(1 << (CTR_GLED_GPIO % 16));     //CTR_GLED->L,GREEN LED ON
        regs0->gpio_out[DSP_RLED_GPIO/16]|= (1 << (DSP_RLED_GPIO % 16));      //DSP_RLED->H,RED LED OFF
    }
    else
    {
        if(lowbat_timer<100)
        {
            PrintOsdMsg(STR_OS_LOWBAT,REGION2,0,0);
            lowbat_timer++;
            regs0->gpio_out[CTR_GLED_GPIO/16]|= (1 << (CTR_GLED_GPIO % 16));  //CTR_GLED->H,GREEN LED OFF
            regs0->gpio_out[DSP_RLED_GPIO/16]&= ~(1 << (DSP_RLED_GPIO % 16)); //DSP_RLED->L,RED LED GLITTER ON
        }   
        else
        {
            if((lowbat_timer>=100) & (lowbat_timer<150))
            {
                ClearOsdMsg(2);
                lowbat_timer++;
                regs0->gpio_out[DSP_RLED_GPIO/16]|= (1 << (DSP_RLED_GPIO % 16));  //DSP_RLED->H,RED LED GLITTER OFF
            }   
            else    
                lowbat_timer=0;
        }   
    }   
         
#endif //end #ifdef GBM_PORTABLE_DVD
}

#ifdef PDVD_USE_IO_SCAN_KEY

const BYTE gpio[8]={46,47,48,49,50,51,52,18};
#ifdef USE_COMBINED_KEY
#define LONG_PRESS_KEY_TIME 12  
#endif

//#define PORTABLE_IOKEY_DEBUG
    
void check_portable_key(void)
{
#ifdef USE_COMBINED_KEY
    BYTE i,j,keydata;
    static BYTE column_dot = 4;
    static BYTE row_dot = 0;
    static BYTE keyprev = 0;
    static BYTE key_press_times = 0 ;
    
    #ifdef HOLD_KEY_DETECT
    if(hold_state)
      return;
    #endif
    
    regs0->gpio_oe[3]&= 0xffcf;     //jhuang org 011f
    
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
          GPIO_O_SET(gpio[j],1);
          
        GPIO_O_SET(gpio[i],0);
    
        for(j=4;j<8;j++)
        {        
            keydata=GPIO_I_GET(gpio[j]);
            
            if(keydata == 0)
            {//have key pressing                  
                keydata=i*4+(j-4)+1;
                column_dot = j;
                row_dot = i;
                
                if(keyprev != keydata)
                {//first press key!                         
                  keyprev = keydata;
                  #ifdef PORTABLE_IOKEY_DEBUG
                  printf("%d key press at the first time\n",keydata);
                  #endif
                }
                else 
                {//count the key press times
                  #ifdef D02_9_10INCH
                  if((keydata == 8) || (keydata == 10))
                  #else 
                  if((keydata == 4) || (keydata == 6)
                     #ifdef D02_A_10INCH
                     ||(keydata == 10) || (keydata == 16)
                     #endif
                    )
                  #endif
                  {
                    key_press_times++;
                    #ifdef PORTABLE_IOKEY_DEBUG
                    printf("key press times:---->%d\n",key_press_times);
                    #endif
                  }
                }           
               break;
             }
             else if((j == column_dot) && (i == row_dot) && (keyprev != 0))
             {//key is released
               if(key_press_times >= LONG_PRESS_KEY_TIME)
               {//long press key 
                 #ifdef PORTABLE_IOKEY_DEBUG
                 printf("call long key:%d!press %d times\n",keyprev,key_press_times);
                 #endif  
                 
                 #ifdef D02_9_10INCH
                 if(keyprev == 8)
                 #else
                 if(keyprev == 4)
                 #endif
                 {
                   #ifdef D02_A_10INCH
                   call_ir_func(IRC_LEFT); 
                   #else
                   call_ir_func(IRC_PREV); 
                   #endif
                 }
                 else
                 {
                   #ifdef D02_A_10INCH
                   if(keyprev == 10)
                     call_ir_func(IRC_DOWN);
                   else if (keyprev == 16)
                     call_ir_func(IRC_UP); 
                   else
                     call_ir_func(IRC_RIGHT);
                   #else
                   call_ir_func(IRC_NEXT);
                   #endif
                 }
              }
              else
              {//short key press
                  call_ir_func(vfd_keycode[keyprev - 1]);
                  #ifdef PORTABLE_IOKEY_DEBUG
                  printf("call short key:%d\n",keyprev);
                  #endif
              }
              
              key_press_times = 0;
              keyprev = 0;
              column_dot = 4;
              row_dot = 0;
           } 
        }       
    }
#else
    BYTE i,j,k,keydata,press_key=0;
    static BYTE keyprev=0;
    
    #ifdef HOLD_KEY_DETECT
    if(hold_state)
      return;
    #endif
    
    regs0->gpio_oe[3]&= 0xffcf;     //jhuang org 011f
    
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
            GPIO_O_SET(gpio[j],1);
        GPIO_O_SET(gpio[i],0);
    
        for(k=4;k<8;k++)
        {        
            keydata=GPIO_I_GET(gpio[k]);
            if(keydata==0)
            {                 
                press_key=1;
                keydata=i*4+(k-4)+1;                
                if(keyprev!=keydata)
                {                           
                  keyprev=keydata;
                  call_ir_func(vfd_keycode[keydata - 1]);
                  printf("key %d SW %d,%d.\n",keydata,i,k-4);
                }  
                break;
            }                       
        }       
    }
    if(press_key==0) keyprev=0;
#endif //end #ifdef USE_COMBINED_KEY

}
#endif //#ifdef PDVD_USE_IO_SCAN_KEY

#endif //end #ifdef PORTABLE_DVD    


