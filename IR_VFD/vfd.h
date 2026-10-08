#ifndef	__VFD_H
#define	__VFD_H

#include "user_init.h"

#ifdef PMP_MCU810
#define	CMD_PMP_IS_BUSY		    0x83
#define	CMD_PMP_IS_UNBUSY		0x82
#define	CMD_PMP_POWER_OFF		0xe0
#define	CMD_WRITE_IR_HEAD_H		0xa0
#define	CMD_WRITE_IR_HEAD_L		0xa1
#define	CMD_WRITE_POWER_KEY		0xa2

#define	PMP_IS_BUSY		        1
#define	PMP_IS_UNBUSY		    2
#define	PMP_POWER_OFF		    3
#define	WRITE_IR_HEAD_H		    4
#define	WRITE_IR_HEAD_L		    5
#define	WRITE_POWER_KEY		    6
#define Bat_var  21
void write_pmp_mcu810(BYTE bCmd, BYTE bData);
#endif


#ifdef TP6317_PANNEL   //yaowh add 04-10-25
  #define IR_USER_CODE_LOW8	0xff	//user code 
  #define IR_USER_CODE_HIGHT8	0xff
  #define TP6317_IR_CODE1	0xFF	//key code
  #define TP6317_IR_CODE2	0xFF
  #define TP6317_IR_CODE3	0xff	//0xff==>unuse
  #define TP6317_IR_CODE4	0xff
  #define TP6317_IR_CODE5	0xff
  #define TP6317_IR_CODE6	0xff
  #define TP6317_IR_CODE7	0xff
  #define TP6317_IR_CODE8	0xff
  #define TP6317_VFD_KEY_CODE1	0xff   //Key7~Key0  all keys could weak up
  #define TP6317_VFD_KEY_CODE2	0xff   //Key15~Key8
  #define TP6317_VFD_KEY_CODE3	0xff   //Key23~Key16
  BYTE Read_SW(void);
  void define_standbykey(void);
  void Power_off_define_TP6317_standbykey(void) ;
  void TP6317_int(void);
#endif

#define  MONE_VFDR    //must open if use panel  11/22
///*  VFD Driver definition  
//**  NEC series VFD controller receive command with LSB first 
//*/  MN12510 command format is MSB first 
#define	VFDC_SET_DISP_13D15S    0x0c           /* add by chichang 2001 6/6 */ 
#define VFDC_SET_DISP_12D16S    0x0b		   // add by shawn 910131	
#define VFDC_SET_DISP_10D18S    0x09		   // add by shawn 910131	
#define VFDC_SET_DISP_11D18S	0x0a		





#if (VFD_DRIVER == NEC16312)

#define	VFDC_SET_DISP			(0<<6)
#define	VFDC_SET_DATA			(1<<6)
#define	VFDC_SET_ADDR			(3<<6)
#define	VFDC_DISP_CTRL			(2<<6)

#define	VFDC_SET_DISP_4D16S		(0<<0)
#define	VFDC_SET_DISP_5D16S		(1<<0)
#define	VFDC_SET_DISP_6D16S		(2<<0)
#define	VFDC_SET_DISP_7D15S		(3<<0)
#define	VFDC_SET_DISP_8D14S		(4<<0)
#define	VFDC_SET_DISP_9D13S		(5<<0)
#define	VFDC_SET_DISP_10D12S	(6<<0)
#define	VFDC_SET_DISP_11D11S	(7<<0)

#define	VFDC_SET_DATA_DISP		(0<<0)
#define	VFDC_SET_DATA_LED		(1<<0)
#define	VFDC_SET_DATA_READKEY	(2<<0)
#define	VFDC_SET_DATA_READSW	(3<<0)

#define	VFDC_SET_DATA_AUTOINC	(0<<2)
#define	VFDC_SET_DATA_FIXED		(1<<2)

#define	VFDC_SET_DATA_TEST		(1<<3)
#define	VFDC_SET_DATA_NORMAL	(0<<3)

#define	VFDC_DISP_CTRL_ON		(1<<3)
#define	VFDC_DISP_CTRL_OFF		(0<<3)

#define	VFDC_DISP_CTRL_1_16		(0<<0)
#define	VFDC_DISP_CTRL_2_16		(1<<0)
#define	VFDC_DISP_CTRL_4_16		(2<<0)
#define	VFDC_DISP_CTRL_10_16	(3<<0)
#define	VFDC_DISP_CTRL_11_16	(4<<0)
#define	VFDC_DISP_CTRL_12_16	(5<<0)
#define	VFDC_DISP_CTRL_13_16	(6<<0)
#define	VFDC_DISP_CTRL_14_16	(7<<0)

#elif (VFD_DRIVER==AD7312)

#define	VFDC_SET_DISP			(0<<6)
#define	VFDC_SET_DATA			(1<<6)
#define	VFDC_SET_ADDR			(3<<6)
#define	VFDC_DISP_CTRL			(2<<6)

#define	VFDC_SET_DISP_4D16S		(0<<0)
#define	VFDC_SET_DISP_5D16S		(1<<0)
#define	VFDC_SET_DISP_6D16S		(2<<0)
#define	VFDC_SET_DISP_7D15S		(3<<0)
#define	VFDC_SET_DISP_8D14S		(4<<0)
#define	VFDC_SET_DISP_9D13S		(5<<0)
#define	VFDC_SET_DISP_10D12S	(6<<0)
#define	VFDC_SET_DISP_11D11S	(7<<0)

#define	VFDC_SET_DATA_DISP		(0<<0)
#define	VFDC_SET_DATA_LED		(1<<0)
#define	VFDC_SET_DATA_READKEY	(2<<0)
#define	VFDC_SET_DATA_READSW	(3<<0)

#define	VFDC_SET_DATA_AUTOINC	(0<<2)
#define	VFDC_SET_DATA_FIXED		(1<<2)

#define	VFDC_SET_DATA_TEST		(1<<3)
#define	VFDC_SET_DATA_NORMAL	(0<<3)

#define	VFDC_DISP_CTRL_ON		(1<<3)
#define	VFDC_DISP_CTRL_OFF		(0<<3)

#define	VFDC_DISP_CTRL_1_16		(0<<0)
#define	VFDC_DISP_CTRL_2_16		(1<<0)
#define	VFDC_DISP_CTRL_4_16		(2<<0)
#define	VFDC_DISP_CTRL_10_16	(3<<0)
#define	VFDC_DISP_CTRL_11_16	(4<<0)
#define	VFDC_DISP_CTRL_12_16	(5<<0)
#define	VFDC_DISP_CTRL_13_16	(6<<0)
#define	VFDC_DISP_CTRL_14_16	(7<<0)

#elif (VFD_DRIVER==HT1621)

#define VFD_CMD_WR          0xa0
#define SYS_EN	            0x0802
#define TIMER_DIS           0x0808
#define WDT_DIS             0x080A
#define BIAS_1_3            0x0852
#define LCD_ON              0x0806
#define LCD_OFF             0x0810

#else        //FOR SPL10

#define SPL10_DUTY_BIAS     0x83
#ifdef  SPL10_KEY_5x4
#define SPL10_KEY_MODE      0x90
#elif   defined(SPL10_KEY_4x4)
#define SPL10_KEY_MODE      0x91
#elif   defined(SPL10_KEY_3x4F_B)
#define SPL10_KEY_MODE      0x93
#else 
#define SPL10_KEY_MODE      0x90
#endif

#endif 


#endif/*__VFD_H*/

