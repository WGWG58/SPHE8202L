/*****************************************************************************
** FILE
** ir_drv.c
**
** DESCRIPTION
** process IR keys and send to ir_cmd_xxx for actual process
**
**   Creater  : Terry
**   Maintain : Terry
**   ------------------------------------
**   Revision History
**   ------------------------------------
**   2003.02.12  seperate driver/parser from ir.c
**   2003.02.25  use define function
**   2004.07.23  maintain program
**
****************************************************************************/

#include "config.h"
#include "regmap.h"
#include "global.h"

#include "cfont.h"
#include "func.h"
#include "sio.h"
#include "ircmd.h"
#include "ircode.h"
#include "user_init.h" 
#include "iop.h"
#include "atapi_if.h"
#include "macro.h"
#include "osd.h"
#include "bitop.h"
#include "timer.h"
#ifdef TAS3001_AMP
#include "ti3001.h"
#endif

#ifdef TAS5026_AMP
#include "ti5026.h"
#endif
#ifdef DVB_SETUP
#include "../driver/message.h"
#endif

//=========================================================================================
// debug option define 
//=========================================================================================
#define WATCH_CUSTID    0
//#define DEBUG_IR_CODE //if you want to see which defined code for key, unmark it
#ifndef DVDRELEASE
#define IR_DBG	1
#define IRCMD_DBG
#endif
#ifndef IRCMD_DBG
#undef printf
#undef print_block
#define printf(f, a...) do {} while (0)
#define print_block(x,y) do {} while (0)
#endif


//=========================================================================================
// var. decalre 
//=========================================================================================
extern const BYTE ir_mapcode[256];  
extern UINT32 save_srn_start_t;
extern void ircmd_pre_paser(BYTE rx);
int rep_ir_times=0;

#ifdef SUPPORT_8202_DVB

#include "..\dvb_h\dvb_func.h"
extern UINT8 Dvb_ircmd_pre_parser(BYTE rx __attribute__((unused)));
#endif

#ifdef QISHENG_DVD	// alan, 2003/9/7 07:08PM
static BYTE pressed=IRC_NULL;
static UINT16 irc_value;
static BYTE not_rdy_times=0;
#endif    


#ifdef TEST_VFD_PANNEL_AND_KEY//lijd 2005-5-16 16:19
BYTE  TestIrData=0;	 
extern  BYTE   Test_Stop_flag;
#endif
//=========================================================================================
// define function
//=========================================================================================
#ifdef IR_PHILIPS       
#define IOP_IR_DATA() ((regs0->iop_data[6]>>6)&0x5f)
#define TRANS_IR_CODE(rx) (rx&0x003f)
#elif defined(IR_PHILIPS_EASTECH)
		#define IOP_IR_DATA()((regs0->iop_data[6]&0xff00)>>8)
       #define TRANS_IR_CODE(rx)(rx & 0x00ff)
#elif  defined(IR_THOMSON)		//wurh modify for 8bit thomson ir keycode 2006-3-1 04:43ÏÂÎç
#define IOP_IR_DATA() ((BYTE)(regs0->iop_data[6]))
#define TRANS_IR_CODE(rx) (BYTE)(rx&0x00ff)
#elif  defined(IR_THOMSON_6BIT)       //wurh add for 6bit thomson ir keycode 2006-3-1 04:45ÏÂÎç
#define IOP_IR_DATA() ((BYTE)(regs0->iop_data[6]))
#define TRANS_IR_CODE(rx) (BYTE)(rx&0x003f)
#elif  defined(IR_M50560)
#define IOP_IR_DATA() (regs0->iop_data[6])
#define TRANS_IR_CODE(rx) reverse_fun(rx)
#elif  defined(IR_AS1213)
#define IOP_IR_DATA() (regs0->iop_data[6])
#define TRANS_IR_CODE(rx) reverse_fun(rx)
#elif  defined(IR_M3004)||defined(IR_ORITRON)||defined (IR_THOMSON_ANGUS)//LIJD 2005-6-20 14:08
#define IOP_IR_DATA() (regs0->iop_data[6])
#define TRANS_IR_CODE(rx) reverse_fun(rx)
#elif  defined(IR_KONKA)//LIJD 2005-2-4 13:24
#define IOP_IR_DATA() (regs0->iop_data[6])
#define TRANS_IR_CODE(rx) (BYTE)(rx&0x00ff)
#elif  defined(IR_TDP101)//lijd 2005-3-25 10:16
#define IOP_IR_DATA() (regs0->iop_data[6])
#define TRANS_IR_CODE(rx) (BYTE)(rx&0x00ff)
#elif  defined(IR_HT220MCU)//2005-4-14 14:57 zhoulin
#define IOP_IR_DATA() (regs0->iop_data[6])
#define TRANS_IR_CODE(rx) (BYTE)(rx&0x00ff)
#else
#define IOP_IR_DATA() (regs0->iop_data[6])
#define TRANS_IR_CODE(rx) reverse_fun(rx)
#endif

#if defined(IR30)||defined(MINTON_LCD_PANEL_6322_KEY) 			//nono 2003-9-26 11:33 for YILI.
#define CHK_CUST_ID(unCustId) ((unCustId!=IR_ADDR_PATT)&&(unCustId!=IR_ADDR_PATT2))
#elif defined(DESAY_PHILIPS_IR)//CLEAD 2004-3-23 
#define CHK_CUST_ID(unCustId) ((unCustId!=IR_ADDR_PATT)&&(unCustId!=IR_ADDR_PATT2)&&(unCustId!=IR_ADDR_PATT3)&&(unCustId!=IR_ADDR_PATT4))
#elif defined(IR_GBM_PHILIPS)//yth 2004-3-23 
//#define CHK_CUST_ID(unCustId) ((unCustId!=IR_ADDR_PATT)&&(unCustId!=IR_ADDR_PATT2)&&(unCustId!=IR_ADDR_PATT3)&&(unCustId!=IR_ADDR_PATT4))
#define CHK_CUST_ID(unCustId) ((unCustId!=IR_ADDR_PATT)&&(unCustId!=IR_ADDR_PATT3))//gerry modified it,when TV mode,these keys should not be functional,2004-7-29 22:31
#elif defined(OP_DVD5121_PANEL) //qinhua add for 5121
#define CHK_CUST_ID(unCustId) ((unCustId!=IR_ADDR_PATT)&&(unCustId!=IR_ADDR_PATT_T))
#elif  defined(IR_PHILIPS_EASTECH)		//wangmin add for philhps rc6
#define CHK_CUST_ID(unCustId) ((unCustId!=IR_ADDR_PATT)&&(unCustId!=IR_ADDR_PATT2)&&(unCustId!=IR_ADDR_PATT3)&&(unCustId!=IR_ADDR_PATT4)&&(unCustId!=IR_ADDR_PATT5))
#else

	#ifdef IR_TOOL
	#define CHK_CUST_ID(unCustId) (unCustId!=IRAddr)
	#else
#define CHK_CUST_ID(unCustId) (unCustId!=IR_ADDR_PATT)

#endif 
#endif 

#ifdef IR_ADDR_PATT_ERR_SHOW_INVALID//nono 2-9-23 13:08
#define show_ir_custid_err() invalid_key()
#else
//#define show_ir_custid_err();                       // Removed by LuoLiuyi at 2006-8-17
static inline void show_ir_custid_err(UINT16 unCustId)   // Added by LuoLiuyi at 2006-8-17
{
       osd_init__();
	psprintf(linebuf,"IR ADDR UNMATCH R:%04x VS S:%04x", unCustId,IR_ADDR_PATT);
	strcpy(RegionValStr[REGION1], linebuf);
	PrintOsdMsg(STR_OS_SPACE, REGION1, 4, 1);	
}
#endif

#if defined(IR30) //philip ir 			//2-10-15 11:12
void adj_ir_rxcode(UINT8 chk,UINT16 *rx,UINT16 offset)
{
    if(chk)
	{
		switch(*rx)
		{
			case 0x30:
			case 0x32:
			case 0x33:
			case 0x34:
				*rx+=offset;
			break;
			default:
				break;
		}
	}
}
#elif defined(MINTON_LCD_PANEL_6322_KEY) ////nono 2003-9-26 11:33 for YILI.
void adj_ir_rxcode(UINT8 chk,UINT16 *rx,UINT16 offset)
{
    if(chk)
	{
		switch(*rx)
		{
			case 0x41:
			case 0x57:
			case 0x00:
			case 0x10:
			case 0x4F:
			case 0x4B:
				*rx=*rx+offset+0x6C;
			break;
			default:
				break;
		}
	}
}
#else
#define adj_ir_rxcode(chk,rx,offset);
#endif
//TCL STANDBY

static inline void ir_tcl_standby(void)
{
#ifdef TCL_STANDBY    
        static BYTE powerkeystate=0;
        BYTE flag;
        flag = (regs0->gpio_in[2/16] >> (2%16)) & 0x01;
        if((!flag ) && powerkeystate)
        {
                call_ir_func(IRC_POWER);
                regs0->sft_cfg1 &= ~(0x1 << 3);//gpio 3 enable
                regs0->gpio_master[ 3/16 ] &= ~(0x1 << (3%16));//gpio 3 for iop
                regs0->gpio_master[ 2/16 ] &= ~(0x1 << (2%16));//gpio 2 for iop
        }
        powerkeystate = flag;
#endif        
}



//=========================================================================================
// debug function
//=========================================================================================
/*
* display ir id
*/
#ifndef IR_TOOL
#ifdef  DEBUG_IR_CODE
static inline void watch_ir_id(UINT16 rx)
{
    psprintf(linebuf, "IR:%02x, F:%02x", rx, ir_mapcode[rx]);
    strcpy(RegionValStr[REGION1], linebuf);
    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
}
#else
#define  watch_ir_id(rx);   
#endif
#else
	static inline void watch_ir_id(UINT16 rx)
	{
	    psprintf(linebuf, "IR:%02x, F:%02x", rx, ir_mapcode[rx]);
	    strcpy(RegionValStr[REGION2], linebuf);
	    PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
	    //printf("IR:%02x,F:%02x\n",rx, ir_mapcode[rx]);
	    printf("%02x\n",rx);
	}
#endif
/*
* display ir's customer id
*/
#ifndef IR_TOOL
#if WATCH_CUSTID            
static inline void watch_ir_custm_id(UINT16 unCustId)
{
    psprintf(linebuf,"ID : %04x", unCustId);           
    strcpy(RegionValStr[REGION2], linebuf);
	PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
}
#else
#define watch_ir_custm_id(x);  
#endif
#else
	static inline void watch_ir_custm_id(UINT16 unCustId)
	{
	    	psprintf(linebuf,"ID : %04x", unCustId);           
	    	strcpy(RegionValStr[REGION2], linebuf);
		PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
		printf("%04x\r\n",unCustId);
			if(watch_ir_id_value)
			IRAddr=unCustId;
	}
#endif
/*
* monitor can input ir function
*/
#ifndef DVDRELEASE
UINT32 monir;
static inline void mon_ir(void)
{	  
    if (monir){
        call_ir_func(monir & 0xff);
        monir=0;
    }
}
#else
#define mon_ir();
#endif


#ifdef MALATA_KEY
#include "fsNAV.h"
BYTE malata_key_check(BYTE rx);
BYTE malata_key_check(BYTE rx)
{
//20051207  tiany test  
//if(rx == IRC_1) rx =  IRC_EJECT;
//if(rx == IRC_2) rx =  IRC_UP_NEXT ;
//if(rx == IRC_0) rx =  IRC_DOWM_PREV ;
//if(rx == IRC_5) rx =  IRC_LEFT_FR ;
//if(rx == IRC_7) rx =  IRC_RIGHT_FF ;
#ifdef ONE_TWO_THREE_FOUR_CHANGE//tianye 200607
if(rx == IRC_1) {xxx = 0; yyy = 0;}
if(rx == IRC_2) {xxx = 0; yyy = 1;}
if(rx == IRC_3) {xxx = 1; yyy = 0;}
if(rx == IRC_4) {xxx = 1; yyy = 1;}
#endif//end=> #ifdef ONE_TWO_THREE_FOUR_CHANGE

//--------------------------
 BYTE  flag_direction_key = 0;
 if((rx == IRC_AUD_LANGUAGE)&&(cd_type_loaded!=CDDVD))
 {

       if((rx == IRC_AUD_LANGUAGE)&&(cd_type_loaded == CDROM)&& (pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER))
       {
            rx = IRC_AUD_LANGUAGE  ;
	 }
	 else
	 {
   		rx =  IRC_CHANNEL;
 	 }
 }


 if((full_scrn&SETUP)||(full_scrn&CUSTM)||(Is_Dvb_State())||(full_scrn&GOTO)
   ||/*(is_menu()&&(cd_type_loaded==CDDVD))||*/(vpp_zoom>=ZOOMIN_BASE && vpp_zoom<=ZOOMIN_MAX)
   ||((cd_type_loaded==CDROM)&&(pFsJpeg->gifsState != FS_STATE_OTHER))
   ||((HL_exist)&&(cd_type_loaded==CDDVD))//20060206 tiany add fix err
   )//20060525 tiany mark  /*(is_menu()&&(cd_type_loaded==CDDVD))||*/ for key err
 {
   flag_direction_key = 1;
 }
 switch(rx)
 {
   case(IRC_UP_NEXT): 
   {
      if(flag_direction_key)
	  {
        	rx = IRC_UP;
	  }
	  else
	  {
	    	rx = IRC_NEXT;
	  }
      break;
   }		 
   case(IRC_DOWM_PREV):
   {
	  if(flag_direction_key)
	  {
        	rx = IRC_DOWN;
	  }
	  else
	  {
	    	rx = IRC_PREV;
	  }
      break;
   }	   
   case(IRC_LEFT_FR): 
   {
	  if(flag_direction_key)
	  {
        	rx = IRC_LEFT;
	  }
	  else
	  {
	    	rx = IRC_BACKWARD;
	  }
      break;
   }
   case(IRC_RIGHT_FF): 
   {
	  if(flag_direction_key)
	  {
        	rx = IRC_RIGHT;
	  }
	  else
	  {
	    	rx = IRC_FORWARD;
	  }
      break;
   }
   default:
			break;
    };
   return rx; 
} 
#endif//end=>#ifdef MALATA_KEY


//=========================================================================================
// ir driver function
//=========================================================================================
/*
* encode ir id
*/
int reverse_fun(int rx)
{
    rx=rx&IRC_MASK;

    return revn(rx,8);
}
/*
** FUNCTION
** reset_ir
**
** DESCRIPTION
** reset IR interface (and queue) according to irconfig.h
*/
void    reset_ir(void)
{
#if defined(QISHENG_DVD)||defined(SUPPORT_IR_GAME)	//alan, 2003/9/7 08:05PM
	regs0->iop_data[IR_PORT]|=IrRepeatRate(6);
#elif defined(HOLD_VOL_KEY_FAST_REPEAT)
    regs0->iop_data[IR_PORT]|=IrRepeatRate(1);
#elif defined(IR_GBM_PHILIPS)||defined(IR_PHILIPS)//gerry modified philips ir timing for lijd's suggestion,2004-8-4 16:35
	regs0->iop_data[IR_PORT]|=IrRepeatRate(2);
#elif ( defined(IR_M3004)||defined(IR_ORITRON) )&& !defined (OP_DVD5121_PANEL)
    regs0->iop_data[IR_PORT]|=IrRepeatRate(8);	
#elif  defined(OP_DVD5121_PANEL) //qinhua ,add for5121
   regs0->iop_data[IR_PORT]|=IrRepeatRate(1);		
#elif  defined(IR_THOMSON)//wurh add 2006-3-21 05:31ÏÂÎç
    regs0->iop_data[IR_PORT]|=IrRepeatRate(8);
#elif  defined(IR_KONKA)//nono 20050224
    regs0->iop_data[IR_PORT]|=IrRepeatRate(8);
#elif  defined(IR_TDP101)//lijd 2005-3-25 10:17
    regs0->iop_data[IR_PORT]|=IrRepeatRate(6);      
#elif  defined(IR_THOMSON_ANGUS)
    regs0->iop_data[IR_PORT]|=IrRepeatRate(6);      
#else
    regs0->iop_data[IR_PORT]|=IrRepeatRate(4);
#endif
}

/*
* detect ir key input,using to search tuner band
*/
//#ifdef SUPPORT_TUNER       // add tuner 2-6-14 23:17
BYTE key_input(void)
{
    BYTE res;
    //need to add vfd key input
    
    if(regs0->iop_data[IR_PORT]&IR_RDY)
      res=1;
    else
      res=0;

   return res;
}
//#endif

#if defined(DESAY_PHILIPS_IR)||defined(IR_GBM_PHILIPS)
UINT16    desay_philips_ir_move(UINT16 rx)
{

	if(((regs0->iop_data[6]>>6)&0x5f) == IR_ADDR_PATT)
        {
	switch(rx)
                {
                case 0x30:
                case 0x32:
                case 0x33:
                case 0x34:
                    rx+=0x10;
                    break;
                case 0x11:
                case 0x12:
                case 0x13:
                    rx+=0x40;
                    break;
                default:
                    break;
               	}
            }
       else	if(((regs0->iop_data[6]>>6)&0x5f) == IR_ADDR_PATT2)
            {
			    switch(rx)
                {

                case 0x06:
                    rx+=0x40;
                    break;
                case 0x02c:
                case 0x02e:
                case 0x02f:
                    rx+=0x20;
                    break;
                default:
                    break;
                	}
            }
       else	if(((regs0->iop_data[6]>>6)&0x5f) == IR_ADDR_PATT3)
       {
                switch(rx)
                {
			    case 0x032:
                case 0x033:
                    rx+=0x15;
                    break;
                default:
                    break;
                	}
		}
       else	if(((regs0->iop_data[6]>>6)&0x5f) == IR_ADDR_PATT4)
            {
			    switch(rx)
                {

                case 0x2c:
                	rx+=0x30;
                    break;
                default:
                    break;
                	}
            }
	return rx;            
}
#endif //CLEAD 2004-3-23

#ifdef  IR_GBM_PHILIPS  //added by wangwei,2004-8-16 20:09
    UINT16  gbm_philips_ir_move(UINT16 rx)
    {
        desay_philips_ir_move(rx);
    }
#endif  //IR_GBM_PHILIPS

/*
* call ir post function (ir parser)
*/
#if defined(DEBUG_IR_CODE)||defined(IR_PHILIPS)
static inline BYTE Call_Ir_Fun(UINT16 rx)
{
#ifdef	 DESAY_PHILIPS_IR

	rx=desay_philips_ir_move(rx);
    rx = ir_mapcode[(BYTE) rx];    
    #ifndef IR_TOOL
    printf("\n ir(705) rx = %x \n",rx);
    call_ir_func(rx);
    #endif
#elif defined(IR_GBM_PHILIPS)
	rx=gbm_philips_ir_move(rx);
    #ifdef DEBUG_IR_CODE//gerry add it for philips ir,2004-8-4 16:41
	watch_ir_id(rx);
	return; 
    #endif
    rx = ir_mapcode[(BYTE) rx];    
    #ifndef IR_TOOL
    printf("\n ir(705) rx = %x \n",rx);
    call_ir_func(rx);
    #endif
#else
    #ifdef DEBUG_IR_CODE//gerry add it for philips ir,2004-8-4 16:41
	watch_ir_id(rx);
	return; 
    #endif
    rx = ir_mapcode[(BYTE) rx];    
    #ifndef IR_TOOL
    printf("\n ir(705) rx = %x \n",rx);
    call_ir_func(rx);
    #endif
#endif
	return rx;
}
#else
static inline BYTE Call_Ir_Fun(UINT16 rx)
{
	if(rx >= MAX_IR_MAP) // Out of MAP range?
        return 0;
    #ifdef TEST_VFD_PANNEL_AND_KEY//lijd 2005-5-8 13:53
	 if(Test_Front_Panel_flag==1)
	 {
	 	 TestIrData=(BYTE)rx;
	 	 if(Test_Stop_flag!=1)
	 	 {
		  	 if((rx!=0x11)&&(rx!=0x26))    return 0; 
		 }else if(Test_Stop_flag==1)
		 {
		 	 if(rx!=0x11)    return 0; 
		 }
	 }
     #endif 
    rx = ir_mapcode[(BYTE) rx]; 
    #ifdef MALATA_KEY
	rx=  malata_key_check(rx);
    #endif //end-> #ifdef MALATA_KEY

    
    #ifdef DMA_DVD_SWITCH
    extern void DMA_DVD_Switch(UINT16 rx);
    DMA_DVD_Switch(rx);
    #endif
    
  
       
    #ifndef IR_TOOL
    printf("\n ir(705) rx = %x \n",rx);
    call_ir_func(rx);
    #endif

    #ifdef TONIC_DVD
    if(rx==IRC_KEYLOCK)
    ircmd_keylock();
    #endif

    return 0;
}    
#endif                

#ifdef USE_VFDPORT_TRANDATA //linrc add 2004-3-27 16:40
#define USE_VFDPORT_TRANDATA_return(); return IRC_NULL;
#else
#define USE_VFDPORT_TRANDATA_return();
#endif

#ifdef  SUPPORT_SPI
#define SUPPORT_SPI_return(); return IRC_NULL; 
#else
#define SUPPORT_SPI_return();
#endif

#ifdef TCL_VFD_GPIO//2004-3-22 12:49 lijd
#define call_SUPPORT_TCL_LED();   tcl_led();
#else
#define call_SUPPORT_TCL_LED();
#endif

static inline void NEXT_FORWARD_IN_A_KEY_short_time(UINT16 rx)
{
#ifdef NEXT_FORWARD_IN_A_KEY    	
    	if(bIrSkipState)
    	{
	    	bIrSkipCnt++;	    	
	    	if(bIrSkipCnt>5)
	    	{
	    		if(rep_ir_times==0)
	    		{
	    			
#ifdef NEW_NEXT_FORWARD_IN_A_KEY
		    		rx = IRC_PREV + bIrSkipState -1;
#else//#ifdef NEW_NEXT_FORWARD_IN_A_KEY
                    rx = IRC_BACKWARD + bIrSkipState -1;      
#endif//#ifdef NEW_NEXT_FORWARD_IN_A_KEY

		        	ircmd_pre_paser(rx);

                }
		    
		        bIrSkipState = 0;
	    	    bIrSkipCnt = 0;
	    	    rep_ir_times = 0;
	    	}
    	}
#else
    if(rx) {}    	
#endif//NEXT_FORWARD_IN_A_KEY
}

static inline void NEXT_FORWARD_IN_A_KEY_long_time(UINT16 rx)
{
#ifdef NEXT_FORWARD_IN_A_KEY	        		    
    bIrSkipCnt = 0;
    if(rep_ir_times<=2)
    {
       	rep_ir_times=2;
#ifdef NEW_NEXT_FORWARD_IN_A_KEY
       	rx = IRC_BACKWARD + bIrSkipState -1;
#else//NEW_NEXT_FORWARD_IN_A_KEY
       	rx = IRC_PREV + bIrSkipState -1;
#endif//NEW_NEXT_FORWARD_IN_A_KEY
       	//printf("run rx:%d \n",rx);
       	ircmd_pre_paser(rx);
    }else if(rep_ir_times>3)
	{
		rep_ir_times = 1;
	}
#else
  if(rx) {}
#endif	
}


#if defined(SUPPORT_DVB_GUI_NEW)&&defined(DVB_IR_3D_ON)
static inline BYTE is_available_key_in_3D_state(BYTE rx __attribute__((unused)))
{  
    if((ir_mapcode[(BYTE) rx]==IRC_SELECT) || (ir_mapcode[(BYTE) rx]==IRC_PLAY_SELECT)
        ||(ir_mapcode[(BYTE) rx]==IRC_UP) || (ir_mapcode[(BYTE) rx]==IRC_DOWN)
        ||(ir_mapcode[(BYTE) rx]==IRC_LEFT) || (ir_mapcode[(BYTE) rx]==IRC_RIGHT)
        ||(ir_mapcode[(BYTE) rx]==IRC_3D)
      )
    return 1;
    
    return 0;
}

static inline BYTE InDVB3DNow(BYTE rx __attribute__((unused)))
{
    if(!(full_scrn&SOUND))
        return 1;
    /*    
    if((ir_mapcode[(BYTE) rx]==IRC_SETUP) || (ir_mapcode[(BYTE) rx]==IRC_DISPLAY)
    #ifdef DVB_IR_SCAN_KEY    //sunzhh add 20051117
    || (ir_mapcode[(BYTE) rx]==IRC_GOTO)
    #endif
    #ifdef SUPPORT_DVB_PREVIEW_9FRAMES     //sunzhh add 20051117
    || (ir_mapcode[(BYTE) rx]==IRC_PREVIEW)
    #endif
    */
    if(!is_available_key_in_3D_state(rx))
    {
        cancel_sound();
        return 1;
    }
    
    return 0;
} 
#endif
	

#ifdef  SLOW_SOME_KEY_IN_MALATA_IR
void  slow_key_update();
void  slow_key_update()
{
 
	if(clear_key == 1)
	{
	      // printf_w("@@@@@@@@@@@     clear_count ++;    clear_count:%d\n",clear_count);//20051207 tiany debug	 
		clear_count --;
		if(clear_count < 1)
		{
                  clear_key = 0;
		    clear_count = 0;	  
		//	printf_w("@@@@@@@@@@@     clear_key = 0;    @@@@@@@@@@@@@@@\n");//20051207 tiany debug	
		}	   
	}
	else
	{
		clear_count = 0;
	}
}	
#endif



	
/*
** FUNCTION
** polling_ir
**
** DESCRIPTION
** polling IR interface and store received IR command
** to IR receive queue
*/
#ifdef XM_MODEL		//fcr 2005-11-3 17:39
        extern unsigned char XMkey_release_hold;
#endif
BYTE polling_ir(void)
{
    #ifdef OP_DVD5121_PANEL //qinhua ,2005-9-13 22:55
    static BYTE count;  	    
    #endif 
    UINT16 rx;    
    UINT16 unCustId;
    #if defined(HOLD_VOL_KEY_FAST_REPEAT)
    static UINT16 rep_ir_hold_times=0;
    static BYTE ir_key_clone_times=0;//insert clone key to increase repeat speed
        #ifdef SUPPORT_MCU_68A
        #define MIN_IR_REPEAT_TIME 3
        #define MIN_IR_REPEAT_TIME_N 5//2
        #define IR_CLONE_TIME 0
        #else
        #define MIN_IR_REPEAT_TIME 4
        #define MIN_IR_REPEAT_TIME_N 5//3
        #define IR_CLONE_TIME 0
        #endif
    #endif
    
    //... terry,2004/7/23 10:56PM
    USE_VFDPORT_TRANDATA_return();
    SUPPORT_SPI_return();
    ir_tcl_standby();
    call_SUPPORT_TCL_LED();    
    mon_ir();	
    #ifdef  SLOW_SOME_KEY_IN_MALATA_IR
    slow_key_update();
    #endif
   #ifdef SUPPORT_SYS_POWER_ON_WAITING_MCUINFO//tianye 200607
   if(!flag_check_mcu_info)
   {
         return;
   }
   #endif//end=> #ifdef  SUPPORT_SYS_POWER_ON_WAITING_MCUINFO

    rx = regs0->iop_data[IR_PORT];
    if (!(rx & IR_RDY))
    {
     #ifdef OP_DVD5121_PANEL //qinhua ,2005-9-13 22:55
       count=0; 
     #endif 
     #ifdef XM_MODEL     //fcr 2005-11-3 17:39
         if(XMkey_release_hold)XMkey_release_hold--;
     #endif
    	//printf("bIrSkipState:%d rep_ir_times:%d bIrSkipCnt:%d \n",bIrSkipState,rep_ir_times,bIrSkipCnt);
        NEXT_FORWARD_IN_A_KEY_short_time(rx);
        
#if defined(ANGLE_GOTO_IN_A_KEY)||defined(TITLE_RETURN_IN_A_KEY)  	
    	if(bIrSkipState1)
    	{
	    	bIrSkipCnt1++;	    	
	    	if(bIrSkipCnt1>5)
	    	{
	    		if(rep_ir_times==0)
	    		{
	    			#ifdef TITLE_RETURN_IN_A_KEY
	    			rx=IRC_TITLEMENU;
	    			#else
	    			rx=IRC_GOTO;
	    			#endif
		        	ircmd_pre_paser(rx);

		        }
		        bIrSkipState1 = 0;
	    	    	bIrSkipCnt1 = 0;
	    	   	rep_ir_times = 0;
	    	}
    	}
#endif
        
#ifdef SLOW_ZOOM_IN_A_KEY    	
    if(bIrSkipState2)
    {
    	bIrSkipCnt2++;	    	
    	if(bIrSkipCnt2>5)
    	{
    	    if(rep_ir_times==0)
    	    {
    		    rx=IRC_ZOOM;
                ircmd_pre_paser(rx);
            }
            bIrSkipState2 = 0;
	        bIrSkipCnt2 = 0;
            rep_ir_times = 0;
    	}
    }
#endif
        
#ifdef QISHENG_DVD	// alan, 2003/9/7 06:30PM    	
    	if (pressed==IRC_PLAY)
    	{
    		if (not_rdy_times>=2)
    		{
	    		rep_ir_times=0;
	    		not_rdy_times=0;
	    		pressed=IRC_NULL;
	    		if(dvd_menu_play==1)
                {//terry,2003/9/12 02:35PM
                  if(IsPBCOn()||(cd_type_loaded==CDDVD))
                  {
                     ircmd_playmode_toggle();
                     return IRC_NULL;
                  }
                }
	    		return Call_Ir_Fun(0x55);	// call IRC_Play, at ir_mapcode position 0x55
	    	} else {
	    		not_rdy_times++;
	    	}
    	} else if (pressed==IRC_DEFAULT_SETUP)
    	{
    		rep_ir_times=0;
    		pressed=IRC_NULL;
    		return Call_Ir_Fun(0x56);	// call IRC_DEFAULT_SETUP, at ir_mapcode position 0x56
    	}
#endif
        #if defined(HOLD_VOL_KEY_FAST_REPEAT)
        if(ir_key_clone_times>0)//insert clone key
        {
            ir_key_clone_times--;
            rx = TRANS_IR_CODE(rx); 
        }
        else
        #endif
        return IRC_NULL;
    }
    else
    {
		//terry,2003/7/14 01:24PM
        if ((rep_ab_mode==REPEAT_FIND_B) && 
			(sys_cmd==(CMD_FUNC|CMD_FUNC_REPAB)) && 
			(cd_type_loaded != CDROM)) // Robert 2004/02/06
        {
			//when system(nav.c) post CMD_FUNC_REPAB to navigation, and navigation tries to exit MediaMain and enter again
			//In the meanwhile, rep_ab_mode can't be set to REPEAT_AB_IDLE
			//For VCD, system will playtrack and then correct s_msf
			//if rep_ab_mode==REPEAT_AB_IDLE, s_msf will not be corrected, and it will jump to the start of this track
			printf("waiting for navigator\n");
			return IRC_NULL;;
        }

        unCustId=IOP_IR_DATA();        
        
        regs0->iop_data[IR_PORT] = rx & (~IR_RDY);        
        #ifdef IR_TOOL
        if (watch_ir_id_value==1)
        	{
        watch_ir_custm_id(unCustId);        
        return IRC_NULL;  
        	}
        #else
        watch_ir_custm_id(unCustId);  
		#endif
	
        if(CHK_CUST_ID(unCustId))
        {
       #ifdef IR_ADDR_PATT_ERR_SHOW_INVALID
            show_ir_custid_err();
	#else
             show_ir_custid_err(unCustId);             //luoliuyi modify 2006-8-17
	#endif
            return IRC_NULL;    
        }
#ifdef XM_MODEL     //fcr 2005-11-3 17:44
            XMkey_release_hold=4;
#endif    
        #if defined(ONLY_VOLUME_REPEAT)||defined(HOLD_VOL_KEY_FAST_REPEAT)
        rx = TRANS_IR_CODE(rx); 
            #ifdef IR_M3004
            if((ir_mapcode[(BYTE) rx]==PANEL_EJECT)||(ir_mapcode[(BYTE) rx]==IRC_EJECT))
            {
                if(!((regs0->iop_data[IR_PORT])&IR_REPEAT))
                    regs0->iop_data[IR_PORT]|=IrRepeatRate(4);
            }
            else if((regs0->iop_data[IR_PORT])&IR_REPEAT)
            {
                regs0->iop_data[IR_PORT]&=~ IrRepeatRate(4);
            }
            #endif//#ifdef IR_M3004
        #endif//#if defined(ONLY_VOLUME_REPEAT)||defined(HOLD_VOL_KEY_FAST_REPEAT)  
        #ifdef HOLD_VOL_KEY_FAST_REPEAT
        if( ((regs0->iop_data[IR_PORT])&IR_REPEAT) &&
            (rep_ir_hold_times>=(
            ((ir_mapcode[(BYTE) rx]!=IRC_VOLUME_UP)&&(ir_mapcode[(BYTE) rx]!=IRC_VOLUME_DN))
            ?MIN_IR_REPEAT_TIME_N:MIN_IR_REPEAT_TIME)))
        #else
        if( (regs0->iop_data[IR_PORT])&IR_REPEAT )
        #endif     
        {
			#ifdef OP_DVD5121_PANEL    //qinhua ,add 2005-9-13 22:55
			    
		  	if (count==0) 
		    {
		       count+=1;
		       printf("\n\n============ count1: ==============%d\n\n",count); 
               rep_ir_times++;         
		    }
		  	else if (count<6)
		    {
		        count++;
		        printf("\n\n============ count2: ==============%d\n\n",count); 
				return IRC_NULL;
			       
			}
		    else  
			{			      
            	rep_ir_times++;         
			 	count=1;
			 	printf("\n\n============ count3: ==============%d\n\n",count); 
			} 
		  	#else//#ifdef OP_DVD5121_PANEL 
		    rep_ir_times++;
		    
              #ifdef XM_MODEL     //fcr 2005-11-3 17:39
		    	    if(rep_ir_times>10)rep_ir_times=10;
		  	#endif    
		  #endif//#ifdef OP_DVD5121_PANEL 
            #if defined(HOLD_VOL_KEY_FAST_REPEAT)
            if((ir_mapcode[(BYTE) rx]==IRC_VOLUME_UP)||(ir_mapcode[(BYTE) rx]==IRC_VOLUME_DN))
                ir_key_clone_times=IR_CLONE_TIME;
            else
                {
                rep_ir_hold_times=0;
                ir_key_clone_times=0;
                }
		  	#endif//#if defined(HOLD_VOL_KEY_FAST_REPEAT)
			                   

        	//printf("rep:%d bIrSkipState:%d\n",rep_ir_times,bIrSkipState);

#ifdef NEXT_FORWARD_IN_A_KEY	        		
        	if(bIrSkipState)
        	{//bw:1 ff:2
        	    NEXT_FORWARD_IN_A_KEY_long_time(rx);        	    	
	        	return;//0;//0 maybe wrong , but a non-void function must return a value
    	    }
#endif//NEXT_FORWARD_IN_A_KEY                     
#if defined(ANGLE_GOTO_IN_A_KEY)||defined(TITLE_RETURN_IN_A_KEY)   		
        	if(bIrSkipState1)
        	{
        	    bIrSkipCnt1 = 0;
        	    #ifdef TITLE_RETURN_IN_A_KEY
        	    if(rep_ir_times<2)
        	    #else
        	    if(rep_ir_times<=2)
        	    #endif
        	    {
        	    	rep_ir_times=2;
        			#ifdef TITLE_RETURN_IN_A_KEY
        			rx=IRC_RETURN;
        			#else
					rx=IRC_ANGLE;
        			#endif
        	    	//printf("run rx:%d \n",rx);
        	    	ircmd_pre_paser(rx);
        	    }
        	    #ifndef TITLE_RETURN_IN_A_KEY
        	    else 
        	    	if(rep_ir_times>3)
	        	{
	        		rep_ir_times = 1;
	        	}	
	        	#endif
	        	return;//0;//0 maybe wrong , but a non-void function must return a value
    	    }
#endif//ANGLE_GOTO_IN_A_KEY                     

#ifdef SLOW_ZOOM_IN_A_KEY	        		
    if(bIrSkipState2)
    {
        bIrSkipCnt2 = 0;
        if(rep_ir_times<=2)
        {
    	    rep_ir_times=2;
            rx=IRC_SLOW;
    	    ircmd_pre_paser(rx);
        }
        else if(rep_ir_times>3)
    	{
    	    rep_ir_times = 1;
    	}	
    	return;//0 maybe wrong , but a non-void function must return a value
    }
#endif

#ifdef QISHENG_DVD	// alan, 2003/9/7 06:31PM
		not_rdy_times=0;
		if (rep_ir_times>=4)
		{
		    /*if (irc_value==IRC_STOP)
		    {
				pressed=IRC_POWER;
            	irc_value=IRC_NULL;
			}*/
		    if (irc_value==IRC_DEFAULT_SETUP)
		    {
            	pressed=IRC_DEFAULT_SETUP;
            	irc_value=IRC_NULL;
			}
		}
#endif

#ifdef ONLY_VOLUME_REPEAT//wangap add 04/5/20
        if((ir_mapcode[(BYTE) rx]!=IRC_VOLUME_UP)&&(ir_mapcode[(BYTE) rx]!=IRC_VOLUME_DN))
            return IRC_NULL;
#elif defined(ONLY_COMPUND_KEY_REPEAT)&&defined(NEXT_FORWARD_IN_A_KEY)&&defined(ANGLE_GOTO_IN_A_KEY)
        if((ir_mapcode[(BYTE) rx]!=IRC_PREV)&&(ir_mapcode[(BYTE) rx]!=IRC_NEXT)&&(ir_mapcode[(BYTE) rx]!=IRC_ANGLE))
            return IRC_NULL;
#elif defined(ONLY_VOL_DIR_REPEAT)//chenzhao20051013
        if((ir_mapcode[(BYTE) rx]!=IRC_VOLUME_UP)&&(ir_mapcode[(BYTE) rx]!=IRC_VOLUME_DN)
            &&(ir_mapcode[(BYTE) rx]!=IRC_UP)&&(ir_mapcode[(BYTE) rx]!=IRC_DOWN)
            &&(ir_mapcode[(BYTE) rx]!=IRC_LEFT)&&(ir_mapcode[(BYTE) rx]!=IRC_RIGHT)
            &&(ir_mapcode[(BYTE) rx]!=IRC_SELECT))
            return IRC_NULL;
#endif            
#ifdef IR_NO_REPEAT
            return IRC_NULL;
#endif
        }
        else	//have key no repeat
        {
            #ifdef HOLD_VOL_KEY_FAST_REPEAT
            ir_key_clone_times=0;
            if((regs0->iop_data[IR_PORT])&IR_REPEAT)
            {
                rep_ir_hold_times++;
                return IRC_NULL;
            }
            else
        	{
                rep_ir_hold_times=0;
            }
            #endif
            rep_ir_times=0;
        }
    }

    save_srn_start_t = get_rtc_val();
    
    #if !(defined(ONLY_VOLUME_REPEAT)||defined(HOLD_VOL_KEY_FAST_REPEAT))
    rx = TRANS_IR_CODE(rx);
    #endif
    #ifdef IR_TOOL
    adj_ir_rxcode(unCustId==IRAddr,&rx,0x10);
    #else
    adj_ir_rxcode(unCustId==IR_ADDR_PATT,&rx,0x10);
    #endif
    adj_ir_rxcode(unCustId==IR_ADDR_PATT2,&rx,0x15);
    #ifdef IR_TOOL
    	if (watch_ir_value==1)  
    		{
    watch_ir_id(rx);   
	    		return IRC_NULL;
    		}
   #else
    	watch_ir_id(rx); 
   #endif
#ifdef QISHENG_DVD	// alan, 2003/9/7 06:32PM
	if (pressed==IRC_NULL)
	{		
		irc_value = ir_mapcode[(BYTE) rx];
		/*if (irc_value==IRC_STOP) 
		{
			pressed=IRC_STOP;
			return IRC_NULL;
		}*/
		if (irc_value==IRC_DEFAULT_SETUP) 
		{
			pressed=IRC_PLAY;
			return IRC_NULL;
		}
	}
#endif

#ifdef BBK_DV961_DVD   // fengjl edit  4-2-5 19:56
    //NOTE:
    //need contious 3s to change video output.
    //zhaoyanhua add 03-10-22 21:36
    if(	  (ir_mapcode[(BYTE) rx]  == IRC_ONLY_P_SCAN)
#ifdef ONLY_VGA_KEY
       	||(ir_mapcode[(BYTE) rx]  == IRC_VGA)
#endif
    	||(ir_mapcode[(BYTE) rx]  == IRC_INTERLACE)	
    	)
    {
    	if(rep_ir_times <= 3)
    		return;
    }
#endif//BBK_DVD

#ifdef BOOMBOX_NOT_USE_SOME_IR_KEYS//nono 2003-11-17 1:02 for YILI.
    if(	  (ir_mapcode[(BYTE) rx]  == IRC_POWER)
       	||(ir_mapcode[(BYTE) rx]  == IRC_MUTE)
    	||(ir_mapcode[(BYTE) rx]  == IRC_VOLUME_UP)	
    	||(ir_mapcode[(BYTE) rx]  == IRC_VOLUME_DN)	
    	)
    {
    		return;
    }
#endif//BOOMBOX_NOT_USE_SOME_IR_KEYS

#ifdef PORTABLE_DVD		//rbhung for Portable DVD HOLD IR
#ifdef HOLD_KEY_DETECT
if(hold_state)
    return IRC_NULL;
#endif
#endif

#ifdef SYBER_NATIVE_DVD_TYPE	
	if((rx == 0x1c) ||(rx == 0x0b) || (rx == 0x07) ||(rx == 0x13)
		||(rx == 0x00) ||(rx == 0x40) || (rx == 0x14) || (rx == 0x47) || (rx == 0x48))
	    return 0;
#endif //Maoyong 2003/12/17 16:20 for mask syber DVD vol+-, stdby and so on

#ifdef SUPPORT_DVD_NATIVE_GAME		//linrc for NATIVE_GAME 2005-10-18 13:54
	if(system_state==SYSTEM_DVDGAME)
	{
    	if(Dvb_ircmd_pre_parser(rx))
    		return 0;
    }
#endif

#ifdef  SLOW_SOME_KEY_IN_MALATA_IR
        #if 0
	if((ir_mapcode[(BYTE) rx]==IRC_SETUP)||(ir_mapcode[(BYTE) rx]==IRC_DOWN)
		||(ir_mapcode[(BYTE) rx]==IRC_UP)||(ir_mapcode[(BYTE) rx]==IRC_LEFT)
		||(ir_mapcode[(BYTE) rx]==IRC_RIGHT)||(ir_mapcode[(BYTE) rx]==IRC_DVB_DVD))
	#endif
	if(ir_mapcode[(BYTE) rx] > 0)
	{
	     if(clear_key == 1)
	     {
                  return  IRC_NULL;
	     }
            else
            {
                 clear_key = 1;
		   clear_count = SLOW_TIME;
	      }
	}
#endif

#ifdef SUPPORT_SHOW_KEYLOCK_WARNING//tianye 200607
if(rx == LOCKKEY_VALUE)
//if(ir_mapcode[(BYTE) rx] == IRC_1)	
{  //IRC_1
   
  psprintf(RegionValStr[REGION1],WARING_STRING);
 if(Is_Dvb_State())
 {
    DVB_PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
 }
 else
 {

	PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
 }
  return 0;
}
#endif//end=> #ifdef SUPPORT_SHOW_KEYLOCK_WARNING 


#ifdef SUPPORT_8202_DVB //Maoyong 2005-6-1 10:47
	#if defined(SUPPORT_DVB_GUI_NEW)&&defined(DVB_IR_3D_ON)
	if((Is_Dvb_State() && InDVB3DNow(rx)))
	#elif defined(SUPPORT_DVB_GUI_NEW)
	if(Is_Dvb_State()) //David for 8202/6600
	#endif	
	{
        #ifdef MALATA_KEY
		BYTE ir_num = 0;
		ir_num = malata_key_check(ir_mapcode[(BYTE) rx]);
		if(ir_num)
		{
	           if(Dvb_ircmd_pre_parser(ir_num))
	           {
			  return 0;
	           } 	
		}
		else
		#endif//end=>#ifdef MALATA_KEY	
    	if(Dvb_ircmd_pre_parser(ir_mapcode[(BYTE) rx]))
    		return 0;
    }
#endif //SUPPORT_8202_DVB

#if 0//def SUPPORT_SHOW_KEYLOCK_WARNING////tianye mark 200607
if(rx == LOCKKEY_VALUE)
//if(ir_mapcode[(BYTE) rx] == IRC_1)	
{  //IRC_1
  psprintf(RegionValStr[REGION1],WARING_STRING);
  PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
  return 0;
}
#endif//end=> #ifdef SUPPORT_SHOW_KEYLOCK_WARNING 


#ifdef DISPLAY_INDIVIDUAL_SPK_VOLUME//2005-4-19 10:23 zhoulin
    if(regs0->iop_data[3]&0x000f) 
    {   
		show_channel_msg( (regs0->iop_data[3]&0x000f), rx);
		regs0->iop_data[3]=0x0000;
        return 0;
    }
#endif    
#ifdef NEED_DIFF_IR_PANEL_KEY
    if(panel_key_flag)
      panel_key_flag |= (0x01<<2);
#endif 
    return Call_Ir_Fun(rx);

}

#ifdef  SUPPORT_SPI
#include "spi.c"
#endif

