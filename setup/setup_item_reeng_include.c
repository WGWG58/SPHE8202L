//nono split from setup_item.c 5-5-9 15:07
//=================================================================
//for DVD setup menu reengineering  //added by JS   //20040728

#ifdef GENERAL_DVD
    #if defined(GENERAL_32_DVD)||defined(GENERAL_8202S_DVD)||defined(GENERAL_16_DVD)||defined(GENERAL_8202S_16_DVD)||defined(GENERAL_8202E_DVD)||defined(GENERAL_8202M_A_DVD)
        #include ".\\Customers\\general\\setup_menu_general.c"
    #elif defined(GENERAL_8202D_DVD)||defined(GENERAL_8202D_16_DVD)||defined(GENERAL_8202D_16_040_NO_MP4)||defined(GENERAL_8202D_16_040_DVD)||defined(GENERAL_8202A256_DVB)||defined(GENERAL_8202D_DVB)||defined(GENERAL_8202M_B_DVD)||defined(GENERAL_PORTABLE_DVD_8202D)||defined(GENERAL_PORTABLE_DVD_8202D_DVB)
        #include ".\\Customers\\general\\setup_menu_general_8202d.c"
    #elif defined(GENERAL_8202L_16_DVD)||defined(GENERAL_8202L_64_DVD)||defined(GENERAL_8202L_16_040_DVD)||defined(GENERAL_8202L_16_040_NO_MP4)||defined(GENERAL_8202L_32_DVD)
        #include ".\\Customers\\general\\setup_menu_general_8202d.c"
    #endif
#endif

#ifdef SUNPLUS_DVD
    #if defined(SUPPORT_TVG)      // 2005/03/29 yltseng
        #include ".\\Customers\\Sunplus\\setup_menu_sunplus_TVG.c"
    #elif defined(CUSTOMERS_DVD)||defined(CUSTOMERS_8202S_DVD)||defined(CUSTOMERS_16_DVD)||defined(CUSTOMERS_8202S_16_DVD) || defined(BOOT_LOAD_CODE)||defined(CUSTOMERS_8202A_256_DVD)
        #ifdef SUPPORT_RECEIVER//2005/05/11 chenzhao
        #include ".\\Customers\\Sunplus\\setup_menu_sunplus_receiver.c"
        #else
        #include ".\\Customers\\Sunplus\\setup_menu_sunplus.c"
        #endif
    #elif defined(CUSTOMERS_8202D_DVD) ||defined(CUSTOMERS_8202D_256_DVD)|| defined(CUSTOMERS_8104_CD)|| defined(CUSTOMERS_PORTABLE_DVD_8202D)|| defined(CUSTOMERS_8202L_32_DVD)|| defined(CUSTOMERS_8202L_64_DVD) || defined(CUSTOMERS_PORTABLE_DVD_8202L_64)
        #ifdef SUPPORT_RECEIVER_TEST//2005/05/11 chenzhao
        #include ".\\Customers\\Sunplus\\setup_menu_sunplus_8202D_receiver.c"
        #else
        #include ".\\Customers\\Sunplus\\setup_menu_sunplus_8202D.c"
        #endif
    #elif defined(CUSTOMERS_8202D_16_DVD)||defined(CUSTOMERS_8202D_16_040_DVD)||defined(CUSTOMERS_8104_16_CD)||defined(CUSTOMERS_8202D_16_040_NO_MP4)||defined(CUSTOMERS_8202L_16_DVD)||defined(CUSTOMERS_8202L_16_040_DVD)||defined(CUSTOMERS_8202L_16_040_NO_MP4) //terry,2005/6/22 10:24¤U¤È
        #include ".\\Customers\\Sunplus\\setup_menu_sunplus_8202D_16.c"        
    #elif defined(CUSTOMERS_PORTABLE_DVD) 
        #include ".\\Customers\\Sunplus\\setup_menu_sunplus.c"
    #elif defined(SUNPLUS_8202A256_DVB)||defined(CUSTOMERS_PORTABLE_DVD_8202D_DVB)||defined(SUNPLUS_8202D_DVB)
			#include ".\\Customers\Sunplus\\setup_menu_sunplus_8202D.c"
    #elif defined(CF_HDD_PMP)||defined(HDD_PLAYER_V01)
            #include ".\\Customers\\Sunplus\\setup_menu_sunplus.c"
    #elif defined(CUSTOMERS_8202M_DVD)
			#include ".\\Customers\Sunplus\\setup_menu_sunplus_8202M.c"
    #elif defined(CUSTOMERS_8202E_DVD)
			#include ".\\Customers\Sunplus\\setup_menu_sunplus_8202E.c"
	#elif defined(CUSTOMERS_1002_16_DVD)
		#include ".\\Customers\\Sunplus\\setup_menu_sunplus_8202D_16.c"
    #endif
#endif

#ifdef HUALU_DVD  // lxg 2006-7-18 09:50ÏÂÎç
#include ".\\Customers\\hualu\\setup_menu_hualu_8202D_16.c" 
#endif

#if defined(INTECH_8202L_16_DVD)||defined(INTECH_8202L_64_DVD)
#include ".\\Customers\\intech\\setup_menu_intech_8202L_16.c"
#endif

#ifdef ZHAOCHI_DVD          //////////yangli add for 8202D+dvb,2005-11-10 16:22
    #if defined(MTC_PORTABLE_DVB_8202D_6600)||defined(MTC_DVD_DVB_8202D_6600)
    #include ".\\Customers\\ZHAOCHI\\setup_menu_mtc_8202d_dvb.c" 
    #elif defined(SCALER_6500)
    #include ".\\Customers\\ZHAOCHI\\setup_menu_MTC_8202d_6500.c"
    #endif 
#endif


#ifdef MUSTEK_PORTABLE_DVD
    #ifdef MUSTEK_K100D_MODEL
    #include ".\\Customers\mustek_portable\\setup_menu_mustek_K100D.c"
    #else
    #include ".\\Customers\\mustek_portable\\setup_menu_mustek.c"
#endif        	
#endif        	
        	
#if defined(TEAC_PORTABLE_DVD)//TEAC 
    #include ".\\Customers\\teac_portable\\setup_menu_teac.c"
#endif

	#if defined(JIANLOON_DVD)// uu
			#include ".\\Customers\\JianLoon\\setup_menu_jianloon.c"
	#endif
	
#if defined(QSI_PORTABLE_DVD) 
    #include ".\\Customers\\Qsi_portable\\setup_menu_QSI.c"
#endif

#if defined(THAKRAL_DVD)&&defined(SHARP_MODE)
    #include ".\\Customers\\thakral\\setup_menu_sharp.c"
#elif defined(THAKRAL_DVD)&&defined(APEX_MODE)
    #include ".\\Customers\\thakral\\setup_menu_apex.c"
#elif defined(THAKRAL_DVD)&&defined(DIXON_MODE)
    #include ".\\Customers\\thakral\\setup_menu_dixon.c"
#elif defined(THAKRAL_DVD)&&defined(DIXON_AMP_MODE)
    #include ".\\Customers\\thakral\\setup_menu_dixon_amp.c"
#elif defined(THAKRAL_DVD)
    #include ".\\Customers\\thakral\\setup_menu_thakral.c"
#endif

#if defined(ORITRON_DVD)
	#ifdef ORITRON_DVD_HT220_RECEIVER 
        #include ".\\Customers\\oritron\\setup_menu_oritron_HT220.c"
	#else
    	#include ".\\Customers\\oritron\\setup_menu_oritron.c"
	#endif
#endif

#if defined(WINGSUM_DVD)
	#if defined(WINGSUM_2CH_DVD)
        #include ".\\Customers\\wingsum\\setup_menu_wingsum_2ch.c"
	#elif defined(WINGSUM_51CH_DVD)
        #include ".\\Customers\\wingsum\\setup_menu_wingsum_51ch.c"
    #elif defined(WINGSUM_TVCOMBO)
        #include ".\\Customers\\wingsum\\setup_menu_wingsum_tvcombo.c"
    #endif
#endif

#if defined(SHINCO_DVD)
    #include ".\\Customers\\shinco\\setup_menu_shinco.c"
#endif

#ifdef EASTECH_DVD
#ifdef EASTECH_STD_SETUP_MENU
#ifdef EASTECH_CP3240_SETUP_MENU
	#include ".\\Customers\\eastech\\setup_menu_eastech_cp3240.c"
	#elif defined(EASTECH_PHILIPS_SETUP_MENU)
	#include ".\\Customers\\eastech\\setup_menu_Eastech_Philips_autoloadsetup.c"
#elif defined(EASTECH_CP2070_SETUP_MENU)
	#include ".\\Customers\\eastech\\setup_menu_eastech_cp2070.c"
#else	
	#include ".\\Customers\\eastech\\setup_menu_eastech_std.c"
#endif//#ifdef EASTECH_CP3240_SETUP_MENU
#else
 #include ".\\Customers\\eastech\\setup_menu_eastech.c"
#endif//#ifdef EASTECH_STD_SETUP_MENU
#endif//#ifdef EASTECH_DVD

#ifdef HANYANG_DVD
    #ifdef HANYANG_DP02CD_WF_8202S_16
        #include ".\\Customers\\hanyang\\setup_menu_hanyang_dp02cd_wf.c"
    #elif defined(HANYANG_DP02CD_WG_8202S_16)
        #include ".\\Customers\\hanyang\\setup_menu_hanyang_dp02cd_wg.c"
    #else
        #include ".\\Customers\\hanyang\\setup_menu_hanyang.c"
    #endif
#endif

#ifdef TONIC_DVD  //zhongshan add 05-07-11
    #include ".\\Customers\\tonic\\setup_menu_tonic.c"
#endif  

#ifdef ORITRON_HK_DVD//lijd 2005-5-10 12:47
 	#ifdef ORITRON_8202S_2X16_16BIT_DVD        
   		#include ".\\Customers\\HK_Oritron\\setup_menu_oritron_8202S_2X16.c"
   	#elif defined(ORITRON_8202S_1X16_16BIT_DVD)
   		#include ".\\Customers\\HK_Oritron\\setup_menu_oritron_8202S_1X16.c"	
    #elif defined(ORITRON_8202D_2X16_16BIT_DVD)
   		#include ".\\Customers\\HK_Oritron\\setup_menu_oritron_8202D_2x16.c"	
   	#elif defined(ORITRON_8202D_1X16_16BIT_DVD)
   		#include ".\\Customers\\HK_Oritron\\setup_menu_oritron_8202D_1x16.c"
   	#elif defined(ORITRON_8202D_3111_DVD)
   		#include ".\\Customers\\HK_Oritron\\setup_menu_oritron_8202D_dvd3111.c"
   	#elif defined(ORITRON_8202D_4110_DVD)
   		#include ".\\Customers\\HK_Oritron\\setup_menu_oritron_8202D_dvd4110.c"
   	#elif defined(ORITRON_8202D_4119_DVD)
   		#include ".\\Customers\\HK_Oritron\\setup_menu_oritron_8202D_dvd4119.c"
   	#elif defined(ORITRON_8202D_4125_DVD)
   		#include ".\\Customers\\HK_Oritron\\setup_menu_oritron_8202D_dvd4125.c"
   	#elif defined(ORITRON_8202D_4127_DVD)
   		#include ".\\Customers\\HK_Oritron\\setup_menu_oritron_8202D_dvd4127.c"
   	#elif defined(ORITRON_8202D_5112_DVD)
   		#include ".\\Customers\\HK_Oritron\\setup_menu_oritron_8202D_dvd5112.c"
   	#elif defined(ORITRON_8202D_5115_DVD)
   		#include ".\\Customers\\HK_Oritron\\setup_menu_oritron_8202D_dvd5115.c"		    
    #elif defined(ORITRON_8202D_5116_DVD)
   		#include ".\\Customers\\HK_Oritron\\setup_menu_oritron_8202D_dvd5116.c"
   	#elif defined(ORITRON_8202D_5117_DVD)
   		#include ".\\Customers\\HK_Oritron\\setup_menu_oritron_8202D_dvd5117.c"
   	#elif defined(ORITRON_8202D_5121_DVD)
   		#include ".\\Customers\\HK_Oritron\\setup_menu_oritron_8202D_dvd5121.c"	    
   	#elif defined(ORITRON_8202D_5122_DVD)
   		#include ".\\Customers\\HK_Oritron\\setup_menu_oritron_8202D_dvd5122.c"		    
   	#elif defined(ORITRON_8202D_6122_DVD)
   		#include ".\\Customers\\HK_Oritron\\setup_menu_oritron_8202D_dvd6122.c"			    
    #endif
#endif

#ifdef HK_ORITRON_DVD_RECEIVER //hongfeng 2005-07-09
    #if defined(ORITRON_RECEIVER_6001)
        #include ".\\Customers\\Oritron\\setup_menu_oritron_receiver_6001.c"
    #elif defined(ORITRON_RECEIVER_5105)
        #include ".\\Customers\\Oritron\\setup_menu_oritron_receiver_5105.c"
    #elif defined(ORITRON_RECEIVER_6008)
    #include ".\\Customers\\Oritron\\setup_menu_oritron_receiver_6008.c"    
    #elif defined(ORITRON_RECEIVER_5003)
    #include ".\\Customers\\Oritron\\setup_menu_oritron_receiver_5003.c"    
    #elif defined(ORITRON_RECEIVER_6505)
    #include ".\\Customers\\Oritron\\setup_menu_oritron_receiver_6505.c"
    #elif defined(ORITRON_RECEIVER_DPL937)
    #include ".\\Customers\\Oritron\\setup_menu_oritron_receiver_dpl937.c"
    #endif
#endif

#ifdef PHILIPS_DVD//chenzhao 20050613
    #ifdef PHILIPS_SETUP
    #include ".\\Customers\\philips\\setup_menu_philips.c"
    #else
    #include ".\\Customers\\Sunplus\\setup_menu_sunplus_8202D.c"
    #endif
#endif

#ifdef SAMBOO_HDDPLAYER_DVD//////////YANGLI 2005/8/17
   #include ".\\Customers\\Samboo\\setup_menu_samboo.c"

#endif


#ifdef MALATA_GPS_DVD//chenzhao 20050613  //liulifeng modify for malata gps dvd
    #include ".\\Customers\\MALATA_GPS_DVD\\setup_menu_malata_gps_dvd.c"
#endif

#ifdef LINKCONCEPT_DVD
    #if defined(LINKCONCEPT_32_DVD)||defined(LINKCONCEPT_8202S_DVD)||defined(LINKCONCEPT_16_DVD)||defined(LINKCONCEPT_8202S_16_DVD)
        #include ".\\Customers\\LINKCONCEPT\\setup_menu_linkconcept.c"
    #elif defined(LINKCONCEPT_8202D_DVD)||defined(LINKCONCEPT_8202D_16_DVD)||defined(LINKCONCEPT_8202D_16_040_NO_MP4)
        #include ".\\Customers\\LINKCONCEPT\\setup_menu_linkconcept_8202d.c"
    #endif
#endif


#if defined(YANGYU_DVD)	//wurh add 2006-9-8
	#if defined(YANGYU_8202D_DVD) || defined(YANGYU_8202D_2_16_DVD) || defined(YANGYU_8202L_64_DVD)
		#include ".\\Customers\\yangyu\\setup_menu_yangyu_8202D.c"
	#elif defined(YANGYU_8202D_16_DVD)||defined(YANGYU_8202D_16_040_DVD)||defined(YANGYU_8202L_16_DVD)
        #include ".\\Customers\\yangyu\\setup_menu_yangyu_8202D_16.c"        
	#else
        #include ".\\Customers\\yangyu\\setup_menu_yangyu.c"
    #endif
#endif

#if defined(ARLINK_DVD)	//yaowh 2005-10-12 11:34
	#if defined(IC_8202D)
		#include ".\\Customers\\arlink\\setup_menu_arlink_8202D.c"
	#else
        #include ".\\Customers\\arlink\\setup_menu_arlink.c"
    #endif
#endif

#if defined(YUXING_DVD)	//yaowh 2005-10-12 11:34
	#if defined(IC_8202D)
		#include ".\\Customers\\YUXING\\setup_menu_yuxing_8202D.c"
	#else
        #include ".\\Customers\\YUXING\\setup_menu_yuxing.c"
    #endif
#endif

#ifdef MALATA_PORTABLE_DVD
   #if defined(MALATA_PORTABLE_DVBT)
//#########################################################################
//#ifdef MODE_67003_ODYS //GERMAN  USER
	//#define SUPPORT_67003_ODYS_SETUP_MENU_CFG
	//#define SUPPORT_67003_BELSON_SETUP_MENU_CFG
	//#define SUPPORT_67003_POLAROID_SETUP_MENU_CFG
	//#define SUPPORT_67003_ITSLABEL_SETUP_MENU_CFG
	//#define SUPPORT_68501_XXX_SETUP_MENU_CFG
	//#define SUPPORT_68502_LENCO_SETUP_MENU_CFG
	//#define SUPPORT_68503_XXX_SETUP_MENU_CFG
	//#define SUPPORT_68504_BELSON_SETUP_MENU_CFG
	
      	    #ifdef  SUPPORT_67003_ODYS_SETUP_MENU_CFG
    		#include ".\\Customers\\malata_portable\\setup_menu_malata_por_67003odys_dvd.c"
	    #endif//end=> #ifdef  MODE_67003_ODYS
		
	    #ifdef  SUPPORT_67003_BELSON_SETUP_MENU_CFG
    		#include ".\\Customers\\malata_portable\\setup_menu_malata_por_67003belson_dvd.c"
	    #endif//end=> #ifdef  MODE_67003_POLAROID

	    #ifdef  SUPPORT_67003_POLAROID_SETUP_MENU_CFG
    		#include ".\\Customers\\malata_portable\\setup_menu_malata_por_67003polaroid_dvd.c"
	    #endif//end=> #ifdef  SUPPORT_67003_POLAROID_SETUP_MENU_CFG

	    #ifdef  SUPPORT_67003_ITSLABEL_SETUP_MENU_CFG
    		#include ".\\Customers\\malata_portable\\setup_menu_malata_por_67003itslabel_dvd.c"
	    #endif//end=> #ifdef  SUPPORT_67003_ITSLABEL_SETUP_MENU_CFG

	    #ifdef  SUPPORT_67003_SVC_SETUP_MENU_CFG
    		#include ".\\Customers\\malata_portable\\setup_menu_malata_por_67003svc_dvd.c"
	    #endif//end=> #ifdef  SUPPORT_67003_SVC_SETUP_MENU_CFG
		
	    #ifdef  SUPPORT_67003_XXX_SETUP_MENU_CFG
    		#include ".\\Customers\\malata_portable\\setup_menu_malata_por_67003_xxx_dvd.c"
	    #endif//end=> #ifdef  SUPPORT_67003_XXX_SETUP_MENU_CFG
		
	    #ifdef  SUPPORT_68501_XXX_SETUP_MENU_CFG
    		#include ".\\Customers\\malata_portable\\setup_menu_malata_por_68501_xxx_dvd.c"
	    #endif//end=> #ifdef  SUPPORT_68501_XXX_SETUP_MENU_CFG
		
		#ifdef  SUPPORT_68501_POLAROID_SETUP_MENU_CFG
    		#include ".\\Customers\\malata_portable\\setup_menu_malata_por_68501polaroid_dvd.c"
	    #endif//end=> #ifdef  SUPPORT_68501_POLAROID_SETUP_MENU_CFG

		#ifdef  SUPPORT_68501_ITSLABEL_SETUP_MENU_CFG
    		#include ".\\Customers\\malata_portable\\setup_menu_malata_por_68501itslabel_dvd.c"
	    #endif//end=> #ifdef  SUPPORT_68501_ITSLABEL_SETUP_MENU_CFG

		
	    #ifdef  SUPPORT_68502_LENCO_SETUP_MENU_CFG
    		#include ".\\Customers\\malata_portable\\setup_menu_malata_por_68502lenco_dvd.c"
	    #endif//end=> #ifdef  SUPPORT_68502_LENCO_SETUP_MENU_CFG
		
	    #ifdef  SUPPORT_68503_XXX_SETUP_MENU_CFG
    		#include ".\\Customers\\malata_portable\\setup_menu_malata_por_68503_xxx_dvd.c"
	    #endif//end=> #ifdef  SUPPORT_68503_XXX_SETUP_MENU_CFG

	    #ifdef  SUPPORT_68504_BELSON_SETUP_MENU_CFG
    		#include ".\\Customers\\malata_portable\\setup_menu_malata_por_68504belson_dvd.c"
           #endif//end=> #ifdef  SUPPORT_68504_BELSON_SETUP_MENU_CFG
    #endif
#endif


#ifdef ALCO_DVD //shenyj add for alco 2006/03/23        
    #if defined(ALCO_8202L_16M_PORTALBE_DVD)||defined(ALCO_8202L_64M_PORTALBE_DVD)
        #include ".\\Customers\\Alco_portable\\setup_menu_alco_8202L.c"
    #else
    #include ".\\Customers\\Alco_portable\\setup_menu_hide_alco_portable.c"
    #endif
#endif

#ifdef GOWELLENT_DVD

      #if defined(GOWELLENT_8202L_16M_DVD)||defined(GOWELLENT_8202L_64M_DVD)
			#include ".\\Customers\\gowellent\\setup_menu_Gowellent_8202L_16.c"
			#endif
			
#endif

