/*
* Terry,2006/4/6 09:15¤U¤È
*/

static  inline  void
reset_setup_digital_video_out()
{
  
#ifdef DIGITAL_VIDEO_OUT
#ifdef SPHE8202
#ifdef MP_BOARD_256_PIN_NON_SHARE
#ifdef CCIR656_TYPE1 //enable ccir656 on pin225 ~pin233
#ifdef IC_8202D //kenny 2005/8/16
regs0->sdc_data_cnt[6][0] |= (0x0e);
regs0->sft_cfg20 &=~(0x1<<0); 
regs0->sft_cfg7 &=~(0x1<<4);
regs0->sft_cfg7 |=(0x1<<5);
regs0->sft_cfg3 |=(0x1<<12);//enable HSYNC, YSYNC on pin 206, pin206
regs0->sft_cfg3 &=~(0x1<<13);
#else
regs0->sdc_data_cnt[6][0] |= (0x0e);//Disable ROM_A20(Pin225),ROM_A21(Pin226),ROM_A22(Pin227) as GPIO92,93,94
regs0->sdc_data_cnt[6][0] |= (0x1 <<4);  //CCIR656 ENABLE on Pin225~233
#endif
#elif defined(CCIR656_TYPE2) 
regs0->sft_cfg7 |= (0x1 << 4);    //rbhung Only for TEST
regs0->sft_cfg3 &= ~(0x1 << 5);   //Disable AUD4 as GPIO50 for TV_CLK ,pin 193

#elif defined(IC_8202D)&& defined(CCIR656_TYPE3) //kenny 2005/2/16 for 8202D IC
regs0->sft_cfg4 &=~(0x1<<6); //disable pin55 DFCT
regs0->sft_cfg7 |=(0x1<<4); //CCIR656 ENABLE on Pin55~66
regs0->sft_cfg7 |=(0x1<<5);

#elif defined(IC_8202D)&& defined(CCIR656_TYPE4) //benson 2005/7/06   for 6500
regs0->sft_cfg0 &= ~(0x1<<7);
regs0->sft_cfg7 &= ~(0x03<<4);
regs0->sft_cfg7 |= (0x1<<4);
#elif defined(IC_8202D)&& defined(CCIR601_TYPE1)// &&defined(DVDRELEASE)
regs0->sysclk_div_sel |= (1<<5); 
regs0->sdc_data_cnt[6][0] |= (0x0e);
regs0->sft_cfg20 &=~(0x1<<0); 
regs0->sft_cfg7 &=~(0x1<<4); /////////CCIR656 ENABLE
regs0->sft_cfg7 |=(0x1<<5);
regs0->sft_cfg3 &=~(0x1<<12);//enable HSYNC, YSYNC on pin 206, pin206
regs0->sft_cfg3 &=~(0x1<<13);
regs0->sft_cfg2&=~(0x01<<2);//disable Uart0
regs0->sft_cfg2&=~(0x01<<3);

//regs0->sft_cfg14 &=~(0x1<<6);//S_RGB ENABLE on Pin225~233
//regs0->sft_cfg14 |=(0x1<<7);
regs0->sft_cfg14 |=(0x1<<8);//S_RGB SYNC Enable on pin 205, pin206
regs0->sft_cfg14 |=(0x1<<9);
regs0->sft_cfg14 &=~(0x1<<10);
/*regs0->tv_pccon[0] = 52;   		// a. HSYNC falling pixel
regs0->tv_pccon[1] = 53+20;		// b. HSYNC rising pixel
regs0->tv_pccon[6] = 1;     		// c. Top Vsync falling line       
regs0->tv_pccon[7] = 4;              		// d. Top Vsync rising line        
regs0->tv_pccon[8] = 313;   		// e. Bottom Vsync falling line
regs0->tv_pccon[9] = 316;   		// f. Bottom Vsync rising line
regs0->tv_pccon[0] = 22;           // a. HSYNC falling pixel
regs0->tv_pccon[1] = 23+20;        // b. HSYNC rising pixel
regs0->tv_pccon[6] = 525;                 // c. Top Vsync falling line
regs0->tv_pccon[7] = 3;                         // d. Top Vsync rising line
regs0->tv_pccon[8] = 263;           // e. Bottom Vsync falling line
regs0->tv_pccon[9] = 266;           // f. Bottom Vsync rising line
*/
regs0->tv2_srgb_mode0|=(0x1<<0); 
#elif defined(IC_8202D)&& defined(S_RGB_TYPE2)//kenny 2005/5/19 for S-RGB
regs0->sdc_data_cnt[6][0] |= (0x0e);//Disable ROM_A20(Pin225),ROM_A21(Pin226),ROM_A22(Pin227) as GPIO92,93,94
regs0->sft_cfg2&=~(0x01<<2);//disable Uart0
regs0->sft_cfg2&=~(0x01<<3);
regs0->sft_cfg14 &=~(0x1<<6);//S_RGB ENABLE on Pin225~233
regs0->sft_cfg14 |=(0x1<<7);
regs0->sft_cfg14 |=(0x1<<8);//S_RGB SYNC Enable on pin 205, pin206
regs0->sft_cfg14 |=(0x1<<9);
regs0->sft_cfg14 &=~(0x1<<10);

#if 1 //for AU A036QN01 (SRGB_UPS051, 960x240)
    SRGB_Setup(SRGB_ON,SRGB_NTSC,SRGB_UPS051,SRGB_HMODE_960,240,
               SRGB_ENCODE_ALL_LINE_FROM_FIRST_PIXEL_BIT|SRGB_UPS051_MODE_BIT);
#else //for AU A015AN02 (SRGB_UPS052, 280x220)
    SRGB_Setup(SRGB_ON,SRGB_NTSC,SRGB_UPS052,SRGB_HMODE_280,220,
               SRGB_ENCODE_ALL_LINE_FROM_FIRST_PIXEL_BIT|SRGB_UPS052_MODE_BIT);
#endif


#endif//CCIR656_TYPE1 in MP_BOARD_256_PIN_NON_SHARE 

#elif defined(MP_BOARD_216_PIN_NON_SHARE)

#if defined(IC_8202D)&& defined(CCIR656_TYPE3) //kenny 2005/2/16 for 8202D IC
regs0->sft_cfg1 &=~(0x1<<3);//disable pin66 ROM_CS4
regs0->sft_cfg4 &=~(0x1<<6); //disable pin55 DFCT
regs0->sft_cfg7 |=(0x1<<4); //CCIR656 ENABLE on Pin55~66
regs0->sft_cfg7 |=(0x1<<5);
#elif defined(IC_8202D)&& defined(CCIR656_TYPE2)	//ronnie for 8202D 216pin
regs0->sft_cfg7 |= (0x1<<4);
regs0->sft_cfg7 &= ~(0x1<<5);
#elif defined(IC_8202D)&& defined(S_RGB_TYPE1)
regs0->sft_cfg14 &= ~(0x1<<1); //disable SPI_CS_B ,!!! must be first disable
regs0->sft_cfg4 &=~(0x1<<6); //disable pin55 DFCT
regs0->sft_cfg1 &=~(0x1<<3);//disable pin66 ROM_CS4

//set Hsysnc, Vsync for pin 67, pin 68 test
regs0->sft_cfg1 &= ~(0x1 << 2);//GPIO17
regs0->sft_cfg1 &= ~(0x1 << 1);//GPIO18
GPIO_M_SET(17, 1);
GPIO_M_SET(18, 1); 
regs0->sft_cfg14 |= (0x1<<8);
regs0->sft_cfg14 &= ~(0x1<<9);
regs0->sft_cfg14 &= ~(0x1<<10);



//disable Pin52 FGIN
//regs0->sft_cfg4 &= ~(1<<5);
//regs0->sft_cfg14 |= (0x3<<11);//enable pin52 RGB enable

regs0->sft_cfg14 |=(0x1<<7); //serial RGB ENABLE on Pin55~66
regs0->sft_cfg14 |=(0x1<<6);


//zyl and Joy added to configure SRGB
#if 1 //for AU A036QN01 (SRGB_UPS051, 960x240)
    SRGB_Setup(SRGB_ON,SRGB_NTSC,SRGB_UPS051,SRGB_HMODE_960,240,
               SRGB_ENCODE_ALL_LINE_FROM_FIRST_PIXEL_BIT|SRGB_UPS051_MODE_BIT);
#else //for AU A015AN02 (SRGB_UPS052, 280x220)
    SRGB_Setup(SRGB_ON,SRGB_NTSC,SRGB_UPS052,SRGB_HMODE_280,220,
               SRGB_ENCODE_ALL_LINE_FROM_FIRST_PIXEL_BIT|SRGB_UPS052_MODE_BIT);
#endif

#endif  //IC_8202D
 

#endif  //MP_BOARD_216_PIN_NON_SHARE
#else   //8210
regs0->sft_cfg6 |= (0x1 << 14); //CCIR656 ENABLE
regs0->sft_cfg3 |= (0x7 << 9);  //CCIR SYNC FROM PIN185,186
regs0->sft_cfg2 &= ~(0xf << 5);     //UART1 SELECT
//regs0->osd_tv_out |=(0x1 << 1);   //Cb\Cr SWAP
regs0->osd_tv_out |=(0x1 << 3); //CCIR EDGE SELECT
//regs0->sft_cfg2 |= (0x7 << 9);    //TV_LCD RGB ENABLE
//regs0->ri_misc_b0 |= (0x3<<11);   //VIDEO CLK SELECT
#endif
#endif//#ifdef DIGITAL 
}

