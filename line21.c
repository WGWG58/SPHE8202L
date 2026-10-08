
#include "config.h"
#include "global.h"
#include "regmap.h"
#include "iop.h"
#include "viddec.h"
#include "tvif.h"
#include "line21.h"

#define	tv_l21_ready()	(WaitIopFunRdy(0)>=0)


void	reset_line21(void)
{
  line21_data_wp = line21_data_rp = 0;
}


static inline void	polling_l21(void)
{
  if (line21_now && tv_l21_ready())
  {
    if (line21_data_rp==line21_data_wp)
    {
      line21_now = 0;
    }
    else
    {
      unsigned d;
      UINT8	*l21_data = line21_data+3*line21_data_rp;
      UINT8	l21_flag = l21_data[0];

      switch (line21_now)
      {
        case LINE21_UPDATE_TOP:
	  if ((l21_flag&0x80) == 0) line21_now=0;
	  else if ((l21_flag&0x7f) != 0x7f)
	  {
	    line21_now=0;
	    if (++line21_data_rp>=LINE21_SIZE) line21_data_rp=0;
	  }
	  else
	  {
	    d = l21_data[1];
    	    tv_writel21_data(0,d);
	    line21_now = LINE21_UPDATE_TOP2;
	  }
	  break;

        case LINE21_UPDATE_TOP2:
	  line21_now = 0;
	  d = l21_data[2];
	  tv_writel21_data(1,d);
	  if (++line21_data_rp>=LINE21_SIZE) line21_data_rp=0;
	  break;
	 
        case LINE21_UPDATE_BOTTOM:
	  if ((l21_flag&0x80) != 0) line21_now=0;	// it's top
	  else if ((l21_flag&0x7f) != 0x7f)
	  {
	    line21_now=0;
	    if (++line21_data_rp>=LINE21_SIZE) line21_data_rp=0;
	  }
	  else
	  {
	    line21_now = LINE21_UPDATE_BOTTOM2;
	    d = l21_data[1];
	    tv_writel21_data(2,d);
	  }
	  break;
        case LINE21_UPDATE_BOTTOM2:
	  line21_now = 0;
	  d = l21_data[2];
	  tv_writel21_data(3,d);
	  if (++line21_data_rp>=LINE21_SIZE) line21_data_rp=0;
	  break;
        default: line21_now = LINE21_UPDATE_NONE;
      }
    }
  }
}


