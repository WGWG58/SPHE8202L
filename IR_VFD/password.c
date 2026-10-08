/*
* Terry,2003/8/20 06:43PM
* This file is about password.
*/
#ifdef PARENT_PWD_DEFAULT_NULL//libing 2005-5-28 00:28
#include "setup.h"
#include "setup_VA.h"
#endif
#if defined(SDRAM_16Mb_Mode)//&&defined(NEW_STYLE_SETUP)//zhaoyanhua add 2003-11-10 16:33
#include "memmap.h"
#include "memmap0.h"
#endif

//huziqin 2006-4-19 removed

#ifdef SHOW_12_BOOKMARK//libing 2005-6-29 21:59
extern void cancel_bookmark();
#endif

#ifdef DVD_5_DISC_RESUME//lijd 2005-6-22 16:38
extern void Clear5DVDResumeInfo(void);
#endif

#ifdef TEST_VFD_PANNEL_AND_KEY//lijd 2005-5-8 14:02
BYTE    Test_Front_Panel_flag=0;
const BYTE oritron_test_panel_password[5]=ORITRON_TEST_PANEL_PASSWORD;
BYTE op_test_panel_count=0;
#endif

// mimitsai merge from dp2070/dp3240
#if defined(EASTECH_DVD_DP3240_D)||defined(EASTECH_DVD_DP2070_D)
#include "setup_def.h"
extern UINT8 setup_sel[MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE][MAX_PAGE_ITEM];
#endif
const BYTE Custm_Password[PASSWORD_TOTAL_DIGITAL]=SUPER_PASSWORD;      //defined in user_init.h, Jeff 20020606

#ifdef PULIANG_PASSWORD     //yaowh add 04-12-22
#define REGION_CODE_PSW             {IRC_8,IRC_2,IRC_0,IRC_0}
#define FIRM_WARE_VER_PSW           {IRC_UP,IRC_DOWN,IRC_LEFT,IRC_RIGHT}
#define SUPER_PASSWORD              {IRC_1,IRC_0,IRC_0,IRC_4}
BYTE custm_count_1 = 0;
BYTE custm_count_2 = 0;
const BYTE Custm_Password_1[4]=FIRM_WARE_VER_PSW;
const BYTE Custm_Password_2[4]=REGION_CODE_PSW;
extern void osd_print_region2(t_osd_region *p, const char *s0, BYTE y_start,BYTE x_start);
#endif

// mimitsai merge from dp2070/dp3240
    #ifdef USER_VERSION_INFORMATION
#define VERSION_INFORMATION {IRC_1,IRC_2,IRC_3}
#define VERSION_INFORMATION1 {IRC_1,IRC_5,IRC_9}
#define DIVX_CODE            {IRC_3,IRC_4,IRC_8,IRC_9}
#define MACROVISION          {IRC_6,IRC_2,IRC_2,IRC_7,IRC_6}
#define REGION_CODE          {IRC_7,IRC_3,IRC_4,IRC_4,IRC_6,IRC_6}
#define CLEAR_EEPROM         {IRC_0,IRC_0,IRC_0,IRC_0}
#define RESET_P_SCAN_OFF     {IRC_7}
const BYTE Custm_version1[3]=VERSION_INFORMATION1;
const BYTE divx_code[4]=DIVX_CODE;
const BYTE macrovision[5]=MACROVISION;
const BYTE region_code[6]=REGION_CODE;
const BYTE reset_p_scan_off[1]=RESET_P_SCAN_OFF;
const BYTE clear_eeprom[4]=CLEAR_EEPROM;
    
const BYTE Custm_version[3]=VERSION_INFORMATION;
BYTE    temp_data[6];
BYTE    enter_display_flag=0;
#define VERSION_INFORMATION_STRING  "VER 040727 1"
BYTE version_count=0;
#endif

#ifdef  MIDI_EJECT_PASSWORD   //ouyang add for eject password 2004-11-20 15:10
#define MIDI_OPEN_PASSWORD {IRC_6,IRC_6,IRC_7,IRC_7}
const BYTE midi_open_password[4]=MIDI_OPEN_PASSWORD;
BYTE    temp_num[4];
//BYTE    enter_display_flag=0;
BYTE midi_open_count=0;
#endif



 #if defined ( AD_TCL) || defined(AD_HL_USE)   //2004-3-22 14:51 lijd   // lxg 2006-7-22 02:18
const BYTE inter_Pass[4]=INTER_PASSWORD;      //defined in user_init.h, Jeff 20020606
const BYTE macro_Pass[4]=MACRO_PASSWORD;      //defined in user_init.h, Jeff 20020606
BYTE inter_count = 0;
BYTE macro_count = 0;
#endif
#ifdef SUPPORT_PASSWD2
const BYTE Custm_Password1[4]=SUPER_PASSWORD1;//defined in user_init.h, Jeff 20020606
#endif

#ifdef QSI_PLATFORM //qsi: added by johnson 20040713
void display_custm_menu(void);

enum {
    VER_SHOW_VIA_NORMAL=0,
    VER_SHOW_VIA_SPECIAL, // for internal
    VER_SHOW_MAX
};
static BYTE version_show_entry;
BYTE is_show_full_qsi_version(void)
{
    return(version_show_entry==VER_SHOW_VIA_SPECIAL);
}

void display_custm_menu_full(void)
{
    version_show_entry = VER_SHOW_VIA_SPECIAL;
    //display_custm_menu();
    setup_ShowCUSTMMsg();
}
#endif

//#define SUPPORT_PASSWD3 //for testing
#ifdef SUPPORT_PASSWD3
#ifndef SUPER_PASSWORD3
#define SUPER_PASSWORD3              {IRC_1,IRC_5,IRC_9,IRC_7}   //define super password when open tray
#endif
UINT8 setup_audio_mode,custm_count3=0;
const BYTE Custm_Password3[4]=SUPER_PASSWORD3;//defined in user_init.h, Jeff 20020606
#endif

#ifdef WATCH_LOADER_ID
const BYTE Loader_Password[4]={IRC_1,IRC_2,IRC_3,IRC_4};     //defined in user_init.h, Jeff 20020606
#endif

#ifdef DVD_SERVO
extern const BYTE Servo_Password[8];                // kernel/hwif.c

extern BYTE *GetServoCodeVersion();
#endif

#if defined (SUPPORT_SPG_GAME) && !defined (DVDRELEASE) && defined (SPG_ICE)                
const BYTE ICE_Password[4]={IRC_9,IRC_9,IRC_9,IRC_2};
static BYTE ICEId_count=0;
#endif

BYTE custm_count = 0;

#ifdef SUPPORT_PASSWD2
BYTE custm_count1 = 0;
BYTE only_disp_setup_menu = 0;
#endif

#ifdef DVD_SERVO
BYTE servo_count=0;  //Jeff 20030818
#endif

#ifdef WATCH_LOADER_ID
static BYTE LoaderId_count=0;
#endif


#ifdef PAUSE_PREV_DISPLAY_MACROVISION_VERSION
const BYTE Macrovision_Version_Password[2]={IRC_PAUSE,IRC_PREV};      
BYTE MACVersion_count=0;
#endif

//=============================================
//for DVD_SETUP_REENG   //added by JS   //20040728
#ifdef DVD_SETUP_REENG
void display_custm_menu(void)
{            
    //printf("display_custm_menu\n");

    full_scrn=(SETUP|CUSTM);
    read_custm_setup_select();
    
#if defined(SDRAM_16Mb_Mode)//&&defined(NEW_STYLE_SETUP)
            //NOTE:
            //when SDRAM_16M_Mode,ShowTitle() may destroyed 
            // OSD memory. So must evaluate osd_base_addr again.
            //zhaoyanhua add 2003-11-10 17:06
            regs0->osd_base_addr=OSD_BASE_USE_ADDR;//P_BIDIR_LUMA;
#endif    
    
    ShowSetupPage(0);
	//Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 9:12
    SetFullscrnCmdFuncPtr( setup_func_up, setup_func_down, setup_func_left,
                           setup_func_right,  setup_func_select);
}
#else    
void display_custm_menu(void)
{            
    index_y=3;
    full_scrn=(SETUP|CUSTM);
    read_custm_setup_select();

#if defined(SDRAM_16Mb_Mode)//&&defined(NEW_STYLE_SETUP)
            //NOTE:
            //when SDRAM_16M_Mode,ShowTitle() may destroyed 
            // OSD memory. So must evaluate osd_base_addr again.
            //zhaoyanhua add 2003-11-10 17:06
            regs0->osd_base_addr=OSD_BASE_USE_ADDR;//P_BIDIR_LUMA;
#endif
    

#ifdef SETUP_TAB
	#ifdef SOFT_MENU//Modifed by ChenZhao on 2004-9-11 13:58 WP
	osd_init_setup();
	ShowSetupPage(REFRESH_CUSTM);
	#else
    ShowSetupPage(1);
	#endif	  
    
            
#else
    ShowSetupPage();
#endif

    //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 9:12
    SetFullscrnCmdFuncPtr( setup_func_up, setup_func_down, setup_func_left,
                           setup_func_right,  setup_func_select); 

#ifdef SUPPORT_PASSWD2         
    custm_count1=0;
#endif    
    custm_count=0;
}
#endif  //endo of DVD_SETUP_REENG

                                                       
#ifdef ORITRON_PASSWORD//libing 2005-4-25 10:07

#define __palette4F(G,B,R,A) \
        ( ((UINT32)((G)&0xff)<<24)|((UINT32)((B)&0xff)<<16)|((UINT32)((R)&0xff)<<8)|(A&0xff) )
	
#define ORITRON_MAX_NUMBER 5
#ifdef SUPPORT_OP_SW_VERSION_UI//libing 2005-11-3 14:43
extern void Dislay_Op_SW_Version_ui(void);
const BYTE oritron_show_swversion_password[ORITRON_MAX_NUMBER]=SHOW_SW_VERSION_UI_PASSWORD;
BYTE op_version_count = 0;
#endif//#ifdef SUPPORT_OP_SW_VERSION_UI//libing 2005-11-3 14:43

#ifdef SUPPORT_OP_REGION_UI
extern void Show_Oritron_Region_UI(void);
const BYTE oritron_show_region_password[ORITRON_MAX_NUMBER]=SHOW_ORITRON_UI_PASSWORD;
BYTE op_region_count = 0;
#endif//#ifdef SUPPORT_OP_REGION_UI

#ifdef ORITRON_TRAY_PASSWORD
extern void show_pwd_ui(void);
const BYTE oritron_tray_password[ORITRON_MAX_NUMBER]=ORITRON_TRAY_LOCK_PASSWORD;
BYTE op_tray_count = 0;
#endif//#ifdef ORITRON_TRAY_PASSWORD

#ifdef ORITRON_PARENTAL_PASSWORD
const BYTE oritron_parent_password[ORITRON_MAX_NUMBER]=ORITRON_PARENT_PASSWORD;
BYTE op_parent_count = 0;
#endif//#ifdef ORITRON_PARENTAL_PASSWORD

#ifdef ORITRON_SET_DEFAULT
const BYTE oritron_set_default_password[ORITRON_MAX_NUMBER]=ORITRON_SET_DEFAULT_PASSWORD;
BYTE op_set_default_count = 0;
#endif

#ifdef ORITRON_TRAY_PASSWORD
void display_pwd_menu(void)
{
	full_scrn=(SETUP|TRAY_PWD);
	show_pwd_ui();
	SetFullscrnCmdFuncPtr( ircmd_null, ircmd_null, tray_pwd_left,tray_pwd_right,tray_pwd_select);
	op_tray_count = 0;
}
#endif//#ifdef ORITRON_TRAY_PASSWORD
#ifdef SUPPORT_OP_REGION_UI		//fcr 2005-10-27 14:17
void Dislay_Op_Region_ui(void)
{
	full_scrn=(OP_REGION_UI | SETUP);//OP_REGION_UI;
	Show_Oritron_Region_UI();	
	SetFullscrnCmdFuncPtr( ircmd_null,ircmd_null,Region_Func_Left,
							Region_Func_Right,Region_Func_Select );
	op_region_count = 0;						
}
#endif	
#ifdef SUPPORT_OP_SW_VERSION_UI//libing 2005-11-3 14:43
void Dislay_Op_SW_Version_ui(void)
{
	full_scrn=(OP_REGION_UI | SETUP);//OP_REGION_UI;
	Show_Oritron_SW_Version_UI();
	SetFullscrnCmdFuncPtr(ircmd_null,ircmd_null,ircmd_null,
							ircmd_null,ircmd_null);
	op_version_count = 0;						
}
#endif//#ifdef ORITRON_TRAY_PASSWORD
extern void set_default_value(void);
extern void run_set_variable(void);
extern void run_save_total_sel(void);
extern void cancel_bookmark();
extern void RsmInfo2Flash(int clr);
extern void ClearDVDResumeInfo(void);

static inline void oritron_chk_password(UINT8 rx)
{
    if( (play_state==VCD_STATE_IDLE)||(play_state==VCD_STATE_STOP)||(play_state==VCD_STATE_OPEN) ) 
    {
    	
    	#ifdef SUPPORT_OP_SW_VERSION_UI//libing 2005-11-3 14:43
    		if(full_scrn==OP_REGION_UI)
	    		op_version_count = 0;
	    	if(rx==oritron_show_swversion_password[op_version_count])
	    	{
	    		op_version_count++;
	    		if(op_version_count>=ORITRON_MAX_NUMBER)
	    		{
	    			Dislay_Op_SW_Version_ui();
	    			return;
	    		}
	    	}else
	    	{
	    		op_version_count = 0;
	    	}
	    #endif		
    	
    #ifdef SUPPORT_OP_REGION_UI
    	if(full_scrn==OP_REGION_UI)
    		op_region_count = 0;
    	if(rx==oritron_show_region_password[op_region_count])
    	{
    		op_region_count++;
    		if(op_region_count>=ORITRON_MAX_NUMBER)
    		{
    			Dislay_Op_Region_ui();
    			return;
    		}
    	}else
    	{
    		op_region_count = 0;
    	}
    #endif
    	#ifdef ORITRON_TRAY_PASSWORD
    	if (full_scrn&TRAY_PWD)
    	{
    		op_tray_count = 0;
    	}	
    	if (full_scrn&SETUP)
    	{
    		custm_count=0;
    	}
        if(rx==oritron_tray_password[op_tray_count]) 
        {
            op_tray_count++;
            if(op_tray_count>=ORITRON_MAX_NUMBER) 
            {
                #ifdef ORITRON_TRAY_PASSWORD
                display_pwd_menu();
                #endif
                #ifdef TEST_VFD_PANNEL_AND_KEY//lijd 2005-5-8 14:03
                	Test_Front_Panel_flag=0;
                 #endif
                return;
            }
         }
        else 
        {
            op_tray_count=0;
        }
        if(rx==Custm_Password[custm_count]) 
        {
            custm_count++;
            if(custm_count>=PASSWORD_TOTAL_DIGITAL) 
            {
                display_custm_menu();
                return;
            }
         }
        else 
        {
            custm_count=0;
        }
        #endif
        #ifdef ORITRON_SET_DEFAULT
        if(rx==oritron_set_default_password[op_set_default_count])
        {
        	op_set_default_count++;
        	if(op_set_default_count>=ORITRON_MAX_NUMBER)
        	{
        		PrintOsdMsg(STR_OS_SET_DEFAULT , REGION2, 2, 0);
        		set_default_value();
                reset_amp_variable();   //OP FCR 2005-10-11 16:49	
            	run_set_variable();
            	run_save_total_sel();
            	rep_mode = REPEAT_IDLE;//libing 2005-6-29 21:42
        	rep_ab_mode = REPEAT_AB_IDLE;
            	prog_func_clear();
            	shuffle_flag=0;
            	#ifdef SUPPORT_BOOK	//hongfeng 2005-08-22
            	cancel_bookmark();
            	#endif
            	#ifdef DVD_5_DISC_RESUME//lijd 2005-6-22 16:38
            	Clear5DVDResumeInfo();
            	#endif
            	#ifdef SUPPORT_TEN_DISC_RESUME  //hongfeng add 2005-09-22
                //RsmInfo2Flash(1);
                ClearDVDResumeInfo();
                #endif
            	set_tuner_default_value(); //opv-joke: set tuner default data when press 76000
            	
            	//
            	printf("joke: =========== set default data  =====================\n");
            	
            	delay_srv_10ms(20);
            	call_ir_func(IRC_POWER);
            	return;
        	}
        }else
        	{
        		op_set_default_count = 0;
        	}
        #endif	
        #ifdef ORITRON_PARENTAL_PASSWORD
        if(rx==oritron_parent_password[op_parent_count])
        {
        	op_parent_count++;
        	if(op_parent_count>=ORITRON_MAX_NUMBER)
        	{
        		PrintOsdMsg(STR_OS_CLAER_PWD , REGION2, 2, 0);
        		UserSet.parent_passwd = DEFAULT_PASSWORD;
        		UserSet.parental_ststus = 1;
        		op_parent_pwd_flag = 1;
        		setup_VA[SETUP_VA_PASSWORD] = 2+1;
        		run_set_variable();
            	        run_save_total_sel();
            	return;
        	}
        }
        	else
        	{
        		op_parent_count = 0;
        	}		
       #endif 		
       #ifdef TEST_VFD_PANNEL_AND_KEY //test front pannel password lijd 2005-5-8 14:05
        if(rx==oritron_test_panel_password[op_test_panel_count]) 
        {
            op_test_panel_count++;
            printf("==========76==============\n"); 
            if(op_test_panel_count>=ORITRON_MAX_NUMBER) 
            {
            	printf("==========88==============\n");  
                op_test_panel_count=0;       
                Test_Front_Panel_flag=1; 
                return;                
            }
         }
        else 
        {
            op_test_panel_count=0;
        }
        #endif 	
        
    } //if( (play_state==VCD_STATE_IDLE)||(play_state==VCD_STATE_OPEN) )
    #ifdef TEST_VFD_PANNEL_AND_KEY//lijd 2005-5-8 14:05
    else
    {
    	Test_Front_Panel_flag=0;
    }
	#endif
}
#endif//#ifdef ORITRON_PASSWORD//libing 2005-4-25 10:07
                                                      
static inline void standard_chk_password(UINT8 rx)
{
    #if defined(ALCO_DVD_UI)
    if(play_state==VCD_STATE_OPEN) 
    #else
    if( (play_state==VCD_STATE_IDLE)||(play_state==VCD_STATE_OPEN) ) 
    #endif
    {
        if (full_scrn&SETUP) 
        {
            custm_count=0;
#ifdef SUPPORT_PASSWD2     
            custm_count1=0;
#endif
        }

        if(rx==Custm_Password[custm_count]) 
        {
            custm_count++;
            if(custm_count>=PASSWORD_TOTAL_DIGITAL) 
            {
#ifdef QSI_PLATFORM //qsi: added by johnson 20040713
                version_show_entry=VER_SHOW_VIA_NORMAL;
#endif
                display_custm_menu();
                return;
            }
         }
 #if defined ( AD_TCL) || defined(AD_HL_USE)//2004-3-22 14:51 lijd   // lxg 2006-7-22 02:18
        else if (rx==inter_Pass[inter_count])
            {
                inter_count++;
                if(inter_count>=4) 
                {
        #ifdef AD_HL_USE      // lxg 2006-7-22 02:18
            int i=0x06ff;    //  0x2fff
              while(i--)
              {
                psprintf(linebuf,MACRO_VER);           
                strcpy(RegionValStr[REGION2], linebuf);
                PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
              }           	  
              macro_count=0;
         #endif
                    psprintf(linebuf,INTER_VER);           
                    strcpy(RegionValStr[REGION2], linebuf);
                    PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
                    inter_count=0;
                    return;
                }
            }
        else if (rx==macro_Pass[macro_count])
            {
                macro_count++;
                if(macro_count>=4) 
                {
                    psprintf(linebuf,MACRO_VER);           
                    strcpy(RegionValStr[REGION2], linebuf);
                    PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
                    macro_count=0;
                    return;
                }
            }
#endif
#ifdef PAUSE_PREV_DISPLAY_MACROVISION_VERSION //Jack added for Alco Portable
        else if(rx == Macrovision_Version_Password[MACVersion_count])
        {
                MACVersion_count++;
                //osd_tog_region(REGION1,OSD_OFF);
                //PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 0);
                if(MACVersion_count>=2) 
                {
                    psprintf(linebuf,MACROVISION_STRING);           
                    #ifdef SDRAM_16Mb_Mode
                    strcpy(RegionValStr[REGION1], linebuf);
                    PrintOsdMsg(STR_OS_SPACE, REGION1, 2, 1);
                    #else
                    strcpy(RegionValStr[REGION2], linebuf);
                    PrintOsdMsg(STR_OS_SPACE, REGION2, 2, 1);
                    #endif
                    return;
                    
                }
        }
#endif//#ifdef PAUSE_PREV_DISPLAY_MACROVISION_VERSION //Jack added for Alco Portable

        else 
        {
            #if defined ( AD_TCL) || defined(AD_HL_USE)//2004-3-22 14:51 lijd   // lxg 2006-7-22 02:18
        	macro_count=0;
            inter_count=0;
            #endif
            custm_count=0;
        }
        
#ifdef SUPPORT_PASSWD2        
        if(rx==Custm_Password1[custm_count1]) 
        {
            custm_count1++;
            if(custm_count1>=4) 
            {                
#ifdef QSI_PLATFORM //qsi: added by johnson 20040713
                version_show_entry=VER_SHOW_VIA_SPECIAL;
#endif
                display_custm_menu();
                only_disp_setup_menu=1;
                return;
            }
        } else 
        {
            custm_count1=0;
        }
        
        if(only_disp_setup_menu==1)
        {
            ExitSetupPage(1);
            only_disp_setup_menu = 0;
        }
#endif


#ifdef SUPPORT_PASSWD3
        if( full_scrn==(SETUP|CUSTM) )
        {
            if(rx==Custm_Password3[custm_count3]) 
            {
                custm_count3++;
                if(custm_count3>=4) 
                {
                    setup_audio_mode=1;
                        chg_audio_default_mode();
                }
            } else 
            {
                custm_count3=0;
            }
    }
#endif

#ifdef DVD_SERVO
        if(rx==Servo_Password[servo_count]) { //Jeff 20030818
            servo_count++;
            if(servo_count>=8) {
                servo_count=0;
                psprintf(RegionValStr[REGION2], "%s", GetServoCodeVersion());
                PrintOsdMsg(STR_OS_SPACE, REGION2, 10, 1);
                return;
            }
        } else {
            servo_count=0;
        }
#endif

        #ifdef WATCH_LOADER_ID                
        if(rx==Loader_Password[LoaderId_count]) {
        
            extern char Loader_ID[28];//kenny 2002/11/22
            
            LoaderId_count++;
            if(LoaderId_count>=4) {
                LoaderId_count=0;
                                        
                psprintf(RegionValStr[REGION3], "LOADER ID: %s", &Loader_ID[0]);
                PrintOsdMsg(STR_OS_SPACE, REGION3, 0, 1);
                
                return;
            }
        } else {
            LoaderId_count=0;
        }
        #endif //#ifdef WATCH_LOADER_ID

        #if defined (SUPPORT_SPG_GAME) && !defined (DVDRELEASE) && defined (SPG_ICE)               
        if(rx==ICE_Password[ICEId_count]) {
            extern void FS_ICEMainLoop();
          
            ICEId_count++;

            if(ICEId_count>=4) {
                ICEId_count=0;
                FS_ICEMainLoop();                     
                return;
            }
        } else {
            ICEId_count=0;
        }
        #endif //#ifdef WATCH_LOADER_ID

    } //if( (play_state==VCD_STATE_IDLE)||(play_state==VCD_STATE_OPEN) )

}

#ifdef PULIANG_PASSWORD     //yaowh add 04-12-22
static inline void puliang_chk_password(UINT8 rx)
{
    if ( (rx==Custm_Password[custm_count])&&(full_scrn&SETUP) )
    {
        custm_count++;
        if(custm_count>=4) 
        {
            display_custm_menu();
            return;
        }
    }
    else if( (rx==Custm_Password_1[custm_count_1])&&(play_state==VCD_STATE_OPEN) )
    {
        custm_count_1++;
        if(custm_count_1>=4) 
        {
            PrintOsdMsg(FIRM_WARE_VER , REGION1, 0, 0);
            return;
        }
    }             
    else if( (rx==Custm_Password_2[custm_count_2])&&(play_state==VCD_STATE_OPEN) )
    {
        custm_count_2++;
        if(custm_count_2>=4) 
        {
            PrintOsdMsg(REGION_CODE , REGION1, 0, 0);
            return;
        }
    }
    else 
    {
        custm_count_1=0;
        custm_count_2=0;
        custm_count=0;
    }
}
#endif  //#ifdef puliang_password

// mimitsai merge from dp2070/dp3240

    #ifdef USER_VERSION_INFORMATION
extern void set_default_value(void);
extern void run_set_variable(void);
extern void run_save_total_sel(void);
#include "setup_popup_gui.h"
#include "setup_page.h"
#include "setup_VA.h"
extern UINT8 ShowingWarningMessage;
BYTE check_password_flag;
    #endif  //#ifdef USER_VERSION_INFORMATION


static inline void eastech_chk_password(UINT8 rx __attribute__((unused)))
{
#ifdef EASTECH_PASSWORD

    coordinate start={0,0}; // mimitsai add

    //printf("enter_display_flag= %x\n",enter_display_flag);
    //printf("------------\n");
    //printf("play_state= %x\n",play_state);
    if( (play_state==VCD_STATE_OPEN)&&(enter_display_flag)) //||(play_state==VCD_STATE_OPEN) ) 
    {
        //printf("enter-------------1\n");
           if (full_scrn&SETUP) 
            {
                    custm_count=0;
            }
           if(custm_count==0)
           {
/*
            temp_data[0]=0;
            temp_data[1]=0;
            temp_data[2]=0;
            temp_data[3]=0;
*/
            temp_data[0]=-1;
            temp_data[1]=-1;
            temp_data[2]=-1;
            temp_data[3]=-1;
            temp_data[4]=-1;
            temp_data[5]=-1;
           }
        temp_data[custm_count]=rx;
        custm_count++;

        if(enter_display_flag==1)
        {

        if(temp_data[0]==Custm_version[0] && 
        temp_data[1]==Custm_version[1] && 
        temp_data[2]==Custm_version[2])
        {
                psprintf(linebuf,"%s",VERSION_INFORMATION_STRING);
            osd_draw_string(&start, linebuf, 3, 1, 1, 0);
            osd_tog_region(1,OSD_ON);
            delay_1ms(3000);

            check_password_flag = 1;
            custm_count=0;
            enter_display_flag=0;
            return;
        }

        // mimitsai merge from dp2070/dp3240

            #ifdef USER_VERSION_INFORMATION            
            // show internal software version
            if(temp_data[0]==Custm_version1[0] && 
               temp_data[1]==Custm_version1[1] && 
               temp_data[2]==Custm_version1[2])
            {
                psprintf(linebuf,"%s",INTERNAL_VERSION_INFORMATION_STRING);
                osd_draw_string(&start, linebuf, 3, 1, 1, 0);
                osd_tog_region(1,OSD_ON);
                delay_1ms(3000);
                
                check_password_flag = 1;
                custm_count=0;
                enter_display_flag=0;
                return;
            }
                    
            // show macrovision
            if(temp_data[0]==macrovision[0] && 
               temp_data[1]==macrovision[1] && 
               temp_data[2]==macrovision[2] && 
               temp_data[3]==macrovision[3] && 
               temp_data[4]==macrovision[4])
            {
                psprintf(linebuf,"%s",MACROVISION_STRING);
                osd_draw_string(&start, linebuf, 3, 1, 1, 0);
                osd_tog_region(1,OSD_ON);
                delay_1ms(3000);
                
            check_password_flag = 1;          
            custm_count=0;
            enter_display_flag=0;
            return;
        }
// clear eeprom
            if(temp_data[0]==clear_eeprom[0] &&
               temp_data[1]==clear_eeprom[1] && 
               temp_data[2]==clear_eeprom[2] && 
               temp_data[3]==clear_eeprom[3])
            {
                psprintf(linebuf,"%s","CLEAR EEPROM");
                osd_draw_string(&start, linebuf, 3, 1, 1, 0);
                osd_tog_region(1,OSD_ON);
                //delay_1ms(3000);
                
    	        set_default_value();
    	        run_set_variable();
    	        run_save_total_sel();
    
            custm_count=0;
            enter_display_flag=0;
            return;
        }
            #endif //#ifdef USER_VERSION_INFORMATION 


#ifdef EASTECH_PWD_SIX_DIGITAL
       if(temp_data[0]==region_code[0] && 
       temp_data[1]==region_code[1] && 
       temp_data[2]==region_code[2] && 
       temp_data[3]==region_code[3] && 
       temp_data[4]==region_code[4] &&
       temp_data[5]==region_code[5])
#else
        if(temp_data[0]==Custm_Password[0] && 
        temp_data[1]==Custm_Password[1] && 
        temp_data[2]==Custm_Password[2]&&
        temp_data[3]==Custm_Password[3])
#endif
        {

            osd_tog_region(REGION1, OSD_OFF);
            RegionOnOff[REGION1][1] = 0;
            RegionOnOff[REGION1][2] = STR_OS_SPACE;
            RegionValStr[REGION1][0] = 0;   //kevinmonkey 050720 clear message so it won't appear again permanently after exit setup
        

            display_custm_menu();
            check_password_flag = 1;
            enter_display_flag=0;
            custm_count=0;
                    return;
        }
            
#ifdef EASTECH_PWD_SIX_DIGITAL
        if(custm_count>6)
#else
            //if(custm_count>4)
            if(custm_count>6)
#endif
        {
            custm_count=0;
            enter_display_flag=0;
        }
        return;
    }

    // mimitsai merge from dp2070/dp3240

        #ifdef USER_VERSION_INFORMATION
        else if(enter_display_flag==2)
        {
            // reset P_SCAN to off
            if(temp_data[0]==reset_p_scan_off[0])
            {
                setup_tv_out(INTERLACE);
                setup_SetPScan();
                PrintOsdMsg(STR_OS_YCbCr,REGION1,1,0);

                setup_VA[SETUP_VA_VIDEO] = 2;
                run_save_sel_cmd(setup_VA[SETUP_VA_VIDEO], SETUP_VA_VIDEO);
                setup_VA[SETUP_VA_PSCAN_ON_OFF] = 3;
                run_save_sel_cmd(setup_VA[SETUP_VA_PSCAN_ON_OFF], SETUP_VA_PSCAN_ON_OFF);
               
                psprintf(linebuf,"%s","P_SCAN OFF");
                osd_draw_string(&start, linebuf, 3, 1, 1, 0);
                osd_tog_region(1,OSD_ON);
                delay_1ms(3000);
                
                custm_count=0;
                enter_display_flag=0;
                return;
            }
        }
        #endif  //#ifdef USER_VERSION_INFORMATION

    }
#endif//#ifdef EASTECH_PASSWORD
}
 #ifdef MIDI_EJECT_PASSWORD    //ouyang add for eject password 2004-11-20 15:10
     
UINT8 midi_open_pwd_start = 0;
UINT8 midi_open_pwd_finished = 0;    
static inline int midi_eject_chk_password(UINT8 rx)
{
    if(midi_open_pwd_start)
    {
           if (full_scrn&SETUP) 
            {
             midi_open_count=0;
            }
           if(midi_open_count==0)
           {
            temp_num[0]=0;
            temp_num[1]=0;
            temp_num[2]=0;
            temp_num[3]=0;
           }
            temp_num[midi_open_count]=rx;
           if( rx != IRC_EJECT )
            midi_open_count++;
            else
             midi_open_count=0;
printf("========temp_num================= %d %d %d %d =====\n",temp_num[0],temp_num[1],temp_num[2],temp_num[3]);
printf("========midi_open_password ====== %d %d %d %d =====\n",midi_open_password[0],midi_open_password[1],midi_open_password[2],midi_open_password[3]);
        if(temp_num[0]==midi_open_password[0] && 
        temp_num[1]==midi_open_password[1] && 
        temp_num[2]==midi_open_password[2]&&
        temp_num[3]==midi_open_password[3])
        {
            if( rx == IRC_SELECT ){
            //enter_display_flag=0;
            midi_open_pwd_finished=1;
            ircmd_eject_toggle();
            midi_open_count=0;
            return 0;
       }            
        }else
        {
            extern void CleanSysMessage(BYTE);
//            extern void osd_Clear_Region(BYTE reg, BYTE bkColor);
            if( rx == IRC_SELECT ){//xlluo modify here 11:16 2004-12-21
                midi_open_pwd_start     =0;    
                midi_open_pwd_finished  =0; 
                midi_open_count=0;
                CleanSysMessage(1);
               }     
        }
        if(midi_open_count>4)
        {
            midi_open_count=0;
            //enter_display_flag=0;
        }
//        return 1;
    }
    return 1;
}

#endif//#ifdef MIDI_EJECT_PASSWORD    //ouyang add for eject password 2004-11-20 15:10


void chk_password(UINT8 rx)
{
#ifdef PASSWORD
	#if defined( EASTECH_PASSWORD )
        eastech_chk_password(rx);
    #elif defined(PULIANG_PASSWORD)     //yaowh add 04-12-22
        puliang_chk_password(rx);
    #elif defined(ORITRON_PASSWORD)//libing 2005-4-25 10:56
        oritron_chk_password(rx);  
    #elif defined( MIDI_EJECT_PASSWORD )   //ouyang add for eject password 2004-11-20 15:10
        if (!midi_eject_chk_password(rx)) return;
        standard_chk_password(rx);        //ouyang 2004-12-3 11:39
    #else
        standard_chk_password(rx);
    #endif
#endif //#ifdef PASSWORD

    safe_srn_off();

    if(old_key==rx)
    {
        UINT16 stmp = regs0->rtc_15_0;
        int diff = stmp-timestamp_key;

        #ifdef Ti3001_OSD_UI_1      // AMP osd timeout=2*OSD_TIMEOUT //jason 2-10-4 15:34
        if (diff < OSD_TIMEOUT*2)
        #elif defined(NEW_UART_COMMAND)
        if(diff< OSD_TIMEOUT*2)
        #else
        if (diff < OSD_TIMEOUT)
        #endif
        {
            #ifndef ALCO_DVD_UI
            if(action_click)
            #endif
                timestamp_key = regs0->rtc_15_0;

            action_click=1;
            //printf("action\n");
        }else
        {
            timestamp_key = regs0->rtc_15_0;
            action_click=0;
            //printf("action time out\n");
        }
    }else
    {
        timestamp_key = regs0->rtc_15_0;
        action_click=0;
        //printf("difference key\n");
    }

    #ifndef IR_TOOL
    #ifdef IR_DBG
    printf("\n\n-----IR input, rx:%x ,cmd:%s -----\n",rx,irc_func_str[rx]);
    #endif
    #endif

    #ifdef SUPPORT_QUICKTIME
    extern UINT32		pre_parse_mode;
    if (pre_parse_mode)
    {
        //File preparse mode
        return;
    }
    #endif //SUPPORT_QUICKTIME

    if(system_state!=SYSTEM_IDLE)
    {
        ircmd_pre_paser(rx);
    }
    old_key=(BYTE)rx;
}



