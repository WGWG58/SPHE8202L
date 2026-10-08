/************************************************************************/

//CZECH:N//"\x0d"
#define Ch_ukey         "\x11"          //#
#define N_ukey          0x11
#define Ch_rkey         "\x12"
#define N_rkey          0x12
#define Ch_dkey         "\x13"
#define N_dkey          0x13
#define Ch_music        "\x14"
#define N_music         0x14
#define	Ch_dot	        "\x1e"          //_
#define N_dot           0x1e
#define Ch_shortbar     "\x1f"
#define N_shortbar      0x1f

#define Ch_space        "\x20"

//ASCII 0x25=%
//ASCII 0x27='
//ASCII 0x2a=*
//ASCII 0x2b=+
//ASCII 0x2d=-
//ASCII 0x2e=.
//ASCII 0x30 ~ 0x39 = 0 ~ 9
//ASCII 0x3a=:
//ASCII 0x3c=<
//ASCII 0x3e=>
//ASCII 0x3f=?
//ASCII 0x41 ~ 0x5a = A ~ Z
//ASCII 0x5b=[
//ASCII 0x5c='\'
//ASCII 0x5d=]
//ASCII 0x5f=_

#define Ch_dir0         "\x60"
#define Ch_dir1         "\x61"
#define Ch_dir2         "\x62"
#define Ch_dir3         "\x63"
#define Ch_dir4         "\x64"
#define Ch_dir5         "\x65"
#define Ch_unlock       "\x67"
#define	Ch_longbar      "\x68"
#define N_longbar       0x68
#define Ch_dir7         "\x69"
#define Ch_dir8         "\x6a"
#define Ch_dir9         "\x6b"

#define JCh_gu         "\x72"	  		//J:gu
//ASCII 0x71=~
//CZECH:r				//"\x81"

//CZECH:s				//"\x85"

#define Ch_arrow        "\xaa"          //>>
#define Ch_169          "\xb5"
#define Ch_43           "\xb6"
#define Ch_dir10        "\xb9"
#define Ch_dir11        "\xba"
#define JCh_space24	    "\xbc"  		//J:space24*24


//c0
//c1
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
#define Ch_hand         "\xf1"          //T:もS:手指
//CZECH:Z				//"\xf7"
#define Ch_arr2	        "\xfc"          //<<
#define Ch_lock         "\xff"


//////////////////----------------Table-2
#define Ch_question     "\r\xf"
//CZECH:U				//"\r\x1a"
#define Ch_CDDA         "\r\x24"
#define Ch_VCD          "\r\x25"
#define Ch_SVCD         "\r\x26"
#define Ch_DVD          "\r\x27"
#define Ch_MP3          "\r\x28"
#define Ch_speaker      "\r\x29"

#if 1
#define Ch_repx         "\r\x74"
#define Ch_rep1         "\r\x75"
#define Ch_repd         "\r\x76"
#else
#define Ch_repx         "\r\x2a"
#define Ch_rep1         "\r\x2b"
#define Ch_repd         "\r\x2c"
#endif

#define Ch_clock        "\r\x2e"
#define Ch_arrorR       "\r\x2f"
#ifdef FUSS_DVD//nono 20020713
#define Ch_SUBT         "\r\x73"
#else
#define Ch_SUBT         "\r\x49"
#endif
#define Ch_repf         "\r\x73"       //JIANGXL 2004-9-23 14:35
#define Ch_LANG         "\r\x4a"
#define Ch_ANGLE        "\r\x4b"
#define Ch_busy1        "\r\x55"        //funnel-1
#define Ch_busy2        "\r\x56"        //funnel-2
#define Ch_43ps         "\r\x5e"
#define	Ch_dolby        "\r\x5f"

#define Ch_CDROM        "\r\x6d"        //CDROM ICON




#ifdef USE_JAPANESE_OSD
///////////////Japanese katakana FONT.
#define JCh_pru          "\r\x7e"  		//J:ru
#define JCh_chi          "\r\x7f"  		//S:遅
#define JCh_diao         "\r\x80"  		//S:調
#define JCh_sru          "\r\x81"  		//S:入
#define JCh_xiao         "\r\x82"  		//S:効
#define JCh_zai   	     "\r\x83"  		//S:再
#define JCh_sheng1       "\r\x84"  		//S:生
#define JCh_tke          "\r\x85"  		//S:読
#define JCh_tru          "\r\x86"  		//S:込
#define JCh_tce          "\r\x87"  		//S:側
#define JCh_sying        "\r\x88"  		//S:映
#define JCh_xiang        "\r\x89"  		//S:像
#define JCh_cheng        "\r\x8a"  		//S:成
#define JCh_ren          "\r\x8b"  		//S:人
//#define JCh_bian         "\r\x8c"  		//S:編//move to table 1
//#define JCh_ji           "\r\x8d"  		//S:集//move to table 1
#define JCh_shi           "\r\x8c"  		//S:時
#define JCh_ba	         "\r\x8d"  		//J:ba
#define JCh_hui          "\r\x8e"  		//S:会
#define JCh_syuan        "\r\x8f"  		//S:元
#define JCh_dian1	     "\r\x90"  		//S:電
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
#define JCh_chang	   "\r\xd4"  		//J: S:常
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
#define JCh_dian	   "\r\xf1"  		//J:	S:点
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

#ifdef USE_KOREAN_OSD

#define KCh_01          "\r\xe4"  //0x01  1
#define KCh_02          "\r\xe5"  //0x02  2
#define KCh_03          "\r\xe6"  //0x03  3
#define KCh_04          "\r\xe7"  //0x04  4
#define KCh_05          "\r\xe8"  //0x05  5
#define KCh_06          "\r\xe9"  //0x06  6
#define KCh_07          "\r\xea"  //0x07  7
#define KCh_08          "\r\xeb"  //0x08  8
#define KCh_09          "\r\xec"  //0x09  9
#define KCh_0a          "\r\xed"  //0x0a  10
#define KCh_0b          "\r\xee"  //0x0b  11
#define KCh_0c          "\r\xef"  //0x0c  12
#define KCh_0d          "\r\xf0"  //0x0d  13
#define KCh_0e          "\r\xf1"  //0x0e  14
#define KCh_0f          "\r\xf2"  //0x0f  15
#define KCh_10          "\r\xf3"  //0x10  16
#define KCh_11          "\r\xf4"  //0x11  17
#define KCh_12          "\r\xf5"  //0x12  18
#define KCh_13          "\r\xf6"  //0x13  19
#define KCh_14          "\r\xf7"  //0x14  20
#define KCh_15          "\r\xf8"  //0x15  21
#define KCh_16          "\r\xf9"  //0x16  22
#define KCh_17          "\r\xfa"  //0x17  23
#define KCh_18          "\r\xfb"  //0x18  24
#define KCh_19          "\r\xfc"  //0x19  25
#define KCh_1a          "\r\xfd"  //0x1a  26
#define KCh_1b          "\r\xfe"  //0x1b  27
#define KCh_1c          "\r\xff"  //0x1c  28


#define KCh_1d          "\x6c"  //0x1d  29
#define KCh_1e          "\x6d"  //0x1e  30
#define KCh_1f          "\x6e"  //0x1f  31
#define KCh_20          "\x6f"  //0x20  32
#define KCh_21          "\x70"  //0x21  33
#define KCh_22          "\x71"  //0x22  34
#define KCh_23          "\x73"  //0x23  35
#define KCh_24          "\x74"  //0x24  36
#define KCh_25          "\x75"  //0x25  37
#define KCh_26          "\x76"  //0x26  38
#define KCh_27          "\x77"  //0x27  39
#define KCh_28          "\x78"  //0x28  40
#define KCh_29          "\x79"  //0x29  41
#define KCh_2a          "\x7a"  //0x2a  42
#define KCh_2b          "\x7b"  //0x2b  43
#define KCh_2c          "\x7c"  //0x2c  44
#define KCh_2d          "\x7d"  //0x2d  45
#define KCh_2e          "\x7f"  //0x2e  46
#define KCh_2f          "\x80"  //0x2f  47
#define KCh_30          "\x82"  //0x30  48
#define KCh_31          "\x83"  //0x31  49
#define KCh_32          "\x84"  //0x32  50
#define KCh_33          "\x86"  //0x33  51
#define KCh_34          "\x87"  //0x34  52
#define KCh_35          "\x88"  //0x35  53
#define KCh_36          "\x89"  //0x36  54
#define KCh_37          "\x8a"  //0x37  55
#define KCh_38          "\x8b"  //0x38  56
#define KCh_39          "\x8c"  //0x39  57
#define KCh_3a          "\x8d"  //0x3a  58
#define KCh_3b          "\x8e"  //0x3b  59
#define KCh_3c          "\x8f"  //0x3c  60
#define KCh_3d          "\x90"  //0x3d  61
#define KCh_3e          "\x91"  //0x3e  62
#define KCh_3f          "\x92"  //0x3f  63
#define KCh_40          "\x93"  //0x40  64
#define KCh_41          "\x94"  //0x41  65
#define KCh_42          "\x95"  //0x42  66
#define KCh_43          "\x96"  //0x43  67
#define KCh_44          "\x97"  //0x44  68
#define KCh_45          "\x98"  //0x45  69
#define KCh_46          "\x99"  //0x46  70
#define KCh_47          "\x9a"  //0x47  71
#define KCh_48          "\x9b"  //0x48  72
#define KCh_49          "\x9c"  //0x49  73
#define KCh_4a          "\x9d"  //0x4a  74
#define KCh_4b          "\x9e"  //0x4b  75
#define KCh_4c          "\x9f"  //0x4c  76
#define KCh_4d          "\xa0"  //0x4d  77
#define KCh_4e          "\xa1"  //0x4e  78
#define KCh_4f          "\xa2"  //0x4f  79
#define KCh_50          "\xa3"  //0x50  80
#define KCh_51          "\xa4"  //0x51  81
#define KCh_52          "\xa5"  //0x52  82
#define KCh_53          "\xa6"  //0x53  83
#define KCh_54          "\xa7"  //0x54  84
#define KCh_55          "\xa8"  //0x55  85
#define KCh_56          "\xa9"  //0x56  86
#define KCh_57          "\xab"  //0x57  87
#define KCh_58          "\xac"  //0x58  88
#define KCh_59          "\xad"  //0x59  89
#define KCh_5a          "\xae"  //0x5a  90
#define KCh_5b          "\xaf"  //0x5b  91
#define KCh_5c          "\xb0"  //0x5c  92
#define KCh_5d          "\xb1"  //0x5d  93
#define KCh_5e          "\xb2"  //0x5e  94
#define KCh_5f          "\xb3"  //0x5f  95
#define KCh_60          "\xb4"  //0x60  96
#define KCh_61          "\xb7"  //0x61  97
#define KCh_62          "\xb8"  //0x62  98
#define KCh_63          "\xbb"  //0x63  99
#define KCh_64          "\xbd"  //0x64  100
#define KCh_65          "\xbe"  //0x65  101
#define KCh_66          "\xbf"  //0x66  102
#define KCh_67          "\xe0"  //0x67  103
#define KCh_68          "\xe1"  //0x68  104
#define KCh_69          "\xe2"  //0x69  105
#define KCh_6a          "\xe3"  //0x6a  106
#define KCh_6b          "\xe4"  //0x6b  107
#define KCh_6c          "\xe5"  //0x6c  108
#define KCh_6d          "\xe6"  //0x6d  109
#define KCh_6e          "\xe7"  //0x6e  110
#define KCh_6f          "\xe8"  //0x6f  111
#define KCh_70          "\xe9"  //0x70  112
#define KCh_71          "\xea"  //0x71  113
#define KCh_72          "\xeb"  //0x72  114
#define KCh_73          "\xec"  //0x73  115
#define KCh_74          "\xed"  //0x74  116
#define KCh_75          "\xee"  //0x75  117
#define KCh_76          "\xef"  //0x76  118
#define KCh_77          "\xfo"  //0x77  119
#define KCh_78          "\xf2"  //0x78  120
#define KCh_79          "\xf3"  //0x79  121
#define KCh_7a          "\xf4"  //0x7a  122
#define KCh_7b          "\xf5"  //0x7b  123
#define KCh_7c          "\xf6"  //0x7c  124
#define KCh_7d          "\xf8"  //0x7d  125
#define KCh_7e          "\xf9"  //0x7e  126
#define KCh_7f          "\xfa"  //0x7f  127
#define KCh_80          "\xfb"  //0x80  128
#define KCh_81          "\xfd"  //0x81  129
#define KCh_82          "\xfe"  //0x82  130

#define KCh_83          "\r\x11"  //0x83  131
#define KCh_84          "\r\x12"  //0x84  132
#define KCh_85          "\r\x13"  //0x85  133
#define KCh_86          "\r\x14"  //0x86  134
#define KCh_87          "\r\x15"  //0x87  135
#define KCh_88          "\r\x16"  //0x88  136
#define KCh_89          "\r\x17"  //0x89  137
#define KCh_8a          "\r\x18"  //0x8a  138
#define KCh_8b          "\r\x19"  //0x8b  139
#define KCh_8c          "\r\x1b"  //0x8c  140
#define KCh_8d          "\r\x1c"  //0x8d  141
#define KCh_8e          "\r\x1d"  //0x8e  142
#define KCh_8f          "\r\x1e"  //0x8f  143
#define KCh_90          "\r\x1f"  //0x90  144
#define KCh_91          "\r\x21"  //0x91  145
#define KCh_92          "\r\x22"  //0x92  146
#define KCh_93          "\r\x23"  //0x93  147
#define KCh_94          "\r\x2a"  //0x94  148
#define KCh_95          "\r\x2b"  //0x95  149
#define KCh_96          "\r\x2c"  //0x96  150
#define KCh_97          "\r\x30"  //0x97  151
#define KCh_98          "\r\x31"  //0x98  152
#define KCh_99          "\r\x32"  //0x99  153
#define KCh_9a          "\r\x33"  //0x9a  154
#define KCh_9b          "\r\x34"  //0x9b  155
#define KCh_9c          "\r\x35"  //0x9c  156
#define KCh_9d          "\r\x36"  //0x9d  157
#define KCh_9e          "\r\x37"  //0x9e  158
#define KCh_9f          "\r\x38"  //0x9f  159
#define KCh_a0          "\r\x39"  //0xa0  160
#define KCh_a1          "\r\x3a"  //0xa1  161
#define KCh_a2          "\r\x3b"  //0xa2  162
#define KCh_a3          "\r\x3c"  //0xa3  163
#define KCh_a4          "\r\x3d"  //0xa4  164
#define KCh_a5          "\r\x3e"  //0xa5  165
#define KCh_a6          "\r\x3f"  //0xa6  166
#define KCh_a7          "\r\x40"  //0xa7  167
#define KCh_a8          "\r\x41"  //0xa8  168
#define KCh_a9          "\r\x42"  //0xa9  169
#define KCh_aa          "\r\x43"  //0xaa  170
#define KCh_ab          "\r\x44"  //0xab  171
#define KCh_ac          "\r\x45"  //0xac  172
#define KCh_ad          "\r\x46"  //0xad  173
#define KCh_ae          "\r\x47"  //0xae  174
#define KCh_af          "\r\x48"  //0xaf  175
#define KCh_b0          "\r\x4c"  //0xb0  176
#define KCh_b1          "\r\x4d"  //0xb1  177
#define KCh_b2          "\r\x4e"  //0xb2  178
#define KCh_b3          "\r\x4f"  //0xb3  179
#define KCh_b4          "\r\x50"  //0xb4  180
#define KCh_b5          "\r\x51"  //0xb5  181
#define KCh_b6          "\r\x52"  //0xb6  182
#define KCh_b7          "\r\x53"  //0xb7  183
#define KCh_b8          "\r\x54"  //0xb8  184
#define KCh_b9          "\r\x57"  //0xb9  185
#define KCh_ba          "\r\x58"  //0xba  186
#define KCh_bb          "\r\x59"  //0xbb  187
#define KCh_bc          "\r\x5a"  //0xbc  188
#define KCh_bd          "\r\x5b"  //0xbd  189
#define KCh_be          "\r\x5c"  //0xbe  190
#define KCh_bf          "\r\x5d"  //0xbf  191
#define KCh_c0          "\r\x60"  //0xc0  192
#define KCh_c1          "\r\x61"  //0xc1  193
#define KCh_c2          "\r\x62"  //0xc2  194
#define KCh_c3          "\r\x63"  //0xc3  195
#define KCh_c4          "\r\x64"  //0xc4  196
#endif 


