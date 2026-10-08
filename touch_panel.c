/*******************************************************************
touch_panel.c: 
	Description:
	    In this file,four_line_resistense touch panel ,whose driver is  TSC2003 which supports
	  I2C communication, was used in the  portable DVD .Of course ,other drivers also can be 
	  used,such as ADS7846 ,whose communication method is SPI.
				                                                       lichuanyue 2006-07-10
*********************************************************************/

#include "user_init.h"
#include "global.h"

#if defined(SUPPORT_TOUCH_PANEL)
 #ifdef driver_TSC2003
 #include "touch_panel.h"
 #include "c_i2c.h"
 #include "iop.h"
 #include "memmap_I2C.h"

/*Address Byte
1    0    0    1    0     A1    A0    R/W
|_____________|   |_____|   
  
    fixed bits            input pins   read"1"/write"0"
*/
#define TSC2003_write 0x90 //1001 0000
#define TSC2003_read  0x91 //1001 0001

/*Command Byte 
C3   C2   C1   C0    PD1   PD0     M     X
|_____________|   |______|
  
Configuration bits     power_down bits   mode bit   reserved
*/
#define command_tem0  0x00//0000 0000
#define command_Vbat1 0x10//0001 0000
#define command_in1     0x20//0010 0000
// 0011 0000 reserved
#define command_tem1  0x40//01000000
#define command_Vbat2 0x50//0101 0000
#define command_in2     0x60//0110 0000
//0111 0000 reserved
#define activate_x_driver  0x80// 1000 0000
#define activate_x_driver  0x90//1001 0000
#define activate_xy_driver     0xa0//1010 0000
//1011 0000 reserved
#define command_x   0xc0 //1100 0000
#define command_y   0xd0 //1101 0000
#define command_z1 0xe0 //1110 0000
#define command_z2 0xf0 //1111 0000

#define e2prom_write 0xa0
#define e2prom_read 0xa1
#if 0
#define x0_add TOUCH_PANEL_ADDR
#define y0_add (TOUCH_PANEL_ADDR+1)
#define dx_add (TOUCH_PANEL_ADDR+2)
#define dy_add (TOUCH_PANEL_ADDR+3)
#endif
#define lcd_high  480
#define lcd_width  720

 BYTE Touch_x_now;
 BYTE Touch_y_now;
 BYTE Count_10ms;
 BYTE  Lcd_x;
 BYTE  Lcd_y;
//The four variables are used at the panel exchange!
 
 BYTE  X0;
 BYTE  Y0;
 BYTE  Dx;
 BYTE  Dy;
 BYTE Touch_x[10];                                                                                                                            
 BYTE Touch_y[10];

 BYTE flag_revise;
 BYTE revise_count;
 BYTE Revise_x[4];                                                                                                                            
 BYTE Revise_y[4];
 BYTE TSC2003_FLAG;

void
polling_tsc2003_10ms()
{    
      if(is_touched()==1)
	  	{ //&&judge_operating_temp()==1
	  	   Touch_x[Count_10ms]=get_x_coordinate();
                 Touch_y[Count_10ms]=get_y_coordinate();
		   Count_10ms=Count_10ms+1;
		   printf("Count_10ms is :%d\n",Count_10ms);
		   if(Count_10ms==10)
		  	{
		  	   Count_10ms=0;
                     }		  	
	  	}
	else 
		{
		int i;
		for(i=0;i<10;i++)
			{
		        Touch_x[i]=0;
                      Touch_y[i]=0;
			}
		 #ifndef DVDRELEASE
		   printf("There is no touch in the four-line-touch-screen!\n");
		 #endif
		}
}

void 
polling_tsc2003_100ms()
{
   int i;
   int sum_x=0;
   int sum_y=0;
   for(i=0;i<10;i++)
   	{
          printf("%d,%d\n",Touch_x[i],Touch_y[i]);
   	   sum_x=sum_x+Touch_x[i];
	   sum_y=sum_y+Touch_y[i];
   	}
     Touch_x_now=sum_x/10;
     Touch_y_now=sum_y/10;
 #ifndef DVDRELEASE
         printf("Touch_x_now,Touch_y_now are %d,%d\n",Touch_x_now,Touch_y_now);
  #endif
     //coordinate_exchange();
/*
After coordinate exchanged ,wo can use the pels coordinates to 
do the operation function as well as you like!
*/
}

void
write_tsc2003(unsigned char addr,  unsigned char  command)
{
	unsigned char loop;
	for (loop=0;loop<100;loop++)
	{
          i2c_start_sig();
          if(0==i2c_byte_w(addr)) 
                if(0==i2c_byte_w(command))
                {
                    i2c_stop_sig();  
                    break;
                }
          init_i2c();
	}
    #ifndef DVDRELEASE
	if (loop == 100) 
	 {
	    printf("\t TSC2003 Write error Sub-addr 0x%x\n",addr);
	 }
   #endif
}


unsigned char read_tsc2003(unsigned char deviceadd)
{
	unsigned char data=0;
	unsigned char loop;
      for (loop=0;loop<100;loop++)
	{
    	i2c_start_sig();
    	if(0==i2c_byte_w (deviceadd)) 
      {
            data=i2c_byte_r(1);
            i2c_stop_sig();  
            break;
        }
    	init_i2c();
	}
	  
    #ifndef DVDRELEASE
	if (loop == 100) 
		{
                printf("\t TSC2003 read error Sub-addr 0x%x\n",deviceadd);
		}
   #endif
   
    return   data;
}


int
 get_x_coordinate()
{  
    unsigned char X;
    write_tsc2003( TSC2003_write,command_x );
    X= read_tsc2003(TSC2003_read);
    return X;
}

int
get_y_coordinate()
{  
    unsigned char Y;
    write_tsc2003( TSC2003_write,command_y );
    Y= read_tsc2003(TSC2003_read);
    return Y;
}

int 
get_tem0()
{
    BYTE tem0;
    write_tsc2003( TSC2003_write,command_tem0);
    tem0= read_tsc2003(TSC2003_read);
    return tem0;
}

int 
get_tem1()
{
    BYTE tem1;
    write_tsc2003( TSC2003_write,command_tem1);
    tem1= read_tsc2003(TSC2003_read);
    return tem1;
}

#ifdef Touch_Panel_PQ063XRA   
int is_touched()
{  
     BYTE X;
     BYTE Y;
    write_tsc2003( TSC2003_write,command_x );
    X= read_tsc2003(TSC2003_read);
    write_tsc2003( TSC2003_write,command_y );
    Y= read_tsc2003(TSC2003_read);

     if(X>=240||X<=10)
     	{
         if (Y>=240||Y<=10)
   	     {
   	        return 0;//no touch in the screen
         	}
      else
   	{
          return 1;//have touch in the screen
   	}
     }
}

int judge_operating_temp()
{
   int temp=0;
   temp=get_tem1();
   if(temp>=-10&&temp<=60)
   	{
   	   return 1;//the opertating temperature is natural
   	}
   else
   	{
   	   return 0;//the opertating temperature is not natural
   	}
}
#endif


#if 0
int is_still_touched()
{
   
}

int 
is_left()
{

}
#endif

void
CalibrateTouchScreen()
{
  caculate_centerpoint();
  //store_tsc();
}

#if 0
void store_original_data()
{
  int  X_0=122;
  int  Y_0=122;
  int  d_x=1;
  int  d_y=1;
   
   WriteI2c(e2prom_write, x0_add,  X_0,1);
   WriteI2c(e2prom_write, y0_add,  Y_0,1);
   WriteI2c(e2prom_write, dx_add,  d_x,1);
   WriteI2c(e2prom_write, dy_add,  d_y,1);
   
   printf("Write the original coordinate exchange success!\n");
}
#endif
void
coordinate_exchange()
{    
   Lcd_x=((Touch_x_now-X0)/Dx)*lcd_width+(lcd_width/2);
   Lcd_y=((Touch_y_now-Y0)/Dy)*lcd_high+(lcd_high/2);
   printf("The touch points in LCD is (Lcd_x ,Lcd_y)=(%d,%d)\n",Lcd_x,Lcd_y);
}

void
get_revise_coordinate()
{
  if(flag_revise==1)
 	{
          Revise_x[revise_count]=Touch_x_now;
          Revise_y[revise_count]= Touch_y_now;
	   revise_count=revise_count+1;
	   if(revise_count==4)
	   	{
	   	  revise_count=0;
		  printf(" Calibrating touch screen is completed!\n");
	   	}
 	}
}

 void
caculate_centerpoint()
{
   int i;
   int s_x=0;
   int s_y=0;
   for(i=0;i<4;i++)
   	{
   	s_x=s_x+ Revise_x[i];
	s_y=s_y+Revise_y[i];
   	}
  X0=s_x/4;
  Y0=s_y/4;
  Dx=Revise_x[1]+Revise_x[2]-Revise_x[0]-Revise_x[3];
  Dy=Revise_y[1]+Revise_y[2]-Revise_y[0]-Revise_y[3];
  printf("The parameters are calulated completely!");
}
#if 0
int store_tsc()
{
   WriteI2c(e2prom_write, x0_add, X0, 1);
   WriteI2c(e2prom_write, y0_add, Y0, 1);
   WriteI2c(e2prom_write, dx_add, Dx, 1);
   WriteI2c(e2prom_write, dy_add, Dy, 1);
   printf("The parameters were stored completely!");
}

int get_stored_tsc()
{
   ReadFromI2c(e2prom_read,x0_add, &X0,1);
   ReadFromI2c(e2prom_read,y0_add, &Y0,1 );
   ReadFromI2c(e2prom_read,dx_add, &Dx,1);
   ReadFromI2c(e2prom_read,dy_add, &Dy,1 );
   printf("The parameter of (X0,Y0,Dx,Dy) is:(%d,%d,%d,%d)\n",X0,Y0,Dx,Dy);
}

#endif

/*
 Make Operation  UI ,which depends on the different requirement.
*/
#if 0
void 
make_operation_UI()
{
   

}

void make_calibration_UI()
{
  
}
 #endif
#endif  //end of #ifdef driver_TSC2003
#endif //end of #if defined(SUPPORT_TOUCH_PANEL)


