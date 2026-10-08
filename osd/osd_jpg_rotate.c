/*
 *************************************************************************
 * File Name:   osd_jpg_rotate.c
 * Created:     2004/6/30 Maoyong
 * Description: for easy do customizied jpeg rotation string display, no need
                to compile JPEG/FS releated files
 * Maintain:
 ************************************************************************/
#include "cmd.h"
#include "set.h"   //terry,2005/1/24 04:29PM
#include "user_init.h"

#ifdef JPG_OLD_PARSER_FLOW
    #ifdef JPG_EFFECT
    #include "jpegeffect.h"
    #endif
#else
    #include "pic_effect.h"
#endif    

#ifdef USE_JAPANESE_IN_JPEG_MODE            //hq, 2004-3-11 16:41
#include "cfont.h"
#include "setup_page.h"
#include "setup_def.h"
extern const UINT8 setup_item[MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE][MAX_PAGE_ITEM][MAX_ITEM_SEL];
#endif//USE_JAPANESE_IN_JPEG_MODE

#ifdef  USE_CHINESE_IN_JPEG_ROTATE //zhaoyanhua add 2004-2-9 14:43
extern const char *const _OsdMessegeFont1[N_OSD_LANGS][MAX_OSD_STR_ID];
#endif//#ifdef  USE_CHINESE_IN_JPEG_ROTATE


//*****linrc move the following here from jpegeffect.c 2005-1-20 16:55****//

#ifdef USE_CHINESE_IN_JPEG_MODE            //fengjl add 4-1-5 20:43
const char * const jpeg_effect_str_chinese[EFFECT_MODE_NUM] = {
     OS_WIPE_TOP,                     //0  //由上至下进图    
     OS_WIPE_BOTTOM,                  //1  //由下至上进图    
     OS_WIPE_LEFT,                    //2  //由左至右进图  
     OS_WIPE_RIGHT,                   //3  //由右至左进图  
     OS_DIGONAL_WIPE_LEFT_TOP,        //4  //由左上至右下进图
     OS_DIGONAL_WIPE_RIGHT_TOP,       //5  //由右上至左下进图
     OS_DIGONAL_WIPE_LEFT_BOTTOM,     //6  //由左下至右上进图
     OS_DIGONAL_WIPE_RIGHT_BOTTOM,    //7  //由右上至左下进图
     OS_EXTEND_FROM_CENTER_H,         //8  //由中间向上下展开图
     OS_EXTEND_FROM_CENTER_V,         //9  //由中间向左右展开图
     OS_COMPRESS_TO_CENTER_H,         //10  //由上下向中间展开图
     OS_COMPRESS_TO_CENTER_V,         //11  //由左右向中间展开图
     OS_WINDOW_H,                     //12  //由上向下分层展开图
     OS_WINDOW_V,                     //13  //由左向右分层展开图
     OS_WIPE_FROM_EDGE_TO_CENTER,     //14  //由四周向中间分层展开图
     OS_RANDOM_WAY,                   //15  //随机进图
     OS_NONE_WAY,                     //16  //正常进图
//     OS_WIPE_TOP,                     //17  //由上至下进图
};
#endif//USE_CHINESE_IN_JPEG_MODE

#ifdef USE_JAPANESE_IN_JPEG_MODE      //hq, 2004-3-11 14:32
const char * const jpeg_effect_str_japanese[EFFECT_MODE_NUM] = {
     JOS_WIPE_TOP,                     //0  //由上至下进图    
     JOS_WIPE_BOTTOM,                  //1  //由下至上进图    
     JOS_WIPE_LEFT,                    //2  //由左至右进图  
     JOS_WIPE_RIGHT,                   //3  //由右至左进图  
     JOS_DIGONAL_WIPE_LEFT_TOP,        //4  //由左上至右下进图
     JOS_DIGONAL_WIPE_RIGHT_TOP,       //5  //由右上至左下进图
     JOS_DIGONAL_WIPE_LEFT_BOTTOM,     //6  //由左下至右上进图
     JOS_DIGONAL_WIPE_RIGHT_BOTTOM,    //7  //由右上至左下进图
     JOS_EXTEND_FROM_CENTER_H,         //8  //由中间向上下展开图
     JOS_EXTEND_FROM_CENTER_V,         //9  //由中间向左右展开图
     JOS_COMPRESS_TO_CENTER_H,         //10  //由上下向中间展开图
     JOS_COMPRESS_TO_CENTER_V,         //11  //由左右向中间展开图
     JOS_WINDOW_H,                     //12  //由上向下分层展开图
     JOS_WINDOW_V,                     //13  //由左向右分层展开图
     JOS_WIPE_FROM_EDGE_TO_CENTER,     //14  //由四周向中间分层展开图
     JOS_RANDOM_WAY,                   //15  //随机进图
     JOS_NONE_WAY,                     //16  //正常进图
};
//for ROTATE etc. in Slide Shoe. I only added Japanese Notes for JPEG_EXT2FULL. 
//if not define JPEG_EXT2FULL, Please add Japanese Notes by yourself when needed. 
//add these strings into 'osd_string.h' is better. hq, 2004-3-22 17:20 
//JOS_UP_DOWN,JOS_LEFT_RIGHT,JOS_ROTATE_LEFT,JOS_ROTATE_RIGHT,
#endif//USE_JAPANESE_IN_JPEG_MODE

#ifndef SDRAM_16Mb_Mode       //only use 16Mb*1 SDRAM

const char * const jpeg_effect_str[EFFECT_MODE_NUM] = {
    "WIPE TOP",                     // 0
    "WIPE BOTTOM",                  // 1
    "WIPE LEFT",                    // 2
    "WIPE RIGHT",                   // 3
    "DIGONAL WIPE LEFT TOP",        // 4
    "DIGONAL WIPE RIGHT TOP",       // 5
    "DIGONAL WIPE LEFT BOTTOM",     // 6
    "DIGONAL WIPE RIGHT BOTTOM",    // 7
    "EXTEND FROM CENTER H",         // 8
    "EXTEND FROM CENTER V",         // 9
    "COMPRESS TO CENTER H",         // 10
    "COMPRESS TO CENTER V",         // 11
    "WINDOW H",                     // 12
    "WINDOW V",                     // 13
    "WIPE FROM EDGE TO CENTER",     // 14
    "RANDOM",                       // 15
    "NONE",                         // 16
#ifdef JPEG_EFFECT_OFFITEM
    "EFFECT CLOSED"                      // 17
#endif 
};

#else

const char * const jpeg_effect_str[EFFECT_MODE_NUM] = {
    "WIPE TOP",                // 0
    "WIPE BOTTOM",             // 1
    "WIPE L",                  // 2
    "WIPE R",                  // 3
    "DIGONAL L TOP",           // 4
    "DIGONAL R TOP",           // 5
    "DIGONAL L BOTTOM",        // 6
    "DIGONAL R BOTTOM",        // 7
    "EXTEND CENTER H",         // 8
    "EXTEND CENTER V",         // 9
    "COMPRESS CENTER H",       // 10
    "COMPRESS CENTER V",       // 11
    "WINDOW H",                // 12
    "WINDOW V",                // 13
    "EDGE TO CENTER",          // 14
    "RANDOM",                  // 15
    "NONE",                    // 16
#ifdef JPEG_EFFECT_OFFITEM
    "EFFECT CLOSED"                      // 17
#endif 
};
#endif

//*******************end linrc move here ***************************//

//======================rotation display osd str=====================
#ifdef YADAI_DVD
#define ROTATION_LEFT_STR     NSZ//2004-3-22 19:14 LIJD
#elif defined(ENGLISH_OSD_IN_JPEG_ROTATE)
#define ROTATION_LEFT_STR     "ROTATE ANTI-CLOCKWISE"
#else
#define ROTATION_LEFT_STR     "<<<"
#endif

#ifdef YADAI_DVD
#define ROTATION_RIGHT_STR    SSZ//2004-3-22 19:14 LIJD
#elif defined(ENGLISH_OSD_IN_JPEG_ROTATE)
#define ROTATION_RIGHT_STR     "ROTATE CLOCKWISE"
#else
#define ROTATION_RIGHT_STR    ">>>"
#endif

#ifdef YADAI_DVD
#define ROTATION_UP_DOWN_STR  ShangXia//2004-3-22 19:15 LIJD
#else
#define ROTATION_UP_DOWN_STR     "UP-DOWN"
#endif

#ifdef YADAI_DVD
#define ROTATION_L_R_STR      ZuoYou//2004-3-22 19:15 LIJD
#else
#define ROTATION_L_R_STR      "LEFT-RIGHT"
#endif

//=============================rotation display  str functino =====================
#ifdef USE_JAPANESE_IN_JPEG_MODE    //I think it's so special, so tell from this case
void DispJpgRotateStr(void)
{
    UINT8 *str = "";
    const UINT8 *osdRotStrJan[5] = {JOS_ROTATE_LEFT, JOS_ROTATE_RIGHT, JOS_LEFT_RIGHT, 0, JOS_UP_DOWN};
    const UINT8 *osdRotStrEng[5] =
    {
    #ifdef	ENGLISH_OSD_IN_JPEG_ROTATE//wuxiaofeng 02-27 for minton DVD
    "ROTATE ANTI-CLOCKWISE", "ROTATE CLOCKWISE", "LEFT-RIGHT", "", "UP-DOWN",
	#else
    "<<<", ">>>", "LEFT-RIGHT", "", "UP-DOWN",
	#endif
    };

  	#ifdef OSD_L_JP_BEFORE_EN//hq, 2004-3-22 9:49
	BYTE my_osd_font_mode = 0;
   	if(osd_font_mode == 0)
    	my_osd_font_mode = 1;
    else
    	my_osd_font_mode = 0;
	if (setup_item[LANGPAGE][LANGITEM][my_osd_font_mode+2]==LCD_JA)
	#else//OSD_L_JP_BEFORE_EN
    if (setup_item[LANGPAGE][LANGITEM][osd_font_mode+2]==LCD_JA)
	#endif//OSD_L_JP_BEFORE_EN
    {
		str = osdRotStrJan[sys_cmd - CMDS_GAME_L]; //Jan
    }else{
        str = osdRotStrEng[sys_cmd - CMDS_GAME_L];
	}
}
#else   //#ifdef USE_JAPANESE_IN_JPEG_MODE
void DispJpgRotateStr(void)
{
    UINT8 *str = "";

#ifndef JPEG_EXT2FULL
    const UINT8 *osdRotStr[5] =
    {
        ROTATION_LEFT_STR, ROTATION_RIGHT_STR, ROTATION_L_R_STR,  "", ROTATION_UP_DOWN_STR,
    };
    str = osdRotStr[sys_cmd - CMDS_GAME_L];
#elif defined(NINTAUS_DVD)
    const UINT16 rotOSDStr[5] =
    {
        STR_OS_PICTURE_ROTATE_LEFT, STR_OS_PICTURE_ROTATE_RIGHT,
        STR_OS_PICTURE_LR, 0, STR_OS_PICTURE_UD,
    };
    psprintf(RegionValStr[REGION1], "");
    PrintOsdMsg(rotOSDStr[sys_cmd - CMDS_GAME_L], REGION1, 1, 0);
#elif  defined(USE_CHINESE_IN_JPEG_ROTATE)&&defined(BBK_DVD)//zhaoyanhua add 2004-2-9 14:44
    if( (sys_cmd == CMDS_GAME_L) || (sys_cmd == CMDS_GAME_L) )
        str = (UINT8 *)_OsdMessegeFont1[osd_font_mode][STR_OS_PICTURE_ROTATE];
    else
        str = (UINT8 *)_OsdMessegeFont1[osd_font_mode][STR_OS_PICTURE_UPTURN];
#else  //for direct string display
    const char * const osdRotStr[5] =
    {
    #if defined(ENGLISH_OSD_IN_JPEG_ROTATE)//wuxiaofeng 02-27 for minton DVD
    "ROTATE ANTI-CLOCKWISE", "ROTATE CLOCKWISE", "LEFT-RIGHT", "", "UP-DOWN",
	#elif  defined(SUPPORT_MALATA_JPEG_ROTATION_SHOW)
    "ROTATE", "ROTATE", "ROTATE", "1234",  "ROTATE",	
	#elif defined(ONLY_USE_ANGLE_TO_ROTATE)&&defined(JPG_EFFECT)
	"ORIGINAL","90 DEG CW","180 DEG CW","90 DEG CCW",
	#else
    "<<<", ">>>", "LEFT-RIGHT", "1234",  "UP-DOWN",
	#endif
    };
    #if defined(ONLY_USE_ANGLE_TO_ROTATE)&&defined(JPG_EFFECT)
    str = (UINT8 *)osdRotStr[rotate_mode];
    #else
    str = (UINT8 *)osdRotStr[sys_cmd - CMDS_GAME_L];
    #endif
#endif  //#ifdef NINTAUS_DVD

#ifndef NINTAUS_DVD
    psprintf(RegionValStr[REGION1], str);
    PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
#endif
}
#endif  //ifdef USE_JAPANESE_IN_JPEG_MODE


#ifdef JPG_EFFECT

//liumzh move here ,from jpegeffect.c ,2006-6-9 14:33
void jpeg_effect_get_str(void)
{
        #ifdef USE_JAPANESE_IN_JPEG_MODE     //hq, 2004-3-11 14:24        
#ifdef OSD_L_JP_BEFORE_EN//hq, 2004-3-22 9:49
//because of 
//OSD_LAGN_SETUP_STRING     LCD_JA,LCD_EN,0,0,0,0,0,0
//OSD_LANG_SETUP_MAP        {1,0,0,0,0,0,0,0} //mapping table(OSD_LAGN_SETUP_STRING --> USE_XXX_OSD)
    BYTE my_osd_font_mode = 0;
    if(osd_font_mode == 0)
        my_osd_font_mode = 1;
        else
        my_osd_font_mode = 0;
    if (setup_item[LANGPAGE][LANGITEM][my_osd_font_mode+2]==LCD_JA)        
#else//OSD_L_JP_BEFORE_EN
        if (setup_item[LANGPAGE][LANGITEM][osd_font_mode+2]==LCD_JA)
#endif//OSD_L_JP_BEFORE_EN        
        {
            psprintf(RegionValStr[REGION1], jpeg_effect_str_japanese[Jpg_effect_mode]);
        }else      
        #endif//USE_JAPANESE_IN_JPEG_MODE
        
        #ifdef USE_CHINESE_IN_JPEG_MODE         //fengjl add 4-1-5 20:37
        if ( IsOSDChinese() )
        {
            psprintf(RegionValStr[REGION1], jpeg_effect_str_chinese[Jpg_effect_mode]);
        }else
        #endif//#ifdef USE_CHINESE_IN_JPEG_MODE         
        {   
            psprintf(RegionValStr[REGION1], jpeg_effect_str[Jpg_effect_mode]);          
        }
}
#endif  //#ifdef JPG_EFFECT
