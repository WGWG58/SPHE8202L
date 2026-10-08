/*
* Terry,2004/8/4 09:59AM
* Navigation Customerize Code
*
*/
#include "user_init.h"
#include "navdata.h"
#include "kinf.h"

//-----------------------  extern function --------------------------------------
extern void sup_select_subtitles(int n);

//sup_select_subtitles(1): 1 sub-title
//sup_select_subtitles(2): 2 sub-title
void nav_menu_sel_subp_no(void)
{
#ifdef TWO_SUBTITLE//terry,2004/8/4 09:39AM
      if( (pDSV->CurrDomain!=TT_DOM)||(pDSV->dAv_SPST_Ns==1) )    sup_select_subtitles(1);      
#endif                
}

//------------------------  ending ----------------------------------------------
