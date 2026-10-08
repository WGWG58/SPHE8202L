#ifndef __TCFONT_H
#define __TCFONT_H

#include "cchar.h"
#include "user_init.h"

#define _cat_(a, b)                         a b
#define _cat3_(a, b, c)                     a b c
#define _cat4_(a, b, c, d)                  a b c d
#define _cat5_(a, b, c, d, e)               a b c d e
#define _cat6_(a, b, c, d, e, f)            a b c d e f
#define _cat7_(a, b, c, d, e, f, g)         a b c d e f g
#define _cat8_(a, b, c, d, e, f, g, h)      		a b c d e f g h
#define _cat9_(a, b, c, d, e, f, g, h, i)   		a b c d e f g h i
#define _cat10_(a, b, c, d, e, f, g, h, i, j)   	a b c d e f g h i j
#define _cat11_(a, b, c, d, e, f, g, h, i, j, k)	a b c d e f g h i j k
#define _cat12_(a, b, c, d, e, f, g, h, i, j, k, l)	a b c d e f g h i j k l
#define _cat13_(a, b, c, d, e, f, g, h, i, j, k, l, m)	a b c d e f g h i j k l m
#define _cat14_(a, b, c, d, e, f, g, h, i, j, k, l, m, n)	a b c d e f g h i j k l m n




#ifdef DISPLAY_INDIVIDUAL_SPK_VOLUME//2005-4-19 11:25 zhoulin
#define OS_MAIN_VOL             _cat3_(Ch_zhu, Ch_yin, Ch_liang)
#define OS_VOL_L             _cat3_(Ch_zuo, Ch_sheng, Ch_dao)
#define OS_VOL_R             _cat3_(Ch_you1, Ch_sheng, Ch_dao)
#define OS_VOL_SL             _cat3_(Ch_zuo, Ch_huan1, Ch_rao)
#define OS_VOL_SR             _cat3_(Ch_you1, Ch_huan1, Ch_rao)
#define OS_VOL_CT             _cat_(Ch_zhong, Ch_zhi5)
#define OS_VOL_SW             _cat3_(Ch_chong, Ch_di, Ch_yin)
#define OS_BASS             _cat_(Ch_di, Ch_yin)
#define OS_TREMBLE          _cat_(Ch_gao, Ch_yin)
#define OS_5_1_CHANNEL           _cat3_("5.1", Ch_sheng, Ch_dao)
#define	OS_KARAOKE_SETUP	_cat3_("KARAOKE",Ch_she,TCh_ding) 	//S:KARAOKE扢隅

#endif

#ifdef SUPPORT_CHANNEL_SETUP//2005-4-23 19:04 zhoulin
#define OS_CHANNEL_SETUP     _cat4_(Ch_sheng, Ch_dao, Ch_mo, Ch_shi)
#endif




//osd_err_str strings
#define OS_PARENTAL_ERR         _cat4_(Ch_ji, Ch_bie, Ch_cuo, Ch_wu)                    // T:(級別錯誤)
#define OS_REGION_ERR           _cat4_(Ch_qu2, Ch_ma, Ch_cuo, Ch_wu)                    // T:(區碼錯誤)

//_OsdMessegeFont1 strings
#define OS_NULL                 ""

#if defined(BAT_DETECT)||defined(GBM_PORTABLE_DVD)||defined(SUNPLUS_8202P_DEMOBOARD)	//rbhung for GBM Portable DVD
#define OS_LOWBAT           _cat3_(Ch_di, Ch_dian, Ch_liang)                        //T:(低電量)
#endif
#define  OS_PICTURE_ROTATE_RIGHT   _cat3_(Ch_you1, Ch_xuan1, Ch_zhuan1)
#define  OS_PICTURE_ROTATE_LEFT     _cat3_(Ch_zuo, Ch_xuan1, Ch_zhuan1)
#define  OS_PICTURE_UD             _cat4_(Ch_shang,Ch_xia,Ch_jing2,JCh_xiang)
#define  OS_PICTURE_LR             _cat4_(Ch_zuo,Ch_you1,Ch_jing2,JCh_xiang)
#define  OS_PASSWORD_RIGHT         _cat_(Ch_zheng1,Ch_que3)
#define  OS_PASSWORD_ERROR         _cat_(Ch_cuo, Ch_wu6)

#define OS_NODISC           _cat_(Ch_vff, Ch_die)                                   //T:(無碟)

#ifdef FUSS_DVD
#define OS_NO               _cat4_(Ch_vff, Ch_xiao4, Ch_space, Ch_hand)             //T:(無效  hand)
#elif defined(GBM_DVD)||defined(QISHENG_DVD)
#define OS_NO               Ch_hand                                                 //T:hand
#else
//#define OS_NO               _cat6_(Ch_nin, Ch_an, Ch_cuo, Ch_nn, Ch_space, Ch_hand) //T:(您按錯了 hand)
#define OS_NO               Ch_hand//nono 2003-8-11 13:40
#endif

#define OS_ERR_DISC             _cat4_(Ch_cuo,Ch_wu,Ch_die,Ch_pian)                     //T:(錯誤碟片)
#define OS_TRACK                _cat_(Ch_qu, Ch_mu1)                                    //T:(曲目)
#define OS_CHINESE              _cat_(Ch_han, Ch_yu2)                                   //T:(漢語)
#define OS_OPEN                 _cat_(Ch_chu, Ch_cang)                                  //T:(出倉)
#define OS_CLOSE                _cat_(Ch_guan, Ch_cang)                                 //T:(關倉)
#define OS_PLAY                 _cat_(Ch_bo, Ch_fang)                                   //T:(播放)
#define OS_REGION_5             _cat_("5 ", Ch_qu2)                                     //T:(5 區)
#define OS_PAUSE                _cat_(Ch_zan, Ch_ting)                                  //T:(暫停)
#define OS_RANDOM               _cat4_(Ch_sui, Ch_ji2, Ch_bo, Ch_fang)                  //T:(隨機播放)
#define OS_STOP                 _cat_(Ch_ting, Ch_zhi)                                  //T:(停止)
#ifdef JIEKE_DVD
#define OS_RESUME               _cat6_(Ch_die, Ch_pian, Ch_ji1, Ch_yi1,Ch_bo, Ch_fang)                   //T:(恢復播放)
#define OS_STEP                 _cat_(Ch_dan, Ch_bu)
#else
#define OS_RESUME               _cat4_(Ch_hui, Ch_fu, Ch_bo, Ch_fang)                   //T:(恢復播放)
#define OS_STEP                 _cat_(Ch_bu, Ch_jin)                                    //T:(步進)
#endif
#define OS_SELECT               _cat_(Ch_xuan, Ch_ze)                                   //T:(選擇)
#define OS_READ                 _cat_(Ch_du, Ch_die)                                    //T:(讀碟)
#define OS_REGION_6             _cat_("6 ", Ch_qu2)                                     //T:(6 區)
//#define OS_SIMULATE             _cat_(Ch_mo, Ch_ni)                                     //T:(模擬)
#define OS_SIMULATE				_cat_("SPDIF/", Ch_guan)
#define OS_FF                   _cat_(Ch_kuai, Ch_jin)                                  //T:(快進)
#define OS_FB                   _cat_(Ch_kuai, Ch_tui)                                  //T:(快退)

#ifndef SUPPORT_PLAYBACK_ICON
#define OS_NEXT                 _cat5_(Ch_xia, Ch_e, Ch_qu, Ch_space, Ch_arrow)         //T:(下一曲 >>)
#define OS_PREV                 _cat5_(Ch_shang, Ch_e, Ch_qu, Ch_space, Ch_arr2)        //T:(上一曲 <<)
#else
#define OS_NEXT                 _cat4_(Ch_xia, Ch_e, Ch_qu, Ch_space)			        //T:(下一曲 >>)
#define OS_PREV                 _cat4_(Ch_shang, Ch_e, Ch_qu, Ch_space)					//T:(上一曲 <<)
#endif

#ifdef SHOW_STANDBY_TIMER//suqiaoi add
#define OS_VFD_TIME_NUM   _cat8_("-","-",":","-","-",":","-","-") 
#endif

#define OS_SAVELOGO             _cat5_(Ch_hua, Ch_mian,Ch_zhua,Ch_qu3,Ch_zhong)

#define OS_RETURN               _cat4_(Ch_cai, Ch_dan, Ch_fan, Ch_hui1)                 //T:(菜單返回)
#define OS_MENU                 _cat_(Ch_xuan, Ch_dan)                                  //T:(選單)
#ifdef SUPPORT_FUNCTION_MENU
#define OS_BROWSE               _cat_(Ch_space,Ch_space)                               
#else
#define OS_BROWSE               _cat_(Ch_liu, Ch_lan)                                   //T:(瀏覽)
#endif //end #ifndef SUPPORT_FUNCTION_MENU
#define OS_PROG                 _cat_(Ch_bian, Ch_cheng)                                //T:(編程)
#define OS_REP                  _cat_(Ch_chong, Ch_fu)                                  //T:(重復)
#ifdef	NINTAUS_OSD_STR			//maoyong 2004.03.05 for NINTAUS
#define	OS_REP_TITLE			_cat4_(Ch_biao, Ch_ti1, Ch_chong, Ch_fu)
#define OS_REP_CHAPTER			_cat4_(Ch_zhang, Ch_jie, Ch_chong, Ch_fu)			
#define OS_REP_GROUP			_cat4_(Ch_qun,Ch_zu, Ch_chong, Ch_fu)
#endif
#define OS_REP_DIR              _cat4_(Ch_mu1, Ch_lu, Ch_chong, Ch_fu)                  //T:(目錄重復)
#define OS_REP_1                _cat4_(Ch_dan, Ch_qu, Ch_chong, Ch_fu)                  //T:(單曲重復)
#define OS_REP_ALL              _cat4_(Ch_quan, Ch_die, Ch_chong, Ch_fu)                //T:(全碟重復)
#define OS_REP_CNL              _cat4_(Ch_qu3, Ch_xiao, Ch_chong, Ch_fu)                //T:(取消重復)
#define OS_GOTO                 _cat4_(Ch_sou, Ch_suo, Ch_bo, Ch_fang)                  //T:(搜索播放)
#define OS_MUTE                 _cat_(Ch_jing, Ch_yin)                                  //T:(靜音)
#define OS_CHL                  _cat3_(Ch_zuo, Ch_sheng, Ch_dao)                        //T:(左聲道)
#define OS_CHR                  _cat3_(Ch_you1, Ch_sheng, Ch_dao)                       //T:(右聲道)
#define OS_STEREO               _cat3_(Ch_li, Ch_ti, Ch_sheng)                          //T:(立體聲)
#define OS_LIVE                 _cat_(Ch_xian1, Ch_chang2)                              //T:(現場)
#define OS_TIME                 _cat_(Ch_shi1, Ch_jian)                                 //T:(時間)
#define OS_ZOOM                 _cat_(Ch_fang, Ch_da1)//Ch_kuan)                        //S:(溫湮)
#define OS_DOWN_SAMPLE          _cat3_(Ch_qu3, Ch_yang1,Ch_lv2 )
#define OS_SHARPNESS            _cat3_(Ch_rui, Ch_li2,Ch_du2)
#ifdef SHOW_MP4_INIT_STR  //wangwei-2004/4/28
#define  OS_MP4_INIT  _cat4_(Ch_chu2,Ch_shi8, Ch_hua2,"...")
#endif



#ifdef BBK_DVD                 
#define OS_NO_ZOOM               _cat_(Ch_suo1, Ch_xiao2) 
#endif             
#define OS_CANCEL               _cat_(Ch_qu3, Ch_xiao)                                  //T:(取消)
#define OS_INTRO                _cat_(Ch_sao, Ch_miaou)                                 //T:(掃描)
#define OS_SURR                 _cat_(Ch_huan1, Ch_rao)                                 //T:(環繞)
//#define OS_PBC_OFF              _cat4_(Ch_shun, Ch_xu, Ch_bo, Ch_fang)                  //T:(順序播放)
#define OS_REP_A                _cat4_(Ch_chong, Ch_fu, "A", "-")                       //T:(重復A-)
#define OS_REP_AB               _cat5_(Ch_chong, Ch_fu, "A", "-", "B")                  //T:(重復A-B)
#define OS_ENGLISH              _cat_(Ch_ying, Ch_yu2)                                  //T:(英語)
#define OS_PICUP                _cat4_(Ch_hua, Ch_mian, Ch_shang, Ch_yi)                //T:(畫面上移)
#define OS_PICDN                _cat4_(Ch_hua, Ch_mian, Ch_xia, Ch_yi)                  //T:(畫面下移)
#define OS_PICL                 _cat4_(Ch_hua, Ch_mian, Ch_zuo, Ch_yi)                  //T:(畫面左移)
#define OS_PICR                 _cat4_(Ch_hua, Ch_mian, Ch_you1, Ch_yi)                 //T:(畫面右移)
#define OS_CHAPTER              _cat_(Ch_zhang, Ch_jie)                                 //T:(章節)
#ifdef NIN_612_STR_SHOW     //LINRC ADD 2004-6-7 14:03
#define OS_ECHO                 _cat4_(Ch_hun, Ch_xiang,Ch_she,Ch_zhi5)
#else
#define OS_ECHO                 _cat_(Ch_hun, Ch_xiang)                                 //T:(混響)
#endif
#define OS_TITLE                _cat_(Ch_biao, Ch_ti1)                                  //T:(標題)
#ifdef DYNAMIC_SPECTRUM             
    #define OS_BAND				_cat4_(Ch_dong, Ch_tai,Ch_pin, Ch_pu2)
#else
#define OS_BAND					_cat_(Ch_pin, Ch_pu2)
#endif
#define OS_VOL                  _cat_(Ch_yin, Ch_liang)   
#ifdef JIEKE_DVD                              //T:(音量)
#define OS_KEY                  _cat_(Ch_yin, Ch_diao)
#else
#define OS_KEY                  _cat_(Ch_yin, Ch_diao)   
#endif                               //T:(音調)
#define OS_9FRAME_1             _cat5_(Ch_dan, Ch_qu, Ch_jiu, Ch_hua, Ch_mian)          //T:(單曲九畫面)
#define OS_AUTO_L               _cat5_(Ch_zi, Ch_dong, Ch_jie1, Ch_chang, Ch_zuo)       //T:(自動接唱左)
#define OS_AUTO_R               _cat5_(Ch_zi, Ch_dong, Ch_jie1, Ch_chang, Ch_you1)      //T:(自動接唱右)
#define OS_SEQUENCE             _cat4_(Ch_shun, Ch_xu, Ch_bo, Ch_fang)                  //T:(順序播放)
#define OS_MENUPLAY             _cat4_(Ch_cai, Ch_dan, Ch_bo, Ch_fang)                  //T:(菜單播放)
#define OS_DISCTIME             _cat4_(Ch_quan,Ch_die, Ch_shi1, Ch_jian)                //S:(�奏�奀潔)
#ifdef ONE_KEY_PASS

#ifdef NINTAUS_OSD_STR
#define OS_ONEKEY                _cat_(Ch_zhi8, Ch_bo)
#else //NINTAUS_OSD_STR
#define OS_ONEKEY                _cat5_(Ch_e,Ch_jian3,Ch_ton,Ch_bo,Ch_fang)
#endif //NINTAUS_OSD_STR
#endif

#define OS_ALL              _cat_(Ch_quan, Ch_die)                //T:(全碟重復)

#ifdef  USE_CHINESE_IN_JPEG_ROTATE
#define OS_PICTURE_ROTATE          _cat4_(Ch_tu,JCh_xiang,Ch_xuan1,Ch_zhuan1)   //S:(芞砉唅蛌)
#define OS_PICTURE_UPTURN          _cat4_(Ch_tu,JCh_xiang,Ch_fan2,Ch_zhuan1)    //S:(芞砉楹蛌)
#endif
#ifdef  VIDEO_SETUP_NEW_GUI
#define OS_ENTER_RETURN           _cat8_("  ",Ch_an,Ch_que1,Ch_ren1,Ch_jian3,Ch_hui1, Ch_zhu, Ch_ye)
#endif
#ifdef SETUP_PASSWORD_GUI       
#define OS_PASSWD_EDIT             _cat4_(Ch_mi, Ch_ma,Ch_xiu, Ch_gai)
#define OS_PASSWD_ERROR            _cat10_("  ",Ch_mi, Ch_ma,Ch_cuo, Ch_wu,Ch_qing,Ch_chong,Ch_xin2,Ch_shu,JCh_sru/*Ch_cuo, Ch_wu*/)
#define OS_PASSWD_SENTENCE1        _cat7_("  ",Ch_qing,Ch_shu,JCh_sru,Ch_jiu2,Ch_mi, Ch_ma) 
#define OS_PASSWD_SENTENCE2        _cat7_("  ",Ch_qing,Ch_shu,JCh_sru,Ch_xin2,Ch_mi, Ch_ma) 
#define OS_OLD_PASSWD              _cat4_("  ",Ch_jiu2,Ch_mi, Ch_ma) 
#define OS_NEW_PASSWD              _cat4_("  ",Ch_xin2,Ch_mi, Ch_ma) 
#endif
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)                  
#define OS_ONEKEY_SETUP          _cat5_(Ch_e,JCh_dian,Ch_ton,Ch_she,Ch_zhi5)
#define OS_PROFESSION_SETUP      _cat5_(Ch_zhuan,Ch_ye1,Ch_ji,Ch_she,Ch_zhi5)
#endif
#ifdef  LPCM_OUTPUT               
#define OS_FREQ_MASK            _cat6_("L","P","C","M",Ch_shu,Ch_chu)
#endif
#ifdef RECORD_KEY

#ifdef NINTAUS_OSD_STR   //2004-2-11 11:32桲迻P
#define OS_RECORD_1     _cat7_(Ch_ci3,Ch_die,Ch_pian,Ch_yi3,Ch_bei,Ch_ji1,Ch_yi1)          //S:(森詠眒暮砪)
#define OS_RECORD_2     _cat_("              ", "                    ")//_cat13_(Ch_qing,Ch_yu5, "6", Ch_miao3,Ch_nei, Ch_an,Ch_ji1,Ch_yi1, Ch_bo,Ch_fang,Ch_jian3,Ch_bo,  Ch_fang)
#define OS_RECORD_3     _cat13_(Ch_qing,Ch_yu5, "6", Ch_miao3,Ch_nei, Ch_an,Ch_ji1,Ch_yi1, Ch_bo,Ch_fang,Ch_jian3,Ch_bo,  Ch_fang)//_cat7_(Ch_yi1, Ch_bo,Ch_fang,"`",Ch_jian3,Ch_bo,  Ch_fang)

#else
#define OS_RECORD_1SENTENCE     _cat5_(Ch_ci2,Ch_die,Ch_yi2,Ch_ji1,Ch_yi1)          //S:(森詠眒暮砪)
#define OS_RECORD_2SENTENCE     _cat8_(Ch_an,Ch_ji1, Ch_yi1, Ch_jian3,Ch_ji1, Ch_yi1,Ch_bo, Ch_fang)
#define OS_RECORD_3SENTENCE     _cat10_("6", Ch_miao1,Ch_hou,Ch_jiang,Ch_zi, Ch_dong,Ch_shun, Ch_xu, Ch_bo, Ch_fang)
#endif //NINTAUS_OSD_STR

#define OS_RECORD_RESUME        _cat6_(Ch_hui, Ch_fu, Ch_ji1,Ch_yi1,Ch_bo, Ch_fang)

#endif

#define OS_PROG_PLAY            _cat4_(Ch_bian, Ch_cheng, Ch_bo, Ch_fang)               //T:(編程播放)
#ifdef NIN_612_STR_SHOW         // linrc modify 2004-6-7 14:14
#define OS_OSD                  _cat4_(Ch_xian3, Ch_shi2, Ch_yu2, Ch_yan1)
#define OS_TV_RATIO             _cat4_(Ch_hua, Ch_mian, Ch_bi1, Ch_li1) //T:(屏慕畫面比例)
#else
#define OS_OSD                  _cat6_(Ch_hua, Ch_mian, Ch_xian3, Ch_shi2, Ch_yu2, Ch_yan1) //T:(畫面顯示語言)
#define OS_TV_RATIO             _cat6_(Ch_ping, Ch_mu, Ch_hua, Ch_mian, Ch_bi1, Ch_li1) //T:(屏慕畫面比例)
#endif
#define OS_TV_SYS               _cat5_(Ch_dian, Ch_shi3, Ch_ji2, Ch_zhi1, Ch_shi)       //T:(電視機制式)
#define OS_EXIT_MENU            _cat6_(Ch_tui, Ch_chu, Ch_she, TCh_ding, Ch_cai, Ch_dan) //T:(退出設置菜單)

//xiaosan 02-06-13
#ifdef HUAJIA_DVD
#define OS_AUD_OUT              _cat4_(Ch_yin, Ch_pin, Ch_shu, Ch_chu)                  //T:(音頻輸出)
#else
#define OS_AUD_OUT              _cat4_(Ch_shu4, Ch_ma, Ch_shu, Ch_chu)                  //T:(數碼輸出)
#endif

#define OS_VIDEO                _cat4_(Ch_shi3, Ch_pin, Ch_shu, Ch_chu)                 //T:(視頻輸出)
#ifdef NIN_612_STR_SHOW     //linrc add 2004-6-7 13:42    
#define OS_PASSWORD             _cat4_(Ch_mi, Ch_ma,Ch_she,Ch_zhi5)                                     //T:(密碼)
#define OS_RATING               _cat4_(Ch_ji, Ch_bie,Ch_she,Ch_zhi5)
#else
#define OS_PASSWORD             _cat_(Ch_mi, Ch_ma)
#define OS_RATING               _cat_(Ch_ji, Ch_bie)                                    //T:(級別)
#endif
#define OS_BITSTREAM            _cat3_("SPDIF/", Ch_yuan2, Ch_ma)                       //T:(SPDIF/源碼)

//#define OS_ANALOG_6CH           _cat3_("AC3 6", Ch_sheng, Ch_dao)

//#define OS_ANALOG_2CH           _cat3_("AC3 2", Ch_sheng, Ch_dao)                       //T:(AC3 2聲道)
#ifdef  NINTAUS_OSD_STR
#define OS_YUV                  _cat_(Ch_shi3, Ch_pin)  
#else
#define OS_YUV                  _cat4_(Ch_shi3, Ch_pin, Ch_fen, Ch_liang)               //T:(視頻分量)
#endif
#define OS_AUTO                 _cat_(Ch_zi, Ch_dong)                                   //T:(自動)
#define OS_OFF                  Ch_guan                                                 //T:(關)
#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW//zhaoyanhua add  2003-12-6 14:10
#define OS_TRACKTIME            _cat4_(Ch_qu, Ch_mu1, Ch_shi1, Ch_jian)
#endif
                                              //T:(關)
#define OS_S_VIDEO              _cat3_("S ", Ch_duan, Ch_zi1)                           //T:(S 端子)

#if defined( BBK_DVD)||defined(HANYANG_DVD)  //3-11-14 8:00桲迻P
#define OS_16_9                 _cat_("16:9", "")                                   //T:(16:9 --)
#define OS_4_3LB                _cat_("4:3LB", "")                                   //T:(4:3LB --)
#define OS_4_3PS                _cat_("4:3PS", "")                                 //T:(4:3PS--)
#elif defined(SUPPORT_FUNCTION_MENU)
#define OS_16_9                 _cat_("16:9 WIDE", "")                                   //T:(16:9 --)
#define OS_4_3LB                _cat_("4:3 FULL", "")                                   //T:(4:3LB --)
#define OS_4_3PS                _cat_("4:3 NORMAL", "")                                 //T:(4:3PS--)
#elif defined(ALCO_DVD_UI)
#define OS_16_9                 _cat_("WIDE SCREEN", "")                                   //T:(16:9 --)
#define OS_4_3LB                _cat_("LETTER BOX", "")                                   //T:(4:3LB --)
#define OS_4_3PS                _cat_("PAN SCAN", "")                                 //T:(4:3PS--)
#else
#define OS_16_9                 _cat_("16:9", Ch_169)                                   //T:(16:9 --)
#define OS_4_3LB                _cat_("4:3LB", Ch_43)                                   //T:(4:3LB --)
#define OS_4_3PS                _cat_("4:3PS", Ch_43ps)                                 //T:(4:3PS--)
#endif

#if defined(NINTAUS_OSD_STR)||defined(JIEKE_DVD)	//"傖�佷�" wangfeng,2003-10-12 10:55
#define OS_KID_ONLY             _cat4_("1 ",Ch_er, Ch_tong, Ch_ji)
#define OS_ADULT             _cat4_("8 ", Ch_cheng1,JCh_ren, Ch_ji)
#else
#define OS_NO_ADULT             _cat4_(Ch_fei, "A", Ch_ji, Ch_pian)                     //T:(非A級片)
#define OS_KID_ONLY             _cat3_(Ch_er, Ch_tong, Ch_pian)                         //T:(兒童片)
#endif
#define OS_VIEW_ALL             _cat3_(Ch_vff, Ch_xian, Ch_zhi1)                        //T:(無限制)

#if defined(SHOW_5_1CH)
#define OS_6CH_SETUP            _cat3_("5.1", Ch_sheng, Ch_dao)                         //T:(5.1聲道)
#else
#define OS_6CH_SETUP            _cat5_("6", Ch_sheng, Ch_dao, Ch_she, TCh_ding)         //T:(6聲道設置)
#endif

#define OS_SUBWOOFER            _cat4_(Ch_chao, Ch_chong, Ch_di, Ch_yin)                //T:(超重低音)
#define OS_ON                   Ch_kai                                                  //T:(開)

#ifdef BBK_DVD
#define OS_DOBLY                _cat_(Ch_dolby,"D")//axel 2003/11/25 10:01PM
#else
#define OS_DOBLY                Ch_dolby
#endif

#define OS_CLEAR                _cat_(Ch_qing1, Ch_chu1)                                //T:(清除)
#define OS_EDIT                 _cat_(Ch_bian, Ch_jil)                                  //T:(編輯)
//#define OS_DIR1                 Ch_dir1
//#define OS_DIR2                 Ch_dir2
#define OS_DIR3                 Ch_dir3
#define OS_DIR4                 Ch_dir4
//#define OS_DIR5                 Ch_dir5

#ifdef SETUP_6_DIGIT_PASSWORD//zhaoyanhua add 03-10-14 13:28
#define OS_LOCK                 _cat8_("-","-","-","-","-","-", Ch_space, Ch_lock)              //T:(------ L)
#define OS_UNLOCK               _cat8_("-","-","-","-","-","-", Ch_space, Ch_unlock)            //T:(------ U)
#else //4 digit password 
#define OS_LOCK                 _cat6_("-","-","-","-", Ch_space, Ch_lock)              //T:(---- L)
#define OS_UNLOCK               _cat6_("-","-","-","-", Ch_space, Ch_unlock)            //T:(---- U)
#endif//end SETUP_6_DIGIT_PASSWORD

#define OS_TRK_S                _cat4_(Ch_dan, Ch_qu, Ch_sou, Ch_suo)                   //T:(單曲搜索)
#define OS_DISC_S               _cat4_(Ch_zong, Ch_die, Ch_sou, Ch_suo)                 //T:(總碟搜索)
#define OS_DIR0                 Ch_dir0
#define OS_DIR7                 Ch_dir7
#define OS_DIR8                 Ch_dir8
#define OS_DIR9                 Ch_dir9
#define OS_CH                   _cat_(Ch_sheng, Ch_dao)                                 //T:(聲道)
//#define OS_FIRMWARE_ID          _cat4_(Ch_ruan, Ch_jian2, Ch_bian, Ch_ma)               //T:(軟件編碼)
//#define OS_CHIP_ID              _cat4_(Ch_ci, Ch_pian, Ch_bian, Ch_ma)                  //T:(芯片編碼)
//#define OS_CHIP_ID              _cat_("CHIP", " ID")                                    //T:(芯片編碼)
#define OS_REGION_CODE          _cat_(Ch_qu2, Ch_ma)                                    //T:(區碼)
//#define OS_FUNCTION             _cat4_(Ch_fu, Ch_du, Ch_fu, Ch_chang)                   //T:(覆讀覆唱)
//#define OS_MODE                 _cat_(Ch_mo, Ch_shi)                                    //T:(模式)
//#define OS_RECORD               _cat_(Ch_fu, Ch_chang)                                  //T:(覆唱)
//#define OS_STUDY                _cat_(Ch_fu, Ch_du)                                     //T:(覆讀)
//#define OS_FOLLOW               _cat_(Ch_gen, Ch_du)                                    //T:(跟讀)
//#define OS_COMPARE              _cat_(Ch_dui, Ch_bi1)                                   //T:(對比)
//#define OS_COUNTER              _cat4_(Ch_chong, Ch_fu, Ch_ci1, Ch_shu4)                //T:(重覆次數)
//#define OS_LEVEL                _cat4_(Ch_lu, Ch_yin, Ch_mo, Ch_shi)                    //T:(錄音模式)
//#define OS_HIGH                 _cat3_(Ch_gao, Ch_pin1, Ch_zhi2)                        //T:(高品質)
//#define OS_NORMAL               _cat4_(Ch_chao, Ch_chang1, Ch_shi1, Ch_jian)            //T:(超長時間)
//#define OS_SUPER                _cat4_(Ch_chao, Ch_gao, Ch_pin1, Ch_zhi2)               //T:(超高品質)
//#define OS_OPERATING            _cat4_(Ch_diao, Ch_jie, Ch_fang1, Ch_shi)               //T:(調節方式)
//#define OS_MANUAL               _cat_(Ch_shou, Ch_dong)                                 //T:(手動)
#define OS_DIR10                Ch_dir10
#define OS_DIR11                Ch_dir11
#define OS_CONCERT              _cat3_(Ch_yin, Ch_yue, Ch_ting1)                        //T:(音樂廳)
#define OS_CHURCH               _cat_(Ch_jiao1, Ch_tang)                                //T:(教堂)
#define OS_PASSIVE              _cat_(Ch_huan1, Ch_rao)  
#ifdef JIEKE_DVD                               //T:(環繞)
#define OS_WIDE                 _cat_(Ch_da1, Ch_ting1)
#else
#define OS_WIDE                 _cat_(Ch_kuan, Ch_chang2)
#endif                               //T:(寬場)
//#define OS_AMPHITH              _cat3_(Ch_yuan1, Ch_ju, Ch_chang2)                      //T:(圓劇場)
//#define OS_STADIUM              _cat3_(Ch_ti, Ch_yu1, Ch_guan1)                         //T:(体育館)
#ifdef BBK_DVD
#define OS_LIGHT_MUSIC         	_cat3_(Ch_qing2,Ch_yin,Ch_yue)							//S ш秞氈
#define OS_5_1_CHANNEL           _cat3_("5.1", Ch_sheng, Ch_dao)
#endif
#define OS_ELECTRON				_cat_(Ch_dian,Ch_zi1)       							//S  萇赽

#define OS_EQ                   _cat_(Ch_jun, Ch_hen)                                   //T:(均衡)
#define OS_STANDARD             _cat_(Ch_biao, Ch_zhun)                                 //T:(標準)
#define OS_CLASSIC              _cat_(Ch_gu, Ch_dian1)                                  //T:(古典)
#define OS_ROCK                 _cat_(Ch_yao, Ch_gun)                                   //T:(搖滾)
#define OS_JAZZ                 _cat_(Ch_jue, Ch_shil)                                  //T:(爵土)
#define OS_POP                  _cat_(Ch_liul, Ch_xing1)                                //T:(流行)
#define OS_USER                 _cat_(Ch_ge, Ch_xing)                                   //T:(個性)
#define OS_ATTRIB               _cat_(Ch_ge, Ch_xing)                                   //T:(個性)
#ifdef	NINTAUS_OSD_STR			//Maoyong 2004.03.04
#define OS_SF                   _cat_(Ch_man, Ch_fang)                                   //T:(慢進)
#else	
#define	OS_SF					_cat_(Ch_man, Ch_jin)
#endif
#define OS_SB                   _cat_(Ch_man, Ch_tui)                                   //T:(慢退)
#define OS_CSPK                 _cat5_(Ch_zhong, Ch_zhi5, Ch_yang, Ch_sheng, Ch_qi)     //T:(中置揚聲器)
#define OS_SSPK                 _cat5_(Ch_huan1, Ch_rao, Ch_yang, Ch_sheng, Ch_qi)      //T:(環繞揚聲器)
#define OS_CSPK_DELAY           _cat4_(Ch_zhong, Ch_zhi5, Ch_yan, Ch_shi1)              //T:(中置延時)
#define OS_SSPK_DELAY           _cat4_(Ch_huan1, Ch_rao, Ch_yan, Ch_shi1)               //T:(環繞延遲時)
#define OS_FSPK                 _cat5_(Ch_qian, Ch_zhi5, Ch_yang, Ch_sheng, Ch_qi)      //T:(前置揚聲器)

#define OS_SYS_SETUP            _cat4_(Ch_xi1, Ch_tong2, Ch_she, TCh_ding)              //T:(系統設置)
#define OS_SPK_SETUP            _cat5_(Ch_yang, Ch_sheng, Ch_qi, Ch_she, TCh_ding)      //T:(揚聲器設置)
#define OS_AUD_SETUP            _cat4_(Ch_yin, Ch_pin, Ch_she, TCh_ding)                //T:(音頻設置)

// video setup
#define OS_VIDEO_SETUP		    _cat4_(Ch_shi3, Ch_pin, Ch_she, TCh_ding)               //T:(視頻設定)
#define OS_BRIGHT_SETUP			_cat_(Ch_liang2, Ch_du2)                                //T:(亮度)

#if 1//def  NINTAUS_OSD_STR         //Maoyong for NINTAUS 2004.03.02
#define OS_CONTRAST 			_cat3_(Ch_dui, Ch_bi1, Ch_du2)                                   //T:(對比)
#else
#define OS_CONTRAST             _cat_(Ch_dui, Ch_bi1)
#endif

#define OS_HUE 		        	_cat_(Ch_se, Ch_diao)                                   //T:(色調)
#define OS_SATURATION        	_cat3_(Ch_bao2, Ch_he2, Ch_du2)                         //T:(飽和度)


// pro-logic II setup
//#define OS_PROLOGIC
#define OS_PL_MOVIE         _cat4_(Ch_dian, Ch_ying1, Ch_mo, Ch_shi)
#define OS_PL_MUSIC 		_cat4_(Ch_yin, Ch_yue, Ch_mo, Ch_shi)

#define OS_DEFAULT_SETUP        _cat3_(Ch_que, Ch_sheng3, Ch_zhi4)                      //T:(缺省值)
#ifdef AUTO_PLAY
#define OS_SSAVER_SETUP         _cat4_(Ch_zi, Ch_dong, Ch_bo, Ch_fang)                   //T:(屏幕保護)
#elif defined(VCD_CDG_PLAY_CONTROL_BY_SETUPMENU)
#define OS_SSAVER_SETUP         _cat_("   MNP  "," ")
#else
#define OS_SSAVER_SETUP         _cat4_(Ch_ping, Ch_mu, Ch_bao, Ch_hu)                   //T:(屏幕保護)
#endif
#define OS_SSAVER_1             _cat3_(Ch_mo, Ch_shi, " 1")                             //T:(模式 1)
#define OS_SSAVER_2             _cat3_(Ch_mo, Ch_shi, " 2")                             //T:(模式 2)
#define OS_SSAVER_3             _cat3_(Ch_mo, Ch_shi, " 3")                             //T:(模式 3)

#define OS_MIC_ONOFF            _cat4_(Ch_hua1, Ch_tong1, Ch_she, TCh_ding)              //T:(話筒設置)
#define OS_DIGITAL_SETUP        _cat6_(Ch_du1, Ch_bi1, Ch_shu4, Ch_ma, Ch_she, TCh_ding) //T:(杜比數碼設置)

#define OS_MIC_VOL              _cat4_(Ch_hua1, Ch_tong1, Ch_yin, Ch_liang)             //T:(話筒音量)
#define	OS_MIC_VOL_1			_cat5_(Ch_hua1, Ch_tong1, Ch_yin, Ch_liang,"1")
#define	OS_MIC_VOL_2			_cat5_(Ch_hua1, Ch_tong1, Ch_yin, Ch_liang,"2")
#define OS_CD_DEBUG             _cat3_(Ch_jou, Ch_cuo, Ch_zhong)                        //T:(糾錯中)
#define OS_SMART_UPGRADE        _cat4_(Ch_zhi3, Ch_neng, Ch_sheng2, Ch_ji)              //T:(智能升級)
#define OS_UPGRADE_TO           _cat3_(Ch_sheng2, Ch_ji, Ch_cheng1)                     //T:(升級成)
#define OS_UPGRADING            _cat3_(Ch_sheng2, Ch_ji, Ch_zhong)                      //T:(升級中)
#define OS_NOT_POWEROFF         _cat3_(Ch_wu1, Ch_guan, Ch_ji2)                         //T:(勿關機)
//nono del.
#define OS_REGION_1             _cat_("1 ", Ch_qu2)                                     //T:(1 區)
#define OS_REGION_2             _cat_("2 ", Ch_qu2)                                     //T:(2 區)
#define OS_REGION_3             _cat_("3 ", Ch_qu2)                                     //T:(3 區)
#define OS_REGION_4             _cat_("4 ", Ch_qu2)                                     //T:(4 區)

#define OS_LANG_SETUP           _cat4_(Ch_yu2, Ch_yan1, Ch_she, TCh_ding)               //T:語言設置
#define OS_SURROUND_SETUP       _cat4_(Ch_huan1, Ch_rao, Ch_she, TCh_ding)              //T:環繞設置

#ifdef SUPPORT_CC_ONOFF//liweihua add 20031118
#define OS_CLOSED_CAPTION  		_cat5_(Ch_long,Ch_ya1,Ch_ren,Ch_zi2, Ch_mu)	//S:趼躉//liweihua add for syber 20031118
#endif
#ifdef SUPPORT_ANGLE_MARK
#define OS_ANGLE_MARK			_cat4_(Ch_jiao,Ch_du3,Ch_biao,Ch_ji1)	//S:褒僅梓暮//liweihua add for syber 20031118
#endif
#define OS_RETURN_MAIN_SETUP    _cat3_(Ch_hui1, Ch_zhu, Ch_ye)                          //T:回主頁
#define OS_AUDIO_LANG_SETUP     _cat4_(Ch_yin, Ch_pin, Ch_yu2, Ch_yan1)                 //T:音頻語言
#define OS_SUBTITLE_LANG_SETUP  _cat4_(Ch_zi2, Ch_mu, Ch_yu2, Ch_yan1)                  //T:字幕語言
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:29
#define OS_SUBTITLE_LANG_2ND_SETUP  _cat5_(Ch_zi2, Ch_mu, Ch_yu2, Ch_yan1, " 2")
#endif
#define OS_MENU_LANG_SETUP      _cat4_(Ch_cai, Ch_dan, Ch_yu2, Ch_yan1)                 //T:菜單語言
#ifdef	JIEKE_DVD	//"坫髦耀宒" wangfeng 2003-10-12 17:46
#define OS_DOWNMIX_SETUP        _cat4_(Ch_suo1, Ch_hun, Ch_mo, Ch_shi)                    //T:混合模式
#elif defined(BBK_NEW_SETUP)          //kubby,3-10-19 21:11
#define OS_DOWNMIX_SETUP		_cat6_(Ch_yin, Ch_pin, Ch_shu, Ch_chu, Ch_mo, Ch_shi)
#else
#define OS_DOWNMIX_SETUP        _cat4_(Ch_hun, Ch_he, Ch_mo, Ch_shi)                    //T:混合模式
#endif
#ifdef NINTAUS_OSD_STR
#define OS_RESTORE_SETUP1               _cat6_(Ch_jin8, Ch_zheng1, Ch_kai, Ch_ji2,Ch_hua, Ch_mian)
#define OS_RESTORE_SETUP              _cat_(Ch_fu, Ch_yuan)
#define OS_P_SCAN_YUV		     _cat_(Ch_zhu1, Ch_xing1)   
#else
#define OS_RESTORE_SETUP        _cat_(Ch_fu, Ch_yuan)                                   //T:復原
#endif
#ifdef AD_TCL//2004-3-22 13:20 lijd
#define OS_VSURROUND_SETUP      _cat4_(Ch_xu1, Ch_ni, Ch_huan1, Ch_rao)       //T:虛擬環繞聲
#else
#define OS_VSURROUND_SETUP      _cat5_(Ch_xu1, Ch_ni, Ch_huan1, Ch_rao, Ch_sheng)       //T:虛擬環繞聲
#endif
#define OS_DOLBY_OP_SETUP       _cat4_(Ch_shu, Ch_chu, Ch_mo, Ch_shi)                   //T:輸出模式
#define OS_DOLBY_LINE_SETUP     _cat4_(Ch_xian2, Ch_lu1, Ch_shu, Ch_chu)                //T:線路輸出
#define OS_DOLBY_RF_SETUP       _cat3_("RF", Ch_diao, Ch_zheng)                         //T:RF 調整
#define OS_DUAL_MONO_SETUP      _cat3_(Ch_zuo, "+", Ch_you1)                            //T:左+右
#ifdef BBK_NEW_SETUP			 //kubby,3-10-19 21:24
#define OS_BASS_MANAGEMENT		_cat5_(Ch_yang, Ch_sheng, Ch_qi, Ch_mo, Ch_shi)					//T:低音模式
#else 
#define OS_BASS_MANAGEMENT		_cat4_(Ch_di, Ch_yin, Ch_mo, Ch_shi)					//T:低音模式
#endif

#define OS_BASS_MODE_1			_cat4_(Ch_da1, Ch_yang, Ch_sheng, Ch_qi)    	 		//T:大揚聲器
#define OS_BASS_MODE_2			_cat4_(Ch_xiao2, Ch_yang, Ch_sheng, Ch_qi)				//T:小揚聲器
#define OS_BASS_MODE_3			_cat5_(Ch_hun, Ch_he, Ch_yang, Ch_sheng, Ch_qi)			//T:混合揚聲器

#define OS_MIX_MONO_SETUP       _cat4_(Ch_hun, Ch_he, Ch_sheng, Ch_dao)                 //T:混合聲道
#define OS_SURROUND_MODE        _cat4_(Ch_huan1, Ch_rao, Ch_mo, Ch_shi2)                //T:環繞模式

#ifdef PRE_STOP_DEFINE2_PRESS_PLAY_KEY_TO_CONTINUE
#define OS_PRE_STOP             _cat7_(Ch_qing, Ch_an, Ch_bo, Ch_fang, Ch_jian3, Ch_ji3, Ch_xu2)
#else//#ifdef PRE_STOP_DEFINE2_PRESS_PLAY_KEY
#define OS_PRE_STOP             _cat3_(Ch_zhun, Ch_ting, Ch_zhi)                        //T:准停止              S:袧礿砦
#endif//#ifdef PRE_STOP_DEFINE2_PRESS_PLAY_KEY

#define OS_SCORE                _cat_(Ch_fen, Ch_shu4)                                  //T:分數
#define OS_MARK                 _cat_(Ch_ji1, Ch_yi1)                                   //T:記憶
#define OS_DYNAMICRANGE         _cat4_(Ch_dong, Ch_tai, Ch_fan1, Ch_wei)                //T:動態範圍

//#define OS_SFE_OUT              _cat6_(Ch_chao, Ch_chong, Ch_di, Ch_yin, Ch_shu, Ch_chu)//T:超重低音輸出
//#define OS_SFE_STD              _cat4_(Ch_biao, Ch_zhun, Ch_mo, Ch_shi)                 //T:標准模式
//#define OS_SFE_EHNANCE          _cat4_(Ch_jia, Ch_qiang, Ch_mo, Ch_shi)                 //T:高效模式

#define OS_GROUP				_cat_(Ch_qun,Ch_zu)										//T:群組

#ifdef USE_CHINESE_IN_JPEG_MODE           //fengjl add 4-1-8 10:15        
#define OS_WIPE_TOP                     _cat6_(Ch_you2, Ch_shang, Ch_zhi7, Ch_xia,Ch_jin, Ch_tu)    //蚕奻祫狟輛芞  
#define OS_WIPE_BOTTOM                  _cat6_(Ch_you2, Ch_xia, Ch_zhi7, Ch_shang,Ch_jin, Ch_tu)  //蚕狟祫奻輛芞
#define OS_WIPE_LEFT                    _cat6_(Ch_you2, Ch_zuo, Ch_zhi7, Ch_you1,Ch_jin, Ch_tu)  //蚕酘祫衵輛芞
#define OS_WIPE_RIGHT                   _cat6_(Ch_you2, Ch_you1, Ch_zhi7, Ch_zuo,Ch_jin, Ch_tu)  //蚕衵祫酘輛芞 
#define OS_DIGONAL_WIPE_LEFT_TOP        _cat8_(Ch_you2, Ch_zuo, Ch_shang,Ch_zhi7,Ch_you1,Ch_xia,Ch_jin, Ch_tu)  //蚕酘奻祫衵狟輛芞
#define OS_DIGONAL_WIPE_RIGHT_TOP       _cat8_(Ch_you2, Ch_you1, Ch_shang,Ch_zhi7,Ch_zuo,Ch_xia,Ch_jin, Ch_tu)  //蚕衵奻祫酘狟輛芞
#define OS_DIGONAL_WIPE_LEFT_BOTTOM     _cat8_(Ch_you2, Ch_zuo, Ch_xia,Ch_zhi7,Ch_you1,Ch_shang,Ch_jin, Ch_tu)  //蚕酘狟祫衵奻輛芞
#define OS_DIGONAL_WIPE_RIGHT_BOTTOM    _cat8_(Ch_you2, Ch_you1, Ch_xia,Ch_zhi7,Ch_zuo,Ch_shang,Ch_jin, Ch_tu)  //蚕衵奻祫酘狟輛芞
#define OS_EXTEND_FROM_CENTER_H         _cat9_(Ch_you2, Ch_zhong,Ch_jian,Ch_xiang2,Ch_shang,Ch_xia,Ch_zhan,Ch_kai,Ch_tu)  //蚕笢潔砃奻狟桯羲芞
#define OS_EXTEND_FROM_CENTER_V         _cat9_(Ch_you2, Ch_zhong,Ch_jian,Ch_xiang2,Ch_zuo,Ch_you1,Ch_zhan,Ch_kai,Ch_tu)  //蚕笢潔砃酘衵桯羲芞
#define OS_COMPRESS_TO_CENTER_H         _cat9_(Ch_you2, Ch_shang, Ch_xia,Ch_xiang2,Ch_zhong,Ch_jian,Ch_zhan,Ch_kai,Ch_tu)  //蚕奻狟砃笢潔桯羲芞
#define OS_COMPRESS_TO_CENTER_V         _cat9_(Ch_you2, Ch_zuo,Ch_you1,Ch_xiang2,Ch_zhong,Ch_jian,Ch_zhan,Ch_kai,Ch_tu)  //蚕酘衵砃笢潔桯羲芞
#define OS_WINDOW_H                     _cat9_(Ch_you2, Ch_shang,Ch_xiang2,Ch_xia,Ch_fen,Ch_ceng,Ch_zhan,Ch_kai,Ch_tu)  //蚕奻砃狟煦脯桯羲芞
#define OS_WINDOW_V                     _cat9_(Ch_you2, Ch_zuo,Ch_xiang2,Ch_you1,Ch_fen,Ch_ceng,Ch_zhan,Ch_kai,Ch_tu)  //蚕酘砃衵煦脯桯羲芞
#define OS_WIPE_FROM_EDGE_TO_CENTER     _cat8_(Ch_you2, Ch_si2,Ch_zhou,Ch_xiang2,Ch_zhong,Ch_jian,Ch_jin, Ch_tu)  //蚕侐笚砃笢潔輛芞
#define OS_RANDOM_WAY                   _cat4_(Ch_sui, Ch_ji2,Ch_jin, Ch_tu)//272  //呴儂輛芞
#define OS_NONE_WAY                     _cat4_(Ch_zheng1, JCh_chang,Ch_jin, Ch_tu)//273  //淏都輛芞
#endif//USE_CHINESE_IN_JPEG_MODE


#ifdef USE_JAPANESE_IN_JPEG_MODE           //hq, 2004-3-11 14:10        
#define JOS_WIPE_TOP                     _cat5_(Ch_shang, JCh_jpcong, JCh_jpdao, Ch_xia, JCh_he)    //蚕奻祫狟輛芞  
#define JOS_WIPE_BOTTOM                  _cat5_(Ch_xia, JCh_jpcong, JCh_jpdao, Ch_shang, JCh_he)   //蚕狟祫奻輛芞
#define JOS_WIPE_LEFT                    _cat5_(Ch_zuo, JCh_jpcong, JCh_jpdao, Ch_you1, JCh_he)   //蚕酘祫衵輛芞
#define JOS_WIPE_RIGHT                   _cat5_(Ch_you1, JCh_jpcong, JCh_jpdao, Ch_zuo, JCh_he)  //蚕衵祫酘輛芞 
#define JOS_DIGONAL_WIPE_LEFT_TOP        _cat9_(Ch_zuo,  Ch_shang, JCh_jpjiao, JCh_jpcong, JCh_jpdao, Ch_you1,Ch_xia, JCh_jpjiao, JCh_he)  //蚕酘奻祫衵狟輛芞
#define JOS_DIGONAL_WIPE_RIGHT_TOP       _cat9_(Ch_you1, Ch_shang, JCh_jpjiao, JCh_jpcong, JCh_jpdao, Ch_zuo,Ch_xia, JCh_jpjiao, JCh_he)  //蚕衵奻祫酘狟輛芞
#define JOS_DIGONAL_WIPE_LEFT_BOTTOM     _cat9_(Ch_zuo,  Ch_xia, JCh_jpjiao, JCh_jpcong, JCh_jpdao, Ch_you1, Ch_shang, JCh_jpjiao, JCh_he)  //蚕酘狟祫衵奻輛芞
#define JOS_DIGONAL_WIPE_RIGHT_BOTTOM    _cat9_(Ch_you1, Ch_xia, JCh_jpjiao, JCh_jpcong, JCh_jpdao, Ch_zuo, Ch_shang, JCh_jpjiao, JCh_he)  //蚕衵奻祫酘狟輛芞
#define JOS_EXTEND_FROM_CENTER_H         _cat7_(Ch_zhong,JCh_jpjian,JCh_jpcong, JCh_jpdao, Ch_shang,Ch_xia,JCh_he)  //蚕笢潔砃奻狟桯羲芞
#define JOS_EXTEND_FROM_CENTER_V         _cat7_(Ch_zhong,JCh_jpjian,JCh_jpcong, JCh_jpdao, Ch_zuo,Ch_you1,JCh_he)  //蚕笢潔砃酘衵桯羲芞
#define JOS_COMPRESS_TO_CENTER_H         _cat7_(Ch_shang, Ch_xia,JCh_jpcong, JCh_jpdao, Ch_zhong,JCh_jpjian, JCh_he)  //蚕奻狟砃笢潔桯羲芞
#define JOS_COMPRESS_TO_CENTER_V         _cat7_(Ch_zuo,Ch_you1,JCh_jpcong, JCh_jpdao, Ch_zhong,JCh_jpjian, JCh_he)  //蚕酘衵砃笢潔桯羲芞
#define JOS_WINDOW_H                     _cat4_(JCh_jpheng, JCh_jpgao,JCh_jpmu,JCh_jpyang)  //蚕奻砃狟煦脯桯羲芞
#define JOS_WINDOW_V                     _cat4_(JCh_jpzong, JCh_jpgao,JCh_jpmu,JCh_jpyang)  //蚕酘砃衵煦脯桯羲芞
#define JOS_WIPE_FROM_EDGE_TO_CENTER     _cat10_(Ch_shang, Ch_xia, Ch_zuo, Ch_you1, JCh_jpjiao, JCh_jpcong, JCh_jpdao, Ch_zhong, JCh_jpxin, JCh_he)  //蚕侐笚砃笢潔輛芞
#define JOS_RANDOM_WAY                   _cat5_(JCh_ri, JCh_hi,JCh_banzhuoyin,JCh_jpyi,JCh_to)//呴儂輛芞
#define JOS_NONE_WAY                     _cat_("","")//淏都輛芞

#define JOS_ROTATE_LEFT                  _cat10_(JCh_jpshi, JCh_jpji, JCh_jpni, JCh_jpfan, JCh_jpdui, Ch_fang1, JCh_jpxiang, JCh_jpcc, Ch_hui1, JCh_jpzhuan)
#define JOS_ROTATE_RIGHT                 _cat7_(JCh_jpshi, JCh_jpji, Ch_fang1, JCh_jpxiang, JCh_jpcc, Ch_hui1, JCh_jpzhuan)
#define JOS_UP_DOWN                      _cat5_(Ch_shang, Ch_xia, JCh_jpcc, JCh_jpfan, JCh_jpzhuan)
#define JOS_LEFT_RIGHT                   _cat5_(Ch_zuo, Ch_you1, JCh_jpcc, JCh_jpfan, JCh_jpzhuan)
#endif//USE_JAPENESE_IN_JPEG_MODE

//Ti3001_OSD_UI_2     gerry  2-8-27 13:19

#if defined(Ti3001_OSD_UI_2)||defined(Ti3001_OSD_UI_1)||defined(Ti5026_OSD_UI_1)
#define OS_AMP_SETUP1           _cat5_(Ch_gong,Ch_fang,Ch_she, TCh_ding,"1")    //髡溫扢隅1
#define OS_AMP_SETUP2           _cat5_(Ch_gong,Ch_fang,Ch_she, TCh_ding,"2")    //髡溫扢隅2

#define OS_AMP_DYNAMICRANGE     _cat4_(Ch_dong, Ch_tai, Ch_fan1, Ch_wei)  //雄怓毓峓
#define OS_AMP_TREMBLE          _cat_(Ch_gao,Ch_yin)                      //詢秞
#define OS_AMP_BASS             _cat_(Ch_di, Ch_yin)                      //腴秞

#define OS_AMP_SUBWOOFER        _cat3_(Ch_chong, Ch_di, Ch_yin)               //笭腴秞
#define OS_AMP_CSPK             _cat_(Ch_zhong, Ch_zhi5)                      //笢离
#define OS_AMP_SSPK             _cat_(Ch_huan1, Ch_rao)                       //遠��
#ifndef SUPPORT_FUNCTION_MENU
#define OS_AMP_SSPK_BALANCE     _cat4_(Ch_huan1, Ch_rao,Ch_ping2,Ch_heng)     //遠�ぢ蝶�
#endif 
#define OS_AMP_FSPK             _cat_(Ch_qian, Ch_zhi5)                       //ヶ离
#ifndef SUPPORT_FUNCTION_MENU
#define OS_AMP_FSPK_BALANCE     _cat4_(Ch_qian, Ch_zhi5,Ch_ping2,Ch_heng)     //ヶ离す算
#endif 
#define OS_AMP_MAINVOLUME       _cat3_(Ch_zhu,Ch_yin, Ch_liang)                //翋秞講
#endif


//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)

#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP		//gerry for gbm,2004-2-2 14:12
	#define TOS_NEXT_PAGE    _cat4_(Ch_gao, TCh_ji, TCh_she, TCh_ding)
	#define TOS_PREV_PAGE    _cat3_(Ch_shang, Ch_e, TCh_ye)
	#define OS_NEXT_PAGE    _cat4_(Ch_gao,	Ch_ji, 	Ch_she, TCh_ding)
	#define OS_PREV_PAGE    _cat3_(Ch_shang, Ch_e, Ch_ye)
#else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
#define TOS_NEXT_PAGE    _cat3_(Ch_xia, Ch_e, TCh_ye)
#define TOS_PREV_PAGE    _cat3_(Ch_shang, Ch_e, TCh_ye)
#define OS_NEXT_PAGE    _cat3_(Ch_xia, Ch_e, Ch_ye)
#define OS_PREV_PAGE    _cat3_(Ch_shang, Ch_e, Ch_ye)
#endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP

#endif

#ifdef SUPPORT_MIDI//nono 20041109
#define OS_MELODY_ON              _cat4_(Ch_zhu,Ch_xuan2,Ch_lv1,Ch_kai)  
#define OS_MELODY_OFF             _cat4_(Ch_zhu,Ch_xuan2,Ch_lv1,Ch_guan)  
#endif

#ifdef MIDI_EJECT_PASSWORD        //ouyang 2004-11-20
#define OS_EJECT_PASSWORD   _cat4_(Ch_qing,Ch_shu,Ch_mi,Ch_ma)  
#endif

#ifdef USER_MPEG_LOGO
#define OS_SELECT_LOGO  _cat4_(Ch_hua, Ch_mian, Ch_xuan, Ch_ze)
#define OS_MPEG_LOGO    _cat4_(Ch_zi,TCh_ding,Ch_hua, Ch_mian)
#endif 

#ifdef ADD_DVI311_SETUP
#define OS_DVI311_FORMAT		_cat4_(Ch_shu, Ch_chu, Ch_xuan, Ch_ze)
#define OS_DVI311_MODE 			_cat4_(Ch_shu,Ch_chu,Ch_mo,Ch_shi) 
#define OS_DVI311_ANOLOG_OUTPUT _cat4_(Ch_mo,Ch_ni,Ch_shu,Ch_chu) 
#define OS_DVI311_DIGIT_OUTPUT  _cat4_(Ch_shu4,Ch_zi2,Ch_shu,Ch_chu)
#endif

#ifdef NEWSTYLE_WINDOW
#define OS_PLAYTIME    _cat4_(Ch_bo, Ch_fang,Ch_shi1, Ch_jian)
#define OS_TITLETIME    _cat4_(Ch_biao, Ch_ti1,Ch_shi1, Ch_jian)
#define OS_CHPTIME    _cat4_(Ch_zhang, Ch_jie,Ch_shi1, Ch_jian)

#endif
//Ti3001_OSD_UI_2

//language string
#define OS_JAPAN                _cat_(Ch_ri, Ch_yu2)                                    //T:日語
#define OS_FRENCH               _cat_(Ch_fa1, Ch_yu2)                                   //T:法語
#define OS_GERMAM               _cat_(Ch_de, Ch_yu2)                                    //T:德語
#define OS_SPANISH              _cat3_(Ch_xi, Ch_ban1, Ch_ya)                           //T:西班牙
#define OS_PORTUGUESE           _cat3_(Ch_pu, Ch_tao, Ch_ya)                            //T:葡萄牙
#define OS_LATIN                _cat3_(Ch_la, Ch_ding1, Ch_yu2)                         //T:拉丁語


//KONKA

#define OS_ACT_PLAY             _cat4_(Ch_jie, Ch_mu1, Ch_bo, Ch_fang)                  //S:誹醴畦溫
#define OS_READY_COPY           _cat4_(Ch_kyu, TCh_ding,Ch_lu, Ch_kxiang)               //S:啎隅翹砓
#define OS_TV_PROGRAM           _cat4_(Ch_dian, Ch_shi3,Ch_jie, Ch_mu1)                 //S:萇弝誹醴
#define OS_COPY_PLAY            _cat4_(Ch_lu, Ch_kxiang, Ch_bo, Ch_fang)                //S:翹砓畦溫
#define OS_DVDPLAY              _cat3_("DVD", Ch_bo, Ch_fang)                           //S:dvd畦溫
#define OS_MAKE_LANG            _cat4_(Ch_kcao,Ch_kzuo,Ch_yu2,Ch_yan1)                  //S:紱釬逄晟
#define OS_CH_SEARCH            _cat4_(Ch_pin, Ch_dao, Ch_sou, Ch_suo)                  //S:け耋刲坰
#define OS_COPY_SETUP           _cat4_(Ch_lu, Ch_kxiang, Ch_she, TCh_ding)              //S:翹砓扢隅
#define OS_HIGH_LEVEL           _cat_(Ch_gao,Ch_ji)                                     //S:詢撰
#define OS_NORMAL_LEVEL         _cat_(Ch_kpu,Ch_ktong)                                  //S:ぱ籵
#define OS_MASS                 _cat_(Ch_zhi2,Ch_liang)                                 //S:窐講

#define OS_TVFORMAT             _cat_(Ch_zhi1,Ch_shi)                                   //S:秶宒
#define OS_AUTO_SEARCH          _cat4_(Ch_zi,Ch_dong,Ch_xuan,Ch_ktai)                   //S:赻雄恁怢
#define OS_HAND_SEARCH          _cat4_(Ch_shou,Ch_dong,Ch_xuan,Ch_ktai)                 //S:忒雄恁怢
#define OS_ACT_EDIT             _cat4_(Ch_jie,Ch_mu1,Ch_bian,Ch_ji1)                    //S:誹醴晤憮
#define OS_ACT_NUM              _cat3_(Ch_jie,Ch_mu1,Ch_khao)                           //S:誹醴瘍
#define OS_CH_NUM               _cat3_(Ch_pin,Ch_dao,Ch_khao)                           //S:け耋瘍
#define OS_FREQUENCY            _cat_(Ch_pin,Ch_klv)                                    //S:け薹
#define OS_COLORS               _cat_(Ch_kcai,Ch_kse)                                   //S:粗伎
#define OS_PARTNER              _cat_(Ch_kban,Ch_yin)                                   //S:圈秞
#define OS_ACT_SWOP             _cat4_(Ch_jie,Ch_mu1,Ch_dui,Ch_diao)                    //S:誹醴勤覃
#define OS_NONCE_ACT_NUM        _cat5_(Ch_mu1,Ch_qian,Ch_jie,Ch_mu1,Ch_khao)            //S:醴ヶ誹醴瘍
#define OS_AIM_ACT_NUM          _cat5_(Ch_mu1,Ch_biao,Ch_jie,Ch_mu1,Ch_khao)            //S:醴梓誹醴瘍
#define OS_SSAVEE               _cat_(Ch_bao,Ch_kcun)                                   //S:悵湔
#define OS_SSYSS_SPACE          _cat6_(Ch_xi1,Ch_tong2,Ch_zan,Ch_yong,Ch_kkong,Ch_jian) //S:炵苀婃蚚諾潔
#define OS_DVDSETUP             _cat3_("DVD",Ch_she,TCh_ding)                           //S:DVD_SETUP
#define OS_AVSVHS               _cat3_("AV","/","SVHS")
#define OS_YEAR                 _cat_(Ch_knian,":")
#define OS_MOUTH                _cat_(Ch_kyue,":")
#define OS_DAY                  _cat_(Ch_ri,":")
#define OS_HOUR                 _cat_(Ch_shi,":")
#define OS_MINUTE               _cat_(Ch_fen,":")

#define OS_COPY_NUM     _cat_(Ch_xu,Ch_khao)//S:唗瘍
#define OS_COPY_NAME        _cat5_(Ch_space,Ch_jie,Ch_mu1,"/",Ch_pin)//S:誹醴/け      //clead
#define OS_STARTTIME        _cat4_(Ch_kai,Ch_bo,Ch_shi1, Ch_jian)//S:羲畦奀潔
#define OS_TOTALTIME        _cat3_(Ch_zong,Ch_shi1, Ch_jian)//S:軞奀潔
#define OS_CH_NUM2      _cat_(Ch_dao,Ch_khao)//S:耋瘍


//KONKA

//#ifdef	KARAOKE_MENU
#if defined(KARAOKE_MENU)||defined(QSI_SETUP_MENU)//liweihua 2004-6-16
#define	OS_KARAOKE_SETUP	_cat3_("KARAOKE",Ch_she,TCh_ding) 	//S:KARAOKE扢隅
#endif














//special case
#define OS_ICON_CDDA            Ch_CDDA

#if defined(SHOW_VCD_VER_INFO)||defined(SYBER_DVD)  //yaowh for kenloon 04-08-03
#define OS_ICON_VCD             _cat_(Ch_VCD,"1.0")
#define OS_ICON_VCD20           _cat_(Ch_VCD,"2.0")    //xulf 2003-11-17
#else
#define OS_ICON_VCD             Ch_VCD
#endif

#define OS_ICON_SVCD            Ch_SVCD
#define OS_ICON_DVD             Ch_DVD
//#define OS_ICON_MP3             Ch_MP3
#define OS_ICON_SUBT            Ch_SUBT
#define OS_ICON_LANG            Ch_LANG
#define OS_ICON_ANGLE           Ch_ANGLE

#define OS_ICON_CDROM           Ch_CDROM

#ifdef SUPPORT_HD_RESOLUTION
#define OS_HD_OUTPUT            _cat4_(Ch_gao, Ch_qing1, TCh_shu1, Ch_chu)
#endif

// Traditional Chinese Section

#define TOS_GROUP				_cat_(TCh_qun,TCh_zu)										//T:群組

//osd_err_str strings
#define TOS_PARENTAL_ERR        _cat4_(TCh_ji, Ch_bie, TCh_cuo, TCh_wu)                 // T:級別錯誤
#define TOS_REGION_ERR          _cat4_(TCh_qu, TCh_ma, TCh_cuo, TCh_wu)                 // T:區碼錯誤

//_OsdMessegeFont1 strings
//#define TOS_NULL                0x0
#define TOS_NULL                ""  //Jeff 20020708

#define TOS_NODISC              _cat_(TCh_wu2, Ch_die)                                  //T:無碟

//Change Chinese String for invalid_key, Jeff 20020510
//#define TOS_NO                  _cat6_(Ch_nin, Ch_an, TCh_cuo, Ch_nn, Ch_space, Ch_hand) //T:您按錯了  hand
//#define TOS_NO                  _cat_(TCh_wu2, TCh_xiao4)                              //T:無效
#ifdef FUSS_DVD
#define TOS_NO               _cat4_(Ch_vff, Ch_xiao4, Ch_space, Ch_hand)             //T:(無效  hand)
#elif defined(GBM_DVD)
#define TOS_NO               Ch_hand                                                 //T:hand
#else
#define TOS_NO                _cat6_(Ch_nin, Ch_an, TCh_cuo, Ch_nn, Ch_space, Ch_hand) //T:(您按錯了 hand)
#endif


// guolin video setup  3-10-30 
#define TOS_VIDEO_SETUP		_cat4_(TCh_shi3, TCh_pin, TCh_she, TCh_ding) 
#define TOS_BRIGHT_SETUP	_cat_(TCh_liang3,TCh_du3)                                //T:(亮度)
#define TOS_CONTRAST 		_cat_(TCh_dui, Ch_bi1)                                   //T:(對比)
#define TOS_HUE 		_cat_(TCh_se, TCh_diao)                                   //T:(色調)
#define TOS_SATURATION        	_cat3_(TCh_bao3,TCh_he3,TCh_du3)                         //T:(飽和度)

////////////---------clead end 

//clead prologicII
#define TOS_MOVIE_MODE		_cat4_(TCh_dian, Ch_ying1, Ch_mo, Ch_shi) 
#define TOS_MUSIC_MODE		_cat4_(Ch_yin, TCh_yue8, Ch_mo, Ch_shi) 
//cleed prologicII



#define TOS_ERR_DISC            _cat4_(TCh_cuo, TCh_wu, Ch_die, Ch_pian)                //T:錯誤碟片
#define TOS_TRACK               _cat_(Ch_qu, Ch_mu1)                                    //T:曲目

#ifdef FUSS_DVD_AVD276
#define TOS_OPEN                _cat_(Ch_qu3, Ch_chu)                			//T:退出片匣S:�○�
#define TOS_CLOSE               _cat_(Ch_zhi5, TCh_ru)              			//T:關閉S:离�諵蠽X
#else
#define TOS_OPEN                _cat4_(Ch_tui, Ch_chu, Ch_pian, TCh_xia)                //T:退出片匣
#define TOS_CLOSE               _cat4_(TCh_guan, TCh_bi, Ch_pian, TCh_xia)              //T:關閉片匣
#endif

#define TOS_PLAY                _cat_(Ch_bo, Ch_fang)                                   //T:播放
#define TOS_REGION_5            _cat_("5 ", TCh_qu)                                     //T:5 區
#define TOS_PAUSE               _cat_(TCh_zhan, Ch_ting)                                //T:暫停

#define TOS_RANDOM              _cat4_(TCh_sui, TCh_ji1, Ch_bo, Ch_fang)                //T:隨機播放
#define TOS_RESUME              _cat4_(Ch_hui, TCh_fu, Ch_bo, Ch_fang)                  //T:恢復播放
#define TOS_STOP                _cat_(Ch_ting, Ch_zhi)                                  //T:停止
#define TOS_STEP                _cat_(Ch_bu, TCh_jin)                                   //T:步進
#define TOS_SELECT              _cat_(TCh_xuan, TCh_ze)                                 //T:選擇
#define TOS_READ                _cat_(TCh_du, Ch_die)                                   //T:讀碟
#define TOS_REGION_6            _cat_("6 ", TCh_qu)                                     //T:6 區

#define TOS_FF                  _cat_(Ch_kuai, TCh_jin)                                 //T:快進
#define TOS_FB                  _cat_(Ch_kuai, Ch_tui)                                  //T:快退

#ifndef SUPPORT_PLAYBACK_ICON
#define TOS_NEXT                _cat5_(Ch_xia, Ch_e, Ch_qu, Ch_space, Ch_arrow)         //T:下一曲 >>
#define TOS_PREV                _cat5_(Ch_shang, Ch_e, Ch_qu, Ch_space, Ch_arr2)        //T:上一曲 <<
#else
#define TOS_NEXT                _cat4_(Ch_xia, Ch_e, Ch_qu, Ch_space)			        //T:下一曲 >>
#define TOS_PREV                _cat4_(Ch_shang, Ch_e, Ch_qu, Ch_space)					//T:上一曲 <<
#endif

#define TOS_RETURN              _cat4_(Ch_fan, Ch_hui1, TCh_xuan, TCh_dan)              //T:返回選單
#define TOS_MENU                _cat_(TCh_xuan, TCh_dan)                                //T:選單
#define TOS_BROWSE              _cat_(TCh_liu, TCh_lan)                                 //T:瀏覽
#define TOS_PROG                _cat_(TCh_bian, Ch_cheng)                               //T:編程
#define TOS_PROV_CHAPTER        _cat4_(Ch_shang, Ch_e, Ch_zhang, TCh_jie)
#define TOS_NEXT_CHAPTER        _cat4_(Ch_xia, Ch_e, Ch_zhang, TCh_jie)

#define TOS_REP                 _cat_(Ch_chong, TCh_fu1)                                //T:重覆
#define TOS_REP_DIR             _cat4_(Ch_mu1, TCh_lu, Ch_chong, TCh_fu1)               //T:目錄重覆
#define TOS_REP_1               _cat4_(TCh_dan, Ch_qu, Ch_chong, TCh_fu1)               //T:單曲重覆
#define TOS_REP_ALL             _cat4_(Ch_quan, Ch_die, Ch_chong, TCh_fu1)              //T:全碟重覆
#define TOS_REP_CNL             _cat4_(Ch_qu3, Ch_xiao, Ch_chong, TCh_fu1)              //T:取消重覆
#define TOS_GOTO                _cat4_(Ch_sou, Ch_suo, Ch_bo, Ch_fang)                  //T:搜索播放
#define TOS_MUTE                _cat_(Ch_jing, Ch_yin)                                  //T:靜音

#define TOS_CHL                 _cat3_(Ch_zuo, TCh_sheng, Ch_dao)                       //T:左聲道
#define TOS_CHR                 _cat3_(Ch_you1, TCh_sheng, Ch_dao)                      //T:右聲道
#define TOS_STEREO              _cat3_(Ch_li, TCh_ti, TCh_sheng)                        //T:立體聲
#define TOS_LIVE                _cat_(TCh_xian, TCh_chang)                              //T:現場
#define TOS_TIME                _cat_(TCh_shi, TCh_jian)                                //T:時間
#define TOS_ZOOM                _cat_(Ch_fang, TCh_kuan)                                //T:放寬

#define TOS_CANCEL              _cat_(Ch_qu3, Ch_xiao)                                  //T:取消
#define TOS_INTRO               _cat_(TCh_sao, Ch_miaou)                                //T:掃描
#define TOS_SURR                _cat_(TCh_huan, TCh_rao)                                //T:環繞
//#define TOS_PBC_OFF             _cat4_(TCh_shun, Ch_xu, Ch_bo, Ch_fang)                 //T:順序播放
#define TOS_REP_A               _cat4_(Ch_chong, TCh_fu1, "A", "-")                     //T:重覆A-
#define TOS_REP_AB              _cat5_(Ch_chong, TCh_fu1, "A", "-", "B")                //T:重覆A-B

#define TOS_PICUP               _cat4_(TCh_hua, Ch_mian, Ch_shang, Ch_yi)               //T:畫面上移
#define TOS_PICDN               _cat4_(TCh_hua, Ch_mian, Ch_xia, Ch_yi)                 //T:畫面下移

#define TOS_PICL                _cat4_(TCh_hua, Ch_mian, Ch_zuo, Ch_yi)                 //T:畫面左移
#define TOS_PICR                _cat4_(TCh_hua, Ch_mian, Ch_you1, Ch_yi)                //T:畫面右移
#define TOS_CHAPTER             _cat_(Ch_zhang, TCh_jie)                                //T:章節

#ifdef FUSS_TCHINESE_CUSTOMER//nono 2-8-26 16:27
#define TOS_ECHO                _cat_(TCh_hui, Ch_yin)                                  //T:回響 S:隙秞
#define TOS_KEY                 _cat3_(Ch_sheng2, TCh_jiang, TCh_diao)                  //T:音調 S:汔蔥覃
#define TOS_SIMULATE            _cat_(TCh_lei, Ch_bi1)                                  //T:模擬 S:濬掀
#define TOS_PRE_STOP            _cat7_(TCh_qing, Ch_an, Ch_bo, Ch_fang, TCh_jian1, TCh_ji4, TCh_xu)       //T:准停止 S:③偌畦溫瑩樟哿

#define TOS_VIDEO               _cat4_(TCh_shi3, TCh_pin, TCh_shu1, Ch_chu)             //T:視訊輸出S:弝け怀堤
#define TOS_YUV                 _cat_(TCh_se, TCh_cha)                      //T:視訊分量    S:伎船

#define TOS_NO_ADULT            _cat3_(Ch_xian, Ch_zhi1, TCh_ji)                        //T:非A級S:癹秶撰片
#define TOS_KID_ONLY            _cat3_(TCh_fu2, TCh_dao, TCh_ji)                        //T:兒童片
#define TOS_VIEW_ALL            _cat3_(TCh_pu, Ch_tong4, TCh_ji)                       //T:無限制
#else
//#define TOS_ECHO                _cat_(Ch_hui1, TCh_xiang)
#define TOS_ECHO                _cat_(TCh_hui, TCh_xiang)                               //T:回響
#define TOS_KEY                 _cat_(Ch_yin, TCh_diao)                                 //T:音調
#define TOS_SIMULATE            _cat_(Ch_mo, TCh_ni)                                    //T:模擬

#ifdef FUSS_DVD_AVD276
#define TOS_PRE_STOP            _cat_(TCh_yu3, Ch_ting)                        //T:准停止
#else
#define TOS_PRE_STOP            _cat3_(TCh_zhun, Ch_ting, Ch_zhi)                        //T:准停止
#endif

#define TOS_VIDEO               _cat4_(TCh_shi3, TCh_xun, TCh_shu1, Ch_chu)             //T:視訊輸出
#define TOS_YUV                 _cat4_(TCh_shi3, TCh_xun, Ch_fen, Ch_liang)             //T:視訊分量

#define TOS_NO_ADULT            _cat4_(Ch_fei, "A", TCh_ji, Ch_pian)                    //T:非A級片
#define TOS_KID_ONLY            _cat3_(TCh_er, Ch_tong, Ch_pian)                        //T:兒童片
#define TOS_VIEW_ALL            _cat3_(TCh_wu2, Ch_xian, Ch_zhi1)                       //T:無限制
#endif

#define TOS_TITLE               _cat_(TCh_biao, TCh_ti1)                                //T:標題
#define TOS_VOL                 _cat_(Ch_yin, Ch_liang)                                 //T:音量

#define TOS_9FRAME_1            _cat5_(TCh_dan, Ch_qu, Ch_jiu, TCh_hua, Ch_mian)        //T:單曲九畫面

#define TOS_AUTO_L              _cat5_(Ch_zi, TCh_dong, Ch_jie1, Ch_chang, Ch_zuo)      //T:自動接唱左
#define TOS_AUTO_R              _cat5_(Ch_zi, TCh_dong, Ch_jie1, Ch_chang, Ch_you1)     //T:自動接唱右
#define TOS_SEQUENCE            _cat4_(TCh_shun, Ch_xu, Ch_bo, Ch_fang)                                             //T:順序播放
#define TOS_MENUPLAY            _cat4_(TCh_xuan, TCh_dan, Ch_bo, Ch_fang)               //T:選單播放
#define TOS_PROG_PLAY           _cat4_(TCh_bian, Ch_cheng, Ch_bo, Ch_fang)              //T:編程播放
#define TOS_OSD                 _cat6_(TCh_hua, Ch_mian, TCh_xian1, Ch_shi2, TCh_yu, Ch_yan1) //T:畫面顯示語言

#define TOS_TV_RATIO            _cat6_(TCh_ying, Ch_mu, TCh_hua, Ch_mian, Ch_bi1, Ch_li1)//T:螢幕畫面比例
#define TOS_TV_SYS              _cat5_(TCh_dian, TCh_shi3, TCh_ji1, Ch_xi1, Ch_tong2)   //T:電視機系統
#define TOS_EXIT_MENU           _cat6_(Ch_tui, Ch_chu, TCh_she, TCh_ding, TCh_xuan, TCh_dan) //T:退出設定選單
#define TOS_AUD_OUT             _cat4_(TCh_shu, TCh_wei, TCh_shu1, Ch_chu)              //T:數位輸出

#define TOS_PASSWORD            _cat_(Ch_mi, TCh_ma)                                    //T:密碼

#ifdef FUSS_DVD_AVD276
#define TOS_RATING              _cat4_(TCh_nian, TCh_ling,Ch_xian,Ch_zhi1)                                   //T:級別
#else
#define TOS_RATING              _cat_(TCh_ji, Ch_bie)                                   //T:級別
#endif

#define TOS_BITSTREAM           _cat3_("SPDIF/", Ch_yuan2, TCh_ma)                      //T:SPDIF/源碼

//#define TOS_ANALOG_6CH          _cat3_("AC3 6", TCh_sheng, Ch_dao)                      //T:AC3 6聲道

#define TOS_ANALOG_2CH          _cat3_("AC3 2", TCh_sheng, Ch_dao)                      //T:AC3 2聲道

#define TOS_AUTO                _cat_(Ch_zi, TCh_dong)                                  //T:自動
#define TOS_OFF                 TCh_guan                                                //T:關
#define TOS_S_VIDEO             _cat3_("S ", Ch_duan, Ch_zi1)                           //T:S 端子
#define TOS_16_9                _cat_("16:9", Ch_169)                                   //T:16:9 --
#define TOS_4_3LB               _cat_("4:3LB", Ch_43)                                   //T:4:3LB --
#define TOS_4_3PS               _cat_("4:3PS", Ch_43ps)                                 //T:4:3PS--

#if defined(SHOW_5_1CH)
#define TOS_6CH_SETUP           _cat3_("5.1", TCh_sheng, Ch_dao)  //T:5.1汒耋
#else
#define TOS_6CH_SETUP           _cat5_("6", TCh_sheng, Ch_dao, TCh_she, TCh_ding)       //T:6聲道設定
#endif

#define TOS_SUBWOOFER           _cat4_(Ch_chao, Ch_chong, Ch_di, Ch_yin)                //T:超重低音
#define TOS_ON                  TCh_kai                                                 //T:開
#define TOS_DOBLY               Ch_dolby
#define TOS_CLEAR               _cat_(Ch_qing1, Ch_chu1)                                //T:清除
#define TOS_EDIT                _cat_(TCh_bian, TCh_ji2)                                //T:編輯
#define TOS_DIR1                Ch_dir1
#define TOS_DIR2                Ch_dir2
#define TOS_DIR3                Ch_dir3
#define TOS_DIR4                Ch_dir4

#define OS_DIR5                 Ch_dir5
#define TOS_LOCK                _cat6_("-","-","-","-", Ch_space, Ch_lock)              //T:---- L
#define TOS_UNLOCK              _cat6_("-","-","-","-", Ch_space, Ch_unlock)            //T:---- U
//#define TOS_TRK_S               _cat4_(TCh_dan, Ch_qu, Ch_sou, Ch_suo)                  //T:單曲搜索
//#define TOS_DISC_S              _cat4_(TCh_zong, Ch_die, Ch_sou, Ch_suo)                //T:總碟搜索

#define TOS_CH                  _cat_(TCh_sheng, Ch_dao)                                //T:聲道
//#define TOS_FIRMWARE_ID         _cat4_(TCh_ruan, TCh_ti, TCh_bian, TCh_ma)              //T:軟體編碼
//#define TOS_CHIP_ID             _cat4_(TCh_jing1, Ch_pian, TCh_bian, TCh_ma)            //T:晶片編碼
#define TOS_REGION_CODE         _cat_(TCh_qu, TCh_ma)                                   //T:區碼
//#define TOS_FUNCTION            _cat4_(TCh_fu1, TCh_du, TCh_fu1, Ch_chang)              //T:覆讀覆唱
//#define TOS_MODE                _cat_(Ch_mo, Ch_shi)                                    //T:模式
//#define TOS_RECORD              _cat_(TCh_fu1, Ch_chang)                                //T:覆唱
//#define TOS_STUDY               _cat_(TCh_fu1, TCh_du)                                  //T:覆讀

//#define TOS_FOLLOW              _cat_(Ch_gen, TCh_du)                                   //T:跟讀
//#define TOS_COMPARE             _cat_(TCh_dui, Ch_bi1)                                  //T:對比
//#define TOS_COUNTER             _cat4_(Ch_chong, TCh_fu1, Ch_ci1, TCh_shu)              //T:重覆次數
//#define TOS_LEVEL               _cat4_(TCh_lu, Ch_yin, Ch_mo, Ch_shi)                   //T:錄音模式
//#define TOS_HIGH                _cat3_(Ch_gao, Ch_pin1, TCh_zhi2)                       //T:高品質
//#define TOS_NORMAL              _cat4_(Ch_chao, TCh_chang1, TCh_shi, TCh_jian)          //T:超長時間
//#define TOS_SUPER               _cat4_(Ch_chao, Ch_gao, Ch_pin1, TCh_zhi2)              //T:超高品質
//#define TOS_OPERATING           _cat4_(TCh_diao, TCh_jie, Ch_fang1, Ch_shi)             //T:調節方式
//#define TOS_MANUAL              _cat_(Ch_shou, TCh_dong)                                //T:手動

#define TOS_CONCERT             _cat3_(Ch_yin, TCh_yue, TCh_ting)                       //T:音樂廳
#define TOS_CHURCH              _cat_(Ch_jiao1, Ch_tang)                                //T:教堂
#define TOS_PASSIVE             TOS_SURR
#define TOS_WIDE                _cat_(TCh_kuan, TCh_chang)                              //T:寬場
//#define TOS_AMPHITH             _cat3_(TCh_yuan1, TCh_ju, TCh_chang)                    //T:圓劇場
//#define TOS_STADIUM             _cat3_(TCh_ti, Ch_yu1, TCh_guan1)                       //T:體育館
#define TOS_EQ                  _cat_(Ch_jun, Ch_hen)                                   //T:均衡
#define TOS_STANDARD            _cat_(TCh_biao, TCh_zhun)                               //T:標準
#define TOS_CLASSIC             _cat_(Ch_gu, Ch_dian1)                                  //T:古典

#define TOS_ROCK                _cat_(Ch_yao, TCh_gun)                                  //T:搖滾
#define TOS_JAZZ                _cat_(Ch_jue, Ch_shil)                                  //T:爵土
#define TOS_POP                 _cat_(Ch_liul, Ch_xing1)                                //T:流行
#define TOS_USER                _cat_(TCh_ge, Ch_xing)                                  //T:個性
#define TOS_ATTRIB              TOS_USER

#ifdef FUSS_DVD_AVD276
#define TOS_SF                  _cat_(Ch_man, Ch_fang)
#else
#define TOS_SF                  _cat_(Ch_man, TCh_jin)                                  //T:慢進
#endif

#define TOS_SB                  _cat_(Ch_man, Ch_tui)                                   //T:慢退
#define TOS_CSPK                _cat5_(Ch_zhong, Ch_zhi5, TCh_yang, TCh_sheng, Ch_qi)   //T:中置揚聲器
#define TOS_SSPK                _cat5_(TCh_huan, TCh_rao, TCh_yang, TCh_sheng, Ch_qi)   //T:環繞揚聲器
#define TOS_CSPK_DELAY          _cat4_(Ch_zhong, Ch_zhi5, Ch_yan, TCh_chi)              //T:中置延遲

#define TOS_SSPK_DELAY          _cat4_(TCh_huan, TCh_rao, Ch_yan, TCh_chi)              //T:環繞延遲
#define TOS_FSPK                _cat5_(Ch_qian, Ch_zhi5, TCh_yang, TCh_sheng, Ch_qi)    //T:前置揚聲器
#define TOS_SYS_SETUP           _cat4_(Ch_xi1, Ch_tong2, TCh_she, TCh_ding)             //T:系統設定
#define TOS_SPK_SETUP           _cat5_(TCh_yang, TCh_sheng, Ch_qi, TCh_she, TCh_ding)   //T:揚聲器設定
#define TOS_AUD_SETUP           _cat4_(Ch_yin, TCh_pin, TCh_she, TCh_ding)              //T:音頻設定
#define TOS_DEFAULT_SETUP       _cat3_(TCh_yu3, TCh_she, Ch_zhi4)                       //T:預設值
#define TOS_SSAVER_SETUP        _cat4_(TCh_ying, Ch_mu, Ch_bao, TCh_hu)                 //T:螢幕保護
#define TOS_SSAVER_1            _cat3_(Ch_mo, Ch_shi, " 1")                             //T:模式 1
#define TOS_SSAVER_2            _cat3_(Ch_mo, Ch_shi, " 2")                             //T:模式 2
#define TOS_SSAVER_3            _cat3_(Ch_mo, Ch_shi, " 3")                             //T:模式 3

#define TOS_DIGITAL_SETUP       _cat6_(Ch_du1, Ch_bi1, TCh_shu, TCh_wei, TCh_she, TCh_ding)     //T:杜比數位設定
#define TOS_MIC_ONOFF           _cat5_(TCh_mai, TCh_ke, TCh_feng, TCh_she, TCh_ding)    //T:麥克風設定
#define TOS_MIC_VOL             _cat5_(TCh_mai, TCh_ke, TCh_feng, Ch_yin, Ch_liang)     //T:麥克風音量
#define TOS_CD_DEBUG            _cat3_(TCh_jiu1, TCh_cuo, Ch_zhong)                     //T:糾錯中
#define TOS_SMART_UPGRADE       _cat4_(Ch_zhi3, Ch_neng, Ch_sheng2, TCh_ji)             //T:智能升級
#define TOS_UPGRADE_TO          _cat3_(Ch_sheng2, TCh_ji, Ch_cheng1)                    //T:升級成
#define TOS_UPGRADING           _cat3_(Ch_sheng2, TCh_ji, Ch_zhong)                     //T:升級中
#define TOS_NOT_POWEROFF        _cat3_(Ch_wu1, TCh_guan, TCh_ji1)                       //T:勿關機
//nono del.

#define TOS_REGION_1            _cat_("1 ", TCh_qu)                                     //T:1 區
#define TOS_REGION_2            _cat_("2 ", TCh_qu)                                     //T:2 區
#define TOS_REGION_3            _cat_("3 ", TCh_qu)                                     //T:3 區
#define TOS_REGION_4            _cat_("4 ", TCh_qu)                                     //T:4 區
#define TOS_LANG_SETUP          _cat4_(TCh_yu, Ch_yan1, TCh_she, TCh_ding)              //T:語言設定
#define TOS_RETURN_MAIN_SETUP   _cat3_(Ch_hui1, Ch_zhu, TCh_ye)                         //T:回主頁
#define TOS_AUDIO_LANG_SETUP    _cat4_(Ch_yin, TCh_pin, TCh_yu, Ch_yan1)                //T:音頻語言
#define TOS_SUBTITLE_LANG_SETUP _cat4_(Ch_zi2, Ch_mu, TCh_yu, Ch_yan1)                  //T:字幕語言
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42
#define TOS_SUBTITLE_LANG_2ND_SETUP _cat5_(Ch_zi2, Ch_mu, TCh_yu, Ch_yan1, " 2")
#endif
#define TOS_MENU_LANG_SETUP     _cat4_(TCh_xuan, TCh_dan, TCh_yu, Ch_yan1)              //T:選單語言

#define TOS_DOWNMIX_SETUP       _cat4_(Ch_hun, Ch_he, Ch_mo, Ch_shi)                    //T:混合模式
#define TOS_RESTORE_SETUP       _cat_(TCh_fu, Ch_yuan)                                  //T:復原
#define TOS_VSURROUND_SETUP     _cat5_(Ch_xu1, TCh_ni, TCh_huan, TCh_rao, TCh_sheng)    //T:虛擬環繞聲
#define TOS_DOLBY_OP_SETUP      _cat4_(TCh_shu1, Ch_chu, Ch_mo, Ch_shi)                 //T:輸出模式
#define TOS_DOLBY_LINE_SETUP    _cat4_(TCh_xian2, Ch_lu1, TCh_shu1, Ch_chu)             //T:線路輸出
#define TOS_DOLBY_RF_SETUP      _cat3_("RF", TCh_diao, Ch_zheng)                        //T:RF 調整
#define TOS_DUAL_MONO_SETUP     _cat3_(Ch_zuo, "+", Ch_you1)                            //T:左+右

#define TOS_MIX_MONO_SETUP      _cat4_(Ch_hun, Ch_he, TCh_sheng, Ch_dao)                //T:混合聲道
#define TOS_SURROUND_MODE       _cat4_(TCh_huan, TCh_rao, Ch_mo, Ch_shi2)               //T:環繞模式
#define TOS_BASS_MANAGEMENT		_cat4_(Ch_di, Ch_yin, Ch_mo, Ch_shi)					//T:低音模式

#define TOS_BASS_MODE_1			_cat4_(Ch_da1, TCh_yang, TCh_sheng, Ch_qi)              //T:(大揚聲器)
#define TOS_BASS_MODE_2			_cat4_(Ch_xiao2, TCh_yang, TCh_sheng, Ch_qi)            //T:(小揚聲器)
#define TOS_BASS_MODE_3			_cat5_(Ch_hun, Ch_he, TCh_yang, TCh_sheng, Ch_qi)       //T:(混合揚聲器)


#define TOS_SCORE               _cat_(Ch_fen, TCh_shu)                                  //T:分數
#define TOS_MARK                _cat_(TCh_ji3, TCh_yi2)                                 //T:記憶

//language string
//#define TOS_JAPAN               _cat_(Ch_ri, TCh_yu)                                    //T:日語
//#define TOS_FRENCH              _cat_(Ch_fa1, TCh_yu)                                   //T:法語
//#define TOS_GERMAM              _cat_(Ch_de, TCh_yu)                                    //T:德語


//#define TOS_LATIN               _cat3_(Ch_la, Ch_ding1, TCh_yu)                         //T:拉丁語

#define TOS_CHINESE             _cat_(Ch_zhong, Ch_wen)                                  //T:漢語
#define TOS_ENGLISH             _cat_(Ch_ying, Ch_wen)
#define TOS_JAPAN               _cat_(Ch_ri, Ch_wen)
#define TOS_FRENCH              _cat_(Ch_fa1, Ch_wen)                                   //T:法語
#define TOS_GERMAM              _cat_(Ch_de, Ch_wen)                                    //T:德語
#define TOS_SPANISH             _cat3_(Ch_xi, Ch_ban1, Ch_ya)                           //T:西班牙
#define TOS_PORTUGUESE          _cat3_(Ch_pu, Ch_tao, Ch_ya)                            //T:葡萄牙
#define TOS_LATIN               _cat3_(Ch_la, Ch_ding1, Ch_wen)                         //T:拉丁語

#define TOS_DYNAMICRANGE         _cat4_(TCh_dong, TCh_tai, TCh_fan, TCh_wei1)           //T:動態範圍

#define TOS_SFE_OUT              _cat6_(Ch_chao, Ch_chong, Ch_di, Ch_yin, TCh_shu1, Ch_chu)//T:超重低音輸出
#define TOS_SFE_STD              _cat4_(TCh_biao, TCh_zhun, Ch_mo, Ch_shi)                 //T:標准模式


// Japanese Section
#ifdef USE_JAPANESE_OSD

//#define JOS_GROUP				_cat_(TCh_qun,TCh_zu)										//T:群組

//osd_err_str strings

#ifdef HUAJIA_DVD
#define JOS_PARENTAL_ERR        _cat6_(JCh_an, JCh_zheng, JCh_fan, JCh_hao,JCh_sru,JCh_li2)                 // T:級別錯誤
#else
#define JOS_PARENTAL_ERR        _cat6_(JCh_an, JCh_zheng, JCh_fan, JCh_hao,JCh_yi,JCh_chang)                 // T:級別錯誤
#endif
#define JOS_REGION_ERR          _cat8_(JCh_ri, JCh_changyin, JCh_si, JCh_zhuoyin, JCh_xyo, JCh_n, JCh_yi, JCh_chang)               // T:區碼錯誤

//_OsdMessegeFont1 strings
//#define TOS_NULL                0x0
#define JOS_NULL                ""  //Jeff 20020708

#ifdef HUAJIA_DVD
#define JOS_NODISC              _cat7_(JCh_te, JCh_zhuoyin, JCh_xi, JCh_su,JCh_ku, JCh_pna, JCh_psi)                                  //T:無碟
#else
#define JOS_NODISC              _cat7_(JCh_no, JCh_changyin, JCh_te, JCh_zhuoyin,JCh_i, JCh_si, JCh_ku)                                  //T:無碟
#endif

#define JOS_NO					_cat4_(JCh_sru, JCh_li2, JCh_wu,JCh_xiao)              //T:關閉片匣
#define JOS_ERR_DISC            _cat8_(JCh_te, JCh_zhuoyin,JCh_xi,JCh_su,JCh_ku, JCh_e, JCh_ra, JCh_changyin)                //T:錯誤碟片

#define JOS_OPEN                _cat4_(JCh_to, JCh_re, JCh_i,JCh_kai)                //T:退出片匣
#define JOS_CLOSE               _cat4_(JCh_to, JCh_re, JCh_i,JCh_bi)              //T:關閉片匣

#define JOS_PLAY                _cat_(JCh_zai, JCh_sheng1)                                   //T:播放
#define JOS_REGION_5            _cat7_(JCh_ri,JCh_changyin,JCh_si,JCh_zhuoyin,JCh_xyo,JCh_n," 5")                                     //T:5 區
//#define JOS_PAUSE               _cat_(Ch_jing, Ch_zhi)                                //T:暫停
#define JOS_PAUSE               _cat7_(Ch_jing, Ch_zhi,"/",Ch_e,JCh_shi,Ch_ting, Ch_zhi)                                //T:暫停
#define JOS_RESUME				_cat_(JCh_li, JCh_psi)

//#define JOS_STOP                _cat5_(JCh_su, JCh_to,JCh_cuyin, JCh_hu,JCh_banzhuoyin)                                  //T:停止
#define JOS_STEP                _cat5_(JCh_su, JCh_te,JCh_cuyin,JCh_hu,JCh_banzhuoyin)                                   //T:步進
#define JOS_SELECT              _cat_(TCh_xuan, JCh_ze)                                 //T:選擇
#define JOS_READ                _cat_(JCh_tke, JCh_tru) //T:讀碟
#define JOS_REGION_6            _cat7_(JCh_ri,JCh_changyin,JCh_si,JCh_zhuoyin,JCh_xyo,JCh_n," 6")                                     //T:6 區

#define JOS_SIMULATE            _cat5_(JCh_a, JCh_na,JCh_ro,JCh_ku,JCh_zhuoyin)                                 //T:快進

#define JOS_FF                  _cat3_(JCh_zao, JCh_song,JCh_pri)                                 //T:快進

#define JOS_FB                  _cat3_(JCh_zao, JCh_li,JCh_psi)                                 //T:快退

#ifndef SUPPORT_PLAYBACK_ICON
#define JOS_NEXT                _cat4_(JCh_hci, JCh_he, Ch_space, Ch_arrow)       //T:下一曲 >>
#define JOS_PREV                _cat4_(JCh_li, JCh_pru, Ch_space, Ch_arr2)        //T:上一曲 <<
#else
#define JOS_NEXT                _cat3_(JCh_hci, JCh_he, Ch_space)		         //T:下一曲 >>
#define JOS_PREV                _cat3_(JCh_li, JCh_pru, Ch_space)				 //T:上一曲 <<
#endif
#define JOS_RETURN				_cat4_(JCh_ri, JCh_ta,JCh_changyin,JCh_n)
#define JOS_NONE	            _cat_(JCh_o, JCh_hu)                                 //T:瀏覽
#define JOS_MENU                _cat4_(JCh_me, JCh_ni,JCh_xyu,JCh_changyin)                                //T:選單
#define JOS_BROWSE				_cat6_(JCh_hu, JCh_zhuoyin,JCh_ra,JCh_u,JCh_su,JCh_zhuoyin)
#define JOS_SCORE	            _cat_(JCh_dian, JCh_shu)                                 //T:瀏覽
#define JOS_MARK	            _cat3_(JCh_ma, JCh_changyin,JCh_ku)                                 //T:瀏覽

#define JOS_PROG                _cat6_(JCh_pu, JCh_ro,JCh_gu,JCh_ra,JCh_mu,JCh_space24)
#define JOS_SLOW                _cat3_(JCh_si, JCh_ro,JCh_changyin)                                //T:重覆
#define JOS_REP                 _cat5_(JCh_ri, JCh_hi,JCh_banzhuoyin,JCh_changyin,JCh_to)                                //T:重覆
#define JOS_REP_DIR             _cat6_(Ch_mu1,JCh_hci, JCh_hi,JCh_banzhuoyin,JCh_changyin,JCh_to)               //T:目錄重覆
#define JOS_REP_1               _cat6_(JCh_ri, JCh_hi,JCh_banzhuoyin,JCh_changyin,JCh_to,"[1]")               //T:單曲重覆
#define JOS_REP_ALL             _cat6_(JCh_ri, JCh_hi,JCh_banzhuoyin,JCh_changyin,JCh_to,"[ALL]")//,JCh_o,JCh_changyin,JCh_ru)              //T:全碟重覆
#define JOS_REP_CNL             _cat11_(JCh_ri, JCh_hi,JCh_banzhuoyin,JCh_changyin,JCh_to," ",JCh_ki, JCh_ya, JCh_n, JCh_se,JCh_ru)              //T:取消重覆

#define JOS_MUTE                _cat_(Ch_xiao, Ch_yin)                                  //T:靜音
#define JOS_CHL					_cat5_(Ch_zuo, JCh_tce,JCh_mo,JCh_no,Ch_yin)
#define JOS_CHR					_cat5_(Ch_you1, JCh_tce,JCh_mo,JCh_no,Ch_yin)
#define JOS_STEREO              _cat4_(JCh_su, JCh_te, JCh_re,JCh_o)                        //T:立體聲
//#define JOS_LIVE                _cat4_(JCh_ra, JCh_i,JCh_hu,JCh_zhuoyin)                              //T:現場
#define JOS_LIVE                _cat5_(JCh_ra, JCh_i,JCh_hu,JCh_zhuoyin,JCh_space)                              //T:現場
//#define JOS_TIME                _cat3_(JCh_ta, JCh_i,JCh_mu)                                //T:時間
#define JOS_ZOOM				_cat4_(JCh_su, JCh_zhuoyin, JCh_changyin,JCh_mu)
#define JOS_CANCEL              _cat5_(JCh_ki, JCh_xya,JCh_n,JCh_se,JCh_ru)                                //T:環繞
#define JOS_INTRO				_cat4_(JCh_i, JCh_n, JCh_to,JCh_ro)
//#define JOS_SURR                _cat6_(JCh_sa, JCh_ra,JCh_u,JCh_n,JCh_to,JCh_zhuoyin)                                //T:環繞

//#define JOS_SURR                _cat6_(JCh_sa, JCh_ra,JCh_u,JCh_n,JCh_to,JCh_zhuoyin)                                //T:環繞
#define JOS_SURR                _cat7_(JCh_sa, JCh_ra,JCh_u,JCh_n,JCh_to,JCh_zhuoyin,JCh_space24)//JCh_changyin)                                //T:環繞

//#define JOS_PBC_OFF             _cat5_("SEQ ", JCh_hu,JCh_banzhuoyin, JCh_re,JCh_changyin)                 //T:順序播放
//#define JOS_PBC_OFF             _cat3_("SEQ ", JCh_zai, JCh_sheng1)                 //T:順序播放
#define JOS_POWER_ON            _cat4_(TCh_dian, Ch_yuan2, JCh_o,JCh_n)                 //T:順序播放

#define JOS_PROG_CANCEL			_cat12_(JCh_hu, JCh_banzhuoyin,JCh_ro,JCh_ku,JCh_zhuoyin,JCh_ra,JCh_mu,JCh_ki, JCh_xya,JCh_n,JCh_se,JCh_ru)

#define JOS_CHAPTER             _cat6_(JCh_ci, JCh_xya,JCh_hu,JCh_banzhuoyin,JCh_ta,JCh_changyin)                                //T:章節
#define JOS_PICUP				_cat7_(JCh_su, JCh_zhuoyin, JCh_changyin,JCh_mu,"[",Ch_shang,"]")
#define JOS_PICDN				_cat7_(JCh_su, JCh_zhuoyin, JCh_changyin,JCh_mu,"[",Ch_xia,"]")
#define JOS_PICL				_cat7_(JCh_su, JCh_zhuoyin, JCh_changyin,JCh_mu,"[",Ch_zuo,"]")
#define JOS_PICR				_cat7_(JCh_su, JCh_zhuoyin, JCh_changyin,JCh_mu,"[",Ch_you1,"]")
#define JOS_ECHO                _cat3_(JCh_e, JCh_ko, JCh_changyin)                               //T:回響

#define JOS_KEY                 _cat_(JCh_ki, JCh_changyin)                                 //T:音調


#define JOS_9FRAME_1			_cat7_("9",JCh_hu,JCh_re,JCh_changyin,JCh_mu, " ", "1")
#define JOS_AUTO_L				_cat5_(JCh_o, JCh_changyin, JCh_to, " ",Ch_zuo)
#define JOS_AUTO_R				_cat5_(JCh_o, JCh_changyin, JCh_to, " ",Ch_you1)

#define JOS_TITLE               _cat4_(JCh_ta, JCh_i,JCh_to,JCh_ru)                                //T:標題
//#define JOS_VOL                 _cat6_(JCh_ho,JCh_zhuoyin,JCh_ri,JCh_yu,JCh_changyin,JCh_mu)                                 //T:音量
#define JOS_VOL                 _cat_(Ch_yin,Ch_liang)                                 //T:音量

#define JOS_SEQUENCE            _cat3_("SEQ ", JCh_zai, JCh_sheng1)                                             //T:順序播放

//#define JOS_MENUPLAY            _cat9_(JCh_me, JCh_ni, JCh_xyu, JCh_changyin," ",JCh_hu,JCh_banzhuoyin,JCh_re,JCh_changyin)               //T:選單播放
#define JOS_MENUPLAY            _cat6_(JCh_me, JCh_ni, JCh_xyu, JCh_changyin,JCh_zai,JCh_sheng1)               //T:選單播放

//#define JOS_PROG_PLAY           _cat5_("PRG ", JCh_hu,JCh_banzhuoyin,JCh_re,JCh_changyin)              //T:編程播放
#define JOS_PROG_PLAY           _cat9_(JCh_hu, JCh_banzhuoyin,JCh_ro,JCh_ku,JCh_zhuoyin,JCh_ra,JCh_mu,JCh_zai,JCh_sheng1)              //T:編程播放
#define JOS_DYNAMICRANGE        _cat5_("DYNAMIC ", JCh_re, JCh_n, JCh_si,JCh_zhuoyin)           //T:動態範圍
#define JOS_OSD                 _cat6_(JCh_hua, Ch_mian, JCh_biao, Ch_shi2, Ch_yan1,TCh_yu) //T:畫面顯示語言

#define JOS_TV_RATIO            _cat8_(JCh_te, JCh_re, JCh_hi, JCh_zhuoyin, JCh_ta, JCh_i,JCh_hu,JCh_banzhuoyin)//T:螢幕畫面比例
#define JOS_TV_SYS              _cat8_(JCh_te, JCh_re, JCh_hi, JCh_zhuoyin,JCh_si, JCh_su, JCh_te, JCh_mu)   //T:電視機系統

#define JOS_AUD_OUT             _cat8_(JCh_o, JCh_changyin, JCh_te,JCh_zhuoyin,JCh_xi,JCh_o, Ch_chu,JCh_li2)              //T:數位輸出

#define JOS_PASSWORD            _cat4_(JCh_an, JCh_zheng,JCh_fan,JCh_hao)                                    //T:密碼

#define JOS_AUTO                 _cat3_(JCh_o,JCh_changyin,JCh_to)

#define JOS_OFF                 _cat_(JCh_o, JCh_hu)                                                //T:關

#define JOS_NO_ADULT			_cat3_(JCh_cheng, JCh_ren,Ch_yong)
#define JOS_KID_ONLY			_cat9_(JCh_ci, JCh_xya,JCh_i,JCh_ru,JCh_to,JCh_zhuoyin,JCh_ro,JCh_cuyin,JCh_ku)
#define JOS_VIEW_ALL			_cat4_(Ch_zhi1,Ch_xian,JCh_pna, JCh_psi)

#define JOS_SUBWOOFER           _cat8_(JCh_sa, JCh_hu, JCh_zhuoyin, JCh_u,JCh_changyin,JCh_hu,JCh_xa,JCh_changyin)                //T:超重低音
#define JOS_ON                  _cat_(JCh_o, JCh_n)

#define JOS_CLEAR               _cat4_(JCh_ku, JCh_ri,JCh_a,JCh_space)                                //T:清除

#define JOS_TRK_S               _cat7_(JCh_to, JCh_ra, JCh_cuyin, JCh_ku,JCh_sa,JCh_changyin,JCh_ci)                  //T:單曲搜索
#define JOS_DISC_S              _cat8_(JCh_te, JCh_zhuoyin,JCh_xi, JCh_su, JCh_ku,JCh_sa,JCh_changyin,JCh_ci)                //T:總碟搜索

#define JOS_CH                  _cat5_(JCh_ci, JCh_xya,JCh_n,JCh_ne,JCh_ru)                                //T:聲道

#define JOS_CHIP_ID             _cat5_(JCh_ci, JCh_cuyin, JCh_hu,JCh_banzhuoyin,"ID")            //T:晶片編碼
#define JOS_REGION_CODE         _cat6_(JCh_ri, JCh_changyin,JCh_si,JCh_zhuoyin,JCh_xyo,JCh_n)                                   //T:區碼

#if 1//defined(GBM_NEW_JAPANESE)
#define JOS_NEXTPAGE			_cat5_(JCh_pso, JCh_pno,Ch_ta,TCh_she,TCh_ding)  
#define JOS_BRIGHT_SETUP		_cat7_(JCh_hu, JCh_zhuoyin, JCh_ra, JCh_i,JCh_to,JCh_ne,JCh_su)
#define JOS_CONTRAST			_cat6_(JCh_ko, JCh_n,JCh_to,JCh_ra,JCh_su,JCh_to)
#define JOS_HUE					_cat3_(Ch_se, Ch_he,JCh_pi)
#define JOS_SATURATION			_cat4_(Ch_se, JCh_pno,Ch_nong,JCh_psa)
#endif
//#define JOS_FUNCTION            _cat7_(JCh_hi, JCh_xa, JCh_n, JCh_ku,JCh_si,JCh_yo,JCh_n)              //T:覆讀覆唱
//#define JOS_MODE                _cat4_(JCh_mo, JCh_changyin,JCh_to,JCh_zhuoyin)                                    //T:模式
//#define JOS_RECORD              _cat5_(JCh_re, JCh_ko,JCh_changyin,JCh_to,JCh_zhuoyin)                                //T:覆唱

//#define JOS_FOLLOW              _cat4_(JCh_hu, JCh_xo,JCh_ro,JCh_changyin)                                   //T:跟讀

//#define JOS_COUNTER             _cat5_(JCh_ka, JCh_u, JCh_n, JCh_ta,JCh_changyin)              //T:重覆次數
//#define JOS_LEVEL               _cat4_(JCh_re, JCh_he, JCh_zhuoyin, JCh_ru)                   //T:錄音模式
//#define JOS_HIGH                _cat_(JCh_ha, JCh_i)                       //T:高品質

//#define JOS_MANUAL              _cat5_(JCh_ma, JCh_ni,JCh_yu,JCh_a,JCh_ru)                                //T:手動

#define JOS_EDIT				_cat_(JCh_bian, JCh_ji)

//#define JOS_CONCERT             _cat5_(JCh_ko, JCh_n, JCh_sa,JCh_changyin,JCh_to)                       //T:音樂廳
#define JOS_CONCERT             _cat6_(JCh_ko, JCh_n, JCh_sa,JCh_changyin,JCh_to,JCh_space)                       //T:音樂廳

//#define JOS_CHURCH              _cat4_(JCh_ci, JCh_ya,JCh_changyin,JCh_ci)                                //T:教堂
#define JOS_CHURCH              _cat_(Ch_jiao1, JCh_hui)                                //T:教堂
#define JOS_PASSIVE				_cat_("PASS","IVE")
#define JOS_WIDE                _cat_("WI","DE")                              //T:寬場
//#define JOS_AMPHITH             _cat_("AMP","HITH")                    //T:圓劇場
//#define JOS_STADIUM             _cat6_(JCh_su, JCh_ta, JCh_si,JCh_zhuoyin,JCh_a,JCh_mu)                       //T:體育館
//#define JOS_EQ                  _cat5_(JCh_ha,JCh_zhuoyin,JCh_ra,JCh_n, JCh_su)                                   //T:均衡
#define JOS_EQ                  _cat7_(JCh_e,JCh_ko,JCh_ra,JCh_i, JCh_sa,JCh_zhuoyin,JCh_changyin)                                   //T:均衡

//#define JOS_STANDARD            _cat6_(JCh_su, JCh_te,JCh_n,JCh_ta,JCh_zhuoyin,JCh_changyin)                               //T:標準
#define JOS_STANDARD            _cat8_(JCh_su, JCh_ta,JCh_n,JCh_ta,JCh_zhuoyin,JCh_changyin,JCh_to,JCh_zhuoyin)                               //T:標準
//#define JOS_CLASSIC             _cat5_(JCh_ku, JCh_ra,JCh_cuyin,JCh_si,JCh_ku)                                  //T:古典
#define JOS_CLASSIC             _cat7_(JCh_ku, JCh_ra,JCh_si,JCh_cuyin,JCh_ku,JCh_space," ")                                  //T:古典

//#define JOS_ROCK                _cat3_(JCh_ro, JCh_cuyin,JCh_ku)                                  //T:搖滾
#define JOS_ROCK                _cat5_(JCh_ro, JCh_cuyin,JCh_ku,JCh_space," ")                                  //T:搖滾
//#define JOS_JAZZ                _cat5_(JCh_si,JCh_zhuoyin,JCh_ya,JCh_su, JCh_zhuoyin)                                  //T:爵土
#define JOS_JAZZ                _cat7_(JCh_si,JCh_zhuoyin,JCh_xya,JCh_su, JCh_zhuoyin,JCh_space," ")                                  //T:爵土
//#define JOS_POP                 _cat5_(JCh_ho,JCh_banzhuoyin,JCh_cuyin,JCh_hu, JCh_banzhuoyin)                                //T:流行
#define JOS_POP                 _cat6_(JCh_ho,JCh_banzhuoyin,JCh_cuyin,JCh_hu, JCh_banzhuoyin,JCh_space)                                //T:流行
#define JOS_USER                _cat5_(JCh_yu, JCh_changyin,JCh_sa,JCh_zhuoyin,JCh_changyin)                                  //T:個性

#define JOS_SF                  _cat5_(JCh_su, JCh_ro,JCh_changyin,JCh_song,JCh_pri)                                  //T:慢進

#define JOS_SB                  _cat5_(JCh_su, JCh_ro,JCh_changyin,JCh_li,JCh_psi)                                   //T:慢退
#define JOS_CSPK                _cat4_(JCh_se, JCh_n, JCh_ta, JCh_changyin)				//T:中置揚聲器
#define JOS_SSPK                _cat_(JCh_ri, JCh_a)   //T:環繞揚聲器
//#define JOS_CSPK_DELAY          _cat6_(JCh_se, JCh_n, JCh_ta, JCh_changyin,TCh_chi, Ch_yan)              //T:中置延遲
#define JOS_CSPK_DELAY          _cat9_(JCh_se, JCh_n, JCh_ta, JCh_changyin,JCh_te,JCh_zhuoyin,JCh_xi,JCh_re, JCh_i)              //T:中置延遲

#define JOS_SSPK_DELAY          _cat7_(JCh_ri, JCh_a,JCh_te,JCh_zhuoyin,JCh_xi,JCh_re, JCh_i)              //T:環繞延遲
#define JOS_FSPK                _cat4_(JCh_hu, JCh_ro, JCh_n, JCh_to)    //T:前置揚聲器

#ifdef GBM_NEW_JAPANESE
#define JOS_SYS_SETUP           _cat6_(JCh_si, JCh_su, JCh_te, JCh_mu,TCh_she,TCh_ding)             //T:系統設定
#define JOS_SPK_SETUP           _cat8_(JCh_su, JCh_hi, JCh_banzhuoyin, JCh_changyin,JCh_ka,JCh_changyin, TCh_she, TCh_ding)   //T:揚聲器設定
#define JOS_AUD_SETUP           _cat8_(JCh_o, JCh_changyin, JCh_te,JCh_zhuoyin,JCh_xi,JCh_o, TCh_she, TCh_ding)              //T:音頻設定
#define JOS_DEFAULT_SETUP       _cat3_(Ch_chu2, Ch_qi1, Ch_hua2)                       //T:預設值
#define JOS_DIGITAL_SETUP       _cat8_(JCh_te, JCh_zhuoyin, JCh_si, JCh_zhuoyin,JCh_ta,JCh_ru, TCh_she, TCh_ding)     //T:杜比數位設定
#define JOS_RESTORE_SETUP       _cat_(Ch_shi6,Ch_xing1)                                  //T:復原
#define JOS_RATING				_cat4_(Ch_shi5,Ch_ting2,Ch_zhi1,Ch_xian)
#define JOS_EXIT_MENU           _cat7_(JCh_si, JCh_su,JCh_te,JCh_mu,TCh_she, TCh_ding,JCh_he) //T:退出設定選單
#define JOS_VIDEO				_cat4_(JCh_hua, Ch_zhi6,TCh_she,TCh_ding)
#else//GBM_NEW_JAPANESE
#define JOS_SYS_SETUP           _cat11_(JCh_si, JCh_su, JCh_te, JCh_mu,JCh_se,JCh_cuyin,JCh_to,JCh_a,JCh_cuyin,JCh_hu,JCh_banzhuoyin)             //T:系統設定
#define JOS_SPK_SETUP           _cat13_(JCh_su, JCh_hi, JCh_banzhuoyin, JCh_changyin,JCh_ka,JCh_changyin, JCh_se,JCh_cuyin,JCh_to,JCh_a,JCh_cuyin,JCh_hu,JCh_banzhuoyin)   //T:揚聲器設定
#define JOS_AUD_SETUP           _cat13_(JCh_o, JCh_changyin, JCh_te, JCh_zhuoyin,JCh_xi,JCh_o, JCh_se,JCh_cuyin,JCh_to,JCh_a,JCh_cuyin,JCh_hu,JCh_banzhuoyin)
#define JOS_DEFAULT_SETUP       _cat6_(JCh_te, JCh_zhuoyin,JCh_hu,JCh_xo, JCh_ru,JCh_to)                       //T:預設值
#define JOS_DIGITAL_SETUP       _cat13_(JCh_te, JCh_zhuoyin, JCh_si, JCh_zhuoyin,JCh_ta,JCh_ru, JCh_se,JCh_cuyin,JCh_to,JCh_a,JCh_cuyin,JCh_hu,JCh_banzhuoyin)   //T:揚聲器設定
#define JOS_RESTORE_SETUP       _cat_(TCh_fu,JCh_syuan)                                  //T:復原
#define JOS_RATING				_cat7_(JCh_re, JCh_changyin, JCh_te, JCh_xi,JCh_n,JCh_ku,JCh_zhuoyin)
#define JOS_EXIT_MENU           _cat9_(JCh_se, JCh_cuyin, JCh_to,JCh_a,JCh_cuyin,JCh_hu,JCh_banzhuoyin,JCh_zhong, JCh_le) //T:退出設定選單
//#define JOS_VIDEO               _cat7_(JCh_hi,JCh_zhuoyin,JCh_te,JCh_zhuoyin,JCh_o, Ch_chu, JCh_li2)             //T:視訊輸出
#define JOS_VIDEO               _cat4_(JCh_sying,JCh_xiang,Ch_chu,JCh_li2)             //T:視訊輸出

#endif//GBM_NEW_JAPANESE

//#define JOS_SSAVER_SETUP        _cat10_(JCh_su, JCh_ku, JCh_ri, JCh_changyin,JCh_n,JCh_se,JCh_changyin,JCh_ha,JCh_zhuoyin,JCh_changyin)                 //T:螢幕保護
#define JOS_SSAVER_SETUP        _cat9_(JCh_su, JCh_ku, JCh_ri, JCh_changyin,JCh_n,JCh_se,JCh_changyin,JCh_ba,JCh_changyin)                 //T:螢幕保護
#define JOS_SSAVER_1            _cat5_(JCh_ta, JCh_i,JCh_hu,JCh_banzhuoyin, " 1")                             //T:模式 1
#define JOS_SSAVER_2            _cat5_(JCh_ta, JCh_i,JCh_hu,JCh_banzhuoyin, " 2")                             //T:模式 2
#define JOS_SSAVER_3            _cat5_(JCh_ta, JCh_i,JCh_hu,JCh_banzhuoyin, " 3")                             //T:模式 3

#define JOS_MIC_ONOFF           _cat10_(JCh_ma, JCh_i, JCh_ku, JCh_se,JCh_cuyin,JCh_to,JCh_a,JCh_cuyin,JCh_hu,JCh_banzhuoyin)    //T:麥克風設定
#define JOS_MIC_VOL             _cat5_(JCh_ma, JCh_i, JCh_ku, Ch_yin, Ch_liang)     //T:麥克風音量

#define JOS_SMART_UPGRADE       _cat13_(JCh_su, JCh_mo, JCh_changyin, JCh_to,JCh_a,JCh_cuyin,JCh_hu,JCh_banzhuoyin,JCh_ku,JCh_zhuoyin,JCh_re,JCh_changyin,JCh_to)             //T:智能升級
#define JOS_UPGRADE_TO          _cat11_(JCh_a,JCh_cuyin,JCh_hu,JCh_banzhuoyin,JCh_ku,JCh_zhuoyin,JCh_re,JCh_changyin,JCh_to,JCh_zhong, JCh_le)                    //T:升級成
#define JOS_UPGRADING           _cat14_(JCh_a,JCh_cuyin,JCh_hu,JCh_banzhuoyin,JCh_ku,JCh_zhuoyin,JCh_re,JCh_changyin,JCh_te, JCh_xi,JCh_n,JCh_ku,JCh_zhuoyin, Ch_zhong)                     //T:升級中
#define JOS_NOT_POWEROFF        _cat14_(TCh_dian, Ch_yuan2, JCh_po,JCh_qie,JCh_pra,JCh_pna,JCh_pi,JCh_pte,JCh_zhuoyin,JCh_pku,JCh_pta,JCh_zhuoyin,JCh_psa,JCh_pi)                       //T:勿關機
//Nono del it.

#define JOS_REGION_1            _cat7_(JCh_ri,JCh_changyin,JCh_si,JCh_zhuoyin,JCh_xyo,JCh_n," 1")                                    //T:1 區
#define JOS_REGION_2            _cat7_(JCh_ri,JCh_changyin,JCh_si,JCh_zhuoyin,JCh_xyo,JCh_n," 2")                                    //T:2 區
#define JOS_REGION_3            _cat7_(JCh_ri,JCh_changyin,JCh_si,JCh_zhuoyin,JCh_xyo,JCh_n," 3")                                     //T:3 區
#define JOS_REGION_4            _cat7_(JCh_ri,JCh_changyin,JCh_si,JCh_zhuoyin,JCh_xyo,JCh_n," 4")                                    //T:4 區
#define JOS_LANG_SETUP          _cat4_(Ch_yan1,TCh_yu , TCh_she, TCh_ding)              //T:語言設定
#define JOS_RETURN_MAIN_SETUP   _cat8_(JCh_me, JCh_i, JCh_n,JCh_he,JCh_banzhuoyin,JCh_changyin,JCh_si,JCh_zhuoyin)                         //T:回主頁
#define JOS_AUDIO_LANG_SETUP    _cat8_(JCh_o, JCh_changyin, JCh_te, JCh_zhuoyin,JCh_xi,JCh_o,Ch_yan1,TCh_yu)                //T:音頻語言
//#define JOS_SUBTITLE_LANG_SETUP _cat6_(Ch_zi2, Ch_mu, JCh_biao,Ch_shi2,Ch_yan1,TCh_yu)                  //T:字幕語言
#define JOS_SUBTITLE_LANG_SETUP _cat4_(Ch_zi2, Ch_mu, Ch_yan1,TCh_yu)                  //T:字幕語言
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42
#define JOS_SUBTITLE_LANG_2ND_SETUP _cat5_(Ch_zi2, Ch_mu, Ch_yan1, TCh_yu, " 2")
#endif
#define JOS_MENU_LANG_SETUP     _cat6_(JCh_me, JCh_ni,JCh_xyu,JCh_changyin, Ch_yan1,TCh_yu)              //T:選單語言
#define JOS_DOWNMIX_SETUP		_cat8_(JCh_ta, JCh_zhuoyin, JCh_u, JCh_n, JCh_mi,JCh_cuyin,JCh_ku,JCh_su)

#define JOS_DOLBY_OP_SETUP      _cat6_(Ch_chu, JCh_li2, JCh_mo, JCh_changyin,JCh_to,JCh_zhuoyin)                 //T:輸出模式
#define JOS_DOLBY_LINE_SETUP    _cat5_(JCh_ra, JCh_i, JCh_n, Ch_chu,JCh_li2)             //T:線路輸出

#define JOS_SURROUND_MODE       _cat10_(JCh_sa, JCh_ra, JCh_u, JCh_n,JCh_to,JCh_zhuoyin,JCh_mo,JCh_changyin,JCh_to,JCh_zhuoyin)               //T:環繞模式
#define JOS_DUAL_MONO_SETUP		_cat8_(JCh_su, JCh_te, JCh_re, JCh_o,JCh_mo,JCh_changyin,JCh_to,JCh_zhuoyin)
#define JOS_MIX_MONO_SETUP		_cat5_(Ch_hun, Ch_he, JCh_mo, JCh_no,Ch_yin)
//language string

#define JOS_ENGLISH             _cat_(Ch_ying, TCh_yu)                                  //T:英語
#define JOS_CHINESE             _cat3_(Ch_zhong, JCh_guo, TCh_yu)
#define JOS_JAPAN               _cat3_(Ch_ri, JCh_ben, TCh_yu)
#define JOS_FRENCH              _cat5_(JCh_hu, JCh_ra, JCh_n, JCh_su, TCh_yu)                                   //T:法語
#define JOS_GERMAM              _cat5_(JCh_to, JCh_zhuoyin,JCh_i, JCh_cu, TCh_yu)                                    //T:德語
#define JOS_SPANISH             _cat6_(JCh_su, JCh_he, JCh_banzhuoyin, JCh_i, JCh_n, TCh_yu)                           //T:西班牙
#define JOS_PORTUGUESE          _cat8_(JCh_ho, JCh_banzhuoyin,JCh_ru, JCh_to, JCh_ka, JCh_zhuoyin,JCh_ru, TCh_yu)                            //T:葡萄牙
#define JOS_LATIN               _cat4_(JCh_ra, JCh_te,JCh_n, TCh_yu)                         //T:拉丁語
#define JOS_POLISH              _cat8_(JCh_ho, JCh_banzhuoyin,JCh_changyin,JCh_ra, JCh_n, JCh_to, JCh_zhuoyin,TCh_yu)                         //T:拉丁語
#define JOS_CZECH               _cat4_(JCh_ci, JCh_xe,JCh_ko, TCh_yu)                         //T:拉丁語
#define JOS_HUNGARIAN           _cat7_(JCh_ha, JCh_n,JCh_ka,JCh_zhuoyin,JCh_ri,JCh_changyin, TCh_yu)                         //T:拉丁語
#define JOS_ICELANDIC           _cat8_(JCh_a, JCh_i,JCh_su,JCh_ra,JCh_n,JCh_to,JCh_zhuoyin, TCh_yu)                         //T:拉丁語
#define JOS_HINDI               _cat5_(JCh_i, JCh_n,JCh_to, JCh_zhuoyin,TCh_yu)                         //T:拉丁語
#define JOS_DUTCH               _cat6_(JCh_o, JCh_ra,JCh_n,JCh_ta,JCh_zhuoyin, TCh_yu)                         //T:拉丁語
#define JOS_TURKISH             _cat4_(JCh_to, JCh_ru,JCh_ko, TCh_yu)                         //T:拉丁語
#define JOS_DANISH              _cat7_(JCh_te,JCh_zhuoyin,JCh_n,JCh_ma, JCh_changyin,JCh_ku, TCh_yu)                         //T:拉丁語
#define JOS_SWEDISH             _cat8_(JCh_su, JCh_u,JCh_xe,JCh_changyin,JCh_te,JCh_zhuoyin,JCh_n, TCh_yu)                         //T:拉丁語
#define JOS_FINNISH             _cat8_(JCh_hu, JCh_xi,JCh_n,JCh_ra,JCh_n,JCh_to,JCh_zhuoyin, TCh_yu)                         //T:拉丁語
#define JOS_GREEK     	        _cat6_(JCh_ki, JCh_zhuoyin,JCh_ri,JCh_si,JCh_xya, TCh_yu)                         //T:拉丁語
#define JOS_NORWEGIAN           _cat6_(JCh_no, JCh_ru,JCh_u,JCh_xe,JCh_changyin,TCh_yu)                         //T:拉丁語

#define JOS_KOREAN              _cat3_(JCh_han, JCh_guo, TCh_yu)                         //T:拉丁語

#define JOS_THAI 	            _cat3_(JCh_ta, JCh_i,TCh_yu)                         //T:拉丁語
#define JOS_ITALIAN             _cat5_(JCh_i, JCh_ta,JCh_ri,JCh_a, TCh_yu)                         //T:拉丁語

#ifdef USE_TCHINESE_OSD
#define JOS_GROUP				TOS_GROUP
#define JOS_BASS_MODE_1			TOS_BASS_MODE_1
#define JOS_BASS_MODE_2			TOS_BASS_MODE_2
#define JOS_BASS_MODE_3			TOS_BASS_MODE_3
#define JOS_BASS_MANAGEMENT		TOS_BASS_MANAGEMENT
#define JOS_SFE_OUT				TOS_SFE_OUT
#define JOS_SFE_STD				TOS_SFE_STD
#define JOS_S_VIDEO				TOS_S_VIDEO
#define JOS_16_9				TOS_16_9
#define JOS_4_3LB				TOS_4_3LB
#define JOS_4_3PS				TOS_4_3PS
#define JOS_DOLBY_RF_SETUP		TOS_DOLBY_RF_SETUP
#elif 1//defined(USE_SCHINESE_OSD)//#ifdef USE_TCHINESE_OSD
#define JOS_GROUP				OS_GROUP
#define JOS_BASS_MODE_1			OS_BASS_MODE_1
#define JOS_BASS_MODE_2			OS_BASS_MODE_2
#define JOS_BASS_MODE_3			OS_BASS_MODE_3
#define JOS_BASS_MANAGEMENT		OS_BASS_MANAGEMENT
#define JOS_SFE_OUT				OS_SFE_OUT
#define JOS_SFE_STD				OS_SFE_STD
#define JOS_S_VIDEO				_cat6_("S", JCh_hi,JCh_zhuoyin,JCh_te,JCh_zhuoyin, JCh_o)
#define JOS_16_9				OS_16_9
#define JOS_4_3LB				OS_4_3LB
#define JOS_4_3PS				OS_4_3PS
#define JOS_DOLBY_RF_SETUP		_cat3_("RF", JCh_diao, Ch_zheng)
#endif//#ifdef USE_TCHINESE_OSD

#endif//USE_JAPANESE_OSD


#ifdef USE_KOREAN_OSD		//clead korean 2003-10-23 
#define KOS_NODISC          _cat6_(KCh_29, KCh_0e, KCh_2a," ",KCh_3d,KCh_3e)
#define KOS_TRACK           _cat_(KCh_42,KCh_43)
#define KOS_OPEN			_cat_(KCh_44,KCh_45)
#define KOS_CLOSE			_cat_(KCh_46,KCh_47)
#define KOS_PLAY			_cat3_(KCh_19,KCh_48,KCh_22)//CLEAD 19
#define KOS_REGION_5		_cat3_(KCh_07,KCh_08," 5")
#define KOS_PAUSE			_cat_(KCh_17,KCh_49)//clead 17
#define KOS_RANDOM			_cat_(KCh_4a,KCh_4b)
#define KOS_RESUME			_cat_(KCh_4c,KCh_4d)
#define KOS_STOP			_cat_(KCh_0e,KCh_4e)
#define KOS_STEP			_cat_(KCh_49,KCh_4f)
#define KOS_SELECT			_cat_(KCh_50,KCh_51)
#define KOS_READ			_cat_(KCh_52,KCh_47)
#define KOS_REGION_6		_cat3_(KCh_07,KCh_08," 6")
#define KOS_SIMULATE		_cat4_(KCh_21,KCh_55,KCh_0f,KCh_2e)
#define KOS_FF				_cat_(KCh_56,KCh_57)
#define KOS_FB				_cat3_(KCh_08,KCh_58,KCh_59)
#define KOS_NEXT			_cat_(KCh_3e,KCh_5a)
#define KOS_PREV			_cat3_(KCh_5b,KCh_5c,KCh_5d)
#define KOS_RETURN			_cat_(KCh_5e,KCh_5f)
#define KOS_MENU			_cat_(KCh_61,KCh_62)
#define KOS_SCORE			_cat_(KCh_64,KCh_1f)
#define KOS_MARK			_cat_(KCh_63,KCh_5b)
#define KOS_BROWSE			_cat4_(KCh_3b,KCh_13,KCh_6c,KCh_6d)
#define KOS_PROG			_cat7_(KCh_0c,KCh_0f,KCh_2e,KCh_65," ",KCh_66,KCh_67)
#define KOS_BASS_MODE_1		_cat7_(KCh_68,KCh_69,KCh_6a," ",KCh_0e,KCh_6b,KCh_6e)
#define KOS_REP				_cat_(KCh_6f,KCh_5e)
#define KOS_REP_DIR			_cat7_(KCh_6f,KCh_5e," ",KCh_70,KCh_43,KCh_26,KCh_20)
#define KOS_REP_1			_cat3_(KCh_6f,KCh_5e," ")
#define KOS_REP_ALL			_cat5_(KCh_56,KCh_53," ",KCh_6f,KCh_5e)
#define KOS_REP_CNL			_cat5_(KCh_6f,KCh_5e," ",KCh_71,KCh_72)
#define KOS_BASS_MODE_2		_cat6_(KCh_72,KCh_73," ",KCh_0e,KCh_6b,KCh_6e)
#define KOS_GOTO			_cat4_(KCh_76,KCh_77,KCh_78,KCh_47)
#define KOS_MUTE			_cat_(KCh_79,KCh_5a)
#define KOS_CANCEL_MUTE		_cat3_("CANCEL",KCh_79,KCh_5a)
#define KOS_CHL				_cat5_(KCh_49,KCh_0a," ",KCh_7a,KCh_7b)
#define KOS_CHR				_cat5_(KCh_49,KCh_0a," ",KCh_6c,KCh_7b)
#define KOS_STEREO			_cat_(KCh_01,KCh_1c)//clead 1c
#define KOS_LIVE			_cat_(KCh_7c,KCh_7d)
#define KOS_BASS_MODE_3		_cat6_(KCh_7e,KCh_7f," ",KCh_0e,KCh_6b,KCh_6e)
#define KOS_TIME			_cat_(KCh_36,KCh_80)
#define KOS_ZOOM			KCh_81
#define KOS_INTRO			_cat4_(KCh_3b,KCh_13,KCh_6c,KCh_6d)
#define KOS_SURR			_cat4_(KCh_82,KCh_13,KCh_83,KCh_1b)
#define KOS_BASS_MANAGEMENT	_cat4_(KCh_79,KCh_5a,KCh_6a,KCh_1b)
#define KOS_REP_A			_cat4_(KCh_6f,KCh_5e,"A","-")
#define KOS_REP_AB			_cat5_(KCh_6f,KCh_5e,"A","-","B")
#define KOS_PICUP			_cat_(KCh_81,"UP")
#define KOS_PICDN			_cat_(KCh_81,"DOWN")
#define KOS_PICL			_cat3_(KCh_81,KCh_7a,KCh_7b)
#define KOS_PICR			_cat3_(KCh_81,KCh_6c,KCh_7b)
#define KOS_CHAPTER			KCh_7d
#define KOS_ECHO			_cat_(KCh_6f,KCh_59)
#define KOS_TITLE			_cat_(KCh_84,KCh_85)
#define KOS_BAND			_cat_(KCh_86,KCh_1b)
#define KOS_VOL				_cat_(KCh_87,KCh_88)
#define KOS_KEY				_cat_(KCh_5a,KCh_89)
#define KOS_9FRAME_1		_cat4_("9",KCh_8a,KCh_8b," 1")
#define KOS_AUTO_L			_cat4_(KCh_44,KCh_8c,KCh_7a,KCh_7b)
#define KOS_AUTO_R			_cat4_(KCh_44,KCh_8c,KCh_6c,KCh_7b)
#define KOS_SEQUENCE		_cat5_(KCh_8d,KCh_82,KCh_19,KCh_48,KCh_22)
#define KOS_MENUPLAY		_cat5_(KCh_61,KCh_62,KCh_19,KCh_48,KCh_22)
#define KOS_PROG_PLAY		_cat4_("PRG",KCh_19,KCh_48,KCh_22)
#define KOS_DYNAMICRANGE	_cat4_(KCh_91,KCh_92,KCh_93,KCh_94)
#define KOS_OSD				_cat3_("OSD-",KCh_95,KCh_09)
#define KOS_TV_RATIO		_cat3_("TV-",KCh_96,KCh_73)
#define KOS_TV_SYS			_cat4_("TV-",KCh_36,KCh_0e,KCh_97)
#define KOS_EXIT_MENU		_cat4_(KCh_98,KCh_41,KCh_99,KCh_9a)
#define KOS_AUD_OUT			_cat4_(KCh_44,KCh_70,KCh_44,"-OUT")
#define KOS_VIDEO			_cat3_(KCh_39,KCh_70,KCh_44)
#define KOS_PASSWORD		_cat_(KCh_03,KCh_04)
#define KOS_RATING			_cat_(KCh_74,KCh_75)
#define KOS_YUV				_cat4_(KCh_9b,KCh_9c,KCh_9d,"-YUV")
#define KOS_AUTO			_cat_(KCh_44,KCh_8c)
#define KOS_OFF				_cat_(KCh_17,KCh_49)
#define KOS_NO_ADULT		_cat4_("A",KCh_75,KCh_21,KCh_38)
#define KOS_KID_ONLY		_cat3_(KCh_21,KCh_91,KCh_75)
#define KOS_VIEW_ALL		_cat3_(KCh_3f,KCh_84,KCh_32)
#define KOS_SUBWOOFER		_cat3_(KCh_a0,KCh_79,KCh_5a)
#define KOS_SATURATION		_cat_(KCh_a1,KCh_8a)
#define KOS_CLEAR			_cat_(KCh_72,KCh_a2)
#define KOS_EDIT			_cat_(KCh_66,KCh_67)
#define KOS_HUE				_cat_(KCh_a3,KCh_a4)
#define KOS_CONTRAST		_cat3_(KCh_50,KCh_a5,KCh_37)
#define KOS_BRIGHT_SETUP	_cat_(KCh_a8,KCh_47)
#define KOS_CHIP_ID			_cat_(KCh_a9,"ID")
#define KOS_REGION_CODE		_cat_(KCh_a8,KCh_47)
#define KOS_CHURCH			_cat_(KCh_aa,KCh_ab)
#define KOS_PASSIVE			_cat3_(KCh_3f,KCh_75,KCh_56)
#define KOS_WIDE			_cat3_(KCh_ac,KCh_22,KCh_1b)
#define KOS_STANDARD		_cat_(KCh_63,KCh_ad)
#define KOS_CLASSIC			_cat_(KCh_8f,KCh_56)
#define KOS_USER			_cat3_(KCh_ae,KCh_b0,KCh_b1)
#define KOS_SF				_cat5_(KCh_b2,KCh_b2,KCh_b3,KCh_56,KCh_57)
#define KOS_CSPK			_cat3_(KCh_b4,KCh_26,KCh_b5)
#define KOS_SSPK			_cat_(KCh_b6,KCh_53)
#define KOS_CSPK_DELAY		_cat5_(KCh_b4,KCh_26,KCh_b5,KCh_5b,KCh_b7)
#define KOS_SSPK_DELAY		_cat4_(KCh_b6,KCh_53,KCh_5b,KCh_b7)
#define KOS_FSPK			_cat_(KCh_b8,KCh_8b)
#define KOS_SYS_SETUP		_cat5_(KCh_36,KCh_0e,KCh_97,KCh_99,KCh_9a)
#define KOS_SPK_SETUP		_cat5_(KCh_0e,KCh_6b,KCh_6e,KCh_99,KCh_9a)
#define KOS_AUD_SETUP		_cat5_(KCh_44,KCh_70,KCh_44,KCh_99,KCh_9a)
#define KOS_DEFAULT_SETUP	_cat3_(KCh_70,KCh_b9,KCh_42)
#define KOS_SSAVER_SETUP	_cat5_(KCh_8a,KCh_8b,KCh_ba,KCh_04,KCh_47)
#define KOS_DIGITAL_SETUP	_cat5_(KCh_70,KCh_5b,KCh_bb,KCh_99,KCh_9a)
#define KOS_MIC_ONOFF		_cat3_("MIC",KCh_99,KCh_9a)
#define KOS_CD_DEBUG		_cat3_("CD",KCh_bc,KCh_5e)
#define KOS_SMART_UPGRADE	_cat8_(KCh_0e,KCh_29,KCh_42,KCh_9a,KCh_2e,KCh_48,KCh_22,KCh_1b)
#define KOS_UPGRADE_TO		_cat6_(KCh_9a,KCh_2e,KCh_48,KCh_22,KCh_1b,"TO")
#define KOS_UPGRADING		_cat6_(KCh_9a,KCh_2e,KCh_48,KCh_22,KCh_1b,KCh_17)
#define KOS_NOT_POWEROFF	_cat5_(KCh_46,KCh_47,KCh_29,KCh_bd,KCh_be)
//nono del.
#define KOS_REGION_1		_cat3_(KCh_07,KCh_08," 1")
#define KOS_REGION_2		_cat3_(KCh_07,KCh_08," 2")
#define KOS_REGION_3		_cat3_(KCh_07,KCh_08," 3")
#define KOS_REGION_4		_cat3_(KCh_07,KCh_08," 4")
#define KOS_LANG_SETUP		_cat4_(KCh_95,KCh_09,KCh_bf,KCh_c0)
#define KOS_RETURN_MAIN_SETUP	_cat3_(KCh_15,KCh_22,KCh_5b)
#define KOS_AUDIO_LANG_SETUP	_cat4_("AUDIO"," ",KCh_95,KCh_09)
#define KOS_SUBTITLE_LANG_SETUP	_cat4_(KCh_b1,KCh_c1,KCh_95,KCh_09)
#define KOS_MENU_LANG_SETUP		_cat4_(KCh_61,KCh_62,KCh_95,KCh_09)
#define KOS_DOWNMIX_SETUP		_cat4_(KCh_7e,KCh_7f,KCh_6a,KCh_1b)//CLEAD 1b
#define KOS_RESTORE_SETUP		_cat_(KCh_5e,KCh_c2)
#define KOS_DOLBY_OP_SETUP		_cat4_("OP"," ",KCh_6a,KCh_1b)//CLEAD 1b
#define KOS_MIX_MONO_SETUP		_cat4_(KCh_7e,KCh_7f,KCh_6a,KCh_2f)
#define KOS_SURROUND_MODE		_cat4_(KCh_8d,KCh_c4,KCh_6a,KCh_2f)
#define KOS_DOLBY_LINE_SETUP	_cat3_(KCh_b5,KCh_98,KCh_02)
#define KOS_DOLBY_RF_SETUP		_cat3_("RF",KCh_a1,KCh_c3)
#define KOS_DUAL_MONO_SETUP		_cat3_(KCh_7a,"+",KCh_6c)
#define KOS_PARENTAL_ERR		_cat4_(KCh_01,KCh_02,KCh_03,KCh_04)
#define KOS_REGION_ERR			_cat4_(KCh_05,KCh_06,KCh_07,KCh_08)

//
#define KOS_ENGLISH             _cat_(KCh_07, KCh_09)
#define KOS_CHINESE             _cat3_(KCh_17, KCh_18, KCh_09)
#define KOS_JAPAN               _cat3_(KCh_0a, KCh_0b, KCh_09)
#define KOS_FRENCH              _cat3_(KCh_0c, KCh_0d, KCh_0e)
#define KOS_GERMAM              _cat_(KCh_12,KCh_0a)
#define KOS_SPANISH             _cat4_(KCh_0e, KCh_15,KCh_16,KCh_09)
#define KOS_PORTUGUESE          _cat5_(KCh_0c, KCh_0f,KCh_10,KCh_11,KCh_09)
#define KOS_LATIN               _cat3_(KCh_13, KCh_14, KCh_09)
#define KOS_POLISH              _cat3_(KCh_19, KCh_1a, KCh_1b)
#define KOS_CZECH               _cat3_(KCh_1c, KCh_1d, KCh_09)
#define KOS_HUNGARIAN           _cat4_(KCh_1e, KCh_1f,KCh_20,KCh_09)
#define KOS_ICELANDIC           _cat5_(KCh_21, KCh_22,KCh_23,KCh_1a,KCh_1b)
#define KOS_HINDI               _cat_(KCh_16,KCh_37)
#define KOS_DUTCH               _cat4_(KCh_24, KCh_25,KCh_1a,KCh_1b)
#define KOS_TURKISH             _cat_(KCh_26,KCh_27)
#define KOS_DANISH              _cat4_(KCh_28, KCh_29,KCh_2a,KCh_09)
#define KOS_SWEDISH             _cat4_(KCh_0e, KCh_2b,KCh_2c,KCh_09)
#define KOS_FINNISH             _cat3_(KCh_2d, KCh_1a, KCh_1b)
#define KOS_GREEK     	        _cat4_(KCh_2e, KCh_20,KCh_0e,KCh_09)
#define KOS_NORWEGIAN           _cat5_(KCh_2f, KCh_30,KCh_31,KCh_22,KCh_09)
#define KOS_KOREAN              _cat_(KCh_32,KCh_18)
#define KOS_THAI 	            _cat_(KCh_33,KCh_18)
#define KOS_ITALIAN             _cat5_(KCh_22, KCh_34,KCh_20,KCh_21,KCh_09)
#define KOS_RUSSIAN    			_cat3_(KCh_35, KCh_36, KCh_21)
#define KOS_INDONESIAN			_cat6_(KCh_16, KCh_37,KCh_38,KCh_36,KCh_21,KCh_09)
#define KOS_ARABIC				_cat4_(KCh_21, KCh_13,KCh_39,KCh_21)
#define KOS_HEBRAIC				_cat4_(KCh_3a, KCh_3b,KCh_3c,KCh_09)
#define KOS_ROMANIAN			_cat5_(KCh_3c, KCh_29,KCh_38,KCh_1f,KCh_09)


#endif			//clead korean 2003-10-23 

#ifdef SUPPORT_FUNCTION_MENU 
#define OS_DISPLAY		_cat_(Ch_ping,Ch_xian3)
#define OS_BATTERY_STATUS   	_cat4_(Ch_dian,Ch_liang,Ch_xian3,Ch_shi2)
#define OS_SETUP    		_cat4_(Ch_cai,Ch_dan,Ch_she,Ch_zhi5)

#define TOS_DISPLAY		_cat_(Ch_ping,TCh_xian1)
#define TOS_BATTERY_STATUS   	_cat4_(TCh_dian,Ch_liang,TCh_xian1,Ch_shi2)
#define TOS_SETUP    		_cat4_(Ch_cai,TCh_dan,TCh_she,Ch_zhi5)

//#define JOS_DISPLAY		_cat_(Ch_ping,TCh_xian1)
//#define JOS_BATTERY_STATUS   	_cat4_(TCh_dian,Ch_liang,TCh_xian1,Ch_shi2)
//#define JOS_SETUP    		_cat4_(Ch_cai,TCh_dan,TCh_she,Ch_zhi5)

#endif


#ifdef USE_THAI_OSD	
#define  COS_OPEN               _cat8_(Th_15,Th_32,Th_81,Th_14,Th_0a,Th_05,Th_07,Th_0a)
#define  COS_CLOSE              _cat6_(Th_10,Th_0b,Th_24,Th_15,Th_16,Th_0b)
#define  COS_READ               _cat7_(Th_01,Th_0b,Th_0f,Th_19,Th_3f,Th_0b,Th_0a)
#define  COS_MUTE               _cat6_(Th_2f,Th_24,Th_15,Th_18,Th_14,Th_19)
#define  COS_STOP               _cat6_(Th_40,Th_25,Th_24,Th_15,Th_0e,Th_0a)
#define  COS_PAUSE              _cat9_(Th_40,Th_25,Th_24,Th_26,Th_1b,Th_27,Th_3e,Th_0b,Th_1b)
#define  COS_PLAY               _cat6_(Th_15,Th_0e,Th_0a,Th_05,Th_07,Th_0a)
#define  COS_FORWARD            _cat8_(Th_0c,Th_3e,Th_02,Th_09,Th_32,Th_40,Th_43,Th_0b)
#define  COS_BACKWARD           _cat9_(Th_0c,Th_3e,Th_02,Th_0c,Th_0f,Th_29,Th_40,Th_0f,Th_19)
#define  COS_NEXT               _cat4_(Th_42,Th_24,Th_09,Th_32)
#define  COS_PREV               _cat6_(Th_35,Th_07,Th_0b,Th_0a,Th_03,Th_0b)
#define  COS_AUTO               _cat6_(Th_60,Th_44,Th_20,Th_0a,Th_69,Th_6a)
#define  COS_ZOOM               _cat7_(Th_1e,Th_14,Th_0b,Th_14,Th_11,Th_0b,Th_21)
#define  COS_OFF                _cat_(Th_2f,Th_24)
#define  COS_ZOOM_UP            _cat9_(Th_15,Th_7d,Th_02,Th_0a,Th_11,Th_0b,Th_21,Th_7d,Th_0a)
#define  COS_ZOOM_DOWN          _cat9_(Th_15,Th_7d,Th_02,Th_0a,Th_11,Th_0b,Th_21,Th_0d,Th_19)
#define  COS_ZOOM_LEFT          _cat12_(Th_15,Th_7d,Th_02,Th_0a,Th_11,Th_0b,Th_21,Th_09,Th_32,Th_1a,Th_0b,Th_14)
#define  COS_ZOOM_RIGHT         _cat9_(Th_15,Th_7d,Th_02,Th_0a,Th_11,Th_0b,Th_1e,Th_1b,Th_0b)
#define  COS_INVALID_KEY        _cat10_(Th_0c,Th_24,Th_7f,Th_03,Th_08,Th_24,Th_21,Th_0d,Th_0b,Th_24)
#define  COS_STEP               _cat7_(Th_3c,Th_0d,Th_28,Th_0a,Th_11,Th_0b,Th_21)
#define  COS_RESUME             _cat11_(Th_15,Th_0e,Th_0a,Th_33,Th_02,Th_82,Th_0b,Th_0c,Th_15,Th_3a,Th_03)
#define  COS_P_SCAN_YPBPR       _cat11_(Th_11,Th_0b,Th_21,Th_05,Th_29,Th_29,Th_0a,Th_95,Th_44,Th_02,Th_0d)  
#define  COS_REPEAT_A           _cat8_(Th_39,Th_0b,Th_1c,Th_1b,Th_19,Th_40,Th_58,Th_19)  
#define  COS_REPEAT_A_B         _cat8_(Th_39,Th_0b,Th_1c,Th_1b,Th_19,Th_17,Th_02,Th_19) 
#define  COS_AB_CANCLE          _cat10_(Th_39,Th_0b,Th_1c,Th_1b,Th_19,Th_14,Th_0c,Th_15,Th_2b,Th_0c)   
#define  COS_REP                _cat5_(Th_15,Th_0e,Th_0a,Th_39,Th_0b) 
#define  COS_REP_1              _cat12_(Th_15,Th_0e,Th_0a,Th_39,Th_0b,Th_8d,Th_02,Th_19,Th_15,Th_18,Th_14,Th_19)   
#define  COS_REP_ALL            _cat8_(Th_15,Th_0e,Th_0a,Th_39,Th_0b,Th_05,Th_07,Th_0a)   
#define  COS_CHANNEL            _cat3_(Th_1c,Th_02,Th_19)
#define  COS_MONO_L             _cat7_(Th_15,Th_18,Th_14,Th_19,Th_1a,Th_0b,Th_14)        
#define  COS_MONO_R             _cat7_(Th_15,Th_18,Th_14,Th_19,Th_1e,Th_1b,Th_0b)
#define  COS_AUTO_L             _cat13_(Th_15,Th_18,Th_14,Th_19,Th_1a,Th_0b,Th_14,Th_60,Th_44,Th_20,Th_0a,Th_69,Th_6a)
#define  COS_AUTO_R             _cat13_(Th_15,Th_18,Th_14,Th_19,Th_1e,Th_1b,Th_0b,Th_60,Th_44,Th_20,Th_0a,Th_69,Th_6a)
#define  COS_PROG               _cat7_(Th_20,Th_32,Th_3e,Th_05,Th_0c,Th_3e,Th_03)
#define  COS_PRG_PLAY           _cat10_(Th_15,Th_0e,Th_0a,Th_20,Th_32,Th_3e,Th_05,Th_0c,Th_3e,Th_03)
#define  COS_RETURN             _cat6_(Th_15,Th_0e,Th_0a,Th_0c,Th_0f,Th_29)
#define  COS_SELECT             _cat4_(Th_15,Th_38,Th_02,Th_0c)
#define  COS_CH                 _cat3_(Th_1c,Th_02,Th_19)
#define  COS_THAI               _cat3_(Th_09,Th_13,Th_14)
#define  COS_ENGLISH            _cat5_(Th_60,Th_19,Th_0c,Th_61,Th_12)
#define  COS_SRND               _cat12_(Th_15,Th_18,Th_14,Th_19,Th_3e,Th_02,Th_29,Th_4d,Th_4e,Th_13,Th_0b,Th_19)
#define  COS_CONCERT            _cat11_(Th_0c,Th_0b,Th_3e,Th_05,Th_17,Th_24,Th_19,Th_24,Th_0a,Th_44,Th_65)
#define  COS_CHURCH             _cat10_(Th_15,Th_18,Th_14,Th_19,Th_17,Th_1b,Th_24,Th_03,Th_0a,Th_47)
#define  COS_WIDE               _cat8_(Th_15,Th_18,Th_14,Th_19,Th_0c,Th_37,Th_0b,Th_19)
#define  COS_LIVE               _cat9_(Th_0c,Th_0b,Th_3e,Th_05,Th_17,Th_24,Th_19,Th_27,Th_24)
#define  COS_MENU_PLAY          _cat9_(Th_15,Th_03,Th_4f,Th_15,Th_0e,Th_0a,Th_05,Th_07,Th_0a)
#define  COS_ANGLE              _cat_(Th_59,Th_03)
#define  COS_SYSTEM_SETUP       _cat8_(Th_45,Th_19,Th_62,Th_0b,Th_3e,Th_28,Th_29,Th_29)
#define  COS_TV_SYSTEM          _cat5_(Th_3e,Th_28,Th_29,Th_29,Th_18)
#define  COS_SCREEN_SAVER       _cat7_(Th_93,Th_0c,Th_40,Th_43,Th_0b,Th_82,Th_02)
#define  COS_ON                 _cat3_(Th_15,Th_2f,Th_24)
#define  COS_VIDEO              _cat4_(Th_84,Th_2a,Th_20,Th_02)
#define  COS_TV_TYPE            _cat5_(Th_78,Th_5d,Th_24,Th_3c,Th_84)
#define  COS_PASSWORD           _cat6_(Th_3e,Th_9b,Th_17,Th_07,Th_0b,Th_0a)
#define  COS_RATING             _cat4_(Th_3e,Th_28,Th_55,Th_29)
#define  COS_NO_ADULT           _cat7_(Th_09,Th_04,Th_06,Th_75,Th_76,Th_40,Th_a1)
#define  COS_KID_SAFE           _cat8_(Th_a2,Th_02,Th_19,Th_31,Th_0a,Th_15,Th_a3,Th_0c)
#define  COS_VIEW_ALL           _cat8_(Th_11,Th_0b,Th_21,Th_4c,Th_19,Th_40,Th_03,Th_24)
#define  COS_DEFAULT            _cat11_(Th_62,Th_0b,Th_44,Th_0b,Th_03,Th_20,Th_3e,Th_19,Th_19,Th_0b,Th_0a)
#define  COS_RESTORE            _cat7_(Th_15,Th_65,Th_14,Th_0c,Th_0c,Th_0f,Th_29)
#define  COS_EXIT_SETUP         _cat9_(Th_02,Th_02,Th_0c,Th_82,Th_0b,Th_0c,Th_15,Th_03,Th_4f)
#define  COS_LANGUAGE_SETUP     _cat8_(Th_45,Th_19,Th_62,Th_0b,Th_11,Th_0b,Th_12,Th_0b)
#define  COS_OSD_LANGUAGE       _cat8_(Th_11,Th_0b,Th_12,Th_0b,Th_8f,Th_1b,Th_09,Th_32)
#define  COS_CHINESE            _cat_(Th_92,Th_0a)
#define  COS_GERMAN             _cat6_(Th_15,Th_14,Th_02,Th_3e,Th_69,Th_0a)
#define  COS_SPANISH            _cat4_(Th_17,Th_15,Th_32,Th_0a)
#define  COS_FRENCH             _cat6_(Th_98,Th_99,Th_19,Th_15,Th_4e,Th_17)
#define  COS_PORTUGUESE         _cat7_(Th_20,Th_32,Th_3e,Th_a4,Th_15,Th_0c,Th_17)
#define  COS_AUDIO_LANG         _cat8_(Th_15,Th_18,Th_14,Th_19,Th_21,Th_0b,Th_0c,Th_a5)
#define  COS_JAPAN              _cat3_(Th_a6,Th_7f,Th_0a)
#define  COS_LATIN              _cat4_(Th_0d,Th_28,Th_6a,Th_0a)
#define  COS_SUBTITLE_LANG      _cat10_(Th_11,Th_0b,Th_12,Th_0b,Th_29,Th_3e,Th_3e,Th_14,Th_0b,Th_14)
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:29
#define  COS_SUBTITLE_2ND_LANG  _cat11_(Th_11,Th_0b,Th_12,Th_0b,Th_29,Th_3e,Th_3e,Th_14,Th_0b,Th_14," 2")
#endif
#define  COS_MENU_LANG          _cat7_(Th_15,Th_03,Th_4f,Th_11,Th_0b,Th_12,Th_0b)
#define  COS_AUDIO_SETUP        _cat8_(Th_45,Th_19,Th_62,Th_0b,Th_15,Th_18,Th_14,Th_19)
#define  COS_AUDIO_OUT          _cat7_(Th_15,Th_18,Th_14,Th_19,Th_02,Th_02,Th_0c)
#define  COS_MIC_SETUP          _cat7_(Th_42,Th_19,Th_62,Th_0b,Th_09,Th_03,Th_8e)
#define  COS_MIC_VOL            _cat8_(Th_3e,Th_28,Th_55,Th_29,Th_15,Th_18,Th_14,Th_19)
#define  COS_KEY                _cat7_(Th_20,Th_13,Th_0a,Th_15,Th_18,Th_14,Th_19)
#define  COS_VIDEO_SETUP        _cat8_(Th_42,Th_19,Th_62,Th_0b,Th_84,Th_2a,Th_20,Th_02)
#define  COS_BRIGHTNESS         _cat11_(Th_27,Th_1b,Th_0b,Th_03,Th_17,Th_a7,Th_0b,Th_19,Th_11,Th_0b,Th_21)
#define  COS_CONTRAST           _cat10_(Th_27,Th_1b,Th_0b,Th_03,Th_15,Th_16,Th_03,Th_11,Th_0b,Th_21)
#define  COS_HUE                _cat_(Th_18,"")
#define  COS_SATURATION         _cat6_(Th_18,Th_15,Th_16,Th_03,Th_56,Th_24)
#define  COS_SPEAKER_SETUP      _cat9_(Th_45,Th_19,Th_62,Th_0b,Th_54,Th_0b,Th_20,Th_21,Th_19)
#define  COS_STEREO             _cat7_(Th_17,Th_15,Th_44,Th_02,Th_1f,Th_20,Th_02)
#define  COS_VSS                _cat9_(Th_15,Th_18,Th_14,Th_19,Th_2e,Th_0b,Th_0d,Th_02,Th_19)
#define  COS_5_1CH              _cat4_("5_1",Th_1c,Th_02,Th_19)
#define  COS_SUBWOOFER          _cat11_(Th_54,Th_0b,Th_20,Th_21,Th_19,Th_15,Th_18,Th_14,Th_19,Th_70,Th_0b)
#define  COS_BASS_MODE          _cat10_(Th_20,Th_40,Th_03,Th_24,Th_15,Th_18,Th_14,Th_19,Th_70,Th_0b)
#define  COS_CENTER_DELAY       _cat13_(Th_40,Th_5c,Th_1b,Th_19,Th_54,Th_0b,Th_20,Th_21,Th_19,Th_0c,Th_0d,Th_0b,Th_19)
#define  COS_0_MS               _cat5_("0",Th_94,Th_0a,Th_0b,Th_3c)
#define  COS_2_MS               _cat5_("2",Th_94,Th_0a,Th_0b,Th_3c)
#define  COS_4_MS               _cat5_("4",Th_94,Th_0a,Th_0b,Th_3c)
#define  COS_6_MS               _cat5_("0",h_94,Th_0a,Th_0b,Th_3c)
#define  COS_12_MS              _cat5_("12",Th_94,Th_0a,Th_0b,Th_3c)
#define  COS_REAR_DELAY         _cat12_(Th_40,Th_5c,Th_1b,Th_19,Th_54,Th_0b,Th_20,Th_21,Th_19,Th_40,Th_0f,Th_19)
#define  COS_DIGITAL_SETUP      _cat9_(Th_45,Th_19,Th_62,Th_0b,Th_3a,Th_95,Th_44,Th_02,Th_0d)
#define  COS_DYNAMICRANGE       _cat9_(Th_2c,Th_0a,Th_09,Th_24,Th_15,Th_01,Th_18,Th_14,Th_19)
#define  COS_DUAL_MONO          _cat7_(Th_05,Th_14,Th_0c,Th_15,Th_18,Th_14,Th_19)
#define  COS_MIX_MONO           _cat7_(Th_3e,Th_1b,Th_03,Th_15,Th_18,Th_14,Th_19)
#define  COS_VOL                _cat8_(Th_3e,Th_28,Th_55,Th_29,Th_15,Th_18,Th_14,Th_19)
#define  COS_ECHO               _cat7_(Th_15,Th_18,Th_14,Th_19,Th_57,Th_02,Th_19)
#define  COS_DOWNMIX            _cat7_(Th_15,Th_18,Th_14,Th_19,Th_21,Th_17,Th_03)
#define  COS_PC_VGA             _cat11_(Th_2f,Th_61,Th_8e,Th_61,Th_21,Th_93,Th_1b,Th_15,Th_8e,Th_61,Th_37)
#define  COS_INTERLACE          _cat6_(Th_47,Th_61,Th_15,Th_7e,Th_61,Th_21)
#define  COS_ALL_LG_SPK         _cat13_(Th_0f,Th_0b,Th_20,Th_21,Th_19,Th_76,Th_40,Th_a6,Th_13,Th_19,Th_40,Th_03,Th_44)
#define  COS_ALL_SM_SPK         _cat12_(Th_0f,Th_0b,Th_20,Th_21,Th_19,Th_15,Th_18,Th_27,Th_19,Th_40,Th_03,Th_44)
#define  COS_MIXED_SPK          _cat10_(Th_0f,Th_0b,Th_20,Th_21,Th_19,Th_15,Th_19,Th_3e,Th_1b,Th_03)
#define  COS_OP_MODE            _cat11_(Th_20,Th_40,Th_03,Th_44,Th_24,Th_24,Th_79,Th_44,Th_27,Th_24,Th_0d)
#define  COS_ALL_SM_SPK         _cat12_(Th_0f,Th_0b,Th_20,Th_21,Th_19,Th_15,Th_18,Th_27,Th_19,Th_40,Th_03,Th_24)
#define  COS_REMOD              _cat6_(Th_27,Th_24,Th_0a,Th_3e,Th_40,Th_23)
#define  COS_LINE_OUT           _cat8_(Th_23,Th_a6,Th_a6,Th_0b,Th_87,Th_24,Th_24,Th_27)


#endif     //USE_THAI_OSD

#if defined(BRIGHTNESS_COLOR_KEY)||defined(VIEW_MODE_KEY)
#define OS_COLOR				_cat_(Ch_se,Ch_du2)
#define OS_VIEW_MODE_NORMAL   	_cat4_(Ch_zheng2, Ch_chang3,Ch_mo, Ch_shi)
#define OS_VIEW_MODE_FULL      	_cat5_(Ch_quan, Ch_ping, Ch_mu,Ch_mo, Ch_shi)
#endif


#ifdef  SUPPORT_CHINESE_OTHER_STRING 
#define OS_JIYI      _cat4_(Ch_ji4,Ch_yi4,Ch_die,Ch_pian)
#define OS_GENERAL_SETUP _cat4_(Ch_pu4,Ch_tong4,Ch_she,TCh_ding)
#endif//endif  #ifdef SUPPORT_CHINESE_OTHER_STRING


#ifdef USE_NEW_SCHINESE_OSD //liyl add 20060116
#define _cat16_(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)     a b c d e f g h i j k l m n o p
#define _cat17_(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q)  a b c d e f g h i j k l m n o p q
#define _cat27_(a, b, c, d, e, f, g, h ,i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, a1)   \
                a b c d e f g h i j k l m n o p q r s t u v w x y z a1
#define _cat35_(a, b, c, d, e, f, g, h ,i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, a1, b1, c1, d1, e1, f1, g1, h1, i1)   \
                a b c d e f g h i j k l m n o p q r s t u v w x y z a1 b1 c1 d1 e1 f1 g1 h1 i1

#define DVB_OS_CHAN_GUIDE           _cat4_(ch_jie_bdda, ch_mu_c4bf, ch_guan_b9dc, ch_li_c0ed)       //CHANNEL GUIDE
#define DVB_OS_SYS_CONFIG           _cat4_(ch_xi_cfb5, ch_tong_cdb3, ch_she_c9e8, ch_zhi_d6c3)      //SYSTEM CONFIG
#define DVB_OS_INSTALLATION         _cat4_(ch_an_b0b2, ch_zhuang_d7b0, ch_she_c9e8, ch_ding_b6a8)   //INSTALLATION
#define DVB_OS_GAME                 _cat_(ch_you_d3ce, ch_xi_cfb7)                                  //GAME
#define DVB_OS_TV_CHAN              _cat4_(ch_dian_b5e7, ch_shi_cad3, ch_jie_bdda, ch_mu_c4bf)      //TV CHANNELS
#define DVB_OS_RADIO_CHAN           _cat4_(ch_guang_b9e3, ch_bo_b2a5, ch_jie_bdda, ch_mu_c4bf)      //RADIO CHANNELS
#define DVB_OS_CHAN_CLASS           _cat4_(ch_jie_bdda, ch_mu_c4bf, ch_fen_b7d6, ch_lei_c0e0)       //CHANNEL CLASS
#define DVB_OS_CHAN_EDIT            _cat4_(ch_jie_bdda, ch_mu_c4bf, ch_bian_b1e0, ch_ji_bcad)       //CHANNEL EDIT
#define DVB_OS_BOOK_LIST            _cat4_(ch_jie_bdda, ch_mu_c4bf, ch_yu_d4a4, ch_yue_d4bc)        //BOOK LIST
#define DVB_OS_NUM                  _cat_(ch_xu_d0f2, ch_hao_bac5)          //NO.
#define DVB_OS_ALL_TV               _cat6_(ch_suo_cbf9, ch_you_d3d0, ch_dian_b5e7, ch_shi_cad3, ch_jie_bdda, ch_mu_c4bf)    //ALL TV
#define DVB_OS_FAVOR                _cat_(ch_xi_cfb2, ch_ai_b0ae)           //favor
#define DVB_OS_MOVIE                _cat_(ch_dian_b5e7, ch_ying_d3b0)       //movie
#define DVB_OS_NEWS                 _cat_(ch_xin_d0c2, ch_wen_cec5)         //news
#define DVB_OS_SHOW                 _cat_(ch_zong_d7db, ch_yi_d2d5)         //show
#define DVB_OS_SPORT                _cat_(ch_ti_cce5, ch_yu_)               //sport
#define DVB_OS_KIDS                 _cat_(ch_er_, ch_tong_)                 //kid
#define DVB_OS_ARTS                 _cat_(ch_yi_d2d5, ch_shu_)              //arts
#define DVB_OS_SOCIAL               _cat_(ch_she_, ch_hui_)                 //social
#define DVB_OS_CANCEL               _cat_(ch_qu_c8a1, ch_xiao_cffb)         //cancel
#define DVB_OS_FREE_SCRAMBLE        _cat5_(ch_mian_c3e2, ch_fei_b7d1, "~", ch_shou_cad5, ch_fei_b7d1)
#define DVB_OS_SCRAMBLE_FREE        _cat5_(ch_shou_cad5, ch_fei_b7d1, "~", ch_mian_c3e2, ch_fei_b7d1)
#define DVB_OS_TRANSPONDER          _cat_(ch_pin_c6b5, ch_dian_b5e3)
#define DVB_OS_LR_KEY_SWICH         _cat10_(ch_zuo_d7f3, "/", ch_you_d3d2, ch_jian_bcfc, ch_qie_c7d0, ch_huan_bbbb, ch_jie_bdda, ch_mu_c4bf, ch_fen_b7d6, ch_lei_c0e0)
#define DVB_OS_CHAN_SORT            _cat9_(ch_xian_cfd4, ch_shi_cabe, ch_jian_bcfc, ch_jin_bdf8, ch_ru_c8eb, ch_pai_c5c5, ch_xu_d0f2, ch_lie_c1d0, ch_biao_b1ed)
#define DVB_OS_ALL_RADIO            _cat6_(ch_suo_cbf9, ch_you_d3d0, ch_guang_b9e3, ch_bo_b2a5, ch_jie_bdda, ch_mu_c4bf)
#define DVB_OS_TV                   _cat_(ch_dian_b5e7, ch_shi_cad3)
#define DVB_OS_RADIO                _cat_(ch_guang_b9e3, ch_bo_b2a5)
#define DVB_OS_ENTER_CHECK_CNL      _cat8_(ch_que_c8b7, ch_ren_c8cf, ch_jian_bcfc, ch_xuan_d1a1, ch_ze_d4f1, "/", ch_qu_c8a1, ch_xiao_cffb)
#define DVB_OS_TV_RADIO_SWICH       _cat13_(ch_dian_b5e7, ch_shi_cad3, "/", ch_guang_b9e3, ch_bo_b2a5, ch_jian_bcfc, ch_qie_c7d0, ch_huan_bbbb, ch_dian_b5e7, ch_shi_cad3, "/", ch_guang_b9e3, ch_bo_b2a5)
#define DVB_OS_MOVE                 _cat_(ch_yi_d2c6, ch_dong_b6af)
#define DVB_OS_SKIP                 _cat_(ch_tiao_, ch_guo_)
#define DVB_OS_LOCK                 _cat_(ch_suo_cbf8, ch_ding_b6a8)
#define DVB_OS_DELETE               _cat_(ch_shan_c9be, ch_chu_b3fd)
#define DVB_OS_ENTER_RENAME         _cat6_(ch_que_c8b7, ch_ren_c8cf, ch_jian_bcfc, ch_chong_d6d8, ch_ming_c3fc, ch_ming_c3fb)
#define DVB_OS_WORD_CHOICE          _cat17_(ch_shang_c9cf, "/", ch_xia_cfc2, ch_jian_bcfc, ch_xuan_d1a1, ch_ze_d4f1, ch_zi_d7d6, ch_fu_b7fb, ",", \
                                            ch_zuo_d7f3, "/", ch_you_d3d2, ch_jian_bcfc, ch_yi_d2c6, ch_dong_b6af, ch_wei_cebb, ch_zhi_d6c3)
#define DVB_OS_ENTER_FINISH_RENAME  _cat8_(ch_que_c8b7, ch_ren_c8cf, ch_jian_bcfc, ch_jie_bde1, ch_shu_caf8, ch_chong_d6d8, ch_ming_c3fc, ch_ming_c3fb)
#define DVB_OS_ENTER_MOVE_PRO       _cat7_(ch_que_c8b7, ch_ren_c8cf, ch_jian_bcfc, ch_yi_d2c6, ch_dong_b6af, ch_jie_bdda, ch_mu_c4bf)
#define DVB_OS_UD_MOVE_PRO          _cat8_(ch_shang_c9cf, "/", ch_xia_cfc2, ch_jian_bcfc, ch_yi_d2c6, ch_dong_b6af, ch_jie_bdda, ch_mu_c4bf)
#define DVB_OS_ENTER_FINISH_MOVE    _cat7_(ch_que_c8b7, ch_ren_c8cf, ch_jian_bcfc, ch_jie_bde1, ch_shu_caf8, ch_yi_d2c6, ch_dong_b6af)
#define DVB_OS_ENTER_LOCK_UNLOCK    _cat8_(ch_que_c8b7, ch_ren_c8cf, ch_jian_bcfc, ch_suo_cbf8, ch_ding_b6a8, "/", ch_jie_bde2, ch_suo_cbf8)
#define DVB_OS_TV_SETTING           _cat5_(ch_dian_b5e7, ch_shi_cad3, ch_ji_bbfa, ch_she_c9e8, ch_zhi_d6c3)
#define DVB_OS_VIDEO_SETTING        _cat4_(ch_shi_cad3, ch_pin_c6b5, ch_she_c9e8, ch_zhi_d6c3)
#define DVB_OS_AUDIO_SETTING        _cat4_(ch_yin_d2f4, ch_pin_c6b5, ch_she_c9e8, ch_zhi_d6c3)
#define DVB_OS_LANGUAGE             _cat4_(ch_yu_d3ef, ch_yan_d1d4, ch_xuan_d1a1, ch_ze_d4f1)
#define DVB_OS_PARENT_CONTROL       _cat4_(ch_suo_cbf8, ch_ding_b6a8, ch_she_c9e8, ch_zhi_d6c3)
#define DVB_OS_TIME_SETTING         _cat4_(ch_shi_cab1, ch_jian_bce4, ch_she_c9e8, ch_zhi_d6c3)
#define DVB_OS_SYS_INFO             _cat4_(ch_xi_cfb5, ch_tong_cdb3, ch_xin_d0c5, ch_xi_cfa2)
#define DVB_OS_TV_SYS               _cat5_(ch_dian_b5e7,ch_shi_cad3, ch_ji_bbfa, ch_zhi_d6c6, ch_shi_cabd)
#define DVB_OS_VIDEO                _cat4_(ch_shi_cad3, ch_pin_c6b5, ch_shu_cae4, ch_chu_b3f6)
#define DVB_OS_TV_TYPE              _cat6_(ch_ping_c6c1, ch_mu_c4bb, ch_hua_bbad, ch_mian_c3e6, ch_bi_b1c8, ch_li_c0fd)
#define DVB_OS_AUTO                 _cat_(ch_zi_d7d4, ch_dong_b6af)
#define DVB_OS_YCBCR                _cat4_(ch_shi_cad3, ch_pin_c6b5, ch_fen_b7d6, ch_liang_c1bf)
#define DVB_OS_BRIGHTNESS           _cat_(ch_liang_c1c1, ch_du_b6c8)
#define DVB_OS_CONTRAST             _cat3_(ch_dui_b6d4, ch_bi_b1c8, ch_du_b6c8)
#define DVB_OS_HUE                  _cat_(ch_se_c9ab, ch_diao_b5f7)
#define DVB_OS_SATURATION           _cat3_(ch_bao_b1a5, ch_he_bacd, ch_du_b6c8)
#define DVB_OS_AUDIO_OUT            _cat4_(ch_shu_cafd, ch_ma_c2eb, ch_shu_cae4, ch_chu_b3f6)
#define DVB_OS_SPDIF_RAW            _cat3_("SPDIF/", ch_yuan_d4b4, ch_ma_c2eb)
#define DVB_OS_OSD_LANGUAGE         _cat6_(ch_hua_bbad, ch_mian_c3e6, ch_xian_cfd4, ch_shi_cabe, ch_yu_d3ef, ch_yan_d1d4)
#define DVB_OS_ENGLISH              _cat_(ch_ying_d3a2, ch_yu_d3ef)
#define DVB_OS_JAPANESE             _cat_(ch_ri_c8d5, ch_yu_d3ef)
#define DVB_OS_FRENCH               _cat_(ch_fa_b7a8, ch_yu_d3ef)
#define DVB_OS_PORTUGUESE           _cat4_(ch_pu_c6cf, ch_tao_ccd1, ch_ya_d1c0, ch_yu_d3ef)
#define DVB_OS_GERMAN               _cat_(ch_de_b5c2, ch_yu_d3ef)
#define DVB_OS_LATIN                _cat3_(ch_la_c0ad, ch_ding_b6a1, ch_yu_d3ef)
#define DVB_OS_SPANISH              _cat4_(ch_xi_cef7, ch_ban_b0e0, ch_ya_d1c0, ch_yu_d3ef)
#define DVB_OS_CHINESE              _cat_(ch_han_baba, ch_yu_d3ef)
#define DVB_OS_POLISH               _cat3_(ch_bo_b2a8, ch_lan_c0bc, ch_yu_d3ef)
#define DVB_OS_CZECH                _cat3_(ch_jie_bddd, ch_ke_bfcb, ch_yu_d3ef)
#define DVB_OS_HUNGARIAN            _cat4_(ch_xiong_d0d9, ch_ya_d1c0, ch_li_c0fb, ch_yu_d3ef)
#define DVB_OS_ICELANDIC            _cat3_(ch_bing_b1f9, ch_dao_b5ba, ch_yu_d3ef)
#define DVB_OS_HINDI                _cat3_(ch_yin_d3a1, ch_di_b5d8, ch_yu_d3ef)
#define DVB_OS_DUTCH                _cat3_(ch_he_bac9, ch_lan_c0bc, ch_yu_d3ef)
#define DVB_OS_TURKISH              _cat4_(ch_tu_cdc1, ch_er_b6fa, ch_qi_c6e4, ch_yu_d3ef)
#define DVB_OS_DANISH               _cat3_(ch_dan_b5a4, ch_mai_c2f3, ch_yu_d3ef)
#define DVB_OS_SWEDISH              _cat3_(ch_rui_c8f0, ch_dian_b5e4, ch_yu_d3ef)
#define DVB_OS_FINNISH              _cat3_(ch_fen_b7d2, ch_lan_c0bc, ch_yu_d3ef)
#define DVB_OS_GREEK                _cat3_(ch_xi_cfa3, ch_la_c0b0, ch_yu_d3ef)
#define DVB_OS_NORWEGIAN            _cat3_(ch_nuo_c5b2, ch_wei_cdfe, ch_yu_d3ef)
#define DVB_OS_KOREAN               _cat3_(ch_han_baab, ch_guo_b9fa, ch_yu_d3ef)
#define DVB_OS_THAI                 _cat3_(ch_tai_cca9, ch_guo_b9fa, ch_yu_d3ef)
#define DVB_OS_ITALIAN              _cat4_(ch_yi_d2e2, ch_da_b4f3, ch_li_c0fb, ch_yu_d3ef)
#define DVB_OS_RUSSIAN              _cat_(ch_e_b6ed, ch_yu_d3ef)
#define DVB_OS_INDONESIAN           _cat3_(ch_yin_d3a1, ch_ni_c4e1, ch_yu_d3ef)
#define DVB_OS_ARABIC               _cat4_(ch_a_b0a2, ch_la_c0ad, ch_bo_b2ae, ch_yu_d3ef)
#define DVB_OS_HEBRAIC              _cat4_(ch_xi_cef7, ch_bo_b2ae, ch_lai_c0b4, ch_yu_d3ef)
#define DVB_OS_ROMANIAN             _cat5_(ch_luo_c2de, ch_ma_c2ed, ch_ni_c4e1, ch_ya_d1c7, ch_yu_d3ef)
#define DVB_OS_BULGARIAN            _cat5_(ch_bao_b1a3, ch_jia_bcd3, ch_li_c0fb, ch_ya_d1c7, ch_yu_d3ef)
#define DVB_OS_CROATIAN             _cat5_(ch_ke_bfcb, ch_luo_c2de, ch_di_b5d8, ch_ya_d1c7, ch_yu_d3ef)
#define DVB_OS_ESTONIAN             _cat5_(ch_ai_b0ae, ch_sha_c9b3, ch_ni_c4e1, ch_ya_d1c7, ch_yu_d3ef)
#define DVB_OS_LITHUANIAN           _cat4_(ch_li_c1a2, ch_tao_ccd5, ch_wan_cdf0, ch_yu_d3ef)
#define DVB_OS_LATVIAN              _cat5_(ch_la_c0ad, ch_tuo_cdd1, ch_wei_ceac, ch_ya_d1c7, ch_yu_d3ef)
#define DVB_OS_PORTUGU              _cat3_(ch_ba_b0cd, ch_xi_cef7, ch_yu_d3ef)
#define DVB_OS_SLOVENIAN            _cat6_(ch_si_cbb9, ch_luo_c2e5, ch_wen_cec4, ch_ni_c4e1, ch_ya_d1c7, ch_yu_d3ef)
#define DVB_OS_CHANGE_PIN           _cat4_(ch_xiu_d0de, ch_gai_b8c4, ch_mi_c3dc, ch_ma_c2eb)
#define DVB_OS_PRESS_ENTER          _cat_(ch_que_c8b7, ch_ren_c8cf)
#define DVB_OS_OLD_PIN              _cat3_(ch_jiu_bec9, ch_mi_c3dc, ch_ma_c2eb)
#define DVB_OS_NEW_PIN              _cat3_(ch_xin_d0c2, ch_mi_c3dc, ch_ma_c2eb)
#define DVB_OS_CONFIRM              DVB_OS_PRESS_ENTER
#define DVB_OS_PASSWORD             _cat_(ch_mi_c3dc, ch_ma_c2eb)
#define DVB_OS_CHAN_LOCK            _cat4_(ch_jie_bdda, ch_mu_c4bf, ch_suo_cbf8, ch_ding_b6a8)
#define DVB_OS_TIME_ZONE            _cat_(ch_shi_cab1, ch_qu_c7f8)
#define DVB_OS_SLEEP_TIME           _cat4_(ch_dai_b4fd, ch_ji_bbfa, ch_shi_cab1, ch_jian_bce4)
#define DVB_OS_TIME_SAVING          _cat4_(ch_bao_b1a3, ch_cun_b4e6, ch_shi_cab1, ch_jian_bce4)
#define DVB_OS_INFO_PAGE            _cat4_(ch_ti_cce1, ch_shi_cabe, ch_xin_d0c5, ch_xi_cfa2)
#define DVB_OS_AUTO_SCAN            _cat4_(ch_zi_d7d4, ch_dong_b6af, ch_sou_cbd1, ch_tai_cca8)
#define DVB_OS_MANUAL_SCAN          _cat4_(ch_shou_cad6, ch_dong_b6af, ch_sou_cbd1, ch_tai_cca8)
#define DVB_OS_DEFAULT_SETUP        _cat4_(ch_chu_b3f6, ch_chang_b3a7, ch_she_c9e8, ch_ding_b6a8)
#define DVB_OS_SELECT_COUNTRY       _cat4_(ch_guo_b9fa, ch_jia_bcd2, ch_xuan_d1a1, ch_ze_d4f1)
#define DVB_OS_START_SCAN           _cat4_(ch_kai_bfaa, ch_shi_cabc, ch_sao_c9a8, ch_tai_cca8)
#define DVB_OS_CHANNEL              _cat_(ch_pin_c6b5, ch_dao_b5c0)
#define DVB_OS_FREQUENCY            _cat_(ch_pin_c6b5, ch_lv_c2ca)
#define DVB_OS_PROGRESS             _cat_(ch_jin_bdf8, ch_du_b6c8)
#define DVB_OS_COUNTRY              DVB_OS_SELECT_COUNTRY
#define DVB_OS_SCAN_TYPE            _cat4_(ch_sou_cbd1, ch_suo_cbf7, ch_lei_c0e0, ch_xing_d0cd)
#define DVB_OS_START_CHANNEL        _cat4_(ch_qi_c6f0, ch_shi_cabc, ch_pin_c6b5, ch_dian_b5e3)
#define DVB_OS_START_FREQ           _cat4_(ch_qi_c6f0, ch_shi_cabc, ch_pin_c6b5, ch_lv_c2ca)
#define DVB_OS_END_CHANNEL          _cat4_(ch_jie_bde1, ch_shu_caf8, ch_pin_c6b5, ch_dian_b5e3)
#define DVB_OS_END_FREQ             _cat4_(ch_jie_bde1, ch_shu_caf8, ch_pin_c6b5, ch_lv_c2ca)
#define DVB_OS_BAND_WIDTH           _cat_(ch_dai_b4f8, ch_kuan_bfed)
#define DVB_OS_CHINA                _cat_(ch_zhong_d6d0, ch_guo_b9fa)
#define DVB_OS_TWN                  _cat_(ch_tai_cca8, ch_wan_cde5)
#define DVB_OS_GERMANY              _cat_(ch_de_b5c2, ch_guo_b9fa)
#define DVB_OS_ENGLAND              _cat_(ch_ying_d3a2, ch_guo_b9fa)
#define DVB_OS_ITALY                _cat3_(ch_yi_d2e2, ch_da_b4f3, ch_li_c0fb)
#define DVB_OS_FRANCE               _cat_(ch_fa_b7a8, ch_guo_b9fa)
#define DVB_OS_SPAIN                _cat3_(ch_xi_cef7, ch_ban_b0e0, ch_ya_d1c0)
#define DVB_OS_HOLLAND              _cat_(ch_he_bac9, ch_lan_c0bc)
#define DVB_OS_AUSTRALIA            _cat4_(ch_ao_b0c4, ch_da_b4f3, ch_li_c0fb, ch_ya_d1c7)
#define DVB_OS_SINGLE_CHANNEL       _cat3_(ch_dan_b5a5, ch_pin_c6b5, ch_dian_b5e3)
#define DVB_OS_CHAN_RANGE           _cat3_(ch_duo_b6e0, ch_pin_c6b5, ch_dian_b5e3)
#define DVB_OS_MSG_BOX              DVB_OS_INFO_PAGE
#define DVB_OS_RESET_DEFAULT        _cat6_(ch_hui_bbd6, ch_fu_b8b4, ch_chu_b3f6, ch_chang_b3a7, ch_she_c9e8, ch_ding_b6a8)
#define DVB_OS_OK                   DVB_OS_PRESS_ENTER
#define DVB_OS_BOXMAN               _cat3_(ch_tui_cdc6, ch_xiang_cfe4, ch_zi_d7d3)
#define DVB_OS_BURNING_TETRIS       _cat5_(ch_e_b6ed, ch_luo_c2de, ch_si_cbb9, ch_fang_b7bd, ch_kuai_bfe9)
#define DVB_OS_HIT_RAT              _cat3_(ch_da_b4f2, ch_di_b5d8, ch_shu_caf3)
#define DVB_OS_PROG_DETAIL_INFO     _cat6_(ch_jie_bdda, ch_mu_c4bf, ch_xiang_cfea, ch_xi_cfb8, ch_xin_d0c5, ch_xi_cfa2)
#define DVB_OS_STRENGTH             _cat4_(ch_xin_d0c5, ch_hao_bac5, ch_qiang_c7bf, ch_du_b6c8)
#define DVB_OS_QUALITY              _cat4_(ch_xin_d0c5, ch_hao_bac5, ch_pin_c6b7, ch_zhi_d6ca)
#define DVB_OS_EPG                  _cat6_(ch_dian_b5e7, ch_zi_d7d3, ch_jie_bdda, ch_mu_c4bf, ch_zhi_d6b8, ch_nan_c4cf)
#define DVB_OS_EPG_INFO             _cat3_("EPG", ch_xin_d0c5, ch_xi_cfa2)
#define DVB_OS_NO_TITLE             _cat4_(ch_wu_cede, ch_jie_bdda, ch_mu_c4bf, ch_ming_c3fb)
#define DVB_OS_NO_DESCRIPTION       _cat5_(ch_wu_cede, ch_miao_c3e8, ch_shu_caf6, ch_xin_d0c5, ch_xi_cfa2)
#define DVB_OS_NO_BAD_SIGNAL        _cat8_(ch_wu_cede, ch_xin_d0c5, ch_hao_bac5, ch_huo_bbf2, ch_xin_d0c5, ch_hao_bac5, ch_tai_ccab, ch_ruo_c8f5)
#define DVB_OS_CHAN_LOCKED          _cat6_(ch_jie_bdda, ch_mu_c4bf, ch_yi_d2d1, ch_bei_b1bb, ch_suo_cbf8, ch_ding_b6a8)
#define DVB_OS_CHAN_SCRAMBLED       _cat4_(ch_shou_cad5, ch_fei_b7d1, ch_jie_bdda, ch_mu_c4bf)
#define DVB_OS_NO_TV_CHAN           _cat5_(ch_wu_cede, ch_dian_b5e7, ch_shi_cad3, ch_jie_bdda, ch_mu_c4bf)
#define DVB_OS_NO_RADIO_CHAN        _cat5_(ch_wu_cede, ch_guang_b9e3, ch_bo_b2a5, ch_jie_bdda, ch_mu_c4bf)
#define DVB_OS_NO_CHAN              _cat3_(ch_wu_cede, ch_jie_bdda, ch_mu_c4bf)
#define DVB_OS_NO_TELETEXT_INFO     _cat7_(ch_wu_cede, ch_tu_cdbc, ch_wen_cec4, ch_dian_b5e7, ch_shi_cad3, ch_xin_d0c5, ch_xi_cfa2)
#define DVB_OS_NO_BOOK_INFO         _cat5_(ch_wu_cede, ch_yu_d4a4, ch_yue_d4bc, ch_xin_d0c5, ch_xi_cfa2)
#define DVB_OS_FIRST_INSTALL        _cat6_(ch_chu_b3f5, ch_ci_b4ce, ch_an_b0b2, ch_zhuang_d7b0, ch_she_c9e8, ch_zhi_d6c3)
#define DVB_OS_START_FIR_INSTALL    _cat11_(ch_yao_d2aa, ch_jin_bdf8, ch_xing_d0d0, ch_chu_b3f5, ch_ci_b4ce, ch_an_b0b2, ch_zhuang_d7b0, ch_she_c9e8, ch_zhi_d6c3, ch_ma_c2f0, "?")
#define DVB_OS_START_AUTO_SCAN      _cat9_(ch_yao_d2aa, ch_kai_bfaa, ch_shi_cabc, ch_zi_d7d4, ch_dong_b6af, ch_sou_cbd1, ch_tai_cca8, ch_ma_c2f0, "?")
#define DVB_OS_MESSAGE              DVB_OS_INFO_PAGE
#define DVB_OS_SAVE_SCAN_RESULT     _cat9_(ch_yao_d2aa, ch_bao_b1a3, ch_cun_b4e6, ch_sou_cbd1, ch_tai_cca8, ch_jie_bde1, ch_guo_b9fb, ch_ma_c2f0, "?")
#define DVB_OS_ERASE_CHAN_LIST      _cat35_(ch_shi_cac7, ch_fou_b7f1, ch_shan_c9be, ch_chu_b3fd, ch_yi_d2d1, ch_you_d3d0, ch_jie_bdda, ch_mu_c4bf, ch_lie_c1d0, ch_biao_b1ed, "?", \
                                            ch_shi_cac7, ch_ze_d4f2, ch_geng_b8fc, ch_xin_d0c2, ch_quan_c8ab, ch_bu_b2bf, ch_lie_c1d0, ch_biao_b1ed, ",", \
                                            ch_fou_b7f1, ch_ze_d4f2, ch_tian_cced, ch_jia_bcd3, ch_xin_d0c2, ch_jie_bdda, ch_mu_c4bf, ch_dao_b5bd, \
                                            ch_xian_cfd6, ch_you_d3d0, ch_jie_bdda, ch_mu_c4bf, ch_lie_c1d0, ch_biao_b1ed, ".")
#define DVB_OS_UPDATE_CHAN_LIST     _cat12_(ch_geng_b8fc, ch_xin_d0c2, ch_jie_bdda, ch_mu_c4bf, ch_lie_c1d0, ch_biao_b1ed, ch_zhong_d6d0, ",", ch_qing_c7eb, ch_shao_c9d4, ch_hou_baf2, "...")
#define DVB_OS_MUTE                 _cat_(ch_jing_beb2, ch_yin_d2f4)
#define DVB_OS_PAUSE                _cat_(ch_zan_d4dd, ch_ting_cda3)
#define DVB_OS_INVALID              _cat3_(ch_wu_cede, ch_xiao_d0a7, ch_jian_bcfc)
#define DVB_OS_SLEEP                _cat_(ch_dai_b4fd, ch_ji_bbfa)
#define DVB_OS_ZOOM                 _cat_(ch_suo_cbf5, ch_fang_b7c5)
#define DVB_OS_STEREO               _cat3_(ch_li_c1a2, ch_ti_cce5, ch_sheng_c9f9)
#define DVB_OS_LEFT                 _cat3_(ch_zuo_d7f3, ch_sheng_c9f9, ch_dao_b5c0)
#define DVB_OS_RIGHT                _cat3_(ch_you_d3d2, ch_sheng_c9f9, ch_dao_b5c0)
#define DVB_OS_NO_CLASS             _cat3_(ch_wu_cede, ch_fen_b7d6, ch_lei_c0e0)
#define DVB_OS_ONE_CHAN             _cat6_(ch_zhi_d6bb, ch_you_d3d0, ch_yi_d2bb, ch_ge_b8f6, ch_jie_bdda, ch_mu_c4bf)
#define DVB_OS_NO_CLASS_CHAN        DVB_OS_NO_CLASS
#define DVB_OS_NOT_IN_CLASS         _cat8_(ch_bu_b2bb, ch_zai_d4da, ch_jie_bdda, ch_mu_c4bf, ch_fen_b7d6, ch_lei_c0e0, ch_zhuang_d7b4, ch_tai_ccac)
#define DVB_OS_ALREADY_IN_LIST      _cat10_(ch_dang_b5b1, ch_qian_c7b0, ch_jie_bdda, ch_mu_c4bf, ch_yi_d2d1, ch_zai_d4da, ch_dang_b5b1, ch_qian_c7b0, ch_fen_b7d6, ch_lei_c0e0)
#define DVB_OS_VERTICAL             _cat_(ch_chui_b4b9, ch_zhi_d6b1)
#define DVB_OS_HORIZONTAL           _cat_(ch_shui_cbae, ch_ping_c6bd)
#define DVB_OS_BOOK_UNBOOK          _cat12_(ch_que_c8b7, ch_ren_c8cf, ch_jian_bcfc, ch_xuan_d1a1, ch_ze_d4f1, "/", ch_qu_c8a1, ch_xiao_cffb, ch_jie_bdda, ch_mu_c4bf, ch_yu_d4a4, ch_yue_d4bc)
#define DVB_OS_PLAYING              _cat13_(ch_dang_b5b1, ch_qian_c7b0, ch_bo_b2a5, ch_fang_b7c5, ch_jie_bdda, ch_mu_c4bf, ",", ch_bu_b2bb, ch_neng_c4dc, ch_bei_b1bb, ch_yu_d4a4, ch_yue_d4bc, "!")
#define DVB_OS_CNL_BOOK             _cat7_(ch_qu_c8a1, ch_xiao_cffb, ch_jie_bdda, ch_mu_c4bf, ch_yu_d4a4, ch_yue_d4bc, "!")
#define DVB_OS_TIME_CONFLICT        _cat12_(ch_shi_cab1, ch_jian_bce4, ch_yu_d3eb, ch_xian_cfc8, ch_qian_c7b0, ch_yu_d4a4, ch_yue_d4bc, ch_shi_cab1, ch_jian_bce4, ch_chong_b3e5, ch_tu_cdbb, "!")
#define DVB_OS_BOOKED               _cat8_(ch_ci_b4cb, ch_jie_bdda, ch_mu_c4bf, ch_yi_d2d1, ch_bei_b1bb, ch_yu_d4a4, ch_yue_d4bc, "!")
#define DVB_OS_SWITCH_BOOK          _cat16_(ch_shi_cac7, ch_fou_b7f1, ch_qie_c7d0, ch_huan_bbbb, ch_dao_b5bd, ch_yu_d4a4, ch_yue_d4bc, ch_jie_bdda, ch_mu_c4bf, ch_bo_b2a5, ch_fang_b7c5, "?", ch_huo_bbf2, ch_bao_b1a3, ch_liu_c1f4, ".")
#define DVB_OS_SERVICE              _cat3_(ch_dian_b5e7, ch_shi_cad3, ch_tai_cca8)
#define DVB_OS_EVENT                _cat_(ch_jie_bdda, ch_mu_c4bf)
#define DVB_OS_START_TIME           _cat4_(ch_qi_c6f0, ch_shi_cabc, ch_shi_cab1, ch_jian_bce4)
#define DVB_OS_END_TIME             _cat4_(ch_jie_bde1, ch_shu_caf8, ch_shi_cab1, ch_jian_bce4)
#define DVB_OS_BOOK_SETTING         _cat4_(ch_yu_d4a4, ch_yue_d4bc, ch_she_c9e8, ch_ding_b6a8)
#define DVB_OS_SERVER_ID            _cat3_(ch_jie_bdda, ch_mu_c4bf, ch_hao_bac5)
#define DVB_OS_DATE                 _cat_(ch_ri_c8d5, ch_qi_c6da)
#define DVB_OS_TIME                 _cat4_(ch_kai_bfaa, ch_shi_cabc, ch_shi_cab1, ch_jian_bce4)
#define DVB_OS_DURATION             DVB_OS_END_TIME
#define DVB_OS_ATTRIBUTE            _cat_(ch_lei_c0e0, ch_xing_d0cd)
#define DVB_OS_ONCE                 _cat_(ch_yi_d2bb, ch_ci_b4ce)
#define DVB_OS_DAILY                _cat_(ch_mei_c3bf, ch_ri_c8d5)
#define DVB_OS_WEEKLY               _cat_(ch_mei_c3bf, ch_zhou_d6dc)
#define DVB_OS_ENTER_EDIT           _cat5_(ch_que_c8b7, ch_ren_c8cf, ch_jian_bcfc, ch_bian_b1e0, ch_ji_bcad)
#define DVB_OS_RL_DEL_ADD           _cat9_(ch_zuo_d7f3, ch_jian_bcfc, ch_shan_c9be, ch_chu_b3fd, ",", ch_you_d3d2, ch_jian_bcfc, ch_tian_cced, ch_jia_bcd3)
#define DVB_OS_POWER_CONTROL        _cat4_(ch_dian_b5e7, ch_yuan_d4b4, ch_guan_b9dc, ch_li_c0ed)
#define DVB_OS_ANTENNA_POWER        _cat4_(ch_tian_ccec, ch_xian_cfdf, ch_dian_b5e7, ch_yuan_d4b4)
#define DVB_OS_WARNING              _cat_(ch_jing_beaf, ch_gao_b8e6)
#define DVB_OS_EXTERNAL_POWER       _cat27_(ch_qing_c7eb, ch_que_c8b7, ch_ren_c8cf, ch_tian_ccec, ch_xian_cfdf, ch_mei_c3bb, ch_you_d3d0, ch_shi_cab9, ch_yong_d3c3, ch_wai_cde2, ch_bu_b2bf, ch_dian_b5e7, ch_yuan_d4b4, ",", \
                                            ch_fou_b7f1, ch_ze_d4f2, ch_bo_b2a5, ch_fang_b7c5, ch_qi_c6f7, ch_ke_bfc9, ch_neng_c4dc, ch_gong_b9a4, ch_zuo_d7f7, ch_bu_b2bb, ch_zheng_d5fd, ch_chang_b3a3, "!")
#define DVB_OS_ON                   ch_kai_bfaa
#define DVB_OS_OFF                  ch_guan_b9d8
#define DVB_OS_NOTHING              ch_wu_cede
#define DVB_OS_MIN                  ch_fen_b7d6
//Add Strs
#define DVB_OS_NEXT                 _cat_(ch_ji_bccc, ch_xu_d0f8)
#define DVB_OS_BACK                 _cat_(ch_fan_b7b5, ch_hui_bbd8)
#define DVB_OS_YES                  ch_shi_cac7
#define DVB_OS_NO                   ch_fou_b7f1

#endif  //end=>  #ifdef USE_NEW_SCHINESE_OSD




#endif//#ifndef __TCFONT_H

