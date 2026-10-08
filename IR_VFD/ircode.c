#include "user_init.h"
#include "global.h"
#include "ircode.h"
#include "irconfig.h"

//...................................................................................
#ifdef USER_SUPER_IR
#include ".\\ir_code_dir\\ircode_sunplus_8200.c"
#else
//...................................................................................

//define ircode mapping table
//this structure is defined const(in ROM), it shouldn't be included by other .c file
#ifdef IR0 //kenny 891109
#include ".\\ir_code_dir\\ircode_v.c"
#endif


#ifdef IR1 //kenny 891109
#include ".\\ir_code_dir\\ircode_m.c"
#endif

#ifdef IR2 //kenny 891109
#include ".\\ir_code_dir\\ircode_315.c"
#endif


#ifdef IR3 //kenny add it 891113
#include ".\\ir_code_dir\\ircode_p.c"
#endif

#ifdef IR4 //kenny add it 2001/1/15
#include ".\\ir_code_dir\\ircode_g.c"
#endif
 
#ifdef IR5 //chichang 900510
#include ".\\ir_code_dir\\ircode_N700.c"
#endif

#ifdef IR6 //chichang 900510
#include ".\\ir_code_dir\\ircode_n9663.c"
#endif

#ifdef IR7 //chichang 900612
#include ".\\ir_code_dir\\ircode_M168.c"
#endif

#ifdef IR8
#include ".\\ir_code_dir\\ircode_yuxing.c"
#endif

#ifdef IR9 //shawn 9101030
#include ".\\ir_code_dir\\ircode_SAMSUNG1.c"
#endif

#ifdef IR10//shawn 910220
#include ".\\ir_code_dir\\ircode_SVCD30.c"
#endif

#ifdef IR11 //shawn 910226 for Mustek_ESS dvd
#include ".\\ir_code_dir\\ircode_Mustek_ESS.c"
#endif

#ifdef IR12 //nono 2-3-24 15:53 for fuss dvd
#include ".\\ir_code_dir\\ircode_fuss.c"
#endif

#ifdef IR13
#include ".\\ir_code_dir\\ircode_huajia.c"
#endif

#ifdef IR14
#include ".\\ir_code_dir\\ircode_wangine.c"
#endif

#ifdef IR15
#include ".\\ir_code_dir\\ircode_intech.c"
#endif

#ifdef IR16
#include ".\\ir_code_dir\\ircode_jcg.c"
#endif

#ifdef IR17
#include ".\\ir_code_dir\\ircode_nextbase.c"
#endif

#ifdef IR18
#include ".\\ir_code_dir\\ircode_fuss_lide.c"
#endif

#ifdef IR19
#include ".\\ir_code_dir\\ircode_fuss_shengke.c"
#endif

#ifdef IR20
#include ".\\ir_code_dir\\ircode_fuss_sanying.c"
#endif

#ifdef IR21
#include ".\\ir_code_dir\\ircode_gaodasi.c"
#endif

#ifdef IR22
#include ".\\ir_code_dir\\ircode_gbm.c"
#endif


#ifdef IR22_GBM_HAIER
#include ".\\ir_code_dir\\ircode_gbm_haier.c"
#endif


#ifdef IR23
#include ".\\ir_code_dir\\ircode_hobo.c"
#endif

#ifdef IR24
#include ".\\ir_code_dir\\ircode_fuss_masco.c"
#endif


#ifdef IR25
#include ".\\ir_code_dir\\ircode_sva.c"
#endif

#ifdef IR26
#include ".\\ir_code_dir\\ircode_huajia_ad1200.c"
#endif

#ifdef IR27
#include ".\\ir_code_dir\\ircode_huajia_IR240.c"
#endif

#ifdef IR28
#include ".\\ir_code_dir\\ircode_wangine_IR28.c"
#endif

#ifdef IR29
#include ".\\ir_code_dir\\ircode_fuss_feiyang.c"
#endif

#ifdef IR30
#include ".\\ir_code_dir\\ircode_fuss_masco2.c"
#endif

#ifdef IR31
#include ".\\ir_code_dir\\ircode_BMT.c"
#endif

#ifdef IR32
#include ".\\ir_code_dir\\ircode_ourmind.c"
#endif

#ifdef IR33
#include ".\\ir_code_dir\\ircode_suojia.c"
#endif

#ifdef IR34
#include ".\\ir_code_dir\\ircode_huajia_2290.c"
#endif

#ifdef IR35
#include ".\\ir_code_dir\\ircode_fuss_xinqiao.c"
#endif

#ifdef IR36
#include ".\\ir_code_dir\\ircode_lucky.c"
#endif

#ifdef IR37
#include ".\\ir_code_dir\\ircode_ourmind_no_lcd.c"
#endif

#ifdef IR38
#include ".\\ir_code_dir\\ircode_fudi.c"
#endif

#ifdef IR39
#include ".\\ir_code_dir\\ircode_fudi_906g.c"
#endif

#ifdef IR40
#include ".\\ir_code_dir\\ircode_weiking_tuner.c"
#endif

#ifdef IR41
#include ".\\ir_code_dir\\ircode_fengkai.c"
#endif 

#ifdef IR42
#include ".\\ir_code_dir\\ircode_fuss_shunjian.c"
#endif

#ifdef IR43
#include ".\\ir_code_dir\\ircode_suojia_jx2002.c"
#endif 

#ifdef IR44
#include ".\\ir_code_dir\\ircode_sunplus_8200.c"
#endif 

#ifdef IR45
#include ".\\ir_code_dir\\ircode_proview.c"
#endif 

#ifdef IR46
#include ".\\ir_code_dir\\ircode_qisheng.c"
#endif 

#ifdef IR47
#include ".\\ir_code_dir\\ircode_mico.c"
#endif

#ifdef IR49
#include ".\\ir_code_dir\\ircode_gbm1.c"
#endif

#ifdef IR50
#include ".\\ir_code_dir\\ircode_KF8000x.c"
#endif 

#ifdef IR51
#include ".\\ir_code_dir\\ircode_ksd.c"
#endif 

#ifdef IR52
#include ".\\ir_code_dir\\ircode_ksd_2.c"
#endif 

#ifdef IR53        //Gordon 2003/07/28
#include ".\\ir_code_dir\\ircode_skyworth.c"
#endif 

#ifdef IR54
#include ".\\ir_code_dir\\ircode_desay.c"
#endif

#ifdef IR55
#include ".\\ir_code_dir\\ircode_minton.c"
#endif

#ifdef IR56
#include ".\\ir_code_dir\\ircode_idall.c"
#endif

#ifdef IR57     // alan, 2003/8/15 10:59PM
#include ".\\ir_code_dir\\ircode_panda.c"
#endif

#ifdef IR58
#include ".\\ir_code_dir\\ircode_himage_112w.c"
#endif

#ifdef IR66
#include ".\\ir_code_dir\\ircode_everstar.c"
#endif

#ifdef IR67
#ifdef VTREK_MINI_DVD
#include ".\\ir_code_dir\\ircode_vtrek_mini.c"
#else
#include ".\\ir_code_dir\\ircode_vtrek.c"
#endif
#endif

#ifdef IR68         //kubby,3-9-18 21:48,add for Yili
#include ".\\ir_code_dir\\ircode_aistar.c"
#endif

#ifdef IR69
#include ".\\ir_code_dir\\ircode_aviq_HNVC06SS91.c"
#endif

#ifdef IR70
#include ".\\ir_code_dir\\ircode_jieke.c"
#endif

#ifdef IR71
#include ".\\ir_code_dir\\ircode_huifengyuan.c"
#endif

#ifdef IR72
#include ".\\ir_code_dir\\ircode_hengchen.c"
#endif

#ifdef IRTCL
#include ".\\ir_code_dir\\ircode_tcl_1.c"
#endif

#ifdef IR74
#include ".\\ir_code_dir\\ircode_xuke.c"
#endif

#ifdef IR75
#include ".\\ir_code_dir\\ircode_aki.c"
#endif

#ifdef IR76
#include ".\\ir_code_dir\\ircode_bbk.c"
#endif

#ifdef IR77
#include ".\\ir_code_dir\\ircode_jieke2.c"
#endif

#ifdef IR78
#include ".\\ir_code_dir\\ircode_smt.c"
#endif
#ifdef IR79
#include ".\\ir_code_dir\\ircode_skyworth2.c"

#endif

#ifdef IR80
#include ".\\ir_code_dir\\ircode_wyd.c"

#endif

#ifdef IR81
#include ".\\ir_code_dir\\ircode_jieke3.c"
#endif

#ifdef IR82
#include ".\\ir_code_dir\\ircode_jieke4.c"
#endif

#ifdef IR83
#include ".\\ir_code_dir\\ircode_himage_dp313.c"
#endif

#ifdef IR84
#include ".\\ir_code_dir\\ircode_weicheng.c"
#endif

#ifdef IR85
#include ".\\ir_code_dir\\ircode_himage_dp316.c"
#endif

#ifdef IR86         //gerry for panda spanish order,2003-12-17 11:13
#include ".\\ir_code_dir\\ircode_panda_spanish.c"
#endif

#ifdef IR87         //gerry for panda spanish order,2003-12-17 11:13
#include ".\\ir_code_dir\\ircode_newfuss.c"
#endif

#ifdef IR89
#include ".\\ir_code_dir\\ircode_oritron.c"
#endif

#ifdef IR90
#include ".\\ir_code_dir\\ircode_gbm_portable.c"
#endif

#ifdef IR91
#include ".\\ir_code_dir\\ircode_syber.c"
#endif

#ifdef IR92
#include ".\\ir_code_dir\\ircode_syber1.c"
#endif

#ifdef IR93
#include ".\\ir_code_dir\\ircode_dss_555.c"
#endif

#ifdef IR94
#include ".\\ir_code_dir\\ircode_nintaus.c"
#endif

#ifdef IR95
#include ".\\ir_code_dir\\ircode_xingqiu.c"
#endif

#ifdef IR96
#include ".\\ir_code_dir\\ircode_dongli.c"
#endif

#ifdef IR97         //gerry for aki-eastwin,2004-2-9 16:33
#include ".\\ir_code_dir\\ircode_aki_eastwin.c"
#endif

#ifdef IR98 
#include ".\\ir_code_dir\\ircode_aistar_dvd1003.c"
#endif

#ifdef IR_GBM_2 
#include ".\\ir_code_dir\\ircode_gbm2.c"
#endif

#ifdef IR100    
#include ".\\ir_code_dir\\ircode_aistar_dvd1005.c"
#endif

#ifdef IR101    
#include ".\\ir_code_dir\\ircode_aistar_dvd381.c"
#endif


#ifdef IR102    
#include ".\\ir_code_dir\\ircode_aistar_dvd383.c"
#endif


#ifdef IR103    
#include ".\\ir_code_dir\\ircode_aistar_dvd921.c"
#endif

#ifdef IR104    
#include ".\\ir_code_dir\\ircode_aistar_dvd127.c"
#endif

#ifdef IR105    
#include ".\\ir_code_dir\\ircode_aistar_dvd301.c"
#endif

#ifdef IR106
#include ".\\ir_code_dir\\ircode_aistar_lcd1003.c"
#endif

#ifdef IR107
#include ".\\ir_code_dir\\ircode_hanyang_dvd300.c"
#endif

#ifdef IR108
#include ".\\ir_code_dir\\ircode_dv911s.c"
#endif

#ifdef IR109                    //gerry,2004-4-22 16:13
#include ".\\ir_code_dir\\ircode_shideli.c"
#endif

#ifdef DESAY_PHILIPS_IR
#include ".\\ir_code_dir\\ircode_desay_philips.c"
#endif

#ifdef IR110
#include ".\\ir_code_dir\\ircode_xingqiu_rcvr.c"
#endif

#ifdef IR111
#include ".\\ir_code_dir\\ircode_kenloon.c"
#endif

#ifdef IR112
#include ".\\ir_code_dir\\ircode_panda_6961.c"
#endif

#ifdef IR113
#include ".\\ir_code_dir\\ircode_panda_dp109.c"
#endif

#ifdef IR114
#include ".\\ir_code_dir\\ircode_argus_portable.c"
#endif

#ifdef IR115
#include ".\\ir_code_dir\\ircode_east_dp2030.c"
#endif

#ifdef IR116
#include ".\\ir_code_dir\\ircode_jengyang.c"
#endif

#ifdef IR117
#include ".\\ir_code_dir\\ircode_oritron_rcvr.c"
#endif

#ifdef IR118
#include ".\\ir_code_dir\\ircode_eastwin_8202.c"
#endif

#ifdef IR_EAST_CP8202D                  //sunzhh add for eastech CP model
#include ".\\ir_code_dir\\ircode_east_cp8202D.c"
#endif

#ifdef IR119
#include ".\\ir_code_dir\\ircode_thakral.c"
#endif

#ifdef IR120
#include ".\\ir_code_dir\\ircode_8202_receiver.c"
#endif

#ifdef IR_ALCO_PORTABLE
#include ".\\ir_code_dir\\ircode_alco_portable.c"
#endif

#ifdef IR200                                         //2004-10-19 12:00 Felix
#include ".\\ir_code_dir\\ircode_sunplus_IR200.c"
#endif

#ifdef IR201                                         //added by wangwei,2005-2-3 9:26
#include ".\\ir_code_dir\\ircode_hanyang_dvdtv.c"
#endif

#ifdef IR201S          //lixuguang     2005-4-29 20:41
#include ".\\ir_code_dir\\ircode_sunplus_IR201S.c"
#endif

#ifdef IR121        //add xrh 2004_10_28 for DP3240 remote controller
#include ".\\ir_code_dir\\ircode_east_dp3240.c"
#endif

#ifdef IR202    //2005-03-07 hongfeng new receiver ir
#include ".\\ir_code_dir\\ircode_8202_receiver_new.c"
#endif

#ifdef IR203    //liumzh 2005-5-6 13:41
#include ".\\ir_code_dir\\ircode_east_dp3181.c"
#endif

#ifdef IR_JIANLOON //zxb 2005-5-8 9:51
#include ".\\ir_code_dir\\ircode_jianloon.c"
#endif

#ifdef IR_HT220     //05-04-14 zhoulin 
#include ".\\ir_code_dir\\ircode_IR_HT220.c"
#endif

#ifdef IR_INTECH     // 2004-10-19 12:00 Felix
#include ".\\ir_code_dir\\ircode_intech.c"
#endif

#ifdef IR_WK_M3004
#include ".\\ir_code_dir\\ircode_weiking_m3004.c"
#endif

#ifdef IR_PHILIPS_EASTECH
	#include ".\\ir_code_dir\\ircode_philips_eastech.c"
#endif

#ifdef WEIKENG_SHAPEX_IR
#include "..\\Customers\\Sunplus\\ircode_weiking_tuner.c"
#endif 

#ifdef IR_ORITRON_M3004
#include ".\\ir_code_dir\\ircode_oritron_m3004.c"
#endif

#ifdef IR_HKOP_NOMCU
	#ifdef SUPPORT_RECEIVER	//hongfeng 2005-07-18
        #if defined(ORITRON_RECEIVER_6001)
        #include ".\\ir_code_dir\\ircode_oritron_m3004_no_mcu_receiver_6001.c"
        #elif defined(ORITRON_RECEIVER_6008)
            #ifdef USE_TOSHIBA
            #include ".\\ir_code_dir\\ircode_oritron_toshiba_no_mcu_receiver.c"
            #else
            #include ".\\ir_code_dir\\ircode_oritron_m3004_no_mcu_receiver_6008.c"
            #endif
        #elif defined(ORITRON_RECEIVER_6505)  //hongfeng add
        #include ".\\ir_code_dir\\ircode_oritron_m3004_no_mcu_receiver_6505.c"
        #endif
	#else
	#include ".\\ir_code_dir\\ircode_oritron_m3004_no_mcu.c"
	#endif
#endif

#ifdef WEIKENG_XINGQIU_IR
#include "..\\Customers\\Sunplus\\ircode_weiking_comdux07.c"
#endif 

#ifdef QSI_PLATFORM //qsi: merge by johnson 20040712
#include "..\\Customers\\Qsi_portable\\rc\\qsi_rc_dispatcher.c"
#endif /* QSI_PLATFORM */

#ifdef IR_TWINHAN //kehw 2005-03-30
#include ".\\ir_code_dir\\ircode_twinhan.c"
#endif

#ifdef IR_Argus_7100 //add by eric 2005-0408
#include ".\\ir_code_dir\\ircode_Argus_7100.c"
#endif

#ifdef IR_7030Demo //add by eric 2005-0420
#include ".\\ir_code_dir\\ircode_sunplus_7030Demo.c"
#endif

#ifdef IR47SL0                                         
#include ".\\ir_code_dir\\ircode_honeywld_asus.c"
#endif

#ifdef IR_WINGSUM
#include ".\\ir_code_dir\\ircode_wingsum.c"
#endif

#ifdef IR_APEX
#include ".\\Customers\\APEX_PDVD\\ircode_apex_eth1007.c"
#endif

#ifdef IR_MALATA_GPS ////frank.huang 050801
#include ".\\ir_code_dir\\ircode_malata_gps.c"
#endif

#ifdef IR_THOMSON_RCT311
#include ".\\ir_code_dir\\ircode_thomson_rct311.c"
#endif

#ifdef IR_THOMSON_RCT195
#include ".\\ir_code_dir\\ircode_thomson_rct195.c"
#endif

#ifdef IR_DVD5116
#include ".\\ir_code_dir\\ircode_oritron_5116.c"
#endif

#ifdef IR_ORITRON_M3004_RCVR   //hongfeng 2005-08-08
    #if defined(ORITRON_RECEIVER_6001)
    #include ".\\ir_code_dir\\ircode_oritron_m3004_mcu_receiver_6001.c"
    #elif defined(ORITRON_RECEIVER_6008)
    #include ".\\ir_code_dir\\ircode_oritron_m3004_mcu_receiver_6008.c"
    #endif
#endif

#ifdef IR205
#include "..\\Customers\\shinco\\ircode_shinco.c"
#endif

#ifdef IR_KM308            
#include ".\\ir_code_dir\\ircode_km308.c"
#endif

#ifdef IR_206
#include ".\\ir_code_dir\\ircode_mustek_K100D_DVB.c"
#endif

#ifdef  IR_MALATA_PORTABLE 
#include ".\\ir_code_dir\\ircode_malata_portable_dvb.c"
#endif

#ifdef IR_MTC
#include ".\\ir_code_dir\\ircode_mtc_8200.c"
#endif

#ifdef IR_ARLINK	//yaowh add 2005-12-22 9:29
#include ".\\ir_code_dir\\ircode_arlink.c"
#endif

#ifdef IR_ODT	///denghg add odt standard IR 2006-4-13 10:04
#include ".\\ir_code_dir\\ircode_odt.c"
#endif

#ifdef IR_hualu	  //lxg add for hualu IR  2006-7-18 09:04
#include ".\\ir_code_dir\\ircode_hualu.c"
#endif

#ifdef IR_INTECH_RJ     //liudan add for intech IR.
#include ".\\ir_code_dir\\ircode_intech_dd817.c"
#endif

#ifdef IR_GOWELLENT
#include ".\\ir_code_dir\\ircode_Gowellent.c"
#endif

#endif
//--------------------------------ending---------------------------------------------


