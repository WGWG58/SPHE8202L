/*
*  Terry,2004/2/10 03:34PM
*/

//=================================================================
//for DVD setup menu reengineering  //added by JS   //20040728

#ifdef DVD_SETUP_REENG
        
    //nono move to setup_item_reeng_include.c 5-5-9 16:58
    #include "setup_item_reeng_include.c"
    
#elif defined(EASTECH_DP3240_SETUP_MENU)
    #include ".\\Customers\\eastech\\eastech_3240_setup_item.c"
#else
	
    //nono move to setup_item_no_reeng.c 5-5-9 16:58
    #include "setup_item_no_reeng.c"
    
    #ifdef SUPPORT_FUNCTION_MENU//who include?//maybe portable?
        #include "setup_item_plus.c"
#endif
    #ifdef SUPPORT_DISPLAY_MENU//who include?//maybe portable?
        #include "setup_display_item.c"
              #endif
    
    
#endif  ////end of DVD_SETUP_REENG
//===========================================ending=================================


