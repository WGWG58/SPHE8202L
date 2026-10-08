#include "user_init.h"
#include "global.h"
#include "osd.h"
#include "auddrv.h" //2004AUDDRV oliver 20041004 for using audio driver purpose
//#include "audif.h"

#ifdef SUPPORT_PROLOGIC_II_ADVANCE_SETTING
void str_os_prologic2_center_width(UINT32 center_width);
void str_os_prologic2_panorama(int sub_id);
void str_os_prologic2_dimension(UINT32 dimension);
#endif
void
str_os_prologic2(int sub_id)
{
#ifdef DVD_SETUP_REENG//dengh add for DVD_SETUP_REEN2004-9-24 13:32
	UINT16 P=0;
	UINT16 I=0,S=0;
#endif 
	BYTE type=0x23;
	if (sub_id!=STR_OS_OFF)	// alan, 2003/8/11 02:17PM
	{
		//to avoid the bug:
		//when audio_channel is LC or RC,  open proloic II.
		//after exit SETUP, the volume of left channel and 
		//right channel is very small.
		//zhaoyanhua add 2004-2-11 14:06
		audio_channel = 0;
		AUDIF_Set_OutputMode(audio_channel+1, 0);//2004AUDDRV AudioSetOutputMode(audio_channel+1, 0);
					
	#ifdef DVD_SETUP_REENG   //denghg  add2004-9-30 11:43
	    P=setup_getItemPos(STR_OS_KEY);
	    I=P&0xff;
        P=P>>8;
        setup_VA[SETUP_VA_KEY]=8;   	
        setup_sel[P][I]=8;
        audio_key=0;
	    AUDIF_Set_Key(setup_VA[SETUP_VA_KEY]);//2004AUDDRV AudioSetKey(setup_VA[SETUP_VA_KEY]);     
	    run_save_sel_cmd( setup_VA[SETUP_VA_KEY],SETUP_VA_KEY);    
	#else       //end dvd_setup_reeng
		SETUP_KEY = 8;	
		audio_key=0;
		AUDIF_Set_Key(SETUP_KEY);//2004AUDDRV AudioSetKey(SETUP_KEY);
		run_save_sel_cmd(AUDPAGE, KEYITEM);//nono 20031117
	#endif//#ifdef DVD_SETUP_REENG  //dengh add for DVD_SETUP_REEN2004-9-24 13:32			
	}
	
	if (sub_id==STR_OS_PL_MOVIE)
	{
		pl2_init_val|=(1<<20);		// set prologic-II enable
		pl2_init_val|=(1<<16);		// set init-val to movie mode						
		//DSP set prologic-II enable
        AUDIF_Set_ProLogicII(0x11);//2004AUDDRV AudioIOControl(PROLOGIC,0x11,0);
		type=0x23;
		//printf("<MOVIE>, pl2_init_val=0x%06x\n",pl2_init_val);
	  #ifdef	DVD_SETUP_REENG    //denghg  add  2004-9-30 11:43
		       P=setup_getItemPos(STR_OS_PROLOGIC);
           I=P&0xff;
           P=P>>8;
           for( S=0; S<MAX_ITEM_SEL; S++) {
          	if (setup_item[P][I][S]==STR_OS_PL_MOVIE) break;
          }
          setup_sel[P][I]=S;
          setup_VA[SETUP_VA_PROLOGIC]=setup_sel[P][I]; 
          #ifdef USE_SETUP_ITEM_ENABLE_FLAG
          setup_VA_EN[SETUP_VA_PL_PANORAMA]=0;
          setup_VA_EN[SETUP_VA_PL_CENTER_WIDTH]=0;
          setup_VA_EN[SETUP_VA_PL_DIMENSION]=0;
          #endif//USE_SETUP_ITEM_ENABLE_FLAG
      #endif      				
	} else if (sub_id==STR_OS_PL_MUSIC) 
	{
		pl2_init_val|=(1<<20);		// set prologic-II enable
		pl2_init_val&=(~(1<<16));	// set init-val to music mode
		//DSP set prologic-II enable
        AUDIF_Set_ProLogicII(0x11);//2004AUDDRV AudioIOControl(PROLOGIC,0x11,0);

        #ifdef USE_MATRIX_PROLOGICII_MODE//nono 4-2-25 23:07			
		type=0x24;
        #else
		type=0x22;
        #endif

       #ifdef DVD_SETUP_REENG//denghg  add  2004-9-30 11:44
       P=setup_getItemPos(STR_OS_PROLOGIC);
       I=P&0xff;
       P=P>>8;
       for( S=0; S<MAX_ITEM_SEL; S++) {
          	if (setup_item[P][I][S]==STR_OS_PL_MUSIC) break;
          }
          setup_sel[P][I]=S;
          setup_VA[SETUP_VA_PROLOGIC]=setup_sel[P][I];       
          #ifdef USE_SETUP_ITEM_ENABLE_FLAG
          setup_VA_EN[SETUP_VA_PL_PANORAMA]=1;
          setup_VA_EN[SETUP_VA_PL_CENTER_WIDTH]=1;
          setup_VA_EN[SETUP_VA_PL_DIMENSION]=1;
          #endif//USE_SETUP_ITEM_ENABLE_FLAG
       #endif
    
       
		//printf("<MUSIC>, pl2_init_val=0x%06x\n",pl2_init_val);
	} else if (sub_id==STR_OS_OFF) 
	{
		//pl2_init_val&=(~(1<<20));	// set prologic-II disable
		pl2_init_val=PROLOGICII_OFF_DSP_INIT;
		//DSP set prologic-II disable
        AUDIF_Set_ProLogicII(0x10);//2004AUDDRV AudioIOControl(PROLOGIC,0x10,0);
#ifdef SUPPORT_PROLOGIC_II //terry,2004/2/10 03:43PM

#ifdef DVD_SETUP_REENG//denghg  add  2004-9-30 11:44
       P=setup_getItemPos(STR_OS_PROLOGIC);
       I=P&0xff;
       P=P>>8;
         for( S=0; S<MAX_ITEM_SEL; S++) {
          	if (setup_item[P][I][S]==STR_OS_OFF) break;
          }
          setup_sel[P][I]=S;
          setup_VA[SETUP_VA_PROLOGIC]=setup_sel[P][I];
          #ifdef USE_SETUP_ITEM_ENABLE_FLAG
          setup_VA_EN[SETUP_VA_PL_PANORAMA]=0;
          setup_VA_EN[SETUP_VA_PL_CENTER_WIDTH]=0;
          setup_VA_EN[SETUP_VA_PL_DIMENSION]=0;
          #endif//USE_SETUP_ITEM_ENABLE_FLAG
#else//#ifdef DVD_SETUP_REENG//denghg  add  2004-9-30 11:44
		SETUP_PROLOGIC_II = PROLOGIC_OFF;
#endif//#ifdef DVD_SETUP_REENG//denghg  add  2004-9-30 11:44

#endif

	}
	//set_dsp3_pcm_value(35,pl2_init_val);
	//DSP set prologic-II Decoder Mode Select
    AUDIF_Set_ProLogicII(type);//2004AUDDRV AudioIOControl(PROLOGIC,type,0);
    #if defined(SUPPORT_PROLOGIC_II_ADVANCE_SETTING) && defined(DVD_SETUP_REENG)
    P=setup_getItemPos(STR_OS_PL_PANORAMA);
    if(P!=0xffff)
    {
        I=P&0xff;
        P=P>>8;
        str_os_prologic2_panorama(setup_item[P][I][setup_VA[SETUP_VA_PL_PANORAMA]]);
    }
    else
        str_os_prologic2_panorama(STR_OS_OFF);
    str_os_prologic2_center_width(setup_VA[SETUP_VA_PL_CENTER_WIDTH]-MIN_ITEM_SEL);
    str_os_prologic2_dimension(setup_VA[SETUP_VA_PL_DIMENSION]-MIN_ITEM_SEL);
    #endif
#ifdef USE_PROLOGIC_II_KEY
  #ifdef DVD_SETUP_REENG
    prologic_val=setup_VA[SETUP_VA_PROLOGIC]-MIN_ITEM_SEL;
  #else
	prologic_val=SETUP_PROLOGIC_II-2;
#endif//#ifdef DVD_SETUP_REENG//denghg  add  2004-9-30 11:44
#endif 
	//break;//nono mark 2004-6-6 17:58
}

#ifdef SUPPORT_PROLOGIC_II_ADVANCE_SETTING
#define DIMENSION_BIT   8
#define CENTER_WIDTH_BIT   4
#define PANORAMA_BIT   3
void
str_os_prologic2_center_width(UINT32 center_width)
{
    if((pl2_init_val & (1<<20))&& !(pl2_init_val & (1<<16))) //prologic-II enable & music mode
    {
        if(center_width>0x7)
            center_width=0x07;
    }
    else
    {
        center_width=0;
    }
    pl2_init_val&=(~(0xf<<CENTER_WIDTH_BIT));   
    pl2_init_val|=((0xf & center_width)<<CENTER_WIDTH_BIT);     // set prologic-II enable
    AUDIF_Set_ProLogicII(0x50|(center_width & 0x0f));
}
 
void
str_os_prologic2_panorama(int sub_id)
{
    if((pl2_init_val & (1<<20))&& !(pl2_init_val & (1<<16))) //prologic-II enable & music mode
    {
        switch(sub_id)
        {   
            case STR_OS_OFF:
                pl2_init_val&=(~(0x1<<PANORAMA_BIT));  
                AUDIF_Set_ProLogicII(0x60);
                break;
            case STR_OS_ON:
                pl2_init_val|=(0x1<<PANORAMA_BIT);
                AUDIF_Set_ProLogicII(0x61);
                break;
            default:
                break;
        }
    }
    else
    {
        pl2_init_val&=(~(0x1<<PANORAMA_BIT));  
        AUDIF_Set_ProLogicII(0x60);
    }
}
 
void
str_os_prologic2_dimension(UINT32 dimension)
{
    if((pl2_init_val & (1<<20))&& !(pl2_init_val & (1<<16))) //prologic-II enable & music mode
    {
        if(dimension>0x6)
            dimension=0x06;
    }
    else
    {
        dimension=0x03;
    }
    pl2_init_val&=(~(0xf<<DIMENSION_BIT));  
    pl2_init_val|=((0xf & dimension)<<DIMENSION_BIT);       
    AUDIF_Set_ProLogicII(0x40|(dimension & 0x0f));
}
#endif

