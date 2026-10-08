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


#define Ch_yu2         "\xba"        //T:ªy S:”Ô//jiangxl 2004-7-21 11:46   
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
#define Ch_hand         "\xf1"          //T:§‚´¸S: ÷÷∏
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
#define Ch_LANG         "\r\x4a"
#define Ch_ANGLE        "\r\x4b"
#define Ch_busy1        "\r\x55"        //funnel-1
#define Ch_busy2        "\r\x56"        //funnel-2
#define Ch_43ps         "\r\x5e"
#define	Ch_dolby        "\r\x5f"

#define Ch_CDROM        "\r\x6d"        //CDROM ICON

 

#ifdef USE_THAI_OSD

#define Th_01          "\r\xe4"  //0x01  1  //thai
#define Th_02          "\r\xe5"  //0x02  2  //thai
#define Th_03          "\r\xe6"  //0x03  3  //thai
#define Th_04          "\r\xe7"  //0x04  4  //thai
#define Th_05          "\r\xe8"  //0x05  5  //thai
#define Th_06          "\r\xe9"  //0x06  6  //thai
#define Th_07          "\r\xea"  //0x07  7  //thai
#define Th_08          "\r\xeb"  //0x08  8  //thai
#define Th_09          "\r\xec"  //0x09  9  //thai
#define Th_0a          "\r\xed"  //0x0a  10 //thai
#define Th_0b          "\r\xee"  //0x0b  11 //thai
#define Th_0c          "\r\xef"  //0x0c  12 //thai
#define Th_0d          "\r\xf0"  //0x0d  13 //thai
#define Th_0e          "\r\xf1"  //0x0e  14 //thai
#define Th_0f          "\r\xf2"  //0x0f  15 //thai
#define Th_10          "\r\xf3"  //0x10  16 //thai
#define Th_11          "\r\xf4"  //0x11  17 //thai
#define Th_12          "\r\xf5"  //0x12  18 //thai
#define Th_13          "\r\xf6"  //0x13  19 //thai
#define Th_14          "\r\xf7"  //0x14  20 //thai
#define Th_15          "\r\xf8"  //0x15  21 //thai
#define Th_16          "\r\xf9"  //0x16  22 //thai
#define Th_17          "\r\xfa"  //0x17  23 //thai
#define Th_18          "\r\xfb"  //0x18  24 //thai
#define Th_19          "\r\xfc"  //0x19  25 //thai
#define Th_1a          "\r\xfd"  //0x1a  26 //thai
#define Th_1b          "\r\xfe"  //0x1b  27 //thai
#define Th_1c          "\r\xff"  //0x1c  28 //thai
                                             
                                            
#define Th_1d          "\x6c"  //0x1d  29  //thai
#define Th_1e          "\x6d"  //0x1e  30  //thai
#define Th_1f          "\x6e"  //0x1f  31  //thai
#define Th_20          "\x6f"  //0x20  32  //thai
#define Th_21          "\x70"  //0x21  33  //thai
#define Th_22          "\x71"  //0x22  34  //thai
#define Th_23          "\x73"  //0x23  35  //thai
#define Th_24          "\x74"  //0x24  36  //thai
#define Th_25          "\x75"  //0x25  37  //thai
#define Th_26          "\x76"  //0x26  38  //thai
#define Th_27          "\x77"  //0x27  39  //thai
#define Th_28          "\x78"  //0x28  40  //thai
#define Th_29          "\x79"  //0x29  41  //thai
#define Th_2a          "\x7a"  //0x2a  42  //thai
#define Th_2b          "\x7b"  //0x2b  43  //thai
#define Th_2c          "\x7c"  //0x2c  44  //thai
#define Th_2d          "\x7d"  //0x2d  45  //thai
#define Th_2e          "\x7f"  //0x2e  46  //thai
#define Th_2f          "\x80"  //0x2f  47  //thai
#define Th_30          "\x82"  //0x30  48  //thai
#define Th_31          "\x83"  //0x31  49  //thai
#define Th_32          "\x84"  //0x32  50  //thai
#define Th_33          "\x86"  //0x33  51  //thai
#define Th_34          "\x87"  //0x34  52  //thai
#define Th_35          "\x88"  //0x35  53  //thai
#define Th_36          "\x89"  //0x36  54  //thai
#define Th_37          "\x8a"  //0x37  55  //thai
#define Th_38          "\x8b"  //0x38  56  //thai
#define Th_39          "\x8c"  //0x39  57  //thai
#define Th_3a          "\x8d"  //0x3a  58  //thai
#define Th_3b          "\x8e"  //0x3b  59  //thai
#define Th_3c          "\x8f"  //0x3c  60  //thai
#define Th_3d          "\x90"  //0x3d  61  //thai
#define Th_3e          "\x91"  //0x3e  62  //thai
#define Th_3f          "\x92"  //0x3f  63  //thai
#define Th_40          "\x93"  //0x40  64  //thai
#define Th_41          "\x94"  //0x41  65  //thai
#define Th_42          "\x95"  //0x42  66  //thai
#define Th_43          "\x96"  //0x43  67  //thai
#define Th_44          "\x97"  //0x44  68  //thai
#define Th_45          "\x98"  //0x45  69  //thai
#define Th_46          "\x99"  //0x46  70  //thai
#define Th_47          "\x9a"  //0x47  71  //thai
#define Th_48          "\x9b"  //0x48  72  //thai
#define Th_49          "\x9c"  //0x49  73  //thai
#define Th_4a          "\x9d"  //0x4a  74  //thai
#define Th_4b          "\x9e"  //0x4b  75  //thai
#define Th_4c          "\x9f"  //0x4c  76  //thai
#define Th_4d          "\xa0"  //0x4d  77  //thai
#define Th_4e          "\xa1"  //0x4e  78  //thai
#define Th_4f          "\xa2"  //0x4f  79  //thai
#define Th_50          "\xa3"  //0x50  80  //thai
#define Th_51          "\xa4"  //0x51  81  //thai
#define Th_52          "\xa5"  //0x52  82  //thai
#define Th_53          "\xa6"  //0x53  83  //thai
#define Th_54          "\xa7"  //0x54  84  //thai
#define Th_55          "\xa8"  //0x55  85  //thai
#define Th_56          "\xa9"  //0x56  86  //thai
#define Th_57          "\xab"  //0x57  87  //thai
#define Th_58          "\xac"  //0x58  88  //thai
#define Th_59          "\xad"  //0x59  89  //thai
#define Th_5a          "\xae"  //0x5a  90  //thai
#define Th_5b          "\xaf"  //0x5b  91  //thai
#define Th_5c          "\xb0"  //0x5c  92  //thai
#define Th_5d          "\xb1"  //0x5d  93  //thai
#define Th_5e          "\xb2"  //0x5e  94  //thai
#define Th_5f          "\xb3"  //0x5f  95  //thai
#define Th_60          "\xb4"  //0x60  96  //thai
#define Th_61          "\xb7"  //0x61  97  //thai
#define Th_62          "\xb8"  //0x62  98  //thai
#define Th_63          "\xbb"  //0x63  99  //thai
#define Th_64          "\xbd"  //0x64  100 //thai
#define Th_65          "\xbe"  //0x65  101 //thai
#define Th_66          "\xbf"  //0x66  102 //thai
#define Th_67          "\xe0"  //0x67  103 //thai
#define Th_68          "\xe1"  //0x68  104 //thai
#define Th_69          "\xe2"  //0x69  105 //thai
#define Th_6a          "\xe3"  //0x6a  106 //thai
#define Th_6b          "\xe4"  //0x6b  107 //thai
#define Th_6c          "\xe5"  //0x6c  108 //thai
#define Th_6d          "\xe6"  //0x6d  109 //thai
#define Th_6e          "\xe7"  //0x6e  110 //thai
#define Th_6f          "\xe8"  //0x6f  111 //thai
#define Th_70          "\xe9"  //0x70  112 //thai
#define Th_71          "\xea"  //0x71  113 //thai
#define Th_72          "\xeb"  //0x72  114 //thai
#define Th_73          "\xec"  //0x73  115 //thai
#define Th_74          "\xed"  //0x74  116 //thai
#define Th_75          "\xee"  //0x75  117 //thai
#define Th_76          "\xef"  //0x76  118 //thai
#define Th_77          "\xf0"  //0x77  119 //thai
#define Th_78          "\xf2"  //0x78  120 //thai
#define Th_79          "\xf3"  //0x79  121 //thai
#define Th_7a          "\xf4"  //0x7a  122 //thai
#define Th_7b          "\xf5"  //0x7b  123 //thai
#define Th_7c          "\xf6"  //0x7c  124 //thai
#define Th_7d          "\xf8"  //0x7d  125 //thai
#define Th_7e          "\xf9"  //0x7e  126 //thai
#define Th_7f          "\xfa"  //0x7f  127 //thai
#define Th_80          "\xfb"  //0x80  128 //thai
#define Th_81          "\xfd"  //0x81  129 //thai
#define Th_82          "\xfe"  //0x82  130 //thai
                                            
#define Th_83          "\r\x11"  //0x83  131 // thai
#define Th_84          "\r\x12"  //0x84  132 // thai
#define Th_85          "\r\x13"  //0x85  133 // thai
#define Th_86          "\r\x14"  //0x86  134 // thai
#define Th_87          "\r\x15"  //0x87  135 // thai
#define Th_88          "\r\x16"  //0x88  136 // thai
#define Th_89          "\r\x17"  //0x89  137 // thai
#define Th_8a          "\r\x18"  //0x8a  138 // thai
#define Th_8b          "\r\x19"  //0x8b  139 // thai
#define Th_8c          "\r\x1b"  //0x8c  140 // thai
#define Th_8d          "\r\x1c"  //0x8d  141 // thai
#define Th_8e          "\r\x1d"  //0x8e  142 // thai
#define Th_8f          "\r\x1e"  //0x8f  143 // thai
#define Th_90          "\r\x1f"  //0x90  144 // thai
#define Th_91          "\r\x21"  //0x91  145 // thai
#define Th_92          "\r\x22"  //0x92  146 // thai
#define Th_93          "\r\x23"  //0x93  147 // thai
#define Th_94          "\r\x2a"  //0x94  148 // thai
#define Th_95          "\r\x2b"  //0x95  149 // thai
#define Th_96          "\r\x2c"  //0x96  150 // thai
#define Th_97          "\r\x30"  //0x97  151 // thai
#define Th_98          "\r\x31"  //0x98  152 // thai
#define Th_99          "\r\x32"  //0x99  153 // thai
#define Th_9a          "\r\x33"  //0x9a  154 // thai
#define Th_9b          "\r\x34"  //0x9b  155 // thai
#define Th_9c          "\r\x35"  //0x9c  156 // thai
#define Th_9d          "\r\x36"  //0x9d  157 // thai
#define Th_9e          "\r\x37"  //0x9e  158 // thai
#define Th_9f          "\r\x38"  //0x9f  159 // thai
#define Th_a0          "\r\x39"  //0xa0  160 // thai
#define Th_a1          "\r\x3a"  //0xa1  161 // thai    
#define Th_a2          "\r\x3b"  //0xa2  162 // thai
#define Th_a3          "\r\x3c"  //0xa3  163 // thai
#define Th_a4          "\r\x3d"  //0xa4  164 // thai
#define Th_a5          "\r\x3e"  //0xa5  165 // thai
#define Th_a6          "\r\x3f"  //0xa6  166 // thai
#define Th_a7          "\r\x40"  //0xa7  167 // thai

#define Ch_ban         "\r\x40"   

#ifdef ICON_REPEAT_FOLDER
#define Ch_repf         "\r\x73"  //zhuyf  2004-8-10
#endif
#endif //USE_THAI_OSD


