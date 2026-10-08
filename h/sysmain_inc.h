/*
*  Terry,2004/2/6 01:09PM
*  1.chg dvd code download mode
*  Terry,2005/10/18 05:40下午
*  2.add DVB modual code.
*/

#ifdef SERVO_TEST 
#include "mpegsys.h"
#include "cd.h"
#endif
#include "mpegsys.h"
#ifdef ROM_ATA_SHARE_BUS			

void atapi_share_rom_bus(void)
{
       UINT16 status;
	
       //rom1234 => 2,4
       // rom1/2 bases       
       regs0->rom1_base = 0x100;       // rom2 n*64k-base ,pcmcia
       regs0->rom2_base = 0x160;       // rom2 n*64k-base ,pcmcia
       regs0->rom3_base = 0x200;       // rom3 n*64k-base ,pcmcia
       
       //regs0->rom_config = 0x50a0;     // pcmcia,rom2,4       
       regs0->rom_config = 0x5060;     // pcmcia,rom2,3

       //regs0->wait_cyc3_2 = 0x0404;
       regs0->pcmcia_ctrl = 0x0018;
       
       
       regs0->pcmcia_iorw_wait =0x2222;
       //regs0->iochrdy_wait_cyc =0x;
       //regs0->oe_wait_cyc3_2 = ;
       //regs0->we_wait_cyc3_2 = ;
       
       /*atapi_reg_read(0x10);
       atapi_reg_read(0x11);
       atapi_reg_read(0x12);
       atapi_reg_read(0x13);
       atapi_reg_read(0x14);
       atapi_reg_read(0x15);
       atapi_reg_read(0x16);
       atapi_reg_read(0x17);
       atapi_reg_write(0x11,0xa5a5);
       atapi_reg_write(0x12,0xa2a2);
       atapi_reg_write(0x14,0xa4a4);
       
       
       printf("ok\n");
       while(1);
       */
       /*
       atapi_init();  
       atapi_open_tray();
       
       delay(1000);
       status = atapi_reg_read(IDE_STATUS);							   
	   printf("status:%x\n",status);       
       printf("............\n");
       
       while(1);*/
}

#ifndef DVD_SERVO

#define CS0 (ROM_BASE_UNCACHED+0x1000000)
#define CS1 (ROM_BASE_UNCACHED+0x2000000)
#define DA0 (1<<0)
#define DA1 (1<<1)
#define DA2 (1<<2)

UINT16
atapi_reg_read(UINT8 addr)
{	
	//UINT8 *p;	
	UINT16 *q,res;
	UINT32 r;
	int cs=0;
	
	cpu_intr_disable();     
	r=(addr&0x7)<<1;
	if(addr&(1<<3))
	{
		 r|=CS1;
		 cs=1;
        }
	else r|=CS0;
	
	//p=(UINT8 *)r;
	q=(UINT16 *)r;
	res=*q;
	
    if(addr!=IDE_DATA)
      res=res&0xff;
    
    cpu_intr_enable();            // enable CPU-level intr_enable
    //printf("<r,cs:%x,r:%x q:%x addr:%x>\n",cs,r,res,addr);		
	return res;	
}

void
atapi_reg_write(UINT8 addr, UINT16 data)
{	
	UINT16 *p;
	UINT32 r;
	int cs=0;
		
	cpu_intr_disable();     
	r=(addr&0x7)<<1;
	if(addr&(1<<3))
	{ r|=CS1;cs=1;}
	else r|=CS0;
		
	
	p=(UINT16 *)r;	
	*p = data;
	cpu_intr_enable();            // enable CPU-level intr_enable
	//printf("<w,cs:%x r:%x p:%x data%x addr:%x>\n",cs,r,p,data,addr);		
}

#endif //#ifndef DVD_SERVO

#else
#define atapi_share_rom_bus() {}
#endif


#ifdef USE_HDD //cyue: Add Test 2002-06-14 04:45PM
void hdd_init()
{
  play_state=VCD_STATE_NORMAL;
  //play_state=VCD_STATE_IDLE;
  system_state=SYSTEM_BROWSE;
  cd_type_loaded=CDDVD;
  //osd_init();
  ClearOsdMsg(0);//kenny add it 2001/5/8
  InitVar();  
  HDD_Test();
  play_state=VCD_STATE_IDLE;
}
#else
#define hdd_init() {}
#endif


#ifdef SERVO_TEST  

void TestRomY()
{
  int i;
  UINT32	ssstate;
  
  AVD_ResetMediaStatus();
  stream_video = 0xe0;
  stream_audio = 0xff;
  restart_video_engine();
  restart_cdlayer();
  regs0->dvddsp_vx = 0;
  regs0->dvddsp_vy = 0;
  regs0->dvddsp_ry = CBV_H-1;	// at least this value
  regs0->dvddsp_rx= 0;
  cbv_y= 0;

 
  while (1)
  {
    // get current cbv pointer   
    polling();    
    if (DISC_DUMP_Y==cbv_y) {
	    ssstate = 0; continue;
    }
    ssstate = 1;
    stream_ptr = get_cbv_ptr(0,cbv_y);
    DISC_BARRIER_Y = cbv_y;
     regs0->dvddsp_ry = cbv_y;
    if (++cbv_y>=CBV_H) cbv_y = 0;
    i++;

    //printf("%x", i);
//	if (decoded_pic>0x30) dump_content("\nSRV ", stream_ptr, 1024);
//dump_content("\nSRV ", stream_ptr, 1024);

    dma_iptr = 0;
    dma_ilen = 1024;
    if (is_svo_dvd())
    {
      do {
        polling();
        if (IsAVDMediaInterrupt()) break;
      } while (do_system());
    }
    else
    {
      do {
        polling();
        if (IsAVDMediaInterrupt()) break;
      } while (do_cd());
    }

    if (IsAVDMediaInterrupt()) break;
  }
}

void servo_test(void)
{
  while (1)
  {
	  printf("MMMAIN\n");
	  TestRomY();
  }
  
  while (1)
  {
//  	extern UINT32 disc_dump_y;
//  	extern UINT32 disc_barrier_y;
    io_write("\t\tMMMAIN\n");
    cd_type=CDDVD;
    bDiscType=CDDVD;
    PlayLBA(0,100000);    
    setup_dvd_motion_ntsc();
    setup_decode_service(SERVICE_CD);
    DISC_DUMP_Y = 0;
    DISC_BARRIER_Y = 30;
    do {
        srv_kernel();   //doing kernel routine.
        polling();      //polling system status for pending-job
    } while (1); //!IsAVDMediaInterrupt());
  }
}
#else
#define servo_test() {}
#endif


#if 1 
extern	char	_stextf[];	
extern	char	_text_drv[],_text_drv2[], _text_drv_dvd[], _text_drv_ap[], _text_drv_iop[], _text_other[], _text_drv_cdrom[];
#ifdef DVD_SERVO
extern	char	_text_drv_srvdp[], _text_drv_ap2[], _text_drv_free[],_text_drv_dvb[], _text_drv_mp4[], _text_drv_wma[];	//terry,2005/10/12 07:52下午
#else
extern	char	_text_drv_ap2[], _text_drv_free[], _text_drv_mp4[], _text_drv_wma[];	
#endif
#ifdef SPHE1000
extern	char	_text_lwip[];
#endif
UINT16 modual_loaded = 0;
#ifdef SYSMAIN_DBG//terry,2005/10/13 01:34下午
const char dbg[][20]=
{
    "DVD",
    "MPEG",
    "JPEG",
    "AP",
    "CDROM",
    "IOP",
    "IOPRESET",
    "OTHER",
    "SRVDSP",
    "AP2",
    "AP3",
    "FREE",
    "",
    "MP4",
    "WMA",
#ifdef SPHE1000
    "LWIP"
#else
#ifdef  SUPPORT_8202_DVB			
    "DVB"  
#endif    
#endif    
};
#endif

void download_text_code(UINT16 iModuleIndex,BYTE *pDestAddr)
{
  BYTE *p;
  UINT32 unOffset;
  int v;

  unOffset = ((UINT32 *)_stextf)[iModuleIndex];
  p = (BYTE *)(_stextf + unOffset + (MODUAL_Ns * 4));
		
  v = dsp3_decompress(p, pDestAddr);
  invalidate_dcache();
  
#ifdef SYSMAIN_DBG
  printf("load:%s v:%x\n",dbg[iModuleIndex],v);
#endif
}

void LoadModual(UINT16 iModuleIndex)
{	
    BYTE *pDestAddr;
    UINT16 index = (1 << (iModuleIndex & 0xf));

/*
	if(iModuleIndex&RESET_MODE)
	{		
		modual_loaded&=(~index);				
	}
	else
*/
	if ((modual_loaded & index) == 0)
	{
		if ((iModuleIndex != MODUAL_CDROM) && (iModuleIndex != MODUAL_MP4) && (iModuleIndex != MODUAL_WMA) &&(iModuleIndex != MODUAL_DVB)  ) // load CDROM ,MP4,DVB and WMA module always		
		modual_loaded |= index;

		switch(iModuleIndex)
		{
		case MODUAL_OTHER:
		default:
			pDestAddr = _text_other;
			break;
		
		case MODUAL_IOP:
		case MODUAL_IOP_RESET:
			pDestAddr = _text_drv_iop;
			break;
		
		case MODUAL_MPEG:
		
		    download_text_code(MODUAL_DVD,_text_drv_dvd);//download dvd
		        
			modual_loaded &= (~(1<<MODUAL_JPEG));
			pDestAddr = _text_drv;
			break;
		
		case MODUAL_JPEG:
			modual_loaded &= (~(1<<MODUAL_MPEG));
			modual_loaded &= (~(1<<MODUAL_DVD));
			pDestAddr = _text_drv2; //terry,2005/4/7 10:51下午 ,for 8202D
			break;
		
		case MODUAL_AP:
			pDestAddr = _text_drv_ap;
			break;
		
		//case MODUAL_DVD:
			//modual_loaded &= (~(1 << MODUAL_CDROM));
			//pDestAddr = _text_drv_dvd;
			//break;
		
		case MODUAL_CDROM:
			pDestAddr = _text_drv_cdrom;
			break;

#ifdef DVD_SERVO
		case MODUAL_SRVDSP:
			pDestAddr = _text_drv_srvdp;
			break;
#endif

		case MODUAL_AP2:
			modual_loaded &= (~(1<<MODUAL_AP3));
			pDestAddr = _text_drv_ap2;
			break;
		
		case MODUAL_AP3:
			modual_loaded &= (~(1<<MODUAL_AP2));
			pDestAddr = _text_drv_ap2;
			break;

		case MODUAL_FREE:
			pDestAddr = _text_drv_free;
			break;

#ifdef  SUPPORT_8202_DVB
    	case MODUAL_DVB: //terry,2005/10/12 07:52下午
			pDestAddr = _text_drv_dvb;
			break;
#endif			


		//case MODUAL_MP4: //terry,2005/5/20 01:44下午, merge mp4 & wma 
			//pDestAddr = _text_drv_mp4;
			//break;

		case MODUAL_WMA:
		case MODUAL_MP4:  //terry,2005/5/20 01:44下午
			pDestAddr = _text_drv_wma;
			break;
#ifdef SPHE1000
		case MODUAL_LWIP:
			pDestAddr = _text_lwip;
			break;
#endif
		}
		
	        download_text_code(iModuleIndex,pDestAddr);//download dvd
	}
#ifdef SYSMAIN_DBG
	else
	{
		printf("[%s] module is already loaded.\n",dbg[iModuleIndex]);
		io_write("------------------------\n");
		return;
	}

    static UINT8 count=0;
    
    if(count>5)
	{
	    
		UINT16 i;
		
		
		printf("loaded(%d,0x%x):",MODUAL_Ns,modual_loaded);
		for(i=0;i<MODUAL_Ns;i++)
		{
           	if(modual_loaded&(1<<i))
				printf("[%s] ",dbg[i]);
		}
		io_write("\n");
	}else count++;
	
	io_write("------------------------\n");
#endif
}

#else

void  LoadModual(UINT16 iModuleIndex) {}
#endif



