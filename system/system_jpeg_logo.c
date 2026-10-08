#ifdef JPG_LOGO
extern UINT8 fetch_jpg_logo;

UINT8 Is_Jpg_Logo()
{
  UINT8 *p,temp;

  p=(BYTE *)&temp;
  if(ReadFromI2c(0xa0,0xf0,p,1)>0)
  {
    if(*p==0x55)  //User jpg logo tag!
    {
      return 1;
    }
    return 0;
  }
  
  return 0;
}


void ShowJpgTitle()
{
  UINT32 Jpglen;
  UINT16 *p,temp;
  BYTE * pJpglogo = (UINT8 *)(SDRAM_BASE_CACHED + SSAVER_YA*1024);
  
  p = (int *)&temp;

  ReadFromI2c(0xa0, 0xf1, p, 2);
  Jpglen=((UINT8 *)(p))[0]<<8|((UINT8 *)(p))[1];
  FlashRead(0x70000+28*1024,pJpglogo, Jpglen);
  fetch_jpg_logo=1;
  config_memory(MEMORY_GRAPH_PAL);
  Jpg_Main(0, Jpglen, 0, 0, 720, 576);
  fetch_jpg_logo=0;
  LoadModual(MODUAL_MPEG);
}

#endif//#ifdef JPG_LOGO


