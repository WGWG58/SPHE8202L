#ifndef __OSD_STR_H
#define __OSD_STR_H

#include "user_init.h"

const char *const osd_err_str[N_OSD_LANGS][3]={

#ifdef USE_ENGLISH_OSD
//English
{
        "INPUT PASSWD",               //0     T:岿粇        S:级别错误              //
        "WRONG REGION",               //1     T:跋絏岿粇        S:区码错误              //
        "FLASH ID ERR",               //2     T:FLASH ID ぃ才   S:FLASH ID 不符         //
},
#endif

#ifdef USE_SCHINESE_OSD
//Simplied Chinese
{
        OS_PARENTAL_ERR,              //0     T:岿粇        S:级别错误              //
        OS_REGION_ERR,                //1     T:跋絏岿粇        S:区码错误              //
        "FLASH ID ERR",               //2     T:FLASH ID ぃ才   S:FLASH ID 不符         //
},
#endif

#ifdef USE_TCHINESE_OSD
//Traditional Chinese
{
        TOS_PARENTAL_ERR,             //0     T:岿粇        S:级别错误              //
        TOS_REGION_ERR,               //1     T:跋絏岿粇        S:区码错误              //
        "FLASH ID ERR",               //2     T:FLASH ID ぃ才   S:FLASH ID 不符         //
},
#endif

#ifdef USE_GERMAN_OSD
//German
{
        "EINGABEKODE",      //"KENNWORT EINGEBEN",          //0     T:岿粇      S:级别错误//
        "FALSCHE REGION",   //"UNG\x0dcLTIGE REGION",       //1     T:跋絏岿粇      S:区码错误 //
        "FLASH ID FEHLER",  //"FLASH ID ERR",               //2     T:FLASH ID ぃ才 S:FLASH ID 不符//
},
#endif

#ifdef USE_SPANISH_OSD
//Spanish
{
        "INGRESE SU CONTRASE\xd1""A",//="INPUT PASSWD", //0     T:岿粇        S:级别错误                  //
        "REGI\xd3""N EQUIVOCADA",//="WRONG REGION", //1     T:跋絏岿粇        S:区码错误      //
        "FLASH ID ERR",               //2     T:FLASH ID ぃ才   S:FLASH ID 不符                               //
},
#endif

#ifdef USE_FRENCH_OSD
//French
{
        "ERREUR DE DEGR\xc9",       //"INPUT PASSWD",               //0     T:岿粇      S:级别错误              //
        "ERREUR DE R\xc9GION",      //"WRONG REGION",               //1     T:跋絏岿粇      S:区码错误              //
        "FLASH ID ERREUR",      //"FLASH ID ERR",               //2     T:FLASH ID ぃ才 S:FLASH ID 不符         //
},
#endif

#ifdef USE_PORTUGUESE_OSD
//Portuguese
{
        "INTRODUZIR C""\xd3""DIGO",//"INPUT PASSWD",               //0     T:岿粇       S:级别错误              //
        "REGI""\xc3""O ERRADA",//"WRONG REGION",               //1     T:跋絏岿粇       S:区码错误              //
        "INDICADOR DE ERRO",//"FLASH ID ERR",               //2     T:FLASH ID ぃ才 S:FLASH ID 不符         //
},
#endif

#ifdef USE_LATIN_OSD
//Latin
{
        "INPUT PASSWD",               //0     T:岿粇        S:级别错误              //
        "WRONG REGION",               //1     T:跋絏岿粇        S:区码错误              //
        "FLASH ID ERR",               //2     T:FLASH ID ぃ才   S:FLASH ID 不符         //
},
#endif
#ifdef USE_ITALIAN_OSD
//Italian
{
        #ifndef HUAJIA_DVD
        "LIVELLO SBAGLIATO",        //"INPUT PASSWD",               //0     T:岿粇      S:级别错误              //
        #else
        "IMMISSIONE PASSWORD",//"LIVELLO SBAGLIATO",        //"INPUT PASSWD",               //0     T:岿粇      S:级别错误              //
        #endif
        "REGIONE SBAGLIATA",        //"WRONG REGION",               //1     T:跋絏岿粇      S:区码错误              //
        "ERRORE FLASH ID",      //"FLASH ID ERR",               //2     T:FLASH ID ぃ才 S:FLASH ID 不符         //
},
#endif

#ifdef USE_JAPANESE_OSD
//Japanese
{
        JOS_PARENTAL_ERR,           //"INPUT PASSWD",               //0     T:岿粇      S:级别错误              //
        JOS_REGION_ERR,             //"WRONG REGION",               //1     T:跋絏岿粇      S:区码错误              //
        "FLASH ID ERR",             //2     T:FLASH ID ぃ才 S:FLASH ID 不符         //
},
#endif

#ifdef USE_RUSSIAN_OSD
//Russian
{
        #ifdef RUSSIAN_FIX_HJ
        "\r\x88""\r\x88""\r\x8e""\r\x90""\r\x8b""\r\x8a ""\r\x8c""\r\x8e""\r\x8f""\r\x9e",//"INPUT PASSWD",               //0     T:岿粇	    S:级别错误              //
		"\r\x8e""\r\x93""\r\x86""\r\x81""\r\x96""\r\x8a"" ""\r\x8c""\r\x98""\r\x99""\r\x86""\r\x8e""\r\x9d",//"WRONG REGION",               //1     T:跋絏岿粇	    S:区码错误              //
        #else
        "\r\x8b""\r\x8a""\r\x8c. ""\r\x90""\r\x8f""\r\x9e ""\r\x88""\r\x82""\r\x8e. ""\r\x88 ""\r\x87""\r\x86""\r\x87.",//"INPUT PASSWD",               //0     T:岿粇	    S:级别错误              //
        "\r\x9d""\r\x98""\r\x88""\r\x98. ""\r\x8e""\r\x81""\r\x8f""\r\x8a""\r\x87.",//"WRONG REGION",               //1     T:跋絏岿粇	    S:区码错误              //
        #endif
        
        "FLASH ID ERR",               //2     T:FLASH ID ぃ才	S:FLASH ID 不符         //
},
        #endif
        
#ifdef USE_HEBRAIC_OSD
{
          "\r\x85""\r\x8c""\r\x8f""\r\x87""\r\x8f""\r\x8d ""\r\x84""\r\x85",//"INPUT PASSWD",               //0     T:岿粇    S:级别错误              //
	
		"\r\x8d""\r\x83""\r\x89""\r\x8e""\r\x7e""\r\x8a"" ""\r\x96""\r\x83""\r\x84""\r\x7e",//"WRONG REGION",               //1     T:跋絏岿粇	    S:区码错误              //
         
        "FLASH ID ERR",               //2     T:FLASH ID ぃ才	S:FLASH ID 不符         //*/
},
#endif

// HEBRAIC_OSD zhuyf add   2004-05-26
#ifdef USE_ROMANIAN_OSD
//Romanian
{
        "INDRODUCETI PAROLA",       //"INPUT PASSWD"                //0    T:岿粇       S:级别错误              //
        "EROARE DE REGIUNE",        //"WRONG REGION"                //1     T:跋絏岿粇      S:区码错误              //
        "FLASH ID ERR",                 //"INDICATOR DE EROARE"="FLASH ID ERR", //2     T:FLASH ID ぃ才 S:FLASH ID 不符         //
},
#endif

#ifdef USE_TURKISH_OSD
//Turkish
{
        "\x002""\x005""FRE G""\x005""R""\x005""\x002""\x005",       //"INPUT PASSWD"                //0    T:岿粇       S:级别错误              //
        "YANLI""\x002"" B""\xd6""LGE",                              //"WRONG REGION"                //1     T:跋絏岿粇      S:区码错误              //
        "FLASH ID",                                                 //"FLASH ID ERR",               //2     T:FLASH ID ぃ才 S:FLASH ID 不符         //
},
#endif

#ifdef USE_DUTCH_OSD
//Dutch
{
        "VOER WACHTWOORD IN",       //"INPUT PASSWD",               //0     T:岿粇      S:级别错误              //
        "VERKEERDE REGIO",          //"WRONG REGION",               //1     T:跋絏岿粇      S:区码错误              //
        "FLASH ID ERR",                                             //2     T:FLASH ID ぃ才 S:FLASH ID 不符         //
},
#endif

#ifdef USE_SWEDISH_OSD
//Swedish
{
        "SL""\xc5" "IN L""\xd6""SEN",       //"INPUT PASSWD",               //0     T:岿粇      S:级别错误              //
        "FEL REGION",                           //"WRONG REGION",               //1     T:跋絏岿粇      S:区码错误              //
        "FLASH ID ERR",                                             //2     T:FLASH ID ぃ才 S:FLASH ID 不符         //
},
#endif

#ifdef USE_CZECH_OSD
//Czech
{
        "VLO""\xf7""TE HESLO",      //"INPUT PASSWD",               //0     T:岿粇      S:级别错误              //
        "JINY REGION",                          //"WRONG REGION",               //1     T:跋絏岿粇      S:区码错误              //
        "FLASH ID ERR",                                             //2     T:FLASH ID ぃ才 S:FLASH ID 不符         //
},
#endif

#ifdef USE_KOREAN_OSD
//KOREAN
{
        KOS_PARENTAL_ERR,              //0     S:级别错误              //
        KOS_REGION_ERR,                //1     S:区码错误              //
        "FLASH ID ERR",               //2     S:FLASH ID 不符         //
},
#endif
 
#ifdef USE_DANISH_OSD
//DANISH
{
        "TILF""\xd8""R.""""KODE.",              //0     S:级别错误              //
        "FORKERT STR""\xd8""G",                //1     S:区码错误              //
        "FLASH ID ERR",               //2     S:FLASH ID 不符         //
},
#endif

//wsf add engelsk language 3-12-2 16:28
#ifdef USE_NORWAY_OSD
//Norwegian 
{
        "INNTASTE PASSCODE",               //0     T:岿粇       S:级别错误              //
        "FEILAKTIG REGION",               //1     T:跋絏岿粇        S:区码错误              //
        "FLASH ID ERR",               //! 3-12-1 23:40 2     T:FLASH ID ぃ才    S:FLASH ID 不符         //
},
#endif

#ifdef USE_POLISH_OSD
    //Poish
{
        "WPISZ HA""\r\a3""S",               //0     T:岿粇      S:级别错误              //
        "Z""\r\a3""Y REGION",               //1     T:跋絏岿粇      S:区码错误              //
        "FLASH_ID ERR",               //2     T:FLASH ID ぃ才   S:FLASH ID 不符         //
},
#endif
#ifdef USE_THAI_OSD//jxlan
//THAI 
 {
        "IN PASSWD",               //0     T:岿粇       S:级别错误              //
        "WRONG REGION",               //1     T:跋絏岿粇        S:区码错误              //
        "FLASH ID ERR",               //! 3-12-1 23:40 2     T:FLASH ID ぃ才    S:FLASH ID 不符         //
},
#endif//USE_THAI_OSD

//HUNGARIAN_OSD zhuyf add 30/12/2004 17:15
#ifdef USE_HUNGARIAN_OSD
//Hungarian
{
        "INPUT PASSWD",               //0     T:岿粇        S:级别错误              //
        "WRONG REGION",               //1     T:跋絏岿粇        S:区码错误              //
        "FLASH ID ERR",               //2     T:FLASH ID ぃ才   S:FLASH ID 不符         //
},
#endif
#ifdef USE_ARABIC_OSD
//English
{
        "\r\x45""\xb0",//"INPUT PASSWD",               //0     T:岿粇        S:级别错误              //
        "\r\x47""\x74",//"WRONG REGION",               //1     T:跋絏岿粇        S:区码错误              //
        "FLASH ID ERR",               //2     T:FLASH ID ぃ才   S:FLASH ID 不符         //
},
#endif
#ifdef USE_GREECE_OSD
//Greece
{
        "INPUT PASSWD",               //0     T:岿粇        S:级别错误              //
        "WRONG REGION",               //1     T:跋絏岿粇        S:区码错误              //
        "FLASH ID ERR",               //2     T:FLASH ID ぃ才   S:FLASH ID 不符         //
},
#endif

#ifdef USE_BRAZIL_OSD
//Brazil
{
        "DIGITE A SENHA",               //0     T:岿粇        S:级别错误              //
        "REGI""\xc3""O ERRADA",               //1     T:跋絏岿粇        S:区码错误              //
        "FLASH ID ERR",               //2     T:FLASH ID ぃ才   S:FLASH ID 不符         //
},
#endif

#ifdef USE_SLOVENIAN_OSD               //felix 2005-9-29 17:57
//SLOVENIAN
{
        "VHODNO GESLO",                                 //"INPUT PASSWD",               //0     T:岿粇      S:级别错误              //
        "NAPA""\r\x06""NO" "PODRO""\r\x06""JE",        //"WRONG REGION",               //1     T:跋絏岿粇      S:区码错误              //
        "IDD NAPAKA",                            //"FLASH ID ERR",               //2     T:FLASH ID ぃ才 S:FLASH ID 不符         //
},
#endif
};



//Need to add Italian, Netherlands, Sweden and Denmark languages
const char *const lang_names[N_OSD_LANGS][MAX_OSD_LANG_STR_ID]=     //extend language support, Jeff 20020517
{

#ifdef USE_ENGLISH_OSD
//English
{
        " ",                          //0
        "ENGLISH",                    //1     T:璣粂        S:英语          //
        #if defined(HUAJIA_DVD)||defined(MINTON_DVD)
        "JAPANESE",                      //2     T:ら粂        S:日语          //
        #else
        "JAPAN",                      //2     T:ら粂        S:日语          //
        #endif
        "FRENCH",                     //3     T:猭粂        S:法语          //
        "PORTUGUESE",                 //4     T:覆靛粂    S:葡萄牙        //
        "GERMAN",                     //5     T:紈粂        S:德国          //
        "LATIN",                      //6     T:┰粂      S:拉丁          //
        "SPANISH",                    //7     T:﹁痁粂    S:西班牙        //
        "CHINESE",                    //8     T:簙粂        S:中文          //
        "POLISH",                     //9     T:猧孽粂      S:波兰          //
        "CZECH",                      //10    T:倍粂      S:捷克          //
        "HUNGARIAN",                  //11    T:粂    S:匈牙利        //
        "ICELANDIC",                  //12    T:畄粂      S:冰岛          //
        "HINDI",                      //13    T:粂      S:印地          //
#if defined(HUAJIA_DVD)&&!defined(OSD_SHOW_DUTCH)
        "NETHERLAND",//"DUTCH",                      //14    T:颤孽粂      S:荷兰          //
#else
        "DUTCH",                      //14    T:颤孽粂      S:荷兰          //
#endif
        "TURKISH",                    //15    T:φㄤ粂    S:土耳其        //
        "DANISH",                     //16    T:う沉粂      S:丹麦          //
        "SWEDISH",                    //17    T:风ㄥ粂      S:瑞典          //
        "FINNISH",                    //18    T:孽粂      S:芬兰          //
        "GREEK",                      //19    T:镁粂      S:希腊          //
        "NORWEGIAN",                  //20    T:粂      S:挪威          //
        "KOREAN",                     //21    T:龙粂        S:韩国          //
        "THAI",                       //22    T:粂        S:泰国          //
        "ITALIAN",                    //23    S:意大利语                    //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",                    //24    S:俄文                        //
        "INDONESIAN",                 //25    S:印尼语Indonesian            //
        "INDONESIAN",                 //26    S:印尼语Indonesian_new        //
        "ARABIC",                   //ARABIC                        //27
        "HEBRAIC",                  //Hebraic                       //28
        "HEBRAIC",                  //Hebraic                       //29
        "ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGUESE",					//BRAZIL 巴西               //36
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_SCHINESE_OSD
//Simplied Chinese
{
        " ",                          //0
        OS_ENGLISH,                   //1     T:璣粂        S:英语          //
        OS_JAPAN,                     //2     T:ら粂        S:日语          //
        OS_FRENCH,                    //3     T:猭粂        S:法语          //
        OS_PORTUGUESE,                //4     T:覆靛粂    S:葡萄牙        //
        OS_GERMAM,                    //5     T:紈粂        S:德语          //
        OS_LATIN,                     //6     T:┰粂      S:拉丁语        //
        OS_SPANISH,                   //7     T:﹁痁粂    S:西班牙语      //
        OS_CHINESE,                   //8     T:簙粂        S:中文          //
        "POLISH",                     //9     T:猧孽粂      S:波兰          //
        "CZECH",                      //10    T:倍粂      S:捷克          //
        "HUNGARIAN",                  //11    T:粂    S:匈牙利        //
        "ICELANDIC",                  //12    T:畄粂      S:冰岛          //
        "HINDI",                      //13    T:粂      S:印地          //
        "DUTCH",                      //14    T:颤孽粂      S:荷兰          //
        "TURKISH",                    //15    T:φㄤ粂    S:土耳其        //
        "DANISH",                     //16    T:う沉粂      S:丹麦          //
        "SWEDISH",                    //17    T:风ㄥ粂      S:瑞典          //
        "FINNISH",                    //18    T:孽粂      S:芬兰          //
        "GREEK",                      //19    T:镁粂      S:希腊          //
        "NORWEGIAN",                  //20    T:粂      S:挪威          //
        "KOREAN",                     //21    T:龙粂        S:韩国          //
        "THAI",                       //22    T:粂        S:泰国          //
        "ITALIAN",                    //23    S:意大利语                    //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",                    //24    S:俄文                        //
        "INDONESIAN",                 //25    S:印尼语Indonesian            //
        "INDONESIAN",                 //26    S:印尼语Indonesian_new        //
        "ARABIC",                   //ARABIC                        //27
        "HEBRAIC",                  //Hebraic                       //28
        "HEBRAIC",                  //Hebraic                       //29
        "ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_TCHINESE_OSD
//Traditional Chinese
{
        " ",                            //0
        TOS_ENGLISH,                    //1     T:璣粂      S:英语          //
        TOS_JAPAN,                      //2     T:ら粂      S:日语          //
        TOS_FRENCH,                     //3     T:猭粂      S:法语          //
        TOS_PORTUGUESE,                 //4     T:覆靛粂  S:葡萄牙        //
        TOS_GERMAM,                     //5     T:紈粂      S:德国          //
        TOS_LATIN,                      //6     T:┰粂    S:拉丁          //
        TOS_SPANISH,                    //7     T:﹁痁粂  S:西班牙        //
        TOS_CHINESE,                    //8     T:簙粂      S:中文          //
        "POLISH",                       //9     T:猧孽粂    S:波兰          //
        "CZECH",                        //10    T:倍粂    S:捷克          //
        "HUNGARIAN",                    //11    T:粂  S:匈牙利        //
        "ICELANDIC",                    //12    T:畄粂    S:冰岛          //
        "HINDI",                        //13    T:粂    S:印地          //
        "DUTCH",                        //14    T:颤孽粂    S:荷兰          //
        "TURKISH",                      //15    T:φㄤ粂  S:土耳其        //
        "DANISH",                       //16    T:う沉粂    S:丹麦          //
        "SWEDISH",                      //17    T:风ㄥ粂    S:瑞典          //
        "FINNISH",                      //18    T:孽粂    S:芬兰          //
        "GREEK",                        //19    T:镁粂    S:希腊          //
        "NORWEGIAN",                    //20    T:粂    S:挪威          //
        "KOREAN",                       //21    T:龙粂      S:韩国          //
        "THAI",                         //22    T:粂      S:泰国          //
        "ITALIAN",                      //23    S:意大利语                  //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",                      //24      S:俄文                        //
        "INDONESIAN",                   //25      S:印尼语Indonesian            //
        "INDONESIAN",                   //26      S:印尼语Indonesian_new        //
        "ARABIC",                   //ARABIC                        //27
        "HEBRAIC",                  //Hebraic                       //28
        "HEBRAIC",                  //Hebraic                       //29
        "ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_GERMAN_OSD
//German
{
        " ",                          //0
        "ENGLISCH",                             //1     T:璣粂      S:英语              //
        "JAPANISCH",                            //2     T:ら粂      S:日语              //
        "FRANZ\xd6\x53\x49\x53\x43\x48",        //3     T:猭粂      S:法语              //
        //LYC add 2005-10-10 note:If set German osd but dvd language show France DB 5.1CH,
        //the length of string is 25 bytes benefit region length(24),must cut some font 
        "PORTUGIESISCH",                        //4     T:覆靛粂  S:葡萄牙            //
        "DEUTSCH",                              //5     T:紈粂      S:德语              //
        "LATEINISCH",                           //6     T:┰粂    S:拉丁语            //
        "SPANISCH",                             //7     T:﹁痁粂  S:西班牙语          //
        "CHINESISCH",                           //8     T:簙粂      S:中文              //
        "POLNISCH",                             //9     T:猧孽粂    S:波兰              //
        "TSCHECHISCH",                          //10    T:倍粂    S:捷克              //
        "UNGARISCH",                            //11    T:粂  S:匈牙利            //
        "ISL\xc4\x4e\x44ISCH",                  //12    T:畄粂    S:冰岛              //
        "HINDI",                                //13    T:粂    S:印地              //
        "NIEDERL\xc4NDISCH",                    //14    T:颤孽粂    S:荷兰              // // "HOLL\xc4\x4e\x44ISCH", //ryan
        "T\xdc\x52KISCH",                       //15    T:φㄤ粂  S:土耳其            //
        "D\xc4NISCH",                           //16    T:う沉粂    S:丹麦              //
        "SCHWEDISCH",                           //17    T:风ㄥ粂    S:瑞典              //
        "FINNISCH",                             //18    T:孽粂    S:芬兰              //
        "GRIECHISCH",                           //19    T:镁粂    S:希腊              //
        "NORWEGISCH",                           //20    T:粂    S:挪威              //
        "KOREAN",                               //21    T:龙粂      S:韩国              //
        "THAI",                                 //22    T:粂      S:泰国              //
        "ITALIENISCH",                          //23    S:意大利语                      //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",                              //24    S:俄文                          //
        "INDONESIAN",                           //25    S:印尼语Indonesian              //
        "INDONESIAN",                           //26    S:印尼语Indonesian_new          //
        "ARABIC",                   //ARABIC                        //27
        "HEBRAIC",                  //Hebraic                       //28
        "HEBRAIC",                  //Hebraic                       //29
        "ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGIESISCH",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_SPANISH_OSD
//Spanish
{
        " ",                            //0
        "INGL\xc9S",                    //1     T:璣粂      S:英语      E:ENGLISCH      //
        "JAPON\xc9S",                   //2     T:ら粂      S:日语      E:JAPAN         //
        "FRANC\xc9S",                   //3     T:猭粂      S:法语      E:FRENCH        //
        "PORTUGU\xc9S",                 //4     T:覆靛粂  S:葡萄牙    E:PORTUGUESE    //
        "ALEM\xc1N",                    //5     T:紈粂      S:德国      E:GERMAN        //
        "LAT\xcdN",                     //6     T:┰粂    S:拉丁      E:LATIN         //
        "ESPA\xd1OL",                   //7     T:﹁痁粂  S:西班牙    E:SPANISH       //
        "CHINO",                        //8     T:簙粂      S:中文      E:CHINESE       //
        "POLACO",                       //9     T:猧孽粂    S:波兰      E:POLISH        //
        "CHECO",                        //10    T:倍粂    S:捷克      E:CZECH         //
        "H\xdaNGARO",                   //11    T:粂  S:匈牙利    E:HUNGARIAN     //
        "ISLAND\xc9S",                  //12    T:畄粂    S:冰岛      E:ICELANDIC     //
        "HINDI",                        //13    T:粂    S:印地      E:HINDI         //
        "HOLAND\xc9S",                  //14    T:颤孽粂    S:荷兰      E:DUTCH         //
        "TURCO",                        //15    T:φㄤ粂  S:土耳其    E:TURKISH       //
        "DAN\xc9S",                     //16    T:う沉粂    S:丹麦      E:DANISH        //
        "SUECO",                        //17    T:风ㄥ粂    S:瑞典      E:SWEDISH       //
        "FINLAND\xc9S",                 //18    T:孽粂    S:芬兰      E:FINNISH       //
        "GRIEGO",                       //19    T:镁粂    S:希腊      E:GREEK         //
        "NORUEGO",                      //20    T:粂    S:挪威      E:NORWEGIAN     //
        "COREANO",                      //21    T:龙粂      S:韩国      E:KOREAN        //
        "TAILAND\xc9S",                 //22    T:粂      S:泰国      E:THAI          //
        "ITALIANO",                     //23    S:意大利语              E:ITALIAN       //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",                      //24    S:俄文                                  //
        "INDONESIAN",                   //25    S:印尼语Indonesian                      //
        "INDONESIAN",                   //26    S:印尼语Indonesian_new                  //
        "ARABIC",                   //ARABIC                        //27
        "HEBRAIC",                  //Hebraic                       //28
        "HEBRAIC",                  //Hebraic                       //29
        "ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU""\xc9""S",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_FRENCH_OSD
//French
{
        " ",                          //0
        "ANGLAIS",          //1     T:璣粂        S:英语          E:ENGLISH       //
        "JAPONAI",          //2     T:ら粂        S:日语          E:JAPAN         //
        "FRAN\xc7""AIS",                //3     T:猭粂        S:法语          E:FRENCH        //
        "PORTUGAIS",                    //4     T:覆靛粂    S:葡萄牙        E:PORTUGUESE    //
        "ALLEMAND",                     //5     T:紈粂        S:德国          E:GERMAN        //
        "LATIN",                      //6     T:┰粂      S:拉丁          E:LATIN         //
        "ESPAGNOL",                     //7     T:﹁痁粂    S:西班牙        E:SPANISH       //
        "CHINOIS",                      //8     T:簙粂        S:中文          E:CHINESE       //
        "POLONAIS",                     //9     T:猧孽粂      S:波兰          E:POLISH        //
        "TCH\xc8QUE",                   //10    T:倍粂      S:捷克          E:CZECH         //
        "HONGROIS",                     //11    T:粂    S:匈牙利        E:HUNGARIAN     //
        "ISLANDAIS",                    //12    T:畄粂      S:冰岛          E:ICELANDIC     //
        "HINDI",                        //13    T:粂      S:印地          E:HINDI          //  //"INDIEN", //ryan 2003-02-12
        "HOLLANDAIS",                   //14    T:颤孽粂      S:荷兰          E:DUTCH         //
        "TURC",                     //15    T:φㄤ粂    S:土耳其        E:TURKISH       //
        "DANOIS",                       //16    T:う沉粂      S:丹麦          E:DANISH        //
        "SU\xc9""DOIS",                 //17    T:风ㄥ粂      S:瑞典          E:SWEDISH       //
        "FINLANDAIS",                   //18    T:孽粂      S:芬兰          E:FINNISH       //
        "GREC",                     //19    T:镁粂      S:希腊          E:GREEK         //
        "NORV\xc9""GIEN",               //20    T:粂      S:挪威          E:NORWEGIAN     //
        "COR\xc9""EN",                  //21    T:龙粂        S:韩国          E:KOREAN        //
        "THAILANDAIS",                  //22    T:粂        S:泰国          E:THAI          //
        "ITALIEN",                      //23      S:意大利语                    E:ITALIAN       //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",                      //24    S:俄文                                          //
        "INDONESIAN",                   //25    S:印尼语Indonesian                              //
        "INDONESIAN",                   //26    S:印尼语Indonesian_new                          //
        "ARABIC",                   //ARABIC                        //27
        "HEBRAIC",                  //Hebraic                       //28
        "HEBRAIC",                  //Hebraic                       //29
        "ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGAIS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_PORTUGUESE_OSD
//Portuguese
{
        " ",                          //0
        "INGL""\xca""S",//"ENGLISH",                    //1     T:璣粂        S:英语          E:ENGLISH       //
        "JAPON""\xca""S",//"JAPAN",                      //2     T:ら粂        S:日语          E:JAPAN         //
        "FRANC""\xca""S",//"FRENCH",                     //3     T:猭粂        S:法语          E:FRENCH        //
        "PORTUGU""\xca""S",//"PORTUGUESE",                 //4     T:覆靛粂    S:葡萄牙        E:PORTUGUESE    //
        "ALEM""\xc3""O",//"GERMAN",                     //5     T:紈粂        S:德国          E:GERMAN        //
        "LATIN",                      //6     T:┰粂      S:拉丁          E:LATIN         //
        "ESPANHOL",//"SPANISH",                    //7     T:﹁痁粂    S:西班牙        E:SPANISH       //
        "CHIN""\xca""S",//"CHINESE",                    //8     T:簙粂        S:中文          E:CHINESE       //
        "POLACO",//"POLISH",                     //9     T:猧孽粂      S:波兰          E:POLISH        //
        "CHECO",//"CZECH",                      //10    T:倍粂      S:捷克          E:CZECH         //
        "H""\xda""NGARO",//"HUNGARIAN",                  //11    T:粂    S:匈牙利        E:HUNGARIAN     //
        "ISLAND""\xca""S",//"ICELANDIC",                  //12    T:畄粂      S:冰岛          E:ICELANDIC     //
        "HINDI",                      //13    T:粂      S:印地          E:HINDI         //
        "HOLAND""\xca""S",//"DUTCH",                      //14    T:颤孽粂      S:荷兰          E:DUTCH         //
        "TURCO",//"TURKISH",                    //15    T:φㄤ粂    S:土耳其        E:TURKISH       //
        "DINAMARQU""\xca""S",//"DANISH",                     //16    T:う沉粂      S:丹麦          E:DANISH        //
        "SUECO",//"SWEDISH",                    //17    T:风ㄥ粂      S:瑞典          E:SWEDISH       //
        "FINLAND""\xca""S",//"FINNISH",                    //18    T:孽粂      S:芬兰          E:FINNISH       //
        "GREGO",//"GREEK",                      //19    T:镁粂      S:希腊          E:GREEK         //
        "NORUEGU""\xca""S",//"NORWEGIAN",                  //20    T:粂      S:挪威          E:NORWEGIAN     //
        "COREANO",//"KOREAN",                     //21    T:龙粂        S:韩国          E:KOREAN        //
        "TAILAND""\xca""S",//"THAI",                       //22    T:粂        S:泰国          E:THAI          //
        "ITALIANO",//"ITALIAN",                    //23   S:意大利语                    E:ITALIAN       //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",                    //24    S:俄文                        //
        "INDONESIAN",                 //25    S:印尼语Indonesian            //
        "INDONESIAN",                 //26    S:印尼语Indonesian_new        //
        "ARABIC",                   //ARABIC                        //27
        "HEBRAIC",                  //Hebraic                       //28
        "HEBRAIC",                  //Hebraic                       //29
        "ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU""\xca""S",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_LATIN_OSD
//Latin
{
        " ",                          //0
        "ENGLISH",                    //1     T:璣粂        S:英语          E:ENGLISH       //
        "JAPAN",                      //2     T:ら粂        S:日语          E:JAPAN         //
        "FRENCH",                     //3     T:猭粂        S:法语          E:FRENCH        //
        "PORTUGUESE",                 //4     T:覆靛粂    S:葡萄牙        E:PORTUGUESE    //
        "GERMAN",                     //5     T:紈粂        S:德国          E:GERMAN        //
        "LATIN",                      //6     T:┰粂      S:拉丁          E:LATIN         //
        "SPANISH",                    //7     T:﹁痁粂    S:西班牙        E:SPANISH       //
        "CHINESE",                    //8     T:簙粂        S:中文          E:CHINESE       //
        "POLISH",                     //9     T:猧孽粂      S:波兰          E:POLISH        //
        "CZECH",                      //10    T:倍粂      S:捷克          E:CZECH         //
        "HUNGARIAN",                  //11    T:粂    S:匈牙利        E:HUNGARIAN     //
        "ICELANDIC",                  //12    T:畄粂      S:冰岛          E:ICELANDIC     //
        "HINDI",                      //13    T:粂      S:印地          E:HINDI         //
        "DUTCH",                      //14    T:颤孽粂      S:荷兰          E:DUTCH         //
        "TURKISH",                    //15    T:φㄤ粂    S:土耳其        E:TURKISH       //
        "DANISH",                     //16    T:う沉粂      S:丹麦          E:DANISH        //
        "SWEDISH",                    //17    T:风ㄥ粂      S:瑞典          E:SWEDISH       //
        "FINNISH",                    //18    T:孽粂      S:芬兰          E:FINNISH       //
        "GREEK",                      //19    T:镁粂      S:希腊          E:GREEK         //
        "NORWEGIAN",                  //20    T:粂      S:挪威          E:NORWEGIAN     //
        "KOREAN",                     //21    T:龙粂        S:韩国          E:KOREAN        //
        "THAI",                       //22    T:粂        S:泰国          E:THAI          //
        "ITALIAN",                    //23    S:意大利语                    E:ITALIAN       //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",                    //24    S:俄文                        //
        "INDONESIAN",                 //25    S:印尼语Indonesian            //
        "INDONESIAN",                 //26    S:印尼语Indonesian_new        //
        "ARABIC",                   //ARABIC                        //27
        "HEBRAIC",                  //Hebraic                       //28
        "HEBRAIC",                  //Hebraic                       //29
        "ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_ITALIAN_OSD
//Italian
{
        " ",                          //0
        "INGLESE",                    //1     T:璣粂        S:英语          E:ENGLISH       //
        "GIAPPONESE",                 //2     T:ら粂        S:日语          E:JAPAN         //
        "FRANCESE",                   //3     T:猭粂        S:法语          E:FRENCH        //
        "PORTOGHESE",                 //4     T:覆靛粂    S:葡萄牙        E:PORTUGUESE    //
        "TEDESCO",                    //5     T:紈粂        S:德国          E:GERMAN        //
        "LATINO",                     //6     T:┰粂      S:拉丁          E:LATIN         //
        "SPAGNOLO",                   //7     T:﹁痁粂    S:西班牙        E:SPANISH       //
        "CINESE",                 //8     T:簙粂        S:中文          E:CHINESE       //
        "POLACCO",                     //9     T:猧孽粂      S:波兰          E:POLISH        //
        "CECO",                       //10    T:倍粂      S:捷克          E:CZECH         //
        #ifdef HUAJIA_DVD
        "UNGHERESE",//"UNGARO",                     //11    T:粂    S:匈牙利        E:HUNGARIAN     //
        #else
        "UNGARO",                     //11    T:粂    S:匈牙利        E:HUNGARIAN     //
        #endif
        "ISLANDESE",                  //12    T:畄粂      S:冰岛          E:ICELANDIC     //
        #ifdef HUAJIA_DVD
        "HINDI",//"INDI",                       //13    T:粂      S:印地          E:HINDI         //
        #else
        "INDI",                       //13    T:粂      S:印地          E:HINDI         //
        #endif
        "OLANDESE",                   //14    T:颤孽粂      S:荷兰          E:DUTCH         //
        "TURCO",                      //15    T:φㄤ粂    S:土耳其        E:TURKISH       //
        "DANESE",                     //16    T:う沉粂      S:丹麦          E:DANISH        //
        "SVEDESE",                    //17    T:风ㄥ粂      S:瑞典          E:SWEDISH       //
        "FINLANDESE",                 //18    T:孽粂      S:芬兰          E:FINNISH       //
        "GRECO",                      //19    T:镁粂      S:希腊          E:GREEK         //
        "NORVEGESE",                  //20    T:粂      S:挪威          E:NORWEGIAN     //
        "COREANO",                    //21    T:龙粂        S:韩国          E:KOREAN        //
        "TAILANDESE",                 //22    T:粂        S:泰国          E:THAI          //
        "ITALIANO",                   //23    S:意大利语                    E:ITALIAN       //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",                    //24    S:俄文                        //
        "INDONESIAN",                 //25    S:印尼语Indonesian            //
        "INDONESIAN",                 //26    S:印尼语Indonesian_new        //
        "ARABIC",               //ARABIC                        //27
        "HEBRAIC",              //Hebraic                       //28
        "HEBRAIC",              //Hebraic                       //29
        "ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTOGHESE",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_JAPANESE_OSD
//Japanese
{
        " ",                          //0
        JOS_ENGLISH,            //"INGLESE",                    //1     T:璣粂        S:英语          E:ENGLISH       //
        JOS_JAPAN,              //"GIAPPONESE",                 //2     T:ら粂        S:日语          E:JAPAN         //
        JOS_FRENCH,             //"FRANCESE",                   //3     T:猭粂        S:法语          E:FRENCH        //
        JOS_PORTUGUESE,         //"PORTOGHESE",                 //4     T:覆靛粂    S:葡萄牙        E:PORTUGUESE    //
        JOS_GERMAM,             //"TEDESCO",                    //5     T:紈粂        S:德国          E:GERMAN        //
        JOS_LATIN,              //"LATINO",                     //6     T:┰粂      S:拉丁          E:LATIN         //
        JOS_SPANISH,            //"SPAGNOLO",                   //7     T:﹁痁粂    S:西班牙        E:SPANISH       //
        JOS_CHINESE,            //"CINESE",                     //8     T:簙粂        S:中文          E:CHINESE       //
        JOS_POLISH,             //"POLACO",                     //9     T:猧孽粂      S:波兰          E:POLISH        //
        JOS_CZECH,              //"CECO",                       //10    T:倍粂      S:捷克          E:CZECH         //
        JOS_HUNGARIAN,          //"UNGARO",                     //11    T:粂    S:匈牙利        E:HUNGARIAN     //
        JOS_ICELANDIC,          //"ISLANDESE",                  //12    T:畄粂      S:冰岛          E:ICELANDIC     //
        JOS_HINDI,              //"INDI",                       //13    T:粂      S:印地          E:HINDI         //
        JOS_DUTCH,              //"OLANDESE",                   //14    T:颤孽粂      S:荷兰          E:DUTCH         //
        JOS_TURKISH,            //"TURCO",                      //15    T:φㄤ粂    S:土耳其        E:TURKISH       //
        JOS_DANISH,             //"DANESE",                     //16    T:う沉粂      S:丹麦          E:DANISH        //
        JOS_SWEDISH,            //"SVEDESE",                    //17    T:风ㄥ粂      S:瑞典          E:SWEDISH       //
        JOS_FINNISH,            //"FINLANDESE",                 //18    T:孽粂      S:芬兰          E:FINNISH       //
        JOS_GREEK,              //"GRECO",                      //19    T:镁粂      S:希腊          E:GREEK         //
        JOS_NORWEGIAN,          //"NORVEGESE",                  //20    T:粂      S:挪威          E:NORWEGIAN     //
        JOS_KOREAN,             //"COREANO",                    //21    T:龙粂        S:韩国          E:KOREAN        //
        JOS_THAI,               //"TAILANDESE",                 //22    T:粂        S:泰国          E:THAI          //
        JOS_ITALIAN,            //"ITALIANO",                   //23      S:意大利语                    E:ITALIAN       //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",                                              //24      S:俄文                        //
        "INDONESIAN",                                           //25      S:印尼语Indonesian            //
        "INDONESIAN",                                           //26      S:印尼语Indonesian_new        //
        "ARABIC",               //ARABIC                        //27
        "HEBRAIC",              //Hebraic                       //28
        "HEBRAIC",              //Hebraic                       //29
        "ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_RUSSIAN_OSD
//Russian
#ifdef RUSSIAN_FIX_HJ
{
        " ",                          //0
        "\r\x8a""\r\x9d""\r\x99""\r\x8f""\r\x86""\r\x95""\r\x87""\r\x96",//"ENGLISH",                    //1     T:璣粂        S:英语          //
        "\r\x9e""\r\x8b""\r\x8e""\r\x9d""\r\x87""\r\x96",//"JAPAN",                      //2     T:ら粂        S:日语          //
        "\r\x85""\r\x8c""\r\x8a""\r\x9d""\r\x9b",//"FRENCH",                     //3     T:猭粂        S:法语          //
        "\r\x8b""\r\x8e""\r\x8c""\r\x92""\r\x89""\r\x99""\r\x8a""\r\x8f""\r\x91""\r\x87""\r\x96",//"PORTUGUESE",                 //4     T:覆靛粂    S:葡萄牙        //
        "\r\x9d""\r\x98""\r\x9a""\r\x98""\r\x9b""\r\x96",//"GERMAN",                     //5     T:紈粂        S:德国          //
        "\r\x8f""\r\x8a""\r\x92""\r\x97""\r\x9d""\r\x83",//"LATIN",                      //6     T:┰粂      S:拉丁          //
        "\r\x86""\r\x87""\r\x8b""\r\x8a""\r\x9d""\r\x87""\r\x96",//"SPANISH",                    //7     T:﹁痁粂    S:西班牙        //
        "\r\x96""\r\x86""\r\x92""\r\x8a""\r\x95""\r\x87""\r\x96",//"CHINESE",                    //8     T:簙粂        S:中文          //
        "\r\x8b""\r\x8e""\r\x8f""\r\x91""\r\x87""\r\x96",//"POLISH",                     //9     T:猧孽粂      S:波兰          //
        "\r\x9c""\r\x98""\r\x8d""\r\x87""\r\x96",//"CZECH",                      //10    T:倍粂      S:捷克          //
        "\r\x88""\r\x98""\r\x9d""\r\x99""\r\x98""\r\x8c""\r\x87""\r\x96",//"HUNGARIAN",                  //11    T:粂    S:匈牙利        //
        "\r\x86""\r\x87""\r\x8f""\r\x8a""\r\x9d""\r\x90""\r\x87""\r\x96",//"ICELANDIC",                  //12    T:畄粂      S:冰岛          //
        "\r\x82""\r\x86""\r\x9d""\r\x90""\r\x86",//"HINDI",                      //13    T:粂      S:印地          //
        "\r\x99""\r\x8e""\r\x8f""\r\x8f""\r\x8a""\r\x9d""\r\x90",//"DUTCH",                      //14    T:颤孽粂      S:荷兰          //
        "\r\x92""\r\x89""\r\x8c""\r\x98""\r\x9b""\r\x96",//"TURKISH",                    //15    T:φㄤ粂    S:土耳其        //
        "\r\x90""\r\x8a""\r\x92""\r\x87""\r\x96",//"DANISH",                     //16    T:う沉粂      S:丹麦          //
        "\r\x8d""\r\x88""\r\x98""\r\x90""\r\x87""\r\x96",//"SWEDISH",                    //17    T:风ㄥ粂      S:瑞典          //
        "\r\x85""\r\x86""\r\x9d""\r\x87""\r\x96""\r\x86""\r\x95",//"FINNISH",                    //18    T:孽粂      S:芬兰          //
        "\r\x99""\r\x8c""\r\x98""\r\x9b""\r\x86""\r\x9e",//"GREEK",                      //19    T:镁粂      S:希腊          //
        "\r\x9d""\r\x8e""\r\x8c""\r\x88""\r\x98""\r\x7e""\r\x87""\r\x96",//"NORWEGIAN",                  //20    T:粂      S:挪威          //
        "\r\x96""\r\x8e""\r\x8c""\r\x98""\r\x95""\r\x87""\r\x96",//"KOREAN",                     //21    T:龙粂        S:韩国          //
        "\r\x92""\r\x8a""\r\x95""\r\x87""\r\x96",//"THAI",                       //22    T:粂        S:泰国          //
        "\r\x86""\r\x92""\r\x8a""\r\x8f""\r\x91""\r\x9e""\r\x9d",//"ITALIAN",                    //23     S:意大利语                    //
#ifndef MAX_OSD_LANG_STR_ID_25
        "\r\x8c""\r\x89""\r\x87""\r\x87""\r\x96""\r\x86""\r\x95",//"RUSSIAN",                    //24     S:俄文                        //
        "\r\x86""\r\x9d""\r\x90""\r\x8e""\r\x9d""\r\x98""\r\x94""\r\x86""\r\x95""\r\x87""\r\x96",//"INDONESIAN",                 //25     S:印尼语Indonesian            //
        "\r\x86""\r\x9d""\r\x90""\r\x8e""\r\x9d""\r\x98""\r\x94""\r\x86""\r\x95""\r\x87""\r\x96",//"INDONESIAN",                 //26     S:印尼语Indonesian_new        //
        "\r\x8a""\r\x8c""\r\x8a""\r\x83""\r\x87""\r\x96",                   //ARABIC    //27
        "\r\x86""\r\x88""\r\x8c""\r\x86""\r\x92",               //Hebraic   //28
        "\r\x86""\r\x88""\r\x8c""\r\x86""\r\x92",                   //Hebraic   //29
        "\r\x8c""\r\x89""\r\x9a""\r\x97""\r\x9d""\r\x87""\r\x96",                   //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#else//RUSSIAN_FIX_HJ
{
        " ",                          //0
        "\r\x8a""\r\x9d""\r\x99""\r\x8f""\r\x86""\r\x95""\r\x87""\r\x96""\r\x86""\r\x95",//"ENGLISH",                    //1     T:璣粂        S:英语          //
        "\r\x9e""\r\x8b""\r\x8e""\r\x9d""\r\x87""\r\x96""\r\x86""\r\x95",//"JAPAN",                      //2     T:ら粂        S:日语          //
        "\r\x85""\r\x8c""\r\x8a""\r\x9d""\r\x9b""\r\x89""\r\x94""\r\x87""\r\x96""\r\x86""\r\x95",//"FRENCH",                     //3     T:猭粂        S:法语          //
        "\r\x8b""\r\x8e""\r\x8c""\r\x92""\r\x89""\r\x99""\r\x8a""\r\x8f""\r\x91""\r\x87""\r\x96""\r\x86""\r\x95",//"PORTUGUESE",                 //4     T:覆靛粂    S:葡萄牙        //
        "\r\x9d""\r\x98""\r\x9a""\r\x98""\r\x9b""\r\x96""\r\x86""\r\x95",//"GERMAN",                     //5     T:紈粂        S:德国          //
        "\r\x8f""\r\x8a""\r\x92""\r\x86""\r\x9d""\r\x87""\r\x96""\r\x86""\r\x95",//"LATIN",                      //6     T:┰粂      S:拉丁          //
        "\r\x86""\r\x87""\r\x8b""\r\x8a""\r\x9d""\r\x87""\r\x96""\r\x86""\r\x95",//"SPANISH",                    //7     T:﹁痁粂    S:西班牙        //
        "\r\x96""\r\x86""\r\x92""\r\x8a""\r\x95""\r\x87""\r\x96""\r\x86""\r\x95",//"CHINESE",                    //8     T:簙粂        S:中文          //
        "\r\x8b""\r\x8e""\r\x8f""\r\x91""\r\x87""\r\x96""\r\x86""\r\x95",//"POLISH",                     //9     T:猧孽粂      S:波兰          //
        "\r\x9c""\r\x98""\r\x8d""\r\x87""\r\x96""\r\x86""\r\x95",//"CZECH",                      //10    T:倍粂      S:捷克          //
        "\r\x88""\r\x98""\r\x9d""\r\x99""\r\x98""\r\x8c""\r\x87""\r\x96""\r\x86""\r\x95",//"HUNGARIAN",                  //11    T:粂    S:匈牙利        //
        "\r\x86""\r\x87""\r\x8f""\r\x8a""\r\x9d""\r\x90""\r\x87""\r\x96""\r\x86""\r\x95",//"ICELANDIC",                  //12    T:畄粂      S:冰岛          //
        "\r\x82""\r\x86""\r\x9d""\r\x90""\r\x86",//"HINDI",                      //13    T:粂      S:印地          //
        "\r\x99""\r\x8e""\r\x8f""\r\x8f""\r\x8a""\r\x9d""\r\x90""\r\x87""\r\x96""\r\x86""\r\x95",//"DUTCH",                      //14    T:颤孽粂      S:荷兰          //
        "\r\x92""\r\x89""\r\x8c""\r\x98""\r\x9b""\r\x96""\r\x86""\r\x95",//"TURKISH",                    //15    T:φㄤ粂    S:土耳其        //
        "\r\x90""\r\x8a""\r\x92""\r\x87""\r\x96""\r\x86""\r\x95",//"DANISH",                     //16    T:う沉粂      S:丹麦          //
        "\r\x8d""\r\x88""\r\x98""\r\x90""\r\x87""\r\x96""\r\x86""\r\x95",//"SWEDISH",                    //17    T:风ㄥ粂      S:瑞典          //
        "\r\x85""\r\x86""\r\x9d""\r\x87""\r\x96""\r\x86""\r\x95",//"FINNISH",                    //18    T:孽粂      S:芬兰          //
        "\r\x99""\r\x8c""\r\x98""\r\x9c""\r\x98""\r\x87""\r\x96""\r\x86""\r\x95",//"GREEK",                      //19    T:镁粂      S:希腊          //
        "\r\x9d""\r\x8e""\r\x8c""\r\x88""\r\x98""\r\x7e""\r\x87""\r\x96""\r\x86""\r\x95",//"NORWEGIAN",                  //20    T:粂      S:挪威          //
        "\r\x96""\r\x8e""\r\x8c""\r\x98""\r\x95""\r\x87""\r\x96""\r\x86""\r\x95",//"KOREAN",                     //21    T:龙粂        S:韩国          //
        "\r\x92""\r\x8a""\r\x95""\r\x87""\r\x96""\r\x86""\r\x95",//"THAI",                       //22    T:粂        S:泰国          //
        "\r\x86""\r\x92""\r\x8a""\r\x8f""\r\x91""\r\x9e""\r\x9d""\r\x87""\r\x96""\r\x86""\r\x95",//"ITALIAN",                    //23     S:意大利语                    //
#ifndef MAX_OSD_LANG_STR_ID_25
        "\r\x8c""\r\x89""\r\x87""\r\x87""\r\x96""\r\x86""\r\x95",//"RUSSIAN",                    //24     S:俄文                        //
        "\r\x86""\r\x9d""\r\x90""\r\x8e""\r\x9d""\r\x98""\r\x94""\r\x86""\r\x9e",//"INDONESIAN",                 //25     S:印尼语Indonesian            //
        "\r\x86""\r\x9d""\r\x90""\r\x8e""\r\x9d""\r\x98""\r\x94""\r\x86""\r\x9e",//"INDONESIAN",                 //26     S:印尼语Indonesian_new        //
        "\r\x8a""\r\x8c""\r\x8a""\r\x83""\r\x87""\r\x96",                   //ARABIC    //27
        "\r\x86""\r\x88""\r\x8c""\r\x86""\r\x92",                   //Hebraic   //28
        "\r\x86""\r\x88""\r\x8c""\r\x86""\r\x92",                   //Hebraic   //29
        "\r\x8c""\r\x89""\r\x9a""\r\x97""\r\x9d""\r\x87""\r\x96",                   //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif//RUSSIAN_FIX_HJ

#endif

#ifdef USE_HEBRAIC_OSD
{   
        " ",                          //0
        "\r\x98""\r\x87""\r\x8a""\r\x80""\r\x8e""\r\x7e",//"ENGLISH",                    //1     T:璣粂        S:英语          //
        "\r\x98""\r\x87""\r\x8e""\r\x92""\r\x87",//"JAPAN"                      //2     T:ら粂        S:日语          //
               //"JAPANESE",              //"JAPANESE"                      //2     T:ら粂        S:日语          //
        "\r\x98""\r\x87""\r\x98""\r\x92""\r\x96""\r\x94",//"FRENCH",                     //3     T:猭粂        S:法语          //
        "\r\x98""\r\x87""\r\x84""\r\x80""\r\x83""\r\x86""\r\x96""\r\x83""\r\x92",//"PORTUGUESE",                 //4     T:覆靛粂    S:葡萄牙        //
        "\r\x98""\r\x87""\r\x8e""\r\x8c""\r\x96""\r\x80",//"GERMAN",                     //5     T:紈粂        S:德国          //
        "\r\x98""\r\x87""\r\x8e""\r\x87""\r\x86""\r\x8a",//"LATIN",                      //6     T:┰粂      S:拉丁          //
        "\r\x98""\r\x87""\r\x81""\r\x96""\r\x92""\r\x8f",//"SPANISH",                    //7     T:﹁痁粂    S:西班牙        //
        "\r\x98""\r\x87""\r\x8e""\r\x87""\r\x8f""E",//"CHINESE",                    //8     T:簙粂        S:中文          //
        "\r\x98""\r\x87""\r\x8e""\r\x8a""\r\x83""\r\x92",//"POLISH",                     //9     T:猧孽粂      S:波兰          //
        "\r\x98""\r\x87""\r\x89""\r\x9c""\r\x94",//"CZECH",                      //10    T:倍粂      S:捷克          //
        "\r\x98""\r\x87""\r\x96""\r\x80""\r\x8e""\r\x83""\r\x82",//"HUNGARIAN",                  //11    T:粂    S:匈牙利        //
        "\r\x98""\r\x87""\r\x81""\r\x8e""\r\x8a""\r\x8f""\r\x87""\r\x7e",//"ICELANDIC",                  //12    T:畄粂      S:冰岛          //
        "\r\x98""\r\x87""\r\x81""\r\x83""\r\x82",//"HINDI",                      //13    T:粂      S:印地          //
        "\r\x98""\r\x87""\r\x8e""\r\x81",//"DUTCH",                      //14    T:颤孽粂      S:荷兰          //
        "\r\x98""\r\x87""\r\x95""\r\x96""\r\x83""\r\x86",//"TURKISH",                    //15    T:φㄤ粂    S:土耳其        //
        "\r\x98""\r\x87""\r\x8e""\r\x81",//"DANISH",                     //16    T:う沉粂      S:丹麦          //
        "\r\x98""\r\x87""\r\x81""\r\x99""\r\x97",//"SWEDISH",                    //17    T:风ㄥ粂      S:瑞典          //
        "\r\x98""\r\x87""\r\x8e""\r\x87""\r\x92",//"FINNISH",                    //18    T:孽粂      S:芬兰          //
        "\r\x98""\r\x87""\r\x8e""\r\x99""\r\x87",//"GREEK",                      //19    T:镁粂      S:希腊          //
        "\r\x98""\r\x87""\r\x80""\r\x99""\r\x96""\r\x83""\r\x8e",//"NORWEGIAN",                  //20    T:粂      S:挪威          //
        "\r\x98""\r\x87""\r\x8e""\r\x7e""\r\x87""\r\x96""\r\x83""\r\x95",//"KOREAN",                     //21    T:龙粂        S:韩国          //
        "\r\x98""\r\x87""\r\x81""\r\x8e""\r\x8a""\r\x87""\r\x7e""\r\x86",//"THAI",                       //22    T:粂        S:泰国          //
        "\r\x98""\r\x87""\r\x95""\r\x8a""\r\x86""\r\x87""\r\x7e",//"ITALIAN",                    //23	  S:意大利语                    //
 #ifndef MAX_OSD_LANG_STR_ID_25
        "\r\x98""\r\x87""\r\x8f""\r\x83""\r\x96",//"RUSSIAN",                    //24	  S:俄文            	        //
        "\r\x98""\r\x87""\r\x84""\r\x8e""\r\x83""\r\x81""\r\x8e""\r\x87""\r\x7e",//"INDONESIAN",                 //25	  S:印尼语Indonesian            //
        "\r\x98""\r\x87""\r\x84""\r\x8e""\r\x83""\r\x81""\r\x8e""\r\x87""\r\x7e",//"INDONESIAN",                 //26	  S:印尼语Indonesian            //
        "\r\x98""\r\x87""\r\x7f""\r\x96""\r\x90",					//ARABIC	//27
        "HEBRAIC",					//Hebraic	//28
        "HEBRAIC",					//Hebraic	//29
        "\r\x98""\r\x87""\r\x8e""\r\x8c""\r\x83""\r\x96",					//ROMANIAN						//30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
 #endif
        " ",                                                         //37
},       
 #endif      
//HEBRAIC_OSD zhuyf  add 2004-05-26

#ifdef USE_ROMANIAN_OSD
//Romanian
{
        " ",                        //0
        "ENGLEZA",                  //"ENGLISH",            //1     T:璣粂        S:英语          //
        "JAPONEZA",                 //"JAPAN",              //2     T:ら粂        S:日语          //
        "FRANCEZA",                 //"FRENCH",             //3     T:猭粂        S:法语          //
        "PORTUGHEZA",               //"PORTUGUESE",         //4     T:覆靛粂    S:葡萄牙        //
        "GERMANA",                  //"GERMAN",             //5     T:紈粂        S:德国          //
        "LATINA",                   //"LATIN",              //6     T:┰粂      S:拉丁          //
        "SPANIOLA",                 //"SPANISH",            //7     T:﹁痁粂    S:西班牙        //
        "CHINEZA",                  //"CHINESE",            //8     T:簙粂        S:中文          //
        "POLONEZA",                 //"POLISH",             //9     T:猧孽粂      S:波兰          //
        "CEHA",                     //"CZECH",              //10    T:倍粂      S:捷克          //
        "MAGHIARA",                 //"HUNGARIAN",          //11    T:粂    S:匈牙利        //
        "ISLANDEZA",                //"ICELANDIC",          //12    T:畄粂      S:冰岛          //
        "INDIANA",                  //"HINDI",              //13    T:粂      S:印地          //
        "OLANDA",                   //"DUTCH",              //14    T:颤孽粂      S:荷兰          //
        "TURCA",                    //"TURKISH",            //15    T:φㄤ粂    S:土耳其        //
        "DANEZA",                   //"DANISH",             //16    T:う沉粂      S:丹麦          //
        "SUEDEZA",                  //"SWEDISH",            //17    T:风ㄥ粂      S:瑞典          //
        "FINLANDEZA",               //"FINNISH",            //18    T:孽粂      S:芬兰          //
        "GREACA",                   //"GREEK",              //19    T:镁粂      S:希腊          //
        "NORVEGIANA",               //"NORWEGIAN",          //20    T:粂      S:挪威          //
        "KOREEANA",                 //"KOREAN",             //21    T:龙粂        S:韩国          //
        "THAILANDEZA",              //"THAI",               //22    T:粂        S:泰国          //
        "ITALIANA",                 //"ITALIAN",            //23      S:意大利语                    //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",                    //24    S:俄文                        //
        "INDONESIAN",                 //25    S:印尼语Indonesian            //
        "INDONESIAN",                 //26    S:印尼语Indonesian_new        //
        "ARABIC",                   //ARABIC                        //27
        "HEBRAIC",                  //Hebraic                       //28
        "HEBRAIC",                  //Hebraic                       //29
        "ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_TURKISH_OSD
//Turkish
{
        " ",                        //0
        "\x005""NG""\x005""L""\x005""ZCE",                  //"ENGLISH",            //1     T:璣粂        S:英语          //
        "JAPONCA",                                          //"JAPAN",              //2     T:ら粂        S:日语          //
        "FRANSIZCA",                                        //"FRENCH",             //3     T:猭粂        S:法语          //
        "PORTEK""\x005""ZCE",                               //"PORTUGUESE",         //4     T:覆靛粂    S:葡萄牙        //
        "ALMANCA",                                          //"GERMAN",             //5     T:紈粂        S:德国          //
        "LAT""\x005""NCE",                                  //"LATIN",              //6     T:┰粂      S:拉丁          //
        "\x005""SPANYOLCA",                                 //"SPANISH",            //7     T:﹁痁粂    S:西班牙        //
        "\xc7""\x005""NCE",                                 //"CHINESE",            //8     T:簙粂        S:中文          //
        "LEH""\xc7""E",//"POLONYACA",                                       //"POLISH",             //9     T:猧孽粂      S:波兰          //
        "\xc7""EKCE",                                       //"CZECH",              //10    T:倍粂      S:捷克          //
        "MACARCA",                                          //"HUNGARIAN",          //11    T:粂    S:匈牙利        //
        "\x005""ZLANDACA",                                  //"ICELANDIC",          //12    T:畄粂      S:冰岛          //
        "H""\x005""ND""\x005""STANCA",                      //"HINDI",              //13    T:粂      S:印地          //
        "HOLLANDACA",                                       //"DUTCH",              //14    T:颤孽粂      S:荷兰          //
        "T""\xdc""RK""\xc7""E",                             //"TURKISH",            //15    T:φㄤ粂    S:土耳其        //
        "DAN""\x005""MARKACA",                              //"DANISH",             //16    T:う沉粂      S:丹麦          //
        "\x005""SVE""\xc7""CE",                             //"SWEDISH",            //17    T:风ㄥ粂      S:瑞典          //
        "F""\x005""NLAND""\x005""YACA",                     //"FINNISH",            //18    T:孽粂      S:芬兰          //
        "YUNANCA",                                          //"GREEK",              //19    T:镁粂      S:希腊          //
        "NORVE""\xc7""CE",                                  //"NORWEGIAN",          //20    T:粂      S:挪威          //
        "KORECE",                                           //"KOREAN",             //21    T:龙粂        S:韩国          //
        "TAYLAND""\xc7""A",                                 //"THAI",               //22    T:粂        S:泰国          //
        "\x05""TALYANCA",                   //"ITALIAN",            //23      S:意大利语                    //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",                    //24    S:俄文                        //
        "INDONESIAN",                 //25    S:印尼语Indonesian            //
        "INDONESIAN",                 //26    S:印尼语Indonesian_new        //
        "ARABIC",                   //ARABIC                        //27
        "HEBRAIC",                  //Hebraic                       //28
        "HEBRAIC",                  //Hebraic                       //29
        "ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_DUTCH_OSD
//Dutch
{
        " ",                                                //0
        "ENGELS",           //"ENGLISH",                    //1     T:璣粂        S:英语          //
        #ifdef HJ_2303
        "JAPANESE",                                         //2     T:ら粂        S:日语          //
        #else
        "JAPANS",           //"JAPAN",                      //2     T:ら粂        S:日语          //
        #endif
        "FRANS",            //"FRENCH",                     //3     T:猭粂        S:法语          //
        "PORTUGEES",        //"PORTUGUESE",                 //4     T:覆靛粂    S:葡萄牙        //
        "DUITS",            //"GERMAN",                     //5     T:紈粂        S:德国          //
        "LATIJN",           //"LATIN",                      //6     T:┰粂      S:拉丁          //
        "SPANNS",           //"SPANISH",                    //7     T:﹁痁粂    S:西班牙        //
        "CHINEES",          //"CHINESE",                    //8     T:簙粂        S:中文          //
        "POOLS",            //"POLISH",                     //9     T:猧孽粂      S:波兰          //
        "TSJECHI",          //"CZECH",                      //10    T:倍粂      S:捷克          //
        "HONGAARS",         //"HUNGARIAN",                  //11    T:粂    S:匈牙利        //
        "IJSLANDS",         //"ICELANDIC",                  //12    T:畄粂      S:冰岛          //
        "HINDI",            //"HINDI",                      //13    T:粂      S:印地          //
        "NEDERLANDS",       //"DUTCH",                      //14    T:颤孽粂      S:荷兰          //
        "TURKS",            //"TURKISH",                    //15    T:φㄤ粂    S:土耳其        //
        "DEENS",            //"DANISH",                     //16    T:う沉粂      S:丹麦          //
        "ZWEEDS",           //"SWEDISH",                    //17    T:风ㄥ粂      S:瑞典          //
        "FINS",             //"FINNISH",                    //18    T:孽粂      S:芬兰          //
        "GRIEKS",           //"GREEK",                      //19    T:镁粂      S:希腊          //
        "NOORS",            //"NORWEGIAN",                  //20    T:粂      S:挪威          //
        "KOREAANS",         //"KOREAN",                     //21    T:龙粂        S:韩国          //
        "THAIS",                                            //22    T:粂        S:泰国          //
        "ITALIAANS",        //"ITALIAN",                    //23      S:意大利语                    //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSISCH",         //"RUSSIAN",                    //24      S:俄文                        //
        "INDONESISCH",      //"INDONESIAN",                 //25      S:印尼语Indonesian            //
        "INDONESISCH",      //"INDONESIAN",                 //26      S:印尼语Indonesian_new        //
        "ARABISCH",         //"ARABIC",                     //ARABIC                        //27
        "HEBREEUWS",        //"HEBRAIC",                    //Hebraic                       //28
        "HEBREEUWS",        //"HEBRAIC",                    //Hebraic                       //29
        "ROEMEENS",         //"ROMANIAN",                   //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_SWEDISH_OSD
//Swedish
{
        " ",                                                //0
        "ENGELSKA",         //"ENGLISH",                    //1     T:璣粂        S:英语          //

        "JAPANSKA",         //"JAPAN",                      //2     T:ら粂        S:日语          //

        "FRANSKA",          //"FRENCH",                     //3     T:猭粂        S:法语          //
        "PORTUGISISKA",     //"PORTUGUESE",                 //4     T:覆靛粂    S:葡萄牙        //
        "TYSKA",            //"GERMAN",                     //5     T:紈粂        S:德国          //
        "LATIN",            //"LATIN",                      //6     T:┰粂      S:拉丁          //
        "SPANSKA",          //"SPANISH",                    //7     T:﹁痁粂    S:西班牙        //
        "KINESISKA",            //"CHINESE",                    //8     T:簙粂        S:中文          //
        "POLSKA",           //"POLISH",                     //9     T:猧孽粂      S:波兰          //
        "TJECKISKA",            //"CZECH",                      //10    T:倍粂      S:捷克          //
        "UNGERSKA",         //"HUNGARIAN",                  //11    T:粂    S:匈牙利        //
        "ISL""\xc4""NDSKA",         //"ICELANDIC",                  //12    T:畄粂      S:冰岛          //
        "HINDI",            //"HINDI",                      //13    T:粂      S:印地          //
        "HOLL""\xc4""NDSKA",        //"DUTCH",                      //14    T:颤孽粂      S:荷兰          //
        "TURKISKA",         //"TURKISH",                    //15    T:φㄤ粂    S:土耳其        //
        "DANSKA",           //"DANISH",                     //16    T:う沉粂      S:丹麦          //
        "SVENSKA",          //"SWEDISH",                    //17    T:风ㄥ粂      S:瑞典          //
        "FINSKA",               //"FINNISH",                    //18    T:孽粂      S:芬兰          //
        "GREKISKA",         //"GREEK",                      //19    T:镁粂      S:希腊          //
        "NORSKA",           //"NORWEGIAN",                  //20    T:粂      S:挪威          //
        "KOREANSKA",            //"KOREAN",                     //21    T:龙粂        S:韩国          //
        "THAI",                                             //22    T:粂        S:泰国          //
        "ITALIENSKA",       //"ITALIAN",                    //23      S:意大利语                    //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RYSKA",            //"RUSSIAN",                    //24      S:俄文                        //
        "INDONESISCH",      //"INDONESIAN",                 //25      S:印尼语Indonesian            //
        "INDONESISCH",      //"INDONESIAN",                 //26      S:印尼语Indonesian_new        //
        "ARABISCH",         //"ARABIC",                     //ARABIC                        //27
        "HEBREEUWS",        //"HEBRAIC",                    //Hebraic                       //28
        "HEBREEUWS",        //"HEBRAIC",                    //Hebraic                       //29
        "ROEMEENS",         //"ROMANIAN",                   //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGISISKA",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_CZECH_OSD
//Czech
{
        " ",                                                //0
        "ENGLISH",          //"ENGLISH",                    //1     T:璣粂        S:英语          //

        "JAPAN",            //"JAPAN",                      //2     T:ら粂        S:日语          //

        "FRENCH",           //"FRENCH",                     //3     T:猭粂        S:法语          //
        "PORTUGUESE",       //"PORTUGUESE",                 //4     T:覆靛粂    S:葡萄牙        //
        "GERMAN",           //"GERMAN",                     //5     T:紈粂        S:德国          //
        "LATIN",            //"LATIN",                      //6     T:┰粂      S:拉丁          //
        "SPANISH",          //"SPANISH",                    //7     T:﹁痁粂    S:西班牙        //
        "CHINESE",          //"CHINESE",                    //8     T:簙粂        S:中文          //
        "POLISH",           //"POLISH",                     //9     T:猧孽粂      S:波兰          //
        "\x06""ESKY",           //"CZECH",                      //10    T:倍粂      S:捷克          //
        "HUNGARIAN",            //"HUNGARIAN",                  //11    T:粂    S:匈牙利        //
        "ICELANDIC",            //"ICELANDIC",                  //12    T:畄粂      S:冰岛          //
        "HINDI",            //"HINDI",                      //13    T:粂      S:印地          //
        "DUTCH",        //"DUTCH",                      //14    T:颤孽粂      S:荷兰          //
        "TURKISH",          //"TURKISH",                    //15    T:φㄤ粂    S:土耳其        //
        "DANISH",           //"DANISH",                     //16    T:う沉粂      S:丹麦          //
        "SWEDISH",          //"SWEDISH",                    //17    T:风ㄥ粂      S:瑞典          //
        "FINNISH",              //"FINNISH",                    //18    T:孽粂      S:芬兰          //
        "GREEK",            //"GREEK",                      //19    T:镁粂      S:希腊          //
        "NORWEGIAN",            //"NORWEGIAN",                  //20    T:粂      S:挪威          //
        "KOREAN",           //"KOREAN",                     //21    T:龙粂        S:韩国          //
        "THAI",                                             //22    T:粂        S:泰国          //
        "ITALIAN",      //"ITALIAN",                    //23      S:意大利语                    //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",          //"RUSSIAN",                    //24      S:俄文                        //
        "INDONESIAN",       //"INDONESIAN",                 //25      S:印尼语Indonesian            //
        "INDONESIAN",       //"INDONESIAN",                 //26      S:印尼语Indonesian_new        //
        "ARABIC",           //"ARABIC",                     //ARABIC                        //27
        "HEBRAIC",      //"HEBRAIC",                    //Hebraic                       //28
        "HEBRAIC",      //"HEBRAIC",                    //Hebraic                       //29
        "ROMANIAN",         //"ROMANIAN",                   //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif//#ifdef USE_CZECH_OSD

#ifdef USE_KOREAN_OSD
//KOREAN
{
        " ",                          //0
        KOS_ENGLISH,            //"INGLESE",                    //1     T:璣粂        S:英语          E:ENGLISH       //
        KOS_JAPAN,              //"GIAPPONESE",                 //2     T:ら粂        S:日语          E:JAPAN         //
        KOS_FRENCH,             //"FRANCESE",                   //3     T:猭粂        S:法语          E:FRENCH        //
        KOS_PORTUGUESE,         //"PORTOGHESE",                 //4     T:覆靛粂    S:葡萄牙        E:PORTUGUESE    //
        KOS_GERMAM,             //"TEDESCO",                    //5     T:紈粂        S:德国          E:GERMAN        //
        KOS_LATIN,              //"LATINO",                     //6     T:┰粂      S:拉丁          E:LATIN         //
        KOS_SPANISH,            //"SPAGNOLO",                   //7     T:﹁痁粂    S:西班牙        E:SPANISH       //
        KOS_CHINESE,            //"CINESE",                     //8     T:簙粂        S:中文          E:CHINESE       //
        KOS_POLISH,             //"POLACO",                     //9     T:猧孽粂      S:波兰          E:POLISH        //
        KOS_CZECH,              //"CECO",                       //10    T:倍粂      S:捷克          E:CZECH         //
        KOS_HUNGARIAN,          //"UNGARO",                     //11    T:粂    S:匈牙利        E:HUNGARIAN     //
        KOS_ICELANDIC,          //"ISLANDESE",                  //12    T:畄粂      S:冰岛          E:ICELANDIC     //
        KOS_HINDI,              //"INDI",                       //13    T:粂      S:印地          E:HINDI         //
        KOS_DUTCH,              //"OLANDESE",                   //14    T:颤孽粂      S:荷兰          E:DUTCH         //
        KOS_TURKISH,            //"TURCO",                      //15    T:φㄤ粂    S:土耳其        E:TURKISH       //
        KOS_DANISH,             //"DANESE",                     //16    T:う沉粂      S:丹麦          E:DANISH        //
        KOS_SWEDISH,            //"SVEDESE",                    //17    T:风ㄥ粂      S:瑞典          E:SWEDISH       //
        KOS_FINNISH,            //"FINLANDESE",                 //18    T:孽粂      S:芬兰          E:FINNISH       //
        KOS_GREEK,              //"GRECO",                      //19    T:镁粂      S:希腊          E:GREEK         //
        KOS_NORWEGIAN,          //"NORVEGESE",                  //20    T:粂      S:挪威          E:NORWEGIAN     //
        KOS_KOREAN,             //"COREANO",                    //21    T:龙粂        S:韩国          E:KOREAN        //
        KOS_THAI,               //"TAILANDESE",                 //22    T:粂        S:泰国          E:THAI          //
        KOS_ITALIAN,            //"ITALIANO",                   //23      S:意大利语                    E:ITALIAN       //
#ifndef MAX_OSD_LANG_STR_ID_25
        KOS_RUSSIAN,
        KOS_INDONESIAN,
        KOS_INDONESIAN,
        KOS_ARABIC,
        KOS_HEBRAIC,
        KOS_HEBRAIC,
        KOS_ROMANIAN,
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_DANISH_OSD
//DANISH
{
        " ",                          //0
        "ENGELSK",          //"INGLESE",                    //1     T:璣粂        S:英语          E:ENGLISH       //
        "JAPAN",                //"GIAPPONESE",                 //2     T:ら粂        S:日语          E:JAPAN         //
        "FRANSK",               //"FRANCESE",                   //3     T:猭粂        S:法语          E:FRENCH        //
        "PORTUGISER",           //"PORTOGHESE",                 //4     T:覆靛粂    S:葡萄牙        E:PORTUGUESE    //
        "TYSK",             //"TEDESCO",                    //5     T:紈粂        S:德国          E:GERMAN        //
        "LATINSK",              //"LATINO",                     //6     T:┰粂      S:拉丁          E:LATIN         //
        "SPANSK",           //"SPAGNOLO",                   //7     T:﹁痁粂    S:西班牙        E:SPANISH       //
        "KINESER",          //"CINESE",                     //8     T:簙粂        S:中文          E:CHINESE       //
        "POLSK",                //"POLACO",                     //9     T:猧孽粂      S:波兰          E:POLISH        //
        "TJEKKISK",             //"CECO",                       //10    T:倍粂      S:捷克          E:CZECH         //
        "UNGARSK",          //"UNGARO",                     //11    T:粂    S:匈牙利        E:HUNGARIAN     //
        "ISLANDSK",         //"ISLANDESE",                  //12    T:畄粂      S:冰岛          E:ICELANDIC     //
        "HINDUSK",              //"INDI",                       //13    T:粂      S:印地          E:HINDI         //
        "HOLLANDSK",                //"OLANDESE",                   //14    T:颤孽粂      S:荷兰          E:DUTCH         //
        "TYRKISK",          //"TURCO",                      //15    T:φㄤ粂    S:土耳其        E:TURKISH       //
        "DANSK",                //"DANESE",                     //16    T:う沉粂      S:丹麦          E:DANISH        //
        "SVENSK",           //"SVEDESE",                    //17    T:风ㄥ粂      S:瑞典          E:SWEDISH       //
        "FINSK",            //"FINLANDESE",                 //18    T:孽粂      S:芬兰          E:FINNISH       //
        "GR""\xc6""KER",                //"GRECO",                      //19    T:镁粂      S:希腊          E:GREEK         //
        "NORSK",            //"NORVEGESE",                  //20    T:粂      S:挪威          E:NORWEGIAN     //
        "KORANEN",              //"COREANO",                    //21    T:龙粂        S:韩国          E:KOREAN        //
        "THAILANDSK",               //"TAILANDESE",                 //22    T:粂        S:泰国          E:THAI          //
        "ITALIENER",            //"ITALIANO",                   //23      S:意大利语                    E:ITALIAN       //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSER",
       "INDONESISK",
        "INDONESISK",
        "ARABISK",
        "HEBRAISK",
        "HEBRAISK",
       "RUM""\xC6""NIENER",
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西 
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_THAI_OSD//jxlan 07/19
//THAI
{
        " ",                          //0
        COS_ENGLISH,                   //1     T:璣粂        S:英语          //
        COS_JAPAN,                     //2     T:ら粂        S:日语          //
        COS_FRENCH,                    //3     T:猭粂        S:法语          //
        COS_PORTUGUESE,                //4     T:覆靛粂    S:葡萄牙        //
        COS_GERMAN,                    //5     T:紈粂        S:德语          //
        COS_LATIN,                     //6     T:┰粂      S:拉丁语        //
        COS_SPANISH,                   //7     T:﹁痁粂    S:西班牙语      //
        COS_CHINESE,                   //8     T:簙粂        S:中文          //
        "POLISH",                     //9     T:猧孽粂      S:波兰          //
        "CZECH",                      //10    T:倍粂      S:捷克          //
        "HUNGARIAN",                  //11    T:粂    S:匈牙利        //
        "ICELANDIC",                  //12    T:畄粂      S:冰岛          //
        "HINDI",                      //13    T:粂      S:印地          //
        "DUTCH",                      //14    T:颤孽粂      S:荷兰          //
        "TURKISH",                    //15    T:φㄤ粂    S:土耳其        //
        "DANISH",                     //16    T:う沉粂      S:丹麦          //
        "SWEDISH",                    //17    T:风ㄥ粂      S:瑞典          //
        "FINNISH",                    //18    T:孽粂      S:芬兰          //
        "GREEK",                      //19    T:镁粂      S:希腊          //
        "NORWEGIAN",                  //20    T:粂      S:挪威          //
        "KOREAN",                     //21    T:龙粂        S:韩国          //
        COS_THAI,                       //22    T:粂        S:泰国          //
        "ITALIAN",                    //23    S:意大利语                    //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",                    //24    S:俄文                        //
        "INDONESIAN",                 //25    S:印尼语Indonesian            //
        "INDONESIAN",                 //26    S:印尼语Indonesian_new        //
        "ARABIC",                   //ARABIC                        //27
        "HEBRAIC",                  //Hebraic                       //28
        "HEBRAIC",                  //Hebraic                       //29
        "ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif//USE_THAI_OSD
//wsf add engelsk language 3-12-2 16:29
#ifdef USE_NORWAY_OSD
//Norwegian 
{
        " ",                          //0
        "ENGELSK",                    //1     T:璣粂        S:英语          //
        #if defined(HUAJIA_DVD)||defined(MINTON_DVD)
        "JAPANSK",                      //2     T:ら粂        S:日语          //
        #else
        "JAPAN",                      //2     T:ら粂        S:日语          //
        #endif
        "FRANSK",                     //3     T:猭粂        S:法语          //
        "PORTUGISISK",                 //4     T:覆靛粂    S:葡萄牙        //
        "TYSK",                     //5     T:紈粂        S:德国          //
        "LATINSK",                      //6     T:┰粂      S:拉丁          //
        "SPANSK",                    //7     T:﹁痁粂    S:西班牙        //
        "KINESISK",                    //8     T:簙粂        S:中文          //
        "POLSK",                     //9     T:猧孽粂      S:波兰          //
        "TSJEKKISK",                      //10    T:倍粂      S:捷克          //
        "UNGARSK",                  //11    T:粂    S:匈牙利        //
        "ISLANDSK",                  //12    T:畄粂      S:冰岛          //
        "HINDISK",                      //13    T:粂      S:印地          //
#if defined(HUAJIA_DVD)&&!defined(OSD_SHOW_DUTCH)
        "NETHERLAND",//"DUTCH",       // 3-12-1 23:44             //14    T:颤孽粂      S:荷兰          //
#else
        "NEDERLANDSK",                      //14    T:颤孽粂      S:荷兰          //
#endif
        "TYRKISK",                    //15    T:φㄤ粂    S:土耳其        //
        "DANSK",                     //16    T:う沉粂      S:丹麦          //
        "SVENSK",                    //17    T:风ㄥ粂      S:瑞典          //
        "FINSK",                    //18    T:孽粂      S:芬兰          //
        "GRESK",                      //19    T:镁粂      S:希腊          //
        "NORSK",                  //20    T:粂      S:挪威          //
        "KOREANSK",                     //21    T:龙粂        S:韩国          //
        "THAI",                       //22    T:粂        S:泰国          //
        "ITALIENSK",                    //23      S:意大利语                    //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIK",                    //24     S:俄文                        //
        "INDONESISK",                 //25    S:印尼语Indonesian            //
        "INDONESISK",                 //26    S:印尼语Indonesian_new        //
        "ARABISK",                  //ARABIC                        //27
        "HEBRAISK",                 //Hebraic                       //28
        "HEBRAISK",                 //Hebraic                       //29
        "ROMANSK",                  //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif

#ifdef USE_POLISH_OSD
//Polish
{
        " ",                          //0
        "ANGIELSKI",                    //1     T:璣粂        S:英语          //
        #if defined(HUAJIA_DVD)||defined(MINTON_DVD)
        "JAPO""\r\xa4""SKI",                      //2     T:ら粂        S:日语          //
        #else
        "JAPNIA",                      //2     T:ら粂        S:日语          //
        #endif
        "FRANCUSKI",                     //3     T:猭粂        S:法语          //
        "PORTUGALSKI",                 //4     T:覆靛粂    S:葡萄牙        //
        "NIEMIECKI",                     //5     T:紈粂        S:德国          //
        "\r\xa3""ACINA",                      //6     T:┰粂      S:拉丁          //
        "HISZPA""\r\xa4""SK""\r\xa2",                    //7     T:﹁痁粂    S:西班牙        //
        "CHI""\r\xa4""SKI",                    //8     T:簙粂        S:中文          //
        "POLSKI",                     //9     T:猧孽粂      S:波兰          //
        "CZESKI",                      //10    T:倍粂      S:捷克          //
        "W""\r\xa1""GIERSKI",                  //11    T:粂    S:匈牙利        //
        "ISLANDZKI",                  //12    T:畄粂      S:冰岛          //
        "HINDU",                      //13    T:粂      S:印地          //
    #if defined(HUAJIA_DVD)&&!defined(OSD_SHOW_DUTCH)
        "NETHERLAND",//"DUTCH",                      //14    T:颤孽粂      S:荷兰          //
    #else
        "NIDERLANDZKI",                      //14    T:颤孽粂      S:荷兰          //
    #endif
        "TURECKI",                    //15    T:φㄤ粂    S:土耳其        //
        "DU""\r\xa4""SKI",                     //16    T:う沉粂      S:丹麦          //
        "SZWEDZKI",                    //17    T:风ㄥ粂      S:瑞典          //
        "FI""\r\xa4""SKI",                    //18    T:孽粂      S:芬兰          //
        "GRECKI",                      //19    T:镁粂      S:希腊          //
        "NORWESKI",                  //20    T:粂      S:挪威          //
        "KOREA""\r\xa4""SKI",                     //21    T:龙粂        S:韩国          //
        "TAJSKI",                       //22    T:粂        S:泰国          //
        "W""\r\xa3""OSKI",                    //23    S:意大利语                    //
    #ifndef MAX_OSD_LANG_STR_ID_25
        "ROSYJSKI",                    //24   S:俄文                        //
        "INDONEZYJSKI",                 //25      S:印尼语Indonesian            //
        "INDONEZYJSKI",                 //26      S:印尼语Indonesian_new        //
        "ARABSKI",                  //ARABIC                        //27
        "HEBRAJSKI",                    //Hebraic                       //28
        "HEBRAJSKI",                    //Hebraic                       //29
        "RUMU""\r\xa4""SKI",                    //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
    #endif
        " ",                                                         //37
},
#endif
//HUNGARIAN_OSD zhuyf add 30/12/2004 17:17
#ifdef USE_HUNGARIAN_OSD
//Hungarian
{
        " ",                          //0
        "ANGOL",                    //1     T:璣粂        S:英语          //
        #if defined(HUAJIA_DVD)||defined(MINTON_DVD)
        "JAPANESE",                      //2     T:ら粂        S:日语          //
        #else
        "JAP""\xc1""N",//"JAPAN",                      //2     T:ら粂        S:日语          //
        #endif
        "FRANCIA",                     //3     T:猭粂        S:法语          //
        "PORTUG""\xc1""L",//"PORTUGUESE",                 //4     T:覆靛粂    S:葡萄牙        //
        "N""\xc9""MET",//"GERMAN",                     //5     T:紈粂        S:德国          //
        "LATIN",                      //6     T:┰粂      S:拉丁          //
        "SPANYOL",                    //7     T:﹁痁粂    S:西班牙        //
        "K""\xcd""NAI",//"CHINESE",                    //8     T:簙粂        S:中文          //
        "POLISH",                     //9     T:猧孽粂      S:波兰          //
        "CZECH",                      //10    T:倍粂      S:捷克          //
        "HUNGARIAN",                  //11    T:粂    S:匈牙利        //
        "ICELANDIC",                  //12    T:畄粂      S:冰岛          //
        "HINDI",                      //13    T:粂      S:印地          //
#if defined(HUAJIA_DVD)&&!defined(OSD_SHOW_DUTCH)
        "NETHERLAND",//"DUTCH",                      //14    T:颤孽粂      S:荷兰          //
#else
        "DUTCH",                      //14    T:颤孽粂      S:荷兰          //
#endif
        "TURKISH",                    //15    T:φㄤ粂    S:土耳其        //
        "DANISH",                     //16    T:う沉粂      S:丹麦          //
        "SWEDISH",                    //17    T:风ㄥ粂      S:瑞典          //
        "FINNISH",                    //18    T:孽粂      S:芬兰          //
        "GREEK",                      //19    T:镁粂      S:希腊          //
        "NORWEGIAN",                  //20    T:粂      S:挪威          //
        "KOREAN",                     //21    T:龙粂        S:韩国          //
        "THAI",                       //22    T:粂        S:泰国          //
        "ITALIAN",                    //23    S:意大利语                    //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",                    //24    S:俄文                        //
        "INDONESIAN",                 //25    S:印尼语Indonesian            //
        "INDONESIAN",                 //26    S:印尼语Indonesian_new        //
        "ARABIC",                   //ARABIC                        //27
        "HEBRAIC",                  //Hebraic                       //28
        "HEBRAIC",                  //Hebraic                       //29
        "ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif
#ifdef USE_ARABIC_OSD
//English
{
        " ",                          //0
        "\r\x50",//"ENGLISH",                    //1     T:璣粂        S:英语          //
        #if defined(HUAJIA_DVD)||defined(MINTON_DVD)
        "\r\x48",//JAPANESE",                      //2     T:ら粂        S:日语          //
        #else
        "\r\x4c",//"JAPAN",                      //2     T:ら粂        S:日语          //
        #endif
        "\r\x52",//"FRENCH",                     //3     T:猭粂        S:法语          //
        "\r\x59",//"PORTUGUESE",                 //4     T:覆靛粂    S:葡萄牙        //
        "\r\x53",//"GERMAN",                     //5     T:紈粂        S:德国          //
        "\r\x5c",//"LATIN",                      //6     T:┰粂      S:拉丁          //
        "\r\x62",//"SPANISH",                    //7     T:﹁痁粂    S:西班牙        //
        "\r\x60",//"CHINESE",                    //8     T:簙粂        S:中文          //
        "\r\x61",//"POLISH",                     //9     T:猧孽粂      S:波兰          //
        "\r\x4d",//"CZECH",                      //10    T:倍粂      S:捷克          //
        "\r\x5a",//"HUNGARIAN",                  //11    T:粂    S:匈牙利        //
        "ICELANDIC",                  //12    T:畄粂      S:冰岛          //
        "\r\x58",//"HINDI",                      //13    T:粂      S:印地          //
#if defined(HUAJIA_DVD)&&!defined(OSD_SHOW_DUTCH)
        "NETHERLAND",//"DUTCH",                      //14    T:颤孽粂      S:荷兰          //
#else
        "\r\x4f",//"DUTCH",                      //14    T:颤孽粂      S:荷兰          //
#endif
        "\r\x64",//"TURKISH",                    //15    T:φㄤ粂    S:土耳其        //
        "\r\x4e",//"DANISH",                     //16    T:う沉粂      S:丹麦          //
        "SWEDISH",                    //17    T:风ㄥ粂      S:瑞典          //
        "\r\x51",//"FINNISH",                    //18    T:孽粂      S:芬兰          //
        "\r\x54",//"GREEK",                      //19    T:镁粂      S:希腊          //
        "NORWEGIAN",                  //20    T:粂      S:挪威          //
        "\r\x5b",//"KOREAN",                     //21    T:龙粂        S:韩国          //
        "\r\x63",//"THAI",                       //22    T:粂        S:泰国          //
        "ITALIAN",                    //23    S:意大利语                    //
#ifndef MAX_OSD_LANG_STR_ID_25
        "\r\xe5",//"RUSSIAN",                    //24    S:俄文                        //
        "INDONESIAN",                 //25    S:印尼语Indonesian            //
        "INDONESIAN",                 //26    S:印尼语Indonesian_new        //
        "\r\x5d",//"ARABIC",                   //ARABIC                        //27
        "\r\x57",//"HEBRAIC",                  //Hebraic                       //28
        "\r\x57",//"HEBRAIC",                  //Hebraic                       //29
        "\r\xe4",//"ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},
#endif
#ifdef USE_GREECE_OSD
//English
{
        " ",                          //0
        "ENGLISH",                    //1     T:璣粂        S:英语          //
        #if defined(HUAJIA_DVD)||defined(MINTON_DVD)
        "JAPANESE",                      //2     T:ら粂        S:日语          //
        #else
        "JAPAN",                      //2     T:ら粂        S:日语          //
        #endif
        "FRENCH",                     //3     T:猭粂        S:法语          //
        "PORTUGUESE",                 //4     T:覆靛粂    S:葡萄牙        //
        "GERMAN",                     //5     T:紈粂        S:德国          //
        "LATIN",                      //6     T:┰粂      S:拉丁          //
        "SPANISH",                    //7     T:﹁痁粂    S:西班牙        //
        "CHINESE",                    //8     T:簙粂        S:中文          //
        "POLISH",                     //9     T:猧孽粂      S:波兰          //
        "CZECH",                      //10    T:倍粂      S:捷克          //
        "HUNGARIAN",                  //11    T:粂    S:匈牙利        //
        "ICELANDIC",                  //12    T:畄粂      S:冰岛          //
        "HINDI",                      //13    T:粂      S:印地          //
#if defined(HUAJIA_DVD)&&!defined(OSD_SHOW_DUTCH)
        "NETHERLAND",//"DUTCH",                      //14    T:颤孽粂      S:荷兰          //
#else
        "DUTCH",                      //14    T:颤孽粂      S:荷兰          //
#endif
        "TURKISH",                    //15    T:φㄤ粂    S:土耳其        //
        "DANISH",                     //16    T:う沉粂      S:丹麦          //
        "SWEDISH",                    //17    T:风ㄥ粂      S:瑞典          //
        "FINNISH",                    //18    T:孽粂      S:芬兰          //
        "GREEK",                      //19    T:镁粂      S:希腊          //
        "NORWEGIAN",                  //20    T:粂      S:挪威          //
        "KOREAN",                     //21    T:龙粂        S:韩国          //
        "THAI",                       //22    T:粂        S:泰国          //
        "ITALIAN",                    //23    S:意大利语                    //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",                    //24    S:俄文                        //
        "INDONESIAN",                 //25    S:印尼语Indonesian            //
        "INDONESIAN",                 //26    S:印尼语Indonesian_new        //
        "ARABIC",                   //ARABIC                        //27
        "HEBRAIC",                  //Hebraic                       //28
        "HEBRAIC",                  //Hebraic                       //29
        "ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
        "SLOVENIAN",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                        //37
},
#endif  //USE_GREECE_OSD

#ifdef USE_BRAZIL_OSD
//Brazil
{
        " ",                          //0
        "INGL""\xca""S",//"ENGLISH",                    //1     T:璣粂        S:英语          //
        #if defined(HUAJIA_DVD)||defined(MINTON_DVD)
        "\r\x48",//JAPANESE",                      //2     T:ら粂        S:日语          //
        #else
        "JAPON""\xca""S",//"JAPAN",                      //2     T:ら粂        S:日语          //
        #endif
        "FRANC""\xca""S",//"FRENCH",                     //3     T:猭粂        S:法语          //
        "PORTUGU""\xca""S",//"PORTUGUESE",                 //4     T:覆靛粂    S:葡萄牙        //
        "ALEM""\xc3""O",//"GERMAN",                     //5     T:紈粂        S:德国          //
        "LATIM",//"LATIN",                      //6     T:┰粂      S:拉丁          //
        "ESPANHOL",//"SPANISH",                    //7     T:﹁痁粂    S:西班牙        //
        "CHIN""\xca""S",//"CHINESE",                    //8     T:簙粂        S:中文          //
        "POLON""\xca""S",//"POLISH",                     //9     T:猧孽粂      S:波兰          //
        "TCHECO",//"CZECH",                      //10    T:倍粂      S:捷克          //
        "H""\xda""NGARO",//"HUNGARIAN",                  //11    T:粂    S:匈牙利        //
        "GROENLAND""\xca""S",                  //12    T:畄粂      S:冰岛          //
        "INDU",//"HINDI",                      //13    T:粂      S:印地          //
#if defined(HUAJIA_DVD)&&!defined(OSD_SHOW_DUTCH)
        "HOLAND""\xca""S",//"DUTCH",                      //14    T:颤孽粂      S:荷兰          //
#else
        "HOLAND""\xca""S",//"DUTCH",                      //14    T:颤孽粂      S:荷兰          //
#endif
        "TURCO",//"TURKISH",                    //15    T:φㄤ粂    S:土耳其        //
        "DINAMARQU""\xca""S",//"DANISH",                     //16    T:う沉粂      S:丹麦          //
        "SUECO",                    //17    T:风ㄥ粂      S:瑞典          //
        "FINLAND""\xca""S",//"FINNISH",                    //18    T:孽粂      S:芬兰          //
        "GREGO",//"GREEK",                      //19    T:镁粂      S:希腊          //
        "NORUEGU""\xca""S",                  //20    T:粂      S:挪威          //
        "COREANO",//"KOREAN",                     //21    T:龙粂        S:韩国          //
        "TAILAND""\xca""S",//"THAI",                       //22    T:粂        S:泰国          //
        "ITALIANO",                    //23    S:意大利语                    //
#ifndef MAX_OSD_LANG_STR_ID_25
        "\r\xe5",//"RUSSIAN",                    //24    S:俄文                        //
        "INDONESIAN",                 //25    S:印尼语Indonesian            //
        "INDONESIAN",                 //26    S:印尼语Indonesian_new        //
        "\r\x5d",//"ARABIC",                   //ARABIC                        //27
        "\r\x57",//"HEBRAIC",                  //Hebraic                       //28
        "\r\x57",//"HEBRAIC",                  //Hebraic                       //29
        "\r\xe4",//"ROMANIAN",                 //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "CROATIAN",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "PORTUGU\xcaS",					//BRAZIL 巴西
#endif
        " ",                                                        //36
},
#endif

#ifdef USE_SLOVENIAN_OSD                //felix 2005-9-29 11:22
//SLOVENIAN
{
        " ",                                                //0
        "ANGLE""\x85""KI",          //"ENGLISH",                    //1     T:璣粂        S:英语          //

        "JAPONSKI",            //"JAPAN",                      //2     T:ら粂        S:日语          //

        "FRANCOSKI",           //"FRENCH",                     //3     T:猭粂        S:法语          //
        "PORTUGALSKI",       //"PORTUGUESE",                 //4     T:覆靛粂    S:葡萄牙        //
        "NEM""\x85""KI",           //"GERMAN",                     //5     T:紈粂        S:德国          //
        "LATINSKI",            //"LATIN",                      //6     T:┰粂      S:拉丁          //
        "\x85""PANSKI",          //"SPANISH",                    //7     T:﹁痁粂    S:西班牙        //
        "KITAJSKI",          //"CHINESE",                    //8     T:簙粂        S:中文          //
        "POLJSKI",           //"POLISH",                     //9     T:猧孽粂      S:波兰          //
        "\x06""E""\x85""KI",           //"CZECH",                      //10    T:倍粂      S:捷克          //
        "MAD""\xf7""ARSKI",            //"HUNGARIAN",                  //11    T:粂    S:匈牙利        //
        "ISLANDSKI",            //"ICELANDIC",                  //12    T:畄粂      S:冰岛          //
        "HINDUJSKI",            //"HINDI",                      //13    T:粂      S:印地          //
        "NIZOZEMSKI",        //"DUTCH",                      //14    T:颤孽粂      S:荷兰          //
        "TUR""\x85""KI",          //"TURKISH",                    //15    T:φㄤ粂    S:土耳其        //
        "DANSKI",           //"DANISH",                     //16    T:う沉粂      S:丹麦          //
        "\x85""VEDSKI",          //"SWEDISH",                    //17    T:风ㄥ粂      S:瑞典          //
        "FINSKI",              //"FINNISH",                    //18    T:孽粂      S:芬兰          //
        "GR""\x85""KI",            //"GREEK",                      //19    T:镁粂      S:希腊          //
        "NORVE""\x85""KI",            //"NORWEGIAN",                  //20    T:粂      S:挪威          //
        "KOREJSKI",           //"KOREAN",                     //21    T:龙粂        S:韩国          //
        "TAJSKI",                                             //22    T:粂        S:泰国          //
        "ITALIJANSKI",      //"ITALIAN",                    //23      S:意大利语                    //
#ifndef MAX_OSD_LANG_STR_ID_25
        "RUSSIAN",          //"RUSSIAN",                    //24      S:俄文                        //
        "INDONESIAN",       //"INDONESIAN",                 //25      S:印尼语Indonesian            //
        "INDONESIAN",       //"INDONESIAN",                 //26      S:印尼语Indonesian_new        //
        "ARABIC",           //"ARABIC",                     //ARABIC                        //27
        "HEBRAIC",      //"HEBRAIC",                    //Hebraic                       //28
        "HEBRAIC",      //"HEBRAIC",                    //Hebraic                       //29
        "ROMANIAN",         //"ROMANIAN",                   //ROMANIAN                      //30
        "BULGARIAN",                //BULGARIAN  S:保加利亚         //31
        "HRVA""\x85""KO",                 //CROATIAN   S:克罗地亚         //32
        "ESTONIAN",                 //ESTONIAN   S:爱沙尼亚         //33
        "LITHUANIAN",               //LITHUANIAN S:立陶宛           //34
        "LATVIAN",                  //LATVIAN    S: 拉脱维亚           //35
        "SLOVENSKO",                //SLOVENIAN  S:斯洛文尼亚        //36
#endif
        " ",                                                         //37
},       
#endif

};

//
//
//
#define make_639(a,b)   (((a)<<8) | (b))

const UINT16 lang_639code[]={
 0,
 make_639('e','n'),        //English
 make_639('j','a'),        //Japanese
 make_639('f','r'),        //French
 make_639('p','t'),        //Portuguese
 make_639('d','e'),        //German
 make_639('l','a'),        //Latin
 make_639('e','s'),        //Spanish
 make_639('z','h'),        //Chinese
 make_639('p','l'),        //Polish
 make_639('c','s'),        //Czech
 make_639('h','u'),        //Hungarian
 make_639('i','s'),        //Icelandic
 make_639('h','i'),        //Hindi
 make_639('n','l'),        //Dutch
 make_639('t','r'),        //Turkish
 make_639('d','a'),        //Danish
 make_639('s','v'),        //Swedish
 make_639('f','i'),        //Finnish
 make_639('e','l'),        //Greek
 make_639('n','o'),        //Norwegian
 make_639('k','o'),        //Korean
 make_639('t','h'),        //Thai
 make_639('i','t'),        //Italian
#ifndef MAX_OSD_LANG_STR_ID_25
 make_639('r','u'),        //Russian
 make_639('i','n'),        //Indonesian
 make_639('i','d'),        //Indonesian_new
 make_639('a','r'),        //arabic
 make_639('h','e'),        //hebrew_new
 make_639('i','w'),        //hebrew
 make_639('r','o'),        //romanian
 make_639('b','g'),        //Bulgarian
 make_639('h','r'),        //Croation
 make_639('e','t'),        //Estonian
 make_639('l','t'),        //Lithuanian
 make_639('l','v'),        //Latin   36
 make_639('b','r'),        //brazil   37
 make_639('s','l'),        //SLOVENIAN  38
 
#endif
 0,           //38
};


//
// OSD MESSAGES
//
//const char *const _OsdMessegeFont1[N_OSD_LANGS][256]={
const char *const _OsdMessegeFont1[N_OSD_LANGS][MAX_OSD_STR_ID]={//nono 2-7-8 17:43

#ifdef USE_ENGLISH_OSD
//English
{
        "",                   //0
        "NO DISC",            //1     T:(礚盒)            S:(无碟)
        #if defined(SKYWORTH_DVD)||defined(BBK_DVD)||defined(INVALID_DISPLAY_HAND)     //#ifdef ALWAYS_DISPLAY_NODISC_ICON    fengjl add 3-12-7 14:28
        OS_NO,
        #else
        "INVALID KEY",        //2     T:(眤岿 hand)   S:(您按错了 HAND)
        #endif
        "TRK",                //3     T:(Ρヘ)            S:(曲目)
        OS_ICON_SVCD,         //4
        "DE-INTERLACE",//"CHINESE",            //5  not use
        "OPEN",               //6     T:()            S:(出仓)
        "CLOSE",              //7     T:(闽)            S:(关仓)
        "PLAY",               //8     T:(冀)            S:(播放)
        "REGION 5",           //9     T:(5 跋)            S:(5区)
        "PAUSE",              //10    T:(既氨)            S:(暂停)
        "RANDOM",             //11    T:(繦诀冀)        S:(随即播放)
        "RESUME",             //12    T:(確冀)        S:(恢复播放)
        "STOP",               //13    T:(氨ゎ)            S:(停止)
        "STEP",               //14    T:(˙秈)            S:(单步)
        "SELECT",             //15    T:(匡拒)            S:(选择)

        #if defined(FUSS_DVD)||defined(HUAJIA_DVD)||defined(HIMAGE_CARD_READER)||defined(MINTON_DVD)   //NONO 2-5-15 3:01
            "LOADING",        //16    T:(弄盒)            S:(读碟)
        #elif defined(BBK_DVD)   //fengjl add 
            "READING",       //16     T:(弄盒)            S:(读碟)
        #elif defined(SETUP_DONGLI459)||defined(KENLOON_DVD)||defined(SHOW_LOAD_WHEN_READ)   //YAOWH  04-07-30
            "LOAD",
        #else
            "READ",           //16    T:(弄盒)            S:(读碟)
        #endif

        "REGION 6",           //17    T:(6 跋)
        
        #ifdef NO_SPDIF
        #ifdef HIMAGE1251    //fengjl add 2004-02-20 20:36
        "SPDIF/OFF",
        #else
        "ANALOG",             //18    T:(家览)
        #endif
        #else//NO_SPDIF
        "SPDIF/OFF",             //18    T:(家览)
        #endif//NO_SPDIF
        
        #ifdef HJ_APEX_FIX_SHOW_OSD
        "FF",            //19    T:(е秈)
        "FR",           //20    T:(е癶)
        #else//HJ_APEX_FIX_SHOW_OSD
        "FORWARD",            //19    T:(е秈)
        "BACKWARD",           //20    T:(е癶)
        #endif//HJ_APEX_FIX_SHOW_OSD
        "NEXT",               //21    T:(Ρ >>)

        #if defined(SETUP_PASSWORD_GUI)      //fengjl add  4-1-19 17:09
        "PASSWD EDIT",      // 22
        #elif defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "VGA",                  //22
        #else
        "SERVO DEBUG",        //22          //joshua, 20050711, modified for servo-debug function on OSD
        #endif
        
        "PREV",               //23    T:(Ρ <<)

        "DIR",               //24

        "RETURN",             //25    T:(垫虫)
        Ch_repx,              //26
        Ch_rep1,              //27
        Ch_repd,              //28
        "OFF",                //29    T:(礚)              S:(无)
        "MENU",               //30    T:(匡虫)            S:(选单)
        "SCORE",              //31    T:(だ计)            S:(分数)
#ifdef  ONE_KEY_PASS
        "SAVING THE POINT",  //32    T:(癘拘)            S:(记忆)
#else
        "MARK",               //32    T:(癘拘)            S:(记忆)
#endif

        "BROWSE",             //33    T:(聅凝)            S:(浏览)
        "PROG",               //34    T:(絪祘)            S:(编程)
        "SAVING LOGO...",     //35    T:                  S:(画面抓取中)
        #ifdef SPEAKER_CONFIG	
        "LARGE",	         //36	T:()
        #else
        "ALL LG SPK",         //36    T:(家Α1)
        #endif        
        "REP",                //37    T:(確)
        "REP DIR",            //38    T:(ヘ魁確)
        "REP 1",              //39    T:(虫Ρ確)
        "REP ALL",            //40    T:(盒確)
        "REP CANCEL",         //41    T:(確)
        #ifdef SPEAKER_CONFIG
       "SMALL",                //42    T:()
        #else
        "ALL SM SPK",         //42    T:(家Α2)
        #endif
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
        #else//#ifdef HJ_APEX_FIX_SHOW_OSD
        "8 ADULT",            //43
        #endif//#ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",
        #endif
        "7 NC-17",            //44    T:(虫Ρ冀)
        "GOTO",               //45    T:(穓)
        "MUTE",               //46    T:(繰)
        "MONO L",             //47    T:(オ羘笵)
        "MONO R",             //48    T:(羘笵)
        "STEREO",             //49    T:(ミ砰羘)
#ifdef HANYANG_MUTEOFF      //caohui 2004-5-13 15:59
        "MUTE OFF",                   //50    //not use
#else
        "DEMUTE",                   //50    //not use
#endif
        "LIVE",               //51    T:
#ifdef QSI_SETUP_MENU//liweihua 2004-6-16
        "KARAOK SETUP",                   //52

#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-23 22:03zhoulin
       "KARAOK SETUP",                   //52

#else
        "",                   //52    //not use
#endif
        #ifdef SPEAKER_CONFIG
        "OFF",                //53	T:(闽)
        #else
        "MIXED SPK",          //53    T:(家Α3)
        #endif 
        OS_ICON_CDROM,        //54
        #ifdef OP_CUST_UI//libing 2005-5-11 11:39
        "JPEG TIME",               //55    T:(丁)            S:(时间)
        #else
        "TIME",                       //55
        #endif
#ifdef RECORD_KEY
    #ifdef NINTAUS_OSD_STR    //2004-2-11 11:35张宇P
           "THE DISC HAS RECORD.",
     #else
        "THE DISC HAS RECORD POINT", //56
      #endif
#elif defined(SUPPORT_ANGLE_MARK)
        "ANGLE MARK",                   //56    S:(角度标记)
#elif defined(SHOW_MP4_INIT_STR)    //wangwei-2004/4/28
        "INITIALIZING...",                 //56 
#elif defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "XGA",                  //56
#elif defined(SCALER_6500)
        "XGA",                  //56             
#else
        "",                   //56    //not use
#endif
        "ZOOM",               //57    T:(糴)            S:(放宽)
#ifdef RECORD_KEY
        #ifdef NINTAUS_OSD_STR    //2004-2-11 11:35张宇P
           "PLEASE PRESS RECORD KEY TO PLAY IT.",
     #else
        "MEM KEY:JUMP TO THE SAVED POINT",//58
      #endif
#elif defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#elif defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "SXGA",                 //58
#elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-19 17:13 zhoulin
         "VOL_SR",
#elif defined(SCALER_6500)      //helm for 6500
//        "SXGA",                 //58
        "480I",                  //58           
#elif defined(DOWNMIX_OFF_DISP_5CH_ON)
        "5.1CH ON",            //58 ZXB2005-4-27 16:21       
#else
        "",                   //58    //not use
#endif     
        OS_ICON_LANG,         //59
        "INTRO",              //60    T:(苯磞)            S:(扫描)
        "SRND",//"SURROUND",           //61    T:(吏露)            S:(环绕)
        "PBC",                //62
#ifdef RECORD_KEY
       #ifdef NINTAUS_OSD_STR    //2004-2-11 11:35张宇P
           "IT WILL BE AUTO PLAYED AFTER 6S.",
     #else
        "OTHER KEY:PLAY FROM BEGINNING",  //63
          #endif
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
       Ch_repf,       //63         //zhuyf 2004/8/10

#else//DIVIDE_AC3_DTS_SPDIF_OUTPUTS
        "",            //63    T:(抖冀)
#endif     
        "RAND CANCEL",        //64    T:(繦诀冀)    S:(随即播放取消)
        "BASS MODE",          //65    T:(家Α)
       #ifdef SUPPORT_TESTSPK
        "TESTSPK",                   //66
       #else
        "",                   //66
       #endif
        "REPEAT A-",          //67    T:(確A-)          S:(重复 A )
        #ifdef JIEKE_DVD
        "P-SCAN VGA",               //"PC-VGA",           //68
        #elif (defined(NINTAUS_OSD_STR)||defined(AD_TCL))//2004-3-22 13:21 lijd
        "VGA",
        #else
        "PC-VGA",               //"PC-VGA",           //68
        #endif
        "REPEAT A-B",         //69    T:(確A-B)         S:(重复播放A-B)
#ifdef BBK_DVD
        "AB CANCEL",         //70    T:(確)        S:(A-B取消)
#else
        "A-B CANCEL",         //70    T:(確)        S:(A-B取消)
#endif
        "PRG CANCEL",         //71    T:(絪胆)            S:(编程取消)
        "",                   //72
#ifdef ONE_KEY_PASS
        "ONE KEY PLAY",      //73
#elif defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "576P/480P",             //73
#elif defined(SCALER_6500)
        "576P",             //73          
#elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-19 17:13 zhoulin
        "VOL_CT",
#elif defined(EASTECH_NO_PARENTAL_CONTROL)
        "  NO PARENTAL",    //73
#else
        "",            //73    T:(璣粂)            S:(英文)
#endif
#ifdef PULIANG_DVD  //yaowh add 04-12-17
        "VCD1.0",           //74
#else
        OS_ICON_VCD,          //74
#endif

#if defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "720P",                  //75
#elif defined(SCALER_6500)       //helm for 6500
        "720P",                  //75         
#else
        "LIGHT MUSIC",                   //75    
#endif
        #if defined(SHOW_VCD_VER_INFO)||defined(SYBER_DVD)  //yaowh add for kenloon 04-08-03
    #ifdef PULIANG_DVD  //yaowh add 04-12-17
        "VCD2.0",           //76
    #else
        OS_ICON_VCD20,        //76    //xulf 2003-11-17
    #endif
        #else        
        "ELECTRON",                   //76   
        #endif
        "CVBS",//OS_ICON_MP3,          //77
        OS_ICON_CDDA,         //78
#ifdef NINTAUS_OSD_STR   
        "48KHZ",                   //79    //not use
        "96KHZ",                   //80    //not use
        "192KHZ",                   //81    //not use
#else
        "48K",                   //79    //not use
        "96K",                   //80    //not use
        "192K",                   //81    //not use
#endif
        "ZOOM UP",            //82    T:(礶簿)        S:(放大上)
        "ZOOM DOWN",          //83    T:(礶簿)        S:(放大下)
        "ZOOM LEFT",          //84    T:(礶オ簿)        S:(放大左)
        "ZOOM RIGHT",         //85    T:(礶簿)        S:(放大右)
        "CH",                 //86    T:(彻竊)            S:(章节)
        "ECHO",               //87    T:(睼臫)            S:(混响)
        "TT",                 //88    T:(夹肈)            S:(标题)
        "BAND",               //89    T:(繵眯)
#ifdef OSD_BMP_REGION1
        "VOULUME",			  //90    T:(秖)            S:(音量)
#elif defined( DISPLAY_INDIVIDUAL_SPK_VOLUME)   
        "VOL",
#else        
        "VOL",                //90    T:(秖)            S:(音量)
#endif
        "DOWN SAMPLE",        //91    //not use
        "KEY",                //92    T:(秸)            S:(音调)

        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif

        "9FRAME_1",           //94    T:(虫Ρ礶)      S:(单曲九画面)
        "AUTO L",             //95    T:(笆钡佰オ)      S:(自动接唱左)
        "AUTO R",             //96    T:(笆钡佰)      S:(自动接唱右)
        "LOW",                //97    // LOW

            "SEQ PLAY",           //98    T:(抖冀)        S:(顺序播放)

        "MENU PLAY",          //99    T:(垫虫冀)        S:(菜单播放)
#ifdef DIV_GOTO_DISPLAY
        "DISC TIME",          //100
#else
        "LFE OUT",            //100
#endif

#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)
        "  COMMON ",       //101
        "PROFESSION",      //102
#elif defined(NINTAUS_OSD_STR)
    "UP-DOWN",
    "LEFT-RIGHT",           
#elif defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102              
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#elif defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "SVGA",             //101
        "1080I",                 //102
#elif defined(SCALER_6500)
//        "SVGA",              //101
        "1080P",             //101
        "1080I",                 //102         
#elif defined(SLEEP_CONTROL_COUNTER)  //ADD XHR 
        "120 MIN",
        "90  MIN",
#else
        "STANDARD",           //101
        "ENHANCE",            //102
#endif
 		#ifdef OP_CUST_UI
        "DIVX ID",                      //103
        #else
        "MEDIUM",             //103   // MEDIUM
        #endif
#ifdef MINTON_DVD
        "PROGRAM PLAY",           //104   T:(絪导僵)          S:(编程播放)
#else
        "PRG PLAY",           //104   T:(絪导僵)          S:(编程播放)
#endif
        "HIGH",               //105   // HIGH
        "DYNAMIC RANGE",      //106
        OS_ICON_DVD,          //107
        "OSD LANGUAGE",       //108   T:(礶陪ボ粂ē)    S:(画面显示语言)
        OS_ICON_SUBT,         //109

        #ifdef SETUP_DONGLI459   //oujx for tonic
        "TV SYSTEM",          //111   T:(1qμ??÷¨?|?)      S:(μ?êó?ú??ê?)
        "TV TYPE",            //110   T:(辊礶ゑㄒ)    S:(屏幕画面比例)
        #elif defined(MINTON_DVD)
        "TV TYPE",            //110   T:(?¨?1?|ìe-?à?è??§¨°)    S:(?¨￠???-???à¨¨¨¤y)
        "TV MODE",        //111   T:(1q|ì?????§?|?)      S:(|ì?¨o¨??¨2??¨o?)
        #elif defined(SUPPORT_FUNCTION_MENU)
        "LCD MODE",           //110   
        "TV SYSTEM",          //111                 
        #else
        "TV TYPE",            //110   T:(?¨?1?|ìe-?à?è??§¨°)    S:(?¨￠???-???à¨¨¨¤y)
        #if defined(MUSTEK_PORTABLE_DVD)&&!defined(MUSTEK_K100D_MODEL)
		"ANGLE MARK", 			//111
		#else
        "TV SYSTEM",          //111   T:(1q|ì?????§?|?)      S:(|ì?¨o¨??¨2??¨o?)
        #endif
        #endif

        "EXIT SETUP",         //112   T:(癶砞竚垫虫)    S:(推出设置菜单)
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#elif defined(EASTECH_NEW_SETUP_MENU)||defined(MUSTEK_PORTABLE_DVD)||defined(PULIANG_DVD)||defined(DP3240_SETUP_MENU)  //yaowh modify 04-12-17
        "DIGITAL OUT",          //113   T:(计絏块)        S:(数码输出)
#else
        "AUDIO OUT",          //113   T:(计絏块)        S:(数码输出)
#endif//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)

		#if defined(MUSTEK_PORTABLE_DVD)
		"VIDEO OUTPUT", 		//114
              #elif defined(DP3240_SETUP_MENU)
		"VIDEO OUT",              //114   T:(跌繵块)        S:(视频输出)
		#else
        "VIDEO",              //114   T:(跌繵块)        S:(视频输出)
        #endif
        "PASSWORD",           //115   T:(盞絏)            S:(密码)

#ifdef GBM_RATING_SHOW_PARENTAL//GBM_FULL_FUNCTION      //gerry,2004-2-4 9:02
        "PARENTAL",//"RATING",             //116   T:()            S:(级别)
#else//GBM_RATING_SHOW_PARENTAL
	#if defined(MUSTEK_PORTABLE_DVD)
		"PARENTAL CTRL", //116
	#else
        "RATING",             //116   T:()            S:(级别)
    #endif
#endif//GBM_RATING_SHOW_PARENTAL

#ifdef EASTECH_NEW_SETUP_MENU
        "RAW",          //117   T:(SPDIF/方絏)      S:(SPDIF/源码)
#elif defined(DP3240_SETUP_MENU)  //add xrh 
         "RAW",  
#else
        "SPDIF/RAW",          //117   T:(SPDIF/方絏)      S:(SPDIF/源码)
#endif

        #ifdef SUPPORT_PALN //4-1-12 10:55
            "PAL-N",        //118
        #elif defined(PASSWORD_IN_CH)
        "ERROR",
        #elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-19 17:13 zhoulin
        "VOL_SW",
        #else
            "",              //118   T:(AC3 6羘笵)
        #endif

#ifdef EASTECH_NEW_SETUP_MENU
        "PCM",          //119
#elif defined (DP3240_SETUP_MENU)  //add xrh 
         "PCM", 
#else
        "SPDIF/PCM",          //119
#endif

        #ifdef SUPPORT_PALM
            "PAL-M",                //120
        #elif defined(PASSWORD_IN_CH)
        "  OK",
        #elif defined(SLEEP_CONTROL_COUNTER)
	 "45  MIN",
        #else
            "",              //120   T:(AC3 2羘笵)       S:AC3 2声道(not use)
        #endif

        #ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
        #else//SHOW_YCbCr
        #ifdef AD_TCL//2004-3-22 13:22 lijd
            "YCbCr",
        #elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
        #elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
        #elif defined(EASTECH_DVI)
        "YCbCr", //121
        #elif defined(DP3240_SETUP_MENU)
	  "YUV",  //121	
        #else
        "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
        #endif//SHOW_INTERLACE
        #endif//SHOW_YCbCr
        
        "AUTO",               //122   T:(笆)            S:(自动)
        "OFF",                //123   T:(闽)              S:(关)
#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
        "TRACK TIME",//124
#elif defined(SLEEP_CONTROL_COUNTER)
	  "60  MIN",
#elif defined(SHOW_DRM_REGISTRATION_CODE_IN_SETUP)
      "DIVX[R] VOD", //124
#else
        "",           //124
#endif     
        "CHAPTER",            //125   T:(彻竊)            S:(章节)
        "TITLE",              //126   T:(夹肈)            S:(标题)
        OS_ICON_ANGLE,        //127
#ifdef NINTAUS_OSD_STR
        "YPbPr",
#elif defined(AD_TCL)//2004-3-22 13:23 lijd
        "YPbPr", 
#elif defined(HANYANG_SETUPMENU)||defined(SUPPORT_FUNCTION_MENU)||defined(EASTECH_NEW_SETUP_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
        #elif defined (ADD_P_SCAN_ONOFF)  //add xrh
         "P-SCAN", 
         #elif defined(DP3240_SETUP_MENU)
	    "P-SCAN", 	 
#else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
#endif    

        OS_16_9,              //129   T:(16:9 --)
        OS_4_3LB,             //130   T:(4:3LB --)
        OS_4_3PS,             //131

#ifdef HJ_SVA_NEW_OSDSTR
        "PAL-D",                //132
#else//HJ_SVA_NEW_OSDSTR
        "PAL",                //132
#endif//HJ_SVA_NEW_OSDSTR
        "NTSC",               //133
        "PAL60",              //134

        #ifdef RATING_8
            "3 PG",               //135   T:(level 3)
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else
            "2",                  //136   T:(level 2)
            "1 G",                //137   T:(level 1)
            #endif
            
        #else
            "NO ADULT",           //135   T:(辅导级)
            "KID SAFE",           //136   T:(保留)
            "VIEW ALL",           //137   T:(礚)
        #endif


        #if defined(SHOW_5_1CH)
            "5.1CH",              //138   T:(5.1羘笵)
        #else
            "6CH SETUP",          //138   T:(6羘笵砞竚)
        #endif

        "SUBWOOFER",          //139   T:(禬)
        "SATURATION",         //140   SATURATION
        "ON",                 //141   T:
        OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
#if defined(OSD_BMP_PROG)
        "RESET",              //145   T:(睲埃)
#else
        "CLEAR",              //145   T:(睲埃)
#endif
        "  T  C",               //146   //2004-2-23 03:56张宇P
        "--:--",              //147
#if	defined(MP3_DIRECT_SELECT)||defined(OSD_BMP_PROG)
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "EDIT",               //149   T:(絪胯)
#ifdef RECORD_KEY 
        "RECORD RESUME",          //150
#elif defined(SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE)  //added by wangwei,2004-10-24 23:42,(English)
        "SUBTITLE LG 2",       //150     
#elif defined(SCALER_6500)
        "HDMI OUTPUT",     //150 //helm for scaler 050707             
#else
        "",//OS_DIR1,              //150
#endif
#ifdef QSI_SETUP_MENU//liweihua 2004-6-15
        " 1 MIN",                   //151
        " 5 MIN",                   //152
        "10 MIN",                   //153
        "30 MIN",                   //154
#elif defined(ADJUST_JPEG_SLIDE_TIME)  ////lyc 2005/2/18
        "15 SEC",                   //151
        "30 SEC",                   //152
        "45 SEC",                   //153
        "50 SEC",                   //154
#else
#ifdef BBK_DVD
        "5.1 CH",                  //151            
#elif defined(NINTAUS_OSD_STR)
    "<<<",
#elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-23 19:04 zhoulin
       "5.1 CH",

#else
        "",//OS_DIR2,              //151
#endif
        OS_DIR3,              //152
        OS_DIR4,              //153
        #ifdef SLEEP_CONTROL_COUNTER
	 "30  MIN",
	 #else
        "PAL-NC",//OS_DIR5,              //154
        #endif
#endif//#ifdef QSI_SETUP_MENU
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
#ifdef PULIANG_DVD      //yaowh add 04-12-17
        "CLOLOR",           //157
#else
        "HUE",                //157   HUE
#endif
#ifdef BBK_NEW_SETUP
        "PROLOGIC II",//"-:--:--",            //158  
#else
        "PROLOGIC",//"-:--:--",            //158     
#endif        
        "MOVIE MODE",//"TRACK SEARCH",       //159    
        "MUSIC MODE",//"DISC SEARCH",        //160    
        
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #elif defined(SUPPORT_PROLOGIC_II_ADVANCE_SETTING) //chenzhao 2005-5-12
        "PANORAMA",                //161
        #else
        "",//TT:CH",               //161    //not use
        #endif

        #ifdef REMAIN_TIME//nono 2-7-12 20:06
            "T",                  //162
        #else
            "",           //162
        #endif

        OS_DIR0,              //163
        "CONTRAST",           //164   CONTRAST
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
        "CHANNEL",            //168   T:(羘笵)            S:(声道)
        "BRIGHTNESS",         //169   BRIGHTNESS
        "F/W ID",             //170   T:(硁ン絪絏)        S:(软件编码)
#ifdef OP_CUST_UI  
		"CHECKSUM",  
#else		    
        "CHIP ID",            //171   T:(絪絏)        S:(芯片编码)
#endif       
        "REGION",             //172   T:(跋絏)            S:(区码)
        "MEMORY",//"FUNCTION",           //173  //not use T:(滦弄滦佰)        S:(复读复唱)
        "DYNAMIC",//"MODE",               //174  //not use  T:(家Α)            S:(模式)

#ifdef  DISPLAY_INDIVIDUAL_SPK_VOLUME   
        "VOL_L",
        "VOL_R",
        "VOL_SL",        
#else
        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177
#endif
        "MIC1 VOL",//"COMPARE",            //178   //not use T:(癸ゑ)            S:(对比)
        "MIC2 VOL",//"COUNTER",            //179   //not use T:(滦Ω计)        S:(重复次数)

#ifdef FUSS_DVD_AVD276
        "PREV CHAPTER",      //180   S:上一章节
        "NEXT CHAPTER",      //181   S:下一章节
//#elif defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#elif defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU)
        "BATTERY STATUS",           //180
        "SETUP",                    //181
#elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-19 17:13 zhoulin
        "BASS",
        "TREMBLE",
#else
        "",//"LEVEL",              //180   T:魁家Α        S:录音模式
        "",//"HIGH",               //181   T:蔼珇借          S:高品质
#endif

#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#elif defined(SUPPORT_PROLOGIC_II_ADVANCE_SETTING) //chenzhao 2005-5-12
        "CENTER WIDTH",             //182
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",             //182   T:(禬丁)        S:(超长时间)
#endif

#ifdef NEWSTYLE_WINDOW
        "PLAYTITLE",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "TITLETIME",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "CHPTIME",//"MANUAL",             //185   T:(も笆)            S:(手动)
#elif defined(ADD_DVI311_SETUP)//Modifed by ChenZhao on 2004-8-19 17:24 WP
			"ANOLOG OUTPUT", //183
			"DIGITAL OUTPUT",  //184
			"480P",//OS_MANUAL, 		   //185   T:(も笆)
#elif defined(SCALER_6500)
			"ANOLOG OUTPUT", //183
			"DIGITAL OUTPUT",  //184
			"480P",//OS_MANUAL, 		   //185   T:(も笆)			
#elif defined(BRIGHTNESS_COLOR_KEY)||defined(VIEW_MODE_KEY)
		"COLOR",					//OS_COLOR 					//183
        "NORMAL MODE",				//OS_VIEW_MODE_NORMAL   	//184   
        "FULL MODE",				//OS_VIEW_MODE_FULL         //185   
#else
        "",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "",//"MANUAL",             //185   T:(も笆)            S:(手动)
#endif

        OS_DIR10,             //186
        OS_DIR11,             //187
        "CONCERT",            //188   T:(贾芔)          S:(音乐厅)
        "CHURCH",             //189   T:(毙绑)            S:(教堂)
        "PASSIVE",            //190   T:(吏露)            S:(环绕)
        "WIDE",               //191   T:(糴初)            S:(宽场)
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192
        "MPEG LOGO",            //193
#elif defined(ADD_DVI311_SETUP)//Modifed by ChenZhao on 2004-8-19 17:20 WP
    #ifdef HDCP_CUSTOM
		"HDCP",	            //192
	#else
		"VIDEO SELECT",	  //192
    #endif
		"VIDEO MODE",		  //193
#elif defined(SCALER_6500)
    #ifdef HDCP_CUSTOM
		"HDCP",	            //192
	#else
		"VIDEO SELECT",	  //192
    #endif
		"HDMI OUTPUT",		  //193			
#elif defined(PULIANG_DVD)//yaowh add 04-12-17
        "VERSION:WPQM_1A25101",     //192
        "REGION CODE",              //193
#elif defined(SLEEP_CONTROL_COUNTER)
   "15  MIN",
   "OFF",
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)
        "",//OS_STADIUM,           //193   T:(蔨▅繻)
#endif
        "EQ",                 //194   T:(А颗)            S:(均衡)
        "STANDARD",           //195   T:(夹非)            S:(标准)
        "CLASSIC",            //196   T:(ㄥ)            S:(古典)
        "ROCK",               //197   T:(穘簎)            S:(摇滚)
        "JAZZ",               //198   T:(里)            S:(爵士)
        "POP",                //199   T:(瑈︽)            S:(流行)
        "USER",               //200   T:(┦)            S:(个性)
        "ATTRIB",             //201   T:(┦)            S:(个性)
        "SF",                 //202   T:(篊秈)            S:(慢进)
        "SB",                 //203   T:(篊癶)            S:(慢退)

        "C",                  //204   //show "C"
       "CENTER",              //205   T:(い竚喘羘竟)      S:(中置扬声器)
        "REAR",               //206   T:(吏露喘羘竟)      S:(环绕扬声器)
        #if !defined(HIMAGE_RGB)&&!defined(NINTAUS_OSD_STR)
        "TV-RGB",             //207
        #else
        "RGB",                    //207
        #endif
        "4 PG13",             //208   T:(辅导级)
        "CENTER DELAY",       //209   T:(い竚┑筐)
        "REAR DELAY",         //210   T:(吏露┑筐)
        "FRONT",              //211   T:(玡竚喘羘竟)
        "VIDEO SETUP",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS
        "SYSTEM SETUP",       //214   T:(╰参砞竚)        S:(系统设置)
        "SPEAKER SETUP",      //215   T:(喘羘竟砞竚)      S:(扬声器设置)
        "AUDIO SETUP",        //216   T:(繵砞竚)        S:(音频设置)
        "DEFAULT",            //217   T:()          S:(缺省值)
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #elif defined(SLEEP_CONTROL_COUNTER)  //ADD XRH 
	"SLEEP CONTROL",
        #else
            
        "GRP",                //218   //not use

        #endif
#ifdef AUTO_PLAY
        "AUTO PLAY",       //219   T:(辊玂臔)        S:(屏幕保护)
#elif defined(VCD_CDG_PLAY_CONTROL_BY_SETUPMENU)
        "   MNP   ",
#else
        "SCREEN SAVER",       //219   T:(辊玂臔)        S:(屏幕保护)
#endif
        #if defined(MUSTEK_PORTABLE_DVD)&&!defined(MUSTEK_K100D_MODEL)
	    "ANGLE MARK", 			//220
	 	#elif defined(ORITRON_PASSWORD)//libing 2005-4-29 9:53
	 	"SET DUFAULT VALUE",//220
        #else
        "TYPE 1",             //220   T:(家Α 1)          S:(模式1)
        #endif
        #if defined(MUSTEK_PORTABLE_DVD)&&!defined(MUSTEK_K100D_MODEL)
        "NIGHT MODE", 	  //227
        #elif defined(ORITRON_PASSWORD)//libing 2005-4-29 9:53
        "CLEAR PASSWORD",             //221   T:(辅导级)
        #else
        "TYPE 2",             //221   T:(家Α 2)          S:(模式2)
        #endif
        #ifdef ORITRON_PASSWORD//libing 2005-4-29 9:53
        "LOADER LOCKED",       //222   T:(い竚┑筐)
        #else
        "TYPE 3",             //222   T:(家Α 3)          S:(模式3)
		#endif

        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   S:(5保留)
        #endif
        
        "6 R",                //224   S:(限制级)

        #ifdef NOT_SUPPROT_VCD
        "NOT SUPPORTED CD",           //225   S:(错误碟片)
        #else
        "ERR DISC",           //225   S:(错误碟片)
        #endif

        #if defined(MUSTEK_PORTABLE_DVD)&&!defined(MUSTEK_K100D_MODEL)
        "MAIN PAGE", 	  //226
        #else
        "DIGITAL SETUP",      //226   T:(计絏砞竚)
        #endif	
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "MIC SETUP",          //227   T:(杠旦砞竚)
        "MIC VOL",            //228   T:(杠旦秖)
        #endif
        "CD RECOVERING",      //229   T:(岿い)     ------------- not use
        "SMART UPGRADE",      //230   T:(醇ど)
        "UPGRADE TO V ",      //231   T:(どΘ)
        "UPGRADING",          //232   T:(どい)
        "DON'T POWER OFF",	//233   T:(づ闽诀)	//YAOWH MODIFY 04-10-26
        "REGION 0",           //234   T:(0 跋)
        "REGION 1",           //235   T:(1 跋)
        "REGION 2",           //236   T:(2 跋)
        "REGION 3",           //237   T:(3 跋)
        "REGION 4",           //238   T:(4 跋)
        "LANGUAGE SETUP",     //239   T:(粂ē砞竚)
#ifdef  JIEKE_DVD
        "GIEC",               //240
#elif defined(BBK_DVD)
        "ZOOM",               //240
#elif defined(NINTAUS_OSD_STR)
    ">>>",
#elif defined(SUPPORT_FUNCTION_MENU)
        "DISPLAY",            //240 
#elif defined(GBM_PORTABLE_DVD)||defined(SUNPLUS_8202P_DEMOBOARD) 
        "LOW BATTERY",        //240         
#elif defined(SUPPORT_PROLOGIC_II_ADVANCE_SETTING) //chenzhao 2005-5-12
        "DIMENSION",          //240         
#else        
        "",                   //240   //not use
#endif      
        "MAIN PAGE",          //241   T:()
#if !defined(BBK_DVD)
        "AUDIO LANG",       //242   T:(繵粂ē)
#else
        "AUDIO",              //242   T:(繵粂ē) //axel 2004/1/27 03:58 eliminate "LANG"
#endif
#ifdef DISC_INFO_KEY  //fengjl  3-11-25 9:55
/*         "SUBP LANG",      //243   T:(辊粂ē)*/ //axel 2004/1/27 03:58 eliminate "LANG"
        "SUBP",      //243   T:(辊粂ē)
#elif defined(BBK_DVD)
        "SUBTITLE",           //243   T:(辊粂ē)
#else
        "SUBTITLE LANG",      //243   T:(辊粂ē) //axel 2004/1/27 03:58 eliminate "LANG"
#endif
        "MENU LANG",          //244   T:(垫虫粂ē)
#ifdef PULIANG_DVD  //yaowh add 04-12-17
        "DOWNMIX",      //245
        "RESET",        //246
#elif defined(SUPPORT_CHANNEL_SETUP)//2005-4-23 19:52 zhoulin
         "CHANNEL",            //245   T:(睼家Α)
        "RESTORE",            //246   T:(確)
#elif defined(DOWNMIX_DISP_20CH51CH)
		"2.0CH/5.1CH",//zxb		//245   T:(睼家Α)
        "RESTORE",            //246   T:(確)
#else
        "DOWNMIX",            //245   T:(睼家Α)
        "RESTORE",            //246   T:(確)
#endif
       
        "LT/RT",              //247
        "VSS",                //248   T:(店览吏露羘)      S:(虚拟环绕声)
        "OP MODE",            //249   T:(块家Α)        S:(输出模式)
        "LINE OUT",           //250   T:(絬隔块)        S:(线路输出)
        "RF REMOD",           //251   T:(RF 秸俱)         S:(RF调整)
#ifdef PULIANG_DVD  //yaowh add 04-12-17
        "MODE",         //252
#else
        "DUAL MONO",          //252   T:(オ+)           S:(左+右)
#endif
        "MIX MONO",           //253   T:(睼羘笵)        S:(混合声道)
        "SURND MODE",         //254   T:(吏露家Α)        S:(环绕模式)
#ifdef KSD_DVD
        "PRESS PLAY BUTTON TO CONTINUE",        //255   T:              S:请按播放键继续
#elif defined(DESAY_DVD)
        "PRESS PLAY BUTTON TO CONTINUE",
#elif defined(TONIC_DVD)
        "PRESS PLAY KEY TO CONTINUE",
#else
        "PRE STOP",           //255   T:                S:(准停止)
#endif
//============================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER

},
#endif  //USE_ENGLISH_OSD

#ifdef USE_SCHINESE_OSD
//Simplied Chinese
{
        OS_NULL,              //0
        OS_NODISC,            //1     T:(礚盒)
        OS_NO,                //2     T:(眤岿 hand)
        OS_TRACK,             //3     T:(Ρヘ)
        OS_ICON_SVCD,         //4
        "DE-INTERLACE",//OS_CHINESE,           //5     not use
        OS_OPEN,              //6     T:()
        OS_CLOSE,             //7     T:(闽)
        OS_PLAY,              //8     T:(冀)
        OS_REGION_5,          //9     T:(5 跋)
        OS_PAUSE,             //10    T:(既氨)
        OS_RANDOM,            //11    T:(繦诀冀)
        OS_RESUME,            //12    T:(確冀)
        OS_STOP,              //13    T:(氨ゎ)
        OS_STEP,              //14    T:(˙秈)
        OS_SELECT,            //15    T:(匡拒)
        OS_READ,              //16    T:(弄盒)
        OS_REGION_6,          //17    T:(6 跋)
        OS_SIMULATE,          //18    T:(家览)
        OS_FF,                //19    T:(е秈)
        OS_FB,                //20    T:(е癶)
        OS_NEXT,              //21    T:(Ρ >>)


        #if defined(SETUP_PASSWORD_GUI)      //fengjl add  4-1-19 17:09
            OS_PASSWD_EDIT,       //22
        #elif defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
            "VGA",                   //22
        #else
            OS_NULL,                     //22
        #endif

        OS_PREV,              //23    T:(Ρ <<)

        "DIR",//OS_NULL,                     //24

        OS_RETURN,            //25    T:(垫虫)
        Ch_repx,              //26
        Ch_rep1,              //27
        Ch_repd,              //28
        Ch_vff,               //29    T:(礚)
        OS_MENU,              //30    T:(匡虫)
        OS_SCORE,             //31    T:(だ计)
        OS_MARK,              //32    T:(癘拘)
        OS_BROWSE,            //33    T:(聅凝)
        OS_PROG,              //34    T:(絪)
        OS_SAVELOGO,          //35    S:画面抓取中
        OS_BASS_MODE_1,       //36    T:(家Α1)
        OS_REP,               //37    T:(確)
        OS_REP_DIR,           //38    T:(ヘ魁確)
        OS_REP_1,             //39    T:(虫Ρ確)
        OS_REP_ALL,           //40    T:(盒確)
        OS_REP_CNL,           //41    T:(確)
        OS_BASS_MODE_2,       //42    T:(家Α2)
        //"8",                //43    S:(8保留)
        #ifdef FIX_RATING_8_DISPLAY
        #if  defined( JIEKE_DVD)
        OS_ADULT,       //43 
        #elif defined(HJ_APEX_FIX_SHOW_OSD)
       "8 BYPASS",            //43
        #else//#ifdef HJ_APEX_FIX_SHOW_OSD 
        "8 ADULT",            //43
        #endif//#ifdef HJ_APEX_FIX_SHOW_OSD
        #elif defined(NINTAUS_OSD_STR)
        OS_ADULT,
        #else
        "8",
        #endif
        "7 NC-17",            //44
        OS_GOTO,              //45    T:(穓)
        OS_MUTE,              //46    T:(繰)
        OS_CHL,               //47    T:(オ羘笵)
        OS_CHR,               //48    T:(羘笵)
        OS_STEREO,            //49    T:(ミ砰羘)
        OS_CANCEL OS_MUTE,    //50    S:取消静音//not use
        OS_LIVE,              //51
        #if defined(KARAOKE_MENU)||defined(QSI_SETUP_MENU)//liweihua 2004-6-16//wangfeng 2003-10-31 10:23
    OS_KARAOKE_SETUP,   //52    //S:KARAOKE设定
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52

         #elif defined( SANJING_MIDI_DVD)  //ouyang2004-11-2 15:49
         OS_MELODY_ON,   //52    
         #elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
        #elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-23 22:03zhoulin
        OS_KARAOKE_SETUP,
         #else
        "",                   //52    //not use                 
        #endif
        OS_BASS_MODE_3,       //53    T:(家Α3)
        OS_ICON_CDROM,        //54
        OS_TIME,              //55    T:丁
#ifdef  RECORD_KEY
     #ifdef NINTAUS_OSD_STR    //2004-2-11 11:35张宇P
           OS_RECORD_1,
     #else  
        OS_RECORD_1SENTENCE,  //56 
     #endif
#elif defined(SUPPORT_ANGLE_MARK)
        OS_ANGLE_MARK,                   //56    S:(角度标记)
#elif defined(SHOW_MP4_INIT_STR)    //wangwei-2004/4/28
    OS_MP4_INIT,   //56 
#elif defined(SANJING_MIDI_DVD) //ouyang 2004-11-2 15:56
          OS_MELODY_OFF,   //56  
#elif defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "XGA",                 //56
          #else
        "",                   //56   //not use                  
#endif
        OS_ZOOM,              //57    T:(糴)
#ifdef  RECORD_KEY
   #ifdef NINTAUS_OSD_STR
       OS_RECORD_2,
   #else
        OS_RECORD_2SENTENCE,   //58
   #endif
#elif defined(SUPPORT_CC_ONOFF)
       OS_CLOSED_CAPTION,            //58    S:(CC字幕)
#elif defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "SXGA",                     //58
#elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-19 17:13 zhoulin
        OS_VOL_SR,
#else
        "",//OS_CANCEL,            //58    T:
#endif
        OS_ICON_LANG,         //59
        OS_INTRO,             //60    T:(苯磞)
        OS_SURR,              //61    T:(吏露)
        "PBC",                //62
#ifdef  RECORD_KEY
#ifdef NINTAUS_OSD_STR
          OS_RECORD_3,
#else       
        OS_RECORD_3SENTENCE,  //63
#endif
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "",//OS_PBC_OFF,           //63    T:抖冀
#endif
        OS_RANDOM OS_CANCEL,  //64    T:(繦诀冀)
        OS_BASS_MANAGEMENT,   //65    T:(家Α)

        OS_ALL,//"POWER ON",                    //66

        OS_REP_A,             //67    T:確A-
        #ifdef JIEKE_DVD
        "P-SCAN VGA",               //"PC-VGA",           //68
        #elif defined(NINTAUS_OSD_STR)
        "VGA",
        #else
        "PC-VGA",               //"PC-VGA",           //68
        #endif
        OS_REP_AB,            //69    T:確A-B
#ifdef BBK_DVD
        OS_CANCEL "AB",
#else
        OS_CANCEL OS_REP,     //70    T:確
#endif
        OS_PROG OS_CANCEL,    //71    T:絪胆?        "",                   //72
        "",                   //72
#ifdef ONE_KEY_PASS
        OS_ONEKEY,                  //73 
#elif defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "576P/480P",                     //73
#elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-19 17:13 zhoulin
        OS_VOL_CT,
#else          
        "",//OS_ENGLISH,           //73    T:璣粂
#endif
        OS_ICON_VCD,          //74
#ifdef BBK_DVD
        OS_LIGHT_MUSIC,        //75   //zhaoyanhua add 03-10-28 21:37 //not use
#elif defined(NINTAUS_OSD_STR)
      OS_RESTORE_SETUP1,
 #elif defined (MIDI_EJECT_PASSWORD) //75//ouyang add for eject pwd in midi 04-11-20
  OS_EJECT_PASSWORD,
#elif defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "720P",                  //75
#else
        "",                     //75
#endif

        #if defined(SHOW_VCD_VER_INFO)||defined(SYBER_DVD)  //yaowh add for kenloon 04-08-03
        OS_ICON_VCD20,        //76    //xulf 2003-11-17
        #else
        OS_ELECTRON,           //76   //zhaoyanhua add 03-10-28 21:37 //not use
        #endif

        "CVBS",//OS_ICON_MP3,      //77

        OS_ICON_CDDA,         //78

#ifdef NINTAUS_OSD_STR   
        "48KHZ",                   //79    //not use
        "96KHZ",                   //80    //not use
        "192KHZ",                   //81    //not use
#else
        "48K",                   //79    //not use
        "96K",                   //80    //not use
        "192K",                   //81    //not use
#endif

        OS_PICUP,             //82    T:礶簿
        OS_PICDN,             //83    T:礶簿
        OS_PICL,              //84    T:礶オ簿
        OS_PICR,              //85    T:礶簿
        OS_CHAPTER,           //86    T:彻竊
        OS_ECHO,              //87    T:睼臫
        OS_TITLE,             //88    T:夹肈
        OS_BAND,              //89    T:繵眯
#if defined( DISPLAY_INDIVIDUAL_SPK_VOLUME)
        OS_MAIN_VOL,
#else
        OS_VOL,               //90    T:秖
#endif                
        #ifdef LPCM_OUTPUT     //fengjl add 3-12-1 15:33
        OS_FREQ_MASK,           //91
        #else            
        OS_DOWN_SAMPLE,//"DOWN SAMPLE",        //91    //not use
        #endif
        
        
        OS_KEY,               //92    T:秸
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        OS_9FRAME_1,          //94    T:虫Ρ礶
        OS_AUTO_L,            //95    T:笆钡佰オ
        OS_AUTO_R,            //96    T:笆钡佰
        "LOW",                //97    // LOW
        OS_SEQUENCE,          //98    T:抖冀
        OS_MENUPLAY,          //99    T:垫虫冀
#ifdef DIV_GOTO_DISPLAY
        OS_DISCTIME,         //100
#else
        "",//OS_SFE_OUT,           //100
#endif
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)  // fengjl  3-11-24 13:44
        OS_ONEKEY_SETUP,           //101
        OS_PROFESSION_SETUP,       //102
#elif defined(NINTAUS_OSD_STR)
        OS_PICTURE_UD ,
                OS_PICTURE_LR ,
#elif defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102   
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102

#elif defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "SVGA",                 //101
        "1080I",                 //102
#else
        "",//OS_SFE_STD,           //101
        "",//OS_SFE_EHNANCE,       //102
#endif

        "MEDIUM",             //103   // MEDIUM
        OS_PROG_PLAY,         //104   T:絪导僵
        "HIGH",               //105   // HIGH
        OS_DYNAMICRANGE,      //106   T:笆篈絛瞅
        OS_ICON_DVD,          //107
        OS_OSD,               //108   T:(礶陪ボ粂ē)
        OS_ICON_SUBT,         //109
        OS_TV_RATIO,          //110   T:辊礶ゑㄒ
        OS_TV_SYS,            //111   T:筿跌诀Α
        OS_EXIT_MENU,         //112   T:癶砞竚垫虫
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        OS_AUD_OUT,           //113   T:计絏块
#endif
        OS_VIDEO,             //114   T:跌繵块
        OS_PASSWORD,          //115   T:盞絏
        OS_RATING,            //116   T:
        OS_BITSTREAM,         //117   T:SPDIF/方絏

        #if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
        #elif defined(PASSWORD_IN_CH)
           OS_PASSWORD_ERROR,
        #elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-19 17:13 zhoulin
        OS_VOL_SW,
        #else
            "",//OS_ANALOG_6CH,                  //118
        #endif

        "SPDIF/PCM",          //119

        #if defined(SUPPORT_PALM)
            "PAL-M",                //120
        #elif defined(PASSWORD_IN_CH)
        OS_PASSWORD_RIGHT ,   
        
        
        #else
            "",//OS_ANALOG_2CH,                  //120
        #endif
        #if defined(KSD_DVD)||defined(DESAY_DVD)//2003-11-9 17:31//20030823
          #ifdef HANYANG_SETUPMENU   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
        #else
        "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
         #endif  
        #else
        OS_YUV,               //121   T:跌繵だ秖
        #endif
        OS_AUTO,              //122   T:笆
        OS_OFF,               //123   T:闽
#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
        OS_TRACKTIME,         //124
#elif  defined(SHOW_DRM_REGISTRATION_CODE_IN_SETUP)
        "DIVX[R] VOD", //124
#else        
        "",//"TM/CH/TL",           //124
#endif     
        OS_CHAPTER,           //125   T:彻竊
        OS_TITLE,             //126   T:夹肈
        OS_ICON_ANGLE,        //127
#ifdef NINTAUS_OSD_STR
        OS_P_SCAN_YUV,//"YPbPr",
#elif defined(HANYANG_SETUPMENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
#elif defined(SUPPORT_FUNCTION_MENU)
        "P-SCAN",  //128
#elif defined(EASTECH_DVI)
        "YPbPr", //128
#else
        "P-SCAN YPBPR",             //128   T:P-SCAN
#endif
        OS_16_9,              //129   T:16:9 --
        OS_4_3LB,             //130   T:4:3LB --
        OS_4_3PS,             //131
        "PAL",                //132
        "NTSC",               //133
        "PAL60",              //134

        #ifdef RATING_8
            "3 PG",               //135   T:level 3
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            #ifdef JIEKE_DVD
            OS_KID_ONLY,    //137
            #else 
            "1 KID SAFE",                //137   T:(level 1)
            #endif
            #else
          #ifdef NINTAUS_OSD_STR      
             "2 G ",                  //136     T:level 2
             OS_KID_ONLY,                //137   T:level 1
        #else
            "2",                  //136     T:level 2
            "1 G",                //137   T:level 1
            #endif
            #endif
        #else
            OS_NO_ADULT,          //135   T:(獶A)
            OS_KID_ONLY,          //136   T:(ㄠ担)
            OS_VIEW_ALL,          //137   T:(礚)
        #endif

        OS_6CH_SETUP,                  //138

        OS_SUBWOOFER,         //139   T:禬
        OS_SATURATION,        //140   埂㎝
        OS_ON,                //141   T:秨
        OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
        OS_CLEAR,             //145   T:睲埃
        "  T  C",               //146  //2004-2-23 03:57张宇P
        "--:--",              //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        OS_EDIT,              //149   T:(絪胯)
#ifdef RECORD_KEY 
        OS_RECORD_RESUME,     //150
#elif defined(SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE)  //added by wangwei,2004-10-24 23:42,(SChinese).
        OS_SUBTITLE_LANG_2ND_SETUP,      //150       
#else
        "",//OS_DIR1,              //150
#endif
#ifdef QSI_SETUP_MENU//liweihua 2004-6-15
        " 1 MIN",                   //151
        " 5 MIN",                   //152
        "10 MIN",                   //153
        "30 MIN",                   //154
#elif defined(ADJUST_JPEG_SLIDE_TIME)  ////lyc 2005/2/18
        "15 SEC",                   //151
        "30 SEC",                   //152
        "45 SEC",                   //153
        "50 SEC",                   //154             
#else
#ifdef BBK_DVD
        OS_5_1_CHANNEL,             //151            
#elif defined(NINTAUS_OSD_STR)
     OS_PICTURE_ROTATE_LEFT,
#elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-23 19:04 zhoulin
     OS_5_1_CHANNEL,

#else
        "",//OS_DIR2,              //151
#endif       
        OS_DIR3,              //152
        OS_DIR4,              //153
        "PAL-NC",//OS_DIR5,              //154
#endif//#ifdef QSI_SETUP_MENU
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
        OS_HUE,               //157   ︹秸

#ifdef BBK_NEW_SETUP
        "PROLOGIC II",//"-:--:--",            //158  
#else
        "PROLOGIC",//"-:--:--",            //158
#endif      
        OS_PL_MOVIE,//OS_TRK_S,             //159   //not use
        OS_PL_MUSIC,//OS_DISC_S,            //160  //not use

        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//"TT:CH",              //161    //not use
        #endif

        #ifdef REMAIN_TIME//nono 2-7-12 20:06
            "T",                  //162
        #else
            "",//"BOOKMARK",           //162
        #endif

        OS_DIR0,              //163
        OS_CONTRAST,          //164   癸ゑ
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
        OS_CH,                //168   T:(羘笵)
        OS_BRIGHT_SETUP,      //169   獹
        "F/W ID",//OS_FIRMWARE_ID,       //170   T:(硁ン絪絏)
        "CHIP ID",//OS_CHIP_ID,           //171   T:(絪絏)
        OS_REGION_CODE,       //172   T:(跋絏)
        "MEMORY",//OS_FUNCTION,          //173   T:(滦弄滦佰)
        "DYNAMIC",//OS_MODE,              //174   T:(家Α)


#ifdef  DISPLAY_INDIVIDUAL_SPK_VOLUME   
        OS_VOL_L,
        OS_VOL_R,
        OS_VOL_SL,        
#else
        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177
#endif                

        OS_MIC_VOL_1,               //178
        OS_MIC_VOL_2,               //179

//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)
        OS_NEXT_PAGE,               //180
        OS_PREV_PAGE,               //181
#elif defined(SUPPORT_FUNCTION_MENU) 
	OS_BATTERY_STATUS,	    //180
	OS_SETUP,    		    //181
#elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-19 17:13 zhoulin
        OS_BASS,
        OS_TREMBLE,
#else 
        "",//OS_LEVEL,             //180   T:(魁家Α)
        "",//OS_HIGH,              //181   T:(蔼珇借)
#endif      
#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//OS_NORMAL,            //182   T:(禬丁)
#endif
#ifdef NEWSTYLE_WINDOW
        OS_PLAYTIME,//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        OS_TITLETIME,//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        OS_CHPTIME,//"MANUAL",             //185   T:(も笆)            S:(手动)
#elif defined(ADD_DVI311_SETUP)
		OS_DVI311_ANOLOG_OUTPUT, //183
		OS_DVI311_DIGIT_OUTPUT,  //184
		"480P",//OS_MANUAL,            //185   T:(も笆)
#elif defined(BRIGHTNESS_COLOR_KEY)||defined(VIEW_MODE_KEY)
    	OS_COLOR,					//183
		OS_VIEW_MODE_NORMAL,   		//184   
        OS_VIEW_MODE_FULL,      	//185
#else
        "",//OS_SUPER,             //183   T:(禬蔼珇借)
        "",//OS_OPERATING,         //184   T:(秸竊よΑ)
        "",//OS_MANUAL,            //185   T:(も笆)
#endif 
        OS_DIR10,             //186
        OS_DIR11,             //187
        OS_CONCERT,           //188   T:(贾芔)
        OS_CHURCH,            //189   T:(毙绑)
        OS_PASSIVE,           //190   T:(吏露)
        OS_WIDE,              //191   T:(糴初)
#ifdef USER_MPEG_LOGO
        OS_SELECT_LOGO,         //192
        OS_MPEG_LOGO,           //193
#elif defined(ADD_DVI311_SETUP)
    #ifdef HDCP_CUSTOM
		"HDCP",	              //192
	#else
		OS_DVI311_FORMAT,	  //192
    #endif
		OS_DVI311_MODE,		  //193
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)
        "",//OS_STADIUM,           //193   T:(蔨▅繻)
#endif
        OS_EQ,                //194   T:(А颗)
        OS_STANDARD,          //195   T:(夹非)
        OS_CLASSIC,           //196   T:(ㄥ)
        OS_ROCK,              //197   T:(穘簎)
        OS_JAZZ,              //198   T:(里)
        OS_POP,               //199   T:(瑈︽)
        OS_USER,              //200   T:(┦)
        OS_ATTRIB,            //201   T:(┦)
        OS_SF,                //202   T:(篊秈)
        OS_SB,                //203   T:(篊癶)

            "C",                 //204   //show "C"


        OS_CSPK,              //205   T:い竚喘羘竟
        OS_SSPK,              //206   T:吏露喘羘竟
        #ifndef NINTAUS_OSD_STR
        "TV-RGB",              //207
        #else
        "RGB",
        #endif
        
        "4 PG13",             //208   S:辅导级
        OS_CSPK_DELAY,        //209   T:い竚┑筐
        OS_SSPK_DELAY,        //210   T:吏露┑筐
        OS_FSPK,              //211   T:玡竚喘羘竟
        OS_VIDEO_SETUP,       //212   跌繵砞﹚
        OS_SHARPNESS,//"SHARPNESS",          //213   SHARPNESS
        OS_SYS_SETUP,         //214   T:╰参砞竚
        OS_SPK_SETUP,         //215   T:喘羘竟砞竚
        OS_AUD_SETUP,         //216   T:繵砞竚
        OS_DEFAULT_SETUP,     //217   T:
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
      
        OS_GROUP,             //218   T:竤舱

        #endif
        OS_SSAVER_SETUP,      //219   T:辊玂臔
        OS_SSAVER_1,          //220   T:家Α 1


        OS_SSAVER_2,          //221   T:(家Α 2)
        OS_SSAVER_3,          //222   T:(家Α 3)


        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #elif defined(NINTAUS_OSD_STR)
        "5 PGR",
        #else
        "5",                  //223   T:(5保留)
        #endif
        "6 R",                //224   T:(限制级)

        OS_ERR_DISC,          //225   S:错误碟片
        OS_DIGITAL_SETUP,     //226   T:计絏砞竚
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        OS_MIC_ONOFF,         //227   T:杠旦砞竚
        OS_MIC_VOL,           //228   T:杠旦秖
        #endif
        OS_CD_DEBUG,          //229   T:岿い       ------------- not use
        OS_SMART_UPGRADE,     //230   T:醇ど
        OS_UPGRADE_TO,        //231   T:どΘ
        OS_UPGRADING,         //232   T:どい
        OS_NOT_POWEROFF,      //233   T:づ闽诀
        OS_REGION_0,          //234   T:0 跋
        OS_REGION_1,          //235   T:1 跋
        OS_REGION_2,          //236   T:2 跋
        OS_REGION_3,          //237   T:3 跋
        OS_REGION_4,          //238   T:4 跋
        OS_LANG_SETUP,        //239   T:粂ē砞竚
#ifdef JIEKE_DVD
        "GIEC",               //240 
#elif defined(BBK_DVD)
        OS_NO_ZOOM,           //240
#elif defined(GBM_PORTABLE_DVD)||defined(SUNPLUS_8202P_DEMOBOARD)     //rbhung for GBM Portable DVD
        OS_LOWBAT,                  //Jack move to here
#elif defined(NINTAUS_OSD_STR)
    OS_PICTURE_ROTATE_RIGHT,
#elif defined(SUPPORT_FUNCTION_MENU) 
	OS_DISPLAY,	      //240	
#else        
        "",                   //240   //not use
#endif       
        OS_RETURN_MAIN_SETUP, //241   T:()
        OS_AUDIO_LANG_SETUP,  //242   T:(繵粂ē)
        OS_SUBTITLE_LANG_SETUP,//243  T:(辊粂ē)
        OS_MENU_LANG_SETUP,   //244   T:(垫虫粂ē)

#if defined(SUPPORT_CHANNEL_SETUP)//2005-4-23 19:52 zhoulin
        OS_CHANNEL_SETUP,
#else       
        OS_DOWNMIX_SETUP,     //245   T:(睼家Α)
#endif 
        OS_RESTORE_SETUP,     //246   T:(確)
      
        "LT/RT",              //247
        OS_VSURROUND_SETUP,   //248   T:店览吏露羘
        OS_DOLBY_OP_SETUP,    //249   T:块家Α
        OS_DOLBY_LINE_SETUP,  //250   T:絬隔块
        OS_DOLBY_RF_SETUP,    //251   T:RF 秸俱
        OS_DUAL_MONO_SETUP,   //252   T:オ+
        OS_MIX_MONO_SETUP,    //253   T:睼羘笵
        OS_SURROUND_MODE,     //254   T:吏露家Α
        OS_PRE_STOP,          //255   T:              S:准停止

//============================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

#ifdef GBM_PORTABLE_DVD     //rbhung for GBM Portable DVD
        OS_LOWBAT,            //256   T:筿秖
#elif defined(USE_CHINESE_IN_JPEG_ROTATE)
        OS_PICTURE_ROTATE,    //256    
#else
        "",                   //256
#endif

#ifdef USE_CHINESE_IN_JPEG_ROTATE
        OS_PICTURE_UPTURN,    //257     
#else
        "",                   //257  
#endif

#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        OS_ENTER_RETURN,      //258
#else
       OS_REP_TITLE,        //258
#endif

#ifdef SETUP_PASSWORD_GUI       
        OS_PASSWD_ERROR,         //259
        OS_PASSWD_SENTENCE1,       //260
#else
       OS_REP_CHAPTER,      //259
       OS_REP_GROUP,        //260
#endif
#ifdef SETUP_PASSWORD_GUI
        OS_PASSWD_SENTENCE2,       //261
        OS_OLD_PASSWD,      //262
        OS_NEW_PASSWD,      //263 
#else
        "",       //261
        "",      //262
        "",      //263 
#endif


#endif  //EXCEED_MAX_NUMBER

},
#endif  //USE_SCHINESE_OSD

#ifdef USE_TCHINESE_OSD
//Traditional Chinese
{
        TOS_NULL,              //0
        TOS_NODISC,            //1     T:礚盒
        TOS_NO,                //2     T:眤岿 hand
        TOS_TRACK,             //3     T:Ρヘ
        OS_ICON_SVCD,          //4
        "DE-INTERLACE",//TOS_CHINESE,           //5     T:簙粂
        TOS_OPEN,              //6     T:癶
        TOS_CLOSE,             //7     T:闽超
        TOS_PLAY,              //8     T:冀
        TOS_REGION_5,          //9     T:5 跋
        TOS_PAUSE,             //10    T:既氨
        TOS_RANDOM,            //11    T:繦诀冀
        TOS_RESUME,            //12    T:確冀
        TOS_STOP,              //13    T:氨ゎ
        TOS_STEP,              //14    T:˙秈
        TOS_SELECT,            //15    T:匡拒
        TOS_READ,              //16    T:弄盒
        TOS_REGION_6,          //17    T:6 跋
        TOS_SIMULATE,          //18    T:家览
        TOS_FF,                //19    T:е秈
        TOS_FB,                //20    T:е癶
        TOS_NEXT,              //21    T:Ρ >>
        OS_NULL,               //22
        TOS_PREV,              //23    T:Ρ <<
        "DIR",//OS_NULL,               //24
        TOS_RETURN,            //25    T:匡虫
        Ch_repx,               //26
        Ch_rep1,               //27
        Ch_repd,               //28
        TCh_wu2,               //29    T:礚
        TOS_MENU,              //30    T:匡虫
        TOS_SCORE,             //31    T:だ计
        TOS_MARK,              //32    T:癘拘
        TOS_BROWSE,            //33    T:聅凝
        TOS_PROG,              //34    T:絪?        
        "SAVING LOGO...",      //35    
        TOS_BASS_MODE_1,       //36    T:家Α1
        TOS_REP,               //37    T:確
        TOS_REP_DIR,           //38    T:ヘ魁確
        TOS_REP_1,             //39    T:虫Ρ確
        TOS_REP_ALL,           //40    T:盒確
        TOS_REP_CNL,           //41    T:確
        TOS_BASS_MODE_2,       //42    T:家Α2
        //"8",                   //43    S:8保留
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
        #else// #ifdef HJ_APEX_FIX_SHOW_OSD
        "8 ADULT",            //43
        #endif// #ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",
        #endif
        "7 NC-17",             //44
        TOS_GOTO,              //45    T:穓冀
        TOS_MUTE,              //46    T:繰
        TOS_CHL,               //47    T:オ羘笵
        TOS_CHR,               //48    T:羘笵
        TOS_STEREO,            //49    T:ミ砰羘
        TOS_CANCEL TOS_MUTE,   //50    //mute cancel
        TOS_LIVE,              //51    T:渤?        
#ifdef QSI_SETUP_MENU//liweihua 2004-6-16
        "KARAOK SETUP",                   //52
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "",                    //52    //not use
#endif      
        TOS_BASS_MODE_3,       //53    T:家Α3
        OS_ICON_CDROM,         //54
        TOS_TIME,              //55    T:丁
        #ifdef SHOW_MP4_INIT_STR   //wangwei-2004/4/28
        "INITIALIZING...",  //56
        #else
        "",                    //56    //not use
        #endif
        
        
        TOS_ZOOM,              //57    T:糴

#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                    //58    //not use
#endif

        OS_ICON_LANG,          //59
        TOS_INTRO,             //60    T:苯磞
        TOS_SURR,              //61    T:吏露
        "PBC",                 //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "",//TOS_PBC_OFF,           //63    T:抖冀
#endif
        TOS_RANDOM TOS_CANCEL, //64    T:繦诀冀
        TOS_BASS_MANAGEMENT,   //65    T:家Α

        "",//"POWER ON",                    //66

        TOS_REP_A,             //67    T:確A-
        "PC-VGA",               //"PC-VGA",           //68
        TOS_REP_AB,            //69    T:確A-B
        TOS_CANCEL TOS_REP,    //70    T:確
        TOS_PROG TOS_CANCEL,   //71    T:絪胆?        
        "",                    //72
        "",//TOS_ENGLISH,           //73    T:璣粂
        OS_ICON_VCD,           //74
        "",                    //75    //not use
        "",                    //76    //not use
        "CVBS",//OS_ICON_MP3,           //77
        OS_ICON_CDDA,          //78
        "48K",                    //79    //not use
        "96K",                    //80    //not use
        "192K",                    //81    //not use
        TOS_PICUP,             //82    T:礶簿
        TOS_PICDN,             //83    T:礶簿
        TOS_PICL,              //84    T:礶オ簿
        TOS_PICR,              //85    T:礶簿
        TOS_CHAPTER,           //86    T:彻竊
        TOS_ECHO,              //87    T:臫
        TOS_TITLE,             //88    T:夹肈
        "BAND",                    //89
        TOS_VOL,               //90    T:秖
        "DOWN SAMPLE",                    //91    //not use
        TOS_KEY,               //92    T:秸
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        TOS_9FRAME_1,          //94    T:虫Ρ礶
        TOS_AUTO_L,            //95    T:笆钡佰オ
        TOS_AUTO_R,            //96    T:笆钡佰
        "LOW",                    //97
        TOS_SEQUENCE,          //98    T:抖冀
        TOS_MENUPLAY,          //99    T:匡虫冀

        "",//TOS_SFE_OUT,            //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else
        "",//TOS_SFE_STD,          //101
        "",//OS_SFE_EHNANCE,        //102
#endif
        "MEDIUM",                    //103
        TOS_PROG_PLAY,         //104   T:絪导僵?
        "HIGH",                    //105
        TOS_DYNAMICRANGE,      //106     T:笆篈絛瞅
        OS_ICON_DVD,           //107
        TOS_OSD,               //108   T:礶陪ボ粂ē
        OS_ICON_SUBT,          //109
        TOS_TV_RATIO,          //110   T:棵辊礶ゑㄒ
        TOS_TV_SYS,            //111   T:筿跌诀╰参
        TOS_EXIT_MENU,         //112   T:癶砞﹚匡虫
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        TOS_AUD_OUT,           //113   T:计块
#endif
        TOS_VIDEO,             //114   T:跌癟块
        TOS_PASSWORD,          //115   T:盞絏
        TOS_RATING,            //116   T:
        TOS_BITSTREAM,         //117   T:SPDIF/方絏

#if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
#else           
        "",//TOS_ANALOG_6CH,        //118   T:AC3 6羘笵(not use)
#endif

        "SPDIF/PCM",           //119
//        "",//TOS_ANALOG_2CH,        //120   T:AC3 2羘笵(not use)
#ifdef SUPPORT_PALM
        "PAL-M",                //120
#else
        "",           //120
#endif
        #ifdef KSD_DVD//20030823
         #ifdef HANYANG_SETUPMENU   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
        #else
        "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
         #endif  
        #else
        TOS_YUV,               //121   T:跌繵だ秖
        #endif
        TOS_AUTO,              //122   T:笆
        TOS_OFF,               //123   T:闽
        "",//"TM/CH/TL",            //124
        TOS_CHAPTER,           //125   T:彻竊
        TOS_TITLE,             //126   T:夹肈
        OS_ICON_ANGLE,         //127
      #if  defined( HANYANG_SETUPMENU)||defined(SUPPORT_FUNCTION_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif
        TOS_16_9,              //129   T:16:9 --
        TOS_4_3LB,             //130   T:4:3LB --
        TOS_4_3PS,             //131
        "PAL",                 //132
        "NTSC",                //133
        "PAL60",               //134

        #ifdef RATING_8
            "3 PG",                //135   T:level 3
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else
            "2",                   //136   T:level 2
            "1 G",                 //137   T:level 1
            #endif
        #else
            TOS_NO_ADULT,          //135   T:(獶A)
            TOS_KID_ONLY,          //136   T:(ㄠ担)
            TOS_VIEW_ALL,          //137   T:(礚)
        #endif

        TOS_6CH_SETUP,         //138   T:6羘笵砞竚
        TOS_SUBWOOFER,         //139   T:禬
        TOS_SATURATION,         //140   SATURATION      //guolin 3-10-30
        TOS_ON,                //141   T:?        
        OS_DOBLY,              //142
        Ch_clock,              //143
        Ch_speaker,            //144
        TOS_CLEAR,             //145   T:睲埃
        "  T  C",                //146
        "--:--",               //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        TOS_EDIT,              //149   T:絪胯
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42,(TChinese).     
        TOS_SUBTITLE_LANG_2ND_SETUP,    //150
#else
        "",//OS_DIR1,               //150
#endif
#ifdef QSI_SETUP_MENU//liweihua 2004-6-15
        " 1 MIN",                   //151
        " 5 MIN",                   //152
        "10 MIN",                   //153
        "30 MIN",                   //154
#elif defined(ADJUST_JPEG_SLIDE_TIME)  ////lyc 2005/2/18
        "15 SEC",                   //151
        "30 SEC",                   //152
        "45 SEC",                   //153
        "50 SEC",                   //154          
#else
        "",//OS_DIR2,               //151
        OS_DIR3,               //152
        OS_DIR4,               //153
        "PAL-NC",//OS_DIR5,               //154
#endif
        TOS_LOCK,              //155   T:---- L
        TOS_UNLOCK,            //156   T:---- U
        TOS_HUE,                //157   HUE     //guolin 3-10-30 
        "PROLOGIC",//"-:--:--",             //158
        TOS_MOVIE_MODE,//TOS_TRK_S,             //159   T:(虫Ρ穓)
        TOS_MUSIC_MODE,//TOS_DISC_S,            //160   T:(羆盒穓)

#if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
#else
        "",//"TT:CH",               //161
#endif

        #ifdef REMAIN_TIME//nono 2-7-12 20:06
            "T",                   //162
        #else
            "",//"BOOKMARK",            //162
        #endif

        OS_DIR0,               //163
        TOS_CONTRAST,           //164   CONTRAST        //guolin 3-10-30 
        OS_DIR7,               //165
        OS_DIR8,               //166
        OS_DIR9,               //167
        TOS_CH,                //168   T:(羘笵)
        TOS_BRIGHT_SETUP,         //169   BRIGHTNESS        //guolin 3-10-30 
        "F/W ID",//TOS_FIRMWARE_ID,       //170   T:(硁ン絪絏)
        "CHIP ID",//TOS_CHIP_ID,           //171   T:(絪絏)
        TOS_REGION_CODE,       //172   T:(跋絏)
        "MEMORY",//TOS_FUNCTION,          //173   T:(滦弄滦佰)
        "DYNAMIC",//TOS_MODE,              //174   T:(家Α)
        "",//TOS_RECORD,            //175   T:(滦佰)
        "",//TOS_STUDY,             //176   T:(滦弄)
        "",//TOS_FOLLOW,            //177   T:(蛤弄)
        "MIC1 VOL",//TOS_COMPARE,           //178   T:(癸ゑ)
        "MIC2 VOL",//TOS_COUNTER,           //179   T:(滦Ω计)

#ifdef FUSS_DVD_AVD276
        TOS_PROV_CHAPTER,      //180   S:上一章节
        TOS_NEXT_CHAPTER,      //181   S:下一章节
//#elif defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#elif defined(NEXTPAGE_SYS)
        TOS_NEXT_PAGE,//NONO 20030813   //180
        TOS_PREV_PAGE,                  //181
#elif defined(SUPPORT_FUNCTION_MENU) 
	TOS_BATTERY_STATUS,	    //180
	TOS_SETUP,    		    //181
#else
        "",//TOS_LEVEL,             //180   T:魁家Α
        "",//TOS_HIGH,              //181   T:蔼珇借
#endif
#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//TOS_NORMAL,            //182   T:禬丁
#endif
        "",//TOS_SUPER,             //183   T:禬蔼珇借
        "",//TOS_OPERATING,         //184   T:秸竊よΑ
        "",//TOS_MANUAL,            //185   T:も笆
        OS_DIR10,              //186
        OS_DIR11,              //187
        TOS_CONCERT,           //188   T:(贾芔)
        TOS_CHURCH,            //189   T:(毙绑)
        TOS_PASSIVE,           //190   T:(吏露)
        TOS_WIDE,              //191   T:(糴初)
//        "",//TOS_AMPHITH,           //192   T:(蛾粿初)
//        "",//TOS_STADIUM,           //193   T:(蔨▅繻)
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192    3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        TOS_EQ,                //194   T:(А颗)
        TOS_STANDARD,          //195   T:(夹非)
        TOS_CLASSIC,           //196   T:(ㄥ)
        TOS_ROCK,              //197   T:(穘簎)
        TOS_JAZZ,              //198   T:(里)
        TOS_POP,               //199   T:(瑈︽)
        TOS_USER,              //200   T:(┦)
        TOS_ATTRIB,            //201   T:(┦)
        TOS_SF,                //202   T:(篊秈)
        TOS_SB,                //203   T:(篊癶)

            "C",                   //204   //show "C"


        TOS_CSPK,              //205   T:い竚喘羘竟
        TOS_SSPK,              //206   T:吏露喘羘竟
        "TV-RGB",               //207
        "4 PG13",              //208   S:辅导级
        TOS_CSPK_DELAY,        //209   T:い竚┑筐
        TOS_SSPK_DELAY,        //210   T:吏露┑筐
        TOS_FSPK,              //211   T:玡竚喘羘竟
        TOS_VIDEO_SETUP,        //212   VIDEO SETUP     //guolin 3-10-30
        "SHARPNESS",          //213   SHARPNESS
        TOS_SYS_SETUP,         //214   T:╰参砞﹚
        TOS_SPK_SETUP,         //215   T:喘羘竟砞﹚
        TOS_AUD_SETUP,         //216   T:繵砞﹚
        TOS_DEFAULT_SETUP,     //217   T:箇砞
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
             
        TOS_GROUP,             //218   T:竤舱

        #endif
        TOS_SSAVER_SETUP,      //219   T:棵辊玂臔
        TOS_SSAVER_1,          //220   T:家Α 1
        TOS_SSAVER_2,          //221   T:家Α 2
        TOS_SSAVER_3,          //222   T:家Α 3
        
        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                   //223   T:5保留
        #endif
        
        "6 R",                 //224   T:限制级
        TOS_ERR_DISC,          //225   T:岿粇盒片
        TOS_DIGITAL_SETUP,     //226   T:ゑ计砞﹚
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        TOS_MIC_ONOFF,         //227   T:沉砞﹚
        TOS_MIC_VOL,           //228   T:沉秖
        #endif
        TOS_CD_DEBUG,          //229   T:岿い     ------------- not use
        TOS_SMART_UPGRADE,     //230   T:醇ど
        TOS_UPGRADE_TO,        //231   T:どΘ
        TOS_UPGRADING,         //232   T:どい
        TOS_NOT_POWEROFF,      //233   T:づ闽诀
        TOS_REGION_0,          //234   T:0 跋
        TOS_REGION_1,          //235   T:1 跋
        TOS_REGION_2,          //236   T:2 跋
        TOS_REGION_3,          //237   T:3 跋
        TOS_REGION_4,          //238   T:4 跋
        TOS_LANG_SETUP,        //239   T:粂ē砞﹚
        #ifdef SUPPORT_FUNCTION_MENU 
	TOS_DISPLAY,	       //240
	#else 
        "",                    //240   //not use
        #endif
        TOS_RETURN_MAIN_SETUP, //241   T:()
        TOS_AUDIO_LANG_SETUP,  //242   T:(繵粂ē)
        TOS_SUBTITLE_LANG_SETUP,//243  T:(辊粂ē)
        TOS_MENU_LANG_SETUP,   //244   T:(匡虫粂ē)
        TOS_DOWNMIX_SETUP,     //245   T:(睼家Α)
        TOS_RESTORE_SETUP,     //246   T:(確)
        "LT/RT",               //247
        TOS_VSURROUND_SETUP,   //248   T:店览吏露羘
        TOS_DOLBY_OP_SETUP,    //249   T:块家Α
        TOS_DOLBY_LINE_SETUP,  //250   T:絬隔块
        TOS_DOLBY_RF_SETUP,    //251   T:RF 秸俱
        TOS_DUAL_MONO_SETUP,   //252   T:オ+
        TOS_MIX_MONO_SETUP,    //253   T:睼羘笵
        TOS_SURROUND_MODE,     //254   T:吏露家Α
        TOS_PRE_STOP,          //255   T:氨ゎ
//=================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER
},
#endif

#ifdef USE_GERMAN_OSD
//German
{
        "",                   //0
        "KEINE BILDPLATTE", //"KEINE DISD",         //1     T:礚盒
        "FALSCHE EINGABE",  //"INVALID ENTRY",      //2     T:眤岿 hand
        "TRK",          //"ST\xdc\x43K",        //3     T:Ρヘ
        OS_ICON_SVCD,         //4
        "DE-INTERLACE",//"CHINESISCH",         //5     T:簙粂
        "AUF",          //"\xdc\x46\x46NEN",    //6     T:
        "ZU",           //"SCHLIESSEN",         //7     T:闽
        "SPIE",         //"WIEDERGABE"="SPIELEN",         //8     T:冀
        "REGION 5",           //9     T:5 跋
        "SPIELPAUSE",       //"PAUSE",              //10    T:既氨
        "FREI",         //"RANDOM",             //11    T:繦诀冀
        "RESTARTEN",        //"RESUME",             //12    T:確冀
        "STOPPEN",      //"STOP",               //13    T:氨ゎ
        "TRITT",        //"SCHRITT",            //14    T:˙秈
        "AUSW\xc4HLEN",     //"AUSWAHL",            //15    T:匡拒
        "LESEN",        //"DISK WIRD ",         //16    T:弄盒
        "REGION 6",           //17    T:6 跋
        "ANALOG",             //18    T:家览
        "VORW\xc4RTS",      //"FF",                 //19    T:е秈
        "R\xdc""CKW\xc4""RTS",  //"FR",                 //20    T:е癶
        "N\xc4\x43""HST",       //"N\xc4\x43HSTES",     //21    T:Ρ >>

        //"N\xc4\x43HSTE SEITE",//"NEXTPAGE",           //22    T:
        "SERVO DEBUG",                   //22

        "LETZT",        //"VORIGES",            //23    T:Ρ <<

        //"LETZTE SEITE",//"PREVPAGE",              //24    T:
        "DIR",                   //24

        "ZUR\xdc""CK",      //"RETURN",             //25    T:垫虫
        Ch_repx,              //26
        Ch_rep1,              //27
        Ch_repd,              //28
        "AUS",          //"OFF"//"KEIN",        //29    T:礚
        "MENU",               //30    T:匡虫
        "PUNKTE",       //"SCORE",              //31    T:だ计
        "MARK",         //"MARKIERUNG"="MARK",  //32    T:癘拘  //Jeff 20020411
        "\xdc""BERFL\xdc""GEN", //"BROWSE",             //33    T:聅凝
        "PROG",         //"PROGRAM",            //34    T:絪祘
        "SAVING LOGO...",//                     //35    T:篊
        "MODE 1",       //"FREI"="FREE"         //36    T:家Α1
#ifdef SDRAM_16Mb_Mode
        "WIED.",        //"WIEDERHOLEN",        //37    T:確
        "DIR WIED.",        //"REP DIR",            //38    T:ヘ魁確
        "1 WIED.",      //"EINHEIT WIEDE",      //39    T:虫Ρ確
        "ALLE WIED.",       //"REP ALL",            //40    T:盒確

#else//SDRAM_16Mb_Mode
        "WIEDER",       //"WIEDERHOLEN",        //37    T:確
        "DIR WIEDER",       //"REP DIR",            //38    T:ヘ魁確
        "1 WIEDER",     //"EINHEIT WIEDE",      //39    T:虫Ρ確
        "ALLE WIEDER",      //"REP ALL",            //40    T:盒確
#endif//SDRAM_16Mb_Mode
        "WIEDER AUFHEBEN",  //"WIEDERHOLEN A",      //41    T:確
        "MODE 2",             //42    T:家Α2

        //"8",                  //43    S:8保留
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
        #else// #ifdef HJ_APEX_FIX_SHOW_OSD
        "8 ADULT",            //43
        #endif// #ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",
        #endif
        "7 NC-17",            //44

        "GEHE ZU",            //45    T:穓
        "RUHE",         //"STUMM",              //46    T:繰

        #ifdef SETUP_DONGLI459   //oujx for tonic
        "AUDIO L",      //"MONO LINKS",         //47    T:オ羘笵
        "AUDIO R",      //"MONO RECHTS",        //48    T:羘笵
        #else
        "MONO L",       //"MONO LINKS",         //47    T:オ羘笵
        "MONO R",       //"MONO RECHTS",        //48    T:羘笵
        #endif

        "STEREOTON",        //"STEREO",             //49    T:ミ砰羘
        "MUTE CANCEL",//"HALLE",        //"HALL",               //50    T:糴初
        "VOR ORT",      //"LIVE",               //51    T:瞷初
#ifdef QSI_SETUP_MENU//liweihua 2004-6-16
        "KARAOK SETUP",                   //52
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "",//"THEATRE",            //52    T:粿初(not use)
#endif
        "MODE 3",       //"SOLO"="SINGLE"       //53    T:家Α3
        OS_ICON_CDROM,        //54    //Jeff 200204113
        #ifdef OP_CUST_UI//libing 2005-5-11 11:39                      
        "JPEG TIME",             //"TIME"                //55    T:丁
        #else
        "ZEIT",            //"TIME"                //55    T:丁
        #endif
        #ifdef SHOW_MP4_INIT_STR   //wangwei-2004/4/28
        "INITIALIZING...",  //56
        #else
        "",//"9 TEILBILDER",        //"AUSWAHL",            //56    T:礶
        #endif
        
        "ZOOM",               //57    T:糴
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#elif defined(DOWNMIX_OFF_DISP_5CH_ON)
        "5.1CH ON",            //58 ZXB2005-4-27 16:21       
#else
        "",                    //58    //not use
#endif
        OS_ICON_LANG,         //59
        "ABTASTUNG",        //"INTRO",              //60    T:苯磞
        "UMGE",//"UMGEBEND",        //"SURROUND",           //61    T:吏露
        "WGS",          //"WGS EIN",        //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "",//"WGS AUS",            //63    T:抖冀
#endif
        "FREI AUFHEBEN",    //"RAND CANCEL",        //64    T:繦诀冀
        "BASS MODE",          //65    T:家Α
        "",//"EIN",                                          //66(not use)
        "A- WIEDERHOLEN",   //"A BIS B A EIN",      //67    T:確A-
        "PC-VGA",               //"PC-VGA",           //68
        "A-B WIEDERHOLEN",  //"A BIS B",            //69    T:確A-B
        "A-B AUFHEBEN",     //"A BIS B ABBRU",      //70    T:確
        "PRG AUFHEBEN",     //"PRG CANCEL",         //71    T:絪祘
        "",                   //72
        "",//"ENGLISCH",           //73    T:璣粂
#ifdef PULIANG_DVD  //yaowh add 04-12-17
        "VCD1.0",           //74
#else
        OS_ICON_VCD,          //74
#endif
        "",//"VCD 1.1",            //75
#if defined(SHOW_VCD_VER_INFO)||defined(SYBER_DVD)  //yaowh add 04-08-03
    #ifdef PULIANG_DVD  //yaowh add 04-12-17
        "VCD2.0",           //76
    #else
        OS_ICON_VCD20,        //76    //xulf 2003-11-17
    #endif
#else
        "",                  //76     //not use
#endif
        "CVBS",//OS_ICON_MP3,                                    //77(not use)
        OS_ICON_CDDA,         //78
        "48K",  //"",//"\xdc""BERFL\xdcGEN AUFHEBEN",   //"BROWSE CANCEL",      //79    T:聅凝(not use)
        "96K",  //"",//"ABTASTUNG AUFHEBEN",    //"INTRO CANCEL",       //80    T:苯磞(not use)
        "192K", //"",//"9 TEILBILDER AUFHEBEN",//"9FRAME CANCEL",      //81    T:礶(not use)
        "ZOOM HOCH",        //"ZOOM UP",            //82    T:礶簿
        "ZOOM NIEDER",      //"ZOOM DOWN",          //83    T:礶簿
        "ZOOM LINKS",       //"ZOOM LEFT",          //84    T:礶オ簿
        "ZOOM RECHT",       //"ZOOM RIGHT",         //85    T:礶簿
        "KA",           //"KAPITEL",            //86    T:彻竊
        "REVERBERATIO",     //"ECHO",               //87    T:睼臫
        "TT",           //"TITEL",              //88    T:夹肈
        "BAND",//"REVERBERATIO AUFHEBEN",//"ECHO AUS",           //89    T:睼臫

#ifdef SDRAM_16Mb_Mode
        "LAU.",//"LAUTST\xc4RKE",   //"VOLUME",             //90    T:秖
#else//SDRAM_16Mb_Mode
        "LAUTST\xc4RKE",    //"VOLUME",             //90    T:秖
#endif//SDRAM_16Mb_Mode

        "DOWN SAMPLE",  //"",//"RESTAURIEREN",      //"RESTORE",            //91    T:临(not use)
        "TON",          //"SCHL\x0dcSSE",       //92    T:秸
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        "9 TEILBILDER_1",   //"9FRAME_1",           //94    T:虫Ρ礶
        "AUTO L",             //95    T:笆钡佰オ
        "AUTO R",             //96    T:笆钡佰
        "LOW",//"LESEN...",     //"READING...",         //97
        "SEQ SPIELEN",      //"SEQ PLAY",           //98    T:抖冀
        "MENU ZEIGEN",      //"MENU PLAY",          //99    T:垫虫冀

        //"S-VIDEO",            //100(not use)
        //"NORMAL",             //101(not use)
        //"ZEIT",               //102   T:匡(not use)
        "LFE OUT",            //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else
        "STANDARD",           //101
        "ENHANCE",            //102
#endif
		#ifdef OP_CUST_UI
        "DIVX ID",                      //103
        #else
        "MEDIUM",//"TRITT",             //"STEP",               //103
        #endif
        "PRG SPIELEN",      //"PRG PLAY",           //104   T:絪祘冀
        "HIGH",//"WARTEN",      //"WAITING",            //105
        "DYNAMISC BERE",    //"DYNAMIC RANGE"="DYNAMISCHER BEREICH",      //106   T:笆篈絛瞅
        OS_ICON_DVD,          //107
        "OSD SPRACHE",      //"OSD SPRACHE",        //108   T:礶陪ボ粂ē
        OS_ICON_SUBT,         //109

        #ifdef SETUP_DONGLI459
        "TV SYSTEM",        //"TV ART",             //111   T:1qμ??÷¨?|?
        "TV TYP",       //"FERNSEHER",          //110   T:辊礶ゑㄒ
       #else
        "TV TYP",       //"FERNSEHER",          //110   T:?¨?1?|ìe-?à?è??§¨°
        #ifdef MINTON_DVD   //heqiang，2004-2-29 10:16
        "FERNSEHMODUS",     //111    "TV MODE     "S:(电视机制式)
        #else        
        "TV SYSTEM",        //"TV ART",             //111   T:1q|ì?????§?|?
        #endif//MINTON_DVD
        #endif//SETUP_DONGLI459

        "ZUR\xdc""CKTRITTA.",//"ZUR\xdc""CKTRITTAUFSTE",//"SETUP BEENDEN",     //112   T:癶砞竚垫虫
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "AUDIO AUSGABE",      //113   T:计絏块
#endif
        "VIDEO AUSGABE",      //114   T:跌繵块
        "KODE",         //"KENNWORT",           //115   T:盞絏
        "KLASSFIKATION",    //"RATING",             //116   T:
        "SPDIF/RAW",          //117   T:SPDIF/方絏

#if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
#else
        "",//"AC3 6KA",     //"AC3 6CH"="AC3 6KANAL", //118   T:AC3 6羘笵(not use)
#endif

        "SPDIF/PCM",          //119
//        "",//"AC3 6KA",       //"AC3 2CH",            //120   T:AC3 2羘笵(not use)
#ifdef SUPPORT_PALM
        "PAL-M",                //120
#else
        "",           //120
#endif
#ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
#elif defined(EASTECH_DVI)
        "YCbCr", //121
#else
        "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
#endif//SHOW_YCbCr
        

        "AUTO",               //122   T:笆
        "AUS",                //123   T:闽
        #ifdef SHOW_DRM_REGISTRATION_CODE_IN_SETUP
        "DIVX[R] VOD", //124
        #else
        "",//"TM/CH/TL",           //124
        #endif
        "KAPITEL",      //"CHAPTER",            //125   T:彻竊
        "TITEL",        //"TITLE",              //126   T:夹肈
        OS_ICON_ANGLE,        //127
      #if defined(HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif
        OS_16_9,              //129   T:16:9 --
        OS_4_3LB,             //130   T:4:3LB --
        OS_4_3PS,             //131
        "PAL",                //132
        "NTSC",               //133
        "PAL60",              //134

#ifdef RATING_8
       "3 PG",                //135   T:level 3
        #ifdef FIX_RATING_8_DISPLAY
        "2 G",                  //136   T:(level 2)
        "1 KID SAFE",                //137   T:(level 1)
        #else
        "2",                  //136   T:level 2
        "1 G",                //137   T:level 1
        #endif
#else
        "NO VOLLJ\x0c4",//"NO VOLLJ\x0c4"="NICHT F\xdcR ERWACHSENE",      //135   T:獶A
        "KINDERSICHERU",//"KINDERSICHERU"="F\xdcR KINDER SICHTIG",      //136   T:ㄠ担
        "VIEW ALLES",       //"VIEW ALL",           //137   T:礚
#endif


#if defined(SHOW_5_1CH)
        "5.1CH",              //138   T:6羘笵砞竚
#else
        "6KA AUFSTELLUNG",  //"6CH SETUP",          //138   T:6羘笵砞竚
#endif

        "SUBBA\xdfSTIMME",  //"SUBWOOFER",          //139   T:禬
        "SATURATION",         //140   SATURATION
        "EIN",                //141   T:秨
        OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
        "WEGR\xc4",     //"CLEAR"="WEGR\xc4UMEN",  //145   T:睲埃
        "  T  C",               //146
        "--:--",              //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "REDA",         //"EDIT"="REDAKTION",   //149   T:絪胯
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42,(German).
        "UNTERT SPRA 2",    //150
#else
        "",//OS_DIR1,              //150
#endif
#ifdef QSI_SETUP_MENU//liweihua 2004-6-15
        " 1 MIN",                   //151
        " 5 MIN",                   //152
        "10 MIN",                   //153
        "30 MIN",                   //154
#elif defined(ADJUST_JPEG_SLIDE_TIME)  ////lyc 2005/2/18
        "15 SEC",                   //151
        "30 SEC",                   //152
        "45 SEC",                   //153
        "50 SEC",                   //154          
#else
        "",//OS_DIR2,              //151
        OS_DIR3,              //152
        OS_DIR4,              //153
        "PAL-NC",//OS_DIR5,              //154
#endif
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
        "HUE",                //157   HUE
        "PROLOGIC",//"-:--:--",            //158
        "MOVIE MODE",//"TRACK SONDIERUNG",  //"TRACK SEARCH",       //159   T:虫Ρ穓
        "MUSIC MODE",//"BILDPLATTEN SONDIERUNG",//"DISC SEARCH",       //160   T:羆盒穓
        
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//"TT:KA",       //"TT:CH",              //161
        #endif

#ifdef REMAIN_TIME//nono 2-7-12 20:06
        "T",                  //162
#else
        "",//"BOOKMARK",           //162
#endif

        OS_DIR0,              //163
        "CONTRAST",           //164   CONTRAST
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
        "KANAL",        //"CHANNEL",            //168   T:羘笵
        "BRIGHTNESS",         //169   BRIGHTNESS
        "F/W ID",             //170   T:硁ン絪絏
#ifdef OP_CUST_UI  
		"CHECKSUM",  
#else		    
        "CHIP ID",            //171   T:(絪絏)        S:(芯片编码)
#endif
        "REGION",             //172   T:跋絏
        "MEMORY",//"FUNKTION",      //"FUNCTION",           //173   T:滦弄滦佰
        "DYNAMIC",//"MODEL",        //"MODE",               //174   T:家Α

        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

        //"",//"AUFNAHME",      //"RECORD",             //175   T:滦佰
        //"",//"STUDIEREN",     //"STUDY",              //176   T:滦弄
        //"",//"FOLGEN",        //"FOLLOW",             //177   T:蛤弄
        "MIC1 VOL",//"VERGLEICH",       //"COMPARE",            //178   T:癸ゑ
        "MIC2 VOL",//"Z\xc4HLER",       //"COUNTER",            //179   T:滦Ω计
//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP 
#elif defined(SUPPORT_FUNCTION_MENU) 
	OS_BATTERY_STATUS,	    //180
	OS_SETUP,    		    //181
#else
        "",//"NIVEAU",      //"LEVEL",              //180   T:魁家Α
        "",//"HOCH",            //"HIGH",               //181   T:蔼珇借
#endif
#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",              //?         //182   T:禬丁
#endif
        "",//"SUPER",               //?         //183   T:禬蔼珇借
        "",//"OPERATING",            //?            //184   T:秸竊よΑ
        "",//"MANUELL",     //"MANUAL",             //185   T:も笆
        OS_DIR10,             //186
        OS_DIR11,             //187
        "KONZERT",      //"CONCERT",            //188   T:贾芔
        "KIRCHE",       //"CHURCH",             //189   T:毙绑
        "PASSIV",       //"PASSIVE",            //190   T:吏露
        "BREIT",        //"WIDE",               //191   T:糴初
//        "",//"AMPHITHEATER",      //"AMPHITH",            //192   T:蛾粿初
//        "",//"STADION",       //"STADIUM",            //193   T:蔨▅繻
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192    3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#elif defined(PULIANG_DVD)//yaowh add 04-12-17
        "VERSION:WPQM_1A25101",     //192
        "REGION CODE",              //193
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "EQ",                 //194   T:А颗
        "STANDARD",           //195   T:夹非
        "KLASSISCH",        //"CLASSIC",            //196   T:ㄥ
        "ROCK",               //197   T:穘簎
        "JAZZ",               //198   T:里
        "POP",                //199   T:瑈︽
        "BENUTZER",     //"USER",               //200   T:┦
        "BENUTZER",     //"ATTRIB",             //201   T:┦

#ifdef SDRAM_16Mb_Mode
        "LAN. VOR.",//"SF",                 //202   T:篊秈
#else//SDRAM_16Mb_Mode
        "LANGSAM VORW\xc4""RTS",//"SF",                 //202   T:篊秈
#endif//SDRAM_16Mb_Mode

        "LANGSAM R\xdc""CKW\xc4RTS",//"SB",                 //203   T:篊癶


        "C",                  //204   //show "C"


        "ZENTRAL",      //"MITTE",              //205   T:い竚喘羘竟
        "R\xdc""CK",        //"HINTEN",             //206   T:吏露喘羘竟
        
        #ifndef HIMAGE_RGB
        "TV-RGB",              //207
        #else
        "RGB",                    //207
        #endif

        "4 PG13",             //208   S:辅导级

        "ZENTRAL-L\xc4""NGE",//"MITTE VERZ\x0d6"="ZENTRALVER-L\xc4""NGERUNG",    //209   T:い竚┑筐
        "R\xdc""CKVER-L\xc4""NGE",//"HINTEN VERZ\x0d6",   //210   T:吏露┑筐
        "VORDER LAUTSP",    //"LAUTSPR. VORNE"="VORDER LAUTSPRECHER",     //211   T:玡竚喘羘竟
        "VIDEO SETUP",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS
        "SYSTEM AUFSTELLUNG",   //"SYSTEM SETUP",       //214   T:╰参砞竚
        "LAUTSPRECHER AUFSTEL",//"LAUTSPRECHER ",      //215   T:喘羘竟砞竚
        "AUDIO LAUTSPRECHER",   //"AUDIO AUSGANG",      //216   T:繵砞竚
        "L\xdc""CKE",       //"STANDARDEINST",      //217   T:
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "KANAL KONTROLL",   //"OUT CHANNEL",        //218   T:羘笵北(not use)
        #endif
        
        #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU
        "   MNP   ",
        #else
        "BILDSCHIRMSCH",      //219   T:辊玂臔
        #endif
        #ifdef ORITRON_PASSWORD//libing 2005-4-29 9:53
        "SET DUFAULT VALUE",//
        "CLEAR PASSWORD",             //221   T:(辅导级)
        "LOADER LOCKED",
        #else
        "TYP 1",        //"ART 1",              //220   T:家Α 1
        "TYP 2",        //"ART 2",              //221   T:家Α 2
        "TYP 3",        //"ART 3",              //222   T:家Α 3
        #endif
        

        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   S:5保留
        #endif
        
        "6 R",                //224   S:限制级

        "BILDPLATTEN FEHLER",   //"ERR DISC",           //225   S:错误碟片
        "DIGITAL AUFST",    //"DIGITAL DIGIT"="DIGITAL AUFSTELLUNG",      //226   T:计絏砞竚
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "MIK AUFSTE",   //"MIC SETUP"="MIKROPHON AUFSTELLUNG",          //227   T:杠旦砞竚
        "MIK LAUTST\xc4RK",//"MIC VOL"="MIKROPHONS LAUTST\xc4RKE",            //228   T:杠旦秖
        #endif
        "CD RICHTIGSTELLUNG",   //"CD RECOVERING",      //     ------------- not use
        "INTELIGENZ AUFR\xdc""CKEN",//"SMART UPGRADE",      //230   T:醇ど
        "ZU V AUFR\xdc""CKEN",  //"UPGRADE TO V ",      //231   T:どΘ
        "AUFR\xdc""CKND",   //"UPGRADING",          //232   T:どい
        "STROM NICHT AUS",  //"NOT POWER OFF",      //233   T:づ闽诀
        "REGION 0",           //234   T:0 跋
        "REGION 1",           //235   T:1 跋
        "REGION 2",           //236   T:2 跋
        "REGION 3",           //237   T:3 跋
        "REGION 4",           //238   T:4 跋
        "SPRACHE AUFST",    //"OSD SPRACHE E"="SPRACHE AUFSTELLEN",      //239   T:粂ē砞竚
        #ifdef SUPPORT_FUNCTION_MENU 
	OS_DISPLAY,	     //240
	#else 
        "SRND AUFST",       //"SRND SETUP"="SRND AUFSTELLEN",         //240   T:吏露砞竚(not use)
        #endif
        "HAUPTSEITE",         //241   T:
        "AUDIO SPRACHE",    //"AUDIO LANG",         //242   T:繵粂ē
        "UNTERT SPRACH",    //"SUBTITLE LANG"="UNTERTITEL SPRACHE",      //243   T:辊粂ē
        "MENU SPRACHE",     //"MENU LANG",          //244   T:垫虫粂ē
    #if defined(DOWNMIX_DISP_20CH51CH)
		"2.0CH/5.1CH",//zxb		//245   T:(睼家Α)        
	#else
		"DOWNMIX",            //245   T:(睼家Α)       
	#endif  
        "RESTAURIEREN",     //"RESTORE",            //246   T:確
        "LT/RT",              //247
        "VSS",                //248   T:店览吏露羘
        "MODEL OP",     //"OP MODE",            //249   T:块家Α
        "LINIE AUSGABE",    //"LINE OUT",           //250   T:絬隔块
        "RF EINSTELUNG",    //"RF REMOD",           //251   T:RF 秸俱
        "DOPPEL MONO",      //"DUAL MONO",          //252   T:オ+
        "MIX MONO",           //253   T:睼羘笵
        "SURND MODEL",      //"SURND MODE",         //254   T:吏露家Α
#ifdef KSD_DVD
        "PRESS PLAY BUTTON TO CONTINUE",        //255   T:              S:请按播放键继续
#elif defined(SETUP_DONGLI459)
         "WEITER MIT WIEDERGABE",
#else
        "PRE STOPPEN",      //"PRE STOP",           //255   T:              S:准停止
#endif

//=================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER 
},
#endif

#ifdef USE_SPANISH_OSD
//Spanish
{
        "",                     //0
        "NO HAY DISCO",         //1     T:礚盒
        #if defined(BBK_DVD)||defined(INVALID_DISPLAY_HAND)     //#ifdef ALWAYS_DISPLAY_NODISC_ICON    fengjl add 3-12-7 14:28
        OS_NO,
        #else
        "ENTRADA INVALIDA",     //2     T:眤岿 hand
        #endif
        
        "TRK",                  //3     T:Ρヘ
        OS_ICON_SVCD,           //4
        "DE-INTERLACE",//"CHINO",               //5     T:簙粂
        "ABIERTO",              //6     T:
        "CERRADO",              //7     T:闽
//     "REPRODUCIR",            //8     T:冀
        "REPRO.",           //"PLAY"="REPRODUCIR""REPRODUCCION",  //8     T:冀
        "REGI\xd3\x4e 5",       //9     T:5 跋
        "PAUSA",                //10    T:既氨
        "ALEATORIA",            //11    T:繦诀冀
        "RESUMEN",              //12    T:確冀
        "PARAR",                //13    T:氨ゎ
        "PASO",                 //14    T:˙秈
        "SELECCIONAR",          //15    T:匡拒
        "LEER",                 //16    T:弄盒
        "REGI\xd3N 6",          //17    T:6 跋
        "AN\xc1\x4cOGO",        //18    T:家览
        "ADELANTAR",            //19    T:е秈
        "REGRESAR",             //20    T:е癶
        "SIGUIENTE",            //21    T:Ρ >>

        //"NEXTPAGE"="P\xc1GINA SIG",           //22    T:
        #ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        "PASSWD EDIT",      // 22
        #else
        "SERVO DEBUG",                     //22
        #endif

        "ANTERIOR",             //23    T:Ρ <<

        //"PREVPAGE"="P\xc1GINA ANT",           //24    T:
        "DIR",                     //24

        "REGRESAR",             //25    T:垫虫
        Ch_repx,                //26
        Ch_rep1,                //27
        Ch_repd,                //28
        "APA",                  //29    T:礚
        "ME\x4e\xda",           //30    T:匡虫
        "PUNTUAR",              //31    T:だ计
        "MAREA",                //32    T:癘拘
        "NAVEGAR",              //33    T:聅凝
        "PROG",                 //34    T:絪?
        "SAVING LOGO...",       //35    T:篊
        "MODE 1",               //36   T:家Α1
        "REP",                  //37    T:確
        "REP DIR",        //"REPETIR DIRECTORIO"="REP DIR"  //38    T:ヘ魁確
        "REP 1",                //39    T:虫Ρ確
        "REP TODO",             //40    T:盒確
        "CANCEL REP",
        ///*"CANCELAR REPETICI\xd3N" = "REP CANCEL",*/   //41    T:確
        "MODE 2",               //42   T:家Α2
        //"8",                    //43    S:8保留
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
        #else// #ifdef HJ_APEX_FIX_SHOW_OSD
        "8 ADULT",            //43
        #endif// #ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",
        #endif
        "7 NC-17",              //44    S:x级
        "VAYA A",               //45    T:穓
        "ENMUDECER",            //46    T:繰
        "MONO IZQ.",             //47    T:オ羘笵
        "MONO DER.",             //48    T:羘笵
        "EST\xc9\x52\x45\x4f",  //49    T:ミ砰羘
        "MUTE CANCEL",                      //50    T:糴初
        "EN VIVO",              //51    T:渤?
#ifdef QSI_SETUP_MENU//liweihua 2004-6-16
        "KARAOK SETUP",                   //52
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",                              //52
#else
        "",                     //52    //not use
#endif
        "MODE 3",               //53   T:家Α3
        OS_ICON_CDROM,          //54    //Jeff 200204113
        #ifdef OP_CUST_UI//libing 2005-5-11 11:39
        "JPEG TIME",
        #else
        "TIEMPO",               //55    T:丁
        #endif
       #ifdef SHOW_MP4_INIT_STR  //wangwei-2004/4/28
       "INITIALIZING...",  //56
       #else
        "",                     //56    T:礶
       #endif
       
       
        "ZOOM",                 //57    T:糴
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#elif defined(DOWNMIX_OFF_DISP_5CH_ON)
        "5.1CH ON",            //58 ZXB2005-4-27 16:21       
#else
        "",                    //58    //not use
#endif
        OS_ICON_LANG,           //59
        "INTRO",                //60    T:苯磞
        "SOEN",//"SONIDO ENVOL",            //61
        //"SONIDO ENVOLVENTE"="SURROUND",           //61    T:吏露
        "PBC",                  //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "PBC APAGADO",          //63    T:抖冀
#endif
        "CANCELAR ALEATORIO",   //64
        //"CANCELACI\xd3\x4e ALEATORIO"="RAND CANCEL",        //64    T:繦诀冀
        "BASS MODE",            //65   T:家Α
        "ENCENDER",             //66
        "REPETIR A-",           //67    T:確A-
        "PC-VGA",               //"PC-VGA",           //68
        "REPETIR A-B",          //69    T:確A-B
        "CANCELAR A-B",         //70    T:確
        "CANCELAR PRG",         //71    T:絪胆? 
        "",                     //72
        "INGL\xc9\x53",         //73    T:璣粂
#ifdef PULIANG_DVD
        "VCD1.0",               //74
#else
        OS_ICON_VCD,            //74
#endif
        "LIGHT MUSIC",                     //75     
        #if defined(SHOW_VCD_VER_INFO)||defined(SYBER_DVD)  //yaowh add for kenloon 04-08-03
    #ifdef PULIANG_DVD  //yaowh add 04-12-17
        "VCD2.0",           //76
    #else
        OS_ICON_VCD20,        //76    //xulf 2003-11-17
    #endif
#else
        "ELECTRON",                     //76    //not use
#endif
        "CVBS",//OS_ICON_MP3,            //77
        OS_ICON_CDDA,           //78
#ifdef NINTAUS_OSD_STR   
        "48KHZ",                   //79    //not use
        "96KHZ",                   //80    //not use
        "192KHZ",                   //81    //not use
#else
        "48K",                      //79    //not use
        "96K",                     //80    //not use
        "192K",                     //81    //not use
#endif

        "ZOOM ACERCAR",         //82      T:礶簿
        "ZOOM ALEJAR",          //83    T:礶簿
        "ZOOM ACERCA",          //84    T:礶オ簿
        "ZOOM DERECHO",         //85    T:礶簿
        "CA",                   //86    T:彻竊
        "ECO",                  //87    T:睼臫
        "TT",                   //88    T:夹肈
        "BAND",                     //89
        "VOL",                  //90    T:秖
        "DOWN SAMPLE",          //91    //not use
        "TECLA",                //92    T:秸
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        "CUADRI-9_1",           //94    T:虫Ρ礶
        "AUTO IZQ.",            //95    T:笆钡佰オ
        "AUTO DER.",            //96    T:笆钡佰
        "LOW",                      //97
        "TOCAR SEC.",           //98    T:抖冀
        "REPRODUCCI\xd3\x4e DE MEN\xda",
        //"MENU PLAY",          //99    T:垫虫冀

#if defined(SHOW_STANDBY_TIMER)
    
    #ifdef SETUP_DONGLI459
    "EST\xc1NDARD",         //100
    #else
    "LFE OUT",              //100
    #endif
     
    OS_VFD_TIME_NUM,        //101
#else
        #ifdef SETUP_DONGLI459
        "EST\xc1NDARD",         //101
        "LFE OUT",              //100 
        #else
        "LFE OUT",              //100
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "USB",                  //101
        #elif defined(SLEEP_CONTROL_COUNTER)  //ADD XHR 
        "120 MIN",     //101    
        #else
        "EST\xc1NDARD",         //101
        #endif  //#ifdef SELECT_MEDIA_IN_SETUPMENU
        #endif//#ifdef SETUP_DONGLI459
#endif

#if defined(SHOW_STANDBY_TIMER)
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "CARD",                 //102
#elif defined(SLEEP_CONTROL_COUNTER)  //ADD XHR 
   "90  MIN",
#else        
        "ENHANCE",              //102
#endif
        #ifdef OP_CUST_UI
        "DIVX ID",                      //103
        #else
        "MEDIUM",                       //103
        #endif
        "REPRODUCCI\xd3\x4e PROG",  //104   T:絪导僵?
        "HIGH",                     //105
#if defined(HJ_SVA_NEW_OSDSTR)
        "RANGO DINAMICO",      //106   T:笆篈絛瞅
        OS_ICON_DVD,          //107
        "IDIOMA OSD",//"OSD LANGUAGE",       //108   T:礶陪ボ粂ē
#else //#if defined(HJ_SVA_NEW_OSDSTR)
        "DYNAMIC RANGE",        //106   T:笆篈絛瞅
        OS_ICON_DVD,            //107
        "LENGUAJE OSD",         //108   T:礶陪ボ粂ē
#endif
        OS_ICON_SUBT,           //109
        "TIPO TV",
        //"RADIO DE VISUAL"="DISPLAY RATIO",      //110   T:辊礶ゑㄒ
#if defined(HJ_SVA_NEW_OSDSTR)
        "SISTEMA TV",//"TV TYPE",            //111   T:筿跌诀Α
#elif defined(MINTON_DVD)       //heqiang, 2004-2-29 10:43
        "MODO TV",              //111    "TV MODE"   S:(电视机制式)
#else
        "SYSTEMA TV",
        //"TIPO TV"="TV TYPE",            //111   T:筿跌诀Α
#endif//HJ_SVA_NEW_OSDSTR        
        "SALGA AJUSTE",         //112   T:癶砞竚垫虫

#if defined(HJ_SVA_NEW_OSDSTR)
        "SALIDA AUDIO",//"AUD OUT",            //113   T:计絏块
        "VIDEO",//"VIDEO",              //114   T:跌繵块
        "SENA",//"PASSWORD",           //115   T:盞絏
        "CLASIFICAR",//"RATING",             //116   T:
#else //#if defined(HJ_SVA_NEW_OSDSTR)
    #if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
    #elif defined(EASTECH_NEW_SETUP_MENU)
        "SALIDA DIGITAL",          //113   T:(计絏块)        S:(数码输出)
    #elif defined ( DP3240_SETUP_MENU)  //add xrh
	    "SALIDA DIGITAL",   
    #else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "SALIDA AUDIO",         //113   T:计絏块
    #endif
#ifdef DP3240_SETUP_MENU  //add xrh
        "VIDEO SALIDA",                //114   T:跌繵块
#else
        "VIDEO",                //114   T:跌繵块
#endif
        "CONTRAS\x45\xd1\x41",  //115   T:盞絏
        "CLASIFICAR",           //116   T:
#endif
    
#ifdef EASTECH_NEW_SETUP_MENU
        "RAW",          //117   T:(SPDIF/方絏)      S:(SPDIF/源码)
#elif defined (DP3240_SETUP_MENU)   //add xrh 
         "RAW", 
#else
        "SPDIF/RAW",            //117   T:SPDIF/方絏
#endif

        #if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",            //118
        #else
            "AC3 6CA",              //118   T:AC3 6羘笵
        #endif

#ifdef EASTECH_NEW_SETUP_MENU
        "PCM",          //117   T:(SPDIF/方絏)      S:(SPDIF/源码)
#elif defined (DP3240_SETUP_MENU)  //add xrh
         "PCM",  
#else
        "SPDIF/PCM",            //119
#endif

//        "AC3 2CA",                //120   T:AC3 2羘笵(not use)
#ifdef SUPPORT_PALM
        "PAL-M",                //120
#elif defined(SLEEP_CONTROL_COUNTER)
        "45  MIN",
#else
        "AC3 2CA",              //120   T:AC3 2羘笵(not use)
#endif
        #ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
        #elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
 #elif defined(DP3240_SETUP_MENU)
	  "YUV",  //121	
#elif defined(EASTECH_DVI)
        "YCbCr", //121
#else
        "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
#endif//SHOW_YCbCr
        
        "AUTO",                 //122   T:笆
        "APA",                  //123   T:闽
       #ifdef  SLEEP_CONTROL_COUNTER
	  "60  MIN",             //124
	   #elif defined(SHOW_DRM_REGISTRATION_CODE_IN_SETUP)
       "DIVX[R] VOD", //124
       #else
        "TM/CH/TL",             //124
        #endif
        "CAPITULO",             //125   T:彻竊
        "TITULO",               //126   T:夹肈
        OS_ICON_ANGLE,          //127
      #if  defined( HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU)||defined(EASTECH_NEW_SETUP_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
     #elif defined(ADD_P_SCAN_ONOFF)  //add xrh
	   "P-SCAN", 
    #elif defined(DP3240_SETUP_MENU)
	    "P-SCAN", 	 
      #else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif
        OS_16_9,                //129   T:16:9 --
        OS_4_3LB,               //130   T:4:3LB --
        OS_4_3PS,               //131
#ifdef HJ_SVA_NEW_OSDSTR
        "PAL-D",                //132
#else//HJ_SVA_NEW_OSDSTR
        "PAL",                  //132
#endif//HJ_SVA_NEW_OSDSTR
        "NTSC",                 //133
        "PAL60",                //134

        #ifdef RATING_8
            "3 PG",               //135   T:level 3
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else
            "2",                  //136   T:level 2
            "1 G",                //137   T:level 1
            #endif
        #else
            "ADULTOS NO",       //"NO ADULT",           //135   T:獶A
            "SEG PARA NI\xd1\x4f",
            //"SEGURO PARA NI\xd1OS"="KID SAFE",           //136   T:ㄠ担
            "VER TODO",     //"VIEW ALL",           //137   T:礚
        #endif

        #if defined(SHOW_5_1CH)
            "5.1CH",              //138   T:5.1羘笵
        #else
            "AJUSTE 6CA",
            //"AJUSTE DE CANAL 6"="6CH SETUP",          //138   T:6羘笵砞竚
        #endif

        "SUBGRAVES",            //139   T:禬
#ifdef HJ_SVA_NEW_OSDSTR
        "SATURACION",         //140   SATURATION
#else//#ifdef HJ_SVA_NEW_OSDSTR
        "SATURATION",         //140   SATURATION
#endif//#ifdef HJ_SVA_NEW_OSDSTR        
        "ENCEDIDO",             //141   T:? 
        OS_DOBLY,               //142
        Ch_clock,               //143
        Ch_speaker,             //144
        "DESP",                 //145   T:睲埃
        "  T  C",                 //146
        "--:--",                //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "EDITAR",                   //149   T:(絪胯)
        
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42,(Spanish).
        "SUBT\xcdTUL LG 2",     //150
#else
        "",//OS_DIR1,                //150
#endif        
        
#ifdef QSI_SETUP_MENU//liweihua 2004-6-15
        " 1 MIN",                   //151
        " 5 MIN",                   //152
        "10 MIN",                   //153
        "30 MIN",                   //154
#elif defined(ADJUST_JPEG_SLIDE_TIME)  ////lyc 2005/2/18
        "15 SEC",                   //151
        "30 SEC",                   //152
        "45 SEC",                   //153
        "50 SEC",                   //154        
#else
#ifdef BBK_DVD
        "5.1 CH",                  //151            
#else
        "",//OS_DIR2,                //151
#endif
        OS_DIR3,                //152
        OS_DIR4,                //153
       #ifdef SLEEP_CONTROL_COUNTER
	 "30  MIN",
       #else
        "PAL-NC",//OS_DIR5,                //154
#endif
#endif
        OS_LOCK,                //155   T:---- L
        OS_UNLOCK,              //156   T:---- U
#ifdef HJ_SVA_NEW_OSDSTR
        "MATIZ",                //157   HUE
#else//#ifdef HJ_SVA_NEW_OSDSTR
        "HUE",                //157   HUE
#endif//#ifdef HJ_SVA_NEW_OSDSTR        
        "PROLOGIC",              //158
        "MOVIE MODE",//"BUSQUEDA DE PISTA", //159   T:虫Ρ穓
        "MUSIC MODE",//"BUSQUEDA DE DISCO", //160   T:羆盒穓
        
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",                //161
        #endif

        #ifdef REMAIN_TIME//nono 2-7-12 20:06
            "T",                    //162
        #else
            "MARCA DE LIBRO",       //162
        #endif

        OS_DIR0,                //163
#ifdef HJ_SVA_NEW_OSDSTR
        "CONTRASTE",           //164   CONTRAST
#else//#ifdef HJ_SVA_NEW_OSDSTR
        "CONTRAST",           //164   CONTRAST
#endif//#ifdef HJ_SVA_NEW_OSDSTR        
        OS_DIR7,                //165
        OS_DIR8,                //166
        OS_DIR9,                //167
        "CANAL",                //168   T:羘笵
#ifdef HJ_SVA_NEW_OSDSTR
        "BRILLO",         //169   BRIGHTNESS
#else //#ifdef HJ_SVA_NEW_OSDSTR
        "BRIGHTNESS",         //169   BRIGHTNESS
#endif//#ifdef HJ_SVA_NEW_OSDSTR      
        "F/W ID",               //170   T:硁ン絪絏
#ifdef OP_CUST_UI  
		"CHECKSUM",  
#else		    
        "CHIP ID",            //171   T:(絪絏)        S:(芯片编码)
#endif
        "REGI\xd3N",            //172   T:跋絏
        "MEMORY",//"FUNCI\xd3N",            //173   T:滦弄滦佰
        "DYNAMIC",                  //174   T:家Α

        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

//        "GRABACI\xd3N",           //175   T:滦佰
//        "STUDIO",               //176   T:滦弄
//        "SEGUIR",             //177   T:蛤弄

        "MIC1 VOL",             //178   T:癸ゑ
        "MIC2 VOL",             //179   T:滦Ω计
//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "AVANZADO",//"ADVANCED",//"NEXT PAGE",              //180
        "AJUSTE AVANZADO",//"ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU) 
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181
#else
        "NIVEL",                //180   T:魁家Α
        "ALTO",                 //181   T:蔼珇借
#endif
#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",               //182   T:禬丁
#endif
        "SUPER",                //183   T:禬蔼珇借
        "OPERATING",            //184   T:秸竊よΑ
        "MANUAL",               //185   T:も笆
        OS_DIR10,               //186
        OS_DIR11,               //187
        "CONCIERTO",            //188   T:贾芔
        "IGLESIA",              //189   T:毙绑
        "PASIVO",               //190   T:吏露
        "ANCHO",                //191   T:糴初
//        "ANFITEATRO",         //192   T:蛾粿初
//        "ESTADIO",                //193   T:蔨▅繻
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192    3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#elif defined(PULIANG_DVD)//yaowh add 04-12-17
        "VERSION:WPQM_1A25101",     //192
        "REGION CODE",              //193
#elif defined(SLEEP_CONTROL_COUNTER)
   "15  MIN",
   "APA",
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "EQ",                   //194   T:А颗
        "EST\xc1NDARD",         //195   T:夹非
        "CL\xc1SICO",           //196   T:ㄥ
        "ROCK",                 //197   T:穘簎
        "JAZZ",                 //198   T:里
        "POP",                  //199   T:瑈︽
        "USUARIO",              //200   T:┦
        "ATTRIB",               //201   T:┦
        "SF",                   //202   T:篊秈
        "SB",                   //203   T:篊癶

        #ifdef ECHOTEST//nono 2-7-13 11:31
            "ECHO DECAY",       //"ECO DECAIMIENTO"="ECHO DECAY"         //204   T:睼臫瞏      //Jeff 20020506
        #else
            "C",                  //204   //show "C"
        #endif

        "CENTRO",               //"CENTER",             //205   T:い竚喘羘竟
        "TRASERO",              //"REAR",               //206   T:吏露喘羘竟

        #if !defined(HIMAGE_RGB)&&!defined(NINTAUS_OSD_STR)
        "TV-RGB",                //207
        #else
        "RGB",                    //207
        #endif

        "4 PG13",               //208   S:辅导级
        "RETRASO CENT.",
        //"RETRASO CENTRAL"="CENTER DELAY",       //209   T:い竚┑筐
        "RETRASO TRAS.",
        //"RETRASO TRASERO"="REAR DELAY",         //210   T:吏露┑筐
        "FRENTE",               //211   T:玡竚喘羘竟

#if defined(HJ_SVA_NEW_OSDSTR)
        "AJUSTE DE VIDEO",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS
        "AJUSTE DEL SISTEMA",//"SYSTEM SETUP",       //214   T:╰参砞竚
        "AJUSTE DE SONIDO",//"SPEAKER SETUP",      //215   T:喘羘竟砞竚
        "AJUSTE DE AUDIO",//"AUDIO SETUP",        //216   T:繵砞竚
        "DE FABRICA",//"DEFAULT",            //217   T:
#else//#if defined(HJ_SVA_NEW_OSDSTR)
        "VIDEO SETUP",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS
        "AJUSTE SYSTEMA",       //214   T:╰参砞竚
        "AJUSTE BOCINAS",       //215   T:喘羘竟砞竚
        "AJUSTE AUDIO",         //216   T:繵砞竚
        "DE F""\xc1""BRICA",    //217   T:
#endif
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #elif defined(SLEEP_CONTROL_COUNTER)  //ADD XRH 
	"CONTROL DE DORMIR", //SLEEP CONTROL
        #else
        "",                     //218   //not use
        #endif
        #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU
        "   MNP   ",
        #else
        "PROTECTOR",            //"SCREEN SAVER",       //219   T:辊玂臔
        #endif
        
        #ifdef ORITRON_PASSWORD//libing 2005-4-29 9:53
        "SET DUFAULT VALUE",
        "CLEAR PASSWORD",             //221   T:(辅导级)
        "LOADER LOCKED",
        #else
        "TYPO 1",               //220   T:家Α 1
        "TYPO 2",               //221   T:家Α 2
        "TYPO 3",               //222   T:家Α 3
        #endif
        

        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                    //223   T:5保留
        #endif
        
        "6 R",                  //224   T:限制级
        "ERR DE DISCO",         //225   S:错误碟片
        "AJUSTE DIGITAL",       //226   T:计絏砞竚
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "AJUSTE DE MIC",        //227   T:杠旦砞竚
        "VOL DE MIC",           //228   T:杠旦秖
        #endif
        "RECUPERACI\xd3N CD",
        //"RECUPERACI\xd3N CD"="CD RECOVERING",      //229   T:岿い     ------------- not use
        "MEJORA INTELIGENTE",   //230   T:醇ど
        "MEJORABLE A V",        //231   T:どΘ
        "MEJORAR",              //232   T:どい
        "NO APAGAR",            //233   T:づ闽诀
        "REGI\xd3N 0",          //234   T:0 跋
        "REGI\xd3N 1",          //235   T:1 跋
        "REGI\xd3N 2",          //236   T:2 跋
        "REGI\xd3N 3",          //237   T:3 跋
        "REGI\xd3N 4",          //238   T:4 跋
#ifdef HJ_SVA_NEW_OSDSTR
        "AJUSTE DE IDIOMA",//"LANG SETUP",         //239   T:粂ē砞竚
#else
        "AJUSTE LANG",          //239   T:粂ē砞竚
#endif
#ifdef SUPPORT_FUNCTION_MENU 
	"DISPLAY",    		//240
#else 
        "",                     //240   //not use
#endif
        "P\xc1\x47INA PRINC",
        //"P\xc1\x47INA PRINCIPAL"="MAIN PAGE",          //241   T:

#ifdef HJ_SVA_NEW_OSDSTR
        "IDIOMA AUDIO",//"AUDIO LANG",         //242   T:繵粂ē
        "IDIOMA SUB-T",//"SUBTITLE LANG",      //243   T:辊粂ē
        "IDIOMA MENU",//"MENU LANG",          //244   T:垫虫粂ē
#elif defined(BBK_DVD)//HJ_SVA_NEW_OSDSTR
        /*"AUDIO LANG",           //242   T:繵粂ē*/
        "AUDIO",           //242   T:繵粂ē  //axel 2004/1/27 03:58 eliminate "LANG"
        /*"SUBT\xcdTUL LANG",*/
        "SUBT\xcdTUL", //axel 2004/1/27 03:58 eliminate "LANG"
        //"SUBT\xcdTULO DE LANG"="SUBTITLE LANG",      //243   T:辊粂ē
        "MEN\xda LANG",         //244   T:垫虫粂ē
#else//HJ_SVA_NEW_OSDSTR
        "AUDIO LANG",           //242   T:繵粂ē
        "SUBT\xcdTUL LANG",
        //"SUBT\xcdTULO DE LANG"="SUBTITLE LANG",      //243   T:辊粂ē
        "MEN\xda LANG",         //244   T:垫虫粂ē
#endif

        #if defined(DOWNMIX_OFF_DISP_5CH_ON)
        "5.1CH ON",            //58 ZXB2005-4-27 16:21       
        #else
		"DOWNMIX",              //245   T:睼家Α
		#endif
        "RESTABLECER",          //246   T:確
        "IZQ/DER",              //247
        "VSS",                  //248   T:店览吏露羘
#ifdef HJ_SVA_NEW_OSDSTR
        "MONO OP",//"OP MODE",            //249   T:块家Α
        "SAIDA DE LIN.",//"SAIDA DE LINHA""LINE OUT",           //250   T:絬隔块
        "RF REMOD",           //251   T:RF 秸俱
        "IZQ-DER",              //252   T:オ+       
        "MONO MIX.",             //253   T:睼羘笵 
#else        
        "MODO OP",              //249   T:块家Α
        "L\xcdNEA SALIDA",      //250   T:絬隔块
        "MODO RF",              //251   T:RF 秸俱
        "IZQ+DER",              //252   T:オ+
        "MIX MONO",             //253   T:睼羘笵
#endif

        "MODO DE SURND",        //254   T:吏露家Α
#ifdef KSD_DVD
        "PRESS PLAY BUTTON TO CONTINUE",        //255   T:              S:请按播放键继续
#elif defined(TONIC_DVD)
         "ELIGAR REANUDACTION", 
#else
        "PRE ALTO",             //255   T:              S:准停止
#endif
//=================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER
},
#endif

#ifdef USE_FRENCH_OSD
//French
{
        "",                   //0
        "SANS DISQUE",          //"NO DISC",            //1     T:礚盒
        "ENTR\xc9""E INVALABLE",    //"INVALID ENTRY",      //2     T:眤岿 hand
        "TRK",                //3     T:Ρヘ
        OS_ICON_SVCD,         //4
        "DE-INTERLACE",         //"CHINESE",            //5     T:簙粂
        "OUVERT",           //"OPEN",               //6     T:
        "FERM\xc9",         //"CLOSE",              //7     T:闽
        "PRODU.",           //"PLAY"="PRODUIRE",               //8     T:冀
        "R\xc9GION 5",          //"REGION 5",           //9     T:5 跋
        "REPOS",            //"PAUSE",              //10    T:既氨
        "AU HASARD",            //"RANDOM",             //11    T:繦诀冀
        "R\xc9TABLIR",          //"RESUME",             //12    T:確冀
        "ARR\xcaT",         //"STOP",               //13    T:氨ゎ
        "MARCHE",           //"STEP",               //14    T:˙秈
        "CHOIX",            //"SELECT",             //15    T:匡拒
        "LIRE",             //"READ",               //16    T:弄盒
        "R\xc9GION 6",          //"REGION 6",           //17    T:6 跋
        "ANALOGIE",         //"ANALOG",             //18    T:家览
        "EN AVANT",         //"FORWARD",            //19    T:е秈
        "RECUL",            //"BACKWARD",           //20    T:е癶
        "PROCHAIN",         //"NEXT",               //21    T:Ρ >>
        "PROCHAIN PAGE",        //"NEXTPAGE",           //22    T:
        "PR\xc9""C\xc9""DENT",      //"PREV",               //23    T:Ρ <<

        //"PREVPAGE",           //24    T:
        "DIR",                   //24

        "RETOURNER",            //"RETURN",             //25    T:垫虫
        Ch_repx,              //26
        Ch_rep1,              //27
        Ch_repd,              //28
        //"NONE",               //29    T:礚
        "FER",              //"OFF"="FERM\xc9",               //29    T:礚
        "MENU",               //30    T:匡虫
        "NOTE",             //"SCORE",              //31    T:だ计
        "M\xc9MO",          //"MARK"="M\xc9MOIRE",               //32    T:癘拘  //Jeff 20020411
        "PARCOURIR",            //"BROWSE",             //33    T:聅凝
        "PROG",               //34    T:絪祘
        "SAVING LOGO...",     //                      //35    T:篊
        "MODE 1",             //36    T:家Α1
#ifdef SDRAM_16Mb_Mode
        "R\xc9P.",      //"REP",                //37    T:確
        "R\xc9P. TABL.",    //"REP DIR",            //38    T:ヘ魁確
        "R\xc9P. 1",        //"REP 1",              //39    T:虫Ρ確
        "TOUT R\xc9P.",     //"REP ALL",            //40    T:盒確
#else//SDRAM_16Mb_Mode
        "R\xc9P\xc9TER",        //"REP",                //37    T:確
        "R\xc9P\xc9TER LE TABLEAU", //"REP DIR",            //38    T:ヘ魁確
        "R\xc9P\xc9TER 1",      //"REP 1",              //39    T:虫Ρ確
        "TOUT R\xc9P\xc9TER",       //"REP ALL",            //40    T:盒確
#endif//SDRAM_16Mb_Mode
        "ANNULER LA R\xc9P\xc9TITION",  //"REP CANCEL",         //41    T:確
        "MODE 2",             //42    T:家Α2

        //"8",                  //43    S:8保留
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
        #else// #ifdef HJ_APEX_FIX_SHOW_OSD
        "8 ADULT",            //43
        #endif// #ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",
        #endif
        "7 NC-17",            //44    S:x级

        "ALLER",            //"GOTO",               //45    T:穓
        "ST\xc9R\xc9O",         //"MUTE",               //46    T:繰

#ifdef SDRAM_16Mb_Mode
        "MONO GA.",         //"MONO L",             //47    T:オ羘笵
        "MONO DR.",         //"MONO R",             //48    T:羘笵
#else//SDRAM_16Mb_Mode        
        "MONO GAUCHE",          //"MONO L",             //47    T:オ羘笵
        "MONO DROIT",           //"MONO R",             //48    T:羘笵
#endif//SDRAM_16Mb_Mode

        "ST\xc9R\xc9O",         //"STEREO",             //49    T:ミ砰羘
        "MUTE CANCEL",               //50    T:糴初
        "EN VIE",           //"LIVE",               //51    T:瞷初
#ifdef QSI_SETUP_MENU//liweihua 2004-6-16
        "KARAOK SETUP",                   //52
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "TH\xc9""ATRE",         //"THEATRE",            //52    T:粿初(not use)
#endif
        "MODE 3",             //53    T:家Α3
        OS_ICON_CDROM,        //54    //Jeff 200204113
        #ifdef OP_CUST_UI//libing 2005-5-11 11:39
        "JPEG TIME",
        #else
        "TEMPS",            //"TIME",               //55    T:丁
        #endif
        #ifdef SHOW_MP4_INIT_STR  //wangwei-2004/4/28
        "INITIALIZING..." ,   //56
        #else
        "CADRE 9",          //"9FRAME",             //56    T:礶
        #endif
        
        "ZOOM",               //57    T:糴
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                    //58    //not use
#endif
        OS_ICON_LANG,         //59
        "INTRO",              //60    T:苯磞
        "ENTR",//"ENTOURER",            //"SURROUND",           //61    T:吏露
        "PBC",                      //?         //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "PBC FERM\xc9",         //"PBC OFF",            //63    T:抖冀
#endif
        "ANNULER LE HASARD",        //"RAND CANCEL",        //64    T:繦诀冀
        "BASS MODE",          //65    T:家Α
        "POWER ON",           //66(not use)
        "R\xc9P\xc9TER A-",     //"REPEAT A-",           //67    T:確A-
        "PC-VGA",               //"PC-VGA",           //68
        "R\xc9P\xc9TER A-B",        //"REPEAT A-B",          //69    T:確A-B
        "ANNULER A-B",          //"A-B CANCEL",          //70    T:確
        "ANNULER PROG",         //"PRG CANCEL",         //71    T:絪祘
        "",                   //72
        "ANGLAIS",          //"ENGLISH",            //73    T:璣粂
        OS_ICON_VCD,          //74
        "VCD 1.1",            //75
        "VCD 2.0",            //76
        "CVBS",//OS_ICON_MP3,          //77(not use)
        OS_ICON_CDDA,         //78
        "48K", //"ANNULER PARCOURIR",       //"BROWSE CANCEL",      //79    T:聅凝(not use)
        "96K", //"ANNULER INTRO",       //"INTRO CANCEL",       //80    T:苯磞(not use)
        "192K", //"ANNULER CADRE 9",        //"9FRAME CANCEL",      //81    T:礶(not use)
        "ZOOM VERS LE HAUT",        //"ZOOM UP",            //82      T:礶簿
        "ZOOM VERS LE BAS",     //"ZOOM DOWN",          //83    T:礶簿
        "ZOOM \xc0"" GAUCHE",       //"ZOOM LEFT",          //84    T:礶オ簿
        "ZOOM \xc0"" DROIT",        //"ZOOM RIGHT",         //85    T:礶簿
        "CH",                 //86    T:彻竊
        "ECHO",               //87    T:睼臫
        "TT",                 //88    T:夹肈
        "BAND",//"ANNULER ECHO",            //"ECHO CANCEL",        //89    T:睼臫
        "VOL",                //90    T:秖
        "DOWN SAMPLE",  //"RESTAURER",          //"RESTORE",            //91    T:临(not use)
        "KEY",                //92    T:秸
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        "CADRE 9_1",            //"9FRAME_1",           //94    T:虫Ρ礶
        "AUTO GAUCHE",          //"AUTO L",             //95    T:笆钡佰オ
        "AUTO DROIT",           //"AUTO R",             //96    T:笆钡佰
        "LOW",//"LIRE",             //"READING...",         //97
        "PRODUIRE D'APR\xc8S SEQ",  //"SEQ PLAY",           //98    T:抖冀
        "PRODUIRE D'APR\xc8S MENU", //"MENU PLAY",          //99    T:垫虫冀

        //"S-VIDEO",            //100(not use)
        //"NORMAL",             //101(not use)
        //"TIME",               //102   T:匡(not use)
        "LFE OUT",            //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else
        "STANDARD",           //101
        "ENHANCE",            //102
#endif        
		#ifdef OP_CUST_UI
        "DIVX ID",                      //103
        #else
        "MEDIUM",               //"STEP",               //103
        #endif
        "PRODUIRE D'APR\xc8S PROG", //"PRG PLAY",           //104   T:絪祘冀
        "HIGH",//"ATTENDEZ",            //"WAITING",            //105
        "RANG\xc9""E",          //"DYNAMIC RANGE",      //106   T:笆篈絛瞅
        OS_ICON_DVD,          //107
        "OSD LANGUE",           //"OSD LANGUAGE",       //108   T:礶陪ボ粂ē
        OS_ICON_SUBT,         //109

 #ifdef SETUP_DONGLI459
        "SYSR\xc8""ME D'TV",        //"TV TYPE",            //111   T:1qμ??÷¨?|?
      #ifdef SDRAM_16Mb_Mode
        "SYSR\xc8"" D'TV",      //"TV TYPE",            //111   T:筿跌诀Α
      #else//SDRAM_16Mb_Mode
     "TYPE DE TV",          //"DISPLAY RATIO",      //110   T:?ì1?μe-±¤?¨ò
      #endif//SDRAM_16Mb_Mode
#else//#ifdef SETUP_DONGLI459
        "TYPE DE TV",           //"DISPLAY RATIO",      //110   T:辊礶ゑㄒ
#ifdef SDRAM_16Mb_Mode
        "SYSR\xc8"" D'TV",      //"TV TYPE",            //111   T:筿跌诀Α
#else//SDRAM_16Mb_Mode
        #ifdef MINTON_DVD       //heqiang, 2004-2-29 10:50 
        "MODE TV",              //111    "TV MODE"   S:(电视机制式)
        #else
        "SYSR\xc8""ME D'TV",        //"TV TYPE",            //111   T:筿跌诀Α
        #endif//MINTON_DVD   
#endif//SDRAM_16Mb_Mode
#endif//SETUP_DONGLI459

        "SORTIE SETUP",//"SORTIE DE SETUP",     //"EXIT SETUP",         //112   T:癶砞竚垫虫
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "SOTIE D'AUD",          //"AUD OUT",            //113   T:计絏块
#endif
        "VIDEO",              //114   T:跌繵块
        "MOT DE PASSAG",        //"PASSWORD",           //115   T:盞絏
        "CLASSE",           //"RATING",             //116   T:
        "SPDIF/RAW",          //117   T:SPDIF/方絏

#if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
#else
        "AC3 5.1CA",            //"AC3 5.1CH",          //118   T:AC3 5.1羘笵(not use)
#endif

        "SPDIF/PCM",          //119
//        "AC3 2CA",            //"AC3 2CH",            //120   T:AC3 2羘笵(not use)
#ifdef SUPPORT_PALM
        "PAL-M",                //120
#else
        "",           //120     
#endif
        #ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
        #elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
#elif defined(EASTECH_DVI)
        "YCbCr", //121
#else
        "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
#endif//SHOW_YCbCr
        
        "AUTO",               //122   T:笆
        "FER",              //"OFF"="FERM\xc9",                //123   T:闽
        #ifdef SHOW_DRM_REGISTRATION_CODE_IN_SETUP
        "DIVX[R] VOD", //124
        #else
        "TM/CH/TL",           //124
        #endif
        "CHAPITRE",         //"CHAPTER",            //125   T:彻竊
        "TITRE",            //"TITLE",              //126   T:夹肈
        OS_ICON_ANGLE,        //127
     #if defined(HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU) //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif
        OS_16_9,              //129   T:16:9 --
        OS_4_3LB,             //130   T:4:3LB --
        OS_4_3PS,             //131
        "PAL",                //132
        "NTSC",               //133
        "PAL60",              //134

#ifdef RATING_8
        "3 PG",               //135   T:level 3
        #ifdef FIX_RATING_8_DISPLAY
        "2 G",                  //136   T:(level 2)
        "1 KID SAFE",                //137   T:(level 1)
        #else
        "2",                  //136   T:level 2
        "1 G",                //137   T:level 1
        #endif
#else
        "NON ADULTE",           //"NO ADULT",           //135   T:獶A
        "ENFANT SUR",           //"KID SAFE",           //136   T:ㄠ担
        "VUE POR TOUT",         //"VIEW ALL",           //137   T:礚
#endif


#if defined(SHOW_5_1CH)
        "5.1CA",            //"5.1CH",              //138   T:5.1羘笵
#else
        "AJUSTER 6CA",          //"6CH SETUP",          //138   T:6羘笵砞竚
#endif

        "SUPER-WOOFER",         //"SUBWOOFER",          //139   T:禬
        "SATURATION",         //140   SATURATION
        "OUVERT",           //"ON",                 //141   T:秨
        OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
        "D\xc9GA.",//"D\xc9GAGER",          //"CLEAR",              //145   T:睲埃
        "  T  C",               //146
        "--:--",              //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "EDIT",               //149   T:絪胯
 
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42,(French).
        "SOUSTITR LG 2",         //150
#else         
        "",//OS_DIR1,              //150
#endif

#ifdef QSI_SETUP_MENU//liweihua 2004-6-15
        " 1 MIN",                   //151
        " 5 MIN",                   //152
        "10 MIN",                   //153
        "30 MIN",                   //154
#elif defined(ADJUST_JPEG_SLIDE_TIME)  ////lyc 2005/2/18
        "15 SEC",                   //151
        "30 SEC",                   //152
        "45 SEC",                   //153
        "50 SEC",                   //154        
#else
        "",//OS_DIR2,              //151
        OS_DIR3,              //152
        OS_DIR4,              //153
        "PAL-NC",//OS_DIR5,              //154
#endif
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
        "HUE",                //157   HUE
        "PROLOGIC",            //158
        "MOVIE MODE",//"CHERCHER LA PISTE",     //"TRACK SEARCH",       //159   T:虫Ρ穓
        "MUSIC MODE",//"CHERCHER LA DISQUE",        //"DISC SEARCH",        //160   T:羆盒穓

        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
#else
        "",              //161
#endif

#ifdef REMAIN_TIME//nono 2-7-12 20:06
        "T",                  //162
#else
        "BOOKMARK",           //162
#endif

        OS_DIR0,              //163
        "CONTRAST",           //164   CONTRAST
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
        "CANNAL",           //"CHANNEL",            //168   T:羘笵
        "BRIGHTNESS",         //169   BRIGHTNESS
        "F/W ID",             //170   T:硁ン絪絏
#ifdef OP_CUST_UI  
		"CHECKSUM",  
#else		    
        "CHIP ID",            //171   T:(絪絏)        S:(芯片编码)
#endif
        "R\xc9""GION",          //"REGION",             //172   T:跋絏
        "MEMORY",           //"FUNCTION",           //173   T:滦弄滦佰
        "DYNAMIC",               //174   T:家Α

        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

//        "ENREGISTRER",            //"RECORD",             //175   T:滦佰
//        "ETUDIER",            //"STUDY",              //176   T:滦弄
//        "SUIVRE",         //"FOLLOW",             //177   T:蛤弄
 
        "MIC1 VOL",         //"COMPARE",            //178   T:癸ゑ
        "MIC2 VOL",         //"COUNTER",            //179   T:滦Ω计
//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU) 
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181
#else
        "NIVEAU",           //"LEVEL",              //180   T:魁家Α
        "HAUT",             //"HIGH",               //181   T:蔼珇借
#endif
#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",                  //?         //182   T:禬丁
#endif
        "SUPER",                    //?         //183   T:禬蔼珇借
        "OPERATING",                //?         //184   T:秸竊よΑ
        "MANUEL",           //"MANUAL",             //185   T:も笆
        OS_DIR10,             //186
        OS_DIR11,             //187
        "CONCERT",            //188   T:贾芔
        "EGLISE",           //"CHURCH",             //189   T:毙绑
        "PASSIF",           //"PASSIVE",            //190   T:吏露
        "LARGE",            //"WIDE",               //191   T:糴初
//        "AMPHIETH\xc9\xc2TRE",        //"AMPHITH",            //192   T:蛾粿初
//        "STADE",          //"STADIUM",            //193   T:蔨▅繻
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192    3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "EQ",                 //194   T:А颗
        "STANDARD",           //195   T:夹非
        "CLASSIC",            //196   T:ㄥ
        "ROCK",               //197   T:穘簎
        "JAZZ",               //198   T:里
        "POP",                //199   T:瑈︽
        "UTILISATEUR",          //"USER",               //200   T:┦
        "ATTRIB",             //201   T:┦
        "SF",                                   //202   T:篊秈
        "SB",                 //203   T:篊癶

#ifdef ECHOTEST//nono 2-7-13 11:31
        "ECHO DECAY",         //204   T:睼臫瞏      //Jeff 20020506
#else
        "C",                  //204   //show "C"
#endif

        "CENTRE",           //"CENTER",             //205   T:い竚喘羘竟
        "ARRI\xc8RE",           //"REAR",               //206   T:吏露喘羘竟

        #ifndef HIMAGE_RGB
        "TV-RGB",              //207
        #else
        "RGB",                    //207
        #endif


        "4 PG13",             //208   S:辅导级

        "DIFF\xc9RER CENT",
        //"CENTER DELAY"="DIFF\xc9RER LE CENTRE",       //209   T:い竚┑筐
        "DIFF\xc9RER ARRI",     //"REAR DELAY"="DIFF\xc9RER L'ARRI\xc8RE",         //210   T:吏露┑筐
        "DEVANT",           //"FRONT",              //211   T:玡竚喘羘竟
        "VIDEO SETUP",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS
        "AJUSTER LE SYST\xc8ME",    //"SYSTEM SETUP",       //214   T:╰参砞竚
        "AJUSTER L'ORATEUR",        //"SPEAKER SETUP",      //215   T:喘羘竟砞竚
        "AJUSTER AUDIO",        //"AUDIO SETUP",        //216   T:繵砞竚
        "D\xc9""FAUT",          //"DEFAULT",            //217   T:
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",                                  //218
        #else
        "SORTIE CANNEL",                            //218
        #endif
        //"OUT CHANNEL"="SORTIE DE CANNEL",        //218   T:羘笵北(not use)
        #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU
        "   MNP   ",
        #else
        "GARDI. L'ECR.",
        #endif
        //"SCREEN SAVER"="GARDIEN DE L'ECRAN",       //219   T:辊玂臔
        #ifdef ORITRON_PASSWORD//libing 2005-4-29 9:53
        "SET DUFAULT VALUE",
        "CLEAR PASSWORD",             //221   T:(辅导级)
        "LOADER LOCKED",
        #else
        "TYPE 1",             //220   T:家Α 1
        "TYPE 2",             //221   T:家Α 2
        "TYPE 3",             //222   T:家Α 3
		#endif
        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   S:5保留
        #endif
        
        "6 R",                //224   S:限制级

        "ERREUR DE DISQUE",     //"ERR DISC",           //225     S:错误碟片
        "AJUSTER DIGITAL",      //"DIGITAL SETUP",      //226   T:计絏砞竚
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "AJUSTER MIC",          //"MIC SETUP",          //227   T:杠旦砞竚
        "VOL DE MIC",           //"MIC VOL",            //228   T:杠旦秖
        #endif
        "R\xc9""CUP\xc9RATION CD",  //"CD RECOVERING",      //229   T:岿い     ------------- not use
        "ESCALADE INTELLIGENTE",    //"SMART UPGRADE",      //230   T:醇ど
        "SUCC\xc8S D'ESCALADE",     //"UPGRADE TO V ",      //231   T:どΘ
        "EN COURS D'ESCALADE",      //"UPGRADING",          //232   T:どい
        "NE PAS \xc9TEINDRE",       //"NOT POWER OFF",      //233   T:づ闽诀
        "R\xc9""GION 0",        //"REGION 0",           //234   T:0 跋
        "R\xc9""GION 1",        //"REGION 1",           //235   T:1 跋
        "R\xc9""GION 2",        //"REGION 2",           //236   T:2 跋
        "R\xc9""GION 3",        //"REGION 3",           //237   T:3 跋
        "R\xc9""GION 4",        //"REGION 4",           //238   T:4 跋
        "AJUSTER DE LANG",      //"LANG SETUP",         //239   T:粂ē砞竚
        #ifdef SUPPORT_FUNCTION_MENU
	"DISPLAY",		//240
	#else 
        "AJUSTER DE SRND",      //"SRND SETUP",         //240   T:吏露砞竚(not use)
        #endif
        "RET. PAGE PR.",        //"MAIN PAGE"="RETOUR \xc0"" LA PAGE PRINCIPALE",          //241   T:
#ifdef BBK_DVD
        /*"AUDIO LANG",         //242   T:繵粂ē*/
        "AUDIO",         //242   T:繵粂ē axel 2004/1/27 03:58 eliminate "LANG"
        /*"SOUSTITR LANG",      //"SUBTITLE LANG"="SOUS-TITRE LANG",      //243   T:辊粂ē*/
        "SOUSTITR",     //"SUBTITLE LANG"="SOUS-TITRE LANG",      //243   T:辊粂ē //axel 2004/1/27 03:58 eliminate "LANG"
#else
        "AUDIO LANG",         //242   T:繵粂ē
        "SOUSTITR LANG",        //"SUBTITLE LANG"="SOUS-TITRE LANG",      //243   T:辊粂ē
#endif
        "MENU LANG",          //244   T:垫虫粂ē
        "MODE MIXTE",           //"DOWNMIX",            //245   T:睼家Α
        "RETOUR",           //"RESTORE",            //246   T:確
        "LT/RT",              //247
        "VSS",                //248   T:店览吏露羘
        "MODE OP",          //"OP MODE",            //249   T:块家Α
        "LIGNE SORTIE",         //"LINE OUT",           //250   T:絬隔块
        "AJUSTER RF",           //"RF REMOD",           //251   T:RF 秸俱
        "G+D",              //"DUAL MONO",          //252   T:オ+
        "MONO MIXTE",           //"MIX MONO",           //253   T:睼羘笵
        "MODE SURND",           //"SURND MODE",         //254   T:吏露家Α
#ifdef KSD_DVD
        "PRESS PLAY BUTTON TO CONTINUE",        //255   T:              S:请按播放键继续
#elif defined(SETUP_DONGLI459)
        "CHOISIR PLAY POUR CONTINUER",
#else
        "PR\xc9""AJUSTER",      //"PRE STOP",           //255   T:              S:准停止
#endif
//=================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER
},
#endif
#ifdef USE_PORTUGUESE_OSD
//Portuguese
{
        "",                   //0
        "SEM DISCO",//"NO DISC",            //1     T:礚盒
        #ifdef   DP3240_SETUP_MENU
	 OS_NO,	
        #else
        "ENTRADA INVALIDA",//"INVALID ENTRY",      //2     T:眤岿 hand
        #endif
        "TRK",                //3     T:Ρヘ
        OS_ICON_SVCD,         //4
        "DE-INTERLACE",            //5     T:簙粂
        "ABRIR",//"OPEN",               //6     T:
        "FECHAR",//"CLOSE",              //7     T:闽
#ifdef HJ_SVA_NEW_OSDSTR
        "REPRO.",//"REPRODUCAO",//"PLAY",               //8     T:冀
#else //HJ_SVA_NEW_OSDSTR
        "LEITU.",//RE",//"PLAY",               //8     T:冀
#endif //HJ_SVA_NEW_OSDSTR
        "REGI""\xc3""O 5",//"REGION 5",           //9     T:5 跋
        "PAUSA",//"PAUSE",              //10    T:既氨
        "ALEAT""\xd3""RIO",//"RANDOM",             //11    T:繦诀冀
        "RESUMO",//"RESUME",             //12    T:確冀
        "PARAR",//"STOP",               //13    T:氨ゎ
#ifdef HJ_SVA_NEW_OSDSTR
        "PASSO A",//"STEP",               //14    T:˙秈
#else //HJ_SVA_NEW_OSDSTR
        "PASSO A PASSO",//"STEP",               //14    T:˙秈
#endif //HJ_SVA_NEW_OSDSTR

        "ESCOLHER",//"SELECT",             //15    T:匡拒

#ifdef HJ_SVA_NEW_OSDSTR
        "LENDO",//"READ",               //16    T:弄盒
#else//HJ_SVA_NEW_OSDSTR
        "LER",//"READ",               //16    T:弄盒
#endif//HJ_SVA_NEW_OSDSTR

        "REGI""\xc3""O 6",//"REGION 6",           //17    T:6 跋
#ifdef HJ_SVA_NEW_OSDSTR
        "ANALOGICO",//"ANALOG",             //18    T:家览
#else//#ifdef HJ_SVA_NEW_OSDSTR
        "ANAL""\xd3""GICO",//"ANALOG",             //18    T:家览
#endif//#ifdef HJ_SVA_NEW_OSDSTR
        "AVAN""\xc7""AR",//"FORWARD",            //19    T:е秈
        "RECUAR",//"BACKWARD",           //20    T:е癶
        "SEGUINTE",//"NEXT",               //21    T:Ρ >>

        //"NEXTPAGE",           //22    T:
        "SERVO DEBUG",                   //22

        "ANTERIOR",//"PREV",               //23    T:Ρ <<

        //"PREVPAGE",           //24    T:
        "DIR",                   //24

        "VOLTAR PARA ATR""\xc1""S",//"RETURN",             //25    T:垫虫
        Ch_repx,              //26
        Ch_rep1,              //27
        Ch_repd,              //28
        //"NONE",               //29    T:礚
        "DES",//"OFF"="DESLIGADO",               //29    T:礚
        "MENU",               //30    T:匡虫
        "SCORE",              //31    T:だ计
        "MARK",               //32    T:癘拘  //Jeff 20020411
        "NAVEGAR",//"BROWSE",             //33    T:聅凝
        "PROG",               //34    T:絪祘
        "SAVING LOGO...",       //35
        "MODE 1",//"LIVRE",             //36    T:家Α1
#ifdef SDRAM_16Mb_Mode
        "REP.",//"REP",                //37    T:確
        "REP. DIREC.",//"REP DIR",            //38    T:ヘ魁確

        "REPETIR 1",//"REP 1",              //39    T:虫Ρ確
        "REPE. TODOS",//"REP ALL",            //40    T:盒確

#else//SDRAM_16Mb_Mode
        "REPETIR",//"REP",                //37    T:確
        "REPETIR DIRECT""\xd3""RIO",//"REP DIR",            //38    T:ヘ魁確

        "REPETIR 1",//"REP 1",              //39    T:虫Ρ確
        "REPETIR TODOS",//"REP ALL",            //40    T:盒確
#endif//SDRAM_16Mb_Mode
        "ANULAR REPETIR",//"REP CANCEL",         //41    T:確
        "MODE 2",             //42    T:家Α2

        //"8",                  //43    S:8保留
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
        #else// #ifdef HJ_APEX_FIX_SHOW_OSD
        "8 ADULT",            //43
        #endif// #ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",
        #endif
        "7 NC-17",            //44    S:x级

        "IR PARA",//"GOTO",               //45    T:穓
        "MUDO",//"MUTE",               //46    T:繰

#ifdef SDRAM_16Mb_Mode
        "MONO ESQ.",//"MONO L",             //47    T:オ羘笵
        "MONO DIR.",//"MONO R",             //48    T:羘笵
#else//SDRAM_16Mb_Mode        
        "MONO ESQUERDO",//"MONO L",             //47    T:オ羘笵
        "MONO DIREITO",//"MONO R",             //48    T:羘笵
#endif//SDRAM_16Mb_Mode

        "EST""\xc9""REO",//"STEREO",             //49    T:ミ砰羘
        "MUTE CANCEL",        //"SCORE MODE",         //50    T:(蝶だ家Α)
        "AO VIVO",//"LIVE",               //51    T:瞷初
#ifdef QSI_SETUP_MENU//liweihua 2004-6-16
        "KARAOK SETUP",                   //52
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "TEST TONE",          //52
#endif
        "MODE 3",             //53    T:家Α3
        OS_ICON_CDROM,        //54    //Jeff 200204113
        #ifdef OP_CUST_UI//libing 2005-5-11 11:39
        "JPEG TIME",             //"TIME"                //55    T:丁
        #else
        "",//"TIME",               //55    T:丁
        #endif
        #ifdef SHOW_MP4_INIT_STR  //wangwei-2004/4/28
        "INITIALIZING...",  //56
        #else
        "",//"9FRAME",             //56    T:礶
        #endif
        
        
        
        "ZOOM",               //57    T:糴
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                    //58    //not use
#endif
        OS_ICON_LANG,         //59
        "INTRO",              //60    T:苯磞
        "SRND",//"SURROUND",           //61    T:吏露
        "PBC",                //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "",//"PBC OFF",            //63    T:抖冀
#endif
        "",//"RAND CANCEL",        //64    T:繦诀冀
        "BASS MODE",          //65    T:家Α
        "",//"POWER ON",           //66(not use)
        "REPEAT A-",           //67    T:確A-
        "PC-VGA",               //"PC-VGA",           //68
        "REPETIR A-B",//"REPEAT A-B",         //69    T:確A-B
        "ANULAR A-B ",//"A-B CANCEL",         //70    T:確
        "ANULAR PROG",//"PRG CANCEL",         //71    T:絪祘
        "",                   //72
        "",//"ENGLISH",            //73    T:璣粂
        OS_ICON_VCD,          //74
        "",//"VCD 1.1",            //75
        #if defined(SHOW_VCD_VER_INFO)||defined(SYBER_DVD)  //yaowh add for kenloon 04-08-03
        OS_ICON_VCD20,        //76    //xulf 2003-11-17
        #else
        "",//"VCD 2.0",            //76
        #endif
        "CVBS",//OS_ICON_MP3,          //77(not use)
        OS_ICON_CDDA,         //78
        "48K", //"",//"BROWSE CANCEL",      //79    T:聅凝(not use)
        "96K", // "",//"INTRO CANCEL",       //80    T:苯磞(not use)
        "192K",//"",//"9FRAME CANCEL",      //81    T:礶(not use)
        "ZOOM PARA CIMA",//"ZOOM UP",            //82    T:礶簿
        "ZOOM PARA ABAIXO",//"ZOOM DOWN",          //83    T:礶簿
        "ZOOM PARA A ESQUERDA",//"ZOOM LEFT",          //84    T:礶オ簿
        "ZOOM PARA A DIRE",//"ZOOM RIGHT",         //85    T:礶簿
        "CA",//"CH"="CANAL",                 //86    T:彻竊
        "ECO",//"ECHO",               //87    T:睼臫
        "TT",//="T""\xcd""TULO"                 //88    T:夹肈
        "BAND",//"ECHO CANCEL",        //89    T:睼臫
        "VOL",                //90    T:秖
        "DOWN SAMPLE",  //"RESTAURAR",//"RESTORE",            //91    T:临(not use)
        "KEY",                //92    T:秸
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        "QUADRO 9_1",//"9FRAME_1",           //94    T:虫Ρ礶
        "AUTO ESQU""\xca""NCIAS",//"AUTO L",             //95    T:笆钡佰オ
        "AUTO DIREITA",//"AUTO R",             //96    T:笆钡佰
        "LOW",//"READING...",         //97    T:弄盒
        "LEITURA DE SEQU""\xca""NCIAS",//"SEQ PLAY",           //98    T:抖冀
        "MENU LEITURA",//"MENU PLAY",          //99    T:垫虫冀

        //"S-VIDEO",            //100(not use)
        //"NORMAL",             //101(not use)
        //"TIME",               //102   T:匡(not use)
        "LFE OUT",            //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else        
        "STANDARD",           //101
        "ENHANCE",            //102
#endif        
		 #ifdef OP_CUST_UI
        "DIVX ID",                      //103
        #else
        "MEDIUM",               //103
        #endif
        "LEITURA DE PROG",//"PRG PLAY",           //104   T:絪祘冀
        "HIGH",//"WAITING",            //105

#if defined(HJ_SVA_NEW_OSDSTR)
        "DYNAMIC RANGE",      //106   T:笆篈絛瞅
        OS_ICON_DVD,          //107
        "IDIOMA OSD",//"OSD LANGUAGE",       //108   T:礶陪ボ粂ē
#else //#if defined(HJ_SVA_NEW_OSDSTR)
        "DYNAMIC RANGE",      //106   T:笆篈絛瞅
        OS_ICON_DVD,          //107
        "IDIOMAS OSD",//"OSD LANGUAGE",       //108   T:礶陪ボ粂ē
#endif //#if defined(HJ_SVA_NEW_OSDSTR)

        OS_ICON_SUBT,         //109
        "TIPO DE TV",//"DISPLAY RATIO",      //110   T:辊礶ゑㄒ

#ifdef SDRAM_16Mb_Mode
        "SISTE. TV",//"TV TYPE",            //111   T:筿跌诀Α
        "SAIR DE INST.",//"SAIR DE INSTALA""\xc7""\xc3""O",//"EXIT SETUP",         //112   T:癶砞竚垫虫
#elif defined(HJ_SVA_NEW_OSDSTR)
        "SISTEMA DE CO",//"TV TYPE",            //111   T:筿跌诀Α
        "SAIR DA CONF.",//"SAIR DE INSTALA""\xc7""\xc3""O",//"EXIT SETUP",         //112   T:癶砞竚垫虫
#else//SDRAM_16Mb_Mode
    #ifdef MINTON_DVD   //heqiang, 2004-2-29 10:50 
        "MODO TV",      //111    "TV MODE"   S:(电视机制式)    
    #else
        "SISTEMA DE TV",//"TV TYPE",            //111   T:筿跌诀Α
    #endif//MINTON_DVD
        "SAIR DE INST.",//"SAIR DE INSTALA""\xc7""\xc3""O",//"EXIT SETUP",         //112   T:癶砞竚垫虫      
#endif//SDRAM_16Mb_Mode

#if defined(HJ_SVA_NEW_OSDSTR)
        "SAIDA AUDIO",//"AUD OUT",            //113   T:计絏块
        "VIDEO",//"VIDEO",              //114   T:跌繵块
        "SENHA",//"PASSWORD",           //115   T:盞絏
        "TIPO DE FILME",//"RATING",             //116   T:
#else //#if defined(HJ_SVA_NEW_OSDSTR)
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "SA""\xcd""DA ""\xc1""UDIO",//"AUD OUT",            //113   T:计絏块
#endif
        "V""\xcd""DEO",//"VIDEO",              //114   T:跌繵块
        "C""\xd3""DIGO",//"PASSWORD",           //115   T:盞絏
        "TIPO DE FILME",//"RATING",             //116   T:
#endif//#if defined(HJ_SVA_NEW_OSDSTR)

        "SPDIF/RAW",          //117   T:SPDIF/方絏

#if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
#else           
        "",//"AC3 5.1CH",          //118   T:AC3 5.1羘笵(not use)
#endif

        "SPDIF/PCM",          //119
//        "",//"AC3 2CH",            //120   T:AC3 2羘笵(not use)
#ifdef SUPPORT_PALM
        "PAL-M",                //120
#else
        "",           //120
#endif

#ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
#elif defined(EASTECH_DVI)
        "YCbCr", //121
#else
        "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
#endif//SHOW_YCbCr
        
        "AUTO",               //122   T:笆

#ifdef SDRAM_16Mb_Mode
        "DESLIG.",//"OFF",                //123   T:闽
#elif defined(HJ_SVA_NEW_OSDSTR)
        "DESATIVADO",//"OFF",                //123   T:闽
#else//SDRAM_16Mb_Mode
        "DESLIGADO",//"OFF",                //123   T:闽
#endif//SDRAM_16Mb_Mode
		#ifdef SHOW_DRM_REGISTRATION_CODE_IN_SETUP
        "DIVX[R] VOD", //124
        #else
        "",//"TM/CH/TL",           //124
        #endif

#ifdef HJ_SVA_NEW_OSDSTR
        "CAPITULO",//"CHAPTER",            //125   T:彻竊
        "TITULO",//"TITLE",              //126   T:夹肈
#else //HJ_SVA_NEW_OSDSTR
        "CAP""\xcd""TULO",//"CHAPTER",            //125   T:彻竊
        "T""\xcd""TULO",//"TITLE",              //126   T:夹肈
#endif//HJ_SVA_NEW_OSDSTR

        OS_ICON_ANGLE,        //127
      #if defined(HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif
        OS_16_9,              //129   T:16:9 --
        OS_4_3LB,             //130   T:4:3LB --
        OS_4_3PS,             //131
#ifdef HJ_SVA_NEW_OSDSTR
        "PAL-D",                //132
#else//HJ_SVA_NEW_OSDSTR
        "PAL",                //132
#endif//HJ_SVA_NEW_OSDSTR
        "NTSC",               //133
        "PAL60",              //134

#ifdef RATING_8
       "3 PG",                //135   T:level 3
        #ifdef FIX_RATING_8_DISPLAY
        "2 G",                  //136   T:(level 2)
        "1 KID SAFE",                //137   T:(level 1)
        #else
        "2",                  //136   T:level 2
        "1 G",                //137   T:level 1
        #endif
#else
        "N""\xc3""O ""ADULTO",//"NO ADULT",           //135   T:辅导级
        "SEGURO CRIAN",//"KID SAFE",           //136   T:保留
        "TIPO DE P""\xda""BL.",//"VIEW ALL",           //137   T:礚
#endif


#if defined(SHOW_5_1CH)
        "5.1CH",              //138   T:5.1羘笵
#else
        "6CH SETUP",          //138   T:6羘笵砞竚
#endif

        "SUBWOOFER",          //139   T:禬
#ifdef HJ_SVA_NEW_OSDSTR
        "SATURACAO",         //140   SATURATION
        "ATIVADO",                 //141   T:秨
#else//#ifdef HJ_SVA_NEW_OSDSTR
        "SATURATION",         //140   SATURATION
        "ON",                 //141   T:秨
#endif//#ifdef HJ_SVA_NEW_OSDSTR        

        OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
        "APAGAR",//"CLEAR",              //145   T:睲埃
        "  T  C",               //146
        "--:--",              //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "EDIT",               //149   T:絪胯
        
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42,(Portuguese).     
        "L""\xcd""NG DA LG 2",  //150
#else 
        "",//OS_DIR1,              //150
#endif

#ifdef QSI_SETUP_MENU//liweihua 2004-6-15
        " 1 MIN",                   //151
        " 5 MIN",                   //152
        "10 MIN",                   //153
        "30 MIN",                   //154
#elif defined(ADJUST_JPEG_SLIDE_TIME)  ////lyc 2005/2/18
        "15 SEC",                   //151
        "30 SEC",                   //152
        "45 SEC",                   //153
        "50 SEC",                   //154        
#else
        "",//OS_DIR2,              //151
        OS_DIR3,              //152
        OS_DIR4,              //153
        "PAL-NC",//OS_DIR5,              //154
#endif
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
#ifdef HJ_SVA_NEW_OSDSTR
        "MATIZ",                //157   HUE
#else//#ifdef HJ_SVA_NEW_OSDSTR
        "HUE",                //157   HUE
#endif//#ifdef HJ_SVA_NEW_OSDSTR        
        "PROLOGIC",//"-:--:--",            //158
        "MOVIE MODE",//"TRACK SEARCH",       //159   T:虫Ρ穓
        "MUSIC MODE",//"DISC SEARCH",        //160   T:羆盒穓
        
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//"TT:CH",              //161
        #endif

#ifdef REMAIN_TIME//nono 2-7-12 20:06
        "T",                  //162
#else
        "",//"BOOKMARK",           //162
#endif

        OS_DIR0,              //163
#ifdef HJ_SVA_NEW_OSDSTR
        "CONTRASTE",           //164   CONTRAST
#else//#ifdef HJ_SVA_NEW_OSDSTR
        "CONTRAST",           //164   CONTRAST
#endif//#ifdef HJ_SVA_NEW_OSDSTR        
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
        "CANAL",//"CHANNEL",            //168   T:羘笵
#ifdef HJ_SVA_NEW_OSDSTR
        "BRILHO",         //169   BRIGHTNESS
#else //#ifdef HJ_SVA_NEW_OSDSTR
        "BRIGHTNESS",         //169   BRIGHTNESS
#endif//#ifdef HJ_SVA_NEW_OSDSTR      
        "F/W ID",             //170   T:硁ン絪絏
#ifdef OP_CUST_UI  
		"CHECKSUM",  
#else		    
        "CHIP ID",            //171   T:(絪絏)        S:(芯片编码)
#endif
        "REGI""\xc3""O",//"REGION",             //172   T:跋絏
        "MEMORY",//"FUN""\xc7""\xc3""O",//"FUNCTION",           //173   T:滦弄滦佰
        "DYNAMIC",//"MODO",//"MODE",               //174   T:家Α

        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

//        "",//"GRAVAR",//"RECORD",             //175   T:滦佰
//        "",//"ESTUDAR",//"STUDY",              //176   T:滦弄
//        "",//"SEGUINTE",//"FOLLOW",             //177   T:蛤弄

        "MIC1 VOL",//"COMPARAR",//"COMPARE",            //178   T:癸ゑ
        "MIC2 VOL",//"CONTADOR",//"COUNTER",            //179   T:滦Ω计
//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP         //181
#elif defined(SUPPORT_FUNCTION_MENU) 
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181
#else
        "",//"N""\xcd""VEL",//"LEVEL",              //180   T:魁家Α
        "",//"ALTO",//"HIGH",               //181   T:蔼珇借
#endif
#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",             //182   T:禬丁
#endif
        "",//"SUPER",              //183   T:禬蔼珇借
        "",//"OPERATING",          //184   T:秸竊よΑ
        "",//"MANUAL",             //185   T:も笆
        OS_DIR10,             //186
        OS_DIR11,             //187
        "CONCERTO",//"CONCERT",            //188   T:贾芔
        "IGREJA",//"CHURCH",             //189   T:毙绑
        "PASSIVO",//"PASSIVE",            //190   T:吏露
        "AMPLO",//"WIDE",               //191   T:糴初
//        "",//"ANFITEATRO",//"AMPHITH",            //192   T:蛾粿初
//        "",//"EST""\xc1""DIO",//"STADIUM",            //193   T:蔨▅繻
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192    3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "EQ",                 //194   T:А颗
        "STANDARD",           //195   T:夹非
        "CL""\xc1""SSICO",//"CLASSIC",            //196   T:ㄥ
        "ROCK",               //197   T:穘簎
        "JAZZ",               //198   T:里
        "POP",                //199   T:瑈︽
        "USER",               //200   T:┦
        "ATTRIB",             //201   T:┦
        "AVAN""\xc7""AR LENTO",//"SF",                 //202   T:篊秈
        "RECUAR LENTO",//"SB",                 //203   T:篊癶

#ifdef ECHOTEST//nono 2-7-13 11:31
        "ECHO DECAY",         //204   T:睼臫瞏      //Jeff 20020506
#else
        "C",                 //204   //show "C"
#endif

        "COLUNA CENT.",//"CENTER",             //205   T:い竚喘羘竟
        "COLUNA TRAS.",//"REAR",               //206   T:吏露喘羘竟

        #ifndef HIMAGE_RGB
        "TV-RGB",              //207
        #else
        "RGB",                    //207
        #endif


        "4 PG13",             //208   T:辅导级

        "DACOLUNA CEN.",//"CENTER DELAY",       //209   T:い竚┑筐
        "DACOLUNA TRA.",//"REAR DELAY",         //210   T:吏露┑筐
        "COLUNA FRONT",//"FRONT",              //211   T:玡竚喘羘竟

#if defined(HJ_SVA_NEW_OSDSTR)
        "CONFIGURACAO DE VIDEO",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS

        "CONFIGURACAO DE SISTEMA",//"SYSTEM SETUP",       //214   T:╰参砞竚
        "CONFIGURACAO DE SOM",//"SPEAKER SETUP",      //215   T:喘羘竟砞竚
        "CONFIGURACAO DE AUDIO",//"AUDIO SETUP",        //216   T:繵砞竚
        "CONF. FABRICA",//"DEFAULT",            //217   T:
#else//#if defined(HJ_SVA_NEW_OSDSTR)
        "VIDEO SETUP",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS

        "INSTALA""\xc7""\xc3""O DE SISTEMA",//"SYSTEM SETUP",       //214   T:╰参砞竚
        "INSTALA""\xc7""\xc3""O DE COLUNAS",//"SPEAKER SETUP",      //215   T:喘羘竟砞竚
        "INSTALA""\xc7""\xc3""O DE ""\xc1""UDIO",//"AUDIO SETUP",        //216   T:繵砞竚
        "POR DEFEITO",//"DEFAULT",            //217   T:
#endif//#if defined(HJ_SVA_NEW_OSDSTR)
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "OUT CHANNEL",        //218   T:羘笵北(not use)
        #endif

#if defined(HJ_SVA_NEW_OSDSTR)
        "PROT. DE TELA",//"SCREEN SAVER",       //219   T:辊玂臔
#else//#elif defined(HJ_SVA_NEW_OSDSTR)
        #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU
        "   MNP   ",
        #else
        "PROTECT ECR""\xc3",//"SCREEN SAVER",       //219   T:辊玂臔
        #endif
#endif//#elif defined(HJ_SVA_NEW_OSDSTR)
		#ifdef ORITRON_PASSWORD//libing 2005-4-29 9:53
        "SET DUFAULT VALUE",
        "CLEAR PASSWORD",             //221   T:(辅导级)
        "LOADER LOCKED",
        #else
        "TIPO 1",//"TYPE 1",             //220   T:家Α 1
        "TYPO 2",//"TYPE 2",             //221   T:家Α 2
        "TYPO 3",//"TYPE 3",             //222   T:家Α 3
		#endif
        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   S:5保留
        #endif
        
        "6 R",                //224   S:限制级

        "ERRO DE DISCO",//"ERR DISC",           //225   S:错误碟片
#ifdef HJ_SVA_NEW_OSDSTR
        "CONFIGURACAO DIGITAL",//"DIGITAL SETUP",      //226   T:计絏砞竚
#else//#ifdef HJ_SVA_NEW_OSDSTR
        "INSTALA""\xc7""\xc3""O DIGITAL",//"DIGITAL SETUP",      //226   T:计絏砞竚
#endif//#ifdef HJ_SVA_NEW_OSDSTR
#ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
#else
        "INSTAL MICRO",//"MIC SETUP",          //227   T:杠旦砞竚
        "VOL MICRO",//"MIC VOL",            //228   T:杠旦秖
#endif
        "",//"CD RECOVERING",      //229   T:岿い     ------------- not use
        "SMART UPGRADE",      //230   T:醇ど
        "UPGRADE TO V ",      //231   T:どΘ
        "UPGRADING",          //232   T:どい
        "N""\xc3""O DESLIGAR",//"NOT POWER OFF",      //233   T:づ闽诀
        "REGI""\xc3""O 0",//"REGION 0",           //234   T:0 跋
        "REGI""\xc3""O 1",//"REGION 1",           //235   T:1 跋
        "REGI""\xc3""O 2",//"REGION 2",           //236   T:2 跋
        "REGI""\xc3""O 3",//"REGION 3",           //237   T:3 跋
        "REGI""\xc3""O 4",//"REGION 4",           //238   T:4 跋
#ifdef HJ_SVA_NEW_OSDSTR
        "CONFIGURACAO DE IDIOMA",//"LANG SETUP",         //239   T:粂ē砞竚
#else
        "INSTALA""\xc7""\xc3""O DA L""\xcd""NGUA",//"LANG SETUP",         //239   T:粂ē砞竚
#endif
        #ifdef SUPPORT_FUNCTION_MENU
	"DISPLAY",		   //240
	#else 
        "",//"SRND SETUP",         //240   T:吏露砞竚(not use)
        #endif
        "PAG.PRINCIPAL",//"MAIN PAGE",          //241   T:

#ifdef HJ_SVA_NEW_OSDSTR
        "IDIO. DE AUD.",//"AUDIO LANG",         //242   T:繵粂ē
        "IDIO. DO SUBT",//"SUBTITLE LANG",      //243   T:辊粂ē
        "IDIO. DO MENU",//"MENU LANG",          //244   T:垫虫粂ē
#else//HJ_SVA_NEW_OSDSTR
        "L""\xcd""NG DA LEGEN",//"SUBTITLE LANG",      //243   T:辊粂ē
        "L""\xcd""NG DO MENU",//"MENU LANG",          //244   T:垫虫粂ē
        "L""\xcd""NG DO ""\xc1""UDIO",//"AUDIO LANG",         //242   T:繵粂ē
#endif//HJ_SVA_NEW_OSDSTR

#ifdef HJ_SVA_NEW_OSDSTR
        "MODO MIX",            //245   T:睼家Α
#else//HJ_SVA_NEW_OSDSTR
        "MODO MISTO",//"DOWNMIX",            //245   T:睼家Α
#endif
        "RESTAURAR",//"RESTORE",            //246   T:確
        "LT/RT",              //247
        "VSS",                //248   T:店览吏露羘
        "MODO OP",//"OP MODE",            //249   T:块家Α
        "FICHA SA""\xcd""DA",//"LINE OUT",           //250   T:絬隔块
        "RF REMOD",           //251   T:RF 秸俱
        "DUAL MONO",          //252   T:オ+
#ifdef HJ_SVA_NEW_OSDSTR
        "MONO MIXADO",//"MIX MONO",           //253   T:睼羘笵
#else
        "MIXED MONO",//"MIX MONO",           //253   T:睼羘笵
#endif

        "MODO SURND",//"SURND MODE",         //254   T:吏露家Α
#ifdef KSD_DVD
        "PRESS PLAY BUTTON TO CONTINUE",        //255   T:              S:请按播放键继续
#else
        "PRE STOP",           //255   T:              S:准停止
#endif
//=================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER 
},
#endif
#ifdef USE_LATIN_OSD
//Latin
{
        "",                   //0
        "NO DISC",            //1     T:礚盒
        "INVALID ENTRY",      //2     T:眤岿 hand
        "TRK",                //3     T:Ρヘ
        OS_ICON_SVCD,         //4
        "DE-INTERLACE",            //5     T:簙粂
        "OPEN",               //6     T:
        "CLOSE",              //7     T:闽
        "PLAY",               //8     T:冀
        "REGION 5",           //9     T:5 跋
        "PAUSE",              //10    T:既氨
        "RANDOM",             //11    T:繦诀冀
        "RESUME",             //12    T:確冀
        "STOP",               //13    T:氨ゎ
        "STEP",               //14    T:˙秈
        "SELECT",             //15    T:匡拒
        "READ",               //16    T:弄盒
        "REGION 6",           //17    T:6 跋
        "ANALOG",             //18    T:家览
        "FORWARD",            //19    T:е秈
        "BACKWARD",           //20    T:е癶
        "NEXT",               //21    T:Ρ >>

        //"NEXTPAGE",           //22    T:
        "SERVO DEBUG",                   //22

        "PREV",               //23    T:Ρ <<

        //"PREVPAGE",           //24    T:
        "DIR",                   //24

        "RETURN",             //25    T:垫虫
        Ch_repx,              //26
        Ch_rep1,              //27
        Ch_repd,              //28
        //"NONE",               //29    T:礚
        "OFF",               //29    T:礚
        "MENU",               //30    T:匡虫
        "SCORE",              //31    T:だ计
        "MARK",               //32    T:癘拘  //Jeff 20020411
        "BROWSE",             //33    T:聅凝
        "PROG",               //34    T:絪祘
        "SAVING LOGO...",     //35    T:篊
        "MODE 1",             //36    T:家Α1
        "REP",                //37    T:確
        "REP DIR",            //38    T:ヘ魁確
        "REP 1",              //39    T:虫Ρ確
        "REP ALL",            //40    T:盒確
        "REP CANCEL",         //41    T:確
        "MODE 2",             //42    T:家Α2

        //"8",                  //43    S:8保留
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
        #else// #ifdef HJ_APEX_FIX_SHOW_OSD
        "8 ADULT",            //43
        #endif// #ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",
        #endif
        "7 NC-17",            //44    S:x级

        "GOTO",               //45    T:穓
        "MUTE",               //46    T:繰
        "MONO L",             //47    T:オ羘笵
        "MONO R",             //48    T:羘笵
        "STEREO",             //49    T:ミ砰羘
        "MUTE CANCEL",               //50    T:糴初
        "LIVE",               //51    T:瞷初
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "THEATRE",            //52    T:粿初(not use)
#endif
        "MODE 3",             //53    T:家Α3
        OS_ICON_CDROM,        //54    //Jeff 200204113
        "TIME",               //55    T:丁
        "9FRAME",             //56    T:礶
        "ZOOM",               //57    T:糴
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                    //58    //not use
#endif
        OS_ICON_LANG,         //59
        "INTRO",              //60    T:苯磞
        "SRND",//"SURROUND",           //61    T:吏露
        "PBC",                //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "PBC OFF",            //63    T:抖冀
#endif
        "RAND CANCEL",        //64    T:繦诀冀
        "BASS MODE",          //65    T:家Α
        "POWER ON",           //66(not use)
        "REPEAT A-",           //67    T:確A-
        "PC-VGA",               //"PC-VGA",           //68
        "REPEAT A-B",          //69    T:確A-B
        "A-B CANCEL",          //70    T:確
        "PRG CANCEL",         //71    T:絪祘
        "",                   //72
        "ENGLISH",            //73    T:璣粂
        OS_ICON_VCD,          //74
        "VCD 1.1",            //75
        "VCD 2.0",            //76
        "CVBS",//OS_ICON_MP3,          //77(not use)
        OS_ICON_CDDA,         //78
        "48K", //"BROWSE CANCEL",      //79    T:聅凝(not use)
        "96K", //"INTRO CANCEL",       //80    T:苯磞(not use)
        "192K", //"9FRAME CANCEL",      //81    T:礶(not use)
        "ZOOM UP",            //82    T:礶簿
        "ZOOM DOWN",          //83    T:礶簿
        "ZOOM LEFT",          //84    T:礶オ簿
        "ZOOM RIGHT",         //85    T:礶簿
        "CH",                 //86    T:彻竊
        "ECHO",               //87    T:睼臫
        "TT",                 //88    T:夹肈
        "BAND",//"ECHO CANCEL",        //89    T:睼臫
        "VOL",                //90    T:秖
        "DOWN SAMPLE",  //"RESTORE",            //91    T:临(not use)
        "KEY",                //92    T:秸
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        "9FRAME_1",           //94    T:虫Ρ礶
        "AUTO L",             //95    T:笆钡佰オ
        "AUTO R",             //96    T:笆钡佰
        "LOW",//"READING...",         //97    T:弄盒
        "SEQ PLAY",           //98    T:抖冀
        "MENU PLAY",          //99    T:垫虫冀

        //"S-VIDEO",            //100(not use)
        //"NORMAL",             //101(not use)
        //"TIME",               //102   T:匡(not use)
        "LFE OUT",            //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else        
        "STANDARD",           //101
        "ENHANCE",            //102
#endif

        "MEDIUM",               //103
        "PRG PLAY",           //104   T:絪祘冀
        "HIGH",//"WAITING",            //105   T:
        "DYNAMIC RANGE",      //106   T:笆篈絛瞅
        OS_ICON_DVD,          //107
        "OSD LANGUAGE",       //108   T:礶陪ボ粂ē
        OS_ICON_SUBT,         //109
        "DISPLAY RATIO",      //110   T:辊礶ゑㄒ
        "TV TYPE",            //111   T:筿跌诀Α
        "EXIT SETUP",         //112   T:癶砞竚垫虫
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "AUD OUT",            //113   T:计絏块
#endif
        "VIDEO",              //114   T:跌繵块
        "PASSWORD",           //115   T:盞絏
#ifdef GBM_RATING_SHOW_PARENTAL//GBM_FULL_FUNCTION      //gerry,2004-2-4 9:02
        "PARENTAL",//"RATING",             //116   T:
#else//GBM_RATING_SHOW_PARENTAL
        "RATING",             //116   T:
#endif//GBM_RATING_SHOW_PARENTAL
        "SPDIF/RAW",          //117   T:SPDIF/方絏

#if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
#else
        "AC3 6CH",            //118   T:AC3 6羘笵
#endif

        "SPDIF/PCM",          //119
//        "AC3 2CH",            //120   T:AC3 2羘笵(not use)
#ifdef SUPPORT_PALM
        "PAL-M",                //120
#else
        "",           //120
#endif
        #ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
        #elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
#elif defined(EASTECH_DVI)
        "YCbCr", //121        
#else
        "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
#endif//SHOW_YCbCr
        
        "AUTO",               //122   T:笆
        "OFF",                //123   T:闽
        "TM/CH/TL",           //124
        "CHAPTER",            //125   T:彻竊
        "TITLE",              //126   T:夹肈
        OS_ICON_ANGLE,        //127
      #if defined(HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif
        OS_16_9,              //129   T:16:9 --
        OS_4_3LB,             //130   T:4:3LB --
        OS_4_3PS,             //131
        "PAL",                //132
        "NTSC",               //133
        "PAL60",              //134

#ifdef RATING_8
       "3 PG",                //135   T:level 3
        #ifdef FIX_RATING_8_DISPLAY
        "2 G",                  //136   T:(level 2)
        "1 KID SAFE",                //137   T:(level 1)
        #else
        "2",                  //136   T:level 2
        "1 G",                //137   T:level 1
        #endif
#else
        "NO ADULT",           //135   T:辅导级
        "KID SAFE",           //136   T:保留
        "VIEW ALL",           //137   T:礚
#endif


#if defined(SHOW_5_1CH)
        "5.1CH",              //138   T:5.1羘笵
#else
        "6CH SETUP",          //138   T:6羘笵砞竚
#endif

        "SUBWOOFER",          //139   T:禬
        "SATURATION",         //140   SATURATION
        "ON",                 //141   T:秨
        OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
        "CLEAR",              //145   T:睲埃
        "  T  C",               //146
        "--:--",              //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "EDIT",               //149   T:絪胯
        
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42,(Latin).
        "SUBTITLE 2",         //150
#else
        "",//OS_DIR1,              //150
#endif     
        
        "",//OS_DIR2,              //151
        OS_DIR3,              //152
        OS_DIR4,              //153
        "PAL-NC",//OS_DIR5,              //154
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
        "HUE",                //157   HUE
        "PROLOGIC",            //158
        "MOVIE MODE",//"TRACK SEARCH",       //159   T:虫Ρ穓
        "MUSIC MODE",//"DISC SEARCH",        //160   T:羆盒穓
        
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
#else
        "",              //161
#endif

#ifdef REMAIN_TIME//nono 2-7-12 20:06
        "T",                  //162
#else
        "BOOKMARK",           //162
#endif

        OS_DIR0,              //163
        "CONTRAST",           //164   CONTRAST
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
        "CHANNEL",            //168   T:羘笵
        "BRIGHTNESS",         //169   BRIGHTNESS
        "F/W ID",             //170   T:硁ン絪絏
        "CHIP ID",            //171   T:絪絏
        "REGION",             //172   T:跋絏
        "MEMORY",           //173   T:滦弄滦佰
        "DYNAMIC",               //174   T:家Α

        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

//        "RECORD",             //175   T:滦佰
//        "STUDY",              //176   T:滦弄
//        "FOLLOW",             //177   T:蛤弄
        "MIC1 VOL",            //178   T:癸ゑ
        "MIC2 VOL",            //179   T:滦Ω计
//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU) 
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181
#else
        "LEVEL",              //180   T:魁家Α
        "HIGH",               //181   T:蔼珇借
#endif
#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",             //182   T:禬丁
#endif
        "SUPER",              //183   T:禬蔼珇借
        "OPERATING",          //184   T:秸竊よΑ
        "MANUAL",             //185   T:も笆
        OS_DIR10,             //186
        OS_DIR11,             //187
        "CONCERT",            //188   T:贾芔
        "CHURCH",             //189   T:毙绑
        "PASSIVE",            //190   T:吏露
        "WIDE",               //191   T:糴初
//        "AMPHITH",            //192   T:蛾粿初
//        "STADIUM",            //193   T:蔨▅繻
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192   3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "EQ",                 //194   T:А颗
        "STANDARD",           //195   T:夹非
        "CLASSIC",            //196   T:ㄥ
        "ROCK",               //197   T:穘簎
        "JAZZ",               //198   T:里
        "POP",                //199   T:瑈︽
        "USER",               //200   T:┦
        "ATTRIB",             //201   T:┦
        "SF",                 //202   T:篊秈
        "SB",                 //203   T:篊癶

#ifdef ECHOTEST//nono 2-7-13 11:31
        "ECHO DECAY",         //204   T:睼臫瞏      //Jeff 20020506
#else
         "C",                 //204   //show "C"
#endif

        "CENTER",             //205   T:い竚喘羘竟
        "REAR",               //206   T:吏露喘羘竟
        "TV-RGB",              //207

        "4 PG13",             //208   S:辅导级

        "CENTER DELAY",       //209   T:い竚┑筐
        "REAR DELAY",         //210   T:吏露┑筐
        "FRONT",              //211   T:玡竚喘羘竟
        "VIDEO SETUP",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS
        "SYSTEM SETUP",       //214   T:╰参砞竚
        "SPEAKER SETUP",      //215   T:喘羘竟砞竚
        "AUDIO SETUP",        //216   T:繵砞竚
        "DEFAULT",            //217   T:
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "OUT CHANNEL",        //218   T:羘笵北(not use)
        #endif
        
        #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU
        "   MNP   ",
        #else
        "SCREEN SAVER",       //219   T:辊玂臔
        #endif
        "TYPE 1",             //220   T:家Α 1
        "TYPE 2",             //221   T:家Α 2
        "TYPE 3",             //222   T:家Α 3

        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   S:5保留
        #endif
        
        "6 R",                //224   S:限制级

        "ERR DISC",           //225   S:错误碟片
        "DIGITAL SETUP",      //226   T:计絏砞竚
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "MIC SETUP",          //227   T:杠旦砞竚
        "MIC VOL",            //228   T:杠旦秖
        #endif
        "CD RECOVERING",      //229   T:岿い     ------------- not use
        "SMART UPGRADE",      //230   T:醇ど
        "UPGRADE TO V ",      //231   T:どΘ
        "UPGRADING",          //232   T:どい
        "NOT POWER OFF",      //233   T:づ闽诀
        "REGION 0",           //234   T:0 跋
        "REGION 1",           //235   T:1 跋
        "REGION 2",           //236   T:2 跋
        "REGION 3",           //237   T:3 跋
        "REGION 4",           //238   T:4 跋
        "LANG SETUP",         //239   T:粂ē砞竚
        #ifdef SUPPORT_FUNCTION_MENU
	"DISPLAY",	      //240	
	#else 
        "SRND SETUP",         //240   T:吏露砞竚(not use)
        #endif
        "MAIN PAGE",          //241   T:
#ifndef BBK_DVD
        "AUDIO LANG",         //242   T:繵粂ē
#else
        "AUDIO",         //242   T:繵粂ē axel 2004/1/27 03:58 eliminate "LANG"
#endif
#ifdef DISC_INFO_KEY  //fengjl  3-11-25 9:55
        /*"SUBP LANG",      //243   T:辊粂ē*/
        "SUBP",      //243   T:辊粂ē  axel 2004/1/27 03:58 eliminate "LANG"
#elif !defined(BBK_DVD)
        "SUBTITLE LANG",      //243   T:辊粂ē
#else
        "SUBTITLE",      //243   T:辊粂ē axel 2004/1/27 03:58 eliminate "LANG"       
#endif
        "MENU LANG",          //244   T:垫虫粂ē
        "DOWNMIX",            //245   T:睼家Α
        "RESTORE",            //246   T:確
        "LT/RT",              //247
        "VSS",                //248   T:店览吏露羘
        "OP MODE",            //249   T:块家Α
        "LINE OUT",           //250   T:絬隔块
        "RF REMOD",           //251   T:RF 秸俱
        "DUAL MONO",          //252   T:オ+
        "MIX MONO",           //253   T:睼羘笵
        "SURND MODE",         //254   T:吏露家Α
#ifdef KSD_DVD
        "PRESS PLAY BUTTON TO CONTINUE",        //255   T:              S:请按播放键继续
#else
        "PRE STOP",           //255   T:              S:准停止
#endif
//=================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER
},
#endif

#ifdef USE_ITALIAN_OSD
//Italian
{
        "",                                 //0
        "NON C'""\xc8"" DISCO", //"NO DISC",            //1     T:礚盒
        "ENTRATA INVALIDA", //"INVALID ENTRY",      //2     T:眤岿 hand
        "TRK",          //"TRK",                //3     T:Ρヘ
        OS_ICON_SVCD,                       //4
        "DE-INTERLACE",//"CINESE",      //"CHINESE",            //5     T:簙粂
        "APERTO",       //"OPEN",               //6     T:
        "CHIUSO",       //"CLOSE",              //7     T:闽
        "RIPRO.",           //"PLAY"="RIPRODUZIONE",//8     T:冀
        "REGIONE 5",        //"REGION 5",           //9     T:5 跋
        "PAUSA",        //"PAUSE",              //10    T:既氨
        "ALEATORIA",        //"RANDOM",             //11    T:繦诀冀
        "RIPRESA",      //"RESUME",             //12    T:確冀
        "FERMA",        //"STOP",               //13    T:氨ゎ
        "PASO",         //"STEP",               //14    T:˙秈
        "SELEZIONARE",      //"SELECT",             //15    T:匡拒
        "LEGGERE",      //"READ",               //16    T:弄盒
        "REGIONE 6",        //"REGION 6",           //17    T:6 跋
        "ANALOGO",      //"ANALOG",             //18    T:家览
        "AVANTI",       //"FORWARD",            //19    T:е秈
        "INDIETRO",     //"BACKWARD",           //20    T:е癶
        "SEGUENTE",     //"NEXT",               //21    T:Ρ >>

        //"NEXTPAGE",           //22    T:
        "SERVO DEBUG",                   //22

        "PRECEDENTE",       //"PREV",               //23    T:Ρ <<

        //"PREVPAGE",           //24    T:
        "DIR",                   //24

        "RITORNARE",        //"RETURN",             //25    T:垫虫
        Ch_repx,                            //26
        Ch_rep1,                            //27
        Ch_repd,                            //28
        //"NONE",               //29    T:礚
        "INA",              //"INA.=INATTIVO"//"OFF"="CHIUSO",       //29    T:礚
        "MENU",                             //30    T:匡虫
        "PUNTO",        //"SCORE",              //31    T:だ计
        "MEMO",         //"MARK"="MEMORIA",     //32    T:癘拘  //Jeff 20020411
        "NAVIGARE",     //"BROWSE",             //33    T:聅凝
        "PROG",                             //34    T:絪祘
        "SAVING LOGO...",                   //35    T:篊
        "MODE 1",                           //36    T:家Α1
#ifdef SDRAM_16Mb_Mode
        "RIP.",     //"REP",                //37    T:確
        "RIP. DIR",     //"REP DIR",            //38    T:ヘ魁確
        "RIP. 1",       //"REP 1",              //39    T:虫Ρ確
        "RIP. TUTTO",   //"REP ALL",            //40    T:盒確

#else//SDRAM_16Mb_Mode
        "RIPETERE",     //"REP",                //37    T:確
        "RIPETERE DIR",     //"REP DIR",            //38    T:ヘ魁確
        "RIPETERE 1",       //"REP 1",              //39    T:虫Ρ確
        "RIPETERE TUTTO",   //"REP ALL",            //40    T:盒確
#endif//"RIPETERE",     //"REP",                //37    T:確
        "CANCELLARE RIP.",  //"REP CANCEL",         //41    T:確
        "MODE 2",                           //42    T:家Α2

        //"8",                                  //43    S:8保留
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
        #else// #ifdef HJ_APEX_FIX_SHOW_OSD
        "8 ADULT",            //43
        #endif// #ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",
        #endif
        "7 NC-17",                          //44    S:x级

        "VA A",         //"GOTO",               //45    T:穓
        "MUTO",         //"MUTE",               //46    T:繰

#ifdef SDRAM_16Mb_Mode
        "MONO SIN.",    //"MONO L",             //47    T:オ羘笵
        "MONO DES.",        //"MONO R",             //48    T:羘笵
#else//SDRAM_16Mb_Mode        
        "MONO SINISTRO",    //"MONO L",             //47    T:オ羘笵
        "MONO DESTRO",      //"MONO R",             //48    T:羘笵
#endif//SDRAM_16Mb_Mode

        "STEREO",                           //49    T:ミ砰羘
        "MUTE CANCEL",      //"HALL",               //50    T:糴初
        "DAL VIVO",     //"LIVE",               //51    T:瞷初
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "TEATRO",       //"THEATRE",            //52    T:粿初(not use)
#endif
        "MODE 3",                           //53    T:家Α3
        OS_ICON_CDROM,                      //54    //Jeff 200204113
        #ifdef OP_CUST_UI//libing 2005-5-11 11:39
        "JPEG TIME",             //"TIME"                //55    T:丁
        #else
        "TEMPO",       //"TIME",               //55    T:丁
        #endif
        "",//"9 QUADRI",        //"9FRAME",             //56    T:礶
        "ZOOM",                             //57    T:糴
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                    //58    //not use
#endif
        OS_ICON_LANG,                       //59
        "SCANSIONE",        //"INTRO",              //60    T:苯磞
        "SRND",         //"SURROUND",           //61    T:吏露
        "PBC",                              //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "",//"PBC IN ORDINE",   //"PBC OFF",            //63    T:抖冀
#endif
        "CANCALARE ALEATORIA",  //"RAND CANCEL",        //64    T:繦诀冀
        "BASS MODE",                        //65    T:家Α
        "",//"POWER ON",                                //66(not use)
        "RIPETERE A-",      //"REPEAT A-",           //67    T:確A-
        "PC-VGA",               //"PC-VGA",           //68
        "RIPETERE A-B",     //"REPEAT A-B",          //69    T:確A-B
        "CANCALARE A-B",        //"A-B CANCEL",          //70    T:確
        "CANCALARE PRG",    //"PRG CANCEL",         //71    T:絪祘
        "",                                 //72
        "",//"INGLESE",     //"ENGLISH",            //73    T:璣粂
        OS_ICON_VCD,                        //74
        "",//"VCD 1.1",                         //75
        "",//"VCD 2.0",                         //76
        "CVBS",//OS_ICON_MP3,                       //77(not use)
        OS_ICON_CDDA,                       //78
        "48K", //"",//"CANCALARE NAV.", //"BROWSE CANCEL",      //79    T:聅凝(not use)
        "96K", //"",//"CANCALARE SCANSIONE",    //"INTRO CANCEL",       //80    T:苯磞(not use)
        "192K", //"",//"CANCALARE 9 QUADRI",    //"9FRAME CANCEL",      //81    T:礶(not use)
        "ZOOM SU",      //"ZOOM UP",            //82    T:礶簿
        "ZOOM GI\xd9",      //"ZOOM DOWN",          //83    T:礶簿
        "ZOOM A SINISTRA",  //"ZOOM LEFT",          //84    T:礶オ簿
        "ZOOM A DESTRA",    //"ZOOM RIGHT",         //85    T:礶簿
        "CH",               //"CH"="CAPITOLO",      //86    T:彻竊
        "ECO",          //"ECHO",               //87    T:睼臫
        "TT",           //"TT"="TITOLO",        //88    T:夹肈
        "BAND",//"CANCALARE ECO",   //"ECHO CANCEL",        //89    T:睼臫
        "VOL",          //"VOL"="VOLUME",                //90    T:秖
        "DOWN SAMPLE",  //"RIPRENDERE",     //"RESTORE",            //91    T:临(not use)
        "TONO",         //"KEY",                //92    T:秸
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        "9 QUADRI_1",       //"9FRAME_1",           //94    T:虫Ρ礶
        "AUTO SINI.",       //"AUTO L",             //95    T:笆钡佰オ
        "AUTO DEST.",       //"AUTO R",             //96    T:笆钡佰
        "LOW",//"LEGGENDO",     //"READING...",         //97    T:弄盒
        "RIPRODUZIONE SEQ", //"SEQ PLAY",           //98    T:抖冀
        "RIPRODUZIONE MENU",    //"MENU PLAY",          //99    T:垫虫冀

        //"S-VIDEO",            //100(not use)
        //"NORMAL",             //101(not use)
        //"TIME",               //102   T:匡(not use)
        "LFE OUT",            //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else        
        "STANDARD",           //101
        "ENHANCE",            //102
#endif
		 #ifdef OP_CUST_UI
        "DIVX ID",                      //103
        #else
        "MEDIUM",           //"STEP",               //103
        #endif
        "RIPRODUZIONE PRG.",    //"PRG PLAY",           //104   T:絪祘冀
        "HIGH",//"ASPETTA",     //"WAITING",            //105
        "GAMMA DINAMIC",    //"DYNAMIC RANGE"="GAMMA DINAMICA",      //106   T:笆篈絛瞅
        OS_ICON_DVD,                        //107
        "LINGUA OSD",       //"OSD LANGUAGE",       //108   T:礶陪ボ粂ē
        OS_ICON_SUBT,                       //109
        "TASSO VISUAL",     //"DISPLAY RATIO",      //110   T:辊礶ゑㄒ
        "SYSTEMA TV",       //"TV TYPE",            //111   T:筿跌诀Α
        "USCIRE SETUP",     //"EXIT SETUP",         //112   T:癶砞竚垫虫
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "USCITA DIGIT.",    //"AUD OUT",            //113   T:计絏块
#endif
        "USCITA VIDEO",     //"VIDEO",              //114   T:跌繵块
        "PASSWORD",                         //115   T:盞絏
        "RAPPORTO",     //"RATING",             //116   T:
        "SPDIF/RAW",                        //117   T:SPDIF/方絏
#if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
#else
        "",//"AC3 6CA",     //"AC3 6CH",            //118   T:AC3 6羘笵
#endif

        "SPDIF/PCM",                        //119
//        "",//"AC3 2CA",       //"AC3 2CH",            //120   T:AC3 2羘笵(not use)
#ifdef SUPPORT_PALM
        "PAL-M",                //120
#else
        "",           //120
#endif
        #ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
        #elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
#elif defined(EASTECH_DVI)
        "YCbCr", //121
#else
        "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
#endif//SHOW_YCbCr
        
        "AUTO",                             //122   T:笆
#ifdef SDRAM_16Mb_Mode
        "INAT.",//"INA.=INATTIVO"//"CHI",               //"OFF"="CHIUSO",       //123   T:闽
#else//SDRAM_16Mb_Mode
        "INATTIVO",//"INA.=INATTIVO"//"CHI",                //"OFF"="CHIUSO",       //123   T:闽
#endif//SDRAM_16Mb_Mode
        #ifdef SHOW_DRM_REGISTRATION_CODE_IN_SETUP
        "DIVX[R] VOD", //124
        #else
        "",//"TM/CH/TL",                        //124
        #endif
        "CAPITOLO",     //"CHAPTER",            //125   T:彻竊
        "TITOLO",       //"TITLE",              //126   T:夹肈
        OS_ICON_ANGLE,                      //127
     #if defined(HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif
        OS_16_9,                            //129   T:16:9 --
        OS_4_3LB,                           //130   T:4:3LB --
        OS_4_3PS,                           //131
        "PAL",                              //132
        "NTSC",                             //133
        "PAL60",                            //134

#ifdef RATING_8
       "3 PG",                //135   T:level 3
        #ifdef FIX_RATING_8_DISPLAY
        "2 G",                  //136   T:(level 2)
        "1 KID SAFE",                //137   T:(level 1)
        #else
        "2",                  //136   T:level 2
        "1 G",                //137   T:level 1
        #endif
#else
        "NON ADULTO",       //"NO ADULT",           //135   T:辅导级
        "SICURO PERBA.",    //"KID SAFE"="SICURO PERBAMBINI",           //136   T:保留
        "NON LIMITATO",     //"VIEW ALL",           //137   T:礚
#endif


#if defined(SHOW_5_1CH)
        "5.1CA",        //"5.1CH",              //138   T:5.1羘笵
#else
        "SETUP 6CA",        //"6CH SETUP",          //138   T:6羘笵砞竚
#endif

        "SUBGRAVE",     //"SUBWOOFER",          //139   T:禬
        "SATURATION",         //140   SATURATION
        "ACCENDERE",        //"ON",                 //141   T:秨
        OS_DOBLY,                           //142
        Ch_clock,                           //143
        Ch_speaker,                         //144
        "PULIRE",       //"CLEAR",              //145   T:睲埃
        "  T  C",                               //146
        "--:--",                            //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",                             //148
#endif        
        "EDIT",                             //149   T:絪胯
        
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42,(Italian).
        "LIN. SUBTIT 2",      //150
#else
        "",//OS_DIR1,                           //150
#endif        
        #ifdef ADJUST_JPEG_SLIDE_TIME  ////lyc 2005/2/18
        "15 SEC",                   //151
        "30 SEC",                   //152
        "45 SEC",                   //153
        "50 SEC",                   //154
        #else
        "",//OS_DIR2,                           //151
        OS_DIR3,                            //152
        OS_DIR4,                            //153
        "PAL-NC",//OS_DIR5,                             //154
        #endif
        OS_LOCK,                            //155   T:---- L
        OS_UNLOCK,                          //156   T:---- U
        "HUE",                //157   HUE
        "PROLOGIC",//"-:--:--",                                 //158
        "MOVIE MODE",//"CERCHA PISTA",      //"TRACK SEARCH",       //159   T:虫Ρ穓
        "MUSIC MODE",//"CERCHA DISCO",      //"DISC SEARCH",        //160   T:羆盒穓
        
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//"TT:CA",           //"TT:CH",              //161
        #endif

        "T",                  //162

        OS_DIR0,                            //163
        "CONTRAST",           //164   CONTRAST
        OS_DIR7,                            //165
        OS_DIR8,                            //166
        OS_DIR9,                            //167
        "CANALE",       //"CHANNEL",            //168   T:羘笵
        "BRIGHTNESS",         //169   BRIGHTNESS
        "F/W ID",                           //170   T:硁ン絪絏
#ifdef OP_CUST_UI  
		"CHECKSUM",  
#else		    

        "ID CHIP",      //"CHIP ID",            //171   T:絪絏
#endif
        "REGIONE",      //"REGION",             //172   T:跋絏
        "MEMORY",//"FUNZIONE",          //"FUNCTION",           //173   T:滦弄滦佰
        "DYNAMIC",//"MODO",             //"MODE",               //174   T:家Α

        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

//        "",//"REGISTRARE",        //"RECORD",             //175   T:滦佰
//        "",//"IMPARARE",          //"STUDY",              //176   T:滦弄
//        "",//"SEGUIRE",           //"FOLLOW",             //177   T:蛤弄
        "MIC1 VOL",//"PARAGONE",            //"COMPARE",            //178   T:癸ゑ
        "MIC2 VOL",//"CONTATORE",       //"COUNTER",            //179   T:滦Ω计
//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU) 
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181
#else
        "",//"NIVELLO",         //"LEVEL",              //180   T:魁家Α
        "",//"ALTO",                //"HIGH",               //181   T:蔼珇借
#endif
#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",           //?                        //182   T:禬丁
#endif
        "",//"SUPER",            //?                        //183   T:禬蔼珇借
        "",//"OPERATING",        //?                        //184   T:秸竊よΑ
        "",//"MANUALE",         //"MANUAL",             //185   T:も笆
        OS_DIR10,                           //186
        OS_DIR11,                           //187
        "CONCERTO",     //"CONCERT",            //188   T:贾芔
        "CHIESA",       //"CHURCH",             //189   T:毙绑
        "PASSIVO",      //"PASSIVE",            //190   T:吏露
        "AMPIO",        //"WIDE",               //191   T:糴初
//        "",//"ANFITEATRO",        //"AMPHITH",            //192   T:蛾粿初
//        "",//"STADIO",            //"STADIUM",            //193   T:蔨▅繻
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192   3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "EQ",                               //194   T:А颗
        "STANDARD",                         //195   T:夹非
        "CLASSICO",     //"CLASSIC",            //196   T:ㄥ
        "ROCK",                             //197   T:穘簎
        "JAZZ",                             //198   T:里
        "POP",                              //199   T:瑈︽
        "PERSONALIT\xc0",   //"USER",               //200   T:┦
        "PERSONALIT\xc0",   //"ATTRIB",             //201   T:┦
        "AVANTI LENTO",     //"SF",                 //202   T:篊秈
        "INDIETRO LENTO",   //"SB",                 //203   T:篊癶

         "C",                                       //204   //show "C"

        "CENTRO",       //"CENTER",             //205   T:い竚喘羘竟
        "RETRO",        //"REAR",               //206   T:吏露喘羘竟

        #ifndef HIMAGE_RGB
        "TV-RGB",                           //207
        #else
        "RGB",                    //207
        #endif


        "4 PG13",                           //208   S:辅导级

        "RINVIO CENTRO",    //"CENTER DELAY",       //209   T:い竚┑筐
        "RINVIO SRND",      //"REAR DELAY",         //210   T:吏露┑筐
        "FRONTE",       //"FRONT",              //211   T:玡竚喘羘竟
        "VIDEO SETUP",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS
        "SETUP SISTEMA",    //"SYSTEM SETUP",       //214   T:╰参砞竚
        "SETUP ALTOP.",     //"SPEAKER SETUP"="SETUP ALTOPARLANTE",      //215   T:喘羘竟砞竚
        "SETUP AUDIO",      //"AUDIO SETUP",        //216   T:繵砞竚
        "DI FABRICA",       //"DEFAULT",            //217   T:
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "CONTROLLO CA.",    //"OUT CHANNEL"="CONTROLLO CANALE",        //218   T:羘笵北(not use)
        #endif
        
        #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU
        "   MNP   ",
        #else
        "PROTT. SCHER.",    //"SCREEN SAVER"="PROTTETORE SCHERMO",       //219   T:辊玂臔
        #endif
        #ifdef ORITRON_PASSWORD//libing 2005-4-29 9:53
        "SET DUFAULT VALUE",
        "CLEAR PASSWORD",             //221   T:(辅导级)
        "LOADER LOCKED",
        #else
        "MODO 1",       //"TYPE 1",             //220   T:家Α 1
        "MODO 2",       //"TYPE 2",             //221   T:家Α 2
        "MODO 3",       //"TYPE 3",             //222   T:家Α 3
        #endif

        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                                //223   S:5保留
        #endif
        
        "6 R",                              //224   S:限制级

        "ERRORE DISCO",     //"ERR DISC",           //225   S:错误碟片
        "SETUP DIGITA.",    //"DIGITAL SETUP",      //226   T:计絏砞竚
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "SETUP MIC.",       //"MIC SETUP",          //227   T:杠旦砞竚
        "VOLUME MIC.",      //"MIC VOL",            //228   T:杠旦秖
        #endif
        "CD IN RICUP",      //"CD RECOVERING",      //229   T:岿い     ------------- not use
        "UPGRADE INTELEGENTE",  //"SMART UPGRADE",      //230   T:醇ど
        "UPGRADE SUCCESSO", //"UPGRADE TO V ",      //231   T:どΘ
        "UPGRADE IN CORSO", //"UPGRADING",          //232   T:どい
        "NON SPEGNERE",     //"NOT POWER OFF",      //233   T:づ闽诀
        "REGIONE 0",        //"REGION 0",           //234   T:0 跋
        "REGIONE 1",        //"REGION 1",           //235   T:1 跋
        "REGIONE 2",        //"REGION 2",           //236   T:2 跋
        "REGIONE 3",        //"REGION 3",           //237   T:3 跋
        "REGIONE 4",        //"REGION 4",           //238   T:4 跋
        "SETUP LINGUA",     //"LANG SETUP",         //239   T:粂ē砞竚
        #ifdef SUPPORT_FUNCTION_MENU
	"DISPLAY",		//240
	#else 
        "",//"SETUP SRND",      //"SRND SETUP",         //240   T:吏露砞竚(not use)
        #endif
        "PAGINA PRICP.",    //"MAIN PAGE"="PAGINE PRINCIPALE",          //241   T:
#ifdef BBK_DVD
        /*"LINGUA AUDIO",       //"AUDIO LANG",         //242   T:繵粂ē*/
        "AUDIO",        //"AUDIO LANG",         //242   T:繵粂ē axel 2004/1/27 03:58 eliminate "LANG"
        /*"LIN. SUBTITOL",  //"SUBTITLE LANG"="LINGUA SUBTITOLO",      //243   T:辊粂ē*/
        "SUBTITOL", //"SUBTITLE LANG"="LINGUA SUBTITOLO",      //243   T:辊粂ē
#else
        "LINGUA AUDIO",     //"AUDIO LANG",         //242   T:繵粂ē
        "LIN. SUBTITOL",    //"SUBTITLE LANG"="LINGUA SUBTITOLO",      //243   T:辊粂ē
#endif
        "LINGUA MENU",      //"MENU LANG",          //244   T:垫虫粂ē
        "MODO MISTO",       //"DOWNMIX",            //245   T:睼家Α
        "RIPRENDERE",       //"RESTORE",            //246   T:確
        "LT/RT",                            //247
        "VSS",                              //248   T:店览吏露羘
        "MODO OP",      //"OP MODE",            //249   T:块家Α
        "USCITA LINEA",     //"LINE OUT",           //250   T:絬隔块
        "RF RIMOD",     //"RF REMOD",           //251   T:RF 秸俱
        "SIN.+DES.",        //"DUAL MONO"="SINISTRO.+DESTRO",          //252   T:オ+
        "MISTO",        //"MIX MONO",           //253   T:睼羘笵
        "MODO SURND",       //"SURND MODE",         //254   T:吏露家Α
#ifdef KSD_DVD
        "PRESS PLAY BUTTON TO CONTINUE",        //255   T:              S:请按播放键继续
#else
        "PRE FERMA",        //"PRE STOP",           //255   T:              S:准停止
#endif
//=================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER
},
#endif


#ifdef USE_JAPANESE_OSD
//Japanese OSD
{
        JOS_NULL,              //0
        JOS_NODISC,            //1     T:礚盒
        #if defined(INVALID_DISPLAY_HAND) 
        OS_NO,
        #else
        JOS_NO,       //2     T:眤岿 hand
        #endif
        JCh_trk,//"TRK",                   //3     T:Ρヘ
        OS_ICON_SVCD,          //4
        "DE-INTERLACE",//JOS_CHINESE,           //5     T:簙粂
        JOS_OPEN,              //6     T:癶
        JOS_CLOSE,             //7     T:闽超
        JOS_PLAY,              //8     T:冀
        JOS_REGION_5,          //9     T:5 跋
        JOS_PAUSE,             //10    T:既氨
        "RANDOM",              //11    T:繦诀冀
        JOS_RESUME,              //12    T:確冀
        OS_STOP,               //13    T:氨ゎ
        JOS_STEP,              //14    T:˙秈
        JOS_SELECT,            //15    T:匡拒
        JOS_READ,              //16    T:弄盒
        JOS_REGION_6,          //17    T:6 跋
        JOS_SIMULATE,          //18    T:家览
        JOS_FF,                //19    T:е秈
        JOS_FB,                //20    T:е癶
        JOS_NEXT,              //21    T:Ρ >>
        OS_NULL,               //22
        JOS_PREV,              //23    T:Ρ <<
        "DIR",//OS_NULL,               //24
        JOS_RETURN,            //25    T:匡虫
        Ch_repx,               //26
        Ch_rep1,               //27
        Ch_repd,               //28
        JOS_NONE,              //29    T:礚
        JOS_MENU,              //30    T:匡虫
        JOS_SCORE,             //31    T:だ计
        JOS_MARK,              //32    T:癘拘
        JOS_BROWSE,            //33    T:聅凝
        JOS_PROG,//"PROG",                 //34    T:
        "SAVING LOGO...",            //35
        "ALL LG SPK",//JOS_BASS_MODE_1,       //36    T:家Α1
        JOS_REP,               //37    T:確
        JOS_REP_DIR,           //38    T:ヘ魁確
        JOS_REP_1,             //39    T:虫Ρ確
        JOS_REP_ALL,           //40    T:盒確
        JOS_REP_CNL,           //41    T:確
        "ALL SM SPK",//JOS_BASS_MODE_2,       //42    T:家Α2
        //"8",                   //43    S:8保留
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
        #else// #ifdef HJ_APEX_FIX_SHOW_OSD
        "8 ADULT",            //43
        #endif// #ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",
        #endif
        "7 NC-17",             //44
        "GOTO",                //45    T:穓冀
        JOS_MUTE,              //46    T:繰
        JOS_CHL,              //47    T:オ羘笵
        JOS_CHR,              //48    T:羘笵
        JOS_STEREO,            //49    T:ミ砰羘
        "MUTE CANCEL",         //"SCORE MODE",         //50    T:(蝶だ家Α)
        JOS_LIVE,              //51    T:

#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "",                    //52    //not use
#endif
        "MIXED SPK",//JOS_BASS_MODE_3,       //53    T:家Α3
        OS_ICON_CDROM,         //54
        "",//JOS_TIME,              //55    T:丁
        "",                    //56    //not use
        JOS_ZOOM,                  //57    T:糴
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                    //58    //not use
#endif
        OS_ICON_LANG,          //59
        JOS_INTRO,             //60    T:苯磞
        "SRND",//JOS_SURR,              //61    T:吏露
        "PBC",                 //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "",//JOS_PBC_OFF,           //63    T:抖冀
#endif 
        "RAND" JOS_CANCEL, //64    T:繦诀冀
        "BASS MODE",//JOS_BASS_MANAGEMENT,   //65    T:家Α

            "",//JOS_POWER_ON,      //66

        JOS_REP "A-",          //67    T:確A-
        "PC-VGA",               //"PC-VGA",           //68
        JOS_REP "A-B",         //69    T:確A-B
        "A-B "JOS_CANCEL,    //70    T:確        JOS_CANCEL JOS_REP,    //70    T:確
        "PROG" JOS_CANCEL,   //71    T:絪胆?

        "",                    //72
        "",//JOS_ENGLISH,           //73    T:璣粂
        OS_ICON_VCD,           //74
        "",                    //75    //not use
        "",                    //76    //not use
        "CVBS",//OS_ICON_MP3,           //77
        OS_ICON_CDDA,          //78
        "48K",                    //79    //not use
        "96K",                    //80    //not use
        "192K",                    //81    //not use
        JOS_PICUP,             //82    T:礶簿
        JOS_PICDN,             //83    T:礶簿
        JOS_PICL,              //84    T:礶オ簿
        JOS_PICR,              //85    T:礶簿
        JCh_ch,//"CH",                 //86    T:彻竊
        JOS_ECHO,              //87    T:臫
        JCh_tt,//"TT",                  //88    T:夹肈
        "BAND",                    //89
        JOS_VOL,               //90    T:秖
        "DOWN SAMPLE",                    //91    //not use
        JOS_KEY,               //92    T:秸
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        JOS_9FRAME_1,            //94    T:虫Ρ礶
        JOS_AUTO_L,              //95    T:笆钡佰オ
        JOS_AUTO_R,              //96    T:笆钡佰
        "LOW",                    //97
        JOS_SEQUENCE,          //98    T:抖冀
        JOS_MENUPLAY,          //99    T:匡虫冀
        "",//JOS_SFE_OUT,           //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else        
        "",//JOS_SFE_STD,          //101
        "",//OS_SFE_EHNANCE,        //102
#endif
        "MEDIUM",                    //103
        JOS_PROG_PLAY,         //104   T:絪导僵
        "HIGH",                    //105
        JOS_DYNAMICRANGE,      //106     T:笆篈絛瞅
        OS_ICON_DVD,           //107
        JOS_OSD,               //108   T:礶陪ボ粂ē
        OS_ICON_SUBT,          //109
        JOS_TV_RATIO,          //110   T:棵辊礶ゑㄒ
        JOS_TV_SYS,            //111   T:筿跌诀╰参
        JOS_EXIT_MENU,         //112   T:癶砞﹚匡虫
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        JOS_AUD_OUT,           //113   T:计块
#endif
        JOS_VIDEO,             //114   T:跌癟块
        JOS_PASSWORD,          //115   T:盞絏
        JOS_RATING,            //116   T:
        "SPDIF/RAW",         //117   T:SPDIF/方絏

#if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
#else 
        "",//"AC3 6CH",             //118   T:AC3 6羘笵(not use)
#endif 

        "SPDIF/PCM",           //119
//        "",//"AC3 2CH",             //120   T:AC3 2羘笵(not use)
#ifdef SUPPORT_PALM
        "PAL-M",                //120
#else
        "",           //120
#endif
        #ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
        #elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
#elif defined(EASTECH_DVI)
        "YCbCr", //121
#else
        "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
#endif//SHOW_YCbCr
        
        JOS_AUTO,//"AUTO",                //122   T:笆
        JOS_OFF,               //123   T:闽
        "",//"TM/CH/TL",            //124
        JOS_CHAPTER,           //125   T:彻竊
        JOS_TITLE,             //126   T:夹肈
        OS_ICON_ANGLE,         //127
      #if defined(HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif
        JOS_16_9,              //129   T:16:9 --
        JOS_4_3LB,             //130   T:4:3LB --
        JOS_4_3PS,             //131
        "PAL",                 //132
        "NTSC",                //133
        "PAL60",               //134

        #ifdef RATING_8
            "3 PG",                //135   T:level 3
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else
            "2",                   //136   T:level 2
            "1 G",                 //137   T:level 1
            #endif
        #else
            JOS_NO_ADULT,          //135   T:獶A
            JOS_KID_ONLY,          //136   T:ㄠ担
            JOS_VIEW_ALL,        //137   T:礚
        #endif

        "6CH_SETUP",           //138   T:6羘笵砞竚
        JOS_SUBWOOFER,         //139   T:禬
#if 1//def GBM_NEW_JAPANESE
        JOS_SATURATION,
#else//#ifdef GBM_NEW_JAPANESE
        "SATURATION",         //140   SATURATION
#endif//#ifdef GBM_NEW_JAPANESE        
        JOS_ON,                //141   T:?

        OS_DOBLY,              //142
        Ch_clock,              //143
        Ch_speaker,            //144
        JOS_CLEAR,             //145   T:睲埃
        "  T  C",                //146
        "--:--",               //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        JOS_EDIT,                //149   T:絪胯
        
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42,(Japanese).
        JOS_SUBTITLE_LANG_2ND_SETUP,      //150
#else
        "",//OS_DIR1,               //150
#endif     
        "",//OS_DIR2,               //151
        OS_DIR3,               //152
        OS_DIR4,               //153
        "PAL-NC",//OS_DIR5,               //154
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
#if 1//def GBM_NEW_JAPANESE
        JOS_HUE,                //157
#else//#ifdef GBM_NEW_JAPANESE
        "HUE",                //157   HUE
#endif//#ifdef GBM_NEW_JAPANESE
        "PROLOGIC",//"-:--:--",             //158
        "MOVIE MODE",//JOS_TRK_S,             //159   T:虫Ρ穓
        "MUSIC MODE",//JOS_DISC_S,            //160   T:羆盒穓
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//"TT:CH",               //161
        #endif

        #ifdef REMAIN_TIME//nono 2-7-12 20:06
            "T",                   //162
        #else
            "",//"BOOKMARK",            //162
        #endif

        OS_DIR0,               //163
#if 1//def GBM_NEW_JAPANESE
        JOS_CONTRAST,           //164
#else//#ifdef GBM_NEW_JAPANESE
        "CONTRAST",           //164   CONTRAST
#endif//#ifdef GBM_NEW_JAPANESE
        OS_DIR7,               //165
        OS_DIR8,               //166
        OS_DIR9,               //167
        JOS_CH,                //168   T:羘笵
#if 1//def GBM_NEW_JAPANESE
        JOS_BRIGHT_SETUP,       //169
#else//GBM_NEW_JAPANESE
        "BRIGHTNESS",         //169   BRIGHTNESS
#endif//GBM_NEW_JAPANESE
        "F/W ID",              //170   T:硁ン絪絏
        JOS_CHIP_ID,           //171   T:絪絏
        JOS_REGION_CODE,       //172   T:跋絏
        "MEMORY",//JOS_FUNCTION,          //173   T:滦弄滦佰
        "DYNAMIC",//JOS_MODE,              //174   T:家Α

        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

//        "",//JOS_RECORD,            //175   T:滦佰
//        "",//"STUDY",            //176   T:滦弄
//        "",//JOS_FOLLOW,            //177   T:蛤弄

        "MIC1 VOL",//"COMPARE",            //178   T:癸ゑ
        "MIC2 VOL",//JOS_COUNTER,           //179   T:滦Ω计

#ifdef FUSS_DVD_AVD276
        TOS_PROV_CHAPTER,      //180   S:上一章节
        TOS_NEXT_CHAPTER,      //181   S:下一章节

//#elif defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#elif defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//JOS_NEXTPAGE,//"NEXT PAGE",                //180   
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU) 
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181 
#else
        "",//JOS_LEVEL,             //180   T:魁家Α
        "",//JOS_HIGH,              //181   T:蔼珇借
#endif

#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",             //182   T:禬丁
#endif
        "",//"SUPER",              //183   T:禬蔼珇借
        "",//"OPERATING",          //184   T:秸竊よΑ
        "",//JOS_MANUAL,            //185   T:も笆
        OS_DIR10,              //186
        OS_DIR11,              //187
        JOS_CONCERT,           //188   T:贾芔
        JOS_CHURCH,            //189   T:毙绑
        JOS_PASSIVE,//"PASSIVE",               //190   T:吏露
        JOS_WIDE,//"WIDE",                 //191   T:糴初
//        "",//JOS_AMPHITH,//"AMPHITH",            //192   T:蛾粿初
//        "",//JOS_STADIUM,           //193   T:蔨▅繻
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192    3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "EQ",//JOS_EQ,                //194   T:А颗
        JOS_STANDARD,          //195   T:夹非
        JOS_CLASSIC,           //196   T:ㄥ
        JOS_ROCK,              //197   T:穘簎
        JOS_JAZZ,              //198   T:里
        JOS_POP,               //199   T:瑈︽
        JOS_USER,              //200   T:┦
        "ATTRIB",              //201   T:┦
        JOS_SF,                //202   T:篊秈
        JOS_SB,                //203   T:篊癶

        "C",                   //204   //show "C"

        JOS_CSPK,              //205   T:い竚喘羘竟
        JOS_SSPK,              //206   T:吏露喘羘竟
        "TV-RGB",               //207
        "4 PG13",              //208   S:辅导级
        JOS_CSPK_DELAY,        //209   T:い竚┑筐
        JOS_SSPK_DELAY,        //210   T:吏露┑筐
        JOS_FSPK,              //211   T:玡竚喘羘竟
#if 1//def GBM_NEW_JAPANESE
        JOS_VIDEO,
#else//GBM_NEW_JAPANESE
        "VIDEO SETUP",        //212   VIDEO SETUP
#endif//GBM_NEW_JAPANESE
        "SHARPNESS",          //213   SHARPNESS
        JOS_SYS_SETUP,         //214   T:╰参砞﹚
        JOS_SPK_SETUP,         //215   T:喘羘竟砞﹚
        JOS_AUD_SETUP,         //216   T:繵砞﹚
        JOS_DEFAULT_SETUP,     //217   T:箇砞
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        JOS_GROUP,             //218   T:竤舱
        #endif
        
        JOS_SSAVER_SETUP,      //219   T:棵辊玂臔
        JOS_SSAVER_1,          //220   T:家Α 1
        JOS_SSAVER_2,          //221   T:家Α 2
        JOS_SSAVER_3,          //222   T:家Α 3
        
        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                   //223   T:5保留
        #endif
        
        "6 R",                 //224   T:限制级
        JOS_ERR_DISC,          //225   T:岿粇盒片
        JOS_DIGITAL_SETUP,     //226   T:ゑ计砞﹚
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        JOS_MIC_ONOFF,         //227   T:沉砞﹚
        JOS_MIC_VOL,           //228   T:沉秖
        #endif
        "CD RECOVERING",       //229   T:岿い     ------------- not use
        JOS_SMART_UPGRADE,     //230   T:醇ど
        JOS_UPGRADE_TO,        //231   T:どΘ
        JOS_UPGRADING,         //232   T:どい
        JOS_NOT_POWEROFF,      //233   T:づ闽诀
        JOS_REGION_0,          //234   T:0 跋
        JOS_REGION_1,          //235   T:1 跋
        JOS_REGION_2,          //236   T:2 跋
        JOS_REGION_3,          //237   T:3 跋
        JOS_REGION_4,          //238   T:4 跋
        JOS_LANG_SETUP,        //239   T:粂ē砞﹚
        #ifdef SUPPORT_FUNCTION_MENU
	"DISPLAY",	       //240
	#else
        "",                    //240   //not use
        #endif
        JOS_RETURN_MAIN_SETUP, //241   T:
        JOS_AUDIO_LANG_SETUP,  //242   T:繵粂ē
        JOS_SUBTITLE_LANG_SETUP,//243  T:辊粂ē
        JOS_MENU_LANG_SETUP,   //244   T:匡虫粂ē
        JOS_DOWNMIX_SETUP,     //245   T:睼家Α
        JOS_RESTORE_SETUP,     //246   T:確
        "LT/RT",               //247
        "VSS",                 //248   T:店览吏露羘
        JOS_DOLBY_OP_SETUP,    //249   T:块家Α
        JOS_DOLBY_LINE_SETUP,  //250   T:絬隔块
        JOS_DOLBY_RF_SETUP,    //251   T:RF 秸俱
        JOS_DUAL_MONO_SETUP,   //252   T:オ+
        JOS_MIX_MONO_SETUP,    //253   T:睼羘笵
        JOS_SURROUND_MODE,     //254   T:吏露家Α
#ifdef KSD_DVD
        "PRESS PLAY BUTTON TO CONTINUE",        //255   T:              S:请按播放键继续
#else
        "PRE STOP",            //255   T:氨ゎ
#endif
//=================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER
},
#endif//#ifdef USE_JAPANESE_OSD

#ifdef USE_RUSSIAN_OSD

#ifdef RUSSIAN_FIX_HJ
{       
    "",                         //0
    "\r\x9d""\r\x98""\r\x92"" ""\r\x90""\r\x86""\r\x87""\r\x96""\r\x8a",  //"NO DISC",          //1     T:(礚盒)            S:(无碟)
    "\r\x8e""\r\x93""\r\x86""\r\x81""\r\x96""\r\x8a"" ""\r\x88""\r\x82""\r\x8e""\r\x90""\r\x8a",//        //2     T:(眤岿 hand)   S:(您按错了 HAND)
    "TRK",             //"\r\x90""\r\x8e""\r\x8c",                //3     T:(Ρヘ)            S:(曲目)
    OS_ICON_SVCD,         //4
    "DE-INTERLACE",//"CHINESE",            //5  not use
    "\r\x8e""\r\x92""\r\x96""\r\x8c",//"OPEN",               //6     T:()            S:(出仓)
    "\r\x94""\r\x8a""\r\x96""\r\x8c",//"CLOSE",              //7     T:(闽)            S:(关仓)
    //"\r\x88""\r\x8e""\r\x87""\r\x8b""\r\x8c",   //"PLAY",               //8     T:(冀)            S:(播放)
    "\x88""\x8e""\x87""\x8b""\x8c",   //"PLAY",               //8     T:(冀)            S:(播放)
        "\r\x8c""\r\x98""\r\x99""\r\x86""\r\x8e""\r\x9d"" ""5", //"REGION 5",           //9     T:(5 跋)            S:(5区)
    "\r\x8b""\r\x8a""\r\x89""\r\x94""\r\x8a",//"PAUSE",              //10    T:(既氨)            S:(暂停)
    "\r\x87""\r\x8f""\r\x89""\r\x9c""\r\x8a""\r\x95""\r\x9d""\r\x8e",//"RANDOM",             //11    T:(繦诀冀)        S:(随即播放)
    "\r\x88""\r\x98""\r\x8c""\r\x9d""\r\x89""\r\x92""\r\x91",//"RESUME",             //12    T:(確冀)        S:(恢复播放)
    "\r\x87""\r\x92""\r\x8e""\r\x8b",//"STOP",               //13    T:(氨ゎ)            S:(停止)
    "\r\x93""\r\x8a""\r\x99",//"STEP",               //14    T:(˙秈)            S:(单步)
    "\r\x88""\r\x97""\r\x81""\r\x8e""\r\x8c",//"SELECT",             //15    T:(匡拒)            S:(选择)
    #if defined(FUSS_DVD)||defined(HUAJIA_DVD)||defined(HIMAGE_CARD_READER)   //NONO 2-5-15 3:01
    "\r\x94""\r\x8a""\r\x99""\r\x8c""\r\x89""\r\x94""\r\x96""\r\x8a",//"LOADING",        //16    T:(弄盒)            S:(读碟)
    #else
         "\r\x87""\r\x9c""\r\x86""\r\x92""\r\x97""\r\x88""\r\x8a""\r\x9d""\r\x86""\r\x98",// "READ",           //16    T:(弄盒)            S:(读碟)
    #endif
     "\r\x8c""\r\x98""\r\x99""\r\x86""\r\x8e""\r\x9d"" ""6",//"REGION 6",           //17    T:(6 跋)
     "\r\x8a""\r\x9d""\r\x8a""\r\x8f""\r\x8e""\r\x99",//"ANALOG"    "SPDIF/OFF",             //18    T:(家览)
     "\r\x88""\r\x8b""\r\x98""\r\x8c""\r\x98""\r\x90",//"FORWARD",            //19    T:(е秈)
    "\r\x9d""\r\x8a""\r\x94""\r\x8a""\r\x90",//"BACKWARD",           //20    T:(е癶)
    "\r\x87""\r\x8f""\r\x98""\r\x90", //"NEXT",               //21    T:(Ρ >>)
    
    "",                 //22
    
     "\r\x8b""\r\x8c""\r\x98""\r\x90",//"PREV",               //23    T:(Ρ <<)
    
     "DIR",                     //24

     "\r\x88""\r\x8e""\r\x94""\r\x88""\r\x8c""\r\x8a""\r\x92",//"RETURN",             //25    T:(垫虫)
     Ch_repx,              //26
     Ch_rep1,              //27
     Ch_repd,              //28
     "OFF",                //29    T:(礚)              S:(无)


    "\r\x9a""\r\x98""\r\x9d""\r\x7f",//"MENU",               //30    T:(匡虫)            S:(选单)
        "SCORE",              //31    T:(だ计)            S:(分数)
        "MARK",               //32    T:(癘拘)            S:(记忆)
    "\r\x8b""\r\x8c""\r\x8e""\r\x87""\r\x9a""\r\x8e""\r\x92""\r\x8c", //"MARK",               //32    T:(癘拘)            S:(记忆)
    //"\r\x8b""\r\x8c""\r\x8e""\r\x99",//"\r\x8c",//"PROG",               //34    T:(絪祘)            S:(编程)
    "\x8b""\x8c""\x8e""\x99",//"\r\x8c",//"PROG",               //34    T:(絪祘)            S:(编程)
    "SAVING LOGO...",                   //35    //not use
    "ALL LG SPK",         //36    T:(家Α1)
    "\r\x8b""\r\x8e""\r\x88""\r\x92",//"REP",                //37    T:(確)
    "\r\x8b""\r\x8e""\r\x88""\r\x92""\r\x8b""\r\x8a""\r\x8b""\r\x96""\r\x89",//"REP DIR",            //38    T:(ヘ魁確)
    "\r\x8b""\r\x8e""\r\x88""\r\x92",//"REP 1",              //39    T:(虫Ρ確)
    "\r\x8b""\r\x8e""\r\x88""\r\x92"" ""\r\x88""\r\x87""\r\x98",//"REP ALL",            //40    T:(盒確)
    "\r\x88""\r\x97""\r\x96""\r\x8f"" ""\r\x8b""\r\x8e""\r\x88""\r\x92",//"REP CANCEL",         //41    T:(確)
     "ALL SM SPK",         //42    T:(家Α2)
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
        #else// #ifdef HJ_APEX_FIX_SHOW_OSD
        "8 ADULT",            //43
        #endif// #ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",
        #endif
        "7 NC-17",            //44    T:(虫Ρ冀)
    "\r\x8b""\r\x98""\r\x8c""\r\x98""\r\x82""\r\x90",//"GOTO",               //45    T:(穓)
    "\r\x9d""\r\x98""\r\x92""\r\x94""\r\x88""\r\x89""\r\x96""\r\x8a",//"MUTE",               //46    T:(繰)
    "MOHO L",             //47    T:(オ羘笵)
        "MOHO R",             //48    T:(羘笵)
    "\r\x87""\r\x92""\r\x98""\r\x8c""\r\x98""\r\x8e",//"STEREO",             //49    T:(ミ砰羘)
#ifdef HANYANG_MUTEOFF      //caohui 2004-5-13 15:59
        "MUTE OFF",                   //50    //not use
#else
    "DEMUTE",                   //50    //not use
#endif
        "LIVE",               //51    T:
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "",                   //52    //not use
#endif
        "MIXED SPK",          //53    T:(家Α3)
        OS_ICON_CDROM,        //54
        "TIME",               //55    T:(丁)            S:(时间)
        "",                   //56    //not use
        "ZOOM",               //57    T:(糴)            S:(放宽)
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                    //58    //not use
#endif
        OS_ICON_LANG,         //59
    "\r\x88""\r\x87""\r\x92""\r\x89""\r\x8b", //"INTRO",              //60    T:(苯磞)            S:(扫描)
    //"\r\x8e""\r\x96""\r\x8c""\r\x89""\r\x7e",//"SRND",//"SURROUND",           //61    T:(吏露)            S:(环绕)
    "\x8e""\x96""\x8c""\x89",//"\r\x7e",//"SRND",//"SURROUND",           //61    T:(吏露)            S:(环绕)
    "\r\x8c""\r\x88""\r\x87",//"PBC",                //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
    "",            //63    T:(抖冀)
#endif
        "RAND CANCEL",        //64    T:(繦诀冀)    S:(随即播放取消)
        "BASS MODE",          //65    T:(家Α)

          "",                //66

        "\r\x8b""\r\x8e""\r\x88""\r\x92"" ""A-",//"REPEAT A-",          //67    T:(確A-)          S:(重复 A   )
        "PC-VGA",               //"PC-VGA",           //68
         "\r\x8b""\r\x8e""\r\x88""\r\x92"" ""A-B",//"REPEAT A-B",         //69    T:(確A-B)         S:(重复播放A-B)
    "\r\x8a""\r\x88"" ""\r\x8e""\r\x92""\r\x9a""\r\x98""\r\x9d""\r\x8a",//"A-B CANCEL",         //70    T:(確)        S:(A-B取消)
    "\r\x8b""\r\x8c""\r\x8e""\r\x99""\r\x8c"" ""\r\x88""\r\x97""\r\x96""\r\x8f", //"PRG CANCEL",         //71    T:(絪胆)            S:(编程取消)
    "",                   //72
        "",            //73    T:(璣粂)            S:(英文)
        OS_ICON_VCD,          //74
        "",                   //75    //not use
        "",                   //76    //not use
        "CVBS",//OS_ICON_MP3,          //77
        OS_ICON_CDDA,         //78
        "48K",                   //79    //not use
        "96K",                   //80    //not use
        "192K",                   //81    //not use
    "ZOOM UP",            //82    T:(礶簿)        S:(放大上)
    "ZOOM DOWN",          //83    T:(礶簿)        S:(放大下)
        "ZOOM LEFT",          //84    T:(礶オ簿)        S:(放大左)
        "ZOOM RIGHT",         //85    T:(礶簿)        S:(放大右)
    "\r\x87""\r\x9d",//"CH",                 //86    T:(彻竊)            S:(章节)
    "\r\x80""\r\x82""\r\x8e",//"ECHO",               //87    T:(睼臫)            S:(混响)
    "\r\x92""\r\x92",//"TT",                 //88    T:(夹肈)            S:(标题)
    //"\r\x90""\r\x86""\r\x8a""\r\x8b""\r\x8a""\r\x94",//"BAND",               //89    T:(繵眯)
    "\x90""\x86""\x8a""\x8b",//"\r\x8a""\r\x94",//"BAND",               //89    T:(繵眯)
    "\r\x99""\r\x8c""\r\x8e""\r\x9a""\r\x96",//"VOL",                //90    T:(秖)            S:(音量)
    "DOWN SAMPLE",        //91    //not use
    //"\r\x92""\r\x8e""\r\x9d",//"KEY",                //92    T:(秸)            S:(音调)
    "\x92""\x8e""\x9d",//"KEY",                //92    T:(秸)            S:(音调)
    #ifdef P_SCAN_ONLY_CHG_INT_MODE
    "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
    #else
        "S-VIDEO",            //93
        #endif

        "9FRAME_1",           //94    T:(虫Ρ礶)      S:(单曲九画面)
        "AUTO L",             //95    T:(笆钡佰オ)      S:(自动接唱左)
        "AUTO R",             //96    T:(笆钡佰)      S:(自动接唱右)
        "LOW",                //97    // LOW

        "SEQ PLAY",           //98    T:(抖冀)        S:(顺序播放)

        "MENU PLAY",          //99    T:(垫虫冀)        S:(菜单播放)
        "LFE OUT",            //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else        
        "STANDARD",           //101
        "ENHANCE",            //102
#endif        
    "\r\x87""\r\x8c""\r\x98""\r\x90""\r\x9d""\r\x98",//"MEDIUM",             //103   // MEDIUM
     "PRG PLAY",           //104   T:(絪导僵)
    "\r\x88""\r\x97""\r\x87""\r\x8e""\r\x96",//"HIGH",               //105   // HIGH
    "\r\x90""\r\x86""\r\x9d""\r\x8a""\r\x9a"" ""\r\x90""\r\x86""\r\x8a""\r\x8b""\r\x8a""\r\x94",//"DYNAMIC RANGE",      //106
    OS_ICON_DVD,          //107
         "\r\x9e""\r\x94""\r\x97""\r\x96"" ""OSD",//"OSD LANGUAGE",       //108   T:(礶陪ボ粂ē)    S:(画面显示语言)
        OS_ICON_SUBT,         //109
    "\r\x92""\r\x86""\r\x8b"" ""\r\x92""\r\x88",//"TV TYPE",              //110   T:(辊礶ゑㄒ)    S:(屏幕画面比例)
    "\r\x87""\r\x92""\r\x8a""\r\x9d""\r\x90""\r\x8a""\r\x8c""\r\x92"" ""\r\x92""\r\x88", //"TV SYSTEM",       //111   T:(筿跌诀Α)      S:(电视机制式)
    "\r\x9d""\r\x8a""\r\x87""\r\x92""\r\x8c"" ""\r\x88""\r\x97""\r\x82""\r\x8e""\r\x90",//"EXIT SETUP",         //112   T:(癶砞竚垫虫)    S:(推出设置菜单)
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
    "\r\x8a""\r\x89""\r\x90""\r\x86""\r\x8e"" ""\r\x88""\r\x97""\r\x82", //"AUDIO OUT",          //113   T:(计絏块)        S:(数码输出)
#endif
    "\r\x88""\r\x86""\r\x90""\r\x98""\r\x8e",//"VIDEO",              //114   T:(跌繵块)        S:(视频输出)
    "\r\x8b""\r\x8a""\r\x8c""\r\x8e""\r\x8f""\r\x91",//"PASSWORD",           //115   T:(盞絏)            S:(密码)
    "\r\x8c""\r\x98""\r\x95""\r\x92""\r\x86""\r\x9d""\r\x99", //"RATING",             //116   T:()            S:(级别)
    "SPDIF/RAW",          //117   T:(SPDIF/方絏)      S:(SPDIF/源码)

        #if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
        #else
            "",              //118   T:(AC3 6羘笵)
        #endif

        "SPDIF/PCM",          //119

        #if defined(SUPPORT_PALM)
            "PAL-M",                //120
        #else
            "",              //120   T:(AC3 2羘笵)       S:AC3 2声道(not use)
        #endif

        #ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
        #elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
#elif defined(EASTECH_DVI)
        "YCbCr", //121
#else
        "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
#endif//SHOW_YCbCr
        
    "\r\x8a""\r\x88""\r\x92""\r\x8e",//"AUTO",               //122   T:(笆)            S:(自动)
     //"\r\x88""\r\x97""\r\x96""\r\x8f",// "OFF",                //123   T:(闽)              S:(关)
     "\x88""\x97""\x96""\x8f",// "OFF",                //123   T:(闽)              S:(关)
     "",           //124
    "\r\x85""\r\x8c""\r\x8a""\r\x99""\r\x9a""\r\x98""\r\x9d""\r\x92", //"CHAPTER",            //125   T:(彻竊)            S:(章节)
    "\r\x8c""\r\x94""\r\x90""\r\x98""\r\x8f",//"TITLE",              //126   T:(夹肈)            S:(标题)
     OS_ICON_ANGLE,        //127
      #if defined(HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif
        OS_16_9,              //129   T:(16:9 --)
        OS_4_3LB,             //130   T:(4:3LB --)
        OS_4_3PS,             //131
        "PAL",                //132
        "NTSC",               //133
        "PAL60",              //134
    #ifdef RATING_8
        "3 PG",               //135   T:(level 3)
        #ifdef FIX_RATING_8_DISPLAY
        "2 G",                  //136   T:(level 2)
        "1 KID SAFE",                //137   T:(level 1)
        #else
        "2",                  //136   T:(level 2)
        "1 G",                //137   T:(level 1)
        #endif
            
        #else
        "NO ADULT",           //135   T:(辅导级)
         "\r\x9a""\r\x8e""\r\x7e""\r\x9d""\r\x8e"" ""\r\x90""\r\x98""\r\x92""\r\x9e""\r\x9a", //"KID SAFE",           //136   T:(保留)
         "\r\x8b""\r\x8c""\r\x8e""\r\x87""\r\x9a"" ""\r\x88""\r\x87""\r\x98", //"VIEW ALL",           //137   T:(礚)
        #endif
        
        #if defined(SHOW_5_1CH)
            "5.1CH",              //138   T:(5.1羘笵)
        #else
            "6CH SETUP",          //138   T:(6羘笵砞竚)
        #endif
        
        "\r\x87""\r\x8a""\r\x81""\r\x88""\r\x89""\r\x85""\r\x98""\r\x8c", //"SUBWOOFER",          //139   T:(禬)
         "\r\x9d""\r\x8a""\r\x87""\r\x97""\r\x93""\r\x98""\r\x9d""\r\x9d",//"SATURATION",         //140   SATURATION
          "\r\x88""\r\x96""\r\x8f",//"ON",                 //141   T:
         OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
    //"\r\x8e""\r\x9c",//"\r\x86""\r\x87",//"\r\x92",//"CLEAR",              //145   T:(睲埃)
    "\x8e""\x9c""\x86""\x87""\x92",//"CLEAR",              //145   T:(睲埃)
    "  T  C",               //146
        "--:--",              //147
    #ifdef  MP3_DIRECT_SELECT
        " ----",               //148
    #else        
        "[--]",               //148
    #endif        
         "EDIT",//"\r\x86""\r\x94""\r\x9a""\r\x98",//"\r\x9d",//"EDIT",               //149   T:(絪胯)
        
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42,(Russian).     
        "\r\x9e""\r\x94""\r\x97""\r\x96"" ""\r\x87""\r\x89""\r\x81""\r\x92""\r\x86""\r\x92""\r\x8c"" 2",  //150
#else
        "",//OS_DIR1,              //150
#endif   
        
        "",//OS_DIR2,              //151
        OS_DIR3,              //152
        OS_DIR4,              //153
        "PAL-NC",//OS_DIR5,              //154
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
         "\r\x8e""\r\x9c""\r\x9a""\r\x98""\r\x9d""\r\x96", //"HUE",                //157   HUE
        "PROLOGIC",//"-:--:--",            //158    //not use
        "MOVIE MODE",//"TRACK SEARCH",       //159   //not use
        "MUSIC MODE",//"DISC SEARCH",        //160   //not use

        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//TT:CH",               //161    //not use
        #endif

        #ifdef REMAIN_TIME//nono 2-7-12 20:06
            "T",                  //162
        #else
            "",           //162
        #endif

        OS_DIR0,              //163
     "\r\x96""\r\x8e""\r\x9d""\r\x92""\r\x8c""\r\x8a""\r\x87""\r\x92""\r\x9d",//"CONTRAST",           //164   CONTRAST
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
    "\r\x96""\r\x86""\r\x9d""\r\x86""\r\x8f",//"CHANNEL",            //168   T:(羘笵)            S:(声道)
    "\r\x9e""\r\x8c""\r\x96""\r\x8e""\r\x87""\r\x92""\r\x83", //"BRIGHTNESS",         //169   BRIGHTNESS
     "F/W ID",             //170   T:(硁ン絪絏)        S:(软件编码)
    "CHIP ID",            //171   T:(絪絏)        S:(芯片编码)
    "\r\x8c""\r\x98""\r\x99""\r\x86""\r\x8e""\r\x9d",//"REGION",             //172   T:(跋絏)            S:(区码)

    "MEMORY",//"FUNCTION",           //173  //not use T:(滦弄滦佰)        S:(复读复唱)
        "DYNAMIC",//"MODE",               //174  //not use  T:(家Α)            S:(模式)


    "LIVELY",               //175
    "SHOWPLACE",            //176
    "MILD",                 //177


    "MIC1 VOL",//"COMPARE",            //178   //not use T:(癸ゑ)            S:(对比)
    "MIC2 VOL",//"COUNTER",            //179   //not use T:(滦Ω计)        S:(重复次数)

    #ifdef FUSS_DVD_AVD276
        "PREV CHAPTER",      //180   S:上一章节
        "NEXT CHAPTER",      //181   S:下一章节
//  #elif defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
    #elif defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
    "NEXT PAGE",                //180
    "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
    #elif defined(SUPPORT_FUNCTION_MENU) 
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181 
    #else
        "",//"LEVEL",              //180   T:魁家Α        S:录音模式
        "",//"HIGH",               //181   T:蔼珇借          S:高品质
    #endif

#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
    "",//"NORMAL",             //182   T:(禬丁)        S:(超长时间)
#endif

    #ifdef NEWSTYLE_WINDOW
        "PLAYTITLE",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "TITLETIME",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "CHPTIME",//"MANUAL",             //185   T:(も笆)            S:(手动)
    #else
        "",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "",//"MANUAL",             //185   T:(も笆)            S:(手动)
    #endif

        OS_DIR10,             //186
        OS_DIR11,             //187
#if 0
     "\r\x96""\r\x8e""\r\x9d""\r\x9b""\r\x98""\r\x8c""\r\x92",//"CONCERT",            //188   T:(贾芔)          S:(音乐厅)
    "\r\x9b""\r\x98""\r\x8c""\r\x96""\r\x8e""\r\x88""\r\x9d",//"CHURCH",             //189   T:(毙绑)            S:(教堂)
    "\r\x8b""\r\x8a""\r\x87""\r\x87""\r\x86""\r\x88",//"PASSIVE",            //190   T:(吏露)            S:(环绕)
    "\r\x93""\r\x86""\r\x8c""\r\x8e""\r\x96",//"WIDE",               //191   T:(糴初)            S:(宽场)
#else
    "\x96""\x8e""\x9d""\x9b""\x98""\x8c""\x92",//"CONCERT",            //188   T:(贾芔)          S:(音乐厅)
    "\x9b""\x98""\x8c""\x96""\x8e""\x88""\x9d",//"CHURCH",             //189   T:(毙绑)            S:(教堂)
    "\x8b""\x8a""\x87""\x87""\x86""\x88",//"PASSIVE",            //190   T:(吏露)            S:(环绕)
    "\x93""\x86""\x8c""\x8e""\x96",//"WIDE",               //191   T:(糴初)            S:(宽场)
#endif
    #ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192
        "MPEG LOGO",            //193
    #else
            "",//OS_AMPHITH,           //192   T:(蛾粿初)
            "",//OS_STADIUM,           //193   T:(蔨▅繻)
    #endif
     "EQ",                 //194   T:(А颗)            S:(均衡)
#if 0
     "\r\x87""\r\x92""\r\x8a""\r\x9d""\r\x90""\r\x8a""\r\x8c""\r\x92",//"STANDARD",           //195   T:(夹非)            S:(标准)
     "\r\x96""\r\x8f""\r\x8a""\r\x87""\r\x87""\r\x86""\r\x96""\r\x8a", //"CLASSIC",            //196   T:(ㄥ)            S:(古典)
     "\r\x8c""\r\x8e""\r\x96",//"ROCK",               //197   T:(穘簎)            S:(摇滚)
    "\r\x90""\r\x7e""\r\x8a""\r\x94",// "JAZZ",               //198   T:(里)            S:(爵士)
    "\r\x8b""\r\x8e""\r\x8b",//"POP",                //199   T:(瑈︽)            S:(流行)
#else
     "\x87""\x92""\x8a""\x9d""\x90""\x8a""\x8c""\x92",//"STANDARD",           //195   T:(夹非)            S:(标准)
     "\x96""\x8f""\x8a""\x87""\x87""\x86""\x96""\x8a", //"CLASSIC",            //196   T:(ㄥ)            S:(古典)
     "\x8c""\x8e""\x96",//"ROCK",               //197   T:(穘簎)            S:(摇滚)
    "\x90""\x9f""\x8a""\x94",// "JAZZ",               //198   T:(里)            S:(爵士)
    "\x8b""\x8e""\x8b",//"POP",                //199   T:(瑈︽)            S:(流行)
#endif
    "USER",               //200   T:(┦)            S:(个性)
     //"\r\x8a""\r\x92""\r\x8c""\r\x86""\r\x81",//"ATTRIB",             //201   T:(┦)            S:(个性)
     "\x8a""\x92""\x8c""\x86""\x81",//"ATTRIB",             //201   T:(┦)            S:(个性)
    "SF",                 //202   T:(篊秈)            S:(慢进)
    "SB",                 //203   T:(篊癶)            S:(慢退)

      "C",                  //204   //show "C"
    "\r\x9b""\r\x98""\r\x9d""\r\x92""\r\x8c",//"CENTER",              //205   T:(い竚喘羘竟)      S:(中置扬声器)
    "\r\x92""\r\x97""\r\x8f",// "REAR",               //206   T:(吏露喘羘竟)      S:(环绕扬声器)
     #ifndef HIMAGE_RGB
            "TV-RGB",             //207
            #else
        "RGB",                    //207
        #endif
        "4 PG13",             //208   T:(辅导级)
    "\r\x94""\r\x8a""\r\x90""\r\x98""\r\x8c""\r\x7e"" ""\r\x9b""\r\x98""\r\x9d""\r\x92""\r\x8c",//"CENTER DELAY",       //209   T:(い竚┑筐)
    "\r\x94""\r\x8a""\r\x90""\r\x98""\r\x8c""\r\x7e"" ""\r\x92""\r\x97""\r\x8f",//"REAR DELAY",         //210   T:(吏露┑筐)
         "\r\x85""\r\x8c""\r\x8e""\r\x9d""\r\x92",   //"FRONT",              //211   T:(玡竚喘羘
    "VIDEO SETUP",        //212   VIDEO SETUP
     "\r\x8c""\r\x98""\r\x94""\r\x9b""\r\x8e""\r\x87""\r\x92""\r\x83",//"SHARPNESS",          //213   SHARPNESS
    "\r\x9d""\r\x8a""\r\x87""\r\x92""\r\x8c"" ""\r\x87""\r\x86""\r\x87""\r\x92""\r\x98""\r\x9a""\r\x9d",//"SYSTEM SETUP",       //214   T:(╰参砞竚)        S:(系统设置)
    "\r\x9d""\r\x8a""\r\x87""\r\x92""\r\x8c"" ""\r\x90""\r\x86""\r\x9d""\r\x8a""\r\x9a""\r\x86""\r\x96",//"SPEAKER SETUP",      //215   T:(喘羘竟砞竚)      S:(扬声器设置)
    "\r\x9d""\r\x8a""\r\x87""\r\x92""\r\x8c"" ""\r\x8a""\r\x89""\r\x90""\r\x86""\r\x8e",//"AUDIO SETUP",        //216   T:(繵砞竚)        S:(音频设置)
    "\r\x8b""\r\x8e"" ""\r\x89""\r\x9a""\r\x8e""\r\x8f""\r\x9c""\r\x8a""\r\x9d",//"DEFAULT",            //217   T:()          S:(缺省值)
    #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
    #else
    "GRP",                //218   //not use
    #endif
    
    #ifdef AUTO_PLAY
            "AUTO PLAY",       //219   T:(辊玂臔)        S:(屏幕保护)
    #elif defined(VCD_CDG_PLAY_CONTROL_BY_SETUPMENU)
        "   MNP   ",
    #else
            "\r\x94""\r\x8a""\r\x87""\r\x92""\r\x8a""\r\x88""\r\x96""\r\x8a",//"SCREEN SAVER",       //219   T:(辊玂臔)        S:(屏幕保护)
    #endif
    "TYPE 1",             //220   T:(家Α 1)          S:(模式1)


        "TYPE 2",             //221   T:(家Α 2)          S:(模式2)
        "TYPE 3",             //222   T:(家Α 3)          S:(模式3)

        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   S:(5保留)
        #endif
        
        "6 R",                //224   S:(限制级)

        #ifdef NOT_SUPPROT_VCD
        "NOT SUPPORTED CD",           //225   S:(错误碟片)
        #else
        "ERR DISC",           //225   S:(错误碟片)
        #endif
     "\r\x9d""\r\x8a""\r\x87""\r\x92""\r\x8c"" ""\r\x9b""\r\x86""\r\x85""\r\x8c""\r\x8e""\r\x88",//"DIGITAL SETUP",      //226   T:(计絏砞竚)
    #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
    "\r\x9d""\r\x8a""\r\x87""\r\x92""\r\x8c"" ""\r\x9a""\r\x86""\r\x96""\r\x8c",//"MIC SETUP",          //227   T:(杠旦砞竚)
    "\r\x99""\r\x8c""\r\x8e""\r\x9a""\r\x96"" ""\r\x9a""\r\x86""\r\x96""\r\x8c",//"MIC VOL",            //228   T:(杠旦秖)
    #endif
    "CD RECOVERING",      //229   T:(岿い)     ------------- not use
    "\r\x8e""\r\x81""\r\x9d""\r\x8e""\r\x88""\r\x8f""\r\x98""\r\x9d""\r\x98""\r\x9d""\r\x86""\r\x98",//"SMART UPGRADE",      //230   T:(醇ど)
    "\r\x8e""\r\x81""\r\x9d""\r\x8e""\r\x88""\r\x90""\r\x8e",//"UPGRADE TO V ",      //231   T:(どΘ)
    "\r\x8e""\r\x81""\r\x9d""\r\x8e""\r\x88""\r\x8f""\r\x9e""\r\x7f",//"UPGRADING",          //232   T:(どい)
    "\r\x9d""\r\x98""\r\x8e""\r\x92""\r\x96""\r\x8f""\r\x7f""\r\x9c""\r\x98""\r\x9d",// "NOT POWER OFF",      //233   T:(づ闽诀)
    "\r\x8c""\r\x98""\r\x99""\r\x86""\r\x8e""\r\x9d"" ""0",//"REGION 0",           //234   T:(0 跋)
      "\r\x8c""\r\x98""\r\x99""\r\x86""\r\x8e""\r\x9d"" ""1",//"REGION 1",           //235   T:(1 跋)
            "\r\x8c""\r\x98""\r\x99""\r\x86""\r\x8e""\r\x9d"" ""2",//"REGION 2",           //236   T:(2 跋)
        "\r\x8c""\r\x98""\r\x99""\r\x86""\r\x8e""\r\x9d"" ""3",//"REGION 3",           //237   T:(3 跋)
        "\r\x8c""\r\x98""\r\x99""\r\x86""\r\x8e""\r\x9d"" " "4",//"REGION 4",           //238   T:(4 跋)
      "\r\x9d""\r\x8a""\r\x87""\r\x92""\r\x8c"" ""\r\x9e""\r\x94""\r\x97""\r\x96", //"LANGUAGE SETUP",     //239   T:(粂ē砞竚)
      #ifdef SUPPORT_FUNCTION_MENU
      "DISPLAY",		    //240
      #else
      "",                   //240   //not use
      #endif
      "\r\x99""\r\x8f""\r\x8a""\r\x88""\r\x9d"" ""\r\x87""\r\x92""\r\x8c",  // "MAIN PAGE",          //241   T:()
      "\r\x9e""\r\x94""\r\x97""\r\x96"" ""\r\x94""\r\x88""\r\x89""\r\x96""\r\x8a",//"AUDIO LANG",         //242   T:(繵粂ē)
      "\r\x9e""\r\x94""\r\x97""\r\x96"" ""\r\x87""\r\x89""\r\x81""\r\x92""\r\x86""\r\x92""\r\x8c", //"SUBTITLE LANG",      //243   T:(辊粂ē)
     "\r\x9e""\r\x94""\r\x97""\r\x96"" ""\r\x9a""\r\x98""\r\x9d""\r\x7f",//"MENU LANG",          //244   T:(垫虫粂ē)
    "DOWNMIX",            //245   T:(睼家Α)
        "RESTORE",            //246   T:(確)
        "LT/RT",              //247
        "VSS",                //248   T:(店览吏露羘)      S:(虚拟环绕声)
        "OP MODE",            //249   T:(块家Α)        S:(输出模式)
        "LINE OUT",           //250   T:(絬隔块)        S:(线路输出)
        "RF REMOD",           //251   T:(RF 秸俱)         S:(RF调整)
        "DUAL MONO",          //252   T:(オ+)           S:(左+右)
       "MIX MONO",           //253   T:(睼羘笵)        S:(混合声道)
    "\r\x8e""\r\x96""\r\x8c""\r\x89""\r\x7e"" ""\r\x8c""\r\x98""\r\x7e""\r\x86""\r\x9a",   //"SURND MODE",         //254   T:(吏露家Α)        S:(环绕模式)
    "\r\x8b""\r\x8c""\r\x98""\r\x90. ""\r\x8e""\r\x87""\r\x92""\r\x8a""\r\x9d""\r\x8e""\r\x88""\r\x96""\r\x8a",//"PRE STOP",           //     T:                S:(准停止)

//=================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257

#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif

        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER
    
},
#else//RUSSIAN_FIX_HJ
{
        "",                   //0
        "\r\x90""\r\x86""\r\x87""\r\x96 ""\r\x8e""\r\x92""\r\x87""\r\x89.",//"\r\x92""\r\x87""\r\x92""\r\x88""\r\x89""\r\x98""\r\x92",//"NO DISC",            //1     T:(礚盒)            S:(无碟)
        "\r\x88""\r\x82""\r\x8e""\r\x90 ""\r\x9d""\r\x98""\r\x90""\r\x98.",//"\r\x95""\r\x87""\r\x92""\r\x88""\r\x86""\r\x92""\r\x98""\r\x8f""\r\x98""\r\x9d",//"INVALID KEY",        //2     T:(眤岿 hand)   S:(您按错了 HAND)
        "\r\x90""\r\x8e""\r\x8c",//"TRK",                //3     T:(Ρヘ)            S:(曲目)
        OS_ICON_SVCD,         //4
        "DE-INTERLACE",//"\r\x96""\r\x86""\r\x92""\r\x8a""\r\x95""\r\x87""\r\x96""\r\x86""\r\x95",//"CHINESE",            //5     T:(簙粂)            S:(中文)
        "\r\x8e""\r\x92""\r\x96""\r\x8c""\r\x97""\r\x92""\r\x91",//"OPEN",               //6     T:()            S:(出仓)
        "\r\x94""\r\x8a""\r\x96""\r\x8c""\r\x97""\r\x92""\r\x91",//"CLOSE",              //7     T:(闽)            S:(关仓)
        "\r\x8b""\r\x8c",//"\r\x8e""\r\x86",//"\r\x99""\r\x8c""\r\x97""\r\x88""\r\x8a""\r\x9d""\r\x86""\r\x98",//"PLAY",               //8     T:(冀)            S:(播放)
        "\r\x8c""\r\x98""\r\x99""\r\x86""\r\x8e""\r\x98"" 5",//"REGION 5",           //9     T:(5 跋)            S:(5区)
        "\r\x8b""\r\x8a""\r\x89""\r\x94""\r\x8a",//"PAUSE",              //10    T:(既氨)            S:(暂停)
        "\r\x88""\r\x97""\r\x81""\r\x8e""\r\x8c ""\r\x9d""\r\x8a""\r\x89""\r\x99""\r\x8a""\r\x90",//"RANDOM",             //11    T:(繦诀冀)        S:(随即播放)
        "\r\x8c""\r\x98""\r\x94""\r\x7f""\r\x9a""\r\x98",//"RESUME",             //12    T:(確冀)        S:(恢复播放)
        "\r\x87""\r\x92""\r\x8e""\r\x8b",//"STOP",               //13    T:(氨ゎ)            S:(停止)
        "\r\x8b""\r\x8c""\r\x8e""\r\x90""\r\x88""\r\x86""\r\x7e""\r\x98""\r\x9d""\r\x86""\r\x98 ""\r\x9d""\r\x8a""\r\x8d""\r\x8a""\r\x99",//"STEP",               //14    T:(˙秈)            S:(单步)
        "\r\x88""\r\x97""\r\x81""\r\x8e""\r\x8c",//"SELECT",             //15    T:(匡拒)            S:(选择)

        #ifdef FUSS_DVD   //NONO 2-5-15 3:01
            "LOADING",        //16    T:(弄盒)            S:(读碟)
        #else
            "\r\x87""\r\x9c""\r\x86""\r\x92""\r\x97""\r\x88""\r\x8a""\r\x9d""\r\x86""\r\x98",//"READ",           //16    T:(弄盒)            S:(读碟)
        #endif

        "\r\x8c""\r\x98""\r\x99""\r\x86""\r\x8e""\r\x98"" 6",//"REGION 6",           //17    T:(6 跋)
        "\r\x8a""\r\x9d""\r\x8a""\r\x8f""\r\x8e""\r\x99",//"ANALOG",             //18    T:(家览)
        "\r\x8b""\r\x98""\r\x8c""\r\x98. ""\r\x88""\r\x8b""\r\x98""\r\x8c""\r\x98""\r\x90",//"FORWARD",            //19    T:(е秈)
        "\r\x8b""\r\x98""\r\x8c""\r\x98. ""\r\x9d""\r\x8a""\r\x94""\r\x8a""\r\x90",//"BACKWARD",           //20    T:(е癶)
        "\r\x87""\r\x8f""\r\x98""\r\x90.",//"\r\x89""\r\x7f""\r\x93""\r\x98""\r\x98 ""\r\x8b""\r\x8c""\r\x8e""\r\x86""\r\x94""\r\x/88""\r\x98""\r\x90""\r\x98""\r\x9d""\r\x86""\r\x98",//"NEXT",               //21    T:(Ρ >>)

        #ifdef ADJ_SXICH
            "AMPVOL",           //22
        #else
            "",                 //22
        #endif

        "\r\x8b""\r\x8c""\r\x98""\r\x90.",//"\r\x97""\r\x90""\r\x89""\r\x93""\r\x98""\r\x98 ""\r\x8b""\r\x8c""\r\x8e""\r\x86""\r\x94""\r\x88""\r\x98""\r\x90""\r\x98""\r\x9d""\r\x86""\r\x98",//"PREV",               //23    T:(Ρ <<)

        "DIR",                     //24

        "\r\x88""\r\x8e""\r\x94""\r\x88""\r\x8c""\r\x8a""\r\x92",//"RETURN",             //25    T:(垫虫)
        Ch_repx,              //26
        Ch_rep1,              //27
        Ch_repd,              //28
        "\r\x88""\r\x97""\r\x96",//"OFF",                //29    T:(礚)              S:(无)
        "\r\x9a""\r\x98""\r\x9d""\r\x7f",//"MENU",               //30    T:(匡虫)            S:(选单)
        "\r\x87""\r\x9c""\r\x98""\r\x92",//"SCORE",              //31    T:(だ计)            S:(分数)
        "\r\x94""\r\x8a""\r\x9a""\r\x98",//"MARK",               //32    T:(癘拘)            S:(记忆)
        "\r\x81""\r\x8c""\r\x8a""\r\x89""\r\x94",//"BROWSE",             //33    T:(聅凝)            S:(浏览)
        "\r\x8b""\r\x8c""\r\x8e""\r\x99",//"PROG",               //34    T:(絪祘)            S:(编程)
        "SAVING LOGO...",           //35
        "ALL LG SPK",         //36    T:(家Α1)
        "REP",                //37    T:(確)
        "REP DIR",            //38    T:(ヘ魁確)
        "\r\x8b""\r\x8e""\r\x88."" 1",//"REP 1",              //39    T:(虫Ρ確)
        "\r\x8b""\r\x8e""\r\x88. ""\r\x88""\r\x87""\r\x98""\r\x99""\r\x8e",//"REP ALL",            //40    T:(盒確)
        "\r\x8e""\r\x92""\r\x9a""\r\x98""\r\x9d""\r\x8a ""\r\x8b""\r\x8e""\r\x88.",//"\r\x92""\r\x8e""\r\x8c""\r\x8a",//"REP CANCEL",         //41    T:(確)
        "ALL SM SPK",         //42    T:(家Α2)
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
        #else// #ifdef HJ_APEX_FIX_SHOW_OSD
        "8 ADULT",            //43
        #endif// #ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",
        #endif
        "7 NC-17",            //44    T:(虫Ρ冀)
        "\r\x9d""\r\x8a""\r\x8b""\r\x8c""\r\x8a""\r\x88""\r\x8f""\r\x98""\r\x9d""\r\x86""\r\x98",//"GOTO",               //45    T:(穓)
        "\r\x94""\r\x8a""\r\x99""\r\x8f""\r\x89""\r\x8d""\r\x98""\r\x9d""\r\x86""\r\x98",//"MUTE",               //46    T:(繰)
        "\r\x8c""\r\x98""\r\x7e""\r\x86""\r\x9a ""\r\x9a""\r\x8e""\r\x9d""\r\x8e ""\r\x8f""\r\x98",//"MONO L",             //47    T:(オ羘笵)
        "\r\x8c""\r\x98""\r\x7e""\r\x86""\r\x9a ""\r\x9a""\r\x8e""\r\x9d""\r\x8e ""\r\x8b""\r\x8c",//"MONO R",             //48    T:(羘笵)
        "\r\x87""\r\x92""\r\x98""\r\x8c""\r\x98""\r\x8e",//"STEREO",             //49    T:(ミ砰羘)
        "MUTE CANCEL",          //"SCORE MODE",         //50    T:(蝶だ家Α)
        "\r\x8e""\r\x81""\r\x97""\r\x9c""\r\x9d""\r\x8a""\r\x9e",//"LIVE",               //51    T:
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "TEST TONE",          //52
#endif
        "MIXED SPK",          //53    T:(家Α3)
        OS_ICON_CDROM,        //54
        "BALANCE L",//"\r\x92""\r\x8a""\r\x95""\r\x9a",//"TIME",               //55    T:(丁)            S:(时间)
        "TV VIDEO",             //56    //nono 3-2-26 18:36
        "\r\x94""\r\x89""\r\x9a""\r\x98""\r\x8c",//"ZOOM",               //57    T:(糴)            S:(放宽)
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                    //58    //not use
#endif
        OS_ICON_LANG,         //59
        "\r\x88""\r\x88""\r\x8e""\r\x90",//"INTRO",              //60    T:(苯磞)            S:(扫描)

        /*
        "\r\x8e\r\x96\r\x8c\r\x89\r\x7e\r\x8a\r\x7f.",//\r\x93",//"\r\x86""\r\x95""\r\x94""\r\x88""\r\x89""\r\x96",//"SURROUND",           //61    T:(吏露)            S:(环绕)
        //"\r\x8e""\r\x96""\r\x8c""\r\x89""\r\x7e""\r\x8a""\r\x7f""\r\x93",//"\r\x86""\r\x95""\r\x94""\r\x88""\r\x89""\r\x96",//"SURROUND",           //61    T:(吏露)            S:(环绕)
        */
        //Jefftest
        "\r\x8e\r\x96\r\x8c\r\x89",//"\r\x8e\r\x96\r\x8c\r\x89\r\x7e",
        //\r\x93",//"\r\x86""\r\x95""\r\x94""\r\x88""\r\x89""\r\x96",//"SURROUND",           //61    T:(吏露)            S:(环绕)

        "\r\x96""\r\x96""\r\x8b",//"PBC",                //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "BALANCE R",//"\r\x8e""\r\x92""\r\x96""\r\x8f.""\r\x96""\r\x96""\r\x8b",//"PBC OFF",            //63    T:(抖冀)
#endif
        "\r\x8e""\r\x92""\r\x9a""\r\x98""\r\x9d""\r\x8a ""\r\x88""\r\x97""\r\x81""\r\x8e""\r\x8c""\r\x8a ""\r\x9d""\r\x8a""\r\x89""\r\x99""\r\x8a""\r\x9a",//"RAND CANCEL",        //64    T:(繦诀冀)    S:(随即播放取消)
        "BASS MODE",          //65    T:(家Α)

       "AMP FRONT",                   //66

        "\r\x8b""\r\x8e""\r\x88""\r\x92""\r\x8e""\r\x8c ""A-",//"REPEAT A-",          //67    T:(確A-)          S:(重复 A )
        "PC-VGA",                   //68
        "\r\x8b""\r\x8e""\r\x88""\r\x92""\r\x8e""\r\x8c ""A-B",//"REPEAT A-B",         //69    T:(確A-B)        S:(重复播放A-B)
        "\r\x8e""\r\x92""\r\x9a""\r\x98""\r\x9d""\r\x8a ""A-B",//"A-B CANCEL",         //70    T:(確)        S:(A-B取消)
        "\r\x8e""\r\x92""\r\x9a""\r\x98""\r\x9d""\r\x8a ""\r\x8b""\r\x8c""\r\x8e""\r\x99""\r\x8c",//"PRG CANCEL",         //71    T:(絪胆)            S:(编程取消)
        "",                   //72
        #ifdef MACROVISION_SHOW_FW_VERSION
        MCRV_STR,//
        #else
        "",//"\r\x8a""\r\x9d""\r\x99""\r\x8f""\r\x86""\r\x95""\r\x87""\r\x96""\r\x86""\r\x95",//"ENGLISH",            //73    T:(璣粂)            S:(英文)
        #endif
        OS_ICON_VCD,          //74
        "NTSC-J",             //75    //NTSC-J
        "",                   //76    //not use
        "CVBS",//OS_ICON_MP3,          //77
        OS_ICON_CDDA,         //78

        #ifdef USE_IDE_SWITCH
        "CD-CARD",            //79    //CD-CARD
        "CD",                 //80    //CD
        "CARD",               //81    //CARD
        #else
        "48K",                   //79    //not use
        "96K",                   //80    //not use
        "192K",                   //81    //not use
        #endif

        "\r\x89""\r\x87""\r\x86""\r\x8f""\r\x98""\r\x9d""\r\x86""\r\x98"" "\
        "\r\x94""\r\x89""\r\x9a""\r\x98""\r\x8c""\r\x8a",//"ZOOM UP",            //82    T:(礶簿)        S:(放大上)
        "\r\x89""\r\x9a""\r\x98""\r\x9d""\r\x91""\r\x8d""\r\x98""\r\x9d""\r\x86""\r\x98"" "\
        "\r\x94""\r\x89""\r\x9a""\r\x98""\r\x8c""\r\x8a",//"ZOOM DOWN",          //83    T:(礶簿)        S:(放大下)
        "\r\x94""\r\x89""\r\x9a""\r\x98""\r\x8c ""\r\x8f""\r\x98""\r\x88.",//"ZOOM LEFT",          //84    T:(礶オ簿)        S:(放大左)
        "\r\x94""\r\x89""\r\x9a""\r\x98""\r\x8c ""\r\x8b""\r\x8c.",//"ZOOM RIGHT",         //85    T:(礶簿)        S:(放大右)
        "\r\x96""\r\x8a",//"CH",                 //86    T:(彻竊)            S:(章节)
        "\r\x80""\r\x82""\r\x8e",//"ECHO",               //87    T:(睼臫)            S:(混响)
        "\r\x94""\r\x8a",//"TT",                 //88    T:(夹肈)            S:(标题)
        "BAND",                   //89
        "\r\x94""\r\x88""\r\x89""\r\x96",//"VOL",                //90    T:(秖)            S:(音量)
        "DOWN SAMPLE",  //91    //not use
        "\r\x96""\r\x8f""\r\x7f""\r\x9c",//"KEY",                //92    T:(秸)            S:(音调)
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        "9FRAME_1",           //94    T:(虫Ρ礶)      S:(单曲九画面)
        "\r\x8a""\r\x88""\r\x92""\r\x8e"" ""\r\x8f""\r\x98""\r\x88",//"AUTO L",             //95    T:(笆钡佰オ)      S:(自动接唱左)
        "\r\x8a""\r\x88""\r\x92""\r\x8e"" ""\r\x8b""\r\x8c.",//"AUTO R",             //96    T:(笆钡佰)      S:(自动接唱右)
        "LOW",                   //97

            "\r\x8b""\r\x8e""\r\x87""\r\x8f""\r\x98""\r\x90""\r\x8e""\r\x88""\r\x8a"\
            "\r\x92""\r\x98""\r\x8f""\r\x91""\r\x9d""\r\x8e""\r\x98"" "\
            "\r\x8b""\r\x8c""\r\x8e""\r\x86""\r\x99""\r\x8c""\r\x97"\
            "\r\x88""\r\x8a""\r\x9d""\r\x86""\r\x98",//"SEQ PLAY",           //98    T:(抖冀)        S:(顺序播放)

        "\r\x9a""\r\x98""\r\x9d""\r\x7f"" ""\r\x8b""\r\x8c""\r\x86 "\
        "\r\x8b""\r\x8c""\r\x8e""\r\x86""\r\x99""\r\x8c""\r\x97"\
        "\r\x88""\r\x8a""\r\x9d""\r\x86""\r\x98",//"MENU PLAY",          //99    T:(垫虫冀)        S:(菜单播放)
        "LFE OUT",            //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else        
        "STANDARD",           //101
        "ENHANCE",            //102
#endif        
        "MEDIUM",                   //103
        "\r\x8b""\r\x8c""\r\x8e""\r\x99"\
        "\r\x8b""\r\x8c""\r\x8e""\r\x86""\r\x99""\r\x8c""\r\x97"\
        "\r\x88""\r\x8a""\r\x9d""\r\x86""\r\x98",//"PRG PLAY",           //104   T:(絪导僵)          S:(编程播放)
        "HIGH",                   //105
        "DYNAMIC RANGE",      //106
        OS_ICON_DVD,          //107
        "\r\x9e""\r\x94""\r\x97""\r\x96",//"OSD LANGUAGE",       //108   T:(礶陪ボ粂ē)    S:(画面显示语言)
        OS_ICON_SUBT,         //109
        "\r\x92""\r\x88"" ""\r\x8c""\r\x98""\r\x7e""\r\x86""\r\x9a",//"TV TYPE",              //110   T:(辊礶ゑㄒ)    S:(屏幕画面比例)
        "\r\x92""\r\x88"" ""\r\x87""\r\x86""\r\x87""\r\x92""\r\x98""\r\x9a""\r\x8a",//"TV SYSTEM",        //111   T:(筿跌诀Α)      S:(电视机制式)
//        "\r\x88""\r\x97""\r\x82""\r\x8e""\r\x90""\r\x9d""\r\x8a""\r\x9e"" ""\r\x89""\r\x87""\r\x92""\r\x8a""\r\x9d""\r\x8e""\r\x88""\r\x96""\r\x8a",//"EXIT SETUP",         //112   T:(癶砞竚垫虫)    S:(推出设置菜单)
        "\r\x88""\r\x97""\r\x82""\r\x8e""\r\x90"".""\r\x89""\r\x87""\r\x92""\r\x8a""\r\x9d""\r\x8e"".",//"EXIT SETUP",         //112   T:(癶砞竚垫虫)    S:(推出设置菜单)
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "\r\x88""\r\x97""\r\x82""\r\x8e""\r\x90""\r\x90"" "\
        "\r\x8a""\r\x89""\r\x90""\r\x86""\r\x8e",//"AUDIO OUT",          //113   T:(计絏块)        S:(数码输出)
#endif
        "\r\x88""\r\x86""\r\x90""\r\x98""\r\x8e",//"VIDEO",              //114   T:(跌繵块)        S:(视频输出)
        "\r\x8b""\r\x8a""\r\x8c""\r\x8e""\r\x8f""\r\x91",//"PASSWORD",           //115   T:(盞絏)            S:(密码)
        "\r\x8b""\r\x8e""\r\x8f""\r\x8e""\r\x7e""\r\x98""\r\x9d""\r\x86""\r\x98",//"RATING",             //116   T:()            S:(级别)
        "SPDIF/RAW",          //117   T:(SPDIF/方絏)      S:(SPDIF/源码)

#if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
#else 
       "AMP CENTER",           //118
#endif

       "SPDIF/PCM",          //119

//       "AMP SUBWOOFER",        //120
#ifdef SUPPORT_PALM
        "PAL-M",                //120
#else
        "AMP SUBWOOFER",           //120
#endif
        #ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
        #elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
#elif defined(EASTECH_DVI)
        "YCbCr", //121
#else
       "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
#endif//SHOW_YCbCr
        


        "\r\x8a""\r\x88""\r\x92""\r\x8e",//"AUTO",               //122   T:(笆)            S:(自动)
        "\r\x88""\r\x97""\r\x96",//"OFF",                //123   T:(闽)              S:(关)
        "",//"TM/CH/TL",           //124
        "\r\x8c""\r\x8a""\r\x94""\r\x90""\r\x98""\r\x8f",//"CHAPTER",            //125   T:(彻竊)            S:(章节)
        "\r\x94""\r\x8a""\r\x99""\r\x8f""\r\x8a""\r\x88""\r\x86""\r\x98",//"TITLE",              //126   T:(夹肈)            S:(标题)
        OS_ICON_ANGLE,        //127
     #if defined(HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif
        OS_16_9,              //129   T:(16:9 --)
        OS_4_3LB,             //130   T:(4:3LB --)
        OS_4_3PS,             //131
        "PAL",                //132
        "NTSC",               //133
        "PAL60",              //134

        #ifdef RATING_8
            "3 PG",               //135   T:(level 3)
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else
            "2",                  //136   T:(level 2)
            "1 G",                //137   T:(level 1)
            #endif
        #else
            "\r\x8b""\r\x8e""\r\x90""\r\x8c""\r\x8e""\r\x87. ""\r\x8c""\r\x98""\r\x7e""\r\x86""\r\x9a",//"NO ADULT",           //135   T:(辅导级)
            "\r\x94""\r\x8a""\r\x93."" ""\r\x90""\r\x8f""\r\x9e ""\r\x90""\r\x98""\r\x92.",//"KID SAFE",           //136   T:(保留)
            "\r\x8e""\r\x81""\r\x93""\r\x86""\r\x95."" ""\r\x8e"\
            "\r\x81""\r\x94""\r\x8e""\r\x8c.",//"VIEW ALL",           //137   T:(礚)
        #endif


        #if defined(SHOW_5_1CH)
            "5.1CH",              //138   T:(5.1羘笵)
        #else
            "6CH SETUP",          //138   T:(6羘笵砞竚)
        #endif

        "\r\x87""\r\x80""\r\x81""\r\x88""\r\x89""\r\x85""\r\x98""\r\x8c",//"SUBWOOFER",          //139   T:(禬)
        "SATURATION",         //140   SATURATION
        "\r\x88""\r\x96""\r\x8f",//"ON",                 //141   T:
        OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
        "\r\x9c""\r\x86""\r\x87""\r\x92""\r\x96",//"\r\x8a",//"CLEAR",              //145   T:(睲埃)
        //"\r\x94 ""\r\x96", //"  T  C",               //146
        //"--:--",              //147
        "  ""\r\x94  ""\r\x96", //"  T  C",               //146
        "--:--",              //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "\r\x8c""\r\x98""\r\x90""\r\x8a", //"EDIT",               //149   T:(絪胯)
        "",//OS_DIR1,              //150
        "",//OS_DIR2,              //151
        OS_DIR3,              //152
        OS_DIR4,              //153
        "PAL-NC",//OS_DIR5,              //154
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
        "HUE",                //157   HUE
        "PROLOGIC",//"-:--:--",            //158
        "MOVIE MODE",//"\r\x8b""\r\x8e""\r\x86""\r\x87""\r\x96 ""\r\x8b""\r\x8c""\r\x8e""\r\x86""\r\x94""\r\x88""\r\x98""\r\x90""\r\x98""\r\x9d""\r\x86""\r\x9e",//"TRACK SEARCH",       //159   T:(虫Ρ穓)        S:(单曲搜索)
        "MUSIC MODE",//"\r\x8b""\r\x8e""\r\x86""\r\x87""\r\x96 ""\r\x90""\r\x86""\r\x87""\r\x96""\r\x8a",//"DISC SEARCH",        //160   T:(羆盒穓)        S:(全碟搜索)

        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//"\r\x94""\r\x9a"":""\r\x96""\r\x8a",//"TT:CH",              //161
        #endif

        "T",                  //162//"\r\x9a""\r\x8a""\r\x8c""\r\x96""\r\x86""\r\x8c""\r\x8e.",//"BOOKMARK",           //162

        OS_DIR0,              //163
        "CONTRAST",           //164   CONTRAST
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
        "\r\x96""\r\x86""\r\x9d""\r\x86""\r\x8f",//"CHANNEL",            //168   T:(羘笵)            S:(声道)
        "BRIGHTNESS",         //169   BRIGHTNESS
        "\r\x8b""\r\x98""\r\x8c""\r\x98""\r\x9a""\r\x8e. ""\r\x88""\r\x8b""\r\x98""\r\x8c.",//"F/W ID",             //170   T:(硁ン絪絏)        S:(软件编码)
        "CHIP ID",            //171   T:(絪絏)        S:(芯片编码)
        "\r\x8e""\r\x81""\r\x8f""\r\x8a""\r\x87""\r\x92""\r\x91",//"REGION",             //172   T:(跋絏)            S:(区码)
        "MEMORY",//"\r\x85""\r\x89""\r\x9d""\r\x96""\r\x9b""\r\x86""\r\x86",//"FUNCTION",           //173   T:(滦弄滦佰)        S:(复读复唱)
        "DYNAMIC",//"\r\x8c""\r\x98""\r\x7e""\r\x86""\r\x9a",//"MODE",               //174   T:(家Α)            S:(模式)


        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

        "MIC1 VOL",//"\r\x87""\r\x8c""\r\x8a""\r\x88""\r\x9d""\r\x98""\r\x9d""\r\x86""\r\x98",//"COMPARE",    //178   T:(癸ゑ)            S:(对比)

        "MIC2 VOL",
        //"\r\x8e""\r\x81""\r\x8c""\r\x8a""\r\x92""\r\x9d""\r\x97""\r\x95"" """,
        //"\r\x8e""\r\x92""\r\x87""\r\x9c""\r\x98""\r\x92""\r\x88""\r\x8c""\r\x98""",
        //"\r\x9a""\r\x98""\r\x9d""\r\x86",
        //"COUNTER",            
        //179   T:(滦Ω计)        S:(重复次数)

//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU) 
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181      
#else
        "", //180   S:上一章节

        "", //181   S:下一章节
#endif
#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",             //182   T:(禬丁)        S:(超长时间)
#endif
        "",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "",                         //185
        OS_DIR10,             //186
        OS_DIR11,             //187
        "\r\x96""\r\x8e""\r\x9d.",//"\r\x9b""\r\x98""\r\x8c""\r\x92",//"CONCERT",188   T:(贾芔)          S:(音乐厅)
        "\r\x9b""\r\x98""\r\x8c.",//"\r\x96""\r\x8e""\r\x88""\r\x91",//"CHURCH", 189   T:(毙绑)            S:(教堂)
        "\r\x8b""\r\x8a""\r\x87.",//"\r\x87""\r\x86""\r\x88",//"PASSIVE",            //190   T:(吏露)            S:(环绕)
        "\r\x8d""\r\x86""\r\x8c.",//"\r\x86""\r\x9d""\r\x8a",//"WIDE",               //191   T:(糴初)            S:(宽场)
//        "",//"AMPHITH",            //192   T:(蛾粿初)          S:(圆剧场)
//        "",//"\r\x87""\r\x92""\r\x8a.",//"\r\x90""\r\x86""\r\x8e""\r\x9d",//"STADIUM",            //193   T:(蔨▅繻)          S:(体育场)
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192    3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "\r\x80""\r\x96",//"EQ",                 //194   T:(А颗)            S:(均衡)
        "\r\x87""\r\x92""\r\x8a.",//"\r\x9d.",//"\r\x90""\r\x8a""\r\x8c""\r\x92",//"STANDARD"           //195   T:(夹非)            S:(标准)
        "\r\x96""\r\x8f""\r\x8a.",//"\r\x87""\r\x87""\r\x86""\r\x96""\r\x8a",//"CLASSIC",            //196   T:(ㄥ)            S:(古典)
        "\r\x8c""\r\x8e""\r\x96",//"ROCK",               //197   T:(穘簎)            S:(摇滚)
        "\r\x90""\r\x7e""\r\x8a.",//"\r\x94",//"JAZZ",               //198   T:(里)            S:(爵士)
        "\r\x8b""\r\x8e""\r\x8b",//"POP",                //199   T:(瑈︽)            S:(流行)
        "\r\x8b""\r\x8e""\r\x8f.",//"\r\x91""\r\x94""\r\x8e""\r\x88.",//"USER",               //200   T:(┦)            S:(个性)
        "\r\x8a""\r\x92""\r\x92.",//"\r\x8c""\r\x86",//"\r\x81""\r\x89""\r\x92""\r\x97",//"ATTRIB",             //201   T:(┦)            S:(个性)
        "\r\x94""\r\x8a""\r\x9a""\r\x98""\r\x90""\r\x8f""\r\x98""\r\x9d""\r\x86""\r\x98",//"SF",                 //202   T:(篊秈)            S:(慢进)
        "SB",                 //203   T:(篊癶)            S:(慢退)

        "C",                  //204   //show "C"

        "\r\x9b""\r\x98""\r\x9d""\r\x92""\r\x8c",//"CENTER",              //205   T:(い竚喘羘竟)      S:(中置扬声器)
        "\r\x8b""\r\x98""\r\x8c""\r\x98""\r\x90",//"REAR",               //206   T:(吏露喘羘竟)      S:(环绕扬声器)

        "TV-RGB",             //207

        "4 PG13",             //208   T:(辅导级)
        "\r\x94""\r\x8a""\r\x9a""\r\x98""\r\x90. ""\r\x88""\r\x9b""\r\x98""\r\x9d""\r\x92.",//"CENTER DELAY",       //209   T:(い竚┑筐)
        "\r\x94""\r\x8a""\r\x9a""\r\x98""\r\x90. ""\r\x87""\r\x8b""\r\x8c""\r\x8a""\r\x88.",//"REAR DELAY",         //210   T:(吏露┑筐)
        "\r\x8b""\r\x98""\r\x8c""\r\x98""\r\x90""\r\x9d. ""\r\x9c""\r\x8a""\r\x87""\r\x92""\r\x91",//"FRONT",              //211   T:(玡竚喘羘竟)
        "VIDEO SETUP",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS

        "\r\x87""\r\x86""\r\x87""\r\x92""\r\x98""\r\x9a""\r\x9d""\r\x8a""\r\x9e ""\r\x89""\r\x87""\r\x92.",
        //"\r\x8a""\r\x9d""\r\x8e""\r\x88""\r\x96""\r\x8a",
        //"SYSTEM SETUP",       //214   T:(╰参砞竚)        S:(系统设置)

        "\r\x89""\r\x87""\r\x92. "/*"\r\x8a""\r\x9d""\r\x8e""\r\x88""\r\x96""\r\x8a "*/"\r\x96""\r\x8e""\r\x8f""\r\x8e""\r\x9d""\r\x8e""\r\x96",//"SPEAKER SETUP",      //215   T:(喘羘竟砞竚)      S:(扬声器设置)
        "\r\x8a""\r\x89""\r\x90""\r\x86""\r\x8e ""\r\x89""\r\x87""\r\x92""\r\x8a""\r\x9d""\r\x8e""\r\x88""\r\x96""\r\x8a",//"AUDIO SETUP",        //216   T:(繵砞竚)        S:(音频设置)
        "\r\x8e""\r\x92""\r\x87""\r\x89""\r\x92""\r\x87""\r\x92""\r\x88""\r\x86""\r\x98",//"DEFAULT",            //217   T:()          S:(缺省值)
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "GRP",                //218   //not use
        #endif
        
        #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU
        "   MNP   ",
        #else
        "\r\x94""\r\x8a""\r\x93""\r\x86""\r\x92. ""\r\x80""\r\x96""\r\x8c""\r\x8a""\r\x9d.",//"SCREEN SAVER",       //219   T:(辊玂臔)        S:(屏幕保护)
        #endif
        "\r\x92""\r\x86""\r\x8b"" 1",//"TYPE 1",             //220   T:(家Α 1)          S:(模式1)


        "\r\x92""\r\x86""\r\x8b"" 2",//"TYPE 2",             //221   T:(家Α 2)          S:(模式2)
        "\r\x92""\r\x86""\r\x8b"" 3",//"TYPE 3",             //222   T:(家Α 3)          S:(模式3)


        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   S:(5保留)
        #endif
        
        "6 R",                //224   S:(限制级)

        "\r\x8e""\r\x8d""\r\x86""\r\x81""\r\x96""\r\x8a ""\r\x90""\r\x86""\r\x87""\r\x96""\r\x8a",//"ERR DISC",           //225   S:(错误碟片)
        "\r\x9b""\r\x86""\r\x85""\r\x8c""\r\x8e""\r\x88""\r\x8a""\r\x9e ""\r\x89""\r\x87""\r\x92.",//"\r\x8a""\r\x9d""\r\x8e""\r\x88""\r\x96""\r\x8a",//"DIGITAL SETUP",      //226   T:(计絏砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "\r\x89""\r\x87""\r\x92""\r\x8a""\r\x9d. ""\r\x9a""\r\x86""\r\x96""\r\x8c""\r\x8e.",//"MIC SETUP",          //227   T:(杠旦砞竚)
        "\r\x94""\r\x88""\r\x89""\r\x96 ""\r\x88 ""\r\x9a""\r\x86""\r\x96""\r\x8c.",//"MIC VOL",            //228   T:(杠旦秖)
        #endif
        "\r\x86""\r\x94""\r\x88""\r\x8f""\r\x98""\r\x9c""\r\x98""\r\x9d""\r\x86""\r\x98 ""\r\x90""\r\x9d""\r\x87""\r\x96""\r\x8a",//"CD RECOVERING",      //229   T:(岿い)
        "SMART UPGRADE",      //230   T:(醇ど)
        "UPGRADE TO V ",      //231   T:(どΘ)
        "UPGRADING",          //232   T:(どい)
        "NOT POWER OFF",      //233   T:(づ闽诀)
        "\r\x8c""\r\x98""\r\x99""\r\x86""\r\x8e""\r\x98"" 0",//"REGION 0",           //234   T:(0 跋)
        "\r\x8c""\r\x98""\r\x99""\r\x86""\r\x8e""\r\x98"" 1",//"REGION 1",           //235   T:(1 跋)
        "\r\x8c""\r\x98""\r\x99""\r\x86""\r\x8e""\r\x98"" 2",//"REGION 2",           //236   T:(2 跋)
        "\r\x8c""\r\x98""\r\x99""\r\x86""\r\x8e""\r\x98"" 3",//"REGION 3",           //237   T:(3 跋)
        "\r\x8c""\r\x98""\r\x99""\r\x86""\r\x8e""\r\x98"" 4",//"REGION 4",           //238   T:(4 跋)
        "\r\x89""\r\x87""\r\x92""\r\x8a""\r\x9d""\r\x8e""\r\x88""\r\x96""\r\x8a ""\r\x9e""\r\x94""\r\x97""\r\x96""\r\x8a",//"LANGUAGE SETUP",     //239   T:(粂ē砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
	"DISPLAY",            //240
	#else
        "",                   //240   //not use
        #endif
        "\r\x99""\r\x8f""\r\x8a""\r\x88""\r\x9d. ""\r\x87""\r\x92""\r\x8c""\r\x8a""\r\x9d.",//"MAIN PAGE",          //241   T:()
        "\r\x9e""\r\x94""\r\x97""\r\x96 ""\r\x88 ""\r\x8c""\r\x98""\r\x7e""\r\x86""\r\x9a.",//"AUDIO LANG",         //242   T:(繵粂ē)
        "\r\x9e""\r\x94""\r\x97""\r\x96 ""\r\x88 ""\r\x94""\r\x8a""\r\x99""\r\x8e""\r\x8f.",//"SUBTITLE LANG",      //243   T:(辊粂ē)
        "\r\x9e""\r\x94""\r\x97""\r\x96 ""\r\x88 ""\r\x9a""\r\x98""\r\x9d""\r\x7f",//"MENU LANG",          //244   T:(垫虫粂ē)
        "DOWNMIX",            //245   T:(睼家Α)
        "\r\x8b""\r\x8e""\r\x88""\r\x92""\r\x8e.""\r\x87""\r\x8e""\r\x92""\r\x8c""\r\x8a.",//"RESTORE",            //246   T:(確)
        "LT/RT",              //247
        "VSS",                //248   T:(店览吏露羘)      S:(虚拟环绕声)
        "OP MODE",            //249   T:(块家Α)        S:(输出模式)
        "LINE OUT",           //250   T:(絬隔块)        S:(线路输出)
        "RF REMOD",           //251   T:(RF 秸俱)         S:(RF调整)
        "\r\x90""\r\x88""\r\x8e""\r\x95""\r\x87.""\r\x9a""\r\x8e""\r\x9d""\r\x8e""\r\x8c.",//"DUAL MONO",          //252   T:(オ+)           S:(左+右)
        "\r\x87""\r\x9a""\r\x98 ""\r\x88 ""\r\x8c""\r\x98 ""\r\x9a""\r\x8e""\r\x9d""\r\x8e",//"MIX MONO",           //253   T:(睼羘笵)        S:(混合声道)
        "\r\x8c""\r\x98""\r\x7e""\r\x86""\r\x9a ""\r\x8e""\r\x96""\r\x8c""\r\x89""\r\x7e""\r\x8a.",//"SURND MODE",         //254   T:(吏露家Α)        S:(环绕模式)
        "\r\x8b""\r\x8c""\r\x98""\r\x90. ""\r\x8e""\r\x87""\r\x92""\r\x8a""\r\x9d""\r\x8e""\r\x88""\r\x96""\r\x8a",//"PRE STOP",           //     T:                S:(准停止)
//=================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER
},

#endif//RUSSIAN_FIX_HJ
#endif//#ifdef USE_RUSSIAN_OSD

#ifdef USE_HEBRAIC_OSD
{
    "",                   		//0
	"\r\x95""\r\x8f""\r\x87""\r\x81"" ""\r\x8d""\r\x87""\r\x7e",  //"NO DISC",          //1     T:(礚盒)            S:(无碟)
    "\r\x98""\r\x8c""\r\x9b""\r\x95"" ""\r\x7e""\r\x8a"" ""\r\x82""\r\x8a""\r\x83""\r\x90""\r\x92",// "INVALIS ENTRY"       //2     T:(眤岿 hand)   S:(您按错了 HAND)
 	"\r\x95""\r\x96""\r\x92",  //"TRK",              //3     T:(Ρヘ)            S:(曲目)
  	OS_ICON_SVCD,                   		//4      
    
    "DE-INTERLACE",             //5	 
 	"\r\x85""\r\x98""\r\x92",//"OPEN",               //6     T:()            S:(出仓)
	"\r\x96""\r\x83""\r\x80""\r\x8f",//"CLOSE",              //7     T:(闽)            S:(关仓)
    "\r\x8d""\r\x80""\r\x8e",   //"PLAY",               //8     T:(冀)            S:(播放)
    "5"" ""\r\x96""\r\x83""\r\x84""\r\x87""\r\x7e", //"REGION 5",           //9     T:(5 跋)            S:(5区)
    "\r\x82""\r\x82""\r\x97""\r\x82",//"PAUSE",              //10    T:(既氨)            S:(暂停)
 	"\r\x87""\r\x7e""\r\x96""\r\x95""\r\x7e",//"RANDOM",             //11    T:(繦诀冀)        S:(随即播放)
    "\r\x96""\r\x83""\r\x84""\r\x85",//"RESUME",             //12    T:(確冀)        S:(恢复播放)
 	"\r\x96""\r\x83""\r\x94""\r\x90",//"STOP",               //13    T:(氨ゎ)            S:(停止)
    "\r\x96""\r\x83""\r\x7f""\r\x90",//"STEP",               //14    T:(˙秈)            S:(单步)
 	"\r\x96""\r\x85""\r\x7f",//"SELECT",             //15    T:(匡拒)            S:(选择)
    //"\r\x8d""\r\x90""\r\x86""\r\x82",//"LOADING",        //16    T:(弄盒)            S:(读碟)
	"\r\x7e""\r\x96""\r\x95",// "READ",           //16    T:(弄盒)            S:(读碟)
    "6"" ""\r\x96""\r\x83""\r\x84""\r\x87""\r\x7e",//"REGION 6",           //17    T:(6 跋)
	"\r\x87""\r\x80""\r\x83""\r\x8a""\r\x8e""\r\x7e",//"ANALOG"    "SPDIF/OFF",             //18    T:(家览)
    "\r\x82""\r\x8c""\r\x87""\r\x81""\r\x95",//"FORWARD",            //19    T:(е秈)
	"\r\x82""\r\x96""\r\x83""\r\x85""\r\x7e",//"BACKWARD",           //20    T:(е癶)
 	"\r\x7e""\r\x7f""\r\x82", //"NEXT",               //21    T:(Ρ >>)
      
     #if defined(SETUP_PASSWORD_GUI)      
        "PASSWD EDIT",      // 22
        #else
            "",                 //22
        #endif        //not use
    "\r\x8b""\r\x81""\r\x83""\r\x95""\r\x82",//"PREV",               //23    T:(Ρ <<)
	
	   "DIR",               //24                       //not use
    "\r\x96""\r\x83""\r\x84""\r\x85",//"RETURN",             //25    T:(垫虫)
     Ch_repx,              				//26
     Ch_rep1,              				//27
     Ch_repd,              				//28    
     
     
     "\r\x82""\r\x7f""\r\x89", //"OFF",                //29    T:(礚)              S:(无)
     "\r\x86""\r\x87""\r\x96""\r\x92""\r\x98",//"MENU",               //30    T:(匡虫)            S:(选单)
     	"SCORE",              //31    T:(だ计)            S:(分数)
     "\r\x8d""\r\x8c""\r\x8f",//"MARK",               //32    T:(癘拘)            S:(记忆)
     "\r\x96""\r\x85""\r\x7e"" ""\r\x96""\r\x85""\r\x7f",//"BROWSE",      //33      
	 "\r\x98""\r\x8e""\r\x89""\r\x98",//"PROG",               //34    T:(絪祘)            S:(编程)
     "SAVING LOGO...",     //35    T:                  S:(画面抓取中)                   
	 "\r\x8b""\r\x87""\r\x8a""\r\x83""\r\x81""\r\x80"" "/*"\r\x8b""\r\x87""\r\x8a""\r\x83""\r\x95""\r\x8c""\r\x96""\r\x82"*/"\r\x8a""\r\x89",//"ALL LG SPK",         //36    T:(家Α1)
     "\r\x7f""\r\x83""\r\x97""\r\x8d""\r\x80""\r\x8e",//"REP",                //37    T:(確)
	 "\r\x82""\r\x87""\r\x95""\r\x87""\r\x98"" ""\r\x7f""\r\x83""\r\x97"" ""\r\x8d""\r\x80""\r\x8e",//"REP DIR",            //38    T:(ヘ魁確)
	 "1"" ""\r\x7f""\r\x83""\r\x97"" ""\r\x8d""\r\x80""\r\x8e",//"REP 1",              //39    T:(虫Ρ確)
	 "\r\x8a""\r\x89""\r\x82"" ""\r\x7f""\r\x83""\r\x97"" ""\r\x8d""\r\x80""\r\x8e",//"REP ALL",            //40    T:(盒確)
 	 "\r\x7f""\r\x83""\r\x97"" ""\r\x8d""\r\x80""\r\x8e"" ""\r\x8a""\r\x86""\r\x7f",//"REP CANCEL",         //41    T:(確)
     "\r\x8b""\r\x87""\r\x8e""\r\x86""\r\x95"/*"\r\x8b""\r\x87""\r\x8a""\r\x83""\r\x95""\r\x8c""\r\x96""\r\x82"*/" ""\r\x8a""\r\x89",//"ALL SM SPK",         //42    T:(家Α2)
     "8"" ""\r\x8b""\r\x87""\r\x96""\r\x80""\r\x83""\r\x7f""\r\x8c",            //43     //"ADULT",            //43
     "7 NC-17",            //44    T:(虫Ρ冀)
     "\r\x8a""\r\x7e"" ""\r\x88""\r\x8a",//"GOTO",               //45    T:(穓)
 	 "\r\x8a""\r\x87""\r\x8a""\r\x94"" ""\r\x7e""\r\x8a""\r\x8a",//"MUTE",               //46    T:(繰)
	 "\r\x8a""\r\x7e""\r\x8c""\r\x97"" ""\r\x83""\r\x8e""\r\x83""\r\x8c",//"MOHO L",             //47    T:(オ羘笵)
     "\r\x8d""\r\x87""\r\x8c""\r\x87"" ""\r\x83""\r\x8e""\r\x83""\r\x8c",//"MOHO R",             //48    T:(羘笵)
	 "\r\x83""\r\x7e""\r\x96""\r\x83""\r\x8f",//"STEREO",             //49    T:(ミ砰羘)
        "DEMUTE",                   //50                   //50    //not use

     "\r\x87""\r\x85",// "LIVE",               //51    T:
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
     "\r\x8a""\r\x87""\r\x8a""\r\x94"" ""\r\x7e""\r\x8a""\r\x8a""-""\r\x8a""\r\x8b""\r\x7f", //"DEMUTE",                           //52    //not use
#endif
     "\r\x8b""\r\x87""\r\x7f""\r\x96""\r\x83""\r\x90""\r\x8c",/*"\r\x8b""\r\x87""\r\x8a""\r\x83""\r\x95""\r\x8c""\r\x96"*/// "MIXED SPK",   "MIXED"       //53    T:(家Α3)
       OS_ICON_CDROM,        //54     
     
     "\r\x8d""\r\x8c""\r\x84", //"TIME",               //55    T:(丁)            S:(时间)
       #if defined(SHOW_MP4_INIT_STR)    
        "INITIALIZING...",                 //56 
#else
        "",                   //56    //not use
#endif
     "\r\x8b""\r\x83""\r\x84",//"ZOOM",               //57    T:(糴)            S:(放宽)

       #ifdef RECORD_KEY
		#ifdef NINTAUS_OSD_STR    
           "PLEASE PRESS RECORD KEY TO PLAY IT.",
     #else
		"MEM KEY:JUMP TO THE SAVED POINT",//58
      #endif
#elif defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                   //58    //not use
#endif     
      OS_ICON_LANG,         //59      
         
      "\r\x82""\r\x8c""\r\x81""\r\x95""\r\x82", //"INTRO",              //60    T:(苯磞)            S:(扫描)
	 "\r\x81""\r\x8e"/*"\r\x83""\r\x7e""\r\x96""\r\x8f"*/,//"SRND",//"SURROUND",           //61    T:(吏露)            S:(环绕)
	 "PBC",                //62
#ifdef RECORD_KEY
       #ifdef NINTAUS_OSD_STR    
           "IT WILL BE AUTO PLAYED AFTER 6S.",
     #else
		"OTHER KEY:PLAY FROM BEGINNING",  //63
          #endif
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "",            //63    T:(抖冀)
#endif     
    
     "RAND CANCEL",       //64    T:(繦诀冀)    S:(随即播放取消)
     "\r\x8f""\r\x7e""\r\x7f",//"BASS MODE",          //65    T:(家Α)

          "",                //66

     "\r\x8a""\r\x7e"" ""\r\x96""\r\x83""\r\x84""\r\x85",//"REPEAT A-",          //67    T:(確A-)          S:(重复 A	)
     "PC-VGA",               //"PC-VGA",           //68
     "\r\x8a""\r\x7e"" ""\r\x96""\r\x83""\r\x84""\r\x85"" ""A-B",//"REPEAT A-B",         //69    T:(確A-B)	      S:(重复播放A-B)
	 "AB"" ""\r\x8a""\r\x8c""\r\x7f",//"A-B CANCEL",         //70    T:(確)        S:(A-B取消)
	 "PRG""\r\x8a""\r\x8c""\r\x7f", //"PRG CANCEL",         //71    T:(絪胆)            S:(编程取消)
  	 "",                   //72
#ifdef ONE_KEY_PASS
		"ONE KEY PLAY",      //73
#else
        "",            //73    T:(璣粂)            S:(英文)
#endif
      OS_ICON_VCD,          //74       
     
      "LIGHT MUSIC",                   //75    
        "ELECTRON",                   //76   
      
        "CVBS",//OS_ICON_MP3,          //77
        OS_ICON_CDDA,         //78
#ifdef NINTAUS_OSD_STR   
        "48KHZ",                   //79    //not use
        "96KHZ",                   //80    //not use
        "192KHZ",                   //81    //not use
#else
        "48K",                   //79    //not use
        "96K",                   //80    //not use
        "192K",                   //81    //not use
#endif
     "\r\x82""\r\x8a""\r\x90""\r\x8c""\r\x8a"" ""\r\x8b""\r\x83""\r\x84",//"ZOOM UP",            //82    T:(礶簿)        S:(放大上)
	 "\r\x82""\r\x86""\r\x8c""\r\x8a"" ""\r\x8b""\r\x83""\r\x84",//"ZOOM DOWN",          //83    T:(礶簿)        S:(放大下)
     "\r\x82""\r\x8a""\r\x7e""\r\x8c""\r\x97"" ""\r\x8b""\r\x83""\r\x84", //"ZOOM LEFT",          //84    T:(礶オ簿)        S:(放大左)
     "\r\x82""\r\x8e""\r\x87""\r\x8c""\r\x87"" ""\r\x8b""\r\x83""\r\x84",//"ZOOM RIGHT",         //85    T:(礶簿)        S:(放大右)
	 "\r\x93""\r\x83""\r\x96""\r\x90",//"CH",                 //86    T:(彻竊)            S:(章节)
     "\r\x81""\r\x82",//"ECHO",               //87    T:(睼臫)            S:(混响)
	 "TT",                 //88    T:(夹肈)            S:(标题)
	 "\r\x96""\r\x81""\r\x86",//"BAND",               //89    T:(繵眯)
	 "\r\x82""\r\x8c""\r\x94""\r\x83""\r\x90",//"VOL",                //90    T:(秖)            S:(音量)
     "DOWN SAMPLE",        //91    //not use
   
	"\r\x85""\r\x98""\r\x92""\r\x8c",//"KEY",                //92    T:(秸)            S:(音调)
#ifdef P_SCAN_ONLY_CHG_INT_MODE
		"CVBS",            //93
		#else
        "S-VIDEO",            //93
        #endif
    "9FRAME_1",         //94    T:(虫Ρ礶)      S:(单曲九画面)
    "\r\x87""\r\x86""\r\x8c""\r\x83""\r\x86""\r\x83""\r\x7e"" ""L",//"AUTO L",             //95    T:(笆钡佰オ)      S:(自动接唱左)
    "\r\x87""\r\x86""\r\x8c""\r\x83""\r\x86""\r\x83""\r\x7e"" ""R",  //"AUTO R",             //96    T:(笆钡佰)      S:(自动接唱右)
       "LOW",                //97    // LOW
	"SEQ PLAY",           //98    T:(抖冀)        S:(顺序播放)

    "\r\x86""\r\x87""\r\x96""\r\x92""\r\x98"" ""\r\x8d""\r\x80""\r\x8e",//"MENU PLAY",          //99    T:(垫虫冀)        S:(菜单播放)
#ifdef DIV_GOTO_DISPLAY
		"DISC TIME",          //100
#else
        "LFE OUT",            //100
#endif


#if defined(NINTAUS_OSD_STR)
	"UP-DOWN",                        //101
	"LEFT-RIGHT",                     //102         
#elif defined(SHOW_STANDBY_TIMER)
	OS_VFD_TIME_NUM,		//101
	"TIMER SETUP",			//102              
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102              
#else
        "STANDARD",           //101
        "ENHANCE",            //102
#endif
       
	 "MEDIUM",             //103   // MEDIUM
	 "PRG"" ""\r\x8d""\r\x80""\r\x8e",           //104   T:(絪导僵)
	 "\r\x82""\r\x83""\r\x7f""\r\x80",//"HIGH",               //105   // HIGH
     "DYNAMIC RANGE",      //106
	  OS_ICON_DVD,          //107 
      
      "OSD"" ""\r\x98""\r\x92""\r\x97",//"OSD LANGUAGE",       //108   T:(礶陪ボ粂ē)    S:(画面显示语言)
       OS_ICON_SUBT,         //109
	"\r\x82""\r\x87""\r\x84""\r\x87""\r\x83""\r\x8a""\r\x86"" ""\r\x80""\r\x83""\r\x8f",//"TV TYPE",		      //110   T:(辊礶ゑㄒ)    S:(屏幕画面比例)
	"\r\x82""\r\x87""\r\x84""\r\x87""\r\x83""\r\x8a""\r\x86"" ""\r\x98""\r\x89""\r\x96""\r\x90""\r\x8c", //"TV SYSTEM",		  //111   T:(筿跌诀Α)      S:(电视机制式)
	"\r\x86""\r\x87""\r\x96""\r\x92""\r\x98""\r\x8c"" ""\r\x98""\r\x7e""\r\x94""\r\x8a",//"EXIT SETUP",         //112   T:(癶砞竚垫虫)    S:(推出设置菜单)
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
	"AUD"" ""\r\x82""\r\x94""\r\x83""\r\x85""\r\x7e", //"AUDIO OUT",          //113   T:(计絏块)        S:(数码输出)
#endif
	"VIDEO",              //114   T:(跌繵块)        S:(视频输出)
	"\r\x82""\r\x8c""\r\x8f""\r\x87""\r\x8f",//"PASSWORD",           //115   T:(盞絏)            S:(密码)
	"\r\x80""\r\x83""\r\x96""\r\x87""\r\x81", //"RATING",             //116   T:()            S:(级别)
    "SPDIF/RAW",          //117   T:(SPDIF/方絏)      S:(SPDIF/源码)
 #ifdef SUPPORT_PALN 
        	"PAL-N",		//118
        #elif defined(PASSWORD_IN_CH)
        "ERROR",
        #else
            "",              //118   T:(AC3 6羘笵)
        #endif

      "SPDIF/PCM",          //119
  
      #ifdef SUPPORT_PALM
			"PAL-M",				//120
        #elif defined(PASSWORD_IN_CH)
        "  OK",
        #else
            "",              //120   T:(AC3 2羘笵)       S:AC3 2声道(not use)
        #endif

#ifdef HANYANG_SETUPMENU   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
#elif defined(EASTECH_DVI)
        "YCbCr", //121
#else
        "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
#endif

        
        
	 "\r\x87""\r\x86""\r\x8c""\r\x83""\r\x86""\r\x83""\r\x7e",//"AUTO",               //122   T:(笆)            S:(自动)
	 "\r\x82""\r\x7f""\r\x89",// "OFF",                //123   T:(闽)              S:(关)
	 
#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
        "TRACK TIME",//124
#else
        "",           //124
#endif     
	"\r\x95""\r\x96""\r\x92", //"CHAPTER",            //125   T:(彻竊)            S:(章节)
	"\r\x90""\r\x86""\r\x95",//"TITLE",              //126   T:(夹肈)            S:(标题)
	  OS_ICON_ANGLE,        //127      
    
      #if defined(HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
    "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif
        OS_16_9,              //129   T:(16:9 --)
        OS_4_3LB,             //130   T:(4:3LB --)
        OS_4_3PS,             //131

       "PAL",                //132
        "NTSC",               //133
        "PAL60",              //134
      "\r\x8b""\r\x87""\r\x96""\r\x80""\r\x83""\r\x7f""\r\x8c""\r\x8a"" ""\r\x7e""\r\x8a",//"NO ADULT",           //135   T:(辅导级)
      "\r\x8b""\r\x87""\r\x81""\r\x8a""\r\x87"" ""\r\x98""\r\x8e""\r\x80""\r\x82", //"KID SAFE",           //136   T:(保留)
      "\r\x8b""\r\x8a""\r\x83""\r\x89"" ""\r\x98""\r\x7e"" ""\r\x82""\r\x7e""\r\x96", //"VIEW ALL",           //137   T:(礚)
   #if defined(SHOW_5_1CH)
            "5.1CH",              //138   T:(5.1羘笵)
        #else
            "6CH SETUP",          //138   T:(6羘笵砞竚)
        #endif
      "SUBWOOFER",          //139   T:(禬)
      "SATURATION",         //140   SATURATION
      "\r\x8a""\r\x90""\r\x92""\r\x82",//"ON",                 //141   T:
        OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
  	  "\r\x82""\r\x95""\r\x8e",//"CLEAR",              //145   T:(睲埃)
        "  T  C",               //146   
        "--:--",              //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "\r\x88""\r\x83""\r\x96""\r\x90",//"EDIT",               //149   T:(絪胯)
#ifdef RECORD_KEY 
        "RECORD RESUME",          //150
#else
        "",//OS_DIR1,              //150
#endif
          
#if defined(NINTAUS_OSD_STR)
	"<<<",
#else
        "",//OS_DIR2,              //151
#endif
        OS_DIR3,              //152
        OS_DIR4,              //153
        "PAL-NC",//OS_DIR5,              //154
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
        "HUE",                //157   HUE
        "PROLOGIC",//"-:--:--",            //158	 
       
        "MOVIE MODE",//"TRACK SEARCH",       //159    
        "MUSIC MODE",//"DISC SEARCH",        //160    
        
  #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//TT:CH",               //161	//not use
        #endif

    #ifdef REMAIN_TIME
            "T",                  //162
        #else
            "",           //162
        #endif

        OS_DIR0,              //163
        "\r\x86""\r\x8f""\r\x96""\r\x86""\r\x8e""\r\x83""\r\x95",//"CONTRAST",           //164   CONTRAST
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
	 "\r\x93""\r\x83""\r\x96""\r\x90",//"CHANNEL",            //168   T:(羘笵)            S:(声道)
 	 "\r\x98""\r\x83""\r\x96""\r\x87""\r\x82""\r\x7f", //"BRIGHTNESS",         //169   BRIGHTNESS
 	 "F/W ID",             //170   T:(硁ン絪絏)        S:(软件编码)
	 "CHIP ID",            //171   T:(絪絏)        S:(芯片编码)
	 "\r\x96""\r\x83""\r\x84""\r\x87""\r\x7e",//"REGION",             //172   T:(跋絏)            S:(区码)
      "MEMORY",//"FUNCTION",           //173  //not use T:(滦弄滦佰)        S:(复读复唱)
        "DYNAMIC",//"MODE",               //174  //not use  T:(家Α)            S:(模式)


		"LIVELY",				//175
		"SHOWPLACE",	   		//176
		"MILD",			   		//177

		"MIC1 VOL",//"COMPARE",            //178   //not use T:(癸ゑ)            S:(对比)
        "MIC2 VOL",//"COUNTER",            //179   //not use T:(滦Ω计)        S:(重复次数)

        "\r\x7e""\r\x7f""\r\x82"" ""\r\x81""\r\x83""\r\x8c""\r\x90",           //180        // "NEXT PAGE" ,
        "\r\x8b""\r\x81""\r\x83""\r\x95"" ""\r\x81""\r\x83""\r\x8c""\r\x90",        //181         //  "PREV PAGE", 
        
#ifdef SUPPORT_IR_I2P_KEY
		"PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
		"",//"NORMAL",             //182   T:(禬丁)        S:(超长时间)
#endif

#ifdef NEWSTYLE_WINDOW
        "PLAYTITLE",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "TITLETIME",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "CHPTIME",//"MANUAL",             //185   T:(も笆)            S:(手动)
#else
        "",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "",//"MANUAL",             //185   T:(も笆)            S:(手动)
#endif

        OS_DIR10,             //186
        OS_DIR11,             //187
      "\r\x82""\r\x90""\r\x92""\r\x83""\r\x82",//"CONCERT",            //188   T:(贾芔)          S:(音乐厅)
	  "\r\x82""\r\x9b""\r\x8f""\r\x8e""\r\x89",//"CHURCH",             //189   T:(毙绑)            S:(教堂)
	  "\r\x87""\r\x7f""\r\x87""\r\x8f""\r\x92",//"PASSIVE",            //190   T:(吏露)            S:(环绕)
	  "\r\x7f""\r\x82""\r\x96",//"WIDE",               //191   T:(糴初)            S:(宽场)
 
#ifdef USER_MPEG_LOGO
		"SELECT LOGO",  		//192
		"MPEG LOGO", 			//193
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)
        "",//OS_STADIUM,           //193   T:(蔨▅繻)
#endif
	 "\r\x96""\r\x84"/*"\r\x9b""\r\x8a""\r\x99""\r\x95""\r\x7e"*/,//"EQ",                 //194   T:(А颗)            S:(均衡)

	 "\r\x87""\r\x86""\r\x96""\r\x81""\r\x8e""\r\x86""\r\x8f",//"STANDARD",           //195   T:(夹非)            S:(标准)
	 "\r\x87""\r\x8f""\r\x7e""\r\x8a""\r\x95", //"CLASSIC",            //196   T:(ㄥ)            S:(古典)
	 "\r\x95""\r\x83""\r\x96",//"ROCK",               //197   T:(穘簎)            S:(摇滚)
	"\r\x84""\r\x7e""\r\x9c""\r\x80",// "JAZZ",               //198   T:(里)            S:(爵士)
	"\r\x92""\r\x83""\r\x92",//"POP",                //199   T:(瑈︽)            S:(流行)
    "\r\x97""\r\x8c""\r\x98""\r\x97""\r\x8c",//"USER", //200
    "ATTRIB",             //201   T:(┦)            S:(个性)
	"\r\x96""\r\x92""\r\x99""       ""\r\x7f""\r\x7e""\r\x8f",//"SF",                 //202   T:(篊秈)            S:(慢进)
        "SB",                 //203   T:(篊癶)            S:(慢退)
        "C",                  //204   //show "C"
     "\r\x96""\r\x8c""\r\x8e""\r\x8f",//"CENTER",              //205   T:(い竚喘羘竟)      S:(中置扬声器)
	"\r\x87""\r\x96""\r\x83""\r\x85""\r\x7e",// "REAR",               //206   T:(吏露喘羘竟)      S:(环绕扬声器)
	"TV-RGB",             //207
	"4 PG13",             //208   T:(辅导级)
	  "\r\x96""\r\x86""\r\x8e""\r\x8f"" ""\r\x82""\r\x9b""\r\x82""\r\x97""\r\x82",//"CENTER DELAY",       //209   T:(い竚┑筐)
	"\r\x87""\r\x96""\r\x83""\r\x82""\r\x7e"" ""\r\x82""\r\x9b""\r\x82""\r\x97""\r\x82",//"REAR DELAY",         //210   T:(吏露┑筐)
    "\r\x87""\r\x8c""\r\x81""\r\x95",   //"FRONT",              //211   T:(玡竚喘羘
	  "VIDEO SETUP",                 //212     //not use   
	   "\r\x98""\r\x83""\r\x81""\r\x85",//"SHARPNESS",          //213	  SHARPNESS
	"\r\x98""\r\x89""\r\x96""\r\x90""\r\x8c"" ""\r\x98""\r\x83""\r\x96""\r\x81""\r\x80""\r\x82",//"SYSTEM SETUP",       //214   T:(╰参砞竚)        S:(系统设置)
	"\r\x8b""\r\x87""\r\x8a""\r\x83""\r\x95""\r\x8c""\r\x96"" ""\r\x98""\r\x83""\r\x96""\r\x81""\r\x80""\r\x82",//"SPEAKER SETUP",      //215   T:(喘羘竟砞竚)      S:(扬声器设置)
	"\r\x83""\r\x87""\r\x81""\r\x83""\r\x7e"" ""\r\x98""\r\x83""\r\x96""\r\x81""\r\x80""\r\x82",//"AUDIO SETUP",        //216   T:(繵砞竚)        S:(音频设置)
	"\r\x8a""\r\x81""\r\x85""\r\x8c"" ""\r\x98""\r\x96""\r\x87""\r\x96""\r\x7f",//"DEFAULT",            //217   T:()          S:(缺省值)
    #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
    #else
        "GRP",                //218   //not use
    #endif
	
	#ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU
        "   MNP   ",
        #else
	"\r\x88""\r\x8f""\r\x8c"" ""\r\x96""\r\x8c""\r\x83""\r\x97",    //219   T:(辊玂臔)      //"SCREEN SAVER",   S:(屏幕保护)           
    #endif
        "TYPE 1",             //220   T:(家Α 1)          S:(模式1)
        "TYPE 2",             //221   T:(家Α 2)          S:(模式2)
        "TYPE 3",             //222   T:(家Α 3)          S:(模式3)


#ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   S:(5保留)
        #endif
        
        "6 R",                //224   S:(限制级)

 #ifdef NOT_SUPPROT_VCD
        "NOT SUPPORTED CD",           //225   S:(错误碟片)
        #else
        "ERR DISC",           //225   S:(错误碟片)
        #endif
	 "\r\x98""\r\x83""\r\x87""\r\x8a""\r\x8b""\r\x87""\r\x80""\r\x87""\r\x81",/*	"\r\x98""\r\x83""\r\x96""\r\x81""\r\x80""\r\x82"*///"DIGITAL SETUP", "DIGITAL"     //226   T:(计絏砞竚)
	#ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
	"\r\x8d""\r\x83""\r\x92""\r\x83""\r\x96""\r\x95""\r\x87""\r\x8c"/*"\r\x98""\r\x83""\r\x96""\r\x81""\r\x80""\r\x82"*/,//"MIC SETUP",   "MIC"       //227   T:(杠旦砞竚)
	"\r\x8d""\r\x83""\r\x92""\r\x83""\r\x96""\r\x95""\r\x87""\r\x8c",//"MIC VOL",            //228   T:(杠旦秖)
	#endif
	"\r\x95""\r\x8f""\r\x87""\r\x81"" ""\r\x96""\r\x84""\r\x85""\r\x97",//"CD RECOVERING",      //229   T:(岿い)     ------------- not use
	"\r\x8b""\r\x89""\r\x85"" ""\r\x80""\r\x83""\r\x96""\r\x81""\r\x97",//"SMART UPGRADE",      //230   T:(醇ど)
    "UPGRADE TO V ",      //231   T:(どΘ)
	"\r\x80""\r\x83""\r\x96""\r\x81""\r\x97",//"UPGRADING",          //232   T:(どい)
    "NOT POWER OFF",      //233   T:(づ闽诀)
	"\r\x96""\r\x83""\r\x84""\r\x7e"" ""0",//"REGION 0",           //234   T:(0 跋)
	"\r\x96""\r\x83""\r\x84""\r\x7e"" ""1",//"REGION 1",           //235   T:(1 跋)
    "\r\x96""\r\x83""\r\x84""\r\x7e"" ""2",//"REGION 2",           //236   T:(2 跋)
    "\r\x96""\r\x83""\r\x84""\r\x7e"" ""3",//"REGION 3",           //237   T:(3 跋)
    "\r\x96""\r\x83""\r\x84""\r\x7e"" " "4",//"REGION 4",           //238   T:(4 跋)
    "\r\x82""\r\x92""\r\x97"" ""\r\x98""\r\x83""\r\x96""\r\x81""\r\x80""\r\x82", //"LANGUAGE SETUP",     //239   T:(粂ē砞竚)
	  
#if defined(NINTAUS_OSD_STR)
	">>>",
#else        
        "",                   //240   //not use
#endif      
	  "\r\x87""\r\x97""\r\x7e""\r\x96"" ""\r\x81""\r\x83""\r\x8c""\r\x90",  // "MAIN PAGE",          //241   T:()
	  "\r\x7f""\r\x83""\r\x7f""\r\x87""\r\x81"" ""\r\x98""\r\x92""\r\x97",//"AUDIO LANG",         //242   T:(繵粂ē)
	  "\r\x98""\r\x83""\r\x87""\r\x7f""\r\x83""\r\x98""\r\x89"" ""\r\x98""\r\x92""\r\x97", //"SUBTITLE LANG",      //243   T:(辊粂ē)
	 "\r\x98""\r\x89""\r\x96""\r\x90""\r\x8c"" ""\r\x98""\r\x92""\r\x97",//"MENU LANG",          //244   T:(垫虫粂ē)
	 "DOWNMIX",            //245   T:(睼家Α)
       "\r\x96""\r\x84""\r\x85""\r\x97",//"RESTORE",            //246   T:(確)
        "LT/RT",              //247
        "VSS",                //248   T:(店览吏露羘)      S:(虚拟环绕声)
        "OP MODE",            //249   T:(块家Α)        S:(输出模式)
        "LINE OUT",           //250   T:(絬隔块)        S:(线路输出)
        "RF REMOD",           //251   T:(RF 秸俱)         S:(RF调整)
    "\r\x83""\r\x8e""\r\x83""\r\x8c""-""\r\x83""\r\x81",//"DUAL MONO",          //252   T:(オ+)           S:(左+右)
    "\r\x83""\r\x8e""\r\x83""\r\x8c"" ""\r\x8f""\r\x95""\r\x87""\r\x8c",//"MIX MONO",           //253   T:(睼羘笵)        S:(混合声道)
   	"\r\x81""\r\x8e""\r\x83""\r\x7e""\r\x96"" ""\r\x8f"" ""\r\x7f""\r\x94""\r\x8c",   //"SURND MODE",         //254   T:(吏露家Α)        S:(环绕模式)
	   "",           //255
 
 
 
 }
 #endif
// HEBRAIC_OSD zhuyf add 2004-05-26

#ifdef USE_ROMANIAN_OSD
//Romanian
{
        "",                                         //0
        "FARA CD",            //"NO DISC",          //1     T:(礚盒)            S:(无碟)
        "INTRARE INVALIDA",   //"INVALID KEY",      //2     T:(眤岿 hand)   S:(您按错了 HAND)
        "TRK",                                      //3     T:(Ρヘ)            S:(曲目)
        OS_ICON_SVCD,                               //4
        "DE-INTERLACE",//"CHINEZA",           //"CHINESE",          //5     T:(簙粂)            S:(中文)
        "DESCHIS",            //"OPEN",             //6     T:()            S:(出仓)
        "INCHIS",             //"CLOSE",            //7     T:(闽)            S:(关仓)
        "REDARE",             //"PLAY",             //8     T:(冀)            S:(播放)
        "REGIUNEA 5",         //"REGION 5",         //9     T:(5 跋)            S:(5区)
        "PAUZA",              //"PAUSE",            //10    T:(既氨)            S:(暂停)
        "ALEATORIU",          //"RANDOM",           //11    T:(繦诀冀)        S:(随即播放)
        "RELUARE",            //"RESUME",           //12    T:(確冀)        S:(恢复播放)
        "STOP",                                     //13    T:(氨ゎ)            S:(停止)
        "PAS",                //"STEP",             //14    T:(˙秈)            S:(单步)
        "SELECTARE",          //"SELECT",           //15    T:(匡拒)            S:(选择)

            "CITESTE",        //"READ",             //16    T:(弄盒)            S:(读碟)

        "REGIUNEA 6",         //"REGION 6",         //17    T:(6 跋)
        "ANALOG",                                   //18    T:(家览)
        "INAINTE",            //"FORWARD",          //19    T:(е秈)
        "INAPOI",             //"BACKWARD",         //20    T:(е癶)
        "URMATORUL",          //"NEXT",             //21    T:(Ρ >>)

        #ifdef ADJ_SIXCH
            "AMPVOL",                           //22
        #else
            "",                                 //22
        #endif

        "PRECEDENT",          //"PREV",             //23    T:(Ρ <<)

        "DIR",                                  //24

        "REVENIRE",           //"RETURN",           //25    T:(垫虫)
        Ch_repx,                                    //26
        Ch_rep1,                                    //27
        Ch_repd,                                    //28
        "OPT",                //"OFF"="OPRIT",      //29    T:(礚)              S:(无)
        "MENU",                                     //30    T:(匡虫)            S:(选单)
        "SCORE",                                    //31    T:(だ计)            S:(分数)
        "MARK",                                     //32    T:(癘拘)            S:(记忆)

        "NAVIGARE",           //"BROWSE",           //33    T:(聅凝)            S:(浏览)
        "PROGRAM",                    //"PROG",             //34    T:(絪祘)            S:(编程)

        "SAVING LOGO...",           //35
        "ALL LG SPK",         //36    T:(家Α1)

        "REPATA",             //"REP",              //37    T:(確)
        "REPETA DIRECTORUL",  //"REP DIR",          //38    T:(ヘ魁確)
        "REPETA 1",           //"REP 1",            //39    T:(虫Ρ確)
        "REPETA TOATE",       //"REP ALL",          //40    T:(盒確)
        "REPETARE ANULATA",   //"REP CANCEL",       //41    T:(確)

        "ALL SM SPK",                               //42    T:(家Α2)
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
        #else// #ifdef HJ_APEX_FIX_SHOW_OSD
        "8 ADULT",                                  //43
        #endif// #ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",                                        //43
        #endif
        "7 NC-17",                                  //44    T:(虫Ρ冀)

        "MEGI LA",            //"GOTO",             //45    T:(穓)
        "MUTING",             //"MUTE",             //46    T:(繰)
#ifdef SDRAM_16Mb_Mode
        "MONO STA.",          //"MONO L",           //47    T:(オ羘笵)
        "MONO DRE.",          //"MONO R",           //48    T:(羘笵)
#else//SDRAM_16Mb_Mode        
        "MONO STANGA",        //"MONO L",           //47    T:(オ羘笵)
        "MONO DREAPTA",       //"MONO R",           //48    T:(羘笵)
#endif//SDRAM_16Mb_Mode
        "STEREO",                                   //49    T:(ミ砰羘)
        "MUTE CANCEL",                              //50
        "LIVE",                                     //51    T:
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "TEST TONE",                                //52
#endif
        "MIXED SPK",                                //53    T:(家Α3)
        OS_ICON_CDROM,                              //54
        "BALANCE L",//"TIMP",                 //"TIME",             //55    T:(丁)            S:(时间)
        "TV VIDEO",                                 //56    //nono 3-2-26 18:36
        "ZOOM",                                     //57    T:(糴)            S:(放宽)
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                    //58    //not use
#endif
        OS_ICON_LANG,                               //59

        "INTRODUCERE",        //"INTRO",            //60    T:(苯磞)            S:(扫描)
        "SRND",//"SURROUND",                                //61    T:(吏露)            S:(环绕)
        "PBC",                                      //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "BALANCE R",//"PBC OPRIT",        //"PBC OFF",          //63    T:(抖冀)
#endif
        "ALEATORIU ANULAT",   //"RAND CANCEL",      //64    T:(繦诀冀)    S:(随即播放取消)
        "BASS MODE",                                //65    T:(家Α)

        "AMP FRONT",                            //66

        "REPETA A-",          //"REPEAT A-",        //67    T:(確A-)          S:(重复 A   )
        "PC-VGA",                                           //68
        "REPETA A-B",         //"REPEAT A-B",       //69    T:(確A-B)       S:(重复播放A-B)
        "ANULAT AB",          //"A-B CANCEL",       //70    T:(確)        S:(A-B取消)
        "ANULAT PRG",         //"PRG CANCEL",       //71    T:(絪胆)            S:(编程取消)
        "",                                         //72
        #ifdef MACROVISION_SHOW_FW_VERSION
        MCRV_STR,//
        #else
        "",//"ENGLEZA",           //"ENGLISH",          //73    T:(璣粂)            S:(英文)
        #endif
        OS_ICON_VCD,                                //74
        "NTSC-J",                                   //75    //NTSC-J
        "",                                         //76    //not use
        "CVBS",//OS_ICON_MP3,                               //77
        OS_ICON_CDDA,                               //78
        "48K",                   //79    //not use
        "96K",                   //80    //not use
        "192K",                   //81    //not use
        "CRESTE ZOOM",        //"ZOOM UP",          //82    T:(礶簿)        S:(放大上)
        "SCADE ZOOM",         //"ZOOM DOWN",        //83    T:(礶簿)        S:(放大下)
        "ZOOM STANGA",        //"ZOOM LEFT",        //84    T:(礶オ簿)        S:(放大左)
        "ZOOM DREAPTA",       //"ZOOM RIGHT",       //85    T:(礶簿)        S:(放大右)
        "CA",                 //"CANAL"="CH",               //86    T:(彻竊)            S:(章节)

        "ECHO",                                     //87    T:(睼臫)            S:(混响)
        "TT",                 //"TT"="TITLU",       //88    T:(夹肈)            S:(标题)
        "BAND",                                         //89
        "VOLUM",              //"VOL",              //90    T:(秖)            S:(音量)
        "DOWN SAMPLE",  //91    //not use
        "TASTA",              //"KEY",              //92    T:(秸)            S:(音调)
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        "CADRE 9-1",          //"9FRAME_1",         //94    T:(虫Ρ礶)      S:(单曲九画面)
        "AUTO STANGA",        //"AUTO L",           //95    T:(笆钡佰オ)      S:(自动接唱左)
        "AUTO DREAPTA",       //"AUTO R",           //96    T:(笆钡佰)      S:(自动接唱右)
        "LOW",                                          //97

            "REDARE SECVENTA",//"SEQ PLAY",         //98    T:(抖冀)        S:(顺序播放)

        "MENU REDARE",        //"MENU PLAY",        //99    T:(垫虫冀)        S:(菜单播放)
        "LFE OUT",                                  //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else        
        "STANDARD",                                 //101
        "ENHANCE",                                  //102
#endif        
        "MEDIUM",                                           //103
        "REDARE PROGR.",      //"PRG PLAY",         //104   T:(絪导僵)          S:(编程播放)
        "HIGH",                                         //105
        "DOM DINAMIC",        //"DOMENIU DINAMIC"="DYNAMIC RANGE",    //106
        OS_ICON_DVD,                                //107
        "LIMBA OSD",          //"OSD LANGUAGE",     //108   T:(礶陪ボ粂ē)    S:(画面显示语言)
        OS_ICON_SUBT,                               //109
        "TIP TV",             //"TV TYPE",          //110   T:(辊礶ゑㄒ)    S:(屏幕画面比例)
        "SISTEM TV",          //"TV SYSTEM",        //111   T:(筿跌诀Α)      S:(电视机制式)
        "IESIRE SETUP",       //"EXIT SETUP",       //112   T:(癶砞竚垫虫)    S:(推出设置菜单)

#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "IESIRE AUDIO",       //"AUDIO OUT",        //113   T:(计絏块)        S:(数码输出)
#endif
        "VIDEO",                                    //114   T:(跌繵块)        S:(视频输出)
        "PAROLA",             //"PASSWORD",         //115   T:(盞絏)            S:(密码)
        "TIP DE FILM",        //"RATING",           //116   T:()            S:(级别)
        "SPDIF/ORIGIN",       //"SPDIF/ORIGINAL"="SPDIF/RAW",        //117   T:(SPDIF/方絏)      S:(SPDIF/源码)

#if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
#else
        "AMP CENTER",                           //118
#endif 

        "SPDIF/PCM",                                //119

//        "AMP SUBWOOFER",                      //120
#ifdef SUPPORT_PALM
        "PAL-M",                //120
#else
        "AMP SUBWOOFER",           //120
#endif
#ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
#elif defined(EASTECH_DVI)
        "YCbCr",//121
#else
        "INTERLACE-YUV",                                    //121   T:(跌繵だ秖)        S:(视频分量)
#endif//SHOW_YCbCr


        "AUTO",                                     //122   T:(笆)            S:(自动)
        "OPRIT",              //"OFF",              //123   T:(闽)              S:(关)
        "",//"TM/CH/TL",                                //124
        "CAPITOL",            //"CHAPTER",          //125   T:(彻竊)            S:(章节)
        "TITLU",              //"TITLE",            //126   T:(夹肈)            S:(标题)
        OS_ICON_ANGLE,                              //127
      #if defined(HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif
        OS_16_9,                                    //129   T:(16:9 --)
        OS_4_3LB,                                   //130   T:(4:3LB --)
        OS_4_3PS,                                   //131
        "PAL",                                      //132
        "NTSC",                                     //133
        "PAL60",                                    //134

        #ifdef RATING_8
            "3 PG",                                 //135   T:(level 3)
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else
            "2",                                    //136   T:(level 2)
            "1 G",                                  //137   T:(level 1)
            #endif
        #else
            "NU ADULTI",      //"NO ADULT",         //135   T:(辅导级)
            "SIGUR PEN COP",  //"SIGUR PENTRU COPII"="KID SAFE",,//"KID SAFE",      //136   T:(保留)
            "VIZIBILE TOA", //"VIZIBILE TOATE"="VIEW ALL",         //137   T:(礚)
        #endif


        #if defined(HIMAGE_DMA5800) //gerry for huajia 3-3-11 11:14
            "BASS VOL",                             //138
        #elif   defined(SHOW_5_1CH)
            "5.1CH",                                //138   T:(5.1羘笵)
        #else
            "INSTALARE CANAL 6",//"6CH SETUP",      //138   T:(6羘笵砞竚)
        #endif

        "SUBWOOFER",                                //139   T:(禬)
        "SATURATION",         //140   SATURATION
        "PORNIT",             //"ON",               //141   T:
        OS_DOBLY,                                   //142
        Ch_clock,                                   //143
        Ch_speaker,                                 //144
        "STERGERE",           //"CLEAR",            //145   T:(睲埃)
        //"  T  C",                                 //146
        //"--:--",                                  //147
        "  T  C",                                       //146
        "--:--",                                //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "EDITARE",            //"EDIT",             //149   T:(絪胯)
        
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42,(Romanian).     
        "LIMBA DE SUB2",       //150
#else
        "",//OS_DIR1,                                   //150
#endif   
        
        "",//OS_DIR2,                                   //151
        OS_DIR3,                                    //152
        OS_DIR4,                                    //153
        "PAL-NC",//OS_DIR5,                                     //154
        OS_LOCK,                                    //155   T:---- L
        OS_UNLOCK,                                  //156   T:---- U
        "HUE",                //157   HUE
        "PROLOGIC",//"-:--:--",                                 //158

        "MOVIE MODE",//"CAUTARE TITLU",   //"TRACK SEARCH",     //159   T:(虫Ρ穓)        S:(单曲搜索)
        "MUSIC MODE",//"CAUTARE CD",          //"DISC SEARCH",      //160   T:(羆盒穓)        S:(全碟搜索)
        
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//"TT:CH",                                   //161
        #endif

        "T",                  //162

        OS_DIR0,                                    //163
        "CONTRAST",           //164   CONTRAST
        OS_DIR7,                                    //165
        OS_DIR8,                                    //166
        OS_DIR9,                                    //167
        "CANAL",              //"CHANNEL",          //168   T:(羘笵)            S:(声道)
        "BRIGHTNESS",         //169   BRIGHTNESS
        "F/W ID",                                   //170   T:(硁ン絪絏)        S:(软件编码)
        "CHIP ID",                                  //171   T:(絪絏)        S:(芯片编码)

        "REGIUNE",            //"REGION",           //172   T:(跋絏)            S:(区码)
        "MEMORY",//"FUNCTIE",             //"FUNCTION",         //173   T:(滦弄滦佰)        S:(复读复唱)
        "DYNAMIC",//"MOD",                //"MODE",             //174   T:(家Α)            S:(模式)



        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

        "MIC1 VOL",//"COMPARARE",         //"COMPARE",          //178   T:(癸ゑ)            S:(对比)
        "MIC2 VOL",//"NUMARATOR",         //"COUNTER",          //179   T:(滦Ω计)        S:(重复次数)
//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU) 
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181 
#else
        "PREV CHAPTER",                             //180   S:(上一章节)
        "NEXT CHAPTER",                             //181   S:(下一章节)
#endif
            //"NIVEL",            //"LEVEL",            //180   T:魁家Α          S:(录音模式)
            //"INALTE",           //"HIGH",             //181   T:蔼珇借            S:(高品质)
#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",                                  //182   T:(禬丁)        S:(超长时间)
#endif
        "",//"SUPER",                                   //183   T:(禬蔼珇借)        S:(超高品质)
        "",//"OPERATING",                               //184   T:(秸竊よΑ)        S:(调节方式)
        "",//"MANUAL",                                  //185   T:(も笆)            S:(手动)
        OS_DIR10,                                   //186
        OS_DIR11,                                   //187
        "CONCERT",                                  //188   T:(贾芔)          S:(音乐厅)

        "BISERICA",           //"CHURCH",           //189   T:(毙绑)            S:(教堂)
        "PASIV",              //"PASSIVE",          //190   T:(吏露)            S:(环绕)
        "WIDE",                                     //191   T:(糴初)            S:(宽场)
//        "",//"AMFITEATRU",          //"AMPHITH",          //192   T:(蛾粿初)          S:(圆剧场)
//        "",//"STADION",             //"STADIUM",          //193   T:(蔨▅繻)          S:(体育场)
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192   
        "MPEG LOGO",            //193   
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "EQ",                                       //194   T:(А颗)            S:(均衡)
        "STANDARD",                                 //195   T:(夹非)            S:(标准)
        "CLASIC",             //"CLASSIC",          //196   T:(ㄥ)            S:(古典)
        "ROCK",                                     //197   T:(穘簎)            S:(摇滚)
        "JAZZ",                                     //198   T:(里)            S:(爵士)
        "POP",                                      //199   T:(瑈︽)            S:(流行)
        "UTILIZATOR",         //"USER",             //200   T:(┦)            S:(个性)
        "ATTRIB",                                   //201   T:(┦)            S:(个性)
        "SF",                                       //202   T:(篊秈)            S:(慢进)
        "SB",                                       //203   T:(篊癶)            S:(慢退)

        "C",                                        //204   //show "C"

        "DIFUZOR CENTR",      //"DIFUZOR CENTRU"="CENTER",           //205   T:(い竚喘羘竟)      S:(中置扬声器)
        "DIFUZOR SPATE",      //"REAR",             //206   T:(吏露喘羘竟)      S:(环绕扬声器)

        "TV-RGB",             //207

        "4 PG13",                                   //208   T:(辅导级)

        "INT DI CENTRU",   //"INTARZIERE DIFUZOR CENTRU"="CENTER DELAY",     //209   T:(い竚┑筐)
        "INT DI SPATE",   //"INTARZIERE DIFUZOR SPATE"="REAR DELAY",         //210   T:(吏露┑筐)

        "DIFUZOR FATA",       //"FRONT",            //211   T:(玡竚喘羘竟)
        "VIDEO SETUP",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS

        "INSTALARE SISTEM",   //"SYSTEM SETUP",     //214   T:(╰参砞竚)        S:(系统设置)
        "INSTALARE DIFUZOARE",//"SPEAKER SETUP",    //215   T:(喘羘竟砞竚)      S:(扬声器设置)
        "INSTALARE AUDIO",    //"AUDIO SETUP",      //216   T:(繵砞竚)        S:(音频设置)
        "DEFECT",             //"DEFAULT",          //217   T:()          S:(缺省值)
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "GRP",                                      //218   //not use
        #endif
        #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU
        "   MNP   ",
        #else
        "PROTECT ECRAN",      //"PROTECTIE ECRAN"="SCREEN SAVER",     //219   T:(辊玂臔)        S:(屏幕保护)
        #endif
        "TIP 1",              //"TYPE 1",           //220   T:(家Α 1)          S:(模式1)

        #if defined(HIMAGE_DMA5800) //gerry for huajia 3-3-11 11:14
            "TREBLE VOL",           //221
            "MAIN VOL",           //222
        #else
            "TIP 2",              //"TYPE 2",       //221   T:(家Α 2)          S:(模式2)
            "TIP 3",              //"TYPE 3",       //222   T:(家Α 3)          S:(模式3)
        #endif

        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                                        //223   S:(5保留)
        #endif
        
        "6 R",                                      //224   S:(限制级)

        #ifdef NOT_SUPPROT_VCD
        "NOT SUPPORTED CD",                         //225   S:(错误碟片)
        #else
        "EROARE CD",              //"ERR DISC",     //225   S:(错误碟片)
        #endif

        "INSTALARE DIGITALA",     //"DIGITAL SETUP",//226   T:(计絏砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "INSTALARE MIC",      //"INSTALARE MICROFON"="MIC SETUP",    //227   T:(杠旦砞竚)
        "VOLUM MIC",          //"VOLUM MICROFON"="MIC VOL",      //228   T:(杠旦秖)
        #endif
        "RECUPERARE CD",          //"CD RECOVERING",//229   T:(岿い)
        "UPGRADE SMART",          //"SMART UPGRADE",//230   T:(醇ど)
        "UPGRADE LA V",           //"UPGRADE TO V ",//231   T:(どΘ)
        "UPGRADARE",              //"UPGRADING",          //232   T:(どい)

        "NU OPRESTE",             //"NOT POWER OFF",//233   T:(づ闽诀)
        "REGIUNE 0",              //"REGION 0",     //234   T:(0 跋)
        "REGIUNE 1",              //"REGION 1",     //235   T:(1 跋)
        "REGIUNE 2",              //"REGION 2",     //236   T:(2 跋)
        "REGIUNE 3",              //"REGION 3",     //237   T:(3 跋)
        "REGIUNE 4",              //"REGION 4",     //238   T:(4 跋)
        "CONFIGURARE LIMBA",      //"LANGUAGE SETUP",     //239   T:(粂ē砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
	"DISPLAY",            //240
	#else
        "",                                         //240   //not use
        #endif
        "PAGINA PRINCI",          //"PAGINA PRINCIPALA"="MAIN PAGE",    //241   T:()
#ifdef BBK_DVD
        /*"LIMBA AUDIO",              //"AUDIO LANG",   //242   T:(繵粂ē)*/
        "AUDIO",              //"AUDIO LANG",   //242   T:(繵粂ē) axel 2004/1/27 03:58 eliminate "LANG"
        /*"LIMBA DE SUB",             //"LIMBA DE SUBTITRARE"="SUBTITLE LANG",      //243   T:(辊粂ē)*/
        "DE SUB",             //"LIMBA DE SUBTITRARE"="SUBTITLE LANG",      //243   T:(辊粂ē)
#else
        "LIMBA AUDIO",            //"AUDIO LANG",   //242   T:(繵粂ē)
        "LIMBA DE SUB",           //"LIMBA DE SUBTITRARE"="SUBTITLE LANG",      //243   T:(辊粂ē)
#endif
        "LIMBA MENU",             //"MENU LANG",    //244   T:(垫虫粂ē)
        "MOD MIXT",               //"DOWNMIX",      //245   T:(睼家Α)
        "RESTABILIRE",                //"RESTORE",      //246   T:(確)
        "LT/RT",                                    //247
        "VSS",                                      //248   T:(店览吏露羘)      S:(虚拟环绕声)
        "MOD OP",                 //"OP MODE",      //249   T:(块家Α)        S:(输出模式)
        "IESIRE",                 //"LINE OUT",     //250   T:(絬隔块)        S:(线路输出)
        "RF REMOD",                                 //251   T:(RF 秸俱)         S:(RF调整)
        "MONO DUBLU",             //"DUAL MONO",    //252   T:(オ+)           S:(左+右)
        "MONO MIXT",              //"MIX MONO",     //253   T:(睼羘笵)        S:(混合声道)
        "MOD SURROUND",           //"SURND MODE",   //254   T:(吏露家Α)        S:(环绕模式)
#ifdef KSD_DVD
        "PRESS PLAY BUTTON TO CONTINUE",        //255   T:              S:请按播放键继续
#else
        "PRE STOP",                                 //255   T:                  S:(准停止)
#endif

//=================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER
},
#endif//#ifdef USE_ROMANIAN_OSD

#ifdef USE_TURKISH_OSD
//Turkish
{
        "",                                         //0
        "D""\x005""SK YOK",            //"NO DISC",         //1     T:(礚盒)            S:(无碟)
        "HATALI G""\x005""R""\x005""\x002",   //"INVALID KEY",      //2     T:(眤岿 hand)   S:(您按错了 HAND)
        "TRK",                                      //3     T:(Ρヘ)            S:(曲目)
        OS_ICON_SVCD,                               //4
        "DE-INTERLACE",//"CHINEZA",           //"CHINESE",          //5     T:(簙粂)            S:(中文)
        "A""\xc7""IK",            //"OPEN",             //6     T:()            S:(出仓)
        "KAPALI",             //"CLOSE",            //7     T:(闽)            S:(关仓)
        "BA""\x002""LA",              //"PLAY",             //8     T:(冀)            S:(播放)
        "B""\xd6""LGE"" 5",       //"REGION 5",         //9     T:(5 跋)            S:(5区)
        "DURAKLA",            //"PAUSE",            //10    T:(既氨)            S:(暂停)
        "RASTGELE",       //"RANDOM",           //11    T:(繦诀冀)        S:(随即播放)
        "BA""\x002""LA",              //"RESUME",           //12    T:(確冀)        S:(恢复播放)
        "DUR",                                      //13    T:(氨ゎ)            S:(停止)
        "ADIM",               //"STEP",             //14    T:(˙秈)            S:(单步)
        "SE""\xc7",       //"SELECT",           //15    T:(匡拒)            S:(选择)

            "OKUYOR",         //"READ",             //16    T:(弄盒)            S:(读碟)

        "B""\xd6""LGE"" 6",       //"REGION 6",         //17    T:(6 跋)
        "ANALOG",                                   //18    T:(家览)
        "\x005""LER""\x005",              //"FORWARD",          //19    T:(е秈)
        "GER""\x005",             //"BACKWARD",         //20    T:(е癶)
        "SONRAK""\x005",          //"NEXT",             //21    T:(Ρ >>)

            #ifdef ADJ_SIXCH
                "AMPVOL",                           //22
            #else
                "",                                 //22
            #endif

        "\xd6""NCEK""\x005",          //"PREV",             //23    T:(Ρ <<)

        "DIR",                                  //24

        "GER""\x005""D""\xd6""N""\xdc""\x002",            //"RETURN",           //25    T:(垫虫)
        Ch_repx,                                    //26
        Ch_rep1,                                    //27
        Ch_repd,                                    //28
        "YOK",                //"OFF"="KAPALI",     //29    T:(礚)              S:(无)
        "MEN""\xdc",                                    //30    T:(匡虫)            S:(选单)
        "SKOR",                                     //31    T:(だ计)            S:(分数)
        "\x05""\x02""AR", //"MARK",             //32    T:(癘拘)            S:(记忆)

        "BROWSE",             //"BROWSE",           //33    T:(聅凝)            S:(浏览)
        "PROG",                   //"PROG",             //34    T:(絪祘)            S:(编程)

        "SAVING LOGO...",           //35
        "ALL LG SPK",         //36    T:(家Α1)

        "TEKRAR",             //"REP",              //37    T:(確)
        "TEKRAR DIR",  //"REP DIR",          //38    T:(ヘ魁確)
        "TEKRAR 1",           //"REP 1",            //39    T:(虫Ρ確)
        "T""\xdc""M""\xdc"" TEKRAR",          //"REP ALL",          //40    T:(盒確)
        "TEKRAR ""\x005""PTAL",   //"REP CANCEL",       //41    T:(確)

        "ALL SM SPK",                               //42    T:(家Α2)
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
        #else// #ifdef HJ_APEX_FIX_SHOW_OSD
        "8 ADULT",                                  //43
        #endif// #ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",                                        //43
        #endif
        "7 NC-17",                                  //44    T:(虫Ρ冀)

        "G""\x005""T",            //"GOTO",             //45    T:(穓)
        "SES KAPALI",             //"MUTE",             //46    T:(繰)
        "MONO SOL",       //"MONO L",           //47    T:(オ羘笵)
        "MONO SA""\x003",         //"MONO R",           //48    T:(羘笵)

        "STEREO",                                   //49    T:(ミ砰羘)
        "MUTE CANCEL",            //"HALL",                 //50
        "CANLI",                    //"LIVE",                                       //51    T:
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "TEST TONE",                                //52
#endif
        "MIXED SPK",                                //53    T:(家Α3)
        OS_ICON_CDROM,                              //54
        "BALANCE L",//"TIMP",                 //"TIME",             //55    T:(丁)            S:(时间)
        "TV VIDEO",                                 //56    //nono 3-2-26 18:36
        "ZOOM",                                     //57    T:(糴)            S:(放宽)
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                    //58    //not use
#endif
        OS_ICON_LANG,                               //59


        "INTRO",                    //"INTRO",            //60    T:(苯磞)            S:(扫描)
        "SRND",//"SURROUND",                                //61    T:(吏露)            S:(环绕)
        "PBC",                                      //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "BALANCE R",//"PBC OPRIT",        //"PBC OFF",          //63    T:(抖冀)
#endif
        "RAND ""\x005""PTAL",     //"RAND CANCEL",      //64    T:(繦诀冀)    S:(随即播放取消)
        "BASS MODE",                                //65    T:(家Α)

        "AMP FRONT",                            //66

        "A TEKRAR",       //"REPEAT A-",        //67    T:(確A-)          S:(重复 A   )
        "PC-VGA",                                           //68
        "A-B TEKRAR",         //"REPEAT A-B",       //69    T:(確A-B)       S:(重复播放A-B)
        "A-B""\x005""PTAL",       //"A-B CANCEL",       //70    T:(確)        S:(A-B取消)
        "PRG""\x005""PTAL",       //"PRG CANCEL",       //71    T:(絪胆)            S:(编程取消)
        "",                                         //72
        #ifdef MACROVISION_SHOW_FW_VERSION
        MCRV_STR,//
        #else
        "",//"\x005""NG""\x005""L""\x005""ZCE",           //"ENGLISH",          //73    T:(璣粂)            S:(英文)
        #endif
        OS_ICON_VCD,                                //74
        "NTSC-J",                                   //75    //NTSC-J
        "",                                         //76    //not use
        "CVBS",//OS_ICON_MP3,                               //77
        OS_ICON_CDDA,                               //78
        "48K", //"",                   //79    //not use
        "92K", //"",                   //80    //not use
        "192K", //"",                   //81    //not use
        "YUKARI ZOOM",        //"ZOOM UP",          //82    T:(礶簿)        S:(放大上)
        "A""\x002""A""\x003""I ZOOM",         //"ZOOM DOWN",        //83    T:(礶簿)        S:(放大下)
        "SOL ZOOM",       //"ZOOM LEFT",        //84    T:(礶オ簿)        S:(放大左)
        "SA""\x003"" ZOOM",       //"ZOOM RIGHT",       //85    T:(礶簿)        S:(放大右)
        "KN",                 //"CANAL"="CH",               //86    T:(彻竊)            S:(章节)

        "EKO",                                      //87    T:(睼臫)            S:(混响)
        "BB",                 //"TT"="TITLU",       //88    T:(夹肈)            S:(标题)
        "BAND",                                         //89    //not use
        "SES",            //"VOL",              //90    T:(秖)            S:(音量)
        "DOWN SAMPLE",  //91    //not use
        "TU""\x002",              //"KEY",              //92    T:(秸)            S:(音调)
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        "9RES""\x005""_1",        //"9FRAME_1",         //94    T:(虫Ρ礶)      S:(单曲九画面)
        "SES SOL",                //"AUTO L",           //95    T:(笆钡佰オ)      S:(自动接唱左)
        "SES SA""\x003",          //"AUTO R",           //96    T:(笆钡佰)      S:(自动接唱右)
        "LOW",                                          //97

            "SEQ OYNA",//"SEQ PLAY",        //98    T:(抖冀)        S:(顺序播放)

        "MEN""\xdc"" G""\xd6""STER""\x005""M""\x005",         //"MENU PLAY",        //99    T:(垫虫冀)        S:(菜单播放)

        "LFE OUT",                                  //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else        
        "STANDARD",                                 //101
        "ENHANCE",                                  //102
#endif        
        "MEDIUM",                                           //103

        "PRG OYNATMA",    //"PRG PLAY",         //104   T:(絪导僵)          S:(编程播放)
        "HIGH",                                         //105
        "DYNAMIC RANGE",          //"DYNAMIC RANGE",    //106
        OS_ICON_DVD,                                //107
        "OSD D""\x005""LLER""\x005",          //"OSD LANGUAGE",     //108   T:(礶陪ボ粂ē)    S:(画面显示语言)
        OS_ICON_SUBT,                               //109
        "EKRAN ORANI",            //"DISPLAY RATIO",            //110   T:(辊礶ゑㄒ)    S:(屏幕画面比例)
        "TV T""\x005""P""\x005",          //"TV TYPE",      //111   T:(筿跌诀Α)      S:(电视机制式)
        "\xc7""IKI""\x002",       //"EXIT SETUP",       //112   T:(癶砞竚垫虫)    S:(推出设置菜单)
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "SES ""\xc7""IKI""\x02""I",       //"AUDIO OUT",        //113   T:(计絏块)        S:(数码输出)
#endif
        "V""\x005""DEO",                                    //114   T:(跌繵块)        S:(视频输出)
        "\x002""\x005""FRE",              //"PASSWORD",         //115   T:(盞絏)            S:(密码)
        "A""\x005""LE K""\x005""L""\x005""D""\x005",          //"A""\x005""LE K""\x005""L""\x005""D""\x005"="RATING",           //116   T:()            S:(级别)

        "SPDIF/RAW",          //"SPDIF/RAW",        //117   T:(SPDIF/方絏)      S:(SPDIF/源码)

#if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
#else
        "AMP CENTER",                           //118
#endif

        "SPDIF/PCM",                                //119

//        "AMP SUBWOOFER",                      //120
#ifdef SUPPORT_PALM
        "PAL-M",                //120
#else
        "AMP SUBWOOFER",           //120
#endif

#ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
#elif defined(EASTECH_DVI)
        "YCbCr", //121
#else
        "INTERLACE-YUV",                                    //121   T:(跌繵だ秖)        S:(视频分量)
#endif//SHOW_YCbCr

#ifdef SDRAM_16Mb_Mode
        "OTOM",    //"AUTO"                                 //122   T:(笆)            S:(自动)
        "KAP.",           //"OFF",              //123   T:(闽)              S:(关)
#else//SDRAM_16Mb_Mode
        "OTOMAT""\x005""K",    //"AUTO"                                 //122   T:(笆)            S:(自动)
        "KAPALI",             //"OFF",              //123   T:(闽)              S:(关)
#endif//SDRAM_16Mb_Mode

        "",//"TM/CH/TL",                                //124
        "B""\xd6""L""\xdc""M",            //"CHAPTER",          //125   T:(彻竊)            S:(章节)
        "BA""\x002""LIK",             //"TITLE",            //126   T:(夹肈)            S:(标题)
        OS_ICON_ANGLE,                              //127
      #if defined(HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU) //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif
        OS_16_9,                                    //129   T:(16:9 --)
        OS_4_3LB,                                   //130   T:(4:3LB --)
        OS_4_3PS,                                   //131
        "PAL",                                      //132
        "NTSC",                                     //133
        "PAL60",                                    //134

        #ifdef RATING_8
            "3 PG",                                 //135   T:(level 3)
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else
            "2",                                    //136   T:(level 2)
            "1 G",                                  //137   T:(level 1)
            #endif
        #else
            "YET""\x005""\x002""K""\x005""N YOK",     //"NO ADULT",         //135   T:(辅导级)
            "\xc7""OCUK ""\x005""\xc7""\x005""N",     //"KID SAFE",      //136   T:(保留)
            "T""\xdc""M""\xdc"" A""\xc7""IK",         //"VIEW ALL",         //137   T:(礚)
        #endif


        #if defined(HIMAGE_DMA5800) //gerry for huajia 3-3-11 11:14
            "BASS VOL",                             //138
        #elif   defined(SHOW_5_1CH)
            "5.1CH",                                //138   T:(5.1羘笵)
        #else
            "6CH AYARI",//"6CH SETUP",      //138   T:(6羘笵砞竚)
        #endif

        "SUBWOOFER",                                //139   T:(禬)
        "SATURATION",         //140   SATURATION
        "A""\xc7""IK",            //"ON",               //141   T:
        OS_DOBLY,                                   //142
        Ch_clock,                                   //143
        Ch_speaker,                                 //144
        "TEM""\x005""ZLEME",              //"CLEAR",            //145   T:(睲埃)
        //"  T  C",                                 //146
        //"--:--",                                  //147
        "  T  C",                                       //146
        "--:--",                                //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "YAZAMA",             //"EDIT",             //149   T:(絪胯)
        
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42,(Turkish).     
        "ALTYA SE""\xc7""\x005""M""\x005"" 2",    //150
#else
        "",//OS_DIR1,                                   //150
#endif   
        
        "",//OS_DIR2,                                   //151
        OS_DIR3,                                    //152
        OS_DIR4,                                    //153
        "PAL-NC",//OS_DIR5,                                     //154
        OS_LOCK,                                    //155   T:---- L
        OS_UNLOCK,                                  //156   T:---- U
        "HUE",                //157   HUE
        "PROLOGIC",//"-:--:--",                                 //158

        "MOVIE MODE",//"CAUTARE TITLU",   //"TRACK SEARCH",     //159   T:(虫Ρ穓)        S:(单曲搜索)
        "MUSIC MODE",//"CAUTARE CD",          //"DISC SEARCH",      //160   T:(羆盒穓)        S:(全碟搜索)
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//"TT:CH",                                   //161
        #endif
        "T",                  //162

        OS_DIR0,                                    //163
        "CONTRAST",           //164   CONTRAST
        OS_DIR7,                                    //165
        OS_DIR8,                                    //166
        OS_DIR9,                                    //167
        "KANAL",              //"CHANNEL",          //168   T:(羘笵)            S:(声道)
        "BRIGHTNESS",         //169   BRIGHTNESS
        "F/W ID",                                   //170   T:(硁ン絪絏)        S:(软件编码)
        "CHIP ID",                                  //171   T:(絪絏)        S:(芯片编码)

        "B""\xd6""LGE",           //"REGION",           //172   T:(跋絏)            S:(区码)
        "MEMORY",//"FUNCTIE",             //"FUNCTION",         //173   T:(滦弄滦佰)        S:(复读复唱)
        "DYNAMIC",//"MOD",                //"MODE",             //174   T:(家Α)            S:(模式)


        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177


        "MIC1 VOL",//"COMPARARE",         //"COMPARE",          //178   T:(癸ゑ)            S:(对比)
        "MIC2 VOL",//"NUMARATOR",         //"COUNTER",          //179   T:(滦Ω计)        S:(重复次数)

//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU) 
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181 
#else
        "PREV CHAPTER",                             //180   S:(上一章节)
        "NEXT CHAPTER",                             //181   S:(下一章节)
#endif
            //"NIVEL",            //"LEVEL",            //180   T:魁家Α          S:(录音模式)
            //"INALTE",           //"HIGH",             //181   T:蔼珇借            S:(高品质)

#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",                                  //182   T:(禬丁)        S:(超长时间)
#endif
        "",//"SUPER",                                   //183   T:(禬蔼珇借)        S:(超高品质)
        "",//"OPERATING",                               //184   T:(秸竊よΑ)        S:(调节方式)
        "",//"MANUAL",                                  //185   T:(も笆)            S:(手动)
        OS_DIR10,                                   //186
        OS_DIR11,
                                            //187
        "KONSER MODU",      //"CONCERT"                                 //188   T:(贾芔)          S:(音乐厅)
        "K""\x005""L""\x005""SE MODU",            //"CHURCH",           //189   T:(毙绑)            S:(教堂)
        "PAS""\x005""F",              //"PASSIVE",          //190   T:(吏露)            S:(环绕)
        "GEN""\x005""S",                                    //191   T:(糴初)            S:(宽场)
//        "",//"AMFITEATRU",          //"AMPHITH",          //192   T:(蛾粿初)          S:(圆剧场)
//        "",//"STADION",             //"STADIUM",          //193   T:(蔨▅繻)          S:(体育场)
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192    3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "EQ",                                       //194   T:(А颗)            S:(均衡)
        "STANDARD",                                 //195   T:(夹非)            S:(标准)
        "KLAS""\x005""K",             //"CLASSIC",          //196   T:(ㄥ)            S:(古典)
        "ROCK",                                     //197   T:(穘簎)            S:(摇滚)
        "JAZZ",                                     //198   T:(里)            S:(爵士)
        "POP",                                      //199   T:(瑈︽)            S:(流行)
        "KULLANICI",          //"USER",             //200   T:(┦)            S:(个性)
        "ATTRIB",                                   //201   T:(┦)            S:(个性)
        "SF",                                       //202   T:(篊秈)            S:(慢进)
        "SB",                                       //203   T:(篊癶)            S:(慢退)

        "C",                                        //204   //show "C"

        "MERKEZ",           //"CENTER",           //205   T:(い竚喘羘竟)      S:(中置扬声器)
        "ARKA",             //"REAR",             //206   T:(吏露喘羘竟)      S:(环绕扬声器)
        "TV-RGB",             //207
        "4 PG13",                                   //208   T:(辅导级)

        "MRK. GEC""\x05""KME",   //"MERKEZ GEC""\x005""KMES""\x005"="CENTER DELAY",     //209   T:(い竚┑筐)
        "A. HOP GEC""\x005""KM",      //"A. HOPARL""\xd6""R GEC""\x005""KMES""\x005"="REAR DELAY",         //210   T:(吏露┑筐)

        "\xd6""N",        //"FRONT",            //211   T:(玡竚喘羘竟)
        "VIDEO SETUP",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS

        "S""\x005""STEM KURULUMU",    //"SYSTEM SETUP",     //214   T:(╰参砞竚)        S:(系统设置)
        "HOPARL""\xd6""R AYARLARI",//"SPEAKER SETUP",    //215   T:(喘羘竟砞竚)      S:(扬声器设置)
        "SES AYARLARI",   //"AUDIO SETUP",      //216   T:(繵砞竚)        S:(音频设置)

        "FB. AYARLARI",           //"FABR""\x005""KA AYARLARI"="DEFAULT",          //217   T:()          S:(缺省值)
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "GRP",                                      //218   //not use
        #endif
        #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU
        "   MNP   ",
        #else
        "EKR KORUYUCU",   //"EKRAN KORUYUCU"="SCREEN SAVER",     //219   T:(辊玂臔)        S:(屏幕保护)
        #endif
        "T""\x005""P 1",              //"TYPE 1",           //220   T:(家Α 1)          S:(模式1)

        #if defined(HIMAGE_DMA5800) //gerry for huajia 3-3-11 11:14
            "TREBLE VOL",           //221
            "MAIN VOL",           //222
        #else
            "T""\x005""P 2",              //"TYPE 2",       //221   T:(家Α 2)          S:(模式2)
            "T""\x005""P 3",              //"TYPE 3",       //222   T:(家Α 3)          S:(模式3)
        #endif

        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                                        //223   S:(5保留)
        #endif
        
        "6 R",                                      //224   S:(限制级)

        #ifdef NOT_SUPPROT_VCD
        "NOT SUPPORTED CD",                         //225   S:(错误碟片)
        #else
        "D""\x005""SK HATASI",            //"ERR DISC",     //225   S:(错误碟片)
        #endif

        "D""\x005""J""\x005""TAL KURULUM",    //"DIGITAL SETUP",//226   T:(计絏砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "M""\x005""K. KURULUM",       //"MIC SETUP",    //227   T:(杠旦砞竚)
        "M""\x005""K. SES",           //"MIC VOL",      //228   T:(杠旦秖)
		#endif
        "CD RECOVERING",//229   T:(岿い)
        "SMART UPGRADE",//230   T:(醇ど)
        "UPGRADE TO V ",//231   T:(どΘ)
        "UPGRADING",          //232   T:(どい)

        "G""\xdc""\xc7"" A""\xc7""IK",            //"NOT POWER OFF",//233   T:(づ闽诀)
        "B""\xd6""LGE 0",             //"REGION 0",     //234   T:(0 跋)
        "B""\xd6""LGE 1",             //"REGION 1",     //235   T:(1 跋)
        "B""\xd6""LGE 2",             //"REGION 2",     //236   T:(2 跋)
        "B""\xd6""LGE 3",             //"REGION 3",     //237   T:(3 跋)
        "B""\xd6""LGE 4",             //"REGION 4",     //238   T:(4 跋)
        "D""\x005""L SE""\xc7""\x005""M""\x005",      //"LANGUAGE SETUP",     //239   T:(粂ē砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
	"DISPLAY",            //240
	#else
        "",                                         //240   //not use
        #endif
        "ANA SAYFA",          //"MAIN PAGE",    //241   T:()
        "SES SE""\xc7""\x005""M""\x005",              //"D""\x005""L/SES SE""\xc7""\x005""M""\x005"="AUDIO LANG",   //242   T:(繵粂ē)
        "ALTYA SE""\xc7""\x005""M""\x005",            //"ALTYAZI SE""\xc7""\x005""M""\x005"="SUBTITLE LANG",      //243   T:(辊粂ē)
        "MEN""\xdc"" D""\x005""L""\x005",             //"MENU LANG",    //244   T:(垫虫粂ē)
        "DOWNMIX",      //245   T:(睼家Α)
        "TAMAM",                  //"RESTORE",      //246   T:(確)
        "LT/RT",                                    //247
        "VSS",                                      //248   T:(店览吏露羘)      S:(虚拟环绕声)
        "OP MODU",                //"OP MODE",      //249   T:(块家Α)        S:(输出模式)
        "LINE OUT",                                 //250   T:(絬隔块)        S:(线路输出)
        "RF REMOD",                                 //251   T:(RF 秸俱)         S:(RF调整)
        "DUAL MONO",                                //252   T:(オ+)           S:(左+右)
        "MIX MONO",                                 //253   T:(睼羘笵)        S:(混合声道)
        "SURROUND MODU",              //"SURND MODE",   //254   T:(吏露家Α)        S:(环绕模式)
#ifdef KSD_DVD
        "PRESS PLAY BUTTON TO CONTINUE",        //255   T:              S:请按播放键继续
#else
        "DURAKLA",                //"PRE STOP",                                 //255   T:                  S:(准停止)
#endif
//=====================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER
},
#endif//#ifdef USE_TURKISH_OSD

#ifdef USE_DUTCH_OSD
//Dutch
{
        "",                                             //0
#ifdef FUSS_KETIAN_DVD
        "CHK DISC",                                     //1
#else
        "GEEN DISK",            //"NO DISC",            //1     T:(礚盒)            S:(无碟)
#endif
        "VERKEERDE INPUT",      //"INVALID KEY",        //2     T:(眤岿 hand)   S:(您按错了 HAND)
        "TRK",                                          //3     T:(Ρヘ)            S:(曲目)
        OS_ICON_SVCD,                                   //4
        "DE-INTERLACE",                 //"CHINESE",            //5 not use
        "OPENEN",               //"OPEN",                                           //6     T:()            S:(出仓)
        "SLUITEN",              //"CLOSE",              //7     T:(闽)            S:(关仓)
        "AFSPE.",               //"AFSPELEN",           //"PLAY",               //8     T:(冀)            S:(播放)
        "REGIO 5",              //"REGION 5",           //9     T:(5 跋)            S:(5区)
        "PAUZE",                //"PAUSE",              //10    T:(既氨)            S:(暂停)
        "WILLEK VOLG",          //"RANDOM",             //11    T:(繦诀冀)        S:(随即播放)
        "HERNEMEN",             //"RESUME",             //12    T:(確冀)        S:(恢复播放)
        "STOP",                                         //13    T:(氨ゎ)            S:(停止)
        "STAP",                 //"STEP",               //14    T:(˙秈)            S:(单步)
        "SELECT",                                       //15    T:(匡拒)            S:(选择)

        #if defined(FUSS_DVD)||defined(HUAJIA_DVD)||defined(HIMAGE_CARD_READER)   //NONO 2-5-15 3:01
            "LADEN",            //"LOADING",        //16    T:(弄盒)            S:(读碟)
        #else
            "LEZEN",            //"READ",           //16    T:(弄盒)            S:(读碟)
        #endif

        "REGIO 6",              //"REGION 6",           //17    T:(6 跋)

        #ifdef FUSS_MASCO_DVD_TV  //2003-03-14
            "OFF",
        #else
            "ANALOOG",          //"ANALOG",             //18    T:(家览)
        #endif

        "FF",                   //"FORWARD",            //19    T:(е秈)
        "FR",                   //"BACKWARD",           //20    T:(е癶)
        "VOLGENDE",             //"NEXT",               //21    T:(Ρ >>)

        #ifdef ADJ_SIXCH
            "AMPVOL",                               //22
        #else
            "",                                     //22
        #endif

        "VORIGE",               //"PREV",               //23    T:(Ρ <<)

        "DIR",                                      //24

        "TERUGKEREN",           //"RETURN",             //25    T:(垫虫)
        Ch_repx,                                        //26
        Ch_rep1,                                        //27
        Ch_repd,                                        //28
        "UIT",                  //"OFF",                //29    T:(礚)              S:(无)
        "MENU",                                         //30    T:(匡虫)            S:(选单)
        "SCORE",                                        //31    T:(だ计)            S:(分数)
        "MARK",                                         //32    T:(癘拘)            S:(记忆)
        "BLADEREN",             //"BROWSE",             //33    T:(聅凝)            S:(浏览)
        "PROG",                                         //34    T:(絪祘)            S:(编程)

        "SAVING LOGO...",                               //35
        "GRTE LSPK",            //"ALL LG SPK",         //36    T:(家Α1)
#ifdef SDRAM_16Mb_Mode
        "HER.",             //"REP",                //37    T:(確)
        "MAP HER.",         //"REP DIR",            //38    T:(ヘ魁確)
        "HER. 1",           //"REP 1",              //39    T:(虫Ρ確)
        "ALLES HER.",       //"REP ALL",            //40    T:(盒確)
#else//SDRAM_16Mb_Mode
        "HERHALEN",             //"REP",                //37    T:(確)
        "MAP HERHALEN",         //"REP DIR",            //38    T:(ヘ魁確)
        "HERHALEN 1",           //"REP 1",              //39    T:(虫Ρ確)
        "ALLES HERHALEN",       //"REP ALL",            //40    T:(盒確)
#endif//SDRAM_16Mb_Mode
        "HERHALEN ANNULEREN",   //"REP CANCEL",         //41    T:(確)
        "ALL SM SPK",                                   //42    T:(家Α2)
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
        #else// #ifdef HJ_APEX_FIX_SHOW_OSD
        "8 ADULT",                                      //43
        #endif// #ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",
        #endif
        "7 NC-17",                                      //44    T:(虫Ρ冀)
        "NAAR",                 //"GOTO",               //45    T:(穓)
        "GEEN GELUID",          //"MUTE",               //46    T:(繰)
#ifdef SDRAM_16Mb_Mode
        "LI. MONO",                                         //47    T:(オ羘笵)
        "RC. MONO",                                         //48    T:(羘笵)
#else//SDRAM_16Mb_Mode        
        "LINKS MONO",                                       //47    T:(オ羘笵)
        "RCHTS MONO",                                       //48    T:(羘笵)
#endif//SDRAM_16Mb_Mode
        
        "STEREO",                                       //49    T:(ミ砰羘)
        "MUTE CANCEL",          //"SCORE MODE",         //50
        "LIVE",                                         //51    T:
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "TOONTSET",             //"TEST TONE",          //52
#endif
        "GEMENGDE LSPK",        //"MIXED SPK",          //53    T:(家Α3)
        OS_ICON_CDROM,                                  //54
        "BALANCE L",            //"TIME",               //55    not use
        "TV-VIDEO",             //"TV VIDEO",           //56    //nono 3-2-26 18:36
        "ZOOM",                                         //57    T:(糴)            S:(放宽)
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                    //58    //not use
#endif
        OS_ICON_LANG,                                   //59
        "INTRO",                                        //60    T:(苯磞)            S:(扫描)
        "SRND",//"SURROUND",                                    //61    T:(吏露)            S:(环绕)
        "PBC",                                          //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "BALANCE R",            //"PBC OFF",            //63    not use
#endif
        "WILLEKEUR ANNULEREN",  //"RAND CANCEL",        //64    T:(繦诀冀)    S:(随即播放取消)
        "BASMODUS",             //"BASS MODE",          //65    T:(家Α)

        "AMP FRONT",                                    //66

        "HERHALEN A-",          //"REPEAT A-",          //67    T:(確A-)          S:(重复 A   )
        "PC-VGA",                                               //68
        "HERHALEN A-B",         //"REPEAT A-B",         //69    T:(確A-B)       S:(重复播放A-B)
        "A-B ANNULEREN",            //"A-B CANCEL",         //70    T:(確)        S:(A-B取消)
        "PRG ANNULEREN",        //"PRG CANCEL",         //71    T:(絪胆)            S:(编程取消)
        "",                                             //72
        #ifdef MACROVISION_SHOW_FW_VERSION
        MCRV_STR,//
        #else
        "",                     //"ENGLISH",            //73   not use
        #endif
        OS_ICON_VCD,                                    //74
        "NTSC-J",                                       //75    //NTSC-J
        "",                                             //76    //not use
        "CVBS",                     //OS_ICON_MP3,          //77 not use
        OS_ICON_CDDA,                                   //78
        "48K",                   //79    //not use
        "96K",                   //80    //not use
        "192K",                   //81    //not use
        "ZOOM NAAR BOVEN",          //"ZOOM UP",            //82    T:(礶簿)        S:(放大上)
        "ZOOM NAAR ONDER",          //"ZOOM DOWN",          //83    T:(礶簿)        S:(放大下)
        "ZOOM LINKS",       //"ZOOM LEFT",          //84    T:(礶オ簿)        S:(放大左)
        "ZOOM RECHTS",      //"ZOOM RIGHT",         //85    T:(礶簿)        S:(放大右)
        "KA",//"CH",                                            //86    T:(彻竊)            S:(章节)
        "ECHO",                                         //87    T:(睼臫)            S:(混响)
        "TT",                                           //88    T:(夹肈)            S:(标题)
        "BAND",                                             //89    //not use

#ifdef SDRAM_16Mb_Mode
        "VOL",//"VOL",                                          //90    T:(秖)            S:(音量)
#else//SDRAM_16Mb_Mode
        "VOLUME",//"VOL",                                           //90    T:(秖)            S:(音量)
#endif//SDRAM_16Mb_Mode
        "DOWN SAMPLE",  //91    //not use
        "SLEUTEL",                  //"KEY",                //92    T:(秸)            S:(音调)
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        "9FRAME_1",                                     //94    T:(虫Ρ礶)      S:(单曲九画面)
        "AUTO LINKS",                                       //95    T:(笆钡佰オ)      S:(自动接唱左)
        "AUTO RECHTS",                                      //96    T:(笆钡佰)      S:(自动接唱右)
        "LOW",                                              //97

            "SEQ WEERGAVE", //"SEQ PLAY",       //98    T:(抖冀)        S:(顺序播放)

        "MENU WEERGAVE",        //"MENU PLAY",          //99    T:(垫虫冀)        S:(菜单播放)
        "VLF UIT",              //"LFE OUT",            //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else        
        "STANDARD",                                     //101
        "ENHANCE",                                      //102
#endif        
        "MEDIUM",                                               //103
        "PROGRAM WEERGAVE",     //"PRG PLAY",           //104   T:(絪导僵)          S:(编程播放)
        "HIGH",                                             //105
        "DYNMC.BEREIK",     //"DYNAMIC RANGE",      //106
        OS_ICON_DVD,                                    //107

        #ifdef FUSS_MASCO_DVD_TV  //2003-03-14
            "OSD LANG",
        #elif defined(HJ_2303)
        "OSD",                                          //108   T:(礶陪ボ粂ē)    S:(画面显示语言)
        #else
        "OSD TAAL",             //"OSD LANGUAGE",       //108   T:(礶陪ボ粂ē)    S:(画面显示语言)
        #endif

        OS_ICON_SUBT,                                   //109

        #ifdef SDRAM_16Mb_Mode  //2003-03-14
        "TYPE TV",                                      //110   T:(辊礶ゑㄒ)    S:(屏幕画面比例)
        "TYP SYS.",         //"TV SYSTEM",        //111   T:(筿跌诀Α)      S:(电视机制式)
        #else
        "TYPE TV",                                      //110   T:(辊礶ゑㄒ)    S:(屏幕画面比例)
        #ifdef MINTON_DVD       //heqiang，2004-2-29 10:16        
        "TV MODE",              //111    S:(电视机制式)
        #else        
        "TYPE SYSTEEM",         //"TV SYSTEM",        //111   T:(筿跌诀Α)      S:(电视机制式)
        #endif//MINTON_DVD
        #endif//SDRAM_16Mb_Mode

        "INSTEL.VERLA.",//"INSTELLEN VERLATEN",     //"EXIT SETUP",         //112   T:(癶砞竚垫虫)    S:(推出设置菜单)

        #ifdef FUSS_MASCO_DVD_TV  //2003-03-14
            "SPDIF/PCM",
        #elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
            "PCM",          //113   T:(计絏块)        S:(数码输出)
        #else
        "AUDIO UIT",            //"AUDIO OUT",          //113   T:(计絏块)        S:(数码输出)
        #endif

        #ifdef HJ_2303
        "VIDEO OUTPUT",                                 //114   T:(跌繵块)        S:(视频输出)
        #else
        "VIDEO",                                        //114   T:(跌繵块)        S:(视频输出)
        #endif
        "WACHTWOORD",           //"PASSWORD",           //115   T:(盞絏)            S:(密码)

        #ifdef FUSS_MASCO_DVD_TV  //2003-03-14
            "PARENTAL",                                 //116
        #elif defined(HJ_2303)
        "SAFETY SET",                                   //116   T:()            S:(级别)
        #else
        "NIVEAU",                   //"RATING",             //116   T:()            S:(级别)
        #endif

        "SPDIF/RAW",                                    //117   T:(SPDIF/方絏)      S:(SPDIF/源码)

#if defined(SUPPORT_PALN)//4-1-12 10:55
        "PAL-N",        //118
#else
        "AMP CENTER",                                   //118
#endif

        #ifdef FUSS_MASCO_DVD_TV  //2003-03-14
            "ON",                                       //119
        #else
        "SPDIF/PCM",                                    //119
        #endif

//        "AMP SUBWOOFER",                              //120
#ifdef SUPPORT_PALM
        "PAL-M",                //120
#else
        "AMP SUBWOOFER",           //120
#endif
        #ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
        #elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
#elif defined(EASTECH_DVI)
        YCbCr, //121
#else
        "INTERLACE-YUV",                                        //121   T:(跌繵だ秖)        S:(视频分量)
#endif//SHOW_YCbCr

#ifdef SDRAM_16Mb_Mode
        "AUTO",         //"AUTO",               //122   T:(笆)            S:(自动)
#else//SDRAM_16Mb_Mode
        "AUTOMATISCH",          //"AUTO",               //122   T:(笆)            S:(自动)
#endif//SDRAM_16Mb_Mode

        "UIT",                  //"OFF",                //123   T:(闽)              S:(关)
        "",                     //"TM/CH/TL",           //124
        "HOOFDSTUK",            //"CHAPTER",            //125   T:(彻竊)            S:(章节)
        "TITEL",                //"TITLE",              //126   T:(夹肈)            S:(标题)
        OS_ICON_ANGLE,                                  //127
        #ifdef SYBER_DVD
        "P-SCAN YUV",         //128
        #elif defined(HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU)  //caoh 2004-6-16 15:33                       //127
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif

        #ifdef FUSS_MASCO_DVD_TV  //2003-03-14
            "16:9",
        #else
        OS_16_9,                                        //129   T:(16:9 --)
        #endif

        OS_4_3LB,                                       //130   T:(4:3LB --)

        #ifdef FUSS_MASCO_DVD_TV  //2003-03-14
            "4:3",
        #else
        OS_4_3PS,                                       //131
        #endif

        "PAL",                                          //132
        "NTSC",                                         //133
        "PAL60",                                        //134

        #ifdef RATING_8
            "3 PG",                                     //135   T:(level 3)
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else
            "2",                                        //136   T:(level 2)
            "1 G",                                      //137   T:(level 1)
            #endif
        #elif defined(HJ_2303)
            "RESTRICTION",                              //135   T:(辅导级)
            "FOR KIDS",                                 //136   T:(保留)
            "OFF",                                      //137   T:(礚)
        #else
            "GEEN VOLWASS.",    //"NO ADULT",           //135   T:(辅导级)
            "KINDERVEILIG", //"KID SAFE",           //136   T:(保留)
            "BEKIJK ALLES",     //"VIEW ALL",           //137   T:(礚)
        #endif


        #if defined(HIMAGE_DMA5800) //gerry for huajia 3-3-11 11:14
            "BASS VOL",                                 //138
        #elif   defined(SHOW_5_1CH)
            "5.1CH",                                    //138   T:(5.1羘笵)
        #else
            "6CH SETUP",                                //138   T:(6羘笵砞竚)
        #endif

        "SUBWOOFER",                                    //139   T:(禬)
        "SATURATION",         //140   SATURATION
        "AAN",                  //"ON",                 //141   T:
        OS_DOBLY,                                       //142
        Ch_clock,                                       //143
        Ch_speaker,                                     //144
        "WIS",          //"CLEAR",              //145   T:(睲埃)
        //"  T  C",               //146
        //"--:--",              //147
        "  T  C",                                           //146
        "--:--",                                    //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        

        "SAMENSTE", //"SAMENSTELLEN",           //"EDIT",               //149   T:(絪胯)
        
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42,(Dutch).
        "TAAL ONDERT.2",         //150
#else
        "",//OS_DIR1,                                       //150
#endif        
        
        "",//OS_DIR2,                                       //151
        OS_DIR3,                                        //152
        OS_DIR4,                                        //153
        "PAL-NC",//OS_DIR5,                                         //154
        OS_LOCK,                                        //155   T:---- L
        OS_UNLOCK,                                      //156   T:---- U
        "HUE",                //157   HUE
        "PROLOGIC",//"-:--:--",            //158    //not use
        "MOVIE MODE",//"TRACK SEARCH",       //159   //not use
        "MUSIC MODE",//"DISC SEARCH",        //160   //not use
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//TT:CH",               //161    //not use
        #endif

        "T",                  //162 //use when define REMAIN_TIME

        OS_DIR0,                                        //163
        "CONTRAST",           //164   CONTRAST
        OS_DIR7,                                        //165
        OS_DIR8,                                        //166
        OS_DIR9,                                        //167
        "KANAAL",               //"CHANNEL",            //168   T:(羘笵)            S:(声道)
        "BRIGHTNESS",         //169   BRIGHTNESS
        "SNEL VOORWA.",//"F/W ID",                                      //170   T:(硁ン絪絏)        S:(软件编码)
        "SPRING",//"CHIP ID",                                       //171   T:(絪絏)        S:(芯片编码)
        "REGIO",                //"REGION",             //172   T:(跋絏)            S:(区码)
        "MEMORY",                       //"FUNCTION",           //173  //not use T:(滦弄滦佰)        S:(复读复唱)
        "DYNAMIC",                      //"MODE",               //174  //not use  T:(家Α)            S:(模式)

        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

        "MIC1 VOL",//"COMPARE",            //178   //not use T:(癸ゑ)            S:(对比)
        "MIC2 VOL",//"COUNTER",            //179   //not use T:(滦Ω计)        S:(重复次数)
//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU) 
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181 
#else
        "VORG HOOFDSTUK",       //"PREV CHAPTER",       //180   S:(上一章节)
        "VOLG HOOFDSTUK",       //"NEXT CHAPTER",       //181   S:(下一章节)
#endif
#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",             //182   not use
#endif
        "",//"SUPER",              //183   not use
        "",//"OPERATING",          //184   not use
        "",//"MANUAL",             //185   not use
        OS_DIR10,             //186
        OS_DIR11,             //187
        "CONCERT",                                      //188   T:(贾芔)          S:(音乐厅)
        "KERK",                 //"CHURCH",             //189   T:(毙绑)            S:(教堂)
        "PASSIEF",              //"PASSIVE",            //190   T:(吏露)            S:(环绕)
        "WIJD",                 //"WIDE",               //191   T:(糴初)            S:(宽场)
//        "",                       //"AMPHITH",            //192   not use
//        "",                       //"STADIUM",            //193   not use
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192    3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "EQ",                                           //194   T:(А颗)            S:(均衡)
        "STANDAARD",            //"STANDARD",           //195   T:(夹非)            S:(标准)
        "KLASSIEK",             //"CLASSIC",            //196   T:(ㄥ)            S:(古典)
        "ROCK",                                         //197   T:(穘簎)            S:(摇滚)
        "JAZZ",                                         //198   T:(里)            S:(爵士)
        "POP",                                          //199   T:(瑈︽)            S:(流行)
        "GEBRUIKER",            //"USER",               //200   T:(┦)            S:(个性)
        "ATTRIB",                                       //201   T:(┦)            S:(个性)
        "SF",                   //"SF",                 //202   T:(篊秈)            S:(慢进)
        "LA",                   //"SB",                 //203   T:(篊癶)            S:(慢退)

        "C",                                            //204   //show "C"

       "MIDDEN",                //"CENTER",             //205   T:(い竚喘羘竟)      S:(中置扬声器)
       "ACHTER",                //"REAR",               //206   T:(吏露喘羘竟)      S:(环绕扬声器)
        "TV-RGB",             //207
        "4 PG13",                                       //208   T:(辅导级)
        "VERTR MID",        //"CENTER DELAY",       //209   T:(い竚┑筐)
        "VERTR ACHT",       //"REAR DELAY",         //210   T:(吏露┑筐)
        "VOORAAN",                  //"FRONT",              //211   T:(玡竚喘羘竟)
        "VIDEO SETUP",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS

        #ifdef FUSS_MASCO_DVD_TV  //2003-03-14
            "--SETUP MENU--",  //214
        #else
        "INSTELLING SYSTEEM",       //"SYSTEM SETUP",       //214   T:(╰参砞竚)        S:(系统设置)
        #endif

        "LUIDSPREKR INST.",                                 //215   T:(喘羘竟砞竚)      S:(扬声器设置)
        "INST.AUDIO",                                   //216   T:(繵砞竚)        S:(音频设置)

        #ifdef HJ_2303
        "FACTORY SET",                                  //217   T:()          S:(缺省值)
        #else
        "STANDAARD",        //"DEFAULT",            //217   T:()          S:(缺省值)
        #endif
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "GRP",                                          //218   //not use
        #endif

        #ifdef FUSS_MASCO_DVD_TV  //2003-03-14
            "SCR SAVER",
        #else
        #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU
        "   MNP   ",
        #else
        "SCHRMBEVEIL",      //"SCREEN SAVER",       //219   T:(辊玂臔)        S:(屏幕保护)
        #endif
        #endif

        "TYPE 1",             //220   T:(家Α 1)          S:(模式1)

        #if defined(HIMAGE_DMA5800) //gerry for huajia 3-3-11 11:14
            "TREBLE VOL",           //221
            "MAIN VOL",           //222
        #else
            "TYPE 2",             //221   T:(家Α 2)          S:(模式2)
            "TYPE 3",             //222   T:(家Α 3)          S:(模式3)
        #endif

        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   S:(5保留)
        #endif
        
        "6 R",                //224   S:(限制级)

        #ifdef NOT_SUPPROT_VCD
        "NOT SUPPORTED CD",           //225   S:(错误碟片)
        #else
        "ERR DISC",           //225   S:(错误碟片)
        #endif

        "DIGITAL INSTELLEN",        //"DIGITAL SETUP",      //226   T:(计絏砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "INST.MIC",                                     //227   T:(杠旦砞竚)
        "VOLUME MIC",                                       //228   T:(杠旦秖)
        #endif
        "CD TERUGNAME",     //"CD RECOVERING",      //229   T:(岿い)
        "SLIMM.UPGRADE",   //"SMART UPGRADE",                               //230   T:(醇ど)
        "UPGRADE NAAR V",   //"UPGRADE TO V ",      //231   T:(どΘ)
        "UPGRADING",          //232   T:(どい)
        "GEEN UITSCHAKELING",   //"NOT POWER OFF",      //233   T:(づ闽诀)

        "REGIO 0",              //"REGION 0",           //234   T:(0 跋)
        "REGIO 1",              //"REGION 1",           //235   T:(1 跋)
        "REGIO 2",              //"REGION 2",           //236   T:(2 跋)
        "REGIO 3",              //"REGION 3",           //237   T:(3 跋)
        "REGIO 4",              //"REGION 4",           //238   T:(4 跋)

        "INST.TAAL",            //"LANGUAGE SETUP",     //239   T:(粂ē砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
	"DISPLAY",            //240
	#else
        "",                                             //240   //not use
        #endif
        "HOOFDPAGINA",          //"MAIN PAGE",          //241   T:()
    #if defined(HJ_2303)
        "AUDIO",         //242   T:(繵粂ē)
        "SUBTITLE",      //243   T:(辊粂ē)
        "MENU",          //244   T:(垫虫粂ē)
        #elif !defined(BBK_DVD)
        "TAAL AUDIO",           //"AUDIO LANG",         //242   T:(繵粂ē)
        "TAAL ONDERT.",     //"SUBTITLE LANG",      //243   T:(辊粂ē)
        "TAAL MENU",            //"MENU LANG",          //244   T:(垫虫粂ē)
        #else//#elif !defined(BBK_DVD)
        "AUDIO",            //"AUDIO LANG",         //242   T:(繵粂ē)//axel 2004/1/27 03:58 eliminate "LANG"
        "ONDERT.",      //"SUBTITLE LANG",      //243   T:(辊粂ē)
        "MENU",         //"MENU LANG",          //244   T:(垫虫粂ē)
        #endif//#elif !defined(BBK_DVD)

        "MIXEN",        //"DOWNMIX",                                        //245   T:(睼家Α)

        #ifdef FUSS_MASCO_DVD_TV  //2003-03-14
            "RESET",
        #elif defined(HJ_2303)
        "DEFAULT",                                      //246   T:(確)
        #else
        "HERSTELLEN",           //"RESTORE",            //246   T:(確)
        #endif

        #ifdef HJ_2303
        "LEFT/RIGHT",                                   //247
        #else
        "LT/RT",                    //"LT/RT",              //247
        #endif
        "VSS",                  //"VSS",                //248   T:(店览吏露羘)      S:(虚拟环绕声)
        "COMPRESSIE",       //"OP MODE",            //249   T:(块家Α)        S:(输出模式)
        "LIN.UIT",              //"LINE OUT",           //250   T:(絬隔块)        S:(线路输出)
        "RF MODULATIE",         //"RF REMOD",           //251   T:(RF 秸俱)         S:(RF调整)
        "DUBBEL MONO",//"DUAL MONO",                                    //252   T:(オ+)           S:(左+右)
        "MIX MONO",                                     //253   T:(睼羘笵)        S:(混合声道)
        "SURROUND MODUS",           //"SURND MODE",         //254   T:(吏露家Α)        S:(环绕模式)
        "PRE STOP",                                     //    T:                  S:(准停止)

//=====================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER

},
#endif//#ifdef USE_DUTCH_OSD

#ifdef USE_SWEDISH_OSD
//Swedish
{
        "",                                             //0
        "INGEN SKIVA",          //"NO DISC",            //1     T:(礚盒)            S:(无碟)
        "OGILT.INSLAG",     //"INVALID KEY",        //2     T:(眤岿 hand)   S:(您按错了 HAND)
        "TRK",                                          //3     T:(Ρヘ)            S:(曲目)
        OS_ICON_SVCD,                                   //4
        "DE-INTERLACE",                 //"CHINESE",            //5 not use
        "\xd6""PPNA",               //"OPEN",                                           //6     T:()            S:(出仓)
        "ST""\xc4""NG",             //"CLOSE",              //7     T:(闽)            S:(关仓)
        "PLAY",             //"PLAY",               //8     T:(冀)            S:(播放)
        "REGION 5",             //"REGION 5",           //9     T:(5 跋)            S:(5区)
        "PAUSE",                //"PAUSE",              //10    T:(既氨)            S:(暂停)
        "SLUMPVIS",         //"RANDOM",             //11    T:(繦诀冀)        S:(随即播放)
        "\xc5""TERG""\xc5",             //"RESUME",             //12    T:(確冀)        S:(恢复播放)
        "STOPP",//"STOP",                                           //13    T:(氨ゎ)            S:(停止)
        "STEGA",                    //"STEP",               //14    T:(˙秈)            S:(单步)
        "V""\xc4""LJ",              //"SELECT",                                     //15    T:(匡拒)            S:(选择)


        "L""\xc4""SA",          //"READ",           //16    T:(弄盒)            S:(读碟)


        "REGION 6",             //"REGION 6",           //17    T:(6 跋)

        "ANALOG",           //"ANALOG",             //18    T:(家览)
        "FRAM""\xc5""T",                    //"FORWARD",            //19    T:(е秈)
        "BAK""\xc5""T",                 //"BACKWARD",           //20    T:(е癶)
        "N""\xc4""STA",             //"NEXT",               //21    T:(Ρ >>)

        "",                                     //22

        "F""\xd6""REG""\xc5""ENDE",             //"PREV",               //23    T:(Ρ <<)

        "DIR",                                      //24

        "TILLBAKA",         //"RETURN",             //25    T:(垫虫)
        Ch_repx,                                        //26
        Ch_rep1,                                        //27
        Ch_repd,                                        //28
        "AV",                   //"OFF",                //29    T:(礚)              S:(无)
        "MENY",                                         //30    T:(匡虫)            S:(选单)
        "SCORE",                                        //31    T:(だ计)            S:(分数)
        "MARK",                                         //32    T:(癘拘)            S:(记忆)
        "BL""\xc4""DDRA",               //"BROWSE",             //33    T:(聅凝)            S:(浏览)
        "PROGRAM",                                          //34    T:(絪祘)            S:(编程)

        "SAVING LOGO...",                               //35
        "ALL LG SPK",           //"ALL LG SPK",         //36    T:(家Α1)

#ifdef SDRAM_16Mb_Mode
        "REP.",             //"REP",                //37    T:(確)
#else//SDRAM_16Mb_Mode
        "REPETERA",             //"REP",                //37    T:(確)
#endif//SDRAM_16Mb_Mode

        "REP.KAT.",         //"REP DIR",            //38    T:(ヘ魁確)
        "REPETERA 1",           //"REP 1",              //39    T:(虫Ρ確)
        "REP.ALLA",     //"REP ALL",            //40    T:(盒確)
        "AVBRYT REP",   //"REP CANCEL",         //41    T:(確)
        "ALL SM SPK",                                   //42    T:(家Α2)

        "8",                                            //43

        "7 NC-17",                                      //44    T:(虫Ρ冀)
        "G""\xc5"" TILL",                   //"GOTO",               //45    T:(穓)
        "MUTE",         //"MUTE",               //46    T:(繰)
        "MONO V.",                                      //47    T:(オ羘笵)
        "MONO H.",                                      //48    T:(羘笵)
        "STEREO",                                       //49    T:(ミ砰羘)
        "MUTE CANCEL",          //"SCORE MODE",         //50
        "LIVE",                                         //51    T:
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "TEST TONE",                //"TEST TONE",          //52
#endif
        "MIXED SPK",        //"MIXED SPK",          //53    T:(家Α3)
        OS_ICON_CDROM,
        #ifdef OP_CUST_UI//libing 2005-5-11 11:39                                  //54
        "JPEG TIME",
        #else
        "BALANCE L",            //"TIME",               //55    not use
        #endif
        "TV VIDEO",             //"TV VIDEO",           //56    //nono 3-2-26 18:36
        "ZOOM",                                         //57    T:(糴)            S:(放宽)
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                    //58    //not use
#endif
        OS_ICON_LANG,                                   //59
        "INTRO",                                        //60    T:(苯磞)            S:(扫描)
        "SRND",//"SURROUND",                                    //61    T:(吏露)            S:(环绕)
        "PBC",                                          //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "BALANCE R",            //"PBC OFF",            //63    not use
#endif
        "RAND CANCEL",  //"RAND CANCEL",        //64    T:(繦诀冀)    S:(随即播放取消)
        "BASS MODE",                //"BASS MODE",          //65    T:(家Α)

        "AMP FRONT",                                    //66

        "REPET.A-",         //"REPEAT A-",          //67    T:(確A-)          S:(重复 A   )
        "PC-VGA",                                               //68
        "REPET.A-B",            //"REPEAT A-B",         //69    T:(確A-B)       S:(重复播放A-B)
        "AVBRYT A-B",           //"A-B CANCEL",         //70    T:(確)        S:(A-B取消)
        "PRG AVBRYT",       //"PRG CANCEL",         //71    T:(絪胆)            S:(编程取消)
        "",                                             //72
        #ifdef MACROVISION_SHOW_FW_VERSION
        MCRV_STR,//
        #else
        "",                     //"ENGLISH",            //73   not use
        #endif
        OS_ICON_VCD,                                    //74
        "NTSC-J",                                       //75    //NTSC-J
        "",                                             //76    //not use
        "CVBS",                     //OS_ICON_MP3,          //77 not use
        OS_ICON_CDDA,                                   //78
        "48K",                   //79    //not use
        "96K",                   //80    //not use
        "192K",                   //81    //not use
        "ZOOM UPP",         //"ZOOM UP",            //82    T:(礶簿)        S:(放大上)
        "ZOOM NER",         //"ZOOM DOWN",          //83    T:(礶簿)        S:(放大下)
        "ZOOM V""\xc4""NST",        //"ZOOM LEFT",          //84    T:(礶オ簿)        S:(放大左)
        "ZOOM H""\xd6""GER",        //"ZOOM RIGHT",         //85    T:(礶簿)        S:(放大右)
        "CH",//"CH",                                            //86    T:(彻竊)            S:(章节)
        "EKO",//"ECHO",                                         //87    T:(睼臫)            S:(混响)
        "TT",                                           //88    T:(夹肈)            S:(标题)
        "BAND",                                             //89
        "VOLYM",//"VOL",                                            //90    T:(秖)            S:(音量)
        "DOWN SAMPLE",  //91    //not use
        "KNAPP",                    //"KEY",                //92    T:(秸)            S:(音调)
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        "9FRAME_1",                                     //94    T:(虫Ρ礶)      S:(单曲九画面)
        "AUTO V""\xc4""NST",                                        //95    T:(笆钡佰オ)      S:(自动接唱左)
        "AUTO H""\xd6""GER",                                        //96    T:(笆钡佰)      S:(自动接唱右)
        "LOW",                                              //97

        "SEKV.PLAY",    //"SEQ PLAY",       //98    T:(抖冀)        S:(顺序播放)

        "MENY PLAY",        //"MENU PLAY",          //99    T:(垫虫冀)        S:(菜单播放)
        "LFE OUT",              //"LFE OUT",            //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else        
        "STANDARD",                                     //101
        "ENHANCE",                                      //102
#endif        
		#ifdef OP_CUST_UI
        "DIVX ID",                      //103
        #else    
        "MEDIUM",        
        #endif                                       //103
        "PRG.PLAY",     //"PRG PLAY",           //104   T:(絪导僵)          S:(编程播放)
        "HIGH",                                             //105
        "DYNAMIK",      //"DYNAMIC RANGE",      //106
        OS_ICON_DVD,                                    //107

        "OSD SPR""\xc5""K",             //"OSD LANGUAGE",       //108   T:(礶陪ボ粂ē)    S:(画面显示语言)

        OS_ICON_SUBT,                                   //109

        "TV TYP",                                       //110   T:(辊礶ゑㄒ)    S:(屏幕画面比例)
        #if 0//def MINTON_DVD  //heqiang，2004-2-29 10:16        
        "TV-L?GE",            //111    S:(电视机制式)
        #else       
        "TV SYSTEM",            //"TV SYSTEM",        //111   T:(筿跌诀Α)      S:(电视机制式)
        #endif//MINTON_DVD
        "AVSL.INST",        //"EXIT SETUP",         //112   T:(癶砞竚垫虫)    S:(推出设置菜单)
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "AUDIO OUT",         //"AUDIO OUT",          //113   T:(计絏块)        S:(数码输出)
#endif

        "VIDEO",                                        //114   T:(跌繵块)        S:(视频输出)

        "L""\xd6""SENORD",          //"PASSWORD",           //115   T:(盞絏)            S:(密码)

        "NIV""\xc5",                    //"RATING",             //116   T:()            S:(级别)

        "SPDIF/RAW",                                    //117   T:(SPDIF/方絏)      S:(SPDIF/源码)

#if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
#else
        "AMP CENTER",                                   //118
#endif

        "SPDIF/PCM",                                    //119

//        "AMP SUBWOOFER",                              //120
#ifdef SUPPORT_PALM
        "PAL-M",                //120
#else
        "AMP SUBWOOFER",           //120
#endif
#ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
#elif defined(EASTECH_DVI)
        YCbCr, //121
#else
        "INTERLACE-YUV",                                        //121   T:(跌繵だ秖)        S:(视频分量)
#endif//SHOW_YCbCr

        "AUTO",         //"AUTO",               //122   T:(笆)            S:(自动)

        "AV",                   //"OFF",                //123   T:(闽)              S:(关)
        #ifdef SHOW_DRM_REGISTRATION_CODE_IN_SETUP
        "DIVX[R] VOD", //124
        #else
        "",                     //"TM/CH/TL",           //124
        #endif
        "KAPITEL",          //"CHAPTER",            //125   T:(彻竊)            S:(章节)
        "TITEL",                //"TITLE",              //126   T:(夹肈)            S:(标题)
        OS_ICON_ANGLE,                                  //127
      #if defined(HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif

        OS_16_9,                                        //129   T:(16:9 --)

        OS_4_3LB,                                       //130   T:(4:3LB --)

        OS_4_3PS,                                       //131

        "PAL",                                          //132
        "NTSC",                                         //133
        "PAL60",                                        //134

        #ifdef RATING_8
            "3 PG",                                     //135   T:(level 3)
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else
            "2",                                        //136   T:(level 2)
            "1 G",                                      //137   T:(level 1)
            #endif
        #else
            "INGEN VUXEN",  //"NO ADULT",           //135   T:(辅导级)
            "BARNS""\xc4""KER", //"KID SAFE",           //136   T:(保留)
            "VISA ALLA",        //"VIEW ALL",           //137   T:(礚)
        #endif

        "6CH SETUP",                                //138   T:(6羘笵砞竚)
        "SUBWOOFER",                                    //139   T:(禬)
        "SATURATION",         //140   SATURATION
        "P""\xc5",                  //"ON",                 //141   T:
        OS_DOBLY,                                       //142
        Ch_clock,                                       //143
        Ch_speaker,                                     //144
        "RENSA",            //"CLEAR",              //145   T:(睲埃)
        //"  T  C",               //146
        //"--:--",              //147
        "  T  C",                                           //146
        "--:--",                                    //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "REDIGERA",         //"EDIT",               //149   T:(絪胯)
        
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42,(Swedish).
        "TEXT SPR""\xc5""K"" 2",    //150
#else
        "",//OS_DIR1,                                       //150
#endif   
        #ifdef ADJUST_JPEG_SLIDE_TIME  ////lyc 2005/2/18
        "15 SEC",                   //151
        "30 SEC",                   //152
        "45 SEC",                   //153
        "50 SEC",                   //154
        #else
        "",//OS_DIR2,                                       //151
        OS_DIR3,                                        //152
        OS_DIR4,                                        //153
        "PAL-NC",//OS_DIR5,                                         //154
        #endif
        OS_LOCK,                                        //155   T:---- L
        OS_UNLOCK,                                      //156   T:---- U
        "HUE",                //157   HUE
        "PROLOGIC",//"-:--:--",            //158    //not use
        "MOVIE MODE",//"TRACK SEARCH",       //159   //not use
        "MUSIC MODE",//"DISC SEARCH",        //160   //not use

        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//TT:CH",               //161    //not use
        #endif

        "T",                  //162 //use when define REMAIN_TIME

        OS_DIR0,                                        //163
        "CONTRAST",           //164   CONTRAST
        OS_DIR7,                                        //165
        OS_DIR8,                                        //166
        OS_DIR9,                                        //167
        "KANAL",                //"CHANNEL",            //168   T:(羘笵)            S:(声道)
        "BRIGHTNESS",         //169   BRIGHTNESS
        "F/W ID",//"F/W ID",                                        //170   T:(硁ン絪絏)        S:(软件编码)
#ifdef OP_CUST_UI  
		"CHECKSUM",  
#else		    
        "CHIP ID",            //171   T:(絪絏)        S:(芯片编码)
#endif
        "REGION",               //"REGION",             //172   T:(跋絏)            S:(区码)
        "MEMORY",                       //"FUNCTION",           //173  //not use T:(滦弄滦佰)        S:(复读复唱)
        "DYNAMIC",                      //"MODE",               //174  //not use  T:(家Α)            S:(模式)

        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

        "MIC1 VOL",//"COMPARE",            //178   //not use T:(癸ゑ)            S:(对比)
        "MIC2 VOL",//"COUNTER",            //179   //not use T:(滦Ω计)        S:(重复次数)

//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU) 
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181 
#else
        "PREV CHAPTER",     //"PREV CHAPTER",       //180   S:(上一章节)
        "NEXT CHAPTER",     //"NEXT CHAPTER",       //181   S:(下一章节)
#endif
#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",             //182   not use
#endif
        "",//"SUPER",              //183   not use
        "",//"OPERATING",          //184   not use
        "",//"MANUAL",             //185   not use
        OS_DIR10,             //186
        OS_DIR11,             //187
        "KONSERT",//"CONCERT",                                      //188   T:(贾芔)          S:(音乐厅)
        "KYRKA",                    //"CHURCH",             //189   T:(毙绑)            S:(教堂)
        "PASSIV",               //"PASSIVE",            //190   T:(吏露)            S:(环绕)
        "WIDE",                 //"WIDE",               //191   T:(糴初)            S:(宽场)
//        "",                       //"AMPHITH",            //192   not use
//        "",                       //"STADIUM",            //193   not use
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192    3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "EQ",                                           //194   T:(А颗)            S:(均衡)
        "STANDARD",         //"STANDARD",           //195   T:(夹非)            S:(标准)
        "KLASSISK",             //"CLASSIC",            //196   T:(ㄥ)            S:(古典)
        "ROCK",                                         //197   T:(穘簎)            S:(摇滚)
        "JAZZ",                                         //198   T:(里)            S:(爵士)
        "POP",                                          //199   T:(瑈︽)            S:(流行)
        "ANV""\xc4""NDARE",         //"USER",               //200   T:(┦)            S:(个性)
        "ATRIB",                                        //201   T:(┦)            S:(个性)
        "SF",                   //"SF",                 //202   T:(篊秈)            S:(慢进)
        "SB",                   //"SB",                 //203   T:(篊癶)            S:(慢退)

        "C",                                            //204   //show "C"

       "CENTER",                //"CENTER",             //205   T:(い竚喘羘竟)      S:(中置扬声器)
       "BAK",               //"REAR",               //206   T:(吏露喘羘竟)      S:(环绕扬声器)

        "TV-RGB",             //207

        "4 PG13",                                       //208   T:(辅导级)
        "CENT F""\xd6""RDR",        //"CENTER DELAY",       //209   T:(い竚┑筐)
        "F""\xd6""RDR.BAK",     //"REAR DELAY",         //210   T:(吏露┑筐)
        "FRONT",                    //"FRONT",              //211   T:(玡竚喘羘竟)
        "VIDEO SETUP",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS

        "SYS.INST",     //"SYSTEM SETUP",       //214   T:(╰参砞竚)        S:(系统设置)

        "H""\xd6""GT.INST",                                 //215   T:(喘羘竟砞竚)      S:(扬声器设置)
        "LJUDINST.",                                    //216   T:(繵砞竚)        S:(音频设置)

        "F""\xd6""RVALD",       //"DEFAULT",            //217   T:()          S:(缺省值)

        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "GRP",                                          //218   //not use
        #endif

        #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU
        "   MNP   ",
        #else
        "SK""\xc4""RMSL""\xc4""CK",     //"SCREEN SAVER",       //219   T:(辊玂臔)        S:(屏幕保护)
        #endif
		#ifdef ORITRON_PASSWORD//libing 2005-4-29 9:53
        "SET DUFAULT VALUE",
        #else
        "TYPE 1",             //220   T:(家Α 1)          S:(模式1)
        #endif

        #if defined(HIMAGE_DMA5800) //gerry for huajia 3-3-11 11:14
            "TREBLE VOL",           //221
            "MAIN VOL",           //222
        #elif defined(ORITRON_PASSWORD)      
            "CLEAR PASSWORD",             //221   T:(辅导级)
        	"LOADER LOCKED",
        #else
            "TYPE 2",             //221   T:(家Α 2)          S:(模式2)
            "TYPE 3",             //222   T:(家Α 3)          S:(模式3)
        #endif

        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   S:(5保留)
        #endif
        
        "6 R",                //224   S:(限制级)

        #ifdef NOT_SUPPROT_VCD
        "NOT SUPPORTED CD",           //225   S:(错误碟片)
        #else
        "ERR DISC",           //225   S:(错误碟片)
        #endif

        "DIGITAL INST",     //"DIGITAL SETUP",      //226   T:(计絏砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "MIC INST",                                     //227   T:(杠旦砞竚)
        "MIK.VOL.",                                     //228   T:(杠旦秖)
		#endif
        "CD RECOV.",        //"CD RECOVERING",      //229   T:(岿い)
        "SMART UPGRAD",   //"SMART UPGRADE",                            //230   T:(醇ど)
        "UPPGRAD TILL V",   //"UPGRADE TO V ",      //231   T:(どΘ)
        "UPPGRADERAR",          //232   T:(どい)
        "EJ AVST""\xc4""NGD",   //"NOT POWER OFF",      //233   T:(づ闽诀)

        "REGION 0",             //"REGION 0",           //234   T:(0 跋)
        "REGION 1",             //"REGION 1",           //235   T:(1 跋)
        "REGION 2",             //"REGION 2",           //236   T:(2 跋)
        "REGION 3",             //"REGION 3",           //237   T:(3 跋)
        "REGION 4",             //"REGION 4",           //238   T:(4 跋)

        "SPR""\xc5""KINST.",            //"LANGUAGE SETUP",     //239   T:(粂ē砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
	"DISPLAY",            //240
	#else
        "",                                             //240   //not use
        #endif
        "HUVUDSIDA",            //"MAIN PAGE",          //241   T:()

        "LJUD SPR""\xc5""K",            //"AUDIO LANG",         //242   T:(繵粂ē)
        "TEXT SPR""\xc5""K",        //"SUBTITLE LANG",      //243   T:(辊粂ē)
        "MENY SPR""\xc5""K",            //"MENU LANG",          //244   T:(垫虫粂ē)

        "NEDMIX",       //"DOWNMIX",                                        //245   T:(睼家Α)

        "\xc5""TERST""\xc4""LLA",           //"RESTORE",            //246   T:(確)

        "LT/RT",                    //"LT/RT",              //247

        "VSS",                  //"VSS",                //248   T:(店览吏露羘)      S:(虚拟环绕声)
        "OP L""\xc4""GE",       //"OP MODE",            //249   T:(块家Α)        S:(输出模式)
        "LINE UT",              //"LINE OUT",           //250   T:(絬隔块)        S:(线路输出)
        "RF",           //"RF REMOD",           //251   T:(RF 秸俱)         S:(RF调整)
        "DUAL MONO",//"DUAL MONO",                                      //252   T:(オ+)           S:(左+右)
        "MIX MONO",                                     //253   T:(睼羘笵)        S:(混合声道)
        "SURND L""\xc4""GE",            //"SURND MODE",         //254   T:(吏露家Α)        S:(环绕模式)
        "PRE STOP",                                     //    T:                  S:(准停止)

//=====================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER

},
#endif//#ifdef USE_SWEDISH_OSD

#ifdef USE_CZECH_OSD
//Czech
{
        "",                                             //0
        "VLO""\xf7""TE DISK",           //"NO DISC",            //1     T:(礚盒)            S:(无碟)
        "CHYBA",        //"INVALID KEY",        //2     T:(眤岿 hand)   S:(您按错了 HAND)
        "TRK",                                          //3     T:(Ρヘ)            S:(曲目)
        OS_ICON_SVCD,                                   //4
        "DE-INTERLACE",                 //"CHINESE",            //5 not use
        "OTEV""\xcd""R""\xc1""M",               //"OPEN",                                           //6     T:()            S:(出仓)
        "ZAV""\xcd""R""\xc1""M",                //"CLOSE",              //7     T:(闽)            S:(关仓)
        "PLAY",//"P""\x81""EHR"".",//"\xc1""V""\xc1",               //"PLAY",               //8     T:(冀)            S:(播放)
        "REGION 5",             //"REGION 5",           //9     T:(5 跋)            S:(5区)
        "PAUZA",                //"PAUSE",              //10    T:(既氨)            S:(暂停)
        "RANDOM",           //"RANDOM",             //11    T:(繦诀冀)        S:(随即播放)
        "RESUME",               //"RESUME",             //12    T:(確冀)        S:(恢复播放)
        "STOP",//"STOP",                                        //13    T:(氨ゎ)            S:(停止)
        "KROK",                 //"STEP",               //14    T:(˙秈)            S:(单步)
        "V""\xdd""B""\x07""R",              //"SELECT",                                     //15    T:(匡拒)            S:(选择)


        "NA""\x06""\xcd""T""\xc1""M",           //"READ",           //16    T:(弄盒)            S:(读碟)


        "REGION 6",             //"REGION 6",           //17    T:(6 跋)

        "ANALOG",           //"ANALOG",             //18    T:(家览)
        "VP""\x81""ED",                 //"FORWARD",            //19    T:(е秈)
        "VZAD",                 //"BACKWARD",           //20    T:(е癶)
        "DAL""\x85""\xcd",              //"NEXT",               //21    T:(Ρ >>)

        "",                                     //22

        "P""\x81""EDCHOZ""\xcd",                //"PREV",               //23    T:(Ρ <<)

        "DIR",                                      //24

        "N""\xc1""VRAT",            //"RETURN",             //25    T:(垫虫)
        Ch_repx,                                        //26
        Ch_rep1,                                        //27
        Ch_repd,                                        //28
        "VYP",                  //"OFF",                //29    T:(礚)              S:(无)
        "HLAVN""\xcd"" MENU",                                           //30    T:(匡虫)            S:(选单)
        "SKORE",                                        //31    T:(だ计)            S:(分数)
        "MARK",//=="ZNA""\x06""KA",                                         //32    T:(癘拘)            S:(记忆)
        "BROWSE",//"PROHL""\xcd""\xf7""EN""\xcd",               //"BROWSE",             //33    T:(聅凝)            S:(浏览)
        "PROGRAM",                                          //34    T:(絪祘)            S:(编程)

        "SAVING LOGO...",                               //35
        "ALL LG SPK",           //"ALL LG SPK",         //36    T:(家Α1)
        "OPAKOVAT",             //"REP",                //37    T:(確)
        "OPAK DIR",         //"REP DIR",            //38    T:(ヘ魁確)
        "OPAK 1",           //"REP 1",              //39    T:(虫Ρ確)
        "OPAK V""\x85""E",      //"REP ALL",            //40    T:(盒確)
        "ZRU""\x85"" OPAK.",    //"REP CANCEL",         //41    T:(確)
        "ALL SM SPK",                                   //42    T:(家Α2)

        "8 PRO DOS",                                            //43

        "7 NC-17",                                      //44    T:(虫Ρ冀)
        "P""\x81""ESUN",                    //"GOTO",               //45    T:(穓)
        "MUTE",         //"MUTE",               //46    T:(繰)
        "LEV""\xdd",                                        //47    T:(オ羘笵)
        "PRAV""\xdd",                                       //48    T:(羘笵)
        "STEREO",                                       //49    T:(ミ砰羘)
        "MUTE CANCEL",          //"SCORE MODE",         //50
        "LIVE",                                         //51    T:
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "TEST TONE",                //"TEST TONE",          //52
#endif
        "MIXED SPK",        //"MIXED SPK",          //53    T:(家Α3)
        OS_ICON_CDROM,                                  //54
        "BALANCE L",            //"TIME",               //55    not use
        "TV VIDEO",             //"TV VIDEO",           //56    //nono 3-2-26 18:36
        "ZOOM",                                         //57    T:(糴)            S:(放宽)
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                    //58    //not use
#endif
        OS_ICON_LANG,                                   //59
        "INTRO",                                        //60    T:(苯磞)            S:(扫描)
        "SRND",//"SURROUND",                                    //61    T:(吏露)            S:(环绕)
        "PBC",                                          //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "BALANCE R",            //"PBC OFF",            //63    not use
#endif
        "RAND.ZRU""\x85""IT",   //"RAND CANCEL",        //64    T:(繦诀冀)    S:(随即播放取消)
        "BASS MODE",                //"BASS MODE",          //65    T:(家Α)

        "AMP FRONT",                                    //66

        "OPAKOVAT A-",          //"REPEAT A-",          //67    T:(確A-)          S:(重复 A   )
        "PC-VGA",                                               //68
        "OPAKOVAT A-B",         //"REPEAT A-B",         //69    T:(確A-B)       S:(重复播放A-B)
        "A-B ""ZRU""\x85""IT",          //"A-B CANCEL",         //70    T:(確)        S:(A-B取消)
        "PRG ""ZRU""\x85""IT",      //"PRG CANCEL",         //71    T:(絪胆)            S:(编程取消)
        "",                                             //72
        #ifdef MACROVISION_SHOW_FW_VERSION
        MCRV_STR,//
        #else
        "",                     //"ENGLISH",            //73   not use
        #endif
        OS_ICON_VCD,                                    //74
        "NTSC-J",                                       //75    //NTSC-J
        "",                                             //76    //not use
        "CVBS",                     //OS_ICON_MP3,          //77 not use
        OS_ICON_CDDA,                                   //78
        "48K",                   //79    //not use
        "96K",                   //80    //not use
        "192K",                   //81    //not use
        "ZV""\x07""T""\x85""IT",            //"ZOOM UP",            //82    T:(礶簿)        S:(放大上)
        "ZMEN""\x85""IT",           //"ZOOM DOWN",          //83    T:(礶簿)        S:(放大下)
        "VLEVO",        //"ZOOM LEFT",          //84    T:(礶オ簿)        S:(放大左)
        "VPRAVO",       //"ZOOM RIGHT",         //85    T:(礶簿)        S:(放大右)
        "CH",                                           //86    T:(彻竊)            S:(章节)
        "ECHO",//"ECHO",                                        //87    T:(睼臫)            S:(混响)
        "TT",                                           //88    T:(夹肈)            S:(标题)
        "BAND",                                             //89
        "HLASITOST",//"VOL",                                            //90    T:(秖)            S:(音量)
        "DOWN SAMPLE",  //91    //not use
        "KL""\xcd""\x06",                   //"KEY",                //92    T:(秸)            S:(音调)
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        "9FRAME_1",                                     //94    T:(虫Ρ礶)      S:(单曲九画面)
        "AUTO L",                                       //95    T:(笆钡佰オ)      S:(自动接唱左)
        "AUTO P",                                       //96    T:(笆钡佰)      S:(自动接唱右)
        "LOW",                                              //97

        "SEKV. PLAY",//"SE.P""\x81""EHR",   //"SEQ PLAY",       //98    T:(抖冀)        S:(顺序播放)

        "MENU DISKU",       //"MENU PLAY",          //99    T:(垫虫冀)        S:(菜单播放)
        "LFE OUT",              //"LFE OUT",            //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else        
        "STANDARD",                                     //101
        "ENHANCE",                                      //102
#endif        
        "MEDIUM",                                               //103
        "PRG PLAY",     //"PRG PLAY",           //104   T:(絪导僵)          S:(编程播放)
        "HIGH",                                             //105
        "DYNAMIC RANGE",        //"DYNAMIC RANGE",      //106
        OS_ICON_DVD,                                    //107

        "JAZYK MENU.",              //"OSD LANGUAGE",       //108   T:(礶陪ボ粂ē)    S:(画面显示语言)

        OS_ICON_SUBT,                                   //109

        "TV FORM""\xc1""T",                                     //110   T:(辊礶ゑㄒ)    S:(屏幕画面比例)
        "TV STANDARD",          //"TV SYSTEM",        //111   T:(筿跌诀Α)      S:(电视机制式)

        "V""\xdd""STUP Z MENU",     //"EXIT SETUP",         //112   T:(癶砞竚垫虫)    S:(推出设置菜单)
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "AUDIO V""\xdd""STUP",          //"AUDIO OUT",          //113   T:(计絏块)        S:(数码输出)
#endif

        "VIDEO V""\xdd""STUP",                                          //114   T:(跌繵块)        S:(视频输出)

        "HESLO",            //"PASSWORD",           //115   T:(盞絏)            S:(密码)

        "OMEZEN""\xcd",                 //"RATING",             //116   T:()            S:(级别)

        "SPDIF/RAW",                                    //117   T:(SPDIF/方絏)      S:(SPDIF/源码)

#if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
#else
        "AMP CENTER",                                   //118
#endif

        "SPDIF/PCM",                                    //119

//        "AMP SUBWOOFER",                              //120
#ifdef SUPPORT_PALM
        "PAL-M",                //120
#else
        "AMP SUBWOOFER",           //120
#endif

#ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
#elif defined(EASTECH_DVI)
        YCbCr, //121
#else
        "INTERLACE-YUV",                                        //121   T:(跌繵だ秖)        S:(视频分量)
#endif//SHOW_YCbCr

        "AUTO",         //"AUTO",               //122   T:(笆)            S:(自动)

        "VYP",                  //"OFF",                //123   T:(闽)              S:(关)
        "",                     //"TM/CH/TL",           //124
        "D""\xcd""L",           //"CHAPTER",            //125   T:(彻竊)            S:(章节)
        "TITUL",                //"TITLE",              //126   T:(夹肈)            S:(标题)
        OS_ICON_ANGLE,                                  //127
      #if defined(HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif

        OS_16_9,                                        //129   T:(16:9 --)

        OS_4_3LB,                                       //130   T:(4:3LB --)

        OS_4_3PS,                                       //131

        "PAL",                                          //132
        "NTSC",                                         //133
        "PAL60",                                        //134

        #ifdef RATING_8
            "3 PG",                                     //135   T:(level 3)
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else
            "2",                                        //136   T:(level 2)
            "1 G",                                      //137   T:(level 1)
            #endif
        #else
            "PRO DOSPELE",  //"NO ADULT",           //135   T:(辅导级)
            "OD 15LET", //"KID SAFE",           //136   T:(保留)
            "BEZ OMEZEN""\xcd",     //"VIEW ALL",           //137   T:(礚)
        #endif


        "6CH SETUP",                                //138   T:(6羘笵砞竚)

        "SUBWOOFER",                                    //139   T:(禬)
        "SATURATION",         //140   SATURATION
        "ZAP",                  //"ON",                 //141   T:
        OS_DOBLY,                                       //142
        Ch_clock,                                       //143
        Ch_speaker,                                     //144
        "SMAZAT",           //"CLEAR",              //145   T:(睲埃)
        //"  T  C",               //146
        //"--:--",              //147
        "  T  C",                                           //146
        "--:--",                                    //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "EDIT",         //"EDIT",               //149   T:(絪胯)
        
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42,(Czech).
        "TITULKY 2",    //150
#else
        "",//OS_DIR1,                                       //150
#endif   
        
        "",//OS_DIR2,                                       //151
        OS_DIR3,                                        //152
        OS_DIR4,                                        //153
        "PAL-NC",//OS_DIR5,                                         //154
        OS_LOCK,                                        //155   T:---- L
        OS_UNLOCK,                                      //156   T:---- U
        "",//"",                   //157   //not use
        "PROLOGIC",//"-:--:--",            //158    //not use
        "MOVIE MODE",//"TRACK SEARCH",       //159   //not use
        "MUSIC MODE",//"DISC SEARCH",        //160   //not use
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//TT:CH",               //161    //not use
        #endif

        "T",                  //162 //use when define REMAIN_TIME

        OS_DIR0,                                        //163
        "CONTRAST",           //164   CONTRAST
        OS_DIR7,                                        //165
        OS_DIR8,                                        //166
        OS_DIR9,                                        //167
        "KAN""\xc1""L",             //"CHANNEL",            //168   T:(羘笵)            S:(声道)
        "BRIGHTNESS",         //169   BRIGHTNESS
        "F/W ID",//"F/W ID",                                        //170   T:(硁ン絪絏)        S:(软件编码)
        "CHIP ID",//"CHIP ID",                                      //171   T:(絪絏)        S:(芯片编码)
        "REGION",               //"REGION",             //172   T:(跋絏)            S:(区码)
        "MEMORY",                       //"FUNCTION",           //173  //not use T:(滦弄滦佰)        S:(复读复唱)
        "DYNAMIC",                      //"MODE",               //174  //not use  T:(家Α)            S:(模式)

        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

        "MIC1 VOL",//"COMPARE",            //178   //not use T:(癸ゑ)            S:(对比)
        "MIC2 VOL",//"COUNTER",            //179   //not use T:(滦Ω计)        S:(重复次数)

//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU) 
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181 
#else
        "PREV CHAPTER",     //"PREV CHAPTER",       //180   S:(上一章节)
        "NEXT CHAPTER",     //"NEXT CHAPTER",       //181   S:(下一章节)
#endif
#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",             //182   not use
#endif
        "",//"SUPER",              //183   not use
        "",//"OPERATING",          //184   not use
        "",//"MANUAL",             //185   not use
        OS_DIR10,             //186
        OS_DIR11,             //187
        "KONCERT",//"CONCERT",                                      //188   T:(贾芔)          S:(音乐厅)
        "KOSTEL",                   //"CHURCH",             //189   T:(毙绑)            S:(教堂)
        "PASIVN""\xcd",             //"PASSIVE",            //190   T:(吏露)            S:(环绕)
        "WIDE",//"\x85""IROKO""\xda""H",                    //"WIDE",               //191   T:(糴初)            S:(宽场)
//        "",                       //"AMPHITH",            //192   not use
//        "",                       //"STADIUM",            //193   not use
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192    3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "EQ",                                           //194   T:(А颗)            S:(均衡)
        "STANDARD",         //"STANDARD",           //195   T:(夹非)            S:(标准)
        "KLASIKA",              //"CLASSIC",            //196   T:(ㄥ)            S:(古典)
        "ROCK",                                         //197   T:(穘簎)            S:(摇滚)
        "JAZZ",                                         //198   T:(里)            S:(爵士)
        "POP",                                          //199   T:(瑈︽)            S:(流行)
        "U""\xf7""IVATEL",          //"USER",               //200   T:(┦)            S:(个性)
        "ATRIB",                                        //201   T:(┦)            S:(个性)
        "SF",                   //"SF",                 //202   T:(篊秈)            S:(慢进)
        "SB",                   //"SB",                 //203   T:(篊癶)            S:(慢退)

        "C",                                            //204   //show "C"

       "ST""\x81""EDN""\xcd",               //"CENTER",             //205   T:(い竚喘羘竟)      S:(中置扬声器)
       "ZADN""\xcd",                //"REAR",               //206   T:(吏露喘羘竟)      S:(环绕扬声器)

        "TV-RGB",             //207

        "4 PG13",                                       //208   T:(辅导级)
        "ZPO""\xf7""D""\x07""N""\xcd"" ST""\x81"".",        //"CENTER DELAY",       //209   T:(い竚┑筐)
        "ZPO""\xf7""D""\x07""N""\xcd"" ZAD.",//"ZADN""\xcd"" ZPO",      //"REAR DELAY",         //210   T:(吏露┑筐)
        "P""\x81""EDN""\xcd",                   //"FRONT",              //211   T:(玡竚喘羘竟)
        "VIDEO SETUP",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS

        "Z""\xc1""KLADN""\xcd"" NASTAVEN""\xcd",//"NASTAVEN""\xcd",     //"SYSTEM SETUP",       //214   T:(╰参砞竚)        S:(系统设置)

        "NASTAVEN""\xcd"" REPRODUKTOR""\r\x1a",//"NAST.REPR",                               //215   T:(喘羘竟砞竚)      S:(扬声器设置)
        "NASTAVEN""\xcd"" V""\xdd""STUPU ZVUKU",//"NAST.AUDIO",                                 //216   T:(繵砞竚)        S:(音频设置)

        "DEFAULT",//"P""\r\x1a""V NAST.",       //"DEFAULT",            //217   T:()          S:(缺省值)

        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "GRP",                                          //218   //not use
        #endif

         #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU
        "   MNP   ",
        #else
        "SPO""\x81""I""\x06"" OBR.",        //"SCREEN SAVER",       //219   T:(辊玂臔)        S:(屏幕保护)
        #endif

        "TYP 1",             //220   T:(家Α 1)          S:(模式1)

        #if defined(HIMAGE_DMA5800) //gerry for huajia 3-3-11 11:14
            "TREBLE VOL",           //221
            "MAIN VOL",           //222
        #else
            "TYP 2",             //221   T:(家Α 2)          S:(模式2)
            "TYP 3",             //222   T:(家Α 3)          S:(模式3)
        #endif

        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   S:(5保留)
        #endif
        
        "6 R",                //224   S:(限制级)

        #ifdef NOT_SUPPROT_VCD
        "NOT SUPPORTED CD",           //225   S:(错误碟片)
        #else
        "CHYBA DISK",           //225   S:(错误碟片)
        #endif

        "NASTAVEN""\xcd"" DIGITAL ZVUKU",//"DOLBY DIGI",        //"DIGITAL SETUP",      //226   T:(计絏砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "MIC SETUP",                                    //227   T:(杠旦砞竚)
        "MIC VOL.",                                     //228   T:(杠旦秖)
		#endif
        "CD RECOV",     //"CD RECOVERING",      //229   T:(岿い)
        "UPGRADE SW",   //"SMART UPGRADE",                              //230   T:(醇ど)
        "UPGRADE NA",   //"UPGRADE TO V ",      //231   T:(どΘ)
        "PRACUJI",          //232   T:(どい)
        "NEVYP""\xcd""NAT", //"NOT POWER OFF",      //233   T:(づ闽诀)

        "REGION 0",             //"REGION 0",           //234   T:(0 跋)
        "REGION 1",             //"REGION 1",           //235   T:(1 跋)
        "REGION 2",             //"REGION 2",           //236   T:(2 跋)
        "REGION 3",             //"REGION 3",           //237   T:(3 跋)
        "REGION 4",             //"REGION 4",           //238   T:(4 跋)

        "JAZYKOV""\xc9"" VOLBY",            //"LANGUAGE SETUP",     //239   T:(粂ē砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
	"DISPLAY",            //240
	#else
        "",                                             //240   //not use
        #endif
        "HLAVN""\xcd"" MENU",           //"MAIN PAGE",          //241   T:()

        "ZVUK",         //"AUDIO LANG",         //242   T:(繵粂ē)
        "TITULKY",      //"SUBTITLE LANG",      //243   T:(辊粂ē)
        "MENU DISKU",           //"MENU LANG",          //244   T:(垫虫粂ē)

        "DOWNMIX",      //"DOWNMIX",                                        //245   T:(睼家Α)

        "OBNOVIT",          //"RESTORE",            //246   T:(確)

        "LT/PT",                    //"LT/RT",              //247

        "VSS",                  //"VSS",                //248   T:(店览吏露羘)      S:(虚拟环绕声)
        "OP MODE",      //"OP MODE",            //249   T:(块家Α)        S:(输出模式)
        "LINK. V""\xdd""STUP",              //"LINE OUT",           //250   T:(絬隔块)        S:(线路输出)
        "RF REMOD",         //"RF REMOD",           //251   T:(RF 秸俱)         S:(RF调整)
        "DUAL MONO",//"DUAL MONO",                                      //252   T:(オ+)           S:(左+右)
        "MIX MONO",                                     //253   T:(睼羘笵)        S:(混合声道)
        "SURR. MOD",            //"SURND MODE",         //254   T:(吏露家Α)        S:(环绕模式)
        "PRE STOP",                                     //    T:                  S:(准停止)
//=====================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER

},
#endif//#ifdef USE_CZECH_OSD




#ifdef USE_KOREAN_OSD
{
        OS_NULL,              //0
        KOS_NODISC,            //1     T:(礚盒)
        OS_NO,                //2     T:(眤岿 hand)
        KOS_TRACK,             //3     T:(Ρヘ)
        OS_ICON_SVCD,         //4
        "DE-INTERLACE",//OS_CHINESE,           //5     not use
        KOS_OPEN,              //6     T:()
        KOS_CLOSE,             //7     T:(闽)
        KOS_PLAY,              //8     T:(冀)
        KOS_REGION_5,          //9     T:(5 跋)
        KOS_PAUSE,             //10    T:(既氨)
        KOS_RANDOM,            //11    T:(繦诀冀)
        KOS_RESUME,            //12    T:(確冀)
        KOS_STOP,              //13    T:(氨ゎ)
        KOS_STEP,              //14    T:(˙秈)
        KOS_SELECT,            //15    T:(匡拒)
        KOS_READ,              //16    T:(弄盒)
        KOS_REGION_6,          //17    T:(6 跋)
        KOS_SIMULATE,          //18    T:(家览)
        KOS_FF,                //19    T:(е秈)
        KOS_FB,                //20    T:(е癶)
        KOS_NEXT,              //21    T:(Ρ >>)
    
        OS_NULL,            //22

        KOS_PREV,              //23    T:(Ρ <<)

        OS_NULL,                     //24

        KOS_RETURN,            //25    T:(垫虫)
        Ch_repx,              //26
        Ch_rep1,              //27
        Ch_repd,              //28
        "NO",//Ch_vff,               //29    T:(礚)
        KOS_MENU,              //30    T:(匡虫)
        KOS_SCORE,             //31    T:(だ计)
        KOS_MARK,              //32    T:(癘拘)
        KOS_BROWSE,            //33    T:(聅凝)
        "PROG",//KOS_PROG,              //34    T:(絪)
        "SAVING LOGO...",      //35    //not use
        KOS_BASS_MODE_1,       //36    T:(家Α1)
        KOS_REP,               //37    T:(確)
        KOS_REP_DIR,           //38    T:(ヘ魁確)
        KOS_REP_1,             //39    T:(虫Ρ確)
        KOS_REP_ALL,           //40    T:(盒確)
        KOS_REP_CNL,           //41    T:(確)
        KOS_BASS_MODE_2,       //42    T:(家Α2)
        //"8",                //43    S:(8保留)
        #ifdef FIX_RATING_8_DISPLAY
        "8 ADULT",            //43
        #else
        "8",
        #endif
        "7 NC-17",            //44
        KOS_GOTO,              //45    T:(穓)
        KOS_MUTE,              //46    T:(繰)
        KOS_CHL,               //47    T:(オ羘笵)
        KOS_CHR,               //48    T:(羘笵)
        KOS_STEREO,            //49    T:(ミ砰羘)
        KOS_CANCEL_MUTE,    //50    S:取消静音//not use
        KOS_LIVE,              //51
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "",                   //52    //not use
#endif
        KOS_BASS_MODE_3,       //53    T:(家Α3)
        OS_ICON_CDROM,        //54
        KOS_TIME,              //55    T:丁
        "",                   //56    //not use
        KOS_ZOOM,              //57    T:(糴)
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                    //58    //not use
#endif
        OS_ICON_LANG,         //59
        KOS_INTRO,             //60    T:(苯磞)
        KOS_SURR,              //61    T:(吏露)
        "PBC",                //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "",//OS_PBC_OFF,           //63    T:抖冀
#endif
        "RANDOM CANCEL",//CLEAD_KOREAN OS_RANDOM OS_CANCEL,  //64    T:(繦诀冀)
        KOS_BASS_MANAGEMENT,      //65    T:(家Α)

            "",//"POWER ON",                    //66

        KOS_REP_A,             //67    T:確A-
        "PC-VGA",               //"PC-VGA",           //68
        KOS_REP_AB,            //69    T:確A-B
        "REP CANCEL",//CLEAD_KOREAN OS_CANCEL OS_REP,     //70    T:確
        "PROG CANCEL",//CLEAD KOREAN OS_PROG OS_CANCEL,    //71    T:絪胆?        "",                   //72
        "",                   //72
        "",//OS_ENGLISH,           //73    T:璣粂
        OS_ICON_VCD,          //74
        "",                   //75    //not use
        "",                   //76    //not use

        "",//OS_ICON_MP3,      //77(not use)

        OS_ICON_CDDA,         //78
        "48K",                   //79    //not use
        "96K",                   //80    //not use
        "192K",                   //81    //not use
        KOS_PICUP,             //82    T:礶簿
        KOS_PICDN,             //83    T:礶簿
        KOS_PICL,              //84    T:礶オ簿
        KOS_PICR,              //85    T:礶簿
        KOS_CHAPTER,           //86    T:彻竊
        KOS_ECHO,              //87    T:睼臫
        KOS_TITLE,             //88    T:夹肈
        KOS_BAND,              //89    T:繵眯
        KOS_VOL,               //90    T:秖
        "DOWN SAMPLE",        //91    //not use
        KOS_KEY,               //92    T:秸
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        KOS_9FRAME_1,          //94    T:虫Ρ礶
        KOS_AUTO_L,            //95    T:笆钡佰オ
        KOS_AUTO_R,            //96    T:笆钡佰
        "LOW",                //97    // LOW
        KOS_SEQUENCE,          //98    T:抖冀
        KOS_MENUPLAY,          //99    T:垫虫冀
        "",//OS_SFE_OUT,           //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else       
        "",//OS_SFE_STD,           //101
        "",//OS_SFE_EHNANCE,       //102
#endif      
        "MEDIUM",             //103   // MEDIUM
        KOS_PROG_PLAY,         //104   T:絪导僵
        "HIGH",               //105   // HIGH
        KOS_DYNAMICRANGE,      //106   T:笆篈絛瞅
        OS_ICON_DVD,          //107
        KOS_OSD,               //108   T:(礶陪ボ粂ē)
        OS_ICON_SUBT,         //109
        KOS_TV_RATIO,          //110   T:辊礶ゑㄒ
        KOS_TV_SYS,            //111   T:筿跌诀Α
        KOS_EXIT_MENU,         //112   T:癶砞竚垫虫
    #if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
    #else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        KOS_AUD_OUT,           //113   T:计絏块
    #endif
        KOS_VIDEO,             //114   T:跌繵块
        KOS_PASSWORD,          //115   T:盞絏
        KOS_RATING,            //116   T:
        "BITSTREAM",//KOS_BITSTREAM,         //117   T:SPDIF/方絏

        #if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
        #else
            "",//OS_ANALOG_6CH,                  //118
        #endif

        "SPDIF/PCM",          //119

        #if defined(SUPPORT_PALM)
            "PAL-M",                //120
        #else
            "",//OS_ANALOG_2CH,                  //120
        #endif
        #ifdef KSD_DVD//20030823
         #ifdef HANYANG_SETUPMENU   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
        #elif defined(EASTECH_DVI)
            "YCbCr", //121
        #else
        "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
         #endif  
        #else
        KOS_YUV,               //121   T:跌繵だ秖
        #endif
        KOS_AUTO,              //122   T:笆
        KOS_OFF,               //123   T:闽
        "",//"TM/CH/TL",           //124
        KOS_CHAPTER,           //125   T:彻竊
        KOS_TITLE,             //126   T:夹肈
        OS_ICON_ANGLE,        //127
      #if defined(HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU) //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
      #endif
        OS_16_9,              //129   T:16:9 --
        OS_4_3LB,             //130   T:4:3LB --
        OS_4_3PS,             //131
        "PAL",                //132
        "NTSC",               //133
        "PAL60",              //134

        #ifdef RATING_8
            "3 PG",               //135   T:level 3
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else
            "2",                  //136     T:level 2
            "1 G",                //137   T:level 1
            #endif
        #else
            KOS_NO_ADULT,          //135   T:(獶A)
            KOS_KID_ONLY,          //136   T:(ㄠ担)
            KOS_VIEW_ALL,          //137   T:(礚)
        #endif

        "6CH",//CLEAD_KOREAN OS_6CH_SETUP,                  //138

        KOS_SUBWOOFER,         //139   T:禬
        KOS_SATURATION,        //140   埂㎝
        "ON",//CLEAD_KOREAN OS_ON,                //141 
        OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
        KOS_CLEAR,             //145   T:睲埃
        "  T  C",               //146
        "--:--",              //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        KOS_EDIT,              //149   T:(絪胯)
        "",//OS_DIR1,              //150
        "",//OS_DIR2,              //151
        OS_DIR3,              //152
        OS_DIR4,              //153
        "PAL-NC",//OS_DIR5,              //154
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
        KOS_HUE,               //157   ︹秸
        "PROLOGIC",//"-:--:--",            //158
        "MOVIE",//OS_PL_MOVIE,//OS_TRK_S,             //159   //not use
        "MUSIC",//OS_PL_MUSIC,//OS_DISC_S,            //160  //not use
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//"TT:CH",              //161    //not use
        #endif

        #ifdef REMAIN_TIME//nono 2-7-12 20:06
            "T",                  //162
        #else
            "",//"BOOKMARK",           //162
        #endif

        OS_DIR0,              //163
        KOS_CONTRAST,          //164   癸ゑ
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
        "CANCEL",//OS_CH,                //168   T:(羘笵)
        KOS_BRIGHT_SETUP,      //169   獹
        "F/W ID",//OS_FIRMWARE_ID,       //170   T:(硁ン絪絏)
        "CHIP ID",//KOS_CHIP_ID,           //171   T:(絪絏)
        KOS_REGION_CODE,       //172   T:(跋絏)
        "MEMORY",//OS_FUNCTION,          //173   T:(滦弄滦佰)
        "DYNAMIC",//OS_MODE,              //174   T:(家Α)

        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

        "MIC VOL 1",//OS_MIC_VOL_1,             //178
        "MIC VOL 2",//OS_MIC_VOL_2,             //179
#ifdef SUPPORT_FUNCTION_MENU
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181 
#else
        "",//OS_LEVEL,             //180   T:(魁家Α)
        "",//OS_HIGH,              //181   T:(蔼珇借)
#endif
#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//OS_NORMAL,            //182   T:(禬丁)
#endif
        "",//OS_SUPER,             //183   T:(禬蔼珇借)
        "",//OS_OPERATING,         //184   T:(秸竊よΑ)
        "",//OS_MANUAL,            //185   T:(も笆)
        OS_DIR10,             //186
        OS_DIR11,             //187
        "CONCERT",//OS_CONCERT,           //188   T:(贾芔)
        "CHURCH",//OS_CHURCH,            //189   T:(毙绑)
        KOS_PASSIVE,           //190   T:(吏露)
        KOS_WIDE,              //191   T:(糴初)
//        "",//OS_AMPHITH,           //192   T:(蛾粿初)
//        "",//OS_STADIUM,           //193   T:(蔨▅繻)
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192    3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "EQ",//OS_EQ,                //194   T:(А颗)
        KOS_STANDARD,          //195   T:(夹非)
        KOS_CLASSIC,           //196   T:(ㄥ)
        "ROCK",//OS_ROCK,              //197   T:(穘簎)
        "JAZZ",//OS_JAZZ,              //198   T:(里)
        "POP",//OS_POP,               //199   T:(瑈︽)
        KOS_USER,              //200   T:(┦)
        "ATTRIB",//CLEAD_KOREANOS_ATTRIB,            //201   T:(┦)
        KOS_SF,                //202   T:(篊秈)
        "SB",//OS_SB,                //203   T:(篊癶)

            "C",                 //204   //show "C"


        KOS_CSPK,              //205   T:い竚喘羘竟
        KOS_SSPK,              //206   T:吏露喘羘竟
        "TV-RGB",              //207
        "4 PG13",             //208   S:辅导级
        KOS_CSPK_DELAY,        //209   T:い竚┑筐
        KOS_SSPK_DELAY,        //210   T:吏露┑筐
        KOS_FSPK,              //211   T:玡竚喘羘竟
        "VIDEO SETUP",//OS_VIDEO_SETUP,       //212   跌繵砞﹚
        "SHARPNESS",          //213   SHARPNESS
        KOS_SYS_SETUP,         //214   T:╰参砞竚
        KOS_SPK_SETUP,         //215   T:喘羘竟砞竚
        KOS_AUD_SETUP,         //216   T:繵砞竚
        KOS_DEFAULT_SETUP,     //217   T:
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "GROUP",//OS_GROUP,           //218   T:竤舱
        #endif
        
         #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU
        "   MNP   ",
        #else
        KOS_SSAVER_SETUP,      //219   T:辊玂臔
        #endif
        "SAVER 1",//OS_SSAVER_1,          //220   T:家Α 1

        "SAVER 2",//OS_SSAVER_2,          //221   T:(家Α 2)
        "SAVER 3",//OS_SSAVER_3,          //222   T:(家Α 3)

        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   T:(5保留)
        #endif
        "6 R",                //224   T:(限制级)

        "ERR DISC",//OS_ERR_DISC,          //225   S:错误碟片
        KOS_DIGITAL_SETUP,     //226   T:计絏砞竚
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        KOS_MIC_ONOFF,         //227   T:杠旦砞竚
        "MIC VOL",//OS_MIC_VOL,           //228   T:杠旦秖
        #endif
        KOS_CD_DEBUG,          //229   T:岿い       ------------- not use
        KOS_SMART_UPGRADE,     //230   T:醇ど
        KOS_UPGRADE_TO,        //231   T:どΘ
        KOS_UPGRADING,         //232   T:どい
        KOS_NOT_POWEROFF,      //233   T:づ闽诀
        KOS_REGION_0,          //234   T:0 跋
        KOS_REGION_1,          //235   T:1 跋
        KOS_REGION_2,          //236   T:2 跋
        KOS_REGION_3,          //237   T:3 跋
        KOS_REGION_4,          //238   T:4 跋
        KOS_LANG_SETUP,        //239   T:粂ē砞竚
        #ifdef SUPPORT_FUNCTION_MENU
	"DISPLAY",            //240
	#else
        "",                   //240   //not use
        #endif
        KOS_RETURN_MAIN_SETUP, //241   T:()
        KOS_AUDIO_LANG_SETUP,  //242   T:(繵粂ē)
        KOS_SUBTITLE_LANG_SETUP,//243  T:(辊粂ē)
        KOS_MENU_LANG_SETUP,   //244   T:(垫虫粂ē)
        KOS_DOWNMIX_SETUP,     //245   T:(睼家Α)
        KOS_RESTORE_SETUP,     //246   T:(確)
        "LT/RT",              //247
        "VSS",//OS_VSURROUND_SETUP,   //248   T:店览吏露羘
        KOS_DOLBY_OP_SETUP,    //249   T:块家Α
        KOS_DOLBY_LINE_SETUP,  //250   T:絬隔块
        KOS_DOLBY_RF_SETUP,    //251   T:RF 秸俱
        KOS_DUAL_MONO_SETUP,   //252   T:オ+
        KOS_MIX_MONO_SETUP,    //253   T:睼羘笵
        KOS_SURROUND_MODE,     //254   T:吏露家Α
        "PRE STOP",//OS_PRE_STOP,          //255   T:              S:准停止

//=====================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER

},
#endif

#ifdef USE_DANISH_OSD
//DANISH
{
        OS_NULL,              //0
        "NEJ"" ""SKIVE",            //1     T:(礚盒)
        "SVAGELIG"" ""INDTR""\xc6""DEN",                //2     T:(眤岿 hand)
        "SPOR",             //3     T:(Ρヘ)
        OS_ICON_SVCD,         //4
        "DE-INTERLACE",//OS_CHINESE,           //5     not use
        "\xc5""BNE",              //6     T:()
        "LUKKE",             //7     T:(闽)
        "SPILLE",              //8     T:(冀)
        "STR""\xd8""G"" ""5",          //9     T:(5 跋)
        "PAUSE",             //10    T:(既氨)
        "TILF""\xc6""LDIG",            //11    T:(繦诀冀)
        "IGEN",            //12    T:(確冀)
      "STOPPE",              //13    T:(氨ゎ)
        "SKRIDT",              //14    T:(˙秈)
        "UDV""\xc6""LGE",            //15    T:(匡拒)
        "L""\xc6""SE",              //16    T:(弄盒)
        "STR""\xd8""G"" ""6",          //17    T:(6 跋)
        "ANALOGI",          //18    T:(家览)
        "FREMADG""\xc5""ENDE",                //19    T:(е秈)
        "TILBAGE",                //20    T:(е癶)
        "N""\xc6""ST",              //21    T:(Ρ >>)

        OS_NULL,            //22

        "FOREG""\xc5""ENDE",              //23    T:(Ρ <<)

         OS_NULL,                     //24

        "INDKOMST",            //25    T:(垫虫)
        Ch_repx,              //26
        Ch_rep1,              //27
        Ch_repd,              //28
        "AFSTED",//Ch_vff,               //29    T:(礚)
        "MENU",              //30    T:(匡虫)
        "RIDSE",             //31    T:(だ计)
        "TEGN",              //32    T:(癘拘)
        "GR""\xc6""SSE",            //33    T:(聅凝)
        "PROG",//KOS_PROG,              //34    T:(絪)
        "SAVING LOGO...",                   //35    //not use
    "ALLE"" ""STOR"" ""TAL.",       //36    T:(家Α1)
#ifdef SDRAM_16Mb_Mode
       "GENT.",               //37    T:(確)
#else//SDRAM_16Mb_Mode
       "GENTAGELSE",               //37    T:(確)
#endif//SDRAM_16Mb_Mode
        "GENTAGE"" ""VEJVISER",           //38    T:(ヘ魁確)
        "GENTAGE"" ""1",             //39    T:(虫Ρ確)
        "GENTAGE"" ""ALLE",           //40    T:(盒確)
        "GENTAGE"" ""UDSTREGNING",           //41    T:(確)
        "ALLE"" ""LILLE"" ""TA.",       //42    T:(家Α2)
        //"8",                //43    S:(8保留)
        #ifdef FIX_RATING_8_DISPLAY
        "8"" ""VOKSEN",            //43
        #else
        "8",
        #endif
        "7 NC-17",            //44
        "G""\xc5""TIL",              //45    T:(穓)
        "FUGLESKARN",              //46    T:(繰)
#ifdef SDRAM_16Mb_Mode        
        "MONO"" ""VEN.",               //47    T:(オ羘笵)
        "MONO"" ""RET",               //48    T:(羘笵)
#else//SDRAM_16Mb_Mode        
        "MONO"" ""VENSTRE",               //47    T:(オ羘笵)
        "MONO"" ""RET",               //48    T:(羘笵)
#endif//SDRAM_16Mb_Mode
        "STEREO",            //49    T:(ミ砰羘)
        "",//KOS_CANCEL_MUTE,    //50    S:取消静音//not use
        "BO",              //51
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "DEGRADERE",                   //52    //not use
#endif
    "BLANDING",       //53    T:(家Α3)
        OS_ICON_CDROM,        //54
        "TID",              //55    T:丁
        "",                   //56    //not use
        "ZOOME",              //57    T:(糴)
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                    //58    //not use
#endif
        OS_ICON_LANG,         //59
       "INTDF""\xd8""RELSE",             //60    T:(苯磞)
        "OMGIVE",              //61    T:(吏露)
        "PRC",                //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "",//OS_PBC_OFF,           //63    T:抖冀
#endif
        "RANDOM CANCEL",//CLEAD_KOREAN OS_RANDOM OS_CANCEL,  //64    T:(繦诀冀)
    "BASS MODE",//KOS_BASS_MANAGEMENT,    //65    T:(家Α)

        "",//"POWER ON",                    //66

        "GENTAGE"" ""A",             //67    T:確A-
        "PC-VGA",               //"PC-VGA",           //68
        "GENTAGE"" ""A""-""B",            //69    T:確A-B
        "AB"" ""UDSTREGNING",//CLEAD_KOREAN OS_CANCEL OS_REP,     //70    T:確
        "PRG"" ""UDSTREGNING",//CLEAD KOREAN OS_PROG OS_CANCEL,    //71    T:絪胆?        "",                   //72
        "",                   //72                  //72
        "",//OS_ENGLISH,           //73    T:璣粂
        OS_ICON_VCD,          //74
        "",                   //75    //not use
        "",                   //76    //not use

        "",//OS_ICON_MP3,      //77(not use)

        OS_ICON_CDDA,         //78
        "48K",                   //79    //not use
        "96K",                   //80    //not use
        "192K",                   //81    //not use
         "ZOOME"" ""OP",             //82    T:礶簿
        "ZOOME"" ""DUN",             //83    T:礶簿
        "ZOOME"" ""VENSTRE",              //84    T:礶オ簿
        "ZOOME"" ""RET",              //85    T:礶簿
        "KAPITEL",           //86    T:彻竊
        "EKKO",              //87    T:睼臫
        "TITEL",             //88    T:夹肈
        "BANDE",              //89    T:繵眯
        "BIND",               //90    T:秖
        "DOWN SAMPLE",        //91    //not use
        "N""\xd8""GLE",               //92    T:秸
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        "9""RAMME""_""1",          //94    T:虫Ρ礶
       "AUTO"" ""VENSTRE",            //95    T:笆钡佰オ
        "AUTO"" ""RET",            //96    T:笆钡佰
        "LOW",                //97    // LOW
        "R""\xc6""KKEF""\xd8""LGE"" ""SPILLE",          //98    T:抖冀
        "MENU"" ""SPILLE",          //99    T:垫虫冀
        "",//OS_SFE_OUT,           //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else       
        "",//OS_SFE_STD,           //101
        "",//OS_SFE_EHNANCE,       //102
#endif      
        "MIDDEL",             //103   // MEDIUM
        "PRG"" ""SPILLE",         //104   T:絪导僵
    "N""\xd8""J",               //105   // HIGH
        "DYNAMISK"" ""R""\xc6"".",      //106   T:笆篈絛瞅
        
        OS_ICON_DVD,          //107
        "OSD"" ""SPROG",               //108   T:(礶陪ボ粂ē)
        OS_ICON_SUBT,         //109
        "TV"" ""SKRIVE",          //110   T:辊礶ゑㄒ
        "TV"" ""SYSTEM",            //111   T:筿跌诀Α
        "UDGANG"" ""OPS.",         //112   T:癶砞竚垫虫
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "AUDIO"" ""UDGANG",           //113   T:计絏块
#endif
        "VIDEO",             //114   T:跌繵块
        "KODEORD",          //115   T:盞絏
        "VURDERE",            //116   T:
        "BITSTREAM",//KOS_BITSTREAM,         //117   T:SPDIF/方絏

        #if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
        #else
            "",//OS_ANALOG_6CH,                  //118
        #endif

        "SPDIF/PCM",          //119

        #if defined(SUPPORT_PALM)
            "PAL-M",                //120
        #else
            "",//OS_ANALOG_2CH,                  //120
        #endif
        #ifdef KSD_DVD//20030823
         #ifdef HANYANG_SETUPMENU   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
        #else
        "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
         #endif  
        #else
        "SAMMEN.-YUV",               //121   T:跌繵だ秖
        #endif
        "AUTO",              //122   T:笆
        "AFSTED",               //123   T:闽
        "",//"TM/CH/TL",           //124
        "KAPITEL",           //125   T:彻竊
        "TITEL",             //126   T:夹肈
        OS_ICON_ANGLE,        //127
        "P-AFS""\xd8""."" ""YPBPR",             //128   T:P-SCAN
        OS_16_9,              //129   T:16:9 --
        OS_4_3LB,             //130   T:4:3LB --
        OS_4_3PS,             //131
        "PAL",                //132
        "NTSC",               //133
        "PAL60",              //134

        #ifdef RATING_8
            "3 PG",               //135   T:level 3
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else
            "2",                  //136     T:level 2
            "1 G",                //137   T:level 1
            #endif
        #else
            "NEJ"" ""VOKSEN",          //135   T:(獶A)
            "BARN"" ""SIKKER",          //136   T:(ㄠ担)
            "SYN"" ""ALLE",          //137   T:(礚)
        #endif

        "6CH",//CLEAD_KOREAN OS_6CH_SETUP,                  //138

        "UNDERBASH""\xd8""J.",         //139   T:禬
        "M""\xc6""TTELSE",        //140   埂㎝
        "OM",//CLEAD_KOREAN OS_ON,                //141 
        OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
        "KLAR",             //145   T:睲埃
        "  T  C",               //146
        "--:--",              //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "OPLAG",              //149   T:(絪胯)
        "",//"OS_DIR1",              //150
        "",//"OS_DIR2",              //151
        OS_DIR3,              //152
        OS_DIR4,              //153
        "PAL-NC",//OS_DIR5,              //154
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
        "L""\xd8""D",               //157   ︹秸
        "PROLOGIC",//"-:--:--",            //158
        "MOVIE",//OS_PL_MOVIE,//OS_TRK_S,             //159   //not use
        "MUSIC",//OS_PL_MUSIC,//OS_DISC_S,            //160  //not use
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//"TT:CH",              //161    //not use
        #endif

        #ifdef REMAIN_TIME//nono 2-7-12 20:06
            "T",                  //162
        #else
            "",//"BOOKMARK",           //162
        #endif

        OS_DIR0,              //163
        "KONTRAST",          //164   癸ゑ
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
        "KANAL",//OS_CH,                //168   T:(羘笵)
        "LYS",      //169   獹
        "F/W ID",//OS_FIRMWARE_ID,       //170   T:(硁ン絪絏)
        "SPLINT"" ""ID",           //171   T:(絪絏)
        "STR""\xd8""G",       //172   T:(跋絏)
        "MEMORY",//OS_FUNCTION,          //173   T:(滦弄滦佰)
        "DYNAMIC",//OS_MODE,              //174   T:(家Α)

        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

        "MIC VOL 1",//OS_MIC_VOL_1,             //178
        "MIC VOL 2",//OS_MIC_VOL_2,             //179
#ifdef SUPPORT_FUNCTION_MENU
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181 
#else
        "",//OS_LEVEL,             //180   T:(魁家Α)
        "",//OS_HIGH,              //181   T:(蔼珇借)
#endif
#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//OS_NORMAL,            //182   T:(禬丁)
#endif
        "",//OS_SUPER,             //183   T:(禬蔼珇借)
        "",//OS_OPERATING,         //184   T:(秸竊よΑ)
        "",//OS_MANUAL,            //185   T:(も笆)
        OS_DIR10,             //186
        OS_DIR11,             //187
        "KONCERT",//OS_CONCERT,           //188   T:(贾芔)
        "KIRKE",//OS_CHURCH,            //189   T:(毙绑)
        "PASSIV",           //190   T:(吏露)
        "BRED",              //191   T:(糴初)
//        "",//OS_AMPHITH,           //192   T:(蛾粿初)
//        "",//OS_STADIUM,           //193   T:(蔨▅繻)
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192    3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "LIGE",//OS_EQ,                //194   T:(А颗)
        "FANE",          //195   T:(夹非)
        "KLASSISK",           //196   T:(ㄥ)
        "RLLPPE",//OS_ROCK,              //197   T:(穘簎)
        "JAZZ",//OS_JAZZ,              //198   T:(里)
        "POP",//OS_POP,               //199   T:(瑈︽)
        "BRUGER",              //200   T:(┦)
        "TILL""\xc6""GGELSE",//CLEAD_KOREANOS_ATTRIB,            //201   T:(┦)
        "LANGSOM"" ""FREMED",                //202   T:(篊秈)
        "SB",//OS_SB,                //203   T:(篊癶)

            "C",                 //204   //show "C"


        "CENTRUM",              //205   T:い竚喘羘竟
        "AVLE",              //206   T:吏露喘羘竟
        "TV-RGB",              //207
        "4 PG13",             //208   S:辅导级
        "CENTRUM"" ""UDS""\xc6"".",        //209   T:い竚┑筐
        "AVLE"" ""UDS""\xc6""TTE",        //210   T:吏露┑筐
        "FORSIDE",              //211   T:玡竚喘羘竟
        "VIDEO SETUP",//OS_VIDEO_SETUP,       //212   跌繵砞﹚
        "SKARP",          //213   SHARPNESS
        "SYSTEM"" ""OPSTILLING",         //214   T:╰参砞竚
        "TALER"" ""OPSTILLING",         //215   T:喘羘竟砞竚
        "AUDIO"" ""OPSTILLING",         //216   T:繵砞竚
        "FORS""\xd8""MMELSE",     //217   T:
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "GROUP",//OS_GROUP,           //218   T:竤舱
        #endif
        #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU
        "   MNP   ",
        #else
       "SK""\xc6""RM"" ""BEVARE",      //219   T:辊玂臔
        #endif
        "SAVER 1",//OS_SSAVER_1,          //220   T:家Α 1

        "SAVER 2",//OS_SSAVER_2,          //221   T:(家Α 2)
        "SAVER 3",//OS_SSAVER_3,          //222   T:(家Α 3)

        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   T:(5保留)
        #endif
        "6 R",                //224   T:(限制级)

        "ERR DISC",//OS_ERR_DISC,          //225   S:错误碟片
       "DIGITALUR"" ""BEVARE",     //226   T:计絏砞竚
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "MIKR."" ""OPST.",         //227   T:杠旦砞竚
        "MIKR."" ""VOL.",//OS_MIC_VOL,           //228   T:杠旦秖
        #endif
        "CD"" ""GENERHRERVE",          //229   T:岿い       ------------- not use
        "SMERTE"" ""FORBEDRE",     //230   T:醇ど
        "FORBEDRE"" ""TIL"" ""V",        //231   T:どΘ
        "FORBEDRE",         //232   T:どい
        "NEJ"" ""KRAFT"" ""AF",      //233   T:づ闽诀
        "STR""\xd8""G"" ""0",          //234   T:0 跋
        "STR""\xd8""G"" ""1",          //235   T:1 跋
        "STR""\xd8""G"" ""2",          //236   T:2 跋
        "STR""\xd8""G"" ""3",          //237   T:3 跋
        "STR""\xd8""G"" ""4",          //238   T:4 跋
        "SPROG"" ""OPSTILLING",        //239   T:粂ē砞竚
        #ifdef SUPPORT_FUNCTION_MENU
	"DISPLAY",            //240
	#else
        "",                   //240   //not use
        #endif
        "HOVEDSIDE", //241   T:()
#if defined(BBK_DVD)
        /*"AUDIO"" ""SPROG",  //242   T:(繵粂ē)*/
        "AUDIO",  //242   T:(繵粂ē) axel 2004/1/27 03:58 eliminate "LANG"
        /*"UNDERT."" ""SPR.",//243  T:(辊粂ē)*/
        "UNDERT.",//243  T:(辊粂ē)
#else
        "AUDIO"" ""SPROG",  //242   T:(繵粂ē)
        "UNDERT."" ""SPR.",//243  T:(辊粂ē)
#endif
        "MENU"" ""SPROG",   //244   T:(垫虫粂ē)
        "DOWNMIX",     //245   T:(睼家Α)
        "ISTANDS""\xc6""TTE",     //246   T:(確)
        "VENSTRE/RET",              //247
        "VSS",//OS_VSURROUND_SETUP,   //248   T:店览吏露羘
        "UDGANG"" ""MANER",    //249   T:块家Α
        "LINIE"" ""UD",  //250   T:絬隔块
        "RF"" ""OMARBEJDE",    //251   T:RF 秸俱
        "DOBBELT"" ""MONO",   //252   T:オ+
        "BLANDE"" ""MONO",    //253   T:睼羘笵
        "OMGIVE"" ""MANER",     //254   T:吏露家Α
        "PRE STOP",//OS_PRE_STOP,          //255   T:              S:准停止

//=====================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER

},
#endif

#ifdef USE_NORWAY_OSD
//Norwegian 
{
        "",                   //0   3-12-1 23:49
        "INGEN DISK",            //1     T:(礚盒)            S:(无碟)
        #if defined(SKYWORTH_DVD)||defined(INVALID_DISPLAY_HAND)
        OS_NO,                 //  3-12-1 23:50
        #else
        "UGYLDIG ADGANG",        //2     T:(眤岿 hand)   S:(您按错了 HAND)
        #endif
        "SPOR",                //3   3-12-1 23:51    T:(Ρヘ)            S:(曲目)
        OS_ICON_SVCD,         //4    3-12-1 23:51
        "DE-INTERLACE",//"CHINESE",            //5   3-12-1 23:51
        "\xc5""PNE",               //6     T:()            S:(出仓)
        "LUKKE",              //7     T:(闽)            S:(关仓)
        "SPILLE",               //8     T:(冀)            S:(播放)
        "REGION 5",           //9     T:(5 跋)            S:(5区)
        "PAUSE",              //10    T:(既氨)            S:(暂停)
        "TILFELDIG",             //11    T:(繦诀冀)        S:(随即播放)
        "GJENOPPTA",             //12    T:(確冀)        S:(恢复播放)
        "STOPPE",               //13    T:(氨ゎ)            S:(停止)
        "SKRITTE",               //14    T:(˙秈)            S:(单步)
        "VELGE",             //15    T:(匡拒)            S:(选择)

        #if defined(FUSS_DVD)||defined(HUAJIA_DVD)||defined(HIMAGE_CARD_READER)||defined(MINTON_DVD)   //NONO 2-5-15 3:01
            "LADNING",        //16    T:(弄盒)            S:(读碟)
        #else
            "LESE",           //16    T:(弄盒)            S:(读碟)
        #endif

        "REGION 6",           //17    T:(6 跋)
        
        #ifdef NO_SPDIF
        "ANALOG",             //18    T:(家览)
        #else//NO_SPDIF
        "ANALOGISK",             //18    T:(家览)  3-12-1 23:55
        #endif//NO_SPDIF
        
        #ifdef HJ_APEX_FIX_SHOW_OSD
        "FF",            //19    T:(е秈)   3-12-1 23:56
        "FR",           //20    T:(е癶)    3-12-1 23:56
        #else//HJ_APEX_FIX_SHOW_OSD
        "FRAM",            //19    T:(е秈)
        "TILBAKE",           //20    T:(е癶)
        #endif//HJ_APEX_FIX_SHOW_OSD
        "NESTE",               //21    T:(Ρ >>)
        "SERVO DEBUG",                 //22   3-12-1 23:57
        "SISTE",               //23    T:(Ρ <<)

        "DIR",                     //24   3-12-1 23:58

        "RETUR",             //25    T:(垫虫)
        Ch_repx,              //26    // 3-12-1 23:58
        Ch_rep1,              //27    // 3-12-1 23:58
        Ch_repd,              //28     3-12-1 23:58
        "AV",                //29    T:(礚)              S:(无)
        "MENY",               //30    T:(匡虫)            S:(选单)
        "POENG",              //31    T:(だ计)            S:(分数)
        "BOKMERKE",               //32    T:(癘拘)            S:(记忆)
        "GJENNOMLESE",             //33    T:(聅凝)            S:(浏览)
        "PROG",               //34    T:(絪祘)            S:(编程)
        "SAVING LOGO...",                   //35    //not use   3-12-1 23:59
        "ALLE ST. H""\xd8""Y.",         //36  3-12-2 0:00   T:(家Α1)

#ifdef SDRAM_16Mb_Mode
        "REP.",                //37    T:(確)
#else//SDRAM_16Mb_Mode
        "REPETERE",                //37    T:(確)
#endif//SDRAM_16Mb_Mode
        "REPETERE VEILEDNING",            //38    T:(ヘ魁確)
        "REPETERE 1",              //39    T:(虫Ρ確)
        "REPETERE ALT",            //40    T:(盒確)
        "AVLYSE REPETISJON",         //41    T:(確)
        "ALLE LI. H""\xd8""Y.",         //42    T:(家Α2)
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43  
        #else//#ifdef HJ_APEX_FIX_SHOW_OSD
        "8 VOKSEN",            //43
        #endif//#ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",
        #endif
        "7 NC-17",            //44    T:(虫Ρ冀)
        "G""\xc5"" TIL",               //45    T:(穓)
        "TAUS",               //46    T:(繰)

#ifdef SDRAM_16Mb_Mode
        "MONO VEN.",             //47    T:(オ羘笵)
        "MONO H""\xd8""Y.",             //48    T:(羘笵)
#else//SDRAM_16Mb_Mode        
        "MONO VENSTRE",             //47    T:(オ羘笵)
        "MONO H""\xd8""YRE",             //48    T:(羘笵)
#endif//SDRAM_16Mb_Mode

        "STEREO",             //49    T:(ミ砰羘)
#ifdef HANYANG_MUTEOFF     //caohui 2004-5-13 15:59
        "MUTE OFF",                   //50    //not use
#else
        "DEMUTE",                   //50    //not use
#endif
        "DIREKTE",               //51    T:
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "AVLYSE TAUSHET",                   //52    //not use chang as demute
#endif
        "MIKSET H""\xd8""Y.",          //53    T:(家Α3)
        OS_ICON_CDROM,        //54   3-12-2 0:07
        "TID",               //55    T:(丁)            S:(时间)
#ifdef RECORD_KEY
        "THE DISC HAS RECORD POINT", //56  
#else
        "",                   //56    //not use  
#endif
        "LINES",               //57    T:(糴)            S:(放宽)
#ifdef RECORD_KEY
        "ENTER RECORD KEY WILL RESUME PLAY",//58
#elif defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                   //58    //not use   3-12-2 0:08
#endif      
        OS_ICON_LANG,         //59    3-12-2 0:08
        "VEILEDE",              //60    T:(苯磞)            S:(扫描)
        "OMRINGE",//"SURROUND",           //61    T:(吏露)            S:(环绕)
        "PBC",                //62
#ifdef RECORD_KEY
        "ELSE IT WILL SEQENCE PALY AFTER 5S",  //63   3-12-2 0:09
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "",            //63    T:(抖冀)  3-12-2 0:09
#endif     
        "RAND CANCEL",        //64   3-12-2 0:10  T:(繦诀冀)    S:(随即播放取消)
        "BASS MODELL",          //65    T:(家Α)

        "",                   //66   3-12-2 0:10

        "REPETERE A-",          //67    T:(確A-)          S:(重复 A   )
        #ifdef JIEKE_DVD
        "P-SCAN VGA",               //"PC-VGA",           //68
        #else
        "PC-VGA",               //"PC-VGA",           //68
        #endif
        "REPETERE A-B",         //69    T:(確A-B)       S:(重复播放A-B)
        "AVLYSE AB",         //70    T:(確)        S:(A-B取消)
        "AVLYSE PROGRAM",         //71    T:(絪胆)            S:(编程取消)
        "",                   //72   3-12-2 0:12
#ifdef ONE_KEY_PASS
        "ONE KEY PLAY",      //73   3-12-2 0:12
#else
        "",            //73    T:(璣粂)    3-12-2 0:12         S:(英文)
#endif
        OS_ICON_VCD,          //74  3-12-2 0:12
        "LIGHT MUSIC",                   //75    3-12-2 0:12  
        "ELECTRON",                   //76     3-12-2 0:13
        "CVBS",//OS_ICON_MP3,          //77    3-12-2 0:13
        OS_ICON_CDDA,         //78     3-12-2 0:13
        "48K",                   //79    //not use   3-12-2 0:13
        "96K",                   //80    //not use   3-12-2 0:13
        "192K",                   //81    //not use   3-12-2 0:13
        "LINSE OPPE",            //82    T:(礶簿)        S:(放大上)
        "LINSE NEDE",          //83    T:(礶簿)        S:(放大下)
        "LINSE VENSTRE",          //84    T:(礶オ簿)        S:(放大左)
        "LINSE H""\xd8""YRE",         //85    T:(礶簿)        S:(放大右)
        "KAPITTEL",                 //86    T:(彻竊)            S:(章节)
        "EKKO",               //87    T:(睼臫)            S:(混响)
        "TITTEL",                 //88    T:(夹肈)            S:(标题)
        "BAND",               //89    T:(繵眯)
        "VOLUM",                //90    T:(秖)            S:(音量)
        "DOWN SAMPLE",        //91    //not use   3-12-2 0:15
        "TONE",                //92    T:(秸)            S:(音调)

        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif

        "9 BILDE_1",           //94    T:(虫Ρ礶)      S:(单曲九画面)
        "AUTO VENSTRE",             //95    T:(笆钡佰オ)      S:(自动接唱左)
        "AUTO H""\xd8""YRE",             //96    T:(笆钡佰)      S:(自动接唱右)
        "LOW",                //97    // LOW  3-12-2 0:16

            "ORDENTLIG SPILLE",           //98    T:(抖冀)        S:(顺序播放)

        "MENY SPILLE",          //99    T:(垫虫冀)        S:(菜单播放)
#ifdef DIV_GOTO_DISPLAY
        "DISC TIME",          //100   3-12-2 0:17
#else
        "LFE OUT",            //100   3-12-2 0:17
#endif
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else
        "STANDARD",           //101    3-12-2 0:17
        "ENHANCE",            //102    3-12-2 0:18
#endif        
        "MEDIUM",             //103   // MEDIUM
#ifdef MINTON_DVD
        "PROG PLAY",           //104   3-12-2 0:18 T:(絪导僵)          S:(编程播放)
#else
        "PROGRAM SPILLE",           //104   T:(絪导僵)          S:(编程播放)
#endif
        "H""\xd8""Y",               //105   // HIGH
        "DYMAMISK OMF.",      //106
        OS_ICON_DVD,          //107   3-12-2 0:19
        "OSD SPR""\xc5""K",       //108   T:(礶陪ボ粂ē)    S:(画面显示语言)
        OS_ICON_SUBT,         //109  
        "TV TYPE",            //110   T:(辊礶ゑㄒ)    S:(屏幕画面比例)
        #ifdef MINTON_DVD  //heqiang，2004-2-29 10:16
        "TV MODUS",           //111    S:(电视机制式)
        #else
        "TV SYSTEM",          //111   T:(筿跌诀Α)      S:(电视机制式)
        #endif//MINTON_DVD
        "FORLATE OPPF""\xd8"".",         //112   T:(癶砞竚垫虫)    S:(推出设置菜单)
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)

        "AUDIO UTE",          //113   T:(计絏块)        S:(数码输出)
#endif
        "VIDEO",              //114   T:(跌繵块)        S:(视频输出)
        "PASSCODE",           //115   T:(盞絏)            S:(密码)

#ifdef GBM_RATING_SHOW_PARENTAL//GBM_FULL_FUNCTION      //gerry,2004-2-4 9:02
        "PARENTAL",//"RATING",             //116   3-12-2 0:21 T:()            S:(级别)
#else//GBM_RATING_SHOW_PARENTAL
        "GRADERING",             //116   T:()            S:(级别)
#endif//GBM_RATING_SHOW_PARENTAL

        "OP. FIBER/RAW",          //117   T:(SPDIF/方絏)      S:(SPDIF/源码)

        #if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
        #else
            "",              //118   T:(AC3 6羘笵)  3-12-2 0:22
        #endif

        "OP. FIBER/PCM",          //119

        #if defined(SUPPORT_PALM)
            "PAL-M",                //120
        #else
            "",              //120   3-12-2 0:23  T:(AC3 2羘笵)       S:AC3 2声道(not use)
        #endif

        #ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121    T:(跌繵だ秖)        S:(视频分量)
        #else//SHOW_YCbCr
        "SAMMENF.-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
        #endif//SHOW_YCbCr
        
        "AUTO",               //122   T:(笆)            S:(自动)
        "AV",                //123   T:(闽)              S:(关)
        "",           //124    3-12-2 0:23
        "KAPITTEL",            //125   T:(彻竊)            S:(章节)
        "TITTEL",              //126   T:(夹肈)            S:(标题)
        OS_ICON_ANGLE,        //127   3-12-2 0:24
        "P-SKAN. YPBPR",       //128   T:(硋︽跌繵だ秖)
        OS_16_9,              //129   T:(16:9 --)   3-12-2 0:24
        OS_4_3LB,             //130   T:(4:3LB --)  3-12-2 0:25
        OS_4_3PS,             //131  3-12-2 0:25
        "PAL",                //132
        "NTSC",               //133
        "PAL60",              //134

        #ifdef RATING_8
            "3 PG",               //135   T:(level 3)  3-12-2 0:26
            #ifdef FIX_RATING_8_DISPLAY  
            "2 G",                  //136   T:(level 2)   3-12-2 0:26
            "1 KID SAFE",                //137   T:(level 1)  3-12-2 0:26
            #else 
            "2",                  //136   T:(level 2)  3-12-2 0:26
            "1 G",                //137   T:(level 1)   3-12-2 0:26
            #endif
            
        #else
            "TIL. FOR ALLE",           //135   T:(辅导级)
            "UFA. FOR BARN",           //136   T:(保留)
            "INGEN GRENSER",           //137   T:(礚)
        #endif


        #if defined(SHOW_5_1CH)
            "5.1CH",              //138   3-12-2 0:27  T:(5.1羘笵)
        #else
            "6CH SETUP",          //138   3-12-2 0:27 T:(6羘笵砞竚)
        #endif

        "SUB BASSH""\xd8""Y.",          //139   T:(禬)
        "METNING",         //140   SATURATION
        "P""\xc5",                 //141   T:
        OS_DOBLY,             //142   3-12-2 0:28
        Ch_clock,             //143   3-12-2 0:28
        Ch_speaker,           //144   3-12-2 0:28
        "KLAR",              //145   T:(睲埃)
        "  T  C",               //146   3-12-2 0:29
        "--:--",              //147   3-12-2 0:29
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148   3-12-2 0:29
#else        
        "[--]",               //148   3-12-2 0:29
#endif        
        "REDIGERE",               //149   T:(絪胯)
        "",//OS_DIR1,              //150   3-12-2 0:30
        "",//OS_DIR2,              //151   3-12-2 0:30
        OS_DIR3,              //152   3-12-2 0:30
        OS_DIR4,              //153   3-12-2 0:30
        "PAL-NC",//OS_DIR5,              //154   3-12-2 0:30
        OS_LOCK,              //155   T:---- L  3-12-2 0:30
        OS_UNLOCK,            //156   T:---- U  3-12-2 0:30
        "FARGETONE",                //157   HUE
        "PROLOGIC",//"-:--:--",            //158    //not use   3-12-2 0:31
        "MOVIE MODE",//"TRACK SEARCH",       //159   //not use  3-12-2 0:31
        "MUSIC MODE",//"DISC SEARCH",        //160   //not use  3-12-2 0:31
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//TT:CH",               //161    //not use   3-12-2 0:31
        #endif

        #ifdef REMAIN_TIME//nono 2-7-12 20:06
            "T",                  //162     3-12-2 0:31
        #else  
            "",           //162   3-12-2 0:32
        #endif

        OS_DIR0,              //163   3-12-2 0:32
        "KONTRAST",           //164   CONTRAST
        OS_DIR7,              //165    3-12-2 0:32
        OS_DIR8,              //166    3-12-2 0:32
        OS_DIR9,              //167    3-12-2 0:32
        "KANAL",            //168   T:(羘笵)            S:(声道)
        "KLARHET",         //169   BRIGHTNESS
        "F/W ID",             //170   T:(硁ン絪絏)        S:(软件编码)
        "CHIP ID",            //171   T:(絪絏)        S:(芯片编码)
        "REGION",             //172   T:(跋絏)            S:(区码)
        "MEMORY",//"FUNCTION",           //173  //not use T:(滦弄滦佰)   3-12-2 0:33       S:(复读复唱)
        "DYNAMIC",//"MODE",               //174  //not use  T:(家Α)     3-12-2 0:33        S:(模式)


        "LIVELY",               //175   3-12-2 0:34
        "SHOWPLACE",            //176   3-12-2 0:34
        "MILD",                 //177   3-12-2 0:34

        "MIC1 VOL",//"COMPARE",            //178   3-12-2 0:35   //not use T:(癸ゑ)            S:(对比)
        "MIC2 VOL",//"COUNTER",            //179   3-12-2 0:35 //not use T:(滦Ω计)        S:(重复次数)

#ifdef FUSS_DVD_AVD276
        "PREV CHAPTER",      //180   3-12-2 0:35  S:上一章节
        "NEXT CHAPTER",      //181  not changed wsd 3-12-2 0:36  S:下一章节
//#elif defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#elif defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU) 
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181 
#else
        "",//"LEVEL",              //180   3-12-2 0:36 T:魁家Α        S:录音模式
        "",//"HIGH",               //181  3-12-2 0:36  T:蔼珇借          S:高品质
#endif

#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",             //182   3-12-2 0:36 T:(禬丁)        S:(超长时间)
#endif
#ifdef NEWSTYLE_WINDOW
        "PLAYTITLE",//"SUPER",              //183  3-12-2 0:36  T:(禬蔼珇借)        S:(超高品质)
        "TITLETIME",//"OPERATING",          //184  3-12-2 0:36  T:(秸竊よΑ)        S:(调节方式)
        "CHPTIME",//"MANUAL",             //185   3-12-2 0:36 T:(も笆)            S:(手动)
#else
        "",//"SUPER",              //183   3-12-2 0:36 T:(禬蔼珇借)        S:(超高品质)
        "",//"OPERATING",          //184   3-12-2 0:36 T:(秸竊よΑ)        S:(调节方式)
        "",//"MANUAL",             //185   3-12-2 0:36 T:(も笆)            S:(手动)
#endif

        OS_DIR10,             //186   3-12-2 0:36
        OS_DIR11,             //187   3-12-2 0:36
        "KONSERT",            //188   T:(贾芔)          S:(音乐厅)
        "KIRKE",             //189   T:(毙绑)            S:(教堂)
        "PASSIV",            //190   T:(吏露)            S:(环绕)
        "BRED",               //191   T:(糴初)            S:(宽场)
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192    3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "BALANSERT",                 //194   T:(А颗)            S:(均衡)
        "STANDARD",           //195   T:(夹非)            S:(标准)
        "KLASSISK",            //196   T:(ㄥ)            S:(古典)
        "ROCK",               //197   T:(穘簎)            S:(摇滚)
        "JAZZ",               //198   T:(里)            S:(爵士)
        "POP",                //199   T:(瑈︽)            S:(流行)
        "BRUKER",               //200   T:(┦)            S:(个性)
        "ATTRIB",             //201   T:(┦)            S:(个性)
        "LANGSOMT FRAM",                 //202   T:(篊秈)            S:(慢进)
        "SB",                 //203   T:(篊癶)    3-12-2 0:39         S:(慢退)

        "C",                  //204     3-12-2 0:39 //show "C"

       "SENTER",              //205   T:(い竚喘羘竟)      S:(中置扬声器)
        "BAKGRUNN",               //206   T:(吏露喘羘竟)      S:(环绕扬声器)
        #ifndef HIMAGE_RGB
        "TV-RGB",             //207
        #else
        "RGB",                    //207  3-12-2 0:40
        #endif
        "4 PG13",             //208   T:(辅导级)   3-12-2 0:40
        "SENTER TENUTO",       //209   T:(い竚┑筐)
        "BAK TENUTO",         //210   T:(吏露┑筐)
        "FRONT",              //211   T:(玡竚喘羘竟)
        "VIDEO SETUP",        //212   VIDEO SETUP   3-12-2 0:41
        "SKARPHET",          //213    SHARPNESS
        "SYS. OPPF""\xd8""RING",       //214   T:(╰参砞竚)        S:(系统设置)
        "H""\xd8""YTT. OPPF""\xd8""R.",      //215   T:(喘羘竟砞竚)      S:(扬声器设置)
        "AUDIO OPPF""\xd8""RING",        //216   T:(繵砞竚)        S:(音频设置)
        "MANGLENDE",            //217   T:()          S:(缺省值)
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "GRP",      //218
        #endif
#ifdef AUTO_PLAY
        "AUTO PLAY",       //219   3-12-2 0:43 T:(辊玂臔)        S:(屏幕保护)
#elif defined(VCD_CDG_PLAY_CONTROL_BY_SETUPMENU)
        "   MNP   ",
#else
        "SKJERM SPAR.",       //219  3-12-2 0:43  T:(辊玂臔)        S:(屏幕保护)
#endif
        "TYPE 1",             //220   3-12-2 0:43 T:(家Α 1)          S:(模式1)


        "TYPE 2",             //221    3-12-2 0:43  T:(家Α 2)          S:(模式2)
        "TYPE 3",             //222  3-12-2 0:43  T:(家Α 3)          S:(模式3)


        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223  3-12-2 0:43  S:(5保留)
        #else
        "5",                  //223   3-12-2 0:43 S:(5保留)
        #endif
        
        "6 R",                //224  3-12-2 0:43  S:(限制级)

        #ifdef NOT_SUPPROT_VCD
        "NOT SUPPORTED CD",           //225   3-12-2 0:43 S:(错误碟片)
        #else
        "ERR DISC",           //225   3-12-2 0:43 S:(错误碟片)
        #endif

        "DIG. OPPF""\xd8"".",      //226   T:(计絏砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "MIK OPPF""\xd8""RING",          //227   T:(杠旦砞竚)
        "MIK VOL",            //228   T:(杠旦秖)
        #endif
        "CD GJENFINNELSE",      //229   T:(岿い)     ------------- not use
        "DYKTIG FORFREMME",      //230   T:(醇ど)
        "FORFREMME TIL V ",      //231   T:(どΘ)   3-12-2 0:45
        "FORFREMME",          //232   T:(どい)
        "IKKE STR""\xd8""MME AV",      //233   T:(づ闽诀)
        "REGION 0",           //234   T:(0 跋)
        "REGION 1",           //235   T:(1 跋)
        "REGION 2",           //236   T:(2 跋)
        "REGION 3",           //237   T:(3 跋)
        "REGION 4",           //238   T:(4 跋)
        "SPR""\xc5""K OPPF""\xd8""RING",     //239   T:(粂ē砞竚)
#ifdef  JIEKE_DVD
        "GIEC",               //240   3-12-2 0:47
#elif defined(SUPPORT_FUNCTION_MENU)
	"DISPLAY",            //240
#else        
        "",                   //240   //not use   3-12-2 0:47
#endif      
        "HOVED SIDE",          //241   T:()
#ifndef BBK_DVD
        "AUDIO SPR""\xc5""K",         //242   T:(繵粂ē)
#else
        "AUDIO",         //242   T:(繵粂ē) axel 2004/1/27 03:58 eliminate "LANG"
#endif

#ifdef DISC_INFO_KEY  //fengjl  3-11-25 9:55
         /*"SUBP LANG",      //243   T:(辊粂ē)  3-12-2 0:48*/
         "SUBP",      //243   T:(辊粂ē)  3-12-2 0:48
#elif !defined(BBK_DVD)
        "UNDERT. SPR""\xc5""K",      //243   T:(辊粂ē)
#else
        /*"UNDERT. SPR""\xc5""K",      //243   T:(辊粂ē)*/
        "UNDERT.",      //243   T:(辊粂ē) axel 2004/1/27 03:58 eliminate "LANG"
#endif
        "MENY SPR""\xc5""K",          //244   T:(垫虫粂ē)
        "MIKSET MODELL",            //245   T:(睼家Α)
     
        "RESTAURERE",            //246   T:(確)
       
        "V MONO/H MONO",              //247
        "HY. OM. MONO",                //248   T:(店览吏露羘)      S:(虚拟环绕声)
        "YTELSE MODELL",            //249   T:(块家Α)        S:(输出模式)
        "LINJE UTE",           //250   T:(絬隔块)        S:(线路输出)
        "RF INNSTILLE",           //251   T:(RF 秸俱)         S:(RF调整)
        "DUELL MONO",          //252   T:(オ+)           S:(左+右)
        "MIKSET MONO",           //253   T:(睼羘笵)        S:(混合声道)
        "SURROUND OMRINGET MODELL",         //254   T:(吏露家Α)        S:(环绕模式)
#ifdef KSD_DVD
        "PRESS PLAY BUTTON TO CONTINUE",        //255  3-12-2 0:50  T:              S:请按播放键继续
#elif defined(DESAY_DVD)
        "PRESS PLAY BUTTON TO CONTINUE",  // 3-12-2 0:50
#else
        "PRE STOP",           //255   T:    3-12-2 0:50             S:(准停止)
#endif

//=====================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER

},
#endif

#ifdef USE_POLISH_OSD
//Polish
{

        "",                   //0
        "BRAL DYSKU",            //1     T:(礚盒)            S:(无碟)
        #if defined(SKYWORTH_DVD)||defined(INVALID_DISPLAY_HAND)
        OS_NO,
        #else
        "NIEPR.WEJ""\r\xa5""\r\xa0",        //2     T:(眤岿 hand)   S:(您按错了 HAND)
        #endif
     "\r\xa5""CIE""\r\xa6""KA",                //3     T:(Ρヘ)            S:(曲目)
        OS_ICON_SVCD,         //4
        "DE-INTERLACE",//"CHINESE",            //5  not use
        "OTW""\xd3""RZ",               //6     T:()            S:(出仓)
        "ZAMKNIJ",              //7     T:(闽)            S:(关仓)
        "ODTWARZAJ",               //8     T:(冀)            S:(播放)
        "REGION 5",           //9     T:(5 跋)            S:(5区)
        "PAUZA",              //10    T:(既氨)            S:(暂停)
        "PRZYPADKOWE",             //11    T:(繦诀冀)        S:(随即播放)
        "POWR""\xd3""\r\xa0",             //12    T:(確冀)        S:(恢复播放)
        "STOP",               //13    T:(氨ゎ)            S:(停止)
        "KROK",               //14    T:(˙秈)            S:(单步)
        "WYBIERZ",             //15    T:(匡拒)            S:(选择)

        #if defined(FUSS_DVD)||defined(HUAJIA_DVD)||defined(HIMAGE_CARD_READER)||defined(MINTON_DVD)   //NONO 2-5-15 3:01
            "ADUJ",        //16    T:(弄盒)            S:(读碟)
        #else
            "CZYTAJ",           //16    T:(弄盒)            S:(读碟)
        #endif

        "REGION 6",           //17    T:(6 跋)
        
        #ifdef NO_SPDIF
        "ANALOG",             //18    T:(家览)
        #else//NO_SPDIF
        "SPDIF/OFF",             //18    T:(家览)
        #endif//NO_SPDIF
        
        #ifdef HJ_APEX_FIX_SHOW_OSD
        "FF",            //19    T:(е秈)
        "FR",           //20    T:(е癶)
        #else//HJ_APEX_FIX_SHOW_OSD
        "DO PRZODU",            //19    T:(е秈)
        "DO T""\r\xa3""YU",           //20    T:(е癶)
        #endif//HJ_APEX_FIX_SHOW_OSD
        "NAST""\r\xa1""PNY",               //21    T:(Ρ >>)
        "",                 //22
        "POPRZEDNI",               //23    T:(Ρ <<)

        "DIR",                     //24

        "WR""\xd3""\r\xa0",             //25    T:(垫虫)
        Ch_repx,              //26
        Ch_rep1,              //27
        Ch_repd,              //28
        "WY""\r\xa3""\r\x9f""CZ",                //29    T:(礚)              S:(无)
        "MENU",               //30    T:(匡虫)            S:(选单)
        "PR""\r\xa1""DKO""\r\xa5""\r\xa0",              //31    T:(だ计)            S:(分数)
        "ZNAK",               //32    T:(癘拘)            S:(记忆)
        "WYSZUKAJ",             //33    T:(聅凝)            S:(浏览)
        "PROGRAM",               //34    T:(絪祘)            S:(编程)
        "",                   //35    //not use
        "G""\r\xa3"".DU""\r\xa6""E",         //36    T:(家Α1)
        "POWT.",                //37    T:(確)
        "POWT.KATALOG",            //38    T:(ヘ魁確)
        "POWT.1",              //39    T:(虫Ρ確)
        "POWT.WSZYSTKO",            //40    T:(盒確)
        "ODW.POWT.",         //41    T:(確)
        "G""\r\xa3"".MA""\r\xa3""E",         //42    T:(家Α2)
        #ifdef FIX_RATING_8_DISPLAY
            #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
            #else//#ifdef HJ_APEX_FIX_SHOW_OSD
            "8 DORS.""\r\xa3",            //43
            #endif//#ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",
        #endif
        "NC-17",            //44    T:(虫Ρ冀)
        "ID""\r\xa7"" DO",               //45    T:(穓)
        "WYCISZ",               //46    T:(繰)
        "KAN.LEWY",             //47    T:(オ羘笵)
        "KAN.PRAWY",             //48    T:(羘笵)
        "STEREO",             //49    T:(ミ砰羘)
        "ODW.WYC",                   //50    //not use
        "LIVE",               //51    T:
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "ODW.WYC",                   //52    //not use
#endif
        "G""\r\xa3"".WSZYSTKIE",          //53    T:(家Α3)
        OS_ICON_CDROM,        //54
        "CZAS",               //55    T:(丁)            S:(时间)
    #ifdef RECORD_KEY
    "THE DISC HAS RECORD POINT", //56
    #else
        "",                   //56    //not use
    #endif
       "ZOOM",               //57    T:(糴)            S:(放宽)
    #ifdef RECORD_KEY
    "ENTER RECORD KEY WILL RESUME PLAY",//58
    #elif defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
    #else
        "",                   //58    //not use
    #endif     
       OS_ICON_LANG,         //59
       "WST""\r\xa1""P",              //60    T:(苯磞)            S:(扫描)
       "SRND",//"SURROUND",           //61    T:(吏露)            S:(环绕)
       "VIDEO-CD",                //62
    #ifdef RECORD_KEY
    "ELSE IT WILL SEQENCE PALY AFTER 5S",  //63
    #elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
    #elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

    #else
       "",            //63    T:(抖冀)
    #endif     
       "RAND CANCEL",        //64    T:(繦诀冀)    S:(随即播放取消)
       "TRYB BAS",          //65    T:(家Α)


        "",                   //66
        "POWT.A",          //67    T:(確A-)          S:(重复 A    )
        #ifdef JIEKE_DVD
        "P-SCAN VGA",               //"PC-VGA",           //68
        #else
        "PC-VGA",               //"PC-VGA",           //68
        #endif
        "POWT.A-B",         //69    T:(確A-B)       S:(重复播放A-B)
        "ODW.AB",         //70    T:(確)        S:(A-B取消)
        "ODW.PROG.",         //71    T:(絪胆)            S:(编程取消)
        "",                   //72
    #ifdef ONE_KEY_PASS
    "ONE KEY PLAY",      //73
    #else
        "",            //73    T:(璣粂)            S:(英文)
    #endif
       OS_ICON_VCD,          //74
        "LIGHT MUSIC",                   //75    
        "ELECTRON",                   //76   
        "CVBS",//OS_ICON_MP3,          //77
        OS_ICON_CDDA,         //78
        "48K",                   //79    //not use
        "96K",                   //80    //not use
        "192K",                   //81    //not use
        "POW.G""\xd3""R.",            //82    T:(礶簿)        S:(放大上)
        "POW.D""\xd3""\r\xa3",          //83    T:(礶簿)        S:(放大下)
        "POW.LEW.",          //84    T:(礶オ簿)        S:(放大左)
        "POW.PEAW.",         //85    T:(礶簿)        S:(放大右)
        "KANA""\r\xa3",                 //86    T:(彻竊)            S:(章节)
        "ECHO",               //87    T:(睼臫)            S:(混响)
        "TYTU""\r\xa3",                 //88    T:(夹肈)            S:(标题)
        "PASMO",               //89    T:(繵眯)
        "G""\r\xa3""OS.",                //90    T:(秖)            S:(音量)
        "DOWN SAMPLE",        //91    //not use
        "KLUCZ",                //92    T:(秸)            S:(音调)

    #ifdef P_SCAN_ONLY_CHG_INT_MODE
    "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
    #else
       "S-VIDEO",            //93
       #endif

        "SCIE""\r\xa6""KI",           //94    T:(虫Ρ礶)      S:(单曲九画面)
        "AUTO L.",             //95    T:(笆钡佰オ)      S:(自动接唱左)
        "AUTO P.",             //96    T:(笆钡佰)      S:(自动接唱右)
        "LOW",                //97    // LOW

        "ODTW.FRAGM",           //98    T:(抖冀)        S:(顺序播放)

        "MENU ODTW.",          //99    T:(垫虫冀)        S:(菜单播放)
    #ifdef DIV_GOTO_DISPLAY
    "DISC TIME",          //100
    #else
        "LFE OUT",            //100
    #endif
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else
        "STANDARD",           //101
        "ENHANCE",            //102
#endif        
        "\r\xa3""REDNI",             //103   // MEDIUM
    #ifdef MINTON_DVD
        "PROG PLAY",           //104   T:(絪导僵)          S:(编程播放)
    #else
        "PRG.ODTW.",           //104   T:(絪导僵)          S:(编程播放)
    #endif
    "WYSOKI",               //105   // HIGH
        "ZAKRES",      //106
        OS_ICON_DVD,          //107
        "J""\r\xa1""Z.OSD",       //108   T:(礶陪ボ粂ē)    S:(画面显示语言)
        OS_ICON_SUBT,         //109
        "TYP TV",             //110   T:(辊礶ゑㄒ)    S:(屏幕画面比例)
        "SYST.TV",        //111   T:(筿跌诀Α)      S:(电视机制式)
        "WYJ.MENU",         //112   T:(癶砞竚垫虫)    S:(推出设置菜单)
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)

        "WYJ.AUDIO",          //113   T:(计絏块)        S:(数码输出)
#endif
        "WIDEO",              //114   T:(跌繵块)        S:(视频输出)
        "HAS""\r\xa3""O",           //115   T:(盞絏)            S:(密码)
        "KONTR.RODZ",             //116   T:()            S:(级别)
        "SPDIF/RAW",          //117   T:(SPDIF/方絏)      S:(SPDIF/源码)

        #if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
        #else
         "",              //118   T:(AC3 6羘笵)
        #endif

        "SPDIF/PCM",          //119

        #if defined(SUPPORT_PALM)
            "PAL-M",                //120
        #else
            "",              //120   T:(AC3 2羘笵)       S:AC3 2声道(not use)
        #endif

#ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
#else
        "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
#endif//SHOW_YCbCr
        
        "AUTO",               //122   T:(笆)            S:(自动)
        "WY""\r\xa3",                //123   T:(闽)              S:(关)
        "",           //124
        "ROZDZ.",            //125   T:(彻竊)            S:(章节)
        "TYTU""\r\xa3",              //126   T:(夹肈)            S:(标题)
        OS_ICON_ANGLE,        //127
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
        OS_16_9,              //129   T:(16:9 --)
        OS_4_3LB,             //130   T:(4:3LB --)
        OS_4_3PS,             //131
        "PAL",                //132
        "NTSC",               //133
        "PAL60",              //134

        #ifdef RATING_8
        "3 PG",               //135   T:(level 3)
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else
            "2",                  //136   T:(level 2)
            "1 G",                //137   T:(level 1)
            #endif
            
        #else
            "ODW.DOROS""\r\xa3",           //135   T:(辅导级)
            "DLA DZIECI",           //136   T:(保留)
            "DLA WSZYST.",           //137   T:(礚)
        #endif


        #if defined(SHOW_5_1CH)
            "5.1CH",              //138   T:(5.1羘笵)
        #else
            "6CH SETUP",          //138   T:(6羘笵砞竚)
        #endif

        "G""\r\xa3"".NISKOT",          //139   T:(禬)
        "NASYCENIE",         //140   SATURATION
        "W""\r\xa3""ACZ",                 //141   T:
        OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
        "WYCZY""\r\xa5""\r\xa0",              //145   T:(睲埃)
        "  T  C",               //146
        "--:--",              //147
    #ifdef  MP3_DIRECT_SELECT
        " ----",               //148
    #else        
        "[--]",               //148
    #endif        
        "EDYTUJ",               //149   T:(絪胯)
        "",//OS_DIR1,              //150
        "",//OS_DIR2,              //151
        OS_DIR3,              //152
        OS_DIR4,              //153
       "PAL-NC", //OS_DIR5,              //154
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
        "BARWA",                //157   HUE
        "PROLOGIC",//"-:--:--",            //158    //not use
        "MOVIE MODE",//"TRACK SEARCH",       //159   //not use
        "MUSIC MODE",//"DISC SEARCH",        //160   //not use
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//TT:CH",               //161    //not use
        #endif

        #ifdef REMAIN_TIME//nono 2-7-12 20:06
        "T",                  //162
        #else
        "",           //162
        #endif

        OS_DIR0,              //163
        "KONTRAST",           //164   CONTRAST
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
        "KANA""\r\xa3",            //168   T:(羘笵)            S:(声道)
        "JASNO""\r\xa5""\r\xa0",         //169   BRIGHTNESS
        "WERSJA OPR",             //170   T:(硁ン絪絏)        S:(软件编码)
        "CHIP",            //171   T:(絪絏)        S:(芯片编码)
        "REGION",             //172   T:(跋絏)            S:(区码)
        "MEMORY",//"FUNCTION",           //173  //not use T:(滦弄滦佰)        S:(复读复唱)
        "DYNAMIC",//"MODE",               //174  //not use  T:(家Α)            S:(模式)


        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

    "MIC1 VOL",//"COMPARE",            //178   //not use T:(癸ゑ)            S:(对比)
       "MIC2 VOL",//"COUNTER",            //179   //not use T:(滦Ω计)        S:(重复次数)

    #ifdef FUSS_DVD_AVD276
        "PREV CHAPTER",      //180   S:上一章节
        "NEXT CHAPTER",      //181   S:下一章节
//  #elif defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
    #elif defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
    "NEXT PAGE",                //180
    "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
    #elif defined(SUPPORT_FUNCTION_MENU) 
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181 
    #else
        "",//"LEVEL",              //180   T:魁家Α        S:录音模式
        "",//"HIGH",               //181   T:蔼珇借          S:高品质
    #endif
#ifdef SUPPORT_IR_I2P_KEY 
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
    "",//"NORMAL",             //182   T:(禬丁)        S:(超长时间)
#endif
    #ifdef NEWSTYLE_WINDOW
        "PLAYTITLE",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "TITLETIME",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "CHPTIME",//"MANUAL",             //185   T:(も笆)            S:(手动)
    #else
        "",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "",//"MANUAL",             //185   T:(も笆)            S:(手动)
    #endif

        OS_DIR10,             //186
        OS_DIR11,             //187
        "KONCERT.",            //188   T:(贾芔)          S:(音乐厅)
        "KO""\r\xa5""CIEL",             //189   T:(毙绑)            S:(教堂)
        "PASYWNY",            //190   T:(吏露)            S:(环绕)
        "SZEROKI",               //191   T:(糴初)            S:(宽场)
    #ifdef USER_MPEG_LOGO
    "SELECT LOGO",          //192
    "MPEG LOGO",            //193
    #else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)
        "",//OS_STADIUM,           //193   T:(蔨▅繻)
    #endif
        "MIKSER",                 //194   T:(А颗)            S:(均衡)
        "STANDARD.",           //195   T:(夹非)            S:(标准)
        "KLASYCZ.",            //196   T:(ㄥ)            S:(古典)
        "ROCK",               //197   T:(穘簎)            S:(摇滚)
        "JAZZ",               //198   T:(里)            S:(爵士)
        "POP",                //199   T:(瑈︽)            S:(流行)
        "W""\r\xa3""ASNE",               //200   T:(┦)            S:(个性)
        "ATRYB.",             //201   T:(┦)            S:(个性)
        "ZWOLN.",                 //202   T:(篊秈)            S:(慢进)
        "SB",                 //203   T:(篊癶)            S:(慢退)

        "C",                  //204   //show "C"

       "CENTER.",              //205   T:(い竚喘羘竟)      S:(中置扬声器)
        "TY""\r\xa3",               //206   T:(吏露喘羘竟)      S:(环绕扬声器)
        #ifndef HIMAGE_RGB
        "TV-RGB",             //207
        #else
        "RGB",                    //207
        #endif
        "4 PG13",             //208   T:(辅导级)
        "OP""\xd3""\r\xa7"".G""\r\xa3"".CENT",       //209   T:(い竚┑筐)
        "OP""\xd3""\r\xa7"".G""\r\xa3"".TYL",         //210   T:(吏露┑筐)
        "PRZ""\xd3""D.",              //211   T:(玡竚喘羘竟)
        "VIDEO SETUP",        //212   VIDEO SETUP
        "OSTRO""\r\xa5""\r\xa0",          //213   SHARPNESS
        "UST.SYST.",       //214   T:(╰参砞竚)        S:(系统设置)
        "UST.G""\r\xa3""O""\r\xa5"".",      //215   T:(喘羘竟砞竚)      S:(扬声器设置)
        "UST.AUDIO",        //216   T:(繵砞竚)        S:(音频设置)
        "DOMY""\r\xa5""LNE",            //217   T:()          S:(缺省值)
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "GRP",          //218   
        #endif
    #ifdef AUTO_PLAY
        "AUTO PLAY",       //219   T:(辊玂臔)        S:(屏幕保护)
    #elif defined(VCD_CDG_PLAY_CONTROL_BY_SETUPMENU)
        "   MNP   ",
    #else
        "WYGASZACZ",       //219   T:(辊玂臔)        S:(屏幕保护)
    #endif
        "TYPE 1",             //220   T:(家Α 1)          S:(模式1)

        "TYPE 2",             //221   T:(家Α 2)          S:(模式2)
        "TYPE 3",             //222   T:(家Α 3)          S:(模式3)


    #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   S:(5保留)
        #endif
        
        "6 R",                //224   S:(限制级)

        #ifdef NOT_SUPPROT_VCD
        "NOT SUPPORTED CD",           //225   S:(错误碟片)
        #else
        "ERR DISC",           //225   S:(错误碟片)
        #endif

        "UST.CYFR.",      //226   T:(计絏砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "UST.MIKR.",          //227   T:(杠旦砞竚)
        "G""\r\xa3""O""\r\xa5"".MIKR.",            //228   T:(杠旦秖)
        #endif
        "IDENT.CD",      //229   T:(岿い)     ------------- not use
        "UAKT.OPR.",      //230   T:(醇ど)
        "UAKT.DO WERS.",      //231   T:(どΘ)
        "UAKTUAL.",          //232   T:(どい)
        "NIE WY""\r\xa3""ACZ.",      //233   T:(づ闽诀)
        "REGION 0",           //234   T:(0 跋)
        "REGION 1",           //235   T:(1 跋)
        "REGION 2",           //236   T:(2 跋)
        "REGION 3",           //237   T:(3 跋)
        "REGION 4",           //238   T:(4 跋)
        "UST.J""\r\xa1""Z.",     //239   T:(粂ē砞竚)
    #ifdef  JIEKE_DVD
        "GIEC",               //240
    #elif defined(SUPPORT_FUNCTION_MENU)
	"DISPLAY",            //240
    #else        
        "",                   //240   //not use
    #endif      
        "STRONA G""\r\xa3"".",          //241   T:()
        "J""\r\xa1""Z.AUDIO",         //242   T:(繵粂ē)
        "J""\r\xa1""Z.NAPIS.",      //243   T:(辊粂ē)
        "MENU J""\r\xa1""Z.",          //244   T:(垫虫粂ē)
        "5.1 DO STEREO",            //245   T:(睼家Α)
     
        "PRZYWR""\xd3""\r\xa0",            //246   T:(確)
       
        "PRZESTRZ.",              //247
        "PSEUDO 5.1",                //248   T:(店览吏露羘)      S:(虚拟环绕声)
        "STAND.WYJ""\r\xa5""\r\xa0"".",            //249   T:(块家Α)        S:(输出模式)
        "WYJ""\r\xa5""CIE",           //250   T:(絬隔块)        S:(线路输出)
        "ZMIANA RF",           //251   T:(RF 秸俱)         S:(RF调整)
        "PODW.MONO",          //252   T:(オ+)           S:(左+右)
        "PO""\r\xa3""CZ.MONO",           //253   T:(睼羘笵)        S:(混合声道)
        "TRYB.D""\r\xa7""W.PRZESTRZ.",         //254   T:(吏露家Α)        S:(环绕模式)
    #ifdef KSD_DVD
    "PRESS PLAY BUTTON TO CONTINUE",        //255   T:              S:请按播放键继续
    #elif defined(DESAY_DVD)
        "PRESS PLAY BUTTON TO CONTINUE",
    #else
        "PRE STOP",           //255   T:                S:(准停止)
    #endif

//=====================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER

},
#endif


#ifdef USE_THAI_OSD//jxlan  07/19
//THAI
{
        "NULL",              //0
        "NODISC",            //1     T:(礚盒)
        "INVALID KEY",               //2     T:(眤岿 hand)
        "TRK",             //3     T:(Ρヘ)
        OS_ICON_SVCD,         //4
        "DE-INTERLACE",//OS_CHINESE,  //5     not use
        COS_OPEN,              //6     T:()
        COS_CLOSE,             //7     T:(闽)
        COS_PLAY,              //8     T:(冀)
        "REGION 5",          //9     T:(5 跋)
        COS_PAUSE,             //10    T:(既氨)
        "RANDOM",            //11    T:(繦诀冀)
        COS_RESUME,            //12    T:(確冀)
        COS_STOP,              //13    T:(氨ゎ)
        COS_STEP,              //14    T:(˙秈)
        COS_SELECT,            //15    T:(匡拒)
           COS_READ,              //16    T:(弄盒)
        "REGION 6",          //17    T:(6 跋)
        "SPDIF/OFF",          //18    T:(家览)
        
        COS_FORWARD,            //19    T:(е秈)
        COS_BACKWARD,           //20    T:(е癶)
        
         COS_NEXT,              //21    T:(Ρ >>)
       #ifdef Ti3001_OSD_UI_2
            "AMP SETUP1",           //22
        #else
            #ifdef SVA_SAMPLE
                "AMPVOL",           //22
            #else
                "",                 //22
            #endif
        #endif

        COS_PREV,              //23    T:(Ρ <<)

        "DIR",//OS_NULL,       //24

        COS_RETURN,            //25    T:(垫虫)
        Ch_repx,              //26
        Ch_rep1,              //27
        Ch_repd,              //28
        COS_OFF,              //29    T:(礚)
        "MENU",              //30    T:(匡虫)
        "SCORE",             //31    T:(だ计)
        "MARK",              //32    T:(癘拘)
        "BROWSE",            //33    T:(聅凝)
        COS_PROG,              //34    T:(絪)
        "",                  //35    S:画面抓取中
        COS_ALL_LG_SPK,        //36    T:(家Α1)
        COS_REP,               //37    T:(確)
        "REP DIR",           //38    T:(ヘ魁確)
        COS_REP_1,              //39    T:(虫Ρ確)
        COS_REP_ALL,           //40    T:(盒確)
        "REP CANCEL",           //41    T:(確)
        COS_ALL_SM_SPK,       //42    T:(家Α2)
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
          	"8 BYPASS",            //43
          #else//#ifdef HJ_APEX_FIX_SHOW_OSD
            "8 ADULT",            //43
          #endif//#ifdef HJ_APEX_FIX_SHOW_OSD
          #else
             "8",
        #endif
        "7 NC-17",            //44
        "GOTO",              //45    T:(穓)
        COS_MUTE,              //46    T:(繰)
        COS_MONO_L,               //47    T:(オ羘笵)
        COS_MONO_R,            //48    T:(羘笵)
        COS_STEREO,            //49    T:(ミ砰羘)
        "DEMUTE",              //50    S:取消静音//not use
        COS_LIVE,              //51
       #ifdef SELECT_MEDIA_IN_SETUPMENU
        "DISC",               //52
        #else
            "",                   //52    //not use
       #endif
        COS_MIXED_SPK,       //53    T:(家Α3)
        OS_ICON_CDROM,        //54
        "TIME",              //55    T:丁

        "",                   //56    //not use
        COS_ZOOM,              //57    T:(糴)
        "",//OS_CANCEL,            //58    T:

        OS_ICON_LANG,         //59
        "INTRO",             //60    T:(苯磞)
        "SURD",              //61    T:(吏露)
        "PBC",                //62

        "",//OS_PBC_OFF,           //63    T:抖冀
        "RAND CANCEL",  //64    T:(繦诀冀)
        COS_BASS_MODE,   //65 "BASS MANAGEMENT"   T:(家Α)
        #ifdef Ti3001_OSD_UI_2
            "AMP FRONT",                   //66
        #else
            "",                   //66
        #endif
        COS_REPEAT_A,             //67    T:確A-
        COS_PC_VGA,               //68
        COS_REPEAT_A_B,            //69    T:確A-B
        "A-B CANCEL",    //70    T:確
        "PRG CANCEL",    //71    T:絪胆?        "",                   //72
        "",              //72
        "",              //73 
        OS_ICON_VCD,          //74
        "",                     //75
        "",           //76   //zhaoyanhua add 03-10-28 21:37 //not use
        "",//OS_ICON_MP3,      //77
        OS_ICON_CDDA,         //78
        "48KHZ",                   //79    //not use
        "96KHZ",                   //80    //not use
        "192KHZ",                   //81    //not use
        COS_ZOOM_UP,                //82    T:礶簿
        COS_ZOOM_DOWN,              //83    T:礶簿
        COS_ZOOM_LEFT,              //84    T:礶オ簿
        COS_ZOOM_RIGHT,             //85    T:礶簿
        COS_CH,           //86    T:彻竊
        COS_ECHO,              //87    T:睼臫
        "TT",              //88    T:夹肈
        "BAND",            //89    T:繵眯
         COS_VOL,          //90    T:秖
        "DOWN SAM",        //91    //not use
        COS_KEY,             //92    T:秸    
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #else
        "S_VIDEO",           //93
        #endif
        
        "9FRAME_1",          //94    T:虫Ρ礶
        COS_AUTO_L,            //95    T:笆钡佰オ
        COS_AUTO_R,            //96    T:笆钡佰
        "LOW",                //97    // LOW
        "SEQ PLAY",          //98    T:抖冀
        "MENU PLAY",          //99    T:垫虫冀
        "LFE OUT",         //100
        "STANDARD",//OS_SFE_STD,           //101
        "ENHANCE",//OS_SFE_EHNANCE,       //102
        "MEDIUM",             //103   // MEDIUM
       #ifdef MINTON_DVD
        "PROG PLAY",           //104   T:(絪导僵)          S:(编程播放)
       #else
        "PRG PLAY",           //104   T:(絪导僵)          S:(编程播放)
       #endif
        "HIGH",               //105   // HIGH
        COS_DYNAMICRANGE,      //106   T:笆篈絛瞅
        OS_ICON_DVD,          //107
        COS_OSD_LANGUAGE,               //108   T:(礶陪ボ粂ē)
        OS_ICON_SUBT,         //109
        COS_TV_TYPE,          //110   T:辊礶ゑㄒ
        COS_TV_SYSTEM,            //111   T:筿跌诀Α
        COS_EXIT_SETUP,         //112   T:癶砞竚垫虫
        COS_AUDIO_OUT,           //113   T:计絏块
        COS_VIDEO,             //114   T:跌繵块
        COS_PASSWORD,          //115   T:盞絏
        COS_RATING,            //116   T:
        "SPDIF/RAW",         //117   T:SPDIF/方絏
        #if defined(Ti3001_OSD_UI_2) || defined(Ti3001_OSD_UI_1) || defined(Ti5026_OSD_UI_1)
            "AMP CENTER",           //118
        #elif defined( SVA_DVD)
            "",            //118   T:(AC3 5.1羘笵)
        #else
            "",              //118   T:(AC3 6羘笵)
        #endif

        "SPDIF/PCM",          //119

       #if defined(Ti3001_OSD_UI_2) || defined(Ti3001_OSD_UI_1) || defined(Ti5026_OSD_UI_1)
            "AMP SUBWOOFER",        //120
        #else
            "",              //120   T:(AC3 2羘笵)       S:AC3 2声道(not use)
        #endif
        COS_INTERLACE,               //121   T:(跌繵だ秖)        S:(视频分量)
        COS_AUTO,              //122   T:笆
        COS_OFF,               //123   T:闽
        "",//"TM/CH/TL",           //124
        "CHAPTER",           //125   T:彻竊
        "TITLE",             //126   T:夹肈
        OS_ICON_ANGLE,              //127
        COS_P_SCAN_YPBPR,       //128   T:(硋︽跌繵だ秖)
        "16 9",              //129   T:16:9 --
        "4 3LB",             //130   T:4:3LB --
        "4 3PS",             //131
        "PAL",                //132
        "NTSC",               //133
        "PAL60",              //134

        #ifdef RATING_8
            "3 PG",               //135   T:level 3
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else             
            "2",                  //136     T:level 2
            "1 G",                //137   T:level 1
            #endif
        #else
            COS_NO_ADULT,          //135   T:(獶A)
            COS_KID_SAFE,          //136   T:(ㄠ担)
            COS_VIEW_ALL,          //137   T:(礚)
        #endif
        COS_5_1CH,              //138   T:(5.1羘笵)

        COS_SUBWOOFER,         //139   T:禬
        COS_SATURATION,        //140   埂㎝
        COS_ON,                //141   T:秨
        OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
        "CLEAR",             //145   T:睲埃
        "  T  C",               //146  //2004-2-23 03:57张宇P
        "--:--",              //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "EDIT",              //149   T:(絪胯)
        
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42,(Thai).
        COS_SUBTITLE_2ND_LANG,    //150
#else
        OS_DIR1,//OS_DIR1,              //150
#endif   
        
        OS_DIR2,//OS_DIR2,              //151
        OS_DIR3,              //152
        OS_DIR4,              //153
        OS_DIR5,//OS_DIR5,    //154
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
        COS_HUE,               //157   ︹秸

#ifdef BBK_NEW_SETUP
        "PROLOGIC II",   //"-:--:--",            //158  
#else
        "PROLOGIC",//"-:--:--",            //158
#endif      
        "PL MOVIE",//OS_TRK_S,             //159   //not use
        "PL MUSIC",//OS_DISC_S,            //160  //not use

        #if defined(SUPPORT_IR_I2P_KEY)
        COS_INTERLACE,"YUV",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//"TT_CH",              //161    //not use
        #endif
        "",//"BOOKMARK",           //162


         OS_DIR0,              //163
        COS_CONTRAST,          //164   癸ゑ
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
        COS_CH,                //168   T:(羘笵)
        COS_BRIGHTNESS,      //169   獹
        "F/W ID",       //170   T:(硁ン絪絏)
        "CHIP ID",           //171   T:(絪絏)
        "REGION",       //172   T:(跋絏)
        "MEMORY",//OS_FUNCTION,          //173   T:(滦弄滦佰)
        "DYNAMIC",//OS_MODE,              //174   T:(家Α)

         #if defined(Ti3001_OSD_UI_2) || defined(Ti3001_OSD_UI_1) || defined(Ti5026_OSD_UI_1)
        "AMP FBALANCE",       //175
        "AMP SURROUND",       //176
        "AMP SBALANCE",       //177
        #elif 1//defined(SUNPLUS_DVD)
		"LIVELY",				//175
		"SHOWPLACE",	   		//176
		"MILD",			   		//177
        #else
        "",//"RECORD",             //175   //not use T:滦佰              S:(复唱)
        "",//"STUDY",              //176   //not use T:滦弄              S:(复读)
        "",//"FOLLOW",             //177   //not use T:蛤弄              S:(跟读)
        #endif

        "MIC1 VOL",               //178
        "MIC2 VOL",               //179

        //#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
        #ifdef FUSS_DVD_AVD276
        "PREV CHAPTER",      //180   S:上一章节
        "NEXT CHAPTER",      //181   S:下一章节
        #elif defined(SAME_DISC_RESUME)
		"NEXT PAGE",				//180
		"PREV PAGE",				//181
        #else
        "",//"LEVEL",              //180   T:魁家Α        S:录音模式
        "",//"HIGH",               //181   T:蔼珇借          S:高品质
        #endif    
        "",//"NORMAL",            //182   T:(禬丁)
        #ifdef NEWSTYLE_WINDOW
        "PLAYTIME",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "TITLETIME",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "CHPTIME",//"MANUAL",             //185   T:(も笆)            S:(手动)
        #else
        "",//OS_SUPER,             //183   T:(禬蔼珇借)
        "",//OS_OPERATING,         //184   T:(秸竊よΑ)
        "",//OS_MANUAL,            //185   T:(も笆)
        #endif 
        OS_DIR10,             //186
        OS_DIR11,             //187
        "CONCERT",           //188   T:(贾芔)
        COS_CHURCH,            //189   T:(毙绑)
        "PASSIVE",           //190   T:(吏露)
        COS_WIDE,              //191   T:(糴初)
        #ifdef USER_MPEG_LOGO
        "SELECT LOGO",         //192
        "MPEG LOGO",           //193
        #else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)
        "",//OS_STADIUM,           //193   T:(蔨▅繻)
        #endif
        "EQ",                //194   T:(А颗)
        "STANDARD",          //195   T:(夹非)
        "CLASSIC",           //196   T:(ㄥ)
        "ROCK",              //197   T:(穘簎)
        "JAZZ",              //198   T:(里)
        "POP",               //199   T:(瑈︽)
        "USER",              //200   T:(┦)
        "ATTRIB",            //201   T:(┦)
        "SF",                //202   T:(篊秈)
        "SB",                //203   T:(篊癶)

         "C",                 //204   //show "C"


        "CENTER",              //205   T:い竚喘羘竟
        "REAR",              //206   T:吏露喘羘竟
        #ifndef NINTAUS_OSD_STR
        "TV-RGB",              //207
        #else
        "RGB",
        #endif
        
        "4 PG13",             //208   S:辅导级
        COS_CENTER_DELAY,        //209   T:い竚┑筐
        COS_REAR_DELAY,        //210   T:吏露┑筐
        "FRONT",              //211   T:玡竚喘羘竟
        COS_VIDEO_SETUP,       //212   跌繵砞﹚
        "SHARPNESS",          //213   SHARPNESS
        COS_SYSTEM_SETUP,         //214   T:╰参砞竚
        COS_SPEAKER_SETUP,         //215   T:喘羘竟砞竚
        COS_AUDIO_SETUP,         //216   T:繵砞竚
        COS_DEFAULT,     //217   T:
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "GRP",           //218   
        #endif
        
        COS_SCREEN_SAVER,       //219   T:(辊玂臔)        S:(屏幕保护)
       
        "TYPE 1",          //220   T:家Α 1
        #if defined(Ti3001_OSD_UI_2) || defined(Ti3001_OSD_UI_1) || defined(Ti5026_OSD_UI_1)
            "AMP TREBLE",           //221
            "AMP MAINVOL",           //222
        #else
            "TYPE 2",             //221   T:(家Α 2)          S:(模式2)
            "TYPE 3",             //222   T:(家Α 3)          S:(模式3)
        #endif

        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #elif defined(NINTAUS_OSD_STR)
        "5 PGR",
        #else
        "5",                  //223   T:(5保留)
        #endif
        "6 R",                //224   T:(限制级)

        #ifdef NOT_SUPPROT_VCD
        "NOT SUPPORTED CD",           //225   S:(错误碟片)
        #else
        "ERR DISC",           //225   S:(错误碟片)
        #endif
        COS_DIGITAL_SETUP,     //226   T:计絏砞竚
        COS_MIC_SETUP,         //227   T:杠旦砞竚
        COS_MIC_VOL,           //228   T:杠旦秖
        "CD RECOVERING",          //229   T:岿い       ------------- not use
        "SMART_UPGRADE",     //230   T:醇ど
        "UPGRADE TO V",        //231   T:どΘ
        "UPGRADING",         //232   T:どい
        "NOT_POWEROFF",      //233   T:づ闽诀
        "REGION 0",          //234   T:0 跋
        "REGION 1",          //235   T:1 跋
        "REGION 2",          //236   T:2 跋
        "REGION 3",          //237   T:3 跋
        "REGION 4",          //238   T:4 跋
        COS_LANGUAGE_SETUP,        //239   T:粂ē砞竚
        
        "",                    //240   //not use
        "MAIN PAGE",           //241   T:()
        COS_AUDIO_LANG,        //242   T:(繵粂ē)
        COS_SUBTITLE_LANG,     //243  T:(辊粂ē)
        COS_MENU_LANG,           //244   T:(垫虫粂ē)
        COS_DOWNMIX,             //245   T:(睼家Α)
 
        COS_RESTORE,             //246   T:(確)
      
        "LT/RT",              //247
        "VSS",        //248   T:店览吏露羘
        COS_OP_MODE,            //249   T:块家Α
        COS_LINE_OUT,   //250   T:絬隔块
        COS_REMOD,     //251   T:RF 秸俱
        COS_DUAL_MONO,    //252   T:オ+
        "MIX MONO",     //253   T:睼羘笵
        "SURND MODE",         //254   T:吏露家Α
       #ifdef KSD_DVD
		"PRESS PLAY BUTTON TO CONTINUE",		//255   T:              S:请按播放键继续
#elif defined(DESAY_DVD)
        "PRESS PLAY BUTTON TO CONTINUE",
#else
        "PRE STOP",           //255	  T:                S:(准停止)
#endif        
},
#endif//USE_THAI_OSD 

//HUNGARIAN_OSD zhuyf add 30/12/2004 17:30
#ifdef USE_HUNGARIAN_OSD
//Hungarian
{
        "",                   //0
        "NO DISC",            //1     T:(礚盒)            S:(无碟)
        #if defined(SKYWORTH_DVD)||defined(BBK_DVD)||defined(INVALID_DISPLAY_HAND)     //#ifdef ALWAYS_DISPLAY_NODISC_ICON    fengjl add 3-12-7 14:28
        OS_NO,
        #else
        "\xc9""RV""\xc9""NYTELEN GOMB",        //2     T:(眤岿 hand)   S:(您按错了 HAND)
        #endif
        "TRK",                //3     T:(Ρヘ)            S:(曲目)
        OS_ICON_SVCD,         //4
        "DE-INTERLACE",//"CHINESE",            //5  not use
        "NYIT",               //6     T:()            S:(出仓)
        "Z""\xc1""R",              //7     T:(闽)            S:(关仓)
        "LEJ""\xc1""TSZ""\XC1""S",               //8     T:(冀)            S:(播放)
        "REGION 5",           //9     T:(5 跋)            S:(5区)
        "PILLANAT""\xc1""LLJ",              //10    T:(既氨)            S:(暂停)
        "RANDOM",             //11    T:(繦诀冀)        S:(随即播放)
        "FOLYTAT",             //12    T:(確冀)        S:(恢复播放)
        "STOP",               //13    T:(氨ゎ)            S:(停止)
        "L""\xc9""P""\xc9""S", //step              //14    T:(˙秈)            S:(单步)
        "V""\xc1""LASZT",//"SELECT",             //15    T:(匡拒)            S:(选择)

        #if defined(FUSS_DVD)||defined(HUAJIA_DVD)||defined(HIMAGE_CARD_READER)||defined(MINTON_DVD)   //NONO 2-5-15 3:01
            "LOADING",        //16    T:(弄盒)            S:(读碟)
        #elif defined(BBK_DVD)   //fengjl add 
            "READING",       //16     T:(弄盒)            S:(读碟)
        #elif defined(SETUP_DONGLI459)||defined(KENLOON_DVD)||defined(SHOW_LOAD_WHEN_READ)   //YAOWH  04-07-30
            "LOAD",
        #else
            "OLVAS",           //16    T:(弄盒)            S:(读碟)
        #endif
        "REGION 6",           //17    T:(6 跋)        
        #ifdef NO_SPDIF
        #ifdef HIMAGE1251    //fengjl add 2004-02-20 20:36
        "SPDIF/KI",
        #else
        "ANALOG",             //18    T:(家览)
        #endif
        #else//NO_SPDIF
        "SPDIF/OFF",             //18    T:(家览)
        #endif//NO_SPDIF        
        #ifdef HJ_APEX_FIX_SHOW_OSD
        "FF",            //19    T:(е秈)
        "FR",           //20    T:(е癶)
        #else//HJ_APEX_FIX_SHOW_OSD
        "EL""\xe0""RE",//"FORWARD",            //19    T:(е秈)
        "H""\xc1""TRA",           //20    T:(е癶)
        #endif//HJ_APEX_FIX_SHOW_OSD
        "K""\xd6""VETKEZ""\xe0",//"NEXT",               //21    T:(Ρ >>)

        #if defined(SETUP_PASSWORD_GUI)      //fengjl add  4-1-19 17:09
        "PASSWD EDIT",      // 22
        #else
            "",                 //22
        #endif       
       "EL""\xe0""Z""\xe0",// "PREV",               //23    T:(Ρ <<)
        "DIR",               //24
        "VISSZA",             //25    T:(垫虫)
        Ch_repx,              //26
        Ch_rep1,              //27
        Ch_repd,              //28
        "OFF",                //29    T:(礚)              S:(无)
        "MENU",               //30    T:(匡虫)            S:(选单)
        "SCORE",              //31    T:(だ计)            S:(分数)
#ifdef  ONE_KEY_PASS
        "SAVING THE POINT",  //32    T:(癘拘)            S:(记忆)
#else
        "MARK",               //32    T:(癘拘)            S:(记忆)
#endif

        "BROWSE",             //33    T:(聅凝)            S:(浏览)
        "PROG",               //34    T:(絪祘)            S:(编程)
        "SAVING LOGO...",     //35    T:                  S:(画面抓取中)
        #ifdef SPEAKER_CONFIG	
        "LARGE",	           //36	T:()
        #else
        "ALL LG HANGFAL",         //36    T:(家Α1)
        #endif        
        "LEJ""\xc1",//"REP",                //37    T:(確)
        "REP DIR",            //38    T:(ヘ魁確)
         "1.LEJ""\xc1",//"REP 1",              //39    T:(虫Ρ確)
        "MIND LEJ""\xc1", //"REP ALL",            //40    T:(盒確)
        "REP CANCEL",         //41    T:(確)
        #ifdef SPEAKER_CONFIG
        "SMALL",                //42    T:()
        #else
        "ALL SM HANGFAL",         //42    T:(家Α2)
        #endif
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
        #else//#ifdef HJ_APEX_FIX_SHOW_OSD
        "8 ADULT",            //43
        #endif//#ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",
        #endif
        "7 NC-17",            //44    T:(虫Ρ冀)
        "GOTO",               //45    T:(穓)
        "N""\xc9""MA",               //46    T:(繰)
        "B MONO",             //47    T:(オ羘笵)
        "J MONO",             //48    T:(羘笵)
        "SZTEREO",             //49    T:(ミ砰羘)
#ifdef HANYANG_MUTEOFF      //caohui 2004-5-13 15:59
        "MUTE OFF",                   //50    //not use
#else
        "DEMUTE",                   //50    //not use
#endif
        "\xc9""L""\xe0",//"LIVE",               //51    T:
#ifdef QSI_SETUP_MENU//liweihua 2004-6-16
        "KARAOK SETUP",                   //52

#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "",                   //52    //not use
#endif
        #ifdef SPEAKER_CONFIG
        "OFF",              //53	T:(闽)
        #else
        "KEVER""\xe0"" HANGFAL",//"MIXED SPK",          //53    T:(家Α3)
        #endif 
        OS_ICON_CDROM,        //54
        "TIME",               //55    T:(丁)            S:(时间)
#ifdef RECORD_KEY
    #ifdef NINTAUS_OSD_STR    //2004-2-11 11:35张宇P
           "THE DISC HAS RECORD.",
     #else
        "THE DISC HAS RECORD POINT", //56
      #endif
#elif defined(SUPPORT_ANGLE_MARK)
        "ANGLE MARK",                   //56    S:(角度标记)
#elif defined(SHOW_MP4_INIT_STR)    //wangwei-2004/4/28
        "INITIALIZING...",                 //56 
#else
        "",                   //56    //not use
#endif
        "ZOOM",               //57    T:(糴)            S:(放宽)
#ifdef RECORD_KEY
        #ifdef NINTAUS_OSD_STR    //2004-2-11 11:35张宇P
           "PLEASE PRESS RECORD KEY TO PLAY IT.",
     #else
        "MEM KEY:JUMP TO THE SAVED POINT",//58
      #endif
#elif defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                   //58    //not use
#endif     
        OS_ICON_LANG,         //59
        "INTRO",              //60    T:(苯磞)            S:(扫描)
        "SRND",//"SURROUND",           //61    T:(吏露)            S:(环绕)
        "PBC",                //62
#ifdef RECORD_KEY
       #ifdef NINTAUS_OSD_STR    //2004-2-11 11:35张宇P
           "IT WILL BE AUTO PLAYED AFTER 6S.",
     #else
        "OTHER KEY:PLAY FROM BEGINNING",  //63
          #endif
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
       Ch_repf,       //63         //zhuyf 2004/8/10

#else//DIVIDE_AC3_DTS_SPDIF_OUTPUTS
        "",            //63    T:(抖冀)
#endif     
        "RAND CANCEL",        //64    T:(繦诀冀)    S:(随即播放取消)
        "BASSZUS M""\xd3""D",//"BASS MODE",          //65    T:(家Α)

        "",                   //66

        "ISM""\xc9""TEL:A",  // REPEAT A-       //67    T:(確A-)          S:(重复 A )
        #ifdef JIEKE_DVD
        "P-SCAN VGA",               //"PC-VGA",           //68
        #elif (defined(NINTAUS_OSD_STR)||defined(AD_TCL))//2004-3-22 13:21 lijd
        "VGA",
        #else
        "PC-VGA",               //"PC-VGA",           //68
        #endif
        "ISM""\xc9""TER:A-B",  //"REPEAT A-B",         //69    T:(確A-B)         S:(重复播放A-B)
#ifdef BBK_DVD
        "AB CANCEL",         //70    T:(確)        S:(A-B取消)
#else
        "A-B T""\xd6""R""\xd6""L",//"A-B CANCEL",         //70    T:(確)        S:(A-B取消)
#endif
        "PRG CANCEL",         //71    T:(絪胆)            S:(编程取消)
        "",                   //72
#ifdef ONE_KEY_PASS
        "ONE KEY PLAY",      //73
#else
        "",            //73    T:(璣粂)            S:(英文)
#endif
        OS_ICON_VCD,          //74
        "LIGHT MUSIC",                   //75    
        #if defined(SHOW_VCD_VER_INFO)||defined(SYBER_DVD)  //yaowh add for kenloon 04-08-03
        OS_ICON_VCD20,        //76    //xulf 2003-11-17
        #else        
        "ELECTRON",                   //76   
        #endif
        "CVBS",//OS_ICON_MP3,          //77
        OS_ICON_CDDA,         //78
#ifdef NINTAUS_OSD_STR   
        "48KHZ",                   //79    //not use
        "96KHZ",                   //80    //not use
        "192KHZ",                   //81    //not use
#else
        "48K",                   //79    //not use
        "96K",                   //80    //not use
        "192K",                   //81    //not use
#endif
        "ZOOM FEL",            //82    T:(礶簿)        S:(放大上)
        "ZOOM LE",          //83    T:(礶簿)        S:(放大下)
        "ZOOM BALRA",          //84    T:(礶オ簿)        S:(放大左)
        "ZOOM JOBBRA",         //85    T:(礶簿)        S:(放大右)
        "CH",                 //86    T:(彻竊)            S:(章节)
        "VISSZHANG",               //87    T:(睼臫)            S:(混响)
        "TT",                 //88    T:(夹肈)            S:(标题)
        "BAND",               //89    T:(繵眯)
#ifdef OSD_BMP_REGION1
        "VOULUME",			  //90    T:(秖)            S:(音量)
#else        
        "HANGER""\xe0",//"VOL",                //90    T:(秖)            S:(音量)
#endif
        "DOWN SAMPLE",        //91    //not use
        "GOMB",                //92    T:(秸)            S:(音调)

        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        "9FRAME_1",           //94    T:(虫Ρ礶)      S:(单曲九画面)
        "B AUTO",             //95    T:(笆钡佰オ)      S:(自动接唱左)
        "J AUTO",             //96    T:(笆钡佰)      S:(自动接唱右)
        "LOW",                //97    // LOW
        "SORBAN LEJ""\xc1",    //98    T:(抖冀)        S:(顺序播放)
        "LEJ""\xc1""MEN""\xdc""B""\xe0""L",//"MENU PLAY",          //99    T:(垫虫冀)        S:(菜单播放)
#ifdef DIV_GOTO_DISPLAY
        "DISC TIME",          //100
#else
        "LFE OUT",            //100
#endif

#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)
        "  COMMON ",       //101
        "PROFESSION",      //102
#elif defined(NINTAUS_OSD_STR)
    "UP-DOWN",
    "LEFT-RIGHT",           
#elif defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102              
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else
        "STANDARD",           //101
        "ENHANCE",            //102
#endif
        "MEDIUM",             //103   // MEDIUM
#ifdef MINTON_DVD
        "PROGRAM PLAY",           //104   T:(絪导僵)          S:(编程播放)
#else
        "PRG LEJ""\xc1",//"PRG PLAY",           //104   T:(絪导僵)          S:(编程播放)
#endif
        "HIGH",               //105   // HIGH
        "DINAMIKAS""\xc1""V",//"DYNAMIC RANGE",      //106
        OS_ICON_DVD,          //107
        "K""\xc9""P NYELV",//"OSD LANGUAGE",       //108   T:(礶陪ボ粂ē)    S:(画面显示语言)
        OS_ICON_SUBT,         //109
        #ifdef SETUP_DONGLI459   //oujx for tonic
        "TV SYSTEM",          //111   T:(1qμ??÷¨?|?)      S:(μ?êó?ú??ê?)
        "TV TYPE",            //110   T:(辊礶ゑㄒ)    S:(屏幕画面比例)
        #elif defined(MINTON_DVD)
        "TV TYPE",            //110   T:(?¨?1?|ìe-?à?è??§¨°)    S:(?¨￠???-???à¨¨¨¤y)
        "TV MODE",        //111   T:(1q|ì?????§?|?)      S:(|ì?¨o¨??¨2??¨o?)
        #elif defined(SUPPORT_FUNCTION_MENU)
        "LCD MODE",           //110   
        "TV-RENDSZER",          //111                 
        #else
        "TV-T""\xcd""PUS",//"TV TYPE",            //110   T:(?¨?1?|ìe-?à?è??§¨°)    S:(?¨￠???-???à¨¨¨¤y)
        "TV SYSTEM",          //111   T:(1q|ì?????§?|?)      S:(|ì?¨o¨??¨2??¨o?)
        #endif
        "KIL""\xc9""P",//"EXIT SETUP",         //112   T:(癶砞竚垫虫)    S:(推出设置菜单)
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#elif defined(EASTECH_NEW_SETUP_MENU)
        "DIGITAL OUT",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "HANG KI",          //113   T:(计絏块)        S:(数码输出)
#endif//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)

        "VIDEO",              //114   T:(跌繵块)        S:(视频输出)
       "JELSZ""\xd3",// "PASSWORD",           //115   T:(盞絏)            S:(密码)
#ifdef GBM_RATING_SHOW_PARENTAL//GBM_FULL_FUNCTION      //gerry,2004-2-4 9:02
        "PARENTAL",//"RATING",             //116   T:()            S:(级别)
#else//GBM_RATING_SHOW_PARENTAL
       "KORL""\xc1""TOZ""\xc1""S",//"RATING",             //116   T:()            S:(级别)
#endif//GBM_RATING_SHOW_PARENTAL

#ifdef EASTECH_NEW_SETUP_MENU
        "RAW",          //117   T:(SPDIF/方絏)      S:(SPDIF/源码)
#else
        "SPDIF/RAW",          //117   T:(SPDIF/方絏)      S:(SPDIF/源码)
#endif

        #ifdef SUPPORT_PALN //4-1-12 10:55
            "PAL-N",        //118
        #elif defined(PASSWORD_IN_CH)
        "ERROR",
        #else
            "",              //118   T:(AC3 6羘笵)
        #endif
#ifdef EASTECH_NEW_SETUP_MENU
        "PCM",          //119
#else
        "SPDIF/PCM",          //119
#endif
        #ifdef SUPPORT_PALM
            "PAL-M",                //120
        #elif defined(PASSWORD_IN_CH)
        "  OK",
        #else
            "",              //120   T:(AC3 2羘笵)       S:AC3 2声道(not use)
        #endif
        #ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
        #else//SHOW_YCbCr
        #ifdef AD_TCL//2004-3-22 13:22 lijd
            "YCbCr",
        #elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
        #elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
        #else
        "INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
        #endif//SHOW_INTERLACE
        #endif//SHOW_YCbCr
        
        "AUTO",               //122   T:(笆)            S:(自动)
        "KI",                //123   T:(闽)              S:(关)
#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
        "TRACK TIME",//124
#else
        "",           //124
#endif     
        "CHAPTER",            //125   T:(彻竊)            S:(章节)
        "TITLE",              //126   T:(夹肈)            S:(标题)
        OS_ICON_ANGLE,        //127
#ifdef NINTAUS_OSD_STR
        "YPbPr",
#elif defined(AD_TCL)//2004-3-22 13:23 lijd
        "YPbPr", 
#elif defined(HANYANG_SETUPMENU)||defined(SUPPORT_FUNCTION_MENU)||defined(EASTECH_NEW_SETUP_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
#else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
#endif    
        OS_16_9,              //129   T:(16:9 --)
        OS_4_3LB,             //130   T:(4:3LB --)
        OS_4_3PS,             //131
#ifdef HJ_SVA_NEW_OSDSTR
        "PAL-D",                //132
#else//HJ_SVA_NEW_OSDSTR
        "PAL",                //132
#endif//HJ_SVA_NEW_OSDSTR
        "NTSC",               //133
        "PAL60",              //134
        #ifdef RATING_8
            "3 PG",               //135   T:(level 3)
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else
            "2",                  //136   T:(level 2)
            "1 G",                //137   T:(level 1)
            #endif            
        #else
            "NEM FELN""\xe0""TT",//"NO ADULT",           //135   T:(辅导级)
            "GYEREKZ""\xc1""R",//"KID SAFE",           //136   T:(保留)
           "MINDENT N""\xc9""Z",// "VIEW ALL",           //137   T:(礚)
        #endif

        #if defined(SHOW_5_1CH)
            "5.1CH",              //138   T:(5.1羘笵)
        #else
            "6CH SETUP",          //138   T:(6羘笵砞竚)
        #endif

        "BASSZUS HANGF",          //139   T:(禬)
        "TEL""\xcd""TETTS""\xc9""G",//"SATURATION",         //140   SATURATION
        "BE",                 //141   T:
        OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
        "CLEAR",              //145   T:(睲埃)
        "  T  C",               //146   //2004-2-23 03:56张宇P
        "--:--",              //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "EDIT",               //149   T:(絪胯)
#ifdef RECORD_KEY 
        "RECORD RESUME",          //150
#else
        "",//OS_DIR1,              //150
#endif
#ifdef QSI_SETUP_MENU//liweihua 2004-6-15
        " 1 MIN",                   //151
        " 5 MIN",                   //152
        "10 MIN",                   //153
        "30 MIN",                   //154
#elif defined(ADJUST_JPEG_SLIDE_TIME)  ////lyc 2005/2/18
        "15 SEC",                   //151
        "30 SEC",                   //152
        "45 SEC",                   //153
        "50 SEC",                   //154        
#else
#ifdef BBK_DVD
        "5.1 CH",                  //151            
#elif defined(NINTAUS_OSD_STR)
    "<<<",
#else
        "",//OS_DIR2,              //151
#endif
        OS_DIR3,              //152
        OS_DIR4,              //153
        "PAL-NC",//OS_DIR5,              //154
#endif//#ifdef QSI_SETUP_MENU
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
        "SZ""\xcd""N""\xc1""RNYALAT",//"HUE",                //157   HUE
#ifdef BBK_NEW_SETUP
        "PROLOGIC II",//"-:--:--",            //158  
#else
        "PROLOGIC",//"-:--:--",            //158     
#endif        
        "MOVIE MODE",//"TRACK SEARCH",       //159    
        "MUSIC MODE",//"DISC SEARCH",        //160    
        
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//TT:CH",               //161    //not use
        #endif

        #ifdef REMAIN_TIME//nono 2-7-12 20:06
            "T",                  //162
        #else
            "",           //162
        #endif

        OS_DIR0,              //163
        "KONTRASZT",           //164   CONTRAST
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
        "CSATORNA",            //168   T:(羘笵)            S:(声道)
        "F""\xc9""NYER""\xe0",//"BRIGHTNESS",         //169   BRIGHTNESS
        "F/W ID",             //170   T:(硁ン絪絏)        S:(软件编码)
        "CHIP ID",            //171   T:(絪絏)        S:(芯片编码)
        "REGION",             //172   T:(跋絏)            S:(区码)
        "MEMORY",//"FUNCTION",           //173  //not use T:(滦弄滦佰)        S:(复读复唱)
        "DYNAMIC",//"MODE",               //174  //not use  T:(家Α)            S:(模式)
        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

        "MIC1 VOL",//"COMPARE",            //178   //not use T:(癸ゑ)            S:(对比)
        "MIC2 VOL",//"COUNTER",            //179   //not use T:(滦Ω计)        S:(重复次数)
#ifdef FUSS_DVD_AVD276
        "PREV CHAPTER",      //180   S:上一章节
        "NEXT CHAPTER",      //181   S:下一章节
//#elif defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#elif defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU)
        "BATTERY STATUS",           //180
        "SETUP",                    //181
#else
        "",//"LEVEL",              //180   T:魁家Α        S:录音模式
        "",//"HIGH",               //181   T:蔼珇借          S:高品质
#endif

#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",             //182   T:(禬丁)        S:(超长时间)
#endif

#ifdef NEWSTYLE_WINDOW
        "PLAYTITLE",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "TITLETIME",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "CHPTIME",//"MANUAL",             //185   T:(も笆)            S:(手动)
#elif defined(ADD_DVI311_SETUP)//Modifed by ChenZhao on 2004-8-19 17:24 WP
			"ANOLOG OUTPUT", //183
			"DIGITAL OUTPUT",  //184
			"",//OS_MANUAL, 		   //185   T:(も笆)
#elif defined(BRIGHTNESS_COLOR_KEY)||defined(VIEW_MODE_KEY)
		"COLOR",					//OS_COLOR 					//183
        "NORMAL MODE",				//OS_VIEW_MODE_NORMAL   	//184   
        "FULL MODE",				//OS_VIEW_MODE_FULL         //185   
#else
        "",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "",//"MANUAL",             //185   T:(も笆)            S:(手动)
#endif
        OS_DIR10,             //186
        OS_DIR11,             //187
        "KONCERT",            //188   T:(贾芔)          S:(音乐厅)
        "TEMPLOM",             //189   T:(毙绑)            S:(教堂)
        "PASSZ""\xcd""V",//"PASSIVE",            //190   T:(吏露)            S:(环绕)
         "SZ""\xc9""LES",//"WIDE",               //191   T:(糴初)            S:(宽场)
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192
        "MPEG LOGO",            //193
#elif defined(ADD_DVI311_SETUP)//Modifed by ChenZhao on 2004-8-19 17:20 WP
		"VIDEO SELECT",	  //192
		"VIDEO MODE",		  //193
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)
        "",//OS_STADIUM,           //193   T:(蔨▅繻)
#endif
        "EQ",                 //194   T:(А颗)            S:(均衡)
        "STANDARD",           //195   T:(夹非)            S:(标准)
        "CLASSIC",            //196   T:(ㄥ)            S:(古典)
        "ROCK",               //197   T:(穘簎)            S:(摇滚)
        "JAZZ",               //198   T:(里)            S:(爵士)
        "POP",                //199   T:(瑈︽)            S:(流行)
        "USER",               //200   T:(┦)            S:(个性)
        "ATTRIB",             //201   T:(┦)            S:(个性)
        "SF",                 //202   T:(篊秈)            S:(慢进)
        "SB",                 //203   T:(篊癶)            S:(慢退)
        "C",                  //204   //show "C"
       "CENTER",              //205   T:(い竚喘羘竟)      S:(中置扬声器)
        "REAR",               //206   T:(吏露喘羘竟)      S:(环绕扬声器)
        #if !defined(HIMAGE_RGB)&&!defined(NINTAUS_OSD_STR)
        "TV-RGB",             //207
        #else
        "RGB",                    //207
        #endif
        "4 PG13",             //208   T:(辅导级)
        "K""\xc9""SLELTET""\xc9""S K""\xd6""Z""\xc9""PEN",//"CENTER DELAY",       //209   T:(い竚┑筐)
        "K""\xc9""SLELTET""\xc9""S H""\xc1""TUL",//"REAR DELAY",         //210   T:(吏露┑筐)
        "FRONT",              //211   T:(玡竚喘羘竟)
       "VIDEO BE""\xc1""LL",// "VIDEO SETUP",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS
        "RENDSZ BE""\xc1""LL",//"SYSTEM SETUP",       //214   T:(╰参砞竚)        S:(系统设置)
        "HANGFAL BE""\xc1""LL",//"SPEAKER SETUP",      //215   T:(喘羘竟砞竚)      S:(扬声器设置)
        "HANG BE""\xc1""LL",//"AUDIO SETUP",        //216   T:(繵砞竚)        S:(音频设置)
        "ALAP""\xc9""RTELM",//"DEFAULT",            //217   T:()          S:(缺省值)
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "GRP",                //218   //not use
        #endif
#ifdef AUTO_PLAY
        "AUTO PLAY",       //219   T:(辊玂臔)        S:(屏幕保护)
#else
        "K""\xc9""PEVNY""\xe0""V""\xc9""D""\xe0",//"SCREEN SAVER",       //219   T:(辊玂臔)        S:(屏幕保护)
#endif
        "TYPE 1",             //220   T:(家Α 1)          S:(模式1)
        "TYPE 2",             //221   T:(家Α 2)          S:(模式2)
        "TYPE 3",             //222   T:(家Α 3)          S:(模式3)
        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   S:(5保留)
        #endif        
        "6 R",                //224   S:(限制级)
        #ifdef NOT_SUPPROT_VCD
        "NOT SUPPORTED CD",           //225   S:(错误碟片)
        #else
        "ERR DISC",           //225   S:(错误碟片)
        #endif
        "DIGIT""\xc1""LIS BE""\xc1""LL",//"DIGITAL SETUP",      //226   T:(计絏砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "MIKR BE""\xc1""LL",//"MIC SETUP",          //227   T:(杠旦砞竚)
        "MIKR HANGER""\xe0",//"MIC VOL",            //228   T:(杠旦秖)
        #endif
        "CD RECOVERING",      //229   T:(岿い)     ------------- not use
        "SMART UPGRADE",      //230   T:(醇ど)
        "UPGRADE TO V ",      //231   T:(どΘ)
        "UPGRADING",          //232   T:(どい)
        "NOT POWER OFF",      //233   T:(づ闽诀)
        "REGION 0",           //234   T:(0 跋)
        "REGION 1",           //235   T:(1 跋)
        "REGION 2",           //236   T:(2 跋)
        "REGION 3",           //237   T:(3 跋)
        "REGION 4",           //238   T:(4 跋)
        "NYELV BE""\xc1""LL",//"LANGUAGE SETUP",     //239   T:(粂ē砞竚)
#ifdef  JIEKE_DVD
        "GIEC",               //240
#elif defined(BBK_DVD)
        "ZOOM",               //240
#elif defined(NINTAUS_OSD_STR)
    ">>>",
#elif defined(SUPPORT_FUNCTION_MENU)
        "DISPLAY",            //240 
#elif defined(GBM_PORTABLE_DVD)||defined(SUNPLUS_8202P_DEMOBOARD) 
        "LOW BATTERY",        //240         
#else        
        "",                   //240   //not use
#endif      
        "MAIN PAGE",          //241   T:()
#if !defined(BBK_DVD)
        "HANG NYELV",       //242   T:(繵粂ē)
#else
        "AUDIO",              //242   T:(繵粂ē) //axel 2004/1/27 03:58 eliminate "LANG"
#endif
#ifdef DISC_INFO_KEY  //fengjl  3-11-25 9:55
/*         "SUBP LANG",      //243   T:(辊粂ē)*/ //axel 2004/1/27 03:58 eliminate "LANG"
        "SUBP",      //243   T:(辊粂ē)
#elif defined(BBK_DVD)
        "SUBTITLE",           //243   T:(辊粂ē)
#else
        "FELIRAT NYELV",      //243   T:(辊粂ē) //axel 2004/1/27 03:58 eliminate "LANG"
#endif
        "MEN""\xdc"" NYELV",//"MENU LANG",          //244   T:(垫虫粂ē)
        "LEKEVER""\xc9""S",//"DOWNMIX",            //245   T:(睼家Α)
     
        "HELYRE""\xc1""LL",//"RESTORE",            //246   T:(確)
       
        "LT/RT",              //247
        "VSS",                //248   T:(店览吏露羘)      S:(虚拟环绕声)
        "OP MODE",            //249   T:(块家Α)        S:(输出模式)
        "LINE OUT",           //250   T:(絬隔块)        S:(线路输出)
        "RF REMOD",           //251   T:(RF 秸俱)         S:(RF调整)
        "DUAL MONO",          //252   T:(オ+)           S:(左+右)
        "VEGYES MONO",           //253   T:(睼羘笵)        S:(混合声道)
        "SURND MODE",         //254   T:(吏露家Α)        S:(环绕模式)
#ifdef KSD_DVD
        "PRESS PLAY BUTTON TO CONTINUE",        //255   T:              S:请按播放键继续
#elif defined(DESAY_DVD)
        "PRESS PLAY BUTTON TO CONTINUE",
#elif defined(TONIC_DVD)
        "PRESS PLAY KEY TO CONTINUE",
#else
        "PRE STOP",           //255   T:                S:(准停止)
#endif
//============================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER

},
#endif  //USE_HUNGARIAN_OSD

#ifdef USE_ARABIC_OSD
//English
{
        "",                   //0
        "\x6c""\x6d",//"NO DISC",            //1     T:(礚盒)            S:(无碟)
        #if defined(SKYWORTH_DVD)||defined(BBK_DVD)||defined(INVALID_DISPLAY_HAND)     //#ifdef ALWAYS_DISPLAY_NODISC_ICON    fengjl add 3-12-7 14:28
        OS_NO,
        #else
        "\x6e",//"INVALID KEY",        //2     T:(眤岿 hand)   S:(您按错了 HAND)
        #endif
        "TRK",                //3     T:(Ρヘ)            S:(曲目)
        OS_ICON_SVCD,         //4
        "\x6f",//"DE-INTERLACE",//"CHINESE",            //5  not use
        "\x70",//"OPEN",               //6     T:()            S:(出仓)
        "\x71",//"CLOSE",              //7     T:(闽)            S:(关仓)
        "\x73",//"PLAY",               //8     T:(冀)            S:(播放)
        "\x74"" 5",//"REGION 5",           //9     T:(5 跋)            S:(5区)
        "\x75",//"PAUSE",              //10    T:(既氨)            S:(暂停)
        "\x76",//"RANDOM",             //11    T:(繦诀冀)        S:(随即播放)
        "\x77",//"RESUME",             //12    T:(確冀)        S:(恢复播放)
        "\x78",//"STOP",               //13    T:(氨ゎ)            S:(停止)
        "\x79",//"STEP",               //14    T:(˙秈)            S:(单步)
        "\x7a",//"SELECT",             //15    T:(匡拒)            S:(选择)

        #if defined(FUSS_DVD)||defined(HUAJIA_DVD)||defined(HIMAGE_CARD_READER)||defined(MINTON_DVD)   //NONO 2-5-15 3:01
            "CD""\x7b",//"LOADING",        //16    T:(弄盒)            S:(读碟)
        #elif defined(BBK_DVD)   //fengjl add 
            "CD""\x7b",//"READING",       //16     T:(弄盒)            S:(读碟)
        #elif defined(SETUP_DONGLI459)||defined(KENLOON_DVD)||defined(SHOW_LOAD_WHEN_READ)   //YAOWH  04-07-30
            "CD""\x7b",//"LOAD",
        #else
            "CD""\x7b",//"READ",           //16    T:(弄盒)            S:(读碟)
        #endif

        "\x74"" 6",//"REGION 6",           //17    T:(6 跋)
        
        #ifdef NO_SPDIF
        #ifdef HIMAGE1251    //fengjl add 2004-02-20 20:36
        "SPDIF/OFF",
        #else
        "\r\xe7",//"ANALOG",             //18    T:(家览)
        #endif
        #else//NO_SPDIF
        "SPDIF/OFF",             //18    T:(家览)
        #endif//NO_SPDIF
        
        
        "\x7c",//"FF",            //19    T:(е秈)
       "\x7d",//"FR",           //20    T:(е癶)
        
        "\x80",//"NEXT",               //21    T:(Ρ >>)

        #if defined(SETUP_PASSWORD_GUI)      //fengjl add  4-1-19 17:09
        "\x82""\x83",//"PASSWD EDIT",      // 22
        #else
            "",                 //22
        #endif
        
        "\r\xe8",//"PREV",               //23    T:(Ρ <<)

        "DIR",               //24

        "RETURN",             //25    T:(垫虫)
        Ch_repx,              //26
        Ch_rep1,              //27
        Ch_repd,              //28
        "\x84",//"OFF",                //29    T:(礚)              S:(无)
        "\x86",//"MENU",               //30    T:(匡虫)            S:(选单)
        "\x87",//"SCORE",              //31    T:(だ计)            S:(分数)
#ifdef  ONE_KEY_PASS
        "\x88""\x89",//"SAVING THE POINT",  //32    T:(癘拘)            S:(记忆)
#else
        "\x8a",//"MARK",               //32    T:(癘拘)            S:(记忆)
#endif

        "\x8b",//"BROWSE",             //33    T:(聅凝)            S:(浏览)
        "\x8c""\x8d",//"PROG",               //34    T:(絪祘)            S:(编程)
        "\r\xe9",//"SAVING LOGO...",     //35    T:                  S:(画面抓取中)
        #ifdef SPEAKER_CONFIG	
        "LARGE",	          //36	T:()
        #else
        "ALL LG SPK",         //36    T:(家Α1)
        #endif        
        "\x8e",//"REP",                //37    T:(確)
        "\x8e""DIR",// "REP DIR",            //38    T:(ヘ魁確)
        "\x8e"" 1",//"REP 1",              //39    T:(虫Ρ確)
        "\x8e""\x8f",//"REP ALL",            //40    T:(盒確)
        "\x8e""\x90",//"REP CANCEL",         //41    T:(確)
        #ifdef SPEAKER_CONFIG
        "SMALL",               //42    T:()
        #else
        "ALL SM SPK",         //42    T:(家Α2)
        #endif

        "8",                 //43

        "7 NC-17",            //44    T:(虫Ρ冀)
        "\x92",//"GOTO",               //45    T:(穓)
        "\x91",//"MUTE",               //46    T:(繰)
        "\x93"" L",//"MONO L",             //47    T:(オ羘笵)
        "\x93"" R",//"MONO R",             //48    T:(羘笵)
        "STEREO",             //49    T:(ミ砰羘)
#ifdef HANYANG_MUTEOFF      //caohui 2004-5-13 15:59
        "\x91""\x84",//"MUTE OFF",                   //50    //not use
#else
        "\x91""\x84",//"DEMUTE",                   //50    //not use
#endif
        "LIVE",               //51    T:
#ifdef QSI_SETUP_MENU//liweihua 2004-6-16
        "KARAOK ""\r\xea",//"KARAOK SETUP",                   //52

#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
       "DOLBY ""\r\xef" ,//"DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "\x94",//"DISC",               //52
#else
        "",                   //52    //not use
#endif
        #ifdef SPEAKER_CONFIG
        	"\x84",//"OFF",  //53	T:(闽)
        #else
        "\r\xeb"" SPK",//"MIXED SPK",          //53    T:(家Α3)
        #endif 
        OS_ICON_CDROM,        //54
        "\x95",//"TIME",               //55    T:(丁)            S:(时间)
#ifdef RECORD_KEY
    #ifdef NINTAUS_OSD_STR    //2004-2-11 11:35张宇P
         "\x96""\x97",//"THE DISC HAS RECORD.",
     #else
        "\x96""\x97",//"THE DISC HAS RECORD POINT", //56
      #endif
#elif defined(SUPPORT_ANGLE_MARK)
        "\r\xec""\x8a",//"ANGLE MARK",                   //56    S:(角度标记)
#elif defined(SHOW_MP4_INIT_STR)    //wangwei-2004/4/28
        "INITIALIZING...",                 //56 
#else
        "",                   //56    //not use
#endif
        "\x98",//"ZOOM",               //57    T:(糴)            S:(放宽)
#ifdef RECORD_KEY
     #ifdef NINTAUS_OSD_STR    //2004-2-11 11:35张宇P
            "\x99""\x9a" "\x9b",//"PLEASE PRESS RECORD KEY TO PLAY IT.",
     #else
         "\x9c""\x9d" "\x9e""\x9f",//"MEM KEY:JUMP TO THE SAVED POINT",//58
     #endif
#elif defined(SUPPORT_CC_ONOFF)
        "\r\xed",//"CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "",                   //58    //not use
#endif     
        OS_ICON_LANG,         //59
        "INTRO",              //60    T:(苯磞)            S:(扫描)
        "\xa2",//"SRND",//"SURROUND",           //61    T:(吏露)            S:(环绕)
        "PBC",                //62
#ifdef RECORD_KEY
       #ifdef NINTAUS_OSD_STR    //2004-2-11 11:35张宇P
           "\xa0""\xa1",//"IT WILL BE AUTO PLAYED AFTER 6S.",
     #else
        "\xa3""\xa4""\xa5",//"OTHER KEY:PLAY FROM BEGINNING",  //63
          #endif
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS ""\r\xef",//"DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
       Ch_repf,       //63         //zhuyf 2004/8/10

#else//DIVIDE_AC3_DTS_SPDIF_OUTPUTS
        "",            //63    T:(抖冀)
#endif     
        "\r\xf0""\r\xf1",//"RAND CANCEL",        //64    T:(繦诀冀)    S:(随即播放取消)
        "BASS ""\xe8",// "BASS MODE",          //65    T:(家Α)

        "",                   //66

        "\x8e"" A-",//"REPEAT A-",          //67    T:(確A-)          S:(重复 A )
        #ifdef JIEKE_DVD
        "P-SCAN VGA",               //"PC-VGA",           //68
        #elif (defined(NINTAUS_OSD_STR)||defined(AD_TCL))//2004-3-22 13:21 lijd
        "VGA",
        #else
        "PC-VGA",               //"PC-VGA",           //68
        #endif
        "\x8e"" A-B",//"REPEAT A-B",         //69    T:(確A-B)         S:(重复播放A-B)
#ifdef BBK_DVD
        " AB""\x90",//"AB CANCEL",         //70    T:(確)        S:(A-B取消)
#else
        " A-B""\x90",//"A-B CANCEL",         //70    T:(確)        S:(A-B取消)
#endif
        "PRG ""\x90",//"PRG CANCEL",         //71    T:(絪胆)            S:(编程取消)
        "",                   //72
#ifdef ONE_KEY_PASS
        "\xa6""\xa7",//"ONE KEY PLAY",      //73
#else
        "",            //73    T:(璣粂)            S:(英文)
#endif
        OS_ICON_VCD,          //74
        "\r\xf2""\r\xf3",//"LIGHT MUSIC",                   //75    
        #if defined(SHOW_VCD_VER_INFO)||defined(SYBER_DVD)  //yaowh add for kenloon 04-08-03
        OS_ICON_VCD20,        //76    //xulf 2003-11-17
        #else        
        "\xa8",//"ELECTRON",                   //76   
        #endif
        "CVBS",//OS_ICON_MP3,          //77
        OS_ICON_CDDA,         //78
#ifdef NINTAUS_OSD_STR   
        "48KHZ",                   //79    //not use
        "96KHZ",                   //80    //not use
        "192KHZ",                   //81    //not use
#else
        "48K",                   //79    //not use
        "96K",                   //80    //not use
        "192K",                   //81    //not use
#endif
        "\x98""\xa9",//"ZOOM UP",            //82    T:(礶簿)        S:(放大上)
        "\x98""\xab",//"ZOOM DOWN",          //83    T:(礶簿)        S:(放大下)
        "\x98""\xac",//"ZOOM LEFT",          //84    T:(礶オ簿)        S:(放大左)
        "\x98""\xad",//"ZOOM RIGHT",         //85    T:(礶簿)        S:(放大右)
        "\xae",//"CH",                 //86    T:(彻竊)            S:(章节)
        "\xaf",//"ECHO",               //87    T:(睼臫)            S:(混响)
        "TT",                 //88    T:(夹肈)            S:(标题)
        "BAND",               //89    T:(繵眯)
#ifdef OSD_BMP_REGION1
        "\xb1",//"VOULUME",			  //90    T:(秖)            S:(音量)
#else        
        "\xb1",//"VOL",                //90    T:(秖)            S:(音量)
#endif
        "\r\xf4""\r\xf5",//"DOWN SAMPLE",        //91    //not use
        "KEY",                //92    T:(秸)            S:(音调)

        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "\xb2""\xb3",//"COMPOSITE",            //93
        #else
        "S-""\xea",//"S-VIDEO",            //93
        #endif

        "9FRAME_1",           //94    T:(虫Ρ礶)      S:(单曲九画面)
        "\xb4"" L",//"AUTO L",             //95    T:(笆钡佰オ)      S:(自动接唱左)
        "\xb4"" R",//"AUTO R",             //96    T:(笆钡佰)      S:(自动接唱右)
        "\xb7",//"LOW",                //97    // LOW

        "\xb8""\xbb",//"SEQ PLAY",           //98    T:(抖冀)        S:(顺序播放)

        "\xbd""\xbe",//"MENU PLAY",          //99    T:(垫虫冀)        S:(菜单播放)
#ifdef DIV_GOTO_DISPLAY
       "DISC ""\x95", // "DISC TIME",          //100
#else
        "LFE OUT",            //100
#endif

#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)
        "\xbf",//"  COMMON ",       //101
        "\xe0",//"PROFESSION",      //102
#elif defined(NINTAUS_OSD_STR)
    "UP-DOWN",
    "LEFT-RIGHT",           
#elif defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "\xe1",//"TIMER SETUP",          //102              
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#else
        "\xe3",//"STANDARD",           //101
        "\xe2",//"ENHANCE",            //102
#endif

        "\xe4",//"MEDIUM",             //103   // MEDIUM
#ifdef MINTON_DVD
        "\x8c""\x8d",//"PROGRAM PLAY",           //104   T:(絪导僵)          S:(编程播放)
#else
        "\x8c""\x8d",//"PRG PLAY",           //104   T:(絪导僵)          S:(编程播放)
#endif
        "HIGH",               //105   // HIGH
        "DYNAMIC RANGE",      //106
        OS_ICON_DVD,          //107
        "OSD""\xe5",//"OSD LANGUAGE",       //108   T:(礶陪ボ粂ē)    S:(画面显示语言)
        OS_ICON_SUBT,         //109

        #ifdef SETUP_DONGLI459   //oujx for tonic
        "TV""\xe6",//"TV SYSTEM",          //111   T:(1qμ??÷¨?|?)      S:(μ?êó?ú??ê?)
        "TV""\xe7",//"TV TYPE",            //110   T:(辊礶ゑㄒ)    S:(屏幕画面比例)
        #else
        "TV""\xe7",//"TV TYPE",            //110   T:(?¨?1?|ìe-?à?è??§¨°)    S:(?¨￠???-???à¨¨¨¤y)
        "TV""\xe6",//"TV SYSTEM",          //111   T:(1q|ì?????§?|?)      S:(|ì?¨o¨??¨2??¨o?)
        #endif


        "\xe9",//"EXIT SETUP",         //112   T:(癶砞竚垫虫)    S:(推出设置菜单)
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#elif defined(EASTECH_NEW_SETUP_MENU)
       "\r\xef""\r\x46" ,//"DIGITAL OUT",          //113   T:(计絏块)        S:(数码输出)
#elif defined(MUSTEK_PORTABLE_DVD)
       "\r\xef""\r\x46",// "DIGITAL OUT",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "\r\x3a""\r\x46",//"AUDIO OUT",          //113   T:(计絏块)        S:(数码输出)
#endif//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)

		#if defined(MUSTEK_PORTABLE_DVD)
		"\xea",//"VIDEO OUTPUT", 		//114
		#else
       "\xea",// "VIDEO",              //114   T:(跌繵块)        S:(视频输出)
        #endif
        "\xb0",//"PASSWORD",           //115   T:(盞絏)            S:(密码)
        "\xed",// "PARENTAL",//"RATING",             //116   T:()            S:(级别)

#ifdef EASTECH_NEW_SETUP_MENU
        "RAW",          //117   T:(SPDIF/方絏)      S:(SPDIF/源码)
#else
        "SPDIF/RAW",          //117   T:(SPDIF/方絏)      S:(SPDIF/源码)
#endif

         "\xef",//"ERROR",   //118 

#ifdef EASTECH_NEW_SETUP_MENU
        "PCM",          //119
#else
        "SPDIF/PCM",          //119
#endif

        #ifdef SUPPORT_PALM
            "PAL-M",                //120
        #elif defined(PASSWORD_IN_CH)
        "  OK",
        #else
            "",              //120   T:(AC3 2羘笵)       S:AC3 2声道(not use)
        #endif

        #ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
        #else//SHOW_YCbCr
        #ifdef AD_TCL//2004-3-22 13:22 lijd
            "YCbCr",
        #elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
          "\r\x19",//"INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
        #elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
        #elif defined(EASTECH_DVI)
        "YCbCr", //121
        #else
         "\r\x19""YUV",//"INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
        #endif//SHOW_INTERLACE
        #endif//SHOW_YCbCr
        
        "\xb4",//"AUTO",               //122   T:(笆)            S:(自动)
        "\x84",//"OFF",                //123   T:(闽)              S:(关)
#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
        "TRACK TIME",//124
#else
        "",           //124
#endif     
         "\xae",//"CHAPTER",            //125   T:(彻竊)            S:(章节)
        "TITLE",              //126   T:(夹肈)            S:(标题)
        OS_ICON_ANGLE,        //127
#ifdef NINTAUS_OSD_STR
        "YPbPr",
#elif defined(AD_TCL)//2004-3-22 13:23 lijd
        "YPbPr", 
#elif defined(HANYANG_SETUPMENU)||defined(SUPPORT_FUNCTION_MENU)||defined(EASTECH_NEW_SETUP_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
#else
        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)
#endif    

        OS_16_9,              //129   T:(16:9 --)
        OS_4_3LB,             //130   T:(4:3LB --)
        OS_4_3PS,             //131

#ifdef HJ_SVA_NEW_OSDSTR
        "PAL-D",                //132
#else//HJ_SVA_NEW_OSDSTR
        "PAL",                //132
#endif//HJ_SVA_NEW_OSDSTR
        "NTSC",               //133
        "PAL60",              //134

        #ifdef RATING_8
            "3 PG",               //135   T:(level 3)
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else
            "2",                  //136   T:(level 2)
            "1 G",                //137   T:(level 1)
            #endif
            
        #else
             "NO ADULT",           //135   T:(辅导级)
           "\xf3""\xf4",//"KID SAFE",           //136   T:(保留)
           "\xf5""\xf6",//"VIEW ALL",           //137   T:(礚)
        #endif


        #if defined(SHOW_5_1CH)
            "5.1CH",              //138   T:(5.1羘笵)
        #else
            "6CH SETUP",          //138   T:(6羘笵砞竚)
        #endif

        "\xf8""\xf9",//"SUBWOOFER",          //139   T:(禬)
        "\xfa",//"SATURATION",         //140   SATURATION
        "\r\x1e",//"ON",                 //141   T:
        OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
#if defined(OSD_BMP_PROG)
        "RESET",              //145   T:(睲埃)
#else
        "\xfb""\xfd",//"CLEAR",              //145   T:(睲埃)
#endif
        "  T  C",               //146   //2004-2-23 03:56张宇P
        "--:--",              //147
#if	defined(MP3_DIRECT_SELECT)||defined(OSD_BMP_PROG)
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "\xfe",//"EDIT",               //149   T:(絪胯)
#ifdef RECORD_KEY 
        "\r\x11",//RECORD RESUME",          //150
#elif defined(SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE)  //added by wangwei,2004-10-24 23:42,(English)
        "\xeb""\xec"" LG 2",//"SUBTITLE LG 2",       //150
#else
        "",//OS_DIR1,              //150
#endif
#ifdef QSI_SETUP_MENU//liweihua 2004-6-15
        " 1 MIN",                   //151
        " 5 MIN",                   //152
        "10 MIN",                   //153
        "30 MIN",                   //154
#elif defined(ADJUST_JPEG_SLIDE_TIME)  ////lyc 2005/2/18
        "15 SEC",                   //151
        "30 SEC",                   //152
        "45 SEC",                   //153
        "50 SEC",                   //154        
#else
#ifdef BBK_DVD
        "5.1 CH",                  //151            
#elif defined(NINTAUS_OSD_STR)
    "<<<",
#else
        "",//OS_DIR2,              //151
#endif
        OS_DIR3,              //152
        OS_DIR4,              //153
        "PAL-NC",//OS_DIR5,              //154
#endif//#ifdef QSI_SETUP_MENU
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
        "\r\x12""\r\x13",//"HUE",                //157   HUE
#ifdef BBK_NEW_SETUP
        "\r\x12""\r\x13""II",//"PROLOGIC II",//"-:--:--",            //158  
#else
        "\r\x12""\r\x13""II",//"PROLOGIC",//"-:--:--",            //158     
#endif        
        "\r\x16""\xe8",//"MOVIE MODE",//"TRACK SEARCH",       //159    
        "\r\x17""\r\x18""\xe8",//"MUSIC MODE",//"DISC SEARCH",        //160    
        
        #if defined(SUPPORT_IR_I2P_KEY)
        "\x6f",//"INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//TT:CH",               //161    //not use
        #endif

        #ifdef REMAIN_TIME//nono 2-7-12 20:06
            "T",                  //162
        #else
            "",           //162
        #endif

        OS_DIR0,              //163
        "\r\x1b",//"CONTRAST",           //164   CONTRAST
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
        "\r\x1c",//"CHANNEL",            //168   T:(羘笵)            S:(声道)
        "\r\x1d",//"BRIGHTNESS",         //169   BRIGHTNESS
        "F/W ID",             //170   T:(硁ン絪絏)        S:(软件编码)
        "CHIP ID",            //171   T:(絪絏)        S:(芯片编码)
        "\x74",//"REGION",             //172   T:(跋絏)            S:(区码)
        "\r\x1f",//"MEMORY",//"FUNCTION",           //173  //not use T:(滦弄滦佰)        S:(复读复唱)
        "DYNAMIC",//"MODE",               //174  //not use  T:(家Α)            S:(模式)


        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177

         "\r\x20""1 ""\xb1",//"MIC1 VOL",//"COMPARE",            //178   //not use T:(癸ゑ)            S:(对比)
         "\r\x20""2 ""\xb1",//"MIC2 VOL",//"COUNTER",            //179   //not use T:(滦Ω计)        S:(重复次数)

#ifdef FUSS_DVD_AVD276
        "\r\xe8""\xae",//"PREV CHAPTER",      //180   S:上一章节
        "\x80""\xae",//"NEXT CHAPTER",      //181   S:下一章节
//#elif defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#elif defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
       "\r\x21",//"ADVANCED",//"NEXT PAGE",               //180
        "\r\x21""\r\xea",//"ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "\x80""\r\xf6",//"NEXT PAGE",                //180
        "\r\xe8""\r\xf6",//"PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU)
        "BATTERY STATUS",           //180
        "\r\xea",//"SETUP",                    //181
#else
        "",//"LEVEL",              //180   T:魁家Α        S:录音模式
        "",//"HIGH",               //181   T:蔼珇借          S:高品质
#endif

#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",             //182   T:(禬丁)        S:(超长时间)
#endif

#ifdef NEWSTYLE_WINDOW
        "PLAYTITLE",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "TITLETIME",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "CHPTIME",//"MANUAL",             //185   T:(も笆)            S:(手动)
#elif defined(ADD_DVI311_SETUP)//Modifed by ChenZhao on 2004-8-19 17:24 WP
			"ANOLOG OUTPUT", //183
			"DIGITAL OUTPUT",  //184
			"",//OS_MANUAL, 		   //185   T:(も笆)
#elif defined(BRIGHTNESS_COLOR_KEY)||defined(VIEW_MODE_KEY)
		"COLOR",					//OS_COLOR 					//183
        "NORMAL MODE",				//OS_VIEW_MODE_NORMAL   	//184   
        "FULL MODE",				//OS_VIEW_MODE_FULL         //185   
#else
        "",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "",//"MANUAL",             //185   T:(も笆)            S:(手动)
#endif

        OS_DIR10,             //186
        OS_DIR11,             //187
        "CONCERT",            //188   T:(贾芔)          S:(音乐厅)
        "CHURCH",             //189   T:(毙绑)            S:(教堂)
        "PASSIVE",            //190   T:(吏露)            S:(环绕)
        "WIDE",               //191   T:(糴初)            S:(宽场)
#ifdef USER_MPEG_LOGO
        "\x7a""\r\xf8",//"SELECT LOGO",          //192
        "MPEG ""\r\xea",//"MPEG LOGO",            //193
#elif defined(ADD_DVI311_SETUP)//Modifed by ChenZhao on 2004-8-19 17:20 WP
		"\xea""\x7a",//"VIDEO SELECT",	  //192
		"\xea""\xe8",//"VIDEO MODE",		  //193
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)
        "",//OS_STADIUM,           //193   T:(蔨▅繻)
#endif
        "EQ",                 //194   T:(А颗)            S:(均衡)
        "\xe3",//"STANDARD",           //195   T:(夹非)            S:(标准)
        "CLASSIC",            //196   T:(ㄥ)            S:(古典)
        "ROCK",               //197   T:(穘簎)            S:(摇滚)
        "JAZZ",               //198   T:(里)            S:(爵士)
        "POP",                //199   T:(瑈︽)            S:(流行)
        "USER",               //200   T:(┦)            S:(个性)
        "ATTRIB",             //201   T:(┦)            S:(个性)
        "\x7c",//"SF",                 //202   T:(篊秈)            S:(慢进)
        "\x7d",//"SB",                 //203   T:(篊癶)            S:(慢退)

        "C",                  //204   //show "C"
	#if defined(MUSTEK_PORTABLE_DVD)
		"ADD", //205
		"DELETE", //206
	#else
       "CENTER",              //205   T:(い竚喘羘竟)      S:(中置扬声器)
       "\r\x22",//"REAR",               //206   T:(吏露喘羘竟)      S:(环绕扬声器)
    #endif
        #if !defined(HIMAGE_RGB)&&!defined(NINTAUS_OSD_STR)
        "TV-RGB",             //207
        #else
        "RGB",                    //207
        #endif
        "4 PG13",             //208   T:(辅导级)
    #if defined(MUSTEK_PORTABLE_DVD)
    	"ANTENNA", //209
    	"CATV", //210
    	"START", //211
    #else
        "CENTER ""\r\xf9""\r\xfa",//"CENTER DELAY",       //209   T:(い竚┑筐)
        "\r\x22""\r\xf9""\r\xfa",//"REAR DELAY",         //210   T:(吏露┑筐)
        "FRONT",              //211   T:(玡竚喘羘竟)
    #endif
          "\xea""\r\xea",//"VIDEO SETUP",        //212   VIDEO SETUP
          "\r\x23",//"SHARPNESS",          //213   SHARPNESS
          "\xe6""\r\xea",//"SYSTEM SETUP",       //214   T:(╰参砞竚)        S:(系统设置)
        #if defined(MUSTEK_PORTABLE_DVD)
        "TV TUNER SETUP", 	  //215
        #else
          "\r\x2a""\r\x2b",//"SPEAKER SETUP",      //215   T:(喘羘竟砞竚)      S:(扬声器设置)
        #endif
        "\r\x3a""\r\xea",//"AUDIO SETUP",        //216   T:(繵砞竚)        S:(音频设置)
         "DEFAULT",            //217   T:()          S:(缺省值)
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #else
        "GRP",                //218   //not use
        #endif
#ifdef AUTO_PLAY
          "\r\x31""\r\x32",//"AUTO PLAY",       //219   T:(辊玂臔)        S:(屏幕保护)
#elif defined(VCD_CDG_PLAY_CONTROL_BY_SETUPMENU)
        "   MNP   ",
#else
          "\r\x33""\r\x34",//"SCREEN SAVER",       //219   T:(辊玂臔)        S:(屏幕保护)
#endif
          "\xe7"" 1",//"TYPE 1",             //220   T:(家Α 1)          S:(模式1)


          "\xe7"" 2",//"TYPE 2",             //221   T:(家Α 2)          S:(模式2)
          "\xe7"" 3",//"TYPE 3",             //222   T:(家Α 3)          S:(模式3)


        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   S:(5保留)
        #endif
        
        "6 R",                //224   S:(限制级)

        #ifdef NOT_SUPPROT_VCD
        "NOT SUPPORTED CD",           //225   S:(错误碟片)
        #else
        "\r\x35""\r\x36",//"ERR DISC",           //225   S:(错误碟片)
        #endif

        #if defined(MUSTEK_PORTABLE_DVD)
        "MAIN PAGE", 	  //226
        #else
        "\r\xef""\r\xea",//"DIGITAL SETUP",      //226   T:(计絏砞竚)
        #endif	
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        #if defined(MUSTEK_PORTABLE_DVD)
        "NIGHT MODE", 	  //227
        #else
        "MIC ""\r\xea",//"MIC SETUP",          //227   T:(杠旦砞竚)
        #endif
        "MIC ""\xb1",//"MIC VOL",            //228   T:(杠旦秖)
        #endif
        "CD RECOVERING",      //229   T:(岿い)     ------------- not use
        "SMART UPGRADE",      //230   T:(醇ど)
        "UPGRADE TO V ",      //231   T:(どΘ)
        "UPGRADING",          //232   T:(どい)
          "\r\x38""\r\x39",//"DON'T POWER OFF",	//233   T:(づ闽诀)	//YAOWH MODIFY 04-10-26
          "\x74"" 0",//"REGION 0",           //234   T:(0 跋)
          "\x74"" 1",//"REGION 1",           //235   T:(1 跋)
          "\x74"" 2",//"REGION 2",           //236   T:(2 跋)
          "\x74"" 3",//"REGION 3",           //237   T:(3 跋)
          "\x74"" 4",//"REGION 4",           //238   T:(4 跋)
        "\r\xe5""\r\xea",//"LANGUAGE SETUP",     //239   T:(粂ē砞竚)
#ifdef  JIEKE_DVD
        "GIEC",               //240
#elif defined(BBK_DVD)
          "\x98",//"ZOOM",               //240
#elif defined(NINTAUS_OSD_STR)
    ">>>",
#elif defined(SUPPORT_FUNCTION_MENU)
        "DISPLAY",            //240 
#elif defined(GBM_PORTABLE_DVD)||defined(SUNPLUS_8202P_DEMOBOARD) 
        "LOW BATTERY",        //240         
#else        
        "",                   //240   //not use
#endif      
        "\r\xf7""\r\xf6",//"MAIN PAGE",          //241   T:()
#if !defined(BBK_DVD)
         "\r\x3a""\xe5",//"AUDIO LANG",       //242   T:(繵粂ē)
#else
         "\r\x3a",//"AUDIO",              //242   T:(繵粂ē) //axel 2004/1/27 03:58 eliminate "LANG"
#endif
#ifdef DISC_INFO_KEY  //fengjl  3-11-25 9:55
/*         "SUBP LANG",      //243   T:(辊粂ē)*/ //axel 2004/1/27 03:58 eliminate "LANG"
        "SUBP",      //243   T:(辊粂ē)
#elif defined(BBK_DVD)
          "\r\x3b""\r\x3c",//"SUBTITLE",           //243   T:(辊粂ē)
#else
           "\r\x3b""\r\x3c",//"SUBTITLE LANG",      //243   T:(辊粂ē) //axel 2004/1/27 03:58 eliminate "LANG"
#endif
        "\x86""\xef",//"MENU LANG",          //244   T:(垫虫粂ē)
      "\r\x3d""\r\x3e",//"DOWNMIX",            //245   T:(睼家Α)
     
       "\r\x3f""\r\x40",//"RESTORE",            //246   T:(確)
       
        "LT/RT",              //247
        "VSS",                //248   T:(店览吏露羘)      S:(虚拟环绕声)
	#if defined(MUSTEK_PORTABLE_DVD)
		"TV SIGNAL",	//249
		"AUTO SEARCH",	//250
		"FINE TUNE",	//251
		"FAVORITE LIST",	//252
		 "\r\x3c""+/-",//"CHANNEL +/-",	//253
	#else        
        "OP ""\xe8",//"OP MODE",            //249   T:(块家Α)        S:(输出模式)
        "LINE ""\r\x46",//"LINE OUT",           //250   T:(絬隔块)        S:(线路输出)
        "RF REMOD",           //251   T:(RF 秸俱)         S:(RF调整)
        "DUAL ""\x93",//"DUAL MONO",          //252   T:(オ+)           S:(左+右)
        "MIX ""\x93",//"MIX MONO",           //253   T:(睼羘笵)        S:(混合声道)
    #endif    
        "\xa2""\r\xe8",//"SURND MODE",         //254   T:(吏露家Α)        S:(环绕模式)

          "\r\x41""\r\x42",//"\r\x43""\r\x44",//"PRE STOP",           //255   T:                S:(准停止)
 
//============================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER

},
#endif  //USE_ARABIC_OSD
#ifdef USE_GREECE_OSD
//English
{
        "",                   //0
        "X""\r\xa8""PI""\r\xa9""\r\xaa""KO",            //1     T:(礚盒)            S:(无碟)
        #if defined(SKYWORTH_DVD)||defined(BBK_DVD)||defined(INVALID_DISPLAY_HAND)     //#ifdef ALWAYS_DISPLAY_NODISC_ICON    fengjl add 3-12-7 14:28
        OS_NO,
        #else
        "AKYPO ""\r\xab""\r\xb0""HKTPO",        //2     T:(眤岿 hand)   S:(您按错了 HAND)
        #endif
        "KOMMATI",                //3     T:(Ρヘ)            S:(曲目)
        OS_ICON_SVCD,         //4
        "DE-INTERLACE",//"CHINESE",            //5  not use
        "ANOI""\r\xad""MA",               //6     T:()            S:(出仓)
        "K""\r\xb0""EI""\r\xa9""IMO",              //7     T:(闽)            S:(关仓)
        "ANA""\r\xab""APA""\r\xad""\r\xa8""\r\xad""H",               //8     T:(冀)            S:(播放)
        "\r\xab""EPIOXH 5",//"REGION 5",           //9     T:(5 跋)            S:(5区)
        "\r\xab""AY""\r\xa9""H",//"PAUSE",              //10    T:(既氨)            S:(暂停)
        "TYXAYA",//"RANDOM",             //11    T:(繦诀冀)        S:(随即播放)
        "\r\xa9""YNEXEIA",//"RESUME",             //12    T:(確冀)        S:(恢复播放)
        "\r\xaa""IAKO""\r\xab""H",//"STOP",               //13    T:(氨ゎ)            S:(停止)
        "BHMA",//"STEP",               //14    T:(˙秈)            S:(单步)
        "E""\r\xab""I""\r\xb0""O""\r\xad""H",//"SELECT",             //15    T:(匡拒)            S:(选择)

        #if defined(FUSS_DVD)||defined(HUAJIA_DVD)||defined(HIMAGE_CARD_READER)||defined(MINTON_DVD)   //NONO 2-5-15 3:01
            "\r\xae""OPT""\r\xa8""NEI",//"LOADING",        //16    T:(弄盒)            S:(读碟)
        #elif defined(BBK_DVD)   //fengjl add 
             "\r\xae""OPT""\r\xa8""NEI",//"READING",       //16     T:(弄盒)            S:(读碟)
        #elif defined(SETUP_DONGLI459)||defined(KENLOON_DVD)||defined(SHOW_LOAD_WHEN_READ)   //YAOWH  04-07-30
            "\r\xae""OPT""\r\xa8""NEI",//"LOAD",
        #else
            "\r\xae""OPT""\r\xa8""NEI",//"READ",           //16    T:(弄盒)            S:(读碟)
        #endif

        "REGION 6",           //17    T:(6 跋)
        
        #ifdef NO_SPDIF
        #ifdef HIMAGE1251    //fengjl add 2004-02-20 20:36
        "SPDIF/ANENEP""\r\xad""O",//"SPDIF/OFF",
        #else
         "SPDIF/ANENEP""\r\xad""O",//"ANALOG",             //18    T:(家览)
        #endif
        #else//NO_SPDIF
         "SPDIF/ANENEP""\r\xad""O",//"SPDIF/OFF",             //18    T:(家览)
        #endif//NO_SPDIF
        
        #ifdef HJ_APEX_FIX_SHOW_OSD
        "M""\r\xab""PO""\r\xa9""TA",//"FF",            //19    T:(е秈)
        "\r\xab""I""\r\xa9""\r\xa8",//"FR",           //20    T:(е癶)
        #else//HJ_APEX_FIX_SHOW_OSD
        "M""\r\xab""PO""\r\xa9""TA",//"FORWARD",            //19    T:(е秈)
        "\r\xab""I""\r\xa9""\r\xa8",//"BACKWARD",           //20    T:(е癶)
        #endif//HJ_APEX_FIX_SHOW_OSD
        "E""\r\xab""OMENO",//"NEXT",               //21    T:(Ρ >>)

        #if defined(SETUP_PASSWORD_GUI)      //fengjl add  4-1-19 17:09
           "\r\xaa""IOP""\r\xac.""K""\r\xa8""\r\xaa""IKOY",//"PASSWD EDIT",      // 22
        #else
           "\r\xaa""IOP""\r\xac.""K""\r\xa8""\r\xaa""IKOY",//  "",                 //22
        #endif
        
        "\r\xab""POH""\r\xad""OYMENO",//"PREV",               //23    T:(Ρ <<)

        "KATA""\r\xb0""O""\r\xad""O""\r\xa9",//"DIR",               //24

         "E""\r\xab""I""\r\xa9""TPO""\r\xae""H",//"RETURN",             //25    T:(垫虫)
        Ch_repx,              //26
        Ch_rep1,              //27
        Ch_repd,              //28
        "ANENEP""\r\xad""O",//"OFF",                //29    T:(礚)              S:(无)
        "MENOY",//"MENU",               //30    T:(匡虫)            S:(选单)
        "\r\xa9""KOP",//"SCORE",              //31    T:(だ计)            S:(分数)
#ifdef  ONE_KEY_PASS
        "MAPKAPI""\r\xa9""MA",//"SAVING THE POINT",  //32    T:(癘拘)            S:(记忆)
#else
        "MAPKAPI""\r\xa9""MA",//"MARK",               //32    T:(癘拘)            S:(记忆)
#endif

        "ANAZHTH""\r\xa9""H",//"BROWSE",             //33    T:(聅凝)            S:(浏览)
        "\r\xab""PO""\r\xad""PAMMA",//"PROG",               //34    T:(絪祘)            S:(编程)
        "A""\r\xab""O""\r\xac""HKEY""\r\xa9""H ""\r\xb0""O""\r\xad""OTY""\r\xad""OY..",//"SAVING LOGO...",     //35    T:                  S:(画面抓取中)
        #ifdef SPEAKER_CONFIG	
           "O""\r\xb0""A ME""\r\xad""A""\r\xb0""A HXEIA",//    LARGE",	//36	T:()
        #else
           "O""\r\xb0""A ME""\r\xad""A""\r\xb0""A HXEIA",//"ALL LG SPK",         //36    T:(家Α1)
        #endif        
        "E""\r\xab""ANA""\r\xb0""H""\r\xaf""H",//   "REP",                //37    T:(確)
        "E""\r\xab""ANA""\r\xb0""H""\r\xaf""H KATA""\r\xb0""O""\r\xad""OY",//"REP DIR",            //38    T:(ヘ魁確)
        "E""\r\xab""AN 1",//"REP 1",              //39    T:(虫Ρ確)
        "E""\r\xab""AN O""\r\xb0""A",//  "REP ALL",            //40    T:(盒確)
        "AKYP""\r\xa8""\r\xa9""H E""\r\xab""AN",//"REP CANCEL",         //41    T:(確)
        #ifdef SPEAKER_CONFIG
        	"O""\r\xb0""A MIKPA HXEIA",//"SMALL",    //42    T:()
        #else
            "O""\r\xb0""A MIKPA HXEIA",//"ALL SM SPK",         //42    T:(家Α2)
        #endif
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 ENH""\r\xb0""IKE""\r\xa9",//"8 BYPASS",            //43
        #else//#ifdef HJ_APEX_FIX_SHOW_OSD
            "8 ENH""\r\xb0""IKE""\r\xa9",//"8 ADULT",            //43
        #endif//#ifdef HJ_APEX_FIX_SHOW_OSD
        #else
            "8 ENH""\r\xb0""IKE""\r\xa9",// "8",
        #endif
        "7 AN""\r\xa8"" T""\r\xa8""N 17",//"7 NC-17",            //44    T:(虫Ρ冀)
        "METABA""\r\xa9""H",//"GOTO",               //45    T:(穓)
        "\r\xa9""I""\r\xad""A""\r\xa9""H",//"MUTE",               //46    T:(繰)
        "MONO AP.",             //47    T:(オ羘笵)
        "MONO ""\r\xaa""E.",             //48    T:(羘笵)
        "STEREO",             //49    T:(ミ砰羘)
#ifdef HANYANG_MUTEOFF      //caohui 2004-5-13 15:59
        "E""\r\xab""ANA""\r\xae""OPA HXOY",//"MUTE OFF",                   //50    //not use
#else
        "E""\r\xab""ANA""\r\xae""OPA HXOY",//"DEMUTE",                   //50    //not use
#endif
        "LIVE",               //51    T:
#ifdef QSI_SETUP_MENU//liweihua 2004-6-16
        "KARAOK SETUP",                   //52

#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "",                   //52    //not use
#endif
        #ifdef SPEAKER_CONFIG
        	"MEIKTA HXEIA",//"OFF",  //53	T:(闽)
        #else
            "MEIKTA HXEIA",//"MIXED SPK",          //53    T:(家Α3)
        #endif 
        OS_ICON_CDROM,        //54
        "\r\xa8""PA",//"TIME",               //55    T:(丁)            S:(时间)
#ifdef RECORD_KEY
    #ifdef NINTAUS_OSD_STR    //2004-2-11 11:35张宇P
        "EN""\r\xaa""EI""\r\xb1""H ""\r\xad""\r\xa8""NIA""\r\xa9",//"THE DISC HAS RECORD.",
     #else
        "EN""\r\xaa""EI""\r\xb1""H ""\r\xad""\r\xa8""NIA""\r\xa9",//"THE DISC HAS RECORD POINT", //56
      #endif
#elif defined(SYBER_DVD)
        "EN""\r\xaa""EI""\r\xb1""H ""\r\xad""\r\xa8""NIA""\r\xa9",//"ANGLE MARK",                   //56    S:(角度标记)
#elif defined(SHOW_MP4_INIT_STR)    //wangwei-2004/4/28
        "EN""\r\xaa""EI""\r\xb1""H ""\r\xad""\r\xa8""NIA""\r\xa9",//"INITIALIZING...",                 //56 
#else
        "EN""\r\xaa""EI""\r\xb1""H ""\r\xad""\r\xa8""NIA""\r\xa9",//"",                   //56    //not use
#endif
        "ZOYM",//"ZOOM",               //57    T:(糴)            S:(放宽)

       
        "K""\r\xb0""EI""\r\xa9""TO""\r\xa9 ""Y""\r\xab""OTIT""\r\xb0""O""\r\xa9",//"PLEASE PRESS RECORD KEY TO PLAY IT.",
                   //58    //not use
   
        OS_ICON_LANG,         //59
        "EI""\r\xa9""A""\r\xad""\r\xa8""\r\xad""H",//"INTRO",              //60    T:(苯磞)            S:(扫描)
        "SRND",//"SURROUND",           //61    T:(吏露)            S:(环绕)
        "PBC",                //62
#ifdef RECORD_KEY
       #ifdef NINTAUS_OSD_STR    //2004-2-11 11:35张宇P
           "IT WILL BE AUTO PLAYED AFTER 6S.",
     #else
        "OTHER KEY:PLAY FROM BEGINNING",  //63
          #endif
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
       Ch_repf,       //63         //zhuyf 2004/8/10

#else//DIVIDE_AC3_DTS_SPDIF_OUTPUTS
        "",            //63    T:(抖冀)
#endif     
        "AKYP""\r\xa8""\r\xa9""H TYXAIA""\r\xa9",//"RAND CANCEL",        //64    T:(繦诀冀)    S:(随即播放取消)
        "KATA""\r\xa9""TA""\r\xa9""H M""\r\xab""A""\r\xa9""\r\xa8""N",//"BASS MODE",          //65    T:(家Α)

        "",                   //66

        "E""\r\xab""ANA""\r\xb0""H""\r\xaf""H A-",                //"REPEAT A-",          //67    T:(確A-)          S:(重复 A )
      
        "P-SCAN VGA",               //"PC-VGA",           //68
       
        "E""\r\xab""ANA""\r\xb0""H""\r\xaf""H A-B",         //"REPEAT A-B",         //69    T:(確A-B)         S:(重复播放A-B)

        "KEYP""\r\xa8""\r\xa9""H AB",        // "AB CANCEL",         //70    T:(確)        S:(A-B取消)
       "KEYP""\r\xa8""\r\xa9""H ""\r\xab""PO""\r\xad""PAMMATO""\r\xa9",    // "PRG CANCEL",         //71    T:(絪胆)            S:(编程取消)
        "",                   //72

       "ANA""\r\xab""APA""\r\xad""\r\xa8""\r\xad""H ME ENA ""\r\xab""\r\xb0""HKTPO",    // "ONE KEY PLAY",      //73

        OS_ICON_VCD,          //74
        "E""\r\xb0""A""\r\xae""PA MOY""\r\xa9""IKH",   //"LIGHT MUSIC",                   //75    
        #if defined(SHOW_VCD_VER_INFO)||defined(SYBER_DVD)  //yaowh add for kenloon 04-08-03
        OS_ICON_VCD20,        //76    //xulf 2003-11-17
        #else        
        "ELECTRON",                   //76   
        #endif
        "CVBS",//OS_ICON_MP3,          //77
        OS_ICON_CDDA,         //78

        "48KHZ",                   //79    //not use
        "96KHZ",                   //80    //not use
        "192KHZ",                   //81    //not use

       "ZOYM E""\r\xab""AN""\r\xa8",    // "ZOOM UP",            //82    T:(礶簿)        S:(放大上)
       "ZOYM KAT""\r\xa8" ,   //"ZOOM DOWN",          //83    T:(礶簿)        S:(放大下)
       "ZOYM API""\r\xa9""TEPA",   //"ZOOM LEFT",          //84    T:(礶オ簿)        S:(放大左)
       "ZOYM ""\r\xaa""E""\r\xb1""IA",   //"ZOOM RIGHT",         //85    T:(礶簿)        S:(放大右)
       "KANA""\r\xb0""I",    // "CH",                 //86    T:(彻竊)            S:(章节)
        "ECHO",               //87    T:(睼臫)            S:(混响)
        "TT",                 //88    T:(夹肈)            S:(标题)
        "M""\r\xab""ANTA",   //"BAND",               //89    T:(繵眯)
       
       "ENTA""\r\xa9""H",    // "VOL",                //90    T:(秖)            S:(音量)

        "DOWN SAMPLE",        //91    //not use
        "\r\xab""\r\xb0""HKTPO",   //"KEY",                //92    T:(秸)            S:(音调)
        "S-VIDEO",            //93

        "9EIKONE""\r\xa9""_1",   //"9FRAME_1",           //94    T:(虫Ρ礶)      S:(单曲九画面)
        "AYTOMATO AP",   //"AUTO L",             //95    T:(笆钡佰オ)      S:(自动接唱左)
        "AYTOMATO ""\r\xaa""E",   //"AUTO R",             //96    T:(笆钡佰)      S:(自动接唱右)
        "XAMH""\r\xb0""A",   //"LOW",                //97    // LOW

         "\r\xa9""YNEXOMENH ANA""\r\xab""APA""\r\xad""\r\xa8""\r\xad""H",// "SEQ PLAY",           //98    T:(抖冀)        S:(顺序播放)

       "ANA""\r\xab""APA""\r\xad""\r\xa8""\r\xad""H MENOY",  // "MENU PLAY",          //99    T:(垫虫冀)        S:(菜单播放)

        "XPONO""\r\xa9 ""\r\xaa""I""\r\xa9""KOY",   //"DISC TIME",          //100

    "O""\r\xac""ONH_VFD_""\r\xa8""PA_API""\r\xac""MO""\r\xa9",//OS_VFD_TIME_NUM,        //101
    "PY""\r\xac""MI""\r\xa9""H XPONO""\r\xaa""IAKO""\r\xab""TH",   //"TIMER SETUP",          //102              

       "ME""\r\xa9""O",    // "MEDIUM",             //103   // MEDIUM
#ifdef MINTON_DVD
       "\r\xab""PO""\r\xad""PAMMATI""\r\xa9""MENH ANA""\r\xab""APA""\r\xad""\r\xa8""\r\xad""H" ,    // "PROGRAM PLAY",           //104   T:(絪导僵)          S:(编程播放)
#else
        "\r\xab""PO""\r\xad""P.ANA""\r\xab""AP.",   //"PRG PLAY",           //104   T:(絪导僵)          S:(编程播放)
#endif
        "Y""\r\xaf""H""\r\xb0""O",   //"HIGH",               //105   // HIGH
        "\r\xaa""YNAMIKH K""\r\xb0""IMKAKA",   //"DYNAMIC RANGE",      //106
        OS_ICON_DVD,          //107
       "\r\xad""\r\xb0""\r\xa8""\r\xa9""\r\xa9""A O""\r\xac""ONH""\r\xa9",    // "OSD LANGUAGE",       //108   T:(礶陪ボ粂ē)    S:(画面显示语言)
        OS_ICON_SUBT,         //109

        
       "TY""\r\xab""O""\r\xa9"" TV",    // "TV TYPE",            //110   T:(?¨?1?|ìe-?à?è??§¨°)    S:(?¨￠???-???à¨¨¨¤y)
       "\r\xb0""EITOYP""\r\xad""IA TV",   //"TV MODE",        //111   T:(1q|ì?????§?|?)      S:(|ì?¨o¨??¨2??¨o?)
        
       "E""\r\xb1""O""\r\xaa""O""\r\xa9"" PY""\r\xac""MI""\r\xa9""E""\r\xa8""N" ,   //"EXIT SETUP",         //112   T:(癶砞竚垫虫)    S:(推出设置菜单)

       "E""\r\xb1""O""\r\xab""O""\r\xa9"" HXOY" ,   //"AUDIO OUT",          //113   T:(计絏块)        S:(数码输出)
       "VIDEO",              //114   T:(跌繵块)        S:(视频输出)
       "K""\r\xa8""\r\xaa""IKO""\r\xa9 ""\r\xab""PO""\r\xa9""BA""\r\xa9""H""\r\xa9",    //"PASSWORD",           //115   T:(盞絏)            S:(密码)

       "\r\xad""ONIKO""\r\xa9"" E""\r\xb0""E""\r\xad""XO""\r\xa9",// "PARENTAL",//"RATING",             //116   T:()            S:(级别)

#ifdef EASTECH_NEW_SETUP_MENU
        "SPDIF/RAW",         //117   T:(SPDIF/方絏)      S:(SPDIF/源码)
#else
        "SPDIF/RAW",          //117   T:(SPDIF/方絏)      S:(SPDIF/源码)
#endif
      
        "\r\xa9""\r\xae""A""\r\xb0""MA",   //"ERROR",              //118  


        "SPDIF/PCM",          //119

        "PAL-M",                //120
                
        "\r\xa9""YN""\r\xaa""YA""\r\xa9""MO""\r\xa9""-YUV",   //"INTERLACE-YUV",                //121   T:(跌繵だ秖)        S:(视频分量)
        
        "AYTOMATO",   //"AUTO",               //122   T:(笆)            S:(自动)
        "ANENEP""\r\xad""O",   //"OFF",                //123   T:(闽)              S:(关)
 
        "XPONO""\r\xa9"" KOMMATIOY",   //"TRACK TIME",//124
      
        "KE""\r\xae""A""\r\xb0""AIO",  //"CHAPTER",            //125   T:(彻竊)            S:(章节)
        "TIT""\r\xb0""O""\r\xa9",   //"TITLE",              //126   T:(夹肈)            S:(标题)
        OS_ICON_ANGLE,        //127

        "P-SCAN YPBPR",       //128   T:(硋︽跌繵だ秖)

        OS_16_9,              //129   T:(16:9 --)
        OS_4_3LB,             //130   T:(4:3LB --)
        OS_4_3PS,             //131

        "PAL",                //132
        "NTSC",               //133
        "PAL60",              //134

         "OXI AKATA""\r\xb0""\r\xb0""H""\r\xb0""O" ,//  "NO ADULT",           //135   T:(辅导级)
         "A""\r\xa9""\r\xae""A""\r\xb0""E""\r\xa9 ""\r\xad""IA ""\r\xab""AI""\r\xaa""IA",  //  "KID SAFE",           //136   T:(保留)
         "\r\xab""POBO""\r\xb0""H O""\r\xb0""\r\xa8""N",//  "VIEW ALL",           //137   T:(礚)

            "5.1CH",              //138   T:(5.1羘笵)

        "SUBWOOFER",          //139   T:(禬)
        "KA""\r\xac""APOTHTA",//"SATURATION",         //140   SATURATION
        "ENEP""\r\xad""O",   //"ON",                 //141   T:
        OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
        "\r\xaa""IA""\r\xad""PA""\r\xae""H",   //"CLEAR",              //145   T:(睲埃)
        "  T  C",               //146   //2004-2-23 03:56张宇P
        "--:--",              //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
       "\r\xaa""IOP""\r\xac""\r\xa8""\r\xa9""H",    // "EDIT",               //149   T:(絪胯)
#ifdef RECORD_KEY 
        "\r\xa9""YNEXEIA E""\r\xad""\r\xad""PA""\r\xae""H""\r\xa9",//"RECORD RESUME",          //150
#else
        "",//OS_DIR1,              //150
#endif


        "",//OS_DIR2,              //151

        OS_DIR3,              //152
        OS_DIR4,              //153
        "PAL-NC",//OS_DIR5,              //154

        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
        "XPOIA",   //"HUE",                //157   HUE
#ifdef BBK_NEW_SETUP
        "PROLOGIC II",//"-:--:--",            //158  
#else
        "PROLOGIC",//"-:--:--",            //158     
#endif        
       "\r\xb0""EITOYP""\r\xad""IA TAINI""\r\xa8""N",    // "MOVIE MODE",//"TRACK SEARCH",       //159    
       "\r\xb0""EITOYP""\r\xad""IA MOY""\r\xa9""IKH""\r\xa9",//"MUSIC MODE",//"DISC SEARCH",        //160    

        "\r\xa9""YN""\r\xaa""YA""\r\xa9""MO""\r\xa9",   //"INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)

        #ifdef REMAIN_TIME//nono 2-7-12 20:06
            "T",                  //162
        #else
            "",           //162
        #endif

        OS_DIR0,              //163
        "ANTI""\r\xac""E""\r\xa9""H",   //"CONTRAST",           //164   CONTRAST
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
        "KANA""\r\xb0""I",   //"CHANNEL",            //168   T:(羘笵)            S:(声道)
        "\r\xae""\r\xa8""TEINOTHTA",   //"BRIGHTNESS",         //169   BRIGHTNESS
        "F/W ID",             //170   T:(硁ン絪絏)        S:(软件编码)
        "CHIP ID",            //171   T:(絪絏)        S:(芯片编码)
        "\r\xab""EPIOXH",   //"REGION",             //172   T:(跋絏)            S:(区码)
        "MNHMH",   //"MEMORY",//"FUNCTION",           //173  //not use T:(滦弄滦佰)        S:(复读复唱)
        "DYNAMIC",//"MODE",               //174  //not use  T:(家Α)            S:(模式)


        "Z""\r\xa8""NTANO",   //"LIVELY",               //175
        "\r\xab""APA""\r\xa9""TA""\r\xa9""H",   //"SHOWPLACE",            //176
        "A""\r\xab""A""\r\xb0""O",   //"MILD",                 //177

        "MIC1 VOL",//"COMPARE",            //178   //not use T:(癸ゑ)            S:(对比)
        "MIC2 VOL",//"COUNTER",            //179   //not use T:(滦Ω计)        S:(重复次数)


        "\r\xab""POH""\r\xad"".KE""\r\xae""A""\r\xb0""AIO",   //"PREV CHAPTER",      //180   S:上一章节
        "E""\r\xab""OM.KE""\r\xae""A""\r\xb0""AIO",   //"NEXT CHAPTER",      //181   S:下一章节


#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",             //182   T:(禬丁)        S:(超长时间)
#endif


        "ANA""\r\xab""APA""\r\xad""\r\xa8""\r\xad""H TIT""\r\xad""OY",   //"PLAYTITLE",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "XPONO""\r\xa9"" KE""\r\xae""A""\r\xb0""AIOY",   //"TITLETIME",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "XPONO""\r\xa9"" KE""\r\xae""A""\r\xb0""AIOY",   //"CHPTIME",//"MANUAL",             //185   T:(も笆)            S:(手动)


        OS_DIR10,             //186
        OS_DIR11,             //187
        "\r\xa9""YNAY""\r\xb0""IA",   //"CONCERT",            //188   T:(贾芔)          S:(音乐厅)
        "EKK""\r\xb0""H""\r\xa9""IA",  //"CHURCH",             //189   T:(毙绑)            S:(教堂)
        "\r\xab""A""\r\xac""HTIKO",   //"PASSIVE",            //190   T:(吏露)            S:(环绕)
        "EYPEIA",   //"WIDE",               //191   T:(糴初)            S:(宽场)

        "E""\r\xab""I""\r\xb0""O""\r\xad""H ","\r\b0""O""\r\xad""OTY""\r\xab""OY"   //"SELECT LOGO",          //192
        "\r\b0""O""\r\xad""OTY""\r\xab""O MPEG",// "MPEG LOGO",            //193

        "EQ",                 //194   T:(А颗)            S:(均衡)
        "BA""\r\xa9""IKO",   //"STANDARD",           //195   T:(夹非)            S:(标准)
        "K""\r\xb0""A""\r\xa9""IKH",   //"CLASSIC",            //196   T:(ㄥ)            S:(古典)
        "POK",   // "ROCK",               //197   T:(穘簎)            S:(摇滚)
        "TZAZ",   //"JAZZ",               //198   T:(里)            S:(爵士)
        "\r\xab""O""\r\xab",       //"POP",                //199   T:(瑈︽)            S:(流行)
        "XPH""K""\r\xa9""TH""\r\xa9",  //"USER",               //200   T:(┦)            S:(个性)
        "XAPAKTHPI""\r\xa9""TIKA",   //"ATTRIB",             //201   T:(┦)            S:(个性)
        "SF",                 //202   T:(篊秈)            S:(慢进)
        "SB",                 //203   T:(篊癶)            S:(慢退)

        "C",                  //204   //show "C"

       "KENTPIKO",    //"CENTER",              //205   T:(い竚喘羘竟)      S:(中置扬声器)
        "\r\xab""I""\r\xa9""\r\xa8",   //"REAR",               //206   T:(吏露喘羘竟)      S:(环绕扬声器)
        
        "TV-RGB",             //207
        
        "4 PG13",             //208   T:(辅导级)
        "KA""\r\xac""Y""\r\xa9""TEPH""\r\xa9""H KENTPIKOY",   //"CENTER DELAY",       //209   T:(い竚┑筐)
        "KA""\r\xac""Y""\r\xa9""TEPH""\r\xa9""H ""\r\xab""I""\r\xa9""\r\xa8",   //"REAR DELAY",         //210   T:(吏露┑筐)
        "M""\r\xab""PO""\r\xa9""TINA",   //"FRONT",              //211   T:(玡竚喘羘竟)
        "PY""\r\xac""MI""\r\xa9""EI""\r\xa9"" EIKONA""\r\xa9",   //"VIDEO SETUP",        //212   VIDEO SETUP
        "O""\r\xb1""YTHTA",   //"SHARPNESS",          //213   SHARPNESS
        "PY""\r\xac""MI""\r\xa9""EI""\r\xa9"" \r\xa9""Y""\r\xa9""THMATO""\r\xa9",   //"SYSTEM SETUP",       //214   T:(╰参砞竚)        S:(系统设置)
        "PY""\r\xac""MI""\r\xa9""EI""\r\xa9"" HXEI""\r\xa8""N",  //"SPEAKER SETUP",      //215   T:(喘羘竟砞竚)      S:(扬声器设置)
        "PY""\r\xac""MI""\r\xa9""EI""\r\xa9"" HXOY",   //"AUDIO SETUP",        //216   T:(繵砞竚)        S:(音频设置)
        "\r\xab""POE""\r\xab""I""\r\xb0""O""\r\xad""H",   //"DEFAULT",            //217   T:()          S:(缺省值)
        
        "GRP",                //218   //not use

        "\r\xab""PO""\r\xae""Y""\r\xb0""A""\r\xb1""H O""\r\xac""ONH""\r\xa9",   //"SCREEN SAVER",       //219   T:(辊玂臔)        S:(屏幕保护)

        "TY""\r\xab""O""\r\xa9"" 1",   //"TYPE 1",             //220   T:(家Α 1)          S:(模式1)


        "TY""\r\xab""O""\r\xa9"" 2",   //"TYPE 2",             //221   T:(家Α 2)          S:(模式2)
        "TY""\r\xab""O""\r\xa9"" 3",   //"TYPE 3",             //222   T:(家Α 3)          S:(模式3)


        "5 PG-R",                  //223   S:(5保留)
        
        "6 R",                //224   S:(限制级)

        "\r\xa9""\r\xae""A""\r\xb0""MA",   //"ERR DISC",           //225   S:(错误碟片)
    
        "\r\xaf""H""\r\xae""IAKE""\r\xa9"" PY""\r\xac""MI""\r\xa9""EI""\r\xa9",//"DIGITAL SETUP",      //226   T:(计絏砞竚)
       
        "PY""\r\xac""MI""\r\xa9""EI""\r\xa9"" MIKPO""\r\xae""\r\xa8""NOY",   //"MIC SETUP",          //227   T:(杠旦砞竚)
        "ENTA""\r\xa9""H MIKPO""\r\xae""\r\xa8""NOY",   //"MIC VOL",            //228   T:(杠旦秖)
    
        "ANAKTH""\r\xa9""H CD",   //"CD RECOVERING",      //229   T:(岿い)     ------------- not use
        "E""\r\xb1""Y""\r\xab""NH ANABA""\r\xac""MI""\r\xa9""H",   //"SMART UPGRADE",      //230   T:(醇ど)
        "ANABA""\r\xac""MI""\r\xa9""H ""\r\xa9""E V",   //"UPGRADE TO V ",      //231   T:(どΘ)
        "ANABA""\r\xac""MI""\r\xa9""H",   //"UPGRADING",          //232   T:(どい)
        "MH ANENEP""\r\xad""O",   //"NOT POWER OFF",      //233   T:(づ闽诀)
        "\r\xab""EPIOXH 0",   //"REGION 0",           //234   T:(0 跋)
        "\r\xab""EPIOXH 1",   //"REGION 1",           //235   T:(1 跋)
        "\r\xab""EPIOXH 2",   //"REGION 2",           //236   T:(2 跋)
        "\r\xab""EPIOXH 3",   //"REGION 3",           //237   T:(3 跋)
        "\r\xab""EPIOXH 4",   //"REGION 4",           //238   T:(4 跋)
        "PY""\r\xac""MI""\r\xa9""EI""\r\xa9 ""\r\xad""\r\xb0""\r\xa8""\r\xa9""\r\xa9""A""\r\xa9",   //"LANGUAGE SETUP",     //239   T:(粂ē砞竚)

        "ZOYM",   //"ZOOM",               //240
     
        "KYPIA ""\r\xa9""E""\r\xb0""I""\r\xaa""A",   //"MAIN PAGE",          //241   T:()

        "HXO""\r\xa9",   //"AUDIO",              //242   T:(繵粂ē) //axel 2004/1/27 03:58 eliminate "LANG"

        "Y""\r\xab""OTIT""\r\xb0""OI",   //"SUBTITLE",           //243   T:(辊粂ē)

        "\r\xad""\r\xb0""\r\xa8""\r\xa9""\r\xa9""A MENOY",   //"MENU LANG",          //244   T:(垫虫粂ē)
        "DOWNMIX",            //245   T:(睼家Α)
     
        "E""\r\xab""ANA""\r\xae""OPA",   //"RESTORE",            //246   T:(確)
       
        "AP/""\r\xaa""E",   //"LT/RT",              //247
        "VSS",                //248   T:(店览吏露羘)      S:(虚拟环绕声)
        "KATA""\r\xa9""TA""\r\xa9""H ""\r\xb0""EITOYP""\r\xad""IA""\r\xa9",   //"OP MODE",            //249   T:(块家Α)        S:(输出模式)
        "E""\r\xb1""O""\r\xaa""O""\r\xa9",   //"LINE OUT",           //250   T:(絬隔块)        S:(线路输出)
        "RF REMOD",           //251   T:(RF 秸俱)         S:(RF调整)
        "DUAL MONO",          //252   T:(オ+)           S:(左+右)
        "MIX MONO",           //253   T:(睼羘笵)        S:(混合声道)
        "\r\xb0""EITOYP""\r\xad""IA SURND",   //"SURND MODE",         //254   T:(吏露家Α)        S:(环绕模式)
#ifdef KSD_DVD
        "\r\xab""IE""\r\xa9""TE PLAY ""\r\xad""IA ""\r\xa9""YNEXEIA",   //"PRESS PLAY BUTTON TO CONTINUE",        //255   T:              S:请按播放键继续
#elif defined(DESAY_DVD)
        "\r\xab""IE""\r\xa9""TE PLAY ""\r\xad""IA ""\r\xa9""YNEXEIA",   //"PRESS PLAY BUTTON TO CONTINUE",
#elif defined(TONIC_DVD)
        "\r\xab""IE""\r\xa9""TE PLAY ""\r\xad""IA ""\r\xa9""YNEXEIA",   //"PRESS PLAY KEY TO CONTINUE",
#else
        "\r\xab""PO-""\r\xaa""IAKO""\r\xab""H",   //"PRE STOP",           //255   T:                S:(准停止)
#endif
//============================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "API""\r\xa9""TEPA-""\r\xaa""E""\r\xb1""IA",   //"LEFT-RIGHT",   //256        
        "\r\xab""AN""\r\xa8""-KAT""\r\xa8",   //"UP-DOWN",      //257

       "E""\r\xab""ANA""\r\xb0""H""\r\xaf""H TIT""\r\xb0""OY",    //"REP TITLE",     //258

    

       "E""\r\xab""ANA""\r\xb0""H""\r\xaf""H KE""\r\xae""A""\r\xb0""AIOY",    //"REP CHAPTER",    //259
       "E""\r\xab""ANA""\r\xb0""H""\r\xaf""H OMA""\r\xaa""A""\r\xa9",    //"REP GROUP",     //260

        "\r\xab""APAKA""\r\xb0""\r\xa9"" EI""\r\xa9""A""\r\xad""ETE NEO",   //" PLEASE INPUT NEW PASSWORD        ",  //261
        "\r\xab""A""\r\xb0""IO""\r\xa9"" K""\r\xa8""\r\xab""IKO""\r\xa9",   //"OLD PASSWD",               //262
        "NEO""\r\xa9"" K""\r\xa8""\r\xab""IKO""\r\xa9",   //"NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER

},
#endif  //USE_GREECE_OSD

#ifdef USE_BRAZIL_OSD
//brazil
{
        "",                   //0
        "SEM DISCO",            //1     T:(礚盒)            S:(无碟)
        #if defined(SKYWORTH_DVD)||defined(BBK_DVD)||defined(INVALID_DISPLAY_HAND)     //#ifdef ALWAYS_DISPLAY_NODISC_ICON    fengjl add 3-12-7 14:28
        OS_NO,
        #else
        OS_NO,//"INV""\xc1""LIDO",        //2     T:(眤岿 hand)   S:(您按错了 HAND)
        #endif
        "FAIX",                //3     T:(Ρヘ)            S:(曲目)
        OS_ICON_SVCD,         //4
        "CHIN""\xca""S",//"CHINESE",            //5  not use
        "ABRIR",               //6     T:()            S:(出仓)
        "FECHAR",              //7     T:(闽)            S:(关仓)
        "REPRODUZIR",               //8     T:(冀)            S:(播放)
        "REGI""\xc3""O 5",           //9     T:(5 跋)            S:(5区)
        "PAUSA",              //10    T:(既氨)            S:(暂停)
        "ALEAT""\xd3""RIO",             //11    T:(繦诀冀)        S:(随即播放)
        "RESUME",             //12    T:(確冀)        S:(恢复播放)
        "PARAR",               //13    T:(氨ゎ)            S:(停止)
        "PASSO",               //14    T:(˙秈)            S:(单步)
        "SELECIONAR",             //15    T:(匡拒)            S:(选择)

        #if defined(FUSS_DVD)||defined(HUAJIA_DVD)||defined(HIMAGE_CARD_READER)||defined(MINTON_DVD)   //NONO 2-5-15 3:01
            "LOADING",        //16    T:(弄盒)            S:(读碟)
        #elif defined(BBK_DVD)   //fengjl add 
            "READING",       //16     T:(弄盒)            S:(读碟)
        #elif defined(SETUP_DONGLI459)||defined(KENLOON_DVD)||defined(SHOW_LOAD_WHEN_READ)   //YAOWH  04-07-30
            "LOAD",
        #else
            "LER",           //16    T:(弄盒)            S:(读碟)
        #endif

        "REGI""\xc3""O 6",           //17    T:(6 跋)
        
        #ifdef NO_SPDIF
        #ifdef HIMAGE1251    //fengjl add 2004-02-20 20:36
        "SPDIF/DESLIG.",
        #else
        "ANAL""\xd3""GICO",             //18    T:(家览)
        #endif
        #else//NO_SPDIF
        "SPDIF/DESLIG.",             //18    T:(家览)
        #endif//NO_SPDIF
        
        #ifdef HJ_APEX_FIX_SHOW_OSD
        "FF",            //19    T:(е秈)
        "FR",           //20    T:(е癶)
        #else//HJ_APEX_FIX_SHOW_OSD
        "SEGUINTE",            //19    T:(е秈)
        "ANTERIOR",           //20    T:(е癶)
        #endif//HJ_APEX_FIX_SHOW_OSD
        "PR""\xd3""XIMO",               //21    T:(Ρ >>)

        #if defined(SETUP_PASSWORD_GUI)      //fengjl add  4-1-19 17:09
        "PASSWD EDIT",      // 22
        #elif defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "VGA",                  //22
        #else
        "SERVO DEBUG",        //22          //joshua, 20050711, modified for servo-debug function on OSD
        #endif

        "ANTERIOR",               //23    T:(Ρ <<)

        "DIR",               //24

        "VOLTAR",             //25    T:(垫虫)
        Ch_repx,              //26
        Ch_rep1,              //27
        Ch_repd,              //28
        "DES",                //29    T:(礚)              S:(无)
        "MENU",               //30    T:(匡虫)            S:(选单)
        "NOTA",              //31    T:(だ计)            S:(分数)
#ifdef  ONE_KEY_PASS
        "SAVING THE POINT",  //32    T:(癘拘)            S:(记忆)
#else
        "MARCA",               //32    T:(癘拘)            S:(记忆)
#endif

        "BUSCA",             //33    T:(聅凝)            S:(浏览)
        "PROG",               //34    T:(絪祘)            S:(编程)
        "SAVING LOGO...",     //35    T:                  S:(画面抓取中)
        #ifdef SPEAKER_CONFIG	
        "LARGE",	         //36	T:()
        #else
        "ALL LG SPK",         //36    T:(家Α1)
        #endif        
        "REPETIR",                //37    T:(確)
        "REP DIR",            //38    T:(ヘ魁確)
        "REPETIR",              //39    T:(虫Ρ確)
        "REP TUDO",            //40    T:(盒確)
        "CANCELAR REPETIR",//LILY"CANCELAR REP",         //41    T:(確)
        #ifdef SPEAKER_CONFIG
       "SMALL",                //42    T:()
        #else
        "ALL SM SPK",         //42    T:(家Α2)
        #endif
        #ifdef FIX_RATING_8_DISPLAY
          #ifdef HJ_APEX_FIX_SHOW_OSD
            "8 BYPASS",            //43
        #else//#ifdef HJ_APEX_FIX_SHOW_OSD
        "8 ADULTO",//"8 ADULT",            //43
        #endif//#ifdef HJ_APEX_FIX_SHOW_OSD
        #else
        "8",
        #endif
        "7 NC-17",            //44    T:(虫Ρ冀)
        "GOTO",               //45    T:(穓)
        "MUDO",               //46    T:(繰)
        "VOCAL ESQ",             //47    T:(オ羘笵)
        "VOCAL DIR",             //48    T:(羘笵)
        "SEM VOCAL",             //49    T:(ミ砰羘)
#ifdef HANYANG_MUTEOFF      //caohui 2004-5-13 15:59
        "MUTE OFF",                   //50    //not use
#elif defined(ORITRON_HK_DVD)//libing 2005-8-19 17:33
		"MODO",       				//50
#else
        "DEMUTE",                   //50    //not use
#endif
        "LIVE",               //51    T:
#ifdef QSI_SETUP_MENU//liweihua 2004-6-16
        "KARAOK SETUP",                   //52

#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISC",               //52
#else
        "",                   //52    //not use
#endif
        #ifdef SPEAKER_CONFIG
        "DESLIG.",                //53	T:(闽)
        #else
        "MIXED SPK",          //53    T:(家Α3)
        #endif 
        OS_ICON_CDROM,        //54
        #ifdef OP_CUST_UI//libing 2005-5-11 11:39
        "TEMPO JPEG",               //55    T:(丁)            S:(时间)
        #else
        "TEMPO",                       //55
        #endif
#ifdef RECORD_KEY
    #ifdef NINTAUS_OSD_STR    //2004-2-11 11:35张宇P
           "THE DISC HAS RECORD.",
     #else
        "THE DISC HAS RECORD POINT", //56
      #endif
#elif defined(SUPPORT_ANGLE_MARK)
        "ANGLE MARK",                   //56    S:(角度标记)
#elif defined(SHOW_MP4_INIT_STR)    //wangwei-2004/4/28
        "INICIALIZANDO",//"INITIALIZING...",                 //56 
#elif defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "XGA",                  //56
#else
        "",                   //56    //not use
#endif
        "ZOOM",               //57    T:(糴)            S:(放宽)
#ifdef RECORD_KEY
        #ifdef NINTAUS_OSD_STR    //2004-2-11 11:35张宇P
           "PLEASE PRESS RECORD KEY TO PLAY IT.",
     #else
        "MEM KEY:JUMP TO THE SAVED POINT",//58
      #endif
#elif defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#elif defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "SXGA",                 //58
#elif defined(DOWNMIX_OFF_DISP_5CH_ON)
        "5.1CH ON",            //58 ZXB2005-4-27 16:21       
#else
        "",                   //58    //not use
#endif     
        OS_ICON_LANG,         //59
        "INTRO",              //60    T:(苯磞)            S:(扫描)
        "SURROUND",           //61    T:(吏露)            S:(环绕)
        "PBC",                //62
#ifdef RECORD_KEY
       #ifdef NINTAUS_OSD_STR    //2004-2-11 11:35张宇P
           "IT WILL BE AUTO PLAYED AFTER 6S.",
     #else
        "OTHER KEY:PLAY FROM BEGINNING",  //63
          #endif
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
       Ch_repf,       //63         //zhuyf 2004/8/10

#else//DIVIDE_AC3_DTS_SPDIF_OUTPUTS
        "",            //63    T:(抖冀)
#endif     
        "CANCELAR ALEAT""\xd3""RIO",        //64    T:(繦诀冀)    S:(随即播放取消)
        "BASS MODE",          //65    T:(家Α)
       #ifdef SUPPORT_TESTSPK
        "TESTSPK",                   //66
       #else
        "",                   //66
       #endif
        "REPETIR A-",          //67    T:(確A-)          S:(重复 A )
        #ifdef JIEKE_DVD
        "P-SCAN VGA",               //"PC-VGA",           //68
        #elif (defined(NINTAUS_OSD_STR)||defined(AD_TCL))//2004-3-22 13:21 lijd
        "VGA",
        #else
        "PC-VGA",               //"PC-VGA",           //68
        #endif
        "REPETIR A-B",         //69    T:(確A-B)         S:(重复播放A-B)
#ifdef BBK_DVD
        "CANCELAR REP AB",         //70    T:(確)        S:(A-B取消)
#else
        "CANCELAR REP A-B",         //70    T:(確)        S:(A-B取消)
#endif
        "CANCELAR PRG",         //71    T:(絪胆)            S:(编程取消)
        "",                   //72
#ifdef ONE_KEY_PASS
        "ONE KEY PLAY",      //73
#elif defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "576P/480P",             //73
#elif defined(EASTECH_NO_PARENTAL_CONTROL)
        "  NO PARENTAL",    //73
#else
        "",            //73    T:(璣粂)            S:(英文)
#endif
#ifdef PULIANG_DVD  //yaowh add 04-12-17
        "VCD1.0",           //74
#else
        OS_ICON_VCD,          //74
#endif

#if defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "720P",                  //75
#else
        "LIGHT MUSIC",                   //75    
#endif
        #if defined(SHOW_VCD_VER_INFO)||defined(SYBER_DVD)  //yaowh add for kenloon 04-08-03
    #ifdef PULIANG_DVD  //yaowh add 04-12-17
        "VCD2.0",           //76
    #else
        OS_ICON_VCD20,        //76    //xulf 2003-11-17
    #endif
        #else        
        "ELECTRON",                   //76   
        #endif
        "CVBS",//OS_ICON_MP3,          //77
        OS_ICON_CDDA,         //78
#ifdef NINTAUS_OSD_STR   
        "48KHZ",                   //79    //not use
        "96KHZ",                   //80    //not use
        "192KHZ",                   //81    //not use
#else
        "48K",                   //79    //not use
        "96K",                   //80    //not use
        "192K",                   //81    //not use
#endif
        "ZOOM CIMA",            //82    T:(礶簿)        S:(放大上)
        "ZOOM BAIXO",          //83    T:(礶簿)        S:(放大下)
        "ZOOM ESQ",          //84    T:(礶オ簿)        S:(放大左)
        "ZOOM DIR",         //85    T:(礶簿)        S:(放大右)
        "CH",                 //86    T:(彻竊)            S:(章节)
        "ECHO",               //87    T:(睼臫)            S:(混响)
        "TT",                 //88    T:(夹肈)            S:(标题)
        "BAND",               //89    T:(繵眯)
#ifdef OSD_BMP_REGION1
        "VOULUME",			  //90    T:(秖)            S:(音量)
#else        
        "VOULUME",                //90    T:(秖)            S:(音量)
#endif
        "SAMPLING",        //91    //not use
        "TECLA",                //92    T:(秸)            S:(音调)

        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-V""\xcd""DEO",            //93
        #endif

        "9QUADRO_1",           //94    T:(虫Ρ礶)      S:(单曲九画面)
        "AUTO ESQ",             //95    T:(笆钡佰オ)      S:(自动接唱左)
        "AUTO DIR",             //96    T:(笆钡佰)      S:(自动接唱右)
        "LOW",                //97    // LOW

            "REPRODUZIR SEQ",           //98    T:(抖冀)        S:(顺序播放)

        "REPRODUZIR MENU",          //99    T:(垫虫冀)        S:(菜单播放)
#ifdef DIV_GOTO_DISPLAY
        "DISC TIME",          //100
#else
        "LFE OUT",            //100
#endif

#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)
        "  COMMON ",       //101
        "PROFESSION",      //102
#elif defined(NINTAUS_OSD_STR)
    "UP-DOWN",
    "LEFT-RIGHT",           
#elif defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "TIMER SETUP",          //102              
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "CARD",             //102
#elif defined(ADD_DVI311_SETUP) && defined(DVD_SETUP_REENG)//Modifed by chenzhao on 2004-11-25 11:32   
        "SVGA",             //101
        "1080I",                 //102
 #elif defined(SLEEP_CONTROL_COUNTER)  //ADD XHR 
        "120 MIN",
        "90  MIN",
#else
        "PADR""\xc1""O",           //101
        "ENHANCE",            //102
#endif
 		#ifdef OP_CUST_UI
        "DIVX ID",                      //103
        #else
        "MEDIUM",             //103   // MEDIUM
        #endif
#ifdef MINTON_DVD
        "REPRODUZIR PROGR.",           //104   T:(絪导僵)          S:(编程播放)
#else
        "REPRODUZIR PROGR.",//LILY"REPRODUZIR PRG",           //104   T:(絪导僵)          S:(编程播放)
#endif
        "ALTO",               //105   // HIGH
        //"FAIXA DIN""\xc2""M.",      //106
        "MODO NOITE",         //106
        OS_ICON_DVD,          //107
        "IDIOMA OSD",       //108   T:(礶陪ボ粂ē)    S:(画面显示语言)
        OS_ICON_SUBT,         //109

        #ifdef SETUP_DONGLI459   //oujx for tonic
        "SISTEMA TV",          //111   T:(1qμ??÷¨?|?)      S:(μ?êó?ú??ê?)
        "TIPO TV",            //110   T:(辊礶ゑㄒ)    S:(屏幕画面比例)
        #elif defined(MINTON_DVD)
        "TIPO TV",            //110   T:(?¨?1?|ìe-?à?è??§¨°)    S:(?¨￠???-???à¨¨¨¤y)
        "MODO TV",        //111   T:(1q|ì?????§?|?)      S:(|ì?¨o¨??¨2??¨o?)
        #elif defined(SUPPORT_FUNCTION_MENU)
        "MODO LCD",           //110   
        "SISTEMA TV",          //111                 
        #else
        "FORMATO TELA",            //110   T:(?¨?1?|ìe-?à?è??§¨°)    S:(?¨￠???-???à¨¨¨¤y)
        #if defined(MUSTEK_PORTABLE_DVD)
		"ANGLE MARK", 			//111
		#else
        "SISTEMA TV",          //111   T:(1q|ì?????§?|?)      S:(|ì?¨o¨??¨2??¨o?)
        #endif
        #endif

        "SAIR SETUP",         //112   T:(癶砞竚垫虫)    S:(推出设置菜单)
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#elif defined(EASTECH_NEW_SETUP_MENU)||defined(MUSTEK_PORTABLE_DVD)||defined(PULIANG_DVD)||defined(DP3240_SETUP_MENU)  //yaowh modify 04-12-17
        "SA""\xcd""DA DIG.",          //113   T:(计絏块)        S:(数码输出)
#else
        "SA""\xcd""DA DIG.",//LILY"\xc1""UDIO OUT",          //113   T:(计絏块)        S:(数码输出)
#endif//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)

		#if defined(MUSTEK_PORTABLE_DVD)
		"V""\xcd""DEO OUTPUT", 		//114
              #elif defined(DP3240_SETUP_MENU)
		"V""\xcd""DEO OUT",              //114   T:(跌繵块)        S:(视频输出)
		#else
        "SAIDA V""\xcd""DEO",//"V""\xcd""DEO",              //114   T:(跌繵块)        S:(视频输出)
        #endif
        "SENHA",           //115   T:(盞絏)            S:(密码)

#ifdef GBM_RATING_SHOW_PARENTAL//GBM_FULL_FUNCTION      //gerry,2004-2-4 9:02
        "PARENTAL",//"RATING",             //116   T:()            S:(级别)
#else//GBM_RATING_SHOW_PARENTAL
	#if defined(MUSTEK_PORTABLE_DVD)
		"PARENTAL CTRL", //116
	#else
        "CENSURA",             //116   T:()            S:(级别)
    #endif
#endif//GBM_RATING_SHOW_PARENTAL

#ifdef EASTECH_NEW_SETUP_MENU
        "RAW",          //117   T:(SPDIF/方絏)      S:(SPDIF/源码)
#elif defined(DP3240_SETUP_MENU)  //add xrh 
         "RAW",  
#else
        "BITSTREAM",          //117   T:(SPDIF/方絏)      S:(SPDIF/源码)
#endif

        #ifdef SUPPORT_PALN //4-1-12 10:55
            "PAL-N",        //118
        #elif defined(PASSWORD_IN_CH)
        "ERROR",
        #else
            "",              //118   T:(AC3 6羘笵)
        #endif

#ifdef EASTECH_NEW_SETUP_MENU
        "PCM",          //119
#elif defined (DP3240_SETUP_MENU)  //add xrh 
         "PCM", 
#else
        "PCM",          //119
#endif

        #ifdef SUPPORT_PALM
            "PAL-M",                //120
        #elif defined(PASSWORD_IN_CH)
        "  OK",
        #elif defined(SLEEP_CONTROL_COUNTER)
	 "45  MIN",
        #else
            "",              //120   T:(AC3 2羘笵)       S:AC3 2声道(not use)
        #endif

        #ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
        #else//SHOW_YCbCr
        #ifdef AD_TCL//2004-3-22 13:22 lijd
            "YCbCr",
        #elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
        #elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
        #elif defined(EASTECH_DVI)
        "YCbCr", //121
        #elif defined(DP3240_SETUP_MENU)
	  "YUV",  //121	
        #else
        "ENTRELA""\xc7""ADO",                //121   T:(跌繵だ秖)        S:(视频分量)
        #endif//SHOW_INTERLACE
        #endif//SHOW_YCbCr
        
        "AUTO",               //122   T:(笆)            S:(自动)
        "DESLIGADO",//LILY"DESLIG.",                //123   T:(闽)              S:(关)
#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
        "TRACK TIME",//124
#elif defined(SLEEP_CONTROL_COUNTER)
	  "60  MIN",
#elif defined(SHOW_DRM_REGISTRATION_CODE_IN_SETUP)
      "DIVX[R] VOD", //124
#else
        "",           //124
#endif     
        "CAP""\xcd""TULO",            //125   T:(彻竊)            S:(章节)
        "T""\xcd""TULO",              //126   T:(夹肈)            S:(标题)
        OS_ICON_ANGLE,        //127
#ifdef NINTAUS_OSD_STR
        "YPbPr",
#elif defined(AD_TCL)//2004-3-22 13:23 lijd
        "YPbPr", 
#elif defined(HANYANG_SETUPMENU)||defined(SUPPORT_FUNCTION_MENU)||defined(EASTECH_NEW_SETUP_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
        #elif defined (ADD_P_SCAN_ONOFF)  //add xrh
         "P-SCAN", 
         #elif defined(DP3240_SETUP_MENU)
	    "P-SCAN", 	 
#else
        "PROGRESSIVE",       //128   T:(硋︽跌繵だ秖)
#endif    

        OS_16_9,              //129   T:(16:9 --)
        OS_4_3LB,             //130   T:(4:3LB --)
        OS_4_3PS,             //131

#ifdef HJ_SVA_NEW_OSDSTR
        "PAL-D",                //132
#else//HJ_SVA_NEW_OSDSTR
        "PAL",                //132
#endif//HJ_SVA_NEW_OSDSTR
        "NTSC",               //133
        "PAL-M",              //134

        #ifdef RATING_8
            "3 PG",               //135   T:(level 3)
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 PARA CRIAN""\xc7""AS",// CRIAN",                //137   T:(level 1)
            #else
            "2 G",                  //136   T:(level 2)
            //"1 G",                //137   T:(level 1)
            "1 G",
            #endif
            
        #else
            "P/ JOVENS",           //135   T:(辅导级)
            "P/ CRIAN""\xc7""AS",           //136   T:(保留)
            "VER TUDO",           //137   T:(礚)
        #endif


        #if defined(SHOW_5_1CH)
            "5.1CH",              //138   T:(5.1羘笵)
        #else
            "SETUP CANAIS",          //138   T:(6羘笵砞竚)
        #endif

        "SUBWOOFER",          //139   T:(禬)
        "SATURATION",         //140   SATURATION
        "LIGADO",//LILY"LIG.",                 //141   T:
        OS_DOBLY,             //142
        Ch_clock,             //143
        Ch_speaker,           //144
#if defined(OSD_BMP_PROG)
        "RESET",              //145   T:(睲埃)
#else
        "LIMPAR",              //145   T:(睲埃)
#endif
        "  T  C",               //146   //2004-2-23 03:56张宇P
        "--:--",              //147
#if	defined(MP3_DIRECT_SELECT)||defined(OSD_BMP_PROG)
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "EDITAR",               //149   T:(絪胯)
#ifdef RECORD_KEY 
        "RECORD RESUME",          //150
#elif defined(SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE)  //added by wangwei,2004-10-24 23:42,(English)
        "SUBTITLE LG 2",       //150       
#else
        "",//OS_DIR1,              //150
#endif
#ifdef QSI_SETUP_MENU//liweihua 2004-6-15
        " 1 MIN",                   //151
        " 5 MIN",                   //152
        "10 MIN",                   //153
        "30 MIN",                   //154
#elif defined(ADJUST_JPEG_SLIDE_TIME)  ////lyc 2005/2/18
        "15 SEG",                   //151
        "30 SEG",                   //152
        "45 SEG",                   //153
        "50 SEG",                   //154
#else
#ifdef BBK_DVD
        "5.1 CH",                  //151            
#elif defined(NINTAUS_OSD_STR)
    "<<<",
#else
        "",//OS_DIR2,              //151
#endif
        OS_DIR3,              //152
        OS_DIR4,              //153
        #ifdef SLEEP_CONTROL_COUNTER
	 "30  MIN",
	 #else
        "PAL-NC",//OS_DIR5,              //154
        #endif
#endif//#ifdef QSI_SETUP_MENU
        OS_LOCK,              //155   T:---- L
        OS_UNLOCK,            //156   T:---- U
#ifdef PULIANG_DVD      //yaowh add 04-12-17
        "CLOLOR",           //157
#else
        "HUE",                //157   HUE
#endif
#ifdef BBK_NEW_SETUP
        "PROLOGIC II",//"-:--:--",            //158  
#else
        "PROLOGIC",//"-:--:--",            //158     
#endif        
		#if defined(ORITRON_HK_DVD)//libing 2005-8-19 19:07
		"MODO DE LEITURA",						//159
		"REPETIR",							//160
		#else
        "MOVIE MODE",//"TRACK SEARCH",       //159    
        "MUSIC MODE",//"DISC SEARCH",        //160    
        #endif
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #elif defined(SUPPORT_PROLOGIC_II_ADVANCE_SETTING) //chenzhao 2005-5-12
        "PANORAMA",                //161
        #else
        "",//TT:CH",               //161    //not use
        #endif

        #if 1//def REMAIN_TIME//nono 2-7-12 20:06
            "T",                  //162
        #else
            "",           //162
        #endif

        OS_DIR0,              //163
        "CONTRAST",           //164   CONTRAST
        OS_DIR7,              //165
        OS_DIR8,              //166
        OS_DIR9,              //167
        "CANAL",            //168   T:(羘笵)            S:(声道)
        "BRIGHTNESS",         //169   BRIGHTNESS
        "F/W ID",             //170   T:(硁ン絪絏)        S:(软件编码)
#ifdef OP_CUST_UI  
		"CHECKSUM",  
#else		    
        "CHIP ID",            //171   T:(絪絏)        S:(芯片编码)
#endif       
        "REGI""\xc3""O",             //172   T:(跋絏)            S:(区码)
        "MEMORY",//"FUNCTION",           //173  //not use T:(滦弄滦佰)        S:(复读复唱)
        "DYNAMIC",//"MODE",               //174  //not use  T:(家Α)            S:(模式)

#if 1//libing 2005-7-29 14:49
		"MONO ESQ",               //175
        "MONO DIR",               //176
        "EST""\xc9""REO",               //177
#else
        "LIVELY",               //175
        "SHOWPLACE",            //176
        "MILD",                 //177
#endif
        "MIC1 VOL",//"COMPARE",            //178   //not use T:(癸ゑ)            S:(对比)
        "MIC2 VOL",//"COUNTER",            //179   //not use T:(滦Ω计)        S:(重复次数)

#ifdef FUSS_DVD_AVD276
        "PREV CHAPTER",      //180   S:上一章节
        "NEXT CHAPTER",      //181   S:下一章节
//#elif defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#elif defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "PR""\xd3""XIMA P""\xc1""GINA",                //180
        "P""\xc1""GINA ANTERIOR",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU)
        "BATTERY STATUS",           //180
        "SETUP",                    //181
#else
        "",//"LEVEL",              //180   T:魁家Α        S:录音模式
        "",//"HIGH",               //181   T:蔼珇借          S:高品质
#endif

#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#elif defined(SUPPORT_PROLOGIC_II_ADVANCE_SETTING) //chenzhao 2005-5-12
        "CENTER WIDTH",             //182
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",             //182   T:(禬丁)        S:(超长时间)
#endif

#ifdef NEWSTYLE_WINDOW
        "PLAYTITLE",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "SA""\xcd""DA DIG.",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "CHPTIME",//"MANUAL",             //185   T:(も笆)            S:(手动)
#elif defined(ADD_DVI311_SETUP)//Modifed by ChenZhao on 2004-8-19 17:24 WP
			"ANOLOG OUTPUT", //183
			"SA""\xcd""DA DIG.",  //184
			"480P",//OS_MANUAL, 		   //185   T:(も笆)
#elif defined(BRIGHTNESS_COLOR_KEY)||defined(VIEW_MODE_KEY)
		"COLOR",					//OS_COLOR 					//183
        "SA""\xcd""DA DIG.",				//OS_VIEW_MODE_NORMAL   	//184   
        "FULL MODE",				//OS_VIEW_MODE_FULL         //185   
#else
        "",//"SUPER",              //183   T:(禬蔼珇借)        S:(超高品质)
        "",//"OPERATING",          //184   T:(秸竊よΑ)        S:(调节方式)
        "",//"MANUAL",             //185   T:(も笆)            S:(手动)
#endif

        OS_DIR10,             //186
        OS_DIR11,             //187
        "CONCERTO",            //188   T:(贾芔)          S:(音乐厅)
        "IGREJA",             //189   T:(毙绑)            S:(教堂)
        "PASSIVO",            //190   T:(吏露)            S:(环绕)
        "AMPLO",               //191   T:(糴初)            S:(宽场)
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192
        "MPEG LOGO",            //193
#elif defined(ADD_DVI311_SETUP)//Modifed by ChenZhao on 2004-8-19 17:20 WP
    #ifdef HDCP_CUSTOM
		"HDCP",	            //192
	#else
		"VIDEO SELECT",	  //192
    #endif
		"VIDEO MODE",		  //193
#elif defined(PULIANG_DVD)//yaowh add 04-12-17
        "VERSION:WPQM_1A25101",     //192
        "REGION CODE",              //193
#elif defined(SLEEP_CONTROL_COUNTER)
   "15  MIN",
   "OFF",
#else
        "",//OS_AMPHITH,           //192   T:(蛾粿初)
        "",//OS_STADIUM,           //193   T:(蔨▅繻)
#endif
        "EQ",                 //194   T:(А颗)            S:(均衡)
        "STANDARD",           //195   T:(夹非)            S:(标准)
        "CL""\xc1""SSICO",            //196   T:(ㄥ)            S:(古典)
        "ROCK",               //197   T:(穘簎)            S:(摇滚)
        "JAZZ",               //198   T:(里)            S:(爵士)
        "POP",                //199   T:(瑈︽)            S:(流行)
        "USU""\xc1""RIO",               //200   T:(┦)            S:(个性)
        "ATRIBUTOS",             //201   T:(┦)            S:(个性)
        "SF",                 //202   T:(篊秈)            S:(慢进)
        "SB",                 //203   T:(篊癶)            S:(慢退)

        "C",                  //204   //show "C"
        "CENTRO",              //205   T:(い竚喘羘竟)      S:(中置扬声器)
        "TRASEIRO",               //206   T:(吏露喘羘竟)      S:(环绕扬声器)
        #if !defined(HIMAGE_RGB)&&!defined(NINTAUS_OSD_STR)
        "TV-RGB",             //207
        #else
        "RGB",                    //207
        #endif
        "4 PG-13",             //208   T:(辅导级)
        "ATRASO CENT.",       //209   T:(い竚┑筐)
        "ATRASO TRAS.",         //210   T:(吏露┑筐)
        "FRONTAL",              //211   T:(玡竚喘羘竟)
        "CONF V""\xcd""DEO",        //212   VIDEO SETUP
        "SHARPNESS",          //213   SHARPNESS
        "CONF SISTEMA",       //214   T:(╰参砞竚)        S:(系统设置)
        "CONF CANAL",      //215   T:(喘羘竟砞竚)      S:(扬声器设置)
        "CONF AUDIO",        //216   T:(繵砞竚)        S:(音频设置)
        "PADR""\xc3""O",            //217   T:()          S:(缺省值)
        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "SOURCE",
        #elif defined(SLEEP_CONTROL_COUNTER)  //ADD XRH 
	"SLEEP CONTROL",
        #else
            
        "GRP",                //218   //not use

        #endif
#ifdef AUTO_PLAY
        "AUTO PLAY",       //219   T:(辊玂臔)        S:(屏幕保护)
#elif defined(VCD_CDG_PLAY_CONTROL_BY_SETUPMENU)
        "   MNP   ",
#else
        "DESC. TELA",       //219   T:(辊玂臔)        S:(屏幕保护)
#endif
        #if defined(MUSTEK_PORTABLE_DVD)
	 "ANGLE MARK", 			//220
	 	#elif defined(ORITRON_PASSWORD)//libing 2005-4-29 9:53
	 	"VALOR PADR""\xc3""O",//220
        #else
        "TIPO 1",             //220   T:(家Α 1)          S:(模式1)
        #endif
        #if defined(MUSTEK_PORTABLE_DVD)
        "NIGHT MODE", 	  //227
        #elif defined(ORITRON_PASSWORD)//libing 2005-4-29 9:53
        "LIMPAR SENHA",             //221   T:(辅导级)
        #else
        "TIPO 2",             //221   T:(家Α 2)          S:(模式2)
        #endif
        #ifdef ORITRON_PASSWORD//libing 2005-4-29 9:53
        "LOADER LOCKED",       //222   T:(い竚┑筐)
        #else
        "TIPO 3",             //222   T:(家Α 3)          S:(模式3)
		#endif

        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   S:(5保留)
        #endif
        
        "6 R",                //224   S:(限制级)

        #ifdef NOT_SUPPROT_VCD
        "NOT SUPPORTED CD",           //225   S:(错误碟片)
        #else
        "ERRO DISCO",           //225   S:(错误碟片)
        #endif

        #if defined(MUSTEK_PORTABLE_DVD)
        "MAIN PAGE", 	  //226
        #else
        "CONF DIGITAL",      //226   T:(计絏砞竚)
        #endif	
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "CONF MIC",          //227   T:(杠旦砞竚)
        "VOL MIC",            //228   T:(杠旦秖)
        #endif
        "RECUPERANDO CD",      //229   T:(岿い)     ------------- not use
        "SMART UPGRADE",      //230   T:(醇ど)
        "UPGRADE TO V",      //231   T:(どΘ)
        "FAZENDO UPGRADE",          //232   T:(どい)
        "N""\xc3""O DESLIGUE",	//233   T:(づ闽诀)	//YAOWH MODIFY 04-10-26
        "REGI""\xc3""O 0",           //234   T:(0 跋)
        "REGI""\xc3""O 1",           //235   T:(1 跋)
        "REGI""\xc3""O 2",           //236   T:(2 跋)
        "REGI""\xc3""O 3",           //237   T:(3 跋)
        "REGI""\xc3""O 4",           //238   T:(4 跋)
        "CONF IDIOMA",     //239   T:(粂ē砞竚)
#ifdef  JIEKE_DVD
        "GIEC",               //240
#elif defined(BBK_DVD)
        "ZOOM",               //240
#elif defined(NINTAUS_OSD_STR)
    ">>>",
#elif defined(SUPPORT_FUNCTION_MENU)
        "DISPLAY",            //240 
#elif defined(GBM_PORTABLE_DVD)||defined(SUNPLUS_8202P_DEMOBOARD) 
        "LOW BATTERY",        //240         
#elif defined(SUPPORT_PROLOGIC_II_ADVANCE_SETTING) //chenzhao 2005-5-12
        "DIMENSION.",          //240         
#else        
        "",                   //240   //not use
#endif      
        "P""\xc1""G. PRINC.",          //241   T:()
#if !defined(BBK_DVD)
        "\xc1""UDIO",       //242   T:(繵粂ē)
#else
        "\xc1""UDIO",              //242   T:(繵粂ē) //axel 2004/1/27 03:58 eliminate "LANG"
#endif
#ifdef DISC_INFO_KEY  //fengjl  3-11-25 9:55
/*         "SUBP LANG",      //243   T:(辊粂ē)*/ //axel 2004/1/27 03:58 eliminate "LANG"
        "SUBP",      //243   T:(辊粂ē)
#elif defined(BBK_DVD)
        "LEGENDA",           //243   T:(辊粂ē)
#else
        "LEGENDA",      //243   T:(辊粂ē) //axel 2004/1/27 03:58 eliminate "LANG"
#endif
        "MENU DISCO",          //244   T:(垫虫粂ē)
#ifdef PULIANG_DVD  //yaowh add 04-12-17
        "DOWNMIX",      //245
        "RESET",        //246
#elif defined(DOWNMIX_DISP_20CH51CH)
		"2.0CH/5.1CH",//zxb		//245   T:(睼家Α)
        "RESTORE",            //246   T:(確)
#else
        "DOWNMIX",            //245   T:(睼家Α)
        "RESTAURAR",            //246   T:(確)
#endif
       
        "LT/RT",              //247
        "VSS",                //248   T:(店览吏露羘)      S:(虚拟环绕声)
        "MODO OP",            //249   T:(块家Α)        S:(输出模式)
        "SA""\xcd""DA LINHA",           //250   T:(絬隔块)        S:(线路输出)
        "RF REMOD",           //251   T:(RF 秸俱)         S:(RF调整)
#ifdef PULIANG_DVD  //yaowh add 04-12-17
        "MODE",         //252
#else
        "MODO VOCAL",          //252   T:(オ+)           S:(左+右)
#endif
        "VOCAL E+D",           //253   T:(睼羘笵)        S:(混合声道)
        "MODO SURR.",         //254   T:(吏露家Α)        S:(环绕模式)
#ifdef KSD_DVD
        "PRESS PLAY BUTTON TO CONTINUE",        //255   T:              S:请按播放键继续
#elif defined(DESAY_DVD)
        "PRESS PLAY BUTTON TO CONTINUE",
#elif defined(TONIC_DVD)
        "PRESS PLAY KEY TO CONTINUE",
#else
        "PRE STOP",           //255   T:                S:(准停止)
#endif
//============================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER

},
#endif  //USE_BRAZIL_OSD

#ifdef USE_SLOVENIAN_OSD              //felix 2005-9-29 15:40
//SLOVENIAN
{
        "",                                             //0
        "NI DISKA",           //"NO DISC",            //1     T:(礚盒)            S:(无碟)
        "TRK",        //"INVALID KEY",        //2     T:(眤岿 hand)   S:(您按错了 HAND)
        "POSNETEK",                                          //3     T:(Ρヘ)            S:(曲目)
        OS_ICON_SVCD,                                   //4
        "KITAJSKO",                 //"CHINESE",            //5 not use
        "ODPIRANJE",               //"OPEN",                                           //6     T:()            S:(出仓)
        "ZAPIRANJE",                //"CLOSE",              //7     T:(闽)            S:(关仓)
        "PREDVAJANJE",//"P""\x81""EHR"".",//"\xc1""V""\xc1",               //"PLAY",               //8     T:(冀)            S:(播放)
        "REGIJA 5",             //"REGION 5",           //9     T:(5 跋)            S:(5区)
        "PAVZA",                //"PAUSE",              //10    T:(既氨)            S:(暂停)
        "NAKLJU""\x06""NO",           //"RANDOM",             //11    T:(繦诀冀)        S:(随即播放)
        "POVZETEK",               //"RESUME",             //12    T:(確冀)        S:(恢复播放)
        "STOP",//"STOP",                                        //13    T:(氨ゎ)            S:(停止)
        "POSTOPOMA",                 //"STEP",               //14    T:(˙秈)            S:(单步)
        "IZBIRA",              //"SELECT",                                     //15    T:(匡拒)            S:(选择)


        "BRANJE",           //"READ",           //16    T:(弄盒)            S:(读碟)


        "REGIJA 6",             //"REGION 6",           //17    T:(6 跋)

        "ANALOGNO",           //"ANALOG",             //18    T:(家览)
        "NAPREJ",                 //"FORWARD",            //19    T:(е秈)
        "NAZAJ",                 //"BACKWARD",           //20    T:(е癶)
        "NASLEDNJE",              //"NEXT",               //21    T:(Ρ >>)

        "NASLEDNJA STRAN",                                     //22

        "PREDOGLED",                //"PREV",               //23    T:(Ρ <<)

        "PREJ""\x85""NJA STRAN",                                      //24

        "POVRATEK",            //"RETURN",             //25    T:(垫虫)
        Ch_repx,                                        //26
        Ch_rep1,                                        //27
        Ch_repd,                                        //28
        "VYP",                  //"OFF",                //29    T:(礚)              S:(无)
        "MENI",                                           //30    T:(匡虫)            S:(选单)
        "BELE""\xf7""KA",                                        //31    T:(だ计)            S:(分数)
        "OZNA""\x06""BA",//=="ZNA""\x06""KA",                                         //32    T:(癘拘)            S:(记忆)
        "LISTANJE",//"PROHL""\xcd""\xf7""EN""\xcd",               //"BROWSE",             //33    T:(聅凝)            S:(浏览)
        "PROG",                                          //34    T:(絪祘)            S:(编程)

        "PO""\x06""ASI",                               //35
        "SVOBODNO",           //"ALL LG SPK",         //36    T:(家Α1)
        "PONAVLJANJE",             //"REP",                //37    T:(確)
        "PON.DIREKTNO",         //"REP DIR",            //38    T:(ヘ魁確)
        "PONAVLJANJE 1",           //"REP 1",              //39    T:(虫Ρ確)
        "PONAVLJANJE VSE",      //"REP ALL",            //40    T:(盒確)
        "PREKLIC PON.",    //"REP CANCEL",         //41    T:(確)
        "POSNETEK REM",                                   //42    T:(家Α2)

        "DISK REM",                                            //43

        "7NC17",                                      //44    T:(虫Ρ冀)
        "POJDI NA",                    //"GOTO",               //45    T:(穓)
        "IZKLOP ZVOKA",         //"MUTE",               //46    T:(繰)
        "LMONO L",                                        //47    T:(オ羘笵)
        "MONO D",                                       //48    T:(羘笵)
        "STEREO",                                       //49    T:(ミ砰羘)
        "DVORANA",          //"SCORE MODE",         //50
        "V" "\xf7""IVO",                                 //51    T:
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DOLBY DIGITAL",                     //52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "DISK",               //52
#else
        "GLEDALI""\x85""\x06""E",                //"TEST TONE",          //52
#endif
        "SOLO",        //"MIXED SPK",          //53    T:(家Α3)
        OS_ICON_CDROM,                                  //54
        "\x06""AS",            //"TIME",               //55    not use
        "9 POSNETKOV",             //"TV VIDEO",           //56    //nono 3-2-26 18:36
        "POVE""\x06""AVA",                                         //57    T:(糴)            S:(放宽)
#if defined(SUPPORT_CC_ONOFF)
        "CLOSE CAPTION",                   //58    S:(CC字幕)
#else
        "PREKLIC",                    //58    //not use
#endif
        OS_ICON_LANG,                                   //59
        "VNOS",                                        //60    T:(苯磞)            S:(扫描)
        "SURROUND",//"SURROUND",                                    //61    T:(吏露)            S:(环绕)
        "PBC",                                          //62
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "DTS DIGITAL",                     //63
#elif defined(ICON_REPEAT_FOLDER)
      Ch_repf,       //63         //zhuyf 2004/8/10

#else
        "PBC IZKLOP",            //"PBC OFF",            //63    not use
#endif
        "PREKLIC NAKLJU""\x06""NO",   //"RAND CANCEL",        //64    T:(繦诀冀)    S:(随即播放取消)
        "PREKLIC POJDI NA",                //"BASS MODE",          //65    T:(家Α)

        "VKLOP",                                    //66

        "PONAVLJANJE A",          //"REPEAT A-",          //67    T:(確A-)          S:(重复 A   )
        "PC-VGA",                                               //68
        "PONAVLJANJE OD A-B",         //"REPEAT A-B",         //69    T:(確A-B)       S:(重复播放A-B)
        "AB PREKLIC",          //"A-B CANCEL",         //70    T:(確)        S:(A-B取消)
        "PREKLIC PROGRAM",      //"PRG CANCEL",         //71    T:(絪胆)            S:(编程取消)
        "",                                             //72
        #ifdef MACROVISION_SHOW_FW_VERSION
        MCRV_STR,//
        #else
        "ANGLE""\x85""KO",                     //"ENGLISH",            //73   not use
        #endif
        OS_ICON_VCD,                                    //74
        "VCD 1.1",                                       //75    //NTSC-J
        "VCD 2.0",                                             //76    //not use
        "CVBS",                     //OS_ICON_MP3,          //77 not use
        OS_ICON_CDDA,                                   //78
        "PREKLIC LISTANJA",                   //79    //not use
        "PREKLIC VNOSA",                   //80    //not use
        "PREKLIC 9 SLIK",                   //81    //not use
        "ZOOM GOR",            //"ZOOM UP",            //82    T:(礶簿)        S:(放大上)
        "ZOOM DOL",           //"ZOOM DOWN",          //83    T:(礶簿)        S:(放大下)
        "ZOOM LEVO",        //"ZOOM LEFT",          //84    T:(礶オ簿)        S:(放大左)
        "ZOOM DESNO",       //"ZOOM RIGHT",         //85    T:(礶簿)        S:(放大右)
        "KANAL",                                           //86    T:(彻竊)            S:(章节)
        "ODMEV",//"ECHO",                                        //87    T:(睼臫)            S:(混响)
        "TT",                                           //88    T:(夹肈)            S:(标题)
        "PODRO""\x06""JE",                                             //89
        "GLASNOST",//"VOL",                                            //90    T:(秖)            S:(音量)
        "OSVE""\xf7""ITEV",  //91    //not use
        "KLJU""\x06",                   //"KEY",                //92    T:(秸)            S:(音调)
        
        #ifdef P_SCAN_ONLY_CHG_INT_MODE
        "CVBS",            //93
        #elif defined(GBM_ONLY_CVBS_S_VIDEO_SHOW_COMPOSITE)     //gerry,2004/2/12 04:20と
        "COMPOSITE",            //93
        #else
        "S-VIDEO",            //93
        #endif
        
        "9SLIK-1",                                     //94    T:(虫Ρ礶)      S:(单曲九画面)
        "AVTO L",                                       //95    T:(笆钡佰オ)      S:(自动接唱左)
        "AVTO D",                                       //96    T:(笆钡佰)      S:(自动接唱右)
        "BRANJE",                                              //97

        "PREDVAJANJE SEQ",//"SE.P""\x81""EHR",   //"SEQ PLAY",       //98    T:(抖冀)        S:(顺序播放)

        "MENI PREDVAJANJE",       //"MENU PLAY",          //99    T:(垫虫冀)        S:(菜单播放)
        "P-SCAN",              //"LFE OUT",            //100
#if defined(SHOW_STANDBY_TIMER)
    OS_VFD_TIME_NUM,        //101
    "\x06""AS",          //102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
        "USB",              //101
        "KARTICA",             //102
#else        
        "STANDARD",                                     //101
        "ENHANCE",                                      //102
#endif        
        "POSTOPOMA",                                               //103
        "PROG PREDVAJANJE",     //"PRG PLAY",           //104   T:(絪导僵)          S:(编程播放)
        "\x06""AKANJE",                                             //105
        "DINAMI""\x06""NO",        //"DYNAMIC RANGE",      //106
        OS_ICON_DVD,                                    //107

        "OSD JEZIK",              //"OSD LANGUAGE",       //108   T:(礶陪ボ粂ē)    S:(画面显示语言)

        OS_ICON_SUBT,                                   //109

        "TV TIP/ DISP",                                     //110   T:(辊礶ゑㄒ)    S:(屏幕画面比例)
        "TV TIP/SISTEM",          //"TV SYSTEM",        //111   T:(筿跌诀Α)      S:(电视机制式)

        "NAST.IZHODA",     //"EXIT SETUP",         //112   T:(癶砞竚垫虫)    S:(推出设置菜单)
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "PCM",          //113   T:(计絏块)        S:(数码输出)
#else//#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
        "AVDIO IZHOD",          //"AUDIO OUT",          //113   T:(计絏块)        S:(数码输出)
#endif

        "VIDEO",                                          //114   T:(跌繵块)        S:(视频输出)

        "GESLO",            //"PASSWORD",           //115   T:(盞絏)            S:(密码)

        "OMEZEN""\xcd",                 //"RATING",             //116   T:()            S:(级别)

        "SPDIF/RAW",                                    //117   T:(SPDIF/方絏)      S:(SPDIF/源码)

#if defined(SUPPORT_PALN)//4-1-12 10:55
            "PAL-N",        //118
#else
        "AC3 6KANALNIR",                                   //118
#endif

        "SPDIF/PCM+SIM",                                    //119

//        "AMP SUBWOOFER",                              //120
#ifdef SUPPORT_PALM
        "PAL-M",                //120
#else
        "AC3 2 KANALNI",           //120
#endif

#ifdef SHOW_YCbCr
        "YPbPr/YCbCr",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(HANYANG_SETUPMENU)   //caoh 2004-6-16 15:22
         "INTERLACE",                //121   T:(跌繵だ秖)        S:(视频分量)
#elif defined(SUPPORT_FUNCTION_MENU)
        "YUV",  //121
#elif defined(EASTECH_DVI)
        YCbCr, //121
#else
        "INTERLACE-YUV",                                        //121   T:(跌繵だ秖)        S:(视频分量)
#endif//SHOW_YCbCr

        "AVTO",         //"AUTO",               //122   T:(笆)            S:(自动)

        "IZKLOP",                  //"OFF",                //123   T:(闽)              S:(关)
        "TM/CH/TL",                     //"TM/CH/TL",           //124
        "POGLAVJE",           //"CHAPTER",            //125   T:(彻竊)            S:(章节)
        "NASLOV",                //"TITLE",              //126   T:(夹肈)            S:(标题)
        OS_ICON_ANGLE,                                  //127
      #if defined(HANYANG_SETUPMENU)||defined( SUPPORT_FUNCTION_MENU)  //caoh 2004-6-16 15:33
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #elif defined(EASTECH_DVI)
        "YPbPr", //128
      #else
        "P-SCAN",       //128   T:(硋︽跌繵だ秖)
      #endif

        OS_16_9,                                        //129   T:(16:9 --)

        OS_4_3LB,                                       //130   T:(4:3LB --)

        OS_4_3PS,                                       //131

        "PAL",                                          //132
        "NTSC",                                         //133
        "PAL60",                                        //134

        #ifdef RATING_8
            "3 PG",                                     //135   T:(level 3)
            #ifdef FIX_RATING_8_DISPLAY
            "2 G",                  //136   T:(level 2)
            "1 KID SAFE",                //137   T:(level 1)
            #else
            "2",                                        //136   T:(level 2)
            "1 G",                                      //137   T:(level 1)
            #endif
        #else
            "NE ODRASLI",  //"NO ADULT",           //135   T:(辅导级)
            "VARNOST OTROK", //"KID SAFE",           //136   T:(保留)
            "PREGLED VSEGA",     //"VIEW ALL",           //137   T:(礚)
        #endif


        "NAST6 KAN",                                //138   T:(6羘笵砞竚)

        "NIZKOTONEC",                                    //139   T:(禬)
        "ZASI""\x06""ENJE",         //140   SATURATION
        "VKLOP",                  //"ON",                 //141   T:
        OS_DOBLY,                                       //142
        Ch_clock,                                       //143
        Ch_speaker,                                     //144
        "IZBRIS",           //"CLEAR",              //145   T:(睲埃)
        //"  T  C",               //146
        //"--:--",              //147
        "  T  C",                                           //146
        "--:--",                                    //147
#ifdef  MP3_DIRECT_SELECT
        " ----",               //148
#else        
        "[--]",               //148
#endif        
        "UREJANJE",         //"EDIT",               //149   T:(絪胯)
        
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 23:42,(Czech).
        "TITULKY 2",    //150
#else
        "",//OS_DIR1,                                       //150
#endif   
        
        "",//OS_DIR2,                                       //151
        OS_DIR3,                                        //152
        OS_DIR4,                                        //153
        "PAL-NC",//OS_DIR5,                                         //154
        OS_LOCK,                                        //155   T:---- L
        OS_UNLOCK,                                      //156   T:---- U
        "VSE",//"",                   //157   //not use
        "PROLOGIC",//"-:--:--",            //158    //not use
        "ISKANJE POSNETKA",//"TRACK SEARCH",       //159   //not use
        "ISKANJE DISKA",//"DISC SEARCH",        //160   //not use
        #if defined(SUPPORT_IR_I2P_KEY)
        "INTERLACE",                //161   T:(跌繵だ秖)        S:(视频分量)
        #else
        "",//TT:CH",               //161    //not use
        #endif

        "ZAZNAMEK",                  //162 //use when define REMAIN_TIME

        OS_DIR0,                                        //163
        "KONTRAST",           //164   CONTRAST
        OS_DIR7,                                        //165
        OS_DIR8,                                        //166
        OS_DIR9,                                        //167
        "KANAL",             //"CHANNEL",            //168   T:(羘笵)            S:(声道)
        "SVETLOBA",         //169   BRIGHTNESS
        "F/W ID",//"F/W ID",                                        //170   T:(硁ン絪絏)        S:(软件编码)
        "\x06""IP ID",//"CHIP ID",                                      //171   T:(絪絏)        S:(芯片编码)
        "REGIJA",               //"REGION",             //172   T:(跋絏)            S:(区码)
        "FUNKCIJA",                       //"FUNCTION",           //173  //not use T:(滦弄滦佰)        S:(复读复唱)
        "NA""\x06""IN",                      //"MODE",               //174  //not use  T:(家Α)            S:(模式)

        "SNEMANJE",               //175
        "\x85""TUDIJA",            //176
        "SLEDENJE",                 //177

        "PRIMERJAVA",//"COMPARE",            //178   //not use T:(癸ゑ)            S:(对比)
        "\x85""TEVEC",//"COUNTER",            //179   //not use T:(滦Ω计)        S:(重复次数)

//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)
       #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP             //gerry,2004-2-2 14:16
        "ADVANCED",//"NEXT PAGE",               //180
        "ADVANCED SETUP",               //181
       #else//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP
        "NEXT PAGE",                //180
        "PREV PAGE",                //181
       #endif//#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP     
#elif defined(SUPPORT_FUNCTION_MENU) 
	"BATTERY STATUS",	    //180
	"SETUP",    		    //181 
#else
        "NIVO",     //"PREV CHAPTER",       //180   S:(上一章节)
        "VISOKO",     //"NEXT CHAPTER",       //181   S:(下一章节)
#endif
#ifdef SUPPORT_IR_I2P_KEY
        "PROGRESSIVE",       //182   T:(硋︽跌繵だ秖)
#else//SUPPORT_IR_I2P_KEY
        "",//"NORMAL",             //182   not use
#endif
        "",//"SUPER",              //183   not use
        "",//"OPERATING",          //184   not use
        "RO""\x06""NO",//"MANUAL",             //185   not use
        OS_DIR10,             //186
        OS_DIR11,             //187
        "KONCERT",//"CONCERT",                                      //188   T:(贾芔)          S:(音乐厅)
        "CERKEV",                   //"CHURCH",             //189   T:(毙绑)            S:(教堂)
        "PASIVNO",             //"PASSIVE",            //190   T:(吏露)            S:(环绕)
        "\x85""IROKO",//"\x85""IROKO""\xda""H",                    //"WIDE",               //191   T:(糴初)            S:(宽场)
//        "",                       //"AMPHITH",            //192   not use
//        "",                       //"STADIUM",            //193   not use
#ifdef USER_MPEG_LOGO
        "SELECT LOGO",          //192    3-12-2 0:37
        "MPEG LOGO",            //193    3-12-2 0:38
#else
        "AMFITEATER",//OS_AMPHITH,           //192   T:(蛾粿初)   3-12-2 0:38
        "STADION",//OS_STADIUM,           //193   T:(蔨▅繻)   3-12-2 0:38
#endif
        "EQ",                                           //194   T:(А颗)            S:(均衡)
        "STANDARDNO",         //"STANDARD",           //195   T:(夹非)            S:(标准)
        "KLASIKA",              //"CLASSIC",            //196   T:(ㄥ)            S:(古典)
        "ROCK",                                         //197   T:(穘簎)            S:(摇滚)
        "JAZZ",                                         //198   T:(里)            S:(爵士)
        "POP",                                          //199   T:(瑈︽)            S:(流行)
        "UPORABNIK",          //"USER",               //200   T:(┦)            S:(个性)
        "PRIPIS",                                        //201   T:(┦)            S:(个性)
        "SF",                   //"SF",                 //202   T:(篊秈)            S:(慢进)
        "SB",                   //"SB",                 //203   T:(篊癶)            S:(慢退)

        "EHO PADEC",                                            //204   //show "C"

       "CENTER",               //"CENTER",             //205   T:(い竚喘羘竟)      S:(中置扬声器)
       "ZADAJ",                //"REAR",               //206   T:(吏露喘羘竟)      S:(环绕扬声器)

        "TV-RGB",             //207

        "4PG13",                                       //208   T:(辅导级)
        "ZAMIK CENTRA",        //"CENTER DELAY",       //209   T:(い竚┑筐)
        "ZAMIK ZADZVO""\x06",//"ZADN""\xcd"" ZPO",      //"REAR DELAY",         //210   T:(吏露┑筐)
        "PREDNJI",                   //"FRONT",              //211   T:(玡竚喘羘竟)
        "VIDEO NASTAVITEV",        //212   VIDEO SETUP
        "12MS",          //213   SHARPNESS

        "NASTAVITEV SISTEMA",//"NASTAVEN""\xcd",     //"SYSTEM SETUP",       //214   T:(╰参砞竚)        S:(系统设置)

        "NASTAVITEV ZVO""\x06""NIKOV",//"NAST.REPR",                               //215   T:(喘羘竟砞竚)      S:(扬声器设置)
        "NASTAVITEV AVDIO",//"NAST.AUDIO",                                 //216   T:(繵砞竚)        S:(音频设置)

        "NAPAKA",//"P""\r\x1a""V NAST.",       //"DEFAULT",            //217   T:()          S:(缺省值)

        #ifdef SELECT_MEDIA_IN_SETUPMENU
        "VIR",
        #else
        "IZHOD KANALA",                                          //218   //not use
        #endif

         #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU
        "   MNP   ",
        #else
        "OHR.ZASLONA",        //"SCREEN SAVER",       //219   T:(辊玂臔)        S:(屏幕保护)
        #endif

        "TIP1",             //220   T:(家Α 1)          S:(模式1)

        #if defined(HIMAGE_DMA5800) //gerry for huajia 3-3-11 11:14
            "TREBLE VOL",           //221
            "MAIN VOL",           //222
        #else
            "TIP2",             //221   T:(家Α 2)          S:(模式2)
            "TIP3",             //222   T:(家Α 3)          S:(模式3)
        #endif

        #ifdef FIX_RATING_8_DISPLAY
        "5 PG-R",                  //223   S:(5保留)
        #else
        "5",                  //223   S:(5保留)
        #endif
        
        "6R",                //224   S:(限制级)

        #ifdef NOT_SUPPROT_VCD
        "NOT SUPPORTED CD",           //225   S:(错误碟片)
        #else
        "NAPAKA DISKA",           //225   S:(错误碟片)
        #endif

        "DIGITALNA NASTAVITEV",//"DOLBY DIGI",        //"DIGITAL SETUP",      //226   T:(计絏砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
        "F/W VERSION",		  //227
        "",					//228
        #else
        "NASTAVITEV MIKROFONA",                                    //227   T:(杠旦砞竚)
        "NAST.GLAS",                                     //228   T:(杠旦秖)
		#endif
        "OBNAVLJANJE DISKA",     //"CD RECOVERING",      //229   T:(岿い)
        "ENOST.NADG.",   //"SMART UPGRADE",                              //230   T:(醇ど)
        "NADGRADNJA V",   //"UPGRADE TO V ",      //231   T:(どΘ)
        "NADGRADNJA",          //232   T:(どい)
        "BREZ IZKLOPA ", //"NOT POWER OFF",      //233   T:(づ闽诀)

        "REGIJA 0",             //"REGION 0",           //234   T:(0 跋)
        "REGIJA 1",             //"REGION 1",           //235   T:(1 跋)
        "REGIJA 2",             //"REGION 2",           //236   T:(2 跋)
        "REGIJA 3",             //"REGION 3",           //237   T:(3 跋)
        "REGIJA 4",             //"REGION 4",           //238   T:(4 跋)

        "NASTAVITEV JEZIKA",            //"LANGUAGE SETUP",     //239   T:(粂ē砞竚)
        #ifdef SUPPORT_FUNCTION_MENU
	"DISPLAY",            //240
	#else
        "NASTAVITEV STD",                                             //240   //not use
        #endif
        "GLAVNA STRAN",           //"MAIN PAGE",          //241   T:()

        "JEZIK ZVOKA",         //"AUDIO LANG",         //242   T:(繵粂ē)
        "JEZIK PODNAP",      //"SUBTITLE LANG",      //243   T:(辊粂ē)
        "MENI",           //"MENU LANG",          //244   T:(垫虫粂ē)

        "DOWNMIX",      //"DOWNMIX",                                        //245   T:(睼家Α)

        "OSVE""\xf7""ITEV",          //"RESTORE",            //246   T:(確)

        "LEVO/DESNO",                    //"LT/RT",              //247

        "VSS",                  //"VSS",                //248   T:(店览吏露羘)      S:(虚拟环绕声)
        "OP NA""\x06""IN",      //"OP MODE",            //249   T:(块家Α)        S:(输出模式)
        "LINIJA IZHOD",              //"LINE OUT",           //250   T:(絬隔块)        S:(线路输出)
        "RF",         //"RF REMOD",           //251   T:(RF 秸俱)         S:(RF调整)
        "DVOJNI MONO",//"DUAL MONO",                                      //252   T:(オ+)           S:(左+右)
        "MIX MONO",                                     //253   T:(睼羘笵)        S:(混合声道)
        "SURROUND",            //"SURND MODE",         //254   T:(吏露家Α)        S:(环绕模式)
        "PRE STOP",                                     //    T:                  S:(准停止)
//=====================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

        "LEFT-RIGHT",   //256        
        "UP-DOWN",      //257
#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
        " ENTER SELECT TO RETURN MAIN SETUP",   //258
#else
       "REP TITLE",     //258
#endif
    
#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
        " PASSWORD ERROR.PLEASE INPUT AGAIN",  //259
        " PLEASE INPUT OLD PASSWORD        ",  //260
#else
       "REP CHAPTER",    //259
       "REP GROUP",     //260
#endif
        " PLEASE INPUT NEW PASSWORD        ",  //261
        "OLD PASSWD",               //262
        "NEW PASSWD",               //263
#endif  //EXCEED_MAX_NUMBER

},
#endif//   SLOVENIAN_OSD

};

#endif//#define __OSD_STR_H



