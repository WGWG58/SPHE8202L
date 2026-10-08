  #define VFD_BACK_COLOR_RED        3 //GPIO 17 ca720 pin29
  #define VFD_BACK_COLOR_GREEN    2 //GPIO 18 ca720 pin28
  #define VFD_BACK_COLOR_BLUE    4 //GPIO 19 ca720 pin163

void Polling_VFD_back_color()
{

  ReadFromI2c(0xa0, 206,(BYTE *)&vfd_color,1);
  switch (vfd_color)
  {
  	case 0:
  	GPIO_O_SET(VFD_BACK_COLOR_RED,0);
  	GPIO_O_SET(VFD_BACK_COLOR_GREEN,0);
	GPIO_O_SET(VFD_BACK_COLOR_BLUE,0);
	  break;
	case 1:
  	GPIO_O_SET(VFD_BACK_COLOR_RED,0);
  	GPIO_O_SET(VFD_BACK_COLOR_GREEN,0);
	GPIO_O_SET(VFD_BACK_COLOR_BLUE,1);
	  break;
	case 2:
  	GPIO_O_SET(VFD_BACK_COLOR_RED,0);
  	GPIO_O_SET(VFD_BACK_COLOR_GREEN,1);
	GPIO_O_SET(VFD_BACK_COLOR_BLUE,0);
	  break;
	case 3:
  	GPIO_O_SET(VFD_BACK_COLOR_RED,0);
  	GPIO_O_SET(VFD_BACK_COLOR_GREEN,1);
	GPIO_O_SET(VFD_BACK_COLOR_BLUE,1);
	  break;
	case 4:
  	GPIO_O_SET(VFD_BACK_COLOR_RED,1);
  	GPIO_O_SET(VFD_BACK_COLOR_GREEN,0);
	GPIO_O_SET(VFD_BACK_COLOR_BLUE,0);
	  break;
	case 5:
  	GPIO_O_SET(VFD_BACK_COLOR_RED,1);
  	GPIO_O_SET(VFD_BACK_COLOR_GREEN,0);
	GPIO_O_SET(VFD_BACK_COLOR_BLUE,1);
	  break;
	case 6:
  	GPIO_O_SET(VFD_BACK_COLOR_RED,1);
  	GPIO_O_SET(VFD_BACK_COLOR_GREEN,1);
	GPIO_O_SET(VFD_BACK_COLOR_BLUE,0);
	  break;
	case 7:
  	GPIO_O_SET(VFD_BACK_COLOR_RED,1);
  	GPIO_O_SET(VFD_BACK_COLOR_GREEN,1);
	GPIO_O_SET(VFD_BACK_COLOR_BLUE,1);
	  break;
	default:
	GPIO_O_SET(VFD_BACK_COLOR_RED,1);
  	GPIO_O_SET(VFD_BACK_COLOR_GREEN,1);
	GPIO_O_SET(VFD_BACK_COLOR_BLUE,1);
	  break; 
   }	
}	

void chang_vfd_back_color_up(void)
{
    if(!Is_JPEG_SlideMode())  
        {
         if(vfd_color<=5)
	      vfd_color++;
          else
          vfd_color=0; 
          WriteToI2c(0xa0, 206,(BYTE *)&vfd_color,1);         
        }
     else
        invalid_key();     
}
void chang_vfd_back_color_down(void)
{	 if(!Is_JPEG_SlideMode())   
   {   
      if(vfd_color>=1)
      vfd_color--;
      else
      
      vfd_color=6; 
     WriteToI2c(0xa0, 206,(BYTE *)&vfd_color,1);
   } 
   else
     invalid_key();  	
   
}


