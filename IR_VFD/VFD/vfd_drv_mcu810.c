//FUNCTION:  
//1. Write SET cmd to MCU810 
//2. Write IR customer ID and POWER KEY value 
//note: if only set cmd ,call write_pmp_mcu810( bCmd, 0) 
void write_pmp_mcu810(BYTE bCmd, BYTE bData) 
{    
    switch(bCmd) 
    { 
        case CMD_PMP_IS_BUSY: 
             regs0->iop_data[2] = (bCmd<<8)|bData; 
        	 regs0->iop_data[0] = (regs0->iop_data[0] & 0x0ff8) 
        	  | (FUN_PMP_MCU810 | PMP_IS_BUSY);    
        	 WaitIopFunRdy(IOP_RDY_WAIT);              
             break; 
        case CMD_PMP_IS_UNBUSY: 
             regs0->iop_data[2] = (bCmd<<8)|bData; 
        	 regs0->iop_data[0] = (regs0->iop_data[0] & 0x0ff8)  
        	 | (FUN_PMP_MCU810 | PMP_IS_UNBUSY);    
        	 WaitIopFunRdy(IOP_RDY_WAIT);                      
             break; 
        case CMD_PMP_POWER_OFF: 
             regs0->iop_data[2] = (bCmd<<8)|bData; 
        	 regs0->iop_data[0] = (regs0->iop_data[0] & 0x0ff8)  
        	 | (FUN_PMP_MCU810 | PMP_POWER_OFF);   
        	 WaitIopFunRdy(IOP_RDY_WAIT);                  
             break; 
        case CMD_WRITE_IR_HEAD_H: 
             regs0->iop_data[2] = (bCmd<<8)|bData; 
        	 regs0->iop_data[0] = (regs0->iop_data[0] & 0x0ff8)  
        	 | (FUN_PMP_MCU810 | WRITE_IR_HEAD_H);  
        	 WaitIopFunRdy(IOP_RDY_WAIT);   
             break; 
        case CMD_WRITE_IR_HEAD_L: 
             regs0->iop_data[2] = (bCmd<<8)|bData; 
        	 regs0->iop_data[0] = (regs0->iop_data[0] & 0x0ff8)  
        	 | (FUN_PMP_MCU810 | WRITE_IR_HEAD_L);     	 
        	 WaitIopFunRdy(IOP_RDY_WAIT);    
             break; 
        case CMD_WRITE_POWER_KEY: 
             regs0->iop_data[2] = (bCmd<<8)|bData;              
        	 regs0->iop_data[0] = (regs0->iop_data[0] & 0x0ff8)  
        	 | (FUN_PMP_MCU810 | WRITE_POWER_KEY);     
        	 WaitIopFunRdy(IOP_RDY_WAIT);  
             break;         
        default: 
             regs0->iop_data[2] = (bCmd<<8)|bData; 
        	 regs0->iop_data[0] = (regs0->iop_data[0] & 0x0ff8) 
        	  | (FUN_PMP_MCU810 | PMP_IS_BUSY);    
        	 WaitIopFunRdy(IOP_RDY_WAIT);              
             break;   
    } 
} 
#ifdef PMP_MCU810 
#include "fsNAV.h"
BYTE Bat_Data;
void polling_vfdr(void) 
{ 
   static BYTE keydata; 

   keydata=(BYTE)(regs0->iop_data[3]&0x00ff); 
   Bat_Data=(BYTE)((regs0->iop_data[7]&0xff00)>>8); 
  /* if(keydata)
  { printf("yangli=%2d\n",keydata);
   psprintf(RegionValStr[REGION1], "KEY %02d F:%d", keydata,Bat_Data);
   PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
}*/
   switch(keydata)
   {
   	 case 0x01:pmpkey_up();delay_1ms(40);keydata=0; break;
   	 case 0x08:pmpkey_down();delay_1ms(40);keydata=0;break;
   	 case 0x06:pmpkey_right();delay_1ms(40);keydata=0;break;
   	 case 0x03:pmpkey_left();delay_1ms(40);keydata=0;break;
   	 case 0x09:pmpkey_return();delay_1ms(40);keydata=0;break;
   	 case 0x07:pmpkey_select();delay_1ms(40);keydata=0;break;
   	 case 0x05:pmpkey_lcd();delay_1ms(40);keydata=0;break;
   	 case 0x0a:ircmd_forward();delay_1ms(40);keydata=0;break;
   	 case 0x04:ircmd_backward();delay_1ms(40);keydata=0;break;
   	 
   }


}

int batflag=0;
void Show_PMP_Bat(void)
{int bat;
  bat=Bat_Data;  
	if (bat>=(0xff-Bat_var))
      {
      	batflag=3;Drawpic_Bat(batflag);
      }
   else if(((0xff-2*Bat_var)<=bat)&&(bat<(0xff-Bat_var)))
      {
      	batflag=2;Drawpic_Bat(batflag);
      	}
   else if(((0xff-3*Bat_var)<=bat)&&(bat<(0xff-2*Bat_var)))
      {
      	batflag=1;Drawpic_Bat(batflag);
      	}
   else if(bat<(0xff-3*Bat_var))
      {
      	batflag=0;Drawpic_Bat(batflag);
    } 
   //s else if(bat<(0xff-4*Bat_var))
    //psprintf(RegionValStr[REGION2], "KEY: %d bat:%x", batflag, Bat_Data); 
  // PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1); 
       // system_sleep();  
   
}
 
	 
void Drawpic_Bat( int flag)
{ 
	switch(flag) 
    {
    	case 0:
    	DrawRect(280,18,40,20, 0,WHITE_Y,WHITE_CRCB);
	    DrawRectEdge(280, 18, 40,20, 0x40,BK_GROUNDCRCB);
        DrawRectEdge(320, 25, 4,6, 0x40,BK_GROUNDCRCB);
        //DrawRect(280,20,20,20, 0,0x40,BK_CRCB);
        break;
        case 1:
        DrawRect(293,18,27,20, 0,WHITE_Y,WHITE_CRCB);
        DrawRect(281,22,12,12, 0,0x60,0x7070);
        DrawRectEdge(280, 18, 40,20, 0x40,BK_GROUNDCRCB);
        DrawRectEdge(320, 25, 4,6, 0x40,BK_GROUNDCRCB);
        break;
        case 2:
        DrawRect(307,18,13,20, 0,WHITE_Y,WHITE_CRCB);
        DrawRect(281,20,12,16, 0,0x60,0x7070);
        DrawRect(295,20,12,16, 0,0x60,0x7070);
        DrawRectEdge(280, 18, 40,20, 0x40,BK_GROUNDCRCB);
        DrawRectEdge(320, 25, 4,6, 0x40,BK_GROUNDCRCB);
        break;
        case 3:
        DrawRect(281,20,12,16, 2,0x60,0x7070);
        DrawRect(295,20,12,16, 2,0x60,0x7070);
        DrawRect(309,20,11,16, 2,0x60,0x7070);
        DrawRectEdge(280, 18, 40,20, 0x40,BK_GROUNDCRCB);
        DrawRectEdge(320, 25, 4,6, 0x40,BK_GROUNDCRCB);
        break;
     }
} 
#endif

