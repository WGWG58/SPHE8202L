#include "global.h"
#include "osd.h"
#include "func.h"
#include "ircmd.h"
#include "memmap.h"
#include "dsp3_if.h"
#include "cchar.h"
#include "auddrv.h"

#ifdef SUPPORT_MIDI
#include "fsmidi.h"
#include "fsmidiui.h"
#endif

#ifdef SCORE_IN_PLAYMODE_MENU//libing
extern int score_flag;
#endif

#if !defined(OP_PLAYMODE)//libing 2005-4-12 10:11 for Op_Menu
#define OP_MENU         0x01<<12
#endif

#if 1
//UINT32 scoreSlow=0;
#ifdef SUPPORT_SCORE

//Jeff 20040325
UINT32  nSilence=0;
UINT32  nScoreSample=0;
UINT32  iScoreSum=0;

//
// Do all score initialization
//      1. draw GUI(osd_init_music)
void Score_Init()
{
    //printf("Score_Init\n");
    DSP_AudioIOControl(SCORING,0,0);//2004AUDDRV AudioIOControl(SCORING,0,0);	// alan, 2003/9/8 11:33¤W¤È
    //show_level(Score_Font_ID, 0, 11);

    //Jeff 20040325
    nSilence        = 0;
    nScoreSample    = 0;
    iScoreSum       = 0;
}

// exit score page
/*
void Score_Exit()
{
        //printf("Score_Exit\n");
}*/

// show score page
// this function is called by polling to update score page
#if 1//def GBM_DVD

#if defined(LARGE_SCORES_DISPLAY)//&& !defined(SUPPORT_DVD_SCORE)
#include "Scorefont.c"
extern void draw_midi_bitmap_HZnew(const UINT8* pFont, int xStart, int yStart,
		BYTE fontcolor, BYTE bgcolor, BYTE	FigureColor, BYTE FontType,
		BYTE number);

#define __palette4F(G,B,R,A) \
        ( ((UINT32)((G)&0xff)<<24)|((UINT32)((B)&0xff)<<16)|((UINT32)((R)&0xff)<<8)|(A&0xff) ) 

void OSD_DrawLargeScore(BYTE score)
{
	//printf("########Need to display the large Number#########\n");//jerry
    	const UINT8* NumFont[10] =
    	{
		score_0, score_1, score_2, score_3, score_4, 
		score_5, score_6, score_7, score_8, score_9, 
    	};

	SetOsdCol(3, 3, 0, __palette4F(255, 255, 255, 0x00));
	draw_midi_bitmap_HZnew(NumFont[score/10], 0, 0, 5, 6, 3, 2, 3);//call the function from midi program
	draw_midi_bitmap_HZnew(NumFont[score%10], 72, 0, 5, 6, 3, 2, 3);
	osd_DrawRegionString(0, 0, "", 5, 6, 3);

}
void OSD_ClearLargeScore()
{
	osd_Clear_Region(3, __palette4F(255, 255, 255, 0x00));//call the function from midi program
}
#endif//#ifdef LARGE_SCORES_DISPLAY

UINT32  Totalscore=0,ScoreInterval=0;
UINT32  iscoreNow=0;
#include "setup.h"
inline void Score_Polling()
{ 
    UINT32  scoreNow;// scoreFinal, micEnergy;
    UINT32  finalscore;
    UINT32  Trk_Time_Svcd = M2I(e_msf);
    UINT32  Disp_T_Svcd = M2I(s_msf);
    //extern  UINT32  iscoreNow;
    //UINT32  iscoreNow=0;
    UINT16  tract_time = dNx_pg_tm-dPg_tm; 
    UINT16  remain_time;
#ifdef SUPPORT_DVD_SCORE//libing 2005-8-30 13:47
    extern UINT16 Calculate_Score_Time(void);
#endif
	#ifdef SCORE_IN_PLAYMODE_MENU
	if((play_state==VCD_STATE_STOP)&&((cd_type_loaded==CDVCD10)||(cd_type_loaded==CDVCD20)||(cd_type_loaded==CDSVCD))&&(!IsPBCOn()))
	{
		osd_init();
		full_scrn = 0;
		score_flag = 0;
		return;
	}
	if((cd_type_loaded==CDDVD)&&(score_flag==1)&&(is_menu()==1))//&&(pDSV->CurrDomain == VTSM_DOM) )  //qinhua add for DVDMENU item not select,2005-8-25 14:46
    {
        osd_init();
        DispFadeOut();
        full_scrn = 0;
     	return;
    }
    #endif
    //Steven 2006/10/04 modify , use get_dsp3_pcm_value() instead of directly access address //
    scoreNow = get_dsp3_pcm_value(DSP_RUNTIME_FINAL_SCORE);
    //scoreNow = getUINT16_bi(bpcm_ya_ptr+52);
    ScoreInterval++;

	if(cd_type_loaded==CDSVCD)
   {
	//	tract_time = tract_time/PLAY_SPEED;
		remain_time = Trk_Time_Svcd - Disp_T_Svcd -7;
	}	
#ifdef SUPPORT_DVD_SCORE//libing 2005-8-30 13:47
	else if(cd_type_loaded==CDDVD)
		remain_time = Calculate_Score_Time();
#endif	
	else
		remain_time = tract_time - disp_time;	
	printf("***** scoreNow is: %d *****\n",scoreNow);
	printf("***** remain_time is: %d *****\n",remain_time);
	if((scoreNow>5)&&(ScoreInterval%4==0)&&(scoreNow<=150)&&(remain_time>6))
    {
   	  printf("!!!!!!!!!! scoreNow = %d \n",scoreNow);	
      Totalscore=Totalscore+scoreNow; 
      iscoreNow++;
    }
    if(remain_time < 5 && remain_time > 0)
    {
    	if(is_menu())
    	return;
    	if(iscoreNow<1)
    	iscoreNow = 1;
      //finalscore=Totalscore/ScoreInterval;
      finalscore=Totalscore/iscoreNow;
    	
      printf("&&&&&&& scoreNow = %d &&&&&&&&&\n",scoreNow);
      printf("&&&&&&& finalscore = %d &&&&&&&&&\n",finalscore);
      printf("&&&&&&& iscoreNow = %d &&&&&&&&&\n",iscoreNow);
      
      UINT16 D_num = 0;
      if(iscoreNow*2<=20)
      	D_num = 20;
      else if( (iscoreNow*2<40)&&(iscoreNow*2>20) )
      	D_num = 15;
      else if( (iscoreNow*2<70)&&(iscoreNow*2>=40) )
      	D_num = 10;	
      else if( (iscoreNow*2<90)&&(iscoreNow*2>=70) )
      	D_num = 5;
      else if(iscoreNow*2>=90)
      	D_num = 0;	
      	
      if(finalscore==0)
           finalscore=40;
      else if((finalscore<=25)&&(finalscore>0))
      {
      	   finalscore=50+finalscore/5 -D_num;     
      	   if(finalscore<40)
      	   finalscore = 40;
      }
      else if((finalscore<=55)&&(finalscore>25))
      	   finalscore=60+(finalscore-25)/3 -D_num;     
      else if((finalscore<=65)&&(finalscore>55))
           finalscore=70+(finalscore-55)/2 -D_num;     
      else if((finalscore<=75)&&(finalscore>65))
           finalscore=80+(finalscore-65)/1 -D_num*2;
      else if((finalscore<=100)&&(finalscore>75))
           finalscore=90+(finalscore-75)/3 -D_num*2;
      else 
    	   finalscore=100;//if score >100; score is 98;
		//libing modify 2005-9-2 14:04 
	
	//finalscore = scoreNow;

	if(setup_IsMICOff())
	finalscore=0;	

#ifdef LARGE_SCORES_DISPLAY//wuxiaofeng add 2004-02-20 for GBM
	if(full_scrn!=OP_MENU)
	OSD_DrawLargeScore(finalscore);
#else
    //show_level(Score_Font_ID, scoreNow, 11);	//Jeff 20020416
    show_level(Score_Font_ID, finalscore, 11);	//jacky
#endif
    }
    else if(full_scrn==OP_MENU || full_scrn==PROGRAM)
	{
	}
    else
    {
		memset(RegionValStr[REGION2],0,sizeof(RegionValStr[REGION2]));
		PrintOsdMsg(STR_OS_SCORE, REGION2, 0, 1); 
#ifdef LARGE_SCORES_DISPLAY//wuxiaofeng add 2004-02-20 for GBM
		OSD_ClearLargeScore();
#endif
	}
	//else if((remain_time == tract_time)||(remain_time == dNx_pg_tm))
    if(disp_time < 2 && disp_time > 0)
    {
    	Totalscore = 0;
    	finalscore = 0;
    	iscoreNow  = 0;
    }
}

#else//GBM_DVD
inline void Score_Polling()
{
    
    UINT32  scoreNow;// scoreFinal, micEnergy;
    //BYTE    *q=(BYTE *)(SDRAM_BASE_UNCACHED+regs0->pcmya*1024);
    UINT16  tract_time = dNx_pg_tm-dPg_tm; 

    //scoreNow = (UINT32)( *(bpcm_ya_ptr+50) ); //3*16+2
    scoreNow = (UINT32)( *(BYTE *)(SDRAM_BASE_CACHED+MEM_PCMYA*1024+50) ); //3*16+2

    //Jeff 20040325
    if (scoreNow) {
        nScoreSample++;
        iScoreSum += scoreNow;

        //printf("1:%d=scoreNow=%d, avgscore=%d\n", nScoreSample, scoreNow, iScoreSum/nScoreSample);
        show_level(Score_Font_ID, iScoreSum/nScoreSample, 11);
    } else {
        nSilence++;

        //printf("0:%d\n", nSilence);
    }

    /*
	if(cd_type_loaded==CDSVCD)
		tract_time = tract_time/PLAY_SPEED;
    if((tract_time - disp_time) < 5)
    {
    show_level(Score_Font_ID, scoreNow, 11);	//Jeff 20020416
    }
    else
    {
		memset(RegionValStr[REGION2],0,sizeof(RegionValStr[REGION2]));
		PrintOsdMsg(STR_OS_SCORE, REGION2, 0, 1); 
	}
    */
}
#endif	//#ifdef GBM_DVD

#else//SUPPORT_SCORE
inline void Score_Polling()
{}
void Score_Init()
{}
#endif//SUPPORT_SCORE
#else//#if !defined(SUPPORT_MIDI)    //xlluo add for score in midi2004.10.9

//Jeff 20040325
UINT32  nSilence=0;
UINT32  nScoreSample=0;
UINT32  iScoreSum=0;

//
// Do all score initialization
//      1. draw GUI(osd_init_music)
void Score_Init()
{
    //printf("Score_Init\n");
    DSP_AudioIOControl(SCORING,0,0);//2004AUDDRV AudioIOControl(SCORING,0,0);	// alan, 2003/9/8 11:33¤W¤È
    //show_level(Score_Font_ID, 0, 11);

    //Jeff 20040325
    nSilence        = 0;
    nScoreSample    = 0;
    iScoreSum       = 0;
}

// exit score page
/*
void Score_Exit()
{
        //printf("Score_Exit\n");
}*/
#ifdef SUPPORT_DVD_SCORE  //liumzh add, by axel
#include "Scorefont.c"
extern void draw_midi_bitmap_HZnew(const UINT8* pFont, int xStart, int yStart,
		BYTE fontcolor, BYTE bgcolor, BYTE	FigureColor, BYTE FontType,
		BYTE number);

#define __palette4F(G,B,R,A) \
        ( ((UINT32)((G)&0xff)<<24)|((UINT32)((B)&0xff)<<16)|((UINT32)((R)&0xff)<<8)|(A&0xff) ) 

void OSD_DrawLargeScore(BYTE score)
{
	//printf("########Need to display the large Number#########\n");//jerry
    	const UINT8* NumFont[10] =
    	{
		score_0, score_1, score_2, score_3, score_4, 
		score_5, score_6, score_7, score_8, score_9, 
    	};

	SetOsdCol(3, 3, 0, __palette4F(255, 255, 255, 0x00));
	draw_midi_bitmap_HZnew(NumFont[score/10], 0, 0, 5, 6, 3, 2, 3);//call the function from midi program
	draw_midi_bitmap_HZnew(NumFont[score%10], 72, 0, 5, 6, 3, 2, 3);
	osd_DrawRegionString(0, 0, "", 5, 6, 3);
	osd_tog_region(3, OSD_ON);

}
void OSD_ClearLargeScore()
{
	osd_Clear_Region(3, __palette4F(255, 255, 255, 0x00));//call the function from midi program
}
#endif//#ifdef LARGE_SCORES_DISPLAY


// show score page
// this function is called by polling to update score page
inline void Score_Polling()
{
    
#ifdef SUPPORT_DVD_SCORE
    UINT32  scoreFinal,scoreNow,scoreNow_EG;// scoreFinal, micEnergy;
    UINT32  nSilenceCounter;
    UINT16  tract_time = dNx_pg_tm-dPg_tm; 
#else
    UINT32  scoreNow;// scoreFinal, micEnergy;
#endif
    //BYTE    *q=(BYTE *)(SDRAM_BASE_UNCACHED+regs0->pcmya*1024);
   // UINT16  tract_time = dNx_pg_tm-dPg_tm; 
#ifdef MIDI_SCORE_TEST
    if (!gb_showScore) return;
#endif

#ifdef SUPPORT_DVD_SCORE
        scoreNow_EG = getUINT16_bi(bpcm_ya_ptr+54);
#else
    scoreNow = (UINT32)( *(BYTE *)(SDRAM_BASE_CACHED+MEM_PCMYA*1024+50) ); //3*16+2
#endif

    //Jeff 20040325
#ifdef SUPPORT_SANJING_SCORE
    if (scoreNow&&Is_MIDI_STATE())//&&bIsSJScoreInvaild)
    {
        SJGetNewScore(scoreNow);
        return;
    }else
#endif

#ifndef SUPPORT_DVD_SCORE
    if (scoreNow) {
        nScoreSample++;
        iScoreSum += scoreNow;
        show_level(Score_Font_ID, iScoreSum/nScoreSample, 11);
    } else {
        nSilence++;
    }
#else
    if (scoreNow_EG ) {
        printf("scoreNow_EG %d\n",scoreNow_EG);
        if (scoreNow_EG > 100)  scoreNow_EG = (scoreNow_EG>>1)+20;
        else if (scoreNow_EG > 60)  scoreNow_EG = (scoreNow_EG>>1)+30;
        else if (scoreNow_EG > 40)  scoreNow_EG = (scoreNow_EG>>1)+50;
        else scoreNow_EG = 50;

        if (scoreNow_EG > 70)
        {
            nScoreSample++;
            iScoreSum += scoreNow_EG;
        }
        nSilenceCounter=0;
        //show_level(Score_Font_ID, iScoreSum/nScoreSample, 11);
        show_level(Score_Font_ID, scoreNow_EG, 11);
        printf("scoreNow_EG %d\n",scoreNow_EG);
        printf("scoreFinal %d\n",iScoreSum/nScoreSample);
        
    } else {
        nSilence++;
        nSilenceCounter++;

        if(nSilenceCounter > 5) 
        {    
            show_level(Score_Font_ID, 50, 11);
        }    
    }

    if(((tract_time - disp_time) < 14 && (tract_time - disp_time) > 5)){
        //show_level(Score_Font_ID, iScoreSum/nScoreSample, 11);
        int FinalScore = iScoreSum/nScoreSample;
        OSD_DrawLargeScore(FinalScore);
    }
    else if ((tract_time - disp_time) < 5 && (tract_time - disp_time) > 0)
    {
        OSD_ClearLargeScore();
        Score_Init(); 
    }
#endif

#ifdef MIDI_SCORE_TEST
    if (gb_showScore)
    {
        printf("Score_Polling %d\n",scoreNow);
        if ((gb_showScore)&&(midiState == MIDI_STATE_PAYLOAD))
            getNewScore(scoreNow);
    }
#endif
}

#endif//#if !defined(SUPPORT_MIDI)

