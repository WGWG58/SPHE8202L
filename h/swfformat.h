#define typebtn 0
#define typebmp 1
#define typeact 2
#define typempg1 3  //()
#define typempg2 4  //()
#define typesprite 5
#define typeEventsn 6
#define typesprite2 7
#define STACKSIZE 50
typedef struct s_swfInfo
{   char head[4];
    int totalframes;
    int framesloaded;
    int visible;
    int width;
    int height;
    int scrwidth;
    int scrheight;
    int objcount;
    
    int btncount;
    int bmpcount;
    int spritecount;
    int actcount;
    int mpgcount;
    int EventSnCount;
    
    int nFramerate;
    int Version;
    
    int btnindex;//Param1;
    int btnnum;
    int mpg1index;
    int mpg1num;
    int mpg2index;
    int mpg2num;
    int actindex;
    int actnum;
    int spriteindex;
    int Eventsnindex;
    int Eventsnnum;
    int totalview;
    int EventsnStart;
    int EventsnCount;
    int sprite2index;
    int startpos;
    int Param17;
    int Param18;
    int Param19;
    int Param20;
}swfInfo;
//indexlength =5 if more than 5 show error
typedef struct s_S_IDX {
	short int type;				//2
	short int sindex;  //=0 all sceen	//2              
	unsigned short start_sec;		//4		action start address
	unsigned short end_sec;				//4
	unsigned short param1;				//4 startframe of mpg;action currentframe
	unsigned short param2;				//4 endframe of mpg;action actid
	unsigned short param3;				//4 action acttype
	unsigned short param4;				//4 action actlength
	unsigned short param5;
	unsigned short param6;
	unsigned short param7;
	unsigned short param8;
	unsigned short param9;
	unsigned short paramA;
}S_IDX;	
/*typedef struct sButtonInfoHead
{
unsigned long actionoffset;			//4
unsigned long actionlength;			//4
unsigned long bkcolor;				//4
unsigned long bmptop;				//4
unsigned long bmpleft;				//4
unsigned long bmpwidth;				//4
unsigned long bmpheight;			//4
unsigned long bmpoffset;			//4
unsigned long bmpfilelength;			//4
}ButtonInfoHead;*/
typedef struct sButtonInfoHead
{
//unsigned long actionoffset;			//4
//unsigned long actionlength;			//4
unsigned long bkcolor;				//4
unsigned short bmptop;				//4
unsigned short bmpleft;				//4
unsigned short bmpwidth;				//4
unsigned short bmpheight;			//4
unsigned long bmpoffset;			//4
unsigned long bmpfilelength;			//4
}ButtonInfoHead;
typedef struct sRECT
{
unsigned short x;				//4
unsigned short y;				//4
unsigned short w;				//4
unsigned short h;
}mRect;
typedef struct sTButtonInfoHead
{
unsigned long validsize;
unsigned long soundoffset;
unsigned long soundlength;
unsigned long actionoffset;			//4
unsigned long actionlength;			//4
ButtonInfoHead mybtninfo[4];
}TButtonInfoHead; 
typedef struct sSpriteInfoHead
{	
unsigned long reswidth;
unsigned long resheight;
unsigned long datapos;
unsigned long bmpfilelength;    
}SpriteInfoHead;
enum
{spritenotexist	=0,
 spritecanclear=1,
 spritecandraw=2,
 spritemustclear=3,
 spritemustdraw=4,
 spritedrawnext=5,
 spritestop=6,
  spritecanmove=0xff,
};
typedef struct sSpriteInfoHead2
{       unsigned long namelength;      //4
        char instancename[16];
        short	int param1;		//2  	frame
        short	int param2;		//2	statas
}SpriteInfoHead2;
typedef struct sSpriteInfoHeadframe2
{      
        long 	refleft;//Ïà¶ÔÆ«ÒÆ
        long	reftop;
        unsigned long reswidth;
	unsigned long resheight;
	
	unsigned long datapos;
	unsigned long bmpfilelength; 
}SpriteInfoHeadframe2;
enum
{       obj_int=0,
        obj_float= 1,
        obj_boolean=2,
        obj_string=3,
        //obj_point=2,
        obj_object=4,
        //obj_class=3,
        //obj_event=4,
        obj_movie=5,
        //obj_pic=6,
        obj_null=6,
        obj_undefined=7,
        obj_function=8
        //obj_bool=8
};
// Action codes
enum
{
    sactionNone                     = 0x00,
    sactionNextFrame                = 0x04,
    sactionPrevFrame                = 0x05,
    sactionPlay                     = 0x06,
    sactionStop                     = 0x07,
    sactionToggleQuality            = 0x08,
    sactionStopSounds               = 0x09,
    sactionAdd                      = 0x0A,
    sactionSubtract                 = 0x0B,
    sactionMultiply                 = 0x0C,
    sactionDivide                   = 0x0D,
    sactionEqual                    = 0x0E,
    sactionLessThan                 = 0x0F,
    sactionLogicalAnd               = 0x10,
    sactionLogicalOr                = 0x11,
    sactionLogicalNot               = 0x12,
    sactionStringEqual              = 0x13,
    sactionStringLength             = 0x14,
    sactionSubString                = 0x15,
    sactionPop			    = 0x17,
    sactionInt                      = 0x18,
    sactionGetVariable              = 0x1C,
    sactionSetVariable              = 0x1D,
    sactionSetTargetExpression      = 0x20,
    sactionStringConcat             = 0x21,
    sactionGetProperty              = 0x22,
    sactionSetProperty              = 0x23,
    sactionDuplicateClip            = 0x24,
    sactionRemoveClip               = 0x25,
    sactionTrace                    = 0x26,
    sactionStartDragMovie           = 0x27,
    sactionStopDragMovie            = 0x28,
    sactionStringLessThan           = 0x29,
    sactionRandom                   = 0x30,
    sactionMBLength                 = 0x31,
    sactionOrd                      = 0x32,
    sactionChr                      = 0x33,
    sactionGetTimer                 = 0x34,
    sactionMBSubString              = 0x35,
    sactionMBOrd                    = 0x36,
    sactionMBChr                    = 0x37,
    sactionDelete                   = 0x3a,
    sactionDelete2                  = 0x3b,
    sactionDefineLocal              = 0x3c,
    sactionReturn                   = 0x3e,
    sactionModulo                   = 0x3f,
    sactionNewObject                = 0x40,
    sactionDefineLocal2             = 0x41,
//    sactionInitArray                = 0x42,
    sactionTypeOf                   = 0x44,
    sactionTargetPath               = 0x45,
    sactionEnumerate                = 0x46,
    sactionAdd2                     = 0x47,
    sactionLess2                    = 0x48,
    sactionEquals2                  = 0x49,
    sactionToNumber                 = 0x4a,
    sactionToString                 = 0x4b,
    sactionPushDuplicate            = 0x4c,
    sactionStackSwap                = 0x4d,
    sactionGetMember                = 0x4e,
    sactionSetMember                = 0x4f,
    sactionIncrement                = 0x50,
    sactionDecrement                = 0x51,
    sactionEnumerate2               = 0x55,
    sDoInitAction                   = 0x59,
    sactionBitAnd                   = 0x60,
    sactionBitOr                    = 0x61,
    sactionBitXor                   = 0x62,
    sactionBitLShift                = 0x63,
    sactionBitRShift                = 0x64,
    sactionBitURShift               = 0x65,
    sactionGreater                  = 0x67,
    sactionStringGreater            = 0x68,
    sactionHasLength                = 0x80,
    sactionGotoFrame                = 0x81, // frame num (WORD)
    sactionGetURL                   = 0x83, // url (STR), window (STR)
    sactionStoreRegister	    = 0x87,
    sactionConstantPool             = 0x88, //flash5
    sactionWaitForFrame             = 0x8A, // frame needed (WORD),
                                            // actions to skip (BYTE)
    
    sactionSetTarget                = 0x8B, // name (STR)
    sactionGotoLabel                = 0x8C, // name (STR)
    sactionWaitForFrameExpression   = 0x8D, // frame needed on stack,
                                            // actions to skip (BYTE)
    sactionPushData                 = 0x96,
    sactionBranchAlways             = 0x99,
    sactionGetURL2                  = 0x9A,
    sactionBranchIfTrue             = 0x9D,
    sactionCallFrame                = 0x9E,
    sactionGotoExpression           = 0x9F,
    sactionMyMovie		    =0xaa,
};

typedef struct sobj_data
{     int i_v;
      int f_v_dec;//4.4
      int f_v_int;
      unsigned char *p_v;
      void *b_v;
}Actobj_data;
typedef struct sActBase_obj
{
   unsigned char name[20];//={0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 ,0,0,0,0,0};
   unsigned char type;
   Actobj_data u;
   void *next;
}ActBase_obj;


