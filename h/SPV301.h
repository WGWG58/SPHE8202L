#ifndef	__SPV301_H__
#define	__SPV301_H__
void init_spv301(void);
void set_SPV301_PLL(unsigned char in_format,unsigned char out_id);
void L1_301intiming(unsigned char format);//for use Port A only.Modifed by ChenZhao on 2004-10-13 16:18  
void	init_sii164(void);
void set_output_timing(unsigned char in_format,unsigned char out_id);
void set_scale_table(unsigned char out_id);
void clear_sdram(void);
void set_unblanking(void);
void L2_SCA_Set_H_Table(unsigned char *tab ) ;
void L2_SCA_Set_V_Table(unsigned char *tab) ;
void Output_signal(unsigned char signal);              //set the gpio of 311 inorder to disable the output of VGA signal
void HD_display(unsigned char id);
void close_pll(unsigned char num);
void PbPr_display(void);
void L1_Txtosd_LoadLUT(unsigned char *LutTable) ;
//void L2_Txtosd_MenuSize(unsigned char W, unsigned char D) ;
void L2_Txtosd_MenuXY(unsigned short int X, unsigned short int Y) ;

void scaler_main(void);
#ifdef COMP
void verify_reg(void);
#endif
void init_scaler(void);
#endif

