
#define Ch_mo           "\x01"          //T:家S:模
//#define Ch_gen          "\x02"          //T:蛤S:跟//not use
//#define Ch_dui          "\x03"          //T:癸S:对//not use
//Turkish:s=0x02
//Turkish:g=0x03

//---------------gbm's Japanese--part1/5--------/////
#if 1 //def GBM_NEW_JAPANESE
#define Ch_chu2       "\x02"          //JS:初
#define Ch_qi1       "\x03"          //JS:期
#endif//GBM_NEW_JAPANESE	
//---------------gbm's Japanese------------------/////
	
#define Ch_bi1          "\x04"          //T:ゑS:比
 
//---------------gbm's Japanese--part2/5--------/////
#if 1 //def GBM_NEW_JAPANESE
#define Ch_hua2       	"\x05"          	//JS:化
#define Ch_shi6       	"\x07"          	//JS:実
#endif//GBM_NEW_JAPANESE	
#define Ch_ta       	"\x06"          	//JS:他

//---------------gbm's Japanese------------------/////

//#define Ch_ci1          "\x05"          //T:ΩS:次//not use
//Turkish:i=0x05
 
//#define Ch_fang1        "\x06"          //T:よS:方//not use
//#define Ch_shou         "\x07"          //T:もS:手//not use
//CZECH:C//"\x06"
//CZECH:E//"\x07"
 
#define Ch_sheng2       "\x08"          //T:どS:升
#define	Ch_tui	        "\x09"          //T:癶S:退
//#define Ch_li2          "\r\x20"          //利

#define Ch_jun          "\x0b"          //T:АS:均
#define Ch_hen          "\x0c"          //T:颗S:衡



//#define Ch_chang1       "\x0d"          //T:S:长//not use 3-3-23 22:23
//CZECH:N//"\x0d"


#define Ch_huan1        "\x0e"          //T:吏S:环

#define Ch_rao          "\x0f"          //T:露S:绕
#define Ch_ge           "\x10"          //T:S:个

#define Ch_ukey         "\x11"          //#
#define N_ukey          0x11
#define Ch_rkey         "\x12"
#define N_rkey          0x12
#define Ch_dkey         "\x13"
#define N_dkey          0x13
#define Ch_music        "\x14"
#define N_music         0x14 
#define	Ch_mian	        "\x15"          //T:S:面
#define	Ch_ping	        "\x16"          //T:S:屏
#define	Ch_dan	        "\x17"          //T:虫S:单
#define	Ch_sheng        "\x18"          //T:羘S:声
#define	Ch_dao	        "\x19"          //T:笵S:道
#define	Ch_xian3        "\x1a"          //T:陪S:显
#define Ch_sao          "\x1b"          //T:苯S:扫
#define Ch_miaou        "\x1c"          //T:磞S:描
#define Ch_jiu          "\x1d"          //T:S:九
#define	Ch_dot	        "\x1e"          //_
#define N_dot           0x1e
#define Ch_shortbar     "\x1f"
#define N_shortbar      0x1f

#define Ch_space        "\x20"
 
#define Ch_xing         "\x21"          //T:┦S:性
#define Ch_chao         "\x22"          //T:禬S:超

#define Ch_gao          "\x23"          //T:蔼S:高

//#define Ch_pin1         "\x24"          //T:珇S:品
#define JCh_bian         "\x24"  		//S:?
 
//ASCII 0x25=% 
//#define Ch_zhi2         "\x26"          //T:借S:质
#define JCh_ji           "\x26"  		//S:集

//#define Ch_chang1       "\x27"          //T:S:长
//ASCII 0x27=' 
#define Ch_yue          "\x28"          //T:贾S:乐
#define Ch_ting1        "\x29"          //T:芔S:厅
//ASCII 0x2a=*
//#define NSZ             "\x2a"    
//ASCII 0x2b=+ 
#define Ch_jiao1        "\x2c"          //T:毙S:教
//ASCII 0x2d=-
//ASCII 0x2e=.
//ASCII 0x30 ~ 0x39 = 0 ~ 9
//ASCII 0x3a=: 
#define Ch_tang         "\x3b"          //T:绑S:堂
//ASCII 0x3c=<
//#define ZuoYou         "\x3C" 
#define Ch_xian1        "\x3d"          //T:瞷S:现
//ASCII 0x3e=>
//#define ShangXia         "\x3e"
//ASCII 0x3f=?
//#define SSZ              "\x3f"  
//#define Ch_yu1          "\x40"          //T:▅S:育//not use
#define Ch_dui          "\x40"          //T:癸S:对
//ASCII 0x41 ~ 0x5a = A ~ Z
//ASCII 0x5b=[
//ASCII 0x5c='\'
//ASCII 0x5d=] 
#define Ch_gu           "\x5e"          //T:S:古
//ASCII 0x5f=_

#define Ch_dir0         "\x60" 
 
#if defined(DVB_MENU_SETUP_STYLE) || defined(USE_LOWERCASE)  //sunzhh modify for lowercase 2005-4-15
#define N_longbar       0x68
//#define Ch_dir1         "\x61"
#define JCh_gu         "\r\x9f"	  		//J:gu

//#define Ch_dir2         "\x62"
//ASCII \r\xa0=b

#define Ch_dir3         "\r\xa1"
#define Ch_dir4         "\r\xa2"
//#define Ch_dir5         "\x65"//not used 3-12-3 10:14 nono
#define Ch_zhua         "\r\xa3"

//#define Ch_dir6         "\x66"          //unused
#define JCh_pu         "\r\xa4"	  		//J:pu

#define Ch_unlock       "\r\xa5"
#define	Ch_longbar      "\r\xa6"

#define Ch_dir7         "\r\xa7"
#define Ch_dir8         "\r\xa8"
#define Ch_dir9         "\r\xa9"
#define Ch_shi          "\r\xaa"          //T:ΑS:式

#define Ch_jil          "\r\xab"          //T:胯S:辑

#define Ch_di           "\r\xac"          //T:S:低
#define Ch_kai          "\r\xad"          //T:秨S:开
#define Ch_chu          "\r\xae"          //T:S:出
#define Ch_ying         "\r\xaf"          //T:璣S:英

//#define Ch_wen          "\x72"          //T:ゅS:文
//#define JCh_gu         "\x72"	  		//J:gu
//ASCII \r\xb0=r

#define Ch_zhong        "\r\xb1"          //T:いS:中
#define Ch_pin          "\r\xb2"          //T:繵S:频
#define Ch_mi           "\r\xb3"          //T:盞S:密
#define Ch_ma           "\r\xb4"          //T:絏S:码
#define Ch_ji           "\r\xb5"          //T:S:级
#define Ch_bie          "\r\xb6"          //T:S:别
#define Ch_shu4         "\r\xb7"          //T:计S:数
#define Ch_fei          "\r\xb8"          //T:獶S:非

#else//#if defined(DVB_MENU_SETUP_STYLE) || defined(USE_LOWERCASE)//sunzhh modify for lowercase 2005-4-15
//#define Ch_dir1         "\x61"
#define JCh_gu         "\x61"	  		//J:gu

//#define Ch_dir2         "\x62"
//ASCII 0x62=b

#define Ch_dir3         "\x63"
#define Ch_dir4         "\x64"
//#define Ch_dir5         "\x65"//not used 3-12-3 10:14 nono
#define Ch_zhua         "\x65"

//#define Ch_dir6         "\x66"          //unused
#define JCh_pu         "\x66"	  		//J:pu

#define Ch_unlock       "\x67"
#define	Ch_longbar      "\x68"
#define N_longbar       0x68
#define Ch_dir7         "\x69"
#define Ch_dir8         "\x6a"
#define Ch_dir9         "\x6b"
#define Ch_shi          "\x6c"          //T:ΑS:式


#define Ch_jil          "\x6d"          //T:胯S:辑

#define Ch_di           "\x6e"          //T:S:低
#define Ch_kai          "\x6f"          //T:秨S:开
#define Ch_chu          "\x70"          //T:S:出
#define Ch_ying         "\x71"          //T:璣S:英

//#define Ch_wen          "\x72"          //T:ゅS:文
//#define JCh_gu         "\x72"	  		//J:gu
//ASCII 0x72=r  

#define Ch_zhong        "\x73"          //T:いS:中
#define Ch_pin          "\x74"          //T:繵S:频
#define Ch_mi           "\x75"          //T:盞S:密
#define Ch_ma           "\x76"          //T:絏S:码
#define Ch_ji           "\x77"          //T:S:级
#define Ch_bie          "\x78"          //T:S:别
#define Ch_shu4         "\x79"          //T:计S:数
#define Ch_fei          "\x7a"          //T:獶S:非

#endif  //#if defined(DVB_MENU_SETUP_STYLE) || defined(USE_LOWERCASE)

#define Ch_pian         "\x7b"          //T:S:片
#define Ch_er           "\x7c"          //T:ㄠS:儿
#define Ch_tong         "\x7d"          //T:担S:童
//ASCII 0x71=~
#define Ch_guan         "\x7f"          //T:闽S:关
#define Ch_xian         "\x80"          //T:S:限

//---------------gbm's Japanese--part3/5--------/////
#ifdef GBM_NEW_JAPANESE
#define Ch_ting2       	"\x81"          	//JS:?
#endif//GBM_NEW_JAPANESE	
//---------------gbm's Japanese------------------/////
//#define Ch_guan1        "\x81"          //T:繻S:馆//not use
//CZECH:r//"\x81"
  
#define	Ch_shu	        "\x82"          //T:块S:输
#define	Ch_suo	        "\x83"          //T:S:索
#define	Ch_die	        "\x84"          //T:盒S:碟

//---------------gbm's Japanese--part4/5--------/////
#if 1//def GBM_NEW_JAPANESE
#define Ch_nong       	"\x85"          	//JS:濃
#endif//GBM_NEW_JAPANESE	
//---------------gbm's Japanese------------------/////
//#define Ch_ju           "\x85"          //T:粿S:剧//not use
//CZECH:s//"\x85"

#define	Ch_zi2	        "\x86"          //T:S:字
#define	Ch_liang        "\x87"          //T:秖S:量

//#define Ch_nin          "\x88"          //T:眤S:您//not use//nono 2003-8-11 13:40
#define	Ch_qing	        "\x88"        //T:叫S:请


#define	Ch_mu	        "\x89"          //T:辊S:幕
#define	Ch_mu1	        "\x8a"          //T:ヘS:目
#define	Ch_lu	        "\x8b"          //T:魁S:录
#define	Ch_yi	        "\x8c"          //T:簿S:移
#define	Ch_biao	        "\x8d"          //T:夹S:标
#define	Ch_ti1	        "\x8e"          //T:肈S:题
#define Ch_an           "\x8f"          //T:S:按
#define	Ch_she	        "\x90"          //T:砞S:设
#define	Ch_zhi5	        "\x91"          //T:竚S:置
#define	Ch_qing1        "\x92"          //T:睲S:清
#define Ch_cuo          "\x93"          //T:岿S:错
#define	Ch_bo	        "\x94"          //T:冀S:播
#define	Ch_fang	        "\x95"          //T:S:放
#define	Ch_zan	        "\x96"          //T:既S:暂
#define	Ch_ting	        "\x97"          //T:氨S:停
#define	Ch_sui	        "\x98"          //T:繦S:随
#define	Ch_ji2	        "\x99"          //T:诀S:机
#define	Ch_chu1	        "\x9a"          //T:埃S:除
#define	Ch_qu	        "\x9b"          //T:ΡS:曲
#define	Ch_huan	        "\x9c"          //T:临S:还
#define	Ch_yuan	        "\x9d"          //T:S:原
#define	Ch_shi1	        "\x9e"          //T:S:时

//#define	Ch_csh	        "\x9f"          //T:S:卡      //unused
//#define Ch_jia          "\x9f"          //T://not use//nono 2003-8-11 14:09

#define	Ch_la           "\xa0"          //T:┰S:拉
#define	Ch_sou          "\xa1"          //T:穓S:搜

//#define	Ch_sheng1       "\xa2"          //T:逞S:剩
//#define	Ch_yu	        "\xa3"          //T:S:余
#define JCh_ra         "\xa2"	  		//J:ra
#define JCh_ro         "\xa3"	  		//J:ro

#define	Ch_liu	        "\xa4"          //T:聅S:浏
#define	Ch_lan	        "\xa5"          //T:凝S:览
#define Ch_cai          "\xa6"          //T:垫S:菜
#define Ch_shun         "\xa7"          //T:抖S:顺
#define Ch_xu           "\xa8"          //T:S:序
#define Ch_nn           "\xa9"          //T:S:了
#define Ch_arrow        "\xaa"          //>>
#define	Ch_shang        "\xab"          //T:S:上
#define	Ch_xia	        "\xac"          //T:S:下
#define	Ch_zuo	        "\xad"          //T:オS:左
#define	Ch_you1	        "\xae"          //T:S:右
#define	Ch_kuai	        "\xaf"          //T:еS:快
#define	Ch_man	        "\xb0"          //T:篊S:慢
#define Ch_kuan         "\xb1"          //T:糴S:宽

//#define Ch_qnbk         "\xb2"          //T:传S:换      //unused
#define Ch_qiang        "\xb2"          //T:眏

#define	Ch_quan	        "\xb3"          //T:S:全
#define	Ch_hui	        "\xb4"          //T:S:恢
#define Ch_169          "\xb5"
#define Ch_43           "\xb6" 
#define	Ch_diao	        "\xb7"          //T:秸S:调
#define	Ch_dian	        "\xb8"          //T:筿S:电
#define Ch_dir10        "\xb9"
#define Ch_dir11        "\xba"  
//#define	Ch_si	        "\xbb"          //T:S:伺
//#define	Ch_fu2	        "\xbc"          //T:狝S:服
#define JCh_mu	         "\xbb"  		//J:mu
#define JCh_space24	         "\xbc"  		//J:space24*24
 
//#define	Ch_ruan	        "\xbd"          //T:硁S:软//not use 5-6-3 0:14
#define	Ch_e	        "\xbe"          //T:S:一
#define	Ch_zong	        "\xbf"          //T:羆S:总

#ifdef SUPPORT_MIDI//nono 4-11-9 22:46
#define Ch_lv1             "\xc0"        //律
#define Ch_xuan2             "\xc1"        //旋
#endif

//c2
//c3
//c4
//c5
//c6
//c7
//c8
//c9
//ca
//cb
//cc
//cd
//ce
//cf
//d0
//d1
//d2
//d3
//d4
//d5
//d6
//d7
//d8
//d9
//da
//db
//dc
//dd
//de
//df
   
#define	Ch_fan	        "\xe0"          //T:S:返
#define	Ch_hui1	        "\xe1"          //T:S:回
#define	Ch_bu	        "\xe2"          //T:˙S:步
#define	Ch_zhun	        "\xe3"          //T:S:准
#define	Ch_jian	        "\xe4"          //T:丁S:间
#define	Ch_zhang        "\xe5"          //T:彻S:章
#define	Ch_chong        "\xe6"          //T:S:重
#define	Ch_fu	        "\xe7"          //T:確S:复
#define Ch_yao          "\xe8"          //T:穘S:摇
#define Ch_gun          "\xe9"          //T:簎S:滚
#define	Ch_dong	        "\xea"          //T:笆S:动
#define Ch_bian         "\xeb"          //T:絪S:编
#define Ch_cheng        "\xec"          //T:祘S:程
#define Ch_xiao	        "\xed"          //T:S:消
#define Ch_jue          "\xee"          //T:里S:爵

//#define Ch_kong         "\xef"          //T:北S:控
#ifdef BBK_DVD
#define Ch_qing2        "\xef"			// S : 轻  03-10-28 21:38
#else
#define Ch_ping3         "\xef"          //T:  S:评
#endif

#define Ch_dian1        "\xf0"          //T:ㄥS:典
#define Ch_hand         "\xf1"          //T:もS:手指
#define Ch_jie1         "\xf2"          //T:钡S:接
#define Ch_shi3         "\xf3"          //T:跌S:视
#define Ch_chang        "\xf4"          //T:佰S:唱
#define Ch_zhi1         "\xf5"          //T:S:制
#define Ch_zi	        "\xf6"          //T:S:自

//---------------gbm's Japanese--part5/5--------/////
#ifdef GBM_NEW_JAPANESE
#define Ch_zhi6       	"\xf7"          	//JS:質
#endif//GBM_NEW_JAPANESE
//---------------gbm's Japanese------------------/////
#ifndef USE_CZECH_OSD
#define Ch_ton          "\xf7"          //T:硄S:通      //unused
#endif//USE_CZECH_OSD
//CZECH:Z//"\xf7"

#define Ch_shil         "\xf8"          //T:S:士
#define Ch_yong         "\xf9"          //T:ノS:用
#define Ch_liul         "\xfa"          //T:瑈S:流
#define Ch_xing1        "\xfb"          //T:︽S:行
#define Ch_arr2	        "\xfc"          //<<
#define Ch_zhi          "\xfd"          //T:ゎS:止
#define Ch_chang2       "\xfe"          //T:初S:场
#define Ch_lock         "\xff"


//Table-2

#define Ch_question     "\r\x0f"
#define Ch_rui          "\r\x10"        //锐
#define Ch_yan          "\r\x11"        //T:┑S:延
#define Ch_chi          "\r\x12"        //T:筐S:迟
#define Ch_que	        "\r\x13"        //T:S:缺
#define	Ch_sheng3       "\r\x14"        //T:S:省
#define Ch_bao          "\r\x15"        //T:玂S:保
#define Ch_hu           "\r\x16"        //T:臔S:护
#define	Ch_hun          "\r\x17"        //T:睼S:混
#define	Ch_xiang        "\r\x18"        //T:臫S:响
#define	Ch_jie	        "\r\x19"        //T:竊S:节

//---------------gbm's Japanese--table2--part1/2--------/////
#if 1//def GBM_NEW_JAPANESE
#define JCh_pso       	"\r\x1a"          	//JS:そpso
#endif//GBM_NEW_JAPANESE
//---------------gbm's Japanese-------------------------/////
//#define Ch_yuan1        "\r\x1a"        //T:蛾S:圆//not use
//CZECH:U//"\r\x1a" 

#define Ch_hua1         "\r\x1b"        //T:杠S:话
#define Ch_tong1        "\r\x1c"        //T:旦S:筒
#define Ch_jou          "\r\x1d"        //T:S:旧
#define Ch_zhi3         "\r\x1e"        //T:醇S:智
#define Ch_neng         "\r\x1f"        //T:S:能
#define Ch_yang1         "\r\x20"        //样
#define Ch_cheng1       "\r\x21"        //T:ΘS:成
#define Ch_ban          "\r\x22"        //T:S:版
#define Ch_wu1          "\r\x23"        //T:づS:勿
#define Ch_CDDA         "\r\x24"
#define Ch_VCD          "\r\x25"
#define Ch_SVCD         "\r\x26"
#define Ch_DVD          "\r\x27"
#define Ch_MP3          "\r\x28"
#define Ch_speaker      "\r\x29"
 
#if 1//def FUSS_DVD//nono 20020713
#ifdef ICON_REPEAT_FOLDER
#define Ch_repf         "\r\x73"  //zhuyf  2004-8-10
#endif
#define Ch_repx         "\r\x74"
#define Ch_rep1         "\r\x75"
#define Ch_repd         "\r\x76"
#else
#define Ch_repx         "\r\x2a"
#define Ch_rep1         "\r\x2b"
#define Ch_repd         "\r\x2c"
#endif
//#define Ch_liang2        "\r\x2a"        //T:    S:亮
//#define Ch_du2           "\r\x2b"        //T:    S:度
//#define Ch_se            "\r\x2c"        //T:    S:色

#define Ch_clock        "\r\x2e"
#define Ch_arrorR       "\r\x2f"
#define Ch_xi1          "\r\x30"        //T:╰S:系
#define Ch_tong2        "\r\x31"        //T:参 S:统
#define Ch_yu2          "\r\x32"        //T:粂 S:语
#define Ch_yan1         "\r\x33"        //T:ē S:言
#define Ch_duan         "\r\x34"        //T:狠 S:端
#define Ch_zi1          "\r\x35"        //T: S:子
#define Ch_fen          "\r\x36"        //T:だ S:分
#define Ch_li1          "\r\x37"        //T:ㄒ S:例
#define Ch_zhu          "\r\x38"        //T: S:主
#define Ch_shi2         "\r\x39"        //T:ボ S:示
#define Ch_han          "\r\x3a"        //T:簙 S:汉
#define Ch_ni           "\r\x3b"        //T:览 S:拟
#define Ch_yuan2        "\r\x3c"        //T:方 S:源
#define Ch_yang         "\r\x3d"        //T:喘 S:扬
#define Ch_qi           "\r\x3e"        //T:竟 S:器
#define	Ch_vff	        "\r\x3f"        //T:礚S:无
#define Ch_he           "\r\x40"        //T: S:合
#define Ch_xian2        "\r\x41"        //T:絬 S:线
#define Ch_lu1          "\r\x42"        //T:隔 S:路
#define Ch_zheng        "\r\x43"        //T:俱 S:整
#define Ch_zhi4         "\r\x44"        //T: S:值
#define Ch_xu1          "\r\x45"        //T:店 S:虚
#define	Ch_yin	        "\r\x46"        //T:S:音
//#define Ch_da           "\r\x46"        //大
//#define Ch_xiao1        "\r\x47"        //小
#define	Ch_jing	        "\r\x47"        //T:繰S:静
#define Ch_cang         "\r\x48"        //T:S:仓

//---------------gbm's Japanese--part2/2--------/////
#if defined(GBM_NEW_JAPANESE)&&!defined(ICON_REPEAT_FOLDER)
#define Ch_shi5				"\r\x73"          	//JS:?
#endif
//---------------gbm's Japanese------------------/////
#if 0//def FUSS_DVD//nono 20020713
#define Ch_SUBT         "\r\x73"
#else
#define Ch_SUBT         "\r\x49"
#endif
#define Ch_LANG         "\r\x4a"
#define Ch_ANGLE        "\r\x4b"
#define Ch_ri           "\r\x4c"        //T:らS:日
#define Ch_fa1          "\r\x4d"        //T:猭S:法
#define Ch_de           "\r\x4e"        //T:紈S:德
#define Ch_xi           "\r\x4f"        //T:﹁S:西
#define Ch_ban1         "\r\x50"        //T:痁S:班
#define Ch_ya           "\r\x51"        //T:S:牙
#define Ch_pu           "\r\x52"        //T:覆S:葡
#define Ch_tao          "\r\x53"        //T:靛S:萄
#define Ch_ding1        "\r\x54"        //T:S:丁
#define Ch_busy1        "\r\x55"        //funnel-1
#define Ch_busy2        "\r\x56"        //funnel-2
#define Ch_qian         "\r\x57"        //T:玡S:前
//#define	Ch_jian2        "\r\x58"        //T:ンS:件//not use 5-6-3 0:14
#define	Ch_jin	        "\r\x59"        //T:秈S:进
#define	Ch_du	        "\r\x5a"        //T:弄S:读
#define	Ch_qu3	        "\r\x5b"        //T:S:取
//#define	Ch_ci	        "\r\x5c"        //T:S:芯
#define Ch_li2          "\r\x5c"          //利//nono 5-6-2 22:21

#define	Ch_qu2	        "\r\x5d"        //T:跋S:区
#define Ch_43ps         "\r\x5e"
#define	Ch_dolby        "\r\x5f"
#define	Ch_hua	        "\r\x60"        //T:礶S:画
#define	Ch_xuan	        "\r\x61"        //T:匡S:选
#define	Ch_ze	        "\r\x62"        //T:拒S:择

//#define	Ch_shao	        "\r\x64"        //T:祔S:稍
//#define	Ch_deng	        "\r\x65"        //T:单S:等
#define	Ch_ce	        "\r\x63"        //S:测
#define	Ch_shi4	        "\r\x64"        //S:试
//#define Ch_bao2          "\r\x65"        //T:    S:饱
#define	Ch_ye	        "\r\x66"        //T:S:页
#define	Ch_li	        "\r\x67"        //T:ミS:立
#define	Ch_ti	        "\r\x68"        //T:蔨S:体
#define	Ch_wu	        "\r\x69"        //T:粇S:误
#define	Ch_du1	        "\r\x6a"        //T:S:杜
//Jeff 20020411
#define Ch_ji1          "\r\x6b"        //T:癘S:记
#define Ch_yi1          "\r\x6c"        //T:拘S:忆
#define Ch_CDROM        "\r\x6d"        //CDROM ICON
#define Ch_xiao4        "\r\x6e"        //T:S:效

#define Ch_da1       	"\r\x6f"        //S:大
#define Ch_tai          "\r\x70"        //T:篈S:态
#define Ch_fan1         "\r\x71"        //T:絛S:范
#define Ch_wei          "\r\x72"        //T:瞅S:围

// Traditional Chinese

#define TCh_ding        "\r\x77"        //T:﹚S:定

#define Ch_gong         "\r\x78"        //T:    S:功
#define Ch_ping2        "\r\x79"        //T:    S:平
#define Ch_heng         "\r\x7a"        //T:    S:衡
#define Ch_xiao2        "\r\x7b"        //T:    S:小

#define Ch_zu         "\r\x7c"        //T:    S:组
#define Ch_qun        "\r\x7d"        //T:    S:群

#ifndef USE_JAPANESE_OSD//nono 20040108
#define Ch_jiao       "\r\x7e"		//S:角
#define Ch_du3 	   "\r\x7f"			//S:度
#define Ch_long         "\r\x80"		//S:聋
#define Ch_ya1	        "\r\x81"		//S:哑
#define Ch_ren          "\r\x82"        //S:人 
#endif//#ifdef USE_JAPANESE_OSD

/*
#define Ch_liang2        "\r\x7e"        //T:    S:群獹
#define Ch_du2           "\r\x7f"        //T:    S:群
#define Ch_se            "\r\x80"        //T:    S:群︹
#define Ch_bao2          "\r\x81"        //T:    S:群埂
#define Ch_he2           "\r\x82"        //T:    S:群㎝

#define Ch_pu2			"\r\x83"		//T:	S:眯
*/

#define Ch_liang2        "\r\x2a"        //T:    S:亮
#define Ch_du2           "\r\x2b"        //T:    S:度
#define Ch_se            "\r\x2c"        //T:    S:色
#define Ch_bao2          "\r\x65"        //T:    S:饱
#define Ch_he2           "\r\x98"        //T:    S:和

#define Ch_pu2			"\r\x9a"		//T:	S:谱

#define Ch_ying1         "\r\x9d"  		//SC:影

#define Ch_suo1		"\r\x9e"		//SC:缩

#define Ch_jian3         "\r\xbf"  		//SC:键
#define Ch_ji3         "\r\xc5"  		//SC:继
#define Ch_xu2         "\r\xc9"  		//SC:续
#define JCh_ren          "\r\x8b"  		//S:人
#define JCh_dian	   "\r\xf1"  		//J:	S:点
#define JCh_chang	   "\r\xd4"  		//J: S:常
#define JCh_xiang        "\r\x89"  		//S:像
#define JCh_sru          "\r\x81"  		//S:入

#ifdef USE_JAPANESE_OSD
///////////////Japanese katakana FONT.
#define JCh_pru          "\r\x7e"  		//J:ru
#define JCh_chi          "\r\x7f"  		//S:遅
#define JCh_diao         "\r\x80"  		//S:調
//#define JCh_sru          "\r\x81"  		//S:入
#define JCh_xiao         "\r\x82"  		//S:効
#define JCh_zai   	     "\r\x83"  		//S:再
#define JCh_sheng1       "\r\x84"  		//S:生
#define JCh_tke          "\r\x85"  		//S:読
#define JCh_tru          "\r\x86"  		//S:込
#define JCh_tce          "\r\x87"  		//S:側
#define JCh_sying        "\r\x88"  		//S:映
//#define JCh_xiang        "\r\x89"  		//S:像
#define JCh_cheng        "\r\x8a"  		//S:成
//#define JCh_ren          "\r\x8b"  		//S:人
//#define JCh_bian         "\r\x8c"  		//S:?//move to table 1
//#define JCh_ji           "\r\x8d"  		//S:集//move to table 1
#define JCh_shi           "\r\x8c"  		//S:時
#define JCh_ba	         "\r\x8d"  		//J:ba
#define JCh_hui          "\r\x8e"  		//S:会
#define JCh_syuan        "\r\x8f"  		//S:元
#define JCh_dian1	     "\r\x90"  		//S:?
#define JCh_wu           "\r\x91"  		//S:无
#define JCh_kai          "\r\x92"  		//S:開
#define JCh_bi           "\r\x93"  		//S:閉
#define JCh_space        "\r\x94"  		//S:space
#define JCh_xya	         "\r\x95"  		//J:xya
#define JCh_xyu	         "\r\x96"  		//J:xya
#define JCh_xyo	         "\r\x97"  		//J:xya
//#define JCh_space24      "\r\x98"  		//J:space24*24//move to table 1
//#define Ch_he2           "\r\x98"        //T:    S:和
#define JCh_trk	         "\r\x99"  		//J:trk
//#define JCh_pu	         "\r\x9a"  		//J:pu//move to table 1
//#define Ch_pu2			"\r\x9a"		//T:	S:谱
#define JCh_ch	         "\r\x9b"  		//J:ch
#define JCh_tt		     "\r\x9c"  		//J:tt

//9d~9e:RUSSIAN letters.

#ifndef DVB1000_OSD_MENU      //sunzhh modify for lowercase 2005-4-15
                              //if use USE_JAPANESE_OSD ,please fix 
#define JCh_a          "\r\x9f"  		//J:A
#define JCh_i          "\r\xa0"  		//J:I
#define JCh_u          "\r\xa1"  		//J:U
#define JCh_e          "\r\xa2"  		//J:E
#define JCh_o          "\r\xa3"  		//J:O

#define JCh_ka         "\r\xa4"  		//J:ka
#define JCh_ki         "\r\xa5"  		//J:ki
#define JCh_ku         "\r\xa6"  		//J:ku
#define JCh_ke         "\r\xa7"  		//J:ke
#define JCh_ko         "\r\xa8"  		//J:ko

#define JCh_sa         "\r\xa9"  		//J:sa
#define JCh_si         "\r\xaa"  		//J:si
#define JCh_su         "\r\xab"  		//J:su
#define JCh_se         "\r\xac"  		//J:se
#define JCh_so         "\r\xad"  		//J:so

#define JCh_ta         "\r\xae"  		//J:ta
#define JCh_ci         "\r\xaf"  		//J:ci
#define JCh_cu         "\r\xb0"  		//J:cu
#define JCh_te         "\r\xb1"  		//J:te
#define JCh_to         "\r\xb2"  		//J:to

#define JCh_na         "\r\xb3"  		//J:na
#define JCh_ni         "\r\xb4"  		//J:ni
#define JCh_nu         "\r\xb5"  		//J:nu
#define JCh_ne         "\r\xb6"  		//J:ne
#define JCh_no         "\r\xb7"  		//J:no

#define JCh_ha         "\r\xb8"  		//J:ha

#endif  //#ifdef DVB1000_OSD_MENU      //sunzhh modify for lowercase 2005-4-15

#define JCh_hi         "\r\xb9"  		//J:hi
#define JCh_hu         "\r\xba"  		//J:hu
#define JCh_he         "\r\xbb"  		//J:he
#define JCh_ho         "\r\xbc"  		//J:ho

#define JCh_ma         "\r\xbd"  		//J:ma
#define JCh_mi         "\r\xbe"  		//J:mi
//#define JCh_mu         "\r\xbf"  		//J:mu//move to table 1
//#define Ch_jian3         "\r\xbf"  		//SC:键

#define JCh_me         "\r\xc0"  		//J:me
#define JCh_mo         "\r\xc1"  		//J:mo

#define JCh_ya         "\r\xc2"  		//J:ya
#define JCh_yu         "\r\xc3"  		//J:yu
#define JCh_yo         "\r\xc4"  		//J:yo

//#define JCh_ra         "\r\xc5"  		//J:ra//move to table 1
//#define Ch_ji3         "\r\xc5"  		//SC:继

#define JCh_ri         "\r\xc6"  		//J:ri
#define JCh_ru         "\r\xc7"  		//J:ru
#define JCh_re         "\r\xc8"  		//J:re
//#define JCh_ro         "\r\xc9"  		//J:ro//move to table 1
//#define Ch_xu2         "\r\xc9"  		//SC:续

#define JCh_wa         "\r\xca"  		//J:wa
#define JCh_cuyin      "\r\xcb"  		//J:cuyin
#define JCh_n	       "\r\xcc"  		//J:n
#define JCh_zhuoyin    "\r\xcd"  		//J:zhuoyin
#define JCh_banzhuoyin "\r\xce"  		//J:banzhuoyin

#define JCh_an		   "\r\xcf"  		//J: S:暗
#define JCh_zheng	   "\r\xd0"  		//J: S:证
#define JCh_fan		   "\r\xd1"  		//J: S:番
#define JCh_hao		   "\r\xd2"  		//J: S:号
#define JCh_yi		   "\r\xd3"  		//J: S:异
//#define JCh_chang	   "\r\xd4"  		//J: S:常
#define JCh_ben		   "\r\xd5"  		//J: S:本
#define JCh_guo		   "\r\xd6"  		//J: S:国
#define JCh_changyin   "\r\xd7"  		//J:changyin
#define JCh_han		   "\r\xd8"  		//J: S:韩

#define JCh_xe		   "\r\xd9"  		//J:e
#define JCh_xi		   "\r\xda"  		//J:i
#define JCh_xa		   "\r\xdb"  		//J:a
#define JCh_xo		   "\r\xdc"  		//J:o

#define JCh_pri		   "\r\xdd"  		//J:pri
#define JCh_pno		   "\r\xde"  		//J:pno
#define JCh_psi		   "\r\xdf"  		//J:psi
#define JCh_po		   "\r\xe0"  		//J:po
#define JCh_pci		   "\r\xe1"  		//J:pci
#define JCh_pte		   "\r\xe2"  		//J:pte
#define JCh_pku		   "\r\xe3"  		//J:pku
#define JCh_pta		   "\r\xe4"  		//J:pta
#define JCh_psa		   "\r\xe5"  		//J:psa
#define JCh_pi		   "\r\xe6"  		//J:pi
#define JCh_poo		   "\r\xe7"  		//J:poo
#define JCh_pra		   "\r\xe8"  		//J:pra
#define JCh_pna		   "\r\xe9"  		//J:pna

#define JCh_zao		   "\r\xea"  		//J:	S:早
#define JCh_dai		   "\r\xeb"  		//J:	S:待
#define JCh_qie		   "\r\xec"  		//J:	S:切
#define JCh_song	   "\r\xed"  		//J:	S:送
#define JCh_ze		   "\r\xee"  		//J:	S:択
#define JCh_hci		   "\r\xef"  		//J:	S:次
#define JCh_li		   "\r\xf0"  		//J:	S:戾
//#define JCh_dian	   "\r\xf1"  		//J:	S:点
#define JCh_shao	   "\r\xf2"  		//J:	S:少
#define JCh_zhong	   "\r\xf3"  		//J:	S:終
#define JCh_le		   "\r\xf4"  		//J:	S:了
#define JCh_li2		   "\r\xf5"  		//J:	S:力
#define JCh_hua		   "\r\xf6"  		//J:	S:画
#define JCh_shu        "\r\xf7"        	//T:计	S:数
#define JCh_biao       "\r\xf8"        	//T:	S:表
#define JCh_sheng      "\r\xf9"        	//T:	S:声

#define TCh_xuan        "\r\xfa"        //T:匡S:选
#define TCh_dian        "\r\xfb"        //T:筿S:电
#define TCh_yu          "\r\xfc"        //T:粂S:语
#define TCh_she         "\r\xfd"        //T:砞S:设
#define TCh_chi         "\r\xfe"        //T:筐S:迟
#define TCh_fu          "\r\xff"        //T:確S:复

////////////////Japanese katakana FONT.
#endif//#ifdef USE_JAPANESE_OSD

#if defined(BBK_DVD)||defined(USE_CHINESE_IN_JPEG_MODE) //yaowh add 05-01-04
#define Ch_ci2          "\r\x9f"  		//S:此
#define Ch_yi2          "\r\xa0"  		//S:已
#define Ch_jiang          "\r\xa1"  	//S:将
#define Ch_hou         "\r\xa2"  		//S:后
#define Ch_zhuan        "\r\xa3"  		//S:专
#define Ch_ye1           "\r\xa4"  		//S:业
#define Ch_you2         "\r\xa5"        //S:由
#define Ch_tu  		    "\r\xa6"        //S:图
#define Ch_zhi7		    "\r\xa7"        //S:至
#define Ch_ceng  		"\r\xa8"        //S:层
#define Ch_zhan 		"\r\xa9"        //S:展
#define Ch_zheng1   	"\r\xaa"        //S:正
#define Ch_zhou     	"\r\xab"        //S:周
#define Ch_xiang2   	"\r\xac"        //S:向
#define Ch_si2        	"\r\xad"        //S:四
#define Ch_miao1       	"\r\xae"        //S:秒
#define Ch_xuan1  		"\r\xaf"        //S:旋
#define Ch_zhuan1  		"\r\xb0"        //S:转
#define Ch_fan2  		"\r\xb1"        //S:翻
#define Ch_que1         "\r\xb2"        //S:确
#define Ch_ren1         "\r\xb3"        //S:认 
#define Ch_xiu          "\r\xb4"        //S:修
#define Ch_gai          "\r\xb5"        //S:改
#define Ch_jiu2         "\r\xb6"        //S:旧
#define Ch_xin2         "\r\xb7"        //S:新
#endif

#ifdef NINTAUS_OSD_STR
#define Ch_fan2          "\r\x9f"   	//翻
#define Ch_tu          "\r\xa0"   	//图
#define Ch_xuan1          "\r\xa1"  	//旋 
#define Ch_you2         "\r\xa2"    	//由
#define Ch_zhan            "\r\xa3"     //展
#define Ch_zhi7          "\r\xa4"      	//至
#define Ch_zhuan1         "\r\xa5"      //转
#define Ch_xiang2   	   "\r\xa6"     //向
#define Ch_ceng  	"\r\xa7"           //成
#define Ch_jin8           "\r\xa8"        //金
#define Ch_zheng1           "\r\xa9"    //正
#define Ch_si2           "\r\xaa"             //四
#define Ch_zhou          "\r\xab"          //周
#define Ch_jing2          "\r\xac"         //镜
#define Ch_bei             "\r\xad"     //被
#define Ch_ci3 		   "\r\xae"     //此
#define Ch_miao3           "\r\xaf"     //秒
#define Ch_nei		   "\r\xb0"     //内
#define Ch_yi3		   "\r\xb1"     //已
#define Ch_yu5		   "\r\xb2"     //于

#define Ch_zhu1          "\r\xb3"         //逐
#define Ch_wu6             "\r\xb4"     //误
#define Ch_que3            "\r\xb5"      //确
#define Ch_zhi8         "\r\xb6"
#endif
#define Ch_lv2           "\r\xc5"          //率
#ifdef SHOW_MP4_INIT_STR  //wangwei-2004/4/28
#define Ch_shi8         "\r\xc7"  	//J:	S:始
#endif


