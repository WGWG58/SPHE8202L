/*nono 5-5-9 12:34 split from safe.c */
/*nono 2-5-20 17:25 modified for differenrt customer with different screen_saver */
//terry,2004/2/6 11:42AM,test condition....

#ifdef GENERAL_DVD
#include ".\\Customers\\general\\safe_general.c" 
#elif defined(SUNPLUS_DVD)
#include ".\\Customers\\Sunplus\\safe_sunplus.c" 
#elif defined(AKI_DVD)          //fengjl  03/10/18
#include ".\\Customers\\Aki\\safe_aki.c" 
#elif defined(APEX_DVD)         //Maoyong 2004.03.23
#include ".\\Customers\\Apex\\safe_apex.c"
#elif defined(ATLAS_DVD)         //Maoyong 2004.03.23
#include ".\\Customers\\atlas\\safe_atlas.c"
#elif defined(BBK_DVD)                 //fengjl  03/10/17
#include ".\\Customers\\Bbk\\safe_bbk.c" 
#elif defined(HUALU_DVD)            //lxg 2006-7-18 09:43
#include ".\\Customers\\hualu\\safe_sunplus.c" 
#elif defined(SMT_DVD)                 //fengjl  3-10-23 18:44
#include ".\\Customers\\Smt\\safe_smt.c" 
#elif defined(ZhengTai_DVD)                 //fengjl  3-10-23 18:44
#include ".\\Customers\\ZhengTai\\safe_zhengtai.c" 
#elif defined(JIEKE_DVD)
#include ".\\Customers\\jieke\\safe_jieke.c" 
#elif defined(YADAI_DVD)                 
#include ".\\Customers\\Yadai\\safe_yadai.c" 
#elif defined(YUXING_DVD)
#include ".\\Customers\\Yuxing\\safe_yuxing.c" 
#elif defined(YUXING_MIDI_DVD)                              //xlluo add 04-6-11
#include ".\\Customers\\Yuxing\\safe_yuxing.c" 
#elif defined(SANJING_MIDI_DVD)                              //ouyang add 05-01-27
#include ".\\Customers\\Sanjing\\safe_sanjing.c"
#elif defined(GAODASI_DVD)                 
#include ".\\Customers\\Gaodasi\\safe_gaodasi.c" 
#elif defined(SAMBOO_HDDPLAYER_DVD)//////////YANGLI 2005/8/17
#include ".\\Customers\\Samboo\\safe_Samboo.c" 
#elif defined(SAMSUNG1_DVD) 
#include ".\\Customers\\Sunplus\\safe_sunplus.c" 
#elif defined(MUSTEK_PORTABLE_DVD) 
#include ".\\Customers\\Mustek_portable\\safe_mustek_portable.c" 
#elif defined(MUSTEK_DVD) 
#include ".\\Customers\\Mustek\\safe_mustek.c" 
#elif defined(FUSS_DVD) 
#ifdef FUSS_LIDE_DVD
#include ".\\Customers\\fuss\\lide\\safe_fuss_lide.c" 
#elif defined(FUSS_SHENGKE_DVD)
#include ".\\Customers\\fuss\\shengke\\safe_fuss_shengke.c" 
#elif defined(FUSS_SANYING_DVD)
#include ".\\Customers\\Fuss\\sanying\\safe_fuss_sanying.c" 
#elif defined(FUSS_MASCO_DVD)
#include ".\\Customers\\Fuss\\masco\\safe_fuss_masco.c" 
#elif defined(FUSS_FEIYANG_DVD)
#include ".\\Customers\\Fuss\\feiyang\\safe_fuss_feiyang.c" 
#elif defined(FUSS_SHUNJIAN_DVD)
#include ".\\Customers\\Fuss\\shunjian\\safe_fuss_shunjian.c" 
#else
#include ".\\Customers\\Fuss\\safe_fuss.c" 
#endif

#elif defined(HUAJIA_DVD) 
#include ".\\Customers\\Huajia\\safe_huajia.c" 

#elif defined(NINTAUS_DVD) 
#include ".\\Customers\\nintaus\\safe_nintaus.c" 
#elif defined(NINTAUS_MIDI_DVD) 
#include ".\\Customers\\nintaus\\safe_nintaus.c" 

#elif defined(SVA_DVD) 
#include ".\\Customers\\Sva\\safe_sva.c"
#elif defined(KONKA_DVD) 
#include ".\\Customers\\Konka\\safe_konka.c"

#elif defined(GBM_DVD) 
#include ".\\Customers\\Gbm\\safe_gbm.c"

#elif defined(GBM_PORTABLE_DVD)
#include ".\\Customers\\gbm_portable\\safe_gbmportable.c"

#elif defined(GBM_AP_DVD) 
#include ".\\Customers\\Gbm_ap\\safe_gbm_ap.c"

#elif defined(CNMOTOR_DVD) 
#include ".\\Customers\\Cnmotor\\safe_cnmotor.c"
#elif defined(BMT_DVD) 
#include ".\\Customers\\BMT\\safe_BMT.c"
#elif defined(SUOJIA_DVD) 
#include ".\\Customers\\suojia\\safe_suojia.c"
#elif defined(OUR_MIND_DVD) 
#include ".\\Customers\\ourmind\\safe_ourmind.c"
#elif defined(WEIKING_DVD_AMP) 
#include ".\\Customers\\weiking\\safe_weiking.c"
#elif defined(APOLLO_DVD) 
#include ".\\Customers\\apollo\\safe_apollo.c"
#elif defined(AVIQ_DVD) 
#include ".\\Customers\\AViQ\\safe_aviq.c"
#elif defined(FUDI_DVD) 
#include ".\\Customers\\fudi\\safe_fudi.c"
#elif defined(CONSER_DVD)
    #if defined(CONSERproview_a)
        #include ".\\Customers\\Sunplus\\safe_sunplus.c" 
    #else
        #include ".\\Customers\\Sunplus\\safe_sunplus.c" 
    #endif
#elif defined(PROVIEW_DVD)
    #if defined(PROVIEW_288k)
        #include ".\\Customers\\Sunplus\\safe_sunplus.c" 
    #else
        #include ".\\Customers\\Sunplus\\safe_sunplus.c" 
    #endif

#elif defined(ZIHUAN_DVD)
#include ".\\Customers\\zihuan\\safe_zihuan.c"

#elif defined(QISHENG_DVD)
#include ".\\Customers\\QiSheng\\safe_qisheng.c"

#elif defined(YAHSIN_DVD)
#include ".\\Customers\\YaHsin\\safe_yahsin.c"

#elif defined(SKYWORTH_DVD)
#include ".\\Customers\\SkyWorth\\safe_skyworth.c"

#elif defined(SKYTECH_DVD)
#include ".\\Customers\\Skytech\\safe_skytech.c"

#elif defined(MICO_DVD)
#include ".\\Customers\\mico\\safe_mico.c"

#elif defined (KSD_DVD)
#include ".\\Customers\\TrendDigit\\safe_ksd.c"

#elif defined (ZHAOCHI_DVD) //LYC 2005-04-04
#include ".\\Customers\\ZHAOCHI\\safe_zhaochi.c"

#elif defined(DESAY_DVD)
#include ".\\Customers\\Desay\\safe_desay.c"

#elif defined(MINTON_DVD)
#include ".\\Customers\\Minton\\safe_minton.c"

#elif defined(IDALL_DVD)
#include ".\\Customers\\IDall\\safe_idall.c"

#elif defined(EASTECH_DVD)    //2004-4-2 1:31 wsf
#include ".\\Customers\\EASTECH\\safe_eastech.c" 

#elif defined(EVERSTAR_DVD)
#include ".\\Customers\\everstar\\safe_everstar.c"

#elif defined(QISHENG_DVD)  // alan, 2003/8/29 12:32AM
#include ".\\Customers\\qisheng\\safe_qisheng.c"

#elif defined(VTREK_DVD)    //wanghaoying 2003-9-10 20:56
#include ".\\Customers\\Vtrek\\safe_vtrek.c"

#elif defined(INTECH_DVD)    //nono 3-9-25 14:14
#include ".\\Customers\\intech\\safe_intech.c"

#elif defined(LINKCONCEPT_DVD)    //nono 3-9-25 14:14
#include ".\\Customers\\LINKCONCEPT\\safe_linkconcept.c"

#elif defined(GENTEK_DVD)
#include ".\\Customers\\Gentek\\safe_gentek.c"

#elif defined(HUIFENGYUAN_DVD)
#include ".\\Customers\\HuiFengYuan\\safe_huifengyuan.c"

#elif defined(HENGCHEN_DVD)
#include ".\\Customers\\HengChen\\safe_hengchen.c"

#elif defined(HARMA_DVD)    //3-10-24 1:38张宇P
#include ".\\Customers\\HARMA\\safe_harma.c"

#elif defined(HANYANG_DVD)    //CAOH 2004-4-6 16:53
#include ".\\Customers\\HANYANG\\safe_HANYANG.c"

#elif defined(ACTIMA_DVD)    //2004-9-14 09:22張宇M
#include ".\\Customers\\actima\\safe_actima.c"
#elif defined(ARGUS_PORTABLE_DVD)
#include ".\\Customers\\argus_portable\\safe_argusportable.c"

#elif defined(QSI_PORTABLE_DVD)//jhuang 2004/7/19
#include ".\\Customers\\qsi_portable\\safe_qsiportable.c"

#elif defined(WYD_DVD)    //3-10-27 1:50张宇P
#include ".\\Customers\\WYD\\safe_WYD.c"

#elif defined(HONGTU_DVD)    //2003-11-25 03:56张宇P
#include ".\\Customers\\HONGTU\\safe_HONGTU.c"

#elif defined(KENLOON_DVD)    //2004-4-14 11:19张宇M
#include ".\\Customers\\kenloon\\safe_kenloon.c"

#elif defined(SZMALATA_DVD)    //2004-2-3 01:18张宇P
#include ".\\Customers\\SZMALATA\\safe_SZMALATA.c"

#elif defined(TONIC_DVD)    //2004-2-3 01:18张宇P
#include ".\\Customers\\TONIC\\safe_TONIC.c"

#elif defined(MALATA_DVD)    //2003-11-25 03:56张宇P
#include ".\\Customers\\MALATA\\safe_MALATA.c"

#elif defined(NEWFUSS_DVD)    //2003-11-25 03:56张宇P
#include ".\\Customers\\NEWFUSS\\safe_NEWFUSS.c"

#elif defined(TIANKE_DVD)    //3-10-24 1:38张宇P
#include ".\\Customers\\TIANKE\\safe_TIANKE.c"

#elif defined(WEICHENG_DVD)
#include ".\\Customers\\weicheng\\safe_weicheng.c"

#elif defined(XUKE_DVD)
#include ".\\Customers\\xuke\\safe_xuke.c"

#elif defined(XINGWEIKE_DVD)
#include ".\\Customers\\XINGWEIKE\\safe_xingweike.c"

#elif defined(YANGYU_DVD)
#include ".\\Customers\\YangYu\\safe_yangyu.c"

#elif defined(ARLINK_DVD)                  //05-03-03 yaowh
#include ".\\Customers\\Arlink\\safe_Arlink.c"

#elif defined(ALON_DVD)
#include ".\\Customers\\Alon\\safe_alon.c"

#elif defined(TONGFANG_DVD)
#include ".\\Customers\\TongFang\\safe_tongfang.c"

#elif defined(XINDE_DVD)
#include ".\\Customers\\XinDe\\safe_xinde.c" 

#elif defined(XINGQIU_DVD)
#include ".\\Customers\\xingqiu\\safe_xingqiu.c"

#elif defined(ORITRON_DVD)
#include ".\\Customers\\Oritron\\safe_oritron.c"

#elif defined(ORITRON_HK_DVD)//lijd 2005-5-8 16:34    
	#include ".\\Customers\\HK_Oritron\\safe_hk_oritron.c"  

#elif defined(HK_ORITRON_DVD_RECEIVER)  //hongfeng 2005-07-09
#include ".\\Customers\\Oritron\\safe_hk_oritron.c"

#elif defined (ORIENTPOWER_DVD)
    #include ".\\Customers\\Orientpower\\safe_orientpower.c" 

#elif defined(SYBER_DVD)    //2003-11-19 9:04 David
#include ".\\Customers\\SYBER\\safe_syber.c"

#elif defined(SHIDELI_DVD)                      
#include ".\\Customers\\SHIDELI\\safe_shideli.c"        //gerry,2004-4-22 16:10

#elif defined(THAKRAL_DVD) 
#include ".\\Customers\\thakral\\safe_thakral.c"        //suqiaoli,2004-9-16 

#elif defined(EASTWIN_PORTABLE_DVD)                      
#include ".\\Customers\\Eastwin\\safe_eastwin.c"

#elif defined(TEAC_PORTABLE_DVD)//TEAC
#include ".\\Customers\\teac_portable\\safe_teac.c"

#elif defined(JIANLOON_DVD)   //liych  added 2005-3-23
#include ".\\Customers\\JIANLOON\\safe_JianLoon.c"

#elif defined(APEX_PORTABLE_DVD)     ////liulifeng 2005-4-29 12:45
    #include ".\\Customers\\APEX_PDVD\\safe_apex.c"

#elif defined(SHINCO_DVD)    
    #include ".\\Customers\\shinco\\safe_shinco.c"
#elif defined(MALATA_GPS_DVD)
    #include ".\\Customers\\MALATA_GPS_DVD\\safe_malata_gps_dvd.c"
#elif defined(MALATA_PORTABLE_DVD)
    #if defined(MALATA_PORTABLE_DVBT)
    #include ".\\Customers\\malata_portable\\safe_malata_por_8202d_dvb.c"
    #endif
#elif defined(ALCO_DVD)//shenyj modify 2006/08/24
    #include ".\\Customers\\Alco_portable\\safe_Alcoportable.c"
#elif defined(GOWELLENT_DVD)
     #include ".\\Customers\\Gowellent\\safe_Gowellent.c"
#else
    #include ".\\Customers\\Sunplus\\safe_sunplus.c"
#endif


