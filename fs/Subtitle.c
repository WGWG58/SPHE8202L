// 2005/09/22 yltseng, add support for unix format new line
#include "SET.H"
#include "user_init.h"

#ifdef SUPPORT_MP4_SUBTITLE

#include "Subtitle.h"
#include "navdata.h"
#include "avsync.h"
#include "memmap0.h"
#include "atapi_if.h"
#include "util.h"
#include "stc.h"
#include "avd.h"
#include "kinf.h"
#include "file_if.h"
#include "cardfs.h"
#ifdef SUPPORT_UNICODE_FONT //joshua 2005/9/2
#include "font_unicode.h"
#endif
#ifndef DVDRELEASE
#define SUBTITLE_DBG     1
#endif

#include "fs_new.h"

#ifdef SUBTITLE_DBG
    //#define DBG_SUBTITLE_BELONG_TO
    //#define DBG_KEYFRAME
    //#define DBG_FILL_SUBTITLE_BUFFER
    //#define DBG_GET_CURRENT_STR
    //#define DBG_PRINT_LOADED_BUFFER
#endif

#ifndef SUBTITLE_DBG
#undef printf
#undef print_block
#define printf(f, a...) do {} while (0)
#define print_block(x,y) do {} while (0)
#endif

#if defined (SUPPORT_SMI_MultiLanguage)||defined(SUPPORT_SMI_MultiColor)//2005-8-16 20:38 zhoulin
UINT8  SmiSupType; 
#endif

#ifdef  SUPPORT_SMI_MultiColor//2005-8-16 20:38 zhoulin
extern UINT32 palette_16color_MP4_SUB[16];
#define CLUTE_TRANS 0x80808000

typedef struct
{   UINT32         value;   
    BYTE           *name;
   
} color_value;

const color_value  color_mapping_table[]=//RGB
{ 
  {0x00FFFF,"aqua"},    {0x808080 ,"gray"}, 
  {0x000080,"navy"},    {0xC0C0C0 ,"silver"}, 
  {0x000000,"black"},   {0x008000,"green"}, 
  {0x808000,"olive"},   {0x008080,"teal"}, 
  {0x0000FF,"blue"},    {0x00FF00,"lime"}, 
  {0x800080,"purple"},  {0xFFFF00,"yellow"}, 
  {0xFF00FF,"fuchsia"}, {0x800000,"maroon"}, 
  {0xFF0000, "red"},    {0xFFFFFF,"white"}, 

};

#define  MAX_color_mapping_Nm   sizeof(color_mapping_table)/sizeof(color_value)
#define MAX_palette_colors 16
BYTE color_temp[MAX_palette_colors][20];
BYTE palette_color_num;

#endif//endif  SUPPORT_SMI_MultiColor



#ifdef SUPPORT_SMI_MultiLanguage//2005-8-16 20:38 zhoulin
#define MAX_langs  5
BYTE lang_temp[MAX_langs][15];
BYTE lang_num;
BYTE nowSupLang=0;

#endif

#ifdef SUBTITLE_SUPPORT_ALL_FORMAT
    #define SUBTITLE_SUPPORT_SRT
    #define SUBTITLE_SUPPORT_SUB_MICRODVD
    #define SUBTITLE_SUPPORT_SUB_SUBVIEWER
    #define SUBTITLE_SUPPORT_SSA
    #define SUBTITLE_SUPPORT_ASS
    #define SUBTITLE_SUPPORT_SMI
    #define SUBTITLE_SUPPORT_PSB
    #define SUBTITLE_SUPPORT_TXT
#elif defined( SUBTITLE_SUPPORT_COMMON_FORMAT )
    #define SUBTITLE_SUPPORT_SRT
    #define SUBTITLE_SUPPORT_SMI
#endif

#ifdef SUBTITLE_SUPPORT_TXT
    #define SUBTITLE_SUPPORT_SUB_SUBVIEWER
    #define SUBTITLE_SUPPORT_TMplayerTXT
#endif

// **************************************************************************************** //
extern FSJPEGDATA*  pFsJpeg;
extern BYTE         ran_read( UINT8 *ptr,UINT32 msf,UINT32 len );
extern void         DispCookOSD0(BYTE bChange);
extern void         ShowOSDText(const char *p,  UINT16 size);
extern void         set_sub_title_Ns(UINT8 Ns);
extern void         osd_ClearOneRegion(BYTE region, BYTE bkColor);//linrc 20050324
extern void         osd_init_OSDSRT(void);

// **************************************************************************************** //
enum INTERNAL_SUP_TYPE
{
    INTERNAL_SUBTITLE_UNKNOWN,
    INTERNAL_SUBTITLE_SRT,
    INTERNAL_SUBTITLE_SUB_MICRODVD,
    INTERNAL_SUBTITLE_SUB_SUBVIEWER,
    INTERNAL_SUBTITLE_SSA,
    INTERNAL_SUBTITLE_ASS,
    INTERNAL_SUBTITLE_SMI,
    INTERNAL_SUBTITLE_PSB,
    INTERNAL_SUBTITLE_TXT,
};

#define NUM_OF_BELONGTO   5
typedef struct
{
    UINT32          loc;
    UINT32          size;
    UINT16          uiBelongTo[NUM_OF_BELONGTO];
    UINT8           uiType;
} MP4_SUBTITLE;

typedef struct
{
    char            aName[128]; // file name( without extension )
    UINT16          uiIndex;    // Index to iso9660 DIR_REC( for video file ) or
                                // Index to subtitle_array( for subtitle file )
    UINT8           uiType;     // 0 for video file, 1 for subtitle file
} SUBTITLE_TEMP_DATA;

typedef struct 
{
    ifunc   pfnParsingSubtitleFunc;
    void    (*pfnGetSubtitleData)( UINT32, void**, UINT32* );
    char    aExtName[4];
    UINT8   uiExternalType;
    UINT8   uiInternalType;
} SUBTITLE_INFO_ENTRY;

// **************************************************************************************** //
#define VIDEO_SUBTITLE_OFFSET       ( _fs9660_buf + ( ( FS9660_SIZE - 1 ) << 10 ) ) // use last 1K size of file system structure
#define VIDEO_SUBTITLE_MAX          ( 1024 / sizeof(MP4_SUBTITLE) )
#define subtitle_array              ( (MP4_SUBTITLE *) VIDEO_SUBTITLE_OFFSET )

#define MATCHBUFSTART               ( SDRAM_BASE_UNCACHED + ( ( SSAVER_YA ) << 10 ) )//( SDRAM_BASE_UNCACHED + ( ( JPEG_YA ) << 10 ) )
#define MATCHBUFSIZE                ( ( SSAVER_PIC_SIZE ) << 10 )//( ( JPEG_CDBUF_SIZE ) << 10 )
#define MATCHBUFEND                 ( MATCHBUFSTART + MATCHBUFSIZE )

#define MS_STC_CLK                  (STC_CLK / 1000)
#define EXTSUPENTRYSIZE             4
#define SUBTITLE_RELOAD_LIMIT       2048    // must be mutiples of 1024

// avi_sup_state
#define EXT_SUP_RESET               0
#define EXT_SUP_INITIALIZED         (1<<0)
#define EXT_SUP_ACTIVATED           (1<<1)
#define EXT_SUP_INDISPLAY           (1<<2)
#define EXT_SUP_NEXTREADY           (1<<3)
#define EXT_SUP_NEEDDATA            (1<<4)

// **************************************************************************************** //
void   (*s_pfnGetSubtitleData)( UINT32, void**, UINT32* )   = NULL;
static ifunc   s_pfnParsingSubtitleFunc                     = NULL;
ifunc  g_pfnPollingSubtitle                                 = NULL;

static UINT32  s_uiSupState;
static UINT32  s_uiSupLen;
static UINT32  s_uiSupLba;
static UINT32  s_uiSupStart;
static UINT32  s_uiSupEnd;
static UINT32* s_pSupIdxPtr         = NULL;
static UINT32* s_pSupIdxEnd         = NULL;
static UINT32  s_uiSupType          = INTERNAL_SUBTITLE_UNKNOWN;

static UINT32* s_pSupIdxBasePtr     = NULL;
static UINT32* s_pSubIdxBaseEndPtr  = NULL;
static UINT32  s_uiSupIdxBaseSize   = 0;
static BYTE*   s_pSupBufPtr         = NULL;
static BYTE*   s_pSupBufEndPtr      = NULL;
static UINT32  s_uiSupBufSize       = 0;
static UINT16  s_uiSupCnt           = 0;
static void*   s_pPrevSup           = NULL;
BYTE  Is_Support_FormatS = 0; //lyc add for check if support subtitle format

// When Changing subtitle initiallization flowchart.
// we should parser two times and check s_supParseAgain.
//BYTE    s_supParseAgain      = 0;  //2006-02-14 mimitsai add for changing sub-title language bug.

// **************************************************************************************** //
extern void ACTIVATE_EXT_SUP()              { s_uiSupState |= EXT_SUP_ACTIVATED; }
extern void DISPLAY_EXT_SUP()               { s_uiSupState |= EXT_SUP_INDISPLAY; }
extern void DEACTIVATE_EXT_SUP()            { s_uiSupState &= (~EXT_SUP_ACTIVATED); }
extern void TURNOFF_EXT_SUP()               { s_uiSupState &= (~EXT_SUP_INDISPLAY); }

extern int  IS_EXT_SUP_INITIALIZED()        { return s_uiSupState & EXT_SUP_INITIALIZED; }
extern int  IS_EXT_SUP_ACTIVATED()          { return s_uiSupState & EXT_SUP_ACTIVATED; }
extern int  IS_EXT_SUP_INDISPLAY()          { return s_uiSupState & EXT_SUP_INDISPLAY; }
extern int  IS_EXT_SUP_NEEDDATA()           { return s_uiSupState & EXT_SUP_NEEDDATA; }

static inline void RESET_EXT_SUP()          { s_uiSupState = EXT_SUP_RESET; }
static inline void INITIALIZE_EXT_SUP()     { s_uiSupState |= EXT_SUP_INITIALIZED; }
static inline void NEEDDATA_EXT_SUP()       { s_uiSupState |= EXT_SUP_NEEDDATA; }
static inline void GOTDATA_EXT_SUP()        { s_uiSupState &= (~EXT_SUP_NEEDDATA); }

static inline int   supParseSubtitle( int iAVIFile, int iSubFile );
static inline int   supParseSubtitleEntry( int );

static inline int   supGetSubtitleCount( int iAVIFile );
static inline int   supGetNthSubtitle( int iAVIFile, int iSubFile );

static inline void  supSetSubtitleIdxBuffer( UINT32* pBufAddr, UINT32 uiSize );
static inline void  supSetSubtitleDataBuffer( BYTE* pBufAddr, UINT32 uiSize );

static void         supGetSubtitleDataTXT( UINT32 uiCurTime, void** pData, UINT32* pSize );
static UINT32       supFillBuffer( BYTE** ppCurrent, UINT32* pByteRead );

static inline int   supPollingSubtitleSRT();
static int          supReplaceSubString( char* pStr, int iSrcLen, const char* pStrSearch, const char* pStrReplace, int iMode );
static int          supReplacePropertyString( char* pStr, int iSrcLen, const char* pStrSearch );
#if defined (SUPPORT_SMI_MultiLanguage)||defined(SUPPORT_SMI_MultiColor)
static int  supReplacePropertyString_rt(char *pStr, int iSrcLen);
#endif
static inline void  supModifyString( char* pStr, int iCnt );

// **************************************************************************************** //
#ifdef SUBTITLE_SUPPORT_SRT
static int     ParsingSubtitleSRT();
#endif

#if defined( SUBTITLE_SUPPORT_SUB_MICRODVD ) || defined( SUBTITLE_SUPPORT_SUB_SUBVIEWER )
static int     ParsingSubtitleSUB();

    #ifdef SUBTITLE_SUPPORT_SUB_MICRODVD
static int     ParsingSubtitleSUB_MicroDVD();
    #endif

    #ifdef SUBTITLE_SUPPORT_SUB_SUBVIEWER
static int     ParsingSubtitleSUB_SubViewer();
    #endif
#endif

#ifdef SUBTITLE_SUPPORT_SSA
static int      ParsingSubtitleSSA();
#endif

#ifdef SUBTITLE_SUPPORT_ASS
static int      ParsingSubtitleASS();
#endif

#ifdef SUBTITLE_SUPPORT_SMI
static int      ParsingSubtitleSMI();
#endif

#ifdef SUBTITLE_SUPPORT_PSB
static int      ParsingSubtitlePSB();
#endif

#ifdef SUBTITLE_SUPPORT_TXT
static int      ParsingSubtitleTXT();
static int      ParsingSubtitleTXT_TXT();
static int      ParsingSubtitleTXT_TXT_OTHER();//denghg add for  some Polish format x:xx:xx:
static int      ParsingSubtitleTXT_TXT_Two_STimeData(); //lyc add 2006-3-15,for TCL more format .txt
static int      ParsingSubtitleTXT_TXT_Two_USTimeData(); //lyc add 2006-3-15,for TCL more format .txt
static int      ParsingSubtitleTXT_TXT_INTERFACE_TIME(); //lyc add 2006-3-15,an interface function for xx:xx:xx:/x:xx:xx:/xx:xx:xx:xx/ xx:xx:xx:xx aa xx:xx:xx:xx
    #ifdef SUBTITLE_SUPPORT_TMplayerTXT
    static int      ParsingSubtitleTmPlayerTXT();
    #endif
#endif

// **************************************************************************************** //
static SUBTITLE_INFO_ENTRY s_aSubtitleInfo[] =
{
    #ifdef SUBTITLE_SUPPORT_SRT
    { ParsingSubtitleSRT, supGetSubtitleDataTXT,   "SRT",  EXT_SUBTITLE_TXT,   INTERNAL_SUBTITLE_SRT },
    #endif

    #if defined( SUBTITLE_SUPPORT_SUB_MICRODVD ) || defined( SUBTITLE_SUPPORT_SUB_SUBVIEWER )
    { ParsingSubtitleSUB, supGetSubtitleDataTXT,   "SUB",  EXT_SUBTITLE_TXT,   INTERNAL_SUBTITLE_SUB_MICRODVD },
    #endif

    #ifdef SUBTITLE_SUPPORT_SSA
    { ParsingSubtitleSSA, supGetSubtitleDataTXT,   "SSA",  EXT_SUBTITLE_TXT,   INTERNAL_SUBTITLE_SSA },
    #endif

    #ifdef SUBTITLE_SUPPORT_ASS
    { ParsingSubtitleASS, supGetSubtitleDataTXT,   "ASS",  EXT_SUBTITLE_TXT,   INTERNAL_SUBTITLE_ASS },
    #endif

    #ifdef SUBTITLE_SUPPORT_SMI
    { ParsingSubtitleSMI, supGetSubtitleDataTXT,   "SMI",  EXT_SUBTITLE_TXT,   INTERNAL_SUBTITLE_SMI },
    #endif

    #ifdef SUBTITLE_SUPPORT_PSB
    { ParsingSubtitlePSB, supGetSubtitleDataTXT,   "PSB",  EXT_SUBTITLE_TXT,   INTERNAL_SUBTITLE_PSB },
    #endif

    #ifdef SUBTITLE_SUPPORT_TXT
    { ParsingSubtitleTXT, supGetSubtitleDataTXT,   "TXT",  EXT_SUBTITLE_TXT,   INTERNAL_SUBTITLE_TXT },
    #endif
};

//#define Support_SubExName_Changed
#ifdef Support_SubExName_Changed  //lyc add-2006-2-20
int supGetOtherFormat()
{
      int i = 0;	
      int iResult = 0; 
      int InfoSize = sizeof( s_aSubtitleInfo ) / sizeof( SUBTITLE_INFO_ENTRY );    
      
      for( ; i <InfoSize; i++ )
        {
            s_pfnParsingSubtitleFunc = s_aSubtitleInfo[ i ].pfnParsingSubtitleFunc;   
            iResult = s_pfnParsingSubtitleFunc(); 
            if((iResult == 1)&&(s_pSupIdxEnd>=s_pSupIdxPtr+EXTSUPENTRYSIZE))  //lyc add 2006-3-10,idx table not empty 
                break; 
        } 
    #ifdef DBG_KEYFRAME    
      printf("===Wrong Sub ExName !!, Now changed to Idx %d==\n",i);     
    #endif
        return iResult; 
}      
#endif
//*********************************************************************************************//
#define _isascii(c)     ( ((c) >= 0x00) && ((c) <= 0x7F) )
#define _iscntrl(c)     ( ( ((c) >= 0x00) && ((c) <= 0x1F) ) || ((c) == 0x7F) )
#define _isprint(c)     ( ((c) >= 0x20) && ((c) <= 0x7E) )
#define _isspace(c)     ( ( ((c) >= 0x09) && ((c) <= 0x0D) ) || ((c) == 0x20) )

#define _islower(c)     ( ((c) >= 'a') && ((c) <= 'z') )
#define _isupper(c)     ( ((c) >= 'A') && ((c) <= 'Z') )
#define _isalpha(c)     ( _isupper() || _islower() )

#define _isdigit(c)     ( ((c) >= '0') && ((c) <= '9') )
#define _isxdigit(c)    ( ( ((c) >= 'A') && ((c) <= 'F') ) || ( ((c) >= 'a') && ((c) <= 'f') ) || _isdigit() )

#define _isalnum(c)     ( _isalpha(c) || _isdigit(c) )

//lyc add  2005-12-29,for SUBT FILE eol flag not "0D0A" but null
//denghg modify for || TO &&.if it is unix tail,last word will be eaten!!
#define _iseol_null(p)  (( *((UINT8*)(p)) == 0x00 ) && ( *((UINT8*)(p+1)) == 0x00 ))
#define _iseol_unix(p)  ( *((UINT8*)(p)) == 0x0A )
#define _iseol_win(p)   ( ( *((UINT8*)(p)) == 0x0D ) && ( *(((UINT8*)(p))+1) == 0x0A ) )
#define _iseol(p)       ( _iseol_unix(p) || _iseol_win(p) || _iseol_null(p))

//*********************************************************************************************//
// mimitsai move from avi_if.c 
// FUNCTION
// supInitSubtitleParam()
//
// DESCRIPTION
// init Subtitle related parameters, variables
void supInitSubtitleParam()
{
    file_extsub_buf         = AVISUPBUF_START;
    file_extsub_bufend      = AVISUPBUF_END;
    file_extsub_bufsize     = AVISUPBUF_SIZE;
    file_extsub_idx_buf     = AVISUPIDX_START;
    file_extsub_idx_bufend  = AVISUPIDX_END;
    file_extsub_idx_bufsize = AVISUPIDX_SIZE;
}

//*********************************************************************************************//

//compare two strings ,ignore uppercase and lowercase 
extern int strncmpIgnoreCase(char *a,char *b,unsigned i)
{   unsigned j;
    char c[i],d[i];
    
    for(j=0;j<i;j++)
    {
         if(a[j]>='a'&&a[j]<='z')    
          c[j]=a[j]-0x20;
         else c[j]=a[j];
         
         if(b[j]>='a'&&b[j]<='z')    
          d[j]=b[j]-0x20;
         else d[j]=b[j];
   
    } 
    return strncmp( (const char*) c,(const char*)d , i );
}
//********************************************************************************************//
#ifdef SUPPORT_SMI_MultiLanguage//2005-8-16 20:38 zhoulin

static int read_lang_info(BYTE **cbufptr)
{   
    BYTE *pbufptr;
    UINT8 cnt=0;
    BYTE langbuf[15];
    pbufptr=*cbufptr;
    
    while(!(*pbufptr==' '||*pbufptr==0x7D))
    {   langbuf[cnt]=*pbufptr;
        cnt++;
        pbufptr++;
        if(cnt>=15)  //exit,if the string >=20
          return 0;
    }
    langbuf[cnt]='\0';
    
    
    if(lang_num<MAX_langs)
    { 
         strcpy(lang_temp[lang_num],(const char*)langbuf);
         lang_num++;
    }
    
    
    *cbufptr=pbufptr;
    return 1;
}

#endif
//*****************************************************************************************//
#ifdef  SUPPORT_SMI_MultiColor//2005-8-16 20:38 zhoulin
UINT32 transRGB2GBRA(UINT32 clrvalue)
{
    return ((clrvalue<<16)&0xffff0000)|((clrvalue>>8)&0x0000ff00)|0x000000ff;
}

//read the color
//input:mode=1 for reading default color
//      mode=0 for reading the color in the main body
//return:1  success
//       0  false

extern  int  read_color(BYTE **cbufptr,BYTE mode)
{   
    BYTE *pbufptr;
    UINT8 cnt=0;
    UINT8  num_letter=0;
    UINT8  num_num;
    UINT8  clrmatch=0;
    BYTE clrbuf[20];
    UINT32 clrvalue=0;
    pbufptr=*cbufptr;
    BYTE clr_identFlg=0;
    
    //check the first number or letter(0-9 or a-z or A-Z)
    while(!((*pbufptr>='0'&&*pbufptr<='9')||(*pbufptr>='a'&&*pbufptr<='z')||(*pbufptr>='A'&&*pbufptr<='Z')))
    {   
        pbufptr++;
        cnt++;
        if(cnt>10)    //exit ，if no number or letter in 10 characters
          return 0;
      
    }
    cnt=0;
   
    //get the real string of string ;end with the first non-number or non-letter char
    while((*pbufptr>='0'&&*pbufptr<='9')||(*pbufptr>='a'&&*pbufptr<='z')||(*pbufptr>='A'&&*pbufptr<='Z'))
    {   if(*pbufptr>='A'&&*pbufptr<='Z')// uppercase to lowercase
            clrbuf[cnt]=*pbufptr+0x20;
        else  clrbuf[cnt]=*pbufptr;
        if(clrbuf[cnt]>'f'&&clrbuf[cnt]<='z') // have one char(f-z) indicate that string is color name ,not RGB value
          num_letter=1;
        cnt++;
        pbufptr++;  
        if(cnt>=20)  //exit,if the string >=20
          return 0;
    }
    
    clrbuf[cnt]='\0';
    num_num=strlen((const char*)clrbuf);
    UINT8  k;
    if( num_letter==0)  //if the string indicate RGB value,transform the string to value 
    {  
        if(num_num<=6)
        {
            for(cnt=0;cnt<num_num;cnt++)
            {  if(clrbuf[cnt]>='0'&&clrbuf[cnt]<='9')
                     k=clrbuf[cnt]-0x30;
               else  k=clrbuf[cnt]-0x61+10;      
               clrvalue=clrvalue*16+k;
            }
            clrmatch=1;
        }
    }  
    else       //if the string indicate color name,get value from the color table defined 
    {
        for(cnt=0;cnt<MAX_color_mapping_Nm;cnt++)
        {
            if(strncmpIgnoreCase(color_mapping_table[cnt].name,clrbuf,num_num)==0)
             {   clrvalue=color_mapping_table[cnt].value;
                 clrmatch=1;
                 break;     
             }
        }
    }
    if(clrmatch==0)//if the string  match neither RGB value type nor color name type,return
        return 0;
    
    if(mode)  //for default color 
    {     
           strcpy(color_temp[1],(const char*)clrbuf);
           palette_16color_MP4_SUB[1]=transRGB2GBRA(clrvalue) ;
        }
    else  //other color
    {   
           if(palette_color_num<MAX_palette_colors)
            {   for(cnt=1;cnt<palette_color_num;cnt++)
                {  if(strncmpIgnoreCase( color_temp[cnt], clrbuf,num_num)==0)
                       clr_identFlg=1;     
                }
                if(!clr_identFlg)
                {   strcpy(color_temp[palette_color_num],(const char*)clrbuf);
                    palette_16color_MP4_SUB[palette_color_num]=transRGB2GBRA(clrvalue) ;
                    palette_color_num++;
                }
            }     
    
    }
    
    
    *cbufptr=pbufptr;
    return 1;
}    

//get the index num in the palette ,return the index
//return=0,read color info error 
extern  int  read_color_index(BYTE **cbufptr)
{   
    BYTE *pbufptr;
    UINT8 cnt=0;
    UINT8  num_letter=0;
    UINT8  num_num;
    BYTE clrbuf[20];
    pbufptr=*cbufptr;
    
    //check the first number or letter(0-9 or a-z or A-Z)
    while(!((*pbufptr>='0'&&*pbufptr<='9')||(*pbufptr>='a'&&*pbufptr<='z')||(*pbufptr>='A'&&*pbufptr<='Z')))
    {   
        pbufptr++;
        cnt++;
        if(cnt>10)    //exit ，if no number or letter in 10 characters
          return 0;
      
    }
    cnt=0;
   
    //get the real string of string ;end with the first non-number or non-letter char
    while((*pbufptr>='0'&&*pbufptr<='9')||(*pbufptr>='a'&&*pbufptr<='z')||(*pbufptr>='A'&&*pbufptr<='Z'))
    {   if(*pbufptr>='A'&&*pbufptr<='Z')// uppercase to lowercase
            clrbuf[cnt]=*pbufptr+0x20;
        else  clrbuf[cnt]=*pbufptr;
        
        if(clrbuf[cnt]>'f'&&clrbuf[cnt]<='z') // have one char(f-z) indicate that string is color name ,not RGB value
          num_letter=1;
        cnt++;
        pbufptr++;  
        if(cnt>=20)  //exit,if the string >=20
          return 0;
    }
    
    clrbuf[cnt]='\0';
 
    num_num=strlen((const char*)clrbuf);
 
    
    for(cnt=1;cnt<palette_color_num;cnt++)
    {
        if(strncmpIgnoreCase( color_temp[cnt], clrbuf,num_num)==0)
        {    
            *cbufptr=pbufptr;
            return cnt;  //return the color palette index
        }
    }
        
    
    *cbufptr=pbufptr;
    return 1;//if the color is not in the palette,use thr default color
}

#endif
// **************************************************************************************** //
static inline int supGetSubtitleCount( int iAVIFile )
{
    if( iAVIFile < 0 )
        return 0;

    int i                   = 0;
    int j                   = 0;
    int iSubCntOfCurFile    = 0;

    for( ; i < s_uiSupCnt; i++ )
    {
        for(j = 0; j < NUM_OF_BELONGTO; j++)
        {
            if( subtitle_array[i].uiBelongTo[j] == iAVIFile )
            //if( subtitle_array[i].uiBelongTo == iAVIFile )
            iSubCntOfCurFile++;
    }
    }
    return iSubCntOfCurFile;
}

// **************************************************************************************** //
extern int supInitSubtitle()
{
    // use the internal subpicture of AVI first
    
    if( FILE_HAS_SUPIC() )
    {
        g_pfnPollingSubtitle = NULL;
		#ifndef TOUCH_KEYBOARD//frank.huang 050926 add to make keyboard display when play cdrom
        osd_tog_region( 3, OSD_OFF );
		#endif
        return FALSE;
    }
    
    int iCurFile = pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry;
    
    #ifdef PMP_UI  //////////////yangli add for PMP_UI with subtitle 20050517 //kenny 2005/9/5 modify
    iCurFile = CurrentFiles1[pFsJpeg->file_index_in_dir]+pFsJpeg->first_mp3_entry;
    #endif
    
    set_sub_title_Ns( supGetSubtitleCount( iCurFile ) );

    supSetSubtitleDataBuffer( (BYTE*) file_extsub_buf, file_extsub_bufsize );
    supSetSubtitleIdxBuffer( (UINT32*) file_extsub_idx_buf, file_extsub_idx_bufsize );

    if( supSetSubtitleStream( 0 ) )
    {
        NP_SPSTN = 0x40 | 0;
        return TRUE;
    }

    NP_SPSTN = 0xffbf;
    return FALSE;
}

extern int supSetSubtitleStream( UINT32 uiStream )
{
    if( uiStream >= pDSV->dAv_SPST_Ns )
    {
        g_pfnPollingSubtitle = NULL;
       	#ifndef TOUCH_KEYBOARD//frank.huang 050926 add to make keyboard display when play cdrom
        osd_tog_region( 3, OSD_OFF );
		#endif
        return 0;
    }

#ifdef DVD_SERVO        // 2005/04/30 yltseng
    extern UINT8 cServoWrongDataPass;
    cServoWrongDataPass = 0;
#endif
    #ifdef PMP_UI  //////////////yangli add for PMP_UI with subtitle 20050517
    pFsJpeg->fsnav_trk_now = CurrentFiles1[pFsJpeg->file_index_in_dir];
    #endif
    int iCurFile    = pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry;
    int iType       = supParseSubtitle( iCurFile, uiStream );

#ifdef DVD_SERVO
    cServoWrongDataPass = 1;
#endif

    switch( iType )
    {
    case EXT_SUBTITLE_TXT:
        g_pfnPollingSubtitle    = supPollingSubtitleSRT;
        s_pPrevSup              = NULL;

        if((!IS_EXT_SUP_ACTIVATED()))
        {
        osd_init_OSDSRT();
        }
        DispCookOSD0(1);    //joshua, 2005.6.9, for refreshing all display bar

        return 1;
        break;

//    case EXT_SUBTITLE_IMG:  // unsupport now
//        break;

    case EXT_SUBTITLE_UNKNOWN:
    default:
        g_pfnPollingSubtitle    = NULL;
        s_pPrevSup              = NULL;
        osd_tog_region( 3, OSD_OFF );
        return 0;
        break;
    }

    return 0;
}

#include "fsNav.h"
static inline int supPollingSubtitleSRT()
{

    UINT32  stc_in;
    void*   pData   = NULL;
    UINT32  uiSize  = 0;

    if( IsAVDMediaTimeout() )
    {
        osd_tog_region( 3, OSD_OFF );
        TURNOFF_EXT_SUP();
        return 0;
    }

	if(!is_stc_valid() || (pFsJpeg->gifsFuncBtn == FS_FUNC_MP3))
        stc_in  = disp_time*90000;
    else
        stc_in  = get_stc_32();

    //printf_w("get_stc_32():%d\n",get_stc_32()); 

    s_pfnGetSubtitleData( stc_in, &pData, &uiSize );

    if( pData != s_pPrevSup )
    {
        if( pData )
        {
            osd_ClearOneRegion( 3, 0 );
            
            #ifdef SUPPORT_UNICODE_FONT//2005/9/2

               show_osd_uni_text((char*) pData, uiSize);                
            #else
            ShowOSDText( (char*) pData, uiSize );
            #endif
            
            osd_tog_region( 3, OSD_ON );
            DISPLAY_EXT_SUP();
        }
        else
        {
            osd_tog_region( 3, OSD_OFF );
            TURNOFF_EXT_SUP();
        }

        s_pPrevSup = pData;
    }

    return 1;
}

// **************************************************************************************** //
extern void supClearSubtitle()      //liumzhi 20041204  // 2005/07/12 yltseng
{
    RESET_EXT_SUP();
    g_pfnPollingSubtitle    = NULL;
    s_pPrevSup              = NULL;
// When Changing subtitle initiallization flowchart.
// we should parser two times and check s_supParseAgain.
    //s_supParseAgain         = 0;
}
// **************************************************************************************** //
extern void supOpenSubtitle()       //caoh 2005-7-18 20:41
{
	//supInitSubtitle();		//yaowh add 2005-12-5 10:00
    g_pfnPollingSubtitle    = supPollingSubtitleSRT;
	s_pPrevSup              = NULL;
	ACTIVATE_EXT_SUP();
	osd_init_OSDSRT();
	DispCookOSD0(1);    //joshua, 2005.6.9, for refreshing all display bar
}
// **************************************************************************************** //
static inline void supSetSubtitleDataBuffer( BYTE* pBufAddr, UINT32 uiSize )
{
    s_pSupBufPtr        = pBufAddr;
    //yltseng 2005/07/20 the size of subtitle should be 2k aligned, 
    //otherwise it would be a little hard to handle buffer control.
    s_uiSupBufSize      = (uiSize & ~0x01) << 10;
    s_pSupBufEndPtr     = pBufAddr + s_uiSupBufSize;
}

// **************************************************************************************** //
static inline void supSetSubtitleIdxBuffer( UINT32* pBufAddr, UINT32 uiSize )
{
    s_pSupIdxBasePtr    = pBufAddr;
    s_uiSupIdxBaseSize  = uiSize << 10;
    s_pSubIdxBaseEndPtr = (UINT32*)( (UINT8*)pBufAddr + s_uiSupIdxBaseSize );   // 2004/01/27 yltseng
}

// **************************************************************************************** //
static UINT32 supFillBuffer( BYTE** ppCurrent, UINT32* pByteRead )
{
    if( !ppCurrent || !pByteRead || ( s_uiSupLen <= *pByteRead ) )
        return FALSE;
        
    BYTE*   pCurrent    = *ppCurrent;   
    UINT32  uiOffset    = SUBTITLE_RELOAD_LIMIT - ( s_pSupBufEndPtr - pCurrent );
    UINT32  uiReadCount = ( s_uiSupLen - *pByteRead ) > ( s_uiSupBufSize - SUBTITLE_RELOAD_LIMIT ) ? 
                          ( s_uiSupBufSize - SUBTITLE_RELOAD_LIMIT ) : ( s_uiSupLen - *pByteRead );
        
    *ppCurrent = (BYTE*)( s_pSupBufPtr + uiOffset );
    memcpy( *ppCurrent, pCurrent, s_pSupBufEndPtr - pCurrent );

    FS_SetOutOfFileReading();
#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)//2005-8-24 17:23 zhoulin  
    if( ran_read( (BYTE*)( s_pSupBufPtr + SUBTITLE_RELOAD_LIMIT ), l2msf( s_uiSupLba + ( (*pByteRead) >> ((media_type == MEDIA_CARD)?9:11) ) ), uiReadCount  ) != ATAPI_OK )
#else
    if( ran_read( (BYTE*)( s_pSupBufPtr + SUBTITLE_RELOAD_LIMIT ), l2msf( s_uiSupLba + ( (*pByteRead) >> 11 ) ), uiReadCount  ) != ATAPI_OK )
#endif
    {
        printf( "supFillBuffer fail! can't read file\n" );
        return FALSE;
    }
    FS_ResetOutOfFileReading();
#ifdef DBG_PRINT_LOADED_BUFFER
    print_block( (BYTE*)( s_pSupBufPtr + SUBTITLE_RELOAD_LIMIT ), 16 );
#endif    
    (*pByteRead) += uiReadCount;
    return TRUE;
}

// **************************************************************************************** //
extern int supAddSubtitleFileInfo( UINT32 uiLoc, UINT32 uiSize, const char* pFileName )
{
    if( !pFsJpeg || !pFileName )
        return 0;

    if( s_uiSupCnt < VIDEO_SUBTITLE_MAX )
    {                
        int iInfoSize = sizeof( s_aSubtitleInfo ) / sizeof( SUBTITLE_INFO_ENTRY );
        int i = 0;

        for( ; i < iInfoSize; i++ )
        {
            #ifdef SUPPORT_NATIVE_FSNAME //DENGHG don't conver file name to uppercase 2006-6-9 19:03
            char* tmpPfileName = (BYTE*)(((BYTE*)pFsJpeg) + sizeof(FSJPEGDATA));
            strcpy(tmpPfileName,pFileName); 
            ConvertLowerCaseToUpperCase( tmpPfileName );            
            if( FindFileExt( tmpPfileName, s_aSubtitleInfo[i].aExtName ) )
            #else
            if( FindFileExt( pFileName, s_aSubtitleInfo[i].aExtName ) )
            #endif
            {    
                break;
        	}
        }

        if( i == iInfoSize )
            return 0;

        subtitle_array[ s_uiSupCnt ].uiType    = i;
        subtitle_array[ s_uiSupCnt ].loc       = msf2l( uiLoc );
        subtitle_array[ s_uiSupCnt ].size      = uiSize;

        supAddVideoFileInfo( s_uiSupCnt, 1, pFileName );
        s_uiSupCnt++;
        
        return 1;
    }

    return 0;
}

// **************************************************************************************** //
extern void supRunSubtitleMatch()
{
    SUBTITLE_TEMP_DATA* pSupBase    = (SUBTITLE_TEMP_DATA*) MATCHBUFSTART;
    SUBTITLE_TEMP_DATA* pSupEnd     = (SUBTITLE_TEMP_DATA*) s_pSupBufPtr;

    SUBTITLE_TEMP_DATA *pOutter, *pInner;
    UINT8 i, belongIdx=0;
   
#ifdef DBG_SUBTITLE_BELONG_TO
    for( pOutter = pSupBase; pOutter < pSupEnd; pOutter++ )
        printf( "type = %d, idx = %d, name = %s\n", pOutter->uiType, pOutter->uiIndex, pOutter->aName );
#endif

    for( pOutter = pSupBase; pOutter < pSupEnd; pOutter++ )
    {
        if( pOutter->uiType == 1 )  // subtitle file
        {
            for(i = 0; i < NUM_OF_BELONGTO; i++)
                subtitle_array[ pOutter->uiIndex ].uiBelongTo[i] = 0xffff;
                //subtitle_array[ pOutter->uiIndex ].uiBelongTo = 0xffff;

            for( pInner = pSupBase; pInner < pSupEnd; pInner++ )
            {
                if( pInner->uiType == 0 )   // video file
                {
                  #ifdef ORITRON_HK_DVD //qinhua,2006-2-20 19:54
                    if((strncmpIgnoreCase( pOutter->aName, pInner->aName, strlen( pInner->aName ))==0)
                    &&(strncmpIgnoreCase(  pInner->aName, pOutter->aName, strlen( pOutter->aName))==0) )
                   #else//#ifdef ORITRON_HK_DVD //qinhua,2006-2-20 19:54
                    if( (strinstr( pOutter->aName, pInner->aName, strlen( pOutter->aName )))
                        ||(strinstr(  pInner->aName, pOutter->aName, strlen( pInner->aName ))) 
                        #ifdef THAKRAL_DVD//liweihua add for THAKRAL DVD 2005-3-11 9:45
                        //for sometime the mp4 file and its subtitle file have different file name
                        ||(GetMatchCharacterCount(pOutter->aName, pInner->aName) >= 8)
                        #endif
                        )
                    #endif//#ifdef ORITRON_HK_DVD //qinhua,2006-2-20 19:54
                    {
#ifdef DBG_SUBTITLE_BELONG_TO
                        printf( "avi = %s, sup = %s\n", pInner->aName, pOutter->aName );
#endif
                        subtitle_array[ pOutter->uiIndex ].uiBelongTo[belongIdx] = pInner->uiIndex;
                        //subtitle_array[ pOutter->uiIndex ].uiBelongTo = pInner->uiIndex;
                        //printf_w( "subtitle_array[%d].uiBelongTo[%d] = %d\n\n", pOutter->uiIndex, belongIdx, pInner->uiIndex);
                        belongIdx ++;
                        if(belongIdx >= NUM_OF_BELONGTO)
                        break;
                    }
                }   // if video
            }   // for pInner
        }   // if subtitle            
        belongIdx = 0;
        
    }   // for pOutter
}

// **************************************************************************************** //
static inline int supGetNthSubtitle( int iAVIFile, int iSubFile )
{
    if( iAVIFile < 0 )
        return 0;

    int i,j;
    int iSubCntOfCurFile    = 0;

    for( i = 0; i < s_uiSupCnt; i++ )
    {
        for(j=0;j<NUM_OF_BELONGTO;j++)
        {
            if( subtitle_array[i].uiBelongTo[j] == iAVIFile )
        {
            if( iSubCntOfCurFile == iSubFile )
                return i;

            iSubCntOfCurFile++;
        }
    }
    }

    return -1;
}

// **************************************************************************************** //
static inline int supParseSubtitleEntry( int iSubFileIdx )
{
    if( iSubFileIdx < 0 || iSubFileIdx >= s_uiSupCnt )
        return FALSE;
    
    s_uiSupLba      = subtitle_array[ iSubFileIdx ].loc;
    s_uiSupLen      = subtitle_array[ iSubFileIdx ].size;
    s_uiSupStart    = 0;
    s_uiSupEnd      = 0;
    BYTE*   bufptr  = s_pSupBufPtr;

    FS_SetOutOfFileReading();
    /* ----------------------------------------------------------
    New FS -- Simon 2006.3.3
    ---------------------------------------------------------- */
#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
    subStLBA = s_uiSupLba;
    
    if (media_type == MEDIA_CARD)
    {
        fs_file_close(pSubFile);
        fs_file_open2(pReadDrive, pSubFile, FSLBA2Clus(subStLBA), s_uiSupLen);
    }
#endif
    /* ----------------------------------------------------------
    End of New FS
    ---------------------------------------------------------- */
    if( ran_read( bufptr, l2msf( s_uiSupLba ), s_uiSupLen > s_uiSupBufSize ? s_uiSupBufSize : s_uiSupLen ) != ATAPI_OK )
    {
        printf("subtitle load fail! can't read file\n");
        return FALSE;
    }
#if 0//def ALCO_DIVX_UI//shenyj add for alco 2006/03/13 ,lyc mark it
if(strcmp(s_aSubtitleInfo[0].aExtName,"SRT") == 0)
{
    while( _isspace( *bufptr ) )
    bufptr++;
    if(*bufptr == 123)
    s_pfnParsingSubtitleFunc = ParsingSubtitleSUB;
}
#endif   
    FS_ResetOutOfFileReading();
    #ifdef SUPPORT_SMI_MultiLanguage//2005-8-16 20:38 zhoulin
    lang_num=0;
    #endif
    
    if(((s_pfnParsingSubtitleFunc())&&(s_pSupIdxEnd>=s_pSupIdxPtr+EXTSUPENTRYSIZE)) //lyc add 2006-3-10,idx table not empty ,do by the default format 
    #ifdef Support_SubExName_Changed
     ||(supGetOtherFormat())  //otherwise try other format do
    #endif
    ) 
    {
        // preload subtitle into buffer
        UINT32 len = s_uiSupLen;
        if( len > s_uiSupBufSize )
            len = s_uiSupBufSize;

        FS_SetOutOfFileReading();
        if( ran_read( s_pSupBufPtr, l2msf(s_uiSupLba), len ) != ATAPI_OK )
        {
            printf("external subtitle read error!!\n");
            RESET_EXT_SUP();
            return FALSE;
        }
        FS_ResetOutOfFileReading();
        s_uiSupEnd      = len;
        return TRUE;
    }
    #ifdef SHOW_UNSUPPORTED_SUBTITLE//zxb 2006-5-12 16:51
   	else if(disp_time > 0)    
   	{              
    	psprintf(RegionValStr[1], ":[UNSUPPORTED]");
    	PrintOsdMsg(109, 1, 1, 1);	
    }           
    #else
    else
      Is_Support_FormatS=1; //lyc add for check if support subtitle format
    #endif
    return FALSE;
}

// **************************************************************************************** //
#ifdef SUBTITLE_SUPPORT_SRT
static int ParsingSubtitleSRT()
{
    BYTE    tbuf[12];
    UINT32  spnum, bcnt;
    UINT32  hr, min, sec, ms;
    UINT32  sttime, endtime;
    
    UINT32  uiByteRead  = s_uiSupBufSize;
    UINT32  uiOffset    = 0;
    BYTE*   base        = s_pSupBufPtr;
    BYTE*   bufend      = s_pSupBufEndPtr;
    BYTE*   bufptr      = base;
    BYTE*   suptr       = NULL;
    UINT32* idxptr      = s_pSupIdxBasePtr;

    // parse subpicture
    do
    {
        if(( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT)&&(s_uiSupLen>s_uiSupBufSize)) //lyc update 2006-8-9;only fileszie>supbufsize,do supFillBuffer
        {            
            if( !supFillBuffer( &bufptr, &uiByteRead ) )
                break;

            uiOffset += ( s_uiSupBufSize - SUBTITLE_RELOAD_LIMIT );
        }
            
        while ( !_isdigit( *bufptr ) )
            bufptr++;

        if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )
            break;
        
        // get subpicture number
        spnum = 0;
        while ( _isdigit( *bufptr ) )
            spnum = (spnum*10) + (*bufptr++ - '0');
      
        // error check omitted, should be "0x0D 0x0A" or "0x20"
        while ( _isspace(*bufptr) )
            bufptr++;

        // get start time, xx:xx:xx,xxx format, 12 bytes
        memcpy(tbuf, bufptr, 12);
        bufptr += 12;
#if 0//liumzh 2005-9-19 16:28 , for both xx:xx:xx,xxx format &  x: x: x,  x format
        hr  = ((tbuf[0]-'0') * 10) + (tbuf[1]-'0');
        min = ((tbuf[3]-'0') * 10) + (tbuf[4]-'0');
        sec = ((tbuf[6]-'0') * 10) + (tbuf[7]-'0');
        ms  = ((tbuf[9]-'0') * 100) + ((tbuf[10]-'0') * 10) + (tbuf[11]-'0');
#else
        #define IsDigitTime( chr )      ( chr >= '0' && chr <= '6' )
        hr =  ((IsDigitTime(tbuf[0]))?((tbuf[0]-'0') * 10) : 0) + (tbuf[1]-'0');
        min = ((IsDigitTime(tbuf[3]))?((tbuf[3]-'0') * 10) : 0) + (tbuf[4]-'0');
        sec = ((IsDigitTime(tbuf[6]))?((tbuf[6]-'0') * 10) : 0) + (tbuf[7]-'0');
        ms  = 0; //((IsDigit(tbuf[9]))?((tbuf[9]-'0') * 100) : 0) + ((IsDigit(tbuf[10]))?((tbuf[10]-'0') * 10) : 0) + (tbuf[11]-'0');
        #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
            if( (!_isdigit(tbuf[1]))||(!_isdigit(tbuf[4]))||(!_isdigit(tbuf[7])) )
               goto Change_To_Next_SubT;
       #endif  
#endif
        sttime = (hr*3600 + min*60 + sec) * STC_CLK + ms * MS_STC_CLK;

        // drop seperation, " --> "
        while ( !_isdigit( *bufptr ) )
            bufptr++;

        // get end time, xx:xx:xx,xxx format, 12 bytes
        memcpy(tbuf, bufptr, 12);
        bufptr += 12;
#if 0 //liumzh 2005-9-19 16:28 , for both xx:xx:xx,xxx format &  x: x: x,  x format
        hr  = ((tbuf[0]-'0') * 10) + (tbuf[1]-'0');
        min = ((tbuf[3]-'0') * 10) + (tbuf[4]-'0');
        sec = ((tbuf[6]-'0') * 10) + (tbuf[7]-'0');
        ms  = ((tbuf[9]-'0') * 100) + ((tbuf[10]-'0') * 10) + (tbuf[11]-'0');
#else
        hr =  ((IsDigitTime(tbuf[0]))?((tbuf[0]-'0') * 10) : 0) + (tbuf[1]-'0');
        min = ((IsDigitTime(tbuf[3]))?((tbuf[3]-'0') * 10) : 0) + (tbuf[4]-'0');
        sec = ((IsDigitTime(tbuf[6]))?((tbuf[6]-'0') * 10) : 0) + (tbuf[7]-'0');
        ms  = 0; //((IsDigit(tbuf[9]))?((tbuf[9]-'0') * 100) : 0) + ((IsDigit(tbuf[10]))?((tbuf[10]-'0') * 10) : 0) + (tbuf[11]-'0');
        //#ifdef Support_SubExName_Changed  //lyc add-2006-2-20
        //    if( (!_isdigit(tbuf[1]))||(!_isdigit(tbuf[4]))||(!_isdigit(tbuf[7])) )
        //       goto Change_To_Next_SubT;
        //#endif  
#endif
        endtime = (hr*3600 + min*60 + sec) * STC_CLK + ms * MS_STC_CLK;

        while( !_iseol( bufptr ) )
            bufptr++;
            
        if( _iseol_unix( bufptr ) )
            bufptr += 1;
        else
            bufptr += 2;
        
        // skip blank string
        if( _iseol( bufptr ) )
            continue;

        bcnt = 0;
        suptr = bufptr;

        while( bufptr < bufend )
        {
            if( _iseol( bufptr ) )
            {
                UINT32 uiEolOffset = _iseol_unix( bufptr ) ? 1 : 2;
                if( _iseol( ( bufptr + uiEolOffset ) ) )
                {
                    bufptr += ( uiEolOffset * 2 );
                    break;
                }
            }

            bufptr++;
            bcnt++;
        }

        *idxptr++ = sttime;
        *idxptr++ = endtime;
        *idxptr++ = suptr + uiOffset - base;
        *idxptr++ = bcnt;

        if( idxptr + 3 >= s_pSubIdxBaseEndPtr )
        {
#ifdef DBG_KEYFRAME
            printf( "Subpicture index buffer too small, can't record all index\n" );            
#endif            
            break;
        }
        
#ifdef DBG_KEYFRAME
        printf( "st = %d, end = %d, offset = %d, cnt = %d\n", sttime, endtime, suptr + uiOffset - base, bcnt );
#endif
    } while (1);

    s_pSupIdxPtr    = s_pSupIdxBasePtr;
    s_pSupIdxEnd    = idxptr;
    s_pSupBufPtr    = s_pSupBufPtr;

    printf("SRT subtitile initialized!!\n" );
    #ifdef Support_SubExName_Changed  //hongfeng 2006/8/9 15:41
    if(s_uiSupType != INTERNAL_SUBTITLE_SRT)  
        s_uiSupType = INTERNAL_SUBTITLE_SRT;
    #endif    

    return 1;
    #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
      Change_To_Next_SubT:
       return 0;
    #endif   
}
#endif

// **************************************************************************************** //
#ifdef SUBTITLE_SUPPORT_SUB_MICRODVD
static int ParsingSubtitleSUB_MicroDVD()
{
    UINT32  uiFrame = 0;
    UINT32  sttime  = 0;
    UINT32  endtime = 0;

    UINT32  uiByteRead  = s_uiSupBufSize;
    UINT32  uiOffset    = 0;
    BYTE*   base        = s_pSupBufPtr;
    BYTE*   bufend      = s_pSupBufEndPtr;
    BYTE*   bufptr      = base;
    BYTE*   suptr       = NULL;
    UINT32* idxptr      = s_pSupIdxBasePtr;

    // parse subpicture
    do
    {
        if(( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT)&&(s_uiSupLen>s_uiSupBufSize)) //lyc update 2006-8-9;only fileszie>supbufsize,do supFillBuffer
        {            
            if( !supFillBuffer( &bufptr, &uiByteRead ) )
                break;

            uiOffset += ( s_uiSupBufSize - SUBTITLE_RELOAD_LIMIT );
        }

        while( !(( *bufptr == '{' ) || ( *bufptr == '[' )) )
        {
         if( bufptr >bufend )  //lyc add-2006-2-20
     	       break;
            bufptr++;
        }
        // skip "{"
        bufptr++;

        if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )
            break;
            
        // get start time, {xx...xx} format
        uiFrame = 0;
        while( !(( *bufptr == '}' ) || ( *bufptr == ']' )) )
        {
             #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
                if(!_isdigit( *bufptr ))
                  goto Change_To_Next_SubT;
             #endif        
            uiFrame = uiFrame * 10 + ( *bufptr++ - '0' );
        }
        if( *bufptr == ']' ) ////DENGHG modify [XXXXX] is not uiFrame ,it is ms time.2006-3-22 15:43
        {	
        	sttime = uiFrame * 100 * MS_STC_CLK;        	
      	}
      	else  
        sttime = frctl_frame_to_stc( uiFrame );

        // drop seperation, "{"
        bufptr += 2;

        // get end time, {xx...xx} format
        uiFrame = 0;
        while( !(( *bufptr == '}' ) || ( *bufptr == ']' )) )
        {
              #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
                if(!_isdigit( *bufptr ))
                  goto Change_To_Next_SubT;
              #endif
            uiFrame = uiFrame * 10 + ( *bufptr++ - '0' );
        }
 			if( *bufptr == ']' ) 
        	{	
        		endtime = uiFrame * 100 * MS_STC_CLK;        	
      		}
      		else      
        endtime = frctl_frame_to_stc( uiFrame );
        // skip "}"
        bufptr++;

        // skip space
        while( _isspace( *bufptr ) )
            bufptr++;

        suptr = bufptr;

        while( !_iseol( bufptr ) )
            bufptr++;

        if(uiFrame == 0) //get end time //some polish MicroDVD SUBTITLE has no end time denghg2006-1-10 11:40     
	    {
	        UINT32 i=0;
	    	UINT32 sttime1=0; 
	    	
	        while( !(( *(bufptr+i) == '{' )||( *(bufptr+i) == '[' ))&&( (bufptr+i) < bufend ) )
	            i++;
	    
	        if( ( *(bufptr+i) == '{' ) || ( *(bufptr+i) == '[' ) ) i++;
	            
	        while( !(( *(bufptr+i) == '}' )||( *(bufptr+i) == ']' ))&&( ( bufptr+i) < bufend ) )
	        {    	   
	            uiFrame = uiFrame * 10 + ( *(bufptr+i) - '0' );
	    	    i++;	    	    
	    	    if( *(bufptr+i) == ']' )   
	    	    	sttime1 =  uiFrame * 100 * MS_STC_CLK;
	    	    else   
	    	    	sttime1 = frctl_frame_to_stc( uiFrame );	    	    
	        }
	        
            #ifdef SUPPORT_TXTSUB_4S_OFF
            endtime = ( sttime1 > ( sttime+4*STC_CLK ) ) ? sttime+4*STC_CLK : sttime1;
            #else
            endtime= sttime1;
            #endif
	    }    

        *idxptr++ = sttime;
        *idxptr++ = endtime;
        *idxptr++ = suptr + uiOffset- base;
        *idxptr++ = bufptr - suptr;

        if( idxptr + 3 >= s_pSubIdxBaseEndPtr )
        {
#ifdef DBG_KEYFRAME
            printf( "Subpicture index buffer too small, can't record all index\n" );            
#endif            
            break;
        }
        
#ifdef DBG_KEYFRAME
        printf( "st = %d, end = %d, offset = %d, cnt = %d\n", sttime, endtime, suptr + uiOffset - base, bufptr - suptr );
#endif
    } while (1);

    s_pSupIdxPtr    = s_pSupIdxBasePtr;
    s_pSupIdxEnd    = idxptr;
    s_pSupBufPtr    = s_pSupBufPtr;

    printf("MicroDVD subtitile initialized!! %x %x %x\n\n", s_pSupIdxPtr, s_pSupIdxEnd, s_pSupBufPtr );
    #ifdef Support_SubExName_Changed  //hongfeng 2006/8/9 15:59
    if(s_uiSupType != INTERNAL_SUBTITLE_SUB_MICRODVD)  //hongfeng 2006/8/9 15:41
        s_uiSupType = INTERNAL_SUBTITLE_SUB_MICRODVD;
    #endif

    return 1;

       #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
        Change_To_Next_SubT:
         return  0;  
       #endif
   
}
#endif

// **************************************************************************************** //
#ifdef SUBTITLE_SUPPORT_SUB_SUBVIEWER
static int ParsingSubtitleSUB_SubViewer()
{
    BYTE    tbuf[12];
    UINT32  hr, min, sec, ms;
    UINT32  sttime, endtime;

    UINT32  uiByteRead  = s_uiSupBufSize;
    UINT32  uiOffset    = 0;
    BYTE*   base        = s_pSupBufPtr;
    BYTE*   bufend      = s_pSupBufEndPtr;
    BYTE*   bufptr      = base;
    BYTE*   suptr       = NULL;
    UINT32* idxptr      = s_pSupIdxBasePtr;

    // parse header
    while( strncmp( (const char*) bufptr, "[FONT]", 6 ) != 0 )
     {
     	   if( bufptr >= bufend )
     	   {
     	      #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
                goto Change_To_Next_SubT;
              #endif
     	   	 goto err_sub;
     	   }
        bufptr++;
     }
    while( !_iseol( bufptr ) )
        bufptr++;

    // parse subpicture
    do
    {
        if(( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT)&&(s_uiSupLen>s_uiSupBufSize)) //lyc update 2006-8-9;only fileszie>supbufsize,do supFillBuffer
        {            
            if( !supFillBuffer( &bufptr, &uiByteRead ) )
                break;

            uiOffset += ( s_uiSupBufSize - SUBTITLE_RELOAD_LIMIT );
        }

        while ( !_isdigit( *bufptr ) )
            bufptr++;
        
        if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )
            break;
            
        // get start time, xx:xx:xx.xx format, 11 bytes
        memcpy(tbuf, bufptr, 11);
        bufptr += 11;
        hr  = ((tbuf[0]-'0') * 10) + (tbuf[1]-'0');
        min = ((tbuf[3]-'0') * 10) + (tbuf[4]-'0');
        sec = ((tbuf[6]-'0') * 10) + (tbuf[7]-'0');
        ms  = ((tbuf[9]-'0') * 100) + ((tbuf[10]-'0') * 10);
        #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
          if((!_isdigit(tbuf[1]))||(!_isdigit(tbuf[4]))||(!_isdigit(tbuf[7]))||(!_isdigit(tbuf[10])))
           goto Change_To_Next_SubT;
        #endif 
        sttime = (hr*3600 + min*60 + sec) * STC_CLK + ms * MS_STC_CLK;

        // drop seperation, ","
        bufptr++;

        // get end time, xx:xx:xx.xx format, 11 bytes
        memcpy(tbuf, bufptr, 11);
        bufptr += 11;
        hr  = ((tbuf[0]-'0') * 10) + (tbuf[1]-'0');
        min = ((tbuf[3]-'0') * 10) + (tbuf[4]-'0');
        sec = ((tbuf[6]-'0') * 10) + (tbuf[7]-'0');
        ms  = ((tbuf[9]-'0') * 100) + ((tbuf[10]-'0') * 10);
        #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
          if((!_isdigit(tbuf[1]))||(!_isdigit(tbuf[4]))||(!_isdigit(tbuf[7]))||(!_isdigit(tbuf[10])))
           goto Change_To_Next_SubT;
        #endif 
        endtime = (hr*3600 + min*60 + sec) * STC_CLK + ms * MS_STC_CLK;

        while( !_iseol( bufptr ) )
            bufptr++;
            
        if( _iseol_unix( bufptr ) )
            bufptr += 1;
        else
            bufptr += 2;
        
        // skip blank string
        if( _iseol( bufptr ) )
            continue;

        suptr = bufptr;

        while( !_iseol( bufptr ) )
            bufptr++;

        *idxptr++ = sttime;
        *idxptr++ = endtime;
        *idxptr++ = suptr + uiOffset - base;
        *idxptr++ = bufptr - suptr;

        if( idxptr + 3 >= s_pSubIdxBaseEndPtr )
        {
#ifdef DBG_KEYFRAME
            printf( "Subpicture index buffer too small, can't record all index\n" );            
#endif            
            break;
        }
        
#ifdef DBG_KEYFRAME
        printf( "st = %d, end = %d, offset = %d, cnt = %d\n", sttime, endtime, suptr + uiOffset - base, bufptr - suptr );
#endif
    } while (1);

    s_pSupIdxPtr    = s_pSupIdxBasePtr;
    s_pSupIdxEnd    = idxptr;
    s_pSupBufPtr    = s_pSupBufPtr;

    printf("SubViewer subtitile initialized!! %x %x %x\n\n", s_pSupIdxPtr, s_pSupIdxEnd, s_pSupBufPtr );
    #ifdef Support_SubExName_Changed  //hongfeng 2006/8/9 15:59
	if(s_uiSupType != INTERNAL_SUBTITLE_SUB_SUBVIEWER)  //hongfeng 2006/8/9 15:41
	    s_uiSupType = INTERNAL_SUBTITLE_SUB_SUBVIEWER;
    #endif

    return 1;
 err_sub:
      return 0;  
        #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
         Change_To_Next_SubT:
          return  0;  
        #endif
}
#endif

// **************************************************************************************** //
#ifdef SUBTITLE_SUPPORT_SSA
static int ParsingSubtitleSSA()
{
    //BYTE	tbuf[10];
    UINT32  bcnt;
    UINT32  hr, min, sec, ms;
    UINT32  sttime, endtime;

    UINT32  uiByteRead  = s_uiSupBufSize;
    UINT32  uiOffset    = 0;
    BYTE*   base        = s_pSupBufPtr;
    BYTE*   bufend      = s_pSupBufEndPtr;
    BYTE*   bufptr      = base;
    BYTE*   suptr       = NULL;
    UINT32* idxptr      = s_pSupIdxBasePtr;

    // parse header  ... until "[Events]"
    while( strncmp( (const char*) bufptr, "[Events]", 8 ) != 0 )
    { 
      if( bufptr >= bufend )
     	{
     	    #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
               goto Change_To_Next_SubT;
            #endif
     	   	 goto err_sub;
     	}
        bufptr++;
    } 
	bufptr += 10;

    while( !_iseol( bufptr ) )
        bufptr++;

    // parse subpicture
    do
    {
        if(( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT)&&(s_uiSupLen>s_uiSupBufSize)) //lyc update 2006-8-9;only fileszie>supbufsize,do supFillBuffer
        {            
            if( !supFillBuffer( &bufptr, &uiByteRead ) )
                break;

            uiOffset += ( s_uiSupBufSize - SUBTITLE_RELOAD_LIMIT );
        }
        
        // error check omitted, should be "0x0D 0x0A" or "0x20"
        while( _isspace( *bufptr ) )
            bufptr++;

        //until start time  
        while (*bufptr != ',')
            bufptr++;
        bufptr++;    
        
        if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )
            break;
                    
        // mimitsai modify for another subtitle format of ssa 
        // get start time, xx:xx:xx,xx format, 11 bytes
        if( *(bufptr + 1) != ':' )
        {
            hr = ((bufptr[0]-'0') * 10) + (bufptr[1]-'0'); 
            bufptr += 3;
        }
        else // get start time, x:xx:xx,xx format, 10 bytes
        {
            hr  = (bufptr[0]-'0');
            bufptr += 2;
        }

        min = ((bufptr[0]-'0') * 10) + (bufptr[1]-'0');
        sec = ((bufptr[3]-'0') * 10) + (bufptr[4]-'0');
        ms  = ((bufptr[6]-'0') * 100) + ((bufptr[7]-'0') * 10);
        #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
          if((!_isdigit(bufptr[1]))||(!_isdigit(bufptr[4]))||(!_isdigit(bufptr[7])))
           goto Change_To_Next_SubT;
        #endif 
        sttime = (hr*3600 + min*60 + sec) * STC_CLK + ms * MS_STC_CLK;

        bufptr += 8;

        // drop seperation, ","
        while ( !_isdigit( *bufptr ) )
            bufptr++;

        // get end time, x:xx:xx,xx format, 10 bytes
        // get start time, xx:xx:xx,xx format, 11 bytes
        if( *(bufptr + 1) != ':' )
        {
            hr = ((bufptr[0]-'0') * 10) + (bufptr[1]-'0'); 
            bufptr += 3;
        }
        else // get start time, x:xx:xx,xx format, 10 bytes
        {
            hr  = (bufptr[0]-'0');
            bufptr += 2;
        }

        min = ((bufptr[0]-'0') * 10) + (bufptr[1]-'0');
        sec = ((bufptr[3]-'0') * 10) + (bufptr[4]-'0');
        ms  = ((bufptr[6]-'0') * 100) + ((bufptr[7]-'0') * 10);
         #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
          if((!_isdigit(bufptr[1]))||(!_isdigit(bufptr[4]))||(!_isdigit(bufptr[7])))
           goto Change_To_Next_SubT;
        #endif
        endtime = (hr*3600 + min*60 + sec) * STC_CLK + ms * MS_STC_CLK;

        bufptr += 8;

        bcnt = 0;
        while(bcnt < 7)
        {
            if( *bufptr == ',' )
                bcnt++;
            bufptr++;
        }
        
        suptr = bufptr;

        while( !_iseol( bufptr ) )
            bufptr++;

        *idxptr++ = sttime;
        *idxptr++ = endtime;
        *idxptr++ = suptr + uiOffset - base;
        *idxptr++ = bufptr - suptr;

        if( idxptr + 3 >= s_pSubIdxBaseEndPtr )
        {
#ifdef DBG_KEYFRAME
            printf( "Subpicture index buffer too small, can't record all index\n" );            
#endif            
            break;
        }
        
#ifdef DBG_KEYFRAME
        printf( "st = %d, end = %d, offset = %d, cnt = %d\n", sttime, endtime, suptr + uiOffset - base, bufptr  - suptr );
#endif
    } while (1);

    s_pSupIdxPtr    = s_pSupIdxBasePtr;
    s_pSupIdxEnd    = idxptr;
    s_pSupBufPtr    = s_pSupBufPtr;

    printf("SSA subtitile initialized!! %x %x %x\n\n", s_pSupIdxPtr, s_pSupIdxEnd, s_pSupBufPtr );
    #ifdef Support_SubExName_Changed  //hongfeng 2006/8/9 15:59
	if(s_uiSupType != INTERNAL_SUBTITLE_SSA)  //hongfeng 2006/8/9 15:41
	    s_uiSupType = INTERNAL_SUBTITLE_SSA;
    #endif

    return 1;
   err_sub:
     return 0;
       #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
        Change_To_Next_SubT:
         return  0; 
       #endif
}
#endif

// **************************************************************************************** //
#ifdef SUBTITLE_SUPPORT_ASS
static int ParsingSubtitleASS()
{
    BYTE    tbuf[10];
    UINT32  bcnt;
    UINT32  hr, min, sec, ms;
    UINT32  sttime, endtime;

    UINT32  uiByteRead  = s_uiSupBufSize;
    UINT32  uiOffset    = 0;
    BYTE*   base        = s_pSupBufPtr;
    BYTE*   bufend      = s_pSupBufEndPtr;
    BYTE*   bufptr      = base;
    BYTE*   suptr       = NULL;
    UINT32* idxptr      = s_pSupIdxBasePtr;

    // parse header  ... until "[Events]"
    while( strncmp( (const char*) bufptr, "[Events]", 8 ) != 0 )
      {
      	 if( bufptr >= bufend )
     	   {
     	      #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
                goto Change_To_Next_SubT;
              #endif
     	   	 goto err_sub;
     	   }
        bufptr++;
      } 
    while( !_iseol( bufptr ) )
        bufptr++;

    // parse subpicture
    do
    {
        if(( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT)&&(s_uiSupLen>s_uiSupBufSize)) //lyc update 2006-8-9;only fileszie>supbufsize,do supFillBuffer
        {            
            if( !supFillBuffer( &bufptr, &uiByteRead ) )
                break;

            uiOffset += ( s_uiSupBufSize - SUBTITLE_RELOAD_LIMIT );
        }

        // error check omitted, should be "0x0D 0x0A" or "0x20"
        while( _isspace( *bufptr ) )
            bufptr++;

        //until start time  
        while (*bufptr != ',')
            bufptr++;
        bufptr++;    
        
        if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )
            break;
        
        // get start time, x:xx:xx,xx format, 10 bytes
        memcpy(tbuf, bufptr, 10);
        bufptr += 10;
        hr  = (tbuf[0]-'0');
        min = ((tbuf[2]-'0') * 10) + (tbuf[3]-'0');
        sec = ((tbuf[5]-'0') * 10) + (tbuf[6]-'0');
        ms  = ((tbuf[8]-'0') * 100) + ((tbuf[9]-'0') * 10);
        #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
          if((!_isdigit(tbuf[3]))||(!_isdigit(tbuf[6]))||(!_isdigit(tbuf[9])))
           goto Change_To_Next_SubT;
        #endif
        sttime = (hr*3600 + min*60 + sec) * STC_CLK + ms * MS_STC_CLK;

        // drop seperation, ","
        while ( !_isdigit( *bufptr ) )
            bufptr++;

        // get end time, x:xx:xx,xx format, 10 bytes
        memcpy(tbuf, bufptr, 10);
        bufptr += 10;
        hr  = (tbuf[0]-'0');
        min = ((tbuf[2]-'0') * 10) + (tbuf[3]-'0');
        sec = ((tbuf[5]-'0') * 10) + (tbuf[6]-'0');
        ms  = ((tbuf[8]-'0') * 100) + ((tbuf[9]-'0') * 10);
        #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
          if((!_isdigit(tbuf[3]))||(!_isdigit(tbuf[6]))||(!_isdigit(tbuf[9])))
           goto Change_To_Next_SubT;
        #endif
        endtime = (hr*3600 + min*60 + sec) * STC_CLK + ms * MS_STC_CLK;

        bcnt = 0;
        while(bcnt < 7)
        {
            if( *bufptr == ',' )
                bcnt++;
            bufptr++;
        }
        
        suptr = bufptr;

        while( !_iseol( bufptr ) )
            bufptr++;

        *idxptr++ = sttime;
        *idxptr++ = endtime;
        *idxptr++ = suptr + uiOffset - base;
        *idxptr++ = bufptr - suptr;

        if( idxptr + 3 >= s_pSubIdxBaseEndPtr )
        {
#ifdef DBG_KEYFRAME
            printf( "Subpicture index buffer too small, can't record all index\n" );            
#endif            
            break;
        }

#ifdef DBG_KEYFRAME
        printf( "st = %d, end = %d, offset = %d, cnt = %d\n", sttime, endtime, suptr + uiOffset - base, bcnt );
#endif
    } while (1);

    s_pSupIdxPtr    = s_pSupIdxBasePtr;
    s_pSupIdxEnd    = idxptr;
    s_pSupBufPtr    = s_pSupBufPtr;

    printf("ASS subtitile initialized!! %x %x %x\n\n", s_pSupIdxPtr, s_pSupIdxEnd, s_pSupBufPtr );
    #ifdef Support_SubExName_Changed  //hongfeng 2006/8/9 15:59
	if(s_uiSupType != INTERNAL_SUBTITLE_ASS)  //hongfeng 2006/8/9 15:41
	    s_uiSupType = INTERNAL_SUBTITLE_ASS;
    #endif

    return 1;
   err_sub:
    return 0;  
       #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
        Change_To_Next_SubT:
          return  0;  
       #endif
}
#endif

// **************************************************************************************** //
#ifdef SUBTITLE_SUPPORT_SMI
#if defined (SUPPORT_SMI_MultiLanguage)||defined(SUPPORT_SMI_MultiColor)//2005-8-16 20:38 zhoulin
static int ParsingSubtitleSMI()
{       
    UINT32  hr, min, sec, ms;
    UINT32  val, cnt, bcnt=0;
    UINT32  sttime = 0;
    BYTE* pTmp;
    BYTE    aTmpBuf[16];
    UINT32  uiByteRead  = s_uiSupBufSize;
    UINT32  uiOffset    = 0;
    BYTE*   base        = s_pSupBufPtr;
    BYTE*   bufend      = s_pSupBufEndPtr;
    BYTE*   bufptr      = base;
    UINT32  suptr=0 ;
    UINT32* idxptr      = s_pSupIdxBasePtr;

    BYTE    firstSupflg =0;
   
    UINT8   state       =0;

    UINT8    i;
    
    #ifdef  SUPPORT_SMI_MultiColor//2005-8-16 20:38 zhoulin
    UINT8    j;
    BYTE*  bufptrb=NULL;
    
    for(i=0;i<MAX_palette_colors;i++)//initialize palette
    {
         for(j=0;j<20;j++)
            color_temp[i][j]='\0';
         palette_16color_MP4_SUB[i]=CLUTE_TRANS;
    }
    palette_16color_MP4_SUB[1]=0xf3f3f3ff;//set default color
    palette_color_num=2;
    #endif
    
    #ifdef  SUPPORT_SMI_MultiLanguage//2005-8-16 20:38 zhoulin
    lang_num=0;
    #endif
 
 //pre-parse SAMI   
    while(!(state==0xff||state==0xf0))//if state==0xff,end of parse
    {                                  //state==0xf0,error
        if( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT )
        {     
            if( !supFillBuffer( &bufptr, &uiByteRead ) )             
                break;
                   
            uiOffset += ( s_uiSupBufSize - SUBTITLE_RELOAD_LIMIT );
        }
        
        switch(state)
        {   //check <SAMI>
            case 0:
                while( bufend - bufptr > SUBTITLE_RELOAD_LIMIT)
                {   
                if( *bufptr == '<' )
                    break;
                       bufptr++;
                }
                if( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT )
                    state=0xf0;//error,end parse                
                else if( strncmpIgnoreCase(  bufptr, "<SAMI>", 6 )==0)
                {
                    bufptr+=6;
                    state=1;//to check HEAD
                }
                else  bufptr++;
            
                break;
            //check <HEAD> 
            case 1:
                while(bufend - bufptr > SUBTITLE_RELOAD_LIMIT)
                {   
                    if( *bufptr == '<' )
                        break;
                    bufptr++;
                }
                if( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT )
                    state=0xf0;//error,end parse 
                else if(strncmpIgnoreCase(  bufptr, "<HEAD>", 6 )==0 )
                {
                  bufptr+=6;
                  state=2;//to check style
                }   
                else if((strncmpIgnoreCase(  bufptr, "<BODY>", 6 )==0) || (strncmpIgnoreCase(  bufptr, "<body>", 6 )==0))
                { 
                  bufptr+=6;
                  state=5;//to check body
                }
                else bufptr++;
                break;
        
                
            //check style
            case 2:
               while( bufend - bufptr > SUBTITLE_RELOAD_LIMIT)
                {   
                    if( *bufptr == '<' )
                        break;
                    bufptr++;
                }
                if( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT )
                    state=0xf0;//error,end parse 
                else if(strncmpIgnoreCase(  bufptr, "<STYLE", 6 )==0 )
                {
                  bufptr+=6;
                  state=3;//to check language info 
                }   
                else if(strncmpIgnoreCase(  bufptr, "</HEAD>", 7 )==0 )
                {
                  bufptr+=7;
                  state=5;//to check body
                }
                else bufptr++;
                break;
                
             //check  language info. & default color
             case 3:
                while(bufend - bufptr > SUBTITLE_RELOAD_LIMIT)
                {   
                    if( *bufptr == '<'
                    #if defined(SUPPORT_SMI_MultiColor)    
                        ||*bufptr == 'P'||*bufptr == 'p'
                    #endif
                    #if defined (SUPPORT_SMI_MultiLanguage)
                        ||*bufptr == '.'
                    #endif    
                         )
                        break;
                    bufptr++;
                }
                if( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT )
                    state=0xf0;//error,end parse 
              #if defined(SUPPORT_SMI_MultiColor)   
                else if(*bufptr == 'P'||*bufptr == 'p')
                {   if(*(bufptr-1)=='-'||*(bufptr-1)==0x0A||*(bufptr-1)==' '||*(bufptr-1)==0x09)
                    {
                        bufptr++;
                        while(*bufptr==' '||*bufptr==0x09) bufptr++;
                        if(*bufptr==0x7B)                    
                             state=4;//to check default color
                        
                    }     
                    else bufptr++; 
                    
                }
             #endif
             #if defined (SUPPORT_SMI_MultiLanguage)
                else if(*bufptr == '.')//check language info
                {   bufptr++;
                   
                    read_lang_info(&bufptr);
                }
             #endif
                else if(strncmpIgnoreCase( bufptr, "</STYLE>", 8 )==0 )
                {
                  bufptr+=8;
                  state=5;//to check body
                  
                }
                else 
                  bufptr++;
                 
                break;
           #if defined(SUPPORT_SMI_MultiColor) 
            //check default color      
            case 4:
                while( bufend - bufptr > SUBTITLE_RELOAD_LIMIT)
                {   
                    if( *bufptr == 0x7D||*bufptr == 'C'||*bufptr == 'c')
                        break;
                    bufptr++;
                    
                }
                if( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT )
                    state=0xf0;//error,end parse 
                else if(*bufptr == 'C'||*bufptr == 'c')
                {   
                    if((strncmpIgnoreCase(  bufptr, "color", 5 )==0)&&
                          (*(bufptr-1)==' '|| *(bufptr-1)==';'||*(bufptr-1)==0x7B||*(bufptr-1)==0x0A||*(bufptr-1)==0x09))     
                    
                    {
                        bufptr+=5;
                        if(read_color(&bufptr,1))
                                 state=3;
                        
                    }               
                    else 
                      bufptr++;
                    
                
                }     
               else if(*bufptr == 0x7D)
               {   state=3;
                   
               }
              
               else 
                  bufptr++;
           
               break;
             #endif
               //check body         
            case 5:     
              
               while( (UINT32)( bufptr + uiOffset - base ) <= s_uiSupLen &&
                        bufend - bufptr > SUBTITLE_RELOAD_LIMIT)
                {   
                    if( *bufptr =='<')
                        break;
                    bufptr++;
                    if(firstSupflg)
                    {    bcnt++;
                         
                    }
                   
                }
               if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )
                    state=0xf0;//error,end parse

               else if( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT )
                    break;
               else if(strncmpIgnoreCase(  bufptr, "<SYNC", 5 )==0 )
               {  
                  if(firstSupflg)
                  {   
                      pTmp = (BYTE*)(bufptr - 1);   
                      while( !( (*pTmp == 0x0A) && (*(pTmp-1) == 0x0D) ) )
                      {
                         bcnt--;
                         pTmp--;
                      }
                       
                      *idxptr++ = sttime;
                      *idxptr++ =0;
                      *idxptr++ = suptr;
                      *idxptr++ = bcnt;
                     
                      if( idxptr + 3 >= s_pSubIdxBaseEndPtr )
                       {
                #ifdef DBG_KEYFRAME
                            printf( "Subpicture index buffer too small, can't record all index\n" );            
                #endif            
                            state=0xff;
                            break;
                       }
                      
                  
                  }

                  bufptr+=5;
                  //to check time
                  while ( *bufptr != '=' )
                    bufptr++;
                     
                    
                  bufptr++;
                  
                  // get start time ... 
                  aTmpBuf[0] = '\0';
                  cnt = 0;
                  i =0;
                  while( _isdigit( *bufptr ) )
                  {
                    aTmpBuf[i] = *bufptr++;
                    cnt++;
                    i++;
                    
                  }
                  aTmpBuf[cnt]='\0';
                  
                    
                  if(cnt > 3)
                  {
                    val = 0;
                    ms = (aTmpBuf[cnt-3] - '0')*100 + (aTmpBuf[cnt-2] - '0')*10 + (aTmpBuf[cnt-1]-'0');
                    for(i=0; i<cnt-3; i++)
                    {
                        val = val * 10  + (aTmpBuf[i] - '0');
                    }
                    hr = val / 3600;
                    min = ( val - hr * 3600 ) / 60;
                   
                    sec = val - hr * 3600 - min * 60;
                  }
                  else
                  {
                    ms = 0;
                    for(i=0; i<cnt; i++)
                    {
                        ms = ms * 10  + (aTmpBuf[i] - '0');
                    }
                    hr = 0;
                    min = 0;
                    sec = 0;
                  }
                
                  sttime = (hr*3600 + min*60 + sec) * STC_CLK + ms * MS_STC_CLK;
                  
                  while(*bufptr != '>')
                      bufptr++;
                      
                
                  bufptr++;
                  bcnt=0;   
                  suptr = (UINT32)(bufptr + uiOffset - base);
                  firstSupflg=1;
                  
               
               }
            #if defined(SUPPORT_SMI_MultiColor) 
               else if(strncmpIgnoreCase(  bufptr, "<font", 5 )==0 )
               {  bcnt+=6;//ignore the ' '
                  bufptr+=6;
                  //to check color
                  state=6;
               
               }
            #endif
               else if(strncmpIgnoreCase(  bufptr, "</BODY>", 7 )==0)
               {  
                  state=0xff;//end parse
                  if(firstSupflg)
                  {   
                      pTmp = (BYTE*)(bufptr - 1);   
                      while( !( (*pTmp == 0x0A) && (*(pTmp-1) == 0x0D) ) )
                      {
                         bcnt--;
                         pTmp--;
                      }
                       
                      *idxptr++ = sttime;
                      *idxptr++ = 0xffffffff;
                      *idxptr++ = suptr;
                      *idxptr++ = bcnt;
                  
                  }
                 
                  
               }
               
               else 
               { bufptr++;
                 if(firstSupflg)
                        bcnt++;
           
               }
               
               break;
         #if defined(SUPPORT_SMI_MultiColor) 
              //check colors in the body 
           case 6:
               while( (UINT32)( bufptr + uiOffset - base ) <= s_uiSupLen &&
                        bufend - bufptr > SUBTITLE_RELOAD_LIMIT)
                {   
                    if( *bufptr =='c'||*bufptr =='C'||*bufptr =='>')
                        break;
                    bufptr++;
                 
                    bcnt++;
                    
                }
               if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )
                    state=0xf0;//error,end parse
               else if( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT )
                    break;
               else if(*bufptr == 'C'||*bufptr == 'c')
                {   
                    if((strncmpIgnoreCase(  bufptr, "color", 5 )==0))        
                    {   bcnt+=5;
                        bufptr+=5;
                        bufptrb=bufptr;
                        if(read_color(&bufptr,0))
                                 state=5;
                        bcnt=bcnt+bufptr-bufptrb;
                    }               
                    
                
                }     
               else if(*bufptr == '>')
               {   state=5;
                  
               }
               else 
               {
                 bufptr++;
                 bcnt++;
                 
               }
               
               break;
         #endif      
        
        }
    }

    s_pSupIdxPtr    = s_pSupIdxBasePtr;
    s_pSupIdxEnd    = idxptr;
    s_pSupBufPtr    = s_pSupBufPtr;
    
    #ifdef Support_SubExName_Changed  //hongfeng 2006/8/9 16:0
    if(s_uiSupType != INTERNAL_SUBTITLE_SMI)  //hongfeng 2006/8/9 15:41
        s_uiSupType = INTERNAL_SUBTITLE_SMI;
    #endif

    if(state==0xff)
       return 1;    
    else return 0;
}  

#else//defined (SUPPORT_SMI_MultiLanguage)||defined(SUPPORT_SMI_MultiColor)
static int ParsingSubtitleSMI()
{       
    UINT32  hr, min, sec, ms;
    UINT32  val, bcnt;
    UINT32  sttime = 0xFFFFFFFF;
    UINT32  i, uiCnt;

    BYTE    aTmpBuf[16];
    UINT32  uiByteRead  = s_uiSupBufSize;
    UINT32  uiOffset    = 0;
    BYTE*   base        = s_pSupBufPtr;
    BYTE*   bufend      = s_pSupBufEndPtr;
    BYTE*   bufptr      = base;
    BYTE*   suptr       = NULL;
    UINT32* idxptr      = s_pSupIdxBasePtr;

     #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
         UINT32 Sync_Num =0;
     #endif
    // parse subpicture
    do
    {
        if(( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT)&&(s_uiSupLen>s_uiSupBufSize)) //lyc update 2006-8-9;only fileszie>supbufsize,do supFillBuffer
        {   
            if( !supFillBuffer( &bufptr, &uiByteRead ) )
                break;
            
            uiOffset += ( s_uiSupBufSize - SUBTITLE_RELOAD_LIMIT );
        }

        if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )
            break;

        // trim space & new line
        while( _isspace( *bufptr ) )
            bufptr++;

        // set value for string
        suptr   = bufptr;
        bcnt    = 0;

        // get time header "<SYNC"
        while( strncmp( (const char*) bufptr, "<SYNC", 5 ) != 0 )
        {
            if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )
                goto SMI_EXIT;
                
            bcnt++;
            bufptr++;
        }

       #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
            if ( strncmp( (const char*) bufptr, "<SYNC", 5 ) == 0 )
              Sync_Num++;
       #endif
        // get time ... 
        while( !_isdigit( *bufptr ) )
            bufptr++;

        i   = uiCnt   = 0;

        while( _isdigit( *bufptr ) )
            aTmpBuf[ uiCnt++ ] = *bufptr++;

        if( uiCnt > 3 )
        {
            val = 0;
            ms = ( aTmpBuf[ uiCnt - 3 ] - '0' ) * 100 + ( aTmpBuf[ uiCnt - 2 ] - '0' ) * 10 + ( aTmpBuf[ uiCnt - 1 ] - '0' );

            for( i = 0; i < uiCnt - 3 ; i++ )
                val = val * 10  + ( aTmpBuf[i] - '0' );

            hr  = val / 3600;
            min = ( val - hr * 3600 ) / 60;
            sec = val - hr * 3600 - min * 60;
        }
        else
        {
            ms = 0;
            for( i = 0; i < uiCnt; i++ )
                ms = ms * 10  + ( aTmpBuf[i] - '0' );

            hr  = 0;
            min = 0;
            sec = 0;
        }
        
        val = ( hr * 3600 + min * 60 + sec ) * STC_CLK + ms * MS_STC_CLK;

        bufptr++;   //lyc update 2006-2-23,for *.smi file no "<P" flag but data fellow
        while((_iseol(bufptr))||( _isspace(*bufptr)))
            bufptr++;
        if( strncmp( (const char*) bufptr, "<P", 2 ) == 0 )    
        {// get content header "<P"
          //while( strncmp( (const char*) bufptr, "<P", 2 ) != 0 )
          //  bufptr++;

        while( *bufptr != '>' )
            bufptr++;

        bufptr++;
        }

        // add key
        if( sttime != 0xFFFFFFFF )
        {
            *idxptr++ = sttime;
            *idxptr++ = val;
            *idxptr++ = suptr + uiOffset - base;
            *idxptr++ = bcnt;
    
            if( idxptr + 3 >= s_pSubIdxBaseEndPtr )
            {
#ifdef DBG_KEYFRAME
                printf( "Subpicture index buffer too small, can't record all index\n" );            
#endif            
                break;
            }

#ifdef DBG_KEYFRAME
            printf( "st = %d, end = %d, offset = %d, cnt = %d\n", sttime, val, suptr + uiOffset - base, bcnt );
#endif
        }
       
        // get content
        if( strncmp( (const char*) bufptr, "&nbsp;", 6 ) == 0 )
            sttime = 0xFFFFFFFF;
        else
            sttime = val;
        
    } while( TRUE );

SMI_EXIT:
     #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
         if(Sync_Num<1)
            goto Change_To_Next_SubT;
     #endif
    s_pSupIdxPtr    = s_pSupIdxBasePtr;
    s_pSupIdxEnd    = idxptr;
    s_pSupBufPtr    = s_pSupBufPtr;

    printf("SMI subtitile initialized!! %x %x %x\n\n", s_pSupIdxPtr, s_pSupIdxEnd, s_pSupBufPtr );
    #ifdef Support_SubExName_Changed  //hongfeng 2006/8/9 16:0
    if(s_uiSupType != INTERNAL_SUBTITLE_SMI)  //hongfeng 2006/8/9 15:41
        s_uiSupType = INTERNAL_SUBTITLE_SMI;
    #endif

     return TRUE;

     #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
        Change_To_Next_SubT:
         return  0; 
      #endif
}

#endif//end defined (SUPPORT_SMI_MultiLanguage)||defined(SUPPORT_SMI_MultiLanguage)
#endif//end SUBTITLE_SUPPORT_SMI

// **************************************************************************************** //
#ifdef SUBTITLE_SUPPORT_PSB
static int ParsingSubtitlePSB()
{
    BYTE    tbuf[7];
    UINT32  hr, min, sec;
    UINT32  sttime, endtime;

    UINT32  uiByteRead  = s_uiSupBufSize;
    UINT32  uiOffset    = 0;
    BYTE*   base        = s_pSupBufPtr;
    BYTE*   bufend      = s_pSupBufEndPtr;
    BYTE*   bufptr      = base;
    BYTE*   suptr       = NULL;
    UINT32* idxptr      = s_pSupIdxBasePtr;

    // parse subpicture
    do
    {
        if(( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT)&&(s_uiSupLen>s_uiSupBufSize)) //lyc update 2006-8-9;only fileszie>supbufsize,do supFillBuffer
        {            
            if( !supFillBuffer( &bufptr, &uiByteRead ) )
                break;

            uiOffset += ( s_uiSupBufSize - SUBTITLE_RELOAD_LIMIT );
        }
                
        while( *bufptr != '{' )
         {
              if( bufptr >= bufend )
     	      {
     	   	  #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
                   goto Change_To_Next_SubT;
                  #endif
     	   	   goto err_sub;
     	      }
            bufptr++;
         }
        if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )
            break;
            
        // skip "{"
        bufptr++;

        // get start time, x:xx:xx format, 7 bytes
        memcpy(tbuf, bufptr, 7);
        bufptr += 7;
        hr  = (tbuf[0]-'0');
        min = ((tbuf[2]-'0') * 10) + (tbuf[3]-'0');
        sec = ((tbuf[5]-'0') * 10) + (tbuf[6]-'0');
        sttime = (hr*3600 + min*60 + sec) * STC_CLK;

        #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
          if((!_isdigit(tbuf[3]))||(!_isdigit(tbuf[6])))
             goto Change_To_Next_SubT;
        #endif
        
        // drop seperation, "}{"
        while ( !_isdigit( *bufptr ) )
            bufptr++;

        // get end time, x:xx:xx format, 7 bytes
        memcpy(tbuf, bufptr, 7);
        bufptr += 7;
        hr  = (tbuf[0]-'0');
        min = ((tbuf[2]-'0') * 10) + (tbuf[3]-'0');
        sec = ((tbuf[5]-'0') * 10) + (tbuf[6]-'0');
        endtime = (hr*3600 + min*60 + sec) * STC_CLK;
        
        #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
          if((!_isdigit(tbuf[3]))||(!_isdigit(tbuf[6])))
             goto Change_To_Next_SubT;
        #endif
        
        // skip "}"
        bufptr++;

        suptr = bufptr;

        while( !_iseol( bufptr ) )
            bufptr++;
        
        *idxptr++ = sttime;
        *idxptr++ = endtime;
        *idxptr++ = suptr + uiOffset - base;
        *idxptr++ = bufptr - suptr;

        if( idxptr + 3 >= s_pSubIdxBaseEndPtr )
        {
#ifdef DBG_KEYFRAME
            printf( "Subpicture index buffer too small, can't record all index\n" );            
#endif            
            break;
        }
        
#ifdef DBG_KEYFRAME
        printf( "st = %d, end = %d, offset = %d, cnt = %d\n", sttime, endtime, suptr + uiOffset - base, bufptr - suptr );
#endif
    } while (1);

    s_pSupIdxPtr    = s_pSupIdxBasePtr;
    s_pSupIdxEnd    = idxptr;
    s_pSupBufPtr    = s_pSupBufPtr;

    printf("PSB subtitile initialized!! %x %x %x\n\n", s_pSupIdxPtr, s_pSupIdxEnd, s_pSupBufPtr );

    return 1;
   err_sub:
     return 0; 
      #ifdef Support_SubExName_Changed  //lyc add-2006-2-20
        Change_To_Next_SubT:
          if((_isdigit(tbuf[3]))&&(_isdigit(tbuf[6])))
          {
             s_pSupIdxPtr    = s_pSupIdxBasePtr;
             s_pSupIdxEnd    = idxptr;
             s_pSupBufPtr    = s_pSupBufPtr;
             printf("PSB subtitile initialized!! %x %x %x\n\n", s_pSupIdxPtr, s_pSupIdxEnd, s_pSupBufPtr );
             return 1;
          }	
          else 
          return  0; 
      #endif
}
#endif

// **************************************************************************************** //
#ifdef SUBTITLE_SUPPORT_TXT

#define IsDigit( chr )      ( chr >= '0' && chr <= '9' )
#define IsSemiColumn( chr ) ( chr == ':' )

#ifdef SUBTITLE_SUPPORT_TMplayerTXT
#define IsSemiColumn1( chr )    ( chr == ',' || chr == '.') 
#endif

static int ParsingSubtitleTXT()
{
    BYTE*   bufptr  = s_pSupBufPtr;
    BYTE*   bufend      = s_pSupBufEndPtr; //lyc add 2006-3-15,for TCL more format .txt
    while( _isspace( *bufptr ) )
        bufptr++;

     //lyc add 2006-3-15,for TCL more format .txt,try to get "{" or "[" or "00:00:" or "0:00:"   
    do
     {   
     	if(( *bufptr == '{' ) || ( *bufptr == '[' ) || ( strncmp( (const char*) bufptr, "00:", 3 ) == 0 ) || ( strncmp( (const char*) bufptr, "0:",2 ) == 0 ))
     	  break;                           
     	 if(bufptr>=bufend)
     	    goto err_txtsub;
        bufptr++;
     }while(1);

    if( ( *bufptr == '{' ) || ( *bufptr == '[' ) )  //denghg add for [][] format subtitle 2006-1-10 01:55     
    {
        s_uiSupType = INTERNAL_SUBTITLE_SUB_MICRODVD;
        return ParsingSubtitleSUB_MicroDVD();
    }
    else if( IsDigit( *bufptr ) )
    {
        s_uiSupType = INTERNAL_SUBTITLE_TXT;

#ifdef SUBTITLE_SUPPORT_TMplayerTXT
        if((*(bufptr + 8) == ':')||(*(bufptr + 7) == ':'))//other txt TMplayerTXT format x:xx:xx:
#endif

        {   
            //return ParsingSubtitleTXT_TXT();//lyc add 2006-3-15,for TCL more format .txt
            return ParsingSubtitleTXT_TXT_INTERFACE_TIME();
        }

#ifdef SUBTITLE_SUPPORT_TMplayerTXT
        else
        {
            return ParsingSubtitleTmPlayerTXT();
        }
#endif
    }

    return 0;
err_txtsub:      
    return 0;
}

// **************************************************************************************** //
static int ParsingSubtitleTXT_TXT_INTERFACE_TIME()
{
	BYTE*   base        = s_pSupBufPtr;
  BYTE*   bufend      = s_pSupBufEndPtr;
  BYTE*   bufptr      = base; 
  
  while ( ( strncmp( (const char*) bufptr, "00:", 3 ) != 0 ) && ( strncmp( (const char*) bufptr, "0:",2 ) != 0 ) )
  {
        bufptr++;
        if( bufptr >= bufend )
            goto TXT_ERROR;
  }

 
  //lyc add 2006-3-15,for TCL more format .txt
  // get start time, xx:xx:xx:xx aa xx:xx:xx:xx format, aa=20 or aa=20 20 or aa=09,or others
   if(  (_isdigit( bufptr[15])||(IsSemiColumn(bufptr[15])))&&(_isdigit( bufptr[16])||(IsSemiColumn(bufptr[16])))&&
        (_isdigit( bufptr[17])||(IsSemiColumn(bufptr[17])))&&(_isdigit( bufptr[18])||(IsSemiColumn(bufptr[18])))
     )
    {
    	 #ifdef DBG_KEYFRAME
     	  printf("*.txt format is  xx:xx:xx:xx aa xx:xx:xx:xx !\n");
     	 #endif
    	 if(ParsingSubtitleTXT_TXT_Two_STimeData())
      	    return 1;
    }	
    
   // get start time, x:xx:xx:xx aa x:xx:xx:xx format, aa=20 or aa=20 20 or aa=09
   else if(( _isspace( bufptr[10] ) && _isdigit( bufptr[11] )&& _isdigit( bufptr[13] )&&IsSemiColumn( bufptr[12] )&&
                                _isdigit( bufptr[14] )&& _isdigit( bufptr[16] )&&IsSemiColumn( bufptr[15] )&&
                                _isdigit( bufptr[17] )&& _isdigit( bufptr[19] )&&IsSemiColumn( bufptr[18] ) )||
     ( _isspace( bufptr[10] )&& _isspace( bufptr[11] )&& _isdigit( bufptr[12] )&& _isdigit( bufptr[14] )&&IsSemiColumn( bufptr[13] )&&
                                                         _isdigit( bufptr[15] )&& _isdigit( bufptr[17] )&&IsSemiColumn( bufptr[16] )&&
                                                         _isdigit( bufptr[18] )&& _isdigit( bufptr[20] )&&IsSemiColumn( bufptr[19] )    
     ))                           
    {
    	 #ifdef DBG_KEYFRAME
     	 printf("*.txt format is  x:xx:xx:xx aa x:xx:xx:xx !\n");
     	#endif
    	 if(ParsingSubtitleTXT_TXT_Two_USTimeData())
      	    return 1;
    }	
   // get start time, x:xx:xx:
   else if(( _isdigit( bufptr[0] )&& _isdigit( bufptr[2] )&&IsSemiColumn( bufptr[1] )&&
             _isdigit( bufptr[3] )&& _isdigit( bufptr[5] )&&IsSemiColumn( bufptr[4] )&&
             _isdigit( bufptr[6] )&&IsSemiColumn( bufptr[7] ) ))
   {
   	  #ifdef DBG_KEYFRAME
     	 printf("*.txt format is  x:xx:xx:xx !\n");
     	#endif
   	 if(ParsingSubtitleTXT_TXT_OTHER() == 1) //denghg add for subtitle format x:xx:xx:2006-1-10 01:50     
        return 1;
   } // get start time, xx:xx:xx:
   else if( _isdigit( bufptr[0] ) && _isdigit( bufptr[1] ) &&IsSemiColumn( bufptr[2] ) &&
            _isdigit( bufptr[3] ) && _isdigit( bufptr[4] ) &&IsSemiColumn( bufptr[5] ) &&
            _isdigit( bufptr[6] ) && _isdigit( bufptr[7] ) &&IsSemiColumn( bufptr[8] ) )
   {
   	  #ifdef DBG_KEYFRAME
     	 printf("*.txt format is  xx:xx:xx:xx !\n");
     	#endif
   	  if(ParsingSubtitleTXT_TXT() == 1) 
        return 1;
   }
   else
     {
     	#ifdef DBG_KEYFRAME
     	 printf("*.txt format in : xx:xx:xx: / x:xx:xx: / x:xx:xx:xx aa x:xx:xx:xx!,but not commonly!\n");
     	#endif
     	 return 0;
    }       	 
    
  TXT_ERROR:
     	#ifdef DBG_KEYFRAME
     	 printf("*.txt format in : xx:xx:xx: / x:xx:xx: / x:xx:xx:xx aa x:xx:xx:xx!,but not commonly!\n");
     	#endif
    return 0;
                          
}	
static int ParsingSubtitleTXT_TXT()
{
    UINT32  hr, min, sec;
    UINT32  sttime;

    UINT32  uiByteRead  = s_uiSupBufSize;
    UINT32  uiOffset    = 0;
    BYTE*   base        = s_pSupBufPtr;
    BYTE*   bufend      = s_pSupBufEndPtr;
    BYTE*   bufptr      = base;
    BYTE*   suptr       = NULL;
    UINT32* idxptr      = s_pSupIdxBasePtr;

  //  if(ParsingSubtitleTXT_TXT_OTHER() == 1) //denghg add for subtitle format x:xx:xx:2006-1-10 01:50     
  //      return 1;  //lyc move to ParsingSubtitleTXT_TXT_INTERFACE

    //while ( !_isdigit( *bufptr ) ) // //lyc add 2006-3-15,for TCL more format .txt
    while ( ( strncmp( (const char*) bufptr, "00:", 3 ) != 0 ) && ( strncmp( (const char*) bufptr, "0:",2 ) != 0 ) )
    {
        bufptr++;
        if( bufptr >= bufend )
            goto TXT_ERROR;
    }

    // get start time, xx:xx:xx: format, 9 bytes
    if( !IsDigit( bufptr[0] ) || !IsDigit( bufptr[1] ) || !IsSemiColumn( bufptr[2] ) ||
        !IsDigit( bufptr[3] ) || !IsDigit( bufptr[4] ) || !IsSemiColumn( bufptr[5] ) ||
        !IsDigit( bufptr[6] ) || !IsDigit( bufptr[7] ) || !IsSemiColumn( bufptr[8] ) )
        goto TXT_ERROR;

    hr      = ((bufptr[0]-'0') * 10) + (bufptr[1]-'0');
    min     = ((bufptr[3]-'0') * 10) + (bufptr[4]-'0');
    sec     = ((bufptr[6]-'0') * 10) + (bufptr[7]-'0');
    sttime  = (hr*3600 + min*60 + sec) * STC_CLK;
    
    //lyc add 2006-3-15,for TCL more format .txt
    if( (bufptr[11]==0xB3)&&(bufptr[12]==0x30)&&
        (bufptr[13]==0x4E)&&(bufptr[14]==0x45)&&(bufptr[15]==0x4E))
     {
       	 bufptr  += 8;
     }
    bufptr  += 9;
    suptr   = bufptr;

    // parse subpicture
    do
    {
        if(( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT)&&(s_uiSupLen>s_uiSupBufSize)) //lyc update 2006-8-9;only fileszie>supbufsize,do supFillBuffer
        {            
            if( !supFillBuffer( &bufptr, &uiByteRead ) )
                break;

            uiOffset += ( s_uiSupBufSize - SUBTITLE_RELOAD_LIMIT );
        }

        while( !_iseol( bufptr ) )
            bufptr++;

        if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )
            break;
        
        idxptr[0] = sttime;
        idxptr[2] = suptr + uiOffset - base;
        idxptr[3] = bufptr - suptr/* - 2*/; //denghg modify no  need -2.  2006-3-9 15:18

        while ( !_isdigit( *bufptr ) )
        {
            bufptr++;

            if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )     
            {
                idxptr[1] = 0xffffffff;

#ifdef DBG_KEYFRAME
        printf( "st = %d, end = %d, offset = %d, cnt = %d\n", idxptr[0], idxptr[1], idxptr[2], idxptr[3] );
#endif
                idxptr += 4;
                goto TXT_END;
            }
        }

        hr      = ((bufptr[0]-'0') * 10) + (bufptr[1]-'0');
        min     = ((bufptr[3]-'0') * 10) + (bufptr[4]-'0');
        sec     = ((bufptr[6]-'0') * 10) + (bufptr[7]-'0');
        sttime  = (hr*3600 + min*60 + sec) * STC_CLK;
        //lyc add 2006-3-15,for TCL more format .txt
        if( (bufptr[11]==0xB3)&&(bufptr[12]==0x30)&&
            (bufptr[13]==0x4E)&&(bufptr[14]==0x45)&&(bufptr[15]==0x4E))
       	     bufptr  += 8;
        
        bufptr  += 9;
        suptr   = bufptr;

        idxptr[1] = sttime;
        
#ifdef DBG_KEYFRAME
        printf( "st = %d, end = %d, offset = %d, cnt = %d\n", idxptr[0], idxptr[1], idxptr[2], idxptr[3] );
#endif      
        idxptr += 4;
        
        if( idxptr + 3 >= s_pSubIdxBaseEndPtr )
        {
#ifdef DBG_KEYFRAME
            printf( "Subpicture index buffer too small, can't record all index\n" );            
#endif            
            break;
        }
                
    } while (1);

TXT_END:

    s_pSupIdxPtr    = s_pSupIdxBasePtr;
    s_pSupIdxEnd    = idxptr;
    s_pSupBufPtr    = s_pSupBufPtr;

    printf("TXT subtitile initialized!! %x %x %x\n\n", s_pSupIdxPtr, s_pSupIdxEnd, s_pSupBufPtr );

    return 1;

TXT_ERROR:
    return 0;
}
static int ParsingSubtitleTXT_TXT_Two_USTimeData() 
{
	#ifdef DBG_KEYFRAME
     	  printf("*.txt format is  x:xx:xx:xx aa x:xx:xx:xx !,but no complete,pls tell lyc\n");
  #endif
  return 0;
}	
static int ParsingSubtitleTXT_TXT_Two_STimeData() 
{ 
	// get start time, xx:xx:xx:xx aa xx:xx:xx:xx format, aa=20 or aa=20 20 or aa=09
    UINT32  hr, min, sec,ms;
    UINT32  sttime,endtime;

    UINT32  uiByteRead  = s_uiSupBufSize;
    UINT32  uiOffset    = 0;
    BYTE*   base        = s_pSupBufPtr;
    BYTE*   bufend      = s_pSupBufEndPtr;
    BYTE*   bufptr      = base;
    BYTE*   suptr       = NULL;
    UINT32* idxptr      = s_pSupIdxBasePtr;
    BYTE    tbuf[11];
    while ( ( strncmp( (const char*) bufptr, "00:", 3 ) != 0 ) && ( strncmp( (const char*) bufptr, "0:",2 ) != 0 ) )
    {
        bufptr++;
        if( bufptr >= bufend )
            goto TXT_ERROR;
    }
    
    // parse subpicture
    do
    {
        if(( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT)&&(s_uiSupLen>s_uiSupBufSize)) //lyc update 2006-8-9;only fileszie>supbufsize,do supFillBuffer
        {            
            if( !supFillBuffer( &bufptr, &uiByteRead ) )
                break;

            uiOffset += ( s_uiSupBufSize - SUBTITLE_RELOAD_LIMIT );
        }
            
        while ( !_isdigit( *bufptr ) )
            bufptr++;

        if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )
            break;
      
        // error check omitted, should be "0x0D 0x0A" or "0x20"
        while ( _isspace(*bufptr) )
            bufptr++;

        // get start time, xx:xx:xx:xx format, 11 bytes
        memcpy(tbuf, bufptr, 11);
        bufptr += 11;

        hr =  ((_isdigit(tbuf[0]))?((tbuf[0]-'0') * 10) : 0) + (tbuf[1]-'0');
        min = ((_isdigit(tbuf[3]))?((tbuf[3]-'0') * 10) : 0) + (tbuf[4]-'0');
        sec = ((_isdigit(tbuf[6]))?((tbuf[6]-'0') * 10) : 0) + (tbuf[7]-'0');
        ms  = 0; 
        sttime = (hr*3600 + min*60 + sec) * STC_CLK + ms * MS_STC_CLK;


        // drop seperation, " space "
        while ( !_isdigit( *bufptr ) )
            bufptr++;

        // get end time, xx:xx:xx:xx format, 11 bytes
        memcpy(tbuf, bufptr, 11);
        bufptr += 11;

        hr =  ((_isdigit(tbuf[0]))?((tbuf[0]-'0') * 10) : 0) + (tbuf[1]-'0');
        min = ((_isdigit(tbuf[3]))?((tbuf[3]-'0') * 10) : 0) + (tbuf[4]-'0');
        sec = ((_isdigit(tbuf[6]))?((tbuf[6]-'0') * 10) : 0) + (tbuf[7]-'0');
        ms  = 0; 
        endtime = (hr*3600 + min*60 + sec) * STC_CLK + ms * MS_STC_CLK;

        while ( _isspace(*bufptr) ) // error check omitted, should be "0x0D 0x0A" or "0x20"
            bufptr++;
        if( strncmp( (const char*) bufptr, "{0 [1 ", 6 ) == 0 ) 
            bufptr+=6; 
        if( (strncmp( (const char*) bufptr, ",", 1 ) == 0)||( strncmp( (const char*) bufptr, "#", 1 ) == 0 )) 
            bufptr++; 
                
        suptr = bufptr;
       
        
        //while((!_iseol( bufptr ))&&(!IsSemiColumn( bufptr[2])||!_isdigit(bufptr[2])||!IsSemiColumn( bufptr[3])||!_isdigit(bufptr[3])||!IsSemiColumn( bufptr[4])||!_isdigit(bufptr[4])))
          while(!_iseol( bufptr ))
            bufptr++;       

       /*if(_iseol( bufptr ))  //perhaps in one str will insert "0X0D/0XOA"
        {
        	if( (((*(bufptr+1)>=23)&&(*(bufptr+1)<=127))||((*(bufptr+2)>=23)&&(*(bufptr+2)<=127)))&&(!_isdigit(bufptr+1))||(!_isdigit(bufptr+2)))
        	  {
        	  	bufptr+=2;
        	  	while( !_iseol( bufptr ) )
                  bufptr++;   
        	  } 	
        }
        */	
        *idxptr++ = sttime;
        *idxptr++ = endtime;
        *idxptr++ = suptr + uiOffset - base;
        *idxptr++ = bufptr - suptr;
        
#ifdef DBG_KEYFRAME
        printf( "st = %d, end = %d, offset = %d, cnt = %d\n", sttime, endtime, suptr + uiOffset - base, bufptr - suptr );
#endif      
        
        if( idxptr + 3 >= s_pSubIdxBaseEndPtr )
        {
#ifdef DBG_KEYFRAME
            printf( "Subpicture index buffer too small, can't record all index\n" );            
#endif            
            break;
        }
                
    } while (1);



    s_pSupIdxPtr    = s_pSupIdxBasePtr;
    s_pSupIdxEnd    = idxptr;
    s_pSupBufPtr    = s_pSupBufPtr;

    printf("TXT_TwoDataTime subtitile initialized!! %x %x %x\n\n", s_pSupIdxPtr, s_pSupIdxEnd, s_pSupBufPtr );

    return 1;

TXT_ERROR:
    return 0;
}

static int ParsingSubtitleTXT_TXT_OTHER() //denghg  add 2006-1-10 11:04     
{
	UINT32	hr, min, sec;
	UINT32	sttime;

	UINT32  uiByteRead  = s_uiSupBufSize;
	UINT32  uiOffset    = 0;
    BYTE*   base        = s_pSupBufPtr;
    BYTE*   bufend	    = s_pSupBufEndPtr;
    BYTE*   bufptr      = base;
    BYTE*   suptr       = NULL;
	UINT32* idxptr	    = s_pSupIdxBasePtr;
	
	
	while ( !_isdigit( *bufptr ) )
    {
        bufptr++;
        if( bufptr >= bufend )
            goto TXT_ERROR;
    }

	// get start time, x:xx:xx: format, 8 bytes
	if( !IsDigit( bufptr[0] ) ||  !IsSemiColumn( bufptr[1] ) ||
		!IsDigit( bufptr[2] ) || !IsDigit( bufptr[3] ) || !IsSemiColumn( bufptr[4] ) ||
		!IsDigit( bufptr[5] ) || !IsDigit( bufptr[6] ) || !IsSemiColumn( bufptr[7] ) )
		goto TXT_ERROR;

	hr		= bufptr[0]-'0' ;
	min		= ((bufptr[2]-'0') * 10) + (bufptr[3]-'0');
	sec		= ((bufptr[5]-'0') * 10) + (bufptr[6]-'0');
	sttime	= (hr*3600 + min*60 + sec) * STC_CLK;
	bufptr	+= 8;
	suptr	= bufptr;

	// parse subpicture
	do
	{
	    if(( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT)&&(s_uiSupLen>s_uiSupBufSize)) //lyc update 2006-8-9;only fileszie>supbufsize,do supFillBuffer
	    {            
	        if( !supFillBuffer( &bufptr, &uiByteRead ) )
	            break;

	        uiOffset += ( s_uiSupBufSize - SUBTITLE_RELOAD_LIMIT );
	    }
	    	    
		while( !_iseol( bufptr ) )
            bufptr++;
		
        if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )
            break;
		
		idxptr[0] = sttime;
	    
		idxptr[2] = suptr + uiOffset - base;
		idxptr[3] = bufptr - suptr /*- 2*/;//denghg modify no need -2 2006-3-9 15:19

		while ((*bufptr < '0') || (*bufptr > '9'))
		{
			bufptr++;

            if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )		
	        {
		        idxptr[1] = 0xffffffff;

                #ifdef DBG_KEYFRAME
                printf( "st = %d, end = %d, offset = %d, cnt = %d\n", idxptr[0], idxptr[1], idxptr[2], idxptr[3] );
                #endif

			    idxptr += 4;
			    goto TXT_END;
	        }
	    }

		hr		= bufptr[0]-'0'; //* 10) + (bufptr[1]-'0');
		min		= ((bufptr[2]-'0') * 10) + (bufptr[3]-'0');
		sec		= ((bufptr[5]-'0') * 10) + (bufptr[6]-'0');
		sttime	= (hr*3600 + min*60 + sec) * STC_CLK;
		bufptr	+= 8;
		suptr	= bufptr;
		
		
		idxptr[1] = sttime;
		
				
	#ifdef SUPPORT_TXTSUB_4S_OFF
        idxptr[1] = ( sttime > idxptr[0]+4 * STC_CLK ) ? idxptr[0]+4 * STC_CLK : sttime;
        #endif 
		
        
        #ifdef DBG_KEYFRAME
        printf( "st = %d, end = %d, offset = %d, cnt = %d\n", idxptr[0], idxptr[1], idxptr[2], idxptr[3] );
        #endif		
		idxptr += 4;
		
        if( idxptr + 3 >= s_pSubIdxBaseEndPtr )
        {
#ifdef DBG_KEYFRAME
            printf( "Subpicture index buffer too small, can't record all index\n" );            
#endif            
            break;
        }
        		
	} while (1);

TXT_END:

	s_pSupIdxPtr	= s_pSupIdxBasePtr;
	s_pSupIdxEnd	= idxptr;
	s_pSupBufPtr	= s_pSupBufPtr;

	printf("TXT subtitile initialized!! %x %x %x\n\n", s_pSupIdxPtr, s_pSupIdxEnd, s_pSupBufPtr );

	return 1;

TXT_ERROR:
	
 return 0;
}
#endif//#ifdef SUBTITLE_SUPPORT_TXT

#ifdef SUBTITLE_SUPPORT_TMplayerTXT
static int ParsingSubtitleTmPlayerTXT()
{
    UINT32  hr, min, sec;
    UINT32  sttime;

    UINT32  uiByteRead  = s_uiSupBufSize;
    UINT32  uiOffset    = 0;
    BYTE*   base        = s_pSupBufPtr;
    BYTE*   bufend      = s_pSupBufEndPtr;
    BYTE*   bufptr      = base;
    BYTE*   suptr       = NULL;
    UINT32* idxptr      = s_pSupIdxBasePtr;

    while ( !_isdigit( *bufptr ) )
    {
        bufptr++;
        if( bufptr >= bufend )
            goto TXT_ERROR;
    }

    // get start time, xx:xx:xx, format, 9 bytes
    if( !IsDigit( bufptr[0] ) || !IsDigit( bufptr[1] ) || !IsSemiColumn( bufptr[2] ) ||
        !IsDigit( bufptr[3] ) || !IsDigit( bufptr[4] ) || !IsSemiColumn( bufptr[5] ) ||
        !IsDigit( bufptr[6] ) || !IsDigit( bufptr[7] ) || !IsSemiColumn1( bufptr[8] ) )
        goto TXT_ERROR;
    
    hr      = ((bufptr[0]-'0') * 10) + (bufptr[1]-'0');
    min     = ((bufptr[3]-'0') * 10) + (bufptr[4]-'0');
    sec     = ((bufptr[6]-'0') * 10) + (bufptr[7]-'0');
    sttime  = (hr*3600 + min*60 + sec) * STC_CLK;
    //lyc add 2006-3-15,for TCL more format .txt
    if( strncmp( (const char*) bufptr, ".0:", 3 ) == 0 )
     bufptr  += 3;
     
    bufptr  += 11;
    suptr   = bufptr;

    // parse subpicture
    do
    {   
        if(( bufend - bufptr <= SUBTITLE_RELOAD_LIMIT)&&(s_uiSupLen>s_uiSupBufSize)) //lyc update 2006-8-9;only fileszie>supbufsize,do supFillBuffer
        {            
            if( !supFillBuffer( &bufptr, &uiByteRead ) )
                break;
            uiOffset += ( s_uiSupBufSize - SUBTITLE_RELOAD_LIMIT );
        }

        while( !_iseol( bufptr ) )
            bufptr++;

        if( _iseol_unix( bufptr ) )
            bufptr += 1;
        else
            bufptr += 2;

        while( !_iseol( bufptr ) )
            bufptr++;
                
        if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )
            break;
            
        idxptr[0] = sttime;
        idxptr[2] = suptr + uiOffset - base;
        idxptr[3] = bufptr - suptr - 11;
                        
        while ( !_isdigit( *bufptr ) )
        {
            bufptr++;

            if( (UINT32)( bufptr + uiOffset - base ) > s_uiSupLen )     
            {
                idxptr[1] = 0xffffffff;
                idxptr += 4;
                goto TXT_END;
            }
        }
        
        hr      = ((bufptr[0]-'0') * 10) + (bufptr[1]-'0');
        min     = ((bufptr[3]-'0') * 10) + (bufptr[4]-'0');
        sec     = ((bufptr[6]-'0') * 10) + (bufptr[7]-'0');
        sttime  = (hr*3600 + min*60 + sec) * STC_CLK;
        //lyc add 2006-3-15,for TCL more format .txt
        if( strncmp( (const char*) bufptr, ".0:", 3 ) == 0 )
            bufptr  += 3;
        bufptr  += 11;
        suptr   = bufptr;

        idxptr[1] = sttime;
        idxptr += 4;
        
        if( idxptr + 3 >= s_pSubIdxBaseEndPtr )
        {
            break;
        }

    } while (1);

TXT_END:

    s_pSupIdxPtr    = s_pSupIdxBasePtr;
    s_pSupIdxEnd    = idxptr;
    s_pSupBufPtr    = s_pSupBufPtr;

    printf("TXT subtitile initialized!! %x %x %x\n\n", s_pSupIdxPtr, s_pSupIdxEnd, s_pSupBufPtr );

    return 1;

TXT_ERROR:
    return 0;

    }
#endif//#ifdef SUBTITLE_SUPPORT_TMplayerTXT

// **************************************************************************************** //
extern int supFillSubtitleBuffer()
{
    UINT32  start       = s_uiSupStart;
    UINT32  end         = s_uiSupEnd;
    UINT32  supstart    = *(s_pSupIdxPtr+2);
    UINT32  supbcnt     = *(s_pSupIdxPtr+3);
    BYTE*   base        = s_pSupBufPtr;

    // check again
#ifdef DBG_FILL_SUBTITLE_BUFFER
    printf(" sup : %x %x %x %x\n", start, end, supstart, supbcnt);
#endif

    if( ( supstart < start ) || ( ( supstart + supbcnt ) > end ) )
    {
        // refill the buffer
        start       = supstart & (~0x7ff);
        UINT32 size = s_uiSupLen - start;

        if( size > s_uiSupBufSize )
            size = s_uiSupBufSize;

#ifdef DVD_SERVO        // 2005/04/30 yltseng
        extern UINT8 cServoWrongDataPass;
        cServoWrongDataPass = 0;
#endif
        FS_SetOutOfFileReading();
   #if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)//2005-8-24 17:23 zhoulin  
        UINT32 uiRtnVal = ran_read( base, l2msf( s_uiSupLba + start / ((media_type == MEDIA_CARD)?512:2048 )), size);
    #else
        UINT32 uiRtnVal = ran_read( base, l2msf( s_uiSupLba + start / 2048 ), size);
    #endif  
        FS_ResetOutOfFileReading();
#ifdef DVD_SERVO
        cServoWrongDataPass = 1;
#endif

        if( uiRtnVal != ATAPI_OK )
        {
#ifdef DBG_FILL_SUBTITLE_BUFFER
            printf("external subtitle read error!!\n");
#endif
            RESET_EXT_SUP();
            return 0;
        }

        s_uiSupStart    = start;
        s_uiSupEnd      = start + size;

#ifdef DBG_FILL_SUBTITLE_BUFFER
        printf(" sup load: %x %x %x %x\n", s_uiSupStart, s_uiSupEnd, supstart, supbcnt);
#endif
    }

    GOTDATA_EXT_SUP();
    return 1;
}

// **************************************************************************************** //
static int  supReplacePropertyString(char *pStr, int iSrcLen, const char* pStrSearch)
{
    int cnt = 0;
    if( !pStr || !pStrSearch || iSrcLen <= 0 )
        return 0;
    char* pEndStr = pStr + iSrcLen;
    char* pReplaceBegin = strinstr( pStr, pStrSearch, iSrcLen );
    if ( pReplaceBegin )
    {
        while ( pReplaceBegin <= pEndStr )
        {
            if( pReplaceBegin )
            {
                cnt++;
                while( *pReplaceBegin++ != '>')
                {
                    *( pReplaceBegin - 1 ) = '\n';
                }
                * ( pReplaceBegin -1 ) = '\n';
            }
            else
                return cnt;
            pReplaceBegin = strinstr( pReplaceBegin, pStrSearch, ( pEndStr - pReplaceBegin + 1 ) );
                        
        }
        return cnt;
    }
    
    return 0;    
}
#if defined (SUPPORT_SMI_MultiLanguage)||defined(SUPPORT_SMI_MultiColor)
//remove the date between <rt> and </ruby>,and keep the date <...>
static int  supReplacePropertyString_rt(char *pStr, int iSrcLen)
{
    int cnt = 0;
    if( !pStr||iSrcLen <= 0 )
        return 0;
    char* pEndStr = pStr + iSrcLen;
    while(pStr<=pEndStr)
    {
        if(*pStr=='<')
        {  if(strncmpIgnoreCase(  pStr, "<rt>", 4 )==0)
           {  
              pStr+=4;
              while(pStr<=pEndStr)
              {  while(*pStr!='<'&&pStr<=pEndStr)
                 {
                     
                    *pStr='\n';
                     pStr++;
                    
                 }

                 if(strncmpIgnoreCase(  pStr, "</ruby>", 7 )==0)
                 {  
                    cnt++; 
                    pStr+=7;
                    break;
                 }
                 else if(pStr<=pEndStr)
                 { 
                    while(*pStr!='>'&&pStr<=pEndStr)
                    {  
                       pStr++;
                    
                    }   
                    pStr++;
                 }
                 
             }
            
           }    
           else  pStr++;    
        }
        else pStr++;
    
    }
    
    return cnt;    
}
#endif
// **************************************************************************************** //
static int supReplaceSubString( char* pStr, int iSrcLen, const char* pStrSearch, const char* pStrReplace, int iMode )
{   // iMode == 0 -> replace first found substring
    // iMode == 1 -> replace all found substring

    if( !pStr || !pStrSearch || !pStrReplace || iSrcLen <= 0 )
        return 0;

    int     iCnt            = 0;
    char*   pReplaceBegin   = NULL;

    if( iMode == 0 )
    {
        if( ( pReplaceBegin = strinstr( pStr, pStrSearch, iSrcLen ) ) )
        {
            memcpy( pReplaceBegin, pStrReplace, strlen( pStrReplace ) );
            iCnt = 1;
        }
    }
    else
    {
        while( ( pReplaceBegin = strinstr( pStr, pStrSearch, iSrcLen ) ) )
        {
            iCnt++;
            memcpy( pReplaceBegin, pStrReplace, strlen( pStrReplace ) );
        }
    }

    return iCnt;
}

// **************************************************************************************** //
static inline void supModifyString( char* pStr, int iCnt )
{
    switch( s_uiSupType )
    {
    #ifdef SUBTITLE_SUPPORT_SRT //liumzh 2005-11-4 15:36
    case INTERNAL_SUBTITLE_SRT:
        supReplacePropertyString( pStr, iCnt, "<font");
        supReplacePropertyString( pStr, iCnt, "</font");
        supReplacePropertyString( pStr, iCnt, "</i");
        supReplacePropertyString( pStr, iCnt, "<i");
        break;
    #endif   
        
    #ifdef SUBTITLE_SUPPORT_SUB_SUBVIEWER
    case INTERNAL_SUBTITLE_SUB_SUBVIEWER:
        supReplaceSubString( pStr, iCnt, "[br]", "  \r\n", 1 );
        break;
    #endif
    
    #ifdef SUBTITLE_SUPPORT_SSA
    case INTERNAL_SUBTITLE_SSA:
        supReplaceSubString( pStr, iCnt, "\\N", " \n", 1 );
        break;
    #endif

    #ifdef SUBTITLE_SUPPORT_ASS
    case INTERNAL_SUBTITLE_ASS:
        supReplaceSubString( pStr, iCnt, "\\N", " \n", 1 );
        break;
    #endif

    #ifdef SUBTITLE_SUPPORT_SMI
    case INTERNAL_SUBTITLE_SMI:
        #if defined (SUPPORT_SMI_MultiLanguage)||defined(SUPPORT_SMI_MultiColor)//2005-8-16 20:38 zhoulin
        //add these to discard more tag
        //wangap 2005/1/25
        supReplaceSubString( pStr, iCnt, "&lt;", "\r\r\r<", 1 );
        supReplaceSubString( pStr, iCnt, "&gt;", ">\r\r\r", 1 );
        supReplaceSubString( pStr, iCnt, "&amp;", "\r\r\r\r&", 1 );
        supReplaceSubString( pStr, iCnt, "&quot;", "\r\r\r\r\r\x22", 1 );

        supReplaceSubString( pStr, iCnt, "\r\n", "\r\r", 1 );       
        supReplaceSubString( pStr, iCnt, "<BR>", " \r\n ", 1 );
        supReplaceSubString( pStr, iCnt, "<Br>", " \r\n ", 1 );
        supReplaceSubString( pStr, iCnt, "<br>", " \r\n ", 1 );
        supReplaceSubString( pStr, iCnt, "&nbsp;", "\r\r\r\r\r\r", 1 );
        supReplaceSubString( pStr, iCnt, "&ensp;", "\r\r\r\r\r ", 1 );
        supReplaceSubString( pStr, iCnt, "&emsp;", "\r\r\r\r  ", 1 );
        
        supReplacePropertyString_rt( pStr, iCnt);
        supReplaceSubString( pStr, iCnt, "<ruby>", "\r\r\r\r\r\r", 1 );
        supReplaceSubString( pStr, iCnt, "</ruby>", "\r\r\r\r\r\r\r", 1 );
        supReplaceSubString( pStr, iCnt, "<rt>", "\r\r\r\r", 1 );
        supReplacePropertyString( pStr, iCnt, "<b");
        supReplacePropertyString( pStr, iCnt, "</b");
        supReplacePropertyString( pStr, iCnt, "<B");
        supReplacePropertyString( pStr, iCnt, "</B");        
        supReplacePropertyString( pStr, iCnt, "<i");
        supReplacePropertyString( pStr, iCnt, "</i");
        supReplacePropertyString( pStr, iCnt, "<I");
        supReplacePropertyString( pStr, iCnt, "</I");
        supReplacePropertyString( pStr, iCnt, "<u");
        supReplacePropertyString( pStr, iCnt, "</u");
        supReplacePropertyString( pStr, iCnt, "<U");
        supReplacePropertyString( pStr, iCnt, "</U");
        supReplacePropertyString( pStr, iCnt, "<H1");
        supReplacePropertyString( pStr, iCnt, "</H1");
        supReplacePropertyString( pStr, iCnt, "<h1");
        supReplacePropertyString( pStr, iCnt, "</h1");
        supReplacePropertyString( pStr, iCnt, "<H2");
        supReplacePropertyString( pStr, iCnt, "</H2");
        supReplacePropertyString( pStr, iCnt, "<h2");
        supReplacePropertyString( pStr, iCnt, "</h2");
        supReplacePropertyString( pStr, iCnt, "<H3");
        supReplacePropertyString( pStr, iCnt, "</H3");
        supReplacePropertyString( pStr, iCnt, "<h3");
        supReplacePropertyString( pStr, iCnt, "</h3");
        supReplacePropertyString( pStr, iCnt, "<H4");
        supReplacePropertyString( pStr, iCnt, "</H4");
        supReplacePropertyString( pStr, iCnt, "<h4");
        supReplacePropertyString( pStr, iCnt, "</h4");
        supReplacePropertyString( pStr, iCnt, "<H5");
        supReplacePropertyString( pStr, iCnt, "</H5");
        supReplacePropertyString( pStr, iCnt, "<h5");
        supReplacePropertyString( pStr, iCnt, "</h5");
        supReplacePropertyString( pStr, iCnt, "<H6");
        supReplacePropertyString( pStr, iCnt, "</H6");
        supReplacePropertyString( pStr, iCnt, "<h6");
        supReplacePropertyString( pStr, iCnt, "</h6");
 
        supReplacePropertyString( pStr, iCnt, "<Span");
        supReplacePropertyString( pStr, iCnt, "<SPAN");
        supReplacePropertyString( pStr, iCnt, "<span");
        supReplacePropertyString( pStr, iCnt, "<Show");
        supReplacePropertyString( pStr, iCnt, "<SHOW");
        supReplacePropertyString( pStr, iCnt, "<show");
       #ifndef SUPPORT_SMI_MultiColor        
        supReplacePropertyString( pStr, iCnt, "<Font");
        supReplacePropertyString( pStr, iCnt, "<font");
        supReplacePropertyString( pStr, iCnt, "<FONT");
        supReplacePropertyString( pStr, iCnt, "</Font");
        supReplacePropertyString( pStr, iCnt, "</font");
        supReplacePropertyString( pStr, iCnt, "</FONT");
       #endif
       #ifndef SUPPORT_SMI_MultiLanguage
       supReplacePropertyString( pStr, iCnt, "<p");
        supReplacePropertyString( pStr, iCnt, "<P");
       #endif
       #else
        supReplaceSubString( pStr, iCnt, "<br>", "  \r\n", 1 );
        supReplaceSubString( pStr, iCnt, "&nbsp;", "\r\r\r\r\r\r", 1 );
        supReplaceSubString( pStr, iCnt, "<ruby>", "\r\r\r\r\r\r", 1 );
        supReplaceSubString( pStr, iCnt, "</ruby>", "\r\r\r\r\r\r\r", 1 );
        supReplaceSubString( pStr, iCnt, "<rt>", "\r\r\r\r", 1 );
        supReplaceSubString( pStr, iCnt, "<b>", "\r\r ", 1 );
        supReplaceSubString( pStr, iCnt, "</b>", "\r\r\r ", 1 );
        supReplacePropertyString( pStr, iCnt, "<font color");
        supReplacePropertyString( pStr, iCnt, "</font");
        supReplacePropertyString( pStr, iCnt, "</FONT");
      #endif  
        break;
    #endif

    #if defined( SUBTITLE_SUPPORT_PSB ) || defined( SUBTITLE_SUPPORT_SUB_MICRODVD ) || defined( SUBTITLE_SUPPORT_TXT )
    case INTERNAL_SUBTITLE_SUB_MICRODVD:
    case INTERNAL_SUBTITLE_PSB:
    case INTERNAL_SUBTITLE_TXT:
        supReplaceSubString( pStr, iCnt, "|", "\n", 1 );
        break;
    #endif
    }
}

// **************************************************************************************** //
static void supGetSubtitleDataTXT( UINT32 uiCurTime, void** pData, UINT32* pSize )
{   
    *pData  = (void*) NULL;
    *pSize  = 0;

    //if (!IS_EXT_SUP_INITIALIZED())
    if (!IS_EXT_SUP_ACTIVATED())
        return;
   
    UINT32* idxptr  = s_pSupIdxPtr;
    UINT32* idxend  = s_pSupIdxEnd;
    UINT32  sttime  = *idxptr;
#if defined (SUPPORT_SMI_MultiLanguage)||defined(SUPPORT_SMI_MultiColor)    

    UINT32  endtime=0;
    if(SmiSupType)
    {   if(*(idxptr+1)==0)
          endtime = *(idxptr+4);
        else if(*(idxptr+1)==0xffffffff) 
          endtime = 0xffffffff;
    }
    else   
      endtime = *(idxptr+1);
#else
    UINT32  endtime = *(idxptr+1);
#endif      
    
    if( uiCurTime >= sttime )
    {
        if( uiCurTime < endtime )       // time to display
        {
            UINT32  start       = s_uiSupStart;
            UINT32  end         = s_uiSupEnd;
            UINT32  supstart    = *(idxptr+2);
            UINT32  supbcnt     = *(idxptr+3);
            BYTE*   base        = s_pSupBufPtr;

            // check if in the ext_sup buffer
            if( ( supstart < start ) || ( ( supstart + supbcnt ) > end ) )
            {
#ifdef DBG_GET_CURRENT_STR
                printf("need data!!: %x %x %x %x\n", start, end, supstart, supbcnt);
#endif
                NEEDDATA_EXT_SUP();
                return;
            }

            BYTE* ptr = base + supstart - start;
            
        #if defined (SUPPORT_SMI_MultiLanguage)
            BYTE* bptr=ptr;
            UINT16 cnt=0; 
            if(lang_num>1&&SmiSupType)       //if the frame have the current language data,to display the frame
            {                                //otherwise to display last frame
                while(cnt<supbcnt)
                {
                    if(*bptr=='<'&&(*(bptr+1)=='P'||*(bptr+1)=='p'))
                    {  
                        while(*bptr!='='&&cnt<supbcnt)
                        {
                           cnt++;
                           bptr++;
                        }               
                        cnt++;
                        bptr++;
                        if(strncmpIgnoreCase( bptr,lang_temp[nowSupLang], strlen((const char*)lang_temp[nowSupLang]) )==0)
                        {    supModifyString( ptr, supbcnt ); 
                            *pData = ptr;
                             *pSize = supbcnt;
                            
                             return;
                        }
                        
                    }
                    cnt++;
                    bptr++; 
                }
            }
            else
        #endif
            {  
            supModifyString( ptr, supbcnt );

            *pData = ptr;
            *pSize = supbcnt;
            } 
            

#ifdef DBG_GET_CURRENT_STR  //2004/09/03 yltseng
            char aTmp[256];
            memcpyS( aTmp, ptr, supbcnt > 256 ? 256 : supbcnt );
            printf( "time %d, cnt %d, str %s\n", uiCurTime, supbcnt, aTmp );
#endif
            return;
        }
    }

    // check if waiting for display
    if( uiCurTime < sttime )
    {
        // first entry
        if( idxptr == s_pSupIdxBasePtr )
            return;

        // the previous one has been displayed
        #if defined (SUPPORT_SMI_MultiLanguage)||defined(SUPPORT_SMI_MultiColor)//2005-8-16 20:38 zhoulin
        if(( uiCurTime > *( idxptr - EXTSUPENTRYSIZE ) &&SmiSupType)
            ||(uiCurTime > *( idxptr - EXTSUPENTRYSIZE + 1 )&&!SmiSupType))
        #else
        if( uiCurTime > *( idxptr - EXTSUPENTRYSIZE + 1 ) ) // previous end time
        #endif
            return;
    }

    // check if index finished
    //if( idxptr >= ( idxend - EXTSUPENTRYSIZE ) )
    if( (UINT32) idxptr >= ( (UINT32) idxend - EXTSUPENTRYSIZE ) )//fix sometime no subtitle displays   yltseng help to fix  denghg 2005-8-22 16:47  
        return;

    // sync to current point
    UINT32 found = 1;
    idxptr = s_pSupIdxBasePtr + EXTSUPENTRYSIZE;
    while( *idxptr < uiCurTime )
    {
        if( idxptr >= idxend ) 
        {
            found = 0;
            break;
        }

        idxptr += EXTSUPENTRYSIZE;
    }

    if( found )
    {
        s_pSupIdxPtr = idxptr - EXTSUPENTRYSIZE;
        // check if in the sup buffer
    }

    return;
}
// **************************************************************************************** //
#if defined( SUBTITLE_SUPPORT_SUB_MICRODVD ) || defined( SUBTITLE_SUPPORT_SUB_SUBVIEWER )
static int ParsingSubtitleSUB()
{
    BYTE*   bufptr  = s_pSupBufPtr;

    while( _isspace( *bufptr ) )
        bufptr++;

    if( *bufptr == '[' )
    {
        s_uiSupType = INTERNAL_SUBTITLE_SUB_SUBVIEWER;
        return ParsingSubtitleSUB_SubViewer();
    }
    else if( *bufptr == '{' )
    {
        s_uiSupType = INTERNAL_SUBTITLE_SUB_MICRODVD;
        return ParsingSubtitleSUB_MicroDVD();
    }
    #ifdef SHOW_UNSUPPORTED_SUBTITLE //zxb 2006-5-12 16:51
   	else if(disp_time > 0)     
   	{              
    	psprintf(RegionValStr[1], ":[UNSUPPORTED]");
    	PrintOsdMsg(109, 1, 1, 1);		              	
    }           
    #else
    else 
      Is_Support_FormatS=1; //lyc add for check if support subtitle format
      // pDSV->dAv_SPST_Ns--;//shenyj add for alco "下一站天后"disc include .sub subtitle,but we can't support 2006/02/17
    #endif
    return 0;
}
#endif

// **************************************************************************************** //
static inline int supParseSubtitle( int iAVIFile, int iSubFile )
{ // 2004/01/31 yltseng, when subtitle to the same file of previous, we don't have to reinitialize
    int iSubFileIdx;    
    if( ( iSubFileIdx = supGetNthSubtitle( iAVIFile, iSubFile ) ) < 0 )
        goto error_sup;

    int iArrayIdx               =   subtitle_array[ iSubFileIdx ].uiType;
    s_uiSupType                 =   s_aSubtitleInfo[ iArrayIdx ].uiInternalType;
    s_pfnParsingSubtitleFunc    =   s_aSubtitleInfo[ iArrayIdx ].pfnParsingSubtitleFunc;
    s_pfnGetSubtitleData        =   s_aSubtitleInfo[ iArrayIdx ].pfnGetSubtitleData;

// When Changing subtitle initiallization flowchart.
// we should parser two times and check s_supParseAgain.
/*
    if((s_uiSupType == INTERNAL_SUBTITLE_SUB_MICRODVD))
    {
    	if(s_supParseAgain == 0)
    	{
	        //printf_w("load subviewer or microdvd subtitle, should be load again, return \n\n");
	        s_supParseAgain = 1;
	        return FALSE;
    	}
		else
			s_supParseAgain = 0;		
    }
	else
	{
		if(	s_supParseAgain == 0)
			s_supParseAgain = 1;
		else
		{
			s_supParseAgain = 0;
			return FALSE;
		}
	}
*/

#if defined (SUPPORT_SMI_MultiLanguage)||defined(SUPPORT_SMI_MultiColor)//2005-8-16 20:38 zhoulin    
    SmiSupType=0;                          //set smi flag
    if(s_uiSupType==INTERNAL_SUBTITLE_SMI)
      SmiSupType=1;
#endif 
    if( 
#if !( defined(SDRAM_16Mb_Mode) && defined(TURBO_DECODE) )  
        // in 8202D 16M turbo decode, sup buffer overlaps CDROM code, so we have to refresh subtitle buffer every time.
        ( s_uiSupLba      == subtitle_array[ iSubFileIdx ].loc &&
          s_uiSupLen      == subtitle_array[ iSubFileIdx ].size && 
          IS_EXT_SUP_INITIALIZED() ) ||
#endif
          supParseSubtitleEntry( iSubFileIdx )
      )
    {
        INITIALIZE_EXT_SUP();
        return s_aSubtitleInfo[ iArrayIdx ].uiExternalType;
    }

error_sup:

    s_uiSupType = INTERNAL_SUBTITLE_UNKNOWN;
    RESET_EXT_SUP();
    return EXT_SUBTITLE_UNKNOWN;
}

// **************************************************************************************** //
extern void supResetSubtitleFileInfo()
{
    s_uiSupCnt = 0;
}

// **************************************************************************************** //
extern void supResetSubtitleMatchBuffer()
{
    (SUBTITLE_TEMP_DATA*) s_pSupBufPtr = (SUBTITLE_TEMP_DATA*) MATCHBUFSTART;
}

// **************************************************************************************** //
extern void supAddVideoFileInfo( UINT32 uiIndex, UINT32 uiType, const char* pName )
{
    if( !pName )
        return;
    //#ifndef MP3_TXT_DISPLAY //xujf-060916 we play a customer's mp3 disc,system reset.
    //if(pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
	//    return;
    //#endif   //lyc 2006-09-29 mark it, find the true reason which cause the problem.

    if( s_pSupBufPtr + sizeof( SUBTITLE_TEMP_DATA ) >= (BYTE*) MATCHBUFEND )
        return;

    const char* pExtBegin = strrchr( pName, '.' );
    if( !pExtBegin || !( pExtBegin + 1 ) )
        return;
  
    int iNameLen = ( pExtBegin - pName ) <= 128 ? ( pExtBegin - pName ) : 128;

    SUBTITLE_TEMP_DATA* pAddr = (SUBTITLE_TEMP_DATA*) s_pSupBufPtr;
    strncpy( pAddr->aName, pName, iNameLen );
    pAddr->aName[ iNameLen ] = '\0';
    
    pAddr->uiIndex  = uiIndex;
    pAddr->uiType   = uiType;

    ((SUBTITLE_TEMP_DATA*) s_pSupBufPtr)++;
}

// **************************************************************************************** //
#endif  // SUPPORT_MP4_SUBTITLE
