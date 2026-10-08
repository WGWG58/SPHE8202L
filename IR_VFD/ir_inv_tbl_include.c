//nono split from ir_parser.c 5-5-9 15:07

#if defined(GENERAL_DVD) 
    #if  MAX_FULL_PAGE==16
        #include ".\\Customers\\general\\inv_tbl_fullosd.h"
    #else
    #include ".\\Customers\\general\\inv_tbl.h"
    #endif
#elif defined(YUXING_DVD)
    #if  MAX_FULL_PAGE==16
        #include ".\\Customers\\yuxing\\inv_tbl_fullosd.h"
    #else
    	#include ".\\Customers\\yuxing\\inv_tbl.h"
    #endif
#elif defined(YUXING_MIDI_DVD)                      //add by xlluo 04-6-11 need build ??
    #include ".\\Customers\\Yuxing\\inv_tbl.h"
#elif defined(SANJING_MIDI_DVD)                 
    #include ".\\Customers\\Sanjing\\inv_tbl.h"
#elif defined(YANGYU_DVD)	//yaowh add 2005-10-12 11:42
    #if  MAX_FULL_PAGE==16
        #include ".\\Customers\\yangyu\\inv_tbl_fullosd.h"
    #else
		#include ".\\Customers\\yangyu\\inv_tbl.h"
    #endif
#elif defined(ARLINK_DVD)	//yaowh add 2005-10-12 11:42
    #if  MAX_FULL_PAGE==16
		#include ".\\Customers\\arlink\\inv_tbl_fullosd.h"
    #else
		#include ".\\Customers\\arlink\\inv_tbl.h"
    #endif
#elif defined(BBK_DVD)
    #include ".\\Customers\\Bbk\\inv_tbl_bbk.h"
#elif defined(AKI_DVD)
    #include ".\\Customers\\Aki\\inv_tbl_aki.h"
#elif defined(APEX_DVD)
    #include ".\\Customers\\Apex\\inv_tbl_apex.h"
#elif defined(ATLAS_DVD)
    #include ".\\Customers\\Atlas\\inv_tbl_atlas.h"
#elif defined(SMT_DVD)
    #include ".\\Customers\\Smt\\inv_tbl_smt.h"
#elif defined(FUSS_DVD)
    #include ".\\Customers\\Fuss\\inv_tbl_fuss.h"
#elif defined(YADAI_DVD)
     #ifdef SHANGGUANGDIAN_DVD
     #include ".\\Customers\\Yadai\\inv_tbl_shangguangdian.h"
     #else
    #include ".\\Customers\\Yadai\\inv_tbl_yadai.h"
     #endif
#elif defined(HUAJIA_DVD)
    #include ".\\Customers\\Huajia\\inv_tbl_huajia.h"    
#elif defined(HUALU_DVD)
    #include ".\\Customers\\hualu\\inv_tbl_fullosd.h"   
#elif defined(INTECH_DVD)
    #include ".\\Customers\\Intech\\inv_tbl_fullosd.h"    
#elif defined(JCG_DVD)
    #include ".\\Customers\\Jcg\\inv_tbl_jcg.h"    
#elif defined(SVA_DVD)
        #include ".\\Customers\\Sva\\inv_tbl_sva.h"
#elif defined(KONKA_DVD)
    #include ".\\Customers\\Konka\\inv_tbl_konka.h"    
#elif defined(GBM_DVD)
    #include ".\\Customers\\Gbm\\inv_tbl_gbm.h"    
#elif defined(GBM_AP_DVD)
    #include ".\\Customers\\Gbm_ap\\inv_tbl_gbm.h"    
#elif defined(GBM_PORTABLE_DVD) 
    #include ".\\Customers\\Gbm_portable\\inv_tbl_gbmportable.h"
#elif defined(HOBO_DVD)
    #include ".\\Customers\\Hobo\\inv_tbl_hobo.h"    
#elif defined(BMT_DVD)
    #include ".\\Customers\\bmt\\inv_tbl_bmt.h"    
#elif defined(SUOJIA_DVD)
    #include ".\\Customers\\suojia\\inv_tbl_suojia.h"    
#elif defined(OUR_MIND_DVD)
    #include ".\\Customers\\ourmind\\inv_tbl_ourmind.h"    
#elif defined(WEIKING_DVD_AMP)
    #include ".\\Customers\\weiking\\inv_tbl_weiking.h"   
#elif defined(APOLLO_DVD)
    #include ".\\Customers\\apollo\\inv_tbl_apollo.h"
#elif defined(CONSER_DVD)
    #include ".\\Customers\\Conser\\inv_tbl_conser.h"
#elif defined(PROVIEW_DVD)
    #include ".\\Customers\\Proview\\inv_tbl_proview.h"
#elif defined(CNMOTOR_DVD)
    #include ".\\Customers\\Cnmotor\\inv_tbl_cnmotor.h"   
#elif defined(AVIQ_DVD)
    #include ".\\Customers\\AViQ\\inv_tbl_aviq.h"   
#elif defined(FUDI_DVD)
    #include ".\\Customers\\fudi\\inv_tbl_fudi.h"   
#elif defined(GAODASI_DVD)
    #include ".\\Customers\\Gaodasi\\inv_tbl_gaodasi.h"    
#elif defined(QISHENG_DVD)
//#ifdef NEWSTYLE_WINDOW
        #include ".\\Customers\\QiSheng\\inv_tbl_qisheng1.h"
//#else
//#include ".\\Customers\\QiSheng\\inv_tbl_qisheng.h"
//#endif
#elif defined(SAMBOO_HDDPLAYER_DVD)////////YANGLI2005/8/17
    #include ".\\Customers\\samboo\\inv_tbl_samboo.h"

#elif defined(YAHSIN_DVD)
    #include ".\\Customers\\YaHsin\\inv_tbl_yahsin.h"
#elif defined(SKYWORTH_DVD)
    #include ".\\Customers\\SkyWorth\\inv_tbl_skyworth.h"
#elif defined(ZIHUAN_DVD)
    #include ".\\Customers\\Zihuan\\inv_tbl_zihuan.h"
#elif defined(MICO_DVD)
    #include ".\\Customers\\MICO\\inv_tbl_mico.h"
#elif defined(KSD_DVD)
    #include ".\\Customers\\trenddigit\\inv_tbl_ksd.h"
#elif defined(ZHAOCHI_DVD)   //LYC 2005-04-04
    #if defined(MTC_PORTABLE_DVB_8202D_6600)||defined(MTC_DVD_DVB_8202D_6600)  ////yangli add for 8202D+dvb,2005-11-10 16:21
    #include ".\\Customers\\ZHAOCHI\\inv_tbl_mtc_dvb.h"   
    #elif defined(SCALER_6500) // FanGang added for mtc HDMI model,2005-11-11 14:33
         #if MAX_FULL_PAGE==16
             #include ".\\Customers\\ZHAOCHI\\inv_tbl_mtc_6500_fullosd.h"
         #else
             #include ".\\Customers\\ZHAOCHI\\inv_tbl_mtc_6500.h"  
         #endif    
      #else
      
         #include ".\\Customers\\ZHAOCHI\\inv_tbl_zhaochi.h"   
    #endif
#elif defined(DESAY_DVD)
    #include ".\\Customers\\Desay\\inv_tbl_desay.h"
#elif defined(MINTON_DVD)
#ifdef MINTON_YILI_DVD1003_2CH
    #include ".\\Customers\\Minton\\inv_tbl_minton_dvd1003.h"
#else
    #include ".\\Customers\\Minton\\inv_tbl_minton.h"
#endif
#elif defined(EASTECH_DVD)    //2004-4-2 1:36  wsf
    #ifdef EASTECH_DVD_SHARP
        #include ".\\Customers\\EASTECH\\inv_tbl_eastech_sharp.h" 
    #elif defined(EASTECH_DVD_PHILIPS)
        #include ".\\Customers\\EASTECH\\inv_tbl_eastech_philips.h"
    #else
        #include ".\\Customers\\EASTECH\\inv_tbl_eastech_top.h" 
    #endif 
#elif defined(EVERSTAR_DVD)
    #include ".\\Customers\\everstar\\inv_tbl_everstar.h"
#elif defined(IDALL_DVD)
    #include ".\\Customers\\Idall\\inv_tbl_idall.h"
#elif defined(VTREK_DVD)
    #include ".\\Customers\\Vtrek\\inv_tbl.h"
#elif defined(LINKCONCEPT_DVD)
    #include ".\\Customers\\linkconcept\\inv_tbl_linkconcept.h"
#elif defined(GENTEK_DVD)
    #include ".\\Customers\\Gentek\\inv_tbl_gentek.h"
#elif defined(HARMA_DVD)
    #include ".\\Customers\\HARMA\\inv_tbl.h"
#elif defined(WYD_DVD)
    #include ".\\Customers\\WYD\\inv_tbl.h"
#elif defined(ACTIMA_DVD)   //2004-9-14 09:25?宇M
    #include ".\\Customers\\ACTIMA\\inv_tbl.h"
#elif defined(HONGTU_DVD)   //2003-11-25 03:59张宇P
    #include ".\\Customers\\HONGTU\\inv_tbl.h"
#elif defined(KENLOON_DVD)   //2004-4-14 11:35张宇M
    #include ".\\Customers\\KENLOON\\inv_tbl.h"
#elif defined(SZMALATA_DVD)   //2004-2-3 01:20张宇P
    #include ".\\Customers\\SZMALATA\\inv_tbl.h"
#elif defined(TONIC_DVD)   //2004-2-3 01:20张宇P
    #include ".\\Customers\\TONIC\\inv_tbl.h"
#elif defined(MALATA_DVD)   //2003-11-25 03:59张宇P
    #include ".\\Customers\\MALATA\\inv_tbl.h"
#elif defined(NEWFUSS_DVD)   //2003-11-25 03:59张宇P
    #include ".\\Customers\\NEWFUSS\\inv_tbl.h"
#elif defined(JIANLOON_DVD)//zxb 2005-5-8 12:17
	#include ".\\Customers\\JIANLOON\\inv_tbl_JianLoon.h"    
#elif defined(TIANKE_DVD)
    #include ".\\Customers\\TIANKE\\inv_tbl.h"
#elif defined(WEICHENG_DVD)
    #include ".\\Customers\\weicheng\\inv_tbl_sunplus.h"
#elif defined(JIEKE_DVD)
    #include ".\\Customers\\jieke\\inv_tbl_jieke.h"
#elif defined(JIEKE_16M_DVD)
    #include ".\\Customers\\jieke\\inv_tbl_jieke.h"
#elif defined(XUKE_DVD)
    #include ".\\Customers\\xuke\\inv_tbl_xuke.h"
#elif defined(ZhengTai_DVD)
    #include ".\\Customers\\ZhengTai\\inv_tbl_zhengtai.h"
#elif defined(SKYTECH_DVD)
    #include ".\\Customers\\skytech\\inv_tbl_skytech.h"
#elif defined(XINDE_DVD)
    #include ".\\Customers\\xinde\\inv_tbl_xinde.h"    
#elif defined (ORIENTPOWER_DVD)
    #if  MAX_FULL_PAGE==16
        #include ".\\Customers\\Orientpower\\inv_tbl_fullosd.h"
    #else
        #include ".\\Customers\\Orientpower\\inv_tbl.h"
    #endif

#elif defined(ORITRON_DVD)
    #if MAX_FULL_PAGE==16//zhoulin add 
        #include ".\\Customers\\oritron\\inv_tbl_fullosd_ori.h"
    #else
    #include ".\\Customers\\oritron\\inv_tbl_oritron.h"
    #endif
#elif defined(THAKRAL_DVD)   
    #include ".\\Customers\\thakral\\inv_tbl_thakral.h" 
#elif defined(WINGSUM_DVD)
    #include ".\\Customers\\wingsum\\inv_tbl_wingsum.h"
   
#elif defined(ORITRON_HK_DVD)//lijd 2005-5-8 16:31
    #if defined(ORITRON_8202S_2X16_16BIT_DVD)       
    	#include ".\\Customers\\HK_Oritron\\inv_tbl_oritron_8202S_2X16_16.h"
    #elif defined(ORITRON_8202S_1X16_16BIT_DVD) 
    	#include ".\\Customers\\HK_Oritron\\inv_tbl_oritron_8202S_1X16_16.h"
    #elif defined(ORITRON_8202D_2X16_16BIT_DVD) 
    	#include ".\\Customers\\HK_Oritron\\inv_tbl_oritron_8202D_2X16_16.h"
    #elif defined(ORITRON_8202D_1X16_16BIT_DVD) 
    	#include ".\\Customers\\HK_Oritron\\inv_tbl_oritron_8202D_1X16_16.h"	
    #elif defined(ORITRON_8202D_3111_DVD)
   		#include ".\\Customers\\HK_Oritron\\inv_tbl_oritron_8202D_1X16_16.h"
   	#elif defined(ORITRON_8202D_4110_DVD)
   		#include ".\\Customers\\HK_Oritron\\inv_tbl_oritron_8202D_1X16_16.h"
    #elif defined(ORITRON_8202D_4119_DVD)
   	#include ".\\Customers\\HK_Oritron\\inv_tbl_oritron_8202D_1X16_16.h"	
   	#elif defined(ORITRON_8202D_4125_DVD)
   		#include ".\\Customers\\HK_Oritron\\inv_tbl_oritron_8202D_2X16_16.h"
    #elif defined(ORITRON_8202D_4127_DVD)
   	#include ".\\Customers\\HK_Oritron\\inv_tbl_oritron_8202D_1X16_16.h"
   	#elif defined(ORITRON_8202D_5112_DVD)
   		#include ".\\Customers\\HK_Oritron\\inv_tbl_oritron_8202D_1X16_16.h"
   	#elif defined(ORITRON_8202D_5115_DVD)
   		#include ".\\Customers\\HK_Oritron\\inv_tbl_oritron_8202D_1X16_16.h"	
    #elif defined(ORITRON_8202D_5116_DVD)
   	#include ".\\Customers\\HK_Oritron\\inv_tbl_oritron_8202D_1X16_16.h"
    #elif defined(ORITRON_8202D_5117_DVD)
   	#include ".\\Customers\\HK_Oritron\\inv_tbl_oritron_8202S_2X16_16.h"
    #elif defined(ORITRON_8202D_5121_DVD)
   	#include ".\\Customers\\HK_Oritron\\inv_tbl_oritron_8202D_2X16_16.h"	
    #elif defined(ORITRON_8202D_5122_DVD)
   	#include ".\\Customers\\HK_Oritron\\inv_tbl_oritron_8202D_2X16_16.h"		
   	#elif defined(ORITRON_8202D_6122_DVD)
   	#include ".\\Customers\\HK_Oritron\\inv_tbl_oritron_8202D_2X16_16.h"		
    #endif

#elif defined(HK_ORITRON_DVD_RECEIVER)   //hongfeng 2005-07-09
    #if defined(ORITRON_RECEIVER_6001)       
    	#include ".\\Customers\\Oritron\\inv_tbl_oritron_receiver_6001.h"
    #elif defined(ORITRON_RECEIVER_6008) 
    #include ".\\Customers\\Oritron\\inv_tbl_oritron_receiver_6008.h"    
    #elif defined(ORITRON_RECEIVER_6505) 
    #include ".\\Customers\\Oritron\\inv_tbl_oritron_receiver_6505.h"
    #elif defined(ORITRON_RECEIVER_5003) 
    #include ".\\Customers\\Oritron\\inv_tbl_oritron_receiver_5003.h"    
    #elif defined(ORITRON_RECEIVER_DPL937) 
    #include ".\\Customers\\Oritron\\inv_tbl_oritron_receiver_dpl937.h"  
    #endif    
#elif defined(SHINCO_DVD)
    #include ".\\Customers\\shinco\\inv_tbl_shinco.h"
#elif defined(SYBER_DVD)
    #include ".\\Customers\\SYBER\\inv_tbl_syber.h"
#elif defined(XINGQIU_DVD)
    #include ".\\Customers\\Xingqiu\\inv_tbl_xingqiu.h"
#elif defined(NINTAUS_DVD)   
    #include ".\\Customers\\nintaus\\inv_tbl_nintaus.h"
#elif defined(HANYANG_DVD)   
    #include ".\\Customers\\hanyang\\inv_tbl_hanyang.h"
#elif defined(ARGUS_PORTABLE_DVD)
    #include ".\\Customers\\argus_portable\\inv_tbl_argusportable.h"
#elif defined(SHIDELI_DVD)   
    #include ".\\Customers\\shideli\\inv_tbl_shideli.h"     //gerry,2004-4-22 16:09
#elif defined(TEAC_PORTABLE_DVD)//TEAC   
    #include ".\\Customers\\teac_portable\\inv_tbl_teac.h"  
#elif defined(EASTWIN_PORTABLE_DVD)
    #if  MAX_FULL_PAGE==16
        #include ".\\Customers\\Eastwin\\inv_tbl_eastwin_fullosd.h"
    #else   
            #include ".\\Customers\\Eastwin\\inv_tbl_eastwin.h"
        #endif  

#elif defined(HONEYWLD_DVD)
    #if  MAX_FULL_PAGE==16
        #include ".\\Customers\\HoneyWld\\inv_tbl_fullosd.h"
    #else   
        #include ".\\Customers\\HoneyWld\\inv_tbl.h" //this path now
    #endif  
		
#elif defined (MALATA_GPS_DVD)//frank.huang 050928
    #if  MAX_FULL_PAGE==16
        #include ".\\Customers\\MALATA_GPS_DVD\\inv_tbl_fullosd.h"
    #else
        #include ".\\Customers\\MALATA_GPS_DVD\\inv_tbl.h"
    #endif
		
#elif defined(MUSTEK_K100D_MODEL)
    #if  MAX_FULL_PAGE==16
        #include ".\\Customers\\Mustek_portable\\inv_tbl_k100d_fullosd.h"
    #else
        #include ".\\Customers\\Mustek_portable\\inv_tbl_k100d.h"
    #endif

#elif defined(ALCO_DVD) 
    #ifdef  DIVX_DRM//shenyj modify 2006-8-24 02:01下午
        	#include ".\\customers\\Alco_portable\\inv_tbl_alco_portable_divx.h"
    	#else
        	#include ".\\customers\\Alco_portable\\inv_tbl_alco_portable.h"     
        #endif
	#else

//#ifdef NEWSTYLE_WINDOW//terry,mark it,2003/7/30 04:32PM
//    #include ".\\Customers\\Sunplus\\inv_tbl_newgoto.h"
//#else
    #if  MAX_FULL_PAGE==16
        #include ".\\Customers\\Sunplus\\inv_tbl_fullosd.h"
    #else
        #include ".\\Customers\\Sunplus\\inv_tbl.h"
    #endif

#endif


