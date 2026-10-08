/* Include VFD Module Type  */

//nono modify to be convenient for customers.2-7-4 13:38
#ifdef GENERAL_PANNEL     /*YUXING_PANEL*/
#ifdef GBM_PORTABLE_DVD
#include ".\\Customers\\Gbm_portable\\vfd_gbm_portable.h"
#elif defined(MUSTEK_K100D_MODEL)
#include ".\\Customers\\Mustek_portable\\panel_key_mustek_k100d_portabledvb.h"
#else
    #if defined(ALCO_PORTABLE)
	#include ".\\Customers\\Alco_portable\\vfd_alco_portable.h"
	#else
    #include ".\\Customers\\general\\vfd_general_16312_k.h" //for NINTAUS DVD-N701 key pad definition
    #endif
#endif
#include ".\\Customers\\general\\vfd_general_16312_l.h"     //vfd LCD HT1611	of NINTAUS DVD-701
#include ".\\Customers\\general\\vfd_general_16312.c"	//HT1611 LCD display function

#elif defined(TWINHAN_8222_PANNEL)  //haoy 2005/03/31 16:06
#include ".\\Customers\\Twinhan\\led_twinhan_k.h" 
#include ".\\Customers\\Twinhan\\led_twinhan_l.h"     
#include ".\\Customers\\Twinhan\\led_twinhan.c"

#elif defined(GENERAL_HT1621_PANNEL)//2004-5-9 18:48 lijd
#include ".\\Customers\\general\\vfd_ht1621_l.h"  
#include ".\\Customers\\general\\vfd_ht1621.c"	

#elif defined(VFD13_PANNEL)//2004-5-9 18:48 lijd
#include ".\\Customers\\Sunplus\\vfd_13_k.h" 
#include ".\\Customers\\Sunplus\\vfd_13_l.h"  
#include ".\\Customers\\Sunplus\\vfd_13.c"	

#elif defined(HUALU_318AK_PANNEL)   //lxg 2006-7-18 10:12
#include ".\\Customers\\hualu\\vfd_general_16312_k.h" 
#include ".\\Customers\\hualu\\vfd_general_16312_l.h"  
#include ".\\Customers\\hualu\\vfd_general_16312.c"	

#elif defined(SY_M5_256_PANNEL)//axel2004/7/13 
#include ".\\Customers\\Sunplus\\vfd_sy_m5_256_k.h" 
#include ".\\Customers\\Sunplus\\vfd_sy_m5_256_l.h" 
#include ".\\Customers\\Sunplus\\vfd_sy_m5_256.c"	

#elif defined(TP6311_DRIVER_VFD)//xyy 2003-11-6 10:15
#include ".\\Customers\\Sunplus\\vfd_gbmsample_k.h" 
#include ".\\Customers\\Sunplus\\vfd_gbmsample_l.h"  
#include ".\\Customers\\Sunplus\\vfd_gbmsample1.c"	

#elif defined(AKI_838LC_PANNEL)      //fengjl 03/10/18 for chuangying
#include ".\\Customers\\aki\\vfd_aki_838lc_k.h" 
#include ".\\Customers\\aki\\vfd_aki_838lc_l.h"     
#include ".\\Customers\\aki\\vfd_aki_838lc.c"

#elif defined(AKI_868LE2_PANNEL)		//2003-12-18  868v30 2004-4-1
#include ".\\Customers\\aki\\vfd_aki_868le2_k.h" 
#include ".\\Customers\\aki\\vfd_aki_868le2_l.h"     
#include ".\\Customers\\aki\\vfd_aki_868le2.c"

#elif defined(AKI_838JO_PANNEL)      //fengjl 03/10/18 for chuangying
#include ".\\Customers\\aki\\vfd_aki_838jo_k.h" 
#include ".\\Customers\\aki\\vfd_aki_838jo_l.h"     
#include ".\\Customers\\aki\\vfd_aki_838jo.c"


#elif defined(AKI_868LE_PANNEL)      //fengjl 03/10/22 for chuangying
#ifdef AKI_868V12_0_vfd
#include ".\\Customers\\aki\\vfd_aki_868le_k_10w.h" 
#else
#include ".\\Customers\\aki\\vfd_aki_868le_k.h" 
#endif

#include ".\\Customers\\aki\\vfd_aki_868le_l.h"     
#include ".\\Customers\\aki\\vfd_aki_868le.c"

#elif defined(AKI_868v60_PANNEL)      //lyl 2004-3-9
#include ".\\Customers\\aki\\vfd_aki_868v60_k.h" 
#include ".\\Customers\\aki\\vfd_aki_868v60_l.h"     
#include ".\\Customers\\aki\\vfd_aki_868v60.c"

#elif defined(BBK_PANNEL)      //fengjl 03/10/16 for bbk
#include ".\\Customers\\bbk\\vfd_bbk_k.h" 
#include ".\\Customers\\bbk\\vfd_bbk_l.h"     
#include ".\\Customers\\bbk\\vfd_bbk.c"

#elif defined(BBK_DSS_555_PANNEL)      //fengjl 03/10/16 for bbk
#include ".\\Customers\\bbk\\vfd_dss_555_k.h" 
#include ".\\Customers\\bbk\\vfd_dss_555_l.h"     
#include ".\\Customers\\bbk\\vfd_dss_555.c"

#elif defined(SMT_PANNEL_898SP)      //fengjl 3-10-23 17:56 for SMT
#include ".\\Customers\\Smt\\vfd_smt898_k.h" 
#include ".\\Customers\\Smt\\vfd_smt898_l.h"     
#include ".\\Customers\\Smt\\vfd_smt898.c"

#elif defined(SMT_PANNEL_868)      //fengjl 3-10-29 9:03 for SMT
#include ".\\Customers\\Smt\\vfd_smt868_k.h" 
#include ".\\Customers\\Smt\\vfd_smt868_l.h"     
#include ".\\Customers\\Smt\\vfd_smt868.c"

#elif defined(SMT_PANNEL_888)      //fengjl 3-10-29 9:03 for SMT
#include ".\\Customers\\Smt\\vfd_smt888_k.h" 
#include ".\\Customers\\Smt\\vfd_smt888_l.h"     
#include ".\\Customers\\Smt\\vfd_smt888.c"

#elif defined(SMT_PANNEL_899)      //fengjl 2004-02-10 10:18 for SMT
#include ".\\Customers\\Smt\\vfd_smt899_k.h" 
#include ".\\Customers\\Smt\\vfd_smt899_l.h"     
#include ".\\Customers\\Smt\\vfd_smt899.c"

#elif defined(N701_PANNEL)     /* add new define 13D15S */
#include ".\\Customers\\Sunplus\\vfd_nin_k.h" //for NINTAUS DVD-N701 key pad definition
#include ".\\Customers\\Sunplus\\vfd_nin_l.h"     //vfd LCD HT1611	of NINTAUS DVD-701
#include ".\\Customers\\Sunplus\\vfd_nin.c"	//HT1611 LCD display function

#elif defined(JIEKE_PANNEL)     /* wangfeng 2003-09-29 21:29 */
#include ".\\Customers\\jieke\\vfd_jieke_k.h" 
#include ".\\Customers\\jieke\\vfd_jieke_l.h"     
#include ".\\Customers\\jieke\\vfd_jieke.c"	

#elif defined(JIEKE_PANNEL_GK906)     /* wangfeng 2003-11-18 11:20 */
#include ".\\Customers\\jieke\\vfd_jieke906_k.h" 
#include ".\\Customers\\jieke\\vfd_jieke906_l.h"     
#include ".\\Customers\\jieke\\vfd_jieke906.c"	

#elif defined(JIEKE_PANNEL_GK3800)     /* wangfeng 2003-11-19 11:04 */
#include ".\\Customers\\jieke\\vfd_jieke3800_k.h" 
#include ".\\Customers\\jieke\\vfd_jieke3800_l.h"     
#include ".\\Customers\\jieke\\vfd_jieke3800.c"	

#elif defined(CONSER_DVD288_PANNEL)	//bruce 2003/2/25 01:44PM
#include ".\\Customers\\Conser\\vfd_conser_k.h"
#include ".\\Customers\\Conser\\vfd_conser_l.h"
#include ".\\Customers\\Conser\\vfd_conser.c"

#elif defined(PROVIEW_PANNEL)	//jim 2003/5/25 
#include ".\\Customers\\Proview\\vfd_proview_k.h"
#include ".\\Customers\\Proview\\vfd_proview_l.h"
#include ".\\Customers\\Proview\\vfd_proview.c"

#elif defined(ZHENGTAI_PANNEL)	//jim 2003/5/25 
#include ".\\Customers\\ZhengTai\\vfd_zhengtai_k.h"
#include ".\\Customers\\ZhengTai\\\vfd_zhengtai_l.h"
#include ".\\Customers\\ZhengTai\\\vfd_zhengtai.c"

#elif defined(SKYWORTH_PANNEL)
#include ".\\Customers\\SkyWorth\\vfd_skyworth_k.h"
#include ".\\Customers\\SkyWorth\\vfd_skyworth_l.h"
#include ".\\Customers\\SkyWorth\\vfd_skyworth.c"

#elif defined(SKYWORTH2752_PANNEL)
#include ".\\Customers\\SkyWorth\\vfd_skyworth2752_k.h"
#include ".\\Customers\\SkyWorth\\vfd_skyworth2752_l.h"
#include ".\\Customers\\SkyWorth\\vfd_skyworth2752.c"
#elif defined(SKYWORTH_HT1621_PANNEL)
#include ".\\Customers\\SkyWorth\\vfd_skyworth2752_k.h"
#include ".\\Customers\\SkyWorth\\vfd_skyworth_ht1621_l.h"
#include ".\\Customers\\SkyWorth\\vfd_skyworth_ht1621.c"


#elif defined(SKYWORTH2752_LED_PANNEL)
#include ".\\Customers\\SkyWorth\\vfd_skyworth2752_k.h"
#include ".\\Customers\\SkyWorth\\vfd_skyworth2752_led_l.h"
#include ".\\Customers\\SkyWorth\\vfd_skyworth2752_led.c"


#elif defined(YUXING_PANEL)

#ifdef YX822A
#include ".\\Customers\\Yuxing\\vfd_yux_k822a.h"
#elif defined(YX822BC)
#include ".\\Customers\\Yuxing\\vfd_yux_k822bc.h"
#else
#include ".\\Customers\\Yuxing\\vfd_yux_k.h"
#endif

#include ".\\Customers\\Yuxing\\vfd_yux_l.h"
#include ".\\Customers\\Yuxing\\vfd_yux.c"

#elif defined(YUXING_MIDI_PANNEL)  //ouyang 2004.07.31

#include ".\\Customers\\Yuxing\\vfd_yux_k.h"
#include ".\\Customers\\Yuxing\\vfd_yux_l.h"
#include ".\\Customers\\Yuxing\\vfd_yux.c"

#elif defined(SAMSUNG1_PANNEL)		//shawn add at 910131

#include ".\\Customers\\Samsung\\vfd_sam1_k.h"
#include ".\\Customers\\Samsung\\vfd_sam1_l.h"
#include ".\\Customers\\Samsung\\vfd_sam1.c"

#elif defined(WANGINE_PANNEL)
#include ".\\Customers\\Wangine\\vfd_wangine_k.h"
#include ".\\Customers\\Wangine\\vfd_wangine_l.h"
#include ".\\Customers\\Wangine\\vfd_wangine.c"
#elif defined(WANGINE_PANNEL2)
#include ".\\Customers\\Wangine\\vfd_wangine2_k.h"
#include ".\\Customers\\Wangine\\vfd_wangine2_l.h"
#include ".\\Customers\\Wangine\\vfd_wangine2.c"


#elif defined(MUSTEK_PANEL)
#include ".\\Customers\\Mustek\\vfd_mustek_k.h"
#include ".\\Customers\\Mustek\\vfd_mustek_l.h"
#include ".\\Customers\\Mustek\\vfd_mustek.c"

#elif defined(FUSS_PANEL)	

#ifdef DV8881VFD
#include ".\\Customers\\Fuss\\vfd_fuss_k.h"
#else
#include ".\\Customers\\Fuss\\vfd_fuss_k2.h"
#endif

#include ".\\Customers\\Fuss\\vfd_fuss_l.h"
#include ".\\Customers\\Fuss\\vfd_fuss.c"

#elif defined(FUSS2_PANEL)//nono 2002-5-20
#include ".\\Customers\\Fuss\\vfd_fuss2_k2.h"
#include ".\\Customers\\Fuss\\vfd_fuss2_l.h"
#include ".\\Customers\\Fuss\\vfd_fuss2.c"

#elif defined(FUSST_PANEL)//nono 2002-5-20
#include ".\\Customers\\Fuss\\vfd_fusst_k.h"
#include ".\\Customers\\Fuss\\vfd_fusst_l.h"
#include ".\\Customers\\Fuss\\vfd_fusst.c"

#elif defined( FENGKAI_M58_PANNEL  )
#include ".\\Customers\\fengkai\\vfd_fengkai_m58_k.h" 
#include ".\\Customers\\fengkai\\vfd_fengkai_m58_l.h" 
#include ".\\Customers\\fengkai\\vfd_fengkai_m58.c"	//2-12-3 16:18

#elif defined(SUOJIA297_PANNEL)	//2-12-6 
#include ".\\Customers\\Suojia\\vfd_suojia297_k.h"
#include ".\\Customers\\Suojia\\vfd_suojia297_l.h"
#include ".\\Customers\\Suojia\\vfd_suojia297.c"

#elif defined(FUSS_SHENGKE_PANEL)		//20020706 
#include ".\\Customers\\Fuss\\shengke\\vfd_fuss_shengke_k.h"
#include ".\\Customers\\Fuss\\shengke\\vfd_fuss_shengke_l.h"
#include ".\\Customers\\Fuss\\shengke\\vfd_fuss_shengke.c"

#elif defined(FUSS_XINQIAO_PANEL)		//2-10-28 22:02 
#include ".\\Customers\\Fuss\\xinqiao\\vfd_fuss_xinqiao_k.h"
#include ".\\Customers\\Fuss\\xinqiao\\vfd_fuss_xinqiao_l.h"
#include ".\\Customers\\Fuss\\xinqiao\\vfd_fuss_xinqiao.c"

#elif defined(FUSS_SANYING_PANEL)		//20020706
#include ".\\Customers\\Fuss\\sanying\\vfd_fuss_sanying_k.h"
#include ".\\Customers\\Fuss\\sanying\\vfd_fuss_sanying_l.h"
#include ".\\Customers\\Fuss\\sanying\\vfd_fuss_sanying.c"

#elif defined(FUSS_SANYING2_PANEL)		//20020706
#include ".\\Customers\\Fuss\\sanying\\vfd_fuss_sanying2_k.h"
#include ".\\Customers\\Fuss\\sanying\\vfd_fuss_sanying2_l.h"
#include ".\\Customers\\Fuss\\sanying\\vfd_fuss_sanying2.c"

#elif defined(FUSS_FEIYANG_2100_PANEL)		//20020706
#include ".\\Customers\\Fuss\\feiyang\\dk2100\\vfd_fuss_feiyang_k.h"
#include ".\\Customers\\Fuss\\feiyang\\dk2100\\vfd_fuss_feiyang_l.h"
#include ".\\Customers\\Fuss\\feiyang\\dk2100\\vfd_fuss_feiyang.c"

#elif defined(FUSS_FEIYANG_2110_PANEL)		//20020706
#include ".\\Customers\\Fuss\\feiyang\\dk2110\\vfd_fuss_feiyang_k.h"
#include ".\\Customers\\Fuss\\feiyang\\dk2110\\vfd_fuss_feiyang_l.h"
#include ".\\Customers\\Fuss\\feiyang\\dk2110\\vfd_fuss_feiyang.c"

#elif defined(FUSS_FEIYANG_2120_PANEL)		//20020706
#include ".\\Customers\\Fuss\\feiyang\\dk2120\\vfd_fuss_feiyang_k.h"
#include ".\\Customers\\Fuss\\feiyang\\dk2120\\vfd_fuss_feiyang_l.h"
#include ".\\Customers\\Fuss\\feiyang\\dk2120\\vfd_fuss_feiyang.c"

#elif defined(FUSS_FEIYANG_2130_PANEL)		//20020706
#include ".\\Customers\\Fuss\\feiyang\\dk2130\\vfd_fuss_feiyang_k.h"
#include ".\\Customers\\Fuss\\feiyang\\dk2130\\vfd_fuss_feiyang_l.h"
#include ".\\Customers\\Fuss\\feiyang\\dk2130\\vfd_fuss_feiyang.c"

#elif defined(FUSS_LIDE_PANEL)	
#include ".\\Customers\\Fuss\\Lide\\vfd_fuss_lide_k2.h"
#include ".\\Customers\\Fuss\\Lide\\vfd_fuss_lide_l.h"
#include ".\\Customers\\Fuss\\Lide\\vfd_fuss_lide.c"

#elif defined(HUAJIA_PANEL)	
#include ".\\Customers\\Huajia\\vfd_huajia_k.h"
#include ".\\Customers\\Huajia\\vfd_huajia_l.h"
#include ".\\Customers\\Huajia\\vfd_huajia.c"

#elif defined(HUAJIA8800_PANEL)	

#if defined(HIMAGE2206)||defined(HIMAGE5900M)||defined(HIMAGE2206_NEW)
#include ".\\Customers\\Huajia\\vfd_huajia8800_k2106.h"
#elif defined(HIMAGE2818)||defined(VFD2818_KEY)//akai 3850S
#include ".\\Customers\\Huajia\\vfd_huajia8800_k2818.h"
#elif defined(HIMAGE909)
#include ".\\Customers\\Huajia\\vfd_huajia8800_k909.h"
#elif defined(HIMAGE921)||defined(HIMAGE2203)//daewoo S200(S250)
#include ".\\Customers\\Huajia\\vfd_huajia8800_k921.h"
#elif defined(HIMAGE929)
#include ".\\Customers\\Huajia\\vfd_huajia8800_k929.h"
#elif defined(HIMAGE927B)||defined(HIMAGE2202)//akishi 6000

#if defined(HIMAGE_KECHENG)
#include ".\\Customers\\Huajia\\vfd_huajia8800_k927B_kecheng.h"
#else
#include ".\\Customers\\Huajia\\vfd_huajia8800_k927B.h"
#endif
#elif defined(HIMAGE2048)||defined(HIMAGE2048new) //2-10-3 13:48
#include ".\\Customers\\Huajia\\vfd_huajia8800_k2048.h"
#else	
#include ".\\Customers\\Huajia\\vfd_huajia8800_k.h"
#endif

#include ".\\Customers\\Huajia\\vfd_huajia8800_l.h"
#include ".\\Customers\\Huajia\\vfd_huajia8800.c"

#elif defined(HUAJIA06SS98_PANEL)	
#include ".\\Customers\\Huajia\\vfd_huajia_06ss98_k.h"
#include ".\\Customers\\Huajia\\vfd_huajia_06ss98_l.h"
#include ".\\Customers\\Huajia\\vfd_huajia_06ss98.c"

#elif defined(HUAJIA9000_PANEL)	
#include ".\\Customers\\Huajia\\vfd_huajia9000_k.h"
#include ".\\Customers\\Huajia\\vfd_huajia9000_l.h"
#include ".\\Customers\\Huajia\\vfd_huajia9000.c"

#elif defined(LINKCONCEPT_PANNEL)		//xiaosan 02-05_20  
#include ".\\Customers\\LINKCONCEPT\\vfd_linkconcept_k.h"
#include ".\\Customers\\LINKCONCEPT\\vfd_linkconcept_l.h"
#include ".\\Customers\\LINKCONCEPT\\vfd_linkconcept.c"

#elif defined(JCG_PANEL)		//2-6-18 17:38
#include ".\\Customers\\Jcg\\vfd_jcg_k.h"
#include ".\\Customers\\Jcg\\vfd_jcg_l.h"
#include ".\\Customers\\Jcg\\vfd_jcg.c" 

#elif defined(NEXTBASE_PANNEL) // for sva tuner panel
#include ".\\Customers\\SVA\\vfd_nextbase_k.h"
#include ".\\Customers\\SVA\\vfd_nextbase_l.h"
#include ".\\Customers\\SVA\\vfd_nextbase.c"   

#elif defined(SVA_SAMPLE_PANNEL)    //2002-9-3 16:11
#include ".\\Customers\\SVA\\vfd_svasample_k.h"
#include ".\\Customers\\SVA\\vfd_svasample_l.h"
#include ".\\Customers\\SVA\\vfd_svasample.c"   

#elif defined(GAODASI_PANNEL) // for gaodasi panel
#include ".\\Customers\\Gaodasi\\vfd_gaodasi_k.h"
#include ".\\Customers\\Gaodasi\\vfd_gaodasi_l.h"
#include ".\\Customers\\Gaodasi\\vfd_gaodasi.c"   

#elif defined(HUAJIA602_PANEL)//white westinghouse S700
#include ".\\Customers\\Huajia\\vfd_huajia602_k.h"
#include ".\\Customers\\Huajia\\vfd_huajia602_l.h"
#include ".\\Customers\\Huajia\\vfd_huajia602.c"

#elif defined(HUAJIA2205_PANEL)//white westinghouse S700
#include ".\\Customers\\Huajia\\vfd_huajia2205_k.h"
#include ".\\Customers\\Huajia\\vfd_huajia2205_l.h"
#include ".\\Customers\\Huajia\\vfd_huajia2205.c"

#elif defined(HUAJIA2205B_PANEL)//02-076w & 02-078w
#include ".\\Customers\\Huajia\\vfd_huajia2205b_k.h"
#include ".\\Customers\\Huajia\\vfd_huajia2205b_l.h"
#include ".\\Customers\\Huajia\\vfd_huajia2205b.c"

#elif defined(HUAJIA04SS13_PANEL)//hj2323
#include ".\\Customers\\Huajia\\vfd_huajia_04ss13_k.h"
#include ".\\Customers\\Huajia\\vfd_huajia_04ss13_l.h"
#include ".\\Customers\\Huajia\\vfd_huajia_04ss13.c"

#elif defined(HUAJIA1251_PANEL)	//wangfeng 2003-09-17 23:00
#include ".\\Customers\\Huajia\\vfd_huajia1251_k.h"
#include ".\\Customers\\Huajia\\vfd_huajia1251_l.h"
#include ".\\Customers\\Huajia\\vfd_huajia1251.c"

#elif defined(HUAJIA600_PANEL)	//wangfeng 2003-09-17 23:00
#include ".\\Customers\\Huajia\\vfd_huajia600_k.h"
#include ".\\Customers\\Huajia\\vfd_huajia600_l.h"
#include ".\\Customers\\Huajia\\vfd_huajia600.c"

#elif defined(HUAJIADP316_PANEL)	//dingzhy	12/10/2003 1:56PM
#include ".\\Customers\\Huajia\\vfd_huajiadp316_k.h"
#include ".\\Customers\\Huajia\\vfd_huajiadp316_l.h"
#include ".\\Customers\\Huajia\\vfd_huajiadp316.c"

#elif defined(GBM_PANEL) // for gbm panel
#include ".\\Customers\\Gbm\\vfd_gbm_k.h"
#include ".\\Customers\\Gbm\\vfd_gbm_l.h"
#include ".\\Customers\\Gbm\\vfd_gbm.c"   
 	
#elif defined(GBM_HT1621_PANEL) // for gbm HT1621 panel,gerry,3-10-29 17:41
#include ".\\Customers\\Gbm\\vfd_gbm_ht1621_k.h"
#include ".\\Customers\\Gbm\\vfd_gbm_ht1621_l.h"
#include ".\\Customers\\Gbm\\vfd_gbm_ht1621.c"   
 	
#elif defined(GBM_LED6961_PANEL)    //gerry add it for GBM_PT6961 pannel,2004-1-17 20:23
#include ".\\Customers\\Gbm\\vfd_gbm_led_1008_k.h"
#include ".\\Customers\\Gbm\\vfd_gbm_led_1008_l.h"
#include ".\\Customers\\Gbm\\vfd_gbm_led_1008.c"   

#elif defined(GBM_PBCY_8202_PANNEL)    //gerry add it for GBM_PT6961 pannel,2004-1-17 20:23
#include ".\\Customers\\Gbm\\vfd_gbm_led_1008_k.h"
#include ".\\Customers\\Gbm\\vfd_gbm_led_1008_8202_l.h"
#include ".\\Customers\\Gbm\\vfd_gbm_led_1008_8202.c"   

#elif defined(GBM_AP_PANEL) // for gbm_ap panel,gerry,2003-12-12 13:25
#include ".\\Customers\\Gbm_ap\\vfd_gbm_ap_k.h"
#include ".\\Customers\\Gbm_ap\\vfd_gbm_ap_l.h"
#include ".\\Customers\\Gbm_ap\\vfd_gbm_ap.c"   

#elif defined(GBM_AP_HT1621_PANEL) // for gbm_ap HT1621 panel,gerry,2003-12-12 13:26
#include ".\\Customers\\Gbm_ap\\vfd_gbm_ap_ht1621_k.h"
#include ".\\Customers\\Gbm_ap\\vfd_gbm_ap_ht1621_l.h"
#include ".\\Customers\\Gbm_ap\\vfd_gbm_ap_ht1621.c"   

#elif defined(GBM_PANEL_35) // for gbm 35 panel
#include ".\\Customers\\Gbm\\vfd_gbm_35_k.h"
#include ".\\Customers\\Gbm\\vfd_gbm_35_l.h"
#include ".\\Customers\\Gbm\\vfd_gbm_35.c"   

#elif defined(P9CE_8202_PANEL) // for gbm 35 panel
#include ".\\Customers\\Gbm\\vfd_gbm_k.h"
#include ".\\Customers\\Gbm\\vfd_gbm_l.h"
#include ".\\Customers\\Gbm\\vfd_gbm.c" 


#elif defined(FUSS_MASCO_PANEL)		//20020706 
#include ".\\Customers\\Fuss\\masco\\vfd_fuss_masco_k.h"
#include ".\\Customers\\Fuss\\masco\\vfd_fuss_masco_l.h"
#include ".\\Customers\\Fuss\\masco\\vfd_fuss_masco.c"	

#elif defined(BMT_PANNEL) // for bmt 841 panel
#include ".\\Customers\\bmt\\vfd_bmt_k.h"
#include ".\\Customers\\bmt\\vfd_bmt_l.h"
#include ".\\Customers\\bmt\\vfd_bmt.c"   

#elif defined(SUOJIA_PANNEL) 
#include ".\\Customers\\suojia\\vfd_suojia_k.h"
#include ".\\Customers\\suojia\\vfd_suojia_l.h"
#include ".\\Customers\\suojia\\vfd_suojia.c"   

#elif defined(WEIKING_SM25_PANNEL) // for weiking smpanel
#include ".\\Customers\\weiking\\vfd_weiking_sm25_k.h"
#include ".\\Customers\\weiking\\vfd_weiking_sm25_l.h"
#include ".\\Customers\\weiking\\vfd_weiking_sm25.c"  

#elif defined(WEIKING_TUNER_PANNEL)
#include ".\\Customers\\weiking\\vfd_weiking_tuner_k.h"
#include ".\\Customers\\weiking\\vfd_weiking_tuner_l.h"
#include ".\\Customers\\weiking\\vfd_weiking_tuner.c"

#elif defined(APOLLO_PANEL) 
#include ".\\Customers\\apollo\\vfd_apollo_k.h"
#include ".\\Customers\\apollo\\vfd_apollo_l.h"
#include ".\\Customers\\apollo\\vfd_apollo.c"   

#elif defined(LUCKY_PANEL) 
#include ".\\Customers\\lucky\\vfd_lucky_k.h"
#include ".\\Customers\\lucky\\vfd_lucky_l.h"
#include ".\\Customers\\lucky\\vfd_lucky.c"   

#elif defined(OURMIND_PANEL)

#include ".\\Customers\\ourmind\\vfd_ourmind_l.h"
#include ".\\Customers\\ourmind\\vfd_ourmind_k.h"
#include ".\\Customers\\ourmind\\vfd_ourmind.c"

#elif defined(FUDI_PANEL)

#include ".\\Customers\\fudi\\vfd_fudi_l.h"
#include ".\\Customers\\fudi\\vfd_fudi_k.h"
#include ".\\Customers\\fudi\\vfd_fudi.c"

#elif defined(FUDI_906G_PANEL)
#include ".\\Customers\\fudi\\vfd_fudi_906g_k.h"
#include ".\\Customers\\fudi\\vfd_fudi_906g_l.h"
#include ".\\Customers\\fudi\\vfd_fudi_906g.c"   

#elif defined(FUSS_SHUNJIAN_PANEL)
#include ".\\Customers\\Fuss\\shunjian\\vfd_fuss_shunjian_k.h"
#include ".\\Customers\\Fuss\\shunjian\\vfd_fuss_shunjian_l.h"
#include ".\\Customers\\Fuss\\shunjian\\vfd_fuss_shunjian.c"	

#elif defined(MICO_PANEL)
#include ".\\Customers\\mico\\vfd_mico_l.h"
#include ".\\Customers\\mico\\vfd_mico_k.h"
#include ".\\Customers\\mico\\vfd_mico.c"

#elif defined(ZHAOCHI_PANEL)		//LYC 2005-04-04
#include ".\\Customers\\ZHAOCHI\\vfd_ZHAOCHI_PANEL_l.h"
#include ".\\Customers\\ZHAOCHI\\vfd_ZHAOCHI_PANEL_k.h"
#include ".\\Customers\\ZHAOCHI\\vfd_ZHAOCHI_PANEL.c"

#elif defined(KSD_PANEL)
#include ".\\Customers\\trenddigit\\vfd_ksd_l.h"
#include ".\\Customers\\trenddigit\\vfd_ksd_k.h"
#include ".\\Customers\\trenddigit\\vfd_ksd.c"

#elif defined(KSD_PANEL_2)
#include ".\\Customers\\trenddigit\\vfd_ksd_panel2_l.h"
#include ".\\Customers\\trenddigit\\vfd_ksd_panel2_k.h"
#include ".\\Customers\\trenddigit\\vfd_ksd_panel2.c"

#elif defined(KSD_PANEL_32)	// alan, 2003/8/15 11:08PM
#include ".\\Customers\\trenddigit\\vfd_ksd_panel32_l.h"
#include ".\\Customers\\trenddigit\\vfd_ksd_panel32_k.h"
#include ".\\Customers\\trenddigit\\vfd_ksd_panel32.c"

#elif defined(JIANLOON_DVD)	 //liych  added 2005-3-23
#include ".\\Customers\\JianLoon\\vfd_JianLoon_l.h"
#include ".\\Customers\\JianLoon\\vfd_JianLoon_k.h"
#include ".\\Customers\\JianLoon\\vfd_JianLoon.c"

#elif defined(ZIHUAN_PANEL)
#include ".\\Customers\\Zihuan\\vfd_zihuan_l.h"
#include ".\\Customers\\Zihuan\\vfd_zihuan_k.h"
#include ".\\Customers\\Zihuan\\vfd_zihuan.c"

#elif defined(QISHENG_PANEL)
#include ".\\Customers\\qisheng\\vfd_qisheng_l.h"
#include ".\\Customers\\qisheng\\vfd_qisheng_k.h"
#include ".\\Customers\\qisheng\\vfd_qisheng.c"

#elif defined(PROVIEW_ZYC20075_PANEL)
#include ".\\Customers\\Proview\\vfd_proview_zyc20075_k.h"
#include ".\\Customers\\Proview\\vfd_proview_zyc20075_l.h"
#include ".\\Customers\\Proview\\vfd_proview_zyc20075.c"

#elif defined(DESAY_PANEL)
#include ".\\Customers\\Desay\\vfd_desay_k.h"
#include ".\\Customers\\Desay\\vfd_desay_l.h"
#include ".\\Customers\\Desay\\vfd_desay.c"

#elif defined(DESAY_PANEL98)
#include ".\\Customers\\Desay\\vfd_desay_98_k.h"
#include ".\\Customers\\Desay\\vfd_desay_98_l.h"
#include ".\\Customers\\Desay\\vfd_desay_98.c"

#elif defined(MINTON_PANEL)
#include ".\\Customers\\Minton\\vfd_minton_k.h"
#include ".\\Customers\\Minton\\vfd_minton_l.h"
#include ".\\Customers\\Minton\\vfd_minton.c"


#elif defined(MINTON_601_PANNEL)
#include ".\\Customers\\Minton\\vfd_minton601_k.h"
#include ".\\Customers\\Minton\\vfd_minton601_l.h"
#include ".\\Customers\\Minton\\vfd_minton601.c"

#elif defined(MINTON_PANEL_DVD1003)
#include ".\\Customers\\Minton\\vfd_minton_dvd1003_k.h"
#include ".\\Customers\\Minton\\vfd_minton_dvd1003_l.h"
#include ".\\Customers\\Minton\\vfd_minton_dvd1003.c"

#elif defined(MINTON_PANEL_LCD1003)
#include ".\\Customers\\Minton\\vfd_minton_lcd1003_k.h"
#include ".\\Customers\\Minton\\vfd_minton_lcd1003_l.h"
#include ".\\Customers\\Minton\\vfd_minton_lcd1003.c"

#elif defined(MINTON_PANEL_DVD1005)
#include ".\\Customers\\Minton\\vfd_minton_dvd1005_k.h"
#include ".\\Customers\\Minton\\vfd_minton_dvd1005_l.h"
#include ".\\Customers\\Minton\\vfd_minton_dvd1005.c"

#elif defined(MINTON_PANEL_DVD381)
#include ".\\Customers\\Minton\\vfd_minton_dvd38_k.h"
#include ".\\Customers\\Minton\\vfd_minton_dvd381_l.h"
#include ".\\Customers\\Minton\\vfd_minton_dvd381.c"

#elif defined(MINTON_PANEL_LCD383)
#include ".\\Customers\\Minton\\vfd_minton_lcd383_k.h"
#include ".\\Customers\\Minton\\vfd_minton_lcd383_l.h"
#include ".\\Customers\\Minton\\vfd_minton_lcdd383.c"

#elif defined(MINTON_PANEL_DVD921)
#include ".\\Customers\\Minton\\vfd_minton_dvd921_k.h"
#include ".\\Customers\\Minton\\vfd_minton_dvd921_l.h"
#include ".\\Customers\\Minton\\vfd_minton_dvd921.c"

#elif defined(MINTON_PANEL_LCD127)
#include ".\\Customers\\Minton\\vfd_minton_lcd127_k.h"
#include ".\\Customers\\Minton\\vfd_minton_lcd127_l.h"
#include ".\\Customers\\Minton\\vfd_minton_lcd127.c"

#elif defined(MINTON_PANEL_LCD301)
#include ".\\Customers\\Minton\\vfd_minton_lcd301_k.h"
#include ".\\Customers\\Minton\\vfd_minton_lcd301_l.h"
#include ".\\Customers\\Minton\\vfd_minton_lcd301.c"

#elif defined(MINTON_LCD_PANEL)
#include ".\\Customers\\Minton\\vfd_minton_lcd_k.h"
#include ".\\Customers\\Minton\\vfd_minton_lcd_l.h"
#include ".\\Customers\\Minton\\vfd_minton_lcd.c"

#elif defined(MINTON_009_PANEL)
#include ".\\Customers\\Minton\\vfd_minton_009_k.h"
#include ".\\Customers\\Minton\\vfd_minton_009_l.h"
#include ".\\Customers\\Minton\\vfd_minton_009.c"

#elif defined(LINGFENG_PANEL)   
#include ".\\Customers\\Aviq\\vfd_lingfeng_k.h" 
#include ".\\Customers\\Aviq\\vfd_lingfeng_l.h" 
#include ".\\Customers\\Aviq\\vfd_lingfeng.c"

#elif defined(IDALL_PANNEL32)
#include ".\\Customers\\IDall\\vfd_idall_32_k.h"
#include ".\\Customers\\IDall\\vfd_idall_32_l.h"
#include ".\\Customers\\IDall\\vfd_idall_32.c"

#elif defined(IDALL_PANNEL16)
#include ".\\Customers\\IDall\\vfd_idall_16_k.h"
#include ".\\Customers\\IDall\\vfd_idall_16_l.h"
#include ".\\Customers\\IDall\\vfd_idall_16.c"

#elif defined(IDALL_PANNEL14)
#include ".\\Customers\\IDall\\vfd_idall_14_k.h"
#include ".\\Customers\\IDall\\vfd_idall_14_l.h"
#include ".\\Customers\\IDall\\vfd_idall_14.c"

#elif defined(IDALL_PANNEL98)
#include ".\\Customers\\IDall\\vfd_idall_98_k.h"
#include ".\\Customers\\IDall\\vfd_idall_98_l.h"
#include ".\\Customers\\IDall\\vfd_idall_98.c"

#elif defined(EVERSTAR_PANEL)     /*YUXING_PANEL*/
#include ".\\Customers\\everstar\\vfd_everstar_k.h" 
#include ".\\Customers\\everstar\\vfd_everstar_l.h" 
#include ".\\Customers\\everstar\\vfd_everstar.c"

#elif defined(VTREK_PANNEL)
#include ".\\Customers\\vtrek\\vfd_vtrek_k.h" 
#include ".\\Customers\\vtrek\\vfd_vtrek_l.h" 
#include ".\\Customers\\vtrek\\vfd_vtrek.c"

#elif defined(VTREK_PANNEL98)
#include ".\\Customers\\vtrek\\vfd_vtrek98_k.h" 
#include ".\\Customers\\vtrek\\vfd_vtrek98_l.h" 
#include ".\\Customers\\vtrek\\vfd_vtrek98.c"

#elif defined(AVIQ_HNVC06SS91_PANNEL)	//wangfeng 2003-09-15 21:23
#include ".\\Customers\\aviq\\vfd_aviq_HNVC06SS91_k.h"
#include ".\\Customers\\aviq\\vfd_aviq_HNVC06SS91_l.h"
#include ".\\Customers\\aviq\\vfd_aviq_HNVC06SS91.c"

#elif defined(GENTEK_PANEL)
#include ".\\Customers\\gentek\\vfd_gentek_k.h"
#include ".\\Customers\\gentek\\vfd_gentek_l.h"
#include ".\\Customers\\gentek\\vfd_gentek.c"

#elif defined(INTECH_PANEL)
#include ".\\Customers\\intech\\vfd_intech_k.h"
#include ".\\Customers\\intech\\vfd_intech_l.h"
#include ".\\Customers\\intech\\vfd_intech.c"

#elif defined(INTECH_DD817_PANNEL)
#include ".\\Customers\\intech\\vfd_intech_dd817_k.h"
#include ".\\Customers\\intech\\vfd_intech_dd817_l.h"
#include ".\\Customers\\intech\\vfd_intech_dd817.c"


#elif defined(HUIFENGYUAN_PANNEL)
#include ".\\Customers\\HuiFengYuan\\vfd_huifengyuan_k.h" 
#include ".\\Customers\\HuiFengYuan\\vfd_huifengyuan_l.h" 
#include ".\\Customers\\HuiFengYuan\\vfd_huifengyuan.c"

#elif defined(HENGCHEN_PANNEL)
#include ".\\Customers\\HengChen\\vfd_hengchen_k.h" 
#include ".\\Customers\\HengChen\\vfd_hengchen_l.h" 
#include ".\\Customers\\HengChen\\vfd_hengchen.c"

#elif defined(GAODASI_PANNEL)
#include ".\\Customers\\Gaodasi\\vfd_gaodasi_k.h" 
#include ".\\Customers\\Gaodasi\\vfd_gaodasi_l.h" 
#include ".\\Customers\\Gaodasi\\vfd_gaodasi.c"

#elif defined(TCL_F60_PANNEL)      // 2004-3-22 12:40 lijd
#include ".\\Customers\\yadai\\f60_pannel\\vfd_tclf60_k.h" 
#include ".\\Customers\\yadai\\f60_pannel\\vfd_tclf60.c"     
#include ".\\Customers\\yadai\\f60_pannel\\vfd_tclf60_l.h"

#elif defined(TCL_F62_PANNEL)     // 2004-3-22 12:40 lijd
#include ".\\Customers\\yadai\\f62_pannel\\vfd_tclf62_k.h" 
#include ".\\Customers\\yadai\\f62_pannel\\vfd_tclf62.c"     
#include ".\\Customers\\yadai\\f62_pannel\\vfd_tclf62_l.h"


#elif defined(TCL_F66_PANNEL)      // 2004-3-22 12:40 lijd
#include ".\\Customers\\yadai\\f66_pannel\\vfd_tclf66_k.h" 
#include ".\\Customers\\yadai\\f66_pannel\\vfd_tclf66.c"     
#include ".\\Customers\\yadai\\f66_pannel\\vfd_tclf66_l.h"

#elif defined(TCL_F80_PANNEL)     // 2004-3-22 12:40 lijd
#include ".\\Customers\\yadai\\f80_pannel\\vfd_tclf80_k.h" 
#include ".\\Customers\\yadai\\f80_pannel\\vfd_tclf80.c"     
#include ".\\Customers\\yadai\\f80_pannel\\vfd_tclf80_l.h"

#elif defined(YADAI_PT6554_PANNEL)
#include ".\\Customers\\Yadai\\vfd_yadai_k.h" 
#include ".\\Customers\\Yadai\\vfd_yadai_l.h" 
#include ".\\Customers\\Yadai\\vfd_yadai.c"

#elif defined(XUKE_PANNEL)
#include ".\\Customers\\Xuke\\vfd_xuke_k.h" 
#include ".\\Customers\\Xuke\\vfd_xuke_l.h" 
#include ".\\Customers\\Xuke\\vfd_xuke.c"

#elif defined(HIMAGE_91_PANEL)
#include ".\\Customers\\huajia\\vfd_himage91_k.h"
#include ".\\Customers\\huajia\\vfd_himage91_l.h"
#include ".\\Customers\\huajia\\vfd_himage91.c"

#elif defined(SHANGGUANGDIAN_PANEL)
#include ".\\Customers\\Yadai\\vfd_shangguangdian_k.h"
#include ".\\Customers\\Yadai\\vfd_shangguangdian_l.h"
#include ".\\Customers\\Yadai\\vfd_shangguangdian.c"

#elif defined(SVA_PANEL)
#include ".\\Customers\\sva\\vfd_sva_k.h"
#include ".\\Customers\\sva\\vfd_sva_l.h"
#include ".\\Customers\\sva\\vfd_sva.c"

#elif defined(HARMA_PANEL)   //3-10-24 1:41张宇P
#include ".\\Customers\\HARMA\\vfd_HARMA_k.h"
#include ".\\Customers\\HARMA\\vfd_HARMA_l.h"
#include ".\\Customers\\HARMA\\vfd_HARMA.c"


#elif defined(WYD_PANEL)   //3-10-24 1:41张宇P
#include ".\\Customers\\WYD\\vfd_WYD_k.h"
#include ".\\Customers\\WYD\\vfd_WYD_l.h"
#include ".\\Customers\\WYD\\vfd_WYD.c"

#elif defined(HONGTU_PANEL)   //2003-11-25 03:56张宇P
#include ".\\Customers\\HONGTU\\vfd_HONGTU_k.h"
#include ".\\Customers\\HONGTU\\vfd_HONGTU_l.h"
#include ".\\Customers\\HONGTU\\vfd_HONGTU.c"

#elif defined(KENLOON_PANEL)   //2004-4-14 11:27张宇M
#include ".\\Customers\\KENLOON\\vfd_KENLOON_k.h"
#include ".\\Customers\\KENLOON\\vfd_KENLOON_l.h"
#include ".\\Customers\\KENLOON\\vfd_KENLOON.c"

#elif defined(KENLOON_PANEL2)   //2004/5/20 lizx
#include ".\\Customers\\KENLOON\\vfd_KENLOON_k_2.h"
#include ".\\Customers\\KENLOON\\vfd_KENLOON_l_2.h"
#include ".\\Customers\\KENLOON\\vfd_KENLOON_2.c"

#elif defined(KENLOON_PANEL3)   //2004/6/8
#include ".\\Customers\\KENLOON\\vfd_KENLOON_k_3.h"
#include ".\\Customers\\KENLOON\\vfd_KENLOON_l_3.h"
#include ".\\Customers\\KENLOON\\vfd_KENLOON_3.c"

#elif defined(TONIC_PANEL)   //2004-2-3 01:31张宇P
#include ".\\Customers\\TONIC\\vfd_TONIC_k.h"
#include ".\\Customers\\TONIC\\vfd_TONIC_l.h"
#include ".\\Customers\\TONIC\\vfd_TONIC.c"

#elif defined(SZMALATA_PANEL)   //2004-2-3 01:17张宇P
#include ".\\Customers\\SZMALATA\\vfd_SZMALATA_k.h"
#include ".\\Customers\\SZMALATA\\vfd_SZMALATA_l.h"
#include ".\\Customers\\SZMALATA\\vfd_SZMALATA.c"

#elif defined(TIANKE_PANEL)   //3-10-24 1:41张宇P
#include ".\\Customers\\TIANKE\\vfd_TIANKE_k.h"
#include ".\\Customers\\TIANKE\\vfd_TIANKE_l.h"
#include ".\\Customers\\TIANKE\\vfd_TIANKE.c"

#elif defined(P9c9_Panel)
#include ".\\Customers\\gbm\\vfd_gbm_p9ca_k.h"
#include ".\\Customers\\gbm\\vfd_gbm_p9ca_l.h"
#include ".\\Customers\\gbm\\vfd_gbm_p9ca.c"

#elif defined(WEICHENG_PANNEL)
#include ".\\Customers\\weicheng\\vfd_yux_k.h"
#include ".\\Customers\\weicheng\\vfd_yux_l.h"
#include ".\\Customers\\weicheng\\vfd_yux.c"

#elif defined(DVD288_PANNEL)
#include ".\\Customers\\yuxing\\vfd_828b_k.h"
#include ".\\Customers\\yuxing\\vfd_828b_l.h"
#include ".\\Customers\\yuxing\\vfd_828b.c"

#elif defined(SKYTECH_PANEL)
#include ".\\Customers\\skytech\\vfd_skytech_k.h"
#include ".\\Customers\\skytech\\vfd_skytech_l.h"
#include ".\\Customers\\skytech\\vfd_skytech.c"

#elif defined(MALATA_PANEL)   //2003-11-25 03:56张宇P
#include ".\\Customers\\MALATA\\vfd_MALATA_k.h"
#include ".\\Customers\\MALATA\\vfd_MALATA_l.h"
#include ".\\Customers\\MALATA\\vfd_MALATA.c"

#elif defined(NEWFUSS_PANEL)   //2003-11-25 03:56张宇P
#include ".\\Customers\\NEWFUSS\\vfd_NEWFUSS_k.h"
#include ".\\Customers\\NEWFUSS\\vfd_NEWFUSS_l.h"
#include ".\\Customers\\NEWFUSS\\vfd_NEWFUSS.c"

#elif defined(XINGWEIKE_PANEL)   //2003-12-22 wangap 
#include ".\\Customers\\XINGWEIKE\\vfd_xingweike_k.h"
#include ".\\Customers\\XINGWEIKE\\vfd_xingweike_l.h"
#include ".\\Customers\\XINGWEIKE\\vfd_xingweike.c"

#elif defined(YANGYU_PANEL)   //2003-12-23 wangap 
#include ".\\Customers\\YangYu\\vfd_yangyu_k.h"
#include ".\\Customers\\YangYu\\vfd_yangyu_l.h"
#include ".\\Customers\\YangYu\\vfd_yangyu.c"

#elif defined(ARLINK_PANEL)   //yaowh add 2005-5-29 23:30
#include ".\\Customers\\ARLINK\\vfd_arlink_k.h"
#include ".\\Customers\\ARLINK\\vfd_arlink_l.h"
#include ".\\Customers\\ARLINK\\vfd_arlink.c"

#elif defined(ALON_PANEL)   //2003-12-23 wangap 
#include ".\\Customers\\Alon\\vfd_alon_k.h"
#include ".\\Customers\\Alon\\vfd_alon_l.h"
#include ".\\Customers\\Alon\\vfd_alon.c"

#elif defined(TONGFANG_PANEL)   //2003-12-23 wangap 
#include ".\\Customers\\Tongfang\\vfd_tongfang_k.h"
#include ".\\Customers\\TongFang\\vfd_tongfang_l.h"
#include ".\\Customers\\TongFang\\vfd_tongfang.c"

#elif defined(XINDE_PANNEL)
#include ".\\Customers\\xinde\\vfd_yux_k.h" //for NINTAUS DVD-N701 key pad definition
#include ".\\Customers\\xinde\\vfd_yux_l.h"     //vfd LCD HT1611	of NINTAUS DVD-701
#include ".\\Customers\\xinde\\vfd_yux.c"	

#elif defined(HK_ORITRON_PANNEL)&&!defined(HK_ORITRON_PANNEL_RCVR)
#include ".\\Customers\\HK_Oritron\\vfd_oritron_k.h" 
#include ".\\Customers\\HK_Oritron\\vfd_oritron_l.h"
#include ".\\Customers\\HK_Oritron\\vfd_oritron.c"	

#elif defined(HK_ORITRON_PANNEL_RCVR)   //hongfeng 2005-07-09
    #if defined(ORITRON_RECEIVER_6001)
    #include ".\\Customers\\Oritron\\vfd_oritron_rcvr_6001_k.h" 
    #include ".\\Customers\\Oritron\\vfd_oritron_rcvr_6001_l.h"
    #include ".\\Customers\\Oritron\\vfd_oritron_rcvr_6001.c"   
    #elif defined(ORITRON_RECEIVER_6008)
    #include ".\\Customers\\Oritron\\vfd_oritron_rcvr_6008_k.h" 
    #include ".\\Customers\\Oritron\\vfd_oritron_rcvr_6008_l.h"
    #include ".\\Customers\\Oritron\\vfd_oritron_rcvr_6008.c"
    #elif defined(ORITRON_RECEIVER_5003)    //hongfeng add
    #include ".\\Customers\\Oritron\\vfd_oritron_rcvr_5003_k.h" 
    #include ".\\Customers\\Oritron\\vfd_oritron_rcvr_5003_l.h"
    #include ".\\Customers\\Oritron\\vfd_oritron_rcvr_5003.c"
    #elif defined(ORITRON_RECEIVER_6505)
    #include ".\\Customers\\Oritron\\vfd_oritron_rcvr_6505_k.h" 
    #include ".\\Customers\\Oritron\\vfd_oritron_rcvr_6505_l.h"
    #include ".\\Customers\\Oritron\\vfd_oritron_rcvr_6505.c"   
    #elif defined(ORITRON_RECEIVER_DPL937)
    #include ".\\Customers\\Oritron\\vfd_oritron_rcvr_dpl937_k.h" 
    #include ".\\Customers\\Oritron\\vfd_oritron_rcvr_dpl937_l.h"
    #include ".\\Customers\\Oritron\\vfd_oritron_rcvr_dpl937.c" 
    #else
	#include ".\\Customers\\Oritron\\vfd_oritron_rcvr_k.h" 
	#include ".\\Customers\\Oritron\\vfd_oritron_rcvr_l.h"
	#include ".\\Customers\\Oritron\\vfd_oritron_rcvr.c"	
    #endif

#elif defined(OP_16312_PANEL)
#include ".\\Customers\\HK_Oritron\\vfd_op_16312_l.h" 
#include ".\\Customers\\HK_Oritron\\vfd_op_16312_k.h"
#include ".\\Customers\\HK_Oritron\\vfd_op_16312.c"



#elif defined(ORITRON_PANNEL)
#include ".\\Customers\\oritron\\vfd_oritron_k.h" 
#include ".\\Customers\\oritron\\vfd_oritron_l.h"
#include ".\\Customers\\oritron\\vfd_oritron.c"	

#elif defined(D565_PANNEL)
#include ".\\Customers\\oritron\\vfd_oritron_d565_k.h" 
#include ".\\Customers\\oritron\\vfd_oritron_d565_l.h"
#include ".\\Customers\\oritron\\vfd_oritron_d565.c"	

#elif defined(ET6201_PANNEL)
#include ".\\Customers\\oritron\\vfd_oritron_et6201_k.h" 
#include ".\\Customers\\oritron\\vfd_oritron_et6201_l.h"
#include ".\\Customers\\oritron\\vfd_oritron_et6201.c"	

#elif defined(NINTAUS_PANEL)
#include ".\\Customers\\nintaus\\vfd_nintaus_k.h" 
#include ".\\Customers\\nintaus\\vfd_nintaus_l.h"
#include ".\\Customers\\nintaus\\vfd_nintaus.c"	

#elif defined(NINTAUS_6961_PANEL)
#include ".\\Customers\\nintaus\\vfd_nintaus6961_k.h" 
#include ".\\Customers\\nintaus\\vfd_nintaus6961_l.h"
#include ".\\Customers\\nintaus\\vfd_nintaus6961.c"	

#elif defined(XINGQIU_PANNEL)
#include ".\\Customers\\xingqiu\\vfd_xingqiu_k.h" 
#include ".\\Customers\\xingqiu\\vfd_xingqiu_l.h"
#include ".\\Customers\\xingqiu\\vfd_xingqiu.c"	

#elif defined(XINGQIU16_PANNEL)
#include ".\\Customers\\xingqiu\\vfd_xingqiu16_k.h" 
#include ".\\Customers\\xingqiu\\vfd_xingqiu16_l.h"
#include ".\\Customers\\xingqiu\\vfd_xingqiu16.c"	

#elif defined(XINGQIU_RECEIVER_PANNEL)//xyy 2004-2-3 10:57   For xingqiu dvd receiver
#include ".\\Customers\\xingqiu\\vfd_xingqiu_rcvr_k.h" 
#include ".\\Customers\\xingqiu\\vfd_xingqiu_rcvr_l.h"  
#include ".\\Customers\\xingqiu\\vfd_xingqiu_rcvr1.c"	

#elif defined(PANDA_13_PANEL)		//gerry,2004-3-16 0:42
#include ".\\Customers\\trenddigit\\vfd_panda_13_panel_l.h"
#include ".\\Customers\\trenddigit\\vfd_panda_13_panel_k.h"
#include ".\\Customers\\trenddigit\\vfd_panda_13_panel.c"

#elif defined(VTREK_MINI_DVDPANNEL)				//add linrc 2004-3-27 17:50
#include ".\\Customers\\vtrek\\vfd_vtrek98_mini_k.h" 
#include ".\\Customers\\vtrek\\vfd_vtrek98_mini_l.h" 
#include ".\\Customers\\vtrek\\vfd_vtrek98_mini.c"

#elif defined(SHIDELI_PANEL)		//gerry,2004-4-21 13:14
#include ".\\Customers\\shideli\\vfd_shideli_panel_l.h"
#include ".\\Customers\\shideli\\vfd_shideli_panel_k.h"
#include ".\\Customers\\shideli\\vfd_shideli_panel.c"

#elif defined(WEIKING_PANEL)
#include ".\\Customers\\weiking\\vfd_weiking_k.h" 
#include ".\\Customers\\weiking\\vfd_weiking_l.h"
#include ".\\Customers\\weiking\\vfd_weiking.c"

#elif defined(ACTIMA_PANEL)         //zhangyu  2004-9-14 09:21張宇M
#include ".\\Customers\\actima\\vfd_actima_k.h" 
#include ".\\Customers\\actima\\vfd_actima_l.h"
#include ".\\Customers\\actima\\vfd_actima.c"
#elif defined(JENGYANG_PANEL)    //liulifeng 2004-8-5 9:53
#include ".\\Customers\\jengyang\\vfd_jengyang_k.h" 
#include ".\\Customers\\jengyang\\vfd_jengyang_l.h"
#include ".\\Customers\\jengyang\\vfd_jengyang.c"

#elif defined(ORITRON_PANEL)     //xyy 2004-8-14 15:11
#include ".\\Customers\\oritron\\vfd_oritron_rcvr_k.h"
#include ".\\Customers\\oritron\\vfd_oritron_rcvr_l.h"
#include ".\\Customers\\oritron\\vfd_oritron_rcvr.c"

#elif defined(DONGQIANG_PANNEL)
#include ".\\Customers\\oritron\\vfd_dongqiang_k.h" 
#include ".\\Customers\\oritron\\vfd_dongqiang_l.h" 
#include ".\\Customers\\oritron\\vfd_dongqiang.c"

#elif defined(THAKRAL_PANEL)     //suqiaoli,2004-9-13 
#include ".\\Customers\\thakral\\vfd_thakral_k.h"
#include ".\\Customers\\thakral\\vfd_thakral_l.h"
#include ".\\Customers\\thakral\\vfd_thakral.c"

#elif defined(ATLAS_PANNEL)      //axel 2004/9/13 
#include ".\\Customers\\atlas\\vfd_atlas_k.h" 
#include ".\\Customers\\atlas\\vfd_atlas_l.h"     
#include ".\\Customers\\atlas\\vfd_atlas.c"

#elif defined(EASTECH_SHARP_PANNEL)      //axel 2004/9/13 
#include ".\\Customers\\eastech\\vfd_eastech_sharp_k.h" 
#include ".\\Customers\\eastech\\vfd_eastech_sharp_l.h"     
#include ".\\Customers\\eastech\\vfd_eastech_sharp.c"

#elif defined(EASTECH_PANNEL)       
#include ".\\Customers\\eastech\\vfd_eastech_k.h" 
#include ".\\Customers\\eastech\\vfd_eastech_l.h"     
#include ".\\Customers\\eastech\\vfd_eastech.c"

#elif defined(EASTECH_PHILIPS_PANNEL)
#include ".\\Customers\\eastech\\vfd_eastech_philips_k.h" 
#include ".\\Customers\\eastech\\vfd_eastech_philips_l.h"     
#include ".\\Customers\\eastech\\vfd_eastech_philips.c"


#elif defined(MCU_PANNEL)
#include ".\\Customers\\Sunplus\\vfd_mcusample_k.h" 
#include ".\\Customers\\Sunplus\\vfd_mcusample_l.h"  
#include ".\\Customers\\Sunplus\\vfd_mcusample.c"	

#elif defined(MCU810_PANNEL)
#include ".\\Customers\\Sunplus\\vfd_pmp_mcu810.c"	
#include ".\\Customers\\Sunplus\\vfd_pmp_mcu810_k.h"  

#elif defined(APEX_PORTABLE_PANNEL)     ////liulifeng 2005-4-29 12:45
#include ".\\Customers\\APEX_PDVD\\vfd_apex_portable.h"

#elif defined(SHINCO_PANNEL)
#include ".\\Customers\\shinco\\vfd_shinco_k.h" 
#include ".\\Customers\\shinco\\vfd_shinco_l.h"  
#include ".\\Customers\\shinco\\vfd_shinco.c"

#elif defined(MCU51_PANNEL)

#ifdef ORITRON_DVD_HT220_RECEIVER
#include ".\\Customers\\Oritron\\vfd_HT220.c"	
//#include ".\\Customers\\Oritron\\vfd_HT220_l.h" 
#include ".\\Customers\\Oritron\\vfd_HT220_k.h" 
#endif 

#elif defined(HD6928_PANNEL)//zhoulin add
#include ".\\Customers\\Oritron\\vfd_oritron_HD6928_l.h" 
#include ".\\Customers\\Oritron\\vfd_oritron_HD6928_k.h"
#include ".\\Customers\\Oritron\\vfd_oritron_HD6928.c"

#elif defined(ORITRON_1001_PANNEL)//zhoulin add
#include ".\\Customers\\Oritron\\vfd_oritron_1001_l.h" 
#include ".\\Customers\\Oritron\\vfd_oritron_1001_k.h"
#include ".\\Customers\\Oritron\\vfd_oritron_1001.c"

#elif defined(GOWELLENT_PANNEL)
#include ".\\Customers\\Gowellent\\vfd_Gowellent_l.h"
#include ".\\Customers\\Gowellent\\vfd_Gowellent_k.h"
#include ".\\Customers\\Gowellent\\vfd_Gowellent.c" 

#endif 











