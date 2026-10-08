#ifndef __USER_INIT_H
#define __USER_INIT_H

#include "ver.h"
//
// FILE
// user_init.h
//
// DESCRIPTION
// user selectable input

/*WMA/HDCD:
* "This product is protected by certain intellectual property rights of
* Microsoft and cannot be used or further
* distributed without a license from Microsoft.
*/

//
// *NOTE*
//
//====================================================================
// Define DVD Module
//====================================================================

//#define GENERAL_DVD               //for general dvd mode nono add 5-5-8 18:03
//#define SUNPLUS_DVD
//#define ACTIMA_DVD                 //zhangyu 2004-9-14 09:09zhangyu
//#define AKI_DVD                  //fengjl 03/10/18  for chuangying
//#define ALCO_DVD           //For alco dvd use
//#define ALON_DVD             //2003-12-23 wangap
//#define APEX_DVD              //2004.03.23 maoyong
//#define APOLLO_DVD
//#define ARLINK_DVD			//:huajia//yaowh add 05-03-03
//#define ATLAS_DVD                  //axel 2004/9/13 
//#define AVIQ_DVD                //Jeff 20021115
//#define BBK_DVD                 //fengjl 03/10/16  for bbk 
//#define BMT_DVD
//#define CNMOTOR_DVD             //Jeff 20020913
//#define CONSER_DVD
//#define DESAY_DVD                   //wanghaoying 2003-8-3 1:43
//#define EASTECH_DVD                  //2004-4-2 1:19 WSF FOR DONGYA
//#define EASTWIN_PORTABLE_DVD		//rbhung 2004-09-02
//#define EVERSTAR_DVD               //for EVERSTAR dvd mode
//#define FENGKAI_DVD               //2-12-3 16:19
//#define FUDI_DVD
//#define FUSS_DVD                //#ifdef REMAIN_TIME, must excute "nav.bat"2-7-12 19:31   
//#define GAODASI_DVD             //2-7-16 22:49
//#define GBM_DVD                 //2-9-10 20:29
//#define GBM_AP_DVD                //gerry,2003-12-12 13:09
//#define GBM_PORTABLE_DVD          //jhuang 2003/12/26
//#define GENTEK_DVD          //wanghaoying 2003-9-24 11:40
//#define GOWELLENT_DVD
//#define HARMA_DVD               //3-10-24 1:33张宇P
//#define HANYANG_DVD             //CAOH 2004-4-6 16:48
//#define ARGUS_PORTABLE_DVD              //Hanyang Portable DVD
//#define HOBO_DVD                //Jeff 20020808
//#define HONGTU_DVD                      //2003-11-25 03:50张宇P
//#define HUAJIA_DVD              //KTC_LOADER,must rebuild emu //must rebuild nav & emu.
//#define HUALU_DVD              // lxg 2006-7-18 09:38
//#define HUIFENGYUAN_DVD        //2003/10/13   LJD
//#define HENGCHEN_DVD           //2003/10/13   LJD
//#define IDALL_DVD               //wanghaoying 2003-8-12 21:34 added
#define INTECH_DVD              //xiaosan for intech 02-05-20
//#define JCG_DVD                 //now use as the rom.bin giving to general customer:use yuxing IR & VFD.
//#define JIEKE_DVD
//#define JIEKE_16M_DVD             //clead 
//#define JIANLOON_DVD              //liych  added 2005-3-23
//#define JUNYUAN_DVD               //lizhx  added 2005-01-20
//#define KENLOON_DVD                 //2004-4-14 10:48张宇M
//#define KONKA_DVD               //2-7-10 14:55
//#define KSD_DVD                   // Robert 030710 for Trend Digital
//#define LUCKY_DVD
//#define MALATA_DVD                 //2003-12-19 09:07张宇M
//#define MALATA_GPS_DVD			//frank.huang 2005-8-26
//#define MALATA_PORTABLE_DVD       //tiany 2005-11-18
//#define MICO_DVD
//#define MINTON_DVD                //wanghaoying 2003-8-3 20:03
//#define MUSTEK_DVD                  //Mustek dvd mode
//#define MUSTEK_PORTABLE_DVD           //Mustek portable DVD       
//#define NEWFUSS_DVD                //2003-12-19 09:07张宇M
//#define NINTAUS_DVD                //4-1-10 16:57
//#define NINTAUS_MIDI_DVD            //2004-4-8 09:40张宇M
//#define ORITRON_DVD
//#define ORITRON_HK_DVD              //For HK oritron DVD lijd 2005-5-8 16:17
//#define ORIENTPOWER_DVD           //zhaoyanhua  2004-3-19 11:27
//#define OUR_MIND_DVD
//#define PROVIEW_DVD               // Robert 20030613
//#define PULIANG_DVD               //Yaowh add. 04-12-03
//#define QISHENG_DVD                   // Robert 20030616
//#define QSI_PORTABLE_DVD            //QSI Portable DVD
//#define RONGXING_DVD
//#define SHINCO_DVD
//#define SMT_DVD                 //  fengjl   3-10-23 17:40
//#define SAMBOO_HDDPLAYER_DVD //////////YANGLI2005/8/17
//#define SAMSUNG1_DVD            //for SAMSUNG DVD-???  dvd mode, add by shawn at 910130
//#define SKYWORTH_DVD          // Robert 20030620
//#define SKYTECH_DVD
//#define SUOJIA_DVD
//#define SVA_DVD                 //for shanghai SVA dvd mode 2002-4-30 16:51
//#define SYBER_DVD                //2003-11-19 9:05 David
//#define SZMALATA_DVD              //2004-2-3 01:12张宇P
//#define TEAC_PORTABLE_DVD            //TEAC Portable DVD
//#define THAKRAL_DVD               //2004-9-13 ,suqiaoli
//#define TIANKE_DVD              //2-8-16 11:21
//#define TIANYANG_DVD              //3-6-16 21:44
//#define TONIC_DVD                   //2004-2-3 01:30张宇P
//#define TONGFANG_DVD             //2003-12-23 wangap
//#define VTREK_DVD //wanghaoying 2003-9-9 0:00
//#define WANGINE_DVD             //for WANGINE DVD-??? dvd mode
//#define WEICHENG_DVD
//#define WEIKING_DVD_AMP         //2-8-16 11:21
//#define WINGSUM_DVD
//#define WYD_DVD                   //3-10-27 1:44张宇P
//#define XINDE_DVD                     //wangfeng 2003-12-25 10:23
//#define XINGQIU_DVD
//#define XINGWEIKE_DVD             //2003-12-22 wangap
//#define XUKE_DVD
//#define YAHSIN_DVD
//#define YUXING_DVD              //for YUXING DVD-801D mode
//#define YUXING_MIDI_DVD              //for YUXING midi DVD //xlluo 04-6-11
//#define SANJING_MIDI_DVD            //for SANJING midi DVD //xlluo 04-6-11
//#define YADAI_DVD               //guolin 2003/10/13
//#define YANGYU_DVD             //2003-12-23 wangap
//#define YONGDEFU_DVD			//yaowh 2005-03-03
//#define ZIHUAN_DVD
//#define ZhengTai_DVD               //3-12-23 9:24 LJD
//#define ZHAOCHI_DVD             //LYC 2005-04-04
//#define SHIDELI_DVD                 //gerry,2004-4-21 13:00
//#define JENGYANG_DVD                //liulifeng 2004-8-5 8:56
//#define ETON_DVD                    //liweihua 2004-9-9 9:50
//#define PHILIPS_DVD                 //chenzhao 2005-6-16 14:03

//for receiver use
//#define HK_ORITRON_DVD_RECEIVER      //for oritron receiver hongfeng 2005-07-09

//nono move to cust_pre_def.h
#include "cust_pre_def.h"

//we use GENERAL_DVD as our general platform.
#ifdef GENERAL_DVD//for general customers dvd mode
//nono 5-5-9 16:39 Note:can't use "#if defined(XXXX)", because font_parse.exe will not find your "XXXX".

       //#define GENERAL_32_DVD         //VER:G32-XXX//for 8200/8202A 32M general customers dvd mode 
       //#define GENERAL_8202S_DVD       //VER:GS32-XXX//nono add 2004-10-16 16:49 for 8202S 32m general customers dvd mode
       //#define GENERAL_8202D_DVD       //VER:GD32-XXX//nono add 2004-10-16 16:49 for 8202D 32m general customers dvd mode
       //#define GENERAL_16_DVD          //VER:G16-XXX//for 8200/8202A 16M general customers dvd mode
       //#define GENERAL_8202S_16_DVD          //for 8202S 16m//VER:GS16-XXX
       //#define GENERAL_8202D_16_DVD          //for 8202D 16m//VER:GD16-XXX
       //#define GENERAL_8202D_16_040_NO_MP4   //for 8202D 16m//VER:GD164XXX//SUPPORT WMA, NO MP4
       //#define GENERAL_8202D_16_040_DVD   //for 8202D 16m//VER:GD164XXX//SUPPORT WMA, MP4, no MP4 sub-title
       //#define GENERAL_8202A256_DVB       //for 8202A256 dvb 64m//ver:DVB-000+GENERAL-DT001
       //#define GENERAL_8202D_DVB         //for 8202D dvb 64m//ver:DVB-000+GENERAL-DT001
       //#define GENERAL_8202E_DVD        //ver:for 8202E general customers dvd mode
       //#define GENERAL_8202M_A_DVD  //Ver:MA-000   ouyang add 2005.07.04//M_A
       //#define GENERAL_8202M_B_DVD       //Ver: MB-000  axel add 2005/8/3 for 8202M general customers dvd mode
       //#define GENERAL_PORTABLE_DVD_8202D     //for standard 8202D portabel dvd(4M*16 SDRAM+080 Flash)
       //#define GENERAL_PORTABLE_DVD_8202D_DVB //for standard 8202A-256/8202D portable DVD+ DVB-T(4M*16 SDRAM+080 Flash)
       #define GENERAL_8202L_16_DVD          //for 8202L 16m//VER:L168-XXX
       //#define GENERAL_8202L_64_DVD         //for 8202L 64m//VER:L648-XXX
       //#define GENERAL_8202L_16_040_DVD     //for 8202L 16m//VER:L164-XXX
       //#define GENERAL_8202L_16_040_NO_MP4  //for 8202L 16m//VER:L164-XXX
       //#define GENERAL_8202L_32_DVD         //for 8202L 32m//VER:L32-XXX

    #if defined(GENERAL_32_DVD)
        #include ".\\Customers\\General\\cfg_general_32.h" 
    #elif defined(GENERAL_8202S_DVD)
        #include ".\\Customers\\General\\cfg_general_8202s.h" 
    #elif defined(GENERAL_8202D_DVD)
        #include ".\\Customers\\General\\cfg_general_8202d.h" 
    #elif defined(GENERAL_16_DVD)
        #include ".\\Customers\\General\\cfg_general_16.h" 
    #elif defined(GENERAL_8202S_16_DVD)
        #include ".\\Customers\\General\\cfg_general_8202s_16.h" 
    #elif defined(GENERAL_8202D_16_DVD)
        #include ".\\Customers\\General\\cfg_general_8202d_16.h" 
    #elif defined(GENERAL_8202D_16_040_NO_MP4)
        #include ".\\Customers\\General\\cfg_general_8202d_16_040_no_mp4.h"      
    #elif defined(GENERAL_8202D_16_040_DVD)
        #include ".\\Customers\\General\\cfg_general_8202d_16_040.h"              
    #elif defined(GENERAL_8202A256_DVB)
        #include ".\\Customers\\General\\cfg_general_8202A256_dvb.h"   
    #elif defined(GENERAL_8202D_DVB)
        #include ".\\Customers\\General\\cfg_general_8202d_dvb.h"  
    #elif defined(GENERAL_8202E_DVD)
        #include ".\\Customers\\General\\cfg_general_8202e.h"  
    #elif defined(GENERAL_8202M_A_DVD)
        #include ".\\Customers\\General\\cfg_general_8202m_a.h"  
    #elif defined(GENERAL_8202M_B_DVD)
        #include ".\\Customers\\General\\cfg_general_8202m_b.h"  
    #elif defined(GENERAL_PORTABLE_DVD_8202D)
        #include ".\\Customers\\General\\cfg_general_portable_8202d.h"     
    #elif defined(GENERAL_PORTABLE_DVD_8202D_DVB)
        #include ".\\Customers\\General\\cfg_general_portable_8202d_dvb.h"    
    #elif defined(GENERAL_8202L_16_DVD)
        #include ".\\Customers\\General\\cfg_general_8202l_16.h"     
    #elif defined(GENERAL_8202L_64_DVD)
        #include ".\\Customers\\General\\cfg_general_8202l_64.h" 
    #elif defined(GENERAL_8202L_16_040_DVD)
        #include ".\\Customers\\General\\cfg_general_8202l_16_040.h"
    #elif defined(GENERAL_8202L_16_040_NO_MP4)
        #include ".\\Customers\\General\\cfg_general_8202l_16_040_no_mp4.h"    
    #elif defined(GENERAL_8202L_32_DVD)
        #include ".\\Customers\\General\\cfg_general_8202l_32.h"
    #endif


//we use SUNPLUS_DVD as our standard developing platform
#elif defined(SUNPLUS_DVD)
        //#define STB_DVD
        
        #define CUSTOMERS_DVD             //for general customers dvd mode
        //#define CUSTOMERS_8202S_DVD       //nono add 2004-10-16 16:49 for 8202S general customers dvd mode
        //#define CUSTOMERS_8202A_256_DVD       //axel add 2005/7/22 for 8202S 256pin dvd mode        
        //#define CUSTOMERS_8202D_DVD       //terry add 2005/2/16 05:25PM for 8202D general customers dvd mode
        //#define CUSTOMERS_8202D_256_DVD	//zhongshan add 2005-8-22 15:30
        //#define CUSTOMERS_8202D_16_DVD    //terry add 2005/3/12 09:28と for 8202D general customers dvd mode
        //#define CUSTOMERS_8202D_16_040_DVD  //terry add 2005/3/12 09:28と for 8202D general customers dvd mode
        //#define CUSTOMERS_8202D_16_040_NO_MP4  //terry,2005/6/22 10:22と
        //#define CUSTOMERS_8202L_16_DVD
        //#define CUSTOMERS_8202L_16_040_DVD
        //#define CUSTOMERS_1002_16_DVD
        //#define CUSTOMERS_8202L_16_040_NO_MP4
        //#define CUSTOMERS_8202L_32_DVD
        //#define CUSTOMERS_8202L_64_DVD
        //#define CUSTOMERS_8202M_DVD       //axel add 2005/8/3 for 8202M_B general customers dvd mode
        //#define CUSTOMERS_8202E_DVD       //terry add 2005/2/22 08:57PM for 8202E general customers dvd mode
        //#define CUSTOMERS_16_DVD          //c16-000
        //#define CUSTOMERS_8202S_16_DVD          //02S-160   
        //#define CUSTOMERS_8104_CD     
        //#define CUSTOMERS_8104_16_CD
        
        //#define EMU_BOARD               //for DSP3 team emu board
        //#define DTS_CERT
        //#define MIDI_TEST
        //#define MIDI_4_FSLOADER
        //#define MIDI_4_FSLOADER_CARD
        //#define MIDI_4_FSLOADER_HD
        //#define HDD_ACCESS
        //#define CUSTOMERS_PORTABLE_DVD
        //#define CUSTOMERS_PORTABLE_DVD_8202D
        //#define CUSTOMERS_PORTABLE_DVD_8202D_DVB
	//#define CUSTOMERS_PORTABLE_DVD_8202L_64
        //#define SY_M5_256
        //#define SY_M5_256_UART
        //#define MIDI_8202M_SY_DVD  //ouyang add 2005.07.04//M_A
    	//#define CF_HDD_PMP                //hdd(must #define PMP_DVD in ver.h)
    	//#define HDD_PLAYER_V01              //hdd(must #define PMP_DVD in ver.h)
        //#define SUNPLUS_TAS_DVD         //Sunplus DVD+Amp(TAS3001 or TAS5026)
        //#define SUNPLUS_RECEIVER_DVD
	    //#define SUNPLUS_RECEIVER_MCU
        //#define SUNPLUS_RELEASE 
        //#define BOOT_LOAD_CODE 
        //#define SUNPLUS_8202A256_DVB        //wthsin, 2005/2/1 11:53am 
        //#define SUNPLUS_8202D_DVB         //YANGLI ,2006-6-22 10:42,FOR 216PIN
        
        #ifdef BOOT_LOAD_CODE
        //#define BOOT_LOAD_CODEA 
       //#define BOOT_LOAD_CODEB
        #endif       


    #if defined(CUSTOMERS_DVD)  
        #include ".\\Customers\\Sunplus\\cfg_customers.h" 
    #elif defined(CUSTOMERS_8202S_DVD)
        #include ".\\Customers\\Sunplus\\cfg_customers_8202s.h" 
    #elif defined(CUSTOMERS_8202A_256_DVD)
        #include ".\\Customers\\Sunplus\\cfg_customers_8202a_256.h" 
    #elif defined(CUSTOMERS_8202D_DVD)
        #include ".\\Customers\\Sunplus\\cfg_customers_8202d.h" 
 #elif defined(CUSTOMERS_8202D_256_DVD)
        #include ".\\Customers\\Sunplus\\cfg_customers_8202d_256.h" 
    #elif defined(CUSTOMERS_8202D_16_DVD)
        #include ".\\Customers\\Sunplus\\cfg_customers_8202d_16.h"         
    #elif defined(CUSTOMERS_8202D_16_040_DVD)
        #include ".\\Customers\\Sunplus\\cfg_customers_8202d_16_040.h"                     
    #elif defined(CUSTOMERS_8202D_16_040_NO_MP4)
        #include ".\\Customers\\Sunplus\\cfg_customers_8202d_16_040_no_mp4.h"                     
    #elif defined(CUSTOMERS_8202L_16_DVD)
        #include ".\\Customers\\Sunplus\\cfg_customers_8202l_16.h"                     
    #elif defined(CUSTOMERS_8202L_16_040_DVD)
        #include ".\\Customers\\Sunplus\\cfg_customers_8202l_16_040.h"
    #elif defined(CUSTOMERS_8202L_16_040_NO_MP4)
        #include ".\\Customers\\Sunplus\\cfg_customers_8202l_16_040_no_mp4.h"    
    #elif defined(CUSTOMERS_8202L_32_DVD)
        #include ".\\Customers\\Sunplus\\cfg_customers_8202l_32.h"
    #elif defined(CUSTOMERS_8202L_64_DVD)
        #include ".\\Customers\\Sunplus\\cfg_customers_8202l_64.h"                     
    #elif defined(CUSTOMERS_8202E_DVD)
        #include ".\\Customers\\Sunplus\\cfg_customers_8202e.h"     
    #elif defined(CUSTOMERS_16_DVD) 
        #include ".\\Customers\\Sunplus\\cfg_customers_16.h" 
    #elif defined(CUSTOMERS_8202S_16_DVD) 
        #include ".\\Customers\\Sunplus\\cfg_customers_8202s_16.h" 
    #elif defined(CUSTOMERS_8104_CD) 
        #include ".\\Customers\\Sunplus\\cfg_customers_8104.h"    
    #elif defined(CUSTOMERS_8104_16_CD) 
        #include ".\\Customers\\Sunplus\\cfg_customers_8104_16.h"            
    #elif defined(EMU_BOARD)
        #include ".\\Customers\\Sunplus\\cfg_emu_board.h" 
    #elif defined(DTS_CERT)
        #include ".\\Customers\\Sunplus\\cfg_sunplus_dts.h" 
    #elif defined(MIDI_TEST)
        #include ".\\Customers\\Sunplus\\cfg_sunplus_midi.h" 
    #elif defined(MIDI_4_FSLOADER)
        #include ".\\Customers\\Sunplus\\cfg_sunplus_midi4fsloader.h" 
    #elif defined(MIDI_4_FSLOADER_CARD)
        #include ".\\Customers\\Sunplus\\cfg_sunplus_midi4fsloader_card.h" 
    #elif defined(MIDI_4_FSLOADER_HD)
        #include ".\\Customers\\Sunplus\\cfg_sunplus_midi4fsloader_hd.h" 
    #elif defined(CUSTOMERS_8202M_DVD)
        #include ".\\Customers\\Sunplus\\cfg_customers_8202m.h" 
    #elif defined(MIDI_8202M_SY_DVD)   //ouyang add 2005.07.04
        #include ".\\Customers\\Sunplus\\cfg_sunplus_midi4sy_8202m.h"            
    #elif defined(HDD_ACCESS)
        #include ".\\Customers\\Sunplus\\cfg_sunplus_hddaccess.h" 
    #elif defined(STB_DVD)
        #include ".\\Customers\\Sunplus\\cfg_sunplus_stb.h" 
    #elif defined(CUSTOMERS_PORTABLE_DVD)
        #include ".\\Customers\\Sunplus\\cfg_customers_portable.h" 
    #elif defined(CUSTOMERS_PORTABLE_DVD_8202D)
        #include ".\\Customers\\Sunplus\\cfg_customers_portable_8202d.h"     
    #elif defined(CUSTOMERS_PORTABLE_DVD_8202D_DVB)
        #include ".\\Customers\\Sunplus\\cfg_customers_portable_8202d_dvb.h"         
    #elif defined(CUSTOMERS_PORTABLE_DVD_8202L_64)
        #include ".\\Customers\\Sunplus\\cfg_customers_portable_8202L_64.h"
    #elif defined(SY_M5_256)
        #include ".\\Customers\\Sunplus\\cfg_sy_m5_256.h" 
    #elif defined(SY_M5_256_UART)
        #include ".\\Customers\\Sunplus\\cfg_sy_m5_256_uart.h" 
    #elif defined(CF_HDD_PMP)    
        #include ".\\Customers\\Sunplus\\cfg_sunplus_cf_hdd_pmp.h" 
    #elif defined(HDD_PLAYER_V01)
        #include ".\\Customers\\Sunplus\\cfg_sunplus_hdd_player_v01.h" 
	#elif defined(SUNPLUS_TAS_DVD)
        #include ".\\Customers\\Sunplus\\cfg_sunplus_tas.h" 
    #elif defined(SUNPLUS_RECEIVER_DVD)
        #include ".\\Customers\\Sunplus\\cfg_sunplus_receiver.h" 
    #elif defined(SUNPLUS_RECEIVER_MCU)
    	#include ".\\Customers\\Sunplus\\cfg_sunplus_recv_mcu.h"
    #elif defined(SUNPLUS_RELEASE)
    	#include ".\\Customers\\Sunplus\\cfg_sunplus_release.h"
    #elif defined(BOOT_LOAD_CODEA)
    	#include ".\\Customers\\Sunplus\\cfg_sunplus_BOOTLOAD.h"
    #elif defined(BOOT_LOAD_CODEB)
    	#include ".\\Customers\\Sunplus\\cfg_sunplus_BTROMB.h"	
    #elif defined(SUNPLUS_8202A256_DVB)
        #include ".\\Customers\\Sunplus\\cfg_sunplus_8202a256_dvb.h"
    #elif defined(SUNPLUS_8202D_DVB)
        #include ".\\Customers\\Sunplus\\cfg_sunplus_8202d_dvb.h"    	
	#elif defined(CUSTOMERS_1002_16_DVD)
		#include ".\\Customers\\Sunplus\\cfg_customers_1002_16.h"		
    #else
        #include ".\\Customers\\Sunplus\\cfg_sunplus.h" 
	#endif

    #elif defined(SANJING_MIDI_DVD)        //ouyang 04-10-29   
     #include ".\\Customers\\Sanjing\\cfg_SanJing_mididvd.h"	 //ouyang 04-10-29   

#elif defined(YUXING_MIDI_DVD)        //xlluo 04-6-11                                      
     #include ".\\Customers\\Yuxing\\cfg_YuXing_mididvd.h"       //xlluo 04-6-11
#elif defined(YUXING_DVD)
    //model name, choose one
    //---------------------
    //#define YUXING_8202D_16_DVD
    #define YUXING_8202D_2_16_DVD
    //#define YX828B
    //#define YX829A
    //---------------------
    #ifdef YX828B
        #include ".\\Customers\\Yuxing\\cfg_828.h"
    #elif defined(YX829A)
        #include ".\\Customers\\Yuxing\\cfg_829a.h"    
	#elif defined(YUXING_8202D_16_DVD)
    	#include ".\\Customers\\Yuxing\\cfg_yuxing_8202d_16.h"
	#elif defined(YUXING_8202D_2_16_DVD)
    	#include ".\\Customers\\Yuxing\\cfg_yuxing_8202d_2_16.h"
    #else
    	#include ".\\Customers\\Yuxing\\cfg_yuxing_8202s.h"
    #endif


#elif defined(SAMBOO_HDDPLAYER_DVD) 
    #include ".\\\\Customers\\Samboo\\cfg_samboo_hddplayer.h"
    
#elif defined(SAMSUNG1_DVD)     //shawn at 910130
    #include ".\\Customers\\Samsung\\cfg_samsung.h" 

#elif defined(NINTAUS_DVD)     //4-1-10 16:58
    //model name, choose one
    //---------------------
    #define NINTAUS_612
    
    #ifdef NINTAUS_612
        #include ".\\Customers\\nintaus\\cfg_nintaus_612.h"     
    #else
    #include ".\\Customers\\nintaus\\cfg_nintaus.h" 
    #endif

#elif defined(NINTAUS_MIDI_DVD)     //2004-4-8 09:40张宇M
    #include ".\\Customers\\nintaus\\cfg_nintaus_midi.h" 

#elif defined(AKI_DVD)     // fengjl  03/10/18 for chuangying
	//#define AKI_8202S_16
	//#define AKI_8202D_16_2_1_CH
	//#define AKI_8202D_16_5_1_CH
	
	#ifdef AKI_8202D_16_2_1_CH
		#include ".\\Customers\\Aki\\cfg_AKI_8202d_16_040.h"
	#elif defined(AKI_8202D_16_5_1_CH)	
		#include ".\\Customers\\Aki\\cfg_AKI_8202d_16.h"
	#elif defined(AKI_8202S_16)
		#include ".\\Customers\\Aki\\cfg_aki_8202S_16.h" 
	#else
    #include ".\\Customers\\Aki\\cfg_aki.h" 
    #endif
    
#elif defined(APEX_DVD)             //Maoyong 2004.03.23 
    #include ".\\Customers\\Apex\\cfg_apex.h"

#elif defined(ATLAS_DVD)             //axel 2004/9/13  
    #include ".\\Customers\\atlas\\cfg_atlas_midi4fsloader.h"

#elif defined(BBK_DVD)     // fengjl  03/10/16 for bbk
/* ===please choose one #define === */
    //#define BBK_DSS_555_DVD
    //#define BBK_DV961_DVD
    #define BBK_DV911S  //BBK_DV912S
//====================================
    
    #ifdef BBK_DSS_555_DVD
    #include ".\\Customers\\Bbk\\cfg_dss_555.h"
    #elif defined(BBK_DV961_DVD)
    #include ".\\Customers\\Bbk\\cfg_bbk.h" 
    #elif defined(BBK_DV911S)
    #include ".\\Customers\\Bbk\\cfg_dv911s.h" 
    #endif
    
#elif defined(SMT_DVD)     // fengjl  3-10-23 17:50 for smt
    
    //#define SMT_898SP
    //#define SMT_SMT
    #define SMT_ZHONGXING
    
    #ifdef SMT_898SP
        #include ".\\Customers\\Smt\\cfg_smt_898sp.h" 
    #elif defined(SMT_SMT)
        #include ".\\Customers\\Smt\\cfg_smt_smt.h" 
    #elif defined(SMT_ZHONGXING)
        #include ".\\Customers\\Smt\\cfg_smt_zhongxing.h" 
    #else 
    #include ".\\Customers\\Smt\\cfg_smt.h" 
    #endif

#elif defined(MUSTEK_DVD)
    #include ".\\Customers\\Mustek\\cfg_mustek.h" 
#elif defined(MUSTEK_PORTABLE_DVD)
    #define PDVD_DVB_K100D_SERIES
    
    #ifdef PDVD_DVB_K100D_SERIES
    #include ".\\Customers\\Mustek_portable\\cfg_mustek_portable_dvb.h"
    #else
    #include ".\\Customers\\Mustek_portable\\cfg_mustek_portable.h"    
    #endif
    
#elif defined(XINGWEIKE_DVD)
    #include ".\\Customers\\XINGWEIKE\\cfg_xingweike.h"
#elif defined(XINGQIU_DVD)
    //#define XINGQIU_DVD_RECEIVER//xyy 2004-2-3 9:30  for xingqiu dvd receiver
    #ifdef XINGQIU_DVD_RECEIVER//xyy 2004-2-3 9:39
        #include ".\\Customers\\Xingqiu\\cfg_xingqiu_rcvr.h"
    #else
    	#include ".\\Customers\\Xingqiu\\cfg_xingqiu.h"
    #endif

#elif defined(YANGYU_DVD)
    //#define YANGYU_8202s_DVD
	//#define YANGYU_8202s_16_DVD
	//#define YANGYU_8202D_DVD
	//#define YANGYU_8202D_16_DVD
	//#define YANGYU_8202D_2_16_DVD
	//#define YANGYU_8202D_16_040_DVD
	#define YANGYU_8202L_16_DVD
    //#define YANGYU_8202L_64_DVD
	
	#ifdef YANGYU_8202s_DVD
		#include ".\\Customers\\YangYu\\cfg_yangyu_8202s.h"
	#elif defined(YANGYU_8202s_16_DVD)
		#include ".\\Customers\\YangYu\\cfg_yangyu_8202s_16.h"
	#elif defined(YANGYU_8202D_2_16_DVD)
		#include ".\\Customers\\YangYu\\cfg_yangyu_8202d_2_16.h"
	#elif defined(YANGYU_8202D_DVD)
		#include ".\\Customers\\YangYu\\cfg_yangyu_8202d.h"
	#elif defined(YANGYU_8202D_16_DVD)
		#include ".\\Customers\\YangYu\\cfg_yangyu_8202d_16.h"
	#elif defined(YANGYU_8202D_16_040_DVD)
		#include ".\\Customers\\YangYu\\cfg_yangyu_8202d_16_040.h"
	#elif defined(YANGYU_8202L_16_DVD)
        #include ".\\Customers\\YangYu\\cfg_yangyu_8202l_16.h"                     
    #elif defined(YANGYU_8202L_64_DVD)
        #include ".\\Customers\\YangYu\\cfg_yangyu_8202l_64.h" 	
	#else
    	#include ".\\Customers\\YangYu\\cfg_yangyu.h"
    #endif
        
#elif defined(YONGDEFU_DVD)
	#include ".\\Customers\\Yongdefu\\cfg_yongdefu.h"
    
#elif defined(ALON_DVD)
    #include ".\\Customers\\Alon\\cfg_alon.h"
#elif defined(TONGFANG_DVD)
    #include ".\\Customers\\TongFang\\cfg_tongfang.h"              
#elif defined(ZhengTai_DVD)
    #include ".\\Customers\\ZhengTai\\cfg_zhengtai.h"   
#elif defined(TONIC_DVD)
    #include ".\\Customers\\tonic\\cfg_tonic.h"
#elif defined(FUSS_DVD)         //nono 2-3-24 15:47
    //model name, choose one
    //---------------------
    //#define FUSS_LIDE_DVD
    //#define FUSS_SHENGKE_DVD
    //#define FUSS_SANYING_DVD
    //#define FUSS_MASCO_DVD
    //#define FUSS_FEIYANG_DVD
//#define FUSS_DV9961_DVD
//#define FUSS_JUHAN_DVD
//#define FUSS_XINQIAO_DVD
#define FUSS_DV8881_DV8893_DVD
//#define FUSS_SHUNJIAN_DVD
    //---------------------
    #ifdef FUSS_LIDE_DVD
        #include ".\\Customers\\Fuss\\lide\\cfg_fuss_lide.h" 
    #elif defined(FUSS_SHENGKE_DVD)
        #include ".\\Customers\\Fuss\\shengke\\cfg_fuss_shengke.h" 
    #elif defined(FUSS_SANYING_DVD)
        #include ".\\Customers\\Fuss\\sanying\\cfg_fuss_sanying.h" 
    #elif defined(FUSS_MASCO_DVD)
        #include ".\\Customers\\Fuss\\Masco\\cfg_fuss_masco.h" 
    #elif defined(FUSS_FEIYANG_DVD)
        #include ".\\Customers\\Fuss\\Feiyang\\cfg_fuss_feiyang.h" 
#elif defined(FUSS_DV9961_DVD)
#include ".\\Customers\\Fuss\\dv9961\\cfg_fuss_dv9961.h"
#elif defined(FUSS_JUHAN_DVD)//base on dv8893
#include ".\\Customers\\Fuss\\juhan\\cfg_fuss_juhan.h" 
#elif defined(FUSS_XINQIAO_DVD)
#include ".\\Customers\\Fuss\\xinqiao\\cfg_fuss_xinqiao.h" 
#elif defined(FUSS_SHUNJIAN_DVD)
#include ".\\Customers\\Fuss\\shunjian\\cfg_fuss_shunjian.h" 
#elif defined(FUSS_DV8881_DV8893_DVD)//dv8893 & dv8881
        //for Fuss define
#include ".\\Customers\\Fuss\\dv8881_dv8893\\cfg_fuss_dv8881_dv8893.h" 
    #endif

#elif defined(HUAJIA_DVD)       //XIAOSAN 02-04-18


    //model name
    //================
    

/*************************************************************/  
     //#define HIMAGE_8202          //for 8202//4-3-15 13:59
     //#define HIMAGE_8202_5401
     //#define HIMAGE_8202_8408
     //#define HIMAGE_8202_2307
     #define HIMAGE_8202_5407      //5408//5410      
/*************************************************************/  
    
//#define HIMAGE2311_2303          //HJ_2311_5151//HJ_2303_1251    
//#define HIMAGE2108//02-084W
//#define HIMAGE2206    //02-063w   //02-077w
    //#define HIMAGE2818        //AKAI 3850S
    //#define HIMAGE602         //WHITE WESTINGHOUSE S700
    //#define HIMAGE602B        //HIMAGE602 daewoo LOGO. only change logo , jason 2-10-3 15:31
    //#define HIMAGE909
//#define HIMAGE921         //daewoo S200 = S250
    //#define HIMAGE929
    //#define HIMAGE927B        //akishi 6000 has been ready.
    //#define HIMAGE1200
    //#define HIMAGE2048
//#define HIMAGE2048new     //jason add 2-10-3 13:39; vfd 2048,ir 13,ktc loader,daewoo logo,2ch,
    //#define HIMAGE9000
    //#define HIMAGE5900M
//#define HIMAGE2205        //02-078w//02-086//02-090w
    //#define HIMAGE2290
//#define HIMAGE2206_NEW  //02-066w
//#define HIMAGEQ48B
//#define HIMAGE2202    //02-081w
//#define HIMAGE2203    //02-083w
//#define HIMAGE2203_242w   //03-242w//57x
//#define HIMAGE2323        //SOC HJ2323//01x//03-157W//03-129w
//#define HIMAGE2202_03_107W//03-107W//02x
//#define HIMAGE2202_03_109W//03-109W//03x
//#define HIMAGE2202_03_112W//03-112W//04x==03-136W//03-205w
//#define HIMAGE2325        //SOC HJ2325 03-113w//05x//03-134w//04-016w
//#define HIMAGE2302        //SOC HJ2302 03-115w//06x
//#define HIMAGE2308        //SOC HJ2308 //07x//388//hj-03-16//HJ-03-21
//#define HIMAGE986     //SOC HJ986 //08x
//#define HIMAGE812     //SOC HJ812 //09x
//#define HIMAGE2305		//03-117w //10x//03-247W//04-054w//04-121w
//#define HIMAGE2317        //03-118w //11x
//#define HIMAGE2206_122W       //03-122w //12x//03-196w//03-236w//03-230w//04-006w
//#define HIMAGE2320        //03-128w //13x
//#define HIMAGE2328            //14x
//#define HIMAGE2202_03_112W_MODEL//03-112W_MODE//15x
//#define HIMAGE2202_03_112W_122W//03-112W_MODE//03-122W//16x//03-156w//03-203w//03-216w
//#define HIMAGE2305_128W       //03-128w //17x//03-162w//03-206w//03-214w//03-232w//04-068w
//#define HIMAGE2326_03_158W        //03-158W//18x//04-026w
//#define HIMAGE2290_03_159W        //03-159W//19x
//#define HIMAGE2290_03_153W        //03-153W//20x//03-250w//03-236w//03-244w//04-074w//04-044w//04-066w //04-006W
//#define HIMAGE2323_03_151W        //03-151W//21x//03-142W//04-051W
//#define HIMAGE2206_152W       //03-152w //22x  //04-014W
//#define HIMAGE1251            //03-135w(04-012W)//23x //04_082W //04-131w
//#define HIMAGE600             //24x
//#define HIMAGE_2439
//#define HIMAGE2201_03_130W        //03-130W//03-131w//03-143w//25x//03-198w//03-243w//04-029w
//#define HIMAGE2316        //SOC HJ2316 //26x//hj-03-15
//#define HIMAGE2301        //SOC HJ2301 //27x
//#define HIMAGE620     //SOC HJ620 //28x//sva
//#define HIMAGE_1125       //SOC HJ1125 //29x FOR APEX//03-229w
//#define HIMAGE_2209_03_150W       //SOC HJ2209 //30x 
//#define HIMAGE_2302_03_150W       //SOC HJ2302 //31x 
//#define HIMAGE_2316_03_140W       //SOC HJ2316 //32x 
//#define HIMAGE_2308_03_144W       //SOC HJ2308 //33x //04-041w//04-067w//04-101w
//#define HIMAGE_5151_03_176W       //SOC HJ5151 //34x //03-hj-18//03-210w//03-219w
//#define HIMAGE2202_03_164W            //soc_hj2202//35x //04-003w
//#define HIMAGE2326_03_169W            //soc_hj2326//36x//==03-188w//03-246w//04-10w//04-047w
//#define HIMAGE_2312_03_165W           //soc_hj2312//37x  //03-165w//04-005w
//#define HIMAGE_2316_03_166W               //soc_hj2316//38x //04-004w
//#define HIMAGE_S161_03_146W               //soc_hj2316//39x//==03-167w
//#define HIMAGE_2308_03_174W       //SOC HJ2308 //40x //for 03-249w
//#define HIMAGE_2325_03_180W       //SOC HJ2325 //41x 
//#define HIMAGE2323_03_199W        //03-199W//42x//==03-200w//03-201w//04-035w
//#define HIMAGE2323_03_202W        //03-199W//43x//03-215w//03-217w//03-218w/03-213w//03-245W //03-251W//03-221W//04-001W//04-036W
//#define HIMAGE_2320_03_170W           //soc_hj2320//44x //03-222w
//#define HIMAGE_1250_03_185W         //03-185W(03-173W)//45x//03-240w  
//#define HIMAGE_2309_03_209W           //soc_hj2309//46x//03-223w
//#define HIMAGE_2311     		//SOC HJ2311 //47x//03-228w//03-240w//04-009w//04-048w//04-109w//04-100w
//#define HIMAGE_DP313          //soc_hjDP313//48x//03-237w//03-238w//03-239w
//#define HIMAGE2290_03_207W        //03-207W//49x//03-211w
//#define HIMAGE2315_HJ_03_22W      //HJ_03_22W//50x//03-226w//03-224w//03-226w//03-212w//04-063w//04-064w
//#define HIMAGE_DP316          //soc_hjDP316//52x//03-233w//03-234w
//#define HIMAGE_3000               //HJ-3000//51x
//#define HIMAGE_3000_2307         //HJ_2307  card_reader//58x
//#define HIMAGE_1250_03_225W           //SOC HJ1250//53x//03-225w
//#define HIMAGE2305_04002W     //04-002w //54x
//#define HIMAGE_DV_010B            //DV-010B  //55x
//#define HIMAGE_DP313_16           //soc_hjDP313//56x/
//#define HIMAGE_2303_04_017W       //59x //HJ_2303   //04-017W/04-019W/04-020W/04-030W/04-032W //04-028W 
//#define HIMAGE_2311_04_021W       //SOC HJ2311 //60x//04-021w(04-034w)//04-040w
//#define HIMAGE_2309_04_029W           //soc_hj2309//61x//04-029w
//#define HIMAGE_2302_04_051W       //SOC HJ2302 //62x //04-051w
//#define HIMAGE2315_04_022W        //SOC HJ2315 //63x//HJ_04_022W 
//#define HIMAGE_2401                   //64x// 1M*16 //2402 //2403
//#define HIMAGE_2308_04_101W
//else cfg_huajia.h//03-94w=03-111w//03-98w//00x//03-125W//03-128W(2305)//03-132_133w//03-163w//03-162w//03-171w//03-181w//03-155=04-007w

    //==================
    #ifdef HIMAGE2108
        #include ".\\Customers\\Huajia\\cfg_huajia_2108.h" 
    #elif defined(HIMAGE2206)
        #include ".\\Customers\\Huajia\\cfg_huajia_2206.h" 


/*************************************************************/    
    #elif defined(HIMAGE_8202)
        #include ".\\Customers\\Huajia\\cfg_huajia_8202.h" 
    #elif defined(HIMAGE_8202_5401)
        #include ".\\Customers\\Huajia\\cfg_huajia_8202_5401.h"
    #elif defined(HIMAGE_8202_8408)
        #include ".\\Customers\\Huajia\\cfg_huajia_8202_8408.h" 
    #elif defined(HIMAGE_8202_2307)
        #include ".\\Customers\\Huajia\\cfg_huajia_8202_2307.h"        
    #elif defined(HIMAGE_8202_5407)
        #include ".\\Customers\\Huajia\\cfg_huajia_8202_5407.h"        
/*************************************************************/    
        
    #elif defined(HIMAGE2311_2303)
        #include ".\\Customers\\Huajia\\cfg_huajia_2311_2303.h" //5151//1251
    #elif defined(HIMAGE2326_04_117w)
        #include ".\\Customers\\Huajia\\cfg_huajia_2326_04_117w.h" 
    #elif defined(HIMAGE2818)
        #include ".\\Customers\\Huajia\\cfg_huajia_2818.h" 
    #elif defined(HIMAGE602)
        #include ".\\Customers\\Huajia\\cfg_huajia_602.h" 
    #elif defined(HIMAGE602B)
        #include ".\\Customers\\Huajia\\cfg_huajia_602b.h" 
    #elif defined(HIMAGE909)
        #include ".\\Customers\\Huajia\\cfg_huajia_909.h" 
    #elif defined(HIMAGE921)
        #include ".\\Customers\\Huajia\\cfg_huajia_921.h" 
    #elif defined(HIMAGE929)
        #include ".\\Customers\\Huajia\\cfg_huajia_929.h" 
    #elif defined(HIMAGE927B)
        #include ".\\Customers\\Huajia\\cfg_huajia_927b.h" 
    #elif defined(HIMAGE1200)
        #include ".\\Customers\\Huajia\\cfg_huajia_1200.h" 
    #elif defined(HIMAGE2048)
        #include ".\\Customers\\Huajia\\cfg_huajia_2048.h" 
    #elif defined(HIMAGE2048new)//HIMAGE5900
        #include ".\\Customers\\Huajia\\cfg_huajia_2048new.h" 
    #elif defined(HIMAGE9000)
        #include ".\\Customers\\Huajia\\cfg_huajia_9000.h" 
    #elif defined(HIMAGE5900M)//"M" means MTK. 
        #include ".\\Customers\\Huajia\\cfg_huajia_5900m.h" 
    #elif defined(HIMAGE2205)
        #include ".\\Customers\\Huajia\\cfg_huajia_2205.h" 
    #elif defined(HIMAGE2290)
        #include ".\\Customers\\Huajia\\cfg_huajia_2290.h" 
#elif defined(HIMAGE2206_NEW)
#include ".\\Customers\\Huajia\\cfg_huajia_2206_new.h" 
#elif defined(HIMAGEQ48B)
#include ".\\Customers\\Huajia\\cfg_huajia_q48b.h" 
#elif defined(HIMAGE2202)
#include ".\\Customers\\Huajia\\cfg_huajia_2202.h" 
#elif defined(HIMAGE2203)
#include ".\\Customers\\Huajia\\cfg_huajia_2203.h" 
#elif defined(HIMAGE2323)
#include ".\\Customers\\Huajia\\cfg_huajia_2323.h" 
#elif defined(HIMAGE2323_03_199W)
#include ".\\Customers\\Huajia\\cfg_huajia_2323_03-199w.h" 
#elif defined(HIMAGE2323_03_202W)
#include ".\\Customers\\Huajia\\cfg_huajia_2323_03-202w.h" 
#elif defined(HIMAGE2202_03_107W)
#include ".\\Customers\\Huajia\\cfg_huajia_2202_03-107w.h"
#elif defined(HIMAGE2202_03_164W)
#include ".\\Customers\\Huajia\\cfg_huajia_2202_03-164w.h"
#elif defined(HIMAGE2202_03_109W)
#include ".\\Customers\\Huajia\\cfg_huajia_2202_03-109w.h"
#elif defined(HIMAGE2202_03_112W)
#include ".\\Customers\\Huajia\\cfg_huajia_2202_03-112w.h"
#elif defined(HIMAGE2202_03_112W_MODEL)
#include ".\\Customers\\Huajia\\cfg_huajia_2202_03-112w_model.h"
#elif defined(HIMAGE2202_03_112W_122W)
#include ".\\Customers\\Huajia\\cfg_huajia_2202_03-112w_122w.h"
#elif defined(HIMAGE2325)
#include ".\\Customers\\Huajia\\cfg_huajia_2325_03-113w.h" 
#elif defined(HIMAGE2302)
#include ".\\Customers\\Huajia\\cfg_huajia_2302_03-115w.h" 
#elif defined(HIMAGE2308)
#include ".\\Customers\\Huajia\\cfg_huajia_2308.h" 
#elif defined(HIMAGE_2308_03_144W)
#include ".\\Customers\\Huajia\\cfg_huajia_2308_03_144w.h" 
#elif defined(HIMAGE2316)
#include ".\\Customers\\Huajia\\cfg_huajia_2316.h" 
#elif defined(HIMAGE_2316_03_140W)
#include ".\\Customers\\Huajia\\cfg_huajia_2316_03_140w.h" 
#elif defined(HIMAGE_2316_03_166W)
#include ".\\Customers\\Huajia\\cfg_huajia_2316_03-166w.h" 
#elif defined(HIMAGE986)
#include ".\\Customers\\Huajia\\cfg_huajia_986.h" 
#elif defined(HIMAGE812)
#include ".\\Customers\\Huajia\\cfg_huajia_812.h" 
#elif defined(HIMAGE2305)
#include ".\\Customers\\Huajia\\cfg_huajia_2305.h" 
#elif defined(HIMAGE2305_128W)
#include ".\\Customers\\Huajia\\cfg_huajia_2305_128w.h" 
#elif defined(HIMAGE2305_04002W)
#include ".\\Customers\\Huajia\\cfg_huajia_2305_04002w.h" 
#elif defined(HIMAGE2317)
#include ".\\Customers\\Huajia\\cfg_huajia_03-118w.h" 
#elif defined(HIMAGE2206_122W)
#include ".\\Customers\\Huajia\\cfg_huajia_03-122w.h" 
#elif defined(HIMAGE2206_152W)
#include ".\\Customers\\Huajia\\cfg_huajia_2206_03-152w.h" 
#elif defined(HIMAGE2320)
#include ".\\Customers\\Huajia\\cfg_huajia_03-128w.h" 
#elif defined(HIMAGE2328)
#include ".\\Customers\\Huajia\\cfg_huajia_2328.h" 
#elif defined(HIMAGE2326_03_158W)
#include ".\\Customers\\Huajia\\cfg_huajia_2326_03-158w.h" 
#elif defined(HIMAGE2326_03_169W)
#include ".\\Customers\\Huajia\\cfg_huajia_2326_03-169w.h" 
#elif defined(HIMAGE2290_03_159W)
#include ".\\Customers\\Huajia\\cfg_huajia_2290_03-159w.h" 
#elif defined(HIMAGE2290_03_153W)
#include ".\\Customers\\Huajia\\cfg_huajia_2290_03-153w.h" 
#elif defined(HIMAGE2290_03_207W)
#include ".\\Customers\\Huajia\\cfg_huajia_2290_03-207w.h" 
#elif defined(HIMAGE2323_03_151W)
#include ".\\Customers\\Huajia\\cfg_huajia_2323_03-151w.h" 
#elif defined(HIMAGE2201_03_130W)
#include ".\\Customers\\Huajia\\cfg_huajia_2201_03-130w.h" 
#elif defined(HIMAGE2301)
#include ".\\Customers\\Huajia\\cfg_huajia_2301.h" 
#elif defined(HIMAGE600)
        #include ".\\Customers\\Huajia\\cfg_huajia_600.h"
#elif defined(HIMAGE1251)
        #include ".\\Customers\\Huajia\\cfg_huajia_1251.h"
#elif defined(HIMAGE620)
#include ".\\Customers\\Huajia\\cfg_huajia_620.h" 
#elif defined(HIMAGE_1125)
#include ".\\Customers\\Huajia\\cfg_huajia_1125.h" 
#elif defined(HIMAGE_2209_03_150W)
#include ".\\Customers\\Huajia\\cfg_huajia_2209_03-150w.h" 
#elif defined(HIMAGE_2302_03_150W)
#include ".\\Customers\\Huajia\\cfg_huajia_2302_03-150w.h" 
#elif defined(HIMAGE_2302_04_051W)
#include ".\\Customers\\Huajia\\cfg_huajia_2302_04-051w.h" 
#elif defined(HIMAGE_2303_04_017W)
#include ".\\Customers\\Huajia\\cfg_huajia_2303_04-017w.h" 
#elif defined(HIMAGE_5151_03_176W)
#include ".\\Customers\\Huajia\\cfg_huajia_5151_03_176w.h" 
#elif defined(HIMAGE_2311)
#include ".\\Customers\\Huajia\\cfg_huajia_2311.h" 
#elif defined(HIMAGE_2311_04_021W)
#include ".\\Customers\\Huajia\\cfg_huajia_2311_04_021W.h" 
#elif defined(HIMAGE_2312_03_165W)
#include ".\\Customers\\Huajia\\cfg_huajia_2312_03-165w.h" 
#elif defined(HIMAGE_S161_03_146W)
#include ".\\Customers\\Huajia\\cfg_huajia_s161_03-146w.h" 
#elif defined(HIMAGE_2308_03_174W)
#include ".\\Customers\\Huajia\\cfg_huajia_2308_03-174w.h" 
#elif defined(HIMAGE_2320_03_170W)
#include ".\\Customers\\Huajia\\cfg_huajia_2320_03-170w.h" 
#elif defined(HIMAGE_2325_03_180W)
#include ".\\Customers\\Huajia\\cfg_huajia_2325_03-180w.h" 
#elif defined(HIMAGE_1250_03_185W)
#include ".\\Customers\\Huajia\\cfg_huajia_1250_03-185w.h"
#elif defined(HIMAGE_DP313)
#include ".\\Customers\\Huajia\\cfg_huajia_dp313.h" 
#elif defined(HIMAGE_2309_03_209W)
#include ".\\Customers\\Huajia\\cfg_huajia_2309_03-209w.h" 
#elif defined(HIMAGE_2309_04_029W)
#include ".\\Customers\\Huajia\\cfg_huajia_2309_04-029w.h" 
#elif defined(HIMAGE2315_HJ_03_22W)
#include ".\\Customers\\Huajia\\cfg_huajia_2315_hj_03_22w.h" 
#elif defined(HIMAGE2315_04_022W)
#include ".\\Customers\\Huajia\\cfg_huajia_2315_04_022w.h" 
#elif defined(HIMAGE_DP316)
#include ".\\Customers\\Huajia\\cfg_huajia_dp316.h" 
#elif defined(HIMAGE_3000)
#include ".\\Customers\\Huajia\\cfg_huajia_3000.h" 
#elif defined(HIMAGE_3000_2307)
#include ".\\Customers\\Huajia\\cfg_huajia_3000_2307.h" 
#elif defined(HIMAGE_1250_03_225W)
#include ".\\Customers\\Huajia\\cfg_huajia_1250_03_225W.h"
#elif defined(HIMAGE_DV_010B)
#include ".\\Customers\\Huajia\\cfg_huajia_DV-010B.h" 
#elif defined(HIMAGE_DP313_16)
#include ".\\Customers\\Huajia\\cfg_huajia_dp313_16.h" 
#elif defined(HIMAGE2203_242w)
#include ".\\Customers\\Huajia\\cfg_huajia_2203_242w.h" 
#elif defined(HIMAGE_2401)
#include ".\\Customers\\Huajia\\cfg_huajia_2401.h" 
#elif defined(HIMAGE_2308_04_101W)
#include ".\\Customers\\Huajia\\cfg_huajia_2308_04_101w.h"   
#elif defined(HIMAGE_2439)
#include ".\\Customers\\Huajia\\cfg_huajia_2439.h"
#elif defined(HIMAGE_DP313_16)
#include ".\\Customers\\Huajia\\cfg_huajia_dp313_16.h" 
    #else
        #include ".\\Customers\\Huajia\\cfg_huajia.h" 
    #endif

#ifdef HUAJIA_DVD     //fengjl  add 2004-03-29 15:56
#define MINTON_STOP_MUTE
#endif

#ifdef HJ_027_PCB   //fengjl add 2004-02-27 09:55
#define LOW_MUTE
#endif

#if 1
#undef SP_ALWAYS_BY_USER_CTL       //we use sub-picture selection in SETUP-MENU as our defult, Jeff 20020925

#define STOP_LOADER//03-113W

#if 1//def TEMP_TWO_CHANNEL
#define SETUP_ALL_VALID             //define it to let SETUP MENU is always valid, Jeff 20021023
#define ONLY_DOWNMIXOFF_CAN_SET_CE_RE
#define SET_PARENTAL_STS_AUTO_LOCK
#define USE_108MHZ
#define DVD_3D_SHOW_SPECTRUM

#ifdef USE_108MHZ
//#define REPEAT_AB_TOO_SHORT_DISABLE_3D
#define INVALID_3D_WHEN_AB
#endif
//#define ECHO_SPECIAL_PARA
#endif

#endif

#elif defined(SVA_DVD)          // majinping 2002-05-02 for SVA
    #include ".\\Customers\\Sva\\cfg_sva.h" 

#elif defined(WANGINE_DVD)      //alan add for wangine dvd 02-05-08
    #include ".\\Customers\\Wangine\\cfg_wangine.h" 

#elif defined(INTECH_DVD)       //XIAOSAN 02-05-20
    
//#define INTECH_DVD_16           //dingzhy
//#define INTECH_DVD_8202
//#define INTECH_8202S_16_DVD
#define INTECH_8202L_16_DVD
//#define INTECH_8202L_64_DVD

    #ifdef INTECH_DVD_16
        #include ".\\Customers\\Intech\\cfg_intech_16.h" 
    #elif defined(INTECH_DVD_8202)
        #include ".\\Customers\\Intech\\cfg_intech_8202.h"
    #elif defined(INTECH_8202S_16_DVD)
        #include ".\\Customers\\Intech\\cfg_intech_8202s_16.h"
    #elif defined(INTECH_8202L_16_DVD)
        #include ".\\Customers\\Intech\\cfg_intech_8202L_16.h"
    #elif defined(INTECH_8202L_64_DVD)
        #include ".\\Customers\\Intech\\cfg_intech_8202L_64.h"
    #else
    #include ".\\Customers\\Intech\\cfg_intech.h" 
    #endif
    
    //dingzhy add for intech 04-8-4 13:35
    #if 1
    #define BAD_DISC_SEQ_PLAY
    
    #define SUPPORT_JOLIET_FORMAT
    #define MODIFY_MULTI_SESSION_CD_DISC
    //#define USE_108MHZ
    
    #define STOP_LOADER
    
    #define RATING_8                  //if we define it, there are 8 ratings, 1/2/3/../8, otherwise, 3 ratings, Jeff 20020723
    #define FIX_RATING_8_DISPLAY
    #define SHOW_5_1CH
    #endif
#elif defined(LINKCONCEPT_DVD)
		//#define LINKCONCEPT_32_DVD         //VER:G32-XXX//for 8200/8202A 32M general customers dvd mode 
       //#define LINKCONCEPT_8202S_DVD       //VER:GS32-XXX//nono add 2004-10-16 16:49 for 8202S 32m general customers dvd mode
       #define LINKCONCEPT_8202D_DVD       //VER:GD32-XXX//nono add 2004-10-16 16:49 for 8202D 32m general customers dvd mode
       //#define LINKCONCEPT_16_DVD          //VER:G16-XXX//for 8200/8202A 16M general customers dvd mode
       //#define LINKCONCEPT_8202S_16_DVD          //for 8202S 16m//VER:GS16-XXX
       //#define LINKCONCEPT_8202D_16_DVD          //for 8202D 16m//VER:GD16-XXX
       //#define LINKCONCEPT_8202D_16_040_NO_MP4   //for 8202D 16m//VER:GD164XXX//SUPPORT WMA, NO MP4

    #if defined(LINKCONCEPT_32_DVD)
        #include ".\\Customers\\LINKCONCEPT\\cfg_linkconcept_32.h" 
    #elif defined(LINKCONCEPT_8202S_DVD)
        #include ".\\Customers\\LINKCONCEPT\\cfg_linkconcept_8202s.h" 
    #elif defined(LINKCONCEPT_8202D_DVD)
        #include ".\\Customers\\LINKCONCEPT\\cfg_linkconcept_8202d.h" 
    #elif defined(LINKCONCEPT_16_DVD)
        #include ".\\Customers\\LINKCONCEPT\\cfg_linkconcept_16.h" 
    #elif defined(LINKCONCEPT_8202S_16_DVD)
        #include ".\\Customers\\LINKCONCEPT\\cfg_linkconcept_8202s_16.h" 
    #elif defined(LINKCONCEPT_8202D_16_DVD)
        #include ".\\Customers\\LINKCONCEPT\\cfg_linkconcept_8202d_16.h" 
    #elif defined(LINKCONCEPT_8202D_16_040_NO_MP4)
        #include ".\\Customers\\LINKCONCEPT\\cfg_linkconcept_8202d_16_040_no_mp4.h"      
    #endif
    
    #if 0
    #define BAD_DISC_SEQ_PLAY
    
    #define SUPPORT_JOLIET_FORMAT
    #define MODIFY_MULTI_SESSION_CD_DISC
    
    #define STOP_LOADER
    
    #define RATING_8                  //if we define it, there are 8 ratings, 1/2/3/../8, otherwise, 3 ratings, Jeff 20020723
    #define FIX_RATING_8_DISPLAY
    #define SHOW_5_1CH
    #endif
#elif defined(JCG_DVD)          //2-6-18 17:14
    #include ".\\Customers\\Jcg\\cfg_jcg.h" 
    
#elif defined(KONKA_DVD)        //20020710
    #include ".\\Customers\\Konka\\cfg_konka.h" 

#elif defined(GAODASI_DVD)      //20020710
    #include ".\\Customers\\Gaodasi\\cfg_gaodasi.h" 
    
#elif defined(HOBO_DVD)
    #include ".\\Customers\\Hobo\\cfg_hobo.h" 

#elif defined(TIANKE_DVD)       //20020710
    #include ".\\Customers\\Tianke\\cfg_tianke.h" 

#elif defined(MICO_DVD)       //3-6-16 21:44
    #include ".\\Customers\\mico\cfg_mico.h"
#elif defined(XINDE_DVD)        //wangfeng 2003-12-25 10:25
    #include ".\\Customers\\xinde\cfg_xinde.h"
#elif defined(GBM_DVD)          //2-6-18 17:14

    //------------040407 add for standard---------------------------
    #define GBM_STANDARD            //gerry,2004-4-7 15:45            
    //------------040315---------------------------
    //#define GBM_P9C5_FULL         //dingzhy   04-03-15 5:36PM
/*********************************************************************/
    //------------040311 add-------------------------
    //#define GBM_P9C8_0501_8202
    //#define GBM_P9C8_0501_8202_256
    //#define GBM_P9Ce_f89_8202
    //#define GBM_P9C8_0501_8202_256_NS
    //#define GBM_PBCE_0500_8202_256_NS
    //#define GBM_16BIT_CARD_STD_8202_256_NS    //gerry add it for gbm 16bit card reader,2004-7-22 19:37
    #define GBM_DIVX_CERTIFICATION_8202_256_NS
/*********************************************************************/
    //#define GBM_P9C0//031121xx
    //#define GBM_P90K//021113xx
    //#define GBM_P9C6//051111xx
    //#define GBM_BOOK_DVD//gbm-010
    //#define GBM_16M//gbm-020
    //#define GBM_P907_32//051111xx
    //#define GBM_P907_0502//051111xx
    //#define GBM_P9CB_F529// for TCL,2004-1-16 16:41
    //-----------------0116 -------------
    //#define GBM_F20A_KB01//book
    //#define GBM_F20A_KB02//book
    //#define GBM_P9CA
    //#define GBM_P9CA_KB01
    //#define GBM_P9CA_0001
    //#define GBM_P9CA_0002
    //#define GBM_P9CB
    //#define GBM_P9CB_KB01
    //#define GBM_P9CB_0001
    //#define GBM_P9CB_0002
    //#define GBM_P971_0503             //PAL-M
    //#define GBM_P971_SAMPLE           //GBM_P971_0503 for all region
    //#define GBM_P902
    //#define GBM_P902_0393
    //#define GBM_P902_0003
    //#define GBM_P902_0003_6CH
    //#define GBM_P90M_0005             //PAL-M
    //#define GBM_P9C3
    //#define GBM_P9C9
    //#define GBM_P9C9_0506
    //#define GBM_P902_0001             //PAL-Nc
    //#define GBM_P9C0_0503
    //#define GBM_P9C0_0503_16
    //#define GBM_P9C2_0507
    //#define GBM_P9C2_0508
    //#define GBM_P919_0500
    //#define GBM_P9CA_0502
    //#define GBM_P9C3_0501
    //#define GBM_P9C3_0502
    
    //---------------0130 add ----------------
    //#define GBM_P902_0002             //PAL-M
    //#define GBM_P971_0001
    //#define GBM_P971_000A             //PAL-M
    //#define GBM_P9C3_0001
    //#define GBM_P90H_0005
    //#define GBM_P9C0_0500
    //#define GBM_P90L_0502             //Especially for WMA&DVD-AUDIO&USER_LOGO,gerry,2004-1-30 18:55 
    
    //--------------040201 add ----------------
    //#define GBM_F20A_KB01_EMI//book_dvd for emi test function,gerry,2004-2-1 14:28

    //-------------040203 add -----------------
    //#define GBM_P9CG_0503     //with DTS & DVD_AUDIO & CARD-READER,gerry,2004-2-3 13:24
    //#define GBM_P9CC_0501     //with CARD-READER,gerry,2004-2-7 10:16
    
    //-------------040205 add -----------------
    //#define GBM_P9CD_0503     //with DTS & DVD_AUDIO ,gerry,2004-2-5 19:06
    //#define GBM_P9CE_0503     //with DTS & DVD_AUDIO & CARD-READER,gerry,2004-2-3 13:24
    //#define GBM_P9CF_0501     //with DTS & DVD_AUDIO & CARD-READER,gerry,2004-2-3 13:24
    //#define GBM_P90H_0501
    //#define GBM_P9C3_0500
    //#define GBM_P9C8_0501
    //#define GBM_P9CF_0504
    //#define GBM_P9CC_0501     //with  CARD-READER,gerry,2004-2-7 9:53
    
    //-------------040211 add -----------------
    //#define GBM_P907_0501             //PAL-Nc
    //#define GBM_P90L_0501             //PAL-M
    //#define GBM_P907_0501_16
    
    //------------040211 wangap add-------------
    //#define GBM_P9CF_SAMPLE     
    //#define GBM_P9CA_SAMPLE   
     //#define GBM_P9CC_SAMPLE
    //#define GBM_P9C0_SAMPLE       //with wma   
    //#define GBM_P9D2_SAMPLE
     //#define GBM_P907_SAMPLE
    //#define GBM_PABC_SAMPLE
      //#define GBM_K010_SAMPLE
    //#define GBM_99_P9CC_0501      //with CARD-READER
    //#define GBM_98_P9CE_KA01
     //#define GBM_99_P9C5_0501
    //#define GBM_99_P9AA_0001      //with Pro-II
    //#define GBM_99_P9CG_0502      //with CARD-READER
    //#define GBM_99_P90K_0001      //with wma 
    //#define GBM_P90S_SAMPLE
    //#define GBM_PA0T_0A03

    //-------------040211 add -----------------
    //#define GBM_P902_0003_PAL_BG              //PAL-B/G == PAL

    //-------------- 040211 add ----------------
    //#define GBM_P9C9_KA01     
    //#define GBM_P80D_0001     
    //#define GBM_P818_0500
    //#define GBM_P9CQ_0502
    //#define GBM_P9CA_0001_6CH         //for Hair 5.1ch,with WMA&PC-VGA&P-SCAN, 2004/2/11 04:18と
    //#define GBM_P9C5_0001             //for TCL 
    //#define GBM_P9C6_0501

    //------------- 040213 ADD ---------------- 
    //#define GBM_P9CA_0503             //for ANGLE_OSD and RATING test,2004-2-13 16:55
     
    //------------ 040216 -----------
    //#define GBM_P971_0503_S               //PAL-M,    

    //------------- 040217 add ----------------
    //#define GBM_P90H_0501_S             //for sample now,2004-2-17 16:54
    //#define GBM_P90L_0501_S             //for sample now,2004-2-17 16:54
    //#define GBM_PAOT_0A01             //sample?

    //------------040219 add -------------------
    //#define GBM_P90H_0502                             

    //------------040225 add -------------------
    //#define GBM_P9CC_SAMPLE_2         //CARD-READER,2004-2-25 16:43
    //#define GBM_F20A_KB01_FULL        //BOOK_DVD FULL_FUNCTION,2004-2-25 22:59
    //#define GBM_P9C8_K001             //USER LOGO FUNCTION,2004-2-27 11:30
     
    //else use cfg_gbm.h//gbm-000
        
    #ifdef GBM_STANDARD
    #include ".\\Customers\\Gbm\\cfg_gbm_standard.h" 

    #elif defined(GBM_P9C0)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c0.h" 
    #elif defined(GBM_P9C5_FULL)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c5_full.h" 
    #elif defined(GBM_P9C8_0501_8202)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c8_0501_8202.h" 
    
    #elif defined(GBM_P9Ce_f89_8202)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9ce_f89_8202.h" 
    
    #elif defined(GBM_P9C8_0501_8202_256)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c8_0501_8202_256.h" 
    
    #elif defined(GBM_P9C8_0501_8202_256_NS)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c8_0501_8202_256_ns.h" 
    
    #elif defined(GBM_PBCE_0500_8202_256_NS)
    #include ".\\Customers\\Gbm\\cfg_gbm_pbce_0500_8202_256_ns.h" 
    
    //gerry for gbm 16bit full card reader,2004-7-20 20:50
    #elif defined(GBM_16BIT_CARD_STD_8202_256_NS)
    #include ".\\Customers\\Gbm\\cfg_gbm_16bit_card_std_8202_256_ns.h" 

    //gerry add it for gbm DIVX cert,2004-7-22 19:43
    #elif defined(GBM_DIVX_CERTIFICATION_8202_256_NS)
    #include ".\\Customers\\Gbm\\cfg_gbm_divx_certification_8202_256_ns.h" 
        
    #elif defined(GBM_P90K)
    #include ".\\Customers\\Gbm\\cfg_gbm_p90k.h" 
    #elif defined(GBM_P9C6)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c6.h" 
    #elif defined(GBM_BOOK_DVD)
    #include ".\\Customers\\Gbm\\cfg_gbm_book_dvd.h"     
    #elif defined(GBM_16M)
    #include ".\\Customers\\Gbm\\cfg_gbm_16m.h"     
    #elif defined(GBM_P907_32)
    #include ".\\Customers\\Gbm\\cfg_gbm_p907_32.h"     
    #elif defined(GBM_P907_0502)
    #include ".\\Customers\\Gbm\\cfg_gbm_p907_0502.h"     

    //------------040116 add-----------------
    #elif defined(GBM_P9CB_F529)        //for GBM_TCL CUS,gerry,2004-1-17 14:14
    #include ".\\Customers\\Gbm\\cfg_gbm_p9cb_f52p.h"     
    #elif defined(GBM_F20A_KB01)
    #include ".\\Customers\\Gbm\\cfg_gbm_f20a_kb01.h"  
    #elif defined(GBM_F20A_KB02)
    #include ".\\Customers\\Gbm\\cfg_gbm_f20a_kb02.h"  
    #elif defined(GBM_P9CA_KB01)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9ca_kb01.h"      
    #elif defined(GBM_P9CB_KB01)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9cb_kb01.h"    
    #elif defined(GBM_P971_0503)
    #include ".\\Customers\\Gbm\\cfg_gbm_p971_0503.h"      
    #elif defined(GBM_P971_SAMPLE)
    #include ".\\Customers\\Gbm\\cfg_gbm_p971_sample.h"      
    #elif defined(GBM_P902)
    #include ".\\Customers\\Gbm\\cfg_gbm_p902.h"  
    #elif defined(GBM_P902_0003)        //2CH,PAL-M
    #include ".\\Customers\\Gbm\\cfg_gbm_p902_0003.h"   
    #elif defined(GBM_P902_0003_6CH)        //5.1CH,PAL-N
    #include ".\\Customers\\Gbm\\cfg_gbm_p902_0003_6ch.h"   
    #elif defined(GBM_P90M_0005)
    #include ".\\Customers\\Gbm\\cfg_gbm_p90m_0005.h"   
    #elif defined(GBM_P9C3)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c3.h"   
    #elif defined(GBM_P9C9)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c9.h"                
    #elif defined(GBM_P902_0001)
    #include ".\\Customers\\Gbm\\cfg_gbm_p902_0001.h"    
    #elif defined(GBM_P9C0_0503)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c0_0503.h"   
    #elif defined(GBM_P9C0_0503_16)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c0_0503_16.h"   
    #elif defined(GBM_P9C9_0506)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c9_0506.h" 
    #elif defined(GBM_P9CB_0001)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9cb_0001.h" 
    #elif defined(GBM_P9CA_0002)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9cA_0002.h" 
    #elif defined(GBM_P9C2_0507)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c2_0507.h" 
    #elif defined(GBM_P9C2_0508)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c2_0508.h" 
    #elif defined(GBM_P9CB_0002)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9cb_0002.h" 
    #elif defined(GBM_P9CA_0001)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9ca_0001.h" 
    #elif defined(GBM_P902_0393)
    #include ".\\Customers\\Gbm\\cfg_gbm_p902_0393.h" 
    #elif defined(GBM_P9CB)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9cb.h" 
    #elif defined(GBM_P9CA)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9ca.h" 
    #elif defined(GBM_P919_0500)
    #include ".\\Customers\\Gbm\\cfg_gbm_p919_0500.h" 
    #elif defined(GBM_P9CA_0502)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9ca_0502.h" 
    #elif defined(GBM_P9C3_0501)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c3_0501.h" 
    #elif defined(GBM_P9C3_0502)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c3_0502.h" 
    //--------0130 add------------
    #elif defined(GBM_P902_0002)
    #include ".\\Customers\\Gbm\\cfg_gbm_p902_0002.h"  
    #elif defined(GBM_P971_0001)
    #include ".\\Customers\\Gbm\\cfg_gbm_p971_0001.h" 
    #elif defined(GBM_P971_000A)
    #include ".\\Customers\\Gbm\\cfg_gbm_p971_000a.h" 
    #elif defined(GBM_P9C3_0001)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c3_0001.h" 
    #elif defined(GBM_P90H_0005)
    #include ".\\Customers\\Gbm\\cfg_gbm_p90h_0005.h" 
    #elif defined(GBM_P9C0_0500)
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c0_0500.h" 
    #elif defined(GBM_P90L_0502)
    #include ".\\Customers\\Gbm\\cfg_gbm_p90l_0502.h"           //Especially for WMA&DVD-AUDIO&USER_LOGO,gerry,2004-1-30 18:55 

    //----------040201 add --------
    #elif defined(GBM_F20A_KB01_EMI)
    #include ".\\Customers\\Gbm\\cfg_gbm_f20a_kb01_emi.h"

    //----------040203 add---------
    #elif defined(GBM_P9CG_0503)                                //with DTS & DVD_AUDIO & CARD-READER,gerry,2004-2-3 13:24
    #include ".\\Customers\\Gbm\\cfg_gbm_p9cg_0503.h"
    #elif defined(GBM_P9CC_0501)                                //with DTS & DVD_AUDIO & CARD-READER,gerry,2004-2-3 13:24
    #include ".\\Customers\\Gbm\\cfg_gbm_p9cc_0501.h"

    //----------040205 add---------
    #elif defined(GBM_P9CD_0503)                                //with DTS & DVD_AUDIO ,gerry,2004-2-5 19:06
    #include ".\\Customers\\Gbm\\cfg_gbm_p9cd_0503.h"
    #elif defined(GBM_P9CE_0503)                                //with DTS & DVD_AUDIO ,gerry,2004-2-5 19:06
    #include ".\\Customers\\Gbm\\cfg_gbm_p9ce_0503.h"
    #elif defined(GBM_P9CF_0501)                                //with DTS & DVD_AUDIO ,gerry,2004-2-5 19:06
    #include ".\\Customers\\Gbm\\cfg_gbm_p9cf_0501.h"
    #elif defined(GBM_P90H_0501)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_p90h_0501.h"
    #elif defined(GBM_P9C3_0500)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c3_0500.h"
    #elif defined(GBM_P9C8_0501)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c8_0501.h"
    #elif defined(GBM_P9CF_0504)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_p9cf_0504.h"
    #elif defined(GBM_P9CC_0501)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_p9cc_0501.h"

    //------------ 040211 add -------------
    #elif defined(GBM_P907_0501)
    #include ".\\Customers\\Gbm\\cfg_gbm_p907_0501.h" 
    #elif defined(GBM_P90L_0501)
    #include ".\\Customers\\Gbm\\cfg_gbm_p90l_0501.h" 
    #elif defined(GBM_P907_0501_16)
    #include ".\\Customers\\Gbm\\cfg_gbm_p907_0501_16.h" 
    
     //-----------wangap add 2004/02/11--------
    #elif defined(GBM_P9CF_SAMPLE)                              
    #include ".\\Customers\\Gbm\\cfg_gbm_p9cf_sample.h"
    #elif defined(GBM_P9CA_SAMPLE)                              
    #include ".\\Customers\\Gbm\\cfg_gbm_p9ca_sample.h"
    #elif defined(GBM_P9CC_SAMPLE)                              
    #include ".\\Customers\\Gbm\\cfg_gbm_p9cc_sample.h"
    #elif defined(GBM_P9C0_SAMPLE)                              
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c0_sample.h"
    #elif defined(GBM_P9D2_SAMPLE)                              
    #include ".\\Customers\\Gbm\\cfg_gbm_p9d2_sample.h"
    #elif defined(GBM_P907_SAMPLE)                              
    #include ".\\Customers\\Gbm\\cfg_gbm_p907_sample.h"
    #elif defined(GBM_PABC_SAMPLE)                              
    #include ".\\Customers\\Gbm\\cfg_gbm_pabc_sample.h"
    #elif defined(GBM_K010_SAMPLE)                              
    #include ".\\Customers\\Gbm\\cfg_gbm_k010_sample.h"
    #elif defined(GBM_99_P9CC_0501)                             
    #include ".\\Customers\\Gbm\\cfg_gbm_99_p9cc_0501.h"
    #elif defined(GBM_99_P9C5_0501)                             
    #include ".\\Customers\\Gbm\\cfg_gbm_99_p9c5_0501.h"
    #elif defined(GBM_99_P9CG_0502)                             
    #include ".\\Customers\\Gbm\\cfg_gbm_99_p9cg_0502.h"
    #elif defined(GBM_99_P90K_0001)                             
    #include ".\\Customers\\Gbm\\cfg_gbm_99_p90k_0001.h"
    #elif defined(GBM_P90S_SAMPLE)                              
    #include ".\\Customers\\Gbm\\cfg_gbm_p90s_sample.h"
    #elif defined(GBM_PA0T_0A03)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_pa0t_0a03.h"
    #elif defined(GBM_F20A_SAMPLE)  //no use now wangap2004/2/11                            
    #include ".\\Customers\\Gbm\\cfg_gbm_f20a_sample.h"

    //------------ 040213 add -------------
    #elif defined(GBM_P902_0003_PAL_BG)
    #include ".\\Customers\\Gbm\\cfg_gbm_p902_0003_pal_bg.h" 

    //------------040211 add -------------------
    #elif defined(GBM_P9C9_KA01)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c9_ka01.h"
    #elif defined(GBM_P80D_0001)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_p80d_0001.h"
    #elif defined(GBM_P818_0500)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_p818_0500.h"
    #elif defined(GBM_P9CQ_0502)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_p9cq_0502.h"
    #elif defined(GBM_P9CA_0001_6CH)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_p9ca_0001_6ch.h"
    #elif defined(GBM_P9C5_0001)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c5_0001.h"
    #elif defined(GBM_P9C6_0501)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c6_0501.h"

    //------------040213 add -------------------
    #elif defined(GBM_P9CA_0503)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_p9ca_0503.h"

    //----------- 040216 add---------------
    #elif defined(GBM_P971_0503_S)
    #include ".\\Customers\\Gbm\\cfg_gbm_p971_0503_s.h" 

    //------------040217 add -------------------
    #elif defined(GBM_P90H_0501_S)                              
    #include ".\\Customers\\Gbm\\cfg_gbm_p90h_0501_s.h"
    #elif defined(GBM_P90L_0501_S)                              
    #include ".\\Customers\\Gbm\\cfg_gbm_p90l_0501_s.h"
    #elif defined(GBM_PAOT_0A01)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_paot_0a01.h"
     
    //------------- 040219 add ----------------
    #elif defined(GBM_P90H_0502)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_p90h_0502.h"

    //------------- 040225 add ----------------
    #elif defined(GBM_P9CC_SAMPLE_2)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_p9cc_sample_2.h"
    #elif defined(GBM_F20A_KB01_FULL)                               
    #include ".\\Customers\\Gbm\\cfg_gbm_f20a_kb01_full.h"
    #elif defined(GBM_P9C8_K001)                                
    #include ".\\Customers\\Gbm\\cfg_gbm_p9c8_k001.h"

    #else
    #include ".\\Customers\\Gbm\\cfg_gbm.h" 
    #endif
    
//gerry mark it for MIC is on when user mute,2004-2-2 22:32
//#define MUTE_EXECUTE_MIC//NONO 4-1-5 12:11
    
#if 1
#define USE_108MHZ
#define SETUP_ALL_VALID             //define it to let SETUP MENU is always valid, Jeff 20021023
#define ONLY_DOWNMIXOFF_CAN_SET_CE_RE

#ifndef SDRAM_16Mb_Mode         //gerry,2004-2-7 16:36
#define GBM_3D_KEY_ALL_VALID
#endif//SDRAM_16Mb_Mode

#define GBM_NEW_OSD_STR
#define GBM_RATING_SHOW_PARENTAL            //gerry,2004-2-4 9:15
#endif
    
//#define SUPER_DEFAULT_OSD_LANG                //wanghaoyin,2004-2-10 20:31

#ifndef NO_MIC
#define GBM_MIC_FUNCTION
#endif    

#define GBM_DEFAULT_NTSC_CAPTION_OFF        //gerry,2004-2-13 14:43



#define PLAY_JPE_JPEG_FILE                              //we can play jpeg and jpe file,2004-2-26 10:40

#define ISO9660_FILE_NOT_SHOW_EXTEND_NAME                       //Iso9660 file will not show extend name,2004-2-27 19:48

//#define GBM_SLOT_IN_LOADER_TEST                       //test slot_in_loader,open tray when no_disc,2004-2-27 19:49

#ifndef DVD_5_DISC_RESUME//lijd 2005-4-11 16:11
#undef POWER_RESUME
#endif

#define MODIFY_MULTI_SESSION_CD_DISC

#ifdef USER_LOGO        //temp for NEXT PAGE,gerry 2004-3-29 10:36
#define NEXTPAGE_SYS
#endif

#elif defined(GBM_AP_DVD)          //2003-12-12 13:10
    //--------------- 2003_12_12 add ----------------
    //#define GBM_AP_DVD_STANDARD
    //--------------- 2005_02_25 add ----------------
    #define GBM_AP_DVD_16//added by wangwei,2005-2-25 11:46
//***********************************************************
    #ifdef GBM_AP_DVD_STANDARD
        #include ".\\Customers\\Gbm_ap\\cfg_gbm_ap.h" 
    #elif defined(GBM_AP_DVD_16)
        #include ".\\Customers\\Gbm_ap\\cfg_gbm_ap_16.h"
    #else
    #include ".\\Customers\\Gbm_ap\\cfg_gbm_ap.h" 
    #endif

#elif defined(WEIKING_DVD_AMP)
//#define WEIKING_SANAWIN_DVD

#ifdef WEIKING_SANAWIN_DVD
#include ".\\Customers\\Weiking\\cfg_weiking_sanawin.h"
#else 
    #include ".\\Customers\\Weiking\\cfg_weiking.h" 
#endif

#elif defined(CNMOTOR_DVD)      //Jeff 20020913
    #include ".\\Customers\\Cnmotor\\cfg_cnmotor.h" 
    
#elif defined(BMT_DVD)          //2-6-18 17:14
    #include ".\\Customers\\bmt\\cfg_bmt.h" 

#elif defined (KSD_DVD)
    #define PANDA_DVD           // alan, 2003/8/15 10:50PM
    //#define PANDA_DVD_EN      //gerry,for panda english order,2003-12-15 10:39
    //#define PANDA_DVD_EN_L109 //gerry,for panda spanish order,2003-12-17 9:48
    //#define PANDA_DVD_16      //gerry,2004-3-4 16:59
    //#define PANDA_DVD_ID3     //gerry,2004-3-15 16:42
    //#define PANDA_DVD_DV_923  //gerry,2004-3-16 16:59
    //#define PANDA_DVD_8202_6961      //gerry,2004-5-22 10:50
    //#define PANDA_DVD_8202_DP109     //2CHANNEL,gerry,2004-5-22 15:29
    
    #ifdef PANDA_DVD
        #include ".\\Customers\\TrendDigit\\cfg_panda.h" 
    #elif defined(PANDA_DVD_EN)
        #include ".\\Customers\\TrendDigit\\cfg_panda_en.h" 
    #elif defined(PANDA_DVD_EN_L109)
        #include ".\\Customers\\TrendDigit\\cfg_panda_en_l109.h" 
    #elif defined(PANDA_DVD_16)
        #include ".\\Customers\\TrendDigit\\cfg_panda_16.h" 
    #elif defined(PANDA_DVD_ID3)
        #include ".\\Customers\\TrendDigit\\cfg_panda_id3.h" 
    #elif defined(PANDA_DVD_DV_923)
        #include ".\\Customers\\TrendDigit\\cfg_panda_dv_923.h" 
    #elif defined(PANDA_DVD_8202_6961)
        #include ".\\Customers\\TrendDigit\\cfg_panda_8202_6961.h" 
    #elif defined(PANDA_DVD_8202_DP109)
        #include ".\\Customers\\TrendDigit\\cfg_panda_8202_dp109.h" 
    #else
    #include ".\\Customers\\TrendDigit\\cfg_ksd.h" 
    #endif
    
#elif defined (ZHAOCHI_DVD)      //LYC 2005-04-04
      //#define ZHAOCHI_DVD_8202S
     // #define ZHAOCHI_DVD_8202S_16
        //#define ZHAOCHI_DVD_8202
      //  #define MTC_DVD_DVB_8202D_6600
       #define  MTC_PORTABLE_DVB_8202D_6600///yangli add ,2005-11-10 16:25
      // #define MTC_DVD_8202D_6500   //FanGang added for mtc HDMI,2005-11-11 14:41
       
    #ifdef ZHAOCHI_DVD_8202S
        #include ".\\Customers\\ZHAOCHI\\cfg_zhaochi_8202s.h" 
    #elif defined(ZHAOCHI_DVD_8202S_16)
        #include ".\\Customers\\ZHAOCHI\\cfg_zhaochi_8202s_16.h" 
    #elif defined(ZHAOCHI_DVD_8202)
        #include ".\\Customers\\ZHAOCHI\\cfg_zhaochi_8202.h" 
    #elif defined(MTC_DVD_DVB_8202D_6600)
        #include ".\\Customers\\ZHAOCHI\\cfg_mtc_dvd_dvb_8202d_6600.h" 
    #elif defined(MTC_PORTABLE_DVB_8202D_6600) ///yang add ,2005-11-10 16:25
        #include ".\\Customers\\ZHAOCHI\\cfg_mtc_portable_dvb_8202d_6600.h" 
    #elif defined(MTC_DVD_8202D_6500)  //FanGang added 2005-11-10 17:55
        #include ".\\Customers\\ZHAOCHI\\cfg_MTC_8202D_6500.h" 
    #endif
        
#elif defined(ORITRON_DVD)
    //#define ORITRON_DVD_RECEIVER      //xyy 2004-8-11
    //#define W5611
    //#define W5690
    //#define W5900B
    #define W8202S
	//#define  ORITRON_DVD_HT220_RECEIVER  //zhoulin 05-04-13
    //#define ORITRON_8202D//zhoulin 
    #ifdef ORITRON_DVD_RECEIVER
        #include ".\\Customers\\Oritron\\cfg_oritron_rcvr.h"
    #elif defined(W5611)
        #include ".\\Customers\\Oritron\\cfg_oritron_5611.h"
    #elif defined(W5690)
        #include ".\\Customers\\Oritron\\cfg_oritron_5690.h"
    #elif defined(W5900B)
        #include ".\\Customers\\Oritron\\cfg_oritron_5900b.h"
    #elif defined(W8202S)
        #include ".\\Customers\\Oritron\\cfg_oritron_8202s.h"
    #elif defined(ORITRON_DVD_HT220_RECEIVER)
        #include ".\\Customers\\Oritron\\cfg_oritron_HT220_rcvr.h"
    #elif defined(ORITRON_8202D)
        #include ".\\Customers\\Oritron\\cfg_oritron_8202D.h"
    #else
    	#include ".\\Customers\\Oritron\\cfg_oritron.h"
    #endif
#elif defined(ORITRON_HK_DVD) //lijd 2005-5-8 16:21 
    //#define ORITRON_8202S_2X16_16BIT_DVD //lijd 2005-4-11 16:02
    //#define ORITRON_8202S_1X16_16BIT_DVD//lijd 2005-4-11 16:02
    //#define ORITRON_8202D_2X16_16BIT_DVD//lijd 2005-4-11 16:02
    //#define ORITRON_8202D_1X16_16BIT_DVD//lijd 2005-5-8 14:37
    //#define ORITRON_8202D_3111_DVD//caoh 2005-6-17 16:53
    //#define ORITRON_8202D_4110_DVD//caoh 2005-6-17 16:53
    //#define ORITRON_8202D_4119_DVD//caoh 2005-6-17 16:53
    //#define ORITRON_8202D_4125_DVD//caoh 2005-6-17 16:53
    //#define ORITRON_8202D_4127_DVD//caoh 2005-6-17 16:53
    //#define ORITRON_8202D_5112_DVD//caoh 2005-6-17 16:53
    //#define ORITRON_8202D_5115_DVD//caoh 2005-6-17 16:53
    //#define ORITRON_8202D_5116_DVD//caoh 2005-6-17 16:53
    //#define ORITRON_8202D_5117_DVD//caoh 2005-6-17 16:53
    //#define ORITRON_8202D_5121_DVD//caoh 2005-6-17 16:53
    //#define ORITRON_8202D_5122_DVD//caoh 2005-6-17 16:53
    #define ORITRON_8202D_6122_DVD//caoh 2005-6-17 16:53
    
    #ifdef ORITRON_8202S_2X16_16BIT_DVD        
   		#include ".\\Customers\\HK_Oritron\\cfg_oritron_8202S_2X16_16.h"
   	#elif defined(ORITRON_8202S_1X16_16BIT_DVD)
   		#include ".\\Customers\\HK_Oritron\\cfg_oritron_8202S_1X16_16.h"	
    #elif defined(ORITRON_8202D_2X16_16BIT_DVD)
   		#include ".\\Customers\\HK_Oritron\\cfg_oritron_8202D_2X16_16.h"	
   	#elif defined(ORITRON_8202D_1X16_16BIT_DVD)
   		#include ".\\Customers\\HK_Oritron\\cfg_oritron_8202D_1X16_16.h"	
   	#elif defined(ORITRON_8202D_3111_DVD)
   		#include ".\\Customers\\HK_Oritron\\cfg_oritron_8202D_DVD3111.h"
   	#elif defined(ORITRON_8202D_4110_DVD)
   		#include ".\\Customers\\HK_Oritron\\cfg_oritron_8202D_DVD4110.h"
   	#elif defined(ORITRON_8202D_4119_DVD)
   		#include ".\\Customers\\HK_Oritron\\cfg_oritron_8202D_DVD4119.h"	
   	#elif defined(ORITRON_8202D_4125_DVD)
   		#include ".\\Customers\\HK_Oritron\\cfg_oritron_8202D_DVD4125.h"
   	#elif defined(ORITRON_8202D_4127_DVD)
   		#include ".\\Customers\\HK_Oritron\\cfg_oritron_8202D_DVD4127.h"	
   	#elif defined(ORITRON_8202D_5112_DVD)
   		#include ".\\Customers\\HK_Oritron\\cfg_oritron_8202D_DVD5112.h"
   	#elif defined(ORITRON_8202D_5115_DVD)
   		#include ".\\Customers\\HK_Oritron\\cfg_oritron_8202D_DVD5115.h"		    
   	#elif defined(ORITRON_8202D_5116_DVD)
   		#include ".\\Customers\\HK_Oritron\\cfg_oritron_8202D_DVD5116.h"
   	#elif defined(ORITRON_8202D_5117_DVD)
   		#include ".\\Customers\\HK_Oritron\\cfg_oritron_8202D_DVD5117.h"
   	#elif defined(ORITRON_8202D_5121_DVD)
   		#include ".\\Customers\\HK_Oritron\\cfg_oritron_8202D_DVD5121.h"
        #elif defined(ORITRON_8202D_5122_DVD)
   		#include ".\\Customers\\HK_Oritron\\cfg_oritron_8202D_DVD5122.h"
   	#elif defined(ORITRON_8202D_6122_DVD)
   		#include ".\\Customers\\HK_Oritron\\cfg_oritron_8202D_DVD6122.h"	
    #endif

#elif defined (HK_ORITRON_DVD_RECEIVER)    //hongfeng 2005-07-09 
    //#define ORITRON_RECEIVER_6001
    //#define ORITRON_RECEIVER_5105 
    //#define ORITRON_RECEIVER_6008   ///2.1ch
    //#define ORITRON_RECEIVER_5003
    #define ORITRON_RECEIVER_6505
    //#define ORITRON_RECEIVER_DPL937
    #if defined(ORITRON_RECEIVER_6001)
    #include ".\\Customers\\Oritron\\cfg_oritron_receiver_6001.h"    
    #elif defined(ORITRON_RECEIVER_5105)
    #include ".\\Customers\\Oritron\\cfg_oritron_receiver_5105.h"   
    #elif defined(ORITRON_RECEIVER_6008)
    #include ".\\Customers\\Oritron\\cfg_oritron_receiver_6008.h"  
    #elif defined(ORITRON_RECEIVER_5003)
    #include ".\\Customers\\Oritron\\cfg_oritron_receiver_5003.h"  
    #elif defined(ORITRON_RECEIVER_6505)
    #include ".\\Customers\\Oritron\\cfg_oritron_receiver_6505.h"  
    #elif defined(ORITRON_RECEIVER_DPL937)
    #include ".\\Customers\\Oritron\\cfg_oritron_receiver_dpl937.h"    
    #endif
    
#elif defined (ORIENTPOWER_DVD)
    #include ".\\Customers\\OrientPower\cfg_orientpower.h"

#elif defined(OUR_MIND_DVD)
//model name, choose one
//---------------------
//#define OUR_MIND_DVD_LCD
#define OUR_MIND_DVD_NO_LCD
//---------------------
#ifdef OUR_MIND_DVD_LCD
    #include ".\\Customers\\ourmind\\cfg_ourmind.h" 
#elif defined(OUR_MIND_DVD_NO_LCD)
#include ".\\Customers\\ourmind\\cfg_ourmind_no_lcd.h" 
#endif 
       
#elif defined(SUOJIA_DVD)
    #include ".\\Customers\\suojia\\cfg_suojia.h" 

#elif defined(CONSER_DVD)

//#define CONSERproview_288k2
//#define CONSERproview_288k
//#define CONSERapollo_288k
//#define CONSERproview_a
#define CONSERproview_b


#if defined(CONSERproview_288k2)
    #include ".\\Customers\\Conser\\cfg_conserproview_288k2.h"
#elif defined(CONSERproview_288k)
    #include ".\\Customers\\Conser\\cfg_conserproview_288k.h"
#elif defined(CONSERapollo_288k)
    #include ".\\Customers\\Conser\\cfg_conserapollo_288k.h"
#elif defined(CONSERproview_a)
        #include ".\\Customers\\Conser\\cfg_conserproview_a.h"
#elif defined(CONSERproview_b)
        #include ".\\Customers\\Conser\\cfg_conserproview_b.h"
#else
    #include ".\\Customers\\Conser\\cfg_conser.h"
#endif

#elif defined(PROVIEW_DVD)

//#define PROVIEW_GPIO_BUTTON      // GPIO control buttons & LEDs
//#define PROVIEW_VFD_WO_LED        //(model-01)16312-button-only(2 channel)
//#define PROVIEW_VFD_LED           //(model-02)16312-with-LED-display(2 channel)
//#define PROVIEW_VFD_WO_LED_6CH      //(model-03)16312-button-only(6 channel)
//#define PROVIEW_VFD_LED_6CH       //(model-04)16312-with-LED-display(6 channel)
//#define PROVIEW_VFD_WO_LED_6CH_CARD       //(model-04)16312-with-LED-display+card(6 channel)
#define PROVIEW_DV_509       // the same as PROVIEW_VFD_LED_6CH, with different VFD panel
//#define PROVIEW_DV_511       // the same as PROVIEW_VFD_LED_6CH, with different VFD panel
//#define PROVIEW_DV_507       // the same as PROVIEW_VFD_LED, with different VFD panel
//#define PROVIEW_DV_503       // the same as PROVIEW_GPIO_BUTTON
//#define PROVIEW_DV_527       // the same as PROVIEW_GPIO_BUTTON

#if defined(PROVIEW_VFD_WO_LED)
    #include ".\\Customers\\Proview\\cfg_proview_vfd_wo_led.h"
#elif defined(PROVIEW_VFD_LED)
    #include ".\\Customers\\Proview\\cfg_proview_vfd_led.h"
#elif defined(PROVIEW_VFD_WO_LED_6CH)
    #include ".\\Customers\\Proview\\cfg_proview_vfd_wo_led_6ch.h"
#elif defined(PROVIEW_VFD_LED_6CH)
    #include ".\\Customers\\Proview\\cfg_proview_vfd_led_6ch.h"
#elif defined(PROVIEW_VFD_WO_LED_6CH_CARD)
    #include ".\\Customers\\Proview\\cfg_proview_vfd_wo_led_6ch_card.h"
#elif defined(PROVIEW_GPIO_BUTTON)
    #include ".\\Customers\\Proview\\cfg_proview_gpiokey_6ch.h"
#elif defined(PROVIEW_DV_509)
    #include ".\\Customers\\Proview\\cfg_proview_509.h"
#elif defined(PROVIEW_DV_511)
    #include ".\\Customers\\Proview\\cfg_proview_511.h"
#elif defined(PROVIEW_DV_507)
    #include ".\\Customers\\Proview\\cfg_proview_507.h"
#elif defined(PROVIEW_DV_503)
    #include ".\\Customers\\Proview\\cfg_proview_gpiokey_6ch.h"
#elif defined(PROVIEW_DV_527)
    #include ".\\Customers\\Proview\\cfg_proview_gpiokey_6ch_527.h"    
#else
    #include ".\\Customers\\Proview\\cfg_proview.h"
#endif

#elif defined(PULIANG_DVD)      //Yaowh add. 04-12-03
    //#define PULIANG_DVD_320
    //#define PULIANG_DVD_420
    #ifdef PULIANG_DVD_320
        #include ".\\Customers\\PuLiang\\cfg_puliang_320.h"
    #elif defined(PULIANG_DVD_420)
        #include ".\\Customers\\PuLiang\\cfg_puliang_420.h"
    #else
        #include ".\\Customers\\PuLiang\\cfg_customers.h"
    #endif

#elif defined (QISHENG_DVD)
	#define DVD_SEQ_PLAY
	//#define QISHENG_8202_DVD
	#define QISHENG_8202S_DVD
	
	#ifdef QISHENG_8202_DVD
		#include ".\\Customers\\QiSheng\\cfg_qisheng_8202.h"
	#elif defined(QISHENG_8202S_DVD)
		#include ".\\Customers\\QiSheng\\cfg_qisheng_8202S.h"
	#else
    #include ".\\Customers\\QiSheng\\cfg_qisheng.h" 
    #endif 

#elif defined (YAHSIN_DVD)
    #include ".\\Customers\\YaHsin\\cfg_yahsin.h" 

#elif defined(APOLLO_DVD)
    #include ".\\Customers\\apollo\\cfg_apollo.h" 
       
#elif defined(ARLINK_DVD)
	#define ARLINK_8202D_DVD
	//#define ARLINK_8202D_16_DVD
	//#define ARLINK_8202D_16_040_DVD
	//#define ARLINK_8202S_DVD
	//#define ARLINK_8202S_16_DVD
	
	#ifdef ARLINK_8202S_DVD
		#include ".\\Customers\\arlink\\cfg_arlink_8202S.h"
	#elif defined(ARLINK_8202S_16_DVD)
		#include ".\\Customers\\arlink\\cfg_arlink_8202s_16.h"
	#elif defined(ARLINK_8202D_16_DVD)
		#include ".\\Customers\\arlink\\cfg_arlink_8202d_16.h"
	#elif defined(ARLINK_8202D_16_040_DVD)
		#include ".\\Customers\\arlink\\cfg_arlink_8202d_16_040.h"
	#elif defined(ARLINK_8202D_DVD)
		#include ".\\Customers\\arlink\\cfg_arlink_8202d.h"
	#else
	 	#include ".\\Customers\\arlink\\cfg_arlink.h"
	#endif
          
#elif defined(LUCKY_DVD)
#include ".\\Customers\\lucky\\cfg_lucky.h"


#elif defined(AVIQ_DVD)

//#define AVIQ_CARD
#define AVIQ_LINGFENG_DVD

#if defined(AVIQ_CARD)
    #include ".\\Customers\\AViQ\\cfg_aviq_card.h"
#elif defined(AVIQ_LINGFENG_DVD)
    #include ".\\Customers\\AViQ\\cfg_aviq_lingfeng.h"
#else
    #include ".\\Customers\\AViQ\\cfg_aviq.h"
#endif

#elif defined(SKYWORTH_DVD)

//#define SKYWORTH_DVD_CARD

#if defined(SKYWORTH_DVD_CARD)
    #include ".\\Customers\\SkyWorth\\cfg_skyworth_card.h"
#else
    #include ".\\Customers\\SkyWorth\\cfg_skyworth.h"
#endif

#elif defined(SKYTECH_DVD)
#include ".\\Customers\\skytech\\cfg_skytech.h"

#elif defined(FUDI_DVD)
#include ".\\Customers\\fudi\\cfg_fudi.h"

#elif defined(RONGXING_DVD)
#include ".\\Customers\\Rongxing\\cfg_rongxing.h"

#elif defined(FENGKAI_DVD)
#include ".\\Customers\\fengkai\\cfg_fengkai.h" //clead 2-12-3 16:20

#elif defined(ZIHUAN_DVD)
    
    //#define ZIHUAN_16_DVD
    //#define ZIHUAN_8202_DVD
    //#define ZIHUAN_8202S_DVD
   // #define ZIHUAN_8202D_DVD    
    //#define ZIHUAN_8202D_16_040_DVD
   //#define ZIHUAN_8202L_16_DVD
#define ZIHUAN_8202L_64_DVD

    #ifdef ZIHUAN_16_DVD
    #include ".\\Customers\\Zihuan\\cfg_16_zihuan.h"
#elif defined(ZIHUAN_8202D_DVD)
    #include ".\\Customers\\Zihuan\\cfg_zihuan_8202d.h"
#elif defined(ZIHUAN_8202D_16_DVD)
    #include ".\\Customers\\Zihuan\\cfg_zihuan_8202d_16.h"
#elif defined(ZIHUAN_8202D_16_040_DVD)
    #include ".\\Customers\\Zihuan\\cfg_zihuan_8202d_16_040.h"
#elif defined(ZIHUAN_8202_DVD)
    #include ".\\Customers\\Zihuan\\cfg_zihuan_8202.h"
#elif defined(ZIHUAN_8202S_DVD)
    #include ".\\Customers\\Zihuan\\cfg_zihuan_8202S.h"    
 #elif defined(ZIHUAN_8202L_16_DVD)
  #include ".\\Customers\\Zihuan\\cfg_zihuan_8202L_16.h"
 #elif defined(ZIHUAN_8202L_64_DVD)
   #include ".\\Customers\\Zihuan\\cfg_zihuan_8202L_64.h"
    #else//ZIHUAN_16_DVD
#include ".\\Customers\\Zihuan\\cfg_zihuan.h"
    #endif//ZIHUAN_16_DVD

#elif defined(VTREK_DVD)
#include ".\\Customers\\Vtrek\\cfg_vtrek.h"

#elif defined(HARMA_DVD)
#include ".\\Customers\\HARMA\\cfg_harma.h"

#elif defined(ACTIMA_DVD)        //2004-9-14 09:26zhangyu
    
    #define ACTIMA_16_DVD
    
    #ifdef ACTIMA_16_DVD
       #include ".\\Customers\\actima\\cfg_actima_16.h"
    #else   
       #include ".\\Customers\\actima\\cfg_actima.h"
    #endif
#elif defined(HANYANG_DVD)        //CAOH 2004-4-6 16:49

    //#define HANYANG_16_DVD
    //#define HANYANG_16_Japan_DVD
    //#define HANYANG_5CH_DVD
    //#define HANYANG_DP02CD_WF_8202S_16//added by wangwei,2005-2-4 10:14
    #define HANYANG_DP02CD_WG_8202S_16//added by wangwei,2005-3-14 22:17
    
    #ifdef HANYANG_16_Japan_DVD
    #include ".\\Customers\\hanyang\\cfg_hanyang_16_japan.h"
    #elif defined(HANYANG_16_DVD)
    #include ".\\Customers\\hanyang\\cfg_hanyang_16.h"
    #elif defined(HANYANG_8202s_16_DVD)
    #include ".\\Customers\\hanyang\\cfg_hanyang_8202s_16.h"
    #elif defined(HANYANG_5CH_DVD)
    #include ".\\Customers\\HANYANG\\cfg_HANYANG_5CH.h"
    #elif defined(HANYANG_DP02CD_WF_8202S_16)
    #include ".\\Customers\\HANYANG\\cfg_hanyang_dp02cd_wf_8202s_16.h"
    #elif defined(HANYANG_DP02CD_WG_8202S_16)
    #include ".\\Customers\\HANYANG\\cfg_hanyang_dp02cd_wg_8202s_16.h"
    #else//HANYANG_16_DVD
#include ".\\Customers\\HANYANG\\cfg_HANYANG.h"
    #endif//HANYANG_16_DVD

#elif defined(WYD_DVD)
#include ".\\Customers\\WYD\\cfg_WYD.h"

#elif defined(HONGTU_DVD)
#include ".\\Customers\\HONGTU\\cfg_HONGTU.h"

#elif defined(KENLOON_DVD)
#include ".\\Customers\\KENLOON\\cfg_KENLOON.h"

#elif defined(SZMALATA_DVD)
#include ".\\Customers\\SZMALATA\\cfg_szmalata.h"

#elif defined(MALATA_DVD)
#include ".\\Customers\\MALATA\\cfg_MALATA.h"

#elif defined(NEWFUSS_DVD)
#include ".\\Customers\\NEWFUSS\\cfg_NEWFUSS.h"

#elif defined(DESAY_DVD)
    //model name, choose one
    //---------------------
    //#define DS_N822_TYPE
    //#define DS_5715_TYPE
    #define DS_5763_TYPE
    //#define DS_16M_TYPE
    //#define DS_CONFIG_TYPE
    //---------------------
    
    #ifdef DS_N822_TYPE
    #include ".\\Customers\\Desay\\cfg_desay_N822.h"
    #elif defined(DS_5715_TYPE)
    #include ".\\Customers\\Desay\\cfg_desay_5715.h"
    #elif defined(DS_5763_TYPE)
        #include ".\\Customers\\Desay\\cfg_desay_5763.h"    
    #elif defined(DS_16M_TYPE)
        #include ".\\Customers\\Desay\\cfg_desay_16m.h" 
    #elif defined(DS_CONFIG_TYPE)
        #include ".\\Customers\\Desay\\cfg_desay_config.h"
    #else
#include ".\\Customers\\Desay\\cfg_desay.h"
    #endif


#elif defined(MINTON_DVD)

//#define MINTON_DVD_1001               //01x
//#define MINTON_DVD_501                //02x//dvd921
//#define MINTON_DVD_BOOMBOX            //04x//dvd301
//#define MINTON_DVD_009                //03x//dvd009
//#define MINTON_DVD_007                //05x//dvd007
//#define MINTON_YILI_DVD1003_2CH       //06x//dvd1003 2ch, 1 2M*16 sdram
//#define MINTON_YILI_DVD1003_6CH
//#define MINTON_YILI_LCD1003_6CH         //07x//dvd1003 5.1ch LCD panel
//#define MINTON_YILI_DVD1005_6CH
//#define MINTON_YILI_LCD127_6CH
//#define MINTON_YILI_LCD301_6CH
//#define MINTON_YILI_DVD381_6CH
//#define MINTON_YILI_LCD383_6CH
//#define MINTON_YILI_DVD921_6CH
//#define MINTON_16M
//#define MINTON_503
//#define MINTON_8202_601
//#define MINTON_YILI_8202S_16M
#define MINTON_YILI_8202S_32M



//#else #include ".\\Customers\\Minton\\cfg_minton.h"//00x

#ifdef MINTON_DVD_1001
#include ".\\Customers\\Minton\\cfg_minton_1001.h"
#elif defined(MINTON_DVD_501)
#include ".\\Customers\\Minton\\cfg_minton_501.h"
#elif defined(MINTON_DVD_BOOMBOX)
#include ".\\Customers\\Minton\\cfg_minton_boombox.h"
#elif defined(MINTON_DVD_009)
#include ".\\Customers\\Minton\\cfg_minton_009.h"
#elif defined(MINTON_DVD_007)
#include ".\\Customers\\Minton\\cfg_minton_007.h"

#elif defined(MINTON_YILI_DVD1001_2CH)
#include ".\\Customers\\Minton\\cfg_minton_dvd1001_2ch.h"
#elif defined(MINTON_YILI_DVD1001_6CH)
#include ".\\Customers\\Minton\\cfg_minton_dvd1001_6ch.h"
#elif defined(MINTON_YILI_DVD1003_2CH)
#include ".\\Customers\\Minton\\cfg_minton_dvd1003_2ch.h"
#elif defined(MINTON_YILI_DVD1003_6CH)
#include ".\\Customers\\Minton\\cfg_minton_dvd1003_6ch.h"
#elif defined(MINTON_YILI_LCD1003_6CH)
#include ".\\Customers\\Minton\\cfg_minton_lcd1003_6ch.h"
#elif defined(MINTON_YILI_DVD1005_6CH)
#include ".\\Customers\\Minton\\cfg_minton_dvd1005_6ch.h"
#elif defined(MINTON_YILI_LCD127_6CH)
#include ".\\Customers\\Minton\\cfg_minton_lcd127_6ch.h"
#elif defined(MINTON_YILI_LCD301_6CH)
#include ".\\Customers\\Minton\\cfg_minton_lcd301_6ch.h"
#elif defined(MINTON_YILI_DVD381_6CH)
#include ".\\Customers\\Minton\\cfg_minton_dvd381_6ch.h"
#elif defined(MINTON_YILI_LCD383_6CH)
#include ".\\Customers\\Minton\\cfg_minton_lcd383_6ch.h"
#elif defined(MINTON_YILI_DVD921_6CH)
#include ".\\Customers\\Minton\\cfg_minton_dvd921_6ch.h"
#elif defined(MINTON_16M)
#include ".\\Customers\\Minton\\cfg_minton_16m.h"
#elif defined(MINTON_503)
#include ".\\Customers\\Minton\\cfg_minton_503.h"
#elif defined(MINTON_8202_601)
#include ".\\Customers\\Minton\\cfg_minton_601.h"
#elif defined(MINTON_YILI_8202S_16M)
#include ".\\Customers\\Minton\\cfg_minton_8202s_16m.h"
#elif defined(MINTON_YILI_8202S_32M)
#include ".\\Customers\\Minton\\cfg_minton_8202s_32m.h"
#else
#include ".\\Customers\\Minton\\cfg_minton.h"
#endif

#elif defined(IDALL_DVD)
#include ".\\Customers\\IDall\\cfg_idall.h"

#elif defined(EASTECH_DVD)
    //#define EASTECH_DVD_TOP_DOOR_LOADER  //wsf  2004-5-8 15:57
    //#define EASTECH_DVD_TOP_DOOR_LOADER_2031	//liumzh 2004-9-8 22:04
    //#define EASTECH_DVD_SHARP	
    //#define EASTECH_DVD_3240
    //#define EASTECH_DVD_3180
    //#define EASTECH_DVD_3170
    #define EASTECH_DVD_DP3240_D
    //#define EASTECH_DVD_DP2070_D

    
    #ifdef EASTECH_DVD_TOP_DOOR_LOADER
        #include ".\\Customers\\EASTECH\\cfg_eastech_top_loader.h"
    #elif defined(EASTECH_DVD_TOP_DOOR_LOADER_2031)
        #include ".\\Customers\\EASTECH\\cfg_eastech_top_loader_2031.h"
    #elif defined(EASTECH_DVD_SHARP)
        #include ".\\Customers\\EASTECH\\cfg_eastech_sharp.h"
    #elif defined(EASTECH_DVD_3240)
        #include ".\\Customers\\EASTECH\\cfg_eastech_3240.h"
    #elif defined(EASTECH_DVD_3180)
        #include ".\\Customers\\EASTECH\\cfg_eastech_3180.h"
    #elif defined(EASTECH_DVD_3170)
        #include ".\\Customers\\EASTECH\\cfg_eastech_3170.h"
    #elif defined(EASTECH_DVD_DP3240_D)
    	#include ".\\Customers\\EASTECH\\cfg_eastech_dp3240_d.h"
    #elif defined(EASTECH_DVD_DP2070_D)
    	#include ".\\Customers\\EASTECH\\cfg_eastech_dp2070_d.h"
    #else
		#include ".\\Customers\\EASTECH\\cfg_eastech.h"
    #endif

#elif defined(EVERSTAR_DVD)
#include ".\\Customers\\everstar\\cfg_everstar.h"

#elif defined(GENTEK_DVD)
#include ".\\Customers\\Gentek\\cfg_gentek.h"

#elif defined(JIEKE_DVD)
    #include ".\\Customers\\jieke\\cfg_jieke.h"

#elif defined(JIEKE_16M_DVD)            //clead 
        #include ".\\Customers\\jieke\\cfg_jieke_16m.h"

#elif defined(JUNYUAN_DVD)              //lizhx
        #include ".\\Customers\\Junyuan\\cfg_junyuan.h"

#elif defined(HUIFENGYUAN_DVD)
    #include ".\\Customers\\HuiFengYuan\\cfg_huifengyuan.h"

#elif defined(HENGCHEN_DVD)
    #include ".\\Customers\\HengChen\\cfg_hengchen.h"
    
#elif defined(YADAI_DVD)

    //#define YADAI_16_DVD
        //#define SHANGGUANGDIAN_DVD
    #ifdef YADAI_16_DVD
    #include ".\\Customers\\Yadai\\cfg_yadai_8202_16.h"
    #elif defined(SHANGGUANGDIAN_DVD)
    #include ".\\Customers\\Yadai\\cfg_shangguangdian.h"
    #else 
    #include ".\\Customers\\Yadai\\cfg_yadai_8202.h"
    #endif
    
#elif defined(XUKE_DVD)
    #include ".\\Customers\\Xuke\\cfg_xuke.h"

#elif defined(WEICHENG_DVD)
    #include ".\\Customers\\weicheng\\cfg_weicheng.h"
    
#elif defined(GBM_PORTABLE_DVD)
    #include ".\\Customers\\Gbm_portable\\cfg_gbmportable.h"

#elif defined(SYBER_DVD)
    //#include ".\\Customers\\SYBER\\cfg_syber.h"
    #include ".\\Customers\\SYBER\\cfg_syber_16.h"

#elif defined(SHIDELI_DVD)                      //gerry,2004-4-21 13:01
    #include ".\\Customers\\SHIDELI\\cfg_shideli.h"

#elif defined(ARGUS_PORTABLE_DVD)
    #include ".\\Customers\\Argus_portable\\cfg_argusportable.h"

#elif defined(TEAC_PORTABLE_DVD)//TEAC
    #include ".\\Customers\\teac_portable\\cfg_teac_portable.h"

#elif defined(QSI_PORTABLE_DVD)                      //gerry,2004-4-21 13:01
    #include ".\\Customers\\Qsi_portable\\cfg_qsiportable.h"
    
#elif defined(JENGYANG_DVD)                //liulifeng 2004-8-5 9:36
    #include ".\\Customers\\JENGYANG\\cfg_jengyang.h"

#elif defined(ETON_DVD)                     //liweihua 2004-9-9 10:37
    //#define ETON_DVD_8M
    //#define ETON_DVD_TUNER
    //#define ETON_16_DVD//liweihua add 2004-12-21
    
    #ifdef ETON_DVD_TUNER
        #include ".\\Customers\\Eton\\cfg_eton_tuner.h"
    #elif defined(ETON_DVD_8M)
        #include ".\\Customers\\Eton\\cfg_eton_ch.h" 
    #elif defined(ETON_16_DVD) 
        #include ".\\Customers\\Eton\\cfg_eton_16.h"  
    #else
        #include ".\\Customers\\Eton\\cfg_eton.h"
    #endif

#elif defined(JIANLOON_DVD)     //liych  added 2005-3-23
   // #define JIANLOON_DVD_8202
   // #define JIANLOON_DVD_8202D
   // #define JIANLOON_DVD_8202E
    #define JIANLOON_DVD_8202S
   
    #if defined(JIANLOON_DVD_8202)
    #include ".\\Customers\\JIANLOON\\cfg_JianLoon_8202.h"   
    #elif defined(JIANLOON_DVD_8202S)
    #include ".\\Customers\\JIANLOON\\cfg_JianLoon_8202S.h"
    #endif
    
#elif defined(THAKRAL_DVD)                //suqiaoli 2004-9-13 
    //#define SHARP_MODE
    //#define APEX_MODE
    //#define DIXON_MODE
    //#define DIXON_AMP_MODE
    //#define THAKRAL_8202//liweihua 2005-3-4 9:10
    
    #if defined(SHARP_MODE)
    #include ".\\Customers\\thakral\\cfg_thakral_sharp.h"   
    #elif defined(APEX_MODE)
    #include ".\\Customers\\thakral\\cfg_thakral_apex.h"
    #elif defined(DIXON_MODE)
    #include ".\\Customers\\thakral\\cfg_thakral_dixon.h"
    #elif defined(DIXON_AMP_MODE)
    #include ".\\Customers\\thakral\\cfg_thakral_dixon_amp.h"
    #elif defined(THAKRAL_8202)
    #include ".\\Customers\\thakral\\cfg_customers.h"
    #else
    #include ".\\Customers\\thakral\\cfg_thakral.h"   
    #endif
    
#elif defined(WINGSUM_DVD)
    //#define WINGSUM_2CH_DVD
    //#define WINGSUM_51CH_DVD    
    #define WINGSUM_TVCOMBO
    
    #if defined(WINGSUM_2CH_DVD)
    #include ".\\Customers\\wingsum\\cfg_wingsum_2ch.h"
    #elif defined(WINGSUM_51CH_DVD)
    #include ".\\Customers\\wingsum\\cfg_wingsum_51ch.h"
    #elif defined(WINGSUM_TVCOMBO)
    #include ".\\Customers\\wingsum\\cfg_wingsum_tvcombo.h"
    #endif

#elif defined(SHINCO_DVD)
    #define VER_8202S
    //#define VER_8202D
    #if defined(VER_8202S)
    #include ".\\Customers\\shinco\\cfg_shinco_s.h"
    #elif defined(VER_8202D)
    #include ".\\Customers\\shinco\\cfg_shinco_d.h"
    #endif
    
#elif defined(PHILIPS_DVD)
    #include ".\\Customers\\philips\\cfg_philips_8202d.h"
    
#elif defined(MALATA_GPS_DVD)
	#include ".\\Customers\\MALATA_GPS_DVD\\cfg_malata_gps_dvd.h"
	
#elif defined(MALATA_PORTABLE_DVD)
    #define MALATA_PORTABLE_DVBT
    
    #if defined(MALATA_PORTABLE_DVBT)
    #include ".\\Customers\\malata_portable\\cfg_malata_portable_8202d_dvb.h"
    #endif

#elif defined(ALCO_DVD)   
    //#define ALCO_8200_PORTABLE_DVD    //8200+2Mx16 SDRAM 
    //#define ALCO_8200_16M_PORTABLE_DVD    //8200+1Mx16 SDRAM
    //#define ALCO_8202S_PORTABLE_DVD     //8202s+2Mx16 SDRAM 
    //#define ALCO_8202S_16M_PORTABLE_DVD   //8202s+1Mx16 SDRAM 
    //#define ALCO_8202D_16M_PORTALBE_DVD
    //#define ALCO_PORTABLE_DVD_8202D_DVB
      #define ALCO_8202L_16M_PORTALBE_DVD
      //#define ALCO_8202L_64M_PORTALBE_DVD
    
    #if defined(ALCO_8200_16M_PORTABLE_DVD) 
    #include ".\\Customers\\Alco_portable\\cfg_alco_pdvd16.h"       
    #elif defined(ALCO_PORTABLE_DVD_8202D_DVB)
    #include ".\\Customers\\Alco_portable\\cfg_alco_portable_8202d_dvb.h" 
    #elif defined(ALCO_8202S_PORTABLE_DVD) 
    #include ".\\Customers\\Alco_portable\\cfg_alco_8202s_pdvd.h"
    #elif defined(ALCO_8202S_16M_PORTABLE_DVD) 
    #include ".\\Customers\\Alco_portable\\cfg_alco_8202s_pdvd16.h"
    #elif defined(ALCO_8202D_16M_PORTALBE_DVD) 
    #include ".\\Customers\\Alco_portable\\cfg_alco_8202d_pdvd16.h"
    #elif defined(ALCO_8202L_16M_PORTALBE_DVD) 
    #include ".\\Customers\\Alco_portable\\cfg_alco_8202L_pdvd16.h"
    #elif defined(ALCO_8202L_64M_PORTALBE_DVD) 
    #include ".\\Customers\\Alco_portable\\cfg_alco_8202L_pdvd64.h"
    #else
    #include ".\\Customers\\Alco_portable\\cfg_alco_portable.h"
    #endif
    
#elif defined(HUALU_DVD) 
    #define HUALU_8202L_318AL   // lxg add 2006-7-18 09:34
    
    #if defined(HUALU_8202L_318AL) 
    #include ".\\Customers\\hualu\\cfg_hualu_8202l_318al_16.h" 
    #endif
    
#elif defined(GOWELLENT_DVD)
    #define GOWELLENT_8202L_16M_DVD
    //#define GOWELLENT_8202L_64M_DVD
    //#define GOWELLENT_8202D_16M_DVD
    //#define GOWELLENT_8202D_32M_DVD
    
    #if defined(GOWELLENT_8202L_16M_DVD)
    #include ".\\Customers\\Gowellent\\cfg_Gowellent_8202L_16.h"
    #elif define(GOWELLENT_8202L_64M_DVD)
    #include ".\\Customers\\Gowellent\\cfg_gowellent_8202L_64.h"
    #else
    #include ".\\Customers\\Gowellent\\cfg_gowellent_8202D.h"
    #endif
    
#endif



/*====================================================================
*  Customerize define ,move to cust_def.h
*  Terry,2003/9/15 03:30PM
*=====================================================================*/
#include "cust_def.h"



#endif //__USER_INIT_H







