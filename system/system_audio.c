#include "auddrv.h"

//ycwen 2005/11/15 use fun pointer to make auddrv.a clear!
#ifdef INTERNAL_AUDIO_DAC
    extern void __internal_dac_setting(int index);        
    extern void __internal_dac_reset();
    void    (*internal_dac_setting)(int index) = __internal_dac_setting;    
    void    (*internal_dac_reset)()= __internal_dac_reset;
#else
    void internal_dac_null_func1(int index __attribute__((unused))) {}            
    void internal_dac_null_func2() {printf("\n########### 2 ###############\n");}
    void	(*internal_dac_setting)(int index) = internal_dac_null_func1;
    void	(*internal_dac_reset)() = internal_dac_null_func2;
#endif

