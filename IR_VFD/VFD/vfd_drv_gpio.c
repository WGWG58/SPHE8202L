/*
history:
2004-7-19 14:43
         wanghaoying move the following functions for nec16312 here
2004-7-7 14:25  
        lijd
        Process 16312sw use for:
        1. extern pannel key
        2. volume button 
        note: need define NEC16312SW in cust_def.h
*/

/*
** FUNCTION
** polling_vfdr
**
** DESCRIPTION
** check if polling-ready
*/

void polling_vfdr(void)  //nec16321 type vfd
{
#if defined(GPIO_KEY_LIGHT)//SUPPORT_VFD nono 3-8-18 14:41
    check_gpio_keylight_status();
#elif defined(USE_VFDPORT_TRANDATA)
    Communication_And_MCU4051();	   
#endif//SUPPORT_VFD

}

