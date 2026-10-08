//
// FILE
// sysmain2_logomp3.inc
//
// DESCRIPTION
//

#ifdef LOGO_PLAY_MP3
void Show_Logo_Play_MP3()
{
    extern const unsigned char LOGO_MP3[];
    int a;
    /*Play Background MP3*/

    #define PlayLen 3

    //b=sizeof(LOGO_MP3);
    //printf("MP3 size=%d\n",b);

    for(a=0;a<PlayLen;a++)
    {
     stream_ptr = (BYTE*)(LOGO_MP3 + playindex*PlayLen*1024+a*1024);
     //print_block(stream_ptr,1024);
     dma_iptr  = 0;
     dma_ilen  = 1024;
     logo_play_mp3_flag=0;
     do_mp3();
     logo_play_mp3_flag=1;
    }

    playindex++;
    if(playindex==MaxPlayLen/PlayLen) playindex=0;
}


static inline void logo_play_mp3()
{
    if(old_system_state!=system_state)
    {
        if( ((old_system_state==SYSTEM_NODISC) && (system_state==SYSTEM_OPEN))
          ||((old_system_state==SYSTEM_IDLE) && (system_state==SYSTEM_OPEN))
          ||((old_system_state==SYSTEM_STOP) && (system_state==SYSTEM_OPEN)))
            play_mp3_flag=0;

        old_system_state=system_state;

        if((system_state==SYSTEM_NODISC)||(system_state==SYSTEM_OPEN)||(system_state==SYSTEM_STOP))
        {
            if(!play_mp3_flag)
            {
                //printf("MP3 INIT!---------\n");
                AUDIF_Init_Audio(); //2004AUDDRV init_audio();
                AUDIF_Init_MP3();   //2004AUDDRV init_mp3();
                AUDIF_Set_Play();   //2004AUDDRV AudioSetPlay();
                playindex=0;
                mp3_count=0;
                play_mp3_flag=1;
            }
        }
    }
    else if((system_state==SYSTEM_NODISC)||(system_state==SYSTEM_OPEN)||(system_state==SYSTEM_STOP))
    {
        if(mp3_count>=500)
        {
            Show_Logo_Play_MP3();
            mp3_count=0;
        }
        else mp3_count++;
    }
}
#endif

