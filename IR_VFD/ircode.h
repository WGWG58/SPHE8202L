#ifndef __IRCODE_H
#define __IRCODE_H
#include "ircmd.h"
#include "user_init.h"//kenny 891109

//...................................................................................
#ifdef USER_SUPER_IR
#include ".\\ir_code_dir\\ircode_sunplus_8200.h"
#else
//...................................................................................
/*
**  IR include file 
*/
#ifdef IR0 //kenny 891109
#include ".\\ir_code_dir\\ircode_v.h"
#endif



#ifdef IR1 //kenny 891109
#include ".\\ir_code_dir\\ircode_m.h"
#endif

#ifdef IR2 //kenny 891109
#include ".\\ir_code_dir\\ircode_315.h"
#endif


#ifdef IR3 //kenny add it 891113
#include ".\\ir_code_dir\\ircode_p.h"
#endif

#ifdef IR4 //kenny add it 2001/1/15
#include ".\\ir_code_dir\\ircode_g.h"
#endif

#ifdef IR5 //chichang 900510
#include ".\\ir_code_dir\\ircode_N700.h"
#endif

#ifdef IR6 //chichang 900510
#include ".\\ir_code_dir\\ircode_n9663.h"
#endif

#ifdef IR7 //chichang 900612
#include ".\\ir_code_dir\\ircode_M168.h"
#endif

#ifdef IR8
#include ".\\ir_code_dir\\ircode_yuxing.h"
#endif

#ifdef IR9 //shawn 9101030
#include ".\\ir_code_dir\\ircode_SAMSUNG1.h"
#endif

#ifdef IR10//shawn 910220
#include ".\\ir_code_dir\\ircode_SVCD30.h"
#endif

#ifdef IR11 //shawn 910226 for Mustek_ESS dvd
#include ".\\ir_code_dir\\ircode_Mustek_ESS.h"
#endif

#ifdef IR12 //nono 2-3-24 15:53 for fuss dvd
#include ".\\ir_code_dir\\ircode_fuss.h"
#endif

#ifdef IR13
#include ".\\ir_code_dir\\ircode_huajia.h"
#endif

#ifdef IR14
#include ".\\ir_code_dir\\ircode_wangine.h"
#endif

#ifdef IR15
#include ".\\ir_code_dir\\ircode_intech.h"
#endif

#ifdef IR16
#include ".\\ir_code_dir\\ircode_jcg.h"
#endif

#ifdef IR17
#include ".\\ir_code_dir\\ircode_nextbase.h"
#endif

#ifdef IR18
#include ".\\ir_code_dir\\ircode_fuss_lide.h"
#endif

#ifdef IR19
#include ".\\ir_code_dir\\ircode_fuss_shengke.h"
#endif

#ifdef IR20
#include ".\\ir_code_dir\\ircode_fuss_sanying.h"
#endif

#ifdef IR21
#include ".\\ir_code_dir\\ircode_gaodasi.h"
#endif

#ifdef IR22
#include ".\\ir_code_dir\\ircode_gbm.h"
#endif


#ifdef IR22_GBM_HAIER
#include ".\\ir_code_dir\\ircode_gbm_haier.h"
#endif


#ifdef IR23
#include ".\\ir_code_dir\\ircode_hobo.h"
#endif

#ifdef IR24
#include ".\\ir_code_dir\\ircode_fuss_masco.h"
#endif


#ifdef IR25
#include ".\\ir_code_dir\\ircode_sva.h"
#endif

#ifdef IR26
#include ".\\ir_code_dir\\ircode_huajia_ad1200.h"
#endif

#ifdef IR27
#include ".\\ir_code_dir\\ircode_huajia_IR240.h"
#endif

#ifdef IR28
#include ".\\ir_code_dir\\ircode_wangine_IR28.h"
#endif

#ifdef IR29
#include ".\\ir_code_dir\\ircode_fuss_feiyang.h"
#endif

#ifdef IR30
#include ".\\ir_code_dir\\ircode_fuss_masco2.h"
#endif

#ifdef IR31
#include ".\\ir_code_dir\\ircode_BMT.h"
#endif

#ifdef IR32
#include ".\\ir_code_dir\\ircode_ourmind.h"
#endif
//#include ".\\ir_code_dir\\ircode_t.h"
//#include ".\\ir_code_dir\\ircode_49.h"

#ifdef IR33
#include ".\\ir_code_dir\\ircode_suojia.h"
#endif

#ifdef IR34
#include ".\\ir_code_dir\\ircode_huajia_2290.h"
#endif

#ifdef IR35
#include ".\\ir_code_dir\\ircode_fuss_xinqiao.h"
#endif

#ifdef IR36
#include ".\\ir_code_dir\\ircode_lucky.h"
#endif

#ifdef IR37
#include ".\\ir_code_dir\\ircode_ourmind_no_lcd.h"
#endif

#ifdef IR38
#include ".\\ir_code_dir\\ircode_fudi.h"
#endif

#ifdef IR39
#include ".\\ir_code_dir\\ircode_fudi_906g.h"
#endif

#ifdef IR40
#include ".\\ir_code_dir\\ircode_weiking_tuner.h"
#endif 

#ifdef IR41
#include ".\\ir_code_dir\\ircode_fengkai.h"
#endif

#ifdef IR42
#include ".\\ir_code_dir\\ircode_fuss_shunjian.h"
#endif

#ifdef IR43
#include ".\\ir_code_dir\\ircode_suojia_jx2002.h"
#endif

#ifdef IR44
#include ".\\ir_code_dir\\ircode_sunplus_8200.h"
#endif

#ifdef IR45
#include ".\\ir_code_dir\\ircode_proview.h"
#endif

#ifdef IR46
#include ".\\ir_code_dir\\ircode_qisheng.h"
#endif

#ifdef IR47
#include ".\\ir_code_dir\\ircode_mico.h"
#endif


#ifdef IR49
#include ".\\ir_code_dir\\ircode_gbm1.h"
#endif

#ifdef IR50
#include ".\\ir_code_dir\\ircode_KF8000x.h" //for PROVIEW KF-8000 remote controller
#endif

#ifdef IR51
#include ".\\ir_code_dir\\ircode_ksd.h"
#endif 

#ifdef IR52
#include ".\\ir_code_dir\\ircode_ksd_2.h"
#endif 

#ifdef IR53                    //Gordon 2003/07/28
#include ".\\ir_code_dir\\ircode_skyworth.h"
#endif  

#ifdef IR54
#include ".\\ir_code_dir\\ircode_desay.h"
#endif

#ifdef IR55
#include ".\\ir_code_dir\\ircode_minton.h"
#endif

#ifdef IR56
#include ".\\ir_code_dir\\ircode_idall.h"
#endif

#ifdef IR57     // alan, 2003/8/15 10:58PM
#include ".\\ir_code_dir\\ircode_panda.h"
#endif

#ifdef IR58
#include ".\\ir_code_dir\\ircode_himage_112w.h"
#endif
    
#ifdef IR66
#include ".\\ir_code_dir\\ircode_everstar.h"
#endif
    
#ifdef IR67
#ifdef VTREK_MINI_DVD
#include ".\\ir_code_dir\\ircode_vtrek_mini.h"
#else
#include ".\\ir_code_dir\\ircode_vtrek.h"
#endif
#endif
    
#ifdef IR68         //kubby,3-9-18 21:48,add for Yili
#include ".\\ir_code_dir\\ircode_aistar.h"
#endif  
    
#ifdef IR69
#include ".\\ir_code_dir\\ircode_aviq_HNVC06SS91.h"
#endif

#ifdef IR70
#include ".\\ir_code_dir\\ircode_jieke.h"
#endif

#ifdef IR71
#include ".\\ir_code_dir\\ircode_huifengyuan.h"
#endif

#ifdef IR72
#include ".\\ir_code_dir\\ircode_hengchen.h"
#endif

#ifdef IRTCL
#include ".\\ir_code_dir\\ircode_tcl_1.h"
#endif

#ifdef IR74
#include ".\\ir_code_dir\\ircode_xuke.h"
#endif

#ifdef IR75
#include ".\\ir_code_dir\\ircode_aki.h"
#endif

#ifdef IR76
#include ".\\ir_code_dir\\ircode_bbk.h"
#endif

#ifdef IR77
#include ".\\ir_code_dir\\ircode_jieke2.h"
#endif

#ifdef IR78
#include ".\\ir_code_dir\\ircode_smt.h"
#endif

#ifdef IR79
#include ".\\ir_code_dir\\ircode_skyworth2.h"
#endif

#ifdef IR80
#include ".\\ir_code_dir\\ircode_wyd.h"
#endif

#ifdef IR81
#include ".\\ir_code_dir\\ircode_jieke3.h"
#endif

#ifdef IR82
#include ".\\ir_code_dir\\ircode_jieke4.h"
#endif

#ifdef IR83
#include ".\\ir_code_dir\\ircode_himage_dp313.h"
#endif

#ifdef IR84
#include ".\\ir_code_dir\\ircode_weicheng.h"
#endif

#ifdef IR85
#include ".\\ir_code_dir\\ircode_himage_dp316.h"
#endif

#ifdef IR86         //gerry for panda spanish order,2003-12-17 11:13
#include ".\\ir_code_dir\\ircode_panda_spanish.h"
#endif

#ifdef IR87         //gerry for panda spanish order,2003-12-17 11:13
#include ".\\ir_code_dir\\ircode_newfuss.h"
#endif

#ifdef IR89
#include ".\\ir_code_dir\\ircode_oritron.h"
#endif

#ifdef IR90
#include ".\\ir_code_dir\\ircode_gbm_portable.h"
#endif

#ifdef IR91
#include ".\\ir_code_dir\\ircode_syber.h"
#endif

#ifdef IR92
#include ".\\ir_code_dir\\ircode_syber1.h"
#endif

#ifdef IR93
#include ".\\ir_code_dir\\ircode_dss_555.h"
#endif

#ifdef IR94
#include ".\\ir_code_dir\\ircode_nintaus.h"
#endif

#ifdef IR95
#include ".\\ir_code_dir\\ircode_xingqiu.h"
#endif

#ifdef IR96
#include ".\\ir_code_dir\\ircode_dongli.h"
#endif

#ifdef IR97         //gerry for aki-eastwin,2004-2-9 16:33
#include ".\\ir_code_dir\\ircode_aki_eastwin.h"
#endif

#ifdef IR98 
#include ".\\ir_code_dir\\ircode_aistar_dvd1003.h"
#endif

#ifdef IR_GBM_2 
#include ".\\ir_code_dir\\ircode_gbm2.h"
#endif
#ifdef IR100    
#include ".\\ir_code_dir\\ircode_aistar_dvd1005.h"
#endif

#ifdef IR101    
#include ".\\ir_code_dir\\ircode_aistar_dvd381.h"
#endif


#ifdef IR102    
#include ".\\ir_code_dir\\ircode_aistar_dvd383.h"
#endif


#ifdef IR103    
#include ".\\ir_code_dir\\ircode_aistar_dvd921.h"
#endif

#ifdef IR104    
#include ".\\ir_code_dir\\ircode_aistar_dvd127.h"
#endif

#ifdef IR105    
#include ".\\ir_code_dir\\ircode_aistar_dvd301.h"
#endif

#ifdef IR106
#include ".\\ir_code_dir\\ircode_aistar_lcd1003.h"
#endif

#ifdef IR107
#include ".\\ir_code_dir\\ircode_hanyang_dvd300.h"
#endif

#ifdef IR108
#include ".\\ir_code_dir\\ircode_dv911s.h"
#endif

#ifdef IR109
#include ".\\ir_code_dir\\ircode_shideli.h"
#endif

#ifdef DESAY_PHILIPS_IR
#include ".\\ir_code_dir\\ircode_desay_philips.h"
#endif

#ifdef IR110
#include ".\\ir_code_dir\\ircode_xingqiu_rcvr.h"
#endif

#ifdef IR111
#include ".\\ir_code_dir\\ircode_kenloon.h"
#endif

#ifdef IR112
#include ".\\ir_code_dir\\ircode_panda_6961.h"
#endif

#ifdef IR113
#include ".\\ir_code_dir\\ircode_panda_dp109.h"
#endif

#ifdef IR114
#include ".\\ir_code_dir\\ircode_argus_portable.h"
#endif


#ifdef IR115
#include ".\\ir_code_dir\\ircode_east_dp2030.h"
#endif

#ifdef IR116
#include ".\\ir_code_dir\\ircode_jengyang.h"
#endif

#ifdef IR117
#include ".\\ir_code_dir\\ircode_oritron_rcvr.h"
#endif

#ifdef IR118
#include ".\\ir_code_dir\\ircode_eastwin_8202.h"
#endif

#ifdef IR_EAST_CP8202D                 //sunzhh add for eastech CP model
#include ".\\ir_code_dir\\ircode_east_cp8202D.h"
#endif

#ifdef IR119
#include ".\\ir_code_dir\\ircode_thakral.h"
#endif

#ifdef IR120
#include ".\\ir_code_dir\\ircode_sunplus_8200.h"
#endif


#ifdef IR_ALCO_PORTABLE
#include ".\\ir_code_dir\\ircode_alco_portable.h"
#endif

#ifdef IR200     // 2004-10-19 12:00 Felix
#include ".\\ir_code_dir\\ircode_sunplus_IR200.h"
#endif

#ifdef IR201                                         //added by wangwei,2005-2-3 9:26
#include ".\\ir_code_dir\\ircode_hanyang_dvdtv.h"
#endif

#ifdef IR201S                //lixuguang   ,  2005-4-29 20:41
#include ".\\ir_code_dir\\ircode_sunplus_IR201S.h"
#endif

#ifdef IR121 //add xrh 2004_10_28 for DP3240 remote controller
#include ".\\ir_code_dir\\ircode_east_dp3240.h"
#endif

#ifdef IR202     // 2004-03-07 new receiver ir hongfeng
#include ".\\ir_code_dir\\ircode_sunplus_IR200.h"
#endif

#ifdef IR203    //liumzh 2005-5-6 13:41
#include ".\\ir_code_dir\\ircode_east_dp3181.h"
#endif

#ifdef IR_JIANLOON //zxb 2005-5-8 9:51
#include ".\\ir_code_dir\\ircode_jianloon.h"
#endif

#ifdef IR_HT220    //05-04-14 zhoulin
#include ".\\ir_code_dir\\ircode_IR_HT220.h"
#endif

#ifdef IR_INTECH     // 2004-10-19 12:00 Felix
#include ".\\ir_code_dir\\ircode_intech.h"
#endif

#ifdef IR_WK_M3004
#include ".\\ir_code_dir\\ircode_weiking_m3004.h"
#endif

#ifdef WEIKENG_SHAPEX_IR
#include "..\\Customers\\Sunplus\\ircode_weiking_tuner.h"
#endif 

#ifdef IR_PHILIPS_EASTECH
	#include ".\\ir_code_dir\\ircode_philips_eastech.h"
#endif


#ifdef IR_ORITRON_M3004
#include ".\\ir_code_dir\\ircode_oritron_m3004.h"
#endif

#ifdef IR_HKOP_NOMCU
	#ifdef SUPPORT_RECEIVER	//hongfeng 2005-07-18
	    #ifdef USE_TOSHIBA
	    #include ".\\ir_code_dir\\ircode_oritron_toshiba_no_mcu_receiver.h"
	    #else
		#include ".\\ir_code_dir\\ircode_oritron_m3004_no_mcu_receiver.h"
	    #endif
	#else
	#include ".\\ir_code_dir\\ircode_oritron_m3004_no_mcu.h"
	#endif
#endif

#ifdef WEIKENG_XINGQIU_IR
#include "..\\Customers\\Sunplus\\ircode_weiking_comdux07.h"
#endif 

#ifdef QSI_PLATFORM //qsi: merge by johnson 20040712

#ifdef IRQSI_RC_51SM0_093A
#include ".\\ir_code_qsi\\ircode_qsi_RC_51SM0_093A.h"
#elif  defined(IRQSI_RC_51SM1_488A)
#include ".\\ir_code_qsi\\ircode_qsi_RC_51SM1_488A.h"
#else
//#error "Can't find remoter that is supported by QSI." 
#endif

#endif /* QSI_PLATFORM */

#ifdef IR_TWINHAN //kehw 2005-03-30
#include ".\\ir_code_dir\\ircode_twinhan.h"
#endif

#ifdef IR_Argus_7100 //add by eric 2005-0408
#include ".\\ir_code_dir\\ircode_Argus_7100.h"
#endif

#ifdef IR_7030Demo //add by eric 2005-0420
#include ".\\ir_code_dir\\ircode_sunplus_7030Demo.h"
#endif

#ifdef IR47SL0
#include ".\\ir_code_dir\\ircode_honeywld_asus.h"
#endif

#ifdef IR_WINGSUM
#include ".\\ir_code_dir\\ircode_wingsum.h"
#endif

#ifdef IR_APEX
#include ".\\Customers\\APEX_PDVD\\ircode_apex_eth1007.h"
#endif

#ifdef IR_MALATA_GPS //frank.huang 050801
#include ".\\ir_code_dir\\ircode_malata_gps.h"
#endif


#ifdef IR_ORITRON_M3004_RCVR   //hongfeng 2005-08-08
#include ".\\ir_code_dir\\ircode_oritron_m3004_mcu_receiver.h"
#endif

#ifdef IR_DVD5116
#include ".\\ir_code_dir\\ircode_oritron_5116.h"
#endif

#ifdef IR205
#include "..\\Customers\\shinco\\ircode_shinco.h"
#endif

#ifdef IR_206
#include ".\\ir_code_dir\\ircode_mustek_K100D_DVB.h"
#endif

#ifdef IR_KM308
#include ".\\ir_code_dir\\ircode_km308.h"
#endif

#ifdef IR_MTC
#include ".\\ir_code_dir\\ircode_mtc_8200.h"
#endif


#ifdef  IR_MALATA_PORTABLE 
#include ".\\ir_code_dir\\ircode_malata_portable_dvb.h"
#endif

#ifdef IR_ARLINK	//yaowh add 2005-12-22 9:29
#include ".\\ir_code_dir\\ircode_arlink.h"
#endif

#ifdef IR_ODT	//denghg add odt standard IR 2006-4-13 10:04
#include ".\\ir_code_dir\\ircode_odt.h"
#endif

#ifdef IR_hualu	  //lxg add for hualu IR  2006-7-18 09:04
#include ".\\ir_code_dir\\ircode_hualu.h"
#endif

#ifdef IR_INTECH_RJ     //liudan add for intech IR.
#include ".\\ir_code_dir\\ircode_intech_dd817.h"
#endif

#ifdef IR_GOWELLENT
#include ".\\ir_code_dir\\ircode_Gowellent.h"
#endif

#endif
//user super ir .........................................................

#define MAX_IR_MAP sizeof(ir_mapcode)
extern const IRFUNC irc_func_table[];

//ir.c ircmd direction table
extern const IRCMDFUNC ircmd_left_table[];
extern const IRCMDFUNC ircmd_right_table[];
extern const IRCMDFUNC ircmd_up_table[];
extern const IRCMDFUNC ircmd_down_table[];
extern const IRCMDFUNC ircmd_clear_table[];
extern const IRCMDFUNC ircmd_select_table[];
#endif







