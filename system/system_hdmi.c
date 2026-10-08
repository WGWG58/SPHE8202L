/*
  Create: by Eric Lin

   Date         who             what
   ----------------------------------------------------------------
   060720       Eric Lin       function pointer for 6500 DAC Marcovision    

*/

#ifdef	SUPPORT_6500
extern void SCL_6500_setup_mv(const UINT8 mv_type, const UINT8 p[], const UINT16 amamp);
void (*sp8200tv_external_mv)(int a, int b, int c) = SCL_6500_setup_mv;
#else	// SUPPORT_6500
void NULL_sp8200tv_external_mv(int a, int b, int c){a=a;b=b;c=c;}
void (*sp8200tv_external_mv)(int a, int b, int c) = NULL_sp8200tv_external_mv;
#endif	// SUPPORT_6500

