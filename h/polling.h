#ifndef	__POLLING_H
#define __POLLING_H

void	polling(void);

// sub
//inline void	polling_1ms(void);
//inline void	polling_10ms(void);
//inline void	polling_500ms(void);
void	polling_timeout(void);
void	polling_rotary(void);

#ifdef SEND_BIT_RATE_TO_IOP  //wsf 040802
void send_bit_rate(void);
#endif 

#ifdef CF_GPIO_CONTROL_COLOR
void Polling_VFD_back_color(void);//wangap
#endif

#ifdef NEW_HOBOVFD
void Polling_VFDPanlBtm(void);
#define START          0
#define BTMDETECT    START+1
#define BTMEJECT     BTMDETECT+1
#define BTMPOWER     BTMEJECT+1
#define BTMBACKWARD  BTMPOWER+1
#define BTMFORWARD   BTMBACKWARD+1
#define BTMSTOP      BTMFORWARD+1
#define BTMPLAY      BTMSTOP+1
#define DETECTHIGH   BTMPLAY+1
#endif

#ifdef PROVIEW_GPIO_KEY
void Polling_VFDPanlBtm_2(void);
void set_cd_type(void);
#define START          0
#define BTMDETECT    START+1
#define BTMEJECT     BTMDETECT+1
#define BTMPOWER     BTMEJECT+1
#define BTMPREV      BTMPOWER+1
#define BTMNEXT      BTMPREV+1
#define BTMSTOP      BTMNEXT+1
#define BTMPAUSEPLAY BTMSTOP+1
#define DETECTHIGH   BTMPAUSEPLAY+1
#endif//#ifdef PROVIEW_GPIO_KEY


#endif
