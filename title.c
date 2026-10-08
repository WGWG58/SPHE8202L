/* alan 2002-05-02 modified for differenrt customer with different title */

#include "user_init.h"

#if defined(GENERAL_DVD)

    #if defined(SUPPORT_6500)
        #include ".\\Customers\\general\\title_6500.c"
    #elif defined(DVB_DVD_8202)
        #include ".\\Customers\\general\\title_dvddvb.c"
    #elif defined(GENERAL_8202L_16_DVD)||defined(GENERAL_8202L_64_DVD)||defined(GENERAL_8202L_16_040_DVD)||defined(GENERAL_8202L_16_040_NO_MP4)||defined(GENERAL_8202L_32_DVD)
        #include ".\\Customers\\general\\title_8202L.c"
    #elif defined(GENERAL_8202E_DVD)
            #include ".\\Customers\\general\\title_8202e.c"
    #elif defined(GENERAL_8202S_DVD)||defined(GENERAL_8202S_16_DVD)
        #include ".\\Customers\\general\\title_8202s.c"
   #elif defined(GENERAL_8202D_DVD)||defined(GENERAL_8202D_16_DVD)||defined(GENERAL_8202D_16_040_NO_MP4)||defined(GENERAL_PORTABLE_DVD_8202D)
            #include ".\\Customers\\general\\title_8202d.c"            
    #else
        #if defined(SPHE8202)||defined(GENERAL_8202M_A_DVD)||defined(GENERAL_8202M_B_DVD)
            #include ".\\Customers\\general\\title_modify1.c"
        #else
            #include ".\\Customers\\general\\title_sunplus.c"
        #endif
    #endif
    
//#include ".\\Customers\\general\\title_whitelogo.c"
//#include ".\\Customers\\general\\title_dvdlogo.c"
#elif defined(SAMBOO_HDDPLAYER_DVD)
#include ".\\Customers\\samboo\\title_PMP3.c"

#elif defined(SUNPLUS_DVD)
    #ifdef CD_PLAYER
    #include ".\\Customers\\Sunplus\\title_sunplus_cd_player.c"
    #elif defined(SUPPORT_HD_DVD)
    #include ".\\Customers\\Sunplus\\title_6500.c"
    #elif defined(SPHE8202)        
        #if defined(IC_8202E)
            #include ".\\Customers\\Sunplus\\title_8202e.c"
        #elif defined (CUSTOMERS_8104_CD) //axel 2005/3/25
            #include ".\\Customers\\Sunplus\\title_8104.c"
        #elif defined(CUSTOMERS_8202S_DVD)||defined(CUSTOMERS_8202S_16_DVD)||defined(CUSTOMERS_8202A_256_DVD)
            #include ".\\Customers\\Sunplus\\title_8202s.c"
        #elif defined(CUSTOMERS_8202D_DVD)||defined(CUSTOMERS_8202D_16_DVD)||defined(CUSTOMERS_8202D_256_DVD)||defined(CUSTOMERS_PORTABLE_DVD_8202D)||defined(CUSTOMERS_8202D_16_040_NO_MP4)//terry,2005/6/22 10:24と
            #include ".\\Customers\\Sunplus\\title_8202d.c"            
        #elif defined(CUSTOMERS_8202L_16_DVD) || defined(CUSTOMERS_8202L_32_DVD) || defined(CUSTOMERS_8202L_64_DVD) || defined(CUSTOMERS_PORTABLE_DVD_8202L_64)||defined(CUSTOMERS_8202L_16_040_NO_MP4)
            #include ".\\Customers\\Sunplus\\title_8202l.c"   
        #elif defined(CUSTOMERS_8202D_16_040_DVD) || defined (CUSTOMERS_8104_16_CD)||defined(CUSTOMERS_8202L_16_040_DVD) //terry,2005/4/4 05:24と           
            #include ".\\Customers\\Sunplus\\title_whitelogo.c"                
        #elif defined(DVB_DVD_8202)  ///yangli mod,2006-6-22 10:44
            #include ".\\Customers\\Sunplus\\title_dvddvb.c"          
        #elif defined(PMP_UI)//liweihua mod 2005-3-16
            #ifdef SUPPORT_PMP_COPY
            #include ".\\Customers\\Sunplus\\title_PMP1.c"
            #elif defined(HDD_PLAYER)//liweihua 2005-3-25
            #include ".\\Customers\\Sunplus\\title_PMP3.c"
            #else
            #include ".\\Customers\\Sunplus\\title_PMP2.c"
            #endif
        #elif defined(MAKE_ONLY_UPDATE_CODE)
		//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
    		#include ".\\Customers\\Sunplus\\title_whitelogo.c"    
		#elif defined(CUSTOMERS_1002_16_DVD)
			#include ".\\Customers\\Sunplus\\title_8202l.c"
        #else
            #include ".\\Customers\\Sunplus\\title_modify1.c"
            //#include ".\\Customers\\Sunplus\\title_whitelogo.c"
        #endif    
    #elif defined(SPHE1000)
    //#include ".\\Customers\\Sunplus\\title_sunplus_stb.c"
    #include ".\\Customers\\Sunplus\\title_whitelogo.c"
    #else
        #include ".\\Customers\\Sunplus\\title_sunplus.c"
        //#include ".\\Customers\\Sunplus\\title_whitelogo.c"
//#include ".\\Customers\\Sunplus\\title_abstract.c"
//#include ".\\Customers\\Sunplus\\title_modify1.c"
//#include ".\\Customers\\Sunplus\\title_dvdvideo.c"
//#include ".\\Customers\\Sunplus\\title_player.c"
//#include ".\\Customers\\Sunplus\\title_simple.c"
    #endif
 #ifdef LOGO_PLAY_MP3
  #include ".\\Customers\\Sunplus\\logo_mp3.c"
 #endif 
#elif defined(YUXING_DVD)
#include ".\\Customers\\Yuxing\\title_yuxing.c"
#elif defined(YUXING_MIDI_DVD)//xlluo add 04-6-11
#include ".\\Customers\\Yuxing\\title_yuxing.c"
#elif defined(SANJING_MIDI_DVD)//ouyang 2005-01-27
#include ".\\Customers\\Sanjing\\title_sanjing.c"
#elif defined(SAMSUNG1_DVD)
#include ".\\Customers\\Sunplus\\title_sunplus.c"
#elif defined(SKYWORTH_DVD)
#include ".\\Customers\\SkyWorth\\title.c"

#elif defined(SKYTECH_DVD)
#include ".\\Customers\\Skytech\\title_skytech.c"

#elif defined(HUALU_DVD)  // lxg 2006-7-18 09:52
#include ".\\Customers\\hualu\\title_8202l.c" 
#elif defined(NINTAUS_DVD)
#include ".\\Customers\\nintaus\\title_nintaus.c"
#elif defined(NINTAUS_MIDI_DVD)
#include ".\\Customers\\nintaus\\title_nintaus.c"

#elif defined(ZhengTai_DVD)
#include ".\\Customers\\ZhengTai\\title_zhengtai.c"

#elif defined(HARMA_DVD)
#include ".\\Customers\\HARMA\\title_harma.c"

#elif defined(ACTIMA_DVD)   //2004-9-14 09:25zhangyuM
#include ".\\Customers\\actima\\title_actima.c"

#elif defined(HANYANG_DVD)   //CAOH 2004-4-6 16:54
    #ifdef HANYANG_DP02CD_WF_LOGO//added by wangwei,2005-2-4 11:25
    #include ".\\Customers\\HANYANG\\title_hanyang_dp02cd_wf_117k.c"
    #elif defined(HANYANG_WHITE_LOGO)
    #include ".\\Customers\\Sunplus\\title_whitelogo.c"
    #else
#include ".\\Customers\\HANYANG\\title_HANYANG.c"
    #endif

#elif defined(ARGUS_PORTABLE_DVD)
#include ".\\Customers\\argus_portable\\title_argusportable.c"

#elif defined(MUSTEK_PORTABLE_DVD)

#ifdef MUSTEK_K100D_MODEL
//#include ".\\Customers\\Sunplus\\title_dvddvb.c"
#include ".\\Customers\\Mustek_portable\title_mustek_k100d.c"
#else
#include ".\\Customers\\mustek_portable\\title_mustek.c"
#endif
            
#elif defined(TIANKE_DVD)
#include ".\\Customers\\TIANKE\\title_TIANKE.c"
#elif defined(GAODASI_DVD)
#include ".\\Customers\\Gaodasi\\title_gaodasi.c"

#elif defined(WYD_DVD)
#include ".\\Customers\\WYD\\title_WYD.c"

#elif defined(INTECH_DVD)
#include ".\\Customers\\intech\\title_intech.c"

#elif defined(LINKCONCEPT_DVD)
#include ".\\Customers\\linkconcept\\title_linkconcept.c"

#elif defined(HONGTU_DVD)  //2003-11-25 03:58张宇P
#include ".\\Customers\\HONGTU\\title_HONGTU.c"

#elif defined(KENLOON_DVD)  //2004-4-14 11:28张宇M
#include ".\\Customers\\KENLOON\\title_KENLOON.c"

#elif defined(SZMALATA_DVD)  //2003-11-25 03:58张宇P
#include ".\\Customers\\SZMALATA\\title_SZMALATA.c"

#elif defined(TONIC_DVD)  //2003-11-25 03:58张宇P
#include ".\\Customers\\TONIC\\title_TONIC.c"

#elif defined(TONIC_DVD_DTH109)  //zhongshan 05/07/07

#include ".\\Customers\\TONIC\\title_thomson.c"


#elif defined(MALATA_DVD)  //2003-11-25 03:58张宇P
#include ".\\Customers\\MALATA\\title_MALATA.c"

#elif defined(NEWFUSS_DVD)  //2003-11-25 03:58张宇P
#include ".\\Customers\\NEWFUSS\\title_NEWFUSS.c"

#elif defined(AKI_DVD)                 // fengjl 03/10/18  for chuangying
//#include ".\\Customers\\Aki\\title_aki.c"
//#include ".\\Customers\\Aki\\title_soundLAB.c"
//#include ".\\Customers\\Aki\\title_xpublic.c"
//#include ".\\Customers\\Aki\\title_comet.c"       //B004-46 DVD-838J0 2004-5-14
//#include ".\\Customers\\Aki\\title_ATD.c"
//#include ".\\Customers\\Aki\\title_hisense.c"     //b004-30
//#include ".\\Customers\\Aki\\title_Rex.c"
//#include ".\\Customers\\Aki\\title_midi.c"        //b004-31-32
//#include ".\\Customers\\Aki\\title_scott.c"
//#include ".\\Customers\\Aki\\title_common.c"
#include ".\\Customers\\Aki\\title_commom_3d.c"     //new 3d dvd-video mark 2004-4-8 for new software aki-009 1.02.03
//#include ".\\Customers\\Aki\\title_7line.c"               //p0403-46-05
//#include ".\\Customers\\Aki\\title_TRANS2.c"      //102 by lyl 2003-12-13
//#include ".\\Customers\\Aki\\title-airis.c"       //2003-12-19    BOO4-19-868V60 xe0404-192-108
//#include ".\\Customers\\Aki\\title_aki10.c"       //2003-12-23
//#include ".\\Customers\\Aki\\title_PROSON.c"      //2003-12-23
//#include ".\\Customers\\Aki\\title_auvion_1.c"        //2004-2-6
//#include ".\\Customers\\Aki\\title_bluetech.c"        //2004-2-15
//#include ".\\Customers\\Aki\\title_foston25.c"        //2004-2-18
//#include ".\\Customers\\Aki\\title_talent.c"      //2004-2-18
//#include ".\\Customers\\Aki\\title_dixon.c"       //2004-2-21 b004-45
//#include ".\\Customers\\Aki\\title_akilucky2.c"       //2004-2-25 p0402-35-22
//#include ".\\Customers\\Aki\\title_microo.c"      //2004-2-25 p0402-38-25
//#include ".\\Customers\\Aki\\title_daewoo.c"      //2004-3-7  b004-16
//#include ".\\Customers\\Aki\\title_cobra.c"       //2004-3-12 p0403-44-03
//#include ".\\Customers\\Aki\\title_midi.c"        //2004-3-17     c04-006
//#include ".\\Customers\\Aki\\title_everytop.c"        //2004-3-19     p0403-48-07
//#include ".\\Customers\\Aki\\title_lenoxx.c"      //2004-3-24     b004-05
//#include ".\\Customers\\Aki\\title_vitek.c"       //2004-3-24     b004-07-08
//#include ".\\Customers\\Aki\\title_xoro.c"        //2004-3-27     b004-13
//#include ".\\Customers\\Aki\\title_tcl.c"     //2004-3-30     xe0403-137(138)-53(54)
//#include ".\\Customers\\Aki\\title_digix.c"       //2004-4-6 xe0403-164(165)-80()81
//#include ".\\Customers\\Aki\\title_karcher.c"     //2004-4-17 xe0404-191-107
//#include ".\\Customers\\Aki\\title_comet.c"       //2004-4-17 xe0404-194-110  b004-46
//#include ".\\Customers\\Aki\\title_citizen.c"     // b004-26 
//#include ".\\Customers\\Aki\\title_ELECTR_1.c"        //2004-4-28 2004-4-15 b004-38
//#include ".\\Customers\\Aki\\title_daytek.c"      //2004-5-11 xe0405-258-259-260-174-175-176
//#include ".\\Customers\\Aki\\title_tosumi.c"      //2004-5-11 b004-41
//#include ".\\Customers\\Aki\\title_bots.c"            //2004-5-14 b004-36     

#elif defined(BBK_DVD)                        // fengjl 03/10/17
    #ifdef BBK_DSS_555_DVD
    #include ".\\Customers\\Bbk\\title_phico.c" 
    #elif defined(BBK_DV911S)               
    #include ".\\Customers\\Bbk\\title_bbk_en.c"
    #else                
    #include ".\\Customers\\Bbk\\title_bbk_ch.c"
    #endif
#elif defined(SMT_DVD)                        // fengjl 3-10-28 21:36

    #ifdef UPXUS_LOGO   //fengjl edit 2004-07-07 09:59
        #include ".\\Customers\\Smt\\title_upxus.c"
    #elif defined(SMT_LOGO)
        #include ".\\Customers\\Smt\\title_smt.c"
    #elif defined(COMMON_LOGO)
        #include ".\\Customers\\Smt\\title_common.c" 
    #elif defined(TRT_LOGO)
        #include ".\\Customers\\Smt\\title_trt.c"
    #else 
        #include ".\\Customers\\Smt\\title.c"
    #endif

#elif defined(MUSTEK_DVD)
#include ".\\Customers\\Mustek\\title_mustek.c"
#elif defined(ATLAS_DVD)
#include ".\\Customers\\atlas\\title_atlas.c"

#elif defined(FUSS_DVD)

#ifdef FUSS_LIDE_DVD//for fuss_lide_dvd 02-07-02
#include ".\\Customers\\Fuss\\Lide\\title_fuss_lide.c"
#elif defined(FUSS_SHENGKE_DVD)
#include ".\\Customers\\Fuss\\shengke\\title_fuss_shengke.c"
#elif defined(FUSS_SANYING_DVD)
#include ".\\Customers\\Fuss\\Sanying\\title_fuss_sanying.c"
#elif defined(FUSS_MASCO_DVD)
#include ".\\Customers\\Fuss\\masco\\title_fuss_masco.c"
#elif defined(FUSS_XINQIAO_DVD)
#include ".\\Customers\\Fuss\\xinqiao\\title_fuss_xinqiao.c"
#elif defined(FUSS_SHUNJIAN_DVD)
#include ".\\Customers\\Fuss\\shunjian\\title_fuss_shunjian.c"
#else
#include ".\\Customers\\Fuss\\title_fuss.c"
#endif

#elif defined(HUAJIA_DVD)

#if defined(DOUBLE_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_2logo.c"
#elif defined(CENTRIOS_LOGO)     //04-100w
#include ".\\Customers\\Huajia\\title_huajia_centrios.c"
#elif defined(DWW_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_dww.c"
#elif defined(NIKENNY_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_nikenny.c"
#elif defined(GOTECH_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_gotech.c"
#elif defined(ENGLISH_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en.c"
#elif defined(BESTBUY_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_bestbuy.c"
#elif defined(ENGLISH_AHISHI_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_akishi.c"
#elif defined(ENGLISH_WHOUSE_LOGO)//white westinghouse S700
#include ".\\Customers\\Huajia\\title_huajia_en_white.c"
#elif defined(PALAZZO_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_palazzo.c"
#elif defined(ENGLISH_PROSOUND_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_prosound.c"
#elif defined(ENG_MAXIM_LOGO)//huajia maxim logo
#include ".\\Customers\\Huajia\\title_huajia_en_maxim.c"
#elif defined(DVD_LOGO)//huajia non-customer's logo
#include ".\\Customers\\Huajia\\title_huajia_dvdlogo.c"
#elif defined(DVD_NEW_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_dvd.c"
#elif defined(ENGLISH_SV_LOGO)//huajia smartvision logo
#include ".\\Customers\\Huajia\\title_huajia_en_sv.c"//02-077w
#elif defined(ENG_METZ_LOGO)//02-081w
#include ".\\Customers\\Huajia\\title_huajia_en_metz.c"
#elif defined(RDPLOGO)//02-084w
#include ".\\Customers\\Huajia\\title_huajia_en_rdp.c"
#elif defined(CANADA_CUS_LOGO)//huajia canada-customer's logo//electrohome logo
#include ".\\Customers\\Huajia\\title_huajia_en_canada.c"
#elif defined(ELEKTA_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_elekta.c"
#elif defined(AKAI_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_akai.c"
#elif defined(AKAI_NEW_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_akai.c"
#elif defined(DAEWOO_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_daewoo.c"
#elif defined(DAEWOO_INTERNATIONAL_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_daewoo_international.c"
#elif defined(CORVUS_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_corvus.c"
#elif defined(FAR_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_far.c"
#elif defined(FENNER_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_fenner.c"
#elif defined(EUROSOUND_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_eurosound.c"
#elif defined(NIKENNY_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_nikenny.c"
#elif defined(NIKENNY_LOGO_NEW)
#include ".\\Customers\\Huajia\\title_huajia_en_nikenny_new.c"
#elif defined(TREVI_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_trevi.c"
#elif defined(DANTAX_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_dantax.c"
#elif defined(GREENPOINT_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_greenpoint.c"
#elif defined(ASSAI_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_assai.c"
#elif defined(CRONER_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_croner.c"
#elif defined(HITO_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_hito.c"
#elif defined(CITIZEN_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_citizen.c"
#elif defined(ACCURA_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_accura.c"
#elif defined(AMC_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_amc.c"
#elif defined(AMSTRAD_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_amstrad.c"
#elif defined(WEISSOUND_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_weissound.c"
#elif defined(NAKS_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_naks.c"
#elif defined(ROYAL_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_royal.c"
#elif defined(LEXSOR_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_lexsor.c"    
#elif defined(EUROSTAR_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_eurostar.c"
#elif defined(MATRLX_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_matrlx.c"
#elif defined(DAVTONA_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_davtona.c"
#elif defined(MONBEL_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_monbel.c"
#elif defined(ELECTRO_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_electro.c"
#elif defined(SCANSONIC_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_scansonic.c"
#elif defined(ASTRO_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_astro.c"
#elif defined(HIMAGE_CH_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_chinese.c"
#elif defined(SUPERSONIC_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_supersonic.c"
#elif defined(NUXIUS_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_nuxius.c"
#elif defined(ALTEK_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_altek.c"
#elif defined(VELLEMAN_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_velleman.c"
#elif defined(PANAVOX_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_panavox.c"
#elif defined(TALENT_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_talent.c"
#elif defined(VIVO_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_vivo.c"
#elif defined(ECG_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_ecg.c"
#elif defined(EUROSTAR_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_eurostar.c"
#elif defined(COLUMBIA_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_columbia.c"
#elif defined(CROWNJAPAN_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_crownjapan.c"
#elif defined(APEX_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_apex.c"
#elif defined(MAJESTIC_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_majestic.c"
#elif defined(RECCO_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_recco.c"
#elif defined(RECCO_LOGO2)
#include ".\\Customers\\Huajia\\title_huajia_en_recco2.c"
#elif defined(POWERPOINT_LOGO)
#include ".\\Customers\\Huajia\\title_himage_en_powerpoint.c"
#elif defined(NORCENT_LOGO)
#include ".\\Customers\\Huajia\\title_himage_en_NORCENT.c"
#elif defined(CCM_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_ccm.c"
#elif defined(CCM2_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_ccm.c"
#elif defined(DVX_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_dvx.c"
#elif defined(NEUTRAL_LOGO)
#include ".\\Customers\\Huajia\\title_neutral.c"
#elif defined(XMS_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_xms.c"
#elif defined(REXTOR_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_rextor.c"
#elif defined(STRONG_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_strong.c"
#elif defined(IMAGE_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_image.c"
#elif defined(HITEKER_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_hiteker.c"
#elif defined(SVA_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_sva.c"
#elif defined(DSE_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_dse.c"
#elif defined(ACASSI_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_acassi.c"
#elif defined(BUDWEISER_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_budweiser.c"
#elif defined(MAX_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_max.c"
#elif defined(VIDEOCON_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_videocon.c"
#elif defined(ACOUSTIC_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_acoustic.c"
#elif defined(EL_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_el.c"
#elif defined(VOXSON_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_voxson.c"
#elif defined(JAMA_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_jama.c"
#elif defined(DELTON_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_delton.c"
#elif defined(OLYMPIC_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_olympic.c"
#elif defined(SANSUI_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_sansui.c"
#elif defined(TONGTEL_LOGO)
#include ".\\Customers\\Huajia\\title_huajia_en_tongtel.c"
#else//#if defined(DOUBLE_LOGO)//huajia chinese logo
#include ".\\Customers\\Huajia\\title_huajia.c"
#endif//#if defined(DOUBLE_LOGO)


#elif defined(SVA_DVD)
#include ".\\Customers\\SVA\\title_sva.c"

#elif defined(KONKA_DVD)
#include ".\\Customers\\Konka\\title_konka.c"

#elif defined(GBM_DVD)

    #ifdef GBM_HAIER_LOGO
    #include ".\\Customers\\Gbm\\title_gbm_haier.c"
    #elif defined(GBM_AMW_LOGO)
        #ifdef NEW_STYLE_SETUP
    #include ".\\Customers\\Gbm\\title_gbm_amw.c"
        #else
        #include ".\\Customers\\Gbm\\title_gbm_amw_g.c"
        #endif
    #elif defined(GBM_AMW_P9C0_LOGO)
    #include ".\\Customers\\Gbm\\title_gbm_amw_p9c0.c"
#elif defined(GBM_POLAROID_P90K_LOGO)
#include ".\\Customers\\Gbm\\title_polaroid_p90k.c"
    #elif defined(GBM_POLAROID_P907_LOGO)//1mx16
    #include ".\\Customers\\Gbm\\title_polaroid_p907.c"
    #elif defined(GBM_RONIN_LOGO)//P9070502
    
        #ifdef SDRAM_16Mb_Mode
        #include ".\\Customers\\Gbm\\title_gbm_ronin_16.c"
        #else//SDRAM_16Mb_Mode
    #include ".\\Customers\\Gbm\\title_gbm_ronin.c"
        #endif//SDRAM_16Mb_Mode

    #elif defined(GBM_SAMPLE_LOGO)
    #include ".\\Customers\\Gbm\\title_gbm_sample.c"
    #elif defined(GBM_TCL_LOGO)
    #include ".\\Customers\\Gbm\\title_gbm_tcl.c"
    #elif defined(GBM_MITSUI_LOGO)
    #include ".\\Customers\\Gbm\\title_gbm_mitsui.c"    
    #elif defined(GBM_BRITANIA_LOGO)
    #include ".\\Customers\\Gbm\\title_gbm_britania.c"    
    #elif defined(GBM_VSONIC1_LOGO)
    #include ".\\Customers\\Gbm\\title_gbm_vsonic1.c"
    #elif defined(GBM_VSONIC2_LOGO)
    #include ".\\Customers\\Gbm\\title_gbm_vsonic2.c"
    #elif defined(GBM_YAMASAKI_LOGO)
    #include ".\\Customers\\Gbm\\title_gbm_yamasaki_power.c"
    #elif defined(GBM_AUDINAC_LOGO)
    #include ".\\Customers\\Gbm\\title_gbm_audinac.c"    
    #elif defined(GBM_TCL03_LOGO)
    #include ".\\Customers\\Gbm\\title_gbm_tcl_03.c"
    #elif defined(GBM_EMERSON_LOGO)
    #include ".\\Customers\\Gbm\\title_gbm_emerson_01.c"
    #elif defined(GBM_AMW_NEW_LOGO)
    #include ".\\Customers\\Gbm\\title_gbm_amw_new.c"
    #elif defined(GBM_AMW_2_LOGO)
    #include ".\\Customers\\Gbm\\title_gbm_amw_2.c"
    //---------0130 add-----------
    #elif defined(GBM_DAYTEK_LOGO)
    #include ".\\Customers\\Gbm\\title_gbm_daytek.c"
    #elif defined(GBM_SOAR_SAMPLE_LOGO)
        #ifdef NEW_STYLE_SETUP
    #include ".\\Customers\\Gbm\\title_gbm_soar_sample.c"
        #else
        #include ".\\Customers\\Gbm\\title_gbm_soar_sample_sunp_setup.c"
        #endif

    //-------0203 add--------------
    #elif defined(GBM_WHITE_LOGO)
    #include ".\\Customers\\Gbm\\title_whitelogo.c"   
    //-------0205 add--------------
    #elif defined(GBM_GRADIENTE01_LOGO)
    #include ".\\Customers\\Gbm\\title_gbm_gradiente01.c"   
    #elif defined(GBM_DAEWOO_01_LOGO) //wangap add 2004/2/11
    #include ".\\Customers\\Gbm\\title_gbm_daewoo_01.c" 

    //------- 0219 add -------------
    #elif defined(GBM_RONIN07_LOGO)
    #include ".\\Customers\\Gbm\\title_gbm_ronin07.c"

    #else
    #include ".\\Customers\\Gbm\\title_gbm.c"
    #endif

#elif defined(GBM_AP_DVD)

    #include ".\\Customers\\Gbm_ap\\title_gbm_ap.c"
#elif defined(GBM_PORTABLE_DVD)//jhuang 2003/12/26
    #ifdef D02_B_10INCH
    #include ".\\Customers\\Gbm_portable\\title_gbmportable_10d02b.c"    
    #elif defined(D02_C_10INCH)
    #include ".\\Customers\\Gbm_portable\\title_gbmportable_10d02c.c"    
    #else
    #include ".\\Customers\\Gbm_portable\\title_gbmportable.c"
    #endif
#elif defined(CNMOTOR_DVD)
#include ".\\Customers\\Cnmotor\\title_cnmotor.c"

#elif defined(QISHENG_DVD)
#include ".\\Customers\\QiSheng\\title_qisheng.c"
 #ifdef LOGO_PLAY_MP3
  #include ".\\Customers\\Sunplus\\logo_mp3.c"
 #endif 
#elif defined(YAHSIN_DVD)
#include ".\\Customers\\YaHsin\\title_yahsin.c"

//#elif defined(SKYWORTH_DVD)
//#include ".\\Customers\\SkyWorth\\title.c"

#elif defined(WANGINE_DVD)
#include ".\\Customers\\Wangine\\title_wangine.c"
#elif defined(BMT_DVD)
#include ".\\Customers\\BMT\\title_BMT.c"
#elif defined(SUOJIA_DVD)
#include ".\\Customers\\suojia\\title_suojia.c"
#elif defined(OUR_MIND_DVD)
#include ".\\Customers\\ourmind\\title_ourmind.c"
#elif defined(WEIKING_DVD_AMP)
#include ".\\Customers\\weiking\\title_weiking.c"
#elif defined(APOLLO_DVD)
#include ".\\Customers\\apollo\\title_apollo.c"
#elif defined(LUCKY_DVD)
#include ".\\Customers\\lucky\\title_lucky.c"
#elif defined(AVIQ_DVD)
#include ".\\Customers\\AViQ\\title_aviq.c"

#elif defined(FUDI_DVD)
#include ".\\Customers\\fudi\\title_fudi.c"

#elif defined(PROVIEW_DVD)
#include ".\\Customers\\Proview\\title_proview_odm.c"

#elif defined(MICO_DVD)
#include ".\\Customers\\MICO\\title_mico.c"

#elif defined(ZIHUAN_DVD)
    #ifdef SPHE8202
    #include ".\\Customers\\Zihuan\\title_zihuan_8202.c"
    #else
#include ".\\Customers\\Zihuan\\title_zihuan.c"
    #endif
#elif defined(ZHAOCHI_DVD)   //LYC 2005-04-04
  #if defined(MTC_PORTABLE_DVB_8202D_6600)||defined(MTC_DVD_DVB_8202D_6600)
    #include ".\\Customers\\ZHAOCHI\\title_mtc_8202d_dvb.c" 
  #elif defined(SCALER_6500)
    #include ".\\Customers\\ZHAOCHI\\title_MTC_6500.c" 
  #else 
  #include ".\\Customers\\ZHAOCHI\\title_zhaochi.c"
  #endif
#elif defined(KSD_DVD)
    #ifdef PANDA_DVD    // alan, 2003/8/15 10:56PM
        #if defined(PHILO_VP588)||defined(PANDA_VP595)      //gerry,3-9-12 9:26
            #include ".\\Customers\\TrendDigit\\title_panda_philo.c"
        #else
        #include ".\\Customers\\TrendDigit\\title_panda.c"
        #endif
    #elif defined(PANDA_DVD_EN)
        #include ".\\Customers\\TrendDigit\\title_panda_english.c"
    #elif defined(PANDA_DVD_EN_L109)
        #include ".\\Customers\\TrendDigit\\title_panda_airis.c"
    #elif defined(PANDA_DVD_16)
        //#include ".\\Customers\\TrendDigit\\title_panda.c"
        #include ".\\Customers\\TrendDigit\\title_panda_airis.c"
    #elif defined(PANDA_DVD_ID3)
        #include ".\\Customers\\TrendDigit\\title_panda.c"
    #elif defined(PANDA_DVD_DV_923)
        #include ".\\Customers\\TrendDigit\\title_panda_dv_923.c"
    #elif defined(PANDA_DVD_8202_6961)
        #include ".\\Customers\\TrendDigit\\title_panda_8202_6961.c"
    #elif defined(PANDA_DVD_8202_DP109)
        #include ".\\Customers\\TrendDigit\\title_panda_dvdvideo.c"
    #else
#include ".\\Customers\\TrendDigit\\title_ksd.c"
    #endif

#elif defined(DESAY_DVD)
    #ifdef DS_N822_TYPE
    #include ".\\Customers\\Desay\\title_desay_n822.c"
    #else
#include ".\\Customers\\Desay\\title_desay.c"
    #endif

#elif defined(MINTON_DVD)
    #if defined(MINTON_YILI_LCD127_6CH)
    #include ".\\Customers\\Minton\\title_minton127.c"
    #elif defined(MINTON_DVD_BOOMBOX)
    #include ".\\Customers\\Minton\\title_minton301.c"
    #else   
#include ".\\Customers\\Minton\\title_minton.c"
    #endif

#elif defined(IDALL_DVD)
#include ".\\Customers\\IDall\\title_idall.c"

#elif defined(XUKE_DVD)
#include ".\\Customers\\xuke\\title_xuke.c"

#elif defined(EASTECH_DVD)  //2004-4-2 1:33  wsf
    #ifdef BLUE_YH_LOGO
        #include ".\\Customers\\EASTECH\\title_eastech_blue_hy_logo.c"    
    #elif defined ( EASTECH_SHARP_LOGO )
        #include ".\\Customers\\EASTECH\\title_eastech_sharp.c"
    #elif defined ( EASTECH_CP_AKIRA_LOGO )
        #include ".\\Customers\\EASTECH\\title_eastech_cp_akira_logo.c"        
    #elif defined ( EASTECH_DP3240_LOGO )
        #include ".\\Customers\\EASTECH\\title_dp3240.c"
    #elif defined ( EASTECH_DP2070_LOGO )
        #include ".\\Customers\\EASTECH\\title_dp2070.c"
    #elif defined ( EASTECH_DP3181_LOGO )
        #include ".\\Customers\\EASTECH\\title_dp3181.c"
    #elif defined ( EASTECH_DP3170_LOGO )
        #include ".\\Customers\\EASTECH\\title_dp3170.c"
    #elif defined ( EASTECH_SIMPLE_DVD_LOGO )
        #include ".\\Customers\\EASTECH\\title_eastech_simple_dvd_logo.c"               
    #elif defined ( EASTECH_USE_SUNPLUS_LOGO )
        #include ".\\Customers\\EASTECH\\title_modify1.c"
    #elif defined ( EASTECH_DP31A1_LOGO )
        #include ".\\Customers\\EASTECH\\title_31a1.c"
    #else
        #include ".\\Customers\\EASTECH\\title_eastech.c"
    #endif

#elif defined(EVERSTAR_DVD)
#include ".\\Customers\\everstar\\title_everstar.c"

#elif defined(VTREK_DVD)
//#include ".\\Customers\\vtrek\\title_vtrek.c"
#include ".\\Customers\\vtrek\\title_enzer.c"

#elif defined(GENTEK_DVD)
#include ".\\Customers\\gentek\\title_gentek.c"

#elif defined(JIEKE_DVD)
#include ".\\Customers\\jieke\\title_jieke.c"

#elif defined(JIEKE_16M_DVD)
#include ".\\Customers\\jieke\\title_jieke_16m.c"

#elif defined(JUNYUAN_DVD)
#include ".\\Customers\\Junyuan\\title_junyuan.c"

#elif defined(HUIFENGYUAN_DVD)
#include ".\\Customers\\HuiFengYuan\\title_huifengyuan.c"

#elif defined(HENGCHEN_DVD)
#include ".\\Customers\\HengChen\\title_hengchen.c"

#elif defined(WEICHENG_DVD)
#include ".\\Customers\\weicheng\\title_sunplus.c"

#elif defined(YADAI_DVD)
      #ifdef SVA_LOGO//use for ShangGuangDian 
             #include ".\\Customers\\Yadai\\title_yadai_en_sva.c"
      #else
#include ".\\Customers\\Yadai\\title_tcl.c"
      #endif

#elif defined(XINGQIU_DVD)
#include ".\\Customers\\xingqiu\\title_xingqiu.c"

#elif defined(XINGWEIKE_DVD)             //2003-12-22 wangap
#include ".\\Customers\\XINGWEIKE\\title_xingweike.c"

#elif defined(YANGYU_DVD)                  //2003-12-23 wangap
#if defined(YANGYU_8202L_16_DVD) || defined(YANGYU_8202L_64_DVD)
    #include ".\\Customers\\yangyu\\title_8202l.c"
#else
#include ".\\Customers\\YangYu\\title_yangyu.c"
#endif

#elif defined(ARLINK_DVD)                  //05-03-03 yaowh
#include ".\\Customers\\Arlink\\title_Arlink.c"

#elif defined(ALON_DVD)                    //2003-12-23 wangap
#include ".\\Customers\\Alon\\title_alon.c"

#elif defined(TONGFANG_DVD)               //2003-12-23 wangap
#include ".\\Customers\\TongFang\\title_tongfang.c"

#elif defined(XINDE_DVD)
#include ".\\Customers\\XinDe\\title_xinde.c"

#elif defined(ORITRON_DVD)
		#include ".\\Customers\\Oritron\\title_oritron.c"
		    
#elif defined(ORITRON_HK_DVD)//lijd 2005-5-8 16:42
    #if defined(ORITRON_8202S_1X16_16BIT_DVD)        
    	#include ".\\Customers\\HK_Oritron\\title_oritron_8202S_1X16.c"  
    #elif defined(ORITRON_8202S_2X16_16BIT_DVD)
    	#include ".\\Customers\\HK_Oritron\\title_oritron_8202S_2X16.c"   	  
    #elif defined(ORITRON_8202D_1X16_16BIT_DVD)
    	#include ".\\Customers\\HK_Oritron\\title_oritron_8202D_1X16.c"	 
    #elif defined(ORITRON_8202D_2X16_16BIT_DVD)
    	#include ".\\Customers\\HK_Oritron\\title_oritron_8202D_2X16.c" 
    #elif defined(ORITRON_8202D_3111_DVD)
   		#include ".\\Customers\\HK_Oritron\\title_oritron_Speler.c"
   	#elif defined(ORITRON_8202D_4110_DVD)
   		#include ".\\Customers\\HK_Oritron\\title_oritron_8202D_1X16.c"
   #elif defined(ORITRON_8202D_4119_DVD)
   	#include ".\\Customers\\HK_Oritron\\title_oritron_8202D_1X16.c"
   	#elif defined(ORITRON_8202D_4125_DVD)
   		#include ".\\Customers\\HK_Oritron\\title_oritron_8202D_2X16.c"
   #elif defined(ORITRON_8202D_4127_DVD)
   	#include ".\\Customers\\HK_Oritron\\title_oritron_8202D_1X16.c"	
   	#elif defined(ORITRON_8202D_5112_DVD)
   		#include ".\\Customers\\HK_Oritron\\title_oritron_8202D_1X16.c"
   	#elif defined(ORITRON_8202D_5115_DVD)
   		#include ".\\Customers\\HK_Oritron\\title_oritron_8202D_1X16.c"		 
   #elif defined(ORITRON_8202D_5116_DVD)
   	#include ".\\Customers\\HK_Oritron\\title_oritron_8202D_1X16.c"	
   #elif defined(ORITRON_8202D_5117_DVD)
   	#include ".\\Customers\\HK_Oritron\\title_oritron_SEMP.c"	
   #elif defined(ORITRON_8202D_5121_DVD)
   	#include ".\\Customers\\HK_Oritron\\title_oritron_SEMP.c"
   #elif defined(ORITRON_8202D_5122_DVD)
   	#include ".\\Customers\\HK_Oritron\\title_oritron_5122.c"			 
   #elif defined(ORITRON_8202D_6122_DVD)
	    #ifdef OP_5121_SAMPLE
	    #include ".\\Customers\\HK_Oritron\\title_oritron_gradiente.c"
	    #else
   	#include ".\\Customers\\HK_Oritron\\title_oritron_6122.c"				 
    #endif
   #endif 

#elif defined(HK_ORITRON_DVD_RECEIVER) //hongfeng 2005-07-09
    #if defined(ORITRON_RECEIVER_6001)
        #ifdef ORITRON_RECEIVER_6001_THOMSON//hongfeng 2005-11-01
        #include ".\\Customers\\oritron\\title_thomson.c"   
        #elif defined BESTBUY_LOGO
        #include ".\\Customers\\oritron\\title_bestbuy.c"   
        #else
        #include ".\\Customers\\oritron\\title_oritron_receiver_6001.c" 	
        #endif    
    #elif defined(ORITRON_RECEIVER_5003)
    #include ".\\Customers\\oritron\\title_oritron_receiver_5003.c"
    #elif defined(ORITRON_RECEIVER_6008)
        #ifdef USE_TOSHIBA  
        #include ".\\Customers\\oritron\\title_oritron_SEMP.c"
        #else
        #include ".\\Customers\\oritron\\title_oritron_receiver_6008_ZHONG.c"
        #endif
    #elif defined(ORITRON_RECEIVER_6505)
    #include ".\\Customers\\oritron\\title_oritron_receiver_6505.c"
    #elif defined(ORITRON_RECEIVER_DPL937)
    #include ".\\Customers\\oritron\\title_oritron_receiver_dpl937.c"
    #endif	  

#elif defined (ORIENTPOWER_DVD)
#include ".\\Customers\\OrientPower\\title_orientpower.c"

#elif defined(SYBER_DVD)  //2003-11-19 9:14 David
#include ".\\Customers\\SYBER\\title_syber.c"

#elif defined(TONIC_DVD)  //dingzhy  2/6/2004 1:33PM
#include ".\\Customers\\tonic\\title_tonic.c"

#elif defined(SHIDELI_DVD)  //gerry,2004-4-21 13:08
#include ".\\Customers\\shideli\\title_shideli.c"

#elif defined(JENGYANG_DVD)  //liulifeng 2004-8-5 8:46
#include ".\\Customers\\JENGYANG\\title_jengyang.c"

#elif defined(THAKRAL_DVD)  //suqiaoli,2004-9-13 
    #ifdef SHARP_MODE
    #include ".\\Customers\\thakral\\title_sharp.c"
    #elif defined(APEX_MODE)
    #include ".\\Customers\\thakral\\title_apex.c"
    #else
	#include ".\\Customers\\thakral\\title_thakral.c"
    #endif

#elif defined(WINGSUM_DVD)
    #include ".\\Customers\\wingsum\\title_wingsum.c"

#elif defined(EASTWIN_PORTABLE_DVD)
#include ".\\Customers\\Eastwin\\title_eastwin.c"

#elif defined(TEAC_PORTABLE_DVD)//TEAC
#include ".\\Customers\\teac_portable\\title_teac.c"

#elif defined(JIANLOON_DVD)   //liych  added 2005-3-23
//#include ".\\Customers\\JIANLOON\\title_JianLoon.c"	
//ZXB2005-5-8 12:45 for double title
#include ".\\Customers\\JIANLOON\\title_jianloon_caution.c"	
#include ".\\Customers\\JIANLOON\\title_jianloon_hyundai.c"

#elif defined(QSI_PORTABLE_DVD) //qsi: added by johnson 20040712

    #if     (QSI_LOGO_TYPE == QSI_LOGO_IS_NU)
    #include ".\\Customers\\Qsi_portable\\title_nu.c"
    #elif   (QSI_LOGO_TYPE == QSI_LOGO_IS_QSI)
    #include ".\\Customers\\Qsi_portable\\title_qsi_salse.c"
    #else
    #include ".\\Customers\\Qsi_portable\\title_logo.c"
    #endif

#elif defined(SUNPLUS_DVB_DVD)  // wrwu, 2004/11/02,  SPHE1000/1001  STB LOGO
	#include ".\\Customers\\Sunplus\\title_sunplus_stb.c"

#elif defined(SUNPLUS_NONOSDVB_DVD)  // wrwu, 2004/11/02, SPHE100X NON-OS DVB LOGO
	#include ".\\Customers\\Sunplus\\title_sunplus_stb.c"
	
#elif defined(PHILIPS_DVD)
    #include ".\\Customers\\Sunplus\\title_8202d.c"            

#elif defined(APEX_PORTABLE_DVD)     ////liulifeng 2005-4-29 12:45
    #include ".\\Customers\\APEX_PDVD\\title_apex.c"

#elif defined(SHINCO_DVD)
    #include ".\\Customers\\shinco\\title_shinco.c"
    
#elif defined(MALATA_GPS_DVD)
    #include ".\\Customers\\MALATA_GPS_DVD\\title_malata_gps_dvd.c"   
#elif defined(MALATA_PORTABLE_DVD)
    #if defined(MALATA_PORTABLE_DVBT)
            //--------------------67003_ODYS-----------------------------------------
           #ifdef  SUPPORT_67003_ODYS_DVD_LOGO
    		#include ".\\Customers\\malata_portable\\title_malata_por_67003odys_dvd.c"	   
	    #endif//end=> #ifdef  SUPPORT_67003_ODYS_DVD_LOGO
	    #ifdef  SUPPORT_67003_ODYS_DVB_LOGO
   		#include ".\\Customers\\malata_portable\\title_malata_por_67003odys_dvb.c"		   
	    #endif//end=> #ifdef  SUPPORT_67003_ODYS_DVB_LOGO
          //--------------------67003_BELSON----------------------------------------
          #ifdef  SUPPORT_67003_BELSON_DVD_LOGO
    		#include ".\\Customers\\malata_portable\\title_malata_por_67003belson_dvd.c"	   
	    #endif//end=> #ifdef  SUPPORT_67003_BELSON_DVD_LOGO
	    #ifdef  SUPPORT_67003_BELSON_DVB_LOGO
   		#include ".\\Customers\\malata_portable\\title_malata_por_67003belson_dvb.c"		   
	    #endif//end=> #ifdef  SUPPORT_67003_BELSON_DVB_LOGO		
	   //-----------------------67003_POLAROID-----------------------------------
	    #ifdef  SUPPORT_67003_POLAROID_DVD_LOGO
    		#include ".\\Customers\\malata_portable\\title_malata_por_67003polaroid_dvd.c"   
	    #endif//end=> #ifdef  SUPPORT_67003_POLAROID_DVD_LOGO
	    #ifdef  SUPPORT_67003_POLAROID_DVB_LOGO
   		#include ".\\Customers\\malata_portable\\title_malata_por_67003polaroid_dvb.c"		   
	    #endif//end=> #ifdef  SUPPORT_67003_POLAROID_DVB_LOGO	
           //-----------------------67003_ITSLABEL------------------------------------
	   #ifdef  SUPPORT_67003_ITSLABEL_DVD_LOGO
    		#include ".\\Customers\\malata_portable\\title_malata_por_67003itslabel_dvd.c"   
	    #endif//end=> #ifdef  SUPPORT_67003_ITSLABEL_DVD_LOGO
	    #ifdef  SUPPORT_67003_ITSLABEL_DVB_LOGO
   		#include ".\\Customers\\malata_portable\\title_malata_por_67003itslabel_dvb.c"		   
	    #endif//end=> #ifdef  SUPPORT_67003_ITSLABEL_DVB_LOGO	
           //--------------------------67003_SVC--------------------------------------
	    #ifdef  SUPPORT_67003_SVC_DVD_LOGO
    		#include ".\\Customers\\malata_portable\\title_malata_por_67003svc_dvd.c"   
	    #endif//end=> #ifdef  SUPPORT_67003_SVC_DVD_LOGO
	    #ifdef  SUPPORT_67003_SVC_DVB_LOGO
   		#include ".\\Customers\\malata_portable\\title_malata_por_67003svc_dvb.c"		   
	    #endif//end=> #ifdef  SUPPORT_67003_SVC_DVB_LOGO	
          //--------------------------67003_XXX---------------------------------------
	   #ifdef  SUPPORT_67003_XXX_DVD_LOGO
    		#include ".\\Customers\\malata_portable\\title_malata_por_67003_xxx_dvd.c"   
	    #endif//end=> #ifdef  SUPPORT_67003_XXX_DVD_LOGO
	    #ifdef  SUPPORT_67003_XXX_DVB_LOGO
   		#include ".\\Customers\\malata_portable\\title_malata_por_67003_xxx_dvb.c"		   
	    #endif//end=> #ifdef  SUPPORT_67003_XXX_DVB_LOGO		
           //-------------------------68501_XXX---------------------------------------
	    #ifdef  SUPPORT_68501_XXX_DVD_LOGO
    		#include ".\\Customers\\malata_portable\\title_malata_por_68501_xxx_dvd.c"	   
	    #endif//end=> #ifdef  SUPPORT_68501_XXX_DVD_LOGO
	    #ifdef  SUPPORT_68501_XXX_DVB_LOGO
   		#include ".\\Customers\\malata_portable\\title_malata_por_68501_xxx_dvb.c"		   
	    #endif//end=> #ifdef  SUPPORT_68501_XXX_DVB_LOGO	
		//-------------------------68501_POLAROID---------------------------------------          
	    #ifdef  SUPPORT_68501_POLAROID_DVD_LOGO
    		#include ".\\Customers\\malata_portable\\title_malata_por_68501polaroid_dvd.c"	   
	    #endif//end=> #ifdef  SUPPORT_68501_POLAROID_DVD_LOGO
	    #ifdef  SUPPORT_68501_POLAROID_DVB_LOGO
   		#include ".\\Customers\\malata_portable\\title_malata_por_68501polaroid_dvb.c"		   
	    #endif//end=> #ifdef  SUPPORT_68501_POLAROID_DVB_LOGO
		
	    //--------------------------68502_LENCO-------------------------------------	
	    #ifdef  SUPPORT_68502_LENCO_DVD_LOGO
    		#include ".\\Customers\\malata_portable\\title_malata_por_68502lenco_dvd.c"	   
	    #endif//end=> #ifdef  SUPPORT_68502_LENCO_DVD_LOGO
	    #ifdef  SUPPORT_68502_LENCO_DVB_LOGO
   		#include ".\\Customers\\malata_portable\\title_malata_por_68502lenco_dvb.c"		   
	    #endif//end=> #ifdef  SUPPORT_68502_LENCO_DVB_LOGO	
	    //---------------------------68503_XXX---------------------------------------	
	    #ifdef  SUPPORT_68503_XXX_DVD_LOGO
    		#include ".\\Customers\\malata_portable\\title_malata_por_68503_xxx_dvd.c"
	    #endif//end=> #ifdef  SUPPORT_68503_XXX_DVD_LOGO
	    #ifdef  SUPPORT_68503_XXX_DVB_LOGO
   		#include ".\\Customers\\malata_portable\\title_malata_por_68503_xxx_dvb.c"
	    #endif//end=> #ifdef  SUPPORT_68503_XXX_DVB_LOGO
	    //---------------------------68504_BELSON------------------------------------	
	    #ifdef  SUPPORT_68504_BELSON_DVD_LOGO
    		#include ".\\Customers\\malata_portable\\title_malata_por_68504_belson_dvd.c"	   
	    #endif//end=> #ifdef  SUPPORT_68504_BELSON_DVD_LOGO
	    #ifdef  SUPPORT_68504_BELSON_DVB_LOGO
   		#include ".\\Customers\\malata_portable\\title_malata_por_68504_belson_dvb.c"		   
	    #endif//end=> #ifdef  SUPPORT_68504_BELSON_DVB_LOGO
	    //---------------------------????--------------------------------------------
	    //---------------------------????--------------------------------------------
	    //---------------------------????--------------------------------------------
	    //---------------------------????--------------------------------------------
	    //---------------------------????--------------------------------------------

		#endif
#elif defined(ALCO_DVD)
    #if defined(ALCO_PORTABLE)
    #ifdef ALCO_REDUCE2_4M_FLASH
        #include ".\\Customers\\Alco_portalbe\\title_Alcoportable_4mflash.c"
    #else
        #include ".\\Customers\\Alco_portable\\title_Alcoportable.c"
        #endif
    #else
        #include ".\\Customers\\general\\title_8202d.c"
    #endif
#elif defined(GOWELLENT_DVD)
		#if defined(GOWELLENT_8202L_16M_DVD)
				#include ".\\Customers\\Gowellent\\title_Gowellent.c"
		#else
				#include ".\\Customers\\Gowellent\\title_Gowellent.c"
		#endif
		
		 
#else
    #include ".\\Customers\\Sunplus\\title_sunplus.c"

#endif

