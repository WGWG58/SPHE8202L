/*//////////////////////////////
///////////radio_rds.h//////////
//////////xyy 2003-12-1 16:32///
*///////////////////////////////
#ifndef __RADIO_RDS_H
#define __RADIO_RDS_H


#ifdef SUPPORT_RDS_FUNCTION//xyy 2003-12-4 9:29
//#define SUPPORT_2B_GP  //the 2b type is rarely seen



#define PS_FUNC   1
#define PTY_FUNC  2
#define RT_FUNC   3
#define CT_FUNC   4
#define PTYN_FUNC 5


#define RDS_PS_RDY()    (psReadyFlag == 0x0f)
#define RDS_PTY_RDY()   (ptyReadyFlag == 0xff)
#define RDS_RTB_RDY()    (txtBreadyFlag == 0xffff)
#define RDS_RTA_RDY()   (txtAreadyFlag == 0xffff)
#define RDS_CT_RDY()    (ctReadyFlag == 0xff)
#define RDS_PTYN_RDY()   (ptynReadyFlag == 0x0f)

#define RDS_PS_CLR_RDY()  (psReadyFlag = 0)
#define RDS_PTY_CLR_RDY()  (ptyReadyFlag = 0)
#define RDS_RTB_CLR_RDY()  (txtBreadyFlag = 0)
#define RDS_RTA_CLR_RDY()  (txtAreadyFlag = 0)
#define RDS_CT_CLR_RDY()  (ctReadyFlag = 0)
#define RDS_PTYN_CLR_RDY()  (ptynReadyFlag = 0)

#define RDS_RT_TYPE()    (radio_text_type)

char * rds_get_ps(void);
char * rds_get_pty(void);
char * rds_get_rt(BYTE type);
char * rds_get_ct(void);
char * rds_get_ptyn(void);


extern UINT16 txtAreadyFlag,txtBreadyFlag,ptynReadyFlag,ctReadyFlag;
extern BYTE psReadyFlag,ptyReadyFlag; 
extern BYTE rds_func_flag;
extern BYTE rdsinfo_dispindex;
extern BYTE radio_text_type;

void rds_clear_var(void);
#ifdef SUPPORT_SAA6588
extern void rds_decoder_init(void);
#endif

extern void rds_collect_data();

#endif  //SUPPORT_RDS_FUNCTION

#endif //__RADIO_RDS_H

