#include "user_init.h"

#ifdef SUPPORT_CARD_STORAGE

#include "global.h"
#include "ata.h"
#include "atapi_if.h"
#include "emuio.h"
#include "func.h"
#include "memmap.h"
#include "cderr.h"
#include "cardfs.h"

//#ifndef GBM_CARD_READER
#if !defined(GBM_CARD_READER)&& !defined(HJ023_CARD_READER)&& !defined(QSI_PORTABLE_DVD)
#define CARD_RESET_INVERSE
#endif

//extern void dac_turn_on();
extern int  font_decompress(void);
//2004AUDDRV extern void DSPReset();
extern void flush_atapi(void);

//#define CARDIF_DBG

extern BYTE    idIDECard;

BYTE    iThCardPlugged=0; //Jeff 20021231

void SetCardCs1Cs2Enable(void)//kenny 200212/26 , enable 74HC367, let card's CS1,CS2 enable
{

    #ifdef CARD_HOT_PLUG
        #ifdef CARD_RESET_INVERSE
            regs0->gpio_oe[CARD_RESET_PIN/16] &= ~(0x1<<(CARD_RESET_PIN%16)); //input mode 
            delay_srv_10ms(10);
        #else
            regs0->gpio_oe[CARD_RESET_PIN/16] |= (0x1<<(CARD_RESET_PIN%16)); //output mode  
            regs0->gpio_out[CARD_RESET_PIN/16] &= ~(0x1<<(CARD_RESET_PIN%16));//output LOW to GPIO17
            delay_srv_10ms(10);
        #endif
    #endif

}

//kenny move polling card plug in or not from polling.c 2002/12/26
void polling_card_plug(void)
{
    if (media_type == MEDIA_CARD) {
        if (resumeMSF!=0) {
            resumeMSF = 0;
        }
    }

    if ( //(system_state!=SYSTEM_BROWSE) && //kenny mark it 2003/1/26
        ( !(card_plug_state&CARD_HAD_PLUGGED_IN) ) &&
        CARDIsPlugIn()
       )//User do plug-in action 
    {
        card_plug_state |= USER_DO_PLUG_IN;//clear this flag in CardTestReady()
    }

    if( !CARDIsPlugIn() )
    {
        #ifdef CARD_HOT_PLUG
            #ifdef CARD_RESET_INVERSE
                regs0->gpio_oe[CARD_RESET_PIN/16] |= (0x1<<(CARD_RESET_PIN%16)); //output mode  
                regs0->gpio_out[CARD_RESET_PIN/16] &= ~(0x1<<(CARD_RESET_PIN%16));//output LOW to GPIO17
            #else
                #ifndef QSI_PORTABLE_DVD
                regs0->gpio_oe[CARD_RESET_PIN/16] &= ~(0x1<<(CARD_RESET_PIN%16)); //input mode               
                #else
                   regs0->gpio_oe[CARD_RESET_PIN/16] |= (0x1<<(CARD_RESET_PIN%16)); //output mode  
            	   regs0->gpio_out[CARD_RESET_PIN/16] |= (0x1<<(CARD_RESET_PIN%16));//output HIGH               
            	#endif
            #endif
        #endif

        if(card_plug_state&CARD_HAD_PLUGGED_IN)//kenny 2003/1/23
        card_plug_state|=USER_DO_PLUG_OUT;
        
        card_plug_state&=~CARD_HAD_PLUGGED_IN;
    } else {
        card_plug_state&=~USER_DO_PLUG_OUT;
        card_plug_state|=CARD_HAD_PLUGGED_IN;
    }
    
    //printf("S1=%x M1=%d \n",card_plug_state,media_type);
    
} 

#ifdef IDE_DIAGNOSTIC
//yw 030303
void CardTestReady()
{

//==============================================
//for QSI source switch		//added by JS	//20040726
#ifdef SUPPORT_QSI_SOURCE_SWITCH
	if (source_type_now!= source_card) {
		return;
	} 		
#endif
//==============================================



  #ifdef __MAIN_MENU__ 
  if(CARD_MASTER)
  	{
//  	  if ( CardIsExist() ) {
  	  if ( FSIsExist() ) {
        #ifdef CARDIF_DBG
        printf("STSTEM STATE=%d:Card Exist\n",system_state);
        #endif

        CardSetBrowse();    //Maoyong 2004.05.18
        //dac_turn_on(); 
        card_plug_state&=~USER_DO_PLUG_IN;//kenny 2002/11/12
        card_plug_state|=CARD_HAD_PLUGGED_IN;//kenny 2002/11/12
        //printf("2.card_plug_state=%x\n",card_plug_state);
        } else {
        #ifdef CARDIF_DBG
        printf("STSTEM STATE=%d:Card not Foundt\n",system_state);
        #endif

        CardReset();

        if (idIDECard != IDE_MASTER_ID) { //Jeff 20021206
            media_type = MEDIA_CD;
        }
      }
  	}
  else
  	{
//      if(CardIsExist()){
      if(FSIsExist()){
          ClearOsdMsg(1);
          //dac_turn_on();
          card_plug_state &= ~USER_DO_PLUG_IN;
          card_plug_state |= CARD_HAD_PLUGGED_IN;
      } else
      {
        CardReset();

        if(idIDECard != IDE_MASTER_ID){
            //media_type = MEDIA_CD;
        }
      }
  	}  
  #else
//    if ( CardIsExist() ) {
    if ( FSIsExist() ) {
        #ifdef CARDIF_DBG
        printf("STSTEM STATE=%d:Card Exist\n",system_state);
        #endif

        CardSetBrowse(); 
        //dac_turn_on(); 
        card_plug_state&=~USER_DO_PLUG_IN;//kenny 2002/11/12
        card_plug_state|=CARD_HAD_PLUGGED_IN;//kenny 2002/11/12
        //printf("2.card_plug_state=%x\n",card_plug_state);
    } else {
        #ifdef CARDIF_DBG
        printf("STSTEM STATE=%d:Card not Found\n",system_state);
        #endif

        CardReset();

        if (idIDECard != IDE_MASTER_ID) { //Jeff 20021206
            media_type = MEDIA_CD;
        }
    }
  #endif

}

#else

void CardTestReady()
{

//==============================================
//for QSI source switch		//added by JS	//20040726
#ifdef SUPPORT_QSI_SOURCE_SWITCH
	if (source_type_now!= source_card) {
		return;
	} 		
#endif
//==============================================
		
  #if defined(__MAIN_MENU__) && !defined(CARD_MASTER)
//    if(CardIsExist()){
    if(FSIsExist()){
        ClearOsdMsg(1);

        //dac_turn_on();

        card_plug_state &= ~USER_DO_PLUG_IN;
        card_plug_state |= CARD_HAD_PLUGGED_IN;
    } else
    {
        CardReset();

        if(idIDECard != IDE_MASTER_ID){
            //media_type = MEDIA_CD;
        }
    }
  #else
//    if ( CardIsExist() ) {
    if ( FSIsExist() ) {

        #ifdef CARDIF_DBG
        printf("STSTEM STATE=%d:Card Exist\n",system_state);
        #endif

        flush_atapi();

        CardSetBrowse();
        //dac_turn_on(); 
        card_plug_state&=~USER_DO_PLUG_IN;//kenny 2002/11/12
        card_plug_state|=CARD_HAD_PLUGGED_IN;//kenny 2002/11/12
        //printf("2.card_plug_state=%x\n",card_plug_state);
        
    } else {
        #ifdef CARDIF_DBG
        printf("STSTEM STATE=%d:Card not Foundt\n",system_state);
        #endif

        CardReset();

        if (idIDECard != IDE_MASTER_ID) { //Jeff 20021206
            media_type = MEDIA_CD;
        }
    }
  #endif

}
#endif

/* yw 030306
void CardTestReady()
{
#if defined(__MAIN_MENU__) && !defined(CARD_MASTER)
//    if(CardIsExist()){
    if(FSIsExist()){
        ClearOsdMsg(1);

        //dac_turn_on();

        card_plug_state &= ~USER_DO_PLUG_IN;
        card_plug_state |= CARD_HAD_PLUGGED_IN;
    } else
    {
        CardReset();

        if(idIDECard != IDE_MASTER_ID){
            //media_type = MEDIA_CD;
        }
    }
#else
//    if ( CardIsExist() ) {
    if ( FSIsExist() ) {
        #ifdef CARDIF_DBG
        printf("STSTEM STATE=%d:Card Exist\n",system_state);
        #endif

        ClearOsdMsg(1);
        browser = read_iso9660;
        cd_type_loaded=CDROM;
        cd_type=CDROM;
        play_state=VCD_STATE_CLOSE;
        system_state=SYSTEM_BROWSE;
        sys_cmd=CMD_FUNC|CMD_FUNC_CLOSE;
        media_type = MEDIA_CARD; 
        //dac_turn_on(); 
        card_plug_state&=~USER_DO_PLUG_IN;//kenny 2002/11/12
        card_plug_state|=CARD_HAD_PLUGGED_IN;//kenny 2002/11/12
        //printf("2.card_plug_state=%x\n",card_plug_state);
    } else {
        #ifdef CARDIF_DBG
        printf("STSTEM STATE=%d:Card not Foundt\n",system_state);
        #endif

        CardReset();

        if (idIDECard != IDE_MASTER_ID) { //Jeff 20021206
            media_type = MEDIA_CD;
        }
    }
#endif
}
*/  
  
int CARDIsPlugIn()
{

#ifdef CARD_HOT_PLUG
    
    BYTE    newCardPlugged=0;


//==============================================
//for QSI source switch		//added by JS	//20040726
#ifdef SUPPORT_QSI_SOURCE_SWITCH
	if (source_type_now!= source_card) {
		return 0;
	} 		
#endif
//==============================================

        
    if ( (regs0->gpio_in[CF_CARD_DETECT_PIN/16] >> (CF_CARD_DETECT_PIN%16)) & 0x01) {
        newCardPlugged &= ~0x01;
    } else {
        newCardPlugged |= 0x01;
    }

    if ( (regs0->gpio_in[CD_CARD_DETECT_PIN/16] >> (CD_CARD_DETECT_PIN%16)) & 0x01) {
        newCardPlugged &= ~0x02;
    } else {
        newCardPlugged |= 0x02;
    }

    if (newCardPlugged==0) {
        iThCardPlugged = 0;    
    } else if (newCardPlugged==3) {
        iThCardPlugged = 0;
    } else {
        iThCardPlugged = newCardPlugged;
    }

    if (iThCardPlugged>0)
        return 1;
    else
        return 0;
    
#else
    return 1;

#endif

}

#ifdef CARD_DISABLE_LOADER_SCHEME
void CardDisable()
{

    //set CARD_RESET_PIN:gpio17 pin( open drain pin) High to reset 
    #ifdef CARD_RESET_INVERSE
        regs0->gpio_oe[CARD_RESET_PIN/16] |= (0x1<<(CARD_RESET_PIN%16));
        regs0->gpio_out[CARD_RESET_PIN/16] &= ~(0x1<<(CARD_RESET_PIN%16));
    #else
        #ifndef QSI_PORTABLE_DVD
           regs0->gpio_oe[CARD_RESET_PIN/16] &= ~(0x1<<(CARD_RESET_PIN%16)); //input mode
        #else
           regs0->gpio_oe[CARD_RESET_PIN/16] |= (0x1<<(CARD_RESET_PIN%16)); //output mode  
       	   regs0->gpio_out[CARD_RESET_PIN/16] |= (0x1<<(CARD_RESET_PIN%16));//output HIGH               
       	#endif        
    #endif
    delay_srv_10ms(5);//Time for GPIO17 to be High

}  
#endif

void CardReset()
{

#ifdef CARD_HOT_PLUG
    //set CARD_RESET_PIN:gpio17 pin( open drain pin) High to reset 
    #ifdef CARD_RESET_INVERSE
        regs0->gpio_oe[CARD_RESET_PIN/16] |= (0x1<<(CARD_RESET_PIN%16)); //output mode
        regs0->gpio_out[CARD_RESET_PIN/16] &= ~(0x1<<(CARD_RESET_PIN%16));//output LOW to GPIO17
    #else
        #ifndef QSI_PORTABLE_DVD
           regs0->gpio_oe[CARD_RESET_PIN/16] &= ~(0x1<<(CARD_RESET_PIN%16)); //input mode
        #else
           regs0->gpio_oe[CARD_RESET_PIN/16] |= (0x1<<(CARD_RESET_PIN%16)); //output mode  
       	   regs0->gpio_out[CARD_RESET_PIN/16] |= (0x1<<(CARD_RESET_PIN%16));//output HIGH               
        #endif
    #endif
    
    delay_srv_10ms(80);//Time for GPIO17 to be High
    
    
    if(CARDIsPlugIn())
    {
        #ifdef CARD_RESET_INVERSE
            regs0->gpio_oe[CARD_RESET_PIN/16] &= ~(0x1<<(CARD_RESET_PIN%16)); //input mode to pull high
        #else
            regs0->gpio_oe[CARD_RESET_PIN/16] |= (0x1<<(CARD_RESET_PIN%16)); //output mode 
            regs0->gpio_out[CARD_RESET_PIN/16] &= ~(0x1<<(CARD_RESET_PIN%16));//output LOW to GPIO17
        #endif
    }
/*    
    else
    {
        #ifdef CARD_RESET_INVERSE
            regs0->gpio_out[CARD_RESET_PIN/16] &= ~(0x1<<(CARD_RESET_PIN%16));//output LOW to GPIO17
            regs0->gpio_oe[CARD_RESET_PIN/16] |= (0x1<<(CARD_RESET_PIN%16)); //output mode  
        #else
            regs0->gpio_out[CARD_RESET_PIN/16] |=(0x1<<(CARD_RESET_PIN%16));//output High to GPIO17
            regs0->gpio_oe[CARD_RESET_PIN/16] |= (0x1<<(CARD_RESET_PIN%16)); //output mode  
        #endif
    } 
*/    
    
    delay_srv_10ms(100);//don't cancel this delay, if it is cancel some card will read fail

    
    #ifdef CARDIF_DBG
    printf("CardReset\n");
    #endif
    
    font_decompress();
    osd_init();
    AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
    
#endif

}


#endif //SUPPORT_CARD_STORAGE

