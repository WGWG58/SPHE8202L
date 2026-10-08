#include "user_init.h"

// 2005/08/29 yltseng, modify draw subtitle function from byte base to pixel base
// 2005/09/12 yltseng, Add new structure for font
// 2005/09/22 yltseng, add support for unix format new line

#if defined( OSD_FONT_API ) && defined( SUPPORT_OSDSRT )

//This is only for Nero Digital Certification (Temp solution)
#ifdef SUPPORT_QUICKTIME
    #include "File_def.h"
    #include "File_if.h"
#endif //SUPPORT_QUICKTIME

#ifdef NEW_OSD_DRIVER

#include "global.h"
#include "func.h"
#include "LanguageUtil.h"

#ifdef SUBTITLE_SUPPORT_ALL_FORMAT
static inline void ModifyStringForTMPlayer( const UINT8* pStr, UINT16 uiStrLen )
{   //suxin,2005-07-29,for support subtitle of TMPlayer(*.txt)
	int     i, j;
	UINT8*  pTmpStr = (UINT8*) pStr;

	for( i = 0; i <= (uiStrLen+11); i++ )
	{
		if( (pTmpStr[i  ] == ',') && 
		    (pTmpStr[i+1] == '2') && 
		    (pTmpStr[i+2] == '=') )
		{	
			UINT16 uiLen = uiStrLen - i + 11;
			i -= 8;
			for( j = 0; j <= uiLen; j++ )
			{
				pTmpStr[i] = pTmpStr[ i + 11 ];
				i++;
			}
			break;
		}
	}//for(i = 0;i<=(size+11);i++)
}
#else
#define ModifyStringForTMPlayer(...)
#endif

#ifdef SWITCH_SUB_DIRECTION // 2005/09/30 yltseng, libing 2005-7-15 14:43
#define redirect_subtitle()                                             \
    if( subtitle_ratate_flag )                                          \
    {                                                                   \
        uiStart_x = ( uiRegionWidth + uiLineLen ) >> 1;                 \
        UINT8   uiChar;                                                 \
        UINT8*  pStrPtr     = &aLineBuf[0];                             \
        UINT8*  pNumStart   = NULL;                                     \
        while( TRUE )                                                   \
        {                                                               \
            uiChar = *pStrPtr;                                          \
            if( !pNumStart )                                            \
            {                                                           \
                if( uiChar >= '0' && uiChar <= '9' )                    \
                    pNumStart = pStrPtr;                                \
            }                                                           \
            else                                                        \
            {                                                           \
                if( uiChar < '0' || uiChar > '9' )                      \
                {                                                       \
                    UINT8* pNumEnd = pStrPtr - 1;                       \
                    while( (UINT32) pNumStart < (UINT32) pNumEnd )      \
                    {                                                   \
                        UINT8 uiTmp = *pNumEnd;                         \
                        *pNumEnd    = *pNumStart;                       \
                        *pNumStart  = uiTmp;                            \
                        pNumStart++;                                    \
                        pNumEnd--;                                      \
                    }                                                   \
                    pNumStart = NULL;                                   \
                }                                                       \
            }                                                           \
            if( uiChar == 0 ) break;                                    \
            pStrPtr++;                                                  \
        }                                                               \
    }
#else
#define redirect_subtitle()
#endif

#if defined (SUPPORT_SMI_MultiLanguage)//libing 2006/3/16
extern int strncmpIgnoreCase(char *a,char *b,unsigned i);
extern UINT8  SmiSupType;
extern BYTE nowSupLang;
extern BYTE lang_temp[][15];
extern BYTE lang_num;
#define MAX_Para   3
#endif

void ShowOSDText( const UINT8* pStr,  UINT16 uiStrLen )
{
    // get font width & height
#ifdef	SUPPORT_FONT_OUTLINE  // 2006-02-24, mimitsai add for adjusting the subtitle string lenth when with subtitle_frame
    #define FONT_WIDTH_INTERNAL_OSD         (18+8-6+1)	// 8: add 4bits for left and right(if width%8=0).
    													// (if width%8!=0, add 4bits for left and right )
#else
    #define FONT_WIDTH_INTERNAL_OSD         18
#endif
    #define FONT_HEIGHT_INTERNAL_OSD        24
    #define OSD_EXTERNAL_SUBTITLE_REGION    3
    #ifdef OSD_SUPPORT_2_COLOR
    #ifdef ALCO_DVD_UI//shenyj add 2006-9-7 08:39ÏÂÎç
    #define FONT_COLOR_INDEX                2       
    #else
    #define FONT_COLOR_INDEX                1       // 2005/12/28 yltseng
    #endif
    #else
    #define FONT_COLOR_INDEX                2
   #endif    

    #ifdef ADJUST_SPACE_BETWEEN_FONT //denghg  add 2006-1-6 06:00     
    #include "osd_AppAPI.h"    
    const UINT8* pBmp   = NULL;
    UINT8  uiFONTRealWidth = 0;
    UINT8  uiDrawWidth     = 0;
    UINT8  uiDrawHeight    = 0;
    #endif
    
    UINT8   uiFontWidth     = FONT_WIDTH_INTERNAL_OSD; 
    UINT8   uiFontHeight    = FONT_HEIGHT_INTERNAL_OSD;

#ifdef	SUPPORT_FONT_OUTLINE
	Mp4Subtitle_flag=1;
#endif

#if defined (SUPPORT_SMI_MultiLanguage)//libing 2006/3/16
	UINT8 Para_num=0;
	UINT8 nPara_num;
	UINT32 Para_addr[MAX_Para];
	UINT8  Para_size[MAX_Para];
	BYTE ParaCntFlg=0;
#endif

    if( langGetSupportedFontNum() )
    {
        UINT8 uiHeight;
        if( !langGetFontSize( &uiFontWidth, &uiHeight ) )
            return;

        UINT8 uiScaleX, uiScaleY;
        langGetScale( &uiScaleX, &uiScaleY );
        uiFontWidth     *= uiScaleX;

        uiHeight    *= uiScaleY;
        uiFontHeight = ( uiHeight     >= uiFontHeight) ? uiHeight : uiFontHeight;
    }

    // get region width & height
    dimension diSize;
    if( !osd_get_original_region_size( OSD_EXTERNAL_SUBTITLE_REGION, &diSize ) )
        return;

    UINT16  uiRegionWidth   = diSize.x_length;
    UINT16  uiRegionHeight  = diSize.y_length;

    // calc max line for subtitle region
    UINT8   uiMaxLine   = uiRegionHeight / uiFontHeight;
    
    // modify string for TMPlayer subtitle
    ModifyStringForTMPlayer( pStr, uiStrLen );
    
    UINT8*  pStrEnd     = (UINT8*) (pStr + uiStrLen);
    UINT8   uiLineCnt   = 0;
    
    //osd_tog_region( OSD_EXTERNAL_SUBTITLE_REGION, OSD_OFF );

#ifdef	SUPPORT_FONT_OUTLINE // 2006-02-24, mimitsai add for adjusting the subtitle string lenth when with subtitle_frame
    uiFontWidth = uiFontWidth+8-6+1;// 8: add 4bits for left and right(if width%8=0).
    								// (if width%8!=0, add 4bits for left and right )
#endif
    

#ifdef SUPPORT_SMI_MultiLanguage//libing 2006/3/16
UINT8   CorrectWordCnt = 0;
	if(SmiSupType)
    {
    	while( (UINT32) pStr < (UINT32) pStrEnd )
    	{
    		if( (*pStr) == '<' && (*(pStr+1) == 'P' || *(pStr+1) == 'p' ) )
    		{
    			if(ParaCntFlg)
			    {   
			       Para_size[Para_num]=CorrectWordCnt;
			       Para_num++;
		        }
		        
    			ParaCntFlg=0;
    			
    			if(lang_num>1)
	    		{
	    			while(*pStr!='='&&(UINT32) pStr < (UINT32) pStrEnd)
	                {
	                   pStr++;
	                }      			
	    		    pStr++;
	    		    if(strncmpIgnoreCase( (BYTE*)pStr,lang_temp[nowSupLang], strlen((const char*)lang_temp[nowSupLang]) )==0)
	    		    {        		       
	    		       while(*pStr!='>')
	    		       {
	    		    	  pStr++;   		       	     		         
	    		       }  
	    		       pStr++;
	    		       Para_addr[Para_num]=(UINT32) pStr;
	    		       CorrectWordCnt=0;
	    		       ParaCntFlg=1;
	       		    }
    		    }
    		    else
    		    {
    		       while(*pStr!='>')
    		       {  
    		    	  pStr++;   		       	     		         
    		       }  
    		       pStr++;
    		       Para_addr[Para_num]=(UINT32) pStr;
    		       CorrectWordCnt=0;
    		       ParaCntFlg=1;    		    
    		    }
    		}
    	    
    		pStr++;
       	    if(ParaCntFlg)
       	      CorrectWordCnt++;       	    
       	}
	    if(ParaCntFlg) 
	    {   
	       Para_size[Para_num]=CorrectWordCnt;
	       Para_num++;
        }
	}
	if(!SmiSupType)
    {      
        Para_num=1;
    }
	nPara_num=0;
    			
#endif  
#if defined (SUPPORT_SMI_MultiLanguage)//libing 2006/3/16
	while(nPara_num<Para_num)
	{   
		if(SmiSupType)
        {          	
            pStr=(BYTE *)Para_addr[nPara_num];
            pStrEnd = (BYTE*) (pStr + Para_size[nPara_num]);
        }
#endif
      
    while( (UINT32) pStr < (UINT32) pStrEnd )
    {
        BYTE    aLineBuf[60];
        UINT8   uiWordCnt   = 0;
        UINT16  uiLineLen   = 0;

        while( ( (*pStr) != '\n' ) && ( (UINT32) pStr < (UINT32) pStrEnd ) )
		{
		    UINT8   uiCurChar   = *pStr;
		    
            if( uiCurChar == '\r' )   //if '\n' not jump next line just continue
            {
                pStr++;
                continue;
            }

            UINT32 uiRtnVal = langIsInCharacterSet( pStr );
            
            if( uiRtnVal == FONT_TWO_BYTE )
			{
                if( uiLineLen + uiFontWidth > uiRegionWidth )
                {
                    break;
                }
                    			    
			    aLineBuf[ uiWordCnt     ] = uiCurChar;
			    aLineBuf[ uiWordCnt + 1 ] = *(pStr+1);
			    
			    #ifdef ADJUST_SPACE_BETWEEN_FONT  //denghg add for FONT_TWO_BYTE 2006-9-25 13:25 
		        ftGetDrawFontSize(pStr, &uiDrawWidth, &uiDrawHeight);
                GetDrawFontBmp(pStr, &pBmp);		    
			    uiFONTRealWidth = Cnt_font_Realwidth( pBmp,uiDrawWidth, uiDrawHeight );
			    uiLineLen      += uiFONTRealWidth;
			    #else			    
			    uiLineLen   += uiFontWidth;
			    #endif
			    
			    uiWordCnt   += 2;
			    pStr        += 2;
			}
			else
            {


                if( uiRtnVal == FONT_NOT_IN_RANGE )
                {
                    #ifndef ADJUST_SPACE_BETWEEN_FONT //DENGHG ADD 2006-1-6 06:04     
                    if( uiLineLen + FONT_WIDTH_INTERNAL_OSD > uiRegionWidth )
                    #else
                    if( uiLineLen + uiFontWidth > uiRegionWidth )   //denghg modify 2006-3-15 9:10
                    #endif                    
                    {                   
                        break;
                    }

                    if( ( uiCurChar < 32 ) || ( uiCurChar > 126 ) )
                    {
    //This is only for Nero Digital Certification (Temp solution)
    #ifdef SUPPORT_QUICKTIME
                        if (GET_FILE_TYPE()==FILE_TYPE_ND)
                            return;
    #endif //SUPPORT_QUICKTIME
                        
                        uiCurChar = '?';
                        ///denghg modify for FONT_NOT_IN_RANGE
                        #ifdef ADJUST_SPACE_BETWEEN_FONT //DENGHG ADD 2006-1-6 06:04     
		    	        ftGetDrawFontSize(&uiCurChar, &uiDrawWidth, &uiDrawHeight);
                        GetDrawFontBmp(&uiCurChar, &pBmp);
		    	        uiFONTRealWidth = Cnt_font_Realwidth( pBmp, uiDrawWidth, uiDrawHeight );
                        #endif
                    }
                    #ifdef ADJUST_SPACE_BETWEEN_FONT //denghg add for FONT_NOT_IN_RANGE and use OSD font 2006-9-25 14:16
                    else
                    {
                        ftGetDrawFontSize(&uiCurChar, &uiDrawWidth, &uiDrawHeight);
                        GetDrawFontBmp(&uiCurChar, &pBmp);
                        uiFONTRealWidth = Cnt_font_Realwidth(pBmp, uiDrawWidth, uiDrawHeight);  
                    }
                    #endif

                    #ifndef ADJUST_SPACE_BETWEEN_FONT     //DENGHG ADD 2006-1-6 06:04                         
                    uiLineLen += FONT_WIDTH_INTERNAL_OSD;
                    #else
                    uiLineLen += uiFONTRealWidth;
                 	#endif
                }
                else
                {
                   
                    #ifdef ADJUST_SPACE_BETWEEN_FONT //DENGHG ADD 2006-1-6 06:04     
		    	    ftGetDrawFontSize(pStr, &uiDrawWidth, &uiDrawHeight);
                    GetDrawFontBmp(pStr, &pBmp);		    
		    		uiFONTRealWidth = Cnt_font_Realwidth(pBmp, uiDrawWidth, uiDrawHeight);
		    	    if (uiLineLen + /*uiFONTRealWidth*/uiDrawWidth > uiRegionWidth) //denghg ADD uiFontWidth for  first font is eaten 2006-3-3 16:51
                    {
                        break;
                    }
                    uiLineLen += uiFONTRealWidth;
                    #else
                    if( uiLineLen + uiFontWidth > uiRegionWidth )
                        break;

                    uiLineLen += uiFontWidth;
                    #endif 
                   
                   
                }

                const UINT8* pTmpStr    = pStr;
                UINT16 uiTmpLineLen      = uiLineLen;
                
                aLineBuf[ uiWordCnt ] = uiCurChar;
                uiWordCnt++;
                pStr++;

                if( uiCurChar == ' ' )
                {
    			    do
    			    {
    			        pTmpStr++;
    			        #ifdef ADJUST_SPACE_BETWEEN_FONT //DENGHG 2006-1-6 06:05     
		    			langGetCharacterBmp( pTmpStr, &pBmp );
		    			uiFONTRealWidth = Cnt_font_Realwidth(pBmp,uiFontWidth, uiFontHeight);
		    			uiTmpLineLen += uiFONTRealWidth;    			        
    			        #else
    			        uiTmpLineLen += uiFontWidth;
    			        #endif
    			        
    			        if( uiTmpLineLen > uiRegionWidth  )
    			            goto PARSE_LINE_END;
    			        else if( ( *pTmpStr == ' ' ) || ( *pTmpStr == '\n' ) )
    			            break;
    			    }while( TRUE );			    
                }
            }
        }

PARSE_LINE_END:
       
        // count uiCurStrLen,'\r':when "return",'\n':next line is blank
        // '\n' just count uiCurStrLen not jump next line wangap add 2005/1/25
        if( (*pStr) == '\n' )
            pStr++;

        if( uiWordCnt > 0 )
        {
            aLineBuf[ uiWordCnt ] = '\0';
            
        	UINT32  uiStart_x = ( uiRegionWidth - uiLineLen ) >> 1;
            UINT32  uiStart_y = uiLineCnt * uiFontHeight;
            redirect_subtitle();    // 2005/09/28 yltseng
            
            #ifdef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-5-16 10:23(for show swith GUI no show MP4 subtitle).
            if(!(full_scrn & SW_MEDIA))
            #endif//DIRECT_ACCESS_MEDIA
            OSD_ShowString( uiStart_x, uiStart_y, aLineBuf, FONT_COLOR_INDEX, OSD_EXTERNAL_SUBTITLE_REGION );

            osd_tog_region( OSD_EXTERNAL_SUBTITLE_REGION, OSD_OFF );

            uiLineCnt++;
            if( uiLineCnt >= uiMaxLine )
                break;
        }        
    }
#if defined (SUPPORT_SMI_MultiLanguage)//libing 2006/3/16       
        nPara_num++;
    }
#endif    
    
    if( uiLineCnt > 0 )
    {
        coordinate coPos;
        if( osd_get_original_region_position( OSD_EXTERNAL_SUBTITLE_REGION, &coPos ) )
        {
        	#if defined(SDRAM_16Mb_Mode)&&defined(EX_SUP_IN_CHANGLESS_POSITION)  //zxb 2006-5-9 20:29 for 16m first line in one position
        	osd_set_region_position( OSD_EXTERNAL_SUBTITLE_REGION, coPos.x, coPos.y + ( uiRegionHeight - uiFontHeight ) / 2 );
        	#else
            osd_set_region_position( OSD_EXTERNAL_SUBTITLE_REGION, coPos.x, coPos.y + ( uiRegionHeight - uiLineCnt * uiFontHeight ) / 2 );
            #endif
            osd_tog_region( OSD_EXTERNAL_SUBTITLE_REGION, OSD_ON );
        }
    }
}

#else

/*
 *Function:display text to osd,display max line:7,display max chinese font in a line:19
 *Parameter:*p:input string
 *           Size:length of string
 *Return:none      
 *Creator:suqiaoli
 *Date:2004-3-17
 *Date:2004/09/06 yltseng modify
*/

#include "OSDShowFont.h"

#define MAX_WORD    50

#ifdef SDRAM_16Mb_Mode
    #define MAX_LINE    2
#else
    #define MAX_LINE	7
#endif

//All char will be put into this str array
//if string long,it will newline
BYTE str[MAX_LINE][MAX_WORD];

#if defined (SUPPORT_SMI_MultiLanguage)||defined(SUPPORT_SMI_MultiColor)//2005-8-16 20:38 zhoulin
extern int strncmpIgnoreCase(char *a,char *b,unsigned i);
extern UINT8  SmiSupType;
#endif

#if defined (SUPPORT_SMI_MultiLanguage)
extern BYTE nowSupLang;
extern BYTE lang_temp[][15];
extern BYTE lang_num;
#define MAX_Para   3
#endif

#if defined(SUPPORT_SMI_MultiColor)
extern BYTE color_temp[][20];
extern BYTE palette_color_num;
extern  int  read_color_index(BYTE **cbufptr);
BYTE chrclr[MAX_LINE][MAX_WORD];
#endif

void ShowOSDText(const char *p,  UINT16 size)
{
    UINT32 uStrStatus=0;
    // 2004/09/03 yltseng	
	BYTE*pStr = (BYTE *)p;
	BYTE c,c1;
	
	BYTE *old_pStr;
	int old_i_len;
	
	int  show_line = -1;
	int  show_word = 0;
	UINT16  nsize=0;
	int  i_len;
	int len[MAX_LINE];
	int i;
	int count=0;
    UINT16  msize;

    #if defined (SUPPORT_SMI_MultiLanguage)
	UINT8 Para_num=0;
	UINT8 nPara_num;
	UINT32 Para_addr[MAX_Para];
	UINT8  Para_size[MAX_Para];
	BYTE ParaCntFlg=0;	
    #endif

    #if defined(SUPPORT_SMI_MultiColor)
	BYTE*pStrb = NULL;
    BYTE clr_index=1;
    #endif

    #ifdef	SUPPORT_FONT_OUTLINE
    Mp4Subtitle_flag=1;
    #endif

	osd_tog_region( 3, OSD_ON );
	
    //suxin,2005-07-29,for support subtitle of TMPlayer(*.txt)
	for(i = 0;i<=(size+11);i++)
	{
		if((pStr[i] == ',')&&(pStr[i+1] == '2')&&(pStr[i+2] == '='))
		{	
			int j;
			UINT16 len2;
			
			len2 = size - i + 11;
			i = i-8;
			for(j = 0;j<=len2;j++)
			{
				pStr[i] = pStr[i+11];
				i++;
			}
			break;
		}
	}//for(i = 0;i<=(size+11);i++)

    #if defined (SUPPORT_SMI_MultiLanguage)//2005-8-16 20:38 zhoulin	
	if(SmiSupType)//process the multiparagraph
	{
	    while(nsize<size)
    	{
    		if(*pStr=='<'&&(*(pStr+1)=='P'||*(pStr+1)=='p'))
    		{  
    			if(ParaCntFlg)
			    {   
			       Para_size[Para_num]=count;
			       Para_num++;
		        }
		        
    			ParaCntFlg=0;
    			
    			if(lang_num>1)
	    		{
	    			while(*pStr!='='&&nsize<size)
	                {
	                   nsize++;
	                   pStr++;
	                }      			
	    		    nsize++;
	    		    pStr++;
	    		    if(strncmpIgnoreCase( pStr,lang_temp[nowSupLang], strlen((const char*)lang_temp[nowSupLang]) )==0)
	    		    {        		       
	    		       while(*pStr!='>')
	    		       {  nsize++;
	    		    	  pStr++;   		       	     		         
	    		       }  
	    		       nsize++;
	    		       pStr++;
	    		       Para_addr[Para_num]=(UINT32) pStr;
	    		       count=0;
	    		       ParaCntFlg=1;
	       		    }
    		    }
    		    else
    		    {
    		       while(*pStr!='>')
    		       {  nsize++;
    		    	  pStr++;   		       	     		         
    		       }  
    		       nsize++;
    		       pStr++;
    		       Para_addr[Para_num]=(UINT32) pStr;
    		       count=0;
    		       ParaCntFlg=1;    		    
    		    }
    		}
    	    
    	    nsize++;
    		pStr++;
       	    if(ParaCntFlg)
       	      count++;       	    
       	}
       	
	    if(ParaCntFlg) 
	    {   
	       Para_size[Para_num]=count;
	       Para_num++;
        }
	}

	if(!SmiSupType)
    {      
        Para_num=1;
    }
	nPara_num=0;
    #endif	
	
	//Read and parse each char,display them on osd
	//include function:display more lines,newline,
	//when string length>276,it will newline
    #if defined (SUPPORT_SMI_MultiLanguage)//2005-8-16 20:38 zhoulin
	while(nPara_num<Para_num)
	{   
		nsize=0;
		if(SmiSupType)
        {  
        	msize=Para_size[nPara_num];
            pStr=(BYTE *)Para_addr[nPara_num];
        }
		else
		{
			msize=size;  
			pStr = (BYTE *)p;	   
		
		}
    #else
    msize=size;
    #endif		
    
	while(nsize<msize)
	{
		show_word = 0;
		i_len = 0;
		count = 0;
		show_line++;
        if( show_line > MAX_LINE - 1 )//most displayed line is 7 line
        {
    #if defined (SUPPORT_SMI_MultiLanguage)//2005-8-16 20:38 zhoulin
	        break;
	#else
            show_line = MAX_LINE - 1;
            break;
	#endif
	            
        }
        
		//read string to string buffer,except "return","next line"
	    while(((*pStr) != '\n' && nsize < msize )/*&& ((*pStr)!='\n')*/ )    // 2005/07/15 yltseng
		{	
    #if defined(SUPPORT_SMI_MultiColor)//2005-8-16 20:38 zhoulin
				if(SmiSupType)	
				{	while(*pStr=='<')
				    {
				    	
				    	if(strncmpIgnoreCase(  pStr, "</font>", 7 )==0)
				        {
				        	pStr+=7;
				            nsize+=7;
				            clr_index=1;
				        }
				    	else if(strncmpIgnoreCase(  pStr, "<font", 5 )==0 )
				    	{			    	
				            pStr+=5;
				            nsize+=5;
				            while(*pStr!='>')
				            {   pStr++;
				                nsize++;
				            	
				            	if(*pStr=='C'||*pStr=='c')
	                            { 	
	                            	if(strncmpIgnoreCase(  pStr, "color", 5 )==0)		            
				                    {   
				                    	pStr+=5;
				                        nsize+=5;
				                        pStrb=pStr;
				                    	clr_index=read_color_index(&pStr);
				                        if(clr_index==0) 
				                            clr_index=1;
				                        nsize=nsize+pStr-pStrb;
				                    } 
				                   
				                }   
				            } 
				            pStr++;
				            nsize++;
				        }
				        else break;
				    
				   }
				
			 }
    #endif	
			c = *pStr;
			c1 = *(pStr + 1);
    
            UINT32 uiRtnVal = langIsInCharacterSet( pStr );

            if(c=='\r')//wangap add 2005/1/25 
            {          //if '\n' not jump next line just continue
                pStr++;
                nsize++;
                continue;
            }
           
            if( uiRtnVal == FONT_NOT_IN_RANGE )
            {
                if ((c >= 32) && (c <= 126))
                    uiRtnVal = FONT_ONE_BYTE;
            }

            if( uiRtnVal == FONT_TWO_BYTE )
			{
				str[show_line][show_word]=c;
				str[show_line][show_word+1]=c1;
				
    #if defined(SUPPORT_SMI_MultiColor)//2005-8-16 20:38 zhoulin
                chrclr[show_line][show_word]=clr_index;
                chrclr[show_line][show_word+1]=clr_index;
    #endif				
				show_word+= 2;
				i_len+= FONT_LEN_EXTERNAL_TWO_BYTE;
				nsize+= 2;
				pStr += 2;
				if((((i_len-count*9)%2==0)&&(i_len>275))||(((i_len-count*9)%2==0)&&(i_len>276)))
					break;
			}
			else if( uiRtnVal == FONT_ONE_BYTE )
            {
				old_pStr = pStr;
			    old_i_len = i_len;
				str[show_line][show_word]=c;
				
    #if defined(SUPPORT_SMI_MultiColor)//2005-8-16 20:38 zhoulin
                chrclr[show_line][show_word]=clr_index;
    #endif	
				show_word += 1;
				i_len += FONT_LEN_EXTERNAL_ONE_BYTE;//len
				nsize += 1;
				pStr += 1;
				
				if(c == 32) //not to cut off a long word,according to space's position
				{
    			    do
                    {   
                        if(*old_pStr!='\r')
                            old_i_len += FONT_LEN_EXTERNAL_ONE_BYTE;//len
                            
                        old_pStr ++;
                        
                        if((*old_pStr == 32)|| (*old_pStr == '\n')||(old_i_len > 276)
    #if defined(SUPPORT_SMI_MultiColor)//2005-8-16 20:38 zhoulin
                        ||(*old_pStr == '<')
    #endif
                        )
                            break;
    			    }while(1);
			    
    			    if (old_i_len > 276)
    			        break;
				}
				else
				{
				    count++;
				    if (i_len>276)
					    break;	
			    }
            }
            else
            {
                uStrStatus =1;
                c = '?';
				str[show_line][show_word]=c;
				
    #if defined(SUPPORT_SMI_MultiColor)//2005-8-16 20:38 zhoulin
                chrclr[show_line][show_word]=clr_index;
    #endif	
				show_word+= 1;
				nsize+= 1;
				i_len+= FONT_LEN_INTERNAL_OSD;
				pStr += 1;
				count++;
				if (i_len>276)
					break;
            }
       
		}//while(((*pStr) != '\r')&& ((*pStr)!='\n') )
		       
        if(((*pStr) == '\n')/*||((*pStr) == '\n')*/)//count nsize,'\r':when "return",'\n':next line is blank
        {                  //'\n' just count nsize not jump next line wangap add 2005/1/25
			pStr++;
			nsize++;
		}

		len[show_line]=i_len;
		
		str[show_line][show_word]='\0';
		
		if( show_word <= 0 )//if blank line,string line will skip
			show_line--;
	    } //while(nsize<msize)
        
    #if defined (SUPPORT_SMI_MultiLanguage)//2005-8-16 20:38 zhoulin       
        if( show_line > MAX_LINE - 1 )//most displayed line is 7 line
	    {
	        show_line = MAX_LINE - 1;
	        break;
	    }
        
        nPara_num++;
    }
    #endif

	int    width    = (int) region[3].osd_w;
	int    height   = (int) region[3].osd_h/MAX_LINE;
	int	   xstart;

    //This is only for Nero Digital Certification (Temp solution)
    #ifdef SUPPORT_QUICKTIME
    if (uStrStatus && (GET_FILE_TYPE()==FILE_TYPE_ND))
    {
        //printf("Skip SubTitle uStrStatus = %x \n", uStrStatus);
        return;
    }
    #endif //SUPPORT_QUICKTIME

    for( i = show_line; i >= 0; i-- )//display each line srt title
    {
    #ifdef SWITCH_SUB_DIRECTION//libing 2005-7-15 14:43
        if(subtitle_ratate_flag)
            xstart = width - ( width - len[i] ) / 2;
        else
    #endif
        
            xstart = ( width - len[i] ) / 2;

        int ystart = height * ( MAX_LINE - ( show_line - i ) - 1 );
        
    #if defined(SUPPORT_SMI_MultiColor)//2005-8-16 20:38 zhoulin 
        if(SmiSupType)
            OSD_ShowColorString( xstart, ystart, str[i],chrclr[i], 3 );
        else
            OSD_ShowString( xstart, ystart, str[i], 2, 3 );
    #else  
         OSD_ShowString( xstart, ystart, str[i], 2, 3 );
    #endif
    }
}

#endif

#endif // #if defined( OSD_FONT_API ) && defined( SUPPORT_OSDSRT )
