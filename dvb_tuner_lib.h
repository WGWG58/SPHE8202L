/*INPUT(-ldvb_tuner)*///xiaopeng modified 2005/11/22

//-------------------------------- NIM --------------------------------
#ifdef TUNER_MDVBT_35308T_NIM                     
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_mdvbt_35308t_nim.a)//Comtech RF:TUA6034(Infineon)/DEMOD:ZL10353(Intel)//
#endif

#ifdef TUNER_MDVBT_3KU6MP_NIM     //wthsin       2006/2/6 11:34am                
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_mdvbt_3ku6mp_nim.a)//Comtech RF:TUA6034(Infineon)/3000MC(Dibcom)
#endif

#ifdef TUNER_MDVBT_90038B6T_NIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_mdvbt_90038b6t_nim.a)//Comtech RF:TUA6034(Infineon)/AF9003(AFA tech)
#endif

#ifdef TUNER_TU1216_NIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_tu1216_nim.a)//RF:TDA6651(philips)/DEMOD:TDA10046(philips)
#endif

#ifdef TUNER_DNOS204ZH102A_NIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_dnos204zh102a_nim.a)//RF:TUA6034(infineon)/DEMOD:MT352(Zarlink)
#endif

#ifdef TUNER_DNOS204ZH103A_NIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_dnos204zh103a_nim.a)//RF:TUA6034(infineon)/DEMOD:ZL10353(Zarlink)
#endif

#ifdef TUNER_DNOS504ZM021A_NIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_dnos504zm021a_nim.a)//RF:TUA6034(infineon)/DEMOD:MT352(Zarlink)
#endif

#ifdef TUNER_DNOS404PH104A_NIM    //tcf 2006-3-2 09:20ÉÏÎç
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_dnos404ph104a_nim.a)//RF:TUA6034(Infineon)/DEMOD:TDA10046(Philips)
#endif

#ifdef TUNER_HXT3T11ASS_NIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_hxt3t11ass_nim.a)//RF:MT2060/DEMOD:MT352(Zarlink)
#endif


#ifdef TUNER_MDVBT_35278MCXT_NIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_mdvbt_35278mcxt_nim.a)//RF:TDA6034/DEMOD:MT352(Zarlink)
#endif

#ifdef TUNER_UTMAF9003MT2060_NIM	//tcf 2006-5-29 02:25ÏÂÎç
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_prime_utmaf9003mt2060_nim.a)//RF:MT2060/DEMOD:AF9003(AFA tech)
#endif

#ifdef TUNER_UTM2AF9013MXL5003_NIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_prime_utm2af9013mxl5003_nim.a)//RF:MXL5003()/DEMOD:AF9013(AFA tech)
#endif

#ifdef TUNER_MDVBT_7K8_NIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_mdvbt_7k8_nim.a)//RF:TDA6651/DEMOD:MT352(Zarlink)
#endif
//---------------------------  SEPARATION --------------------------
#ifdef TUNER_SHA0ZAR1_HALFNIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_sha0zar1_halfnim.a)//RF:Sharp_VA1T1ED6058 DA6651(Philips)/DEMOD:ZL10353(Zarlink)
#endif

#ifdef TUNER_LG0ZAR1_HALFNIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_lg0zar1_halfnim.a)//RF:LG_TDTM-G252D TUA6034(Infineon)/DEMOD:ZL10353(Zarlink)
#endif

#ifdef TUNER_SAM0ZAR1_HALFNIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_sam0zar1_halfnim.a)//RF:Samsung_DTOS446IH241F TUA6034(Infineon)/DEMOD:ZL10353(Zarlink)
#endif

#ifdef TUNER_EM0ZAR1_HALFNIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_em0zar1_halfnim.a)//RF:Empire_DTN-306CTW TDA6651(Philips)/DEMOD:ZL10353(Intel)
#endif

#ifdef TUNER_EM0AF03_HALFNIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_em0af03_halfnim.a)//RF:Empire_DTN-306CTW TDA6651(Philips)/DEMOD:AF9003(AFA tech)
#endif

#ifdef TUNER_LG0AF03_HALFNIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_lg0af03_halfnim.a)//RF:RF:LG_TDTM-G252D TUA6034(Infineon)/DEMOD:AF9003(Afa tech)
#endif

#ifdef TUNER_PH0ZAR1_HALFNIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_ph0zar1_halfnim.a)//RF:Philips_TD1316ALF IHP-3 TUA6034(Infineon)/DEMOD:ZL10353(Intel)
#endif


#ifdef TUNER_PH1ZAR1_HALFNIM
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_ph1zar1_halfnim.a)//RF:Philips_TD1311ALF IHP-3 TUA6034(Infineon)/DEMOD:ZL10353(Intel)
#endif

#ifdef Tuner_AF9003_MT2060
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_af9003_mt2060.a)//RF:MT2060_SiliconRf(Mircotune)/DEMOD:AF9003(AFA tech)
#endif

#ifdef Tuner_AF9002_MT2060_DIV
INPUT(mipsel-elf\mipsel-elf-dvbtuner\lib_af9002_mt2060_diversity.a)//RF:MT2060_SiliconRf(Mircotune)/DEMOD:AF9002(AFA tech)
#endif
