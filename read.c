/*
 *************************************************************************
 * File Name:   read.h
 * Created:     2003/8/1 12:49PM Maoyong 
 * Description: Repeat reading implement C file
 * Maintain:    Maoyong 2004.06.09 rewrite
 ************************************************************************
 */
#include "user_init.h"
#include "global.h"

#ifdef SUPPORT_REP_READ

#include "read.h"
#include "osd.h"
#include "func.h"
#include "osd_arc.h"
#include "stdlib.h"
#include "cfont.h"
#include "vpp.h"
#include "ircmd.h"

#include "emuio.h"
#include "sio.h"
#include "dsp3_def.h"
#include "dsp3_if.h"

/*
******************************************************************************
*                           EXTERN FUNC TIONPROTOTYPES 
******************************************************************************
*/
#ifndef NEW_OSD_DRIVER
extern void osd_draw_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor);
extern void osd_draw_setup_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown);
extern void osd_DrawString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor);
extern void osd_DrawRegionString(BYTE xStart, BYTE yStart, BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r);
extern void osd_DrawRegionLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth, BYTE r);
extern void osd_draw_button_outline(int x1, int y1, int x2, int y2, int bDown, unsigned mask, int r);
extern void osd_draw_region_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor, BYTE r);
extern void osd_print_read_eq(UINT8 r, const BYTE * p);
extern void osd_draw_read_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown);
extern void osd_init_rep_reading(void);
#endif

extern int IsOSDChinese();
extern int is_menu(void);
#ifdef SUPPORT_SOUND_EFFECT
//2004AUDDRV extern int AudioIOControl(UINT16 wCode, UINT32 cType, UINT32 wParam);
#else
//2004AUDDRV extern int AudioIOControl(UINT16 wCode, BYTE cType, UINT16 wParam);
#endif
extern void setup_eq_display(UINT8 val);
extern void add_input_num(int *v);
extern UINT32 get_dsp3_pcm_value(unsigned x_off);
extern void set_dsp3_pcm_value(unsigned x_off, unsigned value);

#ifndef DVDRELEASE
#define  READ_DBG
#endif

/*========================Begining of Implement Code ======================*/

UINT8 uReadSel[MAX_READ_ITEM] = {REC_Q_MIDDLE, FUDO_REPEAT, 0, 0};  //for selection initialization

const UINT8 uReadItem[MAX_READ_ITEM][MAX_ITEM_SEL]=
{
    {SET_FUNC, STR_OS_REC_MODE, STR_OS_HIGH, STR_OS_MIDDLE, STR_OS_LOW, 0,},
    {SET_FUNC, STR_OS_READ_MODE, STR_OS_GENDU, STR_OS_REPEAT, STR_OS_COMPARE, 0,},
    {SET_NM,   STR_OS_REP_TIMES, STR_OS_TIME_PROMP, 0, 0, 0},       
    {SET_CHART, STR_OS_READ_EQ, 0, 0, 0, 0},
};

const char *const read_osd_str[MAX_READ_OSD_LANGS][MAX_OSD_STR] =  
{
    //English 
    {
        "REC MODE",             //0
        "HIGH",                 //1 
        "MIDDLE",               //2
        "LOW",                  //3
        "READ MODE",            //4 
        "FOLLOW",               //5
        "COMPARE",              //6
        "REPEAT",               //7
        "REP TIMES",            //8        
        "EQ",                   //9
        "__",                   //10
    },
    //Chinese
    {
        OS_REC_MODE,            //0   
        OS_REC_HIGH,            //1  
        OS_REC_MIDDLE,          //2  
        OS_REC_LOW,             //3  
        OS_READ_MODE,           //4  
        OS_READ_GENDU,          //5  
        OS_READ_COMPARE,        //6  
        OS_READ_REPEAT,         //7  
        OS_REP_TIMES,          //8  
        OS_READ_EQ,             //9 
        "__",                   //10
    }, 
};

/*
******************************************************************************
* Function: RepReadSendCmd()
* Description: Send DSP command for record and rep reading control
* Syntax: void RepReadSendCmd(UINT8 uCmdType);
* Parameters: uCmdType-----type of rep read DSP command
* Returns: none
******************************************************************************
*/
int RepReadSendCmd(UINT8 uCmdType)
{
    int iRes;
    
    switch(uCmdType){
        case FUDO_CMD_STOP:
            //ClearReadMode();    
            printf("=========send fudu stop command========\n");
            break;
        case FUDO_CMD_REC:
            //set_dsp3_pcm_value(DSP_RUNTIME_CDDA_MIC_BUF_FULLRATIO, 0);
            SetReadRecording();           
            printf("=========send fudu record command========\n");
            break;
        case FUDO_CMD_PLAY:
            SetReadPlayback();
            printf("=========send fudu play command========\n");
            break;
        case FUDO_CMD_PAUSE:
            printf("=========send fudu pause command========\n");
            break;
        case FUDO_CMD_Q_H:       
            printf("=========send fudu high quality setting command========\n");
            break;
        case FUDO_CMD_Q_M:       //middle record quality
            printf("=========send fudu middle quality setting command========\n");
            break;
        case FUDO_CMD_Q_L:
            printf("=========send fudu low quality setting command========\n");
            break;
        default: 
            break; 
    }   

    iRes = DSP_AudioIOControl(RECORDMIC,uCmdType, 0);//2004AUDDRV AudioIOControl(RECORDMIC,uCmdType, 0);
    return iRes;
}

/*
******************************************************************************
* Function: SetRecordQuality()
* Description: Setup rep read record quality
* Syntax: void SetRecordQuality(UINT8 uType);
* Parameters: uCmdType-----type of rep read DSP command
* Returns: none
******************************************************************************
*/
void SetRecordQuality(UINT8 uIndex)
{
    switch(uIndex){
        case 0:
            RepReadSendCmd(FUDO_CMD_Q_H);
            break;
        case 1:
            RepReadSendCmd(FUDO_CMD_Q_M);
            break;
        case 2:
            RepReadSendCmd(FUDO_CMD_Q_L);
            break;
        default:
            break; 
    }
}

/*
******************************************************************************
* Function: InitRead()
* Description: initial read related vars 
* Syntax: void InitRead(void);
* Returns: none
******************************************************************************
*/
void InitRead(void)
{
    uRecordMode = uReadSel[REC_MODE_ITEM];
    uFudoMode = uReadSel[READ_MODE_ITEM];
    uPlaybackTimes = DEF_REP_TIMES;
    uReadMenuLevel = 0;
    uReadShowEq = 0;
    setup_eq_display(0x0f);
    ClearReadMode();
}

/*
******************************************************************************
* Function: CancelRead()
* Description: cancel fudo state
* Syntax: void CancelRead(void);
* Returns: none
******************************************************************************
*/
void CancelRead(void)
{
    full_scrn = 0;
    osd_init();
    setup_eq_display(0x0f);
    ClearReadMode();
    AUDIF_Demute();//2004AUDDRV AudioDemute();
}

/*
******************************************************************************
* Function: ClearReadMode()
* Description: clear read related vars and state and do some action
* Syntax: void ClearReadMode(void);
* Returns: none
******************************************************************************
*/
void ClearReadMode(void)
{
    uReadStatus = READ_ST_NONE; 
    RepReadSendCmd(FUDO_CMD_STOP);
    ReadShowPromptInfo(0);
    uReadEqType = ORI_EQ;
    uRealPBTimes = uPlaybackTimes;                
    uPlaybackFlag = 0;   
}

/*
******************************************************************************
* Function: GetReadBtnMode()
* Description: Draw read panel item button
* Syntax: UINT8 GetReadBtnMode(UINT8 uIndex, UINT8 uLevel);
* Parameters: uIndex    ---------- button's index
              uLevel    ---------- 0: Main Menu, 1: Sub Menu Level  
* Returns: current button's mode of sub menu button
******************************************************************************
*/
UINT8 GetReadBtnMode(UINT8 uIndex)
{
    if(uIndex == uReadSel[index_y] ){
        if (uIndex == index_y2 )
            return SEL_BTN_HL;
        else
            return SEL_BTN_NORM;
    }else{
        if (uIndex == index_y2 )
            return UNSEL_BTN_HL;
        else
            return UNSEL_BTN_NORM;
    }
}
/*
******************************************************************************
* Function: DrawReadItem()
* Description: Draw read panel item button
* Syntax: void DrawReadItem(UINT8 uID, UINT8 uUpDown, UINT8 uDrawY, UINT8 uLevel);
* Parameters:   draw_y    ----------    index in button vertical array   
                uLevel    ----------    0: Main Menu, 1: Sub Menu Level
                uMode     ----------    button's sel/unsel/hl...
* Returns: none
******************************************************************************
*/
void DrawReadItem(UINT8 uDrawY, UINT8 uLevel, UINT8 uMode)
{
	const char   *str;	
	UINT8 uCurrY ;
	UINT8 uBtnX;
	UINT8 uBtnStrX;
	UINT8 uBtnLen;	
	UINT8 uUpDown;
	UINT8 uBgColor;
	UINT8 uFontColor;
	UINT8 uID;
	UINT8 uLangID = 0;
	
	if(IsOSDChinese())
        uLangID = 1;
	 
	if(uLevel){ //sub level
	    uBtnX = READ_SUB_MENU_X;
	    uBtnStrX = READ_SUB_MENU_X + 1;
	    uCurrY = index_y2;
	    uBtnLen = READ_BTN_WIDTH;
	    uID = uReadItem[index_y][uDrawY + 2];
	}else{      //main level
	    uCurrY = index_y;
	    uBtnX = 1;
	    uBtnStrX = 2;
	    uBtnLen = READ_BTN_WIDTH;
	    uID = uReadItem[uDrawY][1];
    }
	
	str=read_osd_str[uLangID][uID];    
    
    switch(uMode)
    {
        default:
    	case UNSEL_BTN_NORM:  
    		uFontColor = FONT_CLR; 
    		uBgColor = BG_CLR; 
    		uUpDown = BTN_UP;     		
    		break;
    	case UNSEL_BTN_HL:
    		uFontColor = ANTI_FONT_CLR; 
    		uBgColor = ANTI_BG_CLR; 
    		uUpDown = BTN_UP;     		
    		break;
    	case SEL_BTN_NORM:
    		uFontColor = SEL_FONT_CLR; 
    		uBgColor = BG_CLR; 
    		uUpDown = BTN_DOWN;     		
    		break;
    	case SEL_BTN_HL:
    		uFontColor = ANTI_FONT_CLR; 
    		uBgColor = ANTI_BG_CLR; 
    		uUpDown = BTN_DOWN; 
    		break;
    }    
	
    if(uLevel)
        uDrawY += index_y_start;
	osd_draw_read_button(uBtnX, uDrawY, uBtnLen,  uBgColor, uUpDown);
	osd_DrawRegionString(uBtnStrX, uDrawY*8 + 2, (BYTE *)str, uFontColor, uBgColor, READ_REGION);
}

/*
******************************************************************************
* Function: DrawRead2ndMenu()
* Description: Draw read panel item button
* Syntax: void DrawRead2ndMenu(UINT8 uTypee);
* Parameters:   type ----------  0: for info display 1: for sub menu display
* Returns: none
******************************************************************************
*/
void DrawRead2ndMenu(UINT8 uType)
{
    UINT8 uID, i;
    const char *str;
    
    if(uType == 0){ //just show current setup information of every items
        //show current record mode
        uID = uReadItem[REC_MODE_ITEM][uRecordMode + 2];
        str = read_osd_str[0][uID];
        osd_DrawRegionString(READ_SUB_MENU_X + 1, REC_MODE_ITEM * 8 + 2, (BYTE *)str, 
                             SEL_FONT_CLR, BG_CLR, READ_REGION);
        
        //show current record mode
        uID = uReadItem[READ_MODE_ITEM][uFudoMode + 2];
        str = read_osd_str[0][uID];
        osd_DrawRegionString(READ_SUB_MENU_X + 1, READ_MODE_ITEM * 8 + 2, (BYTE *)str, 
                             SEL_FONT_CLR, BG_CLR, READ_REGION);
        
        //show current playback times
        psprintf(linebuf, "%02d", uPlaybackTimes);
        osd_DrawRegionString(READ_SUB_MENU_X + 1, REPTIMES_ITEM * 8 + 2, linebuf, 
                             SEL_FONT_CLR, BG_CLR, READ_REGION);
                              
    }else{  //draw sub menu for selection
        osd_draw_region_rect( (READ_SUB_MENU_X - 1) * 16 , 8, (READ_BTN_WIDTH + 1)*16 + 4, 32*4, 
                             BG_CLR, READ_REGION); //clear the old sub menu
        osd_DrawRegionString(READ_SUB_MENU_X - 1, index_y * 8 + 2, Ch_arrorR,
                             FONT_CLR, BG_CLR, READ_REGION);//draw arrow
       
        uReadSelMaxIndex = 0;
        for(i = 2; i < MAX_ITEM_SEL; i++)
        {
            //show sub item except EQ item
            if(uReadItem[index_y][0] != SET_CHART){ 
                
                uID = uReadItem[index_y][i];
                if(uID == 0)
                    break;
                    
                if( (i - 2) == uReadSel[index_y] ){
                    if(uReadMenuLevel)
                        DrawReadItem(i - 2, SUB_LEVEL, SEL_BTN_HL );
                    else
                        DrawReadItem(i - 2, SUB_LEVEL, SEL_BTN_NORM );
                }
                else
                    DrawReadItem(i - 2, SUB_LEVEL, UNSEL_BTN_NORM );
            }            
        }
        uReadSelMaxIndex = i - 2;
    }
    
}

/*
******************************************************************************
* Function: ReadShowPromptInfo()
* Description:  check if need to do fudo cmd and flow contrl 
* Syntax: void ReadShowPromptInfo(UINT8 uShowHide);
* Parameters:   uShowHide ---------- 0: Erase info, 1:Display info
* Returns: none
******************************************************************************
*/
void ReadShowPromptInfo(UINT8 uShowHide)
{
    UINT8 uLangID = 0;
    BYTE ccTimes[10];
    
    if(!uReadShowEq)
        return;
        
	const char *ccInfo[MAX_READ_OSD_LANGS][3] = 
	{
	    { "RECORD...",      "READ...",      "PLAYING",}, 
	    { OS_PLEASE_REC, OS_PLEASE_READ, OS_PLAY_REC, },
	};
	
	if(IsOSDChinese())
        uLangID = 1;
    
    //clear original information
    osd_draw_region_rect(INFO_STR_X * 16 - 2, INFO_STR_Y*4-2, (READ_BTN_WIDTH - 1) *16, 30, BG_CLR, READ_REGION); 
    
    if(uShowHide){             
        if( IsReadRecording() )
            strcpy(linebuf, ccInfo[uLangID][0]);
        else if( IsReadPlayback() ){  
            psprintf(ccTimes, " %d",  uPlaybackTimes - uRealPBTimes + 1);                 
            strcpy(linebuf, ccInfo[uLangID][2]);
            strcat1(linebuf, ccTimes); 
        }else if( IsReadGendu() && uPlaybackFlag ) 
            strcpy(linebuf, ccInfo[uLangID][1]);
        else
            linebuf[0] = '\0';
        osd_DrawRegionString(INFO_STR_X, INFO_STR_Y, linebuf, INFO_FONT_CLR, BG_CLR, READ_REGION);
    }
}

/*
******************************************************************************
* Function: ShowReadPage()
* Description: Show Read operaton osd panel
* Syntax: void ShowReadPage(void);
* Returns: none
******************************************************************************
*/
void ShowReadPage(void)
{
    UINT32  i;
    
    //initialization
    uRecordMode = uReadSel[REC_MODE_ITEM];
    uFudoMode = uReadSel[READ_MODE_ITEM];    
    uReadMenuLevel = 0;
    uReadShowEq = 0;    
    setup_eq_display(0x0f);
    index_y = MAX_READ_ITEM;
    index_y2 = 0;
    
    ClearReadMode();      
    RepReadSendCmd(FUDO_CMD_STOP);
    SetRecordQuality(uRecordMode);
    
    //draw outline 
    osd_init_rep_reading();            
    osd_draw_region_rect(0, 0, READ_REG_W*16, READ_REG_H, BG_CLR, READ_REGION);       	   
    osd_draw_button_outline(2, 2, READ_REG_W*16-2, READ_REG_H -2, BTN_UP, 0x0F, READ_REGION);
       	    
    //draw main buttons       	    
    for(i = 0; i< MAX_READ_ITEM; i++)
    {
        DrawReadItem(i, MAIN_LEVEL, UNSEL_BTN_NORM);    
    }
    
    //initialization for display eq
    uReadShowEq = 1;            
    uReadEqType = ORI_EQ;
    setup_eq_display(1);
    for(i=0;i<13;i++)
        bEqEnergyMax[i]=0;
    unEqMaxRef=0;
    
    //draw EQ background    
    //osd_draw_region_rect( READ_SUB_MENU_X * 16 , EQ_BG_START_Y, READ_BTN_WIDTH * 16, 55, FONT_CLR, READ_REGION);   
}

/*
******************************************************************************
* Function: ReadSaveSetup(void)
* Description:  save rep read setup
* Syntax: void ReadSaveSetup(void);
* Returns: none
******************************************************************************
*/
void ReadSaveSetup(void)
{   
    //Note: when do setup, we clear current read mode
    if(index_y == REC_MODE_ITEM){
        uReadSel[index_y] = index_y2;
        uRecordMode = index_y2;
        ClearReadMode();
        AUDIF_Demute();//2004AUDDRV AudioDemute();
        SetRecordQuality(uRecordMode);
    }else if(index_y == READ_MODE_ITEM){
        uReadSel[index_y] = index_y2;
        uFudoMode = index_y2;
        ClearReadMode();
        AUDIF_Demute();//2004AUDDRV AudioDemute();
    }else{
        if(uPBTimesSetting){            
            uPlaybackTimes = uPBTimesSetting;            
            ClearReadMode();
            AUDIF_Demute();//2004AUDDRV AudioDemute();
        }
    }
}

/*
******************************************************************************
* FUDO UI OPERATION FUNCTIONS
* Up/Down/Left/Right & Enter Operation process
******************************************************************************
*/
void read_func_up(void)
{
    UINT8 uOldIndex;
    
    if(uReadMenuLevel == 0){
        uOldIndex = index_y;
        if(index_y >= MAX_READ_ITEM){
            index_y = MAX_READ_ITEM - 1;            
            DrawReadItem(index_y, MAIN_LEVEL, SEL_BTN_HL );
        }else{
            //current button index       
       	    if(index_y == 0){
       	        index_y = MAX_READ_ITEM - 1;	
            }else{
                index_y--;
            }      
              
            //change button status
            DrawReadItem(uOldIndex, MAIN_LEVEL, UNSEL_BTN_NORM );
            DrawReadItem(index_y, MAIN_LEVEL, SEL_BTN_HL );
        }
        //refresh sub menu
       	index_y_start = index_y;                //sub menu y start intilization
        index_y2 = uReadSel[index_y]; 
        uReadShowEq = 0;
       	if(index_y == EQ_ITEM){
       	    //clear sub menu and draw EQ background
       	    osd_draw_region_rect( (READ_SUB_MENU_X - 1) * 16 , 8, (READ_BTN_WIDTH + 1)*16 + 4, 32*4, BG_CLR, READ_REGION); 
            //osd_draw_region_rect( READ_SUB_MENU_X * 16 , EQ_BG_START_Y, READ_BTN_WIDTH * 16, 110, FONT_CLR, READ_REGION);                                           
            uReadShowEq = 1;                                        
        }else
       	    DrawRead2ndMenu(1);
    }else{  /*second level*/
        uOldIndex = index_y2;
        if(index_y2 > 0)
            index_y2--;
            
        //change sub button status
        DrawReadItem(uOldIndex, SUB_LEVEL, GetReadBtnMode(uOldIndex) );
        DrawReadItem(index_y2, SUB_LEVEL, GetReadBtnMode(index_y2) );
    }
}

void read_func_down(void)
{
    UINT8 uOldIndex;
    
    if(uReadMenuLevel == 0){
        uOldIndex = index_y;
        if(index_y >= MAX_READ_ITEM){
            index_y = 0;
            DrawReadItem(index_y, MAIN_LEVEL, SEL_BTN_HL );
        }else{
            //current button index       
       	    if(index_y == MAX_READ_ITEM - 1){
       	        index_y = 0;	
            }else{
                index_y++;
            }        
            //change sub button status
            DrawReadItem(uOldIndex, MAIN_LEVEL, UNSEL_BTN_NORM );
            DrawReadItem(index_y, MAIN_LEVEL, SEL_BTN_HL );
        }
        //refresh sub menu
        index_y_start = index_y;                //sub menu y start intilization
        index_y2 = uReadSel[index_y];    
        uReadShowEq = 0;
       	if(index_y == EQ_ITEM){
            //clear sub menu and draw EQ background
       	    osd_draw_region_rect( (READ_SUB_MENU_X - 1) * 16 , 8, (READ_BTN_WIDTH + 1)*16 + 4, 32*4, BG_CLR, READ_REGION); 
            //osd_draw_region_rect( READ_SUB_MENU_X * 16 , EQ_BG_START_Y, READ_BTN_WIDTH * 16, 110, FONT_CLR, READ_REGION);                                           
            uReadShowEq = 1;                                        
       	}else
       	    DrawRead2ndMenu(1);
    }else{  /*second level*/
        uOldIndex = index_y2;
        if(index_y2 < (uReadSelMaxIndex - 1) )
            index_y2++;
        //change button status
        DrawReadItem(uOldIndex, SUB_LEVEL, GetReadBtnMode(uOldIndex) );
        DrawReadItem(index_y2, SUB_LEVEL, GetReadBtnMode(index_y2) );
    }
}

void read_func_left(void)
{
    if(uReadMenuLevel){
        uReadMenuLevel = 0;
        DrawRead2ndMenu(1);
        DrawReadItem(index_y, MAIN_LEVEL, SEL_BTN_HL);
    }
}

void read_func_right(void)
{
    if( (uReadMenuLevel == 0) && (index_y != EQ_ITEM) )
        read_func_select();
}

void read_func_select(void)
{
    if(index_y >= MAX_READ_ITEM)
        return;
        
    if(uReadMenuLevel == 0){    
        if(index_y != EQ_ITEM){   
       	    DrawReadItem(index_y, MAIN_LEVEL, SEL_BTN_NORM);
       	    index_y_start = index_y;                //sub menu y start intilization
            index_y2 = uReadSel[index_y];  
            uPBTimesSetting = 0;
            uReadMenuLevel = 1;
            DrawRead2ndMenu(1);
            uReadShowEq = 0;
        }
    }else{  //sub menu 
        uReadMenuLevel = 0; 
        ReadSaveSetup();
        DrawReadItem(index_y, MAIN_LEVEL, SEL_BTN_HL);
             
        //clear the  sub menu and draw EQ background
       	osd_draw_region_rect( (READ_SUB_MENU_X - 1) * 16 , 8, (READ_BTN_WIDTH + 1)*16 + 4, 32*4, BG_CLR, READ_REGION); 
        //osd_draw_region_rect( READ_SUB_MENU_X * 16 , EQ_BG_START_Y, READ_BTN_WIDTH * 16, 110, FONT_CLR, READ_REGION);                                           
        uReadShowEq = 1;                                               
    }
}

void read_func_input(void)
{
    int iDispVal;
    
    iDispVal = uPBTimesSetting;
    add_input_num(&iDispVal);
    uPBTimesSetting = (iDispVal % 100);
    if(uPBTimesSetting > 100)
        uPBTimesSetting = 0;
        
    if(uPBTimesSetting == 0){
        strcpy(linebuf, "__");        
    }else{
        psprintf(linebuf, "%02d", uPBTimesSetting);
    }
    osd_DrawRegionString(READ_SUB_MENU_X + 1, index_y*8 + 2, linebuf, WHITE_CLR, ANTI_BG_CLR, READ_REGION);
}

/*
******************************************************************************
* Function: DisplayReadEq(void)
* Description:  save rep read setup
* Syntax: void DisplayReadEq(UINT8 type, BYTE r);
* Parameters:  type ---------  ORI_EQ/REC_EQ, Eq type
               r    ---------  region to diplay read eq 
* Returns: none
******************************************************************************
*/
//Steven 2006/10/04 modify , use get_dsp3_pcm_value() instead of directly access address //
void DisplayReadEq(UINT8 type, BYTE r)
{
    BYTE    i,j;
	BYTE	bEqValue[7];
	//BYTE 	*p;
	
	if( (full_scrn & READ) && uReadShowEq )	{
	    if(bEqDisplay == 4){
	        //if(type == ORI_EQ)//Steven 2006/10/04 replace cache to uncache way to handshake with DSP module//
                //p = get_dsp_pcm_uptr(DSP_RUNTIME_EQ_SPECTRUM*3,0);
            //else    //Record voice's EQ
                //p = get_dsp_pcm_uptr(DSP_RUNTIME_MIC_EQ_SPECTRUM*3,0);
            			
            for (i=0, j=0;i<7;i++) 
            {
                UINT32  eqSrc;
                UINT32  eqTemp;
                if(type == ORI_EQ)
                    eqSrc = get_dsp3_pcm_value((DSP_RUNTIME_EQ_SPECTRUM+i))>>8;
                else    //Record voice's EQ
                    eqSrc = get_dsp3_pcm_value((DSP_RUNTIME_MIC_EQ_SPECTRUM+i))>>8;
                //eqSrc = (((*p)<<8) | *(p+1));                
                //p+=3;
        			
                if (eqSrc > unEqMaxRef)
        			unEqMaxRef = eqSrc;
        
                //normalize value to 0 ~ 25
                if (unEqMaxRef==0) //EQ value range check, 
                     eqTemp = 0;
                else{
                    eqTemp = eqSrc*25/unEqMaxRef;
                    bEqValue[i] = eqTemp;
                    if (bEqValue[i]<4) {
                        j++;
                    }
                }
            }

            //adjust max refrence 
            if ( (j>=6) && (unEqMaxRef>400) )
                unEqMaxRef=unEqMaxRef-(unEqMaxRef/8);			
            osd_print_read_eq(r, bEqValue);	            
            setup_eq_display(1);
        }else
            bEqDisplay++;
    }
}

/*
******************************************************************************
*           FUDO FLOW CONTROL FUNCTIONS
******************************************************************************
*/
/*
******************************************************************************
* Function: PollingRecBufStatus()
* Description:  polling the buffer's statuas 
* Syntax: UINT32 PollingRecBufStatus(void);
* Returns: 1: buffer all used. 0: not used over
* Side effect: when buffer used over, send REPEAT AB cmd       
******************************************************************************
*/

UINT32 PollingRecBufStatus(void)
{
    UINT32 uRatio;
   
    uRatio = get_dsp3_pcm_value(DSP_RUNTIME_CDDA_MIC_BUF_FULLRATIO);
        
    if( (IsReadPlayback() && (uRatio <= 2)) || 
      ( IsReadRecording() && (uRatio >= 98 )) ){
        if(IsReadRecording())
            uRecBufRatio = uRatio;
        return 1;
    }else
        return 0;
}

/*
******************************************************************************
* Function: ReadRecPlayback()
* Description:  read flow control for record voice playback
* Syntax: void ReadDoRecPlayback(void);
******************************************************************************
*/
void ReadRecPlayback(void)
{
    SetReadPlayback(); 
    RepReadSendCmd(FUDO_CMD_PLAY);
    uReadEqType = REC_EQ;
    ReadShowPromptInfo(1);           
}
/*
******************************************************************************
* Function: MainLoopCtrlReadMode()
* Description:  check if need to do special control mode in MediaMainLoop 
* Parameters:   uFlag --------- befor/in/ou MediaMainLoop
* Syntax: void MainLoopCtrlReadMode(UINT32 uFlag);
* Returns: when in MainLoop, return 1 will break main loop
******************************************************************************
*/
UINT32 MainLoopCtrlReadMode(UINT32 uFlag)
{   
    UINT32 uRes = 0; 
          
    if( (full_scrn & READ) ){
        switch(uFlag)
        {
            case PRE_MAIN_LOOP: //avoid audio stop cmd, we send fudo cmd just before mainloop
                if( IsReadGendu() )
                    break;
                
                if(uPlaybackFlag && uRealPBTimes){
                    set_dsp3_pcm_value(DSP_RUNTIME_CDDA_MIC_BUF_FULLRATIO, uRecBufRatio);
                    if( IsReadRepeat() ){
                        ReadRecPlayback();
                        uRealPBTimes--;
                    }else if( IsReadCompare() ){
                        if( IsReadPlayback() || IsReadRecording() ){                        
                            uReadStatus = READ_ST_NONE;
                            uReadEqType = ORI_EQ; 
                            ReadShowPromptInfo(0);  
                        }else{
                            ReadRecPlayback();
                            uRealPBTimes--;
                        }
                    }
                }else if(uRealPBTimes == 0) {   //playback repeat tiems over, clear read mode
                    ClearReadMode();                                 
                }else if( IsReadRecording() ){                
                    RepReadSendCmd(FUDO_CMD_REC);
                    uReadEqType = REC_EQ;
                    ReadShowPromptInfo(1);                     
                }
                break;
            
            case IN_MAIN_LOOP:  //for read and flow control 
                if( IsReadGendu() ){    //for gendu, jsut mute the origianal music
                    if(uPlaybackFlag)
                        AUDIF_Set_Volume(0);//AudioSetVolume(0);                               
                }else if( IsReadMode() ){
                    AUDIF_Set_Volume(0);//AudioSetVolume(0);
                    uReadEqType = REC_EQ; 
                    if( PollingRecBufStatus() ){
                        if( IsReadRecording() ) //set flag for playback control
                            uPlaybackFlag = 1;
                    
                        //if between AB, buffer used over, should do REPEAT AB
                        RepReadSendCmd(FUDO_CMD_STOP);                         
                        ircmd_post_func( CMD_FUNC | CMD_FUNC_REPAB );
                        uRes = 1;
                    }
                }
                break;
            
            case  POST_MAIN_LOOP:  //for read and flow control  
                break;           
        }
    }
    return uRes;
}

/*
******************************************************************************
* Function: RepBCheckReadMode()
* Description:  check if need to do fudo cmd and flow contrl 
* Syntax: void RepBCheckReadMode(void);
* Returns: none
******************************************************************************
*/
void RepBCtrlReadMode(void)
{    
    if( (full_scrn & READ) ){
        AUDIF_Set_Volume(0);//AudioSetVolume(0);
       
        switch(uFudoMode)      
        {
            case FUDO_GENDU:    
                //just toggle for EQ type and original/record voice
                uPlaybackFlag ^= 0x01;
                ReadShowPromptInfo(uPlaybackFlag);    
                uReadEqType = uPlaybackFlag;
                break;
                
            case FUDO_REPEAT:  //just for record flag and when reach B, buffer not full, used the ratio for playback
            case FUDO_COMPARE:
                RepReadSendCmd(FUDO_CMD_STOP);      
                if( IsReadRecording() ){
                    uRecBufRatio = get_dsp3_pcm_value(DSP_RUNTIME_CDDA_MIC_BUF_FULLRATIO);
                    uPlaybackFlag = 1;
                }
                         
                if( (uRealPBTimes == uPlaybackTimes) && (uPlaybackFlag == 0) ){ //when playback record over, send record cmd again 
                    SetReadRecording();                    
                    set_dsp3_pcm_value(DSP_RUNTIME_CDDA_MIC_BUF_FULLRATIO, 0);    
                }
                break;
                
            default:
                break;            
        }// end switch...    
    }// end if...     
}
#endif  //#ifdef SUPPORT_REP_READ







